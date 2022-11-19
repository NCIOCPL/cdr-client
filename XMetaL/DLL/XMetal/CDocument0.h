// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CDocument0 wrapper class

class CDocument0 : public COleDispatchDriver
{
public:
	CDocument0() {} // Calls COleDispatchDriver default constructor
	CDocument0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDocument0(const CDocument0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// _Document methods
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
	LPDISPATCH createElement(LPCTSTR name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, name);
		return result;
	}
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, target, data);
		return result;
	}
	LPDISPATCH createTextNode(LPCTSTR data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, data);
		return result;
	}
	LPDISPATCH createComment(LPCTSTR data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, data);
		return result;
	}
	LPDISPATCH createDocumentFragment()
	{
		LPDISPATCH result;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_documentElement()
	{
		LPDISPATCH result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH createAttribute(LPCTSTR name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, name);
		return result;
	}
	LPDISPATCH createEntityReference(LPCTSTR name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, name);
		return result;
	}
	LPDISPATCH createCDATASection(LPCTSTR data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, data);
		return result;
	}
	LPDISPATCH getElementsByTagName(LPCTSTR tagName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, tagName);
		return result;
	}
	LPDISPATCH get_doctype()
	{
		LPDISPATCH result;
		InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_implementation()
	{
		LPDISPATCH result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH getNodesByXPath(LPCTSTR xpathExpression)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, xpathExpression);
		return result;
	}
	CString get_name()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_FullName()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Title()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Title(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Saved()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Saved(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Save()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SaveAs(VARIANT * FileName, BOOL AddToRecentFiles)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, AddToRecentFiles);
	}
	void Close(long SaveChanges)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges);
	}
	BOOL Undo(long Times)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Times);
		return result;
	}
	BOOL Redo(long Times)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Times);
		return result;
	}
	void Activate()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ScrollToSelection()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_InCurrentProject()
	{
		BOOL result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_Path()
	{
		CString result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_BodyAttribute(LPCTSTR attrName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, attrName);
		return result;
	}
	void put_BodyAttribute(LPCTSTR attrName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, attrName, newValue);
	}
	CString get_DocumentTitle()
	{
		CString result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DocumentTitle(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString UniqueAttributeValue(LPCTSTR AttributeName, LPCTSTR prefix, VARIANT * number)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, AttributeName, prefix, number);
		return result;
	}
	void Validate()
	{
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Range()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsXML()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsSGML()
	{
		BOOL result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsHTML()
	{
		BOOL result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_ViewType()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ViewType(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_CustomDocumentProperties()
	{
		LPDISPATCH result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_MacroFile()
	{
		CString result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsValid()
	{
		BOOL result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Reload()
	{
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RefreshCssStyle()
	{
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL Layout()
	{
		BOOL result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_LocalPath()
	{
		CString result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_LocalFullName()
	{
		CString result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsEntityDeclared(LPCTSTR EntityName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, EntityName);
		return result;
	}
	void DeleteEntityDeclaration(LPCTSTR EntityName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, EntityName);
	}
	void DeclareTextEntity(LPCTSTR EntityName, LPCTSTR entityContent, long notUsed)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, EntityName, entityContent, notUsed);
	}
	void DeclareExternalEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, EntityName, publicName, FileName);
	}
	void DeclareGraphicEntity(LPCTSTR EntityName, LPCTSTR publicIdentifier, LPCTSTR systemIdentifier, LPCTSTR notationName, long notUsed)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, EntityName, publicIdentifier, systemIdentifier, notationName, notUsed);
	}
	LPDISPATCH get_ChangedNodes()
	{
		LPDISPATCH result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ClearNodeChangedStates(LPDISPATCH inNode, BOOL deep)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, inNode, deep);
	}
	void ClearAllChangedStates()
	{
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL GetNodeState(LPCTSTR stateName, LPDISPATCH inNode)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, stateName, inNode);
		return result;
	}
	void HideInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName, elementType);
	}
	void ShowInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName, elementType);
	}
	CString get_BrowserURL()
	{
		CString result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_BrowserURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_BrowserApplication()
	{
		CString result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_BrowserApplication(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void PreviewInBrowser(LPCTSTR Browser)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Browser);
	}
	BOOL get_RulesChecking()
	{
		BOOL result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_RulesChecking(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void UndoClear()
	{
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString GetRenderedContent(LPDISPATCH inNode)
	{
		CString result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, inNode);
		return result;
	}
	void SetRenderedContent(LPDISPATCH inNode, LPCTSTR renderedContent)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, inNode, renderedContent);
	}
	LPDISPATCH createCharacterReference(long value)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, value);
		return result;
	}
	LPDISPATCH getElementById(LPCTSTR value)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, value);
		return result;
	}
	long get_PreviousViewType()
	{
		long result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_RulesFile()
	{
		CString result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_DOMEnforceValid()
	{
		BOOL result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DOMEnforceValid(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_DisplayStylesFile()
	{
		CString result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL AcceptDropFormat(VARIANT * dropFormat, LPCTSTR formatName)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT VTS_BSTR;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, dropFormat, formatName);
		return result;
	}
	BOOL get_StructureViewVisible()
	{
		BOOL result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_StructureViewVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString CreatePreviewFile()
	{
		CString result;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CustomProperties()
	{
		LPDISPATCH result;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_styleSheets()
	{
		LPDISPATCH result;
		InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsInWellFormedEditingMode()
	{
		BOOL result;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ChangedNodesbyKey(LPCTSTR key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, key);
		return result;
	}
	void ClearNodeChangedStatesbyKey(LPCTSTR key, LPDISPATCH inNode, BOOL deep)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, key, inNode, deep);
	}
	void ClearAllChangedStatesbyKey(LPCTSTR key)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, key);
	}
	BOOL GetNodeStatebyKey(LPCTSTR key, LPCTSTR stateName, LPDISPATCH inNode)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, key, stateName, inNode);
		return result;
	}
	CString get_AllUsersMacroFile()
	{
		CString result;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_CurrentUserMacroFile()
	{
		CString result;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_xml()
	{
		CString result;
		InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Customizations()
	{
		LPDISPATCH result;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_TrackRevisions()
	{
		BOOL result;
		InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_TrackRevisions(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_MinimizeTagIcons()
	{
		BOOL result;
		InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_MinimizeTagIcons(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ResourceSet()
	{
		LPDISPATCH result;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_DropText()
	{
		CString result;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DropText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPUNKNOWN get_DropDataObject()
	{
		LPUNKNOWN result;
		InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	void DropNotAllowed()
	{
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_DropPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_FormattingUpdating()
	{
		BOOL result;
		InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FormattingUpdating(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void GotoNextChange()
	{
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void GotoPrevChange()
	{
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL CanAcceptOrRejectChange()
	{
		BOOL result;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void AcceptChange()
	{
		InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RejectChange()
	{
		InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long AcceptAllChanges()
	{
		long result;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long RejectAllChanges()
	{
		long result;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ValidationErrorList()
	{
		LPDISPATCH result;
		InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CheckData()
	{
		LPDISPATCH result;
		InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_MouseOverNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Host()
	{
		LPDISPATCH result;
		InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void MoveDropPoint(LPDISPATCH newDropPoint)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newDropPoint);
	}
	LPDISPATCH get_DropRange()
	{
		LPDISPATCH result;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH createElementNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, namespaceURI, qualifiedName);
		return result;
	}
	LPDISPATCH createAttributeNS(LPCTSTR namespaceURI, LPCTSTR qualifiedName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, namespaceURI, qualifiedName);
		return result;
	}
	LPDISPATCH getElementsByTagNameNS(LPCTSTR namespaceURI, LPCTSTR localName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, namespaceURI, localName);
		return result;
	}
	CString get_xmlWithCT()
	{
		CString result;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_RMPreserveMode()
	{
		BOOL result;
		InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_RMPreserveMode(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void formatGraphicTable(LPDISPATCH tblNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tblNode);
	}
	LPDISPATCH get_ActiveInPlaceControl()
	{
		LPDISPATCH result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH CreateMark(LPCTSTR ownerKey, long markID, long Flags, VARIANT& userData, LPDISPATCH position)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT VTS_DISPATCH;
		InvokeHelper(0x120, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ownerKey, markID, Flags, &userData, position);
		return result;
	}
	LPDISPATCH get_MarkWalker(LPCTSTR ownerKey)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ownerKey);
		return result;
	}
	void SetMarkPresentationService(LPCTSTR ownerKey, long mpsType, LPDISPATCH mpServiceImpl)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH;
		InvokeHelper(0x122, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ownerKey, mpsType, mpServiceImpl);
	}
	void SetCTMRulesService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x123, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ownerKey, mpServiceImpl);
	}
	void SetImageService(LPCTSTR ownerKey, LPDISPATCH mpServiceImpl)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x124, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ownerKey, mpServiceImpl);
	}
	void EmptyClipboard()
	{
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Clipboard()
	{
		LPDISPATCH result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_DropClipboardText()
	{
		BOOL result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_DropInternalText()
	{
		BOOL result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN;
		InvokeHelper(0x134, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, formatName, data);
		return result;
	}
	LPDISPATCH get_CRLocator()
	{
		LPDISPATCH result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_CRLocator(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ReadOnlyHint()
	{
		BOOL result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ReadOnlyHint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH createElementWF(LPCTSTR name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x137, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, name);
		return result;
	}
	LPDISPATCH createAttributeWF(LPCTSTR name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x138, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, name);
		return result;
	}
	LPDISPATCH createTextNodeWF(LPCTSTR data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x139, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, data);
		return result;
	}
	void attachTransclusion(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_I4;
		InvokeHelper(0x140, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, transNode, transResult);
	}
	void detachTransclusion(LPDISPATCH srcNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x141, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode);
	}
	void showHideTransclusion(LPDISPATCH srcNode, BOOL show)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x142, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, show);
	}
	void importNode(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x143, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	long get_AutoSetImageWidthHeight()
	{
		long result;
		InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoSetImageWidthHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x144, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AutoScaleImageWidth()
	{
		long result;
		InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoScaleImageWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AutoScaleImageHeight()
	{
		long result;
		InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoScaleImageHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void attachTransclusionEx(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_I4;
		InvokeHelper(0x147, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, transNode, transResult);
	}
	void detachTransclusionEx(LPDISPATCH srcNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x148, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode);
	}
	void showHideTransclusionEx(LPDISPATCH srcNode, BOOL show)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x149, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, show);
	}
	CString getTextEntityReplacementText(LPCTSTR entName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x150, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, entName);
		return result;
	}
	BOOL get_DropTextIsMultiCell()
	{
		BOOL result;
		InvokeHelper(0x151, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void HideEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x152, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName, elementType);
	}
	void ShowEditButtonInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x153, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attrName, elementType);
	}
	LPDISPATCH get_EditAttributeNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_EditAttributeName()
	{
		CString result;
		InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_EditAttributeValue()
	{
		CString result;
		InvokeHelper(0x156, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_EditAttributeValue(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x156, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_RefreshCssStyleDoc()
	{
		LPDISPATCH result;
		InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void RefreshCssStyleToAppend(LPCTSTR cssToAppend)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x158, DISPATCH_METHOD, VT_EMPTY, NULL, parms, cssToAppend);
	}
	void ShowXInclude(LPDISPATCH ctxNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x159, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ctxNode);
	}
	void HideXInclude(LPDISPATCH ctxNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x160, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ctxNode);
	}
	void UpdateXInclude(LPDISPATCH ctxNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x161, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ctxNode);
	}
	void OpenXIncludeTarget(LPDISPATCH xincludeNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xincludeNode);
	}
	CString ExportWithXIncludesToXML()
	{
		CString result;
		InvokeHelper(0x163, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ActiveXIncludeNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x164, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL IsXIncludeNode(LPDISPATCH node)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x165, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, node);
		return result;
	}
	BOOL get_IsNamespaceAware()
	{
		BOOL result;
		InvokeHelper(0x166, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void PurgeXIncludeCache()
	{
		InvokeHelper(0x167, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetXIncludeFeature(long feature, VARIANT * val)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT;
		InvokeHelper(0x168, DISPATCH_METHOD, VT_EMPTY, NULL, parms, feature, val);
	}
	LPDISPATCH get_LinkResolutionErrorList()
	{
		LPDISPATCH result;
		InvokeHelper(0x169, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString ConvertXIncludeTargetToXML(LPCTSTR Href, LPCTSTR xptr)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x16a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Href, xptr);
		return result;
	}
	void ExportWithXIncludesToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x16b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	long GetXIncludeTargetState(LPDISPATCH xincludeNode)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x16c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, xincludeNode);
		return result;
	}
	void RegisterNonCopyableAttr(LPCTSTR elemNS, LPCTSTR elemName, LPCTSTR attrNS, LPCTSTR attrName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x16d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elemNS, elemName, attrNS, attrName);
	}
	BOOL get_BackgroundSpellchecking()
	{
		BOOL result;
		InvokeHelper(0x16e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_BackgroundSpellchecking(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SpellAutoCorrect()
	{
		BOOL result;
		InvokeHelper(0x16f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SpellAutoCorrect(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL IsSpellingCorrect(long mode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x170, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, mode);
		return result;
	}
	CString GetSpellingResult(long mode)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x171, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, mode);
		return result;
	}
	BOOL ReplaceWord(LPCTSTR word)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x172, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, word);
		return result;
	}
	BOOL IgnoreWordSpelling()
	{
		BOOL result;
		InvokeHelper(0x173, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL AddWordToDictionary()
	{
		BOOL result;
		InvokeHelper(0x174, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetSpellCheckerService(LPDISPATCH mpServiceImpl)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x175, DISPATCH_METHOD, VT_EMPTY, NULL, parms, mpServiceImpl);
	}
	BOOL get_InlineMediaVisible()
	{
		BOOL result;
		InvokeHelper(0x176, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_InlineMediaVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x176, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_msgHwnd()
	{
		long result;
		InvokeHelper(0x177, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgMessage()
	{
		long result;
		InvokeHelper(0x178, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgWParam()
	{
		long result;
		InvokeHelper(0x179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgLParam()
	{
		long result;
		InvokeHelper(0x17a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgTime()
	{
		long result;
		InvokeHelper(0x17b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgX()
	{
		long result;
		InvokeHelper(0x17c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_msgY()
	{
		long result;
		InvokeHelper(0x17d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_WindowHandle()
	{
		long result;
		InvokeHelper(0x17e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_RangeNearestPoint(long screenX, long screenY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x17f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, screenX, screenY);
		return result;
	}
	void BeginMutations(LPCTSTR niceName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x180, DISPATCH_METHOD, VT_EMPTY, NULL, parms, niceName);
	}
	void EndMutations(BOOL didChange)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x181, DISPATCH_METHOD, VT_EMPTY, NULL, parms, didChange);
	}
	unsigned short GetNodeSpellLanguage(LPDISPATCH inNode)
	{
		unsigned short result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x182, DISPATCH_METHOD, VT_UI2, (void*)&result, parms, inNode);
		return result;
	}
	BOOL IsDummyNode(LPDISPATCH node)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x183, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, node);
		return result;
	}
	long HighlightRange(LPCTSTR location, long highlightType, long highlightState, LPCTSTR hint)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x184, DISPATCH_METHOD, VT_I4, (void*)&result, parms, location, highlightType, highlightState, hint);
		return result;
	}
	long SetHighlightedRangeState(long hId, long hState)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x185, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hId, hState);
		return result;
	}
	LPDISPATCH GetHighlightedRange(long hId)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x186, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, hId);
		return result;
	}
	void ScrollSelectionToTop()
	{
		InvokeHelper(0x187, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ScrollSelectionToBottom()
	{
		InvokeHelper(0x188, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddCompareFunc(LPCTSTR funcName, LPDISPATCH funcImpl)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x189, DISPATCH_METHOD, VT_EMPTY, NULL, parms, funcName, funcImpl);
	}
	void RemoveCompareFunc(LPCTSTR funcName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, funcName);
	}
	CString get_CurrentCSS()
	{
		CString result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_CurrentCSS(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_DefaultWTDictionaryId()
	{
		CString result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DefaultWTDictionaryId(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString exportTransclusion(LPDISPATCH srcNode)
	{
		CString result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x193, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, srcNode);
		return result;
	}
	BOOL get_internalSubsetEditable()
	{
		BOOL result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_internalSubsetEditable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_IsNotationDeclared(LPCTSTR notationName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, notationName);
		return result;
	}
	BOOL DeclareNotation(LPCTSTR notationName, LPCTSTR pubId, LPCTSTR sysId)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x196, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, notationName, pubId, sysId);
		return result;
	}
	BOOL DeleteNotationDeclaration(LPCTSTR notationName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x197, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, notationName);
		return result;
	}
	VARIANT GetUserString(LPDISPATCH node, LPCTSTR name)
	{
		VARIANT result;
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR;
		InvokeHelper(0x198, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, node, name);
		return result;
	}
	void SetUserString(LPDISPATCH node, LPCTSTR name, VARIANT& val)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_VARIANT;
		InvokeHelper(0x199, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node, name, &val);
	}
	CString QueryAttributes(LPDISPATCH node, LPCTSTR mode)
	{
		CString result;
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR;
		InvokeHelper(0x19a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, node, mode);
		return result;
	}
	void includeTransclusionEx(LPDISPATCH srcNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x19b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode);
	}
	void put_TagsOnGraphicalTables(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x19c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_TagsOnGraphicalTables()
	{
		BOOL result;
		InvokeHelper(0x19c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void includeTransclusionEx2(LPDISPATCH srcNode, LPDISPATCH process)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH;
		InvokeHelper(0x19d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, process);
	}
	void SetSubjectScheme(LPCTSTR jsonScheme)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x19e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, jsonScheme);
	}
	void AddValidationError(LPCTSTR Msg, LPDISPATCH node)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x19f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Msg, node);
	}
	void AddValidationWarning(LPCTSTR Msg, LPDISPATCH node)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH;
		InvokeHelper(0x1a0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Msg, node);
	}
	void StartEditNode(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1a1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	void EndEditNode(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1a2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	void ScrollToSelectionEx(long pos)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1a3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pos);
	}
	void attachTransclusion2(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult, LPCTSTR str)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_I4 VTS_BSTR;
		InvokeHelper(0x1a4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, transNode, transResult, str);
	}
	void attachTransclusionEx2(LPDISPATCH srcNode, LPDISPATCH transNode, long transResult, LPCTSTR str)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_I4 VTS_BSTR;
		InvokeHelper(0x1a5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, srcNode, transNode, transResult, str);
	}
	BOOL GenerateCTMFile(LPCTSTR ctmFilePath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1a6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ctmFilePath);
		return result;
	}
	CString get_FileId()
	{
		CString result;
		InvokeHelper(0x1a7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_FileType()
	{
		CString result;
		InvokeHelper(0x1a8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ViewSite()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ShowXmlIsland(LPDISPATCH islandNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1aa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, islandNode);
	}
	void HideXmlIsland(LPDISPATCH islandNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1ab, DISPATCH_METHOD, VT_EMPTY, NULL, parms, islandNode);
	}
	void DetachXmlIsland(LPDISPATCH islandNode)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1ac, DISPATCH_METHOD, VT_EMPTY, NULL, parms, islandNode);
	}
	void UpdateXmlIsland(LPDISPATCH islandNode, LPCTSTR strReuseElems, LPDISPATCH alienNode, LPCTSTR filePath, long crInstanceId, LPCTSTR resourceId, long features)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_DISPATCH VTS_BSTR VTS_I4 VTS_BSTR VTS_I4;
		InvokeHelper(0x1ad, DISPATCH_METHOD, VT_EMPTY, NULL, parms, islandNode, strReuseElems, alienNode, filePath, crInstanceId, resourceId, features);
	}
	void UpdateTextIsland(LPDISPATCH islandNode, LPCTSTR filePath, long crInstanceId, LPCTSTR resourceId)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_I4 VTS_BSTR;
		InvokeHelper(0x1ae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, islandNode, filePath, crInstanceId, resourceId);
	}
	BOOL IsXmlIslandVisible(LPDISPATCH node)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1af, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, node);
		return result;
	}
	BOOL IsXmlIslandAttached(LPDISPATCH islandNode)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x1b0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, islandNode);
		return result;
	}
	void AutoId(LPCTSTR attName, LPCTSTR elemNames, LPCTSTR jsonConfig)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x1b1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attName, elemNames, jsonConfig);
	}
	void AutoOverwriteId(LPCTSTR attName, LPCTSTR elemNames, BOOL exclude, LPCTSTR jsonConfig)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL VTS_BSTR;
		InvokeHelper(0x1b2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, attName, elemNames, exclude, jsonConfig);
	}
	void RemoveEmptyAttributes()
	{
		InvokeHelper(0x1b3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long FormattingUpdatingCommand(long command)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, command);
		return result;
	}
	VARIANT DocReservedCommand(LPCTSTR command, LPCTSTR sParam, long lParam)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0x1b5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, command, sParam, lParam);
		return result;
	}
	CString GetHighlightedRangesIDs(long hIdType)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, hIdType);
		return result;
	}
	long GetHighlightedRangeState(long hId)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hId);
		return result;
	}
	long GetHighlightedRangeType(long hId)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hId);
		return result;
	}
	long SetHighlightedRangeType(long hId, long hType)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x1b9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hId, hType);
		return result;
	}

	// _Document properties
public:

};
