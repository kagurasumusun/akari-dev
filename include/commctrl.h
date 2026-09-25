/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_COMMCTRL_H
#define WCE_COMMCTRL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagINITCOMMONCONTROLSEX { DWORD dwSize; DWORD dwICC; } INITCOMMONCONTROLSEX, *PINITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;
typedef struct tagNMMOUSE { NMHDR hdr; DWORD dwItemSpec; DWORD dwItemData; POINT pt; } NMMOUSE, *PNMMOUSE, *LPNMMOUSE;
typedef struct tagNMKEY { NMHDR hdr; WORD wVKey; UINT flags; } NMKEY, *PNMKEY, *LPNMKEY;
typedef struct tagNMCUSTOMDRAW { NMHDR hdr; DWORD dwDrawStage; HDC hdc; RECT rc; DWORD dwItemSpec; UINT uItemState; LPARAM lItemlParam; } NMCUSTOMDRAW, *PNMCUSTOMDRAW, *LPNMCUSTOMDRAW;
typedef struct tagNMTTCUSTOMDRAW { NMCUSTOMDRAW nmcd; UINT uDrawFlags; } NMTTCUSTOMDRAW, *PNMTTCUSTOMDRAW, *LPNMTTCUSTOMDRAW;
typedef struct tagIMAGEINFO { HBITMAP hbmImage; HBITMAP hbmMask; int Unused1; int Unused2; RECT rcImage; } IMAGEINFO, *PIMAGEINFO, *LPIMAGEINFO;
typedef struct tagHDHITTESTINFO { POINT pt; UINT flags; int iItem; } HDHITTESTINFO, *PHDHITTESTINFO, *LPHDHITTESTINFO;
typedef struct tagNMHDDISPINFOW { NMHDR hdr; int iItem; UINT mask; LPWSTR pszText; int cchTextMax; int iImage; LPARAM lParam; } NMHDDISPINFOW, *PNMHDDISPINFOW, *LPNMHDDISPINFOW;
typedef struct tagNMHDDISPINFOA { NMHDR hdr; int iItem; UINT mask; LPSTR pszText; int cchTextMax; int iImage; LPARAM lParam; } NMHDDISPINFOA, *PNMHDDISPINFOA, *LPNMHDDISPINFOA;
typedef struct tagTBADDBITMAP { HINSTANCE hInst; UINT nID; } TBADDBITMAP, *PTBADDBITMAP, *LPTBADDBITMAP;
typedef struct tagTBREPLACEBITMAP { HINSTANCE hInstOld; UINT nIDOld; HINSTANCE hInstNew; UINT nIDNew; int nButtons; } TBREPLACEBITMAP, *PTBREPLACEBITMAP, *LPTBREPLACEBITMAP;
typedef struct tagTBBUTTONINFOA { UINT cbSize; DWORD dwMask; int idCommand; int iImage; BYTE fsState; BYTE fsStyle; WORD cx; DWORD lParam; LPSTR pszText; int cchText; } TBBUTTONINFOA, *PTBBUTTONINFOA, *LPTBBUTTONINFOA;
typedef struct tagTBBUTTONINFOW { UINT cbSize; DWORD dwMask; int idCommand; int iImage; BYTE fsState; BYTE fsStyle; WORD cx; DWORD lParam; LPWSTR pszText; int cchText; } TBBUTTONINFOW, *PTBBUTTONINFOW, *LPTBBUTTONINFOW;
typedef struct tagNMREBAR { NMHDR hdr; UINT uBand; UINT wID; UINT cyChild; UINT cyBand; } NMREBAR, *PNMREBAR, *LPNMREBAR;
typedef struct tagNMRBAUTOSIZE { NMHDR hdr; BOOL fChanged; RECT rcTarget; RECT rcActual; } NMRBAUTOSIZE, *PNMRBAUTOSIZE, *LPNMRBAUTOSIZE;
typedef struct tagRBHITTESTINFO { POINT pt; UINT flags; int iBand; } RBHITTESTINFO, *PRBHITTESTINFO, *LPRBHITTESTINFO;
typedef struct tagCOMMANDBANDSRESTOREINFO { UINT cbSize; UINT wID; UINT fStyle; UINT cxRestored; BOOL fMaximized; } COMMANDBANDSRESTOREINFO, *PCOMMANDBANDSRESTOREINFO, *LPCOMMANDBANDSRESTOREINFO;
typedef struct tagUDACCEL { UINT nSec; UINT nInc; } UDACCEL, *PUDACCEL, *LPUDACCEL;
typedef struct tagNMUPDOWN { NMHDR hdr; int iPos; int iDelta; } NMUPDOWN, *PNMUPDOWN, *LPNMUPDOWN;
typedef struct tagPBRANGE { int iLow; int iHigh; } PBRANGE, *PPBRANGE, *LPPBRANGE;
typedef struct tagLVFINDINFOA { UINT flags; LPCSTR psz; LPARAM lParam; POINT pt; UINT vkDirection; } LVFINDINFOA, *PLVFINDINFOA, *LPLVFINDINFOA;
typedef struct tagLVFINDINFOW { UINT flags; LPCWSTR psz; LPARAM lParam; POINT pt; UINT vkDirection; } LVFINDINFOW, *PLVFINDINFOW, *LPLVFINDINFOW;
typedef struct tagLVBKIMAGEA { ULONG ulFlags; HBITMAP hbm; LPSTR pszImage; UINT cchImageMax; int xOffsetPercent; int yOffsetPercent; } LVBKIMAGEA, *PLVBKIMAGEA, *LPLVBKIMAGEA;
typedef struct tagLVBKIMAGEW { ULONG ulFlags; HBITMAP hbm; LPWSTR pszImage; UINT cchImageMax; int xOffsetPercent; int yOffsetPercent; } LVBKIMAGEW, *PLVBKIMAGEW, *LPLVBKIMAGEW;
typedef struct tagLVGROUP { UINT cbSize; UINT mask; LPWSTR pszHeader; int cchHeader; LPWSTR pszFooter; int cchFooter; int iGroupId; UINT stateMask; UINT state; UINT uAlign; } LVGROUP, *PLVGROUP, *LPLVGROUP;
typedef struct tagLVGROUPMETRICS { UINT cbSize; UINT mask; UINT Left; UINT Top; UINT Right; UINT Bottom; COLORREF crLeft; COLORREF crTop; COLORREF crRight; COLORREF crBottom; COLORREF crHeader; COLORREF crFooter; } LVGROUPMETRICS, *PLVGROUPMETRICS, *LPLVGROUPMETRICS;
typedef struct tagLVSETINFOTIP { UINT cbSize; DWORD dwFlags; LPWSTR pszText; int iItem; int iSubItem; } LVSETINFOTIP, *PLVSETINFOTIP, *LPLVSETINFOTIP;
typedef struct tagNMLISTVIEW { NMHDR hdr; int iItem; int iSubItem; UINT uNewState; UINT uOldState; UINT uChanged; POINT ptAction; LPARAM lParam; } NMLISTVIEW, *PNMLISTVIEW, *LPNMLISTVIEW;
typedef struct tagNMLVCACHEHINT { NMHDR hdr; int iFrom; int iTo; } NMLVCACHEHINT, *PNMLVCACHEHINT, *LPNMLVCACHEHINT;
typedef struct tagNMLVODSTATECHANGE { NMHDR hdr; int iFrom; int iTo; UINT uNewState; UINT uOldState; } NMLVODSTATECHANGE, *PNMLVODSTATECHANGE, *LPNMLVODSTATECHANGE;
typedef struct tagNMLVKEYDOWN { NMHDR hdr; WORD wVKey; UINT flags; } NMLVKEYDOWN, *PNMLVKEYDOWN, *LPNMLVKEYDOWN;
typedef struct tagNMLVGETINFOTIPA { NMHDR hdr; DWORD dwFlags; LPSTR pszText; int cchTextMax; int iItem; int iSubItem; LPARAM lParam; } NMLVGETINFOTIPA, *PNMLVGETINFOTIPA, *LPNMLVGETINFOTIPA;
typedef struct tagNMLVGETINFOTIPW { NMHDR hdr; DWORD dwFlags; LPWSTR pszText; int cchTextMax; int iItem; int iSubItem; LPARAM lParam; } NMLVGETINFOTIPW, *PNMLVGETINFOTIPW, *LPNMLVGETINFOTIPW;
typedef struct tagNMTVKEYDOWN { NMHDR hdr; WORD wVKey; UINT flags; } NMTVKEYDOWN, *PNMTVKEYDOWN, *LPNMTVKEYDOWN;
typedef struct tagNMTVCUSTOMDRAW { NMCUSTOMDRAW nmcd; COLORREF clrText; COLORREF clrTextBk; } NMTVCUSTOMDRAW, *PNMTVCUSTOMDRAW, *LPNMTVCUSTOMDRAW;
typedef struct tagTCITEMHEADERA { UINT mask; UINT lpReserved1; UINT lpReserved2; LPSTR pszText; int cchTextMax; int iImage; } TCITEMHEADERA, *PTCITEMHEADERA, *LPTCITEMHEADERA;
typedef struct tagTCITEMHEADERW { UINT mask; UINT lpReserved1; UINT lpReserved2; LPWSTR pszText; int cchTextMax; int iImage; } TCITEMHEADERW, *PTCITEMHEADERW, *LPTCITEMHEADERW;
typedef struct tagTCHITTESTINFO { POINT pt; UINT flags; } TCHITTESTINFO, *PTCHITTESTINFO, *LPTCHITTESTINFO;
typedef struct tagNMTCKEYDOWN { NMHDR hdr; WORD wVKey; UINT flags; } NMTCKEYDOWN, *PNMTCKEYDOWN, *LPNMTCKEYDOWN;
typedef struct tagMCHITTESTINFO { UINT cbSize; POINT pt; UINT uHit; SYSTEMTIME st; } MCHITTESTINFO, *PMCHITTESTINFO, *LPMCHITTESTINFO;
typedef struct tagNMSELCHANGE { NMHDR nmhdr; SYSTEMTIME stSelStart; SYSTEMTIME stSelEnd; } NMSELCHANGE, *PNMSELCHANGE, *LPNMSELCHANGE;
typedef struct tagNMDATETIMECHANGE { NMHDR nmhdr; DWORD dwFlags; SYSTEMTIME st; } NMDATETIMECHANGE, *PNMDATETIMECHANGE, *LPNMDATETIMECHANGE;
typedef struct tagNMDATETIMESTRINGA { NMHDR nmhdr; LPCSTR pszUserString; SYSTEMTIME st; DWORD dwFlags; } NMDATETIMESTRINGA, *PNMDATETIMESTRINGA, *LPNMDATETIMESTRINGA;
typedef struct tagNMDATETIMESTRINGW { NMHDR nmhdr; LPCWSTR pszUserString; SYSTEMTIME st; DWORD dwFlags; } NMDATETIMESTRINGW, *PNMDATETIMESTRINGW, *LPNMDATETIMESTRINGW;
typedef struct tagNMDATETIMEWMKEYDOWNA { NMHDR nmhdr; int nVirtKey; LPCSTR pszFormat; SYSTEMTIME st; } NMDATETIMEWMKEYDOWNA, *PNMDATETIMEWMKEYDOWNA, *LPNMDATETIMEWMKEYDOWNA;
typedef struct tagNMDATETIMEWMKEYDOWNW { NMHDR nmhdr; int nVirtKey; LPCWSTR pszFormat; SYSTEMTIME st; } NMDATETIMEWMKEYDOWNW, *PNMDATETIMEWMKEYDOWNW, *LPNMDATETIMEWMKEYDOWNW;
typedef struct tagNMDATETIMEFORMATA { NMHDR nmhdr; LPCSTR pszFormat; SYSTEMTIME st; LPCSTR pszDisplay; CHAR szDisplay[64]; } NMDATETIMEFORMATA, *PNMDATETIMEFORMATA, *LPNMDATETIMEFORMATA;
typedef struct tagNMDATETIMEFORMATW { NMHDR nmhdr; LPCWSTR pszFormat; SYSTEMTIME st; LPCWSTR pszDisplay; WCHAR szDisplay[64]; } NMDATETIMEFORMATW, *PNMDATETIMEFORMATW, *LPNMDATETIMEFORMATW;
typedef struct tagNMDATETIMEFORMATQUERYA { NMHDR nmhdr; LPCSTR pszFormat; SIZE szMax; } NMDATETIMEFORMATQUERYA, *PNMDATETIMEFORMATQUERYA, *LPNMDATETIMEFORMATQUERYA;
typedef struct tagNMDATETIMEFORMATQUERYW { NMHDR nmhdr; LPCWSTR pszFormat; SIZE szMax; } NMDATETIMEFORMATQUERYW, *PNMDATETIMEFORMATQUERYW, *LPNMDATETIMEFORMATQUERYW;

