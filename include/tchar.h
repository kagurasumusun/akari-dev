/* Text mapping. Original text.
 *
 * Windows CE builds are Unicode builds; the ANSI variants exist only for a
 * small set of APIs. Applications should define UNICODE and _UNICODE.
 */
#ifndef AKARI_WCE_TCHAR_H
#define AKARI_WCE_TCHAR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winnt.h"

#if defined(UNICODE) || defined(_UNICODE)
typedef WCHAR TCHAR;
typedef WCHAR *PTCHAR, *LPTCH, *PTSTR, *LPTSTR;
typedef const WCHAR *LPCTSTR, *LPCTCH;
typedef const WCHAR *PCTSTR;
#define __AKARI_TEXT(x) L##x
#else
typedef char TCHAR;
typedef char *PTCHAR, *LPTCH, *PTSTR, *LPTSTR;
typedef const char *LPCTSTR, *LPCTCH;
typedef const char *PCTSTR;
#define __AKARI_TEXT(x) x
#endif

#define _T(x)  __AKARI_TEXT(x)
#define TEXT(x) __AKARI_TEXT(x)



/*
 * Text-mapped names. Windows CE is a Unicode-only platform, but a lot of
 * portable code is written against the unsuffixed names. Every target below is
 * a real export of coredll.dll on all three supported releases, except where the
 * comment says otherwise.
 */
#define CreateFile              CreateFileW
#define FindFirstFile           FindFirstFileW
#define FindNextFile            FindNextFileW
#define GetModuleFileName       GetModuleFileNameW
#define LoadLibrary             LoadLibraryW
#define GetProcAddress          GetProcAddressW
#define FormatMessage           FormatMessageW
#define CreateMutex             CreateMutexW
#define CreateEvent             CreateEventW
#define OpenEvent               OpenEventW
#define CreateDirectory         CreateDirectoryW
#define RemoveDirectory         RemoveDirectoryW
#define GetFileAttributes       GetFileAttributesW
#define SetFileAttributes       SetFileAttributesW
#define DeleteFile              DeleteFileW
#define CopyFile                CopyFileW
#define MoveFile                MoveFileW
#define GetTempPath             GetTempPathW
#define GetTempFileName         GetTempFileNameW
#define CreateWindowEx          CreateWindowExW
#define RegisterClass           RegisterClassW
#define UnregisterClass         UnregisterClassW
#define FindWindow              FindWindowW
#define MessageBox              MessageBoxW
#define SetWindowText           SetWindowTextW
#define GetWindowText           GetWindowTextW
#define GetWindowTextLength     GetWindowTextLengthW
#define SendMessage             SendMessageW
#define PostMessage             PostMessageW
#define GetMessage              GetMessageW
#define PeekMessage             PeekMessageW
#define DispatchMessage         DispatchMessageW
#define SetDlgItemText          SetDlgItemTextW
#define GetDlgItemText          GetDlgItemTextW
#define DialogBoxIndirectParam  DialogBoxIndirectParamW
#define CreateDialogIndirectParam CreateDialogIndirectParamW
#define LoadString              LoadStringW
#define LoadIcon                LoadIconW
#define LoadCursor              LoadCursorW
#define LoadBitmap              LoadBitmapW
#define FindResource            FindResourceW
#define DefWindowProc           DefWindowProcW
#define CallWindowProc          CallWindowProcW
#define GetClassInfo            GetClassInfoW
#define GlobalAddAtom           GlobalAddAtomW
#define RegOpenKeyEx            RegOpenKeyExW
#define RegCreateKeyEx          RegCreateKeyExW
#define RegQueryValueEx         RegQueryValueExW
#define RegSetValueEx           RegSetValueExW
#define RegDeleteValue          RegDeleteValueW
#define RegDeleteKey            RegDeleteKeyW
#define RegEnumKeyEx            RegEnumKeyExW
#define RegEnumValue            RegEnumValueW
#define RegQueryInfoKey         RegQueryInfoKeyW
#define GetLocaleInfo           GetLocaleInfoW
#define SetLocaleInfo           SetLocaleInfoW
#define CompareString           CompareStringW
#define LCMapString             LCMapStringW
#define GetDateFormat           GetDateFormatW
#define GetTimeFormat           GetTimeFormatW
#define GetDiskFreeSpaceEx      GetDiskFreeSpaceExW
#define TextOut                 TextOutW
#define ExtTextOut              ExtTextOutW
#define DrawText                DrawTextW
#define GetTextMetrics          GetTextMetricsW
#define GetTextExtentExPoint    GetTextExtentExPointW
#define CreateFontIndirect      CreateFontIndirectW
#define GetObject               GetObjectW
#define GetWindowLong           GetWindowLongW
#define SetWindowLong           SetWindowLongW
#define lstrcmp                 lstrcmpW
#define lstrcmpi                lstrcmpiW
#define wsprintf                wsprintfW
#define wvsprintf               wvsprintfW
#define OutputDebugString       OutputDebugStringW
#define CharUpper               CharUpperW
#define CharLower               CharLowerW
#define MapVirtualKey           MapVirtualKeyW
#define SystemParametersInfo    SystemParametersInfoW

/* Generic text helpers. The unsuffixed lstr names that are exports were mapped
 * above; the rest resolve to the wide string functions in the same module. */
#ifdef UNICODE
#define _tcslen     wcslen
#define _tcscpy     wcscpy
#define _tcsncpy    wcsncpy
#define _tcscat     wcscat
#define _tcscmp     wcscmp
#define _tcsicmp    _wcsicmp
#define _tcsnicmp   _wcsnicmp
#define _tcschr     wcschr
#define _tcsrchr    wcsrchr
#define _tcsstr     wcsstr
#define _tcsupr     _wcsupr
#define _tcslwr     _wcslwr
#define _tcsdup     _wcsdup
#define _totupper   towupper
#define _totlower   towlower
#define _ttoi       _wtoi
#define _ttol       _wtol
#define _sntprintf  _snwprintf
#define _vstprintf  vswprintf
#else
#define _tcslen     strlen
#define _tcscpy     strcpy
#define _tcsncpy    strncpy
#define _tcscat     strcat
#define _tcscmp     strcmp
#define _tcsicmp    _stricmp
#define _tcsnicmp   _strnicmp
#define _tcschr     strchr
#define _tcsrchr    strrchr
#define _tcsstr     strstr
#define _totupper   toupper
#define _totlower   tolower
#define _ttoi(s)    ((int)atol(s))
#define _ttol       atol
#define _sntprintf  _snprintf
#define _vstprintf  _vsnprintf
#endif

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_TCHAR_H */
