/*
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 * BZIssue::4767
 */

// Local headers.
#include "stdafx.h"
#include "CdrUtil.h"
#include "mp3.h"

// System headers.
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <afxinet.h>
#include <afxole.h>

// Use HTTPS instead of CDR custom port (2019).
#define TUNNELING

// How patient we should be for launching IE (in milliseconds).
#define MESSAGE_PENDING_DELAY 20000

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local support functions.
static CString errResponse(const CString& err);
static bool isUserPath(const CString& path);
static std::string log_timestamp();

/**
 * Login token obtained from the CDR server.
 */
CString CdrSocket::sessionString;

/**
 * DNS names for CDR server host.
 */
CString CdrSocket::cdrHost;
CString CdrSocket::apiHost;

/**
 * Name for CDR server host's CBIIT tier (e.g., PROD, DEV).
 */
CString CdrSocket::tier;

/**
 * Object to ensure proper cleanup at shutdown time.
 */
CdrSocket::Init CdrSocket::Init::init;

/*
 * Map of open document to validation errors (mapped by doc path).
 */
cdr::ValidationErrorSets cdr::validationErrorSets;

/**
 * Initialize the Winsock package and figure out which tier we're talking to.
 */
CdrSocket::Init::Init()
{
    if (WSAStartup(0x0101, &wsaData) != 0) {
        ::AfxMessageBox(L"Unable to initialize Windows socket library");
        throw L"Failure initializing Windows socket library";
    }
    const TCHAR* cdrHostEnv = _tgetenv(L"CDR_HOST");
    const TCHAR* apiHostEnv = _tgetenv(L"API_HOST");
    const TCHAR* sessionEnv = _tgetenv(L"CDRSession");
    const TCHAR* cdrTierEnv = _tgetenv(L"CDR_TIER");
    cdrHost = cdrHostEnv ? cdrHostEnv : L"cdr-dev.cancer.gov";
    // Do this below until the service-based API is gone from all tiers.
    // apiHost = apiHostEnv ? apiHostEnv : cdrHost;

    // Don't do this: it short-circuits needed initialization code.
    // sessionString = sessionEnv ? sessionEnv : L"";

    if (cdrTierEnv) {
        CString tier_buf;
        tier_buf.Format(L"env var CDR_TIER=%s", cdrTierEnv);
        cdr::trace_log(cdr::cStringToUtf8(tier_buf).c_str());
        tier = cdrTierEnv;
    }
    else {
        CString lowerHostName = cdrHost;
        tier = "UNKNOWN TIER";
        lowerHostName.MakeLower();
        if (lowerHostName == "cdr.cancer.gov")
            tier = "PROD";
        else if (lowerHostName == "cdr-dev.cancer.gov")
            tier = "DEV";
        else if (lowerHostName == "cdr-qa.cancer.gov")
            tier = "QA";
        else if (lowerHostName == "cdr-test.cancer.gov")
            tier = "STAGE";
        else if (lowerHostName == "cdr-stage.cancer.gov")
            tier = "STAGE";
        else if (lowerHostName == "cdr.test.cancer.gov")
            tier = "STAGE";
        else if (lowerHostName == "cdr.stage.cancer.gov")
            tier = "STAGE";
        else if (lowerHostName == "cdr.dev.cancer.gov")
            tier = "DEV";
    }
    if (apiHostEnv)
        apiHost = apiHostEnv;
    else {
        if (tier == "PROD")
            apiHost = L"cdrapi.cancer.gov";
        else {
            apiHost.Format(L"cdrapi-%s.cancer.gov", tier);
            apiHost.MakeLower();
        }
    }
    CString buf;
    buf.Format(L"cdrhost=%s apihost=%s", cdrHostEnv, apiHostEnv);
    cdr::trace_log(cdr::cStringToUtf8(buf).c_str());
}

/**
 * Performs cleanup of the Winsock package.
 */
CdrSocket::Init::~Init()
{
    WSACleanup();
}

/**
 * Sends an API command to the CDR server and reads the server's response.
 * The command is wrapped in a <code>CdrCommandSet</code> element prior to
 * submission.
 *
 *  @param  cmd             reference to string object containing the command.
 *  @param  guest           flag indicating that we don't need a real
 *                          session identifier
 *  @param  requestBuf      if not NULL, this parameter contains a byte
 *                          string buffer terminated by a zero byte,
 *                          with an additional 1KB to accomodate the
 *                          CdrCommandSet, SessionId, and CdrCommand
 *                          wrappers (a workaround for a Microsoft heap
 *                          bug, which is preventing the runtime from
 *                          asking the operating system for additional
 *                          memory (which we know is available) when
 *                          storing large blobs); caller is responsible
 *                          for freeing this buffer
 *  @return                 string object containing the server's response.
 *  @exception  const char* if a communications error is encountered.
 */
CString CdrSocket::sendCommand(const CString& cmd, bool guest,
                               char* requestBuf)
{
    try {

        CWaitCursor wc;

        // Wrap the command in a CdrCommandSet element.
        CString front = L"<CdrCommandSet>";
        if (!sessionString.IsEmpty())
            front += L"<SessionId>" + sessionString + L"</SessionId>";
        else if (guest)
            front += L"<SessionId>guest</SessionId>";
        front += L"<CdrCommand>";
        CString back = L"</CdrCommand></CdrCommandSet>";
        const char* commands;

        // Use caller's buffer if present.
        size_t requestLen = 0;
        std::string request; // may not need, but keep in scope when we do
        if (requestBuf) {
            std::string f = cdr::cStringToUtf8(front);
            std::string b = cdr::cStringToUtf8(back);
            size_t cmdLen = strlen(requestBuf);
            memmove(requestBuf + f.length(), requestBuf, cmdLen);
            memcpy(requestBuf, f.c_str(), f.length());
            strcpy(requestBuf + cmdLen + f.length(), b.c_str());
            requestLen = cmdLen + f.length() + b.length();
            commands = requestBuf;
        }
        else {
          CString requestString = front + cmd + back;
          request = cdr::cStringToUtf8(requestString);
          commands = request.c_str();
          requestLen = request.length();
        }

        // Open an HTTPS connection to the CDR API tunnelling wrapper.
        CInternetSession session;
        CString headers;
        CHttpConnection* conn = NULL;
        CHttpFile* file = NULL;
        CStringA::PCXSTR bytes = (CStringA::PCXSTR)commands;
        DWORD length = (DWORD)requestLen;
        BOOL success = FALSE;
        INTERNET_PORT port = 443;
        const TCHAR* verb = L"POST";
        const TCHAR* target = L"/";
        headers.Format(L"Content-type: text/xml\n");
        DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
        //::AfxMessageBox(L"sending command to " + apiHost);
        session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 180000);
        conn = session.GetHttpConnection(apiHost, port);
        file = conn->OpenRequest(verb, target, NULL, 1, NULL, NULL, flags);

        // Sometimes this fails the first time; don't give up too quickly.
        for (int i = 0; !success && i < 3; ++i) {
            DWORD secFlags;
            file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            secFlags |= SECURITY_IGNORE_ERROR_MASK;
            file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            success = file->SendRequest(headers, (void*)bytes, length);
        }
        if (!success)
            throw L"Failure submitting request to server";

        // Make sure the server thinks we succeeded.
        DWORD result;
        file->QueryInfoStatusCode(result);
        if (result != HTTP_STATUS_OK) {
            static wchar_t err[80];
            swprintf(err, 80, L"HTTP status code from server: %lu", result);
            throw err;
        }

        // Read the response in chunks.
        static char buf[1024 * 1024 * 16];
        UINT nread = file->Read(buf, sizeof buf);
        std::string temp;
        while (nread > 0) {
            temp.append(buf, (size_t)nread);
            nread = file->Read(buf, sizeof buf);
        }

        // Clean up communications and decode the response.
        conn->Close();
        file->Close();
        CString response = cdr::utf8ToCString(temp.c_str());
        return response;
    }
    catch (LPCTSTR error) { return errResponse(error); }
    catch (const CString& err) { return errResponse(err); }
    catch (CException *ee) {
        TCHAR message[1024];
        ee->GetErrorMessage(message, 1023);
        CString msg;
        msg.Format(L"failure sending command: %s", message);
        debug_log("Caught exception in sendCommand()\n");
        //ee->ReportError();
        debug_log("Reported exception in sendCommand()\n");
        ee->Delete();
        return errResponse(msg);
    }
    catch (...) { return errResponse(L"sendCommand: unexpected failure"); }
}

