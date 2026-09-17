# Akari-dev — Windows CE API surface

Akari-dev provides the **Windows CE API surface** needed to build
[llvm-project](https://github.com/kagurasumusun/llvm-project) (branch
`LLVM-WinCE`, `*-pc-wince` triples) against Windows CE targets:

```
Akari-dev
├── include/    Windows CE API headers (CE .NET 4.x / 5.0 / 6.0; oak/ = platform headers)
├── def/        module export definitions (<module>-doc.def, one per CE DLL)
├── import libraries   built from def/ with llvm-dlltool
└── startup/    EXE/DLL startup objects and CRT glue for Clang/lld WinCE targets
```

**This is not an SDK and not an OS reimplementation** — only the API
surface above, and nothing else, is in scope.

## Evidence policy

Every declaration and export is grounded in the **official Microsoft
Windows CE documentation** preserved verbatim in the companion corpus
repository [kagurasumusun/wince-docs-corpus](https://github.com/kagurasumusun/wince-docs-corpus)
(MSDN / Microsoft Learn / Wayback Machine). See
[docs/clean-room.md](docs/clean-room.md) (v3, 2026-09-18) for the full
rules; in short:

* **Admissible:** official CE documentation pages only (page ids are
  annotated per declaration).
* **Absolutely excluded:** Wine, ReactOS, MinGW, mingw-w64, desktop
  w32api/mingwrt, desktop-Win32 analogy, shared-source/Platform
  Builder/Visual Studio source, non-public or dump-derived material.
* **Single exception:** the CeGCC-lineage w32api ("R1") and CeGCC
  mingwrt may be used for **value confirmation only** where official
  pages print names but not values; R1 never supplies declarations,
  text, or name sets.

## Building / checking

```sh
make hostcheck   # compile every header for _WIN32_WCE = 0x420/0x500/0x600
make cxxcheck    # same for the C++ view headers
make defcheck    # validate every def/ module surface
make check       # all three
make -C startup  # startup objects (arm-pc-wince cross build)
```

Import libraries are generated from `def/*.def` with
`llvm-dlltool -k` against the `*-pc-wince` triple.

## Session workflow

1. Start of session: clone/pull `wince-docs-corpus` (the corpus lives
   on GitHub; the sandbox copy is disposable).
2. Work: cross-check headers/defs against the corpus; harvest missing
   pages with the corpus' `tools/harvest.py` (rate-limited, resumable);
   push both repositories frequently.
3. End of session: everything except this repository is removed from
   the working environment.

## Audit ledgers (docs/)

* `clean-room.md` — evidence policy v3
* `unpublished-constants.tsv` — name-only constants held per policy §5
* `def-audit-coredll-2026-09-18.tsv` — coredll.def rebuild ledger
  (keep / pending-regrounding / add / drop, per name)
* `def-gap-triage-2026-09-18.tsv` — documented link libraries without
  a def, triaged (COM/GUID, driver-static, resource, needs-check)
* `header-gap-2026-09-18.tsv` — headers named by official pages that
  are not shipped yet
