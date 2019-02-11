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
 *  ======== iresman_edma3Chan.c ========
 *  Implementation of the IRESMAN interface to acquire EDMA3CHAN resource
 *  handles.
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_edma3chan_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>

/*
 * Define this, before including ires_edma3Chan.h, as that checks for this
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_EDMA3CHAN_PROTOCOLREVISION from the header file.
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "_edma3Chan.h"
#include <ti/sdo/fc/edma3/edma3_config.h>
#include "iresman_edma3Chan.h"
#include "ires_edma3Chan.h"

/*
 *  ======== IRESMAN_Edma3Chan_InternalState ========
 *  Structure to hold the internal state information of the IRESMAN EDMA3CHAN
 *  object that will be set once during INIT and then re-used while granting
 *  resources.
 */
typedef struct IRESMAN_Edma3Chan_InternalState {

    IRESMAN_PersistentAllocFxn * allocFxn;    /* Memory allocation Function */

    IRESMAN_PersistentFreeFxn * freeFxn;      /* Memory free Function */

    unsigned short dchmapExists;              /* Flag indicating if Channel
                                                 Mapping exists for this EDMA3
                                                 device */
    unsigned int initialized;
                                              /* Flag indicating if the
                                                 resource manager is
                                                 initialized */
    Int sharedMemId;


    XDAS_Int32 queueMap[IRES_EDMA3CHAN_NUMDESTTYPES];

} IRESMAN_Edma3Chan_InternalState;

/*
 * Represents the IRES EDMA3 Resource manager
 */
__FAR__ static IRESMAN_Edma3Chan_InternalState _EDMA3CHAN_internalState;

__FAR__ static IRESMAN_Edma3Chan_InternalState  * _resmanInternalState =
        &_EDMA3CHAN_internalState;

/*
 * Mapping of Destination types to Queue
 */

/* Internal function to free allocated resources */
static inline IRES_Status _freeResource(IALG_Handle algHandle,
        Int scratchGroupId, short edma3Chan, short qdmaChan, short numPaRams,
        short * paRamIndex, short numTccs, short * tccIndex);


__FAR__ Registry_Desc ti_sdo_fc_ires_edma3chan_desc;

__FAR__ static Int curInit = 0;  /* Reference count on IRESMAN_EDMA3CHAN_init() */
__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

/*
 *  ======== IRESMAN_EDMA3CHAN_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_EDMA3CHAN_getProtocolName()
{
    if (regInit) {
        Log_print0(Diags_ENTRY, "[+E] IRESMAN_EDMA3CHAN_getProtocolName> Enter");

        Log_print1(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getProtocolName> Exit (name=%s)",
                (IArg)(IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getName()));
    }

    return (IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_EDMA3CHAN_getProtocolRevision ========
 * Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_EDMA3CHAN_getProtocolRevision()
{
    IRES_ProtocolRevision * version;


    if (regInit) {
        Log_print0(Diags_ENTRY,
                "[+E] IRESMAN_EDMA3CHAN_getProtocolRevision> Enter");
    }

    version = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getRevision();

    if (regInit) {
            Log_print3(Diags_EXIT, "[+X] IRESMAN_EDMA3CHAN_getProtocolRevision>"
                    " Exit (version=(%d.%d.%d))",
            (IArg)(version->Major), (IArg)(version->Source),
            (IArg)(version->Radius));
    }

    return (version);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_EDMA3CHAN_init(IRESMAN_Params * initArgs)
{
    IRESMAN_Edma3ChanParams * resmanArgs = (IRESMAN_Edma3ChanParams *)initArgs;
    Registry_Result result;
    IRES_Status     status = IRES_OK;


    Assert_isTrue(initArgs != NULL, (Assert_Id)NULL);

    if (regInit == 0) {
        /*
         *  Enable logging. We only want to do this once, since there is
         *  no Registry_removeModule().
         */
        result = Registry_addModule(&ti_sdo_fc_ires_edma3chan_desc,
                EDMA3CHAN_MODNAME);

        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_init();
            FCSettings_setDiags(EDMA3CHAN_MODNAME);
        }
        regInit = 1;
    }

    Log_print1(Diags_ENTRY, "[+E] IRESMAN_EDMA3CHAN_init> Enter "
            "(initArgs=0x%x)", (IArg)initArgs);

    if (curInit++ == 0) {
        /*
         *  Initialize internal structure on first init call.
         */
        _resmanInternalState->allocFxn = NULL;
        _resmanInternalState->freeFxn = NULL;
        _resmanInternalState->dchmapExists = 0;
        _resmanInternalState->sharedMemId = -1;
        _resmanInternalState->initialized = 0;

        if (EDMA3_SOK != EDMA3_init()) {
            Log_print1(Diags_USER7, "[+7] IRESMAN_EDMA3CHAN_init> EDMA3_init()"
                       " failed: %d", status);
            status = IRES_EFAIL;
            Log_print1(Diags_EXIT, "[+X] IRESMAN_EDMA3CHAN_init> Exit "
                    "(status=%d)", status);
            return (status);
        }

        /*
         * Information regarding the memory allocation/free functions
         * is stored as part of the internal state of the resource
         * manager
         */
        _resmanInternalState->allocFxn = resmanArgs->baseConfig.allocFxn;
        _resmanInternalState->freeFxn = resmanArgs->baseConfig.freeFxn;

        /* Obtain information about the mapping */
        /* Assumes ordering of internal memory types INT0,1,2, EXT0,1,2,O0,1*/
        EDMA3_getDestTypeQueueMap(_resmanInternalState->queueMap);

        /* Initialization successful, set initalized flag to 1 */
        _resmanInternalState->initialized = 1;
    }
    else {
        if (_resmanInternalState->initialized) {
            Log_print0(Diags_USER6, "[+6] IRESMAN_EDMA3CHAN_init> Already "
                    "initialized");

            status = IRES_EEXISTS;
        }
        else {
            /* EDMA3_init() must have failed in a previous init() call */
            Log_print0(Diags_USER6, "[+X] IRESMAN_EDMA3CHAN_init> Previous "
                       "initialization failed");

            status = IRES_EFAIL;
        }
    }

    Log_print1(Diags_EXIT, "[+X] IRESMAN_EDMA3CHAN_init> Exit (status=%d)",
            status);

    return (status);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_EDMA3CHAN_exit()
{
    IRES_Status status = IRES_OK;

    Log_print0(Diags_ENTRY, "[+E] IRESMAN_EDMA3CHAN_exit> Enter");

    if (--curInit == 0) {
        /* Check if EDMA3 initialization succeeded */
        if (!(_resmanInternalState->initialized)) {
            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_EDMA3CHAN_exit> Exit (status=IRES_ENOINIT)");

            return (IRES_ENOINIT);
        }

        /*
         * Free up any memory that might be allocated in this module
         * Basically memory that has been used by the protocol implementation
         */
        if (EDMA3_exit() != EDMA3_SOK) {
            Log_print0(Diags_EXIT, "IRESMAN_EDMA3CHAN_exit> EDMA3_exit() "
                    "failed!");
            status = IRES_EFAIL;
        }

        /* Reset initialized flag */
        _resmanInternalState->initialized = 0;
    }

    Log_print1(Diags_EXIT, "[+X] IRESMAN_EDMA3CHAN_exit> Exit (status=%d)",
            status);

    return (status);
}

