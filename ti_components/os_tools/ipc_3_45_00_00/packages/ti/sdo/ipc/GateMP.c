/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== GateMP.c ========
 */

#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include <ti/sysbios/gates/GateMutexPri.h>
#include <ti/sysbios/gates/GateSwi.h>
#include <ti/sysbios/gates/GateAll.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/utils/_NameServer.h>
#include <ti/sdo/ipc/_SharedRegion.h>

#include "package/internal/GateMP.xdc.h"

/* Helper macros */
#define GETREMOTE(mask) ((ti_sdo_ipc_GateMP_RemoteProtect)((mask) >> 8))
#define GETLOCAL(mask)  ((ti_sdo_ipc_GateMP_LocalProtect)((mask) & 0xFF))
#define SETMASK(remoteProtect, localProtect) \
                        ((Bits32)((remoteProtect) << 8 | (localProtect)))

/* Values used to populate the resource 'inUse' arrays */
#define UNUSED          ((UInt8)0)
#define USED            ((UInt8)1)
#define RESERVED        ((UInt8)-1)

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(GateMP_Params_init);
    #pragma FUNC_EXT_CALLED(GateMP_create);
    #pragma FUNC_EXT_CALLED(GateMP_close);
    #pragma FUNC_EXT_CALLED(GateMP_delete);
    #pragma FUNC_EXT_CALLED(GateMP_enter);
    #pragma FUNC_EXT_CALLED(GateMP_getDefaultRemote);
    #pragma FUNC_EXT_CALLED(GateMP_getLocalProtect);
    #pragma FUNC_EXT_CALLED(GateMP_getRemoteProtect);
    #pragma FUNC_EXT_CALLED(GateMP_leave);
    #pragma FUNC_EXT_CALLED(GateMP_open);
    #pragma FUNC_EXT_CALLED(GateMP_openByAddr);
    #pragma FUNC_EXT_CALLED(GateMP_sharedMemReq);
#endif

/*
 *  ======== GateMP_getSharedParams ========
 */
static Void GateMP_getSharedParams(GateMP_Params *sparams,
        const ti_sdo_ipc_GateMP_Params *params)
{
    sparams->name             = params->name;
    sparams->regionId         = params->regionId;
    sparams->sharedAddr       = params->sharedAddr;
    sparams->localProtect     = (GateMP_LocalProtect)
        params->localProtect;
    sparams->remoteProtect    = (GateMP_RemoteProtect)
        params->remoteProtect;
}

/*
 *  ======== GateMP_getRTSCParams ========
 */
static Void GateMP_getRTSCParams(ti_sdo_ipc_GateMP_Params *params,
        const GateMP_Params *sparams)
{

    ti_sdo_ipc_GateMP_Params_init(params);

    params->name             = sparams->name;
    params->regionId         = sparams->regionId;
    params->sharedAddr       = sparams->sharedAddr;
    params->localProtect     = (ti_sdo_ipc_GateMP_LocalProtect)
        sparams->localProtect;
    params->remoteProtect    = (ti_sdo_ipc_GateMP_RemoteProtect)
        sparams->remoteProtect;
}

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== GateMP_Params_init ========
 */
Void GateMP_Params_init(GateMP_Params *sparams)
{
    ti_sdo_ipc_GateMP_Params params;

    ti_sdo_ipc_GateMP_Params_init(&params);
    GateMP_getSharedParams(sparams, &params);
}

/*
 *  ======== GateMP_create ========
 */
GateMP_Handle GateMP_create(const GateMP_Params *sparams)
{
    ti_sdo_ipc_GateMP_Params params;
    ti_sdo_ipc_GateMP_Object *obj;
    Error_Block eb;

    GateMP_getRTSCParams(&params, (Ptr)sparams);

    Error_init(&eb);

    /* call the module create */
    obj = ti_sdo_ipc_GateMP_create(&params, &eb);

    return ((GateMP_Handle)obj);
}

/*
 *  ======== GateMP_close ========
 */
Int GateMP_close(GateMP_Handle *handlePtr)
{
    ti_sdo_ipc_GateMP_Object *obj = (ti_sdo_ipc_GateMP_Object *)*handlePtr;
    UInt key;
    Int count;

    /*
     *  Cannot call with the numOpens equal to zero.  This is either
     *  a created handle or been closed already.
     */
    Assert_isTrue((obj->numOpens != 0), ti_sdo_ipc_GateMP_A_invalidClose);

    key = Hwi_disable();
    count = --obj->numOpens;
    Hwi_restore(key);

    /*
     *  if the count is zero and the gate is opened, then this
     *  object was created in the open (i.e. the create happened
     *  on a remote processor.
     */
    if ((count == 0) && (obj->objType == ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC)) {
        GateMP_delete(handlePtr);
    }

    *handlePtr = NULL;

    return (GateMP_S_SUCCESS);
}

/*
 *  ======== GateMP_delete ========
 */
Int GateMP_delete(GateMP_Handle *handlePtr)
{
    ti_sdo_ipc_GateMP_delete((ti_sdo_ipc_GateMP_Handle *)handlePtr);

    return (GateMP_S_SUCCESS);
}

/*
 *  ======== GateMP_enter ========
 */
IArg GateMP_enter(GateMP_Handle handle)
{
    IArg key;
    ti_sdo_ipc_GateMP_Object *obj = (ti_sdo_ipc_GateMP_Object *)handle;

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    key = IGateProvider_enter(obj->gateHandle);

    Log_write3(ti_sdo_ipc_GateMP_LM_enter,(UArg)obj->remoteProtect,
            (UArg)obj->resourceId, key);

    return (key);
}

/*
 *  ======== GateMP_leave ========
 */
Void GateMP_leave(GateMP_Handle handle, IArg key)
{
    ti_sdo_ipc_GateMP_Object *obj = (ti_sdo_ipc_GateMP_Object *)handle;

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    IGateProvider_leave(obj->gateHandle, key);

    Log_write3(ti_sdo_ipc_GateMP_LM_leave, (UArg)obj->remoteProtect,
        (UArg)obj->resourceId, key);
}

/*
 *  ======== GateMP_open ========
 */
