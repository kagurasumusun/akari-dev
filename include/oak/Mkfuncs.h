/*
 * Mkfuncs.h -- kernel memory-management functions for Windows CE (OAL).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * "Mkfuncs.h" is printed in the Requirements row of the function pages
 * below and named by the "nk Module" pages (ms923602 / ee482339) among
 * the headers defining the nk module's configuration functions.  No
 * declaration below is live yet: each print names a type no CE page
 * prints a definition for, so both stay in the record-only section per
 * the tree policy (see include/oak/Ndis.h "Record-only" note).
 */
#ifndef AKARI_MKFUNCS_H
#define AKARI_MKFUNCS_H

/* --- Record-only: function prints naming types no CE page prints. -- */
/* Declared once the missing type gains a grounded print. */

/* "RegisterDirectMethods" (ee482823; Windows Embedded CE 6.0 and
 * later; Header: mkfuncs.h): print
 * `BOOL RegisterDirectMethods ( HANDLE hApiSet, const PFNVOID
 * *ppfnDirectMethod );` -- PFNVOID is used by the CeLogExportTable
 * (ms903991 / ee478217), OEMGLOBAL (ee478176) and NKSetDataAbortHandler
 * (ms904873) prints but no CE page prints its typedef. */

/* "VirtualSetAttributesEx" (ee488757; Windows Embedded CE 6.0 and
 * later; Header: mkfuncs.h; Library: coredll.lib): the page's Syntax
 * block prints the NON-Ex prototype
 * `BOOL VirtualSetAttributes ( LPVOID lpvAddress, DWORD cbSize, DWORD
 * dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags );` and its Remarks
 * say "For more information, see VirtualSetAttributes" -- an archive
 * artifact; the Ex signature is not printed by any CE page.  The
 * non-Ex VirtualSetAttributes is declared in Pkfuncs.h from its own
 * pages (aa450982 / ee482857, Header: Pkfuncs.h). */

#endif /* AKARI_MKFUNCS_H */
