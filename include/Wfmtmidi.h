/*
 * Wfmtmidi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: wfmtmidi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_WFMTMIDI_H
#define AKARI_WFMTMIDI_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Mmsystem.h"   /* WAVEFORMATEX */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee487515 WAVEFORMAT_MIDI: page print
 * typedef struct _WAVEFORMAT_MIDI { WAVEFORMATEX wfx; UINT32 USecPerQuarterNote; UINT32 TicksPerQuarterNote; } WAVEFORMAT_MIDI, *LPWAVEFORMAT_MIDI;
 * (Windows Embedded CE 6.0 and later) */
typedef struct _WAVEFORMAT_MIDI {
    WAVEFORMATEX wfx;
    UINT32 USecPerQuarterNote;
    UINT32 TicksPerQuarterNote;
} WAVEFORMAT_MIDI, *LPWAVEFORMAT_MIDI;

/* ee487534 WAVEFORMAT_MIDI_MESSAGE: page print
 * typedef struct _WAVEFORMAT_MIDI_MESSAGE { UINT32 DeltaTicks; DWORD MidiMsg; } WAVEFORMAT_MIDI_MESSAGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct _WAVEFORMAT_MIDI_MESSAGE {
    UINT32 DeltaTicks;
    DWORD MidiMsg;
} WAVEFORMAT_MIDI_MESSAGE;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_WFMTMIDI_H */
