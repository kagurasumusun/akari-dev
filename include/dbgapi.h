/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DBGAPI_H
#define WCE_DBGAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDBGPARAM { WCHAR lpszName[32]; WCHAR rglpszZones[16][32]; ULONG ulZoneMask; } DBGPARAM, *PDBGPARAM, *LPDBGPARAM;

WCE_IMPORT void WINAPIV NKDbgPrintfW(LPCWSTR lpszFmt, ...) WCE_LINK(NKDbgPrintfW);
WCE_IMPORT void WINAPI WriteDebugLED(WORD wIndex, DWORD dwPattern) WCE_LINK(WriteDebugLED);
WCE_IMPORT BOOL WINAPI RegisterDbgZones(HMODULE hMod, LPDBGPARAM lpdbgparam) WCE_LINK(RegisterDbgZones);

#define NKDbgPrintf NKDbgPrintfW
#ifdef __cplusplus
}
#endif
#endif

