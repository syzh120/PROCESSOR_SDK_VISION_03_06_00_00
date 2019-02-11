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

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/grcm/RcmTypes.h>
#include <ti/grcm/RcmServer.h>

#include <string.h>
#include <stdlib.h>

#include <ti/ipc/mm/MmType.h>
#include <ti/ipc/rpmsg/RPMessage.h>
#include <ti/ipc/rpmsg/NameMap.h>
#include <ti/srvmgr/ServiceMgr.h>

#include "OmapRpc.h"

typedef struct OmapRpc_Object {
    Char                     channelName[OMAPRPC_MAX_CHANNEL_NAMELEN];
    UInt16                   dstProc;
    UInt32                   port;
    RPMessage_Handle         msgq;
    UInt32                   localEndPt;
    Task_Handle              taskHandle;
    Bool                     shutdown;
    Semaphore_Handle         exitSem;
    OmapRpc_SrvDelNotifyFxn  srvDelCB;
    RcmServer_Params         rcmParams;
    UInt32                   numFuncs;
    OmapRpc_FuncSignature   *funcSigs;
} OmapRpc_Object;

Int32 OmapRpc_GetSvrMgrHandle(Void *srvc, Int32 num, Int32 *params)
{
    System_printf("OMAPRPC: Calling RCM Service Manager Create Function!\n");
    return 0;
}

