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
 *  ======== rman.c ========
 *  Generic IRES Resource Manager for managing IRES Resources and Protocols
 */
/* TODO: Will need a shared memory region to hold the IRES IALG vtable info */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_rman_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/dskt2/dskt2.h>

#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>
#include <ti/sdo/fc/global/FCSettings.h>

#include <string.h>
#include <stdlib.h>

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <fcntl.h>
#include <ti/sdo/fc/utils/shm.h>
#endif

/*
 * Since we will be pre-registering the NULL resource
 */
#include <ti/sdo/fc/ires/nullresource/iresman_nullres.h>

#include "rman.h"

/* Id offset from _RMAN_ipcKeyBase to shared memory containing RMAN object */
#define _RMAN_SHMID (ti_sdo_fc_rman_RMAN_ipcKey)

/* Id offset from _RMAN_ipcKeyBase to semaphore used for critical sections */
#define _RMAN_CSID (ti_sdo_fc_rman_RMAN_ipcKey + 1)

/* Id offset from _RMAN_ipcKeyBase to lock used for protecting RMAN object */
#define _RMAN_LOCKID (ti_sdo_fc_rman_RMAN_ipcKey + 2)

/* Id offset from _RMAN_ipcKeyBase to semaphore used for managing scratch
   RMAN memory resources */
#define _RMAN_MEMID (ti_sdo_fc_rman_RMAN_ipcKey + 3)

extern __FAR__ unsigned int ti_sdo_fc_rman_RMAN_MAXALGS;

extern __FAR__ UInt32 ti_sdo_fc_rman_RMAN_ipcKey;

extern IRES_YieldArgs (* ti_sdo_fc_rman_RMAN_setYieldArgs)
        (Int scratchId, Bool yieldFlag);

extern IRES_Status RMAN_autoRegister();

typedef struct RMAN_InternalStateInfo {

    int index;

    int maxEntries;

    int refCount;

    int sharedMemId;

    unsigned int vTableOffset;

    int numOpens;

} RMAN_InternalStateInfo;

typedef  struct RMAN_VtableEntry {

    unsigned int * algVtable;

    unsigned int * resVtable;

    int refs;

} RMAN_VtableEntry;

typedef struct RMAN_InternalState {

    RMAN_InternalStateInfo info;

} RMAN_InternalState;

/*
 *  ======== RMAN_TableState ========
 *  State information about the RMAN_Table that holds all the Resource Manager
 *  entries
 */
typedef struct RMAN_TableState {

    short tableSize;              /* Current size of Resource Manager table */

    short tableIndex;             /* Index pointing to the next free entry */

    short freeIndex;              /* Index pointing to the last free entry in
                                      Free table */
} RMAN_TableState;

static __FAR__ RMAN_TableState resTable;  /* Resource Manager table (IRESMAN impl.) */

static __FAR__ short rmanInit = 0;                    /* Count of RMAN_init calls */
static __FAR__ IRES_Status initStatus = IRES_ENOINIT; /* Outcome of RMAN_init */
static __FAR__ RMAN_InternalState * rmanInternalState = NULL;
static __FAR__ RMAN_VtableEntry * algresVTable = NULL;

/* Function that checks if two versions are compatible */
static Bool checkResMgrAlgRevision(IRES_ProtocolRevision *resMgrVer,
        IRES_ProtocolRevision *algVer);

static IRESMAN_Fxns * getResman(String name, IRES_ProtocolRevision * revision);
static Void *myAlloc(size_t size, size_t align);
static Void myFree(Ptr addr, size_t size);

static void getInternalState();
static void setInternalState();
static void freeInternalState();

static inline Bool addVTableEntry(IALG_Handle  alg, IRES_Fxns * res);
static inline Bool freeVTableEntry(IALG_Handle alg, IRES_Fxns * res);

#ifndef xdc_target__os_Linux
IRES_Fxns * RMAN_getIresEntry(IALG_Handle alg);
IALG_Fxns * RMAN_getIAlgEntry(IRES_Fxns * alg);
#endif
__FAR__ Registry_Desc ti_sdo_fc_rman_desc;

static __FAR__ IGateProvider_Handle gate = NULL;


/*
 *  ======== RMAN_assignResources ========
 *  Assign resources to the algorithm indicated by alg. The resource
 *  requirements can be determined by using the IRES_Fxns implementation
 */
