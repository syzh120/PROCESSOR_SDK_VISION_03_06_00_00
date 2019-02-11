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
 *  ======== edma3_config.c ========
 *  APIs to configure the EDMA3 resources for various scratch groups and obtain
 *  handles to the same
 *  Specifically for the use of IRES EDMA3CHAN protocol and DMAN3 when it uses
 *  a common Resource Manager layer
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_edma3_desc


#define DMAQNUM_OFFSET  0x240
#define QUETCMAP_OFFSET 0x280
#define QUEPRI_OFFSET   0x284

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include <ti/xdais/ialg.h>
#include <ti/sdo/edma3/rm/edma3_common.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>

#include "edma3_config.h"

extern __FAR__ EDMA3_GblConfigParams * ti_sdo_fc_edma3_Settings_globalConfig;
extern __FAR__ EDMA3_InstanceInitConfig * ti_sdo_fc_edma3_Settings_regionConfig;
/* TODO: Fix the SEMKEY function */
/*
 *  Macro to create a Key from a seed value passed to it
 */
#define EDMA3_SEMKEY(seed) (seed)
#define EDMA3_MIN(a,b,c) ((a) <= (b) ? ((a) <= (c) ? (a) : (c)) \
        : ((b) <= (c) ? (b) : (c)))


/*
 *  ======== EDMA3_ScratchTableEntry ========
 * Structure to store resource Manager associated with each algorithm
 */
typedef struct EDMA3_ScratchTableEntry {
    IALG_Handle alg;                        /* Algorithm handle */
    EDMA3_RM_Handle resourceManager;        /* Resource Manager handle */
    Void * sem;                             /* Semaphore being used by the
                                               Resource Manager */
    Int refCount;                           /* Counts the number of times the
                                               handle is requested */
    struct EDMA3_ScratchTableEntry * next;  /* Pointer to the next entry */
} EDMA3_ScratchTableEntry;

/*
 *  ======== EDMA3_Table ========
 *  Structure to store the Scratch Table Entries per scratch group
 */
typedef struct EDMA3_Table {
    EDMA3_ScratchTableEntry * entry;
    Bool populated;
} EDMA3_Table;

static __FAR__ EDMA3_Table _table[EDMA3_MAXGROUPS];
                                                /* Table to hold the algHandle
                                                   and Resource Manager handle
                                                   info per scratch group */

static __FAR__ Int _initialized = 0;            /* Initialization flag */

static __FAR__ Int _rmObjCreated = 0;

static __FAR__ EDMA3_RM_Handle _systemResourceManagerHandle = NULL;
                                                /* Handle to the system-wide
                                                   Resource Manager */
static __FAR__ Void * _systemResourceManagerSem = NULL;
                                                /* Semaphore to keep track of
                                                   System resource allocations*/

static __FAR__ Int _sysResourceManagerRefCount = 0;
                                                /* Reference count for system
                                                   wide resource manager
                                                   handles requested */

static __FAR__ EDMA3_RM_InstanceInitConfig _regionConfig;
                                                /* Stores the region specific
                                                   configuration for the
                                                   Resource Manager handle */

/*
 * Initialize the EDMA3 Meta config module, create the Resource Manager object
 */
static Int edma3Init();
/*
 * Exits the EDMA3 Meta config module, deletes the Resource Manager object
 */
static Int edma3Exit();

/*
 * Function to release an RM handle for a scratch group
 */
static EDMA3_RM_Result closeRMHandle(EDMA3_RM_Handle handle);

/*
 * Function to return an RM handle for a scratch group
 */
static EDMA3_RM_Handle openRMHandle(Int scratchId, Void * sem);

/*
 * Populates the scratch groups with respective EDMA resources
 */
static Int populateScratchGroup(Int scratchGroupId);

static Int unpopulateScratchGroup(Int scratchGroupId);

__FAR__ Registry_Desc ti_sdo_fc_edma3_desc;

extern __FAR__ Bool ti_sdo_fc_edma3_Settings_eventQueueSetup;

extern __FAR__ Int ti_sdo_fc_edma3_Settings_queueTCMap[];

extern __FAR__ Int ti_sdo_fc_edma3_Settings_queuePriority[];

extern __FAR__ Int ti_sdo_fc_edma3_Settings_memTypeTCMap[8];

/*
 *  ======== EDMA3_exit ========
 */
EDMA3_Result EDMA3_exit()
{
        EDMA3_Result status = EDMA3_SOK;

     if (0 == _sysResourceManagerRefCount) {

         /* Delete the RM handle */
         if (EDMA3_RM_SOK != closeRMHandle(_systemResourceManagerHandle)) {

             Log_print1(Diags_USER7,
                     "[+7] EDMA3_exit> Error deleting"
                     " RM handle 0x%x", (IArg)_systemResourceManagerHandle);

            status = EDMA3_E_RES_ALREADY_FREE;
        }

        /* Delete the Semaphore */
        EDMA3_semDelete(_systemResourceManagerSem);

                _systemResourceManagerHandle = NULL;
        _systemResourceManagerSem = NULL;

        if (!edma3Exit()) {
                Log_print0(Diags_USER7, "[+7] EDMA3_exit> "
                        "Error deleting RM Object");

                status =  EDMA3_E_RES_ALREADY_FREE;
        }

        _initialized = 0;

    }

    return (status);
}

/*
 *  ======== EDMA3_getDestTypeQueueMap ========
 *  Function to obtain the mapping of different dma destination types to
 *  Event Queues as configured.
 */
Void EDMA3_getDestTypeQueueMap(XDAS_Int32 * table)
{
    int i = 0;
    for (i = 0; i < 8; i++) {
        table[i] = ti_sdo_fc_edma3_Settings_memTypeTCMap[i];
    }
}

/*
 *  ======== EDMA3_getResourceManager ========
 *  Function to obtain the resource manager handle corresponding to this
 *  algorithm in this scratch group
 */
