/* IP Helper. Original text. Exported by iphlpapi.dll.
 *
 * The table structures are variable length: the caller sizes a buffer, passes it
 * in, and reads the resulting row count from the dwNumEntries field. Passing a
 * null table with a zero length returns ERROR_INSUFFICIENT_BUFFER together with
 * the size that is needed.
 */
#ifndef AKARI_WCE_IPHLPAPI_H
#define AKARI_WCE_IPHLPAPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winsock2.h"

#define MAX_HOSTNAME_LEN              128
#define MAX_DOMAIN_NAME_LEN           128
#define MAX_SCOPE_ID_LEN              256
#define MAX_ADAPTER_NAME_LENGTH       256
#define MAX_ADAPTER_NAME              128
#define MAX_ADAPTER_DESCRIPTION_LENGTH 128
#define MAX_ADAPTER_ADDRESS_LENGTH    8

#define MAXLEN_PHYSADDR               8
#define MAXLEN_IFDESC                 256
#define MAX_INTERFACE_NAME_LEN        256

#define IF_TYPE_OTHER                 1
#define IF_TYPE_ETHERNET_CSMACD       6
#define IF_TYPE_PPP                   23
#define IF_TYPE_SOFTWARE_LOOPBACK     24
#define IF_TYPE_IEEE80211             71

#define MIB_IF_TYPE_OTHER             1
#define MIB_IF_TYPE_ETHERNET          6
#define MIB_IF_TYPE_TOKENRING         9
#define MIB_IF_TYPE_FDDI              15
#define MIB_IF_TYPE_PPP               23
#define MIB_IF_TYPE_LOOPBACK          24
#define MIB_IF_TYPE_SLIP              28

#define MIB_TCP_STATE_CLOSED          1
#define MIB_TCP_STATE_LISTEN          2
#define MIB_TCP_STATE_SYN_SENT        3
#define MIB_TCP_STATE_SYN_RCVD        4
#define MIB_TCP_STATE_ESTAB           5
#define MIB_TCP_STATE_FIN_WAIT1       6
#define MIB_TCP_STATE_FIN_WAIT2       7
#define MIB_TCP_STATE_CLOSE_WAIT      8
#define MIB_TCP_STATE_CLOSING         9
#define MIB_TCP_STATE_LAST_ACK        10
#define MIB_TCP_STATE_TIME_WAIT       11
#define MIB_TCP_STATE_DELETE_TCB      12


#define IP_STATUS_BASE                11000
#define IP_SUCCESS                    0
#define IP_DEST_NET_UNREACHABLE       (IP_STATUS_BASE + 2)
#define IP_DEST_HOST_UNREACHABLE      (IP_STATUS_BASE + 3)
#define IP_REQ_TIMED_OUT              (IP_STATUS_BASE + 10)
#define IP_BAD_DESTINATION            (IP_STATUS_BASE + 18)

#define IP_FLAG_DF                    0x02
#define IP_OPT_EOL                    0
#define IP_OPT_NOP                    1
#define IP_OPT_SECURITY               130
#define IP_OPT_LSRR                   131
#define IP_OPT_SSRR                   137
#define IP_OPT_RR                     7
#define IP_OPT_TS                     68
#define IP_OPT_SID                    136
#define IP_OPT_ROUTER_ALERT           148
#define MAX_OPT_SIZE                  40

#define GAA_FLAG_SKIP_UNICAST         0x0001
#define GAA_FLAG_SKIP_ANYCAST         0x0002
#define GAA_FLAG_SKIP_MULTICAST       0x0004
#define GAA_FLAG_SKIP_DNS_SERVER      0x0008

typedef struct akari_IP_ADDRESS_STRING {
    CHAR String[16];
} IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;

typedef struct akari_IP_ADDR_STRING {
    struct akari_IP_ADDR_STRING *Next;
    IP_ADDRESS_STRING IpAddress;
    IP_MASK_STRING IpMask;
    DWORD Context;
} IP_ADDR_STRING, *PIP_ADDR_STRING;

