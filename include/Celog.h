/*
 * Celog.h -- CeLog event-tracking API for Windows CE (kernel profiler).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the "CeLog Event Tracking Reference" book (CE-era MSDN archive,
 * learn.microsoft.com previous-versions, (v=msdn.10) IDs).  All of the
 * function pages below print Header: Celog.h and Link Library:
 * Coredll.lib.  OS Versions per function are recorded inline.
 *
 * This header covers the seven *function* pages of the CeLog book.
 * The CEL_* event-record structures (CEL_EVENT_CREATE, CEL_HEADER,
 * MAPHEADER, ... 60+ pages), the event-identifiers pages and the zone
 * list page record the *payload format* of kernel event-log entries
 * (consumed through the CeLog driver stream); they carry no function
 * declarations and no Header/Link rows, and are recorded in
 * docs/inventory.md rather than transcribed here.
 *
 * CROSS-GENERATION (M86 sweep, recorded for the payload structures
 * kept in docs/inventory.md): the CE 4.0 twins print the critical-
 * section event tags as __CEL_CS_ENTER / __CEL_CS_LEAVE (ms905291;
 * CE 5.0: __CEL_CRITSEC_ENTER / __CEL_CRITSEC_LEAVE, members
 * identical), and the CE 6.0 MAPHEADER twin ee488608 appends a
 * VERSION 2 DATA tail (DWORD dwVersion; DWORD dwBufferStart; DWORD
 * dwWriteOffset; DWORD dwReadOffset;) after dwLostBytes.
 */

#ifndef AKARI_CELOG_H
#define AKARI_CELOG_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa450823 "CeLogData (Windows CE 5.0)":
 * void CeLogData(BOOL, WORD, PVOID, WORD, DWORD, DWORD, WORD, BOOL).
 * CE 3.0+; Celog.h; Coredll.lib.  Called by the kernel whenever a
 * loggable event occurs; apps/drivers normally reach it through the
 * zone macros. */
AKARI_CE_IMPORT void CeLogData(BOOL fTimeStamp, WORD wID, PVOID pData, WORD wLen,
               DWORD dwZoneUser, DWORD dwZoneCE, WORD wFlag,
               BOOL fFlagged) AKARI_CE_NAME(CeLogData);

/* aa450824 "CeLogGetZones (Windows CE 5.0)":
 * BOOL CeLogGetZones(LPDWORD, LPDWORD, LPDWORD, LPDWORD).  CE .NET
 * 4.0+; Celog.h; Coredll.lib.  Returns the active user zones, active
 * predefined system zones, the processes being logged, and the zones
 * the kernel supports (any output pointer may be NULL). */
AKARI_CE_IMPORT BOOL CeLogGetZones(LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE,
                   LPDWORD lpdwZoneProcess, LPDWORD lpdwAvailableZones) AKARI_CE_NAME(CeLogGetZones);

/* aa451043 "CeLogInterrupt (Windows CE 5.0)":
 * void CeLogInterrupt(DWORD).  CE .NET 3.0+; Celog.h; Coredll.lib.
 * Called by the kernel twice per interrupt (before the ISR and when
 * the ISR returns).  The value packs the CEL_INT_DATA wSysIntr (upper
 * word) and wNestingLevel (lower word) members; the nesting level's
 * upper bit marks interrupt entry vs exit. */
AKARI_CE_IMPORT void CeLogInterrupt(DWORD dwlogvalue) AKARI_CE_NAME(CeLogInterrupt);

/* aa450825 "CeLogMsg (Windows CE 5.0)":
 * void CeLogMsg(WCHAR *format, ...).  CE .NET 4.0+; Celog.h;
 * Coredll.lib.  Prints a formatted Unicode string to CeLogData; the
 * RETAILCELOGMSG / DEBUGCELOGMSG macros output conditionally. */
AKARI_CE_IMPORT void CeLogMsg(WCHAR *format, ...) AKARI_CE_NAME(CeLogMsg);

/* aa450826 "CeLogQueryZones (Windows CE 5.0)":
 * BOOL CeLogQueryZones(LPDWORD, LPDWORD, LPDWORD).  CE .NET 4.0+;
 * Celog.h (page: "Not applicable"); Coredll.lib.  Called by the kernel
 * to query zone state from the event-tracking DLL. */
AKARI_CE_IMPORT BOOL CeLogQueryZones(LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE,
                     LPDWORD ldpwZoneProcess) AKARI_CE_NAME(CeLogQueryZones);

