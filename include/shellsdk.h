/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SHELLSDK_H
#define WCE_SHELLSDK_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSHMENUBARINFO { DWORD cbSize; HWND hwndParent; DWORD dwFlags; UINT nToolBarId; HINSTANCE hInstRes; int nBmpId; int cBmpImages; HWND hwndMB; COLORREF clrBk; } SHMENUBARINFO, *PSHMENUBARINFO, *LPSHMENUBARINFO;
typedef struct tagSHINITDLGINFO { DWORD dwMask; HWND hDlg; DWORD dwFlags; } SHINITDLGINFO, *PSHINITDLGINFO, *LPSHINITDLGINFO;
typedef struct tagSHRGINFO { DWORD cbSize; HWND hwndClient; POINT ptDown; DWORD dwFlags; } SHRGINFO, *PSHRGINFO, *LPSHRGINFO;
typedef struct tagNMRGINFO { NMHDR hdr; POINT ptAction; DWORD dwItemSpec; } NMRGINFO, *PNMRGINFO, *LPNMRGINFO;

WCE_IMPORT BOOL WINAPI SHCloseApps(DWORD dwMemSought) WCE_LINK(SHCloseApps);
WCE_IMPORT HWND WINAPI SHFindMenuBar(HWND hwnd) WCE_LINK(SHFindMenuBar);
WCE_IMPORT BYTE WINAPI SHGetAppKeyAssoc(LPCTSTR ptszApp) WCE_LINK(SHGetAppKeyAssoc);
WCE_IMPORT void WINAPI SHNavigateBack() WCE_LINK(SHNavigateBack);
WCE_IMPORT void WINAPI SHSetBack(int, HWND) WCE_LINK(SHSetBack);
WCE_IMPORT BOOL WINAPI SHSetAppKeyWndAssoc(BYTE bVk, HWND hwnd) WCE_LINK(SHSetAppKeyWndAssoc);
WCE_IMPORT BOOL WINAPI SHSetNavBarText(HWND hwnd, LPCTSTR pszText) WCE_LINK(SHSetNavBarText);
WCE_IMPORT BOOL WINAPI SHChangeNotifyRegister(HWND hwnd, SHCHANGENOTIFYENTRY *pshcne) WCE_LINK(SHChangeNotifyRegister);
WCE_IMPORT BOOL WINAPI SHChangeNotifyDeregister(HWND hwnd) WCE_LINK(SHChangeNotifyDeregister);
WCE_IMPORT void WINAPI SHChangeNotifyFree(FILECHANGENOTIFY *pfcn) WCE_LINK(SHChangeNotifyFree);
WCE_IMPORT BOOL WINAPI SHCreateMenuBar(SHMENUBARINFO *pmbi) WCE_LINK(SHCreateMenuBar);
WCE_IMPORT HRESULT WINAPI SHCreateNewItem(HWND hwndOwner, REFCLSID clsid) WCE_LINK(SHCreateNewItem);
WCE_IMPORT BOOL WINAPI SHDoneButton(HWND hwndRequester, DWORD dwState) WCE_LINK(SHDoneButton);
WCE_IMPORT BOOL WINAPI SHFreeContextMenuExtensions(HANDLE hCMExtensions) WCE_LINK(SHFreeContextMenuExtensions);
WCE_IMPORT BOOL WINAPI SHFullScreen(HWND hwndRequester, DWORD dwState) WCE_LINK(SHFullScreen);
WCE_IMPORT BOOL WINAPI SHGetAutoRunPath(LPTSTR pAutoRunPath) WCE_LINK(SHGetAutoRunPath);
WCE_IMPORT BOOL WINAPI SHInitDialog(PSHINITDLGINFO pshidi) WCE_LINK(SHInitDialog);
WCE_IMPORT BOOL WINAPI SHInitExtraControls(void) WCE_LINK(SHInitExtraControls);
WCE_IMPORT void WINAPI SHInputDialog(HWND hwnd, UINT uMsg, WPARAM wParam) WCE_LINK(SHInputDialog);
WCE_IMPORT BOOL WINAPI SHInvokeContextMenuCommand(HWND hwndOwner, UINT idCmd, HANDLE hCMExtensions) WCE_LINK(SHInvokeContextMenuCommand);
WCE_IMPORT LRESULT WINAPI SHNotificationRemove(const CLSID *pclsid, DWORD dwID) WCE_LINK(SHNotificationRemove);
WCE_IMPORT DWORD WINAPI SHRecognizeGesture(SHRGINFO *shrg) WCE_LINK(SHRecognizeGesture);
WCE_IMPORT BOOL WINAPI SHSipInfo(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni) WCE_LINK(SHSipInfo);

#ifdef __cplusplus
}
#endif
#endif

