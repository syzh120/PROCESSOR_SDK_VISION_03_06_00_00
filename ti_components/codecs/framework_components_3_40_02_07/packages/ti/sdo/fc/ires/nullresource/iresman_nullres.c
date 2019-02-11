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
 *  ======== iresman_nullres.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_nullres_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <xdc/runtime/Registry.h>

#include "iresman_nullres.h"
#include "ires_nullres.h"

#include <ti/sdo/fc/global/FCSettings.h>

static Void _getStaticProperties(struct IRES_Obj * resourceHandle,
        IRES_Properties *resourceProperties);

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_NULLRES_InternalState {

    /*
     * Memory alloc Function
     */
    IRESMAN_PersistentAllocFxn * allocFxn;

    /*
     * Memory free Function
     */
    IRESMAN_PersistentFreeFxn * freeFxn;

} IRESMAN_NULLRES_InternalState;

/*
 * Flag indicating if the resource manager is initialized
 */
__FAR__ static unsigned int _initialized = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
__FAR__ static IRESMAN_NULLRES_InternalState _resmanInternalState;


__FAR__ Registry_Desc ti_sdo_fc_ires_nullres_desc;

__FAR__ static Int regInit = 0;  /* Registry_addModule() called */
/**
 * Function to return the name of the protocol
 */
String IRESMAN_NULLRES_getProtocolName()
{
/*         return IRESMAN_NULLRES_CONSTRUCTFXNS.getName();*/
        return IRES_NULLRES_PROTOCOLNAME;
}

/**
 * Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_NULLRES_getProtocolRevision()
{
/*         return IRESMAN_NULLRES_CONSTRUCTFXNS.getRevision();*/
        return &IRES_NULLRES_PROTOCOLREVISION;
}

/**
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_NULLRES_init(IRESMAN_Params * initArgs)
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
{
#ifndef xdc_runtime_Assert_DISABLE_ALL
    Registry_Result   result;
#endif

    /*
     *  Register the module name for logging only once. Do this before any
     *  Log functions are called.
     */
    if (!regInit) {
#ifndef xdc_runtime_Assert_DISABLE_ALL
        result =
#endif
                Registry_addModule(&ti_sdo_fc_ires_nullres_desc,
                NULLRES_MODNAME);

        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        /* Set diags mask to FC default */
        FCSettings_init();
        FCSettings_setDiags(NULLRES_MODNAME);
        regInit = 1;
    }
    /*
     *  Check if already initialized
     */
    if (_initialized) {
       return (IRES_EEXISTS);
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState.allocFxn = initArgs->allocFxn;

    _resmanInternalState.freeFxn = initArgs->freeFxn;

    /*
     * Set Initalized flag to 1 if successful
     */
     _initialized = 1;

     return (IRES_OK);
}

/**
 * Function called when RESMAN is no longer needed. Use it to free memory
 * allocated etc
 */
IRES_Status IRESMAN_NULLRES_exit()
{
    /*
     * Check if initialized
     */
    if (!(_initialized)) {
        return IRES_ENOINIT;
    }

    /*
     * Set the initialized flag to zero again
     */
    _initialized = 0;

    return IRES_OK;
}

/*
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_NULLRES_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec memrec;
    IRES_NULLRES_Handle resourceHandle = (IRES_NULLRES_Handle)NULL;

    memrec.size = sizeof(IRES_NULLRES_Obj);
    memrec.alignment = 4;
    memrec.space = IALG_EXTERNAL;
    memrec.attrs = IALG_PERSIST;

    if (FALSE == _resmanInternalState.allocFxn(&memrec,1)) {
        *status = IRES_ENOMEM;
        return ((IRES_Handle)NULL);
    }

    if (_initialized != 1) {
        Log_print0(Diags_USER7,
                "[+7] _IRESMAN_NULLRES_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register NULL resource "
                "with RMAN before requesting or releasing resources.");

        *status =  IRES_ENORESOURCE;
        return NULL;
    }

    Assert_isTrue(memrec.space == IALG_EXTERNAL, (Assert_Id)NULL);

    resourceHandle = memrec.base;

    resourceHandle->ires.getStaticProperties = _getStaticProperties;

    resDesc->handle = (IRES_Obj *)resourceHandle;

    resDesc->revision->Major = 1;
    resDesc->revision->Source = 0;
    resDesc->revision->Radius = 0;

    *status = IRES_OK;
    return ((IRES_Handle)resourceHandle);
}

/**
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_NULLRES_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ResourceDescriptor * resDesc,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs;
    IRES_Status status = IRES_OK;

    if (_initialized != 1) {
        Log_print0(Diags_USER7,
                "[+7] _IRESMAN_NULLRES_getHandles> RMAN_register call has not "
                "happened successfully. Please register NULL resource "
                "with RMAN before requesting or releasing resources.");

        status =  IRES_ENORESOURCE;
        return status;
    }

    resourceMemRecs.base = algResourceHandle;
    resourceMemRecs.size = sizeof(IRES_NULLRES_Obj);
    resourceMemRecs.space = IALG_EXTERNAL;

    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(&resourceMemRecs, 1);

    return status;
}

/*  ARGSUSED - this line tells the compiler not to warn about unused args */
static Void _getStaticProperties(struct IRES_Obj * resourceHandle,
        IRES_Properties *resourceProperties)
{
}

IRESMAN_Fxns IRESMAN_NULLRES =  {
    IRESMAN_NULLRES_getProtocolName,
    IRESMAN_NULLRES_getProtocolRevision,
    IRESMAN_NULLRES_init,
    IRESMAN_NULLRES_exit,
    IRESMAN_NULLRES_getHandles,
    IRESMAN_NULLRES_freeHandle,
    NULL,
    NULL
};
