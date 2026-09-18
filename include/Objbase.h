/*
 * objbase.h -- COM / OLE / Storage / Automation umbrella header for
 * Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (CE-era MSDN / learn.microsoft.com previous-versions
 * archive; page ids msnnnnnn cited per declaration).  This unit covers
 * the 635 corpus pages whose "Requirements -> Header" line names one
 * of the COM-family headers:
 *
 *   Objbase.h                    87 pages   (Co* activation/marshaling)
 *   Objidl.h (+Objidl.idl)      131 pages   (OLE data structures)
 *   Oaidl.h (+Oaidl.idl)        141 pages   (OLE Automation types)
 *   Wtypes.h                       6 pages  (CLSCTX / COAUTH* / ...)
 *   Unknwn.h (+Unknwn.idl)         3 pages  (IUnknown)
 *   Oleauto.h                    227 pages  (Variant/SafeArray/BSTR)
 *   Ocidl.h (+Ocidl.idl)          40 pages  (OLE control interfaces)
 *
 * The link libraries named by those pages are ole32.dll (84 exported
 * functions) and oleaut32.dll (223; the import table carries 222 --
 * UnRegisterTypeLib's page prints "Link Library: None"); the import
 * tables are def/ole32-doc.def and def/oleaut32-doc.def.
 *
 * The CE SDK's <Objbase.h> includes Objidl.h, Oaidl.h, Wtypes.h and
 * Unknwn.h; this single umbrella covers those headers plus
 * Oleauto.h/Ocidl.h, and each declaration notes the header named by
 * its page.
 *
 * Transcription conventions (documented deviations from the printed
 * pages):
 *   - FAR / FARSTRUCT / __RPC_FAR / HUGEP: pointer qualifiers with no
 *     effect on CE's 32-bit flat address space; dropped.
 *   - "UNION_NAME(u)" in the printed TYPEDESC / VARDESC expands to the
 *     named union member "u".
 *   - MIDL attributes ([switch_type(...)], [case(...)], [unique])
 *     printed on the CE 5.0 STGMEDIUM page are stripped.
 *   - Archive print artifacts are fixed at the site and noted:
 *       * IDLDESC: missing closing brace;
 *       * ELEMDESC: alias printed as "ELEMDES";
 *       * VARDESC: missing terminating semicolon;
 *       * TYPEDESC: first union member printed twice with garbage
 *         prefixes ("ESC", "tagTYPEDSC");
 *       * VARTYPE page: the flag tail printed without separators;
 *       * LoadRegTypeLib / UnRegisterTypeLib: missing comma between
 *         wVerMajor and wVerMinor;
 *       * SafeArrayCreate: "SAFEARRRAYBOUND" (three R's);
 *       * VarI4FromUI1: page ms891659 duplicates ms891668 with a wrong
 *         DATE parameter -- ms891668's spelling is used;
 *       * page ms891846 is titled VarR8FromI4 but prints "ULONG ulIn"
 *         -- that is the VarR8FromUI4 signature, declared as such;
 *       * CURRENTY -> CURRENCY, DOUBLE -> char/double, Ulong -> ULONG,
 *         ItypeInfo -> ITypeInfo, IerrorInfo -> IErrorInfo,
 *         VarR8FromDips -> VarR8FromDisp;
 *       * SafeArrayGetDim / SafeArrayGetElemsize: the printed return
 *         type is HRESULT, but each page's own "Return Values" text
 *         says the function returns the dimension count / element
 *         size, so both are declared ULONG;
 *       * SystemTimeToVariantTime / DispInvoke: the parameter printed
 *         by value is documented by the page as a pointer -- declared
 *         as a pointer.
 *   - Interface vtable layouts are not published in the CE corpus:
 *     every COM interface is an opaque pointer type; the methods the
 *     corpus documents for each interface are listed in a comment.
 *   - Names referenced by the pages but whose definitions the corpus
 *     does not publish are declared opaque (or as documented scalar
 *     equivalents) with a note.
 *
 * 32-bit structure sizes are asserted in tests/.
 */

#ifndef AKARI_OBJBASE_H
#define AKARI_OBJBASE_H
/* Audit 2026-09-16: forward declarations for interface types whose
 * full vtable definitions live later in this file, but which also
 * appear (as pointer parameters only) in the OLE Automation block
 * that moved to Oleauto.h in this pass. Re-declaring the same
 * opaque forward here is valid in C11 (6.7p3 permits a typedef
 * name to be redefined to the exact same type) and lets Objbase.h
 * keep compiling standalone without depending on Oleauto.h. */
typedef struct ICatInformation ICatInformation;
typedef struct ICatRegister ICatRegister;
typedef struct IEnumOLEVERB IEnumOLEVERB;
typedef struct IObjectSafety IObjectSafety;
typedef struct IOleAdviseHolder IOleAdviseHolder;
typedef struct IOleClientSite IOleClientSite;
typedef struct IOleContainer IOleContainer;
typedef struct IOleControlSite IOleControlSite;
typedef struct IOleInPlaceSite IOleInPlaceSite;
typedef struct IOleObject IOleObject;
typedef struct IOleWindow IOleWindow;
typedef struct IParseDisplayName IParseDisplayName;
typedef struct IPersist IPersist;
typedef struct IPersistStorage IPersistStorage;
typedef struct IPersistStream IPersistStream;
typedef struct IPersistStreamInit IPersistStreamInit;
typedef struct IProgressNotify IProgressNotify;
typedef struct IProvideClassInfo IProvideClassInfo;
typedef struct IProvideClassInfo2 IProvideClassInfo2;
typedef struct IROTData IROTData;
typedef struct IRootStorage IRootStorage;
typedef struct IRunnableObject IRunnableObject;
typedef struct ISequentialStream ISequentialStream;
typedef struct IServerSecurity IServerSecurity;
typedef struct IStdMarshalInfo IStdMarshalInfo;
typedef struct IViewObject IViewObject;
typedef struct IViewObject2 IViewObject2;



#include "Windef.h"
#include "Winbase.h"  /* FILETIME, HGLOBAL, SYSTEMTIME, SECURITY_ATTRIBUTES */
#include "Wingdi.h"   /* LOGPALETTE/LPLOGPALETTE (IViewObject::GetColorSet --

                         a real vtable parameter since M97) */
#include "Winuser.h"  /* LPMSG, LPCRECT (IOleControlSite::TranslateAccelerator,
                         IOleObject::DoVerb -- real vtable parameters) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Calling-convention tokens printed by the CE pages.  All are empty  */
/* on CE's 32-bit flat model.                                         */
/* ------------------------------------------------------------------ */
#define STDAPI
#define WINOLEAPI
#define WINOLEAUTAPI
#define STDAPICALLTYPE

/* ------------------------------------------------------------------ */
/* Scalar types (Wtypes.h / Oaidl.h family)                           */
/* ------------------------------------------------------------------ */

/* OLECHAR: the BSTR page (ms886145) prints "typedef OLECHAR FAR* BSTR"
 * and describes BSTR as a pointer to a wide character string --
 * OLECHAR is the 16-bit OLE/COM character, i.e. WCHAR on CE. */
typedef WCHAR            OLECHAR;
typedef OLECHAR         *LPOLESTR;    /* CE doc spelling, used throughout */
typedef const OLECHAR   *LPCOLESTR;   /* CE doc spelling, used throughout */
typedef OLECHAR         *BSTR;        /* ms886145 */

/* HRESULT: the 32-bit COM result type (documented return of every
 * COM API).  The S_OK / S_FALSE / E_* constant names are referenced by
 * the pages; their numeric values are not published in the CE corpus,
 * so they are not defined here. */
#ifndef AKARI_HRESULT_DEFINED
#define AKARI_HRESULT_DEFINED
typedef LONG             HRESULT;
#endif

/* GUID (the 16-byte COM identifier) and LPGUID are declared in
 * winnt.h; the layout is fixed by the binary form the
 * StringFromGUID2 / CoCreateGuid / CLSIDFromString pages document
 * (DWORD, USHORT, USHORT, 8 BYTE). */

typedef GUID             CLSID;       /* class identifier (ms886232) */
typedef GUID             IID;         /* interface identifier (ms886232) */
typedef GUID            *LPIID;       /* ms891281 IIDFromString */
typedef GUID            *LPCLSID;     /* ms886181 CLSIDFromProgID */

/* REF*: "reference to" an identifier.  The CE C prototypes take the
 * identifier by reference, which in C is a pointer to a const object
 * (the documented call sites pass addresses of identifiers). */
#define REFGUID           const GUID *
#define REFCLSID          const CLSID *
#define REFIID            const IID *

/* LCID is declared in windef.h (DWORD); the page ms890741 prints
 * "typedef unsigned long LCID" -- consistent, not redeclared. */

typedef LONG             DISPID;      /* ms886967: "Typedef LONG DISPID" */
typedef DISPID           MEMBERID;    /* ms890763: "Typedef DISPID MEMBERID" */
typedef ULONG            HREFTYPE;    /* ms886994: "typedef unsigned long HREFTYPE" */

/* VARIANT_BOOL / DATE / SCODE: members of the VARIANT / EXCEPINFO
 * unions (ms891678 / ms886984); the corpus has no standalone pages --
 * the 16-bit Automation boolean, the double OLE date and the 32-bit
 * HRESULT error code the Automation pages document. */
typedef unsigned short   VARIANT_BOOL;
typedef double           DATE;
typedef LONG             SCODE;

/* CY / CURRENCY (ms886958).  The page's _MAC branch is not the CE
 * branch; CE uses the little-endian 32-bit layout. */
typedef union _tagCY {
    struct {
        unsigned long Lo;
        long          Hi;
    };
    LONGLONG int64;
} CY;
typedef CY               CURRENCY;    /* ms886958 */

/* VARTYPE / VARENUM (ms891853). */
typedef unsigned short   VARTYPE;
typedef enum VARENUM {
    VT_EMPTY = 0, VT_NULL = 1, VT_I2 = 2, VT_I4 = 3, VT_R4 = 4,
    VT_R8 = 5, VT_CY = 6, VT_DATE = 7, VT_BSTR = 8, VT_DISPATCH = 9,
    VT_ERROR = 10, VT_BOOL = 11, VT_VARIANT = 12, VT_UNKNOWN = 13,
    VT_UI1 = 17
} VARENUM;
/* The flag tail of the page prints without separators; transcribed: */
#define VT_ARRAY          0x2000/* aa519284 */
#define VT_BYREF          0x4000/* aa519284 */
#define VT_RESERVED       0x8000/* ee488486 */

/* Opaque types referenced by the documented prototypes but whose
 * definitions the CE corpus does not publish (declared so the
 * documented signatures compile). */
typedef struct _SNB SNB;                                /* storage name buffer (StgOpenStorage) */
typedef struct _PARAMDESCEX PARAMDESCEX;                /* extended parameter description (PARAMDESC) */
typedef PARAMDESCEX     *LPPARAMDESCEX;
typedef struct _SOLE_AUTHENTICATION_LIST SOLE_AUTHENTICATION_LIST; /* CoInitializeSecurity */
typedef void           *RPC_AUTHZ_HANDLE;               /* CoQueryClientBlanket */
typedef void           *RPC_AUTH_IDENTITY_HANDLE;       /* CoQueryProxyBlanket */
typedef struct _SECURITY_DESCRIPTOR SECURITY_DESCRIPTOR; /* CoInitializeSecurity */
typedef SECURITY_DESCRIPTOR *PSECURITY_DESCRIPTOR;
typedef struct _DECIMAL DECIMAL;                        /* Decimal (Var*FromDec) */
typedef struct _UDATE UDATE;                            /* UDATE (VarDateFromUdate) */
typedef struct _NUMPARSE NUMPARSE;                      /* VarParseNumFromStr */
typedef void           *HENHMETAFILE;                   /* enhanced metafile handle (STGMEDIUM) */
typedef void           *HMETAFILEPICT;                  /* metafile picture handle (STGMEDIUM) */

/* SIZEL: the CE spelling of the {LONG cx, LONG cy} size (SIZE) used
 * by the Ocidl.h pages (DVEXTENTINFO). */
/* SIZEL/POINTL moved to Windef.h (the GDI/DDI books share them) */

/* ------------------------------------------------------------------ */
/* Enumeration types (Oaidl.h / Objidl.h / Wtypes.h / Ocidl.h)        */
/* ------------------------------------------------------------------ */

/* CLSCTX (ms863882; Wtypes.h). */
typedef enum tagCLSCTX {
    CLSCTX_INPROC_SERVER  = 0x1,
    CLSCTX_INPROC_HANDLER = 0x2,
    CLSCTX_LOCAL_SERVER   = 0x4,
    CLSCTX_REMOTE_SERVER  = 0x10
} CLSCTX;
#define CLSCTX_SERVER (CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)
#define CLSCTX_ALL    (CLSCTX_INPROC_HANDLER | CLSCTX_SERVER)

/* DVASPECT (ms864437; Wtypes.h). */
typedef enum tagDVASPECT {
    DVASPECT_CONTENT   = 1,
    DVASPECT_THUMBNAIL = 2,
    DVASPECT_ICON      = 4,
    DVASPECT_DOCPRINT  = 8
} DVASPECT;

/* TYMED (ms896492): enumerator order, tag spelling ("tagTYMED") and
 * values exactly as printed on the page. */
typedef enum tagTYMED {
    TYMED_HGLOBAL  = 1,
    TYMED_FILE     = 2,
    TYMED_ISTREAM  = 4,
    TYMED_ISTORAGE = 8,
    TYMED_NULL     = 0
} TYMED;

/* STGC (ms896217; Wtypes.h). */
typedef enum tagSTGC {
    STGC_DEFAULT                 = 0,
    STGC_OVERWRITE               = 1,
    STGC_ONLYIFCURRENT           = 2,
    STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4
} STGC;

/* STGM (ms891273). */
enum {
    STGM_DIRECT         = 0x00000000L,
    STGM_READ           = 0x00000000L,
    STGM_FAILIFTHERE    = 0x00000000L,
    STGM_WRITE          = 0x00000001L,
    STGM_READWRITE      = 0x00000002L,
    STGM_SHARE_EXCLUSIVE= 0x00000010L,
    STGM_SHARE_DENY_WRITE = 0x00000020L,
    STGM_SHARE_DENY_READ  = 0x00000030L,
    STGM_SHARE_DENY_NONE  = 0x00000040L,
    STGM_CREATE         = 0x00001000L,
    STGM_PRIORITY       = 0x00040000L,
    STGM_CONVERT        = 0x00020000L,
    STGM_TRANSACTED     = 0x00010000L,
    STGM_SIMPLE         = 0x08000000L,
    STGM_DELETEONRELEASE= 0x04000000L,
    STGM_NOSCRATCH      = 0x00100000L,
    STGM_NOSNAPSHOT     = 0x00200000L,
    STGM_DIRECT_SWMR    = 0x00400000L
};

/* MKSYS (ms892349). */
typedef enum tagMKSYS {
    MKSYS_NONE             = 0,
    MKSYS_GENERICCOMPOSITE = 1,
    MKSYS_FILEMONIKER      = 2,
    MKSYS_ANTIMONIKER      = 3,
    MKSYS_ITEMMONIKER      = 4,
    MKSYS_POINTERMONIKER   = 5,
    MKSYS_CLASSMONIKER     = 7,
    MKSYS_OBJREFMONIKER    = 8,
    MKSYS_SESSIONMONIKER   = 9
} MKSYS;

/* MKRREDUCE (ms892348). */
typedef enum tagMKRREDUCE {
    MKRREDUCE_ONE          = 3 << 16,
    MKRREDUCE_TOUSER       = 2 << 16,
    MKRREDUCE_THROUGHUSER  = 1 << 16,
    MKRREDUCE_ALL          = 0
} MKRREDUCE;

/* BIND_FLAGS (ms863834). */
typedef enum tagBIND_FLAGS {
    BIND_MAYBOTHERUSER     = 1,
    BIND_JUSTTESTEXISTENCE = 2
} BIND_FLAGS;

/* SYSKIND (ms896474). */
typedef enum tagSYSKIND {
    SYS_WIN16 = 0,
    SYS_WIN32 = SYS_WIN16 + 1,
    SYS_MAC   = SYS_WIN32 + 1
} SYSKIND;

/* TYPEKIND (ms896496). */
typedef enum tagTYPEKIND {
    TKIND_ENUM = 0,
    TKIND_RECORD,
    TKIND_MODULE,
    TKIND_INTERFACE,
    TKIND_DISPATCH,
    TKIND_COCLASS,
    TKIND_ALIAS,
    TKIND_UNION,
    TKIND_MAX
} TYPEKIND;

/* VARKIND (aa519097). */
typedef enum tagVARKIND {
    VAR_PERINSTANCE = 0,
    VAR_STATIC      = VAR_PERINSTANCE + 1,
    VAR_CONST       = VAR_STATIC + 1,
    VAR_DISPATCH    = VAR_CONST + 1
} VARKIND;

/* CALLCONV (ms863871). */
typedef enum tagCALLCONV {
    CC_CDECL      = 1,
    CC_MSCPASCAL  = 2,
    CC_PASCAL     = CC_MSCPASCAL,
    CC_MACPASCAL  = 3,
    CC_STDCALL    = 4,
    CC_RESERVED   = 5,
    CC_SYSCALL    = 6,
    CC_MPWCDECL   = 7,
    CC_MPWPASCAL  = 8,
    CC_MAX        = 9
} CALLCONV;

/* FUNCKIND (aa515010). */
typedef enum tagFUNCKIND {
    FUNC_VIRTUAL     = 0,
    FUNC_PUREVIRTUAL,
    FUNC_NONVIRTUAL,
    FUNC_STATIC,
    FUNC_DISPATCH
} FUNCKIND;

/* INVOKEKIND (ms882878).  The page prints the members as aliases of
 * the DISPATCH_* constants; the CE corpus does not publish the
 * DISPATCH_* values, so the documented ordinal order is transcribed. */
typedef enum tagINVOKEKIND {
    INVOKE_FUNC          = 0,   /* page: DISPATCH_METHOD */
    INVOKE_PROPERTYGET,         /* page: DISPATCH_PROPERTYGET */
    INVOKE_PROPERTYPUT,         /* page: DISPATCH_PROPERTYPUT */
    INVOKE_PROPERTYPUTREF       /* page: DISPATCH_PROPERTYPUTREF */
} INVOKEKIND;

/* FUNCFLAGS (aa515008). */
typedef enum tagFUNCFLAGS {
    FUNCFLAG_FRESTRICTED       = 0x1,
    FUNCFLAG_FSOURCE           = 0x2,
    FUNCFLAG_FBINDABLE         = 0x4,
    FUNCFLAG_FREQUESTEDIT      = 0x8,
    FUNCFLAG_FDISPLAYBIND      = 0x10,
    FUNCFLAG_FDEFAULTBIND      = 0x20,
    FUNCFLAG_FHIDDEN           = 0x40,
    FUNCFLAG_FUSESGETLASTERROR = 0x80,
    FUNCFLAG_FDEFAULTCOLLELEM  = 0x100,
    FUNCFLAG_FUIDEFAULT        = 0x200,
    FUNCFLAG_FNONBROWSABLE     = 0x400,
    FUNCFLAG_FREPLACEABLE      = 0x800,
    FUNCFLAG_FIMMEDIATEBIND    = 0x1000
} FUNCFLAGS;

/* ADVF (aa513925). */
typedef enum tagADVF {
    ADVF_NODATA          = 1,
    ADVF_PRIMEFIRST      = 2,
    ADVF_ONLYONCE        = 4,
    ADVFCACHE_NOHANDLER  = 8,
    ADVFCACHE_FORCEBUILTIN = 16,
    ADVFCACHE_ONSAVE     = 32,
    ADVF_DATAONSTOP      = 64
} ADVF;

/* TYPEFLAGS (ms896495). */
typedef enum tagTYPEFLAGS {
    TYPEFLAG_FAPPOBJECT     = 0x0001,
    TYPEFLAG_FCANCREATE     = 0x0002,
    TYPEFLAG_FLICENSED      = 0x0004,
    TYPEFLAG_FPREDECLID     = 0x0008,
    TYPEFLAG_FHIDDEN        = 0x0010,
    TYPEFLAG_FCONTROL       = 0x0020,
    TYPEFLAG_FDUAL          = 0x0040,
    TYPEFLAG_FNONEXTENSIBLE = 0x0080,
    TYPEFLAG_FOLEAUTOMATION = 0x0100,
    TYPEFLAG_FRESTRICTED    = 0x0200,
    TYPEFLAG_FAGGREGATABLE  = 0x0400,
    TYPEFLAG_FREPLACEABLE   = 0x0800,
    TYPEFLAG_FDISPATCHABLE  = 0x1000,
    TYPEFLAG_FREVERSEBIND   = 0x2000
} TYPEFLAGS;

/* DATADIR (ms864408). */
typedef enum tagDATADIR {
    DATADIR_GET = 1,
    DATADIR_SET = 2
} DATADIR;

/* DESCKIND (ms864416). */
typedef enum tagDESCKIND {
    DESCKIND_NONE         = 0,
    DESCKIND_FUNCDESC,
    DESCKIND_VARDESC,
    DESCKIND_TYPECOMP,
    DESCKIND_IMPLICITAPPOBJ
} DESCKIND;

/* DVASPECT2 (ms864438; Ocidl.h). */
typedef enum tagDVASPECT2 {
    DVASPECT_OPAQUE     = 16,
    DVASPECT_TRANSPARENT= 32
} DVASPECT2;

/* DVASPECTINFOFLAG (ms864450; Ocidl.h). */
typedef enum tagDVASPECTINFOFLAG {
    DVASPECTINFOFLAG_CANOPTIMIZE = 1
} DVASPECTINFOFLAG;

/* DVEXTENTMODE (ms864452; Ocidl.h). */
typedef enum tagDVEXTENTMODE {
    DVEXTENT_CONTENT   = 0,
    DVEXTENT_INTEGRAL  = DVEXTENT_CONTENT + 1
} DVEXTENTMODE;

/* HITRESULT (aa515087; Ocidl.h). */
typedef enum tagHITRESULT {
    HITRESULT_OUTSIDE     = 0,
    HITRESULT_TRANSPARENT = 1,
    HITRESULT_CLOSE       = 2,
    HITRESULT_HIT         = 3
} HITRESULT;

/* VIEWSTATUS (ms897186; Ocidl.h). */
typedef enum tagVIEWSTATUS {
    VIEWSTATUS_OPAQUE              = 1,
    VIEWSTATUS_SOLIDBKGND          = 2,
    VIEWSTATUS_DVASPECTOPAQUE      = 4,
    VIEWSTATUS_DVASPECTTRANSPARENT = 8
} VIEWSTATUS;

/* ------------------------------------------------------------------ */
/* COM interfaces (opaque).  The CE corpus publishes the documented   */
/* methods per interface but not vtable layouts, so each interface is */
/* an opaque pointer type; the documented methods are listed per      */
/* interface.  The LPX pointer aliases are the CE doc spellings.      */
/* ------------------------------------------------------------------ */
typedef struct IAdviseSink IAdviseSink;
typedef IAdviseSink *LPIAdviseSink;
typedef struct IBindCtx IBindCtx;
typedef IBindCtx *LPIBindCtx;
typedef IBindCtx *LPBC;   /* documented short spelling */
typedef struct IClassActivator IClassActivator;
typedef IClassActivator *LPIClassActivator;
typedef struct IClassFactory IClassFactory;
typedef IClassFactory *LPIClassFactory;
typedef struct IClassFactory2 IClassFactory2;
typedef IClassFactory2 *LPIClassFactory2;
typedef struct IClientSecurity IClientSecurity;
typedef IClientSecurity *LPIClientSecurity;
typedef struct IConnectionPoint IConnectionPoint;
typedef IConnectionPoint *LPIConnectionPoint;
typedef struct IConnectionPointContainer IConnectionPointContainer;
typedef IConnectionPointContainer *LPIConnectionPointContainer;
typedef struct ICreateErrorInfo ICreateErrorInfo;
typedef ICreateErrorInfo *LPICreateErrorInfo;
typedef struct ICreateTypeInfo ICreateTypeInfo;
typedef ICreateTypeInfo *LPICreateTypeInfo;
typedef struct ICreateTypeInfo2 ICreateTypeInfo2;
typedef ICreateTypeInfo2 *LPICreateTypeInfo2;
typedef struct ICreateTypeLib ICreateTypeLib;
typedef ICreateTypeLib *LPICreateTypeLib;
typedef struct ICreateTypeLib2 ICreateTypeLib2;
typedef ICreateTypeLib2 *LPICreateTypeLib2;
typedef struct IDataObject IDataObject;
typedef IDataObject *LPIDataObject;
typedef struct IDispatch IDispatch;
typedef IDispatch *LPIDispatch;
typedef struct IEnumConnectionPoints IEnumConnectionPoints;
typedef IEnumConnectionPoints *LPIEnumConnectionPoints;
typedef struct IEnumConnections IEnumConnections;
typedef IEnumConnections *LPIEnumConnections;
typedef struct IEnumFORMATETC IEnumFORMATETC;
typedef IEnumFORMATETC *LPIEnumFORMATETC;
typedef struct IEnumMoniker IEnumMoniker;
typedef IEnumMoniker *LPIEnumMoniker;
typedef struct IEnumSTATDATA IEnumSTATDATA;
typedef IEnumSTATDATA *LPIEnumSTATDATA;
typedef struct IEnumSTATSTG IEnumSTATSTG;
typedef IEnumSTATSTG *LPIEnumSTATSTG;
typedef struct IEnumString IEnumString;
typedef IEnumString *LPIEnumString;
typedef struct IEnumVARIANT IEnumVARIANT;
typedef IEnumVARIANT *LPIEnumVARIANT;
typedef struct IErrorInfo IErrorInfo;
typedef IErrorInfo *LPIErrorInfo;
typedef struct IErrorlog IErrorlog;
typedef IErrorlog *LPIErrorlog;
typedef struct IExternalConnection IExternalConnection;
typedef IExternalConnection *LPIExternalConnection;
typedef struct IFillLockBytes IFillLockBytes;
typedef IFillLockBytes *LPIFillLockBytes;
typedef struct IGlobalInterfaceTable IGlobalInterfaceTable;
typedef IGlobalInterfaceTable *LPIGlobalInterfaceTable;
typedef struct ILockBytes ILockBytes;
typedef ILockBytes *LPILockBytes;
typedef struct IMalloc IMalloc;
typedef IMalloc *LPIMalloc;
typedef IMalloc *LPMALLOC;   /* documented short spelling */
typedef struct IMallocSpy IMallocSpy;
typedef IMallocSpy *LPIMallocSpy;
typedef IMallocSpy *LPMALLOCSPY;   /* documented short spelling */
typedef struct IMarshal IMarshal;
typedef IMarshal *LPIMarshal;
typedef IMarshal *LPMARSHAL;   /* documented short spelling */
typedef struct IMessageFilter IMessageFilter;
typedef IMessageFilter *LPIMessageFilter;
typedef IMessageFilter *LPMESSAGEFILTER;   /* documented short spelling */
typedef struct IMoniker IMoniker;
typedef IMoniker *LPIMoniker;
typedef IMoniker *LPMONIKER;   /* documented short spelling */
typedef struct IMultiQI IMultiQI;
typedef IMultiQI *LPIMultiQI;
typedef struct IOleItemContainer IOleItemContainer;
typedef IOleItemContainer *LPIOleItemContainer;
typedef struct IPersistFile IPersistFile;
typedef IPersistFile *LPIPersistFile;
typedef struct IPersistPropertyBag IPersistPropertyBag;
typedef IPersistPropertyBag *LPIPersistPropertyBag;
typedef struct IPropertyBag IPropertyBag;
typedef IPropertyBag *LPIPropertyBag;
typedef struct IRunningObjectTable IRunningObjectTable;
typedef IRunningObjectTable *LPIRunningObjectTable;
typedef IRunningObjectTable *LPRUNNINGOBJECTTABLE;   /* documented short spelling */
typedef struct IStorage IStorage;
typedef IStorage *LPIStorage;
typedef struct IStream IStream;
typedef IStream *LPIStream;
typedef IStream *LPSTREAM;   /* documented short spelling */
typedef struct ISurrogate ISurrogate;
typedef ISurrogate *LPISurrogate;
typedef struct ITypeComp ITypeComp;
typedef ITypeComp *LPITypeComp;
typedef struct ITypeInfo ITypeInfo;
typedef ITypeInfo *LPITypeInfo;
typedef struct ITypeInfo2 ITypeInfo2;
typedef ITypeInfo2 *LPITypeInfo2;
typedef struct ITypeLib ITypeLib;
typedef ITypeLib *LPITypeLib;
typedef struct ITypeLib2 ITypeLib2;
typedef ITypeLib2 *LPITypeLib2;
typedef struct IUnknown IUnknown;
typedef IUnknown *LPIUnknown;
typedef IUnknown *LPUNKNOWN;   /* documented short spelling */
typedef struct IViewObjectEx IViewObjectEx;
typedef IViewObjectEx *LPIViewObjectEx;

