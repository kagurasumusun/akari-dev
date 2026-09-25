/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_VPTYPE_H
#define WCE_VPTYPE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagAMVPSIZE { DWORD dwWidth; DWORD dwHeight; } AMVPSIZE, *PAMVPSIZE, *LPAMVPSIZE;
typedef struct tagAMVPDIMINFO { DWORD dwFieldWidth; DWORD dwFieldHeight; DWORD dwVBIWidth; DWORD dwVBIHeight; RECT rcValidRegion; } AMVPDIMINFO, *PAMVPDIMINFO, *LPAMVPDIMINFO;
typedef struct tagAMVPDATAINFO { DWORD dwSize; DWORD dwMicrosecondsPerField; AMVPDIMINFO amvpDimInfo; DWORD dwPictAspectRatioX; DWORD dwPictAspectRatioY; BOOL bEnableDoubleClock; BOOL bEnableVACT; BOOL bDataIsInterlaced; LONG lHalfLinesOdd; BOOL bFieldPolarityInverted; DWORD dwNumLinesInVREF; LONG lHalfLinesEven; DWORD dwReserved1; } AMVPDATAINFO, *PAMVPDATAINFO, *LPAMVPDATAINFO;


#ifdef __cplusplus
}
#endif
#endif

