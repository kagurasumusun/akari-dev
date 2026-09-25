/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ADVPUB_H
#define WCE_ADVPUB_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSTRENTRY { LPSTR pszName; LPSTR pszValue; } STRENTRY, *PSTRENTRY, *LPSTRENTRY;
typedef struct tagSTRTABLE { DWORD cEntries; LPSTRENTRY pse; } STRTABLE, *PSTRTABLE, *LPSTRTABLE;

WCE_IMPORT HRESULT WINAPI RunSetupCommand(HWND hWnd, LPCSTR szCmdName, LPCSTR szInfSection, LPCSTR szDir, LPCSTR lpszTitle, HANDLE *phEXE, DWORD dwFlags, LPVOID pvReserved) WCE_LINK(RunSetupCommand);
WCE_IMPORT DWORD WINAPI NeedRebootInit(VOID) WCE_LINK(NeedRebootInit);
WCE_IMPORT BOOL WINAPI NeedReboot(DWORD dwRebootCheck) WCE_LINK(NeedReboot);
WCE_IMPORT HRESULT WINAPI RebootCheckOnInstall(HWND hwnd, PCSTR pszINF, PCSTR pszSec, DWORD dwReserved) WCE_LINK(RebootCheckOnInstall);
WCE_IMPORT HRESULT WINAPI TranslateInfString(PCSTR pszInfFilename, PCSTR pszInstallSection, PCSTR pszTranslateSection, PCSTR pszTranslateKey, PSTR pszBuffer, DWORD dwBufferSize, PDWORD pdwRequiredSize, PVOID pvReserved) WCE_LINK(TranslateInfString);
WCE_IMPORT HRESULT WINAPI RegInstall(HMODULE hm, LPCSTR pszSection, LPCSTRTABLE pstTable) WCE_LINK(RegInstall);
WCE_IMPORT HRESULT WINAPI LaunchINFSectionEx(HWND hwnd, HINSTANCE hInstance, PSTR pszParms, INT nShow) WCE_LINK(LaunchINFSectionEx);
WCE_IMPORT HRESULT WINAPI ExecuteCab(HWND hwnd, PCABINFO pCab, LPVOID pReserved) WCE_LINK(ExecuteCab);
WCE_IMPORT HRESULT WINAPI AdvInstallFile(HWND hwnd, LPCSTR lpszSourceDir, LPCSTR lpszSourceFile, LPCSTR lpszDestDir, LPCSTR lpszDestFile, DWORD dwFlags, DWORD dwReserved) WCE_LINK(AdvInstallFile);
WCE_IMPORT HRESULT WINAPI RegSaveRestore(HWND hWnd, PCSTR pszTitleString, HKEY hkBckupKey, PCSTR pcszRootKey, PCSTR pcszSubKey, PCSTR pcszValueName, DWORD dwFlags) WCE_LINK(RegSaveRestore);
WCE_IMPORT HRESULT WINAPI RegSaveRestoreOnINF(HWND hWnd, PCSTR pszTitle, PCSTR pszINF, PCSTR pszSection, HKEY hHKLMBackKey, HKEY hHKCUBackKey, DWORD dwFlags) WCE_LINK(RegSaveRestoreOnINF);
WCE_IMPORT HRESULT WINAPI RegRestoreAll(HWND hWnd, PSTR pszTitleString, HKEY hkBckupKey) WCE_LINK(RegRestoreAll);
WCE_IMPORT HRESULT WINAPI FileSaveRestore(HWND hDlg, LPSTR lpFileList, LPSTR lpDir, LPSTR lpBaseName, DWORD dwFlags) WCE_LINK(FileSaveRestore);
WCE_IMPORT HRESULT WINAPI FileSaveRestoreOnINF(HWND hWnd, PCSTR pszTitle, PCSTR pszINF, PCSTR pszSection, PCSTR pszBackupDir, PCSTR pszBaseBackupFile, DWORD dwFlags) WCE_LINK(FileSaveRestoreOnINF);
WCE_IMPORT HRESULT WINAPI AddDelBackupEntry(LPCSTR lpcszFileList, LPCSTR lpcszBackupDir, LPCSTR lpcszBaseName, DWORD dwFlags) WCE_LINK(AddDelBackupEntry);
WCE_IMPORT HRESULT WINAPI FileSaveMarkNotExist(LPSTR lpFileList, LPSTR lpDir, LPSTR lpBaseName) WCE_LINK(FileSaveMarkNotExist);
WCE_IMPORT HRESULT WINAPI GetVersionFromFile(LPSTR lpszFilename, LPDWORD pdwMSVer, LPDWORD pdwLSVer, BOOL bVersion) WCE_LINK(GetVersionFromFile);
WCE_IMPORT HRESULT WINAPI GetVersionFromFileEx(LPSTR lpszFilename, LPDWORD pdwMSVer, LPDWORD pdwLSVer, BOOL bVersion) WCE_LINK(GetVersionFromFileEx);
WCE_IMPORT BOOL WINAPI IsNTAdmin(DWORD dwReserved, DWORD *lpdwReserved) WCE_LINK(IsNTAdmin);
WCE_IMPORT HRESULT WINAPI DelNode(LPCSTR pszFileOrDirName, DWORD dwFlags) WCE_LINK(DelNode);
WCE_IMPORT HRESULT WINAPI DelNodeRunDLL32(HWND hwnd, HINSTANCE hInstance, PSTR pszParms, INT nShow) WCE_LINK(DelNodeRunDLL32);
WCE_IMPORT HRESULT WINAPI ExtractFiles(LPCSTR pszCabName, LPCSTR pszExpandDir, DWORD dwFlags, LPCSTR pszFileList, LPVOID lpReserved, DWORD dwReserved) WCE_LINK(ExtractFiles);
WCE_IMPORT INT WINAPI LaunchINFSection(HWND, HINSTANCE, PSTR, INT) WCE_LINK(LaunchINFSection);
WCE_IMPORT HRESULT WINAPI UserInstStubWrapper(HWND hwnd, HINSTANCE hInstance, PSTR pszParms, INT nShow) WCE_LINK(UserInstStubWrapper);
WCE_IMPORT HRESULT WINAPI UserUnInstStubWrapper(HWND hwnd, HINSTANCE hInstance, PSTR pszParms, INT nShow) WCE_LINK(UserUnInstStubWrapper);
WCE_IMPORT HRESULT WINAPI SetPerUserSecValues(PPERUSERSECTION pPerUser) WCE_LINK(SetPerUserSecValues);

#ifdef __cplusplus
}
#endif
#endif