/* aa450827 "CeLogReSync (Windows CE 5.0)":
 * BOOL CeLogReSync(void).  CE 3.0+; Celog.h; Coredll.lib.  Tells the
 * logging engine to dump all current threads and processes (for an
 * event viewer that restarts logging); the page notes this function is
 * part of the kernel and generates CeLogData calls. */
AKARI_CE_IMPORT BOOL CeLogReSync(void) AKARI_CE_NAME(CeLogReSync);

/* aa450828 "CeLogSetZones (Windows CE 5.0)":
 * void CeLogSetZones(DWORD, DWORD, DWORD).  CE 3.0+; Celog.h;
 * Coredll.lib.  Changes the active logging zones: user zones, OS zones
 * (default 0xFFBFFFFF, KCALLS off) and logged processes (default
 * 0xFFFFFFFF, all). */
AKARI_CE_IMPORT void CeLogSetZones(DWORD dwZoneUser, DWORD dwZoneCE, DWORD dwZoneProcess) AKARI_CE_NAME(CeLogSetZones);

/* --- Kernel-callable OEM hooks (official Windows CE 3.0 archive). ---
 *
 * The CE 3.0 Platform Builder pages (_wcepb_*, Defined in Celog.h,
 * Versions 3.0 and later, no Link row) print the hooks the kernel
 * calls into the OEM event-tracking implementation; they are declared
 * without import decoration.  The four global variables adjust the
 * logging thread; the CE 3.0 pages print `extern dwCeLog...;` with
 * no type, the CE 5.0 twins print `extern DWORD ...;` for the two
 * buffer sizes (OS Versions: Windows CE 3.0 and later, Header:
 * Celog.h) -- the DWORD spelling is adopted from the CE 5.0 pages. */

/* _wcepb_CeLogInit "CeLogInit": void CeLogInit(void).  CE 3.0+;
 * Celog.h.  The kernel calls this when the event-tracking subsystem
 * is initialized; the OEM initializes the software/hardware needed
 * to accept event tracking. */
void CeLogInit(void);

/* _wcepb_CeLogThreadMigrate "CeLogThreadMigrate":
 * void CeLogThreadMigrate(HANDLE, DWORD).  CE 3.0+; Celog.h.  The
 * kernel calls this when a thread migrates between processes;
 * hProcess is the process the thread migrates into, dwReserved is
 * reserved. */
void CeLogThreadMigrate(HANDLE hProcess, DWORD dwReserved);

/* ms904009 "dwCeLogLargeBuf (Windows CE 5.0)" (+ CE 3.0 archive
 * _wcepb_dwCeLogLargeBuf): extern DWORD dwCeLogLargeBuf.  CE 3.0+;
 * Celog.h.  Size in bytes of the main logging buffer; must be
 * page-aligned.  Default 128 KB; overridable in OEMInit. */
extern DWORD dwCeLogLargeBuf;

/* ms904010 "dwCeLogSmallBuf (Windows CE 5.0)" (+ CE 3.0 archive
 * _wcepb_dwCeLogSmallBuf): extern DWORD dwCeLogSmallBuf.  CE 3.0+;
 * Celog.h.  Size of the secondary buffer used for interrupt events;
 * must not exceed 50% of dwCeLogLargeBuf.  Default 4 KB; overridable
 * in OEMInit. */
extern DWORD dwCeLogSmallBuf;

/* HELD -- type unpublished (zero-gap policy):
 *   _wcepb_dwCeLogFlushTimeout "dwCeLogFlushTimeout": the CE 3.0
 *   page prints `extern dwCeLogFlushTimeout;` with no type, and the
 *   CE 5.0/6.0 trees carry no page for it.  Milliseconds the logging
 *   thread waits before flushing the large buffer; default 10000;
 *   overridable in OEMInit.
 *   _wcepb_nCeLogThreadPrio "nCeLogThreadPrio": same print shape
 *   (`extern nCeLogThreadPrio;`, no type; absent from CE 5.0/6.0).
 *   Priority of the flushing thread (any CeSetThreadPriority value);
 *   default 248; overridable in OEMInit. */

/* ------------------------------------------------------------------
 * Book surface: core-celog-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451055 CEL_MAPFILE_VIEW_OPEN (page print, compiled) */
