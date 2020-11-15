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
static CString err_response(const CString& err);
static bool is_user_path(const CString& path);
static std::string log_timestamp();

/**
 * Login token obtained from the CDR server.
 */
CString CdrSocket::session_string;

/**
 * DNS names for CDR server host.
 */
CString CdrSocket::cdr_host;
CString CdrSocket::api_host;

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
cdr::ValidationErrorSets cdr::validation_error_sets;

/**
 * Initialize the Winsock package and figure out which tier we're talking to.
 */
CdrSocket::Init::Init()
{
    if (WSAStartup(0x0101, &wsa_data) != 0) {
        ::AfxMessageBox(L"Unable to initialize Windows socket library");
        throw L"Failure initializing Windows socket library";
    }
    const wchar_t* cdr_host_env = _tgetenv(L"CDR_HOST");
    const wchar_t* api_host_env = _tgetenv(L"API_HOST");
    const wchar_t* session_env  = _tgetenv(L"CDRSession");
    const wchar_t* cdr_tier_env = _tgetenv(L"CDR_TIER");
    cdr_host = cdr_host_env ? cdr_host_env : L"cdr-dev.cancer.gov";
    if (cdr_tier_env) {
        CString tier_buf;
        tier_buf.Format(L"env var CDR_TIER=%s", cdr_tier_env);
        cdr::trace_log(cdr::cstring_to_utf8(tier_buf).c_str());
        tier = cdr_tier_env;
    }
    else {
        CString lower_host_name = cdr_host;
        tier = "UNKNOWN TIER";
        lower_host_name.MakeLower();
        if (lower_host_name == "cdr.cancer.gov")
            tier = "PROD";
        else if (lower_host_name == "cdr-dev.cancer.gov")
            tier = "DEV";
        else if (lower_host_name == "cdr-qa.cancer.gov")
            tier = "QA";
        else if (lower_host_name == "cdr-stage.cancer.gov")
            tier = "STAGE";
    }
    if (api_host_env)
        api_host = api_host_env;
    else {
        if (tier == "PROD")
            api_host = L"cdrapi.cancer.gov";
        else {
            api_host.Format(L"cdrapi-%s.cancer.gov", tier);
            api_host.MakeLower();
        }
    }
    CString buf;
    buf.Format(L"cdrhost=%s apihost=%s", cdr_host_env, api_host_env);
    cdr::trace_log(cdr::cstring_to_utf8(buf).c_str());
}

/**
 * Performs cleanup of the Winsock package.
 */
CdrSocket::Init::~Init()
{
    WSACleanup();
}

CString CdrSocket::send_commands(const cdr::CommandSet& commands, char* blob) {
    try {

        CWaitCursor wc;

        // Serialize the command set.
        debug_log("top of send_commands()");
        CString xml_string = commands.get_xml();
        xml_string.Remove(L'\r');
        std::string xml = cdr::cstring_to_utf8(xml_string);

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
        const char* bytes = xml.c_str();
        DWORD length = (DWORD)xml.length();
        BOOL success = FALSE;
        INTERNET_PORT port = 443;
        const wchar_t* verb = L"POST";
        const wchar_t* target = L"/";
        DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
        session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, 180000);
        CHttpConnection* conn = session.GetHttpConnection(api_host, port);
        file = conn->OpenRequest(verb, target, NULL, 1, NULL, NULL, flags);

        // Sometimes this fails the first time; don't give up too quickly.
        for (int i = 0; !success && i < 3; ++i) {
            DWORD sec_flags;
            file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, sec_flags);
            sec_flags |= SECURITY_IGNORE_ERROR_MASK;
            file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, sec_flags);
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
        CString response = cdr::utf8_to_cstring(temp.c_str());
        return response;
    }
    catch (const wchar_t* error) { return err_response(error); }
    catch (const CString& err) { return err_response(err); }
    catch (CException *ee) {
        wchar_t message[1024];
        ee->GetErrorMessage(message, 1023);
        CString msg;
        msg.Format(L"failure sending command: %s", message);
        ee->Delete();
        return err_response(msg);
    }
    catch (...) { return err_response(L"send_commands: unexpected failure"); }
}

