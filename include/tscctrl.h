/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_TSCCTRL_H
#define WCE_TSCCTRL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI InitializeTSC(HINSTANCE hInst) WCE_LINK(InitializeTSC);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI UninitializeTSC() WCE_LINK(UninitializeTSC);
#endif

#ifdef __cplusplus
}
#endif
#endif

