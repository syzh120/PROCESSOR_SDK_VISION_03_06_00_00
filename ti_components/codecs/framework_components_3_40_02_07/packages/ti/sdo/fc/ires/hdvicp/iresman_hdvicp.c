/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 *
 */
/*
 *  ======== iresman_hdvicp.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_hdvicp_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>

#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>
#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_hdvicp.h"
#include "iresman_protocol_hdvicp.h"
#include "ires_hdvicp.h"
#include "_hdvicp.h"

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ti/sdo/fc/utils/shm.h>


extern int VICP_init();
extern int VICP_exit();

#endif

/* can't make this static, as it's used throughout this package */

#define IRESMAN_HDVICP_RESOURCEFREE 0xFFFF

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_HDVICP_InternalState {

    int numOpens;

    int resourceBusy[IRES_HDVICP_MAXRESOURCES]; /**< Busy-status of HDVICP
                                                 *   resources.
                                                 */
    int refCount[IRES_HDVICP_MAXRESOURCES];     /**< Reference count
                                                 *   when multiple
                                                 *   requestors from
                                                 *   the same scratch
                                                 *   group have been
                                                 *   granted the
                                                 *   resource.
                                                 */
    int numResources;                           /**< Number of HDVICP resources
                                                 *   being managed.
                                                 */
    int sharedMemId;
} IRESMAN_HDVICP_InternalState;

extern UInt32 _HDVICP_ipcKeyBase;

__FAR__ static IRESMAN_PersistentAllocFxn * allocFxn; /**< Memory alloc func. */
__FAR__ static IRESMAN_PersistentFreeFxn * freeFxn;   /**< Memory free func. */
/*
 * Flag indicating if the resource manager is initialized
 */
__FAR__ static unsigned int _initialized = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
__FAR__ static IRESMAN_HDVICP_InternalState * _resmanInternalState;

static void getInternalState();
static void setInternalState();
static void freeInternalState();

extern __FAR__ unsigned int _HDVICP_NUMRESOURCES;

__FAR__ Registry_Desc ti_sdo_fc_ires_hdvicp_desc;
__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

#ifdef xdc_target__os_Linux
__FAR__ static IGateProvider_Handle gate = NULL;
#endif

