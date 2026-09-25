/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINSMCRD_H
#define WCE_WINSMCRD_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSCARD_IO_REQUEST { DWORD dwProtocol; DWORD cbPciLength; } SCARD_IO_REQUEST, *PSCARD_IO_REQUEST, *LPSCARD_IO_REQUEST;
typedef struct tagSCARD_T1_REQUEST { SCARD_IO_REQUEST ioRequest; } SCARD_T1_REQUEST, *PSCARD_T1_REQUEST, *LPSCARD_T1_REQUEST;


#ifdef __cplusplus
}
#endif
#endif