#if _WIN32_WCE >= 0x0500   /* Windows CE 5.0 and later. (aa451055) */
typedef struct __CEL_MAPFILE_VIEW_OPEN {
    HANDLE hMap;
    HANDLE hProcess;
    DWORD dwDesiredAccess;
    DWORD dwFileOffset;
    DWORD dwLen;
    LPVOID lpBaseAddress;
} CEL_MAPFILE_VIEW_OPEN;
/* aa451058 CEL_MAPFLUSH_TYPE (page print, compiled) */
typedef enum  {
    CEL_INVALID_MAPFLUSH = 0,
    CEL_FlushMapSimple = 1,
    CEL_FlushMapAtomic = 2,
    CEL_ValidateFile = 3,
    CEL_FlushMapGather = 4,
    CEL_NUM_MAPFLUSH_TYPES
} CEL_MAPFLUSH_TYPE;
#endif /* _WIN32_WCE >= 0x0500 */
/* aa451053 "CEL_MAPFILE_VIEW_CLOSE" page print; the print repeats the
 * same name for the pointer alias (`*CEL_MAPFILE_VIEW_CLOSE`) --
 * documented artifact, only the struct alias is declared. */
typedef struct __CEL_MAPFILE_VIEW_CLOSE {
    HANDLE hMap;
    LPVOID lpBaseAddress;
} CEL_MAPFILE_VIEW_CLOSE;
/* aa450817 CEL_MODULE_FREE: documented name-only (no value published; held) */
/* aa450818 CEL_MODULE_LOAD: documented name-only (no value published; held) */
/* aa450822 CEL_MUTEX_RELEASE: documented name-only (no value published; held) */
/* ms885128 CEL_SYSTEM_INVERT: documented name-only (no value published; held) */
/* ms885129 CEL_SYSTEM_PAGE: documented name-only (no value published; held) */
/* ms885130 CEL_SYSTEM_TLB: documented name-only (no value published; held) */
/* ms885134 CEL_THREAD_MIGRATE: documented name-only (no value published; held) */
/* ms885135 CEL_THREAD_PRIORITY: documented name-only (no value published; held) */
/* ms885136 CEL_THREAD_QUANTUM: documented name-only (no value published; held) */

/* ------------------------------------------------------------------
 * Book surface: core-celog-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450677 CeLog Event Identifiers */
/* aa450679 CeLog Event Tracking Functions */
/* aa451019 CeLog Event Tracking Macros */
/* aa450698 CeLog Event Tracking Structures */
/* aa451021 CeLog Pre-Defined Data Types */
/* aa450700 CeLog Zones */

#ifdef __cplusplus
}
#endif

/* ms885146 "CEL_CRITSEC_DELETE" page print (fused tokens split). */
typedef struct __CEL_CRITSEC_DELETE {
    HANDLE hCS;
} CEL_CRITSEC_DELETE, *PCEL_CRITSEC_DELETE;

/* aa450798 "CEL_CRITSEC_ENTER" page print (fused tokens split). */
typedef struct __CEL_CRITSEC_ENTER {
    HANDLE hCS;
    HANDLE hOwnerThread;
} CEL_CRITSEC_ENTER, *PCEL_CRITSEC_ENTER;

/* ms885147 "CEL_CRITSEC_INIT" page print (fused tokens split). */
typedef struct __CEL_CRITSEC_INIT {
    HANDLE hCS;
} CEL_CRITSEC_INIT, *PCEL_CRITSEC_INIT;

/* aa450799 "CEL_CRITSEC_LEAVE" page print (fused tokens split). */
typedef struct __CEL_CRITSEC_LEAVE {
    HANDLE hCS;
    HANDLE hOwnerThread;
} CEL_CRITSEC_LEAVE, *PCEL_CRITSEC_LEAVE;

/* aa450800 "CEL_DATA_LOSS" page print (fused tokens split). */
typedef struct __CEL_DATA_LOSS {
    DWORD dwBytes;
} CEL_DATA_LOSS, *PCEL_DATA_LOSS;

/* aa451045 "CEL_CEL_DEBUG_MSG" page print (fused tokens split). */
typedef struct __CEL_DEBUG_MSG {
    DWORD pid;
    DWORD tid;
    WCHAR szMessage[0];
} CEL_CEL_DEBUG_MSG, *PCEL_CEL_DEBUG_MSG;

/* aa450801 "CEL_EVENT_CLOSE" page print (fused tokens split). */
typedef struct __CEL_EVENT_CLOSE {
    HANDLE hEvent;
} CEL_EVENT_CLOSE, *PCEL_EVENT_CLOSE;

/* aa450803 "CEL_EVENT_DELETE" page print (fused tokens split). */
typedef struct __CEL_EVENT_DELETE {
    HANDLE hEvent;
} CEL_EVENT_DELETE, *PCEL_EVENT_DELETE;

