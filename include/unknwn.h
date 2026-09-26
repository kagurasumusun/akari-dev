/*
 * unknwn.h -- IUnknown and the interfaces every COM object derives from.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * The declaration macros give a C++ vtable form when compiled as C++ and a
 * function-pointer vtbl form when compiled as C, matching the layout the CE
 * binaries expect in both cases.
 */
#ifndef AKARI_WCE_UNKNWN_H
#define AKARI_WCE_UNKNWN_H

#include <wtypes.h>

#ifndef _UNKNWN_H
#define _UNKNWN_H

#ifdef __cplusplus
extern "C" {
#endif

/* COM calling convention.  Windows CE uses __cdecl for WINAPI on every CPU it
   supports, x86 included, and the COM entry points follow that -- unlike
   desktop Win32, where STDMETHODCALLTYPE is __stdcall on x86.  Declaring these
   __stdcall would produce decorated imports the CE DLLs do not export. */
#ifndef STDMETHODCALLTYPE
#define STDMETHODCALLTYPE __cdecl
#endif

#ifndef STDMETHOD_DEFINED
#define STDMETHOD_DEFINED

#ifdef __cplusplus

#define STDMETHOD(method)        virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type, method) virtual type STDMETHODCALLTYPE method
#define STDMETHODV(method)       virtual HRESULT STDMETHODCALLTYPE method
#define PURE                     = 0
#define THIS_
#define THIS                     void

#define DECLARE_INTERFACE(iface)              struct iface
#define DECLARE_INTERFACE_(iface, baseiface)  struct iface : public baseiface

#else /* C */

#define STDMETHOD(method)        HRESULT (STDMETHODCALLTYPE *method)
#define STDMETHOD_(type, method) type (STDMETHODCALLTYPE *method)
#define STDMETHODV(method)       HRESULT (STDMETHODCALLTYPE *method)
#define PURE
#define THIS_                    INTERFACE * This,
#define THIS                     INTERFACE * This

#ifndef interface
#define interface                struct
#endif

#define DECLARE_INTERFACE(iface) \
    typedef struct iface { struct iface##Vtbl *lpVtbl; } iface; \
    typedef struct iface##Vtbl iface##Vtbl; \
    struct iface##Vtbl

#define DECLARE_INTERFACE_(iface, baseiface) \
    DECLARE_INTERFACE(iface)

#endif /* __cplusplus */

#endif /* STDMETHOD_DEFINED */

/* ------------------------------------------------------------- IUnknown */

#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__

#undef  INTERFACE
#define INTERFACE IUnknown

DECLARE_INTERFACE(IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
};

typedef IUnknown *LPUNKNOWN;

#endif /* __IUnknown_INTERFACE_DEFINED__ */

/* -------------------------------------------------------- IClassFactory */

#ifndef __IClassFactory_INTERFACE_DEFINED__
#define __IClassFactory_INTERFACE_DEFINED__

#undef  INTERFACE
#define INTERFACE IClassFactory

DECLARE_INTERFACE_(IClassFactory, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(CreateInstance)(THIS_ IUnknown *pUnkOuter, REFIID riid,
                              void **ppvObject) PURE;
    STDMETHOD(LockServer)(THIS_ BOOL fLock) PURE;
};

typedef IClassFactory *LPCLASSFACTORY;

#endif /* __IClassFactory_INTERFACE_DEFINED__ */

/* ------------------------------------------------------------- IPersist */

#ifndef __IPersist_INTERFACE_DEFINED__
#define __IPersist_INTERFACE_DEFINED__

#undef  INTERFACE
#define INTERFACE IPersist

DECLARE_INTERFACE_(IPersist, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID *pClassID) PURE;
};

typedef IPersist *LPPERSIST;

#endif /* __IPersist_INTERFACE_DEFINED__ */

/* ------------------------------------------ forward-declared interfaces
 *
 * These are referenced by the objbase.h entry points.  They are declared as
 * incomplete types so that callers can pass and receive the pointers; their
 * full method tables live in objidl.h.
 */
struct akari_ISequentialStream;       typedef struct akari_ISequentialStream       ISequentialStream,       *LPSEQUENTIALSTREAM;
struct akari_IStream;                 typedef struct akari_IStream                 IStream,                 *LPSTREAM;
struct akari_IStorage;                typedef struct akari_IStorage                IStorage,                *LPSTORAGE;
struct akari_ILockBytes;              typedef struct akari_ILockBytes              ILockBytes,              *LPLOCKBYTES;
struct akari_IMalloc;                 typedef struct akari_IMalloc                 IMalloc,                 *LPMALLOC;
struct akari_IMallocSpy;              typedef struct akari_IMallocSpy              IMallocSpy,              *LPMALLOCSPY;
struct akari_IMarshal;                typedef struct akari_IMarshal                IMarshal,                *LPMARSHAL;
struct akari_IMessageFilter;          typedef struct akari_IMessageFilter          IMessageFilter,          *LPMESSAGEFILTER;
struct akari_ISurrogate;              typedef struct akari_ISurrogate              ISurrogate,              *LPSURROGATE;
struct akari_IChannelHook;            typedef struct akari_IChannelHook            IChannelHook,            *LPCHANNELHOOK;
struct akari_IRunningObjectTable;     typedef struct akari_IRunningObjectTable     IRunningObjectTable,     *LPRUNNINGOBJECTTABLE;
struct akari_IBindCtx;                typedef struct akari_IBindCtx                IBindCtx,                *LPBC;
struct akari_IMoniker;                typedef struct akari_IMoniker                IMoniker,                *LPMONIKER;
struct akari_IPersistStorage;         typedef struct akari_IPersistStorage         IPersistStorage,         *LPPERSISTSTORAGE;
struct akari_IPersistStream;          typedef struct akari_IPersistStream          IPersistStream,          *LPPERSISTSTREAM;
struct akari_IOleAdviseHolder;        typedef struct akari_IOleAdviseHolder        IOleAdviseHolder,        *LPOLEADVISEHOLDER;
struct akari_IOleObject;              typedef struct akari_IOleObject              IOleObject,              *LPOLEOBJECT;
struct akari_IOleClientSite;          typedef struct akari_IOleClientSite          IOleClientSite,          *LPOLECLIENTSITE;
struct akari_IOleInPlaceFrame;        typedef struct akari_IOleInPlaceFrame        IOleInPlaceFrame,        *LPOLEINPLACEFRAME;
struct akari_IOleInPlaceActiveObject; typedef struct akari_IOleInPlaceActiveObject IOleInPlaceActiveObject, *LPOLEINPLACEACTIVEOBJECT;

/* The stream enumeration record used by IEnumSTATSTG. */
typedef struct akari_STATSTG {
    LPOLESTR       pwcsName;
    DWORD          type;
    ULARGE_INTEGER cbSize;
    FILETIME       mtime;
    FILETIME       ctime;
    FILETIME       atime;
    DWORD          grfMode;
    DWORD          grfLocksSupported;
    CLSID          clsid;
    DWORD          grfStateBits;
    DWORD          reserved;
} STATSTG, *LPSTATSTG;

typedef struct akari_DVTARGETDEVICE {
    DWORD tdSize;
    WORD  tdDriverNameOffset;
    WORD  tdDeviceNameOffset;
    WORD  tdPortNameOffset;
    WORD  tdExtDevmodeOffset;
    BYTE  tdData[1];
} DVTARGETDEVICE, *LPDVTARGETDEVICE;

/* The COM menu descriptor used by OleSetMenuDescriptor. */
typedef struct akari_HOLEMENU {
    HMENU holemenuFrame;
    HMENU holemenuActive;
    HMENU holemenuObject;
} HOLEMENU, *LPHOLEMENU;

/* IsEqualGUID, IsEqualIID and IsEqualCLSID are provided by guiddef.h. */

#ifdef __cplusplus
}
#endif

#endif /* _UNKNWN_H */
#endif /* AKARI_WCE_UNKNWN_H */
