// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "xmetal2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// DOMNode properties

/////////////////////////////////////////////////////////////////////////////
// DOMNode operations

LPDISPATCH DOMNode::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMNode::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMNode::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMNode::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMNode::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMNode::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMNode::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMNode::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMNode::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNode::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNode::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNode::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMNodeList properties

/////////////////////////////////////////////////////////////////////////////
// DOMNodeList operations

LPDISPATCH DOMNodeList::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long DOMNodeList::GetLength()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMNamedNodeMap properties

/////////////////////////////////////////////////////////////////////////////
// DOMNamedNodeMap operations

LPDISPATCH DOMNamedNodeMap::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long DOMNamedNodeMap::GetLength()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNamedNodeMap::getNamedItem(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH DOMNamedNodeMap::setNamedItem(LPDISPATCH node)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		node);
	return result;
}

LPDISPATCH DOMNamedNodeMap::removeNamedItem(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMDocument properties

/////////////////////////////////////////////////////////////////////////////
// DOMDocument operations

LPDISPATCH DOMDocument::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMDocument::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMDocument::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocument::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMDocument::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMDocument::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMDocument::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMDocument::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMDocument::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocument::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocument::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

LPDISPATCH DOMDocument::createElement(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH DOMDocument::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH DOMDocument::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH DOMDocument::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH DOMDocument::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH DOMDocument::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH DOMDocument::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH DOMDocument::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH DOMDocument::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocument::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMElement properties

/////////////////////////////////////////////////////////////////////////////
// DOMElement operations

LPDISPATCH DOMElement::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMElement::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMElement::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElement::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMElement::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMElement::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMElement::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMElement::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMElement::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMElement::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMElement::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElement::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMElement::GetTagName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElement::getAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void DOMElement::setAttribute(LPCTSTR attrName, LPCTSTR attrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, attrValue);
}

void DOMElement::removeAttribute(LPCTSTR attrName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName);
}

void DOMElement::normalize()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH DOMElement::getAttributeNode(LPCTSTR attrName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrName);
	return result;
}

