/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WS2SPI_H
#define WCE_WS2SPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWSATHREADID { HANDLE ThreadHandle; DWORD_PTR Reserved; } WSATHREADID, *PWSATHREADID, *LPWSATHREADID;

WCE_IMPORT INT WINAPI NSPStartup(LPGUID lpProviderId, LPNSP_ROUTINE lpnspRoutines) WCE_LINK(NSPStartup);

#ifdef __cplusplus
}
#endif
#endif

