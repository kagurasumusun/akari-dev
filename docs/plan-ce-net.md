# Plan: exhaustive CE 1–6 collection + CE 4/5/6 .NET (Compact) Framework + full .NET API surface

Status: **plan / policy** (this is the documented plan the user asked for before
implementation). Milestone M102a is already executed this session; M102b/M102c are
proposed next. `docs/clean-room.md` remains the binding clean-room definition.

## 1. User requirement (paraphrased, binding)

1. CE 1/2/3/4/5/6 の公式ドキュメントを徹底収集する。(4/5/6 は完了済み。)
2. CE 4/5/6 の .NET Framework (= .NET Compact Framework) ドキュメントも収集する。
3. .NET Framework の**完全な API サーフェス**を構築する。
4. Windows CE API はデスクトップ Win32 の（制約された）サブセットであり、
   一部に CE 固有の追加/独自実装（データベース API など）を含む。
5. 実装（wince-api のヘッダ/インポートライブラリ整備）を継続する。

Standing clean-room rules apply unchanged (see `docs/clean-room.md`):
official public sources only; no third-party code; no desktop-Win32/Win64
import by analogy; per-item CE-version evidence required.

## 2. What is already collected (prior milestones)

| Gen | Source | Where |
| --- | --- | --- |
| CE 4.x | Learn `previous-versions/.../embedded` `(v=msdn.10)` | corpus `pages4/`, wince-api `docs/ce4-twins.tsv` |
| CE 5.0 | same tree `(v=msdn.10)` | corpus `pages5/`, `rows.json` |
| CE 6.0 | `(v=winembedded.60)` | corpus `pages6/`, `ce6-twins.tsv` |
| WM 6.5 / Win32 (aux) | Learn | corpus `pageswm/`, `pagesw/` |

## 3. Milestones

### M102a — CE 3.0 (and thus CE 1/2/3) official documentation collection — DONE

CE 1.x/2.x API docs are **not on Learn**. The only complete official reference is
the Microsoft Download Center archive "Windows CE 3.0 Technical Documentation":

* Product page: `https://www.microsoft.com/en-us/download/details.aspx?id=41197`
* Direct archive:
  `https://download.microsoft.com/download/1/3/d/13d0b628-4758-4b87-a9f2-6e98c940e6a9/WindowsCE3.0_DocumentationArchive.zip`
* The zip holds one CHM (13,370,824 B, © 2004 Microsoft) = the retired MSDN
  "Windows CE 3.0" library: **8,962 HTML pages**.

Every API reference page carries a Requirements table with a **`Versions: N and
later`** row (values: `1.0`, `1.01`, `2.0`, `2.01`, `2.1`, `2.10`, `2.11`,
`2.12`, `3.0 and/or later`, incl. DxPAK/MSMQ/Japanese variants). That row is the
official statement of each API's minimum CE version, so the CE 1.0 / 2.x / 3.0
surfaces are derivable **directly from official statements** — no desktop-Win32
analogy anywhere.

Delivered this session (committed & pushed):

* corpus `175fc72c`:
  * `ce30/` — untouched zip + `Important_ReadMe.txt` + `PROVENANCE.md`
  * `pages3/` — all 8,962 raw official HTML pages
  * `catalogs/catalog-windows-ce-30.tsv` — page catalog
  * `rows3.json` — per-page harvest (title / signature / os / **versions** / header / lib)
  * `INDEX.txt` +8,962
* wince-api (this commit):
  * `tools/ce3-collect.py` — CHM→corpus harvest pipeline (7z x → parse → rows)
  * `tools/catalogs/catalog-windows-ce-30.tsv`
  * `docs/ce3-versions.tsv` — the **CE 1/2/3 API surface table**
    (id, title, min_ce, versions, header, lib, os; 5,091 rows with a Versions row)

Surface size by minimum CE version (from `docs/ce3-versions.tsv`):

| min_ce | pages |
| --- | --- |
| 1.0 (incl. 1.01/1.02/1.0-jp/1.9) | ~1,801 |
| 2.0 / 2.01 / 2.1 / 2.10 / 2.11 / 2.12 (incl. jp variants) | ~2,514 |
| 3.0 (+ 4.0 forward) | ~776 |
| **total with a Versions row** | **5,091** |

### M102b — CE 4/5/6 .NET (Compact) Framework documentation collection — PROPOSED

Microsoft's official statement (CF roadmap, Compact 2013):
`https://learn.microsoft.com/en-us/previous-versions/windows/embedded/dn197949(v=winembedded.80)`

> "To see library reference content for the .NET Compact Framework, you should
> access the **.NET Framework Class Library documentation, version 3.5**. Any
> member that is supported in the .NET Compact Framework 3.5 is also supported
> in the .NET Compact Framework 3.9. To determine if a particular member is
> supported in the .NET Compact Framework 3.5, view the Members page for a type
> and look for the mobile phone icon ... or look for the **.NET Compact
> Framework entry in the Version Information section**."

So the official CF API surface is embedded in the **.NET Framework 3.5 class
library** pages on Learn, under `previous-versions/dotnet/netframework-3.5/
ms<ID>(v=vs.90)`. Verified example (member page):

* `https://learn.microsoft.com/en-us/previous-versions/dotnet/netframework-3.5/ms129607(v=vs.90)`
  — `Device.TestCooperativeLevel` (Microsoft.WindowsMobile.DirectX.Direct3D):
  * **Platforms**: `Windows CE, Windows Mobile for Smartphone, Windows Mobile for Pocket PC`
  * **Version Information → .NET Compact Framework → Supported in: 3.5, 2.0**

