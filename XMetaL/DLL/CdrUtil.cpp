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
extern void debugLogWrite(const CString& what, const CString& who);

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
        ::AfxMessageBox(_T("Unable to initialize Windows socket library"));
        throw _T("Failure initializing Windows socket library");
    }
    const TCHAR* cdrHostEnv = _tgetenv(_T("CDR_HOST"));
    const TCHAR* apiHostEnv = _tgetenv(_T("API_HOST"));
    const TCHAR* sessionEnv = _tgetenv(_T("CDRSession"));
    cdrHost = cdrHostEnv ? cdrHostEnv : _T("cdr-dev.cancer.gov");
    apiHost = apiHostEnv ? apiHostEnv : _T("cdrapi-dev.cancer.gov");

    // Don't do this: it short-circuits needed initialization code.
    // sessionString = sessionEnv ? sessionEnv : _T("");

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
        CString front = _T("<CdrCommandSet>");
        if (!sessionString.IsEmpty())
            front += _T("<SessionId>") + sessionString + _T("</SessionId>");
        else if (guest)
            front += _T("<SessionId>guest</SessionId>");
        front += _T("<CdrCommand>");
        CString back = _T("</CdrCommand></CdrCommandSet>");
        const char* commands;

        // Use caller's buffer if present.
        long requestLen = 0;
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
        const TCHAR* verb = _T("POST");
        const TCHAR* target = _T("/");
        headers.Format(_T("Content-type: text/xml\n"));
        DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
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
            throw _T("Failure submitting request to server");

        // Make sure the server thinks we succeeded.
        DWORD result;
        file->QueryInfoStatusCode(result);
        if (result != HTTP_STATUS_OK) {
            CString err;
            err.Format(_T("HTTP status code from server: %lu"), result);
            throw err;
        }

        // Read the response in chunks.
        static char buf[1024 * 1024];
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
    catch (...) { return errResponse(_T("sendCommand: unexpected failure")); }
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
    CString open = _T("<") + tag + _T(">");
    CString close = _T("</") + tag + _T(">");

    // Find the tags.
    int pos = xml.Find(open);
    if (pos == -1)
        return _T("");
    pos += open.GetLength();
    int endPos = xml.Find(close, pos);

    // Make sure we found the element.
    if (endPos == -1 || endPos == pos)
        return _T("");

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
    int pos = msg.Find(_T("<Err>"));
    int n = 0;
    while (pos != -1) {

        // Extract the error message.
        pos += 5;
        int endPos = msg.Find(_T("</Err>"), pos);
        if (endPos == -1) {
            ::AfxMessageBox(_T("Missing closing tag for Err element"));
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
        pos = msg.Find(_T("<Err>"), endPos);
    }

    // Tell the caller if we displayed any error messages.
    return n > 0;
}

