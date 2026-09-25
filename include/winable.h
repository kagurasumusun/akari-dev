/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINABLE_H
#define WCE_WINABLE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagGUITHREADINFO { DWORD cbSize; DWORD flags; HWND hwndActive; HWND hwndFocus; HWND hwndCapture; HWND hwndMenuOwner; HWND hwndMoveSize; HWND hwndCaret; RECT rcCaret; } GUITHREADINFO, *PGUITHREADINFO, *LPGUITHREADINFO;
typedef struct tagMOUSEINPUT { LONG dx; LONG dy; DWORD mouseData; DWORD dwFlags; DWORD time; DWORD dwExtraInfo; } MOUSEINPUT, *PMOUSEINPUT, *LPMOUSEINPUT;
typedef struct tagKEYBDINPUT { WORD wVk; WORD wScan; DWORD dwFlags; DWORD time; DWORD dwExtraInfo; } KEYBDINPUT, *PKEYBDINPUT, *LPKEYBDINPUT;
typedef struct tagHARDWAREINPUT { DWORD uMsg; WORD wParamL; WORD wParamH; DWORD dwExtraInfo; } HARDWAREINPUT, *PHARDWAREINPUT, *LPHARDWAREINPUT;

WCE_IMPORT BOOL WINAPI GetGUIThreadInfo(DWORD idThread, LPGUITHREADINFO lpgui) WCE_LINK(GetGUIThreadInfo);
WCE_IMPORT UINT WINAPI GetWindowModuleFileNameW(HWND hwnd, LPWSTR lpFileName, UINT cchFileName) WCE_LINK(GetWindowModuleFileNameW);
WCE_IMPORT UINT WINAPI GetWindowModuleFileNameA(HWND hwnd, LPSTR lpFileName, UINT cchFileName) WCE_LINK(GetWindowModuleFileNameA);
WCE_IMPORT BOOL WINAPI BlockInput(BOOL fBlockIt) WCE_LINK(BlockInput);
WCE_IMPORT UINT WINAPI SendInput(UINT cInputs, LPINPUT pInputs, int cbSize) WCE_LINK(SendInput);
WCE_IMPORT void WINAPI NotifyWinEvent(DWORD event, HWND hwnd, LONG idObject, LONG idChild) WCE_LINK(NotifyWinEvent);

#define GetWindowModuleFileName GetWindowModuleFileNameW
#ifdef __cplusplus
}
#endif
#endif

