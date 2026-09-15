# M136 -- the audits were measuring a fraction of the archive

The premise of every audit in this tree is that the preserved corpus is the
official surface.  It was not, in two independent ways, and both hid real
gaps.

## Blind spot 1: pages that were never harvested

Measured against all four CE catalogs (`tools/catalogs/catalog-*.tsv`,
**61,926** page ids):

| catalog | TOC pages | in corpus | missing | missing, API-titled |
|---|---|---|---|---|
| CE 3.0 | 8,962 | 8,962 | 0 | 0 |
| CE .NET | 6,363 | 6,363 | 0 | 0 |
| CE 5.0 | 22,918 | 16,717 | 6,201 | 3 |
| CE 6.0 | 23,760 | 15,740 | 8,020 | 1,327 |
| **total** | **61,926** | **47,707** | **14,219** | **1,330** |

`tools/fetch-missing.py` fetched all 1,330 (zero failures).

This was not hypothetical.  M135 reported `ADDCONNECT_DLGPARAMS` as "no
printed definition on the page".  `ee493238` prints:

```c
typedef struct ADDCONNECT_DLGPARAMS {
    WCHAR LocalName[RMLEN + 10];
    WCHAR RemoteName[RMLEN];
    BOOL  bReadOnly;
} ADDCONNECT_DLGPARAMS, *PADDCONNECT_DLGPARAMS;
```

The page had never been fetched, so no audit could see it.

## Blind spot 2: the title filter

`coverage-audit.py` narrows the missing pages to "reference-like" titles with
a `KIND` pattern that requires the title to **end** with
`Function` / `Structure` / `Method` / `Constants` / ...  CE 6.0's XAML, WSD
and COM books title their methods `IXRControlTemplate::SetTargetType`, with no
suffix.  **3,453 such pages** sat outside the filter.  All 3,533 were fetched
(2 failures).

Together: **4,861 pages no audit in this tree had ever seen.**

## What the newly-fetched pages contain

`tools/area-audit.py` is new.  Every other audit buckets by "is the documented
header shipped here", which answers a question about files, not about the
surface -- it cannot say whether Telephony, IrDA or Notifications is covered.
This one groups by the `Header:` row of each page's Requirements block, over
**57,442 pages**, so an area's numbers come from the archive itself.  A header
that serves several areas (`winbase.h` serves Process, Virtual Memory,
Synchronization and Power) counts in each; the columns are not a partition and
the per-name list is what to read.

Full table in `docs/area-coverage.md`.  The areas with the largest undeclared
counts:

| area | documented | declared | undeclared |
|---|---|---|---|
| XAML (Silverlight for CE) | 878 | 38 | 840 |
| PIM / Pocket Outlook | 618 | 29 | 589 |
| UPnP / SOAP / XML | 760 | 166 | 594 |
| User / Window Manager | 1,630 | 1,215 | 415 |
| RTC / VoIP | 397 | 40 | 357 |
| DirectDraw / DDraw | 419 | 123 | 296 |
| COM / OLE | 648 | 358 | 290 |
| Multimedia (DirectShow / DVD / DMO) | 317 | 47 | 270 |
| WSD | 236 | 17 | 219 |
| WinInet / URLMon | 330 | 118 | 212 |
| Telephony | 356 | 195 | 161 |
| Message Queue | 138 | 26 | 112 |

201 headers carrying 2,173 names are still not mapped to an area; they are
listed in the report rather than dropped.

## Tool defects found by reading the pages by hand

Six, each confirmed against the page's own text:

1. **A return type kept its calling convention.**  `__cdecl` and `__stdcall`
   are compiler keywords, not `#define`s in `include/`, so
   `convention_macros()` never puts them in `known_conv`.  `ee479245` prints
   `__int64 __cdecl __ll_lshift( int64 Mask, int nBit );` and the head arrived
   as one token.  `PRIMITIVE` also gains `unsigned __int64` (`ee479349`).
2. **Function-like macros were invisible.**  The `#define` pattern demanded
   whitespace after the name; `ee478525` prints
   `#define CTL_CODE( DeviceType, Function, Method, Access) ( ... )`.  The
   macro's own parameters are now excluded from the value's identifier check.
3. **The documented name may be the struct tag.**  `ee495409` prints
   `typedef struct IRDA_DEVICE_INFO { ... } _IRDA_DEVICE_INFO;` -- the typedef
   is `_IRDA_DEVICE_INFO` and `IRDA_DEVICE_INFO` is reachable as
   `struct IRDA_DEVICE_INFO`, which is still a declaration of the documented
   name.  Requiring the name inside the declarator list rejected the whole
   `af_irda.h` family.
4. **Struct bodies were split on every semicolon**, and any fragment holding a
   brace was rejected as "nested definition".  `render_members` is now
   brace-aware and recursive; the inner definition is the page's own text,
   re-indented -- nothing invented.
