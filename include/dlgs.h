/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DLGS_H
#define WCE_DLGS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCRGB { BYTE bRed; BYTE bGreen; BYTE bBlue; BYTE bExtra; } CRGB, *PCRGB, *LPCRGB;


#ifdef __cplusplus
}
#endif
#endif

