/* Winsock 2. Original text. Exported by ws2.dll.
 *
 * On Windows CE the Winsock 2 API comes from ws2.dll (ws2.lib), not from
 * coredll. Ws2.lib is the documented library for Windows CE 4.0 and later.
 */
#ifndef AKARI_WCE_WINSOCK2_H
#define AKARI_WCE_WINSOCK2_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"

typedef UCHAR u_char;
typedef USHORT u_short;
typedef UINT u_int;
typedef ULONG u_long;
typedef UINT_PTR SOCKET;
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR   (-1)

typedef struct in_addr {
    union {
        struct { UCHAR s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { USHORT s_w1, s_w2; } S_un_w;
        ULONG S_addr;
    } S_un;
#define s_addr  S_un.S_addr
#define s_host  S_un.S_un_b.s_b2
#define s_net   S_un.S_un_b.s_b1
#define s_imp   S_un.S_un_w.s_w2
#define s_impno S_un.S_un_b.s_b4
#define s_lh    S_un.S_un_b.s_b3
} IN_ADDR, *PIN_ADDR, *LPIN_ADDR;

struct in6_addr {
    union {
        UCHAR Byte[16];
        USHORT Word[8];
    } u;
};
typedef struct in6_addr IN6_ADDR, *PIN6_ADDR, *LPIN6_ADDR;

struct sockaddr {
    USHORT sa_family;
    CHAR sa_data[14];
};
typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;

struct sockaddr_in {
    short sin_family;
    USHORT sin_port;
    struct in_addr sin_addr;
    CHAR sin_zero[8];
};
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;

struct sockaddr_in6 {
    short sin6_family;
    USHORT sin6_port;
    ULONG sin6_flowinfo;
    struct in6_addr sin6_addr;
    ULONG sin6_scope_id;
};
typedef struct sockaddr_in6 SOCKADDR_IN6, *PSOCKADDR_IN6, *LPSOCKADDR_IN6;

struct sockaddr_storage {
    short ss_family;
    CHAR __ss_pad1[6];
    __int64 __ss_align;
    CHAR __ss_pad2[112];
};
typedef struct sockaddr_storage SOCKADDR_STORAGE, *PSOCKADDR_STORAGE;

struct hostent {
    CHAR *h_name;
    CHAR **h_aliases;
    short h_addrtype;
    short h_length;
    CHAR **h_addr_list;
#define h_addr h_addr_list[0]
};

struct servent {
    CHAR *s_name;
    CHAR **s_aliases;
    short s_port;
    CHAR *s_proto;
};

struct protoent {
    CHAR *p_name;
    CHAR **p_aliases;
    short p_proto;
};

struct timeval {
    LONG tv_sec;
    LONG tv_usec;
};

struct linger {
    USHORT l_onoff;
    USHORT l_linger;
};

struct fd_set {
    UINT fd_count;
    SOCKET fd_array[64];
};
typedef struct fd_set FD_SET;
typedef FD_SET fd_set;

struct wsacrypt { DWORD dwVersion; DWORD dwProviderId; };

#define FD_SETSIZE 64

#define AF_UNSPEC   0
#define AF_UNIX     1
#define AF_INET     2
#define AF_IMPLINK  3
#define AF_APPLETALK 16
#define AF_INET6    23
#define AF_12844    25
/* AF_IRDA and AF_ATM are swapped on CE 5.0 alone, and that is not a matter of
 * reading the header carefully -- the three releases genuinely differ.
 *
 * CE 4.2 and CE 6.0 both wrap the pair in #ifdef UNDER_CE, with AF_IRDA 22 and
 * AF_ATM 26 in the CE arm (winsock2.h:536 and :544).  CE 5.0 has no conditional
 * at all: a single flat list that gives AF_ATM 22 and AF_IRDA 26.  So the CE 5.0
 * target really does use the opposite numbers, and one value cannot serve all
 * three. */
#if (_WIN32_WCE >= 0x500) && (_WIN32_WCE < 0x600)
#define AF_ATM      22
#define AF_IRDA     26
#else
#define AF_IRDA     22
#define AF_ATM      26
#endif

#define PF_INET     AF_INET
#define PF_INET6    AF_INET6
#define PF_UNSPEC   AF_UNSPEC

#define SOCK_STREAM 1
#define SOCK_DGRAM  2
#define SOCK_RAW    3
#define SOCK_RDM    4
#define SOCK_SEQPACKET 5

#define IPPROTO_IP   0
#define IPPROTO_ICMP 1
#define IPPROTO_IGMP 2
#define IPPROTO_TCP  6
#define IPPROTO_UDP  17
#define IPPROTO_IPV6 41
#define IPPROTO_ICMPV6 58
#define IPPROTO_RM   113

#define SOL_SOCKET 0xffff

#define SO_DEBUG        0x0001
#define SO_REUSEADDR    0x0004
#define SO_KEEPALIVE    0x0008
#define SO_DONTROUTE    0x0010
#define SO_BROADCAST    0x0020
#define SO_LINGER       0x0080
#define SO_OOBINLINE    0x0100
#define SO_SNDBUF       0x1001
#define SO_RCVBUF       0x1002
#define SO_SNDLOWAT     0x1003
#define SO_RCVLOWAT     0x1004
#define SO_SNDTIMEO     0x1005
#define SO_RCVTIMEO     0x1006
#define SO_ERROR        0x1007
#define SO_TYPE         0x1008
#define SO_ACCEPTCONN   0x0002

#define TCP_NODELAY   0x0001
#define TCP_BSDURGENT 0x7000

#define MSG_OOB       0x0001
#define MSG_PEEK      0x0002
#define MSG_DONTROUTE 0x0004

#define INADDR_ANY       ((ULONG)0x00000000)
#define INADDR_LOOPBACK  0x7f000001
#define INADDR_BROADCAST ((ULONG)0xffffffff)
#define INADDR_NONE      0xffffffff

#define FD_READ      0x01
#define FD_WRITE     0x02
#define FD_OOB       0x04
#define FD_ACCEPT    0x08
#define FD_CONNECT   0x10
#define FD_CLOSE     0x20
#define FD_QOS       0x40
#define FD_MAX_EVENTS 10
#define FD_ALL_EVENTS ((1 << FD_MAX_EVENTS) - 1)

#define IOCPARM_MASK 0x7f
#define IOC_VOID     0x20000000
#define IOC_OUT      0x40000000
#define IOC_IN       0x80000000
#define IOC_INOUT    (IOC_IN|IOC_OUT)
#define _IO(x,y)     (IOC_VOID|((x)<<8)|(y))
#define _IOR(x,y,t)  (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define _IOW(x,y,t)  (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD    _IOR('f', 127, u_long)
#define FIONBIO     _IOW('f', 126, u_long)
#define FIOASYNC    _IOW('f', 125, u_long)

#define SIOCSHIWAT  _IOW('s',  0, u_long)
#define SIOCGHIWAT  _IOR('s',  1, u_long)
#define SIOCSLOWAT  _IOW('s',  2, u_long)
#define SIOCGLOWAT  _IOR('s',  3, u_long)
#define SIOCATMARK  _IOR('s',  7, u_long)

#define IOC_UNIX     0x00000000
#define IOC_WS2      0x08000000
#define IOC_PROTOCOL 0x10000000
#define IOC_VENDOR   0x18000000
#define _WSAIO(x,y)     (IOC_VOID|(x)|(y))
#define _WSAIOR(x,y)    (IOC_OUT|(x)|(y))
#define _WSAIOW(x,y)    (IOC_IN|(x)|(y))
#define _WSAIORW(x,y)   (IOC_INOUT|(x)|(y))

#define SIO_ASSOCIATE_HANDLE                 _WSAIOW(IOC_WS2,1)
#define SIO_ENABLE_CIRCULAR_QUEUEING         _WSAIO(IOC_WS2,2)
#define SIO_FIND_ROUTE                       _WSAIOR(IOC_WS2,3)
#define SIO_FLUSH                            _WSAIO(IOC_WS2,4)
#define SIO_GET_BROADCAST_ADDRESS            _WSAIOR(IOC_WS2,5)
#define SIO_GET_EXTENSION_FUNCTION_POINTER   _WSAIORW(IOC_WS2,6)
#define SIO_GET_QOS                          _WSAIORW(IOC_WS2,7)
#define SIO_GET_GROUP_QOS                    _WSAIORW(IOC_WS2,8)
#define SIO_MULTIPOINT_LOOPBACK              _WSAIOW(IOC_WS2,9)
#define SIO_MULTICAST_SCOPE                  _WSAIOW(IOC_WS2,10)
#define SIO_SET_QOS                          _WSAIOW(IOC_WS2,11)
#define SIO_SET_GROUP_QOS                    _WSAIOW(IOC_WS2,12)
#define SIO_TRANSLATE_HANDLE                 _WSAIORW(IOC_WS2,13)
#define SIO_NSP_NOTIFY_CHANGE                _WSAIOW(IOC_WS2,25)

#define SD_RECEIVE 0x00
#define SD_SEND    0x01
#define SD_BOTH    0x02

#define WSADESCRIPTION_LEN 256
#define WSASYS_STATUS_LEN  128

#define WSABASEERR 10000
#define WSAEINTR             (WSABASEERR + 4)
#define WSAEBADF             (WSABASEERR + 9)
#define WSAEACCES            (WSABASEERR + 13)
#define WSAEFAULT            (WSABASEERR + 14)
#define WSAEINVAL            (WSABASEERR + 22)
#define WSAEMFILE            (WSABASEERR + 24)
#define WSAEWOULDBLOCK       (WSABASEERR + 35)
#define WSAEINPROGRESS       (WSABASEERR + 36)
#define WSAEALREADY          (WSABASEERR + 37)
#define WSAENOTSOCK          (WSABASEERR + 38)
#define WSAEDESTADDRREQ      (WSABASEERR + 39)
#define WSAEMSGSIZE          (WSABASEERR + 40)
#define WSAEPROTOTYPE        (WSABASEERR + 41)
#define WSAENOPROTOOPT       (WSABASEERR + 42)
#define WSAEPROTONOSUPPORT   (WSABASEERR + 43)
#define WSAESOCKTNOSUPPORT   (WSABASEERR + 44)
#define WSAEOPNOTSUPP        (WSABASEERR + 45)
#define WSAEPFNOSUPPORT      (WSABASEERR + 46)
#define WSAEAFNOSUPPORT      (WSABASEERR + 47)
#define WSAEADDRINUSE        (WSABASEERR + 48)
#define WSAEADDRNOTAVAIL     (WSABASEERR + 49)
#define WSAENETDOWN          (WSABASEERR + 50)
#define WSAENETUNREACH       (WSABASEERR + 51)
#define WSAENETRESET         (WSABASEERR + 52)
#define WSAECONNABORTED      (WSABASEERR + 53)
#define WSAECONNRESET        (WSABASEERR + 54)
#define WSAENOBUFS           (WSABASEERR + 55)
#define WSAEISCONN           (WSABASEERR + 56)
#define WSAENOTCONN          (WSABASEERR + 57)
#define WSAESHUTDOWN         (WSABASEERR + 58)
#define WSAETOOMANYREFS      (WSABASEERR + 59)
#define WSAETIMEDOUT         (WSABASEERR + 60)
#define WSAECONNREFUSED      (WSABASEERR + 61)
#define WSAELOOP             (WSABASEERR + 62)
#define WSAENAMETOOLONG      (WSABASEERR + 63)
#define WSAEHOSTDOWN         (WSABASEERR + 64)
#define WSAEHOSTUNREACH      (WSABASEERR + 65)
#define WSAENOTEMPTY         (WSABASEERR + 66)
#define WSAEPROCLIM          (WSABASEERR + 67)
#define WSAEUSERS            (WSABASEERR + 68)
#define WSAEDQUOT            (WSABASEERR + 69)
#define WSAESTALE            (WSABASEERR + 70)
#define WSAEREMOTE           (WSABASEERR + 71)
#define WSASYSNOTREADY       (WSABASEERR + 91)
#define WSAVERNOTSUPPORTED   (WSABASEERR + 92)
#define WSANOTINITIALISED    (WSABASEERR + 93)
#define WSAHOST_NOT_FOUND    (WSABASEERR + 1001)
#define WSATRY_AGAIN         (WSABASEERR + 1002)
#define WSANO_RECOVERY       (WSABASEERR + 1003)
#define WSANO_DATA           (WSABASEERR + 1004)

typedef struct WSAData {
    WORD wVersion;
    WORD wHighVersion;
    CHAR szDescription[WSADESCRIPTION_LEN + 1];
    CHAR szSystemStatus[WSASYS_STATUS_LEN + 1];
    USHORT iMaxSockets;
    USHORT iMaxUdpDg;
    CHAR *lpVendorInfo;
} WSADATA, *LPWSADATA;

typedef struct _WSABUF {
    ULONG len;
    CHAR *buf;
} WSABUF, *LPWSABUF;

typedef ULONG SERVICETYPE;

#define SERVICETYPE_NOTRAFFIC      0x00000000
#define SERVICETYPE_BESTEFFORT     0x00000001
#define SERVICETYPE_CONTROLLEDLOAD 0x00000002
#define SERVICETYPE_GUARANTEED     0x00000003
#define QOS_NOT_SPECIFIED          0xFFFFFFFF
#define POSITIVE_INFINITY_RATE     0xFFFFFFFE

typedef struct akari_flowspec {
    ULONG       TokenRate;
    ULONG       TokenBucketSize;
    ULONG       PeakBandwidth;
    ULONG       Latency;
    ULONG       DelayVariation;
    SERVICETYPE ServiceType;
    ULONG       MaxSduSize;
    ULONG       MinimumPolicedSize;
} FLOWSPEC, *PFLOWSPEC, *LPFLOWSPEC;

typedef struct akari_qos {
    FLOWSPEC SendingFlowspec;
    FLOWSPEC ReceivingFlowspec;
    WSABUF   ProviderSpecific;
} QOS, *LPQOS;

#define CF_ACCEPT 0x0000
#define CF_REJECT 0x0001
#define CF_DEFER  0x0002

typedef unsigned long GROUP;
typedef DWORD WSAEVENT, *LPWSAEVENT;

typedef struct akari_wsaoverlapped {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    DWORD     Offset;
    DWORD     OffsetHigh;
    WSAEVENT  hEvent;
} WSAOVERLAPPED, *LPWSAOVERLAPPED;

typedef struct akari_socket_address {
    LPSOCKADDR lpSockaddr;
    INT        iSockaddrLength;
} SOCKET_ADDRESS, *PSOCKET_ADDRESS, *LPSOCKET_ADDRESS;

typedef struct akari_csaddr_info {
    SOCKET_ADDRESS LocalAddr;
    SOCKET_ADDRESS RemoteAddr;
    INT            iSocketType;
    INT            iProtocol;
} CSADDR_INFO, *PCSADDR_INFO, *LPCSADDR_INFO;

typedef struct akari_afprotocols {
    INT iAddressFamily;
    INT iProtocol;
} AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;

#ifndef _tagBLOB_DEFINED
#define _tagBLOB_DEFINED
#define _BLOB_DEFINED
#define _LPBLOB_DEFINED
typedef struct akari_tagBLOB {
    ULONG cbSize;
    BYTE *pBlobData;
} BLOB, *LPBLOB;
#endif /* _tagBLOB_DEFINED */

typedef struct akari_wsanetworkevents {
    long lNetworkEvents;
    int  iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;

#define MAX_PROTOCOL_CHAIN 7
#define BASE_PROTOCOL      1
#define LAYERED_PROTOCOL   0
#define WSAPROTOCOL_LEN    255

typedef struct akari_wsaprotocol_chain {
    int   ChainLen;
    DWORD ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

typedef enum akari_wsaecomparator {
    COMP_EQUAL = 0,
    COMP_NOTLESS
} WSAECOMPARATOR, *PWSAECOMPARATOR, *LPWSAECOMPARATOR;

typedef struct akari_wsaversion {
    DWORD          dwVersion;
    WSAECOMPARATOR ecHow;
} WSAVERSION, *PWSAVERSION, *LPWSAVERSION;

typedef struct akari_wsanamespace_infow {
    GUID   NSProviderId;
    DWORD  dwNameSpace;
    BOOL   fActive;
    DWORD  dwVersion;
    LPWSTR lpszIdentifier;
} WSANAMESPACE_INFOW, *PWSANAMESPACE_INFOW, *LPWSANAMESPACE_INFOW;

typedef enum akari_wsacompletiontype {
    NSP_NOTIFY_IMMEDIATELY = 0,
    NSP_NOTIFY_HWND,
    NSP_NOTIFY_EVENT,
    NSP_NOTIFY_PORT,
    NSP_NOTIFY_APC
} WSACOMPLETIONTYPE, *PWSACOMPLETIONTYPE, *LPWSACOMPLETIONTYPE;

typedef struct akari_wsacompletion {
    WSACOMPLETIONTYPE Type;
    union akari_wsacompletion_u {
        struct akari_wsc_window {
            HWND   hWnd;
            UINT   uMsg;
            WPARAM context;
        } WindowMessage;
        struct akari_wsc_event {
            LPWSAOVERLAPPED lpOverlapped;
        } Event;
        struct akari_wsc_apc {
            LPWSAOVERLAPPED lpOverlapped;
            void (CALLBACK *lpfnCompletionProc)(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
        } Apc;
        struct akari_wsc_port {
            LPWSAOVERLAPPED lpOverlapped;
            HANDLE          hPort;
            ULONG_PTR       Key;
        } Port;
    } Parameters;
} WSACOMPLETION, *PWSACOMPLETION, *LPWSACOMPLETION;

typedef int (CALLBACK *LPCONDITIONPROC)(LPWSABUF, LPWSABUF, LPQOS, LPQOS,
    LPWSABUF, LPWSABUF, GROUP *, DWORD_PTR);

typedef void (CALLBACK *LPWSAOVERLAPPED_COMPLETION_ROUTINE)(DWORD dwError,
    DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);

#define WSA_FLAG_OVERLAPPED     0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT  0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF  0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT  0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF  0x10

typedef enum _WSAESETSERVICEOP {
    RNRSERVICE_REGISTER = 0,
    RNRSERVICE_DEREGISTER,
    RNRSERVICE_DELETE
} WSAESETSERVICEOP;

typedef struct _WSAQUERYSETW {
    DWORD dwSize;
    LPWSTR lpszServiceInstanceName;
    LPGUID lpServiceClassId;
    LPWSAVERSION lpVersion;
    LPWSTR lpszComment;
    DWORD dwNameSpace;
    LPGUID lpNSProviderId;
    LPWSTR lpszContext;
    DWORD dwNumberOfProtocols;
    LPAFPROTOCOLS lpafpProtocols;
    LPWSTR lpszQueryString;
    DWORD dwNumberOfCsAddrs;
    LPCSADDR_INFO lpcsaBuffer;
    DWORD dwOutputFlags;
    LPBLOB lpBlob;
} WSAQUERYSETW, *LPWSAQUERYSETW;

#define LUP_DEEP                0x0001
#define LUP_CONTAINERS          0x0002
#define LUP_NOCONTAINERS        0x0004
#define LUP_NEAREST             0x0008
#define LUP_RETURN_NAME         0x0010
#define LUP_RETURN_TYPE         0x0020
#define LUP_RETURN_VERSION      0x0040
#define LUP_RETURN_COMMENT      0x0080
#define LUP_RETURN_ADDR         0x0100
#define LUP_RETURN_BLOB         0x0200
#define LUP_RETURN_ALIASES      0x0400
#define LUP_RETURN_QUERY_STRING 0x0800
#define LUP_RETURN_ALL          0x0FF0
#define LUP_RES_SERVICE         0x8000
#define LUP_FLUSHCACHE          0x1000
#define LUP_FLUSHPREVIOUS       0x2000

#define NS_ALL          0
#define NS_DNS          12
#define NS_BTH          16

typedef struct _WSAPROTOCOL_INFOW {
    DWORD dwServiceFlags1;
    DWORD dwServiceFlags2;
    DWORD dwServiceFlags3;
    DWORD dwServiceFlags4;
    DWORD dwProviderFlags;
    GUID ProviderId;
    DWORD dwCatalogEntryId;
    WSAPROTOCOLCHAIN ProtocolChain;
    INT iVersion;
    INT iAddressFamily;
    INT iMaxSockAddr;
    INT iMinSockAddr;
    INT iSocketType;
    INT iProtocol;
    INT iProtocolMaxOffset;
    INT iNetworkByteOrder;
    INT iSecurityScheme;
    DWORD dwMessageSize;
    DWORD dwProviderReserved;
    WCHAR szProtocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFOW, *LPWSAPROTOCOL_INFOW;

typedef int (WINAPI *LPFN_WSARECV)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD,
    LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);

WINBASEAPI int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
WINBASEAPI int WINAPI WSACleanup(VOID);
WINBASEAPI int WINAPI WSAGetLastError(VOID);
WINBASEAPI void WINAPI WSASetLastError(int iError);
WINBASEAPI SOCKET WINAPI socket(int af, int type, int protocol);
WINBASEAPI SOCKET WINAPI WSASocketW(int af, int type, int protocol,
    LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags);
WINBASEAPI int WINAPI closesocket(SOCKET s);
WINBASEAPI int WINAPI bind(SOCKET s, const struct sockaddr *name, int namelen);
WINBASEAPI int WINAPI connect(SOCKET s, const struct sockaddr *name, int namelen);
WINBASEAPI int WINAPI WSAConnect(SOCKET s, const struct sockaddr *name, int namelen,
    LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);
WINBASEAPI int WINAPI listen(SOCKET s, int backlog);
WINBASEAPI SOCKET WINAPI accept(SOCKET s, struct sockaddr *addr, int *addrlen);
WINBASEAPI SOCKET WINAPI WSAAccept(SOCKET s, struct sockaddr *addr, LPINT addrlen,
    LPCONDITIONPROC lpfnCondition, DWORD_PTR dwCallbackData);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI SOCKET WINAPI WSAJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
    LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags);
#endif
WINBASEAPI int WINAPI send(SOCKET s, const char *buf, int len, int flags);
WINBASEAPI int WINAPI sendto(SOCKET s, const char *buf, int len, int flags,
    const struct sockaddr *to, int tolen);
WINBASEAPI int WINAPI recv(SOCKET s, char *buf, int len, int flags);
WINBASEAPI int WINAPI recvfrom(SOCKET s, char *buf, int len, int flags,
    struct sockaddr *from, int *fromlen);
WINBASEAPI int WINAPI WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI int WINAPI WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *lpTo, int iTolen,
    LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI int WINAPI WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI int WINAPI WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen,
    LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI int WINAPI select(int nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, const struct timeval *timeout);
WINBASEAPI int WINAPI shutdown(SOCKET s, int how);
WINBASEAPI int WINAPI getsockopt(SOCKET s, int level, int optname, char *optval,
    int *optlen);
WINBASEAPI int WINAPI setsockopt(SOCKET s, int level, int optname, const char *optval,
    int optlen);
WINBASEAPI int WINAPI getsockname(SOCKET s, struct sockaddr *name, int *namelen);
WINBASEAPI int WINAPI getpeername(SOCKET s, struct sockaddr *name, int *namelen);
WINBASEAPI int WINAPI ioctlsocket(SOCKET s, long cmd, u_long *argp);
WINBASEAPI int WINAPI WSAIoctl(SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned,
    LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI u_long WINAPI htonl(u_long hostlong);
WINBASEAPI u_short WINAPI htons(u_short hostshort);
WINBASEAPI u_long WINAPI ntohl(u_long netlong);
WINBASEAPI u_short WINAPI ntohs(u_short netshort);
WINBASEAPI int WINAPI WSAHtonl(SOCKET s, u_long hostlong, u_long *lpNetlong);
WINBASEAPI int WINAPI WSAHtons(SOCKET s, u_short hostshort, u_short *lpNetshort);
WINBASEAPI int WINAPI WSANtohl(SOCKET s, u_long netlong, u_long *lpHostlong);
WINBASEAPI int WINAPI WSANtohs(SOCKET s, u_short netshort, u_short *lpHostshort);
WINBASEAPI u_long WINAPI inet_addr(const char *cp);
WINBASEAPI char *WINAPI inet_ntoa(struct in_addr in);
WINBASEAPI struct hostent *WINAPI gethostbyname(const char *name);
WINBASEAPI struct hostent *WINAPI gethostbyaddr(const char *addr, int len, int type);
WINBASEAPI int WINAPI gethostname(char *name, int namelen);
WINBASEAPI int WINAPI sethostname(char *name, int namelen);
WINBASEAPI struct servent *WINAPI getservbyname(const char *name, const char *proto);
WINBASEAPI struct servent *WINAPI getservbyport(int port, const char *proto);
WINBASEAPI struct protoent *WINAPI getprotobyname(const char *name);
WINBASEAPI struct protoent *WINAPI getprotobynumber(int number);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI INT WINAPI WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
    LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength);
#endif
WINBASEAPI int WINAPI WSAEnumProtocolsW(LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
    LPDWORD lpdwBufferLength);
WINBASEAPI INT WINAPI WSAEnumNameSpaceProvidersW(LPDWORD lpdwBufferLength, LPWSANAMESPACE_INFOW lpnspBuffer);
WINBASEAPI INT WINAPI WSALookupServiceBeginW(LPWSAQUERYSETW lpqsRestrictions,
    DWORD dwControlFlags, LPHANDLE lphLookup);
WINBASEAPI INT WINAPI WSALookupServiceNextW(HANDLE hLookup, DWORD dwControlFlags,
    LPDWORD lpdwBufferLength, LPWSAQUERYSETW lpqsResults);
WINBASEAPI INT WINAPI WSALookupServiceEnd(HANDLE hLookup);
WINBASEAPI INT WINAPI WSASetServiceW(LPWSAQUERYSETW lpqsRegInfo,
    WSAESETSERVICEOP essOperation, DWORD dwControlFlags);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI int WINAPI WSAAsyncSelect(SOCKET s, HWND hWnd, UINT wMsg, LONG lEvent);
WINBASEAPI HANDLE WINAPI WSAAsyncGetHostByName(HWND hWnd, UINT wMsg, const char *name,
    char *buf, int buflen);
WINBASEAPI int WINAPI WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
#endif
WINBASEAPI HANDLE WINAPI WSACreateEvent(VOID);
WINBASEAPI BOOL WINAPI WSACloseEvent(HANDLE hEvent);
WINBASEAPI BOOL WINAPI WSASetEvent(HANDLE hEvent);
WINBASEAPI BOOL WINAPI WSAResetEvent(HANDLE hEvent);
WINBASEAPI DWORD WINAPI WSAWaitForMultipleEvents(DWORD cEvents, const HANDLE *lphEvents,
    BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable);
WINBASEAPI int WINAPI WSAEventSelect(SOCKET s, HANDLE hEventObject, long lNetworkEvents);
WINBASEAPI int WINAPI WSAEnumNetworkEvents(SOCKET s, HANDLE hEventObject, LPWSANETWORKEVENTS lpNetworkEvents);
WINBASEAPI BOOL WINAPI WSAGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped,
    LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI int WINAPI WSANSPIoctl(HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer,
    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned,
    LPWSACOMPLETION lpCompletion);
#endif
#if (_WIN32_WCE >= 0x600)
WINBASEAPI DWORD WINAPI WSAControl(DWORD dwControlCode, ULONG ulOption,
    LPVOID lpvInputBuffer, LPDWORD lpdwInputBufferSize,
    LPVOID lpvOutputBuffer, LPDWORD lpdwOutputBufferSize);
#endif
WINBASEAPI int WINAPI __WSAFDIsSet(SOCKET s, struct fd_set *fds);

#define WSAStartupFailed(x) ((x) != 0)

#define WSAGetAsyncBufLen(lParam)  LOWORD(lParam)
#define WSAGetAsyncError(lParam)   HIWORD(lParam)
#define WSAGetSelectEvent(lParam)  LOWORD(lParam)
#define WSAGetSelectError(lParam)  HIWORD(lParam)

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WINSOCK2_H */
