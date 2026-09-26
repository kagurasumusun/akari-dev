/*
 * winldap.h -- LDAP client API for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * The prototypes cover the application-facing surface of wldap32.dll.  The BER
 * layer it depends on is in winber.h.
 *
 * LDAP and LDAPMessage are opaque: the CE SDK exposes their layouts but no
 * application may rely on them, and every entry point takes a pointer.
 */
#ifndef AKARI_WCE_WINLDAP_H
#define AKARI_WCE_WINLDAP_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <winber.h>

#ifndef _WINLDAP_
#define _WINLDAP_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINLDAPAPI
#define WINLDAPAPI AKARI_DLLIMPORT
#endif

#ifndef LDAPAPI
#define LDAPAPI __cdecl
#endif
#ifndef LDAPCALL
#define LDAPCALL __cdecl
#endif

/* Whether the undecorated names map to the wide entry points.  CE derives this
 * from UNICODE rather than fixing it, so a UNICODE build -- the normal CE
 * build -- gets the W forms.  Hardcoding it to 0 mapped LDAPControl, LDAPMod
 * and LDAPSortKey onto their A forms instead, which is the wrong type. */
#ifndef LDAP_UNICODE
#ifdef UNICODE
#define LDAP_UNICODE 1
#else
#define LDAP_UNICODE 0
#endif
#endif

/* The session and result handles.  Their layouts are internal to wldap32. */
struct ldap;
typedef struct ldap LDAP, *PLDAP;
struct ldapmsg;
typedef struct ldapmsg LDAPMessage, *PLDAPMessage;
struct ldapsearch;
typedef struct ldapsearch LDAPSearch, *PLDAPSearch;

/* A server control: an OID, a BER value and a criticality flag. */
typedef struct akari_ldapcontrolA {
    PCHAR         ldctl_oid;
    BERVAL        ldctl_value;
    BOOLEAN       ldctl_iscritical;
} LDAPControlA, *PLDAPControlA;

typedef struct akari_ldapcontrolW {
    PWCHAR        ldctl_oid;
    BERVAL        ldctl_value;
    BOOLEAN       ldctl_iscritical;
} LDAPControlW, *PLDAPControlW;

#if LDAP_UNICODE
#define LDAPControl  LDAPControlW
#define PLDAPControl PLDAPControlW
#else
#define LDAPControl  LDAPControlA
#define PLDAPControl PLDAPControlA
#endif

/* A modification to one attribute of an entry. */
typedef struct akari_ldapmodW {
    ULONG   mod_op;
    PWCHAR  mod_type;
    union {
        PWCHAR       *modv_strvals;
        PBERVAL        *modv_bvals;
    } mod_vals;
} LDAPModW, *PLDAPModW;

typedef struct akari_ldapmodA {
    ULONG   mod_op;
    PCHAR   mod_type;
    union {
        PCHAR        *modv_strvals;
        PBERVAL        *modv_bvals;
    } mod_vals;
} LDAPModA, *PLDAPModA;

#if LDAP_UNICODE
#define LDAPMod  LDAPModW
#define PLDAPMod PLDAPModW
#else
#define LDAPMod  LDAPModA
#define PLDAPMod PLDAPModA
#endif

#define mod_values  mod_vals.modv_strvals
#define mod_bvalues mod_vals.modv_bvals

#define LDAP_MOD_ADD         0x00
#define LDAP_MOD_DELETE      0x01
#define LDAP_MOD_REPLACE     0x02
#define LDAP_MOD_BVALUES     0x80

/* Search scopes. */
#define LDAP_SCOPE_BASE      0x00
#define LDAP_SCOPE_ONELEVEL  0x01
#define LDAP_SCOPE_SUBTREE   0x02

/* Deref and attribute controls. */
#define LDAP_DEREF_NEVER         0
#define LDAP_DEREF_SEARCHING     1
#define LDAP_DEREF_FINDING       2
#define LDAP_DEREF_ALWAYS        3

#define LDAP_CHASE_SUBORDINATE_REFS  0x20
#define LDAP_CHASE_EXTERNAL_REFS     0x40

#define LDAP_PORT            389
#define LDAP_SSL_PORT        636
#define LDAP_GC_PORT         3268
#define LDAP_SSL_GC_PORT     3269
#define LDAP_UDP_PORT        389

#define LDAP_VERSION1        1
#define LDAP_VERSION2        2
#define LDAP_VERSION3        3
#define LDAP_VERSION         LDAP_VERSION2

