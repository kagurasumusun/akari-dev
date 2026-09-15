/*
 * Connmgr.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: connmgr.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CONNMGR_H
#define AKARI_CONNMGR_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee498058 CONNMGR_CONNECTIONINFO: page print
 * typedef struct { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwPriority; BOOL bExclusive; BOOL bDisabled; GUID guidDestNet; HWND hWnd; UINT uMs
 * (Windows CE .NET 4.2 and later) */
typedef struct {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwPriority;
    BOOL bExclusive;
    BOOL bDisabled;
    GUID guidDestNet;
    HWND hWnd;
    UINT uMsg;
    LPARAM lParam;
    ULONG ulMaxCost;
    ULONG ulMinRcvBw;
    ULONG ulMaxConnLatency;
} CONNMGR_CONNECTIONINFO;

/* ee498245 ConnMgrConRefTypeEnum: page print
 * typedef enum _ConnMgrConRefTypeEnum{ ConRefType_NAP = 0, ConRefType_PROXY } ConnMgrConRefTypeEnum;
 * (Windows CE .NET 4.2 and later) */
typedef enum _ConnMgrConRefTypeEnum {
    ConRefType_NAP = 0,
    ConRefType_PROXY
} ConnMgrConRefTypeEnum;


/* ee496830 ConnMgrProviderMessage: print `HRESULT WINAPI ConnMgrProviderMessage(
HANDLE hConnection,
const GUID *pguidProvider,
DWORD *pdwIndex,
DWORD dwMsg1,
DWORD dwMsg2,
PBYTE pParams,
ULONG cbParamSize
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrProviderMessage(HANDLE hConnection, const GUID *pguidProvider, DWORD *pdwIndex, DWORD dwMsg1, DWORD dwMsg2, PBYTE pParams, ULONG cbParamSize) AKARI_CE_NAME(ConnMgrProviderMessage);

/* ee497253 ConnMgrSetConnectionPriority: print `HRESULT WINAPI ConnMgrSetConnectionPriority(
HANDLE hConnection,
DWORD dwPriority
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrSetConnectionPriority(HANDLE hConnection, DWORD dwPriority) AKARI_CE_NAME(ConnMgrSetConnectionPriority);

/* ee497295 ConnMgrApiReadyEvent: print `HANDLE WINAPI ConnMgrApiReadyEvent (
void
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HANDLE ConnMgrApiReadyEvent(void) AKARI_CE_NAME(ConnMgrApiReadyEvent);

/* ee497349 ConnMgrConnectionStatus: print `HRESULT WINAPI ConnMgrConnectionStatus(
HANDLE hConnection,
DWORD *pdwStatus
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrConnectionStatus(HANDLE hConnection, DWORD *pdwStatus) AKARI_CE_NAME(ConnMgrConnectionStatus);

/* ee497506 ConnMgrEstablishConnection: print `HRESULT WINAPI ConnMgrEstablishConnection(
CONNMGR_CONNECTIONINFO *pConnInfo,
HANDLE *phConnection
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrEstablishConnection(CONNMGR_CONNECTIONINFO *pConnInfo, HANDLE *phConnection) AKARI_CE_NAME(ConnMgrEstablishConnection);

/* ee497602 ConnMgrUnregisterScheduledConnection: print `HRESULT WINAPI ConnMgrUnregisterScheduledConnection(
LPCWSTR pwszToken
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrUnregisterScheduledConnection(LPCWSTR pwszToken) AKARI_CE_NAME(ConnMgrUnregisterScheduledConnection);

/* ee497660 ConnMgrReleaseConnection: print `HRESULT WINAPI ConnMgrReleaseConnection(
HANDLE hConnection,
LONG lCache
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrReleaseConnection(HANDLE hConnection, LONG lCache) AKARI_CE_NAME(ConnMgrReleaseConnection);

/* ee497804 ConnMgrMapConRef: print `HRESULT WINAPI ConnMgrMapConRef(
ConnMgrConRefTypeEnum e,
LPCTSTR szConRef,
GUID *pGUID
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrMapConRef(ConnMgrConRefTypeEnum e, LPCTSTR szConRef, GUID *pGUID) AKARI_CE_NAME(ConnMgrMapConRef);

/* ee497810 ConnMgrMapURL: print `HRESULT WINAPI ConnMgrMapURL(
LPTSTR pwszURL,
GUID *pguid,
DWORD *pdwIndex
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrMapURL(LPTSTR pwszURL, GUID *pguid, DWORD *pdwIndex) AKARI_CE_NAME(ConnMgrMapURL);

/* ee498273 ConnMgrEstablishConnectionSync: print `HRESULT WINAPI ConnMgrEstablishConnectionSync(
CONNMGR_CONNECTIONINFO *pConnInfo,
HANDLE *phConnection,
DWORD dwTimeout,
DWORD *pdwStatus
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT ConnMgrEstablishConnectionSync(CONNMGR_CONNECTIONINFO *pConnInfo, HANDLE *phConnection, DWORD dwTimeout, DWORD *pdwStatus) AKARI_CE_NAME(ConnMgrEstablishConnectionSync);

#endif /* AKARI_CONNMGR_H */
