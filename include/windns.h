/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINDNS_H
#define WCE_WINDNS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDNS_WIRE_QUESTION { WORD QuestionType; WORD QuestionClass; } DNS_WIRE_QUESTION, *PDNS_WIRE_QUESTION, *LPDNS_WIRE_QUESTION;
typedef struct tagDNS_WIRE_RECORD { WORD RecordType; WORD RecordClass; DWORD TimeToLive; WORD DataLength; } DNS_WIRE_RECORD, *PDNS_WIRE_RECORD, *LPDNS_WIRE_RECORD;
typedef struct tagDNS_PTR_DATA { LPTSTR pNameHost; } DNS_PTR_DATA, *PDNS_PTR_DATA, *LPDNS_PTR_DATA;
typedef struct tagDNS_SOA_DATA { LPTSTR pNamePrimaryServer; LPTSTR pNameAdministrator; DWORD dwSerialNo; DWORD dwRefresh; DWORD dwRetry; DWORD dwExpire; DWORD dwDefaultTtl; } DNS_SOA_DATA, *PDNS_SOA_DATA, *LPDNS_SOA_DATA;
typedef struct tagDNS_MINFO_DATA { LPTSTR pNameMailbox; LPTSTR pNameErrorsMailbox; } DNS_MINFO_DATA, *PDNS_MINFO_DATA, *LPDNS_MINFO_DATA;
typedef struct tagDNS_MX_DATA { LPTSTR pNameExchange; WORD wPreference; WORD Pad; } DNS_MX_DATA, *PDNS_MX_DATA, *LPDNS_MX_DATA;
typedef struct tagDNS_SIG_DATA { LPTSTR pNameSigner; WORD wTypeCovered; BYTE chAlgorithm; BYTE chLabelCount; DWORD dwOriginalTtl; DWORD dwExpiration; DWORD dwTimeSigned; WORD wKeyTag; WORD Pad; BYTE Signature[1]; } DNS_SIG_DATA, *PDNS_SIG_DATA, *LPDNS_SIG_DATA;
typedef struct tagDNS_KEY_DATA { WORD wFlags; BYTE chProtocol; BYTE chAlgorithm; BYTE Key[1]; } DNS_KEY_DATA, *PDNS_KEY_DATA, *LPDNS_KEY_DATA;
typedef struct tagDNS_LOC_DATA { WORD wVersion; WORD wSize; WORD wHorPrec; WORD wVerPrec; DWORD dwLatitude; DWORD dwLongitude; DWORD dwAltitude; } DNS_LOC_DATA, *PDNS_LOC_DATA, *LPDNS_LOC_DATA;
typedef struct tagDNS_NXT_DATA { LPTSTR pNameNext; WORD wNumTypes; WORD wTypes[1]; } DNS_NXT_DATA, *PDNS_NXT_DATA, *LPDNS_NXT_DATA;
typedef struct tagDNS_SRV_DATA { LPTSTR pNameTarget; WORD wPriority; WORD wWeight; WORD wPort; WORD Pad; } DNS_SRV_DATA, *PDNS_SRV_DATA, *LPDNS_SRV_DATA;
typedef struct tagDNS_WINSR_DATA { DWORD dwMappingFlag; DWORD dwLookupTimeout; DWORD dwCacheTimeout; LPTSTR pNameResultDomain; } DNS_WINSR_DATA, *PDNS_WINSR_DATA, *LPDNS_WINSR_DATA;
typedef struct tagDNS_RRSET { PDNS_RECORD pFirstRR; PDNS_RECORD pLastRR; } DNS_RRSET, *PDNS_RRSET, *LPDNS_RRSET;

WCE_IMPORT BOOL WINAPI DnsRecordCompare(IN PDNS_RECORD pRecord1, IN PDNS_RECORD pRecord2) WCE_LINK(DnsRecordCompare);
WCE_IMPORT BOOL WINAPI DnsRecordSetCompare(IN OUT PDNS_RECORD pRR1, IN OUT PDNS_RECORD pRR2, OUT PDNS_RECORD * ppDiff1, OUT PDNS_RECORD * ppDiff2) WCE_LINK(DnsRecordSetCompare);
WCE_IMPORT VOID WINAPI DnsReleaseContextHandle(IN HANDLE hContext) WCE_LINK(DnsReleaseContextHandle);
WCE_IMPORT BOOL WINAPI DnsNameCompare_A(IN LPSTR pName1, IN LPSTR pName2) WCE_LINK(DnsNameCompare_A);
WCE_IMPORT BOOL WINAPI DnsNameCompare_W(IN LPWSTR pName1, IN LPWSTR pName2) WCE_LINK(DnsNameCompare_W);
WCE_IMPORT BOOL WINAPI DnsWriteQuestionToBuffer_W(IN OUT PDNS_MESSAGE_BUFFER pDnsBuffer, IN OUT LPDWORD pdwBufferSize, IN LPWSTR pszName, IN WORD wType, IN WORD Xid, IN BOOL fRecursionDesired) WCE_LINK(DnsWriteQuestionToBuffer_W);
WCE_IMPORT BOOL WINAPI DnsWriteQuestionToBuffer_UTF8(IN OUT PDNS_MESSAGE_BUFFER pDnsBuffer, IN OUT LPDWORD pdwBufferSize, IN LPSTR pszName, IN WORD wType, IN WORD Xid, IN BOOL fRecursionDesired) WCE_LINK(DnsWriteQuestionToBuffer_UTF8);

#define DnsNameCompare_ DnsNameCompare_W
#define DnsWriteQuestionToBuffer_ DnsWriteQuestionToBuffer_W
#ifdef __cplusplus
}
#endif
#endif