/* aa450804 "CEL_EVENT_PULSE" page print (fused tokens split). */
typedef struct __CEL_EVENT_PULSE {
    HANDLE hEvent;
} CEL_EVENT_PULSE, *PCEL_EVENT_PULSE;

/* aa450805 "CEL_EVENT_RESET" page print (fused tokens split). */
typedef struct __CEL_EVENT_RESET {
    HANDLE hEvent;
} CEL_EVENT_RESET, *PCEL_EVENT_RESET;

/* aa450806 "CEL_EVENT_SET" page print (fused tokens split). */
typedef struct __CEL_EVENT_SET {
    HANDLE hEvent;
} CEL_EVENT_SET, *PCEL_EVENT_SET;

/* ms885148 "CEL_EXTRA_MODULE_INFO" page print (fused tokens split). */
typedef struct __CEL_EXTRA_MODULE_INFO {
    HANDLE hModule;
    DWORD dwVMLen;
    DWORD dwModuleFlags;
    DWORD dwOID;
    WCHAR szFullPath[0];
} CEL_EXTRA_MODULE_INFO, *PCEL_EXTRA_MODULE_INFO;

/* ms885149 "CEL_EXTRA_PROCESS_INFO" page print (fused tokens split). */
typedef struct __CEL_EXTRA_PROCESS_INFO {
    HANDLE hProcess;
    DWORD dwCodeBaseDWORDdwVMLen;
    DWORD dwOID;
    WCHAR szFullPath[0];
} CEL_EXTRA_PROCESS_INFO, *PCEL_EXTRA_PROCESS_INFO;

/* aa450808 "CEL_HEAP_ALLOC" page print (fused tokens split). */
typedef struct __CEL_HEAP_ALLOC {
    HANDLE hHeap;
    DWORD dwFlags;
    DWORD dwBytes;
    DWORD lpMem;
    DWORD dwTID;
    DWORD dwPID;
    DWORD dwCallerPID;
    DWORD adwStackTrace[0];
} CEL_HEAP_ALLOC, *PCEL_HEAP_ALLOC;

/* aa450809 "CEL_HEAP_CREATE" page print (fused tokens split). */
typedef struct __CEL_HEAP_CREATE {
    DWORD dwOptions;
    DWORD dwInitSize;
    DWORD dwMaxSize;
    HANDLE hHeap;
    DWORD dwTID;
    DWORD dwPID;
} CEL_HEAP_CREATE, *PCEL_HEAP_CREATE;

/* aa450810 "CEL_HEAP_DESTROY" page print (fused tokens split). */
typedef struct __CEL_HEAP_DESTROY {
    HANDLE hHeap;
    DWORD dwTID;
    DWORD dwPID;
} CEL_HEAP_DESTROY, *PCEL_HEAP_DESTROY;

/* aa450811 "CEL_HEAP_FREE" page print (fused tokens split). */
typedef struct __CEL_HEAP_FREE {
    HANDLE hHeap;
    DWORD dwFlags;
    DWORD lpMem;
    DWORD dwTID;
    DWORD dwPID;
    DWORD dwCallerPID;
    DWORD adwStackTrace[0];
} CEL_HEAP_FREE, *PCEL_HEAP_FREE;

/* aa450812 "CEL_HEAP_REALLOC" page print (fused tokens split). */
typedef struct __CEL_HEAP_REALLOC {
    HANDLE hHeap;
    DWORD dwFlags;
    DWORD dwBytes;
    DWORD lpMemOld;
    DWORD lpMem;
    DWORD dwTID;
    DWORD dwPID;
    DWORD dwCallerPID;
    DWORD adwStackTrace[0];
} CEL_HEAP_REALLOC, *PCEL_HEAP_REALLOC;

/* CHM page "_wcepb_CEL_INT_DATA" (Windows CE 3.0, retired content)
 * prints `typedef __CEL_INT_DATA { DWORD dwTimeStamp ; WORD wSysIntr
 * ; WORD wNestingLevel ; } CEL_INT_DATA, *PCEL_INT_DATA;` (the CHM
 * conversion drops the `struct` keyword after typedef; restored). */
typedef struct __CEL_INT_DATA {
    DWORD dwTimeStamp;
    WORD wSysIntr;
    WORD wNestingLevel;
} CEL_INT_DATA, *PCEL_INT_DATA;

