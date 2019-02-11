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
 *  ======== NotifyMbxSetup.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>

#include <ti/sdo/ipc/family/ti81xx/NotifyDriverMbx.h>
#include <ti/sdo/ipc/_Notify.h>

#include "package/internal/NotifyMbxSetup.xdc.h"

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

/*!
 *  ======== NotifyMbxSetup_attach ========
 */
Int NotifyMbxSetup_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    NotifyDriverMbx_Params mbxDrvParams;
    NotifyDriverMbx_Handle mbxDrvHandle;
    ti_sdo_ipc_Notify_Handle notifyHandle;
    Int status = Notify_S_SUCCESS;
    Error_Block eb;

    Error_init(&eb);

    NotifyDriverMbx_Params_init(&mbxDrvParams);
    mbxDrvParams.remoteProcId = remoteProcId;
    mbxDrvHandle = NotifyDriverMbx_create(&mbxDrvParams, &eb);
    if (mbxDrvHandle == NULL) {
        return (Notify_E_FAIL);
    }

    notifyHandle = ti_sdo_ipc_Notify_create(
            NotifyDriverMbx_Handle_upCast(mbxDrvHandle), remoteProcId, 0,
            NULL, &eb);
    if (notifyHandle == NULL) {
        NotifyDriverMbx_delete(&mbxDrvHandle);
        status = Notify_E_FAIL;
    }

    return (status);
}


/*!
 *  ======== NotifyMbxSetup_sharedMemReq ========
 */
SizeT NotifyMbxSetup_sharedMemReq(UInt16 remoteProcId, Ptr sharedAddr)
{
    return (0);
}

/*!
 * ======== NotifyMbxSetup_numIntLines ========
 */
UInt16 NotifyMbxSetup_numIntLines(UInt16 remoteProcId)
{
    return (1);
}