Int GateMP_open(String name, GateMP_Handle *handlePtr)
{
    SharedRegion_SRPtr sharedShmBase;
    Int status;
    ti_sdo_ipc_GateMP_Object *obj;
    ti_sdo_ipc_GateMP_Params params;
    Error_Block eb;
    UInt key;
    UInt32 len;
    UInt32 mask;
    UInt32 resourceId;
    Ptr sharedAddr;
    UInt32 nsValue[4];

    Error_init(&eb);

    /* Assert that a pointer has been supplied */
    Assert_isTrue(handlePtr != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    len = sizeof(nsValue);

    /*
     *  Get the Attrs out of the NameServer instance.
     *  Search all processors.
     */
    status = NameServer_get((NameServer_Handle)GateMP_module->nameServer, name,
            &nsValue, &len, MultiProc_getClusterProcList());

    if (status < 0) {
        *handlePtr = NULL;
        return (GateMP_E_NOTFOUND);
    }

    /*
     * The least significant bit of nsValue[1] == 0 means its a
     * local GateMP, otherwise its a remote GateMP.
     */
    if (((nsValue[1] & 0x1) == 0) &&
        ((nsValue[1] >> 16) != MultiProc_self())) {
        /* Trying to open a local GateMP remotely */
        *handlePtr = NULL;
        return (GateMP_E_FAIL);
    }

    if ((nsValue[1] & 0x1) == 0) {
        /*
         * Opening a local GateMP locally. The GateMP is created
         * from a local heap so don't do SharedRegion Ptr conversion.
         */
        sharedAddr = (Ptr)nsValue[0];
        status = GateMP_openByAddr(sharedAddr, handlePtr);
    }
    else if (GateMP_module->hostSupport == FALSE) {
        /* Opening a remote GateMP. Need to do SharedRegion Ptr conversion. */
        sharedShmBase = (SharedRegion_SRPtr)nsValue[0];
        sharedAddr = SharedRegion_getPtr(sharedShmBase);
        status = GateMP_openByAddr(sharedAddr, handlePtr);
    }
    else {
        /*  need to track number of opens atomically */
        key = Hwi_disable();
        resourceId = nsValue[2];
        mask = nsValue[3];

        /* Remote case */
        switch (GETREMOTE(mask)) {
            case GateMP_RemoteProtect_SYSTEM:
                obj = GateMP_module->remoteSystemGates[resourceId];
                break;

            case GateMP_RemoteProtect_CUSTOM1:
                obj = GateMP_module->remoteCustom1Gates[resourceId];
                break;

            case GateMP_RemoteProtect_CUSTOM2:
                obj = GateMP_module->remoteCustom2Gates[resourceId];
                break;

            default:
                obj = NULL;
                status = GateMP_E_FAIL;
                break;
        }

        if (status == GateMP_S_SUCCESS) {
            /*
             *  If the object is NULL, then it must have been created on a
             *  remote processor. Need to create a local object. This is
             *  accomplished by setting the openFlag to TRUE.
             */
            if (obj == NULL) {
                /* Create a GateMP object with the openFlag set to true */
                ti_sdo_ipc_GateMP_Params_init(&params);
                params.openFlag = TRUE;
                params.sharedAddr = NULL;
                params.resourceId = resourceId;
                params.localProtect = GETLOCAL(mask);
                params.remoteProtect = GETREMOTE(mask);

                obj = ti_sdo_ipc_GateMP_create(&params, &eb);
                if (obj == NULL) {
                    status = GateMP_E_FAIL;
                }
            }
            else {
                obj->numOpens++;
            }
        }

        /* Return the GateMP instance  */
        *handlePtr = (GateMP_Handle)obj;

        /* restore hwi mask */
        Hwi_restore(key);
    }

    return (status);
}

/*
 *  ======== GateMP_openByAddr ========
 */
Int GateMP_openByAddr(Ptr sharedAddr, GateMP_Handle *handlePtr)
{
    Int status = GateMP_S_SUCCESS;
    UInt key;
    ti_sdo_ipc_GateMP_Object *obj;
    ti_sdo_ipc_GateMP_Params params;
    ti_sdo_ipc_GateMP_Attrs *attrs;
    UInt16 regionId;
    Error_Block eb;

    Error_init(&eb);

    attrs = (ti_sdo_ipc_GateMP_Attrs *)sharedAddr;

    /* get the region id and invalidate attrs is needed */
    regionId = SharedRegion_getId(sharedAddr);
    if (regionId != SharedRegion_INVALIDREGIONID) {
        if (SharedRegion_isCacheEnabled(regionId)) {
            Cache_inv(attrs, sizeof(ti_sdo_ipc_GateMP_Attrs), Cache_Type_ALL,
                    TRUE);
        }
    }

    if (attrs->status != ti_sdo_ipc_GateMP_CREATED) {
        *handlePtr = NULL;
        status = GateMP_E_NOTFOUND;
    }
    else {
        /* Local gate */
        if (GETREMOTE(attrs->mask) == GateMP_RemoteProtect_NONE) {
            if (attrs->creatorProcId != MultiProc_self()) {
                Error_raise(&eb, ti_sdo_ipc_GateMP_E_localGate, 0, 0);
                return (GateMP_E_FAIL);
            }

            /* need to atomically increment number of opens */
            key = Hwi_disable();

            obj = (ti_sdo_ipc_GateMP_Object *)attrs->arg;
            *handlePtr = (GateMP_Handle)obj;
            obj->numOpens++;

            /* restore hwi mask */
            Hwi_restore(key);

            return (GateMP_S_SUCCESS);
        }

        /*  need to track number of opens atomically */
        key = Hwi_disable();

        /* Remote case */
        switch (GETREMOTE(attrs->mask)) {
            case GateMP_RemoteProtect_SYSTEM:
                obj = GateMP_module->remoteSystemGates[attrs->arg];
                break;

            case GateMP_RemoteProtect_CUSTOM1:
                obj = GateMP_module->remoteCustom1Gates[attrs->arg];
                break;

            case GateMP_RemoteProtect_CUSTOM2:
                obj = GateMP_module->remoteCustom2Gates[attrs->arg];
                break;

            default:
                obj = NULL;
                status = GateMP_E_FAIL;
                break;
        }

        if (status == GateMP_S_SUCCESS) {
            /*
             *  If the object is NULL, then it must have been created on a
             *  remote processor. Need to create a local object. This is
             *  accomplished by setting the openFlag to TRUE.
             */
            if (obj == NULL) {
                /* Create a GateMP object with the openFlag set to true */
                ti_sdo_ipc_GateMP_Params_init(&params);
                params.openFlag = TRUE;
                params.sharedAddr = sharedAddr;
                params.resourceId = attrs->arg;
                params.localProtect = GETLOCAL(attrs->mask);
                params.remoteProtect = GETREMOTE(attrs->mask);

                obj = ti_sdo_ipc_GateMP_create(&params, &eb);
                if (obj == NULL) {
                    status = GateMP_E_FAIL;
                }
            }
            else {
                obj->numOpens++;
            }
        }

        /* Return the GateMP instance  */
        *handlePtr = (GateMP_Handle)obj;

        /* restore hwi mask */
        Hwi_restore(key);
    }

    return (status);
}

/*
 *  ======== GateMP_sharedMemReq ========
 */
SizeT GateMP_sharedMemReq(const GateMP_Params *params)
{
    SizeT memReq, minAlign;
    UInt16 regionId;
    ti_sdo_ipc_GateMP_RemoteSystemProxy_Params systemParams;
    ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params custom1Params;
    ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params custom2Params;

    if (params->sharedAddr) {
        regionId = SharedRegion_getId(params->sharedAddr);
    }
    else {
        regionId = params->regionId;
    }

    Assert_isTrue(regionId != SharedRegion_INVALIDREGIONID,
            ti_sdo_ipc_Ipc_A_internal);

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(regionId) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(regionId);
    }

    memReq = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Attrs), minAlign);

    /* add the amount of shared memory required by proxy */
    if (params->remoteProtect == GateMP_RemoteProtect_SYSTEM) {
        ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_init(&systemParams);
        systemParams.regionId = regionId;
        memReq += ti_sdo_ipc_GateMP_RemoteSystemProxy_sharedMemReq(
                (IGateMPSupport_Params *)&systemParams);
    }
    else if (params->remoteProtect == GateMP_RemoteProtect_CUSTOM1) {
        ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_init(&custom1Params);
        custom1Params.regionId = regionId;
        memReq += ti_sdo_ipc_GateMP_RemoteCustom1Proxy_sharedMemReq(
                (IGateMPSupport_Params *)&custom1Params);
    }
    else if (params->remoteProtect == GateMP_RemoteProtect_CUSTOM2) {
        ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params_init(&custom2Params);
        custom2Params.regionId = regionId;
        memReq += ti_sdo_ipc_GateMP_RemoteCustom2Proxy_sharedMemReq(
                (IGateMPSupport_Params *)&custom2Params);
    }

    return (memReq);
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_GateMP_createLocal ========
 */
