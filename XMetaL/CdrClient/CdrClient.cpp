/*
 * Ensures that the CDR client files are up-to-date, then launches XMetaL
 * with custom CDR DLL.  See documentation of the InitInstance method
 * (the entry point for a dialog-based application) below for an overview
 * of the processing logic.
 */
#include "stdafx.h"
#include "CdrClient.h"
#include "CdrLogin.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <winsock.h>
#include <wininet.h>
#include <wincrypt.h>
#include <tlhelp32.h>
#include <atlenc.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// For checksum support (OCECDR-4006)
#ifndef BUFSIZE
#define BUFSIZE (BUFSIZ * 16)
#endif
#define MD5LEN 16

/*
 * Local utility functions.
 */
static CComPtr<IXMLDOMNode> getFirstChild(CComPtr<IXMLDOMNode>& node);
static CComPtr<IXMLDOMNode> getNextSibling(CComPtr<IXMLDOMNode>& node);
static CString getNodeName(CComPtr<IXMLDOMNode>& node);
static CString getTextContent(CComPtr<IXMLDOMNode>& element);
static CString getAttribute(CComPtr<IXMLDOMNode>& elem, const TCHAR* name);
static CString findXmetalProgram(CdrClient*);
static CString tryXmetalPath(TCHAR* tail, CdrClient*);
static void usage();
static DWORD find_process_id(const CString name);

/*
 * CdrClient class implementation.
 */
BEGIN_MESSAGE_MAP(CdrClient, CWinApp)
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/*
 * Global object for the application.
 */
CdrClient theApp;

/*
 * CdrClient constructor.
 */
CdrClient::CdrClient() : loaderReplaced(false),
                         serverSettings(NULL),
                         dialog(NULL),
                         logger(NULL) {
    CoInitialize(NULL);
    xmlDomParser.CoCreateInstance(__uuidof(DOMDocument));

    // Figure out which version of XMetaL is running.
    TCHAR buf[256];
    TCHAR* temp = _tgetcwd(buf, sizeof buf / sizeof buf[0]);
    if (!temp) {
        CString msg;
        msg.Format(_T("Failure getting CWD: %S"), strerror(errno));
        throw msg;
    }
    CString cwd = buf;
    cwd.MakeLower();
    if (cwd.Find(_T("softquad")) >= 0) {
        if (cwd.Find(_T("9.0")) >= 0)
            xmver = XM9;
        else if (cwd.Find(_T("17.0")) >= 0)
            xmver = XM17;
        else {
            CString msg;
            msg.Format(_T("Unsupported XMetaL version %s"), buf);
            throw msg;
        }
    }
}

/*
 * Release our objects for server settings and the connection dialog,
 * and close down the COM mechanism.
 */
CdrClient::~CdrClient() {
    delete serverSettings;
    delete dialog;
    delete logger;
    xmlDomParser = NULL;
    CoUninitialize();
}

/*
 * Since this is a dialog-based application, the InitInstance() method
 * is the main entry point for the program's processing logic.
 *
 *   0. Invoke the base class's version of this method.
 *   1. Make sure there isn't already an instance of XMetaL running.
 *   2. Read the options from the application's settings file.
 *   3. Parse the command-line arguments.
 *   4. If we aren't already logged into the CDR, do it.
 *   5. Clear out files we don't want to keep.
 *   6. Install any new files from the server and delete obsolete files.
 *   7. If this program was replaced, launch the new version; otherwise
 *      register the CDR DLL and launch XMetaL.
 */
BOOL CdrClient::InitInstance() {

    try {

        // Create object for logging major events.
        logger = new LogFile();

        // Do this to get password mask characters to display as bullets.
        InitCommonControls();

        // 0. Invoke the base class's version of this method.
        CWinApp::InitInstance();

        // 1. Make sure there isn't already an instance of XMetaL running.
        checkForRunningInstance();

        // 2. Read the settings from the application's state file.
        serverSettings = new ServerSettings(xmlDomParser, this);
        log(_T("Settings loaded -- tier is '") +
            serverSettings->currentGroup + _T("'.\n"));

        // 3. Parse the command-line arguments.
        ParseCommandLine(commandLineOptions);
        logOptions();

        // 4. If we aren't already logged into the CDR, do it.
        if (!createCdrSession())
            return FALSE;

        // 5. Clear out temporary caches and unwanted XMetaL files.
        clearCaches();

        // 6. Install any new files from the server and delete obsolete files.
        refreshFiles();

        // 7. Launch new version of this program, if any; else start XMetal.
        if (loaderReplaced)
            runAgain();
        else
            launchClient();
    }

    // Bail out for failures.
    catch (const TCHAR* error) {
        AfxMessageBox(error);
        log(CString(error) + _T("\n"));
    }
    catch (const CString error) {
        AfxMessageBox(error);
        log(error + _T("\n"));
    }
    catch (...) {
        AfxMessageBox(_T("Unexpected failure ... closing"));
        log(_T("Unexpected failure ... closing\n"));
    }

    // We're done; FALSE means don't start the Windows message pump.
    return FALSE;
}

/*
 * Loads information for connection to the CDR servers from the XML
 * configuration file, stored locally to remember the values the
 * user last gave us.
 */
ServerSettings::ServerSettings(CComPtr<IXMLDOMDocument>& xmlDomParser,
                               CdrClient* client) {

    // Parse the XML settings file.
    if (!xmlDomParser)
        throw _T("XML parser not created");
    VARIANT_BOOL success;
    CComVariant fileName = SETTINGS_FILE;

    // If the settings file doesn't exist yet, set default tier names.
    if (FAILED(xmlDomParser->load(fileName, &success)) || !success) {
        serverGroups.push_back(ServerGroup(_T("PROD"),
                                           _T("cdr.cancer.gov"),
                                           _T("cdrapi.cancer.gov")));
        serverGroups.push_back(ServerGroup(_T("STAGE"),
                                           _T("cdr-stage.cancer.gov"),
                                           _T("cdrapi-stage.cancer.gov")));
        serverGroups.push_back(ServerGroup(_T("QA"),
                                           _T("cdr-qa.cancer.gov"),
                                           _T("cdrapi-qa.cancer.gov")));
        serverGroups.push_back(ServerGroup(_T("DEV"),
                                           _T("cdr-dev.cancer.gov"),
                                           _T("cdrapi-dev.cancer.gov")));
        return;
    }

    // Start at the top-level element.
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting elements from settings document");

    // Walk through the nodes extracting the remembered settings.
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("ServerGroup"))
            serverGroups.push_back(ServerGroup(node));
        else if (nodeName == _T("CurrentUser"))
            currentUser = getTextContent(node);
        else if (nodeName == _T("CurrentGroup"))
            currentGroup = getTextContent(node);
        node = getNextSibling(node);
    }
}

/*
 * Creates a new XML document file to remember the current server
 * settings, overwriting an existing file if there is one.  All
 * of the characters will be ASCII (mostly DNS names and strings
 * representing decimal port numbers).
 */
void ServerSettings::serialize(const CString& name, CdrClient* client) const {

    // Now update the new four-tier settings file.
    CStdioFile file;
    CFileException e;
    UINT flags = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone;

    BOOL success = file.Open(name, flags);
    if (!success) {
        _TCHAR errmsg[1028];
        int    len = 1024;
        e.GetErrorMessage(errmsg, len);
        throw CString(errmsg);
    }
    file.WriteString(_T("<CDRServerSettings>\n"));
    file.WriteString(_T(" <CurrentUser>"));
    file.WriteString((LPCTSTR)currentUser);
    file.WriteString(_T("</CurrentUser>\n"));
    file.WriteString(_T(" <CurrentGroup>"));
    file.WriteString((LPCTSTR)currentGroup);
    file.WriteString(_T("</CurrentGroup>\n"));
    for (size_t i = 0; i < serverGroups.size(); ++i)
        serverGroups[i].serialize(file);
    file.WriteString(_T("</CDRServerSettings>\n"));
    file.Close();
}

