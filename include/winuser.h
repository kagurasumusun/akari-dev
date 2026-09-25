/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINUSER_H
#define WCE_WINUSER_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWNDCLASSA { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; LPCSTR lpszMenuName; LPCSTR lpszClassName; } WNDCLASSA, *PWNDCLASSA, *LPWNDCLASSA;
typedef struct tagCREATESTRUCTA { LPVOID lpCreateParams; HINSTANCE hInstance; HMENU hMenu; HWND hwndParent; int cy; int cx; int y; int x; LONG style; LPCSTR lpszName; LPCSTR lpszClass; DWORD dwExStyle; } CREATESTRUCTA, *PCREATESTRUCTA, *LPCREATESTRUCTA;
typedef struct tagSTYLESTRUCT { DWORD styleOld; DWORD styleNew; } STYLESTRUCT, *PSTYLESTRUCT, *LPSTYLESTRUCT;
typedef struct tagWINDOWPOS { HWND hwnd; HWND hwndInsertAfter; int x; int y; int cx; int cy; UINT flags; } WINDOWPOS, *PWINDOWPOS, *LPWINDOWPOS;
typedef struct tagTPMPARAMS { UINT cbSize; RECT rcExclude; } TPMPARAMS, *PTPMPARAMS, *LPTPMPARAMS;
typedef struct tagMENUITEMINFOA { UINT cbSize; UINT fMask; UINT fType; UINT fState; UINT wID; HMENU hSubMenu; HBITMAP hbmpChecked; HBITMAP hbmpUnchecked; DWORD dwItemData; LPSTR dwTypeData; UINT cch; } MENUITEMINFOA, *PMENUITEMINFOA, *LPMENUITEMINFOA;
typedef struct tagMENUITEMINFOW { UINT cbSize; UINT fMask; UINT fType; UINT fState; UINT wID; HMENU hSubMenu; HBITMAP hbmpChecked; HBITMAP hbmpUnchecked; DWORD dwItemData; LPWSTR dwTypeData; UINT cch; } MENUITEMINFOW, *PMENUITEMINFOW, *LPMENUITEMINFOW;
typedef struct tagACCEL { BYTE fVirt; WORD key; WORD cmd; WORD pad; } ACCEL, *PACCEL, *LPACCEL;
typedef struct tagCOPYDATASTRUCT { DWORD dwData; DWORD cbData; PVOID lpData; } COPYDATASTRUCT, *PCOPYDATASTRUCT, *LPCOPYDATASTRUCT;
typedef struct tagMOUSEINPUT { LONG dx; LONG dy; DWORD mouseData; DWORD dwFlags; DWORD time; DWORD dwExtraInfo; } MOUSEINPUT, *PMOUSEINPUT, *LPMOUSEINPUT;
typedef struct tagKEYBDINPUT { WORD wVk; WORD wScan; DWORD dwFlags; DWORD time; DWORD dwExtraInfo; } KEYBDINPUT, *PKEYBDINPUT, *LPKEYBDINPUT;
typedef struct tagHARDWAREINPUT { DWORD uMsg; WORD wParamL; WORD wParamH; DWORD dwExtraInfo; } HARDWAREINPUT, *PHARDWAREINPUT, *LPHARDWAREINPUT;
typedef struct tagMEASUREITEMSTRUCT { UINT CtlType; UINT CtlID; UINT itemID; UINT itemWidth; UINT itemHeight; UINT itemData; } MEASUREITEMSTRUCT, *PMEASUREITEMSTRUCT, *LPMEASUREITEMSTRUCT;
typedef struct tagDRAWITEMSTRUCT { UINT CtlType; UINT CtlID; UINT itemID; UINT itemAction; UINT itemState; HWND hwndItem; HDC hDC; RECT rcItem; DWORD itemData; } DRAWITEMSTRUCT, *PDRAWITEMSTRUCT, *LPDRAWITEMSTRUCT;
typedef struct tagDELETEITEMSTRUCT { UINT CtlType; UINT CtlID; UINT itemID; HWND hwndItem; UINT itemData; } DELETEITEMSTRUCT, *PDELETEITEMSTRUCT, *LPDELETEITEMSTRUCT;
typedef struct tagCOMPAREITEMSTRUCT { UINT CtlType; UINT CtlID; HWND hwndItem; UINT itemID1; DWORD itemData1; UINT itemID2; DWORD itemData2; DWORD dwLocaleId; } COMPAREITEMSTRUCT, *PCOMPAREITEMSTRUCT, *LPCOMPAREITEMSTRUCT;
typedef struct tagSCROLLINFO { UINT cbSize; UINT fMask; int nMin; int nMax; UINT nPage; int nPos; int nTrackPos; } SCROLLINFO, *PSCROLLINFO, *LPSCROLLINFO;
typedef struct tagDLGTEMPLATE { DWORD style; DWORD dwExtendedStyle; WORD cdit; short x; short y; short cx; short cy; } DLGTEMPLATE, *PDLGTEMPLATE, *LPDLGTEMPLATE;
typedef struct tagDLGITEMTEMPLATE { DWORD style; DWORD dwExtendedStyle; short x; short y; short cx; short cy; WORD id; } DLGITEMTEMPLATE, *PDLGITEMTEMPLATE, *LPDLGITEMTEMPLATE;
typedef struct tagCOMBOBOXINFO { DWORD cbSize; RECT rcItem; RECT rcButton; DWORD stateButton; HWND hwndCombo; HWND hwndItem; HWND hwndList; } COMBOBOXINFO, *PCOMBOBOXINFO, *LPCOMBOBOXINFO;
typedef struct tagMOUSEKEYS { UINT cbSize; DWORD dwFlags; DWORD iMaxSpeed; DWORD iTimeToMaxSpeed; DWORD iCtrlSpeed; DWORD dwReserved1; DWORD dwReserved2; } MOUSEKEYS, *PMOUSEKEYS, *LPMOUSEKEYS;
typedef struct tagSTICKYKEYS { UINT cbSize; DWORD dwFlags; } STICKYKEYS, *PSTICKYKEYS, *LPSTICKYKEYS;
typedef struct tagHIGHCONTRAST { UINT cbSize; DWORD dwFlags; LPTSTR lpszDefaultScheme; } HIGHCONTRAST, *PHIGHCONTRAST, *LPHIGHCONTRAST;
typedef struct tagSOUNDSENTRY { UINT cbSize; DWORD dwFlags; DWORD iFSTextEffect; DWORD iFSTextEffectMSec; DWORD iFSTextEffectColorBits; DWORD iFSGrafEffect; DWORD iFSGrafEffectMSec; DWORD iFSGrafEffectColor; DWORD iWindowsEffect; DWORD iWindowsEffectMSec; LPTSTR lpszWindowsEffectDLL; DWORD iWindowsEffectOrdinal; } SOUNDSENTRY, *PSOUNDSENTRY, *LPSOUNDSENTRY;
typedef struct tagTOGGLEKEYS { UINT cbSize; DWORD dwFlags; } TOGGLEKEYS, *PTOGGLEKEYS, *LPTOGGLEKEYS;
typedef struct tagACCESSTIMEOUT { UINT cbSize; DWORD dwFlags; DWORD iTimeOutMSec; } ACCESSTIMEOUT, *PACCESSTIMEOUT, *LPACCESSTIMEOUT;
typedef struct tagICONINFO { BOOL fIcon; DWORD xHotspot; DWORD yHotspot; HBITMAP hbmMask; HBITMAP hbmColor; } ICONINFO, *PICONINFO, *LPICONINFO;
typedef struct tagMONITORINFO { DWORD cbSize; RECT rcMonitor; RECT rcWork; DWORD dwFlags; } MONITORINFO, *PMONITORINFO, *LPMONITORINFO;

