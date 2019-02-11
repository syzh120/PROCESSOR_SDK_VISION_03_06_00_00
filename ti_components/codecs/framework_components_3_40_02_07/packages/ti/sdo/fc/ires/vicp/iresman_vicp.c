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
 *  ======== iresman_vicp.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_vicp_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_vicp.h"
#include "ires_vicp.h"
#include "iresman_protocol_vicp.h"


#define IRESMAN_VICP_RESOURCEFREE 0xFFFF

typedef enum IRES_VICP_RESOURCETYPE {
    IMX,
    VLCD,
    SEQ
} IRES_VICP_RESOURCETYPE;

/*
 *  ======== IRESMAN_VICP_InternalState ========
 *  Holds the internal state of an initialized object
 */
typedef struct IRESMAN_VICP_InternalState {
    /*
     * Memory alloc Function
     */
    IRESMAN_PersistentAllocFxn * allocFxn;

    /*
     * Memory free Function
     */
    IRESMAN_PersistentFreeFxn * freeFxn;

    Int IMXbusy;
    Int VLCDbusy;
    Int SEQbusy;          /* Keeps track of busy status of resource */
    short refCount[3];    /* Reference count of number of algs using
                                       the same resource */
    Void * base;
} IRESMAN_VICP_InternalState;

/*
 * Flag indicating if the resource manager is initialized
 */
__FAR__ static unsigned int _initialized = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
__FAR__ static IRESMAN_VICP_InternalState _resmanInternalState;



__FAR__ Registry_Desc ti_sdo_fc_ires_vicp_desc;

__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

/*
 * Function to return the name of the protocol
 */
String IRESMAN_VICP_getProtocolName()
{
    return IRESMAN_VICP_CONSTRUCTFXNS.getName();
}

/*
 * Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_VICP_getProtocolRevision()
{
    return IRESMAN_VICP_CONSTRUCTFXNS.getRevision();
}

/*
 *  ======== IRESMAN_VICP_init ========
 */
IRES_Status IRESMAN_VICP_init(IRESMAN_Params * initArgs)
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
{
    int i;
    IRESMAN_VicpParams * resmanArgs = (IRESMAN_VicpParams *)initArgs;
    Registry_Result result;

    if (!regInit) {
        /*
         *  Enable logging. We only want to do this once, since there is
         *  no Registry_removeModule().
         */
        result = Registry_addModule(&ti_sdo_fc_ires_vicp_desc,
                VICP_MODNAME);

        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_init();
            FCSettings_setDiags(VICP_MODNAME);
        }
        regInit = 1;
    }

    Assert_isTrue(initArgs != NULL, (Assert_Id)NULL);

    /*  Check if already initialized */
    if (_initialized) {
       return IRES_EEXISTS;
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState.allocFxn = resmanArgs->baseConfig.allocFxn;
    _resmanInternalState.freeFxn = resmanArgs->baseConfig.freeFxn;

    /*
     * Set resource status to default
     */
   _resmanInternalState.IMXbusy = IRESMAN_VICP_RESOURCEFREE;
   _resmanInternalState.VLCDbusy = IRESMAN_VICP_RESOURCEFREE;
   _resmanInternalState.SEQbusy = IRESMAN_VICP_RESOURCEFREE;

    for(i = 0; i < 3; i++) {
        _resmanInternalState.refCount[i] = 0;
    }

    /* Set Initalized flag to 1 if successful */
    _initialized = 1;

     return IRES_OK;
}

/*
 *  ======== IRESMAN_VICP_exit ========
 */
IRES_Status IRESMAN_VICP_exit()
{
    int i ;

    /* Check if initialized */
    if (!(_initialized)) {
        return IRES_ENOINIT;
    }

    /*
     * Free up any memory/resources that might be allocated in this module
     */
    _resmanInternalState.IMXbusy = IRESMAN_VICP_RESOURCEFREE;
    _resmanInternalState.VLCDbusy = IRESMAN_VICP_RESOURCEFREE;
    _resmanInternalState.SEQbusy = IRESMAN_VICP_RESOURCEFREE;

    for (i = 0; i < IRES_VICP_MAXRESOURCES; i++) {
        _resmanInternalState.refCount[i] = 0;
    }

    /* Set the initialized flag to zero again */
    _initialized = 0;

    return IRES_OK;
}