/**
 * Show errors returned in the server's response.
 *
 *  @param response - parsed response from server
 *
 * Return:
 *   true if any errors were found and displayed.
 */
bool cdr::show_errors(cdr::DOM& response) {
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

bool cdr::show_validation_errors(cdr::ValidationErrors& errors)
{
    // Walk through the errors.
    const cdr::ValidationError* error = errors.get_next_error();
    int n = 0;
    while (error) {
        CString msg = L"[" + error->eid + L"] " + error->message;
        int rc = ::AfxMessageBox(msg, MB_OKCANCEL);
        ++n;

        // Let the user bail out to avoid seeing cascading error messages.
        if (rc == IDCANCEL) {
            errors.current_error--;
            break;
        }
        error = errors.get_next_error();
    }

    // Tell the caller if we displayed any error messages.
    return n > 0;
}

/**
 * Extracts document information from the XML containing the CDR
 * server's response.
 *
 *  @param  dom             reference to parsed server query response
 *  @param  doc_set          reference to set we will populate
 */
void cdr::extract_search_results(DOM& dom, DocSet& docSet)
{
    // Extract the first query result.
    docSet.clear();
    auto nodes = dom.find_all("//QueryResult");
    for (auto& node : nodes) {
        CString id = dom.get_text(dom.find("DocId", node));
        CString type = dom.get_text(dom.find("DocType", node));
        CString title = dom.get_text(dom.find("DocTitle", node));
        docSet.push_back(SearchResult(id, type, title));
    }
}

/**
 * Populates the caller's list box object with strings drawn from the query
 * result information passed in.
 *
 *  @param  list_box        reference to caller's list box, to which
 *                          we add strings identifying each document
 *                          in the server's response.
 *  @param  doc_set         reference to list of SearchResult objects.
 *  @return                 number of strings added to list box, or -1
 *                          in the event of an error.
 */
int cdr::fill_list_box(CListBox& list_box, const DocSet& doc_set)
{
    // Start with a clean slate.
    list_box.ResetContent();
    int n         = 0;
    int max_width = 0;
    CDC*   dc     = 0;
    CFont* font   = list_box.GetFont();
    ASSERT(font);

    // Wrap this in a try block so we're sure to release the device context.
    try {

        dc = list_box.GetDC();

        // Loop through the elements of the document set.
        DocSet::const_iterator iter = doc_set.begin();
        while (iter != doc_set.end()) {

            // Build a string in the form "[doc-id] doc-title"
            CString id    = (*iter).get_doc_id();
            CString title = (*iter).get_doc_title();
            ++iter;
            ++n;

            // Append the new string to the list box object.
            CString str = L"[" + id + L"] " + title;
            CSize size  = dc->GetTextExtent(str);
            if (max_width < size.cx)
                max_width = size.cx;
            list_box.AddString(str);
        }

        // Make sure horizontal scrolling works properly.
        list_box.SetHorizontalExtent(max_width + 6);
    }
    catch (...) {
        if (dc) {
            list_box.ReleaseDC(dc);
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
_Application cdr::get_app()
{
    debug_log("Top of getApp()");
    _Application app;
    CWinApp* win_app = ::AfxGetApp();
    if (!win_app->m_pMessageFilter) {
        win_app->m_pMessageFilter = new COleMessageFilter();
        win_app->m_pMessageFilter->Register();
    }
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
CString cdr::get_xmetal_path() {
    static CString xmetal_path;
    if (xmetal_path.IsEmpty()) {
        _Application app = get_app();
        if (app)
            xmetal_path = app.GetPath();
    }
    return xmetal_path;
}

/**
 * Finds the user-specific location where client files for the application
 * are stored.
 *
 *  @return             reference to string containing location for client
 *                      files.
 */
CString cdr::get_user_path() {
    static CString user_path;
    if (user_path.IsEmpty()) {
        CString tail = L"\\Softquad\\XMetaL\\";
        wchar_t* vars[] = { L"LOCALAPPDATA", L"APPDATA" };
        wchar_t* vers[] = { L"9.0", L"4.5" };
        for (size_t i = 0; i < sizeof vars / sizeof vars[0]; ++i) {
            wchar_t* dir = _tgetenv(vars[i]);
            if (dir) {
                for (size_t j = 0; j < sizeof vers / sizeof vers[0]; ++j) {
                    CString candidate = CString(dir) + tail + CString(vers[j]);
                    if (is_user_path(candidate)) {
                        user_path = candidate;
                        return user_path;
                    }
                }
            }
        }
        user_path = cdr::get_xmetal_path();
    }
    return user_path;
}

/**
 * Test a candidate path to determine whether it can be used to store
 * client files for our application.
 *
 *  @param  path      fully qualified path string for candidate path
 */
bool is_user_path(const CString& path) {
    CString manifest = path + L"\\CdrManifest.xml";
    if (!_waccess((LPCTSTR)manifest, 0))
        return true;
    return false;
}

/**
 * Extracts document number from CDR ID string, which is generally
 * in the form "CDR\d\d\d\d\d\d\d\d\d\d".
 *
 *  @param  doc_string       reference to document ID string.
 *  @return                 integer representing document's primary key
 *                          in SQL Server.
 */
unsigned long cdr::get_doc_no(const CString& doc_string) {
    int pos = doc_string.FindOneOf(L"0123456789");
    if (pos == -1)
        return 0L;
    const wchar_t* p = (const wchar_t*)doc_string;
    return _tcstoul(p + pos, 0, 10);
}

/**
 * Extracts and concatenates the text content for an element.
 *
 *  @param  node            DOM node object for element.
 *  @return                 string object containing concatenated text
 *                          content for element.
 */
CString cdr::extract_element_text(DOMNode node) {
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
    CString new_str = s;
    new_str.TrimRight();
    new_str.TrimLeft();
    return new_str;
}

/**
 * Pulls out the document's type, title, and ID from its XML representation.
 *
 *  @param  node            reference to DOM node object for document.
 *  @param  info            reference to control information object to be
 *                          populated.
 */
void cdr::extract_ctl_info(DOMNode node, CdrDocCtrlInfo& info) {
    // Initialize flags to defaults.
    info.ready_for_review = false;
    info.blocked        = false;

    // Get type from doc element name
    info.doc_type = node.GetNodeName();

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
                ::DOMElement cdr_doc_ctl = node;
                if (cdr_doc_ctl.getAttribute(L"readyForReview") == L"Y")
                    info.ready_for_review = true;

                // MUST do this!  Otherwise XMetaL blows up with a complaint
                // about a pure virtual function!
                cdr_doc_ctl.m_bAutoRelease = 0;

                node = node.GetFirstChild();
                while (node) {

                    // Only interested in elements (type 1).
                    if (node.GetNodeType() == 1) {
                        CString name = node.GetNodeName();
                        if (name == L"DocTitle")
                            info.doc_title = extract_element_text(node);
                        else if (name == L"DocId")
                            info.doc_id = cdr::trim(extract_element_text(node));

                        // This is where we find this flag when we get the
                        // document from the CDR Server.
                        else if (name == L"ReadyForReview") {
                            if (extract_element_text(node) == L"Y")
                                info.ready_for_review = true;
                        }
                        else if (name == L"DocActiveStatus") {
                            if (extract_element_text(node) == L"I")
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
CString err_response(const CString& err) {
    cdr::DOM dom("CdrResponseSet");
    auto root = dom.get_root();
    auto response = dom.child_element(root, "CdrResponse");
    dom.set(response, "Status", "failure");
    auto errors = dom.child_element(response, "Errors");
    dom.child_element(errors, "Err", err);
    return dom.get_xml();
}

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 */
inline unsigned short char_to_unsigned_short(wchar_t c) {
    return static_cast<unsigned short>(c);
}

std::string cdr::cstring_to_utf8(const CString& str) {
    // Calculate storage requirement.
    size_t i, len = 0;
    size_t str_len = str.GetLength();
    const wchar_t* wchars = static_cast<const wchar_t*>(str);
    for (i = 0; i < str_len; ++i) {
        unsigned short ch = char_to_unsigned_short(wchars[i]);
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
    for (i = j = 0; i < str_len; ++i) {
        unsigned short ch = char_to_unsigned_short(*wchars++);
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
CString cdr::utf8_to_cstring(const char* s) {
    // Calculate storage requirement.
    size_t i, len = 0;
    for (i = 0; s[i]; ++i) {
        if (((unsigned char)s[i] & 0x80) == 0)
            ++len;
        else if (((unsigned char)s[i] & 0x40) == 0x40)
            ++len;
    }

    // Make room.
    std::wstring new_str(len, ' ');

    // Populate string.
    for (i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)*s;
        if (ch < 0x80) {
            new_str[i] = (wchar_t)ch;
            ++s;
        }
        else if ((ch & 0xE0) == 0xC0) {
            new_str[i] = ((ch & 0x1F) << 6)
                       | (((unsigned char)s[1]) & 0x3F);
            s += 2;
        }
        else {
            new_str[i] = ((ch & 0x0F) << 12)
                       | ((((unsigned char)s[1]) & 0x3F) << 6)
                       | (((unsigned char)s[2]) & 0x3F);
            s += 3;
        }
    }
    return CString(new_str.c_str());
}

CdrLinkInfo cdr::extract_link_info(const CString& str) {
    CdrLinkInfo info;

    // Parse out the document ID and text content.
    int pos = str.Find(L"[");
    if (pos == -1) {
        ::AfxMessageBox(L"Unable to find link target start delimiter.");
        return info;
    }
    int end_pos = str.Find(L"]", ++pos);
    if (end_pos == -1) {
        ::AfxMessageBox(L"Unable to find link target end delimiter.");
        return info;
    }
    info.target = str.Mid(pos, end_pos - pos);
    pos = end_pos + 1;
    while (pos < str.GetLength() && str[pos] == L' ')
        ++pos;
    info.data = str.Mid(pos);
    return info;
}

::Range cdr::get_elem_range(const CString& elemName) {
    // Find out where we are.
    ::_Document active_doc = get_app().GetActiveDocument();
    ::Range rng = active_doc.GetRange();

    // Make sure what we find is an ancestor of the current element.
    if (!rng.GetIsParentElement(elemName))
        return ::Range();

    // Move.
    if (!rng.MoveToElement(elemName, FALSE))
        return ::Range();

    return rng;
}

::Range cdr::find_or_create_child(::Range parent, const CString& elemName) {
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

CString cdr::doc_id_string(int id) {
    wchar_t buf[40];
    swprintf(buf, L"CDR%010d", id);
    return buf;
}

CString cdr::suppress_leading_zeros(const CString& s) {
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
    int keep_on_right = s.GetLength() - i;
    return s.Left(keepOnLeft) + s.Right(keep_on_right);
}

CString cdr::expand_leading_zeros(const CString& s) {
    CString zeros = L"0000000000";
    int i = 0;
    int first_digit = 0;
    int num_digits = 0;
    while (i < s.GetLength()) {
        if (_istdigit(s.GetAt(i))) {
            first_digit = i++;
            num_digits = 1;
            break;
        }
        ++i;
    }
    while (i < s.GetLength()) {
        if (!_istdigit(s.GetAt(i)))
            break;
        ++i;
        ++num_digits;
    }
    if (num_digits >= 10 || num_digits < 1)
        return s;
    int zeros_needed = 10 - num_digits;
    return s.Left(first_digit) + zeros.Left(zeros_needed) + s.Mid(first_digit);
}

int cdr::show_page(const CString& url) {
    CString ie = L"\"%ProgramFiles%\\Internet Explorer\\iexplore.exe\"";
    CString command = L"\"" + ie + L" \"" + url + L"\"\"";
    _tsystem(command);
    return EXIT_SUCCESS;
}
cdr::GlossaryTree::GlossaryTree(const CString& language,
                                const CString& dictionary) {
    char* tag = "CdrGetGlossaryMap";
    if (language == L"es")
        tag = "CdrGetSpanishGlossaryMap";
    cdr::CommandSet request(tag);
    if (!dictionary.IsEmpty())
        request.child_element(request.command, "Dictionary", dictionary);
    CString response_xml = CdrSocket::send_commands(request);
    cdr::DOM dom(response_xml);
    auto nodes = dom.find_all("//Term");
    std::wistringstream iss;
    for (auto& node : nodes) {
        int id = (int)get_doc_no(dom.get(node, "id").GetString());
        CString name = dom.get_text(dom.find("Name", node));
        names[id] = name;
        auto phrase_nodes = dom.find_all("Phrase", node);
        for (auto& phrase_node : phrase_nodes) {
            GlossaryNodeMap* current_map = &node_map;
            GlossaryNode* current_node = nullptr;
            iss.str(dom.get_text(phrase_node).GetString());
            iss.clear();
            iss.seekg(0);
            std::wstring s;
            while (iss >> s) {
                CString word(s.c_str());
                auto iter = current_map->find(word);
                if (iter == current_map->end())
                    current_node = (*current_map)[word] = new GlossaryNode;
                else
                    current_node = iter->second;
                current_map = &current_node->node_map;
            }
            if (current_node)
                current_node->doc_id = id;
        }
    }
}

cdr::GlossaryTree::~GlossaryTree() {
    GlossaryNodeMap::iterator i = node_map.begin();
    while (i != node_map.end()) {
        delete i->second;
        ++i;
    }
}

cdr::ValidationErrors::ValidationErrors(cdr::DOM& dom) {
    current_error = 0;
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
cdr::GlossaryTree* cdr::get_glossary_tree(const CString& language,
                                          const CString& dictionary) {

    // Cache the trees.
    // Make sure the memory gets cleaned up so BoundsChecker is happy.
    struct TreeCache {
        typedef std::map<CString, cdr::GlossaryTree*> Trees;
        ~TreeCache() {
            CString buf;
            for (auto i = trees.begin(); i != trees.end(); ++i) {
                buf.Format(L"deleting %s glossary tree", i->first);
                cdr::trace_log(cdr::cstring_to_utf8(buf).c_str());
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
        cache.trees[key] = new cdr::GlossaryTree(language, dictionary);
        CString buf;
        buf.Format(L"fetched %s glossary tree", key);
        cdr::trace_log(cdr::cstring_to_utf8(buf).c_str());
    }
    return cache.trees[key];
}

static inline unsigned short get_network_short(const unsigned char* buf) {
    return (((unsigned short)buf[0]) << 8) + (unsigned short)buf[1];
}

static inline unsigned short get_little_endian_short(const unsigned char* buf) {
    return (((unsigned short)buf[1]) << 8) + (unsigned short)buf[0];
}

static inline unsigned long get_network_long(const unsigned char* buf) {
    return (((unsigned long)buf[0]) << 24) +
           (((unsigned long)buf[1]) << 16) +
           (((unsigned long)buf[2]) <<  8) +
             (unsigned long)buf[3];
}

// Fills in dim structure with height and width of image if possible.
// We only support the image types stored in the CDR.
bool cdr::get_image_dimensions(CFile& file, ImageDimensions& dim) {

    // Get the first byte, which will give us a clue about which type we have.
    unsigned char buf[256];
    if (file.Read(buf, 1) != 1)
        return false;

    // Try GIF.
    if (buf[0] == 'G') {
        if (file.Read(buf + 1, 9) == 9 && buf[1] == 'I' && buf[2] == 'F') {
            dim.width  = (unsigned long)get_little_endian_short(buf + 6);
            dim.height = (unsigned long)get_little_endian_short(buf + 8);
            return true;
        }
    }

    // Try PNG
    else if (buf[0] == 0x89) {
        if (file.Read(buf, 23) == 23) {
            if (!memcmp(buf, "PNG\r\n\x1a\n", 7)) {
                if (!memcmp(buf + 11, "IHDR", 4)) {
                    dim.width  = get_network_long(buf + 15);
                    dim.height = get_network_long(buf + 19);
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
                dim.height = (unsigned long)get_network_short(buf + 3);
                dim.width  = (unsigned long)get_network_short(buf + 5);
                return true;
            case 0xDA: // SOS (Start of Scan) marker
            case 0xD9: // EOI (End of Image) marker
                return false;
            default:
                if (file.Read(buf, 2) != 2)
                    return false;
                skip = (int)get_network_short(buf) - 2;
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
int cdr::get_audio_seconds(CFile& file) {
    MP3INFO mp3;
    if (getMp3Info(&mp3, file))
        return mp3.seconds;
    return -1;
}

// Assumes text-only content; no mixed-content markup allowed!
bool cdr::replace_element_content(::DOMElement& elem, const CString& value) {

    // Clear out all the child nodes.
    ::DOMNode child = elem.GetFirstChild();
    while (child) {
        ::DOMNode nextChild = child.GetNextSibling();
        ::DOMNode dummy = elem.removeChild(child);
        child = nextChild;
    }

    // Pop in a new text node.
    ::_Document cur_doc = cdr::get_app().GetActiveDocument();
    ::DOMNode text_node = cur_doc.createTextNode(value);
    ::DOMNode dummy = elem.appendChild(text_node);
    return true;
}

// Fetch data from a web service.
CString cdr::fetch_from_url(const CString& url) {
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
    return cdr::utf8_to_cstring(response.c_str());
}

// Figure out where the user's trace log lives.
const char* cdr::get_cdr_trace_log_path() {
    static char* path = 0;
    if (!path) {
        try {
            char* name = "cdr-dll-trace.log";
            CString user_path = cdr::get_user_path();
            size_t extra = 2; // 1 for path separator + 1 for null byte
            size_t len = user_path.GetLength() + strlen(name) + extra;
            const std::string p = cdr::cstring_to_utf8(user_path);
            path = new char[len];
            if (!path)
                return 0;
            sprintf(path, "%s\\%s", p.c_str(), name);
        }
        catch (...) {}
    }
    return path;
}

// String suitable for time-stamping logging entries.
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

// Developer-oriented logging for troubleshooting.
void debug_log(const CString& what, const CString& who) {
    if (who != L"bkline")
        return;
    try {
        FILE* log_file = fopen("c:/tmp/debug.log", "ab");
        static bool warned = true; // false;
        if (!log_file) {
            if (!warned) {
                warned = true;
                ::AfxMessageBox(L"Can't open log file");
            }
            return;
        }
        fprintf(log_file, "%s %s\n", log_timestamp().c_str(),
                cdr::cstring_to_utf8(what).c_str());
        fclose(log_file);
    }
    catch (...) {}
}

// Logging performed for all users.
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
        CString log_data = cdr::utf8_to_cstring(temp.c_str());
        if (log_data.IsEmpty()) {
            return;
        }
        cdr::CommandSet request("CdrSaveClientTraceLog");
        request.child_element(request.command, "LogData", log_data);
        CString response = CdrSocket::send_commands(request);
        if (response.Find(L"success") >= 0)
            _unlink(path);
    }
    catch (...) {}
}

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

cdr::CommandSet::CommandSet(const char* name) : DOM("CdrCommandSet") {
    CString session = CdrSocket::get_session_string();
    if (session.IsEmpty())
        session = "guest";
    child_element(root, "SessionId", session);
    auto wrapper = child_element(root, "CdrCommand");
    command = child_element(wrapper, name);
}

void cdr::CommandSet::add_cdr_document(IXMLDOMElement* parent,
                                       const CString& original) {

    // Generate a new DOM from the serialized original document.
    DOM new_dom(original);

    // Strip the CdrDocCtl block.
    auto doomed = new_dom.find("CdrDocCtl");
    if (doomed) {
        auto new_root = new_dom.get_root();
        Node out;
        if (FAILED(new_root->removeChild(doomed, &out)))
            throw L"removeChild(CdrDocXml) failed";
    }

    // Strip the 'readonly' attributes.
    auto elements = new_dom.find_all("//*[@readonly]");
    CComBSTR name(L"readonly");
    for (auto& element : elements) {
        if (FAILED(element->removeAttribute(name)))
            throw L"removeAttribute(readonly) failed";
    }

    // Create, populate, and append the CdrDocXml element.
    auto child = child_element(parent, "CdrDocXml");
    CString doc_xml = new_dom.get_xml();
    doc_xml.Remove(L'\r');
    CComBSTR bstr(doc_xml);
    CComPtr<IXMLDOMCDATASection> cdata;
    HRESULT hr = this->doc->createCDATASection(bstr, &cdata);
    if (FAILED(hr))
        throw L"createCDATASection failed";

    // Drop the element into the command document.
    append(child, cdata);
}
