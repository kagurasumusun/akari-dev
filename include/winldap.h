/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINLDAP_H
#define WCE_WINLDAP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLDAP_TIMEVAL { LONG tv_sec; LONG tv_usec; } LDAP_TIMEVAL, *PLDAP_TIMEVAL, *LPLDAP_TIMEVAL;
typedef struct tagLDAP_BERVAL { ULONG bv_len; PCHAR bv_val; } LDAP_BERVAL, *PLDAP_BERVAL, *LPLDAP_BERVAL;
typedef struct tagBerElement { PCHAR opaque; } BerElement, *PBerElement, *LPBerElement;
typedef struct tagLDAP_VERSION_INFO { ULONG lv_size; ULONG lv_major; ULONG lv_minor; } LDAP_VERSION_INFO, *PLDAP_VERSION_INFO, *LPLDAP_VERSION_INFO;
typedef struct tagLDAPAPIInfoA { int ldapai_info_version; int ldapai_api_version; int ldapai_protocol_version; char **ldapai_extensions; char *ldapai_vendor_name; int ldapai_vendor_version; } LDAPAPIInfoA, *PLDAPAPIInfoA, *LPLDAPAPIInfoA;
typedef struct tagLDAPAPIInfoW { int ldapai_info_version; int ldapai_api_version; int ldapai_protocol_version; PWCHAR *ldapai_extensions; PWCHAR ldapai_vendor_name; int ldapai_vendor_version; } LDAPAPIInfoW, *PLDAPAPIInfoW, *LPLDAPAPIInfoW;
typedef struct tagLDAPAPIFeatureInfoA { int ldapaif_info_version; char *ldapaif_name; int ldapaif_version; } LDAPAPIFeatureInfoA, *PLDAPAPIFeatureInfoA, *LPLDAPAPIFeatureInfoA;
typedef struct tagLDAPAPIFeatureInfoW { int ldapaif_info_version; PWCHAR ldapaif_name; int ldapaif_version; } LDAPAPIFeatureInfoW, *PLDAPAPIFeatureInfoW, *LPLDAPAPIFeatureInfoW;
typedef struct tagLDAPSortKeyW { PWCHAR sk_attrtype; PWCHAR sk_matchruleoid; BOOLEAN sk_reverseorder; } LDAPSortKeyW, *PLDAPSortKeyW, *LPLDAPSortKeyW;
typedef struct tagLDAPSortKeyA { PCHAR sk_attrtype; PCHAR sk_matchruleoid; BOOLEAN sk_reverseorder; } LDAPSortKeyA, *PLDAPSortKeyA, *LPLDAPSortKeyA;
typedef struct tagLDAPVLVInfo { int ldvlv_version; ULONG ldvlv_before_count; ULONG ldvlv_after_count; ULONG ldvlv_offset; ULONG ldvlv_count; PBERVAL ldvlv_attrvalue; PBERVAL ldvlv_context; VOID *ldvlv_extradata; } LDAPVLVInfo, *PLDAPVLVInfo, *LPLDAPVLVInfo;


#ifdef __cplusplus
}
#endif
#endif

