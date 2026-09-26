/* User interface: windows, messages, painting. Original text.
 * Exported by coredll.dll.
 */
#ifndef AKARI_WCE_WINUSER_H
#define AKARI_WCE_WINUSER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "wingdi.h"

#define WM_NULL             0x0000
#define WM_CREATE           0x0001
#define WM_DESTROY          0x0002
#define WM_MOVE             0x0003
#define WM_SIZE             0x0005
#define WM_ACTIVATE         0x0006
#define WM_SETFOCUS         0x0007
#define WM_KILLFOCUS        0x0008
#define WM_ENABLE           0x000A
#define WM_SETREDRAW        0x000B
#define WM_SETTEXT          0x000C
#define WM_GETTEXT          0x000D
#define WM_GETTEXTLENGTH    0x000E
#define WM_PAINT            0x000F
#define WM_CLOSE            0x0010
#define WM_QUIT             0x0012
#define WM_ERASEBKGND       0x0014
#define WM_SHOWWINDOW       0x0018
#define WM_SETTINGCHANGE    0x001A
#define WM_WININICHANGE     WM_SETTINGCHANGE
#define WM_GETFONT          0x0031
#define WM_SETFONT          0x0030
#define WM_GETICON          0x007F
#define WM_SETICON          0x0080
#define WM_NCCREATE         0x0081
#define WM_NCDESTROY        0x0082
#define WM_NCPAINT          0x0085
#define WM_NCACTIVATE       0x0086
#define WM_KEYDOWN          0x0100
#define WM_KEYUP            0x0101
#define WM_CHAR             0x0102
#define WM_DEADCHAR         0x0103
#define WM_SYSKEYDOWN       0x0104
#define WM_SYSKEYUP         0x0105
#define WM_SYSCHAR          0x0106
#define WM_INITDIALOG       0x0110
#define WM_COMMAND          0x0111
#define WM_SYSCOMMAND       0x0112
#define WM_TIMER            0x0113
#define WM_HSCROLL          0x0114
#define WM_VSCROLL          0x0115
#define WM_INITMENU         0x0116
#define WM_MENUSELECT       0x011F
#define WM_MOUSEMOVE        0x0200
#define WM_LBUTTONDOWN      0x0201
#define WM_LBUTTONUP        0x0202
#define WM_LBUTTONDBLCLK    0x0203
#define WM_RBUTTONDOWN      0x0204
#define WM_RBUTTONUP        0x0205
#define WM_CAPTURECHANGED   0x0215
#define WM_ACTIVATEAPP      0x001C
#define WM_DEVICECHANGE     0x0020
#define WM_HOTKEY           0x0312
#define WM_USER             0x0400
#define WM_APP              0x8000

#define CS_VREDRAW        0x0001
#define CS_HREDRAW        0x0002
#define CS_DBLCLKS        0x0008
#define CS_OWNDC          0x0020
#define CS_CLASSDC        0x0040
#define CS_NOCLOSE        0x0200
#define CS_SAVEBITS       0x0800
#define CS_PARENTDC       0x0080

#define WS_OVERLAPPED WS_BORDER | WS_CAPTION
#define WS_TILED        WS_OVERLAPPED
#define WS_TABSTOP      0x00010000
#define WS_MAXIMIZEBOX  0x00020000
#define WS_GROUP        0x00020000
#define WS_MINIMIZEBOX  0x00010000
#define WS_THICKFRAME   0x00040000
#define WS_CAPTION      0x00C00000
#define WS_BORDER       0x00800000
#define WS_DLGFRAME     0x00400000
#define WS_VSCROLL      0x00200000
#define WS_HSCROLL      0x00100000
#define WS_SYSMENU      0x00080000
#define WS_VISIBLE      0x10000000
#define WS_CHILD        0x40000000
#define WS_CHILDWINDOW  WS_CHILD
#define WS_POPUP        0x80000000
#define WS_DISABLED     0x08000000
#define WS_CLIPCHILDREN 0x02000000
#define WS_CLIPSIBLINGS 0x04000000

