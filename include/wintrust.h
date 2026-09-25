/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINTRUST_H
#define WCE_WINTRUST_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWINTRUST_FILE_INFO { DWORD cbStruct; LPCWSTR pcwszFilePath; HANDLE hFile; GUID *pgKnownSubject; } WINTRUST_FILE_INFO, *PWINTRUST_FILE_INFO, *LPWINTRUST_FILE_INFO;
typedef struct tagWINTRUST_CATALOG_INFO { DWORD cbStruct; DWORD dwCatalogVersion; LPCWSTR pcwszCatalogFilePath; LPCWSTR pcwszMemberTag; LPCWSTR pcwszMemberFilePath; HANDLE hMemberFile; BYTE *pbCalculatedFileHash; DWORD cbCalculatedFileHash; PCCTL_CONTEXT pcCatalogContext; } WINTRUST_CATALOG_INFO, *PWINTRUST_CATALOG_INFO, *LPWINTRUST_CATALOG_INFO;
typedef struct tagWINTRUST_BLOB_INFO { DWORD cbStruct; GUID gSubject; LPCWSTR pcwszDisplayName; DWORD cbMemObject; BYTE *pbMemObject; DWORD cbMemSignedMsg; BYTE *pbMemSignedMsg; } WINTRUST_BLOB_INFO, *PWINTRUST_BLOB_INFO, *LPWINTRUST_BLOB_INFO;
typedef struct tagCRYPT_PROVUI_DATA { DWORD cbStruct; DWORD dwFinalError; WCHAR *pYesButtonText; WCHAR *pNoButtonText; WCHAR *pMoreInfoButtonText; WCHAR *pAdvancedLinkText; WCHAR *pCopyActionText; WCHAR *pCopyActionTextNoTS; WCHAR *pCopyActionTextNotSigned; } CRYPT_PROVUI_DATA, *PCRYPT_PROVUI_DATA, *LPCRYPT_PROVUI_DATA;
typedef struct tagCRYPT_PROVIDER_PRIVDATA { DWORD cbStruct; GUID gProviderID; DWORD cbProvData; void *pvProvData; } CRYPT_PROVIDER_PRIVDATA, *PCRYPT_PROVIDER_PRIVDATA, *LPCRYPT_PROVIDER_PRIVDATA;
typedef struct tagCRYPT_TRUST_REG_ENTRY { DWORD cbStruct; WCHAR *pwszDLLName; WCHAR *pwszFunctionName; } CRYPT_TRUST_REG_ENTRY, *PCRYPT_TRUST_REG_ENTRY, *LPCRYPT_TRUST_REG_ENTRY;
typedef struct tagCRYPT_REGISTER_ACTIONID { DWORD cbStruct; CRYPT_TRUST_REG_ENTRY sInitProvider; CRYPT_TRUST_REG_ENTRY sObjectProvider; CRYPT_TRUST_REG_ENTRY sSignatureProvider; CRYPT_TRUST_REG_ENTRY sCertificateProvider; CRYPT_TRUST_REG_ENTRY sCertificatePolicyProvider; CRYPT_TRUST_REG_ENTRY sFinalPolicyProvider; CRYPT_TRUST_REG_ENTRY sTestPolicyProvider; CRYPT_TRUST_REG_ENTRY sCleanupProvider; } CRYPT_REGISTER_ACTIONID, *PCRYPT_REGISTER_ACTIONID, *LPCRYPT_REGISTER_ACTIONID;
typedef struct tagCRYPT_PROVIDER_REGDEFUSAGE { DWORD cbStruct; GUID *pgActionID; WCHAR *pwszDllName; char *pwszLoadCallbackDataFunctionName; char *pwszFreeCallbackDataFunctionName; } CRYPT_PROVIDER_REGDEFUSAGE, *PCRYPT_PROVIDER_REGDEFUSAGE, *LPCRYPT_PROVIDER_REGDEFUSAGE;
typedef struct tagCRYPT_PROVIDER_DEFUSAGE { DWORD cbStruct; GUID gActionID; LPVOID pDefPolicyCallbackData; LPVOID pDefSIPClientData; } CRYPT_PROVIDER_DEFUSAGE, *PCRYPT_PROVIDER_DEFUSAGE, *LPCRYPT_PROVIDER_DEFUSAGE;
typedef struct tagSPC_SIGINFO { DWORD dwSipVersion; GUID gSIPGuid; DWORD dwReserved1; DWORD dwReserved2; DWORD dwReserved3; DWORD dwReserved4; DWORD dwReserved5; } SPC_SIGINFO, *PSPC_SIGINFO, *LPSPC_SIGINFO;
typedef struct tagSPC_FINANCIAL_CRITERIA { BOOL fFinancialInfoAvailable; BOOL fMeetsCriteria; } SPC_FINANCIAL_CRITERIA, *PSPC_FINANCIAL_CRITERIA, *LPSPC_FINANCIAL_CRITERIA;
typedef struct tagSPC_STATEMENT_TYPE { DWORD cKeyPurposeId; LPSTR *rgpszKeyPurposeId; } SPC_STATEMENT_TYPE, *PSPC_STATEMENT_TYPE, *LPSPC_STATEMENT_TYPE;
typedef struct tagCAT_MEMBERINFO { LPWSTR pwszSubjGuid; DWORD dwCertVersion; } CAT_MEMBERINFO, *PCAT_MEMBERINFO, *LPCAT_MEMBERINFO;
typedef struct tagWIN_TRUST_SUBJECT_FILE { HANDLE hFile; LPCWSTR lpPath; } WIN_TRUST_SUBJECT_FILE, *PWIN_TRUST_SUBJECT_FILE, *LPWIN_TRUST_SUBJECT_FILE;
typedef struct tagWIN_TRUST_SUBJECT_FILE_AND_DISPLAY { HANDLE hFile; LPCWSTR lpPath; LPCWSTR lpDisplayName; } WIN_TRUST_SUBJECT_FILE_AND_DISPLAY, *PWIN_TRUST_SUBJECT_FILE_AND_DISPLAY, *LPWIN_TRUST_SUBJECT_FILE_AND_DISPLAY;

