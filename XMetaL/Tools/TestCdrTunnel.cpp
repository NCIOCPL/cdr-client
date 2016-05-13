//----------------------------------------------------------------------
//
// $Id$
//
// Proof of concept for OCECDR-3748
//
// Build:
//     cl /EHsc TestCdrTunnel.cpp
//
// Usage:
//     TestCdrTunnel.exe [server [command-set]]
//     [default server is cdr.dev.cancer.gov; reads command set from
//      standard input by default]
//
//----------------------------------------------------------------------
#define WINVER 0x0500
#define WIN32
#define _WINDOWS
#define _WIN32_WINNT 0x0500
#define _WIN32_WINDOWS 0x0500
#define _CTR_SECURE_NO_WARNINGS
#include <afxwin.h>
#include <afxext.h>
#include <afxinet.h>
#include <afxdtctl.h>
#include <winsock.h>
#include <wininet.h>
#include <atlenc.h>
#include <iostream>
#include <string>

CString send_command(const CString& cmd, const CString& server) {
    CString response;
    CInternetSession session;
    CString headers;
    CHttpConnection* conn = NULL;
    CHttpFile* file = NULL;
    CStringA ascii = (CStringA)cmd.GetString();
    CStringA::PCXSTR bytes = ascii.GetString();
    DWORD length = ascii.GetLength();
    BOOL success = FALSE;
    INTERNET_PORT port = 443;
    const TCHAR* target = _T("/cgi-bin/cdr/https-tunnel.ashx");
    headers.Format(_T("Content-type: application/xml; charset=utf-8\n"));
    DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
    conn = session.GetHttpConnection(server, port);
    std::cerr << "got http connection\n";
    file = conn->OpenRequest(_T("POST"), target, NULL, 1, NULL, NULL, flags);
    for (int i = 0; !success && i < 3; ++i) {
	DWORD secFlags;
	file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
	secFlags |= SECURITY_IGNORE_ERROR_MASK;
	file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
	std::cerr << "sec flags=" << secFlags << "\n";
	success = file->SendRequest(headers, (void*)bytes, length);
	if (!success)
	    std::cerr << "SendRequest() failure\n";
    }
    if (!success)
	throw _T("Failure submitting request to server");
    DWORD result;
    file->QueryInfoStatusCode(result);
    std::cerr << "status code=" << result << "\n";
    if (result != HTTP_STATUS_OK) {
	CString err;
	err.Format(_T("HTTP status code from server: %lu"), result);
	throw err;
    }
    static char buf[1024 * 1024];
    UINT nread = file->Read(buf, sizeof buf);
    while (nread > 0) {
	response += CString(buf, (int)nread);
	nread = file->Read(buf, sizeof buf);
    }
    conn->Close();
    file->Close();
    return response;
}

CString read_command() {
    std::string cmd;
    std::string line;
    while (std::getline(std::cin, line))
	cmd += line + "\n";
    return cmd.c_str();
}

int main(int ac, char** av) {
    try {
	CString server = ac > 1 ? av[1] : _T("cdr.dev.cancer.gov");
	CString cmd = ac > 2 ? av[2] : read_command();
	std::cout << send_command(cmd, server);
    }
    catch (CString& s) {
	std::cerr << "failure: " << s << "\n";
    }
    catch (const char* e) {
	std::cerr << "Failure: " << e << "\n";
    }
    catch (...) {
	std::cerr << "Failure!\n";
    }
    return 0;
}
