/*
 * Pwinbase.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_PWINBASE_H_
#define AKARI_PWINBASE_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms902891: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT void FileSystemPowerFunction(DWORD dwflags) AKARI_CE_NAME(FileSystemPowerFunction);

#endif /* AKARI_PWINBASE_H_ */