IRES_Status RMAN_assignResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    Int              numResources;
    Int              k;
    Int              n = 0;
    size_t           resDescSize;
    IRESMAN_Fxns   * resman = NULL;
    IRES_Status      status = IRES_OK;
    IRES_Status      freeStatus = IRES_OK;
    IRES_Status      algStatus = IRES_OK;
    IRES_YieldFxn    yieldFxn = NULL;
    IRES_YieldArgs * yieldArgs = NULL;
    IRES_ResourceDescriptor * resDesc = NULL;
    IArg             key;


    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_assignResources> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_assignResources> "
                "Exit (status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Assert_isTrue(resFxns != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.freeFxn != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] RMAN_assignResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)",
            (IArg)alg, (IArg)resFxns, (IArg)scratchGroupId);

    /*
     *  Get resource requirements of the algorithm
     */
    numResources = (resFxns->numResourceDescriptors)(alg);
    resDescSize = numResources * sizeof(IRES_ResourceDescriptor);

    /* Allocate memory to hold algorithm's resource descriptors */
    if ((resDesc = myAlloc(resDescSize, 0)) == NULL) {
        Log_print1(Diags_USER7, "[+7] RMAN_assignResources> "
                "Could not allocate memory size 0x%x in space "
                "IALG_EXTERNAL of type IALG_PERSIST", (IArg)resDescSize);

        Log_print0(Diags_EXIT, "[+X] RMAN_assignResources> "
                "Exit (status=IRES_ENOMEM)");

        return (IRES_ENOMEM);
    }

    algStatus = resFxns->getResourceDescriptors(alg, resDesc);

    if (algStatus != IRES_OK) {
        Log_print3(Diags_USER7, "[+7] RMAN_assignResources> Error obtaining "
                "Resource Descriptors [status: %d] from alg 0x%x, "
                "IRES interface 0x%x",
                (IArg)algStatus, (IArg)alg, (IArg)resDesc);

        status = IRES_EALG;
    }

    if (status == IRES_OK) {
        /* For each requested resource */
        for (n = 0 ; n < numResources; n++) {
            /* If someone populated the resource descriptor improperly, bail */
            if ((resDesc[n].resourceName == NULL) ||
                    (resDesc[n].revision == NULL)) {

                Log_print0(Diags_USER7, "[+7] RMAN_assignResources> "
                        "Resource protocol and/or version were NULL. "
                        "Most likely an issue  with the algorithm's "
                        "getResourceRequestDescriptor implementation.");

                status = IRES_EALG;
                break;
            }

            resman = getResman(resDesc[n].resourceName, resDesc[n].revision);

            if (resman != NULL) {
                /*
                 *  Call getHandle on the IRESMAN implementation using
                 *  the protocolArgs extracted.
                 */
                Log_print1(Diags_USER2, "[+2] RMAN_assignResources> Call "
                        "getHandle on the IRESMAN implementation 0x%x",
                        (IArg)resman);

                /* Acquire lock */
                key = IGateProvider_enter(gate);

                resDesc[n].handle = resman->getHandle(alg, &resDesc[n],
                        scratchGroupId, &status);

                /* Release lock */
                IGateProvider_leave(gate, key);

                if (IRES_OK != status) {
                    break;
                }
            }
            else {
                Log_print2(Diags_USER7, "[+7] RMAN_assignResources> "
                        "Resource protocol %s and version 0x%x didn't match "
                        "any registered protocol.",
                        (IArg)(resDesc[n].resourceName),
                        (IArg)(resDesc[n].revision));

                status = IRES_ENOTFOUND;
                break;
            }
        }
    }

    /* n = number of resources allocated */

    /*
     * Return those handles to IALG using the appropriate IRES call
     */
    if (IRES_OK == status) {

        if ((RMAN_PARAMS.yieldFxn != NULL) &&
                (ti_sdo_fc_rman_RMAN_setYieldArgs != NULL)) {

            yieldFxn = RMAN_PARAMS.yieldFxn;

            yieldArgs = ti_sdo_fc_rman_RMAN_setYieldArgs(scratchGroupId,
                    RMAN_PARAMS.yieldSamePriority);
        }

        /* Acquire lock */
        key = IGateProvider_enter(gate);

        algStatus = resFxns->initResources(alg, resDesc, yieldFxn, yieldArgs);

        /* Release lock */
        IGateProvider_leave(gate, key);

        if (algStatus != IRES_OK) {
            Log_print1(Diags_USER7, "[+7] RMAN_assignResources> "
                    "resFxns->initResources() failed [%d]", (IArg)algStatus);
            status = IRES_EALG;
        }
    }

    if (status != IRES_OK) {
        /*
         *  Error somewhere in initialization of resource handles
         *  Free all allocated handles.
         */

        for (k = 0; k < n; k++) {
            resman = getResman(resDesc[k].resourceName, resDesc[k].revision);

            if (NULL == resman) {
                /* Resource table is messed up - bail out */
                Log_print2(Diags_USER7, "[+7] RMAN_assignResources> Could "
                        "not find IRESMAN matching resource %s version 0x%x",
                        (IArg)(resDesc[k].resourceName),
                        (IArg)(resDesc[k].revision));

                status = IRES_EFAIL;
                break;
            }

            /* Acquire lock */
            key = IGateProvider_enter(gate);

            freeStatus = resman->freeHandle(alg, resDesc[k].handle, &resDesc[k],
                                scratchGroupId);

            /* Release lock */
            IGateProvider_leave(gate, key);

            if (freeStatus != IRES_OK) {
                /*
                 *  If we can't free the resource handle, something is really
                 *  messed up. Don't try to free anything else.
                 */
                status = IRES_EFAIL;
                Log_print2(Diags_USER7, "[+7] RMAN_assignResources> Free "
                        "handle failed [%d] on IRESMAN implementation 0x%x",
                        (IArg)status, (IArg)resman);

                break;
            }
        }
    }
    else {
        /* Status is OKAY, add entry to table */
        /*
        if (FALSE == addVTableEntry((IALG_Fxns *)alg->fxns,
                resFxns)) {
        */
        if (FALSE == addVTableEntry((IALG_Handle)alg, resFxns)) {
/* TODO: Add trace */
            status = IRES_EFAIL;
            RMAN_freeResources(alg, resFxns, scratchGroupId);
        }
    }

    if (resDesc) {
        myFree(resDesc, resDescSize);
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_assignResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}
/*
 *  ======== RMAN_allocateResources ========
 *  Directly allocate IRES resources by client without implementing IRES_Fxns
 */
