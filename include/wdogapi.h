/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WDOGAPI_H
#define WCE_WDOGAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI CreateWatchDogTimer(LPCWSTR pszWatchDogName, DWORD dwPeriod, DWORD dwWait, DWORD dwDfltAction, DWORD dwParam, DWORD dwFlags) WCE_LINK(CreateWatchDogTimer);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI OpenWatchDogTimer(LPCWSTR pszWatchDogName, DWORD dwFlags) WCE_LINK(OpenWatchDogTimer);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI StartWatchDogTimer(HANDLE hWatchDog, DWORD dwFlags) WCE_LINK(StartWatchDogTimer);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI StopWatchDogTimer(HANDLE hWatchDog, DWORD dwFlags) WCE_LINK(StopWatchDogTimer);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI RefreshWatchDogTimer(HANDLE hWatchDog, DWORD dwFlags) WCE_LINK(RefreshWatchDogTimer);
#endif

#ifdef __cplusplus
}
#endif
#endif

