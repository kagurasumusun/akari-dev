/*
 * icmpapi.h -- ICMP helper functions for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * The CE SDK declares the four ICMP helpers in this header, separate from
 * iphlpapi.h, even though they are exported by the same iphlpapi.dll.  They
 * were previously declared in the kit's iphlpapi.h; they are declared here now,
 * where CE puts them, so that #include <icmpapi.h> finds them.
 *
 * IP_OPTION_INFORMATION, ICMP_ECHO_REPLY and the address types live in the
 * kit's iphlpapi.h, which is why this header includes it.
 */
#ifndef AKARI_WCE_ICMPAPI_H
#define AKARI_WCE_ICMPAPI_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <iphlpapi.h>

#ifndef _ICMPAPI_
#define _ICMPAPI_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IPHLPAPI
#define IPHLPAPI AKARI_DLLIMPORT
#endif

IPHLPAPI HANDLE WINAPI IcmpCreateFile(VOID);
IPHLPAPI BOOL   WINAPI IcmpCloseHandle(HANDLE IcmpHandle);
IPHLPAPI DWORD  WINAPI IcmpSendEcho(HANDLE IcmpHandle, ULONG DestinationAddress,
    LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions,
    LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
IPHLPAPI DWORD  WINAPI IcmpParseReplies(LPVOID ReplyBuffer, DWORD ReplySize);

#ifdef __cplusplus
}
#endif

#endif /* _ICMPAPI_ */
#endif /* AKARI_WCE_ICMPAPI_H */
