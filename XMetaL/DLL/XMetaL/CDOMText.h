// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "XMetaL/xmetal.tlb" no_namespace
// CDOMText wrapper class

class CDOMText : public COleDispatchDriver
{
public:
	CDOMText() {} // Calls COleDispatchDriver default constructor
	CDOMText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDOMText(const CDOMText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// DOMText methods
public:
	LPDISPATCH get_parentNode()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	short get_nodeType()
	{
		short result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	CString get_nodeName()
	{
		CString result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_nodeValue()
	{
		CString result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_nodeValue(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_firstChild()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_lastChild()
	{
		LPDISPATCH result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_nextSibling()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_previousSibling()
	{
		LPDISPATCH result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL hasChildNodes()
	{
		BOOL result;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH;
		InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, newChild, oldChild);
		return result;
	}
	LPDISPATCH insertBefore(LPDISPATCH newNode, VARIANT& refNode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_VARIANT;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, newNode, &refNode);
		return result;
	}
	LPDISPATCH removeChild(LPDISPATCH child)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, child);
		return result;
	}
	LPDISPATCH appendChild(LPDISPATCH child)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, child);
		return result;
	}
	LPDISPATCH get_ownerDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_childNodes()
	{
		LPDISPATCH result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_attributes()
	{
		LPDISPATCH result;
		InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH cloneNode(BOOL deep)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, deep);
		return result;
	}
	CString get_data()
	{
		CString result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_data(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_length()
	{
		long result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString substringData(long offset, long count)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, offset, count);
		return result;
	}
	void appendData(LPCTSTR data)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms, data);
	}
	void insertData(long offset, LPCTSTR data)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms, offset, data);
	}
	void deleteData(long offset, long count)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms, offset, count);
	}
	void replaceData(long offset, long count, LPCTSTR data)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms, offset, count, data);
	}
	LPDISPATCH splitText(long offset)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x191, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, offset);
		return result;
	}

	// DOMText properties
public:

};
