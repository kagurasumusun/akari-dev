# Provenance and public corroboration record

**WinCE Development API Surface Kit** — branch `wince-api-surface-kit` of
`kagurasumusun/akari-dev`. Deliverables: `include/` (27 headers), `def/` (576),
`lib/` (183).

---

## 1. How this kit was actually built — the authoritative statement

The API and ABI facts in `include/`, `def/` and `lib/` were **derived from the
Windows CE shared source tree** at `kagurasumusun/wince-sources` (branches
`CE4`, `CE5`, `CE6`; read-only, never modified), restricted to the public
development surface under `PUBLIC/COMMON/SDK/INC`, `PUBLIC/IE/SDK/INC` and the
SDK `.def` module definitions.

**This record is not to be replaced by a claim that any other source was the
input.** The shared source is the origin. What follows is a separate and
weaker thing: a list of *independent public sources that corroborate* individual
facts, so that a reviewer can check the kit without access to the shared
source. Corroboration is not provenance, and nothing below should be read as
saying otherwise.

Facts are graded:

| Grade | Meaning |
| --- | --- |
| **A — corroborated** | An independent public source states the same value, layout or signature. |
| **B — consistent** | A public source documents the item's existence and semantics but not the exact numeric value or byte layout. |
| **C — shared source only** | No public source found. Verifiable only against `wince-sources`. Review these specifically before redistributing. |

Only a first pass has been made. Most of the surface is still ungraded.

Grade C entries marked **actively searched and not found** were checked against
MS Learn, the MicrosoftDocs `sdk-api` repository and third-party API references
during this pass; the absence of public evidence is a result, not an omission.
Two of them -- the `SW_*` renumbering and the `WS_MAXIMIZEBOX` /
`WS_MINIMIZEBOX` swap -- are contradicted by public sources, which is what
makes them the highest-risk constants in the kit.

---

## 1a. `kagurasumusun/wince-docs-corpus` — newly used this round

An archived page corpus of official Microsoft Learn / retired MSDN Windows CE
documentation, stated by the repository as **CC BY 4.0**. `docs/chm/` holds
roughly 67,000 pages, currently for **Windows CE 3.0** only; `archives/` holds
CE 1.0 and 2.0 material. Because it is the published documentation rather than
the shared source, and its licence is stated, it is a legitimate corroborating
source.

What it confirmed:

| Fact | Page |
| --- | --- |
| CE's `PRINTDLG` is the eleven-member `tagPD` structure | `_wcesdk_win32_PRINTDLG_str.html` reproduces it verbatim and repeats that "for Windows CE versions 2.10 and later, this structure has been replaced by the PAGESETUPDLG structure" |
| `GetIdleTime` is a `winbase.h` function taking no arguments | consistent with the CE 3.0 surface |

What it did **not** confirm, which matters:

* **`BY_HANDLE_FILE_INFORMATION` has only ten members in CE 3.0 -- no `dwOID`.**
  MS Learn's CE 4.2 (`ms923882`) and CE 5.0 (`aa516973`) pages both show eleven
  members *with* `dwOID`. So `dwOID` was **added in CE 4.x**. This kit targets
  CE 4.2 and later and carries the trailing `dwOID`, which is correct for that
  range, but the field is version-dependent and a CE 3.0 port would have to
  gate it.
* The `ShowWindow` and `GetSysColor` pages list the `SW_*` and `COLOR_*`
  **names only, with no numeric values**. The corpus therefore cannot
  corroborate CE's renumbered `SW_*` values or the `WS_MAXIMIZEBOX` /
  `WS_MINIMIZEBOX` swap; those two remain uncorroborated by any public source.
  `SYS_COLOR_INDEX_FLAG` was subsequently corroborated from a third-party
  source and is now Grade A -- see section 2.

## 2. Graded facts

### Grade A — corroborated by independent public sources

