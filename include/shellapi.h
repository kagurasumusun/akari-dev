/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SHELLAPI_H
#define WCE_SHELLAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSHELLEXECUTEINFO { DWORD cbSize; ULONG fMask; HWND hwnd; LPCTSTR lpVerb; LPCTSTR lpFile; LPCTSTR lpParameters; LPCTSTR lpDirectory; int nShow; HINSTANCE hInstApp; LPVOID lpIDList; LPCTSTR lpClass; HKEY hkeyClass; DWORD dwHotKey; HANDLE hIcon; HANDLE hProcess; } SHELLEXECUTEINFO, *PSHELLEXECUTEINFO, *LPSHELLEXECUTEINFO;
typedef struct tagNOTIFYICONDATAA { DWORD cbSize; HWND hWnd; UINT uID; UINT uFlags; UINT uCallbackMessage; HICON hIcon; CHAR szTip[64]; } NOTIFYICONDATAA, *PNOTIFYICONDATAA, *LPNOTIFYICONDATAA;
typedef struct tagNOTIFYICONDATAW { DWORD cbSize; HWND hWnd; UINT uID; UINT uFlags; UINT uCallbackMessage; HICON hIcon; WCHAR szTip[64]; } NOTIFYICONDATAW, *PNOTIFYICONDATAW, *LPNOTIFYICONDATAW;

WCE_IMPORT HICON WINAPI ExtractIconExA(LPCSTR lpszFile, int nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIcons) WCE_LINK(ExtractIconExA);
WCE_IMPORT HICON WINAPI ExtractIconExW(LPCWSTR lpszFile, int nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIcons) WCE_LINK(ExtractIconExW);
WCE_IMPORT int WINAPI SHFileOperationA(LPSHFILEOPSTRUCTA lpFileOp) WCE_LINK(SHFileOperationA);
WCE_IMPORT int WINAPI SHFileOperationW(LPSHFILEOPSTRUCTW lpFileOp) WCE_LINK(SHFileOperationW);
WCE_IMPORT BOOL WINAPI ShellExecuteEx(LPSHELLEXECUTEINFO lpExecInfo) WCE_LINK(ShellExecuteEx);
WCE_IMPORT BOOL WINAPI Shell_NotifyIcon(DWORD dwMessage, PNOTIFYICONDATA lpData) WCE_LINK(Shell_NotifyIcon);
WCE_IMPORT BOOL WINAPI SHGetSpecialFolderPath(HWND hwndOwner, LPTSTR lpszPath, int nFolder, BOOL fCreate) WCE_LINK(SHGetSpecialFolderPath);
WCE_IMPORT void WINAPI SHAddToRecentDocs(UINT uFlags, LPCVOID pv) WCE_LINK(SHAddToRecentDocs);
WCE_IMPORT DWORD WINAPI SHCreateShortcut(LPTSTR szShortcut, LPTSTR szTarget) WCE_LINK(SHCreateShortcut);
WCE_IMPORT DWORD WINAPI SHCreateShortcutEx(LPTSTR lpszDir, LPTSTR lpszTarget, LPTSTR szShortcut, LPDWORD lpcbShortcut) WCE_LINK(SHCreateShortcutEx);
WCE_IMPORT BOOL WINAPI SHGetShortcutTarget(LPCTSTR szShortcut, LPTSTR szTarget, int cb) WCE_LINK(SHGetShortcutTarget);
WCE_IMPORT int WINAPI SHShowOutOfMemory(HWND hwndOwner, UINT grfFlags) WCE_LINK(SHShowOutOfMemory);
WCE_IMPORT HBITMAP WINAPI SHLoadDIBitmap(LPCTSTR szFileName) WCE_LINK(SHLoadDIBitmap);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI SHLoadIndirectString(LPCWSTR pszSource, LPWSTR pszOutBuf, UINT cchOutBuf, void ** ppvReserved) WCE_LINK(SHLoadIndirectString);
#endif

#define ExtractIconEx ExtractIconExW
#define SHFileOperation SHFileOperationW
#ifdef __cplusplus
}
#endif
#endif