IRES_Status RMAN_allocateResources(Int requestId,
        IRES_ResourceDescriptor * resDesc, Int numResources, Int scratchGroupId)
{
    Int              n = 0;
    IRESMAN_Fxns   * resman = NULL;
    IRES_Status      status = IRES_OK;
    IArg             key;


    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_allocateResources> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_allocateResource> "
                "Exit (status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Assert_isTrue(resDesc != NULL, (Assert_Id)NULL);
    Assert_isTrue(numResources >=1, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.freeFxn != NULL, (Assert_Id)NULL);

    Log_print4(Diags_ENTRY, "[+E] RMAN_allocateResources> Enter "
            "requestId=%d, (resDesc=0x%x, numResources=%d, scratchGroupId=%d)",
            (IArg)requestId, (IArg)resDesc, (IArg)numResources,
            (IArg)scratchGroupId);

    /*
     *  Allocate requested resources one by one.
     */
    if (status == IRES_OK) {
        /* For each requested resource */
        for (n = 0 ; n < numResources; n++) {
            /* If someone populated the resource descriptor improperly, bail */
            if ((resDesc[n].resourceName == NULL) ||
                    (resDesc[n].revision == NULL)) {

                Log_print0(Diags_USER7, "[+7] RMAN_allocateResources> "
                        "Resource protocol and/or version were NULL. "
                        "Most likely an issue  with the algorithm's "
                        "getResourceRequestDescriptor implementation.");

                status = IRES_EALG;
                break;
            }

            resman = getResman(resDesc[n].resourceName, resDesc[n].revision);

            if (resman != NULL) {
                /*
                 *  Call getHandle on the IRESMAN implementation using
                 *  the protocolArgs extracted.
                 */
                Log_print1(Diags_USER2, "[+2] RMAN_allocateResources> Call "
                        "getHandle on the IRESMAN implementation 0x%x",
                        (IArg)resman);

                /* Acquire lock */
                key = IGateProvider_enter(gate);

                resDesc[n].handle = resman->getHandle((IALG_Handle)requestId,
                        &resDesc[n], scratchGroupId, &status);

                /* Release lock */
                IGateProvider_leave(gate, key);

                if (IRES_OK != status) {
                    break;
                }
            }
            else {
                Log_print2(Diags_USER7, "[+7] RMAN_allocateResources> "
                        "Resource protocol %s and version 0x%x didn't match "
                        "any registered protocol.",
                        (IArg)(resDesc[n].resourceName),
                        (IArg)(resDesc[n].revision));

                status = IRES_ENOTFOUND;
                break;
            }
        }
    }

    /*
     * Return those handles to IALG using the appropriate IRES call
     */
    if (FALSE == addVTableEntry((IALG_Handle)requestId, (IRES_Fxns *)NULL)) {
    /* TODO: Add trace */
            status = IRES_EFAIL;

            RMAN_freeAllocatedResources(requestId, resDesc, numResources,
                    scratchGroupId);
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_allocateResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== RMAN_exit ========
 *  Exit the generic IRES RMAN and free the memory back to the Memory manager
 *  using which it was created.
 */
IRES_Status RMAN_exit()
{
    IArg        key;
    Int         i;
    IRES_Status status = IRES_OK;


    if (rmanInit == 0) {
        return (IRES_ENOINIT);
    }

    Log_print0(Diags_ENTRY, "[+E] RMAN_exit> Enter ");

    rmanInternalState->info.refCount--;

    if (--rmanInit == 0) {
        if (initStatus != IRES_OK) {
            Log_print0(Diags_USER7, "[+7] RMAN_exit> RMAN_init call didn't "
                    "happen successfully. RMAN_exit will not unregister "
                    "any resources.");
            status = IRES_ENOINIT;
        }
        else {
            key = IGateProvider_enter(gate);

            Log_print1(Diags_EXIT, "[+X] RMAN_exit> tableIndex = %d",
                    (IArg)(resTable.tableIndex));

            /* Unregister the entries */
            Log_print0(Diags_EXIT, "[+X] RMAN_exit> Unregistering resources");

            for (i = 0; i < resTable.tableIndex; i++) {
                if (RMAN_TABLE[i] != NULL) {

                    /* Even if there is an error, unregister the rest */
                    if ((status = RMAN_TABLE[i]->exit()) != IRES_OK) {
                        Log_print2(Diags_USER7, "[+7] RMAN_exit> Error "
                                "unregistering the IRESMAN implementation "
                                "0x%x, status = %d",
                                (IArg)(RMAN_TABLE[i]), (IArg)status);
                        status = IRES_EFAIL;
                    }
                }
            }
            /* Free the RMAN object */
            freeInternalState();

            initStatus = IRES_ENOINIT;

            /* Free the gate after leaving it */
            IGateProvider_leave(gate, key);
            OsalSupport_deleteGate(gate);
            gate = NULL;
        }
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_exit> Exit (status=%d)", (IArg)status);

    return (status);
}

/*
 *  ======== RMAN_freeResources ========
 *  Free resources held by the algorithm resource handle
 */
IRES_Status RMAN_freeResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    short           numResources;
    short           i;
    size_t          resDescSize;
    IRESMAN_Fxns  * resman = NULL;
    IArg            key;
    IRES_Status     status = IRES_OK;
    IRES_ResourceDescriptor * resDesc = NULL;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_freeResources> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_freeResources> "
                "Exit (status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Assert_isTrue(resFxns != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.freeFxn != NULL, (Assert_Id)NULL);

    Log_print3(Diags_ENTRY, "[+E] RMAN_freeResources> Enter "
            "(alg=0x%x, resFxns=0x%x, scratchGroupId=%d)",
            (IArg)alg, (IArg)resFxns, (IArg)scratchGroupId);


    /*
     *  Get resource descriptors held by the algorithm
     */
    numResources = (resFxns->numResourceDescriptors)(alg);
    resDescSize = numResources * sizeof(IRES_ResourceDescriptor);

    /* Allocate memory for algorithm's resource descriptors */
    if ((resDesc = myAlloc(resDescSize, 0)) == NULL) {
        Log_print0(Diags_USER7, "[+7] RMAN_freeResources> Memory "
                "allocation failed");

        status = IRES_ENOMEM;
    }

    if (status == IRES_OK) {
        if (IRES_OK != (resFxns->getResourceDescriptors(alg, resDesc))) {

            Log_print2(Diags_USER7, "[+7] RMAN_freeResources> Error "
                    "obtaining Resource Descriptors from alg 0x%x with IRES "
                    "interface 0x%x", (IArg)alg, (IArg)resDesc);

            status = IRES_ENORESOURCE;
        }
    }

    if (status == IRES_OK) {
        /* Deinit the Resources that were granted to the algorithm */
        if (IRES_OK != (resFxns->deinitResources(alg, resDesc))) {

            Log_print2(Diags_USER7, "[+7] RMAN_freeResources> "
                    "De-init failed on alg 0x%x IRES interface 0x%x",
                    (IArg)alg, (IArg)resDesc);

            status = IRES_EALG;
        }

        for (i = 0 ; i < numResources; i++) {
            resman = getResman(resDesc[i].resourceName, resDesc[i].revision);

            if (NULL == resman) {
                Log_print2(Diags_USER7, "[+7] RMAN_freeResources> IRESMAN "
                        "handle not found for resource %s version 0x%x",
                        (IArg)(resDesc[i].resourceName),
                        (IArg)(resDesc[i].revision));

                status = IRES_ENOTFOUND;
            }
            else {
                /*
                 *  Call freeHandle on resman Implementation and deinit
                 *  resources held by the algorithm
                 */
                key = IGateProvider_enter(gate);

                status = resman->freeHandle(alg, resDesc[i].handle, &resDesc[i],
                                                scratchGroupId);

                IGateProvider_leave(gate, key);

                if (status != IRES_OK) {
                    /* TODO: Some SYS ABORT type error here */
                    Log_print1(Diags_USER7,
                            "[+7] RMAN_freeResources> Free handle failed on IRESMAN"
                            " implementation 0x%x", (IArg)resman);

                    status = IRES_EFAIL;
                }
            }
        }
    }

    if (FALSE == freeVTableEntry((IALG_Handle )alg, resFxns)) {
/* TODO: Add trace */
        status = IRES_EFAIL;
    }

    if (resDesc) {
        myFree(resDesc, resDescSize);
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_freeResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== RMAN_freeAllocatedResources ========
 *  Free resources that were directly allocated by RMAN_allocateResources
 */
IRES_Status RMAN_freeAllocatedResources (Int requestId,
        IRES_ResourceDescriptor * resDesc, Int numResources, Int scratchGroupId)
{
    short           i;
    IRESMAN_Fxns  * resman = NULL;
    IArg            key;
    IRES_Status     status = IRES_OK;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_freeAllocatedResources> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_freeAllocatedResources> "
                "Exit (status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Assert_isTrue(RMAN_PARAMS.allocFxn != NULL, (Assert_Id)NULL);
    Assert_isTrue(RMAN_PARAMS.freeFxn != NULL, (Assert_Id)NULL);

    Log_print4(Diags_ENTRY, "[+E] RMAN_freeAllocatedResources> Enter "
            "requestId=%d, (resDesc=0x%x, numResources=%d, scratchGroupId=%d)",
            (IArg)requestId, (IArg)resDesc, (IArg)numResources,
            (IArg)scratchGroupId);

    for (i = 0 ; i < numResources; i++) {
            resman = getResman(resDesc[i].resourceName, resDesc[i].revision);

        if (NULL == resman) {
            Log_print2(Diags_USER7, "[+7] RMAN_freeAllocatedResources> IRESMAN "
                    "handle not found for resource %s version 0x%x",
                    (IArg)(resDesc[i].resourceName),
                    (IArg)(resDesc[i].revision));

            status = IRES_ENOTFOUND;
        }
        else {
            /*
             *  Call freeHandle on resman Implementation and deinit
             *  resources held by the algorithm
             */
            key = IGateProvider_enter(gate);

            status = resman->freeHandle((IALG_Handle)requestId,
                     resDesc[i].handle, &resDesc[i], scratchGroupId);

            IGateProvider_leave(gate, key);

            if (status != IRES_OK) {
                /* TODO: Some SYS ABORT type error here */
                Log_print1(Diags_USER7,
                        "[+7] RMAN_freeAllocatedResources> Free handle failed "
                        "on IRESMAN implementation 0x%x", (IArg)resman);

                status = IRES_EFAIL;
            }
        }
    }

    if (FALSE == freeVTableEntry((IALG_Handle)requestId, (IRES_Fxns *)NULL)) {
/* TODO: Add trace */
        status = IRES_EFAIL;
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_freeResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== RMAN_init ========
 *  Initialize the RMAN object with static information from the headers/
 *  configuration etc. This function has to return successfully before the
 *  other APIs can be called
 */
IRES_Status RMAN_init()
{

    __FAR__ static Int regInit = 0;  /* Registry_addModule() called */
    Int             i = 0;
    IRES_Status     status;
    IRESMAN_Params  nullParams;
#ifndef xdc_runtime_Assert_DISABLE_ALL
    Registry_Result regResult;
#endif


    /*
     *  Register the module name for logging only once. Do this before any
     *  Log functions are called.
     */
    if (regInit == 0) {
#ifndef xdc_runtime_Assert_DISABLE_ALL
        regResult =
#endif
                Registry_addModule(&ti_sdo_fc_rman_desc, RMAN_MODNAME);
        Assert_isTrue(regResult == Registry_SUCCESS, (Assert_Id)NULL);

        /* Set diags mask to FC default */
        FCSettings_init();
        FCSettings_setDiags(RMAN_MODNAME);
        regInit = 1;
    }

    /* Ensure it is called/initialized at least once */
    if (rmanInit++) {
        Log_print0(Diags_ENTRY, "[+E] RMAN_init> Enter");
        Log_print0(Diags_EXIT, "[+X] RMAN_init> Exit (status=IRES_OK)");

        /* TODO: Return IRES_OK even if RMAN_init() failed earlier? */
        return (IRES_OK);
    }

    Log_print0(Diags_ENTRY, "[+E] RMAN_init> Enter");

    if ((NULL == RMAN_PARAMS.allocFxn) || (NULL == RMAN_PARAMS.freeFxn)) {
        Log_print0(Diags_USER7, "[+7] RMAN_init> RMAN_PARAMS not "
                "configured with allocFxn and freeFxn functions");

        initStatus = IRES_ENOMEM;
    }
    else {
        /* Set initStatus to IRES_OK so RMAN_register() can succeed. */
        initStatus = IRES_OK;
    }

    if (initStatus == IRES_OK) {
        /* Create a lock for protecting RMAN_data object */
        gate = OsalSupport_createGate(ti_sdo_fc_rman_RMAN_ipcKey);

        if (gate == NULL) {
            Log_print1(Diags_USER7,
                    "[+7] RMAN_init> Failed to create IPC gate, key = 0x%x",
                    ti_sdo_fc_rman_RMAN_ipcKey);

            initStatus = IRES_ENOMEM;
        }
    }

    if (initStatus == IRES_OK) {
        /*
         *  Register the NULL resource.
         */
        resTable.tableSize = RMAN_PARAMS.numRegistries;

        /* Initialize the registry table and the free index table */
        for (i = 0; i < resTable.tableSize; i++) {
            RMAN_TABLE[i] = NULL;
            RMAN_FREE_ENTRIES[i] = 0;
        }

        resTable.tableIndex = 0;
        resTable.freeIndex = -1;

        /* First pre-register the NULL resource */
        nullParams.allocFxn = RMAN_PARAMS.allocFxn;
        nullParams.freeFxn = RMAN_PARAMS.freeFxn;
        nullParams.size = sizeof(IRESMAN_Params);

        status = RMAN_register(&IRESMAN_NULLRES, &nullParams);
        if (status != IRES_OK) {
            Log_print1(Diags_USER7, "[+7] RMAN_init> Register failed "
                    "on NULL IRESMAN implementation: %d", (IArg)status);
            initStatus = status;
        }
    }

    if (initStatus == IRES_OK) {
        /*
         *  In this function, we can populate the RMAN_registryEntries,
         *  RMAN_registeryResmanArgs and fix RMAN_numRegistryEntries
         */
        initStatus = RMAN_autoRegister();
    }

    /*
     * Static registration of Resource Registry entries
     */
    if ((initStatus == IRES_OK) && (RMAN_registryEntries != NULL)) {

        Assert_isTrue(RMAN_numRegistryEntries < resTable.tableSize,
                (Assert_Id)NULL);
        Log_print0(Diags_USER2, "[+2] RMAN_init> Registering statically "
                "added resources");
        /*
         *  Copy the entries from the static configuration into the resource
         *  table.
         */
        for (i = 0; i < RMAN_numRegistryEntries; i++) {

            status = RMAN_register(RMAN_registryEntries[i],
                    RMAN_registryResmanArgs[i]);

            if (status != IRES_OK) {
                Log_print2(Diags_USER7, "[+7] RMAN_init> Register failed on "
                        "IRESMAN implementation 0x%x, status: %d",
                        (IArg)(RMAN_registryEntries[i]), (IArg)status);

                initStatus = status;
                break;
            }
        }
    }

    getInternalState();

    if (NULL == rmanInternalState) {
        initStatus = IRES_EFAIL;
    }

    Log_print1(Diags_EXIT, "[+X] RMAN_init> Exit (status=%d)",
            (IArg)initStatus);

    return (initStatus);
}

/*
 *  ======== RMAN_register ========
 *  Register the protocol/protocol revision and the device specific resource
 *  manager implementation with the Resource Registry of the RMAN
 */
IRES_Status RMAN_register(IRESMAN_Fxns * resmanFxns, IRESMAN_Params * initArgs)
{
    Int            index = -1;
    Int            i = 0;
    IRESMAN_Fxns * resman = NULL;
    String         protocolName = NULL;
    IRES_Status    status = IRES_OK;
    IArg           key;
    IRES_ProtocolRevision * revNo;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_register> RMAN_init call "
                "hasn't happened successfully. Please initialize RMAN "
                "before registering resources");
        Log_print0(Diags_EXIT, "[+X] RMAN_register> Exit "
                "(status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Log_print2(Diags_ENTRY, "[+E] RMAN_register> Enter (resmanFxns=0x%x, "
            "initArgs=0x%x)", (IArg)resmanFxns, (IArg)initArgs);

    Assert_isTrue(resmanFxns != NULL, (Assert_Id)NULL);

    protocolName = resmanFxns->getProtocolName();

    Assert_isTrue(protocolName != NULL, (Assert_Id)NULL);

    revNo = resmanFxns->getProtocolRevision();

    Log_print4(Diags_USER4, "[+4] RMAN_register> Registering protocol %s "
            "revision (%d.%d.%d)",
            (IArg)protocolName, (IArg)(revNo->Major), (IArg)(revNo->Source),
            (IArg)(revNo->Radius));

    /*
     * Use the protocolName and revisionNo to log the Resman Implementation
     * in the ResourceRegistry table.
     */

    key = IGateProvider_enter(gate);

    /*
     * First check the entire table to see if there are any duplicates
     */
    for (i = 0; i < resTable.tableIndex; i++) {

        if ((resman = RMAN_TABLE[i]) &&
                !strcmp(protocolName, RMAN_TABLE[i]->getProtocolName()) &&
                checkResMgrAlgRevision(RMAN_TABLE[i]->getProtocolRevision(),
                revNo)) {

            /* Found a match */
            if (resmanFxns == RMAN_TABLE[i]) {
                /* Re-registering the same protocol, do nothing. */
                IGateProvider_leave(gate, key);

                Log_print0(Diags_EXIT, "[+X] RMAN_register> "
                        "Exit (status=IRES_EEXISTS)");

                return (IRES_EEXISTS);
            }

            /*
             * Re-registering a different protocol for an existing entry.
             * Replace current entry with new entry
             */
            index = i;

            if ((status = resman->exit()) != IRES_OK) {
                IGateProvider_leave(gate, key);

                Log_print2(Diags_USER7, "[+7] RMAN_register> Exit failed on"
                        "IRESMAN implementation 0x%x, status: %d",
                        (IArg)resman, (IArg)status);
                Log_print0(Diags_EXIT, "[+X] RMAN_register> Exit "
                        "(status=IRES_EFAIL)");

                return (IRES_EFAIL);
            }
            break;
        }
    }

    /* Registering a new protocol */
    if ((status = resmanFxns->init(initArgs)) != IRES_OK) {
        IGateProvider_leave(gate, key);

        Log_print2(Diags_USER7, "[+7] RMAN_register> Init failed on "
                "IRESMAN implementation 0x%x, status: %d",
                (IArg)resman, (IArg)status);
        Log_print0(Diags_EXIT, "[+X] RMAN_register> Exit "
                "(status=IRES_ENORESOURCE)");

        return (IRES_ENORESOURCE);
    }

    if (index == -1) {
        /* Not found in table. Check for available entry in freeIndex table */
        if (-1 != resTable.freeIndex) {
            index = RMAN_FREE_ENTRIES[resTable.freeIndex];
            resTable.freeIndex--;
        }
        else {
            /* No free entries available, use new one in the registry table */

            /* Should never exceed pre configured table size */
            Assert_isTrue(index < resTable.tableSize, (Assert_Id)NULL);

            index = resTable.tableIndex;
            resTable.tableIndex++;
        }
    }

    /* Add the actual entry to the Resource table */
    RMAN_TABLE[index] = resmanFxns;

    IGateProvider_leave(gate, key);

    Log_print0(Diags_EXIT, "[+X] RMAN_register> Exit (status=IRES_OK)");

    return (IRES_OK);
}

/*
 *  ======== RMAN_unregister ========
 *  Unregister the protocol and the corresponding resource manager
 *  implementation from the Resource Registry
 */
IRES_Status RMAN_unregister(IRESMAN_Fxns * resmanFxns)
{
    Int     i = 0;
    String  protocolName = NULL;
    IArg    key;
    IRES_ProtocolRevision * revNo;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_unregister> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling other RMAN APIs");

        Log_print0(Diags_EXIT, "[+X] RMAN_unregister> "
                "Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

    Log_print1(Diags_ENTRY, "[+E] RMAN_unregister> Enter (resmanFxns=0x%x)",
            (IArg)resmanFxns);

    protocolName = resmanFxns->getProtocolName();
    revNo = resmanFxns->getProtocolRevision();

    Assert_isTrue(protocolName != NULL, (Assert_Id)NULL);

    key = IGateProvider_enter(gate);

    /*
     * Search the table matching the protocolName and revision Number
     * with the entries
     */
    for (i = 0; i < resTable.tableIndex; i++) {

        /* Check for NULL before checking for protocol and revision */
        if ((RMAN_TABLE[i]) &&
                checkResMgrAlgRevision(RMAN_TABLE[i]->getProtocolRevision(),
                revNo) &&
                !strncmp(protocolName, RMAN_TABLE[i]->getProtocolName(),
                        RMAN_PROTOCOLNAMESIZE)) {
            /* Found a match */
            break;
        }
    }

    if (i == resTable.tableIndex) {
        /* Entry not found */
        IGateProvider_leave(gate, key);

        Log_print0(Diags_USER7, "[+7] RMAN_unregister> Entry not found "
                "in table of registered IRESMAN implementations");

        Log_print0(Diags_EXIT, "[+X] RMAN_unregister> Exit "
                "(status=IRES_ENOTFOUND)");

        return (IRES_ENOTFOUND);
    }

    /*
     *  Call the exit interface of the specific IResman implementation and
     *  delete that entry from the table
     */
    if (IRES_OK != (RMAN_TABLE[i])->exit()) {
        IGateProvider_leave(gate, key);

        Log_print1(Diags_USER7, "[+7] RMAN_unregister> Exit "
                "failed on IRESMAN implementation 0x%x", (IArg)(RMAN_TABLE[i]));

        Log_print0(Diags_EXIT, "[+X] RMAN_unregister> Exit (status=IRES_EFAIL)");

        return (IRES_EFAIL);
    }

    /* Reset this entry in the entries table */
    RMAN_TABLE[i] = NULL;

    /* Since this table index is now available, add it to the freeTable */
    resTable.freeIndex++;

    /* Should never run out of space in free Table */
    Assert_isTrue(resTable.freeIndex < resTable.tableSize, (Assert_Id)NULL);

    RMAN_FREE_ENTRIES[resTable.freeIndex] = i;

    IGateProvider_leave(gate, key);

    Log_print0(Diags_EXIT, "[+X] RMAN_unregister> Exit (status=IRES_OK)");

    return (IRES_OK);
}

/*
 *  ======== RMAN_activateResource ========
 *  Activate resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_activateResource(IALG_Handle alg,
        IRES_Handle resourceHandle, IRES_Fxns * resFxns, Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_activateResource> RMAN_init "
                "call hasn't happened successfully. Please initialize "
                "RMAN before calling any other RMAN API");
        Log_print0(Diags_EXIT, "[+X] RMAN_activateResource> Exit "
                "(status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Log_print4(Diags_ENTRY, "[+E] RMAN_activateResource> Enter "
            "(alg=0x%x, resourceHandle=0x%x, resFxns=0x%x, scratchGroupId=%d",
            (IArg)alg, (IArg)resourceHandle, (IArg)resFxns,
            (IArg)scratchGroupId);

    status = resFxns->activateResource(alg, resourceHandle);

    Log_print1(Diags_EXIT, "[+X] RMAN_activateResource> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 * ======== RMAN_activateAllResource ========
 * Activate all resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_activateAllResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_activateAllResources>"
                " RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_activateAllResources> "
                "Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

    Log_print3(Diags_ENTRY, "[+E] RMAN_activateAllResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)",
            (IArg)alg, (IArg)resFxns, (IArg)scratchGroupId);

    status = resFxns->activateAllResources(alg);

    Log_print1(Diags_EXIT, "[+X] RMAN_activateAllResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 * ======== RMAN_deactivateResource ========
 * Deactivate the resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_deactivateResource(IALG_Handle alg,
        IRES_Handle resourceHandle, IRES_Fxns * resFxns, Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_deactivateResource>"
                " RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_deactivateResource> "
                "Exit (status=IRES_ENOINIT)");
        return (IRES_ENOINIT);
    }

    Log_print4(Diags_ENTRY, "[+E] RMAN_deactivateResource> "
            "Enter (alg=0x%x, resourceHandle=0x%x, resFxns=0x%x, "
            "scratchGroupId=%d)",
            (IArg)alg, (IArg)resourceHandle, (IArg)resFxns,
            (IArg)scratchGroupId);

    status =  resFxns->deactivateResource(alg, resourceHandle);

    Log_print1(Diags_EXIT, "[+X] RMAN_deactivateResource> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== RMAN_deactivateAllResources ========
 *  Deactivate the resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_deactivateAllResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_deactivateAllResources> "
                "RMAN_init call hasn't happened successfully. Please "
                "initialize RMAN before calling any other RMAN API");

        Log_print0(Diags_EXIT, "[+X] RMAN_deactivateAllResources> "
                "Exit (status=IRES_ENOINIT)");

        return (IRES_ENOINIT);
    }

    Log_print3(Diags_ENTRY, "[+E] RMAN_deactivateAllResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)",
            (IArg)alg, (IArg)resFxns, (IArg)scratchGroupId);

    status = resFxns->deactivateAllResources(alg);

    Log_print1(Diags_EXIT, "[+X] RMAN_deactivateAllResources> Exit (status=%d)",
            (IArg)status);

    return (status);
}

Int  RMAN_getNumResources(IALG_Handle alg, IRES_Fxns * resFxns)
{
    return (resFxns->numResourceDescriptors)(alg);
}

Int  RMAN_getResman(IALG_Handle alg,
                IRES_Fxns * resFxns, IRESMAN_Fxns ** resmanList)
{
    IRES_Status     status = IRES_OK;
    Int             numResources = 0;
    Int             n = 0;
    size_t          resDescSize;
    IRES_ResourceDescriptor * resDesc = NULL;
    IRES_Status      algStatus = IRES_OK;
    Int             numResman = 0;

    if (initStatus != IRES_OK) {
        Log_print0(Diags_USER7, "[+7] RMAN_getResman> RMAN_init "
                "call hasn't happened successfully. Please initialize "
                "RMAN before calling any other RMAN API");
        Log_print0(Diags_EXIT, "[+X] RMAN_getResman> Exit "
                "(status=IRES_ENOINIT)");
/*          return (IRES_ENOINIT);*/
    }

    Log_print3(Diags_ENTRY, "[+E] RMAN_getResman> Enter "
            "(alg=0x%x, resFxns=0x%x, resmanList=0x%x)",  (IArg)alg,
            (IArg)resFxns, (IArg)resmanList);

/* 1. Obtain iresman fxns */
    /*
     *  Get resource requirements of the algorithm
     */
    numResources = (resFxns->numResourceDescriptors)(alg);
    resDescSize = numResources * sizeof(IRES_ResourceDescriptor);

    /* Allocate memory to hold algorithm's resource descriptors */
    if ((resDesc = myAlloc(resDescSize, 0)) == NULL) {
        Log_print1(Diags_USER7, "[+7] RMAN_getResman> "
                "Could not allocate memory size 0x%x in space "
                "IALG_EXTERNAL of type IALG_PERSIST", (IArg)resDescSize);

        Log_print0(Diags_EXIT, "[+X] RMAN_getResman> "
                "Exit (status=IRES_ENOMEM)");

/*          return (IRES_ENOMEM);*/
    }

    algStatus = resFxns->getResourceDescriptors(alg, resDesc);

    if (algStatus != IRES_OK) {
        Log_print3(Diags_USER7, "[+7] RMAN_getResman> Error obtaining "
                "Resource Descriptors [status: %d] from alg 0x%x, "
                "IRES interface 0x%x",
                (IArg)algStatus, (IArg)alg, (IArg)resDesc);

        status = IRES_EALG;
    }

    if (status == IRES_OK) {
        /* For each requested resource */
        for (n = 0 ; n < numResources; n++) {
            /* If someone populated the resource descriptor improperly, bail */
            if ((resDesc[n].resourceName == NULL) ||
                    (resDesc[n].revision == NULL)) {

                Log_print0(Diags_USER7, "[+7] RMAN_getResman> "
                        "Resource protocol and/or version were NULL. "
                        "Most likely an issue  with the algorithm's "
                        "getResourceRequestDescriptor implementation.");

                status = IRES_EALG;
                break;
            }

            /* need to fetch resman for the righ resource ?! */
            resmanList[numResman] = getResman(resDesc[n].resourceName,
                    resDesc[n].revision);
            numResman++;
        }

    }

    myFree(resDesc, resDescSize);

#if 0
/* 2. check if activate resource exists */

        if (resman->activateResource != NULL) {
/* 3. if it does, call it */
                        resman->activateResource(alg, resourceHandle,
                                        resDesc, scratchGroupId);
                }
        }

    Log_print1(Diags_EXIT, "[+X] RMAN_getResman> Exit (status=%d)",
            (IArg)status);
#endif

    return (numResman);
}
/*
 *  ======== checkResMgrAlgRevision ========
 *  Checks of the versions of the protocols are compatible
 */
static Bool checkResMgrAlgRevision(IRES_ProtocolRevision *resMgrVer,
        IRES_ProtocolRevision *algVer2)
{
    /* Check if resource mgr Major is >= alg's Major, if so, we support it */
    /* No longer compares versions, returns TRUE always*/
    return (TRUE);
}

/*
 *  ======== getResman ========
 *  Searches through valid entries of RMAN_TABLE to find a RESMAN corresponding
 *  to the name and revision of the protocol.
 */
static IRESMAN_Fxns * getResman(String name, IRES_ProtocolRevision * rev)
{
    IRESMAN_Fxns  *fxns = NULL;
    Int     j;
    IArg    key;

    key = IGateProvider_enter(gate);

    /*
     *  For each non-NULL RMAN_TABLE entry, compare protocolName and version
     *  number.
     */
    for (j = 0; j < resTable.tableIndex; j++) {
        if ((RMAN_TABLE[j]) &&
                !strcmp(name, RMAN_TABLE[j]->getProtocolName()) &&
                checkResMgrAlgRevision(RMAN_TABLE[j]->getProtocolRevision(), rev)) {

            /* Found a match */
            fxns = RMAN_TABLE[j];
            break;
        }
    }

    IGateProvider_leave(gate, key);

    return (fxns);
}

/*
 *  ======== myAlloc ========
 *  Wrapper around RMAN_PARAMS.allocFxn.
 */
static Void *myAlloc(size_t size, size_t align)
{
    IALG_MemRec memTab;
    Void       *addr = NULL;

    memTab.size = size;
    memTab.alignment = align;
    memTab.space = IALG_EXTERNAL;
    memTab.attrs = IALG_PERSIST;

    if (RMAN_PARAMS.allocFxn(&memTab, 1)) {
        addr = memTab.base;
    }

    /* Make sure memory was allocated in the space we asked for */
    Assert_isTrue((IALG_EXTERNAL == memTab.space), (Assert_Id)NULL);

    return (addr);
}

/*
 *  ======== myFree ========
 *  Wrapper around RMAN_PARAMS.freeFxn.
 */
static Void myFree(Ptr addr, size_t size)
{
    IALG_MemRec memTab;

    memTab.base = addr;
    memTab.size = size;
    memTab.alignment = 0;         /* Alignment shouldn't be needed here */
    memTab.space = IALG_EXTERNAL;
    memTab.attrs = IALG_PERSIST;

    RMAN_PARAMS.freeFxn(&memTab, 1);
}


/*
 *  ======= setInternalState =======
 */
static Void setInternalState(Void * addr)
{
    RMAN_InternalState * intState =
            (RMAN_InternalState *)addr;
    int i;

    RMAN_VtableEntry * ptr = algresVTable;

    if (NULL != intState) {
        intState->info.maxEntries = ti_sdo_fc_rman_RMAN_MAXALGS;
        intState->info.index = -1;
        intState->info.refCount = 0;
        intState->info.vTableOffset = sizeof(RMAN_InternalStateInfo);

#ifdef xdc_target__os_Linux
        ptr = (RMAN_VtableEntry *)((unsigned int)intState +
            (unsigned int) (intState->info.vTableOffset));
#endif

        for (i = 0; i < ti_sdo_fc_rman_RMAN_MAXALGS; i++) {
            ptr[i].algVtable = NULL;
            ptr[i].resVtable = NULL;
            ptr[i].refs      = 0;
        }
    }
}


static void getInternalState()
{

    Int sharedMemId = -1;
#ifdef xdc_target__os_Linux

    rmanInternalState = (RMAN_InternalState *)SHM_getObj(gate,
            sizeof(RMAN_InternalState) + (ti_sdo_fc_rman_RMAN_MAXALGS *
            sizeof(RMAN_VtableEntry)), (key_t)_RMAN_LOCKID,
            &setInternalState, &sharedMemId);

    algresVTable = (RMAN_VtableEntry *)((unsigned int)rmanInternalState +
            (unsigned int) (rmanInternalState->info.vTableOffset));
#else
    static RMAN_InternalState _RMAN_internalState;
    rmanInternalState = (RMAN_InternalState *)
            &_RMAN_internalState;
    algresVTable = (RMAN_VtableEntry *)(myAlloc(ti_sdo_fc_rman_RMAN_MAXALGS *
            sizeof(RMAN_VtableEntry), 0));
    setInternalState(rmanInternalState);
    sharedMemId = 0;
#endif
    rmanInternalState->info.sharedMemId = sharedMemId;
    rmanInternalState->info.refCount++;
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState()
{
    if (rmanInternalState->info.numOpens == 0) {
    }
#ifdef xdc_target__os_Linux
    SHM_freeObj(rmanInternalState, rmanInternalState->info.sharedMemId);
#else
    if (algresVTable) {
        myFree(algresVTable, ti_sdo_fc_rman_RMAN_MAXALGS * sizeof(RMAN_VtableEntry));
        algresVTable = NULL;
    }

    rmanInternalState = NULL;
#endif

}

/*
 *  ========  addVTableEntry ========
 */
Bool addVTableEntry(IALG_Handle alg, IRES_Fxns * res)
{
    Bool found = FALSE;
    RMAN_VtableEntry *ptr = algresVTable;
    int count = rmanInternalState->info.index;
    unsigned int * algHandle = (unsigned int *)alg;
    unsigned int * resFxns = (unsigned int *)res;
    Int index = count;
    int i = 0;

    /* If there are active duplicates, complain */
    for (i = 0; i <= count; i++) {
        if (ptr[i].refs == 0) {
            index = i;
            found = TRUE;
        }
        if ((algHandle == ptr[i].algVtable) && (resFxns == ptr[i].resVtable)
                && (ptr[i].refs > 0)) {
            index = i;
            found = TRUE;
            break;
        }
    }
    if (!found) index = ++count;

    if (count >= ti_sdo_fc_rman_RMAN_MAXALGS) {
        return (FALSE);
    }

    if (ptr[index].refs == 0) {
        ptr[index].algVtable = algHandle;
        ptr[index].resVtable = resFxns;
    }
    ptr[index].refs++;

    if (count > rmanInternalState->info.index) {
        rmanInternalState->info.index = count;
    }

    return (TRUE);
}

/*
 *  ========  freeVTableEntry ========
 */
Bool freeVTableEntry(IALG_Handle alg, IRES_Fxns * res)
{
    Bool found = FALSE;
    RMAN_VtableEntry *ptr = algresVTable;
    int count = rmanInternalState->info.index;
    unsigned int * algHandle = (unsigned int *)alg;
    unsigned int * resFxns = (unsigned int *)res;
    Int index = -1;
    Int i = 0;

    /* If there are active duplicates, complain */
    for (i = 0; i <= count; i++) {
        if ((algHandle == ptr[i].algVtable) && (resFxns == ptr[i].resVtable) &&
                (ptr[i].refs > 0)) {
            index = i;
            found = TRUE;
            break;
        }
    }
    if (found) {
        ptr[index].refs--;
        if (ptr[index].refs == 0) {
            ptr[index].algVtable= NULL;
            ptr[index].resVtable = NULL;

            if (index == count) {
                /* We are removing the last entry in the table, can decrease the
                   size of table */
                rmanInternalState->info.index--;
            }
        }
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}


#ifndef xdc_target__os_Linux
IRES_Fxns * RMAN_getIresEntry(IALG_Handle alg)
{
    Bool found = FALSE;
    RMAN_VtableEntry *ptr = algresVTable;
    int count = rmanInternalState->info.index;
    unsigned int * algHandle = (unsigned int *)alg;
    unsigned int * res = NULL;
    Int index = -1;
    Int i = 0;

    /* If there are active duplicates, complain */
    for (i = 0; i <= count; i++) {
        if ((algHandle == ptr[i].algVtable) && (ptr[i].refs > 0)) {
            index = i;
            found = TRUE;
            break;
        }
    }

    if (found) {
        res = ptr[index].resVtable;
        /* Could even be NULL */
        return ((IRES_Fxns * )res);

    }
    else {
        return (NULL);
    }
}

IALG_Fxns * RMAN_getIAlgEntry(IRES_Fxns * res)
{
    Bool found = FALSE;
    RMAN_VtableEntry *ptr = algresVTable;
    int count = rmanInternalState->info.index;
    unsigned int * resFxns = (unsigned int *)res;
    IALG_Handle alg = NULL;
    Int index = -1;
    Int i = 0;

    /* If there are active duplicates, complain */
    for (i = 0; i <= count; i++) {
        if ((resFxns == ptr[i].resVtable) && (ptr[i].refs > 0)) {
            index = i;
            found = TRUE;
            break;
        }
    }

    if (found) {
        alg = (IALG_Handle)(ptr[index].algVtable);
/*
#ifdef xdc_target__os_Linux
        alg = mmap(0, sizeof(IRES_Fxns), PROT_READ|PROT_WRITE, MAP_SHARED,
                RMAN_memfd, (off_t)alg);
#endif
*/
        /* This could be NULL */
        return ((IALG_Fxns *)alg->fxns);

    }
    else {
        return (NULL);
    }
}
#endif
