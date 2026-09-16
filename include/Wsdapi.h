/*
 * Wsdapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: wsdapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_WSDAPI_H
#define AKARI_WSDAPI_H

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


/* ee498418 WSD_LOCALIZED_STRING: page print
 * typedef struct _WSD_LOCALIZED_STRING { const WCHAR* Lang; const WCHAR* String; } WSD_LOCALIZED_STRING;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_LOCALIZED_STRING {
    const WCHAR *Lang;
    const WCHAR *String;
} WSD_LOCALIZED_STRING;

/* ee498851 WSD_PROTOCOL_TYPE: page print
 * typedef enum _WSD_PROTOCOL_TYPE { WSD_PT_NONE = 0x00, WSD_PT_UDP = 0x01, WSD_PT_HTTP = 0x02, WSD_PT_HTTPS = 0x04, WSD_PT_ALL = 0xff }WSD_PROTOCOL_TYPE
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef enum _WSD_PROTOCOL_TYPE {
    WSD_PT_NONE = 0x00,
    WSD_PT_UDP = 0x01,
    WSD_PT_HTTP = 0x02,
    WSD_PT_HTTPS = 0x04,
    WSD_PT_ALL = 0xff
} WSD_PROTOCOL_TYPE;

/* ee498965 WSD_EVENTING_FILTER: page print
 * typedef struct _WSD_EVENTING_FILTER { const WCHAR* Dialect; void* Data; } WSD_EVENTING_FILTER;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_EVENTING_FILTER {
    const WCHAR *Dialect;
    void *Data;
} WSD_EVENTING_FILTER;

/* ee498997 WSDUdpMessageType: page print
 * typedef enum _WSDUdpMessageType { ONE_WAY = 0, TWO_WAY = 1 }WSDUdpMessageType;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef enum _WSDUdpMessageType {
    ONE_WAY = 0,
    TWO_WAY = 1
} WSDUdpMessageType;

/* ee499157 WSDEventType: page print
 * typedef enum _WSDEventType { WSDET_NONE = 0, WSDET_INCOMING_MESSAGE = 1, WSDET_INCOMING_FAULT = 2, WSDET_TRANSMISSION_FAILURE = 3, WSDET_RESPONSE_TIME
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef enum _WSDEventType {
    WSDET_NONE = 0,
    WSDET_INCOMING_MESSAGE = 1,
    WSDET_INCOMING_FAULT = 2,
    WSDET_TRANSMISSION_FAILURE = 3,
    WSDET_RESPONSE_TIMEOUTWSDET_RESPONSE_TIMEOUT = 4
} WSDEventType;

/* ee499494 WSD_EVENTING_DELIVERY_MODE: page print
 * typedef struct _WSD_EVENTING_DELIVERY_MODE { const WCHAR* Mode; void* Data; } WSD_EVENTING_DELIVERY_MODE;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_EVENTING_DELIVERY_MODE {
    const WCHAR *Mode;
    void *Data;
} WSD_EVENTING_DELIVERY_MODE;

/* ee499533 WSDXML_TYPE: page print
 * typedef struct _WSDXML_TYPE { WCHAR* Uri; BYTE* Table; } WSDXML_TYPE;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSDXML_TYPE {
    WCHAR *Uri;
    BYTE *Table;
} WSDXML_TYPE;

/* ee500315 WSD_APP_SEQUENCE: page print
 * typedef struct _WSD_APP_SEQUENCE { ULONGLONG InstanceId; const WCHAR* SequenceId; ULONGLONG MessageNumber; } WSD_APP_SEQUENCE;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_APP_SEQUENCE {
    ULONGLONG InstanceId;
    const WCHAR *SequenceId;
    ULONGLONG MessageNumber;
} WSD_APP_SEQUENCE;

/* ee500867 WSD_DATETIME: page print
 * typedef struct _WSD_DATETIME { BOOL isPositive; ULONG year; UCHAR month; UCHAR day; UCHAR hour; UCHAR minute; UCHAR second; UINT millisecond; BOOL TZI
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_DATETIME {
    BOOL isPositive;
    ULONG year;
    UCHAR month;
    UCHAR day;
    UCHAR hour;
    UCHAR minute;
    UCHAR second;
    UINT millisecond;
    BOOL TZIsLocal;
    BOOL TZIsPositive;
    UCHAR TZHour;
    UCHAR TZMinute;
} WSD_DATETIME;

/* ee500879 WSD_DURATION: page print
 * typedef struct _WSD_DURATION { BOOL isPositive; ULONG year; ULONG month; ULONG day; ULONG hour; ULONG minute; ULONG second; ULONG millisecond; } WSD_D
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_DURATION {
    BOOL isPositive;
    ULONG year;
    ULONG month;
    ULONG day;
    ULONG hour;
    ULONG minute;
    ULONG second;
    ULONG millisecond;
} WSD_DURATION;

/* ee501276 WSDUdpRetransmitParams: page print
 * typedef struct _WSDUpdRetransmitParams { ULONG ulSendDelay; ULONG ulRepeat; ULONG ulRepeatMinDelay; ULONG ulRepeatMaxDelay; ULONG ulRepeatUpperDelay; 
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSDUpdRetransmitParams {
    ULONG ulSendDelay;
    ULONG ulRepeat;
    ULONG ulRepeatMinDelay;
    ULONG ulRepeatMaxDelay;
    ULONG ulRepeatUpperDelay;
} WSDUdpRetransmitParams, *PWSDUdpRetransmitParams;


/* ee498840 WSD_EVENTING_EXPIRES: page print
 * typedef struct _WSD_EVENTING_EXPIRES { WSD_DURATION* Duration; WSD_DATETIME* DateTime; } WSD_EVENTING_EXPIRES;
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
typedef struct _WSD_EVENTING_EXPIRES {
    WSD_DURATION *Duration;
    WSD_DATETIME *DateTime;
} WSD_EVENTING_EXPIRES;


/* ee499176 WSDDetachLinkedMemory: print `void WSDDetachLinkedMemory(
void* pVoid
);`
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT void WSDDetachLinkedMemory(void *pVoid) AKARI_CE_NAME(WSDDetachLinkedMemory);

/* ee499437 WSDFreeLinkedMemory: print `void WSDFreeLinkedMemory(
void* pVoid
);`
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT void WSDFreeLinkedMemory(void *pVoid) AKARI_CE_NAME(WSDFreeLinkedMemory);

/* ee499826 WSDAttachLinkedMemory: print `void WSDAttachLinkedMemory (
void* pParent,
void* pChild
);`
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT void WSDAttachLinkedMemory(void *pParent, void *pChild) AKARI_CE_NAME(WSDAttachLinkedMemory);

/* ee500770 WSDSetConfigurationOption: print `HRESULT WINAPI WSDSetConfigurationOption(
DWORD dwOption,
LPVOID pVoid,
DWORD cbInBuffer
);`
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT HRESULT WSDSetConfigurationOption(DWORD dwOption, LPVOID pVoid, DWORD cbInBuffer) AKARI_CE_NAME(WSDSetConfigurationOption);

/* ee500826 WSDGetConfigurationOption: print `HRESULT WINAPI WSDGetConfigurationOption(
DWORD dwOption,
LPVOID pVoid,
DWORD cbOutBuffer
);`
 * (Windows Embedded CE 6.0 R2; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT HRESULT WSDGetConfigurationOption(DWORD dwOption, LPVOID pVoid, DWORD cbOutBuffer) AKARI_CE_NAME(WSDGetConfigurationOption);


/* ee501098 WSDAllocateLinkedMemory: print `void* WSDAllocateLinkedMemory(
void* pParent,
size_t cbSize
);`
 * (generation not stated; Link Library: wsdapi.lib) */
AKARI_CE_IMPORT void* WSDAllocateLinkedMemory(void *pParent, size_t cbSize) AKARI_CE_NAME(WSDAllocateLinkedMemory);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_WSDAPI_H */
