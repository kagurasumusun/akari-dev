/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CMDTREE_H
#define WCE_CMDTREE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDBCONTENT { LPOLESTR pwszPhrase; DWORD dwGenerateMethod; LONG lWeight; LCID lcid; } DBCONTENT, *PDBCONTENT, *LPDBCONTENT;
typedef struct tagDBCONTENTSCOPE { DWORD dwFlags; LPOLESTR *rgpwszTagName; LPOLESTR pwszElementValue; } DBCONTENTSCOPE, *PDBCONTENTSCOPE, *LPDBCONTENTSCOPE;
typedef struct tagDBCONTENTTABLE { LPOLESTR pwszMachine; LPOLESTR pwszCatalog; } DBCONTENTTABLE, *PDBCONTENTTABLE, *LPDBCONTENTTABLE;
typedef struct tagDBCONTENTVECTOR { LONG lWeight; DWORD dwRankingMethod; } DBCONTENTVECTOR, *PDBCONTENTVECTOR, *LPDBCONTENTVECTOR;
typedef struct tagDBGROUPINFO { LCID lcid; } DBGROUPINFO, *PDBGROUPINFO, *LPDBGROUPINFO;
typedef struct tagDBSETFUNC { DWORD dwSetQuantifier; } DBSETFUNC, *PDBSETFUNC, *LPDBSETFUNC;
typedef struct tagDBSORTINFO { BOOL fDesc; LCID lcid; } DBSORTINFO, *PDBSORTINFO, *LPDBSORTINFO;
typedef struct tagDBTEXT { LPOLESTR pwszText; ULONG ulErrorLocator; ULONG ulTokenLength; GUID guidDialect; } DBTEXT, *PDBTEXT, *LPDBTEXT;
typedef struct tagDBLIKE { LONG lWeight; GUID guidDialect; } DBLIKE, *PDBLIKE, *LPDBLIKE;
typedef struct tagDBCONTENTPROXIMITY { DWORD dwProximityUnit; ULONG ulProximityDistance; LONG lWeight; } DBCONTENTPROXIMITY, *PDBCONTENTPROXIMITY, *LPDBCONTENTPROXIMITY;
typedef struct tagDBPROBABILISTIC { LONG lWeight; float flK1; float flK2; float flK3; float flB; } DBPROBABILISTIC, *PDBPROBABILISTIC, *LPDBPROBABILISTIC;


#ifdef __cplusplus
}
#endif
#endif