bool cdr::showValidationErrors(cdr::ValidationErrors& errors)
{
    // Walk through the errors.
    const cdr::ValidationError* error = errors.getNextError();
    int n = 0;
    while (error) {
        CString msg = _T("[") + error->eid + _T("] ") + error->message;
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
    Element r = Element::extractElement(xml, _T("QueryResult"));

    // Loop through each QueryResult element.
    while (r) {
        Element id    = r.extractElement(r.getString(), _T("DocId"));
        Element type  = r.extractElement(r.getString(), _T("DocType"));
        Element title = r.extractElement(r.getString(), _T("DocTitle"));
        SearchResult qr = SearchResult(id.getString(),
                                       type.getString(),
                                       title.getString());
        docSet.push_back(qr);
        r = r.extractElement(xml, _T("QueryResult"), r.getEndPos());
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
            CString str = _T("[") + id + _T("] ") + cdr::decode(title);
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
    debugLogWrite(_T("Top of getApp()"), _T("rmk"));
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
        debugLogWrite(_T("Before CreateDispatch()"), _T("rmk"));
        if (app.CreateDispatch(_T("XMetaL.Application"), &e)) {
            debugLogWrite(_T("After CreateDispatch()"), _T("rmk"));
            return app;
        }
        debugLogWrite(_T("After after CreateDispatch()"), _T("rmk"));
        e.ReportError();
    }
    catch (CException *ee) {
        debugLogWrite(_T("Caught exception in cdr::getApp()\n"), _T("rmk"));
        ee->ReportError();
        debugLogWrite(_T("Reported exception in cdr::getApp()\n"), _T("rmk"));
    }
    throw _T("Unable to create XMetaL Application-level automation object");
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
        CString tail = _T("\\Softquad\\XMetaL\\");
        TCHAR* vars[] = { _T("LOCALAPPDATA"), _T("APPDATA") };
        TCHAR* vers[] = { _T("9.0"), _T("4.5") };
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
    CString manifest = path + _T("\\CdrManifest.xml");
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
    str.Replace(_T("&"), _T("&amp;"));
    str.Replace(_T("<"), _T("&lt;"));
    str.Replace(_T(">"), _T("&gt;"));
    if (fixQuotes) {
        str.Replace(_T("\""), _T("&quot;"));
        str.Replace(_T("'"), _T("&apos;"));
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
    str.Replace(_T("&amp;"), _T("&"));
    str.Replace(_T("&lt;"), _T("<"));
    str.Replace(_T("&gt;"), _T(">"));
    str.Replace(_T("&quot;"), _T("\""));
    str.Replace(_T("&apos;"), _T("'"));
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
    int pos = docString.FindOneOf(_T("0123456789"));
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
            if (node.GetNodeName() == _T("CdrDocCtl")) {

                // Check the ready-for-review flag.  This is where we
                // stick the document when we pass it off to XMetaL
                // (so we don't have to worry about formatting it in
                // the CSS).
                ::DOMElement cdrDocCtl = node;
                if (cdrDocCtl.getAttribute(_T("readyForReview")) == _T("Y"))
                    info.readyForReview = true;

                // MUST do this!  Otherwise XMetaL blows up with a complaint
                // about a pure virtual function!
                cdrDocCtl.m_bAutoRelease = 0;

                node = node.GetFirstChild();
                while (node) {

                    // Only interested in elements (type 1).
                    if (node.GetNodeType() == 1) {
                        CString name = node.GetNodeName();
                        if (name == _T("DocTitle"))
                            info.docTitle =
                                cdr::encode(extractElementText(node));
                        else if (name == _T("DocId"))
                            info.docId = cdr::trim(extractElementText(node));

                        // This is where we find this flag when we get the
                        // document from the CDR Server.
                        else if (name == _T("ReadyForReview")) {
                            if (extractElementText(node) == _T("Y"))
                                info.readyForReview = true;
                        }
                        else if (name == _T("DocActiveStatus")) {
                            if (extractElementText(node) == _T("I"))
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
    return _T("<CdrResponseSet><CdrResponse Status='failure'><Errors><Err>")
        + err + _T("</Err></Errors></CdrResponse></CdrResponseSet>");
}

/**
 * Writes the string equivalent of the XML tree represented by the caller's
 * DOM node.
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
    if (nodeType == 1 && name != _T("CdrDocCtl")) {

        // Element node.  Output the start tag.
        os << _T("<") << (LPCTSTR)name;
        DOMNamedNodeMap attrs = node.GetAttributes();
        int n = attrs.GetLength();
        for (int i = 0; i < n; ++i) {
            DOMNode attr = attrs.item(i);
            CString attrName = attr.GetNodeName();
            if (attrName != _T("readonly")) {
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
                os << _T(" ") << (LPCTSTR)attrName << _T("='")
                   << (LPCTSTR)cdr::encode(cdr::decode(val), true) << _T("'");
            }
        }
        if (!node.hasChildNodes())
            os << _T("/");
        os << _T(">");
    }

    // If this is a text node (type 3) pump out the characters.
    else if (nodeType == 3) {

        CString val = node.GetNodeValue();
        os << (LPCTSTR)cdr::encode(val);
    }

    // Handle processing instructions.
    else if (nodeType == 7) {

        CString val = node.GetNodeValue();
        os << _T("<?") << (LPCTSTR)name << _T(" ") << (LPCTSTR)val << _T("?>");
    }

    // Don't lose comments.
    else if (nodeType == 8) {

        CString val = node.GetNodeValue();
        os << _T("<!--") << (LPCTSTR)val << _T("-->");
    }

    // Process any children of the node.
    if (node.hasChildNodes() && name != "CdrDocCtl") {
        DOMNode n = node.GetFirstChild();
        os << n;

        // If this is an element node, write the closing tag.
        if (nodeType == 1)
            os << _T("</") << (LPCTSTR)name << _T(">");
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
#ifndef _UNICODE
        if ((unsigned short)newStr[j] > 0xFF) {
            CString err;
            err.Format(_T("Received Unicode character U%04X which")
                       _T(" will not fit in the ANSI character set;")
                       _T(" build DLL with _UNICODE defined."),
                       (unsigned short)newStr[i]);
            throw (LPCTSTR)err;
        }
#endif
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
    int startPos = s.Find(_T("<") + name, pos);
    while (startPos != -1) {
        if (startPos + nameLen + 1 >= strLen)
            return e;
        startPos += nameLen + 1;
        TCHAR ch = s[startPos];

        // Make sure we don't have another tag that starts the same way.
        if (_istspace(ch) || ch == (TCHAR)'>' || ch == (TCHAR)'/')
            break;

        // Try another position.
        startPos = s.Find(_T("<") + name, startPos);
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
            startPos = s.Find(_T(">"), startPos);
            if (startPos == -1)
                return e;
            e.startPos = e.endPos = startPos + 1;
            e.str = _T("");
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
                    throw (LPCTSTR)(_T("Duplicate attribute ") + attrName +
                                    _T(" in element ") + name);
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
    int endPos = s.Find(_T("</") + name + _T(">"), startPos);
    if (endPos == -1)
        return e;
    e.str = s.Mid(startPos, endPos - startPos);
    e.startPos = startPos;
    e.endPos = endPos;
    return e;
}

CString cdr::Element::getCdataSection() const {
    static CString target = _T("<![CDATA[");
    int pos = str.Find(target);
    if (pos == -1)
        return CString();
    pos += target.GetLength();
    int end = str.Find(_T("]]>"), pos);
    if (end == -1)
        return CString();
    return str.Mid(pos, end - pos);
}

CdrLinkInfo cdr::extractLinkInfo(const CString& str) {
    CdrLinkInfo info;

    // Parse out the document ID and text content.
    int pos = str.Find(_T("["));
    if (pos == -1) {
        ::AfxMessageBox(_T("Unable to find link target start delimiter."));
        return info;
    }
    int endPos = str.Find(_T("]"), ++pos);
    if (endPos == -1) {
        ::AfxMessageBox(_T("Unable to find link target end delimiter."));
        return info;
    }
    info.target = str.Mid(pos, endPos - pos);
    pos = endPos + 1;
    while (pos < str.GetLength() && str[pos] == _T(' '))
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
    swprintf(buf, _T("CDR%010d"), id);
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
    CString zeros = _T("0000000000");
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
        if (!ie.CreateDispatch(_T("InternetExplorer.Application"), pe)) {
            DWORD error = ::GetLastError();
            TCHAR buf[256];
            swprintf(buf,
               _T("CreateDisplatch: Unable to launch Internet Explorer (%ld)"),
               error);
            ::AfxMessageBox(buf, MB_ICONEXCLAMATION);
            throw pe;
        }
    }
    catch (COleDispatchException* pExc) {
        CString s;
        if (!pExc->m_strSource.IsEmpty())
            s = pExc->m_strSource + _T(" - ");
        if (!pExc->m_strDescription.IsEmpty())
            s += pExc->m_strDescription;
        else
            s += _T("unknown error");
        ::AfxMessageBox(s, MB_OK, pExc->m_strHelpFile.IsEmpty() ? 0
                        : pExc->m_dwHelpContext);
        pExc->Delete();
        return EXIT_FAILURE;
    }
    catch (CException* e) {
        TCHAR b[256];
        swprintf(b, _T("%S(%d): OLE Exception caught: SCODE = %x"),
                 __FILE__, __LINE__, COleException::Process(e));
        ::AfxMessageBox(b, MB_OK);
        e->Delete();
        return EXIT_FAILURE;
    }
    pe->Delete();
    DISPID dispid;
    OLECHAR* member = _T("Navigate");
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL,
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(_T("GetIDsOfNames: Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return EXIT_FAILURE;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
        url, 0L, _T("CdrViewWindow"), &dummy, &dummy);
    return EXIT_SUCCESS;
}
#endif
int cdr::showPage(const CString& url) {
    CString ie = _T("\"%ProgramFiles%\\Internet Explorer\\iexplore.exe\"");
    CString command = _T("\"") + ie + _T(" \"") + url + _T("\"\"");
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
            ::AfxMessageBox(_T("Can't open log file"));
        }
        return;
    }
    fprintf(logFile, "%s\n", cdr::cStringToUtf8(what).c_str());
    fclose(logFile);
}

cdr::GlossaryTree::GlossaryTree(const CString& command) {
    CString response = CdrSocket::sendCommand(command, true);
    // logWrite(response);
    cdr::Element termElem = cdr::Element::extractElement(response, _T("Term"));
    while (termElem) {
        LPCTSTR p = (LPCTSTR)termElem.getAttribute(_T("id"));
        int docId = _tcstoul(p, 0, 10);
        CString termString = termElem.getString();
        cdr::Element nameElem = cdr::Element::extractElement(termString,
                                                             _T("Name"));
        CString name = cdr::decode(nameElem.getString());
        cdr::Element phraseElem = cdr::Element::extractElement(termString,
                                                               _T("Phrase"));
        names[docId] = name;
        while (phraseElem) {
            int numWords = 0;
            int start = 0;
            GlossaryNodeMap* currentMap = &nodeMap;
            GlossaryNode*    currentNode = 0;
            CString phrase = cdr::decode(phraseElem.getString());
            while (start < phrase.GetLength()) {
                int end = phrase.Find(_T(" "), start);
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
            phraseElem = cdr::Element::extractElement(termString, _T("Phrase"),
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
        termElem = cdr::Element::extractElement(response, _T("Term"),
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

// Constructor for set of validation error messages.
cdr::ValidationErrors::ValidationErrors(const Element& e) {
    currentError = 0;
    Element err = Element::extractElement(e.getString(), _T("Err"), 0);
    while (err) {
        CString message = err.getString();
        CString eid = err.getAttribute(_T("eref"));
        CString etype = err.getAttribute(_T("etype"));
        CString elevel = err.getAttribute(_T("elevel"));
        if (etype == _T("validation"))
            errors.push_back(cdr::ValidationError(message, eid, elevel));
        else
            ::AfxMessageBox(message + _T(" (") + elevel + _T(")"));
        err = Element::extractElement(e.getString(), _T("Err"),
                                      err.getEndPos());
    }
}

// static cdr::GlossaryTree* glossaryTree;
cdr::GlossaryTree* cdr::getGlossaryTree(const CString& language) {

    // Make sure the memory gets cleaned up so BoundsChecker is happy.
    struct GlossaryTreeWrapper {
        GlossaryTreeWrapper() : tree(0) {}
        ~GlossaryTreeWrapper() { if (tree) delete tree; }
        cdr::GlossaryTree* tree;
    };
    static GlossaryTreeWrapper englishWrapper;
    static GlossaryTreeWrapper spanishWrapper;

    // No need for locking; we'll be called in a single thread.
    if (language == _T("es")) {
        if (!spanishWrapper.tree) {
            CString command = _T("<CdrGetSpanishGlossaryMap/>");
            spanishWrapper.tree = new cdr::GlossaryTree(command);
        }
        return spanishWrapper.tree;
    }
    else {
        if (!englishWrapper.tree) {
            CString command = _T("<CdrGetGlossaryMap/>");
            englishWrapper.tree = new cdr::GlossaryTree(command);
        }
        return englishWrapper.tree;
    }
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
    CInternetSession session(_T("CDR"));
    DWORD flags = INTERNET_FLAG_TRANSFER_BINARY;
    if (url.Left(5) == _T("https"))
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

void cdr::trace_log(const char* what) {
    static bool startup = true;
    if (startup) {
        cdr::send_trace_log();
        startup = false;
    }
    try {
        SYSTEMTIME sys_time;
        ::GetLocalTime(&sys_time);
        const char* path = get_cdr_trace_log_path();
        if (!path)
            return;
        FILE* fp = fopen(path, "ab");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d.%03d %s",
                sys_time.wYear,
                sys_time.wMonth,
                sys_time.wDay,
                sys_time.wHour,
                sys_time.wMinute,
                sys_time.wSecond,
                sys_time.wMilliseconds,
                what);
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
        CString command = _T("<CdrSaveClientTraceLog><LogData>");
        command += cdr::encode(log_data);
        command += _T("</LogData></CdrSaveClientTraceLog>");
        CString response = CdrSocket::sendCommand(command, true);
        if (response.Find(_T("success")) >= 0)
            _unlink(path);
    }
    catch (...) {}
}
