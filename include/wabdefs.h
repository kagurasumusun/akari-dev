/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WABDEFS_H
#define WCE_WABDEFS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMAPIUID { BYTE ab[16]; } MAPIUID, *PMAPIUID, *LPMAPIUID;
typedef struct tagSBinary { ULONG cb; LPBYTE lpb; } SBinary, *PSBinary, *LPSBinary;
typedef struct tagSShortArray { ULONG cValues; short int FAR *lpi; } SShortArray, *PSShortArray, *LPSShortArray;
typedef struct tagSGuidArray { ULONG cValues; GUID FAR *lpguid; } SGuidArray, *PSGuidArray, *LPSGuidArray;
typedef struct tagSRealArray { ULONG cValues; float FAR *lpflt; } SRealArray, *PSRealArray, *LPSRealArray;
typedef struct tagSLongArray { ULONG cValues; LONG FAR *lpl; } SLongArray, *PSLongArray, *LPSLongArray;
typedef struct tagSLargeIntegerArray { ULONG cValues; LARGE_INTEGER FAR *lpli; } SLargeIntegerArray, *PSLargeIntegerArray, *LPSLargeIntegerArray;
typedef struct tagSDateTimeArray { ULONG cValues; FILETIME FAR *lpft; } SDateTimeArray, *PSDateTimeArray, *LPSDateTimeArray;
typedef struct tagSAppTimeArray { ULONG cValues; double FAR *lpat; } SAppTimeArray, *PSAppTimeArray, *LPSAppTimeArray;
typedef struct tagSBinaryArray { ULONG cValues; SBinary FAR *lpbin; } SBinaryArray, *PSBinaryArray, *LPSBinaryArray;
typedef struct tagSDoubleArray { ULONG cValues; double FAR *lpdbl; } SDoubleArray, *PSDoubleArray, *LPSDoubleArray;
typedef struct tagSWStringArray { ULONG cValues; LPWSTR FAR *lppszW; } SWStringArray, *PSWStringArray, *LPSWStringArray;
typedef struct tagSLPSTRArray { ULONG cValues; LPSTR FAR *lppszA; } SLPSTRArray, *PSLPSTRArray, *LPSLPSTRArray;
typedef struct tagMAPIERROR { ULONG ulVersion; LPTSTR lpszError; LPTSTR lpszComponent; ULONG ulLowLevelError; ULONG ulContext; } MAPIERROR, *PMAPIERROR, *LPMAPIERROR;
typedef struct tagNEWMAIL_NOTIFICATION { ULONG cbEntryID; LPENTRYID lpEntryID; ULONG cbParentID; LPENTRYID lpParentID; ULONG ulFlags; LPTSTR lpszMessageClass; ULONG ulMessageFlags; } NEWMAIL_NOTIFICATION, *PNEWMAIL_NOTIFICATION, *LPNEWMAIL_NOTIFICATION;
typedef struct tagEXTENDED_NOTIFICATION { ULONG ulEvent; ULONG cb; LPBYTE pbEventParameters; } EXTENDED_NOTIFICATION, *PEXTENDED_NOTIFICATION, *LPEXTENDED_NOTIFICATION;
typedef struct tagSSortOrder { ULONG ulPropTag; ULONG ulOrder; } SSortOrder, *PSSortOrder, *LPSSortOrder;
typedef struct tagSBitMaskRestriction { ULONG relBMR; ULONG ulPropTag; ULONG ulMask; } SBitMaskRestriction, *PSBitMaskRestriction, *LPSBitMaskRestriction;
typedef struct tagSComparePropsRestriction { ULONG relop; ULONG ulPropTag1; ULONG ulPropTag2; } SComparePropsRestriction, *PSComparePropsRestriction, *LPSComparePropsRestriction;
typedef struct tagSSizeRestriction { ULONG relop; ULONG ulPropTag; ULONG cb; } SSizeRestriction, *PSSizeRestriction, *LPSSizeRestriction;
typedef struct tagSExistRestriction { ULONG ulReserved1; ULONG ulPropTag; ULONG ulReserved2; } SExistRestriction, *PSExistRestriction, *LPSExistRestriction;
typedef struct tagDTBLLABEL { ULONG ulbLpszLabelName; ULONG ulFlags; } DTBLLABEL, *PDTBLLABEL, *LPDTBLLABEL;
typedef struct tagDTBLEDIT { ULONG ulbLpszCharsAllowed; ULONG ulFlags; ULONG ulNumCharsAllowed; ULONG ulPropTag; } DTBLEDIT, *PDTBLEDIT, *LPDTBLEDIT;
typedef struct tagDTBLLBX { ULONG ulFlags; ULONG ulPRSetProperty; ULONG ulPRTableName; } DTBLLBX, *PDTBLLBX, *LPDTBLLBX;
typedef struct tagDTBLCOMBOBOX { ULONG ulbLpszCharsAllowed; ULONG ulFlags; ULONG ulNumCharsAllowed; ULONG ulPRPropertyName; ULONG ulPRTableName; } DTBLCOMBOBOX, *PDTBLCOMBOBOX, *LPDTBLCOMBOBOX;
typedef struct tagDTBLDDLBX { ULONG ulFlags; ULONG ulPRDisplayProperty; ULONG ulPRSetProperty; ULONG ulPRTableName; } DTBLDDLBX, *PDTBLDDLBX, *LPDTBLDDLBX;
typedef struct tagDTBLCHECKBOX { ULONG ulbLpszLabel; ULONG ulFlags; ULONG ulPRPropertyName; } DTBLCHECKBOX, *PDTBLCHECKBOX, *LPDTBLCHECKBOX;
typedef struct tagDTBLGROUPBOX { ULONG ulbLpszLabel; ULONG ulFlags; } DTBLGROUPBOX, *PDTBLGROUPBOX, *LPDTBLGROUPBOX;
typedef struct tagDTBLBUTTON { ULONG ulbLpszLabel; ULONG ulFlags; ULONG ulPRControl; } DTBLBUTTON, *PDTBLBUTTON, *LPDTBLBUTTON;
typedef struct tagDTBLPAGE { ULONG ulbLpszLabel; ULONG ulFlags; ULONG ulbLpszComponent; ULONG ulContext; } DTBLPAGE, *PDTBLPAGE, *LPDTBLPAGE;
typedef struct tagDTBLRADIOBUTTON { ULONG ulbLpszLabel; ULONG ulFlags; ULONG ulcButtons; ULONG ulPropTag; long lReturnValue; } DTBLRADIOBUTTON, *PDTBLRADIOBUTTON, *LPDTBLRADIOBUTTON;
typedef struct tagDTBLMVLISTBOX { ULONG ulFlags; ULONG ulMVPropTag; } DTBLMVLISTBOX, *PDTBLMVLISTBOX, *LPDTBLMVLISTBOX;
typedef struct tagDTBLMVDDLBX { ULONG ulFlags; ULONG ulMVPropTag; } DTBLMVDDLBX, *PDTBLMVDDLBX, *LPDTBLMVDDLBX;


#ifdef __cplusplus
}
#endif
#endif

