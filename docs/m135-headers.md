# M135 -- shipping the 36 headers the pages name but `include/` did not have

## What was wrong

`tools/coverage-audit.py` had been reporting **1,054 records** in its "header
not shipped here" bucket: official pages naming a header that `include/` did
not contain.  No audit downstream could act on those records, because there
was no file to put a declaration in.  `xamlruntime.h` (114), `wsdapi.h` (100),
`d3dmx.h` (95), `extapi.h` (44), `simmgr.h` (38), `cs.h` (36), `sms.h` (36)
were the largest.

## What shipped

`sh tools/ship-pipeline.sh` reproduces the whole of it from a clean tree.

| | before | after |
|---|---|---|
| headers in `include/` (`Makefile` `HDRS`) | 271 | **307** |
| "header not shipped here" | 1,054 | **307** |
| "already declared" | 454 | **752** |
| app-layer gaps | 163 | 550 |
| documented libraries with no `def` | 66 | **15** |

36 new headers, 263 declarations transcribed from their pages, plus 44 more
declarations written into 24 existing headers by the gap pass.  Every one
carries its page id, the page's own print, its OS Versions row and its Link
Library row.

`make check` EXIT=0 (headers + TU, C and C++, at `_WIN32_WCE` 0x420 / 0x500 /
0x600).  `make e2e` EXIT=0 -- 6 WinCE targets linked against the doc-derived
import libraries.  `tools/gen-audit.py`: 0 unguarded names.
`tools/placement-audit.py`: 65 groups, 848 names, **0 unreachable**.

App-layer gaps rose 163 -> 550 because records that used to stop at "no file
to put this in" now reach the buckets below it.  That is the audit getting
more precise, not coverage regressing.

## Generation gating

19 of the 36 headers declare nothing before CE 6.0, so
`tools/gate-new-headers.py` wraps their declarations in
`#if _WIN32_WCE >= 0x0600`, derived from each block's own OS Versions row
through `tools/gen-guard.py`'s `OS_VERSIONS` map (extended this milestone with
the `Windows Embedded CE 6.0 R2` and `R3` rows, which both map to 0x0600 --
the encoding has no R2/R3 field).

The gate goes *after* the includes.  A whole-file gate placed above them makes
the header empty at a lower generation while its includers still expect the
names: `include/D3dm.h` is gated at 0x0500, which is why `D3dmx.h` lost
`D3DMFORMAT` at 0x420 until it got a gate of its own.

## Pipeline ordering, and why it is that order

Recorded in `tools/ship-pipeline.sh`, which is the runnable form of this
section.

1. **`coverage-audit.py` first.**  `ship-missing-headers.py` reads the audit's
   "header not shipped here" bucket.  A stale `coverage.json` still says a
   header that was just deleted is covered, and the run ships nothing
   (measured: 1 header instead of 36).
2. `ship-missing-headers.py --passes 3` -- a fixpoint, because a type declared
   in pass 1 unblocks the declarations that use it in pass 2.
3. `add-header-includes.py` -- before the gate, so the includes stay outside it.
4. `gate-new-headers.py` -- before the gap pass, because the transcribers
   insert relative to the gate's `#endif`.
5. `coverage-audit.py` again -- step 2 moved ~750 records into the buckets
   below, and the residue is what step 6 works on.
6. `gap-pass.py` -- every remaining app-layer gap whose header now exists,
   offered to **both** transcribers.  Splitting them by "does the page print a
   Link Library" sends the `sms.h` and `tsp.h` enum pages, which do print one,
   to the function transcriber, where they are rejected as "page has no
   prototype block".
7. `add-header-includes.py` again, for what step 6 added.
8. `merge-hdrs.py` -- `HDRS` must equal `include/`'s contents.  A header not in
   `HDRS` is compiled by neither `hostcheck` nor `crosscheck`, so `make check`
   stays green while the header is broken.  The 33 first-generation M135
   headers sat uncompilable for a whole run this way.

## Rule changes this milestone forced

Each of these was found by a compile failure, not by inspection.

- **`decl-{from,types}-from-pages.py` skip a name the tree already declares.**
  Without it a rerun writes every declaration twice: the second gap pass added
  a second `IMAGE_DATA_DIRECTORY` to `Winnt.h` and a second `COMPOSITIONSTRING`
  to `Imm.h`.
- **Insert before the innermost region's `#endif`:** generation gate, then the
  `__cplusplus` region, then the include guard.  After the guard, `Cs.h`
  compiled with its gated includes switched off and lost `ULONG` and `GUID`;
  in `Scrollview.hpp`, `ScrollBarInfoInternal` landed where the
  `enum SCROLL_STATE` at line 35 was out of scope.
- **A page that prints `Link Library: none.` declares nothing.**  ms860404
  (`StringCbGetsEx`) prints an explicit none where its 29 siblings print
  `strsafe.lib`.  Nothing exports the name, so no `AKARI_CE_IMPORT` is
  admissible and no `def` may list it.
- **An enum whose enumerators collide with a shipped macro is held.**
  `#define olNormal 0` (from aa513746) turns `olNormal = 0,` inside
  `enum OlSensitivity` (ee483685) into `0 = 0,`.  The same constants reach this
  tree in two official spellings; the shipped macro spelling wins, and 9 of the
  10 CE 6.0 Pocket Outlook enums are held on that ground.
