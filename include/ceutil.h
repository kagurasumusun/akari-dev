/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CEUTIL_H
#define WCE_CEUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSVCINFO_GENERIC { DWORD cbSize; DWORD Flags; DWORD ProfileId; BOOL Enabled; } SVCINFO_GENERIC, *PSVCINFO_GENERIC, *LPSVCINFO_GENERIC;
typedef struct tagSVCINFO_SYNC { DWORD cbSize; DWORD Flags; DWORD ProfileId; BOOL Enabled; LPTSTR DisplayName; LPTSTR ProgId; } SVCINFO_SYNC, *PSVCINFO_SYNC, *LPSVCINFO_SYNC;


#ifdef __cplusplus
}
#endif
#endif

