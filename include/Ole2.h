/*
 * Ole2.h -- the header spelling the official CE pages print for
 * the OLE2 core surface (Ole32.lib / Ole232.lib).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * 51 official pages name Ole2.h in their Header row. Every declaration
 * they attribute to it is already carried by this tree (a few are
 * recorded there as held, with the reason); each is listed below with
 * its page id and the header that holds it. Nothing is re-declared
 * here: a second copy of a typedef, struct or prototype is a second
 * thing to keep in step with the pages, and the pages are the only
 * evidence this tree accepts.
 *
 * A consumer that writes `#include <Ole2.h>` -- the spelling the
 * documentation uses -- therefore gets exactly the declarations
 * the documentation attributes to it.
 *
 *   CreateOleAdviseHolder (_wcesdk_COM_CreateOleAdviseHolder) --
 *   Objbase.h
 *       Windows CE OS; Ole232.lib
 *   CreateOleAdviseHolder (ms864397) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   CreateOleAdviseHolder (ms886953) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   CreateStreamOnHGlobal (_wcesdk_com_CreateStreamOnHGlobal) --
 *   Objbase.h
 *       Windows CE OS; Ole232.lib
 *   CreateStreamOnHGlobal (ms864401) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   CreateStreamOnHGlobal (ms886955) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   GetHGlobalFromStream (_wcesdk_com_GetHGlobalFromStream) --
 *   Objbase.h
 *       Windows CE OS; Ole232.lib
 *   GetHGlobalFromStream (aa515040) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   GetHGlobalFromStream (ms886990) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleCreate (_wcesdk_COM_OleCreate) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleCreate (ms890815) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleCreate (ms892590) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleDraw (_wcesdk_COM_OleDraw) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleDraw (ms890819) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleDraw (ms892591) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleIsRunning (_wcesdk_COM_OleIsRunning) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleIsRunning (ms890830) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleIsRunning (ms892593) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleLoadFromStream (_wcesdk_com_OleLoadFromStream) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleLoadFromStream (ms890841) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleLoadFromStream (ms892595) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleRun (_wcesdk_COM_OleRun) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleRun (ms890845) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleRun (ms892596) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSave (_wcesdk_COM_OleSave) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleSave (ms890847) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSave (ms892597) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSaveToStream (_wcesdk_com_OleSaveToStream) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleSaveToStream (ms890854) -- Objbase.h
 *       Windows CE 3.0 and later.; Ole32.lib.
 *   OleSaveToStream (ms892598) -- Objbase.h
 *       Windows CE 3.0 and later.; Ole32.lib.
 *   OleSetContainedObject (_wcesdk_COM_OleSetContainedObject) --
 *   Objbase.h
 *       Windows CE OS; Ole232.lib
 *   OleSetContainedObject (ms890858) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSetContainedObject (ms892599) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSetMenuDescriptor (_wcesdk_COM_OleSetMenuDescriptor) --
 *   Objbase.h (held there: the print takes HOLEMENU / LPOLEINPLACEFRAME
 *   / LPOLEINPLACEACTIVEOBJECT and no CE page publishes those typedefs)
 *       Windows CE OS; Ole232.lib
 *   OleSetMenuDescriptor (ms890863) -- Objbase.h (held there: the print
 *   takes HOLEMENU / LPOLEINPLACEFRAME / LPOLEINPLACEACTIVEOBJECT and
 *   no CE page publishes those typedefs)
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   OleSetMenuDescriptor (ms892600) -- Objbase.h (held there: the print
 *   takes HOLEMENU / LPOLEINPLACEFRAME / LPOLEINPLACEACTIVEOBJECT and
 *   no CE page publishes those typedefs)
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   ReadClassStg (_wcesdk_com_ReadClassStg) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   ReadClassStg (ms891237) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   ReadClassStg (ms892641) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   ReadClassStm (_wcesdk_COM_ReadClassStm) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   ReadClassStm (ms891238) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   ReadClassStm (ms892642) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   ReleaseStgMedium (_wcesdk_COM_ReleaseStgMedium) -- Objbase.h
 *       Windows CE OS
 *   ReleaseStgMedium (ms891240) -- Objbase.h
 *       Windows CE 2.10 and later.; Ole32.lib.
 *   ReleaseStgMedium (ms892649) -- Objbase.h
 *       Windows CE 2.10 and later.; Ole32.lib.
 *   WriteClassStg (_wcesdk_COM_WriteClassStg) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   WriteClassStg (ms892128) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   WriteClassStg (ms897190) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   WriteClassStm (_wcesdk_COM_WriteClassStm) -- Objbase.h
 *       Windows CE OS; Ole232.lib
 *   WriteClassStm (ms892129) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 *   WriteClassStm (ms897191) -- Objbase.h
 *       Windows CE 2.0 and later.; Ole32.lib.
 */

#ifndef AKARI_OLE2_H_
#define AKARI_OLE2_H_

#include "Objbase.h"

#endif /* AKARI_OLE2_H_ */
