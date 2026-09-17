# Clean-room definition and scope (investigation result)

This document fixes the meaning of "clean-room" for wince-api (and
wince-crt).  It is the binding interpretation of the requirement:
"公式の公開資料のみ / ライセンスの問題もないように / 自分のライセンス
が持てるように / 第三者のコードをコピー・移植・翻案しない".

## 1. The goal

A Win32-for-CE API package (headers + import libraries) that is a
drop-in replacement for the w32api role of the CeGCC-lineage sysroot
(kagurasumusun/w32api), while being an **independent, original
implementation** whose only spec inputs are (a) official Microsoft
public information and (b) facts observable from the OS/toolchain
itself.  The result is licensed MIT under "Akari API contributors"
copyright — a license the author controls, with no code derived from
GPL/LGPL/public-domain-with-unknown-history third-party packages.

## 2. Why this is legally and practically coherent

* The Win32/CE **interfaces** (names, signatures, constants,
  semantics) are dictated by the OS and its official documentation.
  Facts and functional interfaces are not creative expression;
  Microsoft publishes them precisely so that programs can be written
  against them.  Expressing the same interface in our own words is
  interoperability, not copying (this is the settled position behind
  interface re-implementation; the facts here originate from
  Microsoft's own published docs, so no third-party copyright is
  even implicated).
* What **is** protected in a header package is the *expression*:
  comment text, macro tricks, layout order, naming of private
  helpers, formatting.  None of that is taken from w32api/mingwrt/
  CeGCC; every file is written here from the official pages.
* "Clean-room" as a process therefore means: the implementer works
  from the specification (official docs + OS facts) without copying
  protected code — and the paper trail (this repo's per-declaration
  page IDs in `docs/inventory.md`) demonstrates it.

## 3. Evidence hierarchy (allowed spec sources)

**Policy revision (2026-09-17, user direction; supersedes the
2026-09-10 expansion).**  The allowed spec sources are again
**official public CE material only**:

* Grounds for any declaration, value, type, vtable order, layout or
  export name: official Microsoft CE documentation (Microsoft Learn /
  archived MSDN / the official CE 3.0 Technical Documentation
  archive), and official Win32/PE/COFF/ABI references **for the
  container format only** (never for CE API content).
* Third-party trees (CeGCC-lineage w32api, mingw, Wine, ReactOS, any
  other reimplementation) are **never** grounds -- not for values, not
  for vtable orders, not for existence scoping, and not even as
  "corroboration" of an inference.  Their only permitted use is
  contamination checking (verifying nothing was copied from them) and
  recorded, numbers-and-names-only parity measurement that introduces
  nothing into the tree.
* "It is in desktop Win32 / has been stable since Windows NT" is not
  a CE fact.  A value no CE page prints is *unpublished*: the name is
  recorded as held, per §5.2, and never filled in by analogy.
* Binary observation (device dumps, import libraries extracted from
  OS images) is not official documentation.  The tier-2
  "EXPORT-SURFACE-VERIFIED" entries it produced in
  `def/coredll-doc.def` are legacy under disposition (§7); no new
  name enters the tree on that basis.  Compiler/ABI behavior of the
  verified toolchain (kagurasumusun/llvm-project, branch LLVM-WinCE)
  remains usable for what it is -- facts about our own toolchain,
  not about the CE API surface.
* A specification that cannot be confirmed from official CE material
  is labeled "公式資料で確認できない" (not confirmable from official
  material) and held.  Holds are recorded in
  `docs/unpublished-constants.tsv` / `docs/undeclared-blocked.tsv` /
  `docs/coverage-blocked.tsv`.

**Scope note -- "Windows CE Desktop" (2026-09, user direction).**  The
project targets **Windows CE in all of its configurations**, including
the desktop-like configuration that presents a full GUI desktop
(referred to as "wince desktop").  This is a *Windows CE* platform --
the WinCE OS, coredll, the Unicode-only CE API, the CE ABI -- and is
**not** the desktop Windows (Win32/Win64) API.  "wince desktop" never
licenses bringing Win32/Win64 definitions, values, or APIs into the CE
surface, and the Win32/Win64 restrictions elsewhere in this file are
unchanged.  In the verified toolchain (kagurasumusun/llvm-project,
branch LLVM-WinCE) the CE OS is `windowsce`/`wince` (aliases
`mingw32ce`), a distinct OS from `windows`/`win32`.

