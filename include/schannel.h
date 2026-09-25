/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SCHANNEL_H
#define WCE_SCHANNEL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSecPkgCred_CipherStrengths { DWORD dwMinimumCipherStrength; DWORD dwMaximumCipherStrength; } SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths, *LPSecPkgCred_CipherStrengths;
typedef struct tagSecPkgContext_IssuerListInfoEx { PCERT_NAME_BLOB aIssuers; DWORD cIssuers; } SecPkgContext_IssuerListInfoEx, *PSecPkgContext_IssuerListInfoEx, *LPSecPkgContext_IssuerListInfoEx;
typedef struct tagSecPkgContext_EapKeyBlock { BYTE rgbKeys[128]; BYTE rgbIVs[64]; } SecPkgContext_EapKeyBlock, *PSecPkgContext_EapKeyBlock, *LPSecPkgContext_EapKeyBlock;
typedef struct tagSecPkgContext_MappedCredAttr { DWORD dwAttribute; PVOID pvBuffer; } SecPkgContext_MappedCredAttr, *PSecPkgContext_MappedCredAttr, *LPSecPkgContext_MappedCredAttr;
typedef struct tagSecPkgCred_CacheInfo { DWORD cbBytesCommitted; DWORD cMaxCacheEntries; DWORD cEntries; DWORD cUsed; DWORD cOrphans; DWORD cExpiredOrphans; DWORD cExpiredAbortedOrphans; DWORD cHandshaking; } SecPkgCred_CacheInfo, *PSecPkgCred_CacheInfo, *LPSecPkgCred_CacheInfo;
typedef struct tagSCHANNEL_ALERT_TOKEN { DWORD dwTokenType; DWORD dwAlertType; DWORD dwAlertNumber; } SCHANNEL_ALERT_TOKEN, *PSCHANNEL_ALERT_TOKEN, *LPSCHANNEL_ALERT_TOKEN;

WCE_IMPORT DWORD WINAPI SslGetMaximumKeySize(DWORD Reserved) WCE_LINK(SslGetMaximumKeySize);
WCE_IMPORT BOOL WINAPI SslEmptyCache(VOID) WCE_LINK(SslEmptyCache);
WCE_IMPORT BOOL WINAPI SslCrackCertificate(PUCHAR pbCertificate, DWORD cbCertificate, DWORD dwFlags, PX509Certificate * ppCertificate) WCE_LINK(SslCrackCertificate);
WCE_IMPORT VOID WINAPI SslFreeCertificate(PX509Certificate pCertificate) WCE_LINK(SslFreeCertificate);
WCE_IMPORT BOOL WINAPI SslGetDefaultIssuers(PBYTE pbIssuers, DWORD *pcbIssuers) WCE_LINK(SslGetDefaultIssuers);

#ifdef __cplusplus
}
#endif
#endif

