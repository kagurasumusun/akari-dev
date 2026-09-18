/*
 * Sms.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: sms.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_SMS_H
#define AKARI_SMS_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Winbase.h"   /* SYSTEMTIME */

/* --- Handle types no CE page typedefs. ------------------------------
 * SMS_HANDLE: 6 corpus pages mention it and none prints a typedef, but
 * ee498029 "SmsOpen" prints
 *   `HRESULT SmsOpen ( const LPCTSTR ptsMessageProtocol,
 *      const DWORD dwMessageModes, const SMS_HANDLE* psmshHandle,
 *      const HANDLE* phMessageAvailableEvent);`
 * and ee497862 "SmsClose" prints `HRESULT SmsClose ( const SMS_HANDLE
 * smshHandle );` (both Header: sms.h, Link Library: sms.lib, Windows
 * Embedded CE 6.0).  A pointer the open call fills and the close call
 * consumes is a handle; see Windef.h:236 for the in-tree precedent. */
typedef HANDLE SMS_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee496874 BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE: page print
 * enum BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE { BPSGS_UNKNOWN = 0, BPSGS_CELL_DISPLAY_IMMEDIATE, BPSGS_CELL, BPSGS_PLMN, BPSGS_LOCATION_AREA, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE {
    BPSGS_UNKNOWN = 0,
    BPSGS_CELL_DISPLAY_IMMEDIATE,
    BPSGS_CELL,
    BPSGS_PLMN,
    BPSGS_LOCATION_AREA
} BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE;

/* ee497250 SMS_ADDRESS_TYPE: page print
 * enum SMS_ADDRESS_TYPE { SMSAT_UNKNOWN=0, SMSAT_INTERNATIONAL, SMSAT_NATIONAL, SMSAT_NETWORKSPECIFIC, SMSAT_SUBSCRIBER, SMSAT_ALPHANUMERIC, SMSAT_ABBRE
 * (Windows Embedded CE 6.0 and later) */
typedef enum SMS_ADDRESS_TYPE {
    SMSAT_UNKNOWN = 0,
    SMSAT_INTERNATIONAL,
    SMSAT_NATIONAL,
    SMSAT_NETWORKSPECIFIC,
    SMSAT_SUBSCRIBER,
    SMSAT_ALPHANUMERIC,
    SMSAT_ABBREVIATED
} SMS_ADDRESS_TYPE;

/* ee497352 PROVIDER_SPECIFIC_REPLACE_OPTION: page print
 * enum PROVIDER_SPECIFIC_REPLACE_OPTION { PSRO_NONE = 0, PSRO_REPLACE_TYPE1, PSRO_REPLACE_TYPE2, PSRO_REPLACE_TYPE3, PSRO_REPLACE_TYPE4, PSRO_REPLACE_TY
 * (Windows Embedded CE 6.0 and later) */
typedef enum PROVIDER_SPECIFIC_REPLACE_OPTION {
    PSRO_NONE = 0,
    PSRO_REPLACE_TYPE1,
    PSRO_REPLACE_TYPE2,
    PSRO_REPLACE_TYPE3,
    PSRO_REPLACE_TYPE4,
    PSRO_REPLACE_TYPE5,
    PSRO_REPLACE_TYPE6,
    PSRO_REPLACE_TYPE7,
    PSRO_RETURN_CALL,
    PSRO_DEPERSONALIZATION
} PROVIDER_SPECIFIC_REPLACE_OPTION;

/* ee497441 SMS_RANGE: page print
 * typedef struct sms_range_tag { DWORD dwMinimum; DWORD dwMaximum; } SMS_RANGE, *LPSMS_RANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct sms_range_tag {
    DWORD dwMinimum;
    DWORD dwMaximum;
} SMS_RANGE, *LPSMS_RANGE;

/* SMS_MAX_ADDRESS_LENGTH: no corpus page prints the value (checked
 * 2026-09-18); 256 per the permitted CeGCC w32api value check
 * (their sms.h marks it "??").  Replace on an official print. */
#define SMS_MAX_ADDRESS_LENGTH 256

/* ee498006 "SMS_ADDRESS" (Windows Embedded CE 6.0 and later) page
 * print. */
typedef struct sms_address_tag {
    SMS_ADDRESS_TYPE smsatAddressType;
    TCHAR ptsAddress[SMS_MAX_ADDRESS_LENGTH];
} SMS_ADDRESS, *LPSMS_ADDRESS;
/* SMS_MESSAGE_ID: no corpus page prints the definition (checked
 * 2026-09-18; the SmsGetMessageStatus/SmsSendMessage/SMS_STATUS_
 * INFORMATION prints only use it).  Derived as the standard WinCE
 * 128-bit identifier; replace on an official print. */
typedef GUID SMS_MESSAGE_ID;

/* ee497110 "SMS_STATUS_INFORMATION" (Windows Embedded CE 6.0 and
 * later) page print. */
typedef struct sms_status_information_tag {
    SMS_MESSAGE_ID smsmidMessageID;
    DWORD dwMessageStatus0;
    DWORD dwMessageStatus1;
    SMS_ADDRESS smsaRecipientAddress;
    SYSTEMTIME stServiceCenterTimeStamp;
    SYSTEMTIME stDischargeTime;
} SMS_STATUS_INFORMATION, *LPSMS_STATUS_INFORMATION;

/* ee497131 "SMS_BROADCAST_RANGES" (Windows Embedded CE 6.0 and
 * later) page print. */
typedef struct sms_broadcast_ranges_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwNumRanges;
    DWORD dwBroadcastMsgLangs;
    BOOL bAccept;
    SMS_RANGE smsrBroadcastRanges[];
} SMS_BROADCAST_RANGES, *LPSMS_BROADCAST_RANGES;

