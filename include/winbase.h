/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINBASE_H
#define WCE_WINBASE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTIME_ZONE_INFORMATION { LONG Bias; WCHAR StandardName[ 32 ]; SYSTEMTIME StandardDate; LONG StandardBias; WCHAR DaylightName[ 32 ]; SYSTEMTIME DaylightDate; LONG DaylightBias; } TIME_ZONE_INFORMATION, *PTIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;
typedef struct tagMEMORYSTATUS { DWORD dwLength; DWORD dwMemoryLoad; DWORD dwTotalPhys; DWORD dwAvailPhys; DWORD dwTotalPageFile; DWORD dwAvailPageFile; DWORD dwTotalVirtual; DWORD dwAvailVirtual; } MEMORYSTATUS, *PMEMORYSTATUS, *LPMEMORYSTATUS;
typedef struct tagOSVERSIONINFOA { DWORD dwOSVersionInfoSize; DWORD dwMajorVersion; DWORD dwMinorVersion; DWORD dwBuildNumber; DWORD dwPlatformId; CHAR szCSDVersion[ 128 ]; } OSVERSIONINFOA, *POSVERSIONINFOA, *LPOSVERSIONINFOA;
typedef struct tagOSVERSIONINFOW { DWORD dwOSVersionInfoSize; DWORD dwMajorVersion; DWORD dwMinorVersion; DWORD dwBuildNumber; DWORD dwPlatformId; WCHAR szCSDVersion[ 128 ]; } OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW;
typedef struct tagCREATE_THREAD_DEBUG_INFO { HANDLE hThread; LPVOID lpThreadLocalBase; LPTHREAD_START_ROUTINE lpStartAddress; } CREATE_THREAD_DEBUG_INFO, *PCREATE_THREAD_DEBUG_INFO, *LPCREATE_THREAD_DEBUG_INFO;
typedef struct tagCREATE_PROCESS_DEBUG_INFO { HANDLE hFile; HANDLE hProcess; HANDLE hThread; LPVOID lpBaseOfImage; DWORD dwDebugInfoFileOffset; DWORD nDebugInfoSize; LPVOID lpThreadLocalBase; LPTHREAD_START_ROUTINE lpStartAddress; LPVOID lpImageName; WORD fUnicode; } CREATE_PROCESS_DEBUG_INFO, *PCREATE_PROCESS_DEBUG_INFO, *LPCREATE_PROCESS_DEBUG_INFO;
typedef struct tagEXIT_THREAD_DEBUG_INFO { DWORD dwExitCode; } EXIT_THREAD_DEBUG_INFO, *PEXIT_THREAD_DEBUG_INFO, *LPEXIT_THREAD_DEBUG_INFO;
typedef struct tagEXIT_PROCESS_DEBUG_INFO { DWORD dwExitCode; } EXIT_PROCESS_DEBUG_INFO, *PEXIT_PROCESS_DEBUG_INFO, *LPEXIT_PROCESS_DEBUG_INFO;
typedef struct tagLOAD_DLL_DEBUG_INFO { HANDLE hFile; LPVOID lpBaseOfDll; DWORD dwDebugInfoFileOffset; DWORD nDebugInfoSize; LPVOID lpImageName; WORD fUnicode; } LOAD_DLL_DEBUG_INFO, *PLOAD_DLL_DEBUG_INFO, *LPLOAD_DLL_DEBUG_INFO;
typedef struct tagUNLOAD_DLL_DEBUG_INFO { LPVOID lpBaseOfDll; } UNLOAD_DLL_DEBUG_INFO, *PUNLOAD_DLL_DEBUG_INFO, *LPUNLOAD_DLL_DEBUG_INFO;
typedef struct tagOUTPUT_DEBUG_STRING_INFO { LPSTR lpDebugStringData; WORD fUnicode; WORD nDebugStringLength; } OUTPUT_DEBUG_STRING_INFO, *POUTPUT_DEBUG_STRING_INFO, *LPOUTPUT_DEBUG_STRING_INFO;
typedef struct tagRIP_INFO { DWORD dwError; DWORD dwType; } RIP_INFO, *PRIP_INFO, *LPRIP_INFO;
typedef struct tagWIN32_FILE_ATTRIBUTE_DATA { DWORD dwFileAttributes; FILETIME ftCreationTime; FILETIME ftLastAccessTime; FILETIME ftLastWriteTime; DWORD nFileSizeHigh; DWORD nFileSizeLow; } WIN32_FILE_ATTRIBUTE_DATA, *PWIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
typedef struct tagBY_HANDLE_FILE_INFORMATION { DWORD dwFileAttributes; FILETIME ftCreationTime; FILETIME ftLastAccessTime; FILETIME ftLastWriteTime; DWORD dwVolumeSerialNumber; DWORD nFileSizeHigh; DWORD nFileSizeLow; DWORD nNumberOfLinks; DWORD nFileIndexHigh; DWORD nFileIndexLow; DWORD dwOID; } BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;
typedef struct tagCOMMPROP { WORD wPacketLength; WORD wPacketVersion; DWORD dwServiceMask; DWORD dwReserved1; DWORD dwMaxTxQueue; DWORD dwMaxRxQueue; DWORD dwMaxBaud; DWORD dwProvSubType; DWORD dwProvCapabilities; DWORD dwSettableParams; DWORD dwSettableBaud; WORD wSettableData; WORD wSettableStopParity; DWORD dwCurrentTxQueue; DWORD dwCurrentRxQueue; DWORD dwProvSpec1; DWORD dwProvSpec2; WCHAR wcProvChar[1]; } COMMPROP, *PCOMMPROP, *LPCOMMPROP;
typedef struct tagCOMMTIMEOUTS { DWORD ReadIntervalTimeout; DWORD ReadTotalTimeoutMultiplier; DWORD ReadTotalTimeoutConstant; DWORD WriteTotalTimeoutMultiplier; DWORD WriteTotalTimeoutConstant; } COMMTIMEOUTS, *PCOMMTIMEOUTS, *LPCOMMTIMEOUTS;
typedef struct tagSYSTEM_POWER_STATUS_EX { BYTE ACLineStatus; BYTE BatteryFlag; BYTE BatteryLifePercent; BYTE Reserved1; DWORD BatteryLifeTime; DWORD BatteryFullLifeTime; BYTE Reserved2; BYTE BackupBatteryFlag; BYTE BackupBatteryLifePercent; BYTE Reserved3; DWORD BackupBatteryLifeTime; DWORD BackupBatteryFullLifeTime; } SYSTEM_POWER_STATUS_EX, *PSYSTEM_POWER_STATUS_EX, *LPSYSTEM_POWER_STATUS_EX;
typedef struct tagSYSTEM_POWER_STATUS_EX2 { BYTE ACLineStatus; BYTE BatteryFlag; BYTE BatteryLifePercent; BYTE Reserved1; DWORD BatteryLifeTime; DWORD BatteryFullLifeTime; BYTE Reserved2; BYTE BackupBatteryFlag; BYTE BackupBatteryLifePercent; BYTE Reserved3; DWORD BackupBatteryLifeTime; DWORD BackupBatteryFullLifeTime; DWORD BatteryVoltage; DWORD BatteryCurrent; DWORD BatteryAverageCurrent; DWORD BatteryAverageInterval; DWORD BatterymAHourConsumed; DWORD BatteryTemperature; DWORD BackupBatteryVoltage; BYTE BatteryChemistry; } SYSTEM_POWER_STATUS_EX2, *PSYSTEM_POWER_STATUS_EX2, *LPSYSTEM_POWER_STATUS_EX2;