- **A bare `enum X { … };` is also declared as a typedef.**  The tag alone
  cannot be used as a type, yet the consuming pages do exactly that: ee497177
  prints `CALLER_ID_OPTIONS cidoOptions;` for the enum ee497030 defines with no
  typedef.
- **`add-header-includes.py` counts only names in type position, and indexes
  only real declarations.**  Reading every identifier pulled in parameter names
  (`pCaps`, `pv`, `dwSize`), each of which is also a typedef somewhere else in
  the tree, so `Winnt.h` grew an `#include` of `Shellcb.h` and the build
  deadlocked on an include cycle.  `const` had to sit outside the capture
  group too: inside it, `const SYSTEMTIME *ptsCurrentTime` yielded the single
  token `const SYSTEMTIME`, which no header declares, and `Sms.h` never got its
  `Winbase.h` include.
- **`Tchar.h` takes `TCHAR` / `PTCHAR` / `PCTSTR` / `LPCTSTR` / `PTSTR` /
  `LPTSTR` from `Windef.h`** instead of redeclaring them.  Redeclaring made it
  un-includable next to `Windef.h` -- "conflicting types for `TCHAR`" -- so
  nothing in the tree could reach `PCTSTR`, which `LoadIconW_I` (aa453412)
  prints.  `Windef.h` now declares `PCTSTR` beside `LPCTSTR`, in the same
  category as the `PTCHAR` / `PWCHAR` / `PCHAR` documentation pointer forms it
  already carried.  Both include orders compile in C at 0x420 and 0x600 and in
  C++.
- **`gen-doc-def.py` is dry-run unless `--write` is passed**, and takes
  `--outdir`.  It deletes `def` files it cannot reproduce, and it does not
  reproduce every committed one (`ddi_*`, `conshid_lib`); invoking it with
  `--help` deleted 9 committed defs before this guard existed.

## Held, with reasons

- **15 documented libraries still have no `def`** -- `wsdapi` (83 documented
  names), `d3dmx` (48), `cellcore` (32), `phcommon` (18), `sms` (12),
  `cardea_wince` (6), `fatutil` (6), `ppp` (5), `loadauth` (4), `gpsapi` (2),
  `cecap` (2), `shdocvw` (2), `tileengine` (1), `certmod` (1), `drm_nd_oem` (1).
  Measured: **none of their documented names is declared by any header**, so a
  `def` would offer import symbols with no declaration behind them.  Their
  headers now exist; what is missing is the declarations, and their pages print
  nothing this tree can transcribe.
- **`RMLEN`, `PWLEN`, `DNLEN`, `UNLEN`** appear only as array sizes inside
  other pages' struct prints (`WCHAR LocalName[RMLEN + 10]`).  No CE page
  prints a `#define` for any of them and no coverage record names them, so no
  value is admissible.  They block `ADDCONNECT_DLGPARAMS`, `NETUI_RESPWD`,
  `NETUI_USERPWD`, `NETUI_NEWPWD` and, through those, `ConnectionDialog`,
  `GetResourcePassword`, `GetUsernamePassword`, `GetNewPassword`,
  `GetNewPasswordEx`, `GetUsernamePasswordEx` (`netui.lib`).
- **`NOTIFICATIONCONDITION`** prints a nested definition the transcriber does
  not flatten; **`GETDRIVERNAMEPARMS`** and **`REGISTRYNOTIFYCALLBACK`** print
  no definition at all; **`DSENUMCALLBACK`**, **`LINECONFIGDATA`** and
  **`HREGNOTIFY`** have no page of their own in the corpus.  These block the
  seven `regext.h` `Registry*` functions (`aygshell.lib`) and
  `DirectSoundEnumerate` / `DirectSoundCaptureEnumerate` (`dsound.lib`).
- The `undeclared-audit` work list is 100 names, of which **66 cite an OEM,
  driver or Platform Builder header** (`Pkfuncs.h` 42, `pwinuser.h` 8,
  `pwindbas.h` 7, `Ddkreg.h` 3, and the rest) -- out of scope by the standing
  instruction.  The 34 app-layer names are the ones listed above plus the
  already-held `CeHeapCreate`, `RasIOControl`, `AddVectoredExceptionHandler`,
  `CeRegGetInfo` and the two SAPI COM interfaces.

## Open finding: `def/pimstore-doc.def` lists type names as exports

`ee483685` prints `Header: pimstore.h / Library: Pimstore.lib`, so
`gen-doc-def.py` transcribed `OlSensitivity` faithfully -- but `OlSensitivity`
is an enum, and the same file lists the COM interface names `IAppointment`,
`IContact`, `IException`, `IFolder`, `IRecipient`, `IRecurrencePattern`,
`ITask`, `ITimeZone` and the rest.  No module exports a type name.  This is
unchanged in M135: `make e2e` passes with it and nothing in `tests/e2e/`
references those names, so removing them is a separate decision from shipping
the headers.  `undeclared-audit` counts 9 of them (`Ol*`) in its work list for
exactly this reason.
