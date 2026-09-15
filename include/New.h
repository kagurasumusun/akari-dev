/*
 * New.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: new.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_NEW_H
#define AKARI_NEW_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ms861451 _set_new_mode: print `int _set_new_mode(intnewhandlermode);`
 * (Windows CE 2.0 and later.; Link Library: coredll.dll) */
AKARI_CE_IMPORT int _set_new_mode(int newhandlermode) AKARI_CE_NAME(_set_new_mode);

#endif /* AKARI_NEW_H */