WCE_IMPORT BOOL WINAPI DrawFrameControl(HDC, LPRECT, UINT, UINT) WCE_LINK(DrawFrameControl);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT UINT WINAPI RegisterWindowMessageA(LPCSTR lpString) WCE_LINK(RegisterWindowMessageA);
#endif
WCE_IMPORT UINT WINAPI RegisterWindowMessageW(LPCWSTR lpString) WCE_LINK(RegisterWindowMessageW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI PostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(PostMessageA);
#endif
WCE_IMPORT BOOL WINAPI PostMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(PostMessageW);
WCE_IMPORT BOOL WINAPI PostThreadMessageA(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(PostThreadMessageA);
WCE_IMPORT BOOL WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(PostThreadMessageW);
WCE_IMPORT VOID WINAPI PostQuitMessage(int nExitCode) WCE_LINK(PostQuitMessage);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendMessageA);
#endif
WCE_IMPORT LRESULT WINAPI SendMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendMessageW);
WCE_IMPORT BOOL WINAPI SendNotifyMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendNotifyMessageA);
WCE_IMPORT BOOL WINAPI SendNotifyMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendNotifyMessageW);
WCE_IMPORT LRESULT WINAPI SendMessageTimeout(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult) WCE_LINK(SendMessageTimeout);
WCE_IMPORT DWORD WINAPI GetMessageQueueReadyTimeStamp(HWND hWnd) WCE_LINK(GetMessageQueueReadyTimeStamp);
WCE_IMPORT BOOL WINAPI InSendMessage(VOID) WCE_LINK(InSendMessage);
WCE_IMPORT DWORD WINAPI GetQueueStatus(UINT flags) WCE_LINK(GetQueueStatus);
WCE_IMPORT BOOL WINAPI GetMessageA(LPMSG lpMsg, HWND hWnd , UINT wMsgFilterMin, UINT wMsgFilterMax) WCE_LINK(GetMessageA);
WCE_IMPORT BOOL WINAPI GetMessageW(LPMSG lpMsg, HWND hWnd , UINT wMsgFilterMin, UINT wMsgFilterMax) WCE_LINK(GetMessageW);
WCE_IMPORT BOOL WINAPI PeekMessageW(PMSG pMsg, HWND hWnd , UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) WCE_LINK(PeekMessageW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI PeekMessageA(PMSG pMsg, HWND hWnd , UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) WCE_LINK(PeekMessageA);
#endif
WCE_IMPORT BOOL WINAPI TranslateMessage(CONST MSG *pMsg) WCE_LINK(TranslateMessage);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LONG WINAPI DispatchMessageA(CONST MSG *lpMsg) WCE_LINK(DispatchMessageA);
#endif
WCE_IMPORT LONG WINAPI DispatchMessageW(CONST MSG *lpMsg) WCE_LINK(DispatchMessageW);
WCE_IMPORT DWORD WINAPI GetMessagePos(VOID) WCE_LINK(GetMessagePos);
WCE_IMPORT UINT WINAPI GetMessageSource(void) WCE_LINK(GetMessageSource);
WCE_IMPORT DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount, LPHANDLE pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags) WCE_LINK(MsgWaitForMultipleObjectsEx);
WCE_IMPORT DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount, LPHANDLE pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask) WCE_LINK(MsgWaitForMultipleObjects);
WCE_IMPORT HWND WINAPI GetCapture(VOID) WCE_LINK(GetCapture);
WCE_IMPORT HWND WINAPI SetCapture(HWND hWnd) WCE_LINK(SetCapture);
WCE_IMPORT BOOL WINAPI ReleaseCapture(VOID) WCE_LINK(ReleaseCapture);
WCE_IMPORT BOOL WINAPI MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint) WCE_LINK(MoveWindow);
WCE_IMPORT int WINAPI SetWindowRgn(HWND hwnd, HRGN hrgn, BOOL bRedraw) WCE_LINK(SetWindowRgn);
WCE_IMPORT int WINAPI GetWindowRgn(HWND hwnd, HRGN hrgn) WCE_LINK(GetWindowRgn);
WCE_IMPORT BOOL WINAPI SetWindowPos(HWND hwnd, HWND hwndInsertAfter, int x, int y, int dx, int dy, UINT fuFlags) WCE_LINK(SetWindowPos);
WCE_IMPORT BOOL WINAPI GetWindowRect(HWND hwnd, LPRECT prc) WCE_LINK(GetWindowRect);
WCE_IMPORT int WINAPI GetWindowTextLengthA(HWND hWnd) WCE_LINK(GetWindowTextLengthA);
WCE_IMPORT int WINAPI GetWindowTextLengthW(HWND hWnd) WCE_LINK(GetWindowTextLengthW);
WCE_IMPORT BOOL WINAPI GetClientRect(HWND hwnd, LPRECT prc) WCE_LINK(GetClientRect);
WCE_IMPORT BOOL WINAPI AdjustWindowRectEx(LPRECT prc, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle) WCE_LINK(AdjustWindowRectEx);
WCE_IMPORT BOOL WINAPI ValidateRect(HWND hWnd , CONST RECT *lpRect) WCE_LINK(ValidateRect);
WCE_IMPORT BOOL WINAPI InvalidateRect(HWND hwnd, LPCRECT prc, BOOL fErase) WCE_LINK(InvalidateRect);
WCE_IMPORT BOOL WINAPI ValidateRgn(HWND hWnd, HRGN hRgn) WCE_LINK(ValidateRgn);
WCE_IMPORT BOOL WINAPI InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL fErase) WCE_LINK(InvalidateRgn);
WCE_IMPORT HWND WINAPI GetWindow(HWND hwnd, UINT uCmd) WCE_LINK(GetWindow);
WCE_IMPORT BOOL WINAPI BringWindowToTop(HWND hWnd) WCE_LINK(BringWindowToTop);
WCE_IMPORT BOOL WINAPI SetProp(HWND hWnd, LPCWSTR lpString, HANDLE hData) WCE_LINK(SetProp);
WCE_IMPORT HANDLE WINAPI GetProp(HWND hWnd, LPCWSTR lpString) WCE_LINK(GetProp);
WCE_IMPORT HANDLE WINAPI RemoveProp(HWND hWnd, LPCWSTR lpString) WCE_LINK(RemoveProp);
WCE_IMPORT int WINAPI EnumPropsEx(HWND hWnd, PROPENUMPROCEX lpEnumFunc, LPARAM lParam) WCE_LINK(EnumPropsEx);
WCE_IMPORT int WINAPI ScrollWindowEx(HWND hWnd, int dx, int dy, CONST RECT *prcScroll, CONST RECT *prcClip , HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags) WCE_LINK(ScrollWindowEx);
WCE_IMPORT BOOL WINAPI ScrollDC(HDC hDC, int dx, int dy, CONST RECT *lprcScroll, CONST RECT *lprcClip , HRGN hrgnUpdate, LPRECT lprcUpdate) WCE_LINK(ScrollDC);
WCE_IMPORT BOOL WINAPI CheckMenuRadioItem(HMENU, UINT, UINT, UINT, UINT) WCE_LINK(CheckMenuRadioItem);
WCE_IMPORT HBITMAP WINAPI LoadBitmapA(HINSTANCE hInstance, LPCSTR lpBitmapName) WCE_LINK(LoadBitmapA);
WCE_IMPORT HBITMAP WINAPI LoadBitmapW(HINSTANCE hInstance, LPCWSTR lpBitmapName) WCE_LINK(LoadBitmapW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HMENU WINAPI LoadMenuA(HINSTANCE hInstance, LPCSTR lpMenuName) WCE_LINK(LoadMenuA);
#endif
WCE_IMPORT HMENU WINAPI LoadMenuW(HINSTANCE hInstance, LPCWSTR lpMenuName) WCE_LINK(LoadMenuW);
WCE_IMPORT BOOL WINAPI DrawMenuBar(HWND hWnd) WCE_LINK(DrawMenuBar);
WCE_IMPORT HMENU WINAPI CreateMenu(VOID) WCE_LINK(CreateMenu);
WCE_IMPORT HMENU WINAPI CreatePopupMenu(VOID) WCE_LINK(CreatePopupMenu);
WCE_IMPORT BOOL WINAPI DestroyMenu(HMENU hMenu) WCE_LINK(DestroyMenu);
WCE_IMPORT DWORD WINAPI CheckMenuItem(HMENU hMenu, UINT uIDCheckItem, UINT uCheck) WCE_LINK(CheckMenuItem);
WCE_IMPORT BOOL WINAPI EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable) WCE_LINK(EnableMenuItem);
WCE_IMPORT HMENU WINAPI GetSubMenu(HMENU hMenu, int nPos) WCE_LINK(GetSubMenu);
WCE_IMPORT BOOL WINAPI InsertMenuA(HMENU hMenu, UINT uPosition, UINT uFlags, UINT uIDNewItem, LPCSTR lpNewItem) WCE_LINK(InsertMenuA);
WCE_IMPORT BOOL WINAPI InsertMenuW(HMENU hMenu, UINT uPosition, UINT uFlags, UINT uIDNewItem, LPCWSTR lpNewItem) WCE_LINK(InsertMenuW);
WCE_IMPORT BOOL WINAPI AppendMenuA(HMENU hMenu, UINT uFlags, UINT uIDNewItem, LPCSTR lpNewItem) WCE_LINK(AppendMenuA);
WCE_IMPORT BOOL WINAPI AppendMenuW(HMENU hMenu, UINT uFlags, UINT uIDNewItem, LPCWSTR lpNewItem) WCE_LINK(AppendMenuW);
WCE_IMPORT BOOL WINAPI RemoveMenu(HMENU hMenu, UINT uPosition, UINT uFlags) WCE_LINK(RemoveMenu);
WCE_IMPORT BOOL WINAPI DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags) WCE_LINK(DeleteMenu);
WCE_IMPORT BOOL WINAPI TrackPopupMenu(HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT *prcRect) WCE_LINK(TrackPopupMenu);
WCE_IMPORT BOOL WINAPI TrackPopupMenuEx(HMENU hmenu, UINT uFlags, int x, int y, HWND hwnd, LPTPMPARAMS lptpm) WCE_LINK(TrackPopupMenuEx);
WCE_IMPORT BOOL WINAPI GetMenuItemInfoA(HMENU, UINT, BOOL, LPMENUITEMINFOA) WCE_LINK(GetMenuItemInfoA);
WCE_IMPORT BOOL WINAPI GetMenuItemInfoW(HMENU, UINT, BOOL, LPMENUITEMINFOW) WCE_LINK(GetMenuItemInfoW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI SetMenuItemInfoA(HMENU, UINT, BOOL, LPCMENUITEMINFOA) WCE_LINK(SetMenuItemInfoA);
#endif
WCE_IMPORT BOOL WINAPI SetMenuItemInfoW(HMENU, UINT, BOOL, LPCMENUITEMINFOW) WCE_LINK(SetMenuItemInfoW);
WCE_IMPORT HACCEL WINAPI LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName) WCE_LINK(LoadAcceleratorsA);
WCE_IMPORT HACCEL WINAPI LoadAcceleratorsW(HINSTANCE hInstance, LPCWSTR lpTableName) WCE_LINK(LoadAcceleratorsW);
WCE_IMPORT HACCEL WINAPI CreateAcceleratorTableA(LPACCEL, int cEntries) WCE_LINK(CreateAcceleratorTableA);
WCE_IMPORT HACCEL WINAPI CreateAcceleratorTableW(LPACCEL, int cEntries) WCE_LINK(CreateAcceleratorTableW);
WCE_IMPORT BOOL WINAPI DestroyAcceleratorTable(HACCEL hAccel) WCE_LINK(DestroyAcceleratorTable);
WCE_IMPORT BOOL WINAPI SetSysColors(int cElements, CONST INT * lpaElements, CONST COLORREF * lpaRgbValues) WCE_LINK(SetSysColors);
WCE_IMPORT BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom) WCE_LINK(SetRect);
WCE_IMPORT BOOL WINAPI SetRectEmpty(LPRECT lprc) WCE_LINK(SetRectEmpty);
WCE_IMPORT BOOL WINAPI CopyRect(LPRECT lprcDst, CONST RECT *lprcSrc) WCE_LINK(CopyRect);
WCE_IMPORT BOOL WINAPI InflateRect(LPRECT lprc, int dx, int dy) WCE_LINK(InflateRect);
WCE_IMPORT BOOL WINAPI IntersectRect(LPRECT lprcDst, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2) WCE_LINK(IntersectRect);
WCE_IMPORT BOOL WINAPI UnionRect(LPRECT lprcDst, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2) WCE_LINK(UnionRect);
WCE_IMPORT BOOL WINAPI OffsetRect(LPRECT lprc, int dx, int dy) WCE_LINK(OffsetRect);
WCE_IMPORT BOOL WINAPI IsRectEmpty(CONST RECT *lprc) WCE_LINK(IsRectEmpty);
WCE_IMPORT BOOL WINAPI EqualRect(CONST RECT *lprc1, CONST RECT *lprc2) WCE_LINK(EqualRect);
WCE_IMPORT BOOL WINAPI PtInRect(CONST RECT *lprc, POINT pt) WCE_LINK(PtInRect);
WCE_IMPORT BOOL WINAPI SubtractRect(LPRECT prcDst, CONST RECT *prcSrc1, CONST RECT *prcSrc2) WCE_LINK(SubtractRect);
WCE_IMPORT int WINAPI MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints) WCE_LINK(MapWindowPoints);
WCE_IMPORT HWND WINAPI WindowFromPoint(POINT Point) WCE_LINK(WindowFromPoint);
WCE_IMPORT HWND WINAPI ChildWindowFromPoint(HWND hWndParent, POINT Point) WCE_LINK(ChildWindowFromPoint);
WCE_IMPORT BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint) WCE_LINK(ClientToScreen);
WCE_IMPORT BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint) WCE_LINK(ScreenToClient);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI SetWindowTextA(HWND hWnd, LPCSTR lpString) WCE_LINK(SetWindowTextA);
#endif
WCE_IMPORT BOOL WINAPI SetWindowTextW(HWND hWnd, LPCWSTR lpString) WCE_LINK(SetWindowTextW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPI GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount) WCE_LINK(GetWindowTextA);
#endif
WCE_IMPORT int WINAPI GetWindowTextW(HWND hWnd, LPWSTR lpString, int nMaxCount) WCE_LINK(GetWindowTextW);
WCE_IMPORT HDC WINAPI BeginPaint(HWND hwnd, LPPAINTSTRUCT pps) WCE_LINK(BeginPaint);
WCE_IMPORT BOOL WINAPI EndPaint(HWND hwnd, LPPAINTSTRUCT pps) WCE_LINK(EndPaint);
WCE_IMPORT BOOL WINAPI GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase) WCE_LINK(GetUpdateRect);
WCE_IMPORT int WINAPI GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase) WCE_LINK(GetUpdateRgn);
WCE_IMPORT HDC WINAPI GetDCEx(HWND hWnd , HRGN hrgnClip, DWORD flags) WCE_LINK(GetDCEx);
WCE_IMPORT HWND WINAPI GetDesktopWindow(void) WCE_LINK(GetDesktopWindow);
WCE_IMPORT BOOL WINAPI IsWindow(HWND hWnd) WCE_LINK(IsWindow);
WCE_IMPORT BOOL WINAPI IsWindowVisible(HWND hWnd) WCE_LINK(IsWindowVisible);
WCE_IMPORT HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent , HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) WCE_LINK(CreateWindowExA);
WCE_IMPORT HWND WINAPI CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent , HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) WCE_LINK(CreateWindowExW);
WCE_IMPORT BOOL WINAPI DestroyWindow(HWND hwnd) WCE_LINK(DestroyWindow);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LRESULT WINAPI CallWindowProcA(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(CallWindowProcA);
#endif
WCE_IMPORT LRESULT WINAPI CallWindowProcW(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(CallWindowProcW);
WCE_IMPORT DWORD WINAPI GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId) WCE_LINK(GetWindowThreadProcessId);
WCE_IMPORT UINT WINAPI GetDoubleClickTime(VOID) WCE_LINK(GetDoubleClickTime);
WCE_IMPORT int WINAPI GetSystemMetrics(int nIndex) WCE_LINK(GetSystemMetrics);
WCE_IMPORT DWORD WINAPI GetClassLongA(HWND hWnd, int nIndex) WCE_LINK(GetClassLongA);
WCE_IMPORT DWORD WINAPI GetClassLongW(HWND hWnd, int nIndex) WCE_LINK(GetClassLongW);
WCE_IMPORT DWORD WINAPI SetClassLongA(HWND hWnd, int nIndex, LONG dwNewLong) WCE_LINK(SetClassLongA);
WCE_IMPORT DWORD WINAPI SetClassLongW(HWND hWnd, int nIndex, LONG dwNewLong) WCE_LINK(SetClassLongW);
WCE_IMPORT ATOM WINAPI RegisterClassA(CONST WNDCLASSA *lpWndClass) WCE_LINK(RegisterClassA);
WCE_IMPORT ATOM WINAPI RegisterClassW(CONST WNDCLASSW *lpWndClass) WCE_LINK(RegisterClassW);
WCE_IMPORT BOOL WINAPI UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance) WCE_LINK(UnregisterClassA);
WCE_IMPORT BOOL WINAPI UnregisterClassW(LPCWSTR lpClassName, HINSTANCE hInstance) WCE_LINK(UnregisterClassW);
WCE_IMPORT BOOL WINAPI GetClassInfoA(HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSA lpWndClass) WCE_LINK(GetClassInfoA);
WCE_IMPORT BOOL WINAPI GetClassInfoW(HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass) WCE_LINK(GetClassInfoW);
WCE_IMPORT BOOL WINAPI EnableWindow(HWND hWnd, BOOL bEnable) WCE_LINK(EnableWindow);
WCE_IMPORT BOOL WINAPI IsWindowEnabled(HWND hWnd) WCE_LINK(IsWindowEnabled);
WCE_IMPORT DWORD WINAPI GetSysColor(int nIndex) WCE_LINK(GetSysColor);
WCE_IMPORT HDC WINAPI GetDC(HWND hwnd) WCE_LINK(GetDC);
WCE_IMPORT HDC WINAPI GetWindowDC(HWND hwnd) WCE_LINK(GetWindowDC);
WCE_IMPORT int WINAPI ReleaseDC(HWND hwnd, HDC hdc) WCE_LINK(ReleaseDC);
WCE_IMPORT BOOL WINAPI GetMouseMovePoints(PPOINT pptBuf, UINT nBufPoints, UINT *pnPointsRetrieved) WCE_LINK(GetMouseMovePoints);
WCE_IMPORT VOID WINAPI mouse_event(DWORD dwFlags, DWORD dx, DWORD dy, DWORD cButtons, DWORD dwExtraInfo) WCE_LINK(mouse_event);
WCE_IMPORT UINT WINAPI SendInput(UINT nInputs, LPINPUT pInputs, int cbSize) WCE_LINK(SendInput);
WCE_IMPORT int WINAPI TranslateAcceleratorA(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg) WCE_LINK(TranslateAcceleratorA);
WCE_IMPORT int WINAPI TranslateAcceleratorW(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg) WCE_LINK(TranslateAcceleratorW);
WCE_IMPORT void WINAPI SystemIdleTimerReset(void) WCE_LINK(SystemIdleTimerReset);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(DefWindowProcA);
#endif
WCE_IMPORT LRESULT WINAPI DefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(DefWindowProcW);
WCE_IMPORT LONG WINAPI GetWindowLongA(HWND hWnd, int nIndex) WCE_LINK(GetWindowLongA);
WCE_IMPORT LONG WINAPI GetWindowLongW(HWND hWnd, int nIndex) WCE_LINK(GetWindowLongW);
WCE_IMPORT LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) WCE_LINK(SetWindowLongA);
WCE_IMPORT LONG WINAPI SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong) WCE_LINK(SetWindowLongW);
WCE_IMPORT BOOL WINAPI IsChild(HWND hWndParent, HWND hWnd) WCE_LINK(IsChild);
WCE_IMPORT BOOL WINAPI ShowWindow(HWND hwnd, INT nCmdShow) WCE_LINK(ShowWindow);
WCE_IMPORT BOOL WINAPI UpdateWindow(HWND hwnd) WCE_LINK(UpdateWindow);
WCE_IMPORT BOOL WINAPI RedrawWindow(HWND hwnd, CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT flags) WCE_LINK(RedrawWindow);
WCE_IMPORT HWND WINAPI SetParent(HWND hwnd, HWND hwndParent) WCE_LINK(SetParent);
WCE_IMPORT HWND WINAPI GetParent(HWND hwnd) WCE_LINK(GetParent);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HWND WINAPI FindWindowA(LPCSTR lpClassName , LPCSTR lpWindowName) WCE_LINK(FindWindowA);
#endif
WCE_IMPORT HWND WINAPI FindWindowW(LPCWSTR lpClassName , LPCWSTR lpWindowName) WCE_LINK(FindWindowW);
WCE_IMPORT int WINAPI GetClassNameA(HWND hWnd, LPSTR lpClassName, int nMaxCount) WCE_LINK(GetClassNameA);
WCE_IMPORT int WINAPI GetClassNameW(HWND hWnd, LPWSTR lpClassName, int nMaxCount) WCE_LINK(GetClassNameW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPI MessageBoxA(HWND hWnd , LPCSTR lpText, LPCSTR lpCaption, UINT uType) WCE_LINK(MessageBoxA);
#endif
WCE_IMPORT int WINAPI MessageBoxW(HWND hWnd , LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) WCE_LINK(MessageBoxW);
WCE_IMPORT BOOL WINAPI MessageBeep(UINT uType) WCE_LINK(MessageBeep);
WCE_IMPORT BOOL WINAPI CreateCaret(HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight) WCE_LINK(CreateCaret);
WCE_IMPORT BOOL WINAPI DestroyCaret(VOID) WCE_LINK(DestroyCaret);
WCE_IMPORT BOOL WINAPI HideCaret(HWND hWnd) WCE_LINK(HideCaret);
WCE_IMPORT BOOL WINAPI ShowCaret(HWND hWnd) WCE_LINK(ShowCaret);
WCE_IMPORT BOOL WINAPI SetCaretPos(int X, int Y) WCE_LINK(SetCaretPos);
WCE_IMPORT BOOL WINAPI GetCaretPos(LPPOINT lpPoint) WCE_LINK(GetCaretPos);
WCE_IMPORT BOOL WINAPI SetCaretBlinkTime(UINT uMSeconds) WCE_LINK(SetCaretBlinkTime);
WCE_IMPORT UINT WINAPI GetCaretBlinkTime(VOID) WCE_LINK(GetCaretBlinkTime);
WCE_IMPORT HWND WINAPI SetActiveWindow(HWND hWnd) WCE_LINK(SetActiveWindow);
WCE_IMPORT HWND WINAPI GetForegroundWindow(VOID) WCE_LINK(GetForegroundWindow);
WCE_IMPORT BOOL WINAPI SetForegroundWindow(HWND hWnd) WCE_LINK(SetForegroundWindow);
WCE_IMPORT HWND WINAPI SetFocus(HWND hWnd) WCE_LINK(SetFocus);
WCE_IMPORT HWND WINAPI GetActiveWindow(VOID) WCE_LINK(GetActiveWindow);
WCE_IMPORT HWND WINAPI GetFocus(VOID) WCE_LINK(GetFocus);
WCE_IMPORT SHORT WINAPI GetAsyncKeyState(int vKey) WCE_LINK(GetAsyncKeyState);
WCE_IMPORT SHORT WINAPI GetKeyState(int nVirtKey) WCE_LINK(GetKeyState);
WCE_IMPORT VOID WINAPI keybd_event(BYTE bVk, BYTE bScan, DWORD dwFlags, DWORD dwExtraInfo) WCE_LINK(keybd_event);
WCE_IMPORT BOOL WINAPI PostKeybdMessage(HWND hwnd, UINT VKey, UINT KeyStateFlags, UINT cCharacters, UINT *pShiftStateBuffer, UINT *pCharacterBuffer) WCE_LINK(PostKeybdMessage);
WCE_IMPORT int WINAPI GetKeyboardType(int nTypeFlag) WCE_LINK(GetKeyboardType);
WCE_IMPORT BOOL WINAPI GetKeyboardLayoutNameA(LPSTR pwszKLID) WCE_LINK(GetKeyboardLayoutNameA);
WCE_IMPORT BOOL WINAPI GetKeyboardLayoutNameW(LPWSTR pwszKLID) WCE_LINK(GetKeyboardLayoutNameW);
WCE_IMPORT UINT WINAPI MapVirtualKeyA(UINT uCode, UINT uMapType) WCE_LINK(MapVirtualKeyA);
WCE_IMPORT UINT WINAPI MapVirtualKeyW(UINT uCode, UINT uMapType) WCE_LINK(MapVirtualKeyW);
WCE_IMPORT int WINAPI SetScrollInfo(HWND, int, LPCSCROLLINFO, BOOL) WCE_LINK(SetScrollInfo);
WCE_IMPORT BOOL WINAPI GetScrollInfo(HWND, int, LPSCROLLINFO) WCE_LINK(GetScrollInfo);
WCE_IMPORT int WINAPI SetScrollPos(HWND hwnd, int fnBar, int nPos, BOOL bRedraw) WCE_LINK(SetScrollPos);
WCE_IMPORT BOOL WINAPI SetScrollRange(HWND hwnd, int fnBar, int nMinPos, int nMaxPos, BOOL bRedraw) WCE_LINK(SetScrollRange);
WCE_IMPORT HWND WINAPI CreateDialogIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) WCE_LINK(CreateDialogIndirectParamA);
WCE_IMPORT HWND WINAPI CreateDialogIndirectParamW(HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) WCE_LINK(CreateDialogIndirectParamW);
WCE_IMPORT int WINAPI DialogBoxIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent , DLGPROC lpDialogFunc, LPARAM dwInitParam) WCE_LINK(DialogBoxIndirectParamA);
WCE_IMPORT int WINAPI DialogBoxIndirectParamW(HINSTANCE hInstance, LPCDLGTEMPLATEW hDialogTemplate, HWND hWndParent , DLGPROC lpDialogFunc, LPARAM dwInitParam) WCE_LINK(DialogBoxIndirectParamW);
WCE_IMPORT BOOL WINAPI IsDialogMessageA(HWND hDlg, LPMSG lpMsg) WCE_LINK(IsDialogMessageA);
WCE_IMPORT BOOL WINAPI IsDialogMessageW(HWND hDlg, LPMSG lpMsg) WCE_LINK(IsDialogMessageW);
WCE_IMPORT BOOL WINAPI EndDialog(HWND hDlg, int nResult) WCE_LINK(EndDialog);
WCE_IMPORT HWND WINAPI GetNextDlgGroupItem(HWND hDlg, HWND hCtl, BOOL bPrevious) WCE_LINK(GetNextDlgGroupItem);
WCE_IMPORT HWND WINAPI GetNextDlgTabItem(HWND hDlg, HWND hCtl, BOOL bPrevious) WCE_LINK(GetNextDlgTabItem);
WCE_IMPORT int WINAPI GetDlgCtrlID(HWND hWnd) WCE_LINK(GetDlgCtrlID);
WCE_IMPORT long WINAPI GetDialogBaseUnits(VOID) WCE_LINK(GetDialogBaseUnits);
WCE_IMPORT BOOL WINAPI MapDialogRect(HWND hwnd, LPRECT prc) WCE_LINK(MapDialogRect);
WCE_IMPORT HWND WINAPI GetDlgItem(HWND hDlg, int iCtrlID) WCE_LINK(GetDlgItem);
WCE_IMPORT LRESULT WINAPI DefDlgProcA(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(DefDlgProcA);
WCE_IMPORT LRESULT WINAPI DefDlgProcW(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(DefDlgProcW);
WCE_IMPORT BOOL WINAPI SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned) WCE_LINK(SetDlgItemInt);
WCE_IMPORT UINT WINAPI GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL *lpTranslated, BOOL bSigned) WCE_LINK(GetDlgItemInt);
WCE_IMPORT BOOL WINAPI CheckRadioButton(HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton) WCE_LINK(CheckRadioButton);
WCE_IMPORT LONG WINAPI SendDlgItemMessageA(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendDlgItemMessageA);
WCE_IMPORT LONG WINAPI SendDlgItemMessageW(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) WCE_LINK(SendDlgItemMessageW);
WCE_IMPORT BOOL WINAPI SetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPCSTR lpString) WCE_LINK(SetDlgItemTextA);
WCE_IMPORT BOOL WINAPI SetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPCWSTR lpString) WCE_LINK(SetDlgItemTextW);
WCE_IMPORT UINT WINAPI GetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPSTR lpString, int nMaxCount) WCE_LINK(GetDlgItemTextA);
WCE_IMPORT UINT WINAPI GetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPWSTR lpString, int nMaxCount) WCE_LINK(GetDlgItemTextW);
WCE_IMPORT BOOL WINAPI OpenClipboard(HWND hWndNewOwner) WCE_LINK(OpenClipboard);
WCE_IMPORT BOOL WINAPI CloseClipboard(VOID) WCE_LINK(CloseClipboard);
WCE_IMPORT HWND WINAPI GetClipboardOwner(VOID) WCE_LINK(GetClipboardOwner);
WCE_IMPORT HANDLE WINAPI SetClipboardData(UINT uFormat, HANDLE hMem) WCE_LINK(SetClipboardData);
WCE_IMPORT HANDLE WINAPI GetClipboardData(UINT uFormat) WCE_LINK(GetClipboardData);
WCE_IMPORT HANDLE WINAPI GetClipboardDataAlloc(UINT uFormat) WCE_LINK(GetClipboardDataAlloc);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT UINT WINAPI RegisterClipboardFormatA(LPCSTR lpszFormat) WCE_LINK(RegisterClipboardFormatA);
#endif
WCE_IMPORT UINT WINAPI RegisterClipboardFormatW(LPCWSTR lpszFormat) WCE_LINK(RegisterClipboardFormatW);
WCE_IMPORT int WINAPI CountClipboardFormats(VOID) WCE_LINK(CountClipboardFormats);
WCE_IMPORT UINT WINAPI EnumClipboardFormats(UINT format) WCE_LINK(EnumClipboardFormats);
WCE_IMPORT int WINAPI GetClipboardFormatNameA(UINT format, LPSTR lpszFormatName, int cchMaxCount) WCE_LINK(GetClipboardFormatNameA);
WCE_IMPORT int WINAPI GetClipboardFormatNameW(UINT format, LPWSTR lpszFormatName, int cchMaxCount) WCE_LINK(GetClipboardFormatNameW);
WCE_IMPORT BOOL WINAPI EmptyClipboard(VOID) WCE_LINK(EmptyClipboard);
WCE_IMPORT BOOL WINAPI IsClipboardFormatAvailable(UINT format) WCE_LINK(IsClipboardFormatAvailable);
WCE_IMPORT int WINAPI GetPriorityClipboardFormat(UINT *paFormatPriorityList, int cFormats) WCE_LINK(GetPriorityClipboardFormat);
WCE_IMPORT HWND WINAPI GetOpenClipboardWindow(VOID) WCE_LINK(GetOpenClipboardWindow);
WCE_IMPORT HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) WCE_LINK(LoadCursorA);
WCE_IMPORT HCURSOR WINAPI LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName) WCE_LINK(LoadCursorW);
WCE_IMPORT int WINAPI ShowCursor(BOOL bShow) WCE_LINK(ShowCursor);
WCE_IMPORT BOOL WINAPI SetCursorPos(int X, int Y) WCE_LINK(SetCursorPos);
WCE_IMPORT HCURSOR WINAPI SetCursor(HCURSOR hCursor) WCE_LINK(SetCursor);
WCE_IMPORT BOOL WINAPI GetCursorPos(LPPOINT lpPoint) WCE_LINK(GetCursorPos);
WCE_IMPORT BOOL WINAPI ClipCursor(CONST RECT *lpRect) WCE_LINK(ClipCursor);
WCE_IMPORT BOOL WINAPI GetClipCursor(LPRECT lpRect) WCE_LINK(GetClipCursor);
WCE_IMPORT HCURSOR WINAPI GetCursor(VOID) WCE_LINK(GetCursor);
WCE_IMPORT HCURSOR WINAPI LoadAnimatedCursor(HINSTANCE hInstance, DWORD ResourceId, int cFrames, int FrameTimeInterval) WCE_LINK(LoadAnimatedCursor);
WCE_IMPORT BOOL WINAPI KillTimer(HWND hwnd, UINT idEvent) WCE_LINK(KillTimer);
WCE_IMPORT DWORD WINAPI GetKeyboardStatus(VOID) WCE_LINK(GetKeyboardStatus);
WCE_IMPORT BOOL WINAPI EnableHardwareKeyboard(BOOL fEnable) WCE_LINK(EnableHardwareKeyboard);
WCE_IMPORT BOOL WINAPI RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk) WCE_LINK(RegisterHotKey);
WCE_IMPORT BOOL WINAPI UnregisterHotKey(HWND hWnd, int id) WCE_LINK(UnregisterHotKey);
WCE_IMPORT BOOL WINAPI AllKeys(BOOL bAllKeys) WCE_LINK(AllKeys);
WCE_IMPORT BOOL WINAPI SystemParametersInfoA(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni) WCE_LINK(SystemParametersInfoA);
WCE_IMPORT BOOL WINAPI SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni) WCE_LINK(SystemParametersInfoW);
WCE_IMPORT void WINAPI AccessibilitySoundSentryEvent(void) WCE_LINK(AccessibilitySoundSentryEvent);
WCE_IMPORT HICON WINAPI LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName) WCE_LINK(LoadIconA);
WCE_IMPORT HICON WINAPI LoadIconW(HINSTANCE hInstance, LPCWSTR lpIconName) WCE_LINK(LoadIconW);
WCE_IMPORT BOOL WINAPI DestroyIcon(HICON hIcon) WCE_LINK(DestroyIcon);
WCE_IMPORT BOOL WINAPI DrawIconEx(HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) WCE_LINK(DrawIconEx);
WCE_IMPORT HICON WINAPI CreateIconIndirect(PICONINFO piconinfo) WCE_LINK(CreateIconIndirect);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI GetIconInfo(HICON hIcon, PICONINFO piconinfo) WCE_LINK(GetIconInfo);
#endif
WCE_IMPORT HCURSOR WINAPI CreateCursor(HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane) WCE_LINK(CreateCursor);
WCE_IMPORT BOOL WINAPI DestroyCursor(HCURSOR hCursor) WCE_LINK(DestroyCursor);
WCE_IMPORT BOOL WINAPI EnumDisplaySettings(IN LPCTSTR lpszDeviceName, IN DWORD iModeNum, OUT LPDEVMODEW lpDevMode) WCE_LINK(EnumDisplaySettings);
WCE_IMPORT BOOL WINAPI EnumDisplayDevices(IN LPCTSTR lpDevice, IN DWORD iDevNum, OUT PDISPLAY_DEVICE lpDisplayDevice, IN DWORD dwFlags) WCE_LINK(EnumDisplayDevices);
WCE_IMPORT LONG WINAPI ChangeDisplaySettingsEx(IN LPCTSTR lpszDeviceName, IN LPDEVMODE lpDevMode, IN HWND hwnd, IN DWORD dwflags, LPVOID lParam) WCE_LINK(ChangeDisplaySettingsEx);