EDMA3_Handle EDMA3_getResourceManager(IALG_Handle algHandle,
        Int scratchGroupId)
{
    EDMA3_RM_Handle           handle = NULL;
    EDMA3_ScratchTableEntry * entry = NULL;
    EDMA3_ScratchTableEntry * pEntry = NULL;
    IALG_MemRec               memTab;
    Void                    * sem;

    Log_print2(Diags_ENTRY,
            "[+E] EDMA3_getResourceManager> Enter (alg=0x%x, "
            "scratchGroupId =%d)", (IArg)algHandle, (IArg)scratchGroupId);

    if (-1 == scratchGroupId) {

        Log_print0(Diags_USER2,
                "[+2] EDMA3_getResourceManager> Return system Resource "
                "Manager handle");

        Log_print1(Diags_EXIT,
                "[+X] EDMA3_getResourceManager> Exit (handle=0x%x)",
                (IArg)_systemResourceManagerHandle);

        _sysResourceManagerRefCount++;

        return ((EDMA3_Handle)_systemResourceManagerHandle);
    }

    Log_print1(Diags_USER2, "[+2] EDMA3_getResourceManager> "
            "Look for matching entry for ALG 0x%x", (IArg)algHandle);

    /* Search for entry */
    entry = _table[scratchGroupId].entry;
    pEntry = NULL;

    while (entry != NULL) {

        if (algHandle == entry->alg) {

                        entry->refCount++;

            Log_print1(Diags_EXIT,
                    "[+X] EDMA3_getResourceManager> Exit (handle=0x%x)",
                    (IArg)(entry->resourceManager));

            return ((EDMA3_Handle)(entry->resourceManager));
        }

        /* No matching entry was found, try next */
        pEntry = entry;
        entry = entry->next;
    }

    Log_print0(Diags_USER2, "[+2] EDMA3_getResourceManager> Match not found, "
            "create new entry, get resource handle");

    memTab.size = sizeof(EDMA3_ScratchTableEntry);
    memTab.alignment = sizeof(int);
    memTab.space = IALG_ESDATA;
    memTab.attrs = IALG_PERSIST;

    if (FALSE == EDMA3_PARAMS.allocFxn(&memTab, 1)) {

        Log_print0(Diags_USER2,
                "[+2] EDMA3_getResourceManager> Could not allocate memory to "
                "add alg entry.");

        Log_print0(Diags_EXIT,
                "[+X] EDMA3_getResourceManager> Exit (handle=NULL)");

        return (NULL);
    }

    sem = (Void *)EDMA3_semCreate((Int)(EDMA3_SEMKEY(memTab.base)), 1);

    /*
     *  This semaphore is created per algorithm per scratch group. The algorithm
     *  owns a copy of the handle, there won't be contention for resources
     *  protected by this semaphore.
     */
    if (NULL == sem) {

        Log_print0(Diags_USER7,
                "[+7] EDMA3_getResourceManager> Error creating semaphore."
                " Free memory and exit");

        /* Free memory */
        EDMA3_PARAMS.freeFxn(&memTab, 1);

        Log_print0(Diags_EXIT,
                "[+X] EDMA3_getResourceManager> Exit (handle=NULL)");

        return (NULL);
    }

    Log_print0(Diags_USER2,
            "[+2] EDMA3_getResourceManager> Opening new Resource Manager Handle");

    handle = openRMHandle(scratchGroupId, sem);

    if (NULL == handle) {

        Log_print0(Diags_USER7,
                "[+7] EDMA3_getResourceManager> Error opening Resource "
                " Manager handle. Delete semaphore and free memory");

        /* Delete sem */
        EDMA3_semDelete(sem);

        /* Free memory */
        EDMA3_PARAMS.freeFxn(&memTab, 1);

        Log_print0(Diags_EXIT,
                "[+X] EDMA3_getResourceManager> Exit (handle=NULL)");

        return (NULL);
    }

    Log_print0(Diags_USER2,
            "[+2] EDMA3_getResourceManager> Populate new Table entry");

    entry = (EDMA3_ScratchTableEntry *)memTab.base;
    entry->alg = algHandle;
    entry->resourceManager = handle;
    entry->sem = sem;
    entry->refCount = 1;
    entry->next = NULL;

    if (NULL != pEntry) {
        pEntry->next = entry;
    }
        else {
                _table[scratchGroupId].entry = entry;
        }

    Log_print1(Diags_EXIT, "[+X] EDMA3_getResourceManager> Exit (handle=0x%x)",
            (IArg)(entry->resourceManager));

    return ((EDMA3_Handle)(handle));
}

/*
 *  ======== EDMA3_init ========
 */
EDMA3_Result EDMA3_init()
{
    Registry_Result result;
    __FAR__ static Int _EDMA3_refCount  = 0;


    if (_EDMA3_refCount++ == 0) {
        /* Register this module for logging */
        result = Registry_addModule(&ti_sdo_fc_edma3_desc, EDMA3_MODNAME);
        Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

        if (result == Registry_SUCCESS) {
            /* Set the diags mask to the FC default */
            FCSettings_init();
            FCSettings_setDiags(EDMA3_MODNAME);
        }
    }

    if (0 == _initialized) {
        Log_print0(Diags_ENTRY,
                "[+E] EDMA3_init> Enter ");

        Log_print0(Diags_USER2, "[+2] EDMA3_init>"
                " Initializing EDMA3 Meta config module");

        if (1 != edma3Init()) {
            Log_print0(Diags_USER7,
                    "[+7] EDMA3_init> Error Intializaing EDMA3 "
                    "Meta config module ");

            Log_print0(Diags_EXIT, "[+X] EDMA3_init> Exit "
                    "(status=EDMA3_E_OBJ_NOT_DELETED");

            return (EDMA3_E_OBJ_NOT_DELETED);
        }

        Assert_isTrue(_sysResourceManagerRefCount == 0, (Assert_Id)NULL);
        Assert_isTrue(_systemResourceManagerHandle == NULL, (Assert_Id)NULL);
        Log_print0(Diags_USER2, "[+2] EDMA3_init>"
                " Creating semaphore for System Resource Manager Handle");

        _systemResourceManagerSem = (Void *)EDMA3_semCreate
                (EDMA3_SEMKEY((Int)&_systemResourceManagerHandle), 1);

        /*
         *  The system semaphore needs to be unique, and different for a handle
         *  opened on any other region on this hardware.
         */
        if (NULL == _systemResourceManagerSem) {

            Log_print0(Diags_USER7,
                    "[+7] EDMA3_init> Error creating Semaphore");

            if (1 != edma3Exit()) {

                Log_print0(Diags_USER7,
                        "[+7] EDMA3_init> Error exiting EDMA3 Meta "
                        "config module");
            }

            Log_print0(Diags_EXIT,
                    "[+X] EDMA3_init> Exit (status=EDMA3_E_SEMAPHORE)");

            return (EDMA3_E_SEMAPHORE);
        }

        Log_print0(Diags_USER2, "[+2] EDMA3_init>"
                " Opening System Resource Manager Handle");

        _systemResourceManagerHandle = openRMHandle(-1,
                _systemResourceManagerSem);

        if (NULL == _systemResourceManagerHandle ) {

            Log_print0(Diags_USER7,
                    "[+7] EDMA3_init> Error opening System Resource "
                    "Manager Handle");

            /* Delete the Semaphore */
            EDMA3_semDelete(_systemResourceManagerSem);

                _systemResourceManagerSem = NULL;

            if (1 != edma3Exit()) {
                Log_print0(Diags_USER7,
                        "[+7] EDMA3_init> Error exiting EDMA3 Meta "
                        "config module");
            }

            Log_print0(Diags_EXIT,
                    "[+X] EDMA3_init> Exit (status=EDMA3_E_RES_NOT_ALLOCATED)");

            return (EDMA3_E_RES_NOT_ALLOCATED);
        }

        _initialized = 1;

    }

    return (EDMA3_SOK);
}

