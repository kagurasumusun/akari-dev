/*
 * winsock.h -- Winsock 1.1 entry point for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * CE ships two socket libraries: winsock.dll, the 1.1 interface, and ws2.dll,
 * the 2.0 interface.  An application links against one or the other, never
 * both.
 *
 * The two share their entire declaration set.  Every one of the 31 exports of
 * winsock.dll -- WSAStartup, WSACleanup, WSAIoctl, __WSAFDIsSet, socket, bind,
 * connect, listen, accept, send, sendto, recv, recvfrom, select, shutdown,
 * closesocket, getsockname, getpeername, getsockopt, setsockopt, ioctlsocket,
 * gethostbyname, gethostbyaddr, gethostname, sethostname, inet_addr,
 * inet_ntoa, htonl, htons, ntohl and ntohs -- is declared in winsock2.h, with
 * the same prototypes and the same calling convention, which on CE is __cdecl
 * on every CPU.
 *
 * This header therefore declares nothing of its own.  It exists so that
 * #include <winsock.h> works for code written against the 1.1 interface, and
 * pulls in the declarations from winsock2.h.  The _WINSOCKAPI_ guard is the
 * one winsock2.h sets, so including both is safe: whichever comes first
 * provides the types and the other contributes nothing.
 *
 * Which library an application binds to is decided at link time by whether
 * winsock.lib or ws2.lib is on the link line, not by this header.
 */
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <winsock2.h>
