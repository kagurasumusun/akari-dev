/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CPROP_H
#define WCE_CPROP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT INT_PTR WINAPI DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) WCE_LINK(DialogProc);

#ifdef __cplusplus
}
#endif
#endif