/* IAdviseSink: documented methods (5 pages).
 *   ms887005 OnClose: void OnClose()
 *   ms887006 OnDataChange: void OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed)
 *   ms887007 OnRename: void OnRename(IMoniker* pmk)
 *   ms887008 OnSave: void OnSave()
 *   ms887009 OnViewChange: void OnViewChange(DWORD dwAspect, LONG lindex)
 */

/* IBindCtx: documented methods (10 pages).
 *   ms887010 EnumObjectParam: HRESULT EnumObjectParam(IEnumString** ppenum)
 *   ms887011 GetBindOptions: HRESULT GetBindOptions(BIND_OPTS* pbindopts)
 *   ms887012 GetObjectParam: HRESULT GetObjectParam(LPOLESTR pszKey, IUnknown** ppunk)
 *   ms887013 GetRunningObjectTable: HRESULT GetRunningObjectTable(IRunningObjectTable** pprot)
 *   ms887015 RegisterObjectBound: HRESULT RegisterObjectBound(IUnknown* punk)
 *   ms887016 RegisterObjectParam: HRESULT RegisterObjectParam(LPOLESTR pszKey, IUnknown* punk)
 *   ms887017 ReleaseBoundObjects: HRESULT ReleaseBoundObjects(void)
 *   ms887018 RevokeObjectBound: HRESULT RevokeObjectBound(IUnknown* punk)
 *   ms887019 RevokeObjectParam: HRESULT RevokeObjectParam(LPOLESTR pszKey)
 *   ms887020 SetBindOptions: HRESULT SetBindOptions(BIND_OPTS* pbindopts)
 */

/* IClassActivator: documented methods (1 pages).
 *   ms887268 GetClassObject: HRESULT GetClassObject(REFCLSID* pClassID, DWORD dwClsContext, LCID locale, REFIID riid, void** ppv)
 */

/* IClassFactory: documented methods (2 pages).
 *   ms887274 CreateInstance: HRESULT CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject)
 *   ms887276 LockServer: HRESULT LockServer(BOOL fLock)
 */

/* IClassFactory2: documented methods (3 pages).
 *   ms887270 CreateInstanceLic: HRESULT CreateInstanceLic(IUnknown* pUnkOuter, IUnknown* pUnkReserved, REFIID riid, BSTR bstrKey, void**...
 *   ms887271 GetLicInfo: HRESULT GetLicInfo(LICINFO* pLicInfo)
 *   ms887273 RequestLicKey: HRESULT RequestLicKey(DWORD dwReserved, BSTR* pbstrKey)
 */

/* IClientSecurity: documented methods (3 pages).
 *   ms887277 CopyProxy: HRESULT CopyProxy(IUnknown* pProxy, IUnknown** ppCopy)
 *   ms887279 QueryBlanket: HRESULT QueryBlanket(IUnknown* pProxy, DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DW...
 *   ms887280 SetBlanket: HRESULT SetBlanket(IUnknown* pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, OLECHAR* pServerPrincName, DWORD...
 */

/* IConnectionPoint: documented methods (5 pages).
 *   ms887281 Advise: HRESULT Advise(IUnknown* pUnk, DWORD* pdwCookie)
 *   ms887286 EnumConnections: HRESULT EnumConnections(IEnumConnections** ppEnum)
 *   ms887287 GetConnectionInterface: HRESULT GetConnectionInterface(IID* pIID)
 *   ms887288 GetConnectionPointContainer: HRESULT GetConnectionPointContainer(IConnectionPointContainer** ppCPC)
 *   ms887290 Unadvise: HRESULT Unadvise(DWORD dwCookie)
 */

/* IConnectionPointContainer: documented methods (2 pages).
 *   ms887283 EnumConnectionPoints: HRESULT EnumConnectionPoints(IEnumConnectionPoints** ppEnum)
 *   ms887284 FindConnectionPoint: HRESULT FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP)
 */

/* ICreateErrorInfo: documented methods (5 pages).
 *   ms887295 SetDescription: HRESULT SetDescription(LPCOLESTR* szDescription)
 *   ms887296 SetGUID: HRESULT SetGUID(REFGUID rguid)
 *   ms887297 SetHelpContext: HRESULT SetHelpContext(DWORD dwHelpContext)
 *   ms887298 SetHelpFile: HRESULT SetHelpFile(LPCOLESTR szHelpFile)
 *   ms887299 SetSource: HRESULT SetSource(LPCOLESTR szSource)
 */

/* ICreateTypeInfo: documented methods (21 pages).
 *   ms887315 AddFuncDesc: HRESULT AddFuncDesc(unsigned int index, FUNCDESC * pFuncDesc)
 *   ms887316 AddImplType: HRESULT AddImplType(unsigned int index, HREFTYPE hRefType)
 *   ms887317 AddRefTypeInfo: HRESULT AddRefTypeInfo(ITypeInfo * pTInfo, HREFTYPE * phRefType)
 *   ms887318 AddVarDesc: HRESULT AddVarDesc(unsigned int index, VARDESC * pVarDesc)
 *   ms887319 DefineFuncAsDllEntry: HRESULT DefineFuncAsDllEntry(unsigned int index, OLECHAR * szDllName, OLECHAR * szProcName)
 *   ms887321 LayOut: HRESULT LayOut()
 *   ms887322 SetAlignment: HRESULT SetAlignment(unsigned short cbAlignment)
 *   ms887323 SetDocString: HRESULT SetDocString(OLECHAR * pStrDoc)
 *   ms887324 SetFuncAndParamNames: HRESULT SetFuncAndParamNames(unsigned int index, OLECHAR ** rgszNames, unsigned int cNames)
 *   ms887325 SetFuncDocString: HRESULT SetFuncDocString(unsigned int index, OLECHAR * szDocString)
 *   ms887326 SetFuncHelpContext: HRESULT SetFuncHelpContext(unsigned int index, unsigned long dwHelpContext)
 *   ms887327 SetGuid: HRESULT SetGuid(REFGUID guid)
 *   ms887328 SetHelpContext: HRESULT SetHelpContext(unsigned long dwHelpContext)
 *   ms887329 SetImplTypeFlags: HRESULT SetImplTypeFlags(unsigned int index, int implTypeFlags)
 *   ms887330 SetMops: HRESULT SetMops(unsigned int index, BSTR bstrMops)
 *   ms887331 SetTypeDescAlias: HRESULT SetTypeDescAlias(TYPEDESC * pTDescAlias)
 *   ms887332 SetTypeFlags: HRESULT SetTypeFlags(unsigned int uTypeFlags)
 *   ms887334 SetVarDocString: HRESULT SetVarDocString(unsigned int index, OLECHAR * szDocString)
 *   ms887335 SetVarHelpContext: HRESULT SetVarHelpContext(unsigned int index, unsigned long dwHelpContext)
 *   ms887336 SetVarName: HRESULT SetVarName(unsigned int index, OLECHAR * szName)
 *   ms887337 SetVersion: HRESULT SetVersion(unsigned short wMajorVerNum, unsigned short wMinorVerNum)
 */

/* ICreateTypeInfo2: documented methods (14 pages).
 *   ms887300 DeleteFuncDesc: HRESULT DeleteFuncDesc(unsigned int index)
 *   ms887301 DeleteFuncDescByMemId: HRESULT DeleteFuncDescByMemId(MEMBERID memid, INVOKEKIND invKind)
 *   ms887302 DeleteImplType: HRESULT DeleteImplType(unsigned int index)
 *   ms887303 DeleteVarDesc: HRESULT DeleteVarDesc(unsigned int index)
 *   ms887304 DeleteVarDescByMemId: HRESULT DeleteVarDescByMemId(MEMBERID memid)
 *   ms887306 SetCustData: HRESULT SetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms887307 SetFuncCustData: HRESULT SetFuncCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887308 SetFuncHelpStringContext: HRESULT SetFuncHelpStringContext(unsigned int index, DWORD dwHelpStringContext)
 *   ms887309 SetHelpStringContext: HRESULT SetHelpStringContext(DWORD* dwHelpStringContext)
 *   ms887310 SetImplTypeCustData: HRESULT SetImplTypeCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887311 SetName: HRESULT SetName(OLECHAR * szName)
 *   ms887312 SetParamCustData: HRESULT SetParamCustData(unsigned int indexFunc, unsigned int indexParam, REFGUID guid, VARIANT* pVarVal)
 *   ms887313 SetVarCustData: HRESULT SetVarCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887314 SetVarHelpStringContext: HRESULT SetVarHelpStringContext(unsigned int index, DWORD dwHelpStringContext)
 */

/* ICreateTypeLib: documented methods (8 pages).
 *   ms887343 CreateTypeInfo: HRESULT CreateTypeInfo(OLECHAR * szName, TYPEKIND tkind, ICreateTypeInfo ** ppCTInfo)
 *   ms887345 SetGuid: HRESULT SetGuid(REFGUID guid)
 *   ms887346 SetHelpContext: HRESULT SetHelpContext(unsigned long dwHelpContext)
 *   ms887347 SetHelpFileName: HRESULT SetHelpFileName(OLECHAR * szHelpFileName)
 *   ms887348 SetLcid: HRESULT SetLcid(LCID lcid)
 *   ms887349 SetLibFlags: HRESULT SetLibFlags(unsigned int uLibFlags)
 *   ms887350 SetName: HRESULT SetName(OLECHAR * szName)
 *   ms887351 SetVersion: HRESULT SetVersion(unsigned short wMajorVerNum, unsigned short wMinorVerNum)
 */

/* ICreateTypeLib2: documented methods (4 pages).
 *   ms887338 DeleteTypeInfo: HRESULT DeleteTypeInfo(OLECHAR * szName)
 *   ms887340 SetCustData: HRESULT SetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms887341 SetHelpStringContext: HRESULT SetHelpStringContext(DWORD* dwHelpStringContext)
 *   ms887342 SetHelpStringDll: HRESULT SetHelpStringDll(LPOLESTR szFileName)
 */

/* IDataObject: documented methods (9 pages).
 *   ms887353 DAdvise: HRESULT DAdvise(FORMATETC* pFormatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection)
 *   ms887354 DUnadvise: HRESULT DUnadvise(DWORD dwConnection)
 *   ms887355 EnumDAdvise: HRESULT EnumDAdvise(IEnumSTATDATA** ppenumAdvise)
 *   ms887356 EnumFormatEtc: HRESULT EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatetc)
 *   ms887357 GetCanonicalFormatEtc: HRESULT GetCanonicalFormatEtc(FORMATETC* pFormatetcIn, FORMATETC* pFormatetcOut)
 *   ms887358 GetData: HRESULT GetData(FORMATETC* pFormatetc, STGMEDIUM* pmedium)
 *   ms887359 GetDataHere: HRESULT GetDataHere(FORMATETC* pFormatetc, STGMEDIUM* pmedium)
 *   ms887360 QueryGetData: HRESULT QueryGetData(FORMATETC* pFormatetc)
 *   ms887361 SetData: HRESULT SetData(FORMATETC* pFormatetc, STGMEDIUM* pmedium, BOOL fRelease)
 */

/* IDispatch: documented methods (4 pages).
 *   ms887721 GetIDsOfNames: HRESULT GetIDsOfNames(REFIID riid, OLECHAR ** rgszNames, unsigned int cNames, LCID lcid, DISPID * rgDispId)
 *   ms887722 GetTypeInfo: HRESULT GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo ** ppTInfo)
 *   ms887723 GetTypeInfoCount: HRESULT GetTypeInfoCount(unsigned int * pctinfo)
 *   ms887724 Invoke: HRESULT Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS * pDispParams, VARIAN...
 */

/* IEnumConnectionPoints: documented methods (4 pages).
 *   ms887727 Clone: HRESULT Clone(IEnumConnectionPoints** ppEnum)
 *   ms887729 Next: HRESULT Next(ULONG cConnections, IConnectionPoint** rgpcn, ULONG* pcFetched)
 *   ms887730 Reset: HRESULT Reset(void)
 *   ms887731 Skip: HRESULT Skip(ULONG cConnections)
 */

/* IEnumConnections: documented methods (4 pages).
 *   ms887732 Clone: HRESULT Clone(IEnumConnectionPoints** ppEnum)
 *   ms887734 Next: HRESULT Next(ULONG cConnections, CONNECTDATA** rgpcd, ULONG* pcFetched)
 *   ms887735 Reset: HRESULT Reset(void)
 *   ms887736 Skip: HRESULT Skip(ULONG cConnections)
 */

/* IEnumFORMATETC: documented methods (4 pages).
 *   ms887738 Clone: HRESULT Clone(IEnumFORMATETC** ppenum)
 *   ms887739 Next: HRESULT Next(ULONG celt, FORMATETC* rgelt, ULONG* pceltFetched)
 *   ms887740 Reset: HRESULT Reset(void)
 *   ms887741 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumMoniker: documented methods (4 pages).
 *   ms887742 Clone: HRESULT Clone(IEnumMoniker** ppenum)
 *   ms887744 Next: HRESULT Next(ULONG celt, IMoniker* rgelt, ULONG* pceltFetched)
 *   ms887745 Reset: HRESULT Reset(void)
 *   ms887746 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumSTATDATA: documented methods (4 pages).
 *   ms887747 Clone: HRESULT Clone(Ienum<ELT_T>** ppenum)
 *   ms887749 Next: HRESULT Next(ULONG celt, ELT_T[ ] rgelt, ULONG* pceltFetched)
 *   ms887750 Reset: HRESULT Reset(void)
 *   ms887751 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumSTATSTG: documented methods (4 pages).
 *   ms887752 Clone: HRESULT Clone(Ienum<ELT_T>** ppenum)
 *   ms887754 Next: HRESULT Next(ULONG celt, ELT_T[ ] rgelt, ULONG* pceltFetched)
 *   ms887755 Reset: HRESULT Reset(void)
 *   ms887756 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumString: documented methods (4 pages).
 *   ms887758 Clone: HRESULT Clone(IEnumString** ppenum)
 *   ms887759 Next: HRESULT Next(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched)
 *   ms887760 Reset: HRESULT Reset(void)
 *   ms887761 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumVARIANT: documented methods (4 pages).
 *   ms887763 Clone: HRESULT Clone(IEnumVARIANT ** ppEnum)
 *   ms887765 Next: HRESULT Next(unsigned long celt, VARIANT * rgVar, unsigned long * pCeltFetched)
 *   ms887766 Reset: HRESULT Reset()
 *   ms887767 Skip: HRESULT Skip(unsigned long celt)
 */

/* IErrorInfo: documented methods (5 pages).
 *   ms887768 GetDescription: HRESULT GetDescription(BSTR* pBstrDescription)
 *   ms887769 GetGUID: HRESULT GetGUID(GUID* pGUID)
 *   ms887780 GetHelpContext: HRESULT GetHelpContext(DWORD* pdwHelpContext)
 *   ms887781 GetHelpFile: HRESULT GetHelpFile(BSTR* pBstrHelpFile)
 *   ms887782 GetSource: HRESULT GetSource(BSTR* pBstrSource)
 */

/* IErrorlog: documented methods (1 pages).
 *   ms886009 AddError: HRESULT AddError(LPCOLESTR pszPropName, EXCEPINFO* pExcepInfo)
 */

/* IExternalConnection: documented methods (2 pages).
 *   ms887785 AddConnection: HRESULT AddConnection(DWORD exconn, DWORD dwreserved)
 *   ms887786 ReleaseConnection: HRESULT ReleaseConnection(DWORD extconn, DWORD dwreserved, BOOL fLastReleaseCloses)
 */

/* IFillLockBytes: documented methods (4 pages).
 *   ms887788 FillAppend: HRESULT FillAppend(void const* pv, ULONG cb, ULONG* pcbWritten)
 *   ms887789 FillAt: HRESULT FillAt(ULARGE_INTEGER uIOffset, void const* pv, ULONG cb, ULONG* pcbWritten)
 *   ms887791 SetFillSize: HRESULT SetFillSize(ULARGE_INTEGER uISize)
 *   ms887792 Terminate: HRESULT Terminate(BOOL bCanceled)
 */

/* IGlobalInterfaceTable: documented methods (3 pages).
 *   ms887794 GetInterfaceFromGlobal: HRESULT GetInterfaceFromGlobal(DWORD dwCookie, REFIID riid, void** ppv)
 *   ms887795 RegisterInterfaceInGlobal: HRESULT RegisterInterfaceInGlobal(IUnknown* pUnk, REFIID riid, DWORD* pdwCookie)
 *   ms887796 RevokeInterfaceFromGlobal: HRESULT RevokeInterfaceFromGlobal(DWORD dwCookie)
 */

/* ILockBytes: documented methods (7 pages).
 *   ms887798 Flush: HRESULT Flush(void)
 *   ms887800 LockRegion: HRESULT LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
 *   ms887801 ReadAt: HRESULT ReadAt(ULARGE_INTEGER ulOffset, void* pv, ULONG cb, ULONG* pcbRead)
 *   ms887802 SetSize: HRESULT SetSize(ULARGE_INTEGER cb)
 *   ms887803 Stat: HRESULT Stat(STATSTG* pstatstg, DWORD grfStatFlag)
 *   ms887804 UnlockRegion: HRESULT UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
 *   ms887805 WriteAt: HRESULT WriteAt(ULARGE_INTEGER ulOffset, void const* pv, ULONG cb, ULONG* pcbWritten)
 */

/* IMalloc: documented methods (6 pages).
 *   ms887807 Alloc: void* Alloc(ULONG cb)
 *   ms887808 DidAlloc: int DidAlloc(void* pv)
 *   ms887809 Free: void Free(void* pv)
 *   ms887810 GetSize: ULONG GetSize(void* pv)
 *   ms887811 HeapMinimize: void HeapMinimize()
 *   ms887812 Realloc: void* Realloc(void* pv, ULONG cb)
 */

/* IMallocSpy: documented methods (12 pages).
 *   ms887814 PostAlloc: void* PostAlloc(void* pActual)
 *   ms887815 PostDidAlloc: int PostDidAlloc(void* pRequest, BOOL fSpyed, int fActual)
 *   ms887816 PostFree: void PostFree(BOOL fSpyed)
 *   ms887817 PostGetSize: ULONG PostGetSize(ULONG cbActual, BOOL fSpyed)
 *   ms887818 PostHeapMinimize: void PostHeapMinimize(void)
 *   ms887819 PostRealloc: void* PostRealloc(void* pActual, BOOL fSpyed)
 *   ms887820 PreAlloc: ULONG PreAlloc(ULONG cbRequest)
 *   ms887921 PreDidAlloc: void* PreDidAlloc(void* pRequest, BOOL fSpyed)
 *   ms887929 PreFree: void* PreFree(void* pRequest, BOOL fSpyed)
 *   ms887937 PreGetSize: void* PreGetSize(void* pRequest, BOOL fSpyed)
 *   ms887943 PreHeapMinimize: void PreHeapMinimize(void)
 *   ms887950 PreRealloc: ULONG PreRealloc(void* pRequest, ULONG cbRequest, void** ppNewRequest, BOOL fSpyed)
 */

/* IMarshal: documented methods (6 pages).
 *   ms887969 DisconnectObject: HRESULT DisconnectObject(DWORD dwReserved)
 *   ms887979 GetMarshalSizeMax: HRESULT GetMarshalSizeMax(REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext, DWORD mshlflag...
 *   ms887985 GetUnmarshalClass: HRESULT GetUnmarshalClass(REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext, DWORD mshlflag...
 *   ms889003 MarshalInterface: HRESULT MarshalInterface(IStream* pStm, REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext,...
 *   ms889299 ReleaseMarshalData: HRESULT ReleaseMarshalData(IStream* pStm)
 *   ms889306 UnmarshalInterface: HRESULT UnmarshalInterface(IStream* pStm, REFIID riid, void** ppv)
 */

/* IMessageFilter: documented methods (3 pages).
 *   ms889308 HandleInComingCall: DWORD HandleInComingCall(DWORD dwCallType, HTASK threadIDCaller, DWORD dwTickCount, LPINTERFACEINFO lpInt...
 *   ms889310 MessagePending: DWORD MessagePending(HTASK threadIDCallee, DWORD dwTickCount, DWORD dwPendingType)
 *   ms889311 RetryRejectedCall: DWORD RetryRejectedCall(HTASK threadIDCallee, DWORD dwTickCount, DWORD dwRejectType)
 */

/* IMoniker: documented methods (15 pages).
 *   ms889312 BindToObject: HRESULT BindToObject(IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riidResult, void** ppvResult)
 *   ms889313 BindToStorage: HRESULT BindToStorage(IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, void** ppvObj)
 *   ms889314 CommonPrefixWith: HRESULT CommonPrefixWith(IMoniker* pmkOther, IMoniker** ppmkPrefix)
 *   ms889316 ComposeWith: HRESULT ComposeWith(IMoniker* pmkRight, BOOL fOnlyIfNotGeneric, IMoniker** ppmkComposite)
 *   ms889317 Enum: HRESULT Enum(BOOL fForward, IEnumMoniker** ppenumMoniker)
 *   ms889318 GetDisplayName: HRESULT GetDisplayName(IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* ppszDisplayName)
 *   ms889319 GetTimeOfLastChange: HRESULT GetTimeOfLastChange(IBindCtx* pbc, IMoniker* pmkToLeft, FILETIME* pFileTime)
 *   ms889320 Hash: HRESULT Hash(DWORD* pdwHash)
 *   ms889321 Inverse: HRESULT Inverse(IMoniker** ppmk)
 *   ms889322 IsEqual: HRESULT IsEqual(IMoniker* pmkOtherMoniker)
 *   ms889323 IsRunning: HRESULT IsRunning(IBindCtx* pbc, IMoniker* pmkToLeft, IMoniker* pmkNewlyRunning)
 *   ms889324 IsSystemMoniker: HRESULT IsSystemMoniker(DWORD* pdwMksys)
 *   ms889326 ParseDisplayName: HRESULT ParseDisplayName(IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* pszDisplayName, ULONG* pchEaten, I...
 *   ms889327 Reduce: HRESULT Reduce(IBindCtx* pbc, DWORD dwReduceHowFar, IMoniker** ppmkToLeft, IMoniker** ppmkReduced)
 *   ms889328 RelativePathTo: HRESULT RelativePathTo(IMoniker* pmkOther, IMoniker** ppmkRelPath)
 */

/* IMultiQI: documented methods (1 pages).
 *   ms889331 QueryMultipleInterfaces: HRESULT QueryMultipleInterfaces(ULONG cMQIs, MULTI_QI* pMQIs)
 */

/* IOleItemContainer: documented methods (3 pages).
 *   ms889355 GetObject: HRESULT GetObject(LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx* pbc, REFIID riid, void** ppvObject)
 *   ms889356 GetObjectStorage: HRESULT GetObjectStorage(LPOLESTR pszItem, IBindCtx* pbc, REFIID riid, void** ppvStorage)
 *   ms889357 IsRunning: HRESULT IsRunning(LPOLESTR pszItem)
 */

/* IPersistFile: documented methods (2 pages).
 *   ms889394 GetCurFile: HRESULT GetCurFile(LPOLESTR* ppszFileName)
 *   ms889395 IsDirty: HRESULT IsDirty(void)
 */

/* IPersistPropertyBag: documented methods (3 pages).
 *   ms886021 InitNew: HRESULT InitNew(void)
 *   ms886038 Load: HRESULT Load(IPropertyBag* pPropBag, IErrorlog* pErrorLog)
 *   ms886047 Save: HRESULT Save(IPropertyBag* pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties)
 */

/* IPropertyBag: documented methods (2 pages).
 *   ms886063 Read: HRESULT Read(LPCOLESTR pszPropName, VARIANT* pVar, IErrorlog* pErrorLog)
 *   ms886069 Write: HRESULT Write(LPCOLESTR pszPropName, VARIANT* pVar)
 */

/* IRunningObjectTable: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* IStorage: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* IStream: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ISurrogate: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ITypeComp: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ITypeInfo: documented methods (19 pages).
 *   ms890484 AddressOfMember: HRESULT AddressOfMember(MEMBERID memid, INVOKEKIND invKind, VOID ** ppv)
 *   ms890488 CreateInstance: HRESULT CreateInstance(IUnknown * pUnkOuter, REFIID riid, VOID ** ppvObj)
 *   ms890493 GetContainingTypeLib: HRESULT GetContainingTypeLib(ITypeLib ** ppTLib, unsigned int * pIndex)
 *   ms890496 GetDllEntry: HRESULT GetDllEntry(MEMBERID memid, INVOKEKIND invKind, BSTR * pBstrDllName, BSTR * pBstrName, unsigned s...
 *   ms890501 GetDocumentation: HRESULT GetDocumentation(MEMBERID memid, BSTR * pBstrName, BSTR * pBstrDocString, unsigned long * pdwHelp...
 *   ms890506 GetFuncDesc: HRESULT GetFuncDesc(unsigned int index, FUNCDESC ** ppFuncDesc)
 *   ms890510 GetIDsOfNames: HRESULT GetIDsOfNames(OLECHAR ** rgszNames, unsigned int cNames, MEMBERID * pMemId)
 *   ms890517 GetImplTypeFlags: HRESULT GetImplTypeFlags(unsigned int index, int* pImplTypeFlags)
 *   ms890520 GetMops: HRESULT GetMops(MEMBERID memid, BSTR * pBstrMops)
 *   ms890524 GetNames: HRESULT GetNames(MEMBERID memid, BSTR * rgBstrNames, unsigned int cMaxNames, unsigned int * pcNames)
 *   ms890529 GetRefTypeInfo: HRESULT GetRefTypeInfo(HREFTYPE hRefType, ITypeInfo ** ppTInfo)
 *   ms890533 GetRefTypeOfImplType: HRESULT GetRefTypeOfImplType(unsigned int index, HREFTYPE * pRefType)
 *   ms890537 GetTypeAttr: HRESULT GetTypeAttr(TYPEATTR ** ppTypeAttr)
 *   ms890541 GetTypeComp: HRESULT GetTypeComp(ITypeComp ** ppTComp)
 *   ms890548 GetVarDesc: HRESULT GetVarDesc(unsigned int index, VARDESC ** ppVarDesc)
 *   ms890551 Invoke: HRESULT Invoke(VOID * pvInstance, MEMBERID memid, unsigned short wFlags, DISPPARAMS * pDispParams, VARIAN...
 *   ms890564 ReleaseFuncDesc: HRESULT ReleaseFuncDesc(FUNCDESC * pFuncDesc)
 *   ms890570 ReleaseTypeAttr: HRESULT ReleaseTypeAttr(TYPEATTR * pTypeAttr)
 *   ms890575 ReleaseVarDesc: HRESULT ReleaseVarDesc(VARDESC * pVarDesc)
 */

