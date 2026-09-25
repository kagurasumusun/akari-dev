/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FWAPI_H
#define WCE_FWAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI IsFirewallEnabled(USHORT Family) WCE_LINK(IsFirewallEnabled);
WCE_IMPORT DWORD WINAPI FirewallEnable(USHORT Family, BOOL bEnable, BOOL bPersist) WCE_LINK(FirewallEnable);
WCE_IMPORT DWORD WINAPI FirewallGetRules(PFW_RULE pRules, DWORD *pcbSize, DWORD* pdwCount) WCE_LINK(FirewallGetRules);
WCE_IMPORT VOID WINAPI FirewallRefresh() WCE_LINK(FirewallRefresh);
WCE_IMPORT DWORD WINAPI FirewallSetInterface(LPCWSTR pszInterfaceName, BOOL bFirewalled, BOOL bPersist) WCE_LINK(FirewallSetInterface);
WCE_IMPORT BOOL WINAPI IsInterfaceFirewalled(LPCWSTR pszInterfaceName) WCE_LINK(IsInterfaceFirewalled);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT void WINAPI FirewallLogInit() WCE_LINK(FirewallLogInit);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT void WINAPI FirewallLogUninit() WCE_LINK(FirewallLogUninit);
#endif

#ifdef __cplusplus
}
#endif
#endif