/*
 *  ======== IRESMAN_HDVICP_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_HDVICP_getProtocolName()
{
    if  (regInit) {
        Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP_getProtocolName> Enter");

        Log_print1(Diags_EXIT, "[+X] IRESMAN_HDVICP_getProtocolName> Exit "
                "(name=%s)", (IArg)(IRESMAN_HDVICP_CONSTRUCTFXNS.getName()));
    }

    return (IRESMAN_HDVICP_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_HDVICP_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_HDVICP_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if (regInit)
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP_getProtocolRevision> Enter");

    version = IRESMAN_HDVICP_CONSTRUCTFXNS.getRevision();

    if (regInit)
    Log_print3(Diags_EXIT,
            "[+X] IRESMAN_HDVICP_getProtocolRevision> Exit(version=(%d.%d.%d))",
            (IArg)(version->Major), (IArg)(version->Source),
            (IArg)(version->Radius));

    return (version);
}

/*
 *  ======== IRESMAN_HDVICP_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_HDVICP_init(IRESMAN_Params * initArgs)
{
    IRESMAN_HdVicpParams * resmanArgs = (IRESMAN_HdVicpParams *)initArgs;
    Registry_Result result;

    if (!regInit) {
        /*
         *  Enable logging. We only want to do this once, since there is
         *  no Registry_removeModule().
         */
        result = Registry_addModule(&ti_sdo_fc_ires_hdvicp_desc,
                HDVICP_MODNAME);

        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_init();
            FCSettings_setDiags(HDVICP_MODNAME);
        }
        regInit = 1;
    }

    Log_print1(Diags_ENTRY, "[+E] IRESMAN_HDVICP_init> Enter (initArgs=0x%x)",
            (IArg)initArgs);

    Assert_isTrue(initArgs != NULL, (Assert_Id)NULL);

    /* Check if already initialized */
    if (_initialized) {
       Log_print0(Diags_EXIT,
               "[+X] IRESMAN_HDVICP_init> Exit (status=IRES_EEXISTS)");

       return (IRES_EEXISTS);
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    allocFxn = resmanArgs->baseConfig.allocFxn;
    freeFxn = resmanArgs->baseConfig.freeFxn;

#ifdef xdc_target__os_Linux
    if (gate == NULL) {
        OsalSupport_createGate(_HDVICP_ipcKeyBase);
    }
    if (gate == NULL) {
        Log_print0(Diags_USER7,
                "[+7] IRESMAN_VICP2_init> Failed to create gate");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_VICP2_init> Exit (status=IRES_EFAIL)");

        return (IRES_EFAIL);
    }
#endif

    getInternalState();

    if ((NULL == _resmanInternalState) ||
            (_resmanInternalState->sharedMemId == -1)) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_VICP2_init> Failed to obtain Internal state "
                "Object");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_VICP2_init> Exit (status=IRES_EFAIL)");

        return (IRES_EFAIL);
    }

    _resmanInternalState->numOpens++;

    if (sizeof(IRESMAN_Params) == resmanArgs->baseConfig.size) {
        _resmanInternalState->numResources = _HDVICP_NUMRESOURCES;
    }
    else {
        _resmanInternalState->numResources = resmanArgs->numResources;
    }

    Assert_isTrue(
            _resmanInternalState->numResources <= IRES_HDVICP_MAXRESOURCES,
            (Assert_Id)NULL);

    /* Set Initalized flag to 1 if successful */
     _initialized = 1;

     Log_print0(Diags_EXIT, "[+X] IRESMAN_HDVICP_init> Exit (status=IRES_OK)");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_HDVICP_exit()
{
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_HDVICP_exit> Enter");

    if (!(_initialized)) {
        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_exit> Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

#ifdef xdc_target__os_Linux
    if (gate) {
        OsalSupport_deleteGate(gate);
        gate = NULL;
    }
#endif

    /* Set the initialized flag to zero again */
    _initialized = 0;

    _resmanInternalState->numOpens--;

    freeInternalState();

    Log_print0(Diags_EXIT, "[+X] IRESMAN_HDVICP_exit> Exit (status=IRES_OK)");

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Handle IRESMAN_HDVICP_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec protocolMemRecs[IRES_HDVICP_MAXRESOURCES];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs = 0;
    Int i;
    Int Id = -1;
    IRESMAN_HDVICP_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;

    /*
     * Cast the protocolArgs
     */
    IRES_HDVICP_ProtocolArgs * configArgs =
            (IRES_HDVICP_ProtocolArgs *) protocolArgs;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY,
            "[+E] IRESMAN_HDVICP_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)", (IArg)protocolArgs, (IArg)scratchGroupId);


    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP_getHandles> RMAN register for HDVICP resource "
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources");

        return (NULL);
    }

    if (0 == _resmanInternalState->numResources) {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP_getHandles> Trying to request HDVICP resource "
                "on a device with 0 HDVICP resources. Check device "
                "configuration.");

        return (NULL);
    }

    if (configArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    /*
     * Get IRES_HDVICP handle's memory requirements
     */
    numMemRecs = IRESMAN_HDVICP_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    Assert_isTrue(numMemRecs <= IRES_HDVICP_MAXRESOURCES, (Assert_Id)NULL);

    /*
     * Use the protocolArgs to determine which resource to allocate
     */
    if (configArgs->id == IRES_HDVICP_ID_ANY) {

        Log_print0(Diags_USER4,
                "[+4] IRESMAN_HDVICP_getHandles> ANY Resource requested");

        for (i = (_resmanInternalState->numResources - 1); i >= 0; i--) {

            /*
             * If the requested resource is free or if the same scratch group
             * requests it return the Id
             * If the resourceBusy status is set to -1, this implies that the
             * resource has been granted persistently
             */
            if ((IRESMAN_HDVICP_RESOURCEFREE ==
                    _resmanInternalState->resourceBusy[i])) {

                _resmanInternalState->resourceBusy[i] = scratchGroupId;

                Id = i;

                _resmanInternalState->refCount[i] = 1;

                Log_print1(Diags_USER4,
                        "[+4] IRESMAN_HDVICP_getHandles> HDVICP Resource %d is "
                        "available", (IArg)Id);

                break;
            }
            else if ((_resmanInternalState->resourceBusy[i] != -1 ) &&
                    (_resmanInternalState->resourceBusy[i] == scratchGroupId)) {
                _resmanInternalState->refCount[i]++;

                Id = i;

                Log_print2(Diags_USER4,
                        "[+4] IRESMAN_HDVICP_getHandles> HDVICP Resource %d is "
                        "available to scratch group %d",
                        (IArg)Id, (IArg)scratchGroupId);

                break;
            }
        }

        if  (Id == -1) {
            *status = IRES_ENORESOURCE;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_HDVICP_getHandles> Error obtaining free HDVICP"
                    "resource.");

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }
    }
    else {

        switch (configArgs->id) {

            case IRES_HDVICP_ID_0 :
                Id = 0;
                if (Id >= _resmanInternalState->numResources)  {

                    *status = IRES_ENORESOURCE;
                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_HDVICP_getHandles> Did not recognize "
                            "HDVICP resource request.");

                    Log_print0(Diags_EXIT,
                            "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                            "status=IRES_ENORESOURCE)");

                    return (NULL);
               }
               break;

            case IRES_HDVICP_ID_1:
                Id = 1;
                if (Id >= _resmanInternalState->numResources) {

                    *status = IRES_ENORESOURCE;
                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_HDVICP_getHandles> Did not recognize "
                            "HDVICP resource request.");

                    Log_print0(Diags_EXIT,
                            "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                            "status=IRES_ENORESOURCE)");

                    return (NULL);
               }
               break;

            default:
                *status = IRES_ENORESOURCE;
                Log_print0(Diags_USER7,
                        "[+7] IRESMAN_HDVICP_getHandles> Did not recognize HDVICP "
                        "resource request.");

                Log_print0(Diags_EXIT,
                        "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                        "status=IRES_ENORESOURCE)");

                return (NULL);
        }

        Log_print1(Diags_USER4,
                "[+4] IRESMAN_HDVICP_getHandles> Specific HDVICP Resource requ"
                "ested "                "%d", (IArg)Id);

        if ((IRESMAN_HDVICP_RESOURCEFREE ==
                _resmanInternalState->resourceBusy[Id])) {
            _resmanInternalState->resourceBusy[Id] = scratchGroupId;
            _resmanInternalState->refCount[Id] = 1;

            Log_print1(Diags_USER4,
                    "[+4] IRESMAN_HDVICP_getHandles> HDVICP Resource %d available",
                    (IArg)Id);
        }
        else if ((_resmanInternalState->resourceBusy[Id] != -1) &&
                (_resmanInternalState->resourceBusy[Id] == scratchGroupId)) {
            _resmanInternalState->refCount[Id]++;

            Log_print2(Diags_USER4,
                    "[+4] IRESMAN_HDVICP_getHandles> HDVICP Resource %d available "
                    "to scratch group %d", (IArg)Id, (IArg)scratchGroupId);
        }
        else {
            *status = IRES_ENORESOURCE;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_HDVICP_getHandles> Error obtaining HDVICP"
                    "resource.");

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }
    }

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_HDVICP_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == allocFxn(&constructHandleMemRec, 1)) {
        *status =  IRES_ENOMEM;

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_HDVICP_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(constructHandleMemRec.size),
                (IArg)(constructHandleMemRec.alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        _resmanInternalState->refCount[Id]-- ;
        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] =
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }

    Assert_isTrue(IALG_EXTERNAL == constructHandleMemRec.space,
            (Assert_Id)NULL);
    constructArgs = constructHandleMemRec.base;

    /*
     * Populate the construct args
     */
    (constructArgs->args).size = sizeof(IRESMAN_HDVICP_ConstructHandleArgs);
    constructArgs->id = Id;

    constructArgs->info = NULL;

    if (-1 == scratchGroupId) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    /*
     * Obtain memory resources to build the handle
     */
    IRESMAN_HDVICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory
     */
    if (FALSE == allocFxn(protocolMemRecs, numMemRecs)) {

        *status = IRES_ENOMEM;

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_HDVICP_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(protocolMemRecs->size),
                (IArg)(protocolMemRecs->alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        freeFxn(&constructHandleMemRec, 1);

        _resmanInternalState->refCount[Id]-- ;
        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] =
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }

    /*
     * Use the CONSTRUCT interface of the protocol implementation to
     * construct the handle within the allocated resource
     */
     resourceHandle = IRESMAN_HDVICP_CONSTRUCTFXNS.constructHandle(
            protocolArgs, protocolMemRecs,
            (IRESMAN_ConstructArgs *)constructArgs, status);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    freeFxn(&constructHandleMemRec, 1);

    if (IRES_OK != *status) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP_getHandles> Error freeing memory ");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        _resmanInternalState->refCount[Id]-- ;

        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] =
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }
    else {

        Log_print2(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_getHandles> Exit (handle=0x%x, status=0x%x)",
                (IArg)resourceHandle, (IArg)(*status));

        resDesc->handle = resourceHandle;

        resDesc->revision->Major = 1;
        resDesc->revision->Source = 0;
        resDesc->revision->Radius = 0;

        return (resourceHandle);
    }
}

