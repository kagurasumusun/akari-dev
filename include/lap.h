/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_LAP_H
#define WCE_LAP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagInitLap { DWORD size; DWORD capabilities; } InitLap, *PInitLap, *LPInitLap;

#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI InitLAP(InitLap *il) WCE_LINK(InitLAP);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT void WINAPI DeinitLAP() WCE_LINK(DeinitLAP);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI VerifyUser(const GUID *AEKey, LPCWSTR pwszAEDisplayText, HWND hWndParent, DWORD dwOptions, PVOID pExtended) WCE_LINK(VerifyUser);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI LAPCreateEnrollmentConfigDialog(HWND hParentWindow,DWORD dwOptions) WCE_LINK(LAPCreateEnrollmentConfigDialog);
#endif

#ifdef __cplusplus
}
#endif
#endif

