/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RPCDCEP_H
#define WCE_RPCDCEP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagRPC_VERSION { unsigned short MajorVersion; unsigned short MinorVersion; } RPC_VERSION, *PRPC_VERSION, *LPRPC_VERSION;
typedef struct tagRPC_SYNTAX_IDENTIFIER { GUID SyntaxGUID; RPC_VERSION SyntaxVersion; } RPC_SYNTAX_IDENTIFIER, *PRPC_SYNTAX_IDENTIFIER, *LPRPC_SYNTAX_IDENTIFIER;
typedef struct tagRPC_PROTSEQ_ENDPOINT { unsigned char * RpcProtocolSequence; unsigned char * Endpoint; } RPC_PROTSEQ_ENDPOINT, *PRPC_PROTSEQ_ENDPOINT, *LPRPC_PROTSEQ_ENDPOINT;


#ifdef __cplusplus
}
#endif
#endif