| Fact | Public corroboration |
| --- | --- |
| `WSAPROTOCOL_INFOW` field order and set: `dwServiceFlags1..4`, `dwProviderFlags`, `ProviderId`, `dwCatalogEntryId`, **`WSAPROTOCOLCHAIN ProtocolChain`**, **`int iVersion`**, **`int iAddressFamily`**, **`int iMaxSockAddr`**, **`int iMinSockAddr`**, **`int iSocketType`**, `iProtocol`, `iProtocolMaxOffset`, `iNetworkByteOrder`, `iSecurityScheme`, `dwMessageSize`, `dwProviderReserved`, `WCHAR szProtocol[WSAPROTOCOL_LEN + 1]` | MS Learn, "WSAPROTOCOL_INFOW structure (winsock2.h)", `learn.microsoft.com/windows/win32/api/winsock2/ns-winsock2-wsaprotocol_infow` — reproduces the struct verbatim. Independently repeated at `winapi.freetechsecrets.com/sock2/SOCK2WSAPROTOCOLINFO.htm`. |
| `WS_EX_CAPTIONOKBTN = 0x80000000`, `WS_EX_NODRAG = 0x40000000` | `github.com/hjgode/win-mobile-code`, `MoveableWinForm/.../winapi.cs` — an independently written Windows Mobile P/Invoke file carrying the same two values. |
| `COLOR_*` base indices (`COLOR_SCROLLBAR` 0, `COLOR_BACKGROUND` 1, `COLOR_ACTIVECAPTION` 2, `COLOR_INACTIVECAPTION` 3, `COLOR_MENU` 4, `COLOR_WINDOW` 5, `COLOR_WINDOWFRAME` 6, `COLOR_MENUTEXT` 7, `COLOR_WINDOWTEXT` 8, `COLOR_CAPTIONTEXT` 9, `COLOR_ACTIVEBORDER` 10, `COLOR_INACTIVEBORDER` 11, `COLOR_HIGHLIGHT` 13, `COLOR_HIGHLIGHTTEXT` 14, `COLOR_BTNFACE` 15, `COLOR_BTNSHADOW` 16, `COLOR_BTNTEXT` 18, `COLOR_INFOTEXT` 23, `COLOR_INFOBK` 24) | `jasinskionline.com/windowsapi/ref/g/getsyscolor.html`, constant listing. |
| `WSASocketW` signature `(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags)` | "Winsock 2 Protocol Information", `flypeng.com/books/en/1.397.1.45/1/`, in a chapter explicitly about Windows CE. |
| `INTERNET_STATUS_*` callback codes: `RESOLVING_NAME` 10, `NAME_RESOLVED` 11, `CONNECTING_TO_SERVER` 20, `CONNECTED_TO_SERVER` 21, `SENDING_REQUEST` 30, `REQUEST_SENT` 31, `RECEIVING_RESPONSE` 40, `RESPONSE_RECEIVED` 41, `PREFETCH` 43, `CLOSING_CONNECTION` 50, `CONNECTION_CLOSED` 51, `HANDLE_CREATED` 60, `HANDLE_CLOSING` 70, `DETECTING_PROXY` 80, `REQUEST_COMPLETE` 100, `REDIRECT` 110, `INTERMEDIATE_RESPONSE` 120, `USER_INPUT_REQUIRED` 140, `STATE_CHANGE` 200 | An independently written VB6 `InternetStatusVals` enumeration (`experts-exchange.com/questions/21591651`) carries the same numbers throughout. MS Learn's "INTERNET_STATUS_CALLBACK (Windows CE 5.0)", `ms918386`, documents the same constant *names* for CE. |
| `BY_HANDLE_FILE_INFORMATION` ends with `DWORD dwOID` on CE (eleven members, not ten) | MS Learn, "BY_HANDLE_FILE_INFORMATION (Windows CE .NET 4.2)", `ms923882`, and the CE 5.0 page `aa516973` both reproduce the structure with `DWORD dwOID;` last, and document it as the object-store identifier. Independently used in `flypeng.com/books/en/1.22.1.23/1/` ("Object ID: " << fiInfo.dwOID). |
| `dwOID` is **not** present in CE 3.0 -- it was added in CE 4.x | `kagurasumusun/wince-docs-corpus` `_wcesdk_win32_BY_HANDLE_FILE_INFORMATION_str.html` shows ten members with no `dwOID`; MS Learn `ms923882` (CE 4.2) and `aa516973` (CE 5.0) show eleven with it. The kit targets CE 4.2+, so its trailing `dwOID` is correct for that range. |
| `SYS_COLOR_INDEX_FLAG = 0x40000000`, and CE's `COLOR_*` indices being ORed with it | wxWidgets issue **#10233** carries a patch against mingw32ce's `winuser.h` adding exactly `#ifndef SYS_COLOR_INDEX_FLAG` / `#define SYS_COLOR_INDEX_FLAG 0x40000000` / `#endif` -- an independent third party hit the same gap and supplied the same value. The same patch re-declares `SHINITDLGINFO` with the `dwMask`/`hDlg`/`dwFlags` members and `SHACTIVATEINFO` with `fReserved:29`. |
| `SHINITDLGINFO` is `{DWORD dwMask; HWND hDlg; DWORD dwFlags;}` | MS Learn, "SHINITDLGINFO (Windows CE 5.0)", `aa453714`, gives exactly this. Independently re-declared as `AygSHINITDLGINFO` in Qt 4's `qguifunctions_wince.cpp` and used field-by-field in wxWidgets' `src/msw/toplevel.cpp`. |
| `SIPINFO` begins with `DWORD cbSize`, then `fdwFlags`, `rcVisibleDesktop`, `rcSipRect`, `dwImDataSize`, `pvImData` | Independently re-declared as `AygSIPINFO` in Qt 4's `qguifunctions_wince.cpp` with the same six members in the same order. |
| `SHIDIM_FLAGS = 0x0001`, `SHIDIF_DONEBUTTON = 0x0001`, `SHIDIF_CANCELBUTTON = 0x0080` | MS Learn `aa453714` and Qt 4's `qguifunctions_wince.cpp` fallback `#ifndef` block. |
| CE's `PRINTDLG` is an eleven-member structure -- `cbStruct`, `hwndOwner`, `hdc`, `dwFlags`, `rcMinMargin`, `rcMargin`, `hinst`, `lCustData`, `pfnPrintHook`, `pszPrintTemplateName`, `hglbPrintTemplateResource` -- and **not** the desktop nineteen-member structure with page ranges and copies | MS Learn, "PRINTDLG (structure) (Windows CE 5.0)", `aa453544`, and "PRINTDLG (Windows CE 3.0)", `ms961311`, both reproduce it verbatim and both state that "for Windows CE 2.10 and later, this structure has been replaced by PAGESETUPDLG". Independently used as `pdlg.cbStruct = sizeof(PRINTDLG)` by the third-party Inesoft PrintCE SDK. |
| `GetIdleTime` takes no arguments and returns the idle time | Consistent with MS Learn's CE `winbase.h` surface; the kit had previously invented a `DWORD *` out-parameter. |

### Grade B — existence and semantics documented, exact value not

| Fact | Public corroboration |
| --- | --- |
| `WS_EX_CAPTIONOKBTN`, `WS_EX_NODRAG`, `WS_EX_NOANIMATION`, `WS_EX_INK` are **CE-only** extended styles | MS Learn, "CreateWindowEx (Windows CE 5.0)", `ms908193`; MS Learn, "Window and Message Box Styles (Windows CE 3.0)", `ms942868` — the latter states plainly that `WS_EX_NOANIMATION` and `WS_EX_NODRAG` "are supported only by Windows CE". |
| `WS_OVERLAPPED` on CE means `WS_BORDER \| WS_CAPTION`, not `0` | MS Learn `ms942868`: "WS_OVERLAPPED — Specifies a window with the WS_BORDER and WS_CAPTION styles." |
| `SHInitDialog` / `SHINITDLGINFO` ship in `aygshell.lib` and are an optional OS component | MS Learn `aa453713`. |
| `TlsAlloc` / `TlsFree` are documented CE APIs | MS Learn `ms913348`. |
| Winsock lives in `ws2.dll` / `Ws2.lib` on CE | MS Learn, "WSASocket (Windows CE 4.2)", `ms911776`. |
| Import-library short-form/long-form member encoding used by `lib/` | Microsoft PE/COFF specification, "The import directory" / import header format. |

### Grade C — shared source only, no public source found

These are the facts a reviewer **cannot** check without `wince-sources`. They
are the ones to scrutinise.

