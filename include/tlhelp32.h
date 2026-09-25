/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_TLHELP32_H
#define WCE_TLHELP32_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHEAPLIST32 { DWORD dwSize; DWORD th32ProcessID; DWORD th32HeapID; DWORD dwFlags; } HEAPLIST32, *PHEAPLIST32, *LPHEAPLIST32;
typedef struct tagHEAPENTRY32 { DWORD dwSize; HANDLE hHandle; DWORD dwAddress; DWORD dwBlockSize; DWORD dwFlags; DWORD dwLockCount; DWORD dwResvd; DWORD th32ProcessID; DWORD th32HeapID; } HEAPENTRY32, *PHEAPENTRY32, *LPHEAPENTRY32;
typedef struct tagTHREADENTRY32 { DWORD dwSize; DWORD cntUsage; DWORD th32ThreadID; DWORD th32OwnerProcessID; LONG tpBasePri; LONG tpDeltaPri; DWORD dwFlags; DWORD th32AccessKey; DWORD th32CurrentProcessID; } THREADENTRY32, *PTHREADENTRY32, *LPTHREADENTRY32;

WCE_IMPORT HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID) WCE_LINK(CreateToolhelp32Snapshot);
WCE_IMPORT BOOL WINAPI CloseToolhelp32Snapshot(HANDLE hSnapshot) WCE_LINK(CloseToolhelp32Snapshot);
WCE_IMPORT BOOL WINAPI Heap32ListFirst(HANDLE hSnapshot, LPHEAPLIST32 lphl) WCE_LINK(Heap32ListFirst);
WCE_IMPORT BOOL WINAPI Heap32ListNext(HANDLE hSnapshot, LPHEAPLIST32 lphl) WCE_LINK(Heap32ListNext);
WCE_IMPORT BOOL WINAPI Heap32First(HANDLE hSnapshot, LPHEAPENTRY32 lphe, DWORD th32ProcessID, DWORD th32HeapID) WCE_LINK(Heap32First);
WCE_IMPORT BOOL WINAPI Heap32Next(HANDLE hSnapshot, LPHEAPENTRY32 lphe) WCE_LINK(Heap32Next);
WCE_IMPORT BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD th32ProcessID, LPCVOID lpBaseAddress, LPVOID lpBuffer, DWORD cbRead, LPDWORD lpNumberOfBytesRead) WCE_LINK(Toolhelp32ReadProcessMemory);
WCE_IMPORT BOOL WINAPI Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) WCE_LINK(Process32First);
WCE_IMPORT BOOL WINAPI Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) WCE_LINK(Process32Next);
WCE_IMPORT BOOL WINAPI Thread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte) WCE_LINK(Thread32First);
WCE_IMPORT BOOL WINAPI Thread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte) WCE_LINK(Thread32Next);
WCE_IMPORT BOOL WINAPI Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme) WCE_LINK(Module32First);
WCE_IMPORT BOOL WINAPI Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme) WCE_LINK(Module32Next);

#ifdef __cplusplus
}
#endif
#endif

