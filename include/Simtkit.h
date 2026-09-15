/*
 * Simtkit.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: simtkit.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_SIMTKIT_H
#define AKARI_SIMTKIT_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee496894 SIMTKITRSPITEM: page print
 * typedef struct simtkitrspitem_tag { DWORD cbSize; DWORD dwParams; DWORD dwId; } SIMTKITRSPITEM, *LPSIMTKITRSPITEM;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrspitem_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwId;
} SIMTKITRSPITEM, *LPSIMTKITRSPITEM;

/* ee496908 SIMTKITRSPRECEIVEDATA: page print
 * typedef struct simtkitrspreceivedata_tag { DWORD cbSize; DWORD dwParams; DWORD dwChannelId; DWORD dwDataSize; DWORD dwDataOffset; } SIMTKITRSPRECEIVED
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrspreceivedata_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwChannelId;
    DWORD dwDataSize;
    DWORD dwDataOffset;
} SIMTKITRSPRECEIVEDATA, FAR *LPSIMTKITRSPRECEIVEDATA;

/* ee497027 SIMUSSD: page print
 * typedef struct simussd_tag { DWORD cbSize; DWORD dwParams; DWORD dwAddressType; DWORD dwNumPlan; DWORD dwUSSDSize; DWORD dwUSSDOffset; DWORD dwTextSiz
 * (Windows Embedded CE 6.0 and later) */
typedef struct simussd_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwAddressType;
    DWORD dwNumPlan;
    DWORD dwUSSDSize;
    DWORD dwUSSDOffset;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMUSSD, FAR *LPSIMUSSD;

/* ee497038 SIMLAUNCHBROWSER: page print
 * typedef struct simlaunchbrowser_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwBrowserId; DWORD dwURLSize; DWORD dwURLOffset; DWORD dwBear
 * (Windows Embedded CE 6.0 and later) */
typedef struct simlaunchbrowser_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwBrowserId;
    DWORD dwURLSize;
    DWORD dwURLOffset;
    DWORD dwBearerSize;
    DWORD dwBearerOffset;
    DWORD dwGatewaySize;
    DWORD dwGatewayOffset;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwProvisionFileCount;
    DWORD dwProvisionFileSize;
    DWORD dwProvisionFileOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMLAUNCHBROWSER, FAR *LPSIMLAUNCHBROWSER;

/* ee497090 SIMTKITRSPTEXT: page print
 * typedef struct simtkitrsptext_tag { DWORD cbSize; DWORD dwParams; DWORD dwDCS; DWORD dwYesNo; DWORD dwTextOffset; DWORD dwTextSize; } SIMTKITRSPTEXT, 
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrsptext_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwDCS;
    DWORD dwYesNo;
    DWORD dwTextOffset;
    DWORD dwTextSize;
} SIMTKITRSPTEXT, FAR *LPSIMTKITRSPTEXT;

/* ee497114 SIMSENDDATA: page print
 * typedef struct simsenddata_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwChannelId; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwChannel
 * (Windows Embedded CE 6.0 and later) */
typedef struct simsenddata_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwChannelId;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwChannelDataSize;
    DWORD dwChannelDataOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMSENDDATA, FAR *LPSIMSENDDATA;

/* ee497251 SIMMENU: page print
 * typedef struct simmenu_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwDefaultItem; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwMenuItemC
 * (Windows Embedded CE 6.0 and later) */
typedef struct simmenu_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwDefaultItem;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwMenuItemCount;
    DWORD dwMenuItemSize;
    DWORD dwMenuItemOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMMENU, FAR *LPSIMMENU;

/* ee497278 SIMEVENTLIST: page print
 * typedef struct simeventlist_tag { DWORD cbSize; DWORD dwParams; DWORD dwEventsSize; DWORD dwEventsOffset; } SIMEVENTLIST, FAR *LPSIMEVENTLIST;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simeventlist_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwEventsSize;
    DWORD dwEventsOffset;
} SIMEVENTLIST, FAR *LPSIMEVENTLIST;

/* ee497369 SIMRUNATCMD: page print
 * typedef struct simrunatcmd_tag { DWORD cbSize; DWORD dwParams; DWORD dwCmdSize; DWORD dwCmdOffset; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwIconI
 * (Windows Embedded CE 6.0 and later) */
typedef struct simrunatcmd_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwCmdSize;
    DWORD dwCmdOffset;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMRUNATCMD, FAR *LPSIMRUNATCMD;

/* ee497646 SIMSMS: page print
 * typedef struct simsms_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwAddressType; DWORD dwNumPlan; DWORD dwTextSize; DWORD dwTextOffset; D
 * (Windows Embedded CE 6.0 and later) */
typedef struct simsms_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwAddressType;
    DWORD dwNumPlan;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwAddressSize;
    DWORD dwAddressOffset;
    DWORD dwTPDUSize;
    DWORD dwTPDUOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMSMS, FAR *LPSIMSMS;

/* ee497802 SIMSENDDTMF: page print
 * typedef struct simsenddtmf_tag { DWORD cbSize; DWORD dwParams; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwDTMFSize; DWORD dwDTMFOffset; DWORD dwIco
 * (Windows Embedded CE 6.0 and later) */
typedef struct simsenddtmf_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwDTMFSize;
    DWORD dwDTMFOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMSENDDTMF, FAR *LPSIMSENDDTMF;

/* ee497826 SIMCALL: page print
 * typedef struct simcall_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwRedialDuration; DWORD dwAddressType; DWORD dwNumPlan; DWORD dwTextSi
 * (Windows Embedded CE 6.0 and later) */
typedef struct simcall_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwRedialDuration;
    DWORD dwAddressType;
    DWORD dwNumPlan;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwAddressSize;
    DWORD dwAddressOffset;
    DWORD dwSubAddrSize;
    DWORD dwSubAddrOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMCALL, FAR *LPSIMCALL;

