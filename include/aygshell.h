/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_AYGSHELL_H
#define WCE_AYGSHELL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI SHSetInputContext(HWND hwnd, DWORD dwFeature, const LPVOID lpValue) WCE_LINK(SHSetInputContext);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI SHGetInputContext(HWND hwnd, DWORD dwFeature, LPVOID lpValue, LPDWORD lpdwSize) WCE_LINK(SHGetInputContext);
#endif

#ifdef __cplusplus
}
#endif
#endif

