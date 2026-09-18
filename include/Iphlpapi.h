/* Iphlpapi.h -- IP Helper API (Windows CE .NET 4.0+).
 *
 * Pages: tools/manifests/netgen.manifest (Networking - General);
 * Link Library rows print Iphlpapi.lib (def/iphlpapi-doc.def).
 * See docs/inventory.md M77a.
 */

#ifndef AKARI_IPHLPAPI_H
#define AKARI_IPHLPAPI_H

#include "Windef.h"    /* DWORD, ULONG, UINT, BOOL, PDWORD, PVOID */
#include "Winbase.h"   /* PHANDLE, LPOVERLAPPED, LPWSTR */
#include "Iptypes.h"     /* IP_ADAPTER_INFO, FIXED_INFO,
                          * IP_PER_ADAPTER_INFO, IP_ADAPTER_ADDRESSES */
#include "Iprtrmib.h"    /* MIB_* rows/tables */
#include "Ipexport.h"    /* IP_INTERFACE_INFO, IP_ADAPTER_INDEX_MAP,
                          * IP_UNIDIRECTIONAL_ADAPTER_ADDRESS */
#include "Winsock2.h"    /* struct sockaddr (GetBestInterfaceEx) */

/* --- Functions (Iphlpapi.lib -> def/iphlpapi-doc.def). ---------- */

/* ms887916 "CreateIpForwardEntry" */
AKARI_CE_IMPORT DWORD CreateIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(CreateIpForwardEntry);

/* aa450325 "DeleteIpForwardEntry" */
AKARI_CE_IMPORT DWORD DeleteIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(DeleteIpForwardEntry);

/* aa450922 "SetIpForwardEntry" */
/* twin-print: ee494909 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450922 lacks the print. */
AKARI_CE_IMPORT DWORD SetIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(SetIpForwardEntry);

/* ms887917 "CreateIpNetEntry" */
AKARI_CE_IMPORT DWORD CreateIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(CreateIpNetEntry);

/* aa450326 "DeleteIpNetEntry" */
AKARI_CE_IMPORT DWORD DeleteIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(DeleteIpNetEntry);

/* aa450924 "SetIpNetEntry" */
/* twin-print: ee493663 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450924 lacks the print. */
AKARI_CE_IMPORT DWORD SetIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(SetIpNetEntry);

/* ms887918 "CreateProxyArpEntry" */
AKARI_CE_IMPORT DWORD CreateProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex) AKARI_CE_NAME(CreateProxyArpEntry);

/* aa450327 "DeleteProxyArpEntry" */
AKARI_CE_IMPORT DWORD DeleteProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex) AKARI_CE_NAME(DeleteProxyArpEntry);

/* aa450382 "FlushIpNetTable" */
/* twin-print: ee493293 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450382 lacks the print. */
AKARI_CE_IMPORT DWORD FlushIpNetTable(DWORD dwIfIndex) AKARI_CE_NAME(FlushIpNetTable);

/* aa450394 "GetAdaptersInfo" */
/* twin-print: ee494906 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450394 lacks the print. */
AKARI_CE_IMPORT DWORD GetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen) AKARI_CE_NAME(GetAdaptersInfo);

/* aa450393 "GetAdaptersAddresses" */
AKARI_CE_IMPORT DWORD GetAdaptersAddresses(ULONG Family, DWORD Flags, PVOID Reserved,
                    PIP_ADAPTER_ADDRESSES pAdapterAddresses,
                    PULONG pOutBufLen) AKARI_CE_NAME(GetAdaptersAddresses);

/* aa450392 "GetAdapterIndex" */
/* twin-print: ee494496 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450392 lacks the print. */
AKARI_CE_IMPORT DWORD GetAdapterIndex(LPWSTR AdapterName, PULONG IfIndex) AKARI_CE_NAME(GetAdapterIndex);

/* aa450397 "GetBestInterfaceEx" (page spells it GetBestInterfaceEX) */
AKARI_CE_IMPORT DWORD GetBestInterfaceEx(struct sockaddr *pDestAddr, PDWORD pdwBestIfIndex) AKARI_CE_NAME(GetBestInterfaceEx);

/* aa450398 "GetBestRoute" */
/* twin-print: ee494119 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450398 lacks the print. */
AKARI_CE_IMPORT DWORD GetBestRoute(DWORD dwDestAddr, DWORD dwSourceAddr,
                    PMIB_IPFORWARDROW pBestRoute) AKARI_CE_NAME(GetBestRoute);

/* aa450401 "GetFriendlyIfIndex" */
/* twin-print: ee494694 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450401 lacks the print. */
AKARI_CE_IMPORT DWORD GetFriendlyIfIndex(DWORD IfIndex) AKARI_CE_NAME(GetFriendlyIfIndex);

