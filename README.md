# Akari SDK (cellvm-sdk)

Clean-room **Windows CE application development interface** for building WinCE-targeted applications on a plain host (Linux, macOS, ...). It supplies the Windows CE API declarations and import-library definitions needed to compile and link applications against the real Windows CE OS, plus a small in-tree program-startup support layer.

This repository does **not** implement Windows CE itself. In particular, it does not implement the Windows CE kernel/OS services or DLLs such as `coredll.dll`, and it does not provide a C standard library or C++ standard library. Conceptually, its application-facing API/import portion is closer to a platform `*-dev` package; the startup support is an additional build-time component needed to produce WinCE application images.

Targets:

- `arm-pc-wince` (ARM/armel)
- `i386-pc-wince` (x86 CE)
- Windows CE 4.2 / 5.0 / 6.0

## Responsibility boundaries

| Concern | Provider |
|---|---|
| Windows CE API headers | **cellvm-sdk** (`include/`) |
| Windows CE import-library definitions | **cellvm-sdk** (`def/`) |
| Windows CE program-startup support | **cellvm-sdk** (`startup/`) |
| Compiler/code generation, WinCE target driver, linker and PE/COFF target support | **kagurasumusun/llvm-project** |
| Windows CE OS/kernel and system DLL implementation | **Windows CE device/OS** |
| C standard library | **consumer's C library** |
| C++ standard library / ABI support | **consumer's C++ runtime/toolchain** |

The `startup/` component is startup/process glue, not libc. It supplies PE entry objects and the per-module initialization/data machinery required by WinCE programs, while ordinary C/C++ library facilities remain the responsibility of the consumer's selected runtime.

The OAK/DDK headers under `include/oak/` are a separate driver/OEM development surface. They are intentionally excluded from the ordinary application `-dev` surface and default installation; a small number of application headers may reference leaked OAK types where the documented API requires them.

## Header layout and documentation policy

The repository's filenames and directory layout are an implementation of the documented WinCE API surface; they are not required to reproduce Microsoft's original SDK directory layout verbatim. Where Microsoft documents a declaration under a particular header, that documented header is the canonical declaration location. Umbrella headers such as `Windows.h` may include component headers, but inclusion through an umbrella header does not make the umbrella the canonical declaration owner.

- **Official public information only.** Declarations are based on Microsoft's official Windows CE documentation and the official Win32/PE/ABI references where a CE-specific page does not exist. Sources are recorded in `docs/inventory.md`.
- **CE is not desktop Win32.** A declaration is included only when its CE availability and shape can be established from the documented CE surface.
- **Clean-room implementation.** No declarations or implementation material are copied from w32api, mingwrt, mingw32ce, MinGW-w64, CeGCC, or other third-party SDK trees.
- **MIT licensed.** See `LICENSE`; source files carry the applicable SPDX notice.

## Export definitions and import libraries

The export definitions are derived from the official Microsoft CE documentation. The pipeline is:

1. `tools/ce-manifest.py` reads the official Learn table of contents and creates a page manifest.
2. `tools/ce-fetch.py` downloads the documented pages and extracts their Requirements information into `build/rows.json`.
3. `tools/gen-doc-def.py` generates `def/*-doc.def` from that record set.

The generated definitions are committed so the repository remains self-contained. After harvesting additional categories, regenerate them with `make defdoc`.

```sh
python3 tools/ce-fetch.py tools/manifests/core-synchronization-reference.manifest
make defdoc

llvm-dlltool -m armce -d def/coredll-doc.def -l coredll.lib
llvm-dlltool -m i386 --no-leading-underscore -d def/coredll-doc.def \
    -l coredll-x86.lib
```

## Layout

```text
startup/            Windows CE program-startup support
include/             application API headers
include/oak/         OAK/DDK driver/OEM headers
def/                 documentation-derived import definitions
tools/               documentation harvest and generation tools
docs/inventory.md    per-declaration official-source matrix
tests/host/          host compile checks
tests/e2e/            end-to-end link consumers
Makefile              build and verification entry points
```

## Build and check

```sh
make check
make crosscheck WINCECLANG=/path/to/LLVM-WinCE/clang
make crt WINCECLANG=/path/to/LLVM-WinCE/clang
make e2e WINCECLANG=/path/to/LLVM-WinCE/clang
```

`make check` verifies the headers for CE 4.2, 5.0 and 6.0. `make crosscheck` performs real-toolchain compile checks for the ARM and x86 CE targets. `make e2e` builds the documentation-derived import libraries, links the end-to-end consumers, and checks the resulting PE images.

The historical `crt` path is retained as a compatibility symlink to `startup`; new documentation and repository structure use `startup`.

## Status

The SDK is developed incrementally from the official CE documentation. Each batch records its declarations and source references in `docs/inventory.md`.
