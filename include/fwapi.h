/*
 * fwapi.h -- Windows CE Firewall for Windows CE.
 *
 * Part of the WinCE development API surface kit.  CE 6.0 only; fwapi.dll does
 * not exist in CE 4.2 or 5.0, so every declaration here is gated on
 * _WIN32_WCE >= 0x600.
 *
 * The rule record describes one filter: an address or prefix, a protocol, an
 * action, and the time window during which it applies.
 */
#ifndef AKARI_WCE_FWAPI_H
#define AKARI_WCE_FWAPI_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <winsock2.h>   /* struct in_addr, struct in6_addr */

#ifndef _FWAPI_
#define _FWAPI_

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WCE >= 0x600)

#ifndef FWAPI
#define FWAPI AKARI_DLLIMPORT
#endif

/* --------------------------------------------------------- handles */

typedef DWORD_PTR HRULE;

/* --------------------------------------------------------- actions */

typedef enum akari_FW_ACTIONS {
    FWA_BLOCK          = 0x01,
    FWA_ALLOW          = 0x02,
    FWA_ALLOW_RESPONSE = 0x03
} FW_ACTIONS;

typedef enum akari_FW_DIRECTIONS {
    FWD_INBOUND  = 0x08,
    FWD_OUTBOUND = 0x10
} FW_DIRECTIONS;

typedef enum akari_FW_DAYS {
    FWD_SUNDAY    = 0x01,
    FWD_MONDAY    = 0x02,
    FWD_TUESDAY   = 0x04,
    FWD_WEDNESDAY = 0x08,
    FWD_THURSDAY  = 0x10,
    FWD_FRIDAY    = 0x20,
    FWD_SATURDAY  = 0x40,
    FWD_WEEKDAY   = 0x3E,
    FWD_WEEKEND   = 0x41
} FW_DAYS;

/* Which fields of a rule the caller has filled in, and so which the resource
   manager should look at. */
typedef enum akari_FW_RULE_MASKS {
    FWM_PRIVATE_HOST = 0x0001,
    FWM_PUBLIC_HOST  = 0x0002,
    FWM_PORT         = 0x0004,
    FWM_TYPE         = 0x0008,
    FWM_CODE         = 0x0010,
    FWM_PROTOCOL     = 0x0020,
    FWM_ACTION       = 0x0040,
    FWM_HOURS        = 0x0080,
    FWM_DAY          = 0x0100,
    FWM_MONTH        = 0x0200,
    FWM_WEEKDAY      = 0x0400,
    FWM_DESCRIPTION  = 0x0800,
    FWM_PREFIX       = 0x1000,
    FWM_MASK         = 0x2000
} FW_RULE_MASKS;

typedef enum akari_FW_RULE_FLAGS {
    FWF_BLOCK    = FWA_BLOCK,
    FWF_ALLOW    = FWA_ALLOW,
    FWF_LOG      = 0x04,
    FWF_INBOUND  = FWD_INBOUND,
    FWF_OUTBOUND = FWD_OUTBOUND,
    FWF_DISABLED = 0x20
} FW_RULE_FLAGS;

/* An address in either family.  Family selects the union member. */
typedef struct akari_FW_IP_ADDRESS {
    USHORT Family;
    union {
        struct in6_addr AddressIPv6;
        struct in_addr  AddressIPv4;
    };
} FW_IP_ADDRESS, *PFW_IP_ADDRESS;

typedef struct akari_FIREWALL_RULE {
    DWORD         dwSize;
    HRULE         hRule;
    DWORD         dwFlags;
    DWORD         dwMask;
    LPWSTR        wszDescription;
    FW_IP_ADDRESS PrivateHost;
    FW_IP_ADDRESS PublicHost;
    union {
        UINT           PublicHostPrefixLength;
        struct in_addr PublicHostMask;
    };
    INT          Protocol;
    FW_ACTIONS   Action;
    WORD         wHourStart, wHourEnd;
    WORD         wDayOfWeek;
    WORD         wDay;
    WORD         wMonth;
    union {
        struct { USHORT PortMin; USHORT PortMax; };
        struct { UCHAR  Type;    UCHAR  Code;   };
    };
} FW_RULE, *PFW_RULE;

typedef struct akari_FIREWALL_LOG_ENTRY {
    FW_IP_ADDRESS PrivateHost;
    FW_IP_ADDRESS PublicHost;
    INT           Protocol;
    FW_ACTIONS    Action;
    WORD          wHour;
    WORD          wDayOfWeek;
    WORD          wDay;
    WORD          wMonth;
    USHORT        Port;
    UCHAR         Type;
    UCHAR         Code;
} FW_LOG_ENTRY, *PFW_LOG_ENTRY;

/* ------------------------------------------------------- prototypes */

FWAPI DWORD FirewallCreateRule(FW_RULE* pRule, BOOL bPersist);
FWAPI DWORD FirewallDeleteRule(HRULE hRule, BOOL bPersist);
FWAPI DWORD FirewallEnable(USHORT Family, BOOL bEnable, BOOL bPersist);
FWAPI DWORD FirewallEnableRule(HRULE hRule, BOOL bEnable, BOOL bPersist);
FWAPI DWORD FirewallGetRules(PFW_RULE pRules, DWORD *pcbSize, DWORD* pdwCount);
FWAPI VOID FirewallRefresh(void);
FWAPI DWORD FirewallSetInterface(LPCWSTR pszInterfaceName, BOOL bFirewalled, BOOL bPersist);
FWAPI BOOL IsFirewallEnabled(USHORT Family);
FWAPI BOOL IsInterfaceFirewalled(LPCWSTR pszInterfaceName);

#endif /* _WIN32_WCE >= 0x600 */

#ifdef __cplusplus
}
#endif

#endif /* _FWAPI_ */
#endif /* AKARI_WCE_FWAPI_H */
