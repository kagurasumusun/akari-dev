# Clean-room and Source Handling

## Boundary

Akari-dev must be independently authored.

Do not copy, transform, or incorporate third-party implementation source as Akari-dev source code. Do not reconstruct a Microsoft or vendor implementation merely because implementation details are available elsewhere.

## Facts vs source text

Individual interface facts—such as API names, type names, constants, prototypes, header names, DLL names, exports, documented ABI properties, and version/availability statements—are distinct from copying source text.

Use public specification facts as the basis for independent declarations and contracts. Do not derive Akari-dev source by mechanically editing or translating a third-party header or implementation.

## Microsoft restricted source areas

For Shared Source, Visual Studio, Platform Builder, and similar Microsoft source distributions:

- do not collect or use source code for copying/reimplementation;
- use accompanying public development documentation when appropriate;
- use permitted public metadata to establish API, header, ABI, version, and development requirements;
- do not inspect source with the goal of reproducing internal implementation behavior.

## Third-party material

Third-party documentation, personal technical articles, mailing-list archives, and reverse-engineering reports may be evidence when lawfully and legitimately obtained, publicly available or otherwise appropriately accessible, and not confidential or non-public material.

Their role is evidence or comparison. They are not permission to copy code.

## Provenance

For material implementation decisions, preserve enough provenance to answer:

- Which source established the fact?
- What generation/version did it describe?
- Was the fact direct, correlated, or inferred?
- What uncertainty remains?

Source text itself should not be imported merely to preserve provenance.
