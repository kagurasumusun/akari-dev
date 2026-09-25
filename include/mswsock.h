/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSWSOCK_H
#define WCE_MSWSOCK_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTRANSMIT_FILE_BUFFERS { LPVOID Head; DWORD HeadLength; LPVOID Tail; DWORD TailLength; } TRANSMIT_FILE_BUFFERS, *PTRANSMIT_FILE_BUFFERS, *LPTRANSMIT_FILE_BUFFERS;
typedef struct tagWSACMSGHDR { SIZE_T cmsg_len; INT cmsg_level; INT cmsg_type; } WSACMSGHDR, *PWSACMSGHDR, *LPWSACMSGHDR;


#ifdef __cplusplus
}
#endif
#endif