#define WS_EX_TOPMOST        0x00000008
#define WS_EX_CAPTIONOKBTN   0x80000000L
#define WS_EX_CLIENTEDGE     0x00000200
#define WS_EX_STATICEDGE     0x00020000
#define WS_EX_NODRAG         0x40000000L
#define WS_EX_NOANIMATION    0x04000000L
#define WS_EX_ABOVESTARTUP   0x20000000L
#define WS_EX_INK            0x10000000L
#define WS_EX_LAYERED        0x00080000

#define SW_HIDE            0
#define SW_SHOWNORMAL      1
#define SW_SHOWMINIMIZED   2
#define SW_SHOWNA          8
#define SW_SHOWMAXIMIZED   11
#define SW_MAXIMIZE        12
#define SW_SHOWNOACTIVATE  4
#define SW_SHOW            5
#define SW_MINIMIZE        6
#define SW_RESTORE         13
#define SW_SHOWDEFAULT     10
#define SW_MAX             10

#define MB_OK              0x00000000
#define MB_OKCANCEL        0x00000001
#define MB_ABORTRETRYIGNORE 0x00000002
#define MB_YESNOCANCEL     0x00000003
#define MB_YESNO           0x00000004
#define MB_ICONHAND        0x00000010
#define MB_ICONQUESTION    0x00000020
#define MB_ICONEXCLAMATION 0x00000030
#define MB_ICONASTERISK    0x00000040
#define MB_DEFBUTTON1      0x00000000
#define MB_DEFBUTTON2      0x00000100
#define MB_TOPMOST         0x00040000
#define IDOK     1
#define IDCANCEL 2
#define IDABORT  3
#define IDRETRY  4
#define IDIGNORE 5
#define IDYES    6
#define IDNO     7

#define CW_USEDEFAULT ((int)0x80000000)
#define HWND_TOP      ((HWND)0)
#define HWND_BOTTOM   ((HWND)1)
#define HWND_TOPMOST  ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)

#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SM_CXVSCROLL 2
#define SM_CYHSCROLL 3
#define SM_CYCAPTION 4
#define SM_CXBORDER  5
#define SM_CYBORDER  6
#define SM_CXEDGE    45
#define SM_CYEDGE    46
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79

#define RDW_INVALIDATE   0x0001
#define RDW_ERASE        0x0004
#define RDW_VALIDATE     0x0008
#define RDW_ALLCHILDREN  0x0080
#define RDW_UPDATENOW    0x0100
#define RDW_FRAME        0x0400

#define GW_HWNDFIRST 0
#define GW_HWNDLAST  1
#define GW_HWNDNEXT  2
#define GW_HWNDPREV  3
#define GW_OWNER     4
#define GW_CHILD     5

#define GWL_WNDPROC    (-4)
#define GWL_HINSTANCE  (-6)
#define GWL_HWNDPARENT (-8)
#define GWL_ID         (-12)
#define GWL_STYLE      (-16)
#define GWL_EXSTYLE    (-20)
#define GWL_USERDATA   (-21)

#define SYS_COLOR_INDEX_FLAG 0x40000000

#define COLOR_SCROLLBAR      ( 0 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BACKGROUND    ( 1 | SYS_COLOR_INDEX_FLAG)
#define COLOR_ACTIVECAPTION ( 2 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INACTIVECAPTION ( 3 | SYS_COLOR_INDEX_FLAG)
#define COLOR_MENU          ( 4 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOW        ( 5 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOWFRAME   ( 6 | SYS_COLOR_INDEX_FLAG)
#define COLOR_MENUTEXT      ( 7 | SYS_COLOR_INDEX_FLAG)
#define COLOR_WINDOWTEXT    ( 8 | SYS_COLOR_INDEX_FLAG)
#define COLOR_CAPTIONTEXT   ( 9 | SYS_COLOR_INDEX_FLAG)
#define COLOR_ACTIVEBORDER  (10 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INACTIVEBORDER (11 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNFACE       (15 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNSHADOW     (16 | SYS_COLOR_INDEX_FLAG)
#define COLOR_BTNTEXT       (18 | SYS_COLOR_INDEX_FLAG)
#define COLOR_HIGHLIGHT     (13 | SYS_COLOR_INDEX_FLAG)
#define COLOR_HIGHLIGHTTEXT (14 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INFOBK        (24 | SYS_COLOR_INDEX_FLAG)
#define COLOR_INFOTEXT      (23 | SYS_COLOR_INDEX_FLAG)
#define COLOR_STATIC        (25 | SYS_COLOR_INDEX_FLAG)

