/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 *  ======== GateHWSpinlock.c ========
 */

/* Standard headers */
#include <ti/ipc/Std.h>

/* Utilities & OSAL headers */
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/GateMP.h>

#include <GateHWSpinlock.h>

#include <IGateProvider.h>

/*
 * TODO: does this belong in ti/ipc/Std.h? We should consider getting rid of
 *       error blocks from the GateMutex.h interface.
 */
typedef UInt32            Error_Block;
#include <GateMutex.h>

/* Socket Utils */
#include <_lad.h>
#include <ladclient.h>

/* Linux headers */
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <linux/ioctl.h>
#include <linux/hwspinlock_user.h>

/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */
/* GateHWSpinlock Module Local State */
typedef struct {
    Int32                           fd;         /* spinlock device handle */
    UInt32 *                        baseAddr;   /* base addr lock registers */
    GateMutex_Handle                gmHandle;   /* handle to gate mutex */
    Bool                            useHwlockDrv; /* use the hwspinlock driver */
} GateHWSpinlock_Module_State;

/* GateHWSpinlock instance object */
struct GateHWSpinlock_Object {
    IGateProvider_SuperObject; /* For inheritance from IGateProvider */
    UInt                        lockNum;
    UInt                        nested;
    IGateProvider_Handle        localGate;
    int                         token;  /* HWSpinlock token */
};


/* =============================================================================
 * Globals
 * =============================================================================
 */
GateHWSpinlock_Config _GateHWSpinlock_cfgParams;

static GateHWSpinlock_Module_State GateHWSpinlock_state =
{
    .fd = -1,
    .baseAddr = NULL,
    .gmHandle = NULL,
    .useHwlockDrv = false,
};

static GateHWSpinlock_Module_State *Mod = &GateHWSpinlock_state;

static GateHWSpinlock_Params GateHWSpinlock_defInstParams =
{
    .resourceId = 0,
    .openFlag   = FALSE,
    .regionId   = 0,
    .sharedAddr = NULL
};

/* traces in this file are controlled via _GateHWSpinlock_verbose */
Bool _GateHWSpinlock_verbose = FALSE;
#define verbose _GateHWSpinlock_verbose

/* =============================================================================
 * APIS
 * =============================================================================
 */
/* Function to get configuration address & sizes for the GateHWSpinlock module.
 *
 */
Void GateHWSpinlock_getConfig (GateHWSpinlock_Config * cfgParams)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    assert (cfgParams != NULL);

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE0(
          "GateHWSpinlock_getConfig: can't find connection to daemon for pid")
        PRINTVERBOSE1("%d\n", getpid())

        return;
    }

    cmd.cmd = LAD_GATEHWSPINLOCK_GETCONFIG;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateHWSpinlock_getConfig: sending LAD command failed, status=%d\n",
          status)
        return;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateHWSpinlock_getConfig: no LAD response, status=%d\n",
        status)
        return;
    }
    status = rsp.gateHWSpinlockGetConfig.status;

    PRINTVERBOSE2(
      "GateHWSpinlock_getConfig: got LAD response for client %d, status=%d\n",
      handle, status)

    memcpy(cfgParams, &rsp.gateHWSpinlockGetConfig.cfgParams,
        sizeof(*cfgParams));

    return;
}


/*
 *  Function to start the GateHWSpinlock module.
 */
Int32 GateHWSpinlock_start(Void)
{
    Int32               status = GateHWSpinlock_S_SUCCESS;
    UInt32              dst;
    int                 flags;

    /* Fall back to /dev/mem if hwspinlock_user driver is not supported */
    Mod->fd = open("/dev/hwspinlock", O_RDWR);
    if (Mod->fd < 0) {
        Mod->fd = open ("/dev/mem", O_RDWR | O_SYNC);
    }
    else {
        Mod->useHwlockDrv = true;
    }

    if (Mod->fd < 0){
        PRINTVERBOSE0("GateHWSpinlock_start: failed to open the spinlock device");
        status = GateHWSpinlock_E_OSFAILURE;
    }

    if (!Mod->useHwlockDrv) {
        /* make sure /dev/mem fd doesn't exist for 'fork() -> exec*()'ed child */
        flags = fcntl(Mod->fd, F_GETFD);
        if (flags != -1) {
            fcntl(Mod->fd, F_SETFD, flags | FD_CLOEXEC);
        }

        /* map the hardware lock registers into the local address space */
        if (status == GateHWSpinlock_S_SUCCESS) {
            dst = (UInt32)mmap(NULL, _GateHWSpinlock_cfgParams.size,
                               (PROT_READ | PROT_WRITE),
                               (MAP_SHARED), Mod->fd,
                               (off_t)_GateHWSpinlock_cfgParams.baseAddr);

            if (dst == (UInt32)MAP_FAILED) {
                PRINTVERBOSE0("GateHWSpinlock_start: Memory map failed")
                    status = GateHWSpinlock_E_OSFAILURE;
                close(Mod->fd);
                Mod->fd = -1;
            }
            else {
                Mod->baseAddr = (UInt32 *)(dst + _GateHWSpinlock_cfgParams.offset);
                status = GateHWSpinlock_S_SUCCESS;
            }
        }
    }

    /* create GateMutex for local protection*/
    if (status == GateHWSpinlock_S_SUCCESS) {
        Mod->gmHandle = GateMutex_create(NULL, NULL);

        if (Mod->gmHandle == NULL) {
            PRINTVERBOSE0("GateHWSpinlock_start: GateMutex create failed")
            status = GateHWSpinlock_E_FAIL;
            GateHWSpinlock_stop();
        }
    }

    return (status);
}