/*
 *  ======== EDMA3_releaseResourceManager ========
 *  Function to release the Resource manager corresponding to this
 *  algorithm and this scratch group
 */
EDMA3_Result EDMA3_releaseResourceManager(IALG_Handle algHandle,
        Int scratchGroupId)
{
    IALG_MemRec memTab;
    EDMA3_RM_Handle handle = NULL;
    EDMA3_ScratchTableEntry * entry, * pEntry;
    EDMA3_Result status = EDMA3_SOK;

    Log_print2(Diags_ENTRY, "[+E] EDMA3_releaseResourceManager> Enter "
            "(alg=0x%x, scratchGroupId=%d)", (IArg)algHandle,
            (IArg)scratchGroupId);

    if (-1 == scratchGroupId) {
        _sysResourceManagerRefCount--;


        Log_print1(Diags_EXIT,
                "[+X] EDMA3_releaseResourceManager> Exit (status=0x%x)",
                (IArg)status);

        return (status);
    }

    /* Search for entry */
    entry = _table[scratchGroupId].entry;
    pEntry = NULL;

    while (entry != NULL) {

        if (algHandle == entry->alg) {
            handle = entry->resourceManager;
            break;
        }

        /* No matching entry was found, try next */
        pEntry = entry;
        entry = entry->next;
    }

    if (NULL == entry) {

/* TODO: Figure out if there is a better error for this */
        Log_print2(Diags_USER7,
                "[+7] EDMA3_releaseResourceManager> Could not find "
                "Resource Manager handle corresponding to algHandle 0x%x "
                "in scratch group %d", (IArg)algHandle, (IArg)scratchGroupId);

        Log_print1(Diags_EXIT,
                "[+X] EDMA3_releaseResourceManager> Exit (status=0x%x)",
                (IArg)status);

        return (EDMA3_E_RES_ALREADY_FREE);
    }

    entry->refCount--;

    Log_print3(Diags_USER2,
            "[+2] EDMA3_releaseResourceManager> (alg=0x%x, scratchGroupId=%d) "
            "entry->refCount=%d",
            (IArg)algHandle, (IArg)scratchGroupId, (IArg)(entry->refCount));

    if (entry->refCount <= 0) {

        Log_print2(Diags_USER2,
                "[+2] EDMA3_releaseResourceManager> Closing RM Handle (alg=0x%x, "
                "scratchGroupId=%d)", (IArg)algHandle, (IArg)scratchGroupId);

        /* Close the RM handle */
        if(EDMA3_RM_SOK != closeRMHandle(handle)) {

            Log_print1(Diags_USER7,
                    "[+7] EDMA3_releaseResourceManager> Error deleting"
                    " RM handle 0x%x", (IArg)handle);
        }

        /* Delete the Semaphore */
        EDMA3_semDelete(entry->sem);

        /* Fix the linked list */
        if (NULL != pEntry) {
            pEntry->next = entry->next;
        }
        else {
            _table[scratchGroupId].entry = entry->next;
        }

        /* Free the memory for this entry */
        memTab.base = entry;
        memTab.size = sizeof(EDMA3_ScratchTableEntry);
        memTab.alignment = 4;
        memTab.space = IALG_ESDATA;
                memTab.attrs = IALG_PERSIST;

        EDMA3_PARAMS.freeFxn(&memTab, 1);

        entry = NULL;
    }

/* TODO: Before closing the RM handle, can check if this is the last alg
         in the scratch group, and if so, can release the resources abck
         to the system */

    if ( NULL == _table[scratchGroupId].entry) {

        /* No more RM handles requesting this resource, release resources
           back to the system */
                if (!(unpopulateScratchGroup(scratchGroupId))) {

            Log_print0(Diags_USER7,
                    "[+7] EDMA3_releaseResourceManager> Error releasing "
                            "scratch group resources back to the system");

            status = EDMA3_E_RES_ALREADY_FREE;
        }
    }

    Log_print1(Diags_EXIT, "[+X] EDMA3_releaseResourceManager> Exit (status=%d)"
            ,(IArg)status);

    return (EDMA3_SOK);
}

/*
 *  ======== edma3Exit() ========
 *  Exits the EDMA3 Meta config module, deletes the Resource Manager object
 */
Int edma3Exit()
{
    Int i;
    Int status = 1;
    EDMA3_ScratchTableEntry * entry;

    Log_print0(Diags_ENTRY, "[+E] edma3Exit> Enter");

    Log_print0(Diags_USER2,
            "[+2] edma3Exit> Initializing table of Resource Manager handles");

    for (i = 0; i < EDMA3_MAXGROUPS; i++) {

        entry = _table[i].entry;

        while (NULL != entry ) {

            entry->alg = NULL;

            Log_print1(Diags_USER2,
                    "[+2] edma3Exit> Closing resource manager handle 0x%x",
                    (IArg)(entry->resourceManager));

            if (EDMA3_RM_SOK != closeRMHandle(entry->resourceManager)) {

                Log_print1(Diags_USER6,
                        "[+6] edma3Exit> Error closing resource manager handle "
                        "0x%x", (IArg)(entry->resourceManager));

                status = 0;
            }

            EDMA3_semDelete(entry->sem);
            entry = entry->next;
        }

        _table[i].entry = NULL;
    }

    Log_print0(Diags_USER2, "[+2] edma3Exit> Deleting resource manager object");

   /* Delete the Resource Manager object */
    if (_rmObjCreated && (EDMA3_SOK != EDMA3_deleteResourceManagerObject())) {

        Log_print0(Diags_USER6,
                "[+6] edma3Exit> Error deleting resource manager object");

        status = 0;
    }

    _rmObjCreated = 0;

    Log_print1(Diags_EXIT, "[+X] edma3Exit> Exit(status=%d)", (IArg)status);

    return (status);
}

/*
 *  ======== edma3Init() ========
 *  Initializes the EDMA3 Meta config module, creates the Resource Manager
 *  object
 */
