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


/* --- WSD XML / SOAP structs (each block cites its page print). ------
 * Pointers-only COM interfaces stay opaque: no corpus page prints
 * vtable order for them (checked 2026-09-18). */

/* ee499798 WSDXML_NAME (ee499172's member needs the forward). */
typedef struct _WSDXML_NAMESPACE WSDXML_NAMESPACE;
typedef struct _WSDXML_NAME {
  WSDXML_NAMESPACE *Space;
  WCHAR *LocalName;
} WSDXML_NAME;

/* ee499172 WSDXML_NAMESPACE page print. */
struct _WSDXML_NAMESPACE {
  const WCHAR *Uri;
  const WCHAR *PreferredPrefix;
  WSDXML_NAME *Names;
  WORD NamesCount;
  WORD Encoding;
};

/* ee498807 WSDXML_NODE page print (anonymous enum as printed). */
typedef struct _WSDXML_ELEMENT WSDXML_ELEMENT;
typedef struct _WSDXML_NODE {
  enum {
     ElementType,
     TextType
  } Type;
  WSDXML_ELEMENT *Parent;
  struct _WSDXML_NODE *Next;
} WSDXML_NODE;

/* ee498922 WSDXML_ELEMENT page print. */
typedef struct _WSDXML_ATTRIBUTE WSDXML_ATTRIBUTE;
typedef struct _WSDXML_PREFIX_MAPPING WSDXML_PREFIX_MAPPING;
struct _WSDXML_ELEMENT {
  WSDXML_NODE Node;
  WSDXML_NAME *Name;
  WSDXML_ATTRIBUTE *FirstAttribute;
  WSDXML_NODE *FirstChild;
  WSDXML_PREFIX_MAPPING *PrefixMappings;
};

/* ee498865 WSDXML_ATTRIBUTE page print. */
struct _WSDXML_ATTRIBUTE {
  WSDXML_ELEMENT *Element;
  WSDXML_ATTRIBUTE *Next;
  WSDXML_NAME *Name;
  WCHAR *Value;
};

/* ee500942 WSDXML_PREFIX_MAPPING page print. */
struct _WSDXML_PREFIX_MAPPING {
  DWORD Refs;
  WSDXML_PREFIX_MAPPING *Next;
  WSDXML_NAMESPACE *Space;
  WCHAR *Prefix;
};

/* ee499462 WSD_LOCALIZED_STRING_LIST page print. */
typedef struct _WSD_LOCALIZED_STRING_LIST {
  struct _WSD_LOCALIZED_STRING_LIST *Next;
  WSD_LOCALIZED_STRING *Element;
} WSD_LOCALIZED_STRING_LIST;

/* ee498962 WSD_SOAP_FAULT_SUBCODE page print. */
typedef struct _WSD_SOAP_FAULT_SUBCODE {
  WSDXML_NAME *Value;
  struct _WSD_SOAP_FAULT_SUBCODE *Subcode;
} WSD_SOAP_FAULT_SUBCODE;

/* ee498689 WSD_SOAP_FAULT_CODE page print. */
typedef struct _WSD_SOAP_FAULT_CODE {
  WSDXML_NAME *Value;
  WSD_SOAP_FAULT_SUBCODE *Subcode;
} WSD_SOAP_FAULT_CODE;

/* ee498943 WSD_SOAP_FAULT_REASON page print. */
typedef struct _WSD_SOAP_FAULT_REASON {
  WSD_LOCALIZED_STRING_LIST *Text;
} WSD_SOAP_FAULT_REASON;

/* ee500259 WSD_SOAP_FAULT page print. */
typedef struct _WSD_SOAP_FAULT {
  WSD_SOAP_FAULT_CODE *Code;
  WSD_SOAP_FAULT_REASON *Reason;
  const WCHAR *Node;
  const WCHAR *Role;
  WSDXML_ELEMENT *Detail;
} WSD_SOAP_FAULT;

/* COM interfaces used only through pointers below; no corpus page
 * prints their vtable order (checked 2026-09-18). */
typedef struct IWSDXMLContext IWSDXMLContext;
typedef struct IWSDDeviceHost IWSDDeviceHost;
typedef struct IWSDDeviceProxy IWSDDeviceProxy;
typedef struct IWSDAddress IWSDAddress;
typedef struct IWSDiscoveryProvider IWSDiscoveryProvider;
typedef struct IWSDiscoveryPublisher IWSDiscoveryPublisher;
typedef struct IWSDHttpAddress IWSDHttpAddress;
typedef struct IWSDHttpMessageParameters IWSDHttpMessageParameters;
typedef struct IWSDOutboundAttachment IWSDOutboundAttachment;
typedef struct IWSDUdpAddress IWSDUdpAddress;
typedef struct IWSDUdpMessageParameters IWSDUdpMessageParameters;