/*
 * Constructs a ServerGroup object from its serialized form in the
 * DOM node from the XML document for remembered server settings.
 */
ServerSettings::ServerGroup::ServerGroup(CComPtr<IXMLDOMNode>& node) {
    groupName = getAttribute(node, _T("Name"));
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("CDRServer"))
            cdrServer = getTextContent(child);
        else if (nodeName == _T("APIServer"))
            apiServer = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Create a group for a new settings file, with default names for the group.
 *
 * Pass:
 *   n - CString for group name
 *   c - CString for CDR server DNS name
 *   a - CString for CDR API server DNS name
 */
ServerSettings::ServerGroup::ServerGroup(CString n, CString c, CString a) {
    groupName = n;
    cdrServer = c;
    apiServer = a;
}

/*
 * Write the XML document fragment representing this server settings
 * group.
 */
void ServerSettings::ServerGroup::serialize(CStdioFile& file) const {
    file.WriteString(_T(" <ServerGroup Name=\""));
    file.WriteString((LPCTSTR)groupName);
    file.WriteString(_T("\">\n"));
    file.WriteString(_T("  <CDRServer>"));
    file.WriteString((LPCTSTR)cdrServer);
    file.WriteString(_T("</CDRServer>\n"));
    file.WriteString(_T("  <APIServer>"));
    file.WriteString((LPCTSTR)apiServer);
    file.WriteString(_T("</APIServer>\n"));
    file.WriteString(_T(" </ServerGroup>\n"));
}

/*
 * Looks up the group corresponding to the name specified by the caller.
 * Returns the address of the object for the group.
 */
ServerSettings::ServerGroup* ServerSettings::findGroup(const CString& name) {
    for (size_t i = 0; i < serverGroups.size(); ++i)
        if (serverGroups[i].groupName == name)
            return &serverGroups[i];
    return NULL;
}

/*
 * Sets the initial values for settings which can be specified on the
 * command line.
 */
CdrCommandLineOptions::CdrCommandLineOptions() {
    skipCdrLogin     = false;
    skipDialog       = false;
    skipRefresh      = false;
    skipReload       = false;
    runAgain         = false;
    serverDebugLevel = 1;
    clientDebugLevel = 1;
    TCHAR* envClient = _tgetenv(_T("CDR_CLIENT_DEBUG_LEVEL"));
    if (envClient) {
        errno = 0;
        int level = (int)_tcstol(envClient, NULL, 10);
        if (!errno)
            clientDebugLevel = level;
    }
    TCHAR* envServer = _tgetenv(_T("CDR_SERVER_DEBUG_LEVEL"));
    if (envServer) {
        errno = 0;
        int level = (int)_tcstol(envServer, NULL, 10);
        if (!errno)
            serverDebugLevel = level;
    }
}

/*
 * Overrides the ParseParam method of the base CCommandLineInfo class.
 * This method is invoked indirectly when we call the MFC function
 * ParseCommandLine with a reference to our CdrCommandLineOptions
 * object.
 */
void CdrCommandLineOptions::ParseParam(const TCHAR* param,
                                       BOOL flag, BOOL last) {
    CString msg;
    CString previousOption = currentOption;
    currentOption = _T("");
    if (flag) {
        if (!_tcscmp(param,  _T("-skip-login")))
            skipCdrLogin = true;
        else if (!_tcscmp(param, _T("-skip-dialog")))
            skipDialog = true;
        else if (!_tcscmp(param, _T("-skip-refresh")))
            skipRefresh = true;
        else if (!_tcscmp(param, _T("-skip-reload")))
            skipReload = true;
        else if (!_tcscmp(param, _T("-server-debug-level")))
            currentOption = _T("server-debug-level");
        else if (!_tcscmp(param, _T("-debug-level")))
            currentOption = _T("debug-level");
        else if (!_tcscmp(param, _T("-run-again"))) {
            runAgain = true;
            _tremove(RELAUNCH_SCRIPT);
        }
        else {
            usage();
        }
    }
    else {
        CString msg;
        msg.Format(_T("param=%s previousOption=%s"), param, previousOption);
        if (previousOption == _T("server-debug-level")) {
            errno = 0;
            int level = _tcstol((LPCTSTR)param, NULL, 10);
            if (!errno)
                serverDebugLevel = level;
            else
                usage();
        }
        else if (previousOption == _T("debug-level")) {
            errno = 0;
            int level = _tcstol((LPCTSTR)param, NULL, 10);
            if (!errno)
                clientDebugLevel = level;
            else
                usage();
        }
    }
}

/*
 * Record the command-line options specified and the client and server
 * debugging level, if the client debugging level is 2 or higher.
 */
void CdrClient::logOptions() {
    if (commandLineOptions.runAgain)
        log(_T("Option --run-again specified.\n"), 2);
    if (commandLineOptions.skipCdrLogin)
        log(_T("Option --skip-login specified.\n"), 2);
    if (commandLineOptions.skipDialog)
        log(_T("Option --skip-dialog specified.\n"), 2);
    if (commandLineOptions.skipReload)
        log(_T("Option --skip-reload specified.\n"), 2);
    if (commandLineOptions.skipRefresh)
        log(_T("Option --skip-refresh specified.\n"), 2);
    CString buf;
    buf.Format(_T("Client logging level: %d.\n"),
               commandLineOptions.clientDebugLevel);
    log(buf, 2);
    buf.Format(_T("Server logging level: %d.\n"),
               commandLineOptions.serverDebugLevel);
    log(buf, 2);
    log(_T("Tier is '") + serverSettings->currentGroup + _T("'.\n"), 1);
    TCHAR* v = xmver == XM17 ? _T("17.0") : _T("9.0");
    buf.Format(_T("Running XMetaL version %s\n"), v);
    log(buf, 0);
}

/*
 * Tell the user how to invoke the program.  Will be displayed in a
 * dialog window by the InitInstance method where the exception is caught.
 */
void usage() {

    throw _T("Usage: CdrClient [options]           \n\n")
          _T("available options:\n")
          _T("  --run-again\n")
          _T("  --skip-login\n")
          _T("  --skip-dialog\n")
          _T("  --skip-refresh\n")
          _T("  --skip-reload\n")
          _T("  --debug-level N\n")
          _T("  --server-debug-level N\n");
}

/*
 * Request a session ID from the CDR web server's login.py script.
 * The directory in which this script resides is protected, so we
 * submit the user's NIH domain account credentials to be verified
 * by Windows authentication. If the credentials are invalid, an
 * exception will be thrown. If the credentials pass Windows
 * authentication, but the domain account name is not found in
 * the CDR account mapping table, the HTTP status code returned
 * will be 403 (forbidden), and we'll throw our own exception here.
 */
static CString login(CdrClient* cli, CString host, CString uid, CString pwd) {
    CString response;
    CInternetSession session(_T("CDR Client"));
    CHttpConnection* conn = NULL;
    CHttpFile* file = NULL;
    BOOL success = FALSE;
    INTERNET_PORT port = INTERNET_DEFAULT_HTTPS_PORT;
    const TCHAR* target = _T("/cgi-bin/secure/login.py");
    conn = session.GetHttpConnection(host, port, uid, pwd);
    DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
    file = conn->OpenRequest(_T("GET"), target, NULL, 1, NULL, NULL, flags);
    for (int i = 0; !success && i < 3; ++i) {
        DWORD secFlags;
        file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
        secFlags |= SECURITY_IGNORE_ERROR_MASK;
        file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
        try {
            cli->log(_T("Calling login SendRequest().\n"), 2);
            success = file->SendRequest();
        }
        catch (CInternetException* e) {
            CString errmsg;
            TCHAR msg[1024];
            if (e->GetErrorMessage(msg, 1024))
                errmsg.Format(_T("login SendRequest(): %s"), msg);
            else
                errmsg.Format(_T("login SendRequest() error: %d\n"),
                              e->m_dwError);
            if (errmsg.Right(1) != _T("\n"))
                errmsg += _T("\n");
            cli->log(errmsg);
        }
        catch (...) {
            cli->log(_T("Unspecified exception thrown by SendRequest()"));
        }
    }
    if (!success)
        throw _T("Failure submitting logon request to server");
    DWORD result;
    file->QueryInfoStatusCode(result);
    std::cerr << "status code=" << result << "\n";
    if (result != HTTP_STATUS_OK) {
        CString err;
        err.Format(_T("HTTP status code from login request: %lu"), result);
        throw err;
    }
    static char buf[1024 * 1024];
    UINT nread = file->Read(buf, sizeof buf);
    while (nread > 0) {
        response += CString(buf, (int)nread);
        nread = file->Read(buf, sizeof buf);
    }
    file->Close();
    conn->Close();
    return response.Trim();
}