LPDISPATCH DOMElement::setAttributeNode(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElement::removeAttributeNode(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElement::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x134, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

BOOL DOMElement::hasAttribute(LPCTSTR attrName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x135, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		attrName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMAttr properties

/////////////////////////////////////////////////////////////////////////////
// DOMAttr operations

LPDISPATCH DOMAttr::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMAttr::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMAttr::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttr::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttr::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMAttr::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMAttr::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMAttr::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMAttr::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMAttr::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMAttr::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMAttr::GetName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttr::GetValue()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttr::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL DOMAttr::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttr::GetOwnerElement()
{
	LPDISPATCH result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMProcessingInstruction properties

/////////////////////////////////////////////////////////////////////////////
// DOMProcessingInstruction operations

LPDISPATCH DOMProcessingInstruction::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMProcessingInstruction::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstruction::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstruction::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMProcessingInstruction::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMProcessingInstruction::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMProcessingInstruction::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMProcessingInstruction::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMProcessingInstruction::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMProcessingInstruction::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstruction::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMProcessingInstruction::GetTarget()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstruction::GetData()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMProcessingInstruction::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// DOMText properties

/////////////////////////////////////////////////////////////////////////////
// DOMText operations

LPDISPATCH DOMText::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMText::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMText::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMText::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMText::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMText::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMText::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMText::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMText::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMText::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMText::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMText::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMText::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMText::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMText::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMText::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMText::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMText::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMText::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMText::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH DOMText::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x191, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCharacterData properties

/////////////////////////////////////////////////////////////////////////////
// DOMCharacterData operations

LPDISPATCH DOMCharacterData::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCharacterData::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCharacterData::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCharacterData::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCharacterData::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCharacterData::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCharacterData::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCharacterData::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCharacterData::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterData::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterData::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterData::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMCharacterData::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCharacterData::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMCharacterData::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMCharacterData::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMCharacterData::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMCharacterData::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMCharacterData::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMCharacterData::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}


/////////////////////////////////////////////////////////////////////////////
// DOMComment properties

/////////////////////////////////////////////////////////////////////////////
// DOMComment operations

LPDISPATCH DOMComment::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMComment::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMComment::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMComment::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMComment::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMComment::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMComment::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMComment::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMComment::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMComment::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMComment::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMComment::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMComment::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMComment::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMComment::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMComment::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMComment::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMComment::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMComment::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMComment::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}


/////////////////////////////////////////////////////////////////////////////
// DOMDocumentFragment properties

/////////////////////////////////////////////////////////////////////////////
// DOMDocumentFragment operations

LPDISPATCH DOMDocumentFragment::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMDocumentFragment::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMDocumentFragment::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentFragment::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMDocumentFragment::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMDocumentFragment::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentFragment::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMDocumentFragment::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMDocumentFragment::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentFragment::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragment::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMEntityReference properties

/////////////////////////////////////////////////////////////////////////////
// DOMEntityReference operations

LPDISPATCH DOMEntityReference::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMEntityReference::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMEntityReference::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntityReference::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMEntityReference::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMEntityReference::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMEntityReference::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMEntityReference::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMEntityReference::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityReference::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityReference::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReference::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCDATASection properties

/////////////////////////////////////////////////////////////////////////////
// DOMCDATASection operations

LPDISPATCH DOMCDATASection::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCDATASection::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCDATASection::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCDATASection::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCDATASection::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCDATASection::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCDATASection::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCDATASection::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCDATASection::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCDATASection::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCDATASection::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASection::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMCDATASection::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCDATASection::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMCDATASection::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMCDATASection::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMCDATASection::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMCDATASection::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMCDATASection::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMCDATASection::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH DOMCDATASection::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x191, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMDocumentType properties

/////////////////////////////////////////////////////////////////////////////
// DOMDocumentType operations

LPDISPATCH DOMDocumentType::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMDocumentType::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMDocumentType::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentType::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMDocumentType::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMDocumentType::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentType::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMDocumentType::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMDocumentType::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentType::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentType::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMDocumentType::GetName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetEntities()
{
	LPDISPATCH result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentType::GetNotations()
{
	LPDISPATCH result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DOMDocumentType::GetElementType(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

VARIANT DOMDocumentType::GetElementTypes()
{
	VARIANT result;
	InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentType::GetHasElementType(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL DOMDocumentType::GetHasAttribute(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentType::GetElementAttribute(LPCTSTR ElementName, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, index);
	return result;
}

VARIANT DOMDocumentType::GetElementAttributes(LPCTSTR ElementName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		ElementName);
	return result;
}

CString DOMDocumentType::GetPublicId()
{
	CString result;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentType::GetSystemId()
{
	CString result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long DOMDocumentType::GetAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentType::GetEnumeratedAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, AttributeName, index);
	return result;
}

VARIANT DOMDocumentType::GetEnumeratedAttributeTypes(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

long DOMDocumentType::GetElementContentType(LPCTSTR ElementName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName);
	return result;
}

long DOMDocumentType::GetAttributeDefaultType(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentType::GetAttributeDefaultValue(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

void DOMDocumentType::addElement(LPCTSTR ElementName, LPCTSTR description, BOOL any, BOOL retainWhiteSpace)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x13d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName, description, any, retainWhiteSpace);
}

void DOMDocumentType::addElementToInclusions(LPCTSTR ElementNameToAdd, LPCTSTR ElementNameInclusions)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementNameToAdd, ElementNameInclusions);
}

void DOMDocumentType::addAttribute(LPCTSTR ElementName, LPCTSTR attrName, LPCTSTR helpString, long attrType, long dfltType, LPCTSTR attValueDefault)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x13f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName, attrName, helpString, attrType, dfltType, attValueDefault);
}

void DOMDocumentType::addInPlaceControlOverride(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, BOOL useBmpPrinting)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 selector, progID, scriptPrefix, useBmpPrinting);
}


/////////////////////////////////////////////////////////////////////////////
// DOMImplementation properties

/////////////////////////////////////////////////////////////////////////////
// DOMImplementation operations

BOOL DOMImplementation::hasFeature(LPCTSTR feature, LPCTSTR version)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		feature, version);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Document properties

/////////////////////////////////////////////////////////////////////////////
// _Document operations

LPDISPATCH _Document::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short _Document::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString _Document::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _Document::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH _Document::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH _Document::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _Document::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _Document::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

LPDISPATCH _Document::createElement(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _Document::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH _Document::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _Document::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _Document::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _Document::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _Document::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _Document::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH _Document::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Document::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetFullName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetTitle()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _Document::GetSaved()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetSaved(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Document::Save()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::SaveAs(VARIANT* FileName, BOOL AddToRecentFiles)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, AddToRecentFiles);
}

void _Document::Close(long SaveChanges)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveChanges);
}

BOOL _Document::Undo(long Times)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Times);
	return result;
}

BOOL _Document::Redo(long Times)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Times);
	return result;
}

void _Document::Activate()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::ScrollToSelection()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Document::GetInCurrentProject()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Document::GetPath()
{
	CString result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetBodyAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void _Document::SetBodyAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, lpszNewValue);
}

CString _Document::GetDocumentTitle()
{
	CString result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetDocumentTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Document::UniqueAttributeValue(LPCTSTR AttributeName, LPCTSTR Prefix, VARIANT* number)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		AttributeName, Prefix, number);
	return result;
}

