#!/usr/bin/env python3
"""local-pages.py -- materialise build/pages/ from the official corpus.

Several generators in tools/ read the flattened text of a page through
`rtctext.page_text(pid)`, which resolves `build/pages/<page-id>.html`.
That directory is a build artifact (build/ is git-ignored) and used to be
filled by hand from the harvest; this tool rebuilds it from the official
corpus in wince-docs-corpus, so the generation runs are reproducible:

  python3 tools/local-pages.py <manifest> [<manifest> ...]

For every page id listed in the manifests it copies the first corpus file
that matches `<corpus>/<page-dir>/<id>.html`, in the same preference order
the harvest used (CE 5.0, CE 6.0, CE .NET 4.0, CE 3.0, then the remaining
trees).  Nothing is downloaded: the corpus is the archive of record.

Inputs are the manifests only (page ids); the corpus path can be
overridden with WINCE_CORPUS.
"""

import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.environ.get('WINCE_CORPUS', '/home/user/wince-docs-corpus')
OUT = os.path.join(ROOT, 'build', 'pages')

# the order the earlier harvests used when the same page id exists in more
# than one tree
TREES = ('pages5', 'pages6', 'pages4', 'pages3', 'coredll', 'pagesnet',
         'pagesw', 'pageswm', 'pagesmag', 'ce10', 'ce20', 'ce30', 'ce40',
         'ce50', 'ce60')


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    ids = []
    for m in sys.argv[1:]:
        mf = os.path.join(ROOT, 'tools', 'manifests', m + '.manifest')
        for line in open(mf, encoding='utf-8'):
            line = line.strip()
            if line:
                ids.append(line.split('\t')[0].split('(')[0])
    os.makedirs(OUT, exist_ok=True)
    found = missed = 0
    for pid in ids:
        dst = os.path.join(OUT, pid + '.html')
        if os.path.exists(dst):
            found += 1
            continue
        for tree in TREES:
            src = os.path.join(CORPUS, tree, pid + '.html')
            if os.path.exists(src):
                shutil.copyfile(src, dst)
                found += 1
                break
        else:
            missed += 1
            print(f'  not in the corpus: {pid}')
    print(f'build/pages: {found} pages ready, {missed} missing')


if __name__ == '__main__':
    main()
