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
static CString xml_decode(CString str);
static CString xml_encode(CString str, bool fixQuotes=false);
static std::wostringstream& operator<<(std::wostringstream& os, DOMNode& node);

//////////////////////////////////////////////////////////////////////
///                          INLINE FUNCTIONS
//////////////////////////////////////////////////////////////////////

/**
 * Cast a wide character to a 16-bit unsigned integer.
 *
 * Called by:
 *   cstring_to_utf8()
 *
 * @param c - wide character to be cast
 * @return  - 16-bit unsigned integer value
 */
inline unsigned short char_to_unsigned_short(wchar_t c) {
    return static_cast<unsigned short>(c);
}

/**
 * Extract the 16-bit unsigned integer value from two memory bytes.
 *
 * Called by:
 *   get_image_dimensions()
 *
 * @param buf - pointer to two consecutive memory bytes representing
 *              an unsigned integer in big-endian order (commonly
 *              referred to as "network" order)
 * @return    - 16-bit unsigned integer value
 */
static inline unsigned short get_network_short(const unsigned char* buf) {
    return (((unsigned short)buf[0]) << 8) + (unsigned short)buf[1];
}

/**
 * Extract the 16-bit unsigned integer value from two memory bytes.
 *
 * Called by:
 *   get_image_dimensions()
 *
 * @param buf - pointer to two consecutive memory bytes representing
 *              an unsigned integer in little-endian order
 * @return    - 16-bit unsigned integer value
 */
static inline unsigned short get_little_endian_short(const unsigned char* buf) {
    return (((unsigned short)buf[1]) << 8) + (unsigned short)buf[0];
}

/**
 * Extract the 32-bit unsigned integer value from four memory bytes.
 *
 * Called by:
 *   get_image_dimensions()
 *
 * @param buf - pointer to four consecutive memory bytes representing
 *              an unsigned integer in big-endian order (commonly
 *              referred to as "network" order)
 * @return    - 32-bit unsigned integer value
 */
static inline unsigned long get_network_long(const unsigned char* buf) {
    return (((unsigned long)buf[0]) << 24) +
           (((unsigned long)buf[1]) << 16) +
           (((unsigned long)buf[2]) <<  8) +
             (unsigned long)buf[3];
}


//////////////////////////////////////////////////////////////////////
///                          UTILITY CLASSES
//////////////////////////////////////////////////////////////////////

/**
 * Wrapper around base class, picking up the session ID.
 *
 * This piece of the functionality was factored out in order to be
 * able to test the base class without introducing dependencies in
 * the test harness on the "Socket" class and its dependencies.
 *
 * @param name - string for the name of the specific CDR command
 */
cdr::CommandSet::CommandSet(const char* name) :
    CommandSetBase(name, Socket::get_session_string()) {
}

/**
 * Clean up resources used by a `GlossaryTree` object.
 */
cdr::GlossaryTree::~GlossaryTree() {
    GlossaryNodeMap::iterator i = node_map.begin();
    while (i != node_map.end()) {
        delete i->second;
        ++i;
    }
}

/**
 * Fetch glossary information from the CDR server.
 *
 * Called by:
 *   cdr::GlossaryTrees::get_glossary_tree()
 *
 * @param language   - "es" or "en"
 * @param dictionary - optional string for restricting the terms retrieved
 *                     to those used by a specific dictionary (e.g., Genetics)
 * @param audience   - optional string for restricting the terms retrieved
 *                     to those intended for a particular audience (e.g.,
 *                     Patient)
 */
