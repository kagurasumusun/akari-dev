/* Base types, handles and geometry. Original text. */
#ifndef AKARI_WCE_WINDEF_H
#define AKARI_WCE_WINDEF_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "wcever.h"

#if !defined(NULL)
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define FALSE 0
#define TRUE  1

/* Segmented-address modifiers inherited from 16-bit Windows.  On every 32-bit
 * CE CPU they expand to nothing, but they still appear in the SDK's own
 * declarations, so code written against them has to compile.
 */
#undef  FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#define far
#define near
#ifndef CONST
#define CONST               const
#endif

typedef int BOOL;
typedef BOOL *PBOOL, *LPBOOL;
typedef unsigned char BYTE;
typedef BYTE *PBYTE, *LPBYTE;
typedef const BYTE *LPCBYTE;
typedef unsigned short WORD;
typedef WORD *PWORD, *LPWORD;
typedef unsigned long DWORD;
typedef DWORD *PDWORD, *LPDWORD;
typedef int INT;
typedef INT *PINT, *LPINT;
typedef const INT *LPCINT;
typedef unsigned int UINT;
typedef UINT *PUINT, *LPUINT;
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef LONG *PLONG, *LPLONG;
typedef float FLOAT;
typedef double DOUBLE;
typedef void VOID;
typedef void *PVOID, *LPVOID;
typedef const void *LPCVOID;
typedef char *PCHAR, *LPSTR, *PSTR;
typedef const char *LPCSTR, *PCSTR;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef BYTE BOOLEAN;
typedef BOOLEAN *PBOOLEAN;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

typedef void *HANDLE;
typedef HANDLE *PHANDLE, *LPHANDLE;
typedef HANDLE HINSTANCE;
typedef HINSTANCE *PHINSTANCE;
typedef HANDLE HMODULE;
typedef HANDLE HWND;
typedef HWND *PHWND;
typedef HANDLE HDC;
typedef HANDLE HICON;
typedef HANDLE HCURSOR;
typedef HICON HBRUSH;
typedef HANDLE HPEN;
typedef HANDLE HFONT;
typedef HANDLE HBITMAP;
typedef HANDLE HPALETTE;
typedef HANDLE HRGN;
typedef HANDLE HMENU;
typedef HANDLE HACCEL;
typedef HANDLE HKEY;
typedef HANDLE *PHKEY;
typedef HANDLE HRSRC;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE HFILE;
typedef HANDLE HPROPSHEETPAGE;
typedef struct akari_IMAGELIST *HIMAGELIST;
typedef ULONG ATOM;
typedef HANDLE HDROP;

typedef unsigned long ULONG_PTR;
typedef long LONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
typedef ULONG_PTR UINT_PTR, *PUINT_PTR;
typedef LONG_PTR INT_PTR, *PINT_PTR;
typedef ULONG_PTR *PULONG_PTR;
typedef LONG_PTR SHANDLE_PTR;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

typedef struct akari_POINT { LONG x; LONG y; } POINT, *PPOINT, *LPPOINT;
typedef struct akari_SIZE { LONG cx; LONG cy; } SIZE, *PSIZE, *LPSIZE;
typedef SIZE SIZEL;
typedef struct akari_RECT { LONG left; LONG top; LONG right; LONG bottom; }
    RECT, *PRECT, *LPRECT;
typedef const RECT *LPCRECT;

#define MAKEWORD(lo, hi)  ((WORD)(((BYTE)(lo)) | ((WORD)((BYTE)(hi))) << 8))
#define MAKELONG(lo, hi)  ((LONG)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#define MAKEWPARAM(lo, hi) ((WPARAM)MAKELONG((lo), (hi)))
#define MAKELPARAM(lo, hi) ((LPARAM)MAKELONG((lo), (hi)))
#define MAKELRESULT(lo, hi) ((LRESULT)MAKELONG((lo), (hi)))
#define LOWORD(l)   ((WORD)((DWORD_PTR)(l) & 0xFFFF))
#define HIWORD(l)   ((WORD)(((DWORD_PTR)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)   ((BYTE)((DWORD_PTR)(w) & 0xFF))
#define HIBYTE(w)   ((BYTE)(((DWORD_PTR)(w) >> 8) & 0xFF))
/*
 * Memory helpers. Windows CE has no moveable memory, so there is no handle
 * indirection to unwind; these are written out rather than mapped onto the run
 * time so that a translation unit including nothing but this kit still compiles
 * on releases where the C run time is linked separately from coredll.
 */
static __inline void ZeroMemory(PVOID Destination, size_t Length)
{
    unsigned char *d = (unsigned char *)Destination;
    while (Length--) { *d++ = 0; }
}
static __inline void FillMemory(PVOID Destination, size_t Length, BYTE Fill)
{
    unsigned char *d = (unsigned char *)Destination;
    while (Length--) { *d++ = Fill; }
}
static __inline void CopyMemory(PVOID Destination, const void *Source, size_t Length)
{
    unsigned char *d = (unsigned char *)Destination;
    const unsigned char *s = (const unsigned char *)Source;
    while (Length--) { *d++ = *s++; }
}
static __inline void MoveMemory(PVOID Destination, const void *Source, size_t Length)
{
    unsigned char *d = (unsigned char *)Destination;
    const unsigned char *s = (const unsigned char *)Source;
    if (d < s) {
        while (Length--) { *d++ = *s++; }
    } else {
        d += Length; s += Length;
        while (Length--) { *--d = *--s; }
    }
}
#define SecureZeroMemory(Destination, Length) ZeroMemory((Destination), (Length))

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

#define MAX_PATH 260
#define INFINITE 0xFFFFFFFFu

typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef VOID (CALLBACK *TIMERPROC)(HWND, UINT, UINT, DWORD);
typedef BOOL (CALLBACK *PROC)(void);
typedef VOID (CALLBACK *FIBER_START_ROUTINE)(LPVOID);
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);
typedef VOID (CALLBACK *LPOVERLAPPED_COMPLETION_ROUTINE)(DWORD, DWORD, LPVOID);
typedef INT (WINAPI *FARPROC)(void);

#define IN
#define OUT
#define OPTIONAL

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WINDEF_H */