/*
 *  ======== IRESMAN_VICP_getHandles ========
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_VICP_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec protocolMemRecs[IRES_VICP_MAXRESOURCES];
    IALG_MemRec constructHandleMemRec;
    IRESMAN_VICP_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = NULL;
    Int numMemRecs = 0;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;


    /* Cast the protocolArgs */
    IRES_VICP_ProtocolArgs * configArgs =
            (IRES_VICP_ProtocolArgs *) protocolArgs;

    Assert_isTrue(configArgs, (Assert_Id)NULL);

    if (_initialized != 1) {
        Log_print0(Diags_USER7,
                "[+7] _IRESMAN_VICP_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register VICP resource "
                "with RMAN before requesting or releasing resources.");

        *status =  IRES_ENORESOURCE;
        return NULL;
    }

    /* Get IRES_VICP handle's memory requirements */
    numMemRecs = IRESMAN_VICP_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    Assert_isTrue(numMemRecs <= IRES_VICP_MAXRESOURCES, (Assert_Id)NULL);

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_VICP_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _resmanInternalState.allocFxn(&constructHandleMemRec, 1)) {
        *status =  IRES_ENOMEM;
        return NULL;
    }

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }

    Assert_isTrue(IALG_EXTERNAL == constructHandleMemRec.space,
            (Assert_Id)NULL);
    constructArgs = constructHandleMemRec.base;
    constructArgs->base = _resmanInternalState.base;
    (constructArgs->args).size = sizeof(IRESMAN_VICP_ConstructHandleArgs);

    constructArgs->persistent = (scratchGroupId == -1) ? TRUE : FALSE;

    if ( configArgs->requestIMX ) {
        if (_resmanInternalState.IMXbusy == IRESMAN_VICP_RESOURCEFREE){
            _resmanInternalState.IMXbusy = scratchGroupId;
            _resmanInternalState.refCount[IMX] = 1;
            constructArgs->assignedIMX = 1;
        }
        else if (( -1 != _resmanInternalState.IMXbusy) &&
                (_resmanInternalState.IMXbusy == scratchGroupId)) {
            _resmanInternalState.refCount[IMX]++;
            constructArgs->assignedIMX = 1;
        }
        else {
           *status = IRES_ENORESOURCE;
            constructArgs->assignedIMX = 0;
            goto getHandleEnd;
        }
    }

    if (configArgs->requestVLCD) {
        if (_resmanInternalState.VLCDbusy == IRESMAN_VICP_RESOURCEFREE) {
            _resmanInternalState.VLCDbusy = scratchGroupId;
            _resmanInternalState.refCount[VLCD] = 1;
            constructArgs->assignedVLCD = 1;
        }
        else if (( -1 != _resmanInternalState.VLCDbusy) &&
                (_resmanInternalState.VLCDbusy == scratchGroupId)) {
            _resmanInternalState.refCount[VLCD]++;
            constructArgs->assignedVLCD = 1;
        }
        else {
           *status = IRES_ENORESOURCE;
            constructArgs->assignedVLCD = 0;
            goto getHandleEnd;
        }

    }

    if (configArgs->requestSEQ) {
        if (_resmanInternalState.SEQbusy == IRESMAN_VICP_RESOURCEFREE) {
            _resmanInternalState.SEQbusy = scratchGroupId;
            _resmanInternalState.refCount[SEQ] = 1;
            constructArgs->assignedSEQ = 1;
        }
        else if (( -1 != _resmanInternalState.SEQbusy) &&
                (_resmanInternalState.SEQbusy == scratchGroupId)) {
            _resmanInternalState.refCount[SEQ]++;
            constructArgs->assignedSEQ = 1;
        }
        else {
           *status = IRES_ENORESOURCE;
            constructArgs->assignedSEQ = 0;
            goto getHandleEnd;
        }
    }

