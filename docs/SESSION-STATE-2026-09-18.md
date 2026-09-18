# Session state — 2026-09-18 (continuation 9, final)

Akari-dev pushed through `e9d6fce`. All audits 0 MISMATCH.
Corpus: kagurasumusun/wince-docs-corpus @ `171adda42` (85,816 pages,
layout `docs/{mslearn,chm,wayback-msdn}/<generation>/*.html`;
INDEX at `data/index/INDEX.tsv`).

## Shipped this continuation (commits)
- `d91c216` proto citation backfill: tools/proto-cite.py — 385 decls
  cited, proto no-pageid 459→68, match 2,160. 81 latent diffs surfaced
  and resolved as documented artifacts: Tapicomn TSPIAPI decoration
  (76, TSPIAPI=WINAPI empty in tree), Icmpapi glued WINAPI span (2),
  Winldap UNICODE-decorated return (2), Winsock2 inet_ntoa decl spacing
  fixed (DECL regex was swallowing ioctlsocket). Extractor fixes:
  struct-audit match-truncated-print (+3), fnptr-audit block-end.
  absent-prints.py made permanent; app-layer in-def absent set
  EXHAUSTED (remainder = 27 oak kernel + 59 CRT + 1 nkstub).
  Const backfill dead end confirmed: 5 of 1,569 no-pageid names have
  value prints corpus-wide.
- `a338d37` tools/type-cite.py: 112 struct + 6 fnptr citations;
  struct match 669→781 (no-pageid 24), fnptr 59→65 (no-pageid 30).
- `fd59895` tools/enum-cite.py: 113 citations; enum match 164→277
  (no-pageid 5).
- `fabc801` def-gap.py recursive-walk fix (2-level scan found 0 libs on
  new layout); at 85,816 pages: 153 documented libs / 127 defs /
  49 no-def (30 DLL-backed). Old 14 still zero evidence. Triage ledger
  rewritten: 12 app-candidates, 18 oak-excluded.
- `e9d6fce` no-pageid cleanup: Storemgr 3 + Wincrypt 2 documented
  deviations annotated with pids; proto-cite base-name scanning for
  W/A variants (+24 cites, no-page bucket zeroed)
- `25c96db` tools/gen-app-defs.py + 4 new defs: cellcore-doc.def (56),
  wsdapi-doc.def (6), sms-doc.def (4), gpsapi-doc.def (2). No def for
  av_upnp/imaging/mqoa/shdocvw/mqelib/wap/owaexchangeclient/
  commctrlview — their pages are COM method pages (vtable surface).

## Audit state (corpus 171adda42, 85,816 pages)
- const: 2,026 match / 0 MISMATCH (no-pageid 1,582 = verified
  no-print; name-no-value 937; name-not-on-page 159)
- proto: 2,176 match / 0 MISMATCH (no-print 873; no-pageid 42;
  annotated 101 all documented; argc-page-short 3; page-drops-star 17)
- struct: 781 match / 0 (no-print 158; no-pageid 24; truncated 3)
- enum: 277 / 0 (no-print 69; no-pageid 5)
- fnptr: 65 / 0 (no-print 50; no-pageid 30)
- surface: declared 6,706 / absent 2,365 / D1–D5 = 0; make check 0

