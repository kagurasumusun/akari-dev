/*
 * Kitl.h -- declarations recovered from the official
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

#ifndef AKARI_KITL_H_
#define AKARI_KITL_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms897909: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL KitlInit(BOOL fStartKitl);

/* ms897911: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL KitlSendRawData(LPBYTE pbData, WORD wLength);

/* ms897915: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
DWORD OEMKitlGetSecs(void);

/* ms897917: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
LPBYTE TransportDecode(LPBYTE pbFrame, PUSHORT pcbData);

/* ms897918: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
void TransportEnableInt(BOOL fEnable);

/* ms897919: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL TransportEncode(LPBYTE pbFrame, USHORT cbData);

/* ms897920: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL TransportGetDevCfg(LPBYTE pbBuffer, PUSHORT pcbBuffer);

/* ms897922: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL TransportRecv(LPBYTE pbBuffer, PUSHORT pcbBuffer);

/* ms897923: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL TransportSend(LPBYTE pbFrame, USHORT cbFrame);

/* ms897924: page-printed prototype (Windows CE .NET 4.0 and later.; kitl.lib). */
BOOL TransportSetHostCfg(LPBYTE pbBuffer, PUSHORT pcbBuffer);

#endif /* AKARI_KITL_H_ */
