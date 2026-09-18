/*
 * Pwindbas.h -- declarations recovered from the official
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

#ifndef AKARI_PWINDBAS_H_
#define AKARI_PWINDBAS_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Cesync.h"   /* HREPL (Repl* declarations) */
#include "Windbase.h"   /* 1 declaration(s) whose official pages print
                    * "Header: Pwindbas.h" are carried there, so including it
                    * makes <Pwindbas.h> provide them as those pages promise
                    * (docs/header-placement-audit.md). */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* GetSystemMemoryDivision moved to Winbase.h in M134: ms885639 prints
 * "Header: windows.h" and "Link Library: Coredll.lib", so it is app-layer
 * surface, not Platform Builder surface.  This header still reaches it
 * through Windbase.h -> Winbase.h. */

/* _wcepb_SetSystemMemoryDivision: page-printed prototype (Windows CE OS). */
/* ee482768: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD SetSystemMemoryDivision(DWORD dwStorePages) AKARI_CE_NAME(SetSystemMemoryDivision);


/* --- absent-surface pass 2026-09-18: coredll-exported functions
 * whose pages print "Header: Pwindbas.h" + "Link Library: Coredll.lib"
 * (docs/absent-funcprints-2026-09-18.tsv). --------------------- */

/* REPLCHANGEINFO: no CE page prints the definition (corpus-wide search
 * 2026-09-18); the Repl* prototypes only pass pointers, so the name is
 * forward-typedef'd, never invented. */
typedef struct REPLCHANGEINFO REPLCHANGEINFO;

/* ms891473(v=msdn.10) ReplChangeSyncSettings: page print `BOOL ReplChangeSyncSettings(HREPL hRepl,DWORDdwSyncFlags,LPDWORDlpdwOldFlags);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplChangeSyncSettings(HREPL hRepl, DWORD dwSyncFlags, LPDWORD lpdwOldFlags) AKARI_CE_NAME(ReplChangeSyncSettings);

/* ms891474(v=msdn.10) ReplCheckpoint: page print `BOOL ReplCheckpoint(HREPL hRepl,DWORDdwReserved);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplCheckpoint(HREPL hRepl, DWORD dwReserved) AKARI_CE_NAME(ReplCheckpoint);

/* ms891698(v=msdn.10) ReplCloseSync: page print `BOOL ReplCloseSync(HREPL hRepl);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplCloseSync(HREPL hRepl) AKARI_CE_NAME(ReplCloseSync);

/* ms891775(v=msdn.10) ReplFindNextChange: page print `BOOL ReplFindNextChange(HREPL hRepl,REPLCHANGEINFO* lpChangeInfo,BOOLfRestart);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplFindNextChange(HREPL hRepl, REPLCHANGEINFO*lpChangeInfo, BOOL fRestart) AKARI_CE_NAME(ReplFindNextChange);

/* ms891783(v=msdn.10) ReplGetOidStatus: page print `BOOL ReplGetOidStatus(HREPL hRepl,CEOIDoid,REPLCHANGEINFO* lpChangeInfo);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplGetOidStatus(HREPL hRepl, CEOID oid, REPLCHANGEINFO*lpChangeInfo) AKARI_CE_NAME(ReplGetOidStatus);

/* ms891797(v=msdn.10) ReplGetSyncState: page print `BOOL ReplGetSyncState(HREPL hRepl,LPBYTElpSyncState,LPDWORDlpdwSize,BOOLfFailIfUnchanged);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplGetSyncState(HREPL hRepl, LPBYTE lpSyncState, LPDWORD lpdwSize, BOOL fFailIfUnchanged) AKARI_CE_NAME(ReplGetSyncState);

/* ms891805(v=msdn.10) ReplOpenSync: page print `BOOL ReplOpenSync(CEGUID* pguid,LPBYTElpSyncState,DWORDdwSize,DWORDdwSyncFlags,HREPL* phRepl);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReplOpenSync(CEGUID*pguid, LPBYTE lpSyncState, DWORD dwSize, DWORD dwSyncFlags, HREPL*phRepl) AKARI_CE_NAME(ReplOpenSync);

#endif /* AKARI_PWINDBAS_H_ */
