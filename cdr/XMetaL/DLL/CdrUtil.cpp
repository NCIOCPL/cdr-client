/*
 * $Id: CdrUtil.cpp,v 1.2 2001-04-18 14:43:55 bkline Exp $
 *
 * Common utility classes and functions for CDR DLL used to customize XMetaL.
 *
 * $Log: not supported by cvs2svn $
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
static std::string errResponse(const char* err);

/**
 * Login token obtained from the CDR server.
 */
std::string CdrSocket::sessionString;

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
        ::AfxMessageBox("Unable to initialize Windows socket library");
        throw "Failure initializing Windows socket library";
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
        throw "Failure resolving host name";

    // Build the socket address.
    addr.sin_family = ph->h_addrtype;
    memcpy(&addr.sin_addr, ph->h_addr, ph->h_length);
    addr.sin_port = htons(CDR_SOCK);

    // Create the socket.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        throw "Failure creating socket";

    // Connect to the server.
    if (connect(sock, (struct sockaddr *)&addr, sizeof addr) < 0)
        throw "Failure connecting to CDR server";
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
std::string CdrSocket::sendCommand(const std::string& cmd) 
{
    try {

        // Wrap the command in a CdrCommandSet element.
        std::string request = "<CdrCommandSet>";
        if (!sessionString.empty())
            request += "<SessionId>" + sessionString + "</SessionId>";
        request += "<CdrCommand>" + cmd + "</CdrCommand></CdrCommandSet>";

        // Connect to the server.
        CdrSocket cdrSocket;

        // Tell the server the size of the coming request buffer.
        long len = htonl(request.length());
        if (send(cdrSocket.sock, (char *)&len, sizeof len, 0) < 0)
            throw "Failure sending command length";

        // Submit the command to the server.
        if (send(cdrSocket.sock, request.c_str(), request.length(), 0) < 0)
            throw "Failure sending command";

        // Retrieve the server's response.
        std::string response = cdrSocket.read();
        return response;
    }
    catch (const char* error) { return errResponse(error); }
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
			return errResponse("Failure reading byte count from server");
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
			return errResponse("Failure reading reply from server");
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
std::string TinyXmlParser::extract(const std::string& tag) const 
{
    // Create target strings used in searching for the element's tags.
    std::string open = std::string("<") + tag + ">";
    std::string close = std::string("</") + tag + ">";

    // Find the tags.
    size_t pos = xml.find(open);
    if (pos == xml.npos)
        return "";
    pos += open.length();
    size_t endPos = xml.find(close, pos);

    // Make sure we found the element.
    if (endPos == xml.npos || endPos == pos)
        return "";

    // Pull out the text content.
    return xml.substr(pos, endPos - pos);
}

/**
 * Display each of a set of Err elements to the user.
 *
 *  @param  msg         reference to string object containing the
 *                      <code>Err</code> elements.
 *  @return             <code>true</code> if at least one error message
 *                      was displayed to the user.
 */
bool cdr::showErrors(const std::string& msg)
{
    // Find the first Err element.
	size_t pos = msg.find("<Err>");
	int n = 0;
	while (pos != msg.npos) {

        // Extract the error message.
		pos += 5;
		size_t endPos = msg.find("</Err>", pos);
		if (endPos == msg.npos) {
			::AfxMessageBox("Missing closing tag for Err element");
			break;
		}
		if (pos < endPos) {

            // Show the error message to the user.
			int rc = ::AfxMessageBox(msg.substr(pos, endPos - pos).c_str(), 
                MB_OKCANCEL);
			++n;

            // Let the user bail out to avoid seeing cascading error messages.
            if (rc == IDCANCEL)
                break;
		}

        // Find the next Err element.
		pos = msg.find("<Err>", endPos);
	}

    // Tell the caller if we displayed any error messages.
	return n > 0;
}

/**
 * Extracts document ID and title from the XML containing the CDR
 * server's response and uses each pair to populate the caller's
 * list box object.
 *
 *  @param  listBox         reference to caller's list box, to which
 *                          we add strings identifying each document
 *                          in the server's response.
 *  @param  xml             reference to string object containing
 *                          server's response to a request for potential
 *                          link targets.
 *  @return                 number of strings added to list box, or -1
 *                          in the event of an error.
 */
int cdr::fillListBox(CListBox& listBox, const std::string& xml)
{
    // Start with a clean slate.
    listBox.ResetContent();

    // Start at the beginning of the XML string.
    size_t pos = 0;
    int n = 0;

    // Locate each DocId and DocTitle element.
	while ((pos = xml.find("<DocId>", pos)) != xml.npos) {
        ++n;
		pos += 7;
		size_t endPos = xml.find("</DocId>", pos);
		if (endPos == xml.npos) {
			::AfxMessageBox("Missing closing tag for DocId element");
            listBox.ResetContent();
            return -1;
		}

        // Build a string in the form "[doc-id] doc-title"
		std::string id = "[" + xml.substr(pos, endPos - pos);
		std::string title;
		pos = xml.find("<DocTitle>", endPos);
		if (pos != xml.npos) {
			pos += 10;
			endPos = xml.find("</DocTitle>", pos);
			if (endPos == xml.npos) {
				::AfxMessageBox("Missing closing tag for DocTitle element");
                listBox.ResetContent();
                return -1;
			}
			title = xml.substr(pos, endPos - pos);
			pos = endPos;
		}

        // Append the new string to the list box object.
		listBox.AddString((id + "] " + title).c_str());
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
        if (app.CreateDispatch("XMetaL.Application", &e))
            return app;
    }
    catch (CException *e) {
		e->ReportError();
    }
    throw "Unable to create XMetaL Application-level automation object";
}

/**
 * Finds the location where the currently running XMetaL application is
 * installed.
 *
 *  @return             reference to string containing path for base XMetaL
 *                      folder.
 */
std::string cdr::getXmetalPath() 
{
    static std::string xmetalPath;
    if (xmetalPath.empty()) {
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
std::string cdr::encode(std::string str, bool fixQuotes)
{
	for (size_t i = 0; i < str.length(); ++i) {
		switch (str[i]) {
		case '<':
			str.replace(i, 1, "&lt;");
			i += 3;
			break;
		case '>':
			str.replace(i, 1, "&gt;");
			i += 3;
			break;
		case '&':
			str.replace(i, 1, "&amp;");
			i += 4;
			break;
		case '\'':
			if (fixQuotes) {
				str.replace(i, 1, "&apos;");
				i += 5;
			}
			break;
		case '"':
			if (fixQuotes) {
				str.replace(i, 1, "&quot;");
				i += 5;
			}
		}
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
unsigned long cdr::getDocNo(const std::string& docString)
{
    const char* p = docString.c_str();
    while (*p && !isdigit(*p))
        ++p;
    return strtoul(p, 0, 10);
}

/**
 * Extracts and concatenates the text content for an element.
 *
 *  @param  node            DOM node object for element.
 *  @return                 string object containing concatenated text
 *                          content for element.
 */
std::string cdr::extractElementText(DOMNode node)
{
    std::string s;
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
std::string cdr::trim(const std::string& s)
{
    // Working variables.
    size_t first = 0;
    size_t len = s.size();
    size_t last = len;

    // Find the first non-whitespace character in the string.
    while (len > 0 && isspace(s[first])) {
        ++first;
        --len;
    }

    // Find the last ditto.
    while (len > 0 && isspace(s[last])) {
        --len;
        --last;
    }

    // Just return a direct copy of the original string if no trimming needed.
    if (first == 0 && len == s.size())
        return s;
    else
        return s.substr(first, len);
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
            if (node.GetNodeName() == "CdrDocCtl") {
                node = node.GetFirstChild();
                while (node) {

                    // Only interested in elements (type 1).
                    if (node.GetNodeType() == 1) {
                        std::string name = node.GetNodeName();
                        if (name == "DocTitle")
                            info.docTitle = extractElementText(node);
                        else if (name == "DocId")
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
std::string errResponse(const char* err)
{
	return std::string("<CdrResponseSet><CdrResponse Status='failure'>"
			           "<Errors><Err>") + err + "</Err></Errors>"
					   "</CdrResponse></CdrResponseSet>";
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
std::ostream& operator<<(std::ostream& os, DOMNode& node)
{
	// Obtain some local copies of the node's "attributes" (not in the XML 
    // sense).
	int nodeType = node.GetNodeType();
	std::string name = node.GetNodeName();

    // Swallow the CdrDocCtl element.
	if (nodeType == 1 && name != "CdrDocCtl") {

		// Element node.  Output the start tag.
		os << '<' << name;
		DOMNamedNodeMap attrs = node.GetAttributes();
		int n = attrs.GetLength();
		for (int i = 0; i < n; ++i) {
			DOMNode attr = attrs.item(i);
			std::string attrName = attr.GetNodeName();
			std::string val = attr.GetNodeValue();
			os << ' ' << attrName << "='"
               << cdr::encode(val, true) << '\'';
		}
		if (!node.hasChildNodes())
			os << '/';
		os << '>';
    }

    // If this is a text node (type 3) pump out the characters.
	else if (nodeType == 3) {

		std::string val = node.GetNodeValue();
        os << cdr::encode(val);
	}

    // Handle processing instructions.
	else if (nodeType == 9) {

		std::string val = node.GetNodeValue();
		os << "<?" << name << " " << val << "?>";
	}

	// Process any children of the node.
	if (node.hasChildNodes() && name != "CdrDocCtl") {
		DOMNode n = node.GetFirstChild();
		os << n;

		// If this is an element node, write the closing tag.
		if (nodeType == 1)
			os << "</" << name << '>';
	}

	// Continue with this node's siblings
	DOMNode sibling = node.GetNextSibling();
	if (sibling)
		os << sibling;
	return os;
}
