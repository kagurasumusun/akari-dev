/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WABAPI_H
#define WCE_WABAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWAB_PARAM { ULONG cbSize; HWND hwnd; LPSTR szFileName; ULONG ulFlags; GUID guidPSExt; } WAB_PARAM, *PWAB_PARAM, *LPWAB_PARAM;

WCE_IMPORT BOOL WINAPI WABInitThread() WCE_LINK(WABInitThread);

#ifdef __cplusplus
}
#endif
#endif

