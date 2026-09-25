/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FSDMGR_H
#define WCE_FSDMGR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFSD_DISK_INFO { DWORD cSectors; DWORD cbSector; DWORD cCylinders; DWORD cHeadsPerCylinder; DWORD cSectorsPerTrack; DWORD dwFlags; } FSD_DISK_INFO, *PFSD_DISK_INFO, *LPFSD_DISK_INFO;
typedef struct tagFSD_BUFFER_INFO { PBYTE pBuffer; DWORD cbBuffer; } FSD_BUFFER_INFO, *PFSD_BUFFER_INFO, *LPFSD_BUFFER_INFO;
typedef struct tagFSD_SCATTER_GATHER_RESULTS { DWORD dwFlags; DWORD cSectorsTransferred; } FSD_SCATTER_GATHER_RESULTS, *PFSD_SCATTER_GATHER_RESULTS, *LPFSD_SCATTER_GATHER_RESULTS;


#ifdef __cplusplus
}
#endif
#endif