typedef struct akari_IP_ADAPTER_INFO {
    struct akari_IP_ADAPTER_INFO *Next;
    DWORD ComboIndex;
    CHAR AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
    CHAR Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
    UINT AddressLength;
    BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
    DWORD Index;
    UINT Type;
    UINT DhcpEnabled;
    PIP_ADDR_STRING CurrentIpAddress;
    IP_ADDR_STRING IpAddressList;
    IP_ADDR_STRING GatewayList;
    IP_ADDR_STRING DhcpServer;
    BOOL HaveWins;
    IP_ADDR_STRING PrimaryWinsServer;
    IP_ADDR_STRING SecondaryWinsServer;
    /* time_t is 32 bits on every Windows CE CPU. */
    DWORD LeaseObtained;
    DWORD LeaseExpires;
} IP_ADAPTER_INFO, *PIP_ADAPTER_INFO;

typedef struct akari_IP_PER_ADAPTER_INFO {
    UINT AutoconfigEnabled;
    UINT AutoconfigActive;
    PIP_ADDR_STRING CurrentDnsServer;
    IP_ADDR_STRING DnsServerList;
} IP_PER_ADAPTER_INFO, *PIP_PER_ADAPTER_INFO;

typedef struct akari_FIXED_INFO {
    CHAR HostName[MAX_HOSTNAME_LEN + 4];
    CHAR DomainName[MAX_DOMAIN_NAME_LEN + 4];
    PIP_ADDR_STRING CurrentDnsServer;
    IP_ADDR_STRING DnsServerList;
    UINT NodeType;
    CHAR ScopeId[MAX_SCOPE_ID_LEN + 4];
    UINT EnableRouting;
    UINT EnableProxy;
    UINT EnableDns;
} FIXED_INFO, *PFIXED_INFO, IP_GLOBAL_INFO, *PIP_GLOBAL_INFO;

typedef struct akari_IP_ADAPTER_INDEX_MAP {
    ULONG Index;
    WCHAR Name[MAX_ADAPTER_NAME];
} IP_ADAPTER_INDEX_MAP, *PIP_ADAPTER_INDEX_MAP;

typedef struct akari_IP_INTERFACE_INFO {
    LONG NumAdapters;
    IP_ADAPTER_INDEX_MAP Adapter[1];
} IP_INTERFACE_INFO, *PIP_INTERFACE_INFO;

typedef struct akari_MIB_IFROW {
    WCHAR wszName[MAX_INTERFACE_NAME_LEN];
    DWORD dwIndex;
    DWORD dwType;
    DWORD dwMtu;
    DWORD dwSpeed;
    DWORD dwPhysAddrLen;
    UCHAR bPhysAddr[MAXLEN_PHYSADDR];
    DWORD dwAdminStatus;
    DWORD dwOperStatus;
    DWORD dwLastChange;
    DWORD dwInOctets;
    DWORD dwInUcastPkts;
    DWORD dwInNUcastPkts;
    DWORD dwInDiscards;
    DWORD dwInErrors;
    DWORD dwInUnknownProtos;
    DWORD dwOutOctets;
    DWORD dwOutUcastPkts;
    DWORD dwOutNUcastPkts;
    DWORD dwOutDiscards;
    DWORD dwOutErrors;
    DWORD dwOutQLen;
    DWORD dwDescrLen;
    UCHAR bDescr[MAXLEN_IFDESC];
} MIB_IFROW, *PMIB_IFROW;

typedef struct akari_MIB_IFTABLE {
    DWORD dwNumEntries;
    MIB_IFROW table[1];
} MIB_IFTABLE, *PMIB_IFTABLE;

typedef struct akari_MIB_IPADDRROW {
    DWORD dwAddr;
    DWORD dwIndex;
    DWORD dwMask;
    DWORD dwBCastAddr;
    DWORD dwReasmSize;
    USHORT unused1;
    USHORT wType;
} MIB_IPADDRROW, *PMIB_IPADDRROW, MIB_IPADDRESS, *PMIB_IPADDRESS;

