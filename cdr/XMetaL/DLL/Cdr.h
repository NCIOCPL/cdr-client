/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Nov 15 11:30:44 2001
 */
/* Compiler settings for C:\cdr\src\CdrClient\Cdr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Cdr_h__
#define __Cdr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICommands_FWD_DEFINED__
#define __ICommands_FWD_DEFINED__
typedef interface ICommands ICommands;
#endif 	/* __ICommands_FWD_DEFINED__ */


#ifndef __Commands_FWD_DEFINED__
#define __Commands_FWD_DEFINED__

#ifdef __cplusplus
typedef class Commands Commands;
#else
typedef struct Commands Commands;
#endif /* __cplusplus */

#endif 	/* __Commands_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICommands_INTERFACE_DEFINED__
#define __ICommands_INTERFACE_DEFINED__

/* interface ICommands */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICommands;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("744ECEA9-3F8F-497C-ABCA-2A6C4C653466")
    ICommands : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE logon( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE retrieve( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE search( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE save( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE validate( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE logoff( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE edit( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isReadOnly( 
            /* [in] */ const BSTR __RPC_FAR *docType,
            /* [in] */ const BSTR __RPC_FAR *elemName,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE advancedSearch( 
            /* [retval][out] */ int __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_username( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE protUpdPerson( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getPersonAddress( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE particOrgs( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOrgAddress( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE pasteDocLink( 
            const BSTR __RPC_FAR *val,
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_session( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE checkIn( 
            /* [retval][out] */ int __RPC_FAR *pRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *logon )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *retrieve )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *search )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *save )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *validate )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *logoff )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *edit )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isReadOnly )( 
            ICommands __RPC_FAR * This,
            /* [in] */ const BSTR __RPC_FAR *docType,
            /* [in] */ const BSTR __RPC_FAR *elemName,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *advancedSearch )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *retVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_username )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *protUpdPerson )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getPersonAddress )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *particOrgs )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOrgAddress )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *pasteDocLink )( 
            ICommands __RPC_FAR * This,
            const BSTR __RPC_FAR *val,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_session )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *checkIn )( 
            ICommands __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pRet);
        
        END_INTERFACE
    } ICommandsVtbl;

    interface ICommands
    {
        CONST_VTBL struct ICommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommands_logon(This,pRet)	\
    (This)->lpVtbl -> logon(This,pRet)

#define ICommands_retrieve(This,pRet)	\
    (This)->lpVtbl -> retrieve(This,pRet)

#define ICommands_search(This,pRet)	\
    (This)->lpVtbl -> search(This,pRet)

#define ICommands_save(This,pRet)	\
    (This)->lpVtbl -> save(This,pRet)

#define ICommands_validate(This,pRet)	\
    (This)->lpVtbl -> validate(This,pRet)

#define ICommands_logoff(This,pRet)	\
    (This)->lpVtbl -> logoff(This,pRet)

#define ICommands_edit(This,pRet)	\
    (This)->lpVtbl -> edit(This,pRet)

#define ICommands_isReadOnly(This,docType,elemName,pVal)	\
    (This)->lpVtbl -> isReadOnly(This,docType,elemName,pVal)

#define ICommands_advancedSearch(This,retVal)	\
    (This)->lpVtbl -> advancedSearch(This,retVal)

#define ICommands_get_username(This,pVal)	\
    (This)->lpVtbl -> get_username(This,pVal)

#define ICommands_protUpdPerson(This,pRet)	\
    (This)->lpVtbl -> protUpdPerson(This,pRet)

#define ICommands_getPersonAddress(This,pRet)	\
    (This)->lpVtbl -> getPersonAddress(This,pRet)

#define ICommands_particOrgs(This,pRet)	\
    (This)->lpVtbl -> particOrgs(This,pRet)

#define ICommands_getOrgAddress(This,pRet)	\
    (This)->lpVtbl -> getOrgAddress(This,pRet)

#define ICommands_pasteDocLink(This,val,pRet)	\
    (This)->lpVtbl -> pasteDocLink(This,val,pRet)

#define ICommands_get_session(This,pVal)	\
    (This)->lpVtbl -> get_session(This,pVal)

#define ICommands_checkIn(This,pRet)	\
    (This)->lpVtbl -> checkIn(This,pRet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_logon_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_logon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_retrieve_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_retrieve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_search_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_save_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_validate_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_validate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_logoff_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_logoff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_edit_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_edit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_isReadOnly_Proxy( 
    ICommands __RPC_FAR * This,
    /* [in] */ const BSTR __RPC_FAR *docType,
    /* [in] */ const BSTR __RPC_FAR *elemName,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ICommands_isReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_advancedSearch_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *retVal);


void __RPC_STUB ICommands_advancedSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICommands_get_username_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICommands_get_username_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_protUpdPerson_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_protUpdPerson_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_getPersonAddress_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_getPersonAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_particOrgs_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_particOrgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_getOrgAddress_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_getOrgAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_pasteDocLink_Proxy( 
    ICommands __RPC_FAR * This,
    const BSTR __RPC_FAR *val,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_pasteDocLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICommands_get_session_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICommands_get_session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_checkIn_Proxy( 
    ICommands __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pRet);


void __RPC_STUB ICommands_checkIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommands_INTERFACE_DEFINED__ */



#ifndef __CDRLib_LIBRARY_DEFINED__
#define __CDRLib_LIBRARY_DEFINED__

/* library CDRLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CDRLib;

EXTERN_C const CLSID CLSID_Commands;

#ifdef __cplusplus

class DECLSPEC_UUID("41A6D40C-952F-4E4C-B329-CE529E4F3C16")
Commands;
#endif
#endif /* __CDRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
