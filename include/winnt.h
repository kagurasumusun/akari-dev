/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINNT_H
#define WCE_WINNT_H
#include "windef.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef union _LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; } u;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
typedef union _ULARGE_INTEGER {
    struct { DWORD LowPart; DWORD HighPart; } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;
typedef struct _MEMORY_BASIC_INFORMATION {
    PVOID BaseAddress;
    PVOID AllocationBase;
    DWORD AllocationProtect;
    SIZE_T RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
#define MAKELANGID(p, s) ((((WORD)(s)) << 10) | (WORD)(p))
#define MAKELCID(lgid, sort) ((DWORD)((((DWORD)(sort)) << 16) | ((DWORD)(lgid))))
#define LANG_NEUTRAL 0x00
#define LANG_ENGLISH 0x09
#define LANG_JAPANESE 0x11
#define SUBLANG_NEUTRAL 0x00
#define SUBLANG_DEFAULT 0x01
#define SORT_DEFAULT 0x0

typedef struct _GUID {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[8];
} GUID;
typedef GUID *LPGUID;
typedef const GUID *LPCGUID;
typedef const GUID *REFGUID;
typedef const GUID *REFIID;
typedef const GUID *REFCLSID;
typedef GUID IID;
typedef GUID CLSID;
typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } FILETIME, *PFILETIME, *LPFILETIME;
typedef struct _SYSTEMTIME {
    WORD wYear; WORD wMonth; WORD wDayOfWeek; WORD wDay;
    WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
typedef struct _OVERLAPPED {
    DWORD Internal; DWORD InternalHigh; DWORD Offset; DWORD OffsetHigh; HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED, *POVERLAPPED;
typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
/* CE critical section. The desktop RTL layout is not the on-device layout. */
typedef struct CRITICAL_SECTION {
    unsigned int LockCount;
    HANDLE OwnerThread;
    HANDLE hCrit;
    DWORD needtrap;
    DWORD dwContentions;
} CRITICAL_SECTION, *LPCRITICAL_SECTION, *PCRITICAL_SECTION;
typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess; HANDLE hThread; DWORD dwProcessId; DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
typedef struct _STARTUPINFOW {
    DWORD cb; LPWSTR lpReserved; LPWSTR lpDesktop; LPWSTR lpTitle;
    DWORD dwX; DWORD dwY; DWORD dwXSize; DWORD dwYSize;
    DWORD dwXCountChars; DWORD dwYCountChars; DWORD dwFillAttribute; DWORD dwFlags;
    WORD wShowWindow; WORD cbReserved2; LPBYTE lpReserved2;
    HANDLE hStdInput; HANDLE hStdOutput; HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW, *PSTARTUPINFOW;
typedef STARTUPINFOW STARTUPINFO;
typedef LPSTARTUPINFOW LPSTARTUPINFO;
typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwOID;
    WCHAR cFileName[MAX_PATH];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;
typedef struct tagMSG {
    HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt;
} MSG, *PMSG, *LPMSG;
typedef LRESULT (WINAPI *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);
typedef INT_PTR (WINAPI *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef struct tagWNDCLASSW {
    UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra;
    HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground;
    LPCWSTR lpszMenuName; LPCWSTR lpszClassName;
} WNDCLASSW, *PWNDCLASSW, *LPWNDCLASSW;
typedef WNDCLASSW WNDCLASS;
typedef LPWNDCLASSW LPWNDCLASS;
#define LF_FACESIZE 32
typedef struct tagLOGFONTW {
    LONG lfHeight; LONG lfWidth; LONG lfEscapement; LONG lfOrientation; LONG lfWeight;
    BYTE lfItalic; BYTE lfUnderline; BYTE lfStrikeOut; BYTE lfCharSet;
    BYTE lfOutPrecision; BYTE lfClipPrecision; BYTE lfQuality; BYTE lfPitchAndFamily;
    WCHAR lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, *LPLOGFONTW;
typedef LOGFONTW LOGFONT;
typedef LPLOGFONTW LPLOGFONT;
typedef struct tagRGBQUAD { BYTE rgbBlue; BYTE rgbGreen; BYTE rgbRed; BYTE rgbReserved; } RGBQUAD, *LPRGBQUAD;
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize; LONG biWidth; LONG biHeight; WORD biPlanes; WORD biBitCount;
    DWORD biCompression; DWORD biSizeImage; LONG biXPelsPerMeter; LONG biYPelsPerMeter;
    DWORD biClrUsed; DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef u_int SOCKET;
typedef struct tagNMHDR { HWND hwndFrom; UINT idFrom; UINT code; } NMHDR, *LPNMHDR;
typedef struct tagPALETTEENTRY { BYTE peRed; BYTE peGreen; BYTE peBlue; BYTE peFlags; } PALETTEENTRY, *LPPALETTEENTRY;
typedef union tagCY { struct { ULONG Lo; LONG Hi; } s; LONGLONG int64; } CY, *LPCY;

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_INROM 0x00000040
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800
#define FILE_ATTRIBUTE_OFFLINE 0x00001000
#define FILE_ATTRIBUTE_ROMSTATICREF 0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ROMMODULE 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000
#define FILE_NOTIFY_CHANGE_FILE_NAME 0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME 0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES 0x00000004
#define FILE_NOTIFY_CHANGE_SIZE 0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE 0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS 0x00000020
#define FILE_NOTIFY_CHANGE_CREATION 0x00000040
#define FILE_NOTIFY_CHANGE_SECURITY 0x00000100
#define FILE_NOTIFY_CHANGE_CEGETINFO 0x80000000
#define FILE_ACTION_ADDED 0x00000001
#define FILE_ACTION_REMOVED 0x00000002
#define FILE_ACTION_MODIFIED 0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME 0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME 0x00000005
#define FILE_ACTION_CHANGE_COMPLETED 0x00010000
#define FILE_CASE_SENSITIVE_SEARCH 0x00000001
#define FILE_CASE_PRESERVED_NAMES 0x00000002
#define FILE_UNICODE_ON_DISK 0x00000004
#define FILE_PERSISTENT_ACLS 0x00000008
#define FILE_FILE_COMPRESSION 0x00000010
#define FILE_VOLUME_QUOTAS 0x00000020
#define FILE_SUPPORTS_SPARSE_FILES 0x00000040
#define FILE_SUPPORTS_REPARSE_POINTS 0x00000080
#define FILE_SUPPORTS_REMOTE_STORAGE 0x00000100
#define FILE_VOLUME_IS_COMPRESSED 0x00008000
#define FILE_SUPPORTS_OBJECT_IDS 0x00010000
#define FILE_SUPPORTS_ENCRYPTION 0x00020000
#include "wceunk.h"
#ifdef __cplusplus
}
#endif
#endif
