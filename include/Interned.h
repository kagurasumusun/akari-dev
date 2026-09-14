/*
 * Interned.h -- declarations recovered from the official
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

#ifndef AKARI_INTERNED_H_
#define AKARI_INTERNED_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Objbase.h"   /* BSTR, IUnknown -- the BSTR page (ms886145)
                        * prints the type but no Header row; this tree
                        * carries it in Objbase.h */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* aa451906: page-printed prototype (Windows CE 5.0 and later.). */
#if _WIN32_WCE >= 0x0500   /* Windows CE 5.0 and later. (aa451906) */
HRESULT BeforeWindowOpen(BSTR url, BSTR urlContext, BSTR name, BSTR features, IUnknown* punkEvents);
#endif /* _WIN32_WCE >= 0x0500 */

#endif /* AKARI_INTERNED_H_ */
