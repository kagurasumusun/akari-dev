/* Wzcsapi.h -- Wireless Zero Configuration (WZC) API.
 *
 * Source pages: Automatic Configuration Reference rows printing
 * "Header: Wzcsapi.h" (15 pages; 8 functions print
 * "Link Library: Wzcsapi.lib" -- def/wzcsapi-doc.def).
 *
 * INTF_ENTRY embeds RAW_DATA and WZC_WLAN_CONFIG embeds
 * WZCCTL_MAX_WEPK_MATERIAL + RAW_DATA; none of the three is
 * printed by any CE page, so those structs (and the config list
 * embedding WZC_WLAN_CONFIG) are recorded verbatim and closed
 * opaquely.  Every function takes them through pointers, so all
 * eight are declared.  See docs/inventory.md M78c.
 */

#ifndef AKARI_WZCSAPI_H
#define AKARI_WZCSAPI_H

#include "Windef.h"    /* DWORD, LPWSTR, ULONG, BOOL, BYTE */

/* "INTF_KEY_ENTRY": print `typedef struct{ LPWSTR wszGuid;}
 * INTF_KEY_ENTRY, *PINTF_KEY_ENTRY;` */
/* aa448307: members/signature verified against this page (type-cite) */
typedef struct _INTF_KEY_ENTRY {
    LPWSTR wszGuid;
} INTF_KEY_ENTRY, *PINTF_KEY_ENTRY;

/* "INTFS_KEY_TABLE": print `typedef struct{ DWORD dwNumIntfs;
 * PINTF_KEY_ENTRY pIntfs;} INTFS_KEY_TABLE, *PINTFS_KEY_TABLE;` */
/* aa448305: members/signature verified against this page (type-cite) */
typedef struct _INTFS_KEY_TABLE {
    DWORD           dwNumIntfs;
    PINTF_KEY_ENTRY pIntfs;
} INTFS_KEY_TABLE, *PINTFS_KEY_TABLE;

/* "WZC_CONTEXT": print `typedef struct _wzc_context_t{ DWORD
 * dwFlags; DWORD tmTr; DWORD tmTc; DWORD tmTp; DWORD tmTf; DWORD
 * tmTd; } WZC_CONTEXT, *PWZC_CONTEXT;` (tag as printed). */
/* aa448336: members/signature verified against this page (type-cite) */
typedef struct _wzc_context_t {
    DWORD dwFlags;
    DWORD tmTr;
    DWORD tmTc;
    DWORD tmTp;
    DWORD tmTf;
    DWORD tmTd;
} WZC_CONTEXT, *PWZC_CONTEXT;

/* "WZC_EAPOL_PARAMS": print `typedef struct _WZC_EAPOL_PARAMS{
 * BOOL bEnable8021x; DWORD dwEapFlags; DWORD dwEapType; DWORD
 * dwAuthDataLen; BYTE *pbAuthData;}WZC_EAPOL_PARAMS,
 * *PWZC_EAPOL_PARAMS;` */
/* aa448337: members/signature verified against this page (type-cite) */
typedef struct _WZC_EAPOL_PARAMS {
    BOOL  bEnable8021x;
    DWORD dwEapFlags;
    DWORD dwEapType;
    DWORD dwAuthDataLen;
    BYTE *pbAuthData;
} WZC_EAPOL_PARAMS, *PWZC_EAPOL_PARAMS;

/* --- Held WZC structures (unpublished members; prints recorded). */
/* "INTF_ENTRY": print `typedef struct { LPWSTR wszGuid; LPWSTR
 * wszDescr; ULONG ulMediaState; ULONG ulMediaType; ULONG
 * ulPhysicalMediaType; INT nInfraMode; INT nAuthMode; INT
 * nWepStatus; DWORD dwCtlFlags; DWORD dwCapabilities; RAW_DATA
 * rdSSID; RAW_DATA rdBSSID; RAW_DATA rdBSSIDList; RAW_DATA
 * rdStSSIDList; BOOL bInitialized;} INTF_ENTRY, *PINTF_ENTRY;`
 * -- RAW_DATA is not printed by any CE page; held. */
typedef struct _INTF_ENTRY INTF_ENTRY, *PINTF_ENTRY;

/* "WZC_WLAN_CONFIG": print embeds RAW_DATA and
 * `UCHAR KeyMaterial[WZCCTL_MAX_WEPK_MATERIAL]` -- neither is
 * printed by any CE page; held (the 802.11 members are Ntddndis.h
 * types). */
typedef struct _WZC_WLAN_CONFIG WZC_WLAN_CONFIG, *PWZC_WLAN_CONFIG;

/* "WZC_802_11_CONFIG_LIST": print `typedef struct{ ULONG
 * NumberOfItems; ULONG Index; WZC_WLAN_CONFIG Config[1];}
 * WZC_802_11_CONFIG_LIST, *PWZC_802_11_CONFIG_LIST;` -- embeds the
 * held WZC_WLAN_CONFIG; held. */
typedef struct _WZC_802_11_CONFIG_LIST WZC_802_11_CONFIG_LIST,
    *PWZC_802_11_CONFIG_LIST;

/* --- Functions (Wzcsapi.lib). --------------------------------- */
/* ms923684 "WZCDeleteIntfObj": `VOID WZCDeleteIntfObj(PINTF_ENTRYpIntf);` */
AKARI_CE_IMPORT void WZCDeleteIntfObj(PINTF_ENTRY pIntf)
                    AKARI_CE_NAME(WZCDeleteIntfObj);