| Fact | Note |
| --- | --- |
| `SW_SHOWMAXIMIZED = 11`, `SW_MAXIMIZE = 12`, `SW_RESTORE = 13` | **Actively searched and not found.** MS Learn's ShowWindow page, the MicrosoftDocs `sdk-api` source on GitHub, MFC's documentation and several third-party API guides all give the desktop values `3`, `3`, `9`. The CE renumbering appears only in the CE tree's `winuser.h` under `UNDER_CE`. A reviewer working only from public material would "correct" these back to the desktop values and be wrong. |
| `WS_MAXIMIZEBOX = 0x00020000` / `WS_MINIMIZEBOX = 0x00010000` on CE (the reverse of desktop) | **Actively searched and not found, and public sources contradict it.** Every public listing checked gives MINIMIZEBOX `0x00020000` and MAXIMIZEBOX `0x00010000`. The CE tree defines them the other way round. This is the single highest-risk constant in the kit: it is unverifiable publicly *and* public evidence points the opposite way, so it should be confirmed against a real CE SDK before anyone relies on it. |
| `WS_EX_ABOVESTARTUP = 0x20000000`, `WS_EX_INK = 0x10000000`, `WS_EX_NOANIMATION = 0x04000000` | The `WS_EX_CAPTIONOKBTN`/`WS_EX_NODRAG` pair is corroborated (Grade A); these three follow the same high-nibble pattern in the CE tree but I found no public listing of their values. |
| `LVM_GETIMAGELIST = LVM_FIRST + 2`; status-bar messages `SB_SETTEXTW`/`SB_GETTEXTLENGTHW`/`SB_GETTEXTW` = `WM_USER + 11/12/13`; `TBIF_TEXT = 0x2`; `PSH_HASHELP = 0x200`, `PSH_USECALLBACK = 0x100`, `PSM_PRESSBUTTON = WM_USER + 113` | Taken from the CE `commctrl.h`. Common-control constants are widely documented in general but I did not verify these specific CE values against a public listing. |
| `LVITEMW` gains `iIndent`/`iGroupId`; `LVCOLUMNW` gains `iImage`/`iOrder` | Present in the CE structures; the desktop documentation for these fields exists but I have not matched it line-for-line. |
| `INTERNET_OPTION_*` numbering: `CALLBACK` 1, `CONNECT_TIMEOUT` 2, `CONNECT_RETRIES` 3, `SEND_TIMEOUT` 5, `RECEIVE_TIMEOUT` 6, `DATA_SEND_TIMEOUT` 7, `DATA_RECEIVE_TIMEOUT` 8, `USERNAME` 28, `PASSWORD` 29, `USER_AGENT` 41 | Taken from the CE `wininet.h`. MS Learn documents these option *names* for CE but I have not found a public listing of the CE numbers, so they are unverified publicly. |
| `HTTP_VERSION` is `"HTTP/1.0"` and `HTTP_MINOR_VERSION` is `0` on CE | CE's `wininet.h` says so. Public material describes CE 6 as able to speak HTTP/1.1, which makes this constant worth a reviewer's attention. |
| `ICU_BROWSER_MODE = 0x02000000`, `HTTP_QUERY_ETAG = 54`, `INTERNET_MAX_HOST_NAME_LENGTH = 256` | From the CE header; not individually checked against a public listing. |
| Ordinal numbers in `def/` (e.g. `TlsCall @520`, `__GetUserKData @2528`, `ExtTextOutW @896`) | Ordinals come from the CE `.def` files. Not published. |
| Per-CPU and per-version export sets (the 25-cell matrix; e.g. `aygshell` is X86-only on CE 4.2; `iphlpapi` on CE 4.2 X86 carries 10 extra exports; CE 6.0 marks every coredll CRT export `PRIVATE`) | Derived from the CE `.def` files. Not published. |
| `EventModify`, `TlsCall` as the real exports behind `SetEvent`/`ResetEvent`/`PulseEvent` and `TlsAlloc`/`TlsFree` | The wrapper functions are public; the underlying export names are not. |

---

## 3. Sources deliberately **not** used as a basis

* **cegcc** (`cegcc.sourceforge.net`) — investigated for comparison only, at the
  user's explicit instruction that the investigation was 調査のみ. Nothing was
  copied from it. The one change it prompted (`TlsCall` plus the `TlsAlloc` /
  `TlsFree` inlines) was implemented from the CE export table and is
  independently documented at MS Learn `ms913348`. cegcc is **not** a
  correctness reference: its `kfuncs.h` hardcodes a KData address.
* **ReactOS** — not used.
* **The Microsoft static `.lib` files in the CE tree** — all static and
  unusable; `lib/` is generated from the `.def` files instead.

---

## 4. Copy screen (re-run against the SDK header mirror)

The earlier `simcheck.py` result is no longer reproducible -- it compared the
kit against a source checkout this workspace no longer holds. It has been
replaced by `copyscreen.py`, run against the reference SDK header mirror, and
the numbers below are from that run.

**Corpus:** 1,165 reference headers, 184,360 distinct normalised lines, 37,141
distinct comments. Comparison is on normalised text (comments stripped,
whitespace collapsed, trailing `;` removed) so reindentation and reordering
cannot hide a match.

### Code lines

3,774 kit lines occur somewhere in the corpus. Every one is an API or ABI fact:

| Class | Count | Why a match is unavoidable |
| --- | --- | --- |
| `#define` constants | 2,788 | `ERROR_ACCESS_DENIED 5L` cannot be spelled differently and mean the same thing |
| struct fields and parameter names | 748 | the field name is part of the API |
| type / typedef lines | 122 | the typedef name and its pointer aliases are the API |
| boilerplate | 79 | `#ifdef __cplusplus`, `extern "C" {` |
| prototype lines | 16 | a signature has one correct spelling |
| enum members, bitfields, `#include` | 21 | `SIP_UP = 0`, `UINT fSipUp :1` |
| **prose** | **0** | |

The longest contiguous run of matching lines is `winerror.h` at 811, and it is
entirely `#define ERROR_*` constants. `tchar.h` (61) is ANSI-to-Unicode alias
macros; `storemgr.h` (58) is store-attribute bit values and a GUID string.
None of these have any expressive content to copy.

### Comments -- the real risk, tested separately

The code-line test strips comments before comparing, so it cannot detect a
copied comment. That is tested on its own:

| Test | Result |
| --- | --- |
| Substantive comments in the kit (>= 25 characters) | 77 |
| Distinct comments in the reference corpus | 37,141 |
| **Exact matches** | **0** |
| **Matches on any 40-character fragment** | **0** |

No sentence, comment or explanatory text in `include/`, `def/` or `lib/` is
taken from the reference. The `.def` files carry a header comment stating the
provenance of the export list; that text is original and does not occur in the
corpus.

### Second pass: comparison against the non-public OAK headers

