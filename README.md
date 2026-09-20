# Akari-dev

A clean-room, independently authored Windows CE development API surface.

## Initial vertical slice

`data/apis/winbase.json` is the local authoritative implementation input for the initial `Winbase.h` group (`GetTickCount` and `Sleep`). It records only facts consumed by this repository and pins the normalized upstream corpus record and commit that established them. `tools/generate_surface.py` deterministically produces:

- `generated/include/winbase.h` — the independently authored `GetTickCount` declaration and a 32-bit `DWORD` definition;
- `generated/link/winbase.link.json` — the documented CE 5.0 `Coredll.lib` linker requirement and explicit nulls for module/export facts not established by the evidence.

No DLL name, export name/ordinal, or calling convention is inferred. Consequently this slice deliberately does **not** generate a `.def` file or import library. The link metadata is a build-input contract, not a replacement for those missing facts.

Regenerate with `python3 tools/generate_surface.py`; reject stale artifacts with `python3 tools/generate_surface.py --check`; verify with `python3 tests/verify_surface.py`.