WCE_IMPORT LONG WINAPI InterlockedIncrement(LONG volatile *lpAddend) WCE_LINK(InterlockedIncrement);
WCE_IMPORT LONG WINAPI InterlockedDecrement(LONG volatile *lpAddend) WCE_LINK(InterlockedDecrement);
WCE_IMPORT LONG WINAPI InterlockedExchange(LONG volatile *Target, LONG Value) WCE_LINK(InterlockedExchange);
WCE_IMPORT LONG WINAPI InterlockedCompareExchange(LONG volatile *Target, LONG Exchange, LONG Comperand) WCE_LINK(InterlockedCompareExchange);
WCE_IMPORT LONG WINAPI InterlockedExchangeAdd(LONG volatile *lpAddend, LONG Value) WCE_LINK(InterlockedExchangeAdd);
WCE_IMPORT DWORD WINAPI Random() WCE_LINK(Random);
WCE_IMPORT LONG WINAPI CompareFileTime(const FILETIME *lpft1, const FILETIME *lpft2) WCE_LINK(CompareFileTime);
WCE_IMPORT BOOL WINAPI FileTimeToSystemTime(const FILETIME *lpft, LPSYSTEMTIME lpst) WCE_LINK(FileTimeToSystemTime);
WCE_IMPORT BOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME *lpst, LPFILETIME lpft) WCE_LINK(SystemTimeToFileTime);
WCE_IMPORT BOOL WINAPI FileTimeToLocalFileTime(const FILETIME *lpft, LPFILETIME lpftLocal) WCE_LINK(FileTimeToLocalFileTime);
WCE_IMPORT BOOL WINAPI LocalFileTimeToFileTime(const FILETIME *lpftLocal, LPFILETIME lpft) WCE_LINK(LocalFileTimeToFileTime);
WCE_IMPORT BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved) WCE_LINK(DllMain);
WCE_IMPORT FARPROC WINAPI GetProcAddressW(HMODULE hModule, LPCWSTR lpProcName) WCE_LINK(GetProcAddressW);
WCE_IMPORT FARPROC WINAPI GetProcAddressA(HMODULE hModule, LPCSTR lpProcName) WCE_LINK(GetProcAddressA);
WCE_IMPORT FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName) WCE_LINK(GetProcAddress);
WCE_IMPORT int WINAPI MulDiv(IN int nNumber, IN int nNumerator, IN int nDenominator) WCE_LINK(MulDiv);
WCE_IMPORT VOID WINAPI GetLocalTime(LPSYSTEMTIME lpSystemTime) WCE_LINK(GetLocalTime);
WCE_IMPORT VOID WINAPI GetSystemTime(LPSYSTEMTIME lpSystemTime) WCE_LINK(GetSystemTime);
WCE_IMPORT VOID WINAPI GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime) WCE_LINK(GetSystemTimeAsFileTime);
WCE_IMPORT DWORD WINAPI GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation) WCE_LINK(GetTimeZoneInformation);
WCE_IMPORT BOOL WINAPI SetLocalTime(CONST SYSTEMTIME *lpSystemTime) WCE_LINK(SetLocalTime);
WCE_IMPORT BOOL WINAPI SetSystemTime(CONST SYSTEMTIME *lpSystemTime) WCE_LINK(SetSystemTime);
WCE_IMPORT void WINAPI SetDaylightTime(DWORD dst) WCE_LINK(SetDaylightTime);
WCE_IMPORT BOOL WINAPI SetTimeZoneInformation(CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation) WCE_LINK(SetTimeZoneInformation);
WCE_IMPORT LPSTR WINAPI lstrcatA(LPSTR lpString1, LPCSTR lpString2) WCE_LINK(lstrcatA);
WCE_IMPORT int WINAPI lstrcmpA(LPCSTR lpString1, LPCSTR lpString2) WCE_LINK(lstrcmpA);
WCE_IMPORT int WINAPI lstrcmpW(LPCWSTR lpString1, LPCWSTR lpString2) WCE_LINK(lstrcmpW);
WCE_IMPORT int WINAPI lstrcmpiA(LPCSTR lpString1, LPCSTR lpString2) WCE_LINK(lstrcmpiA);
WCE_IMPORT int WINAPI lstrcmpiW(LPCWSTR lpString1, LPCWSTR lpString2) WCE_LINK(lstrcmpiW);
WCE_IMPORT LPSTR WINAPI lstrcpyA(LPSTR lpString1, LPCSTR lpString2) WCE_LINK(lstrcpyA);
WCE_IMPORT int WINAPI lstrlenA(LPCSTR lpString) WCE_LINK(lstrlenA);
WCE_IMPORT DWORD WINAPI CharLowerBuffA(LPSTR lpsz, DWORD cchLength) WCE_LINK(CharLowerBuffA);
WCE_IMPORT DWORD WINAPI CharLowerBuffW(LPWSTR lpsz, DWORD cchLength) WCE_LINK(CharLowerBuffW);
WCE_IMPORT DWORD WINAPI CharUpperBuffA(LPSTR lpsz, DWORD cchLength) WCE_LINK(CharUpperBuffA);
WCE_IMPORT DWORD WINAPI CharUpperBuffW(LPWSTR lpsz, DWORD cchLength) WCE_LINK(CharUpperBuffW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LPSTR WINAPI CharLowerA(LPSTR lpsz) WCE_LINK(CharLowerA);
#endif
WCE_IMPORT LPWSTR WINAPI CharLowerW(LPWSTR lpsz) WCE_LINK(CharLowerW);
WCE_IMPORT LPSTR WINAPI CharUpperA(LPSTR lpsz) WCE_LINK(CharUpperA);
WCE_IMPORT LPWSTR WINAPI CharUpperW(LPWSTR lpsz) WCE_LINK(CharUpperW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LPSTR WINAPI CharPrevA(LPCSTR lpszStart, LPCSTR lpszCurrent) WCE_LINK(CharPrevA);
#endif
WCE_IMPORT LPWSTR WINAPI CharPrevW(LPCWSTR lpszStart, LPCWSTR lpszCurrent) WCE_LINK(CharPrevW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT LPSTR WINAPI CharNextA(LPCSTR lpsz) WCE_LINK(CharNextA);
#endif
WCE_IMPORT LPWSTR WINAPI CharNextW(LPCWSTR lpsz) WCE_LINK(CharNextW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPIV wsprintfA(LPSTR, LPCSTR, ...) WCE_LINK(wsprintfA);
#endif
WCE_IMPORT int WINAPIV wsprintfW(LPWSTR, LPCWSTR, ...) WCE_LINK(wsprintfW);
WCE_IMPORT VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer) WCE_LINK(GlobalMemoryStatus);
WCE_IMPORT LPVOID WINAPI LocalLock(HLOCAL hMem) WCE_LINK(LocalLock);
WCE_IMPORT BOOL WINAPI LocalUnlock(HLOCAL hMem) WCE_LINK(LocalUnlock);
WCE_IMPORT HLOCAL WINAPI LocalHandle(LPCVOID pMem) WCE_LINK(LocalHandle);
WCE_IMPORT UINT WINAPI LocalFlags(HLOCAL hMem) WCE_LINK(LocalFlags);
WCE_IMPORT HLOCAL WINAPI LocalAlloc(UINT fuFlags, UINT cbBytes) WCE_LINK(LocalAlloc);
WCE_IMPORT HLOCAL WINAPI LocalAllocTrace(UINT fuFlags, UINT cbBytes, UINT cLineNum, LPCWSTR szFilename) WCE_LINK(LocalAllocTrace);
WCE_IMPORT HLOCAL WINAPI LocalFree(HLOCAL hMem) WCE_LINK(LocalFree);
WCE_IMPORT HLOCAL WINAPI LocalReAlloc(HLOCAL hMem, UINT cbBytes, UINT fuFlags) WCE_LINK(LocalReAlloc);
WCE_IMPORT UINT WINAPI LocalSize(HLOCAL hMem) WCE_LINK(LocalSize);
WCE_IMPORT LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect) WCE_LINK(VirtualAlloc);
WCE_IMPORT BOOL WINAPI VirtualFree(LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType) WCE_LINK(VirtualFree);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT LPVOID WINAPI VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect) WCE_LINK(VirtualAllocEx);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI VirtualFreeEx(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType) WCE_LINK(VirtualFreeEx);
#endif
WCE_IMPORT BOOL WINAPI VirtualProtect(LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) WCE_LINK(VirtualProtect);
WCE_IMPORT DWORD WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, DWORD dwLength) WCE_LINK(VirtualQuery);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI VirtualProtectEx(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) WCE_LINK(VirtualProtectEx);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI VirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, DWORD dwLength) WCE_LINK(VirtualQueryEx);
#endif
WCE_IMPORT HANDLE WINAPI GetProcessHeap(VOID) WCE_LINK(GetProcessHeap);
WCE_IMPORT HANDLE WINAPI HeapCreate(DWORD flOptions, DWORD dwInitialSize, DWORD dwMaximumSize) WCE_LINK(HeapCreate);
WCE_IMPORT BOOL WINAPI HeapDestroy(HANDLE hHeap) WCE_LINK(HeapDestroy);
WCE_IMPORT LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, DWORD dwBytes) WCE_LINK(HeapAlloc);
WCE_IMPORT LPVOID WINAPI HeapAllocTrace(HANDLE hHeap, DWORD dwFlags, DWORD dwBytes, DWORD dwLineNum, PCHAR szFilename) WCE_LINK(HeapAllocTrace);
WCE_IMPORT LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, DWORD dwBytes) WCE_LINK(HeapReAlloc);
WCE_IMPORT BOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) WCE_LINK(HeapFree);
WCE_IMPORT DWORD WINAPI HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) WCE_LINK(HeapSize);
WCE_IMPORT BOOL WINAPI HeapValidate(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) WCE_LINK(HeapValidate);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT UINT WINAPI HeapCompact(HANDLE hHeap, DWORD dwFlags) WCE_LINK(HeapCompact);
#endif
WCE_IMPORT HANDLE WINAPI CeHeapCreate(DWORD flOptions, DWORD dwInitialSize, DWORD dwMaximumSize, PFN_AllocHeapMem pfnAlloc, PFN_FreeHeapMem pfnFree) WCE_LINK(CeHeapCreate);
WCE_IMPORT VOID WINAPI OutputDebugStringA(LPCSTR lpOutputString) WCE_LINK(OutputDebugStringA);
WCE_IMPORT VOID WINAPI OutputDebugStringW(LPCWSTR lpOutputString) WCE_LINK(OutputDebugStringW);
WCE_IMPORT VOID WINAPI DebugBreak(VOID) WCE_LINK(DebugBreak);
WCE_IMPORT BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount) WCE_LINK(QueryPerformanceCounter);
WCE_IMPORT BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency) WCE_LINK(QueryPerformanceFrequency);
WCE_IMPORT BOOL WINAPI GetVersionExA(LPOSVERSIONINFOA lpVersionInformation) WCE_LINK(GetVersionExA);
WCE_IMPORT BOOL WINAPI GetVersionExW(LPOSVERSIONINFOW lpVersionInformation) WCE_LINK(GetVersionExW);
WCE_IMPORT HINSTANCE WINAPI LoadLibraryA(LPCSTR lpLibFileName) WCE_LINK(LoadLibraryA);
WCE_IMPORT HINSTANCE WINAPI LoadLibraryW(LPCWSTR lpLibFileName) WCE_LINK(LoadLibraryW);
WCE_IMPORT HMODULE WINAPI LoadLibraryExA(IN LPCSTR lpLibFileName, IN HANDLE hFile, IN DWORD dwFlags) WCE_LINK(LoadLibraryExA);
WCE_IMPORT HMODULE WINAPI LoadLibraryExW(IN LPCWSTR lpLibFileName, IN HANDLE hFile, IN DWORD dwFlags) WCE_LINK(LoadLibraryExW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) WCE_LINK(GetModuleFileNameA);
#endif
WCE_IMPORT DWORD WINAPI GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize) WCE_LINK(GetModuleFileNameW);
WCE_IMPORT HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName) WCE_LINK(GetModuleHandleA);
WCE_IMPORT HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName) WCE_LINK(GetModuleHandleW);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT PVOID WINAPI AddVectoredExceptionHandler(IN ULONG FirstHandler, IN PVECTORED_EXCEPTION_HANDLER VectoredHandler) WCE_LINK(AddVectoredExceptionHandler);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT ULONG WINAPI RemoveVectoredExceptionHandler(IN PVOID VectoredHandlerHandle) WCE_LINK(RemoveVectoredExceptionHandler);
#endif
WCE_IMPORT VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION pcsCriticalSection) WCE_LINK(EnterCriticalSection);
WCE_IMPORT VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION pcsCriticalSection) WCE_LINK(LeaveCriticalSection);
WCE_IMPORT VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION pcsCriticalSection) WCE_LINK(InitializeCriticalSection);
WCE_IMPORT BOOL WINAPI TryEnterCriticalSection(IN OUT LPCRITICAL_SECTION lpCriticalSection) WCE_LINK(TryEnterCriticalSection);
WCE_IMPORT VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION pcsCriticalSection) WCE_LINK(DeleteCriticalSection);
WCE_IMPORT BOOL WINAPI WaitForDebugEvent(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds) WCE_LINK(WaitForDebugEvent);
WCE_IMPORT BOOL WINAPI ContinueDebugEvent(DWORD dwProcessId, DWORD dwThreadId, DWORD dwContinueStatus) WCE_LINK(ContinueDebugEvent);
WCE_IMPORT BOOL WINAPI DebugActiveProcess(DWORD dwProcessId) WCE_LINK(DebugActiveProcess);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DebugActiveProcessStop(DWORD dwProcessId) WCE_LINK(DebugActiveProcessStop);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DebugSetProcessKillOnExit(BOOL KillOnExit) WCE_LINK(DebugSetProcessKillOnExit);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI CheckRemoteDebuggerPresent(HANDLE hProcess, PBOOL pbDebuggerPresent) WCE_LINK(CheckRemoteDebuggerPresent);
#endif
WCE_IMPORT LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, DWORD dwNumberOfBytesToMap) WCE_LINK(MapViewOfFile);
WCE_IMPORT BOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress) WCE_LINK(UnmapViewOfFile);
WCE_IMPORT BOOL WINAPI FlushViewOfFile(LPCVOID lpBaseAddress, DWORD dwNumberOfBytesToFlush) WCE_LINK(FlushViewOfFile);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName) WCE_LINK(CreateFileMappingA);
#endif
WCE_IMPORT HANDLE WINAPI CreateFileMappingW(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName) WCE_LINK(CreateFileMappingW);
WCE_IMPORT HANDLE WINAPI CreateFileForMappingW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) WCE_LINK(CreateFileForMappingW);
WCE_IMPORT DWORD WINAPI GetTempPathA(DWORD nBufferLength, LPSTR lpBuffer) WCE_LINK(GetTempPathA);
WCE_IMPORT DWORD WINAPI GetTempPathW(DWORD nBufferLength, LPWSTR lpBuffer) WCE_LINK(GetTempPathW);
WCE_IMPORT HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, LPTHREAD_START_ROUTINE lpStartAddr, LPVOID lpvThreadParam, DWORD fdwCreate, LPDWORD lpIDThread) WCE_LINK(CreateThread);
WCE_IMPORT VOID WINAPI ExitThread(DWORD dwExitCode) WCE_LINK(ExitThread);
WCE_IMPORT BOOL WINAPI TerminateThread(HANDLE hThread, DWORD dwExitCode) WCE_LINK(TerminateThread);
WCE_IMPORT LPVOID WINAPI ConvertThreadToFiber(LPVOID lpParameter) WCE_LINK(ConvertThreadToFiber);
WCE_IMPORT LPVOID WINAPI CreateFiber(DWORD dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter) WCE_LINK(CreateFiber);
WCE_IMPORT VOID WINAPI DeleteFiber(LPVOID lpFiber) WCE_LINK(DeleteFiber);
WCE_IMPORT LPVOID WINAPI GetFiberData(VOID) WCE_LINK(GetFiberData);
WCE_IMPORT VOID WINAPI SwitchToFiber(LPVOID lpFiber) WCE_LINK(SwitchToFiber);
WCE_IMPORT LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex) WCE_LINK(TlsGetValue);
WCE_IMPORT BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpvTlsValue) WCE_LINK(TlsSetValue);
WCE_IMPORT BOOL WINAPI CreateProcessA(LPCSTR pszImageName, LPCSTR pszCmdLine, LPSECURITY_ATTRIBUTES psaProcess, LPSECURITY_ATTRIBUTES psaThread, BOOL fInheritHandles, DWORD fdwCreate, LPVOID pvEnvironment, LPSTR pszCurDir, LPSTARTUPINFO psiStartInfo, LPPROCESS_INFORMATION pProcInfo) WCE_LINK(CreateProcessA);
WCE_IMPORT BOOL WINAPI CreateProcessW(LPCWSTR pszImageName, LPCWSTR pszCmdLine, LPSECURITY_ATTRIBUTES psaProcess, LPSECURITY_ATTRIBUTES psaThread, BOOL fInheritHandles, DWORD fdwCreate, LPVOID pvEnvironment, LPWSTR pszCurDir, LPSTARTUPINFO psiStartInfo, LPPROCESS_INFORMATION pProcInfo) WCE_LINK(CreateProcessW);
WCE_IMPORT DWORD WINAPI GetProcessVersion(DWORD ProcessId) WCE_LINK(GetProcessVersion);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI GetProcessId(HANDLE hProcess) WCE_LINK(GetProcessId);
#endif
WCE_IMPORT LPSTR WINAPI GetCommandLineA(VOID) WCE_LINK(GetCommandLineA);
WCE_IMPORT LPWSTR WINAPI GetCommandLineW(VOID) WCE_LINK(GetCommandLineW);
WCE_IMPORT DWORD WINAPI GetLastError(VOID) WCE_LINK(GetLastError);
WCE_IMPORT DWORD WINAPI GetTickCount(VOID) WCE_LINK(GetTickCount);
WCE_IMPORT DWORD WINAPI GetIdleTime(VOID) WCE_LINK(GetIdleTime);
WCE_IMPORT BOOL WINAPI CloseHandle(HANDLE hObject) WCE_LINK(CloseHandle);
WCE_IMPORT BOOL WINAPI DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions) WCE_LINK(DuplicateHandle);
WCE_IMPORT HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo) WCE_LINK(LoadResource);
WCE_IMPORT DWORD WINAPI SizeofResource(HMODULE hModule, HRSRC hResInfo) WCE_LINK(SizeofResource);
WCE_IMPORT HRSRC WINAPI FindResourceA(HMODULE hModule, LPCSTR lpName, LPCSTR lpType) WCE_LINK(FindResourceA);
WCE_IMPORT HRSRC WINAPI FindResourceW(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType) WCE_LINK(FindResourceW);
WCE_IMPORT int WINAPI LoadStringA(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int nBufferMax) WCE_LINK(LoadStringA);
WCE_IMPORT int WINAPI LoadStringW(HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int nBufferMax) WCE_LINK(LoadStringW);
WCE_IMPORT LPVOID WINAPI LockResource(HGLOBAL hResData) WCE_LINK(LockResource);
WCE_IMPORT ATOM WINAPI GlobalAddAtomA(LPCSTR lpString) WCE_LINK(GlobalAddAtomA);
WCE_IMPORT ATOM WINAPI GlobalAddAtomW(LPCWSTR lpString) WCE_LINK(GlobalAddAtomW);
WCE_IMPORT ATOM WINAPI GlobalFindAtomA(LPCSTR lpString) WCE_LINK(GlobalFindAtomA);
WCE_IMPORT ATOM WINAPI GlobalFindAtomW(LPCWSTR lpString) WCE_LINK(GlobalFindAtomW);
WCE_IMPORT ATOM WINAPI GlobalDeleteAtom(ATOM nAtom) WCE_LINK(GlobalDeleteAtom);
WCE_IMPORT BOOL WINAPI TerminateProcess(HANDLE hProcess, DWORD uExitCode) WCE_LINK(TerminateProcess);
WCE_IMPORT BOOL WINAPI FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, DWORD dwSize) WCE_LINK(FlushInstructionCache);
WCE_IMPORT BOOL WINAPI ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead) WCE_LINK(ReadProcessMemory);
WCE_IMPORT BOOL WINAPI WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesWritten) WCE_LINK(WriteProcessMemory);
WCE_IMPORT HANDLE WINAPI OpenProcess(DWORD fdwAccess, BOOL fInherit, DWORD IDProcess) WCE_LINK(OpenProcess);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI OpenThread(DWORD fdwAccess, BOOL fInherit, DWORD IDThread) WCE_LINK(OpenThread);
#endif
WCE_IMPORT BOOL WINAPI GetThreadContext(HANDLE hThread, LPCONTEXT lpContext) WCE_LINK(GetThreadContext);
WCE_IMPORT BOOL WINAPI SetThreadContext(HANDLE hThread, CONST CONTEXT *lpContext) WCE_LINK(SetThreadContext);
WCE_IMPORT DWORD WINAPI SuspendThread(HANDLE hThread) WCE_LINK(SuspendThread);
WCE_IMPORT DWORD WINAPI ResumeThread(HANDLE hThread) WCE_LINK(ResumeThread);
WCE_IMPORT BOOL WINAPI GetThreadTimes(HANDLE hThread, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime) WCE_LINK(GetThreadTimes);
WCE_IMPORT int WINAPI GetThreadPriority(HANDLE hThread) WCE_LINK(GetThreadPriority);
WCE_IMPORT BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority) WCE_LINK(SetThreadPriority);
WCE_IMPORT int WINAPI CeGetThreadPriority(HANDLE hThread) WCE_LINK(CeGetThreadPriority);
WCE_IMPORT BOOL WINAPI CeSetThreadPriority(HANDLE hThread, int nPriority) WCE_LINK(CeSetThreadPriority);
WCE_IMPORT DWORD WINAPI CeGetThreadQuantum(HANDLE hThread) WCE_LINK(CeGetThreadQuantum);
WCE_IMPORT BOOL WINAPI CeSetThreadQuantum(HANDLE hThread, DWORD dwTime) WCE_LINK(CeSetThreadQuantum);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI GetThreadId(HANDLE hThread) WCE_LINK(GetThreadId);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI GetProcessIdOfThread(HANDLE hThread) WCE_LINK(GetProcessIdOfThread);
#endif
WCE_IMPORT LPVOID WINAPI CeZeroPointer(LPVOID ptr) WCE_LINK(CeZeroPointer);
WCE_IMPORT VOID WINAPI SetLastError(DWORD dwErrCode) WCE_LINK(SetLastError);
WCE_IMPORT UINT WINAPI GetTempFileNameA(IN LPCSTR lpPathName, IN LPCSTR lpPrefixString, IN UINT uUnique, LPSTR lpTempFileName) WCE_LINK(GetTempFileNameA);
WCE_IMPORT UINT WINAPI GetTempFileNameW(IN LPCWSTR lpPathName, IN LPCWSTR lpPrefixString, IN UINT uUnique, LPWSTR lpTempFileName) WCE_LINK(GetTempFileNameW);
WCE_IMPORT DWORD WINAPI CeGetCanonicalPathNameA(IN LPCSTR lpPathName, LPSTR lpCanonicalPathName, IN DWORD cchCanonicalPathName, IN DWORD dwReserved) WCE_LINK(CeGetCanonicalPathNameA);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI CeGetCanonicalPathNameW(IN LPCWSTR lpPathName, LPWSTR lpCanonicalPathName, IN DWORD cchCanonicalPathName, IN DWORD dwReserved) WCE_LINK(CeGetCanonicalPathNameW);
#endif
WCE_IMPORT HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) WCE_LINK(CreateFileA);
WCE_IMPORT HANDLE WINAPI CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) WCE_LINK(CreateFileW);
WCE_IMPORT BOOL WINAPI DeleteFileA(LPCSTR lpFileName) WCE_LINK(DeleteFileA);
WCE_IMPORT BOOL WINAPI DeleteFileW(LPCWSTR lpFileName) WCE_LINK(DeleteFileW);
WCE_IMPORT BOOL WINAPI DeleteAndRenameFile(LPCWSTR lpOldFileName, LPCWSTR lpNewFileName) WCE_LINK(DeleteAndRenameFile);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) WCE_LINK(FindFirstFileA);
#endif
WCE_IMPORT HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) WCE_LINK(FindFirstFileW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) WCE_LINK(FindNextFileA);
#endif
WCE_IMPORT BOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) WCE_LINK(FindNextFileW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists) WCE_LINK(CopyFileA);
#endif
WCE_IMPORT BOOL WINAPI CopyFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists) WCE_LINK(CopyFileW);
WCE_IMPORT BOOL WINAPI CopyFileExA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags) WCE_LINK(CopyFileExA);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CopyFileExW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags) WCE_LINK(CopyFileExW);
#endif
WCE_IMPORT BOOL WINAPI MoveFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName) WCE_LINK(MoveFileA);
WCE_IMPORT BOOL WINAPI MoveFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName) WCE_LINK(MoveFileW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) WCE_LINK(CreateDirectoryA);
#endif
WCE_IMPORT BOOL WINAPI CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) WCE_LINK(CreateDirectoryW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI RemoveDirectoryA(LPCSTR lpPathName) WCE_LINK(RemoveDirectoryA);
#endif
WCE_IMPORT BOOL WINAPI RemoveDirectoryW(LPCWSTR lpPathName) WCE_LINK(RemoveDirectoryW);
WCE_IMPORT BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) WCE_LINK(WriteFile);
WCE_IMPORT BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) WCE_LINK(ReadFile);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI LockFileEx(HANDLE hFile, DWORD dwFlags, DWORD dwReserved, DWORD nNumberOfBytesToLockLow, DWORD nNumberOfBytesToLockHigh, LPOVERLAPPED lpOverlapped) WCE_LINK(LockFileEx);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI UnlockFileEx(HANDLE hFile, DWORD dwReserved, DWORD nNumberOfBytesToUnlockLow, DWORD nNumberOfBytesToUnlockHigh, LPOVERLAPPED lpOverlapped) WCE_LINK(UnlockFileEx);
#endif
WCE_IMPORT BOOL WINAPI FlushFileBuffers(HANDLE hFile) WCE_LINK(FlushFileBuffers);
WCE_IMPORT BOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreation, LPFILETIME lpLastAccess, LPFILETIME lpLastWrite) WCE_LINK(GetFileTime);
WCE_IMPORT BOOL WINAPI SetFileTime(HANDLE hFile, CONST FILETIME *lpCreation, CONST FILETIME *lpLastAccess, CONST FILETIME *lpLastWrite) WCE_LINK(SetFileTime);
WCE_IMPORT BOOL WINAPI SetEndOfFile(HANDLE hFile) WCE_LINK(SetEndOfFile);
WCE_IMPORT BOOL WINAPI DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) WCE_LINK(DeviceIoControl);
WCE_IMPORT HANDLE WINAPI FindFirstChangeNotificationA(IN LPCSTR lpPathName, IN BOOL bWatchSubtree, IN DWORD dwNotifyFilter) WCE_LINK(FindFirstChangeNotificationA);
WCE_IMPORT HANDLE WINAPI FindFirstChangeNotificationW(IN LPCWSTR lpPathName, IN BOOL bWatchSubtree, IN DWORD dwNotifyFilter) WCE_LINK(FindFirstChangeNotificationW);
WCE_IMPORT BOOL WINAPI FindNextChangeNotification(IN HANDLE hChangeHandle) WCE_LINK(FindNextChangeNotification);
WCE_IMPORT BOOL WINAPI CeGetFileNotificationInfo(HANDLE hChangeHandle, DWORD dwFlags, LPVOID lpBuffer, DWORD nBufferLength, LPDWORD lpBytesReturned, LPDWORD lpBytesAvailable) WCE_LINK(CeGetFileNotificationInfo);
WCE_IMPORT BOOL WINAPI FindCloseChangeNotification(IN HANDLE hChangeHandle) WCE_LINK(FindCloseChangeNotification);
WCE_IMPORT BOOL WINAPI GetOverlappedResult(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait) WCE_LINK(GetOverlappedResult);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT BOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) WCE_LINK(SetFileAttributesA);
#endif
WCE_IMPORT BOOL WINAPI SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes) WCE_LINK(SetFileAttributesW);
WCE_IMPORT DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) WCE_LINK(SetFilePointer);
WCE_IMPORT BOOL WINAPI FindClose(HANDLE hFindFile) WCE_LINK(FindClose);
WCE_IMPORT DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh) WCE_LINK(GetFileSize);
WCE_IMPORT DWORD WINAPI GetFileAttributesA(LPCSTR lpFileName) WCE_LINK(GetFileAttributesA);
WCE_IMPORT DWORD WINAPI GetFileAttributesW(LPCWSTR lpFileName) WCE_LINK(GetFileAttributesW);
WCE_IMPORT BOOL WINAPI GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation) WCE_LINK(GetFileInformationByHandle);
WCE_IMPORT VOID WINAPI Sleep(DWORD dwMilliseconds) WCE_LINK(Sleep);
WCE_IMPORT HANDLE WINAPI CreateMutexA(LPSECURITY_ATTRIBUTES lpsa, BOOL bInitialOwner, LPCSTR lpName) WCE_LINK(CreateMutexA);
WCE_IMPORT HANDLE WINAPI CreateMutexW(LPSECURITY_ATTRIBUTES lpsa, BOOL bInitialOwner, LPCWSTR lpName) WCE_LINK(CreateMutexW);
WCE_IMPORT HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName) WCE_LINK(CreateEventA);
WCE_IMPORT HANDLE WINAPI CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName) WCE_LINK(CreateEventW);
WCE_IMPORT HANDLE WINAPI OpenEventA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) WCE_LINK(OpenEventA);
WCE_IMPORT HANDLE WINAPI OpenEventW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName) WCE_LINK(OpenEventW);
WCE_IMPORT HANDLE WINAPI CreateSemaphoreA(IN LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, IN LONG lInitialCount, IN LONG lMaximumCount, IN LPCSTR lpName) WCE_LINK(CreateSemaphoreA);
WCE_IMPORT HANDLE WINAPI CreateSemaphoreW(IN LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, IN LONG lInitialCount, IN LONG lMaximumCount, IN LPCWSTR lpName) WCE_LINK(CreateSemaphoreW);
WCE_IMPORT BOOL WINAPI SetEvent(HANDLE hEvent) WCE_LINK(SetEvent);
WCE_IMPORT BOOL WINAPI ResetEvent(HANDLE hEvent) WCE_LINK(ResetEvent);
WCE_IMPORT BOOL WINAPI PulseEvent(HANDLE hEvent) WCE_LINK(PulseEvent);
WCE_IMPORT BOOL WINAPI ReleaseSemaphore(IN HANDLE hSemaphore, IN LONG lReleaseCount, OUT LPLONG lpPreviousCount) WCE_LINK(ReleaseSemaphore);
WCE_IMPORT BOOL WINAPI ReleaseMutex(HANDLE hMutex) WCE_LINK(ReleaseMutex);
WCE_IMPORT DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) WCE_LINK(WaitForSingleObject);
WCE_IMPORT DWORD WINAPI WaitForMultipleObjects(DWORD cObjects, CONST HANDLE *lphObjects, BOOL fWaitAll, DWORD dwTimeout) WCE_LINK(WaitForMultipleObjects);
WCE_IMPORT BOOL WINAPI GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode) WCE_LINK(GetExitCodeThread);
WCE_IMPORT BOOL WINAPI GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode) WCE_LINK(GetExitCodeProcess);
WCE_IMPORT HANDLE WINAPI GetCurrentThread(VOID) WCE_LINK(GetCurrentThread);
WCE_IMPORT HANDLE WINAPI GetCurrentProcess(VOID) WCE_LINK(GetCurrentProcess);
WCE_IMPORT DWORD WINAPI GetCurrentThreadId(VOID) WCE_LINK(GetCurrentThreadId);
WCE_IMPORT DWORD WINAPI GetCurrentProcessId(VOID) WCE_LINK(GetCurrentProcessId);
WCE_IMPORT DWORD WINAPI TlsAlloc(VOID) WCE_LINK(TlsAlloc);
WCE_IMPORT BOOL WINAPI IsBadCodePtr(FARPROC lpfn) WCE_LINK(IsBadCodePtr);
WCE_IMPORT BOOL WINAPI IsBadReadPtr(CONST VOID *lp, UINT ucb) WCE_LINK(IsBadReadPtr);
WCE_IMPORT BOOL WINAPI TlsFree(DWORD dwTlsIndex) WCE_LINK(TlsFree);
WCE_IMPORT BOOL WINAPI IsBadWritePtr(LPVOID lp, UINT ucb) WCE_LINK(IsBadWritePtr);
WCE_IMPORT VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) WCE_LINK(GetSystemInfo);
WCE_IMPORT BOOL WINAPI QueryInstructionSet(DWORD dwInstructionSet, LPDWORD lpdwCurrentInstructionSet) WCE_LINK(QueryInstructionSet);
WCE_IMPORT BOOL WINAPI IsProcessorFeaturePresent(DWORD dwProcessorFeature) WCE_LINK(IsProcessorFeaturePresent);
WCE_IMPORT VOID WINAPI RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, CONST DWORD *lpArguments) WCE_LINK(RaiseException);
WCE_IMPORT BOOL WINAPI FreeLibrary(HMODULE hLibModule) WCE_LINK(FreeLibrary);
WCE_IMPORT VOID WINAPI FreeLibraryAndExitThread(HMODULE hLibModule, DWORD dwExitCode) WCE_LINK(FreeLibraryAndExitThread);
WCE_IMPORT BOOL WINAPI DisableThreadLibraryCalls(IN HMODULE hLibModule) WCE_LINK(DisableThreadLibraryCalls);
WCE_IMPORT BOOL WINAPI ClearCommBreak(HANDLE hFile) WCE_LINK(ClearCommBreak);
WCE_IMPORT BOOL WINAPI ClearCommError(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat) WCE_LINK(ClearCommError);
WCE_IMPORT BOOL WINAPI SetupComm(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue) WCE_LINK(SetupComm);
WCE_IMPORT BOOL WINAPI EscapeCommFunction(HANDLE hFile, DWORD dwFunc) WCE_LINK(EscapeCommFunction);
WCE_IMPORT BOOL WINAPI GetCommMask(HANDLE hFile, LPDWORD lpEvtMask) WCE_LINK(GetCommMask);
WCE_IMPORT BOOL WINAPI GetCommProperties(HANDLE hFile, LPCOMMPROP lpCommProp) WCE_LINK(GetCommProperties);
WCE_IMPORT BOOL WINAPI GetCommModemStatus(HANDLE hFile, LPDWORD lpModemStat) WCE_LINK(GetCommModemStatus);
WCE_IMPORT BOOL WINAPI GetCommState(HANDLE hFile, LPDCB lpDCB) WCE_LINK(GetCommState);
WCE_IMPORT BOOL WINAPI GetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts) WCE_LINK(GetCommTimeouts);
WCE_IMPORT BOOL WINAPI PurgeComm(HANDLE hFile, DWORD dwFlags) WCE_LINK(PurgeComm);
WCE_IMPORT BOOL WINAPI SetCommBreak(HANDLE hFile) WCE_LINK(SetCommBreak);
WCE_IMPORT BOOL WINAPI SetCommMask(HANDLE hFile, DWORD dwEvtMask) WCE_LINK(SetCommMask);
WCE_IMPORT BOOL WINAPI SetCommState(HANDLE hFile, LPDCB lpDCB) WCE_LINK(SetCommState);
WCE_IMPORT BOOL WINAPI SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts) WCE_LINK(SetCommTimeouts);
WCE_IMPORT BOOL WINAPI TransmitCommChar(HANDLE hFile, char cChar) WCE_LINK(TransmitCommChar);
WCE_IMPORT BOOL WINAPI WaitCommEvent(HANDLE hFile, LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped) WCE_LINK(WaitCommEvent);
WCE_IMPORT BOOL WINAPI GetSystemPowerStatusEx(PSYSTEM_POWER_STATUS_EX pSystemPowerStatusEx, BOOL fUpdate) WCE_LINK(GetSystemPowerStatusEx);
WCE_IMPORT DWORD WINAPI GetSystemPowerStatusEx2(PSYSTEM_POWER_STATUS_EX2 pSystemPowerStatusEx2, DWORD dwLen, BOOL fUpdate) WCE_LINK(GetSystemPowerStatusEx2);
WCE_IMPORT void WINAPI BatteryNotifyOfTimeChange(BOOL fForward, FILETIME *pftDelta) WCE_LINK(BatteryNotifyOfTimeChange);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ReportEventW(HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCWSTR* lpStrings, LPVOID lpRawData) WCE_LINK(ReportEventW);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI RegisterEventSourceW(LPCWSTR lpUNCServerName, LPCWSTR lpSourceName) WCE_LINK(RegisterEventSourceW);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI DeregisterEventSource(HANDLE hEventLog) WCE_LINK(DeregisterEventSource);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ClearEventLogW(HANDLE hEventLog, LPCWSTR lpBackupFileName) WCE_LINK(ClearEventLogW);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI OpenEventLogW(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName) WCE_LINK(OpenEventLogW);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CloseEventLog(HANDLE hEventLog) WCE_LINK(CloseEventLog);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI BackupEventLogW(HANDLE hEventLog, LPCTSTR szBackupFileName) WCE_LINK(BackupEventLogW);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI LockEventLog(HANDLE hEventLog) WCE_LINK(LockEventLog);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI UnLockEventLog(HANDLE hEventLog) WCE_LINK(UnLockEventLog);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ReadEventLogRaw(HANDLE hEventLog, BYTE *pReadBuffer, DWORD dwReadBufferSize, DWORD *pdwBytesRead) WCE_LINK(ReadEventLogRaw);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT DWORD WINAPI CeCertVerify(HANDLE hFile, HANDLE * phHandle, LPCWSTR pszFileName, LPWSTR pszAccountName, DWORD cbAccountNameSize, DWORD dwFlags) WCE_LINK(CeCertVerify);
#endif
WCE_IMPORT VOID WINAPI GetCurrentFT(LPFILETIME lpFileTime) WCE_LINK(GetCurrentFT);
WCE_IMPORT VOID WINAPI SignalStarted(DWORD dw) WCE_LINK(SignalStarted);
WCE_IMPORT LPVOID WINAPI GetCurrentFiber(VOID) WCE_LINK(GetCurrentFiber);
WCE_IMPORT BOOL WINAPI GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes) WCE_LINK(GetDiskFreeSpaceExW);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeFsIoControlW(IN LPCWSTR pszRootPath, IN DWORD dwIoctl, IN LPVOID lpInBuf, IN DWORD nInBufSize, OUT LPVOID lpOutBuf, IN DWORD nOutBufSize, OUT LPDWORD lpBytesReturned, IN LPOVERLAPPED lpOverlapped) WCE_LINK(CeFsIoControlW);
#endif
WCE_IMPORT BOOL WINAPI CheckPassword(LPWSTR lpszPassword) WCE_LINK(CheckPassword);
WCE_IMPORT HANDLE WINAPI RegisterDevice(LPCWSTR lpszName, DWORD index, LPCWSTR lpszLib, DWORD dwInfo) WCE_LINK(RegisterDevice);
WCE_IMPORT BOOL WINAPI DeregisterDevice(HANDLE hDevice) WCE_LINK(DeregisterDevice);
WCE_IMPORT BOOL WINAPI LoadFSD(HANDLE hDevice, LPCWSTR lpFSDName) WCE_LINK(LoadFSD);
WCE_IMPORT BOOL WINAPI LoadFSDEx(HANDLE hDevice, LPCWSTR lpFSDName, DWORD dwFlag) WCE_LINK(LoadFSDEx);
WCE_IMPORT HANDLE WINAPI ActivateDevice(LPCWSTR lpszDevKey,DWORD dwClientInfo) WCE_LINK(ActivateDevice);
WCE_IMPORT HANDLE WINAPI ActivateDeviceEx(LPCWSTR lpszDevKey, LPCVOID lpRegEnts, DWORD cRegEnts, LPVOID lpvParam) WCE_LINK(ActivateDeviceEx);
WCE_IMPORT BOOL WINAPI DeactivateDevice(HANDLE hDevice) WCE_LINK(DeactivateDevice);
WCE_IMPORT BOOL WINAPI CeResyncFilesys(HANDLE hDevice) WCE_LINK(CeResyncFilesys);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI GetDeviceInformationByDeviceHandle(HANDLE hDevice, PDEVMGR_DEVICE_INFORMATION pdi) WCE_LINK(GetDeviceInformationByDeviceHandle);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI GetDeviceInformationByFileHandle(HANDLE hFile, PDEVMGR_DEVICE_INFORMATION pdi) WCE_LINK(GetDeviceInformationByFileHandle);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI FindNextDevice(HANDLE h, PDEVMGR_DEVICE_INFORMATION pdi) WCE_LINK(FindNextDevice);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI EnumDeviceInterfaces(HANDLE h, DWORD dwIndex, GUID *pClass, LPWSTR pszNameBuf, LPDWORD lpdwNameBufSize) WCE_LINK(EnumDeviceInterfaces);
#endif
WCE_IMPORT HKEY WINAPI RegOpenProcessKey(DWORD hPnp) WCE_LINK(RegOpenProcessKey);
WCE_IMPORT BOOL WINAPI CeGenRandom(DWORD dwLen, PBYTE pbBuffer) WCE_LINK(CeGenRandom);
WCE_IMPORT BOOL WINAPI ResourceCreateList(DWORD dwResId, DWORD dwMinimum, DWORD dwCount) WCE_LINK(ResourceCreateList);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ResourceDestroyList(DWORD dwResId) WCE_LINK(ResourceDestroyList);
#endif
WCE_IMPORT BOOL WINAPI ResourceRequest(DWORD dwResId, DWORD dwId, DWORD dwLen) WCE_LINK(ResourceRequest);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ResourceRequestEx(DWORD dwResId, DWORD dwId, DWORD dwLen, DWORD dwFlags) WCE_LINK(ResourceRequestEx);
#endif
WCE_IMPORT BOOL WINAPI ResourceRelease(DWORD dwResId, DWORD dwId, DWORD dwLen) WCE_LINK(ResourceRelease);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ResourceMarkAsShareable(DWORD dwResId, DWORD dwId, DWORD dwLen, BOOL fShareable) WCE_LINK(ResourceMarkAsShareable);
#endif
WCE_IMPORT HANDLE WINAPI RequestDeviceNotifications(const GUID *devclass, HANDLE hMsgQ, BOOL fAll) WCE_LINK(RequestDeviceNotifications);
WCE_IMPORT BOOL WINAPI StopDeviceNotifications(HANDLE h) WCE_LINK(StopDeviceNotifications);
WCE_IMPORT BOOL WINAPI AdvertiseInterface(const GUID *devclass, LPCWSTR name, BOOL fAdd) WCE_LINK(AdvertiseInterface);

