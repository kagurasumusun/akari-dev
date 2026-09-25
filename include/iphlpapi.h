/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IPHLPAPI_H
#define WCE_IPHLPAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT DWORD WINAPI GetNumberOfInterfaces(OUT PDWORD pdwNumIf) WCE_LINK(GetNumberOfInterfaces);
WCE_IMPORT DWORD WINAPI GetIfEntry(IN OUT PMIB_IFROW pIfRow) WCE_LINK(GetIfEntry);
WCE_IMPORT DWORD WINAPI GetIfTable(OUT PMIB_IFTABLE pIfTable, IN OUT PULONG pdwSize, IN BOOL bOrder) WCE_LINK(GetIfTable);
WCE_IMPORT DWORD WINAPI GetIpAddrTable(OUT PMIB_IPADDRTABLE pIpAddrTable, IN OUT PULONG pdwSize, IN BOOL bOrder) WCE_LINK(GetIpAddrTable);
WCE_IMPORT DWORD WINAPI GetIpNetTable(OUT PMIB_IPNETTABLE pIpNetTable, IN OUT PULONG pdwSize, IN BOOL bOrder) WCE_LINK(GetIpNetTable);
WCE_IMPORT DWORD WINAPI GetIpForwardTable(OUT PMIB_IPFORWARDTABLE pIpForwardTable, IN OUT PULONG pdwSize, IN BOOL bOrder) WCE_LINK(GetIpForwardTable);
WCE_IMPORT DWORD WINAPI GetTcpTable(OUT PMIB_TCPTABLE pTcpTable, IN OUT PDWORD pdwSize, IN BOOL bOrder) WCE_LINK(GetTcpTable);
WCE_IMPORT DWORD WINAPI GetUdpTable(OUT PMIB_UDPTABLE pUdpTable, IN OUT PDWORD pdwSize, IN BOOL bOrder) WCE_LINK(GetUdpTable);
WCE_IMPORT DWORD WINAPI GetIpStatistics(OUT PMIB_IPSTATS pStats) WCE_LINK(GetIpStatistics);
WCE_IMPORT DWORD WINAPI GetIpStatisticsEx(OUT PMIB_IPSTATS pStats, IN DWORD dwFamily) WCE_LINK(GetIpStatisticsEx);
WCE_IMPORT DWORD WINAPI GetIcmpStatistics(OUT PMIB_ICMP pStats) WCE_LINK(GetIcmpStatistics);
WCE_IMPORT DWORD WINAPI GetIcmpStatisticsEx(OUT PMIB_ICMP_EX pStats, IN DWORD dwFamily) WCE_LINK(GetIcmpStatisticsEx);
WCE_IMPORT DWORD WINAPI GetTcpStatistics(OUT PMIB_TCPSTATS pStats) WCE_LINK(GetTcpStatistics);
WCE_IMPORT DWORD WINAPI GetTcpStatisticsEx(OUT PMIB_TCPSTATS pStats, IN DWORD dwFamily) WCE_LINK(GetTcpStatisticsEx);
WCE_IMPORT DWORD WINAPI GetUdpStatistics(OUT PMIB_UDPSTATS pStats) WCE_LINK(GetUdpStatistics);
WCE_IMPORT DWORD WINAPI GetUdpStatisticsEx(OUT PMIB_UDPSTATS pStats, IN DWORD dwFamily) WCE_LINK(GetUdpStatisticsEx);
WCE_IMPORT DWORD WINAPI SetIfEntry(IN PMIB_IFROW pIfRow) WCE_LINK(SetIfEntry);
WCE_IMPORT DWORD WINAPI CreateIpForwardEntry(IN PMIB_IPFORWARDROW pRoute) WCE_LINK(CreateIpForwardEntry);
WCE_IMPORT DWORD WINAPI SetIpForwardEntry(IN PMIB_IPFORWARDROW pRoute) WCE_LINK(SetIpForwardEntry);
WCE_IMPORT DWORD WINAPI DeleteIpForwardEntry(IN PMIB_IPFORWARDROW pRoute) WCE_LINK(DeleteIpForwardEntry);
WCE_IMPORT DWORD WINAPI SetIpStatistics(IN PMIB_IPSTATS pIpStats) WCE_LINK(SetIpStatistics);
WCE_IMPORT DWORD WINAPI SetIpTTL(UINT nTTL) WCE_LINK(SetIpTTL);
WCE_IMPORT DWORD WINAPI CreateIpNetEntry(IN PMIB_IPNETROW pArpEntry) WCE_LINK(CreateIpNetEntry);
WCE_IMPORT DWORD WINAPI SetIpNetEntry(IN PMIB_IPNETROW pArpEntry) WCE_LINK(SetIpNetEntry);
WCE_IMPORT DWORD WINAPI DeleteIpNetEntry(IN PMIB_IPNETROW pArpEntry) WCE_LINK(DeleteIpNetEntry);
WCE_IMPORT DWORD WINAPI FlushIpNetTable(IN DWORD dwIfIndex) WCE_LINK(FlushIpNetTable);
WCE_IMPORT DWORD WINAPI CreateProxyArpEntry(IN DWORD dwAddress, IN DWORD dwMask, IN DWORD dwIfIndex) WCE_LINK(CreateProxyArpEntry);
WCE_IMPORT DWORD WINAPI DeleteProxyArpEntry(IN DWORD dwAddress, IN DWORD dwMask, IN DWORD dwIfIndex) WCE_LINK(DeleteProxyArpEntry);
WCE_IMPORT DWORD WINAPI SetTcpEntry(IN PMIB_TCPROW pTcpRow) WCE_LINK(SetTcpEntry);
WCE_IMPORT DWORD WINAPI GetInterfaceInfo(IN PIP_INTERFACE_INFO pIfTable, OUT PULONG dwOutBufLen) WCE_LINK(GetInterfaceInfo);
WCE_IMPORT DWORD WINAPI GetUniDirectionalAdapterInfo(OUT PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo, OUT PULONG dwOutBufLen) WCE_LINK(GetUniDirectionalAdapterInfo);
WCE_IMPORT DWORD WINAPI GetBestRoute(IN DWORD dwDestAddr, IN DWORD dwSourceAddr, OPTIONAL OUT PMIB_IPFORWARDROW pBestRoute) WCE_LINK(GetBestRoute);
WCE_IMPORT DWORD WINAPI NotifyAddrChange(OUT PHANDLE Handle, IN LPOVERLAPPED overlapped) WCE_LINK(NotifyAddrChange);
WCE_IMPORT DWORD WINAPI NotifyRouteChange(OUT PHANDLE Handle, IN LPOVERLAPPED overlapped) WCE_LINK(NotifyRouteChange);
WCE_IMPORT DWORD WINAPI GetAdapterIndex(IN LPWSTR AdapterName, OUT PULONG IfIndex) WCE_LINK(GetAdapterIndex);
WCE_IMPORT DWORD WINAPI DeleteIPAddress(ULONG NTEContext) WCE_LINK(DeleteIPAddress);
WCE_IMPORT DWORD WINAPI GetNetworkParams(PFIXED_INFO pFixedInfo, PULONG pOutBufLen) WCE_LINK(GetNetworkParams);
WCE_IMPORT DWORD WINAPI GetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen) WCE_LINK(GetAdaptersInfo);
WCE_IMPORT DWORD WINAPI GetAdaptersAddresses(IN ULONG Family, IN DWORD Flags, IN PVOID Reserved, OUT PIP_ADAPTER_ADDRESSES pAdapterAddresses, IN OUT PULONG pOutBufLen) WCE_LINK(GetAdaptersAddresses);
WCE_IMPORT DWORD WINAPI GetPerAdapterInfo(ULONG IfIndex, PIP_PER_ADAPTER_INFO pPerAdapterInfo, PULONG pOutBufLen) WCE_LINK(GetPerAdapterInfo);
WCE_IMPORT DWORD WINAPI IpReleaseAddress(PIP_ADAPTER_INDEX_MAP AdapterInfo) WCE_LINK(IpReleaseAddress);
WCE_IMPORT DWORD WINAPI IpRenewAddress(PIP_ADAPTER_INDEX_MAP AdapterInfo) WCE_LINK(IpRenewAddress);
WCE_IMPORT DWORD WINAPI GetFriendlyIfIndex(DWORD IfIndex) WCE_LINK(GetFriendlyIfIndex);
WCE_IMPORT DWORD WINAPI EnableRouter(HANDLE* pHandle, OVERLAPPED* pOverlapped) WCE_LINK(EnableRouter);
WCE_IMPORT DWORD WINAPI UnenableRouter(OVERLAPPED* pOverlapped, LPDWORD lpdwEnableCount OPTIONAL) WCE_LINK(UnenableRouter);
WCE_IMPORT DWORD WINAPI DisableMediaSense(HANDLE *pHandle, OVERLAPPED *pOverLapped) WCE_LINK(DisableMediaSense);
WCE_IMPORT DWORD WINAPI RestoreMediaSense(OVERLAPPED* pOverlapped, LPDWORD lpdwEnableCount OPTIONAL) WCE_LINK(RestoreMediaSense);

#ifdef __cplusplus
}
#endif
#endif

