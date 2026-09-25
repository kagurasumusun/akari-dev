/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SOFTPUB_H
#define WCE_SOFTPUB_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDRIVER_VER_MAJORMINOR { DWORD dwMajor; DWORD dwMinor; } DRIVER_VER_MAJORMINOR, *PDRIVER_VER_MAJORMINOR, *LPDRIVER_VER_MAJORMINOR;


#ifdef __cplusplus
}
#endif
#endif

