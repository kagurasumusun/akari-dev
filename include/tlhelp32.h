/* Process, thread, module and heap enumeration. Original text.
 * Exported by toolhelp.dll.
 *
 * tlhelp32.h is the header name Windows CE uses for this surface; the CE 6.0
 * SDK has no toolhelp.h.  toolhelp.h is kept as an alias that includes this
 * file, because toolhelp.dll is the module the entry points come from and code
 * written against that name should still compile.
 *
 * Windows CE exports these entry points without an A/W suffix and there is only
 * one form of each structure; the character arrays are TCHAR, which on Windows
 * CE means wide characters. The layout is the same on .NET 4.2, 5.0 and 6.0.
 */
#ifndef AKARI_WCE_TLHELP32_H
#define AKARI_WCE_TLHELP32_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"
#include "tchar.h"

/* CreateToolhelp32Snapshot flags. */
#define TH32CS_SNAPHEAPLIST 0x00000001
#define TH32CS_SNAPPROCESS  0x00000002
#define TH32CS_SNAPTHREAD   0x00000004
#define TH32CS_SNAPMODULE   0x00000008
#define TH32CS_SNAPNOHEAPS  0x40000000
#define TH32CS_SNAPALL      (TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | \
                             TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE)
#define TH32CS_GETALLMODS   0x80000000
#define TH32CS_INHERIT      0x80000000

/* HEAPLIST32 dwFlags. */
#define HF32_DEFAULT        1

/* HEAPENTRY32 dwFlags. */
#define LF32_FIXED          0x00000001
#define LF32_FREE           0x00000002
#define LF32_MOVEABLE       0x00000004
#define LF32_DECOMMIT       0x00000008
#define LF32_BIGBLOCK       0x00000010

typedef struct akari_HEAPLIST32 {
    DWORD dwSize;
    DWORD th32ProcessID;
    DWORD th32HeapID;
    DWORD dwFlags;
} HEAPLIST32, *PHEAPLIST32, *LPHEAPLIST32;

typedef struct akari_HEAPENTRY32 {
    DWORD dwSize;
    HANDLE hHandle;
    DWORD dwAddress;
    DWORD dwBlockSize;
    DWORD dwFlags;
    DWORD dwLockCount;
    DWORD dwResvd;
    DWORD th32ProcessID;
    DWORD th32HeapID;
} HEAPENTRY32, *PHEAPENTRY32, *LPHEAPENTRY32;

typedef struct akari_PROCESSENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID;
    DWORD th32DefaultHeapID;
    DWORD th32ModuleID;
    DWORD cntThreads;
    DWORD th32ParentProcessID;
    LONG pcPriClassBase;
    DWORD dwFlags;
    TCHAR szExeFile[MAX_PATH];
    DWORD th32MemoryBase;
    DWORD th32AccessKey;
} PROCESSENTRY32, *PPROCESSENTRY32, *LPPROCESSENTRY32;

typedef struct akari_THREADENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ThreadID;
    DWORD th32OwnerProcessID;
    LONG tpBasePri;
    LONG tpDeltaPri;
    DWORD dwFlags;
    DWORD th32AccessKey;
    DWORD th32CurrentProcessID;
} THREADENTRY32, *PTHREADENTRY32, *LPTHREADENTRY32;

typedef struct akari_MODULEENTRY32 {
    DWORD dwSize;
    DWORD th32ModuleID;
    DWORD th32ProcessID;
    DWORD GlblcntUsage;
    DWORD ProccntUsage;
    BYTE *modBaseAddr;
    DWORD modBaseSize;
    HMODULE hModule;
    TCHAR szModule[MAX_PATH];
    TCHAR szExePath[MAX_PATH];
    DWORD dwFlags;
} MODULEENTRY32, *PMODULEENTRY32, *LPMODULEENTRY32;

TOOLHELPAPI HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
TOOLHELPAPI BOOL WINAPI CloseToolhelp32Snapshot(HANDLE hSnapshot);
TOOLHELPAPI BOOL WINAPI Heap32ListFirst(HANDLE hSnapshot, LPHEAPLIST32 lphl);
TOOLHELPAPI BOOL WINAPI Heap32ListNext(HANDLE hSnapshot, LPHEAPLIST32 lphl);
TOOLHELPAPI BOOL WINAPI Heap32First(HANDLE hSnapshot, LPHEAPENTRY32 lphe,
    DWORD th32ProcessID, DWORD th32HeapID);
TOOLHELPAPI BOOL WINAPI Heap32Next(HANDLE hSnapshot, LPHEAPENTRY32 lphe);
TOOLHELPAPI BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD th32ProcessID,
    LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD cbRead,
    LPDWORD lpNumberOfBytesRead);
TOOLHELPAPI BOOL WINAPI Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
TOOLHELPAPI BOOL WINAPI Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
TOOLHELPAPI BOOL WINAPI Thread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
TOOLHELPAPI BOOL WINAPI Thread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
TOOLHELPAPI BOOL WINAPI Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
TOOLHELPAPI BOOL WINAPI Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme);

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_TLHELP32_H */
