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
 *  @file   MultiProc.c
 *
 *  @brief  MultiProc module "client" implementation
 */

/* Standard IPC header */
#include <ti/ipc/Std.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/inc/_MultiProc.h>
#include <_IpcLog.h>
#include <ti/syslink/inc/MultiProcDrvDefs.h>

/* Socket Headers */
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <ti/syslink/inc/usr/Qnx/MultiProcDrv.h>

/* traces in this file are controlled via _MultiProc_verbose */
Bool _MultiProc_verbose = FALSE;
#define verbose _MultiProc_verbose

/* =============================================================================
 * APIS
 * =============================================================================
 */
/* Function to get default configuration for the MultiProc module.
 *
 */
Void MultiProc_getConfig (MultiProc_Config * cfg)
{
    Int status;
    MultiProcDrv_CmdArgs cmdArgs;

    assert (cfg != NULL);

    cmdArgs.args.getConfig.config = cfg;
    status = MultiProcDrv_ioctl (CMD_MULTIPROC_GETCONFIG, &cmdArgs);

    if (status < 0) {
        PRINTVERBOSE1("MultiProc_getConfig: API (through IOCTL) failed, \
            status=%d\n", status)
    }

    return;
}
