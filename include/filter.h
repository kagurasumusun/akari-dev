/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FILTER_H
#define WCE_FILTER_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFILTERREGION { ULONG idChunk; ULONG cwcStart; ULONG cwcExtent; } FILTERREGION, *PFILTERREGION, *LPFILTERREGION;


#ifdef __cplusplus
}
#endif
#endif