/* ms923686 "WZCEnumInterfaces": `DWORD WZCEnumInterfaces(LPWSTRpSrvAddr,
 * PINTFS_KEY_TABLE pIntfs);` */
AKARI_CE_IMPORT DWORD WZCEnumInterfaces(LPWSTR pSrvAddr,
                    PINTFS_KEY_TABLE pIntfs)
                    AKARI_CE_NAME(WZCEnumInterfaces);

/* ms923687 "WZCPassword2Key": `VOID WZCPassword2Key(PWZC_WLAN_CONFIG
 * pwzcConfig,LPCSTR cszPassword);` */
AKARI_CE_IMPORT void WZCPassword2Key(PWZC_WLAN_CONFIG pwzcConfig,
                    LPCSTR cszPassword) AKARI_CE_NAME(WZCPassword2Key);

/* ms923688 "WZCQueryContext": `DWORD WZCQueryContext(LPWSTRpSrvAddr,
 * DWORD dwInFlags,PWZC_CONTEXT pContext,LPDWORD pdwOutFlags);` */
AKARI_CE_IMPORT DWORD WZCQueryContext(LPWSTR pSrvAddr,
                    DWORD dwInFlags, PWZC_CONTEXT pContext,
                    LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCQueryContext);

/* ms923689 "WZCQueryInterface": `DWORD WZCQueryInterface(LPWSTRpSrvAddr,
 * DWORD dwInFlags,PINTF_ENTRY pIntf,LPDWORD pdwOutFlags);` */
AKARI_CE_IMPORT DWORD WZCQueryInterface(LPWSTR pSrvAddr,
                    DWORD dwInFlags, PINTF_ENTRY pIntf,
                    LPDWORD pdwOutFlags)
                    AKARI_CE_NAME(WZCQueryInterface);

/* ms923690 "WZCRefreshInterface": `DWORD WZCRefreshInterface(LPWSTRpSrvAddr,
 * DWORD dwInFlags,PINTF_ENTRY pIntf,LPDWORD pdwOutFlags);` */
AKARI_CE_IMPORT DWORD WZCRefreshInterface(LPWSTR pSrvAddr,
                    DWORD dwInFlags, PINTF_ENTRY pIntf,
                    LPDWORD pdwOutFlags)
                    AKARI_CE_NAME(WZCRefreshInterface);

/* ms923691 "WZCSetContext": `DWORD WZCSetContext(LPWSTRpSrvAddr,
 * DWORD dwInFlags,PWZC_CONTEXT pContext,LPDWORD pdwOutFlags);` */
AKARI_CE_IMPORT DWORD WZCSetContext(LPWSTR pSrvAddr,
                    DWORD dwInFlags, PWZC_CONTEXT pContext,
                    LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCSetContext);

/* ms923692 "WZCSetInterface": `DWORD WZCSetInterface(LPWSTRpSrvAddr,
 * DWORD dwInFlags,PINTF_ENTRY pIntf, LPDWORD pdwOutFlags);` */
AKARI_CE_IMPORT DWORD WZCSetInterface(LPWSTR pSrvAddr,
                    DWORD dwInFlags, PINTF_ENTRY pIntf,
                    LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCSetInterface);



/* INTF_ENTRY_EX: ee486847 prints the full struct, but five of its
 * members are RAW_DATA and no corpus page defines RAW_DATA (checked
 * 2026-09-18); kept opaque so the Ex-function pointer parameters can
 * be declared without inventing RAW_DATA.  Full print recorded at
 * ee486847. */
typedef struct _INTF_ENTRY_EX INTF_ENTRY_EX, *PINTF_ENTRY_EX;

/* ee481708 WZCDeleteIntfObjEx: print `VOID WZCDeleteIntfObjEx(
 * PINTF_ENTRY_EX pIntf );` (Link Library: Wzcsapi.lib) */
AKARI_CE_IMPORT void WZCDeleteIntfObjEx(PINTF_ENTRY_EX pIntf) AKARI_CE_NAME(WZCDeleteIntfObjEx);

/* ee483427 WZCQueryInterfaceEx: print `DWORD WZCQueryInterfaceEx(
 * LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx,
 * LPDWORD pdwOutFlags );` (Link Library: Wzcsapi.lib) */
AKARI_CE_IMPORT DWORD WZCQueryInterfaceEx(LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx, LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCQueryInterfaceEx);

/* ee482278 WZCRefreshInterfaceEx: print `DWORD WZCRefreshInterfaceEx(
 * LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx,
 * LPDWORD pdwOutFlags );` (Link Library: Wzcsapi.lib) */
AKARI_CE_IMPORT DWORD WZCRefreshInterfaceEx(LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx, LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCRefreshInterfaceEx);

/* ee481704 WZCSetInterfaceEx: print `DWORD WZCSetInterfaceEx(
 * LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx,
 * LPDWORD pdwOutFlags );` (Link Library: Wzcsapi.lib) */
AKARI_CE_IMPORT DWORD WZCSetInterfaceEx(LPWSTR pSrvAddr, DWORD dwInFlags, PINTF_ENTRY_EX pIntfEx, LPDWORD pdwOutFlags) AKARI_CE_NAME(WZCSetInterfaceEx);

/* WZCEnumEapExtensions HELD: EAP_EXTENSION_INFO has no corpus page
 * (checked 2026-09-18). */

#endif /* AKARI_WZCSAPI_H */
