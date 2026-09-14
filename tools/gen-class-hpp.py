#!/usr/bin/env python3
"""gen-class-hpp.py -- emit the documented C++ class headers (.hpp) of the
Windows CE SDK from the pages' own prints (M107d).

The M107 census leaves one cluster of Header tokens the tree does not
carry: the C++ class headers.  Every page of that cluster prints its
member with the `static` storage class, because the documented surface is
a class of static methods, e.g.

    Buttonview.hpp   static void DrawPushable( HDC hdc, HBRUSH hbr,
                                               RECT* lprc, UINT state,
                                               UINT flags );
                     enum ButtonControlRectangleStyle_t { ... };
    Gdi.hpp          static WINGDIAPI BOOL WINAPI BitBlt_I( HDC hdc, ... );

This tool reads a manifest of (page id, title) rows, pulls each page's own
print, and writes one class header per documented Header token:

    class ButtonView_t {
    public:
        /* <page id> ButtonView_t::DrawPushable: print `static void ...` */
        static void DrawPushable(HDC hdc, HBRUSH hbr, RECT* lprc,
                                 UINT state, UINT flags);
    };

Only the SQL-of-record rules of the project apply: the print is the
ground truth, the verbatim print stays in the per-member comment, the SDK
decoration macros (WINGDIAPI / INGDIAPI / WINUSERAPI) are defined empty
with a note (the tree already treats them as empty -- include/Wingdi.h
line 25), and a member whose parameter or return type is NOT carried by
the tree is emitted as a record comment instead of a declaration (nothing
is invented).

Usage:
  python3 tools/gen-class-hpp.py <manifest> [<manifest> ...]
"""

import html
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))

import importlib

gb = importlib.import_module('gen-book')

# the SDK decoration macros these pages print; all empty on CE's 32-bit
# flat model (the tree's existing policy -- see include/Windef.h and
# include/Wingdi.h line 25)
DECOR = ('WINGDIAPI', 'INGDIAPI', 'WINUSERAPI', 'WINBASEAPI', 'WINUSERAPI',
         'STDAPI', 'STDAPICALLTYPE', 'WINAPIV')

DECOR_DEFS = '''/* %s: the CE pages print the class members with the SDK's decoration
 * macros.  No official page of the harvested corpus publishes their
 * expansion; this project's CE model has no decoration on the 32-bit
 * flat ABI (include/Windef.h WINAPI note, include/Wingdi.h), so they are
 * defined empty here -- only when the environment has not defined them --
 * so that the pages' prints compile verbatim. */
'''


def page_text(pid):
    """flattened text of a corpus page (reuses the gen-book cache)"""
    return gb.page_text(pid)


METHOD_RE = re.compile(
    r'\bstatic\s+(?:' + '|'.join(DECOR) + r')\s*'   # decoration macros
    r'([A-Za-z_][A-Za-z0-9_\s\*]*?)\s+'             # return type
    r'(?:WINAPI\s+|WINAPIV\s+|CALLBACK\s+)?'
    r'([A-Za-z_]\w*)\s*\(([^;]*?)\)\s*;')

# same, but with no decoration macro between `static` and the type
METHOD_NODECOR_RE = re.compile(
    r'\bstatic\s+([A-Za-z_][A-Za-z0-9_\s\*]*?)\s+'
    r'(?:WINAPI\s+|WINAPIV\s+|CALLBACK\s+)?'
    r'([A-Za-z_]\w*)\s*\(([^;]*?)\)\s*;')

ENUM_RE = re.compile(r'\benum\s+([A-Za-z_]\w*)\s*\{([^}]*)\}\s*;')


def find_print(pid, name):
    """the page's own print for `name`: (kind, ret, params, enumbody)"""
    t = page_text(pid)
    if not t:
        return None
    t = ' '.join(t.split())
    # enum page?
    m = ENUM_RE.search(t)
    if m and m.group(1) == name:
        return ('enum', None, None, m.group(2))
    for rx in (METHOD_RE, METHOD_NODECOR_RE):
        for m in rx.finditer(t):
            if m.group(2) != name:
                continue
            ret = re.sub(r'\s+', ' ', m.group(1)).strip()
            if not ret:
                continue
            return ('method', ret, m.group(3), None)
    return None


def conv_params(paramtext):
    """(list of ('type name'), note) -- None when a type is not carried"""
    if not paramtext.strip() or paramtext.strip().lower() in ('void', ''):
        return [], None
    out = []
    for piece in gb.split_top_commas(paramtext):
        piece = ' '.join(piece.split())
        piece = re.sub(r'\b(IN|OUT|IN_OUT|OPTIONAL|CONST)\b\s*', '', piece)
        p = gb.parse_piece(piece)
        if not p:
            return None, piece
        t, n = p
        t = gb.norm_type(t)
        base = gb.base_of(t)
        if not base:
            return None, piece
        if base not in gb.PRIMS and not gb.known_type(t):
            return None, piece
        out.append((t, n))
    return out, None