## Citation-backfill tool family (all cache scans in build/)
proto-cite.py / type-cite.py / enum-cite.py — cite only exact-match
pages; comment wording matters: proto-audit annotated triggers are
artifact|print shows|prints a|printed|the print|print `|\bprint\b|
missing comma|dropped|typo; enum-audit: artifact|page print|omits.
Unresolved remainders: docs/{proto,type,enum}-cite-unresolved.tsv.

## Next axes
1. proto no-print 870: try CE5↔CE6 twin pages / sibling generation
   pages for decls whose cited page lacks the print.
2. no-pageid remainders: proto 42 (print-differs; sampled Storemgr/
   Wincrypt cases = documented deviations, rest likely same class),
   struct 24, fnptr 30, enum 5.
3. COM surface for av_upnp/wsdapi/imaging/shdocvw (vtable decls,
   separate jurisdiction — decide scope with user).
4. const name-no-value 937 / name-not-on-page 159 sweeps.
5. Harvest re-sweeps (msdn-live 31,388 / mslearn-embedded 38,726
   queues not dispatched).

## Continuation (cont. 12) -- 95,439-page corpus sweeps + printed-absent declarations
Commits: `38d3a10` (const sweep +9 dvddrvr citations; conflict verdicts
file docs/const-cite-conflict-verdicts-2026-09-18.tsv: 10 'differs' =
mispairings/context prints, decls stand), `1019f1d` (audits refreshed,
0 MISMATCH), `1a19174` (gpsapi 2 + sms 9), `5862d52` (wzcsapi Ex 4 +
cellcore 3), `79bfe6d` (wsdapi 20 + urlmon 1 + rapi2 2), `5365361`
(STDAPI wording; audits: surface declared 6,780 / absent 2,577; proto
2,212 match / 0 MISMATCH).
- **35 corpus-printed previously-absent functions declared** (found via
  absent-prints rescan 1,062 prints -> page Link Library vs shipped
  defs): gpsapi 2, sms 9, wzcsapi Ex 4, cellcore 3 (ConnMgr 2 +
  SimGetPhonebookCapabilities), wsdapi 20, urlmon 1, rapi2 2.
- Types added with page cites: GPS_POSITION (ee484992 full print;
  earlier `} NAME;` regex missed `*PGPS_POSITION` aliases!),
  GPS_MAX_SATELLITES=12, SMS_ADDRESS (ee498006; SMS_MAX_ADDRESS_LENGTH
  =256 via permitted CeGCC value check, noted), SMS_MESSAGE_ID (no
  print; derived GUID, noted), SMS_STATUS_INFORMATION, SMS_BROADCAST_
  RANGES, SCHEDULEDCONNECTIONINFO, CONNMGR_CONNECTION_DETAILED_STATUS,
  12 WSD XML/SOAP structs, LPSIMPHONEBOOKCAPS alias, UINT64=ULONGLONG.
- Opaque (pointer-only) where print chain dead-ends: GPS_DEVICE,
  INTF_ENTRY_EX (needs RAW_DATA - no page), CONNMGR_CONNECTION_IPADDR
  (needs unprintable _SS_PAD sizes), 11 IWSD* + IServiceProvider
  (no vtable-order pages).
- HELD (unprintable array-size constants, noted in headers):
  SmsSetMessageNotification (SMS_MAX_APPNAME/PARAMS/PROTOCOLNAME),
  ConnMgrEnumDestinations (CONNMGR_MAX_DESC), SimGetDevCaps
  (SIM_NUMLOCKFACILITIES), SimReadMessage/SimWriteMessage
  (MAX_LENGTH_*), Sim*PhonebookEntry* (MAX_LENGTH_*/MAX_NUM_GROUPS),
  WZCEnumEapExtensions (no EAP_EXTENSION_INFO page). CeGCC lacks all
  these constants too (checked simmgr.h/sms.h).
- proto-audit 'annotated' trigger needs comment words
  (artifact|print `|printed|...): `HRESULT STDAPI` prints resolved by
  wording, not code.
- const sweep on new corpus: const-index 19/2,501 gap names have
  prints; const-cite +9 (dvddrvr.h); absent-prints rescan: 1,062
  prints / in-def exhausted (88 coredll = oak/CRT + nkstub 1).
- NOTE: docs/absent-funcprints-2026-09-18.tsv is now stale (31 of its
  rows declared after the scan); re-run tools/absent-prints.py before
  reusing it.
- Remaining axes: thin-header fills (mostly done: 14 empty headers are
  cited aliases with real carriers), proto no-print 873 twins,
  no-pageid 42, deeper derivations, ceddk/fsdmgr/sdcardlib (driver-
  layer: OUT per oak scope).

- **twin axis DONE** (`bf6a867`): tools/twin-proto-scan.py over 872
  no-print decls -> 557 twin-match (sibling-generation print
  evidence), 167 twin-diff ALL classified (118 ret-convword e.g.
  WINAPI/CRYPTFUNC/WINOLEAPI/TSPIAPI in prints, 22 star-drop/extra,
  P-alias/spelling, CE5-vs-CE6 generation deltas like CeFindNextFile
  LPCE_FIND_DATA, NdisWriteErrorLogEntry variadic `ULONG ...` marker)
  -> ZERO declarations changed; 108 no-twin-page + 41
  no-print-in-twin = no further evidence.