CString CdrSocket::sendCommands(const cdr::CommandSet& commands, char* blob) {
    try {

        CWaitCursor wc;

        // Serialize the command set.
        debug_log("top of sendCommands()");
        std::string xml = cdr::cStringToUtf8(commands.get_xml());

        // Plug in the blob if we have one.
        if (blob) {
            auto start = xml.find(BLOB_PLACEHOLDER);
            if (start == std::string::npos)
                throw L"missing blob placeholder";
            auto length = strlen(BLOB_PLACEHOLDER);
            xml.replace(start, length, blob);
        }

        // Open an HTTPS connection to the CDR API tunnelling wrapper.
        CInternetSession session;
        CString headers = L"Content-type: text/xml\n";
        CHttpFile* file = NULL;
        //CStringA::PCXSTR bytes = (CStringA::PCXSTR)xml.c_str();
        const char* bytes = xml.c_str();
        DWORD length = (DWORD)xml.length();
        BOOL success = FALSE;
        INTERNET_PORT port = 443;
        const wchar_t* verb = L"POST";
        const wchar_t* target = L"/";
        DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
        session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 180000);
        CHttpConnection* conn = session.GetHttpConnection(apiHost, port);
        debug_log("calling conn->OpenRequest()");
        file = conn->OpenRequest(verb, target, NULL, 1, NULL, NULL, flags);
        debug_log("back from conn->OpenRequest()");

        // Sometimes this fails the first time; don't give up too quickly.
        for (int i = 0; !success && i < 3; ++i) {
            DWORD secFlags;
            file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            secFlags |= SECURITY_IGNORE_ERROR_MASK;
            file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
            success = file->SendRequest(headers, (void*)bytes, length);
        }
        debug_log("past SendRequest() loop");
        if (!success)
            throw L"Failure submitting request to server";

        // Make sure the server thinks we succeeded.
        DWORD result;
        file->QueryInfoStatusCode(result);
        if (result != HTTP_STATUS_OK) {
            static wchar_t err[80];
            swprintf(err, 80, L"HTTP status code from server: %lu", result);
            throw err;
        }

        // Read the response in chunks.
        static char buf[1024 * 1024 * 16];
        UINT nread = file->Read(buf, sizeof buf);
        std::string temp;
        while (nread > 0) {
            temp.append(buf, (size_t)nread);
            nread = file->Read(buf, sizeof buf);
        }

        // Clean up communications and decode the response.
        conn->Close();
        file->Close();
        CString response = cdr::utf8ToCString(temp.c_str());
        return response;
    }
    catch (LPCTSTR error) { return errResponse(error); }
    catch (const CString& err) { return errResponse(err); }
    catch (CException *ee) {
        TCHAR message[1024];
        ee->GetErrorMessage(message, 1023);
        CString msg;
        msg.Format(L"failure sending command: %s", message);
        ee->Delete();
        return errResponse(msg);
    }
    catch (...) { return errResponse(L"sendCommand: unexpected failure"); }
}

/**
 * Extract the text content from the first occurrence of the specified
 * element.
 *
 *  @param  tag             reference to string object for the element's
 *                          name.
 *  @return                 string object containing the element's text
 *                          content, or an empty string if the element
 *                          is not found.
 */
CString TinyXmlParser::extract(const CString& tag) const
{
    // Create target strings used in searching for the element's tags.
    CString open = L"<" + tag + L">";
    CString close = L"</" + tag + L">";

    // Find the tags.
    int pos = xml.Find(open);
    if (pos == -1)
        return L"";
    pos += open.GetLength();
    int endPos = xml.Find(close, pos);

    // Make sure we found the element.
    if (endPos == -1 || endPos == pos)
        return L"";

    // Pull out the text content.
    return xml.Mid(pos, endPos - pos);
}

/**
 * Display each of a set of Err elements to the user.
 *
 *  @param  msg         reference to string object containing the
 *                      <code>Err</code> elements.
 *  @return             <code>true</code> if at least one error message
 *                      was displayed to the user.
 */
bool cdr::showErrors(const CString& msg)
{
    // Find the first Err element.
    int pos = msg.Find(L"<Err>");
    int n = 0;
    while (pos != -1) {

        // Extract the error message.
        pos += 5;
        int endPos = msg.Find(L"</Err>", pos);
        if (endPos == -1) {
            ::AfxMessageBox(L"Missing closing tag for Err element");
            break;
        }
        if (pos < endPos) {

            // Show the error message to the user.
            int rc = ::AfxMessageBox(msg.Mid(pos, endPos - pos), MB_OKCANCEL);
            ++n;

            // Let the user bail out to avoid seeing cascading error messages.
            if (rc == IDCANCEL)
                break;
        }

        // Find the next Err element.
        pos = msg.Find(L"<Err>", endPos);
    }

    // Tell the caller if we displayed any error messages.
    return n > 0;
}

/**
 * Show errors returned in the server's response.
 *
 *  @param response - parsed response from server
 *
 * Return:
 *   true if any errors were found and displayed.
 */
bool cdr::showErrors(cdr::DOM& response) {
    bool found = false;
    auto errors = response.find_all("//Errors/Err");
    for (auto& node : errors) {
        CString error = response.get_text(node);
        if (!error.IsEmpty()) {
            int rc = ::AfxMessageBox(error, MB_OKCANCEL);
            found = true;
            if (rc == IDCANCEL)
                break;
        }
    }
    return found;
}

bool cdr::showValidationErrors(cdr::ValidationErrors& errors)
{
    // Walk through the errors.
    const cdr::ValidationError* error = errors.getNextError();
    int n = 0;
    while (error) {
        CString msg = L"[" + error->eid + L"] " + error->message;
        int rc = ::AfxMessageBox(msg, MB_OKCANCEL);
        ++n;

        // Let the user bail out to avoid seeing cascading error messages.
        if (rc == IDCANCEL) {
            errors.currentError--;
            break;
        }
        error = errors.getNextError();
    }

    // Tell the caller if we displayed any error messages.
    return n > 0;
}

/**
 * Extracts document information from the XML containing the CDR
 * server's response.
 *
 *  @param  xml             reference to string object containing
 *                          server's response to a request for potential
 *                          link targets.
 *  @return                 list of SearchResult objects.
 */
void cdr::extractSearchResults(const CString& xml, DocSet& docSet)
{
    // Extract the first query result.
    docSet.clear();
    Element r = Element::extractElement(xml, L"QueryResult");

    // Loop through each QueryResult element.
    while (r) {
        Element id    = r.extractElement(r.getString(), L"DocId");
        Element type  = r.extractElement(r.getString(), L"DocType");
        Element title = r.extractElement(r.getString(), L"DocTitle");
        SearchResult qr = SearchResult(id.getString(),
                                       type.getString(),
                                       title.getString());
        docSet.push_back(qr);
        r = r.extractElement(xml, L"QueryResult", r.getEndPos());
    }
}

/**
 * Populates the caller's list box object with strings drawn from the query
 * result information passed in.
 *
 *  @param  listBox         reference to caller's list box, to which
 *                          we add strings identifying each document
 *                          in the server's response.
 *  @param  docSet          reference to list of SearchResult objects.
 *  @return                 number of strings added to list box, or -1
 *                          in the event of an error.
 */
int cdr::fillListBox(CListBox& listBox, const DocSet& docSet)
{
    // Start with a clean slate.
    listBox.ResetContent();
    int n        = 0;
    int maxWidth = 0;
    CDC*   dc    = 0;
    CFont* font  = listBox.GetFont();
    ASSERT(font);

    // Wrap this in a try block so we're sure to release the device context.
    try {

        dc = listBox.GetDC();

        // Loop through the elements of the document set.
        DocSet::const_iterator iter = docSet.begin();
        while (iter != docSet.end()) {

            // Build a string in the form "[doc-id] doc-title"
            CString id    = (*iter).getDocId();
            CString title = (*iter).getDocTitle();
            ++iter;
            ++n;

            // Append the new string to the list box object.
            CString str = L"[" + id + L"] " + cdr::decode(title);
            CSize size  = dc->GetTextExtent(str);
            if (maxWidth < size.cx)
                maxWidth = size.cx;
            listBox.AddString(str);
        }

        // Make sure horizontal scrolling works properly.
        listBox.SetHorizontalExtent(maxWidth + 6);
    }
    catch (...) {
        if (dc) {
            listBox.ReleaseDC(dc);
        }
    }

    // Tell the caller how many items we added to the list box.
    return n;
}

/**
 * Obtains an Automation dispatch object for the running XMetaL application.
 *
 *  @return             new object to be used for invoking application-
 *                      level XMetaL methods.
 */
_Application cdr::getApp()
{
    debug_log("Top of getApp()");
    _Application app;
    CWinApp* win_app = ::AfxGetApp();
    if (!win_app->m_pMessageFilter) {
        win_app->m_pMessageFilter = new COleMessageFilter();
        win_app->m_pMessageFilter->Register();
    }
    //win_app->m_pMessageFilter->EnableNotRespondingDialog(FALSE);
    win_app->m_pMessageFilter->SetMessagePendingDelay(MESSAGE_PENDING_DELAY);
    try {
        COleException e;
        debug_log("Before CreateDispatch()");
        if (app.CreateDispatch(L"XMetaL.Application", &e)) {
            debug_log("After CreateDispatch()");
            return app;
        }
        debug_log("After after CreateDispatch()");
        e.ReportError();
    }
    catch (CException *ee) {
        debug_log("Caught exception in cdr::getApp()\n");
        ee->ReportError();
        debug_log("Reported exception in cdr::getApp()\n");
        ee->Delete();
    }
    throw L"Unable to create XMetaL Application-level automation object";
}

