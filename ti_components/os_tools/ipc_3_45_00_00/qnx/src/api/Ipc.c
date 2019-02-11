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
/*!
 *  @file       Ipc.c
 *
 *  @brief      Starts and stops user side Ipc
 *              All setup/destroy APIs on user side will be call from this
 *              module.
 *
 *  @ver        0002
 *
 */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ti/ipc/Std.h>

/* Common IPC headers: */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/NameServer.h>

/* User side headers */
#include <ti/syslink/inc/usr/Qnx/IpcDrv.h>

/* IPC startup/shutdown stuff: */
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/NameServer.h>
#include <_MessageQ.h>
#include <_NameServer.h>
#include <_GateMP.h>
#include <_GateMP_usr.h>
#include <_TiIpcFxns.h>
#include <_IpcLog.h>
#include <ti/syslink/inc/_GateHWSpinlock.h>
#include <ti/syslink/inc/_MultiProc.h>

MultiProc_Config _MultiProc_cfg;

/* traces in this file are controlled via _Ipc_verbose */
Bool _Ipc_verbose = FALSE;
#define verbose _Ipc_verbose

static void cleanup(int arg);

/** ============================================================================
 *  Functions
 *  ============================================================================
 */
/* Function to start Ipc */
Int Ipc_start (Void)
{
    MessageQ_Config   msgqCfg;
    MultiProc_Config  mpCfg;
    Int32             status = Ipc_S_SUCCESS;
    UInt16            rprocId;

    /* Catch ctrl-C, and cleanup: */
    (void) signal(SIGINT, cleanup);

    if (getenv("IPC_DEBUG") != NULL) {
        /* turn on tracing */
        if (getenv("IPC_DEBUG")[0] == '1') {
            /* level 1 enables typical user API tracing */
            _Ipc_verbose = TRUE;
            _MessageQ_verbose = TRUE;
            _MultiProc_verbose = TRUE;
            _NameServer_verbose = TRUE;
#if defined(GATEMP_SUPPORT)
            _GateMP_verbose = TRUE;

            _GateHWSpinlock_verbose = TRUE;
#endif
        }
        else if ((getenv("IPC_DEBUG")[0] == '2') ||
                (getenv("IPC_DEBUG")[0] == '3')) {
            /* levels 2 and 3 add TiIpcFxns tracing */
            _Ipc_verbose = TRUE;
            _MessageQ_verbose = TRUE;
            _MultiProc_verbose = TRUE;
            _NameServer_verbose = TRUE;

#if defined(GATEMP_SUPPORT)
            _GateMP_verbose = TRUE;

            _GateHWSpinlock_verbose = TRUE;
#endif

            _TiIpcFxns_verbose = TRUE;
        }
    }

    status = IpcDrv_open();
    if (status < 0) {
        printf("Ipc_start: IpcDrv_open() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    status = NameServer_setup();
    if (status >= 0) {
        MessageQ_getConfig(&msgqCfg);
        MessageQ_setup(&msgqCfg);

        /* Setup and get MultiProc configuration from resource manager */
        MultiProc_getConfig(&mpCfg);
        _MultiProc_cfg = mpCfg;

        /* Now attach to all remote processors, assuming they are up. */
        for (rprocId = 0;
             (rprocId < MultiProc_getNumProcessors()) && (status >= 0);
             rprocId++) {
           if (0 == rprocId) {
               /* Skip host, which should always be 0th entry. */
               continue;
           }
           status = MessageQ_attach (rprocId, NULL);
           if (status < 0) {
              printf("Ipc_start: MessageQ_attach(%d) failed: %d\n",
                     rprocId, status);
              status = Ipc_E_FAIL;
              goto messageqattach_fail;
           }
        }

        /*
         * Check if MultiProc config is valid and that
         * MultiProc_getNumProcessors() is non-zero to make sure we are not
         * in the middle of a recovery.
         */
        if (rprocId == 0) {
            PRINTVERBOSE0("Ipc_start: MultiProc not yet configured\n")
            status = Ipc_E_FAIL;
            goto messageqattach_fail;
        }
    }
    else {
        printf("Ipc_start: NameServer_setup() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto nameserversetup_fail;
    }

    /* Start GateMP only if it is setup in the resource manager */
#if defined(GATEMP_SUPPORT)
    if (GateMP_isSetup()) {
        /* Get GateHWSpinlock configuration from resource manager */
        status = GateHWSpinlock_start();
        if (status < 0) {
            printf("Ipc_start: GateHWSpinlock_start failed: %d\n",
                status);
            status = Ipc_E_FAIL;
            goto gatehwspinlockstart_fail;
        }
        else {
            status = GateMP_start();
            if (status < 0) {
                printf("Ipc_start: GateMP_start failed: %d\n",
                status);
                status = Ipc_E_FAIL;
                goto gatempstart_fail;
            }
        }
    }
#endif
    /* Success */
    goto exit;
#if defined(GATEMP_SUPPORT)
gatempstart_fail:
    GateHWSpinlock_stop();
gatehwspinlockstart_fail:
    for (rprocId = rprocId - 1; (rprocId > 0) && (status >= 0); rprocId--) {
       MessageQ_detach(rprocId);
    }
#endif
messageqattach_fail:
    MessageQ_destroy();
    NameServer_destroy();
nameserversetup_fail:
    IpcDrv_close();

exit:
    return (status);
}


/* Function to stop Ipc */
Int Ipc_stop (Void)
{
    Int32             status = Ipc_S_SUCCESS;
    UInt16            rprocId;
#if defined(GATEMP_SUPPORT)
    if (GateMP_isSetup()) {
        /* Stop GateMP */
        status = GateMP_stop();
        if (status < 0) {
            printf("Ipc_stop: GateMP_stop() failed: %d\n", status);
            status = Ipc_E_FAIL;
            goto exit;
        }

        /* Finalize GateHWSpinlock */
        status = GateHWSpinlock_stop();
        if (status < 0) {
            printf("Ipc_stop: GateHWSpinlock_stop() failed: %d\n", status);
            status = Ipc_E_FAIL;
            goto exit;
        }
    }
#endif
    /* Now detach from all remote processors, assuming they are up. */
    for (rprocId = 0;
         (rprocId < MultiProc_getNumProcessors()) && (status >= 0);
         rprocId++) {
       if (0 == rprocId) {
          /* Skip host, which should always be 0th entry. */
          continue;
       }
       status = MessageQ_detach(rprocId);
       if (status < 0) {
            printf("Ipc_stop: MessageQ_detach(%d) failed: %d\n",
                 rprocId, status);
            status = Ipc_E_FAIL;
            goto exit;
       }
    }

    status = MessageQ_destroy();
    if (status < 0) {
        printf("Ipc_stop: MessageQ_destroy() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    status = NameServer_destroy();
    if (status < 0) {
        printf("Ipc_stop: NameServer_destroy() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    IpcDrv_close();

exit:
    return (status);
}

static void cleanup(int arg)
{
    printf("Ipc: Caught SIGINT, calling Ipc_stop...\n");
    Ipc_stop();
    exit(0);
}
