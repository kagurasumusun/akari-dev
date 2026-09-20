# Initial Winbase starter group

## Objective

Establish a reproducible evidence-to-artifact path for a native Windows CE API group without adding unsupported export or ABI claims.

## Completed work

1. Normalized the public CE 3.0 and CE 5.0 GetTickCount and Sleep (plus CE 6.0 corroboration for GetTickCount) documentation into `wince-docs-corpus/data/api/{gettickcount,sleep}.json` and committed it as `79d0c1100300f3b239181e634295a2b343f73d8d`.
2. Added an Akari-local group source record that pins that corpus revision.
3. Generated `winbase.h` for both declarations and linker-requirement metadata from the local record.
4. Added stale-output, metadata, 32-bit-width, and C syntax checks.

## Evidence and decisions

The corpus record classifies the prototype and header as corroborated, the CE 5.0 `Coredll.lib` requirement as observed, and the 32-bit `DWORD` width as observed. The generated `uint32_t` spelling is an Akari implementation decision preserving that width; it is not copied header text.

## Explicit gaps

The available record does not establish a calling convention, DLL module, export name/ordinal, or a CE 6 user-mode linker contract. Akari emits null metadata rather than guessing; no import library or `.def` is produced.

## Next work

Research a publicly documented DLL/export and calling-convention contract before adding linker binaries or decorated declarations. Extend the corpus schema only when evidence supports those fields, then add a generation-specific Akari record and artifacts.