IGateProvider_Handle ti_sdo_ipc_GateMP_createLocal(
    ti_sdo_ipc_GateMP_LocalProtect localProtect)
{
    IGateProvider_Handle gateHandle;

    /* Create the local gate. */
    switch (localProtect) {
        case GateMP_LocalProtect_NONE:
            /* Plug with the GateNull singleton */
            gateHandle = GateMP_module->gateNull;
            break;

        case GateMP_LocalProtect_INTERRUPT:
            /* Plug with the GateAll singleton */
            gateHandle = GateMP_module->gateAll;
            break;

        case GateMP_LocalProtect_TASKLET:
            /* Plug with the GateSwi singleton */
            gateHandle = GateMP_module->gateSwi;
            break;

        case GateMP_LocalProtect_THREAD:
        case GateMP_LocalProtect_PROCESS:
            /* Plug with the GateMutexPri singleton */
            gateHandle = GateMP_module->gateMutexPri;
            break;

        default:
            /* Invalid local protection level encountered */
            Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
            break;
    }

    return (gateHandle);
}

/*
 *  ======== GateMP_getDefaultRemote ========
 */
GateMP_Handle GateMP_getDefaultRemote()
{
    return ((GateMP_Handle)GateMP_module->defaultGate);
}

/*
 *  ======== GateMP_getLocalProtect ========
 */
GateMP_LocalProtect GateMP_getLocalProtect(GateMP_Handle handle)
{
    ti_sdo_ipc_GateMP_Object *obj = (ti_sdo_ipc_GateMP_Object *)handle;

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    return ((GateMP_LocalProtect)obj->localProtect);
}

/*
 *  ======== GateMP_getRemoteProtect ========
 */
GateMP_RemoteProtect GateMP_getRemoteProtect(GateMP_Handle handle)
{
    ti_sdo_ipc_GateMP_Object *obj = (ti_sdo_ipc_GateMP_Object *)handle;

    Assert_isTrue(obj != NULL, ti_sdo_ipc_Ipc_A_nullArgument);

    return ((GateMP_RemoteProtect)obj->remoteProtect);
}

/*
 *  ======== ti_sdo_ipc_GateMP_getRegion0ReservedSize ========
 */
SizeT ti_sdo_ipc_GateMP_getRegion0ReservedSize(Void)
{
    SizeT reserved, minAlign;

    minAlign = Memory_getMaxDefaultTypeAlign();

    if (SharedRegion_getCacheLineSize(0) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(0);
    }

    reserved = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Reserved), minAlign);

    reserved += _Ipc_roundup(GateMP_module->numRemoteSystem, minAlign);

    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1) {
            reserved += _Ipc_roundup(GateMP_module->numRemoteCustom1, minAlign);
    }

    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2) {
            reserved += _Ipc_roundup(GateMP_module->numRemoteCustom2, minAlign);
    }

    return (reserved);
}

/*
 *  ======== ti_sdo_ipc_GateMP_setRegion0Reserved ========
 */