/*
 * If we have been invoked by ourselves, a login session will already have
 * been created for the user and the ID for the session will have been
 * passed to us as part of the environment strings provided to the process.
 * If not we put up the logon dialog window, in which the user enters
 * her CDR account's credentials (and optionally modifies the values
 * used to connect to the CDR and client refresh servers).  If the user
 * confirms the request to log into the CDR, we create the logon command,
 * submit it to the CDR server, extract the session ID, and set the
 * environment variables which will be passed to the CDR XMetaL custom
 * DLL.  Returns false if the user cancels the logon request, otherwise
 * returns true.  An exception is thrown if the logon is unsuccessful.
 *
 * The XML for the client's request to logon has the following structure:
 *
 *   CdrLogon
 *     UserName [string]
 *     Password [string]
 *
 * All CDR client requests are sent as an XML document wrapped as
 * described above in the comments for the CdrSocket type, which handles
 * packing the individual commands into the CdrCommandSet document.
 *
 * The server's response has the following structure:
 *
 *   CdrLogonResp
 *     SessionId [string]
 *
 * The CdrLogonResp element is wrapped by the document-level element
 * CdrResponseSet, as described above for the CdrSocket type.
 *
 * Change of strategy, mandated by CBIIT: we now integrate the CDR
 * logon process with the NIH Active Directory, using Windows
 * authentication. (2015-01-10, OCECDR-3849).
 */
bool CdrClient::createCdrSession() {

    // See if we have already been logged in to the CDR.
    TCHAR* envId = _tgetenv(_T("CDRSession"));
    if (envId) {
        sessionId = envId;
        extractServerSettings();
        log(_T("Already logged into the CDR on ") + cdrServer + _T("\n"), 1);
        log(_T("Session: ") + sessionId + _T("\n"), 1);
        return true;
    }

    // Put up the login dialog window unless we've been asked not to.
    if (!commandLineOptions.skipDialog) {
        CWaitCursor waitCursor;
        dialog = new CdrLoginDlg(serverSettings);
        INT_PTR nResponse = dialog->DoModal();
        if (nResponse == IDOK) {

            // Remember any changes to the server settings.
            serverSettings->currentUser = dialog->uid;
            serverSettings->serialize(SETTINGS_FILE, this);

            // Create the logon command.
            CString uidElem;
            CString pwdElem;

            // Submit the login credentials to the login script.
            extractServerSettings();
            CString uid(dialog->uid);
            CString pwd(dialog->pwd);
            CString tier(serverSettings->currentGroup);
            sessionId = login(this, cdrServer, uid, pwd);
            if (sessionId.IsEmpty())
                throw _T("empty session string received from logon server");
            CString logMessage;
            logMessage.Format(_T("Logged into %s as %s\n"),
                              cdrServer, dialog->uid);
            log(logMessage, 1);
            log(_T("Session: ") + sessionId + _T("\n"), 1);
            log(_T("Server: ") + cdrServer + _T("\n"), 2);

            // Inject some important values into the environment.
            CString clientDebugEnv;
            CString serverDebugEnv;
            clientDebugEnv.Format(_T("CDR_CLIENT_DEBUG_LEVEL=%d"),
                                  commandLineOptions.clientDebugLevel);
            serverDebugEnv.Format(_T("CDR_SERVER_DEBUG_LEVEL=%d"),
                                  commandLineOptions.serverDebugLevel);
            _tputenv((LPCTSTR)(_T("CDRUser=") + dialog->uid));
            _tputenv((LPCTSTR)(_T("CDRSession=") + sessionId));
            _tputenv((LPCTSTR)(_T("CDR_HOST=") + cdrServer));
            _tputenv((LPCTSTR)(_T("CDR_PORT=443")));
            _tputenv((LPCTSTR)(_T("API_HOST=") + apiServer));
            _tputenv((LPCTSTR)(_T("CDR_TIER=") + tier));
            _tputenv((LPCTSTR)clientDebugEnv);
            _tputenv((LPCTSTR)serverDebugEnv);
            return true;
        }
        else if (nResponse == IDCANCEL) {
            log(_T("User cancelled logon; shutting down ...\n"), 1);
            return false;
        }
    }
    return true;
}

/*
 * Find the currently-selected server group, and extract the server
 * names and ports into private member variables of the CdrClient
 * object.  Invoked by createCdrSession().
 */
void CdrClient::extractServerSettings() {
    log(_T("Extracting settings for '") + serverSettings->currentGroup +
        _T("'\n"), 2);
    for (size_t i = 0; i < serverSettings->serverGroups.size(); ++i) {
        ServerSettings::ServerGroup* group = &serverSettings->serverGroups[i];
        if (serverSettings->currentGroup == group->groupName) {
            if (!group->cdrServer.IsEmpty()) {
                cdrServer = group->cdrServer;
                log(_T("CDR server=") + cdrServer + _T("\n"), 2);
            }
            if (!group->apiServer.IsEmpty())
                apiServer = group->apiServer;
        }
    }
}

/*
 * This method accomplishes two goals.  First, we clear out any cached
 * multimedia documents so we don't fill up the user's disk with unwanted
 * bulk.  Second, we avoid stepping into some nasty XMetaL bugs.  XMetaL
 * does not behave correctly when we install changed DTDs for our document
 * types, even though the file timestamps for the DTDs are more recent
 * than the dates on XMetaL's compiled RLX files for these DTDs.  Sometimes
 * XMetaL ignores our changes; at other times XMetaL simply crashes.  We
 * eliminate these problems by clearing out XMetaL's compiled RLX files.
 */
void CdrClient::clearCaches() {

    log(_T("Clearing out unwanted cached and compiled files.\n"), 1);
    deleteFiles(_T(".\\Cdr\\Media\\*"));
    deleteRlxFiles(_T("."));
}

/*
 * Modified workaround to cope with the fact that our original workaround
 * was broken when XMetaL changed the location where it wrote the compiled
 * RLX files. This version is recursive.
 */
void CdrClient::deleteRlxFiles(const CString& where) {
    CString pattern(where);
    pattern += _T("\\*.*");
    CFileFind finder;
    BOOL more = finder.FindFile(pattern);
    while (more) {
        more = finder.FindNextFile();
        if (!finder.IsDots()) {
            CString path = finder.GetFilePath();
            if (finder.IsDirectory())
                deleteRlxFiles(path);
            else if (!path.Right(4).CompareNoCase(_T(".rlx"))) {
                try {
                    CFile::Remove(path);
                }
                catch (...) {
                    log(_T("Failure removing " + path + _T("\n")));
                }
            }
        }
    }
}

/*
 * Helper method invoked by clearCaches() with common code to find
 * all files whose pathnames match a string pattern, and delete them.
 */
void CdrClient::deleteFiles(const CString& pattern) {
    CFileFind fileFinder;
    BOOL more = fileFinder.FindFile(pattern);
    while (more) {
        more = fileFinder.FindNextFile();
        if (!fileFinder.IsDots()) {
            CString filePath = fileFinder.GetFilePath();
            try {
                CFile::Remove(filePath);
            }
            catch (...) {
                log(_T("Failure removing ") + filePath + _T("\n"));
            }
        }
    }
}