getHandleEnd:
    if (*status != IRES_OK) {

       if (constructArgs->assignedIMX == 1) {
           _resmanInternalState.refCount[IMX]--;
            if (_resmanInternalState.refCount[IMX] == 0 ) {
                _resmanInternalState.IMXbusy = IRESMAN_VICP_RESOURCEFREE;
            }
        }
        else if (constructArgs->assignedVLCD == 1) {
           _resmanInternalState.refCount[VLCD]--;
            if (_resmanInternalState.refCount[VLCD] == 0 ) {
                _resmanInternalState.VLCDbusy = IRESMAN_VICP_RESOURCEFREE;
            }
        }
        else if (constructArgs->assignedSEQ == 1) {
           _resmanInternalState.refCount[SEQ]--;
            if (_resmanInternalState.refCount[SEQ] == 0 ) {
                _resmanInternalState.SEQbusy = IRESMAN_VICP_RESOURCEFREE;
            }
        }

    }
    else {
       /*
        * Obtain memory resources to build the handle
        */
       IRESMAN_VICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
                (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

        /*
         * Allocate that memory
         */
        if (FALSE == _resmanInternalState.allocFxn(protocolMemRecs,
                numMemRecs)) {
            *status = IRES_ENOMEM;
            resourceHandle = NULL;
        }
        else {
           /*
            * Use the CONSTRUCT interface of the protocol implementation to
            * construct the handle within the allocated resource
            */
            resourceHandle = IRESMAN_VICP_CONSTRUCTFXNS.constructHandle(
                    protocolArgs, protocolMemRecs,
                            (IRESMAN_ConstructArgs *)constructArgs, status);
        }
    }

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

    resDesc->handle = (IRES_Obj *)resourceHandle;

    resDesc->revision->Major = 1;
    resDesc->revision->Source = 0;
    resDesc->revision->Radius = 0;

    return (resourceHandle);
}

/*
 *  ======== IRESMAN_VICP_freeHandles ========
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_VICP_freeHandles(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor * resDesc,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[IRES_VICP_MAXRESOURCES];
    Int numMemRecs;
    IRES_ProtocolArgs * protocolArgs = resDesc->protocolArgs;

    IRES_VICP_Handle resourceHandle = (IRES_VICP_Handle)
            algResourceHandle;
    /*
     * Cast the protocolArgs
     */
    /*
    IRES_VICP_ProtocolArgs * configArgs =
            (IRES_VICP_ProtocolArgs *) protocolArgs;

    Assert_isTrue(configArgs, (Assert_Id)NULL);
    */

    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    Assert_isTrue(protocolArgs, (Assert_Id)NULL);
    Assert_isTrue(algResourceHandle, (Assert_Id)NULL);

    if (_initialized != 1) {
        Log_print0(Diags_USER7,
                "[+7] _IRESMAN_VICP_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register VICP resource "
                "with RMAN before requesting or releasing resources.");

        return (IRES_ENORESOURCE);
    }

    /*
    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    }
    */

    /*
     * Free the handles to the resource manager
     */
    if (resourceHandle->assignedIMX == 1) {
        if (_resmanInternalState.refCount[IMX] == 0) {
            return (IRES_ENORESOURCE);
        }
        _resmanInternalState.refCount[IMX]--;
        if (_resmanInternalState.refCount[IMX] == 0 ) {
            _resmanInternalState.IMXbusy = IRESMAN_VICP_RESOURCEFREE;
        }
    }
    else if (resourceHandle->assignedVLCD == 1) {
        if (_resmanInternalState.refCount[VLCD] == 0) {
            return IRES_ENORESOURCE;
        }
        _resmanInternalState.refCount[VLCD]--;
        if (_resmanInternalState.refCount[VLCD] == 0 ) {
            _resmanInternalState.VLCDbusy = IRESMAN_VICP_RESOURCEFREE;
        }
    }
    else if (resourceHandle->assignedSEQ == 1) {
        if (_resmanInternalState.refCount[SEQ] == 0) {
            return (IRES_ENORESOURCE);
        }
        _resmanInternalState.refCount[SEQ]--;
        if (_resmanInternalState.refCount[SEQ] == 0 ) {
            _resmanInternalState.SEQbusy = IRESMAN_VICP_RESOURCEFREE;
        }
    }


    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_VICP_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_VICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_VICP_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_VICP_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(resourceMemRecs, numMemRecs);

    return (IRES_OK);
}


IRESMAN_Fxns IRESMAN_VICP =  {
    IRESMAN_VICP_getProtocolName,
    IRESMAN_VICP_getProtocolRevision,
    IRESMAN_VICP_init,
    IRESMAN_VICP_exit,
    IRESMAN_VICP_getHandles,
    IRESMAN_VICP_freeHandles,
    NULL,
    NULL
};

IRESMAN_VicpParams IRESMAN_VICP_DEFAULTPARAM;

IRESMAN_Fxns * VICP_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_VICP));
}


IRESMAN_Params * VICP_getDefaultParams()
{
    IRESMAN_VICP_DEFAULTPARAM.baseConfig.size =
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_VICP_DEFAULTPARAM);
}
