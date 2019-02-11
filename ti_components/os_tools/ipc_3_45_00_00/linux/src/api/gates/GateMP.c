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
 *  ======== GateMP.c ========
 */
#include <ti/ipc/Std.h>

#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <assert.h>

#include <ti/ipc/GateMP.h>
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>

#include <GateMP_config.h>

#include <_GateMP.h>

/* Socket Protocol Family */
#include <net/rpmsg.h>

/* Socket utils: */
#include <SocketFxns.h>

#include <ladclient.h>
#include <_lad.h>


/* structure for GateMP module state */
typedef struct {
    GateMP_Params       defaultInstParams;
    /* Default instance creation parameters */
    GateMP_Handle       defaultGate;
    /* Handle to default gate */
    NameServer_Handle   nameServer;
    /* NameServer for GateMP instances */
    Bool                isStarted;
    /* Has GateMP been started */
    pthread_mutex_t     mutex;
    /* Mutex for use on local process to serialize access to gate obj */
    GateMP_Object **    remoteSystemGates;
    /* Remote system gates */
    Int                 numRemoteSystem;
    /* Number of remote system gates */
} GateMP_ModuleObject;

/* traces in this file are controlled via _GateMP_verbose */
Bool _GateMP_verbose = FALSE;
#define verbose _GateMP_verbose

/* Internal structure defining parameters for GateMP_Instance_init */
typedef struct {
    String name;                        /* Name of instance */
    UInt16 regionId;                    /* not used on host*/
    Ptr sharedAddr;                     /* not used on host*/
    GateMP_LocalProtect localProtect;   /* Local protection level  */
    GateMP_RemoteProtect remoteProtect; /* Remote protection level */
    UInt32 resourceId;                  /* resource id */
    Bool openFlag;                      /* Is this open or create? */
} _GateMP_Params;

static Int GateMP_getNumResources(GateMP_RemoteProtect type);
static Int GateMP_getFreeResource(GateMP_RemoteProtect type);
static Int GateMP_releaseResource(UInt id, GateMP_RemoteProtect type);
static GateMP_Handle _GateMP_create (const _GateMP_Params * params);
static Int GateMP_Instance_init(GateMP_Object *obj,
    const _GateMP_Params *params);
static Void GateMP_Instance_finalize(GateMP_Object *obj, Int status);

/* -----------------------------------------------------------------------------
 * Globals
 * -----------------------------------------------------------------------------
 */
static GateMP_ModuleObject GateMP_state =
{
    .remoteSystemGates  = NULL,
    .defaultGate        = NULL,
    .nameServer         = NULL,
    .mutex              = PTHREAD_MUTEX_INITIALIZER,
//    .gateMutex          = NULL,
//    .gateProcess        = NULL
};

static GateMP_ModuleObject *GateMP_module = &GateMP_state;

static GateMP_Params GateMP_defInstParams =
{
    .name           = NULL,
    .regionId       = 0,
    .sharedAddr     = NULL,
    .localProtect   = GateMP_LocalProtect_PROCESS,
    .remoteProtect  = GateMP_RemoteProtect_SYSTEM
};

/*
 *  ======== GateMP_attach ========
 *  Internal function.
 */
Int GateMP_attach(UInt16 procId)
{
    Int status;
    LAD_ClientHandle clHandle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    clHandle = LAD_findHandle();

    if (clHandle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE0("GateMP_attach: not connected to LAD\n");
        return (GateMP_E_RESOURCE);
    }

    cmd.cmd = LAD_GATEMP_ATTACH;
    cmd.clientId = clHandle;
    cmd.args.attach.procId = procId;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_attach: sending LAD command failed, "
                "status=%d\n", status);
        return (GateMP_E_FAIL);
    }

    if ((status = LAD_getResponse(clHandle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_attach: no LAD response, status=%d\n",
                status);
        return (GateMP_E_FAIL);
    }

    status = rsp.status;
    PRINTVERBOSE1("GateMP_attach: LAD response, status=%d\n", status)

    return (status);
}

/*
 *  ======== GateMP_detach ========
 *  Internal function.
 */
