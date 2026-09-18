/*
 * D3dmtypes.h -- documented include-name alias for d3dm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: D3dmtypes.h" (65 pages);
 * D3dmtypes.h types/enums/structures are carried in d3dm.h (M67).  This project carries the declarations in d3dm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <D3dmtypes.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide D3dmtypes.h with d3dm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "D3dm.h"/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms939139 D3DMCLEAR Values (Header: D3dmtypes.h.) */
/* ms939144 D3DMCOLORWRITEENABLE Values (Header: D3dmtypes.h.) */
/* ms928308 D3DMCS Values (Header: D3dmtypes.h.) */
/* ms907708 D3DMFVF Values (Header: D3dmtypes.h.) */
/* ms907711 D3DMFVF_TEXCOORDSIZE Macros (Header: D3dmtypes.h.) */
/* ms907717 D3DMLOCK Values (Header: D3dmtypes.h.) */
/* ms907736 D3DMPV Values (Header: D3dmtypes.h.) */
/* ms907746 D3DMTA Values (Header: D3dmtypes.h.) */
/* ms907754 D3DMTSS_TCI Values (Header: D3dmtypes.h.) */
/* ms907755 D3DMUSAGE Values (Header: D3dmtypes.h.) */
/* ms907761 D3DMWRAPCOORD Values (Header: D3dmtypes.h.) */
/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907727 D3DMPRESENTFLAG_LOCKABLE_BACKBUFFER: value adopted at the M99 three-generation sweep -- ms907727: the Remarks of the D3DMPRESENTFLAG page print the value (CE 6.0 twin ee490892 prints the same 0x00000001). */
#if _WIN32_WCE >= 0x0500   /* Windows CE 5.0 and later. (ms907727) */
#define D3DMPRESENTFLAG_LOCKABLE_BACKBUFFER 0x00000001/* ee490892 */
#endif /* _WIN32_WCE >= 0x0500 */
/* ms939139 D3DMCLEAR Values (Header: D3dmtypes.h.) */
/* ms939144 D3DMCOLORWRITEENABLE Values (Header: D3dmtypes.h.) */
/* ms928308 D3DMCS Values (Header: D3dmtypes.h.) */
/* ms907708 D3DMFVF Values (Header: D3dmtypes.h.) */
/* ms907711 D3DMFVF_TEXCOORDSIZE Macros (Header: D3dmtypes.h.) */
/* ms907717 D3DMLOCK Values (Header: D3dmtypes.h.) */
/* ms907736 D3DMPV Values (Header: D3dmtypes.h.) */
/* ms907746 D3DMTA Values (Header: D3dmtypes.h.) */
/* ms907754 D3DMTSS_TCI Values (Header: D3dmtypes.h.) */
/* ms907755 D3DMUSAGE Values (Header: D3dmtypes.h.) */
/* ms907761 D3DMWRAPCOORD Values (Header: D3dmtypes.h.) */
/* ms939133 D3DMADAPTER_IDENTIFIER: structure print on the page; derived at
 * the M99 sweep.  Declared here because the page prints
 * "Header: D3dmtypes.h." (Windows CE 5.0 and later); it previously sat in
 * D3dmddk.h, so <D3dmtypes.h> did not provide it (M130). */
#if _WIN32_WCE >= 0x0500   /* ms939133: Windows CE 5.0 and later (M130) */
typedef struct _D3DMADAPTER_IDENTIFIER D3DMADAPTER_IDENTIFIER;
struct _D3DMADAPTER_IDENTIFIER{
    TCHAR Driver[MAX_DEVICE_IDENTIFIER_STRING];
    TCHAR Description[MAX_DEVICE_IDENTIFIER_STRING];
    LARGE_INTEGER DriverVersion;
    ULONG VendorId;
    ULONG DeviceId;
    ULONG SubSysId;
    ULONG Revision;
    GUID DeviceIdentifier;
};