/*
 *  ======== IRESMAN_EDMA3CHAN_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Handle IRESMAN_EDMA3CHAN_getHandles( IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    EDMA3_ResDesc resObj;
    IALG_MemRec protocolMemRecs[IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs;
    EDMA3_Handle rmHandle;
    EDMA3_Result rmStatus;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;

    short reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
    short reqQdma = IRES_EDMA3CHAN_CHAN_NONE;
    short reqTcc[64];
    short numReqTccs = 0;

    short edma3Chan = IRES_EDMA3CHAN_CHAN_NONE;
    short qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    short numPaRams = 0;
    short numTccs = 0;
    short toFreeParams = 0;
    short paRamArray[IRES_EDMA3CHAN_MAXPARAMS] = { IRES_EDMA3CHAN_PARAM_NONE };
    short tccArray[IRES_EDMA3CHAN_MAXTCCS] = { IRES_EDMA3CHAN_TCC_NONE };
    unsigned int cccfg = 0x0;
    int i = 0;
    IRESMAN_EDMA3CHAN_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = NULL;

    /*
     * Cast the protocolArgs
     */
    IRES_EDMA3CHAN_ProtocolArgs * configArgs =
            (IRES_EDMA3CHAN_ProtocolArgs *) protocolArgs;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);

    Log_print2(Diags_ENTRY,
            "[+E] IRESMAN_EDMA3CHAN_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)", (IArg)protocolArgs, (IArg)scratchGroupId);

    if (_resmanInternalState->initialized != 1) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before assigning resources");

        *status =  IRES_ENORESOURCE;
        return (NULL);
    }

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    if (resDesc->revision->Major > 2) {

        Log_print3(Diags_USER6,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Requested version of "
                "IRES_EDMA3CHAN resource (%d %d %d) not supported. Maximum "
                " version supported is 2.0.0. Will create resource accordingly."
                "\n", resDesc->revision->Major, resDesc->revision->Source,
                resDesc->revision->Radius);

    }

    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);

    if (NULL == rmHandle) {

        *status =  IRES_ENORESOURCE;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error obtaining Low level "
                "Resource Manager Handle.");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENORESOURCE)");

        return (NULL);
    }

    if (EDMA3_SOK != EDMA3_getCCRegister( rmHandle , 4, &cccfg)) {

        *status =  IRES_EFAIL;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error reading EDMA3's CCCFG "
                "Register.");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                scratchGroupId)) {

            *status = IRES_EFAIL;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.");
        }

        return (NULL);
    }

    _resmanInternalState->dchmapExists =
            IRES_EDMA3CHAN_EDMA3REGISTERLAYER_CHMAPEXIST(cccfg);

    if (_resmanInternalState->dchmapExists) {
        Log_print0(Diags_USER2,
                "[+2] IRESMAN_EDMA3CHAN_getHandles> DCHMAP exists on device ");
    }

    numPaRams = configArgs->numPaRams;
    numTccs = configArgs->numTccs;
    Assert_isTrue(numPaRams <= IRES_EDMA3CHAN_MAXPARAMS, (Assert_Id)NULL);
    Assert_isTrue(numTccs <= IRES_EDMA3CHAN_MAXTCCS, (Assert_Id)NULL);

    reqEdma = configArgs->edmaChan;
    reqQdma = configArgs->qdmaChan;

        if ((reqEdma != IRES_EDMA3CHAN_EDMACHAN_ANY) &&
                        (reqEdma != IRES_EDMA3CHAN_CHAN_NONE) &&
                        ((reqEdma < 0) ||
                        (reqEdma >= 64 ))) {

        Log_print0(Diags_USER6,
                "[+6] IRESMAN_EDMA3CHAN_getHandles> Bad request for EDMA channel. "
                "Will not grant request EDMA channel");

                reqEdma = IRES_EDMA3CHAN_CHAN_NONE;
        }

        if ((reqQdma != IRES_EDMA3CHAN_QDMACHAN_ANY) &&
                        (reqQdma != IRES_EDMA3CHAN_CHAN_NONE) &&
                        ((reqQdma < 0) ||
                        (reqQdma >= 8))) {

        Log_print0(Diags_USER6,
                "[+6] IRESMAN_EDMA3CHAN_getHandles> Bad request for QDMA channel. "
                "Will not grant request QDMA channel");

                reqQdma = IRES_EDMA3CHAN_CHAN_NONE;
        }

    /* Check if the resources have been requested properly,
     * fail if there is an error */
    if ((numPaRams > 0) && (!(_resmanInternalState->dchmapExists))) {

        if ((numPaRams > 1) &&
                (IRES_EDMA3CHAN_CHAN_NONE != reqEdma)) {

            *status =  IRES_ENORESOURCE;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Cannot request multiple "
                    " paRams alongwith an EDMA3 channel when DCHMAP does not"
                    "exist. Request only one PaRam alongwith EDMA channel or "
                    "only multiple PaRams with no EDMA channel per handle");

            if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                    scratchGroupId)) {

                *status = IRES_EFAIL;

                Log_print0(Diags_USER7,
                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                        "level Resource Manager Handle.");
            }

            Log_print0(Diags_EXIT,
                    "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)");

            return (NULL);
        }

        if ((numPaRams == 1) &&
                (IRES_EDMA3CHAN_CHAN_NONE != reqEdma)) {

            /* 1 paRam requested alongwith an EDMA3 channel */
            if ((IRES_EDMA3CHAN_PARAM_ANY != configArgs->paRamIndex) &&
                    (IRES_EDMA3CHAN_EDMACHAN_ANY != reqEdma) &&
                    (reqEdma != configArgs->paRamIndex) ) {

                /* If specific channel requested doesn`t not match paRam
                   requested, cannot allocate the resource */

                *status = IRES_ENORESOURCE;

                Log_print2(Diags_USER7,
                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Channel requested %d "
                        " has to match PaRam requested %d when DCHMAP does"
                        "not exist for this device",
                        (IArg)reqEdma, (IArg)(configArgs->paRamIndex));

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                        scratchGroupId)) {

                    *status = IRES_EFAIL;

                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                            "level Resource Manager Handle.");
                }

                Log_print0(Diags_EXIT,
                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=IRES_ENORESOURCE)");

                return (NULL);
            }
        }
    }

    /*
     * Allocate PaRams at this time, only if DCHMAP exists
     * Or if (No DCHMAP and ) No EDMA channel is requested.
     * If an EDMA channel is requested, need to allocate a logical channel
     * so do it later
     */
    if ( (numPaRams > 0) &&
            (_resmanInternalState->dchmapExists ||
            (IRES_EDMA3CHAN_CHAN_NONE == reqEdma)) ) {

        resObj.type = EDMA3_RES_PARAM_SET;

        if ((numPaRams > 1) && configArgs->contiguousAllocation) {

            Log_print0(Diags_USER4,
                    "[+4] IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "requested");

            resObj.resId = (configArgs->paRamIndex ==
                    IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY:
                    configArgs->paRamIndex;

            if (EDMA3_SOK != EDMA3_allocContiguousResource(
                    rmHandle, &resObj, numPaRams)) {

                _freeResource(algHandle, scratchGroupId,
                        edma3Chan, qdmaChan, 0, NULL, 0, NULL);

                Log_print2(Diags_USER7,
                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate %d "
                        "contiguous paRams starting from %d",
                        (IArg)(numPaRams -1), (IArg)(resObj.resId));

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                        scratchGroupId)) {

                    *status = IRES_EFAIL;

                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low "
                            "level Resource Manager Handle.");
                }

                *status =  IRES_ENORESOURCE;

                Log_print1(Diags_EXIT,
                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=%d)", (IArg)(*status));

                return (NULL);
            }
            else {

                for (i = 0; i < numPaRams; i++) {
                    paRamArray[i] = resObj.resId + i;
                }

                toFreeParams = numPaRams;

                Log_print2(Diags_USER4,
                        "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained %d PaRams "
                        "starting at %d ",
                        (IArg)numPaRams, (IArg)(paRamArray[0]));
            }
        }
        else {

            Log_print0(Diags_USER4,
                    "[+4] IRESMAN_EDMA3CHAN_getHandles> Contiguous PaRams "
                    "NOT required");

            if (numPaRams == 1) {

                resObj.resId =(configArgs->paRamIndex ==
                        IRES_EDMA3CHAN_PARAM_ANY)? EDMA3_RES_ANY:
                        configArgs->paRamIndex;
            }
            else {
                /* Multiple non-contig PaRams should always be requested as
                   ANY */
                resObj.resId = EDMA3_RES_ANY;
            }

            /*
             * Allocate the PaRams individually
             */
            for (i = 0; i < numPaRams; i++) {

                if (EDMA3_SOK != EDMA3_allocResource( rmHandle,&resObj)) {

                    Log_print1(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "Param %d", (IArg)(resObj.resId));

                    _freeResource(algHandle, scratchGroupId,
                            edma3Chan, qdmaChan, i, paRamArray, 0, NULL);

                    *status = IRES_ENORESOURCE;

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                            scratchGroupId)) {

                        *status = IRES_EFAIL;

                        Log_print0(Diags_USER7,
                                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                                "Low level Resource Manager Handle.");
                    }

                    Log_print1(Diags_EXIT,
                            "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)", (IArg)(*status));

                    return (NULL);
                }
                else {

                    paRamArray[i] = resObj.resId;

                    Log_print1(Diags_USER4,
                            "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained Param %d"                            , (IArg)(paRamArray[i]));

                    resObj.resId = EDMA3_RES_ANY;
                }
            }
            toFreeParams = numPaRams;
        }
    }

    /* Obtain the TCCs if requested */
    if ((configArgs->numTccs > 0) &&
            (IRES_EDMA3CHAN_TCC_NONE != configArgs->tccIndex)) {

        resObj.type = EDMA3_RES_TCC;

        if (configArgs->numTccs > 1) {
            /* If requesting multiple TCCs then use ANY to request */
            resObj.resId = EDMA3_RES_ANY;
        }
        else {
            resObj.resId = (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY)?
                    EDMA3_RES_ANY:((unsigned int)configArgs->tccIndex);
        }

        for(i = 0 ; i <configArgs->numTccs; i++) {

            if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj)) {
                /*
                 * Error allocating tcc
                 * Free all resources and exit
                 */
                Log_print1(Diags_USER7,
                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate Tcc "
                        "%d", (IArg)(resObj.resId));

               _freeResource(algHandle, scratchGroupId,
                        edma3Chan, qdmaChan, toFreeParams, paRamArray,
                        i, tccArray );

                *status = IRES_ENORESOURCE;

                if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                            scratchGroupId)) {

                    *status = IRES_EFAIL;

                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                            "Low level Resource Manager Handle.");
                }

                Log_print1(Diags_EXIT,
                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                        "status=%d)", (IArg)(*status));


                return (NULL);
            }

            tccArray[i] = resObj.resId;
                        resObj.resId = EDMA3_RES_ANY;

            Log_print1(Diags_USER4,
                    "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained TCC %d",
                    (IArg)(tccArray[i]));
        }
    }

    /*
     * Obtain the channel requirements qdma or edmaChan
     * In one handle, can request for either QDMA or EDMA channel
     */

    if (IRES_EDMA3CHAN_CHAN_NONE != reqQdma) {

        /*
         * Request a qdma channel assign it to qdmaChan
         */
        resObj.type = EDMA3_RES_QDMA_CHANNEL;

        resObj.resId =(IRES_EDMA3CHAN_QDMACHAN_ANY == reqQdma)?
                EDMA3_RES_ANY:((unsigned int)reqQdma);

        if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj) ) {

            *status = IRES_ENORESOURCE;

            Log_print1(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate QDMA "
                    "Channel %d", (IArg)(resObj.resId));

            _freeResource(algHandle, scratchGroupId,
                    edma3Chan, qdmaChan, toFreeParams, paRamArray,
                    numTccs, tccArray);

            if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                    scratchGroupId)) {

                *status = IRES_EFAIL;

                Log_print0(Diags_USER7,
                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing "
                        "Low level Resource Manager Handle.");
            }

            Log_print1(Diags_EXIT,
                    "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                    "status=%d)", (IArg)(*status));

            return (NULL);
        }

        Log_print1(Diags_USER4,
                "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained qdma channel %d",
                (IArg)(resObj.resId));

        qdmaChan = resObj.resId;
    }

    if (IRES_EDMA3CHAN_CHAN_NONE != reqEdma) {

        /*
         * Request an edma channel assign it to edmaChan
         */
        resObj.type = EDMA3_RES_DMA_CHANNEL;

        if (_resmanInternalState->dchmapExists) {

            Log_print0(Diags_USER4,
                    "[+4] IRESMAN_EDMA3CHAN_getHandles> DCHMAP exists on device");

            /*
             * If DCHMAP exists then any channel request can be satisfied by
             * mapping it to the PaRam that has been allocated
             */
            if ((numTccs == 1) &&
                    (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY) &&
                    (reqEdma == IRES_EDMA3CHAN_EDMACHAN_ANY)) {

                Log_print0(Diags_USER2,
                        "[+2] IRESMAN_EDMA3CHAN_getHandles> EDMA Channel ANY "
                        "requested with 1 TCC ANY.");

                resObj.resId = tccArray[0];
            }
            else {
                resObj.resId = (IRES_EDMA3CHAN_EDMACHAN_ANY == reqEdma)
                        ? EDMA3_RES_ANY:((unsigned int)reqEdma);
            }

            if (EDMA3_SOK != EDMA3_allocResource( rmHandle, &resObj) ) {

                if ((numTccs == 1) &&
                        (configArgs->tccIndex == IRES_EDMA3CHAN_TCC_ANY) &&
                        (reqEdma == IRES_EDMA3CHAN_EDMACHAN_ANY)) {

                    /*
                     * Resource probably failed because it was a special
                     * request for mapped Tcc and Edma channel. Allocate
                     * another TCC and try to acquire a channel mapped to it
                     */
                    Log_print1(Diags_USER2,
                            "[+2] IRESMAN_EDMA3CHAN_getHandles> Request for EDMA "
                            "channel %d failed. Try new EDMA:TCC allocation.",
                            (IArg)(resObj.resId));

                    resObj.type = EDMA3_RES_TCC;
                    resObj.resId = EDMA3_RES_ANY;

                    rmStatus = EDMA3_allocResource(rmHandle, &resObj);

                    while(EDMA3_SOK == rmStatus) {

                    Log_print1(Diags_USER2,
                            "[+2] IRESMAN_EDMA3CHAN_getHandles> "
                            "Allocated New Tcc %d", (IArg)(resObj.resId));

                        resObj.type = EDMA3_RES_DMA_CHANNEL;

                        if (EDMA3_SOK ==
                                EDMA3_allocResource(rmHandle, &resObj)) {

                            reqTcc[numReqTccs] = tccArray[0];
                            numReqTccs++;

                            edma3Chan = resObj.resId;
                            tccArray[0] = resObj.resId;

                            Log_print2(Diags_USER4,
                                    "[+4] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Obtained EDMA channel %d and Tcc %d",
                                    (IArg)edma3Chan, (IArg)(tccArray[0]));

                            break;
                        }
                        else {

                            reqTcc[numReqTccs] = resObj.resId;
                            numReqTccs++;

                            Log_print1(Diags_USER2,
                                    "[+2] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate EDMA channel %d",
                                    (IArg)(resObj.resId));

                            resObj.type = EDMA3_RES_TCC;
                            resObj.resId = EDMA3_RES_ANY;

                            rmStatus =
                                    EDMA3_allocResource(rmHandle, &resObj);
                        }
                    }

                    if (numReqTccs > 0) {

                        /* Free all extra Tccs requested */
                        resObj.type = EDMA3_RES_TCC;

                        for (i = 0; i < numReqTccs; i++) {

                            resObj.resId = reqTcc[i];

                            Log_print1( Diags_USER2,
                                    "[+2] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Free Extra Tcc %d", (IArg)(resObj.resId));

                            if (EDMA3_SOK !=
                                    EDMA3_freeResource(rmHandle, & resObj)) {

                                *status = IRES_EFAIL;

                                Log_print1( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> Error "
                                        "freeing Tcc %d", (IArg)(resObj.resId));
                            }
                        }
                    }

                    /*
                     * Check if we broke out because of success or failure
                     */
                    if (EDMA3_SOK != rmStatus) {

                        *status = IRES_ENORESOURCE;

                        Log_print0(Diags_USER7,
                                "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not "
                                "allocate matching EDMA channel and Tcc.");

                        _freeResource(algHandle, scratchGroupId, edma3Chan,
                                qdmaChan, toFreeParams, paRamArray, numTccs,
                                tccArray);

                        if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                            *status = IRES_EFAIL;

                            Log_print0( Diags_USER7,
                                    "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Error releasing Low level Resource Manager"
                                    " Handle.");
                        }

                        Log_print1(Diags_EXIT,
                                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                "(handle=NULL, status=%d)", (IArg)(*status));

                        return (NULL);
                    }
                }
                else {

                    *status = IRES_ENORESOURCE;

                    Log_print1(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "EDMA Channel %d", (IArg)(resObj.resId));

                    _freeResource(algHandle, scratchGroupId, edma3Chan,
                            qdmaChan, toFreeParams, paRamArray, numTccs,
                            tccArray);

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                        *status = IRES_EFAIL;

                        Log_print0( Diags_USER7,
                                "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager"
                                " Handle.");
                    }

                    Log_print1(Diags_EXIT,
                            "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)", (IArg)(*status));

                    return (NULL);
                }
            }
            else {
                edma3Chan = resObj.resId;

                Log_print1(Diags_USER4,
                        "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained Edma channel "
                        "%d", (IArg)edma3Chan);
            }
        }
        else {

            resObj.resId = (IRES_EDMA3CHAN_EDMACHAN_ANY == reqEdma)
                    ? EDMA3_RES_ANY:((unsigned int)reqEdma);

            Log_print0(Diags_USER4,
                    "[+4] IRESMAN_EDMA3CHAN_getHandles> DCHMAP does not exist on "
                    "device");

            if (numPaRams > 0 ) {

                if (numPaRams > 1) {

                    /* Multiple PaRams requested, and EDMA channel requested
                       on an SOC where DCHMAP does not exist, assert error */

                    Log_print0(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> [Error] DCHMAP "
                            "does not exist, Multiple PaRams requested "
                            "alongwith an EDMA channel ");

                    Assert_isTrue(0, (Assert_Id)NULL);

                    _freeResource( algHandle, scratchGroupId, edma3Chan,
                            qdmaChan, 0, NULL, numTccs, tccArray);

                    *status = IRES_ENORESOURCE;

                    if (EDMA3_SOK != EDMA3_releaseResourceManager(
                                algHandle, scratchGroupId)) {

                        *status = IRES_EFAIL;

                        Log_print0( Diags_USER7,
                                "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager"
                                " Handle.");
                    }

                    Log_print1(Diags_EXIT,
                            "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                            "status=%d)", (IArg)(*status));

                    return (NULL);
                }
                else {

                    /* TODO: Use allocLogical channel here */
                    if (EDMA3_RES_ANY == resObj.resId) {

                        if (IRES_EDMA3CHAN_PARAM_ANY ==
                                configArgs->paRamIndex) {

                            /* Allocate ANY PaRam and ANY Channel as long as
                               they are mapped
                               We request a Channel first and then the
                               corresponding PaRam */

                            resObj.type = EDMA3_RES_DMA_CHANNEL;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                Log_print0( Diags_USER4,
                                        "[+4] IRESMAN_EDMA3CHAN_getHandles> Channel"
                                        " ANY allocation failed");

                                *status = IRES_ENORESOURCE;

                                Log_print0( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate EDMA Channel ");

                                _freeResource(algHandle, scratchGroupId,
                                        edma3Chan, qdmaChan, toFreeParams,
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK !=
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL;

                                    Log_print0( Diags_USER7,
                                            "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.");
                                }

                                Log_print1( Diags_EXIT,
                                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)",
                                        (IArg)(*status));

                                return (NULL);
                            }

                            edma3Chan = resObj.resId;
                            resObj.type = EDMA3_RES_PARAM_SET;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                Log_print1( Diags_USER4,
                                        "[+4] IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                        " %d allocation failed",
                                        (IArg)(resObj.resId));

                                *status = IRES_ENORESOURCE;

                                Log_print1( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate paRam %d",
                                        (IArg)(resObj.resId));

                                _freeResource( algHandle, scratchGroupId,
                                        edma3Chan, qdmaChan,
                                        toFreeParams, paRamArray, numTccs,
                                        tccArray);

                                if (EDMA3_SOK !=
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL;

                                    Log_print0( Diags_USER7,
                                            "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.");
                                }

                                Log_print1( Diags_EXIT,
                                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)",
                                        (IArg)(*status));

                                return (NULL);
                            }

                            paRamArray[0] = resObj.resId;
                        }
                        else {

                            /* PaRam number requested is fixed, EDMA channel
                             * ANY */
                            resObj.resId = configArgs->paRamIndex;
                            resObj.type = EDMA3_RES_PARAM_SET;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                Log_print1( Diags_USER4,
                                        "[+4] IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                        " %d allocation failed",
                                        (IArg)(resObj.resId));

                                *status = IRES_ENORESOURCE;

                                Log_print1( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate paRam %d",
                                        (IArg)(resObj.resId));

                                _freeResource( algHandle, scratchGroupId,
                                        edma3Chan, qdmaChan, toFreeParams,
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK !=
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL;

                                    Log_print0( Diags_USER7,
                                            "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.");
                                }

                                Log_print1( Diags_EXIT,
                                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)",
                                        (IArg)(*status));

                                return (NULL);
                            }

                            paRamArray[0] = resObj.resId;
                            resObj.type = EDMA3_RES_DMA_CHANNEL;

                            if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                                *status = IRES_ENORESOURCE;

                                Log_print1( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Could not allocate EDMA Channel %d",
                                        (IArg)(resObj.resId));

                                _freeResource( algHandle, scratchGroupId,
                                        edma3Chan, qdmaChan, toFreeParams,
                                        paRamArray, numTccs, tccArray);

                                if (EDMA3_SOK !=
                                        EDMA3_releaseResourceManager(algHandle,                                         scratchGroupId)) {

                                    *status = IRES_EFAIL;

                                    Log_print0( Diags_USER7,
                                            "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                            "Error releasing Low level Resource"
                                            " Manager Handle.");
                                }

                                Log_print1( Diags_EXIT,
                                        "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                        "(handle=NULL, status=%d)",
                                        (IArg)(*status));

                                return (NULL);

                            }
                            edma3Chan = resObj.resId;
                        }
                    }
                    else {

                        /* EDMA channel is fixed, allocate PaRam corresponding
                         to that */
                        resObj.resId = reqEdma;
                        resObj.type = EDMA3_RES_DMA_CHANNEL;

                        if (EDMA3_SOK != EDMA3_allocResource(
                                    rmHandle, &resObj)) {

                            Log_print1( Diags_USER4,
                                    "[+4] IRESMAN_EDMA3CHAN_getHandles> Channel"
                                    " %d allocation failed, truly "
                                    "allocating ANY Channel",
                                    (IArg)(resObj.resId));

                            *status = IRES_ENORESOURCE;

                            Log_print0( Diags_USER7,
                                    "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate EDMA Channel ");

                            _freeResource(algHandle, scratchGroupId, edma3Chan,                                     qdmaChan, toFreeParams,
                                    paRamArray, numTccs, tccArray);

                            if (EDMA3_SOK !=
                                    EDMA3_releaseResourceManager(algHandle,
                                    scratchGroupId)) {

                                *status = IRES_EFAIL;

                                Log_print0( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Error releasing Low level Resource"
                                        " Manager Handle.");
                            }

                            Log_print1( Diags_EXIT,
                                    "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                    "(handle=NULL, status=%d)",
                                    (IArg)(*status));

                            return (NULL);

                        }

                        edma3Chan = resObj.resId;
                        resObj.type = EDMA3_RES_PARAM_SET;

                        if (EDMA3_SOK != EDMA3_allocResource(
                                rmHandle, &resObj)) {

                            Log_print1( Diags_USER4,
                                    "[+4] IRESMAN_EDMA3CHAN_getHandles> PaRam "
                                    " %d allocation failed",
                                    (IArg)(resObj.resId));

                            *status = IRES_ENORESOURCE;

                            Log_print1( Diags_USER7,
                                    "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                    "Could not allocate paRam %d",
                                    (IArg)(resObj.resId));

                            _freeResource( algHandle, scratchGroupId, edma3Chan,                                    qdmaChan, toFreeParams, paRamArray, numTccs,                                    tccArray);

                            if (EDMA3_SOK !=
                                    EDMA3_releaseResourceManager(algHandle,
                                    scratchGroupId)) {

                                *status = IRES_EFAIL;

                                Log_print0( Diags_USER7,
                                        "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                        "Error releasing Low level Resource"
                                        " Manager Handle.");
                            }

                            Log_print1( Diags_EXIT,
                                    "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                                    "(handle=NULL, status=%d)",
                                    (IArg)(*status));

                            return (NULL);
                        }

                        paRamArray[0] = resObj.resId;
                    }
                }

                toFreeParams = numPaRams;
            }
            else {

                /* No PaRams requested, allocate channel requested */

                if (EDMA3_SOK != EDMA3_allocResource(
                        rmHandle, &resObj)) {
                    *status = IRES_ENORESOURCE;

                    Log_print1(Diags_USER7,
                            "[+7] IRESMAN_EDMA3CHAN_getHandles> Could not allocate "
                            "EDMA Channel %d", (IArg)(resObj.resId));


                    _freeResource( algHandle, scratchGroupId, edma3Chan,
                            qdmaChan, 0, NULL, numTccs, tccArray);

                    if (EDMA3_SOK !=
                            EDMA3_releaseResourceManager(algHandle,
                            scratchGroupId)) {

                        *status = IRES_EFAIL;

                        Log_print0( Diags_USER7,
                                "[+7] IRESMAN_EDMA3CHAN_getHandles> "
                                "Error releasing Low level Resource Manager "
                                "Handle.");
                    }

                    Log_print1( Diags_EXIT,
                            "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit "
                            "(handle=NULL, status=%d)", (IArg)(*status));

                    return (NULL);
                }

                Log_print1(Diags_USER4,
                        "[+4] IRESMAN_EDMA3CHAN_getHandles> Obtained Edma channel "
                        "%d", (IArg)(resObj.resId));

                edma3Chan = resObj.resId;
            }
        }
    }

    /*
     * To call the Construct handle protocol interface, first construct the
     * arguments that need to be passed IRES_EDMA3CHAN_ConstructHandleArgs
     * This has the list of actual params that need to be sent back as handle
     */

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_EDMA3CHAN_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _resmanInternalState->allocFxn(&constructHandleMemRec, 1)) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,                paRamArray, numTccs, tccArray);

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(constructHandleMemRec.size),
                (IArg)(constructHandleMemRec.alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        *status =  IRES_ENOMEM;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                scratchGroupId)) {

            *status = IRES_EFAIL;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.");
        }

        Log_print1(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, status=%d)",
                (IArg)(*status));

        return (NULL);
    }

    Assert_isTrue(IALG_EXTERNAL == constructHandleMemRec.space,
            (Assert_Id)NULL);
    constructArgs = constructHandleMemRec.base;
    constructArgs->numPaRams = numPaRams;
    constructArgs->paRamIndex = paRamArray;
    constructArgs->edma3Chan = edma3Chan;
    constructArgs->qdmaChan = qdmaChan;
    constructArgs->tccIndex = tccArray;
        constructArgs->numTccs = numTccs;

    if (scratchGroupId == -1) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    if ( EDMA3_SOK != EDMA3_getBaseAddress(rmHandle, EDMA3_CC_PHY_ADDR,
            &(constructArgs->edma3CCBaseAddress))) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,                paRamArray, numTccs, tccArray);

        _resmanInternalState->freeFxn(&constructHandleMemRec, 1);

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error obtaining EDMA3 base "
                "address");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        *status = IRES_EFAIL;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                scratchGroupId)) {

            *status = IRES_EFAIL;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.");
        }

        return (NULL);
    }

    /*
     * Get IRES_EDMA3CHAN_RESOURCEPROTOCOL's memory requirements
     */
    numMemRecs = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getNumMemRecs
            ((IRES_ProtocolArgs *) protocolArgs);

    Assert_isTrue(numMemRecs <= IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS,
            (Assert_Id)NULL);

    /*
     * Get the memory requirements of the protocol in resMemRecs
     */
    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory
     */
    if (FALSE == _resmanInternalState->allocFxn(protocolMemRecs, numMemRecs)) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,
                paRamArray, numTccs, tccArray);

        Log_print2(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST",
                (IArg)(protocolMemRecs->size),
                (IArg)(protocolMemRecs->alignment));

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)");

        *status = IRES_ENOMEM;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                scratchGroupId)) {

            *status = IRES_EFAIL;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.");
        }

        return (NULL);
    }

    for (i=0; i < numMemRecs; i++) {
        Assert_isTrue(protocolMemRecs[i].space == IALG_EXTERNAL,
                (Assert_Id)NULL);
    }

    /*
     * Construct the resource protocol handle
     */
    resourceHandle = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.constructHandle(
             protocolArgs, protocolMemRecs,
             (IRESMAN_ConstructArgs *)constructArgs, status);

    Assert_isTrue(resourceHandle != NULL, (Assert_Id)NULL);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */

    _resmanInternalState->freeFxn(&constructHandleMemRec, 1);

    if (IRES_OK != *status) {

        _freeResource(algHandle, scratchGroupId, edma3Chan, qdmaChan, numPaRams,
                paRamArray, numTccs, tccArray);

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandles> Error freeing memory ");

        Log_print0(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)");

        *status = IRES_EFAIL;

        if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
                scratchGroupId)) {

            *status = IRES_EFAIL;

            Log_print0(Diags_USER7,
                    "[+7] IRESMAN_EDMA3CHAN_getHandles> Error releasing Low level "
                    "Resource Manager Handle.");
        }

        return (NULL);
    }
    else {

        ((IRES_EDMA3CHAN2_Obj *)resourceHandle)->queueMap =
                _resmanInternalState->queueMap;

        resDesc->handle = (IRES_Obj *)resourceHandle;

        IRES_EDMA3CHAN_SETPROTOCOLREVISION_2_0_0(resDesc->revision);

        *status = IRES_OK;

        Log_print1(Diags_EXIT,
                "[+X] IRESMAN_EDMA3CHAN_getHandles> Exit (handle=0x%x, "
                "status=IRES_OK)", (IArg)resourceHandle);

        return (resourceHandle);
    }

}