/**
 * Finds the location where the currently running XMetaL application is
 * installed.
 *
 *  @return             reference to string containing path for base XMetaL
 *                      folder.
 */
CString cdr::getXmetalPath() {
    static CString xmetalPath;
    if (xmetalPath.IsEmpty()) {
        _Application app = getApp();
        if (app)
            xmetalPath = app.GetPath();
    }
    return xmetalPath;
}

/**
 * Finds the user-specific location where client files for the application
 * are stored.
 *
 *  @return             reference to string containing location for client
 *                      files.
 */
CString cdr::getUserPath() {
    static CString userPath;
    if (userPath.IsEmpty()) {
        CString tail = L"\\Softquad\\XMetaL\\";
        TCHAR* vars[] = { L"LOCALAPPDATA", L"APPDATA" };
        TCHAR* vers[] = { L"9.0", L"4.5" };
        for (size_t i = 0; i < sizeof vars / sizeof vars[0]; ++i) {
            TCHAR* dir = _tgetenv(vars[i]);
            if (dir) {
                for (size_t j = 0; j < sizeof vers / sizeof vers[0]; ++j) {
                    CString candidate = CString(dir) + tail + CString(vers[j]);
                    if (isUserPath(candidate)) {
                        userPath = candidate;
                        return userPath;
                    }
                }
            }
        }
        userPath = cdr::getXmetalPath();
    }
    return userPath;
}

/**
 * Test a candidate path to determine whether it can be used to store
 * client files for our application.
 *
 *  @param  path      fully qualified path string for candidate path
 */
bool isUserPath(const CString& path) {
    CString manifest = path + L"\\CdrManifest.xml";
    if (!_waccess((LPCTSTR)manifest, 0))
        return true;
    return false;
}

/**
 * Alters the caller's string in place, making it suitable to
 * serve as XML text content, replacing reserved characters with
 * their built-in entity reference equivalents.
 *
 *  @param  str         caller's string object to be modified in place.
 *  @param  fixQuotes   <code>true</code> iff single- and double-quote
 *                      marks should be replaced; otherwise <code>false</code>
 *                      (the default).
 *  @return             copy of modified string.
 */
CString cdr::encode(CString str, bool fixQuotes) {
    str.Replace(L"&", L"&amp;");
    str.Replace(L"<", L"&lt;");
    str.Replace(L">", L"&gt;");
    if (fixQuotes) {
        str.Replace(L"\"", L"&quot;");
        str.Replace(L"'", L"&apos;");
    }
    return str;
}

/**
 * Reverses the XML encoding process, replacing builtin entity
 * references with the corresponding characters.
 *
 *  @param  str         caller's string object to be modified in place.
 *  @return             copy of modified string.
 */
CString cdr::decode(CString str)
{
    str.Replace(L"&amp;", L"&");
    str.Replace(L"&lt;", L"<");
    str.Replace(L"&gt;", L">");
    str.Replace(L"&quot;", L"\"");
    str.Replace(L"&apos;", L"'");
    return str;
}

/**
 * Extracts document number from CDR ID string, which is generally
 * in the form "CDR\d\d\d\d\d\d\d\d\d\d".
 *
 *  @param  docString       reference to document ID string.
 *  @return                 integer representing document's primary key
 *                          in SQL Server.
 */
unsigned long cdr::getDocNo(const CString& docString) {
    int pos = docString.FindOneOf(L"0123456789");
    if (pos == -1)
        return 0L;
    LPCTSTR p = (LPCTSTR)docString;
    return _tcstoul(p + pos, 0, 10);
}

/**
 * Extracts and concatenates the text content for an element.
 *
 *  @param  node            DOM node object for element.
 *  @return                 string object containing concatenated text
 *                          content for element.
 */
CString cdr::extractElementText(DOMNode node) {
    CString s;
    node = node.GetFirstChild();
    while (node) {
        // Text nodes only.
        if (node.GetNodeType() == 3) {
            s += node.GetNodeValue();
        }
        node = node.GetNextSibling();
    }
    return s;
}

/**
 * Strips leading and trailing whitespace from the caller's string.
 *
 *  @param  s           reference to string to be trimmed.
 *  @return             new string object containing trimmed string.
 */
CString cdr::trim(const CString& s) {
    CString newStr = s;
    newStr.TrimRight();
    newStr.TrimLeft();
    return newStr;
}

/**
 * Pulls out the document's type, title, and ID from its XML representation.
 *
 *  @param  node            reference to DOM node object for document.
 *  @param  info            reference to control information object to be
 *                          populated.
 */
void cdr::extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info) {
    // Initialize flags to defaults.
    info.readyForReview = false;
    info.blocked        = false;

    // Get type from doc element name
    info.docType = node.GetNodeName();

    // Rest is in CdrDocCtl, a child of the doc element.
    node = node.GetFirstChild();
    while (node) {

        // Look for an element.
        if (node.GetNodeType() == 1) {

            // If CdrDocCtl, walk through its child nodes.
            if (node.GetNodeName() == L"CdrDocCtl") {

                // Check the ready-for-review flag.  This is where we
                // stick the document when we pass it off to XMetaL
                // (so we don't have to worry about formatting it in
                // the CSS).
                ::DOMElement cdrDocCtl = node;
                if (cdrDocCtl.getAttribute(L"readyForReview") == L"Y")
                    info.readyForReview = true;

                // MUST do this!  Otherwise XMetaL blows up with a complaint
                // about a pure virtual function!
                cdrDocCtl.m_bAutoRelease = 0;

                node = node.GetFirstChild();
                while (node) {

                    // Only interested in elements (type 1).
                    if (node.GetNodeType() == 1) {
                        CString name = node.GetNodeName();
                        if (name == L"DocTitle")
                            info.docTitle =
                                cdr::encode(extractElementText(node));
                        else if (name == L"DocId")
                            info.docId = cdr::trim(extractElementText(node));

                        // This is where we find this flag when we get the
                        // document from the CDR Server.
                        else if (name == L"ReadyForReview") {
                            if (extractElementText(node) == L"Y")
                                info.readyForReview = true;
                        }
                        else if (name == L"DocActiveStatus") {
                            if (extractElementText(node) == L"I")
                                info.blocked = true;
                        }
                    }
                    node = node.GetNextSibling();
                }

                // Once we've seen CdrDocCtl, we're done.
                break;
            }
        }
        node = node.GetNextSibling();
    }
}

/**
 * Packs up a string containing an error message inside the XML structure
 * appropriate for simulating a buffer returned by the CDR server, in the
 * event of a failure to communicate with the server.
 *
 *  @param  err             error message to be packed inside the buffer.
 *  @return                 string object representing response buffer.
 */
CString errResponse(const CString& err) {
    cdr::DOM dom("CdrResponseSet");
    auto root = dom.get_root();
    auto response = dom.child_element(root, "CdrResponse");
    dom.set(response, "Status", "failure");
    auto errors = dom.child_element(response, "Errors");
    dom.child_element(errors, "Err", err);
    return dom.get_xml();
}

/**
 * Writes the string equivalent of the XML tree represented by the caller's
 * DOM node. We do this ourselves instead of getting the xml property of
 * the document so we can cherry-pick, leaving out the bits we added for
 * XMetaL's benefit (like the CdrDocCtl block and the 'readonly' attributes).
 *
 *  @param  os              reference to output stream on which to write
 *                          the XML string.
 *  @param  node            reference to the DOM node to be written out.
 *  @return                 reference to output stream.
 */
