/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IPRTRMIB_H
#define WCE_IPRTRMIB_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMIB_IFNUMBER { DWORD dwValue; } MIB_IFNUMBER, *PMIB_IFNUMBER, *LPMIB_IFNUMBER;
typedef struct tagMIBICMPSTATS { DWORD dwMsgs; DWORD dwErrors; DWORD dwDestUnreachs; DWORD dwTimeExcds; DWORD dwParmProbs; DWORD dwSrcQuenchs; DWORD dwRedirects; DWORD dwEchos; DWORD dwEchoReps; DWORD dwTimestamps; DWORD dwTimestampReps; DWORD dwAddrMasks; DWORD dwAddrMaskReps; } MIBICMPSTATS, *PMIBICMPSTATS, *LPMIBICMPSTATS;
typedef struct tagMIBICMPINFO { MIBICMPSTATS icmpInStats; MIBICMPSTATS icmpOutStats; } MIBICMPINFO, *PMIBICMPINFO, *LPMIBICMPINFO;
typedef struct tagMIBICMPSTATS_EX { DWORD dwMsgs; DWORD dwErrors; DWORD rgdwTypeCount[256]; } MIBICMPSTATS_EX, *PMIBICMPSTATS_EX, *LPMIBICMPSTATS_EX;
typedef struct tagMIB_UDPROW { DWORD dwLocalAddr; DWORD dwLocalPort; } MIB_UDPROW, *PMIB_UDPROW, *LPMIB_UDPROW;
typedef struct tagMIB_IPADDRROW { DWORD dwAddr; DWORD dwIndex; DWORD dwMask; DWORD dwBCastAddr; DWORD dwReasmSize; unsigned short unused1; unsigned short wType; } MIB_IPADDRROW, *PMIB_IPADDRROW, *LPMIB_IPADDRROW;
typedef struct tagMIB_IPFORWARDNUMBER { DWORD dwValue; } MIB_IPFORWARDNUMBER, *PMIB_IPFORWARDNUMBER, *LPMIB_IPFORWARDNUMBER;
typedef struct tagMIB_IPMCAST_OIF { DWORD dwOutIfIndex; DWORD dwNextHopAddr; DWORD dwReserved; DWORD dwReserved1; } MIB_IPMCAST_OIF, *PMIB_IPMCAST_OIF, *LPMIB_IPMCAST_OIF;
typedef struct tagMIB_IPMCAST_OIF_STATS { DWORD dwOutIfIndex; DWORD dwNextHopAddr; DWORD dwDialContext; ULONG ulTtlTooLow; ULONG ulFragNeeded; ULONG ulOutPackets; ULONG ulOutDiscards; } MIB_IPMCAST_OIF_STATS, *PMIB_IPMCAST_OIF_STATS, *LPMIB_IPMCAST_OIF_STATS;
typedef struct tagMIB_IPMCAST_GLOBAL { DWORD dwEnable; } MIB_IPMCAST_GLOBAL, *PMIB_IPMCAST_GLOBAL, *LPMIB_IPMCAST_GLOBAL;
typedef struct tagMIB_IPMCAST_IF_ENTRY { DWORD dwIfIndex; DWORD dwTtl; DWORD dwProtocol; DWORD dwRateLimit; ULONG ulInMcastOctets; ULONG ulOutMcastOctets; } MIB_IPMCAST_IF_ENTRY, *PMIB_IPMCAST_IF_ENTRY, *LPMIB_IPMCAST_IF_ENTRY;
typedef struct tagMIB_IPMCAST_BOUNDARY { DWORD dwIfIndex; DWORD dwGroupAddress; DWORD dwGroupMask; DWORD dwStatus; } MIB_IPMCAST_BOUNDARY, *PMIB_IPMCAST_BOUNDARY, *LPMIB_IPMCAST_BOUNDARY;
typedef struct tagMIB_BOUNDARYROW { DWORD dwGroupAddress; DWORD dwGroupMask; } MIB_BOUNDARYROW, *PMIB_BOUNDARYROW, *LPMIB_BOUNDARYROW;
typedef struct tagMIB_MCAST_LIMIT_ROW { DWORD dwTtl; DWORD dwRateLimit; } MIB_MCAST_LIMIT_ROW, *PMIB_MCAST_LIMIT_ROW, *LPMIB_MCAST_LIMIT_ROW;
typedef struct tagMIB_BEST_IF { DWORD dwDestAddr; DWORD dwIfIndex; } MIB_BEST_IF, *PMIB_BEST_IF, *LPMIB_BEST_IF;
typedef struct tagMIB_PROXYARP { DWORD dwAddress; DWORD dwMask; DWORD dwIfIndex; } MIB_PROXYARP, *PMIB_PROXYARP, *LPMIB_PROXYARP;
typedef struct tagMIB_IFSTATUS { DWORD dwIfIndex; DWORD dwAdminStatus; DWORD dwOperationalStatus; BOOL bMHbeatActive; BOOL bMHbeatAlive; } MIB_IFSTATUS, *PMIB_IFSTATUS, *LPMIB_IFSTATUS;
typedef struct tagMIB_ROUTESTATE { BOOL bRoutesSetToStack; } MIB_ROUTESTATE, *PMIB_ROUTESTATE, *LPMIB_ROUTESTATE;


#ifdef __cplusplus
}
#endif
#endif

