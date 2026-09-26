/* Core services: files, processes, threads, synchronisation, memory, time and
 * system information. Original text.
 *
 * Windows CE has no console and no separate kernel32/user32/gdi32 modules: the
 * names below are all exported by coredll.dll.
 */
#ifndef AKARI_WCE_WINBASE_H
#define AKARI_WCE_WINBASE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winnt.h"
#include "winerror.h"

typedef struct akari_SYSTEMTIME {
    WORD wYear; WORD wMonth; WORD wDayOfWeek; WORD wDay;
    WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct akari_WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;

typedef struct akari_WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwOID;
    WCHAR cFileName[MAX_PATH];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

typedef struct akari_BY_HANDLE_FILE_INFORMATION {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD dwVolumeSerialNumber;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD nNumberOfLinks;
    DWORD nFileIndexHigh;
    DWORD nFileIndexLow;
    DWORD dwOID;
} BY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

typedef struct akari_MEMORYSTATUS {
    DWORD dwLength;
    DWORD dwMemoryLoad;
    DWORD dwTotalPhys;
    DWORD dwAvailPhys;
    DWORD dwTotalPageFile;
    DWORD dwAvailPageFile;
    DWORD dwTotalVirtual;
    DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct akari_SYSTEM_INFO {
    union {
        DWORD dwOemId;
        struct { WORD wProcessorArchitecture; WORD wReserved; } s;
    } u;
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

#define PROCESSOR_ARCHITECTURE_INTEL  0
#define PROCESSOR_ARCHITECTURE_MIPS   1
#define PROCESSOR_ARCHITECTURE_ARM    5
#define PROCESSOR_ARCHITECTURE_SH     6
#define PROCESSOR_ARCHITECTURE_UNKNOWN 0xFFFF

typedef struct akari_PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct akari_STARTUPINFOW {
    DWORD cb;
    LPWSTR lpReserved;
    LPWSTR lpDesktop;
    LPWSTR lpTitle;
    DWORD dwX, dwY, dwXSize, dwYSize;
    DWORD dwXCountChars, dwYCountChars, dwFillAttribute, dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;

typedef struct akari_OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    DWORD Offset;
    DWORD OffsetHigh;
    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct akari_SYSTEM_POWER_STATUS {
    BYTE ACLineStatus;
    BYTE BatteryFlag;
    BYTE BatteryLifePercent;
    BYTE Reserved1;
    DWORD BatteryLifeTime;
    DWORD BatteryFullLifeTime;
} SYSTEM_POWER_STATUS, *LPSYSTEM_POWER_STATUS;

/* File creation dispositions and flags. */
#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

#define FILE_SHARE_READ   0x00000001
#define FILE_SHARE_WRITE  0x00000002
#define FILE_SHARE_DELETE 0x00000004

#define FILE_FLAG_WRITE_THROUGH    0x80000000
#define FILE_FLAG_OVERLAPPED       0x40000000
#define FILE_FLAG_NO_BUFFERING     0x20000000
#define FILE_FLAG_RANDOM_ACCESS    0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN  0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE  0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS 0x02000000
#define FILE_FLAG_POSIX_SEMANTICS  0x01000000

#define FILE_BEGIN   0
#define FILE_CURRENT 1
#define FILE_END     2

#define FILE_MAP_COPY    0x0001
#define FILE_MAP_WRITE   0x0002
#define FILE_MAP_READ    0x0004
#define FILE_MAP_ALL_ACCESS SECTION_ALL_ACCESS

#define THREAD_PRIORITY_LOWEST 5
#define THREAD_PRIORITY_BELOW_NORMAL 4
#define THREAD_PRIORITY_NORMAL 3
#define THREAD_PRIORITY_ABOVE_NORMAL 2
#define THREAD_PRIORITY_HIGHEST 1
#define THREAD_PRIORITY_TIME_CRITICAL 0
#define THREAD_PRIORITY_IDLE 7

#define DUPLICATE_CLOSE_SOURCE 0x00000001
#define DUPLICATE_SAME_ACCESS  0x00000002

#define DEBUG_PROCESS 0x00000001

/* Local and global heap flags.  CE defines the full 16-bit set at
 * winbase.h:709 and aliases every GMEM_* name onto its LMEM_* equivalent at
 * winbase.h:735, because on CE GlobalAlloc is LocalAlloc.  The kit previously
 * carried only three LMEM_* flags and no GMEM_* names at all, so ordinary code
 * such as GlobalAlloc(GMEM_MOVEABLE, n) would not compile.
 */
#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_NOCOMPACT      0x0010      /* used for moveable memory */
#define LMEM_NODISCARD      0x0020      /* ignored */
#define LMEM_ZEROINIT       0x0040
#define LMEM_MODIFY         0x0080      /* used only in LocalReAlloc() */
#define LMEM_DISCARDABLE    0x0F00      /* ignored */
#define LMEM_VALID_FLAGS    0x0F72
#define LMEM_INVALID_HANDLE 0x8000
#define LMEM_DDESHARE       0x0000      /* ignored */
#define LMEM_LOWER          0x0000      /* ignored */
#define LMEM_NOT_BANKED     0x0000      /* ignored */
#define LMEM_NOTIFY         0x0000      /* ignored */
#define LMEM_SHARE          0x0000      /* ignored */

#define LHND                (LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)
#define NONZEROLHND         (LMEM_MOVEABLE)
#define NONZEROLPTR         (LMEM_FIXED)

#define LMEM_DISCARDED      0x4000
#define LMEM_LOCKCOUNT      0x00FF

#define GMEM_FIXED          LMEM_FIXED
#define GMEM_MOVEABLE       LMEM_MOVEABLE
#define GPTR                LPTR
#define GHND                LHND
#define GMEM_DDESHARE       LMEM_DDESHARE
#define GMEM_DISCARDABLE    LMEM_DISCARDABLE
#define GMEM_LOWER          LMEM_LOWER
#define GMEM_NOCOMPACT      LMEM_NOCOMPACT
#define GMEM_NODISCARD      LMEM_NODISCARD
#define GMEM_NOT_BANKED     LMEM_NOT_BANKED
#define GMEM_NOTIFY         LMEM_NOTIFY
#define GMEM_SHARE          LMEM_SHARE
#define GMEM_ZEROINIT       LMEM_ZEROINIT
#define GMEM_VALID_FLAGS    LMEM_VALID_FLAGS
#define GMEM_INVALID_HANDLE LMEM_INVALID_HANDLE
#define LPTR (LMEM_FIXED | LMEM_ZEROINIT)

/* Files. */
WINBASEAPI HANDLE WINAPI CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess,
    DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINBASEAPI BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINBASEAPI BOOL WINAPI CloseHandle(HANDLE hObject);
WINBASEAPI BOOL WINAPI DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
    HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess,
    BOOL bInheritHandle, DWORD dwOptions);
WINBASEAPI BOOL WINAPI DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
    HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess,
    BOOL bInheritHandle, DWORD dwOptions);
WINBASEAPI DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove,
    LONG *lpDistanceToMoveHigh, DWORD dwMoveMethod);
WINBASEAPI DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
WINBASEAPI BOOL WINAPI GetFileInformationByHandle(HANDLE hFile,
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
typedef enum akari_GET_FILEEX_INFO_LEVELS {
    GetFileExInfoStandard,
    GetFileExMaxInfoLevel
} GET_FILEEX_INFO_LEVELS;

WINBASEAPI BOOL WINAPI GetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId,
    LPVOID lpFileInformation);
WINBASEAPI DWORD WINAPI GetFileAttributesW(LPCWSTR lpFileName);
WINBASEAPI BOOL WINAPI SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes);
WINBASEAPI BOOL WINAPI DeleteFileW(LPCWSTR lpFileName);
WINBASEAPI BOOL WINAPI CopyFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName,
    BOOL bFailIfExists);
