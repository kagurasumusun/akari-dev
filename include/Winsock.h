/*
 * Winsock.h -- the header spelling the official CE pages print for
 * the Winsock 1.1 surface.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * 36 official pages name Winsock.h in their Header row. Every
 * declaration they attribute to it is already carried by this tree (a
 * few are recorded there as held, with the reason); each is listed
 * below with its page id and the header that holds it. Nothing is
 * re-declared here: a second copy of a typedef, struct or prototype is
 * a second thing to keep in step with the pages, and the pages are the
 * only evidence this tree accepts.
 *
 * A consumer that writes `#include <Winsock.h>` -- the spelling the
 * documentation uses -- therefore gets exactly the declarations
 * the documentation attributes to it.
 *
 *   accept (wcesdkraccept_function) -- Winsock2.h
 *       Windows CE OS
 *   bind (wcesdkrbind) -- Winsock2.h
 *       Windows CE OS
 *   CEBLOB (wcesdkrCEBLOB) -- Windbase.h
 *       Windows CE OS
 *   connect (wcesdkrconnect_function) -- Winsock2.h
 *       Windows CE OS
 *   gethostbyaddr (wcesdkrgethostbyaddr) -- Winsock2.h
 *       Windows CE OS
 *   gethostbyname (wcesdkrgethostbyname) -- Winsock2.h
 *       Windows CE OS
 *   gethostname (wcesdkrgethostname) -- Winsock2.h
 *       Windows CE OS
 *   getpeername (wcesdkrgetpeername) -- Winsock2.h
 *       Windows CE OS
 *   getsockname (wcesdkrgetsockname) -- Winsock2.h
 *       Windows CE OS
 *   getsockopt (wcesdkrgetsockopt) -- Winsock2.h
 *       Windows CE OS
 *   hostent (wcesdkrHOSTENT) -- Winsock2.h
 *       Windows CE OS
 *   htonl (wcesdkrhtonl) -- Winsock2.h
 *       Windows CE OS
 *   htons (wcesdkrhtons) -- Winsock2.h
 *       Windows CE OS
 *   IN_ADDR (wcesdkrIN_ADDR) -- Winsock2.h
 *       Windows CE OS
 *   inet_addr (wcesdkrinet_addr) -- Winsock2.h
 *       Windows CE OS
 *   inet_ntoa (wcesdkrinet_ntoa) -- Winsock2.h
 *       Windows CE OS
 *   ioctlsocket (wcesdkrioctlsocket) -- Winsock2.h
 *       Windows CE OS
 *   LINGER (wcesdkrLINGER) -- Winsock2.h (declared as `linger`)
 *       Windows CE OS
 *   listen (wcesdkrlisten_function) -- Winsock2.h
 *       Windows CE OS
 *   ntohl (wcesdkrntohl) -- Winsock2.h
 *       Windows CE OS
 *   ntohs (wcesdkrntohs) -- Winsock2.h
 *       Windows CE OS
 *   recv (wcesdkrrecv) -- Winsock2.h
 *       Windows CE OS
 *   recvfrom (wcesdkrrecvfrom) -- Winsock2.h
 *       Windows CE OS
 *   select (wcesdkrselect) -- Winsock2.h
 *       Windows CE OS
 *   send (wcesdkrsend) -- Winsock2.h
 *       Windows CE OS
 *   sendto (wcesdkrsendto) -- Winsock2.h
 *       Windows CE OS
 *   shutdown (wcesdkrshutdown_function) -- Winsock2.h
 *       Windows CE OS
 *   sockaddr (wcesdkrSOCKADDR) -- Iphlpapi.h (+ Winsock2.h, Ws2spi.h,
 *   Ws2tcpip.h)
 *       Windows CE OS
 *   SOCKADDR_IN (wcesdkrSOCKADDR_IN) -- Winsock2.h (declared as
 *   `sockaddr_in`)
 *       Windows CE OS
 *   sockaddr_irda (wcesdkrsockaddr_irda) -- Winsock2.h
 *       Windows CE OS
 *   socket (wcesdkrsocket) -- Winsock2.h
 *       Windows CE OS
 *   WSACleanup (wcesdkrWSACleanup) -- Winsock2.h
 *       Windows CE OS
 *   WSADATA (wcesdkrWSADATA) -- Winsock2.h
 *       Windows CE OS
 *   WSAGetLastError (wcesdkrWSAGetLastError) -- Winsock2.h
 *       Windows CE OS
 *   WSASetLastError (wcesdkrWSASetLastError) -- Winsock2.h
 *       Windows CE OS
 *   WSAStartup (wcesdkrWSAStartup) -- Winsock2.h
 *       Windows CE OS
 */

#ifndef AKARI_WINSOCK_H_
#define AKARI_WINSOCK_H_

#include "Winsock2.h"
#include "Windbase.h"
#include "Iphlpapi.h"

#endif /* AKARI_WINSOCK_H_ */
