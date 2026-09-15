/*
 * Bthutil.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: bthutil.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_BTHUTIL_H
#define AKARI_BTHUTIL_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee495609 BTH_RADIO_MODE: page print
 * enum BTH_RADIO_MODE { BTH_POWER_OFF, BTH_CONNECTABLE, BTH_DISCOVERABLE };
 * (Windows CE .NET 4.2 and later) */
typedef enum BTH_RADIO_MODE {
    BTH_POWER_OFF,
    BTH_CONNECTABLE,
    BTH_DISCOVERABLE
} BTH_RADIO_MODE;


/* ee495631 BthGetMode: print `int BthGetMode(
DWORD*
pdwMode
);`
 * (Windows CE .NET 4.2 and later; Link Library: Bthutil.lib) */
AKARI_CE_IMPORT int BthGetMode(DWORD *pdwMode) AKARI_CE_NAME(BthGetMode);

/* ee495834 BthSetMode: print `int BthSetMode(
DWORD
dwMode
);`
 * (Windows CE .NET 4.2 and later; Link Library: Bthutil.lib) */
AKARI_CE_IMPORT int BthSetMode(DWORD dwMode) AKARI_CE_NAME(BthSetMode);

#endif /* AKARI_BTHUTIL_H */
