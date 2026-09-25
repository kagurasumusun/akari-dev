/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_WINREG_H
#define AKARI_WINREG_H
#include "windef.h"
#include "winbase.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HKEY_CLASSES_ROOT ((HKEY)(ULONG_PTR)0x80000000)
#define HKEY_CURRENT_USER ((HKEY)(ULONG_PTR)0x80000001)
#define HKEY_LOCAL_MACHINE ((HKEY)(ULONG_PTR)0x80000002)
#define HKEY_USERS ((HKEY)(ULONG_PTR)0x80000003)
#define REG_NONE (0)
#define REG_SZ (1)
#define REG_EXPAND_SZ (2)
#define REG_BINARY (3)
#define REG_DWORD (4)
#define REG_DWORD_LITTLE_ENDIAN (4)
#define REG_MULTI_SZ (7)
#define KEY_QUERY_VALUE (0x0001)
#define KEY_SET_VALUE (0x0002)
#define KEY_CREATE_SUB_KEY (0x0004)
#define KEY_ENUMERATE_SUB_KEYS (0x0008)
#define KEY_NOTIFY (0x0010)
#define KEY_CREATE_LINK (0x0020)
#define KEY_READ ((STANDARD_RIGHTS_READ | KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_NOTIFY) & (~SYNCHRONIZE))
#define KEY_WRITE ((STANDARD_RIGHTS_WRITE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY) & (~SYNCHRONIZE))
#define KEY_ALL_ACCESS ((STANDARD_RIGHTS_ALL | KEY_QUERY_VALUE | KEY_SET_VALUE | KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | KEY_NOTIFY | KEY_CREATE_LINK) & (~SYNCHRONIZE))
AKARI_IMPORT LONG WINAPI RegCloseKey(HKEY hKey) AKARI_NAME(RegCloseKey);
AKARI_IMPORT LONG WINAPI RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) AKARI_NAME(RegCreateKeyExW);
AKARI_IMPORT LONG WINAPI RegDeleteKeyW(HKEY hKey, LPCWSTR lpSubKey) AKARI_NAME(RegDeleteKeyW);
AKARI_IMPORT LONG WINAPI RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName) AKARI_NAME(RegDeleteValueW);
AKARI_IMPORT LONG WINAPI RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcchName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcchClass, PFILETIME lpftLastWriteTime) AKARI_NAME(RegEnumKeyExW);
AKARI_IMPORT LONG WINAPI RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, LPDWORD lpcchValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) AKARI_NAME(RegEnumValueW);
AKARI_IMPORT LONG WINAPI RegFlushKey(HKEY hKey) AKARI_NAME(RegFlushKey);
AKARI_IMPORT LONG WINAPI RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) AKARI_NAME(RegOpenKeyExW);
AKARI_IMPORT LONG WINAPI RegQueryInfoKeyW(HKEY hKey, LPWSTR lpClass, LPDWORD lpcchClass, LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen, LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen, LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime) AKARI_NAME(RegQueryInfoKeyW);
AKARI_IMPORT LONG WINAPI RegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) AKARI_NAME(RegQueryValueExW);
AKARI_IMPORT LONG WINAPI RegSetValueExW(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData) AKARI_NAME(RegSetValueExW);
AKARI_IMPORT HANDLE WINAPI CeFindFirstRegChange(HKEY hKey, BOOL bWatchSubTree, DWORD dwNotifyFilter) AKARI_NAME(CeFindFirstRegChange);
AKARI_IMPORT BOOL WINAPI CeFindNextRegChange(HANDLE hNotify) AKARI_NAME(CeFindNextRegChange);
AKARI_IMPORT BOOL WINAPI CeFindCloseRegChange(HANDLE hNotify) AKARI_NAME(CeFindCloseRegChange);
AKARI_IMPORT LONG WINAPI CeRegTestSetValueW(HKEY hKey, LPCWSTR lpValueName, DWORD dwType, CONST BYTE* lpOldData, DWORD cbOldData, CONST BYTE* lpNewData, DWORD cbNewData, DWORD dwFlags) AKARI_NAME(CeRegTestSetValueW);
AKARI_IMPORT LONG WINAPI CeRegGetNotificationInfo(HANDLE hChangeHandle, DWORD dwFlags, LPVOID lpBuffer, DWORD nBufferLength, LPDWORD lpBytesReturned, LPDWORD lpBytesAvailable) AKARI_NAME(CeRegGetNotificationInfo);

#define CeRegTestSetValue CeRegTestSetValueW
#define RegCreateKeyEx RegCreateKeyExW
#define RegDeleteKey RegDeleteKeyW
#define RegDeleteValue RegDeleteValueW
#define RegEnumKeyEx RegEnumKeyExW
#define RegEnumValue RegEnumValueW
#define RegOpenKeyEx RegOpenKeyExW
#define RegQueryInfoKey RegQueryInfoKeyW
#define RegQueryValueEx RegQueryValueExW
#define RegSetValueEx RegSetValueExW

#ifdef __cplusplus
}
#endif
#endif
