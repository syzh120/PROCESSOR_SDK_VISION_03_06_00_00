/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  @file       MultiProcQ.c
 *
 *  @brief      MultiProc Linux implementation
 */

/* Standard IPC header */
#include <ti/ipc/Std.h>

/* Module level headers */
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <ladclient.h>
#include <_lad.h>

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
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    assert (cfg != NULL);

    handle = LAD_findHandle();

    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1("MultiProc_getConfig: can't find connection to daemon "
                "for pid %d\n", getpid())
        return;
    }

    cmd.cmd = LAD_MULTIPROC_GETCONFIG;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MultiProc_getConfig: sending LAD command failed, "
                "status=%d\n", status)
        return;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("MultiProc_getConfig: no LAD response, status=%d\n",
                status)
        return;
    }
    status = rsp.multiprocGetConfig.status;

    PRINTVERBOSE2("MultiProc_getConfig: got LAD response for client %d, "
            "status=%d\n", handle, status)

    memcpy(cfg, &rsp.multiprocGetConfig.cfg, sizeof(*cfg));

    return;
}
