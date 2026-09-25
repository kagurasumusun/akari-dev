/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINDBASE_H
#define WCE_WINDBASE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCEGUID { DWORD Data1; DWORD Data2; DWORD Data3; DWORD Data4; } CEGUID, *PCEGUID, *LPCEGUID;
typedef struct tagCENOTIFYREQUEST { DWORD dwSize; HWND hwnd; DWORD dwFlags; HANDLE hHeap; DWORD dwParam; } CENOTIFYREQUEST, *PCENOTIFYREQUEST, *LPCENOTIFYREQUEST;
typedef struct tagSTORE_INFORMATION { DWORD dwStoreSize; DWORD dwFreeSize; } STORE_INFORMATION, *PSTORE_INFORMATION, *LPSTORE_INFORMATION;
typedef struct tagCEBLOB { DWORD dwCount; LPBYTE lpb; } CEBLOB, *PCEBLOB, *LPCEBLOB;

WCE_IMPORT BOOL WINAPI GetStoreInformation(LPSTORE_INFORMATION lpsi) WCE_LINK(GetStoreInformation);
WCE_IMPORT HANDLE WINAPI CeFindFirstDatabase(DWORD dwClassID) WCE_LINK(CeFindFirstDatabase);
WCE_IMPORT BOOL WINAPI CeGetDBInformationByHandle(HANDLE hDbase, LPBY_HANDLE_DB_INFORMATION lpDBInfo) WCE_LINK(CeGetDBInformationByHandle);
WCE_IMPORT HANDLE WINAPI CeFindFirstDatabaseEx(PCEGUID pguid, DWORD dwClassID) WCE_LINK(CeFindFirstDatabaseEx);
WCE_IMPORT BOOL WINAPI CeMountDBVol(PCEGUID pguid, LPWSTR lpszVol, DWORD dwFlags) WCE_LINK(CeMountDBVol);
WCE_IMPORT BOOL WINAPI CeUnmountDBVol(PCEGUID pguid) WCE_LINK(CeUnmountDBVol);
WCE_IMPORT BOOL WINAPI CeFlushDBVol(PCEGUID pguid) WCE_LINK(CeFlushDBVol);
WCE_IMPORT BOOL WINAPI CeEnumDBVolumes(PCEGUID pguid, LPWSTR lpBuf, DWORD dwSize) WCE_LINK(CeEnumDBVolumes);
WCE_IMPORT BOOL WINAPI CeFreeNotification(PCENOTIFYREQUEST pRequest, PCENOTIFICATION pNotify) WCE_LINK(CeFreeNotification);
WCE_IMPORT VOID WINAPI CeChangeDatabaseLCID(PCEGUID pguid, DWORD LCID) WCE_LINK(CeChangeDatabaseLCID);

#ifdef __cplusplus
}
#endif
#endif