static Void omapRpcTask(UArg arg0, UArg arg1)
{
    OmapRpc_Object *obj = (OmapRpc_Object *)arg0;
    UInt32 local;
    UInt32 remote;
    Int status;
    UInt16 len;
    Char  * msg = NULL;
    OmapRpc_MsgHeader *hdr = NULL;

    msg = Memory_alloc(NULL, 512, 0, NULL); /* maximum rpmsg size is probably
                                             * smaller, but we need to
                                             * be cautious */
    if (msg == NULL) {
        System_printf("OMAPRPC: Failed to allocate msg!\n");
        return;
    }

    hdr = (OmapRpc_MsgHeader *)&msg[0];

    if (obj == NULL) {
        System_printf("OMAPRPC: Failed to start task as arguments are NULL!\n");
        return;
    }

    if (obj->msgq == NULL) {
        System_printf("OMAPRPC: Failed to start task as MessageQ was NULL!\n");
        return;
    }

    /* get the local endpoint we are to use */
    local = obj->localEndPt;
    System_printf("OMAPRPC: connecting from local endpoint %u to port %u\n",
                        obj->localEndPt, obj->port);

    NameMap_register("rpmsg-rpc", obj->channelName, obj->port);

    System_printf("OMAPRPC: started channel %s on port: %d\n", obj->channelName, obj->port);

    while (!obj->shutdown) {

        /* clear out the message and our message vars */
        _memset(msg, 0, sizeof(msg));
        len = 0;
        remote = 0;

        /* receive the message */
        status = RPMessage_recv(obj->msgq, (Ptr)msg, &len, &remote,
                                        RPMessage_FOREVER);

        if (status == RPMessage_E_UNBLOCKED) {
            System_printf("OMAPRPC: unblocked while waiting for messages\n");
            continue;
        }

        System_printf("OMAPRPC: received msg type: %d len: %d from addr: %d\n",
                             hdr->msgType, len, remote);
        switch (hdr->msgType) {
            case OmapRpc_MsgType_CREATE_INSTANCE:
            {
                /* temp pointer to payload */
                OmapRpc_CreateInstance *create =
                                OmapRpc_PAYLOAD(msg, OmapRpc_CreateInstance);
                /* local copy of name */
                Char name[sizeof(create->name)];
                /* return structure */
                OmapRpc_InstanceHandle *handle =
                                OmapRpc_PAYLOAD(msg, OmapRpc_InstanceHandle);
                /* save a copy of the input structure data */
                _strcpy(name, create->name);
                /* clear out the old data */
                _memset(msg, 0, sizeof(msg));

                /* create a new instance of the service */
                handle->status = ServiceMgr_createService(name,
                                                &handle->endpointAddress);

                System_printf("OMAPRPC: created service instance named: %s "
                              "(status=%d) addr: %d\n", name, handle->status,
                                handle->endpointAddress);

                hdr->msgType = OmapRpc_MsgType_INSTANCE_CREATED;
                hdr->msgLen  = sizeof(OmapRpc_InstanceHandle);
                break;
            }
            case OmapRpc_MsgType_DESTROY_INSTANCE:
            {
                /* temp pointer to payload */
                OmapRpc_InstanceHandle *handle =
                                OmapRpc_PAYLOAD(msg, OmapRpc_InstanceHandle);

                /* Stash away endpointAddress for MmServiceMgr_getId to work */
                Task_setEnv(Task_self(), (Ptr)handle->endpointAddress);

                if (obj->srvDelCB != NULL) {
                    obj->srvDelCB();
                }

                Task_setEnv(Task_self(), NULL);

                /* don't clear out the old data... */
                System_printf("OMAPRPC: destroying instance addr: %d\n",
                                                    handle->endpointAddress);
                handle->status = ServiceMgr_deleteService(
                                                    handle->endpointAddress);
                hdr->msgType = OmapRpc_MsgType_INSTANCE_DESTROYED;
                hdr->msgLen = sizeof(OmapRpc_InstanceHandle);
                /* leave the endpoint address alone. */
                break;
            }
            case OmapRpc_MsgType_QUERY_CHAN_INFO:
            {
                OmapRpc_ChannelInfo *chanInfo =
                                      OmapRpc_PAYLOAD(msg, OmapRpc_ChannelInfo);

                chanInfo->numFuncs = obj->numFuncs;
                System_printf("OMAPRPC: channel info query - name %s fxns %u\n",
                                            obj->channelName, chanInfo->numFuncs);
                hdr->msgType = OmapRpc_MsgType_CHAN_INFO;
                hdr->msgLen = sizeof(OmapRpc_ChannelInfo);
                break;
            }
            case OmapRpc_MsgType_QUERY_FUNCTION:
            {
                OmapRpc_QueryFunction *fxnInfo = OmapRpc_PAYLOAD(msg,
                                                         OmapRpc_QueryFunction);
                System_printf("OMAPRPC: function query of type %u\n",
                              fxnInfo->infoType);

                switch (fxnInfo->infoType)
                {
                    case OmapRpc_InfoType_FUNC_SIGNATURE:
                        if (fxnInfo->funcIndex < obj->numFuncs)
                            memcpy(&fxnInfo->info.signature,
                                   &obj->funcSigs[fxnInfo->funcIndex],
                                   sizeof(OmapRpc_FuncSignature));
                        break;
                    case OmapRpc_InfoType_FUNC_PERFORMANCE:
                        break;
                    case OmapRpc_InfoType_NUM_CALLS:
                        break;
                    default:
                        System_printf("OMAPRPC: Invalid info type!\n");
                        break;
                }
                hdr->msgType = OmapRpc_MsgType_FUNCTION_INFO;
                hdr->msgLen = sizeof(OmapRpc_QueryFunction);
                break;
            }
            default:
            {
                /* temp pointer to payload */
                OmapRpc_Error *err = OmapRpc_PAYLOAD(msg, OmapRpc_Error);

                /* the debugging message before we clear */
                System_printf("OMAPRPC: unexpected msg type: %d\n",
                              hdr->msgType);

                /* clear out the old data */
                _memset(msg, 0, sizeof(msg));

                hdr->msgType = OmapRpc_MsgType_ERROR;
                err->endpointAddress = local;
                err->status = OmapRpc_ErrorType_NOT_SUPPORTED;
                break;
            }
       }

       /* compute the length of the return message. */
       len = sizeof(struct OmapRpc_MsgHeader) + hdr->msgLen;

       System_printf("OMAPRPC: Replying with msg type: %d to addr: %d "
                      " from: %d len: %u\n", hdr->msgType, remote, local, len);

       /* send the response. All messages get responses! */
       RPMessage_send(obj->dstProc, remote, local, msg, len);
    }

    System_printf("OMAPRPC: destroying channel on port: %d\n", obj->port);
    NameMap_unregister("rpmsg-rpc", obj->channelName, obj->port);
    if (msg != NULL) {
       Memory_free(NULL, msg, 512);
    }
    /* @TODO delete any outstanding ServiceMgr instances if no disconnect
     * was issued? */

    Semaphore_post(obj->exitSem);
}

/*
 *  ======== OmapRpc_createChannel ========
 */