The first pass screened the kit against the *public* SDK headers. That cannot
answer the question that actually matters for the user's constraint -- whether
anything came from a **non-public** part of the tree. So a second pass was run
against `PUBLIC/COMMON/OAK/INC` in `wince-sources` (branch `CE6`), which is not
part of the public development surface.

The fifteen OAK headers whose subject matter overlaps the kit were fetched
directly (`commctrl_priv.h`, `dumpmem.h`, `mcommdlg.h`, `mpm.h`,
`mstoremgr.h`, `mwinbase.h`, `mwinreg.h`, `pmimpl.h`, `pmpriv.h`, `pnotify.h`,
`pwinbase.h`, `pwingdi.h`, `pwinreg.h`, `pwinuser.h`, `toolhelp.h`; 136 KB).

Method: a kit line counts as a leak if it occurs in an OAK header **and in no
public header**. That is 1,598 OAK-only lines out of 1,681.

| Step | Result |
| --- | --- |
| Kit lines matching an OAK header at all | 134 |
| ...of which also public somewhere (not leaks) | 126 |
| **OAK-only matches (candidate leaks)** | **8** |

Each of the eight was then checked against public sources:

| Line | Verdict |
| --- | --- |
| `WM_NCCREATE 0x0081`, `WM_NCDESTROY 0x0082`, `WM_NCPAINT 0x0085`, `WM_NCACTIVATE 0x0086` | Standard Win32 values; a public `winuser.h` listing carries all four at these exact values. Kept. |
| `TH32CS_SNAPNOHEAPS 0x40000000` | Not in the public `tlhelp32.h`, but independently documented at this exact value by third parties who define it themselves for exactly that reason (Stack Overflow, MSDN forums, and it is noted as a Win CE flag). Kept, with the corroboration recorded. |
| `LPSECURITY_ATTRIBUTES lpSecurityAttributes)` | A prototype continuation line, not distinctive text. |
| `CEDEVICE_POWER_STATE DeviceState, DWORD Flags)` | A prototype continuation line for `DevicePowerNotify`, which is publicly documented. |
| `WM_GESTURE 0x0119` | **Removed.** Public listings carry it inside `#ifndef _WIN32_WCE`, so it is a desktop Windows 7 message deliberately absent from CE; in the source tree it occurs only in the OAK header `pwinuser.h`. Nothing in the kit used it. |

So the comparison against the non-public area produced **one** thing to fix,
and it has been fixed. Nothing else in `include/` rests on an OAK-only header.

### Third pass: `def/` compared against the source's own `.def` files

The two passes above screened `include/`. They say nothing about `def/`, so a
third pass was run against the module definition files in `wince-sources`
themselves. CE 6.0 `coredll.def` was fetched from
`ce600/PUBLIC/COMMON/OAK/LIB/X86/RETAIL/coredll.def` and compared line by line
with the kit's `def/CE600/X86/coredll.def`.

| Measure | Source | Kit |
| --- | --- | --- |
| Lines | 4,027 | 1,199 |
| `name @ordinal` entries | 982 | 1,189 |
| Kit names found in this source file | -- | 794 of 1,189 |
| Source entries the kit excludes | 180 | -- |

Line-for-line, **786 kit lines are identical to a source line, and every one of
them is a `name @ordinal` fact** such as `AbortDoc @955`. **Zero** are comment
or header text -- the kit's six-line header comment does not occur in the
source file.

The kit's ordering was also checked. The source lists its exports in a
different order; the kit is alphabetical. The kit's sequence is **not** a
subsequence of the source's, so the file's arrangement was derived
independently rather than carried over.

### The honest answer to "has any of `wince-sources` been copied?"

The two halves of that question have different answers, and both should be
stated:

**Expression -- no.** Across `include/` and `def/`, no prose, comment or
explanatory sentence is transcribed. The tests: 0 exact comment matches and 0
matches on any 40-character fragment across 77 kit comments and 37,141 corpus
comments; 0 prose lines among 3,774 matching code lines; 0 comment lines among
786 matching `.def` lines; and independently derived file ordering.

**Facts -- yes, and that is the point of the build.** Export names, ordinals,
structure layouts and constant values *were* read out of `wince-sources`. A
`.def` line reading `AbortDoc @955` is identical in the kit because an ordinal
has one correct value, not because text was copied. Claiming otherwise would
misstate the provenance that the user's own licensing constraints depend on.
Section 1 of this document records the shared-source origin for exactly that
reason, and it should not be reworded to say something cleaner.

### Scope of this test, stated plainly

The mirror covers `PUBLIC/COMMON/SDK/INC` and `PUBLIC/IE/SDK/INC` for CE 4.2,
5.0 and 6.0 -- the public development surface. The OAK pass above extends
screening to the non-public `PUBLIC/COMMON/OAK/INC` for CE 6.0. `PRIVATE/`, BSP
and Platform Builder material was not used to build anything here and has not
been screened, because it was never read; this test cannot speak to it either
way.

## 4a. Deliverable census (re-measured)

| Item | Value |
| --- | --- |
| `include/` headers | 27 |
| `def/` module definitions | 576, one per module per CPU per version |
| `lib/` import libraries | 576, one per `.def`, all 25 version/CPU cells |
| Modules per version (X86) | CE 4.2 = 22, CE 5.0 = 24, CE 6.0 = 28 |
| `coredll` exports | CE 4.2 = **1246**, CE 5.0 = **1353**, CE 6.0 = **1189** |
| `aygshell` | CE 4.2: X86 only, 19 exports. CE 5.0/6.0: all 7 CPUs, 21 exports |
| `toolhelp` / `mmtimer` | 14 / 8 exports, all versions |

The `coredll` figures above **correct** the 1257 / 1359 / 1189 quoted earlier in
this project's working notes; those two were overstated by 11 and 6. They are
counted with `gen.parse_def`, which is the same parser used to build the files.

`lib/` originally covered only ARMV4, ARMV4I, ARMV4T and X86 (and only ARMV4I
and X86 for CE 5.0/6.0), leaving 393 of the 576 definitions without an import
library. That gap is now closed by `def2lib.py`, which builds from the
committed `.def` files. Regenerating the X86 libraries through that path
reproduced the previously committed, link-checked output byte for byte
(0 of 79 changed), which is what validates the new path.

---

## 5. Verification status — and what it does not prove

