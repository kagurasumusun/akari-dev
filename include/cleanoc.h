/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CLEANOC_H
#define WCE_CLEANOC_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI FindControlClose(HANDLE hFindHandle) WCE_LINK(FindControlClose);
WCE_IMPORT void WINAPI ReleaseControlHandle(HANDLE hControlHandle) WCE_LINK(ReleaseControlHandle);
WCE_IMPORT BOOL WINAPI GetControlInfo(HANDLE hControlHandle, UINT nFlag, LPDWORD lpdwData, LPTSTR lpszBuf, int nBufLen) WCE_LINK(GetControlInfo);
WCE_IMPORT BOOL WINAPI IsModuleRemovable(LPCTSTR lpszFile) WCE_LINK(IsModuleRemovable);
WCE_IMPORT HRESULT WINAPI RemoveExpiredControls(DWORD dwFlags, DWORD dwReserved) WCE_LINK(RemoveExpiredControls);

#ifdef __cplusplus
}
#endif
#endif

