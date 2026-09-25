/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RPCDCE_H
#define WCE_RPCDCE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagRPC_PROTSEQ_VECTORA { unsigned int Count; unsigned char * Protseq[1]; } RPC_PROTSEQ_VECTORA, *PRPC_PROTSEQ_VECTORA, *LPRPC_PROTSEQ_VECTORA;
typedef struct tagRPC_PROTSEQ_VECTORW { unsigned int Count; unsigned short * Protseq[1]; } RPC_PROTSEQ_VECTORW, *PRPC_PROTSEQ_VECTORW, *LPRPC_PROTSEQ_VECTORW;
typedef struct tagRPC_PROTSEQ_VECTOR { unsigned int Count; unsigned char * Protseq[1]; } RPC_PROTSEQ_VECTOR, *PRPC_PROTSEQ_VECTOR, *LPRPC_PROTSEQ_VECTOR;
typedef struct tagRPC_POLICY { unsigned int Length; unsigned long EndpointFlags; unsigned long NICFlags; } RPC_POLICY, *PRPC_POLICY, *LPRPC_POLICY;
typedef struct tagRPC_STATS_VECTOR { unsigned int Count; unsigned long Stats[1]; } RPC_STATS_VECTOR, *PRPC_STATS_VECTOR, *LPRPC_STATS_VECTOR;
typedef struct tagRPC_SECURITY_QOS { unsigned long Version; unsigned long Capabilities; unsigned long IdentityTracking; unsigned long ImpersonationType; } RPC_SECURITY_QOS, *PRPC_SECURITY_QOS, *LPRPC_SECURITY_QOS;
typedef struct tagSEC_WINNT_AUTH_IDENTITY { char *User; char *Domain; char *Password; } SEC_WINNT_AUTH_IDENTITY, *PSEC_WINNT_AUTH_IDENTITY, *LPSEC_WINNT_AUTH_IDENTITY;
typedef struct tagSEC_WINNT_AUTH_IDENTITY_W { unsigned short *User; unsigned long UserLength; unsigned short *Domain; unsigned long DomainLength; unsigned short *Password; unsigned long PasswordLength; unsigned long Flags; } SEC_WINNT_AUTH_IDENTITY_W, *PSEC_WINNT_AUTH_IDENTITY_W, *LPSEC_WINNT_AUTH_IDENTITY_W;
typedef struct tagSEC_WINNT_AUTH_IDENTITY_A { unsigned char *User; unsigned long UserLength; unsigned char *Domain; unsigned long DomainLength; unsigned char *Password; unsigned long PasswordLength; unsigned long Flags; } SEC_WINNT_AUTH_IDENTITY_A, *PSEC_WINNT_AUTH_IDENTITY_A, *LPSEC_WINNT_AUTH_IDENTITY_A;
typedef struct tagRPC_CLIENT_INFORMATION1 { unsigned char * UserName; unsigned char * ComputerName; unsigned short Privilege; unsigned long AuthFlags; } RPC_CLIENT_INFORMATION1, *PRPC_CLIENT_INFORMATION1, *LPRPC_CLIENT_INFORMATION1;


#ifdef __cplusplus
}
#endif
#endif