5. **`declared_in_tree()` never indexed the tag** of
   `typedef struct TAG { ... } NAME;`, so the gap pass wrote a second copy of
   the `IRDA_DEVICE_INFO` that `Af_irda.h:130` already carried.
6. **`declared_in_tree()` never indexed plain prototypes.**
   `Notifext.hxx:55` is a bare
   `int CeNotifyPublic_Initialize(HINSTANCE hInst, HWND hwndUI);` from an
   earlier milestone; because the index only read `AKARI_CE_NAME(...)`, the gap
   pass added a second one with the CE 6.0 page's `void` parameter list.

**New rule:** a page with **no Link Library row at all** yields no
`AKARI_CE_IMPORT`, same as one printing an explicit `none`.  `ee479764`
(`__emul`) and `ee479349` (`__emulu`) print
`Architecture: MIPS 32, MIPS IV, ... / Header: winnt.h / Routine: __emul` and
no library -- compiler helper routines for 64-bit multiplication on a 32-bit
target, not coredll exports, spelled in `__int64` which the host compiler
`make check` runs does not even have.

20 declarations added across 8 headers: `Netui.h` 7, `Kernel.h` 4,
`Windows.h` 3, `Startui.h` 2, `Cecap.h` 1, `Notifext.hxx` 1, `Nclientview.hpp`
1, `Windev.h` 1.

## Why the rest is not declarable -- measured, not assumed

A census of every skip reason over the 5,099 undeclared names these pages add:

| count | reason |
|---|---|
| 1,155 | no prototype block names this function |
| 1,096 | not an identifier (`Class::Member` COM methods) |
| 125 | no printed definition of this name on the page |
| 88 | page has no prototype block |
| 29 | a parameter type is not declared by this tree |
| 14 | page prints no Link Library row |

The 1,096 `Class::Member` names span **146 interfaces, 128 of which `include/`
does not declare** -- XAML's `IXR*` family above all (`IXRUIElement` 46
methods, `IXRControl` 38, `IXRTextBlock` 34, `IXRTextBox` 34,
`IXRFrameworkElement` 34), plus `Gdi` (101) and `GweBypassCoredllThunk_t` (50).

**These cannot be declared from the archive.**  The CE 6.0 catalog contains no
`IXR* Interface` page at all -- only the per-method pages -- so the vtable
order is nowhere published, and a COM interface without its vtable order is
not a declaration, it is a guess.  Recording that is the correct outcome;
writing the vtables would be inventing an ABI.

## Held, with the evidence

`docs/unpublished-constants.tsv` records every constant a declaration needs
and no page publishes:

| constant | pages mentioning it | page printing a `#define` |
|---|---|---|
| `RMLEN` | 15 | none |
| `PWLEN` | 20 | none |
| `DNLEN` | 21 | none |
| `UNLEN` | 28 | none |
| `NETUI_LCD_DIAL_MOD_LEN` | 4 | none |
| `IAS_MAX_CLASSNAME_LEN` and 3 siblings | 0 | none |

These block, among others, `ADDCONNECT_DLGPARAMS`, `NETUI_RESPWD`,
`NETUI_USERPWD`, `NETUI_NEWPWD`, `LINECONFIGDATA` (whose definition `ee493261`
does print, but with `szDialModifier[NETUI_LCD_DIAL_MOD_LEN + 1]`) and
therefore `ConnectionDialog`, `GetResourcePassword`, `GetUsernamePassword`,
`GetNewPassword`, `GetNewPasswordEx`, `GetUsernamePasswordEx` and
`LineConfigEdit`.

`LINE_USSD`, `LINE_REGISTERSTATE`, `LINE_RADIOPRESENCE`,
`LINE_GPRSREGISTERSTATE` and `LINE_GPRSCLASS` are recorded as holds too, for a
different reason: their `<pre>` reads
`#define LINE_USSD dwParam1 = LINE_USSD; dwParam2; dwParam3;`, which is the
`extapi.h` line-event callback-parameter documentation format, not a macro.
No numeric value is published.

`TIMERPROC`, `WSDXML_ELEMENT`, `WSDXML_NAME` and `IWSDXMLContext` are used by
the WSD and GWE-bypass prototypes and **no page in the corpus prints a
definition** of any of them.  `LINEOPERATOR` is not mentioned by any page at
all.

## Gates

`make check` EXIT=0 (C and C++, `_WIN32_WCE` 0x420 / 0x500 / 0x600).
`make defcheck` OK (117 defs).

## Reproducing

```sh
python3 tools/fetch-missing.py --ref-only --out build/pagesgap2
python3 tools/fetch-missing.py --jobs build/missing-member.json --out build/pagesmember
python3 tools/area-audit.py
```

`build/` is not in the snapshot, so the fetch is a prerequisite; the corpus at
`/home/user/wince-docs-corpus` is `kagurasumusun/wince-docs-corpus` at
`80eae90a`.
