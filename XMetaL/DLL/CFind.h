// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CFind wrapper class

class CFind : public COleDispatchDriver
{
public:
	CFind() {} // Calls COleDispatchDriver default constructor
	CFind(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFind(const CFind& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Find methods
public:
	BOOL Execute(LPCTSTR FindString, LPCTSTR ReplaceString, LPCTSTR ConstraintString, BOOL MatchCase, BOOL MatchWholeWords, BOOL MatchPatterns, BOOL Forward, BOOL Wrap, long action, BOOL SetFindDialogOptions)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FindString, ReplaceString, ConstraintString, MatchCase, MatchWholeWords, MatchPatterns, Forward, Wrap, action, SetFindDialogOptions);
		return result;
	}
	BOOL ExecuteEx(LPCTSTR FindString, LPCTSTR ReplaceString, LPCTSTR ConstraintString, BOOL MatchCase, BOOL MatchWholeWords, BOOL MatchPatterns, BOOL Forward, BOOL Wrap, BOOL HighlightAllOccurences, long action, BOOL SetFindDialogOptions)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FindString, ReplaceString, ConstraintString, MatchCase, MatchWholeWords, MatchPatterns, Forward, Wrap, HighlightAllOccurences, action, SetFindDialogOptions);
		return result;
	}

	// Find properties
public:

};
