/*
 * Copyright (c) 2012-2016 Texas Instruments Incorporated - http://www.ti.com
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
 */

/* standard headers */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/* package headers */
#include <ti/ipc/Std.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/NameServer.h>
#include <ti/ipc/heaps/HeapStd.h>
#include <ti/ipc/interfaces/IHeap.h>

/* User side headers */
#include <ladclient.h>

/* IPC startup/shutdown stuff: */
#include <ti/ipc/MultiProc.h>
#include <GateHWSpinlock.h>
#include <_GateMP.h>
#include <_Ipc.h>
#include <_MultiProc.h>
#include <_MessageQ.h>
#include <_NameServer.h>

/* module definition */
typedef struct {
    Int                         refCount;
    pthread_mutex_t             gate;
    Ipc_TransportFactoryFxns   *transportFactory;
    Ipc_Config                  config;
    Int                         attached[MultiProc_MAXPROCESSORS];
} Ipc_Module;

/* hack: rpmsgproto driver work around */
Void MessageQ_bind(UInt16 procId);
Void MessageQ_unbind(UInt16 procId);


/* =============================================================================
 *  Globals
 * =============================================================================
 */
static Ipc_Module Ipc_module = {
    .refCount           = 0,
#if defined(IPC_BUILDOS_ANDROID) && (PLATFORM_SDK_VERSION < 23)
    .gate               = PTHREAD_RECURSIVE_MUTEX_INITIALIZER,
#else
// only _NP (non-portable) type available in CG tools which we're using
    .gate               = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP,
#endif
    .transportFactory   = NULL,
    .config.procSync    = Ipc_ProcSync_NONE,
    .config.idHeapStd   = 0
};

GateHWSpinlock_Config _GateHWSpinlock_cfgParams;
static LAD_ClientHandle ladHandle;

/* traces in this file are controlled via _Ipc_verbose */
Bool _Ipc_verbose = FALSE;
#define verbose _Ipc_verbose

/** ============================================================================
 *  Functions
 *  ============================================================================
 */
static void cleanup(int arg);


/*
 *  ======== Ipc_start ========
 */
