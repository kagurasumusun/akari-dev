/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SIPAPI_H
#define WCE_SIPAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSIPINFO { DWORD cbSize; DWORD fdwFlags; RECT rcVisibleDesktop; RECT rcSipRect; DWORD dwImDataSize; void *pvImData; } SIPINFO, *PSIPINFO, *LPSIPINFO;
typedef struct tagIMWINDOWPOS { int x; int y; int cx; int cy; } IMWINDOWPOS, *PIMWINDOWPOS, *LPIMWINDOWPOS;

WCE_IMPORT DWORD WINAPI SipStatus() WCE_LINK(SipStatus);
WCE_IMPORT BOOL WINAPI SipSetDefaultRect(RECT *) WCE_LINK(SipSetDefaultRect);
WCE_IMPORT BOOL WINAPI SipRegisterNotification(HWND) WCE_LINK(SipRegisterNotification);
WCE_IMPORT BOOL WINAPI SipShowIM(DWORD) WCE_LINK(SipShowIM);
WCE_IMPORT BOOL WINAPI SipGetInfo(SIPINFO *) WCE_LINK(SipGetInfo);
WCE_IMPORT BOOL WINAPI SipSetInfo(SIPINFO *) WCE_LINK(SipSetInfo);
WCE_IMPORT BOOL WINAPI SipGetCurrentIM(CLSID *) WCE_LINK(SipGetCurrentIM);
WCE_IMPORT BOOL WINAPI SipSetCurrentIM(CLSID *) WCE_LINK(SipSetCurrentIM);

#ifdef __cplusplus
}
#endif
#endif

