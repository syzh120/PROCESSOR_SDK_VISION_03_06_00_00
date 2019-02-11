/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  ======== GatePeterson.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include <ti/sysbios/hal/Cache.h>

#include "package/internal/GatePeterson.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GatePeterson_Instance_init ========
 */
Int GatePeterson_Instance_init(GatePeterson_Object *obj,
                               IGateProvider_Handle localGate,
                               const GatePeterson_Params *params,
                               Error_Block *eb)
{
    Assert_isTrue(params->sharedAddr != NULL, ti_sdo_ipc_Ipc_A_invParam);
    Assert_isTrue(GatePeterson_numInstances != 0, ti_sdo_ipc_Ipc_A_invParam);

    obj->localGate      = localGate;
    obj->cacheEnabled   = SharedRegion_isCacheEnabled(params->regionId);
    obj->cacheLineSize  = SharedRegion_getCacheLineSize(params->regionId);

    /* Settings for both the creator and opener */
    if (obj->cacheLineSize > sizeof(GatePeterson_Attrs)) {
        obj->attrs   = params->sharedAddr;
        obj->flag[0] = (Bits16 *)((UArg)(obj->attrs) + obj->cacheLineSize);
        obj->flag[1] = (Bits16 *)((UArg)(obj->flag[0]) + obj->cacheLineSize);
        obj->turn    = (Bits16 *)((UArg)(obj->flag[1]) + obj->cacheLineSize);
    }
    else {
        obj->attrs   = params->sharedAddr;
        obj->flag[0] = (Bits16 *)((UArg)(obj->attrs) +
                        sizeof(GatePeterson_Attrs));
        obj->flag[1] = (Bits16 *)((UArg)(obj->flag[0]) + sizeof(Bits16));
        obj->turn    = (Bits16 *)((UArg)(obj->flag[1]) + sizeof(Bits16));
    }
    obj->nested  = 0;

    if (!params->openFlag) {
        /* Creating. */
        obj->selfId = 0;
        obj->otherId = 1;
        obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
        GatePeterson_postInit(obj);
    }
    else {
        /* Opening. */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;

        Cache_inv((Ptr)obj->attrs, sizeof(GatePeterson_Attrs), Cache_Type_ALL,
                  TRUE);

        if (obj->attrs->creatorProcId == MultiProc_self()) {
            /* Opening locally */
            obj->selfId         = 0;
            obj->otherId        = 1;
        }
        else {
            /* Trying to open a gate remotely */
            obj->selfId         = 1;
            obj->otherId        = 0;
            if (obj->attrs->openerProcId == MultiProc_INVALIDID) {
                /* Opening remotely for the first time */
                obj->attrs->openerProcId    = MultiProc_self();
            }
            else if (obj->attrs->openerProcId != MultiProc_self()) {
                Error_raise(eb, GatePeterson_E_gateRemotelyOpened,
                            obj->attrs->creatorProcId,
                            obj->attrs->openerProcId);
            }

            if (obj->cacheEnabled) {
                Cache_wbInv((Ptr)obj->attrs, sizeof(GatePeterson_Attrs),
                            Cache_Type_ALL, TRUE);
            }
        }
    }

    return (0);
}

/*
 *  ======== GatePeterson_Instance_finalize ========
 */
Void GatePeterson_Instance_finalize(GatePeterson_Object *obj, Int status)
{
    if (!status) {
        /* Modify shared memory */
        if (obj->objType == ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
            obj->attrs->openerProcId = MultiProc_INVALIDID;
            Cache_wbInv(obj->attrs, sizeof(GatePeterson_Attrs), Cache_Type_ALL,
                        TRUE);
        }
    }
}

/*
 *  ======== GatePeterson_enter ========
 */