WINBASEAPI BOOL WINAPI MoveFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);
WINBASEAPI BOOL WINAPI FlushFileBuffers(HANDLE hFile);
WINBASEAPI BOOL WINAPI SetEndOfFile(HANDLE hFile);
WINBASEAPI BOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime,
    LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
WINBASEAPI BOOL WINAPI SetFileTime(HANDLE hFile, const FILETIME *lpCreationTime,
    const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime);
WINBASEAPI HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
WINBASEAPI BOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
WINBASEAPI BOOL WINAPI FindClose(HANDLE hFindFile);
WINBASEAPI BOOL WINAPI CreateDirectoryW(LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes);
WINBASEAPI BOOL WINAPI RemoveDirectoryW(LPCWSTR lpPathName);
/* Windows CE has no GetDiskFreeSpace and no GetFullPathName; the "Ex" form is
 * what the platform provides, and paths are resolved by the file system. */
WINBASEAPI BOOL WINAPI GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName,
    PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes,
    PULARGE_INTEGER lpTotalNumberOfFreeBytes);
WINBASEAPI DWORD WINAPI GetTempPathW(DWORD nBufferLength, LPWSTR lpBuffer);
WINBASEAPI UINT WINAPI GetTempFileNameW(LPCWSTR lpPathName, LPCWSTR lpPrefixString,
    UINT uUnique, LPWSTR lpTempFileName);