/*
 * This is where we do the work for which this program was principally
 * created: make sure all of the files needed by the CDR client are
 * up to date.  This is accomplished by communicating via the network
 * with a server which has a set of the current version of all of
 * these files, as well as a list of all of those files (the "Manifest")
 * with pathname and checksum for each file, as well as a header (called
 * a "Ticket" below) identifying the server on which the manifest was
 * generated, as well as a cumulative checksum for the client files.
 *
 * The first time this program connects to the client refresh server,
 * it sends a stub version of the manifest to the server, asking it
 * to send a complete set of the client files.  The server does so
 * and the client installs these files locally.  A copy of the manifest
 * document is included in the set.
 *
 * For subsequent invocations of this program, the client first asks
 * the client refresh server if any changes have been made to the file
 * set since the previous session.  It does this by extracting the
 * header ("Ticket") from the stored manifest document and sending it
 * to the server.  If the server name and checksum match those in
 * the server's copy of the manifest, the response "<Current>Y</Current>"
 * is returned to the client, and no further work needs to be done.
 *
 * In the event that we detect tampering with the local client files
 * (we check to ensure that all of the files in our local copy of the
 * manifest are present, with checksums which match those in the
 * manifest exactly), then we discard the manifest and get a complete
 * new set, as if this were the first time we had connected to the
 * server.  A possible side effect is that the client might retain
 * a file which has been removed from the complete set of client files,
 * and which the server would have asked to be deleted, had it received
 * the manifest listing that file.  This is extremely unlikely to present
 * a problem.
 *
 * If the server determines that changes have occurred, it returns the
 * response "<Current>N</Current>" and the client sends a copy of its
 * complete manifest file to the server.  The server compares its own
 * copy of the manifest with the copy from the client and builds two
 * lists: one for files which the client currently has but are no longer
 * in the set of files needed by the client, and a second list of files
 * which the client does not yet have, or for which the client's copy
 * differs from that on the server.  If the second list is not empty,
 * the server creates a compressed archive containing the files
 * represented by this list.  An XML document ("Updates") is sent back
 * to the client with a ZipFile child element containing the bytes
 * for the archive containing the new and updated client files, and
 * an optional "Delete" element with one or more child "File" elements.
 * If the ZipFile element is present and non-empty, its contents are
 * installed locally on the client machine.  If there are any files to
 * be removed, they are then deleted.
 *
 * For additional information about the structure of the XML responses
 * returned by the server, see the interface documentation for the
 * Manifest and Updates types.
 *
 * In summary, the following sequence of exchanges would take place
 * if the client's files are not completely up to date, and the
 * refresh process is successful:
 *
 *      1. Client sends <Ticket>...</Ticket> document.
 *      2. Server responds with <Current>N</Current>.
 *      3. Client sends <Manifest>...</Manifest> document.
 *      4. Server responds with <Updates>...</Updates> document.
 */
void CdrClient::refreshFiles() {

    // Don't do anything if we're asked to skip this step (for debugging).
    if (commandLineOptions.skipRefresh)
        return;

    // Start out with stubs for the manifest document and ticket header.
    CString manifestXml = _T("<Manifest/>");
    CString ticketXml;

    // Parse the local copy of the manifest, if it exists.
    try {
        Manifest manifest(xmlDomParser);

        // Make sure no one has manually changed any of the client files.
        CString mismatch = manifest.validate(this);
        if (mismatch.IsEmpty()) {
            manifestXml = manifest.manifestXml;
            ticketXml   = manifest.ticketXml;
        }
    }

    // Errors are not fatal; log them and use the stub manifest.
    catch (const TCHAR* err) {
        CString msg;
        msg.Format(_T("Failure parsing local manifest: %s\n"), err);
        log(msg);
    }

    // If we found a valid manifest, ask the server if it's current.
    if (ticketXml.IsEmpty())
        log(_T("No local ticket available; refresh forced.\n"), 1);
    else {
        log(_T("Asking ") + cdrServer +
            _T(" if any files have changed.\n"), 1);
        CString response = sendHttpCommand(ticketXml);
        TicketValidation ticketValidation(xmlDomParser, response);
        if (ticketValidation.response == _T("Y")) {
            log(_T("Local files are up to date.\n"), 1);
            return;
        }
    }

    // Make sure the user doesn't think we've died if this takes a long time.
    CdrProgressDlg progressDialog;
    progressDialog.Create(progressDialog.IDD, m_pMainWnd);
    progressDialog.Init();
    progressDialog.ShowWindow(SW_SHOWNORMAL);
    progressDialog.Advance();

    // There are changes; find out what they are.  May take some time.
    log(_T("Some files have changed; sending manifest for local files.\n"), 1);
    CString response = sendHttpCommand(manifestXml);
    progressDialog.Advance();
    Updates updates = Updates(xmlDomParser, response);

    // If there are new or changed files, retrieve and unpack them.
    if (!updates.zipBytes.empty())
        getNewFiles(updates.zipBytes, progressDialog);
    progressDialog.Advance();

    // If we've been asked to delete any files, do so here.
    std::list<CString>::const_iterator iter = updates.deletes.begin();
    while (iter != updates.deletes.end()) {
        log(_T("Removing ") + *iter + _T(" on instructions from server\n"), 1);
        try {
            CFile::Remove((LPCTSTR)*iter);
        }
        catch (...) {
            log(_T("Unable to remove ") + *iter + _T("\n"));
        }
        ++iter;
    }

    // Added 2014-02-18: sweep to remove older versions of this program.
    cleanOutOlderVersions();
    log(_T("Refresh of local files complete.\n"), 1);
}

/*
 * Compare two CString values, case insensitive.
 */
static bool compareNoCase(const CString& s1, const CString& s2) {
    return s1.CompareNoCase(s2) < 0;
}

/*
 * Determine whether the file name specified matches the pattern for
 * the CDR client loader executable (CdrClient-YYYYMMDDHHMMSS.exe).
 */
static bool isClientProgram(const CString& name) {
    if (name.GetLength() != 28)
        return false;
    CString start = name.Left(10);
    start.MakeLower();
    if (start != _T("cdrclient-"))
        return false;
    CString tail = name.Right(4);
    tail.MakeLower();
    if (tail != _T(".exe"))
        return false;
    CString middle = name.Mid(10, 14);
    return middle.SpanIncluding(_T("0123456789")) == middle;
}

/*
 * Collect the names of all files in the current directory whose names
 * match the pattern CdrClient-YYYYMMDDHHMMSS.exe, sort them (without
 * regard to case), and delete all but the most recent five of these files.
 */
void CdrClient::cleanOutOlderVersions() {
    std::vector<CString> files;
    CFileFind finder;
    BOOL more = finder.FindFile(_T("CdrClient-*.exe"));
    CString appName = AfxGetAppName();
    while (more) {
        more = finder.FindNextFile();
        CString name = finder.GetFileName();
        if (isClientProgram(name) && name != appName)
            files.push_back(name);
    }
    std::sort(std::begin(files), std::end(files), compareNoCase);
    if (files.size() > 10) {
        files.resize(files.size() - 10);
        std::vector<CString>::iterator iter = files.begin();
        while (iter != files.end()) {
            log(_T("Removing old client ") + *iter + _T("\n"), 1);
            try {
                CFile::Remove((LPCTSTR)*iter);
            }
            catch (...) {
                log(_T("Unable to remove client ") + *iter + _T("\n"));
            }
            ++iter;
        }
    }
}

/*
 * Parse the XML document for a manifest for a client file set,
 * and populate the data members of the object with the values
 * found in the document.  Throws a string-based exception if
 * the document is missing or corrupt.  See the interface documentation
 * for this class for the structure of the manifest XML document.
 */
