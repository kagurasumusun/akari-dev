/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RECOG_H
#define WCE_RECOG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHWXRESULTS { USHORT indxBox; WCHAR rgChar[1]; } HWXRESULTS, *PHWXRESULTS, *LPHWXRESULTS;
typedef struct tagHWXGUIDE { UINT cHorzBox; UINT cVertBox; INT xOrigin; INT yOrigin; UINT cxBox; UINT cyBox; UINT cxOffset; UINT cyOffset; UINT cxWriting; UINT cyWriting; UINT cyMid; UINT cyBase; UINT nDir; } HWXGUIDE, *PHWXGUIDE, *LPHWXGUIDE;

WCE_IMPORT BOOL WINAPI HwxConfig() WCE_LINK(HwxConfig);

#ifdef __cplusplus
}
#endif
#endif

