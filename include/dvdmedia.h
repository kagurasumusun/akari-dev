/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DVDMEDIA_H
#define WCE_DVDMEDIA_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagAM_AC3_ERROR_CONCEALMENT { BOOL fRepeatPreviousBlock; BOOL fErrorInCurrentBlock; } AM_AC3_ERROR_CONCEALMENT, *PAM_AC3_ERROR_CONCEALMENT, *LPAM_AC3_ERROR_CONCEALMENT;
typedef struct tagAM_AC3_ALTERNATE_AUDIO { BOOL fStereo; ULONG DualMode; } AM_AC3_ALTERNATE_AUDIO, *PAM_AC3_ALTERNATE_AUDIO, *LPAM_AC3_ALTERNATE_AUDIO;
typedef struct tagAM_AC3_DOWNMIX { BOOL fDownMix; BOOL fDolbySurround; } AM_AC3_DOWNMIX, *PAM_AC3_DOWNMIX, *LPAM_AC3_DOWNMIX;
typedef struct tagAM_AC3_BIT_STREAM_MODE { LONG BitStreamMode; } AM_AC3_BIT_STREAM_MODE, *PAM_AC3_BIT_STREAM_MODE, *LPAM_AC3_BIT_STREAM_MODE;
typedef struct tagAM_AC3_DIALOGUE_LEVEL { ULONG DialogueLevel; } AM_AC3_DIALOGUE_LEVEL, *PAM_AC3_DIALOGUE_LEVEL, *LPAM_AC3_DIALOGUE_LEVEL;
typedef struct tagAM_AC3_ROOM_TYPE { BOOL fLargeRoom; } AM_AC3_ROOM_TYPE, *PAM_AC3_ROOM_TYPE, *LPAM_AC3_ROOM_TYPE;
typedef struct tagAM_DVDCOPY_CHLGKEY { BYTE ChlgKey[10]; BYTE Reserved[2]; } AM_DVDCOPY_CHLGKEY, *PAM_DVDCOPY_CHLGKEY, *LPAM_DVDCOPY_CHLGKEY;
typedef struct tagAM_DVDCOPY_BUSKEY { BYTE BusKey[5]; BYTE Reserved[1]; } AM_DVDCOPY_BUSKEY, *PAM_DVDCOPY_BUSKEY, *LPAM_DVDCOPY_BUSKEY;
typedef struct tagAM_DVDCOPY_DISCKEY { BYTE DiscKey[2048]; } AM_DVDCOPY_DISCKEY, *PAM_DVDCOPY_DISCKEY, *LPAM_DVDCOPY_DISCKEY;
typedef struct tagAM_COPY_MACROVISION { ULONG MACROVISIONLevel; } AM_COPY_MACROVISION, *PAM_COPY_MACROVISION, *LPAM_COPY_MACROVISION;
typedef struct tagAM_DVDCOPY_SET_COPY_STATE { ULONG DVDCopyState; } AM_DVDCOPY_SET_COPY_STATE, *PAM_DVDCOPY_SET_COPY_STATE, *LPAM_DVDCOPY_SET_COPY_STATE;


#ifdef __cplusplus
}
#endif
#endif

