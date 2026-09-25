/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINCRYPT_H
#define WCE_WINCRYPT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagVTableProvStruc { DWORD Version; FARPROC FuncVerifyImage; FARPROC FuncReturnhWnd; DWORD dwProvType; BYTE *pbContextInfo; DWORD cbContextInfo; LPWSTR pszProvName; } VTableProvStruc, *PVTableProvStruc, *LPVTableProvStruc;
typedef struct tagRSAPUBKEY { DWORD magic; DWORD bitlen; DWORD pubexp; } RSAPUBKEY, *PRSAPUBKEY, *LPRSAPUBKEY;
typedef struct tagDHPUBKEY { DWORD magic; DWORD bitlen; } DHPUBKEY, *PDHPUBKEY, *LPDHPUBKEY;
typedef struct tagDSSSEED { DWORD counter; BYTE seed[20]; } DSSSEED, *PDSSSEED, *LPDSSSEED;
typedef struct tagDHPUBKEY_VER3 { DWORD magic; DWORD bitlenP; DWORD bitlenQ; DWORD bitlenJ; DSSSEED DSSSeed; } DHPUBKEY_VER3, *PDHPUBKEY_VER3, *LPDHPUBKEY_VER3;
typedef struct tagDHPRIVKEY_VER3 { DWORD magic; DWORD bitlenP; DWORD bitlenQ; DWORD bitlenJ; DWORD bitlenX; DSSSEED DSSSeed; } DHPRIVKEY_VER3, *PDHPRIVKEY_VER3, *LPDHPRIVKEY_VER3;
typedef struct tagKEY_TYPE_SUBTYPE { DWORD dwKeySpec; GUID Type; GUID Subtype; } KEY_TYPE_SUBTYPE, *PKEY_TYPE_SUBTYPE, *LPKEY_TYPE_SUBTYPE;
typedef struct tagCERT_FORTEZZA_DATA_PROP { unsigned char SerialNumber[8]; int CertIndex; unsigned char CertLabel[36]; } CERT_FORTEZZA_DATA_PROP, *PCERT_FORTEZZA_DATA_PROP, *LPCERT_FORTEZZA_DATA_PROP;
typedef struct tagCRYPT_INTEGER_BLOB { DWORD cbData; BYTE *pbData; } CRYPT_INTEGER_BLOB, *PCRYPT_INTEGER_BLOB, *LPCRYPT_INTEGER_BLOB;
typedef struct tagCRYPT_BIT_BLOB { DWORD cbData; BYTE *pbData; DWORD cUnusedBits; } CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB, *LPCRYPT_BIT_BLOB;
typedef struct tagCRYPT_OBJID_TABLE { DWORD dwAlgId; LPCSTR pszObjId; } CRYPT_OBJID_TABLE, *PCRYPT_OBJID_TABLE, *LPCRYPT_OBJID_TABLE;
typedef struct tagCRYPT_ATTRIBUTES { IN DWORD cAttr; IN PCRYPT_ATTRIBUTE rgAttr; } CRYPT_ATTRIBUTES, *PCRYPT_ATTRIBUTES, *LPCRYPT_ATTRIBUTES;
typedef struct tagCERT_RDN { DWORD cRDNAttr; PCERT_RDN_ATTR rgRDNAttr; } CERT_RDN, *PCERT_RDN, *LPCERT_RDN;
typedef struct tagCERT_NAME_INFO { DWORD cRDN; PCERT_RDN rgRDN; } CERT_NAME_INFO, *PCERT_NAME_INFO, *LPCERT_NAME_INFO;
typedef struct tagCRL_ENTRY { CRYPT_INTEGER_BLOB SerialNumber; FILETIME RevocationDate; DWORD cExtension; PCERT_EXTENSION rgExtension; } CRL_ENTRY, *PCRL_ENTRY, *LPCRL_ENTRY;
typedef struct tagCTL_USAGE { DWORD cUsageIdentifier; LPSTR *rgpszUsageIdentifier; } CTL_USAGE, *PCTL_USAGE, *LPCTL_USAGE;
typedef struct tagCRYPT_ENROLLMENT_NAME_VALUE_PAIR { LPWSTR pwszName; LPWSTR pwszValue; } CRYPT_ENROLLMENT_NAME_VALUE_PAIR, *PCRYPT_ENROLLMENT_NAME_VALUE_PAIR, *LPCRYPT_ENROLLMENT_NAME_VALUE_PAIR;
typedef struct tagCRYPT_CSP_PROVIDER { DWORD dwKeySpec; LPWSTR pwszProviderName; CRYPT_BIT_BLOB Signature; } CRYPT_CSP_PROVIDER, *PCRYPT_CSP_PROVIDER, *LPCRYPT_CSP_PROVIDER;
typedef struct tagCERT_EXTENSIONS { DWORD cExtension; PCERT_EXTENSION rgExtension; } CERT_EXTENSIONS, *PCERT_EXTENSIONS, *LPCERT_EXTENSIONS;
typedef struct tagCERT_PRIVATE_KEY_VALIDITY { FILETIME NotBefore; FILETIME NotAfter; } CERT_PRIVATE_KEY_VALIDITY, *PCERT_PRIVATE_KEY_VALIDITY, *LPCERT_PRIVATE_KEY_VALIDITY;
typedef struct tagCERT_POLICY_ID { DWORD cCertPolicyElementId; LPSTR *rgpszCertPolicyElementId; } CERT_POLICY_ID, *PCERT_POLICY_ID, *LPCERT_POLICY_ID;
typedef struct tagCERT_KEY_USAGE_RESTRICTION_INFO { DWORD cCertPolicyId; PCERT_POLICY_ID rgCertPolicyId; CRYPT_BIT_BLOB RestrictedKeyUsage; } CERT_KEY_USAGE_RESTRICTION_INFO, *PCERT_KEY_USAGE_RESTRICTION_INFO, *LPCERT_KEY_USAGE_RESTRICTION_INFO;
typedef struct tagCERT_BASIC_CONSTRAINTS2_INFO { BOOL fCA; BOOL fPathLenConstraint; DWORD dwPathLenConstraint; } CERT_BASIC_CONSTRAINTS2_INFO, *PCERT_BASIC_CONSTRAINTS2_INFO, *LPCERT_BASIC_CONSTRAINTS2_INFO;
typedef struct tagCERT_POLICY_QUALIFIER_NOTICE_REFERENCE { LPSTR pszOrganization; DWORD cNoticeNumbers; int *rgNoticeNumbers; } CERT_POLICY_QUALIFIER_NOTICE_REFERENCE, *PCERT_POLICY_QUALIFIER_NOTICE_REFERENCE, *LPCERT_POLICY_QUALIFIER_NOTICE_REFERENCE;
typedef struct tagCERT_POLICY_QUALIFIER_USER_NOTICE { CERT_POLICY_QUALIFIER_NOTICE_REFERENCE *pNoticeReference; LPWSTR pszDisplayText; } CERT_POLICY_QUALIFIER_USER_NOTICE, *PCERT_POLICY_QUALIFIER_USER_NOTICE, *LPCERT_POLICY_QUALIFIER_USER_NOTICE;
typedef struct tagCERT_POLICY_MAPPING { LPSTR pszIssuerDomainPolicy; LPSTR pszSubjectDomainPolicy; } CERT_POLICY_MAPPING, *PCERT_POLICY_MAPPING, *LPCERT_POLICY_MAPPING;
typedef struct tagCERT_POLICY_MAPPINGS_INFO { DWORD cPolicyMapping; PCERT_POLICY_MAPPING rgPolicyMapping; } CERT_POLICY_MAPPINGS_INFO, *PCERT_POLICY_MAPPINGS_INFO, *LPCERT_POLICY_MAPPINGS_INFO;
typedef struct tagCERT_POLICY_CONSTRAINTS_INFO { BOOL fRequireExplicitPolicy; DWORD dwRequireExplicitPolicySkipCerts; BOOL fInhibitPolicyMapping; DWORD dwInhibitPolicyMappingSkipCerts; } CERT_POLICY_CONSTRAINTS_INFO, *PCERT_POLICY_CONSTRAINTS_INFO, *LPCERT_POLICY_CONSTRAINTS_INFO;
typedef struct tagCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY { LPSTR pszObjId; DWORD cValue; PCRYPT_DER_BLOB rgValue; } CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY, *PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY, *LPCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;
typedef struct tagCRYPT_SEQUENCE_OF_ANY { DWORD cValue; PCRYPT_DER_BLOB rgValue; } CRYPT_SEQUENCE_OF_ANY, *PCRYPT_SEQUENCE_OF_ANY, *LPCRYPT_SEQUENCE_OF_ANY;
typedef struct tagCERT_X942_DH_VALIDATION_PARAMS { CRYPT_BIT_BLOB seed; DWORD pgenCounter; } CERT_X942_DH_VALIDATION_PARAMS, *PCERT_X942_DH_VALIDATION_PARAMS, *LPCERT_X942_DH_VALIDATION_PARAMS;
typedef struct tagCRYPT_RC2_CBC_PARAMETERS { DWORD dwVersion; BOOL fIV; BYTE rgbIV[8]; } CRYPT_RC2_CBC_PARAMETERS, *PCRYPT_RC2_CBC_PARAMETERS, *LPCRYPT_RC2_CBC_PARAMETERS;
typedef struct tagCMC_ADD_EXTENSIONS_INFO { DWORD dwCmcDataReference; DWORD cCertReference; DWORD *rgdwCertReference; DWORD cExtension; PCERT_EXTENSION rgExtension; } CMC_ADD_EXTENSIONS_INFO, *PCMC_ADD_EXTENSIONS_INFO, *LPCMC_ADD_EXTENSIONS_INFO;
typedef struct tagCMC_ADD_ATTRIBUTES_INFO { DWORD dwCmcDataReference; DWORD cCertReference; DWORD *rgdwCertReference; DWORD cAttribute; PCRYPT_ATTRIBUTE rgAttribute; } CMC_ADD_ATTRIBUTES_INFO, *PCMC_ADD_ATTRIBUTES_INFO, *LPCMC_ADD_ATTRIBUTES_INFO;
typedef struct tagCERT_TEMPLATE_EXT { LPSTR pszObjId; DWORD dwMajorVersion; BOOL fMinorVersion; DWORD dwMinorVersion; } CERT_TEMPLATE_EXT, *PCERT_TEMPLATE_EXT, *LPCERT_TEMPLATE_EXT;
typedef struct tagCRYPT_OID_FUNC_ENTRY { LPCSTR pszOID; void *pvFuncAddr; } CRYPT_OID_FUNC_ENTRY, *PCRYPT_OID_FUNC_ENTRY, *LPCRYPT_OID_FUNC_ENTRY;
typedef struct tagCMSG_RC2_AUX_INFO { DWORD cbSize; DWORD dwBitLen; } CMSG_RC2_AUX_INFO, *PCMSG_RC2_AUX_INFO, *LPCMSG_RC2_AUX_INFO;
typedef struct tagCMSG_SP3_COMPATIBLE_AUX_INFO { DWORD cbSize; DWORD dwFlags; } CMSG_SP3_COMPATIBLE_AUX_INFO, *PCMSG_SP3_COMPATIBLE_AUX_INFO, *LPCMSG_SP3_COMPATIBLE_AUX_INFO;
typedef struct tagCMSG_RC4_AUX_INFO { DWORD cbSize; DWORD dwBitLen; } CMSG_RC4_AUX_INFO, *PCMSG_RC4_AUX_INFO, *LPCMSG_RC4_AUX_INFO;
typedef struct tagCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA { DWORD cbSize; DWORD dwSignerIndex; DWORD dwUnauthAttrIndex; } CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, *LPCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;
typedef struct tagCRYPT_KEY_PROV_PARAM { DWORD dwParam; BYTE *pbData; DWORD cbData; DWORD dwFlags; } CRYPT_KEY_PROV_PARAM, *PCRYPT_KEY_PROV_PARAM, *LPCRYPT_KEY_PROV_PARAM;
typedef struct tagCRYPT_KEY_PROV_INFO { LPWSTR pwszContainerName; LPWSTR pwszProvName; DWORD dwProvType; DWORD dwFlags; DWORD cProvParam; PCRYPT_KEY_PROV_PARAM rgProvParam; DWORD dwKeySpec; } CRYPT_KEY_PROV_INFO, *PCRYPT_KEY_PROV_INFO, *LPCRYPT_KEY_PROV_INFO;
typedef struct tagCERT_REGISTRY_STORE_CLIENT_GPT_PARA { HKEY hKeyBase; LPWSTR pwszRegPath; } CERT_REGISTRY_STORE_CLIENT_GPT_PARA, *PCERT_REGISTRY_STORE_CLIENT_GPT_PARA, *LPCERT_REGISTRY_STORE_CLIENT_GPT_PARA;
typedef struct tagCERT_REGISTRY_STORE_ROAMING_PARA { HKEY hKey; LPWSTR pwszStoreDirectory; } CERT_REGISTRY_STORE_ROAMING_PARA, *PCERT_REGISTRY_STORE_ROAMING_PARA, *LPCERT_REGISTRY_STORE_ROAMING_PARA;
typedef struct tagCERT_LDAP_STORE_OPENED_PARA { void *pvLdapSessionHandle; LPCWSTR pwszLdapUrl; } CERT_LDAP_STORE_OPENED_PARA, *PCERT_LDAP_STORE_OPENED_PARA, *LPCERT_LDAP_STORE_OPENED_PARA;
typedef struct tagCERT_STORE_PROV_FIND_INFO { DWORD cbSize; DWORD dwMsgAndCertEncodingType; DWORD dwFindFlags; DWORD dwFindType; const void *pvFindPara; } CERT_STORE_PROV_FIND_INFO, *PCERT_STORE_PROV_FIND_INFO, *LPCERT_STORE_PROV_FIND_INFO;
typedef struct tagCRL_FIND_ISSUED_FOR_PARA { PCCERT_CONTEXT pSubjectCert; PCCERT_CONTEXT pIssuerCert; } CRL_FIND_ISSUED_FOR_PARA, *PCRL_FIND_ISSUED_FOR_PARA, *LPCRL_FIND_ISSUED_FOR_PARA;
typedef struct tagCERT_SYSTEM_STORE_INFO { DWORD cbSize; } CERT_SYSTEM_STORE_INFO, *PCERT_SYSTEM_STORE_INFO, *LPCERT_SYSTEM_STORE_INFO;
typedef struct tagCTL_VERIFY_USAGE_STATUS { DWORD cbSize; DWORD dwError; DWORD dwFlags; PCCTL_CONTEXT *ppCtl; DWORD dwCtlEntryIndex; PCCERT_CONTEXT *ppSigner; DWORD dwSignerIndex; } CTL_VERIFY_USAGE_STATUS, *PCTL_VERIFY_USAGE_STATUS, *LPCTL_VERIFY_USAGE_STATUS;
typedef struct tagCERT_REVOCATION_CRL_INFO { DWORD cbSize; PCCRL_CONTEXT pBaseCrlContext; PCCRL_CONTEXT pDeltaCrlContext; PCRL_ENTRY pCrlEntry; BOOL fDeltaCrlEntry; } CERT_REVOCATION_CRL_INFO, *PCERT_REVOCATION_CRL_INFO, *LPCERT_REVOCATION_CRL_INFO;
typedef struct tagCERT_REVOCATION_STATUS { DWORD cbSize; DWORD dwIndex; DWORD dwError; DWORD dwReason; BOOL fHasFreshnessTime; DWORD dwFreshnessTime; } CERT_REVOCATION_STATUS, *PCERT_REVOCATION_STATUS, *LPCERT_REVOCATION_STATUS;
typedef struct tagCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA { DWORD cOID; LPSTR *rgpszOID; } CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA, *PCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA, *LPCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA;
typedef struct tagCRYPT_BLOB_ARRAY { DWORD cBlob; PCRYPT_DATA_BLOB rgBlob; } CRYPT_BLOB_ARRAY, *PCRYPT_BLOB_ARRAY, *LPCRYPT_BLOB_ARRAY;
typedef struct tagCRYPT_CREDENTIALS { DWORD cbSize; LPCSTR pszCredentialsOid; LPVOID pvCredentials; } CRYPT_CREDENTIALS, *PCRYPT_CREDENTIALS, *LPCRYPT_CREDENTIALS;
typedef struct tagCRYPT_PASSWORD_CREDENTIALSA { DWORD cbSize; LPSTR pszUsername; LPSTR pszPassword; } CRYPT_PASSWORD_CREDENTIALSA, *PCRYPT_PASSWORD_CREDENTIALSA, *LPCRYPT_PASSWORD_CREDENTIALSA;
typedef struct tagCRYPT_PASSWORD_CREDENTIALSW { DWORD cbSize; LPWSTR pszUsername; LPWSTR pszPassword; } CRYPT_PASSWORD_CREDENTIALSW, *PCRYPT_PASSWORD_CREDENTIALSW, *LPCRYPT_PASSWORD_CREDENTIALSW;
typedef struct tagCRYPT_RETRIEVE_AUX_INFO { DWORD cbSize; FILETIME *pLastSyncTime; DWORD dwMaxUrlRetrievalByteCount; } CRYPT_RETRIEVE_AUX_INFO, *PCRYPT_RETRIEVE_AUX_INFO, *LPCRYPT_RETRIEVE_AUX_INFO;
typedef struct tagCRYPT_URL_ARRAY { DWORD cUrl; LPWSTR* rgwszUrl; } CRYPT_URL_ARRAY, *PCRYPT_URL_ARRAY, *LPCRYPT_URL_ARRAY;
typedef struct tagCRYPT_URL_INFO { DWORD cbSize; DWORD dwSyncDeltaTime; DWORD cGroup; DWORD *rgcGroupEntry; } CRYPT_URL_INFO, *PCRYPT_URL_INFO, *LPCRYPT_URL_INFO;
typedef struct tagCERT_CRL_CONTEXT_PAIR { PCCERT_CONTEXT pCertContext; PCCRL_CONTEXT pCrlContext; } CERT_CRL_CONTEXT_PAIR, *PCERT_CRL_CONTEXT_PAIR, *LPCERT_CRL_CONTEXT_PAIR;
typedef struct tagCRYPTPROTECT_PROMPTSTRUCT { DWORD cbSize; DWORD dwPromptFlags; HWND hwndApp; LPCWSTR szPrompt; } CRYPTPROTECT_PROMPTSTRUCT, *PCRYPTPROTECT_PROMPTSTRUCT, *LPCRYPTPROTECT_PROMPTSTRUCT;
typedef struct tagCERT_TRUST_STATUS { DWORD dwErrorStatus; DWORD dwInfoStatus; } CERT_TRUST_STATUS, *PCERT_TRUST_STATUS, *LPCERT_TRUST_STATUS;
typedef struct tagCERT_TRUST_LIST_INFO { DWORD cbSize; PCTL_ENTRY pCtlEntry; PCCTL_CONTEXT pCtlContext; } CERT_TRUST_LIST_INFO, *PCERT_TRUST_LIST_INFO, *LPCERT_TRUST_LIST_INFO;
typedef struct tagCTL_USAGE_MATCH { DWORD dwType; CTL_USAGE Usage; } CTL_USAGE_MATCH, *PCTL_USAGE_MATCH, *LPCTL_USAGE_MATCH;
typedef struct tagCRL_REVOCATION_INFO { PCRL_ENTRY pCrlEntry; PCCRL_CONTEXT pCrlContext; PCCERT_CHAIN_CONTEXT pCrlIssuerChain; } CRL_REVOCATION_INFO, *PCRL_REVOCATION_INFO, *LPCRL_REVOCATION_INFO;
typedef struct tagCERT_CHAIN_POLICY_PARA { DWORD cbSize; DWORD dwFlags; void *pvExtraPolicyPara; } CERT_CHAIN_POLICY_PARA, *PCERT_CHAIN_POLICY_PARA, *LPCERT_CHAIN_POLICY_PARA;
typedef struct tagCERT_CHAIN_POLICY_STATUS { DWORD cbSize; DWORD dwError; LONG lChainIndex; LONG lElementIndex; void *pvExtraPolicyStatus; } CERT_CHAIN_POLICY_STATUS, *PCERT_CHAIN_POLICY_STATUS, *LPCERT_CHAIN_POLICY_STATUS;
typedef struct tagAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS { DWORD cbSize; BOOL fCommercial; } AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS, *PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS, *LPAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS;
typedef struct tagAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA { DWORD cbSize; DWORD dwRegPolicySettings; BOOL fCommercial; } AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA, *PAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA, *LPAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA;