Manifest::Manifest(CComPtr<IXMLDOMDocument>& xmlDomParser) {

    // Parse the document.
    VARIANT_BOOL success;
    CComVariant fileName = MANIFEST_FILE;
    if (FAILED(xmlDomParser->load(fileName, &success)) || !success)
        if (PathFileExists(MANIFEST_FILE))
            throw _T("Manifest file is corrupt");
        else
            throw _T("User has no local manifest file");

    // Save the string representation of the document in case we need to
    // send it to the server or log it.
    CComBSTR xmlString;
    xmlDomParser->get_xml(&xmlString);
    manifestXml = xmlString;

    // Walk through the children of the document element and extract the
    // ticket header and the list of files.
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting elements from manifest");
    CString elemName = getNodeName((CComPtr<IXMLDOMNode>)docElem);
    if (elemName != _T("Manifest"))
        throw _T("Expected Manifest element; got ") + elemName;
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("Ticket")) {
            ticket = Ticket(node);
            CComBSTR xmlString;
            node->get_xml(&xmlString);
            ticketXml = xmlString;
        }
        else if (nodeName == _T("FileList")) {
            CComPtr<IXMLDOMNode> child = getFirstChild(node);
            while (child) {
                CString nodeName = getNodeName(child);
                if (nodeName == _T("File"))
                    fileList.push_back(File(child));
                child = getNextSibling(child);
            }
        }
        node = getNextSibling(node);
    }
}

/*
 * Populates this object with the values found in the DOM node for
 * its XML representation.
 */
Ticket::Ticket(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("Application"))
            application = getTextContent(child);
        else if (nodeName == _T("Host"))
            host = getTextContent(child);
        else if (nodeName == _T("Author"))
            author = getTextContent(child);
        else if (nodeName == _T("Checksum"))
            checksum = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Extract the pathname and checksum for a single node in the manifest's
 * fileList vector.
 */
File::File(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("Name"))
            name = getTextContent(child);
        else if (nodeName == _T("Checksum"))
            checksum = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Get the MD5 checksum for this file. We're calculating the value
 * from the bytes on the user's disk, rather than returning the
 * value we got for the file from the manifest, to which we'll
 * compare the return value from this method.
 */
CString File::getChecksum() const {

    // Return value for failure.
    CString err;

    // Open the file for reading.
    HANDLE h = ::CreateFile((LPCTSTR)name, GENERIC_READ, FILE_SHARE_READ, NULL,
                            OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
    if (!h) {
        err.Format(_T("failure getting checksum for %s"), name);
        return err;
    }

    // Get a handle for the cryptography provider.
    HCRYPTPROV p = 0;
    if (!::CryptAcquireContext(&p, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        ::CloseHandle(h);
        err.Format(_T("failure getting cryptography provider for %s"), name);
        return err;
    }

    // Create a hash for the checksum.
    HCRYPTHASH hash = 0;
    if (!::CryptCreateHash(p, CALG_MD5, 0, 0, &hash)) {
        ::CryptReleaseContext(p, 0);
        ::CloseHandle(h);
        err.Format(_T("failure creating hash for %s"), name);
        return err;
    }

    // Read the file.
    BOOL ok = FALSE;
    BYTE buffer[BUFSIZE];
    DWORD count = 0;
    while ((ok = ReadFile(h, buffer, BUFSIZE, &count, NULL)) == TRUE) {
        if (count == 0)
            break;
        if (!CryptHashData(hash, buffer, count, 0)) {
            ::CryptReleaseContext(p, 0);
            ::CryptDestroyHash(hash);
            ::CloseHandle(h);
            err.Format(_T("unable to hash data for %s"), name);
            return err;
        }
    }
    ::CloseHandle(h);

    // Check for failure reading the file.
    if (!ok) {
        ::CryptReleaseContext(p, 0);
        ::CryptDestroyHash(hash);
        err.Format(_T("failure reading %s"), name);
        return err;
    }

    // Extract the bytes from the hash.
    BYTE hash_bytes[MD5LEN];
    count = MD5LEN;
    ok = CryptGetHashParam(hash, HP_HASHVAL, hash_bytes, &count, 0);
    ::CryptReleaseContext(p, 0);
    ::CryptDestroyHash(hash);
    if (!ok) {
        err.Format(_T("failure extracting checksum for %s"), name);
        return err;
    }

    // Assemble the string representation for the hash.
    const TCHAR digits[] = _T("0123456789abcdef");
    CString md5;
    for (DWORD i = 0; i < count; ++i) {
        md5 += digits[hash_bytes[i] >> 4];
        md5 += digits[hash_bytes[i] & 0xf];
    }
    return md5;
}

/*
 * Determine whether we can bypass the check whether this file has been
 * changed. We don't check the relaunch script, because that's deleted
 * after a one-time use. The manifest file is already checked using its
 * Ticket block. The builds of this program have their build time
 * embedded in their names, so if a new build is sent it will have a
 * different name. We check everything else.
 */
bool File::skipValidation() const {
    CString relaunchScript = CString(RELAUNCH_SCRIPT).MakeLower();
    CString manifestFile = CString(MANIFEST_FILE).MakeLower();
    CString lowerName(name);
    lowerName.MakeLower();
    if (lowerName.Find(relaunchScript) != -1)
        return true;
    if (lowerName.Find(manifestFile) != -1)
        return true;
    if (lowerName.Find(_T("cdr.dll")) != -1)
        return true;
    if (lowerName.Find(_T("cdrclient-20")) != -1) {
        if (lowerName.Find(_T(".exe")) != -1)
            return true;
    }
    return false;
}

/*
 * Compares the manifest with the files on the local disk, making sure
 * they're all present and have matching checksums.  Returns an empty
 * string if there are no discrepancies; otherwise returns a string
 * identifying the first mismatch or missing file detected.  We don't
 * bother checking the script to invoke ourselves a second time, because
 * we delete that file as soon as we are invoked with the --run-again
 * command-line option, in order to prevent infinite relaunching.  For
 * a more detailed explanation of how the relaunch works (and why
 * and when it is needed), see the comment for the implementation
 * of the CdrClient::runAgain() method.
 *
 * 2014-02-10: Modified to skip check of CdrClient-<timestamp>.exe.
 * 2015-12-07: Use checksums instead of timestamps (OCECDR-4006).
 */
CString Manifest::validate(CdrClient* client) {
    std::vector<File>::const_iterator file = fileList.begin();
    while (file != fileList.end()) {
        if (!file->skipValidation()) {
            CString clientChecksum = file->getChecksum();
            if (clientChecksum != file->checksum) {
                client->log(_T("Client ") + file->name + _T(": ") +
                            clientChecksum + _T("\n"), 1);
                client->log(_T("Server ") + file->name + _T(": ") +
                            file->checksum + _T("\n"), 1);
                CString msg;
                msg.Format(_T("%s: checksum mismatch"), file->name);
                AfxMessageBox(msg);
                return file->name + _T(" mismatch");
            }
        }
        ++file;
    }
    return _T("");
}

/*
 * Send an XML document via HTTP to the CDR client refresh service, then
 * retrieve and return the server's response.
 *
 * See https://docs.microsoft.com/en-us/windows/desktop/WinInet/option-flags
 * for documentation of the Microsoft options flags.
 */
CString CdrClient::sendHttpCommand(const CString& cmd, const TCHAR* target) {

    // Build the strings needed for submitting the request.
    CInternetSession session;
    CString          response;
    CString          headers;
    CHttpConnection* conn    = NULL;
    CHttpFile*       file    = NULL;
    CStringA         ascii   = (CStringA)cmd.GetString();
    CStringA::PCXSTR bytes   = ascii.GetString();
    DWORD            length  = ascii.GetLength();
    BOOL             success = FALSE;
    try {
        headers.Format(_T("Content-Type: text/xml; charset=utf-8\n")
                       _T("X-Debug-Level: %d\n"),
                       commandLineOptions.serverDebugLevel);
        log(_T("HTTP headers:\n") + headers, 3);

        // Connect the to client refresh server.
        try {
            INTERNET_PORT port = INTERNET_DEFAULT_HTTPS_PORT;
            DWORD flags = INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_SECURE;
            conn = session.GetHttpConnection(cdrServer, port);
            log(_T("Got HTTP connection to ") + cdrServer + _T("\n"), 3);
            file = conn->OpenRequest(_T("POST"), target, NULL, 1, NULL, NULL,
                                     flags);
            log(_T("POST request opened successfully.\n"), 3);
        }
        catch (...) {
            throw _T("Unable to connect to client update server");
        }

        // This fails occasionally; give the server three chances.
        for (int i = 0; !success && i < 3; ++i) {

            // It appears that our options are ignored; we still get the error
            // ERROR_INTERNET_INVALID_CA (decimal 12045) trying to connect
            // to a CBIIT server with a self-signed cert.
            // 2012-10-25 update: it turns out that invoking the SetOption
            // method on the connection object before creating the request
            // object (CHttpFile) doesn't do anything.  It also turns out
            // that the CHttpFile class supports QueryOption and SetOption,
            // even though Microsoft omitted these methods from the MSDN
            // documentation for the class.
            DWORD secFlags;
            file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            CString flagMessage;
            flagMessage.Format(_T("Original security flags: %08X\n"),
                               secFlags);
            log(flagMessage, 3);
            secFlags |= SECURITY_IGNORE_ERROR_MASK;
            file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            flagMessage.Format(_T("New security flags: %08X\n"), secFlags);
            log(flagMessage, 3);

            try {
                log(_T("Calling SendRequest().\n"), 3);
                success = file->SendRequest(headers, (void *)bytes, length);
            }
            catch (CInternetException* e) {
                CString errmsg;
                TCHAR msg[1024];
                if (e->GetErrorMessage(msg, 1024))
                    errmsg.Format(_T("SendRequest(): %s"), msg);
                else
                    errmsg.Format(_T("SendRequest() error: %d\n"),
                                  e->m_dwError);
                if (errmsg.Right(1) != _T("\n"))
                    errmsg += _T("\n");
                log(errmsg);
            }
        }
        if (!success)
            throw _T("Failure submitting request to update server");

        // Find out if the mechanics of the exchange were successful.
        DWORD result;
        file->QueryInfoStatusCode(result);
        if (result != HTTP_STATUS_OK) {
            CString err;
            err.Format(_T("HTTP status code from update server: %lu"),
                       result);
            throw err;
        }

        // Read the response in chunks.
        try {
            CString msg;
            char buf[1024];
            UINT nread = file->Read(buf, sizeof buf);
            msg.Format(_T("Read %u bytes.\n"), nread);
            log(msg, 4);
            while (nread > 0) {
                response += CString(buf, (int)nread);
                nread = file->Read(buf, sizeof buf);
                msg.Format(_T("Read %u bytes.\n"), nread);
                log(msg, 4);
            }
        }

        // Haven't had this ever fail before, but you never know.
        catch (...) {
            throw _T("Failure reading response from update server");
        }
    }
    catch (...) {
        if (conn)
            conn->Close();
        if (file)
            file->Close();
        throw;
    }
    conn->Close();
    file->Close();
    log(_T("HTTP response:\n") + response + _T("\n"), 3);
    return response;
}

/*
 * Constructor for parsing the server response when we ask if our
 * manifest is up to date.  Throws a string-based exception if
 * we are unable to parse the response's XML document.
 */
TicketValidation::TicketValidation(CComPtr<IXMLDOMDocument>& xmlDomParser,
                                   const CString& xmlString) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xmlString);
    if (FAILED(xmlDomParser->loadXML(bstrXml, &success)))
        throw _T("Failure parsing ticket validation response");
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting ticket validation response");
    response = getTextContent((CComPtr<IXMLDOMNode>)docElem);
}