/* ee497833 SIMTEXT: page print
 * typedef struct simtext_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwMinResponse; DWORD dwMaxResponse; DWORD dwTextSize; DWORD dwTextOffs
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtext_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwMinResponse;
    DWORD dwMaxResponse;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwDefaultTextSize;
    DWORD dwDefaultTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMTEXT, FAR *LPSIMTEXT;

/* ee497858 SIMCLOSECHANNEL: page print
 * typedef struct simclosechannel_tag { DWORD cbSize; DWORD dwParams; DWORD dwChannelId; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwIconIdentifier; DW
 * (Windows Embedded CE 6.0 and later) */
typedef struct simclosechannel_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwChannelId;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMCLOSECHANNEL, FAR *LPSIMCLOSECHANNEL;

/* ee497868 SIMTONE: page print
 * typedef struct simtone_tag { DWORD cbSize; DWORD dwParams; DWORD dwTone; DWORD dwDuration; DWORD dwTextSize; DWORD dwTextOffset; DWORD dwIconIdentifie
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtone_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwTone;
    DWORD dwDuration;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMTONE, FAR *LPSIMTONE;

/* ee497876 SIMFILEREFERENCE: page print
 * typedef struct simfilereference_tag { DWORD cbSize; DWORD dwParams; DWORD dwFileSize; DWORD dwFileOffset; } SIMFILEREFERENCE, FAR *LPSIMFILEREFERENCE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simfilereference_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFileSize;
    DWORD dwFileOffset;
} SIMFILEREFERENCE, FAR *LPSIMFILEREFERENCE;

/* ee498025 SIMRECEIVEDATA: page print
 * typedef struct simreceivedata_tag { DWORD cbSize; DWORD dwParams; DWORD dwChannelId; DWORD dwChannelDataLength; DWORD dwTextSize; DWORD dwTextOffset; 
 * (Windows Embedded CE 6.0 and later) */
typedef struct simreceivedata_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwChannelId;
    DWORD dwChannelDataLength;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMRECEIVEDATA, FAR *LPSIMRECEIVEDATA;

/* ee498207 SIMMENUITEM: page print
 * typedef struct simmenuitem_tag { DWORD cbSize; DWORD dwParams; DWORD dwIdentifier; DWORD dwFlags; DWORD dwNextAction; DWORD dwTextSize; DWORD dwTextOf
 * (Windows Embedded CE 6.0 and later) */
typedef struct simmenuitem_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwIdentifier;
    DWORD dwFlags;
    DWORD dwNextAction;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMMENUITEM, FAR *LPSIMMENUITEM;

/* ee498211 SIMOPENCHANNEL: page print
 * typedef struct simopenchannel_tag { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwBearerDescType; DWORD dwBufferSize; DWORD dwAddressType; DWOR
 * (Windows Embedded CE 6.0 and later) */
typedef struct simopenchannel_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwFlags;
    DWORD dwBearerDescType;
    DWORD dwBufferSize;
    DWORD dwAddressType;
    DWORD dwNumPlan;
    DWORD dwDuration1;
    DWORD dwDuration2;
    DWORD dwLocalAddrType;
    DWORD dwDestAddrType;
    DWORD dwProtocolType;
    DWORD dwPortNum;
    DWORD dwTextSize;
    DWORD dwTextOffset;
    DWORD dwBearerDescSize;
    DWORD dwBearerDescOffset;
    DWORD dwAddressSize;
    DWORD dwAddressOffset;
    DWORD dwSubAddressSize;
    DWORD dwSubAddressOffset;
    DWORD dwLocalAddrSize;
    DWORD dwLocalAddrOffset;
    DWORD dwDestAddrSize;
    DWORD dwDestAddrOffset;
    DWORD dwLoginSize;
    DWORD dwLoginOffset;
    DWORD dwPasswordSize;
    DWORD dwPasswordOffset;
    DWORD dwAccessNameSize;
    DWORD dwAccessNameOffset;
    DWORD dwIconIdentifier;
    DWORD dwIconQualifier;
} SIMOPENCHANNEL, FAR *LPSIMOPENCHANNEL;

/* ee498215 SIMTKITRSPCLOSECHANNEL: page print
 * typedef struct simtkitrspclosechannel_tag { DWORD cbSize; DWORD dwParams; DWORD dwChannelId; } SIMTKITRSPCLOSECHANNEL, FAR *LPSIMTKITRSPCLOSECHANNEL;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrspclosechannel_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwChannelId;
} SIMTKITRSPCLOSECHANNEL, FAR *LPSIMTKITRSPCLOSECHANNEL;

/* ee498243 SIMTKITRSPPOLLINTERVAL: page print
 * typedef struct simtkitrsppollinterval_tag { DWORD cbSize; DWORD dwParams; DWORD dwUnit; DWORD dwInterval; } SIMTKITRSPPOLLINTERVAL, FAR *LPSIMTKITRSPP
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrsppollinterval_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwUnit;
    DWORD dwInterval;
} SIMTKITRSPPOLLINTERVAL, FAR *LPSIMTKITRSPPOLLINTERVAL;

/* ee498260 SIMTKITRSPSENDDATA: page print
 * typedef struct simtkitrspsenddata_tag { DWORD cbSize; DWORD dwParams; DWORD dwChannelId; DWORD dwDataLength; } SIMTKITRSPSENDDATA, FAR *LPSIMTKITRSPSE
 * (Windows Embedded CE 6.0 and later) */
typedef struct simtkitrspsenddata_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwChannelId;
    DWORD dwDataLength;
} SIMTKITRSPSENDDATA, FAR *LPSIMTKITRSPSENDDATA;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_SIMTKIT_H */
