/*
 * Winver.h -- version-information resource structures (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Fix note (audit 2026-09-14): this content was previously emitted by
 * tools/gen-book.py under the literal (invalid) filename
 * "Not applicable.h" because the source page's Header row read
 * "Not applicable" -- that row describes the *binary resource*
 * layout, which every Win32/CE reference places under Winver.h, not
 * a literal file named after the row text. The generator must treat
 * "Not applicable" / "None" / "Developer-defined" Header-row values
 * as "no header to alias" rather than as a filename to create.
 *
 * VS_VERSIONINFO/VS_FIXEDFILEINFO are the standard version-resource
 * structures used identically across desktop Win32 and Windows CE;
 * StringFileInfo/StringTable/VarFileInfo/Var remain variable-length
 * binary blocks with no fixed C struct (the reason the original
 * record was HELD) and are described here only as layout comments,
 * matching how desktop winver.h documents them.
 */

#ifndef AKARI_WINVER_H
#define AKARI_WINVER_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagVS_FIXEDFILEINFO {
    DWORD dwSignature;        /* 0xFEEF04BD */
    DWORD dwStrucVersion;
    DWORD dwFileVersionMS;
    DWORD dwFileVersionLS;
    DWORD dwProductVersionMS;
    DWORD dwProductVersionLS;
    DWORD dwFileFlagsMask;
    DWORD dwFileFlags;
    DWORD dwFileOS;
    DWORD dwFileType;
    DWORD dwFileSubtype;
    DWORD dwFileDateMS;
    DWORD dwFileDateLS;
} VS_FIXEDFILEINFO;

/* dwSignature */
#define VS_FFI_SIGNATURE        0xFEEF04BDL
#define VS_FFI_STRUCVERSION     0x00010000L
#define VS_FFI_FILEFLAGSMASK    0x0000003FL

/* dwFileFlags / dwFileFlagsMask bits */
#define VS_FF_DEBUG             0x00000001L
#define VS_FF_PRERELEASE        0x00000002L
#define VS_FF_PATCHED           0x00000004L
#define VS_FF_PRIVATEBUILD      0x00000008L
#define VS_FF_INFOINFERRED      0x00000010L
#define VS_FF_SPECIALBUILD      0x00000020L

/* dwFileOS */
#define VOS_UNKNOWN             0x00000000L
#define VOS__WINDOWS32          0x00000004L
#define VOS_NT                  0x00000010L
#define VOS_NT_WINDOWS32        0x00000014L

/* dwFileType */
#define VFT_UNKNOWN             0x00000000L
#define VFT_APP                 0x00000001L
#define VFT_DLL                 0x00000002L
#define VFT_DRV                 0x00000003L
#define VFT_FONT                0x00000004L
#define VFT_VXD                 0x00000005L
#define VFT_STATIC_LIB          0x00000007L

/* dwFileSubtype, when dwFileType == VFT_DRV */
#define VFT2_UNKNOWN            0x00000000L
#define VFT2_DRV_COMM           0x0000000AL
#define VFT2_DRV_KEYBOARD       0x00000002L
#define VFT2_DRV_LANGUAGE       0x00000003L
#define VFT2_DRV_DISPLAY        0x00000004L
#define VFT2_DRV_MOUSE          0x00000005L
#define VFT2_DRV_NETWORK        0x00000006L
#define VFT2_DRV_SYSTEM         0x00000007L
#define VFT2_DRV_INSTALLABLE    0x00000008L
#define VFT2_DRV_SOUND          0x00000009L
#define VFT2_DRV_VERSIONED_PRINTER 0x0000000CL

/*
 * The VS_VERSION_INFO resource is a variable-length binary block, not
 * a fixed C struct: after the fixed wLength/wValueLength/wType/szKey
 * header (szKey == L"VS_VERSION_INFO") and the padded
 * VS_FIXEDFILEINFO, it holds zero or more variable-length child
 * blocks (StringFileInfo, VarFileInfo), each themselves holding
 * further variable-length children (StringTable/String, Var). These
 * are produced by the resource compiler from a VERSIONINFO .rc block
 * and consumed with VerQueryValue(); Akari does not model their
 * binary layout as a C struct, matching desktop <winver.h>. See
 * docs/inventory.md M73b for the source pages (ms647001 and
 * children) and the HELD rationale.
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINVER_H */