#define GetProcAddress GetProcAddressW
#define lstrcmp lstrcmpW
#define lstrcmpi lstrcmpiW
#define CharLowerBuff CharLowerBuffW
#define CharUpperBuff CharUpperBuffW
#define CharLower CharLowerW
#define CharUpper CharUpperW
#define CharPrev CharPrevW
#define CharNext CharNextW
#define wsprintf wsprintfW
#define OutputDebugString OutputDebugStringW
#define LoadLibrary LoadLibraryW
#define LoadLibraryEx LoadLibraryExW
#define GetModuleFileName GetModuleFileNameW
#define GetModuleHandle GetModuleHandleW
#define CreateFileMapping CreateFileMappingW
#define GetTempPath GetTempPathW
#define CreateProcess CreateProcessW
#define GetCommandLine GetCommandLineW
#define LoadString LoadStringW
#define GlobalAddAtom GlobalAddAtomW
#define GlobalFindAtom GlobalFindAtomW
#define GetTempFileName GetTempFileNameW
#define CeGetCanonicalPathName CeGetCanonicalPathNameW
#define CreateFile CreateFileW
#define DeleteFile DeleteFileW
#define FindFirstFile FindFirstFileW
#define FindNextFile FindNextFileW
#define CopyFile CopyFileW
#define CopyFileEx CopyFileExW
#define MoveFile MoveFileW
#define CreateDirectory CreateDirectoryW
#define RemoveDirectory RemoveDirectoryW
#define FindFirstChangeNotification FindFirstChangeNotificationW
#define SetFileAttributes SetFileAttributesW
#define GetFileAttributes GetFileAttributesW
#define CreateMutex CreateMutexW
#define CreateEvent CreateEventW
#define OpenEvent OpenEventW
#define CreateSemaphore CreateSemaphoreW
#define ReportEvent ReportEventW
#define RegisterEventSource RegisterEventSourceW
#define ClearEventLog ClearEventLogW
#define OpenEventLog OpenEventLogW
#define BackupEventLog BackupEventLogW
#define GetDiskFreeSpaceEx GetDiskFreeSpaceExW
#define CeFsIoControl CeFsIoControlW
#define GMEM_DDESHARE LMEM_DDESHARE
#define GMEM_ZEROINIT LMEM_ZEROINIT
#define GMEM_LOWER LMEM_LOWER
#define GMEM_SHARE LMEM_SHARE
#define GMEM_NOCOMPACT LMEM_NOCOMPACT
#define GMEM_MOVEABLE LMEM_MOVEABLE
#define GMEM_NOTIFY LMEM_NOTIFY
#define GMEM_DISCARDABLE LMEM_DISCARDABLE
#define GMEM_NOT_BANKED LMEM_NOT_BANKED
#define GMEM_FIXED LMEM_FIXED
#define GMEM_NODISCARD LMEM_NODISCARD
#ifdef __cplusplus
}
#endif
#define MAX_COMPUTERNAME_LENGTH 15
#define WAIT_ABANDONED 0x00000080L
#define CREATE_SUSPENDED 0x00000004
#define FILE_END 2
#define LMEM_NOCOMPACT 0x0010
#define LMEM_LOCKCOUNT 0x00FF
#define LMEM_MODIFY 0x0080
#define INVALID_HANDLE_VALUE (HANDLE)-1
#define GENERIC_EXECUTE (0x20000000L)
#define WAIT_OBJECT_0 0x00000000L
#define THREAD_PRIORITY_ABOVE_IDLE 6
#define MAX_CE_PRIORITY_LEVELS 256
#define THREAD_PRIORITY_LOWEST 5
#define FILE_FLAG_POSIX_SEMANTICS 0x01000000
#define FILE_FLAG_RANDOM_ACCESS 0x10000000
#define FILE_SHARE_WRITE 0x00000002
#define THREAD_PRIORITY_IDLE 7
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define LMEM_LOWER 0x0000
#define LMEM_SHARE 0x0000
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define LMEM_ZEROINIT 0x0040
#define VER_PLATFORM_WIN32_CE 3
#define INFINITE 0xffffffffL
#define WAIT_FAILED 0xffffffffL
#define VER_PLATFORM_WIN32_HH 3
#define INVALID_FILE_SIZE (DWORD)0xFFFFFFFF
#define GENERIC_ALL (0x10000000L)
#define GENERIC_READ (0x80000000L)
#define VER_PLATFORM_WIN32_NT 2
#define FORMAT_MESSAGE_FROM_HMODULE 0x00000800
#define OPEN_ALWAYS 4
#define LMEM_DDESHARE 0x0000
#define FILE_SHARE_READ 0x00000001
#define FILE_FLAG_WRITE_THROUGH 0x80000000
#define MAX_WIN32_PRIORITY_LEVELS 8
#define LMEM_VALID_FLAGS 0x0F72
#define CREATE_NEW 1
#define FORMAT_MESSAGE_ARGUMENT_ARRAY 0x00002000
#define LMEM_NOTIFY 0x0000
#define VER_PLATFORM_WIN32_WINDOWS 1
#define LMEM_INVALID_HANDLE 0x8000
#define LMEM_DISCARDABLE 0x0F00
#define LMEM_NOT_BANKED 0x0000
#define FILE_FLAG_BACKUP_SEMANTICS 0x02000000
#define FILE_FLAG_OVERLAPPED 0x40000000
#define THREAD_PRIORITY_HIGHEST 1
#define LMEM_MOVEABLE 0x0002
#define IGNORE 0
#define OPEN_FOR_LOADER 6
#define FILE_CURRENT 1
#define THREAD_PRIORITY_NORMAL 3
#define FILE_BEGIN 0
#define CREATE_THREAD_DEBUG_EVENT 2
#define FILE_FLAG_DELETE_ON_CLOSE 0x04000000
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define THREAD_PRIORITY_TIME_CRITICAL 0
#define CREATE_ALWAYS 2
#define FILE_FLAG_NO_BUFFERING 0x20000000
#define WAIT_ABANDONED_0 0x00000080L
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define THREAD_PRIORITY_ABOVE_NORMAL 2
#define FORMAT_MESSAGE_FROM_STRING 0x00000400
#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200
#define OPEN_EXISTING 3
#define GENERIC_WRITE (0x40000000L)
#define LMEM_FIXED 0x0000
#define CREATE_NEW_CONSOLE 0x00000010
#define TRUNCATE_EXISTING 5
#define LMEM_DISCARDED 0x4000
#define CREATE_PROCESS_DEBUG_EVENT 3
#define THREAD_PRIORITY_BELOW_NORMAL 4
#define LMEM_NODISCARD 0x0020
#define FORMAT_MESSAGE_MAX_WIDTH_MASK 0x000000FF
#define VER_PLATFORM_WIN32s 0
#endif