std::basic_ostream<TCHAR>& operator<<(std::basic_ostream<TCHAR>& os,
                                      DOMNode& node) {
    // Obtain some local copies of the node's "attributes" (not in the XML
    // sense).
    int nodeType = node.GetNodeType();
    CString name = node.GetNodeName();

    // Swallow the CdrDocCtl element.
    if (nodeType == 1 && name != L"CdrDocCtl") {

        // Element node.  Output the start tag.
        os << L"<" << (LPCTSTR)name;
        DOMNamedNodeMap attrs = node.GetAttributes();
        int n = attrs.GetLength();
        for (int i = 0; i < n; ++i) {
            DOMNode attr = attrs.item(i);
            CString attrName = attr.GetNodeName();
            if (attrName != L"readonly") {
                CString val = attr.GetNodeValue();

                // OK, this is bizarre, but necessary because of a strange
                // pair of bugs in XMetaL.  XXX This runs the risk of
                // stepping on the intentions of the user, in the rare
                // (probably so rare that it will never happen) case in
                // which she really wants to end up with an EntityRef as
                // the _value_ (not just the representation) of the
                // attribute.  No way around this problem until Corel
                // fixes their bugs.  When that happens, take out the
                // call to cdr::decode() here and things will work the
                // way they should in _all_ cases.
                os << L" " << (LPCTSTR)attrName << L"='"
                   << (LPCTSTR)cdr::encode(cdr::decode(val), true) << L"'";
            }
        }
        if (!node.hasChildNodes())
            os << L"/";
        os << L">";
    }

    // If this is a text node (type 3) pump out the characters.
    else if (nodeType == 3) {

        CString val = node.GetNodeValue();
        os << (LPCTSTR)cdr::encode(val);
    }

    // Handle processing instructions.
    else if (nodeType == 7) {

        CString val = node.GetNodeValue();
        os << L"<?" << (LPCTSTR)name << L" " << (LPCTSTR)val << L"?>";
    }

    // Don't lose comments.
    else if (nodeType == 8) {

        CString val = node.GetNodeValue();
        os << L"<!--" << (LPCTSTR)val << L"-->";
    }

    // Process any children of the node.
    if (node.hasChildNodes() && name != "CdrDocCtl") {
        DOMNode n = node.GetFirstChild();
        os << n;

        // If this is an element node, write the closing tag.
        if (nodeType == 1)
            os << L"</" << (LPCTSTR)name << L">";
    }

    // Continue with this node's siblings
    DOMNode sibling = node.GetNextSibling();
    if (sibling)
        os << sibling;
    return os;
}

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 * If _UNICODE is not defined, we let the server catch any characters we're
 * given which are legal ANSI characters but not legal Unicode characters.
 */

#ifdef _UNICODE
inline unsigned short charToUnsignedShort(TCHAR c) {
    return static_cast<unsigned short>(c);
}
#else
inline unsigned short charToUnsignedShort(TCHAR c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return static_cast<unsigned short>(uc);
}
#endif