/* aa450814 "CEL_INTERRUPTS" page print (fused tokens split). */
typedef struct __CEL_INTERRUPTS {
    DWORD dwDiscarded;
    CEL_INT_DATA IntData[0];   /* page print fused CEL_INT_DATAIntData */
} CEL_INTERRUPTS, *PCEL_INTERRUPTS;

/* aa450815 "CEL_LOG_MARKER" page print (fused tokens split). */
typedef struct __CEL_LOG_MARKER {
    DWORD dwFrequency;
    DWORD dwDefaultQuantum;
    DWORD dwVersion;
} CEL_LOG_MARKER, *PCEL_LOG_MARKER;

/* aa451047 "CEL_MAPFILE_CREATE" page print (fused tokens split). */
typedef struct __CEL_MAPFILE_CREATE {
    HANDLE hMap;
    DWORD flProtect;
    DWORD dwMapFlags;
    DWORD dwMaxSize;
    WCHAR szName[0];
} CEL_MAPFILE_CREATE, *PCEL_MAPFILE_CREATE;

/* aa451049 "CEL_MAPFILE_DESTROY" page print (fused tokens split). */
typedef struct __CEL_MAPFILE_DESTROY {
    HANDLE hMap;
} CEL_MAPFILE_DESTROY, *PCEL_MAPFILE_DESTROY;

/* aa451051 "CEL_MAPFILE_FLUSH" page print (fused tokens split). */
typedef struct __CEL_MAPFILE_FLUSH {
    LPVOID lpBaseAddress;
    DWORD dwLen;
    WORD wFlushFlags;
    WORD wNumPages;
} CEL_MAPFILE_FLUSH, *PCEL_MAPFILE_FLUSH;

/* aa450816 "CEL_MEMTRACK_BASELINE" page print (fused tokens split). */
typedef struct __CEL_MEMTRACK_BASELINE {
    DWORD dwReserved;
} CEL_MEMTRACK_BASELINE, *PCEL_MEMTRACK_BASELINE;

/* aa450819 "CEL_MUTEX_CLOSE" page print (fused tokens split). */
typedef struct __CEL_MUTEX_CLOSE {
    HANDLE hMutex;
} CEL_MUTEX_CLOSE, *PCEL_MUTEX_CLOSE;

/* aa450820 "CEL_MUTEX_CREATE" page print (fused tokens split). */
typedef struct __CEL_MUTEX_CREATE {
    HANDLE hMutex;
    WCHAR szName[0];
} CEL_MUTEX_CREATE, *PCEL_MUTEX_CREATE;

/* aa450821 "CEL_MUTEX_DELETE" page print (fused tokens split). */
typedef struct __CEL_MUTEX_DELETE {
    HANDLE hMutex;
} CEL_MUTEX_DELETE, *PCEL_MUTEX_DELETE;

/* aa450829 "CEL_PROCESS_CLOSE" page print (fused tokens split). */
typedef struct __CEL_PROCESS_CLOSE {
    HANDLE hProcess;
} CEL_PROCESS_CLOSE, *PCEL_PROCESS_CLOSE;

/* aa450830 "CEL_PROCESS_CREATE" page print (fused tokens split). */
typedef struct __CEL_PROCESS_CREATE {
    HANDLE hProcess;
    DWORD dwVMBase;
    WCHAR szName[0];
} CEL_PROCESS_CREATE, *PCEL_PROCESS_CREATE;

/* ms884894 "CEL_PROCESS_DELETE" page print (fused tokens split). */
typedef struct __CEL_PROCESS_DELETE {
    HANDLE hProcess;
} CEL_PROCESS_DELETE, *PCEL_PROCESS_DELETE;

/* ms885151 "CEL_PROCESS_REFCOUNT" page print (fused tokens split). */
typedef struct __CEL_PROCESS_REFCOUNT {
    HANDLE hProcess;
    DWORD dwRefCount;
} CEL_PROCESS_REFCOUNT, *PCEL_PROCESS_REFCOUNT;

/* ms884998 "CEL_PROCESS_TERMINATE" page print (fused tokens split). */
typedef struct __CEL_PROCESS_TERMINATE {
    HANDLE hProcess;
} CEL_PROCESS_TERMINATE, *PCEL_PROCESS_TERMINATE;

/* ms885107 "CEL_SEM_CLOSE" page print (fused tokens split). */
typedef struct __CEL_SEM_CLOSE {
    HANDLE hSem;
} CEL_SEM_CLOSE, *PCEL_SEM_CLOSE;

