/*
 * Gpsapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: gpsapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_GPSAPI_H
#define AKARI_GPSAPI_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee484122 GPS_FIX_TYPE: page print
 * typedef enum { GPS_FIX_UNKNOWN = 0, GPS_FIX_2D, GPS_FIX_3D } GPS_FIX_TYPE;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    GPS_FIX_UNKNOWN = 0,
    GPS_FIX_2D,
    GPS_FIX_3D
} GPS_FIX_TYPE;

/* ee485759 GPS_FIX_QUALITY: page print
 * typedef enum { GPS_FIX_QUALITY_UNKNOWN = 0, GPS_FIX_QUALITY_GPS, GPS_FIX_QUALITY_DGPS } GPS_FIX_QUALITY;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    GPS_FIX_QUALITY_UNKNOWN = 0,
    GPS_FIX_QUALITY_GPS,
    GPS_FIX_QUALITY_DGPS
} GPS_FIX_QUALITY;

/* ee487278 GPS_FIX_SELECTION: page print
 * typedef enum { GPS_FIX_SELECTION_UNKNOWN = 0, GPS_FIX_SELECTION_AUTO, GPS_FIX_SELECTION_MANUAL } GPS_FIX_SELECTION;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    GPS_FIX_SELECTION_UNKNOWN = 0,
    GPS_FIX_SELECTION_AUTO,
    GPS_FIX_SELECTION_MANUAL
} GPS_FIX_SELECTION;


/* ee483557 GPSCloseDevice: print `DWORD GPSCloseDevice(
HANDLE hGPSDevice
);`
 * (Windows Embedded CE 6.0 and later; Link Library: Gpsapi.lib) */
AKARI_CE_IMPORT DWORD GPSCloseDevice(HANDLE hGPSDevice) AKARI_CE_NAME(GPSCloseDevice);

/* ee485975 GPSOpenDevice: print `HANDLE GPSOpenDevice(
HANDLE hNewLocationData,
HANDLE hDeviceStateChange,
const WCHAR *szDeviceName,
DWORD dwFlags
);`
 * (Windows Embedded CE 6.0 and later; Link Library: Gpsapi.lib) */
AKARI_CE_IMPORT HANDLE GPSOpenDevice(HANDLE hNewLocationData, HANDLE hDeviceStateChange, const WCHAR *szDeviceName, DWORD dwFlags) AKARI_CE_NAME(GPSOpenDevice);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_GPSAPI_H */
