# ISO collection policy — CE 1.0–6.0 (documents only)

User directive (2026-09-14): download one Windows CE ISO per generation
(1.0, 2.x, 3.0, 4.x, 5.0, 6.0), collect the **documents inside** —
**documents only** — and proceed one at a time (download → collect →
delete → next).  Shared Source and any other source/code material is
excluded by explicit instruction, matching the standing clean-room rule.

## 1. Scope rule: documents only, never code

* Collected: documentation artifacts — HTML/CHM/HLP reference, PDF/Word
  white papers, .txt readme/notes — i.e. the *documentation tier*.
* Excluded (deleted, never saved, never read for implementation):
  * Shared Source / source distributions (e.g. the "Windows CE 3.0
    Standard Source Distribution Kit"), any `.c/.h/.cpp/.asm` source,
    sample source, Platform Builder private sources, "internal builds".
  * Binaries are not "documents" either (drivers, OS images, SDK DLLs,
    compilers) — they are ignored/not extracted.
* Documents become the same documentation-tier evidence as the Learn
  pages and the CE 3.0 CHM: they ground declarations; they are never
  used as code to copy.  (The ban on third-party/derived *code* is
  unchanged; documentation facts are not code.)

## 2. Sources and per-version plan

archive.org preserves the official Microsoft CDs.  Chosen items
(one ISO per version; item list recorded with each corpus commit):

| CE | archive.org item (identifier) | ISO | note |
| --- | --- | --- | --- |
| 1.0 | `ms-wince-desktopemulation-sdk-beta21` | WCESDK.iso ~115 MB | **DONE** — CE 1.0 SDK/DDK Books Online (`VCWCE/HELP/`, 13 files → corpus `ce10/`). `msvcceu.100` was toolchain-only (no docs), do not reuse. |
| 2.0 | `Windows_CE_2.0_Technical_Information_Microsoft_1997` | *.iso ~566 MB | **DONE** — MS `windowsce/developer/` mirror, 40 .htm → corpus `ce20/`. (CE 2.0 API Books Online is a separate SDK CD, still sought → `ce2x/`.) |
| 3.0 | `ms-wince-pb30` (Platform Builder 3.0 Evaluation) | DISK1.ISO etc. ~611 MB ea. | **DONE via CHM** — official CE 3.0 reference already collected as CHM (corpus). ISO skipped: multi-disc PB toolchain; no doc-only disc found. |
| 4.x | `winceemul42` (CE .NET 4.2 PB Emulation Ed.) | winceemul42.exe ~542 MB | **DONE** — emulator + remote-tools CHMs + release notes only (`ce42/`). No API reference on any CE 4.x media (eVC 4.0 disc toolchain-only too); CE .NET 4.x API docs come from Learn `pages4/` + MSDN Library VS.NET 2003 (CF 1.0). |
| 5.0 | `en_win_ce_net_cd1` (Windows Embedded CE 5.0 CD1) | en_win_ce_net_cd1.iso ~533 MB | **DONE** — 98 component CHMs (`P3xx_wce*5.chm`, ~33 MB, concepts + API reference) from `PB_1.cab` → corpus `ce50/`. The real CE 5.0 API documentation. |
| 6.0 | `en_windows_embedded_ce_6.0_dvd` (CE 6.0 English) | *.iso ~4.08 GB | **DONE** — no API docs on the DVD (363 CABs = OS catalog/tools/CTK); release notes only → `ce60/`. CE 6.0 API docs come from Learn `pages6/`; CF 3.5 (R3) from `catalog-netfx-35.tsv`. |

**Explicitly excluded** (never downloaded): `windows-ceopen-source`
(CE 3.0 Source Distribution Kit), `shared-source-device-emulator-*`,
`windows-ce-internal-builds` (leaked internals).

## 3. Workflow (one version at a time)

1. `curl -L -C -` the ISO into `/home/user/iso-work/` (transient, **not**
   part of the persisted workspace; 20 GB scratch available).
2. `7z x` to a scratch dir; **inspect the listing only** for document
   formats (`.htm/.html/.chm/.hlp/.pdf/.doc/.txt`).
3. Copy **documents only** into the corpus clone under a per-version dir
   (`ce10/`, `ce20/`, ...) with a `PROVENANCE.md` (item URL, ISO name,
   size, what was kept/skipped).
4. Commit + push the corpus; record the run in `docs/inventory.md`.
5. Delete the ISO and the extraction (scratch) before the next version.

## 4. Relationship to the other tracks

* The CE 1.0/2.0 documents recovered here fill the only gap in the
  CE 1/2/3 surface (which the CE 3.0 CHM's "Versions: N and later" rows
  already enumerate officially).
* The CE 4.x/5.0/6.0 Platform Builder discs may contain the **.NET
  Compact Framework 1.0 / 2.0** documentation (CE 4.x shipped CF 1.0,
  CE 5.0 shipped CF 2.0), which Learn no longer carries — this closes
  the CF 1.0/2.0 half of the .NET API surface (M102c).
* The non-.NET (native) API surface continues from `docs/ce3-versions.tsv`
  and the M103 batches.

## 5. Runs (corpus commits, 2026-09-14)

| CE | corpus dir | corpus commit |
| --- | --- | --- |
| 1.0 | `ce10/` (Pegasus SDK+DDK Books Online, 13 files) | `a94b2995` |
| 2.0 | `ce20/` (Technical Information CD, 40 .htm) | `8009285a` |
| 3.0 | CHM set (collected earlier) | — |
| 4.x | `ce42/` (emulator/remtools CHMs + notes) | `418246e2` |
| 5.0 | `ce50/` (98 component CHMs) | `4486f35c` |
| 6.0 | `ce60/` (release notes; no API docs on disc) | `c3fac771` |

All source media deleted after collection (`iso-work/` is empty).
