/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_KFUNCS_H
#define WCE_KFUNCS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI EventModify(HANDLE hEvent, DWORD func) WCE_LINK(EventModify);
WCE_IMPORT DWORD WINAPI TlsCall(DWORD p1, DWORD p2) WCE_LINK(TlsCall);
WCE_IMPORT DWORD WINAPI CeGetCurrentTrust(void) WCE_LINK(CeGetCurrentTrust);
WCE_IMPORT DWORD WINAPI CeGetCallerTrust(void) WCE_LINK(CeGetCallerTrust);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI CeGetProcessTrust(HANDLE hProc) WCE_LINK(CeGetProcessTrust);
#endif

#ifdef __cplusplus
}
#endif
#endif