Int GateMP_detach(UInt16 procId)
{
    Int status;
    LAD_ClientHandle clHandle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    clHandle = LAD_findHandle();

    if (clHandle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE0("GateMP_detach: not connected to LAD\n");
        return (GateMP_E_RESOURCE);
    }

    cmd.cmd = LAD_GATEMP_DETACH;
    cmd.clientId = clHandle;
    cmd.args.detach.procId = procId;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_detach: sending LAD command failed, "
                "status=%d\n", status);
        return (GateMP_E_FAIL);
    }

    if ((status = LAD_getResponse(clHandle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_detach: no LAD response, status=%d\n",
                status);
        return (GateMP_E_FAIL);
    }

    status = rsp.status;
    PRINTVERBOSE1("GateMP_detach: LAD response, status=%d\n", status)

    return (status);
}

Int GateMP_start(Void)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "GateMP_start: can't find connection to daemon for pid %d\n",
           getpid())

        return -1;
    }

    cmd.cmd = LAD_GATEMP_START;
    cmd.clientId = handle;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateMP_start: sending LAD command failed, status=%d\n", status)
        return -1;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_start: no LAD response, status=%d\n", status)
        return -1;
    }

    status = rsp.gateMPStart.status;

    PRINTVERBOSE2(
      "GateMP_start: got LAD response for client %d, status=%d\n",
      handle, status)

    /*
     * Initialize module state. Note that Nameserver handles are compatible
     * across processes.
     */
    GateMP_module->nameServer = rsp.gateMPStart.nameServerHandle;


    /* allocate memory for remote system gate handles */
    if (status == GateMP_S_SUCCESS) {
        GateMP_module->numRemoteSystem =
            GateMP_getNumResources(GateMP_RemoteProtect_SYSTEM);
        if (GateMP_module->numRemoteSystem > 0) {
            GateMP_module->remoteSystemGates = calloc(1,
                GateMP_module->numRemoteSystem *
                sizeof(IGateProvider_Handle));

            if (GateMP_module->remoteSystemGates == NULL) {
                status = GateMP_E_MEMORY;
                PRINTVERBOSE0("GateMP_start: memory allocation failed")
            }
        }
        else {
            GateMP_module->remoteSystemGates = NULL;
        }
    }

    if (status == GateMP_S_SUCCESS) {
        /* Open default gate */
        status = GateMP_open("_GateMP_TI_dGate", &GateMP_module->defaultGate);
        if (status < 0) {
            PRINTVERBOSE1("GateMP_start: could not open default gate, \
                status=%d\n", status)
        }
    }

    /* in failure case, release acquired resources in reverse order */
    if (status < 0) {
        GateMP_stop();
    }

    GateMP_module->isStarted = TRUE;

    return status;
}

Int GateMP_stop(Void)
{
    Int status = GateMP_S_SUCCESS;

    PRINTVERBOSE0("GateMP_stop: entered\n")

    /* close the default gate */
    if (GateMP_module->defaultGate) {
        GateMP_close(&GateMP_module->defaultGate);
        GateMP_module->defaultGate = NULL;
    }

    /* free system gate array */
    if (GateMP_module->remoteSystemGates != NULL) {
        free(GateMP_module->remoteSystemGates);
        GateMP_module->remoteSystemGates = NULL;
    }

    GateMP_module->isStarted = FALSE;

    return status;
}

Void GateMP_Params_init(GateMP_Params *params)
{
    if (params != NULL) {
        memcpy(params, &GateMP_defInstParams, sizeof(GateMP_Params));
    }
    else {
        PRINTVERBOSE0("GateMP_Params_init: Params argument cannot be NULL")
    }

    return;
}

GateMP_Handle GateMP_create(const GateMP_Params *params)
{
    _GateMP_Params      _params;
    GateMP_Handle       handle = NULL;

    if (GateMP_module->isStarted == FALSE) {
        PRINTVERBOSE0("GateMP_create: GateMP module has not been started!")
    }
    else {
        memset(&_params, 0, sizeof(_GateMP_Params));
        memcpy(&_params, params, sizeof(GateMP_Params));

        handle = _GateMP_create(&_params);
    }

    return(handle);
}

