/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DEVMGMT_H
#define WCE_DEVMGMT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDMTASKINFO { DWORD dwSize; SYSTEMTIME stStartTime; SYSTEMTIME stDeltaTime; SYSTEMTIME stRetryTime; DWORD dwType; DWORD dwMaxRetryTime; DWORD dwFlags; LPTSTR pwzRDN; LPTSTR pwzURL; LPTSTR pwzURLSig; LPTSTR pwzMisc; LPTSTR pwzData; LPTSTR pwzXml; } DMTASKINFO, *PDMTASKINFO, *LPDMTASKINFO;
typedef struct tagDMSINVHEADER { DWORD dwMagic; DWORD dwRecSize; DWORD dwRecNumber; DWORD dwReserved; } DMSINVHEADER, *PDMSINVHEADER, *LPDMSINVHEADER;

WCE_IMPORT HRESULT WINAPI CeSetDevMgmtTask(PDMTASKINFO pdi) WCE_LINK(CeSetDevMgmtTask);
WCE_IMPORT HRESULT WINAPI CeGetDevMgmtPackageList(PDMSINVRECORD pRecord, LPDWORD pdwEntryNumber, DWORD dwFilter) WCE_LINK(CeGetDevMgmtPackageList);
WCE_IMPORT HRESULT WINAPI CeSetDevMgmtPackageList(PDMSINVRECORD pRecord, DWORD dwFlags) WCE_LINK(CeSetDevMgmtPackageList);

#ifdef __cplusplus
}
#endif
#endif

