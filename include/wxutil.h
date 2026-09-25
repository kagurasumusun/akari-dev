/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WXUTIL_H
#define WCE_WXUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI DbgLockTrace(BOOL fTrace) WCE_LINK(DbgLockTrace);
WCE_IMPORT DWORD WINAPI InitialThreadProc(LPVOID pv) WCE_LINK(InitialThreadProc);
WCE_IMPORT int WINAPIV wsprintfWInternal(LPWSTR, LPCWSTR, ...) WCE_LINK(wsprintfWInternal);
WCE_IMPORT LPWSTR WINAPI lstrcpyWInternal(LPWSTR lpString1, LPCWSTR lpString2) WCE_LINK(lstrcpyWInternal);
WCE_IMPORT LPWSTR WINAPI lstrcpynWInternal(LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength) WCE_LINK(lstrcpynWInternal);
WCE_IMPORT int WINAPI lstrcmpWInternal(LPCWSTR lpString1, LPCWSTR lpString2) WCE_LINK(lstrcmpWInternal);
WCE_IMPORT int WINAPI lstrcmpiWInternal(LPCWSTR lpString1, LPCWSTR lpString2) WCE_LINK(lstrcmpiWInternal);
WCE_IMPORT int WINAPI lstrlenWInternal(LPCWSTR lpString) WCE_LINK(lstrlenWInternal);
WCE_IMPORT void WINAPI IntToWstr(int i, LPWSTR wstr) WCE_LINK(IntToWstr);
WCE_IMPORT LONGLONG WINAPI llMulDiv(LONGLONG a, LONGLONG b, LONGLONG c, LONGLONG rnd) WCE_LINK(llMulDiv);
WCE_IMPORT LONGLONG WINAPI Int64x32Div32(LONGLONG a, LONG b, LONG c, LONG rnd) WCE_LINK(Int64x32Div32);
WCE_IMPORT HRESULT WINAPI AMGetWideString(LPCWSTR pszString, LPWSTR *ppszReturn) WCE_LINK(AMGetWideString);

#ifdef __cplusplus
}
#endif
#endif

