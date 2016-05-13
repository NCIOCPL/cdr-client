//----------------------------------------------------------------------
//
// $Id$
//
// Proof of concept for OCECDR-3746
//
// Build:
//     cl /EHsc TestSecureLogin.cpp
//
// Usage:
//     TestSecureLogin.exe uid pwd
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

CString login(const char* server, const char* uid, const char* pwd) {
    CString response;
    CInternetSession session(_T("CDR Client"));
    CHttpConnection* conn = NULL;
    CHttpFile* file = NULL;
    BOOL success = FALSE;
    INTERNET_PORT port = INTERNET_DEFAULT_HTTPS_PORT;
    const TCHAR* target = _T("/cgi-bin/secure/login.py");
    const CString host(server);
    conn = session.GetHttpConnection(host, port, (LPCTSTR)uid, (LPCTSTR)pwd);
    std::cerr << "got http connection\n";
    DWORD flags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_SECURE;
    file = conn->OpenRequest(_T("GET"), target, NULL, 1, NULL, NULL, flags);
    std::cerr << "request opened\n";
    for (int i = 0; !success && i < 3; ++i) {
        DWORD secFlags;
        file->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
        secFlags |= SECURITY_IGNORE_ERROR_MASK;
        file->SetOption(INTERNET_OPTION_SECURITY_FLAGS, secFlags);
        std::cerr << "sec flags=" << secFlags << "\n";
        success = file->SendRequest();
        if (!success)
            std::cerr << "login() failure\n";
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

int main(int ac, char** av) {
    if (ac != 4) {
        std::cerr << "usage: TestSecureLogin HOST UID PWD\n";
        return 1;
    }
    try {
        std::cout << login(av[1], av[2], av[3]);
    }
    catch (CString& s) {
        std::cerr << "failure: " << s << "\n";
    }
    catch (const char* e) {
        std::cerr << "Failure: " << e << "\n";
    }
    catch (CInternetException* ie) {
        char message[256];
        ie->GetErrorMessage(message, 256);
        std::cerr << "CInternetException: " << message << "\n";
    }
    catch (...) {
        std::cerr << "Failure!\n";
    }
    return 0;
}
