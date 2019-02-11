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
 *  ======== iresman_tiledmemory.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_tiledmem_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Registry.h>
#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>
#include <ti/sdo/fc/global/FCSettings.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_protocol_tiledmemory.h"
#include "ires_tiledmemory.h"
#include "iresman_tiledmemory.h"
#include "tiledmemory.h"
#include "_tiledmemory.h"

#include <ti/sdo/tiler/MemMgr.h>

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#endif

#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>
#include <ti/sdo/fc/global/FCSettings.h>

#define TILEDMEMORY_MAXRESOURCES 1


#define MEMSET(addr, val, count)        \
{                                       \
    UInt i;                             \
    UInt8 *ptr = (UInt8 *)((addr));       \
                                        \
    for (i = 0; i < (count); i++) {       \
        *ptr++ = (val);                   \
    }                                   \
}

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_TILEDMEMORY_InternalState {

    int numOpens;        /* Number of instances of this resource manager */

    int sharedMemId;     /* Identifies the shared memory segment used to
                          * hold this state (in MP cases). */
} IRESMAN_TILEDMEMORY_InternalState;

extern UInt32 _TILEDMEMORY_ipcKeyBase;

__FAR__ static IRESMAN_PersistentAllocFxn * allocFxn; /* Memory alloc func. */
__FAR__ static IRESMAN_PersistentFreeFxn * freeFxn;   /* Memory free func. */

/*
 * Flag indicating if the resource manager is initialized
 */
__FAR__ static unsigned int _initialized = 0;

__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

__FAR__ Registry_Desc ti_sdo_fc_ires_tiledmem_desc;

__FAR__ static IGateProvider_Handle gate = NULL;

static inline Void freeRes(Void *memoryBaseAddress, Int size,
        IALG_Handle alg, Int scratchGroupId, Bool isTiled);

static Void * retryMemAlloc(MemAllocBlock * tilerDescPtr,
        pixel_fmt_t * unitPtr, Bool * isTiled, unsigned int size);

/*  extern unsigned int _TILEDMEMORY_NUMRESOURCES;*/

