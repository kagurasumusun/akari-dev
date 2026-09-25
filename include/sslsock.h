/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SSLSOCK_H
#define WCE_SSLSOCK_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSSLPROTOCOL { DWORD dwProtocol; DWORD dwVersion; DWORD dwFlags; } SSLPROTOCOL, *PSSLPROTOCOL, *LPSSLPROTOCOL;
typedef struct tagSSLPROTOCOLS { DWORD dwCount; SSLPROTOCOL ProtocolList[1]; } SSLPROTOCOLS, *PSSLPROTOCOLS, *LPSSLPROTOCOLS;
typedef struct tagSSLCIPHERS { DWORD dwProtocol; DWORD dwCount; DWORD CipherList[1]; } SSLCIPHERS, *PSSLCIPHERS, *LPSSLCIPHERS;


#ifdef __cplusplus
}
#endif
#endif

