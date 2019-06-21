

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jun 21 22:09:15 2019
 */
/* Compiler settings for MoonPDF.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MoonPDFidl_h__
#define __MoonPDFidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMoonPDF_FWD_DEFINED__
#define ___DMoonPDF_FWD_DEFINED__
typedef interface _DMoonPDF _DMoonPDF;

#endif 	/* ___DMoonPDF_FWD_DEFINED__ */


#ifndef ___DMoonPDFEvents_FWD_DEFINED__
#define ___DMoonPDFEvents_FWD_DEFINED__
typedef interface _DMoonPDFEvents _DMoonPDFEvents;

#endif 	/* ___DMoonPDFEvents_FWD_DEFINED__ */


#ifndef __MoonPDF_FWD_DEFINED__
#define __MoonPDF_FWD_DEFINED__

#ifdef __cplusplus
typedef class MoonPDF MoonPDF;
#else
typedef struct MoonPDF MoonPDF;
#endif /* __cplusplus */

#endif 	/* __MoonPDF_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MoonPDF_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_MoonPDF_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MoonPDF_0000_0000_v0_0_s_ifspec;


#ifndef __MoonPDFLib_LIBRARY_DEFINED__
#define __MoonPDFLib_LIBRARY_DEFINED__

/* library MoonPDFLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_MoonPDFLib;

#ifndef ___DMoonPDF_DISPINTERFACE_DEFINED__
#define ___DMoonPDF_DISPINTERFACE_DEFINED__

/* dispinterface _DMoonPDF */
/* [uuid] */ 


EXTERN_C const IID DIID__DMoonPDF;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("50FEEB59-40AA-4376-A625-B7E1CEADC4D8")
    _DMoonPDF : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMoonPDFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMoonPDF * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMoonPDF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMoonPDF * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMoonPDF * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMoonPDF * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMoonPDF * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMoonPDF * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMoonPDFVtbl;

    interface _DMoonPDF
    {
        CONST_VTBL struct _DMoonPDFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMoonPDF_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMoonPDF_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMoonPDF_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMoonPDF_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMoonPDF_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMoonPDF_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMoonPDF_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMoonPDF_DISPINTERFACE_DEFINED__ */


#ifndef ___DMoonPDFEvents_DISPINTERFACE_DEFINED__
#define ___DMoonPDFEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMoonPDFEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DMoonPDFEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("91A28D6A-936C-4DEF-812D-2F6E83108617")
    _DMoonPDFEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMoonPDFEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMoonPDFEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMoonPDFEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMoonPDFEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMoonPDFEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMoonPDFEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMoonPDFEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMoonPDFEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMoonPDFEventsVtbl;

    interface _DMoonPDFEvents
    {
        CONST_VTBL struct _DMoonPDFEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMoonPDFEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMoonPDFEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMoonPDFEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMoonPDFEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMoonPDFEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMoonPDFEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMoonPDFEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMoonPDFEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MoonPDF;

#ifdef __cplusplus

class DECLSPEC_UUID("8C99F46D-8421-478E-9787-5D424D215A2F")
MoonPDF;
#endif
#endif /* __MoonPDFLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


