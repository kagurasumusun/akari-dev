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

## Environment hazards (hit 4× now)
- Snapshot rollbacks wipe: corpus clone, .git config/identity, file
  modes, /home/user/.claude memory dir, and can roll Akari-dev back to
  an old commit with stale worktree files. Recovery recipe: re-add
  origin PAT remote (owner `kagurasumusun`), fetch, `git reset --mixed
  origin/main`, `git checkout -- .`, chmod 755, re-clone corpus, set
  git identity, use THIS file for session state.
- Audits take the corpus ROOT (they scan docs/ themselves).
- GitHub owner is `kagurasumusun` — `AkariOS`/`akarios-jp` do not exist.