WINBASEAPI BOOL WINAPI DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode,
    LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize,
    LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
/* Storage Manager volume details come from CeGetVolumeInfoW on Windows CE 5.0
 * and later; see storemgr.h. There is no GetVolumeInformation on this platform. */
#ifdef AKARI_HAVE_FILE_MAPPING
WINBASEAPI HANDLE WINAPI CreateFileMappingW(HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow, LPCWSTR lpName);
WINBASEAPI LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject,
    DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,
    DWORD dwNumberOfBytesToMap);
WINBASEAPI BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress);
WINBASEAPI BOOL WINAPI FlushViewOfFile(LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush);
#endif

/* Errors and messages. */
WINBASEAPI DWORD WINAPI GetLastError(VOID);
WINBASEAPI VOID WINAPI SetLastError(DWORD dwErrCode);
WINBASEAPI DWORD WINAPI FormatMessageW(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId,
    DWORD dwLanguageId, LPWSTR lpBuffer, DWORD nSize, va_list *Arguments);
/* SetErrorMode does not exist on Windows CE: hard faults always raise. */

#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define FORMAT_MESSAGE_FROM_STRING     0x00000400
#define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000

/* Memory. */
WINBASEAPI HLOCAL WINAPI LocalAlloc(UINT uFlags, UINT uBytes);
WINBASEAPI HLOCAL WINAPI LocalReAlloc(HLOCAL hMem, UINT uBytes, UINT uFlags);
WINBASEAPI HLOCAL WINAPI LocalFree(HLOCAL hMem);
WINBASEAPI UINT WINAPI LocalSize(HLOCAL hMem);

/*
 * Windows CE has a single flat heap, so there is no second "global" heap and no
 * locking step: a handle returned by LocalAlloc is the pointer itself. The
 * Local* and Global* names therefore resolve to the four LocalAlloc family
 * exports plus trivial pointer conversions.
 */
#define LocalLock(hMem)      ((LPVOID)(hMem))
#define LocalUnlock(hMem) (0)
#define GlobalAlloc(uFlags, dwBytes)      LocalAlloc((uFlags), (dwBytes))
#define GlobalReAlloc(handle, cb, uFlags) LocalReAlloc(handle, cb, LMEM_MOVEABLE)
#define GlobalFree(hMem)     LocalFree(hMem)
#define GlobalSize(hMem)     LocalSize(hMem)
#define GlobalLock(hMem)     LocalLock(hMem)
#define GlobalUnlock(hMem)   LocalUnlock(hMem)
WINBASEAPI LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, DWORD dwSize,
    DWORD flAllocationType, DWORD flProtect);
WINBASEAPI BOOL WINAPI VirtualFree(LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType);
WINBASEAPI BOOL WINAPI VirtualProtect(LPVOID lpAddress, DWORD dwSize,
    DWORD flNewProtect, PDWORD lpflOldProtect);
WINBASEAPI VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer);

