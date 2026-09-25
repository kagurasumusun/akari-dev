/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINDEF_H
#define WCE_WINDEF_H
#include "wcever.h"
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
/* Surveyed fact: outside emulation, CE headers define stdcall as cdecl.
   DLL export names are undecorated on ARM and x86. */
#ifndef _WIN32_WCE_EMULATION
#undef __stdcall
#define __stdcall __cdecl
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
#ifndef WSAAPI
#define WSAAPI WINAPI
#endif
#ifndef PASCAL
#define PASCAL WINAPI
#endif
#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
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
#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif

/* x86 CE import names have no leading underscore and no @n suffix. */
#if defined(__i386__) || defined(_M_IX86)
#define WCE_IMPORT __declspec(dllimport)
#define WCE_LINK(name) __asm__(#name)
#else
#define WCE_IMPORT
#define WCE_LINK(name)
#endif

#ifndef UNICODE
#define UNICODE 1
#endif
#ifndef _UNICODE
#define _UNICODE 1
#endif
#ifndef _WIN32
#define _WIN32
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
typedef int BOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef uint32_t ULONG_PTR;
typedef int32_t LONG_PTR;
typedef int32_t INT_PTR;
typedef uint32_t UINT_PTR;
typedef uint32_t DWORD_PTR;
typedef ULONG_PTR SIZE_T;
typedef LONG_PTR LPARAM;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LRESULT;
typedef LONG HRESULT;
typedef DWORD COLORREF;
typedef DWORD LCID;
typedef WORD LANGID;
typedef WORD ATOM;
typedef BYTE BOOLEAN;
typedef int HFILE;
typedef void *HANDLE;
typedef void *PVOID;
typedef void *LPVOID;
typedef const void *LPCVOID;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HHOOK);
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
typedef void *HGDIOBJ;
typedef HICON HCURSOR;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR;
typedef WCHAR TCHAR;
typedef WCHAR *LPTSTR;
typedef const WCHAR *LPCTSTR;
typedef BYTE *PBYTE;
typedef BYTE *LPBYTE;
typedef WORD *LPWORD;
typedef DWORD *PDWORD;
typedef DWORD *LPDWORD;
typedef LONG *PLONG;
typedef LONG *LPLONG;
typedef BOOL *LPBOOL;
typedef HANDLE *LPHANDLE;
typedef INT *PINT;
typedef UINT *PUINT;
typedef DWORD REGSAM;
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
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
typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT, *PRECT, *LPRECT;
typedef const RECT *LPCRECT;
typedef struct tagPOINT { LONG x; LONG y; } POINT, *PPOINT, *LPPOINT;
typedef struct tagSIZE { LONG cx; LONG cy; } SIZE, *PSIZE, *LPSIZE;
typedef struct tagPOINTS { SHORT x; SHORT y; } POINTS, *PPOINTS, *LPPOINTS;
typedef INT_PTR (WINAPI *FARPROC)(void);
typedef INT_PTR (WINAPI *PROC)(void);
#define HFILE_ERROR ((HFILE)-1)
#define TEXT(lit) L##lit
#define _T(lit) L##lit
#ifdef __cplusplus
}
#endif
#endif
