// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CDOMDocumentType wrapper class

class CDOMDocumentType : public COleDispatchDriver
{
public:
	CDOMDocumentType() {} // Calls COleDispatchDriver default constructor
	CDOMDocumentType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDOMDocumentType(const CDOMDocumentType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// DOMDocumentType methods
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
	CString get_name()
	{
		CString result;
		InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_entities()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_notations()
	{
		LPDISPATCH result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_elementType(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	VARIANT get_elementTypes()
	{
		VARIANT result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	BOOL get_hasElementType(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL get_hasAttribute(LPCTSTR ElementName, LPCTSTR AttributeName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName, AttributeName);
		return result;
	}
	CString get_elementAttribute(LPCTSTR ElementName, long index)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ElementName, index);
		return result;
	}
	VARIANT get_elementAttributes(LPCTSTR ElementName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, ElementName);
		return result;
	}
	CString get_publicId()
	{
		CString result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_systemId()
	{
		CString result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_attributeType(LPCTSTR ElementName, LPCTSTR AttributeName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, ElementName, AttributeName);
		return result;
	}
	CString get_enumeratedAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName, long index)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ElementName, AttributeName, index);
		return result;
	}
	VARIANT get_enumeratedAttributeTypes(LPCTSTR ElementName, LPCTSTR AttributeName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, ElementName, AttributeName);
		return result;
	}
	long get_elementContentType(LPCTSTR ElementName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, ElementName);
		return result;
	}
	long get_attributeDefaultType(LPCTSTR ElementName, LPCTSTR AttributeName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, ElementName, AttributeName);
		return result;
	}
	CString get_attributeDefaultValue(LPCTSTR ElementName, LPCTSTR AttributeName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ElementName, AttributeName);
		return result;
	}
	void addElement(LPCTSTR ElementName, LPCTSTR description, BOOL any, BOOL retainWhiteSpace)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL;
		InvokeHelper(0x13d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName, description, any, retainWhiteSpace);
	}
	void addElementToInclusions(LPCTSTR ElementNameToAdd, LPCTSTR ElementNameInclusions)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x13e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementNameToAdd, ElementNameInclusions);
	}
	void addAttribute(LPCTSTR ElementName, LPCTSTR attrName, LPCTSTR helpString, long attrType, long dfltType, LPCTSTR attValueDefault)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x13f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName, attrName, helpString, attrType, dfltType, attValueDefault);
	}
	void addEnumeratedAttribute(LPCTSTR ElementName, LPCTSTR attrName, LPCTSTR helpString, long attrType, long dfltType, LPCTSTR attValueSpec, SAFEARRAY * EnumValues)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_UNKNOWN;
		InvokeHelper(0x140, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName, attrName, helpString, attrType, dfltType, attValueSpec, EnumValues);
	}
	void addInPlaceControlOverride(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, LPCTSTR userData, BOOL useBmpPrinting)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL;
		InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms, selector, progID, scriptPrefix, userData, useBmpPrinting);
	}
	CString get_parentElementType(LPCTSTR elementType, long index)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, elementType, index);
		return result;
	}
	VARIANT get_parentElementTypes(LPCTSTR elementType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, elementType);
		return result;
	}
	BOOL get_hasParentElementType(LPCTSTR elementType, LPCTSTR ParentElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementType, ParentElementName);
		return result;
	}
	CString get_childElementType(LPCTSTR elementType, long index)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, elementType, index);
		return result;
	}
	VARIANT get_childElementTypes(LPCTSTR elementType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, elementType);
		return result;
	}
	BOOL get_hasChildElementType(LPCTSTR elementType, LPCTSTR ChildElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementType, ChildElementName);
		return result;
	}
	void addTableElementMap(LPCTSTR tableType, LPCTSTR json)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x148, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tableType, json);
	}
	void addInPlaceControlOverrideEx(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, LPCTSTR userData, BOOL useBmpPrinting, BOOL canZoom, LPCTSTR reserved)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BSTR;
		InvokeHelper(0x149, DISPATCH_METHOD, VT_EMPTY, NULL, parms, selector, progID, scriptPrefix, userData, useBmpPrinting, canZoom, reserved);
	}

	// DOMDocumentType properties
public:

};
