/*
 * wincrypt.h -- CryptoAPI for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * The prototypes cover the application-facing surface of crypt32.dll: the
 * certificate store functions, the ASN.1 encode and decode entry points, the
 * chain engine, and the OID information table.
 *
 * HCRYPTPROV, HCRYPTKEY, HCRYPTHASH and HCRYPTMSG are handles whose underlying
 * objects live in the CSP, not in this header; they are declared opaque.
 */
#ifndef AKARI_WCE_WINCRYPT_H
#define AKARI_WCE_WINCRYPT_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <wtypes.h>

#ifndef _WINCRYPT_
#define _WINCRYPT_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINCRYPT32API
#define WINCRYPT32API AKARI_DLLIMPORT
#endif

/* ---------------------------------------------------------- handles */

typedef ULONG_PTR HCRYPTPROV;
typedef ULONG_PTR HCRYPTKEY;
typedef ULONG_PTR HCRYPTHASH;
typedef ULONG_PTR HCRYPTDEFAULTCONTEXT;
typedef void *HCERTSTORE;
typedef void *HCERTCHAINENGINE;
typedef void *HCRYPTMSG;
typedef void *HCRYPTOIDFUNCSET;
typedef void *HCRYPTOIDFUNCADDR;

typedef unsigned int ALG_ID;
typedef ALG_ID *PALG_ID;

/* ------------------------------------------------------- basic blobs
 *
 * CE declares all of these as aliases of one two-field structure.  Keeping
 * them as aliases rather than distinct structs matches the ABI and lets a
 * CRYPT_DATA_BLOB be passed where a CERT_NAME_BLOB is expected, as the API
 * requires.
 */
typedef struct akari_CRYPTOAPI_BLOB {
    DWORD cbData;
    BYTE *pbData;
} CRYPT_INTEGER_BLOB, *PCRYPT_INTEGER_BLOB,
  CRYPT_UINT_BLOB,    *PCRYPT_UINT_BLOB,
  CRYPT_OBJID_BLOB,   *PCRYPT_OBJID_BLOB,
  CERT_NAME_BLOB,     *PCERT_NAME_BLOB,
  CERT_RDN_VALUE_BLOB,*PCERT_RDN_VALUE_BLOB,
  CRYPT_DATA_BLOB,    *PCRYPT_DATA_BLOB,
  CRYPT_HASH_BLOB,    *PCRYPT_HASH_BLOB,
  CRYPT_DIGEST_BLOB,  *PCRYPT_DIGEST_BLOB,
  CRYPT_DER_BLOB,     *PCRYPT_DER_BLOB,
  CRYPT_ATTR_BLOB,    *PCRYPT_ATTR_BLOB;

typedef struct akari_CRYPT_BIT_BLOB {
    DWORD cbData;
    BYTE *pbData;
    DWORD cUnusedBits;
} CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB;

typedef struct akari_CRYPT_ALGORITHM_IDENTIFIER {
    LPSTR            pszObjId;
    CRYPT_OBJID_BLOB Parameters;
} CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER;

typedef struct akari_CERT_PUBLIC_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER Algorithm;
    CRYPT_BIT_BLOB             PublicKey;
} CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO;

typedef struct akari_CRYPT_ATTRIBUTE {
    LPSTR           pszObjId;
    DWORD           cValue;
    PCRYPT_ATTR_BLOB rgValue;
} CRYPT_ATTRIBUTE, *PCRYPT_ATTRIBUTE;

typedef struct akari_CERT_RDN_ATTR {
    LPSTR               pszObjId;
    DWORD               dwValueType;
    CERT_RDN_VALUE_BLOB Value;
} CERT_RDN_ATTR, *PCERT_RDN_ATTR;

typedef struct akari_CERT_RDN {
    DWORD          cRDNAttr;
    PCERT_RDN_ATTR rgRDNAttr;
} CERT_RDN, *PCERT_RDN;

typedef struct akari_CERT_NAME_INFO {
    DWORD      cRDN;
    PCERT_RDN  rgRDN;
} CERT_NAME_INFO, *PCERT_NAME_INFO;

typedef struct akari_CERT_EXTENSION {
    LPSTR            pszObjId;
    BOOL             fCritical;
    CRYPT_OBJID_BLOB Value;
} CERT_EXTENSION, *PCERT_EXTENSION;

typedef struct akari_CERT_INFO {
    DWORD                      dwVersion;
    CRYPT_INTEGER_BLOB         SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER SignatureAlgorithm;
    CERT_NAME_BLOB             Issuer;
    FILETIME                   NotBefore;
    FILETIME                   NotAfter;
    CERT_NAME_BLOB             Subject;
    CERT_PUBLIC_KEY_INFO       SubjectPublicKeyInfo;
    CRYPT_BIT_BLOB             IssuerUniqueId;
    CRYPT_BIT_BLOB             SubjectUniqueId;
    DWORD                      cExtension;
    PCERT_EXTENSION            rgExtension;
} CERT_INFO, *PCERT_INFO;

typedef struct akari_CERT_CONTEXT {
    DWORD        dwCertEncodingType;
    BYTE        *pbCertEncoded;
    DWORD        cbCertEncoded;
    PCERT_INFO   pCertInfo;
    HCERTSTORE   hCertStore;
} CERT_CONTEXT, *PCERT_CONTEXT;
typedef const CERT_CONTEXT *PCCERT_CONTEXT;

