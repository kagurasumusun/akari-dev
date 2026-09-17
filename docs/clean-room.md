# Evidence policy and clean-room rules — v2

**Fixed by user direction, 2026-09-17 (second revision of the day).**
This document replaces `clean-room.md` v1 **in its entirety**: the
original 2026-09 text, the 2026-09-10 "permitted reference set"
revision (R1/R2), and the earlier 2026-09-17 "B-1" revision are all
withdrawn.  Per the same direction, every convention or policy
statement previously written into this repository's headers and
documents is a past incorrect setting and is re-established by the
rules below; §5 is the withdrawal ledger.  Git history preserves all
earlier texts.

## 1. Source rules

### 1.1 Priority investigation targets

1. **Official Microsoft material — top priority.**  MSDN / Microsoft
   Learn (including the `previous-versions/windows/embedded` CE pages,
   `(v=msdn.10)` and `(v=winembedded.60)`), official archives (e.g.
   the "Windows CE 3.0 Technical Documentation" archive, Microsoft
   Download Center id 41197), and Wayback captures **of official
   pages**.  Per-page Requirements rows (OS Versions / Header / Link
   Library) are transcribed into `docs/inventory.md`.
2. **Major, reliable, legal public information that is not official**
   (公式ではないが大手の信頼できる合法の公開情報) — an allowed
   investigation target, secondary to official material.  Where such a
   source grounds a shipped fact, the record names the source and
   marks it as non-official.

### 1.2 CeGCC lineage — reference, comparison and value confirmation only

CeGCC, the CeGCC-edition mingwrt, and the CeGCC-lineage w32api
(kagurasumusun/w32api, the "R1" parity target) may be used as
**reference, comparison and value-confirmation targets**
(参考・比較・値確認対象) — and to that extent only:

* **No code is copied from them, ever.**  No expression either:
  prose, comments, macro bodies, member orders as *layout choices*,
  formatting — all expression in this repository is written here.
* A candidate fact (constant value, enumeration order, vtable member
  order, structure layout) may be **confirmed** against the CeGCC
  lineage where official pages do not print it.  The inventory record
  then cites the official page for the declaration/name **and** notes
  the CeGCC-lineage value confirmation, so a value-confirmed fact is
  never presented as an officially printed one.
* Parity measurement against the CeGCC-lineage w32api remains allowed
  as comparison, recorded as numbers and names only
  (`docs/parity-target.md`); it introduces nothing into the tree by
  itself.

### 1.3 Never — excluded absolutely

* **No code copying from any of**: CeGCC, mingw, mingw-w64,
  mingw-w32, mingwrt, Wine, ReactOS, w64api, w32api.
* **No reference and no investigation at all** (参考も調査も一切しない)
  of: mingw, mingw-w64, mingw-w32, Wine, ReactOS, w64api, and
  non-CeGCC w32api.  These are not comparison targets, not
  corroboration, not "sanity checks" — they are out of scope for
  every activity in this repository.
* **Shared Source, Visual Studio internal/semi-internal material,
  Platform Builder material**: never investigated, never referenced.
* **Leaked or comparable unofficial material** (非公式・流出に類する
  もの): excluded.
* **Desktop Win32/Win64 analogy**: "present in Win32" is not evidence
  for CE.  CE facts come from CE sources (§1.1, §1.2).
* **Binary observation** (device dumps, import libraries extracted
  from OS images) is not one of the source categories this direction
  establishes.  Entries previously grounded on it are legacy (§4/§5);
  no new name or value enters the tree on that basis.

## 2. WinCE-specific mechanisms first

The WinCE support in llvm-project's libc/libc++ — and consumers of
this SDK generally — must **connect to WinCE's own mechanisms**.
Where the WinCE API provides a facility, the WinCE-provided facility
is used instead of a generic C (or desktop-Windows) substitute.

Worked example (the case that prompted this revision): **Windows CE
provides its own NLS** — the officially documented National Language
Support surface (GetLocaleInfo/SetLocaleInfo, the Enum* NLS
functions, CompareString, LCMapString, GetStringType*, Coreloc.lib;
declared in `include/Winnls.h` from those pages).  The libc++ WinCE
locale backend must obtain locale data through that WinCE NLS
mechanism.  The former convention "the C runtime a Windows CE image
links against provides the classic 'C' locale and no locale tables
besides it" (libcxx `__locale_dir/support/wince.h` top note, and the
C-locale-only `__localeconv` rework it motivated, llvm-project
cc5c872a8) is **withdrawn as factually wrong**; the backend is to be
reworked onto WinCE NLS, with the LCTYPE/LCID constant values it
needs re-verified under §1 (official first; CeGCC-lineage value
confirmation where official pages print names only).

## 3. Process rules

1. Every shipped declaration/constant has a row in
   `docs/inventory.md` naming its evidence: official page IDs first,
   non-official-but-allowed sources marked as such (§1.1.2),
   CeGCC-lineage value confirmations marked as such (§1.2), own
   design labeled *own design* — never dressed up as documentation.