/* ee497445 SMS_DATA_ENCODING: page print
 * enum SMS_DATA_ENCODING { SMSDE_OPTIMAL=0, SMSDE_GSM, SMSDE_UCS2, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum SMS_DATA_ENCODING {
    SMSDE_OPTIMAL = 0,
    SMSDE_GSM,
    SMSDE_UCS2
} SMS_DATA_ENCODING;

/* ee497655 WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING: page print
 * enum WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING { WDPPSPA_8_BIT_PORT_NUMBERS = 0, WDPPSPA_16_BIT_PORT_NUMBERS, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING {
    WDPPSPA_8_BIT_PORT_NUMBERS = 0,
    WDPPSPA_16_BIT_PORT_NUMBERS
} WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING;

/* ee497683 PROVIDER_SPECIFIC_MESSAGE_CLASS: page print
 * enum PROVIDER_SPECIFIC_MESSAGE_CLASS { PS_MESSAGE_CLASS0 = 0, PS_MESSAGE_CLASS1, PS_MESSAGE_CLASS2, PS_MESSAGE_CLASS3, PS_MESSAGE_CLASSUNSPECIFIED, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum PROVIDER_SPECIFIC_MESSAGE_CLASS {
    PS_MESSAGE_CLASS0 = 0,
    PS_MESSAGE_CLASS1,
    PS_MESSAGE_CLASS2,
    PS_MESSAGE_CLASS3,
    PS_MESSAGE_CLASSUNSPECIFIED
} PROVIDER_SPECIFIC_MESSAGE_CLASS;

/* ee498007 BROADCAST_PROVIDER_SPECIFIC_DATA: page print
 * typedef struct broadcast_provider_specific_data_tag { WORD wMessageID; WORD wMessageCode; BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE bpsgsGeograph
 * (Windows Embedded CE 6.0 and later) */
typedef struct broadcast_provider_specific_data_tag {
    WORD wMessageID;
    WORD wMessageCode;
    BROADCAST_PROVIDER_SPECIFIC_GEOGRAPHICAL_SCOPE bpsgsGeographicalScope;
    WORD wUpdateNumber;
} BROADCAST_PROVIDER_SPECIFIC_DATA;

/* ee498093 NOTIFICATION_PROVIDER_SPECIFIC_INDICATOR_TYPE: page print
 * enum NOTIFICATION_PROVIDER_SPECIFIC_INDICATOR_TYPE { NOTIFICATIONPSIT_NONE = 0, NOTIFICATIONPSIT_LINE1 = 1, NOTIFICATIONPSIT_LINE2 = 2, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum NOTIFICATION_PROVIDER_SPECIFIC_INDICATOR_TYPE {
    NOTIFICATIONPSIT_NONE = 0,
    NOTIFICATIONPSIT_LINE1 = 1,
    NOTIFICATIONPSIT_LINE2 = 2
} NOTIFICATION_PROVIDER_SPECIFIC_INDICATOR_TYPE;

/* ee498229 WCMP_PROVIDER_SPECIFIC_MESSAGE_TYPE: page print
 * enum WCMP_PROVIDER_SPECIFIC_MESSAGE_TYPE { WCMPPSMT_UNSUPPORTED = 0, WCMPPSMT_PORT_UNREACHABLE, WCMPPSMT_MESSAGE_TOO_BIG, WCMPPSMT_ECHO_REQUEST, WCMPP
 * (Windows Embedded CE 6.0 and later) */
