/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_TCHAR_H
#define AKARI_TCHAR_H
#include "windef.h"
/* Windows CE is Unicode-only. Generic text names are the wide names. */
#define TEXT(lit) L##lit
#define _T(lit) L##lit
#define __TEXT(lit) L##lit
#define _TEOF WEOF
#endif
