/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_LOCKMGRTYPES_H
#define WCE_LOCKMGRTYPES_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFILELOCKSTATE { DWORD dwPosLow; DWORD dwPosHigh; DWORD dwAccess; LPCRITICAL_SECTION lpcs; BOOL fTerminal; HANDLE hevUnlock; DWORD cQueue; PVOID pvLockContainer; } FILELOCKSTATE, *PFILELOCKSTATE, *LPFILELOCKSTATE;


#ifdef __cplusplus
}
#endif
#endif

