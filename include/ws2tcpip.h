/*
 * ws2tcpip.h -- TCP/IP protocol-specific definitions for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * This is the header Windows CE uses for the getaddrinfo family and the
 * per-socket TCP/IP option structures.  It is a separate header from winsock2.h
 * in the CE SDK and it is separate here for the same reason: an application
 * that includes <ws2tcpip.h> must find ADDRINFO, socklen_t and getaddrinfo
 * there.  Before this file existed, <ws2tcpip.h> resolved to the host
 * toolchain's header instead, which collided with the kit's own definitions.
 *
 * The base socket types -- SOCKET, struct sockaddr, struct in_addr,
 * struct in6_addr -- come from winsock2.h.
 */
#ifndef AKARI_WCE_WS2TCPIP_H
#define AKARI_WCE_WS2TCPIP_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <winsock2.h>

#ifndef _WS2TCPIP_
#define _WS2TCPIP_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINSOCK_API_LINKAGE
#define WINSOCK_API_LINKAGE AKARI_DLLIMPORT
#endif

typedef int socklen_t;

/* --------------------------------------------------- address information */

struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    size_t           ai_addrlen;
    char            *ai_canonname;
    struct sockaddr *ai_addr;
    struct addrinfo *ai_next;
};
typedef struct addrinfo ADDRINFO, FAR *LPADDRINFO;

#define AI_PASSIVE      0x00000001
#define AI_CANONNAME    0x00000002
#define AI_NUMERICHOST  0x00000004

#define NI_NOFQDN       0x01
#define NI_NUMERICHOST  0x02
#define NI_NAMEREQD     0x04
#define NI_NUMERICSERV  0x08
#define NI_DGRAM        0x10

#define EAI_AGAIN       WSATRY_AGAIN
#define EAI_BADFLAGS    WSAEINVAL
#define EAI_FAIL        WSANO_RECOVERY
#define EAI_FAMILY      WSAEAFNOSUPPORT
#define EAI_MEMORY      WSA_NOT_ENOUGH_MEMORY
#define EAI_NONAME      WSAHOST_NOT_FOUND
#define EAI_SERVICE     WSATYPE_NOT_FOUND
#define EAI_SOCKTYPE    WSAESOCKTNOSUPPORT

/* ------------------------------------------- per-socket TCP/IP structures */

struct in_pktinfo {
    IN_ADDR ipi_addr;
    UINT    ipi_ifindex;
};
typedef struct in_pktinfo IN_PKTINFO;

struct in6_pktinfo {
    IN6_ADDR ipi6_addr;
    UINT     ipi6_ifindex;
};
typedef struct in6_pktinfo IN6_PKTINFO;

struct ipv6_mreq {
    struct in6_addr ipv6mr_multiaddr;
    unsigned int    ipv6mr_interface;
};
typedef struct ipv6_mreq IPV6_MREQ;

/* The pre-RFC2553 IPv6 socket address, retained so sockaddr_gen can hold one. */
struct sockaddr_in6_old {
    short           sin6_family;
    u_short         sin6_port;
    u_long          sin6_flowinfo;
    struct in6_addr sin6_addr;
};

typedef union sockaddr_gen {
    struct sockaddr         Address;
    struct sockaddr_in      AddressIn;
    struct sockaddr_in6_old AddressIn6;
} sockaddr_gen;

struct _INTERFACE_INFO {
    u_long      iiFlags;
    sockaddr_gen iiAddress;
    sockaddr_gen iiBroadcastAddress;
    sockaddr_gen iiNetmask;
};
typedef struct _INTERFACE_INFO INTERFACE_INFO, FAR *LPINTERFACE_INFO;

#define IFF_UP            0x00000001
#define IFF_BROADCAST     0x00000002
#define IFF_LOOPBACK      0x00000004
#define IFF_POINTTOPOINT  0x00000008
#define IFF_MULTICAST     0x00000010

/* Socket option numbers, from the CE branch of the conditional at
 * ws2tcpip.h:83.  The reference has two sets: one under #ifndef UNDER_CE with
 * the familiar BSD numbering, and one in the #else arm with CE's own.  UNDER_CE
 * is defined on CE, so the #else arm is the one that applies -- IP_MULTICAST_IF
 * is 2 there, not 9, and not the 0x24 a desktop header would give.  These were
 * originally written from desktop values and were all wrong.
 *
 * IP_OPTIONS is outside the conditional, so it is 1 on both. */
#define IP_OPTIONS         1
#define IP_MULTICAST_IF    2
#define IP_MULTICAST_TTL   3
#define IP_MULTICAST_LOOP  4
#define IP_ADD_MEMBERSHIP  5
#define IP_DROP_MEMBERSHIP 6
#define IP_TTL             7
#define IP_TOS             8
#define IP_HDRINCL         9

/* ------------------------------------------------------- prototypes */

WINSOCK_API_LINKAGE int WINAPI getaddrinfo(const char *nodename,
    const char *servname, const struct addrinfo *hints, struct addrinfo **res);
WINSOCK_API_LINKAGE int WINAPI getnameinfo(const struct sockaddr *sa,
    socklen_t salen, char *host, DWORD hostlen, char *serv, DWORD servlen,
    int flags);
WINSOCK_API_LINKAGE void WINAPI freeaddrinfo(struct addrinfo *ai);

#ifdef __cplusplus
}
#endif

#endif /* _WS2TCPIP_ */
#endif /* AKARI_WCE_WS2TCPIP_H */
