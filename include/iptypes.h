/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IPTYPES_H
#define WCE_IPTYPES_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagIP_ADDRESS_STRING { char String[4 * 4]; } IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, *LPIP_ADDRESS_STRING;


#ifdef __cplusplus
}
#endif
#endif