/*
 *  ======== IRESMAN_EDMA3CHAN_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_EDMA3CHAN_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ResourceDescriptor * resDesc,
                Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;


    IRES_EDMA3CHAN_Handle resourceHandle = (IRES_EDMA3CHAN_Handle)
            algResourceHandle;

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);
    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY,
            "[+E] IRESMAN_EDMA3CHAN_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)",
            (IArg)algResourceHandle, (IArg)protocolArgs,
            (IArg)scratchGroupId);

    if (_resmanInternalState->initialized != 1) {

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_getHandle> RMAN_register call has not "
                "happened successfully\n. Please register EDMA3CHAN resource "
                "with RMAN before requesting or releasing resources.");

        status =  IRES_ENORESOURCE;
        return (status);
    }

    if (protocolArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    /*
         * Don't need to free resources unless they were acquired persistently,          * as otherwise we will release this particular handle
         */
        if (-1 == scratchGroupId) {

            status = _freeResource(algHandle, scratchGroupId,
                    resourceHandle->assignedEdmaChannelIndex,
                    resourceHandle->assignedQdmaChannelIndex,
                    resourceHandle->assignedNumPaRams,
                    resourceHandle->assignedPaRamIndices,
                    resourceHandle->assignedNumTccs,
                    resourceHandle->assignedTccIndices);
        }

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
            scratchGroupId)) {

        status = IRES_EFAIL;

        Log_print0(Diags_USER7,
                "[+7] IRESMAN_EDMA3CHAN_freeHandle> Error releasing Low level "
                "Resource Manager Handle.");
    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getNumMemRecs
            ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.getMemRecs((IRES_Handle)resourceHandle,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_EDMA3CHAN_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_EDMA3CHAN_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _resmanInternalState->freeFxn(resourceMemRecs, numMemRecs);

    Log_print1(Diags_EXIT,
            "[+X] IRESMAN_EDMA3CHAN_freeHandles> Exit (status=%d)", (IArg)status);

    return (status);
}

/*
 *  ======== _freeResource ========
 *  Actually free resources from the EDMA3 Low Level Resource Manager Handle
 */
static inline IRES_Status _freeResource(IALG_Handle algHandle,
       Int scratchGroupId, short edma3Chan, short qdmaChan,
       short numPaRams, short * paRamIndex, short numTccs, short * tccIndex)
{

    EDMA3_ResDesc resObj;
    IRES_Status status = IRES_OK;
    EDMA3_Handle rmHandle;
    int i;

    Log_print6(Diags_ENTRY, "[+E] _freeResource> Enter "
            "(algHandle=0x%x, scratchGroupId=%d, edma3Chan=%d, qdmaChan=%d, "
            "numPaRams=%d, numTccs=0x%x\n)",
            (IArg)algHandle, (IArg)scratchGroupId, (IArg)edma3Chan,
            (IArg)qdmaChan, (IArg)numPaRams, (IArg)numTccs);
    /*
     * Obtain Resource Manager handle corresponding to this algorithm in this
     * scratch Group
     */
    rmHandle = EDMA3_getResourceManager(algHandle, scratchGroupId);

     /*
      * Free all channel/param resources
      */
     if (IRES_EDMA3CHAN_CHAN_NONE != edma3Chan) {

         /*
          * Free allocated edma3 channel
          */
         resObj.type = EDMA3_RES_DMA_CHANNEL;
         resObj.resId = edma3Chan;
         if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

                      Log_print1(Diags_USER2,
                              "[+2] _freeResource> Error releasing edma channe"
                              "l %d", (IArg)edma3Chan);

             status = IRES_EFAIL;
         }
     }

    if (IRES_EDMA3CHAN_CHAN_NONE != qdmaChan) {

        /*
         * Free allocated qdma channel
         */
        resObj.type = EDMA3_RES_QDMA_CHANNEL;
        resObj.resId = qdmaChan;

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

            Log_print1(Diags_USER7,
                    "[+7] _freeResource> Error releasing qdma channel %d",
                    (IArg)qdmaChan);
            status = IRES_EFAIL;
        }
    }

    resObj.type = EDMA3_RES_PARAM_SET;

    for (i = 0; i < numPaRams; i++) {

        /*
         * Free the actual params back
         */
        resObj.resId = paRamIndex[i];

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

            Log_print1(Diags_USER2,
                    "[+2] _freeResource> Error releasing PaRam %d",
                    (IArg)(paRamIndex[i]));

            status = IRES_EFAIL;
        }
    }

    /*
     * Free Tcc
     */
    resObj.type = EDMA3_RES_TCC;
    for (i = 0; i < numTccs; i++) {

        resObj.resId = tccIndex[i];

        if (EDMA3_SOK != EDMA3_freeResource( rmHandle, &resObj)) {

                    Log_print1(Diags_USER2,
                            "[+2] _freeResource> Error releasing tcc %d",
                            (IArg)(tccIndex[i]));

            status = IRES_EFAIL;
        }
    }

    if (EDMA3_SOK != EDMA3_releaseResourceManager(algHandle,
            scratchGroupId)) {

        status = IRES_EFAIL;

        Log_print0(Diags_USER2,
                "[+2] _freeResource> Error releasing Low level "
                "Resource Manager Handle.");
    }

    Log_print1(Diags_EXIT, "[+X] _freeResource> Exit (status=%d)", (IArg)status);

    return (status);
}

__FAR__ IRESMAN_Fxns IRESMAN_EDMA3CHAN =  {
    IRESMAN_EDMA3CHAN_getProtocolName,
    IRESMAN_EDMA3CHAN_getProtocolRevision,
    IRESMAN_EDMA3CHAN_init,
    IRESMAN_EDMA3CHAN_exit,
    IRESMAN_EDMA3CHAN_getHandles,
    IRESMAN_EDMA3CHAN_freeHandle,
    NULL,
    NULL
};

IRESMAN_Edma3ChanParams IRESMAN_EDMA3CHAN_DEFAULTPARAM;

IRESMAN_Fxns * EDMA3CHAN_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_EDMA3CHAN));
}


IRESMAN_Params * EDMA3CHAN_getDefaultParams()
{
    IRESMAN_EDMA3CHAN_DEFAULTPARAM.baseConfig.size =
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_EDMA3CHAN_DEFAULTPARAM);
}
