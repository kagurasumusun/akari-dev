/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_GETDEVICEUNIQUEID_H
#define WCE_GETDEVICEUNIQUEID_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI GetDeviceUniqueID(LPBYTE pbApplicationData, DWORD cbApplicationData, DWORD dwDeviceIDVersion, LPBYTE pbDeviceIDOutput, DWORD *pcbDeviceIDOutput) WCE_LINK(GetDeviceUniqueID);
#endif

#ifdef __cplusplus
}
#endif
#endif