/* ITypeInfo2: documented methods (14 pages).
 *   ms890300 GetAllFuncCustData: HRESULT GetAllFuncCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890409 GetAllImplTypeCustData: HRESULT GetAllImplTypeCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890417 GetAllParamCustData: HRESULT GetAllParamCustData(unsigned int indexFunc, unsigned int indexParam, CUSTDATA* pCustData)
 *   ms890424 GetAllVarCustData: HRESULT GetAllVarCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890431 GetCustData: HRESULT GetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms890439 GetDocumentation2: HRESULT GetDocumentation2(MEMID memid, LCID lcid, BSTR * pbstrHelpString, unsigned long * pdwHelpStringCo...
 *   ms890446 GetFuncCustData: HRESULT GetFuncCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890451 GetFuncIndexOfMemId: HRESULT GetFuncIndexOfMemId(MEMBERID memid, INVOKEKIND invKind, unsigned int* pFuncIndex)
 *   ms890455 GetImplTypeCustData: HRESULT GetImplTypeCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890459 GetParamCustData: HRESULT GetParamCustData(unsigned int indexFunc, unsigned int indexParam, REFGUID guid, VARIANT* pVarVal)
 *   ms890464 GetTypeFlags: HRESULT GetTypeFlags(unsigned long* pTypeFlags)
 *   ms890468 GetTypeKind: HRESULT GetTypeKind(TYPEKIND* pTypeKind)
 *   ms890473 GetVarCustData: HRESULT GetVarCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890476 GetVarIndexOfMemId: HRESULT GetVarIndexOfMemId(MEMBERID memid, unsigned int* pVarIndex)
 */

/* ITypeLib: documented methods (10 pages).
 *   ms890598 FindName: HRESULT FindName(OLECHAR * szNameBuf, unsigned long lHashVal, ITypeInfo ** ppTInfo, MEMBERID * rgMemId, u...
 *   ms890602 GetDocumentation: HRESULT GetDocumentation(int index, BSTR * pBstrName, BSTR * pBstrDocString, unsigned long * pdwHelpConte...
 *   ms890605 GetLibAttr: HRESULT GetLibAttr(TLIBATTR ** ppTLibAttrr)
 *   ms890610 GetTypeComp: HRESULT GetLibAttr(ITypeComp ** ppTComp)
 *   ms890614 GetTypeInfo: HRESULT GetTypeInfo(unsigned int index, ITypeInfo ** ppTInfo)
 *   ms890620 GetTypeInfoCount: HRESULT GetTypeInfoCount()
 *   ms890629 GetTypeInfoOfGuid: HRESULT GetTypeInfoOfGuid(REFGUID guid, ITypeInfo ** ppTinfo)
 *   ms890632 GetTypeInfoType: HRESULT GetTypeInfoType(unsigned int index, TYPEKIND * pTKind)
 *   ms890638 IsName: HRESULT IsName(OLECHAR * szNameBuf, unsigned long lHashVal, BOOL pfName)
 *   ms890649 ReleaseTLibAttr: HRESULT ReleaseTLibAttr(TLIBATTR * pTLibAttr)
 */

/* ITypeLib2: documented methods (4 pages).
 *   ms890578 GetAllCustData: HRESULT GetAllCustData(CUSTDATA* pCustData)
 *   ms890582 GetCustData: HRESULT GetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms890587 GetDocumentation2: HRESULT GetDocumentation2(in] int index, LCID lcid, BSTR * pbstrHelpString, unsigned long * pdwHelpString...
 *   ms890591 GetLibStatistics: HRESULT GetLibStatistics(unsigned long* pcUniqueNames, unsigned long* pcchUniqueNames)
 */

/* IUnknown: documented methods (3 pages).
 *   ms890658 AddRef: ULONG AddRef(void)
 *   ms890661 QueryInterface: HRESULT QueryInterface(REFIID iid, void** ppvObject)
 *   ms890669 Release: ULONG Release(void)
 */

/* IViewObjectEx: documented methods (5 pages).
 *   ms890692 GetNaturalExtent: HRESULT GetNaturalExtent(DWORD dwAspect, LONG lindex, DVTARGETDEVICE* ptd, HDC hicTargetDev, DVEXTENTINFO...
 *   ms890696 GetRect: HRESULT GetRect(DWORD dwAspect, LPRECTL pRect)
 *   ms890701 GetViewStatus: HRESULT GetViewStatus(DWORD* pdwStatus)
 *   ms890707 QueryHitPoint: HRESULT QueryHitPoint(DWORD dwAspect, LPRECT pRectBounds, POINTL ptlLoc, LONG lCloseHint, DWORD* pHitResult)
 *   ms890711 QueryHitRect: HRESULT QueryHitRect(DWORD dwAspect, LPRECT pRectBounds, LPRECT pRectLoc, LONG lCloseHint, DWORD* pHitRes...
 */

/* ------------------------------------------------------------------ */
/* OLE Automation types (Oaidl.h / Oleauto.h)                         */
/* ------------------------------------------------------------------ */

/* SAFEARRAYBOUND (ms892134). */
typedef struct _SAFEARRAYBOUND {
    unsigned long cElements;
    long          lLbound;
} SAFEARRAYBOUND;

/* SAFEARRAY (ms892133). */
typedef struct _SAFEARRAY {
    unsigned short cDims;
    unsigned short fFeatures;
    unsigned short cbElements;
    unsigned short cLocks;
    unsigned long  handle;
    void          *pvData;
    SAFEARRAYBOUND rgsabound[1];
} SAFEARRAY;

/* FADF_*: the SAFEARRAY page (ms892133). */
#define FADF_AUTO         0x0001
#define FADF_STATIC       0x0002
#define FADF_EMBEDDED     0x0004
#define FADF_FIXEDSIZE    0x0010
#define FADF_BSTR         0x0100
#define FADF_UNKNOWN      0x0200
#define FADF_DISPATCH     0x0400
#define FADF_VARIANT      0x0800
#define FADF_RESERVED     0xF0E8

/* VARIANT and VARIANTARG (ms891678): the page prints the union as
 * anonymous. */
typedef struct _tagVARIANT VARIANT;   /* forward (self-reference in the union) */

typedef struct _tagVARIANT {
    VARTYPE        vt;
    unsigned short wReserved1;
    unsigned short wReserved2;
    unsigned short wReserved3;
    union {
        unsigned char  bVal;
        short          iVal;
        long           lVal;
        float          fltVal;
        double         dblVal;
        VARIANT_BOOL   boolVal;
        SCODE          scode;
        CY             cyVal;
        DATE           date;
        BSTR           bstrVal;
        IUnknown      *punkVal;
        IDispatch     *pdispVal;
        SAFEARRAY     *parray;
        unsigned char *pbVal;
        short         *piVal;
        long          *plVal;
        float         *pfltVal;
        double        *pdblVal;
        VARIANT_BOOL  *pboolVal;
        SCODE         *pscode;
        CY            *pcyVal;
        DATE          *pdate;
        BSTR          *pbstrVal;
        IUnknown     **ppunkVal;
        IDispatch   **ppdispVal;
        SAFEARRAY   **pparray;
        VARIANT       *pvarVal;
        void          *byref;
    };
} VARIANT;
typedef struct _tagVARIANT VARIANTARG;   /* ms891678 */

/* DISPPARAMS (ms886970; Header: Oleauto.h). */
typedef struct _tagDISPPARAMS {
    VARIANTARG *rgvarg;
    DISPID     *rgdispidNamedArgs;
    unsigned int cArgs;
    unsigned int cNamedArgs;
} DISPPARAMS;

/* EXCEPINFO (ms886984). */
typedef struct _tagEXCEPINFO {
    unsigned short wCode;
    unsigned short wReserved;
    BSTR           bstrSource;
    BSTR           bstrDescription;
    BSTR           bstrHelpFile;
    unsigned long  dwHelpContext;
    void          *pvReserved;
    HRESULT (STDAPICALLTYPE *pfnDeferredFillIn)(struct _tagEXCEPINFO *);
    SCODE          scode;
} EXCEPINFO;

/* PARAMDATA (ms891225; Oleauto.h). */
typedef struct _tagPARAMDATA {
    OLECHAR *szName;
    VARTYPE  vtReturn;
} PARAMDATA;

/* METHODDATA (ms890768; Oleauto.h). */
typedef struct _tagMETHODDATA {
    OLECHAR *szName;
    PARAMDATA *ppData;
    DISPID   dispid;
    unsigned int iMeth;
    CALLCONV cc;
    unsigned int cArgs;
    unsigned short wFlags;
    VARTYPE  vtReturn;
} METHODDATA;

/* ------------------------------------------------------------------ */
/* Type library structures (Oaidl.h)                                  */
/* ------------------------------------------------------------------ */

/* TLIBATTR (ms891296). */
typedef struct _tagTLIBATTR {
    GUID   guid;
    LCID   lcid;
    SYSKIND syskind;
    unsigned short wMajorVerNum;
    unsigned short wMinorVerNum;
    unsigned short wLibFlags;
} TLIBATTR, *LPTLIBATTR;

/* TYPEDESC (ms891300).  The page prints the first union member twice
 * with garbage prefixes ("ESC", "tagTYPEDSC" archive artifacts); the
 * documented union is { TYPEDESC*, ARRAYDESC*, HREFTYPE }. */
typedef struct _tagTYPEDESC {
    union {
        struct _tagTYPEDESC *lptdesc;
        struct _tagARRAYDESC *lpadesc;
        HREFTYPE hreftype;
    } u;
    VARTYPE vt;
} TYPEDESC;

/* ARRAYDESC (ms886091). */
typedef struct _tagARRAYDESC {
    TYPEDESC tdescElem;
    unsigned short cDims;
    SAFEARRAYBOUND rgbounds[1];
} ARRAYDESC, *LPARRAYDESC;

/* IDLDESC (ms892132).  The page prints "};IDLDESC" -- the closing
 * brace is restored. */
typedef struct _tagIDLDESC {
    ULONG  dwReserved;
    USHORT wIDLFlags;
} IDLDESC, *LPIDLDESC;

/* PARAMDESC (ms891232).  PARAMDESCEX is opaque (no corpus page). */
typedef struct _tagPARAMDESC {
    LPPARAMDESCEX pparamdescex;
    USHORT        wParamFlags;
} PARAMDESC;

/* ELEMDESC (ms886983).  The page prints the alias as "ELEMDES"
 * (archive typo); the LPELEMDESC pointer alias names the full type. */
typedef struct _tagELEMDESC {
    TYPEDESC tdesc;
    union {
        IDLDESC   idldesc;
        PARAMDESC paramdesc;
    } u;
} ELEMDESC, *LPELEMDESC;

/* FUNCDESC (ms886986). */
typedef struct _tagFUNCDESC {
    MEMBERID memid;
    SCODE   *lprgscode;
    ELEMDESC *lprgelemdescParam;
    FUNCKIND funckind;
    INVOKEKIND invkind;
    CALLCONV callconv;
    short    cParams;
    short    cParamsOpt;
    short    oVft;
    short    cScodes;
    ELEMDESC elemdescFunc;
    WORD     wFuncFlags;
} FUNCDESC;

/* VARDESC (ms891630).  The page's terminating semicolon is missing;
 * "UNION_NAME(u)" expands to the member "u". */
typedef struct _tagVARDESC {
    MEMBERID memid;
    OLECHAR *lpstrSchema;
    union {
        ULONG   oInst;
        VARIANT *lpvarValue;
    } u;
    ELEMDESC elemdescVar;
    USHORT   wVarFlags;
    VARKIND  varkind;
} VARDESC, *LPVARDESC;

/* INTERFACEINFO (ms889334). */
typedef struct _tagINTERFACEINFO {
    LPUNKNOWN pUnk;
    IID       iid;
    WORD      wMethod;
} INTERFACEINFO, *LPINTERFACEINFO;

/* BINDPTR (ms886124). */
typedef union _tagBINDPTR {
    FUNCDESC *lpfuncdesc;
    VARDESC  *lpvardesc;
    ITypeComp *lptcomp;
} BINDPTR;

/* TYPEATTR (ms891299). */
typedef struct _tagTYPEATTR {
    GUID     guid;
    LCID     lcid;
    ULONG    dwReserved;
    MEMBERID memidConstructor;
    MEMBERID memidDestructor;
    OLECHAR *lpstrSchema;
    ULONG    cbSizeInstance;
    TYPEKIND typekind;
    unsigned short cFuncs;
    unsigned short cVars;
    unsigned short cImplTypes;
    unsigned short cbAlignment;
    unsigned short wTypeFlags;
    unsigned short wMajorVerNum;
    unsigned short wMinorVerNum;
    TYPEDESC tdescAlias;
    IDLDESC  idldescType;
} TYPEATTR, *LPTYPEATTR;

/* CUSTDATA / CUSTDATAITEM (ms886959 / ms886960). */
typedef struct _tagCUSTDATAITEM {
    GUID     guid;
    VARIANTARG varValue;
} CUSTDATAITEM, *LPCUSTDATAITEM;

typedef struct _tagCUSTDATA {
    ULONG          cCustData;
    LPCUSTDATAITEM prgCustData;
} CUSTDATA, *LPCUSTDATA;

/* SECURITY_ATTRIBUTES: winbase.h forward-declares it (the CE kernel
 * pages pass it by pointer) and the CE corpus has no standalone page
 * for it; BINDINFO (ms928761) embeds it by value, so the layout is
 * declared here in the form the official Win32 documentation
 * specifies (length / descriptor pointer / inherit flag; typedef
 * redefinition, same type). */
