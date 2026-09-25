/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_AVIRIFF_H
#define WCE_AVIRIFF_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagAVISTDINDEX_ENTRY { DWORD dwOffset; DWORD dwSize; } AVISTDINDEX_ENTRY, *PAVISTDINDEX_ENTRY, *LPAVISTDINDEX_ENTRY;
typedef struct tagAVITIMEDINDEX_ENTRY { DWORD dwOffset; DWORD dwSize; DWORD dwDuration; } AVITIMEDINDEX_ENTRY, *PAVITIMEDINDEX_ENTRY, *LPAVITIMEDINDEX_ENTRY;


#ifdef __cplusplus
}
#endif
#endif

