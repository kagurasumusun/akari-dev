# Akari-dev evidence policy ("clean room") — v3, 2026-09-18

This file is the evidence policy referenced throughout the tree
(`clean-room.md` citations). v3 restates the owner's rules of
2026-09-18 and supersedes v2 (2026-09-17). Where a header comment
cites "clean-room.md §N", the section numbers below apply.

## 1. Scope

Akari-dev provides **only** the Windows CE API surface needed to
build llvm-project against Windows CE targets:

1. Windows CE API headers (`include/`)
2. module export definitions (`def/`)
3. import libraries (built from 2.)
4. startup / toolchain integration (`startup/`)

It is not an SDK and not an OS reimplementation.

## 2. Evidence sources — admissible

* **Official Microsoft Windows CE documentation only** — the MSDN /
  Microsoft Learn / Wayback pages preserved in the companion corpus
  repository `kagurasumusun/wince-docs-corpus`
  (`docs/mslearn/windows-ce-5.0/`, `.../windows-embedded-ce-6.0/`,
  `.../windows-ce-net-4x/`, `docs/chm/windows-ce-3.0/`,
  `docs/wayback-msdn/2010-05/`). Every declaration is annotated with
  the page identifier it is derived from.
* Per-page "Requirements" rows (OS Versions / Header / Link Library)
  govern header placement and `.def` membership.

## 3. Evidence sources — absolutely excluded

Never referenced, investigated, compared against, or copied from:

* Wine, ReactOS, MinGW, mingw-w64, w32api (desktop), mingwrt
  (desktop) — no reference, no investigation, no cross-check, no
  value adoption;
* desktop Win32 analogy ("version invariance" arguments) — desktop
  documentation is not CE evidence;
* shared-source releases, Platform Builder source, Visual Studio
  source;
* unauthorized non-public information, material of unknown
  provenance, illegal sources, and **anything derived from
  binary/device dumps** (the former EXPORT-SURFACE-VERIFIED tier of
  `def/coredll-doc.def` was removed under this rule on 2026-09-18);
* desktop .NET Framework reference material.

## 4. The single exception — CeGCC-lineage value confirmation

The **CeGCC-lineage w32api** ("R1") and the **CeGCC mingwrt** may be
consulted **for value confirmation only** ("値確認・参考程度"):

* permitted: confirming a numeric constant, flag bit, or ABI-ordering
  fact that official CE pages document *by name but not by value*;
  for COM vtables this includes slot *ordering* — where dropping an
  R1-carried middle slot the CE pages do not name would shift the
  layout and break callability, the slot is kept and tagged "(R1)"
  (the M97 banners record this per interface);
* not permitted: copying text, deriving declarations, general name
  sets, prototypes, or struct member *shapes* from R1 — the CE pages
  alone govern names and shapes; where R1 carries flag/constant names
  the CE pages do not list, those names stay excluded (e.g. the
  SKF_CONFIRMHOTKEY / HCF_INDICATOR family, excluded on 2026-09-18).

R1 references used: `cegcc/src/w32api/include/*.h` (CeGCC SVN trunk
mirror).

## 5. Procedure for undocumented values

1. Search the official pages first (all generations in the corpus).
2. If the pages print the name but no value → confirm the value
   against R1 and annotate: *"value confirmed against R1 (value
   confirmation only); names/shapes per the CE pages (ids listed)"*.
3. If R1 does not carry it either → the value stays **held** in
   `docs/unpublished-constants.tsv`; nothing is shipped speculatively.

## 6. Repository hygiene

* Raw Microsoft HTML lives only in `wince-docs-corpus` (attribution:
  Microsoft Learn / Microsoft Corporation, CC BY 4.0); this tree
  carries only transcribed facts and original text.
* Session rule: the corpus clone is deleted from the working
  environment at session end; GitHub is the corpus' home.