/* aa450406 "GetIcmpStatistics" */
/* twin-print: ee494858 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450406 lacks the print. */
AKARI_CE_IMPORT DWORD GetIcmpStatistics(PMIB_ICMP pStats) AKARI_CE_NAME(GetIcmpStatistics);

/* aa450407 "GetIcmpStatisticsEx" */
/* twin-print: ms927389 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450407 lacks the print. */
AKARI_CE_IMPORT DWORD GetIcmpStatisticsEx(PMIB_ICMP pStats, DWORD dwFamily) AKARI_CE_NAME(GetIcmpStatisticsEx);

/* aa450408 "GetIfEntry" */
/* twin-print: ee493262 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450408 lacks the print. */
AKARI_CE_IMPORT DWORD GetIfEntry(PMIB_IFROW pIfRow) AKARI_CE_NAME(GetIfEntry);

/* aa450409 "GetIfTable" */
/* twin-print: ee494305 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450409 lacks the print. */
AKARI_CE_IMPORT DWORD GetIfTable(PMIB_IFTABLE pIfTable, PULONG pdwSize, BOOL bOrder) AKARI_CE_NAME(GetIfTable);

/* aa450410 "GetInterfaceInfo" */
/* twin-print: ee493639 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450410 lacks the print. */
AKARI_CE_IMPORT DWORD GetInterfaceInfo(PIP_INTERFACE_INFO pIfTable, PULONG dwOutBufLen) AKARI_CE_NAME(GetInterfaceInfo);

/* aa450411 "GetIpAddrTable" */
/* twin-print: ee493850 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450411 lacks the print. */
AKARI_CE_IMPORT DWORD GetIpAddrTable(PMIB_IPADDRTABLE pIpAddrTable, PULONG pdwSize,
                    BOOL bOrder) AKARI_CE_NAME(GetIpAddrTable);

/* aa450412 "GetIpForwardTable" */
/* twin-print: ee493868 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450412 lacks the print. */
AKARI_CE_IMPORT DWORD GetIpForwardTable(PMIB_IPFORWARDTABLE pIpForwardTable,
                    PULONG pdwSize, BOOL bOrder) AKARI_CE_NAME(GetIpForwardTable);

/* aa450413 "GetIpNetTable" */
/* twin-print: ee494695 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450413 lacks the print. */
AKARI_CE_IMPORT DWORD GetIpNetTable(PMIB_IPNETTABLE pIpNetTable, PULONG pdwSize,
                    BOOL bOrder) AKARI_CE_NAME(GetIpNetTable);

/* aa450414 "GetIpStatistics" */
AKARI_CE_IMPORT DWORD GetIpStatistics(PMIB_IPSTATS pStats) AKARI_CE_NAME(GetIpStatistics);

/* aa450415 "GetIpStatisticsEx" */
AKARI_CE_IMPORT DWORD GetIpStatisticsEx(PMIB_IPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetIpStatisticsEx);

/* aa450417 "GetNetworkParams" */
/* twin-print: ee494470 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450417 lacks the print. */
AKARI_CE_IMPORT DWORD GetNetworkParams(FIXED_INFO *pFixedInfo, PULONG pOutBufLen) AKARI_CE_NAME(GetNetworkParams);

/* aa450418 "GetNumberOfInterfaces" */
/* twin-print: ee494841 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450418 lacks the print. */
AKARI_CE_IMPORT DWORD GetNumberOfInterfaces(PDWORD pdwNumIf) AKARI_CE_NAME(GetNumberOfInterfaces);

/* aa450421 "GetPerAdapterInfo" */
/* twin-print: ee495165 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450421 lacks the print. */
AKARI_CE_IMPORT DWORD GetPerAdapterInfo(ULONG IfIndex,
                    PIP_PER_ADAPTER_INFO pPerAdapterInfo,
                    PULONG pOutBufLen) AKARI_CE_NAME(GetPerAdapterInfo);

/* ms890306 "GetTcpStatistics" */
/* twin-print: ee493828 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890306 lacks the print. */
AKARI_CE_IMPORT DWORD GetTcpStatistics(PMIB_TCPSTATS pStats) AKARI_CE_NAME(GetTcpStatistics);

/* ms890307 "GetTcpStatisticsEx" */
/* twin-print: ms927394 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890307 lacks the print. */
AKARI_CE_IMPORT DWORD GetTcpStatisticsEx(PMIB_TCPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetTcpStatisticsEx);

/* ms890308 "GetTcpTable" */
/* twin-print: ee493852 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890308 lacks the print. */
AKARI_CE_IMPORT DWORD GetTcpTable(PMIB_TCPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder) AKARI_CE_NAME(GetTcpTable);