OmapRpc_Handle OmapRpc_createChannel(String channelName, UInt16 dstProc,
        UInt32 port, RcmServer_Params *rcmParams, MmType_FxnSigTab *fxnSigTab,
        OmapRpc_SrvDelNotifyFxn srvDelCBFunc)
{
    Task_Params taskParams;
    UInt32      func;

    OmapRpc_Object *obj = Memory_alloc(NULL, sizeof(OmapRpc_Object), 0, NULL);

    if (obj == NULL) {
        System_printf("OMAPRPC: Failed to allocate memory for object!\n");
        goto unload;
    }
    _memset(obj, 0, sizeof(OmapRpc_Object));
    obj->numFuncs = fxnSigTab->count + 1;
#if 0
    RcmServer_Params_init(&obj->rcmParams);
    obj->rcmParams.priority = Thread_Priority_ABOVE_NORMAL;
    obj->rcmParams.stackSize = 0x1000;
    obj->rcmParams.fxns.length = obj->numFuncs;
    obj->rcmParams.fxns.elem = Memory_alloc(NULL,
            sizeof(RcmServer_FxnDesc) * obj->numFuncs, 0, NULL);

    if (obj->rcmParams.fxns.elem == NULL) {
        System_printf("OMAPRPC: Failed to allocate RCM function list!\n");
        goto unload;
    }
#else
    memcpy(&obj->rcmParams, rcmParams, sizeof(RcmServer_Params));
    obj->rcmParams.fxns.length = obj->numFuncs;
    obj->rcmParams.fxns.elem = Memory_calloc(NULL, obj->numFuncs *
            sizeof(RcmServer_FxnDesc), 0, NULL);

    if (obj->rcmParams.fxns.elem == NULL) {
        System_printf("OMAPRPC: Failed to allocate RCM function list!\n");
        goto unload;
    }
#endif

    /* setup other variables... */
    obj->shutdown = FALSE;
    obj->dstProc = dstProc;
    obj->port = port;
    strncpy(obj->channelName, channelName, OMAPRPC_MAX_CHANNEL_NAMELEN-1);
    obj->channelName[OMAPRPC_MAX_CHANNEL_NAMELEN-1]='\0';
    obj->srvDelCB = srvDelCBFunc;
    obj->funcSigs = Memory_alloc(NULL, obj->numFuncs *
            sizeof(OmapRpc_FuncSignature), 0, NULL);

    if (obj->funcSigs == NULL) {
        System_printf("OMAPRPC: Failed to allocate signtures list!\n");
        goto unload;
    }

    /* setup the RCM functions and Signatures */
    for (func = 0; func < obj->numFuncs; func++) {
        if (func == 0) {
            /* assign the "first function" */
            obj->rcmParams.fxns.elem[func].name =
                    OmapRpc_Stringerize(OmapRpc_GetSvrMgrHandle);
            obj->rcmParams.fxns.elem[func].addr.createFxn =
                    (RcmServer_MsgCreateFxn)OmapRpc_GetSvrMgrHandle;

            strncpy(obj->funcSigs[func].name, obj->rcmParams.fxns.elem[0].name,
                    OMAPRPC_MAX_CHANNEL_NAMELEN);
            obj->funcSigs[func].numParam = 0;
        }
        else {
            /* assign the other functions */
/*          obj->rcmParams.fxns.elem[func].name = fxns[func-1].signature.name; */
            obj->rcmParams.fxns.elem[func].name =
                    rcmParams->fxns.elem[func-1].name;
/*          obj->rcmParams.fxns.elem[func].addr.fxn =
                    (RcmServer_MsgFxn)fxns[func-1].function; */
            obj->rcmParams.fxns.elem[func].addr.fxn =
                    rcmParams->fxns.elem[func-1].addr.fxn;

            /* copy the signature */
/*          memcpy(&obj->funcSigs[func], &fxns[func-1].signature,
                    sizeof(OmapRpc_FuncSignature)); */
            memcpy(&obj->funcSigs[func], &fxnSigTab->table[func - 1],
                    sizeof(MmType_FxnSig));
        }
    }

    ServiceMgr_init();

    if (ServiceMgr_register(channelName, &obj->rcmParams) == TRUE) {
        System_printf("OMAPRPC: registered channel: %s\n", obj->channelName);

        obj->msgq = RPMessage_create(obj->port, NULL, NULL,&obj->localEndPt);

        if (obj->msgq == NULL) {
            goto unload;
        }

        /* set port to the created local endpoint */
        obj->port = obj->localEndPt;

        Task_Params_init(&taskParams);
        taskParams.instance->name = channelName;
        taskParams.stackSize = 0x2000; /* must cover all proxy stack usage */
        taskParams.priority = 1;   /* lowest priority thread */
        taskParams.arg0 = (UArg)obj;

        obj->exitSem = Semaphore_create(0, NULL, NULL);

        if (obj->exitSem == NULL) {
            goto unload;
        }

        obj->taskHandle = Task_create(omapRpcTask, &taskParams, NULL);

        if (obj->taskHandle == NULL) {
            goto unload;
        }
    }
    else {
        System_printf("OMAPRPC: FAILED to register channel: %s\n",
                obj->channelName);
    }

    System_printf("OMAPRPC: Returning Object %p\n", obj);
    return(obj);

unload:
    OmapRpc_deleteChannel(obj);
    return(NULL);
}

