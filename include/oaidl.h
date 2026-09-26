/*
 * oaidl.h -- OLE Automation for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * This header carries the automation base types -- BSTR, VARIANT, SAFEARRAY,
 * the dispid and exception records, the automation interfaces -- and the
 * application-facing prototypes of oleaut32.dll.
 */
#ifndef AKARI_WCE_OAIDL_H
#define AKARI_WCE_OAIDL_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <winbase.h>   /* SYSTEMTIME, used by SystemTimeToVariantTime */
#include <wtypes.h>
#include <unknwn.h>

#ifndef _OAIDL_
#define _OAIDL_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINOLEAUTAPI
#define WINOLEAUTAPI         AKARI_DLLIMPORT
#define WINOLEAUTAPI_(t)     AKARI_DLLIMPORT t
#define WINOLEAUT            AKARI_DLLIMPORT
#endif

/* CE declares these RPC helper qualifiers but leaves them empty; __RPC_USER
   follows STDMETHODCALLTYPE, which is __cdecl on every CE CPU. */
#ifndef __RPC_FAR
#define __RPC_FAR
#endif
#ifndef __RPC_USER
#define __RPC_USER
#endif
#ifndef __RPC_STUB
#define __RPC_STUB
#endif

/* The vtbl structs below are written out by hand rather than through
   DECLARE_INTERFACE_, so the two markers need defining here.  DECLARE_INTERFACE_
   in unknwn.h defines the same pair and is guarded, so whichever comes first
   wins and both agree on an empty expansion. */
/* Segmented-pointer macros carried over from 16-bit Windows.  They expand to
   nothing on every 32-bit CE CPU but still appear in the prototypes. */
#ifndef HUGEP
#define HUGEP
#define HUGE
#define __huge
#endif

#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#define END_INTERFACE
#endif

/* --------------------------------------------------- automation basics */

/* Parsed-number record, used by VarParseNumFromStr and VarNumFromParseNum. */
typedef struct akari_tagNUMPARSE {
    INT   cDig;
    ULONG dwInFlags;
    ULONG dwOutFlags;
    INT   cchUsed;
    INT   nBaseShift;
    INT   nPwr10;
} NUMPARSE;

#define NUMPRS_LEADING_WHITE    0x0001
#define NUMPRS_TRAILING_WHITE   0x0002
#define NUMPRS_LEADING_PLUS     0x0004
#define NUMPRS_TRAILING_PLUS    0x0008
#define NUMPRS_LEADING_MINUS    0x0010
#define NUMPRS_TRAILING_MINUS   0x0020
#define NUMPRS_HEX_OCT          0x0040
#define NUMPRS_PARENS           0x0080
#define NUMPRS_DECIMAL          0x0100
#define NUMPRS_THOUSANDS        0x0200
#define NUMPRS_CURRENCY         0x0400
#define NUMPRS_EXPONENT         0x0800
#define NUMPRS_USE_ALL          0x1000
#define NUMPRS_STD  (NUMPRS_LEADING_WHITE|NUMPRS_TRAILING_WHITE| \
                     NUMPRS_LEADING_PLUS|NUMPRS_TRAILING_PLUS| \
                     NUMPRS_LEADING_MINUS|NUMPRS_TRAILING_MINUS| \
                     NUMPRS_HEX_OCT|NUMPRS_PARENS|NUMPRS_DECIMAL| \
                     NUMPRS_THOUSANDS|NUMPRS_CURRENCY|NUMPRS_EXPONENT)
#define NUMPRS_NEG  0x10000
#define NUMPRS_INEXACT 0x20000

/* Broken-down date, used by VarDateFromUdate and VarUdateFromDate. */
typedef struct akari_tagUDATE {
    SYSTEMTIME st;
    USHORT     wDayOfYear;
} UDATE;

typedef short VARIANT_BOOL;
typedef short _VARIANT_BOOL;
typedef VARIANT_BOOL *LPVARIANT_BOOL;
typedef short _bool;
typedef short BOOL16;

typedef double DATE;

typedef struct akari_tagCY {
    LONG lo;
    LONG hi;
} CY;

typedef LONG SCODE;
typedef SCODE *PSCODE;

