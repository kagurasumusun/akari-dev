/*
 * Obexserver.h -- the header spelling the official CE pages print for
 * the OBEX server service API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * 4 official pages name Obexserver.h in their Header row. Every
 * declaration they attribute to it is already carried by this tree (a
 * few are recorded there as held, with the reason); each is listed
 * below with its page id and the header that holds it. Nothing is
 * re-declared here: a second copy of a typedef, struct or prototype is
 * a second thing to keep in step with the pages, and the pages are the
 * only evidence this tree accepts.
 *
 * A consumer that writes `#include <Obexserver.h>` -- the spelling the
 * documentation uses -- therefore gets exactly the declarations
 * the documentation attributes to it.
 *
 *   OBEXCOMMAND (ms900557) -- Obex.h (record-only there: the print
 *   takes ObexPacketData / ObexVariant members and no CE page publishes
 *   those types)
 *       Windows CE .NET 4.0 and later
 *   OBEXTRANSACTION (ms900561) -- Obex.h (record-only there: the print
 *   takes MemAlloc / MemFree / ObexCommand members and no CE page
 *   publishes MemAlloc or MemFree)
 *       Windows CE .NET 4.0 and later
 *   ServerCallback (ms900565) -- Obex.h
 *       Windows CE .NET 4.0 and later; Developer Defined
 *   ServiceCallback (ms900568) -- Obex.h
 *       Windows CE .NET 4.0 and later; Developer Defined.
 */

#ifndef AKARI_OBEXSERVER_H_
#define AKARI_OBEXSERVER_H_

#include "Obex.h"

#endif /* AKARI_OBEXSERVER_H_ */
