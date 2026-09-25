/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINCRED_H
#define WCE_WINCRED_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSecHandle { ULONG_PTR dwLower; ULONG_PTR dwUpper; } SecHandle, *PSecHandle, *LPSecHandle;
typedef struct tagCREDENTIAL_ATTRIBUTEA { LPSTR Keyword; DWORD Flags; DWORD ValueSize; LPBYTE Value; } CREDENTIAL_ATTRIBUTEA, *PCREDENTIAL_ATTRIBUTEA, *LPCREDENTIAL_ATTRIBUTEA;
typedef struct tagCREDENTIALA { DWORD Flags; DWORD Type; LPSTR TargetName; LPSTR Comment; FILETIME LastWritten; DWORD CredentialBlobSize; LPBYTE CredentialBlob; DWORD Persist; DWORD AttributeCount; PCREDENTIAL_ATTRIBUTEA Attributes; LPSTR TargetAlias; LPSTR UserName; } CREDENTIALA, *PCREDENTIALA, *LPCREDENTIALA;
typedef struct tagCREDENTIAL_TARGET_INFORMATIONA { LPSTR TargetName; LPSTR NetbiosServerName; LPSTR DnsServerName; LPSTR NetbiosDomainName; LPSTR DnsDomainName; LPSTR DnsTreeName; LPSTR PackageName; ULONG Flags; DWORD CredTypeCount; LPDWORD CredTypes; } CREDENTIAL_TARGET_INFORMATIONA, *PCREDENTIAL_TARGET_INFORMATIONA, *LPCREDENTIAL_TARGET_INFORMATIONA;
typedef struct tagUSERNAME_TARGET_CREDENTIAL_INFO { LPWSTR UserName; } USERNAME_TARGET_CREDENTIAL_INFO, *PUSERNAME_TARGET_CREDENTIAL_INFO, *LPUSERNAME_TARGET_CREDENTIAL_INFO;
typedef struct tagBINARY_BLOB_CREDENTIAL_INFO { ULONG cbBlob; LPBYTE pbBlob; } BINARY_BLOB_CREDENTIAL_INFO, *PBINARY_BLOB_CREDENTIAL_INFO, *LPBINARY_BLOB_CREDENTIAL_INFO;
typedef struct tagCREDUI_INFOA { DWORD cbSize; HWND hwndParent; PCSTR pszMessageText; PCSTR pszCaptionText; HBITMAP hbmBanner; } CREDUI_INFOA, *PCREDUI_INFOA, *LPCREDUI_INFOA;
typedef struct tagCREDUI_INFOW { DWORD cbSize; HWND hwndParent; PCWSTR pszMessageText; PCWSTR pszCaptionText; HBITMAP hbmBanner; } CREDUI_INFOW, *PCREDUI_INFOW, *LPCREDUI_INFOW;