## Continuation (cont. 13) -- comment-only axis + HELD recheck + struct twins
Commits: `02cd9e4` (8 functions: Ce_setup 4 developer-provided,
DirectInputCreate + derived LPDIRECTINPUT, CeSetDevMgmtTask;
OS_DEP_DATA, DMSDLINFO, LPDSENUMCALLBACK + 2 Dsound enumerates),
`a45a9f7` (Celog.h 51 CEL_* structs -- HELD notes were stale;
CEL_INT_DATA from CHM page), `6a6d8be` (9 types: CFF/PFF_CONVERTINFO,
HREPLFLD/HREPLITEM, 3 Avc STREAM_*_Request, UNIT_AllocateLocalPlug_
Request, DELETE_SECTOR_INFO; blockers pinned), `2f41828` (audits:
surface declared 6,847 / comment-only 2,179 / absent 2,579; const
match 2,036), + twin-struct-scan commit.
- comment-only 2,248 breakdown: 245 print-recorded (69 app-layer;
  declarables extracted above, rest blocked on unprintable types),
  230 HELD (rechecked: Celog 51 + 9 declared; precise blockers now
  recorded per family: _MAX_* CRT sizes, OBJTYPENAME/MAX_OBJTYPE_
  NAME, STREAM_SESSION_ID/STREAM_BUFFER_ID, WAVEFILTER, PFN_REQDONE,
  READER_EXTENSION family, CONNMGR_MAX_DESC, CE5-vs-CE6 deltas),
  1,091 book-record pattern (642 concept-page mentions = false
  positives, 392 name-only, 20 no-print, 10 const-value records --
  TBM_GETPOS/TVM_SETITEMSPACING values unprintable), 618 loose
  mentions.  Axis exhausted; remaining comment-only are legitimately
  unprintable or non-API mentions.
- **twin-struct-scan** (tools/twin-struct-scan.py): 160 no-print
  structs -> 60 twin-match, 20 twin-diff ALL reviewed as scanner
  artifacts (fused print tokens, comments-as-members, dropped
  semicolons, C++ #ifdef blocks, DLGTEMPLATEEX variable-length
  pseudo-members) -> ZERO declaration changes; 66 no-print-in-twin,
  16 no-twin-page.
- const name-not-on-page 159: 15 have other-page prints, all known
  mispair classes (AF_INET6 firewall ports, DT_* perftest syntax);
  decls stand.
- Harvest: dispatched urls/mslearn-embedded.txt (38,726 URLs) via
  harvest.yml workflow_dispatch at 2026-09-18T10:38Z (run
  in_progress; sequential rate-limited).
- Snapshot rollback hit again this turn (Akari-dev at 9f4b870, corpus
  .git wiped): recovered via PAT remote + reset --mixed + re-clone.
  core.fileMode=false set.

- **Add_Share defect FIXED** (`8e0275c`): decl had 3 params + cited
  aa450328 = the Del_Share page; real page aa450283 prints 7 params
  (pACL/pROACL/pDriver/pComment were missing).  tu_compile.c test
  call updated.  Found via the no-pageid pid-backfill sweep.
- **pid backfill**: 37 of 42 proto no-pageid decls have title-page
  prints; 34 verified identical -> pid comments inserted.
  proto-audit now: match 2,242 / no-pageid 13 / MISMATCH 0.
- twin-enum-scan (`391a912`): 69 no-print enums -> 2 match, 1 CE5/CE6
  delta (SPSTREAMFORMAT), 61 no-print-in-twin.
- Harvest findings: urls/msdn-live.txt is NOT fetchable (harvest.py
  has no live-MSDN URL parser; run completed stored=0) -- the
  wayback-msdn-2010.txt queue (31,388 archive URLs, same pages) is
  the fetchable form; dispatched 2026-09-18T10:51Z (1.5s delay,
  500-page batch pushes; runner will persist partial progress on
  timeout).  mslearn-embedded.txt queue was already exhausted
  (+2 pages only).

## Environment hazards (hit 4× now)
- Snapshot rollbacks wipe: corpus clone, .git config/identity, file
  modes, /home/user/.claude memory dir, and can roll Akari-dev back to
  an old commit with stale worktree files. Recovery recipe: re-add
  origin PAT remote (owner `kagurasumusun`), fetch, `git reset --mixed
  origin/main`, `git checkout -- .`, chmod 755, re-clone corpus, set
  git identity, use THIS file for session state.