void _Document::Validate()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Document::GetRange()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsXML()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsSGML()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsHTML()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _Document::GetViewType()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Document::SetViewType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Document::GetCustomDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Document::GetMacroFile()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsValid()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::Reload()
{
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::RefreshCssStyle()
{
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Document::Layout()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Document::GetLocalPath()
{
	CString result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetLocalFullName()
{
	CString result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsEntityDeclared(LPCTSTR EntityName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		EntityName);
	return result;
}

void _Document::DeleteEntityDeclaration(LPCTSTR EntityName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName);
}

void _Document::DeclareTextEntity(LPCTSTR EntityName, LPCTSTR entityContent, long entityType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, entityContent, entityType);
}

void _Document::DeclareExternalEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicName, FileName);
}

void _Document::DeclareGraphicEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName, LPCTSTR notationName, long entityType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicName, FileName, notationName, entityType);
}

LPDISPATCH _Document::GetChangedNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Document::ClearNodeChangedStates(LPDISPATCH inNode, BOOL deep)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 inNode, deep);
}

void _Document::ClearAllChangedStates()
{
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Document::GetNodeState(LPCTSTR stateName, LPDISPATCH inNode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		stateName, inNode);
	return result;
}

void _Document::HideInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

void _Document::ShowInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

CString _Document::GetBrowserURL()
{
	CString result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetBrowserURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Document::GetBrowserApplication()
{
	CString result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetBrowserApplication(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Document::PreviewInBrowser(LPCTSTR Browser)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Browser);
}

BOOL _Document::GetRulesChecking()
{
	BOOL result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetRulesChecking(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Document::UndoClear()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _Document::GetRenderedContent(LPDISPATCH inNode)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		inNode);
	return result;
}

void _Document::SetRenderedContent(LPDISPATCH inNode, LPCTSTR renderedContent)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 inNode, renderedContent);
}

LPDISPATCH _Document::createCharacterReference(long value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		value);
	return result;
}

LPDISPATCH _Document::getElementById(LPCTSTR value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		value);
	return result;
}