typedef int   DISPID;
typedef int   MEMBERID;
typedef DISPID *LPDISPID;
#define DISPID_UNKNOWN       (-1)
#define DISPID_VALUE         (0)
#define DISPID_PROPERTY_PUT  (-3)
#define DISPID_NEWENUM       (-4)
#define DISPID_EVALUATE      (-5)
#define DISPID_CONSTRUCTOR   (-6)
#define DISPID_DESTRUCTOR    (-7)
#define DISPID_COLLECT       (-8)

typedef UINT HREFTYPE;

typedef enum akari_tagVARENUM {
    VT_EMPTY        = 0,
    VT_NULL         = 1,
    VT_I2           = 2,
    VT_I4           = 3,
    VT_R4           = 4,
    VT_R8           = 5,
    VT_CY           = 6,
    VT_DATE         = 7,
    VT_BSTR         = 8,
    VT_DISPATCH     = 9,
    VT_ERROR        = 10,
    VT_BOOL         = 11,
    VT_VARIANT      = 12,
    VT_UNKNOWN      = 13,
    VT_DECIMAL      = 14,
    VT_I1           = 16,
    VT_UI1          = 17,
    VT_UI2          = 18,
    VT_UI4          = 19,
    VT_I8           = 20,
    VT_UI8          = 21,
    VT_INT          = 22,
    VT_UINT         = 23,
    VT_VOID         = 24,
    VT_HRESULT      = 25,
    VT_PTR          = 26,
    VT_SAFEARRAY    = 27,
    VT_CARRAY       = 28,
    VT_USERDEFINED  = 29,
    VT_LPSTR        = 30,
    VT_LPWSTR       = 31,
    VT_FILETIME     = 64,
    VT_BLOB         = 65,
    VT_STREAM       = 66,
    VT_STORAGE      = 67,
    VT_STREAMED_OBJECT  = 68,
    VT_STORED_OBJECT    = 69,
    VT_BLOB_OBJECT      = 70,
    VT_CF           = 71,
    VT_CLSID        = 72,
    VT_VECTOR       = 0x1000,
    VT_ARRAY        = 0x2000,
    VT_BYREF        = 0x4000,
    VT_RESERVED     = 0x8000,
    VT_ILLEGAL      = 0xffff,
    VT_ILLEGALMASKED = 0xfff,
    VT_TYPEMASK     = 0xfff
} VARTYPE;

typedef short VT;

typedef struct akari_tagDEC {
    USHORT wReserved;
    union {
        struct { BYTE scale; BYTE sign; };
        USHORT signscale;
    };
    ULONG Hi32;
    union {
        struct { ULONG Lo32; LONG  Mid32; };
        ULONGLONG Lo64;
    };
} DECIMAL;
#define DECIMAL_NEG ((BYTE)0x80)

/* ------------------------------------------------------- safe arrays */

typedef struct akari_tagSAFEARRAYBOUND {
    ULONG cElements;
    LONG  lLbound;
} SAFEARRAYBOUND, *LPSAFEARRAYBOUND;

typedef struct akari_tagSAFEARRAY {
    USHORT        cDims;
    USHORT        fFeatures;
    ULONG         cbElements;
    ULONG         cLocks;
    PVOID         pvData;
    SAFEARRAYBOUND rgsabound[1];
} SAFEARRAY, *LPSAFEARRAY;

#define FADF_AUTO        0x0001
#define FADF_STATIC      0x0002
#define FADF_EMBEDDED    0x0004
#define FADF_FIXEDSIZE   0x0010
#define FADF_RECORD      0x0020
#define FADF_HAVEIID     0x0040
#define FADF_HAVEVARTYPE 0x0080
#define FADF_BSTR        0x0100
#define FADF_UNKNOWN     0x0200
#define FADF_DISPATCH    0x0400
#define FADF_VARIANT     0x0800
#define FADF_RESERVED    0xF008

typedef struct akari_IDispatch IDispatch;
typedef IDispatch *LPDISPATCH;
/* VARIANTARG is a VARIANT by another name; tagVARIANT refers to it, so the
   name has to exist before the struct is closed. */
typedef struct akari_tagVARIANT VARIANTARG;
typedef VARIANTARG *LPVARIANTARG_FWD;

/* ---------------------------------------------------------- VARIANT */