Int OmapRpc_deleteChannel(OmapRpc_Handle handle)
{
    OmapRpc_Object *obj = (OmapRpc_Object *)handle;

    if (obj == NULL) {
        return OmapRpc_E_FAIL;
    }

    System_printf("OMAPRPC: deleting channel %s\n", obj->channelName);
    obj->shutdown = TRUE;
    if (obj->msgq) {
        RPMessage_unblock(obj->msgq);
        if (obj->exitSem) {
            Semaphore_pend(obj->exitSem, BIOS_WAIT_FOREVER);
            RPMessage_delete(&obj->msgq);
            Semaphore_delete(&obj->exitSem);
        }
        if (obj->taskHandle) {
            Task_delete(&obj->taskHandle);
        }
    }
    if (obj->funcSigs)
        Memory_free(NULL, obj->funcSigs, sizeof(*obj->funcSigs)*(obj->numFuncs-1));
    if (obj->rcmParams.fxns.elem)
        Memory_free(NULL, obj->rcmParams.fxns.elem,
                    sizeof(obj->rcmParams.fxns.elem[0])*obj->numFuncs);

    Memory_free(NULL, obj, sizeof(*obj));
    return OmapRpc_S_SUCCESS;
}

#if 0
/*
 *  ======== OmapRpc_start ========
 */
Int OmapRpc_start(const String name, Int port, Int aryLen,
        OmapRpc_FuncSignature *sigAry)
{
    Int status = OmapRpc_S_SUCCESS;
    Task_Params taskParams;
    OmapRpc_Object *obj;

    /* create an instance */
    obj = Memory_calloc(NULL, sizeof(OmapRpc_Object), 0, NULL);

    if (obj == NULL) {
        System_printf("OMAPRPC: Failed to allocate memory for object!\n");
        status = OmapRpc_E_FAIL;
        goto leave;
    }

    obj->numFuncs = aryLen + 1;
    obj->shutdown = FALSE;
    obj->dstProc = MultiProc_getId("HOST");
    obj->port = port;
    strncpy(obj->channelName, name, OMAPRPC_MAX_CHANNEL_NAMELEN-1);
    obj->channelName[OMAPRPC_MAX_CHANNEL_NAMELEN-1]='\0';
    obj->srvDelCB = srvDelCBFunc;
    obj->funcSigs = Memory_alloc(NULL,
            sizeof(OmapRpc_FuncSignature) * obj->numFuncs, 0, NULL);

    if (obj->funcSigs == NULL) {
        System_printf("OMAPRPC: Failed to allocate signtures list!\n");
        goto unload;
    }

    /* setup the functions and signatures */
    for (func = 0; func < obj->numFuncs; func++) {
        if (func == 0) {
            /* assign the "first function" */
/*          strncpy(obj->funcSigs[func].name, obj->rcmParams.fxns.elem[0].name,
                    OMAPRPC_MAX_CHANNEL_NAMELEN); */
            strncpy(obj->funcSigs[func].name,
                    OmapRpc_Stringerize(OmapRpc_GetSvrMgrHandle),
                    OMAPRPC_MAX_CHANNEL_NAMELEN);
            obj->funcSigs[func].numParam = 0;
        }
        else {
            /* copy the signature */
            memcpy(&obj->funcSigs[func], &fxns[func-1].signature,
                    sizeof(OmapRpc_FuncSignature));
        }
    }

    obj->msgq = RPMessage_create(obj->port, NULL, NULL,&obj->localEndPt);

    if (obj->msgq == NULL) {
        goto unload;
    }

    Task_Params_init(&taskParams);
    taskParams.instance->name = channelName;
    taskParams.priority = 1;   /* Lowest priority thread */
    taskParams.arg0 = (UArg)obj;

    obj->exitSem = Semaphore_create(0, NULL, NULL);

    if (obj->exitSem == NULL) {
        goto unload;
    }

    obj->taskHandle = Task_create(omapRpcTask, &taskParams, NULL);

    if (obj->taskHandle == NULL) {
        goto unload;
    }

    System_printf("OMAPRPC: Returning Object %p\n", obj);
    return(obj);

leave:
    if (status < 0) {
        OmapRpc_deleteChannel(obj);
    }
    return(status);
}
#endif