WCE_IMPORT LONG WINAPI WinVerifyTrust(HWND hwnd, GUID *pgActionID, LPVOID pWVTData) WCE_LINK(WinVerifyTrust);
WCE_IMPORT void WINAPI WintrustGetRegPolicyFlags(DWORD *pdwPolicyFlags) WCE_LINK(WintrustGetRegPolicyFlags);
WCE_IMPORT BOOL WINAPI WintrustSetRegPolicyFlags(DWORD dwPolicyFlags) WCE_LINK(WintrustSetRegPolicyFlags);
WCE_IMPORT BOOL WINAPI WintrustAddActionID(IN GUID *pgActionID, IN DWORD fdwReserved, IN CRYPT_REGISTER_ACTIONID *psProvInfo) WCE_LINK(WintrustAddActionID);
WCE_IMPORT BOOL WINAPI WintrustRemoveActionID(IN GUID *pgActionID) WCE_LINK(WintrustRemoveActionID);
WCE_IMPORT BOOL WINAPI WintrustAddDefaultForUsage(IN const char *pszUsageOID, IN CRYPT_PROVIDER_REGDEFUSAGE *psDefUsage) WCE_LINK(WintrustAddDefaultForUsage);
WCE_IMPORT BOOL WINAPI WintrustGetDefaultForUsage(IN DWORD dwAction, IN const char *pszUsageOID, IN OUT CRYPT_PROVIDER_DEFUSAGE *psUsage) WCE_LINK(WintrustGetDefaultForUsage);

#ifdef __cplusplus
}
#endif
#endif