typedef struct _SECURITY_ATTRIBUTES {
    DWORD  nLength;
    LPVOID lpSecurityDescriptor;
    BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES;

/* ------------------------------------------------------------------ */
/* OLE structures (Objidl.h / Wtypes.h)                               */
/* ------------------------------------------------------------------ */

/* COAUTHIDENTITY (ms886203; Wtypes.h). */
typedef struct _COAUTHIDENTITY {
    USHORT *User;
    ULONG   UserLength;
    USHORT *Domain;
    ULONG   DomainLength;
    USHORT *Password;
    ULONG   PasswordLength;
    ULONG   Flags;
} COAUTHIDENTITY;

/* COAUTHINFO (ms886208; Wtypes.h). */
typedef struct _COAUTHINFO {
    DWORD            dwAuthnSvc;
    DWORD            dwAuthzSvc;
    LPWSTR           pwszServerPrincName;
    DWORD            dwAuthnLevel;
    DWORD            dwImpersonationLevel;
    COAUTHIDENTITY  *pAuthIdentityData;
    DWORD            dwCapabilities;
} COAUTHINFO;

/* COSERVERINFO (ms886935; Wtypes.h). */
typedef struct _COSERVERINFO {
    DWORD       dwReserved1;
    LPWSTR      pwszName;
    COAUTHINFO *pAuthInfo;
    DWORD       dwReserved2;
} COSERVERINFO;

/* SOLE_AUTHENTICATION_SERVICE (ms891267). */
typedef struct _SOLE_AUTHENTICATION_SERVICE {
    DWORD    dwAuthnSvc;
    DWORD    dwAuthzSvc;
    OLECHAR *pPrincipalName;
    HRESULT  hr;
} SOLE_AUTHENTICATION_SERVICE;

/* MULTI_QI (ms890798). */
typedef struct _MULTI_QI {
    const IID *pIID;
    IUnknown  *pItf;
    HRESULT    hr;
} MULTI_QI;

/* DVTARGETDEVICE (ms886982). */
typedef struct _DVTARGETDEVICE {
    DWORD tdSize;
    WORD  tdDriverNameOffset;
    WORD  tdDeviceNameOffset;
    WORD  tdPortNameOffset;
    WORD  tdExtDevmodeOffset;
    BYTE  tdData;
} DVTARGETDEVICE;

/* FORMATETC (ms886985). */
typedef struct _FORMATETC {
    unsigned long    cfFormat;
    DVTARGETDEVICE  *ptd;
    unsigned long    dwAspect;
    long             lindex;
    unsigned long    tymed;
} FORMATETC, *LPFORMATETC;

/* STGMEDIUM (ms891275; the CE 5.0 page ms928939 prints MIDL
 * attributes, stripped here). */
typedef struct _tagSTGMEDIUM {
    unsigned long tymed;
    union {
        HBITMAP       hBitmap;
        HMETAFILEPICT hMetaFilePict;
        HENHMETAFILE  hEnhMetaFile;
        HGLOBAL       hGlobal;
        LPOLESTR      lpszFileName;
        IStream      *pstm;
        IStorage     *pstg;
    } u;
    IUnknown *pUnkForRelease;
} STGMEDIUM, *LPSTGMEDIUM;

/* STATSTG (ms891269). */
typedef struct _tagSTATSTG {
    LPOLESTR        pwcsName;
    DWORD           type;
    ULARGE_INTEGER  cbSize;
    FILETIME        mtime;
    FILETIME        ctime;
    FILETIME        atime;
    DWORD           grfMode;
    DWORD           grfLocksSupported;
    CLSID           clsid;
    DWORD           grfStateBits;
    DWORD           reserved;
} STATSTG;

/* BIND_OPTS (ms886131). */
typedef struct _tagBIND_OPTS {
    DWORD cbStruct;
    DWORD grfFlags;
    DWORD grfMode;
    DWORD dwTickCountDeadline;
} BIND_OPTS, *LPBIND_OPTS;

/* BIND_OPTS2 (ms886139). */
typedef struct _tagBIND_OPTS2 {
    DWORD          cbStruct;
    DWORD          grfFlags;
    DWORD          grfMode;
    DWORD          dwTickCountDeadline;
    DWORD          dwTrackFlags;
    DWORD          dwClassContext;
    LCID           locale;
    COSERVERINFO  *pServerInfo;
} BIND_OPTS2, *LPBIND_OPTS2;

/* BINDINFO (ms928761). */
typedef struct _tagBINDINFO {
    ULONG              cbSize;
    LPWSTR             szExtraInfo;
    STGMEDIUM          stgmedData;
    DWORD              grfBindInfoF;
    DWORD              dwBindVerb;
    LPWSTR             szCustomVerb;
    DWORD              cbStgmedData;
    DWORD              dwOptions;
    DWORD              dwOptionsFlags;
    DWORD              dwCodePage;
    SECURITY_ATTRIBUTES securityAttributes;
    IID                iid;
    IUnknown          *pUnk;
    DWORD              dwReserved;
} BINDINFO;

/* LICINFO (ms890747; Ocidl.h). */
typedef struct _tagLICINFO {
    ULONG cbLicInfo;
    BOOL  fRuntimeKeyAvail;
    BOOL  fLicVerified;
} LICINFO;

/* Ocidl.h structures. */
/* ms863928: members/signature verified against this page (type-cite) */
typedef struct _tagCONNECTDATA {   /* ms886466 */
    IUnknown *pUnk;
    DWORD     dwCookie;
} CONNECTDATA;

typedef struct _tagCONTROLINFO {   /* ms886467 */
    ULONG   cb;
    HACCEL  hAccel;
    USHORT  cAccel;
    DWORD   dwFlags;
} CONTROLINFO;

typedef struct _tagDVASPECTINFO {  /* ms886978: page prints "struct
                                    * STRUCT ... UNIT cb" (typos) */
    ULONG cb;
    DWORD dwFlags;
} DVASPECTINFO;

typedef struct _tagDVEXTENTINFO {  /* ms886980 */
    ULONG    cb;
    DWORD    dwExtentMode;
    SIZEL    sizelProposed;
} DVEXTENTINFO;

/* ------------------------------------------------------------------ */
/* Free functions                                                      */
/* ------------------------------------------------------------------ */

/* ---- OLE (ole32.dll) (84 functions) ---- */

/* ms886121 "BindMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT BindMoniker(LPMONIKER pmk, DWORD grfOpt, REFIID iidResult, LPVOID * ppvResult) AKARI_CE_NAME(BindMoniker);

/* ms886181 "CLSIDFromProgID" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT CLSIDFromProgID(LPCOLESTR lpszProgID, LPCLSID pclsid) AKARI_CE_NAME(CLSIDFromProgID);

/* ms886190 "CLSIDFromString" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CLSIDFromString(LPOLESTR lpsz, LPCLSID pclsid) AKARI_CE_NAME(CLSIDFromString);

/* ms886201 "CoAddRefServerProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT ULONG CoAddRefServerProcess(void) AKARI_CE_NAME(CoAddRefServerProcess);

/* ms886216 "CoCopyProxy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCopyProxy(IUnknown* pProxy, IUnknown** ppCopy) AKARI_CE_NAME(CoCopyProxy);

/* ms886221 "CoCreateFreeThreadedMarshaler" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter, LPUNKNOWN* ppunkMarshaler) AKARI_CE_NAME(CoCreateFreeThreadedMarshaler);

/* ms886229 "CoCreateGuid" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateGuid(GUID* pguid) AKARI_CE_NAME(CoCreateGuid);

/* ms886232 "CoCreateInstance" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoCreateInstance);

/* ms886235 "CoCreateInstanceEx" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateInstanceEx(REFCLSID rclsid, IUnknown* punkOuter, DWORD dwClsCtx, COSERVERINFO* pServerInfo, ULONG cmq, MULTI_QI* pResults) AKARI_CE_NAME(CoCreateInstanceEx);

/* ms886239 "CoDisconnectObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoDisconnectObject(IUnknown* pUnk, DWORD dwReserved) AKARI_CE_NAME(CoDisconnectObject);

/* ms886243 "CoFileTimeNow" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoFileTimeNow(FILETIME* lpFileTime) AKARI_CE_NAME(CoFileTimeNow);

/* ms886248 "CoFreeAllLibraries" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT void CoFreeAllLibraries(void) AKARI_CE_NAME(CoFreeAllLibraries);

/* ms886250 "CoFreeLibrary" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoFreeLibrary(HINSTANCE hInst) AKARI_CE_NAME(CoFreeLibrary);

/* ms886254 "CoFreeUnusedLibraries" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoFreeUnusedLibraries(void) AKARI_CE_NAME(CoFreeUnusedLibraries);

/* ms886256 "CoGetCallContext" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetCallContext(REFIID riid, void** ppInterface) AKARI_CE_NAME(CoGetCallContext);

/* ms886259 "CoGetClassObject" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetClassObject(REFCLSID rclsid, WORD dwClsContext, COSERVERINFO* pServerInfo, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoGetClassObject);

/* ms886262 "CoGetCurrentProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT DWORD CoGetCurrentProcess(void) AKARI_CE_NAME(CoGetCurrentProcess);

/* ms886267 "CoGetInstanceFromFile" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInstanceFromFile(COSERVERINFO* pServerInfo, CLSID* pclsid, IUnknown* punkOuter, DWORD dwClsCtx, DWORD grfMode, OLECHAR* szName, ULONG cmq, MULTI_QI* rgmqResults) AKARI_CE_NAME(CoGetInstanceFromFile);

/* ms886271 "CoGetInstanceFromIStorage" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInstanceFromIStorage(COSERVERINFO* pServerInfo, CLSID* pclsid, IUnknown* punkOuter, DWORD dwClsCtx, IStorage* pstg, ULONG cmq, MULTI_QI* rgmqResults) AKARI_CE_NAME(CoGetInstanceFromIStorage);

/* ms886275 "CoGetInterfaceAndReleaseStream" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInterfaceAndReleaseStream(LPSTREAM pStm, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoGetInterfaceAndReleaseStream);

/* ms886278 "CoGetMalloc" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetMalloc(DWORD dwMemContext, LPMALLOC* ppMalloc) AKARI_CE_NAME(CoGetMalloc);

/* ms886282 "CoGetMarshalSizeMax" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetMarshalSizeMax(ULONG* pulSize, REFIID riid, IUnknown* pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags) AKARI_CE_NAME(CoGetMarshalSizeMax);

/* ms886284 "CoGetObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetObject(LPCWSTR pszName, BIND_OPTS* pBindOptions, REFIID riid, void** ppv) AKARI_CE_NAME(CoGetObject);

/* ms886289 "CoGetPSClsid" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetPSClsid(REFIID riid, CLSID* pclsid) AKARI_CE_NAME(CoGetPSClsid);

/* ms886292 "CoGetStandardMarshal" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetStandardMarshal(REFIID riid, IUnknown* pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags, LPMARSHAL* ppMarshal) AKARI_CE_NAME(CoGetStandardMarshal);

/* ms886297 "CoGetTreatAsClass" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetTreatAsClass(REFCLSID clsidOld, LPCLSID pclsidNew) AKARI_CE_NAME(CoGetTreatAsClass);

/* ms886299 "CoImpersonateClient" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoImpersonateClient(void) AKARI_CE_NAME(CoImpersonateClient);

/* ms886303 "CoInitialize" (Header: Objbase.h; Link Library:
 * Ole32.lib; Windows CE 3.0 and later).  TWIN NOTE (M73a): the CE 5
 * COM Functions page ms863914 prints "This function is not
 * supported. Instead, your application should call CoInitializeEx
 * using the COINIT_MULTITHREADED constant" and carries NO
 * Requirements block; the CE 3.0 page documents the export, so the
 * declaration and the ole32-doc.def entry stand on ms886303 with
 * the CE 5 deprecation recorded. */
AKARI_CE_IMPORT HRESULT CoInitialize(LPVOID pvReserved) AKARI_CE_NAME(CoInitialize);

/* ms886306 "CoInitializeEx" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit) AKARI_CE_NAME(CoInitializeEx);

/* ms886314 "CoInitializeSecurity" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoInitializeSecurity(PSECURITY_DESCRIPTOR pVoid, LONG cAuthSvc, SOLE_AUTHENTICATION_SERVICE* asAuthSvc, void* pReserved1, DWORD dwAuthnLevel, DWORD dwImpLevel, SOLE_AUTHENTICATION_LIST* pAuthList, DWORD dwCapabilities, void* pReserved3) AKARI_CE_NAME(CoInitializeSecurity);

/* ms886324 "CoIsHandlerConnected" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT BOOL CoIsHandlerConnected(LPUNKNOWN pUnk) AKARI_CE_NAME(CoIsHandlerConnected);

/* ms886335 "CoIsOle1Class" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT BOOL CoIsOle1Class(REFCLSID rclsid) AKARI_CE_NAME(CoIsOle1Class);

/* ms886346 "CoLoadLibrary" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HINSTANCE CoLoadLibrary(LPOLESTR lpszLibName, BOOL bAutoFree) AKARI_CE_NAME(CoLoadLibrary);

/* ms886357 "CoLockObjectExternal" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoLockObjectExternal(IUnknown* pUnk, BOOL fLock, BOOL fLastUnlockReleases) AKARI_CE_NAME(CoLockObjectExternal);

/* ms886365 "CoMarshalHresult" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalHresult(IStream* pStm, HRESULT hresult) AKARI_CE_NAME(CoMarshalHresult);

/* ms886456 "CoMarshalInterface" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalInterface(IStream* pStm, REFIID riid, IUnknown* pUnk, DWORD dwDestContext, void* pvDestContext, DWORD mshlflags) AKARI_CE_NAME(CoMarshalInterface);

/* ms886464 "CoMarshalInterThreadInterfaceInStream" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalInterThreadInterfaceInStream(REFIID riid, LPUNKNOWN pUnk, LPSTREAM* ppStm) AKARI_CE_NAME(CoMarshalInterThreadInterfaceInStream);

/* ms886468 "CoQueryAuthenticationServices" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryAuthenticationServices(DWORD* pcAuthSvc, SOLE_AUTHENTICATION_SERVICE** asAuthSvc) AKARI_CE_NAME(CoQueryAuthenticationServices);

/* ms886469 "CoQueryClientBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryClientBlanket(DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DWORD* pAuthnLevel, DWORD* pImpLevel, RPC_AUTHZ_HANDLE* pPrivs, DWORD** pCapabilities) AKARI_CE_NAME(CoQueryClientBlanket);

/* ms886470 "CoQueryProxyBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryProxyBlanket(IUnknown* pProxy, DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DWORD* pAuthnLevel, DWORD* pImpLevel, RPC_AUTH_IDENTITY_HANDLE* ppAuthInfo, DWORD* pCapabilities) AKARI_CE_NAME(CoQueryProxyBlanket);

/* ms886471 "CoRegisterClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterClassObject(REFCLSID rclsid, IUnknown* pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister) AKARI_CE_NAME(CoRegisterClassObject);

/* ms886472 "CoRegisterMallocSpy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterMallocSpy(LPMALLOCSPY pMallocSpy) AKARI_CE_NAME(CoRegisterMallocSpy);

/* ms886491 "CoRegisterMessageFilter" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter, LPMESSAGEFILTER* lplpMessageFilter) AKARI_CE_NAME(CoRegisterMessageFilter);

/* ms886499 "CoRegisterPSClsid" (Header: Objbase.h; Windows CE 3.0 and later).
 * Page artifact: printed prototype says CoRegisterPSCLsid; the documented title (and export name) is CoRegisterPSClsid.
 */
AKARI_CE_IMPORT HRESULT CoRegisterPSClsid(REFIID riid, REFCLSID rclsid) AKARI_CE_NAME(CoRegisterPSClsid);

/* ms886609 "CoRegisterSurrogate" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterSurrogate(ISurrogate* pSurrogate) AKARI_CE_NAME(CoRegisterSurrogate);

/* ms886724 "CoReleaseMarshalData" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoReleaseMarshalData(IStream* pStm) AKARI_CE_NAME(CoReleaseMarshalData);

/* ms886823 "CoReleaseServerProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT ULONG CoReleaseServerProcess(void) AKARI_CE_NAME(CoReleaseServerProcess);

/* ms886929 "CoResumeClassObjects" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoResumeClassObjects(void) AKARI_CE_NAME(CoResumeClassObjects);

/* ms886931 "CoRevertToSelf" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevertToSelf(void) AKARI_CE_NAME(CoRevertToSelf);

/* ms886932 "CoRevokeClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevokeClassObject(DWORD dwRegister) AKARI_CE_NAME(CoRevokeClassObject);

/* ms886933 "CoRevokeMallocSpy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevokeMallocSpy(void) AKARI_CE_NAME(CoRevokeMallocSpy);

/* ms886936 "CoSetProxyBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSetProxyBlanket(IUnknown* pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, WCHAR* pServerPrincName, DWORD dwAuthnLevel, DWORD dwImpLevel, RPC_AUTH_IDENTITY_HANDLE pAuthInfo, DWORD dwCapabilities) AKARI_CE_NAME(CoSetProxyBlanket);

/* ms886937 "CoSuspendClassObjects" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSuspendClassObjects(void) AKARI_CE_NAME(CoSuspendClassObjects);

/* ms886938 "CoSwitchCallContext" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSwitchCallContext(IUnknown* pNewObject, IUnknown** ppOldObject) AKARI_CE_NAME(CoSwitchCallContext);

/* ms886939 "CoTaskMemAlloc" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT LPVOID CoTaskMemAlloc(ULONG cb) AKARI_CE_NAME(CoTaskMemAlloc);

/* ms886940 "CoTaskMemFree" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoTaskMemFree(LPVOID pv) AKARI_CE_NAME(CoTaskMemFree);

/* ms886941 "CoTaskMemRealloc" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT LPVOID CoTaskMemRealloc(LPVOID pv, ULONG cb) AKARI_CE_NAME(CoTaskMemRealloc);

/* ms886942 "CoTreatAsClass" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoTreatAsClass(REFCLSID clsidOld, REFCLSID clsidNew) AKARI_CE_NAME(CoTreatAsClass);

/* ms886943 "CoUninitialize" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoUninitialize(void) AKARI_CE_NAME(CoUninitialize);

/* ms886944 "CoUnmarshalHresult" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoUnmarshalHresult(LPSTREAM pStm, HRESULT* phresult) AKARI_CE_NAME(CoUnmarshalHresult);

/* ms886945 "CoUnmarshalInterface" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoUnmarshalInterface(IStream* pStm, REFIID riid, void** ppv) AKARI_CE_NAME(CoUnmarshalInterface);

/* ms886946 "CreateAntiMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateAntiMoniker(LPMONIKER * ppmk) AKARI_CE_NAME(CreateAntiMoniker);

/* ms886947 "CreateBindCtx" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT CreateBindCtx(DWORD reserved, LPBC * ppbc) AKARI_CE_NAME(CreateBindCtx);

/* ms886948 "CreateClassMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateClassMoniker(REFCLSID rclsid, IMoniker** ppmk) AKARI_CE_NAME(CreateClassMoniker);

/* ms886950 "CreateFileMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateFileMoniker(LPCOLESTR lpszPathName, LPMONIKER * ppmk) AKARI_CE_NAME(CreateFileMoniker);

/* ms886951 "CreateGenericComposite" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateGenericComposite(LPMONIKER pmkFirst, LPMONIKER pmkRest, LPMONIKER * ppmkComposite) AKARI_CE_NAME(CreateGenericComposite);

/* ms886952 "CreateItemMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateItemMoniker(LPCOLESTR lpszDelim, LPCOLESTR lpszItem, LPMONIKER * ppmk) AKARI_CE_NAME(CreateItemMoniker);

/* ms886954 "CreatePointerMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreatePointerMoniker(LPUNKNOWN punk, LPMONIKER * ppmk) AKARI_CE_NAME(CreatePointerMoniker);

/* ms886973 "DllGetClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(DllGetClassObject);

/* ms886988 "GetClassFile" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT GetClassFile(LPCWSTR szFileName, CLSID* pclsid) AKARI_CE_NAME(GetClassFile);

/* ms886991 "GetRunningObjectTable" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT GetRunningObjectTable(DWORD reserved, LPRUNNINGOBJECTTABLE* pprot) AKARI_CE_NAME(GetRunningObjectTable);

/* ms887797 "IIDFromString" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT IIDFromString(LPOLESTR lpsz, LPIID lpiid) AKARI_CE_NAME(IIDFromString);

/* ms890774 "MkParseDisplayName" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MkParseDisplayName(LPBC pbc, LPCOLESTR szUserName, ULONG * pchEaten, LPMONIKER * ppmk) AKARI_CE_NAME(MkParseDisplayName);

/* ms890790 "MonikerCommonPrefixWith" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MonikerCommonPrefixWith(LPMONIKER pmkThis, LPMONIKER pmkOther, LPMONIKER * ppmkCommon) AKARI_CE_NAME(MonikerCommonPrefixWith);

/* ms890794 "MonikerRelativePathTo" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MonikerRelativePathTo(LPMONIKER pmkSrc, LPMONIKER pmkDest, LPMONIKER * ppmkRelPath, BOOL dwReserved) AKARI_CE_NAME(MonikerRelativePathTo);

/* ms891234 "ProgIDFromCLSID" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT ProgIDFromCLSID(REFCLSID clsid, LPOLESTR* lplpszProgID) AKARI_CE_NAME(ProgIDFromCLSID);

/* ms891271 "StgCreateDocfile" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgCreateDocfile(const WCHAR* pwcsName, DWORD grfMode, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgCreateDocfile);

/* ms891272 "StgCreateDocfileOnILockBytes" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgCreateDocfileOnILockBytes(ILockBytes* plkbyt, DWORD grfMode, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgCreateDocfileOnILockBytes);

/* ms891276 "StgOpenStorage" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgOpenStorage(const WCHAR* pwcsName, IStorage* pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgOpenStorage);

/* ms891277 "StgOpenStorageOnILockBytes" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgOpenStorageOnILockBytes(ILockBytes* plkbyt, IStorage* pStgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgOpenStorageOnILockBytes);

/* ms891280 "StringFromCLSID" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StringFromCLSID(REFCLSID rclsid, LPOLESTR* ppsz) AKARI_CE_NAME(StringFromCLSID);

/* ms891281 "StringFromGUID2" (Header: Objbase.h; Windows CE 2.0 and later).
 * Page artifact: printed form lacks a return type; "Return Values" says it returns the character count (int).
 */
AKARI_CE_IMPORT int StringFromGUID2(REFGUID rguid, LPOLESTR lpsz, int cbMax) AKARI_CE_NAME(StringFromGUID2);

/* ms891282 "StringFromIID" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StringFromIID(REFIID rclsid, LPOLESTR* lplpsz) AKARI_CE_NAME(StringFromIID);

/* ms891304 "UpdateDCOMSettings" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT void UpdateDCOMSettings(void) AKARI_CE_NAME(UpdateDCOMSettings);

/* ---- OLE Automation (oleaut32.dll) (245 functions) moved to Oleauto.h,
 * 2026-09-16 -- see that file's header comment and
 * docs/CHANGELOG-audit-2026-09-16.md. ---- */

/* ------------------------------------------------------------------ */
/* Auxiliary spellings the M97 vtable fill-in signatures reference:     */
/* LP aliases of recorded structs / interface-pointer spellings R1      */
/* uses, plus opaque forward carriers for pointer-only parameters.      */
/* ------------------------------------------------------------------ */
typedef FUNCDESC *LPFUNCDESC;
typedef ITypeInfo *LPTYPEINFO;
typedef ITypeLib *LPTYPELIB;
typedef ITypeComp *LPTYPECOMP;
typedef struct IEnumUnknown IEnumUnknown;  /* opaque; pointer-only use */
/* Category / ole-container spellings the Comcat-family records use
 * (ICatInformation / ICatRegister, recorded here per their pages):
 * CATID is the category-GUID twin of IID/CLSID; the IEnum* carriers
 * and LPOLECONTAINER are pointer-only forward declarations. */
typedef GUID CATID;
#define REFCATID            const CATID *
typedef struct IEnumCLSID       IEnumCLSID;        /* opaque */
typedef struct IEnumCATID       IEnumCATID;        /* opaque */
typedef struct IEnumCATEGORYINFO IEnumCATEGORYINFO; /* opaque */
typedef struct IEnumSTATDATA    IEnumSTATDATA;     /* opaque (page
    misprint spells it IENumSTATDATA -- normalized in the vtables) */
typedef IOleContainer *LPOLECONTAINER;
typedef struct CATEGORYINFO CATEGORYINFO;   /* opaque; RegisterCategories
    takes it as an array (pointer-only use here) */
/* OLE carrier types the embedding-family vtables reference (same
 * shapes as their GDI twins; the M44 "OLE carriers" note).  RECTL /
 * POINTL / POINTF / SIZEL are pointer-only here apart from their
 * trivial layouts. */
/* POINTL moved to Windef.h (the GDI/DDI books share it) */
typedef struct _POINTF { FLOAT x; FLOAT y; } POINTF, *LPPOINTF;
/* SIZEL / RECTL are already declared (Windef); only the OLE pointer
 * spellings are added. */
typedef SIZEL *LPSIZEL;
typedef const RECTL *LPCRECTL;
typedef struct OLEINPLACEFRAMEINFO OLEINPLACEFRAMEINFO,
    *LPOLEINPLACEFRAMEINFO;      /* opaque; pointer-only use */
typedef LOGPALETTE *LPLOGPALETTE;   /* GetColorSet out-parameter */
typedef struct IOleInPlaceFrame     IOleInPlaceFrame;      /* opaque */
typedef struct IOleInPlaceUIWindow  IOleInPlaceUIWindow;   /* opaque */
typedef struct IEnumOLEVERB         IEnumOLEVERB;          /* opaque
    (R1 spells it IEnumOleVerb in a fill-in -- normalized) */
typedef BOOL (WINAPI *LPFNCONTINUE)(DWORD);  /* IViewObject::Draw
    continuation callback (R1 spells it __IView_pfncont) */

/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* M97 vtable adoption -- COM interfaces made callable from C.  Vtable
 * ORDER adopted from R1 (CeGCC-lineage w32api, public
 * domain; docs/clean-room.md par.4 revision 2026-09-10);
 * method names/types are the CE pages' own printed
 * signatures (the records above).  Methods the CE pages do
 * not document but R1 carries are INCLUDED and tagged
 * "(R1)" -- dropping a middle slot would shift the layout.
 * Calling convention: plain function pointers (WINAPI is
 * empty here: CE-wide cdecl; R1's __stdcall NOT adopted). */
/* ================================================================== */

/* ---- IAdviseSink: 5 documented method pages; order R1 ---- */
typedef struct IAdviseSinkVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IAdviseSink*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IAdviseSink*);  /* (R1) */
    ULONG (WINAPI *Release)(IAdviseSink*);  /* (R1) */
    /* IAdviseSink */
    void (WINAPI *OnDataChange)(IAdviseSink*, FORMATETC* pFormatetc, STGMEDIUM* pStgmed);  /* 887006 */
    void (WINAPI *OnViewChange)(IAdviseSink*, DWORD dwAspect, LONG lindex);  /* 887009 */
    void (WINAPI *OnRename)(IAdviseSink*, IMoniker* pmk);  /* 887007 */
    void (WINAPI *OnSave)(IAdviseSink*);  /* 887008 */
    void (WINAPI *OnClose)(IAdviseSink*);  /* 887005 */
} IAdviseSinkVtbl;
struct IAdviseSink { const IAdviseSinkVtbl *lpVtbl; };
#define IAdviseSink_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IAdviseSink_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IAdviseSink_Release(T) ((T)->lpVtbl->Release(T))
#define IAdviseSink_OnDataChange(T,a,b) ((T)->lpVtbl->OnDataChange(T,a,b))
#define IAdviseSink_OnViewChange(T,a,b) ((T)->lpVtbl->OnViewChange(T,a,b))
#define IAdviseSink_OnRename(T,a) ((T)->lpVtbl->OnRename(T,a))
#define IAdviseSink_OnSave(T) ((T)->lpVtbl->OnSave(T))
#define IAdviseSink_OnClose(T) ((T)->lpVtbl->OnClose(T))

/* ---- IBindCtx: 10 documented method pages; order R1 ---- */
typedef struct IBindCtxVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IBindCtx*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IBindCtx*);  /* (R1) */
    ULONG (WINAPI *Release)(IBindCtx*);  /* (R1) */
    /* IBindCtx */
    HRESULT (WINAPI *RegisterObjectBound)(IBindCtx*, IUnknown* punk);  /* 887015 */
    HRESULT (WINAPI *RevokeObjectBound)(IBindCtx*, IUnknown* punk);  /* 887018 */
    HRESULT (WINAPI *ReleaseBoundObjects)(IBindCtx*);  /* 887017 */
    HRESULT (WINAPI *SetBindOptions)(IBindCtx*, BIND_OPTS* pbindopts);  /* 887020 */
    HRESULT (WINAPI *GetBindOptions)(IBindCtx*, BIND_OPTS* pbindopts);  /* 887011 */
    HRESULT (WINAPI *GetRunningObjectTable)(IBindCtx*, IRunningObjectTable** pprot);  /* 887013 */
    HRESULT (WINAPI *RegisterObjectParam)(IBindCtx*, LPOLESTR pszKey, IUnknown* punk);  /* 887016 */
    HRESULT (WINAPI *GetObjectParam)(IBindCtx*, LPOLESTR pszKey, IUnknown** ppunk);  /* 887012 */
    HRESULT (WINAPI *EnumObjectParam)(IBindCtx*, IEnumString** ppenum);  /* 887010 */
    HRESULT (WINAPI *RevokeObjectParam)(IBindCtx*, LPOLESTR pszKey);  /* 887019 */
} IBindCtxVtbl;
struct IBindCtx { const IBindCtxVtbl *lpVtbl; };
#define IBindCtx_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IBindCtx_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IBindCtx_Release(T) ((T)->lpVtbl->Release(T))
#define IBindCtx_RegisterObjectBound(T,a) ((T)->lpVtbl->RegisterObjectBound(T,a))
#define IBindCtx_RevokeObjectBound(T,a) ((T)->lpVtbl->RevokeObjectBound(T,a))
#define IBindCtx_ReleaseBoundObjects(T) ((T)->lpVtbl->ReleaseBoundObjects(T))
#define IBindCtx_SetBindOptions(T,a) ((T)->lpVtbl->SetBindOptions(T,a))
#define IBindCtx_GetBindOptions(T,a) ((T)->lpVtbl->GetBindOptions(T,a))
#define IBindCtx_GetRunningObjectTable(T,a) ((T)->lpVtbl->GetRunningObjectTable(T,a))
#define IBindCtx_RegisterObjectParam(T,a,b) ((T)->lpVtbl->RegisterObjectParam(T,a,b))
#define IBindCtx_GetObjectParam(T,a,b) ((T)->lpVtbl->GetObjectParam(T,a,b))
#define IBindCtx_EnumObjectParam(T,a) ((T)->lpVtbl->EnumObjectParam(T,a))
#define IBindCtx_RevokeObjectParam(T,a) ((T)->lpVtbl->RevokeObjectParam(T,a))

/* ---- IClassActivator: 1 documented method pages; order R1 ---- */
typedef struct IClassActivatorVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IClassActivator*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IClassActivator*);  /* (R1) */
    ULONG (WINAPI *Release)(IClassActivator*);  /* (R1) */
    /* IClassActivator */
    HRESULT (WINAPI *GetClassObject)(IClassActivator*, REFCLSID* pClassID, DWORD dwClsContext, LCID locale, REFIID riid, void** ppv);  /* 887268 */
} IClassActivatorVtbl;
struct IClassActivator { const IClassActivatorVtbl *lpVtbl; };
#define IClassActivator_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IClassActivator_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IClassActivator_Release(T) ((T)->lpVtbl->Release(T))
#define IClassActivator_GetClassObject(T,a,b,c,d,e) ((T)->lpVtbl->GetClassObject(T,a,b,c,d,e))

/* ---- IClassFactory: 2 documented method pages; order R1 ---- */
typedef struct IClassFactoryVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IClassFactory*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IClassFactory*);  /* (R1) */
    ULONG (WINAPI *Release)(IClassFactory*);  /* (R1) */
    /* IClassFactory */
    HRESULT (WINAPI *CreateInstance)(IClassFactory*, IUnknown* pUnkOuter, REFIID riid, void** ppvObject);  /* 887274 */
    HRESULT (WINAPI *LockServer)(IClassFactory*, BOOL fLock);  /* 887276 */
} IClassFactoryVtbl;
struct IClassFactory { const IClassFactoryVtbl *lpVtbl; };
#define IClassFactory_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IClassFactory_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IClassFactory_Release(T) ((T)->lpVtbl->Release(T))
#define IClassFactory_CreateInstance(T,a,b,c) ((T)->lpVtbl->CreateInstance(T,a,b,c))
#define IClassFactory_LockServer(T,a) ((T)->lpVtbl->LockServer(T,a))

/* ---- IClassFactory2: 2 documented method pages; order R1 ---- */
typedef struct IClassFactory2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IClassFactory2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IClassFactory2*);  /* (R1) */
    ULONG (WINAPI *Release)(IClassFactory2*);  /* (R1) */
    /* IClassFactory */
    HRESULT (WINAPI *CreateInstance)(IClassFactory2*, LPUNKNOWN, REFIID, PVOID*);  /* (R1) */
    HRESULT (WINAPI *LockServer)(IClassFactory2*, BOOL);  /* (R1) */
    /* IClassFactory2 */
    HRESULT (WINAPI *GetLicInfo)(IClassFactory2*, LICINFO* pLicInfo);  /* 887271 */
    HRESULT (WINAPI *RequestLicKey)(IClassFactory2*, DWORD dwReserved, BSTR* pbstrKey);  /* 887273 */
    HRESULT (WINAPI *CreateInstanceLic)(IClassFactory2*, LPUNKNOWN, LPUNKNOWN, REFIID, BSTR, PVOID*);  /* (R1) */
} IClassFactory2Vtbl;
struct IClassFactory2 { const IClassFactory2Vtbl *lpVtbl; };
#define IClassFactory2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IClassFactory2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IClassFactory2_Release(T) ((T)->lpVtbl->Release(T))
#define IClassFactory2_CreateInstance(T,a,b,c) ((T)->lpVtbl->CreateInstance(T,a,b,c))
#define IClassFactory2_LockServer(T,a) ((T)->lpVtbl->LockServer(T,a))
#define IClassFactory2_GetLicInfo(T,a) ((T)->lpVtbl->GetLicInfo(T,a))
#define IClassFactory2_RequestLicKey(T,a,b) ((T)->lpVtbl->RequestLicKey(T,a,b))
#define IClassFactory2_CreateInstanceLic(T,a,b,c,d,e) ((T)->lpVtbl->CreateInstanceLic(T,a,b,c,d,e))

/* ---- IClientSecurity: 1 documented method pages; order R1 ---- */
typedef struct IClientSecurityVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IClientSecurity*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IClientSecurity*);  /* (R1) */
    ULONG (WINAPI *Release)(IClientSecurity*);  /* (R1) */
    /* IClientSecurity */
    HRESULT (WINAPI *QueryBlanket)(IClientSecurity*, VOID*, PDWORD, PDWORD, OLECHAR**, PDWORD, PDWORD, RPC_AUTH_IDENTITY_HANDLE**, PDWORD*);  /* (R1) */
    HRESULT (WINAPI *SetBlanket)(IClientSecurity*, VOID*, DWORD, DWORD, LPWSTR, DWORD, DWORD, RPC_AUTH_IDENTITY_HANDLE*, DWORD);  /* (R1) */
    HRESULT (WINAPI *CopyProxy)(IClientSecurity*, IUnknown* pProxy, IUnknown** ppCopy);  /* 887277 */
} IClientSecurityVtbl;
struct IClientSecurity { const IClientSecurityVtbl *lpVtbl; };
#define IClientSecurity_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IClientSecurity_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IClientSecurity_Release(T) ((T)->lpVtbl->Release(T))
#define IClientSecurity_QueryBlanket(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->QueryBlanket(T,a,b,c,d,e,f,g,h))
#define IClientSecurity_SetBlanket(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->SetBlanket(T,a,b,c,d,e,f,g,h))
#define IClientSecurity_CopyProxy(T,a,b) ((T)->lpVtbl->CopyProxy(T,a,b))

/* ---- IConnectionPoint: 5 documented method pages; order R1 ---- */
typedef struct IConnectionPointVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IConnectionPoint*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IConnectionPoint*);  /* (R1) */
    ULONG (WINAPI *Release)(IConnectionPoint*);  /* (R1) */
    /* IConnectionPoint */
    HRESULT (WINAPI *GetConnectionInterface)(IConnectionPoint*, IID* pIID);  /* 887287 */
    HRESULT (WINAPI *GetConnectionPointContainer)(IConnectionPoint*, IConnectionPointContainer** ppCPC);  /* 887288 */
    HRESULT (WINAPI *Advise)(IConnectionPoint*, IUnknown* pUnk, DWORD* pdwCookie);  /* 887281 */
    HRESULT (WINAPI *Unadvise)(IConnectionPoint*, DWORD dwCookie);  /* 887290 */
    HRESULT (WINAPI *EnumConnections)(IConnectionPoint*, IEnumConnections** ppEnum);  /* 887286 */
} IConnectionPointVtbl;
struct IConnectionPoint { const IConnectionPointVtbl *lpVtbl; };
#define IConnectionPoint_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IConnectionPoint_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IConnectionPoint_Release(T) ((T)->lpVtbl->Release(T))
#define IConnectionPoint_GetConnectionInterface(T,a) ((T)->lpVtbl->GetConnectionInterface(T,a))
#define IConnectionPoint_GetConnectionPointContainer(T,a) ((T)->lpVtbl->GetConnectionPointContainer(T,a))
#define IConnectionPoint_Advise(T,a,b) ((T)->lpVtbl->Advise(T,a,b))
#define IConnectionPoint_Unadvise(T,a) ((T)->lpVtbl->Unadvise(T,a))
#define IConnectionPoint_EnumConnections(T,a) ((T)->lpVtbl->EnumConnections(T,a))

/* ---- IConnectionPointContainer: 2 documented method pages; order R1 ---- */
typedef struct IConnectionPointContainerVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IConnectionPointContainer*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IConnectionPointContainer*);  /* (R1) */
    ULONG (WINAPI *Release)(IConnectionPointContainer*);  /* (R1) */
    /* IConnectionPointContainer */
    HRESULT (WINAPI *EnumConnectionPoints)(IConnectionPointContainer*, IEnumConnectionPoints** ppEnum);  /* 887283 */
    HRESULT (WINAPI *FindConnectionPoint)(IConnectionPointContainer*, REFIID riid, IConnectionPoint** ppCP);  /* 887284 */
} IConnectionPointContainerVtbl;
struct IConnectionPointContainer { const IConnectionPointContainerVtbl *lpVtbl; };
#define IConnectionPointContainer_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IConnectionPointContainer_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IConnectionPointContainer_Release(T) ((T)->lpVtbl->Release(T))
#define IConnectionPointContainer_EnumConnectionPoints(T,a) ((T)->lpVtbl->EnumConnectionPoints(T,a))
#define IConnectionPointContainer_FindConnectionPoint(T,a,b) ((T)->lpVtbl->FindConnectionPoint(T,a,b))