Void ti_sdo_ipc_GateMP_setRegion0Reserved(Ptr sharedAddr)
{
    ti_sdo_ipc_GateMP_Reserved *reserve;
    SizeT minAlign, offset;
    UInt i;
    Bits32 *delegateReservedMask;
    UInt32 nsValue[6];
    Int ret;

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(0) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(0);
    }

    /* setup ti_sdo_ipc_GateMP_Reserved fields */
    reserve = (ti_sdo_ipc_GateMP_Reserved *)sharedAddr;
    reserve->version = ti_sdo_ipc_GateMP_VERSION;

    if (SharedRegion_isCacheEnabled(0)) {
        Cache_wbInv(sharedAddr, sizeof(ti_sdo_ipc_GateMP_Reserved),
            Cache_Type_ALL, TRUE);
    }

    /*
     *  initialize the in-use array in shared memory for the system gates.
     */
    offset = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Reserved), minAlign);
    GateMP_module->remoteSystemInUse =
        (Ptr)((UInt32)sharedAddr + offset);

    if (GateMP_module->numRemoteSystem != 0) {
        memset(GateMP_module->remoteSystemInUse, 0,
            GateMP_module->numRemoteSystem * sizeof(UInt8));
        delegateReservedMask =
                ti_sdo_ipc_GateMP_RemoteSystemProxy_getReservedMask();
        if (delegateReservedMask != NULL) {
            for (i = 0; i < GateMP_module->numRemoteSystem; i++) {
                if (delegateReservedMask[i >> 5] & (1 << (i % 32))) {
                    GateMP_module->remoteSystemInUse[i] = RESERVED;
                }
            }
        }

        if (SharedRegion_isCacheEnabled(0)) {
            Cache_wbInv(GateMP_module->remoteSystemInUse,
                GateMP_module->numRemoteSystem * sizeof(UInt8),
                Cache_Type_ALL,
                TRUE);
        }
    }

    /*
     *  initialize the in-use array in shared memory for the custom1 gates.
     *  Need to check if this proxy is the same as system
     */
    offset = _Ipc_roundup(GateMP_module->numRemoteSystem, minAlign);
    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1) {
        if (GateMP_module->numRemoteCustom1 != 0) {
            GateMP_module->remoteCustom1InUse =
                GateMP_module->remoteSystemInUse + offset;

            memset(GateMP_module->remoteCustom1InUse, 0,
                GateMP_module->numRemoteCustom1 * sizeof(UInt8));
            delegateReservedMask =
                    ti_sdo_ipc_GateMP_RemoteCustom1Proxy_getReservedMask();
            if (delegateReservedMask != NULL) {
                for (i = 0; i < GateMP_module->numRemoteCustom1; i++) {
                    if (delegateReservedMask[i >> 5] & (1 << (i % 32))) {
                        GateMP_module->remoteCustom1InUse[i] = RESERVED;
                    }
                }
            }
            if (SharedRegion_isCacheEnabled(0)) {
                Cache_wbInv(GateMP_module->remoteCustom1InUse,
                     GateMP_module->numRemoteCustom1 * sizeof(UInt8),
                     Cache_Type_ALL,
                     TRUE);
            }
        }
    }
    else {
        GateMP_module->remoteCustom1InUse = GateMP_module->remoteSystemInUse;
        GateMP_module->remoteCustom1Gates = GateMP_module->remoteSystemGates;
    }

    /*
     *  initialize the in-use array in shared memory for the custom2 gates.
     *  Need to check if this proxy is the same as system or custom1
     */
    offset = _Ipc_roundup(GateMP_module->numRemoteCustom1, minAlign);
    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2) {
        if (GateMP_module->numRemoteCustom2 != 0) {
                GateMP_module->remoteCustom2InUse =
                    GateMP_module->remoteCustom1InUse + offset;

            memset(GateMP_module->remoteCustom2InUse, 0,
                GateMP_module->numRemoteCustom2 * sizeof(UInt8));
            delegateReservedMask =
                    ti_sdo_ipc_GateMP_RemoteCustom2Proxy_getReservedMask();
            if (delegateReservedMask != NULL) {
                for (i = 0; i < GateMP_module->numRemoteCustom2; i++) {
                    if (delegateReservedMask[i >> 5] & (1 << (i % 32))) {
                        GateMP_module->remoteCustom2InUse[i] = RESERVED;
                    }
                }
            }

            if (SharedRegion_isCacheEnabled(0)) {
                Cache_wbInv(GateMP_module->remoteCustom2InUse,
                     GateMP_module->numRemoteCustom2 * sizeof(UInt8),
                     Cache_Type_ALL,
                     TRUE);
            }
        }
    }
    else if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2] ==
             ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1) {
        GateMP_module->remoteCustom2InUse =
            GateMP_module->remoteCustom1InUse;
        GateMP_module->remoteCustom2Gates =
            GateMP_module->remoteCustom1Gates;
    }
    else {
        GateMP_module->remoteCustom2InUse = GateMP_module->remoteSystemInUse;
        GateMP_module->remoteCustom2Gates = GateMP_module->remoteSystemGates;
    }

    if (GateMP_module->hostSupport == TRUE) {
        /* Add special entry to store inuse arrays' location and size */
        ret = _GateMP_virtToPhys(
            (UInt32)GateMP_module->remoteSystemInUse, &nsValue[0]);
        Assert_isTrue(ret == GateMP_S_SUCCESS, (Assert_Id)NULL);
        (void)ret;   /* silence unused var warning when asserts disabled */
        if (GateMP_module->numRemoteCustom1 != 0) {
            ret = _GateMP_virtToPhys(
                (UInt32)GateMP_module->remoteCustom1InUse, &nsValue[1]);
            Assert_isTrue(ret == GateMP_S_SUCCESS, (Assert_Id)NULL);
        }
        else {
            nsValue[1] = 0;
        }
        if (GateMP_module->numRemoteCustom2 != 0) {
            ret = _GateMP_virtToPhys(
                (UInt32)GateMP_module->remoteCustom2InUse, &nsValue[2]);
            Assert_isTrue(ret == GateMP_S_SUCCESS, (Assert_Id)NULL);
	}
        else {
            nsValue[2] = 0;
        }
        nsValue[3] = GateMP_module->numRemoteSystem;
        nsValue[4] = GateMP_module->numRemoteCustom1;
        nsValue[5] = GateMP_module->numRemoteCustom2;
        GateMP_module->nsKey = NameServer_add((NameServer_Handle)
            GateMP_module->nameServer, "_GateMP_TI_info", &nsValue,
            sizeof(nsValue));
    }
}

/*
 *  ======== ti_sdo_ipc_GateMP_openRegion0Reserved ========
 */
Void ti_sdo_ipc_GateMP_openRegion0Reserved(Ptr sharedAddr)
{
    ti_sdo_ipc_GateMP_Reserved *reserve;
    SizeT minAlign, offset;

    minAlign = Memory_getMaxDefaultTypeAlign();
    if (SharedRegion_getCacheLineSize(0) > minAlign) {
        minAlign = SharedRegion_getCacheLineSize(0);
    }


    /* setup ti_sdo_ipc_GateMP_Reserved fields */
    reserve = (ti_sdo_ipc_GateMP_Reserved *)sharedAddr;

    if (reserve->version != ti_sdo_ipc_GateMP_VERSION) {
        /* Version mismatch: return an error */
        Error_raise(NULL, ti_sdo_ipc_Ipc_E_versionMismatch, reserve->version,
                    ti_sdo_ipc_GateMP_VERSION);
        return;
    }

    offset = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Reserved), minAlign);
    GateMP_module->remoteSystemInUse =
        (Ptr)((UInt32)sharedAddr + offset);

    /*
     *  initialize the in-use array in shared memory for the custom1 gates.
     *  Need to check if this proxy is the same as system
     */
    offset = _Ipc_roundup(GateMP_module->numRemoteSystem, minAlign);
    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1) {
        if (GateMP_module->numRemoteCustom1 != 0) {
            GateMP_module->remoteCustom1InUse =
                GateMP_module->remoteSystemInUse + offset;
        }
    }
    else {
        GateMP_module->remoteCustom1InUse = GateMP_module->remoteSystemInUse;
        GateMP_module->remoteCustom1Gates = GateMP_module->remoteSystemGates;
    }

    offset = _Ipc_roundup(GateMP_module->numRemoteCustom1, minAlign);
    if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2] ==
        ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2) {
        if (GateMP_module->numRemoteCustom2 != 0) {
            GateMP_module->remoteCustom2InUse =
                GateMP_module->remoteCustom1InUse + offset;
        }
    }
    else if (GateMP_module->proxyMap[ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM2] ==
             ti_sdo_ipc_GateMP_ProxyOrder_CUSTOM1) {
        GateMP_module->remoteCustom2InUse =
            GateMP_module->remoteCustom1InUse;
        GateMP_module->remoteCustom2Gates =
            GateMP_module->remoteCustom1Gates;
    }
    else {
        GateMP_module->remoteCustom2InUse = GateMP_module->remoteSystemInUse;
        GateMP_module->remoteCustom2Gates = GateMP_module->remoteSystemGates;
    }
}

