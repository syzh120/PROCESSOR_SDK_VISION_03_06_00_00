/*
 * Copyright (c) 2013-2014 Texas Instruments Incorporated
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
 *  ======== GatePetersonN.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include <ti/sysbios/hal/Cache.h>

#include "package/internal/GatePetersonN.xdc.h"

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_SharedRegion.h>

#define ROUND_UP(a, b) (SizeT)((((UInt32) a) + ((b) - 1)) & ~((b) - 1))

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GatePetersonN_Instance_init ========
 */
Int GatePetersonN_Instance_init(GatePetersonN_Object *obj,
                               IGateProvider_Handle localGate,
                               const GatePetersonN_Params *params,
                               Error_Block *eb)
{
    SizeT  offset;
    SizeT  minAlign = Memory_getMaxDefaultTypeAlign();
    SizeT  i;

    if (SharedRegion_getCacheLineSize(params->regionId) > minAlign) {
            minAlign = SharedRegion_getCacheLineSize(params->regionId);
    }

    Assert_isTrue(params->sharedAddr != NULL, ti_sdo_ipc_Ipc_A_invParam);
    Assert_isTrue(GatePetersonN_numInstances != 0, ti_sdo_ipc_Ipc_A_invParam);

    obj->localGate      = localGate;
    obj->cacheEnabled   = SharedRegion_isCacheEnabled(params->regionId);
    obj->cacheLineSize  = SharedRegion_getCacheLineSize(params->regionId);
    obj->nested  = 0;

    /* This is not cluster aware:
     * obj->numProcessors  = MultiProc_getNumProcessors();
     * obj->selfId         = MultiProc_self();
     */

    /* Cluster aware initialization */
    obj->numProcessors  = MultiProc_getNumProcsInCluster();

    /* set selfId to 0-based offset within cluster. */
    obj->selfId         = MultiProc_self() - MultiProc_getBaseIdOfCluster();

    /* Assign shared memory addresses for the protocol state variables */

    offset = 0;

    for (i=0; i < obj->numProcessors; i++) {
        obj->enteredStage[i] = (Int32 *)((UArg)(params->sharedAddr) + offset);
        offset += minAlign;
    }

    for (i=0; i < obj->numProcessors - 1; i++) {
	obj->lastProcEnteringStage[i] = (Int32 *)((UArg)(params->sharedAddr)
                                                   + offset);
        offset += minAlign;
    }

    if (!params->openFlag) {
        /* Creating. */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
        GatePetersonN_postInit(obj);
    }
    else {
        /* Opening. */
        obj->objType = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;
    }

    return (0);
}

/*
 *  ======== GatePetersonN_Instance_finalize ========
 */
Void GatePetersonN_Instance_finalize(GatePetersonN_Object *obj, Int status)
{
}

/*
 *  ======== GatePetersonN_enter ========
 */