typedef struct akari_CTL_USAGE {
    DWORD  cUsageIdentifier;
    LPSTR *rgpszUsageIdentifier;
} CTL_USAGE, *PCTL_USAGE,
  CERT_ENHKEY_USAGE, *PCERT_ENHKEY_USAGE;

typedef struct akari_CERT_USAGE_MATCH {
    DWORD              dwType;
    CERT_ENHKEY_USAGE  Usage;
} CERT_USAGE_MATCH, *PCERT_USAGE_MATCH;

typedef struct akari_CERT_CHAIN_PARA {
    DWORD            cbSize;
    CERT_USAGE_MATCH RequestedUsage;
} CERT_CHAIN_PARA, *PCERT_CHAIN_PARA;

typedef struct akari_CERT_TRUST_STATUS {
    DWORD dwErrorStatus;
    DWORD dwInfoStatus;
} CERT_TRUST_STATUS, *PCERT_TRUST_STATUS;

typedef struct akari_CRYPT_ENCODE_PARA {
    DWORD cbSize;
    void *(__cdecl *pfnAlloc)(DWORD);
    void  (__cdecl *pfnFree)(void *);
} CRYPT_ENCODE_PARA, *PCRYPT_ENCODE_PARA;

typedef struct akari_CRYPT_DECODE_PARA {
    DWORD cbSize;
    void *(__cdecl *pfnAlloc)(DWORD);
    void  (__cdecl *pfnFree)(void *);
} CRYPT_DECODE_PARA, *PCRYPT_DECODE_PARA;

/* One entry registering an address for an OID function. */
typedef struct akari_CRYPT_OID_FUNC_ENTRY {
    LPCSTR pszOID;
    void  *pvFuncAddr;
} CRYPT_OID_FUNC_ENTRY, *PCRYPT_OID_FUNC_ENTRY;

#define CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG  1
typedef void *PCMSG_STREAM_INFO;
typedef void *PCERT_CHAIN_ENGINE_CONFIG;
typedef void *PCCERT_CHAIN_CONTEXT;

/* The public key blob header shared with the CSP. */
typedef struct akari_PUBLICKEYSTRUC {
    BYTE   bType;
    BYTE   bVersion;
    WORD   reserved;
    ALG_ID aiKeyAlg;
} BLOBHEADER, PUBLICKEYSTRUC;

/* One entry of the OID information table.  The union is anonymous, as CE
   declares it, so the value is reachable as both dwValue and Algid. */
typedef struct akari_CRYPT_OID_INFO {
    DWORD           cbSize;
    LPCSTR          pszOID;
    LPCWSTR         pwszName;
    DWORD           dwGroupId;
    union {
        DWORD  dwValue;
        ALG_ID Algid;
        DWORD  dwLength;
    };
    CRYPT_DATA_BLOB ExtraInfo;
} CRYPT_OID_INFO, *PCRYPT_OID_INFO;
typedef const CRYPT_OID_INFO CCRYPT_OID_INFO, *PCCRYPT_OID_INFO;

#define CRYPT_HASH_ALG_OID_GROUP_ID     1
#define CRYPT_ENCRYPT_ALG_OID_GROUP_ID  2
#define CRYPT_PUBKEY_ALG_OID_GROUP_ID   3
#define CRYPT_SIGN_ALG_OID_GROUP_ID     4
#define CRYPT_RDN_ATTR_OID_GROUP_ID     5
#define CRYPT_EXT_OR_ATTR_OID_GROUP_ID  6
#define CRYPT_ENHKEY_USAGE_OID_GROUP_ID 7
#define CRYPT_POLICY_OID_GROUP_ID       8
#define CRYPT_TEMPLATE_OID_GROUP_ID     9

/* ------------------------------------------------------- callbacks */

typedef void *(__cdecl *PFN_CRYPT_ALLOC)(DWORD cbSize);
typedef void  (__cdecl *PFN_CRYPT_FREE)(void *pv);

typedef BOOL (WINAPI *PFN_CERT_ENUM_PHYSICAL_STORE)(
    const void *pvStore, DWORD dwFlags, LPCWSTR pwszStoreName,
    void *pvSystemStore, DWORD dwFlags2, void *pvReserved, void *pvArg);
typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE)(DWORD dwFlags,
    void *pwszStoreName, void *pvStore, void *pvReserved, void *pvArg);
typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)(DWORD dwFlags,
    void *pwszStoreName, void *pvReserved, void *pvArg);
typedef BOOL (WINAPI *PFN_CRYPT_ENUM_KEYID_PROP)(
    const CRYPT_HASH_BLOB *pKeyId, void *pvReserved, DWORD dwFlags,
    void *pvArg, DWORD cProp, const DWORD *rgdwPropId,
    void *const *rgpvProp);
typedef BOOL (WINAPI *PFN_CRYPT_ENUM_OID_INFO)(
    void *pInfo, void *pvReserved, void *pvArg);

/* ----------------------------------------------------- store flags */

#define CERT_STORE_PROV_MSG             ((LPCSTR)1)
#define CERT_STORE_PROV_MEMORY          ((LPCSTR)2)
#define CERT_STORE_PROV_FILE            ((LPCSTR)3)
#define CERT_STORE_PROV_SYSTEM          ((LPCSTR)10)
#define CERT_STORE_PROV_COLLECTION      ((LPCSTR)11)
#define CERT_STORE_PROV_FILENAME        CERT_STORE_PROV_FILE
#define CERT_STORE_PROV_SYSTEM_W        ((LPCSTR)10)