/*
 *  ======== ti_sdo_ipc_GateMP_attach ========
 */
Int ti_sdo_ipc_GateMP_attach(UInt16 remoteProcId, Ptr sharedAddr)
{
    Ptr gateMPsharedAddr;
    SharedRegion_Entry entry;
    ti_sdo_ipc_GateMP_Handle defaultGate;
    Int status = GateMP_S_SUCCESS;

    /* If default gate is not NULL return since its already set */
    if (GateMP_getDefaultRemote() != NULL) {
        return(GateMP_S_ALREADYSETUP);
    }

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    gateMPsharedAddr = (Ptr)((UInt32)sharedAddr +
                       ti_sdo_ipc_GateMP_getRegion0ReservedSize());

    if ((entry.ownerProcId != MultiProc_self()) &&
        (entry.ownerProcId != MultiProc_INVALIDID)) {
        /* if not the owner of the SharedRegion */
        ti_sdo_ipc_GateMP_openRegion0Reserved(sharedAddr);

        /* open the gate by address */
        status = GateMP_openByAddr(gateMPsharedAddr,
                (GateMP_Handle *)&defaultGate);

        /* openByAddr should always succeed */
        Assert_isTrue(status >= 0, ti_sdo_ipc_Ipc_A_internal);

        /* set the default GateMP for opener */
        ti_sdo_ipc_GateMP_setDefaultRemote(defaultGate);
    }

    return (status);
}

/*
 *  ======== ti_sdo_ipc_GateMP_detach ========
 */
Int ti_sdo_ipc_GateMP_detach(UInt16 remoteProcId)
{
    SharedRegion_Entry entry;
    GateMP_Handle gate;
    Int status = GateMP_S_SUCCESS;

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    if ((entry.isValid) &&
        (entry.ownerProcId == remoteProcId)) {
        /* get the default gate */
        gate = GateMP_getDefaultRemote();

        if (gate != NULL) {
            /* close the gate */
            status = GateMP_close(&gate);

            /* set the default remote gate to NULL */
            ti_sdo_ipc_GateMP_setDefaultRemote(NULL);
        }
    }

    return (status);
}

/*
 *  ======== ti_sdo_ipc_GateMP_start ========
 */
Int ti_sdo_ipc_GateMP_start(Ptr sharedAddr)
{
    SharedRegion_Entry       entry;
    ti_sdo_ipc_GateMP_Params gateMPParams;
    ti_sdo_ipc_GateMP_Handle defaultGate;
    Int status = GateMP_S_SUCCESS;
    Error_Block eb;

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /* if entry owner proc is not specified return */
    if (entry.ownerProcId == MultiProc_INVALIDID) {
        return (status);
    }

    if (entry.ownerProcId == MultiProc_self()) {
        /* if owner of the SharedRegion */
        ti_sdo_ipc_GateMP_setRegion0Reserved(sharedAddr);

        /* create default GateMP */
        ti_sdo_ipc_GateMP_Params_init(&gateMPParams);
        gateMPParams.sharedAddr = (Ptr)((UInt32)sharedAddr +
                ti_sdo_ipc_GateMP_getRegion0ReservedSize());
        gateMPParams.localProtect  = ti_sdo_ipc_GateMP_LocalProtect_TASKLET;
        gateMPParams.name = "_GateMP_TI_dGate";

        if (ti_sdo_utils_MultiProc_numProcessors > 1) {
            gateMPParams.remoteProtect = ti_sdo_ipc_GateMP_RemoteProtect_SYSTEM;
        }
        else {
            gateMPParams.remoteProtect = ti_sdo_ipc_GateMP_RemoteProtect_NONE;
        }

        Error_init(&eb);
        defaultGate = ti_sdo_ipc_GateMP_create(&gateMPParams, &eb);
        if (defaultGate != NULL) {
            /* set the default GateMP for creator */
            ti_sdo_ipc_GateMP_setDefaultRemote(defaultGate);
        }
        else {
            status = GateMP_E_FAIL;
        }
    }

    return (status);
}

/*
 *  ======== ti_sdo_ipc_GateMP_stop ========
 */
