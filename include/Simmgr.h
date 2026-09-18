/*
 * Simmgr.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: simmgr.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_SIMMGR_H
#define AKARI_SIMMGR_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

/* --- Handle types no CE page typedefs. ------------------------------
 * HSIM: 24 corpus pages mention it and none prints a typedef, but
 * ee498206 "SimDeinitialize" prints
 *   `HRESULT SimDeinitialize ( HSIM hSim );`
 * (Header: simmgr.h, Link Library: cellcore.lib, Windows Embedded CE 6.0)
 * and the SIM API opens it in SimInitialize, so it is a handle closed by
 * the documented deinitializer -- the same evidence shape that decides
 * HINTERNET (Wininet.h) and the in-tree precedent for it, Windef.h:236
 * `typedef HANDLE HRSRC;`.  Its size is not published; a wrong one would
 * fix a wrong ABI, so HANDLE is the only spelling the pages support. */
typedef HANDLE HSIM;
typedef HSIM *LPHSIM;   /* page spelling of the SimInitialize out parameter */

/* ee497363 "SIMCALLBACK" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Header: simmgr.h, Link Library: cellcore.lib). */
typedef void (*SIMCALLBACK)(
    DWORD dwNotifyCode,
    const void *pData,
    DWORD dwDataSize,
    DWORD dwParam);

/* ee497869 "SimInitialize" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Header: simmgr.h, Link Library: cellcore.lib). */
AKARI_CE_IMPORT HRESULT SimInitialize(
    DWORD dwFlags,
    SIMCALLBACK lpfnCallBack,
    DWORD dwParam,
    LPHSIM lphSim) AKARI_CE_NAME(SimInitialize);


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee497103 SIMLOCKINGPWDLENGTH: page print
 * typedef struct simlockingpwdlength { DWORD dwFacility; DWORD dwPasswordLength; } SIMLOCKINGPWDLENGTH, FAR *LPSIMLOCKINGPWDLENGTH;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simlockingpwdlength {
    DWORD dwFacility;
    DWORD dwPasswordLength;
} SIMLOCKINGPWDLENGTH, FAR *LPSIMLOCKINGPWDLENGTH;

/* ee497361 SIMPBECHANGE: page print
 * typedef struct simpbechange_tag { DWORD dwEntry; DWORD dwStorage; } SIMPBECHANGE, FAR *LPSIMPBECHANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simpbechange_tag {
    DWORD dwEntry;
    DWORD dwStorage;
} SIMPBECHANGE, FAR *LPSIMPBECHANGE;

/* ee497628 SIMPHONEBOOKCAPS: page print
 * typedef struct simphonebookcaps_tag { DWORD cbSize; DWORD dwParams; DWORD dwStorages; DWORD dwMinIndex; DWORD dwMaxIndex; DWORD dwMaxAddressLength; DW
 * (generation not stated) */
typedef struct simphonebookcaps_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwStorages;
    DWORD dwMinIndex;
    DWORD dwMaxIndex;
    DWORD dwMaxAddressLength;
    DWORD dwMaxTextLength;
    DWORD dwMaxSecondNameLength;
    DWORD dwMaxAdditionalNumberLength;
    DWORD dwMaxEmailAddressLength;
    DWORD dwMaxGroupTagLength;
    DWORD dwMaxAdditionalNumberTagLength;
    DWORD dwAdditionalNumberCount;
    DWORD dwEmailAddressCount;
    DWORD dwMaxGroupTags;
    DWORD dwMaxAdditionalNumberTags;
    BOOL fHidden;
    BOOL fUid;
    DWORD dwMaxGroupIdCount;
} SIMPHONEBOOKCAPS, FAR *LPPHONEBOOKSIMCAPS;