/*
 *  ======== IRESMAN_TILEDMEMORY_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_TILEDMEMORY_getProtocolName()
{
    if (regInit) {
    Log_print0(Diags_ENTRY, "[+E] IRESMAN_TILEDMEMORY_getProtocolName> Enter");

    Log_print1(Diags_EXIT,
            "[+X] IRESMAN_TILEDMEMORY_getProtocolName> Exit (name=%s)",
            (IArg)(IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getName()));
    }

    return (IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_TILEDMEMORY_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_TILEDMEMORY_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if (regInit)
    Log_print0(Diags_ENTRY,
            "[+E] IRESMAN_TILEDMEMORY_getProtocolRevision> Enter");

    version = IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getRevision();

    if (regInit)
    Log_print3(Diags_EXIT,
            "[+X] IRESMAN_TILEDMEMORY_getProtocolRevision> Exit "
            "(version=(%d.%d.%d))",
            (IArg)(version->Major), (IArg)(version->Source),
            (IArg)(version->Radius));

    return (version);
}

/*
 *  ======== IRESMAN_TILEDMEMORY_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_TILEDMEMORY_init(IRESMAN_Params * initArgs)
{
    IRESMAN_TiledmemoryParams * resmanArgs =
            (IRESMAN_TiledmemoryParams *)initArgs;
#ifndef xdc_runtime_Assert_DISABLE_ALL
    Registry_Result   regResult;
#endif

    Assert_isTrue(initArgs != NULL, (Assert_Id)NULL);

    /*
     *  Register the module name for logging only once. Do this before any
     *  Log functions are called.
     */
    if (!regInit) {
#ifndef xdc_runtime_Assert_DISABLE_ALL
        regResult =
#endif
                Registry_addModule(&ti_sdo_fc_ires_tiledmem_desc,
                TILEDMEMORY_MODNAME);

        Assert_isTrue(regResult == Registry_SUCCESS, (Assert_Id)NULL);

        /* Set diags mask to FC default */
        FCSettings_init();
        FCSettings_setDiags(TILEDMEMORY_MODNAME);
        regInit = 1;
    }

    Log_print1(Diags_ENTRY,
            "[+E] IRESMAN_TILEDMEMORY_init> Enter (initArgs=0x%x)",
            (IArg)initArgs);

    /* Check if already initialized */
    if (_initialized) {
       Log_print0(Diags_EXIT,
               "[+X] IRESMAN_TILEDMEMORY_init> Exit (status=IRES_EEXISTS)");

       return (IRES_EEXISTS);
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored statically.
     */
    allocFxn = resmanArgs->baseConfig.allocFxn;
    freeFxn = resmanArgs->baseConfig.freeFxn;

    /* Create a gate */
    if (gate == NULL) {
        gate = OsalSupport_createGate(_TILEDMEMORY_ipcKeyBase);
        if (gate == NULL) {
            Log_print0(Diags_EXIT, "[+X] IRESMAN_TILEDMEMORY_init> "
                    "Exit (status=IRES_ENOMEM)");
            return (IRES_ENOMEM);
        }
    }

    /* Set Initalized flag to 1 if successful */
     _initialized = 1;

     Log_print0(Diags_EXIT,
             "[+X] IRESMAN_TILEDMEMORY_init> Exit (status=IRES_OK)");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_TILEDMEMORY_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_TILEDMEMORY_exit()
{
    /*
     * Check if initialized
     */

    Log_print0(Diags_ENTRY, "[+E] IRESMAN_TILEDMEMORY_exit> Enter");

    if (!(_initialized)) {

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_exit> Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

    if (gate) {
        OsalSupport_deleteGate(gate);
        gate = NULL;
    }

    /* Set the initialized flag to zero again */
    _initialized = 0;

    Log_print0(Diags_EXIT,
            "[+X] IRESMAN_TILEDMEMORY_exit> Exit (status=IRES_OK)");


    return (IRES_OK);
}

/*
 *  ======== IRESMAN_TILEDMEMORY_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Handle IRESMAN_TILEDMEMORY_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec protocolMemRecs[TILEDMEMORY_MAXRESOURCES];
    Int numMemRecs = 0;
    Int sizeTiledMemory = 0;
    IRESMAN_TILEDMEMORY_ConstructHandleArgs  constructArgs;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    MemAllocBlock  tilerDesc;
    Void *         tilerAddr = NULL;
    IArg key;
    pixel_fmt_t unit;
    IRES_TILEDMEMORY_AccessUnit accessUnit;
    Bool isTiled = TRUE;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;


    /*
     * Cast the protocolArgs as the request descriptor for Tiledmemory resource
     */
    IRES_TILEDMEMORY_ProtocolArgs * requestDescArgs =
            (IRES_TILEDMEMORY_ProtocolArgs *) protocolArgs;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY,
            "[+E] IRESMAN_TILEDMEMORY_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)", (IArg)protocolArgs, (IArg)scratchGroupId);

    if (_initialized != 1) {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_getHandles> RMAN register for "
                "TILEDMEMORY "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources");

        return (NULL);
    }

    if (requestDescArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }
    else {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_getHandles> Request for IRES_SCRATCH "
                "TILEDMEMORY resources, not supported.\n");

        return (NULL);

    }

    /* clear tiler descriptor */
    MEMSET(&tilerDesc, 0, sizeof(tilerDesc));

    /*
     * Error checking for accessDimension and accessUnit comobinations
     */
    if (requestDescArgs->accessDimension == IRES_TILEDMEMORY_1D) {

        if (requestDescArgs->sizeDim0 <= 0) {
           *status =  IRES_EALG;

           Log_print0(Diags_USER7,
                   "[+7] IRESMAN_TILEDMEMORY_getHandles> Incorrect value "
                   "specified for sizeDim0 or sizeDim1 in codec's "
                    "protocolArgs.\n");

           return (NULL);
        }

        tilerDesc.dim.len = requestDescArgs->sizeDim0;

        if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_PAGE) {
            unit = PIXEL_FMT_PAGE;
        }
        else if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_RAW) {
            isTiled = FALSE;
            sizeTiledMemory = requestDescArgs->sizeDim0;
        }
        else {
            *status =  IRES_ENORESOURCE;

            Log_print1(Diags_USER7,
                    "[+7] IRESMAN_TILEDMEMORY_getHandles> Did not recognize "
                    "requested access Unit %d\n", requestDescArgs->accessUnit);

            return (NULL);
        }

    } else if (requestDescArgs->accessDimension == IRES_TILEDMEMORY_2D) {

        if ((requestDescArgs->sizeDim0 <= 0) ||
                (requestDescArgs->sizeDim1 <= 0) ||
                (requestDescArgs->sizeDim0 > 0xFFFF) ||
                (requestDescArgs->sizeDim1 > 0xFFFF)) {

           *status =  IRES_EALG;

           Log_print0(Diags_USER7,
                   "[+7] IRESMAN_TILEDMEMORY_getHandles> Incorrect value "
                   "specified for sizeDim0 or sizeDim1 in codec's "
                   "protocolArgs.\n");

           return (NULL);

        }

        if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_8BIT){
            unit = PIXEL_FMT_8BIT;
            tilerDesc.dim.area.width = requestDescArgs->sizeDim0;
            tilerDesc.dim.area.height = requestDescArgs->sizeDim1;
        }
        else if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_16BIT) {
            unit = PIXEL_FMT_16BIT;
            tilerDesc.dim.area.width = (requestDescArgs->sizeDim0)/2;
            tilerDesc.dim.area.height = requestDescArgs->sizeDim1;
        }
        else if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_32BIT) {
            unit = PIXEL_FMT_32BIT;
            tilerDesc.dim.area.width = (requestDescArgs->sizeDim0)/4;
            tilerDesc.dim.area.height = requestDescArgs->sizeDim1;
        }
        else if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_PAGE) {

            unit = PIXEL_FMT_PAGE;
            tilerDesc.dim.len = requestDescArgs->sizeDim0 *
                requestDescArgs->sizeDim1;
        }
        else if (requestDescArgs->accessUnit == IRES_TILEDMEMORY_RAW) {
            isTiled = FALSE;
            tilerDesc.dim.len = requestDescArgs->sizeDim0 *
            /* size is required only for RAW allocations */
                requestDescArgs->sizeDim1;
            sizeTiledMemory = requestDescArgs->sizeDim0 *
                    requestDescArgs->sizeDim1;
        }
        else {
           *status =  IRES_ENORESOURCE;

            Log_print1(Diags_USER7,
                    "[+7] IRESMAN_TILEDMEMORY_getHandles> Did not recognize "
                    "request type %d\n", requestDescArgs->accessUnit);

            return (NULL);

        }
    }
    else {
        *status =  IRES_ENORESOURCE;

        Log_print1(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_getHandles> Did not recognize "
                "requested accessDimension%d\n",
                requestDescArgs->accessDimension);

        return (NULL);
    }

    key = IGateProvider_enter(gate);

    /* Call to tiler Alloc*/
    tilerAddr = retryMemAlloc(&tilerDesc, &unit, &isTiled, sizeTiledMemory);

    IGateProvider_leave(gate, key);

    /* Error if returned address is NULL */
    if (tilerAddr == (Void *)NULL ) {

       *status =  IRES_ENORESOURCE;

       Log_print0(Diags_USER7,
               "[+7] IRESMAN_TILEDMEMORY_getHandles> Error obtaining "
               "TILEDMEMORY resource.");

       Log_print0(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_getHandles> Exit (handle=NULL, "
                "status=IRES_ENORESOURCE)");

       return (NULL);
    }

    if (isTiled) {

        /* TILED memory was allocated */
        switch(unit) {
            case PIXEL_FMT_32BIT:
                accessUnit = IRES_TILEDMEMORY_32BIT;
                break;
            case PIXEL_FMT_16BIT:
                accessUnit = IRES_TILEDMEMORY_16BIT;
                break;
            case PIXEL_FMT_8BIT:
                accessUnit = IRES_TILEDMEMORY_8BIT;
                break;
            case PIXEL_FMT_PAGE:
                accessUnit = IRES_TILEDMEMORY_PAGE;
                break;
            default:
                accessUnit = IRES_TILEDMEMORY_RAW;
            }
    }
    else {
        /* RAW memory was returned */
        accessUnit = IRES_TILEDMEMORY_RAW;
    }


    /*
     * Get IRES_TILEDMEMORY resource handle's memory requirements
     */
    numMemRecs = IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    Assert_isTrue(numMemRecs <= TILEDMEMORY_MAXRESOURCES, (Assert_Id)NULL);

    /*
     * Populate the construct args
     */
    (constructArgs.args).size =
                        sizeof(IRESMAN_TILEDMEMORY_ConstructHandleArgs);
    constructArgs.isTiledMemory = isTiled;
    constructArgs.systemSpaceBaseAddress = tilerAddr;
    constructArgs.memBaseAddr =    tilerAddr;  /* MMU set up for 0x0 offset */
    constructArgs.tilerBaseAddr =
            (void *)TILEDMEMORY_PARAMS.tiledmemoryBaseAddress;
    constructArgs.unit = accessUnit;
    constructArgs.sizeTiledMemory = sizeTiledMemory;

    constructArgs.info = NULL;

    /* Only persistent requests supported */
    constructArgs.persistent = TRUE;

    /*
     * Obtain memory resources to build the handle
     */
    IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory
     */
    if (FALSE == allocFxn(protocolMemRecs, numMemRecs)) {

        *status = IRES_ENOMEM;

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_getHandles> Error allocating memory "
                "for constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(protocolMemRecs->size),
                (IArg)(protocolMemRecs->alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        /* Error so free acquired resource */
        freeRes(tilerAddr, sizeTiledMemory, algHandle, scratchGroupId,
                isTiled);

        return (NULL);
    }

    /*
     * Use the CONSTRUCT interface of the protocol implementation to
     * construct the handle within the allocated resource
     */
    resourceHandle = IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.constructHandle(
            protocolArgs, protocolMemRecs,
            (IRESMAN_ConstructArgs *)&constructArgs, status);

    if (IRES_OK != *status) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_getHandles> Error creating "
                "handle\n");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        /* Error so free acquired resource */
        freeRes(tilerAddr, constructArgs.sizeTiledMemory,
                algHandle, scratchGroupId, isTiled);

        return (NULL);
    }
    else {

        Log_print2(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_getHandles> Exit (handle=0x%x, "
                "status=0x%x)", (IArg)resourceHandle, (IArg)(*status));

        resDesc->handle = (IRES_Obj *)resourceHandle;

        resDesc->revision->Major = 1;
        resDesc->revision->Source = 0;
        resDesc->revision->Radius = 0;

        return (resourceHandle);
    }
}

