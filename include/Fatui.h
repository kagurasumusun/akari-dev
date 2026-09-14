/*
 * Fatui.h -- Windows CE FAT file system UI (FATUI) header of record.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive; page
 * ids cited per record).  Sources (all "Microsoft Windows CE 3.0",
 * Header: Fatui.h; the full book is the FATUIEvent/FATUIDATA pair used
 * by the file-allocation-table UI hook):
 *   * pages3/_wcepb_UIPARAM.html
 *   * pages3/_wcepb_FATUIDATA.html
 *   * pages3/_wcepb_FATUIEvent.html
 *
 * UIPARAM's page prints its two members separated by a comma
 * (`struct _UIPARAM { DWORD dwType , DWORD dwValue };`) where every
 * other structural page of the same book uses the C member separator.
 * The verbatim print is recorded above each declaration; the compiled
 * form uses the separator that makes the printed member list legal C
 * (no member, type or layout is added or changed).
 */

#ifndef AKARI_FATUI_H
#define AKARI_FATUI_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------
 * FATUI event interface (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */

/* _wcepb_UIPARAM UIPARAM: print
 *   `struct _UIPARAM { DWORD dwType , DWORD dwValue };`
 * ("This structure contains event data and type information.") */
typedef struct _UIPARAM {
    DWORD dwType;
    DWORD dwValue;
} UIPARAM;

/* _wcepb_FATUIDATA FATUIDATA: print
 *   `struct _FATUIDATA { DWORD dwSize ; DWORD dwFlags ; DWORD idsEvent ;
 *    DWORD idsEventCaption ; DWORD cuiParams ; UIPARAM auiParams [4]; };
 *    typedef struct _FATUIDATA FATUIDATA, *PFATUIDATA;`
 * ("This structure retains all information necessary for the processing
 * of a file allocation table (FAT) file system disk event.") */
typedef struct _FATUIDATA {
    DWORD   dwSize;
    DWORD   dwFlags;
    DWORD   idsEvent;
    DWORD   idsEventCaption;
    DWORD   cuiParams;
    UIPARAM auiParams[4];
} FATUIDATA, *PFATUIDATA;

/* _wcepb_FATUIEvent FATUIEvent: print
 *   `int FATUIEvent ( HANDLE hModule , PCWSTR pszVol , PFATUIDATA pfui );`
 * ("Implement this function to receive events of file allocation table
 * (FAT) file system scans and disk formatting.") -- an application-
 * supplied entry point, so it is declared here without an import
 * binding (the page publishes no Link Library row). */
int FATUIEvent(HANDLE hModule, PCWSTR pszVol, PFATUIDATA pfui);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_FATUI_H */
