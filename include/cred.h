/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CRED_H
#define WCE_CRED_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCRED { DWORD dwVersion; DWORD dwType; PWCHAR wszUser; DWORD dwUserLen; PWCHAR wszTarget; DWORD dwTargetLen; PBYTE pBlob; DWORD dwBlobSize; DWORD dwFlags; } CRED, *PCRED, *LPCRED;

#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CredWrite(IN PCRED pCred, IN DWORD dwFlags) WCE_LINK(CredWrite);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CredRead(IN PWCHAR wszTarget, IN DWORD dwTargetLen, IN DWORD dwType, IN DWORD dwFlags, OUT PPCRED ppCred) WCE_LINK(CredRead);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CredDelete(IN PWCHAR wszTarget, IN DWORD dwTargetLen, IN DWORD dwType, IN DWORD dwFlags) WCE_LINK(CredDelete);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CredUpdate(IN PWCHAR wszTarget, IN DWORD dwTargetLen, IN DWORD dwType, IN PCRED pCred, IN DWORD dwFlags) WCE_LINK(CredUpdate);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CredFree(IN PBYTE pbBuffer) WCE_LINK(CredFree);
#endif

#ifdef __cplusplus
}
#endif
#endif

