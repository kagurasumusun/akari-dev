/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINVER_H
#define WCE_WINVER_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagVS_FIXEDFILEINFO { DWORD dwSignature; DWORD dwStrucVersion; DWORD dwFileVersionMS; DWORD dwFileVersionLS; DWORD dwProductVersionMS; DWORD dwProductVersionLS; DWORD dwFileFlagsMask; DWORD dwFileFlags; DWORD dwFileOS; DWORD dwFileType; DWORD dwFileSubtype; DWORD dwFileDateMS; DWORD dwFileDateLS; } VS_FIXEDFILEINFO, *PVS_FIXEDFILEINFO, *LPVS_FIXEDFILEINFO;

WCE_IMPORT DWORD WINAPI VerFindFileA(DWORD uFlags, LPSTR szFileName, LPSTR szWinDir, LPSTR szAppDir, LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen) WCE_LINK(VerFindFileA);
WCE_IMPORT DWORD WINAPI VerFindFileW(DWORD uFlags, LPWSTR szFileName, LPWSTR szWinDir, LPWSTR szAppDir, LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir, PUINT lpuDestDirLen) WCE_LINK(VerFindFileW);
WCE_IMPORT DWORD WINAPI VerInstallFileA(DWORD uFlags, LPSTR szSrcFileName, LPSTR szDestFileName, LPSTR szSrcDir, LPSTR szDestDir, LPSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen) WCE_LINK(VerInstallFileA);
WCE_IMPORT DWORD WINAPI VerInstallFileW(DWORD uFlags, LPWSTR szSrcFileName, LPWSTR szDestFileName, LPWSTR szSrcDir, LPWSTR szDestDir, LPWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen) WCE_LINK(VerInstallFileW);
WCE_IMPORT DWORD WINAPI GetFileVersionInfoSizeA(LPSTR lptstrFilename, LPDWORD lpdwHandle) WCE_LINK(GetFileVersionInfoSizeA);
WCE_IMPORT DWORD WINAPI GetFileVersionInfoSizeW(LPWSTR lptstrFilename, LPDWORD lpdwHandle) WCE_LINK(GetFileVersionInfoSizeW);
WCE_IMPORT BOOL WINAPI GetFileVersionInfoA(LPSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) WCE_LINK(GetFileVersionInfoA);
WCE_IMPORT BOOL WINAPI GetFileVersionInfoW(LPWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) WCE_LINK(GetFileVersionInfoW);
WCE_IMPORT DWORD WINAPI VerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD nSize) WCE_LINK(VerLanguageNameA);
WCE_IMPORT DWORD WINAPI VerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD nSize) WCE_LINK(VerLanguageNameW);
WCE_IMPORT BOOL WINAPI VerQueryValueA(const LPVOID pBlock, LPSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen) WCE_LINK(VerQueryValueA);
WCE_IMPORT BOOL WINAPI VerQueryValueW(const LPVOID pBlock, LPWSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen) WCE_LINK(VerQueryValueW);

#define VerFindFile VerFindFileW
#define VerInstallFile VerInstallFileW
#define GetFileVersionInfoSize GetFileVersionInfoSizeW
#define GetFileVersionInfo GetFileVersionInfoW
#define VerLanguageName VerLanguageNameW
#define VerQueryValue VerQueryValueW
#ifdef __cplusplus
}
#endif
#endif

