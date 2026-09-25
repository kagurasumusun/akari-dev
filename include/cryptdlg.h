/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CRYPTDLG_H
#define WCE_CRYPTDLG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCERT_FILTER_EXTENSION_MATCH { LPCSTR szExtensionOID; DWORD dwTestOperation; LPBYTE pbTestData; DWORD cbTestData; } CERT_FILTER_EXTENSION_MATCH, *PCERT_FILTER_EXTENSION_MATCH, *LPCERT_FILTER_EXTENSION_MATCH;
typedef struct tagCERT_FILTER_DATA { DWORD dwSize; DWORD cExtensionChecks; CERT_FILTER_EXTENSION_MATCH * arrayExtensionChecks; DWORD dwCheckingFlags; } CERT_FILTER_DATA, *PCERT_FILTER_DATA, *LPCERT_FILTER_DATA;
typedef struct tagCTL_MODIFY_REQUEST { PCCERT_CONTEXT pccert; DWORD dwOperation; DWORD dwError; } CTL_MODIFY_REQUEST, *PCTL_MODIFY_REQUEST, *LPCTL_MODIFY_REQUEST;

WCE_IMPORT BOOL WINAPI CertSelectCertificateA(IN OUT PCERT_SELECT_STRUCT_A pCertSelectInfo) WCE_LINK(CertSelectCertificateA);
WCE_IMPORT BOOL WINAPI CertSelectCertificateW(IN OUT PCERT_SELECT_STRUCT_W pCertSelectInfo) WCE_LINK(CertSelectCertificateW);
WCE_IMPORT BOOL WINAPI CertViewPropertiesA(PCERT_VIEWPROPERTIES_STRUCT_A pCertViewInfo) WCE_LINK(CertViewPropertiesA);
WCE_IMPORT BOOL WINAPI CertViewPropertiesW(PCERT_VIEWPROPERTIES_STRUCT_W pCertViewInfo) WCE_LINK(CertViewPropertiesW);
WCE_IMPORT DWORD WINAPI GetFriendlyNameOfCertA(PCCERT_CONTEXT pccert, LPSTR pchBuffer, DWORD cchBuffer) WCE_LINK(GetFriendlyNameOfCertA);
WCE_IMPORT DWORD WINAPI GetFriendlyNameOfCertW(PCCERT_CONTEXT pccert, LPWSTR pchBuffer, DWORD cchBuffer) WCE_LINK(GetFriendlyNameOfCertW);
WCE_IMPORT BOOL WINAPI CertConfigureTrustA(void) WCE_LINK(CertConfigureTrustA);
WCE_IMPORT BOOL WINAPI FormatVerisignExtension(DWORD , DWORD , DWORD , void * , LPCSTR , const BYTE * , DWORD , void * pbFormat, DWORD * pcbFormat) WCE_LINK(FormatVerisignExtension);

#define CertSelectCertificate CertSelectCertificateW
#define CertViewProperties CertViewPropertiesW
#define GetFriendlyNameOfCert GetFriendlyNameOfCertW
#ifdef __cplusplus
}
#endif
#endif