#define LDAP_SUCCESS                  0x00
#define LDAP_OPERATIONS_ERROR         0x01
#define LDAP_PROTOCOL_ERROR           0x02
#define LDAP_TIMELIMIT_EXCEEDED       0x03
#define LDAP_SIZELIMIT_EXCEEDED       0x04
#define LDAP_COMPARE_FALSE            0x05
#define LDAP_COMPARE_TRUE             0x06
#define LDAP_AUTH_METHOD_NOT_SUPPORTED 0x07
#define LDAP_STRONG_AUTH_REQUIRED     0x08
#define LDAP_REFERRAL                 0x0a
#define LDAP_ADMIN_LIMIT_EXCEEDED     0x0b
#define LDAP_UNAVAILABLE_CRIT_EXTENSION 0x0c
#define LDAP_CONFIDENTIALITY_REQUIRED 0x0d
#define LDAP_SASL_BIND_IN_PROGRESS    0x0e
#define LDAP_NO_SUCH_ATTRIBUTE        0x10
#define LDAP_UNDEFINED_TYPE           0x11
#define LDAP_INAPPROPRIATE_MATCHING   0x12
#define LDAP_CONSTRAINT_VIOLATION     0x13
#define LDAP_ATTRIBUTE_EXISTS         0x14
#define LDAP_NO_RESULTS_RETURNED      0x1a
#define LDAP_MORE_RESULTS_TO_RETURN   0x1b
#define LDAP_NO_OBJECT_CLASS_MODS     0x45
#define LDAP_LOCAL_ERROR              0x51
#define LDAP_ENCODING_ERROR           0x52
#define LDAP_DECODING_ERROR           0x53
#define LDAP_TIMEOUT                  0x55
#define LDAP_AUTH_UNKNOWN             0x56
#define LDAP_FILTER_ERROR             0x57
#define LDAP_USER_CANCELLED           0x58
#define LDAP_PARAM_ERROR              0x59
#define LDAP_NO_MEMORY                0x5a
#define LDAP_CONNECT_ERROR            0x5b
#define LDAP_NOT_SUPPORTED            0x5c
#define LDAP_SERVER_DOWN              0x51
#define LDAP_CLIENT_LOOP              0x60
#define LDAP_REFERRAL_LIMIT_EXCEEDED  0x61

#define LDAP_RES_ANY             (-1)
#define LDAP_RES_UNSOLICITED     0
#define LDAP_RES_BIND            0x61
#define LDAP_RES_SEARCH_ENTRY    0x64
#define LDAP_RES_SEARCH_RESULT   0x65
#define LDAP_RES_MODIFY          0x67
#define LDAP_RES_ADD             0x69
#define LDAP_RES_DELETE          0x6b
#define LDAP_RES_MODRDN          0x6d
#define LDAP_RES_COMPARE         0x6f
#define LDAP_RES_SEARCH_REFERENCE 0x73
#define LDAP_RES_EXTENDED        0x78

#define LDAP_OPT_DESC                0x01
#define LDAP_OPT_DEREF             0x02
#define LDAP_OPT_SIZELIMIT           0x03
#define LDAP_OPT_TIMELIMIT           0x04
#define LDAP_OPT_THREAD_FN_PTRS      0x05
#define LDAP_OPT_REBIND_FN           0x06
#define LDAP_OPT_REBIND_ARG          0x07
#define LDAP_OPT_REFERRALS           0x08
#define LDAP_OPT_RESTART             0x09
#define LDAP_OPT_SSL                 0x0a
#define LDAP_OPT_IO_FN_PTRS          0x0b
#define LDAP_OPT_CACHE_FN_PTRS       0x0d
#define LDAP_OPT_CACHE_STRATEGY      0x0e
#define LDAP_OPT_CACHE_ENABLE        0x0f
#define LDAP_OPT_REFERRAL_HOP_LIMIT  0x10
#define LDAP_OPT_PROTOCOL_VERSION    0x11
#define LDAP_OPT_VERSION             0x11
#define LDAP_OPT_API_INFO            0x00
#define LDAP_OPT_GETDSNAME_FLAGS     0x3D
#define LDAP_OPT_HOST_NAME           0x30
#define LDAP_OPT_ERROR_NUMBER        0x31
#define LDAP_OPT_ERROR_STRING        0x32
#define LDAP_OPT_SERVER_ERROR        0x33
#define LDAP_OPT_SERVER_EXT_ERROR    0x34
#define LDAP_OPT_NETWORK_TIMEOUT     0x4005

#define LDAP_FILTER_AND              0xa0
#define LDAP_FILTER_OR               0xa1
#define LDAP_FILTER_NOT              0xa2
#define LDAP_FILTER_EQUALITY         0xa3
#define LDAP_FILTER_SUBSTRINGS       0xa4
#define LDAP_FILTER_GE               0xa5
#define LDAP_FILTER_LE               0xa6
#define LDAP_FILTER_PRESENT          0x87
#define LDAP_FILTER_APPROX           0xa8
#define LDAP_FILTER_EXTENSIBLE       0xa9

/* An LDAP timeout, in seconds and microseconds. */
typedef struct akari_l_timeval {
    LONG tv_sec;
    LONG tv_usec;
} LDAP_TIMEVAL, *PLDAP_TIMEVAL;

/* Virtual list view request state. */
typedef struct akari_ldapvlvinfo {
    int     ldvlv_version;
    ULONG   ldvlv_before_count;
    ULONG   ldvlv_after_count;
    ULONG   ldvlv_offset;
    ULONG   ldvlv_count;
    PBERVAL ldvlv_attrvalue;
    PBERVAL ldvlv_context;
    void   *ldvlv_extradata;
} LDAPVLVInfo, *PLDAPVLVInfo;

#define LDAP_VLVINFO_VERSION 1

/* Version record passed to ldap_startup. */
typedef struct akari_ldap_version_info {
    ULONG lv_size;
    ULONG lv_major;
    ULONG lv_minor;
} LDAP_VERSION_INFO, *PLDAP_VERSION_INFO;

/* Debug output callback, used by ldap_set_dbg_routine. */
typedef ULONG (__cdecl *DBGPRINT)(char *, ...);