/*
 * Constructor for parsing the server response when we ask it to
 * compare our copy of the manifest with its copy and determine
 * what the differences are, if any.  Throws a string-based
 * exception if we are unable to parse the response's XML
 * document.
 *
 * Extracts the bytes for the compressed archive containing new and/or
 * modified files.  Decodes the bytes into a non-Unicode string object
 * which is saved as the bytes data member of the object.  Throws a
 * string-based exception if the XML document representing the zipfile
 * cannot be parsed successfully, or if the bytes cannot be decoded from
 * their base 64 representation.
 */
Updates::Updates(CComPtr<IXMLDOMDocument>& xmlParser,
                 const CString& xmlString) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xmlString);
    if (FAILED(xmlParser->loadXML(bstrXml, &success)))
        throw _T("Failure parsing server updates response");
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlParser->get_documentElement(&docElem)))
        throw _T("Failure extracting server updates response");
    CString docElemName = getNodeName((CComPtr<IXMLDOMNode>)docElem);
    if (docElemName == _T("ERROR")) {
        CString errorMessage =
            getTextContent((CComPtr<IXMLDOMNode>)docElem);
        AfxMessageBox(errorMessage);
        throw _T("Failure assembling update package");
    }
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("ZipFile")) {
            CString encoding = getAttribute(node, _T("encoding"));
            if (encoding != _T("base64"))
                throw _T("Unsupported encoding for zipfile: ") + encoding;
            CString zipFile = getTextContent(node);
            CStringA bytes = CStringA(zipFile);
            int nBytes = zipFile.GetLength();
            struct SafeBuf {
                SafeBuf(int n) { buf = new char[n]; }
                ~SafeBuf() { delete [] buf; }
                char* buf;
            };
            SafeBuf safeBuf(nBytes);
            BOOL success = Base64Decode((LPCSTR)bytes, zipFile.GetLength(),
                                        (BYTE*)safeBuf.buf, &nBytes);
            if (!success)
                throw _T("Failure decoding base64 bytes for zipfile");
            zipBytes = std::string((char*)safeBuf.buf, nBytes);
        }
        else if (nodeName == _T("Delete")) {
            CComPtr<IXMLDOMNode> child = getFirstChild(node);
            while (child) {
                CString nodeName = getNodeName(child);
                if (nodeName == _T("File"))
                    deletes.push_back(getTextContent(child));
                child = getNextSibling(child);
            }
        }
        node = getNextSibling(node);
    }
}

