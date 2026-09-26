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

struct wsacrypt { DWORD dwVersion; DWORD dwProviderId; };

#define FD_SETSIZE 64

#define AF_UNSPEC   0
#define AF_UNIX     1
#define AF_INET     2
#define AF_IMPLINK  3
#define AF_APPLETALK 16
#define AF_IRDA     26
#define AF_INET6    23

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
#define FD_ALL_EVENTS 0x7f

#define IOCPARM_MASK 0x7f
#define IOC_VOID     0x20000000
#define IOC_OUT      0x40000000
#define IOC_IN       0x80000000
#define IOC_INOUT    (IOC_IN | IOC_OUT)
#define FIONBIO      0x5427
#define FIONREAD     0x4004667f
#define FIOASYNC     0x5280
#define SIOCATMARK   0x40047307
#define SIOCGHIWAT   0x40047301
#define SIOCGLOWAT   0x40047303
#define SIOCSHIWAT   0x80047300
#define SIOCSLOWAT   0x80047302
#define SIO_GET_EXTENSION_FUNCTION_POINTER 0xC8000006

#define SD_RECEIVE 0x00
#define SD_SEND    0x01
#define SD_BOTH    0x02

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
    CHAR szDescription[257];
    CHAR szSystemStatus[129];
    USHORT iMaxSockets;
    USHORT iMaxUdpDg;
    CHAR *lpVendorInfo;
} WSADATA, *LPWSADATA;

typedef struct _WSABUF {
    ULONG len;
    CHAR *buf;
} WSABUF, *LPWSABUF;

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
    void *lpServiceClassId;
    void *lpVersion;
    LPWSTR lpszComment;
    DWORD dwNameSpace;
    void *lpNSProviderId;
    LPWSTR lpszContext;
    DWORD dwNumberOfProtocols;
    void *lpafpProtocols;
    LPWSTR lpszQueryString;
    DWORD dwNumberOfCsAddrs;
    void *lpcsaBuffer;
    DWORD dwOutputFlags;
    LPWSTR lpszBlob;
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
    DWORD ProtocolChainLen;
    INT iLayer;
    INT iProtocol;
    INT iProtocolMaxOffset;
    INT iNetworkByteOrder;
    INT iSecurityScheme;
    DWORD dwMessageSize;
    DWORD dwProviderReserved;
    WCHAR szProtocol[256];
} WSAPROTOCOL_INFOW, *LPWSAPROTOCOL_INFOW;

typedef int (WINAPI *LPFN_WSARECV)(SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD,
    void *, void *);

WINBASEAPI int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
WINBASEAPI int WINAPI WSACleanup(VOID);
WINBASEAPI int WINAPI WSAGetLastError(VOID);
WINBASEAPI void WINAPI WSASetLastError(int iError);
WINBASEAPI SOCKET WINAPI socket(int af, int type, int protocol);
WINBASEAPI SOCKET WINAPI WSASocketW(int af, int type, int protocol,
    const WSAPROTOCOL_INFOW *lpProtocolInfo, unsigned int g, DWORD dwFlags);
WINBASEAPI int WINAPI closesocket(SOCKET s);
WINBASEAPI int WINAPI bind(SOCKET s, const struct sockaddr *name, int namelen);
WINBASEAPI int WINAPI connect(SOCKET s, const struct sockaddr *name, int namelen);
WINBASEAPI int WINAPI WSAConnect(SOCKET s, const struct sockaddr *name, int namelen,
    LPWSABUF lpCallerData, LPWSABUF lpCalleeData, void *lpSQOS, void *lpGQOS);
WINBASEAPI int WINAPI listen(SOCKET s, int backlog);
WINBASEAPI SOCKET WINAPI accept(SOCKET s, struct sockaddr *addr, int *addrlen);
WINBASEAPI SOCKET WINAPI WSAAccept(SOCKET s, struct sockaddr *addr, int *addrlen,
    void *lpfnCondition, DWORD_PTR dwCallbackData);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI SOCKET WINAPI WSAJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
    LPWSABUF lpCallerData, LPWSABUF lpCalleeData, void *lpSQOS, void *lpGQOS, DWORD dwFlags);
#endif
WINBASEAPI int WINAPI send(SOCKET s, const char *buf, int len, int flags);
WINBASEAPI int WINAPI sendto(SOCKET s, const char *buf, int len, int flags,
    const struct sockaddr *to, int tolen);
WINBASEAPI int WINAPI recv(SOCKET s, char *buf, int len, int flags);
WINBASEAPI int WINAPI recvfrom(SOCKET s, char *buf, int len, int flags,
    struct sockaddr *from, int *fromlen);
WINBASEAPI int WINAPI WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent, DWORD dwFlags, void *lpOverlapped, void *lpCompletionRoutine);
WINBASEAPI int WINAPI WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *lpTo, int iTolen,
    void *lpOverlapped, void *lpCompletionRoutine);
WINBASEAPI int WINAPI WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, void *lpOverlapped,
    void *lpCompletionRoutine);