#define CERT_STORE_NO_CRYPT_RELEASE_FLAG    0x00000001
#define CERT_STORE_SET_LOCALIZED_NAME_FLAG  0x00000002
#define CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG 0x00000004
#define CERT_STORE_DELETE_FLAG              0x00000010
#define CERT_STORE_READONLY_FLAG            0x00008000
#define CERT_STORE_SHARE_STORE_FLAG         0x00000040
#define CERT_STORE_SHARE_CONTEXT_FLAG       0x00000080
#define CERT_STORE_MANIFOLD_FLAG            0x00000100
#define CERT_STORE_ENUM_ARCHIVED_FLAG       0x00000200
#define CERT_STORE_UPDATE_KEYID_FLAG        0x00000400
#define CERT_STORE_MAXIMUM_ALLOWED_FLAG     0x00010000
#define CERT_STORE_CREATE_NEW_FLAG          0x00002000
#define CERT_STORE_OPEN_EXISTING_FLAG       0x00004000
#define CERT_STORE_BACKUP_RESTORE_FLAG      0x00000800

#define CERT_SYSTEM_STORE_CURRENT_USER          0x00010000
#define CERT_SYSTEM_STORE_LOCAL_MACHINE         0x00020000
#define CERT_SYSTEM_STORE_CURRENT_SERVICE       0x00040000
#define CERT_SYSTEM_STORE_SERVICES              0x00050000
#define CERT_SYSTEM_STORE_USERS                 0x00060000

#define CERT_STORE_ADD_NEW                  1
#define CERT_STORE_ADD_USE_EXISTING         2
#define CERT_STORE_ADD_REPLACE_EXISTING     3
#define CERT_STORE_ADD_ALWAYS               4
#define CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES 5
#define CERT_STORE_ADD_NEWER                6
#define CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES 7

#define CERT_FIND_ANY                   0
#define CERT_FIND_CERT_ID               1048576
#define CERT_FIND_CTL_USAGE             655360
#define CERT_FIND_ENHKEY_USAGE          655360
#define CERT_FIND_EXISTING              851968
#define CERT_FIND_HASH                  65536
#define CERT_FIND_ISSUER_ATTR           131077
#define CERT_FIND_ISSUER_NAME           131076
#define CERT_FIND_ISSUER_OF             786432
#define CERT_FIND_PROPERTY              327680
#define CERT_FIND_PUBLIC_KEY            393216
#define CERT_FIND_SHA1_HASH             65536
#define CERT_FIND_SIGNATURE_HASH        983040
#define CERT_FIND_SUBJECT_ATTR          196613
#define CERT_FIND_SUBJECT_CERT          917504
#define CERT_FIND_SUBJECT_NAME          196612
#define CERT_FIND_SUBJECT_STR_A         458756
#define CERT_FIND_SUBJECT_STR_W         524292
#define CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG 0x10
#define CERT_FIND_NO_ENHKEY_USAGE_FLAG  0x08
#define CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG 0x40

#define CERT_CLOSE_STORE_CHECK_FLAG     0x00000001
#define CERT_CLOSE_STORE_FORCE_FLAG     0x00000002

#define CERT_NAME_EMAIL_TYPE            1
#define CERT_NAME_RDN_TYPE              2
#define CERT_NAME_ATTR_TYPE             3
#define CERT_NAME_SIMPLE_DISPLAY_TYPE   4
#define CERT_NAME_FRIENDLY_DISPLAY_TYPE 5
#define CERT_NAME_ISSUER_FLAG           0x1

#define CERT_STORE_CTRL_RESYNC          1
#define CERT_STORE_CTRL_AUTO_RESYNC     4
#define CERT_STORE_CTRL_COMMIT_FORCE    8
#define CERT_STORE_CTRL_COMMIT_CLEAR    16

#define CERT_X500_NAME_STR          3
#define CERT_SIMPLE_NAME_STR        1
#define CERT_OID_NAME_STR           2

#define CRYPT_ENCODE_ALLOC_FLAG     0x8000
#define CRYPT_UNICODE_NAME_ENCODE_ENABLE_FLAG 0x00000001
#define CRYPT_UNICODE_NAME_DECODE_DISABLE_FLAG 0x00000002

#define PKCS_7_ASN_ENCODING         0x00010000
#define X509_ASN_ENCODING           0x00000001
#define X509_NDR_ENCODING           0x00000020

#define CERT_CHAIN_CACHE_END_CERT   0x00000001
#define CERT_CHAIN_THREAD_CHAINING  0x00000002
#define CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL 0x00000004

#define szOID_COMMON_NAME               "2.5.4.3"
#define szOID_COUNTRY_NAME              "2.5.4.6"
#define szOID_LOCALITY_NAME             "2.5.4.7"
#define szOID_ORGANIZATION_NAME         "2.5.4.10"
#define szOID_ORGANIZATIONAL_UNIT_NAME  "2.5.4.11"
#define szOID_STATE_OR_PROVINCE_NAME    "2.5.4.8"
#define szOID_TITLE                     "2.5.4.12"
#define szOID_RSA_RSA                   "1.2.840.113549.1.1.1"
#define szOID_RSA_MD5RSA                "1.2.840.113549.1.1.4"
#define szOID_RSA_SHA1RSA               "1.2.840.113549.1.1.5"
#define szOID_ENHANCED_KEY_USAGE        "2.5.29.37"
#define szOID_KEY_USAGE                 "2.5.29.15"
#define szOID_BASIC_CONSTRAINTS         "2.5.29.19"

