// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "XMetaL/xmetal.tlb" no_namespace
// CSelection wrapper class

class CSelection : public COleDispatchDriver
{
public:
	CSelection() {} // Calls COleDispatchDriver default constructor
	CSelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSelection(const CSelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Selection methods
public:
	void TypeText(LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text);
	}
	void Cut()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Copy()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Paste()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Delete()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveLeft(long MovementType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MovementType);
	}
	void MoveRight(long MovementType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MovementType);
	}
	void MoveUp(long MovementType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MovementType);
	}
	void MoveDown(long MovementType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MovementType);
	}
	void MoveColumnLeft()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveColumnRight()
	{
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveRowUp()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveRowDown()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MergeCellLeft()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MergeCellRight()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MergeCellUp()
	{
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MergeCellDown()
	{
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SplitCellColumn()
	{
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SplitCellRow()
	{
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertRowsAbove(long number)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, number);
	}
	void InsertRowsBelow(long number)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, number);
	}
	void InsertColumnsLeft(long number)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, number);
	}
	void InsertColumnsRight(long number)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, number);
	}
	void HomeKey(long unit, long extend)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, unit, extend);
	}
	void EndKey(long unit, long extend)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, unit, extend);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_HorizontalAlignment()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HorizontalAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void GotoNext(long GotoItem)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GotoItem);
	}
	void GotoPrevious(long GotoItem)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GotoItem);
	}
	void Collapse(long CollapseDirection)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CollapseDirection);
	}
	void PasteString(LPCTSTR String)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, String);
	}
	void InsertForm(long FormElement)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FormElement);
	}
	void InsertElement(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	void InsertElementWithRequired(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	CString get_ContainerName()
	{
		CString result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ContainerName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void RemoveContainerTags()
	{
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SplitContainer()
	{
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_ContainerAttribute(LPCTSTR attrName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, attrName);
		return result;
	}
	void put_ContainerAttribute(LPCTSTR attrName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, attrName, newValue);
	}
	void InsertComment()
	{
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertBreak()
	{
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertHorizontalRule()
	{
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertNBSP()
	{
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void JoinElementToPreceding()
	{
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertEntity(LPCTSTR EntityName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, EntityName);
	}
	void Surround(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	void SelectElement()
	{
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void TypingSplit()
	{
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteColumn()
	{
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteRow()
	{
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertTable(long NumRows, long NumCols, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumRows, NumCols, BGColor, TableWidth, TableWidthUnit, TableBorder, CellPadding, CellSpacing);
	}
	void InsertCaption()
	{
		InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Indent()
	{
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Outdent()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertImage(LPCTSTR Src, LPCTSTR Alt, LPCTSTR Align, LPCTSTR Width, LPCTSTR Height, LPCTSTR Border)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Src, Alt, Align, Width, Height, Border);
	}
	CString get_Style()
	{
		CString result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Style(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void PageUp()
	{
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PageDown()
	{
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ToggleTableCellType()
	{
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_ElementName(long AncestorNum)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, AncestorNum);
		return result;
	}
	CString get_elementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, attrName, ElementName, SkipNum);
		return result;
	}
	void put_elementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
		InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, attrName, ElementName, SkipNum, newValue);
	}
	BOOL get_IsParentElement(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	void ListIndent(VARIANT * ElementName)
	{
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	void ListOutdent(VARIANT * ElementName)
	{
		static BYTE parms[] = VTS_PVARIANT;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_IsInsertionPoint()
	{
		BOOL result;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void InsertLink(LPCTSTR Href, LPCTSTR target)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Href, target);
	}
	LPDISPATCH get_ContainerNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SelectBeforeNode(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	void SelectAfterNode(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	void SelectNodeContents(LPDISPATCH node)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms, node);
	}
	void SelectAfterContainer()
	{
		InvokeHelper(0x48, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SelectBeforeContainer()
	{
		InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SelectContainerContents()
	{
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Find()
	{
		LPDISPATCH result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void BasicPaste()
	{
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PasteStringWithInterpret(LPCTSTR String)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, String);
	}
	BOOL get_CanInsert(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL get_CanChange(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL get_CanSurround(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL get_CanPaste(LPCTSTR String, BOOL interpret)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, String, interpret);
		return result;
	}
	BOOL get_IsValid()
	{
		BOOL result;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void MoveToDocumentStart()
	{
		InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveToDocumentEnd()
	{
		InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SelectAll()
	{
		InvokeHelper(0x55, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL ExtendTo(LPDISPATCH Selection)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Selection);
		return result;
	}
	BOOL get_Contains(LPDISPATCH Selection, BOOL IncludeSelOnEdge)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection, IncludeSelOnEdge);
		return result;
	}
	BOOL get_IsEqual(LPDISPATCH Selection)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection);
		return result;
	}
	BOOL get_Overlaps(LPDISPATCH Selection)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection);
		return result;
	}
	BOOL MoveToElement(LPCTSTR ElementName, BOOL Forward)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ElementName, Forward);
		return result;
	}
	BOOL get_CanInsertText()
	{
		BOOL result;
		InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void InsertProcessingInstruction()
	{
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH result;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsAdjacent(LPDISPATCH Selection)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection);
		return result;
	}
	BOOL get_IsLessThan(LPDISPATCH Selection, BOOL OrEqual)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection, OrEqual);
		return result;
	}
	BOOL get_IsGreaterThan(LPDISPATCH Selection, BOOL OrEqual)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Selection, OrEqual);
		return result;
	}
	BOOL get_hasAttribute(LPCTSTR attrName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, attrName);
		return result;
	}
	void InsertCALSTable(long NumRows, long NumCols, LPCTSTR TableElement, BOOL WantTHead, BOOL WantTFoot)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL VTS_BOOL;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumRows, NumCols, TableElement, WantTHead, WantTFoot);
	}
	void InsertWithTemplate(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	void InsertCDATASection()
	{
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Validate()
	{
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertReplaceableText(LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text);
	}
	void ContractCell(long ContractDirection)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ContractDirection);
	}
	BOOL get_ReadOnlyContainer()
	{
		BOOL result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ReadOnlyContainer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ReadOnly()
	{
		BOOL result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Select()
	{
		InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Duplicate()
	{
		LPDISPATCH result;
		InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL Layout()
	{
		BOOL result;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_CollapsedContainerTags()
	{
		BOOL result;
		InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CollapsedContainerTags(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CollapsedTags()
	{
		BOOL result;
		InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_CanDelete()
	{
		BOOL result;
		InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_CanRemoveContainerTags()
	{
		BOOL result;
		InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_HiddenContainer()
	{
		BOOL result;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HiddenContainer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_hidden()
	{
		BOOL result;
		InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_ContainerStyle()
	{
		CString result;
		InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ContainerStyle(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL FindInsertLocation(LPCTSTR ElementName, BOOL Forward)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ElementName, Forward);
		return result;
	}
	void DropFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	BOOL get_SVCollapsedContainer()
	{
		BOOL result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SVCollapsedContainer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void TypeTab(BOOL shift)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms, shift);
	}
	void ToggleInline(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	BOOL get_CanSplitContainer(LPCTSTR ElementName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL get_CanJoinElementToPreceding()
	{
		BOOL result;
		InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SplitToElementType(LPCTSTR ElementName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ElementName);
	}
	CString get_StyleElement()
	{
		CString result;
		InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_StyleElement(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_NonRemovableContainer()
	{
		BOOL result;
		InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_NonRemovableContainer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL FindPasteLocation(LPCTSTR String, BOOL Forward)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, String, Forward);
		return result;
	}
	BOOL get_WritePermittedContainer()
	{
		BOOL result;
		InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_WritePermittedContainer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void PasteStringAsText(LPCTSTR String)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, String);
	}
	BOOL get_InContextOfType(LPCTSTR ContextType)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ContextType);
		return result;
	}
	BOOL get_IsParentElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName);
		return result;
	}
	BOOL get_CanInsertNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName);
		return result;
	}
	void InsertElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	void InsertElementWithRequiredNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	void InsertWithTemplateNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	LPDISPATCH get_CanInsertList()
	{
		LPDISPATCH result;
		InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CanChangeList()
	{
		LPDISPATCH result;
		InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ValidationErrorList()
	{
		LPDISPATCH result;
		InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_ElementNameNS(long AncestorNum)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, AncestorNum);
		return result;
	}
	BOOL get_CanChangeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName);
		return result;
	}
	CString get_ContainerNameNS()
	{
		CString result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ContainerNameNS(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_StyleNS()
	{
		CString result;
		InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_StyleNS(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CanSplitContainerNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName);
		return result;
	}
	void SplitToElementTypeNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	BOOL get_CanSurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName);
		return result;
	}
	void SurroundNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	void ToggleInlineNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	BOOL FindInsertLocationNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL;
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName, Forward);
		return result;
	}
	BOOL MoveToElementNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, BOOL Forward)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, elementNamespaceURI, elementLocalName, Forward);
		return result;
	}
	void ListIndentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	void ListOutdentNS(LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, elementNamespaceURI, elementLocalName);
	}
	BOOL get_hasAttributeNS(LPCTSTR namespaceURI, LPCTSTR localName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, namespaceURI, localName);
		return result;
	}
	CString get_ContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, attrNamespaceURI, attrLocalName);
		return result;
	}
	void put_ContainerAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, attrNamespaceURI, attrLocalName, newValue);
	}
	CString get_ElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum);
		return result;
	}
	void put_ElementAttributeNS(LPCTSTR attrNamespaceURI, LPCTSTR attrLocalName, LPCTSTR elementNamespaceURI, LPCTSTR elementLocalName, long SkipNum, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
		InvokeHelper(0xa3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, attrNamespaceURI, attrLocalName, elementNamespaceURI, elementLocalName, SkipNum, newValue);
	}
	void RejectAllChanges()
	{
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AcceptAllChanges()
	{
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_TextWithRM()
	{
		CString result;
		InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_TextWithRM(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CanPasteStrict(LPCTSTR String, BOOL interpret)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, String, interpret);
		return result;
	}
	void ToggleList(long type)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x107, DISPATCH_METHOD, VT_EMPTY, NULL, parms, type);
	}
	long get_screenTop(long rectOrd)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, rectOrd);
		return result;
	}
	long get_screenLeft(long rectOrd)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, rectOrd);
		return result;
	}
	long get_screenBottom(long rectOrd)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, rectOrd);
		return result;
	}
	long get_screenRight(long rectOrd)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, rectOrd);
		return result;
	}
	BOOL get_IsPointInside(long screenX, long screenY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, screenX, screenY);
		return result;
	}
	BOOL SelectNodeContentsAt(LPDISPATCH node, long offset, long length, LPCTSTR hint)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x10d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, node, offset, length, hint);
		return result;
	}
	CString get_SelectionLocation()
	{
		CString result;
		InvokeHelper(0x10e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SelectionLocation(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x10e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL CanSplitTable(BOOL belowThisRow)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x10f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, belowThisRow);
		return result;
	}
	void SplitTable(BOOL belowThisRow)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x110, DISPATCH_METHOD, VT_EMPTY, NULL, parms, belowThisRow);
	}
	BOOL CanSplitTableGroup(BOOL belowThisRow)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x111, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, belowThisRow);
		return result;
	}
	void SplitTableGroup(BOOL belowThisRow)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x112, DISPATCH_METHOD, VT_EMPTY, NULL, parms, belowThisRow);
	}
	BOOL CanMergeTable(BOOL withTableBelow)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x113, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, withTableBelow);
		return result;
	}
	void MergeTable(BOOL withTableBelow)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x114, DISPATCH_METHOD, VT_EMPTY, NULL, parms, withTableBelow);
	}
	BOOL get_IsMultiCellSelection()
	{
		BOOL result;
		InvokeHelper(0x115, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Cells()
	{
		LPDISPATCH result;
		InvokeHelper(0x116, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void InsertTableEx(long NumRows, long NumCols, LPCTSTR TableElement, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x117, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumRows, NumCols, TableElement, BGColor, TableWidth, TableWidthUnit, TableBorder, CellPadding, CellSpacing);
	}
	void InsertCALSTableEx(long NumRows, long NumCols, LPCTSTR TableElement, LPCTSTR tgroupElement, BOOL WantTHead, BOOL WantTFoot)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL;
		InvokeHelper(0x118, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumRows, NumCols, TableElement, tgroupElement, WantTHead, WantTFoot);
	}

	// Selection properties
public:

};