/* ---- ICreateErrorInfo: 5 documented method pages; order R1 ---- */
typedef struct ICreateErrorInfoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ICreateErrorInfo*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ICreateErrorInfo*);  /* (R1) */
    ULONG (WINAPI *Release)(ICreateErrorInfo*);  /* (R1) */
    /* ICreateErrorInfo */
    HRESULT (WINAPI *SetGUID)(ICreateErrorInfo*, REFGUID rguid);  /* 887296 */
    HRESULT (WINAPI *SetSource)(ICreateErrorInfo*, LPCOLESTR szSource);  /* 887299 */
    HRESULT (WINAPI *SetDescription)(ICreateErrorInfo*, LPCOLESTR* szDescription);  /* 887295 */
    HRESULT (WINAPI *SetHelpFile)(ICreateErrorInfo*, LPCOLESTR szHelpFile);  /* 887298 */
    HRESULT (WINAPI *SetHelpContext)(ICreateErrorInfo*, DWORD dwHelpContext);  /* 887297 */
} ICreateErrorInfoVtbl;
struct ICreateErrorInfo { const ICreateErrorInfoVtbl *lpVtbl; };
#define ICreateErrorInfo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ICreateErrorInfo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ICreateErrorInfo_Release(T) ((T)->lpVtbl->Release(T))
#define ICreateErrorInfo_SetGUID(T,a) ((T)->lpVtbl->SetGUID(T,a))
#define ICreateErrorInfo_SetSource(T,a) ((T)->lpVtbl->SetSource(T,a))
#define ICreateErrorInfo_SetDescription(T,a) ((T)->lpVtbl->SetDescription(T,a))
#define ICreateErrorInfo_SetHelpFile(T,a) ((T)->lpVtbl->SetHelpFile(T,a))
#define ICreateErrorInfo_SetHelpContext(T,a) ((T)->lpVtbl->SetHelpContext(T,a))

/* ---- IDataObject: 9 documented method pages; order R1 ---- */
typedef struct IDataObjectVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IDataObject*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IDataObject*);  /* (R1) */
    ULONG (WINAPI *Release)(IDataObject*);  /* (R1) */
    /* IDataObject */
    HRESULT (WINAPI *GetData)(IDataObject*, FORMATETC* pFormatetc, STGMEDIUM* pmedium);  /* 887358 */
    HRESULT (WINAPI *GetDataHere)(IDataObject*, FORMATETC* pFormatetc, STGMEDIUM* pmedium);  /* 887359 */
    HRESULT (WINAPI *QueryGetData)(IDataObject*, FORMATETC* pFormatetc);  /* 887360 */
    HRESULT (WINAPI *GetCanonicalFormatEtc)(IDataObject*, FORMATETC* pFormatetcIn, FORMATETC* pFormatetcOut);  /* 887357 */
    HRESULT (WINAPI *SetData)(IDataObject*, FORMATETC* pFormatetc, STGMEDIUM* pmedium, BOOL fRelease);  /* 887361 */
    HRESULT (WINAPI *EnumFormatEtc)(IDataObject*, DWORD dwDirection, IEnumFORMATETC** ppenumFormatetc);  /* 887356 */
    HRESULT (WINAPI *DAdvise)(IDataObject*, FORMATETC* pFormatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection);  /* 887353 */
    HRESULT (WINAPI *DUnadvise)(IDataObject*, DWORD dwConnection);  /* 887354 */
    HRESULT (WINAPI *EnumDAdvise)(IDataObject*, IEnumSTATDATA** ppenumAdvise);  /* 887355 */
} IDataObjectVtbl;
struct IDataObject { const IDataObjectVtbl *lpVtbl; };
#define IDataObject_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IDataObject_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IDataObject_Release(T) ((T)->lpVtbl->Release(T))
#define IDataObject_GetData(T,a,b) ((T)->lpVtbl->GetData(T,a,b))
#define IDataObject_GetDataHere(T,a,b) ((T)->lpVtbl->GetDataHere(T,a,b))
#define IDataObject_QueryGetData(T,a) ((T)->lpVtbl->QueryGetData(T,a))
#define IDataObject_GetCanonicalFormatEtc(T,a,b) ((T)->lpVtbl->GetCanonicalFormatEtc(T,a,b))
#define IDataObject_SetData(T,a,b,c) ((T)->lpVtbl->SetData(T,a,b,c))
#define IDataObject_EnumFormatEtc(T,a,b) ((T)->lpVtbl->EnumFormatEtc(T,a,b))
#define IDataObject_DAdvise(T,a,b,c,d) ((T)->lpVtbl->DAdvise(T,a,b,c,d))
#define IDataObject_DUnadvise(T,a) ((T)->lpVtbl->DUnadvise(T,a))
#define IDataObject_EnumDAdvise(T,a) ((T)->lpVtbl->EnumDAdvise(T,a))

/* ---- IDispatch: 3 documented method pages; order R1 ---- */
typedef struct IDispatchVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IDispatch*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IDispatch*);  /* (R1) */
    ULONG (WINAPI *Release)(IDispatch*);  /* (R1) */
    /* IDispatch */
    HRESULT (WINAPI *GetTypeInfoCount)(IDispatch*, unsigned int* pctinfo);  /* 887723 */
    HRESULT (WINAPI *GetTypeInfo)(IDispatch*, unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo);  /* 887722 */
    HRESULT (WINAPI *GetIDsOfNames)(IDispatch*, REFIID riid, OLECHAR** rgszNames, unsigned int cNames, LCID lcid, DISPID* rgDispId);  /* 887721 */
    HRESULT (WINAPI *Invoke)(IDispatch*, DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);  /* (R1) */
} IDispatchVtbl;
struct IDispatch { const IDispatchVtbl *lpVtbl; };
#define IDispatch_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IDispatch_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IDispatch_Release(T) ((T)->lpVtbl->Release(T))
#define IDispatch_GetTypeInfoCount(T,a) ((T)->lpVtbl->GetTypeInfoCount(T,a))
#define IDispatch_GetTypeInfo(T,a,b,c) ((T)->lpVtbl->GetTypeInfo(T,a,b,c))
#define IDispatch_GetIDsOfNames(T,a,b,c,d,e) ((T)->lpVtbl->GetIDsOfNames(T,a,b,c,d,e))
#define IDispatch_Invoke(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->Invoke(T,a,b,c,d,e,f,g,h))

/* ---- IEnumConnectionPoints: 4 documented method pages; order R1 ---- */
typedef struct IEnumConnectionPointsVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumConnectionPoints*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumConnectionPoints*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumConnectionPoints*);  /* (R1) */
    /* IEnumConnectionPoints */
    HRESULT (WINAPI *Next)(IEnumConnectionPoints*, ULONG cConnections, IConnectionPoint** rgpcn, ULONG* pcFetched);  /* 887729 */
    HRESULT (WINAPI *Skip)(IEnumConnectionPoints*, ULONG cConnections);  /* 887731 */
    HRESULT (WINAPI *Reset)(IEnumConnectionPoints*);  /* 887730 */
    HRESULT (WINAPI *Clone)(IEnumConnectionPoints*, IEnumConnectionPoints** ppEnum);  /* 887727 */
} IEnumConnectionPointsVtbl;
struct IEnumConnectionPoints { const IEnumConnectionPointsVtbl *lpVtbl; };
#define IEnumConnectionPoints_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumConnectionPoints_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumConnectionPoints_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumConnectionPoints_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumConnectionPoints_Skip(T,a) ((T)->lpVtbl->Skip(T,a))
#define IEnumConnectionPoints_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumConnectionPoints_Clone(T,a) ((T)->lpVtbl->Clone(T,a))

/* ---- IEnumConnections: 4 documented method pages; order R1 ---- */
typedef struct IEnumConnectionsVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumConnections*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumConnections*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumConnections*);  /* (R1) */
    /* IEnumConnections */
    HRESULT (WINAPI *Next)(IEnumConnections*, ULONG cConnections, CONNECTDATA** rgpcd, ULONG* pcFetched);  /* 887734 */
    HRESULT (WINAPI *Skip)(IEnumConnections*, ULONG cConnections);  /* 887736 */
    HRESULT (WINAPI *Reset)(IEnumConnections*);  /* 887735 */
    HRESULT (WINAPI *Clone)(IEnumConnections*, IEnumConnectionPoints** ppEnum);  /* 887732 */
} IEnumConnectionsVtbl;
struct IEnumConnections { const IEnumConnectionsVtbl *lpVtbl; };
#define IEnumConnections_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumConnections_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumConnections_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumConnections_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumConnections_Skip(T,a) ((T)->lpVtbl->Skip(T,a))
#define IEnumConnections_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumConnections_Clone(T,a) ((T)->lpVtbl->Clone(T,a))

/* ---- IEnumVARIANT: 4 documented method pages; order R1 ---- */
typedef struct IEnumVARIANTVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumVARIANT*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumVARIANT*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumVARIANT*);  /* (R1) */
    /* IEnumVARIANT */
    HRESULT (WINAPI *Next)(IEnumVARIANT*, unsigned long celt, VARIANT* rgVar, unsigned long* pCeltFetched);  /* 887765 */
    HRESULT (WINAPI *Skip)(IEnumVARIANT*, unsigned long celt);  /* 887767 */
    HRESULT (WINAPI *Reset)(IEnumVARIANT*);  /* 887766 */
    HRESULT (WINAPI *Clone)(IEnumVARIANT*, IEnumVARIANT** ppEnum);  /* 887763 */
} IEnumVARIANTVtbl;
struct IEnumVARIANT { const IEnumVARIANTVtbl *lpVtbl; };
#define IEnumVARIANT_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumVARIANT_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumVARIANT_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumVARIANT_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumVARIANT_Skip(T,a) ((T)->lpVtbl->Skip(T,a))
#define IEnumVARIANT_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumVARIANT_Clone(T,a) ((T)->lpVtbl->Clone(T,a))

/* ---- IErrorInfo: 5 documented method pages; order R1 ---- */
typedef struct IErrorInfoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IErrorInfo*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IErrorInfo*);  /* (R1) */
    ULONG (WINAPI *Release)(IErrorInfo*);  /* (R1) */
    /* IErrorInfo */
    HRESULT (WINAPI *GetGUID)(IErrorInfo*, GUID* pGUID);  /* 887769 */
    HRESULT (WINAPI *GetSource)(IErrorInfo*, BSTR* pBstrSource);  /* 887782 */
    HRESULT (WINAPI *GetDescription)(IErrorInfo*, BSTR* pBstrDescription);  /* 887768 */
    HRESULT (WINAPI *GetHelpFile)(IErrorInfo*, BSTR* pBstrHelpFile);  /* 887781 */
    HRESULT (WINAPI *GetHelpContext)(IErrorInfo*, DWORD* pdwHelpContext);  /* 887780 */
} IErrorInfoVtbl;
struct IErrorInfo { const IErrorInfoVtbl *lpVtbl; };
#define IErrorInfo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IErrorInfo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IErrorInfo_Release(T) ((T)->lpVtbl->Release(T))
#define IErrorInfo_GetGUID(T,a) ((T)->lpVtbl->GetGUID(T,a))
#define IErrorInfo_GetSource(T,a) ((T)->lpVtbl->GetSource(T,a))
#define IErrorInfo_GetDescription(T,a) ((T)->lpVtbl->GetDescription(T,a))
#define IErrorInfo_GetHelpFile(T,a) ((T)->lpVtbl->GetHelpFile(T,a))
#define IErrorInfo_GetHelpContext(T,a) ((T)->lpVtbl->GetHelpContext(T,a))

/* ---- IExternalConnection: 2 documented method pages; order R1 ---- */
typedef struct IExternalConnectionVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IExternalConnection*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IExternalConnection*);  /* (R1) */
    ULONG (WINAPI *Release)(IExternalConnection*);  /* (R1) */
    /* IExternalConnection */
    HRESULT (WINAPI *AddConnection)(IExternalConnection*, DWORD exconn, DWORD dwreserved);  /* 887785 */
    HRESULT (WINAPI *ReleaseConnection)(IExternalConnection*, DWORD extconn, DWORD dwreserved, BOOL fLastReleaseCloses);  /* 887786 */
} IExternalConnectionVtbl;
struct IExternalConnection { const IExternalConnectionVtbl *lpVtbl; };
#define IExternalConnection_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IExternalConnection_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IExternalConnection_Release(T) ((T)->lpVtbl->Release(T))
#define IExternalConnection_AddConnection(T,a,b) ((T)->lpVtbl->AddConnection(T,a,b))
#define IExternalConnection_ReleaseConnection(T,a,b,c) ((T)->lpVtbl->ReleaseConnection(T,a,b,c))

/* ---- IFillLockBytes: 4 documented method pages; order R1 ---- */
typedef struct IFillLockBytesVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IFillLockBytes*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IFillLockBytes*);  /* (R1) */
    ULONG (WINAPI *Release)(IFillLockBytes*);  /* (R1) */
    /* IFillLockBytes */
    HRESULT (WINAPI *FillAppend)(IFillLockBytes*, void const* pv, ULONG cb, ULONG* pcbWritten);  /* 887788 */
    HRESULT (WINAPI *FillAt)(IFillLockBytes*, ULARGE_INTEGER uIOffset, void const* pv, ULONG cb, ULONG* pcbWritten);  /* 887789 */
    HRESULT (WINAPI *SetFillSize)(IFillLockBytes*, ULARGE_INTEGER uISize);  /* 887791 */
    HRESULT (WINAPI *Terminate)(IFillLockBytes*, BOOL bCanceled);  /* 887792 */
} IFillLockBytesVtbl;
struct IFillLockBytes { const IFillLockBytesVtbl *lpVtbl; };
#define IFillLockBytes_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IFillLockBytes_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IFillLockBytes_Release(T) ((T)->lpVtbl->Release(T))
#define IFillLockBytes_FillAppend(T,a,b,c) ((T)->lpVtbl->FillAppend(T,a,b,c))
#define IFillLockBytes_FillAt(T,a,b,c,d) ((T)->lpVtbl->FillAt(T,a,b,c,d))
#define IFillLockBytes_SetFillSize(T,a) ((T)->lpVtbl->SetFillSize(T,a))
#define IFillLockBytes_Terminate(T,a) ((T)->lpVtbl->Terminate(T,a))

/* ---- IGlobalInterfaceTable: 3 documented method pages; order R1 ---- */
typedef struct IGlobalInterfaceTableVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IGlobalInterfaceTable*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IGlobalInterfaceTable*);  /* (R1) */
    ULONG (WINAPI *Release)(IGlobalInterfaceTable*);  /* (R1) */
    /* IGlobalInterfaceTable */
    HRESULT (WINAPI *RegisterInterfaceInGlobal)(IGlobalInterfaceTable*, IUnknown* pUnk, REFIID riid, DWORD* pdwCookie);  /* 887795 */
    HRESULT (WINAPI *RevokeInterfaceFromGlobal)(IGlobalInterfaceTable*, DWORD dwCookie);  /* 887796 */
    HRESULT (WINAPI *GetInterfaceFromGlobal)(IGlobalInterfaceTable*, DWORD dwCookie, REFIID riid, void** ppv);  /* 887794 */
} IGlobalInterfaceTableVtbl;
struct IGlobalInterfaceTable { const IGlobalInterfaceTableVtbl *lpVtbl; };
#define IGlobalInterfaceTable_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IGlobalInterfaceTable_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IGlobalInterfaceTable_Release(T) ((T)->lpVtbl->Release(T))
#define IGlobalInterfaceTable_RegisterInterfaceInGlobal(T,a,b,c) ((T)->lpVtbl->RegisterInterfaceInGlobal(T,a,b,c))
#define IGlobalInterfaceTable_RevokeInterfaceFromGlobal(T,a) ((T)->lpVtbl->RevokeInterfaceFromGlobal(T,a))
#define IGlobalInterfaceTable_GetInterfaceFromGlobal(T,a,b,c) ((T)->lpVtbl->GetInterfaceFromGlobal(T,a,b,c))

/* ---- ILockBytes: 7 documented method pages; order R1 ---- */
typedef struct ILockBytesVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ILockBytes*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ILockBytes*);  /* (R1) */
    ULONG (WINAPI *Release)(ILockBytes*);  /* (R1) */
    /* ILockBytes */
    HRESULT (WINAPI *ReadAt)(ILockBytes*, ULARGE_INTEGER ulOffset, void* pv, ULONG cb, ULONG* pcbRead);  /* 887801 */
    HRESULT (WINAPI *WriteAt)(ILockBytes*, ULARGE_INTEGER ulOffset, void const* pv, ULONG cb, ULONG* pcbWritten);  /* 887805 */
    HRESULT (WINAPI *Flush)(ILockBytes*);  /* 887798 */
    HRESULT (WINAPI *SetSize)(ILockBytes*, ULARGE_INTEGER cb);  /* 887802 */
    HRESULT (WINAPI *LockRegion)(ILockBytes*, ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);  /* 887800 */
    HRESULT (WINAPI *UnlockRegion)(ILockBytes*, ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);  /* 887804 */
    HRESULT (WINAPI *Stat)(ILockBytes*, STATSTG* pstatstg, DWORD grfStatFlag);  /* 887803 */
} ILockBytesVtbl;
struct ILockBytes { const ILockBytesVtbl *lpVtbl; };
#define ILockBytes_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ILockBytes_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ILockBytes_Release(T) ((T)->lpVtbl->Release(T))
#define ILockBytes_ReadAt(T,a,b,c,d) ((T)->lpVtbl->ReadAt(T,a,b,c,d))
#define ILockBytes_WriteAt(T,a,b,c,d) ((T)->lpVtbl->WriteAt(T,a,b,c,d))
#define ILockBytes_Flush(T) ((T)->lpVtbl->Flush(T))
#define ILockBytes_SetSize(T,a) ((T)->lpVtbl->SetSize(T,a))
#define ILockBytes_LockRegion(T,a,b,c) ((T)->lpVtbl->LockRegion(T,a,b,c))
#define ILockBytes_UnlockRegion(T,a,b,c) ((T)->lpVtbl->UnlockRegion(T,a,b,c))
#define ILockBytes_Stat(T,a,b) ((T)->lpVtbl->Stat(T,a,b))

/* ---- IMalloc: 4 documented method pages; order R1 ---- */
typedef struct IMallocVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMalloc*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMalloc*);  /* (R1) */
    ULONG (WINAPI *Release)(IMalloc*);  /* (R1) */
    /* IMalloc */
    void (WINAPI *Free)(IMalloc*, void* pv);  /* 887809 */
    ULONG (WINAPI *GetSize)(IMalloc*, void* pv);  /* 887810 */
    int (WINAPI *DidAlloc)(IMalloc*, void* pv);  /* 887808 */
    void (WINAPI *HeapMinimize)(IMalloc*);  /* 887811 */
} IMallocVtbl;
struct IMalloc { const IMallocVtbl *lpVtbl; };
#define IMalloc_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMalloc_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMalloc_Release(T) ((T)->lpVtbl->Release(T))
#define IMalloc_Free(T,a) ((T)->lpVtbl->Free(T,a))
#define IMalloc_GetSize(T,a) ((T)->lpVtbl->GetSize(T,a))
#define IMalloc_DidAlloc(T,a) ((T)->lpVtbl->DidAlloc(T,a))
#define IMalloc_HeapMinimize(T) ((T)->lpVtbl->HeapMinimize(T))

/* ---- IMallocSpy: 7 documented method pages; order R1 ---- */
typedef struct IMallocSpyVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMallocSpy*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMallocSpy*);  /* (R1) */
    ULONG (WINAPI *Release)(IMallocSpy*);  /* (R1) */
    /* IMallocSpy */
    ULONG (WINAPI *PreAlloc)(IMallocSpy*, ULONG cbRequest);  /* 887820 */
    void (WINAPI *PostFree)(IMallocSpy*, BOOL fSpyed);  /* 887816 */
    ULONG (WINAPI *PreRealloc)(IMallocSpy*, void* pRequest, ULONG cbRequest, void** ppNewRequest, BOOL fSpyed);  /* 887950 */
    ULONG (WINAPI *PostGetSize)(IMallocSpy*, ULONG cbActual, BOOL fSpyed);  /* 887817 */
    int (WINAPI *PostDidAlloc)(IMallocSpy*, void* pRequest, BOOL fSpyed, int fActual);  /* 887815 */
    void (WINAPI *PreHeapMinimize)(IMallocSpy*);  /* 887943 */
    void (WINAPI *PostHeapMinimize)(IMallocSpy*);  /* 887818 */
} IMallocSpyVtbl;
struct IMallocSpy { const IMallocSpyVtbl *lpVtbl; };
#define IMallocSpy_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMallocSpy_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMallocSpy_Release(T) ((T)->lpVtbl->Release(T))
#define IMallocSpy_PreAlloc(T,a) ((T)->lpVtbl->PreAlloc(T,a))
#define IMallocSpy_PostFree(T,a) ((T)->lpVtbl->PostFree(T,a))
#define IMallocSpy_PreRealloc(T,a,b,c,d) ((T)->lpVtbl->PreRealloc(T,a,b,c,d))
#define IMallocSpy_PostGetSize(T,a,b) ((T)->lpVtbl->PostGetSize(T,a,b))
#define IMallocSpy_PostDidAlloc(T,a,b,c) ((T)->lpVtbl->PostDidAlloc(T,a,b,c))
#define IMallocSpy_PreHeapMinimize(T) ((T)->lpVtbl->PreHeapMinimize(T))
#define IMallocSpy_PostHeapMinimize(T) ((T)->lpVtbl->PostHeapMinimize(T))

/* ---- IMarshal: 3 documented method pages; order R1 ---- */
typedef struct IMarshalVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMarshal*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMarshal*);  /* (R1) */
    ULONG (WINAPI *Release)(IMarshal*);  /* (R1) */
    /* IMarshal */
    HRESULT (WINAPI *GetUnmarshalClass)(IMarshal*, REFIID, VOID*, DWORD, VOID*, DWORD, CLSID*);  /* (R1) */
    HRESULT (WINAPI *GetMarshalSizeMax)(IMarshal*, REFIID, VOID*, DWORD, VOID*, PDWORD, ULONG*);  /* (R1) */
    HRESULT (WINAPI *MarshalInterface)(IMarshal*, IStream*, REFIID, VOID*, DWORD, VOID*, DWORD);  /* (R1) */
    HRESULT (WINAPI *UnmarshalInterface)(IMarshal*, IStream* pStm, REFIID riid, void** ppv);  /* 889306 */
    HRESULT (WINAPI *ReleaseMarshalData)(IMarshal*, IStream* pStm);  /* 889299 */
    HRESULT (WINAPI *DisconnectObject)(IMarshal*, DWORD dwReserved);  /* 887969 */
} IMarshalVtbl;
struct IMarshal { const IMarshalVtbl *lpVtbl; };
#define IMarshal_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMarshal_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMarshal_Release(T) ((T)->lpVtbl->Release(T))
#define IMarshal_GetUnmarshalClass(T,a,b,c,d,e,f) ((T)->lpVtbl->GetUnmarshalClass(T,a,b,c,d,e,f))
#define IMarshal_GetMarshalSizeMax(T,a,b,c,d,e,f) ((T)->lpVtbl->GetMarshalSizeMax(T,a,b,c,d,e,f))
#define IMarshal_MarshalInterface(T,a,b,c,d,e,f) ((T)->lpVtbl->MarshalInterface(T,a,b,c,d,e,f))
#define IMarshal_UnmarshalInterface(T,a,b,c) ((T)->lpVtbl->UnmarshalInterface(T,a,b,c))
#define IMarshal_ReleaseMarshalData(T,a) ((T)->lpVtbl->ReleaseMarshalData(T,a))
#define IMarshal_DisconnectObject(T,a) ((T)->lpVtbl->DisconnectObject(T,a))

/* ---- IMessageFilter: 2 documented method pages; order R1 ---- */
typedef struct IMessageFilterVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMessageFilter*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMessageFilter*);  /* (R1) */
    ULONG (WINAPI *Release)(IMessageFilter*);  /* (R1) */
    /* IMessageFilter */
    DWORD (WINAPI *HandleInComingCall)(IMessageFilter*, DWORD, HTASK, DWORD, LPINTERFACEINFO);  /* (R1) */
    DWORD (WINAPI *RetryRejectedCall)(IMessageFilter*, HTASK threadIDCallee, DWORD dwTickCount, DWORD dwRejectType);  /* 889311 */
    DWORD (WINAPI *MessagePending)(IMessageFilter*, HTASK threadIDCallee, DWORD dwTickCount, DWORD dwPendingType);  /* 889310 */
} IMessageFilterVtbl;
struct IMessageFilter { const IMessageFilterVtbl *lpVtbl; };
#define IMessageFilter_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMessageFilter_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMessageFilter_Release(T) ((T)->lpVtbl->Release(T))
#define IMessageFilter_HandleInComingCall(T,a,b,c,d) ((T)->lpVtbl->HandleInComingCall(T,a,b,c,d))
#define IMessageFilter_RetryRejectedCall(T,a,b,c) ((T)->lpVtbl->RetryRejectedCall(T,a,b,c))
#define IMessageFilter_MessagePending(T,a,b,c) ((T)->lpVtbl->MessagePending(T,a,b,c))

/* ---- IMoniker: 14 documented method pages; order R1 ---- */
typedef struct IMonikerVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMoniker*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMoniker*);  /* (R1) */
    ULONG (WINAPI *Release)(IMoniker*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IMoniker*, LPCLSID);  /* (R1) */
    /* IPersistStream */
    HRESULT (WINAPI *IsDirty)(IMoniker*);  /* (R1) */
    HRESULT (WINAPI *Load)(IMoniker*, IStream*);  /* (R1) */
    HRESULT (WINAPI *Save)(IMoniker*, IStream*, BOOL);  /* (R1) */
    HRESULT (WINAPI *GetSizeMax)(IMoniker*, PULARGE_INTEGER);  /* (R1) */
    /* IMoniker */
    HRESULT (WINAPI *BindToObject)(IMoniker*, IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riidResult, void** ppvResult);  /* 889312 */
    HRESULT (WINAPI *BindToStorage)(IMoniker*, IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, void** ppvObj);  /* 889313 */
    HRESULT (WINAPI *Reduce)(IMoniker*, IBindCtx* pbc, DWORD dwReduceHowFar, IMoniker** ppmkToLeft, IMoniker** ppmkReduced);  /* 889327 */
    HRESULT (WINAPI *ComposeWith)(IMoniker*, IMoniker* pmkRight, BOOL fOnlyIfNotGeneric, IMoniker** ppmkComposite);  /* 889316 */
    HRESULT (WINAPI *Enum)(IMoniker*, BOOL fForward, IEnumMoniker** ppenumMoniker);  /* 889317 */
    HRESULT (WINAPI *IsEqual)(IMoniker*, IMoniker* pmkOtherMoniker);  /* 889322 */
    HRESULT (WINAPI *Hash)(IMoniker*, DWORD* pdwHash);  /* 889320 */
    HRESULT (WINAPI *IsRunning)(IMoniker*, IBindCtx* pbc, IMoniker* pmkToLeft, IMoniker* pmkNewlyRunning);  /* 889323 */
    HRESULT (WINAPI *GetTimeOfLastChange)(IMoniker*, IBindCtx* pbc, IMoniker* pmkToLeft, FILETIME* pFileTime);  /* 889319 */
    HRESULT (WINAPI *Inverse)(IMoniker*, IMoniker** ppmk);  /* 889321 */
    HRESULT (WINAPI *CommonPrefixWith)(IMoniker*, IMoniker* pmkOther, IMoniker** ppmkPrefix);  /* 889314 */
    HRESULT (WINAPI *RelativePathTo)(IMoniker*, IMoniker* pmkOther, IMoniker** ppmkRelPath);  /* 889328 */
    HRESULT (WINAPI *GetDisplayName)(IMoniker*, IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* ppszDisplayName);  /* 889318 */
    HRESULT (WINAPI *ParseDisplayName)(IMoniker*, IBindCtx*, IMoniker*, LPOLESTR, ULONG*, IMoniker**);  /* (R1) */
    HRESULT (WINAPI *IsSystemMoniker)(IMoniker*, DWORD* pdwMksys);  /* 889324 */
} IMonikerVtbl;
struct IMoniker { const IMonikerVtbl *lpVtbl; };
#define IMoniker_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMoniker_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMoniker_Release(T) ((T)->lpVtbl->Release(T))
#define IMoniker_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IMoniker_IsDirty(T) ((T)->lpVtbl->IsDirty(T))
#define IMoniker_Load(T,a) ((T)->lpVtbl->Load(T,a))
#define IMoniker_Save(T,a,b) ((T)->lpVtbl->Save(T,a,b))
#define IMoniker_GetSizeMax(T,a) ((T)->lpVtbl->GetSizeMax(T,a))
#define IMoniker_BindToObject(T,a,b,c,d) ((T)->lpVtbl->BindToObject(T,a,b,c,d))
#define IMoniker_BindToStorage(T,a,b,c,d) ((T)->lpVtbl->BindToStorage(T,a,b,c,d))
#define IMoniker_Reduce(T,a,b,c,d) ((T)->lpVtbl->Reduce(T,a,b,c,d))
#define IMoniker_ComposeWith(T,a,b,c) ((T)->lpVtbl->ComposeWith(T,a,b,c))
#define IMoniker_Enum(T,a,b) ((T)->lpVtbl->Enum(T,a,b))
#define IMoniker_IsEqual(T,a) ((T)->lpVtbl->IsEqual(T,a))
#define IMoniker_Hash(T,a) ((T)->lpVtbl->Hash(T,a))
#define IMoniker_IsRunning(T,a,b,c) ((T)->lpVtbl->IsRunning(T,a,b,c))
#define IMoniker_GetTimeOfLastChange(T,a,b,c) ((T)->lpVtbl->GetTimeOfLastChange(T,a,b,c))
#define IMoniker_Inverse(T,a) ((T)->lpVtbl->Inverse(T,a))
#define IMoniker_CommonPrefixWith(T,a,b) ((T)->lpVtbl->CommonPrefixWith(T,a,b))
#define IMoniker_RelativePathTo(T,a,b) ((T)->lpVtbl->RelativePathTo(T,a,b))
#define IMoniker_GetDisplayName(T,a,b,c) ((T)->lpVtbl->GetDisplayName(T,a,b,c))
#define IMoniker_ParseDisplayName(T,a,b,c,d,e) ((T)->lpVtbl->ParseDisplayName(T,a,b,c,d,e))
#define IMoniker_IsSystemMoniker(T,a) ((T)->lpVtbl->IsSystemMoniker(T,a))

