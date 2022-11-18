// Cdr.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL,
//      run nmake -f Cdrps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "Cdr.h"

#include "Cdr_i.c"
#include "Commands.h"
#include "CdrUtil.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Commands, CCommands)
END_OBJECT_MAP()

class CCdrApp : public CWinApp
{
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCdrApp)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CCdrApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCdrApp, CWinApp)
    //{{AFX_MSG_MAP(CCdrApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCdrApp theApp;

BOOL CCdrApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_CDRLib);
    BOOL success = CWinApp::InitInstance();
    if (success)
        cdr::debug_log("CWinApp::InitInstance() succeeded");
    else
        cdr::debug_log("CWinApp::InitInstance() failed");
    return success;
}

int CCdrApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    AtlSetPerUserRegistration(true);
    HRESULT hr = _Module.RegisterServer(TRUE);
    CString msg;
    msg.Format(L"RegisterServer() returned %lx", hr);
    cdr::debug_log(msg);
    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    AtlSetPerUserRegistration(true);
    HRESULT hr = _Module.UnregisterServer(TRUE);
    CString msg;
    msg.Format(L"UnregisterServer() returned %lx", hr);
    cdr::debug_log(msg);
    return hr;
}