/*
 * Thread local storage. The single exported entry point is TlsCall, which
 * allocates and releases an index; TlsAlloc and TlsFree are the documented names
 * applications use and are provided here as inline wrappers over it.
 */
#define TLS_FUNCALLOC 0
#define TLS_FUNCFREE  1

WINBASEAPI DWORD WINAPI TlsCall(DWORD dwFunction, DWORD dwParam);
WINBASEAPI LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex);
WINBASEAPI BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);

static __inline DWORD TlsAlloc(void) { return TlsCall(TLS_FUNCALLOC, 0); }
static __inline BOOL TlsFree(DWORD dwTlsIndex) { return (BOOL)TlsCall(TLS_FUNCFREE, dwTlsIndex); }

#define TLS_OUT_OF_INDEXES 0xFFFFFFFF

/* Threads and processes. */
WINBASEAPI HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
    DWORD dwCreationFlags, LPDWORD lpThreadId);
WINBASEAPI HANDLE WINAPI CreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
    LPVOID lpEnvironment, LPWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation);
WINBASEAPI VOID WINAPI ExitThread(DWORD dwExitCode);
WINBASEAPI BOOL WINAPI TerminateThread(HANDLE hThread, DWORD dwExitCode);
WINBASEAPI BOOL WINAPI TerminateProcess(HANDLE hProcess, DWORD uExitCode);
WINBASEAPI BOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);
WINBASEAPI BOOL WINAPI GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode);
WINBASEAPI DWORD WINAPI ResumeThread(HANDLE hThread);
WINBASEAPI DWORD WINAPI SuspendThread(HANDLE hThread);
WINBASEAPI BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority);
WINBASEAPI int WINAPI GetThreadPriority(HANDLE hThread);
/*
 * GetCurrentThread, GetCurrentProcess, GetCurrentThreadId and GetCurrentProcessId
 * are deliberately absent here. On Windows CE they are compiler inlines that read
 * kernel-private per-thread data, which is outside the development surface this
 * kit covers. Use the handle or identifier handed back by CreateThread, or
 * GetThreadId/GetProcessId on Windows CE 6.0, and call ExitThread or
 * TerminateProcess/TerminateThread to stop execution.
 */
#if (_WIN32_WCE >= 0x600)
WINBASEAPI DWORD WINAPI GetThreadId(HANDLE hThread);
WINBASEAPI DWORD WINAPI GetProcessId(HANDLE hProcess);
#endif
WINBASEAPI LPWSTR WINAPI GetCommandLineW(VOID);

/* Synchronisation. */
WINBASEAPI VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINBASEAPI HANDLE WINAPI CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);
WINBASEAPI BOOL WINAPI EventModify(HANDLE hEvent, DWORD dwFunc);

#define EVENT_PULSE 1
#define EVENT_RESET 2
#define EVENT_SET   3

/*
 * SetEvent, ResetEvent and PulseEvent are not exports on Windows CE; every state
 * change goes through the single EventModify entry point, so the familiar names
 * are provided as inline wrappers.
 */
static __inline BOOL SetEvent(HANDLE hEvent) { return EventModify(hEvent, EVENT_SET); }
static __inline BOOL ResetEvent(HANDLE hEvent) { return EventModify(hEvent, EVENT_RESET); }
static __inline BOOL PulseEvent(HANDLE hEvent) { return EventModify(hEvent, EVENT_PULSE); }
WINBASEAPI HANDLE WINAPI CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes,
    BOOL bInitialOwner, LPCWSTR lpName);
WINBASEAPI BOOL WINAPI ReleaseMutex(HANDLE hMutex);
WINBASEAPI HANDLE WINAPI CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName);
WINBASEAPI BOOL WINAPI ReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount,
    LPLONG lpPreviousCount);
WINBASEAPI DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI WaitForMultipleObjects(DWORD nCount, const HANDLE *lpHandles,
    BOOL bWaitAll, DWORD dwMilliseconds);
WINBASEAPI DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount,
    const HANDLE *pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags);
WINBASEAPI VOID WINAPI Sleep(DWORD dwMilliseconds);

