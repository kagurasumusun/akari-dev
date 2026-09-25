/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_PRSHT_H
#define WCE_PRSHT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPSHNOTIFY { NMHDR hdr; LPARAM lParam; } PSHNOTIFY, *PPSHNOTIFY, *LPPSHNOTIFY;

WCE_IMPORT int WINAPI PropertySheetA(LPCPROPSHEETHEADERA) WCE_LINK(PropertySheetA);
WCE_IMPORT int WINAPI PropertySheetW(LPCPROPSHEETHEADERW) WCE_LINK(PropertySheetW);

#define PropertySheet PropertySheetW
#ifdef __cplusplus
}
#endif
#endif