#define CERT_TRUST_NO_ERROR                   0x00000000
#define CERT_TRUST_IS_NOT_TIME_VALID          0x00000001
#define CERT_TRUST_IS_NOT_TIME_NESTED         0x00000002
#define CERT_TRUST_IS_REVOKED                 0x00000004
#define CERT_TRUST_IS_NOT_SIGNATURE_VALID     0x00000008
#define CERT_TRUST_IS_NOT_VALID_FOR_USAGE     0x00000010
#define CERT_TRUST_IS_UNTRUSTED_ROOT          0x00000020
#define CERT_TRUST_REVOCATION_STATUS_UNKNOWN  0x00000040
#define CERT_TRUST_IS_CYCLIC                  0x00000080

#define CERT_TRUST_IS_EXACT_MATCH issuer  0x00000000
#define CERT_TRUST_HAS_EXACT_MATCH_ISSUER 0x00000001
#define CERT_TRUST_HAS_KEY_MATCH_ISSUER   0x00000002
#define CERT_TRUST_HAS_NAME_MATCH_ISSUER  0x00000004
#define CERT_TRUST_IS_SELF_SIGNED         0x00000008
#define CERT_TRUST_HAS_PREFERRED_ISSUER   0x00000100
#define CERT_TRUST_HAS_ISSUANCE_CHAIN_POLICY 0x00000200

#define CERT_KEY_PROV_INFO_PROP_ID          2
#define CERT_SHA1_HASH_PROP_ID              3
#define CERT_MD5_HASH_PROP_ID               4
#define CERT_KEY_CONTEXT_PROP_ID            5
#define CERT_KEY_SPEC_PROP_ID               6
#define CERT_ISSUER_SERIAL_NUMBER_MD5_HASH_PROP_ID 8
#define CERT_SUBJECT_NAME_MD5_HASH_PROP_ID  9
#define CERT_EXTENDED_ERROR_INFO_PROP_ID    10
#define CERT_FRIENDLY_NAME_PROP_ID          11
#define CERT_PVK_FILE_PROP_ID               12
#define CERT_ARCHIVED_PROP_ID               14

#define CRYPT_E_NOT_FOUND   ((HRESULT)0x80092004L)
#define CRYPT_E_EXISTS      ((HRESULT)0x80092005L)
#define CRYPT_E_NO_PROVIDER ((HRESULT)0x80092006L)
#define CRYPT_E_FILE_ERROR  ((HRESULT)0x80092003L)
#define CRYPT_E_OSS_ERROR   ((HRESULT)0x80093000L)
#define CRYPT_E_INVALID_NUMERIC_STRING ((HRESULT)0x80092020L)

/* ------------------------------------------------------- prototypes */

