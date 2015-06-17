// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "xmetal90.h"

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

LPDISPATCH DOMNamedNodeMap::getNamedItemNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

LPDISPATCH DOMNamedNodeMap::setNamedItemNS(LPDISPATCH node)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		node);
	return result;
}

LPDISPATCH DOMNamedNodeMap::removeNamedItemNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
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

CString DOMAttr::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttr::GetPrefix()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttr::SetPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString DOMAttr::GetLocalName()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
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

CString DOMElement::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElement::GetPrefix()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMElement::SetPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString DOMElement::GetLocalName()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElement::getAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x193, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

void DOMElement::setAttributeNS(LPCTSTR namespaceName, LPCTSTR localName, LPCTSTR attrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x194, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceName, localName, attrValue);
}

void DOMElement::removeAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x195, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceName, localName);
}

LPDISPATCH DOMElement::getAttributeNodeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x196, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

LPDISPATCH DOMElement::setAttributeNodeNS(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x197, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElement::getElementsByTagNameNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x198, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

BOOL DOMElement::hasAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x199, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

LPDISPATCH DOMElement::getNodesByXPath(LPCTSTR xpathExpression)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x19a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression);
	return result;
}

LPDISPATCH DOMElement::setAttributeNodeWF(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x19b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
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

void DOMDocumentType::addInPlaceControlOverride(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, LPCTSTR userData, BOOL useBmpPrinting)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 selector, progID, scriptPrefix, userData, useBmpPrinting);
}

CString DOMDocumentType::GetParentElementType(LPCTSTR elementType, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		elementType, index);
	return result;
}

VARIANT DOMDocumentType::GetParentElementTypes(LPCTSTR elementType)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		elementType);
	return result;
}

BOOL DOMDocumentType::GetHasParentElementType(LPCTSTR elementType, LPCTSTR ParentElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementType, ParentElementName);
	return result;
}

CString DOMDocumentType::GetChildElementType(LPCTSTR elementType, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		elementType, index);
	return result;
}

VARIANT DOMDocumentType::GetChildElementTypes(LPCTSTR elementType)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		elementType);
	return result;
}

BOOL DOMDocumentType::GetHasChildElementType(LPCTSTR elementType, LPCTSTR ChildElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementType, ChildElementName);
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
// DocumentHost properties

/////////////////////////////////////////////////////////////////////////////
// DocumentHost operations

void DocumentHost::Run(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

BOOL DocumentHost::RunKeyedMacro(LPCTSTR KeyString)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		KeyString);
	return result;
}

void DocumentHost::DisableMacro(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

void DocumentHost::PushInMacro(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

void DocumentHost::Beep()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString DocumentHost::PathToURL(LPCTSTR Path, VARIANT* Base)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Path, Base);
	return result;
}

CString DocumentHost::URLToPath(LPCTSTR URL, VARIANT* Base)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		URL, Base);
	return result;
}

void DocumentHost::Alert(LPCTSTR Msg, VARIANT* Title)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Msg, Title);
}

BOOL DocumentHost::Confirm(LPCTSTR Msg, VARIANT* Title)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Msg, Title);
	return result;
}

CString DocumentHost::Prompt(LPCTSTR Msg, VARIANT* Text, VARIANT* length, VARIANT* MaxLength, VARIANT* Title)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Msg, Text, length, MaxLength, Title);
	return result;
}

long DocumentHost::MessageBox(LPCTSTR Msg, long Btns, VARIANT* Title)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PVARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Msg, Btns, Title);
	return result;
}

long DocumentHost::NoticeBox(LPCTSTR Msg, LPCTSTR Btn1, VARIANT* Btn2, VARIANT* Btn3, VARIANT* Title)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Msg, Btn1, Btn2, Btn3, Title);
	return result;
}

long DocumentHost::GetDisplayAlerts()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void DocumentHost::SetDisplayAlerts(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void DocumentHost::SetCursor(long cursorType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cursorType);
}

void DocumentHost::SetStatusText(LPCTSTR statusText)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 statusText);
}

VARIANT DocumentHost::CreateFormDlg(LPCTSTR formFileName, VARIANT* DOMNode)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		formFileName, DOMNode);
	return result;
}

LPDISPATCH DocumentHost::QueryService(LPCTSTR serviceName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		serviceName);
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
// StyleSheetList properties

/////////////////////////////////////////////////////////////////////////////
// StyleSheetList operations

long StyleSheetList::GetLength()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH StyleSheetList::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleSheet properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleSheet operations

CString DOMCSSStyleSheet::GetType()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL DOMCSSStyleSheet::GetDisabled()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void DOMCSSStyleSheet::SetDisabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH DOMCSSStyleSheet::GetOwnerNode()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleSheet::GetParentStyleSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DOMCSSStyleSheet::GetHref()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCSSStyleSheet::GetTitle()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleSheet::GetMedia()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleSheet::GetOwnerRule()
{
	LPDISPATCH result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleSheet::GetCssRules()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long DOMCSSStyleSheet::insertRule(LPCTSTR rule, long index)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		rule, index);
	return result;
}

void DOMCSSStyleSheet::deleteRule(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x104, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}


/////////////////////////////////////////////////////////////////////////////
// StyleSheet properties

/////////////////////////////////////////////////////////////////////////////
// StyleSheet operations

CString StyleSheet::GetType()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL StyleSheet::GetDisabled()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void StyleSheet::SetDisabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH StyleSheet::GetOwnerNode()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH StyleSheet::GetParentStyleSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString StyleSheet::GetHref()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString StyleSheet::GetTitle()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH StyleSheet::GetMedia()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSRule properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSRule operations

short DOMCSSRule::GetType()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCSSRule::GetCssText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCSSRule::SetCssText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCSSRule::GetParentStyleSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSRule::GetParentRule()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSRuleList properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSRuleList operations

long DOMCSSRuleList::GetLength()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSRuleList::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Customizations properties

/////////////////////////////////////////////////////////////////////////////
// Customizations operations

LPDISPATCH Customizations::GetParagraphs()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Customizations::GetLists()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Customizations::GetImages()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Customizations::GetTogglingElements()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Customizations::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Customizations::GetElementPropList()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraphs properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraphs operations

LPDISPATCH TreatAsParagraphs::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long TreatAsParagraphs::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraph properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraph operations

CString TreatAsParagraph::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsParagraph::GetParent()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsLists properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsLists operations

LPDISPATCH TreatAsLists::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long TreatAsLists::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsList properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsList operations

CString TreatAsList::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long TreatAsList::GetType()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString TreatAsList::GetListHeader()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsList::GetListItem()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsList::GetTerm()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsList::GetDefinition()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsImages properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsImages operations

LPDISPATCH TreatAsImages::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long TreatAsImages::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsImage properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsImage operations

CString TreatAsImage::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetSource()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetHeight()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetWidth()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetAltText()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetVerticalAlign()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsImage::GetScale()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TogglingElements properties

/////////////////////////////////////////////////////////////////////////////
// TogglingElements operations

LPDISPATCH TogglingElements::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long TogglingElements::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString TogglingElements::GetBold()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TogglingElements::GetItalic()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TogglingElements::GetUnderline()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TogglingElement properties

/////////////////////////////////////////////////////////////////////////////
// TogglingElement operations

CString TogglingElement::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TogglingElement::GetMacroName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsLinks properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsLinks operations

LPDISPATCH TreatAsLinks::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long TreatAsLinks::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// TreatAsLink properties

/////////////////////////////////////////////////////////////////////////////
// TreatAsLink operations

CString TreatAsLink::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsLink::GetParentList()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsLink::GetSource()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL TreatAsLink::GetEnableBuiltInChooser()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString TreatAsLink::GetChooserTitleString()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString TreatAsLink::GetChooserFilterString()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL TreatAsLink::GetEnableBuiltInFetcher()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL TreatAsLink::GetEnableRebase()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL TreatAsLink::GetEnableFolderLink()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ElementProps properties

/////////////////////////////////////////////////////////////////////////////
// ElementProps operations

LPDISPATCH ElementProps::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ElementProps::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ElementProp properties

/////////////////////////////////////////////////////////////////////////////
// ElementProp operations

CString ElementProp::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ElementProp::GetLongDescription()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ElementProp::GetShortDescription()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
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

void Selection::InsertLink(LPCTSTR href, LPCTSTR target)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 href, target);
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

void Selection::TypeTab(BOOL shift)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 shift);
}

void Selection::ToggleInline(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

BOOL Selection::GetCanSplitContainer(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Selection::GetCanJoinElementToPreceding()
{
	BOOL result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SplitToElementType(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Selection::GetStyleElement()
{
	CString result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetStyleElement(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::GetNonRemovableContainer()
{
	BOOL result;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetNonRemovableContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Selection::FindPasteLocation(LPCTSTR String, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		String, Forward);
	return result;
}

BOOL Selection::GetWritePermittedContainer()
{
	BOOL result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Selection::SetWritePermittedContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void Selection::PasteStringAsText(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

BOOL Selection::GetInContextOfType(LPCTSTR ContextType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ContextType);
	return result;
}

BOOL Selection::GetIsParentElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

BOOL Selection::GetCanInsertNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Selection::InsertElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Selection::InsertElementWithRequiredNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Selection::InsertWithTemplateNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

LPDISPATCH Selection::GetCanInsertList()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetCanChangeList()
{
	LPDISPATCH result;
	InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetValidationErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Selection::GetElementNameNS(long AncestorNum)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		AncestorNum);
	return result;
}

BOOL Selection::GetCanChangeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

CString Selection::GetContainerNameNS()
{
	CString result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetContainerNameNS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Selection::GetStyleNS()
{
	CString result;
	InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetStyleNS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::GetCanSplitContainerNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Selection::SplitToElementTypeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Selection::GetCanSurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Selection::SurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Selection::ToggleInlineNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Selection::FindInsertLocationNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x9d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName, Forward);
	return result;
}

BOOL Selection::MoveToElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName, Forward);
	return result;
}

void Selection::ListIndentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Selection::ListOutdentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Selection::GetHasAttributeNS(LPCTSTR namespaceURI, LPCTSTR localName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		namespaceURI, localName);
	return result;
}

CString Selection::GetContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrNamespaceURI, attrLocalName);
	return result;
}

void Selection::SetContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrNamespaceURI, attrLocalName, lpszNewValue);
}

