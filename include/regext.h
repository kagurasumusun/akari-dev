/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_REGEXT_H
#define WCE_REGEXT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistryGetDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD * pdwData) WCE_LINK(RegistryGetDWORD);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistryGetString(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPTSTR pszData, UINT cchData) WCE_LINK(RegistryGetString);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistrySetDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwData) WCE_LINK(RegistrySetDWORD);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistrySetString(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszData) WCE_LINK(RegistrySetString);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistryDeleteValue(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName) WCE_LINK(RegistryDeleteValue);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistryTestExchangeDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwOldValue, DWORD dwNewValue) WCE_LINK(RegistryTestExchangeDWORD);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI RegistryStopNotification(LPCTSTR pszName) WCE_LINK(RegistryStopNotification);
#endif

#ifdef __cplusplus
}
#endif
#endif

