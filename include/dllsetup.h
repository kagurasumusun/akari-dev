/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DLLSETUP_H
#define WCE_DLLSETUP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI AMovieDllRegisterServer2(BOOL) WCE_LINK(AMovieDllRegisterServer2);
WCE_IMPORT HRESULT WINAPI AMovieDllRegisterServer() WCE_LINK(AMovieDllRegisterServer);
WCE_IMPORT HRESULT WINAPI AMovieDllUnregisterServer() WCE_LINK(AMovieDllUnregisterServer);
WCE_IMPORT HRESULT WINAPI EliminateSubKey(HKEY, LPTSTR) WCE_LINK(EliminateSubKey);

#ifdef __cplusplus
}
#endif
#endif

