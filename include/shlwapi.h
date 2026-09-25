/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SHLWAPI_H
#define WCE_SHLWAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDLLVERSIONINFO { DWORD cbSize; DWORD dwMajorVersion; DWORD dwMinorVersion; DWORD dwBuildNumber; DWORD dwPlatformID; } DLLVERSIONINFO, *PDLLVERSIONINFO, *LPDLLVERSIONINFO;
typedef struct tagDLLVERSIONINFO2 { DLLVERSIONINFO info1; DWORD dwFlags; ULONGLONG ullVersion; } DLLVERSIONINFO2, *PDLLVERSIONINFO2, *LPDLLVERSIONINFO2;

WCE_IMPORT HRESULT WINAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine) WCE_LINK(DllInstall);

#ifdef __cplusplus
}
#endif
#endif

