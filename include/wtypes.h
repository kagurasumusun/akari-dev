/*
 * wtypes.h -- fundamental OLE Automation and COM types for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * Types are declared in their Windows CE form, which is not always the desktop
 * form.
 */
#ifndef AKARI_WCE_WTYPES_H
#define AKARI_WCE_WTYPES_H

#include <windef.h>
#include <winnt.h>
#include <guiddef.h>
#include <winerror.h>


#ifndef _WTYPES_
#define _WTYPES_

#ifdef __cplusplus
extern "C" {
#endif

/* OLE strings are 16-bit on every CE target. */
#ifndef OLECHAR_DEFINED
#define OLECHAR_DEFINED
typedef WCHAR OLECHAR;
typedef OLECHAR *LPOLESTR;
typedef const OLECHAR *LPCOLESTR;
#endif

#ifndef BSTR_DEFINED
#define BSTR_DEFINED
typedef OLECHAR *BSTR;
typedef BSTR *LPBSTR;
#endif

/* CLSID, IID, GUID and REFGUID come from guiddef.h. */

/* Enhanced metafile handle; declared here so STGMEDIUM does not depend on
   the GDI header. */
#ifndef HENHMETAFILE_DEFINED
#define HENHMETAFILE_DEFINED
typedef HANDLE HENHMETAFILE;
#endif

/* Clipboard formats.  CE uses the same 16-bit base as the desktop. */
typedef WORD CLIPFORMAT;
typedef CLIPFORMAT *LPCLIPFORMAT;

#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14
#define CF_HDROP            15
#define CF_LOCALE           16
#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF
#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF

/* The transfer medium used by IDataObject and the OLE clipboard. */
typedef struct akari_STGMEDIUM {
    DWORD   tymed;
    union {
        HBITMAP       hBitmap;
        PVOID         hMetaFilePict;
        HENHMETAFILE  hEnhMetaFile;
        HGLOBAL       hGlobal;
        LPOLESTR      lpszFileName;
        struct akari_IStream      *pstm;
        struct akari_IStorage     *pstg;
    } u;
    struct akari_IUnknown *pUnkForRelease;
} STGMEDIUM, *LPSTGMEDIUM;

typedef STGMEDIUM USTGMEDIUM;
typedef USTGMEDIUM *LPUSTGMEDIUM;

#define TYMED_HGLOBAL   1
#define TYMED_FILE      2
#define TYMED_ISTREAM   4
#define TYMED_ISTORAGE  8
#define TYMED_GDI       16
#define TYMED_MFPICT    32
#define TYMED_ENHMF     64
#define TYMED_NULL      0

/* Format descriptor pairing a clipboard format with a target device. */
typedef struct akari_FORMATETC {
    CLIPFORMAT  cfFormat;
    void       *ptd;
    DWORD       dwAspect;
    LONG        lindex;
    DWORD       tymed;
} FORMATETC, *LPFORMATETC;

#define DVASPECT_CONTENT    1
#define DVASPECT_THUMBNAIL  2
#define DVASPECT_ICON       4
#define DVASPECT_DOCPRINT   8

#define STATFLAG_DEFAULT    0
#define STATFLAG_NONAME     1
#define STATFLAG_NOSEEK     2

/* Storage element types, shared with objidl.h. */
#define STGTY_STORAGE   1
#define STGTY_STREAM    2
#define STGTY_LOCKBYTES 3
#define STGTY_PROPERTY  4

#define STREAM_SEEK_SET     0
#define STREAM_SEEK_CUR     1
#define STREAM_SEEK_END     2

#define STGM_READ           0x00000000
#define STGM_WRITE          0x00000001
#define STGM_READWRITE      0x00000002
#define STGM_SHARE_DENY_NONE 0x00000040
#define STGM_SHARE_DENY_READ 0x00000030
#define STGM_SHARE_DENY_WRITE 0x00000020
#define STGM_SHARE_EXCLUSIVE 0x00000010
#define STGM_PRIORITY       0x00040000
#define STGM_CREATE         0x00001000
#define STGM_CONVERT        0x00020000
#define STGM_FAILIFTHERE    0x00000000
#define STGM_DIRECT         0x00000000
#define STGM_TRANSACTED     0x00010000
#define STGM_NOSCRATCH      0x00100000
#define STGM_NOSNAPSHOT     0x00200000
#define STGM_DELETEONRELEASE 0x04000000

/* Contexts in which a class object may be created. */
#define CLSCTX_INPROC_SERVER        0x1
#define CLSCTX_INPROC_HANDLER       0x2
#define CLSCTX_LOCAL_SERVER         0x4
#define CLSCTX_INPROC_SERVER16      0x8
#define CLSCTX_REMOTE_SERVER        0x10
#define CLSCTX_INPROC_HANDLER16     0x20
#define CLSCTX_NO_CODE_DOWNLOAD     0x400
#define CLSCTX_NO_CUSTOM_MARSHAL    0x1000
#define CLSCTX_ENABLE_CODE_DOWNLOAD 0x2000
#define CLSCTX_NO_FAILURE_LOG       0x4000
#define CLSCTX_DISABLE_AAA          0x8000
#define CLSCTX_SERVER               (CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER)
#define CLSCTX_ALL                  (CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER)

/* CoInitializeEx apartment and threading options. */
#define COINIT_APARTMENTTHREADED    0x2
#define COINIT_MULTITHREADED        0x0
#define COINIT_DISABLE_OLE1DDE      0x4
#define COINIT_SPEED_OVER_MEMORY    0x8

#define REGCLS_SINGLEUSE        0
#define REGCLS_MULTIPLEUSE      1
#define REGCLS_MULTI_SEPARATE   2
#define REGCLS_SUSPENDED        4
#define REGCLS_SURROGATE        8

#define MARSHALINTERFACE_MIN 500

#define MEMCTX_TASK     1
#define MEMCTX_SHARED   2
#define MEMCTX_MACSYSTEM 3
#define MEMCTX_UNKNOWN  -1
#define MEMCTX_SAME     -2
#define MEMCTX_LOCAL    -3

#define MSFTCALLCONV_CDECL      0
#define MSFTCALLCONV_PASCAL     1

#define OLERENDER_NONE      0
#define OLERENDER_DRAW      1
#define OLERENDER_FORMAT    2
#define OLERENDER_ASIS      3

#define DATADIR_GET   1
#define DATADIR_SET   2

/* Task handle, used by the message filter. */
typedef void *HTASK;

/* Server-side name binding: a null-terminated array of name pointers. */
typedef OLECHAR **SNB;

/* Security descriptor, used by the DCOM entry points. */
typedef void *PSECURITY_DESCRIPTOR;

/* BLOB, as used by the property system and by PROPVARIANT. */
typedef struct akari_tagBLOB {
    ULONG cbSize;
    BYTE *pBlobData;
} BLOB, *LPBLOB;

#ifdef __cplusplus
}
#endif

#endif /* _WTYPES_ */
#endif /* AKARI_WCE_WTYPES_H */
