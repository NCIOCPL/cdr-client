/*
 * $Id: CdrUtil.cpp,v 1.25 2004-09-09 18:43:03 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.24  2004/02/26 01:57:25  bkline
 * Cleared out some experimental/debugging dross.
 *
 * Revision 1.23  2004/02/26 01:45:53  bkline
 * Added glossifier support.
 *
 * Revision 1.22  2004/02/26 00:46:33  bkline
 * Added code for suppressing/expanding leading zeros in document IDs.
 *
 * Revision 1.21  2003/03/05 12:41:50  bkline
 * Added workaround for XMetaL entity encoding bugs in attributes.
 *
 * Revision 1.20  2003/01/23 17:21:43  bkline
 * Eliminated some dead code.
 *
 * Revision 1.19  2002/12/24 15:04:15  bkline
 * Switched from DDE to ActiveX Automation for showPage().
 *
 * Revision 1.18  2002/10/16 19:56:26  bkline
 * Workaround for XMetaL automation bug.
 *
 * Revision 1.17  2002/10/15 22:22:05  bkline
 * Adding code for issue #471.
 *
 * Revision 1.16  2002/10/14 20:06:22  bkline
 * Added DDE replacement for SoftQuad's ShowPage().
 *
 * Revision 1.15  2002/10/04 16:42:42  bkline
 * Added my own showPage method, to get around the buggy version in XMetaL.
 *
 * Revision 1.14  2002/07/30 21:37:36  bkline
 * Fixed problem with & in DocTitle; removed hard tabs inserted by Visual
 * Studio.
 *
 * Revision 1.13  2002/07/26 20:30:15  bkline
 * Added wait cursor to sendCommand().
 *
 * Revision 1.12  2002/07/18 00:51:37  bkline
 * Added cdr::decode().
 *
 * Revision 1.11  2002/07/05 18:57:59  bkline
 * Masked out 'readonly' attributes.
 *
 * Revision 1.10  2002/06/13 18:48:47  bkline
 * Added hostname property.
 *
 * Revision 1.9  2002/04/29 10:57:30  bkline
 * Added code to preserve XML comments.
 *
 * Revision 1.8  2002/04/12 01:32:25  bkline
 * Fixed bug in PI handling.  Added CDR_HOST and CDR_PORT environment
 * variable overrides.
 *
 * Revision 1.7  2002/02/12 21:44:05  bkline
 * Replaced mmdb2 with mmdb2.nci.nih.gov.
 *
 * Revision 1.6  2002/02/08 18:53:27  bkline
 * Fixed typos in last change.
 *
 * Revision 1.5  2002/02/08 14:28:32  bkline
 * Added code to handle empty element tags.
 *
 * Revision 1.4  2001/11/27 14:18:57  bkline
 * New utility methods; modified extraction methods.
 *
 * Revision 1.3  2001/06/09 12:31:51  bkline
 * Switched to Unicode strings; added more sophisticated XML parsing.
 *
 * Revision 1.2  2001/04/18 14:43:55  bkline
 * Added insertion operator for DOM node.
 *
 * Revision 1.1  2000/10/16 22:29:27  bkline
 * Initial revision
 */

// Local headers.
#include "stdafx.h"
#include "CdrUtil.h"

// System headers.
#include <map>
#include <set>
#include <fstream>

// Implement our own command to show an HTML page.
// #define SHOW_PAGE_WITH_DDE /* Use ActiveX Automation instead. */
#ifdef SHOW_PAGE_WITH_DDE
#include <ddeml.h>
#endif

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local support functions.
static CString errResponse(const CString& err);

/**
 * Login token obtained from the CDR server.
 */
CString CdrSocket::sessionString;

/**
 * DNS name for CDR server host.
 */
CString CdrSocket::hostName;

/**
 * Object to ensure proper cleanup at shutdown time.
 */
CdrSocket::Init CdrSocket::Init::init;

/**
 * Initializes the Winsock package.
 */
CdrSocket::Init::Init()
{
    if (WSAStartup(0x0101, &wsaData) != 0) {
        ::AfxMessageBox(_T("Unable to initialize Windows socket library"));
        throw _T("Failure initializing Windows socket library");
    }
}

/**
 * Performs cleanup of the Winsock package.
 */
CdrSocket::Init::~Init()
{
    WSACleanup();
}

/**
 * Creates a socket and connects to the CDR server.
 *
 *  @exception  const char*  if a network error is encountered.
 */