/* ---- IOleItemContainer: 3 documented method pages; order R1 ---- */
typedef struct IOleItemContainerVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleItemContainer*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleItemContainer*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleItemContainer*);  /* (R1) */
    /* IParseDisplayName */
    HRESULT (WINAPI *ParseDisplayName)(IOleItemContainer*, IBindCtx*, LPOLESTR, ULONG*, IMoniker**);  /* (R1) */
    /* IOleContainer */
    HRESULT (WINAPI *EnumObjects)(IOleItemContainer*, DWORD, IEnumUnknown**);  /* (R1) */
    HRESULT (WINAPI *LockContainer)(IOleItemContainer*, BOOL);  /* (R1) */
    /* IOleItemContainer */
    HRESULT (WINAPI *GetObject)(IOleItemContainer*, LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx* pbc, REFIID riid, void** ppvObject);  /* 889355 */
    HRESULT (WINAPI *GetObjectStorage)(IOleItemContainer*, LPOLESTR pszItem, IBindCtx* pbc, REFIID riid, void** ppvStorage);  /* 889356 */
    HRESULT (WINAPI *IsRunning)(IOleItemContainer*, LPOLESTR pszItem);  /* 889357 */
} IOleItemContainerVtbl;
struct IOleItemContainer { const IOleItemContainerVtbl *lpVtbl; };
#define IOleItemContainer_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleItemContainer_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleItemContainer_Release(T) ((T)->lpVtbl->Release(T))
#define IOleItemContainer_ParseDisplayName(T,a,b,c,d) ((T)->lpVtbl->ParseDisplayName(T,a,b,c,d))
#define IOleItemContainer_EnumObjects(T,a,b) ((T)->lpVtbl->EnumObjects(T,a,b))
#define IOleItemContainer_LockContainer(T,a) ((T)->lpVtbl->LockContainer(T,a))
#define IOleItemContainer_GetObject(T,a,b,c,d,e) ((T)->lpVtbl->GetObject(T,a,b,c,d,e))
#define IOleItemContainer_GetObjectStorage(T,a,b,c,d) ((T)->lpVtbl->GetObjectStorage(T,a,b,c,d))
#define IOleItemContainer_IsRunning(T,a) ((T)->lpVtbl->IsRunning(T,a))

/* ---- IPersistFile: 2 documented method pages; order R1 ---- */
typedef struct IPersistFileVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistFile*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistFile*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistFile*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistFile*, CLSID*);  /* (R1) */
    /* IPersistFile */
    HRESULT (WINAPI *IsDirty)(IPersistFile*);  /* 889395 */
    HRESULT (WINAPI *Load)(IPersistFile*, LPCOLESTR, DWORD);  /* (R1) */
    HRESULT (WINAPI *Save)(IPersistFile*, LPCOLESTR, BOOL);  /* (R1) */
    HRESULT (WINAPI *SaveCompleted)(IPersistFile*, LPCOLESTR);  /* (R1) */
    HRESULT (WINAPI *GetCurFile)(IPersistFile*, LPOLESTR* ppszFileName);  /* 889394 */
} IPersistFileVtbl;
struct IPersistFile { const IPersistFileVtbl *lpVtbl; };
#define IPersistFile_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistFile_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistFile_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistFile_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistFile_IsDirty(T) ((T)->lpVtbl->IsDirty(T))
#define IPersistFile_Load(T,a,b) ((T)->lpVtbl->Load(T,a,b))
#define IPersistFile_Save(T,a,b) ((T)->lpVtbl->Save(T,a,b))
#define IPersistFile_SaveCompleted(T,a) ((T)->lpVtbl->SaveCompleted(T,a))
#define IPersistFile_GetCurFile(T,a) ((T)->lpVtbl->GetCurFile(T,a))

/* ---- IPersistPropertyBag: 3 documented method pages; order R1 ---- */
typedef struct IPersistPropertyBagVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistPropertyBag*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistPropertyBag*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistPropertyBag*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistPropertyBag*, LPCLSID);  /* (R1) */
    /* IPersistPropertyBag */
    HRESULT (WINAPI *InitNew)(IPersistPropertyBag*);  /* 886021 */
    HRESULT (WINAPI *Load)(IPersistPropertyBag*, IPropertyBag* pPropBag, IErrorlog* pErrorLog);  /* 886038 */
    HRESULT (WINAPI *Save)(IPersistPropertyBag*, IPropertyBag* pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties);  /* 886047 */
} IPersistPropertyBagVtbl;
struct IPersistPropertyBag { const IPersistPropertyBagVtbl *lpVtbl; };
#define IPersistPropertyBag_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistPropertyBag_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistPropertyBag_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistPropertyBag_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistPropertyBag_InitNew(T) ((T)->lpVtbl->InitNew(T))
#define IPersistPropertyBag_Load(T,a,b) ((T)->lpVtbl->Load(T,a,b))
#define IPersistPropertyBag_Save(T,a,b,c) ((T)->lpVtbl->Save(T,a,b,c))

/* ---- IPropertyBag: 2 documented method pages; order R1 ---- */
typedef struct IPropertyBagVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPropertyBag*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPropertyBag*);  /* (R1) */
    ULONG (WINAPI *Release)(IPropertyBag*);  /* (R1) */
    /* IPropertyBag */
    HRESULT (WINAPI *Read)(IPropertyBag*, LPCOLESTR pszPropName, VARIANT* pVar, IErrorlog* pErrorLog);  /* 886063 */
    HRESULT (WINAPI *Write)(IPropertyBag*, LPCOLESTR pszPropName, VARIANT* pVar);  /* 886069 */
} IPropertyBagVtbl;
struct IPropertyBag { const IPropertyBagVtbl *lpVtbl; };
#define IPropertyBag_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPropertyBag_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPropertyBag_Release(T) ((T)->lpVtbl->Release(T))
#define IPropertyBag_Read(T,a,b,c) ((T)->lpVtbl->Read(T,a,b,c))
#define IPropertyBag_Write(T,a,b) ((T)->lpVtbl->Write(T,a,b))

/* ---- ITypeInfo: 16 documented method pages; order R1 ---- */
typedef struct ITypeInfoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ITypeInfo*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ITypeInfo*);  /* (R1) */
    ULONG (WINAPI *Release)(ITypeInfo*);  /* (R1) */
    /* ITypeInfo */
    HRESULT (WINAPI *GetTypeAttr)(ITypeInfo*, TYPEATTR** ppTypeAttr);  /* 890537 */
    HRESULT (WINAPI *GetTypeComp)(ITypeInfo*, ITypeComp** ppTComp);  /* 890541 */
    HRESULT (WINAPI *GetFuncDesc)(ITypeInfo*, unsigned int index, FUNCDESC** ppFuncDesc);  /* 890506 */
    HRESULT (WINAPI *GetVarDesc)(ITypeInfo*, unsigned int index, VARDESC** ppVarDesc);  /* 890548 */
    HRESULT (WINAPI *GetNames)(ITypeInfo*, MEMBERID memid, BSTR* rgBstrNames, unsigned int cMaxNames, unsigned int* pcNames);  /* 890524 */
    HRESULT (WINAPI *GetRefTypeOfImplType)(ITypeInfo*, unsigned int index, HREFTYPE* pRefType);  /* 890533 */
    HRESULT (WINAPI *GetImplTypeFlags)(ITypeInfo*, unsigned int index, int* pImplTypeFlags);  /* 890517 */
    HRESULT (WINAPI *GetIDsOfNames)(ITypeInfo*, OLECHAR** rgszNames, unsigned int cNames, MEMBERID* pMemId);  /* 890510 */
    HRESULT (WINAPI *Invoke)(ITypeInfo*, VOID*, MEMBERID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);  /* (R1) */
    HRESULT (WINAPI *GetDocumentation)(ITypeInfo*, MEMBERID, BSTR*, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *GetDllEntry)(ITypeInfo*, MEMBERID, INVOKEKIND, BSTR*, BSTR*, WORD*);  /* (R1) */
    HRESULT (WINAPI *GetRefTypeInfo)(ITypeInfo*, HREFTYPE hRefType, ITypeInfo** ppTInfo);  /* 890529 */
    HRESULT (WINAPI *AddressOfMember)(ITypeInfo*, MEMBERID memid, INVOKEKIND invKind, VOID** ppv);  /* 890484 */
    HRESULT (WINAPI *CreateInstance)(ITypeInfo*, IUnknown* pUnkOuter, REFIID riid, VOID** ppvObj);  /* 890488 */
    HRESULT (WINAPI *GetMops)(ITypeInfo*, MEMBERID memid, BSTR* pBstrMops);  /* 890520 */
    HRESULT (WINAPI *GetContainingTypeLib)(ITypeInfo*, ITypeLib** ppTLib, unsigned int* pIndex);  /* 890493 */
    HRESULT (WINAPI *ReleaseTypeAttr)(ITypeInfo*, TYPEATTR* pTypeAttr);  /* 890570 */
    HRESULT (WINAPI *ReleaseFuncDesc)(ITypeInfo*, FUNCDESC* pFuncDesc);  /* 890564 */
    HRESULT (WINAPI *ReleaseVarDesc)(ITypeInfo*, VARDESC* pVarDesc);  /* 890575 */
} ITypeInfoVtbl;
struct ITypeInfo { const ITypeInfoVtbl *lpVtbl; };
#define ITypeInfo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ITypeInfo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ITypeInfo_Release(T) ((T)->lpVtbl->Release(T))
#define ITypeInfo_GetTypeAttr(T,a) ((T)->lpVtbl->GetTypeAttr(T,a))
#define ITypeInfo_GetTypeComp(T,a) ((T)->lpVtbl->GetTypeComp(T,a))
#define ITypeInfo_GetFuncDesc(T,a,b) ((T)->lpVtbl->GetFuncDesc(T,a,b))
#define ITypeInfo_GetVarDesc(T,a,b) ((T)->lpVtbl->GetVarDesc(T,a,b))
#define ITypeInfo_GetNames(T,a,b,c,d) ((T)->lpVtbl->GetNames(T,a,b,c,d))
#define ITypeInfo_GetRefTypeOfImplType(T,a,b) ((T)->lpVtbl->GetRefTypeOfImplType(T,a,b))
#define ITypeInfo_GetImplTypeFlags(T,a,b) ((T)->lpVtbl->GetImplTypeFlags(T,a,b))
#define ITypeInfo_GetIDsOfNames(T,a,b,c) ((T)->lpVtbl->GetIDsOfNames(T,a,b,c))
#define ITypeInfo_Invoke(T,a,b,c,d,e,f,g) ((T)->lpVtbl->Invoke(T,a,b,c,d,e,f,g))
#define ITypeInfo_GetDocumentation(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation(T,a,b,c,d,e))
#define ITypeInfo_GetDllEntry(T,a,b,c,d,e) ((T)->lpVtbl->GetDllEntry(T,a,b,c,d,e))
#define ITypeInfo_GetRefTypeInfo(T,a,b) ((T)->lpVtbl->GetRefTypeInfo(T,a,b))
#define ITypeInfo_AddressOfMember(T,a,b,c) ((T)->lpVtbl->AddressOfMember(T,a,b,c))
#define ITypeInfo_CreateInstance(T,a,b,c) ((T)->lpVtbl->CreateInstance(T,a,b,c))
#define ITypeInfo_GetMops(T,a,b) ((T)->lpVtbl->GetMops(T,a,b))
#define ITypeInfo_GetContainingTypeLib(T,a,b) ((T)->lpVtbl->GetContainingTypeLib(T,a,b))
#define ITypeInfo_ReleaseTypeAttr(T,a) ((T)->lpVtbl->ReleaseTypeAttr(T,a))
#define ITypeInfo_ReleaseFuncDesc(T,a) ((T)->lpVtbl->ReleaseFuncDesc(T,a))
#define ITypeInfo_ReleaseVarDesc(T,a) ((T)->lpVtbl->ReleaseVarDesc(T,a))

/* ---- ITypeInfo2: 13 documented method pages; order R1 ---- */
typedef struct ITypeInfo2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ITypeInfo2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ITypeInfo2*);  /* (R1) */
    ULONG (WINAPI *Release)(ITypeInfo2*);  /* (R1) */
    /* ITypeInfo */
    HRESULT (WINAPI *GetTypeAttr)(ITypeInfo2*, LPTYPEATTR*);  /* (R1) */
    HRESULT (WINAPI *GetTypeComp)(ITypeInfo2*, LPTYPECOMP*);  /* (R1) */
    HRESULT (WINAPI *GetFuncDesc)(ITypeInfo2*, UINT, LPFUNCDESC*);  /* (R1) */
    HRESULT (WINAPI *GetVarDesc)(ITypeInfo2*, UINT, LPVARDESC*);  /* (R1) */
    HRESULT (WINAPI *GetNames)(ITypeInfo2*, MEMBERID, BSTR*, UINT, UINT*);  /* (R1) */
    HRESULT (WINAPI *GetRefTypeOfImplType)(ITypeInfo2*, UINT, HREFTYPE*);  /* (R1) */
    HRESULT (WINAPI *GetImplTypeFlags)(ITypeInfo2*, UINT, INT*);  /* (R1) */
    HRESULT (WINAPI *GetIDsOfNames)(ITypeInfo2*, LPOLESTR*, UINT, MEMBERID*);  /* (R1) */
    HRESULT (WINAPI *Invoke)(ITypeInfo2*, VOID*, MEMBERID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);  /* (R1) */
    HRESULT (WINAPI *GetDocumentation)(ITypeInfo2*, MEMBERID, BSTR*, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *GetDllEntry)(ITypeInfo2*, MEMBERID, INVOKEKIND, BSTR*, BSTR*, WORD*);  /* (R1) */
    HRESULT (WINAPI *GetRefTypeInfo)(ITypeInfo2*, HREFTYPE, LPTYPEINFO*);  /* (R1) */
    HRESULT (WINAPI *AddressOfMember)(ITypeInfo2*, MEMBERID, INVOKEKIND, PVOID*);  /* (R1) */
    HRESULT (WINAPI *CreateInstance)(ITypeInfo2*, LPUNKNOWN, REFIID, PVOID*);  /* (R1) */
    HRESULT (WINAPI *GetMops)(ITypeInfo2*, MEMBERID, BSTR*);  /* (R1) */
    HRESULT (WINAPI *GetContainingTypeLib)(ITypeInfo2*, LPTYPELIB*, UINT*);  /* (R1) */
    void (WINAPI *ReleaseTypeAttr)(ITypeInfo2*, LPTYPEATTR);  /* (R1) */
    void (WINAPI *ReleaseFuncDesc)(ITypeInfo2*, LPFUNCDESC);  /* (R1) */
    void (WINAPI *ReleaseVarDesc)(ITypeInfo2*, LPVARDESC);  /* (R1) */
    /* ITypeInfo2 */
    HRESULT (WINAPI *GetTypeKind)(ITypeInfo2*, TYPEKIND* pTypeKind);  /* 890468 */
    HRESULT (WINAPI *GetTypeFlags)(ITypeInfo2*, unsigned long* pTypeFlags);  /* 890464 */
    HRESULT (WINAPI *GetFuncIndexOfMemId)(ITypeInfo2*, MEMBERID memid, INVOKEKIND invKind, unsigned int* pFuncIndex);  /* 890451 */
    HRESULT (WINAPI *GetVarIndexOfMemId)(ITypeInfo2*, MEMBERID memid, unsigned int* pVarIndex);  /* 890476 */
    HRESULT (WINAPI *GetCustData)(ITypeInfo2*, REFGUID guid, VARIANT* pVarVal);  /* 890431 */
    HRESULT (WINAPI *GetFuncCustData)(ITypeInfo2*, unsigned int index, REFGUID guid, VARIANT* pVarVal);  /* 890446 */
    HRESULT (WINAPI *GetParamCustData)(ITypeInfo2*, unsigned int indexFunc, unsigned int indexParam, REFGUID guid, VARIANT* pVarVal);  /* 890459 */
    HRESULT (WINAPI *GetVarCustData)(ITypeInfo2*, unsigned int index, REFGUID guid, VARIANT* pVarVal);  /* 890473 */
    HRESULT (WINAPI *GetImplTypeCustData)(ITypeInfo2*, unsigned int index, REFGUID guid, VARIANT* pVarVal);  /* 890455 */
    HRESULT (WINAPI *GetDocumentation2)(ITypeInfo2*, MEMBERID, LCID, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *GetAllCustData)(ITypeInfo2*, CUSTDATA*);  /* (R1) */
    HRESULT (WINAPI *GetAllFuncCustData)(ITypeInfo2*, unsigned int index, CUSTDATA* pCustData);  /* 890300 */
    HRESULT (WINAPI *GetAllParamCustData)(ITypeInfo2*, unsigned int indexFunc, unsigned int indexParam, CUSTDATA* pCustData);  /* 890417 */
    HRESULT (WINAPI *GetAllVarCustData)(ITypeInfo2*, unsigned int index, CUSTDATA* pCustData);  /* 890424 */
    HRESULT (WINAPI *GetAllImplTypeCustData)(ITypeInfo2*, unsigned int index, CUSTDATA* pCustData);  /* 890409 */
} ITypeInfo2Vtbl;
struct ITypeInfo2 { const ITypeInfo2Vtbl *lpVtbl; };
#define ITypeInfo2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ITypeInfo2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ITypeInfo2_Release(T) ((T)->lpVtbl->Release(T))
#define ITypeInfo2_GetTypeAttr(T,a) ((T)->lpVtbl->GetTypeAttr(T,a))
#define ITypeInfo2_GetTypeComp(T,a) ((T)->lpVtbl->GetTypeComp(T,a))
#define ITypeInfo2_GetFuncDesc(T,a,b) ((T)->lpVtbl->GetFuncDesc(T,a,b))
#define ITypeInfo2_GetVarDesc(T,a,b) ((T)->lpVtbl->GetVarDesc(T,a,b))
#define ITypeInfo2_GetNames(T,a,b,c,d) ((T)->lpVtbl->GetNames(T,a,b,c,d))
#define ITypeInfo2_GetRefTypeOfImplType(T,a,b) ((T)->lpVtbl->GetRefTypeOfImplType(T,a,b))
#define ITypeInfo2_GetImplTypeFlags(T,a,b) ((T)->lpVtbl->GetImplTypeFlags(T,a,b))
#define ITypeInfo2_GetIDsOfNames(T,a,b,c) ((T)->lpVtbl->GetIDsOfNames(T,a,b,c))
#define ITypeInfo2_Invoke(T,a,b,c,d,e,f,g) ((T)->lpVtbl->Invoke(T,a,b,c,d,e,f,g))
#define ITypeInfo2_GetDocumentation(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation(T,a,b,c,d,e))
#define ITypeInfo2_GetDllEntry(T,a,b,c,d,e) ((T)->lpVtbl->GetDllEntry(T,a,b,c,d,e))
#define ITypeInfo2_GetRefTypeInfo(T,a,b) ((T)->lpVtbl->GetRefTypeInfo(T,a,b))
#define ITypeInfo2_AddressOfMember(T,a,b,c) ((T)->lpVtbl->AddressOfMember(T,a,b,c))
#define ITypeInfo2_CreateInstance(T,a,b,c) ((T)->lpVtbl->CreateInstance(T,a,b,c))
#define ITypeInfo2_GetMops(T,a,b) ((T)->lpVtbl->GetMops(T,a,b))
#define ITypeInfo2_GetContainingTypeLib(T,a,b) ((T)->lpVtbl->GetContainingTypeLib(T,a,b))
#define ITypeInfo2_ReleaseTypeAttr(T,a) ((T)->lpVtbl->ReleaseTypeAttr(T,a))
#define ITypeInfo2_ReleaseFuncDesc(T,a) ((T)->lpVtbl->ReleaseFuncDesc(T,a))
#define ITypeInfo2_ReleaseVarDesc(T,a) ((T)->lpVtbl->ReleaseVarDesc(T,a))
#define ITypeInfo2_GetTypeKind(T,a) ((T)->lpVtbl->GetTypeKind(T,a))
#define ITypeInfo2_GetTypeFlags(T,a) ((T)->lpVtbl->GetTypeFlags(T,a))
#define ITypeInfo2_GetFuncIndexOfMemId(T,a,b,c) ((T)->lpVtbl->GetFuncIndexOfMemId(T,a,b,c))
#define ITypeInfo2_GetVarIndexOfMemId(T,a,b) ((T)->lpVtbl->GetVarIndexOfMemId(T,a,b))
#define ITypeInfo2_GetCustData(T,a,b) ((T)->lpVtbl->GetCustData(T,a,b))
#define ITypeInfo2_GetFuncCustData(T,a,b,c) ((T)->lpVtbl->GetFuncCustData(T,a,b,c))
#define ITypeInfo2_GetParamCustData(T,a,b,c,d) ((T)->lpVtbl->GetParamCustData(T,a,b,c,d))
#define ITypeInfo2_GetVarCustData(T,a,b,c) ((T)->lpVtbl->GetVarCustData(T,a,b,c))
#define ITypeInfo2_GetImplTypeCustData(T,a,b,c) ((T)->lpVtbl->GetImplTypeCustData(T,a,b,c))
#define ITypeInfo2_GetDocumentation2(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation2(T,a,b,c,d,e))
#define ITypeInfo2_GetAllCustData(T,a) ((T)->lpVtbl->GetAllCustData(T,a))
#define ITypeInfo2_GetAllFuncCustData(T,a,b) ((T)->lpVtbl->GetAllFuncCustData(T,a,b))
#define ITypeInfo2_GetAllParamCustData(T,a,b,c) ((T)->lpVtbl->GetAllParamCustData(T,a,b,c))
#define ITypeInfo2_GetAllVarCustData(T,a,b) ((T)->lpVtbl->GetAllVarCustData(T,a,b))
#define ITypeInfo2_GetAllImplTypeCustData(T,a,b) ((T)->lpVtbl->GetAllImplTypeCustData(T,a,b))

/* ---- ITypeLib: 8 documented method pages; order R1 ---- */
typedef struct ITypeLibVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ITypeLib*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ITypeLib*);  /* (R1) */
    ULONG (WINAPI *Release)(ITypeLib*);  /* (R1) */
    /* ITypeLib */
    HRESULT (WINAPI *GetTypeInfoCount)(ITypeLib*);  /* 890620 */
    HRESULT (WINAPI *GetTypeInfo)(ITypeLib*, unsigned int index, ITypeInfo** ppTInfo);  /* 890614 */
    HRESULT (WINAPI *GetTypeInfoType)(ITypeLib*, unsigned int index, TYPEKIND* pTKind);  /* 890632 */
    HRESULT (WINAPI *GetTypeInfoOfGuid)(ITypeLib*, REFGUID guid, ITypeInfo** ppTinfo);  /* 890629 */
    HRESULT (WINAPI *GetLibAttr)(ITypeLib*, TLIBATTR** ppTLibAttrr);  /* 890605 */
    HRESULT (WINAPI *GetTypeComp)(ITypeLib*, ITypeComp** ppTComp);  /* 890610 */
    HRESULT (WINAPI *GetDocumentation)(ITypeLib*, INT, BSTR*, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *IsName)(ITypeLib*, OLECHAR* szNameBuf, unsigned long lHashVal, BOOL pfName);  /* 890638 */
    HRESULT (WINAPI *FindName)(ITypeLib*, LPOLESTR, ULONG, ITypeInfo**, MEMBERID*, USHORT*);  /* (R1) */
    HRESULT (WINAPI *ReleaseTLibAttr)(ITypeLib*, TLIBATTR* pTLibAttr);  /* 890649 */
} ITypeLibVtbl;
struct ITypeLib { const ITypeLibVtbl *lpVtbl; };
#define ITypeLib_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ITypeLib_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ITypeLib_Release(T) ((T)->lpVtbl->Release(T))
#define ITypeLib_GetTypeInfoCount(T) ((T)->lpVtbl->GetTypeInfoCount(T))
#define ITypeLib_GetTypeInfo(T,a,b) ((T)->lpVtbl->GetTypeInfo(T,a,b))
#define ITypeLib_GetTypeInfoType(T,a,b) ((T)->lpVtbl->GetTypeInfoType(T,a,b))
#define ITypeLib_GetTypeInfoOfGuid(T,a,b) ((T)->lpVtbl->GetTypeInfoOfGuid(T,a,b))
#define ITypeLib_GetLibAttr(T,a) ((T)->lpVtbl->GetLibAttr(T,a))
#define ITypeLib_GetTypeComp(T,a) ((T)->lpVtbl->GetTypeComp(T,a))
#define ITypeLib_GetDocumentation(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation(T,a,b,c,d,e))
#define ITypeLib_IsName(T,a,b,c) ((T)->lpVtbl->IsName(T,a,b,c))
#define ITypeLib_FindName(T,a,b,c,d,e) ((T)->lpVtbl->FindName(T,a,b,c,d,e))
#define ITypeLib_ReleaseTLibAttr(T,a) ((T)->lpVtbl->ReleaseTLibAttr(T,a))

