/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 *  ======== GateHWSpinlock_client.c ========
 */

/* Standard headers */
#include <ti/ipc/Std.h>

#include <ti/syslink/inc/GateHWSpinlock.h>
#include <ti/syslink/inc/_GateHWSpinlock.h>
#include <ti/syslink/inc/usr/Qnx/GateHWSpinlockDrv.h>
#include <ti/syslink/inc/GateHWSpinlockDrvDefs.h>

#include <_IpcLog.h>
#include <assert.h>

/* traces in this file are controlled via _GateHWSpinlock_verbose */
#define verbose _GateHWSpinlock_verbose

/* =============================================================================
 * APIS
 * =============================================================================
 */
/*
 * Function to get configuration address & sizes for the GateHWSpinlock module.
 */
Void GateHWSpinlock_getConfig(GateHWSpinlock_Config * cfg)
{
    Int status;
    GateHWSpinlockDrv_CmdArgs cmdArgs;

    assert (cfg != NULL);

    cmdArgs.args.getConfig.config = cfg;
    status = GateHWSpinlockDrv_ioctl(CMD_GATEHWSPINLOCK_GETCONFIG, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("GateHWSpinlock_getConfig: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return;
}
