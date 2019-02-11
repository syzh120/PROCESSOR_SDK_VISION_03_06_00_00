/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
 *  ======== ServiceMgr.c ========
 *  Simple server that handles requests to create threads (services) by name
 *  and provide an endpoint to the new thread.
 *
 */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/grcm/RcmTypes.h>
#include <ti/grcm/RcmServer.h>

#include <string.h>
#include <stdlib.h>

#include <ti/ipc/rpmsg/RPMessage.h>
#include "rpmsg_omx.h"
#include "ServiceMgr.h"

#define  MAX_NAMELEN       64

/* This artificially limits the number of service instances on this core: */
#define  MAX_TUPLES        256
#define  FREE_TUPLE_KEY    0xFFFFFFFF

#define  MAX_SERVICES      4

/* ServiceMgr disconnect hook function */
static ServiceMgr_disconnectFuncPtr ServiceMgr_disconnectUserFxn = NULL;

struct ServiceDef {
    Char                   name[MAX_NAMELEN];
    RcmServer_Params       rcmServerParams;
    Bool                   taken;
};

struct ServiceDef serviceDefs[ServiceMgr_NUMSERVICETYPES];

struct Tuple {
    UInt32   key;
    UInt32   value;
};
struct Tuple Tuples[MAX_TUPLES];

typedef struct {
    Task_FuncPtr    fxn;
    Char            name[MAX_NAMELEN];
    Task_Params     params;
    UInt16          reserved;
    Bool            taken;
} ServiceMgr_ServiceTask;

static ServiceMgr_ServiceTask serviceTasks[MAX_SERVICES];


Void ServiceMgr_init()
{
    static Int  curInit = 0;
    UInt        i;

    if (curInit++ != 0) {
        return; /* module already initialized */
    }

    RcmServer_init();

    for (i = 0; i < ServiceMgr_NUMSERVICETYPES; i++) {
       serviceDefs[i].taken = FALSE;
    }

    for (i = 0; i < MAX_TUPLES; i++) {
       Tuples[i].key = FREE_TUPLE_KEY;
    }

    for (i = 0; i < MAX_SERVICES; i++) {
        serviceTasks[i].taken = FALSE;
        serviceTasks[i].fxn = NULL;
        serviceTasks[i].reserved = (UInt16) -1;
    }
}

UInt ServiceMgr_start(UInt16 reserved)
{
    UInt        i;
    UInt        count = 0;
    static Bool started = FALSE;

    if (started) {
        return 0;
    }

    for (i = 0; (i < MAX_SERVICES) && (serviceTasks[i].taken); i++) {
        Task_create(serviceTasks[i].fxn, &serviceTasks[i].params, NULL);
        count++;
    }

    return (count);
}

Bool ServiceMgr_registerSrvTask(UInt16 reserved, Task_FuncPtr func,
                                Task_Params *taskParams)
{
    UInt                    i;
    Bool                    found = FALSE;
    ServiceMgr_ServiceTask  *st;
    Task_Params             *params;

    /* Search the array for a free slot */
    for (i = 0; (i < MAX_SERVICES) && (found == FALSE); i++) {
        if (!serviceTasks[i].taken) {
            st = &serviceTasks[i];
            st->fxn = func;
            strncpy(st->name, taskParams->instance->name, MAX_NAMELEN-1);
            st->name[MAX_NAMELEN-1] = '\0';

            /* Deal with the Task_Params to avoid IInstance mismatch */
            params = &st->params;
            Task_Params_init(params);
            memcpy((Void *)(&params->arg0), &taskParams->arg0,
                        sizeof(*params) - sizeof(Void *));
            params->instance->name = st->name;

            st->reserved = reserved;
            st->taken = TRUE;
            found = TRUE;
            break;
        }
    }

    return (found);
}

Bool ServiceMgr_register(String name, RcmServer_Params *rcmServerParams)
{
    UInt              i;
    Bool              found = FALSE;
    struct ServiceDef *sd;

    if (strlen(name) >= MAX_NAMELEN) {
        System_printf("ServiceMgr_register: service name longer than %d\n",
                       MAX_NAMELEN );
    }
    else {
        /* Search the array for a free slot */
        for (i = 0; (i < ServiceMgr_NUMSERVICETYPES) && (found == FALSE); i++) {
            if (!serviceDefs[i].taken) {
                sd = &serviceDefs[i];
                strcpy(sd->name, name);
                sd->rcmServerParams = *rcmServerParams;
                sd->taken = TRUE;
                found = TRUE;
                break;
            }
        }
    }

    return(found);
}

Void ServiceMgr_send(Service_Handle srvc, Ptr data, UInt16 len)
{
    UInt32 local;
    UInt32 remote;
    struct omx_msg_hdr * hdr = (struct omx_msg_hdr *)data;
    UInt16 dstProc;

    /* Get reply endpoint and local address for sending: */
    remote  = RcmServer_getRemoteAddress(srvc);
    dstProc = RcmServer_getRemoteProc(srvc);
    local   = RcmServer_getLocalAddress(srvc);

    /* Set special rpmsg_omx header so Linux side can strip it off: */
    hdr->type    = OMX_RAW_MSG;
    hdr->len     = len;

    /* Send it off (and no response expected): */
    RPMessage_send(dstProc, remote, local, data, HDRSIZE+len);
}