typedef struct akari_MIB_IPADDRTABLE {
    DWORD dwNumEntries;
    MIB_IPADDRROW table[1];
} MIB_IPADDRTABLE, *PMIB_IPADDRTABLE;

typedef struct akari_MIB_TCPROW {
    DWORD dwState;
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwRemoteAddr;
    DWORD dwRemotePort;
} MIB_TCPROW, *PMIB_TCPROW;

typedef struct akari_MIB_TCPTABLE {
    DWORD dwNumEntries;
    MIB_TCPROW table[1];
} MIB_TCPTABLE, *PMIB_TCPTABLE;

typedef struct akari_MIB_UDPROW {
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
} MIB_UDPROW, *PMIB_UDPROW;

typedef struct akari_MIB_UDPTABLE {
    DWORD dwNumEntries;
    MIB_UDPROW table[1];
} MIB_UDPTABLE, *PMIB_UDPTABLE;

typedef struct akari_MIB_TCPSTATS {
    DWORD dwRtoAlgorithm;
    DWORD dwRtoMin;
    DWORD dwRtoMax;
    DWORD dwMaxConn;
    DWORD dwActiveOpens;
    DWORD dwPassiveOpens;
    DWORD dwAttemptFails;
    DWORD dwEstabResets;
    DWORD dwCurrEstab;
    DWORD dwInSegs;
    DWORD dwOutSegs;
    DWORD dwRetransSegs;
    DWORD dwInErrs;
    DWORD dwOutRsts;
    DWORD dwNumConns;
} MIB_TCPSTATS, *PMIB_TCPSTATS;

typedef struct akari_MIB_UDPSTATS {
    DWORD dwInDatagrams;
    DWORD dwNoPorts;
    DWORD dwInErrors;
    DWORD dwOutDatagrams;
    DWORD dwNumAddrs;
} MIB_UDPSTATS, *PMIB_UDPSTATS;

typedef struct akari_MIBICMPSTATS {
    DWORD dwMsgs;
    DWORD dwErrors;
    DWORD dwDestUnreachs;
    DWORD dwTimeExcds;
    DWORD dwParmProbs;
    DWORD dwSrcQuenchs;
    DWORD dwRedirects;
    DWORD dwEchos;
    DWORD dwEchoReps;
    DWORD dwTimestamps;
    DWORD dwTimestampReps;
    DWORD dwAddrMasks;
    DWORD dwAddrMaskReps;
} MIBICMPSTATS, *PMIBICMPSTATS;

typedef struct akari_MIBICMPINFO {
    MIBICMPSTATS icmpInStats;
    MIBICMPSTATS icmpOutStats;
} MIBICMPINFO, *PMIBICMPINFO;

typedef struct akari_MIB_ICMP {
    MIBICMPINFO stats;
} MIB_ICMP, *PMIB_ICMP;

typedef struct akari_MIB_IPSTATS {
    DWORD dwForwarding;
    DWORD dwDefaultTTL;
    DWORD dwInReceives;
    DWORD dwInHdrErrors;
    DWORD dwInAddrErrors;
    DWORD dwForwDatagrams;
    DWORD dwInUnknownProtos;
    DWORD dwInDiscards;
    DWORD dwInDelivers;
    DWORD dwOutRequests;
    DWORD dwRoutingDiscards;
    DWORD dwOutDiscards;
    DWORD dwOutNoRoutes;
    DWORD dwReasmTimeout;
    DWORD dwReasmReqds;
    DWORD dwReasmOks;
    DWORD dwReasmFails;
    DWORD dwFragOks;
    DWORD dwFragFails;
    DWORD dwFragCreates;
    DWORD dwNumIf;
    DWORD dwNumAddr;
    DWORD dwNumRoutes;
} MIB_IPSTATS, *PMIB_IPSTATS;

