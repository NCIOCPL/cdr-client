// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CDocuments wrapper class

class CDocuments : public COleDispatchDriver
{
public:
	CDocuments() {} // Calls COleDispatchDriver default constructor
	CDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDocuments(const CDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Documents methods
public:
	LPDISPATCH item(VARIANT * index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, index);
		return result;
	}
	long get_count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Open(LPCTSTR FileName, long ViewType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, ViewType);
		return result;
	}
	LPDISPATCH Add(BOOL UseDefaultTemplate)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, UseDefaultTemplate);
		return result;
	}
	void Save()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Close()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH OpenTemplate(LPCTSTR FileName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName);
		return result;
	}
	LPDISPATCH OpenString(LPCTSTR inputString, long ViewType, LPCTSTR FileName, BOOL TreatAsTemplate, BOOL IsXML, BOOL EditAsWellFormed)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, inputString, ViewType, FileName, TreatAsTemplate, IsXML, EditAsWellFormed);
		return result;
	}
	CString ChooseTemplate()
	{
		CString result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH OpenEx(LPCTSTR FileName, VARIANT * CRLocatorDisp, long ViewType, BOOL ReadOnly)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_I4 VTS_BOOL;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, CRLocatorDisp, ViewType, ReadOnly);
		return result;
	}
	BOOL MoveToNewTabGroup(VARIANT * Document, BOOL vertical)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT VTS_BOOL;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Document, vertical);
		return result;
	}
	BOOL MoveToNextTabGroup(VARIANT * Document)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Document);
		return result;
	}
	BOOL MoveToPrevTabGroup(VARIANT * Document)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Document);
		return result;
	}
	__int64 TabGroupCommand(__int64 tabGroup, __int64 tabCommand)
	{
		__int64 result;
		static BYTE parms[] = VTS_I8 VTS_I8;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I8, (void*)&result, parms, tabGroup, tabCommand);
		return result;
	}
	LPDISPATCH OpenAsXml(LPCTSTR filePath, VARIANT * CRLocator, LPCTSTR vwProgId, LPCTSTR xml, long vwType, LPCTSTR openInfo)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, filePath, CRLocator, vwProgId, xml, vwType, openInfo);
		return result;
	}
	void EnableTemplateFolder(LPCTSTR dir)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dir);
	}
	void DisableTemplateFolder(LPCTSTR dir)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dir);
	}
	void EnableTemplate(LPCTSTR fp)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fp);
	}
	void DisableTemplate(LPCTSTR fp)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fp);
	}

	// Documents properties
public:

};