- Audits take the corpus ROOT (they scan docs/ themselves).
- GitHub owner is `kagurasumusun` — `AkariOS`/`akarios-jp` do not exist.

## cont.14 sweep (2026-09-18, commits d1d7fdf..HEAD)
- twin-proto citation re-anchor: 557 twin-match rows got `twin-print:
  <pid>` comments above the decl -> proto-audit match 2,242->2,610,
  no-print-on-page 876->509, MISMATCH 0.
- no-pageid backfill round 2 (struct/enum/fnptr title-page scan): 16
  of 55 have pages; RASPROJECTION gained RASP_PppIpV6=0x8057 (CE5
  page aa450856 prints it; older archive print lacks it); cites for
  FW_RULE_MASKS (aa450390) + 5 PDCARD structs (ms922799-856,
  Sockserv.h).  CHM-page names (BATTERY_STATUS etc.) left as-is.
- twin-fnptr-scan: 50 no-print fnptrs -> 6 title pages, 1 match;
  fnptr evidence axis EXHAUSTED.
- absent-types-scan (tools/ + docs/absent-types-scan-2026-09-18.tsv):
  2,663 absent names have page prints (proto 2,455 / enum 130 /
  const 78).  Declared: 24 D3D Mobile enums in D3dmtypes.h (240
  enumerators, page prints verbatim; D3DFORMAT MAKEFOURCC entries
  #ifdef-guarded - macro undocumented in corpus; 260 verified by
  make check).  HELD (out of scope / no header): csmedia camera-DDK
  7, DirectMusic 8 (Dmusici.h not in tree), AM_* 2 (no header on
  page), eXDI2 3, FlexiPMT 3, oak/OAL/KITL/SD/NDIS/RIL 10, Dbgapi
  (oak) 4, RTC (oak) 3, lfapi 1, registry/BIB config consts (all 78
  const hits: AUTOSIZE_*, DLL*ADDR*, cbNK*, dwNK* etc).
- surface-audit BUG FIX: BOOKTAG skipped uncategorized (2,086) +
  dotnet-compact-framework (8,985) titles.  Now declared 6,876 /
  comment-only 2,181 / absent 2,794.  +239 new absent names ALL
  verified managed .NET/SPOT (ComPortHandle=SPOT.Emulator, TouchInput
  =SPOT.Touch, WsFaultType/WsPrefix=Ws.Services, crypto params) ->
  not native candidates; dcf/misc tag in TSV col2 marks them.
- const HELD cross-check (rebuilt /tmp/const-index.tsv value-form,
  3,217 names): 928 name-no-value-on-page -> only 3 documented
  elsewhere: MAX_PATH (=128 but DVD/IDL-local on UNICODE_PATH pages;
  global 260 value-checked vs CeGCC w32api windef.h, noted in
  Windef.h), EM_SETLIMITTEXT (ee499421 alias of EM_LIMITTEXT; already
  0x00C5), EXCEPTION_ACCESS_VIOLATION (=STATUS_ACCESS_VIOLATION
  alias, aa450192; already 0xC0000005L).  0 pinned blockers unblocked.
  const no-pageid 1,583: 0 have documented values (derived tokens).
- wayback-msdn-2010 harvest (dispatched 19:05Z, batch=200): ~3h no
  batch push; wayback answers 302 fast from sandbox, harvest.py has
  60s timeout x5 retries -> runner likely in Retry-After backoff.
  Left running (6h runner cap ~01:05Z); if killed with 0 pushes,
  re-dispatch with batch=25.  On yield: pull corpus, re-run surface/
  proto/const audits, re-sweep B blockers on new pages, absent recheck.

## cont.14 harvest resolution (evening)
- ROOT CAUSE of 0-yield wayback runs: harvest.py resume index used raw
  filenames; 17,622 stored files carry `(v=...)` suffixes, so ~30,937
  already-harvested queue URLs were RE-FETCHED every run (never
  reaching a batch push within the runner cap).  Fixed: bare-id
  indexing of (v=) files (corpus commit 06283904a).
- Queue truths: wayback-msdn-2010.txt = 30,937 already stored + 1 new
  pid (ms838324) + 450 legacy-slug URLs (/library/01c3x0ze.aspx form
  - parseable by dest_for, genuinely new content).
  to-fetch-mslearn.txt = 0 new (fully harvested).  The only remaining
  collection work is those ~451 pages.