/*
 * Unpack the set of new and/or changed files, and then verify that the
 * files match the manifest.
 *
 * Mismatches can happen for a variety of reasons:
 *
 *   (1) Sometimes a new or changed file is added to the set on the
 *       server, and the account under which the client refresh server
 *       is running does not have sufficient permission to read the
 *       file when it tries to add it to the compressed archive.
 *       This condition should be addressed by enhancements to the
 *       software which builds the manifest on the server, to ensure
 *       at manifest build time that the client refresh server can
 *       read all of the files represented on the manifest.  Of
 *       course, this would not completely eliminate this class of
 *       problem, as it is possible for systems administrators to
 *       make changes to permission settings, or for bugs to surface
 *       in the operating system, changing the way permissions are
 *       granted or denied.  We might address this problem by having
 *       a periodic job run to confirm that permissions needed by
 *       the server are intact, with email alerts sent to appropriate
 *       persons whenever this assumption is violated.  It is possible
 *       that moving the client refresh servers from Windows to an
 *       operating system with a less Byzantine authentication /
 *       permission system would dramatically reduce or eliminate
 *       this class of problem.
 *
 *   (2) The copy of a file on the client machine can have settings
 *       which deny the current user permission to overwrite that
 *       file with a new version.  This can happen, for example,
 *       if an administrator logs onto the machine and runs the
 *       CDR client, resulting in files for which only the administrator
 *       has sufficient permissions for removal or replacement.
 *       Or the systems support staff can change the account with which
 *       the user logs onto the machine (e.g., different domain).
 *       There isn't much we can do about this problem, beyond
 *       educating users (or at least, lead users responsible for
 *       troubleshooting failures) about the need to check the
 *       the logs for error messages and ensure that the user has
 *       adequate permissions for changing all of the files
 *       represented in the manifest.
 *
 *   (3) A file can be added to (changed in, deleted from) the set
 *       of current client files without rebuilding the manifest.
 *       One solution might be to have a scheduled job run periodically
 *       to verify that the manifest is in sync with the set of current
 *       files, with email alerts when problems are detected.  A more
 *       elaborate approach would be to set up a mechanism for
 *       managing the client file set (adding new files, removing
 *       or replacing existing files) exclusively through an interface
 *       designed for this purpose.  This would eliminate the window
 *       for failures allowed by the first approach to dealing with
 *       this type of problem.  For example, a web interface might
 *       be used with the file upload feature of CGI for submitting
 *       new or changed files.  The web interface would also allow
 *       for removing files from the client set.  An additional
 *       benefit from this technique would be the ability to capture
 *       information about who installed the most recent version of
 *       a file (or deleted a file), and any reasons for the change.
 *       Another side benefit of the web interface would be easier
 *       upload of files from the user's workstation, which is currently
 *       made more difficult by the inability to map drives locally
 *       to the CDR Servers.
 *
 *       A command-line version of the interface might also be useful,
 *       to allow developers or lead users to install or delete files
 *       from a telnet or ssh connection, where a browser cannot be
 *       used for installing files from the remote server's filesystem.
 *
 *       An even more elaborate, but more reliable approach (and one
 *       providing richer functionality), would be to store the client
 *       file set in tables of a DBMS.
 *
 *   (4) Transmission errors.  Theoretically possible, but should be
 *       eliminated by the error-correction facilities provided by
 *       TCP/IP, over which the connections communicate.
 *
 *   (5) Bugs in the libraries for calculating checksums. So far we
 *       haven't yet encountered such bugs.
 *
 * In the past, bugs in how the operating system reported file time
 * stamps also caused bogus discrepancies. This class of problem has
 * been eliminated by switching to the use of checksums for detecting
 * file changes.
 *
 * The zipfile is saved in the current working directory under the
 * name CdrClientFiles.zip.  The output from the command to unpack
 * the files (listing the files which were unpacked) is stored in
 * the a file named unzip.out.  Any error messages from that operation
 * are stored in a file named unzip.err.
 */
void CdrClient::getNewFiles(const std::string& bytes, CdrProgressDlg& dialog) {

    // Save the zipfile to the current working directory.
    dialog.Advance();
    FILE* fp = fopen("CdrClientFiles.zip", "wb");
    if (!fp)
        throw _T("Failure opening CdrClientFiles.zip");
    size_t n = fwrite(bytes.c_str(), 1, bytes.size(), fp);
    if (n != bytes.size())
        throw _T("Failure writing CdrClientFiles.zip");
    if (fclose(fp))
        throw _T("Failure closing CdrClientFiles.zip");

    // Unpack the archive.
    dialog.Advance();
    log(_T("Unpacking updated files from the server.\n"), 1);
    int rc = system(".\\unzip -o CdrClientFiles.zip >unzip.out 2>unzip.err");
    if (rc == -1)
        throw _T("Failure unpacking new files from server");

    // Verify that the manifest and files match each other.
    dialog.Advance();
    CString mismatch;
    try {
        Manifest manifest(xmlDomParser);
        log(_T("Verifying the new manifest against our local files ...\n"), 1);
        mismatch = manifest.validate(this);
    }
    catch (...) {
        throw _T("Missing or corrupted server manifest");
    }
    dialog.Advance();
    if (!mismatch.IsEmpty())
        throw mismatch;

    // If a new version of this program was included, there will be a
    // copy of the script to launch the program again.  Make a note so
    // we'll know to invoke the script.
    if (PathFileExists(RELAUNCH_SCRIPT))
        this->loaderReplaced = true;
}

/*
 * Registers the custom DLL we wrote to provide CDR functionality
 * for users of XMetaL and invokes the latest Unicode version of
 * XMetaL.  Throws a string-based exception if the launch does not
 * succeed.
 */
void CdrClient::launchClient() {

    // If we're running a later version of XMetaL than the one
    // most users are running, swap in a DLL to match.
    if (xmver == XM17 && !_waccess(_T(".\\CDR\\cdr.xm17"), 0)) {
        log(_T("Swapping in DLL for XMetaL 17.0\n"));
        system(".\\regcdrdll --unregister Cdr\\Cdr.dll");
        BOOL success = CopyFileA("CDR\\Cdr.xm17", "CDR\\Cdr.dll", FALSE);
        if (!success)
            throw _T("Failure swapping DLL for XMetaL 17.0");
    }

    // Make it possible to switch back and forth.
    if (xmver == XM9 && !_waccess(_T(".\\CDR\\cdr.xm9"), 0)) {
        log(_T("Swapping in DLL for XMetaL 9.0\n"));
        system(".\\RegSvrEx /u CDR\\Cdr.dll");
        BOOL success = CopyFileA("CDR\\Cdr.xm9", "CDR\\Cdr.dll", FALSE);
        if (!success)
            throw _T("Failure swapping DLL for XMetaL 9.0");
    }

    // Fall back on a 32-bit registration tool if we're running XMetaL 9.0.
    char* cmd = ".\\regcdrdll Cdr\\Cdr.dll";
    if (xmver == XM9)
        cmd = ".\\RegSvrEx /c CDR\\Cdr.dll";
    CString msg;
    msg.Format(_T("Registering DLL: %S\n"), cmd);
    log(msg, 1);
    int rc = system(cmd);
    if (rc) {
        msg.Format(_T("Failure registering Cdr.dll: %S"), strerror(errno));
        throw msg;
    }
    CString programName = findXmetalProgram(this);
    if (programName.IsEmpty())
        throw _T("Unable to find XMetaL program");
    TCHAR* args[2] = { _T("XMetaL") };
    log(_T("Launching ") + programName + _T("\n"), 1);
    int err = (int)_texecve(programName.GetBuffer(), args, NULL);
    msg.Format(_T("Failure launching %s: %S"), programName, strerror(errno));
    throw msg;
}

/*
 * Returns the path to the XMetaL executable program to be
 * launched; or an empty string if no appropriate path is found.
 */
CString findXmetalProgram(CdrClient* client) {
    client->log(_T("Top of findXmetalProgram\n"), 3);
    TCHAR* xm17 = _T("\\XMetaL 17.0\\Author\\xmetal.exe");
    TCHAR* xm9 = _T("\\XMetaL 9.0\\Author\\xmetal90.exe");
    CString msg;
    switch (client->xmver) {
    case CdrClient::XM17:
        return tryXmetalPath(xm17, client);
    case CdrClient::XM9:
        return tryXmetalPath(xm9, client);
    default:
        msg.Format(_T("Unrecognized XMetaL version %d"), client->xmver);
        throw msg;
    }
}

/*
 * Tries to find the path to the XMetaL executable by appending the tail
 * for a proposed path to the Program Files directory at the root of
 * the system drive.  The Program Files directory is different on
 * machines running 64-bit Windows from those running 32-bit Windows,
 * so we have to try both.
 */
CString tryXmetalPath(TCHAR* t, CdrClient* client) {
    TCHAR* vars[] = {
        _T("ProgramFiles(x86)"),
        _T("ProgramFiles"),
        _T("ProgramW6432")
    };
    CString tail = t;
    for (size_t i = 0; i < sizeof vars / sizeof vars[0]; ++i) {
        TCHAR* dir = _tgetenv(vars[i]);
        if (dir) {
            CString path = dir + tail;
            client->log(_T("Testing presence of ") + path + _T("\n"), 3);
            if (!_waccess((LPCTSTR)path, 0))
                return path;
        }
    }
    return L"";
}

