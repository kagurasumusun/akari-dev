/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CESDDL_H
#define WCE_CESDDL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeConvertStrToSD(IN LPCWSTR StringSecurityDescriptor, IN DWORD StringSDRevision, OUT PSECURITY_DESCRIPTOR *SecurityDescriptor, OUT PULONG SecurityDescriptorSize OPTIONAL) WCE_LINK(CeConvertStrToSD);
#endif

#ifdef __cplusplus
}
#endif
#endif

