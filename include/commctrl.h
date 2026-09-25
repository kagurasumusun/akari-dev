/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_COMMCTRL_H
#define AKARI_COMMCTRL_H
#include "windef.h"
#include "winuser.h"

#ifdef __cplusplus
extern "C" {
#endif
AKARI_IMPORT void WINAPI InitCommonControls(void) AKARI_NAME(InitCommonControls);
AKARI_IMPORT HWND WINAPI CommandBar_Create(HINSTANCE hInst, HWND hwndParent, int idCmdBar) AKARI_NAME(CommandBar_Create);
AKARI_IMPORT BOOL WINAPI CommandBar_Show(HWND hwndCB, BOOL fShow) AKARI_NAME(CommandBar_Show);
AKARI_IMPORT int WINAPI CommandBar_AddBitmap(HWND hwndCB, HINSTANCE hInst, int idBitmap, int iNumImages, int iImageWidth, int iImageHeight) AKARI_NAME(CommandBar_AddBitmap);
AKARI_IMPORT HWND WINAPI CommandBar_InsertComboBox(HWND hwndCB, HINSTANCE hInstance, int iWidth, UINT dwStyle, WORD idComboBox, WORD iButton) AKARI_NAME(CommandBar_InsertComboBox);
AKARI_IMPORT BOOL WINAPI CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst, WORD idMenu, WORD iButton) AKARI_NAME(CommandBar_InsertMenubar);
AKARI_IMPORT BOOL WINAPI CommandBar_InsertMenubarEx(HWND hwndCB, HINSTANCE hinst, LPTSTR pszMenu, WORD iButton) AKARI_NAME(CommandBar_InsertMenubarEx);
AKARI_IMPORT BOOL WINAPI CommandBar_DrawMenuBar(HWND hwndCB, WORD iButton) AKARI_NAME(CommandBar_DrawMenuBar);
AKARI_IMPORT HMENU WINAPI CommandBar_GetMenu(HWND hwndCB, WORD iButton) AKARI_NAME(CommandBar_GetMenu);
AKARI_IMPORT BOOL WINAPI CommandBar_AddAdornments(HWND hwndCB, DWORD dwFlags, DWORD dwReserved) AKARI_NAME(CommandBar_AddAdornments);
AKARI_IMPORT void WINAPI CommandBar_AlignAdornments(HWND hwndCB) AKARI_NAME(CommandBar_AlignAdornments);
AKARI_IMPORT int WINAPI CommandBar_Height(HWND hwndCB) AKARI_NAME(CommandBar_Height);
AKARI_IMPORT BOOL WINAPI IsCommandBarMessage(HWND hwndCB, LPMSG lpMsg) AKARI_NAME(IsCommandBarMessage);
AKARI_IMPORT HWND WINAPI CommandBands_GetCommandBar(HWND hwndCmdBands, UINT uBand) AKARI_NAME(CommandBands_GetCommandBar);
AKARI_IMPORT BOOL WINAPI CommandBands_Show(HWND hwndCmdBands, BOOL fShow) AKARI_NAME(CommandBands_Show);
AKARI_IMPORT void WINAPI DrawStatusTextW(HDC hDC, LPRECT lprc, LPCWSTR pszText, UINT uFlags) AKARI_NAME(DrawStatusTextW);
AKARI_IMPORT HWND WINAPI CreateStatusWindowW(LONG style, LPCWSTR lpszText, HWND hwndParent, UINT wID) AKARI_NAME(CreateStatusWindowW);
AKARI_IMPORT HWND WINAPI CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy, HWND hParent, int nID, HINSTANCE hInst, HWND hBuddy, int nUpper, int nLower, int nPos) AKARI_NAME(CreateUpDownControl);

#ifdef __cplusplus
}
#endif
#endif
