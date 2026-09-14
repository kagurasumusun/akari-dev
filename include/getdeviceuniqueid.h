/*
 * getdeviceuniqueid.h -- declarations recovered from the official
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

#ifndef AKARI_GETDEVICEUNIQUEID_H_
#define AKARI_GETDEVICEUNIQUEID_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ee488618: page-printed prototype (Windows Embedded CE 6.0 and later; coredll.lib). */
AKARI_CE_IMPORT HRESULT GetDeviceUniqueID(LPBYTE pbApplicationData, DWORD cbApplictionData, DWORD dwDeviceIDVersion, LPBYTE pbDeviceIDOutput, DWORD* pcbDeviceIDOutput) AKARI_CE_NAME(GetDeviceUniqueID);

#endif /* AKARI_GETDEVICEUNIQUEID_H_ */