CString Selection::GetElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum);
	return result;
}

void Selection::SetElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0xa3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum, lpszNewValue);
}

void Selection::RejectAllChanges()
{
	InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Selection::AcceptAllChanges()
{
	InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Selection::GetTextWithRM()
{
	CString result;
	InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetTextWithRM(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::GetCanPasteStrict(LPCTSTR String, BOOL interpret)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		String, interpret);
	return result;
}

void Selection::ToggleList(long type)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x107, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 type);
}

long Selection::GetScreenTop(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Selection::GetScreenLeft(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Selection::GetScreenBottom(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Selection::GetScreenRight(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

BOOL Selection::GetIsPointInside(long screenX, long screenY)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		screenX, screenY);
	return result;
}

BOOL Selection::SelectNodeContentsAt(LPDISPATCH node, long offset, long length, LPCTSTR hint)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x10d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node, offset, length, hint);
	return result;
}

CString Selection::GetSelectionLocation()
{
	CString result;
	InvokeHelper(0x10e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Selection::SetSelectionLocation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x10e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Selection::CanSplitTable(BOOL belowThisRow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		belowThisRow);
	return result;
}

void Selection::SplitTable(BOOL belowThisRow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x110, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 belowThisRow);
}

BOOL Selection::CanSplitTableGroup(BOOL belowThisRow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x111, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		belowThisRow);
	return result;
}

void Selection::SplitTableGroup(BOOL belowThisRow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x112, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 belowThisRow);
}

BOOL Selection::CanMergeTable(BOOL withTableBelow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x113, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		withTableBelow);
	return result;
}

void Selection::MergeTable(BOOL withTableBelow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x114, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 withTableBelow);
}


/////////////////////////////////////////////////////////////////////////////
// _Font properties

/////////////////////////////////////////////////////////////////////////////
// _Font operations

CString _Font::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Font::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Font::GetBold()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetBold(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetItalic()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetItalic(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetUnderline()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetUnderline(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetStrong()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetStrong(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetEmphasis()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetEmphasis(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetTeletype()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetTeletype(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Font::GetCitation()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Font::SetCitation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Font::GetSize()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Font::SetSize(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Font::GetColor()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Font::SetColor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _Font::Grow()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Font::Shrink()
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

void Range::InsertLink(LPCTSTR href, LPCTSTR target)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 href, target);
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

void Range::TypeTab(BOOL shift)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 shift);
}

void Range::ToggleInline(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

BOOL Range::GetCanSplitContainer(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL Range::GetCanJoinElementToPreceding()
{
	BOOL result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SplitToElementType(LPCTSTR ElementName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName);
}

CString Range::GetStyleElement()
{
	CString result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetStyleElement(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::GetNonRemovableContainer()
{
	BOOL result;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetNonRemovableContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL Range::FindPasteLocation(LPCTSTR String, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		String, Forward);
	return result;
}

BOOL Range::GetWritePermittedContainer()
{
	BOOL result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Range::SetWritePermittedContainer(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void Range::PasteStringAsText(LPCTSTR String)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 String);
}

BOOL Range::GetInContextOfType(LPCTSTR ContextType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ContextType);
	return result;
}

BOOL Range::GetIsParentElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

BOOL Range::GetCanInsertNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Range::InsertElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Range::InsertElementWithRequiredNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Range::InsertWithTemplateNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

LPDISPATCH Range::GetCanInsertList()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Range::GetCanChangeList()
{
	LPDISPATCH result;
	InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Range::GetValidationErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Range::GetElementNameNS(long AncestorNum)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		AncestorNum);
	return result;
}

BOOL Range::GetCanChangeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

CString Range::GetContainerNameNS()
{
	CString result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetContainerNameNS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Range::GetStyleNS()
{
	CString result;
	InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetStyleNS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::GetCanSplitContainerNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Range::SplitToElementTypeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Range::GetCanSurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName);
	return result;
}

void Range::SurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Range::ToggleInlineNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Range::FindInsertLocationNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x9d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName, Forward);
	return result;
}

BOOL Range::MoveToElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		elementNamespaceURI, elementLocalName, Forward);
	return result;
}

void Range::ListIndentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

void Range::ListOutdentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elementNamespaceURI, elementLocalName);
}

BOOL Range::GetHasAttributeNS(LPCTSTR namespaceURI, LPCTSTR localName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		namespaceURI, localName);
	return result;
}

CString Range::GetContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrNamespaceURI, attrLocalName);
	return result;
}

void Range::SetContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrNamespaceURI, attrLocalName, lpszNewValue);
}

CString Range::GetElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum);
	return result;
}

void Range::SetElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0xa3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum, lpszNewValue);
}

void Range::RejectAllChanges()
{
	InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Range::AcceptAllChanges()
{
	InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Range::GetTextWithRM()
{
	CString result;
	InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetTextWithRM(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::GetCanPasteStrict(LPCTSTR String, BOOL interpret)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		String, interpret);
	return result;
}

void Range::ToggleList(long type)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x107, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 type);
}

long Range::GetScreenTop(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Range::GetScreenLeft(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Range::GetScreenBottom(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

long Range::GetScreenRight(long rectOrd)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		rectOrd);
	return result;
}

BOOL Range::GetIsPointInside(long screenX, long screenY)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		screenX, screenY);
	return result;
}

BOOL Range::SelectNodeContentsAt(LPDISPATCH node, long offset, long length, LPCTSTR hint)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x10d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node, offset, length, hint);
	return result;
}

CString Range::GetSelectionLocation()
{
	CString result;
	InvokeHelper(0x10e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Range::SetSelectionLocation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x10e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL Range::CanSplitTable(BOOL belowThisRow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		belowThisRow);
	return result;
}

void Range::SplitTable(BOOL belowThisRow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x110, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 belowThisRow);
}

BOOL Range::CanSplitTableGroup(BOOL belowThisRow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x111, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		belowThisRow);
	return result;
}

void Range::SplitTableGroup(BOOL belowThisRow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x112, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 belowThisRow);
}

BOOL Range::CanMergeTable(BOOL withTableBelow)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x113, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		withTableBelow);
	return result;
}

void Range::MergeTable(BOOL withTableBelow)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x114, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 withTableBelow);
}

short Range::GetShape()
{
	short result;
	InvokeHelper(0x207, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

LPDISPATCH Range::GetNodeItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x208, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH Range::GetRangeItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x209, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long Range::GetCount()
{
	long result;
	InvokeHelper(0x210, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
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

LPDISPATCH _Document::getNodesByXPath(LPCTSTR xpathExpression)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression);
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

CString _Document::UniqueAttributeValue(LPCTSTR AttributeName, LPCTSTR prefix, VARIANT* number)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		AttributeName, prefix, number);
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

void _Document::DeclareTextEntity(LPCTSTR EntityName, LPCTSTR entityContent, long notUsed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, entityContent, notUsed);
}

void _Document::DeclareExternalEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicName, FileName);
}

void _Document::DeclareGraphicEntity(LPCTSTR EntityName, LPCTSTR publicIdentifier, LPCTSTR systemIdentifier, LPCTSTR notationName, long notUsed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicIdentifier, systemIdentifier, notationName, notUsed);
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

CString _Document::CreatePreviewFile()
{
	CString result;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetCustomProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetStyleSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetIsInWellFormedEditingMode()
{
	BOOL result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetChangedNodesbyKey(LPCTSTR key)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		key);
	return result;
}

void _Document::ClearNodeChangedStatesbyKey(LPCTSTR key, LPDISPATCH inNode, BOOL deep)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key, inNode, deep);
}

void _Document::ClearAllChangedStatesbyKey(LPCTSTR key)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key);
}

BOOL _Document::GetNodeStatebyKey(LPCTSTR key, LPCTSTR stateName, LPDISPATCH inNode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, stateName, inNode);
	return result;
}

