/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_WINSOCK2_H
#define AKARI_WINSOCK2_H
#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef UINT_PTR SOCKET;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
#define INVALID_SOCKET ((SOCKET)(~0))
#define SOCKET_ERROR (-1)
#define WSADESCRIPTION_LEN 256
#define WSASYS_STATUS_LEN 128
typedef struct WSAData {
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[WSADESCRIPTION_LEN + 1];
    char szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *lpVendorInfo;
} WSADATA, *LPWSADATA;
struct in_addr {
    union {
        struct { u_char s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { u_short s_w1, s_w2; } S_un_w;
        u_long S_addr;
    } S_un;
#define s_addr S_un.S_addr
};
struct sockaddr {
    u_short sa_family;
    char sa_data[14];
};
struct sockaddr_in {
    short sin_family;
    u_short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};
struct hostent {
    char *h_name;
    char **h_aliases;
    short h_addrtype;
    short h_length;
    char **h_addr_list;
};
#define FD_SETSIZE 64
typedef struct fd_set {
    u_int fd_count;
    SOCKET fd_array[FD_SETSIZE];
} fd_set;
struct timeval {
    long tv_sec;
    long tv_usec;
};
#define AF_UNSPEC 0
#define AF_INET 2
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define INADDR_ANY ((u_long)0x00000000)
#define INADDR_NONE ((u_long)0xffffffff)
#define SOL_SOCKET 0xffff
#define SO_REUSEADDR 0x0004
#define SD_RECEIVE 0
#define SD_SEND 1
#define SD_BOTH 2
AKARI_IMPORT int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData) AKARI_NAME(WSAStartup);
AKARI_IMPORT int WINAPI WSACleanup(void) AKARI_NAME(WSACleanup);
AKARI_IMPORT int WINAPI WSAGetLastError(void) AKARI_NAME(WSAGetLastError);
AKARI_IMPORT void WINAPI WSASetLastError(int iError) AKARI_NAME(WSASetLastError);
AKARI_IMPORT SOCKET WINAPI socket(int af, int type, int protocol) AKARI_NAME(socket);
AKARI_IMPORT int WINAPI closesocket(SOCKET s) AKARI_NAME(closesocket);
AKARI_IMPORT int WINAPI bind(SOCKET s, const struct sockaddr *name, int namelen) AKARI_NAME(bind);
AKARI_IMPORT int WINAPI listen(SOCKET s, int backlog) AKARI_NAME(listen);
AKARI_IMPORT SOCKET WINAPI accept(SOCKET s, struct sockaddr *addr, int *addrlen) AKARI_NAME(accept);
AKARI_IMPORT int WINAPI connect(SOCKET s, const struct sockaddr *name, int namelen) AKARI_NAME(connect);
AKARI_IMPORT int WINAPI send(SOCKET s, const char *buf, int len, int flags) AKARI_NAME(send);
AKARI_IMPORT int WINAPI recv(SOCKET s, char *buf, int len, int flags) AKARI_NAME(recv);
AKARI_IMPORT int WINAPI sendto(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen) AKARI_NAME(sendto);
AKARI_IMPORT int WINAPI recvfrom(SOCKET s, char *buf, int len, int flags, struct sockaddr *from, int *fromlen) AKARI_NAME(recvfrom);
AKARI_IMPORT int WINAPI select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout) AKARI_NAME(select);
AKARI_IMPORT int WINAPI ioctlsocket(SOCKET s, long cmd, u_long *argp) AKARI_NAME(ioctlsocket);
AKARI_IMPORT int WINAPI setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen) AKARI_NAME(setsockopt);
AKARI_IMPORT int WINAPI getsockopt(SOCKET s, int level, int optname, char *optval, int *optlen) AKARI_NAME(getsockopt);
AKARI_IMPORT int WINAPI shutdown(SOCKET s, int how) AKARI_NAME(shutdown);
AKARI_IMPORT int WINAPI getpeername(SOCKET s, struct sockaddr *name, int *namelen) AKARI_NAME(getpeername);
AKARI_IMPORT int WINAPI getsockname(SOCKET s, struct sockaddr *name, int *namelen) AKARI_NAME(getsockname);
AKARI_IMPORT struct hostent * WINAPI gethostbyname(const char *name) AKARI_NAME(gethostbyname);
AKARI_IMPORT unsigned long WINAPI inet_addr(const char *cp) AKARI_NAME(inet_addr);
AKARI_IMPORT char * WINAPI inet_ntoa(struct in_addr in) AKARI_NAME(inet_ntoa);
AKARI_IMPORT u_short WINAPI htons(u_short hostshort) AKARI_NAME(htons);
AKARI_IMPORT u_long WINAPI htonl(u_long hostlong) AKARI_NAME(htonl);
AKARI_IMPORT u_short WINAPI ntohs(u_short netshort) AKARI_NAME(ntohs);
AKARI_IMPORT u_long WINAPI ntohl(u_long netlong) AKARI_NAME(ntohl);

#ifdef __cplusplus
}
#endif
#endif