#define MF_STRING       0x00000000
#define MF_ENABLED      0x00000000
#define MF_GRAYED       0x00000001
#define MF_DISABLED     0x00000002
#define MF_CHECKED      0x00000008
#define MF_SEPARATOR    0x00000800
#define MF_POPUP        0x00000010
#define MF_BYCOMMAND    0x00000000
#define MF_BYPOSITION   0x00000400

#define VK_LBUTTON  0x01
#define VK_RBUTTON  0x02
#define VK_BACK     0x08
#define VK_TAB      0x09
#define VK_RETURN   0x0D
#define VK_SHIFT    0x10
#define VK_CONTROL  0x11
#define VK_MENU     0x12
#define VK_ESCAPE   0x1B
#define VK_SPACE    0x20
#define VK_LEFT     0x25
#define VK_UP       0x26
#define VK_RIGHT    0x27
#define VK_DOWN     0x28
#define VK_DELETE   0x2E
#define VK_F1       0x70

typedef struct akari_NMHDR {
    HWND hwndFrom;
    UINT_PTR idFrom;
    UINT code;
} NMHDR, *LPNMHDR;

typedef struct akari_MSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG, *PMSG, *LPMSG;

typedef struct akari_WNDCLASSW {
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCWSTR lpszMenuName;
    LPCWSTR lpszClassName;
} WNDCLASSW, *PWNDCLASSW, *LPWNDCLASSW;

typedef struct akari_PAINTSTRUCT {
    HDC hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
} PAINTSTRUCT, *PPAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct akari_CREATESTRUCTW {
    LPVOID lpCreateParams;
    HINSTANCE hInstance;
    HMENU hMenu;
    HWND hwndParent;
    int cy; int cx;
    int y; int x;
    LONG style;
    LPCWSTR lpszName;
    LPCWSTR lpszClass;
    DWORD dwExStyle;
} CREATESTRUCTW, *LPCREATESTRUCTW;

WINUSERAPI HWND WINAPI CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName,
    DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
    HINSTANCE hInstance, LPVOID lpParam);
WINUSERAPI BOOL WINAPI DestroyWindow(HWND hWnd);
WINUSERAPI BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow);
WINUSERAPI BOOL WINAPI UpdateWindow(HWND hWnd);
WINUSERAPI BOOL WINAPI InvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase);
WINUSERAPI BOOL WINAPI RedrawWindow(HWND hWnd, const RECT *lprcUpdate, HRGN hrgnUpdate,
    UINT flags);
WINUSERAPI HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
WINUSERAPI BOOL WINAPI EndPaint(HWND hWnd, const PAINTSTRUCT *lpPaint);
WINUSERAPI BOOL WINAPI GetClientRect(HWND hWnd, LPRECT lpRect);
WINUSERAPI BOOL WINAPI GetWindowRect(HWND hWnd, LPRECT lpRect);
WINUSERAPI BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx,
    int cy, UINT uFlags);
WINUSERAPI BOOL WINAPI MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight,
    BOOL bRepaint);
