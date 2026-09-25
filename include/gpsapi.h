/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_GPSAPI_H
#define WCE_GPSAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI GPSOpenDevice(HANDLE hNewLocationData, HANDLE hDeviceStateChange, const WCHAR *szDeviceName, DWORD dwFlags) WCE_LINK(GPSOpenDevice);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI GPSCloseDevice(HANDLE hGPSDevice) WCE_LINK(GPSCloseDevice);
#endif

#ifdef __cplusplus
}
#endif
#endif