cdr::GlossaryTree::GlossaryTree(const CString& language,
                                const CString& dictionary,
                                const CString& audience) {

    // Prepare the command we'll send to the CDR server.
    char* tag = "CdrGetGlossaryMap";
    if (language == L"es")
        tag = "CdrGetSpanishGlossaryMap";
    cdr::CommandSet request(tag);
    if (!dictionary.IsEmpty())
        request.child_element(request.command, "Dictionary", dictionary);
    if (!audience.IsEmpty())
        request.child_element(request.command, "Audience", audience);

    // Walk through all the `Term` elements in the server's response.
    CString response_xml = cdr::Socket::send_commands(request);
    cdr::DOM dom(response_xml);
    auto terms = dom.find_all("//Term");
    for (auto& term : terms) {
        int id = (int)get_doc_no(dom.get(term, "id").GetString());
        CString name = dom.get_text(dom.find("Name", term));
        names[id] = name;
        auto phrases = dom.find_all("Phrase", term);
        for (auto& phrase : phrases) {

            // It's not the most obvious solution, but the extraction
            // operator of the standard streams does exactly what we need
            // by default for tokenizing words on whitespace.
            std::wistringstream iss(dom.get_text(phrase).GetString());
            GlossaryNodeMap* current_map = &node_map;
            GlossaryNode* current_node = nullptr;
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

            // Only the last word in the phrase gets the term document's ID.
            if (current_node)
                current_node->doc_id = id;
        }
    }
}

/**
 * Static cache of glossary tree maps.
 */
cdr::GlossaryTrees::Cache cdr::GlossaryTrees::cache;

/**
 * Keep BoundsChecker happy by cleaning up after ourselves.
 */
cdr::GlossaryTrees::~GlossaryTrees() {
    CString buf;
    for (auto i = cache.begin(); i != cache.end(); ++i) {
        buf.Format(L"deleting %s glossary tree", i->first);
        cdr::trace_log(cdr::cstring_to_utf8(buf).c_str());
        delete i->second;
    }
}

/**
 * Find or load and cache one of the glossary term trees.
 *
 * Called by:
 *   CGlossify::OnInitDialog()
 *   CGlossify::find_next_match()
 *
 *  @param language   - en or es
 *  @param dictionary - optional string for limiting tree
 *                      to terms for a specific dictionary
 *  @param audience   - optional string for limiting tree
 *                      to terms for a specific audience
 *
 * Return:
 *   address of the matching glossary term tree
 */
cdr::GlossaryTree* cdr::GlossaryTrees::get_glossary_tree(
    const CString& language,
    const CString& dictionary,
    const CString& audience
) {

    // Fetch the tree if we don't already have it.
    // No need for locking; we'll be called in a single thread.
    CString key;
    key.Format(L"%s-%s-%s", language, dictionary, audience);
    if (cache.count(key) == 0) {
        cache[key] = new GlossaryTree(language, dictionary, audience);
        CString buf;
        buf.Format(L"fetched %s glossary tree", key);
        cdr::trace_log(cdr::cstring_to_utf8(buf).c_str());
    }
    return cache[key];
}

/**
 * Login token obtained from the CDR server.
 */
CString cdr::Socket::session_string;

/**
 * DNS names for CDR server hosts.
 */
CString cdr::Socket::cdr_host;
CString cdr::Socket::api_host;

/**
 * Name for CDR server host's CBIIT tier (e.g., PROD, DEV).
 */
CString cdr::Socket::tier;

/**
 * Send a client request to the CDR Server.
 *
 * Called extensively, including by every method invoking a CDR client-
 * server API command.
 *
 *  @param commands - DOM object for the XML command set to be submitted
 *  @param blob     - optional bytes for a media attachment
 *
 *  @return           serialized XML for the server's response
 */