typedef struct akari_tagVARIANT VARIANT;
struct akari_tagVARIANT {
    VARTYPE vt;
    WORD    wReserved1;
    WORD    wReserved2;
    WORD    wReserved3;
    union {
        LONG            lVal;
        BYTE            bVal;
        SHORT           iVal;
        FLOAT           fltVal;
        DOUBLE          dblVal;
        VARIANT_BOOL    boolVal;
        SCODE           scode;
        CY              cyVal;
        DATE            date;
        BSTR            bstrVal;
        IUnknown       *punkVal;
        IDispatch      *pdispVal;
        SAFEARRAY      *parray;
        BYTE           *pbVal;
        SHORT          *piVal;
        LONG           *plVal;
        FLOAT          *pfltVal;
        DOUBLE         *pdblVal;
        VARIANT_BOOL   *pboolVal;
        SCODE          *pscode;
        CY             *pcyVal;
        DATE           *pdate;
        BSTR           *pbstrVal;
        IUnknown      **ppunkVal;
        IDispatch     **ppdispVal;
        SAFEARRAY     **pparray;
        VARIANTARG     *pvarVal;
        PVOID           byref;
        CHAR            cVal;
        USHORT          uiVal;
        ULONG           ulVal;
        INT             intVal;
        UINT            uintVal;
        DECIMAL        *pdecVal;
        CHAR           *pcVal;
        USHORT         *puiVal;
        ULONG          *pulVal;
        INT            *pintVal;
        UINT           *puintVal;
        struct {
            PVOID pvRecord;
            void *pRecInfo;
        };
    };
};

typedef VARIANT *LPVARIANT;
typedef VARIANT VARIANTARG;
typedef VARIANTARG *LPVARIANTARG;

/* -------------------------------------------------- dispatch records */

typedef struct akari_tagDISPPARAMS {
    VARIANTARG *rgvarg;
    DISPID     *rgdispidNamedArgs;
    UINT        cArgs;
    UINT        cNamedArgs;
} DISPPARAMS, *LPDISPPARAMS;

typedef struct akari_tagEXCEPINFO {
    WORD        wCode;
    WORD        wReserved;
    BSTR        bstrSource;
    BSTR        bstrDescription;
    BSTR        bstrHelpFile;
    DWORD       dwHelpContext;
    ULONG_PTR   pvReserved;
    ULONG_PTR   pfnDeferredFillIn;
    SCODE       scode;
} EXCEPINFO, *LPEXCEPINFO;

typedef enum akari_tagDISPID {
    DISPATCH_METHOD         = 0x1,
    DISPATCH_PROPERTYGET    = 0x2,
    DISPATCH_PROPERTYPUT    = 0x4,
    DISPATCH_PROPERTYPUTREF = 0x8
} DISPIDFLAGS;

typedef enum akari_tagDESCKIND {
    DESCKIND_NONE = 0,
    DESCKIND_FUNCDESC,
    DESCKIND_VARDESC,
    DESCKIND_TYPECOMP,
    DESCKIND_IMPLICITAPPOBJ,
    DESCKIND_MAX
} DESCKIND;

typedef struct akari_tagPARAMDESCEX {
    ULONG   cBytes;
    VARIANTARG varDefaultValue;
} PARAMDESCEX, *LPPARAMDESCEX;

typedef struct akari_tagPARAMDESC {
    LPPARAMDESCEX pparamdescex;
    USHORT        wParamFlags;
} PARAMDESC, *LPPARAMDESC;

#define PARAMFLAG_NONE        0
#define PARAMFLAG_FIN         0x1
#define PARAMFLAG_FOUT        0x2
#define PARAMFLAG_FLCID       0x4
#define PARAMFLAG_FRETVAL     0x8
#define PARAMFLAG_FHASDEFAULT 0x20
#define PARAMFLAG_FHASCUSTDATA 0x40

typedef struct akari_tagIDLDESC {
    ULONG_PTR dwReserved;
    USHORT  wIDLFlags;
} IDLDESC, *LPIDLDESC;

/* TYPEDESC and ARRAYDESC are named rather than nested so the anonymous union
   inside TYPEDESC stays legal in C++. */
struct akari_tagTYPEDESC;
typedef struct akari_tagTYPEDESC TYPEDESC;

typedef struct akari_tagARRAYDESC {
    struct akari_tagTYPEDESC *lptdesc;
    ULONG                     cDims;
    SAFEARRAYBOUND            rgbounds[1];
} ARRAYDESC;

struct akari_tagTYPEDESC {
    union {
        struct akari_tagTYPEDESC *lptdesc;
        ARRAYDESC                *lpadesc;
        HREFTYPE                  hreftype;
    };
    VARTYPE vt;
};
typedef TYPEDESC *LPTYPEDESC;

