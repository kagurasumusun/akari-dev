/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_QOS_H
#define WCE_QOS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagQOS_OBJECT_HDR { ULONG ObjectType; ULONG ObjectLength; } QOS_OBJECT_HDR, *PQOS_OBJECT_HDR, *LPQOS_OBJECT_HDR;
typedef struct tagQOS_SD_MODE { QOS_OBJECT_HDR ObjectHdr; ULONG ShapeDiscardMode; } QOS_SD_MODE, *PQOS_SD_MODE, *LPQOS_SD_MODE;
typedef struct tagQOS_SHAPING_RATE { QOS_OBJECT_HDR ObjectHdr; ULONG ShapingRate; } QOS_SHAPING_RATE, *PQOS_SHAPING_RATE, *LPQOS_SHAPING_RATE;


#ifdef __cplusplus
}
#endif
#endif