- Owner (kagurasumusun) actively working in corpus repo same evening:
  massive harvest.py refactor (5b4c59c69, +708/-156, keeps my (v=)
  fix, adds learn.microsoft.com parser) + own dispatch/cancel cycles
  that cancelled my runs B/C via workflow concurrency.  Final run D
  35392202849 (head 5b4c59c69, batch=25) in flight at session end.
- NEXT SESSION: check run D; if pushed, pull corpus, count new pages
  in wayback-msdn/2010-05, re-run surface/proto/const audits, re-sweep
  B blockers + absent recheck on new pages.  If D cancelled by owner
  activity again, coordinate timing / re-dispatch off-peak.

## cont.15 (2026-09-19, user order: defs/headers structure, empty headers, SQL index, rate limits)
CORPUS (wince-docs-corpus, shared with owner kagurasumusun):
- tools/build-index-sql.py + data/index/corpus.sqlite3 committed
  (9380a697b): pages/names(kind=title|const|proto|struct|enum) tables,
  incremental by file size, full build 2m45s, no-op pass 0.8s.
  Workflow refresh step updates it.
- harvest.py: adaptive throttle (429/503 consecutive -> delay x2 up to
  20x + jitter; only ever slows down), Retry-After to 300s, end-of-run
  retry pass for non-404 fails, fail logs committed per batch.
  urls/msdn-live.txt deleted.  Owner's big refactor 5b4c59c69 absorbed
  the (v=) resume fix.
- Run E 35396319250 (batch=25) YIELDING: first batch 01c7dadcb +25
  pages 21:58Z.  Cancelled a duplicate concurrent run (35399399544) -
  never run two harvesters (double wayback access).
- Queue truth: only ~451 pages new (450 legacy /library/<slug>.aspx +
  ms838324); everything else already stored.
AKARI-DEV:
- DEF RESTRUCTURE (user-flagged): 41 component defs merged into
  coredll-doc.def (1,064->1,413 exports; gwes Module ms923451 +
  coredll Module aa448387 prove componenthood; Nk.lib/Ceddk.lib/etc
  are CE1.0-era import spellings, no such DLLs); 22 defs deleted
  (18 driver/BSP static libs oak-scope, imgctl=commctrl duplicate,
  msimeuic/urlmonui/wininetui undocumented).  131 -> 69 defs (+owner's
  wap).  gen-doc-def.py: COREDLL_COMPONENTS/FORBIDDEN_TOKENS +
  PhCommon.dll module-form mapping.
- Header structure: Commandapi/Databaseapi/Phoneapi/Settingsapi ->
  .hpp (page spelling) + new def/phcommon-doc.def (16 PH* exports,
  "Library: PhCommon.dll" rows); Tchaud/dvdcss/dvddrvr/Fatui moved to
  include/oak/ (DDK/PB content); Makefile+tu_compile updated.
- def-gap closure: +51 documented exports across 10 defs (CryptMsg*8,
  Hwx* 22, Bth*5, Icmp*5, SHChangeNotify*3, ...); undeclared-fn triage
  done (118): SIMCALLBACK+SimInitialize+LPHSIM declared; rest blocked
  on pinned HELD constants (IPAddr, CONNMGR_MAX_DESC, MAX_LENGTH_*,
  EAP_EXTENSION_INFO, SIMCAPS) or page artifacts (sibling-signature
  prints: WSDCreateDeviceProxyAdvanced, PrivacySetZonePreferenceW,
  CoInternetCreateZoneManager) - records verified accurate.
- Empty-header review: 14 zero-decl headers = COM vtable-order HELD
  (interface pages print method tables "in alphabetical order" -
  confirmed again on ms891543) or include-compat shims (D3dmcaps:
  D3DMCAPS lives in D3dm.h; VARIANT/BSTR in Objbase.h).  Legit.
- Commits this cont: e51d394(def restructure) 47de542(headers)
  c82fcf4(RasGetDispPhoneNum) a3c9eec(+51 exports) 506f8a7(SimInit).
  Owner interleaved 6ae383b (Wap.h + wap-doc.def + Makefile).
- NEXT: wait run E finish -> pull corpus -> refresh SQL index ->
  re-run surface/proto/const audits + B-blocker re-sweep + absent
  recheck on new wayback pages; make check 0 at all times.
