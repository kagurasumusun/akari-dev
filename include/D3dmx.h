/*
 * D3dmx.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: d3dmx.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_D3DMX_H
#define AKARI_D3DMX_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "D3dm.h"   /* D3DMFORMAT */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee490107 D3DMXIMAGE_INFO: page print
 * typedef struct _D3DMXIMAGE_INFO { UINT Width; UINT Height; UINT Depth; UINT MipLevels; D3DMFORMAT Format; } D3DMXIMAGE_INFO;
 * (Windows Embedded CE 6.0 and later) */
typedef struct _D3DMXIMAGE_INFO {
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DMFORMAT Format;
} D3DMXIMAGE_INFO;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_D3DMX_H */
