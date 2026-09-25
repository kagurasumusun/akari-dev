/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WTYPES_H
#define WCE_WTYPES_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLOGPALETTE { WORD palVersion; WORD palNumEntries; PALETTEENTRY palPalEntry[ 1 ]; } LOGPALETTE, *PLOGPALETTE, *LPLOGPALETTE;
typedef struct tagRECTL { LONG left; LONG top; LONG right; LONG bottom; } RECTL, *PRECTL, *LPRECTL;
typedef struct tagPOINTL { LONG x; LONG y; } POINTL, *PPOINTL, *LPPOINTL;
typedef struct tagSIZEL { LONG cx; LONG cy; } SIZEL, *PSIZEL, *LPSIZEL;
typedef struct tagCOAUTHIDENTITY { USHORT *User; ULONG UserLength; USHORT *Domain; ULONG DomainLength; USHORT *Password; ULONG PasswordLength; ULONG Flags; } COAUTHIDENTITY, *PCOAUTHIDENTITY, *LPCOAUTHIDENTITY;
typedef struct tagCOAUTHINFO { DWORD dwAuthnSvc; DWORD dwAuthzSvc; LPWSTR pwszServerPrincName; DWORD dwAuthnLevel; DWORD dwImpersonationLevel; COAUTHIDENTITY *pAuthIdentityData; DWORD dwCapabilities; } COAUTHINFO, *PCOAUTHINFO, *LPCOAUTHINFO;
typedef struct tagCOSERVERINFO { DWORD dwReserved1; LPWSTR pwszName; COAUTHINFO *pAuthInfo; DWORD dwReserved2; } COSERVERINFO, *PCOSERVERINFO, *LPCOSERVERINFO;
typedef struct tagOBJECTID { GUID Lineage; unsigned long Uniquifier; } OBJECTID, *POBJECTID, *LPOBJECTID;
typedef struct tagWORD_BLOB { unsigned long clSize; unsigned short asData[ 1 ]; } WORD_BLOB, *PWORD_BLOB, *LPWORD_BLOB;
typedef struct tagDWORD_BLOB { unsigned long clSize; unsigned long alData[ 1 ]; } DWORD_BLOB, *PDWORD_BLOB, *LPDWORD_BLOB;
typedef struct tagFLAGGED_WORD_BLOB { unsigned long fFlags; unsigned long clSize; unsigned short asData[ 1 ]; } FLAGGED_WORD_BLOB, *PFLAGGED_WORD_BLOB, *LPFLAGGED_WORD_BLOB;
typedef struct tagWORD_SIZEDARR { unsigned long clSize; unsigned short *pData; } WORD_SIZEDARR, *PWORD_SIZEDARR, *LPWORD_SIZEDARR;
typedef struct tagDWORD_SIZEDARR { unsigned long clSize; unsigned long *pData; } DWORD_SIZEDARR, *PDWORD_SIZEDARR, *LPDWORD_SIZEDARR;
typedef struct tagrpcLOGPALETTE { WORD palVersion; WORD palNumEntries; PALETTEENTRY palPalEntry[ 1 ]; } rpcLOGPALETTE, *PrpcLOGPALETTE, *LPrpcLOGPALETTE;
typedef struct tagDECIMAL { USHORT wReserved; BYTE scale; BYTE sign; ULONG Hi32; ULONGLONG Lo64; } DECIMAL, *PDECIMAL, *LPDECIMAL;
typedef struct tagBSTRBLOB { ULONG cbSize; BYTE *pData; } BSTRBLOB, *PBSTRBLOB, *LPBSTRBLOB;
typedef struct tagBLOB { ULONG cbSize; BYTE *pBlobData; } BLOB, *PBLOB, *LPBLOB;
typedef struct tagCLIPDATA { ULONG cbSize; long ulClipFmt; BYTE *pClipData; } CLIPDATA, *PCLIPDATA, *LPCLIPDATA;


#ifdef __cplusplus
}
#endif
#endif