/* ---- ITypeLib2: 3 documented method pages; order R1 ---- */
typedef struct ITypeLib2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ITypeLib2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ITypeLib2*);  /* (R1) */
    ULONG (WINAPI *Release)(ITypeLib2*);  /* (R1) */
    /* ITypeLib */
    UINT (WINAPI *GetTypeInfoCount)(ITypeLib2*);  /* (R1) */
    HRESULT (WINAPI *GetTypeInfo)(ITypeLib2*, UINT, ITypeInfo**);  /* (R1) */
    HRESULT (WINAPI *GetTypeInfoType)(ITypeLib2*, UINT, TYPEKIND*);  /* (R1) */
    HRESULT (WINAPI *GetTypeInfoOfGuid)(ITypeLib2*, REFGUID, ITypeInfo**);  /* (R1) */
    HRESULT (WINAPI *GetLibAttr)(ITypeLib2*, TLIBATTR**);  /* (R1) */
    HRESULT (WINAPI *GetTypeComp)(ITypeLib2*, ITypeComp**);  /* (R1) */
    HRESULT (WINAPI *GetDocumentation)(ITypeLib2*, INT, BSTR*, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *IsName)(ITypeLib2*, LPOLESTR, ULONG, BOOL*);  /* (R1) */
    HRESULT (WINAPI *FindName)(ITypeLib2*, LPOLESTR, ULONG, ITypeInfo**, MEMBERID*, USHORT*);  /* (R1) */
    void (WINAPI *ReleaseTLibAttr)(ITypeLib2*, TLIBATTR*);  /* (R1) */
    /* ITypeLib2 */
    HRESULT (WINAPI *GetCustData)(ITypeLib2*, REFGUID guid, VARIANT* pVarVal);  /* 890582 */
    HRESULT (WINAPI *GetLibStatistics)(ITypeLib2*, unsigned long* pcUniqueNames, unsigned long* pcchUniqueNames);  /* 890591 */
    HRESULT (WINAPI *GetDocumentation2)(ITypeLib2*, INT, LCID, BSTR*, DWORD*, BSTR*);  /* (R1) */
    HRESULT (WINAPI *GetAllCustData)(ITypeLib2*, CUSTDATA* pCustData);  /* 890578 */
} ITypeLib2Vtbl;
struct ITypeLib2 { const ITypeLib2Vtbl *lpVtbl; };
#define ITypeLib2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ITypeLib2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ITypeLib2_Release(T) ((T)->lpVtbl->Release(T))
#define ITypeLib2_GetTypeInfoCount(T) ((T)->lpVtbl->GetTypeInfoCount(T))
#define ITypeLib2_GetTypeInfo(T,a,b) ((T)->lpVtbl->GetTypeInfo(T,a,b))
#define ITypeLib2_GetTypeInfoType(T,a,b) ((T)->lpVtbl->GetTypeInfoType(T,a,b))
#define ITypeLib2_GetTypeInfoOfGuid(T,a,b) ((T)->lpVtbl->GetTypeInfoOfGuid(T,a,b))
#define ITypeLib2_GetLibAttr(T,a) ((T)->lpVtbl->GetLibAttr(T,a))
#define ITypeLib2_GetTypeComp(T,a) ((T)->lpVtbl->GetTypeComp(T,a))
#define ITypeLib2_GetDocumentation(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation(T,a,b,c,d,e))
#define ITypeLib2_IsName(T,a,b,c) ((T)->lpVtbl->IsName(T,a,b,c))
#define ITypeLib2_FindName(T,a,b,c,d,e) ((T)->lpVtbl->FindName(T,a,b,c,d,e))
#define ITypeLib2_ReleaseTLibAttr(T,a) ((T)->lpVtbl->ReleaseTLibAttr(T,a))
#define ITypeLib2_GetCustData(T,a,b) ((T)->lpVtbl->GetCustData(T,a,b))
#define ITypeLib2_GetLibStatistics(T,a,b) ((T)->lpVtbl->GetLibStatistics(T,a,b))
#define ITypeLib2_GetDocumentation2(T,a,b,c,d,e) ((T)->lpVtbl->GetDocumentation2(T,a,b,c,d,e))
#define ITypeLib2_GetAllCustData(T,a) ((T)->lpVtbl->GetAllCustData(T,a))

/* ---- IUnknown: 3 documented method pages; order R1 ---- */
typedef struct IUnknownVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IUnknown*, REFIID iid, void** ppvObject);  /* 890661 */
    ULONG (WINAPI *AddRef)(IUnknown*);  /* 890658 */
    ULONG (WINAPI *Release)(IUnknown*);  /* 890669 */
} IUnknownVtbl;
struct IUnknown { const IUnknownVtbl *lpVtbl; };
#define IUnknown_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IUnknown_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IUnknown_Release(T) ((T)->lpVtbl->Release(T))

/* ---- ICatInformation: 6 documented method pages; order R1 ---- */
typedef struct ICatInformationVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ICatInformation*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ICatInformation*);  /* (R1) */
    ULONG (WINAPI *Release)(ICatInformation*);  /* (R1) */
    /* ICatInformation */
    HRESULT (WINAPI *EnumCategories)(ICatInformation*, LCID lcid, IEnumCATEGORYINFO** ppenumCatInfo);  /* 879987 */
    HRESULT (WINAPI *GetCategoryDesc)(ICatInformation*, REFCATID rcatid, LCID lcid, PWCHAR* ppszDesc);  /* 880029 */
    HRESULT (WINAPI *EnumClassesOfCategories)(ICatInformation*, ULONG cImplemented, CATID rgcatidImpl, ULONG cRequired, CATID rgcatidReq, IEnumCLSID** ppenumCLSID);  /* 880012 */
    HRESULT (WINAPI *IsClassOfCategories)(ICatInformation*, REFCLSID rclsid, ULONG cImplemented, CATID* rgcatidImpl, ULONG cRequired, CATID* rgcatidReq);  /* 880032 */
    HRESULT (WINAPI *EnumImplCategoriesOfClass)(ICatInformation*, REFCLSID rclsid, IEnumCATID** ppenumCATD);  /* 880020 */
    HRESULT (WINAPI *EnumReqCategoriesOfClass)(ICatInformation*, REFCLSID rclsid, IEnumCATID** ppenumCATD);  /* 880024 */
} ICatInformationVtbl;
struct ICatInformation { const ICatInformationVtbl *lpVtbl; };
#define ICatInformation_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ICatInformation_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ICatInformation_Release(T) ((T)->lpVtbl->Release(T))
#define ICatInformation_EnumCategories(T,a,b) ((T)->lpVtbl->EnumCategories(T,a,b))
#define ICatInformation_GetCategoryDesc(T,a,b,c) ((T)->lpVtbl->GetCategoryDesc(T,a,b,c))
#define ICatInformation_EnumClassesOfCategories(T,a,b,c,d,e) ((T)->lpVtbl->EnumClassesOfCategories(T,a,b,c,d,e))
#define ICatInformation_IsClassOfCategories(T,a,b,c,d,e) ((T)->lpVtbl->IsClassOfCategories(T,a,b,c,d,e))
#define ICatInformation_EnumImplCategoriesOfClass(T,a,b) ((T)->lpVtbl->EnumImplCategoriesOfClass(T,a,b))
#define ICatInformation_EnumReqCategoriesOfClass(T,a,b) ((T)->lpVtbl->EnumReqCategoriesOfClass(T,a,b))

/* ---- ICatRegister: 6 documented method pages; order R1 ---- */
typedef struct ICatRegisterVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ICatRegister*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ICatRegister*);  /* (R1) */
    ULONG (WINAPI *Release)(ICatRegister*);  /* (R1) */
    /* ICatRegister */
    HRESULT (WINAPI *RegisterCategories)(ICatRegister*, ULONG cCategories, CATEGORYINFO* rgCategoryInfo);  /* 880045 */
    HRESULT (WINAPI *UnRegisterCategories)(ICatRegister*, ULONG cCategories, CATID* rgcatid);  /* 880063 */
    HRESULT (WINAPI *RegisterClassImplCategories)(ICatRegister*, REFCLSID rclsid, ULONG cCategories, CATID* rgcatid);  /* 880052 */
    HRESULT (WINAPI *UnRegisterClassImplCategories)(ICatRegister*, REFCLSID rclsid, ULONG cCategories, CATID* rgcatid);  /* 880068 */
    HRESULT (WINAPI *RegisterClassReqCategories)(ICatRegister*, REFCLSID rclsid, ULONG cCategories, CATID* rgcatid);  /* 880057 */
    HRESULT (WINAPI *UnRegisterClassReqCategories)(ICatRegister*, REFCLSID rclsid, ULONG cCategories, CATID* rgcatid);  /* 880073 */
} ICatRegisterVtbl;
struct ICatRegister { const ICatRegisterVtbl *lpVtbl; };
#define ICatRegister_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ICatRegister_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ICatRegister_Release(T) ((T)->lpVtbl->Release(T))
#define ICatRegister_RegisterCategories(T,a,b) ((T)->lpVtbl->RegisterCategories(T,a,b))
#define ICatRegister_UnRegisterCategories(T,a,b) ((T)->lpVtbl->UnRegisterCategories(T,a,b))
#define ICatRegister_RegisterClassImplCategories(T,a,b,c) ((T)->lpVtbl->RegisterClassImplCategories(T,a,b,c))
#define ICatRegister_UnRegisterClassImplCategories(T,a,b,c) ((T)->lpVtbl->UnRegisterClassImplCategories(T,a,b,c))
#define ICatRegister_RegisterClassReqCategories(T,a,b,c) ((T)->lpVtbl->RegisterClassReqCategories(T,a,b,c))
#define ICatRegister_UnRegisterClassReqCategories(T,a,b,c) ((T)->lpVtbl->UnRegisterClassReqCategories(T,a,b,c))

/* ---- IObjectSafety: 2 documented method pages; order R1 ---- */
typedef struct IObjectSafetyVtbl {
    /* IObjectSafety */
    HRESULT (WINAPI *GetInterfaceSafetyOptions)(IObjectSafety*, REFIID riid, DWORD* pdwSupportedOptions, DWORD* pdwEnabledOptions);  /* 882879 */
    HRESULT (WINAPI *SetInterfaceSafetyOptions)(IObjectSafety*, REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);  /* 882881 */
} IObjectSafetyVtbl;
struct IObjectSafety { const IObjectSafetyVtbl *lpVtbl; };
#define IObjectSafety_GetInterfaceSafetyOptions(T,a,b,c) ((T)->lpVtbl->GetInterfaceSafetyOptions(T,a,b,c))
#define IObjectSafety_SetInterfaceSafetyOptions(T,a,b,c) ((T)->lpVtbl->SetInterfaceSafetyOptions(T,a,b,c))

/* ---- IOleAdviseHolder: 4 documented method pages; order R1 ---- */
typedef struct IOleAdviseHolderVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleAdviseHolder*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleAdviseHolder*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleAdviseHolder*);  /* (R1) */
    /* IOleAdviseHolder */
    HRESULT (WINAPI *Advise)(IOleAdviseHolder*, IAdviseSink* pAdvise, DWORD* pdwConnection);  /* 882882 */
    HRESULT (WINAPI *Unadvise)(IOleAdviseHolder*, DWORD dwConnection);  /* 882889 */
    HRESULT (WINAPI *EnumAdvise)(IOleAdviseHolder*, IEnumSTATDATA* ppEnumAdvise);  /* 882883 */
    HRESULT (WINAPI *SendOnRename)(IOleAdviseHolder*, IMoniker* pmk);  /* 882886 */
    HRESULT (WINAPI *SendOnSave)(IOleAdviseHolder*);  /* (R1) */
    HRESULT (WINAPI *SendOnClose)(IOleAdviseHolder*);  /* (R1) */
} IOleAdviseHolderVtbl;
struct IOleAdviseHolder { const IOleAdviseHolderVtbl *lpVtbl; };
#define IOleAdviseHolder_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleAdviseHolder_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleAdviseHolder_Release(T) ((T)->lpVtbl->Release(T))
#define IOleAdviseHolder_Advise(T,a,b) ((T)->lpVtbl->Advise(T,a,b))
#define IOleAdviseHolder_Unadvise(T,a) ((T)->lpVtbl->Unadvise(T,a))
#define IOleAdviseHolder_EnumAdvise(T,a) ((T)->lpVtbl->EnumAdvise(T,a))
#define IOleAdviseHolder_SendOnRename(T,a) ((T)->lpVtbl->SendOnRename(T,a))
#define IOleAdviseHolder_SendOnSave(T) ((T)->lpVtbl->SendOnSave(T))
#define IOleAdviseHolder_SendOnClose(T) ((T)->lpVtbl->SendOnClose(T))

/* ---- IOleClientSite: 5 documented method pages; order R1 ---- */
typedef struct IOleClientSiteVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleClientSite*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleClientSite*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleClientSite*);  /* (R1) */
    /* IOleClientSite */
    HRESULT (WINAPI *SaveObject)(IOleClientSite*);  /* 882895 */
    HRESULT (WINAPI *GetMoniker)(IOleClientSite*, DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk);  /* 882891 */
    HRESULT (WINAPI *GetContainer)(IOleClientSite*, LPOLECONTAINER*);  /* (R1) */
    HRESULT (WINAPI *ShowObject)(IOleClientSite*);  /* 882896 */
    HRESULT (WINAPI *OnShowWindow)(IOleClientSite*, BOOL fShow);  /* 882893 */
    HRESULT (WINAPI *RequestNewObjectLayout)(IOleClientSite*);  /* 882894 */
} IOleClientSiteVtbl;
struct IOleClientSite { const IOleClientSiteVtbl *lpVtbl; };
#define IOleClientSite_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleClientSite_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleClientSite_Release(T) ((T)->lpVtbl->Release(T))
#define IOleClientSite_SaveObject(T) ((T)->lpVtbl->SaveObject(T))
#define IOleClientSite_GetMoniker(T,a,b,c) ((T)->lpVtbl->GetMoniker(T,a,b,c))
#define IOleClientSite_GetContainer(T,a) ((T)->lpVtbl->GetContainer(T,a))
#define IOleClientSite_ShowObject(T) ((T)->lpVtbl->ShowObject(T))
#define IOleClientSite_OnShowWindow(T,a) ((T)->lpVtbl->OnShowWindow(T,a))
#define IOleClientSite_RequestNewObjectLayout(T) ((T)->lpVtbl->RequestNewObjectLayout(T))

/* ---- IOleContainer: 2 documented method pages; order R1 ---- */
typedef struct IOleContainerVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleContainer*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleContainer*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleContainer*);  /* (R1) */
    /* IParseDisplayName */
    HRESULT (WINAPI *ParseDisplayName)(IOleContainer*, IBindCtx*, LPOLESTR, ULONG*, IMoniker**);  /* (R1) */
    /* IOleContainer */
    HRESULT (WINAPI *EnumObjects)(IOleContainer*, DWORD, IEnumUnknown**);  /* (R1) */
    HRESULT (WINAPI *LockContainer)(IOleContainer*, BOOL fLock);  /* 519258 */
} IOleContainerVtbl;
struct IOleContainer { const IOleContainerVtbl *lpVtbl; };
#define IOleContainer_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleContainer_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleContainer_Release(T) ((T)->lpVtbl->Release(T))
#define IOleContainer_ParseDisplayName(T,a,b,c,d) ((T)->lpVtbl->ParseDisplayName(T,a,b,c,d))
#define IOleContainer_EnumObjects(T,a,b) ((T)->lpVtbl->EnumObjects(T,a,b))
#define IOleContainer_LockContainer(T,a) ((T)->lpVtbl->LockContainer(T,a))

/* ---- IOleControlSite: 7 documented method pages; order R1 ---- */
typedef struct IOleControlSiteVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleControlSite*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleControlSite*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleControlSite*);  /* (R1) */
    /* IOleControlSite */
    HRESULT (WINAPI *OnControlInfoChanged)(IOleControlSite*);  /* 519262 */
    HRESULT (WINAPI *LockInPlaceActive)(IOleControlSite*, BOOL fLock);  /* 519261 */
    HRESULT (WINAPI *GetExtendedControl)(IOleControlSite*, IDispatch** ppDisp);  /* 519259 */
    HRESULT (WINAPI *TransformCoords)(IOleControlSite*, POINTL* pPtlHimetric, POINTF* pPtfContainer, DWORD dwFlags);  /* 519265 */
    HRESULT (WINAPI *TranslateAccelerator)(IOleControlSite*, LPMSG pMsg, DWORD grfModifiers);  /* 519266 */
    HRESULT (WINAPI *OnFocus)(IOleControlSite*, BOOL fGotFocus);  /* 519263 */
    HRESULT (WINAPI *ShowPropertyFrame)(IOleControlSite*);  /* 519264 */
} IOleControlSiteVtbl;
struct IOleControlSite { const IOleControlSiteVtbl *lpVtbl; };
#define IOleControlSite_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleControlSite_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleControlSite_Release(T) ((T)->lpVtbl->Release(T))
#define IOleControlSite_OnControlInfoChanged(T) ((T)->lpVtbl->OnControlInfoChanged(T))
#define IOleControlSite_LockInPlaceActive(T,a) ((T)->lpVtbl->LockInPlaceActive(T,a))
#define IOleControlSite_GetExtendedControl(T,a) ((T)->lpVtbl->GetExtendedControl(T,a))
#define IOleControlSite_TransformCoords(T,a,b,c) ((T)->lpVtbl->TransformCoords(T,a,b,c))
#define IOleControlSite_TranslateAccelerator(T,a,b) ((T)->lpVtbl->TranslateAccelerator(T,a,b))
#define IOleControlSite_OnFocus(T,a) ((T)->lpVtbl->OnFocus(T,a))
#define IOleControlSite_ShowPropertyFrame(T) ((T)->lpVtbl->ShowPropertyFrame(T))

/* ---- IOleInPlaceSite: 7 documented method pages; order R1 ---- */
typedef struct IOleInPlaceSiteVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleInPlaceSite*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleInPlaceSite*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleInPlaceSite*);  /* (R1) */
    /* IOleWindow */
    HRESULT (WINAPI *GetWindow)(IOleInPlaceSite*, HWND*);  /* (R1) */
    HRESULT (WINAPI *ContextSensitiveHelp)(IOleInPlaceSite*, BOOL);  /* (R1) */
    /* IOleInPlaceSite */
    HRESULT (WINAPI *CanInPlaceActivate)(IOleInPlaceSite*);  /* 519268 */
    HRESULT (WINAPI *OnInPlaceActivate)(IOleInPlaceSite*);  /* 519273 */
    HRESULT (WINAPI *OnUIActivate)(IOleInPlaceSite*);  /* (R1) */
    HRESULT (WINAPI *GetWindowContext)(IOleInPlaceSite*, IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);  /* 519271 */
    HRESULT (WINAPI *Scroll)(IOleInPlaceSite*, SIZE scrollExtent);  /* 519278 */
    HRESULT (WINAPI *OnUIDeactivate)(IOleInPlaceSite*, BOOL fUndoable);  /* 519277 */
    HRESULT (WINAPI *OnInPlaceDeactivate)(IOleInPlaceSite*);  /* 519274 */
    HRESULT (WINAPI *DiscardUndoState)(IOleInPlaceSite*);  /* (R1) */
    HRESULT (WINAPI *DeactivateAndUndo)(IOleInPlaceSite*);  /* (R1) */
    HRESULT (WINAPI *OnPosRectChange)(IOleInPlaceSite*, LPCRECT lprcPosRect);  /* 519275 */
} IOleInPlaceSiteVtbl;
struct IOleInPlaceSite { const IOleInPlaceSiteVtbl *lpVtbl; };
#define IOleInPlaceSite_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleInPlaceSite_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleInPlaceSite_Release(T) ((T)->lpVtbl->Release(T))
#define IOleInPlaceSite_GetWindow(T,a) ((T)->lpVtbl->GetWindow(T,a))
#define IOleInPlaceSite_ContextSensitiveHelp(T,a) ((T)->lpVtbl->ContextSensitiveHelp(T,a))
#define IOleInPlaceSite_CanInPlaceActivate(T) ((T)->lpVtbl->CanInPlaceActivate(T))
#define IOleInPlaceSite_OnInPlaceActivate(T) ((T)->lpVtbl->OnInPlaceActivate(T))
#define IOleInPlaceSite_OnUIActivate(T) ((T)->lpVtbl->OnUIActivate(T))
#define IOleInPlaceSite_GetWindowContext(T,a,b,c,d,e) ((T)->lpVtbl->GetWindowContext(T,a,b,c,d,e))
#define IOleInPlaceSite_Scroll(T,a) ((T)->lpVtbl->Scroll(T,a))
#define IOleInPlaceSite_OnUIDeactivate(T,a) ((T)->lpVtbl->OnUIDeactivate(T,a))
#define IOleInPlaceSite_OnInPlaceDeactivate(T) ((T)->lpVtbl->OnInPlaceDeactivate(T))
#define IOleInPlaceSite_DiscardUndoState(T) ((T)->lpVtbl->DiscardUndoState(T))
#define IOleInPlaceSite_DeactivateAndUndo(T) ((T)->lpVtbl->DeactivateAndUndo(T))
#define IOleInPlaceSite_OnPosRectChange(T,a) ((T)->lpVtbl->OnPosRectChange(T,a))

/* ---- IOleObject: 20 documented method pages; order R1 ---- */
typedef struct IOleObjectVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleObject*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleObject*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleObject*);  /* (R1) */
    /* IOleObject */
    HRESULT (WINAPI *SetClientSite)(IOleObject*, IOleClientSite* pClientSite);  /* 882928 */
    HRESULT (WINAPI *GetClientSite)(IOleObject*, IOleClientSite** ppClientSite);  /* 882918 */
    HRESULT (WINAPI *SetHostNames)(IOleObject*, LPCOLESTR szContainerApp, LPCOLESTR szContainerObj);  /* 882931 */
    HRESULT (WINAPI *Close)(IOleObject*, DWORD dwSaveOption);  /* 882914 */
    HRESULT (WINAPI *SetMoniker)(IOleObject*, DWORD, LPMONIKER);  /* (R1) */
    HRESULT (WINAPI *GetMoniker)(IOleObject*, DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk);  /* 882922 */
    HRESULT (WINAPI *InitFromData)(IOleObject*, IDataObject* pDataObject, BOOL fCreation, DWORD dwReserved);  /* 882925 */
    HRESULT (WINAPI *GetClipboardData)(IOleObject*, DWORD dwReserved, IDataObject** ppDataObject);  /* 882919 */
    HRESULT (WINAPI *DoVerb)(IOleObject*, LONG iVerb, LPMSG lpmsg, IOleClientSite* pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect);  /* 882915 */
    HRESULT (WINAPI *EnumVerbs)(IOleObject*, IEnumOLEVERB** ppEnumOleVerb);  /* 882917 */
    HRESULT (WINAPI *Update)(IOleObject*);  /* 882934 */
    HRESULT (WINAPI *IsUpToDate)(IOleObject*);  /* 882926 */
    HRESULT (WINAPI *GetUserClassID)(IOleObject*, CLSID* pClsid);  /* 882923 */
    HRESULT (WINAPI *GetUserType)(IOleObject*, DWORD dwFormOfType, LPOLESTR* pszUserType);  /* 882924 */
    HRESULT (WINAPI *SetExtent)(IOleObject*, DWORD dwDrawAspect, SIZEL* psizel);  /* 882930 */
    HRESULT (WINAPI *GetExtent)(IOleObject*, DWORD dwDrawAspect, SIZEL* psizel);  /* 882920 */
    HRESULT (WINAPI *Advise)(IOleObject*, IAdviseSink* pAdvSink, DWORD* pdwConnection);  /* 882913 */
    HRESULT (WINAPI *Unadvise)(IOleObject*, DWORD dwConnection);  /* 882933 */
    HRESULT (WINAPI *EnumAdvise)(IOleObject*, IEnumSTATDATA** ppenumAdvise);  /* 882916 */
    HRESULT (WINAPI *GetMiscStatus)(IOleObject*, DWORD dwAspect, DWORD* pdwStatus);  /* 882921 */
    HRESULT (WINAPI *SetColorScheme)(IOleObject*, LOGPALETTE* pLogpal);  /* 882929 */
} IOleObjectVtbl;
struct IOleObject { const IOleObjectVtbl *lpVtbl; };
#define IOleObject_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleObject_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleObject_Release(T) ((T)->lpVtbl->Release(T))
#define IOleObject_SetClientSite(T,a) ((T)->lpVtbl->SetClientSite(T,a))
#define IOleObject_GetClientSite(T,a) ((T)->lpVtbl->GetClientSite(T,a))
#define IOleObject_SetHostNames(T,a,b) ((T)->lpVtbl->SetHostNames(T,a,b))
#define IOleObject_Close(T,a) ((T)->lpVtbl->Close(T,a))
#define IOleObject_SetMoniker(T,a,b) ((T)->lpVtbl->SetMoniker(T,a,b))
#define IOleObject_GetMoniker(T,a,b,c) ((T)->lpVtbl->GetMoniker(T,a,b,c))
#define IOleObject_InitFromData(T,a,b,c) ((T)->lpVtbl->InitFromData(T,a,b,c))
#define IOleObject_GetClipboardData(T,a,b) ((T)->lpVtbl->GetClipboardData(T,a,b))
#define IOleObject_DoVerb(T,a,b,c,d,e,f) ((T)->lpVtbl->DoVerb(T,a,b,c,d,e,f))
#define IOleObject_EnumVerbs(T,a) ((T)->lpVtbl->EnumVerbs(T,a))
#define IOleObject_Update(T) ((T)->lpVtbl->Update(T))
#define IOleObject_IsUpToDate(T) ((T)->lpVtbl->IsUpToDate(T))
#define IOleObject_GetUserClassID(T,a) ((T)->lpVtbl->GetUserClassID(T,a))
#define IOleObject_GetUserType(T,a,b) ((T)->lpVtbl->GetUserType(T,a,b))
#define IOleObject_SetExtent(T,a,b) ((T)->lpVtbl->SetExtent(T,a,b))
#define IOleObject_GetExtent(T,a,b) ((T)->lpVtbl->GetExtent(T,a,b))
#define IOleObject_Advise(T,a,b) ((T)->lpVtbl->Advise(T,a,b))
#define IOleObject_Unadvise(T,a) ((T)->lpVtbl->Unadvise(T,a))
#define IOleObject_EnumAdvise(T,a) ((T)->lpVtbl->EnumAdvise(T,a))
#define IOleObject_GetMiscStatus(T,a,b) ((T)->lpVtbl->GetMiscStatus(T,a,b))
#define IOleObject_SetColorScheme(T,a) ((T)->lpVtbl->SetColorScheme(T,a))

/* ---- IOleWindow: 2 documented method pages; order R1 ---- */
typedef struct IOleWindowVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IOleWindow*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IOleWindow*);  /* (R1) */
    ULONG (WINAPI *Release)(IOleWindow*);  /* (R1) */
    /* IOleWindow */
    HRESULT (WINAPI *GetWindow)(IOleWindow*, HWND* phwnd);  /* 519280 */
    HRESULT (WINAPI *ContextSensitiveHelp)(IOleWindow*, BOOL fEnterMode);  /* 519279 */
} IOleWindowVtbl;
struct IOleWindow { const IOleWindowVtbl *lpVtbl; };
#define IOleWindow_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IOleWindow_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IOleWindow_Release(T) ((T)->lpVtbl->Release(T))
#define IOleWindow_GetWindow(T,a) ((T)->lpVtbl->GetWindow(T,a))
#define IOleWindow_ContextSensitiveHelp(T,a) ((T)->lpVtbl->ContextSensitiveHelp(T,a))

