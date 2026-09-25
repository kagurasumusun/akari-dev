/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DVP_H
#define WCE_DVP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDDVIDEOPORTCONNECT { DWORD dwSize; DWORD dwPortWidth; GUID guidTypeID; DWORD dwFlags; } DDVIDEOPORTCONNECT, *PDDVIDEOPORTCONNECT, *LPDDVIDEOPORTCONNECT;
typedef struct tagDDVIDEOPORTCAPS { DWORD dwSize; DWORD dwFlags; DWORD dwMaxWidth; DWORD dwMaxVBIWidth; DWORD dwMaxHeight; DWORD dwVideoPortID; DWORD dwCaps; DWORD dwFX; DWORD dwNumAutoFlipSurfaces; DWORD dwAlignVideoPortBoundary; DWORD dwAlignVideoPortPrescaleWidth; DWORD dwAlignVideoPortCropBoundary; DWORD dwAlignVideoPortCropWidth; DWORD dwPreshrinkXStep; DWORD dwPreshrinkYStep; DWORD dwNumVBIAutoFlipSurfaces; DWORD dwNumPreferredAutoflip; WORD wNumFilterTapsX; WORD wNumFilterTapsY; } DDVIDEOPORTCAPS, *PDDVIDEOPORTCAPS, *LPDDVIDEOPORTCAPS;
typedef struct tagDDVIDEOPORTDESC { DWORD dwSize; DWORD dwFieldWidth; DWORD dwVBIWidth; DWORD dwFieldHeight; DWORD dwMicrosecondsPerField; DWORD dwMaxPixelsPerSecond; DWORD dwVideoPortID; DDVIDEOPORTCONNECT VideoPortType; } DDVIDEOPORTDESC, *PDDVIDEOPORTDESC, *LPDDVIDEOPORTDESC;
typedef struct tagDDVIDEOPORTBANDWIDTH { DWORD dwSize; DWORD dwCaps; DWORD dwOverlay; DWORD dwColorkey; DWORD dwYInterpolate; DWORD dwYInterpAndColorkey; } DDVIDEOPORTBANDWIDTH, *PDDVIDEOPORTBANDWIDTH, *LPDDVIDEOPORTBANDWIDTH;
typedef struct tagDDVIDEOPORTSTATUS { DWORD dwSize; BOOL bInUse; DWORD dwFlags; DDVIDEOPORTCONNECT VideoPortType; } DDVIDEOPORTSTATUS, *PDDVIDEOPORTSTATUS, *LPDDVIDEOPORTSTATUS;


#ifdef __cplusplus
}
#endif
#endif

