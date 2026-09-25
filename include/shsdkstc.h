/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SHSDKSTC_H
#define WCE_SHSDKSTC_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFILECHANGEINFO { DWORD cbSize; LONG wEventId; ULONG uFlags; DWORD dwItem1; DWORD dwItem2; DWORD dwAttributes; FILETIME ftModified; ULONG nFileSize; } FILECHANGEINFO, *PFILECHANGEINFO, *LPFILECHANGEINFO;


#ifdef __cplusplus
}
#endif
#endif