/* Sort keys, used by ldap_create_sort_control. */
typedef struct akari_ldapsortkeyA {
    PCHAR  sk_attrtype;
    PCHAR  sk_matchruleoid;
    BOOLEAN sk_reverseorder;
} LDAPSortKeyA, *PLDAPSortKeyA;

typedef struct akari_ldapsortkeyW {
    PWCHAR sk_attrtype;
    PWCHAR sk_matchruleoid;
    BOOLEAN sk_reverseorder;
} LDAPSortKeyW, *PLDAPSortKeyW;

#if LDAP_UNICODE
#define LDAPSortKey  LDAPSortKeyW
#define PLDAPSortKey PLDAPSortKeyW
#else
#define LDAPSortKey  LDAPSortKeyA
#define PLDAPSortKey PLDAPSortKeyA
#endif

/* ------------------------------------------------------- prototypes */

WINLDAPAPI LDAP * LDAPAPI cldap_open(PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI cldap_openA(PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI cldap_openW(PWCHAR HostName, ULONG PortNumber);
WINLDAPAPI ULONG LDAPAPI ldap_abandon(LDAP *ld, ULONG msgid);
WINLDAPAPI ULONG LDAPAPI ldap_add(LDAP *ld, PCHAR dn, LDAPMod *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_add_ext(LDAP *ld, const PCHAR dn, LDAPModA *attrs[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_add_ext_s(LDAP *ld, const PCHAR dn, LDAPModA *attrs[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_add_ext_sA(LDAP *ld, const PCHAR dn, LDAPModA *attrs[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_add_ext_sW(LDAP *ld, const PWCHAR dn, LDAPModW *attrs[], PLDAPControlW *ServerControls, PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_add_extA(LDAP *ld, const PCHAR dn, LDAPModA *attrs[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_add_extW(LDAP *ld, const PWCHAR dn, LDAPModW *attrs[], PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_add_s(LDAP *ld, PCHAR dn, LDAPMod *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_add_sA(LDAP *ld, PCHAR dn, LDAPModA *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_add_sW(LDAP *ld, PWCHAR dn, LDAPModW *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_addA(LDAP *ld, PCHAR dn, LDAPModA *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_addW(LDAP *ld, PWCHAR dn, LDAPModW *attrs[]);
WINLDAPAPI ULONG LDAPAPI ldap_bind(LDAP *ld, const PCHAR dn, const PCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_bind_s(LDAP *ld, const PCHAR dn, const PCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_bind_sA(LDAP *ld, PCHAR dn, PCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_bind_sW(LDAP *ld, PWCHAR dn, PWCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_bindA(LDAP *ld, PCHAR dn, PCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_bindW(LDAP *ld, PWCHAR dn, PWCHAR cred, ULONG method);
WINLDAPAPI ULONG LDAPAPI ldap_check_filterA(LDAP *ld, PCHAR SearchFilter);
WINLDAPAPI ULONG LDAPAPI ldap_check_filterW(LDAP *ld, PWCHAR SearchFilter);
WINLDAPAPI ULONG LDAPAPI ldap_cleanup(HANDLE hInstance);
WINLDAPAPI ULONG LDAPAPI ldap_close_extended_op(LDAP *ld, ULONG MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_compare(LDAP *ld, const PCHAR dn, const PCHAR attr, PCHAR value);
WINLDAPAPI ULONG LDAPAPI ldap_compare_ext(LDAP *ld, const PCHAR dn, const PCHAR Attr, const PCHAR Value, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_compare_ext_s(LDAP *ld, const PCHAR dn, const PCHAR Attr, const PCHAR Value, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_compare_ext_sA(LDAP *ld, const PCHAR dn, const PCHAR Attr, const PCHAR Value, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_compare_ext_sW(LDAP *ld, const PWCHAR dn, const PWCHAR Attr, const PWCHAR Value, PBERVAL Data, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_compare_extA(LDAP *ld, const PCHAR dn, const PCHAR Attr, const PCHAR Value, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_compare_extW(LDAP *ld, const PWCHAR dn, const PWCHAR Attr, const PWCHAR Value, PBERVAL Data, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_compare_s(LDAP *ld, const PCHAR dn, const PCHAR attr, PCHAR value);
WINLDAPAPI ULONG LDAPAPI ldap_compare_sA(LDAP *ld, const PCHAR dn, const PCHAR attr, PCHAR value);
WINLDAPAPI ULONG LDAPAPI ldap_compare_sW(LDAP *ld, const PWCHAR dn, const PWCHAR attr, PWCHAR value);
WINLDAPAPI ULONG LDAPAPI ldap_compareA(LDAP *ld, const PCHAR dn, const PCHAR attr, PCHAR value);
WINLDAPAPI ULONG LDAPAPI ldap_compareW(LDAP *ld, const PWCHAR dn, const PWCHAR attr, PWCHAR value);
WINLDAPAPI LDAP * LDAPAPI ldap_conn_from_msg(LDAP *PrimaryConn, LDAPMessage *res);
WINLDAPAPI ULONG LDAPAPI ldap_connect(LDAP *ld, LDAP_TIMEVAL *timeout);
WINLDAPAPI ULONG LDAPAPI ldap_control_free(LDAPControlA *Control);
WINLDAPAPI ULONG LDAPAPI ldap_control_freeA(LDAPControlA *Controls);
WINLDAPAPI ULONG LDAPAPI ldap_control_freeW(LDAPControlW *Control);
WINLDAPAPI ULONG LDAPAPI ldap_controls_free(LDAPControlA **Controls);
WINLDAPAPI ULONG LDAPAPI ldap_controls_freeA(LDAPControlA **Controls);
WINLDAPAPI ULONG LDAPAPI ldap_controls_freeW(LDAPControlW **Control);
WINLDAPAPI ULONG LDAPAPI ldap_count_entries(LDAP *ld, LDAPMessage *res);
WINLDAPAPI ULONG LDAPAPI ldap_count_references(LDAP *ld, LDAPMessage *res);
WINLDAPAPI ULONG LDAPAPI ldap_count_values(PCHAR *vals);
WINLDAPAPI ULONG LDAPAPI ldap_count_values_len(PBERVAL *vals);
WINLDAPAPI ULONG LDAPAPI ldap_count_valuesA(PCHAR *vals);
WINLDAPAPI ULONG LDAPAPI ldap_count_valuesW(PWCHAR *vals);
WINLDAPAPI ULONG LDAPAPI ldap_create_page_control(PLDAP ExternalHandle, ULONG PageSize, PBERVAL Cookie, UCHAR IsCritical, PLDAPControlA *Control);
WINLDAPAPI ULONG LDAPAPI ldap_create_page_controlA(PLDAP ExternalHandle, ULONG PageSize, PBERVAL Cookie, UCHAR IsCritical, PLDAPControlA *Control);
WINLDAPAPI ULONG LDAPAPI ldap_create_page_controlW(PLDAP ExternalHandle, ULONG PageSize, PBERVAL Cookie, UCHAR IsCritical, PLDAPControlW *Control);
WINLDAPAPI ULONG LDAPAPI ldap_create_sort_control(PLDAP ExternalHandle, PLDAPSortKeyA *SortKeys, UCHAR IsCritical, PLDAPControlA *Control);
WINLDAPAPI ULONG LDAPAPI ldap_create_sort_controlA(PLDAP ExternalHandle, PLDAPSortKeyA *SortKeys, UCHAR IsCritical, PLDAPControlA *Control);
WINLDAPAPI ULONG LDAPAPI ldap_create_sort_controlW(PLDAP ExternalHandle, PLDAPSortKeyW *SortKeys, UCHAR IsCritical, PLDAPControlW *Control);
WINLDAPAPI INT LDAPAPI ldap_create_vlv_controlA(PLDAP ExternalHandle, PLDAPVLVInfo VlvInfo, UCHAR IsCritical, PLDAPControlA *Control);
WINLDAPAPI INT LDAPAPI ldap_create_vlv_controlW(PLDAP ExternalHandle, PLDAPVLVInfo VlvInfo, UCHAR IsCritical, PLDAPControlW *Control);
WINLDAPAPI ULONG LDAPAPI ldap_delete(LDAP *ld, PCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_delete_ext(LDAP *ld, const PCHAR dn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_delete_ext_s(LDAP *ld, const PCHAR dn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_delete_ext_sA(LDAP *ld, const PCHAR dn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_delete_ext_sW(LDAP *ld, const PWCHAR dn, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_delete_extA(LDAP *ld, const PCHAR dn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_delete_extW(LDAP *ld, const PWCHAR dn, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_delete_s(LDAP *ld, PCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_delete_sA(LDAP *ld, const PCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_delete_sW(LDAP *ld, const PWCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_deleteA(LDAP *ld, const PCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_deleteW(LDAP *ld, const PWCHAR dn);
WINLDAPAPI PCHAR LDAPAPI ldap_dn2ufn(const PCHAR dn);
WINLDAPAPI PCHAR LDAPAPI ldap_dn2ufnA(const PCHAR dn);
WINLDAPAPI PWCHAR LDAPAPI ldap_dn2ufnW(const PWCHAR dn);
WINLDAPAPI ULONG LDAPAPI ldap_encode_sort_controlA(PLDAP ExternalHandle, PLDAPSortKeyA *SortKeys, PLDAPControlA Control, BOOLEAN Criticality);
WINLDAPAPI ULONG LDAPAPI ldap_encode_sort_controlW(PLDAP ExternalHandle, PLDAPSortKeyW *SortKeys, PLDAPControlW Control, BOOLEAN Criticality);
WINLDAPAPI PCHAR LDAPAPI ldap_err2string(ULONG err);
WINLDAPAPI PCHAR LDAPAPI ldap_err2stringA(ULONG err);
WINLDAPAPI PWCHAR LDAPAPI ldap_err2stringW(ULONG err);
WINLDAPAPI ULONG LDAPAPI ldap_escape_filter_element(PCHAR sourceFilterElement, ULONG sourceLength, PCHAR destFilterElement, ULONG destLength);
WINLDAPAPI ULONG LDAPAPI ldap_escape_filter_elementA(PCHAR sourceFilterElement, ULONG sourceLength, PCHAR destFilterElement, ULONG destLength);
WINLDAPAPI ULONG LDAPAPI ldap_escape_filter_elementW(PCHAR sourceFilterElement, ULONG sourceLength, PWCHAR destFilterElement, ULONG destLength);
WINLDAPAPI PCHAR *LDAPAPI LDAPAPI ldap_explode_dn(const PCHAR dn, ULONG notypes);
WINLDAPAPI PCHAR *LDAPAPI LDAPAPI ldap_explode_dnA(const PCHAR dn, ULONG notypes);
WINLDAPAPI PWCHAR *LDAPAPI LDAPAPI ldap_explode_dnW(const PWCHAR dn, ULONG notypes);
WINLDAPAPI ULONG LDAPAPI ldap_extended_operation(LDAP *ld, const PCHAR Oid, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_extended_operation_sA(LDAP *ExternalHandle, PCHAR Oid, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, PCHAR *ReturnedOid, PBERVAL *ReturnedData);
WINLDAPAPI ULONG LDAPAPI ldap_extended_operation_sW(LDAP *ExternalHandle, PWCHAR Oid, PBERVAL Data, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, PWCHAR *ReturnedOid, PBERVAL *ReturnedData);
WINLDAPAPI ULONG LDAPAPI ldap_extended_operationA(LDAP *ld, const PCHAR Oid, PBERVAL Data, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_extended_operationW(LDAP *ld, const PWCHAR Oid, PBERVAL Data, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI PCHAR LDAPAPI ldap_first_attribute(LDAP *ld, LDAPMessage *entry, BerElement **ptr);
WINLDAPAPI PCHAR LDAPAPI ldap_first_attributeA(LDAP *ld, LDAPMessage *entry, BerElement **ptr);
WINLDAPAPI PWCHAR LDAPAPI ldap_first_attributeW(LDAP *ld, LDAPMessage *entry, BerElement **ptr);
WINLDAPAPI LDAPMessage *LDAPAPI LDAPAPI ldap_first_entry(LDAP *ld, LDAPMessage *res);
WINLDAPAPI LDAPMessage *LDAPAPI LDAPAPI ldap_first_reference(LDAP *ld, LDAPMessage *res);
WINLDAPAPI ULONG LDAPAPI ldap_free_controls(LDAPControlA **Controls);
WINLDAPAPI ULONG LDAPAPI ldap_free_controlsA(LDAPControlA **Controls);
WINLDAPAPI ULONG LDAPAPI ldap_free_controlsW(LDAPControlW **Controls);
WINLDAPAPI PCHAR LDAPAPI ldap_get_dn(LDAP *ld, LDAPMessage *entry);
WINLDAPAPI PCHAR LDAPAPI ldap_get_dnA(LDAP *ld, LDAPMessage *entry);
WINLDAPAPI PWCHAR LDAPAPI ldap_get_dnW(LDAP *ld, LDAPMessage *entry);
WINLDAPAPI ULONG LDAPAPI ldap_get_next_page(PLDAP ExternalHandle, PLDAPSearch SearchHandle, ULONG PageSize, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_get_next_page_s(PLDAP ExternalHandle, PLDAPSearch SearchHandle, LDAP_TIMEVAL *timeout, ULONG PageSize, ULONG *TotalCount, LDAPMessage **Results);
WINLDAPAPI ULONG LDAPAPI ldap_get_option(LDAP *ld, int option, void *outvalue);
WINLDAPAPI ULONG LDAPAPI ldap_get_optionW(LDAP *ld, int option, void *outvalue);
WINLDAPAPI ULONG LDAPAPI ldap_get_paged_count(PLDAP ExternalHandle, PLDAPSearch SearchBlock, ULONG *TotalCount, PLDAPMessage Results);
WINLDAPAPI PCHAR *LDAPAPI LDAPAPI ldap_get_values(LDAP *ld, LDAPMessage *entry, const PCHAR attr);
WINLDAPAPI PBERVAL *LDAPAPI LDAPAPI ldap_get_values_len(LDAP *ExternalHandle, LDAPMessage *Message, const PCHAR attr);
WINLDAPAPI PBERVAL *LDAPAPI LDAPAPI ldap_get_values_lenA(LDAP *ExternalHandle, LDAPMessage *Message, const PCHAR attr);
WINLDAPAPI PBERVAL *LDAPAPI LDAPAPI ldap_get_values_lenW(LDAP *ExternalHandle, LDAPMessage *Message, const PWCHAR attr);
WINLDAPAPI PCHAR *LDAPAPI LDAPAPI ldap_get_valuesA(LDAP *ld, LDAPMessage *entry, const PCHAR attr);
WINLDAPAPI PWCHAR *LDAPAPI LDAPAPI ldap_get_valuesW(LDAP *ld, LDAPMessage *entry, const PWCHAR attr);
WINLDAPAPI LDAP * LDAPAPI ldap_init(PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI ldap_initA(const PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI ldap_initW(const PWCHAR HostName, ULONG PortNumber);
WINLDAPAPI VOID LDAPAPI ldap_memfree(PCHAR Block);
WINLDAPAPI VOID LDAPAPI ldap_memfreeA(PCHAR Block);
WINLDAPAPI VOID LDAPAPI ldap_memfreeW(PWCHAR Block);
WINLDAPAPI ULONG LDAPAPI ldap_modify(LDAP *ld, PCHAR dn, LDAPModA *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modify_ext(LDAP *ld, const PCHAR dn, LDAPModA *mods[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_modify_ext_s(LDAP *ld, const PCHAR dn, LDAPModA *mods[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_modify_ext_sA(LDAP *ld, const PCHAR dn, LDAPModA *mods[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_modify_ext_sW(LDAP *ld, const PWCHAR dn, LDAPModW *mods[], PLDAPControlW *ServerControls, PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_modify_extA(LDAP *ld, const PCHAR dn, LDAPModA *mods[], PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_modify_extW(LDAP *ld, const PWCHAR dn, LDAPModW *mods[], PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_modify_s(LDAP *ld, PCHAR dn, LDAPModA *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modify_sA(LDAP *ld, PCHAR dn, LDAPModA *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modify_sW(LDAP *ld, PWCHAR dn, LDAPModW *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modifyA(LDAP *ld, PCHAR dn, LDAPModA *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modifyW(LDAP *ld, PWCHAR dn, LDAPModW *mods[]);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2_s(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2_sA(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2_sW(LDAP *ExternalHandle, const PWCHAR DistinguishedName, const PWCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2A(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn2W(LDAP *ExternalHandle, const PWCHAR DistinguishedName, const PWCHAR NewDistinguishedName, INT DeleteOldRdn);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn_s(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn_sA(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_modrdn_sW(LDAP *ExternalHandle, const PWCHAR DistinguishedName, const PWCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_modrdnA(LDAP *ExternalHandle, const PCHAR DistinguishedName, const PCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_modrdnW(LDAP *ExternalHandle, const PWCHAR DistinguishedName, const PWCHAR NewDistinguishedName);
WINLDAPAPI ULONG LDAPAPI ldap_msgfree(LDAPMessage *res);
WINLDAPAPI PCHAR LDAPAPI ldap_next_attribute(LDAP *ld, LDAPMessage *entry, BerElement *ptr);
WINLDAPAPI PCHAR LDAPAPI ldap_next_attributeA(LDAP *ld, LDAPMessage *entry, BerElement *ptr);
WINLDAPAPI PWCHAR LDAPAPI ldap_next_attributeW(LDAP *ld, LDAPMessage *entry, BerElement *ptr);
WINLDAPAPI LDAPMessage *LDAPAPI LDAPAPI ldap_next_entry(LDAP *ld, LDAPMessage *entry);
WINLDAPAPI LDAPMessage *LDAPAPI LDAPAPI ldap_next_reference(LDAP *ld, LDAPMessage *entry);
WINLDAPAPI LDAP * LDAPAPI ldap_open(PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI ldap_openA(const PCHAR HostName, ULONG PortNumber);
WINLDAPAPI LDAP * LDAPAPI ldap_openW(const PWCHAR HostName, ULONG PortNumber);
WINLDAPAPI ULONG LDAPAPI ldap_parse_extended_resultA(LDAP *Connection, LDAPMessage *ResultMessage, PCHAR *ResultOID, PBERVAL *ResultData, BOOLEAN Freeit);
WINLDAPAPI ULONG LDAPAPI ldap_parse_extended_resultW(LDAP *Connection, LDAPMessage *ResultMessage, PWCHAR *ResultOID, PBERVAL *ResultData, BOOLEAN Freeit);
WINLDAPAPI ULONG LDAPAPI ldap_parse_page_control(PLDAP ExternalHandle, PLDAPControlA *ServerControls, ULONG *TotalCount, PBERVAL *Cookie);
WINLDAPAPI ULONG LDAPAPI ldap_parse_page_controlA(PLDAP ExternalHandle, PLDAPControlA *ServerControls, ULONG *TotalCount, PBERVAL *Cookie);
WINLDAPAPI ULONG LDAPAPI ldap_parse_page_controlW(PLDAP ExternalHandle, PLDAPControlW *ServerControls, ULONG *TotalCount, PBERVAL *Cookie);
WINLDAPAPI ULONG LDAPAPI ldap_parse_reference(LDAP *Connection, LDAPMessage *ResultMessage, PCHAR **Referrals);
WINLDAPAPI ULONG LDAPAPI ldap_parse_referenceA(LDAP *Connection, LDAPMessage *ResultMessage, PCHAR **Referrals);
WINLDAPAPI ULONG LDAPAPI ldap_parse_referenceW(LDAP *Connection, LDAPMessage *ResultMessage, PWCHAR **Referrals);
WINLDAPAPI ULONG LDAPAPI ldap_parse_result(LDAP *Connection, LDAPMessage *ResultMessage, ULONG *ReturnCode OPTIONAL, PCHAR *MatchedDNs OPTIONAL, PCHAR *ErrorMessage OPTIONAL, PCHAR **Referrals OPTIONAL, PLDAPControlA **ServerControls OPTIONAL, BOOLEAN Freeit);
WINLDAPAPI ULONG LDAPAPI ldap_parse_resultA(LDAP *Connection, LDAPMessage *ResultMessage, ULONG *ReturnCode OPTIONAL, PCHAR *MatchedDNs OPTIONAL, PCHAR *ErrorMessage OPTIONAL, PCHAR **Referrals OPTIONAL, PLDAPControlA **ServerControls OPTIONAL, BOOLEAN Freeit);
WINLDAPAPI ULONG LDAPAPI ldap_parse_resultW(LDAP *Connection, LDAPMessage *ResultMessage, ULONG *ReturnCode OPTIONAL, PWCHAR *MatchedDNs OPTIONAL, PWCHAR *ErrorMessage OPTIONAL, PWCHAR **Referrals OPTIONAL, PLDAPControlW **ServerControls OPTIONAL, BOOLEAN Freeit);
WINLDAPAPI ULONG LDAPAPI ldap_parse_sort_control(PLDAP ExternalHandle, PLDAPControlA *Control, ULONG *Result, PCHAR *Attribute);
WINLDAPAPI ULONG LDAPAPI ldap_parse_sort_controlA(PLDAP ExternalHandle, PLDAPControlA *Control, ULONG *Result, PCHAR *Attribute);
WINLDAPAPI ULONG LDAPAPI ldap_parse_sort_controlW(PLDAP ExternalHandle, PLDAPControlW *Control, ULONG *Result, PWCHAR *Attribute);
WINLDAPAPI INT LDAPAPI ldap_parse_vlv_controlA(PLDAP ExternalHandle, PLDAPControlA *Control, PULONG TargetPos, PULONG ListCount, PBERVAL *Context, PINT ErrCode);
WINLDAPAPI INT LDAPAPI ldap_parse_vlv_controlW(PLDAP ExternalHandle, PLDAPControlW *Control, PULONG TargetPos, PULONG ListCount, PBERVAL *Context, PINT ErrCode);
WINLDAPAPI void LDAPAPI ldap_perror(LDAP *ld, const PCHAR msg);
WINLDAPAPI ULONG LDAPAPI ldap_rename_ext(LDAP *ld, const PCHAR dn, const PCHAR NewRDN, const PCHAR NewParent, INT DeleteOldRdn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_rename_ext_s(LDAP *ld, const PCHAR dn, const PCHAR NewRDN, const PCHAR NewParent, INT DeleteOldRdn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_rename_ext_sA(LDAP *ld, const PCHAR dn, const PCHAR NewRDN, const PCHAR NewParent, INT DeleteOldRdn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_rename_ext_sW(LDAP *ld, const PWCHAR dn, const PWCHAR NewRDN, const PWCHAR NewParent, INT DeleteOldRdn, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_rename_extA(LDAP *ld, const PCHAR dn, const PCHAR NewRDN, const PCHAR NewParent, INT DeleteOldRdn, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_rename_extW(LDAP *ld, const PWCHAR dn, const PWCHAR NewRDN, const PWCHAR NewParent, INT DeleteOldRdn, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_result(LDAP *ld, ULONG msgid, ULONG all, LDAP_TIMEVAL *timeout, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_result2error(LDAP *ld, LDAPMessage *res, ULONG freeit);
WINLDAPAPI ULONG LDAPAPI ldap_search(LDAP *ld, PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly);
WINLDAPAPI ULONG LDAPAPI ldap_search_abandon_page(PLDAP ExternalHandle, PLDAPSearch SearchBlock);
WINLDAPAPI ULONG LDAPAPI ldap_search_ext(LDAP *ld, PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG TimeLimit, ULONG SizeLimit, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_search_ext_s(LDAP *ld, PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, LDAP_TIMEVAL *timeout, ULONG SizeLimit, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_ext_sA(LDAP *ld, const PCHAR base, ULONG scope, const PCHAR filter, PCHAR attrs[], ULONG attrsonly, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, LDAP_TIMEVAL *timeout, ULONG SizeLimit, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_ext_sW(LDAP *ld, const PWCHAR base, ULONG scope, const PWCHAR filter, PWCHAR attrs[], ULONG attrsonly, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, LDAP_TIMEVAL *timeout, ULONG SizeLimit, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_extA(LDAP *ld, const PCHAR base, ULONG scope, const PCHAR filter, PCHAR attrs[], ULONG attrsonly, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG TimeLimit, ULONG SizeLimit, ULONG *MessageNumber);
WINLDAPAPI ULONG LDAPAPI ldap_search_extW(LDAP *ld, const PWCHAR base, ULONG scope, const PWCHAR filter, PWCHAR attrs[], ULONG attrsonly, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG TimeLimit, ULONG SizeLimit, ULONG *MessageNumber);
WINLDAPAPI PLDAPSearch LDAPAPI ldap_search_init_page(PLDAP ExternalHandle, const PCHAR DistinguishedName, ULONG ScopeOfSearch, const PCHAR SearchFilter, PCHAR AttributeList[], ULONG AttributesOnly, PLDAPControl *ServerControls, PLDAPControl *ClientControls, ULONG PageTimeLimit, ULONG TotalSizeLimit, PLDAPSortKey *SortKeys);
WINLDAPAPI PLDAPSearch LDAPAPI ldap_search_init_pageA(PLDAP ExternalHandle, const PCHAR DistinguishedName, ULONG ScopeOfSearch, const PCHAR SearchFilter, PCHAR AttributeList[], ULONG AttributesOnly, PLDAPControlA *ServerControls, PLDAPControlA *ClientControls, ULONG PageTimeLimit, ULONG TotalSizeLimit, PLDAPSortKeyA *SortKeys);
WINLDAPAPI PLDAPSearch LDAPAPI ldap_search_init_pageW(PLDAP ExternalHandle, const PWCHAR DistinguishedName, ULONG ScopeOfSearch, const PWCHAR SearchFilter, PWCHAR AttributeList[], ULONG AttributesOnly, PLDAPControlW *ServerControls, PLDAPControlW *ClientControls, ULONG PageTimeLimit, ULONG TotalSizeLimit, PLDAPSortKeyW *SortKeys);
WINLDAPAPI ULONG LDAPAPI ldap_search_s(LDAP *ld, PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_sA(LDAP *ld, const PCHAR base, ULONG scope, const PCHAR filter, PCHAR attrs[], ULONG attrsonly, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_st(LDAP *ld, PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly, LDAP_TIMEVAL *timeout, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_stA(LDAP *ld, const PCHAR base, ULONG scope, const PCHAR filter, PCHAR attrs[], ULONG attrsonly, LDAP_TIMEVAL *timeout, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_stW(LDAP *ld, const PWCHAR base, ULONG scope, const PWCHAR filter, PWCHAR attrs[], ULONG attrsonly, LDAP_TIMEVAL *timeout, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_search_sW(LDAP *ld, const PWCHAR base, ULONG scope, const PWCHAR filter, PWCHAR attrs[], ULONG attrsonly, LDAPMessage **res);
WINLDAPAPI ULONG LDAPAPI ldap_searchA(LDAP *ld, const PCHAR base, ULONG scope, const PCHAR filter, PCHAR attrs[], ULONG attrsonly);
WINLDAPAPI ULONG LDAPAPI ldap_searchW(LDAP *ld, const PWCHAR base, ULONG scope, const PWCHAR filter, PWCHAR attrs[], ULONG attrsonly);
WINLDAPAPI ULONG LDAPAPI ldap_set_dbg_flags(ULONG NewFlags);
WINLDAPAPI VOID LDAPAPI ldap_set_dbg_routine(DBGPRINT DebugPrintRoutine);
WINLDAPAPI ULONG LDAPAPI ldap_set_option(LDAP *ld, int option, const void *invalue);
WINLDAPAPI ULONG LDAPAPI ldap_set_optionW(LDAP *ld, int option, const void *invalue);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bind(LDAP *ld, const PCHAR dn, const PCHAR passwd);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bind_s(LDAP *ld, const PCHAR dn, const PCHAR passwd);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bind_sA(LDAP *ld, PCHAR dn, PCHAR passwd);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bind_sW(LDAP *ld, PWCHAR dn, PWCHAR passwd);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bindA(LDAP *ld, PCHAR dn, PCHAR passwd);
WINLDAPAPI ULONG LDAPAPI ldap_simple_bindW(LDAP *ld, PWCHAR dn, PWCHAR passwd);
WINLDAPAPI LDAP * LDAPAPI ldap_sslinit(PCHAR HostName, ULONG PortNumber, int secure);
WINLDAPAPI LDAP * LDAPAPI ldap_sslinitA(PCHAR HostName, ULONG PortNumber, int secure);
WINLDAPAPI LDAP * LDAPAPI ldap_sslinitW(PWCHAR HostName, ULONG PortNumber, int secure);
WINLDAPAPI ULONG LDAPAPI ldap_start_tls_sA(IN PLDAP ExternalHandle, OUT PULONG ServerReturnValue, OUT LDAPMessage **result, IN PLDAPControlA *ServerControls, IN PLDAPControlA *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_start_tls_sW(IN PLDAP ExternalHandle, OUT PULONG ServerReturnValue, OUT LDAPMessage **result, IN PLDAPControlW *ServerControls, IN PLDAPControlW *ClientControls);
WINLDAPAPI ULONG LDAPAPI ldap_startup(PLDAP_VERSION_INFO version, HANDLE *Instance);
WINLDAPAPI BOOLEAN LDAPAPI ldap_stop_tls_s(IN PLDAP ExternalHandle);
WINLDAPAPI ULONG LDAPAPI ldap_ufn2dn(const PCHAR ufn, PCHAR *pDn);
WINLDAPAPI ULONG LDAPAPI ldap_ufn2dnA(const PCHAR ufn, PCHAR *pDn);
WINLDAPAPI ULONG LDAPAPI ldap_ufn2dnW(const PWCHAR ufn, PWCHAR *pDn);
WINLDAPAPI ULONG LDAPAPI ldap_unbind(LDAP *ld);
WINLDAPAPI ULONG LDAPAPI ldap_unbind_s(LDAP *ld);
WINLDAPAPI ULONG LDAPAPI ldap_value_free(PCHAR *vals);
WINLDAPAPI ULONG LDAPAPI ldap_value_free_len(PBERVAL *vals);
WINLDAPAPI ULONG LDAPAPI ldap_value_freeA(PCHAR *vals);
WINLDAPAPI ULONG LDAPAPI ldap_value_freeW(PWCHAR *vals);
WINLDAPAPI ULONG LDAPAPI LdapGetLastError(VOID);
WINLDAPAPI ULONG LDAPAPI LdapMapErrorToWin32(ULONG LdapError);
WINLDAPAPI int LDAPAPI LdapUnicodeToUTF8(LPCWSTR lpSrcStr, int cchSrc, LPSTR lpDestStr, int cchDest);
WINLDAPAPI int LDAPAPI LdapUTF8ToUnicode(LPCSTR lpSrcStr, int cchSrc, LPWSTR lpDestStr, int cchDest);

#ifdef __cplusplus
}
#endif

#endif /* _WINLDAP_ */
#endif /* AKARI_WCE_WINLDAP_H */
