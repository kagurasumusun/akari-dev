/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_PSAPI_H
#define WCE_PSAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMODULEINFO { LPVOID lpBaseOfDll; DWORD SizeOfImage; LPVOID EntryPoint; } MODULEINFO, *PMODULEINFO, *LPMODULEINFO;

WCE_IMPORT BOOL WINAPI GetModuleInformation(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb) WCE_LINK(GetModuleInformation);
WCE_IMPORT BOOL WINAPI CeSetProcessVersion(HANDLE hProcess, DWORD dwVersion) WCE_LINK(CeSetProcessVersion);

#ifdef __cplusplus
}
#endif
#endif