IArg GatePeterson_enter(GatePeterson_Object *obj)
{
    IArg key;

    /* Enter local gate */
    key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the key */
    obj->nested++;
    if (obj->nested > 1) {
        return (key);
    }

    /* Indicate that we need to use the resource. */
    *(obj->flag[obj->selfId]) = GatePeterson_BUSY ;
    if (obj->cacheEnabled) {
        Cache_wbInv((Ptr)obj->flag[obj->selfId], obj->cacheLineSize,
            Cache_Type_ALL, TRUE);
    }

    /* Give away the turn. */
    *(obj->turn) = obj->otherId;

    if (obj->cacheEnabled) {
        Cache_wbInv((Ptr)obj->turn, obj->cacheLineSize, Cache_Type_ALL, TRUE);
        Cache_inv((Ptr)obj->flag[obj->otherId], obj->cacheLineSize,
            Cache_Type_ALL, TRUE);
    }

    /* Wait while other process is using the resource and has the turn. */
    while ((*(obj->flag[obj->otherId]) == GatePeterson_BUSY) &&
        (*(obj->turn) == obj->otherId)) {
        if (obj->cacheEnabled) {
            Cache_inv((Ptr)obj->flag[obj->otherId], obj->cacheLineSize,
                Cache_Type_ALL, FALSE);
            Cache_inv((Ptr)obj->turn, obj->cacheLineSize, Cache_Type_ALL, TRUE);
        }
    }

    return (key);
}

/*
 *  ======== GatePeterson_leave ========
 */
Void GatePeterson_leave(GatePeterson_Object *obj, IArg key)
{
    /* Release the resource and leave system gate. */
    obj->nested--;
    if (obj->nested == 0) {
        *(obj->flag[obj->selfId]) = GatePeterson_FREE;
        if (obj->cacheEnabled) {
            Cache_wbInv((Ptr)obj->flag[obj->selfId], obj->cacheLineSize,
                Cache_Type_ALL, TRUE);
        }
    }

    /* Leave local gate */
    IGateProvider_leave(obj->localGate, key);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== GatePeterson_getReservedMask ========
 */
Bits32 *GatePeterson_getReservedMask()
{
    /* This gate doesn't allow reserving resources */
    return (NULL);
}

/*
 *  ======== GatePeterson_sharedMemReq ========
 */
SizeT GatePeterson_sharedMemReq(const IGateMPSupport_Params *params)
{
    SizeT memReq;

    if (SharedRegion_getCacheLineSize(params->regionId) >=
        sizeof(GatePeterson_Attrs)) {
        /*! 4 Because shared of shared memory usage (see GatePeterson.xdc) */
        memReq = 4 * SharedRegion_getCacheLineSize(params->regionId);
    }
    else {
        memReq = sizeof(GatePeterson_Attrs) + sizeof(Bits16) * 3;
    }

    return(memReq);
}

/*
 *  ======== GatePeterson_query ========
 */
Bool GatePeterson_query(Int qual)
{
    Bool rc;

    switch (qual) {
        case IGateProvider_Q_BLOCKING:
            /* GatePeterson is never blocking */
            rc = FALSE;
            break;
        case IGateProvider_Q_PREEMPTING:
            /* Depends on gate proxy? */
            rc = TRUE;
            break;
        default:
            rc = FALSE;
            break;
    }

    return (rc);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */
/*
 *  ======== GatePeterson_postInit ========
 *  Function to be called during
 *  1. module startup to complete the initialization of all static instances
 *  2. instance_init to complete the initialization of a dynamic instance
 *
 *  Main purpose is to set up shared memory
 */
Void GatePeterson_postInit(GatePeterson_Object *obj)
{
    /* Set up shared memory */
    *(obj->turn)       = 0;
    *(obj->flag[0])    = 0;
    *(obj->flag[1])    = 0;
    obj->attrs->creatorProcId  = MultiProc_self();
    obj->attrs->openerProcId   = MultiProc_INVALIDID;

    /*
     * Write everything back to memory. This assumes that obj->attrs is equal
     * to the shared memory base address
     */
    if (obj->cacheEnabled) {
        Cache_wbInv((Ptr)obj->attrs, sizeof(GatePeterson_Attrs), Cache_Type_ALL,
            FALSE);
        Cache_wbInv((Ptr)(obj->flag[0]), obj->cacheLineSize * 3, Cache_Type_ALL,
            TRUE);
    }
}
