/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WXDEBUG_H
#define WCE_WXDEBUG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI DbgInitModuleName() WCE_LINK(DbgInitModuleName);
WCE_IMPORT BOOL WINAPI DbgRegisterObjectDestruction(DWORD dwCookie) WCE_LINK(DbgRegisterObjectDestruction);
WCE_IMPORT void WINAPI DbgInitKeyLevels(HKEY hKey) WCE_LINK(DbgInitKeyLevels);
WCE_IMPORT void WINAPI DbgInitGlobalSettings() WCE_LINK(DbgInitGlobalSettings);
WCE_IMPORT void WINAPI DbgInitModuleSettings() WCE_LINK(DbgInitModuleSettings);
WCE_IMPORT void WINAPI DbgInitialise(HINSTANCE hInst) WCE_LINK(DbgInitialise);
WCE_IMPORT void WINAPI DbgTerminate() WCE_LINK(DbgTerminate);
WCE_IMPORT void WINAPI DbgDumpObjectRegister() WCE_LINK(DbgDumpObjectRegister);
WCE_IMPORT void WINAPI DbgOutString(LPCTSTR psz) WCE_LINK(DbgOutString);
WCE_IMPORT DWORD WINAPI DbgWaitForSingleObject(HANDLE h) WCE_LINK(DbgWaitForSingleObject);
WCE_IMPORT DWORD WINAPI DbgWaitForMultipleObjects(DWORD nCount, CONST HANDLE *lpHandles, BOOL bWaitAll) WCE_LINK(DbgWaitForMultipleObjects);
WCE_IMPORT void WINAPI DbgSetWaitTimeout(DWORD dwTimeout) WCE_LINK(DbgSetWaitTimeout);

#ifdef __cplusplus
}
#endif
#endif