/* ms885251 "D3DCULL" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DCULL {
    D3DCULL_NONE = 1,
    D3DCULL_CW = 2,
    D3DCULL_CCW = 3,
    D3DCULL_FORCE_DWORD = 0x7fffffff
} D3DCULL;

/* ms885264 "D3DDEBUGMONITORTOKENS" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DDEBUGMONITORTOKENS {
    D3DDMT_ENABLE = 0,
    D3DDMT_DISABLE = 1,
    D3DDMT_FORCE_DWORD = 0x7fffffff
} D3DDEBUGMONITORTOKENS;

/* ms885282 "D3DDEVTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DDEVTYPE {
    D3DDEVTYPE_HAL = 1,
    D3DDEVTYPE_REF = 2,
    D3DDEVTYPE_SW = 3,
    D3DDEVTYPE_FORCE_DWORD = 0xffffffff
} D3DDEVTYPE;

/* ms886214 "D3DFILLMODE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DFILLMODE {
    D3DFILL_POINT = 1,
    D3DFILL_WIREFRAME = 2,
    D3DFILL_SOLID = 3,
    D3DFILL_FORCE_DWORD = 0x7fffffff
} D3DFILLMODE;

/* ms886225 "D3DFOGMODE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DFOGMODE {
    D3DFOG_NONE = 0,
    D3DFOG_EXP = 1,
    D3DFOG_EXP2 = 2,
    D3DFOG_LINEAR = 3,
    D3DFOG_FORCE_DWORD = 0x7fffffff
} D3DFOGMODE;

/* ms886236 "D3DFORMAT" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DFORMAT {
    D3DFMT_UNKNOWN = 0,
    D3DFMT_R8G8B8 = 20,
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_R5G6B5 = 23,
    D3DFMT_X1R5G5B5 = 24,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_A4R4G4B4 = 26,
    D3DFMT_R3G3B2 = 27,
    D3DFMT_A8 = 28,
    D3DFMT_A8R3G3B2 = 29,
    D3DFMT_X4R4G4B4 = 30,
    D3DFMT_A8P8 = 40,
    D3DFMT_P8 = 41,
    D3DFMT_L8 = 50,
    D3DFMT_A8L8 = 51,
    D3DFMT_A4L4 = 52,
    D3DFMT_V8U8 = 60,
    D3DFMT_L6V5U5 = 61,
    D3DFMT_X8L8V8U8 = 62,
    D3DFMT_Q8W8V8U8 = 63,
    D3DFMT_V16U16 = 64,
    D3DFMT_W11V11U10 = 65,
#ifdef MAKEFOURCC
    /* The page print references MAKEFOURCC; no corpus page
     * documents that macro definition, so the FOURCC pixel
     * formats stay guarded until the definition is
     * documented or supplied by the toolchain. */
    D3DFMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    D3DFMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
    D3DFMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
    D3DFMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
    D3DFMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
    D3DFMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
    D3DFMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),
#endif
    D3DFMT_D16_LOCKABLE = 70,
    D3DFMT_D32 = 71,
    D3DFMT_D15S1 = 73,
    D3DFMT_D24S8 = 75,
    D3DFMT_D16 = 80,
    D3DFMT_D24X8 = 77,
    D3DFMT_D24X4S4 = 79,
    D3DFMT_VERTEXDATA = 100,
    D3DFMT_INDEX16 = 101,
    D3DFMT_INDEX32 = 102,
    D3DFMT_FORCE_DWORD = 0xFFFFFFFF
} D3DFORMAT;

