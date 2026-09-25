/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_NOTIFY_H
#define WCE_NOTIFY_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI CeGetUserNotificationPreferences(HWND hWndParent, PCE_USER_NOTIFICATION lpNotification) WCE_LINK(CeGetUserNotificationPreferences);
WCE_IMPORT BOOL WINAPI CeClearUserNotification(HANDLE hNotification) WCE_LINK(CeClearUserNotification);
WCE_IMPORT BOOL WINAPI CeGetUserNotification(HANDLE hNotification, DWORD cBufferSize, LPDWORD pcBytesNeeded, LPBYTE pBuffer) WCE_LINK(CeGetUserNotification);
WCE_IMPORT BOOL WINAPI CeGetUserNotificationHandles(HANDLE *rghNotifications, DWORD cHandles, LPDWORD pcHandlesNeeded) WCE_LINK(CeGetUserNotificationHandles);

#ifdef __cplusplus
}
#endif
#endif

