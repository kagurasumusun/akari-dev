/*
 * Blcommon.h -- declarations recovered from the official
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

#ifndef AKARI_BLCOMMON_H_
#define AKARI_BLCOMMON_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms902064: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
void BootloaderMain(void);

/* ms903219: page-printed prototype (Windows CE .NET 4.2 and later.; blcommon.lib). */
BOOL OEMCheckSignature(DWORD dwImageStart, DWORD dwROMOffset, DWORD dwLaunchAddr, BOOL bDownloaded);

/* ms903221: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
void OEMContinueEraseFlash(void);

/* ms903224: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMDebugInit(void);

/* ms903226: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMFinishEraseFlash(void);

/* ms903231: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMIsFlashAddr(DWORD dwAddr);

/* ms903233: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
LPBYTE OEMMapMemAddr(DWORD dwImageStart, DWORD dwAddr);

/* ms903236: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMPlatformInit(void);

/* ms903238: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
DWORD OEMPreDownload(void);

/* ms903239: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMReadData(DWORD cbData, LPBYTE pbData);

/* ms903524: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
void OEMShowProgress(DWORD dwPacketNum);

/* ms903525: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMStartEraseFlash(DWORD dwStartAddr, DWORD dwLength);

/* ms903530: page-printed prototype (Windows CE .NET 4.2 and later.; blcommon.lib). */
BOOL OEMVerifyMemory(DWORD dwStartAddr, DWORD dwLength);

/* ms903531: page-printed prototype (Windows CE .NET 4.0 and later.; blcommon.lib). */
BOOL OEMWriteFlash(DWORD dwStartAddr, DWORD dwLength);

#endif /* AKARI_BLCOMMON_H_ */
