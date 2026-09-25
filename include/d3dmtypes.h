/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_D3DMTYPES_H
#define WCE_D3DMTYPES_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagD3DMVIEWPORT { ULONG X; ULONG Y; ULONG Width; ULONG Height; float MinZ; float MaxZ; } D3DMVIEWPORT, *PD3DMVIEWPORT, *LPD3DMVIEWPORT;
typedef struct tagD3DMCLIPSTATUS { ULONG ClipUnion; ULONG ClipIntersection; } D3DMCLIPSTATUS, *PD3DMCLIPSTATUS, *LPD3DMCLIPSTATUS;
typedef struct tagD3DMLOCKED_RECT { INT Pitch; void* pBits; } D3DMLOCKED_RECT, *PD3DMLOCKED_RECT, *LPD3DMLOCKED_RECT;


#ifdef __cplusplus
}
#endif
#endif

