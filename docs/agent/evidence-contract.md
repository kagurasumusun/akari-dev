# Evidence Contract

## Purpose

Define the minimum evidence needed before turning a Windows CE fact into an Akari-dev implementation decision.

## Evidence classes

Treat each claim as one of:

1. **Observed** — directly stated or directly observable in an acceptable public source.
2. **Correlated** — supported by multiple independent sources or by matching records with preserved provenance.
3. **Inferred** — a reasoned conclusion not stated directly by a source.
4. **Unknown** — not established by available evidence.

Only the first two classes should normally become authoritative implementation facts. Inferences must stay explicitly marked until independently supported.

## API evidence

For an affected API or symbol, collect the fields that matter to the task, such as:

- API/function/type/constant identity;
- prototype or declaration shape;
- header name and placement;
- DLL/module;
- export name and ordinal when documented;
- import library;
- calling convention / ABI;
- structure layout or packing requirements;
- CE generation / OS version;
- availability and restrictions;
- kernel/user-mode placement when relevant;
- source identifier and locator.

Do not invent missing fields from naming conventions.

## Conflict handling

When sources disagree:

- keep the source provenance;
- preserve generation/version context;
- identify exactly what differs;
- prefer stronger, more direct evidence;
- do not silently merge incompatible facts;
- record the unresolved state when evidence remains insufficient.

## Comparative sources

ReactOS, Wine, mingw-w64, mingw-w32, w32api, w64api, CeGCC, and mingw32ce are comparative material, not direct Windows CE specifications. Use them for gap detection, relationship discovery, historical comparison, or implementation-structure ideas only.

## Upstream rule

When Akari-dev needs a fact that the corpus cannot currently support, prefer improving the corpus evidence/database over encoding an unsupported guess in Akari-dev.