Int ti_sdo_ipc_GateMP_stop()
{
    SharedRegion_Entry entry;
    GateMP_Handle gate;
    Int status = GateMP_S_SUCCESS;

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    if ((entry.isValid) &&
        (entry.createHeap) &&
        (entry.ownerProcId == MultiProc_self())) {
        /* get the default GateMP */
        gate = GateMP_getDefaultRemote();

        if (gate != NULL) {
            /* set the default GateMP to NULL */
            ti_sdo_ipc_GateMP_setDefaultRemote(NULL);

            /* delete the default GateMP */
            status = GateMP_delete(&gate);
        }

        /* Remove global info entry from NameServer */
        if ((GateMP_module->hostSupport == TRUE) &&
            (GateMP_module->nsKey != 0)) {
            NameServer_removeEntry((NameServer_Handle)GateMP_module->nameServer,
                GateMP_module->nsKey);
        }
    }

    return (status);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_GateMP_Instance_init ========
 */
Int ti_sdo_ipc_GateMP_Instance_init(ti_sdo_ipc_GateMP_Object *obj,
        const ti_sdo_ipc_GateMP_Params *params,
        Error_Block *eb)
{
    UInt key;
    IGateMPSupport_Handle remoteHandle;
    IGateProvider_Handle localHandle;
    ti_sdo_ipc_GateMP_RemoteSystemProxy_Params systemParams;
    ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params custom1Params;
    ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params custom2Params;
    SizeT minAlign, offset;
    SharedRegion_SRPtr sharedShmBase;
    GateMP_Params sparams;
    UInt32 nsValue[4];
    UInt32 sizeNsValue;
    IHeap_Handle regionHeap;

    /* Initialize resourceId to an invalid value */
    obj->resourceId = (UInt)-1;

    localHandle = ti_sdo_ipc_GateMP_createLocal(params->localProtect);

    /* Open GateMP instance */
    if (params->openFlag == TRUE) {
        /* all open work done here except for remote gateHandle */
        obj->localProtect   = params->localProtect;
        obj->remoteProtect  = params->remoteProtect;
        obj->nsKey          = 0;
        obj->numOpens       = 0; /* Will be set to 1 after init() complete */
        obj->attrs          = (ti_sdo_ipc_GateMP_Attrs *)params->sharedAddr;
        if (obj->attrs != NULL) {
            obj->regionId       = SharedRegion_getId((Ptr)obj->attrs);
            obj->cacheEnabled   = SharedRegion_isCacheEnabled(obj->regionId);
            /* Assert that the buffer is in a valid shared region */
            Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
                      ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);
        }

        obj->allocSize      = 0;
        obj->objType        = ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC;

        minAlign = Memory_getMaxDefaultTypeAlign();

        if ((obj->attrs != NULL) &&
            (SharedRegion_getCacheLineSize(obj->regionId) > minAlign)) {
            minAlign = SharedRegion_getCacheLineSize(obj->regionId);
        }

        offset = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Attrs), minAlign);

        /* TODO: host side created gates cannot have proxy memory */
        if (obj->attrs != NULL) {
            obj->proxyAttrs = (Ptr)((UInt32)obj->attrs + offset);
        }
        else {
            obj->proxyAttrs = NULL;
        }
    }
    /* Create GateMP instance */
    else {
        obj->localProtect  = params->localProtect;
        obj->remoteProtect = params->remoteProtect;
        obj->nsKey         = 0;
        obj->numOpens      = 0;

        if (obj->remoteProtect == GateMP_RemoteProtect_NONE) {
            obj->gateHandle = ti_sdo_ipc_GateMP_createLocal(obj->localProtect);
            if (params->sharedAddr != NULL) {
                /* Create a local gate using shared memory */
                obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;
                obj->attrs = params->sharedAddr;
                obj->regionId = SharedRegion_getId((Ptr)obj->attrs);
                obj->cacheEnabled = SharedRegion_isCacheEnabled(obj->regionId);
            }
            else {
                /* Create a local gate allocating from the local heap */
                obj->objType = ti_sdo_ipc_Ipc_ObjType_LOCAL;
                obj->regionId = ti_sdo_ipc_SharedRegion_INVALIDREGIONID;
                obj->cacheEnabled  = FALSE; /* local */
                obj->attrs = Memory_alloc(NULL,
                        sizeof(ti_sdo_ipc_GateMP_Attrs), 0, eb);
                if (obj->attrs == NULL) {
                    return (2);
                }

            }

            obj->attrs->arg = (Bits32)obj;
            obj->attrs->mask = SETMASK(obj->remoteProtect, obj->localProtect);
            obj->attrs->creatorProcId = MultiProc_self();
            obj->attrs->status = ti_sdo_ipc_GateMP_CREATED;
            if (obj->cacheEnabled) {
                /*
                 *  Need to write back memory if cache is enabled because cache
                 *  will be invalidated during openByAddr
                 */
                Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_GateMP_Attrs),
                        Cache_Type_ALL, TRUE);
            }

            if (params->name) {
                nsValue[0] = (UInt32)obj->attrs;
                /*
                 *  Top 16 bits = procId of creator
                 *  Bottom 16 bits = '0' if local, '1' otherwise
                 */
                nsValue[1] = ((UInt32)MultiProc_self()) << 16;

                if (GateMP_module->hostSupport == TRUE) {
                    nsValue[2] = obj->attrs->arg;
                    nsValue[3] = obj->attrs->mask;
                    sizeNsValue = sizeof(nsValue);
                }
                else {
                    sizeNsValue = 2 * sizeof(UInt32);
                }

                obj->nsKey = NameServer_add((NameServer_Handle)
                        GateMP_module->nameServer, params->name, &nsValue,
                        sizeNsValue);

                if (obj->nsKey == NULL) {
                    Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name,
                        0);
                    return (3);
                }
            }

            /* Nothing else to do for local gates */
            return (0);
        }

        if (params->sharedAddr == NULL) {
            /* Need to allocate from heap */
            obj->objType        = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION;
            obj->regionId       = params->regionId;
            GateMP_getSharedParams(&sparams, params);
            obj->allocSize      = GateMP_sharedMemReq(&sparams);
            obj->cacheEnabled   = SharedRegion_isCacheEnabled(obj->regionId);

            /* The region heap will do the alignment */
            regionHeap = SharedRegion_getHeap(obj->regionId);
            Assert_isTrue(regionHeap != NULL, ti_sdo_ipc_SharedRegion_A_noHeap);
            obj->attrs = Memory_alloc(regionHeap, obj->allocSize, 0, eb);
            if (obj->attrs == NULL) {
                return (3);
            }

            minAlign = Memory_getMaxDefaultTypeAlign();

            if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
                minAlign = SharedRegion_getCacheLineSize(obj->regionId);
            }

            offset = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Attrs), minAlign);

            obj->proxyAttrs = (Ptr)((UInt32)obj->attrs + offset);
        }
        else {
            /* creating using sharedAddr */
            obj->regionId = SharedRegion_getId(params->sharedAddr);
            /* Assert that the buffer is in a valid shared region */
            Assert_isTrue(obj->regionId != SharedRegion_INVALIDREGIONID,
                          ti_sdo_ipc_Ipc_A_addrNotInSharedRegion);

            obj->attrs = (ti_sdo_ipc_GateMP_Attrs *)params->sharedAddr;
            obj->cacheEnabled  = SharedRegion_isCacheEnabled(obj->regionId);
            obj->objType = ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC;

            minAlign = Memory_getMaxDefaultTypeAlign();

            if (SharedRegion_getCacheLineSize(obj->regionId) > minAlign) {
                minAlign = SharedRegion_getCacheLineSize(obj->regionId);
            }

            /* Assert that sharedAddr has correct alignment */
            Assert_isTrue(minAlign == 0 ||
                          ((UInt32)params->sharedAddr % minAlign) == 0,
                          ti_sdo_ipc_Ipc_A_addrNotCacheAligned);

            offset = _Ipc_roundup(sizeof(ti_sdo_ipc_GateMP_Attrs), minAlign);

            obj->proxyAttrs = (Ptr)((UInt32)obj->attrs + offset);
        }
    }

    /* Proxy work for open and create done here */
    switch (obj->remoteProtect) {
        case GateMP_RemoteProtect_SYSTEM:
            if (obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
                /* Created Instance */
                obj->resourceId = GateMP_getFreeResource(
                    GateMP_module->remoteSystemInUse,
                             GateMP_module->numRemoteSystem, eb);
                if (Error_check(eb) == TRUE) {
                    return (4);
                }
            }
            else {
                /* resourceId set by open call */
                obj->resourceId = params->resourceId;
            }

            /* Create the proxy object */
            ti_sdo_ipc_GateMP_RemoteSystemProxy_Params_init(&systemParams);
            systemParams.resourceId = obj->resourceId;
            systemParams.openFlag =
                    (obj->objType == ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC);
            systemParams.sharedAddr = obj->proxyAttrs;
            systemParams.regionId = obj->regionId;
            remoteHandle = ti_sdo_ipc_GateMP_RemoteSystemProxy_create(
                    localHandle, &systemParams, eb);

            if (remoteHandle == NULL) {
                return (5);
            }

            /* Fill in the local array because it is cooked */
            key = Hwi_disable();
            GateMP_module->remoteSystemGates[obj->resourceId] = obj;
            Hwi_restore(key);
            break;

        case GateMP_RemoteProtect_CUSTOM1:
            if (obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
                obj->resourceId = GateMP_getFreeResource(
                             GateMP_module->remoteCustom1InUse,
                             GateMP_module->numRemoteCustom1, eb);
                if (Error_check(eb) == TRUE) {
                    return (4);
                }
            }
            else {
                /* resourceId set by open call */
                obj->resourceId = params->resourceId;
            }

            /* Create the proxy object */
            ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Params_init(&custom1Params);
            custom1Params.resourceId = obj->resourceId;
            custom1Params.openFlag =
                    (obj->objType == ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC);
            custom1Params.sharedAddr = obj->proxyAttrs;
            custom1Params.regionId = obj->regionId;
            remoteHandle = ti_sdo_ipc_GateMP_RemoteCustom1Proxy_create(
                    localHandle, &custom1Params, eb);
            if (remoteHandle == NULL) {
                return (5);
            }

            /* Fill in the local array because it is cooked */
            key = Hwi_disable();
            GateMP_module->remoteCustom1Gates[obj->resourceId] = obj;
            Hwi_restore(key);
            break;

        case GateMP_RemoteProtect_CUSTOM2:
            if (obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
                obj->resourceId = GateMP_getFreeResource(
                             GateMP_module->remoteCustom2InUse,
                             GateMP_module->numRemoteCustom2, eb);
                if (Error_check(eb) == TRUE) {
                    return (4);
                }
            }
            else {
                /* resourceId set by open call */
                obj->resourceId = params->resourceId;
            }

            /* Create the proxy object */
            ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Params_init(&custom2Params);
            custom2Params.resourceId = obj->resourceId;
            custom2Params.openFlag =
                    (obj->objType == ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC);
            custom2Params.sharedAddr = obj->proxyAttrs;
            custom2Params.regionId = obj->regionId;
            remoteHandle = ti_sdo_ipc_GateMP_RemoteCustom2Proxy_create(
                    localHandle, &custom2Params, eb);
            if (remoteHandle == NULL) {
                return (5);
            }

            /* Fill in the local array because it is cooked */
            key = Hwi_disable();
            GateMP_module->remoteCustom2Gates[obj->resourceId] = obj;
            Hwi_restore(key);
            break;

        default:
            /* Should never be here */
            Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
            return (5);  /* keep Coverity happy */
    }

    obj->gateHandle = IGateMPSupport_Handle_upCast(remoteHandle);

    /* Place Name/Attrs into NameServer table */
    if (obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
        /* Fill in the attrs */
        obj->attrs->arg = obj->resourceId;
        obj->attrs->mask = SETMASK(obj->remoteProtect, obj->localProtect);
        obj->attrs->creatorProcId = MultiProc_self();
        obj->attrs->status = ti_sdo_ipc_GateMP_CREATED;

        if (obj->cacheEnabled) {
            Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_GateMP_Attrs),
                    Cache_Type_ALL, TRUE);
        }

        if (params->name != NULL) {
            sharedShmBase = SharedRegion_getSRPtr(obj->attrs, obj->regionId);
            nsValue[0] = (UInt32)sharedShmBase;
            /*
             *  Top 16 bits = procId of creator
             *  Bottom 16 bits = '0' if local, '1' otherwise
             */
            nsValue[1] = ((UInt32)MultiProc_self() << 16) | 1;

            if (GateMP_module->hostSupport == TRUE) {
                /* Making a copy of these for host processor */
                nsValue[2] = obj->attrs->arg;
                nsValue[3] = obj->attrs->mask;
                sizeNsValue = sizeof(nsValue);
            }
            else {
                sizeNsValue = 2 * sizeof(UInt32);
            }

            obj->nsKey = NameServer_add((NameServer_Handle)
                    GateMP_module->nameServer, params->name, &nsValue,
                    sizeNsValue);

            if (obj->nsKey == NULL) {
                Error_raise(eb, ti_sdo_ipc_Ipc_E_nameFailed, params->name, 0);
                return (6);
            }
        }

        Log_write2(ti_sdo_ipc_GateMP_LM_create,
                (UArg)obj->remoteProtect, (UArg)obj->resourceId);
    }
    else {
        obj->numOpens = 1;

        Log_write2(ti_sdo_ipc_GateMP_LM_open,
            (UArg)obj->remoteProtect, (UArg)obj->resourceId);
    }

    return (0);
}

