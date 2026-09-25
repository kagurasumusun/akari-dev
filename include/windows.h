/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_WINDOWS_H
#define AKARI_WINDOWS_H
#include "sdkddkver.h"
#include "excpt.h"
#include "windef.h"
#include "winnt.h"
#include "winbase.h"
#include "wingdi.h"
#include "winuser.h"
#include "winreg.h"
#include "winnls.h"
#include "winerror.h"
#include "tchar.h"
#endif