WCE_IMPORT BOOL WINAPI CryptSetProviderA(LPCSTR pszProvName, DWORD dwProvType) WCE_LINK(CryptSetProviderA);
WCE_IMPORT BOOL WINAPI CryptSetProviderW(LPCWSTR pszProvName, DWORD dwProvType) WCE_LINK(CryptSetProviderW);
WCE_IMPORT BOOL WINAPI CryptSetProviderExA(LPCSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags) WCE_LINK(CryptSetProviderExA);
WCE_IMPORT BOOL WINAPI CryptSetProviderExW(LPCWSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags) WCE_LINK(CryptSetProviderExW);
WCE_IMPORT BOOL WINAPI CryptGetDefaultProviderA(DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags, LPSTR pszProvName, DWORD *pcbProvName) WCE_LINK(CryptGetDefaultProviderA);
WCE_IMPORT BOOL WINAPI CryptGetDefaultProviderW(DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags, LPWSTR pszProvName, DWORD *pcbProvName) WCE_LINK(CryptGetDefaultProviderW);
WCE_IMPORT BOOL WINAPI CryptEnumProviderTypesA(DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType, LPSTR szTypeName, DWORD *pcbTypeName) WCE_LINK(CryptEnumProviderTypesA);
WCE_IMPORT BOOL WINAPI CryptEnumProviderTypesW(DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType, LPWSTR szTypeName, DWORD *pcbTypeName) WCE_LINK(CryptEnumProviderTypesW);
WCE_IMPORT BOOL WINAPI CryptEnumProvidersA(DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType, LPSTR szProvName, DWORD *pcbProvName) WCE_LINK(CryptEnumProvidersA);
WCE_IMPORT BOOL WINAPI CryptEnumProvidersW(DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType, LPWSTR szProvName, DWORD *pcbProvName) WCE_LINK(CryptEnumProvidersW);
WCE_IMPORT BOOL WINAPI CryptFormatObject(IN DWORD dwCertEncodingType, IN DWORD dwFormatType, IN DWORD dwFormatStrType, IN void *pFormatStruct, IN LPCSTR lpszStructType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, OUT void *pbFormat, IN OUT DWORD *pcbFormat) WCE_LINK(CryptFormatObject);
WCE_IMPORT BOOL WINAPI CryptEncodeObjectEx(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const void *pvStructInfo, IN DWORD dwFlags, IN OPTIONAL PCRYPT_ENCODE_PARA pEncodePara, OUT void *pvEncoded, IN OUT DWORD *pcbEncoded) WCE_LINK(CryptEncodeObjectEx);
WCE_IMPORT BOOL WINAPI CryptEncodeObject(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const void *pvStructInfo, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded) WCE_LINK(CryptEncodeObject);
WCE_IMPORT BOOL WINAPI CryptDecodeObjectEx(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, IN DWORD dwFlags, IN OPTIONAL PCRYPT_DECODE_PARA pDecodePara, OUT OPTIONAL void *pvStructInfo, IN OUT DWORD *pcbStructInfo) WCE_LINK(CryptDecodeObjectEx);
WCE_IMPORT BOOL WINAPI CryptDecodeObject(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, IN DWORD dwFlags, OUT void *pvStructInfo, IN OUT DWORD *pcbStructInfo) WCE_LINK(CryptDecodeObject);
WCE_IMPORT BOOL WINAPI CryptInstallOIDFunctionAddress(IN HMODULE hModule, IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN DWORD cFuncEntry, IN const CRYPT_OID_FUNC_ENTRY rgFuncEntry[], IN DWORD dwFlags) WCE_LINK(CryptInstallOIDFunctionAddress);
WCE_IMPORT BOOL WINAPI CryptRegisterOIDFunction(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN LPCSTR pszOID, IN OPTIONAL LPCWSTR pwszDll, IN OPTIONAL LPCSTR pszOverrideFuncName) WCE_LINK(CryptRegisterOIDFunction);
WCE_IMPORT BOOL WINAPI CryptUnregisterOIDFunction(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN LPCSTR pszOID) WCE_LINK(CryptUnregisterOIDFunction);
WCE_IMPORT BOOL WINAPI CryptRegisterDefaultOIDFunction(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN DWORD dwIndex, IN LPCWSTR pwszDll) WCE_LINK(CryptRegisterDefaultOIDFunction);
WCE_IMPORT BOOL WINAPI CryptUnregisterDefaultOIDFunction(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN LPCWSTR pwszDll) WCE_LINK(CryptUnregisterDefaultOIDFunction);
WCE_IMPORT BOOL WINAPI CryptSetOIDFunctionValue(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN LPCSTR pszOID, IN LPCWSTR pwszValueName, IN DWORD dwValueType, IN const BYTE *pbValueData, IN DWORD cbValueData) WCE_LINK(CryptSetOIDFunctionValue);
WCE_IMPORT BOOL WINAPI CryptGetOIDFunctionValue(IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN LPCSTR pszOID, IN LPCWSTR pwszValueName, OUT DWORD *pdwValueType, OUT BYTE *pbValueData, IN OUT DWORD *pcbValueData) WCE_LINK(CryptGetOIDFunctionValue);
WCE_IMPORT BOOL WINAPI CryptEnumOIDFunction(IN DWORD dwEncodingType, IN OPTIONAL LPCSTR pszFuncName, IN OPTIONAL LPCSTR pszOID, IN DWORD dwFlags, IN void *pvArg, IN PFN_CRYPT_ENUM_OID_FUNC pfnEnumOIDFunc) WCE_LINK(CryptEnumOIDFunction);
WCE_IMPORT PCCRYPT_OID_INFO WINAPI CryptFindOIDInfo(IN DWORD dwKeyType, IN void *pvKey, IN DWORD dwGroupId) WCE_LINK(CryptFindOIDInfo);
WCE_IMPORT BOOL WINAPI CryptRegisterOIDInfo(IN PCCRYPT_OID_INFO pInfo, IN DWORD dwFlags) WCE_LINK(CryptRegisterOIDInfo);
WCE_IMPORT BOOL WINAPI CryptUnregisterOIDInfo(IN PCCRYPT_OID_INFO pInfo) WCE_LINK(CryptUnregisterOIDInfo);
WCE_IMPORT BOOL WINAPI CryptEnumOIDInfo(IN DWORD dwGroupId, IN DWORD dwFlags, IN void *pvArg, IN PFN_CRYPT_ENUM_OID_INFO pfnEnumOIDInfo) WCE_LINK(CryptEnumOIDInfo);
WCE_IMPORT LPCWSTR WINAPI CryptFindLocalizedName(IN LPCWSTR pwszCryptName) WCE_LINK(CryptFindLocalizedName);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CryptMsgCalculateEncodedLength(IN DWORD dwMsgEncodingType, IN DWORD dwFlags, IN DWORD dwMsgType, IN void const *pvMsgEncodeInfo, IN OPTIONAL LPSTR pszInnerContentObjID, IN DWORD cbData) WCE_LINK(CryptMsgCalculateEncodedLength);
#endif
WCE_IMPORT BOOL WINAPI CryptMsgCountersignEncoded(IN DWORD dwEncodingType, IN PBYTE pbSignerInfo, IN DWORD cbSignerInfo, IN DWORD cCountersigners, IN PCMSG_SIGNER_ENCODE_INFO rgCountersigners, OUT PBYTE pbCountersignature, IN OUT PDWORD pcbCountersignature) WCE_LINK(CryptMsgCountersignEncoded);
WCE_IMPORT BOOL WINAPI CertVerifySubjectCertificateContext(IN PCCERT_CONTEXT pSubject, IN OPTIONAL PCCERT_CONTEXT pIssuer, IN OUT DWORD *pdwFlags) WCE_LINK(CertVerifySubjectCertificateContext);
WCE_IMPORT PCCERT_CONTEXT WINAPI CertDuplicateCertificateContext(IN PCCERT_CONTEXT pCertContext) WCE_LINK(CertDuplicateCertificateContext);
WCE_IMPORT PCCERT_CONTEXT WINAPI CertCreateCertificateContext(IN DWORD dwCertEncodingType, IN const BYTE *pbCertEncoded, IN DWORD cbCertEncoded) WCE_LINK(CertCreateCertificateContext);
WCE_IMPORT BOOL WINAPI CertFreeCertificateContext(IN PCCERT_CONTEXT pCertContext) WCE_LINK(CertFreeCertificateContext);
WCE_IMPORT BOOL WINAPI CertSetCertificateContextProperty(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId, IN DWORD dwFlags, IN const void *pvData) WCE_LINK(CertSetCertificateContextProperty);
WCE_IMPORT BOOL WINAPI CertGetCertificateContextProperty(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId, OUT void *pvData, IN OUT DWORD *pcbData) WCE_LINK(CertGetCertificateContextProperty);
WCE_IMPORT DWORD WINAPI CertEnumCertificateContextProperties(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId) WCE_LINK(CertEnumCertificateContextProperties);
WCE_IMPORT BOOL WINAPI CertCreateCTLEntryFromCertificateContextProperties(IN PCCERT_CONTEXT pCertContext, IN DWORD cOptAttr, IN OPTIONAL PCRYPT_ATTRIBUTE rgOptAttr, IN DWORD dwFlags, IN OPTIONAL void *pvReserved, OUT OPTIONAL PCTL_ENTRY pCtlEntry, IN OUT DWORD *pcbCtlEntry) WCE_LINK(CertCreateCTLEntryFromCertificateContextProperties);
WCE_IMPORT BOOL WINAPI CertSetCertificateContextPropertiesFromCTLEntry(IN PCCERT_CONTEXT pCertContext, IN PCTL_ENTRY pCtlEntry, IN DWORD dwFlags) WCE_LINK(CertSetCertificateContextPropertiesFromCTLEntry);
WCE_IMPORT PCCRL_CONTEXT WINAPI CertDuplicateCRLContext(IN PCCRL_CONTEXT pCrlContext) WCE_LINK(CertDuplicateCRLContext);
WCE_IMPORT PCCRL_CONTEXT WINAPI CertCreateCRLContext(IN DWORD dwCertEncodingType, IN const BYTE *pbCrlEncoded, IN DWORD cbCrlEncoded) WCE_LINK(CertCreateCRLContext);
WCE_IMPORT BOOL WINAPI CertFreeCRLContext(IN PCCRL_CONTEXT pCrlContext) WCE_LINK(CertFreeCRLContext);
WCE_IMPORT BOOL WINAPI CertSetCRLContextProperty(IN PCCRL_CONTEXT pCrlContext, IN DWORD dwPropId, IN DWORD dwFlags, IN const void *pvData) WCE_LINK(CertSetCRLContextProperty);
WCE_IMPORT BOOL WINAPI CertGetCRLContextProperty(IN PCCRL_CONTEXT pCrlContext, IN DWORD dwPropId, OUT void *pvData, IN OUT DWORD *pcbData) WCE_LINK(CertGetCRLContextProperty);
WCE_IMPORT DWORD WINAPI CertEnumCRLContextProperties(IN PCCRL_CONTEXT pCrlContext, IN DWORD dwPropId) WCE_LINK(CertEnumCRLContextProperties);
WCE_IMPORT BOOL WINAPI CertFindCertificateInCRL(IN PCCERT_CONTEXT pCert, IN PCCRL_CONTEXT pCrlContext, IN DWORD dwFlags, IN OPTIONAL void *pvReserved, OUT PCRL_ENTRY *ppCrlEntry) WCE_LINK(CertFindCertificateInCRL);
WCE_IMPORT BOOL WINAPI CertIsValidCRLForCertificate(IN PCCERT_CONTEXT pCert, IN PCCRL_CONTEXT pCrl, IN DWORD dwFlags, IN void *pvReserved) WCE_LINK(CertIsValidCRLForCertificate);
WCE_IMPORT BOOL WINAPI CertDeleteCertificateFromStore(IN PCCERT_CONTEXT pCertContext) WCE_LINK(CertDeleteCertificateFromStore);
WCE_IMPORT BOOL WINAPI CertDeleteCRLFromStore(IN PCCRL_CONTEXT pCrlContext) WCE_LINK(CertDeleteCRLFromStore);
WCE_IMPORT BOOL WINAPI CertSerializeCertificateStoreElement(IN PCCERT_CONTEXT pCertContext, IN DWORD dwFlags, OUT BYTE *pbElement, IN OUT DWORD *pcbElement) WCE_LINK(CertSerializeCertificateStoreElement);
WCE_IMPORT BOOL WINAPI CertSerializeCRLStoreElement(IN PCCRL_CONTEXT pCrlContext, IN DWORD dwFlags, OUT BYTE *pbElement, IN OUT DWORD *pcbElement) WCE_LINK(CertSerializeCRLStoreElement);
WCE_IMPORT PCCTL_CONTEXT WINAPI CertDuplicateCTLContext(IN PCCTL_CONTEXT pCtlContext) WCE_LINK(CertDuplicateCTLContext);
WCE_IMPORT PCCTL_CONTEXT WINAPI CertCreateCTLContext(IN DWORD dwMsgAndCertEncodingType, IN const BYTE *pbCtlEncoded, IN DWORD cbCtlEncoded) WCE_LINK(CertCreateCTLContext);
WCE_IMPORT BOOL WINAPI CertFreeCTLContext(IN PCCTL_CONTEXT pCtlContext) WCE_LINK(CertFreeCTLContext);
WCE_IMPORT BOOL WINAPI CertSetCTLContextProperty(IN PCCTL_CONTEXT pCtlContext, IN DWORD dwPropId, IN DWORD dwFlags, IN const void *pvData) WCE_LINK(CertSetCTLContextProperty);
WCE_IMPORT BOOL WINAPI CertGetCTLContextProperty(IN PCCTL_CONTEXT pCtlContext, IN DWORD dwPropId, OUT void *pvData, IN OUT DWORD *pcbData) WCE_LINK(CertGetCTLContextProperty);
WCE_IMPORT DWORD WINAPI CertEnumCTLContextProperties(IN PCCTL_CONTEXT pCtlContext, IN DWORD dwPropId) WCE_LINK(CertEnumCTLContextProperties);
WCE_IMPORT PCTL_ENTRY WINAPI CertFindSubjectInCTL(IN DWORD dwEncodingType, IN DWORD dwSubjectType, IN void *pvSubject, IN PCCTL_CONTEXT pCtlContext, IN DWORD dwFlags) WCE_LINK(CertFindSubjectInCTL);
WCE_IMPORT BOOL WINAPI CertSerializeCTLStoreElement(IN PCCTL_CONTEXT pCtlContext, IN DWORD dwFlags, OUT BYTE *pbElement, IN OUT DWORD *pcbElement) WCE_LINK(CertSerializeCTLStoreElement);
WCE_IMPORT BOOL WINAPI CertDeleteCTLFromStore(IN PCCTL_CONTEXT pCtlContext) WCE_LINK(CertDeleteCTLFromStore);
WCE_IMPORT const void* WINAPI CertCreateContext(IN DWORD dwContextType, IN DWORD dwEncodingType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, IN DWORD dwFlags, IN OPTIONAL PCERT_CREATE_CONTEXT_PARA pCreatePara) WCE_LINK(CertCreateContext);
WCE_IMPORT BOOL WINAPI CertRegisterSystemStore(IN const void *pvSystemStore, IN DWORD dwFlags, IN PCERT_SYSTEM_STORE_INFO pStoreInfo, IN OPTIONAL void *pvReserved) WCE_LINK(CertRegisterSystemStore);
WCE_IMPORT BOOL WINAPI CertRegisterPhysicalStore(IN const void *pvSystemStore, IN DWORD dwFlags, IN LPCWSTR pwszStoreName, IN PCERT_PHYSICAL_STORE_INFO pStoreInfo, IN OPTIONAL void *pvReserved) WCE_LINK(CertRegisterPhysicalStore);
WCE_IMPORT BOOL WINAPI CertUnregisterSystemStore(IN const void *pvSystemStore, IN DWORD dwFlags) WCE_LINK(CertUnregisterSystemStore);
WCE_IMPORT BOOL WINAPI CertUnregisterPhysicalStore(IN const void *pvSystemStore, IN DWORD dwFlags, IN LPCWSTR pwszStoreName) WCE_LINK(CertUnregisterPhysicalStore);
WCE_IMPORT BOOL WINAPI CertEnumSystemStoreLocation(IN DWORD dwFlags, IN void *pvArg, IN PFN_CERT_ENUM_SYSTEM_STORE_LOCATION pfnEnum) WCE_LINK(CertEnumSystemStoreLocation);
WCE_IMPORT BOOL WINAPI CertEnumSystemStore(IN DWORD dwFlags, IN OPTIONAL void *pvSystemStoreLocationPara, IN void *pvArg, IN PFN_CERT_ENUM_SYSTEM_STORE pfnEnum) WCE_LINK(CertEnumSystemStore);
WCE_IMPORT BOOL WINAPI CertEnumPhysicalStore(IN const void *pvSystemStore, IN DWORD dwFlags, IN void *pvArg, IN PFN_CERT_ENUM_PHYSICAL_STORE pfnEnum) WCE_LINK(CertEnumPhysicalStore);
WCE_IMPORT BOOL WINAPI CertGetEnhancedKeyUsage(IN PCCERT_CONTEXT pCertContext, IN DWORD dwFlags, OUT PCERT_ENHKEY_USAGE pUsage, IN OUT DWORD *pcbUsage) WCE_LINK(CertGetEnhancedKeyUsage);
WCE_IMPORT BOOL WINAPI CertSetEnhancedKeyUsage(IN PCCERT_CONTEXT pCertContext, IN PCERT_ENHKEY_USAGE pUsage) WCE_LINK(CertSetEnhancedKeyUsage);
WCE_IMPORT BOOL WINAPI CertAddEnhancedKeyUsageIdentifier(IN PCCERT_CONTEXT pCertContext, IN LPCSTR pszUsageIdentifier) WCE_LINK(CertAddEnhancedKeyUsageIdentifier);
WCE_IMPORT BOOL WINAPI CertRemoveEnhancedKeyUsageIdentifier(IN PCCERT_CONTEXT pCertContext, IN LPCSTR pszUsageIdentifier) WCE_LINK(CertRemoveEnhancedKeyUsageIdentifier);
WCE_IMPORT BOOL WINAPI CertGetValidUsages(IN DWORD cCerts, IN PCCERT_CONTEXT *rghCerts, OUT int *cNumOIDs, OUT LPSTR *rghOIDs, IN OUT DWORD *pcbOIDs) WCE_LINK(CertGetValidUsages);
WCE_IMPORT BOOL WINAPI CryptMsgSignCTL(IN DWORD dwMsgEncodingType, IN BYTE *pbCtlContent, IN DWORD cbCtlContent, IN PCMSG_SIGNED_ENCODE_INFO pSignInfo, IN DWORD dwFlags, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded) WCE_LINK(CryptMsgSignCTL);
WCE_IMPORT BOOL WINAPI CryptMsgEncodeAndSignCTL(IN DWORD dwMsgEncodingType, IN PCTL_INFO pCtlInfo, IN PCMSG_SIGNED_ENCODE_INFO pSignInfo, IN DWORD dwFlags, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded) WCE_LINK(CryptMsgEncodeAndSignCTL);
WCE_IMPORT BOOL WINAPI CertFindSubjectInSortedCTL(IN PCRYPT_DATA_BLOB pSubjectIdentifier, IN PCCTL_CONTEXT pCtlContext, IN DWORD dwFlags, IN void *pvReserved, OUT OPTIONAL PCRYPT_DER_BLOB pEncodedAttributes) WCE_LINK(CertFindSubjectInSortedCTL);
WCE_IMPORT BOOL WINAPI CertEnumSubjectInSortedCTL(IN PCCTL_CONTEXT pCtlContext, IN OUT void **ppvNextSubject, OUT OPTIONAL PCRYPT_DER_BLOB pSubjectIdentifier, OUT OPTIONAL PCRYPT_DER_BLOB pEncodedAttributes) WCE_LINK(CertEnumSubjectInSortedCTL);
WCE_IMPORT BOOL WINAPI CertVerifyCTLUsage(IN DWORD dwEncodingType, IN DWORD dwSubjectType, IN void *pvSubject, IN PCTL_USAGE pSubjectUsage, IN DWORD dwFlags, IN OPTIONAL PCTL_VERIFY_USAGE_PARA pVerifyUsagePara, IN OUT PCTL_VERIFY_USAGE_STATUS pVerifyUsageStatus) WCE_LINK(CertVerifyCTLUsage);
WCE_IMPORT BOOL WINAPI CertVerifyRevocation(IN DWORD dwEncodingType, IN DWORD dwRevType, IN DWORD cContext, IN PVOID rgpvContext[], IN DWORD dwFlags, IN OPTIONAL PCERT_REVOCATION_PARA pRevPara, IN OUT PCERT_REVOCATION_STATUS pRevStatus) WCE_LINK(CertVerifyRevocation);
WCE_IMPORT BOOL WINAPI CertCompareIntegerBlob(IN PCRYPT_INTEGER_BLOB pInt1, IN PCRYPT_INTEGER_BLOB pInt2) WCE_LINK(CertCompareIntegerBlob);
WCE_IMPORT BOOL WINAPI CertCompareCertificate(IN DWORD dwCertEncodingType, IN PCERT_INFO pCertId1, IN PCERT_INFO pCertId2) WCE_LINK(CertCompareCertificate);
WCE_IMPORT BOOL WINAPI CertCompareCertificateName(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pCertName1, IN PCERT_NAME_BLOB pCertName2) WCE_LINK(CertCompareCertificateName);
WCE_IMPORT BOOL WINAPI CertIsRDNAttrsInCertificateName(IN DWORD dwCertEncodingType, IN DWORD dwFlags, IN PCERT_NAME_BLOB pCertName, IN PCERT_RDN pRDN) WCE_LINK(CertIsRDNAttrsInCertificateName);
WCE_IMPORT BOOL WINAPI CertComparePublicKeyInfo(IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pPublicKey1, IN PCERT_PUBLIC_KEY_INFO pPublicKey2) WCE_LINK(CertComparePublicKeyInfo);
WCE_IMPORT DWORD WINAPI CertGetPublicKeyLength(IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pPublicKey) WCE_LINK(CertGetPublicKeyLength);
WCE_IMPORT LONG WINAPI CertVerifyTimeValidity(IN LPFILETIME pTimeToVerify, IN PCERT_INFO pCertInfo) WCE_LINK(CertVerifyTimeValidity);
WCE_IMPORT LONG WINAPI CertVerifyCRLTimeValidity(IN LPFILETIME pTimeToVerify, IN PCRL_INFO pCrlInfo) WCE_LINK(CertVerifyCRLTimeValidity);
WCE_IMPORT BOOL WINAPI CertVerifyValidityNesting(IN PCERT_INFO pSubjectInfo, IN PCERT_INFO pIssuerInfo) WCE_LINK(CertVerifyValidityNesting);
WCE_IMPORT BOOL WINAPI CertVerifyCRLRevocation(IN DWORD dwCertEncodingType, IN PCERT_INFO pCertId, IN DWORD cCrlInfo, IN PCRL_INFO rgpCrlInfo[]) WCE_LINK(CertVerifyCRLRevocation);
WCE_IMPORT LPCSTR WINAPI CertAlgIdToOID(IN DWORD dwAlgId) WCE_LINK(CertAlgIdToOID);
WCE_IMPORT DWORD WINAPI CertOIDToAlgId(IN LPCSTR pszObjId) WCE_LINK(CertOIDToAlgId);
WCE_IMPORT PCERT_RDN_ATTR WINAPI CertFindRDNAttr(IN LPCSTR pszObjId, IN PCERT_NAME_INFO pName) WCE_LINK(CertFindRDNAttr);
WCE_IMPORT BOOL WINAPI CertGetIntendedKeyUsage(IN DWORD dwCertEncodingType, IN PCERT_INFO pCertInfo, OUT BYTE *pbKeyUsage, IN DWORD cbKeyUsage) WCE_LINK(CertGetIntendedKeyUsage);
WCE_IMPORT BOOL WINAPI CryptFindCertificateKeyProvInfo(IN PCCERT_CONTEXT pCert, IN DWORD dwFlags, IN void *pvReserved) WCE_LINK(CryptFindCertificateKeyProvInfo);
WCE_IMPORT DWORD WINAPI CertRDNValueToStrA(IN DWORD dwValueType, IN PCERT_RDN_VALUE_BLOB pValue, OUT OPTIONAL LPSTR psz, IN DWORD csz) WCE_LINK(CertRDNValueToStrA);
WCE_IMPORT DWORD WINAPI CertRDNValueToStrW(IN DWORD dwValueType, IN PCERT_RDN_VALUE_BLOB pValue, OUT OPTIONAL LPWSTR psz, IN DWORD csz) WCE_LINK(CertRDNValueToStrW);
WCE_IMPORT DWORD WINAPI CertNameToStrA(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pName, IN DWORD dwStrType, OUT OPTIONAL LPSTR psz, IN DWORD csz) WCE_LINK(CertNameToStrA);
WCE_IMPORT DWORD WINAPI CertNameToStrW(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pName, IN DWORD dwStrType, OUT OPTIONAL LPWSTR psz, IN DWORD csz) WCE_LINK(CertNameToStrW);
WCE_IMPORT BOOL WINAPI CertStrToNameA(IN DWORD dwCertEncodingType, IN LPCSTR pszX500, IN DWORD dwStrType, IN OPTIONAL void *pvReserved, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded, OUT OPTIONAL LPCSTR *ppszError) WCE_LINK(CertStrToNameA);
WCE_IMPORT BOOL WINAPI CertStrToNameW(IN DWORD dwCertEncodingType, IN LPCWSTR pszX500, IN DWORD dwStrType, IN OPTIONAL void *pvReserved, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded, OUT OPTIONAL LPCWSTR *ppszError) WCE_LINK(CertStrToNameW);
WCE_IMPORT DWORD WINAPI CertGetNameStringA(IN PCCERT_CONTEXT pCertContext, IN DWORD dwType, IN DWORD dwFlags, IN void *pvTypePara, OUT OPTIONAL LPSTR pszNameString, IN DWORD cchNameString) WCE_LINK(CertGetNameStringA);
WCE_IMPORT DWORD WINAPI CertGetNameStringW(IN PCCERT_CONTEXT pCertContext, IN DWORD dwType, IN DWORD dwFlags, IN void *pvTypePara, OUT OPTIONAL LPWSTR pszNameString, IN DWORD cchNameString) WCE_LINK(CertGetNameStringW);
WCE_IMPORT BOOL WINAPI CryptSignMessage(IN PCRYPT_SIGN_MESSAGE_PARA pSignPara, IN BOOL fDetachedSignature, IN DWORD cToBeSigned, IN const BYTE *rgpbToBeSigned[], IN DWORD rgcbToBeSigned[], OUT BYTE *pbSignedBlob, IN OUT DWORD *pcbSignedBlob) WCE_LINK(CryptSignMessage);
WCE_IMPORT BOOL WINAPI CryptVerifyMessageSignature(IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, IN DWORD dwSignerIndex, IN const BYTE *pbSignedBlob, IN DWORD cbSignedBlob, OUT BYTE OPTIONAL *pbDecoded, IN OUT OPTIONAL DWORD *pcbDecoded, OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert) WCE_LINK(CryptVerifyMessageSignature);
WCE_IMPORT LONG WINAPI CryptGetMessageSignerCount(IN DWORD dwMsgEncodingType, IN const BYTE *pbSignedBlob, IN DWORD cbSignedBlob) WCE_LINK(CryptGetMessageSignerCount);
WCE_IMPORT BOOL WINAPI CryptVerifyDetachedMessageSignature(IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, IN DWORD dwSignerIndex, IN const BYTE *pbDetachedSignBlob, IN DWORD cbDetachedSignBlob, IN DWORD cToBeSigned, IN const BYTE *rgpbToBeSigned[], IN DWORD rgcbToBeSigned[], OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert) WCE_LINK(CryptVerifyDetachedMessageSignature);
WCE_IMPORT BOOL WINAPI CryptEncryptMessage(IN PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, IN DWORD cRecipientCert, IN PCCERT_CONTEXT rgpRecipientCert[], IN const BYTE *pbToBeEncrypted, IN DWORD cbToBeEncrypted, OUT BYTE *pbEncryptedBlob, IN OUT DWORD *pcbEncryptedBlob) WCE_LINK(CryptEncryptMessage);
WCE_IMPORT BOOL WINAPI CryptDecryptMessage(IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara, IN const BYTE *pbEncryptedBlob, IN DWORD cbEncryptedBlob, OUT OPTIONAL BYTE *pbDecrypted, IN OUT OPTIONAL DWORD *pcbDecrypted, OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert) WCE_LINK(CryptDecryptMessage);
WCE_IMPORT BOOL WINAPI CryptSignAndEncryptMessage(IN PCRYPT_SIGN_MESSAGE_PARA pSignPara, IN PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, IN DWORD cRecipientCert, IN PCCERT_CONTEXT rgpRecipientCert[], IN const BYTE *pbToBeSignedAndEncrypted, IN DWORD cbToBeSignedAndEncrypted, OUT BYTE *pbSignedAndEncryptedBlob, IN OUT DWORD *pcbSignedAndEncryptedBlob) WCE_LINK(CryptSignAndEncryptMessage);
WCE_IMPORT BOOL WINAPI CryptDecryptAndVerifyMessageSignature(IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara, IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, IN DWORD dwSignerIndex, IN const BYTE *pbEncryptedBlob, IN DWORD cbEncryptedBlob, OUT OPTIONAL BYTE *pbDecrypted, IN OUT OPTIONAL DWORD *pcbDecrypted, OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert, OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert) WCE_LINK(CryptDecryptAndVerifyMessageSignature);
WCE_IMPORT BOOL WINAPI CryptDecodeMessage(IN DWORD dwMsgTypeFlags, IN PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara, IN PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, IN DWORD dwSignerIndex, IN const BYTE *pbEncodedBlob, IN DWORD cbEncodedBlob, IN DWORD dwPrevInnerContentType, OUT OPTIONAL DWORD *pdwMsgType, OUT OPTIONAL DWORD *pdwInnerContentType, OUT OPTIONAL BYTE *pbDecoded, IN OUT OPTIONAL DWORD *pcbDecoded, OUT OPTIONAL PCCERT_CONTEXT *ppXchgCert, OUT OPTIONAL PCCERT_CONTEXT *ppSignerCert) WCE_LINK(CryptDecodeMessage);
WCE_IMPORT BOOL WINAPI CryptHashMessage(IN PCRYPT_HASH_MESSAGE_PARA pHashPara, IN BOOL fDetachedHash, IN DWORD cToBeHashed, IN const BYTE *rgpbToBeHashed[], IN DWORD rgcbToBeHashed[], OUT OPTIONAL BYTE *pbHashedBlob, IN OUT OPTIONAL DWORD *pcbHashedBlob, OUT OPTIONAL BYTE *pbComputedHash, IN OUT OPTIONAL DWORD *pcbComputedHash) WCE_LINK(CryptHashMessage);
WCE_IMPORT BOOL WINAPI CryptVerifyMessageHash(IN PCRYPT_HASH_MESSAGE_PARA pHashPara, IN BYTE *pbHashedBlob, IN DWORD cbHashedBlob, OUT OPTIONAL BYTE *pbToBeHashed, IN OUT OPTIONAL DWORD *pcbToBeHashed, OUT OPTIONAL BYTE *pbComputedHash, IN OUT OPTIONAL DWORD *pcbComputedHash) WCE_LINK(CryptVerifyMessageHash);
WCE_IMPORT BOOL WINAPI CryptVerifyDetachedMessageHash(IN PCRYPT_HASH_MESSAGE_PARA pHashPara, IN BYTE *pbDetachedHashBlob, IN DWORD cbDetachedHashBlob, IN DWORD cToBeHashed, IN const BYTE *rgpbToBeHashed[], IN DWORD rgcbToBeHashed[], OUT OPTIONAL BYTE *pbComputedHash, IN OUT OPTIONAL DWORD *pcbComputedHash) WCE_LINK(CryptVerifyDetachedMessageHash);
WCE_IMPORT BOOL WINAPI CryptSignMessageWithKey(IN PCRYPT_KEY_SIGN_MESSAGE_PARA pSignPara, IN const BYTE *pbToBeSigned, IN DWORD cbToBeSigned, OUT BYTE *pbSignedBlob, IN OUT DWORD *pcbSignedBlob) WCE_LINK(CryptSignMessageWithKey);
WCE_IMPORT BOOL WINAPI CryptVerifyMessageSignatureWithKey(IN PCRYPT_KEY_VERIFY_MESSAGE_PARA pVerifyPara, IN OPTIONAL PCERT_PUBLIC_KEY_INFO pPublicKeyInfo, IN const BYTE *pbSignedBlob, IN DWORD cbSignedBlob, OUT OPTIONAL BYTE *pbDecoded, IN OUT OPTIONAL DWORD *pcbDecoded) WCE_LINK(CryptVerifyMessageSignatureWithKey);
WCE_IMPORT BOOL WINAPI CertAddEncodedCertificateToSystemStoreA(LPCSTR szCertStoreName, const BYTE * pbCertEncoded, DWORD cbCertEncoded) WCE_LINK(CertAddEncodedCertificateToSystemStoreA);
WCE_IMPORT BOOL WINAPI CertAddEncodedCertificateToSystemStoreW(LPCWSTR szCertStoreName, const BYTE * pbCertEncoded, DWORD cbCertEncoded) WCE_LINK(CertAddEncodedCertificateToSystemStoreW);
WCE_IMPORT HRESULT WINAPI FindCertsByIssuer(OUT PCERT_CHAIN pCertChains, IN OUT DWORD *pcbCertChains, OUT DWORD *pcCertChains, IN BYTE* pbEncodedIssuerName, IN DWORD cbEncodedIssuerName, IN LPCWSTR pwszPurpose, IN DWORD dwKeySpec) WCE_LINK(FindCertsByIssuer);
WCE_IMPORT LPVOID WINAPI CryptMemAlloc(IN ULONG cbSize) WCE_LINK(CryptMemAlloc);
WCE_IMPORT LPVOID WINAPI CryptMemRealloc(IN LPVOID pv, IN ULONG cbSize) WCE_LINK(CryptMemRealloc);
WCE_IMPORT VOID WINAPI CryptMemFree(IN LPVOID pv) WCE_LINK(CryptMemFree);
WCE_IMPORT BOOL WINAPI CryptCreateAsyncHandle(IN DWORD dwFlags, OUT PHCRYPTASYNC phAsync) WCE_LINK(CryptCreateAsyncHandle);
WCE_IMPORT BOOL WINAPI CryptInstallCancelRetrieval(IN PFN_CRYPT_CANCEL_RETRIEVAL pfnCancel, IN const void *pvArg, IN DWORD dwFlags, IN void *pvReserved) WCE_LINK(CryptInstallCancelRetrieval);
WCE_IMPORT BOOL WINAPI CryptUninstallCancelRetrieval(IN DWORD dwFlags, IN void *pvReserved) WCE_LINK(CryptUninstallCancelRetrieval);
WCE_IMPORT BOOL WINAPI CryptGetObjectUrl(IN LPCSTR pszUrlOid, IN LPVOID pvPara, IN DWORD dwFlags, OUT OPTIONAL PCRYPT_URL_ARRAY pUrlArray, IN OUT DWORD* pcbUrlArray, OUT OPTIONAL PCRYPT_URL_INFO pUrlInfo, IN OUT OPTIONAL DWORD* pcbUrlInfo, IN OPTIONAL LPVOID pvReserved) WCE_LINK(CryptGetObjectUrl);
WCE_IMPORT BOOL WINAPI CryptGetTimeValidObject(IN LPCSTR pszTimeValidOid, IN LPVOID pvPara, IN PCCERT_CONTEXT pIssuer, IN OPTIONAL LPFILETIME pftValidFor, IN DWORD dwFlags, IN DWORD dwTimeout, OUT OPTIONAL LPVOID* ppvObject, IN OPTIONAL PCRYPT_CREDENTIALS pCredentials, IN OPTIONAL LPVOID pvReserved) WCE_LINK(CryptGetTimeValidObject);
WCE_IMPORT BOOL WINAPI CryptFlushTimeValidObject(IN LPCSTR pszFlushTimeValidOid, IN LPVOID pvPara, IN PCCERT_CONTEXT pIssuer, IN DWORD dwFlags, IN LPVOID pvReserved) WCE_LINK(CryptFlushTimeValidObject);
WCE_IMPORT BOOL WINAPI CryptProtectMemory(IN OUT LPVOID pDataIn, IN DWORD cbDataIn, IN DWORD dwFlags) WCE_LINK(CryptProtectMemory);
WCE_IMPORT BOOL WINAPI CryptUnprotectMemory(IN OUT LPVOID pDataIn, IN DWORD cbDataIn, IN DWORD dwFlags) WCE_LINK(CryptUnprotectMemory);
WCE_IMPORT BOOL WINAPI CryptCreateKeyIdentifierFromCSP(IN DWORD dwCertEncodingType, IN OPTIONAL LPCSTR pszPubKeyOID, IN const PUBLICKEYSTRUC *pPubKeyStruc, IN DWORD cbPubKeyStruc, IN DWORD dwFlags, IN OPTIONAL void *pvReserved, OUT BYTE *pbHash, IN OUT DWORD *pcbHash) WCE_LINK(CryptCreateKeyIdentifierFromCSP);
WCE_IMPORT VOID WINAPI CertFreeCertificateChain(IN PCCERT_CHAIN_CONTEXT pChainContext) WCE_LINK(CertFreeCertificateChain);
WCE_IMPORT PCCERT_CHAIN_CONTEXT WINAPI CertDuplicateCertificateChain(IN PCCERT_CHAIN_CONTEXT pChainContext) WCE_LINK(CertDuplicateCertificateChain);
WCE_IMPORT BOOL WINAPI CertVerifyCertificateChainPolicy(IN LPCSTR pszPolicyOID, IN PCCERT_CHAIN_CONTEXT pChainContext, IN PCERT_CHAIN_POLICY_PARA pPolicyPara, IN OUT PCERT_CHAIN_POLICY_STATUS pPolicyStatus) WCE_LINK(CertVerifyCertificateChainPolicy);
WCE_IMPORT BOOL WINAPI CryptStringToBinaryA(IN LPCSTR pszString, IN DWORD cchString, IN DWORD dwFlags, IN BYTE *pbBinary, IN OUT DWORD *pcbBinary, OUT DWORD *pdwSkip, OUT DWORD *pdwFlags) WCE_LINK(CryptStringToBinaryA);
WCE_IMPORT BOOL WINAPI CryptStringToBinaryW(IN LPCWSTR pszString, IN DWORD cchString, IN DWORD dwFlags, IN BYTE *pbBinary, IN OUT DWORD *pcbBinary, OUT DWORD *pdwSkip, OUT DWORD *pdwFlags) WCE_LINK(CryptStringToBinaryW);
WCE_IMPORT BOOL WINAPI CryptBinaryToStringA(IN CONST BYTE *pbBinary, IN DWORD cbBinary, IN DWORD dwFlags, IN LPSTR pszString, IN OUT DWORD *pcchString) WCE_LINK(CryptBinaryToStringA);
WCE_IMPORT BOOL WINAPI CryptBinaryToStringW(IN CONST BYTE *pbBinary, IN DWORD cbBinary, IN DWORD dwFlags, IN LPWSTR pszString, IN OUT DWORD *pcchString) WCE_LINK(CryptBinaryToStringW);

#define CryptSetProvider CryptSetProviderW
#define CryptSetProviderEx CryptSetProviderExW
#define CryptGetDefaultProvider CryptGetDefaultProviderW
#define CryptEnumProviderTypes CryptEnumProviderTypesW
#define CryptEnumProviders CryptEnumProvidersW
#define CertRDNValueToStr CertRDNValueToStrW
#define CertNameToStr CertNameToStrW
#define CertStrToName CertStrToNameW
#define CertGetNameString CertGetNameStringW
#define CertAddEncodedCertificateToSystemStore CertAddEncodedCertificateToSystemStoreW
#define CryptStringToBinary CryptStringToBinaryW
#define CryptBinaryToString CryptBinaryToStringW
#ifdef __cplusplus
}
#endif
#endif