static GateMP_Handle _GateMP_create(const _GateMP_Params *params)
{
    GateMP_Handle       handle = NULL;
    GateMP_Object *     obj = NULL;
    Int                 status;

    /* allocate the instance object */
    obj = (GateMP_Object *)calloc(1, sizeof(GateMP_Object));

    if (obj != NULL) {
        status = GateMP_Instance_init(obj, params);
        if (status < 0) {
            free(obj);
        }
        else {
            handle = (GateMP_Handle)obj;
        }
    }
    else {
        PRINTVERBOSE0("GateMP_create: Memory allocation failed")
    }

    return(handle);
}

Int GateMP_open(String name, GateMP_Handle *handle)
{
    Int             status = GateMP_S_SUCCESS;
    UInt32          len;
    UInt32          nsValue[4];
    GateMP_Object * obj = NULL;
    UInt32          arg;
    UInt32          mask;
    UInt32          creatorProcId;
    _GateMP_Params  params;

    /* assert that a valid pointer has been supplied */
    if (handle == NULL) {
        PRINTVERBOSE0("GateMP_open: handle cannot be null")
        status = GateMP_E_INVALIDARG;
    }

    if (status == GateMP_S_SUCCESS) {
        len = sizeof(nsValue);

        status = NameServer_get(GateMP_module->nameServer, name, &nsValue,
            &len, NULL);

        if (status < 0) {
            *handle = NULL;
            status = GateMP_E_NOTFOUND;
        }
        else if (len != sizeof(nsValue)) {
            *handle = NULL;
            status = GateMP_E_NOTFOUND;
            PRINTVERBOSE0("GateMP configuration not valid for hostSupport. "
                "Try adding hostSupport to your config if it is needed.\n");
        }
        else {
            arg = nsValue[2];
            mask = nsValue[3];
            creatorProcId = nsValue[1] >> 16;
        }
    }

    if (status == GateMP_S_SUCCESS) {
        /*
         * The least significant bit of nsValue[1] == 0 means its a
         * local (private) GateMP, otherwise its a remote (shared) GateMP.
         */
        if ((nsValue[1] & 0x1) == 0) {
            if ((nsValue[1] >> 16) != MultiProc_self()) {
                /* error: trying to open another processor's private gate */
                *handle = NULL;
                PRINTVERBOSE0("GateMP_open: cannot open private gate from \
                    another processor")
                status = GateMP_E_FAIL;
            }
            else if (nsValue[0] != getpid()) {
                /* error: trying to open another process's private gate */
                *handle = NULL;
                PRINTVERBOSE0("GateMP_open: cannot open private gate from \
                    another process")
                status = GateMP_E_FAIL;
            }
        }
    }

    if (status == GateMP_S_SUCCESS) {
        /* local gate */
        if (GETREMOTE(mask) == GateMP_RemoteProtect_NONE) {
            if (creatorProcId != MultiProc_self()) {
                status = GateMP_E_FAIL;
            }
            else {
                *handle = (GateMP_Handle)arg;
                obj = (GateMP_Object *)(*handle);
                pthread_mutex_lock(&GateMP_module->mutex);
                obj->numOpens++;
                pthread_mutex_unlock(&GateMP_module->mutex);
            }
        }
        else {
            /* remote case */
            switch (GETREMOTE(mask)) {
                case GateMP_RemoteProtect_SYSTEM:
                case GateMP_RemoteProtect_CUSTOM1:
                case GateMP_RemoteProtect_CUSTOM2:
                    obj = GateMP_module->remoteSystemGates[arg];
                    break;

                default:
                    status = GateMP_E_FAIL;
                    PRINTVERBOSE0("GateMP_open: unsupported remote protection \
                        type")
                    break;
            }

            /*  If the object is NULL, then it must have been created
             *  on a remote processor or in another process on the
             *  local processor. Need to create a local object. This is
             *  accomplished by setting the openFlag to TRUE.
             */
            if (status == GateMP_S_SUCCESS) {
                if (obj == NULL) {
                    /* create a GateMP object with the openFlag set to true */
                    params.name = NULL;
                    params.openFlag = TRUE;
                    params.sharedAddr = NULL;
                    params.resourceId = arg;
                    params.localProtect = GETLOCAL(mask);
                    params.remoteProtect = GETREMOTE(mask);

                    obj = (GateMP_Object *)_GateMP_create(&params);

                    if (obj == NULL) {
                        status = GateMP_E_FAIL;
                    }
                }
                else {
                    pthread_mutex_lock(&GateMP_module->mutex);
                    obj->numOpens++;
                    pthread_mutex_unlock(&GateMP_module->mutex);
                }
            }

            /* Return the "opened" GateMP instance  */
            *handle = (GateMP_Handle)obj;
        }
    }

    return status;
}

