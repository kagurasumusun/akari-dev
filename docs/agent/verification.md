# Verification

## Principle

Verification is risk-based. Match the checks to the changed contract instead of treating every task as a full repository audit.

## Relevant checks

Depending on the change, verify:

- declarations and compile behavior;
- source-of-truth ↔ generated-output consistency;
- generator determinism;
- API completeness;
- header placement;
- DLL/export mapping;
- import-library/linker behavior;
- ABI, calling convention, alignment, and structure layout;
- CE generation / OS-version availability;
- kernel/user-mode placement;
- binary or generated-artifact properties;
- clean-room provenance;
- repository scope and unintended changes.

## Two-pass review

Use two distinct questions:

### Pass 1 — Result verification

Did the implementation satisfy the requested contract and do the applicable checks pass?

### Pass 2 — Verification review

Were the right checks selected? Did they cover the risk introduced by the change? Did any assumption, evidence gap, or test limitation remain hidden?

Rerun affected checks after changes. Do not repeat unrelated expensive checks just to satisfy a ritual.

## Completion rule

A change is complete only when:

- applicable verification has actually run;
- failures are resolved or explicitly reported;
- unverified assumptions are recorded;
- generated artifacts are consistent with their source of truth;
- the final diff contains no unrelated change.

A successful build alone is insufficient evidence of API, ABI, availability, or provenance correctness.
