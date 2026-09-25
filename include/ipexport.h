/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IPEXPORT_H
#define WCE_IPEXPORT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTCP_RESERVE_PORT_RANGE { USHORT UpperRange; USHORT LowerRange; } TCP_RESERVE_PORT_RANGE, *PTCP_RESERVE_PORT_RANGE, *LPTCP_RESERVE_PORT_RANGE;
typedef struct tagIP_ADAPTER_ORDER_MAP { ULONG NumAdapters; ULONG AdapterOrder[1]; } IP_ADAPTER_ORDER_MAP, *PIP_ADAPTER_ORDER_MAP, *LPIP_ADAPTER_ORDER_MAP;


#ifdef __cplusplus
}
#endif
#endif

