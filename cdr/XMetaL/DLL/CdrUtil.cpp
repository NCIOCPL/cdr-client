/*
 * $Id: CdrUtil.cpp,v 1.6 2002-02-08 18:53:27 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
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

// Prevent annoying warning from compiler about Microsoft's own bugs.
#pragma warning(disable : 4503)

// Local support functions.
static CString errResponse(const CString& err);

/**
 * Login token obtained from the CDR server.
 */
CString CdrSocket::sessionString;

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
    // Working variables.
    struct sockaddr_in  addr;
    struct hostent *    ph = gethostbyname("mmdb2");
    if (!ph)
        throw _T("Failure resolving host name");

    // Build the socket address.
    addr.sin_family = ph->h_addrtype;
    memcpy(&addr.sin_addr, ph->h_addr, ph->h_length);
    addr.sin_port = htons(CDR_SOCK);

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
CString CdrSocket::sendCommand(const CString& cmd) 
{
    try {

        // Wrap the command in a CdrCommandSet element.
        CString request = _T("<CdrCommandSet>");
        if (!sessionString.IsEmpty())
            request += _T("<SessionId>") + sessionString + _T("</SessionId>");
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
            CString str = _T("[") + id + _T("] ") + title;
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
    // Get type from doc element name
	info.docType = node.GetNodeName();

    // Rest is in CdrDocCtl, a child of the doc element.
    node = node.GetFirstChild();
	while (node) {

        // Look for an element.
        if (node.GetNodeType() == 1) {

            // If CdrDocCtl, walk through its child nodes.
            if (node.GetNodeName() == _T("CdrDocCtl")) {
                node = node.GetFirstChild();
                while (node) {

                    // Only interested in elements (type 1).
                    if (node.GetNodeType() == 1) {
                        CString name = node.GetNodeName();
                        if (name == _T("DocTitle"))
                            info.docTitle = extractElementText(node);
                        else if (name == _T("DocId"))
                            info.docId = cdr::trim(extractElementText(node));
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
			CString val = attr.GetNodeValue();
			os << _T(" ") << (LPCTSTR)attrName << _T("='")
               << (LPCTSTR)cdr::encode(val, true) << _T("'");
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
	else if (nodeType == 9) {

		CString val = node.GetNodeValue();
		os << _T("<?") << (LPCTSTR)name << _T(" ") << (LPCTSTR)val << _T("?>");
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
    /*
    while (rng && rng.GetElementName(0) != elemName) {
        rng.SelectContainerContents();
        rng.Collapse(1);
        rng.MoveLeft(0);
    }
    */
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