/*
 *  ======== ti_sdo_ipc_GateMP_Instance_finalize ========
 */
Void ti_sdo_ipc_GateMP_Instance_finalize(
        ti_sdo_ipc_GateMP_Object *obj, Int status)
{
    UInt systemKey;
    ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle systemHandle;
    ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle custom1Handle;
    ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Handle custom2Handle;

    ti_sdo_ipc_GateMP_Handle *remoteHandles;
    UInt8 *inUseArray;
    UInt size;

    /* Cannot call when numOpen is non-zero. */
    Assert_isTrue(obj->numOpens == 0, ti_sdo_ipc_GateMP_A_invalidDelete);

    /* Removed from NameServer */
    if (obj->nsKey != 0) {
        NameServer_removeEntry((NameServer_Handle)GateMP_module->nameServer,
                obj->nsKey);
    }

    /* Set the status to 0 */
    if (obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) {
        obj->attrs->status = 0;
        if (obj->cacheEnabled) {
            Cache_wbInv(obj->attrs, sizeof(ti_sdo_ipc_GateMP_Attrs),
                    Cache_Type_ALL, TRUE);
        }
    }

    /*
     *  If ObjType_LOCAL, memory was allocated from the local system heap.
     *  obj->attrs might be NULL if the Memory_alloc failed in Instance_init
     */
    if (obj->objType == ti_sdo_ipc_Ipc_ObjType_LOCAL && obj->attrs != NULL) {
        Memory_free(NULL, obj->attrs, sizeof(ti_sdo_ipc_GateMP_Attrs));
    }

    switch (obj->remoteProtect) {
        case GateMP_RemoteProtect_SYSTEM:
            if (obj->gateHandle) {
                systemHandle =
                ti_sdo_ipc_GateMP_RemoteSystemProxy_Handle_downCast2(
                        obj->gateHandle);
                ti_sdo_ipc_GateMP_RemoteSystemProxy_delete(&systemHandle);
            }

            inUseArray = GateMP_module->remoteSystemInUse;
            remoteHandles = GateMP_module->remoteSystemGates;
            size = GateMP_module->numRemoteSystem * sizeof(UInt8);
            break;

        case GateMP_RemoteProtect_CUSTOM1:
            if (obj->gateHandle) {
                custom1Handle =
                        ti_sdo_ipc_GateMP_RemoteCustom1Proxy_Handle_downCast2(
                            obj->gateHandle);
                ti_sdo_ipc_GateMP_RemoteCustom1Proxy_delete(&custom1Handle);
            }

            inUseArray = GateMP_module->remoteCustom1InUse;
            remoteHandles = GateMP_module->remoteCustom1Gates;
            size = GateMP_module->numRemoteCustom1 * sizeof(UInt8);
            break;

        case GateMP_RemoteProtect_CUSTOM2:
            if (obj->gateHandle) {
                custom2Handle =
                        ti_sdo_ipc_GateMP_RemoteCustom2Proxy_Handle_downCast2(
                            obj->gateHandle);
                ti_sdo_ipc_GateMP_RemoteCustom2Proxy_delete(&custom2Handle);
            }

            inUseArray = GateMP_module->remoteCustom2InUse;
            remoteHandles = GateMP_module->remoteCustom2Gates;
            size = GateMP_module->numRemoteCustom2 * sizeof(UInt8);
            break;
        case GateMP_RemoteProtect_NONE:
            /*
             *  Nothing else to finalize. Any alloc'ed memory has already been
             *  freed
             */
            Log_write2(ti_sdo_ipc_GateMP_LM_delete, (UArg)obj->remoteProtect,
                (UArg)obj->resourceId);
            return;
        default:
            /* Should never be here */
            Assert_isTrue(FALSE, ti_sdo_ipc_Ipc_A_internal);
            break;
    }

    /* Clear the handle array entry in local memory */
    if (obj->resourceId != (UInt)-1) {
        remoteHandles[obj->resourceId] = NULL;
    }

    if ((obj->objType != ti_sdo_ipc_Ipc_ObjType_OPENDYNAMIC) &&
        (obj->resourceId != (UInt)-1)) {
        /* Clear the resource used flag in shared memory */
        if (GateMP_module->defaultGate != NULL) {
            systemKey = GateMP_enter((GateMP_Handle)GateMP_module->defaultGate);
        }
        else {
            /* this should only be done when deleting the very last GateMP */
            systemKey = Hwi_disable();
        }

#ifdef xdc_target__isaCompatible_v7A
        /* ARM speculative execution might have pulled array into cache */
        if (obj->cacheEnabled) {
            Cache_inv(inUseArray, size, Cache_Type_ALL, TRUE);
        }
#endif
        /* update the GateMP resource tracker */
        inUseArray[obj->resourceId] = UNUSED;
        if (obj->cacheEnabled) {
            Cache_wbInv(inUseArray, size, Cache_Type_ALL, TRUE);
        }

        if (GateMP_module->defaultGate != NULL) {
            GateMP_leave((GateMP_Handle)GateMP_module->defaultGate, systemKey);
        }
        else {
            Hwi_restore(systemKey);
        }
    }

    if (obj->objType == ti_sdo_ipc_Ipc_ObjType_CREATEDYNAMIC_REGION) {
        /* Free memory allocated from the region heap */
        if (obj->attrs) {
            Memory_free(SharedRegion_getHeap(obj->regionId), obj->attrs,
                obj->allocSize);
        }
    }

    Log_write2(ti_sdo_ipc_GateMP_LM_delete, (UArg)obj->remoteProtect,
            (UArg)obj->resourceId);
}