long _Document::GetPreviousViewType()
{
	long result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _Document::GetRulesFile()
{
	CString result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetDOMEnforceValid()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetDOMEnforceValid(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _Document::GetDisplayStylesFile()
{
	CString result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Document::AcceptDropFormat(VARIANT* dropFormat, LPCTSTR formatName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dropFormat, formatName);
	return result;
}

BOOL _Document::GetStructureViewVisible()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetStructureViewVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Range properties

/////////////////////////////////////////////////////////////////////////////
// Range operations

void Range::TypeText(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void Range::Cut()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Copy()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Paste()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Delete()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MoveLeft(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Range::MoveRight(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Range::MoveUp(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Range::MoveDown(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Range::MoveColumnLeft()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MoveColumnRight()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MoveRowUp()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MoveRowDown()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MergeCellLeft()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MergeCellRight()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MergeCellUp()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MergeCellDown()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SplitCellColumn()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SplitCellRow()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertRowsAbove(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Range::InsertRowsBelow(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Range::InsertColumnsLeft(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Range::InsertColumnsRight(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Range::HomeKey(long unit, long extend)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 unit, extend);
}

void Range::EndKey(long unit, long extend)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 unit, extend);
}

LPDISPATCH Range::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Range::GetHorizontalAlignment()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Range::SetHorizontalAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Range::GotoNext(long GotoItem)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GotoItem);
}

void Range::GotoPrevious(long GotoItem)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GotoItem);
}

void Range::Collapse(long CollapseDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CollapseDirection);
}

void Range::PasteString(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

void Range::InsertForm(long FormElement)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FormElement);
}

void Range::InsertElement(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Range::InsertElementWithRequired(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Range::GetContainerName()
{
	CString result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetContainerName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Range::RemoveContainerTags()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SplitContainer()
{
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Range::GetContainerAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void Range::SetContainerAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, lpszNewValue);
}

void Range::InsertComment()
{
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertBreak()
{
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertHorizontalRule()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertNBSP()
{
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::JoinElementToPreceding()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertEntity(LPCTSTR EntityName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName);
}

void Range::Surround(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Range::SelectElement()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::TypingSplit()
{
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::DeleteColumn()
{
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::DeleteRow()
{
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertTable(long NumRows, long NumCols, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRows, NumCols, BGColor, TableWidth, TableWidthUnit, TableBorder, CellPadding, CellSpacing);
}

void Range::InsertCaption()
{
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Indent()
{
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Outdent()
{
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertImage(LPCTSTR Src, LPCTSTR Alt, LPCTSTR Align, LPCTSTR Width, LPCTSTR Height, LPCTSTR Border)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Src, Alt, Align, Width, Height, Border);
}

CString Range::GetStyle()
{
	CString result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Range::PageUp()
{
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::PageDown()
{
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::ToggleTableCellType()
{
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Range::GetElementName(long AncestorNum)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		AncestorNum);
	return result;
}

CString Range::GetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName, ElementName, SkipNum);
	return result;
}

void Range::SetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, ElementName, SkipNum, lpszNewValue);
}

BOOL Range::GetIsParentElement(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

void Range::ListIndent(VARIANT* ElementName)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Range::ListOutdent(VARIANT* ElementName)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Range::GetText()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::GetIsInsertionPoint()
{
	BOOL result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::InsertLink(LPCTSTR Href, LPCTSTR target)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Href, target);
}

LPDISPATCH Range::GetContainerNode()
{
	LPDISPATCH result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Range::SelectBeforeNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Range::SelectAfterNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Range::SelectNodeContents(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Range::SelectAfterContainer()
{
	InvokeHelper(0x48, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SelectBeforeContainer()
{
	InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SelectContainerContents()
{
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Range::GetFind()
{
	LPDISPATCH result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Range::BasicPaste()
{
	InvokeHelper(0x4c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::PasteStringWithInterpret(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

BOOL Range::GetCanInsert(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Range::GetCanChange(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Range::GetCanSurround(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Range::GetCanPaste(LPCTSTR String, BOOL interpret)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		String, interpret);
	return result;
}

BOOL Range::GetIsValid()
{
	BOOL result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::MoveToDocumentStart()
{
	InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::MoveToDocumentEnd()
{
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::SelectAll()
{
	InvokeHelper(0x55, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL Range::ExtendTo(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Range::GetContains(LPDISPATCH Selection, BOOL IncludeSelOnEdge)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, IncludeSelOnEdge);
	return result;
}

BOOL Range::GetIsEqual(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Range::GetOverlaps(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Range::MoveToElement(LPCTSTR ElementName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName, Forward);
	return result;
}

BOOL Range::GetCanInsertText()
{
	BOOL result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::InsertProcessingInstruction()
{
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Range::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Range::GetIsAdjacent(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Range::GetIsLessThan(LPDISPATCH Selection, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, OrEqual);
	return result;
}

BOOL Range::GetIsGreaterThan(LPDISPATCH Selection, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, OrEqual);
	return result;
}

BOOL Range::GetHasAttribute(LPCTSTR attrName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		attrName);
	return result;
}

void Range::InsertCALSTable(long NumRows, long NumCols, LPCTSTR TableElement, BOOL WantTHead, BOOL WantTFoot)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x62, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRows, NumCols, TableElement, WantTHead, WantTFoot);
}

void Range::InsertWithTemplate(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Range::InsertCDATASection()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::Validate()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::InsertReplaceableText(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void Range::ContractCell(long ContractDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ContractDirection);
}

BOOL Range::GetReadOnlyContainer()
{
	BOOL result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetReadOnlyContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Range::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::Select()
{
	InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Range::GetDuplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Range::Layout()
{
	BOOL result;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Range::GetCollapsedContainerTags()
{
	BOOL result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetCollapsedContainerTags(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Range::GetCollapsedTags()
{
	BOOL result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Range::GetCanDelete()
{
	BOOL result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Range::GetCanRemoveContainerTags()
{
	BOOL result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Range::GetHiddenContainer()
{
	BOOL result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetHiddenContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Range::GetHidden()
{
	BOOL result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString Range::GetContainerStyle()
{
	CString result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetContainerStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::FindInsertLocation(LPCTSTR ElementName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName, Forward);
	return result;
}

void Range::DropFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

BOOL Range::GetSVCollapsedContainer()
{
	BOOL result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetSVCollapsedContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Selection properties

/////////////////////////////////////////////////////////////////////////////
// Selection operations

void Selection::TypeText(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void Selection::Cut()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Copy()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Paste()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Delete()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MoveLeft(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Selection::MoveRight(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Selection::MoveUp(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Selection::MoveDown(long MovementType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MovementType);
}

void Selection::MoveColumnLeft()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MoveColumnRight()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MoveRowUp()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MoveRowDown()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MergeCellLeft()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MergeCellRight()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MergeCellUp()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MergeCellDown()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SplitCellColumn()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SplitCellRow()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertRowsAbove(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Selection::InsertRowsBelow(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Selection::InsertColumnsLeft(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Selection::InsertColumnsRight(long number)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 number);
}

void Selection::HomeKey(long unit, long extend)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 unit, extend);
}

void Selection::EndKey(long unit, long extend)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 unit, extend);
}

LPDISPATCH Selection::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Selection::GetHorizontalAlignment()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Selection::SetHorizontalAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Selection::GotoNext(long GotoItem)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GotoItem);
}

void Selection::GotoPrevious(long GotoItem)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GotoItem);
}

void Selection::Collapse(long CollapseDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CollapseDirection);
}

void Selection::PasteString(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

void Selection::InsertForm(long FormElement)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FormElement);
}

void Selection::InsertElement(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Selection::InsertElementWithRequired(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Selection::GetContainerName()
{
	CString result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetContainerName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Selection::RemoveContainerTags()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SplitContainer()
{
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Selection::GetContainerAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void Selection::SetContainerAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, lpszNewValue);
}

void Selection::InsertComment()
{
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertBreak()
{
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertHorizontalRule()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertNBSP()
{
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::JoinElementToPreceding()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertEntity(LPCTSTR EntityName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName);
}

void Selection::Surround(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Selection::SelectElement()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::TypingSplit()
{
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::DeleteColumn()
{
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::DeleteRow()
{
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertTable(long NumRows, long NumCols, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRows, NumCols, BGColor, TableWidth, TableWidthUnit, TableBorder, CellPadding, CellSpacing);
}

void Selection::InsertCaption()
{
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Indent()
{
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Outdent()
{
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertImage(LPCTSTR Src, LPCTSTR Alt, LPCTSTR Align, LPCTSTR Width, LPCTSTR Height, LPCTSTR Border)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Src, Alt, Align, Width, Height, Border);
}

CString Selection::GetStyle()
{
	CString result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Selection::PageUp()
{
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::PageDown()
{
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::ToggleTableCellType()
{
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Selection::GetElementName(long AncestorNum)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		AncestorNum);
	return result;
}

CString Selection::GetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName, ElementName, SkipNum);
	return result;
}

void Selection::SetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, ElementName, SkipNum, lpszNewValue);
}

BOOL Selection::GetIsParentElement(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

void Selection::ListIndent(VARIANT* ElementName)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Selection::ListOutdent(VARIANT* ElementName)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Selection::GetText()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::GetIsInsertionPoint()
{
	BOOL result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::InsertLink(LPCTSTR Href, LPCTSTR target)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Href, target);
}

LPDISPATCH Selection::GetContainerNode()
{
	LPDISPATCH result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Selection::SelectBeforeNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Selection::SelectAfterNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Selection::SelectNodeContents(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

void Selection::SelectAfterContainer()
{
	InvokeHelper(0x48, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SelectBeforeContainer()
{
	InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SelectContainerContents()
{
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Selection::GetFind()
{
	LPDISPATCH result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Selection::BasicPaste()
{
	InvokeHelper(0x4c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::PasteStringWithInterpret(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

BOOL Selection::GetCanInsert(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Selection::GetCanChange(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Selection::GetCanSurround(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Selection::GetCanPaste(LPCTSTR String, BOOL interpret)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		String, interpret);
	return result;
}

BOOL Selection::GetIsValid()
{
	BOOL result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::MoveToDocumentStart()
{
	InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::MoveToDocumentEnd()
{
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::SelectAll()
{
	InvokeHelper(0x55, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL Selection::ExtendTo(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Selection::GetContains(LPDISPATCH Selection, BOOL IncludeSelOnEdge)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, IncludeSelOnEdge);
	return result;
}

BOOL Selection::GetIsEqual(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Selection::GetOverlaps(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Selection::MoveToElement(LPCTSTR ElementName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName, Forward);
	return result;
}

BOOL Selection::GetCanInsertText()
{
	BOOL result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::InsertProcessingInstruction()
{
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Selection::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Selection::GetIsAdjacent(LPDISPATCH Selection)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection);
	return result;
}

BOOL Selection::GetIsLessThan(LPDISPATCH Selection, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, OrEqual);
	return result;
}

BOOL Selection::GetIsGreaterThan(LPDISPATCH Selection, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Selection, OrEqual);
	return result;
}

BOOL Selection::GetHasAttribute(LPCTSTR attrName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		attrName);
	return result;
}

void Selection::InsertCALSTable(long NumRows, long NumCols, LPCTSTR TableElement, BOOL WantTHead, BOOL WantTFoot)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x62, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRows, NumCols, TableElement, WantTHead, WantTFoot);
}

void Selection::InsertWithTemplate(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

void Selection::InsertCDATASection()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::Validate()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::InsertReplaceableText(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void Selection::ContractCell(long ContractDirection)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ContractDirection);
}

BOOL Selection::GetReadOnlyContainer()
{
	BOOL result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetReadOnlyContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Selection::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::Select()
{
	InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Selection::GetDuplicate()
{
	LPDISPATCH result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Selection::Layout()
{
	BOOL result;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Selection::GetCollapsedContainerTags()
{
	BOOL result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetCollapsedContainerTags(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Selection::GetCollapsedTags()
{
	BOOL result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Selection::GetCanDelete()
{
	BOOL result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Selection::GetCanRemoveContainerTags()
{
	BOOL result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Selection::GetHiddenContainer()
{
	BOOL result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetHiddenContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Selection::GetHidden()
{
	BOOL result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString Selection::GetContainerStyle()
{
	CString result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetContainerStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::FindInsertLocation(LPCTSTR ElementName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName, Forward);
	return result;
}

void Selection::DropFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

BOOL Selection::GetSVCollapsedContainer()
{
	BOOL result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetSVCollapsedContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Font properties

/////////////////////////////////////////////////////////////////////////////
// Font operations

CString Font::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Font::GetBold()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetBold(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetItalic()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetItalic(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetUnderline()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetUnderline(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetStrong()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetStrong(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetEmphasis()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetEmphasis(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetTeletype()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetTeletype(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Font::GetCitation()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Font::SetCitation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString Font::GetSize()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetSize(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Font::GetColor()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Font::SetColor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void Font::Grow()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Font::Shrink()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Find properties

/////////////////////////////////////////////////////////////////////////////
// Find operations

BOOL Find::Execute(LPCTSTR FindString, LPCTSTR ReplaceString, LPCTSTR ConstraintString, BOOL MatchCase, BOOL MatchWholeWords, BOOL MatchPatterns, BOOL Forward, BOOL Wrap, long action, BOOL SetFindDialogOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FindString, ReplaceString, ConstraintString, MatchCase, MatchWholeWords, MatchPatterns, Forward, Wrap, action, SetFindDialogOptions);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DocumentProperties properties

/////////////////////////////////////////////////////////////////////////////
// DocumentProperties operations

LPDISPATCH DocumentProperties::item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long DocumentProperties::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentProperties::Add(LPCTSTR name, LPCTSTR value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, value);
}


/////////////////////////////////////////////////////////////////////////////
// DocumentProperty properties

/////////////////////////////////////////////////////////////////////////////
// DocumentProperty operations

CString DocumentProperty::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DocumentProperty::GetValue()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DocumentProperty::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void DocumentProperty::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// DOMCharacterReference properties

/////////////////////////////////////////////////////////////////////////////
// DOMCharacterReference operations

LPDISPATCH DOMCharacterReference::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCharacterReference::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCharacterReference::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCharacterReference::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCharacterReference::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCharacterReference::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCharacterReference::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCharacterReference::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCharacterReference::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterReference::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterReference::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReference::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FX properties

/////////////////////////////////////////////////////////////////////////////
// FX operations

BOOL FX::CopyFile(LPCTSTR SrcFile, LPCTSTR DstFile, VARIANT* ForceUpdate)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		SrcFile, DstFile, ForceUpdate);
	return result;
}

BOOL FX::ShowDialog(LPCTSTR dialogName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dialogName);
	return result;
}

BOOL FX::setAttribute(LPCTSTR ElementName, LPCTSTR AttributeName, LPCTSTR AttributeValue, LPCTSTR Relative)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName, AttributeName, AttributeValue, Relative);
	return result;
}

BOOL FX::RemoveAll(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL FX::DTC(LPCTSTR Guid)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Guid);
	return result;
}

BOOL FX::HTML(VARIANT* HTMLSrc, VARIANT* SrcFile, VARIANT* ElementName, VARIANT* ElementID, VARIANT* location, VARIANT* LeaveSelected)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		HTMLSrc, SrcFile, ElementName, ElementID, location, LeaveSelected);
	return result;
}

BOOL FX::Surround(LPCTSTR Before, LPCTSTR After, VARIANT* LeaveSelected)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Before, After, LeaveSelected);
	return result;
}

CString FX::GetPath()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL FX::SelectDropPoint()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Global properties

/////////////////////////////////////////////////////////////////////////////
// _Global operations

LPDISPATCH _Global::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetDocuments()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetActiveDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Global::GetResourceManager()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Application properties

/////////////////////////////////////////////////////////////////////////////
// _Application operations

LPDISPATCH _Application::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetDocuments()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetActiveDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Application::GetVisible()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::Quit(long SaveChanges)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveChanges);
}

void _Application::Help(long HelpType, long ContextID)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HelpType, ContextID);
}

void _Application::Run(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

CString _Application::GetProjectDirectory()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetFx()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetPath()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::PathToURL(LPCTSTR Path, VARIANT* Base)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Path, Base);
	return result;
}

CString _Application::URLToPath(LPCTSTR URL, VARIANT* Base)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		URL, Base);
	return result;
}

CString _Application::UniqueFileName(LPCTSTR Directory, LPCTSTR Prefix, VARIANT* Extension)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Directory, Prefix, Extension);
	return result;
}

BOOL _Application::FileExists(LPCTSTR Path)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Path);
	return result;
}

BOOL _Application::ReadableFileExists(LPCTSTR Path)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Path);
	return result;
}

BOOL _Application::WritableFileExists(LPCTSTR Path)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Path);
	return result;
}

BOOL _Application::WritableDirExists(LPCTSTR Path)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Path);
	return result;
}

CString _Application::FileToString(LPCTSTR Path)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Path);
	return result;
}

void _Application::Alert(LPCTSTR Msg, VARIANT* Title)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Msg, Title);
}

BOOL _Application::Confirm(LPCTSTR Msg, VARIANT* Title)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Msg, Title);
	return result;
}

CString _Application::Prompt(LPCTSTR Msg, VARIANT* Text, VARIANT* length, VARIANT* MaxLength, VARIANT* Title)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Msg, Text, length, MaxLength, Title);
	return result;
}

long _Application::MessageBox(LPCTSTR Msg, long Btns, VARIANT* Title)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PVARIANT;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Msg, Btns, Title);
	return result;
}

long _Application::NoticeBox(LPCTSTR Msg, LPCTSTR Btn1, VARIANT* Btn2, VARIANT* Btn3, VARIANT* Title)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Msg, Btn1, Btn2, Btn3, Title);
	return result;
}

LPDISPATCH _Application::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Application::GetWindowHandle()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::EnableModeless(BOOL prop)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 prop);
}

void _Application::HelpFinder(LPCTSTR HelpFile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HelpFile);
}

void _Application::HelpContext(LPCTSTR HelpFile, long ContextID)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HelpFile, ContextID);
}

void _Application::RefreshMacros()
{
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::RunKeyedMacro(LPCTSTR KeyString)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 KeyString);
}

LPDISPATCH _Application::GetDropPoint()
{
	LPDISPATCH result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::DisableMacro(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

CString _Application::GetMacroFile()
{
	CString result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::Beep()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _Application::GetAssetsPath()
{
	CString result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::DisablePlainTextView()
{
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Application::GetIsDocumentOpen(LPDISPATCH Document)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Document);
	return result;
}

BOOL _Application::CopyAssetFile(LPCTSTR SrcFile, LPCTSTR DstFile, BOOL ForceUpdate)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		SrcFile, DstFile, ForceUpdate);
	return result;
}

void _Application::ShowPage(LPCTSTR URL)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL);
}

long _Application::GetDisplayAlerts()
{
	long result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Application::SetDisplayAlerts(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Application::GetActiveInPlaceControl()
{
	LPDISPATCH result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetMouseOverNode()
{
	LPDISPATCH result;
	InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::SetCursor(long cursorType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cursorType);
}

void _Application::SetStatusText(LPCTSTR statusText)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 statusText);
}

void _Application::AppendMacro(LPCTSTR Label, LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Label, MacroName);
}

LPDISPATCH _Application::GetCustomProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetNewDocumentType()
{
	LPDISPATCH result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Application::GetDropFileCount()
{
	long result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _Application::GetDropFileName(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

BOOL _Application::GetInitComplete()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetResourceManager()
{
	LPDISPATCH result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::PreventExit(LPCTSTR appName, LPCTSTR msgText)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 appName, msgText);
}

void _Application::AllowExit(LPCTSTR appName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 appName);
}

LPUNKNOWN _Application::GetDropDataObject()
{
	LPUNKNOWN result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

BOOL _Application::AcceptDropFormat(VARIANT* dropFormat, LPCTSTR formatName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_BSTR;
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dropFormat, formatName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Documents properties

/////////////////////////////////////////////////////////////////////////////
// Documents operations

LPDISPATCH Documents::item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long Documents::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Documents::Open(LPCTSTR FileName, long ViewType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, ViewType);
	return result;
}

LPDISPATCH Documents::Add(BOOL UseDefaultTemplate)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		UseDefaultTemplate);
	return result;
}

void Documents::Save()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Documents::Close()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Documents::OpenTemplate(LPCTSTR FileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName);
	return result;
}

LPDISPATCH Documents::OpenString(LPCTSTR inputString, long ViewType, LPCTSTR FileName, BOOL asTemplate, BOOL IsXML, BOOL wfEdit)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		inputString, ViewType, FileName, asTemplate, IsXML, wfEdit);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBars properties

/////////////////////////////////////////////////////////////////////////////
// CommandBars operations

LPDISPATCH CommandBars::Add(LPCTSTR name, VARIANT* positon)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, positon);
	return result;
}

LPDISPATCH CommandBars::FindControl(long Type, long cmdId, VARIANT* Visible, VARIANT* recursive)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, cmdId, Visible, recursive);
	return result;
}

long CommandBars::GetCount()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::GetItem(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBar properties

/////////////////////////////////////////////////////////////////////////////
// CommandBar operations

void CommandBar::Delete()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBar::Reset()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH CommandBar::FindControl(long Type, long cmdId, VARIANT* Visible, VARIANT* recursive)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, cmdId, Visible, recursive);
	return result;
}

long CommandBar::GetBuiltIn()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBar::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBar::GetEnabled()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBar::GetName()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBar::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CommandBar::GetPosition()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBar::GetVisible()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBar::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarControl properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarControl operations

void CommandBarControl::Copy(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarControl::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarControl::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarControl::Move(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarControl::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarControl::GetBuiltIn()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetId()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetType()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarControl::GetBeginGroup()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetBeginGroup(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarControl::GetDescriptionText()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetDescriptionText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarControl::GetEnabled()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarControl::GetHeight()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarControl::GetLeft()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarControl::GetOnAction()
{
	VARIANT result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetOnAction(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarControl::GetState()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarControl::GetTooltipText()
{
	VARIANT result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetTooltipText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarControl::GetTop()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarControl::GetVisible()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarControl::GetWidth()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarControls properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarControls operations

LPDISPATCH CommandBarControls::Add(long controlType, VARIANT* commandId, VARIANT* Before, VARIANT* param)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		controlType, commandId, Before, param);
	return result;
}

long CommandBarControls::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBarControls::GetItem(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// InPlaceControl properties

/////////////////////////////////////////////////////////////////////////////
// InPlaceControl operations

LPDISPATCH InPlaceControl::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH InPlaceControl::GetNode()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT InPlaceControl::GetControl()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long InPlaceControl::GetUserMovedIntoControl()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long InPlaceControl::GetUpdateFromDocument()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT InPlaceControl::GetNextEventParam()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetShouldCreate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long InPlaceControl::GetWidth()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long InPlaceControl::GetHeight()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// NameVariantProperties properties

/////////////////////////////////////////////////////////////////////////////
// NameVariantProperties operations

LPDISPATCH NameVariantProperties::item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long NameVariantProperties::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void NameVariantProperties::Add(LPCTSTR name, const VARIANT& value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, &value);
}


/////////////////////////////////////////////////////////////////////////////
// NameVariantProperty properties

/////////////////////////////////////////////////////////////////////////////
// NameVariantProperty operations

CString NameVariantProperty::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT NameVariantProperty::GetValue()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void NameVariantProperty::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _Resman properties

/////////////////////////////////////////////////////////////////////////////
// _Resman operations

LPDISPATCH _Resman::GetAssets()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Resman::GetDesktop()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Resman::GetFtpNeighborhood()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Resman::GetLocalSites()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Resman::AddTab(LPCTSTR tabName, LPCTSTR Guid)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, Guid);
}

void _Resman::SelectTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

void _Resman::RemoveTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

void _Resman::RemoveAllTabs()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Resman::GetControlInTab(LPCTSTR tabName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		tabName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Assets properties

/////////////////////////////////////////////////////////////////////////////
// Assets operations

LPDISPATCH Assets::GetWebBrowser()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Assets::SelectFolder(LPCTSTR Path)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path);
}

void Assets::Refresh()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// ApplicationEvents properties

/////////////////////////////////////////////////////////////////////////////
// ApplicationEvents operations

void ApplicationEvents::SelectionChanged()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ApplicationEvents::DocumentChanged()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ApplicationEvents::Quit()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// DocumentEvents properties

/////////////////////////////////////////////////////////////////////////////
// DocumentEvents operations

void DocumentEvents::New()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DocumentEvents::Open()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DocumentEvents::Close()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// DOMEntity properties

/////////////////////////////////////////////////////////////////////////////
// DOMEntity operations

LPDISPATCH DOMEntity::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMEntity::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMEntity::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntity::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMEntity::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMEntity::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMEntity::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMEntity::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMEntity::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntity::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntity::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntity::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMEntity::GetPublicId()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntity::GetSystemId()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntity::GetNotationName()
{
	CString result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMNotation properties

/////////////////////////////////////////////////////////////////////////////
// DOMNotation operations

LPDISPATCH DOMNotation::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMNotation::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMNotation::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMNotation::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMNotation::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMNotation::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMNotation::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMNotation::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMNotation::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNotation::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNotation::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotation::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMNotation::GetPublicId()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMNotation::GetSystemId()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarButton properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarButton operations

void CommandBarButton::Copy(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarButton::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::Move(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarButton::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarButton::GetBuiltIn()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetId()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetType()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarButton::GetBeginGroup()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBeginGroup(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarButton::GetDescriptionText()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetDescriptionText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarButton::GetEnabled()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetHeight()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetLeft()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarButton::GetOnAction()
{
	VARIANT result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetOnAction(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarButton::GetState()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarButton::GetTooltipText()
{
	VARIANT result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetTooltipText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarButton::GetTop()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetVisible()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetWidth()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CommandBarButton::CopyFace()
{
	InvokeHelper(0x10001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::PasteFace()
{
	InvokeHelper(0x10002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarButton::GetBuiltInFace()
{
	long result;
	InvokeHelper(0x10003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBuiltInFace(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarButton::GetFaceId()
{
	long result;
	InvokeHelper(0x10004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetFaceId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup operations

void CommandBarPopup::Copy(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarPopup::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::Move(VARIANT* toBar, VARIANT* Before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, Before);
}

void CommandBarPopup::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CommandBarPopup::GetBuiltIn()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetId()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetType()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetBeginGroup()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetBeginGroup(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarPopup::GetDescriptionText()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetDescriptionText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarPopup::GetEnabled()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetEnabled(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarPopup::GetHeight()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarPopup::GetLeft()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarPopup::GetOnAction()
{
	VARIANT result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetOnAction(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarPopup::GetState()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT CommandBarPopup::GetTooltipText()
{
	VARIANT result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetTooltipText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CommandBarPopup::GetTop()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarPopup::GetVisible()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CommandBarPopup::GetWidth()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CommandBarPopup::GetCaption()
{
	CString result;
	InvokeHelper(0x20001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarPopup::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x20002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