Bool ServiceMgr_registerDisconnectFxn(Service_Handle srvc, Ptr data,
                                      ServiceMgr_disconnectFuncPtr func)
{
    if (func == NULL) {
        System_printf("ServiceMgr_registerDisconnectFxn: Invalid function.\n");
        return FALSE;
    }

    /* Register the user-supplied function */
    if (!ServiceMgr_disconnectUserFxn) {
        ServiceMgr_disconnectUserFxn = func;
    }
    return TRUE;
}

/* Tuple store/retrieve fxns:  */

static Bool storeTuple(UInt32 key, UInt32 value)
{
    UInt              i;
    Bool              stored = FALSE;

    if (key == FREE_TUPLE_KEY) {
        System_printf("storeTuple: reserved key %d\n", key);
    }
    else {
        /* Search the array for a free slot: */
        for (i = 0; (i < MAX_TUPLES) && (stored == FALSE); i++) {
           if (Tuples[i].key == FREE_TUPLE_KEY) {
               Tuples[i].key = key;
               Tuples[i].value = value;
               stored = TRUE;
               break;
           }
        }
    }

    return(stored);
}

static Bool removeTuple(UInt32 key, UInt32 * value)
{
    UInt              i;
    Bool              found = FALSE;

    /* Search the array for tuple matching key: */
    for (i = 0; (i < MAX_TUPLES) && (found == FALSE); i++) {
       if (Tuples[i].key == key) {
           found = TRUE;
           *value = Tuples[i].value;
           /* and free it... */
           Tuples[i].value = 0;
           Tuples[i].key = FREE_TUPLE_KEY;
           break;
       }
    }

    return(found);
}

UInt32 ServiceMgr_createService(Char * name, UInt32 * endpt)
{
    Int i;
    Int status = 0;
    struct ServiceDef *sd;
    RcmServer_Handle  rcmSrvHandle;

    for (i = 0; i < ServiceMgr_NUMSERVICETYPES; i++) {
       if (!strcmp(name, serviceDefs[i].name)) {
           sd = &serviceDefs[i];
           break;
       }
    }

    if (i >= ServiceMgr_NUMSERVICETYPES) {
       System_printf("createService: unrecognized service name: %s\n", name);
       return OMX_NOTSUPP;
    }

    /* Create the RcmServer instance. */
#if 0
    System_printf("createService: Calling RcmServer_create with name = %s\n"
                  "priority = %d\n"
                  "osPriority = %d\n"
                  "rcmServerParams.fxns.length = %d\n",
                  sd->name, sd->rcmServerParams.priority,
                  sd->rcmServerParams.osPriority,
                  sd->rcmServerParams.fxns.length);
#endif
    status = RcmServer_create(sd->name, &sd->rcmServerParams, &rcmSrvHandle);

    if (status < 0) {
        System_printf("createService: RcmServer_create() returned error %d\n",
                       status);
        return OMX_FAIL;
    }

    /* Get endpoint allowing clients to send messages to this new server: */
    *endpt = RcmServer_getLocalAddress(rcmSrvHandle);

    /* Store Server's endpoint with handle so we can cleanup on disconnect: */
    if (!storeTuple(*endpt, (UInt32)rcmSrvHandle))  {
        System_printf("createService: Limit reached on max instances!\n");
        RcmServer_delete(&rcmSrvHandle);
        return OMX_FAIL;
    }

    /* start the server */
    RcmServer_start(rcmSrvHandle);

    System_printf("createService: new OMX Service at endpoint: %d\n", *endpt);

    return OMX_SUCCESS;
}


UInt32 ServiceMgr_deleteService(UInt32 addr)
{
    Int status = 0;
    RcmServer_Handle  rcmSrvHandle;

    if (!removeTuple(addr, (UInt32 *)&rcmSrvHandle))  {
       System_printf("deleteService: could not find service instance at"
                     " address: 0x%x\n", addr);
       return OMX_FAIL;
    }

    /* Notify a ServiceMgr client of disconnection.
     * rcmSrvHandle is same as the ServiceMgr handle
     */
    if (ServiceMgr_disconnectUserFxn) {
        /* Pass NULL data for the moment */
        ServiceMgr_disconnectUserFxn(rcmSrvHandle, NULL);
    }

    /* Destroy the RcmServer instance. */
    status = RcmServer_delete(&rcmSrvHandle);
    if (status < 0) {
        System_printf("deleteService: RcmServer_delete() returned error %d\n",
                       status);
        return OMX_FAIL;
    }

    System_printf("deleteService: removed RcmServer at endpoint: %d\n", addr);

    return OMX_SUCCESS;
}
