/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CAPI_H
#define WCE_CAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagJAVA_TRUST { DWORD cbSize; DWORD flag; BOOL fAllActiveXPermissions; BOOL fAllPermissions; DWORD dwEncodingType; PBYTE pbJavaPermissions; DWORD cbJavaPermissions; PBYTE pbSigner; DWORD cbSigner; LPCWSTR pwszZone; GUID guidZone; HRESULT hVerify; } JAVA_TRUST, *PJAVA_TRUST, *LPJAVA_TRUST;
typedef struct tagJAVA_POLICY_PROVIDER { DWORD cbSize; LPVOID pZoneManager; LPCWSTR pwszZone; BOOL fNoBadUI; PJAVA_TRUST pbJavaTrust; DWORD cbJavaTrust; DWORD dwActionID; DWORD dwUnsignedActionID; BOOL VMBased; } JAVA_POLICY_PROVIDER, *PJAVA_POLICY_PROVIDER, *LPJAVA_POLICY_PROVIDER;


#ifdef __cplusplus
}
#endif
#endif

