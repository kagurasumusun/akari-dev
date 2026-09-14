/*
 * Tchar.h -- generic-text (TCHAR) mappings for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Added 2026-09-14 (audit follow-up): confirmed absent from the tree.
 * This is one of the small set of headers that portable CE application
 * source (including most cegcc-targeting code and any code shared
 * with desktop Win32) expects to be able to include unconditionally.
 *
 * Windows CE has no ANSI (multi-byte) system call layer: every OS
 * entry point is Unicode-only (see Windows.h's umbrella comment).
 * Desktop tchar.h supports three modes (SBCS / MBCS / Unicode)
 * selected by _UNICODE and _MBCS; on CE only the Unicode mode is
 * meaningful for anything that calls into the OS, so:
 *
 *   - If the consumer defines _UNICODE (the normal, recommended case
 *     for CE app code), the _T()/_TEXT() family map to L"..." and
 *     TCHAR = wchar_t, exactly as on desktop.
 *   - If the consumer does NOT define _UNICODE, this header still
 *     lets narrow-string-shaped source compile (TCHAR = char, _T(x)
 *     = x) for portability with shared desktop sources, but the
 *     resulting narrow strings are only usable with the small set of
 *     narrow helper routines the CRT layer provides (see
 *     wince-crt's crt.h narrow/wide note) -- they cannot be passed
 *     directly to CE OS entry points, which take wide strings only.
 *     _MBCS is not a supported mode on this target and is rejected.
 */

#ifndef AKARI_TCHAR_H
#define AKARI_TCHAR_H

#include <wchar.h>
#include <string.h>

#if defined(_MBCS)
#error "Tchar.h: _MBCS is not a supported mode on Windows CE (Unicode-only OS layer)"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_UNICODE)

typedef wchar_t TCHAR, *PTCHAR;
typedef unsigned short _TUCHAR, *_PTUCHAR;
typedef const wchar_t *PCTSTR, *LPCTSTR;
typedef wchar_t *PTSTR, *LPTSTR;

#define _T(x)       L##x
#define _TEXT(x)    L##x

#define _tcslen     wcslen
#define _tcscpy     wcscpy
#define _tcsncpy    wcsncpy
#define _tcscat     wcscat
#define _tcsncat    wcsncat
#define _tcscmp     wcscmp
#define _tcsncmp    wcsncmp
#define _tcsicmp    _wcsicmp
#define _tcschr     wcschr
#define _tcsrchr    wcsrchr
#define _tcsstr     wcsstr
#define _tcstok     wcstok
#define _tprintf    wprintf
#define _sntprintf  _snwprintf
#define _tcstol     wcstol
#define _tcstoul    wcstoul
#define _ftprintf   fwprintf
#define _tfopen     _wfopen
#define _stprintf   swprintf

#else /* narrow, source-portability-only mode; see file header note */

typedef char TCHAR, *PTCHAR;
typedef unsigned char _TUCHAR, *_PTUCHAR;
typedef const char *PCTSTR, *LPCTSTR;
typedef char *PTSTR, *LPTSTR;

#define _T(x)       x
#define _TEXT(x)    x

#define _tcslen     strlen
#define _tcscpy     strcpy
#define _tcsncpy    strncpy
#define _tcscat     strcat
#define _tcsncat    strncat
#define _tcscmp     strcmp
#define _tcsncmp    strncmp
#define _tcsicmp    _stricmp
#define _tcschr     strchr
#define _tcsrchr    strrchr
#define _tcsstr     strstr
#define _tcstok     strtok
#define _tprintf    printf
#define _sntprintf  _snprintf
#define _tcstol     strtol
#define _tcstoul    strtoul
#define _ftprintf   fprintf
#define _tfopen     fopen
#define _stprintf   sprintf

#endif /* _UNICODE */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_TCHAR_H */