static Int edma3Init()
{
    Int i,k;

    EDMA3_Result status = EDMA3_SOK;

    Log_print0(Diags_ENTRY, "[+E] edma3Init> Enter");

    Log_print0(Diags_USER2,
            "[+2] edma3Init> Initializing table of Resource Manager handles");

    for (i = 0; i < EDMA3_MAXGROUPS; i++) {

        _table[i].entry = NULL;
        _table[i].populated = FALSE;

        for( k =0; k < EDMA3_MAX_TCC_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownTccs[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdTccs[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_DMA_CHAN_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownDmaChannels[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdDmaChannels[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_PARAM_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownPaRAMSets[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdPaRAMSets[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_QDMA_CHAN_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownQdmaChannels[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdQdmaChannels[k] = 0x0;
        }
    }

    /* Check if EDMA3_PARAMS.global/region has to be updated because of GENERIC
       library being used */

    if ((EDMA3_PARAMS.globalConfig == NULL) &&
            (ti_sdo_fc_edma3_Settings_globalConfig)) {
        EDMA3_PARAMS.globalConfig = &ti_sdo_fc_edma3_Settings_globalConfig
                [ti_sdo_fc_edma3_EDMA3_physicalId];
    }

    if ((EDMA3_PARAMS.regionConfig == NULL) &&
            (ti_sdo_fc_edma3_Settings_regionConfig)) {
        EDMA3_PARAMS.regionConfig = ti_sdo_fc_edma3_Settings_regionConfig
                + EDMA3_MAX_REGIONS * ti_sdo_fc_edma3_EDMA3_physicalId +
                EDMA3_PARAMS.regionId;
        /*
        EDMA3_PARAMS.regionConfig = &(ti_sdo_fc_edma3_Settings_regionConfig
                [ti_sdo_fc_edma3_EDMA3_physicalId][EDMA3_PARAMS.regionId]);
        */
    }

    /* Create the Resource Manager object */
    Log_print0(Diags_USER2, "[+2] edma3Init> Create Resource Manager object");

    status = EDMA3_createResourceManagerObject();

    if (EDMA3_SOK == status) {
        _rmObjCreated = 1;
    }
    else if (EDMA3_E_OBJ_NOT_DELETED != status) {

        Log_print0(Diags_USER7, "[+7] edma3Init> Error "
                "creating Resource Manager object");

        Log_print1(Diags_USER2, "[+2] edma3Init> Exit (status=%d)", status);

        return (0);
    }

    Log_print0(Diags_EXIT, "[+X] edma3Init> Exit (status=1)");

    return (1);
}


/*
 *  ======== populateScratchGroup ========
 *  Populates the Instance information for all the scratch groups
 */
static Int populateScratchGroup(Int scratchGroupId)
{
    Int k = 0;
    Int tccs = 0;
    Int edmas = 0;
    Int qdmas = 0;
    Int params = 0;
    Int tccIndex = 0;
    Int paramIndex = 0;
    Int edmaIndex = 0;
    Int qdmaIndex = 0;
    Int tccWord = 0;
    Int paramWord = 0;
    Int edmaWord = 0;
    Int qdmaWord = 0;
    Int minMarker = 0;
    short numReqTccs = 0;
    short reqTccs[64];
    Int count = 0;
    Int regOffset = 0x0;
    unsigned int value = 0x0;

    EDMA3_RM_Result rmStatus;
    EDMA3_RM_ResDesc resObj;

    Log_print1(Diags_ENTRY,
            "[+E] poulateScratchGroups> Enter (scratchGroupId=%d)",
            (IArg)scratchGroupId);

    if (_table[scratchGroupId].populated) {

        Log_print0(Diags_USER2, "[+2] poulateScratchGroups> Exit (status=1)");

        return (1);
    }

    tccs = EDMA3_tccScratchSizes[scratchGroupId];
    edmas = EDMA3_edmaChanScratchSizes[scratchGroupId];
    qdmas = EDMA3_qdmaChanScratchSizes[scratchGroupId];
    params = EDMA3_paRamScratchSizes[scratchGroupId];

    minMarker = EDMA3_MIN(tccs, edmas, params);

    if (!( tccs + edmas + qdmas + params)) {
            goto populateEnd;
    }

    Log_print4(Diags_USER2,
            "[+2] populateScratchGroup> Allocating %d tccs %d edma %d "
            "qdma channels and %d params",
            (IArg)tccs, (IArg)edmas, (IArg)qdmas, (IArg)params);


    Log_print0(Diags_USER2,
            "[+2] populateScratchGroup> Attempting symmetric allocation of EDMA"
            " channels and Tccs");

    while (count < minMarker) {

        resObj.type = EDMA3_RM_RES_TCC;
        resObj.resId = EDMA3_RM_RES_ANY;

        rmStatus = EDMA3_RM_allocResource(_systemResourceManagerHandle,
                &resObj);

        if (EDMA3_RM_SOK != rmStatus) {
            Log_print0(Diags_USER2,
                    "[+2] populateScratchGroup> Could not allocate a TCC\n");
            break;
        }

        Log_print1(Diags_USER2,
                "[+2] populateScratchGroup> Allocated New Tcc %d",
                (IArg)(resObj.resId));

        resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

        if (EDMA3_RM_SOK == EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            tccWord = (resObj.resId)/32;
            tccIndex = resObj.resId - (32 * tccWord);

            EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[tccWord] |=
                    (0x1 << tccIndex);

            EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels
                    [tccWord] |= (0x1 << tccIndex);

            tccs--;
            edmas--;

            Log_print1(Diags_USER2,
                    "[+2] populateScratchGroup> Obtained EDMA channel %d and "
                    "corresponding Tcc", (IArg)(resObj.resId));

            if (ti_sdo_fc_edma3_Settings_eventQueueSetup) {
                regOffset = DMAQNUM_OFFSET + 0x4 * (resObj.resId >> 3);

                EDMA3_RM_getCCRegister(_systemResourceManagerHandle,
                        regOffset, &value);

                value &= (~(0xF << (0x4 * (resObj.resId & 0x7))));
                value |= (ti_sdo_fc_edma3_Settings_defaultQ << (0x4 *
                        (resObj.resId & 0x7)));

                Log_print2(Diags_USER2,
                        "[+2] populateScratchGroup> Writing 0x%x to offset 0x%x"
                        " for setting DMAQNUM", (IArg)(value),
                        (IArg)(regOffset));

                EDMA3_RM_setCCRegister(_systemResourceManagerHandle, regOffset,
                        value);
            }

            count++;
        }
        else {

            reqTccs[numReqTccs] = resObj.resId;
            numReqTccs++;

            Log_print1(Diags_USER2,
                    "[+2] populateScratchGroup> Could not allocate EDMA channel"
                    " %d", (IArg)(resObj.resId));
        }

    }

    if (numReqTccs > 0) {

        /* Free all extra Tccs requested */
        resObj.type = EDMA3_RM_RES_TCC;

        for (k = 0; k < numReqTccs; k++) {

            resObj.resId = reqTccs[k];

            Log_print1(Diags_USER2,
                    "[+2] populateScratchGroup> Free Extra Tcc %d",
                    (IArg)(resObj.resId));

            if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                    _systemResourceManagerHandle, & resObj)) {

                Log_print1(Diags_USER7,
                        "[+7] populateScratchGroup> Error freeing Tcc %d",
                        (IArg)(resObj.resId));

                /* Fatal error */
                return (0);
            }
        }
    }

    resObj.type = EDMA3_RM_RES_TCC;

    while(tccs) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            Log_print1(Diags_USER7,
                    "[+7] populateScratchGroup> Error allocating tcc %d",
                    (IArg)(resObj.resId));

            Log_print0(Diags_EXIT, "[+X] populateScratchGroup> Exit (status=0)");

            return (0);
        }

        tccWord = (resObj.resId)/32;
        tccIndex = resObj.resId - (32 * tccWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[tccWord] |=
                (0x1 << tccIndex);

        tccs--;
    }

    if (tccs) {

        Log_print1(Diags_USER7,
                "[+7] populateScratchGroup> Error allocating TCCs for scratch "
                "group %d", (IArg)scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

    while(edmas ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            Log_print1(Diags_USER7,
                    "[+7] populateScratchGroup> Error allocating edma channel %d",
                    (IArg)(resObj.resId));

            Log_print0(Diags_EXIT, "[+X] populateScratchGroup> Exit (status=0)");

            return (0);
        }

        Assert_isTrue(resObj.resId <  EDMA3_MAX_DMA_CH, (Assert_Id)NULL);

        edmaWord = (resObj.resId)/32;
        edmaIndex = resObj.resId - (32 * edmaWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels[edmaWord]
            |= (0x1 << edmaIndex);

        edmas--;
        /* Allocated edma channel successfully*/

        if (ti_sdo_fc_edma3_Settings_eventQueueSetup) {
            regOffset = DMAQNUM_OFFSET + 0x4 * (resObj.resId >> 3);

            EDMA3_RM_getCCRegister(_systemResourceManagerHandle,
                    regOffset, &value);

            value &= (~(0xF << (0x4 * (resObj.resId & 0x7))));
            value |= (ti_sdo_fc_edma3_Settings_defaultQ << (0x4 *
                    (resObj.resId & 0x7)));

            Log_print2(Diags_USER2,
                    "[+2] populateScratchGroup> Writing 0x%x to offset 0x%x "
                    "for setting DMAQNUM", (IArg)(value),
                        (IArg)(regOffset));

            EDMA3_RM_setCCRegister(_systemResourceManagerHandle, regOffset,
                    value);
        }

    }

    if (edmas) {

        Log_print1(Diags_USER7,
                "[+7] populateScratchGroup> Error allocating EDMA channels for"
                " scratch group %d", (IArg)scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_QDMA_CHANNEL;
    while(qdmas ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            Log_print1(Diags_USER7,
                    "[+7] populateScratchGroup> Error allocating qdma channel %d",
                    (IArg)(resObj.resId));

            Log_print0(Diags_EXIT, "[+X] populateScratchGroup> Exit (status=0)");

            return (0);
        }

        Assert_isTrue(resObj.resId <  EDMA3_MAX_QDMA_CH, (Assert_Id)NULL);

        qdmaWord = (resObj.resId)/32;
        qdmaIndex = resObj.resId - (32 * qdmaWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownQdmaChannels[qdmaWord]
                |= (0x1 << qdmaIndex);

        qdmas--;
    }

    if (qdmas) {

        Log_print1(Diags_USER7,
                "[+7] populateScratchGroup> Error allocating QDMA channels for"
                " scratch group %d", (IArg)scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_PARAM_SET;
    while(params ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_PARAMS.contigParams) {
            if (EDMA3_RM_SOK != EDMA3_RM_allocContiguousResource(
                    _systemResourceManagerHandle, &resObj, params)) {

                Log_print1(Diags_USER7,
                        "[+7] populateScratchGroup> Error allocating %d "
                        "contiguous param sets", (IArg)params);

                Log_print0(Diags_EXIT,
                        "[+X] populateScratchGroup> Exit (status=0)");

                return (0);
            }
            else {

                Assert_isTrue(resObj.resId < EDMA3_MAX_PARAM_SETS , (Assert_Id)NULL);
                Assert_isTrue((resObj.resId + params) <= EDMA3_MAX_PARAM_SETS , (Assert_Id)NULL);

                for (k = 0 ; k < params; k++) {

                    paramWord = (k + resObj.resId)/32;
                    paramIndex = (k + resObj.resId) - (32 * paramWord);

                    EDMA3_scratchResourceConfig[scratchGroupId].
                            ownPaRAMSets[paramWord] |= (0x1 << paramIndex);
                }

                params = 0;
                break;
            }
        }

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            Log_print1(Diags_USER7,
                    "[+7] populateScratchGroup> Error allocating param set %d",
                    (IArg)(resObj.resId));

            Log_print0(Diags_EXIT, "[+X] populateScratchGroup> Exit (status=0)");

            return (0);
        }

        Assert_isTrue(resObj.resId < EDMA3_MAX_PARAM_SETS , (Assert_Id)NULL);

        paramWord = (resObj.resId)/32;
        paramIndex = resObj.resId - (32 * paramWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownPaRAMSets[paramWord]
                |= (0x1 << paramIndex);

        params--;
    }

    if (params) {

        Log_print1(Diags_USER7,
                "[+7] populateScratchGroup> Error allocating PaRAMs for"
                " scratch group %d", (IArg)scratchGroupId);
    }

populateEnd:
    if (tccs + edmas + params + qdmas) {

        Log_print0(Diags_USER7,
                "[+7] populateScratchGroup> Error allocating resources");

        Log_print0(Diags_EXIT, "[+X] populateScratchGroup> Exit (status=0)");

        return (0);
    }

    _table[scratchGroupId].populated = TRUE;

    Log_print0(Diags_USER2, "[+2] populateScratchGroup> Exit (status=1)");

    return (1);
}

/*
 *  ======== openRMHandle ========
 *  Opens a new RM handle for a particular scratch group
 */
static EDMA3_RM_Handle openRMHandle(Int scratchId, Void * sem )
{
    EDMA3_RM_Handle handle;
    EDMA3_RM_Result status;
    EDMA3_RM_Param initParam;
    EDMA3_RM_IoctlCmd ioctlCmd = EDMA3_RM_IOCTL_SET_PARAM_CLEAR_OPTION;
    UInt setMask = 0x0;
    UInt clearMask = 0xFFFFFFFF;
    unsigned int baseAddr = 0x0;
    unsigned int registerAddr = 0x0;
    int i;

    Log_print2(Diags_ENTRY, "[+E] openRMHandle> Enter (scratchId=%d, sem=0x%x)",
            (IArg)scratchId, (IArg)sem);

    initParam.isMaster = 0;         /* ? This module is never the master */

    if (-1 == scratchId) {

        Log_print0(Diags_USER2, "[+2] openRMHandle> System RM handle requested");

        initParam.rmInstInitConfig = (EDMA3_RM_InstanceInitConfig *)
                EDMA3_PARAMS.regionConfig;

        initParam.regionId = EDMA3_PARAMS.regionId;
    }
    else {

/* TODO: Adding some book keeping from the Region Config would let us expand the
         resources allocated as per the first requesting Alg in that scratch
         Group. (new API will be required for that in this MODULE to share
         that information)
 */

        Log_print0(Diags_USER2, "[+2] openRMHandle>"
                " Populating Scratch Groups with Resources");

        if (!(populateScratchGroup(scratchId))) {

            Log_print0(Diags_USER7,
                    "[+7] openRMHandle> Error populating RM scratch groups");

            if (EDMA3_RM_SOK != closeRMHandle(_systemResourceManagerHandle)) {

                Log_print1(Diags_USER7,
                        "[+7] openRMHandle> Error deleting RM handle 0x%x",
                        (IArg)_systemResourceManagerHandle);
            }

            _systemResourceManagerHandle = NULL;

            Log_print0(Diags_USER2,
                    "[+2] openRMHandle> Deleting System semaphore");

            EDMA3_semDelete(_systemResourceManagerSem);

                _systemResourceManagerSem = NULL;

            if (1 != edma3Exit()) {

                Log_print0(Diags_USER7,
                        "[+7] openRMHandle> Error exiting EDMA3 Meta config module"
                        "");
            }

            Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

            return (NULL);
                }

        initParam.rmInstInitConfig = (EDMA3_RM_InstanceInitConfig *)
                &EDMA3_scratchResourceConfig[scratchId];

        initParam.regionId = EDMA3_PARAMS.regionId;
    }

    initParam.rmSemHandle = sem;

    initParam.regionInitEnable = 0; /* ? Not supporting region access etc */

    handle = EDMA3_RM_open(ti_sdo_fc_edma3_EDMA3_physicalId, &initParam,
            &status);

    if (EDMA3_RM_SOK != status) {

        Log_print1(Diags_USER7, "[+7] openRMHandle> Error "
                "opening RM handle requested, status 0x%x\n", status);

        Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

        return (NULL);
    }

    status = EDMA3_RM_Ioctl(handle, ioctlCmd, (void *)EDMA3_PARAMS.globalInit,
            NULL);

    if (EDMA3_RM_SOK != status) {

        Log_print0(Diags_USER7, "[+7] openRMHandle> Error "
                "during IOCTL command EDMA3_RM_IOCTL_SET_PARAM_CLEAR_OPTION "
                "on EDMA3 Low Level Resource Manager");

        Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

        return (NULL);
    }

    ioctlCmd = EDMA3_RM_IOCTL_SET_GBL_REG_MODIFY_OPTION;

    status = EDMA3_RM_Ioctl(handle, ioctlCmd, (void *)EDMA3_PARAMS.globalInit,
            NULL);

    if (EDMA3_RM_SOK != status) {

        Log_print0(Diags_USER7, "[+7] openRMHandle> Error "
                "during IOCTL command EDMA3_RM_IOCTL_SET_GBL_REG_MODIFY_OPTION "
                "on EDMA3 Low Level Resource Manager");

        Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

        return (NULL);
    }

    if (-1 == scratchId) {

        if (EDMA3_RM_SOK != EDMA3_RM_getBaseAddress(handle,
                (EDMA3_RM_Cntrlr_PhyAddr)EDMA3_RM_CC_PHY_ADDR, &baseAddr)) {

            Log_print0(Diags_USER7, "[+7] openRMHandle> Error during IOCTL "
                    "command EDMA3_RM_IOCTL_SET_GBL_REG_MODIFY_OPTION "
                    "on EDMA3 Low Level Resource Manager");

            Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

            return (NULL);

        }

        /* The system resource handle is opened once per executable, at this
           time, set up the Queue TC mapping and priorities, if required */
        if (ti_sdo_fc_edma3_Settings_eventQueueSetup) {

            /* ti_sdo_fc_edma3_Settings_queueTCMap */
            registerAddr = (baseAddr + (QUETCMAP_OFFSET));

            setMask = 0x0;
            clearMask = 0xFFFFFFFF;
            /* Create QUETCMAP mask */
            for (i = 0; i < 8; i++) {
                if (ti_sdo_fc_edma3_Settings_queueTCMap[i] != -1){
                    clearMask &= (~(0xF << (i * 4)));
                    setMask |= (ti_sdo_fc_edma3_Settings_queueTCMap[i] <<
                            (i * 4));
                }
            }
            /* Obtain QUETCMAP register and write mask to it */
            *(unsigned int *)registerAddr &= clearMask;
            *(unsigned int *)registerAddr |= setMask;

            /* ti_sdo_fc_edma3_Settings_queuePriority */
            registerAddr = (baseAddr + QUEPRI_OFFSET);

            /* Create QUEPRI mask */
            setMask = 0x0;
            clearMask = 0xFFFFFFFF;
            for (i = 0; i < 8; i++) {
                if (ti_sdo_fc_edma3_Settings_queuePriority[i] != -1) {
                    clearMask &= (~(0xF << (i * 4)));
                    setMask |= (ti_sdo_fc_edma3_Settings_queuePriority[i] <<
                            (i * 4));
                }
            }
            /* Obtain QUEPRI register and write mask to it */
            *(unsigned int *)registerAddr &= clearMask;
            *(unsigned int *)registerAddr |= setMask;
        }

        if ((NULL == EDMA3_PARAMS.regionConfig)) {

           if (EDMA3_RM_SOK != EDMA3_RM_getInstanceInitCfg(handle,
                   &_regionConfig)) {

               Log_print0(Diags_USER7, "[+7] openRMHandle> Error "
                       "trying to get Region information from EDMA3 RM");

               Log_print0(Diags_EXIT, "[+X] openRMHandle> Exit (handle=NULL)");

               return (NULL);
           }

           EDMA3_PARAMS.regionConfig =
                    (EDMA3_InstanceInitConfig * ) &_regionConfig;
       }
    }

    Log_print1(Diags_EXIT, "[+X] openRMHandle> Exit (handle=0x%x)",
            (IArg)handle);

    return (handle);
}

/*
 *  ========  closeRMHandle ========
 *  Closes the RM Handle for a particular scratch group
 */
static EDMA3_RM_Result closeRMHandle(EDMA3_RM_Handle handle)
{
    EDMA3_RM_Result status = EDMA3_RM_SOK;

    Log_print1(Diags_ENTRY, "[+E] closeRMHandle> Enter (handle=0x%x)",
            (IArg)handle);

    status = EDMA3_RM_close(handle, NULL);

    Log_print1(Diags_EXIT, "[+X] closeRMHandle> Exit (status=0x%x)",
            (IArg)status);

    return (status);
}

/*
 *  ======== unpopulateScratchGroup ========
 *  Unpopulates the scratch resources for the scratch group
 */
static Int unpopulateScratchGroup(Int scratchGroupId)
{
    Int i,j = 0;
    Int tccs = 0;
    Int edmas = 0;
    Int qdmas = 0;
    Int params = 0;
    Int resourceWord = 0;
    Int status = 1;
    Int mask = 0x0;

    EDMA3_RM_ResDesc resObj;

    Log_print1(Diags_ENTRY,
            "[+E] unpoulateScratchGroups> Enter (scratchGroupId=%d)",
            (IArg)scratchGroupId);

    if (!(_table[scratchGroupId].populated)) {

        Log_print0(Diags_USER2, "[+2] unpoulateScratchGroups> Exit (status=0)");

        return (0);
    }

    tccs = EDMA3_tccScratchSizes[scratchGroupId];
    edmas = EDMA3_edmaChanScratchSizes[scratchGroupId];
    qdmas = EDMA3_qdmaChanScratchSizes[scratchGroupId];
    params = EDMA3_paRamScratchSizes[scratchGroupId];

    if (!( tccs + edmas + qdmas + params)) {
            goto unpopulateEnd;
    }

    Log_print4(Diags_USER2,
            "[+2] unpopulateScratchGroup> Freeing %d tccs %d edma %d "
            "qdma channels and %d params",
            (IArg)tccs, (IArg)edmas, (IArg)qdmas, (IArg)params);

    resObj.type = EDMA3_RM_RES_TCC;

    for (i = 0; i < EDMA3_MAX_TCC_DWRDS; i++) {
        if (EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[i] == 0x0) {
            continue;
        }
        else {
            resourceWord =
                    EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[i];
            for (j = 0; j < 32; j++) {
                if (resourceWord & (0x1 << j)) {
                    resObj.resId = i * 32 + j;
                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {
                        Log_print1(Diags_USER7,
                                "[+7] unpopulateScratchGroup> Error freeing tc"
                                "c %d"                                , (IArg)(resObj.resId));
                        status = 0;
                    }
                    else {
                        mask = ~(0x1 << j);
                        EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[i]
                                &= mask;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

    for (i = 0; i < EDMA3_MAX_DMA_CHAN_DWRDS; i++) {
        if (EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels[i] ==
                0x0) {
            continue;
        }
        else {
            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownDmaChannels[i];
            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;
                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        Log_print1(Diags_USER7,
                                "[+7] unpopulateScratchGroup> Error freeing DM"
                                "A %d"                                , (IArg)(resObj.resId));
                        status = 0;
                    }
                    else {
                        mask = ~(0x1 << j);
                        EDMA3_scratchResourceConfig[scratchGroupId].
                                ownDmaChannels[i] &= mask;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_QDMA_CHANNEL;

    for (i = 0; i < EDMA3_MAX_QDMA_CHAN_DWRDS; i++) {

        if (EDMA3_scratchResourceConfig[scratchGroupId].ownQdmaChannels[i] ==
                0x0) {
            continue;
        }
        else {

            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownQdmaChannels[i];

            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;

                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        Log_print1(Diags_USER7,
                                "[+7] unpopulateScratchGroup> Error freeing DM"
                                "A %d"                                , (IArg)(resObj.resId));
                        status = 0;
                    }
                    else {
                        mask = ~(0x1 << j);
                        EDMA3_scratchResourceConfig[scratchGroupId].
                                ownQdmaChannels[i] &= mask;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_PARAM_SET;

    for (i = 0; i < EDMA3_MAX_PARAM_DWRDS; i++) {

        if (EDMA3_scratchResourceConfig[scratchGroupId].ownPaRAMSets[i] ==
                0x0) {
            continue;
        }
        else {

            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownPaRAMSets[i];

            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;

                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        Log_print1(Diags_USER7,
                                "[+7] unpopulateScratchGroup> Error freeing PARAM %d"
                                "", (IArg)(resObj.resId));
                        status = 0;
                    }
                    else {
                        mask = ~(0x1 << j);
                        EDMA3_scratchResourceConfig[scratchGroupId].
                                ownPaRAMSets[i] &= mask;
                    }
                }
            }
        }
    }

unpopulateEnd:
    if (status == 0) {

        Log_print0(Diags_USER7,
                "[+7] unpopulateScratchGroup> Error freeing resources");

        Log_print0(Diags_EXIT, "[+X] unpopulateScratchGroup> Exit (status=0)");

        return (0);
    }

    _table[scratchGroupId].populated = FALSE;

    Log_print0(Diags_USER2, "[+2] unpopulateScratchGroup> Exit (status=1)");

    return (1);
}

EDMA3_Result EDMA3_getBaseAddress(EDMA3_Handle hEdmaResMgr,
        EDMA3_Cntrlr_PhyAddr controllerId, unsigned int *phyAddress)
{
    return ((EDMA3_Result)EDMA3_RM_getBaseAddress((EDMA3_RM_Handle)hEdmaResMgr,
            (EDMA3_RM_Cntrlr_PhyAddr)controllerId, phyAddress));
}

EDMA3_Result EDMA3_getCCRegister(EDMA3_Handle hEdmaResMgr,
        unsigned int regOffset, unsigned int *regValue)
{
    return ((EDMA3_RM_Result)EDMA3_RM_getCCRegister(
            (EDMA3_RM_Handle)hEdmaResMgr, regOffset, regValue));
}

EDMA3_Result EDMA3_allocResource(EDMA3_Handle hEdmaResMgr,
                                        EDMA3_ResDesc *resObj)
{
    return ((EDMA3_Result)(EDMA3_RM_allocResource((EDMA3_RM_Handle)hEdmaResMgr,
            (EDMA3_RM_ResDesc *)resObj)));
}

EDMA3_Result EDMA3_freeResource(EDMA3_Handle hEdmaResMgr,
        const EDMA3_ResDesc *resObj)
{
    return ((EDMA3_Result)(EDMA3_RM_freeResource((EDMA3_RM_Handle)
            hEdmaResMgr, (const EDMA3_RM_ResDesc *)resObj)));
}

EDMA3_Result EDMA3_allocContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources)
{
    return ((EDMA3_Result)(EDMA3_RM_allocContiguousResource((EDMA3_RM_Handle)
            hEdmaResMgr, (EDMA3_RM_ResDesc *)firstResIdObj, numResources)));
}

EDMA3_Result EDMA3_allocLogicalChannel(EDMA3_Handle hEdmaResMgr,
       EDMA3_ResDesc *lChObj, unsigned int *pParam, unsigned int *pTcc)
{
    return ((EDMA3_Result)EDMA3_RM_allocLogicalChannel((EDMA3_RM_Handle)
            hEdmaResMgr, (EDMA3_RM_ResDesc *)lChObj, pParam, pTcc));

}

EDMA3_Result EDMA3_freeLogicalChannel (EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *lChObj)
{
    return ((EDMA3_Result)EDMA3_RM_freeLogicalChannel((EDMA3_RM_Handle)
            hEdmaResMgr, (EDMA3_RM_ResDesc *)lChObj));
}

EDMA3_Result EDMA3_freeContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources)
{
    return ((EDMA3_Result)(EDMA3_RM_freeContiguousResource((EDMA3_RM_Handle)
            hEdmaResMgr, (EDMA3_RM_ResDesc *)firstResIdObj, numResources)));
}


#include <xdc/runtime/System.h>
#include <xdc/runtime/knl/ISemaphore.h>
#include <ti/sdo/fc/utils/osalsupport/OsalSupport.h>

/*
 *  ======== EDMA3_semCreate ========
 *  Function to create a Semaphore given a key
 */
void * EDMA3_semCreate(Int key, Int count)
{
    void * sem;

    /*
     * Call RMAN's configured semCreateFxn, cast the returned semaphore value
     * to the Semaphore type expected by EDMA3 RM.
     */
    sem = (void *)OsalSupport_createSem(count, key);

    if (sem == NULL) {
        xdc_runtime_System_abort("EDMA3_semCreate: Sempahore Creation "
                "failed\n");
    }

    return (sem);
}

/*
 *  ======== EDMA3_semDelete ========
 *  Function to delete a given Semaphore
 */
void EDMA3_semDelete(EDMA3_SemHandle hSem)
{
     OsalSupport_deleteSem((xdc_runtime_knl_ISemaphore_Handle)hSem);
}

/*
 *  ======== EDMA3_createResourceManagerObject ========
 *  Creates a resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_createResourceManagerObject()
{
    EDMA3_Result status;
    EDMA3_RM_MiscParam param = {NULL , NULL};

    param.isSlave = (EDMA3_PARAMS.globalInit == 1) ? 0 : 1;

    status = EDMA3_RM_create( ti_sdo_fc_edma3_EDMA3_physicalId,
            (EDMA3_RM_GblConfigParams *)(EDMA3_PARAMS.globalConfig), &param);

    return ((EDMA3_Result)status);
}

/*
 *  ======== EDMA3_deleteResourceManagerObject ========
 *  Deletes the resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_deleteResourceManagerObject()
{
    EDMA3_Result status;

    status = EDMA3_RM_delete(ti_sdo_fc_edma3_EDMA3_physicalId,
            (const void *)NULL);

    return (status);
}

#ifdef RMOBJCREA
/*
 *  ======== edma3OsSemGive ========
 *  Function to Post a semaphore
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemGive(EDMA3_SemHandle hSem)
{
    EDMA3_RM_Result semGiveResult = EDMA3_RM_SOK;
    if(NULL == hSem) {
        semGiveResult = EDMA3_RM_E_INVALID_PARAM;
    }
    else {
        xdc_runtime_knl_ISemaphore_post(hSem, NULL);
    }
    return (semGiveResult);
}

/*
 *  ======== edma3OsSemTake ========
 *  Function to Pend on a semaphore
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemTake(EDMA3_SemHandle hSem, int mSecTimeout)
{
    EDMA3_Result semTakeResult = EDMA3_SOK;
    unsigned short semPendResult;
    if(NULL == hSem) {
        semTakeResult = EDMA3_E_INVALID_PARAM;
    }
    else {
        semPendResult = xdc_runtime_knl_ISemaphore_pend(hSem,
                xdc_runtime_knl_ISemaphore_FOREVER, NULL);

        if (semPendResult != TRUE) {
            semTakeResult = EDMA3_E_SEMAPHORE;
        }
    }

    return (semTakeResult);
}

/*
 *  ======== edma3OsProtectEntry ========
 *  OS critical section protect (Entry) function
 */
void edma3OsProtectEntry (unsigned int edma3InstanceId, int level,
        unsigned int *intState)
{
    /* For now we ignore the instanceId */
    /* (void)edma3InstanceId;*/

    if (((level == EDMA3_OS_PROTECT_INTERRUPT)
        || (level == EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR))
        && (intState == NULL)) {
        return;
    }
    else {
        switch (level) {
            /* Disable all (global) interrupts */
            case EDMA3_OS_PROTECT_INTERRUPT :
                    *intState = ti_sysbios_hal_Hwi_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_SCHEDULER :
                    *intState = ti_sysbios_knl_Task_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
                    *intState = ti_sysbios_knl_Task_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
                    *intState = ti_sysbios_knl_Task_disable();
                break;

            case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
                switch (*intState) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        /* Fall through... */
                            *intState = ti_sysbios_knl_Task_disable();
                        break;

                     default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}

/*
 *  ======== edma3OsProtectExit ========
 *  OS critical section protect (Exit) function
 */
void edma3OsProtectExit(unsigned int edma3InstanceId, int level,
        unsigned int intState)
{
/*      (void)edma3InstanceId;*/

    switch (level) {
        /* Enable all (global) interrupts */
        case EDMA3_OS_PROTECT_INTERRUPT :
                ti_sysbios_hal_Hwi_restore(intState);
            break;

        /* Enable scheduler */
        case EDMA3_OS_PROTECT_SCHEDULER :
            break;

        case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
                ti_sysbios_knl_Task_restore(intState);
            break;

        case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
                ti_sysbios_knl_Task_restore(intState);
            break;

        /* Enable EDMA3 TC error interrupt only */
        case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
            switch (intState)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    /* Fall through... */
                    /* Enable the corresponding interrupt */
                        ti_sysbios_knl_Task_restore(intState);
                    break;

                 default:
                    break;
                }

            break;

        default:
            break;
    }
}

#endif