/*
 *  Function to stop the GateHWSpinlock module.
 */
Int GateHWSpinlock_stop(Void)
{
    Int32               status = GateHWSpinlock_S_SUCCESS;

    /* delete GateMutex */
    if (Mod->gmHandle != NULL) {
        status = GateMutex_delete(&Mod->gmHandle);
    }

    /* release lock register mapping */
    if (!Mod->useHwlockDrv && (Mod->baseAddr != NULL)) {
        munmap((void *)_GateHWSpinlock_cfgParams.baseAddr,
           _GateHWSpinlock_cfgParams.size);
    }

    /* close the spinlock device file */
    if (Mod->fd >= 0) {
        close(Mod->fd);
        Mod->fd = -1;
    }

    return(status);
}

/*
 *  Initialize parameter structure
 */
Void GateHWSpinlock_Params_init(GateHWSpinlock_Params *params)
{
    assert(params != NULL);

    memcpy(params, &GateHWSpinlock_defInstParams,
        sizeof(GateHWSpinlock_Params));
}

/*
 * Create a GateHWSpinlock instance
 */
/* TODO: change the function to accept a local gate. Do this on all platforms */
GateHWSpinlock_Handle GateHWSpinlock_create(GateHWSpinlock_LocalProtect
    localProtect, const GateHWSpinlock_Params * params)
{
    GateHWSpinlock_Object * obj = (GateHWSpinlock_Object *)calloc(1,
        sizeof (GateHWSpinlock_Object));

    if (!obj) {
        PRINTVERBOSE0("GateHWSpinlock_create: memory allocation failure")
        return NULL;
    }

    IGateProvider_ObjectInitializer(obj, GateHWSpinlock);
    /* TODO: handle more local protection types */
    obj->localGate = (IGateProvider_Handle)Mod->gmHandle;
    obj->lockNum = params->resourceId;
    obj->nested = 0;

    return (GateHWSpinlock_Handle)obj;
}

/*
 * Delete a GateHWSpinlock instance
 */
Int GateHWSpinlock_delete (GateHWSpinlock_Handle * handle)
{
    GateHWSpinlock_Object * obj;
    Int  status = GateHWSpinlock_S_SUCCESS;

    if (handle == NULL) {
        return GateHWSpinlock_E_INVALIDARG;
    }
    if (*handle == NULL) {
        return GateHWSpinlock_E_INVALIDARG;
    }

    obj = (GateHWSpinlock_Object *)(*handle);

    free(obj);
    *handle = NULL;

    return (status);
}

/*
 *  Enter a GateHWSpinlock instance
 */
IArg GateHWSpinlock_enter(GateHWSpinlock_Object *obj)
{
    volatile UInt32 *baseAddr = Mod->baseAddr;
    struct hwspinlock_user_lock data = {
        .id = obj->lockNum,
        .timeout = 10,
    };
    IArg key;
    Bool locked;

    key = IGateProvider_enter(obj->localGate);

    /* if gate already entered, just return with current key */
    obj->nested++;
    if (obj->nested > 1) {
        return(key);
    }

    /* enter the spinlock */
    while (1) {
        if (Mod->useHwlockDrv) {
            locked = !ioctl(Mod->fd, HWSPINLOCK_USER_LOCK, &data);
        }
        else {
            /* read the spinlock, returns non-zero when we get it */
            locked = (baseAddr[obj->lockNum] == 0);
        }

        if (locked) {
            break;
        }

        obj->nested--;
        IGateProvider_leave(obj->localGate, key);
        key = IGateProvider_enter(obj->localGate);
        obj->nested++; /* re-nest the gate */
    }

    return (key);
}

/*
 *  Leave a GateHWSpinlock instance
 */
Int GateHWSpinlock_leave(GateHWSpinlock_Object *obj, IArg key)
{
    volatile UInt32 *baseAddr = Mod->baseAddr;
    struct hwspinlock_user_unlock data = {
        .id = obj->lockNum,
    };

    obj->nested--;

    /* release the spinlock if not nested */
    if (obj->nested == 0) {
        if (Mod->useHwlockDrv) {
            ioctl(Mod->fd, HWSPINLOCK_USER_UNLOCK, &data);
        }
        else {
            baseAddr[obj->lockNum] = 0;
        }
    }

    IGateProvider_leave(obj->localGate, key);

    return GateHWSpinlock_S_SUCCESS;
}
