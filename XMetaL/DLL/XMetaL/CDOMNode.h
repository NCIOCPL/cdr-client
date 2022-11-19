// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CDOMNode wrapper class

class CDOMNode : public COleDispatchDriver
{
public:
	CDOMNode() {} // Calls COleDispatchDriver default constructor
	CDOMNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDOMNode(const CDOMNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// DOMNode methods
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

	// DOMNode properties
public:

};