1. Official Microsoft public information:
   * CE-era MSDN pages, now `learn.microsoft.com/.../previous-versions/
     windows/embedded/...` — `(v=msdn.10)` (CE 4.x/5.0 API & CRT
     reference; also the older CE 3.0-era `ms9xxxxx` pages) and
     `(v=winembedded.60)` (CE 6.0 Platform Builder/run-time docs).
   * **The official "Windows CE 3.0 Technical Documentation" archive**
     (Microsoft Download Center id 41197; CHM of the retired MSDN
     "Windows CE 3.0" library, © 2004 Microsoft) — the complete CE 1/2/3
     API reference, harvested to corpus `pages3/` / `rows3.json` /
     `docs/ce3-versions.tsv`.  Each page's `Versions: N and later`
     Requirements row is the official minimum-CE-version statement, so
     CE 1.0 / 2.x / 3.0 availability is taken from those rows, never
     from desktop-Win32 analogy.  (archive.org CE 1.x/2.x CD images are
     corroboration-only, see `docs/plan-ce-net.md` §4.)
   * **.NET Compact Framework surface** (for CE 4/5/6): only the
     `.NET Framework 3.5` class-library pages (`previous-versions/dotnet/
     netframework-3.5/ms<ID>(v=vs.90)`) whose "Version Information"
     carries a `.NET Compact Framework → Supported in: N` row (or the CF
     member icon) — per Microsoft's own CF roadmap statement
     (`dn197949(v=winembedded.80)`).  Desktop-.NET members without a CF
     row are **not** part of the CE surface; CF-specific namespaces
     (`Microsoft.WindowsCE.Forms`, `Microsoft.WindowsMobile.*`) are the
     documented CE-side additions.  This is the .NET analogue of the
     "CE is a constrained subset, never desktop by analogy" rule.
   * Microsoft's official Win32/PE/COFF/ABI reference pages.
   * Per-page "Requirements" rows (OS Versions / Header / Link
     Library) are transcribed verbatim into `docs/inventory.md`.
2. Observable facts: ~~the verified export surface of the OS/toolchain
   (device-dump-audited coredll import libraries of the sysroot)~~
   **REMOVED as an API-surface source (2026-09-17, user direction --
   binary dumps are not official documentation; the entries they
   produced are legacy under §7 disposition)**, compiler/ABI behavior
   of the verified toolchain (kagurasumusun/llvm-project, branch
   LLVM-WinCE) -- retained, as facts about our own toolchain.
3. Own design decisions, always labeled *own design* in the
   inventory, never dressed up as documentation.

## 4. Third-party trees: permitted uses

**Policy revision (2026-09-17, user direction; supersedes the
2026-09-10 expansion below).**  The 2026-09-10 permission to adopt
ABI facts from R1 is **REMOVED**.  No third-party implementation --
CeGCC-lineage w32api (R1), mingw, Wine, ReactOS, or any other --
may serve as grounds for a value, vtable order, layout, export name
or existence claim, nor as "corroboration" of a Win32-ABI inference.
Permitted uses are exactly two: **contamination checking** (verifying
this tree copied nothing from them) and **parity measurement recorded
as numbers and names only**, which introduces nothing into the tree.
The material adopted under the 2026-09-10 policy before its removal
is legacy under §7 disposition.  The 2026-09-16 addition of 20
LOCALE_* values to `Winnls.h` on a Wine/ReactOS cross-check was the
first violation of this rule found after it was fixed, and was
retracted on 2026-09-17 (commit d830cab;
`docs/CHANGELOG-audit-2026-09-17.md`).

~~**Policy revision (2026-09-10, user direction; R2 removed same day
by further user direction).**  Sources expanded from "official only"
to *legal, trustworthy, and safe*.  Third-party material is permitted
as an **ABI-fact source** when, and only when, it is in the **public
domain** or carries an equally unproblematic license.~~  (Superseded
2026-09-17; kept as the historical record of what was adopted and
why.)  The former permitted reference set (checked in as read-only
clones outside this repository, never committed):

* ~~**R1 — CeGCC-lineage w32api** (kagurasumusun/w32api, the parity
  target itself).  README: "THIS SOFTWARE IS NOT COPYRIGHTED ...
  offered for use in the public domain".  Exceptions recorded there
  (winsock.h/winsock2.h/ws2tcpip.h BSD Regents/DEC, gl.h Mesa,
  glext.h/glu.h SGI) are used for nothing here -- no value, enum
  order, vtable order or layout fact is taken from those files.~~
  **REMOVED as an ABI-fact source (2026-09-17, user direction).**
  R1 remains the parity-measurement target only (numbers and names,
  `docs/parity-target.md`); values/vtable orders already adopted
  from it are legacy under §7 disposition.
* ~~R2 — mingw-w64 headers~~ **REMOVED** (2026-09-10, user
  direction): mingw-w64 is a *desktop* Win32 ABI source, not a CE
  lineage; spot-checks showed it carrying modern desktop values
  where the CE lineage differs (INTERNET_OPTION_CONTEXT_VALUE 45 vs
  CE 10, INTERNET_LAST_OPTION 0x60 vs CE 0x32, MCN_GETDAYSTATE
  MCN_FIRST+3 vs CE -747).  Adopting from it would corrupt CE
  4/5/6 fidelity.  Nothing was ever adopted from it (checked before
  the first write); it must not be re-added as a source.

Third-party trees may be used for:

* **Contamination checking** — verifying no expression or fact in
  this tree was copied from a third-party implementation.
* **Parity measurement** — recorded as numbers and names only (see
  `docs/parity-target.md`); introduces nothing into the tree.
* ~~**Existence / parity scoping** — as before.~~ (Superseded
  2026-09-17: an existence claim needs an official CE page.)
