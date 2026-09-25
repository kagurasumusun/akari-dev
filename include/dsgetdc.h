/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DSGETDC_H
#define WCE_DSGETDC_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI DsGetDcNameW(IN LPCWSTR ComputerName OPTIONAL, IN LPCWSTR DomainName OPTIONAL, IN GUID *DomainGuid OPTIONAL, IN LPCWSTR SiteName OPTIONAL, IN ULONG Flags, OUT PDOMAIN_CONTROLLER_INFOW *DomainControllerInfo) WCE_LINK(DsGetDcNameW);
#endif

#define DsGetDcName DsGetDcNameW
#ifdef __cplusplus
}
#endif
#endif

