/*
 * Security.h -- the header spelling the official CE pages print for
 * the SSPI surface (Secur32.lib).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * 15 official pages name Security.h in their Header row. Every
 * declaration they attribute to it is already carried by this tree (a
 * few are recorded there as held, with the reason); each is listed
 * below with its page id and the header that holds it. Nothing is
 * re-declared here: a second copy of a typedef, struct or prototype is
 * a second thing to keep in step with the pages, and the pages are the
 * only evidence this tree accepts.
 *
 * A consumer that writes `#include <Security.h>` -- the spelling the
 * documentation uses -- therefore gets exactly the declarations
 * the documentation attributes to it.
 *
 *   AcceptSecurityContext (ms937012) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   AcquireCredentialsHandle (ms937013) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   ApplyControlToken (ms937015) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   CompleteAuthToken (ms937725) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   DeleteSecurityContext (ms906494) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   EnumerateSecurityPackages (ms906509) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   FreeContextBuffer (ms906515) -- Sspi.h
 *       Windows CE 2.12 and later.; Secur32.lib.
 *   FreeCredentialsHandle (ms906519) -- Sspi.h
 *       Windows CE 2.12 and later.; Secur32.lib.
 *   InitializeSecurityContext (ms926002) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   InitSecurityInterface (ms926095) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   MakeSignature (ms926142) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   QueryContextAttributes (ms938456) -- Sspi.h
 *       Windows CE 1.0 and later.; Secur32.lib.
 *   QueryCredentialsAttributes (ms938459) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   QuerySecurityPackageInfo (ms938462) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 *   VerifySignature (ms926455) -- Sspi.h
 *       Windows CE 2.10 and later.; Secur32.lib.
 */

#ifndef AKARI_SECURITY_H_
#define AKARI_SECURITY_H_

#include "Sspi.h"

#endif /* AKARI_SECURITY_H_ */
