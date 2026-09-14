#!/usr/bin/env python3
"""
cf-crawl-vs90.py -- expand the .NET Compact Framework API surface over the
official `previous-versions/dotnet/netframework-3.5/<id>(v=vs.90)` pages
(M102b, part 2), link-driven and resumable.

Why link-driven (measured, M102b):
  * the harvested `toc.json` leaves of that tree now point at the modern API
    browser (`/dotnet/api/...?redirectedfrom=msdn`); fetched verbatim, those
    pages carry **no** `.NET Compact Framework` Version Information row at
    all (two samples checked: system.string, system.windows.ink.
    applicationgesture -- 0 occurrences of "Compact Framework"), while the
    `(v=vs.90)` pages do.  So the toc.json catalog cannot be used as the
    harvest seed for the desktop subset.
  * the `(v=vs.90)` pages themselves link to their relatives (base classes,
    member lists, argument types) with the same `(v=vs.90)` anchor, e.g.
    `4xzkbd1z(v=vs.90)` -- that link graph is the archive's own navigation,
    so a BFS over it reaches exactly the pages the CF reference itself
    points at.

The crawler never invents a page id: every id comes from a link found in a
page that was itself harvested from the official tree (seeded from the
CF-specific pages already in the corpus `pagesnet/`).

Evidence policy (unchanged): a page is recorded as part of the CE surface
only when it carries the `.NET Compact Framework` "Supported in:" row or the
CF-only `Platforms` list; pages without it are recorded as
`cf_supported = -` (desktop-only / not confirmable in the CF docs), never
by analogy.

Usage:
  python3 tools/cf-crawl-vs90.py [--batch N] [--out docs/cf-surface-vs90.tsv]

State: build/cf-crawl-queue.txt (pending ids) and build/cf-crawl-seen.txt
(every id touched), so the crawl resumes exactly where it stopped.
"""

import html
import os
import re
import sys
import time
import urllib.error
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.environ.get('WINCE_CORPUS', '/home/user/wince-docs-corpus')
PAGES = os.path.join(CORPUS, 'pagesnet')
BUILD = os.path.join(ROOT, 'build')
QUEUE = os.path.join(BUILD, 'cf-crawl-queue.txt')
SEEN = os.path.join(BUILD, 'cf-crawl-seen.txt')
GONE = os.path.join(BUILD, 'cf-crawl-gone.txt')
BASE = ('https://learn.microsoft.com/en-us/previous-versions/dotnet/'
        'netframework-3.5/{}(v=vs.90)')
UA = ('Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 '
      '(KHTML, like Gecko) Chrome/120 Safari/537.36')

LINK_RE = re.compile(r'([0-9a-z]{8})\(v=vs\.90\)')


def load(path):
    if not os.path.exists(path):
        return []
    return [l.strip() for l in open(path, encoding='utf-8') if l.strip()]


def save(path, items):
    with open(path, 'w', encoding='utf-8') as fh:
        for it in items:
            fh.write(it + '\n')


def flatten(raw):
    flat = re.sub(r'<script.*?</script>', ' ', raw, flags=re.S)
    flat = re.sub(r'<style.*?</style>', ' ', flat, flags=re.S)
    flat = html.unescape(re.sub(r'<[^>]+>', ' ', flat))
    return re.sub(r'\s+', ' ', flat)


def fetch(root):
    path = os.path.join(PAGES, root + '.html')
    if os.path.exists(path) and os.path.getsize(path) > 2000:
        return open(path, encoding='utf-8', errors='replace').read()
    url = BASE.format(root)
    req = urllib.request.Request(url, headers={'User-Agent': UA})
    data = None
    for attempt in range(3):
        try:
            with urllib.request.urlopen(req, timeout=45) as resp:
                data = resp.read().decode('utf-8', 'replace')
            break
        except urllib.error.HTTPError as exc:
            if exc.code == 404:
                # the archive retired this page: record it and move on
                # (no sleep -- the id is a link target of a harvested
                # page, so the finding belongs in the report)
                with open(GONE, 'a', encoding='utf-8') as fh:
                    fh.write(root + '\n')
                return None
            if attempt == 2:
                return None
            time.sleep(2 * (attempt + 1))
        except Exception:
            if attempt == 2:
                return None
            time.sleep(2 * (attempt + 1))
    os.makedirs(PAGES, exist_ok=True)
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write(data)
    time.sleep(0.12)
    return data