typedef enum WCMP_PROVIDER_SPECIFIC_MESSAGE_TYPE {
    WCMPPSMT_UNSUPPORTED = 0,
    WCMPPSMT_PORT_UNREACHABLE,
    WCMPPSMT_MESSAGE_TOO_BIG,
    WCMPPSMT_ECHO_REQUEST,
    WCMPPSMT_ECHO_REPLY
} WCMP_PROVIDER_SPECIFIC_MESSAGE_TYPE;

/* ee498285 NOTIFICATION_PROVIDER_SPECIFIC_MSG_WAITING_TYPE: page print
 * enum NOTIFICATION_PROVIDER_SPECIFIC_MSG_WAITING_TYPE { NOTIFICATIONPSMWT_NONE = 0, NOTIFICATIONPSMWT_GENERIC, NOTIFICATIONPSMWT_VOICEMAIL, NOTIFICATIO
 * (Windows Embedded CE 6.0 and later) */
typedef enum NOTIFICATION_PROVIDER_SPECIFIC_MSG_WAITING_TYPE {
    NOTIFICATIONPSMWT_NONE = 0,
    NOTIFICATIONPSMWT_GENERIC,
    NOTIFICATIONPSMWT_VOICEMAIL,
    NOTIFICATIONPSMWT_FAX,
    NOTIFICATIONPSMWT_EMAIL,
    NOTIFICATIONPSMWT_OTHER
} NOTIFICATION_PROVIDER_SPECIFIC_MSG_WAITING_TYPE;


/* ee497478 WDP_PROVIDER_SPECIFIC_DATA: page print
 * typedef struct wdp_provider_specific_data_tag { WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING wdppsPortAddressing; WORD wDestinationPort; WORD wOriginatorPort
 * (Windows Embedded CE 6.0 and later) */
typedef struct wdp_provider_specific_data_tag {
    WDP_PROVIDER_SPECIFIC_PORT_ADDRESSING wdppsPortAddressing;
    WORD wDestinationPort;
    WORD wOriginatorPort;
} WDP_PROVIDER_SPECIFIC_DATA;

/* ee497886 NOTIFICATION_PROVIDER_SPECIFIC_DATA: page print
 * typedef struct notification_provider_specific_data_tag { DWORD dwMessageOptions; PROVIDER_SPECIFIC_MESSAGE_CLASS psMessageClass; PROVIDER_SPECIFIC_REP
 * (Windows Embedded CE 6.0 and later) */
typedef struct notification_provider_specific_data_tag {
    DWORD dwMessageOptions;
    PROVIDER_SPECIFIC_MESSAGE_CLASS psMessageClass;
    PROVIDER_SPECIFIC_REPLACE_OPTION psReplaceOption;
    NOTIFICATION_PROVIDER_SPECIFIC_MSG_WAITING_TYPE npsMsgWaitingType;
    int iNumberOfMessagesWaiting;
    NOTIFICATION_PROVIDER_SPECIFIC_INDICATOR_TYPE npsIndicatorType;
} NOTIFICATION_PROVIDER_SPECIFIC_DATA;


/* ee497060 SmsGetTime: print `HRESULT SmsGetTime (
const SYSTEMTIME* ptsCurrentTime,
const DWORD* pdwErrorMargin);`
 * (Windows Embedded CE 6.0 and later; Link Library: sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetTime(const SYSTEMTIME *ptsCurrentTime, const DWORD *pdwErrorMargin) AKARI_CE_NAME(SmsGetTime);

/* ee497339 SmsClearMessageNotification: print `HRESULT SmsClearMessageNotification (
const LPCTSTR tszProtocolName
);`
 * (Windows Embedded CE 6.0 and later; Link Library: sms.lib) */
AKARI_CE_IMPORT HRESULT SmsClearMessageNotification(const LPCTSTR tszProtocolName) AKARI_CE_NAME(SmsClearMessageNotification);


/* ee497862 SmsClose: print `HRESULT SmsClose (
const SMS_HANDLE smshHandle
);`
 * (generation not stated; Link Library: sms.lib) */
AKARI_CE_IMPORT HRESULT SmsClose(const SMS_HANDLE smshHandle) AKARI_CE_NAME(SmsClose);

/* ee498029 SmsOpen: print `HRESULT SmsOpen (
const LPCTSTR ptsMessageProtocol,
const DWORD dwMessageModes,
const SMS_HANDLE* psmshHandle,
const HANDLE* phMessageAvailableEvent);`
 * (generation not stated; Link Library: sms.lib) */
