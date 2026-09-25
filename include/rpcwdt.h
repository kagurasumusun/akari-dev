/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RPCWDT_H
#define WCE_RPCWDT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI LPSAFEARRAY_UserFree(unsigned long *, LPSAFEARRAY *) WCE_LINK(LPSAFEARRAY_UserFree);

#ifdef __cplusplus
}
#endif
#endif

