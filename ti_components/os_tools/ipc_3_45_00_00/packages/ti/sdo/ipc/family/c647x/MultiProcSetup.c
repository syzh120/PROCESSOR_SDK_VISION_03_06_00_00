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
 *  ======== MultiProcSetup.c ========
 */

#include <xdc/std.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/family/c647x/Interrupt.h>
#include <xdc/runtime/Assert.h>

#include "package/internal/MultiProcSetup.xdc.h"

/*!
 *  ======== MultiProcSetup_init ========
 */
Void MultiProcSetup_init()
{
    extern cregister volatile UInt DNUM;
    UInt16 procId;

    /* Skip if the procId has already been set */
    if (MultiProc_self() != MultiProc_INVALIDID) {
        return;
    }

    procId = MultiProcSetup_getProcId(DNUM);

    /*
     *  Assert that image is being loaded onto a core that was included in the
     *  MultiProc name list (via setConfig)
     */
    Assert_isTrue(procId != MultiProc_INVALIDID,
            MultiProcSetup_A_invalidProcessor);

    /* Set the local ID */
    MultiProc_setLocalId(procId);
}


/*
 *  ======== MultiProcSetup_getProcId ========
 */
UInt16 MultiProcSetup_getProcId(UInt coreId)
{
    UInt i;
    for (i = 0; i < ti_sdo_utils_MultiProc_numProcessors; i++) {
        if (MultiProcSetup_procMap[i] == coreId) {
            return (i);
        }
    }

    return (MultiProc_INVALIDID);
}
