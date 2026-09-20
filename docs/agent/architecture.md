# Architecture

## Role

Akari-dev is the implementation-side repository for a Windows CE Development API Surface. Its job is to express publicly documented interface facts as independently authored development artifacts.

## Boundaries

```text
wince-docs-corpus
    public documents
        ↓
    observed / normalized facts
        ↓
Akari-dev
    source-of-truth data
        ↓
    headers / ABI definitions / .def / import libraries / generators
        ↓
    buildable development interface
```

The corpus is evidence. Akari-dev is an independent implementation of an interface derived from that evidence. Neither repository is a Windows CE operating-system source tree.

## Artifact model

Keep these concerns separable:

- API declarations: names, types, constants, prototypes, header placement.
- ABI contracts: calling convention, structure layout, decoration, alignment, architecture-specific details.
- DLL/export contracts: module, exported symbol, ordinal/name behavior when documented.
- Linker interface: import libraries and other link-time artifacts.
- Availability: CE generation, OS version, architecture, and other documented conditions.
- Generation tooling: deterministic transformation from authoritative project data to generated artifacts.
- Verification: checks proving that generated artifacts agree with the source of truth and recorded evidence.

## Design consequence

An API record is not complete merely because its prototype is known. Where applicable, implementation must also account for header, DLL/export, import library, ABI, generation/version, and availability data.

Likewise, a buildable artifact is not proof that the underlying Windows CE fact is correct.
