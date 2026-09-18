# Session state — 2026-09-18 (continuation 8)

Akari-dev pushed through `dd62264`. All audits 0 MISMATCH.
Corpus: kagurasumusun/wince-docs-corpus @ `d26b06123` (82,816 pages,
post-reorg layout `docs/{mslearn,chm,wayback-msdn}/<generation>/*.html`;
INDEX at `data/index/INDEX.tsv`, 70,317 rows).

## Shipped in `dd62264`
- Pwinuser.h: GESTUREINFO (ee503892), HGESTUREINFO, 7 touchgesture fns
  (CloseGestureInfoHandle ee504292, DisableGestures ee504053,
  EnableGestures ee499762, GetGestureExtraArguments ee505235 —
  UNIT→UINT page typo noted, GetGestureInfo ee503217,
  QueryGestures ee503597, RegisterGesture ee505707)
- Winnt.h: PULONGLONG (QueryGestures print)
- Winreg.h: CE_REGISTRY_INFO (aa517289), CeRegGetInfo (ee490230),
  AddVectoredExceptionHandler HELD (PVECTORED_EXCEPTION_HANDLER unprinted)
- Regext.h (inside the `_WIN32_WCE >= 0x0600` gate — includes live
  inside it): REGISTRYNOTIFYCALLBACK (ee488033), RegistryDeleteValue
  (ee488640, print drops a comma — noted), RegistryNotifyCallback
  (ee487978)
- tools/proto-audit.py: `page_protos` now accepts mslearn `<pre><code>`
  blocks whose closing `);` falls outside the block. Proto match
  ~900 → 1,863, still 0 MISMATCH.

## Audit state (corpus d26b06123)
- const: 2,026 match / 0 MISMATCH (no-pageid 1,582; name-no-value 937;
  name-not-on-page 159; annotated 7)
- proto: 1,863 match / 0 MISMATCH (no-print 859; no-pageid 459;
  const-diff 19; annotated 15; argc-page-short 3: SealMessage ms926485,
  EnumFontFamiliesExW ms901124, SetTextCharacterExtra ms901144)
- struct: 669 / 0 (no-print 148; no-pageid 149)
- enum: 164 / 0 — fnptr: 59 / 0 (no-print 48; no-pageid 38)
- surface: declared 6,706 / absent 2,365 / D1–D5 = 0; make check 0

## Next axes
1. Citation backfill for app no-pageid gaps (const 1,582 / proto 459 /
   struct 149 / enum 66+81 / fnptr 38+48) on the 82,816-page corpus.
2. def-gap: 14 app libs still with zero "Link Library" evidence
   (commctl, coresip, cryptapi, getpower, httpextn, httpfilt, locusa,
   mixerapi, notify, ole232, redir, schannel, shortcut, user32).
3. Harvest re-sweeps (queues msdn-live 31,388 / mslearn-embedded 38,726
   not yet dispatched).

## Environment hazards (hit repeatedly)
- Snapshot rollbacks wipe: corpus clone, .git config/identity, file
  modes, `/home/user/.claude` memory dir. Recovery recipe: re-add
  origin PAT remote (owner `kagurasumusun`), `git reset --mixed
  origin/main`, `chmod 755`, re-clone corpus, set git identity, use
  THIS file for session state.
- Corpus remote is `kagurasumusun/wince-docs-corpus` — `AkariOS/...`
  and `akarios-jp/...` do NOT exist.
- Audits take the corpus ROOT (they scan docs/mslearn + docs/chm
  themselves); the old `mdsdump/` layout no longer exists.
