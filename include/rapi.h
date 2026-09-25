/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RAPI_H
#define WCE_RAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSTORE_INFORMATION { DWORD dwStoreSize; DWORD dwFreeSize; } STORE_INFORMATION, *PSTORE_INFORMATION, *LPSTORE_INFORMATION;
typedef struct tagCEGUID { DWORD Data1; DWORD Data2; DWORD Data3; DWORD Data4; } CEGUID, *PCEGUID, *LPCEGUID;
typedef struct tagCENOTIFYREQUEST { DWORD dwSize; HWND hwnd; DWORD dwFlags; HANDLE hHeap; DWORD dwParam; } CENOTIFYREQUEST, *PCENOTIFYREQUEST, *LPCENOTIFYREQUEST;
typedef struct tagCEBLOB { DWORD dwCount; LPBYTE lpb; } CEBLOB, *PCEBLOB, *LPCEBLOB;
typedef struct tagCEOSVERSIONINFO { DWORD dwOSVersionInfoSize; DWORD dwMajorVersion; DWORD dwMinorVersion; DWORD dwBuildNumber; DWORD dwPlatformId; WCHAR szCSDVersion[ 128 ]; } CEOSVERSIONINFO, *PCEOSVERSIONINFO, *LPCEOSVERSIONINFO;
typedef struct tagSYSTEM_POWER_STATUS_EX { BYTE ACLineStatus; BYTE BatteryFlag; BYTE BatteryLifePercent; BYTE Reserved1; DWORD BatteryLifeTime; DWORD BatteryFullLifeTime; BYTE Reserved2; BYTE BackupBatteryFlag; BYTE BackupBatteryLifePercent; BYTE Reserved3; DWORD BackupBatteryLifeTime; DWORD BackupBatteryFullLifeTime; } SYSTEM_POWER_STATUS_EX, *PSYSTEM_POWER_STATUS_EX, *LPSYSTEM_POWER_STATUS_EX;
typedef struct tagRAPIINIT { DWORD cbSize; HANDLE heRapiInit; HRESULT hrRapiInit; } RAPIINIT, *PRAPIINIT, *LPRAPIINIT;

WCE_IMPORT HRESULT WINAPI CeRapiInitEx(RAPIINIT*) WCE_LINK(CeRapiInitEx);
WCE_IMPORT HRESULT WINAPI CeRapiInit() WCE_LINK(CeRapiInit);
WCE_IMPORT HRESULT WINAPI CeRapiUninit() WCE_LINK(CeRapiUninit);
WCE_IMPORT HRESULT WINAPI CeRapiGetError(void) WCE_LINK(CeRapiGetError);
WCE_IMPORT HRESULT WINAPI CeRapiFreeBuffer(LPVOID) WCE_LINK(CeRapiFreeBuffer);

#ifdef __cplusplus
}
#endif
#endif