/*
 *  ======== ti_sdo_ipc_GateMP_getSharedAddr ========
 */
SharedRegion_SRPtr ti_sdo_ipc_GateMP_getSharedAddr(
        ti_sdo_ipc_GateMP_Object *obj)
{
    SharedRegion_SRPtr srPtr;

    srPtr = SharedRegion_getSRPtr(obj->attrs, obj->regionId);

    return (srPtr);
}

/*
 *  ======== ti_sdo_ipc_GateMP_setDefaultRemote ========
 */
Void ti_sdo_ipc_GateMP_setDefaultRemote(ti_sdo_ipc_GateMP_Object *obj)
{
    GateMP_module->defaultGate = obj;
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_GateMP_getFreeResource ========
 */
UInt ti_sdo_ipc_GateMP_getFreeResource(UInt8 *inUse, Int num, Error_Block *eb)
{
    UInt key;
    Bool flag = FALSE;
    UInt resourceId;
    GateMP_Handle defaultGate;

    /* Need to look at shared memory. Enter default gate */
    defaultGate = GateMP_getDefaultRemote();

    if (defaultGate){
        key = GateMP_enter(defaultGate);
    }

    /* Invalidate cache before looking at the in-use flags */
    if (SharedRegion_isCacheEnabled(0)) {
        Cache_inv(inUse, num * sizeof(UInt8), Cache_Type_ALL, TRUE);
    }

    /*
     *  Find a free resource id. Note: zero is reserved on the
     *  system proxy for the default gate.
     */
    for (resourceId = 0; resourceId < num; resourceId++) {
        /*
         *  If not in-use, set the inUse to TRUE to prevent other
         *  creates from getting this one.
         */
        if (inUse[resourceId] == UNUSED) {
           flag = TRUE;

           /* Denote in shared memory that the resource is used */
           inUse[resourceId] = USED;
           break;
       }
    }

    /* Write-back if a in-use flag was changed */
    if (flag == TRUE && SharedRegion_isCacheEnabled(0)) {
        Cache_wbInv(inUse, num * sizeof(UInt8), Cache_Type_ALL, TRUE);
    }

    /* Done with the critical section */
    if (defaultGate) {
        GateMP_leave(defaultGate, key);
    }

    if (flag == FALSE) {
        resourceId = (UInt)-1;
        Error_raise(eb, ti_sdo_ipc_GateMP_E_gateUnavailable, 0, 0);
    }

    return (resourceId);
}