def parse(raw, rid):
    flat = flatten(raw)
    m = re.search(r'<title>(.*?)</title>', raw, re.S)
    title = html.unescape(m.group(1)).strip() if m else ''
    title = re.sub(r'\s*\|\s*Microsoft Learn\s*$', '', title)
    ns = (re.search(r'Namespace:\s*([A-Za-z_][\w.]*)', flat) or [None, ''])[1]
    asm = (re.search(r'Assembly:\s*([A-Za-z0-9_.]+)', flat) or [None, ''])[1]
    m = re.search(r'Platforms\s+(.*?)(?:Version Information|See Also|'
                  r'\.NET Framework Security|$)', flat)
    platforms = ' '.join(m.group(1).split()) if m else ''
    cf = ''
    m = re.search(r'\.NET Compact Framework\s+Supported in:\s*'
                  r'([0-9]+\.[0-9]+(?:\s*,\s*[0-9]+\.[0-9]+)*)', flat)
    if m:
        cf = re.sub(r'\s+', '', m.group(1))
    kind = ''
    m = re.search(r'\b(Namespace|Class|Structure|Interface|Delegate|'
                  r'Enumeration|Method|Property|Field|Event|Constructor|'
                  r'Operator|Members)\s*$', title)
    if m:
        kind = m.group(1)
    return {
        'id': rid, 'title': title, 'namespace': ns, 'assembly': asm,
        'platforms': platforms[:160], 'cf': cf or '-', 'kind': kind,
    }


def main():
    batch = 300
    out = os.path.join(ROOT, 'docs', 'cf-surface-vs90.tsv')
    for i, a in enumerate(sys.argv[1:]):
        if a == '--batch':
            batch = int(sys.argv[i + 2])
        elif a == '--out':
            out = sys.argv[i + 2]
    os.makedirs(BUILD, exist_ok=True)

    seen = set(load(SEEN))
    queue = load(QUEUE)
    if not queue and not seen:
        # seed from the link graph of the harvested CF-specific pages
        queue = []
        for fn in sorted(os.listdir(PAGES)):
            raw = open(os.path.join(PAGES, fn), encoding='utf-8',
                       errors='replace').read()
            for rid in LINK_RE.findall(raw):
                if rid != fn[:-5]:
                    queue.append(rid)
        queue = sorted(set(queue))
        print(f'seeded {len(queue)} ids from the corpus link graph')
    queue = [q for q in queue if q not in seen]

    new_rows = []
    for n, rid in enumerate(queue[:batch]):
        raw = fetch(rid)
        seen.add(rid)
        if raw is None:
            print(f'  {rid}: fetch failed (recorded as seen)')
            continue
        row = parse(raw, rid)
        new_rows.append(row)
        print(f"  [{n + 1}/{min(batch, len(queue))}] {rid} {row['title'][:44]:46s}"
              f" cf={row['cf']:12s} ns={row['namespace'][:28]}")
    save(QUEUE, [q for q in queue if q not in seen])
    save(SEEN, sorted(seen))

    header = ('id\ttitle\tkind\tnamespace\tassembly\tplatforms\tcf_supported\n')
    exists = os.path.exists(out)
    with open(out, 'a', encoding='utf-8') as fh:
        if not exists:
            fh.write(header)
        for r in new_rows:
            fh.write('\t'.join([r['id'], r['title'], r['kind'],
                                r['namespace'], r['assembly'],
                                r['platforms'], r['cf']]) + '\n')
    with_cf = sum(1 for r in new_rows if r['cf'] != '-')
    gone = len(load(GONE))
    print(f'{len(new_rows)} pages fetched, {with_cf} carry a CF row, '
          f'{gone} link targets retired (404); queue left: '
          f'{len(load(QUEUE))}, seen: {len(seen)}')


if __name__ == '__main__':
    main()