CString _Document::GetAllUsersMacroFile()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetCurrentUserMacroFile()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetXml()
{
	CString result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetCustomizations()
{
	LPDISPATCH result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetTrackRevisions()
{
	BOOL result;
	InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetTrackRevisions(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Document::GetMinimizeTagIcons()
{
	BOOL result;
	InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetMinimizeTagIcons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _Document::GetResourceSet()
{
	LPDISPATCH result;
	InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Document::GetDropText()
{
	CString result;
	InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetDropText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPUNKNOWN _Document::GetDropDataObject()
{
	LPUNKNOWN result;
	InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void _Document::DropNotAllowed()
{
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Document::GetDropPoint()
{
	LPDISPATCH result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetFormattingUpdating()
{
	BOOL result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetFormattingUpdating(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Document::GotoNextChange()
{
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::GotoPrevChange()
{
	InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Document::CanAcceptOrRejectChange()
{
	BOOL result;
	InvokeHelper(0x4f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::AcceptChange()
{
	InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::RejectChange()
{
	InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _Document::AcceptAllChanges()
{
	long result;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::RejectAllChanges()
{
	long result;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetValidationErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetCheckData()
{
	LPDISPATCH result;
	InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetMouseOverNode()
{
	LPDISPATCH result;
	InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetHost()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Document::MoveDropPoint(LPDISPATCH newDropPoint)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 newDropPoint);
}

LPDISPATCH _Document::GetDropRange()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::createElementNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, qualifiedName);
	return result;
}

LPDISPATCH _Document::createAttributeNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, qualifiedName);
	return result;
}

LPDISPATCH _Document::getElementsByTagNameNS(LPCTSTR namespaceURI, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, localName);
	return result;
}

CString _Document::GetXmlWithCT()
{
	CString result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetRMPreserveMode()
{
	BOOL result;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetRMPreserveMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Document::formatGraphicTable(LPDISPATCH tblNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tblNode);
}

LPDISPATCH _Document::GetActiveInPlaceControl()
{
	LPDISPATCH result;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::CreateMark(LPCTSTR ownerKey, long markID, long Flags, const VARIANT& userData, LPDISPATCH position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT VTS_DISPATCH;
	InvokeHelper(0x120, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ownerKey, markID, Flags, &userData, position);
	return result;
}

LPDISPATCH _Document::GetMarkWalker(LPCTSTR ownerKey)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		ownerKey);
	return result;
}

void _Document::SetMarkPresentationService(LPCTSTR ownerKey, long mpsType, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x122, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpsType, mpServiceImpl);
}

void _Document::SetCTMRulesService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x123, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpServiceImpl);
}

void _Document::SetImageService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x124, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpServiceImpl);
}

void _Document::EmptyClipboard()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Document::GetClipboard()
{
	LPDISPATCH result;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetDropClipboardText()
{
	BOOL result;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _Document::GetDropInternalText()
{
	BOOL result;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Document::DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_UNKNOWN;
	InvokeHelper(0x134, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		formatName, data);
	return result;
}

LPDISPATCH _Document::GetCRLocator()
{
	LPDISPATCH result;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Document::SetCRLocator(VARIANT* newValue)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _Document::GetReadOnlyHint()
{
	BOOL result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetReadOnlyHint(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _Document::createElementWF(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x137, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _Document::createAttributeWF(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x138, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _Document::createTextNodeWF(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x139, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

void _Document::attachTransclusion(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_I4;
	InvokeHelper(0x140, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, transNode, transResult);
}

void _Document::detachTransclusion(LPDISPATCH srcNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode);
}

void _Document::showHideTransclusion(LPDISPATCH srcNode, BOOL show)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x142, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, show);
}

void _Document::importNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x143, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

long _Document::GetAutoSetImageWidthHeight()
{
	long result;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Document::SetAutoSetImageWidthHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x144, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Document::GetAutoScaleImageWidth()
{
	long result;
	InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Document::SetAutoScaleImageWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Document::GetAutoScaleImageHeight()
{
	long result;
	InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Document::SetAutoScaleImageHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Document::attachTransclusionEx(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_I4;
	InvokeHelper(0x147, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, transNode, transResult);
}

void _Document::detachTransclusionEx(LPDISPATCH srcNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x148, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode);
}

void _Document::showHideTransclusionEx(LPDISPATCH srcNode, BOOL show)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x149, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, show);
}

CString _Document::getTextEntityReplacementText(LPCTSTR entName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x150, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		entName);
	return result;
}

BOOL _Document::GetDropTextIsMultiCell()
{
	BOOL result;
	InvokeHelper(0x151, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::HideEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x152, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

void _Document::ShowEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x153, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

LPDISPATCH _Document::GetEditAttributeNode()
{
	LPDISPATCH result;
	InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Document::GetEditAttributeName()
{
	CString result;
	InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Document::GetEditAttributeValue()
{
	CString result;
	InvokeHelper(0x156, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetEditAttributeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x156, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _Document::GetRefreshCssStyleDoc()
{
	LPDISPATCH result;
	InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Document::RefreshCssStyleToAppend(LPCTSTR cssToAppend)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x158, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cssToAppend);
}

void _Document::ShowXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x159, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _Document::HideXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x160, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _Document::UpdateXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x161, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _Document::OpenXIncludeTarget(LPDISPATCH xincludeNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 xincludeNode);
}

CString _Document::ExportWithXIncludesToXML()
{
	CString result;
	InvokeHelper(0x163, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetActiveXIncludeNode()
{
	LPDISPATCH result;
	InvokeHelper(0x164, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Document::IsXIncludeNode(LPDISPATCH node)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x165, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node);
	return result;
}

BOOL _Document::GetIsNamespaceAware()
{
	BOOL result;
	InvokeHelper(0x166, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::PurgeXIncludeCache()
{
	InvokeHelper(0x167, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::SetXIncludeFeature(long feature, VARIANT* val)
{
	static BYTE parms[] =
		VTS_I4 VTS_PVARIANT;
	InvokeHelper(0x168, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 feature, val);
}

LPDISPATCH _Document::GetLinkResolutionErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x169, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Document::ConvertXIncludeTargetToXML(LPCTSTR href, LPCTSTR xptr)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x16a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		href, xptr);
	return result;
}

void _Document::ExportWithXIncludesToFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x16b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

long _Document::GetXIncludeTargetState(LPDISPATCH xincludeNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x16c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		xincludeNode);
	return result;
}

void _Document::RegisterNonCopyableAttr(LPCTSTR elemNS, LPCTSTR elemName, LPCTSTR attrNS, LPCTSTR attrName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x16d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elemNS, elemName, attrNS, attrName);
}

BOOL _Document::GetBackgroundSpellchecking()
{
	BOOL result;
	InvokeHelper(0x16e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetBackgroundSpellchecking(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Document::GetSpellAutoCorrect()
{
	BOOL result;
	InvokeHelper(0x16f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetSpellAutoCorrect(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Document::IsSpellingCorrect(long mode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x170, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		mode);
	return result;
}

CString _Document::GetSpellingResult(long mode)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x171, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		mode);
	return result;
}

BOOL _Document::ReplaceWord(LPCTSTR word)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x172, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		word);
	return result;
}

BOOL _Document::IgnoreWordSpelling()
{
	BOOL result;
	InvokeHelper(0x173, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _Document::AddWordToDictionary()
{
	BOOL result;
	InvokeHelper(0x174, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetSpellCheckerService(LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x175, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 mpServiceImpl);
}

BOOL _Document::GetInlineMediaVisible()
{
	BOOL result;
	InvokeHelper(0x176, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Document::SetInlineMediaVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x176, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _Document::GetMsgHwnd()
{
	long result;
	InvokeHelper(0x177, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgMessage()
{
	long result;
	InvokeHelper(0x178, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgWParam()
{
	long result;
	InvokeHelper(0x179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgLParam()
{
	long result;
	InvokeHelper(0x17a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgTime()
{
	long result;
	InvokeHelper(0x17b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgX()
{
	long result;
	InvokeHelper(0x17c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetMsgY()
{
	long result;
	InvokeHelper(0x17d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Document::GetWindowHandle()
{
	long result;
	InvokeHelper(0x17e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Document::GetRangeNearestPoint(long screenX, long screenY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x17f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		screenX, screenY);
	return result;
}

void _Document::BeginMutations(LPCTSTR niceName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x180, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 niceName);
}

void _Document::EndMutations(BOOL didChange)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x181, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 didChange);
}

unsigned short _Document::GetNodeSpellLanguage(LPDISPATCH inNode)
{
	unsigned short result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x182, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		inNode);
	return result;
}

BOOL _Document::IsDummyNode(LPDISPATCH node)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x183, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node);
	return result;
}

long _Document::HighlightRange(LPCTSTR location, long highlightType, long highlightState, LPCTSTR hint)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x184, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		location, highlightType, highlightState, hint);
	return result;
}

long _Document::SetHighlightedRangeState(long hId, long hState)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x185, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		hId, hState);
	return result;
}

LPDISPATCH _Document::GetHighlightedRange(long hId)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x186, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		hId);
	return result;
}

void _Document::ScrollSelectionToTop()
{
	InvokeHelper(0x187, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::ScrollSelectionToBottom()
{
	InvokeHelper(0x188, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Document::AddCompareFunc(LPCTSTR funcName, LPDISPATCH funcImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x189, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 funcName, funcImpl);
}

void _Document::RemoveCompareFunc(LPCTSTR funcName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 funcName);
}

CString _Document::GetCurrentCSS()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetCurrentCSS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Document::GetDefaultWTDictionaryId()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Document::SetDefaultWTDictionaryId(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _DOMDocument properties

/////////////////////////////////////////////////////////////////////////////
// _DOMDocument operations

LPDISPATCH _DOMDocument::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short _DOMDocument::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString _DOMDocument::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DOMDocument::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DOMDocument::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _DOMDocument::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DOMDocument::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH _DOMDocument::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH _DOMDocument::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _DOMDocument::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _DOMDocument::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

LPDISPATCH _DOMDocument::createElement(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DOMDocument::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH _DOMDocument::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DOMDocument::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DOMDocument::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DOMDocument::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DOMDocument::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DOMDocument::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH _DOMDocument::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DOMDocument::getNodesByXPath(LPCTSTR xpathExpression)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourceSet properties

/////////////////////////////////////////////////////////////////////////////
// ResourceSet operations

LPDISPATCH ResourceSet::GetAssets()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ResourceSet::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ResourceSet::GetRoot()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourceAssetCollection properties

/////////////////////////////////////////////////////////////////////////////
// ResourceAssetCollection operations

LPDISPATCH ResourceAssetCollection::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ResourceAssetCollection::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ResourceAssetCollection::Add(LPCTSTR UseAs, LPCTSTR value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		UseAs, value);
	return result;
}

LPDISPATCH ResourceAssetCollection::ItemByName(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH ResourceAssetCollection::ItemByUseAs(LPCTSTR UseAs)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		UseAs);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourceAssetList properties

/////////////////////////////////////////////////////////////////////////////
// ResourceAssetList operations

LPDISPATCH ResourceAssetList::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ResourceAssetList::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourceAsset properties

/////////////////////////////////////////////////////////////////////////////
// ResourceAsset operations

CString ResourceAsset::GetUseAs()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ResourceAsset::GetValue()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResourceAsset::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResourceAsset::GetDescription()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResourceAsset::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResourceAsset::GetName()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ResourceAsset::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourcePropertyCollection properties

/////////////////////////////////////////////////////////////////////////////
// ResourcePropertyCollection operations

LPDISPATCH ResourcePropertyCollection::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ResourcePropertyCollection::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ResourcePropertyCollection::Add(LPCTSTR name, LPCTSTR value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, value);
	return result;
}

LPDISPATCH ResourcePropertyCollection::ItemByName(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourcePropertyList properties

/////////////////////////////////////////////////////////////////////////////
// ResourcePropertyList operations

LPDISPATCH ResourcePropertyList::item(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ResourcePropertyList::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ResourceProperty properties

/////////////////////////////////////////////////////////////////////////////
// ResourceProperty operations

CString ResourceProperty::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ResourceProperty::GetValue()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResourceProperty::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResourceProperty::GetDescription()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResourceProperty::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ValidationErrorList properties

/////////////////////////////////////////////////////////////////////////////
// ValidationErrorList operations

long ValidationErrorList::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ValidationErrorList::GetItem(long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

void ValidationErrorList::GoToError(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}


/////////////////////////////////////////////////////////////////////////////
// ValidationError properties

/////////////////////////////////////////////////////////////////////////////
// ValidationError operations

long ValidationError::GetErrorType()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ValidationError::GetErrorLevel()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString ValidationError::GetErrorMessage()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ValidationError::GetRange()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CheckData properties

/////////////////////////////////////////////////////////////////////////////
// CheckData operations

LPDISPATCH CheckData::GetElement()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString CheckData::GetAttributeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CheckData::GetValue()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CheckData::GetValidationMsg()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CheckData::SetValidationMsg(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
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

CString InPlaceControl::GetUserData()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT InPlaceControl::GetControl()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL InPlaceControl::GetUserMovedIntoControl()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL InPlaceControl::GetUpdateFromDocument()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT InPlaceControl::GetNextEventParam()
{
	VARIANT result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetShouldCreate(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long InPlaceControl::GetWidth()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long InPlaceControl::GetHeight()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString InPlaceControl::GetProgID()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void InPlaceControl::SetProgID(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Mark properties

/////////////////////////////////////////////////////////////////////////////
// Mark operations

long Mark::GetId()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Mark::GetFlags()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Mark::GetRange()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Mark::GetIsLessThan(LPDISPATCH Range, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Range, OrEqual);
	return result;
}

BOOL Mark::GetIsGreaterThan(LPDISPATCH Range, BOOL OrEqual)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Range, OrEqual);
	return result;
}

BOOL Mark::GetIsEqual(LPDISPATCH Range)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Range);
	return result;
}

void Mark::show()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Mark::Hide()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Mark::Redraw()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Mark::Remove()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL Mark::HideFromRevisionTracking()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Mark::ShowToRevisionTracking()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// MarkWalker properties

/////////////////////////////////////////////////////////////////////////////
// MarkWalker operations

LPDISPATCH MarkWalker::GetFirst()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH MarkWalker::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH MarkWalker::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH MarkWalker::GetLast()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Clipboard properties

/////////////////////////////////////////////////////////////////////////////
// Clipboard operations

CString Clipboard::GetText()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Clipboard::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Clipboard::FirstFormatName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString Clipboard::NextFormatName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPUNKNOWN Clipboard::GetDataObject()
{
	LPUNKNOWN result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Clipboard::SetEmpty()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL Clipboard::GetHasText()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Clipboard::GetHasFile()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL Clipboard::GetHasFormat(VARIANT* format)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		format);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CanElementList properties

/////////////////////////////////////////////////////////////////////////////
// CanElementList operations

LPDISPATCH CanElementList::GetItem(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long CanElementList::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CanElement properties

/////////////////////////////////////////////////////////////////////////////
// CanElement operations

CString CanElement::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CanElement::GetDescription()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CanElement::GetRequired()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CanElement::GetUsageCount()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleRule properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleRule operations

short DOMCSSStyleRule::GetType()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCSSStyleRule::GetCssText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCSSStyleRule::SetCssText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCSSStyleRule::GetParentStyleSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleRule::GetParentRule()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DOMCSSStyleRule::GetSelectorText()
{
	CString result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSStyleRule::GetStyle()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleDeclaration properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleDeclaration operations

CString DOMCSSStyleDeclaration::GetCssText()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCSSStyleDeclaration::SetCssText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString DOMCSSStyleDeclaration::getPropertyValue(LPCTSTR name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH DOMCSSStyleDeclaration::getPropertyCSSValue(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

CString DOMCSSStyleDeclaration::removeProperty(LPCTSTR name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		name);
	return result;
}

CString DOMCSSStyleDeclaration::getPropertyPriority(LPCTSTR name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		name);
	return result;
}

void DOMCSSStyleDeclaration::setProperty(LPCTSTR name, LPCTSTR value, LPCTSTR priority)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, value, priority);
}

long DOMCSSStyleDeclaration::GetLength()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMCSSStyleDeclaration::item(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

LPDISPATCH DOMCSSStyleDeclaration::GetParentRule()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _DocumentXM properties

/////////////////////////////////////////////////////////////////////////////
// _DocumentXM operations

LPDISPATCH _DocumentXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short _DocumentXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _DocumentXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH _DocumentXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH _DocumentXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _DocumentXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH _DocumentXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

LPDISPATCH _DocumentXM::createElement(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DocumentXM::createProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		target, data);
	return result;
}

LPDISPATCH _DocumentXM::createTextNode(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DocumentXM::createComment(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DocumentXM::createDocumentFragment()
{
	LPDISPATCH result;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetDocumentElement()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::createAttribute(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DocumentXM::createEntityReference(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DocumentXM::createCDATASection(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

LPDISPATCH _DocumentXM::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

LPDISPATCH _DocumentXM::GetDoctype()
{
	LPDISPATCH result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetImplementation()
{
	LPDISPATCH result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::getNodesByXPath(LPCTSTR xpathExpression)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression);
	return result;
}

CString _DocumentXM::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetFullName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetTitle()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _DocumentXM::GetSaved()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetSaved(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _DocumentXM::Save()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::SaveAs(VARIANT* FileName, BOOL AddToRecentFiles)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, AddToRecentFiles);
}

void _DocumentXM::Close(long SaveChanges)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveChanges);
}

BOOL _DocumentXM::Undo(long Times)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Times);
	return result;
}

BOOL _DocumentXM::Redo(long Times)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Times);
	return result;
}

void _DocumentXM::Activate()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::ScrollToSelection()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _DocumentXM::GetInCurrentProject()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetPath()
{
	CString result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetBodyAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void _DocumentXM::SetBodyAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 attrName, lpszNewValue);
}

CString _DocumentXM::GetDocumentTitle()
{
	CString result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetDocumentTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentXM::UniqueAttributeValue(LPCTSTR AttributeName, LPCTSTR prefix, VARIANT* number)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		AttributeName, prefix, number);
	return result;
}

void _DocumentXM::Validate()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _DocumentXM::GetRange()
{
	LPDISPATCH result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsXML()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsSGML()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsHTML()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetViewType()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetViewType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _DocumentXM::GetCustomDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetMacroFile()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsValid()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::Reload()
{
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::RefreshCssStyle()
{
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _DocumentXM::Layout()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetLocalPath()
{
	CString result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetLocalFullName()
{
	CString result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsEntityDeclared(LPCTSTR EntityName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		EntityName);
	return result;
}

void _DocumentXM::DeleteEntityDeclaration(LPCTSTR EntityName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName);
}

void _DocumentXM::DeclareTextEntity(LPCTSTR EntityName, LPCTSTR entityContent, long notUsed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, entityContent, notUsed);
}

void _DocumentXM::DeclareExternalEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicName, FileName);
}

void _DocumentXM::DeclareGraphicEntity(LPCTSTR EntityName, LPCTSTR publicIdentifier, LPCTSTR systemIdentifier, LPCTSTR notationName, long notUsed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 EntityName, publicIdentifier, systemIdentifier, notationName, notUsed);
}

LPDISPATCH _DocumentXM::GetChangedNodes()
{
	LPDISPATCH result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentXM::ClearNodeChangedStates(LPDISPATCH inNode, BOOL deep)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 inNode, deep);
}

void _DocumentXM::ClearAllChangedStates()
{
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _DocumentXM::GetNodeState(LPCTSTR stateName, LPDISPATCH inNode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		stateName, inNode);
	return result;
}

void _DocumentXM::HideInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

void _DocumentXM::ShowInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

CString _DocumentXM::GetBrowserURL()
{
	CString result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetBrowserURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentXM::GetBrowserApplication()
{
	CString result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetBrowserApplication(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _DocumentXM::PreviewInBrowser(LPCTSTR Browser)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Browser);
}

BOOL _DocumentXM::GetRulesChecking()
{
	BOOL result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetRulesChecking(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _DocumentXM::UndoClear()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _DocumentXM::GetRenderedContent(LPDISPATCH inNode)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		inNode);
	return result;
}

void _DocumentXM::SetRenderedContent(LPDISPATCH inNode, LPCTSTR renderedContent)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 inNode, renderedContent);
}

LPDISPATCH _DocumentXM::createCharacterReference(long value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		value);
	return result;
}

LPDISPATCH _DocumentXM::getElementById(LPCTSTR value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		value);
	return result;
}

long _DocumentXM::GetPreviousViewType()
{
	long result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetRulesFile()
{
	CString result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetDOMEnforceValid()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetDOMEnforceValid(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _DocumentXM::GetDisplayStylesFile()
{
	CString result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::AcceptDropFormat(VARIANT* dropFormat, LPCTSTR formatName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dropFormat, formatName);
	return result;
}

BOOL _DocumentXM::GetStructureViewVisible()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetStructureViewVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _DocumentXM::CreatePreviewFile()
{
	CString result;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetCustomProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetStyleSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetIsInWellFormedEditingMode()
{
	BOOL result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetChangedNodesbyKey(LPCTSTR key)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		key);
	return result;
}

void _DocumentXM::ClearNodeChangedStatesbyKey(LPCTSTR key, LPDISPATCH inNode, BOOL deep)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key, inNode, deep);
}

void _DocumentXM::ClearAllChangedStatesbyKey(LPCTSTR key)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key);
}

BOOL _DocumentXM::GetNodeStatebyKey(LPCTSTR key, LPCTSTR stateName, LPDISPATCH inNode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		key, stateName, inNode);
	return result;
}

CString _DocumentXM::GetAllUsersMacroFile()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetCurrentUserMacroFile()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetXml()
{
	CString result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetCustomizations()
{
	LPDISPATCH result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetTrackRevisions()
{
	BOOL result;
	InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetTrackRevisions(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _DocumentXM::GetMinimizeTagIcons()
{
	BOOL result;
	InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetMinimizeTagIcons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _DocumentXM::GetResourceSet()
{
	LPDISPATCH result;
	InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetDropText()
{
	CString result;
	InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetDropText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPUNKNOWN _DocumentXM::GetDropDataObject()
{
	LPUNKNOWN result;
	InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void _DocumentXM::DropNotAllowed()
{
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _DocumentXM::GetDropPoint()
{
	LPDISPATCH result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetFormattingUpdating()
{
	BOOL result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetFormattingUpdating(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _DocumentXM::GotoNextChange()
{
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::GotoPrevChange()
{
	InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _DocumentXM::CanAcceptOrRejectChange()
{
	BOOL result;
	InvokeHelper(0x4f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::AcceptChange()
{
	InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::RejectChange()
{
	InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _DocumentXM::AcceptAllChanges()
{
	long result;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::RejectAllChanges()
{
	long result;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetValidationErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetCheckData()
{
	LPDISPATCH result;
	InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetMouseOverNode()
{
	LPDISPATCH result;
	InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetHost()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentXM::MoveDropPoint(LPDISPATCH newDropPoint)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 newDropPoint);
}

LPDISPATCH _DocumentXM::GetDropRange()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::createElementNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, qualifiedName);
	return result;
}

LPDISPATCH _DocumentXM::createAttributeNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, qualifiedName);
	return result;
}

LPDISPATCH _DocumentXM::getElementsByTagNameNS(LPCTSTR namespaceURI, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceURI, localName);
	return result;
}

CString _DocumentXM::GetXmlWithCT()
{
	CString result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetRMPreserveMode()
{
	BOOL result;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetRMPreserveMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _DocumentXM::formatGraphicTable(LPDISPATCH tblNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tblNode);
}

LPDISPATCH _DocumentXM::GetActiveInPlaceControl()
{
	LPDISPATCH result;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::CreateMark(LPCTSTR ownerKey, long markID, long Flags, const VARIANT& userData, LPDISPATCH position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT VTS_DISPATCH;
	InvokeHelper(0x120, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ownerKey, markID, Flags, &userData, position);
	return result;
}

LPDISPATCH _DocumentXM::GetMarkWalker(LPCTSTR ownerKey)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		ownerKey);
	return result;
}

void _DocumentXM::SetMarkPresentationService(LPCTSTR ownerKey, long mpsType, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x122, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpsType, mpServiceImpl);
}

void _DocumentXM::SetCTMRulesService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x123, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpServiceImpl);
}

void _DocumentXM::SetImageService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x124, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ownerKey, mpServiceImpl);
}

void _DocumentXM::EmptyClipboard()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _DocumentXM::GetClipboard()
{
	LPDISPATCH result;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetDropClipboardText()
{
	BOOL result;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::GetDropInternalText()
{
	BOOL result;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_UNKNOWN;
	InvokeHelper(0x134, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		formatName, data);
	return result;
}

LPDISPATCH _DocumentXM::GetCRLocator()
{
	LPDISPATCH result;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetCRLocator(VARIANT* newValue)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _DocumentXM::GetReadOnlyHint()
{
	BOOL result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetReadOnlyHint(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _DocumentXM::createElementWF(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x137, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DocumentXM::createAttributeWF(LPCTSTR name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x138, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name);
	return result;
}

LPDISPATCH _DocumentXM::createTextNodeWF(LPCTSTR data)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x139, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		data);
	return result;
}

void _DocumentXM::attachTransclusion(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_I4;
	InvokeHelper(0x140, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, transNode, transResult);
}

void _DocumentXM::detachTransclusion(LPDISPATCH srcNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode);
}

void _DocumentXM::showHideTransclusion(LPDISPATCH srcNode, BOOL show)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x142, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, show);
}

void _DocumentXM::importNode(LPDISPATCH node)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x143, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 node);
}

long _DocumentXM::GetAutoSetImageWidthHeight()
{
	long result;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetAutoSetImageWidthHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x144, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _DocumentXM::GetAutoScaleImageWidth()
{
	long result;
	InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetAutoScaleImageWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _DocumentXM::GetAutoScaleImageHeight()
{
	long result;
	InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetAutoScaleImageHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _DocumentXM::attachTransclusionEx(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_I4;
	InvokeHelper(0x147, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, transNode, transResult);
}

void _DocumentXM::detachTransclusionEx(LPDISPATCH srcNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x148, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode);
}

void _DocumentXM::showHideTransclusionEx(LPDISPATCH srcNode, BOOL show)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x149, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 srcNode, show);
}

CString _DocumentXM::getTextEntityReplacementText(LPCTSTR entName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x150, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		entName);
	return result;
}

BOOL _DocumentXM::GetDropTextIsMultiCell()
{
	BOOL result;
	InvokeHelper(0x151, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::HideEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x152, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

void _DocumentXM::ShowEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x153, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, elementType);
}

LPDISPATCH _DocumentXM::GetEditAttributeNode()
{
	LPDISPATCH result;
	InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetEditAttributeName()
{
	CString result;
	InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::GetEditAttributeValue()
{
	CString result;
	InvokeHelper(0x156, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetEditAttributeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x156, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _DocumentXM::GetRefreshCssStyleDoc()
{
	LPDISPATCH result;
	InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentXM::RefreshCssStyleToAppend(LPCTSTR cssToAppend)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x158, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cssToAppend);
}

void _DocumentXM::ShowXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x159, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _DocumentXM::HideXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x160, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _DocumentXM::UpdateXInclude(LPDISPATCH ctxNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x161, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ctxNode);
}

void _DocumentXM::OpenXIncludeTarget(LPDISPATCH xincludeNode)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 xincludeNode);
}

CString _DocumentXM::ExportWithXIncludesToXML()
{
	CString result;
	InvokeHelper(0x163, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetActiveXIncludeNode()
{
	LPDISPATCH result;
	InvokeHelper(0x164, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::IsXIncludeNode(LPDISPATCH node)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x165, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node);
	return result;
}

BOOL _DocumentXM::GetIsNamespaceAware()
{
	BOOL result;
	InvokeHelper(0x166, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::PurgeXIncludeCache()
{
	InvokeHelper(0x167, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::SetXIncludeFeature(long feature, VARIANT* val)
{
	static BYTE parms[] =
		VTS_I4 VTS_PVARIANT;
	InvokeHelper(0x168, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 feature, val);
}

LPDISPATCH _DocumentXM::GetLinkResolutionErrorList()
{
	LPDISPATCH result;
	InvokeHelper(0x169, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DocumentXM::ConvertXIncludeTargetToXML(LPCTSTR href, LPCTSTR xptr)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x16a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		href, xptr);
	return result;
}

void _DocumentXM::ExportWithXIncludesToFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x16b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

long _DocumentXM::GetXIncludeTargetState(LPDISPATCH xincludeNode)
{
	long result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x16c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		xincludeNode);
	return result;
}

void _DocumentXM::RegisterNonCopyableAttr(LPCTSTR elemNS, LPCTSTR elemName, LPCTSTR attrNS, LPCTSTR attrName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x16d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 elemNS, elemName, attrNS, attrName);
}

BOOL _DocumentXM::GetBackgroundSpellchecking()
{
	BOOL result;
	InvokeHelper(0x16e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetBackgroundSpellchecking(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _DocumentXM::GetSpellAutoCorrect()
{
	BOOL result;
	InvokeHelper(0x16f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetSpellAutoCorrect(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _DocumentXM::IsSpellingCorrect(long mode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x170, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		mode);
	return result;
}

CString _DocumentXM::GetSpellingResult(long mode)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x171, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		mode);
	return result;
}

BOOL _DocumentXM::ReplaceWord(LPCTSTR word)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x172, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		word);
	return result;
}

BOOL _DocumentXM::IgnoreWordSpelling()
{
	BOOL result;
	InvokeHelper(0x173, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _DocumentXM::AddWordToDictionary()
{
	BOOL result;
	InvokeHelper(0x174, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetSpellCheckerService(LPDISPATCH mpServiceImpl)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x175, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 mpServiceImpl);
}

BOOL _DocumentXM::GetInlineMediaVisible()
{
	BOOL result;
	InvokeHelper(0x176, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetInlineMediaVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x176, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _DocumentXM::GetMsgHwnd()
{
	long result;
	InvokeHelper(0x177, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgMessage()
{
	long result;
	InvokeHelper(0x178, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgWParam()
{
	long result;
	InvokeHelper(0x179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgLParam()
{
	long result;
	InvokeHelper(0x17a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgTime()
{
	long result;
	InvokeHelper(0x17b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgX()
{
	long result;
	InvokeHelper(0x17c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetMsgY()
{
	long result;
	InvokeHelper(0x17d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _DocumentXM::GetWindowHandle()
{
	long result;
	InvokeHelper(0x17e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::GetRangeNearestPoint(long screenX, long screenY)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x17f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		screenX, screenY);
	return result;
}

void _DocumentXM::BeginMutations(LPCTSTR niceName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x180, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 niceName);
}

void _DocumentXM::EndMutations(BOOL didChange)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x181, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 didChange);
}

unsigned short _DocumentXM::GetNodeSpellLanguage(LPDISPATCH inNode)
{
	unsigned short result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x182, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		inNode);
	return result;
}

BOOL _DocumentXM::IsDummyNode(LPDISPATCH node)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x183, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		node);
	return result;
}

long _DocumentXM::HighlightRange(LPCTSTR location, long highlightType, long highlightState, LPCTSTR hint)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x184, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		location, highlightType, highlightState, hint);
	return result;
}

long _DocumentXM::SetHighlightedRangeState(long hId, long hState)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x185, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		hId, hState);
	return result;
}

LPDISPATCH _DocumentXM::GetHighlightedRange(long hId)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x186, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		hId);
	return result;
}

void _DocumentXM::ScrollSelectionToTop()
{
	InvokeHelper(0x187, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::ScrollSelectionToBottom()
{
	InvokeHelper(0x188, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentXM::AddCompareFunc(LPCTSTR funcName, LPDISPATCH funcImpl)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x189, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 funcName, funcImpl);
}

void _DocumentXM::RemoveCompareFunc(LPCTSTR funcName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 funcName);
}

CString _DocumentXM::GetCurrentCSS()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetCurrentCSS(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentXM::GetDefaultWTDictionaryId()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentXM::SetDefaultWTDictionaryId(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _DocumentXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentXM::getElementsByTagNameEx(LPCTSTR tagName, long mode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xdc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName, mode);
	return result;
}

LPDISPATCH _DocumentXM::getNodesByXPathEx(LPCTSTR xpathExpression, long mode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xdd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression, mode);
	return result;
}

LPDISPATCH _DocumentXM::querySelector(LPCTSTR cssExpr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xde, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		cssExpr);
	return result;
}

LPDISPATCH _DocumentXM::querySelectorAll(LPCTSTR cssExpr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xdf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		cssExpr);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMAttrXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMAttrXM operations

LPDISPATCH DOMAttrXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMAttrXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMAttrXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttrXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttrXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMAttrXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMAttrXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMAttrXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMAttrXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMAttrXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMAttrXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMAttrXM::GetName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttrXM::GetValue()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttrXM::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL DOMAttrXM::GetSpecified()
{
	BOOL result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMAttrXM::GetOwnerElement()
{
	LPDISPATCH result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DOMAttrXM::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMAttrXM::GetPrefix()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMAttrXM::SetPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString DOMAttrXM::GetLocalName()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long DOMAttrXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMEntityReferenceXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMEntityReferenceXM operations

LPDISPATCH DOMEntityReferenceXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMEntityReferenceXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMEntityReferenceXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntityReferenceXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMEntityReferenceXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMEntityReferenceXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMEntityReferenceXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityReferenceXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

long DOMEntityReferenceXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCharacterReferenceXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMCharacterReferenceXM operations

LPDISPATCH DOMCharacterReferenceXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCharacterReferenceXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCharacterReferenceXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCharacterReferenceXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCharacterReferenceXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCharacterReferenceXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCharacterReferenceXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCharacterReferenceXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

long DOMCharacterReferenceXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMDocumentTypeXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMDocumentTypeXM operations

LPDISPATCH DOMDocumentTypeXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMDocumentTypeXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMDocumentTypeXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentTypeXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMDocumentTypeXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMDocumentTypeXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentTypeXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMDocumentTypeXM::GetName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetEntities()
{
	LPDISPATCH result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentTypeXM::GetNotations()
{
	LPDISPATCH result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString DOMDocumentTypeXM::GetElementType(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

VARIANT DOMDocumentTypeXM::GetElementTypes()
{
	VARIANT result;
	InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentTypeXM::GetHasElementType(LPCTSTR ElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName);
	return result;
}

BOOL DOMDocumentTypeXM::GetHasAttribute(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentTypeXM::GetElementAttribute(LPCTSTR ElementName, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, index);
	return result;
}

VARIANT DOMDocumentTypeXM::GetElementAttributes(LPCTSTR ElementName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		ElementName);
	return result;
}

CString DOMDocumentTypeXM::GetPublicId()
{
	CString result;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentTypeXM::GetSystemId()
{
	CString result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long DOMDocumentTypeXM::GetAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentTypeXM::GetEnumeratedAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, AttributeName, index);
	return result;
}

VARIANT DOMDocumentTypeXM::GetEnumeratedAttributeTypes(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

long DOMDocumentTypeXM::GetElementContentType(LPCTSTR ElementName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName);
	return result;
}

long DOMDocumentTypeXM::GetAttributeDefaultType(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

CString DOMDocumentTypeXM::GetAttributeDefaultValue(LPCTSTR ElementName, LPCTSTR AttributeName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		ElementName, AttributeName);
	return result;
}

void DOMDocumentTypeXM::addElement(LPCTSTR ElementName, LPCTSTR description, BOOL any, BOOL retainWhiteSpace)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x13d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName, description, any, retainWhiteSpace);
}

void DOMDocumentTypeXM::addElementToInclusions(LPCTSTR ElementNameToAdd, LPCTSTR ElementNameInclusions)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x13e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementNameToAdd, ElementNameInclusions);
}

void DOMDocumentTypeXM::addAttribute(LPCTSTR ElementName, LPCTSTR attrName, LPCTSTR helpString, long attrType, long dfltType, LPCTSTR attValueDefault)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x13f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ElementName, attrName, helpString, attrType, dfltType, attValueDefault);
}

void DOMDocumentTypeXM::addInPlaceControlOverride(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, LPCTSTR userData, BOOL useBmpPrinting)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 selector, progID, scriptPrefix, userData, useBmpPrinting);
}

CString DOMDocumentTypeXM::GetParentElementType(LPCTSTR elementType, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		elementType, index);
	return result;
}

VARIANT DOMDocumentTypeXM::GetParentElementTypes(LPCTSTR elementType)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		elementType);
	return result;
}

BOOL DOMDocumentTypeXM::GetHasParentElementType(LPCTSTR elementType, LPCTSTR ParentElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementType, ParentElementName);
	return result;
}

CString DOMDocumentTypeXM::GetChildElementType(LPCTSTR elementType, long index)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		elementType, index);
	return result;
}

VARIANT DOMDocumentTypeXM::GetChildElementTypes(LPCTSTR elementType)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		elementType);
	return result;
}

BOOL DOMDocumentTypeXM::GetHasChildElementType(LPCTSTR elementType, LPCTSTR ChildElementName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		elementType, ChildElementName);
	return result;
}

long DOMDocumentTypeXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMElementXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMElementXM operations

LPDISPATCH DOMElementXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMElementXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMElementXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMElementXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMElementXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMElementXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMElementXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMElementXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMElementXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMElementXM::GetTagName()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::getAttribute(LPCTSTR attrName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		attrName);
	return result;
}

void DOMElementXM::setAttribute(LPCTSTR attrName, LPCTSTR attrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName, attrValue);
}

void DOMElementXM::removeAttribute(LPCTSTR attrName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 attrName);
}

void DOMElementXM::normalize()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH DOMElementXM::getAttributeNode(LPCTSTR attrName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrName);
	return result;
}

LPDISPATCH DOMElementXM::setAttributeNode(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElementXM::removeAttributeNode(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElementXM::getElementsByTagName(LPCTSTR tagName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x134, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName);
	return result;
}

BOOL DOMElementXM::hasAttribute(LPCTSTR attrName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x135, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		attrName);
	return result;
}

CString DOMElementXM::GetNamespaceURI()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::GetPrefix()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMElementXM::SetPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString DOMElementXM::GetLocalName()
{
	CString result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::getAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x193, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

void DOMElementXM::setAttributeNS(LPCTSTR namespaceName, LPCTSTR localName, LPCTSTR attrValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x194, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceName, localName, attrValue);
}

void DOMElementXM::removeAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x195, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 namespaceName, localName);
}

LPDISPATCH DOMElementXM::getAttributeNodeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x196, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

LPDISPATCH DOMElementXM::setAttributeNodeNS(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x197, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

LPDISPATCH DOMElementXM::getElementsByTagNameNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x198, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

BOOL DOMElementXM::hasAttributeNS(LPCTSTR namespaceName, LPCTSTR localName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x199, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		namespaceName, localName);
	return result;
}

LPDISPATCH DOMElementXM::getNodesByXPath(LPCTSTR xpathExpression)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x19a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression);
	return result;
}

LPDISPATCH DOMElementXM::setAttributeNodeWF(LPDISPATCH attrNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x19b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		attrNode);
	return result;
}

long DOMElementXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMElementXM::GetXml()
{
	CString result;
	InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMElementXM::getElementsByTagNameEx(LPCTSTR tagName, long mode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xdd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		tagName, mode);
	return result;
}

LPDISPATCH DOMElementXM::getElementsByTagNameNSEx(LPCTSTR namespaceName, LPCTSTR localName, long mode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xde, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		namespaceName, localName, mode);
	return result;
}

LPDISPATCH DOMElementXM::getNodesByXPathEx(LPCTSTR xpathExpression, long mode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xdf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		xpathExpression, mode);
	return result;
}

LPDISPATCH DOMElementXM::querySelector(LPCTSTR cssExpr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		cssExpr);
	return result;
}

LPDISPATCH DOMElementXM::querySelectorAll(LPCTSTR cssExpr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		cssExpr);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMProcessingInstructionXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMProcessingInstructionXM operations

LPDISPATCH DOMProcessingInstructionXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMProcessingInstructionXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstructionXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstructionXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMProcessingInstructionXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMProcessingInstructionXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMProcessingInstructionXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMProcessingInstructionXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMProcessingInstructionXM::GetTarget()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMProcessingInstructionXM::GetData()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMProcessingInstructionXM::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMProcessingInstructionXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
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
// DOMEntityXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMEntityXM operations

LPDISPATCH DOMEntityXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMEntityXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMEntityXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntityXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMEntityXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMEntityXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMEntityXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMEntityXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMEntityXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMEntityXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMEntityXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMEntityXM::GetPublicId()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntityXM::GetSystemId()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMEntityXM::GetNotationName()
{
	CString result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long DOMEntityXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
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
// DOMNotationXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMNotationXM operations

LPDISPATCH DOMNotationXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMNotationXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMNotationXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMNotationXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMNotationXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMNotationXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMNotationXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMNotationXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMNotationXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNotationXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMNotationXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMNotationXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMNotationXM::GetPublicId()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMNotationXM::GetSystemId()
{
	CString result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long DOMNotationXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMTextXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMTextXM operations

LPDISPATCH DOMTextXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMTextXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMTextXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMTextXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMTextXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMTextXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMTextXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMTextXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMTextXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMTextXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMTextXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMTextXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMTextXM::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMTextXM::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMTextXM::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMTextXM::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMTextXM::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMTextXM::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMTextXM::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMTextXM::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH DOMTextXM::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x191, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}

long DOMTextXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCommentXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMCommentXM operations

LPDISPATCH DOMCommentXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCommentXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCommentXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCommentXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCommentXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCommentXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCommentXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCommentXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCommentXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCommentXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCommentXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCommentXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMCommentXM::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCommentXM::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMCommentXM::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMCommentXM::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMCommentXM::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMCommentXM::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMCommentXM::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMCommentXM::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

long DOMCommentXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCDATASectionXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMCDATASectionXM operations

LPDISPATCH DOMCDATASectionXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMCDATASectionXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCDATASectionXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMCDATASectionXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCDATASectionXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCDATASectionXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMCDATASectionXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMCDATASectionXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMCDATASectionXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCDATASectionXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCDATASectionXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

CString DOMCDATASectionXM::GetData()
{
	CString result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCDATASectionXM::SetData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long DOMCDATASectionXM::GetLength()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString DOMCDATASectionXM::substringData(long offset, long count)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		offset, count);
	return result;
}

void DOMCDATASectionXM::appendData(LPCTSTR data)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 data);
}

void DOMCDATASectionXM::insertData(long offset, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, data);
}

void DOMCDATASectionXM::deleteData(long offset, long count)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count);
}

void DOMCDATASectionXM::replaceData(long offset, long count, LPCTSTR data)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x133, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 offset, count, data);
}

LPDISPATCH DOMCDATASectionXM::splitText(long offset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x191, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		offset);
	return result;
}

long DOMCDATASectionXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMDocumentFragmentXM properties

/////////////////////////////////////////////////////////////////////////////
// DOMDocumentFragmentXM operations

LPDISPATCH DOMDocumentFragmentXM::GetParentNode()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

short DOMDocumentFragmentXM::GetNodeType()
{
	short result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMDocumentFragmentXM::GetNodeName()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString DOMDocumentFragmentXM::GetNodeValue()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMDocumentFragmentXM::SetNodeValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMDocumentFragmentXM::GetFirstChild()
{
	LPDISPATCH result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetLastChild()
{
	LPDISPATCH result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetNextSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetPreviousSibling()
{
	LPDISPATCH result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL DOMDocumentFragmentXM::hasChildNodes()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newChild, oldChild);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::insertBefore(LPDISPATCH newNode, const VARIANT& refNode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		newNode, &refNode);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::removeChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::appendChild(LPDISPATCH child)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		child);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetOwnerDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetChildNodes()
{
	LPDISPATCH result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::GetAttributes()
{
	LPDISPATCH result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMDocumentFragmentXM::cloneNode(BOOL deep)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xda, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		deep);
	return result;
}

long DOMDocumentFragmentXM::GetTransState()
{
	long result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DOMCSSUnknownRule properties

/////////////////////////////////////////////////////////////////////////////
// DOMCSSUnknownRule operations

short DOMCSSUnknownRule::GetType()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString DOMCSSUnknownRule::GetCssText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void DOMCSSUnknownRule::SetCssText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH DOMCSSUnknownRule::GetParentStyleSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH DOMCSSUnknownRule::GetParentRule()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Rule properties

/////////////////////////////////////////////////////////////////////////////
// _Rule operations

CString _Rule::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Rule::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Rule::GetValue()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Rule::SetValue(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _RuleSet properties

/////////////////////////////////////////////////////////////////////////////
// _RuleSet operations

LPDISPATCH _RuleSet::item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long _RuleSet::GetCount()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _RuleSet::Add(LPCTSTR name, LPCTSTR value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, value);
}

void _RuleSet::Remove(VARIANT* index)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}


/////////////////////////////////////////////////////////////////////////////
// ResolveEntityInfo properties

/////////////////////////////////////////////////////////////////////////////
// ResolveEntityInfo operations

CString ResolveEntityInfo::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResolveEntityInfo::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResolveEntityInfo::GetPublicId()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResolveEntityInfo::SetPublicId(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResolveEntityInfo::GetSystemId()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResolveEntityInfo::SetSystemId(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResolveEntityInfo::GetBasePath()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResolveEntityInfo::SetBasePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ResolveEntityInfo::GetFileName()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ResolveEntityInfo::SetFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL ResolveEntityInfo::IsDocType()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
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

LPUNKNOWN _Application::GetFx()
{
	LPUNKNOWN result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
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

CString _Application::UniqueFileName(LPCTSTR Directory, LPCTSTR prefix, VARIANT* Extension)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Directory, prefix, Extension);
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

void _Application::EmptyClipboard()
{
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _Application::GetMakeFaceId(LPCTSTR groupName, long rowNum, long iconNum)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		groupName, rowNum, iconNum);
	return result;
}

void _Application::HideViewModeButton(long vtButton)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 vtButton);
}

void _Application::HideMiniContext()
{
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::HideStructureView()
{
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::HideStatusBarPane(long pane)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pane);
}

void _Application::SetWorkbookMode(BOOL modeOn)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 modeOn);
}

void _Application::DisableToolbarContextMenu()
{
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::DisableDocumentContextMenu()
{
	InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Application::GetUnicodeSupported()
{
	BOOL result;
	InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Application::GetResolveURL()
{
	CString result;
	InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetResolveURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _Application::GetResolveEntityInfo()
{
	LPDISPATCH result;
	InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _Application::GetValidationSuccess()
{
	BOOL result;
	InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetValidationSuccess(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::StopValidation()
{
	InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::PushInMacro(LPCTSTR MacroName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroName);
}

LPDISPATCH _Application::GetStyleElements()
{
	LPDISPATCH result;
	InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetStyleElementName()
{
	CString result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetStyleElementType()
{
	CString result;
	InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::HideSplashDialog()
{
	InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Application::GetClipboard()
{
	LPDISPATCH result;
	InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetDropText()
{
	CString result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetDropText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _Application::GetDropClipboardText()
{
	BOOL result;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _Application::GetDropInternalText()
{
	BOOL result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::MoveDropPoint(LPDISPATCH newDropPoint)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 newDropPoint);
}

LPDISPATCH _Application::GetDropRange()
{
	LPDISPATCH result;
	InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetAttributeInspector()
{
	LPDISPATCH result;
	InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::DropNotAllowed()
{
	InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::AddChangedNodeKey(LPCTSTR key)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key);
}

void _Application::RemoveChangedNodeKey(LPCTSTR key)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key);
}

CString _Application::GetAllUsersMacroFile()
{
	CString result;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetCurrentUserMacroFile()
{
	CString result;
	InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetCheckData()
{
	LPDISPATCH result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT _Application::CreateFormDlg(LPCTSTR formFileName, VARIANT* DOMNode)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		formFileName, DOMNode);
	return result;
}

LPDISPATCH _Application::GetElementList()
{
	LPDISPATCH result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_UNKNOWN;
	InvokeHelper(0x5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		formatName, data);
	return result;
}

LPDISPATCH _Application::GetActiveContextMenu()
{
	LPDISPATCH result;
	InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetCurrentUser()
{
	CString result;
	InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetCurrentUserName()
{
	CString result;
	InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetCurrentUserName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Application::GetCurrentUserInitials()
{
	CString result;
	InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetCurrentUserInitials(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Application::GetCurrentUserRole()
{
	CString result;
	InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetCurrentUserRole(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _Application::GetDocumentRuleSet()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetExeName()
{
	CString result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetResources()
{
	LPDISPATCH result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetStyleElementTypeNS()
{
	CString result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetVersionNumber()
{
	CString result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetOpenFileName()
{
	CString result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Application::GetCancelOpenDocument()
{
	BOOL result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetCancelOpenDocument(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::SetForegroundWindow()
{
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::ShowWindow(long nCmdShow)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nCmdShow);
}

void _Application::PostSetFocus(long nWndType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nWndType);
}

BOOL _Application::GetCancelDocumentEventMacro()
{
	BOOL result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetCancelDocumentEventMacro(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _Application::GetQueriedServiceName()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetQueriedServiceImpl(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _Application::GetAlwaysUndoClearAfterSave()
{
	BOOL result;
	InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetAlwaysUndoClearAfterSave(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::RegisterCRCL(LPDISPATCH CRCLcore)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CRCLcore);
}

void _Application::UnregisterCRCL()
{
	InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Application::AddNewTemplateDialogFileExtension(LPCTSTR fileExt)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fileExt);
}

void _Application::AddOpenFileDialogFilter(LPCTSTR filterEntry, BOOL ignoredTreatAsXML)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 filterEntry, ignoredTreatAsXML);
}

CString _Application::GetSkuName()
{
	CString result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetResolveNode()
{
	LPDISPATCH result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetSaveAsFileName()
{
	CString result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _Application::GetCancelSaveAsDocument()
{
	BOOL result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetCancelSaveAsDocument(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Application::GetCancelNewDocument()
{
	BOOL result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetCancelNewDocument(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Application::GetUseMultiUserLocalTBRs()
{
	BOOL result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetUseMultiUserLocalTBRs(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::AddToRecentFileList(LPCTSTR FullName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullName);
}

void _Application::RemoveFromRecentFileList(LPCTSTR FullName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullName);
}

CString _Application::GetLastOpenDocumentPath()
{
	CString result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetLastOpenDocumentPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Application::GetLastOpenImagePath()
{
	CString result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetLastOpenImagePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _Application::GetIsMRUOpenDocumentAction()
{
	BOOL result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Application::GetUserSettingMode()
{
	CString result;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetDefaultSaveAsExtension()
{
	CString result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetDefaultSaveAsExtension(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _Application::GetDropTextIsMultiCell()
{
	BOOL result;
	InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Application::GetResolvePath()
{
	CString result;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Application::SetResolvePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Application::GetParentURL()
{
	CString result;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetResolveAttrName()
{
	CString result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetResolveAttrNS()
{
	CString result;
	InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetResultsManager()
{
	LPDISPATCH result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Application::RunAfterProcessDone(long ProcessID, LPCTSTR MacroName, LPCTSTR ResourceName, LPCTSTR ResourceData)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ProcessID, MacroName, ResourceName, ResourceData);
}

BOOL _Application::IsProcessRunning(long ProcessID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ProcessID);
	return result;
}

BOOL _Application::GetCancelAllDocumentsAction()
{
	BOOL result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetCancelAllDocumentsAction(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _Application::GetSaveAllDocumentsOption()
{
	long result;
	InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _Application::GetIniVariable(LPCTSTR iniVarName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		iniVarName);
	return result;
}

void _Application::SetIniVariable(LPCTSTR iniVarName, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x8e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iniVarName, lpszNewValue);
}

BOOL _Application::GetHandledViewEvent()
{
	BOOL result;
	InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Application::SetHandledViewEvent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void _Application::ShowSpellChecker(long command)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x90, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 command);
}

void _Application::MapXmlLangToWTDictionaryId(LPCTSTR langID, LPCTSTR dictionaryID)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 langID, dictionaryID);
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

LPDISPATCH Documents::OpenString(LPCTSTR inputString, long ViewType, LPCTSTR FileName, BOOL TreatAsTemplate, BOOL IsXML, BOOL EditAsWellFormed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		inputString, ViewType, FileName, TreatAsTemplate, IsXML, EditAsWellFormed);
	return result;
}

CString Documents::ChooseTemplate()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH Documents::OpenEx(LPCTSTR FileName, VARIANT* CRLocatorDisp, long ViewType, BOOL ReadOnly)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_I4 VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, CRLocatorDisp, ViewType, ReadOnly);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CommandBars properties

/////////////////////////////////////////////////////////////////////////////
// CommandBars operations

LPDISPATCH CommandBars::GetItem(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPDISPATCH CommandBars::Add(LPCTSTR name, VARIANT* positon)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, positon);
	return result;
}

LPDISPATCH CommandBars::FindControl(long type, long cmdId, VARIANT* visible, VARIANT* recursive)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		type, cmdId, visible, recursive);
	return result;
}

long CommandBars::GetCount()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CommandBars::GetName()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CommandBars::GetHasSamples()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::AddToSamples(LPCTSTR caption, LPCTSTR OnAction, BOOL separator, VARIANT* description, VARIANT* faceId)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		caption, OnAction, separator, description, faceId);
	return result;
}

BOOL CommandBars::GetIsImportantContextPopup(LPDISPATCH pcbp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		pcbp);
	return result;
}

BOOL CommandBars::GetHasResults()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBars::AddToResults(LPCTSTR caption, LPCTSTR OnAction, BOOL separator, VARIANT* description, VARIANT* faceId)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		caption, OnAction, separator, description, faceId);
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

LPDISPATCH CommandBar::FindControl(long type, long cmdId, VARIANT* visible, VARIANT* recursive)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		type, cmdId, visible, recursive);
	return result;
}

BOOL CommandBar::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH CommandBar::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL CommandBar::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBar::GetVisible()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CommandBar::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBar::SetReadOnly(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CommandBarControl properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarControl operations

void CommandBarControl::Copy(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarControl::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarControl::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarControl::Move(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarControl::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CommandBarControl::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
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

BOOL CommandBarControl::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarControl::GetEnabled()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarControl::GetVisible()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarControl::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

LPDISPATCH CommandBarControls::Add(long controlType, VARIANT* commandId, VARIANT* before, VARIANT* param)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		controlType, commandId, before, param);
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
// CommandBarPopup properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup operations

void CommandBarPopup::Copy(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarPopup::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::Move(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarPopup::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CommandBarPopup::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
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

BOOL CommandBarPopup::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarPopup::GetEnabled()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarPopup::GetVisible()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

void CommandBarPopup::CopyFace()
{
	InvokeHelper(0x20001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarPopup::PasteFace()
{
	InvokeHelper(0x20002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CommandBarPopup::GetBuiltInFace()
{
	BOOL result;
	InvokeHelper(0x20003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetBuiltInFace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CommandBarPopup::GetCaption()
{
	CString result;
	InvokeHelper(0x20004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH CommandBarPopup::GetControls()
{
	LPDISPATCH result;
	InvokeHelper(0x20005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long CommandBarPopup::GetFaceId()
{
	long result;
	InvokeHelper(0x20006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CommandBarPopup::SetFaceId(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// _ResourceManager properties

/////////////////////////////////////////////////////////////////////////////
// _ResourceManager operations

LPDISPATCH _ResourceManager::GetAssets()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ResourceManager::GetDesktop()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ResourceManager::GetFtpNeighborhood()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ResourceManager::GetLocalSites()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _ResourceManager::AddTab(LPCTSTR tabName, LPCTSTR Guid)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, Guid);
}

void _ResourceManager::SelectTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

void _ResourceManager::RemoveTab(LPCTSTR tabName, BOOL delayed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, delayed);
}

void _ResourceManager::RemoveAllTabs()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _ResourceManager::GetControlInTab(LPCTSTR tabName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		tabName);
	return result;
}

BOOL _ResourceManager::GetVisible()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ResourceManager::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _ResourceManager::GetFrontmostTabName()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ResourceManager::RenameTab(LPCTSTR oldTabName, LPCTSTR newTabName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oldTabName, newTabName);
}

LPDISPATCH _ResourceManager::DoResman2(LPCTSTR cmdStr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		cmdStr);
	return result;
}

BOOL _ResourceManager::ShowTab(LPCTSTR tabName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		tabName);
	return result;
}

BOOL _ResourceManager::HideTab(LPCTSTR tabName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
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
// StyleElements properties

/////////////////////////////////////////////////////////////////////////////
// StyleElements operations

long StyleElements::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString StyleElements::item(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

long StyleElements::Insert(long index, LPCTSTR name)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		index, name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// AttributeInspector properties

/////////////////////////////////////////////////////////////////////////////
// AttributeInspector operations

LPDISPATCH AttributeInspector::GetElement()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString AttributeInspector::GetAttributeName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString AttributeInspector::GetAttributeValueBeforeChange()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString AttributeInspector::GetAttributeValueAfterChange()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void AttributeInspector::SetAttributeValueAfterChange(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void AttributeInspector::CancelChange()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL AttributeInspector::GetVisible()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void AttributeInspector::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ElementList properties

/////////////////////////////////////////////////////////////////////////////
// ElementList operations

BOOL ElementList::GetVisible()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ElementList::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH ElementList::GetItem(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ElementList::GetCount()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH ElementList::InsertItem(LPCTSTR name, LPCTSTR description, long index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, description, index);
	return result;
}

LPDISPATCH ElementList::InsertSortedItem(LPCTSTR name, LPCTSTR description)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		name, description);
	return result;
}

void ElementList::RemoveItem(VARIANT* index)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}

void ElementList::RemoveAllItems()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString ElementList::GetTabName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ElementList::SetTabName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString ElementList::GetSelectedName()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL ElementList::GetIsInsert()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ElementList::SetIsInsert(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void ElementList::SelectTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

CString ElementList::GetNameToSelect()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ElementList::SetNameToSelect(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void ElementList::AddTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

void ElementList::RemoveTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}


/////////////////////////////////////////////////////////////////////////////
// ElementListItem properties

/////////////////////////////////////////////////////////////////////////////
// ElementListItem operations

CString ElementListItem::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ElementListItem::GetDescription()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void ElementListItem::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL ElementListItem::GetRequired()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ElementListItem::SetRequired(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ElementListItem::GetUsageCount()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ApplicationResources properties

/////////////////////////////////////////////////////////////////////////////
// ApplicationResources operations

LPDISPATCH ApplicationResources::item(VARIANT* index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		index);
	return result;
}

long ApplicationResources::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _ResultsManager properties

/////////////////////////////////////////////////////////////////////////////
// _ResultsManager operations

void _ResultsManager::ShowLinkLogTab()
{
	InvokeHelper(0x0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ResultsManager::HideLinkLogTab()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ResultsManager::AddWebTab(LPCTSTR tabName, LPDISPATCH extDisp)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, extDisp);
}

void _ResultsManager::NavigateInWebTab(LPCTSTR tabName, LPCTSTR URL)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, URL);
}

void _ResultsManager::SelectTab(LPCTSTR tabName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName);
}

void _ResultsManager::RemoveTab(LPCTSTR tabName, BOOL delayed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 tabName, delayed);
}

BOOL _ResultsManager::GetVisible()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ResultsManager::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _ResultsManager::GetFrontmostTabName()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _ResultsManager::GetIsLinkLogTabVisible()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL _ResultsManager::ShowTab(LPCTSTR tabName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		tabName);
	return result;
}

BOOL _ResultsManager::HideTab(LPCTSTR tabName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		tabName);
	return result;
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
// CommandBarButton properties

/////////////////////////////////////////////////////////////////////////////
// CommandBarButton operations

void CommandBarButton::Copy(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarButton::Delete()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CommandBarButton::Move(VARIANT* toBar, VARIANT* before)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 toBar, before);
}

void CommandBarButton::Reset()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CommandBarButton::GetBuiltIn()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
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

BOOL CommandBarButton::GetBeginGroup()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBeginGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarButton::GetEnabled()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarButton::GetVisible()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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

BOOL CommandBarButton::GetBuiltInFace()
{
	BOOL result;
	InvokeHelper(0x10003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CommandBarButton::SetBuiltInFace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
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