CString cdr::Socket::send_commands(const cdr::CommandSet& commands,
                                   char* blob) {
    try {

        CWaitCursor wc;

        // Serialize the command set.
        cdr::debug_log("top of send_commands()");
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

        // Open an HTTPS connection to the CDR API tunneling wrapper.
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
        if (!success)
            throw L"Failure submitting request to server";

        // Make sure the server thinks we succeeded.
        cdr::debug_log("request sent successfully");
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
 * Object to ensure proper cleanup at shutdown time.
 */
cdr::Socket::Init cdr::Socket::Init::init;

/**
 * Initialize the Winsock package and figure out which tier we're talking to.
 *
 * Invoked for the singleton immediately above.
 */
cdr::Socket::Init::Init()
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
cdr::Socket::Init::~Init() {
    WSACleanup();
}

/**
 * Extract the validation errors from `Errors/Err` elements in the response.
 *
 * Called by:
 *   CCommands::save()
 *   CCommands::validate()
 *
 * @param dom - parsed response from the CDR server.
 */
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

/*
 * Map of open document to validation errors (mapped by doc path).
 */
cdr::ValidationErrorSets cdr::validation_error_sets;


//////////////////////////////////////////////////////////////////////
///                      COMMON UTILITY FUNCTIONS
//////////////////////////////////////////////////////////////////////

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 *
 * Called by:
 *   cdr::Socket::Init()
 *   cdr::debug_log()
 *   cdr::get_cdr_trace_log_path()
 *   cdr::GlossaryTrees::get_glossary_tree()
 *   cdr::GlossaryTrees::~GlossaryTrees()
 *   cdr::Socket::send_commands()
 *   CCommands::launchBlob()
 *   open_doc() in Commands.cpp
 *
 * @param str - Unicode string to be converted
 * @return    - UTF-8 encoding of the caller's string
 */
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
 * Log developer-oriented information useful for troubleshooting.
 *
 * Called by various places throughout the code, changing as
 * dictated by what needs to be debugged at any given moment.
 *
 * @param what - string for the information being logged
 * @param who  - if set to a user other than the current user, do nothing
 */
void cdr::debug_log(const CString& what, const CString& who) {
    if (!who.IsEmpty() && who != L"bkline")
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

/**
 * Create the canonical form of a CDR document ID.
 *
 * Called by:
 *   CSearchDialog::OnVersionsButton()
 *   CCommands::doRetrieve()
 *
 * @param id - integer for the unique document ID
 * @return   - string version of the ID, in the form "CDR0000012345"
 */
CString cdr::doc_id_string(int id) {
    wchar_t buf[40];
    swprintf(buf, L"CDR%010d", id);
    return buf;
}

/**
 * Pulls out the document's type, title, and ID from its XML representation.
 *
 * Called by:
 *   CCommands::checkIn()
 *   CCommands::edit()
 *   CCommands::save()
 *   CCommands::validate()
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
 * Extracts and concatenates the text content for an element.
 *
 * Called by:
 *   CGlossify::CGlossify()
 *   cdr::extract_ctl_info()
 *   is_spanish_summary() in Commands.cpp
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
 * Create a `CdrLinkInfo` object using information parsed from a string.
 *
 * Called by:
 *   COrgLocs::OnOK()
 *   CCommands::doInsertLink()
 *   CEditElement::insert_org_location()
 *
 * @param str - information in the form "[id] text-content"
 * @return    - object with `target` and `data` members
 */
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

/**
 * Extracts document information from the XML containing the CDR
 * server's response.
 *
 * Called by:
 *   CEditElement::OnOK()
 *   CSearchDialog::OnSearchButton()
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
 * Fetch data from a web service.
 *
 * Called by:
 *   CCommands::fetchFromUrl()
 *
 * @param url - string for the service's end point
 * @return    - string returned by the service
 */
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

/**
 * Populates the caller's list box object with strings drawn from the query
 * result information passed in.
 *
 * Called by:
 *   CEditElement::OnOK()
 *   COrgLocs::OnInitDialog()
 *   CSearchDialog::OnSearchButton()
 *   CSearchDialog::OnInitDialog()
 *
 *  @param  list_box        reference to caller's list box, to which
 *                          we add strings identifying each document
 *                          in the server's response.
 *  @param  doc_set         reference to list of SearchResult objects.
 *  @return                 number of strings added to list box, or -1
 *                          in the event of an error.
 */
int cdr::fill_list_box(CListBox& list_box, const DocSet& doc_set) {

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
 * Find a node by name in the document selection, or create one if not found.
 *
 * Called by:
 *   CCommands::getOrgAddress()
 *
 * @param parent    - `Range` object from XMetaL's DOM API
 * @param elem_name - string for the desired element's tag name
 * @return          - `Range` object for the found or created element
 *                    (empty if the element isn't allowed in this location)
 */
::Range cdr::find_or_create_child(::Range parent, const CString& elem_name) {

    // Try to find an existing occurrence first.
    parent.SelectContainerContents();
    ::Range child = parent.GetDuplicate();
    child.Collapse(1);
    if (child.MoveToElement(elem_name, TRUE)) {
        if (parent.GetContains(child, FALSE))
            return child;
    }

    // Didn't find one; try to create a new one.
    parent.Collapse(1);
    if (parent.FindInsertLocation(elem_name, TRUE)) {
        parent.InsertElement(elem_name);
        return parent;
    }

    // Bust. Can't find *or* create the element!
    return ::Range();
}

/**
 * Obtains an Automation dispatch object for the running XMetaL application.
 *
 * Called from many methods throughout the code base.
 *
 *  @return             new object to be used for invoking application-
 *                      level XMetaL methods.
 */
_Application cdr::get_app()
{
    cdr::debug_log("Top of getApp()");
    _Application app;
    CWinApp* win_app = ::AfxGetApp();
    if (!win_app->m_pMessageFilter) {
        win_app->m_pMessageFilter = new COleMessageFilter();
        win_app->m_pMessageFilter->Register();
    }
    win_app->m_pMessageFilter->SetMessagePendingDelay(MESSAGE_PENDING_DELAY);
    try {
        COleException e;
        cdr::debug_log("Before CreateDispatch()");
        if (app.CreateDispatch(L"XMetaL.Application", &e)) {
            cdr::debug_log("After CreateDispatch()");
            return app;
        }
        cdr::debug_log("After after CreateDispatch()");
        e.ReportError();
    }
    catch (CException *ee) {
        cdr::debug_log("Caught exception in cdr::getApp()\n");
        ee->ReportError();
        cdr::debug_log("Reported exception in cdr::getApp()\n");
        ee->Delete();
    }
    throw L"Unable to create XMetaL Application-level automation object";
}

/**
 * Parse beginning of mp3 file to determine the duration in seconds.
 *
 * Called by:
 *   insert_audio_seconds() in Commands.cpp
 *
 * @param file - reference to `CFile` object to be read
 * @return     - run-time seconds if successful, otherwise -1
 */
int cdr::get_audio_seconds(CFile& file) {
    MP3INFO mp3;
    if (getMp3Info(&mp3, file))
        return mp3.seconds;
    return -1;
}

/**
 * Figure out where the user's trace log lives.
 *
 * Called by:
 *   cdr::send_trace_log()
 *   cdr::trace_log()
 *
 * @return  - address of static c-style string with the full log file path
 */
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

/**
 * Extracts document number from CDR ID string, which is generally
 * in the form "CDR\d\d\d\d\d\d\d\d\d\d".
 *
 * Called by:
 *   cdr::GlossaryTree::GlossaryTree()
 *   CSearchDialog::OnVersionsButton()
 *   CCommands::doRetrieve()
 *   CCommands::launchBlob()
 *   open_doc() in Commands.cpp
 *   remove_doc() in Commands.cpp
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
 * Find a parent element of the current editing location by name.
 *
 * Called by:
 *   CCommands::getOrgAddress()
 *
 * @param elem_name - string naming the element we're looking for
 * @return          - `Range` object from the XMetaL DOM API for the
 *                    sought element (empty if not found)
 */
::Range cdr::get_elem_range(const CString& elem_name) {
    // Find out where we are.
    ::_Document active_doc = get_app().GetActiveDocument();
    ::Range rng = active_doc.GetRange();

    // Make sure what we find is an ancestor of the current element.
    if (!rng.GetIsParentElement(elem_name))
        return ::Range();

    // Move.
    if (!rng.MoveToElement(elem_name, FALSE))
        return ::Range();

    return rng;
}

/**
 * Determine the width and height of the image stored in a file.
 *
 * We only support the image types stored in the CDR (GIF, PNG, and JPEG).
 *
 * Called by:
 *   cdr::insert_image_dimensions()
 *
 * @param file - open `CFile` object from which the file's bytes can be read
 * @param dim  - `ImageDimensions` object to be populated
 * @return     - `true` if we were successful; otherwise `false`
 */
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

/**
 * Finds the user-specific location where client files for the application
 * are stored.
 *
 * Called by:
 *   cdr::get_cdr_trace_log_path()
 *   CCommands::get_userPath()
 *   CCommands::launchBlob()
 *   load_doc_types() in Commands.cpp
 *   CCommands::logon()
 *   open_doc() in Commands.cpp
 *   remove_doc() in Commands.cpp
 *
 *  @return             reference to string containing location for client
 *                      files.
 */
const CString& cdr::get_user_path() {
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
 * Finds the location where the currently running XMetaL application is
 * installed.
 *
 * Called by:
 *   cdr::get_user_path()
 *
 *  @return             reference to string containing path for base XMetaL
 *                      folder.
 */
const CString& cdr::get_xmetal_path() {
    static CString xmetal_path;
    if (xmetal_path.IsEmpty()) {
        _Application app = get_app();
        if (app)
            xmetal_path = app.GetPath();
    }
    return xmetal_path;
}

/**
 * Replace the text content of an element.
 *
 * Assumes text-only content; no mixed-content markup allowed!
 *
 * Called by:
 *   replace_audio_seconds() in Commands.cpp
 *   replace_image_dimensions() in Commands.cpp
 *
 * @param elem  - reference to `DOMElement` from the XMetaL DOM API
 * @param value - replacement text content
 * @return      - true
 */
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

/**
 * Pack up the user's trace log, send it to the CDR server, and drop the file.
 *
 * Called by:
 *   cdr::trace_log()
 */
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
        CString response = cdr::Socket::send_commands(request);
        if (response.Find(L"success") >= 0)
            _unlink(path);
    }
    catch (...) {}
}

/**
 * Serialize a document from XMetaL's DOM.
 *
 * This is necessary because of bugs in the XMetaL implementation of the
 * document object's `xml` property, which (at least in the C++ `GetXml()`
 * version) mangles whitespace inside text nodes.
 *
 * Called by:
 *  CCommands::save()
 *  CCommands::validate()
 *
 * @param doc - pointer to current XMetaL document
 * @return    - serialization of the document
 */
CString cdr::serialize(_Document* doc) {
    std::wostringstream os;
    DOMNode root = doc->GetDocumentElement();
    os << root;
    CString xml(os.str().c_str());
    return xml;
}

/**
 * Show errors returned in the server's response.
 *
 * Typical use:
 *
 *       CString response_xml = cdr::Session::send_commands(request);
 *       cdr::DOM response(response_xml);
 *       if (!show_erors(response) {
 *           process_the(response);
 *       }
 *
 * Invoked extensively throughout the code base.
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

/**
 * Open Internet Explorer and navigate to the caller's URL.
 *
 * Yes, it is strange that we're launching an unsupported browser.
 * This feature was originally implemented when IE had around 95%
 * of the browser market share, so with all its flaws, we didn't
 * have a lot of good options. We have explored (ha-ha) revisiting
 * this decision with the users, but so far they have insisted that
 * at least for now, we'll stick with what they've been using.
 *
 * Called by:
 *   CCommands::showPage()
 *
 * @param url - string for the address of the requested page
 * @return    - EXIT_SUCCESS
 */
int cdr::show_page(const CString& url) {
    CString ie = L"\"%ProgramFiles%\\Internet Explorer\\iexplore.exe\"";
    CString command = L"\"" + ie + L" \"" + url + L"\"\"";
    _wsystem(command);
    return EXIT_SUCCESS;
}

/**
 * Log high-level information about each command the user invokes.
 *
 * Invoked by almost every command exposed by the DLL publicly.
 *
 * @param what - identification of the action being logged
 */
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

/**
 * Strips leading and trailing whitespace from the caller's string.
 *
 * Called by:
 *   cdr::extract_ctl_info()
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
 * Converts string from UTF-8 to UTF-16.  Ignores values beyond U+FFFF.
 *
 * Called by:
 *   cdr::fetch_from_url()
 *   load_doc_types() in Commands.cpp
 *   cdr::Socket::send_commands()
 *   cdr::send_trace_log()
 *
 * @param s - UTF-8 byte string to be converted
 * @return  - decoded Unicode string
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


//////////////////////////////////////////////////////////////////////
///                        LOCAL HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////

/**
 * Packs up a string containing an error message inside the XML structure
 * appropriate for simulating a buffer returned by the CDR server, in the
 * event of a failure to communicate with the server.
 *
 * Called by:
 *   cdr::Socket::send_commands()
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
 * Test a candidate path to determine whether it can be used to store
 * client files for our application.
 *
 * Called by:
 *   cdr::get_user_path()
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
 * Create a string suitable for time-stamping logging entries.
 *
 * Called by:
 *   cdr::debug_log()
 *   cdr::trace_log()
 *
 * @return - string in the form YYYY-MM-DD MM:HH:SS.sss
 */
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

/**
 * Reverses the XML encoding process, replacing builtin entity
 * references with the corresponding characters.
 *
 * Called by:
 *   operator<<() below
 *
 *  @param  str         caller's string object to be modified in place.
 *  @return             copy of modified string.
 */
CString xml_decode(CString str) {
    str.Replace(L"&amp;", L"&");
    str.Replace(L"&lt;", L"<");
    str.Replace(L"&gt;", L">");
    str.Replace(L"&quot;", L"\"");
    str.Replace(L"&apos;", L"'");
    return str;
}

/**
 * Alters the caller's string in place, making it suitable to
 * serve as XML text content, replacing reserved characters with
 * their built-in entity reference equivalents.
 *
 * Called by:
 *   operator<<() below
 *
 *  @param  str         caller's string object to be modified in place.
 *  @param  fixQuotes   <code>true</code> iff single- and double-quote
 *                      marks should be replaced; otherwise <code>false</code>
 *                      (the default).
 *  @return             copy of modified string.
 */
CString xml_encode(CString str, bool fixQuotes) {
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
 * Writes the string equivalent of the XML tree represented by the caller's
 * DOM node.
 *
 * Called by:
 *   cdr::get_xml()
 *
 *  @param  os              reference to output stream on which to write
 *                          the XML string.
 *  @param  node            reference to the DOM node to be written out.
 *  @return                 reference to output stream.
 */
std::wostringstream& operator<<(std::wostringstream& os, DOMNode& node) {

    // Obtain some local copies of the node's properties.
    int node_type = node.GetNodeType();
    CString name = node.GetNodeName();

    // Swallow the CdrDocCtl element.
    if (node_type == 1 && name != L"CdrDocCtl") {

        // Element node.  Output the start tag.
        os << L"<" << (LPCWSTR)name;
        DOMNamedNodeMap attrs = node.GetAttributes();
        int n = attrs.GetLength();
        for (int i = 0; i < n; ++i) {
            DOMNode attr = attrs.item(i);
            CString attr_name = attr.GetNodeName();
            if (attr_name != L"readonly") {
                CString val = attr.GetNodeValue();

                // OK, this is bizarre, but necessary because of a strange
                // pair of bugs in XMetaL.  XXX This runs the risk of
                // stepping on the intentions of the user, in the rare
                // (probably so rare that it will never happen) case in
                // which she really wants to end up with an EntityRef as
                // the _value_ (not just the representation) of the
                // attribute.  No way around this problem until the vendor
                // fixes the bugs.  When that happens, take out the
                // call to xml_decode() here and things will work the
                // way they should in _all_ cases.
                os << L" " << (LPCWSTR)attr_name << L"='"
                   << (LPCWSTR)xml_encode(xml_decode(val), true) << L"'";
            }
        }
        if (!node.hasChildNodes())
            os << L"/";
        os << L">";
    }

    // If this is a text node (type 3) pump out the characters.
    else if (node_type == 3) {

        CString val = node.GetNodeValue();
        os << (LPCWSTR)xml_encode(val);
    }

    // Handle processing instructions.
    else if (node_type == 7) {

        CString val = node.GetNodeValue();
        os << L"<?" << (LPCWSTR)name << L" " << (LPCWSTR)val << L"?>";
    }

    // Don't lose comments.
    else if (node_type == 8) {

        CString val = node.GetNodeValue();
        os << L"<!--" << (LPCWSTR)val << L"-->";
    }

    // Process any children of the node.
    if (node.hasChildNodes() && name != "CdrDocCtl") {
        DOMNode n = node.GetFirstChild();
        os << n;

        // If this is an element node, write the closing tag.
        if (node_type == 1)
            os << L"</" << (LPCWSTR)name << L">";
    }

    // Continue with this node's siblings
    DOMNode sibling = node.GetNextSibling();
    if (sibling)
        os << sibling;
    return os;
}