/*
 * Invokes the script to run this program a second time with the
 * --run-again command-line argument.  Throws a string-based exception
 * if the launch does not succeed.
 *
 * Here's how this works.  The set of client files always includes
 * a script named CdrRunAgain.cmd, which has a single line calling
 * this program with the --run-again argument.  Whenever this program
 * (CdrClient-versionstamp.exe) is updated, an executable with a new
 * name containing a timestamp representing the date and time this
 * version of the program was compiled (e.g., CdrClient20051103-1709.exe).
 * At the same time, the script CdrRunAgain.cmd is edited to invoke this
 * version of the program instead of the previous version.  Since the
 * client's manifest indicates that its version of the CdrRunAgain.cmd
 * script is older than the version now on the server, the server
 * sends this new version of the script to the client, along with
 * the new version of this program.  This program downloads the
 * new client files, notices that the script to run again is present
 * in the set, and invokes the script (using the function below
 * this comment).  The code to parse the command-line arguments
 * deletes the script when it sees the --run-again option in the
 * current invocation of the program, preventing an endless
 * re-launching.  Although the re-launch script file has been deleted,
 * the client's copy of the manifest still includes the listing
 * for the script file, so the server doesn't keep sending the
 * missing script over and over.  The code which verifies that the
 * client files are in sync with the manifest is smart enough to
 * know that it shouldn't bother checking this script file, because
 * if it did, the check would almost always fail needlessly.  A bit
 * complicated, but it all works just fine.
 *
 * The reason we need to use different names for the individual
 * versions of this program is that Windows is not capable of
 * allowing the binary file for a program to be replaced while
 * the program is still running.
 */
void CdrClient::runAgain() {

    // Don't do this if we're asked not to.
    if (commandLineOptions.skipReload)
        return;

    // Avoid infinite relaunching.
    if (commandLineOptions.runAgain) {
        log(_T("Trying to relaunch too many times; bailing out.\n"));
        return;
    }

    CString msg;
    msg.Format(_T("Launching %s\n"), RELAUNCH_SCRIPT);
    log(msg, 1);
    TCHAR* args[2] = { RELAUNCH_SCRIPT };
    (void)_texecve(RELAUNCH_SCRIPT, args, NULL);
    msg.Format(_T("Failure launching %s: %d"), RELAUNCH_SCRIPT,
               strerror(errno));
    throw msg;
}

/*
 * Returns a new CString object for the value of the specified
 * attribute of an element.  This is the first of a series of
 * convenient utility functions which encapsulate frequently
 * used XML DOM processing tasks.
 */
CString getAttribute(CComPtr<IXMLDOMNode>& elem, const TCHAR* name) {
    CComPtr<IXMLDOMNamedNodeMap> attrMap;
    elem->get_attributes(&attrMap);
    CComVariant value;
    CComPtr<IXMLDOMNode> attribute;
    CComBSTR bstrName(name);
    attrMap->getNamedItem(bstrName, &attribute);
    attribute->get_nodeValue(&value);
    return CString(value);
}

/*
 * Returns a pointer to the object for the next DOM node in the
 * chain; used for walking through the children of a DOM node
 * sequentially.
 */
CComPtr<IXMLDOMNode> getNextSibling(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> nextNode;
    node->get_nextSibling(&nextNode);
    return nextNode;
}

/*
 * Wrapper for the DOM node's get_firstChild method.
 */
CComPtr<IXMLDOMNode> getFirstChild(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child;
    node->get_firstChild(&child);
    return child;
}

/*
 * Returns the name of the current DOM node.
 */
CString getNodeName(CComPtr<IXMLDOMNode>& node) {
    CComBSTR name;
    if (SUCCEEDED(node->get_nodeName(&name)))
        return CString(name);
    throw _T("Failure getting XML node name");
}

/*
 * Extract the text content from a DOM element node and returns it
 * as a new CString object.
 */
CString getTextContent(CComPtr<IXMLDOMNode>& element) {
    CString textContent = _T("");
    CComPtr<IXMLDOMNode> child = getFirstChild(element);
    while (child) {
        DOMNodeType nodeType;
        child->get_nodeType(&nodeType);
        if (nodeType == NODE_TEXT || nodeType == NODE_CDATA_SECTION) {

            COleVariant childTextContent;
            if (SUCCEEDED(child->get_nodeValue(&childTextContent))) {
                textContent += CString(childTextContent.bstrVal);
            }
        }
        child = getNextSibling(child);
    }
    return textContent;
}

/*
 * Opens the log file and writes a heading for this session.  File is
 * opened in append mode, so entries from previous sessions are preserved.
 */
LogFile::LogFile() {
    try {
        time_t now = time(0);
        logFile.open("CdrClient.log", std::ios::app);
        logFile << "===================================================\n";
        logFile << cStringToUtf8(AfxGetAppName()) << " " << ctime(&now);
        logFile << "===================================================\n";
        logFile << std::flush;
    }
    catch (...) {
        AfxMessageBox(_T("Unable to open log file"));
    }
}

/*
 * Converts the caller's string to a UTF-8--encoded string and writes
 * it to the open log file.
 */
void LogFile::write(const CString& what) {
    SYSTEMTIME t;
    ::GetLocalTime(&t);
    char buf[80];
    sprintf(buf, "%02u:%02u:%02u.%03u ", t.wHour, t.wMinute, t.wSecond,
            t.wMilliseconds);
    std::string s = cStringToUtf8(what);
    logFile << buf << s << std::flush;
}

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 */
std::string LogFile::cStringToUtf8(const CString& str) {

    // Calculate storage requirement.
    size_t i, len = 0;
    size_t strLen = str.GetLength();
    LPCTSTR wchars = static_cast<LPCTSTR>(str);
    for (i = 0; i < strLen; ++i) {
        unsigned short ch = charToUnsignedShort(wchars[i]);
        if (ch < 0x80)
            ++len;
        else if (ch < 0x800)
            len += 2;
        else
            len += 3;
    }

    // Create string.
    std::string utf8(len, ' ');
    size_t j;

    // Populate string.
    for (i = j = 0; i < strLen; ++i)
    {
        unsigned short ch = charToUnsignedShort(*wchars++);
        if (ch < 0x80)
            utf8[j++] = (char)(unsigned char)ch;
        else if (ch < 0x800)
        {
            utf8[j++] = (char)(unsigned char)(0xC0 | ((ch & 0x07C0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
        else
        {
            utf8[j++] = (char)(unsigned char)(0xE0 | ((ch & 0xF000) >> 12));
            utf8[j++] = (char)(unsigned char)(0x80 | ((ch & 0x0FC0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
    }
    return utf8;
}

/*
 * Wrapper for the LogFile object's write() method.
 */
void CdrClient::log(const CString& what, int level) {
    if (level <= commandLineOptions.clientDebugLevel)
        logger->write(what);
}

/**
 * Ensure that we don't already have a running instance of XMetaL.
 *
 * See https://tracker.nci.nih.gov/browse/OCECDR-5006.
 */
void CdrClient::checkForRunningInstance() {

    // Suppress this check on the shared host used for testing XMetaL 17.0.
    TCHAR* computer_name_env = _tgetenv(_T("COMPUTERNAME"));
    if (computer_name_env) {
        CString computer_name = computer_name_env;
        computer_name.MakeLower();
        if (computer_name.Find(_T("ncits-d170-v")) >= 0) {
            return;
        }
    }

    // We're on a single-user machine, so do the check.
    CString program_name = findXmetalProgram(this);
    if (program_name.IsEmpty())
        throw _T("Unable to find XMetaL program");
    int position = program_name.ReverseFind(_T('\\'));
    if (position == -1)
        throw _T("Unable to find a full path for XMetaL");
    CString name = program_name.Right(program_name.GetLength() - ++position);
    if (find_process_id(name))
        throw _T("XMetaL is already running");
}

/*
 * See if a process is running.
 */
DWORD find_process_id(const CString process_name) {

    PROCESSENTRY32 process_info;
    process_info.dwSize = sizeof(process_info);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(snapshot, &process_info);
    if (process_name == process_info.szExeFile) {
        CloseHandle(snapshot);
        return process_info.th32ProcessID;
    }

    while (Process32Next(snapshot, &process_info)) {
        if (process_name == process_info.szExeFile) {
            CloseHandle(snapshot);
            return process_info.th32ProcessID;
        }
    }

    CloseHandle(snapshot);
    return 0;
}
