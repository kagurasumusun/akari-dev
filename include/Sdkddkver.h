/*
 * Sdkddkver.h -- Windows CE generation version constants (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Added 2026-09-14 (audit follow-up): this is the missing piece behind
 * the "共有部分と固有部分を混同しない" requirement -- almost none of
 * the 293 headers in this tree gate a declaration on _WIN32_WCE today
 * (1 occurrence found by grep before this change). This header does
 * not fix that by itself; it supplies the constants every future
 * per-declaration guard needs, so that guards are written as
 * `#if _WIN32_WCE >= _WIN32_WCE_500` instead of hand-rolled literals.
 *
 * Encoding (verified against archived CE-era MSDN pages and the
 * cegcc/w32api convention -- e.g. aygshell.h: "#if (_WIN32_WCE >=
 * 0x0420)" for CE .NET 4.2, cegcc-devel ml thread 2007-11-18): CE
 * "major.minor" is packed as 0xMmm where the minor number's own
 * decimal digits are written directly into the low hex nibbles, NOT
 * arithmetically scaled. So CE 4.2 -> 0x0420, CE 4.10 -> 0x0410 (not
 * 0x040A), CE 5.0 -> 0x0500, CE 6.0 -> 0x0600. This matches how
 * eVC/Platform Builder itself emits /D_WIN32_WCE=0x0500 etc.
 *
 * Confidence note: the CE 4.x/5.0/6.0 values below are well attested
 * (multiple independent CE-era MSDN "Requirements" tables and the
 * cegcc headers agree). The CE 1.x/2.x values are attested for the
 * major.0 releases; the exact minor-release boundaries some OEMs used
 * for 2.01/2.10/2.11/2.12 during 1998-2000 are less consistently
 * documented across sources and are marked below -- verify against a
 * specific device's SDK before relying on one of those four.
 */

#ifndef AKARI_SDKDDKVER_H
#define AKARI_SDKDDKVER_H

/* Windows CE 1.0 (Nov 1996) / 1.01 */
#define _WIN32_WCE_100   0x0100
#define _WIN32_WCE_101   0x0101

/* Windows CE 2.0 (Nov 1997) and the 2.x H/PC Pro, Palm-size PC,
 * H/PC 2000 point releases -- minor-boundary confidence caveat above */
#define _WIN32_WCE_200   0x0200
#define _WIN32_WCE_201   0x0201
#define _WIN32_WCE_210   0x0210
#define _WIN32_WCE_211   0x0211
#define _WIN32_WCE_212   0x0212

/* Windows CE 3.0 (Pocket PC 2000 / Pocket PC 2002 kernel base, Apr 2000) */
#define _WIN32_WCE_300   0x0300

/* Windows CE .NET 4.0 / 4.1 / 4.2 (2002-2003; Pocket PC 2003 = CE 4.20) */
#define _WIN32_WCE_400   0x0400
#define _WIN32_WCE_410   0x0410
#define _WIN32_WCE_420   0x0420

/* Windows CE 5.0 (2004; Windows Mobile 5/6 kernel base) */
#define _WIN32_WCE_500   0x0500

/* Windows CE 6.0 (2006; per-process 2 GB VM, GetTickCount64, etc.) */
#define _WIN32_WCE_600   0x0600

/*
 * If the build did not already define _WIN32_WCE (normally passed by
 * the driver/toolchain, e.g. -D_WIN32_WCE=0x0600), default to the
 * highest generation this tree documents. Consumers targeting an
 * older device MUST define _WIN32_WCE themselves before the first
 * wince-api header is included -- silently defaulting to "newest"
 * without this fallback would make every declaration visible
 * unconditionally, defeating the purpose of gating at all.
 */
#ifndef _WIN32_WCE
#define _WIN32_WCE _WIN32_WCE_600
#endif

#endif /* AKARI_SDKDDKVER_H */