WCE_IMPORT void WINAPI InitCommonControls(void) WCE_LINK(InitCommonControls);
WCE_IMPORT BOOL WINAPI InitCommonControlsEx(LPINITCOMMONCONTROLSEX) WCE_LINK(InitCommonControlsEx);
WCE_IMPORT void WINAPI ImageList_EndDrag() WCE_LINK(ImageList_EndDrag);
WCE_IMPORT BOOL WINAPI ImageList_DragEnter(HWND hwndLock, int x, int y) WCE_LINK(ImageList_DragEnter);
WCE_IMPORT BOOL WINAPI ImageList_DragLeave(HWND hwndLock) WCE_LINK(ImageList_DragLeave);
WCE_IMPORT BOOL WINAPI ImageList_DragMove(int x, int y) WCE_LINK(ImageList_DragMove);
WCE_IMPORT BOOL WINAPI ImageList_DragShowNolock(BOOL fShow) WCE_LINK(ImageList_DragShowNolock);
WCE_IMPORT HWND WINAPI CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps, HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons, int iNumButtons, int dxButton, int dyButton, int dxBitmap, int dyBitmap, UINT uStructSize) WCE_LINK(CreateToolbarEx);
WCE_IMPORT HWND WINAPI CommandBar_Create(HINSTANCE hInst, HWND hwndParent, int idCmdBar) WCE_LINK(CommandBar_Create);
WCE_IMPORT BOOL WINAPI CommandBar_Show(HWND hwndCB, BOOL fShow) WCE_LINK(CommandBar_Show);
WCE_IMPORT int WINAPI CommandBar_AddBitmap(HWND hwndCB, HINSTANCE hInst, int idBitmap, int iNumImages, int iImageWidth, int iImageHeight) WCE_LINK(CommandBar_AddBitmap);
WCE_IMPORT HWND WINAPI CommandBar_InsertComboBox(HWND hwndCB, HINSTANCE hInstance, int iWidth, UINT dwStyle, WORD idComboBox, WORD iButton) WCE_LINK(CommandBar_InsertComboBox);
WCE_IMPORT BOOL WINAPI CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst, WORD idMenu, WORD iButton) WCE_LINK(CommandBar_InsertMenubar);
WCE_IMPORT BOOL WINAPI CommandBar_InsertMenubarEx(HWND hwndCB, HINSTANCE hinst, LPTSTR pszMenu, WORD iButton) WCE_LINK(CommandBar_InsertMenubarEx);
WCE_IMPORT BOOL WINAPI CommandBar_DrawMenuBar(HWND hwndCB, WORD iButton) WCE_LINK(CommandBar_DrawMenuBar);
WCE_IMPORT HMENU WINAPI CommandBar_GetMenu(HWND hwndCB, WORD iButton) WCE_LINK(CommandBar_GetMenu);
WCE_IMPORT BOOL WINAPI CommandBar_AddAdornments(HWND hwndCB, DWORD dwFlags, DWORD dwReserved) WCE_LINK(CommandBar_AddAdornments);
WCE_IMPORT void WINAPI CommandBar_AlignAdornments(HWND hwndCB) WCE_LINK(CommandBar_AlignAdornments);
WCE_IMPORT int WINAPI CommandBar_Height(HWND hwndCB) WCE_LINK(CommandBar_Height);
WCE_IMPORT BOOL WINAPI IsCommandBarMessage(HWND hwndCB, LPMSG lpMsg) WCE_LINK(IsCommandBarMessage);
WCE_IMPORT BOOL WINAPI CommandBands_AddBands(HWND hwndCmdBands, HINSTANCE hinst, UINT cBands, LPREBARBANDINFO prbbi) WCE_LINK(CommandBands_AddBands);
WCE_IMPORT HWND WINAPI CommandBands_GetCommandBar(HWND hwndCmdBands, UINT uBand) WCE_LINK(CommandBands_GetCommandBar);
WCE_IMPORT BOOL WINAPI CommandBands_AddAdornments(HWND hwndCmdBands, HINSTANCE hinst, DWORD dwFlags, LPREBARBANDINFO prbbi) WCE_LINK(CommandBands_AddAdornments);
WCE_IMPORT BOOL WINAPI CommandBands_Show(HWND hwndCmdBands, BOOL fShow) WCE_LINK(CommandBands_Show);
WCE_IMPORT BOOL WINAPI CommandBands_GetRestoreInformation(HWND hwndCmdBands, UINT uBand, LPCOMMANDBANDSRESTOREINFO pcbri) WCE_LINK(CommandBands_GetRestoreInformation);
WCE_IMPORT void WINAPI DrawStatusTextA(HDC hDC, LPRECT lprc, LPCSTR pszText, UINT uFlags) WCE_LINK(DrawStatusTextA);
WCE_IMPORT void WINAPI DrawStatusTextW(HDC hDC, LPRECT lprc, LPCWSTR pszText, UINT uFlags) WCE_LINK(DrawStatusTextW);
WCE_IMPORT HWND WINAPI CreateStatusWindowA(LONG style, LPCSTR lpszText, HWND hwndParent, UINT wID) WCE_LINK(CreateStatusWindowA);
WCE_IMPORT HWND WINAPI CreateStatusWindowW(LONG style, LPCWSTR lpszText, HWND hwndParent, UINT wID) WCE_LINK(CreateStatusWindowW);
WCE_IMPORT HWND WINAPI CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy, HWND hParent, int nID, HINSTANCE hInst, HWND hBuddy, int nUpper, int nLower, int nPos) WCE_LINK(CreateUpDownControl);

#define DrawStatusText DrawStatusTextW
#define CreateStatusWindow CreateStatusWindowW
#ifdef __cplusplus
}
#endif
#endif