WINBASEAPI int WINAPI WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, int *lpFromlen,
    void *lpOverlapped, void *lpCompletionRoutine);
WINBASEAPI int WINAPI select(int nfds, struct fd_set *readfds, struct fd_set *writefds,
    struct fd_set *exceptfds, const struct timeval *timeout);
WINBASEAPI int WINAPI shutdown(SOCKET s, int how);
WINBASEAPI int WINAPI getsockopt(SOCKET s, int level, int optname, char *optval,
    int *optlen);
WINBASEAPI int WINAPI setsockopt(SOCKET s, int level, int optname, const char *optval,
    int optlen);
WINBASEAPI int WINAPI getsockname(SOCKET s, struct sockaddr *name, int *namelen);
WINBASEAPI int WINAPI getpeername(SOCKET s, struct sockaddr *name, int *namelen);
WINBASEAPI int WINAPI ioctlsocket(SOCKET s, LONG cmd, ULONG *argp);
WINBASEAPI int WINAPI WSAIoctl(SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned,
    void *lpOverlapped, void *lpCompletionRoutine);
WINBASEAPI u_long WINAPI htonl(u_long hostlong);
WINBASEAPI u_short WINAPI htons(u_short hostshort);
WINBASEAPI u_long WINAPI ntohl(u_long netlong);
WINBASEAPI u_short WINAPI ntohs(u_short netshort);
WINBASEAPI DWORD WINAPI WSAHtonl(SOCKET s, u_long hostlong, u_long *lpNetlong);
WINBASEAPI DWORD WINAPI WSAHtons(SOCKET s, u_short hostshort, u_short *lpNetshort);
WINBASEAPI DWORD WINAPI WSANtohl(SOCKET s, u_long netlong, u_long *lpHostlong);
WINBASEAPI DWORD WINAPI WSANtohs(SOCKET s, u_short netshort, u_short *lpHostshort);
WINBASEAPI ULONG WINAPI inet_addr(const char *cp);
WINBASEAPI char *WINAPI inet_ntoa(struct in_addr in);
WINBASEAPI struct hostent *WINAPI gethostbyname(const char *name);
WINBASEAPI struct hostent *WINAPI gethostbyaddr(const char *addr, int len, int type);
WINBASEAPI int WINAPI gethostname(char *name, int namelen);
WINBASEAPI int WINAPI sethostname(const char *name, int namelen);
WINBASEAPI struct servent *WINAPI getservbyname(const char *name, const char *proto);
WINBASEAPI struct servent *WINAPI getservbyport(int port, const char *proto);
WINBASEAPI struct protoent *WINAPI getprotobyname(const char *name);
WINBASEAPI struct protoent *WINAPI getprotobynumber(int number);
WINBASEAPI int WINAPI getaddrinfo(const char *nodename, const char *servname,
    const void *hints, void **res);
WINBASEAPI int WINAPI getnameinfo(const struct sockaddr *sa, int salen, char *host,
    int hostlen, char *serv, int servlen, int flags);
WINBASEAPI void WINAPI freeaddrinfo(void *ai);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI int WINAPI WSAAddressToStringW(LPSOCKADDR Address, DWORD AddressLength,
    void *lpProtocolInfo, LPWSTR AddressString, LPDWORD lpdwAddressStringLength);
#endif
WINBASEAPI int WINAPI WSAEnumProtocolsW(LPINT lpiProtocols, void *lpProtocolBuffer,
    LPDWORD lpdwBufferLength);
WINBASEAPI int WINAPI WSAEnumNameSpaceProvidersW(LPDWORD lpdwBufferLength, void *lpnspBuffer);
WINBASEAPI int WINAPI WSALookupServiceBeginW(const WSAQUERYSETW *lpqsRestrictions,
    DWORD dwControlFlags, HANDLE *lphLookup);
WINBASEAPI int WINAPI WSALookupServiceNextW(HANDLE hLookup, DWORD dwControlFlags,
    LPDWORD lpdwBufferLength, WSAQUERYSETW *lpqsResults);
WINBASEAPI int WINAPI WSALookupServiceEnd(HANDLE hLookup);
WINBASEAPI int WINAPI WSASetServiceW(const WSAQUERYSETW *lpqsRegInfo,
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
WINBASEAPI int WINAPI WSAEventSelect(SOCKET s, HANDLE hEventObject, LONG lNetworkEvents);
WINBASEAPI int WINAPI WSAEnumNetworkEvents(SOCKET s, HANDLE hEventObject, void *lpNetworkEvents);
WINBASEAPI BOOL WINAPI WSAGetOverlappedResult(SOCKET s, void *lpOverlapped,
    LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags);
#if (_WIN32_WCE >= 0x500)
WINBASEAPI int WINAPI WSANSPIoctl(HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer,
    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned,
    void *lpCompletion);
#endif
#if (_WIN32_WCE >= 0x600)
WINBASEAPI int WINAPI WSAControl(DWORD dwControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer,
    LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned);
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
