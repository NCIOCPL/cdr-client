/*
 * Proof of concept for being able to launch MS Edge from XMetaL.
 *
 * Built using 64-bit cl version 19.29.30137:
 *
 *   cl /EHsc /MD launch-msedge.cpp
 */

#define _WIN32_WINNT 0x0A00
#define _AFXDLL 1
#define _UNICODE 1
#include <iostream>
#include <cstdlib>
#include <afxwin.h>
#include <afxdisp.h>
#include <afxole.h>
#include <cwchar>

static CString find_msedge() {
    wchar_t* vars[] = {
        L"ProgramFiles(x86)",
        L"ProgramFiles",
        L"APPDATA",
        L"LOCALAPPDATA"
    };
    CString tail = L"\\Microsoft\\Edge\\Application\\msedge.exe";
    for (size_t i = 0; i < sizeof vars / sizeof vars[0]; ++i) {
        wchar_t* dir = _wgetenv(vars[i]);
        if (dir) {
            CString path = dir + tail;
            std::wcout << "testing " << (const wchar_t*)path << std::endl;
            if (!_waccess((const wchar_t*)path, 0)) {
                std::wcout << "found " << (const wchar_t*)path << std::endl;
                return path;
            }
        }
    }
    return L"";
}

static int showPage(const CString& url) {
    wchar_t* cmd = new wchar_t[url.GetLength() + 10];
    swprintf(cmd, url.GetLength() + 10, L"msedge %ls", (const wchar_t*)url);
    CString msedge = find_msedge();
    if (msedge.IsEmpty()) {
        std::cout << "Unable to find msedge\n";
        return EXIT_FAILURE;
    }
    PROCESS_INFORMATION process_information;
    STARTUPINFO startup_information;
    memset(&process_information, 0, sizeof(process_information));
    memset(&startup_information, 0, sizeof(startup_information));
    startup_information.cb = sizeof(startup_information);
    std::wcout << _T("Launching ") << cmd << std::endl;
    BOOL result= CreateProcess(msedge, cmd, NULL, NULL, FALSE,
                               NORMAL_PRIORITY_CLASS, NULL, NULL,
                               &startup_information, &process_information);

    if (result) {
        WaitForSingleObject(process_information.hProcess, INFINITE);
        CloseHandle(process_information.hProcess);
        CloseHandle(process_information.hThread);
        delete[] cmd;
        return EXIT_SUCCESS;
    }
    else {
        std::cerr << "CreateProcess() failed\n";
        delete[] cmd;
        return EXIT_FAILURE;
    }
}

int wmain(int ac, wchar_t** av) {
    AfxOleInit();
    CoInitialize(NULL);
    CString url = ac > 1 ? av[1] : L"https://cancer.gov";
    return showPage(url);
}
