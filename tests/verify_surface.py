#!/usr/bin/env python3
"""Verify the initial generated surface, including a C declaration compile."""
import json
import pathlib
import subprocess
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[1]
subprocess.run(["python3", "tools/generate_surface.py", "--check"], cwd=ROOT, check=True)
link = json.loads((ROOT / "generated/link/gettickcount.link.json").read_text(encoding="utf-8"))
assert link["link_library"] == "Coredll.lib"
assert link["dll_module"] is None and link["export_name"] is None and link["ordinal"] is None
assert "calling convention" in link["unknowns"]
source = """#include <winbase.h>
_Static_assert(sizeof(DWORD) == 4, \"DWORD must be 32 bits\");
static DWORD (*const get_tick_count)(void) = GetTickCount;
int main(void) { return get_tick_count == 0; }
"""
with tempfile.TemporaryDirectory() as tmp:
    path = pathlib.Path(tmp) / "surface.c"
    path.write_text(source, encoding="utf-8")
    subprocess.run([
        "clang", "-std=c11", "-fsyntax-only", "-I", str(ROOT / "generated/include"), str(path)
    ], check=True)
print("[verify-surface] generated header, ABI width, and linker-gap metadata verified")