CdrSocket::CdrSocket()
{
    const char* hostEnv = getenv("CDR_HOST");
    const char* portEnv = getenv("CDR_PORT");
    const char* host = hostEnv ? hostEnv : "mahler.nci.nih.gov";
    hostName = host;
    int port = portEnv ? atoi(portEnv) : CDR_SOCK;

    // Working variables.
    struct sockaddr_in  addr;
    struct hostent *    ph = gethostbyname(host);
    if (!ph)
        throw _T("Failure resolving host name");

    // Build the socket address.
    addr.sin_family = ph->h_addrtype;
    memcpy(&addr.sin_addr, ph->h_addr, ph->h_length);
    addr.sin_port = htons(port);

    // Create the socket.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw _T("Failure creating socket");

    // Connect to the server.
    if (connect(sock, (struct sockaddr *)&addr, sizeof addr) < 0)
        throw _T("Failure connecting to CDR server");
}

/**
 * Sends an API command to the CDR server and reads the server's response.
 * The command is wrapped in a <code>CdrCommandSet</code> element prior to
 * submission.
 *
 *  @param  cmd             reference to string object containing the command.
 *  @return                 string object containing the server's response.
 *  @exception  const char* if a communications error is encountered.
 */
CString CdrSocket::sendCommand(const CString& cmd, bool guest) 
{
    try {

        CWaitCursor wc;

        // Wrap the command in a CdrCommandSet element.
        CString request = _T("<CdrCommandSet>");
        if (!sessionString.IsEmpty())
            request += _T("<SessionId>") + sessionString + _T("</SessionId>");
        else if (guest)
            request += _T("<SessionId>guest</SessionId>");
        request += _T("<CdrCommand>") + cmd 
            + _T("</CdrCommand></CdrCommandSet>");

        // Connect to the server.
        CdrSocket cdrSocket;

        // Tell the server the size of the coming request buffer.
        std::string buf = cdr::cStringToUtf8(request);
        long len = htonl(buf.length());
        if (send(cdrSocket.sock, (char *)&len, sizeof len, 0) < 0)
            throw _T("Failure sending command length");

        // Submit the command to the server.
        if (send(cdrSocket.sock, buf.c_str(), buf.length(), 0) < 0)
            throw _T("Failure sending command");

        // Retrieve the server's response.
        std::string response = cdrSocket.read();
        return cdr::utf8ToCString(response.c_str());
    }
    catch (LPCTSTR error) { return errResponse(error); }
}

/**
 * Reads a response buffer from the CDR server.
 *
 *  @return                 string object containing the server's response.
 */
