// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "XMetaL/xmetal.tlb" no_namespace
// CApplication wrapper class

class CApplication : public COleDispatchDriver
{
public:
	CApplication() {} // Calls COleDispatchDriver default constructor
	CApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CApplication(const CApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// _Application methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Documents()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ActiveDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Selection()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_visible()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Quit(long SaveChanges)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges);
	}
	void Help(long HelpType, long ContextID)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpType, ContextID);
	}
	void Run(LPCTSTR MacroName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MacroName);
	}
	CString get_ProjectDirectory()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPUNKNOWN get_FX()
	{
		LPUNKNOWN result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	CString get_Path()
	{
		CString result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString PathToURL(LPCTSTR Path, VARIANT * Base)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Path, Base);
		return result;
	}
	CString URLToPath(LPCTSTR URL, VARIANT * Base)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, URL, Base);
		return result;
	}
	CString UniqueFileName(LPCTSTR Directory, LPCTSTR prefix, VARIANT * Extension)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Directory, prefix, Extension);
		return result;
	}
	BOOL FileExists(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL ReadableFileExists(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL WritableFileExists(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL WritableDirExists(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	CString FileToString(LPCTSTR Path)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Path);
		return result;
	}
	void Alert(LPCTSTR Msg, VARIANT * Title)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Msg, Title);
	}
	BOOL Confirm(LPCTSTR Msg, VARIANT * Title)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Msg, Title);
		return result;
	}
	CString Prompt(LPCTSTR Msg, VARIANT * Text, VARIANT * length, VARIANT * MaxLength, VARIANT * Title)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Msg, Text, length, MaxLength, Title);
		return result;
	}
	long MessageBox(LPCTSTR Msg, long Btns, VARIANT * Title)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PVARIANT;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Msg, Btns, Title);
		return result;
	}
	long NoticeBox(LPCTSTR Msg, LPCTSTR Btn1, VARIANT * Btn2, VARIANT * Btn3, VARIANT * Title)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Msg, Btn1, Btn2, Btn3, Title);
		return result;
	}
	LPDISPATCH get_CommandBars()
	{
		LPDISPATCH result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_WindowHandle()
	{
		long result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void EnableModeless(BOOL prop)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, prop);
	}
	void HelpFinder(LPCTSTR HelpFile)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpFile);
	}
	void HelpContext(LPCTSTR HelpFile, long ContextID)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpFile, ContextID);
	}
	void RefreshMacros()
	{
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RunKeyedMacro(LPCTSTR KeyString)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, KeyString);
	}
	LPDISPATCH get_DropPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void DisableMacro(LPCTSTR MacroName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MacroName);
	}
	CString get_MacroFile()
	{
		CString result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void Beep()
	{
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_AssetsPath()
	{
		CString result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void DisablePlainTextView()
	{
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_IsDocumentOpen(LPDISPATCH Document)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Document);
		return result;
	}
	BOOL CopyAssetFile(LPCTSTR SrcFile, LPCTSTR DstFile, BOOL ForceUpdate)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, SrcFile, DstFile, ForceUpdate);
		return result;
	}
	void ShowPage(LPCTSTR URL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, URL);
	}
	long get_DisplayAlerts()
	{
		long result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DisplayAlerts(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ActiveInPlaceControl()
	{
		LPDISPATCH result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_MouseOverNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetCursor(long cursorType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, cursorType);
	}
	void SetStatusText(LPCTSTR statusText)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, statusText);
	}
	void AppendMacro(LPCTSTR Label, LPCTSTR MacroName)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Label, MacroName);
	}
	LPDISPATCH get_CustomProperties()
	{
		LPDISPATCH result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_NewDocumentType()
	{
		LPDISPATCH result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_DropFileCount()
	{
		long result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_DropFileName(long index)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, index);
		return result;
	}
	BOOL get_InitComplete()
	{
		BOOL result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ResourceManager()
	{
		LPDISPATCH result;
		InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void PreventExit(LPCTSTR appName, LPCTSTR msgText)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, appName, msgText);
	}
	void AllowExit(LPCTSTR appName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, appName);
	}
	LPUNKNOWN get_DropDataObject()
	{
		LPUNKNOWN result;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	BOOL AcceptDropFormat(VARIANT * dropFormat, LPCTSTR formatName)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT VTS_BSTR;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, dropFormat, formatName);
		return result;
	}
	void EmptyClipboard()
	{
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_MakeFaceId(LPCTSTR groupName, long rowNum, long iconNum)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, groupName, rowNum, iconNum);
		return result;
	}
	void HideViewModeButton(long vtButton)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, vtButton);
	}
	void HideMiniContext()
	{
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void HideStructureView()
	{
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void HideStatusBarPane(long pane)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pane);
	}
	void SetWorkbookMode(BOOL modeOn)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parms, modeOn);
	}
	void DisableToolbarContextMenu()
	{
		InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DisableDocumentContextMenu()
	{
		InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_UnicodeSupported()
	{
		BOOL result;
		InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_ResolveURL()
	{
		CString result;
		InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ResolveURL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ResolveEntityInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_ValidationSuccess()
	{
		BOOL result;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ValidationSuccess(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void StopValidation()
	{
		InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PushInMacro(LPCTSTR MacroName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MacroName);
	}
	LPDISPATCH get_StyleElements()
	{
		LPDISPATCH result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_StyleElementName()
	{
		CString result;
		InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_StyleElementType()
	{
		CString result;
		InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void HideSplashDialog()
	{
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Clipboard()
	{
		LPDISPATCH result;
		InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_DropText()
	{
		CString result;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DropText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DropClipboardText()
	{
		BOOL result;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_DropInternalText()
	{
		BOOL result;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void MoveDropPoint(LPDISPATCH newDropPoint)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newDropPoint);
	}
	LPDISPATCH get_DropRange()
	{
		LPDISPATCH result;
		InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_AttributeInspector()
	{
		LPDISPATCH result;
		InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void DropNotAllowed()
	{
		InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddChangedNodeKey(LPCTSTR key)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_EMPTY, NULL, parms, key);
	}
	void RemoveChangedNodeKey(LPCTSTR key)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms, key);
	}
	CString get_AllUsersMacroFile()
	{
		CString result;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_CurrentUserMacroFile()
	{
		CString result;
		InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CheckData()
	{
		LPDISPATCH result;
		InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT CreateFormDlg(LPCTSTR formFileName, VARIANT * DOMNode)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, formFileName, DOMNode);
		return result;
	}
	LPDISPATCH get_ElementList()
	{
		LPDISPATCH result;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, formatName, data);
		return result;
	}
	LPDISPATCH get_ActiveContextMenu()
	{
		LPDISPATCH result;
		InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_CurrentUser()
	{
		CString result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_CurrentUserName()
	{
		CString result;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_CurrentUserName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_CurrentUserInitials()
	{
		CString result;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_CurrentUserInitials(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_CurrentUserRole()
	{
		CString result;
		InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_CurrentUserRole(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_DocumentRuleSet()
	{
		LPDISPATCH result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_exeName()
	{
		CString result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Properties()
	{
		LPDISPATCH result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Resources()
	{
		LPDISPATCH result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_StyleElementTypeNS()
	{
		CString result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_VersionNumber()
	{
		CString result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_OpenFileName()
	{
		CString result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_CancelOpenDocument()
	{
		BOOL result;
		InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CancelOpenDocument(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetForegroundWindow()
	{
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ShowWindow(long nCmdShow)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCmdShow);
	}
	void PostSetFocus(long nWndType)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nWndType);
	}
	BOOL get_CancelDocumentEventMacro()
	{
		BOOL result;
		InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CancelDocumentEventMacro(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_QueriedServiceName()
	{
		CString result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_QueriedServiceImpl(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AlwaysUndoClearAfterSave()
	{
		BOOL result;
		InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AlwaysUndoClearAfterSave(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void RegisterCRCL(LPDISPATCH CRCLcore)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CRCLcore);
	}
	void UnregisterCRCL()
	{
		InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddNewTemplateDialogFileExtension(LPCTSTR fileExt)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fileExt);
	}
	void AddOpenFileDialogFilter(LPCTSTR filterEntry, BOOL ignoredTreatAsXML)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms, filterEntry, ignoredTreatAsXML);
	}
	CString get_SkuName()
	{
		CString result;
		InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ResolveNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_SaveAsFileName()
	{
		CString result;
		InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_CancelSaveAsDocument()
	{
		BOOL result;
		InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CancelSaveAsDocument(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CancelNewDocument()
	{
		BOOL result;
		InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CancelNewDocument(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_UseMultiUserLocalTBRs()
	{
		BOOL result;
		InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UseMultiUserLocalTBRs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AddToRecentFileList(LPCTSTR FullName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FullName);
	}
	void RemoveFromRecentFileList(LPCTSTR FullName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FullName);
	}
	CString get_LastOpenDocumentPath()
	{
		CString result;
		InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_LastOpenDocumentPath(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_LastOpenImagePath()
	{
		CString result;
		InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_LastOpenImagePath(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_IsMRUOpenDocumentAction()
	{
		BOOL result;
		InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_UserSettingMode()
	{
		CString result;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_DefaultSaveAsExtension()
	{
		CString result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_DefaultSaveAsExtension(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DropTextIsMultiCell()
	{
		BOOL result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_ResolvePath()
	{
		CString result;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ResolvePath(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ParentURL()
	{
		CString result;
		InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ResolveAttrName()
	{
		CString result;
		InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ResolveAttrNS()
	{
		CString result;
		InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ResultsManager()
	{
		LPDISPATCH result;
		InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void RunAfterProcessDone(long ProcessID, LPCTSTR MacroName, LPCTSTR ResourceName, VARIANT& ResourceData)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_VARIANT;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ProcessID, MacroName, ResourceName, &ResourceData);
	}
	BOOL IsProcessRunning(long ProcessID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ProcessID);
		return result;
	}
	BOOL get_CancelAllDocumentsAction()
	{
		BOOL result;
		InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CancelAllDocumentsAction(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SaveAllDocumentsOption()
	{
		long result;
		InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_IniVariable(LPCTSTR iniVarName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, iniVarName);
		return result;
	}
	void put_IniVariable(LPCTSTR iniVarName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x8e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, iniVarName, newValue);
	}
	BOOL get_HandledViewEvent()
	{
		BOOL result;
		InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HandledViewEvent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void ShowSpellChecker(long command)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x90, DISPATCH_METHOD, VT_EMPTY, NULL, parms, command);
	}
	void MapXmlLangToWTDictionaryId(LPCTSTR langID, LPCTSTR dictionaryID)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms, langID, dictionaryID);
	}
	BOOL get_IsActivated(LPCTSTR featureName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, featureName);
		return result;
	}
	void DestroySplashScreenNow()
	{
		InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddOptionsPage(LPCTSTR pageXftFilePath, VARIANT * pageXftProxyDisp, LPCTSTR pageTitle, LPCTSTR pageCategory)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_BSTR;
		InvokeHelper(0x94, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pageXftFilePath, pageXftProxyDisp, pageTitle, pageCategory);
	}
	void RemoveOptionsPage(LPCTSTR pageXftFilePath)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pageXftFilePath);
	}
	void ShowOptionsPage(LPCTSTR pageTitle, LPCTSTR pageCategory)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x96, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pageTitle, pageCategory);
	}
	BOOL IsMacroDisabled(LPCTSTR MacroName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x97, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, MacroName);
		return result;
	}
	CString GetFilesList(long listType)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x98, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, listType);
		return result;
	}
	CString GetRecentFileList()
	{
		CString result;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString PushSxSManifest(LPCTSTR manifestPath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x9a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, manifestPath);
		return result;
	}
	void PopSxSManifest(LPCTSTR cookie)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, cookie);
	}
	LPDISPATCH get_CopyFileInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString GetDesktopSelectedItemPath(LPCTSTR windowType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, windowType);
		return result;
	}
	void ReloadMacros(long listType, LPCTSTR filesList)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, listType, filesList);
	}
	long AddFileChangeMacro(LPCTSTR filePath, LPCTSTR MacroName, LPCTSTR propertyName, VARIANT& propertyValue)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filePath, MacroName, propertyName, &propertyValue);
		return result;
	}
	long RemoveFileChangeMacro(LPCTSTR filePath, LPCTSTR MacroName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filePath, MacroName);
		return result;
	}
	long IsFileChangeMacro(LPCTSTR filePath, LPCTSTR MacroName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filePath, MacroName);
		return result;
	}
	CString get_TopLevelCustomizationFolder()
	{
		CString result;
		InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long RunMacroOnIdle(LPCTSTR MacroName, long mlsDelay, LPCTSTR propertyName, VARIANT& propertyValue)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_VARIANT;
		InvokeHelper(0xa3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MacroName, mlsDelay, propertyName, &propertyValue);
		return result;
	}
	long TerminateProcessEx(long ProcessID, long AppWindow, long Timeout, long Flags)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ProcessID, AppWindow, Timeout, Flags);
		return result;
	}
	void RunAfterProcessDone2(long ProcessID, LPCTSTR MacroName, LPCTSTR ResourceName, VARIANT& ResourceData)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_VARIANT;
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ProcessID, MacroName, ResourceName, &ResourceData);
	}
	void ReloadCTM(LPCTSTR ctmPath)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ctmPath);
	}
	void QuickSwitch()
	{
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT AppReservedCommand(LPCTSTR command, LPCTSTR sParam, long lParam)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4;
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, command, sParam, lParam);
		return result;
	}
	long RunScriptOnIdle(LPCTSTR ScriptObjectName, LPCTSTR MethodName, VARIANT& Parameter, long mlsDelay)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT VTS_I4;
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ScriptObjectName, MethodName, &Parameter, mlsDelay);
		return result;
	}
	VARIANT RunScript(LPCTSTR ScriptObjectName, LPCTSTR MethodName, VARIANT& Parameter)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT;
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, ScriptObjectName, MethodName, &Parameter);
		return result;
	}

	// _Application properties
public:

};
