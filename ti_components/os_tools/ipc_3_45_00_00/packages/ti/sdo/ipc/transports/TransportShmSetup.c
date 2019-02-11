/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *  ======== TransportShmSetup.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <ti/sdo/ipc/transports/TransportShm.h>

#include "package/internal/TransportShmSetup.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/ipc/_MessageQ.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/utils/_MultiProc.h>

/*
 *  ======== TransportShmSetup_attach ========
 */
Int TransportShmSetup_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    TransportShm_Params params;
    TransportShm_Handle handle;
    Int status = MessageQ_E_FAIL;
    Error_Block eb;

    Error_init(&eb);

    /* init the transport parameters */
    TransportShm_Params_init(&params);
    params.gate = (ti_sdo_ipc_GateMP_Handle)GateMP_getDefaultRemote();
    params.sharedAddr = sharedAddr;
    params.priority = TransportShmSetup_priority;

    /* make sure notify driver has been created */
    if (Notify_intLineRegistered(remoteProcId, 0)) {
        /* create if self < remoteProcId, otherwise open */
        if (MultiProc_self() < remoteProcId) {
            /* create the transport */
            handle = TransportShm_create(remoteProcId, &params, &eb);

            if (handle != NULL) {
                TransportShmSetup_module->handles[remoteProcId] = handle;
                status = MessageQ_S_SUCCESS;
            }
        }
        else {
            status = TransportShm_openByAddr(params.sharedAddr, &handle, &eb);
            TransportShmSetup_module->handles[remoteProcId] = handle;
        }
    }

    return (status);
}

/*
 *  ======== TransportShmSetup_detach ========
 */
Int TransportShmSetup_detach(UInt16 remoteProcId)
{
    TransportShm_Handle handle;

    handle = TransportShmSetup_module->handles[remoteProcId];

    /* Trying to detach an un-attached processor should fail */
    if (handle == NULL) {
        return (MessageQ_E_FAIL);
    }

    /* Unregister the instance */
    TransportShmSetup_module->handles[remoteProcId] = NULL;

    /* Delete/close the transport */
    if (MultiProc_self() < remoteProcId) {
        TransportShm_delete(&handle);
    }
    else {
        TransportShm_close(&handle);
    }

    return (MessageQ_S_SUCCESS);
}

/*
 *  ======== TransportShmSetup_isRegistered ========
 */
Bool TransportShmSetup_isRegistered(UInt16 remoteProcId)
{
    Bool registered;

    registered = (TransportShmSetup_module->handles[remoteProcId] != NULL);

    return (registered);
}

/*
 *  ======== TransportShmSetup_sharedMemReq ========
 */
SizeT TransportShmSetup_sharedMemReq(Ptr sharedAddr)
{
    TransportShm_Params params;
    SizeT memReq = 0;

    if (ti_sdo_utils_MultiProc_numProcessors > 1) {
        params.sharedAddr = sharedAddr;
        memReq += TransportShm_sharedMemReq(&params);
    }

    return(memReq);
}
