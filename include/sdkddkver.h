/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_SDKDDKVER_H
#define AKARI_SDKDDKVER_H
#ifndef _WIN32_WCE
#define _WIN32_WCE 0x600
#endif
#ifndef WINVER
#define WINVER 0x0500
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef UNDER_CE
#define UNDER_CE 1
#endif
#ifndef WIN32_PLATFORM_PSPC
/* not a smartphone/pocket-pc flavor macro; left undefined */
#endif
#define AKARI_WINCE_SURFACE 0x600
#endif
