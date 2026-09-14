/*
 * Htmlctrl.h -- declarations recovered from the official
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

#ifndef AKARI_HTMLCTRL_H_
#define AKARI_HTMLCTRL_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcesdk_InitHTMLControl: page-printed prototype (Windows CE OS). */
BOOL InitHTMLControl(HINSTANCE hinst);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* _wcesdk_NM_HTMLCONTEXT: page-printed definition (Windows CE OS). */
typedef struct tagNM_HTMLCONTEXT {
    NMHDR hdr;
    POINT pt;
    UINT uTypeFlags;
    LPSTR szLinkHREF;
    LPSTR szImageSrc;
    HBITMAP hbmImage;
    DWORD dwImageCookie;
} NM_HTMLCONTEXT;

/* _wcesdk_NM_HTMLVIEW: page-printed definition (Windows CE OS). */
typedef struct tagNM_HTMLVIEW {
    NMHDR hdr;
    LPSTR szTarget;
    LPSTR szData;
    DWORD dwCookie;
} NM_HTMLVIEW;

#endif /* AKARI_HTMLCTRL_H_ */
