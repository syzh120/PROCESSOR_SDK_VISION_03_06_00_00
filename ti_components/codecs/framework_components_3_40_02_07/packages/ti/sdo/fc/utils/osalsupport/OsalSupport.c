/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 */
/*
 *  ======== OsalSupport.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include <xdc/runtime/knl/GateThread.h>
#include <xdc/runtime/knl/GateProcess.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/knl/SemThread.h>
#include <xdc/runtime/knl/SemProcess.h>
#include <xdc/runtime/knl/ISemaphore.h>

#define CREATE_FAILURE 1

extern __FAR__ Bool ti_sdo_fc_multiProcess;

/*
 *  ======== OsalSupport_createGate ========
 */
IGateProvider_Handle OsalSupport_createGate(Int key)
{
    GateThread_Handle    gate;
    GateProcess_Handle   gateMP;
    GateThread_Params    gateParams;
    GateProcess_Params   gateMPParams;
    IGateProvider_Handle h = NULL;
    Error_Block eb;
    Error_init(&eb);


    if (ti_sdo_fc_multiProcess) {
        /* Need a valid key for process-safe gate */
        Assert_isTrue(key != -1, NULL);

        GateProcess_Params_init(&gateMPParams);
        gateMPParams.key = key;
        gateMP = GateProcess_create(&gateMPParams, &eb);

        if (Error_check(&eb)) {
                /* Error occurred, but there's not much we can do about it */
                Error_print(&eb);
        }

        h = GateProcess_Handle_upCast(gateMP);
    }
    else {
        GateThread_Params_init(&gateParams);
        gate = GateThread_create(&gateParams, NULL);

        h = GateThread_Handle_upCast(gate);
    }

    return (h);
}

/*
 *  ======== OsalSupport_deleteGate ========
 */
Void OsalSupport_deleteGate(IGateProvider_Handle h)
{
    GateThread_Handle  gate;
    GateProcess_Handle gateMP;

    if (ti_sdo_fc_multiProcess) {
        gateMP = GateProcess_Handle_downCast(h);
        GateProcess_delete(&gateMP);
    }
    else {
        gate = GateThread_Handle_downCast(h);
        GateThread_delete(&gate);
    }
}

/*
 *  ======== OsalSupport_createSem ========
 */
ISemaphore_Handle OsalSupport_createSem(Int count, Int key)
{
    SemThread_Handle    sem;
    SemProcess_Handle   semMP;
    SemThread_Params    semParams;
    SemProcess_Params   semMPParams;
    ISemaphore_Handle   h = NULL;

    if (ti_sdo_fc_multiProcess) {
        SemProcess_Params_init(&semMPParams);

        semMP = SemProcess_create(count, key, &semMPParams, NULL);

        if (semMP != NULL) {
            h = SemProcess_Handle_upCast(semMP);
        }
    }
    else {
        SemThread_Params_init(&semParams);
        sem = SemThread_create(count, &semParams, NULL);

        if (sem != NULL) {
            h = SemThread_Handle_upCast(sem);
        }
    }

    return (h);
}

/*
 *  ======== OsalSupport_deleteSem ========
 */
Void OsalSupport_deleteSem(ISemaphore_Handle h)
{
    SemThread_Handle  sem;
    SemProcess_Handle semMP;

    if (ti_sdo_fc_multiProcess) {
        semMP = SemProcess_Handle_downCast(h);
        SemProcess_delete(&semMP);
    }
    else {
        sem = SemThread_Handle_downCast(h);
        SemThread_delete(&sem);
    }
}
