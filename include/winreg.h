/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINREG_H
#define WCE_WINREG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagREG_NOTIFY_INFORMATION { DWORD NextEntryOffset; DWORD Action; DWORD RegNameLength; WCHAR RegName[1]; } REG_NOTIFY_INFORMATION, *PREG_NOTIFY_INFORMATION, *LPREG_NOTIFY_INFORMATION;

WCE_IMPORT LONG WINAPI RegCloseKey(HKEY hKey) WCE_LINK(RegCloseKey);
WCE_IMPORT LONG WINAPI RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) WCE_LINK(RegCreateKeyExA);
WCE_IMPORT LONG WINAPI RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) WCE_LINK(RegCreateKeyExW);
WCE_IMPORT LONG WINAPI RegDeleteKeyA(HKEY hKey, LPCSTR lpSubKey) WCE_LINK(RegDeleteKeyA);
WCE_IMPORT LONG WINAPI RegDeleteKeyW(HKEY hKey, LPCWSTR lpSubKey) WCE_LINK(RegDeleteKeyW);
WCE_IMPORT LONG WINAPI RegDeleteValueA(HKEY hKey, LPCSTR lpValueName) WCE_LINK(RegDeleteValueA);
WCE_IMPORT LONG WINAPI RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName) WCE_LINK(RegDeleteValueW);
WCE_IMPORT LONG WINAPI RegEnumKeyExA(HKEY hKey, DWORD dwIndex, LPSTR lpName, LPDWORD lpcchName, LPDWORD lpReserved, LPSTR lpClass, LPDWORD lpcchClass, PFILETIME lpftLastWriteTime) WCE_LINK(RegEnumKeyExA);
WCE_IMPORT LONG WINAPI RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcchName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcchClass, PFILETIME lpftLastWriteTime) WCE_LINK(RegEnumKeyExW);
WCE_IMPORT LONG WINAPI RegEnumValueA(HKEY hKey, DWORD dwIndex, LPSTR lpValueName, LPDWORD lpcchValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) WCE_LINK(RegEnumValueA);
WCE_IMPORT LONG WINAPI RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcchValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) WCE_LINK(RegEnumValueW);
WCE_IMPORT LONG WINAPI RegFlushKey(HKEY hKey) WCE_LINK(RegFlushKey);
WCE_IMPORT LONG WINAPI RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) WCE_LINK(RegOpenKeyExA);
WCE_IMPORT LONG WINAPI RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) WCE_LINK(RegOpenKeyExW);
WCE_IMPORT LONG WINAPI RegQueryInfoKeyA(HKEY hKey, LPSTR lpClass, LPDWORD lpcchClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime) WCE_LINK(RegQueryInfoKeyA);
WCE_IMPORT LONG WINAPI RegQueryInfoKeyW(HKEY hKey, LPWSTR lpClass, LPDWORD lpcchClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime) WCE_LINK(RegQueryInfoKeyW);
WCE_IMPORT LONG WINAPI RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) WCE_LINK(RegQueryValueExA);
WCE_IMPORT LONG WINAPI RegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) WCE_LINK(RegQueryValueExW);
WCE_IMPORT LONG WINAPI RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData) WCE_LINK(RegSetValueExA);
WCE_IMPORT LONG WINAPI RegSetValueExW(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData) WCE_LINK(RegSetValueExW);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI CeFindFirstRegChange(HKEY hKey, BOOL bWatchSubTree, DWORD dwNotifyFilter) WCE_LINK(CeFindFirstRegChange);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeFindNextRegChange(HANDLE hNotify) WCE_LINK(CeFindNextRegChange);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeFindCloseRegChange(HANDLE hNotify) WCE_LINK(CeFindCloseRegChange);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT LONG WINAPI CeRegTestSetValueW(HKEY hKey, LPCWSTR lpValueName, DWORD dwType, CONST BYTE* lpOldData, DWORD cbOldData, CONST BYTE* lpNewData, DWORD cbNewData, DWORD dwFlags) WCE_LINK(CeRegTestSetValueW);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT LONG WINAPI CeRegGetInfo(HKEY hKey, PCE_REGISTRY_INFO pInfo) WCE_LINK(CeRegGetInfo);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT LONG WINAPI CeRegGetNotificationInfo(HANDLE hChangeHandle, DWORD dwFlags, LPVOID lpBuffer, DWORD nBufferLength, LPDWORD lpBytesReturned, LPDWORD lpBytesAvailable) WCE_LINK(CeRegGetNotificationInfo);
#endif

#define RegCreateKeyEx RegCreateKeyExW
#define RegDeleteKey RegDeleteKeyW
#define RegDeleteValue RegDeleteValueW
#define RegEnumKeyEx RegEnumKeyExW
#define RegEnumValue RegEnumValueW
#define RegOpenKeyEx RegOpenKeyExW
#define RegQueryInfoKey RegQueryInfoKeyW
#define RegQueryValueEx RegQueryValueExW
#define RegSetValueEx RegSetValueExW
#define CeRegTestSetValue CeRegTestSetValueW
#ifdef __cplusplus
}
#endif
#endif

