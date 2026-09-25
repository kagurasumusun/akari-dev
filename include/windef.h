/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_WINDEF_H
#define AKARI_WINDEF_H
#include "sdkddkver.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cdecl
#define __cdecl
#endif
#ifndef __stdcall
#define __stdcall
#endif
/* Windows CE public headers define stdcall as cdecl outside emulation,
 * so export names carry no @n decoration on x86 or ARM. */
#ifndef _WIN32_WCE_EMULATION
#undef __stdcall
#define __stdcall __cdecl
#undef _stdcall
#define _stdcall __cdecl
#endif

#ifndef WINAPI
#define WINAPI __stdcall
#endif
#ifndef WINAPIV
#define WINAPIV __cdecl
#endif
#ifndef APIENTRY
#define APIENTRY WINAPI
#endif
#ifndef CALLBACK
#define CALLBACK WINAPI
#endif
#ifndef APIPRIVATE
#define APIPRIVATE WINAPI
#endif

#ifndef CONST
#define CONST const
#endif
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
#endif

/* x86 CE import names are undecorated. Pin them so a stock cdecl compiler
 * does not look up a leading-underscore or @n spelling. ARM names already
 * match the import library, so the attributes are empty there. */
#if defined(_M_IX86) || defined(__i386__)
#define AKARI_IMPORT __declspec(dllimport)
#define AKARI_NAME(n) __asm__(#n)
#else
#define AKARI_IMPORT
#define AKARI_NAME(n)
#endif

#ifndef _WIN32
#define _WIN32
#endif
#ifndef WIN32
#define WIN32
#endif
#ifndef UNICODE
#define UNICODE 1
#endif
#ifndef _UNICODE
#define _UNICODE 1
#endif

typedef void VOID;
typedef char CHAR;
#if defined(__WCHAR_MAX__) && (__WCHAR_MAX__ <= 0xFFFF)
typedef wchar_t WCHAR;
#else
typedef uint16_t WCHAR;
#endif
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint32_t ULONG;
typedef int INT;
typedef unsigned int UINT;
typedef int16_t SHORT;
typedef uint16_t USHORT;
typedef float FLOAT;
typedef double DOUBLE;
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int BOOL;
typedef uint32_t UINT_PTR;
typedef int32_t LONG_PTR;
typedef uint32_t ULONG_PTR;
typedef int32_t INT_PTR;
typedef uint32_t DWORD_PTR;
typedef ULONG_PTR SIZE_T;
typedef LONG_PTR SSIZE_T;
typedef LONG_PTR LPARAM;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LRESULT;
typedef LONG HRESULT;
typedef DWORD LCID;
typedef WORD LANGID;
typedef BYTE BOOLEAN;
typedef DWORD COLORREF;
typedef DWORD *LPCOLORREF;
typedef WORD ATOM;
typedef int HFILE;

typedef void *HANDLE;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef void *PVOID;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HHOOK);
DECLARE_HANDLE(HEVENT);
DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;
DECLARE_HANDLE(HACCEL);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HPEN);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HKL);
DECLARE_HANDLE(HMONITOR);
typedef void *HGDIOBJ;
typedef HICON HCURSOR;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE HDWP;

typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR;
typedef WCHAR TCHAR;
typedef WCHAR *LPTSTR;
typedef const WCHAR *LPCTSTR;
typedef BYTE *PBYTE;
typedef BYTE *LPBYTE;
typedef WORD *PWORD;
typedef WORD *LPWORD;
typedef DWORD *PDWORD;
typedef DWORD *LPDWORD;
typedef UINT *PUINT;
typedef BOOL *LPBOOL;
typedef LONG *PLONG;
typedef LONG *LPLONG;
typedef HANDLE *LPHANDLE;
typedef INT *PINT;
typedef INT *LPINT;

#ifndef NULL
#define NULL ((void *)0)
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b) ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l) ((WORD)(l))
#define HIWORD(l) ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w) ((BYTE)(w))
#define HIBYTE(w) ((BYTE)(((WORD)(w) >> 8) & 0xFF))

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;
typedef const RECT *LPCRECT;

typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef struct tagSIZE {
    LONG cx;
    LONG cy;
} SIZE, *PSIZE, *LPSIZE;
typedef SIZE SIZEL;

typedef struct tagPOINTS {
    SHORT x;
    SHORT y;
} POINTS, *PPOINTS, *LPPOINTS;

#define HFILE_ERROR ((HFILE)-1)

typedef INT_PTR (FAR WINAPI *FARPROC)(void);
typedef INT_PTR (NEAR WINAPI *NEARPROC)(void);
typedef INT_PTR (WINAPI *PROC)(void);

#ifdef __cplusplus
}
#endif
#endif
