// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "XMetaL/xmetal.tlb" no_namespace
// CDOMElement wrapper class

class CDOMElement : public COleDispatchDriver
{
public:
	CDOMElement() {} // Calls COleDispatchDriver default constructor
	CDOMElement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDOMElement(const CDOMElement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// DOMElement methods
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
	CString get_tagName()
	{
		CString result;
		InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString getAttribute(LPCTSTR attrName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, attrName);
		return result;
	}
	void setAttribute(LPCTSTR attrName, LPCTSTR attrValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName, attrValue);
	}
	void removeAttribute(LPCTSTR attrName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName);
	}
	void normalize()
	{
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH getAttributeNode(LPCTSTR attrName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x131, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, attrName);
		return result;
	}
	LPDISPATCH setAttributeNode(LPDISPATCH attrNode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x132, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, attrNode);
		return result;
	}
	LPDISPATCH removeAttributeNode(LPDISPATCH attrNode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x133, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, attrNode);
		return result;
	}
	LPDISPATCH getElementsByTagName(LPCTSTR tagName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x134, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, tagName);
		return result;
	}
	BOOL hasAttribute(LPCTSTR attrName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x135, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, attrName);
		return result;
	}
	CString get_namespaceURI()
	{
		CString result;
		InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_prefix()
	{
		CString result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_prefix(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_localName()
	{
		CString result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString getAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x193, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, namespaceName, localName);
		return result;
	}
	void setAttributeNS(LPCTSTR namespaceName, LPCTSTR localName, LPCTSTR attrValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x194, DISPATCH_METHOD, VT_EMPTY, NULL, parms, namespaceName, localName, attrValue);
	}
	void removeAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x195, DISPATCH_METHOD, VT_EMPTY, NULL, parms, namespaceName, localName);
	}
	LPDISPATCH getAttributeNodeNS(LPCTSTR namespaceName, LPCTSTR localName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x196, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, namespaceName, localName);
		return result;
	}
	LPDISPATCH setAttributeNodeNS(LPDISPATCH attrNode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x197, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, attrNode);
		return result;
	}
	LPDISPATCH getElementsByTagNameNS(LPCTSTR namespaceName, LPCTSTR localName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x198, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, namespaceName, localName);
		return result;
	}
	BOOL hasAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x199, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, namespaceName, localName);
		return result;
	}
	LPDISPATCH getNodesByXPath(LPCTSTR xpathExpression)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x19a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xpathExpression);
		return result;
	}
	LPDISPATCH setAttributeNodeWF(LPDISPATCH attrNode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x19b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, attrNode);
		return result;
	}

	// DOMElement properties
public:

};
