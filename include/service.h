/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SERVICE_H
#define WCE_SERVICE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagServiceEnumInfo { WCHAR szPrefix[6]; WCHAR *szDllName; HANDLE hServiceHandle; DWORD dwServiceState; } ServiceEnumInfo, *PServiceEnumInfo, *LPServiceEnumInfo;

WCE_IMPORT HANDLE WINAPI ActivateService(LPCWSTR lpszDevKey, DWORD dwClientInfo) WCE_LINK(ActivateService);
WCE_IMPORT HANDLE WINAPI RegisterService(LPCWSTR lpszType, DWORD dwIndex, LPCWSTR lpszLib, DWORD dwInfo) WCE_LINK(RegisterService);
WCE_IMPORT BOOL WINAPI DeregisterService(HANDLE hDevice) WCE_LINK(DeregisterService);
WCE_IMPORT HANDLE WINAPI CreateServiceHandle(LPCWSTR lpNew, DWORD dwAccess, DWORD dwShareMode, HANDLE hProc) WCE_LINK(CreateServiceHandle);
WCE_IMPORT BOOL WINAPI GetServiceByIndex(DWORD dwIndex, LPWIN32_FIND_DATA lpFindFileData) WCE_LINK(GetServiceByIndex);
WCE_IMPORT BOOL WINAPI ServiceIoControl(HANDLE hService, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) WCE_LINK(ServiceIoControl);
WCE_IMPORT BOOL WINAPI ServiceUnbindPorts(HANDLE hService) WCE_LINK(ServiceUnbindPorts);
WCE_IMPORT BOOL WINAPI EnumServices(PBYTE pBuffer, DWORD *pdwServiceEntries, DWORD *pdwBufferLen) WCE_LINK(EnumServices);
WCE_IMPORT HANDLE WINAPI GetServiceHandle(LPWSTR szPrefix, LPWSTR szDllName, DWORD *pdwDllBuf) WCE_LINK(GetServiceHandle);

#ifdef __cplusplus
}
#endif
#endif