/* ee499213 WSDCreateDeviceHost (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateDeviceHost(const WCHAR *pszLocalId, IWSDXMLContext *pContext, IWSDDeviceHost **ppDeviceHost) AKARI_CE_NAME(WSDCreateDeviceHost);

/* ee500217 WSDCreateDeviceHostAdvanced (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateDeviceHostAdvanced(const WCHAR *pszLocalId, IWSDXMLContext *pContext, IWSDAddress **ppHostAddresses, DWORD dwHostAddressCount, IWSDDeviceHost **ppDeviceHost) AKARI_CE_NAME(WSDCreateDeviceHostAdvanced);

/* ee499802 WSDCreateDeviceProxy (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateDeviceProxy(const WCHAR *pszDeviceId, IWSDAddress *pDeviceAddress, const WCHAR *pszLocalId, IWSDXMLContext *pContext, IWSDDeviceProxy **ppDeviceProxy) AKARI_CE_NAME(WSDCreateDeviceProxy);

/* ee500750 WSDCreateDiscoveryProvider (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateDiscoveryProvider(IWSDXMLContext *pContext, IWSDiscoveryProvider **ppProvider) AKARI_CE_NAME(WSDCreateDiscoveryProvider);

/* ee500819 WSDCreateDiscoveryPublisher (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateDiscoveryPublisher(IWSDXMLContext *pContext, IWSDiscoveryPublisher **ppPublisher) AKARI_CE_NAME(WSDCreateDiscoveryPublisher);

/* ee499018 WSDCreateHttpAddress (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateHttpAddress(IWSDHttpAddress **ppAddress) AKARI_CE_NAME(WSDCreateHttpAddress);

/* ee498662 WSDCreateHttpMessageParameters (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateHttpMessageParameters(IWSDHttpMessageParameters **ppTxParams) AKARI_CE_NAME(WSDCreateHttpMessageParameters);

/* ee501103 WSDCreateOutboundAttachment (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateOutboundAttachment(IWSDOutboundAttachment **attachmentOut) AKARI_CE_NAME(WSDCreateOutboundAttachment);

/* ee498998 WSDCreateUdpAddress (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateUdpAddress(IWSDUdpAddress **ppAddress) AKARI_CE_NAME(WSDCreateUdpAddress);

/* ee499481 WSDCreateUdpMessageParameters (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDCreateUdpMessageParameters(IWSDUdpMessageParameters **ppTxParams) AKARI_CE_NAME(WSDCreateUdpMessageParameters);

/* ee498805 WSDGenerateFault (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDGenerateFault(const LPCWSTR *pszCode, const LPCWSTR *pszSubCode, const LPCWSTR *pszReason, const LPCWSTR *pszDetail, IWSDXMLContext *pContext, WSD_SOAP_FAULT **ppFault) AKARI_CE_NAME(WSDGenerateFault);

/* ee498654 WSDGenerateFaultEx (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDGenerateFaultEx(WSDXML_NAME *pCode, WSDXML_NAME *pSubCode, WSD_LOCALIZED_STRING_LIST *pReasons, const LPCWSTR *pszDetail, WSD_SOAP_FAULT **ppFault) AKARI_CE_NAME(WSDGenerateFaultEx);

/* ee499484 WSDRegisterNamespaces (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT void WSDRegisterNamespaces(IWSDXMLContext *pContext) AKARI_CE_NAME(WSDRegisterNamespaces);

/* ee498632 WSDXMLAddChild; the print `HRESULT STDAPI` is an
 * artifact -- STDAPI already spells the HRESULT convention, kept
 * once (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLAddChild(WSDXML_ELEMENT *pParent, WSDXML_ELEMENT *pChild) AKARI_CE_NAME(WSDXMLAddChild);

/* ee499225 WSDXMLAddSibling (same STDAPI print artifact; wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLAddSibling(WSDXML_ELEMENT *pFirst, WSDXML_ELEMENT *pSecond) AKARI_CE_NAME(WSDXMLAddSibling);

/* ee498989 WSDXMLBuildAnyForSingleElement (STDAPI print artifact; wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLBuildAnyForSingleElement(WSDXML_NAME *pElementName, const LPCWSTR *pszText, WSDXML_ELEMENT **ppAny) AKARI_CE_NAME(WSDXMLBuildAnyForSingleElement);

/* ee500847 WSDXMLCleanupElement (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLCleanupElement(WSDXML_ELEMENT *pAny) AKARI_CE_NAME(WSDXMLCleanupElement);

/* ee498635 WSDXMLCreateContext (Link Library: wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLCreateContext(IWSDXMLContext **ppContext) AKARI_CE_NAME(WSDXMLCreateContext);

/* ee498682 WSDXMLGetNameFromBuiltinNamespace (wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLGetNameFromBuiltinNamespace(LPCWSTR pszNamespace, LPCWSTR pszName, WSDXML_NAME **ppName) AKARI_CE_NAME(WSDXMLGetNameFromBuiltinNamespace);

/* ee499228 WSDXMLGetValueFromAny (STDAPI print artifact; wsdapi.lib). */
AKARI_CE_IMPORT HRESULT WSDXMLGetValueFromAny(const WCHAR *pszNamespace, const WCHAR *pszName, WSDXML_ELEMENT *pAny, const LPCWSTR **ppszValue) AKARI_CE_NAME(WSDXMLGetValueFromAny);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_WSDAPI_H */