typedef union akari_tagELEMDESC_UNION {
    IDLDESC   idldesc;
    PARAMDESC paramdesc;
} ELEMDESC_UNION;

typedef struct akari_tagELEMDESC {
    TYPEDESC        tdesc;
    ELEMDESC_UNION  u;
} ELEMDESC, *LPELEMDESC;

/* ----------------------------------------------------- forward decls */

typedef struct akari_ITypeInfo ITypeInfo, *LPTYPEINFO;
typedef struct akari_ITypeInfo2 ITypeInfo2, *LPTYPEINFO2;
typedef struct akari_ITypeLib ITypeLib, *LPTYPELIB;
typedef struct akari_ITypeLib2 ITypeLib2, *LPTYPELIB2;
typedef struct akari_ICreateTypeLib ICreateTypeLib, *LPCREATETYPELIB;
typedef struct akari_ICreateTypeLib2 ICreateTypeLib2, *LPCREATETYPELIB2;
typedef struct akari_ICreateTypeInfo ICreateTypeInfo, *LPCREATETYPEINFO;
typedef struct akari_ITypeComp ITypeComp, *LPTYPECOMP;
typedef struct akari_IRecordInfo IRecordInfo, *LPRECORDINFO;
typedef struct akari_IEnumVARIANT IEnumVARIANT, *LPENUMVARIANT;
typedef struct akari_IErrorInfo IErrorInfo, *LPERRORINFO;
typedef struct akari_ICreateErrorInfo ICreateErrorInfo, *LPCREATEERRORINFO;
typedef struct akari_ISupportErrorInfo ISupportErrorInfo, *LPSUPPORTERRORINFO;
typedef struct akari_IFont IFont, *LPFONT;
typedef struct akari_IFontDisp IFontDisp, *LPFONTDISP;
typedef struct akari_IPicture IPicture, *LPPICTURE;
typedef struct akari_IPictureDisp IPictureDisp, *LPPICTUREDISP;
typedef struct akari_IProvideClassInfo IProvideClassInfo, *LPPROVIDECLASSINFO;
typedef struct akari_IConnectionPoint IConnectionPoint, *LPCONNECTIONPOINT;
typedef struct akari_IConnectionPointContainer IConnectionPointContainer, *LPCONNECTIONPOINTCONTAINER;

/* ---------------------------------------------------------- IDispatch */

