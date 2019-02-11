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
 *  ======== GateHWSpinlock.c ========
 */

/* Standard headers */
#include <ti/ipc/Std.h>

/* Utilities & OSAL headers */
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/GateMP.h>

#include <ti/syslink/inc/GateHWSpinlock.h>
#include <ti/syslink/inc/usr/Qnx/GateHWSpinlockDrv.h>
#include <ti/syslink/inc/GateHWSpinlockDrvDefs.h>
#include <ti/syslink/inc/_GateHWSpinlock.h>

#include <ti/syslink/utils/IGateProvider.h>

#include <ti/syslink/utils/GateMutex.h>

/* Module level headers */
#include <ti/syslink/utils/String.h>

#include <_IpcLog.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>


/* =============================================================================
 * Structures & Enums
 * =============================================================================
 */
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
GateHWSpinlock_Module_State _GateHWSpinlock_state =
{
    .vAddr                  = NULL,
    .gmHandle               = NULL,
    .cfg.numLocks           = 128,
    .cfg.baseAddr           = 0,
    .cfg.offset             = 0,
    .cfg.size               = 0,
    .numLocks               = 128u
};

static GateHWSpinlock_Module_State *Mod = &_GateHWSpinlock_state;

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
/*
 *  Function to start the GateHWSpinlock module.
 */
Int32 GateHWSpinlock_start(Void)
{
    Int32                 status = GateHWSpinlock_S_SUCCESS;
    UInt32                dst;

    GateHWSpinlock_getConfig(&Mod->cfg);

    /* map the hardware lock registers into the local address space */
    if (status == GateHWSpinlock_S_SUCCESS) {
        dst = (UInt32)mmap(NULL, Mod->cfg.size,
                            (PROT_READ | PROT_WRITE | PROT_NOCACHE),
                            (MAP_PHYS|MAP_SHARED), NOFD,
                            (off_t)Mod->cfg.baseAddr);

        if (dst == (UInt32)MAP_FAILED) {
            PRINTVERBOSE0("GateHWSpinlock_start: Memory map failed")
            status = GateHWSpinlock_E_OSFAILURE;
        }
        else {
            Mod->vAddr = (UInt32 *)(dst + Mod->cfg.offset);
            status = GateHWSpinlock_S_SUCCESS;
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
    if (Mod->vAddr != NULL) {
        munmap((void *)Mod->vAddr, Mod->cfg.size);
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
    volatile UInt32 *baseAddr = Mod->vAddr;
    IArg key;

    key = IGateProvider_enter(obj->localGate);

    /* if gate already entered, just return with current key */
    obj->nested++;
    if (obj->nested > 1) {
        return(key);
    }

    /* enter the spinlock */
    while (1) {
        /* read the spinlock, returns non-zero when we get it */
        if (baseAddr[obj->lockNum] == 0) {
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
    volatile UInt32 *baseAddr = Mod->vAddr;

    obj->nested--;

    /* release the spinlock if not nested */
    if (obj->nested == 0) {
        baseAddr[obj->lockNum] = 0;
    }

    IGateProvider_leave(obj->localGate, key);

    return GateHWSpinlock_S_SUCCESS;
}