#define RegisterWindowMessage RegisterWindowMessageW
#define PostMessage PostMessageW
#define PostThreadMessage PostThreadMessageW
#define SendMessage SendMessageW
#define SendNotifyMessage SendNotifyMessageW
#define GetMessage GetMessageW
#define PeekMessage PeekMessageW
#define DispatchMessage DispatchMessageW
#define GetWindowTextLength GetWindowTextLengthW
#define LoadBitmap LoadBitmapW
#define LoadMenu LoadMenuW
#define InsertMenu InsertMenuW
#define AppendMenu AppendMenuW
#define GetMenuItemInfo GetMenuItemInfoW
#define SetMenuItemInfo SetMenuItemInfoW
#define LoadAccelerators LoadAcceleratorsW
#define CreateAcceleratorTable CreateAcceleratorTableW
#define SetWindowText SetWindowTextW
#define GetWindowText GetWindowTextW
#define CreateWindowEx CreateWindowExW
#define CallWindowProc CallWindowProcW
#define RegisterClass RegisterClassW
#define UnregisterClass UnregisterClassW
#define GetClassInfo GetClassInfoW
#define TranslateAccelerator TranslateAcceleratorW
#define DefWindowProc DefWindowProcW
#define GetWindowLong GetWindowLongW
#define SetWindowLong SetWindowLongW
#define FindWindow FindWindowW
#define GetClassName GetClassNameW
#define MessageBox MessageBoxW
#define GetKeyboardLayoutName GetKeyboardLayoutNameW
#define MapVirtualKey MapVirtualKeyW
#define CreateDialogIndirectParam CreateDialogIndirectParamW
#define DialogBoxIndirectParam DialogBoxIndirectParamW
#define IsDialogMessage IsDialogMessageW
#define DefDlgProc DefDlgProcW
#define SendDlgItemMessage SendDlgItemMessageW
#define SetDlgItemText SetDlgItemTextW
#define GetDlgItemText GetDlgItemTextW
#define RegisterClipboardFormat RegisterClipboardFormatW
#define GetClipboardFormatName GetClipboardFormatNameW
#define LoadCursor LoadCursorW
#define SystemParametersInfo SystemParametersInfoW
#define LoadIcon LoadIconW
#define LoadImage LoadImageW
#define MB_ICONINFORMATION MB_ICONASTERISK
#define BS_RIGHTBUTTON BS_LEFTTEXT
#define SWP_NOREPOSITION SWP_NOOWNERZORDER
#define MB_ICONERROR MB_ICONHAND
#define WS_SIZEBOX WS_THICKFRAME
#define SWP_DRAWFRAME SWP_FRAMECHANGED
#define MB_ICONSTOP MB_ICONHAND
#define MB_ICONWARNING MB_ICONEXCLAMATION
#define WM_SETTINGCHANGE WM_WININICHANGE
#define SM_CYFIXEDFRAME SM_CYDLGFRAME
#define SM_CXFIXEDFRAME SM_CXDLGFRAME
#ifdef __cplusplus
}
#endif
#define EN_ALIGN_RTL_EC 0x0701
#define BDR_SUNKENOUTER 0x0002
#define TPM_TOPALIGN 0x0000L
#define SW_SHOW 5
#define SB_TOP 6
#define MIIM_CHECKMARKS 0x00000008
#define SS_CENTERIMAGE 0x00000200L
#define DFCS_SCROLLUP 0x0000
#define MF_END 0x00000080L
#define SPI_GETEXTERNALIDLETIMEOUT 254
#define BS_PUSHLIKE 0x00001000L
#define EN_VSCROLL 0x0602
#define SB_LINELEFT 0
#define VK_DBE_ENTERIMECONFIGMODE 0x0f8
#define SC_KEYMENU 0xF100
#define WM_SYSKEYUP 0x0105
#define WM_IME_REQUEST 0x0288
#define MK_XBUTTON1 0x0020
#define MK_XBUTTON2 0x0040
#define SW_RESTORE 13
#define MIIM_STATE 0x00000001
#define WM_CTLCOLORSCROLLBAR 0x0137
#define VK_RWIN 0x5C
#define WM_CTLCOLORDLG 0x0136
#define WS_CLIPCHILDREN 0x02000000L
#define MB_SETFOREGROUND 0x00010000L
#define SB_BOTTOM 7
#define VK_PAUSE 0x13
#define VK_LBRACKET 0xDB
#define ES_CENTER 0x0001L
#define CBN_CLOSEUP 8
#define SM_CXFULLSCREEN 16
#define WM_IME_CONTROL 0x0283
#define SPI_SETMOUSE 4
#define VK_VOLUME_UP 0xAF
#define WM_IME_KEYUP 0x0291
#define MF_UNCHECKED 0x00000000L
#define BF_TOP 0x0002
#define WM_SETREDRAW 0x000B
#define SM_CYICONSPACING 39
#define SPI_GETHIGHCONTRAST 66
#define WS_CAPTION 0x00C00000L
#define WM_IME_SYSTEM 0x0287
#define CBN_DBLCLK 2
#define GW_HWNDLAST 1
#define WM_CLOSE 0x0010
#define SPI_GETSCREENSAVETIMEOUT 14
#define DFCS_CAPTIONRESTORE 0x0003
#define SW_SHOWMAXIMIZED 11
#define SW_HIDE 0
#define BF_RIGHT 0x0004
#define SS_NOPREFIX 0x00000080L
#define SWP_NOMOVE 0x0002
#define VK_HELP 0x2F
#define MB_ICONASTERISK 0x00000040L
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define SPI_SETWHEELSCROLLLINES 105
#define GW_HWNDFIRST 0
#define SPI_GETSOUNDSENTRY 64
#define WM_HIBERNATE 0x03FF
#define SB_LINEUP 0
#define BS_TOP 0x00000400L
#define EN_SETFOCUS 0x0100
#define WM_IME_STARTCOMPOSITION 0x010D
#define MIIM_SUBMENU 0x00000004
#define SWP_NOZORDER 0x0004
#define SMTO_NORMAL 0x0000
#define RDW_VALIDATE 0x0008
#define VK_DBE_KATAKANA 0x0f1
#define PM_REMOVE 0x0001
#define WS_MINIMIZEBOX 0x00010000L
#define SPI_GETPLATFORMTYPE 257
#define WS_DISABLED 0x08000000L
#define SM_CXVIRTUALSCREEN 78
#define WM_DESTROY 0x0002
#define SIZE_MINIMIZED 1
#define HWND_TOP ((HWND)0)
#define EN_ALIGN_LTR_EC 0x0700
#define WM_XBUTTONDOWN 0x020B
#define VK_DBE_ALPHANUMERIC 0x0f0
#define WM_KEYFIRST 0x0100
#define RDW_ERASENOW 0x0200
#define BS_LEFTTEXT 0x00000020L
#define SS_LEFTNOWORDWRAP 0x0000000CL
#define HWND_BROADCAST ((HWND)0xffff)
#define SPI_GETBATTERYIDLETIMEOUT 252
#define WM_TIMER 0x0113
#define VK_MBUTTON 0x04
#define GW_HWNDPREV 3
#define EN_HSCROLL 0x0601
#define WM_LBUTTONDBLCLK 0x0203
#define WM_VKEYTOITEM 0x002E
#define CBN_SETFOCUS 3
#define SPI_SETLANGTOGGLE 91
#define VK_F14 0x7D
#define SW_MINIMIZE 6
#define BS_BOTTOM 0x00000800L
#define BS_OWNERDRAW 0x0000000BL
#define WM_MOUSEFIRST 0x0200
#define DFCS_SCROLLDOWN 0x0001
#define SM_CYVIRTUALSCREEN 79
#define WM_APP 0x8000
#define SW_SHOWNORMAL 1
#define EN_UPDATE 0x0400
#define GWL_EXSTYLE (-20)
#define CS_IME 0x00010000
#define VK_ATTN 0xF6
#define VK_LAUNCH_APP1 0xB6
#define QS_TIMER 0x0010
#define SPI_GETSTICKYKEYS 58
#define VK_MEDIA_PLAY_PAUSE 0xB3
#define WM_CONTEXTMENU 0x007B
#define WM_INITMENUPOPUP 0x0117
#define VK_DBE_ROMAN 0x0f5
#define VK_LMENU 0xA4
#define WM_MBUTTONDOWN 0x0207
#define SW_SHOWNOACTIVATE 4
#define SM_CYHSCROLL 3
#define SPI_GETWORKAREA 48
#define SM_CXDOUBLECLK 36
#define VK_DELETE 0x2E
#define QS_MOUSEMOVE 0x0002
#define SW_MAXIMIZE 12
#define MF_UNHILITE 0x00000000L
#define VK_OEM_102 0xE2
#define WM_SETICON 0x0080
#define SPI_GETTOGGLEKEYS 52
#define SM_CXVSCROLL 2
#define SB_LEFT 6
#define VK_OFF 0xDF
#define SB_VERT 1
#define WM_HELP 0x0053
#define WM_CREATE 0x0001
#define MF_MENUBARBREAK 0x00000020L
#define WM_SETFOCUS 0x0007
#define RDW_NOERASE 0x0020
#define DFCS_BUTTON3STATE 0x0008
#define BS_3STATE 0x00000005L
#define CBN_SELENDOK 9
#define ES_READONLY 0x0800L
#define WS_EX_ABOVESTARTUP 0x20000000L
#define VK_ESCAPE 0x1B
#define WM_CHAR 0x0102
#define DFCS_CAPTIONOKBTN 0x0080
#define MB_ICONHAND 0x00000010L
#define WS_VSCROLL 0x00200000L
#define TPM_VCENTERALIGN 0x0010L
#define WM_SYSKEYDOWN 0x0104
#define SM_CXSCREEN 0
#define MB_RETRYCANCEL 0x00000005L
#define WM_CLEAR 0x0303
#define SPI_SETFONTSMOOTHING 0x004B
#define LBN_SELCHANGE 1
#define TPM_LEFTALIGN 0x0000L
#define SM_CXCURSOR 13
#define WM_CTLCOLOREDIT 0x0133
#define VK_BACK 0x08
#define WS_EX_NOACTIVATE 0x08000000L
#define WM_IM_INFO 0x010C
#define VK_SLASH 0xBF
#define VK_SEPARATOR 0x6C
#define WM_ACTIVATE 0x0006
#define VK_PLAY 0xFA
#define VK_F1 0x70
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define SM_CYDOUBLECLK 37
#define SPI_GETWHEELSCROLLLINES 104
#define VK_F3 0x72
#define MF_STRING 0x00000000L
#define CS_SAVEBITS 0x0800
#define VK_F2 0x71
#define SS_BITMAP 0x0000000EL
#define WM_DEADCHAR 0x0103
#define DFCS_CAPTIONHELP 0x0004
#define VK_HOME 0x24
#define VK_DBE_ENTERDLGCONVERSIONMODE 0x0fd
#define HWND_TOPMOST ((HWND)-1)
#define WM_CAPTURECHANGED 0x0215
#define WM_PASTE 0x0302
#define BS_GROUPBOX 0x00000007L
#define WM_DESTROYCLIPBOARD 0x0307
#define WS_HSCROLL 0x00100000L
#define WM_CTLCOLORMSGBOX 0x0132
#define VK_F20 0x83
#define BS_AUTO3STATE 0x00000006L
#define WM_UNDO 0x0304
#define VK_SCROLL 0x91
#define VK_MULTIPLY 0x6A
#define WM_SIZE 0x0005
#define MB_DEFBUTTON4 0x00000300L
#define MF_MENUBREAK 0x00000040L
#define DFC_CAPTION 1
#define VK_NUMPAD0 0x60
#define VK_NONAME 0xFC
#define CBN_KILLFOCUS 4
#define VK_NUMPAD3 0x63
#define WM_GETFONT 0x0031
#define VK_NUMPAD5 0x65
#define GW_MAX 5
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define WS_VISIBLE 0x10000000L
#define VK_ZOOM 0xFB
#define BS_RIGHT 0x00000200L
#define WS_TABSTOP 0x00010000L
#define QS_KEY 0x0001
#define SWP_NOSIZE 0x0001
#define ES_AUTOVSCROLL 0x0040L
#define VK_LAUNCH_MAIL 0xB4
#define WS_EX_INK 0x10000000L
#define VK_DBE_CODEINPUT 0x0fa
#define EN_MAXTEXT 0x0501
#define RDW_ALLCHILDREN 0x0080
#define WM_IME_ENDCOMPOSITION 0x010E
#define MF_OWNERDRAW 0x00000100L
#define WS_EX_RIGHT 0x00001000L
#define HWND_DESKTOP ((HWND)0)
#define RDW_INTERNALPAINT 0x0002
#define WM_RBUTTONUP 0x0205
#define SPI_GETMOUSEKEYS 54
#define MB_ICONQUESTION 0x00000020L
#define SW_SHOWNA 8
#define BS_VCENTER 0x00000C00L
#define BS_AUTORADIOBUTTON 0x00000009L
#define WM_RBUTTONDBLCLK 0x0206
#define BDR_OUTER 0x0003
#define SPI_SETDESKPATTERN 21
#define VK_ADD 0x6B
#define DFCS_CAPTIONALL 0x000F
#define DFCS_BUTTONCHECK 0x0000
#define VK_MENU 0x12
#define MF_BYPOSITION 0x00000400L
#define VK_DBE_NOCODEINPUT 0x0fb
#define WS_EX_CLIENTEDGE 0x00000200L
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD4 0x64
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_BROWSER_FAVORITES 0xAB
#define VK_HANGEUL 0x15
#define ES_LEFT 0x0000L
#define SPI_GETPLATFORMNAME 260
#define SB_ENDSCROLL 8
#define BS_DEFPUSHBUTTON 0x00000001L
#define LBN_SELCANCEL 3
#define VK_DBE_NOROMAN 0x0f6
#define MK_MBUTTON 0x0010
#define WM_SYSCHAR 0x0106
#define VK_HANJA 0x19
#define SPI_GETPROJECTNAME 259
#define WS_THICKFRAME 0x00040000L
#define SM_CMONITORS 80
#define RDW_INVALIDATE 0x0001
#define QS_SENDMESSAGE 0x0040
#define WS_POPUP 0x80000000L
#define VK_UP 0x26
#define MB_DEFBUTTON1 0x00000000L
#define MB_DEFBUTTON2 0x00000100L
#define MB_DEFBUTTON3 0x00000200L
#define BDR_RAISEDOUTER 0x0001
#define SPI_GETSHOWSOUNDS 56
#define BF_FLAT 0x4000
#define TPM_VERTICAL 0x0040L
#define DFCS_CHECKED 0x0400
#define WS_EX_TOPMOST 0x00000008L
#define WM_GETTEXTLENGTH 0x000E
#define WM_NOTIFY 0x004E
#define WM_PALETTECHANGED 0x0311
#define SW_INVALIDATE 0x0002
#define WM_SETFONT 0x0030
#define SM_SAMEDISPLAYFORMAT 81
#define VK_RSHIFT 0xA1
#define VK_HANGUL 0x15
#define QS_MOUSEBUTTON 0x0004
#define GWL_USERDATA (-21)
#define SM_XVIRTUALSCREEN 76
#define MB_APPLMODAL 0x00000000L
#define MIIM_ID 0x00000002
#define WM_SYSDEADCHAR 0x0107
#define VK_DECIMAL 0x6E
#define VK_APOSTROPHE 0xDE
#define PM_NOREMOVE 0x0000
#define VK_KANJI 0x19
#define RDW_NOCHILDREN 0x0040
#define WM_QUERYNEWPALETTE 0x030F
#define VK_EXSEL 0xF8
#define SPI_SETACCESSTIMEOUT 61
#define SM_CXBORDER 5
#define VK_CRSEL 0xF7
#define SPI_SETSCREENSAVETIMEOUT 15
#define EN_CHANGE 0x0300
#define VK_CLEAR 0x0C
#define SS_CENTER 0x00000001L
#define SM_CYEDGE 46
#define CBN_DROPDOWN 7
#define VK_SNAPSHOT 0x2C
#define BS_PUSHBUTTON 0x00000000L
#define WM_KEYDOWN 0x0100
#define SPI_GETOEMINFO 258
#define VK_DBE_DETERMINESTRING 0x0fc
#define VK_PA1 0xFD
#define VK_MEDIA_STOP 0xB2
#define VK_CONTROL 0x11
#define LBN_ERRSPACE (-2)
#define WM_NETCONNECT 0x03FE
#define MB_YESNO 0x00000004L
#define VK_SEMICOLON 0xBA
#define WM_LBUTTONDOWN 0x0201
#define VK_EQUAL 0xBB
#define WS_EX_CONTEXTHELP 0x00000400L
#define VK_F22 0x85
#define VK_F24 0x87
#define SM_YVIRTUALSCREEN 77
#define SIZE_MAXIMIZED 2
#define DFCS_INACTIVE 0x0100
#define SWP_NOOWNERZORDER 0x0200
#define GWL_ID (-12)
#define WM_DBNOTIFICATION 0x03FD
#define MB_OKCANCEL 0x00000001L
#define BS_RADIOBUTTON 0x00000004L
#define SPI_SETWAKEUPIDLETIMEOUT 255
#define TPM_BOTTOMALIGN 0x0020L
#define VK_EREOF 0xF9
#define VK_END 0x23
#define VK_XBUTTON1 0x05
#define VK_XBUTTON2 0x06
#define WS_CLIPSIBLINGS 0x04000000L
#define WM_SYSCOMMAND 0x0112
#define WS_EX_TOOLWINDOW 0x00000080L
#define ES_WANTRETURN 0x1000L
#define WS_CHILD 0x40000000L
#define WM_CTLCOLORBTN 0x0135
#define VK_BROWSER_BACK 0xA6
#define BN_KILLFOCUS 7
#define VK_KANA 0x15
#define CBN_EDITUPDATE 6
#define WM_ENABLE 0x000A
#define BS_NOTIFY 0x00004000L
#define SWP_SHOWWINDOW 0x0040
#define WM_PAINT 0x000F
#define TPM_RETURNCMD 0x0100L
#define DFCS_BUTTONRADIO 0x0004
#define SB_RIGHT 7
#define RDW_ERASE 0x0004
#define MB_YESNOCANCEL 0x00000003L
#define WM_QUERYDRAGICON 0x0037
#define VK_CAPITAL 0x14
#define MF_GRAYED 0x00000001L
#define SB_LINERIGHT 1
#define VK_BROWSER_HOME 0xAC
#define MF_HILITE 0x00000080L
#define BF_BOTTOM 0x0008
#define VK_PROCESSKEY 0xE5
#define DFCS_BUTTONPUSH 0x0010
#define CS_VREDRAW 0x0001
#define WM_COPY 0x0301
#define SB_PAGERIGHT 3
#define SPI_GETPLATFORMMANUFACTURER 262
#define MIIM_DATA 0x00000020
#define ES_COMBOBOX 0x0200L
#define SPI_SETDESKWALLPAPER 20
#define RDW_UPDATENOW 0x0100
#define CBN_ERRSPACE (-1)
#define QS_PAINT 0x0020
#define WM_FONTCHANGE 0x001D
#define WM_CTLCOLORSTATIC 0x0138
#define SPI_SETSHOWSOUNDS 57
#define WM_RENDERFORMAT 0x0305
#define VK_TAB 0x09
#define VK_EXTEND_BSLASH 0xE2
#define BS_AUTOCHECKBOX 0x00000003L
#define SM_CXEDGE 45
#define SIZE_RESTORED 0
#define SPI_GETGUIDPATTERN 264
#define WM_INPUTLANGCHANGE 0x0051
#define WA_ACTIVE 1
#define SM_CYSMICON 50
#define CBN_SELENDCANCEL 10
#define VK_OEM_CLEAR 0xFE
#define ES_MULTILINE 0x0004L
#define EN_KILLFOCUS 0x0200
#define CS_NOCLOSE 0x0200
#define SM_CYDLGFRAME 8
#define VK_NOCONVERT 0x1d
#define SPI_SETHIGHCONTRAST 67
#define VK_RBUTTON 0x02
#define SIZE_MAXSHOW 3
#define VK_HYPHEN 0xBD
#define WM_MEASUREITEM 0x002C
#define SWP_NOACTIVATE 0x0010
#define WM_STYLECHANGED 0x007D
#define GW_OWNER 4
#define VK_BACKSLASH 0xDC
#define SM_MOUSEPRESENT 19
#define BS_MULTILINE 0x00002000L
#define SPI_SETSTICKYKEYS 59
#define DI_IMAGE 0x0002
#define DFCS_CAPTIONMAX 0x0002
#define SPI_GETMOUSE 3
#define GWL_WNDPROC (-4)
#define WM_MOUSELAST 0x020D
#define MK_SHIFT 0x0004
#define EN_ERRSPACE 0x0500
#define SPI_SETBATTERYIDLETIMEOUT 251
#define BDR_SUNKEN 0x000A
#define WM_IME_SETCONTEXT 0x0281
#define VK_FINAL 0x18
#define IMAGE_BITMAP 0
#define SPI_GETBOOTMENAME 261
#define SB_PAGEDOWN 3
#define DFCS_PUSHED 0x0200
#define SWP_HIDEWINDOW 0x0080
#define SC_CLOSE 0xF060
#define WS_EX_RTLREADING 0x00002000L
#define WM_MBUTTONUP 0x0208
#define VK_CONVERT 0x1c
#define WM_GETICON 0x007F
#define SM_CYVSCROLL 20
#define WS_EX_DLGMODALFRAME 0x00000001L
#define SPI_SETTOGGLEKEYS 53
#define SS_RIGHT 0x00000002L
#define WM_SHOWWINDOW 0x0018
#define ES_NUMBER 0x2000L
#define WM_MENUCHAR 0x0120
#define DFCS_CAPTIONMIN 0x0001
#define TPM_CENTERALIGN 0x0004L
#define WM_WINDOWPOSCHANGED 0x0047
#define WS_BORDER 0x00800000L
#define VK_LBUTTON 0x01
#define WM_COPYDATA 0x004A
#define WM_IME_NOTIFY 0x0282
#define BF_LEFT 0x0001
#define VK_JUNJA 0x17
#define SM_CYMENU 15
#define WS_SYSMENU 0x00080000L
#define SS_ICON 0x00000003L
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define CS_PARENTDC 0x0080
#define WS_MAXIMIZEBOX 0x00020000L
#define MIIM_TYPE 0x00000010
#define VK_F21 0x84
#define WM_USER 0x0400
#define VK_F23 0x86
#define SM_DEBUG 22
#define BDR_RAISED 0x0005
#define SPI_SETSOUNDSENTRY 65
#define WA_CLICKACTIVE 2
#define VK_DBE_FLUSHSTRING 0x0f9
#define WM_CANCELMODE 0x001F
#define WM_IME_COMPOSITIONFULL 0x0284
#define BS_CHECKBOX 0x00000002L
#define CS_HREDRAW 0x0002
#define WM_COMPAREITEM 0x0039
#define WM_IME_KEYDOWN 0x0290
#define VK_MEDIA_PREV_TRACK 0xB1
#define QS_POSTMESSAGE 0x0008
#define WS_EX_STATICEDGE 0x00020000L
#define SM_CYICON 12
#define WM_IME_CHAR 0x0286
#define BN_DBLCLK 5
#define WM_KILLFOCUS 0x0008
#define ES_AUTOHSCROLL 0x0080L
#define DFCS_SCROLLLEFT 0x0002
#define WM_DRAWITEM 0x002B
#define WS_EX_LAYOUTRTL 0x00400000L
#define SW_SCROLLCHILDREN 0x0001
#define VK_DIVIDE 0x6F
#define CS_DBLCLKS 0x0008
#define BDR_RAISEDINNER 0x0004
#define SB_PAGELEFT 2
#define WM_EXITMENULOOP 0x0212
#define GWL_STYLE (-16)
#define MF_ENABLED 0x00000000L
#define MK_CONTROL 0x0008
#define SM_CYCAPTION 4
#define DFCS_SCROLLRIGHT 0x0003
#define WS_EX_LEFTSCROLLBAR 0x00004000L
#define TPM_NONOTIFY 0x0080L
#define DFC_SCROLL 3
#define SPI_GETFONTSMOOTHING 0x004A
#define WM_SETTEXT 0x000C
#define VK_NEXT 0x22
#define WM_KEYUP 0x0101
#define ES_RIGHT 0x0002L
#define SM_CXICONSPACING 38
#define WM_COMMAND 0x0111
#define SM_CYSCREEN 1
#define MF_SEPARATOR 0x00000800L
#define WM_NULL 0x0000
#define CW_USEDEFAULT ((int)0x80000000)
#define SM_CYCURSOR 14
#define WS_EX_NOANIMATION 0x04000000L
#define VK_BROWSER_FORWARD 0xA7
#define VK_EXECUTE 0x2B
#define WM_CHARTOITEM 0x002F
#define WS_EX_NODRAG 0x40000000L
#define WM_CTLCOLORLISTBOX 0x0134
#define VK_VOLUME_MUTE 0xAD
#define SPI_GETWAKEUPIDLETIMEOUT 256
#define WM_SETCURSOR 0x0020
#define SM_CYFULLSCREEN 17
#define SM_CXICON 11
#define VK_APPS 0x5D
#define BN_SETFOCUS 6
#define WS_EX_NOINHERITLAYOUT 0x00100000L
#define VK_COMMA 0xBC
#define BF_DIAGONAL 0x0010
#define VK_RMENU 0xA5
#define SPI_GETDEFAULTINPUTLANG 89
#define WM_VSCROLL 0x0115
#define WM_DELETEITEM 0x002D
#define CS_GLOBALCLASS 0x4000
#define WM_IME_COMPOSITION 0x010F
#define VK_DBE_SBCSCHAR 0x0f3
#define MB_ABORTRETRYIGNORE 0x00000002L
#define BF_TOPRIGHT (BF_TOP | BF_RIGHT)
#define VK_BROWSER_SEARCH 0xAA
#define VK_RCONTROL 0xA3
#define WM_MOVE 0x0003
#define VK_NUMLOCK 0x90
#define SB_PAGEUP 2
#define WM_WININICHANGE 0x001A
#define WM_SYSCOLORCHANGE 0x0015
#define VK_CANCEL 0x03
#define BF_MONO 0x8000
#define GW_CHILD 5
#define EDGE_ETCHED (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define VK_PERIOD 0xBE
#define VK_LAUNCH_APP2 0xB7
#define VK_BROWSER_REFRESH 0xA8
#define SM_CXSMICON 49
#define WS_DLGFRAME 0x00400000L
#define VK_PRINT 0x2A
#define CBN_EDITCHANGE 5
#define BN_CLICKED 0
#define VK_RBRACKET 0xDD
#define WS_EX_CAPTIONOKBTN 0x80000000L
#define VK_PRIOR 0x21
#define WM_RBUTTONDOWN 0x0204
#define VK_LWIN 0x5B
#define WM_QUIT 0x0012
#define BS_CENTER 0x00000300L
#define VK_RETURN 0x0D
#define SWP_FRAMECHANGED 0x0020
#define VK_BACKQUOTE 0xC0
#define BDR_SUNKENINNER 0x0008
#define LBN_DBLCLK 2
#define VK_SUBTRACT 0x6D
#define DI_MASK 0x0001
#define MB_ICONEXCLAMATION 0x00000030L
#define WM_MOUSEMOVE 0x0200
#define WM_XBUTTONUP 0x020C
#define SB_BOTH 3
#define LR_DEFAULTCOLOR 0x0000
#define WM_INITDIALOG 0x0110
#define WM_ENTERMENULOOP 0x0211
#define ES_LOWERCASE 0x0010L
#define VK_MEDIA_NEXT_TRACK 0xB0
#define BF_ADJUST 0x2000
#define TPM_HORIZONTAL 0x0000L
#define ES_OEMCONVERT 0x0400L
#define IMAGE_CURSOR 2
#define SPI_GETACCESSTIMEOUT 60
#define DFCS_SCROLLCOMBOBOX 0x0005
#define VK_BROWSER_STOP 0xA9
#define MK_RBUTTON 0x0002
#define WM_RENDERALLFORMATS 0x0306
#define SB_CTL 2
#define SM_CXDLGFRAME 7
#define HWND_NOTOPMOST ((HWND)-2)
#define LBN_KILLFOCUS 5
#define VK_LSHIFT 0xA0
#define BS_TEXT 0x00000000L
#define WM_GETTEXT 0x000D
#define WS_EX_WINDOWEDGE 0x00000100L
#define SB_THUMBTRACK 5
#define WM_NEXTDLGCTL 0x0028
#define BN_PAINT 1
#define WM_MBUTTONDBLCLK 0x0209
#define SW_ERASE 0x0004
#define SS_LEFT 0x00000000L
#define DFC_BUTTON 4
#define VK_SPACE 0x20
#define MB_RTLREADING 0x00100000L
#define MF_BYCOMMAND 0x00000000L
#define WS_GROUP 0x00020000L
#define VK_RIGHT 0x27
#define HWND_BOTTOM ((HWND)1)
#define WM_XBUTTONDBLCLK 0x020D
#define SPI_SETMOUSEKEYS 55
#define SPI_SETFONTSMOOTHINGCONTRAST 0x200D
#define MF_POPUP 0x00000010L
#define VK_SELECT 0x29
#define PM_NOYIELD 0x0002
#define VK_SLEEP 0x5F
#define VK_LCONTROL 0xA2
#define SPI_GETUUID 263
#define BF_DIAGONAL_ENDTOPLEFT (BF_DIAGONAL | BF_TOP | BF_LEFT)
#define WM_KEYLAST 0x0108
#define VK_DOWN 0x28
#define WM_LBUTTONUP 0x0202
#define WM_IME_KEYLAST 0x010F
#define SB_THUMBPOSITION 4
#define MB_TOPMOST 0x00040000L
#define GW_HWNDNEXT 2
#define BF_SOFT 0x1000
#define SIZE_MAXHIDE 4
#define SPI_SETEXTERNALIDLETIMEOUT 253
#define MK_LBUTTON 0x0001
#define WM_ERASEBKGND 0x0014
#define WM_IME_SELECT 0x0285
#define TPM_RIGHTALIGN 0x0008L
#define VK_VOLUME_DOWN 0xAE
#define SPI_SETWORKAREA 47
#define BS_LEFT 0x00000100L
#define WM_HSCROLL 0x0114
#define SS_NOTIFY 0x00000100L
#define ES_UPPERCASE 0x0008L
#define VK_DBE_DBCSCHAR 0x0f4
#define VK_INSERT 0x2D
#define ES_NOHIDESEL 0x0100L
#define BF_MIDDLE 0x0800
#define SPI_GETFONTSMOOTHINGCONTRAST 0x200C
#define WA_INACTIVE 0
#define CBN_SELCHANGE 1
#define VK_LEFT 0x25
#define SM_CYBORDER 6
#define WM_CUT 0x0300
#define WM_INPUTLANGCHANGEREQUEST 0x0050
#define WM_MOUSEWHEEL 0x020A
#define VK_DBE_ENTERWORDREGISTERMODE 0x0f7
#define MF_CHECKED 0x00000008L
#define ES_PASSWORD 0x0020L
#define DI_NORMAL 0x0003
#define LBN_SETFOCUS 4
#define IMAGE_ICON 1
#define BDR_INNER 0x000C
#define VK_DBE_HIRAGANA 0x0f2
#define SB_HORZ 0
#define WM_HOTKEY 0x0312
#define SB_LINEDOWN 1
#define SM_CXHSCROLL 21
#define MB_OK 0x00000000L
#define DFCS_CAPTIONCLOSE 0x0000
#define WM_GETDLGCODE 0x0087
#define VK_SHIFT 0x10
#define BF_BOTTOMLEFT (BF_BOTTOM | BF_LEFT)
#define QS_MOUSE (QS_MOUSEMOVE | QS_MOUSEBUTTON)
#define BF_DIAGONAL_ENDTOPRIGHT (BF_DIAGONAL | BF_TOP | BF_RIGHT)
#define BF_TOPLEFT (BF_TOP | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMRIGHT (BF_DIAGONAL | BF_BOTTOM | BF_RIGHT)
#define BF_DIAGONAL_ENDBOTTOMLEFT (BF_DIAGONAL | BF_BOTTOM | BF_LEFT)
#define QS_INPUT (QS_MOUSE | QS_KEY)
#define EDGE_RAISED (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP (BDR_RAISEDOUTER | BDR_SUNKENINNER)
#define BF_BOTTOMRIGHT (BF_BOTTOM | BF_RIGHT)
#define WS_OVERLAPPED WS_BORDER | WS_CAPTION
#define EDGE_SUNKEN (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define BF_RECT (BF_LEFT | BF_RIGHT | BF_TOP | BF_BOTTOM)
#define QS_ALLEVENTS (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT)
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define QS_ALLINPUT (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_SENDMESSAGE)
#define SYS_COLOR_INDEX_FLAG 0x40000000
#define COLOR_ACTIVEBORDER (10 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INFOBK (24 | SYS_COLOR_INDEX_FLAG)
#define COLOR_APPWORKSPACE (12 | SYS_COLOR_INDEX_FLAG)
#define COLOR_3DLIGHT (22 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNSHADOW (16 | SYS_COLOR_INDEX_FLAG)
#define COLOR_ACTIVECAPTION ( 2 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNTEXT (18 | SYS_COLOR_INDEX_FLAG)
#define COLOR_STATICTEXT (26 | SYS_COLOR_INDEX_FLAG)
#define COLOR_HIGHLIGHTTEXT (14 | SYS_COLOR_INDEX_FLAG)
#define COLOR_3DDKSHADOW (21 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INFOTEXT (23 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOWTEXT ( 8 | SYS_COLOR_INDEX_FLAG)
#define COLOR_GRAYTEXT (17 | SYS_COLOR_INDEX_FLAG)
#define COLOR_MENU ( 4 | SYS_COLOR_INDEX_FLAG)
#define COLOR_HIGHLIGHT (13 | SYS_COLOR_INDEX_FLAG)
#define COLOR_MENUTEXT ( 7 | SYS_COLOR_INDEX_FLAG)
#define COLOR_SCROLLBAR ( 0 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNHIGHLIGHT (20 | SYS_COLOR_INDEX_FLAG)
#define COLOR_GRADIENTACTIVECAPTION (27 | SYS_COLOR_INDEX_FLAG)
#define COLOR_STATIC (25 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOWFRAME ( 6 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOW ( 5 | SYS_COLOR_INDEX_FLAG)
#define COLOR_3DHIGHLIGHT COLOR_BTNHIGHLIGHT
#define COLOR_GRADIENTINACTIVECAPTION (28 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INACTIVEBORDER (11 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BACKGROUND ( 1 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNFACE (15 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INACTIVECAPTION ( 3 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INACTIVECAPTIONTEXT (19 | SYS_COLOR_INDEX_FLAG)
#define COLOR_CAPTIONTEXT ( 9 | SYS_COLOR_INDEX_FLAG)
#define COLOR_3DSHADOW COLOR_BTNSHADOW
#define COLOR_DESKTOP COLOR_BACKGROUND
#define COLOR_3DHILIGHT COLOR_BTNHIGHLIGHT
#define COLOR_3DFACE COLOR_BTNFACE
#endif

