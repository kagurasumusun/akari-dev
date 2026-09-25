/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_LFAPI_H
#define WCE_LFAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLOCATION_REPORT_BASE { DWORD version; GUID type; DWORD size; GUID plugin; FILETIME creationTime; DWORD flags; } LOCATION_REPORT_BASE, *PLOCATION_REPORT_BASE, *LPLOCATION_REPORT_BASE;
typedef struct tagLOCATION_REPORT_LATLONG { LOCATION_REPORT_BASE base; DWORD validFields; DOUBLE latitude; DOUBLE longitude; DOUBLE altitudeWRTSeaLevel; DOUBLE speed; DOUBLE heading; DOUBLE accuracy; } LOCATION_REPORT_LATLONG, *PLOCATION_REPORT_LATLONG, *LPLOCATION_REPORT_LATLONG;
typedef struct tagLOCATION_REPORT_ADDRESS { LOCATION_REPORT_BASE base; DWORD countryRegionOffset; DWORD administrativeDivisionOffset; DWORD cityOffset; DWORD postalCodeOffset; DWORD addressLineOffset; DWORD descriptionOffset; BYTE data[1]; } LOCATION_REPORT_ADDRESS, *PLOCATION_REPORT_ADDRESS, *LPLOCATION_REPORT_ADDRESS;
typedef struct tagLOCATION_REPORT_BUILDING { LOCATION_REPORT_BASE base; DWORD buildingNameOffset; DWORD floorOffset; DWORD roomOffset; DWORD descriptionOffset; BYTE data[1]; } LOCATION_REPORT_BUILDING, *PLOCATION_REPORT_BUILDING, *LPLOCATION_REPORT_BUILDING;
typedef struct tagLOCATION_SERVICE_STATE { DWORD serviceState; DWORD numLoadedProviders; DWORD numLoadedResolvers; DWORD numActiveProviders; DWORD numActiveResolvers; } LOCATION_SERVICE_STATE, *PLOCATION_SERVICE_STATE, *LPLOCATION_SERVICE_STATE;


#ifdef __cplusplus
}
#endif
#endif