* ~~**ABI facts** (NEW): numeric constant values, enumeration orders,
  vtable member orders, and structure layouts ... may be *adopted*
  from R1 with per-family provenance recorded in `docs/inventory.md`
  and in the header where they land.~~  **REMOVED (2026-09-17, user
  direction)**: adoption of values/vtable orders/layouts from R1 is
  no longer permitted; a value no official CE page prints is held
  (§3, §5.2).  The *expression* rule is unchanged and was never in
  question: all prose, macro bodies, struct member comments and code
  are written here, not taken from any third-party tree.

**Still forbidden, unchanged**: shared-source / leaked /
unofficially-posted Microsoft material (e.g. Windows CE Shared
Source), anything whose publication or redistribution is legally
problematic, GPL/LGPL-covered expression (~~facts may be corroborated
across sources,~~ code may not), and non-official mirrors of MS
headers as *documentation* evidence.  Official Microsoft pages
~~remain the primary source; R1 fills only the gaps the official CE
pages leave (chiefly: constant values and full vtable orders)~~
**are the only source (2026-09-17); gaps the official CE pages leave
are held, not filled**.

## 5. Process rules

1. Every shipped declaration/constant has a row in
   `docs/inventory.md` naming its official page ID and Requirements.
2. Items not covered by official text are marked *own design* and
   decided from toolchain-observable behavior, never from a
   third-party implementation's behavior alone.  ~~ABI facts adopted
   from the R1 reference under §4 are marked *adopted* with their
   source noted (the "derived values need a recorded path" rule
   extends to adopted values).~~  (2026-09-17: the §4 adoption path
   is closed; no new *adopted* facts.  Existing *adopted* annotations
   stay in place, and are marked, until §7 disposition processes each
   family -- an annotation is a provenance record, and silently
   deleting the record before the value would break traceability.)
   A value no official CE page prints is held and registered in
   `docs/unpublished-constants.tsv`.
3. A file is added to `include/` only after its content is fully
   grounded; partial modules are not shipped half-grounded.
4. No third-party license or copyright text appears anywhere in this
   repository (MIT text is our own).
5. Third-party trees are never committed into this repository; parity
   measurements are recorded as numbers and names only.

## 6. Scope of "own license"

Everything in this repository is © 2026 Akari API contributors, MIT.
The interface parity with w32api creates no derivative-work chain,
because the interface facts come from Microsoft's official
documentation and the OS itself, and the expression is original.
If a future consumer needs the exact binary interface, the def/import
libraries produced here express OS facts (function names) that the OS
itself dictates.

## 7. Legacy adoptions: inventory and disposition (2026-09-17)

Material that entered the tree under the pre-2026-09-17 policies is
legacy.  It is inventoried here; disposition (withdraw-and-hold, or
re-justify from an official CE page where one exists) is tracked per
family and has NOT been executed yet beyond the entries marked done.

Measured scope (grep/inventory counts, 2026-09-17):

| family | source under old policy | measured size | status |
|---|---|---|---|
| `Winnls.h` 20 LOCALE_* values | Wine/ReactOS cross-check + Win32-ABI inference (commit 051ee54) | 20 defines | **DONE -- withdrawn 2026-09-17 (d830cab)** |
| `Winuser.h` accessibility flags + WM_MOUSEMOVE | Wine/ReactOS cross-check (2026-09-14 audit) | 21 defines | listed in `docs/CHANGELOG-audit-2026-09-17.md` §A-2; disposition pending |
| M96 value adoptions | R1 (CeGCC-lineage w32api) | 1,381 defines across 10 headers (inventory M96 totals) | pending |
| M97 vtable adoptions | R1 | COM interfaces made callable from C (Objbase 58, Dshow 15, ...) | pending |
| M99 three-generation sweep adoptions | mixed: official page prints (keep) + R1 values (pending) | per-constant annotations in headers | pending split |
| other R1-annotated constants/types | R1 | 870 annotation lines across 26 headers (grep `R1`/`CeGCC-lineage` in `include/`) | pending |
| def tier-2 entries | device-dump-audited coredll import libraries (corpus `coredll/*.def`) | `def/coredll-doc.def` tier-2 block incl. 75 C++ mangled names | pending (3 Enum*W rows already moved to coreloc per their documented Link Library row, d830cab) |

Disposition principles (fixed 2026-09-17, user direction):

1. Evidence re-examination is per family, from the official corpus --
   where a CE page prints the value/order/layout, the fact stays and
   the annotation is rewritten to cite the page; where no page prints
   it, the fact is withdrawn to held status (name recorded, value
   removed), exactly as the Winnls.h LOCALE_* retraction did.
2. Withdrawn values are never a starting point for re-adoption; an
   official-source re-investigation, if wanted, is a separate task.
3. Downstream consumers (notably llvm-project libcxx WinCE support)
   are reworked to not depend on unpublished values, or to obtain
   them at run time (e.g. via documented APIs) rather than at
   compile time.
4. Every disposition step is recorded in the audit changelog and
   `docs/inventory.md` so that "why was this removed / kept" stays
   traceable in both directions.