/* ms885117 "CEL_SEM_CREATE" page print (fused tokens split). */
typedef struct __CEL_SEM_CREATE {
    HANDLE hSem;
    DWORD dwInitCount;
    DWORD dwMaxCount;
    WCHAR szName[0];
} CEL_SEM_CREATE, *PCEL_SEM_CREATE;

/* ms885125 "CEL_SEM_DELETE" page print (fused tokens split). */
typedef struct __CEL_SEM_DELETE {
    HANDLE hSem;
} CEL_SEM_DELETE, *PCEL_SEM_DELETE;

/* ms885126 "CEL_SEM_RELEASE" page print (fused tokens split). */
typedef struct __CEL_SEM_RELEASE {
    HANDLE hSem;
    DWORD dwReleaseCount;
    DWORD dwPreviousCount;
} CEL_SEM_RELEASE, *PCEL_SEM_RELEASE;

/* ms885127 "CEL_SLEEP" page print (fused tokens split). */
typedef struct __CEL_SLEEP {
    DWORD dwTimeout;
} CEL_SLEEP, *PCEL_SLEEP;

/* ms885131 "CEL_THREAD_CLOSE" page print (fused tokens split). */
typedef struct __CEL_THREAD_CLOSE {
    HANDLE hThread;
} CEL_THREAD_CLOSE, *PCEL_THREAD_CLOSE;

/* ms885132 "CEL_THREAD_CREATE" page print (fused tokens split). */
typedef struct __CEL_THREAD_CREATE {
    HANDLE hThread;
    HANDLE hProcess;
    HANDLE hModule;
    DWORD dwStartAddr;
    int nPriority;
    WCHAR szName[0];
} CEL_THREAD_CREATE, *PCEL_THREAD_CREATE;

/* ms885133 "CEL_THREAD_DELETE" page print (fused tokens split). */
typedef struct __CEL_THREAD_DELETE {
    HANDLE hThread;
} CEL_THREAD_DELETE, *PCEL_THREAD_DELETE;

/* ms885137 "CEL_THREAD_RESUME" page print (fused tokens split). */
typedef struct __CEL_THREAD_RESUME {
    HANDLE hThread;
} CEL_THREAD_RESUME, *PCEL_THREAD_RESUME;

/* ms885138 "CEL_THREAD_SUSPEND" page print (fused tokens split). */
typedef struct __CEL_THREAD_SUSPEND {
    HANDLE hThread;
} CEL_THREAD_SUSPEND, *PCEL_THREAD_SUSPEND;

/* ms885139 "CEL_THREAD_SWITCH" page print (fused tokens split). */
typedef struct __CEL_THREAD_SWITCH {
    HANDLE hThread;
} CEL_THREAD_SWITCH, *PCEL_THREAD_SWITCH;

/* ms885140 "CEL_THREAD_TERMINATE" page print (fused tokens split). */
typedef struct __CEL_THREAD_TERMINATE {
    HANDLE hThread;
} CEL_THREAD_TERMINATE, *PCEL_THREAD_TERMINATE;

/* ms885141 "CEL_VIRTUAL_ALLOC" page print (fused tokens split). */
typedef struct __CEL_VIRTUAL_ALLOC {
    DWORD dwResult;
    DWORD dwAddress;
    DWORD dwSize;
    DWORD dwType;
    DWORD dwProtect;
    BYTE bReserved[0];
} CEL_VIRTUAL_ALLOC, *PCEL_VIRTUAL_ALLOC;

/* ms885142 "CEL_VIRTUAL_COPY" page print (fused tokens split). */
typedef struct __CEL_VIRTUAL_COPY {
    DWORD dwDest;
    DWORD dwSource;
    DWORD dwSize;
    DWORD dwProtect;
} CEL_VIRTUAL_COPY, *PCEL_VIRTUAL_COPY;

/* ms885143 "CEL_VIRTUAL_FREE" page print (fused tokens split). */
typedef struct __CEL_VIRTUAL_FREE {
    DWORD dwAddress;
    DWORD dwSize;
    DWORD dwType;
    BYTE bReserved[0];
} CEL_VIRTUAL_FREE, *PCEL_VIRTUAL_FREE;

/* ms885145 "CEL_WAIT_MULTI" page print (fused tokens split). */
typedef struct __CEL_WAIT_MULTI {
    DWORD dwTimeout;
    DWORD fWaitAll:1;
    DWORD dwReserved:31;
    HANDLE hHandles[0];
} CEL_WAIT_MULTI, *PCEL_WAIT_MULTI;

#endif /* AKARI_CELOG_H */
