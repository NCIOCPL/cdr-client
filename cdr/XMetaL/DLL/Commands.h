// Commands.h: Definition of the CCommands class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDS_H__B4E5B924_A6EE_46EA_A5D4_FB1EA9F19174__INCLUDED_)
#define AFX_COMMANDS_H__B4E5B924_A6EE_46EA_A5D4_FB1EA9F19174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include <string>
#include "LogonDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCommands

class CCommands : 
	public IDispatchImpl<ICommands, &IID_ICommands, &LIBID_CDRLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CCommands,&CLSID_Commands>
{
public:
	CCommands() {}
    static bool doRetrieve(const CString& id,
                           BOOL checkOut,
                           const CString& version);
    static bool doInsertLink(const CString&);
    static bool doLogon(LogonDialog& dialog);

BEGIN_COM_MAP(CCommands)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ICommands)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
DECLARE_NOT_AGGREGATABLE(CCommands) 

DECLARE_REGISTRY_RESOURCEID(IDR_Commands)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICommands
public:
	STDMETHOD(isReadOnly)(/*[in]*/ const BSTR* docType, /*[in]*/ const BSTR* elemName, /*[out retval]*/ BOOL* pVal);
	STDMETHOD(edit)(/*[out, retval]*/ int* pRet);
	STDMETHOD(logoff)(/*[out, retval]*/ int* pRet);
	STDMETHOD(validate)(/*[out, retval]*/ int* pRet);
	STDMETHOD(save)(/*[out, retval]*/ int* pRet);
	STDMETHOD(search)(/*[out, retval]*/ int* pRet);
	STDMETHOD(retrieve)(/*[out, retval]*/ int* pRet);
	STDMETHOD(logon)(/*[out, retval]*/ int* pRet);
};

#endif // !defined(AFX_COMMANDS_H__B4E5B924_A6EE_46EA_A5D4_FB1EA9F19174__INCLUDED_)
