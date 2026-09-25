/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ICMPAPI_H
#define WCE_ICMPAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HANDLE WINAPI IcmpCreateFile(VOID) WCE_LINK(IcmpCreateFile);
WCE_IMPORT HANDLE WINAPI Icmp6CreateFile(VOID) WCE_LINK(Icmp6CreateFile);
WCE_IMPORT BOOL WINAPI IcmpCloseHandle(HANDLE IcmpHandle) WCE_LINK(IcmpCloseHandle);
WCE_IMPORT DWORD WINAPI IcmpParseReplies(LPVOID ReplyBuffer, DWORD ReplySize) WCE_LINK(IcmpParseReplies);
WCE_IMPORT DWORD WINAPI Icmp6ParseReplies(LPVOID ReplyBuffer, DWORD ReplySize) WCE_LINK(Icmp6ParseReplies);

#ifdef __cplusplus
}
#endif
#endif

