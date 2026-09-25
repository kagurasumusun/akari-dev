/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_LASS_H
#define WCE_LASS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagAuthenticationEvent { GUID AEKey; LPWSTR Name; int FrequencyType; int FrequencyValue; } AuthenticationEvent, *PAuthenticationEvent, *LPAuthenticationEvent;

#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI VerifyUser(const GUID *AEKey, LPCWSTR wszAEDisplayText, HWND hWndParent, DWORD dwOptions, PVOID pExtended) WCE_LINK(VerifyUser);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI LASSReloadConfig() WCE_LINK(LASSReloadConfig);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CreateEnrollmentConfigDialog(HWND hParentWindow) WCE_LINK(CreateEnrollmentConfigDialog);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI LASSGetValue(DWORD ValueId,PVOID lpvOutBuffer, DWORD cbOutBuffer, DWORD* pcbReturned) WCE_LINK(LASSGetValue);
#endif

#ifdef __cplusplus
}
#endif
#endif

