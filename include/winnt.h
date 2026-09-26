/* Character types, integer widths, synchronisation and access constants.
 * Original text.
 */
#ifndef AKARI_WCE_WINNT_H
#define AKARI_WCE_WINNT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "guiddef.h"
#include "windef.h"
#include "wcestr.h"

/* Windows CE stores text as 16 bit code units. */
typedef unsigned short WCHAR;
typedef WCHAR *PWCHAR, *LPWCH, *PWCH, *NWPSTR, *LPWSTR, *PWSTR;
typedef const WCHAR *LPCWCH, *PCWCH, *LPCWSTR, *PCWSTR;

typedef union akari_LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; } u;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union akari_ULARGE_INTEGER {
    struct { DWORD LowPart; DWORD HighPart; } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

/* The critical section object is allocated by the caller. Windows CE uses its
 * own layout, which is five machine words; the fields are opaque and are only
 * written by the synchronisation functions. */
typedef struct akari_CRITICAL_SECTION {
    unsigned int LockCount;
    HANDLE OwnerThread;
    HANDLE hCrit;
    DWORD needtrap;
    DWORD dwContentions;
} CRITICAL_SECTION, *PCRITICAL_SECTION, *LPCRITICAL_SECTION;

typedef struct akari_SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct akari_LUID { DWORD LowPart; LONG HighPart; } LUID, *PLUID;

/* Locale and language identifiers.  Every automation and national-language
   entry point takes an LCID. */
typedef DWORD  LCID;
typedef PDWORD PLCID;
typedef WORD   LANGID;
typedef WORD  *PLANGID;

typedef struct akari_FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; }
    FILETIME, *PFILETIME, *LPFILETIME;

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define INVALID_FILE_SIZE 0xFFFFFFFFu
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

#define FILE_ATTRIBUTE_READONLY    0x00000001
#define FILE_ATTRIBUTE_HIDDEN      0x00000002
#define FILE_ATTRIBUTE_SYSTEM      0x00000004
#define FILE_ATTRIBUTE_DIRECTORY   0x00000010
#define FILE_ATTRIBUTE_ARCHIVE     0x00000020
#define FILE_ATTRIBUTE_INROM       0x00000040
#define FILE_ATTRIBUTE_NORMAL      0x00000080
#define FILE_ATTRIBUTE_TEMPORARY   0x00000100
#define FILE_ATTRIBUTE_ROMMODULE       0x00002000

#define GENERIC_READ     0x80000000
#define GENERIC_WRITE    0x40000000
#define GENERIC_EXECUTE  0x20000000
#define GENERIC_ALL      0x10000000

#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD             0x100
#define PAGE_NOCACHE           0x200

#define MEM_COMMIT      0x1000
#define MEM_RESERVE     0x2000
#define MEM_DECOMMIT    0x4000
#define MEM_RELEASE     0x8000
#define MEM_FREE        0x10000
#define MEM_PRIVATE     0x20000
#define MEM_MAPPED      0x40000
#define MEM_RESET       0x80000
#define MEM_TOP_DOWN    0x100000
#define MEM_SHARED      0x8000000

#define STATUS_WAIT_0             0x00000000
#define STATUS_ABANDONED_WAIT_0   0x00000080
#define STATUS_USER_APC           0x000000C0
#define STATUS_TIMEOUT            0x00000102
#define STATUS_PENDING            0x00000103
#define WAIT_OBJECT_0             STATUS_WAIT_0
#define WAIT_ABANDONED            STATUS_ABANDONED_WAIT_0
#define WAIT_ABANDONED_0          STATUS_ABANDONED_WAIT_0
#define WAIT_TIMEOUT              STATUS_TIMEOUT
#define WAIT_PENDING              STATUS_PENDING
#define WAIT_FAILED               ((DWORD)0xFFFFFFFF)

#define STILL_ACTIVE 259

#define DELETE                   0x00010000
#define READ_CONTROL             0x00020000
#define WRITE_DAC                0x00040000
#define WRITE_OWNER              0x00080000
#define SYNCHRONIZE              0x00100000
#define STANDARD_RIGHTS_REQUIRED 0x000F0000
#define SECTION_QUERY        0x0001
#define SECTION_MAP_WRITE    0x0002
#define SECTION_EXTEND_SIZE  0x0010
#define SECTION_MAP_READ     0x0004
#define SECTION_MAP_EXECUTE  0x0008
#define SECTION_ALL_ACCESS   (STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | \
                              SECTION_MAP_WRITE | \
                              SECTION_MAP_READ | \
                              SECTION_MAP_EXECUTE | \
                              SECTION_EXTEND_SIZE)

#define STANDARD_RIGHTS_READ (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE (READ_CONTROL)
#define STANDARD_RIGHTS_ALL      0x001F0000

/*
 * Atomic helpers. Whether these are calls or inline code depends on the target
 * CPU: the x86 build of Windows CE resolves them in the compiler, so coredll
 * does not export them there, while every other CPU imports them from coredll.
 */
#if defined(_M_IX86) || defined(__i386__)
#if defined(_MSC_VER)
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, \
                  _InterlockedExchangeAdd, _InterlockedCompareExchange)
#define InterlockedIncrement(lpAddend)         _InterlockedIncrement(lpAddend)
#define InterlockedDecrement(lpAddend)         _InterlockedDecrement(lpAddend)
#define InterlockedExchange(Target, Value)     _InterlockedExchange((Target), (Value))
#define InterlockedExchangeAdd(Addend, Value)  _InterlockedExchangeAdd((Addend), (Value))
#define InterlockedCompareExchange(Destination, Exchange, Comparand) \
        _InterlockedCompareExchange((Destination), (Exchange), (Comparand))
#else
static __inline long InterlockedIncrement(long volatile *p)
    { return __sync_add_and_fetch(p, 1L); }
static __inline long InterlockedDecrement(long volatile *p)
    { return __sync_sub_and_fetch(p, 1L); }
static __inline long InterlockedExchange(long volatile *p, long v)
    { return __sync_lock_test_and_set(p, v); }
static __inline long InterlockedExchangeAdd(long volatile *p, long v)
    { return __sync_fetch_and_add(p, v); }
static __inline long InterlockedCompareExchange(long volatile *p, long ex, long cmp)
    { return __sync_val_compare_and_swap(p, cmp, ex); }
#endif
#else
/* On every CPU other than x86 these are imported from coredll, which is where
 * the CE SDK declares them (winbase.h).  They are declared here, inside the
 * non-x86 arm of the conditional, because the declaration has to be absent on
 * x86 -- see the comment above.
 */
WINBASEAPI LONG WINAPI InterlockedCompareExchange(LONG volatile *Destination,
                                                  LONG Exchange, LONG Comparand);
WINBASEAPI LONG WINAPI InterlockedDecrement(LONG volatile *lpAddend);
WINBASEAPI LONG WINAPI InterlockedExchange(LONG volatile *Target, LONG Value);
WINBASEAPI LONG WINAPI InterlockedExchangeAdd(LONG volatile *Addend, LONG Value);
WINBASEAPI LONG WINAPI InterlockedIncrement(LONG volatile *lpAddend);
#endif

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WINNT_H */
