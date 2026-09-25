/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_USP10_H
#define WCE_USP10_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagGOFFSET { LONG du; LONG dv; } GOFFSET, *PGOFFSET, *LPGOFFSET;
typedef struct tagSCRIPT_FONTPROPERTIES { int cBytes; WORD wgBlank; WORD wgDefault; WORD wgInvalid; WORD wgKashida; int iKashidaWidth; } SCRIPT_FONTPROPERTIES, *PSCRIPT_FONTPROPERTIES, *LPSCRIPT_FONTPROPERTIES;
typedef struct tagSCRIPT_TABDEF { int cTabStops; int iScale; int *pTabStops; int iTabOrigin; } SCRIPT_TABDEF, *PSCRIPT_TABDEF, *LPSCRIPT_TABDEF;

#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI ScriptLayout(int cRuns, const BYTE *pbLevel, int *piVisualToLogical, int *piLogicalToVisual) WCE_LINK(ScriptLayout);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI ScriptIsComplex(const WCHAR *pwcInChars, int cInChars, DWORD dwFlags) WCE_LINK(ScriptIsComplex);
#endif

#ifdef __cplusplus
}
#endif
#endif

