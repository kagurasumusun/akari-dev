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

| population | names | not declared | declared, not exported by its own lib | declared, exported by no lib at all |
|---|---|---|---|---|
| all app-layer exports | 2433 | 357 | 49 | 32 |
| eVC-era (first OS <= CE 4.2) | 1869 | 236 | 19 | 18 |

> **Correction (M116).**  The first revision of this table read
> `117 / 237` and `74 / 152`.  Those numbers were wrong, and the cause
> matters: "declared" was tested by searching the **raw** header text,
> comments included, so every *held* name the tree records in a comment
> counted as declared.  `InternetOpen` (`Wininet.h`), `CeSvcClose`
> (`Ceutil.h`) and `Header_GetItem` (`Commctrl.h`) are comment records,
> not declarations.  Re-measured against comment-stripped code the
> columns are the ones above, and the "declared" test was further split
> in two, because a name can be absent from the library its page names
> and still be linkable: CE aggregates most of the surface into
> coredll, and 16 of the 49 are exported by `def/coredll-doc.def`
> (`LocalAlloc`/`LocalFree`/`LocalReAlloc`/`LocalSize`,
> `HeapCreate`/`HeapFree`/`HeapReAlloc`, `GetMessagePos`,
> `PostQuitMessage`, `TranslateMessage`, `GetCapture`/`SetCapture`/
> `ReleaseCapture`, `GetDoubleClickTime`, `OffsetRgn`, `SHLoadDIBitmap`)
> even though their pages say `Lmem.lib`, `Msgque.lib`, `Foregnd.lib`
> and so on.  The last column is the one an app actually feels.

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

## What the 32 "exported by no lib at all" names are

Every one was read individually.  None of them is a missing export:

| class | n | names |
|---|---|---|
| parse artifact -- the print's return type taken as the name | 7 | `BOOLEAN` `DWORD` `HRESULT` `ULONG` `VOID` `int` `void` |
| `SNDMSG` common-control macros, not DLL exports | 8 | `Header_CreateDragImage` `Header_GetImageList` `Header_GetItemRect` `Header_GetOrderArray` `Header_OrderToIndex` `Header_SetHotDivider` `Header_SetImageList` `Header_SetOrderArray` |
| driver / OEM-side entry points -- called by the OS, not by an app | 12 | `ACM_Seek` `BatteryDrvrGetStatus` `DdsiTouchPanelGetPoint` `HCI_CloseDeviceContext` `InitLAP` `MyFSD_CloseVolume` `MyFSD_DeleteAndRenameFileW` `MyFSD_DeviceIoControl` `MyFSD_FlushFileBuffers` `MyFSD_LockFileEx` `MyFSD_Notify` `MyFSD_ReadFileWithSeek` |
| names an app supplies, never imports | 3 | `AbnormalTermination` (SEH) `CreateInstance` (IClassFactory) `WindowProc` |
| held comment records -- no declaration, so nothing to export | 2 | `AutoDialGetConnectionStatus` (`Autodial.h`) `DMORegister` (aa451608 prints no Requirements block at all, so no library is documented) |

Three names that *were* genuine gaps are exported as of M116:
`DrawIcon` (`icon-doc.def`, page aa452971), `OleCreatePropertyFrame`
(`oleaut32-doc.def`, `_wcesdk_oa96_OleCreatePropertyFrame`) and
`WSCDeinstallProvider` (`ws2-doc.def`, ms898778).  Each is declared with
`AKARI_CE_IMPORT`, each file stayed alphabetically sorted, and
`llvm-dlltool -m arm-pc-wince5.0` was run over the three with
`llvm-readobj` confirming the symbol lands in the import library.
(Earlier entries in `docs/inventory.md` say `-m armce`; that invented
machine name is gone -- a CE machine is named by its target triple.)

So the **declared-but-not-linkable axis is closed**: no documented
app-layer export that this tree declares is missing from every import
library.  The live gap is the other column -- **357 documented
app-layer exports the tree does not declare in code**, 236 of them
eVC-era.  Those are the held records and the absent names, and that is
where the remaining work is.

Reproduce with the same three inputs: the corpus rows, `include/`
(comments stripped -- see the correction above), and `def/`; the
generation mapping is `OS_VERSIONS` in `tools/gen-guard.py`.
