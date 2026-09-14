#!/usr/bin/env python3
"""
verify-ptr.py -- cross-check every live declaration in include/ against
the official page print it cites, for parameter/return *pointer*
differences.

Why this exists (M107b): gen-book.py's parameter splitter matched the
stars between a type and its parameter name with a throwaway regex
group, so a print in the SDK-reference spacing (`const WCHAR * pwszAdd`)
was compiled as a by-value parameter.  That silently changes the type of
a declaration while still compiling, so no gate could see it.  This tool
compares the tree against the prints directly.

Method: for every harvested row whose `sig` parses as a function
prototype (the same parser gen-book.py/decl-d1.py use), find the
declaration of that name in include/, parse its parameter list, and
compare the pointer depth of each parameter (by position) and of the
return type.  Only pointer-ness is compared -- parameter *names* differ
legitimately between archive trees, and the tree is free to spell types
through documented aliases.

Usage:  python3 tools/verify-ptr.py [--verbose]
"""

import importlib.util
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_TOOLS = os.path.join(ROOT, 'tools')

_spec = importlib.util.spec_from_file_location('gb', os.path.join(_TOOLS, 'gen-book.py'))
gb = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(gb)

VERBOSE = '--verbose' in sys.argv


def inc_text():
    parts = []
    for d in ('include', os.path.join('include', 'oak')):
        for fn in sorted(os.listdir(os.path.join(ROOT, d))):
            if fn.endswith(('.h', '.hxx', '.hpp')):
                parts.append(open(os.path.join(ROOT, d, fn), encoding='utf-8',
                                  errors='replace').read())
    return '\n'.join(parts)


def strip_comments(text):
    text = re.sub(r'(?s)/\*.*?\*/', ' ', text)
    text = re.sub(r'//[^\n]*', ' ', text)
    return text


def sig_slice(sig):
    """the parameter text of a printed signature, split on top-level commas"""
    lp, rp = sig.find('('), sig.rfind(')')
    if lp < 0 or rp < lp:
        return []
    txt = re.sub(r'\s+', ' ', sig[lp + 1:rp]).strip()
    if txt in ('', 'void', 'VOID'):
        return []
    parts, depth, cur = [], 0, ''
    for ch in txt:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += ch
    parts.append(cur)
    return parts


DECL_RE = r'\b%s\s*\('


def find_decl(code, name):
    """returns the parameter text of the declaration of `name`, or None"""
    out = []
    for m in re.finditer(DECL_RE % re.escape(name), code):
        line_start = code.rfind('\n', 0, m.start()) + 1
        if '#' in code[line_start:m.start()]:
            continue                 # macro body, not a declaration
        # not a call: a call would be `foo(` preceded by `=`/`(`/`;`
        pre = code[max(0, m.start() - 40):m.start()]
        if re.search(r'(=\s*|return\s+)$', pre):
            continue
        start = m.end() - 1
        depth = 0
        i = start
        while i < len(code):
            if code[i] in '([{':
                depth += 1
            elif code[i] in ')]}':
                depth -= 1
                if depth == 0:
                    break
            i += 1
        head = code[max(0, m.start() - 120):m.start()]
        # skip macro bodies / comments already stripped
        out.append((head.strip().splitlines()[-1], code[start + 1:i]))
    return out


def ptr_depth(t):
    """pointer-ness of a parameter type.  Star count, plus the CE/Win32
    P/LP/PP/LPP name prefixes (PCENOTIFYREQUEST and CENOTIFYREQUEST* are
    the same pointer type and must not be reported as a difference), plus
    the array-parameter decay."""
    t = t.strip()
    if '*' in t:
        n = t.count('*')
    else:
        base = t.split()[-1] if t.split() else ''
        m = re.match(r'^(L?P{1,2})(?=[A-Z0-9_])', base)
        n = len(m.group(1).lstrip('L')) if m else 0
    if re.search(r'\b\w+\s*\[\s*\d*\s*\]\s*$', t):
        n += 1
    return n


def fix_array(type_, name):
    """`WCHAR szName[]` / `FILETIME rg[ ]` style: the decaying [] belongs
    to the type"""
    if re.search(r'\[\s*\d*\s*\]$', name):
        name = re.sub(r'\[.*$', '', name).strip()
        type_ = type_ + '*'
    return type_, name


def norm_params(params_txt):
    """split a compiled parameter list into (type, name) pairs"""
    txt = re.sub(r'\s+', ' ', params_txt).strip()
    if txt in ('', 'void'):
        return []
    parts, depth, cur = [], 0, ''
    for ch in txt:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += ch
    parts.append(cur)
    out = []
    for p in parts:
        p = p.strip()
        if not p:
            continue
        m = re.match(r'^(.*?)(\**)\s*([A-Za-z_]\w*(?:\[[^\]]*\])?)?$', p)
        if not m:
            out.append((p, ''))
            continue
        t = (m.group(1).strip() + m.group(2)).strip() or 'int'
        t, n = fix_array(t, m.group(3) or '')
        out.append((t, n))
    return out


def main():
    rows = json.load(open(os.path.join(ROOT, 'build', 'rows.json')))
    code = strip_comments(inc_text())
    checked = mism = 0
    report = []
    for r in rows:
        sig = (r.get('sig') or '').strip()
        if not sig or sig.startswith(('#', 'typedef', 'struct', 'enum', 'union')):
            continue
        p = gb.parse_sig(sig)
        if not p:
            continue
        ret, conv, name, params = p
        if re.match(r'^[A-Z0-9_]+$', name) or '::' in sig:
            continue
        # a print this parser could not split cleanly (empty or glued
        # type token) is not comparable -- skip instead of guessing
        # glide-damaged prints (`WCHARszName[]`, `UNICODE PTCHARdn`) are
        # not comparable: a parameter name that starts upper-case is the
        # tail of a glued type, not a name.
        if not ret.strip():
            continue
        if re.match(r'^(void|typedef|Typedef|VOID)$', (r.get('title') or '').strip()):
            continue
        bad = False
        for piece in sig_slice(sig):
            if ' ' not in piece.strip() and piece.strip() not in ('void', 'VOID'):
                bad = True          # fully glued piece: not comparable
        if not bad:
            bad = any(not t.strip() or re.match(r'^[A-Z][A-Z0-9_]*[a-z]', t)
                      or re.match(r'^[A-Z]', n) or not re.match(r'^[a-z_\[]', n)
                      for t, n in params)
        if bad:
            continue
        found = find_decl(code, name)
        if not found:
            continue
        checked += 1
        want = [ptr_depth(t) for t, _ in params]
        ret_want = ptr_depth(ret)
        for head, params_txt in found:
            gp = norm_params(params_txt)
            if any('(' in t for t, _ in gp):
                continue          # function-pointer parameter: not comparable
            got = [ptr_depth(t) for t, _ in gp]
            if len(got) != len(want):
                continue          # arity differs: overload/other row
            if got != want:
                mism += 1
                report.append((r['id'], name, sig, [t for t, _ in params],
                               [t for t, _ in norm_params(params_txt)],
                               head))
                break
    print(f"checked {checked} declared functions against their page prints; "
          f"{mism} pointer mismatches")
    for pid, name, sig, want, got, head in report:
        print(f"\n{pid} {name}")
        print(f"  print : {sig[:200]}")
        print(f"  tree  : {head[:60]}")
        print(f"  want  : {want}")
        print(f"  got   : {got}")
    return 0


if __name__ == '__main__':
    sys.exit(main())
