/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_EXTAPI_H
#define WCE_EXTAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLINEOPERATORSTATUS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwPreferredCount; DWORD dwPreferredSize; DWORD dwPreferredOffset; DWORD dwAvailableCount; DWORD dwAvailableSize; DWORD dwAvailableOffset; } LINEOPERATORSTATUS, *PLINEOPERATORSTATUS, *LPLINEOPERATORSTATUS;
typedef struct tagLINEGENERALINFO { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwManufacturerSize; DWORD dwManufacturerOffset; DWORD dwModelSize; DWORD dwModelOffset; DWORD dwRevisionSize; DWORD dwRevisionOffset; DWORD dwSerialNumberSize; DWORD dwSerialNumberOffset; DWORD dwSubscriberNumberSize; DWORD dwSubscriberNumberOffset; } LINEGENERALINFO, *PLINEGENERALINFO, *LPLINEGENERALINFO;


#ifdef __cplusplus
}
#endif
#endif

