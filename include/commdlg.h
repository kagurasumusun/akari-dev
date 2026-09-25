/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_COMMDLG_H
#define WCE_COMMDLG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagOFNOTIFYW { NMHDR hdr; LPOPENFILENAMEW lpOFN; LPWSTR pszFile; } OFNOTIFYW, *POFNOTIFYW, *LPOFNOTIFYW;
typedef struct tagOFNOTIFYA { NMHDR hdr; LPOPENFILENAMEA lpOFN; LPSTR pszFile; } OFNOTIFYA, *POFNOTIFYA, *LPOFNOTIFYA;
typedef struct tagDEVNAMES { WORD wDriverOffset; WORD wDeviceOffset; WORD wOutputOffset; WORD wDefault; } DEVNAMES, *PDEVNAMES, *LPDEVNAMES;

WCE_IMPORT BOOL WINAPI GetOpenFileNameA(LPOPENFILENAMEA) WCE_LINK(GetOpenFileNameA);
WCE_IMPORT BOOL WINAPI GetOpenFileNameW(LPOPENFILENAMEW) WCE_LINK(GetOpenFileNameW);
WCE_IMPORT BOOL WINAPI GetSaveFileNameW(LPOPENFILENAMEW) WCE_LINK(GetSaveFileNameW);
WCE_IMPORT BOOL WINAPI GetSaveFileNameA(LPOPENFILENAMEA) WCE_LINK(GetSaveFileNameA);
WCE_IMPORT BOOL WINAPI ChooseColor(LPCHOOSECOLOR) WCE_LINK(ChooseColor);
WCE_IMPORT BOOL WINAPI PrintDlg(LPPRINTDLG) WCE_LINK(PrintDlg);
WCE_IMPORT DWORD WINAPI CommDlgExtendedError(VOID) WCE_LINK(CommDlgExtendedError);
WCE_IMPORT BOOL WINAPI PageSetupDlgA(LPPAGESETUPDLGA) WCE_LINK(PageSetupDlgA);
WCE_IMPORT BOOL WINAPI PageSetupDlgW(LPPAGESETUPDLGW) WCE_LINK(PageSetupDlgW);
WCE_IMPORT BOOL WINAPI ChooseFontW(LPCHOOSEFONTW) WCE_LINK(ChooseFontW);

#define GetOpenFileName GetOpenFileNameW
#define GetSaveFileName GetSaveFileNameW
#define PageSetupDlg PageSetupDlgW
#define ChooseFont ChooseFontW
#ifdef __cplusplus
}
#endif
#endif

