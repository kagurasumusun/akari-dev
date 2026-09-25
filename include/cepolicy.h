/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CEPOLICY_H
#define WCE_CEPOLICY_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI CeOpenModuleByPolicy(HANDLE ReferenceTokenHandle, LPCWSTR ModuleName, DWORD OpenModuleFlags, HANDLE *NewTokenHandle) WCE_LINK(CeOpenModuleByPolicy);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI CePolicyCheck(HANDLE TokenHandle,DWORD PolicyType, DWORD PolicyClass, DWORD PolicyMethod, LPCWSTR Name, DWORD DesiredAccess) WCE_LINK(CePolicyCheck);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI CeOpenPolicy(DWORD PolicyType, DWORD PolicyClass, DWORD PolicyMethod, LPCWSTR Name, DWORD OpenPolicyFlags) WCE_LINK(CeOpenPolicy);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI CePolicyCheckByHandle(HANDLE PolicyHandle, HANDLE TokenHandle, DWORD DesiredAccess) WCE_LINK(CePolicyCheckByHandle);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI CeClosePolicy(HANDLE PolicyHandle) WCE_LINK(CeClosePolicy);
#endif

#ifdef __cplusplus
}
#endif
#endif

