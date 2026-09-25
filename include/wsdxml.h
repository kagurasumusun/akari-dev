/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WSDXML_H
#define WCE_WSDXML_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWSD_DURATION { BOOL isPositive; ULONG year; ULONG month; ULONG day; ULONG hour; ULONG minute; ULONG second; ULONG millisecond; } WSD_DURATION, *PWSD_DURATION, *LPWSD_DURATION;


#ifdef __cplusplus
}
#endif
#endif