GateMP_Handle GateMP_getDefaultRemote()
{
    return(GateMP_module->defaultGate);
}

GateMP_LocalProtect GateMP_getLocalProtect(GateMP_Handle handle)
{
    GateMP_Object *obj;

    obj = (GateMP_Object *)handle;
    return(obj->localProtect);
}

GateMP_RemoteProtect GateMP_getRemoteProtect(GateMP_Handle handle)
{
    GateMP_Object *obj;

    obj = (GateMP_Object *)handle;
    return (obj->remoteProtect);
}

static Int GateMP_getNumResources(GateMP_RemoteProtect type)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "GateMP_getNumResources: can't find connection to daemon for pid %d\n",
           getpid())

        return -1;
    }

    cmd.cmd = LAD_GATEMP_GETNUMRESOURCES;
    cmd.clientId = handle;
    cmd.args.gateMPGetNumResources.type = type;


    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateMP_getNumResources: sending LAD command failed, status=%d\n", status)
        return -1;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_getNumResources: no LAD response, status=%d\n", status)
        return -1;
    }

    status = rsp.gateMPGetNumResources.status;

    PRINTVERBOSE2(
      "GateMP_getNumResources: got LAD response for client %d, status=%d\n",
      handle, status)


    return (rsp.gateMPGetNumResources.value);
}

static Int GateMP_getFreeResource(GateMP_RemoteProtect type)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "GateMP_getFreeResource: can't find connection to daemon for pid %d\n",
           getpid())

        return -1;
    }

    cmd.cmd = LAD_GATEMP_GETFREERESOURCE;
    cmd.clientId = handle;
    cmd.args.gateMPGetFreeResource.type = type;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateMP_getFreeResource: sending LAD command failed, status=%d\n", status)
        return -1;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_getFreeResource: no LAD response, status=%d\n", status)
        return -1;
    }

    status = rsp.gateMPGetFreeResource.status;

    PRINTVERBOSE2(
      "GateMP_getNumResources: got LAD response for client %d, status=%d\n",
      handle, status)

    return (rsp.gateMPGetFreeResource.id);
}

static Int GateMP_releaseResource(UInt id, GateMP_RemoteProtect type)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "GateMP_releaseResource: can't find connection to daemon for pid %d\n",
           getpid())

        return -1;
    }

    cmd.cmd = LAD_GATEMP_RELEASERESOURCE;
    cmd.clientId = handle;
    cmd.args.gateMPReleaseResource.type = type;
    cmd.args.gateMPReleaseResource.id   = id;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateMP_releaseResource: sending LAD command failed, status=%d\n", status)
        return -1;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_releaseResource: no LAD response, status=%d\n", status)
        return -1;
    }

    status = rsp.gateMPReleaseResource.status;

    PRINTVERBOSE2(
      "GateMP_releaseResource: got LAD response for client %d, status=%d\n",
      handle, status)

    return (status);
}

Bool GateMP_isSetup(Void)
{
    Int status;
    LAD_ClientHandle handle;
    struct LAD_CommandObj cmd;
    union LAD_ResponseObj rsp;

    handle = LAD_findHandle();
    if (handle == LAD_MAXNUMCLIENTS) {
        PRINTVERBOSE1(
          "GateMP_isSetup: can't find connection to daemon for pid %d\n",
           getpid())

        return -1;
    }

    cmd.cmd = LAD_GATEMP_ISSETUP;
    cmd.clientId = handle;
    cmd.args.gateMPIsSetup.result = FALSE;

    if ((status = LAD_putCommand(&cmd)) != LAD_SUCCESS) {
        PRINTVERBOSE1(
          "GateMP_isSetup: sending LAD command failed, status=%d\n", status)
        return -1 ;
    }

    if ((status = LAD_getResponse(handle, &rsp)) != LAD_SUCCESS) {
        PRINTVERBOSE1("GateMP_isSetup: no LAD response, status=%d\n", status)
        return -1;
    }

    status = rsp.gateMPIsSetup.status;

    PRINTVERBOSE2(
      "GateMP_isSetup: got LAD response for client %d, status=%d\n",
      handle, status)

    assert(status == GateMP_S_SUCCESS);

    return (rsp.gateMPIsSetup.result);
}

