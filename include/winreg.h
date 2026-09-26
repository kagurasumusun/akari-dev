/* Registry. Original text. Exported by coredll.dll. */
#ifndef AKARI_WCE_WINREG_H
#define AKARI_WCE_WINREG_H

#include "winbase.h"

#define HKEY_CLASSES_ROOT     ((HKEY)(ULONG_PTR)0x80000000)
#define HKEY_CURRENT_USER     ((HKEY)(ULONG_PTR)0x80000001)
#define HKEY_LOCAL_MACHINE    ((HKEY)(ULONG_PTR)0x80000002)
#define HKEY_USERS            ((HKEY)(ULONG_PTR)0x80000003)
#define HKEY_PERFORMANCE_DATA ((HKEY)(ULONG_PTR)0x80000004)
#define HKEY_CURRENT_CONFIG   ((HKEY)(ULONG_PTR)0x80000005)
#define HKEY_DYN_DATA         ((HKEY)(ULONG_PTR)0x80000006)

#define KEY_QUERY_VALUE        0x0001
#define KEY_SET_VALUE          0x0002
#define KEY_CREATE_SUB_KEY     0x0004
#define KEY_ENUMERATE_SUB_KEYS 0x0008
#define KEY_NOTIFY             0x0010
#define KEY_ALL_ACCESS         0xF003F
#define KEY_READ               0x20019
#define KEY_WRITE              0x20006

#define REG_OPTION_NON_VOLATILE   0x00000000
#define REG_OPTION_VOLATILE       0x00000001
#define REG_CREATED_NEW_KEY       0x00000001
#define REG_OPENED_EXISTING_KEY   0x00000002

#define REG_NONE      0
#define REG_SZ        1
#define REG_EXPAND_SZ 2
#define REG_BINARY    3
#define REG_DWORD     4
#define REG_MULTI_SZ  7
#define REG_RESOURCE_LIST 8
#define REG_FULL_RESOURCE_DESCRIPTOR 9
#define REG_RESOURCE_REQUIREMENTS_LIST 10
#define REG_DWORD_LITTLE_ENDIAN 4
#define REG_DWORD_BIG_ENDIAN    5
#define REG_LINK                6

#define RRF_RT_ANY          0x0000FFFF
#define REG_NOTIFY_CHANGE_NAME       0x00000001
#define REG_NOTIFY_CHANGE_ATTRIBUTES 0x00000002
#define REG_NOTIFY_CHANGE_LAST_SET   0x00000004

WINBASEAPI LONG WINAPI RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions,
    DWORD samDesired, PHKEY phkResult);
WINBASEAPI LONG WINAPI RegCreateKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved,
    LPWSTR lpClass, DWORD dwOptions, DWORD samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
WINBASEAPI LONG WINAPI RegCloseKey(HKEY hKey);
WINBASEAPI LONG WINAPI RegDeleteKeyW(HKEY hKey, LPCWSTR lpSubKey);
WINBASEAPI LONG WINAPI RegDeleteValueW(HKEY hKey, LPCWSTR lpValueName);
WINBASEAPI LONG WINAPI RegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved,
    LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
WINBASEAPI LONG WINAPI RegSetValueExW(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved,
    DWORD dwType, const BYTE *lpData, DWORD cbData);
WINBASEAPI LONG WINAPI RegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName,
    LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass,
    PFILETIME lpftLastWriteTime);
WINBASEAPI LONG WINAPI RegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName,
    LPDWORD lpcbValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData,
    LPDWORD lpcbData);
WINBASEAPI LONG WINAPI RegQueryInfoKeyW(HKEY hKey, LPWSTR lpClass, LPDWORD lpcbClass,
    LPDWORD lpReserved, LPDWORD lpcSubKeys, LPDWORD lpcbMaxSubKeyLen,
    LPDWORD lpcbMaxClassLen, LPDWORD lpcValues, LPDWORD lpcbMaxValueNameLen,
    LPDWORD lpcbMaxValueLen, LPDWORD lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime);
WINBASEAPI LONG WINAPI RegFlushKey(HKEY hKey);
/* Windows CE has no registry change notification. */

#endif /* AKARI_WCE_WINREG_H */