std::string cdr::cStringToUtf8(const CString& str) {
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
    for (i = j = 0; i < strLen; ++i) {
        unsigned short ch = charToUnsignedShort(*wchars++);
        if (ch < 0x80)
            utf8[j++] = (char)(unsigned char)ch;
        else if (ch < 0x800) {
            utf8[j++] = (char)(unsigned char)(0xC0 | ((ch & 0x07C0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
        else {
            utf8[j++] = (char)(unsigned char)(0xE0 | ((ch & 0xF000) >> 12));
            utf8[j++] = (char)(unsigned char)(0x80 | ((ch & 0x0FC0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
    }
    return utf8;
}

/**
 * Converts string from UTF-8 to UTF-16.  Ignores values beyond U+FFFF.
 */
CString cdr::utf8ToCString(const char* s) {
    // Calculate storage requirement.
    size_t i, len = 0;
    for (i = 0; s[i]; ++i) {
        if (((unsigned char)s[i] & 0x80) == 0)
            ++len;
        else if (((unsigned char)s[i] & 0x40) == 0x40)
            ++len;
    }

    // Make room.
    std::wstring newStr(len, ' ');

    // Populate string.
    for (i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)*s;
        if (ch < 0x80) {
            newStr[i] = (wchar_t)ch;
            ++s;
        }
        else if ((ch & 0xE0) == 0xC0) {
            newStr[i] = ((ch & 0x1F) << 6)
                      | (((unsigned char)s[1]) & 0x3F);
            s += 2;
        }
        else {
            newStr[i] = ((ch & 0x0F) << 12)
                      | ((((unsigned char)s[1]) & 0x3F) << 6)
                      | (((unsigned char)s[2]) & 0x3F);
            s += 3;
        }
    }
    return CString(newStr.c_str());
}

CString cdr::Element::getAttribute(const CString& name) const {
    Attrs::const_iterator i = attrs.find(name);
    if (i == attrs.end())
        return CString();
    else
        return i->second;
}

cdr::Element cdr::Element::extractElement(const CString& s,
                                          const CString& name,
                                          int pos) {
    // Start with an element that returns false.
    Element e;

    // Cache some frequently used values.
    int nameLen = name.GetLength();
    int strLen  = s.GetLength();

    // Look for start tag of element.
    int startPos = s.Find(L"<" + name, pos);
    while (startPos != -1) {
        if (startPos + nameLen + 1 >= strLen)
            return e;
        startPos += nameLen + 1;
        TCHAR ch = s[startPos];

        // Make sure we don't have another tag that starts the same way.
        if (_istspace(ch) || ch == (TCHAR)'>' || ch == (TCHAR)'/')
            break;

        // Try another position.
        startPos = s.Find(L"<" + name, startPos);
    }
    if (startPos == -1)
        return e;

    // Loop through the start tag extracting all attributes.
    while (startPos < strLen) {
        CString attrName;
        CString attrValue;
        int     attrNameStart;
        int     attrValueStart;
        TCHAR   delim;
        TCHAR   ch = s[startPos];

        // Check for an empty-element tag.
        if (ch == (TCHAR)'/') {
            startPos = s.Find(L">", startPos);
            if (startPos == -1)
                return e;
            e.startPos = e.endPos = startPos + 1;
            e.str = L"";
            return e;
        }

        // Check for end of tag; move past it if we find it.
        if (ch == (TCHAR)'>') {
            ++startPos;
            break;
        }

        // Skip past whitespace.
        if (_istspace(ch)) {
            startPos++;
            continue;
        }

        // Extract the attribute's name.
        attrNameStart = startPos++;
        while (startPos < strLen) {
            ch = s[startPos];
            if (ch == (TCHAR)'=' || _istspace(ch)) {
                attrName = s.Mid(attrNameStart, startPos++ - attrNameStart);
                if (e.attrs.find(attrName) != e.attrs.end())
                    throw (LPCTSTR)(L"Duplicate attribute " + attrName +
                                    L" in element " + name);
                break;
            }
            ++startPos;
        }

        // Find the character delimiting the attribute's string value.
        while (startPos < strLen) {
            ch = s[startPos++];
            if (ch == (TCHAR)'\'' || ch == (TCHAR)'\"') {
                delim = ch;
                attrValueStart = startPos;
                break;
            }
        }

        // Find the matching end delimiter and extract the value.
        while (startPos < strLen) {
            if (s[startPos] == delim) {
                attrValue = s.Mid(attrValueStart, startPos++ - attrValueStart);
                e.attrs[attrName] = attrValue;
                break;
            }
            ++startPos;
        }
    }

    // We now have all the attributes and startPos points just past closing >.
    // XXX Note that this approach fails with nested elements of the same
    // name.  Should not pose a problem for the uses the client DLL makes of
    // this method, but watch out for future uses.  At that point we may need
    // to link in a real XML parser.
    int endPos = s.Find(L"</" + name + L">", startPos);
    if (endPos == -1)
        return e;
    e.str = s.Mid(startPos, endPos - startPos);
    e.startPos = startPos;
    e.endPos = endPos;
    return e;
}

CString cdr::Element::getCdataSection() const {
    static CString target = L"<![CDATA[";
    int pos = str.Find(target);
    if (pos == -1)
        return CString();
    pos += target.GetLength();
    int end = str.Find(L"]]>", pos);
    if (end == -1)
        return CString();
    return str.Mid(pos, end - pos);
}

CdrLinkInfo cdr::extractLinkInfo(const CString& str) {
    CdrLinkInfo info;

    // Parse out the document ID and text content.
    int pos = str.Find(L"[");
    if (pos == -1) {
        ::AfxMessageBox(L"Unable to find link target start delimiter.");
        return info;
    }
    int endPos = str.Find(L"]", ++pos);
    if (endPos == -1) {
        ::AfxMessageBox(L"Unable to find link target end delimiter.");
        return info;
    }
    info.target = str.Mid(pos, endPos - pos);
    pos = endPos + 1;
    while (pos < str.GetLength() && str[pos] == L' ')
        ++pos;
    info.data = str.Mid(pos);
    return info;
}

::Range cdr::getElemRange(const CString& elemName) {
    // Find out where we are.
    ::_Document activeDoc = getApp().GetActiveDocument();
    ::Range rng = activeDoc.GetRange();

    // Make sure what we find is an ancestor of the current element.
    if (!rng.GetIsParentElement(elemName))
        return ::Range();

    // Move.
    if (!rng.MoveToElement(elemName, FALSE))
        return ::Range();

    return rng;
}

::Range cdr::findOrCreateChild(::Range parent, const CString& elemName) {
    // Try to find an existing occurrence first.
    parent.SelectContainerContents();
    ::Range child = parent.GetDuplicate();
    child.Collapse(1);
    if (child.MoveToElement(elemName, TRUE)) {
        if (parent.GetContains(child, FALSE))
            return child;
    }

    // Didn't find one; try to create a new one.
    parent.Collapse(1);
    if (parent.FindInsertLocation(elemName, TRUE)) {
        parent.InsertElement(elemName);
        return parent;
    }

    // Bust.  Can't find *or* create the element!
    return ::Range();
}

CString cdr::docIdString(int id) {
    TCHAR buf[40];
    swprintf(buf, L"CDR%010d", id);
    return buf;
}

CString cdr::suppressLeadingZeros(const CString& s) {
    int i = 0;
    while (i < s.GetLength()) {
        if (_istdigit(s.GetAt(i))) {
            if (s.GetAt(i) != '0')
                return s;
            break;
        }
        ++i;
    }
    int keepOnLeft = i++;
    while (i < s.GetLength()) {
        if (s.GetAt(i) != '0')
            break;
        ++i;
    }
    int keepOnRight = s.GetLength() - i;
    return s.Left(keepOnLeft) + s.Right(keepOnRight);
}

CString cdr::expandLeadingZeros(const CString& s) {
    CString zeros = L"0000000000";
    int i = 0;
    int firstDigit = 0;
    int numDigits = 0;
    while (i < s.GetLength()) {
        if (_istdigit(s.GetAt(i))) {
            firstDigit = i++;
            numDigits = 1;
            break;
        }
        ++i;
    }
    while (i < s.GetLength()) {
        if (!_istdigit(s.GetAt(i)))
            break;
        ++i;
        ++numDigits;
    }
    if (numDigits >= 10 || numDigits < 1)
        return s;
    int zerosNeeded = 10 - numDigits;
    return s.Left(firstDigit) + zeros.Left(zerosNeeded) + s.Mid(firstDigit);
}

// Implement our own command to show an HTML page
// (SoftQuad's version has bugs).
// This version uses ActiveX Automation instead of DDE,
// to get around a bug in Internet Explorer's DDE code.
#if 0
int cdr::showPage(const CString& url) {
    COleDispatchDriver ie;
    COleException* pe = new COleException;
    try {
        if (!ie.CreateDispatch(L"InternetExplorer.Application", pe)) {
            DWORD error = ::GetLastError();
            TCHAR buf[256];
            swprintf(buf,
               L"CreateDisplatch: Unable to launch Internet Explorer (%ld)",
               error);
            ::AfxMessageBox(buf, MB_ICONEXCLAMATION);
            throw pe;
        }
    }
    catch (COleDispatchException* pExc) {
        CString s;
        if (!pExc->m_strSource.IsEmpty())
            s = pExc->m_strSource + L" - ";
        if (!pExc->m_strDescription.IsEmpty())
            s += pExc->m_strDescription;
        else
            s += L"unknown error";
        ::AfxMessageBox(s, MB_OK, pExc->m_strHelpFile.IsEmpty() ? 0
                        : pExc->m_dwHelpContext);
        pExc->Delete();
        return EXIT_FAILURE;
    }
    catch (CException* e) {
        TCHAR b[256];
        swprintf(b, L"%S(%d): OLE Exception caught: SCODE = %x",
                 __FILE__, __LINE__, COleException::Process(e));
        ::AfxMessageBox(b, MB_OK);
        e->Delete();
        return EXIT_FAILURE;
    }
    pe->Delete();
    DISPID dispid;
    OLECHAR* member = L"Navigate";
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL,
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(L"GetIDsOfNames: Unable to launch Internet Explorer",
            MB_ICONEXCLAMATION);
        return EXIT_FAILURE;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
        url, 0L, L"CdrViewWindow", &dummy, &dummy);
    return EXIT_SUCCESS;
}
#endif
int cdr::showPage(const CString& url) {
    CString ie = L"\"%ProgramFiles%\\Internet Explorer\\iexplore.exe\"";
    CString command = L"\"" + ie + L" \"" + url + L"\"\"";
    _tsystem(command);
    return EXIT_SUCCESS;
}
// For debugging.
void logWrite(const CString& what) {
    return;
    FILE* logFile = fopen("c:/tmp/Phrase.log", "a");
    static bool warned = false;
    if (!logFile) {
        if (!warned) {
            warned = true;
            ::AfxMessageBox(L"Can't open log file");
        }
        return;
    }
    fprintf(logFile, "%s\n", cdr::cStringToUtf8(what).c_str());
    fclose(logFile);
}

cdr::GlossaryTree::GlossaryTree(const CString& command) {
    CString response = CdrSocket::sendCommand(command, true);
    // logWrite(response);
    cdr::Element termElem = cdr::Element::extractElement(response, L"Term");
    while (termElem) {
        LPCTSTR p = (LPCTSTR)termElem.getAttribute(L"id");
        int docId = _tcstoul(p, 0, 10);
        CString termString = termElem.getString();
        cdr::Element nameElem = cdr::Element::extractElement(termString,
                                                             L"Name");
        CString name = cdr::decode(nameElem.getString());
        cdr::Element phraseElem = cdr::Element::extractElement(termString,
                                                               L"Phrase");
        names[docId] = name;
        while (phraseElem) {
            int numWords = 0;
            int start = 0;
            GlossaryNodeMap* currentMap = &nodeMap;
            GlossaryNode*    currentNode = 0;
            CString phrase = cdr::decode(phraseElem.getString());
            while (start < phrase.GetLength()) {
                int end = phrase.Find(L" ", start);
                CString word;
                if (end == -1)
                    word = phrase.Mid(start);
                else
                    word = phrase.Mid(start, end - start);
                if (!word.IsEmpty()) {
                    // CString msg;
                    // msg.Format(L"tree word '%s'", word);
                    // logWrite(msg);
                    ++numWords;
                    GlossaryNodeMap::iterator iter = currentMap->find(word);
                    if (iter == currentMap->end())
                        currentNode = (*currentMap)[word] = new GlossaryNode;
                    else
                        currentNode = iter->second;
                    currentMap = &currentNode->nodeMap;
                }
                if (end == -1)
                    break;
                start = ++end;
            }
            phraseElem = cdr::Element::extractElement(termString, L"Phrase",
                                                      phraseElem.getEndPos());
            if (currentNode)
                currentNode->docId = docId;
            if (numWords) {
                if (numWords > (int)counts.size()) {
                    counts.resize(numWords);
                    counts[numWords - 1] = 0;
                }
                ++counts[numWords - 1];
            }
        }
        termElem = cdr::Element::extractElement(response, L"Term",
                                                termElem.getEndPos());
    }
}

cdr::GlossaryTree::~GlossaryTree() {
    GlossaryNodeMap::iterator i = nodeMap.begin();
    while (i != nodeMap.end()) {
        delete i->second;
        ++i;
    }
}

// Obsolete constructor for set of validation error messages.
cdr::ValidationErrors::ValidationErrors(const Element& e) {
    currentError = 0;
    Element err = Element::extractElement(e.getString(), L"Err", 0);
    while (err) {
        CString message = err.getString();
        CString eid = err.getAttribute(L"eref");
        CString etype = err.getAttribute(L"etype");
        CString elevel = err.getAttribute(L"elevel");
        if (etype == L"validation" || etype == L"link")
            errors.push_back(cdr::ValidationError(message, eid, elevel));
        else
            ::AfxMessageBox(message + L" (" + elevel + L")");
        err = Element::extractElement(e.getString(), L"Err",
                                      err.getEndPos());
    }
}

cdr::ValidationErrors::ValidationErrors(cdr::DOM& dom) {
    currentError = 0;
    auto nodes = dom.find_all("//Errors/Err");
    for (auto& node : nodes) {
        CString message = dom.get_text(node);
        CString eid = dom.get(node, "eref");
        CString etype = dom.get(node, "etype");
        CString elevel = dom.get(node, "elevel");
        if (etype == "validation" || etype == "link")
            errors.push_back(ValidationError(message, eid, elevel));
        else
            ::AfxMessageBox(message + " (" + elevel + ")");
    }
}

// static cdr::GlossaryTree* glossaryTree;
cdr::GlossaryTree* cdr::getGlossaryTree(const CString& language,
                                        const CString& dictionary) {

    // Cache the trees.
    // Make sure the memory gets cleaned up so BoundsChecker is happy.
    struct TreeCache {
        typedef std::map<CString, cdr::GlossaryTree*> Trees;
        ~TreeCache() {
            CString buf;
            for (auto i = trees.begin(); i != trees.end(); ++i) {
                buf.Format(L"deleting %s glossary tree", i->first);
                cdr::trace_log(cdr::cStringToUtf8(buf).c_str());
                delete i->second;
            }
        }
        Trees trees;
    };
    static TreeCache cache;

    // Fetch the tree if we don't already have it.
    // No need for locking; we'll be called in a single thread.
    CString key(language);
    if (!dictionary.IsEmpty())
        key += L"-" + dictionary;
    if (cache.trees.count(key) == 0) {
        CString spanish = language == L"es" ? L"Spanish" : L"";
        CString command;
        if (dictionary.IsEmpty())
            command.Format(L"<CdrGet%sGlossaryMap/>", spanish);
        else
            command.Format(L"<CdrGet%sGlossaryMap>"
                           L"<Dictionary>%s</Dictionary>"
                           L"</CdrGet%sGlossaryMap>",
                           spanish, dictionary, spanish);
        cache.trees[key] = new cdr::GlossaryTree(command);
        CString buf;
        buf.Format(L"fetched %s glossary tree", key);
        cdr::trace_log(cdr::cStringToUtf8(buf).c_str());
    }
    return cache.trees[key];
}

static inline unsigned short getNetworkShort(const unsigned char* buf) {
    return (((unsigned short)buf[0]) << 8) + (unsigned short)buf[1];
}

static inline unsigned short getLittleEndianShort(const unsigned char* buf) {
    return (((unsigned short)buf[1]) << 8) + (unsigned short)buf[0];
}

static inline unsigned long getNetworkLong(const unsigned char* buf) {
    return (((unsigned long)buf[0]) << 24) +
           (((unsigned long)buf[1]) << 16) +
           (((unsigned long)buf[2]) <<  8) +
             (unsigned long)buf[3];
}

// Fills in dim structure with height and width of image if possible.
// We only support the image types stored in the CDR.
bool cdr::getImageDimensions(CFile& file, ImageDimensions& dim) {

    // Get the first byte, which will give us a clue about which type we have.
    unsigned char buf[256];
    if (file.Read(buf, 1) != 1)
        return false;

    // Try GIF.
    if (buf[0] == 'G') {
        if (file.Read(buf + 1, 9) == 9 && buf[1] == 'I' && buf[2] == 'F') {
            dim.width  = (unsigned long)getLittleEndianShort(buf + 6);
            dim.height = (unsigned long)getLittleEndianShort(buf + 8);
            return true;
        }
    }

    // Try PNG
    else if (buf[0] == 0x89) {
        if (file.Read(buf, 23) == 23) {
            if (!memcmp(buf, "PNG\r\n\x1a\n", 7)) {
                if (!memcmp(buf + 11, "IHDR", 4)) {
                    dim.width  = getNetworkLong(buf + 15);
                    dim.height = getNetworkLong(buf + 19);
                    return true;
                }
            }
        }
    }

    // Try JPEG
    else if (buf[0] == 0xFF) {
        int skip = 0;
        if (file.Read(buf, 1) != 1 || buf[0] != 0xD8) // SOI marker
            return false;

        // Read until we find the SOF (Start Of Frame) markers
        while (file.Read(buf, 1) == 1) {

            // Skip past 0xFF bytes
            while (buf[0] == 0xFF)
                if (file.Read(buf, 1) != 1)
                    return false;
            switch (buf[0]) {
            case 0xC0: case 0xC1: case 0xC2: case 0xC3:
            case 0xC5: case 0xC6: case 0xC7: case 0xC9:
            case 0xCA: case 0xCB: case 0xCD: case 0xCE:
            case 0xCF: // SOF (Start Of Frame) markers
                if (file.Read(buf, 7) != 7)
                    return false;
                dim.height = (unsigned long)getNetworkShort(buf + 3);
                dim.width  = (unsigned long)getNetworkShort(buf + 5);
                return true;
            case 0xDA: // SOS (Start of Scan) marker
            case 0xD9: // EOI (End of Image) marker
                return false;
            default:
                if (file.Read(buf, 2) != 2)
                    return false;
                skip = (int)getNetworkShort(buf) - 2;
                if (skip < 0)
                    return false;
                file.Seek((LONGLONG)skip, CFile::current);
                break;
            }
        }
    }

    // Give up.
    return false;
}

// Parses mp3 file to determine the duration in seconds.
// Returns the number of seconds if successful, otherwise -1.
int cdr::getAudioSeconds(CFile& file) {
    MP3INFO mp3;
    if (getMp3Info(&mp3, file))
        return mp3.seconds;
    return -1;
}

// Assumes text-only content; no mixed-content markup allowed!
bool cdr::replaceElementContent(::DOMElement& elem, const CString& value) {

    // Clear out all the child nodes.
    ::DOMNode child = elem.GetFirstChild();
    while (child) {
        ::DOMNode nextChild = child.GetNextSibling();
        ::DOMNode dummy = elem.removeChild(child);
        child = nextChild;
    }

    // Pop in a new text node.
    ::_Document curDoc = cdr::getApp().GetActiveDocument();
    ::DOMNode textNode = curDoc.createTextNode(value);
    ::DOMNode dummy = elem.appendChild(textNode);
    return true;
}

CString cdr::fetchFromUrl(const CString& url) {
    CInternetSession session(L"CDR");
    DWORD flags = INTERNET_FLAG_TRANSFER_BINARY;
    if (url.Left(5) == L"https")
        flags |= INTERNET_FLAG_SECURE;
    CStdioFile* file = session.OpenURL(url, 1, flags);
    std::string response;
    for (;;) {
        char buf[1024];
        UINT read = file->Read((void*)buf, sizeof(buf));
        if (read > 0)
            response.append(buf, read);
        else
            break;
    }
    return cdr::utf8ToCString(response.c_str());
}

const char* cdr::get_cdr_trace_log_path() {
    static char* path = 0;
    if (!path) {
        try {
            char* name = "cdr-dll-trace.log";
            CString userPath = cdr::getUserPath();
            size_t extra = 2; // 1 for path separator + 1 for null byte
            size_t len = userPath.GetLength() + strlen(name) + extra;
            const std::string p = cdr::cStringToUtf8(userPath);
            path = new char[len];
            if (!path)
                return 0;
            sprintf(path, "%s\\%s", p.c_str(), name);
        }
        catch (...) {}
    }
    return path;
}

std::string log_timestamp() {
    char buf[80];
    SYSTEMTIME sys_time;
    ::GetLocalTime(&sys_time);
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            sys_time.wYear,
            sys_time.wMonth,
            sys_time.wDay,
            sys_time.wHour,
            sys_time.wMinute,
            sys_time.wSecond,
            sys_time.wMilliseconds);
    std::string timestamp(buf);
    return timestamp;
}

void debug_log(const CString& what, const CString& who) {
    if (who != L"bkline")
        return;
    try {
        FILE* logFile = fopen("c:/tmp/debug.log", "a");
        static bool warned = true; // false;
        if (!logFile) {
            if (!warned) {
                warned = true;
                ::AfxMessageBox(L"Can't open log file");
            }
            return;
        }
        fprintf(logFile, "%s %s\n", log_timestamp().c_str(),
                cdr::cStringToUtf8(what).c_str());
        fclose(logFile);
    }
    catch (...) {}
}

void cdr::trace_log(const char* what) {
    static bool startup = true;
    if (startup) {
        cdr::send_trace_log();
        startup = false;
    }
    try {
        const char* path = get_cdr_trace_log_path();
        if (!path)
            return;
        FILE* fp = fopen(path, "ab");
        fprintf(fp, "%s %s", log_timestamp().c_str(), what);
        if (strcmp(what, "logon") == 0) {
            const char* session = getenv("CDRSession");
            const char* user = getenv("CDRUser");
            fprintf(fp, "(%s, %s)",
                    user ? user : "unknown",
                    session ? session : "unknown");
        }
        fprintf(fp, "\n");
        fclose(fp);
        if (strcmp(what, "logoff") == 0)
            cdr::send_trace_log();
    }
    catch (...) {}
}
void cdr::send_trace_log() {
    try {
        const char* path = get_cdr_trace_log_path();
        if (!path)
            return;
        FILE* fp = fopen(path, "rb");
        if (!fp) {
            return;
        }
        static char buf[1024 * 1024];
        size_t nread = fread(buf, 1, sizeof buf, fp);
        std::string temp;
        while (nread > 0) {
            temp.append(buf, (size_t)nread);
            nread = fread(buf, 1, sizeof buf, fp);
        }
        fclose(fp);
        CString log_data = cdr::utf8ToCString(temp.c_str());
        if (log_data.IsEmpty()) {
            return;
        }
        CString command = L"<CdrSaveClientTraceLog><LogData>";
        command += cdr::encode(log_data);
        command += L"</LogData></CdrSaveClientTraceLog>";
        CString response = CdrSocket::sendCommand(command, true);
        if (response.Find(L"success") >= 0)
            _unlink(path);
    }
    catch (...) {}
}


#if 0
// Get started with what we need to build an XML document.
cdr::DOMBuilder::DOMBuilder(const CString& name)
    : doc(NULL), root(NULL) {

    HRESULT hr = CoCreateInstance(
        __uuidof(DOMDocument),
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&doc)
        );
    if (FAILED(hr))
        throw L"CoCreateInstance() failed for DOCDocument";
    doc->put_async(VARIANT_FALSE);
    doc->put_validateOnParse(VARIANT_FALSE);
    doc->put_resolveExternals(VARIANT_FALSE);
    doc->put_preserveWhiteSpace(VARIANT_TRUE);
    if (!name.IsEmpty())
        root = child_element(doc, name);
}

// Clean up resources we manage.
cdr::DOMBuilder::~DOMBuilder() {
    if (doc) {
        doc->Release();
        doc = NULL;
    }
    for (auto& p : nodes) {
        if (p) {
            p->Release();
            p = NULL;
        }
    }
}

// Create a new element with optional text content.
IXMLDOMElement* cdr::DOMBuilder::element(const CString& name,
                                         const CString& text) {
    IXMLDOMElement* e = NULL;
    BSTR bstr = SysAllocString(name);
    if (!bstr)
        throw L"memory for element name exhausted";
    HRESULT hr = doc->createElement(bstr, &e);
    if (FAILED(hr)) {
        SysFreeString(bstr);
        throw L"createElement() failed";
    }
    if (!text.IsEmpty()) {
        try {
            append_text(e, text);
        }
        catch (...) {
            SysFreeString(bstr);
            throw;
        }
    }
    SysFreeString(bstr);
    nodes.push_back(e);
    return e;
}

// Assign a value to one of an element's attributes.
void cdr::DOMBuilder::set(IXMLDOMElement* elem, const CString& name,
                          const CString& value) {
    BSTR bstr = SysAllocString(name);
    if (!bstr)
        throw L"memory for attribute name exhausted";
    IXMLDOMAttribute* attr = NULL;
    HRESULT hr = doc->createAttribute(bstr, &attr);
    SysFreeString(bstr);
    if (FAILED(hr)) {
        if (attr)
            attr->Release();
        throw L"createAttribute() failed";
    }
    bstr = SysAllocString(value);
    if (!bstr) {
        attr->Release();
        throw L"memory for attribute value exhausted";
    }
    VARIANT variant;
    VariantInit(&variant);
    V_VT(&variant) = VT_BSTR;
    V_BSTR(&variant) = bstr;
    hr = attr->put_value(variant);
    VariantClear(&variant);
    SysFreeString(bstr);
    if (FAILED(hr)) {
        attr->Release();
        throw L"put_value() failed for attribute";
    }
    IXMLDOMAttribute* out = NULL;
    hr = elem->setAttributeNode(attr, &out);
    attr->Release();
    if (out)
        out->Release();
    if (FAILED(hr))
        throw L"setAttributeNode() failed";
}

// Attach an element to its existing parent.
void cdr::DOMBuilder::append(IXMLDOMNode* parent, IXMLDOMNode* child) {
    IXMLDOMNode* out = NULL;
    HRESULT hr = parent->appendChild(child, &out);
    if (out)
        out->Release();
    if (FAILED(hr))
        throw L"appendChild() failed";
}

// Create a new element and attach it to an existing parent.
IXMLDOMElement* cdr::DOMBuilder::child_element(IXMLDOMNode* parent,
                                               const CString& name,
                                               const CString& text) {
    IXMLDOMElement* e = element(name, text);
    append(parent, e);
    return e;
}

// Add a new text node to an existing element.
void cdr::DOMBuilder::append_text(IXMLDOMNode* parent, const CString& text) {
    BSTR bstr = SysAllocString(text);
    if (!bstr)
        throw L"memory for text exhausted";
    IXMLDOMText* text_node = NULL;
    HRESULT hr = doc->createTextNode(bstr, &text_node);
    if (FAILED(hr)) {
        SysFreeString(bstr);
        if (text_node)
            text_node->Release();
        throw L"createTextNode() failed";
    }
    try {
        append(parent, text_node);
    }
    catch (...) {
        SysFreeString(bstr);
        text_node->Release();
        throw;
    }
    SysFreeString(bstr);
    text_node->Release();
}

// Serialize the document to a string.
CString cdr::DOMBuilder::get_xml() const {
    BSTR bstr = NULL;
    HRESULT hr = doc->get_xml(&bstr);
    if (FAILED(hr)) {
        if (bstr)
            SysFreeString(bstr);
        throw L"get_xml() failed";
    }
    CString xml(bstr);
    SysFreeString(bstr);
    return xml;
}


// Get the DOM tree for an XML document.
cdr::ParsedDOM::ParsedDOM(const CString& xml) : doc(NULL), root(NULL) {
    HRESULT hr = CoCreateInstance(
        __uuidof(DOMDocument),
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&doc)
        );
    if (FAILED(hr))
        throw L"CoCreateInstance() failed for DOCDocument";
    doc->put_async(VARIANT_FALSE);
    doc->put_validateOnParse(VARIANT_FALSE);
    doc->put_resolveExternals(VARIANT_FALSE);
    doc->put_preserveWhiteSpace(VARIANT_TRUE);
    VARIANT_BOOL succeeded = VARIANT_FALSE;
    BSTR bstr = SysAllocString(xml);
    if (!bstr)
        throw L"memory for XML string exhausted";
    hr = doc->loadXML(bstr, &succeeded);
    SysFreeString(bstr);
    if (FAILED(hr))
        throw L"loadXml() failed";
    if (succeeded == VARIANT_FALSE) {
        IXMLDOMParseError* parse_error = NULL;
        hr = doc->get_parseError(&parse_error);
        if (FAILED(hr))
            throw L"XML parse failed but can't get parse error";
        BSTR reason = NULL;
        hr = parse_error->get_reason(&reason);
        if (FAILED(hr))
            throw L"XML parse failed but can't get failure reason";
        CString why(reason);
        throw why;
    }
}

// Clean up the resources we manage.
cdr::ParsedDOM::~ParsedDOM() {
    if (doc) {
        doc->Release();
        doc = NULL;
    }
    for (auto& p : nodes) {
        if (p) {
            p->Release();
            p = NULL;
        }
    }
}

// Find the first element matching an XPath query.
IXMLDOMElement* cdr::ParsedDOM::find(const CString& xpath,
                                     IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    IXMLDOMElement* root = get_root();
    BSTR bstr = SysAllocString(xpath);
    if (!bstr)
        throw L"memory exhausted for xpath";
    IXMLDOMNode* node = NULL;
    HRESULT hr = top->selectSingleNode(bstr, &node);
    SysFreeString(bstr);
    if (FAILED(hr))
        throw L"selectSingleNode() failed";
    if (!node)
        return NULL;
    IXMLDOMElement* element;
    hr = node->QueryInterface(__uuidof(IXMLDOMElement),
                              (void**)&element);
    node->Release();
    if (FAILED(hr))
        throw L"QueryInterface failed for IXMLDOMElement";
    nodes.push_back(element);
    return element;
}

// Find all the elements matching an XPath query.
std::vector<IXMLDOMElement*> cdr::ParsedDOM::find_all(const CString& xpath,
                                                      IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    BSTR bstr = SysAllocString(xpath);
    if (!bstr)
        throw L"memory exhausted for xpath";
    IXMLDOMNodeList* list = NULL;
    HRESULT hr = top->selectNodes(bstr, &list);
    SysFreeString(bstr);
    if (FAILED(hr))
        throw L"selectNodes() failed";
    IXMLDOMNode* node;
    hr = list->nextNode(&node);
    if (FAILED(hr)) {
        list->Release();
        throw L"nextNode() failed for DOM node list";
    }
    std::vector<IXMLDOMElement*> elements;
    while (node) {
        IXMLDOMElement* e;
        hr = node->QueryInterface(__uuidof(IXMLDOMElement),
                                  (void**)&e);
        node->Release();
        node = NULL;
        if (FAILED(hr))
            throw L"QueryInterface failed for IXMLDOMElement";
        nodes.push_back(e);
        elements.push_back(e);
        hr = list->nextNode(&node);
        if (FAILED(hr)) {
            list->Release();
            throw L"nextNode() failed for DOM node list";
        }
    }
    list->Release();
    return elements;
}

// Give the caller a pointer to the document's root element.
IXMLDOMElement* cdr::ParsedDOM::get_root() {
    if (!root) {
        HRESULT hr = doc->get_documentElement(&root);
        if (FAILED(hr))
            throw L"get_documentElement() failed";
        nodes.push_back(root);
    }
    return root;
}

// Get the text content for one of the document's elements.
CString cdr::ParsedDOM::get_text(IXMLDOMElement* element) {
    if (!element)
        return L"";
    BSTR bstr = NULL;
    HRESULT hr = element->get_text(&bstr);
    if (FAILED(hr))
        throw L"get_text() failed";
    CString text(bstr);
    SysFreeString(bstr);
    return text;
}

// Get the string for the name of one of the document's elements.
CString cdr::ParsedDOM::get_node_name(IXMLDOMNode* node) {
    BSTR bstr = NULL;
    HRESULT hr = node->get_nodeName(&bstr);
    if (FAILED(hr))
        throw L"get_nodeName() failed";
    CString name(bstr);
    SysFreeString(bstr);
    return name;
}

// Get the string for the value of one of an element's attributes.
CString cdr::ParsedDOM::get(IXMLDOMElement* elem, const CString& name) {
    BSTR bstr = SysAllocString(name);
    if (!bstr)
        throw L"memory exhausted for attribute name";
    VARIANT variant;
    VariantInit(&variant);
    HRESULT hr = elem->getAttribute(bstr, &variant);
    SysFreeString(bstr);
    if (FAILED(hr)) {
        throw L"getAttribute failed";
    }
    CString value = "";
    if (variant.vt == VT_BSTR)
        value = variant.bstrVal;
    VariantClear(&variant);
    return value;
}
#endif

// Initialize the DOM.
cdr::DOM::DOM() {
    HRESULT hr = doc.CoCreateInstance(__uuidof(DOMDocument));
    if (FAILED(hr))
        throw L"Unable to initialize DOM";
    doc->put_async(VARIANT_FALSE);
    doc->put_validateOnParse(VARIANT_FALSE);
    doc->put_resolveExternals(VARIANT_FALSE);
    doc->put_preserveWhiteSpace(VARIANT_TRUE);
}

// Create the DOM object from its serialized XML.
cdr::DOM::DOM(const CString& xml) : DOM() {
    VARIANT_BOOL succeeded = VARIANT_FALSE;
    CComBSTR bstr(xml);
    if (FAILED(doc->loadXML(bstr, &succeeded)))
        throw L"loadXml() failed";
    if (succeeded == VARIANT_FALSE) {
        CComPtr<IXMLDOMParseError> parse_error;
        if (FAILED(doc->get_parseError(&parse_error)))
            throw L"XML parse failed but can't get parse error";
        CComBSTR reason;
        if (FAILED(parse_error->get_reason(&reason)))
            throw L"XML parse failed but can't get failure reason";
        CString why(reason);
        static wchar_t error[1024];
        wcsncpy(error, why.GetString(), 1023);
        throw error;
    }
}

// Create a DOM object with just a root element.
cdr::DOM::DOM(const char* root_name) : DOM() {
    root = child_element(doc, root_name);
}

// Attach an element to its existing parent.
void cdr::DOM::append(IXMLDOMNode* parent, IXMLDOMNode* child) {
    Node out;
    HRESULT hr = parent->appendChild(child, &out);
    if (FAILED(hr))
        throw L"appendChild() failed";
}

// Add a new text node to an existing element.
void cdr::DOM::append_text(IXMLDOMNode* parent, const CString& text) {
    CComBSTR bstr(text);
    CComPtr<IXMLDOMText> text_node;
    if (FAILED(doc->createTextNode(bstr, &text_node)))
        throw L"createTextNode() failed";
    append(parent, text_node);
}

// Create a new element and attach it to an existing parent.
cdr::DOM::Element cdr::DOM::child_element(IXMLDOMNode* parent,
                                          const CString& name,
                                          const CString& text) {
    Element e = element(name, text);
    append(parent, e);
    return e;
}

// Create a new element with optional text content.
cdr::DOM::Element cdr::DOM::element(const CString& name, const CString& text) {
    Element e;
    CComBSTR bstr(name);
    if (FAILED(doc->createElement(bstr, &e)))
        throw L"createElement() failed";
    if (!text.IsEmpty())
        append_text(e, text);
    return e;
}

// Find the first element matching an XPath query.
cdr::DOM::Element cdr::DOM::find(const CString& xpath, IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    CComBSTR bstr(xpath);
    Node node;
    if (FAILED(top->selectSingleNode(bstr, &node)))
        throw L"selectSingleNode() failed";
    if (!node)
        return NULL;
    Element element;
    HRESULT hr = node->QueryInterface(__uuidof(IXMLDOMElement),
                                      (void**)&element);
    if (FAILED(hr))
        throw L"QueryInterface failed for IXMLDOMElement";
    return element;
}

// Find all the elements matching an XPath query.
std::vector<cdr::DOM::Element> cdr::DOM::find_all(const CString& xpath,
                                                  IXMLDOMElement* top) {
    if (!top)
        top = get_root();
    CComBSTR bstr(xpath);
    NodeList list = NULL;
    if (FAILED(top->selectNodes(bstr, &list)))
        throw L"selectNodes() failed";
    std::vector<Element> elements;
    for (;;) {
        Node node;
        if (FAILED(list->nextNode(&node)))
            throw L"nextNode() failed for DOM node list";
        if (!node)
            return elements;
        Element e;
        if (FAILED(node->QueryInterface(__uuidof(IXMLDOMElement), (void**)&e)))
            throw L"QueryInterface failed for IXMLDOMElement";
        elements.push_back(e);
    }
}

// Get the string for the value of one of an element's attributes.
CString cdr::DOM::get(IXMLDOMElement* elem, const CString& name) {
    CComBSTR bstr(name);
    /*
    VARIANT variant;
    VariantInit(&variant);
    if (FAILED(elem->getAttribute(bstr, &variant)))
        throw L"getAttribute failed";
    CString value = "";
    if (variant.vt == VT_BSTR)
        value = variant.bstrVal;
    VariantClear(&variant);
    return value;
    */
    CComVariant variant;
    if (FAILED(elem->getAttribute(bstr, &variant)))
        throw L"getAttribute failed";
    CString value(variant);
    return value;
}

// Get the string for the name of one of the document's elements.
CString cdr::DOM::get_node_name(IXMLDOMNode* node) {
    CComBSTR bstr;
    if (FAILED(node->get_nodeName(&bstr)))
        throw L"get_nodeName() failed";
    CString name(bstr);
    return name;
}

// Give the caller a pointer to the document's root element.
cdr::DOM::Element cdr::DOM::get_root() {
    if (!root) {
        if (FAILED(doc->get_documentElement(&root)))
            throw L"get_documentElement() failed";
    }
    return root;
}

// Get the text content for one of the document's elements.
CString cdr::DOM::get_text(IXMLDOMNode* element) {
    if (!element)
        return L"";
    CComBSTR bstr;
    if (FAILED(element->get_text(&bstr)))
        throw L"get_text() failed";
    CString text(bstr);
    return text;
}

// Serialize the document to a string.
CString cdr::DOM::get_xml(IXMLDOMNode* node) const {
    CComBSTR bstr;
    if (!node)
        node = doc;
    if (FAILED(node->get_xml(&bstr)))
        throw L"get_xml() failed";
    CString xml(bstr);
    return xml;
}

// Install a node in front of an existing node.
void cdr::DOM::insert(IXMLDOMNode* parent, IXMLDOMNode* new_node,
                      IXMLDOMNode* sibling) {
    Node out;
    CComVariant reference(sibling);
    HRESULT hr = parent->insertBefore(new_node, reference, &out);
    if (FAILED(hr))
        throw L"insertBefore() failed";
}

// Assign a value to one of an element's attributes.
void cdr::DOM::set(IXMLDOMElement* elem, const CString& name,
                   const CString& value) {
    CComBSTR bstr_name(name);
    CComPtr<IXMLDOMAttribute> attr;
    if (FAILED(doc->createAttribute(bstr_name, &attr)))
        throw L"createAttribute() failed";
    CComBSTR bstr_value(value);
    CComVariant variant(bstr_value);
    if (FAILED(attr->put_value(variant)))
        throw L"put_value() failed for attribute";
    CComPtr<IXMLDOMAttribute> out;
    if (FAILED(elem->setAttributeNode(attr, &out)))
        throw L"setAttributeNode() failed";
}

// Make an existing element node the new root of the DOM document.
void cdr::DOM::set_root(IXMLDOMElement* new_root) {
    Element old_root = get_root();
    if (old_root) {
        Node out_root;
        if (FAILED(doc->replaceChild(new_root, old_root, &out_root)))
            throw L"replaceChild() failed";
    }
    else {
        root = new_root;
        append(doc, root);
    }
}

cdr::CommandSet::CommandSet(const char* name, bool guest)
    : DOM("CdrCommandSet") {
    CString session = CdrSocket::getSessionString();
    if (session.IsEmpty() && guest)
        session = "guest";
    if (!session.IsEmpty())
        child_element(root, "SessionId", session);
    auto wrapper = child_element(root, "CdrCommand");
    command = child_element(wrapper, name);
}

void cdr::CommandSet::add_cdr_document(IXMLDOMElement* parent, DOMNode& doc) {
    auto child = child_element(parent, "CdrDocXml");
    std::wostringstream os;
    os << doc;
    CComBSTR bstr(os.str().c_str());
    CComPtr<IXMLDOMCDATASection> cdata;
    HRESULT hr = this->doc->createCDATASection(bstr, &cdata);
    if (FAILED(hr))
        throw L"createCDATASection failed";
    append(child, cdata);
}
