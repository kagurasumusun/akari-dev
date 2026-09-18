/*
 * Msr.h -- declarations recovered from the official page prints.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own print (page id
 * cited); docs/absent-funcprints-2026-09-18.tsv records the audit
 * pass that found these coredll-exported functions undeclared.
 */

#ifndef AKARI_MSR_H_
#define AKARI_MSR_H_

#include "Windef.h"    /* base Win32 types */

/* ms904867(v=msdn.10) NKrdmsr: page print `BOOL NKrdmsr(DWORDdwAddr,DWORD*lpdwValHigh,DWORD*lpdwValLow);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL NKrdmsr(DWORD dwAddr, DWORD*lpdwValHigh, DWORD*lpdwValLow) AKARI_CE_NAME(NKrdmsr);

/* ms904875(v=msdn.10) NKwrmsr: page print `BOOL NKwrmsr(DWORDdwAddr,DWORDdwValHigh,DWORDdwValLow);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL NKwrmsr(DWORD dwAddr, DWORD dwValHigh, DWORD dwValLow) AKARI_CE_NAME(NKwrmsr);

#endif /* AKARI_MSR_H_ */


