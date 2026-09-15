/*
 * Cecap.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: Cecap.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CECAP_H
#define AKARI_CECAP_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ms894342 MarkProfile: print `int MarkProfile(long lMarkID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int MarkProfile(long lMarkID) AKARI_CE_NAME(MarkProfile);

/* ms894396 NameProfile: print `int NameProfile(LPCSTRpszName,intnLevel,DWORDdwID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int NameProfile(LPCSTR pszName, int nLevel, DWORD dwID) AKARI_CE_NAME(NameProfile);

/* ms894925 ResumeProfile: print `int ResumeProfile(int nLevel,DWORDdwID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int ResumeProfile(int nLevel, DWORD dwID) AKARI_CE_NAME(ResumeProfile);

/* ms894960 StartProfile: print `int StartProfile(intnLevel,DWORDdwID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int StartProfile(int nLevel, DWORD dwID) AKARI_CE_NAME(StartProfile);

/* ms894963 StopProfile: print `int StopProfile(intnLevel,DWORDdwID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int StopProfile(int nLevel, DWORD dwID) AKARI_CE_NAME(StopProfile);

/* ms894973 SuspendProfile: print `int SuspendProfile(intnLevel,DWORDdwID);`
 * (Windows CE .NET 4.0 and later.; Link Library: Cecap.lib) */
AKARI_CE_IMPORT int SuspendProfile(int nLevel, DWORD dwID) AKARI_CE_NAME(SuspendProfile);


/* ee480465 CommentMarkProfile: print `int CommentMarkProfile(
long lMarkID,
char* pszText
);`
 * (generation not stated; Link Library: cecap.lib) */
AKARI_CE_IMPORT int CommentMarkProfile(long lMarkID, char *pszText) AKARI_CE_NAME(CommentMarkProfile);

#endif /* AKARI_CECAP_H */
