# App-build surface: measured (c) and (d)

Measured at M113 over all three record sets (33,473 rows).  The
question both axes ask is the same one an app asks: *can I compile
against this and then link it?*  So the unit of measurement is the
**documented DLL-export function** -- a row with a call-shaped code
print and a `Library:` row naming one of the 108 import libraries
this tree ships.  Two checks per name:

- **declared** -- the name appears as a function in `include/`;
- **exported** -- the name, or its `W`/`A` spelling, appears in one
  of the `def/*-doc.def` files (3,862 distinct export names).

## Exclusions, and why each one is not a gap

| excluded | count | reason |
|---|---|---|
| COM interface methods (title contains `::`) | -- | a vtable slot is not a linkable export; the CE pages still print `Library: ddraw.lib` for `IDirectDrawSurface5::AddOverlayDirtyRect` |
| `Library:` names with no shipped import lib | -- | OEM/BSP or driver-side libraries, out of scope for new work (`include/oak/`) |
| `Library:` values that are not libraries | -- | e.g. `Developer implemented.`, empty |

## (c) every documented app-layer export

| population | names | not declared | declared but not exported |
|---|---|---|---|
| all app-layer exports | 2433 | 117 | 237 |
| eVC-era (first OS <= CE 4.2) | 1869 | 74 | 152 |

Generation split of the same population, from the official
`OS Versions:` row: **1869** documented as present by CE 4.2, **213**
first appearing in CE 5.0/6.0, **348** stating no version at all
(`` / `Windows CE OS`), and 3 carrying a label with no CE
counterpart (`Windows CE .NET 2.0/3.0 and later.`, `Windows CE 2.10
through 4.1.`).  Unstated is not absent: those 348 stay in the (c)
population and are simply not attributed to (d).

## (d) eVC-era

eMbedded Visual C++ 3.0/4.0 targeted CE 2.11 through CE 4.2, so the
eVC-era population is the subset whose *first* documented OS is
CE 4.2 or earlier -- 1869 of the 2433 names.  Its gaps are strictly
smaller than (c)'s: 74 undeclared and 152 unexported, against 117 and
237.  Nothing an eVC-era app needs is missing that a CE 5/6 app does
not also miss.

## What the gap lists still contain

Both lists are *candidates*, not defects: a name reaches them by
shape, and several shapes are not linkable exports at all.
Confirmed by inspection in the top slices:

- **callback typedefs** -- `BrowseCallbackProc`, `AbortProc`: the
  page prints a `Library:` row for the prototype it documents, but
  the name is a type the app supplies, never imports;
- **macro / SEH names** -- `AbnormalTermination`, and the
  `CRYPTFUNC`-prefixed spellings (`CRYPTFUNCCryptDestroyHash`),
  which are the pages' own macro aliases;
- **driver-side entry points** -- `ACM_Seek`, `BatteryDrvrGetStatus`:
  documented with an app-layer library row but called by the OS, not
  by an app;
- **one misparsed row** -- `BOOLEAN`, where the print's return type
  was taken as the name.

The remainder is real work and is per-name: the largest unexported
slices are `Wininet.lib` (46), `Commctrl.lib` (43), `Coredll.lib`
(34), `Sdcardlib.lib` (18); the largest undeclared slices are
`Coredll.lib` (43), `Coreimm.lib` (18), `Coreloc.lib` (15),
`Dlgmgr.lib` (7).  Each needs its page read before it can be either
added or rejected, which is why this document records the
measurement rather than a guess at the fix.

Reproduce with the same three inputs: the corpus rows, `include/`,
and `def/`; the generation mapping is `OS_VERSIONS` in
`tools/gen-guard.py`.
