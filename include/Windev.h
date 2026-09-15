/*
 * Windev.h -- declarations recovered from the official
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

#ifndef AKARI_WINDEV_H_
#define AKARI_WINDEV_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_IsAPIReady: page-printed prototype (Windows CE OS; coredll.dll). */
AKARI_CE_IMPORT BOOL IsAPIReady(DWORD hAPI) AKARI_CE_NAME(IsAPIReady);


/* ee478525 CTL_CODE: page print
 * #define CTL_CODE( DeviceType, Function, Method, Access) ( ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
 * (generation not stated) */
#define CTL_CODE( DeviceType, Function, Method, Access) ( ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))

#endif /* AKARI_WINDEV_H_ */