IArg GatePetersonN_enter(GatePetersonN_Object *obj)
{
    IArg key;
    SizeT   numProcessors;
    SizeT   myProcId;
    Int32   curStage;
    SizeT   proc;

    /* Enter local gate */
    key = IGateProvider_enter(obj->localGate);

    /* If the gate object has already been entered, return the key */
    obj->nested++;
    if (obj->nested > 1) {
        return (key);
    }
    numProcessors = obj->numProcessors;
    myProcId      = obj->selfId;

    for (curStage=0; curStage < (numProcessors - 1); curStage++) {

        *(obj->enteredStage[myProcId]) = curStage;
        *(obj->lastProcEnteringStage[curStage]) = myProcId;

	if (obj->cacheEnabled) {

            Cache_wbInv((Ptr)obj->enteredStage[myProcId], obj->cacheLineSize,
                    Cache_Type_ALL, FALSE);
            Cache_wbInv((Ptr)obj->lastProcEnteringStage[curStage],
                    obj->cacheLineSize, Cache_Type_ALL, TRUE);
        }

        for (proc=0; proc < numProcessors; proc++) {

            if (proc != myProcId) {

	        if (obj->cacheEnabled) {

                    Cache_inv((Ptr)obj->enteredStage[proc],
                            obj->cacheLineSize, Cache_Type_ALL, FALSE);
                    Cache_inv((Ptr)obj->lastProcEnteringStage[curStage],
                            obj->cacheLineSize, Cache_Type_ALL, TRUE);
		}

                while ((*(obj->enteredStage[proc]) >= curStage) &&
                       (*(obj->lastProcEnteringStage[curStage]) == myProcId)) {

                    /* wait till 'proc' leaves or another 'proc' enters stage */
	            if (obj->cacheEnabled) {

                        Cache_inv((Ptr)obj->enteredStage[proc],
                                obj->cacheLineSize, Cache_Type_ALL, FALSE);
                        Cache_inv((Ptr)obj->lastProcEnteringStage[curStage],
                                obj->cacheLineSize, Cache_Type_ALL, TRUE);
                    }
                }
            }
        }

    } /* stages */

    return (key);
}

/*
 *  ======== GatePetersonN_leave ========
 */
Void GatePetersonN_leave(GatePetersonN_Object *obj, IArg key)
{
    /* Release the resource and leave system gate. */
    obj->nested--;
    if (obj->nested == 0) {

        *(obj->enteredStage[obj->selfId]) = GatePetersonN_NOT_INTERESTED;

        if (obj->cacheEnabled) {
            Cache_wbInv((Ptr)obj->enteredStage[obj->selfId], obj->cacheLineSize,
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
 *  ======== GatePetersonN_getReservedMask ========
 */
Bits32 *GatePetersonN_getReservedMask()
{
    /* This gate doesn't allow reserving resources */
    return (NULL);
}

/*
 *  ======== GatePetersonN_sharedMemReq ========
 */
SizeT GatePetersonN_sharedMemReq(const IGateMPSupport_Params *params)
{
    SizeT  memReq;
    UInt16 numProcessors = MultiProc_getNumProcsInCluster(); /* Cluster aware */
    SizeT  minAlign = Memory_getMaxDefaultTypeAlign();

    if (SharedRegion_getCacheLineSize(params->regionId) > minAlign) {
            minAlign = SharedRegion_getCacheLineSize(params->regionId);
    }

    /*  Allocate aligned memory for shared state variables used in protocol
     *      enteredStage[NUM_PROCESSORS]
     *	    lastProcEnteringStage[NUM_STAGES]
     */
    memReq = ((2 * numProcessors) - 1) *
              SharedRegion_getCacheLineSize(params->regionId);

    return(memReq);
}

/*
 *  ======== GatePetersonN_query ========
 */
Bool GatePetersonN_query(Int qual)
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
 *  ======== GatePetersonN_postInit ========
 *  Function to be called during
 *  1. module startup to complete the initialization of all static instances
 *  2. instance_init to complete the initialization of a dynamic instance
 *
 *  Main purpose is to set up shared memory
 */
Void GatePetersonN_postInit(GatePetersonN_Object *obj)
{
    UInt16 i;

    /* Set up shared memory */
    for (i=0; i < obj->numProcessors; i++) {
        *(obj->enteredStage[i]) = GatePetersonN_NOT_INTERESTED;
    }

    for (i=0; i < obj->numProcessors - 1; i++) {
	*(obj->lastProcEnteringStage[i]) = 0;
    }

    /*
     * Write everything back to shared memory.
     */
    if (obj->cacheEnabled) {
        Cache_wbInv((Ptr)(obj->enteredStage[0]), obj->cacheLineSize *
                obj->numProcessors, Cache_Type_ALL, FALSE);
        Cache_wbInv((Ptr)(obj->lastProcEnteringStage[0]), obj->cacheLineSize *
                obj->numProcessors-1, Cache_Type_ALL, TRUE);
    }
}
