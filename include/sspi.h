/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SSPI_H
#define WCE_SSPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSecHandle { ULONG_PTR dwLower; ULONG_PTR dwUpper; } SecHandle, *PSecHandle, *LPSecHandle;
typedef struct tagSECURITY_STRING { unsigned short Length; unsigned short MaximumLength; unsigned short * Buffer; } SECURITY_STRING, *PSECURITY_STRING, *LPSECURITY_STRING;
typedef struct tagSEC_CHANNEL_BINDINGS { unsigned long dwInitiatorAddrType; unsigned long cbInitiatorLength; unsigned long dwInitiatorOffset; unsigned long dwAcceptorAddrType; unsigned long cbAcceptorLength; unsigned long dwAcceptorOffset; unsigned long cbApplicationDataLength; unsigned long dwApplicationDataOffset; } SEC_CHANNEL_BINDINGS, *PSEC_CHANNEL_BINDINGS, *LPSEC_CHANNEL_BINDINGS;
typedef struct tagSecPkgContext_Sizes { unsigned long cbMaxToken; unsigned long cbMaxSignature; unsigned long cbBlockSize; unsigned long cbSecurityTrailer; } SecPkgContext_Sizes, *PSecPkgContext_Sizes, *LPSecPkgContext_Sizes;
typedef struct tagSecPkgContext_StreamSizes { unsigned long cbHeader; unsigned long cbTrailer; unsigned long cbMaximumMessage; unsigned long cBuffers; unsigned long cbBlockSize; } SecPkgContext_StreamSizes, *PSecPkgContext_StreamSizes, *LPSecPkgContext_StreamSizes;
typedef struct tagSecPkgContext_UserFlags { unsigned long UserFlags; } SecPkgContext_UserFlags, *PSecPkgContext_UserFlags, *LPSecPkgContext_UserFlags;
typedef struct tagSecPkgContext_Flags { unsigned long Flags; } SecPkgContext_Flags, *PSecPkgContext_Flags, *LPSecPkgContext_Flags;
typedef struct tagSecPkgContext_Bindings { unsigned long BindingsLength; SEC_CHANNEL_BINDINGS * Bindings; } SecPkgContext_Bindings, *PSecPkgContext_Bindings, *LPSecPkgContext_Bindings;
typedef struct tagSecPkgContext_AccessToken { void * AccessToken; } SecPkgContext_AccessToken, *PSecPkgContext_AccessToken, *LPSecPkgContext_AccessToken;
typedef struct tagSecPkgContext_NegotiatedTlsExtensions { unsigned long ExtensionsCount; unsigned short * Extensions; } SecPkgContext_NegotiatedTlsExtensions, *PSecPkgContext_NegotiatedTlsExtensions, *LPSecPkgContext_NegotiatedTlsExtensions;


#ifdef __cplusplus
}
#endif
#endif