/*
 *  ======== IRESMAN_TILEDMEMORY_freeHandles ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_TILEDMEMORY_freeHandles(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor * resDesc,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[TILEDMEMORY_MAXRESOURCES];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    Bool isTiled = TRUE;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;
    IRES_TILEDMEMORY_IntObj *resourceHandle = (IRES_TILEDMEMORY_IntObj *)
            algResourceHandle;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);
    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRESMAN_TILEDMEMORY_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)",
            (IArg)algResourceHandle, (IArg)protocolArgs,
            (IArg)scratchGroupId);

    if (_initialized != 1) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_TILEDMEMORY_freeHandles>RMAN register for "
                "TILEDMEMORY "
                "resource was not successful. Please call RMAN_register "
                "before trying to assign or release resources");

        status =  IRES_ENORESOURCE;

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_TILEDMEMORY_freeHandles>Exit "
                "(status=IRES_ENORESOURCE)");

        return (status);
    }

    if (resourceHandle->resObj.isTiledMemory) {
        isTiled = TRUE;
    }
    else {
        isTiled = FALSE;
    }

    /*
     * Free the memory allocated for the tiledmemory resource.
     */
    freeRes(((IRES_TILEDMEMORY_Handle)resourceHandle)->memoryBaseAddress,
            resourceHandle->sizeTiledMemory, algHandle, scratchGroupId,
            isTiled);

    /*
     * Obtain handle memory resources to free and free them
     */
    numMemRecs = IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getNumMemRecs
            ((IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_TILEDMEMORY_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_TILEDMEMORY_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    freeFxn(resourceMemRecs, numMemRecs);

    Log_print1(Diags_EXIT,
            "[+X] IRESMAN_TILEDMEMORY_freeHandles> Exit (status=%d)",
            (IArg)status);

    return (status);
}


static inline Void freeRes(Void *memoryBaseAddress, Int size,
        IALG_Handle alg, Int scratchGroupId, Bool isTiled)
{
    IArg key;
    IALG_MemRec freeMemRec;

    if (isTiled) {
        key = IGateProvider_enter(gate);

        MemMgr_Free(memoryBaseAddress);

        IGateProvider_leave(gate, key);
    }
    else {
        freeMemRec.size = size;
        freeMemRec.alignment = 0x4;
        freeMemRec.space = IALG_EXTERNAL;
        freeMemRec.attrs = IALG_PERSIST;
        freeMemRec.base = memoryBaseAddress;

        freeFxn(&freeMemRec, 1);
    }
}

static Void * retryMemAlloc(MemAllocBlock * tilerDescPtr,
        pixel_fmt_t * unitPtr, Bool * isTiled, unsigned int size )
{
    Void * tilerAddr;
    IALG_MemRec requestMemRec;

    if (!(*isTiled)) {

        /* RAW memory requested */
        requestMemRec.size = size;
        requestMemRec.alignment = 0x4;
        requestMemRec.space = IALG_EXTERNAL;
        requestMemRec.attrs = IALG_PERSIST;

        if (FALSE == allocFxn(&requestMemRec, 1)) {
            return (NULL);
        }
        tilerAddr = (void *)(requestMemRec.base);
        return (tilerAddr);
    }


    /* First try and alloc the requested tiler block */
    tilerDescPtr->pixelFormat = *unitPtr;
    tilerDescPtr->stride = 0;
    tilerDescPtr->ptr = 0;
    tilerDescPtr->reserved = 0;

    if (PIXEL_FMT_PAGE == tilerDescPtr->pixelFormat) {
        /* round len up to next page (4KB) boundary */
        tilerDescPtr->dim.len =
            (4096 - 1 + tilerDescPtr->dim.len) & ~(4096 - 1);
    }

    tilerAddr = (Void *)MemMgr_Alloc(tilerDescPtr, 1);

    if (NULL != tilerAddr) {
        return (tilerAddr);
    }

    /* If it Fails */
    if (PIXEL_FMT_PAGE == tilerDescPtr->pixelFormat) {
        *isTiled = FALSE;
    }
    else if (PIXEL_FMT_8BIT == tilerDescPtr->pixelFormat) {
        *unitPtr = PIXEL_FMT_PAGE;
        /* convert the dimensions if required */
        tilerDescPtr->dim.len = size;
    }
    else if (PIXEL_FMT_16BIT == tilerDescPtr->pixelFormat) {
        tilerDescPtr->dim.area.width *= 2;
        *unitPtr = PIXEL_FMT_8BIT;
        /* convert the dimensions if required */
    }
    else if (PIXEL_FMT_32BIT == tilerDescPtr->pixelFormat) {
        tilerDescPtr->dim.area.width *= 2;
        *unitPtr = PIXEL_FMT_16BIT;
        /* convert the dimensions if required */
    }

    tilerAddr = retryMemAlloc(tilerDescPtr, unitPtr, isTiled, size);

    return (tilerAddr);
}

IRESMAN_Fxns IRESMAN_TILEDMEMORY =  {
    IRESMAN_TILEDMEMORY_getProtocolName,
    IRESMAN_TILEDMEMORY_getProtocolRevision,
    IRESMAN_TILEDMEMORY_init,
    IRESMAN_TILEDMEMORY_exit,
    IRESMAN_TILEDMEMORY_getHandles,
    IRESMAN_TILEDMEMORY_freeHandles,
    NULL,
    NULL
};

IRESMAN_TiledmemoryParams IRESMAN_TILEDMEMORY_DEFAULTPARAM;

IRESMAN_Fxns * TILEDMEMORY_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_TILEDMEMORY));
}


IRESMAN_Params * TILEDMEMORY_getDefaultParams()
{
    IRESMAN_TILEDMEMORY_DEFAULTPARAM.baseConfig.size =
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_TILEDMEMORY_DEFAULTPARAM);
}