WCE_IMPORT BOOL WINAPI CredWriteW(PCREDENTIALW Credential, DWORD Flags) WCE_LINK(CredWriteW);
WCE_IMPORT BOOL WINAPI CredWriteA(PCREDENTIALA Credential, DWORD Flags) WCE_LINK(CredWriteA);
WCE_IMPORT BOOL WINAPI CredReadW(LPCWSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALW *Credential) WCE_LINK(CredReadW);
WCE_IMPORT BOOL WINAPI CredReadA(LPCSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALA *Credential) WCE_LINK(CredReadA);
WCE_IMPORT BOOL WINAPI CredEnumerateW(LPCWSTR Filter, DWORD Flags, DWORD *Count, PCREDENTIALW **Credential) WCE_LINK(CredEnumerateW);
WCE_IMPORT BOOL WINAPI CredEnumerateA(LPCSTR Filter, DWORD Flags, DWORD *Count, PCREDENTIALA **Credential) WCE_LINK(CredEnumerateA);
WCE_IMPORT BOOL WINAPI CredWriteDomainCredentialsW(PCREDENTIAL_TARGET_INFORMATIONW TargetInfo, PCREDENTIALW Credential, DWORD Flags) WCE_LINK(CredWriteDomainCredentialsW);
WCE_IMPORT BOOL WINAPI CredWriteDomainCredentialsA(PCREDENTIAL_TARGET_INFORMATIONA TargetInfo, PCREDENTIALA Credential, DWORD Flags) WCE_LINK(CredWriteDomainCredentialsA);
WCE_IMPORT BOOL WINAPI CredReadDomainCredentialsW(PCREDENTIAL_TARGET_INFORMATIONW TargetInfo, DWORD Flags, DWORD *Count, PCREDENTIALW **Credential) WCE_LINK(CredReadDomainCredentialsW);
WCE_IMPORT BOOL WINAPI CredReadDomainCredentialsA(PCREDENTIAL_TARGET_INFORMATIONA TargetInfo, DWORD Flags, DWORD *Count, PCREDENTIALA **Credential) WCE_LINK(CredReadDomainCredentialsA);
WCE_IMPORT BOOL WINAPI CredDeleteW(LPCWSTR TargetName, DWORD Type, DWORD Flags) WCE_LINK(CredDeleteW);
WCE_IMPORT BOOL WINAPI CredDeleteA(LPCSTR TargetName, DWORD Type, DWORD Flags) WCE_LINK(CredDeleteA);
WCE_IMPORT BOOL WINAPI CredRenameW(LPCWSTR OldTargetName, LPCWSTR NewTargetName, DWORD Type, DWORD Flags) WCE_LINK(CredRenameW);
WCE_IMPORT BOOL WINAPI CredRenameA(LPCSTR OldTargetName, LPCSTR NewTargetName, DWORD Type, DWORD Flags) WCE_LINK(CredRenameA);
WCE_IMPORT BOOL WINAPI CredGetTargetInfoW(LPCWSTR TargetName, DWORD Flags, PCREDENTIAL_TARGET_INFORMATIONW *TargetInfo) WCE_LINK(CredGetTargetInfoW);
WCE_IMPORT BOOL WINAPI CredGetTargetInfoA(LPCSTR TargetName, DWORD Flags, PCREDENTIAL_TARGET_INFORMATIONA *TargetInfo) WCE_LINK(CredGetTargetInfoA);
WCE_IMPORT BOOL WINAPI CredUnmarshalCredentialW(LPCWSTR MarshaledCredential, PCRED_MARSHAL_TYPE CredType, PVOID *Credential) WCE_LINK(CredUnmarshalCredentialW);
WCE_IMPORT BOOL WINAPI CredUnmarshalCredentialA(LPCSTR MarshaledCredential, PCRED_MARSHAL_TYPE CredType, PVOID *Credential) WCE_LINK(CredUnmarshalCredentialA);
WCE_IMPORT BOOL WINAPI CredIsMarshaledCredentialW(LPCWSTR MarshaledCredential) WCE_LINK(CredIsMarshaledCredentialW);
WCE_IMPORT BOOL WINAPI CredIsMarshaledCredentialA(LPCSTR MarshaledCredential) WCE_LINK(CredIsMarshaledCredentialA);
WCE_IMPORT BOOL WINAPI CredUnPackAuthenticationBufferW(DWORD dwFlags, PVOID pAuthBuffer, DWORD cbAuthBuffer, LPWSTR pszUserName, DWORD* pcchMaxUserName, LPWSTR pszDomainName, DWORD* pcchMaxDomainName, LPWSTR pszPassword, DWORD* pcchMaxPassword) WCE_LINK(CredUnPackAuthenticationBufferW);
WCE_IMPORT BOOL WINAPI CredUnPackAuthenticationBufferA(DWORD dwFlags, PVOID pAuthBuffer, DWORD cbAuthBuffer, LPSTR pszUserName, DWORD* pcchlMaxUserName, LPSTR pszDomainName, DWORD* pcchMaxDomainName, LPSTR pszPassword, DWORD* pcchMaxPassword) WCE_LINK(CredUnPackAuthenticationBufferA);
WCE_IMPORT BOOL WINAPI CredPackAuthenticationBufferW(DWORD dwFlags, LPWSTR pszUserName, LPWSTR pszPassword, PBYTE pPackedCredentials, DWORD* pcbPackedCredentials) WCE_LINK(CredPackAuthenticationBufferW);
WCE_IMPORT BOOL WINAPI CredPackAuthenticationBufferA(DWORD dwFlags, LPSTR pszUserName, LPSTR pszPassword, PBYTE pPackedCredentials, DWORD* pcbPackedCredentials) WCE_LINK(CredPackAuthenticationBufferA);
WCE_IMPORT BOOL WINAPI CredUnprotectW(BOOL fAsSelf, LPWSTR pszProtectedCredentials, DWORD cchProtectedCredentials, LPWSTR pszCredentials, DWORD* pcchMaxChars) WCE_LINK(CredUnprotectW);
WCE_IMPORT BOOL WINAPI CredUnprotectA(BOOL fAsSelf, LPSTR pszProtectedCredentials, DWORD cchProtectedCredentials, LPSTR pszCredentials, DWORD* pcchMaxChars) WCE_LINK(CredUnprotectA);
WCE_IMPORT BOOL WINAPI CredFindBestCredentialW(IN LPCWSTR TargetName, IN DWORD Type, IN DWORD Flags, OUT PCREDENTIALW *Credential) WCE_LINK(CredFindBestCredentialW);
WCE_IMPORT BOOL WINAPI CredFindBestCredentialA(IN LPCSTR TargetName, IN DWORD Type, IN DWORD Flags, OUT PCREDENTIALA *Credential) WCE_LINK(CredFindBestCredentialA);
WCE_IMPORT BOOL WINAPI CredGetSessionTypes(DWORD MaximumPersistCount, LPDWORD MaximumPersist) WCE_LINK(CredGetSessionTypes);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT VOID WINAPI CredFree(PVOID Buffer) WCE_LINK(CredFree);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI CredUIPromptForCredentialsW(PCREDUI_INFOW pUiInfo, PCWSTR pszTargetName, PCtxtHandle pContext, DWORD dwAuthError, PWSTR pszUserName, ULONG ulUserNameBufferSize, PWSTR pszPassword, ULONG ulPasswordBufferSize, BOOL *save, DWORD dwFlags) WCE_LINK(CredUIPromptForCredentialsW);
#endif
WCE_IMPORT DWORD WINAPI CredUIPromptForCredentialsA(PCREDUI_INFOA pUiInfo, PCSTR pszTargetName, PCtxtHandle pContext, DWORD dwAuthError, PSTR pszUserName, ULONG ulUserNameBufferSize, PSTR pszPassword, ULONG ulPasswordBufferSize, BOOL *save, DWORD dwFlags) WCE_LINK(CredUIPromptForCredentialsA);
WCE_IMPORT DWORD WINAPI CredUIPromptForWindowsCredentialsW(PCREDUI_INFOW pUiInfo, DWORD dwAuthError, ULONG *pulAuthPackage, LPCVOID pvInAuthBuffer, ULONG ulInAuthBufferSize, LPVOID * ppvOutAuthBuffer, ULONG * pulOutAuthBufferSize, BOOL *pfSave, DWORD dwFlags) WCE_LINK(CredUIPromptForWindowsCredentialsW);
WCE_IMPORT DWORD WINAPI CredUIPromptForWindowsCredentialsA(PCREDUI_INFOA pUiInfo, DWORD dwAuthError, ULONG *pulAuthPackage, LPCVOID pvInAuthBuffer, ULONG ulInAuthBufferSize, LPVOID * ppvOutAuthBuffer, ULONG * pulOutAuthBufferSize, BOOL *pfSave, DWORD dwFlags) WCE_LINK(CredUIPromptForWindowsCredentialsA);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI CredUIParseUserNameW(CONST WCHAR *UserName, WCHAR *user, ULONG userBufferSize, WCHAR *domain, ULONG domainBufferSize) WCE_LINK(CredUIParseUserNameW);
#endif
WCE_IMPORT DWORD WINAPI CredUIParseUserNameA(CONST CHAR *userName, CHAR *user, ULONG userBufferSize, CHAR *domain, ULONG domainBufferSize) WCE_LINK(CredUIParseUserNameA);
WCE_IMPORT DWORD WINAPI CredUICmdLinePromptForCredentialsW(PCWSTR pszTargetName, PCtxtHandle pContext, DWORD dwAuthError, PWSTR UserName, ULONG ulUserBufferSize, PWSTR pszPassword, ULONG ulPasswordBufferSize, PBOOL pfSave, DWORD dwFlags) WCE_LINK(CredUICmdLinePromptForCredentialsW);
WCE_IMPORT DWORD WINAPI CredUICmdLinePromptForCredentialsA(PCSTR pszTargetName, PCtxtHandle pContext, DWORD dwAuthError, PSTR UserName, ULONG ulUserBufferSize, PSTR pszPassword, ULONG ulPasswordBufferSize, PBOOL pfSave, DWORD dwFlags) WCE_LINK(CredUICmdLinePromptForCredentialsA);
WCE_IMPORT DWORD WINAPI CredUIConfirmCredentialsW(PCWSTR pszTargetName, BOOL bConfirm) WCE_LINK(CredUIConfirmCredentialsW);
WCE_IMPORT DWORD WINAPI CredUIConfirmCredentialsA(PCSTR pszTargetName, BOOL bConfirm) WCE_LINK(CredUIConfirmCredentialsA);
WCE_IMPORT DWORD WINAPI CredUIStoreSSOCredW(PCWSTR pszRealm, PCWSTR pszUsername, PCWSTR pszPassword, BOOL bPersist) WCE_LINK(CredUIStoreSSOCredW);
WCE_IMPORT DWORD WINAPI CredUIReadSSOCredW(PCWSTR pszRealm, PWSTR* ppszUsername) WCE_LINK(CredUIReadSSOCredW);

#define CredEnumerate CredEnumerateW
#define CredWriteDomainCredentials CredWriteDomainCredentialsW
#define CredReadDomainCredentials CredReadDomainCredentialsW
#define CredRename CredRenameW
#define CredGetTargetInfo CredGetTargetInfoW
#define CredUnmarshalCredential CredUnmarshalCredentialW
#define CredIsMarshaledCredential CredIsMarshaledCredentialW
#define CredUnPackAuthenticationBuffer CredUnPackAuthenticationBufferW
#define CredPackAuthenticationBuffer CredPackAuthenticationBufferW
#define CredUnprotect CredUnprotectW
#define CredFindBestCredential CredFindBestCredentialW
#define CredUIPromptForCredentials CredUIPromptForCredentialsW
#define CredUIPromptForWindowsCredentials CredUIPromptForWindowsCredentialsW
#define CredUIParseUserName CredUIParseUserNameW
#define CredUICmdLinePromptForCredentials CredUICmdLinePromptForCredentialsW
#define CredUIConfirmCredentials CredUIConfirmCredentialsW
#define CredUIStoreSSOCred CredUIStoreSSOCredW
#define CredUIReadSSOCred CredUIReadSSOCredW
#ifdef __cplusplus
}
#endif
#endif

