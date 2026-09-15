/*
 * Formatdisk.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: Formatdisk.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_FORMATDISK_H
#define AKARI_FORMATDISK_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ms890480 FormatVolumeUI: print `VOID FormatVolumeUI(
HANDLEhVolume,HWNDhWnd);`
 * (Windows CE .NET 4.0 and later.; Link Library: Fatutil.dll) */
AKARI_CE_IMPORT VOID FormatVolumeUI(HANDLE hVolume, HWND hWnd) AKARI_CE_NAME(FormatVolumeUI);

#endif /* AKARI_FORMATDISK_H */