/* ee497860 SIMMESSAGECHANGE: page print
 * typedef struct simmessagechange_tag { DWORD dwEntry; DWORD dwStorage; } SIMMESSAGECHANGE, FAR *LPSIMMESSAGECHANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simmessagechange_tag {
    DWORD dwEntry;
    DWORD dwStorage;
} SIMMESSAGECHANGE, FAR *LPSIMMESSAGECHANGE;

/* ee498275 SIMRECORDINFO: page print
 * typedef struct simrecordinfo_tag { DWORD cbSize; DWORD dwParams; DWORD dwRecordType; DWORD dwItemCount; DWORD dwSize; } SIMRECORDINFO, FAR *LPSIMRECOR
 * (Windows Embedded CE 6.0 and later) */
typedef struct simrecordinfo_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwRecordType;
    DWORD dwItemCount;
    DWORD dwSize;
} SIMRECORDINFO, FAR *LPSIMRECORDINFO;


/* ee496869 SimReadRecord: print `HRESULT SimReadRecord (
HSIM hSim,
DWORD dwAddress,
DWORD dwRecordType,
DWORD dwIndex,
LPBYTE lpData,
DWORD dwBufferSize,
LPDWORD lpdwBytesRead
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimReadRecord(HSIM hSim, DWORD dwAddress, DWORD dwRecordType, DWORD dwIndex, LPBYTE lpData, DWORD dwBufferSize, LPDWORD lpdwBytesRead) AKARI_CE_NAME(SimReadRecord);

/* ee496922 SimGetPhoneLockedState: print `HRESULT SimGetPhoneLockedState (
HSIM hSim,
LPDWORD lpdwLockedState
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimGetPhoneLockedState(HSIM hSim, LPDWORD lpdwLockedState) AKARI_CE_NAME(SimGetPhoneLockedState);

/* ee497120 SimChangeLockingPassword: print `HRESULT SimChangeLockingPassword (
HSIM hSim,
DWORD dwLockingFacility,
LPTSTR lpszOldPassword,
LPTSTR lpszNewPassword
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimChangeLockingPassword(HSIM hSim, DWORD dwLockingFacility, LPTSTR lpszOldPassword, LPTSTR lpszNewPassword) AKARI_CE_NAME(SimChangeLockingPassword);

/* ee497261 SimGetPhonebookStatus: print `HRESULT SimGetPhonebookStatus (
HSIM hSim,
DWORD dwLocation,
LPDWORD lpdwUsed,
LPDWORD lpdwTotal
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimGetPhonebookStatus(HSIM hSim, DWORD dwLocation, LPDWORD lpdwUsed, LPDWORD lpdwTotal) AKARI_CE_NAME(SimGetPhonebookStatus);

/* ee497384 SimWriteRecord: print `HRESULT SimWriteRecord (
HSIM hSim,
DWORD dwAddress,
DWORD dwRecordType,
DWORD dwIndex,
LPBYTE lpData,
DWORD dwByteCount
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimWriteRecord(HSIM hSim, DWORD dwAddress, DWORD dwRecordType, DWORD dwIndex, LPBYTE lpData, DWORD dwByteCount) AKARI_CE_NAME(SimWriteRecord);

/* ee497408 SimDeletePhonebookEntry: print `HRESULT SimDeletePhonebookEntry (
HSIM hSim,
DWORD dwLocation,
DWORD dwIndex
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimDeletePhonebookEntry(HSIM hSim, DWORD dwLocation, DWORD dwIndex) AKARI_CE_NAME(SimDeletePhonebookEntry);

/* ee497538 SimGetSmsStorageStatus: print `HRESULT SimGetSmsStorageStatus (
HSIM hSim,
DWORD dwStorage,
LPDWORD lpdwUsed,
LPDWORD lpdwTotal
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimGetSmsStorageStatus(HSIM hSim, DWORD dwStorage, LPDWORD lpdwUsed, LPDWORD lpdwTotal) AKARI_CE_NAME(SimGetSmsStorageStatus);

/* ee497657 SimDeleteMessage: print `HRESULT SimDeleteMessage (
HSIM hSim,
DWORD dwStorage,
DWORD dwIndex
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimDeleteMessage(HSIM hSim, DWORD dwStorage, DWORD dwIndex) AKARI_CE_NAME(SimDeleteMessage);

/* ee497684 SimGetLockingStatus: print `HRESULT SimGetLockingStatus (
HSIM hSim,
DWORD dwLockingFacility,
LPTSTR lpszPassword,
BOOL* pfEnabled
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimGetLockingStatus(HSIM hSim, DWORD dwLockingFacility, LPTSTR lpszPassword, BOOL *pfEnabled) AKARI_CE_NAME(SimGetLockingStatus);

/* ee498041 SimReadPhonebookTag: print `HRESULT SimReadPhonebookTag(
HSIM hSim,
DWORD dwTag,
DWORD dwIndex,
__out_ecount(cchNameSize) LPTSTR szName,
DWORD cchNameSize
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimReadPhonebookTag(HSIM hSim, DWORD dwTag, DWORD dwIndex, LPTSTR szName, DWORD cchNameSize) AKARI_CE_NAME(SimReadPhonebookTag);

/* ee498206 SimDeinitialize: print `HRESULT SimDeinitialize (
HSIM hSim
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimDeinitialize(HSIM hSim) AKARI_CE_NAME(SimDeinitialize);

/* ee498240 SimSetLockingStatus: print `HRESULT SimSetLockingStatus (
HSIM hSim,
DWORD dwLockingFacility,
LPTSTR lpszPassword,
BOOL fEnabled
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimSetLockingStatus(HSIM hSim, DWORD dwLockingFacility, LPTSTR lpszPassword, BOOL fEnabled) AKARI_CE_NAME(SimSetLockingStatus);

/* ee498242 SimUnlockPhone: print `HRESULT SimUnlockPhone (
HSIM hSim,
LPTSTR lpszPassword,
LPTSTR lpszNewPin
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimUnlockPhone(HSIM hSim, LPTSTR lpszPassword, LPTSTR lpszNewPin) AKARI_CE_NAME(SimUnlockPhone);

/* ee498259 SimGetRecordInfo: print `HRESULT SimGetRecordInfo (
HSIM hSim,
DWORD dwAddress,
LPSIMRECORDINFO lpSimRecordInfo
);`
 * (generation not stated; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT SimGetRecordInfo(HSIM hSim, DWORD dwAddress, LPSIMRECORDINFO lpSimRecordInfo) AKARI_CE_NAME(SimGetRecordInfo);

/* ee497617 SimGetPhonebookCapabilities: print `HRESULT
 * SimGetPhonebookCapabilities( HSIM hSim, LPSIMPHONEBOOKCAPS
 * lpCapabilities );` (Link Library: Cellcore.lib).  The print spells
 * the pointer LPSIMPHONEBOOKCAPS while the SIMPHONEBOOKCAPS page
 * (ee497628) typedefs only LPPHONEBOOKSIMCAPS; alias added so the
 * parameter keeps its printed spelling. */
typedef SIMPHONEBOOKCAPS FAR *LPSIMPHONEBOOKCAPS;
AKARI_CE_IMPORT HRESULT SimGetPhonebookCapabilities(HSIM hSim, LPSIMPHONEBOOKCAPS lpCapabilities) AKARI_CE_NAME(SimGetPhonebookCapabilities);

/* HELD (array-size constants no corpus page prints, checked
 * 2026-09-18): SimGetDevCaps (SIMCAPS/SIM_NUMLOCKFACILITIES),
 * SimReadMessage/SimWriteMessage (SIMMESSAGE/MAX_LENGTH_*),
 * SimReadPhonebookEntry(ies)/SimWritePhonebookEntry(Ex)
 * (SIMPHONEBOOKENTRY(EX), MAX_LENGTH_ constants, MAX_NUM_GROUPS). */

#endif /* _WIN32_WCE >= 0x0600 */

#endif /* AKARI_SIMMGR_H */
