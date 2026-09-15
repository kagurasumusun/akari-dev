/*
 * MediaQueryEngine.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: MediaQueryEngine.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_MEDIAQUERYENGINE_H
#define AKARI_MEDIAQUERYENGINE_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* aa456357 DeviceStatus_e: page print
 * enum DeviceStatus_e { DETACHED = 0, ATTACHED, ACTIVE };
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum DeviceStatus_e {
    DETACHED = 0,
    ATTACHED,
    ACTIVE
} DeviceStatus_e;

/* aa456358 Item_Attribute_e: page print
 * enum Item_Attribute_e { Attr_Title = 0, Attr_Class, Attr_UpnpItemId, Attr_UpnpParentId, Attr_URI, Attr_Date, Attr_Artist, Attr_Actor, Attr_Album, Attr
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum Item_Attribute_e {
    Attr_Title = 0,
    Attr_Class,
    Attr_UpnpItemId,
    Attr_UpnpParentId,
    Attr_URI,
    Attr_Date,
    Attr_Artist,
    Attr_Actor,
    Attr_Album,
    Attr_AlbumArtURI,
    Attr_Genre,
    Attr_Rating,
    Attr_ResSize,
    Attr_ResDuration,
    Attr_ResResolution,
    Attr_ResColorDepth,
    Attr_MusicSampleFrequency,
    Attr_MusicAudioChannels,
    Attr_Description,
    Attr_ProtocolInfo
} Item_Attribute_e;

/* aa456396 MediaType_e: page print
 * enum MediaType_e { Music = 0, Video, Picture, Playlist, MusicAlbum, VideoAlbum, PictureAlbum, MusicArtist, MovieActor, PictureDateFolder, MusicGenre, 
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum MediaType_e {
    Music = 0,
    Video,
    Picture,
    Playlist,
    MusicAlbum,
    VideoAlbum,
    PictureAlbum,
    MusicArtist,
    MovieActor,
    PictureDateFolder,
    MusicGenre,
    VideoGenre
} MediaType_e;

/* aa456397 QueryEngineState_e: page print
 * enum QueryEngineState_e { UnInitialized = 0, Error, Stopped, Running };
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum QueryEngineState_e {
    UnInitialized = 0,
    Error,
    Stopped,
    Running
} QueryEngineState_e;

/* aa456400 QuerySinkEvent_e: page print
 * enum QuerySinkEvent_e { MQE_EVENT_NETWORKAVAILABLE = 0, MQE_EVENT_NETWORKNOTAVAILABLE, MQE_EVENT_SERVERCONNECTED, MQE_EVENT_SERVERDISCONNECTED, MQE_EV
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum QuerySinkEvent_e {
    MQE_EVENT_NETWORKAVAILABLE = 0,
    MQE_EVENT_NETWORKNOTAVAILABLE,
    MQE_EVENT_SERVERCONNECTED,
    MQE_EVENT_SERVERDISCONNECTED,
    MQE_EVENT_SERVERACTIVATED,
    MQE_EVENT_SERVERDEACTIVATED,
    MQE_EVENT_DEVICEAUTHORIZED,
    MQE_EVENT_DEVICEAUTHORIZATIONREVOKED,
    MQE_EVENT_DEVICEREGISTERED,
    MQE_EVENT_DEVICEREGISTRATIONREVOKED,
    MQE_EVENT_CONTENTUPDATE_MUSIC,
    MQE_EVENT_CONTENTUPDATE_VIDEO,
    MQE_EVENT_CONTENTUPDATE_PICTURE,
    MQE_EVENT_CRITICALERROR
} QuerySinkEvent_e;

/* aa456401 SearchBy_e: page print
 * enum SearchBy_e { SearchBy_None = 0, SearchBy_Title, SearchBy_Artist, SearchBy_Actor, SearchBy_Album, SearchBy_Genre, SearchBy_Date };
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum SearchBy_e {
    SearchBy_None = 0,
    SearchBy_Title,
    SearchBy_Artist,
    SearchBy_Actor,
    SearchBy_Album,
    SearchBy_Genre,
    SearchBy_Date
} SearchBy_e;

/* aa456413 SortBy_e: page print
 * enum SortBy_e { SortBy_None = 0, SortBy_Name_Ascending, SortBy_Name_Descending, SortBy_Date_Ascending, SortBy_Date_Descending };
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: MQELib.lib) */
typedef enum SortBy_e {
    SortBy_None = 0,
    SortBy_Name_Ascending,
    SortBy_Name_Descending,
    SortBy_Date_Ascending,
    SortBy_Date_Descending
} SortBy_e;

#endif /* AKARI_MEDIAQUERYENGINE_H */