Int GateMP_close(GateMP_Handle *handle)
{
    GateMP_Object * obj;
    Int             status = GateMP_S_SUCCESS;

    obj = (GateMP_Object *)(*handle);

    pthread_mutex_lock(&GateMP_module->mutex);

    /*  Cannot call with the numOpens equal to zero.  This is either
     *  a created handle or been closed already.
     */
    if (obj->numOpens == 0) {
        status = GateMP_E_INVALIDSTATE;
    }

    if (status == GateMP_S_SUCCESS) {
        obj->numOpens--;

        /*  If the count is zero and the gate is opened, then this
         *  object was created in the open (i.e. the create happened
         *  on a remote processor or another process).
         */
        if ((obj->numOpens == 0) && (obj->objType == Ipc_ObjType_OPENDYNAMIC)) {
            GateMP_delete(handle);
        }
        else {
            *handle = NULL;
        }
    }

    pthread_mutex_unlock(&GateMP_module->mutex);

    return(status);
}

Int GateMP_delete(GateMP_Handle *handlePtr)
{
    Int               status = GateMP_S_SUCCESS;

    if ((handlePtr == NULL) || (*handlePtr == NULL)) {
        status =  GateMP_E_INVALIDARG;
    }
    else {
        GateMP_Instance_finalize((GateMP_Object *)(*handlePtr), 0);
        free(*handlePtr);
        *handlePtr = NULL;
    }

    return status;
}

static Int GateMP_Instance_init(GateMP_Object *obj,
    const _GateMP_Params *params)
{
    GateMP_RemoteSystemProxy_Params     systemParams;
    UInt32                              nsValue[4];

    obj->resourceId = (UInt)-1;

    /* TODO: create/open the local gate instance */
    obj->localGate = NULL;

    /* open GateMP instance */
    if (params->openFlag == TRUE) {
        /* all open work done here except for remote gateHandle */
        obj->localProtect  = params->localProtect;
        obj->remoteProtect = params->remoteProtect;
        obj->nsKey         = 0;
        obj->numOpens      = 1;

        obj->objType       = Ipc_ObjType_OPENDYNAMIC;
    }

    /* create GateMP instance */
    else {
        obj->localProtect  = params->localProtect;
        obj->remoteProtect = params->remoteProtect;
        obj->nsKey         = 0;
        obj->numOpens      = 0;

        if (obj->remoteProtect == GateMP_RemoteProtect_NONE) {
            /* TODO: create a local gate */
            obj->gateHandle = obj->localGate;

            /* create a local gate allocating from the local heap */
            obj->objType = Ipc_ObjType_LOCAL;
            obj->arg = (Bits32)obj;
            obj->mask = SETMASK(obj->remoteProtect, obj->localProtect);
            obj->creatorProcId = MultiProc_self();

            if (params->name != NULL) {
                /*  nsv[0]       : creator process id
                 *  nsv[1](31:16): creator procId
                 *  nsv[1](15:0) : 0 = local gate, 1 = remote gate
                 *  nsv[2]       : local gate object
                 *  nsv[3]       : protection mask
                 */
                nsValue[0] = getpid();
                nsValue[1] = MultiProc_self() << 16;
                nsValue[2] = obj->arg;
                nsValue[3] = obj->mask;
                obj->nsKey = NameServer_add(GateMP_module->nameServer,
                        params->name, &nsValue, sizeof(nsValue));
                if (obj->nsKey == NULL) {
                    PRINTVERBOSE0("GateMP_Instance_init: NameServer_add failed")
                    return (GateMP_E_FAIL);
                }
            }

            /* nothing else to do for local gates */
            return(0);
        }

        obj->objType = Ipc_ObjType_CREATEDYNAMIC;
    }

    /* proxy work for open and create done here */
    switch (obj->remoteProtect) {
        /* TODO: implement other types of remote protection */
        case GateMP_RemoteProtect_SYSTEM:
        case GateMP_RemoteProtect_CUSTOM1:
        case GateMP_RemoteProtect_CUSTOM2:
            if (obj->objType == Ipc_ObjType_OPENDYNAMIC) {
                /* resourceId set by open call */
                obj->resourceId = params->resourceId;
            }
            else {
                /* created instance */
                obj->resourceId = GateMP_getFreeResource(obj->remoteProtect);
                if (obj->resourceId == -1) {
                    return (GateMP_E_RESOURCE);
                }
            }

            /* create the proxy object */
            GateMP_RemoteSystemProxy_Params_init(&systemParams);
            systemParams.resourceId = obj->resourceId;
            systemParams.openFlag = (obj->objType == Ipc_ObjType_OPENDYNAMIC);
            //systemParams.sharedAddr = obj->proxyAttrs;

            /*
             * TODO: Currently passing in localProtect instead of localGate,
             * since existing GateHWSpinlock.h defines it this way
             */
            obj->gateHandle = (IGateProvider_Handle)
                GateMP_RemoteSystemProxy_create(obj->localProtect,
                    &systemParams);

            if (obj->gateHandle == NULL) {
                PRINTVERBOSE0("GateMP_Instance_init: failed to create proxy\n");
                return(GateMP_E_FAIL);
            }

            /* store the object handle in the gate array */
            GateMP_module->remoteSystemGates[obj->resourceId] = obj;
            break;

        default:
            break;
    }

    /* add name/attrs to NameServer table */
    if (obj->objType != Ipc_ObjType_OPENDYNAMIC) {
        obj->arg = obj->resourceId;
        obj->mask = SETMASK(obj->remoteProtect, obj->localProtect);

        if (params->name != NULL) {
            /*  nsv[0]       : creator pid
             *  nsv[1](31:16): creator procId
             *  nsv[1](15:0) : 0 = local gate, 1 = remote gate
             *  nsv[2]       : resource id
             *  nsv[3]       : protection mask
             */
            nsValue[0] = getpid();
            nsValue[1] = MultiProc_self() << 16 | 1;
            nsValue[2] = obj->resourceId;
            nsValue[3] = obj->mask;
            obj->nsKey = NameServer_add(GateMP_module->nameServer,
                    params->name, &nsValue, sizeof(nsValue));

            if (obj->nsKey == NULL) {
                PRINTVERBOSE0("GateMP_Instance_init: NameServer_add failed")
                return (GateMP_E_FAIL);
            }
        }
    }

    return (GateMP_S_SUCCESS);
}

