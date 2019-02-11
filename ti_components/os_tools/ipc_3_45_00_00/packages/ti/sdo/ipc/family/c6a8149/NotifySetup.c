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
 *  ======== NotifySetup.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>

#include <ti/sdo/ipc/notifyDrivers/NotifyDriverShm.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/Ipc.h>

#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/NotifySetup.xdc.h"

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== NotifySetup_attach ========
 *  Initialize interrupt
 */
Int NotifySetup_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    NotifyDriverShm_Params notifyShmParams;
    NotifyDriverShm_Handle shmDrvHandle;
    ti_sdo_ipc_Notify_Handle notifyHandle;
    Int status = Notify_S_SUCCESS;
    Error_Block eb;

    Error_init(&eb);

    NotifyDriverShm_Params_init(&notifyShmParams);
    notifyShmParams.sharedAddr = sharedAddr;
    notifyShmParams.remoteProcId  = remoteProcId;

    /* Disable cache for inter-ducati NotifyDriverShm instances */
    if ((MultiProc_self() == NotifySetup_vpssProcId &&
         remoteProcId == NotifySetup_videoProcId) ||
        (MultiProc_self() == NotifySetup_videoProcId &&
         remoteProcId == NotifySetup_vpssProcId)) {
         notifyShmParams.cacheLineSize = 0;
         notifyShmParams.cacheEnabled = FALSE;
    }

    /* Set the intVectorId if on the DSP */
    if (MultiProc_self() == NotifySetup_dspProcId) {
        notifyShmParams.intVectorId = NotifySetup_dspIntVectId;

        if (remoteProcId == NotifySetup_eveProcId) {
            notifyShmParams.intVectorId = NotifySetup_dspIntVectIdForEve;
        }
        else {
            notifyShmParams.intVectorId = NotifySetup_dspIntVectId;
        }
    }

    /* Set the intVectorId if on the EVE */
    if (MultiProc_self() == NotifySetup_eveProcId) {
        notifyShmParams.intVectorId = NotifySetup_eveIntVectId;
    }

    shmDrvHandle = NotifyDriverShm_create(&notifyShmParams, &eb);
    if (shmDrvHandle == NULL) {
        return (Notify_E_FAIL);
    }

    notifyHandle = ti_sdo_ipc_Notify_create(
            NotifyDriverShm_Handle_upCast(shmDrvHandle), remoteProcId, 0,
            NULL, &eb);

    if (notifyHandle == NULL) {
        NotifyDriverShm_delete(&shmDrvHandle);
        status = Notify_E_FAIL;
    }

    return (status);
}


/*!
 *  ======== NotifySetup_sharedMemReq ========
 */
SizeT NotifySetup_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr)
{
    SizeT memReq;
    NotifyDriverShm_Params notifyShmParams;

    NotifyDriverShm_Params_init(&notifyShmParams);
    notifyShmParams.sharedAddr = sharedAddr;
    /* Disable cache for inter-ducati NotifyDriverShm instances */
    if ((MultiProc_self() == NotifySetup_vpssProcId &&
         remoteProcId == NotifySetup_videoProcId) ||
        (MultiProc_self() == NotifySetup_videoProcId &&
        remoteProcId == NotifySetup_vpssProcId)) {
        notifyShmParams.cacheEnabled = FALSE;
        notifyShmParams.cacheLineSize = 0;
    }

    memReq = NotifyDriverShm_sharedMemReq(&notifyShmParams);

    return (memReq);
}

/*!
 * ======== NotifySetup_numIntLines ========
 */
UInt16 NotifySetup_numIntLines(UInt16 remoteProcId)
{
    return (1);
}