WINCRYPT32API BOOL WINAPI CertAddCertificateContextToStore(IN HCERTSTORE hCertStore, IN PCCERT_CONTEXT pCertContext, IN DWORD dwAddDisposition, OUT OPTIONAL PCCERT_CONTEXT *ppStoreContext);
WINCRYPT32API BOOL WINAPI CertAddCertificateLinkToStore(IN HCERTSTORE hCertStore, IN PCCERT_CONTEXT pCertContext, IN DWORD dwAddDisposition, OUT OPTIONAL PCCERT_CONTEXT *ppStoreContext);
WINCRYPT32API BOOL WINAPI CertAddEncodedCertificateToStore(IN HCERTSTORE hCertStore, IN DWORD dwCertEncodingType, IN const BYTE *pbCertEncoded, IN DWORD cbCertEncoded, IN DWORD dwAddDisposition, OUT OPTIONAL PCCERT_CONTEXT *ppCertContext);
WINCRYPT32API BOOL WINAPI CertAddEnhancedKeyUsageIdentifier(IN PCCERT_CONTEXT pCertContext, IN LPCSTR pszUsageIdentifier);
WINCRYPT32API BOOL WINAPI CertAddSerializedElementToStore(IN HCERTSTORE hCertStore, IN const BYTE *pbElement, IN DWORD cbElement, IN DWORD dwAddDisposition, IN DWORD dwFlags, IN DWORD dwContextTypeFlags, OUT OPTIONAL DWORD *pdwContextType, OUT OPTIONAL const void **ppvContext);
WINCRYPT32API LPCSTR WINAPI CertAlgIdToOID(IN DWORD dwAlgId);
WINCRYPT32API BOOL WINAPI CertCloseStore(IN HCERTSTORE hCertStore, DWORD dwFlags);
WINCRYPT32API BOOL WINAPI CertCompareCertificate(IN DWORD dwCertEncodingType, IN PCERT_INFO pCertId1, IN PCERT_INFO pCertId2);
WINCRYPT32API BOOL WINAPI CertCompareCertificateName(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pCertName1, IN PCERT_NAME_BLOB pCertName2);
WINCRYPT32API BOOL WINAPI CertCompareIntegerBlob(IN PCRYPT_INTEGER_BLOB pInt1, IN PCRYPT_INTEGER_BLOB pInt2);
WINCRYPT32API BOOL WINAPI CertComparePublicKeyInfo(IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pPublicKey1, IN PCERT_PUBLIC_KEY_INFO pPublicKey2);
WINCRYPT32API BOOL WINAPI CertControlStore(IN HCERTSTORE hCertStore, IN DWORD dwFlags, IN DWORD dwCtrlType, IN void const *pvCtrlPara);
WINCRYPT32API BOOL WINAPI CertCreateCertificateChainEngine(IN PCERT_CHAIN_ENGINE_CONFIG pConfig, OUT HCERTCHAINENGINE* phChainEngine);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertCreateCertificateContext(IN DWORD dwCertEncodingType, IN const BYTE *pbCertEncoded, IN DWORD cbCertEncoded);
WINCRYPT32API BOOL WINAPI CertDeleteCertificateFromStore(IN PCCERT_CONTEXT pCertContext);
WINCRYPT32API PCCERT_CHAIN_CONTEXT WINAPI CertDuplicateCertificateChain(IN PCCERT_CHAIN_CONTEXT pChainContext);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertDuplicateCertificateContext(IN PCCERT_CONTEXT pCertContext);
WINCRYPT32API HCERTSTORE WINAPI CertDuplicateStore(IN HCERTSTORE hCertStore);
WINCRYPT32API DWORD WINAPI CertEnumCertificateContextProperties(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertEnumCertificatesInStore(IN HCERTSTORE hCertStore, IN PCCERT_CONTEXT pPrevCertContext);
WINCRYPT32API BOOL WINAPI CertEnumPhysicalStore(IN const void *pvSystemStore, IN DWORD dwFlags, IN void *pvArg, IN PFN_CERT_ENUM_PHYSICAL_STORE pfnEnum);
WINCRYPT32API BOOL WINAPI CertEnumSystemStore(IN DWORD dwFlags, IN OPTIONAL void *pvSystemStoreLocationPara, IN void *pvArg, IN PFN_CERT_ENUM_SYSTEM_STORE pfnEnum);
WINCRYPT32API BOOL WINAPI CertEnumSystemStoreLocation(IN DWORD dwFlags, IN void *pvArg, IN PFN_CERT_ENUM_SYSTEM_STORE_LOCATION pfnEnum);
WINCRYPT32API PCRYPT_ATTRIBUTE WINAPI CertFindAttribute(IN LPCSTR pszObjId, IN DWORD cAttr, IN CRYPT_ATTRIBUTE rgAttr[]);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertFindCertificateInStore(IN HCERTSTORE hCertStore, IN DWORD dwCertEncodingType, IN DWORD dwFindFlags, IN DWORD dwFindType, IN const void *pvFindPara, IN PCCERT_CONTEXT pPrevCertContext);
WINCRYPT32API PCCERT_CHAIN_CONTEXT WINAPI CertFindChainInStore(IN HCERTSTORE hCertStore, IN DWORD dwCertEncodingType, IN DWORD dwFindFlags, IN DWORD dwFindType, IN const void *pvFindPara, IN PCCERT_CHAIN_CONTEXT pPrevChainContext);
WINCRYPT32API PCERT_EXTENSION WINAPI CertFindExtension(IN LPCSTR pszObjId, IN DWORD cExtensions, IN CERT_EXTENSION rgExtensions[]);
WINCRYPT32API PCERT_RDN_ATTR WINAPI CertFindRDNAttr(IN LPCSTR pszObjId, IN PCERT_NAME_INFO pName);
WINCRYPT32API VOID WINAPI CertFreeCertificateChain(IN PCCERT_CHAIN_CONTEXT pChainContext);
WINCRYPT32API VOID WINAPI CertFreeCertificateChainEngine(IN HCERTCHAINENGINE hChainEngine);
WINCRYPT32API BOOL WINAPI CertFreeCertificateContext(IN PCCERT_CONTEXT pCertContext);
WINCRYPT32API BOOL WINAPI CertGetCertificateChain(IN OPTIONAL HCERTCHAINENGINE hChainEngine, IN PCCERT_CONTEXT pCertContext, IN OPTIONAL LPFILETIME pTime, IN OPTIONAL HCERTSTORE hAdditionalStore, IN PCERT_CHAIN_PARA pChainPara, IN DWORD dwFlags, IN LPVOID pvReserved, OUT PCCERT_CHAIN_CONTEXT* ppChainContext);
WINCRYPT32API BOOL WINAPI CertGetCertificateContextProperty(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId, OUT void *pvData, IN OUT DWORD *pcbData);
WINCRYPT32API BOOL WINAPI CertGetEnhancedKeyUsage(IN PCCERT_CONTEXT pCertContext, IN DWORD dwFlags, OUT PCERT_ENHKEY_USAGE pUsage, IN OUT DWORD *pcbUsage);
WINCRYPT32API BOOL WINAPI CertGetIntendedKeyUsage(IN DWORD dwCertEncodingType, IN PCERT_INFO pCertInfo, OUT BYTE *pbKeyUsage, IN DWORD cbKeyUsage);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertGetIssuerCertificateFromStore(IN HCERTSTORE hCertStore, IN PCCERT_CONTEXT pSubjectContext, IN OPTIONAL PCCERT_CONTEXT pPrevIssuerContext, IN OUT DWORD *pdwFlags);
WINCRYPT32API DWORD WINAPI CertGetNameStringA(IN PCCERT_CONTEXT pCertContext, IN DWORD dwType, IN DWORD dwFlags, IN void *pvTypePara, OUT OPTIONAL LPSTR pszNameString, IN DWORD cchNameString);
WINCRYPT32API DWORD WINAPI CertGetNameStringW(IN PCCERT_CONTEXT pCertContext, IN DWORD dwType, IN DWORD dwFlags, IN void *pvTypePara, OUT OPTIONAL LPWSTR pszNameString, IN DWORD cchNameString);
WINCRYPT32API DWORD WINAPI CertGetPublicKeyLength(IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pPublicKey);
WINCRYPT32API BOOL WINAPI CertGetStoreProperty(IN HCERTSTORE hCertStore, IN DWORD dwPropId, OUT void *pvData, IN OUT DWORD *pcbData);
WINCRYPT32API PCCERT_CONTEXT WINAPI CertGetSubjectCertificateFromStore(IN HCERTSTORE hCertStore, IN DWORD dwCertEncodingType, IN PCERT_INFO pCertId);
WINCRYPT32API BOOL WINAPI CertGetValidUsages(IN DWORD cCerts, IN PCCERT_CONTEXT *rghCerts, OUT int *cNumOIDs, OUT LPSTR *rghOIDs, IN OUT DWORD *pcbOIDs);
WINCRYPT32API BOOL WINAPI CertIsRDNAttrsInCertificateName(IN DWORD dwCertEncodingType, IN DWORD dwFlags, IN PCERT_NAME_BLOB pCertName, IN PCERT_RDN pRDN);
WINCRYPT32API DWORD WINAPI CertNameToStrA(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pName, IN DWORD dwStrType, OUT OPTIONAL LPSTR psz, IN DWORD csz);
WINCRYPT32API DWORD WINAPI CertNameToStrW(IN DWORD dwCertEncodingType, IN PCERT_NAME_BLOB pName, IN DWORD dwStrType, OUT OPTIONAL LPWSTR psz, IN DWORD csz);
WINCRYPT32API DWORD WINAPI CertOIDToAlgId(IN LPCSTR pszObjId);
WINCRYPT32API HCERTSTORE WINAPI CertOpenStore(IN LPCSTR lpszStoreProvider, IN DWORD dwEncodingType, IN HCRYPTPROV hCryptProv, IN DWORD dwFlags, IN const void *pvPara);
WINCRYPT32API DWORD WINAPI CertRDNValueToStrA(IN DWORD dwValueType, IN PCERT_RDN_VALUE_BLOB pValue, OUT OPTIONAL LPSTR psz, IN DWORD csz);
WINCRYPT32API DWORD WINAPI CertRDNValueToStrW(IN DWORD dwValueType, IN PCERT_RDN_VALUE_BLOB pValue, OUT OPTIONAL LPWSTR psz, IN DWORD csz);
WINCRYPT32API BOOL WINAPI CertRemoveEnhancedKeyUsageIdentifier(IN PCCERT_CONTEXT pCertContext, IN LPCSTR pszUsageIdentifier);
WINCRYPT32API BOOL WINAPI CertSaveStore(IN HCERTSTORE hCertStore, IN DWORD dwEncodingType, IN DWORD dwSaveAs, IN DWORD dwSaveTo, IN OUT void *pvSaveToPara, IN DWORD dwFlags);
WINCRYPT32API BOOL WINAPI CertSerializeCertificateStoreElement(IN PCCERT_CONTEXT pCertContext, IN DWORD dwFlags, OUT BYTE *pbElement, IN OUT DWORD *pcbElement);
WINCRYPT32API BOOL WINAPI CertSetCertificateContextProperty(IN PCCERT_CONTEXT pCertContext, IN DWORD dwPropId, IN DWORD dwFlags, IN const void *pvData);
WINCRYPT32API BOOL WINAPI CertSetEnhancedKeyUsage(IN PCCERT_CONTEXT pCertContext, IN PCERT_ENHKEY_USAGE pUsage);
WINCRYPT32API BOOL WINAPI CertSetStoreProperty(IN HCERTSTORE hCertStore, IN DWORD dwPropId, IN DWORD dwFlags, IN const void *pvData);
WINCRYPT32API BOOL WINAPI CertStrToNameA(IN DWORD dwCertEncodingType, IN LPCSTR pszX500, IN DWORD dwStrType, IN OPTIONAL void *pvReserved, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded, OUT OPTIONAL LPCSTR *ppszError);
WINCRYPT32API BOOL WINAPI CertStrToNameW(IN DWORD dwCertEncodingType, IN LPCWSTR pszX500, IN DWORD dwStrType, IN OPTIONAL void *pvReserved, OUT BYTE *pbEncoded, IN OUT DWORD *pcbEncoded, OUT OPTIONAL LPCWSTR *ppszError);
WINCRYPT32API BOOL WINAPI CertVerifySubjectCertificateContext(IN PCCERT_CONTEXT pSubject, IN OPTIONAL PCCERT_CONTEXT pIssuer, IN OUT DWORD *pdwFlags);
WINCRYPT32API LONG WINAPI CertVerifyTimeValidity(IN LPFILETIME pTimeToVerify, IN PCERT_INFO pCertInfo);
WINCRYPT32API BOOL WINAPI CertVerifyValidityNesting(IN PCERT_INFO pSubjectInfo, IN PCERT_INFO pIssuerInfo);
WINCRYPT32API BOOL WINAPI CryptAcquireCertificatePrivateKey(IN PCCERT_CONTEXT pCert, IN DWORD dwFlags, IN void *pvReserved, OUT HCRYPTPROV *phCryptProv, OUT OPTIONAL DWORD *pdwKeySpec, OUT OPTIONAL BOOL *pfCallerFreeProv);
WINCRYPT32API BOOL WINAPI CryptCreateKeyIdentifierFromCSP(IN DWORD dwCertEncodingType, IN OPTIONAL LPCSTR pszPubKeyOID, IN const PUBLICKEYSTRUC *pPubKeyStruc, IN DWORD cbPubKeyStruc, IN DWORD dwFlags, IN OPTIONAL void *pvReserved, OUT BYTE *pbHash, IN OUT DWORD *pcbHash);
WINCRYPT32API BOOL WINAPI CryptDecodeObjectEx(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, IN DWORD dwFlags, IN OPTIONAL PCRYPT_DECODE_PARA pDecodePara, OUT OPTIONAL void *pvStructInfo, IN OUT DWORD *pcbStructInfo);
WINCRYPT32API BOOL WINAPI CryptEncodeObjectEx(IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const void *pvStructInfo, IN DWORD dwFlags, IN OPTIONAL PCRYPT_ENCODE_PARA pEncodePara, OUT void *pvEncoded, IN OUT DWORD *pcbEncoded);
WINCRYPT32API BOOL WINAPI CryptEnumKeyIdentifierProperties(IN OPTIONAL const CRYPT_HASH_BLOB *pKeyIdentifier, IN DWORD dwPropId, IN DWORD dwFlags, IN OPTIONAL LPCWSTR pwszComputerName, IN OPTIONAL void *pvReserved, IN OPTIONAL void *pvArg, IN PFN_CRYPT_ENUM_KEYID_PROP pfnEnum);
WINCRYPT32API BOOL WINAPI CryptEnumOIDInfo(IN DWORD dwGroupId, IN DWORD dwFlags, IN void *pvArg, IN PFN_CRYPT_ENUM_OID_INFO pfnEnumOIDInfo);
WINCRYPT32API BOOL WINAPI CryptExportPublicKeyInfo(IN HCRYPTPROV hCryptProv, IN DWORD dwKeySpec, IN DWORD dwCertEncodingType, OUT PCERT_PUBLIC_KEY_INFO pInfo, IN OUT DWORD *pcbInfo);
WINCRYPT32API BOOL WINAPI CryptExportPublicKeyInfoEx(IN HCRYPTPROV hCryptProv, IN DWORD dwKeySpec, IN DWORD dwCertEncodingType, IN LPSTR pszPublicKeyObjId, IN DWORD dwFlags, IN OPTIONAL void *pvAuxInfo, OUT PCERT_PUBLIC_KEY_INFO pInfo, IN OUT DWORD *pcbInfo);
WINCRYPT32API BOOL WINAPI CryptFindCertificateKeyProvInfo(IN PCCERT_CONTEXT pCert, IN DWORD dwFlags, IN void *pvReserved);
WINCRYPT32API LPCWSTR WINAPI CryptFindLocalizedName(IN LPCWSTR pwszCryptName);
WINCRYPT32API PCCRYPT_OID_INFO WINAPI CryptFindOIDInfo(IN DWORD dwKeyType, IN void *pvKey, IN DWORD dwGroupId);
WINCRYPT32API BOOL WINAPI CryptFreeOIDFunctionAddress(IN HCRYPTOIDFUNCADDR hFuncAddr, IN DWORD dwFlags);
WINCRYPT32API BOOL WINAPI CryptGetKeyIdentifierProperty(IN const CRYPT_HASH_BLOB *pKeyIdentifier, IN DWORD dwPropId, IN DWORD dwFlags, IN OPTIONAL LPCWSTR pwszComputerName, IN OPTIONAL void *pvReserved, OUT void *pvData, IN OUT DWORD *pcbData);
WINCRYPT32API BOOL WINAPI CryptGetOIDFunctionAddress(IN HCRYPTOIDFUNCSET hFuncSet, IN DWORD dwEncodingType, IN LPCSTR pszOID, IN DWORD dwFlags, OUT void **ppvFuncAddr, OUT HCRYPTOIDFUNCADDR *phFuncAddr);
WINCRYPT32API BOOL WINAPI CryptHashCertificate(IN HCRYPTPROV hCryptProv, IN ALG_ID Algid, IN DWORD dwFlags, IN const BYTE *pbEncoded, IN DWORD cbEncoded, OUT BYTE *pbComputedHash, IN OUT DWORD *pcbComputedHash);
WINCRYPT32API BOOL WINAPI CryptHashPublicKeyInfo(IN HCRYPTPROV hCryptProv, IN ALG_ID Algid, IN DWORD dwFlags, IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pInfo, OUT BYTE *pbComputedHash, IN OUT DWORD *pcbComputedHash);
WINCRYPT32API BOOL WINAPI CryptHashToBeSigned(IN HCRYPTPROV hCryptProv, IN DWORD dwCertEncodingType, IN const BYTE *pbEncoded, IN DWORD cbEncoded, OUT BYTE *pbComputedHash, IN OUT DWORD *pcbComputedHash);
WINCRYPT32API BOOL WINAPI CryptImportPublicKeyInfo(IN HCRYPTPROV hCryptProv, IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pInfo, OUT HCRYPTKEY *phKey);
WINCRYPT32API BOOL WINAPI CryptImportPublicKeyInfoEx(IN HCRYPTPROV hCryptProv, IN DWORD dwCertEncodingType, IN PCERT_PUBLIC_KEY_INFO pInfo, IN ALG_ID aiKeyAlg, IN DWORD dwFlags, IN OPTIONAL void *pvAuxInfo, OUT HCRYPTKEY *phKey);
WINCRYPT32API HCRYPTOIDFUNCSET WINAPI CryptInitOIDFunctionSet(IN LPCSTR pszFuncName, IN DWORD dwFlags);
WINCRYPT32API BOOL WINAPI CryptInstallDefaultContext(IN HCRYPTPROV hCryptProv, IN DWORD dwDefaultType, IN const void *pvDefaultPara, IN DWORD dwFlags, IN void *pvReserved, OUT HCRYPTDEFAULTCONTEXT *phDefaultContext);
WINCRYPT32API BOOL WINAPI CryptInstallOIDFunctionAddress(IN HMODULE hModule, IN DWORD dwEncodingType, IN LPCSTR pszFuncName, IN DWORD cFuncEntry, IN const CRYPT_OID_FUNC_ENTRY rgFuncEntry[], IN DWORD dwFlags);
WINCRYPT32API LPVOID WINAPI CryptMemAlloc(IN ULONG cbSize);
WINCRYPT32API VOID WINAPI CryptMemFree(IN LPVOID pv);
WINCRYPT32API LPVOID WINAPI CryptMemRealloc(IN LPVOID pv, IN ULONG cbSize);
WINCRYPT32API DWORD WINAPI CryptMsgCalculateEncodedLength(IN DWORD dwMsgEncodingType, IN DWORD dwFlags, IN DWORD dwMsgType, IN void const *pvMsgEncodeInfo, IN OPTIONAL LPSTR pszInnerContentObjID, IN DWORD cbData);
WINCRYPT32API BOOL WINAPI CryptMsgClose(IN HCRYPTMSG hCryptMsg);
WINCRYPT32API BOOL WINAPI CryptMsgControl(IN HCRYPTMSG hCryptMsg, IN DWORD dwFlags, IN DWORD dwCtrlType, IN void const *pvCtrlPara);
WINCRYPT32API HCRYPTMSG WINAPI CryptMsgDuplicate(IN HCRYPTMSG hCryptMsg);
WINCRYPT32API BOOL WINAPI CryptMsgGetParam(IN HCRYPTMSG hCryptMsg, IN DWORD dwParamType, IN DWORD dwIndex, OUT void *pvData, IN OUT DWORD *pcbData);
WINCRYPT32API HCRYPTMSG WINAPI CryptMsgOpenToDecode(IN DWORD dwMsgEncodingType, IN DWORD dwFlags, IN DWORD dwMsgType, IN HCRYPTPROV hCryptProv, IN OPTIONAL PCERT_INFO pRecipientInfo, IN OPTIONAL PCMSG_STREAM_INFO pStreamInfo);
WINCRYPT32API HCRYPTMSG WINAPI CryptMsgOpenToEncode(IN DWORD dwMsgEncodingType, IN DWORD dwFlags, IN DWORD dwMsgType, IN void const *pvMsgEncodeInfo, IN OPTIONAL LPSTR pszInnerContentObjID, IN OPTIONAL PCMSG_STREAM_INFO pStreamInfo);
WINCRYPT32API BOOL WINAPI CryptMsgUpdate(IN HCRYPTMSG hCryptMsg, IN const BYTE *pbData, IN DWORD cbData, IN BOOL fFinal);
WINCRYPT32API BOOL WINAPI CryptSetKeyIdentifierProperty(IN const CRYPT_HASH_BLOB *pKeyIdentifier, IN DWORD dwPropId, IN DWORD dwFlags, IN OPTIONAL LPCWSTR pwszComputerName, IN OPTIONAL void *pvReserved, IN const void *pvData);
WINCRYPT32API BOOL WINAPI CryptSignAndEncodeCertificate(IN HCRYPTPROV hCryptProv, IN DWORD dwKeySpec, IN DWORD dwCertEncodingType, IN LPCSTR lpszStructType, IN const void *pvStructInfo, IN PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, IN OPTIONAL const void *pvHashAuxInfo, OUT PBYTE pbEncoded, IN OUT DWORD *pcbEncoded);
WINCRYPT32API BOOL WINAPI CryptSignCertificate(IN HCRYPTPROV hCryptProv, IN DWORD dwKeySpec, IN DWORD dwCertEncodingType, IN const BYTE *pbEncodedToBeSigned, IN DWORD cbEncodedToBeSigned, IN PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, IN OPTIONAL const void *pvHashAuxInfo, OUT BYTE *pbSignature, IN OUT DWORD *pcbSignature);
WINCRYPT32API BOOL WINAPI CryptUninstallDefaultContext(HCRYPTDEFAULTCONTEXT hDefaultContext, IN DWORD dwFlags, IN void *pvReserved);
WINCRYPT32API BOOL WINAPI CryptVerifyCertificateSignature(IN HCRYPTPROV hCryptProv, IN DWORD dwCertEncodingType, IN const BYTE * pbEncoded, IN DWORD cbEncoded, IN PCERT_PUBLIC_KEY_INFO pPublicKey);
WINCRYPT32API BOOL WINAPI PFXExportCertStoreEx(IN HCERTSTORE hStore, IN OUT CRYPT_DATA_BLOB* pPFX, IN LPCWSTR szPassword, IN void* pvReserved, IN DWORD dwFlags);
WINCRYPT32API HCERTSTORE WINAPI PFXImportCertStore(IN CRYPT_DATA_BLOB* pPFX, IN LPCWSTR szPassword, IN DWORD dwFlags);
WINCRYPT32API BOOL WINAPI PFXIsPFXBlob(IN CRYPT_DATA_BLOB* pPFX);
WINCRYPT32API BOOL WINAPI PFXVerifyPassword(IN CRYPT_DATA_BLOB* pPFX, IN LPCWSTR szPassword, IN DWORD dwFlags);

#ifdef __cplusplus
}
#endif

#endif /* _WINCRYPT_ */
#endif /* AKARI_WCE_WINCRYPT_H */