static Void GateMP_Instance_finalize(GateMP_Object *obj, Int status)
{
    GateMP_Object ** remoteGates = NULL;

    /* remove from NameServer */
    if (obj->nsKey != 0) {
        NameServer_removeEntry(GateMP_module->nameServer, obj->nsKey);
        obj->nsKey = 0;
    }

    /* delete the remote gate */
    switch (obj->remoteProtect) {

        case GateMP_RemoteProtect_SYSTEM:
        case GateMP_RemoteProtect_CUSTOM1:
        case GateMP_RemoteProtect_CUSTOM2:
            if (obj->gateHandle != NULL) {
                GateMP_RemoteSystemProxy_delete(
                        (GateMP_RemoteSystemProxy_Handle *)&obj->gateHandle);
            }
            remoteGates = GateMP_module->remoteSystemGates;
            break;

        case GateMP_RemoteProtect_NONE:
            /*  nothing else to finalize */
            return;

        default:
            /* Nothing to do */
            break;
    }

    /* TODO: close/delete local gate */

    /* clear the handle array entry in local memory */
    if (remoteGates && (obj->resourceId != (UInt)-1)) {
        remoteGates[obj->resourceId] = NULL;
    }

    if ((obj->objType != Ipc_ObjType_OPENDYNAMIC)
        && (obj->resourceId != (UInt)-1)) {
        GateMP_releaseResource(obj->resourceId, obj->remoteProtect);
    }

}

IArg GateMP_enter(GateMP_Handle handle)
{
    GateMP_Object * obj;
    IArg            key;

    obj = (GateMP_Object *)handle;
    key = IGateProvider_enter(obj->gateHandle);

    return(key);
}

Void GateMP_leave(GateMP_Handle handle, IArg key)
{
    GateMP_Object *obj;

    obj = (GateMP_Object *)handle;
    IGateProvider_leave(obj->gateHandle, key);
}