/* ms890309 "GetUdpStatistics" */
/* twin-print: ee494233 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890309 lacks the print. */
AKARI_CE_IMPORT DWORD GetUdpStatistics(PMIB_UDPSTATS pStats) AKARI_CE_NAME(GetUdpStatistics);

/* ms890310 "GetUdpStatisticsEx" */
/* twin-print: ms927396 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890310 lacks the print. */
AKARI_CE_IMPORT DWORD GetUdpStatisticsEx(PMIB_UDPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetUdpStatisticsEx);

/* ms890311 "GetUdpTable" */
/* twin-print: ee493220 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890311 lacks the print. */
AKARI_CE_IMPORT DWORD GetUdpTable(PMIB_UDPTABLE pUdpTable, PDWORD pdwSize, BOOL bOrder) AKARI_CE_NAME(GetUdpTable);

/* ms890312 "GetUniDirectionalAdapterInfo" */
/* twin-print: ee493427 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms890312 lacks the print. */
AKARI_CE_IMPORT DWORD GetUniDirectionalAdapterInfo(PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo,
                    PULONG dwOutBufLen) AKARI_CE_NAME(GetUniDirectionalAdapterInfo);

/* aa450426 "IpReleaseAddress" */
/* twin-print: ee494303 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450426 lacks the print. */
AKARI_CE_IMPORT DWORD IpReleaseAddress(PIP_ADAPTER_INDEX_MAP Adapter) AKARI_CE_NAME(IpReleaseAddress);

/* aa450427 "IpRenewAddress" */
/* twin-print: ee493830 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450427 lacks the print. */
AKARI_CE_IMPORT DWORD IpRenewAddress(PIP_ADAPTER_INDEX_MAP Adapter) AKARI_CE_NAME(IpRenewAddress);

/* ms895712 "NotifyAddrChange" */
AKARI_CE_IMPORT DWORD NotifyAddrChange(PHANDLE Handle, LPOVERLAPPED overlapped) AKARI_CE_NAME(NotifyAddrChange);

/* ms895720 "NotifyRouteChange" */
AKARI_CE_IMPORT DWORD NotifyRouteChange(PHANDLE Handle, LPOVERLAPPED overlapped) AKARI_CE_NAME(NotifyRouteChange);

/* aa450920 "SetIfEntry" */
AKARI_CE_IMPORT DWORD SetIfEntry(PMIB_IFROW pIfRow) AKARI_CE_NAME(SetIfEntry);

/* aa450929 "SetIpStatistics" */
/* twin-print: ee494885 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450929 lacks the print. */
AKARI_CE_IMPORT DWORD SetIpStatistics(PMIB_IPSTATS pIpStats) AKARI_CE_NAME(SetIpStatistics);

/* aa450931 "SetIpTTL" */
/* twin-print: ee494316 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450931 lacks the print. */
AKARI_CE_IMPORT DWORD SetIpTTL(UINT nTTL) AKARI_CE_NAME(SetIpTTL);

/* aa450937 "SetTcpEntry" */
/* twin-print: ee494687 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page aa450937 lacks the print. */
AKARI_CE_IMPORT DWORD SetTcpEntry(PMIB_TCPROW pTcpRow) AKARI_CE_NAME(SetTcpEntry);

/* --- Held (IPAddr / IPMask scalar typedefs unpublished). ---------
 * Recorded verbatim; the IPAddr and IPMask typedefs are printed
 * by these signatures but not published on any CE page:
 *   aa450280 AddIPAddress: `DWORD AddIPAddress(IPAddr Address,
 *     IPMask IpMask,DWORD IfIndex,PULONG NTEContext,
 *     PULONG NTEInstance);`
 *   aa450884 SendARP: `DWORD SendARP(IPAddr DestIP,IPAddr SrcIP,
 *     PULONG pMacAddr,PULONG PhyAddrLen );`
 *   aa450396 GetBestInterface: `DWORDGetBestInterface(IPAddrdwDestAddr,
 *     PDWORDpdwBestIfIndex);` (use GetBestInterfaceEx instead)
 *   aa450422 GetRTTAndHopCount: `BOOLGetRTTAndHopCount(IPAddrDestIpAddress,
 *     PULONGHopCount, ULONGMaxHops, PULONG RTT);` */

/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms887920 DeleteIPAddress: print `DWORD DeleteIPAddress(ULONGNTEContext);` -- recorded verbatim (no compiled prototype) */

/* M132: documented app-layer names this tree did not declare (page-cited). */

/* ms887920 DeleteIPAddress: print `DWORD DeleteIPAddress(ULONGNTEContext);`
 * (Windows CE 3.0 and later.; Link Library: Iphlpapi.lib) */
AKARI_CE_IMPORT DWORD DeleteIPAddress(ULONG NTEContext) AKARI_CE_NAME(DeleteIPAddress);

#endif /* AKARI_IPHLPAPI_H */
