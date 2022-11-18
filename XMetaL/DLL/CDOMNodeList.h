// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// #import "...\\xmetal.tlb" no_namespace
// CDOMNodeList wrapper class

class CDOMNodeList : public COleDispatchDriver
{
public:
	CDOMNodeList() {} // Calls COleDispatchDriver default constructor
	CDOMNodeList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDOMNodeList(const CDOMNodeList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// DOMNodeList methods
public:
	LPDISPATCH item(long index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, index);
		return result;
	}
	long get_length()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// DOMNodeList properties
public:

};