Int Ipc_start(Void)
{
    MessageQ_Config         msgqCfg;
    MultiProc_Config        mpCfg;
#if defined(GATEMP_SUPPORT)
    GateHWSpinlock_Config   gateHWCfg;
#endif
    Int         status;
    LAD_Status  ladStatus;
    UInt16      procId;
    UInt16      clusterSize;
    UInt16      baseId;
    UInt16      clusterId;
    Int         i;
    HeapStd_Handle heap;
    IHeap_Handle iheap;

    /* function must be serialized */
    pthread_mutex_lock(&Ipc_module.gate);

    /* ensure only first thread performs startup procedure */
    if (Ipc_module.refCount >= 1) {
        Ipc_module.refCount++;
        status = Ipc_S_ALREADYSETUP;
        goto exit;
    }

    /* make sure transport factory has been configured */
    if (Ipc_module.transportFactory == NULL) {
        status = Ipc_E_INVALIDSTATE;
        goto exit;
    }

    /* initialize module object */
    for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
        Ipc_module.attached[i] = 0;
    }

    /* Catch ctrl-C, and cleanup: */
    (void) signal(SIGINT, cleanup);

    if (getenv("IPC_DEBUG") != NULL) {
        /* turn on tracing */
        if (getenv("IPC_DEBUG")[0] == '1') {
            /* level 1 enables typical user API tracing */
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
            /* levels 2 and 3 add socket and LAD client tracing */
            _MessageQ_verbose = TRUE;
            _MultiProc_verbose = TRUE;
            _NameServer_verbose = TRUE;

#if defined(GATEMP_SUPPORT)
            _GateMP_verbose = TRUE;

            _GateHWSpinlock_verbose = TRUE;
#endif

            /* internals - should be declared in respective _*.h files */
            extern Bool _SocketFxns_verbose;
            extern Bool _LAD_Client_verbose;

            _SocketFxns_verbose = TRUE;
            _LAD_Client_verbose = TRUE;
        }
    }

    /* establish a communication link to the LAD daemon */
    ladStatus = LAD_connect(&ladHandle);

    if (ladStatus != LAD_SUCCESS) {
        fprintf(stderr, "Ipc_start: LAD_connect() failed: %d\n", ladStatus);
        status = Ipc_E_FAIL;
        goto exit;
    }

    /* get global configuration from LAD */
    Ipc_getConfig(&Ipc_module.config);

    /* get global configuration from LAD */
    MultiProc_getConfig(&mpCfg);
    _MultiProc_initCfg(&mpCfg);

    /* setup name server thread in LAD daemon */
    status = NameServer_setup();

    if (status < 0) {
        fprintf(stderr, "Ipc_start: NameServer_setup() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    /* get global configuration from LAD */
    MessageQ_getConfig(&msgqCfg);
    MessageQ_setup(&msgqCfg);

    /* register the standard heap */
    heap = HeapStd_handle();
    iheap = HeapStd_upCast(heap);
    MessageQ_registerHeap((Ptr)iheap, Ipc_module.config.idHeapStd);

    /* invoke the transport factory create method */
    status = Ipc_module.transportFactory->createFxn();

    if (status < 0) {
        goto exit;
    }

    /* if using ProcSync_ALL, then attach to all processors in the cluster */
    if (Ipc_module.config.procSync == Ipc_ProcSync_ALL) {
        clusterSize = MultiProc_getNumProcsInCluster();
        baseId = MultiProc_getBaseIdOfCluster();

        for (clusterId = 0; clusterId < clusterSize; clusterId++) {
            procId = baseId + clusterId;

            if (procId == MultiProc_self()) {
                continue;
            }

            status = Ipc_attach(procId);

            /*  For backward compatibility, it is okay for attach to fail.
             *  We don't expect all remote processors to be running.
             */
            if (status < 0) {
                status = 0;
                /* do nothing */
            }
        }
    }

    /* Start GateMP only if device has support */
#if defined(GATEMP_SUPPORT)
    if (GateMP_isSetup()) {
        /*
         * Get HWSpinlock base address and size from LAD and
         * initialize the local config structure.
         */
        GateHWSpinlock_getConfig(&gateHWCfg);
        _GateHWSpinlock_cfgParams = gateHWCfg;

        status = GateHWSpinlock_start();
        if (status < 0) {
            fprintf(stderr, "Ipc_start: GateHWSpinlock_start failed: %d\n",
                    status);
            status = Ipc_E_FAIL;
            goto exit;
        }

        status = GateMP_start();
        if (status < 0) {
            if (status == GateMP_E_NOTFOUND) {
                /* Ignore if Gate not found */
                PRINTVERBOSE1(
                    "Ipc_start: GateMP_start: gate not found, ignored %d\n",
                    status);
                status = 0;
            } else {
                fprintf(stderr, "Ipc_start: GateMP_start failed: %d\n", status);
                status = Ipc_E_FAIL;
                GateHWSpinlock_stop();
                goto exit;
            }
        }
    }
#endif

    /* getting here means we have successfully started */
    Ipc_module.refCount++;

exit:
    pthread_mutex_unlock(&Ipc_module.gate);

    return (status);
}

/*
 *  ======== Ipc_stop ========
 */
Int Ipc_stop(Void)
{
    Int32       status = Ipc_S_SUCCESS;
    LAD_Status  ladStatus;
    UInt16      procId;
    UInt16      clusterSize;
    UInt16      baseId;
    UInt16      clusterId;

    /* function must be serialized */
    pthread_mutex_lock(&Ipc_module.gate);

    if (Ipc_module.refCount == 0) {
        status = Ipc_E_INVALIDSTATE;
        goto exit;
    }

    /* ensure only last thread performs stop procedure */
    if (--Ipc_module.refCount > 0) {
        goto exit;
    }

    /* if using ProcSync_ALL, then detach from all processors in the cluster */
    if (Ipc_module.config.procSync == Ipc_ProcSync_ALL) {
        clusterSize = MultiProc_getNumProcsInCluster();
        baseId = MultiProc_getBaseIdOfCluster();

        for (clusterId = 0; clusterId < clusterSize; clusterId++) {
            procId = baseId + clusterId;

            if (MultiProc_self() == procId) {
                continue;
            }

            /*  For backward compatibility, we might not be attached to
             *  all cluster members. Skip unattached processors.
             */
            if (!Ipc_isAttached(procId)) {
                continue;
            }

            status = Ipc_detach(procId);

            if (status < 0) {
                /* Should we keep going or stop? */
            }
        }
    }

    Ipc_module.transportFactory->deleteFxn();

    /* unregister the standard heap */
    MessageQ_unregisterHeap(Ipc_module.config.idHeapStd);

    status = MessageQ_destroy();
    if (status < 0) {
        fprintf(stderr, "Ipc_stop: MessageQ_destroy() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    status = NameServer_destroy();
    if (status < 0) {
        fprintf(stderr, "Ipc_stop: NameServer_destroy() failed: %d\n", status);
        status = Ipc_E_FAIL;
        goto exit;
    }

    ladStatus = LAD_disconnect(ladHandle);
    if (ladStatus != LAD_SUCCESS) {
        fprintf(stderr, "LAD_disconnect() failed: %d\n", ladStatus);
        status = Ipc_E_FAIL;
        goto exit;
    }

exit:
    pthread_mutex_unlock(&Ipc_module.gate);

    return (status);
}

/*
 *  ======== Ipc_transportConfig ========
 */
Int Ipc_transportConfig(Ipc_TransportFactoryFxns *factory)
{
    Int status = Ipc_S_SUCCESS;

    pthread_mutex_lock(&Ipc_module.gate);

    /*  Only the first caller can actually set the transport factory.
     *  Subsequent callers (e.g. multi-threaded application) must be
     *  using the same factory. Otherwise, it is an error.
     */
    if (Ipc_module.transportFactory == NULL) {
        Ipc_module.transportFactory = factory;
    }
    else if (Ipc_module.transportFactory != factory) {
        status = Ipc_E_INVALIDARG;
        goto exit;
    }

exit:
    pthread_mutex_unlock(&Ipc_module.gate);

    return (status);
}

static void cleanup(int arg)
{
    printf("Ipc: Caught SIGINT, calling Ipc_stop...\n");
    Ipc_stop();
    exit(0);
}

/*
 *  ======== Ipc_attach ========
 */
Int Ipc_attach(UInt16 procId)
{
    Int status = Ipc_S_SUCCESS;
    UInt16 clusterId;
#if defined(GATEMP_SUPPORT)
    Int ret;
#endif

    /* cannot attach to yourself */
    if (MultiProc_self() == procId) {
        status =  Ipc_E_INVALIDARG;
        goto done;
    }

    /* processor must be a member of the cluster */
    clusterId = procId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_getNumProcsInCluster()) {
        status =  Ipc_E_INVALIDARG;
        goto done;
    }

    /* function must be serialized */
    pthread_mutex_lock(&Ipc_module.gate);

    /* if already attached, just increment reference count */
    if (Ipc_module.attached[clusterId] > 0) {
        Ipc_module.attached[clusterId]++;
        goto done;
    }

    /* establish name server connection to remote processor */
    status = NameServer_attach(procId);

    if (status < 0) {
        status = Ipc_E_FAIL;
        goto done;
    }

    /* attach the transport to remote processor */
    status = Ipc_module.transportFactory->attachFxn(procId);

    if (status < 0) {
        NameServer_detach(procId);
        status = Ipc_E_FAIL;
        goto done;
    }

    /* hack: bind all existing message queues to remote processor */
    MessageQ_bind(procId);

#if defined(GATEMP_SUPPORT)
    if (GateMP_isSetup()) {
        /* establish GateMP connection to remote processor */
        ret = GateMP_attach(procId);

        if (ret < 0) {
            PRINTVERBOSE1("Ipc_attach: failed to GateMP_attach to procId %d\n",
                          procId);
        }
    }
#endif

    /* getting here means we have successfully attached */
    Ipc_module.attached[clusterId]++;

done:
    pthread_mutex_unlock(&Ipc_module.gate);

    return (status);
}

/*
 *  ======== Ipc_detach ========
 */
Int Ipc_detach(UInt16 procId)
{
    Int status = Ipc_S_SUCCESS;
    UInt16 clusterId;
#if defined(GATEMP_SUPPORT)
    Int ret;
#endif

    /* cannot detach from yourself */
    if (MultiProc_self() == procId) {
        status =  Ipc_E_INVALIDARG;
        goto done;
    }

    /* processor must be a member of the cluster */
    clusterId = procId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_getNumProcsInCluster()) {
        status =  Ipc_E_INVALIDARG;
        goto done;
    }

    /* function must be serialized */
    pthread_mutex_lock(&Ipc_module.gate);

    if (Ipc_module.attached[clusterId] == 0) {
        status = Ipc_E_INVALIDSTATE;
        goto done;
    }

    if (--Ipc_module.attached[clusterId] > 0) {
        goto done;
    }

#if defined(GATEMP_SUPPORT)
    if (GateMP_isSetup()) {
        /* establish GateMP connection to remote processor */
        ret = GateMP_detach(procId);

        if (ret < 0) {
            PRINTVERBOSE1("Ipc_detach: failed to GateMP_detach from procId %d\n",
                          procId);
        }
    }
#endif

    /* hack: unbind all existing message queues from remote processor */
    MessageQ_unbind(procId);

    /* detach transport from remote processor */
    status = Ipc_module.transportFactory->detachFxn(procId);

    if (status < 0) {
        status = Ipc_E_FAIL;
        /* report the error */
        goto done;
    }

    /* remove connection to remote processor */
    status = NameServer_detach(procId);

    if (status < 0) {
        status = Ipc_E_FAIL;
        /* report the error */
        goto done;
    }

done:
    if (status < 0) {
        /* report error */
        fprintf(stderr, "Ipc_detach: Error %d, procId %d\n", status, procId);
    }
    pthread_mutex_unlock(&Ipc_module.gate);

    return (status);
}

/*
 *  ======== Ipc_isAttached ========
 */
Bool Ipc_isAttached(UInt16 procId)
{
    Bool attached;
    UInt16 clusterId;

    /* cannot be attached to yourself */
    if (MultiProc_self() == procId) {
        return (FALSE);
    }

    /* processor must be a member of the cluster */
    clusterId = procId - MultiProc_getBaseIdOfCluster();

    if (clusterId >= MultiProc_getNumProcsInCluster()) {
        return (FALSE);
    }

    attached = (Ipc_module.attached[clusterId] > 0 ? TRUE : FALSE);
    return (attached);
}

/*
 *  ======== Ipc_getConfig ========
 *  Get the run-time configuration for the Ipc module
 *
 *  This is an IPC internal function. It is used to acquire
 *  the global Ipc module configuration values from LAD.
 */
Void Ipc_getConfig(Ipc_Config *cfg)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE0("Ipc_getConfig: no connection to LAD\n");
        return;
    }

    cmd.cmd = LAD_IPC_GETCONFIG;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("Ipc_getConfig: sending LAD command failed, "
                "status=%d\n", status);
        return;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("Ipc_getConfig: no LAD response, status=%d\n", status);
        return;
    }

    memcpy(cfg, &rsp.ipcConfig, sizeof(Ipc_Config));
    return;
}