2. A candidate value that no allowed source confirms is **not
   guessed**: it is marked "公式資料で確認できない" / unconfirmed and
   held in `docs/unpublished-constants.tsv`,
   `docs/undeclared-blocked.tsv` or `docs/coverage-blocked.tsv`.
3. CE generations (1.x/2.x/3.0, 4.x, 5.x, 6.x) are never conflated;
   version guards follow each page's Requirements row.
4. A file enters `include/` only after its content is fully grounded;
   partial modules are not shipped half-grounded.
5. Types, constants, structs, prototypes, macros and ABI are verified
   — not just comments and licenses.
6. Third-party trees are never committed into this repository; no
   third-party license or copyright text appears anywhere here
   (everything is © 2026 Akari API contributors, MIT, original
   expression).
7. Claims made by this repository's own documents (or anyone's
   write-ups) are not evidence; every fact is checked against the
   sources in §1 directly.

## 4. Legacy annotations — reading key

Header annotations citing superseded policies stay in place as
provenance records until the per-family re-verification runs; under
this policy they read as follows:

* **"clean-room.md §4 / par.4 revision 2026-09-10 / R1 adoption /
  M96·M97·M99 value adoption"** (870 annotation lines across 26
  headers; M96's 1,381 defines; the M97 vtable orders): these values
  came from the CeGCC-lineage w32api.  CeGCC-lineage value
  confirmation **is** allowed under §1.2, so they are not policy
  violations; they are, however, not yet re-verified official-first.
  Re-verification per family: where an official page prints the
  value/order, cite the page; where it does not, restate the record
  as a §1.2 value confirmation; where neither holds, hold the value.
* **"clean-room.md §3.2 / tier-2 / device-dump-audited"** (the
  `def/coredll-doc.def` tier-2 block, including its 75 C++ mangled
  names): binary observation is not a source category (§1.3); these
  entries are legacy pending disposition.
* **The 20 withdrawn `Winnls.h` LOCALE_\* values** (retraction commit
  d830cab): the retraction executed under the withdrawn v1
  official-only rule.  Its finding that the recorded justification
  cited Wine/ReactOS — an absolutely excluded tree (§1.3) — stands.
  Under v2 the values become **re-verification candidates**: the
  official pages print their names only (corpus-verified), so a
  §1.2 CeGCC-lineage value confirmation can ground them.  They stay
  withdrawn until that confirmation is run and recorded; nothing is
  restored speculatively.
* **The 21 `Winuser.h` accessibility/WM_MOUSEMOVE values** (A-2
  ledger) and the **21 `Winnls.h` Win32-ABI-inferred values**
  (CP_*/MB_*/WC_*/CT_*/LCID_*/MAX_DEFAULTCHAR): the recorded
  groundings (Wine/ReactOS cross-check; desktop-Win32 analogy) are
  and remain inadmissible (§1.3).  Both families await
  re-verification under §1 (official first, CeGCC-lineage value
  confirmation second).

## 5. Withdrawal ledger (旧規約文書の撤回)

Withdrawn/superseded 2026-09-17 by user direction ("cellvm-sdk に
配置されている .h やドキュメント内に記述されている規約や方針はすべて
過去の誤った設定である"):

| doc / location | former convention | status under v2 |
|---|---|---|
| `clean-room.md` v1 (original + 2026-09-10 R1/R2 revision + 2026-09-17 B-1 revision) | evidence hierarchy: official-only (B-1); R1 ABI-fact adoption (2026-09-10); device-dump tier (§3.2) | wholly replaced by this v2 |
| `docs/plan-ce-net.md` ("Standing clean-room rules apply unchanged"; "clean-room.md remains the binding clean-room definition") | points at v1 as binding | banner added; binding policy is this v2 |
| `docs/parity-target.md` | parity measurement under v1 §4 adoption policy | survives as §1.2 comparison/value-confirmation; banner added |
| `docs/ce-not-nt.md` ("a clean-room w32api replacement can reuse Win32 names/shapes…") | v1-era claim | banner added; desktop-Win32 analogy stays excluded (§1.3) |
| llvm-project `libcxx/include/__locale_dir/support/wince.h` top note + `locale_wince.cpp` design note (cc5c872a8) | "CE provides only the classic C locale and no locale tables" | withdrawn as factually wrong (§2); comments rewritten; NLS rework pending |
| `include/Winuser.h` 2026-09-14 audit block | Wine/ReactOS cross-check cited as grounding | citation withdrawn; values pending re-verification (§4) |
| `include/Winnls.h` retraction record ("re-adoption … independent official-source investigation only") | v1 official-only re-adoption path | updated to the v2 re-verification path (§4) |
| M96/M97/M99 and R1-annotation families, tier-2 defs | v1-adopted evidence | legacy under the §4 reading key, pending re-verification |

## 6. Own license

Everything in this repository is © 2026 Akari API contributors, MIT.
All expression is original; all facts come from the §1 sources and are
recorded per §3.  No derivative-work chain exists to any third-party
tree because nothing is copied from any (§1.2, §1.3).  The
def/import libraries express OS-dictated function names; interface
parity with the CeGCC-lineage w32api is measured as numbers and names
only.
