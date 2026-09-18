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
#include "Winbase.h"   /* SYSTEMTIME (Winbase.h declares it) */

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


/* ee483540 "GPS_MAX_..." (Windows Embedded CE 6.0 and later):
 * GPS_MAX_SATELLITES = 12 */
#define GPS_MAX_SATELLITES 12

/* ee484992 "GPS_POSITION" (Windows Embedded CE 6.0 and later) prints
 * the full struct; the GPS_FIX_* enums above are its member types. */
typedef struct _GPS_POSITION {
  DWORD dwVersion;
  DWORD dwSize;
  DWORD dwValidFields;
  DWORD dwFlags;
  SYSTEMTIME stUTCTime;
  double dblLatitude;
  double dblLongitude;
  float  flSpeed;
  float  flHeading;
  double dblMagneticVariation;
  float  flAltitudeWRTSeaLevel;
  float  flAltitudeWRTEllipsoid;
  GPS_FIX_QUALITY     FixQuality;
  GPS_FIX_TYPE        FixType;
  GPS_FIX_SELECTION   SelectionType;
  float flPositionDilutionOfPrecision;
  float flHorizontalDilutionOfPrecision;
  float flVerticalDilutionOfPrecision;
  DWORD dwSatelliteCount;
  DWORD rgdwSatellitesUsedPRNs[GPS_MAX_SATELLITES];
  DWORD dwSatellitesInView;
  DWORD rgdwSatellitesInViewPRNs[GPS_MAX_SATELLITES];
  DWORD rgdwSatellitesInViewElevation[GPS_MAX_SATELLITES];
  DWORD rgdwSatellitesInViewAzimuth[GPS_MAX_SATELLITES];
  DWORD rgdwSatellitesInViewSignalToNoiseRatio[GPS_MAX_SATELLITES];
} GPS_POSITION, *PGPS_POSITION;

/* GPS_DEVICE: no "GPS_DEVICE Structure" page prints the members
 * anywhere in the corpus (checked 2026-09-18); carried opaque so the
 * GPSGetDeviceState print can be declared verbatim. */
typedef struct _GPS_DEVICE GPS_DEVICE, *PGPS_DEVICE;

/* ee483702 GPSGetDeviceState: print `DWORD GPSGetDeviceState(
GPS_DEVICE *pGPSDevice
);`
 * (Windows Embedded CE 6.0 and later; Link Library: Gpsapi.lib) */
AKARI_CE_IMPORT DWORD GPSGetDeviceState(GPS_DEVICE *pGPSDevice) AKARI_CE_NAME(GPSGetDeviceState);

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

/* ee483312 GPSGetPosition: print `DWORD GPSGetPosition(
HANDLE hGPSDevice,
GPS_POSITION *pGPSPosition,
DWORD dwMaximumAge,
DWORD dwFlags
);`
 * (Windows Embedded CE 6.0 and later; Link Library: Gpsapi.lib) */
AKARI_CE_IMPORT DWORD GPSGetPosition(HANDLE hGPSDevice, GPS_POSITION *pGPSPosition, DWORD dwMaximumAge, DWORD dwFlags) AKARI_CE_NAME(GPSGetPosition);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_GPSAPI_H */