Plan (policy-compliant, no desktop-.NET import):

0. **Enumeration (done, M103)**: `tools/cf-toc.py` snapshots
   `previous-versions/dotnet/netframework-3.5/toc.json` →
   `tools/catalogs/catalog-netfx-35.tsv` (14,764 leaves, book + path columns).
   The **CF-specific managed reference** ("Additional Managed Reference
   Topics", ms229434) is 7,530 leaves / 20 namespaces, including
   `Microsoft.WindowsCE.Forms`, `Microsoft.WindowsMobile.*`,
   `Microsoft.ServiceModel.Channels.Mail.*`, `Microsoft.Ink`,
   `Microsoft.StylusInput`, `Microsoft.SqlServer.Server`.  The desktop
   `System.*` class library subtree is **not** enumerated in this toc.json
   (migrated to the modern API browser, which drops the CF rows), so part 2
   (the CF-supported desktop subset) is recovered per the archive policy in
   §4.
1. Enumerate the `netframework-3.5` `(v=vs.90)` class-library TOC (reuse the
   existing Learn TOC snapshot technique in `tools/ce-corpus.py`; root anchor
   `w0x726c2(v=vs.90)` works).
2. Harvest every class-library page (types **and** members) that carries a
   `.NET Compact Framework` Version Information row (or the CF member icon),
   plus the CE/WM-specific namespaces (e.g. `Microsoft.WindowsCE.Forms`,
   `Microsoft.WindowsMobile.*`) that document CF-only additions.
3. Save raw HTML to corpus `pagesnet/` (new tree) with the same catalog +
   INDEX discipline; record per page: id, title, namespace, assembly,
   platforms, and the CF "Supported in:" version list.
4. Treat the CF "Supported in: N" row as the **only** evidence that a member is
   in the CE surface. Desktop-.NET-only members (no CF row) are **not** CE.
   This keeps the "CE is a constrained subset, never desktop by analogy" rule
   intact at the .NET level.

Fallback: the old `msdn.microsoft.com/.../library/*(v=vs.90)` pages (which the
Learn `w0x726c2` root still links to) now redirect to the modern API browser
(`/dotnet/api/...`) that **drops** the CF rows; Wayback Machine has snapshots of
the vs.90 pages. Archive.org is therefore a *corroboration* fallback only, and
only after the Learn `previous-versions` harvest is exhausted — the archive
policy for CE 1/2 material is decided below (§4).

### M102c — complete .NET API surface (per CE generation) — PROPOSED

Build `docs/cf-surface.tsv` (id, namespace, kind, name, signature, assembly,
cf_versions, ce_generations) mapping the CF version list to CE generations:

| CF version | Windows CE generation |
| --- | --- |
| CF 1.0 (SP1–SP3) | CE .NET 4.0 / 4.1 / 4.2 |
| CF 2.0 (SP1/SP2) | CE 5.0 / CE 6.0 |
| CF 3.5 | CE 6.0 R3 / Compact 7 (and CE 6.0 via redistributable) |
| CF 3.9 | Compact 2013 (CE 7 lineage) |

Result: a complete, machine-readable .NET API surface for CE 4/5/6, split into
(a) the CF-supported subset of the desktop class library and (b) CF-specific
namespaces. This becomes the spec input for any future managed-API headers and
for the `wince-api` documentation inventory.

### M103+ — implementation continues

With `docs/ce3-versions.tsv` in hand, CE 1.0-era headers can now be grounded
the same way CE 4/5/6 were: each shipped declaration gets a CE 3.0 page ID +
"Versions: 1.0 and later" (etc.) citation in `docs/inventory.md`. CE-specific
additions (database APIs — CEDB/CeCreateDatabaseEx family, RAPI Ce* functions,
CE GDI/user extensions) are collected in the CHM set and implemented from those
pages. CE-version-specific evidence required for every item, per standing rule.

## 4. Archive.org policy (decided here)

* **Primary source** for every claim: official Microsoft pages/archives
  (Learn `previous-versions`, Microsoft Download Center archives such as the
  CE 3.0 CHM). These are always preferred and are sufficient for CE 3.0+.
* **CE 1.0/2.0 era**: the CE 3.0 CHM's "Versions: 1.0 and later / 2.0 and
  later" rows already reconstruct the CE 1/2 surface officially — archive.org
  CD images are **not required** for the API surface. They may be inspected
  only to *corroborate* an item already attested by the CHM, and any such use
  is recorded in `docs/inventory.md` with the snapshot URL. Nothing is adopted
  from archive.org as primary evidence.
* **.NET vs.90 pages**: Learn `previous-versions` first; Wayback snapshots of
  `msdn.microsoft.com` vs.90 pages only as corroboration, recorded per page.

## 5. Environment / pipeline notes

* CHM extraction requires p7zip (`7z x`); this sandbox has it via `p7zip-full`.
  Re-run the pipeline any time from the zip (see `tools/ce3-collect.py` docstring).
* Corpus hygiene (unchanged): save to `wince-docs-corpus`, push, then remove
  local heavy trees; keep small tables inside wince-api (`docs/`, `tools/`).
* Rate/access discipline for the .NET harvest: reuse the corpus first; gentle
  serial fetches; the vs.90 class library is large (≈10^5 member pages), so the
  harvest runs in batches across sessions with the catalog checkpointed.