WINUSERAPI LONG WINAPI GetWindowLongW(HWND hWnd, int nIndex);
WINUSERAPI LONG WINAPI SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);
WINUSERAPI BOOL WINAPI SetWindowTextW(HWND hWnd, LPCWSTR lpString);
WINUSERAPI int WINAPI GetWindowTextW(HWND hWnd, LPWSTR lpString, int nMaxCount);
WINUSERAPI int WINAPI GetWindowTextLengthW(HWND hWnd);
WINUSERAPI BOOL WINAPI EnableWindow(HWND hWnd, BOOL bEnable);
WINUSERAPI BOOL WINAPI IsWindowEnabled(HWND hWnd);
WINUSERAPI BOOL WINAPI IsWindowVisible(HWND hWnd);
WINUSERAPI BOOL WINAPI IsWindow(HWND hWnd);
WINUSERAPI HWND WINAPI GetFocus(VOID);
WINUSERAPI HWND WINAPI SetFocus(HWND hWnd);
WINUSERAPI HWND WINAPI GetParent(HWND hWnd);
WINUSERAPI HWND WINAPI SetParent(HWND hWndChild, HWND hWndNewParent);
WINUSERAPI HWND WINAPI GetDlgItem(HWND hDlg, int nIDDlgItem);
WINUSERAPI BOOL WINAPI SetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPCWSTR lpString);
WINUSERAPI UINT WINAPI GetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPWSTR lpString, int cchMax);
WINUSERAPI BOOL WINAPI SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned);
WINUSERAPI UINT WINAPI GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL *lpTranslated, BOOL bSigned);
/* Windows CE has no CheckDlgButton or IsDlgButtonChecked; use CheckRadioButton
 * together with SendMessage on the button control. */
WINUSERAPI BOOL WINAPI CheckRadioButton(HWND hDlg, int nIDFirstButton,
    int nIDLastButton, int nIDCheckButton);
WINUSERAPI LRESULT WINAPI SendMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
/* The timeout variant has a single, non-suffixed name on Windows CE. */
WINUSERAPI LRESULT WINAPI SendMessageTimeout(HWND hWnd, UINT Msg, WPARAM wParam,
    LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult);
#define SendMessageTimeoutW SendMessageTimeout
WINUSERAPI BOOL WINAPI PostMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WINUSERAPI void WINAPI PostQuitMessage(int nExitCode);
WINUSERAPI BOOL WINAPI GetMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
    UINT wMsgFilterMax);
WINUSERAPI BOOL WINAPI PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
    UINT wMsgFilterMax, UINT wRemoveMsg);
WINUSERAPI BOOL WINAPI TranslateMessage(const MSG *lpMsg);
WINUSERAPI LRESULT WINAPI DispatchMessageW(const MSG *lpMsg);
WINUSERAPI int WINAPI GetSystemMetrics(int nIndex);
WINUSERAPI UINT WINAPI SetTimer(HWND hWnd, UINT nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc);
WINUSERAPI BOOL WINAPI KillTimer(HWND hWnd, UINT uIDEvent);
WINUSERAPI ATOM WINAPI RegisterClassW(const WNDCLASSW *lpWndClass);
WINUSERAPI BOOL WINAPI UnregisterClassW(LPCWSTR lpClassName, HINSTANCE hInstance);
WINUSERAPI BOOL WINAPI GetClassInfoW(HINSTANCE hInstance, LPCWSTR lpClassName,
    LPWNDCLASSW lpWndClass);

WINUSERAPI HWND WINAPI SetCapture(HWND hWnd);
WINUSERAPI BOOL WINAPI ReleaseCapture(VOID);
WINUSERAPI HWND WINAPI GetCapture(VOID);
WINUSERAPI int WINAPI MessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
WINUSERAPI BOOL WINAPI MessageBeep(UINT uType);
WINUSERAPI HWND WINAPI FindWindowW(LPCWSTR lpClassName, LPCWSTR lpWindowName);
WINUSERAPI HWND WINAPI WindowFromPoint(POINT pt);
WINUSERAPI BOOL WINAPI ClientToScreen(HWND hWnd, LPPOINT lpPoint);
WINUSERAPI BOOL WINAPI ScreenToClient(HWND hWnd, LPPOINT lpPoint);
WINUSERAPI int WINAPI MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints);
WINUSERAPI BOOL WINAPI SetForegroundWindow(HWND hWnd);
WINUSERAPI HWND WINAPI GetForegroundWindow(VOID);
WINUSERAPI COLORREF WINAPI GetSysColor(int nIndex);
WINUSERAPI LRESULT WINAPI DefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WINUSERAPI LRESULT WINAPI CallWindowProcW(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg,
    WPARAM wParam, LPARAM lParam);