/* ---- IParseDisplayName: 1 documented method pages; order R1 ---- */
typedef struct IParseDisplayNameVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IParseDisplayName*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IParseDisplayName*);  /* (R1) */
    ULONG (WINAPI *Release)(IParseDisplayName*);  /* (R1) */
    /* IParseDisplayName */
    HRESULT (WINAPI *ParseDisplayName)(IParseDisplayName*, IBindCtx* pbc, LPOLESTR pszDisplayName, ULONG* pchEaten, IMoniker** ppmkOut);  /* 882936 */
} IParseDisplayNameVtbl;
struct IParseDisplayName { const IParseDisplayNameVtbl *lpVtbl; };
#define IParseDisplayName_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IParseDisplayName_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IParseDisplayName_Release(T) ((T)->lpVtbl->Release(T))
#define IParseDisplayName_ParseDisplayName(T,a,b,c,d) ((T)->lpVtbl->ParseDisplayName(T,a,b,c,d))

/* ---- IPersist: 1 documented method pages; order R1 ---- */
typedef struct IPersistVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersist*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersist*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersist*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersist*, CLSID* pClassID);  /* 883501 */
} IPersistVtbl;
struct IPersist { const IPersistVtbl *lpVtbl; };
#define IPersist_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersist_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersist_Release(T) ((T)->lpVtbl->Release(T))
#define IPersist_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))

/* ---- IPersistStorage: 6 documented method pages; order R1 ---- */
typedef struct IPersistStorageVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistStorage*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistStorage*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistStorage*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistStorage*, CLSID*);  /* (R1) */
    /* IPersistStorage */
    HRESULT (WINAPI *IsDirty)(IPersistStorage*);  /* 883704 */
    HRESULT (WINAPI *InitNew)(IPersistStorage*, IStorage* pStg);  /* 883686 */
    HRESULT (WINAPI *Load)(IPersistStorage*, IStorage* pStg);  /* 883717 */
    HRESULT (WINAPI *Save)(IPersistStorage*, IStorage* pStgSave, BOOL fSameAsLoad);  /* 883726 */
    HRESULT (WINAPI *SaveCompleted)(IPersistStorage*, IStorage* pStgNew);  /* 883737 */
    HRESULT (WINAPI *HandsOffStorage)(IPersistStorage*);  /* 883673 */
} IPersistStorageVtbl;
struct IPersistStorage { const IPersistStorageVtbl *lpVtbl; };
#define IPersistStorage_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistStorage_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistStorage_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistStorage_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistStorage_IsDirty(T) ((T)->lpVtbl->IsDirty(T))
#define IPersistStorage_InitNew(T,a) ((T)->lpVtbl->InitNew(T,a))
#define IPersistStorage_Load(T,a) ((T)->lpVtbl->Load(T,a))
#define IPersistStorage_Save(T,a,b) ((T)->lpVtbl->Save(T,a,b))
#define IPersistStorage_SaveCompleted(T,a) ((T)->lpVtbl->SaveCompleted(T,a))
#define IPersistStorage_HandsOffStorage(T) ((T)->lpVtbl->HandsOffStorage(T))

/* ---- IPersistStream: 4 documented method pages; order R1 ---- */
typedef struct IPersistStreamVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistStream*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistStream*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistStream*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistStream*, LPCLSID);  /* (R1) */
    /* IPersistStream */
    HRESULT (WINAPI *IsDirty)(IPersistStream*);  /* 883830 */
    HRESULT (WINAPI *Load)(IPersistStream*, IStream* pStm);  /* 883840 */
    HRESULT (WINAPI *Save)(IPersistStream*, IStream* pStm, BOOL fClearDirty);  /* 883850 */
    HRESULT (WINAPI *GetSizeMax)(IPersistStream*, ULARGE_INTEGER* pcbSize);  /* 883746 */
} IPersistStreamVtbl;
struct IPersistStream { const IPersistStreamVtbl *lpVtbl; };
#define IPersistStream_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistStream_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistStream_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistStream_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistStream_IsDirty(T) ((T)->lpVtbl->IsDirty(T))
#define IPersistStream_Load(T,a) ((T)->lpVtbl->Load(T,a))
#define IPersistStream_Save(T,a,b) ((T)->lpVtbl->Save(T,a,b))
#define IPersistStream_GetSizeMax(T,a) ((T)->lpVtbl->GetSizeMax(T,a))

/* ---- IPersistStreamInit: 5 documented method pages; order R1 ---- */
typedef struct IPersistStreamInitVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistStreamInit*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistStreamInit*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistStreamInit*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistStreamInit*, LPCLSID);  /* (R1) */
    /* IPersistStreamInit */
    HRESULT (WINAPI *IsDirty)(IPersistStreamInit*);  /* 883784 */
    HRESULT (WINAPI *Load)(IPersistStreamInit*, LPSTREAM pStm);  /* 883792 */
    HRESULT (WINAPI *Save)(IPersistStreamInit*, LPSTREAM pStm, BOOL fClearDirty);  /* 883806 */
    HRESULT (WINAPI *GetSizeMax)(IPersistStreamInit*, ULARGE_INTEGER* pcbSize);  /* 883758 */
    HRESULT (WINAPI *InitNew)(IPersistStreamInit*);  /* 883767 */
} IPersistStreamInitVtbl;
struct IPersistStreamInit { const IPersistStreamInitVtbl *lpVtbl; };
#define IPersistStreamInit_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistStreamInit_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistStreamInit_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistStreamInit_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistStreamInit_IsDirty(T) ((T)->lpVtbl->IsDirty(T))
#define IPersistStreamInit_Load(T,a) ((T)->lpVtbl->Load(T,a))
#define IPersistStreamInit_Save(T,a,b) ((T)->lpVtbl->Save(T,a,b))
#define IPersistStreamInit_GetSizeMax(T,a) ((T)->lpVtbl->GetSizeMax(T,a))
#define IPersistStreamInit_InitNew(T) ((T)->lpVtbl->InitNew(T))

/* ---- IProgressNotify: 1 documented method pages; order R1 ---- */
typedef struct IProgressNotifyVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IProgressNotify*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IProgressNotify*);  /* (R1) */
    ULONG (WINAPI *Release)(IProgressNotify*);  /* (R1) */
    /* IProgressNotify */
    HRESULT (WINAPI *OnProgress)(IProgressNotify*, DWORD dwProgressCurrent, DWORD dwProgressMaximum, BOOL fAccurate, BOOL fOwner);  /* 884240 */
} IProgressNotifyVtbl;
struct IProgressNotify { const IProgressNotifyVtbl *lpVtbl; };
#define IProgressNotify_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IProgressNotify_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IProgressNotify_Release(T) ((T)->lpVtbl->Release(T))
#define IProgressNotify_OnProgress(T,a,b,c,d) ((T)->lpVtbl->OnProgress(T,a,b,c,d))

/* ---- IProvideClassInfo: 1 documented method pages; order R1 ---- */
typedef struct IProvideClassInfoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IProvideClassInfo*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IProvideClassInfo*);  /* (R1) */
    ULONG (WINAPI *Release)(IProvideClassInfo*);  /* (R1) */
    /* IProvideClassInfo */
    HRESULT (WINAPI *GetClassInfo)(IProvideClassInfo*, ITypeInfo** ppTI);  /* 884308 */
} IProvideClassInfoVtbl;
struct IProvideClassInfo { const IProvideClassInfoVtbl *lpVtbl; };
#define IProvideClassInfo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IProvideClassInfo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IProvideClassInfo_Release(T) ((T)->lpVtbl->Release(T))
#define IProvideClassInfo_GetClassInfo(T,a) ((T)->lpVtbl->GetClassInfo(T,a))

/* ---- IProvideClassInfo2: 1 documented method pages; order R1 ---- */
typedef struct IProvideClassInfo2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IProvideClassInfo2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IProvideClassInfo2*);  /* (R1) */
    ULONG (WINAPI *Release)(IProvideClassInfo2*);  /* (R1) */
    /* IProvideClassInfo */
    HRESULT (WINAPI *GetClassInfo)(IProvideClassInfo2*, LPTYPEINFO*);  /* (R1) */
    /* IProvideClassInfo2 */
    HRESULT (WINAPI *GetGUID)(IProvideClassInfo2*, DWORD dwGuidKind, GUID* pGUID);  /* 884278 */
} IProvideClassInfo2Vtbl;
struct IProvideClassInfo2 { const IProvideClassInfo2Vtbl *lpVtbl; };
#define IProvideClassInfo2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IProvideClassInfo2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IProvideClassInfo2_Release(T) ((T)->lpVtbl->Release(T))
#define IProvideClassInfo2_GetClassInfo(T,a) ((T)->lpVtbl->GetClassInfo(T,a))
#define IProvideClassInfo2_GetGUID(T,a,b) ((T)->lpVtbl->GetGUID(T,a,b))

/* ---- IROTData: 1 documented method pages; order R1 ---- */
typedef struct IROTDataVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IROTData*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IROTData*);  /* (R1) */
    ULONG (WINAPI *Release)(IROTData*);  /* (R1) */
    /* IROTData */
    HRESULT (WINAPI *GetComparisonData)(IROTData*, BYTE* pbData, ULONG cbMax, ULONG* pcbData);  /* 884587 */
} IROTDataVtbl;
struct IROTData { const IROTDataVtbl *lpVtbl; };
#define IROTData_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IROTData_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IROTData_Release(T) ((T)->lpVtbl->Release(T))
#define IROTData_GetComparisonData(T,a,b,c) ((T)->lpVtbl->GetComparisonData(T,a,b,c))

/* ---- IRootStorage: 1 documented method pages; order R1 ---- */
typedef struct IRootStorageVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IRootStorage*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IRootStorage*);  /* (R1) */
    ULONG (WINAPI *Release)(IRootStorage*);  /* (R1) */
    /* IRootStorage */
    HRESULT (WINAPI *SwitchToFile)(IRootStorage*, LPOLESTR pszFile);  /* 884586 */
} IRootStorageVtbl;
struct IRootStorage { const IRootStorageVtbl *lpVtbl; };
#define IRootStorage_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IRootStorage_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IRootStorage_Release(T) ((T)->lpVtbl->Release(T))
#define IRootStorage_SwitchToFile(T,a) ((T)->lpVtbl->SwitchToFile(T,a))

/* ---- IRunnableObject: 5 documented method pages; order R1 ---- */
typedef struct IRunnableObjectVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IRunnableObject*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IRunnableObject*);  /* (R1) */
    ULONG (WINAPI *Release)(IRunnableObject*);  /* (R1) */
    /* IRunnableObject */
    HRESULT (WINAPI *GetRunningClass)(IRunnableObject*, LPCLSID lpClsid);  /* 884589 */
    HRESULT (WINAPI *Run)(IRunnableObject*, LPBC lpbc);  /* 884594 */
    BOOL (WINAPI *IsRunning)(IRunnableObject*);  /* 884590 */
    HRESULT (WINAPI *LockRunning)(IRunnableObject*, BOOL fLock, BOOL fLastUnlockCloses);  /* 884593 */
    HRESULT (WINAPI *SetContainedObject)(IRunnableObject*, BOOL fContained);  /* 884595 */
} IRunnableObjectVtbl;
struct IRunnableObject { const IRunnableObjectVtbl *lpVtbl; };
#define IRunnableObject_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IRunnableObject_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IRunnableObject_Release(T) ((T)->lpVtbl->Release(T))
#define IRunnableObject_GetRunningClass(T,a) ((T)->lpVtbl->GetRunningClass(T,a))
#define IRunnableObject_Run(T,a) ((T)->lpVtbl->Run(T,a))
#define IRunnableObject_IsRunning(T) ((T)->lpVtbl->IsRunning(T))
#define IRunnableObject_LockRunning(T,a,b) ((T)->lpVtbl->LockRunning(T,a,b))
#define IRunnableObject_SetContainedObject(T,a) ((T)->lpVtbl->SetContainedObject(T,a))

/* ---- ISequentialStream: 2 documented method pages; order R1 ---- */
typedef struct ISequentialStreamVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(ISequentialStream*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(ISequentialStream*);  /* (R1) */
    ULONG (WINAPI *Release)(ISequentialStream*);  /* (R1) */
    /* ISequentialStream */
    HRESULT (WINAPI *Read)(ISequentialStream*, void* pv, ULONG cb, ULONG* pcbRead);  /* 886039 */
    HRESULT (WINAPI *Write)(ISequentialStream*, void const* pv, ULONG cb, ULONG* pcbWritten);  /* 886049 */
} ISequentialStreamVtbl;
struct ISequentialStream { const ISequentialStreamVtbl *lpVtbl; };
#define ISequentialStream_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define ISequentialStream_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define ISequentialStream_Release(T) ((T)->lpVtbl->Release(T))
#define ISequentialStream_Read(T,a,b,c) ((T)->lpVtbl->Read(T,a,b,c))
#define ISequentialStream_Write(T,a,b,c) ((T)->lpVtbl->Write(T,a,b,c))

/* ---- IServerSecurity: 1 documented method pages; order R1 ---- */
typedef struct IServerSecurityVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IServerSecurity*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IServerSecurity*);  /* (R1) */
    ULONG (WINAPI *Release)(IServerSecurity*);  /* (R1) */
    /* IServerSecurity */
    HRESULT (WINAPI *QueryBlanket)(IServerSecurity*, DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DWORD* pAuthnLevel, DWORD* pImpLevel, RPC_AUTHZ_HANDLE* pPrivs, DWORD* pCapabilities);  /* 886085 */
    HRESULT (WINAPI *ImpersonateClient)(IServerSecurity*);  /* (R1) */
    HRESULT (WINAPI *RevertToSelf)(IServerSecurity*);  /* (R1) */
    HRESULT (WINAPI *IsImpersonating)(IServerSecurity*);  /* (R1) */
} IServerSecurityVtbl;
struct IServerSecurity { const IServerSecurityVtbl *lpVtbl; };
#define IServerSecurity_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IServerSecurity_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IServerSecurity_Release(T) ((T)->lpVtbl->Release(T))
#define IServerSecurity_QueryBlanket(T,a,b,c,d,e,f,g) ((T)->lpVtbl->QueryBlanket(T,a,b,c,d,e,f,g))
#define IServerSecurity_ImpersonateClient(T) ((T)->lpVtbl->ImpersonateClient(T))
#define IServerSecurity_RevertToSelf(T) ((T)->lpVtbl->RevertToSelf(T))
#define IServerSecurity_IsImpersonating(T) ((T)->lpVtbl->IsImpersonating(T))

/* ---- IStdMarshalInfo: 1 documented method pages; order R1 ---- */
typedef struct IStdMarshalInfoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IStdMarshalInfo*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IStdMarshalInfo*);  /* (R1) */
    ULONG (WINAPI *Release)(IStdMarshalInfo*);  /* (R1) */
    /* IStdMarshalInfo */
    HRESULT (WINAPI *GetClassForHandler)(IStdMarshalInfo*, DWORD dwDestContext, void* pvDestContext, CLSID* pClsid);  /* 890547 */
} IStdMarshalInfoVtbl;
struct IStdMarshalInfo { const IStdMarshalInfoVtbl *lpVtbl; };
#define IStdMarshalInfo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IStdMarshalInfo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IStdMarshalInfo_Release(T) ((T)->lpVtbl->Release(T))
#define IStdMarshalInfo_GetClassForHandler(T,a,b,c) ((T)->lpVtbl->GetClassForHandler(T,a,b,c))

/* ---- IViewObject: 6 documented method pages; order R1 ---- */
typedef struct IViewObjectVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IViewObject*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IViewObject*);  /* (R1) */
    ULONG (WINAPI *Release)(IViewObject*);  /* (R1) */
    /* IViewObject */
    HRESULT (WINAPI *Draw)(IViewObject*, DWORD, LONG, VOID*, DVTARGETDEVICE*, HDC, HDC, LPCRECTL, LPCRECTL, LPFNCONTINUE pfnContinue, DWORD);  /* (R1) */
    HRESULT (WINAPI *GetColorSet)(IViewObject*, DWORD dwAspect, LONG lindex, void* pvAspect, DVTARGETDEVICE* ptd, HDC hicTargetDev, LOGPALETTE** ppColorSet);  /* 891695 */
    HRESULT (WINAPI *Freeze)(IViewObject*, DWORD dwAspect, LONG lindex, void* pvAspect, DWORD* pdwFreeze);  /* 891597 */
    HRESULT (WINAPI *Unfreeze)(IViewObject*, DWORD dwFreeze);  /* 891710 */
    HRESULT (WINAPI *SetAdvise)(IViewObject*, DWORD dwAspect, DWORD advf, IAdviseSink* pAdvSink);  /* 891709 */
    HRESULT (WINAPI *GetAdvise)(IViewObject*, DWORD* pdwAspect, DWORD* padvf, IAdviseSink** ppAdvSink);  /* 891602 */
} IViewObjectVtbl;
struct IViewObject { const IViewObjectVtbl *lpVtbl; };
#define IViewObject_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IViewObject_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IViewObject_Release(T) ((T)->lpVtbl->Release(T))
#define IViewObject_Draw(T,a,b,c,d,e,f,g,h,i,j) ((T)->lpVtbl->Draw(T,a,b,c,d,e,f,g,h,i,j))
#define IViewObject_GetColorSet(T,a,b,c,d,e,f) ((T)->lpVtbl->GetColorSet(T,a,b,c,d,e,f))
#define IViewObject_Freeze(T,a,b,c,d) ((T)->lpVtbl->Freeze(T,a,b,c,d))
#define IViewObject_Unfreeze(T,a) ((T)->lpVtbl->Unfreeze(T,a))
#define IViewObject_SetAdvise(T,a,b,c) ((T)->lpVtbl->SetAdvise(T,a,b,c))
#define IViewObject_GetAdvise(T,a,b,c) ((T)->lpVtbl->GetAdvise(T,a,b,c))

/* ---- IViewObject2: 1 documented method pages; order R1 ---- */
typedef struct IViewObject2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IViewObject2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IViewObject2*);  /* (R1) */
    ULONG (WINAPI *Release)(IViewObject2*);  /* (R1) */
    /* IViewObject */
    HRESULT (WINAPI *Draw)(IViewObject2*, DWORD, LONG, VOID*, DVTARGETDEVICE*, HDC, HDC, LPCRECTL, LPCRECTL, LPFNCONTINUE pfnContinue, DWORD);  /* (R1) */
    HRESULT (WINAPI *GetColorSet)(IViewObject2*, DWORD, LONG, VOID*, DVTARGETDEVICE*, HDC, LPLOGPALETTE*);  /* (R1) */
    HRESULT (WINAPI *Freeze)(IViewObject2*, DWORD, LONG, VOID*, PDWORD);  /* (R1) */
    HRESULT (WINAPI *Unfreeze)(IViewObject2*, DWORD);  /* (R1) */
    HRESULT (WINAPI *SetAdvise)(IViewObject2*, DWORD, DWORD, IAdviseSink*);  /* (R1) */
    HRESULT (WINAPI *GetAdvise)(IViewObject2*, PDWORD, PDWORD, IAdviseSink**);  /* (R1) */
    /* IViewObject2 */
    HRESULT (WINAPI *GetExtent)(IViewObject2*, DWORD dwAspect, LONG lindex, DVTARGETDEVICE ptd, LPSIZEL lpsizel);  /* 891559 */
} IViewObject2Vtbl;
struct IViewObject2 { const IViewObject2Vtbl *lpVtbl; };
#define IViewObject2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IViewObject2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IViewObject2_Release(T) ((T)->lpVtbl->Release(T))
#define IViewObject2_Draw(T,a,b,c,d,e,f,g,h,i,j) ((T)->lpVtbl->Draw(T,a,b,c,d,e,f,g,h,i,j))
#define IViewObject2_GetColorSet(T,a,b,c,d,e,f) ((T)->lpVtbl->GetColorSet(T,a,b,c,d,e,f))
#define IViewObject2_Freeze(T,a,b,c,d) ((T)->lpVtbl->Freeze(T,a,b,c,d))
#define IViewObject2_Unfreeze(T,a) ((T)->lpVtbl->Unfreeze(T,a))
#define IViewObject2_SetAdvise(T,a,b,c) ((T)->lpVtbl->SetAdvise(T,a,b,c))
#define IViewObject2_GetAdvise(T,a,b,c) ((T)->lpVtbl->GetAdvise(T,a,b,c))
#define IViewObject2_GetExtent(T,a,b,c,d) ((T)->lpVtbl->GetExtent(T,a,b,c,d))

#ifdef __cplusplus
}
#endif


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcesdk_ReportStatus: page-printed prototype (Windows CE OS). */
BOOL ReportStatus(LPWSTR lpszObjType, UINT uCode, UINT uParam);

typedef struct IContinueCallback IContinueCallback;

/* ---- IContinueCallback: vtable order printed by ms880195.html
 *      ("Methods in Vtable Order" tables; method page ids per entry) ---- */
typedef struct IContinueCallbackVtbl {
    HRESULT (WINAPI *QueryInterface)(IContinueCallback*, REFIID iid, void** ppvObject);  /* (R1) */
    ULONG (WINAPI *AddRef)(IContinueCallback*);  /* (R1) */
    ULONG (WINAPI *Release)(IContinueCallback*);  /* (R1) */
    HRESULT (WINAPI *FContinue)(IContinueCallback*);  /* ms880185 */
    HRESULT (WINAPI *FContinuePrinting)(IContinueCallback*, LONG cPagesPrinted, LONG nCurrentPage, LPOLESTR pszPrintStatus);  /* ms880191 */
} IContinueCallbackVtbl;
struct IContinueCallback { const IContinueCallbackVtbl *lpVtbl; };
#define IContinueCallback_QueryInterface(T) ((T)->lpVtbl->QueryInterface(T))
#define IContinueCallback_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IContinueCallback_Release(T) ((T)->lpVtbl->Release(T))
#define IContinueCallback_FContinue(T) ((T)->lpVtbl->FContinue(T))
#define IContinueCallback_FContinuePrinting(T,a,b,c) ((T)->lpVtbl->FContinuePrinting(T,a,b,c))

/* ---- IEnumMoniker: vtable order printed by aa515624.html
 *      ("Methods in Vtable Order" tables; method page ids per entry) ---- */
typedef struct IEnumMonikerVtbl {
    HRESULT (WINAPI *QueryInterface)(IEnumMoniker*, REFIID iid, void** ppvObject);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumMoniker*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumMoniker*);  /* (R1) */
    HRESULT (WINAPI *Next)(IEnumMoniker*, ULONG celt, IMoniker*** rgelt, ULONG* pceltFetched);  /* aa515626 */
    HRESULT (WINAPI *Skip)(IEnumMoniker*, ULONG celt);  /* aa515628 */
    HRESULT (WINAPI *Reset)(IEnumMoniker*);  /* aa515627 */
    HRESULT (WINAPI *Clone)(IEnumMoniker*, IEnumMoniker** ppenum);  /* aa515623 */
} IEnumMonikerVtbl;
struct IEnumMoniker { const IEnumMonikerVtbl *lpVtbl; };
#define IEnumMoniker_QueryInterface(T) ((T)->lpVtbl->QueryInterface(T))
#define IEnumMoniker_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumMoniker_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumMoniker_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumMoniker_Skip(T,a) ((T)->lpVtbl->Skip(T,a))
#define IEnumMoniker_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumMoniker_Clone(T,a) ((T)->lpVtbl->Clone(T,a))

/* ---- IMultiQI: vtable order printed by ms882829.html
 *      ("Methods in Vtable Order" tables; method page ids per entry) ---- */
typedef struct IMultiQIVtbl {
    HRESULT (WINAPI *QueryInterface)(IMultiQI*, REFIID iid, void** ppvObject);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMultiQI*);  /* (R1) */
    ULONG (WINAPI *Release)(IMultiQI*);  /* (R1) */
    HRESULT (WINAPI *QueryMultipleInterfaces)(IMultiQI*, ULONG cMQIs, MULTI_QI* pMQIs);  /* ms882837 */
} IMultiQIVtbl;
struct IMultiQI { const IMultiQIVtbl *lpVtbl; };
#define IMultiQI_QueryInterface(T) ((T)->lpVtbl->QueryInterface(T))
#define IMultiQI_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMultiQI_Release(T) ((T)->lpVtbl->Release(T))
#define IMultiQI_QueryMultipleInterfaces(T,a,b) ((T)->lpVtbl->QueryMultipleInterfaces(T,a,b))

/* ---- IRunningObjectTable: vtable order printed by ms884601.html
 *      ("Methods in Vtable Order" tables; method page ids per entry) ---- */
typedef struct IRunningObjectTableVtbl {
    HRESULT (WINAPI *QueryInterface)(IRunningObjectTable*, REFIID iid, void** ppvObject);  /* (R1) */
    ULONG (WINAPI *AddRef)(IRunningObjectTable*);  /* (R1) */
    ULONG (WINAPI *Release)(IRunningObjectTable*);  /* (R1) */
    HRESULT (WINAPI *Register)(IRunningObjectTable*, DWORD grfFlags, IUnknown* punkObject, IMoniker* pmkObjectName, DWORD* pdwRegister);  /* ms884603 */
    HRESULT (WINAPI *Revoke)(IRunningObjectTable*, DWORD dwRegister);  /* ms884604 */
    HRESULT (WINAPI *IsRunning)(IRunningObjectTable*, IMoniker* pmkObjectName);  /* ms884600 */
    HRESULT (WINAPI *GetObject)(IRunningObjectTable*, IMoniker* pmkObjectName, IUnknown** ppunkObject);  /* ms884597 */
    HRESULT (WINAPI *NoteChangeTime)(IRunningObjectTable*, DWORD dwRegister, FILETIME* pfiletime);  /* ms884602 */
    HRESULT (WINAPI *GetTimeOfLastChange)(IRunningObjectTable*, IMoniker* pmkObjectName, FILETIME* pfiletime);  /* ms884598 */
    HRESULT (WINAPI *EnumRunning)(IRunningObjectTable*, IEnumMoniker** ppenumMoniker);  /* ms884596 */
} IRunningObjectTableVtbl;
struct IRunningObjectTable { const IRunningObjectTableVtbl *lpVtbl; };
#define IRunningObjectTable_QueryInterface(T) ((T)->lpVtbl->QueryInterface(T))
#define IRunningObjectTable_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IRunningObjectTable_Release(T) ((T)->lpVtbl->Release(T))
#define IRunningObjectTable_Register(T,a,b,c,d) ((T)->lpVtbl->Register(T,a,b,c,d))
#define IRunningObjectTable_Revoke(T,a) ((T)->lpVtbl->Revoke(T,a))
#define IRunningObjectTable_IsRunning(T,a) ((T)->lpVtbl->IsRunning(T,a))
#define IRunningObjectTable_GetObject(T,a,b) ((T)->lpVtbl->GetObject(T,a,b))
#define IRunningObjectTable_NoteChangeTime(T,a,b) ((T)->lpVtbl->NoteChangeTime(T,a,b))
#define IRunningObjectTable_GetTimeOfLastChange(T,a,b) ((T)->lpVtbl->GetTimeOfLastChange(T,a,b))
#define IRunningObjectTable_EnumRunning(T,a) ((T)->lpVtbl->EnumRunning(T,a))

#endif /* AKARI_OBJBASE_H */
