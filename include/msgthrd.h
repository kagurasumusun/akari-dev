/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSGTHRD_H
#define WCE_MSGTHRD_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT DWORD WINAPI DefaultThreadProc(LPVOID lpParam) WCE_LINK(DefaultThreadProc);
WCE_IMPORT BOOL WINAPI CreateThread() WCE_LINK(CreateThread);
WCE_IMPORT int WINAPI GetThreadPriority() WCE_LINK(GetThreadPriority);
WCE_IMPORT BOOL WINAPI SetThreadPriority(int nPriority) WCE_LINK(SetThreadPriority);

#ifdef __cplusplus
}
#endif
#endif

