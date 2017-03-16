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
                           const CString& version = _T("Current"));
    static bool doInsertLink(const CString&);
    static bool doLogon(LogonDialog* dialog);
    static CString getUsername() { return username; }

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
    STDMETHOD(acceptOrRejectMarkup)(void);
    STDMETHOD(addGlossaryPhrase)(void);
    STDMETHOD(advancedSearch)(/*[out, retval]*/ int* retVal);
    STDMETHOD(checkIn)(/*[out, retval]*/ int* pRet);
    STDMETHOD(chooseRevisionLevel)(BSTR* response_);
    STDMETHOD(edit)(/*[out, retval]*/ int* pRet);
    STDMETHOD(editComment)(VARIANT_BOOL readOnly);
    STDMETHOD(fetchFromUrl)(const BSTR* url_, BSTR* response_);
    STDMETHOD(getBoardMemberId)(const BSTR* personId, BSTR* boardMemberId);
    STDMETHOD(getDiagnosisSetTerms)(BSTR* termIds);
    STDMETHOD(getGlossaryTermNameIds)(const BSTR* conceptId, BSTR* termNameIds);
    STDMETHOD(getGlossaryTermNames)(const BSTR* conceptId, BSTR* termNames);
    STDMETHOD(getNextValidationError)(BSTR* valError);
    STDMETHOD(getOrgAddress)(/*[out, retval]*/ int* pRet);
    STDMETHOD(getPatientDocId)(const BSTR* hpDocId, BSTR* patientDocId);
    STDMETHOD(getPersonAddress)(/*[out, retval]*/ int* pRet);
    STDMETHOD(getTranslatedDocId)(const BSTR* originalId, BSTR* translatedDocId);
    STDMETHOD(get_hostname)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_session)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_userPath)(BSTR* pVal);
    STDMETHOD(get_username)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(glossify)(VARIANT_BOOL dig);
    STDMETHOD(isReadOnly)(/*[in]*/ const BSTR* docType, /*[in]*/ const BSTR* elemName, /*[out retval]*/ BOOL* pVal);
    STDMETHOD(launchBlob)(const BSTR* docId, const BSTR* docVer);
    STDMETHOD(logClientEvent)(const BSTR* description, int* pRet);
    STDMETHOD(logoff)(/*[out, retval]*/ int* pRet);
    STDMETHOD(logon)(/*[out, retval]*/ int* pRet);
    STDMETHOD(openCdrDoc)(const BSTR* docId, const BSTR* docVer, VARIANT_BOOL checkOut);
    STDMETHOD(particOrgs)(/*[out, retval]*/ int* pRet);
    STDMETHOD(pasteDocLink)(/*[in]*/ const BSTR* val, /*[out, retval]*/ int* pRet);
    STDMETHOD(protUpdPerson)(/*[out, retval]*/ int* pRet);
    STDMETHOD(retrieve)(/*[out, retval]*/ int* pRet);
    STDMETHOD(save)(/*[out, retval]*/ int* pRet);
    STDMETHOD(search)(/*[out, retval]*/ int* pRet);
    STDMETHOD(setTitleBar)(void);
    STDMETHOD(showPage)(const BSTR* url,  int* pRet);
    STDMETHOD(validate)(/*[out, retval]*/ int* pRet);
    STDMETHOD(valuesForPath)(const BSTR* docId, const BSTR* path, BSTR* values);

    static bool invokedFromClientRefreshTool;

private:
    static CString username;
    static CString linkClipboard;
};

#endif // !defined(AFX_COMMANDS_H__B4E5B924_A6EE_46EA_A5D4_FB1EA9F19174__INCLUDED_)
