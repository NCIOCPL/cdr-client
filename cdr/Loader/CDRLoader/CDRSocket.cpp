/***************************************************
*	CDRSocket
*	
*		Extracted (cut & paste) from client/CDRUtil 
*		so it can be used without pulling in all the 
*		references to XMetal's export COM functions
*
***************************************************/

#include "stdafx.h"

#include "CDRSocket.h"
#include "CDRGenerics.h"

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
    const char* hostEnv = getenv("CDR_HOST");
    const char* portEnv = getenv("CDR_PORT");
    const char* host = hostEnv ? hostEnv : "mmdb2.nci.nih.gov";
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
 * Packs up a string containing an error message inside the XML structure
 * appropriate for simulating a buffer returned by the CDR server, in the
 * event of a failure to communicate with the server.
 *
 *  @param  err             error message to be packed inside the buffer.
 *  @return                 string object representing response buffer.
 */
CString CdrSocket::errResponse(const CString& err)
{
	return _T("<CdrResponseSet><CdrResponse Status='failure'><Errors><Err>")
		+ err + _T("</Err></Errors></CdrResponse></CdrResponseSet>");
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
    catch (LPCTSTR error) { return CdrSocket::errResponse(error); }
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