typedef struct akari_IDispatchVtbl {
    BEGIN_INTERFACE
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDispatch *, REFIID, void **);
    ULONG   (STDMETHODCALLTYPE *AddRef)(IDispatch *);
    ULONG   (STDMETHODCALLTYPE *Release)(IDispatch *);
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(IDispatch *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(IDispatch *, UINT, LCID, ITypeInfo **);
    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(IDispatch *, REFIID, LPOLESTR *, UINT, LCID, DISPID *);
    HRESULT (STDMETHODCALLTYPE *Invoke)(IDispatch *, DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    END_INTERFACE
} IDispatchVtbl;

struct akari_IDispatch { const IDispatchVtbl *lpVtbl; };

#define IDispatch_QueryInterface(p,a,b)   (p)->lpVtbl->QueryInterface(p,a,b)
#define IDispatch_AddRef(p)               (p)->lpVtbl->AddRef(p)
#define IDispatch_Release(p)              (p)->lpVtbl->Release(p)
#define IDispatch_GetTypeInfoCount(p,a)   (p)->lpVtbl->GetTypeInfoCount(p,a)
#define IDispatch_GetTypeInfo(p,a,b,c)    (p)->lpVtbl->GetTypeInfo(p,a,b,c)
#define IDispatch_GetIDsOfNames(p,a,b,c,d,e) (p)->lpVtbl->GetIDsOfNames(p,a,b,c,d,e)
#define IDispatch_Invoke(p,a,b,c,d,e,f,g,h)  (p)->lpVtbl->Invoke(p,a,b,c,d,e,f,g,h)

/* -------------------------------------------- type library descriptors */

typedef enum akari_tagSYSKIND {
    SYS_WIN16 = 0, SYS_WIN32 = 1, SYS_MAC = 2
} SYSKIND;

typedef enum akari_tagLIBFLAGS {
    LIBFLAG_FRESTRICTED   = 0x1,
    LIBFLAG_FCONTROL      = 0x2,
    LIBFLAG_FHIDDEN       = 0x4,
    LIBFLAG_FHASDISKIMAGE = 0x8
} LIBFLAGS;

typedef enum akari_tagTYPEKIND {
    TKIND_ENUM = 0, TKIND_RECORD, TKIND_MODULE, TKIND_INTERFACE,
    TKIND_DISPATCH, TKIND_COCLASS, TKIND_ALIAS, TKIND_UNION, TKIND_MAX
} TYPEKIND;

typedef enum akari_tagCALLCONV {
    CC_FASTCALL = 0, CC_CDECL = 1, CC_MSCPASCAL, CC_PASCAL = CC_MSCPASCAL,
    CC_MACPASCAL, CC_STDCALL, CC_FPFASTCALL, CC_SYSCALL, CC_MPWCDECL,
    CC_MPWPASCAL, CC_MAX
} CALLCONV;

typedef enum akari_tagFUNCKIND {
    FUNC_VIRTUAL = 0, FUNC_PUREVIRTUAL, FUNC_NONVIRTUAL, FUNC_STATIC, FUNC_DISPATCH
} FUNCKIND;

typedef enum akari_tagINVOKEKIND {
    INVOKE_FUNC = 1, INVOKE_PROPERTYGET = 2,
    INVOKE_PROPERTYPUT = 4, INVOKE_PROPERTYPUTREF = 8
} INVOKEKIND;

typedef enum akari_tagTYPEFLAGS {
    TYPEFLAG_FAPPOBJECT   = 0x1,   TYPEFLAG_FCANCREATE   = 0x2,
    TYPEFLAG_FLICENSED    = 0x4,   TYPEFLAG_FPREDECLID   = 0x8,
    TYPEFLAG_FHIDDEN      = 0x10,  TYPEFLAG_FCONTROL     = 0x20,
    TYPEFLAG_FDUAL        = 0x40,  TYPEFLAG_FNONEXTENSIBLE = 0x80,
    TYPEFLAG_FOLEAUTOMATION = 0x100, TYPEFLAG_FRESTRICTED = 0x200,
    TYPEFLAG_FAGGREGATABLE  = 0x400, TYPEFLAG_FREPLACEABLE = 0x800,
    TYPEFLAG_FDISPATCHABLE  = 0x1000, TYPEFLAG_FREVERSEBIND = 0x2000
} TYPEFLAGS;

typedef enum akari_tagFUNCFLAGS {
    FUNCFLAG_FRESTRICTED = 0x1, FUNCFLAG_FSOURCE = 0x2,
    FUNCFLAG_FBINDABLE = 0x4, FUNCFLAG_FREQUESTEDIT = 0x8,
    FUNCFLAG_FDISPLAYBIND = 0x10, FUNCFLAG_FDEFAULTBIND = 0x20,
    FUNCFLAG_FHIDDEN = 0x40, FUNCFLAG_FUSESGETLASTERROR = 0x80,
    FUNCFLAG_FDEFAULTCOLLELEM = 0x100, FUNCFLAG_FUIDEFAULT = 0x200,
    FUNCFLAG_FNONBROWSABLE = 0x400, FUNCFLAG_FREPLACEABLE = 0x800,
    FUNCFLAG_FIMMEDIATEBIND = 0x1000
} FUNCFLAGS;

typedef enum akari_tagVARFLAGS {
    VARFLAG_FREADONLY = 0x1, VARFLAG_FSOURCE = 0x2, VARFLAG_FBINDABLE = 0x4,
    VARFLAG_FREQUESTEDIT = 0x8, VARFLAG_FDISPLAYBIND = 0x10,
    VARFLAG_FDEFAULTBIND = 0x20, VARFLAG_FHIDDEN = 0x40,
    VARFLAG_FRESTRICTED = 0x80, VARFLAG_FDEFAULTCOLLELEM = 0x100,
    VARFLAG_FUIDEFAULT = 0x200, VARFLAG_FNONBROWSABLE = 0x400,
    VARFLAG_FREPLACEABLE = 0x800, VARFLAG_FIMMEDIATEBIND = 0x1000
} VARFLAGS;

typedef enum akari_tagVARKIND {
    VAR_PERINSTANCE = 0, VAR_STATIC, VAR_CONST, VAR_DISPATCH
} VARKIND;

typedef struct akari_tagTYPEATTR {
    GUID         guid;
    LCID         lcid;
    DWORD        dwReserved;
    MEMBERID     memidConstructor;
    MEMBERID     memidDestructor;
    LPSTR        lpstrSchema;
    ULONG        cbSizeInstance;
    TYPEKIND     typekind;
    WORD         cFuncs;
    WORD         cVars;
    WORD         cImplTypes;
    WORD         cbSizeVft;
    WORD         cbAlignment;
    WORD         wTypeFlags;
    WORD         wMajorVerNum;
    WORD         wMinorVerNum;
    TYPEDESC     tdescAlias;
    IDLDESC      idldescType;
} TYPEATTR, *LPTYPEATTR;

typedef struct akari_tagFUNCDESC {
    MEMBERID   memid;
    SCODE     *lprgscode;
    ELEMDESC  *lprgelemdescParam;
    FUNCKIND   funckind;
    INVOKEKIND invkind;
    CALLCONV   callconv;
    SHORT      cParams;
    SHORT      cParamsOpt;
    SHORT      oVft;
    SHORT      cScodes;
    ELEMDESC   elemdescFunc;
    WORD       wFuncFlags;
} FUNCDESC, *LPFUNCDESC;

typedef struct akari_tagVARDESC {
    MEMBERID   memid;
    LPSTR      lpstrSchema;
    union {
        ULONG oInst;
        VARIANT *lpvarValue;
    };
    ELEMDESC   elemdescVar;
    WORD       wVarFlags;
    VARKIND    varkind;
} VARDESC, *LPVARDESC;

#define MEMBERID_NIL ((MEMBERID)(-1))

typedef struct akari_tagCLIPDATA {
    ULONG  cbSize;
    LONG   ulClipFmt;
    BYTE  *pClipData;
} CLIPDATA;

/* PROPVARIANT is a VARIANT with a few extra members for the property system.
   It has the same size and the same leading fields, so a PROPVARIANT can be
   passed where a VARIANT is expected. */
typedef struct akari_tag_inner_PROPVARIANT {
    VARTYPE vt;
    WORD    wReserved1;
    WORD    wReserved2;
    WORD    wReserved3;
    union {
        LONG            lVal;
        BYTE            bVal;
        SHORT           iVal;
        FLOAT           fltVal;
        DOUBLE          dblVal;
        VARIANT_BOOL    boolVal;
        SCODE           scode;
        CY              cyVal;
        DATE            date;
        BSTR            bstrVal;
        IUnknown       *punkVal;
        IDispatch      *pdispVal;
        SAFEARRAY      *parray;
        BLOB            blob;
        CHAR           *pszVal;
        WCHAR          *pwszVal;
        CLIPDATA       *pclipdata;
        VARIANTARG     *pvarVal;
        PVOID           byref;
        CHAR            cVal;
        USHORT          uiVal;
        ULONG           ulVal;
        INT             intVal;
        UINT            uintVal;
        DECIMAL         decVal;
        DECIMAL        *pdecVal;
        CHAR           *pcVal;
        USHORT         *puiVal;
        ULONG          *pulVal;
        INT            *pintVal;
        UINT           *puintVal;
    };
} PROPVARIANT;
typedef PROPVARIANT *LPPROPVARIANT;

/* ---------------------------------------------------- error interface */

typedef struct akari_IErrorInfoVtbl {
    BEGIN_INTERFACE
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IErrorInfo *, REFIID, void **);
    ULONG   (STDMETHODCALLTYPE *AddRef)(IErrorInfo *);
    ULONG   (STDMETHODCALLTYPE *Release)(IErrorInfo *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(IErrorInfo *, GUID *);
    HRESULT (STDMETHODCALLTYPE *GetSource)(IErrorInfo *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(IErrorInfo *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetHelpFile)(IErrorInfo *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetHelpContext)(IErrorInfo *, ULONG *);
    END_INTERFACE
} IErrorInfoVtbl;

struct akari_IErrorInfo { const IErrorInfoVtbl *lpVtbl; };

/* The WINOLEAUTAPI entry points are declared in oleauto.h, which is where
 * the CE SDK puts them.  This header declares the automation types.
 */

#ifdef __cplusplus
}
#endif

#endif /* _OAIDL_ */
#endif /* AKARI_WCE_OAIDL_H */
