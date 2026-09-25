/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ASTDTAPI_H
#define WCE_ASTDTAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT LONG WINAPI tapiRequestMakeCallW(LPCWSTR lpszDestAddress, LPCWSTR lpszAppName, LPCWSTR lpszCalledParty, LPCWSTR lpszComment) WCE_LINK(tapiRequestMakeCallW);
#endif

#define tapiRequestMakeCall tapiRequestMakeCallW
#ifdef __cplusplus
}
#endif
#endif