def emit_group(manifest, ids, rows):
    target = None
    members = {}          # class name -> list of (row, print tuple)
    order = []
    enums, records = [], []
    for pid in ids:
        r = rows.get(pid)
        if not r:
            continue
        title = re.sub(r'\s*\(Windows CE[^)]*\)\s*$', '', r['title']).strip()
        hdr = (r.get('header') or '').strip().rstrip('.')
        if hdr and not re.search(r'\.(hpp|hxx)$', hdr, re.I):
            continue
        if hdr:
            target = hdr if target is None else target
            m = re.match(r'^(.*)\.(hpp|hxx)$', hdr, re.I)
            target = m.group(1) + '.' + m.group(2).lower()
        if '::' not in title:
            # file-scope enumeration page
            pr = find_print(pid, title)
            if pr and pr[0] == 'enum':
                enums.append((pid, title, pr, r))
            else:
                records.append((pid, title, r))
            continue
        cls, name = title.split('::', 1)
        pr = find_print(pid, name)
        if not pr:
            records.append((pid, title, r))
            continue
        if cls not in members:
            members[cls] = []
            order.append(cls)
        members[cls].append((pid, title, name, pr, r))
    if target is None:
        print(f'[{manifest}] no .hpp Header token; skipped')
        return
    path = os.path.join(ROOT, 'include', target)
    guard = 'AKARI_' + re.sub(r'\W', '_', target).upper()
    L = []
    L.append('/*')
    L.append(f' * {target} -- Windows CE C++ class surface (Akari API).')
    L.append(' *')
    L.append(' * Copyright (c) 2026 Akari API contributors')
    L.append(' * SPDX-License-Identifier: MIT')
    L.append(' *')
    L.append(' * Written from scratch from the official Microsoft Windows CE')
    L.append(' * documentation (learn.microsoft.com previous-versions archive;')
    L.append(' * page ids cited per member).  Every member below is the page\'s own')
    L.append(' * print; the verbatim print is kept in the member\'s comment.')
    L.append(' * Generated by tools/gen-class-hpp.py.')
    L.append(' */')
    L.append('')
    L.append(f'#ifndef {guard}')
    L.append(f'#define {guard}')
    L.append('')
    L.append('#include <Windows.h>')
    L.append('')
    L.append('#ifdef __cplusplus')
    L.append('#ifndef _INC_WINDOWS_CE_SDK_DECOR_EMPTY')
    L.append('#define _INC_WINDOWS_CE_SDK_DECOR_EMPTY  1')
    for d in ('WINGDIAPI', 'INGDIAPI', 'WINUSERAPI'):
        L.append(f'#ifndef {d}')
        L.append(f'#define {d}')
        L.append('#endif')
    L.append('#endif')
    L.append('')
    for e in enums:
        pid, name, pr, r = e
        body = ' '.join(pr[3].split())
        L.append(f'/* {pid} {name} (page print, compiled):')
        L.append(f' *   enum {name} {{ {body} }}; */')
        L.append(f'enum {name} {{')
        members_out = [m.strip() for m in body.split(',') if m.strip()]
        for i, m in enumerate(members_out):
            L.append('    ' + m + (',' if i < len(members_out) - 1 else ''))
        L.append('};')
        L.append('')
    for cls in order:
        L.append(f'class {cls} {{')
        L.append('public:')
        for pid, title, name, pr, r in members[cls]:
            kind, ret, params, _ = pr
            conv, bad = conv_params(params)
            verbatim = f'static {ret} {name}({params.strip()});'
            if conv is None:
                L.append(f'    /* {pid} {title}: print `{verbatim}`')
                L.append(f'     *   -- HELD: parameter type `{bad}` has no defining')
                L.append('     *   page in the harvested official corpus */')
                continue
            arglist = ', '.join((f'{t} {n}'.strip()) for t, n in conv)
            L.append(f'    /* {pid} {title}: print `{verbatim}` */')
            L.append(f'    static {ret} {name}({arglist});')
        L.append('};')
        L.append('')
    for pid, title, r in records:
        L.append(f'/* {pid} {title} (Header: {r.get("header")}): no class-member')
        L.append(' * print on the page (record only) */')
    L.append('#endif /* __cplusplus */')
    L.append('')
    L.append(f'#endif /* {guard} */')
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write('\n'.join(L) + '\n')
    nd = sum(len(members[c]) for c in members)
    print(f'{target}: NEW, {len(L)} lines '
          f'({len(members)} class(es), {nd} members, {len(enums)} enums, '
          f'{len(records)} records)')


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    gb.load_registry()
    rows = {}
    for f in gb.ROW_FILES:
        for r in json.load(open(f)):
            rows[r['id'].split('(')[0]] = r
    for manifest in sys.argv[1:]:
        mf = os.path.join(ROOT, 'tools', 'manifests', manifest + '.manifest')
        ids = []
        for line in open(mf, encoding='utf-8'):
            line = line.strip()
            if line:
                ids.append(line.split('\t')[0].split('(')[0])
        emit_group(manifest, ids, rows)


if __name__ == '__main__':
    main()