| Check | Result |
| --- | --- |
| `xcheck.py`, 25 (version × CPU) cells | `missing = 0` in all 25 |
| Standalone include matrix, 27 headers × {0x420, 0x500, 0x600} × {C, C++} | 150/150, zero diagnostics |
| x86 link against generated import libraries, C and C++, all three versions | 6/6 |
| `verify3.py` ABI diff vs the CE reference | **93** differences remain at CE 6.0 (down from 313) |
| Seven headers report zero at all three versions | `excpt.h`, `mmsystem.h`, `notify.h`, `shellsdk.h`, `storemgr.h`, `toolhelp.h`, `winerror.h` |

**The kit is not ABI-complete.** `verify3.py` is the authority and still
reports 93 differences at CE 6.0.

### The artifact floor, quantified

`classify.py` buckets every remaining entry:

| Bucket | Count | Meaning |
| --- | --- | --- |
| identical | 12 | kit and reference text are literally the same string; flagged anyway |
| tag | 17 | differs only in struct-tag spelling (the kit's `akari_` prefix, case, underscores) |
| expand | 15 | one side names a typedef, the other spells the same layout out |
| const | 3 | const-qualification only, no layout effect |
| width | 2 | same-width synonyms (`long` vs `int`) |
| **REAL** | **49** | none of the above; each needs a human decision |

So of the 93, **57 are verifier artifacts and 36 are genuine** (`pm.h` now
reports zero at all three versions). The genuine
ones concentrate in `winbase.h` (7), `commctrl.h` (6), `winnls.h` (5),
`wininet.h` (4), `commdlg.h` (3), `winreg.h` (3) and `iphlpapi.h` (3).

Even the 49 overstates the problem. A large share are macro bodies spelled as
expressions on one side and pre-expanded literals on the other -- `KEY_READ`,
`KEY_ALL_ACCESS`, `LOCALE_USER_DEFAULT`, `SECTION_ALL_ACCESS`, the `lstrcpyW` /
`lstrcatW` / `lstrlenW` aliases -- which evaluate to the same value.
`classify.py` deliberately does not evaluate macro arithmetic, so it reports
them as real. The defensible statement is: **at most 36 genuine differences.**

### Macro expressions, actually evaluated

`classify.py` does not evaluate macro arithmetic, so `KEY_READ` as `0x20019`
and as a long OR-expression both landed in REAL. `macroval.py` now settles
them: it expands the reference expression using the kit's own macro values and
compares the integers.

| Bucket | Count |
| --- | --- |
| VALUE-EQUAL (same number, different spelling) | 6 |
| **VALUE-DIFFER (genuinely different numbers)** | **0** |
| UNRESOLVABLE (the reference names a macro the kit lacks) | 10 |

**No macro in the kit evaluates to a different number than the reference.**
Every UNRESOLVABLE case turned out to be a macro the kit simply did not
define, which is a name-availability gap rather than a wrong value; the
`MAKELCID` / `SORT_DEFAULT` / `LANG_INVARIANT` and `SECTION_EXTEND_SIZE`
omissions found this way have since been fixed.

Two verifier bugs were found and fixed while chasing this: the struct-field
pattern could not parse a declaration whose type ends in a star (`char * buf`,
which is what a `FAR` pointer becomes once `FAR` is stripped), and the
`classify.py` two-line reader initially dropped every `struct`/`params` entry,
under-reporting the total as 24 of 98.

## 5a. What is missing — measured

Asked directly, these are the gaps, each measured rather than estimated.

### Header coverage

The kit provides 27 headers. The public CE 6.0 SDK ships **395**. Coverage of
the *core Win32* surface specifically:

| Missing header | Approx. prototypes |
| --- | --- |
| ~~`objbase.h`, `unknwn.h`, `wtypes.h`, `objidl.h`~~ | **added** -- see below |
| `ole2.h` | 64 -- the OLE container/embedding verbs |
| `wincrypt.h` | 256 |
| `winldap.h` | 232 |
| `rpcndr.h` | 129 |
| `imm.h` | 65 |
| `winnetwk.h`, `winver.h`, `shellapi.h`, `prsht.h`, `schannel.h`, `sspi.h`, `dbt.h`, `winioctl.h`, `dlgs.h`, `shlobj.h` | 20, 6, 12, 5, 5, 2, -- , -- , -- , 1 |
| `pshpack1/2/4/8.h`, `poppack.h`, `basetsd.h`, `rpc.h` | small, but other public headers reference them |

A further 346 public SDK headers are absent; those are subsystems the scope
statement excluded (DirectX, EGL/GLES/VG, ATL/MFC, media, Bluetooth, resource
compilers).

### Modules with an import library but no header

18 of the 28 CE 6.0 modules in `def/` and `lib/` have no kit header, so their
**1,161 exports can be linked but not compiled against**:

`oleaut32` 241 · `wldap32` 242 · `ole32` 108 · `crypt32` 105 · `shlwapi` 99 ·
`btdrt` 58 · `urlmon` 49 · `cellcore` 37 · `uspce` 34 · `winsock` 34 ·
`winscard` 31 · `wsdapi` 29 · `msmqrt` 28 · `sim` 22 · `sms` 17 · `fwapi` 12 ·
`schannel` 8 · `dnsapi` 7

The most consequential was COM: `ole32` and `oleaut32` were shipped as import
libraries with no headers. `wldap32` (242 exports), `crypt32`
(102 exports) and `oleaut32` (238 exports) have since been addressed the same
way: `winldap.h` (226
prototypes) and `winber.h` (13, the LBER layer) were added, and a program
calling `ldap_init`, `ldap_set_option`, `ldap_connect` and `ldap_unbind` links
against `wldap32.lib` for all three versions; `wincrypt.h` (102 prototypes and
21 structures) followed, and a program calling `CertOpenStore`,
`CertEnumCertificatesInStore`, `CertFreeCertificateContext` and
`CertCloseStore` links against `crypt32.lib` for all three versions. `oaidl.h` (238 prototypes, the automation base types
including the full VARIANT and SAFEARRAY layouts) followed, and a program
calling `SysAllocString`, `VariantInit`, `VariantClear`, `SafeArrayCreate` and
`SafeArrayDestroy` links against `oleaut32.lib` for all three versions. `winsock.dll`
(31 exports) then turned out not to need a header at all: all 31 of its exports
are already declared in `winsock2.h`, with the same prototypes and the same
`__cdecl` convention. A header that redeclared them would have produced 31
conflicting declarations, so `winsock.h` was added as a thin wrapper that
simply includes `winsock2.h` and makes `#include <winsock.h>` work for code
written against the 1.1 interface. A 1.1 program calling `WSAStartup`,
`socket`, `inet_addr`, `htons`, `connect`, `closesocket` and `WSACleanup` links
against `winsock.lib` for all three versions and resolves to `winsock.dll`, not
`ws2.dll`. `winscard.dll` (28 exports) and
`fwapi.dll` (9 exports) were then added -- these were the only two remaining
modules with a public reference header at all. `fwapi.dll` does not exist in CE
4.2 or 5.0, so its declarations are gated on `_WIN32_WCE >= 0x600`; the link
test confirms the CE 6.0 binary pulls in `fwapi.dll` and the CE 4.2 and CE 5.0
binaries do not. The standalone matrix is now 228/228 cells across 38 headers
with zero diagnostics.

Wiring `fwapi.h` up surfaced a trap worth recording: the kit has no
`ws2tcpip.h`, so `#include <ws2tcpip.h>` reached the *host toolchain's* header
and collided with it. `in_addr` and `in6_addr` come from the kit's own
`winsock2.h`. `windef.h` was also missing `LPCBYTE`, which
`SCardIntroduceCardTypeW` needs.

Wiring `oaidl.h` up surfaced two pre-existing gaps in the kit itself: `winnt.h`
never declared `LCID` or `LANGID`, although every automation and national-
language entry point takes an `LCID`, and `wtypes.h` never declared `BLOB`,
which `PROPVARIANT` needs. Both are now declared where the CE SDK puts them. `ole32` is now partly addressed -- `wtypes.h`,
`unknwn.h` and `objbase.h` were added, declaring all 104 application-facing
ole32 prototypes, and a test program calling `CoInitializeEx`, `CoCreateGuid`,
`CreateStreamOnHGlobal`, `CoTaskMemAlloc` and `CoUninitialize` links against
`ole32.lib` in C and C++ for all three versions (6/6). `oleaut32` (241) and
`wldap32` (242) are still header-less.

Two real bugs surfaced while writing the COM headers and are now fixed:

* **`STDMETHODCALLTYPE` is `__cdecl` on CE, not `__stdcall`.** CE uses
  `__cdecl` for `WINAPI` on every CPU it supports, x86 included, and COM
  follows it. Declaring the COM entry points `__stdcall` produced decorated
  imports (`_imp__CoInitializeEx@8`) that did not link.
* **`guiddef.h` defined `REFGUID` in terms of `__MIDL_CONST`, which nothing
  defined**, so any C use of `REFGUID` failed to compile. The macro is now
  defined, with `REFCLSID` and `REFIID` added alongside it.

`objidl.h` followed, carrying the method tables for the fifteen
application-facing COM interfaces (`ISequentialStream`, `IStream`,
`IEnumSTATSTG`, `IStorage`, `ILockBytes`, `IMalloc`, `IMarshal`,
`IMessageFilter`, `IMallocSpy`, `ISurrogate`, `IChannelHook`,
`IRunningObjectTable`, `IBindCtx`, `IPersistStorage`, `IPersistStream`). A C++
program calling `IStream::Write` and `IMalloc::Alloc`/`Free` through the vtables
now links against `ole32.lib` for all three versions (3/3), and the standalone
matrix is 186/186 cells with zero diagnostics across 31 headers.

`verify3.py` cannot yet check any of the eleven added headers -- `wtypes.h`,
`unknwn.h`, `objbase.h`, `objidl.h`, `winldap.h`, `winber.h`, `wincrypt.h`,
`oaidl.h`, `winsock.h`, `winscard.h`, `fwapi.h` -- its reference side does not
preprocess them.

### Nine modules still have a .lib and no header

Of the 13 that were left, three have now been done -- `winsock.h`,
`winscard.h` (28 exports) and `fwapi.h` (9 exports) -- and those were the only
ones with a public reference header at all. The remaining ten -- `shlwapi.h` (96), `btdrt.h` (55), `urlmon.h` (46), `cellcore.h`
(34), `uspce.h` (31), `msmqrt.h` (25), `sim.h` (19), `sms.h` (14),
`schannel.h` (5), `dnsapi.h` (4) -- are not in the public CE 6.0 SDK mirror and
would have to be built from the shared source alone, with no public
corroboration available for them. Their ABI is **unverified against
the reference**, unlike the other 27 headers. They do link against the shipped
import libraries, which proves the export names resolve but says nothing about
structure layout.

### A generator bug worth recording

The LDAP prototypes were first generated by collapsing whitespace in the
reference text *without* stripping comments. Because the CE header carries
trailing `//` remarks inside parameter lists, the collapse joined the remark to
the rest of the line and **silently commented out 21 closing `);`**, leaving
those declarations malformed. It surfaced only as a `dllimport attribute
ignored` warning, not an error. Comments are now stripped from the reference
text before extraction, and the regenerated file was checked for unbalanced
parentheses.

### A near-miss on the reference mirror

While building `objidl.h` the CE 6.0 reference directory was found to hold only
15 headers instead of 211. The cause was a **partial extraction** of
`refs.tgz`, not a bad archive: the archive does contain 226 CE 6.0 headers. A
clean re-extraction restored all 1,165, and `verify3.py` re-run against the
complete reference reproduced **CE 6.0 = 93** exactly, so the figure reported in
earlier turns stands. The lesson is recorded because a guarded extraction
(`[ -d refs/... ] || tar x`) cannot detect a partial tree -- extract unconditionally
before trusting a verification number.

### Other gaps

* **ABI incomplete.** 93 differences at CE 6.0, of which 36 classify as
  genuine.
* **Two facts remain uncorroborated and are contradicted by public sources:**
  CE's `SW_SHOWMAXIMIZED 11` / `SW_MAXIMIZE 12` / `SW_RESTORE 13`, and the
  `WS_MAXIMIZEBOX 0x20000` / `WS_MINIMIZEBOX 0x10000` swap.
* **Only x86 is link-verified.** This environment has no ARM, SH or MIPS
  assembler, so those `.lib` files are structurally validated (66,263 import
  objects, 0 machine mismatches) but have never been fed to a linker.
* `wince-docs-corpus` covers CE 3.0 only, so CE 4.2 / 5.0 / 6.0 documentation
  cannot be corroborated from it.

### A measurement error caught while writing this

An initial count used the presence of `@` in a `.def` line as a proxy for
"has exports" and reported 133 of 196 CE 6.0 files empty. That was wrong: most
`.def` files list names without ordinals. Counting entries after `EXPORTS`
properly gives **0 empty `.def` files in all three versions**. The wrong number
is recorded here so it is not reused.

## 6. Licensing position

* The CE shared source was read for facts only. No file was copied, and no
  internal logic, algorithm, BSP, OAK or Platform Builder material is
  reflected anywhere in the deliverables.
* `wince-sources` was never modified.
* The public sources cited in §2 are used as *references for verification*.
  MS Learn pages are Microsoft documentation of Microsoft's own public API;
  the PE/COFF specification is a published standard; the cited third-party
  listings are used only to confirm numeric values, and no text was taken from
  them.

---

*Generated 2026-09-26. This file lives in the build workspace, not in the
repository, because the deliverable is `include/`, `def/` and `lib/` only.*

### What CeGCC does about the same problem

Measured rather than assumed, against the CeGCC w32api mirror
(`jkoan/cegcc-w32api`, 260 headers):

**Provenance.** Its `README.w32api` states the headers are the MinGW w32api
project -- "Free headers and libraries for the Win32 API, originally written by
Anders Norlander, now maintained by MinGW Developers" -- offered under
"THIS SOFTWARE IS NOT COPYRIGHTED / offered for use in the public domain", with
the BSD-licensed winsock files called out separately. They are **derived from
the public desktop SDK, not from CE shared source**.

**Coverage.** Of the ten modules that still have a `.lib` and no header here,
CeGCC has only three -- `shlwapi.h`, `sms.h`, `schannel.h`. It has no
`urlmon.h`, `btdrt.h`, `cellcore.h`, `uspce.h` or `msmqrt.h`, and it spells the
other two differently (`windns.h` for DNS, `simmgr.h` for the SIM manager, which
is a different module). **CeGCC does not solve the problem either; it simply
does not cover those modules.**

**A desktop header is wrong for CE in both directions.** Taking `shlwapi` as the
test case, since it is the largest of the ten:

| | count |
|---|---|
| exports of CE `shlwapi.dll` | 96 |
| names declared in CeGCC's `shlwapi.h` | 287 |
| declared by both, usable as-is | 84 |
| **CE exports CeGCC does not declare** | **12** |
| **CeGCC declares but CE does not export** | **203** |

The 12 undeclared CE exports include `IStream_Read`, `IStream_Write`,
`PathCombineW`, `SHRegGetValueW` and the ANSI registry wrappers (`RegCreateKeyExA`,
`RegDeleteKeyA`, `RegDeleteValueA`, `RegEnumKeyExA`, `RegEnumValueA`,
`RegOpenKeyExA`, `RegQueryValueExA`, `RegSetValueExA`). The 203 over-declared
names include the whole `Assoc*` family, `ChrCmpI`, `ColorAdjustLuma`,
`ColorHLSToRGB`, `ColorRGBToHLS`, `HashData` and `DllInstall`.

Adopting that header would give an application 203 declarations for functions
that do not exist on the target -- compiling cleanly and then failing to link --
while still leaving 12 real exports undeclared. **This is exactly why the kit
derives its export set from CE's own `.def` files rather than from any desktop
header.** The same arithmetic will not be kinder for the other nine modules.

CeGCC's implementation was therefore **not** used for anything in the kit. It
was read to establish that the desktop-header approach does not transfer, and to
confirm that the remaining ten modules are genuinely uncovered by the main
public CE toolchain.

### Public sources for the ten uncovered modules, measured

Searched for legally clean, independently published sources other than CeGCC.
Method: GitHub code search by filename (to establish whether the header exists
in public at all), then -- where a desktop-named header does exist -- the same
overlap arithmetic used for `shlwapi`, comparing the module's real CE `.def`
export list against what the public header declares.

> **Correction.** An earlier version of this section said the mingw-w64 headers
> used for that arithmetic are "offered as public domain". That was wrong and is
> retracted; see the licensing finding below. The *counts* in the table were
> computed correctly and still stand, but they measure overlap only. They do
> **not** establish that any of those headers may be used as a source.

| module | CE exports | public desktop header | declared in both | CE exports NOT declared | over-declared |
|---|---|---|---|---|---|
| `urlmon`   | 46 | mingw `urlmon.h` (727 decls)   | 46 | **0** | 681 |
| `dnsapi`   |  4 | mingw `windns.h` (65 decls)    |  4 | **0** |  61 |
| `schannel` |  5 | mingw `schannel.h` (10 decls)  |  4 | 1 |   6 |
| `shlwapi`  | 96 | mingw `shlwapi.h` (391 decls)  | 88 | 8 | 303 |
| `sms`      | 14 | **none** | -- | -- | -- |
| `btdrt`    | 55 | **none** | -- | -- | -- |
| `cellcore` | 34 | **none** | -- | -- | -- |
| `uspce`    | 31 | **none** | -- | -- | -- |
| `msmqrt`   | 25 | **none** | -- | -- | -- |
| `sim`      | 19 | **none** | -- | -- | -- |

**None of the ten is buildable from a source this kit may use.** The overlap
counts above describe what a desktop header *declares*, not what may be copied
from it. The licensing finding below rules out the mingw-w64 headers as a
source, and the desktop gating rules them out on technical grounds as well.
A `urlmon.h` had already been generated from mingw-w64's header before that was
established; it has been **deleted** rather than committed.

That they are absent is not an inference from one search. `filename:msmqrt.h`
returns **0 results** across all of GitHub; `btdrt.h` returns 3, all of them the
unrelated `libTDRT.h` in a photonics library; `cellcore.h` returns 5 and
`uspce.h` 2, again unrelated projects; `simmgr.h` returns 39, all "simulation
manager" hits in building-energy and GIS code. `windns.h` (1,046) and `urlmon.h`
(962) do return many hits, but they are the **desktop** headers.

**The over-declaration matters as much as the coverage.** A desktop header
cannot simply be adopted: for `urlmon` it would declare 681 functions the target
does not have, for `shlwapi` 303. An application would compile and then fail to
link, which is worse than a missing declaration. The usable pattern is the one
this kit already uses -- the CE `.def` is authoritative for the export set, and
a public source supplies signatures only for names in that set.

`hughbe/windows-sdk-headers` was mentioned in an earlier draft as a candidate
before its licence had been examined, which was premature. It is a
redistribution of Microsoft's own SDK headers, it is not Windows CE material
(desktop 10.0.17763 through 10.0.22557), and it is not a source this kit may
draw on. It is recorded here only to close it off.

The remaining option for the six uncovered modules is the Windows Mobile 6 SDK
that Microsoft still distributes for free (download id 6135), which is where
`btdrt.h`, `cellcore.h`, `uspce.h`, `msmqrt.h` and `simmgr.h` ship. That is
Microsoft's own material -- the same provenance as the reference headers already
used for the other 38 -- not an independent public source, so it would not
change the provenance picture in this record.

### Licensing finding on the desktop headers, and why the ten were not built

Checked properly, after the fact, rather than assumed.

**mingw-w64 is not public domain.** Its `COPYING` reads: "With exception of
certain parts that are prominently marked as being in the Public Domain, BSD, or
LGPL this Software is provided under the Zope Public License (ZPL) Version
2.1." `urlmon.h` itself carries the notice "This file is part of the mingw-w64
runtime package. No warranty is given; refer to the file DISCLAIMER within this
package", and that `DISCLAIMER` states ZPL 2.1. So the default licence is ZPL,
and only specifically marked files are public domain -- the opposite of what was
recorded earlier.

**It is also generated from Microsoft's IDL.** The first line of mingw-w64's
`urlmon.h` is:

    /*** Autogenerated by WIDL 11.12 from include/urlmon.idl - Do not edit ***/

The header is a machine translation of Microsoft's interface definition, not
independently authored material. Treating it as a clean third-party source for
signatures does not survive that fact.

**And it is desktop-only, by its own gating.** Line 463 of the same file is
`#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)`. It is not a Windows CE
header in any sense, which is the same conclusion the `shlwapi` overlap arithmetic
reached from the other direction.

**Consequence.** A `urlmon.h` covering all 46 exports of CE's `urlmon.dll` had
already been generated from that header. It was never committed, and it has been
deleted. `dnsapi.h`, `schannel.h` and `shlwapi.h` were not generated. Per the
instruction that a module with no safe public source should not be built, the
ten uncovered modules stay uncovered: `urlmon` 46, `btdrt` 55, `cellcore` 34,
`uspce` 31, `msmqrt` 25, `sim` 19, `sms` 14, `shlwapi` 96, `schannel` 5,
`dnsapi` 4 -- 335 exports in total, with a `.lib` and no header. Their export
lists are still published in `def/`, so the symbols remain linkable; only the
declarations are absent.

**One change from that work was kept, on its own merits.** Wiring `urlmon.h` up
showed that the kit's `objidl.h` declared `LPBC` but not `LPBINDCTX`. The CE 6.0
reference declares both, at `objidl.h:1674` and `:1676`, so `LPBINDCTX` is a
genuine gap in the kit and was added. That fix is corroborated by the CE
reference and does not depend on any desktop header.

### Audit of header names and placement against the CE 6.0 reference

Every kit header was checked against the CE 6.0 reference for two things: does
a header of that name exist in the CE SDK, and is each declaration in the header
CE puts it in.  This found four real faults, all now fixed.

**`toolhelp.h` and `tlhelp32.h` were the wrong way round.** CE calls this
surface `tlhelp32.h`; there is no `toolhelp.h` in the CE SDK.  The kit had all
118 lines of content in `toolhelp.h` and made `tlhelp32.h` a nine-line shim, so
the CE-canonical name was the alias.  The shim's comment also asserted the
opposite of the truth -- "Alternate name for toolhelp.h, which is how Windows CE
names it".  The content now lives in `tlhelp32.h` and `toolhelp.h` is the shim,
kept because `toolhelp.dll` is the module the entry points come from.  The same
check was run on `aygshell.h`, the other alias in the kit, and that one was
already correct: content in `shellsdk.h`, which is the CE 6.0 name.

**`ws2tcpip.h` did not exist.** CE declares the getaddrinfo family and the
per-socket TCP/IP option structures there, separate from `winsock2.h`.  The kit
had declared `getaddrinfo`, `getnameinfo` and `freeaddrinfo` in `winsock2.h` and
had no `ws2tcpip.h` at all, so `#include <ws2tcpip.h>` resolved to the *host
toolchain's* header.  `fwapi.h` hit that and had to be rewritten.  `windef.h`
was also missing `FAR`, `NEAR`, `far`, `near` and `CONST` entirely, which the CE
6.0 reference defines at `windef.h:154` and which `ADDRINFO` uses.

**`prsht.h` and `icmpapi.h` did not exist.** CE declares the property sheet
handle, notification record and three entry points in `prsht.h`, and the four
ICMP helpers in `icmpapi.h` -- separate from `commctrl.h` and `iphlpapi.h`
respectively, though the same DLLs export them.  The kit had them in those two
headers.  `HPROPSHEETPAGE` was in `windef.h` as an alias for `HANDLE`; CE
declares it as a pointer to an incomplete `struct _PSP`.  All thirty `PSN_*`,
`PSM_*`, `PSBTN_*` and `PSNRET_*` constants were in the kit's `commctrl.h`; CE
declares all thirty in `prsht.h` and none in `commctrl.h`.

**`oleauto.h` did not exist.** CE splits the automation surface: `oaidl.h` holds
the types and has no `DECLARE_INTERFACE` at all, while `oleauto.h` holds the 244
`WINOLEAUTAPI` prototypes and includes `oaidl.h`.  The kit had both halves in
`oaidl.h`.  The 238 prototypes now live in `oleauto.h`.

Five kit headers still have no same-named CE reference header, and each is
intentional: `wcever.h` is the kit's own version selector, `wcestr.h` holds the
CRT string prototypes CE spreads across its own CRT headers, `wininet.h` and
`shellsdk.h` do exist in CE but under `PUBLIC/IE/SDK/INC` and as the CE 6.0
spelling respectively, and `aygshell.h` and `toolhelp.h` are now documented
aliases.

### The verify3 count moved down for the wrong reason, and that is recorded

The CE6 total went 93 -> 90 across these changes.  It is not an improvement in
correctness.  Measured against the committed state rather than assumed:
`commctrl.h` went from 16 differences to 13, exactly the three property sheet
prototypes leaving it for `prsht.h`, and `iphlpapi.h` stayed at 6, so the four
ICMP prototypes were never counted as differences.  Three declarations moved out
of reach of the checker.  `oaidl.h`, `oleauto.h`, `prsht.h`, `icmpapi.h` and
`ws2tcpip.h` are all headers verify3 cannot preprocess, so the placement work
that put declarations into them necessarily *reduces* the reported figure.  A
falling number here means less is being checked, not that less is wrong.