/* ms886266 "D3DLIGHTTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DLIGHTTYPE {
    D3DLIGHT_POINT = 1,
    D3DLIGHT_SPOT = 2,
    D3DLIGHT_DIRECTIONAL = 3,
    D3DLIGHT_FORCE_DWORD = 0x7fffffff
} D3DLIGHTTYPE;

/* ms886291 "D3DMATERIALCOLORSOURCE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DMATERIALCOLORSOURCE {
    D3DMCS_MATERIAL = 0,
    D3DMCS_COLOR1 = 1,
    D3DMCS_COLOR2 = 2,
    D3DMCS_FORCE_DWORD = 0x7fffffff
} D3DMATERIALCOLORSOURCE;

/* ms886302 "D3DMULTISAMPLE_TYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DMULTISAMPLE_TYPE {
    D3DMULTISAMPLE_NONE = 0,
    D3DMULTISAMPLE_2_SAMPLES = 2,
    D3DMULTISAMPLE_3_SAMPLES = 3,
    D3DMULTISAMPLE_4_SAMPLES = 4,
    D3DMULTISAMPLE_5_SAMPLES = 5,
    D3DMULTISAMPLE_6_SAMPLES = 6,
    D3DMULTISAMPLE_7_SAMPLES = 7,
    D3DMULTISAMPLE_8_SAMPLES = 8,
    D3DMULTISAMPLE_9_SAMPLES = 9,
    D3DMULTISAMPLE_10_SAMPLES = 10,
    D3DMULTISAMPLE_11_SAMPLES = 11,
    D3DMULTISAMPLE_12_SAMPLES = 12,
    D3DMULTISAMPLE_13_SAMPLES = 13,
    D3DMULTISAMPLE_14_SAMPLES = 14,
    D3DMULTISAMPLE_15_SAMPLES = 15,
    D3DMULTISAMPLE_16_SAMPLES = 16,
    D3DMULTISAMPLE_FORCE_DWORD = 0xffffffff
} D3DMULTISAMPLE_TYPE;

/* ms886305 "D3DORDERTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DORDERTYPE {
    D3DORDER_LINEAR = 1,
    D3DORDER_CUBIC = 3,
    D3DORDER_QUINTIC = 5,
    D3DORDER_FORCE_DWORD = 0x7fffffff
} D3DORDERTYPE;

/* ms886313 "D3DPOOL" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DPOOL {
    D3DPOOL_DEFAULT = 0,
    D3DPOOL_MANAGED = 1,
    D3DPOOL_SYSTEMMEM = 2,
    D3DPOOL_FORCE_DWORD = 0x7fffffff
} D3DPOOL;

/* ms886323 "D3DPRIMITIVETYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DPRIMITIVETYPE {
    D3DPT_POINTLIST = 1,
    D3DPT_LINELIST = 2,
    D3DPT_LINESTRIP = 3,
    D3DPT_TRIANGLELIST = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN = 6,
    D3DPT_FORCE_DWORD = 0x7fffffff
} D3DPRIMITIVETYPE;

/* ms886344 "D3DRENDERSTATETYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DRENDERSTATETYPE {
    D3DRS_ZENABLE = 7,
    D3DRS_FILLMODE = 8,
    D3DRS_SHADEMODE = 9,
    D3DRS_LINEPATTERN = 10,
    D3DRS_ZWRITEENABLE = 14,
    D3DRS_ALPHATESTENABLE = 15,
    D3DRS_LASTPIXEL = 16,
    D3DRS_SRCBLEND = 19,
    D3DRS_DESTBLEND = 20,
    D3DRS_CULLMODE = 22,
    D3DRS_ZFUNC = 23,
    D3DRS_ALPHAREF = 24,
    D3DRS_ALPHAFUNC = 25,
    D3DRS_DITHERENABLE = 26,
    D3DRS_ALPHABLENDENABLE = 27,
    D3DRS_FOGENABLE = 28,
    D3DRS_SPECULARENABLE = 29,
    D3DRS_ZVISIBLE = 30,
    D3DRS_FOGCOLOR = 34,
    D3DRS_FOGTABLEMODE = 35,
    D3DRS_FOGSTART = 36,
    D3DRS_FOGEND = 37,
    D3DRS_FOGDENSITY = 38,
    D3DRS_EDGEANTIALIAS = 40,
    D3DRS_ZBIAS = 47,
    D3DRS_RANGEFOGENABLE = 48,
    D3DRS_STENCILENABLE = 52,
    D3DRS_STENCILFAIL = 53,
    D3DRS_STENCILZFAIL = 54,
    D3DRS_STENCILPASS = 55,
    D3DRS_STENCILFUNC = 56,
    D3DRS_STENCILREF = 57,
    D3DRS_STENCILMASK = 58,
    D3DRS_STENCILWRITEMASK = 59,
    D3DRS_TEXTUREFACTOR = 60,
    D3DRS_WRAP0 = 128,
    D3DRS_WRAP1 = 129,
    D3DRS_WRAP2 = 130,
    D3DRS_WRAP3 = 131,
    D3DRS_WRAP4 = 132,
    D3DRS_WRAP5 = 133,
    D3DRS_WRAP6 = 134,
    D3DRS_WRAP7 = 135,
    D3DRS_CLIPPING = 136,
    D3DRS_LIGHTING = 137,
    D3DRS_AMBIENT = 139,
    D3DRS_FOGVERTEXMODE = 140,
    D3DRS_COLORVERTEX = 141,
    D3DRS_LOCALVIEWER = 142,
    D3DRS_NORMALIZENORMALS = 143,
    D3DRS_DIFFUSEMATERIALSOURCE = 145,
    D3DRS_SPECULARMATERIALSOURCE = 146,
    D3DRS_AMBIENTMATERIALSOURCE = 147,
    D3DRS_EMISSIVEMATERIALSOURCE = 148,
    D3DRS_VERTEXBLEND = 151,
    D3DRS_CLIPPLANEENABLE = 152,
    D3DRS_SOFTWAREVERTEXPROCESSING = 153,
    D3DRS_POINTSIZE = 154,
    D3DRS_POINTSIZE_MIN = 155,
    D3DRS_POINTSPRITEENABLE = 156,
    D3DRS_POINTSCALEENABLE = 157,
    D3DRS_POINTSCALE_A = 158,
    D3DRS_POINTSCALE_B = 159,
    D3DRS_POINTSCALE_C = 160,
    D3DRS_MULTISAMPLEANTIALIAS = 161,
    D3DRS_MULTISAMPLEMASK = 162,
    D3DRS_PATCHEDGESTYLE = 163,
    D3DRS_PATCHSEGMENTS = 164,
    D3DRS_DEBUGMONITORTOKEN = 165,
    D3DRS_POINTSIZE_MAX = 166,
    D3DRS_INDEXEDVERTEXBLENDENABLE = 167,
    D3DRS_COLORWRITEENABLE = 168,
    D3DRS_TWEENFACTOR = 170,
    D3DRS_BLENDOP = 171,
    D3DRS_FORCE_DWORD = 0x7fffffff
} D3DRENDERSTATETYPE;

/* ms886347 "D3DRESOURCETYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DRESOURCETYPE {
    D3DRTYPE_SURFACE = 1,
    D3DRTYPE_VOLUME = 2,
    D3DRTYPE_TEXTURE = 3,
    D3DRTYPE_VOLUMETEXTURE = 4,
    D3DRTYPE_CUBETEXTURE = 5,
    D3DRTYPE_VERTEXBUFFER = 6,
    D3DRTYPE_INDEXBUFFER = 7,
    D3DRTYPE_FORCE_DWORD = 0x7fffffff
} D3DRESOURCETYPE;

/* ms886350 "D3DSHADEMODE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DSHADEMODE {
    D3DSHADE_FLAT = 1,
    D3DSHADE_GOURAUD = 2,
    D3DSHADE_PHONG = 3,
    D3DSHADE_FORCE_DWORD = 0x7fffffff
} D3DSHADEMODE;

/* ms886355 "D3DSTATEBLOCKTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DSTATEBLOCKTYPE {
    D3DSBT_ALL = 1,
    D3DSBT_PIXELSTATE = 2,
    D3DSBT_VERTEXSTATE = 3,
    D3DSBT_FORCE_DWORD = 0xffffffff
} D3DSTATEBLOCKTYPE;

/* ms886364 "D3DSWAPEFFECT" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DSWAPEFFECT {
    D3DSWAPEFFECT_DISCARD = 1,
    D3DSWAPEFFECT_FLIP = 2,
    D3DSWAPEFFECT_COPY = 3,
    D3DSWAPEFFECT_COPY_VSYNC = 4,
    D3DSWAPEFFECT_FORCE_DWORD = 0xFFFFFFFF
} D3DSWAPEFFECT;

/* ms886457 "D3DTEXTUREADDRESS" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTEXTUREADDRESS {
    D3DTADDRESS_WRAP = 1,
    D3DTADDRESS_MIRROR = 2,
    D3DTADDRESS_CLAMP = 3,
    D3DTADDRESS_BORDER = 4,
    D3DTADDRESS_MIRRORONCE = 5,
    D3DTADDRESS_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREADDRESS;

/* ms886483 "D3DTEXTUREFILTERTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTEXTUREFILTERTYPE {
    D3DTEXF_NONE = 0,
    D3DTEXF_POINT = 1,
    D3DTEXF_LINEAR = 2,
    D3DTEXF_ANISOTROPIC = 3,
    D3DTEXF_FLATCUBIC = 4,
    D3DTEXF_GAUSSIANCUBIC = 5,
    D3DTEXF_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREFILTERTYPE;

/* ms886501 "D3DTEXTUREOP" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTEXTUREOP {
    D3DTOP_DISABLE = 1,
    D3DTOP_SELECTARG1 = 2,
    D3DTOP_SELECTARG2 = 3,
    D3DTOP_MODULATE = 4,
    D3DTOP_MODULATE2X = 5,
    D3DTOP_MODULATE4X = 6,
    D3DTOP_ADD = 7,
    D3DTOP_ADDSIGNED = 8,
    D3DTOP_ADDSIGNED2X = 9,
    D3DTOP_SUBTRACT = 10,
    D3DTOP_ADDSMOOTH = 11,
    D3DTOP_BLENDDIFFUSEALPHA = 12,
    D3DTOP_BLENDTEXTUREALPHA = 13,
    D3DTOP_BLENDFACTORALPHA = 14,
    D3DTOP_BLENDTEXTUREALPHAPM = 15,
    D3DTOP_BLENDCURRENTALPHA = 16,
    D3DTOP_PREMODULATE = 17,
    D3DTOP_MODULATEALPHA_ADDCOLOR = 18,
    D3DTOP_MODULATECOLOR_ADDALPHA = 19,
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,
    D3DTOP_BUMPENVMAP = 22,
    D3DTOP_BUMPENVMAPLUMINANCE = 23,
    D3DTOP_DOTPRODUCT3 = 24,
    D3DTOP_MULTIPLYADD = 25,
    D3DTOP_LERP = 26,
    D3DTOP_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREOP;

/* ms886612 "D3DTEXTURESTAGESTATETYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTEXTURESTAGESTATETYPE {
    D3DTSS_COLOROP = 1,
    D3DTSS_COLORARG1 = 2,
    D3DTSS_COLORARG2 = 3,
    D3DTSS_ALPHAOP = 4,
    D3DTSS_ALPHAARG1 = 5,
    D3DTSS_ALPHAARG2 = 6,
    D3DTSS_BUMPENVMAT00 = 7,
    D3DTSS_BUMPENVMAT01 = 8,
    D3DTSS_BUMPENVMAT10 = 9,
    D3DTSS_BUMPENVMAT11 = 10,
    D3DTSS_TEXCOORDINDEX = 11,
    D3DTSS_ADDRESSU = 13,
    D3DTSS_ADDRESSV = 14,
    D3DTSS_BORDERCOLOR = 15,
    D3DTSS_MAGFILTER = 16,
    D3DTSS_MINFILTER = 17,
    D3DTSS_MIPFILTER = 18,
    D3DTSS_MIPMAPLODBIAS = 19,
    D3DTSS_MAXMIPLEVEL = 20,
    D3DTSS_MAXANISOTROPY = 21,
    D3DTSS_BUMPENVLSCALE = 22,
    D3DTSS_BUMPENVLOFFSET = 23,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_ADDRESSW = 25,
    D3DTSS_COLORARG0 = 26,
    D3DTSS_ALPHAARG0 = 27,
    D3DTSS_RESULTARG = 28,
    D3DTSS_FORCE_DWORD = 0x7fffffff
} D3DTEXTURESTAGESTATETYPE;

/* ms886828 "D3DTEXTURETRANSFORMFLAGS" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTEXTURETRANSFORMFLAGS {
    D3DTTFF_DISABLE = 0,
    D3DTTFF_COUNT1 = 1,
    D3DTTFF_COUNT2 = 2,
    D3DTTFF_COUNT3 = 3,
    D3DTTFF_COUNT4 = 4,
    D3DTTFF_PROJECTED = 256,
    D3DTTFF_FORCE_DWORD = 0x7fffffff
} D3DTEXTURETRANSFORMFLAGS;

/* ms887031 "D3DTRANSFORMSTATETYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DTRANSFORMSTATETYPE {
    D3DTS_VIEW = 2,
    D3DTS_PROJECTION = 3,
    D3DTS_TEXTURE0 = 16,
    D3DTS_TEXTURE1 = 17,
    D3DTS_TEXTURE2 = 18,
    D3DTS_TEXTURE3 = 19,
    D3DTS_TEXTURE4 = 20,
    D3DTS_TEXTURE5 = 21,
    D3DTS_TEXTURE6 = 22,
    D3DTS_TEXTURE7 = 23,
    D3DTS_FORCE_DWORD = 0x7fffffff
} D3DTRANSFORMSTATETYPE;

/* ms887540 "D3DZBUFFERTYPE" (Windows Embedded CE 6.0 and later) page
 * print verbatim (Direct3D Mobile, D3dmtypes.h). */
typedef enum _D3DZBUFFERTYPE {
    D3DZB_FALSE = 0,
    D3DZB_TRUE = 1,
    D3DZB_USEW = 2,
    D3DZB_FORCE_DWORD = 0x7fffffff
} D3DZBUFFERTYPE;

#endif /* _WIN32_WCE >= 0x0500 */

