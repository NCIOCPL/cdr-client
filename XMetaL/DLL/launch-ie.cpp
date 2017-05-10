/*
 * Repro case for CBIIT to show Microsoft for tracking down why IE
 * is opening duplicate tabs when launched using OLE automation.
 *
 * Built using 32-bit cl version 16.00.30319.01:
 *
 *   cl /EHsc /MD launch-ie.cpp
 */

#define _WIN32_WINNT 0x0501
#define _AFXDLL 1
#define _UNICODE 1
#include <iostream>
#include <cstdlib>
#include <afxwin.h>
#include <afxdisp.h>
#include <afxole.h>

static int xxshowPage(const CString& url) {
    COleDispatchDriver ie;
    COleException* pe = new COleException;
    try {
        if (!ie.CreateDispatch(_T("InternetExplorer.Application"), pe)) {
            DWORD error = ::GetLastError();
            std::cerr << "CreateDispatch: unable to launch IE (error "
                      << error << ")" << std::endl;
            return EXIT_FAILURE;
        }
    }
    catch (COleDispatchException* pExc) {
        std::cerr << "caught COleDispatchException" << std::endl;
        pExc->Delete();
        return EXIT_FAILURE;
    }
    catch (CException* e) {
        std::cerr << "caught CException" << std::endl;
        e->Delete();
        return EXIT_FAILURE;
    }
    pe->Delete();
    COleMessageFilter* pFilter = AfxOleGetMessageFilter();
    pFilter->SetMessagePendingDelay(20000);
    pFilter->EnableNotRespondingDialog(FALSE);
    pFilter->EnableBusyDialog(FALSE);
    DISPID dispid;
    OLECHAR* member = L"Navigate";
    HRESULT hresult = ie.m_lpDispatch->GetIDsOfNames(IID_NULL,
        &member, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
    if (hresult != S_OK) {
        std::cerr << "GetIDsOfNames: Unable to launch IE" << std::endl;
        return EXIT_FAILURE;
    }
    static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR
                          VTS_PVARIANT VTS_PVARIANT;
    COleVariant dummy;
    ie.InvokeHelper(dispid, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
        url, 0L, _T("CdrViewWindow"), &dummy, &dummy);
    return EXIT_SUCCESS;
}

static int showPage(const CString& url) {
    CString ie = _T("\"%ProgramFiles%\\Internet Explorer\\iexplore.exe\"");
    CString command = _T("\"") + ie + _T(" \"") + url + _T("\"\"");
    _tsystem(command);
    return EXIT_SUCCESS;
}

int main(int ac, char** av) {
    AfxOleInit();
    CoInitialize(NULL);
    CString url = ac > 1 ? av[1] : "https://cancer.gov";
    return showPage(url);
}
