/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_NLED_H
#define WCE_NLED_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI NLedGetDeviceInfo(UINT nInfoId, void *pOutput) WCE_LINK(NLedGetDeviceInfo);
WCE_IMPORT BOOL WINAPI NLedSetDevice(UINT nDeviceId, void *pInput) WCE_LINK(NLedSetDevice);

#ifdef __cplusplus
}
#endif
#endif

