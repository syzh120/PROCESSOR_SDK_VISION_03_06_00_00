/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== _GateMP_daemon.h ========
 *
 *  Internal header
 *
 */

#ifndef _GATEMP_DAEMON_H
#define _GATEMP_DAEMON_H

#include <ti/ipc/GateMP.h>
#include <ti/ipc/NameServer.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*!
 * Setup the GateMP module. Return the procId of SR0 owner.
 */
Int GateMP_setup(Int32 * sr0ProcId);

/*!
 * Function to destroy the GateMP module. If forced is set
 * we terminate the module regardless of whether there
 * are processes that are using GateMP on the host.
 */
Int GateMP_destroy(Bool forced);

/*!
 * Start the GateMP module.
 */
Int GateMP_start(Void);

/*!
 * Stop the GateMP module.
 */
Int GateMP_stop(Void);

/*!
 * Find a free resource id for a particular protection type.
 */
Int GateMP_getFreeResource(GateMP_RemoteProtect type);

/*!
 * Release a resource id for a particular protection type.
 */
Int GateMP_releaseResource(UInt id, GateMP_RemoteProtect type);

/*!
 * Get the total number of resources for a particular protection type.
 */
Int GateMP_getNumResources(GateMP_RemoteProtect type);

/*!
 * Get the NameServer handle for GateMP.
 */
NameServer_Handle GateMP_getNameServer(Void);

/*!
 * Find out whether GateMP is setup
 */
Bool GateMP_isSetup(Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* _GATEMP_DAEMONH */