typedef struct akari_OSVERSIONINFOW {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    WCHAR szCSDVersion[128];
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW;

/* Modules and versioning. */
WINBASEAPI HMODULE WINAPI LoadLibraryW(LPCWSTR lpLibFileName);
WINBASEAPI HMODULE WINAPI LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
WINBASEAPI BOOL WINAPI FreeLibrary(HMODULE hLibModule);
WINBASEAPI FARPROC WINAPI GetProcAddressW(HMODULE hModule, LPCWSTR lpProcName);
WINBASEAPI HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName);
WINBASEAPI DWORD WINAPI GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
WINBASEAPI BOOL WINAPI GetVersionExW(OSVERSIONINFOW *lpVersionInformation);
WINBASEAPI VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
/* DebugBreak is a compiler intrinsic on Windows CE rather than an export. */
#if defined(_MSC_VER)
#define DebugBreak() __debugbreak()
#elif defined(__GNUC__)
static __inline void DebugBreak(void) { __builtin_trap(); }
#else
WINBASEAPI VOID WINAPI DebugBreak(VOID);
#endif
WINBASEAPI VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString);

#define DONT_RESOLVE_DLL_REFERENCES 0x00000001
#define LOAD_LIBRARY_AS_DATAFILE    0x00000002

/* Time. */
WINBASEAPI VOID WINAPI GetSystemTime(LPSYSTEMTIME lpSystemTime);
WINBASEAPI VOID WINAPI GetLocalTime(LPSYSTEMTIME lpSystemTime);
WINBASEAPI BOOL WINAPI SetSystemTime(const SYSTEMTIME *lpSystemTime);
WINBASEAPI BOOL WINAPI SetLocalTime(const SYSTEMTIME *lpSystemTime);
WINBASEAPI DWORD WINAPI GetTickCount(VOID);
#if (_WIN32_WCE >= 0x600)
WINBASEAPI VOID WINAPI GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);
#endif
WINBASEAPI BOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME *lpSystemTime,
    LPFILETIME lpFileTime);
WINBASEAPI BOOL WINAPI FileTimeToSystemTime(const FILETIME *lpFileTime,
    LPSYSTEMTIME lpSystemTime);
WINBASEAPI BOOL WINAPI FileTimeToLocalFileTime(const FILETIME *lpFileTime,
    LPFILETIME lpLocalFileTime);
WINBASEAPI BOOL WINAPI LocalFileTimeToFileTime(const FILETIME *lpLocalFileTime,
    LPFILETIME lpFileTime);
WINBASEAPI BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
WINBASEAPI BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

/* Strings and locale support that lives in coredll. */
/*
 * The lstr* family is only partly present on Windows CE: the comparison forms are
 * exports while the length, copy and concatenate forms map onto the wide string
 * functions in the same module.
 */
#define lstrlenW(lpString)              wcslen(lpString)
#define lstrlenA(lpString)              ((int)strlen(lpString))
#define lstrcpyW(lpString1, lpString2)  wcscpy(lpString1, lpString2)
#define lstrcatW(lpString1, lpString2)  wcscat(lpString1, lpString2)
WINBASEAPI int WINAPI lstrcmpW(LPCWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI lstrcmpiW(LPCWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
    int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
WINBASEAPI int WINAPI WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr,
    int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCSTR lpDefaultChar,
    LPBOOL lpUsedDefaultChar);
WINBASEAPI int WINAPI wsprintfW(LPWSTR lpOut, LPCWSTR lpFmt, ...);
WINBASEAPI int WINAPI wvsprintfW(LPWSTR lpOutput, LPCWSTR lpFmt, void *arglist);

#define CP_ACP     0
#define CP_OEMCP   1
#define CP_MACCP   2
#define CP_THREAD_ACP 3
#define CP_SYMBOL  42
#define CP_UTF7    65000
#define CP_UTF8    65001

/* Battery and power state reporting is GetSystemPowerStatusEx and
 * GetSystemPowerStatusEx2; see pm.h. */

#ifdef AKARI_HAVE_STORE_MANAGER
#include "storemgr.h"
#endif

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WINBASE_H */