/*
 *  ======== IRESMAN_HDVICP_freeHandles ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_HDVICP_freeHandles(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor * resDesc,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[IRES_HDVICP_MAXRESOURCES];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    Int Id = -1;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;
    IRES_HDVICP_Handle resourceHandle = (IRES_HDVICP_Handle)
            algResourceHandle;
    /*
     * Cast the protocolArgs
     */
    IRES_HDVICP_ProtocolArgs * configArgs =
            (IRES_HDVICP_ProtocolArgs *) protocolArgs;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);
    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRESMAN_HDVICP_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)",
            (IArg)algResourceHandle, (IArg)protocolArgs,
            (IArg)scratchGroupId);

    if (_initialized != 1) {
        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP_freeHandles> RMAN register for HDVICP resource "
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources");

        status =  IRES_ENORESOURCE;

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_freeHandles> Exit (status=IRES_ENORESOURCE)");

        return (status);
    }

    if (configArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    /*
     * Use the protocolArgs to determine which resource to free
     */
    Id = resourceHandle->id;

    if ((Id >= _resmanInternalState->numResources) ||
            (_resmanInternalState->resourceBusy[Id] != scratchGroupId)) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_HDVICP_freeHandles> Error freeing HDVICP resource. "
                "Resource already free");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_HDVICP_freeHandles> Exit (status=IRES_ENORESOURCE)");

        return (IRES_ENORESOURCE);
    }
    else {
        _resmanInternalState->refCount[Id]-- ;

        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] =
                    IRESMAN_HDVICP_RESOURCEFREE;
        }
    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_HDVICP_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_HDVICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_HDVICP_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_HDVICP_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    freeFxn(resourceMemRecs, numMemRecs);

    Log_print1(Diags_EXIT, "[+X] IRESMAN_HDVICP_freeHandles> Exit (status=%d)",
            (IArg)status);

    return (status);
}

