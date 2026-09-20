# Akari-dev Agent Guide

## Purpose

Akari-dev is the project where a clean-room, independently authored Windows CE Development API Surface is constructed.

It is **not** a Windows CE OS reimplementation, SDK reconstruction, BSP reconstruction, OAK reconstruction, or third-party implementation import.

## Repository boundary

`wince-docs-corpus/` is a separate repository. It provides public evidence and normalized facts; Akari-dev uses that evidence to construct its own declarations, ABI/export contracts, linker interfaces, generators, and validation artifacts.

When a specification question is unresolved, use the corpus and its evidence records rather than guessing.

## Core invariants

- Do not copy, transform, or incorporate third-party implementation source into Akari-dev.
- Keep documented facts separate from interpretations and implementation decisions.
- Do not infer DLL, export, import library, calling convention, ABI, version, or availability from an API name alone.
- Preserve Windows CE generation/version differences; do not silently create one universal definition when the evidence distinguishes generations.
- Treat desktop Win32 material as comparative context unless CE-specific evidence establishes the fact.
- Keep generated artifacts and hand-written sources distinguishable.

## Before editing

1. Inspect the existing code, generators, data files, tests, and generated artifacts relevant to the task.
2. Identify the source-of-truth data used by the affected artifact.
3. For API/ABI/specification questions, consult `wince-docs-corpus` evidence records.
4. Make the smallest change that satisfies the requested outcome.

Read only the detailed guidance relevant to the task:

- `docs/agent/architecture.md` — repository boundaries and artifact flow.
- `docs/agent/evidence-contract.md` — what evidence is required for API/ABI decisions.
- `docs/agent/clean-room.md` — source handling and independent implementation rules.
- `docs/agent/verification.md` — risk-based validation and completion criteria.
- `docs/exec-plans/README.md` — persistent plans for multi-step work.

## Implementation contract

Think in terms of:

```text
public evidence
    -> normalized facts
    -> Akari-dev source of truth
    -> declarations / ABI / linker artifacts
    -> generated output
    -> verification
```

Prefer changing the authoritative input and regenerating outputs over editing generated files directly.

## Verification

Run checks appropriate to the change. High-risk changes include public ABI, structure layout, exports, import libraries, generator logic, generation/version availability, and cross-repository source-of-truth changes.

After the first verification pass, review whether the selected checks actually cover the change and whether any assumption remains unverified. Then rerun the affected checks as needed. Do not automatically rerun every expensive check for every small change.

Record failures and unknowns honestly. A green build does not establish API correctness or clean-room provenance by itself.

## Git

Keep diffs focused. Inspect `git diff` and `git status` before completion. Commit or push only when the requested workflow requires it.