AKARI_CE_IMPORT HRESULT SmsOpen(const LPCTSTR ptsMessageProtocol, const DWORD dwMessageModes, const SMS_HANDLE *psmshHandle, const HANDLE *phMessageAvailableEvent) AKARI_CE_NAME(SmsOpen);

/* ee498021 SmsGetBroadcastMsgRanges: print `HRESULT
 * SmsGetBroadcastMsgRanges ( const SMS_BROADCAST_RANGES*
 * psmsbrBroadcastRanges );` (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetBroadcastMsgRanges(const SMS_BROADCAST_RANGES *psmsbrBroadcastRanges) AKARI_CE_NAME(SmsGetBroadcastMsgRanges);

/* ee496906 SmsGetMessageSize: print `HRESULT SmsGetMessageSize (
 * const SMS_HANDLE smshHandle, DWORD* const pdwDataSize );`
 * (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetMessageSize(const SMS_HANDLE smshHandle, DWORD *const pdwDataSize) AKARI_CE_NAME(SmsGetMessageSize);

/* ee497508 SmsGetMessageStatus: print `HRESULT SmsGetMessageStatus
 * ( const SMS_HANDLE smshHandle, SMS_MESSAGE_ID smsmidMessageID,
 * SMS_STATUS_INFORMATION* psmssiStatusInformation, const DWORD
 * dwTimeout );` (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetMessageStatus(const SMS_HANDLE smshHandle, SMS_MESSAGE_ID smsmidMessageID, SMS_STATUS_INFORMATION *psmssiStatusInformation, const DWORD dwTimeout) AKARI_CE_NAME(SmsGetMessageStatus);

/* ee498284 SmsGetPhoneNumber: print `HRESULT SmsGetPhoneNumber (
 * const SMS_ADDRESS* psmsaAddress );` (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetPhoneNumber(const SMS_ADDRESS *psmsaAddress) AKARI_CE_NAME(SmsGetPhoneNumber);

/* ee497367 SmsGetSMSC: print `HRESULT SmsGetSMSC ( SMS_ADDRESS*
 * psmsaSMSCAddress );` (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsGetSMSC(SMS_ADDRESS *psmsaSMSCAddress) AKARI_CE_NAME(SmsGetSMSC);

/* ee496912 SmsReadMessage: page print carries SAL `bcount(...)`
 * annotations; declared without them (same parameters).
 * (Link Library: Sms.lib) */
AKARI_CE_IMPORT HRESULT SmsReadMessage(const SMS_HANDLE smshHandle, SMS_ADDRESS *const psmsaSMSCAddress, SMS_ADDRESS *const psmsaSourceAddress, SYSTEMTIME *const pstReceiveTime, BYTE *pbBuffer, DWORD dwBufferSize, BYTE *pbProviderSpecificBuffer, DWORD dwProviderSpecificDataBuffer, DWORD *pdwBytesRead) AKARI_CE_NAME(SmsReadMessage);

/* ee498244 SmsSendMessage page print (Link Library: Sms.lib). */
AKARI_CE_IMPORT HRESULT SmsSendMessage(const SMS_HANDLE smshHandle, const SMS_ADDRESS *psmsaSMSCAddress, const SMS_ADDRESS *psmsaDestinationAddress, const SYSTEMTIME *pstValidityPeriod, const BYTE *pbData, const DWORD dwDataSize, const BYTE *pbProviderSpecificData, const DWORD dwProviderSpecificDataSize, const SMS_DATA_ENCODING smsdeDataEncoding, const DWORD dwOptions, SMS_MESSAGE_ID *psmsmidMessageID) AKARI_CE_NAME(SmsSendMessage);

/* ee497819 SmsSetBroadcastMsgRanges page print
 * (Link Library: Sms.lib). */
AKARI_CE_IMPORT HRESULT SmsSetBroadcastMsgRanges(const SMS_BROADCAST_RANGES *psmsbrBroadcastRanges) AKARI_CE_NAME(SmsSetBroadcastMsgRanges);

/* ee497839 SmsSetSMSC page print (Link Library: Sms.lib). */
AKARI_CE_IMPORT HRESULT SmsSetSMSC(const SMS_ADDRESS *psmsaSMSCAddress) AKARI_CE_NAME(SmsSetSMSC);

/* SmsSetMessageNotification HELD: its SMSREGISTRATIONDATA members
 * are sized by SMS_MAX_APPNAME_LENGTH / SMS_MAX_PARAMS_LENGTH /
 * SMS_MAX_PROTOCOLNAME_LENGTH, and no corpus page prints those
 * values (checked 2026-09-18). */


#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_SMS_H */
