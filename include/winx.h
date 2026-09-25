/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINX_H
#define WCE_WINX_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LPSTR WINAPI lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength) WCE_LINK(lstrcpynA);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI FileTimeToDosDateTime(CONST FILETIME *lpFileTime, LPWORD lpFatDate, LPWORD lpFatTime) WCE_LINK(FileTimeToDosDateTime);
#endif

#ifdef __cplusplus
}
#endif
#endif

