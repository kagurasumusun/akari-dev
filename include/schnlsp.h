/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SCHNLSP_H
#define WCE_SCHNLSP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSecPkgContext_IssuerListInfo { DWORD cbIssuerList; PBYTE pIssuerList; } SecPkgContext_IssuerListInfo, *PSecPkgContext_IssuerListInfo, *LPSecPkgContext_IssuerListInfo;
typedef struct tagSecPkgContext_RemoteCredentialInfo { DWORD cbCertificateChain; PBYTE pbCertificateChain; DWORD cCertificates; DWORD fFlags; DWORD dwBits; } SecPkgContext_RemoteCredentialInfo, *PSecPkgContext_RemoteCredentialInfo, *LPSecPkgContext_RemoteCredentialInfo;
typedef struct tagSecPkgContext_LocalCredentialInfo { DWORD cbCertificateChain; PBYTE pbCertificateChain; DWORD cCertificates; DWORD fFlags; DWORD dwBits; } SecPkgContext_LocalCredentialInfo, *PSecPkgContext_LocalCredentialInfo, *LPSecPkgContext_LocalCredentialInfo;
typedef struct tagSecPkgCred_CipherStrengths { DWORD dwMinimumCipherStrength; DWORD dwMaximumCipherStrength; } SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths, *LPSecPkgCred_CipherStrengths;
typedef struct tagSecPkgCred_SupportedProtocols { DWORD grbitProtocol; } SecPkgCred_SupportedProtocols, *PSecPkgCred_SupportedProtocols, *LPSecPkgCred_SupportedProtocols;
typedef struct tagSecPkgContext_IssuerListInfoEx { PCERT_NAME_BLOB aIssuers; DWORD cIssuers; } SecPkgContext_IssuerListInfoEx, *PSecPkgContext_IssuerListInfoEx, *LPSecPkgContext_IssuerListInfoEx;
typedef struct tagSecPkgContext_EapKeyBlock { BYTE rgbKeys[128]; BYTE rgbIVs[64]; } SecPkgContext_EapKeyBlock, *PSecPkgContext_EapKeyBlock, *LPSecPkgContext_EapKeyBlock;
typedef struct tagSecPkgContext_MappedCredAttr { DWORD dwAttribute; PVOID pvBuffer; } SecPkgContext_MappedCredAttr, *PSecPkgContext_MappedCredAttr, *LPSecPkgContext_MappedCredAttr;
typedef struct tagSecPkgCred_CacheInfo { DWORD cbBytesCommitted; DWORD cMaxCacheEntries; DWORD cEntries; DWORD cUsed; DWORD cOrphans; DWORD cExpiredOrphans; DWORD cExpiredAbortedOrphans; DWORD cHandshaking; } SecPkgCred_CacheInfo, *PSecPkgCred_CacheInfo, *LPSecPkgCred_CacheInfo;
typedef struct tagSCHANNEL_ALERT_TOKEN { DWORD dwTokenType; DWORD dwAlertType; DWORD dwAlertNumber; } SCHANNEL_ALERT_TOKEN, *PSCHANNEL_ALERT_TOKEN, *LPSCHANNEL_ALERT_TOKEN;
typedef struct tagSSL_CREDENTIAL_CERTIFICATE { DWORD cbPrivateKey; PBYTE pPrivateKey; DWORD cbCertificate; PBYTE pCertificate; PSTR pszPassword; } SSL_CREDENTIAL_CERTIFICATE, *PSSL_CREDENTIAL_CERTIFICATE, *LPSSL_CREDENTIAL_CERTIFICATE;
typedef struct tagSCH_CRED_SECRET_PRIVKEY { DWORD dwType; PBYTE pPrivateKey; DWORD cbPrivateKey; PSTR pszPassword; } SCH_CRED_SECRET_PRIVKEY, *PSCH_CRED_SECRET_PRIVKEY, *LPSCH_CRED_SECRET_PRIVKEY;
typedef struct tagSCH_CRED_PUBLIC_CERTCHAIN { DWORD dwType; DWORD cbCertChain; PBYTE pCertChain; } SCH_CRED_PUBLIC_CERTCHAIN, *PSCH_CRED_PUBLIC_CERTCHAIN, *LPSCH_CRED_PUBLIC_CERTCHAIN;

WCE_IMPORT DWORD WINAPI SslGetMaximumKeySize(DWORD Reserved) WCE_LINK(SslGetMaximumKeySize);
WCE_IMPORT BOOL WINAPI SslSetProtocols(DWORD rgbitsProtocols) WCE_LINK(SslSetProtocols);
WCE_IMPORT DWORD WINAPI SslGetProtocols() WCE_LINK(SslGetProtocols);
WCE_IMPORT BOOL WINAPI SslEmptyCache(VOID) WCE_LINK(SslEmptyCache);
WCE_IMPORT BOOL WINAPI SslCrackCertificate(PUCHAR pbCertificate, DWORD cbCertificate, DWORD dwFlags, PX509Certificate * ppCertificate) WCE_LINK(SslCrackCertificate);
WCE_IMPORT VOID WINAPI SslFreeCertificate(PX509Certificate pCertificate) WCE_LINK(SslFreeCertificate);
WCE_IMPORT BOOL WINAPI SslGetDefaultIssuers(PBYTE pbIssuers, DWORD *pcbIssuers) WCE_LINK(SslGetDefaultIssuers);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI IsSSLServerName(IN PCCERT_CONTEXT pCertContext, IN LPCWSTR pwszServerName) WCE_LINK(IsSSLServerName);
#endif

#ifdef __cplusplus
}
#endif
#endif