WINUSERAPI DWORD WINAPI GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId);
WINUSERAPI BOOL WINAPI SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);
WINUSERAPI BOOL WINAPI SetRectEmpty(LPRECT lprc);
WINUSERAPI int WINAPI OffsetRect(LPRECT lprc, int dx, int dy);
WINUSERAPI BOOL WINAPI PtInRect(const RECT *lprc, POINT pt);
WINUSERAPI BOOL WINAPI IntersectRect(LPRECT lprcDst, const RECT *lprcSrc1,
    const RECT *lprcSrc2);
WINUSERAPI BOOL WINAPI UnionRect(LPRECT lprcDst, const RECT *lprcSrc1,
    const RECT *lprcSrc2);
WINUSERAPI BOOL WINAPI SubtractRect(LPRECT lprcDst, const RECT *lprcSrc1,
    const RECT *lprcSrc2);
WINUSERAPI BOOL WINAPI IsRectEmpty(const RECT *lprc);
WINUSERAPI BOOL WINAPI InflateRect(LPRECT lprc, int dx, int dy);
WINUSERAPI BOOL WINAPI EqualRect(const RECT *lprc1, const RECT *lprc2);
WINUSERAPI BOOL WINAPI CopyRect(LPRECT lprcDst, const RECT *lprcSrc);
WINUSERAPI BOOL WINAPI DrawIconEx(HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth,
    int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
WINUSERAPI int WINAPI SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw);
WINUSERAPI SHORT WINAPI GetAsyncKeyState(int vKey);
WINUSERAPI SHORT WINAPI GetKeyState(int nVirtKey);
WINUSERAPI UINT WINAPI MapVirtualKeyW(UINT uCode, UINT uMapType);
WINUSERAPI UINT WINAPI GetDoubleClickTime(VOID);
WINUSERAPI BOOL WINAPI SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam,
    UINT fWinIni);
WINUSERAPI BOOL WINAPI GetCursorPos(LPPOINT lpPoint);
WINUSERAPI BOOL WINAPI SetCursorPos(int X, int Y);
WINUSERAPI HCURSOR WINAPI SetCursor(HCURSOR hCursor);
/* Windows CE only exposes the indirect dialog forms: the template has to be a
 * resource already loaded into memory. */
WINUSERAPI INT_PTR WINAPI DialogBoxIndirectParamW(HINSTANCE hInstance,
    const void *lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
WINUSERAPI HWND WINAPI CreateDialogIndirectParamW(HINSTANCE hInstance,
    const void *lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
WINUSERAPI BOOL WINAPI EndDialog(HWND hDlg, INT_PTR nResult);

WINUSERAPI HICON WINAPI LoadIconW(HINSTANCE hInstance, LPCWSTR lpIconName);
WINUSERAPI HCURSOR WINAPI LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);
WINUSERAPI HBITMAP WINAPI LoadBitmapW(HINSTANCE hInstance, LPCWSTR lpBitmapName);
WINBASEAPI HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo);

/* Resource data is not moveable on Windows CE, so locking is a no-op. */
#define LockResource(hResData) ((LPVOID)(hResData))

#define PM_NOREMOVE 0x0000
#define PM_REMOVE   0x0001
#define PM_NOYIELD  0x0002

#define SWP_NOSIZE     0x0001
#define SWP_NOMOVE     0x0002
#define SWP_NOZORDER   0x0004
#define SWP_NOREDRAW   0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080


/* Moved here from GetDC, GetWindowDC, MsgWaitForMultipleObjectsEx, ReleaseDC: the CE SDK declares these entry points in this header. */
WINBASEAPI DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount,
    const HANDLE *pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags);
WINBASEAPI HDC WINAPI GetDC(HWND hWnd);
WINBASEAPI HDC WINAPI GetWindowDC(HWND hWnd);
WINBASEAPI int WINAPI ReleaseDC(HWND hWnd, HDC hDC);

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WINUSER_H */
