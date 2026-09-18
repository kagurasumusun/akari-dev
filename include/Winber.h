/*
 * Winber.h -- Basic Encoding Rules API for Windows CE (Winber.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Lightweight Directory Access Protocol (LDAP)
 * Client :: LDAP Reference" (the 13 Winber.h function pages of
 * tools/manifests/ldap.manifest); whitespace-preserved prototypes were
 * cross-read against the CE 6.0 (v=winembedded.60) twins
 * (tools/manifests/m54-ce60.manifest).
 *
 * Requirement rows: Header Winber.h, Link Library Wldap32.lib for every
 * page (see def/wldap32-doc.def); OS Versions "Windows CE .NET 4.0 and
 * later".  The BerElement and berval structure pages live in the Winldap.h
 * layer (see winldap.h, ms863747 / ms863826).
 *
 * Quirk recorded once: like winldap.h, the migrated pages print a
 * "UNICODE" marker before PTCHAR parameters ("UNICODE PTCHAR fmt",
 * ms863798 / ms863810) -- the archive's Unicode-only notation, not a C
 * type qualifier (CE is Unicode-only, see windef.h).
 */

#ifndef AKARI_WINBER_H
#define AKARI_WINBER_H

#include "Windef.h"
#include "Winldap.h"    /* BerElement, BERVAL (ms863747 / ms863826) */

#ifdef __cplusplus
extern "C" {
#endif

/* ber_alloc_t flag: "The LBER_USE_DER flag (0x01) should always be
 * specified" (ms863718 ber_alloc_t page text). */
#define LBER_USE_DER     0x01

AKARI_CE_IMPORT BerElement* ber_alloc_t(INT iOptions) AKARI_CE_NAME(ber_alloc_t);                    /* ms863718 */
/* twin-print: ms863725 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863718 lacks the print. */
AKARI_CE_IMPORT BERVAL*     ber_bvdup(BERVAL *pBerVal) AKARI_CE_NAME(ber_bvdup);                   /* ms863725 */
/* twin-print: ms863730 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863725 lacks the print. */
AKARI_CE_IMPORT void        ber_bvecfree(BERVAL **pBerVal) AKARI_CE_NAME(ber_bvecfree);               /* ms863730 */
/* twin-print: ms863737 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863730 lacks the print. */
AKARI_CE_IMPORT void        ber_bvfree(BERVAL *pBerVal) AKARI_CE_NAME(ber_bvfree);                  /* ms863737 */
/* twin-print: ms863754 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863737 lacks the print. */
AKARI_CE_IMPORT ULONG       ber_first_element(BerElement *pBerElement, ULONG *pLen,
                              CHAR **ppOpaque) AKARI_CE_NAME(ber_first_element);           /* ms863754 */
/* twin-print: ms863761 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863754 lacks the print. */
AKARI_CE_IMPORT INT         ber_flatten(BerElement *pBerElement,
                        BERVAL **pBerVal) AKARI_CE_NAME(ber_flatten);                /* ms863761 */
/* twin-print: ms863769 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863761 lacks the print. */
AKARI_CE_IMPORT void        ber_free(BerElement *pBerElement, INT fbuf) AKARI_CE_NAME(ber_free);  /* ms863769 */
/* twin-print: ms863775 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863769 lacks the print. */
AKARI_CE_IMPORT BerElement* ber_init(BERVAL *pBerVal) AKARI_CE_NAME(ber_init);                    /* ms863775 */
/* twin-print: ms863786 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863775 lacks the print. */
AKARI_CE_IMPORT ULONG       ber_next_element(BerElement *pBerElement, ULONG *pLen,
                             CHAR *pOpaque) AKARI_CE_NAME(ber_next_element);              /* ms863786 */
/* twin-print: ms863791 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863786 lacks the print. */
AKARI_CE_IMPORT ULONG       ber_peek_tag(BerElement *pBerElement, ULONG *pLen) AKARI_CE_NAME(ber_peek_tag); /* ms863791 */
/* twin-print: ms863798 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863791 lacks the print. */
AKARI_CE_IMPORT INT         ber_printf(BerElement *pBerElement, PTCHAR fmt, ...) AKARI_CE_NAME(ber_printf); /* ms863798 */
/* twin-print: ms863810 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863798 lacks the print. */
AKARI_CE_IMPORT INT         ber_scanf(BerElement *pBerElement, PTCHAR fmt, ...) AKARI_CE_NAME(ber_scanf);  /* ms863810 */
/* twin-print: ms863817 -- sibling-generation page prints this prototype identically (verified 2026-09-18); cited page ms863810 lacks the print. */
AKARI_CE_IMPORT ULONG       ber_skip_tag(BerElement *pBerElement, ULONG *pLen) AKARI_CE_NAME(ber_skip_tag);   /* ms863817 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINBER_H */