std::string CdrSocket::read() 
{
    // Find out how many bytes the response contains.  This solves the
    // "how do we know we're done?" problem.
    size_t totalRead = 0;
    char lengthBytes[4];
    while (totalRead < sizeof lengthBytes) {
        int leftToRead = sizeof lengthBytes - totalRead;
        int bytesRead = recv(sock, lengthBytes + totalRead, leftToRead, 0);
        if (bytesRead < 0)
            throw _T("Failure reading byte count from server");
        totalRead += bytesRead;
    }
    long length;
    memcpy(&length, lengthBytes, sizeof length);
    length = ntohl(length);

    // Use a local buffer type to ensure memory release even if an
    // exception occurs.
    struct Buf { 
        Buf(size_t n) : buf(new char[n + 1]) { memset(buf, 0, n + 1); }
        ~Buf() { delete [] buf; }
        char* buf;
    };
    Buf b(length);

    // Read until we have all the bytes we've been promised.
    char* buf = b.buf;
    int recd = 0;
    while (recd < length) {
        int n = recv(sock, buf + recd, length - recd, 0);
        if (n > 0)
            recd += n;
        else if (n < 0)
            throw _T("Failure reading reply from server");
    }
    return buf;
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
    _Application app;
    try {
        COleException e;
        if (app.CreateDispatch(_T("XMetaL.Application"), &e))
            return app;
    }
    catch (CException *e) {
        e->ReportError();
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
CString cdr::getXmetalPath() 
{
    static CString xmetalPath;
    if (xmetalPath.IsEmpty()) {
        _Application app = getApp();
        if (app)
            xmetalPath = app.GetPath();
    }
    return xmetalPath;
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
CString cdr::encode(CString str, bool fixQuotes)
{
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
 * Reverses the XML encoding process, replacing builting entity
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
unsigned long cdr::getDocNo(const CString& docString)
{
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
CString cdr::extractElementText(DOMNode node)
{
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
CString cdr::trim(const CString& s)
{
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
void cdr::extractCtlInfo(DOMNode node, CdrDocCtrlInfo& info)
{
    // Initialize flags to defaults.
    info.readyForReview = false;

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
CString errResponse(const CString& err)
{
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
                                      DOMNode& node)
{
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

std::string cdr::cStringToUtf8(const CString& str)
{
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
CString cdr::utf8ToCString(const char* s)
{
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

CString cdr::Element::getAttribute(const CString& name) const
{
    Attrs::const_iterator i = attrs.find(name);
    if (i == attrs.end())
        return CString();
    else
        return i->second;
}

cdr::Element cdr::Element::extractElement(const CString& s,
                                          const CString& name,
                                          int pos)
{
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

CString cdr::Element::getCdataSection() const
{
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

CdrLinkInfo cdr::extractLinkInfo(const CString& str)
{
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

::Range cdr::getElemRange(const CString& elemName)
{
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

::Range cdr::findOrCreateChild(::Range parent, const CString& elemName)
{
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

CString cdr::docIdString(int id)
{
    TCHAR buf[40];
    swprintf(buf, _T("CDR%010d"), id);
    return buf;
}

CString cdr::suppressLeadingZeros(const CString& s)
{
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

CString cdr::expandLeadingZeros(const CString& s)
{
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
#ifdef SHOW_PAGE_WITH_DDE
static HDDEDATA ddeCallback(UINT type, UINT fmt, HCONV conv, 
                            HSZ str1, HSZ str2,
                            HDDEDATA data, DWORD data1, DWORD data2)
{
    return NULL;
}

int cdr::showPage(const CString& url)
{
    // Initial assumptions about where the browser is.
    const char* ie  = "c:\\Program Files\\Internet Explorer\\IEXPLORE.EXE";
    const char* app = ie;

    // Put together the DDE command.
    std::string cmdStr = "\"" + cStringToUtf8(url) + "\",,-1,,,,,";
    const char* cmd = cmdStr.c_str();
    size_t len = strlen(cmd) + 1;

    // Prepare the DDE variables.
    DWORD instance = 0;
    HCONV conv     = 0;
    DWORD flags    = APPCLASS_STANDARD | APPCMD_CLIENTONLY;

    // Initialize DDE.
    UINT rc = DdeInitialize(&instance, (PFNCALLBACK)&ddeCallback, flags, 0);
    if (rc != DMLERR_NO_ERROR)
        return EXIT_FAILURE;

    // Connect to the service.
    HSZ service = DdeCreateStringHandle(instance, L"IExplore", 0);
    HSZ topic   = DdeCreateStringHandle(instance, L"WWW_OpenURL", 0);
    conv = DdeConnect(instance, service, topic, NULL);
    if (!conv) {
        WinExec(app, SW_SHOWMINNOACTIVE);
        conv = DdeConnect(instance, service, topic, NULL);
    }

    // Clean up.
    DdeFreeStringHandle(instance, service);
    DdeFreeStringHandle(instance, topic);

    // Bring up the URL.
    if (conv) {
        DWORD dummy = 0;
        LPBYTE vCmd = (LPBYTE)cmd;
        DdeClientTransaction(vCmd, len, conv, 0, 0, XTYP_EXECUTE, 2000, &dummy);
        DdeDisconnect(conv);
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}

#else

// This version uses ActiveX Automation instead of DDE, 
// to get around a bug in Internet Explorer's DDE code.
int cdr::showPage(const CString& url)
{
    COleDispatchDriver ie;
    if (!ie.CreateDispatch(_T("InternetExplorer.Application"))) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
            MB_ICONEXCLAMATION);
        return EXIT_FAILURE;
    }
    DISPID dispid;
    OLECHAR* member = _T("Navigate");
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL, 
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        ::AfxMessageBox(_T("Unable to launch Internet Explorer"),
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

cdr::GlossaryTree::GlossaryTree() {
    CString response = CdrSocket::sendCommand(_T("<CdrGetGlossaryMap/>"),
                                              true);
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
                    CString msg;
                    msg.Format(L"tree word '%s'", word);
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

// static cdr::GlossaryTree* glossaryTree;
cdr::GlossaryTree* cdr::getGlossaryTree() {

    // Make sure the memory gets cleaned up so BoundsChecker is happy.
    struct GlossaryTreeWrapper {
        GlossaryTreeWrapper() : tree(0) {}
        ~GlossaryTreeWrapper() { if (tree) delete tree; }
        cdr::GlossaryTree* tree;
    };
    static GlossaryTreeWrapper wrapper;

    // No need for locking; we'll be called in a single thread.
    if (!wrapper.tree)
        wrapper.tree = new cdr::GlossaryTree;
    return wrapper.tree;
}