typedef struct akari_IP_OPTION_INFORMATION {
    UCHAR Ttl;
    UCHAR Tos;
    UCHAR Flags;
    UCHAR OptionsSize;
    UCHAR *OptionsData;
} IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;

typedef struct akari_ICMP_ECHO_REPLY {
    ULONG Address;
    ULONG Status;
    ULONG RoundTripTime;
    USHORT DataSize;
    USHORT Reserved;
    PVOID Data;
    IP_OPTION_INFORMATION Options;
} ICMP_ECHO_REPLY, *PICMP_ECHO_REPLY;


IPHLPAPI DWORD WINAPI GetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen);
IPHLPAPI DWORD WINAPI GetPerAdapterInfo(ULONG IfIndex, PIP_PER_ADAPTER_INFO pPerAdapterInfo,
    PULONG pOutBufLen);
IPHLPAPI DWORD WINAPI GetAdapterIndex(LPWSTR AdapterName, PULONG IfIndex);
IPHLPAPI DWORD WINAPI GetNumberOfInterfaces(PDWORD pdwNumIf);
IPHLPAPI DWORD WINAPI GetIfEntry(PMIB_IFROW pIfRow);
IPHLPAPI DWORD WINAPI GetIfTable(PMIB_IFTABLE pIfTable, PULONG pdwSize, BOOL bOrder);
IPHLPAPI DWORD WINAPI GetInterfaceInfo(PIP_INTERFACE_INFO pIfTable, PULONG dwOutBufLen);
IPHLPAPI DWORD WINAPI GetIpAddrTable(PMIB_IPADDRTABLE pIpAddrTable, PULONG pdwSize,
    BOOL bOrder);
IPHLPAPI DWORD WINAPI GetNetworkParams(PFIXED_INFO pFixedInfo, PULONG pOutBufLen);
IPHLPAPI DWORD WINAPI GetTcpTable(PMIB_TCPTABLE pTcpTable, PULONG pdwSize, BOOL bOrder);
IPHLPAPI DWORD WINAPI GetUdpTable(PMIB_UDPTABLE pUdpTable, PULONG pdwSize, BOOL bOrder);
IPHLPAPI DWORD WINAPI GetIpStatistics(PMIB_IPSTATS pStats);
IPHLPAPI DWORD WINAPI GetTcpStatistics(PMIB_TCPSTATS pStats);
IPHLPAPI DWORD WINAPI GetUdpStatistics(PMIB_UDPSTATS pStats);
IPHLPAPI DWORD WINAPI GetIcmpStatistics(PMIB_ICMP pStats);
IPHLPAPI DWORD WINAPI GetBestInterface(DWORD dwDestAddr, PDWORD pdwBestIfIndex);
IPHLPAPI DWORD WINAPI GetFriendlyIfIndex(DWORD IfIndex);

/*
 * The raw ICMP helper calls were only added to the ARM, SH and MIPS builds of
 * iphlpapi in Windows CE 5.0; the x86 build of Windows CE 4.2 already had them.
 */
#if (_WIN32_WCE >= 0x500) || defined(AKARI_CPU_X86)
IPHLPAPI HANDLE WINAPI IcmpCreateFile(VOID);
IPHLPAPI BOOL WINAPI IcmpCloseHandle(HANDLE IcmpHandle);
IPHLPAPI DWORD WINAPI IcmpSendEcho(HANDLE IcmpHandle, ULONG DestinationAddress,
    LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions,
    LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
IPHLPAPI DWORD WINAPI IcmpParseReplies(LPVOID ReplyBuffer, DWORD ReplySize);
#endif

IPHLPAPI DWORD WINAPI SendARP(ULONG DestIP, ULONG SrcIP, PULONG pMacAddr, PULONG PhyAddrLen);
IPHLPAPI DWORD WINAPI NotifyAddrChange(PHANDLE Handle, LPOVERLAPPED lpOverlapped);
IPHLPAPI DWORD WINAPI NotifyRouteChange(PHANDLE Handle, LPOVERLAPPED lpOverlapped);

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_IPHLPAPI_H */