static void getInternalState()
{
#ifdef xdc_target__os_Linux
    Int sharedMemId = -1;

    _resmanInternalState = (IRESMAN_HDVICP_InternalState *)SHM_getObj(gate,
            sizeof(IRESMAN_HDVICP_InternalState), _HDVICP_LOCKID,
            &setInternalState, &sharedMemId);
    _resmanInternalState->sharedMemId = sharedMemId;
#else
    __FAR__ static IRESMAN_HDVICP_InternalState _HDVICP_internalState;

    _resmanInternalState = (IRESMAN_HDVICP_InternalState *)
            &_HDVICP_internalState;
    setInternalState(_resmanInternalState);
    _resmanInternalState->sharedMemId = 0;
#endif
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState()
{
#ifdef xdc_target__os_Linux


    SHM_freeObj(_resmanInternalState, _resmanInternalState->sharedMemId);
#else
    _resmanInternalState = NULL;
#endif
}

/*
 *  ======= setInternalState =======
 */
static Void setInternalState(Void * addr)
{
    IRESMAN_HDVICP_InternalState * intState =
            (IRESMAN_HDVICP_InternalState *)addr;
    Int i;

    if (NULL != intState) {
        intState->numOpens = 0;

        for (i = 0; i < IRES_HDVICP_MAXRESOURCES; i++) {
            intState->resourceBusy[i] = IRESMAN_HDVICP_RESOURCEFREE;
            intState->refCount[i] = 0;
        }

#ifdef xdc_target__os_Linux
        VICP_init();
#endif
    }
}

IRESMAN_Fxns IRESMAN_HDVICP =  {
    IRESMAN_HDVICP_getProtocolName,
    IRESMAN_HDVICP_getProtocolRevision,
    IRESMAN_HDVICP_init,
    IRESMAN_HDVICP_exit,
    IRESMAN_HDVICP_getHandles,
    IRESMAN_HDVICP_freeHandles,
    NULL,
    NULL
};

IRESMAN_HdVicpParams IRESMAN_HDVICP_DEFAULTPARAM;

IRESMAN_Fxns * HDVICP_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_HDVICP));
}


IRESMAN_Params * HDVICP_getDefaultParams()
{
    IRESMAN_HDVICP_DEFAULTPARAM.baseConfig.size = sizeof(IRESMAN_Params);

    /* Don't need to populate this, xdt will figure this one out */
    /* IRESMAN_HDVICP_DEFAULTPARAM->numResources = 2;*/
    return ((IRESMAN_Params *)&IRESMAN_HDVICP_DEFAULTPARAM);
}
