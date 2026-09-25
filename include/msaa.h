/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSAA_H
#define WCE_MSAA_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI xNotifyWinEvent(DWORD dwEvent, HWND hWnd, LONG idObject, LONG idChild) WCE_LINK(xNotifyWinEvent);

#ifdef __cplusplus
}
#endif
#endif

