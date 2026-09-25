/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ERRORS_H
#define WCE_ERRORS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT DWORD WINAPI AMGetErrorTextW(HRESULT hr , WCHAR *pbuffer , DWORD MaxLen) WCE_LINK(AMGetErrorTextW);
WCE_IMPORT DWORD WINAPI AMGetErrorTextA(HRESULT hr , char *pbuffer , DWORD MaxLen) WCE_LINK(AMGetErrorTextA);

#define AMGetErrorText AMGetErrorTextW
#ifdef __cplusplus
}
#endif
#endif

