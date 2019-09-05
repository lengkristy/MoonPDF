

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Sep 05 09:47:16 2019
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_MoonPDFLib,0x0CD40F6A,0x42E2,0x41DE,0x95,0xA4,0xF7,0x4D,0xC7,0xF2,0x71,0x2C);


MIDL_DEFINE_GUID(IID, DIID__DMoonPDF,0x50FEEB59,0x40AA,0x4376,0xA6,0x25,0xB7,0xE1,0xCE,0xAD,0xC4,0xD8);


MIDL_DEFINE_GUID(IID, DIID__DMoonPDFEvents,0x91A28D6A,0x936C,0x4DEF,0x81,0x2D,0x2F,0x6E,0x83,0x10,0x86,0x17);


MIDL_DEFINE_GUID(CLSID, CLSID_MoonPDF,0x8C99F46D,0x8421,0x478E,0x97,0x87,0x5D,0x42,0x4D,0x21,0x5A,0x2F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



