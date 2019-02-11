/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== Ipc.c ========
 */

#include <string.h>     /* for memcpy() */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/sdo/ipc/_Ipc.h>
#include <ti/sdo/ipc/_Notify.h>
#include <ti/sdo/ipc/_GateMP.h>
#include <ti/sdo/ipc/_SharedRegion.h>
#include <ti/sdo/utils/_MultiProc.h>
#include <ti/sdo/utils/_NameServer.h>
#include <ti/sdo/ipc/_MessageQ.h>

#include "package/internal/Ipc.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(Ipc_attach);
    #pragma FUNC_EXT_CALLED(Ipc_clusterConfig);
    #pragma FUNC_EXT_CALLED(Ipc_detach);
    #pragma FUNC_EXT_CALLED(Ipc_isAttached);
    #pragma FUNC_EXT_CALLED(Ipc_readConfig);
    #pragma FUNC_EXT_CALLED(Ipc_start);
    #pragma FUNC_EXT_CALLED(Ipc_stop);
    #pragma FUNC_EXT_CALLED(Ipc_writeConfig);
#endif

/*
 *  For no MMU case, it should be set to TRUE always.
 *  For MMU, it would be set by IPC link between local and HOST processors.
 */
extern __FAR__ Bits32 Ipc_sr0MemorySetup;

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== Ipc_attach ========
 */
Int Ipc_attach(UInt16 remoteProcId)
{
    Int i;
    Ptr sharedAddr;
    SizeT memReq;
    volatile ti_sdo_ipc_Ipc_Reserved *slave;
    ti_sdo_ipc_Ipc_ProcEntry *ipc;
    Error_Block eb;
    SharedRegion_Entry entry;
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    Int status;
    UInt hwiKey;

    /* Assert remoteProcId is in our cluster and isn't our own */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);
    Assert_isTrue(remoteProcId != MultiProc_self(),
                  ti_sdo_ipc_Ipc_A_invArgument);

    /* Check whether Ipc_start has been called.  If not, fail. */
    if (Ipc_module->ipcSharedAddr == NULL) {
        return (Ipc_E_FAIL);
    }

    /* for checking and incrementing attached below */
    hwiKey = Hwi_disable();

    /* Make sure its not already attached */
    if (Ipc_module->procEntry[clusterId].attached) {
        Ipc_module->procEntry[clusterId].attached++;
        /* restore interrupts and return */
        Hwi_restore(hwiKey);
        return (Ipc_S_ALREADYSETUP);
    }

    /* restore interrupts */
    Hwi_restore(hwiKey);

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /* Make sure we've attached to owner of SR0 if we're not owner */
    if ((MultiProc_self() != entry.ownerProcId) &&
        (remoteProcId != entry.ownerProcId) &&
        !(Ipc_module->procEntry[ti_sdo_utils_MultiProc_getClusterId(
            entry.ownerProcId)].attached)) {
        return (Ipc_E_FAIL);
    }

    /* Init error block */
    Error_init(&eb);

    /* determine the slave's slot */
    slave = Ipc_getSlaveAddr(remoteProcId, Ipc_module->ipcSharedAddr);

    if (cacheEnabled) {
        Cache_inv((Ptr)slave, reservedSize, Cache_Type_ALL, TRUE);
    }

    /* Synchronize the processors. */
    status = Ipc_procSyncStart(remoteProcId, Ipc_module->ipcSharedAddr);
    if (status < 0) {
        return (status);
    }

    /* must be called before SharedRegion_attach */
    status = ti_sdo_ipc_GateMP_attach(remoteProcId,
            Ipc_module->gateMPSharedAddr);
    if (status < 0) {
        return (status);
    }

    /* retrieves the SharedRegion Heap handles */
    status = ti_sdo_ipc_SharedRegion_attach(remoteProcId);
    if (status < 0) {
        return (status);
    }

    /* get the attach parameters associated with remoteProcId */
    ipc = &(Ipc_module->procEntry[clusterId]);

    /* attach Notify if not yet attached and specified to set internal setup */
    if (!(Notify_intLineRegistered(remoteProcId, 0)) &&
        (ipc->entry.setupNotify)) {
        /* call Notify_attach */
        memReq = Notify_sharedMemReq(remoteProcId, Ipc_module->ipcSharedAddr);
        if (memReq != 0) {
            if (MultiProc_self() < remoteProcId) {
                /*
                 *  calloc required here due to race condition.  Its possible
                 *  that the slave, who creates the instance, tries a sendEvent
                 *  before the master has created its instance because the
                 *  state of memory was enabled from a previous run.
                 */
                sharedAddr = Memory_calloc(SharedRegion_getHeap(0),
                                       memReq,
                                       SharedRegion_getCacheLineSize(0),
                                       &eb);

                /* make sure alloc did not fail */
                if (sharedAddr == NULL) {
                    return (Ipc_E_MEMORY);
                }

                /* if cache enabled, wbInv the calloc above */
                if (cacheEnabled) {
                    Cache_wbInv(sharedAddr, memReq, Cache_Type_ALL, TRUE);
                }

                /* set the notify SRPtr */
                slave->notifySRPtr = SharedRegion_getSRPtr(sharedAddr, 0);
            }
            else {
                /* get the notify SRPtr */
                sharedAddr = SharedRegion_getPtr(slave->notifySRPtr);
            }
        }
        else {
            sharedAddr = NULL;
            if (MultiProc_self() < remoteProcId) {
                slave->notifySRPtr = SharedRegion_invalidSRPtr();
            }
        }

        /* call attach to remote processor */
        status = Notify_attach(remoteProcId, sharedAddr);

        if (status < 0) {
            if (MultiProc_self() < remoteProcId && sharedAddr != NULL) {
                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0), sharedAddr, memReq);
            }

            return (Ipc_E_FAIL);
        }
    }

    /* Must come after GateMP_start because depends on default GateMP */
    if (!(ti_sdo_utils_NameServer_isRegistered(remoteProcId)) &&
        (ipc->entry.setupNotify)) {
        memReq = ti_sdo_utils_NameServer_SetupProxy_sharedMemReq(
            Ipc_module->ipcSharedAddr);
        if (memReq != 0) {
            if (MultiProc_self() < remoteProcId) {
                sharedAddr = Memory_alloc(SharedRegion_getHeap(0),
                                     memReq,
                                     SharedRegion_getCacheLineSize(0),
                                     &eb);

                /* make sure alloc did not fail */
                if (sharedAddr == NULL) {
                    return (Ipc_E_MEMORY);
                }

                /* set the NSRN SRPtr */
                slave->nsrnSRPtr = SharedRegion_getSRPtr(sharedAddr, 0);
            }
            else {
                /* get the NSRN SRPtr */
                sharedAddr = SharedRegion_getPtr(slave->nsrnSRPtr);
            }
        }
        else {
            sharedAddr = NULL;
            if (MultiProc_self() < remoteProcId) {
                slave->nsrnSRPtr = SharedRegion_invalidSRPtr();
            }
        }

        /* call attach to remote processor */
        status = ti_sdo_utils_NameServer_SetupProxy_attach(remoteProcId,
                                                           sharedAddr);

        if (status < 0) {
            if (MultiProc_self() < remoteProcId && sharedAddr != NULL) {
                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0), sharedAddr, memReq);
            }

            return (Ipc_E_FAIL);
        }
    }

    /* Must come after GateMP_start because depends on default GateMP */
    if (!(ti_sdo_ipc_MessageQ_SetupTransportProxy_isRegistered(remoteProcId)) &&
        (ipc->entry.setupMessageQ)) {
        memReq = ti_sdo_ipc_MessageQ_SetupTransportProxy_sharedMemReq(
            Ipc_module->ipcSharedAddr);

        if (memReq != 0) {
            if (MultiProc_self() < remoteProcId) {
                sharedAddr = Memory_alloc(SharedRegion_getHeap(0),
                    memReq, SharedRegion_getCacheLineSize(0), &eb);

                /* make sure alloc did not fail */
                if (sharedAddr == NULL) {
                    return (Ipc_E_MEMORY);
                }

                /* set the transport SRPtr */
                slave->transportSRPtr = SharedRegion_getSRPtr(sharedAddr, 0);
            }
            else {
                /* get the transport SRPtr */
                sharedAddr = SharedRegion_getPtr(slave->transportSRPtr);
            }
        }
        else {
            sharedAddr = NULL;
            if (MultiProc_self() < remoteProcId) {
                slave->transportSRPtr = SharedRegion_invalidSRPtr();
            }
        }

        /* call attach to remote processor */
        status = ti_sdo_ipc_MessageQ_SetupTransportProxy_attach(remoteProcId,
            sharedAddr);

        if (status < 0) {
            if (MultiProc_self() < remoteProcId && sharedAddr != NULL) {
                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0), sharedAddr, memReq);
            }

            return (Ipc_E_FAIL);
        }
    }

    /* writeback invalidate slave's shared memory if cache enabled */
    if (cacheEnabled) {
        if (MultiProc_self() < remoteProcId) {
            Cache_wbInv((Ptr)slave, reservedSize, Cache_Type_ALL, TRUE);
        }
    }

    /* Call user attach fxns */
    for (i = 0; i < ti_sdo_ipc_Ipc_numUserFxns; i++) {
        if (ti_sdo_ipc_Ipc_userFxns[i].userFxn.attach) {
            status = ti_sdo_ipc_Ipc_userFxns[i].userFxn.attach(
                ti_sdo_ipc_Ipc_userFxns[i].arg, remoteProcId);

            if (status < 0) {
                return (status);
            }
        }
    }

    /* Finish the processor synchronization */
    status = ti_sdo_ipc_Ipc_procSyncFinish(remoteProcId,
        Ipc_module->ipcSharedAddr);

    if (status < 0) {
        return (status);
    }

    /* for atomically incrementing attached */
    hwiKey = Hwi_disable();

    /* now attached to remote processor */
    Ipc_module->procEntry[clusterId].attached++;

    /* restore interrupts */
    Hwi_restore(hwiKey);

    return (status);
}

/*
 *  ======== Ipc_clusterConfig ========
 */
Int Ipc_clusterConfig(Void)
{
    UInt16 *procIdPtr;
    UInt16 numProcs;
    UInt16 baseId;
    UInt16 i;


    /* sanity check the cluster baseId */
    baseId = MultiProc_getBaseIdOfCluster();

    if (baseId == MultiProc_INVALIDID) {
        return (Ipc_E_INVALIDSTATE);
    }

    /* initialize the MultiProc.clusterProcList array */
    numProcs = MultiProc_getNumProcsInCluster();
    procIdPtr = MultiProc_getClusterProcList();

    for (i = 0; i < numProcs; i++) {
        *procIdPtr++ = baseId + i;
    }

    /* update the Ipc.procEntry[] array with valid procIds */
    for (i = 0; i < numProcs; i++) {
        Ipc_module->procEntry[i].entry.remoteProcId = baseId + i;
    }

    return (Ipc_S_SUCCESS);
}

/*
 *  ======== Ipc_isAttached ========
 */
Bool Ipc_isAttached(UInt16 remoteProcId)
{
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);

    /* Assert remoteProcId is in our cluster */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    if (remoteProcId == MultiProc_self()) {
        return (FALSE);
    }
    else {
        return (Ipc_module->procEntry[clusterId].attached);
    }
}

/*
 *  ======== Ipc_detach ========
 */
Int Ipc_detach(UInt16 remoteProcId)
{
    Int i;
    UInt16 baseId = MultiProc_getBaseIdOfCluster();
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    Ptr notifySharedAddr;
    Ptr nsrnSharedAddr;
    Ptr msgqSharedAddr;
    volatile ti_sdo_ipc_Ipc_Reserved *slave, *master;
    SharedRegion_Entry entry;
    ti_sdo_ipc_Ipc_ProcEntry *ipc;
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);
    Int status = Ipc_S_SUCCESS;
    UInt hwiKey;

    /* Assert remoteProcId is in our cluster and isn't our own */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);
    Assert_isTrue(remoteProcId != MultiProc_self(),
                  ti_sdo_ipc_Ipc_A_invArgument);

    /* for checking and incrementing attached below */
    hwiKey = Hwi_disable();

    if (Ipc_module->procEntry[clusterId].attached > 1) {
        /* only detach if attach count reaches 1 */
        Ipc_module->procEntry[clusterId].attached--;
        Hwi_restore(hwiKey);
        return (Ipc_S_BUSY);
    }
    else if (Ipc_module->procEntry[clusterId].attached == 0) {
        /* already detached, restore interrupts and return success */
        Hwi_restore(hwiKey);
        return (Ipc_S_SUCCESS);
    }

    /* restore interrupts */
    Hwi_restore(hwiKey);

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /*
     *  Make sure we detach from all other procs in cluster before
     *  detaching from owner of SR 0.
     */
    if (remoteProcId == entry.ownerProcId) {
        for (i = 0; i < ti_sdo_utils_MultiProc_numProcsInCluster; i++, baseId++) {
            if ((baseId != MultiProc_self()) && (baseId != entry.ownerProcId) &&
                (Ipc_module->procEntry[i].attached)) {
                return (Ipc_E_FAIL);
            }
        }
    }

    /* get the paramters associated with remoteProcId */
    ipc = &(Ipc_module->procEntry[clusterId]);

    /* determine the slave's slot */
    slave = Ipc_getSlaveAddr(remoteProcId, Ipc_module->ipcSharedAddr);

    /* determine the master's slot */
    master = ti_sdo_ipc_Ipc_getMasterAddr(remoteProcId,
        Ipc_module->ipcSharedAddr);

    if (cacheEnabled) {
        Cache_inv((Ptr)slave, reservedSize, Cache_Type_ALL, TRUE);
        Cache_inv((Ptr)master, reservedSize, Cache_Type_ALL, TRUE);
    }

    if (MultiProc_self() < remoteProcId) {
        /* check to make sure master is not trying to attach */
        if (master->startedKey == ti_sdo_ipc_Ipc_PROCSYNCSTART) {
            return (Ipc_E_NOTREADY);
        }
    }
    else {
        /* check to make sure slave is not trying to attach */
        if (slave->startedKey == ti_sdo_ipc_Ipc_PROCSYNCSTART) {
            return (Ipc_E_NOTREADY);
        }
    }

    /* The slave processor waits for master to finish its detach sequence */
    if (MultiProc_self() < remoteProcId) {
        if (master->startedKey != ti_sdo_ipc_Ipc_PROCSYNCDETACH) {
            return (Ipc_E_NOTREADY);
        }
    }

    /* Call user detach fxns */
    for (i = 0; i < ti_sdo_ipc_Ipc_numUserFxns; i++) {
        if (ti_sdo_ipc_Ipc_userFxns[i].userFxn.detach) {
            status = ti_sdo_ipc_Ipc_userFxns[i].userFxn.detach(
                ti_sdo_ipc_Ipc_userFxns[i].arg, remoteProcId);

            if (status < 0) {
                return (status);
            }
        }
    }

    if ((ipc->entry.setupMessageQ) &&
       (ti_sdo_ipc_MessageQ_SetupTransportProxy_isRegistered(remoteProcId))) {
        /* call MessageQ_detach for remote processor */
        status = ti_sdo_ipc_MessageQ_SetupTransportProxy_detach(remoteProcId);
        if (status < 0) {
            return (Ipc_E_FAIL);
        }

        if (slave->transportSRPtr != SharedRegion_invalidSRPtr()) {
            /* free the memory if slave processor */
            if (MultiProc_self() < remoteProcId) {
                /* get the pointer to MessageQ transport instance */
                msgqSharedAddr = SharedRegion_getPtr(slave->transportSRPtr);

                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0),
                    msgqSharedAddr,
                    ti_sdo_ipc_MessageQ_SetupTransportProxy_sharedMemReq(
                        msgqSharedAddr));

                /* set pointer for MessageQ transport instance to INVALID */
                slave->transportSRPtr = SharedRegion_invalidSRPtr();
            }
        }
    }

    if ((ipc->entry.setupNotify) &&
        (ti_sdo_utils_NameServer_isRegistered(remoteProcId))) {
        /* call NameServer_SetupProxy_detach for remote processor */
        status = ti_sdo_utils_NameServer_SetupProxy_detach(remoteProcId);
        if (status < 0) {
            return (Ipc_E_FAIL);
        }

        if (slave->nsrnSRPtr != SharedRegion_invalidSRPtr()) {
            /* free the memory if slave processor */
            if (MultiProc_self() < remoteProcId) {
                /* get the pointer to NSRN instance */
                nsrnSharedAddr = SharedRegion_getPtr(slave->nsrnSRPtr);

                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0),
                            nsrnSharedAddr,
                            ti_sdo_utils_NameServer_SetupProxy_sharedMemReq(
                                nsrnSharedAddr));

                /* set pointer for NSRN instance to INVALID */
                slave->nsrnSRPtr = SharedRegion_invalidSRPtr();
            }
        }
    }

    if ((ipc->entry.setupNotify) &&
        (Notify_intLineRegistered(remoteProcId, 0))) {
        /* call Notify_detach for remote processor */
        status = ti_sdo_ipc_Notify_detach(remoteProcId);
        if (status < 0) {
            return (Ipc_E_FAIL);
        }

        if (slave->notifySRPtr != SharedRegion_invalidSRPtr()) {
            /* free the memory if slave processor */
            if (MultiProc_self() < remoteProcId) {
                /* get the pointer to Notify instance */
                notifySharedAddr = SharedRegion_getPtr(slave->notifySRPtr);

                /* free the memory back to SharedRegion 0 heap */
                Memory_free(SharedRegion_getHeap(0),
                            notifySharedAddr,
                            Notify_sharedMemReq(remoteProcId, notifySharedAddr));

                /* set pointer for Notify instance to INVALID */
                slave->notifySRPtr = SharedRegion_invalidSRPtr();
            }
        }
    }

    /* close any HeapMemMP which may have been opened */
    status = ti_sdo_ipc_SharedRegion_detach(remoteProcId);
    if (status < 0) {
        return (status);
    }

    /* close any GateMP which may have been opened */
    status = ti_sdo_ipc_GateMP_detach(remoteProcId);
    if (status < 0) {
        return (status);
    }

    if (MultiProc_self() < remoteProcId) {
        slave->configListHead = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        slave->startedKey = ti_sdo_ipc_Ipc_PROCSYNCDETACH;
        if (cacheEnabled) {
            Cache_wbInv((Ptr)slave, reservedSize, Cache_Type_ALL, TRUE);
        }
    }
    else {
        master->configListHead = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;
        master->startedKey = ti_sdo_ipc_Ipc_PROCSYNCDETACH;
        if (cacheEnabled) {
            Cache_wbInv((Ptr)master, reservedSize, Cache_Type_ALL, TRUE);
        }
    }

    /* attached must be decremented atomically */
    hwiKey = Hwi_disable();

    /* now detached from remote processor */
    Ipc_module->procEntry[clusterId].attached--;

    /* restore interrupts */
    Hwi_restore(hwiKey);

    return (status);
}

/*
 *  ======== Ipc_readConfig ========
 */
Int Ipc_readConfig(UInt16 remoteProcId, UInt32 tag, Ptr cfg, SizeT size)
{
    Int status = Ipc_E_FAIL;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    volatile ti_sdo_ipc_Ipc_ConfigEntry *entry;
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);

    /* Assert that the remoteProc in our cluster and isn't our own */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    if (cacheEnabled) {
        Cache_inv(Ipc_module->procEntry[clusterId].remoteConfigList,
                  SharedRegion_getCacheLineSize(0),
                  Cache_Type_ALL,
                  TRUE);
    }

    entry = (ti_sdo_ipc_Ipc_ConfigEntry *)
            *Ipc_module->procEntry[clusterId].remoteConfigList;

    while ((SharedRegion_SRPtr)entry != ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
        entry = (ti_sdo_ipc_Ipc_ConfigEntry *)
                SharedRegion_getPtr((SharedRegion_SRPtr)entry);

        /* Traverse the list to find the tag */
        if (cacheEnabled) {
            Cache_inv((Ptr)entry,
                      size + sizeof(ti_sdo_ipc_Ipc_ConfigEntry),
                      Cache_Type_ALL,
                      TRUE);
        }

        if ((entry->remoteProcId == MultiProc_self()) &&
            (entry->localProcId == remoteProcId) &&
            (entry->tag == tag)) {

            if (size == entry->size) {
                memcpy(cfg, (Ptr)((UInt32)entry + sizeof(ti_sdo_ipc_Ipc_ConfigEntry)),
                        entry->size);
                return (Ipc_S_SUCCESS);
            }
            else {
                return (Ipc_E_FAIL);
            }
        }

        entry = (ti_sdo_ipc_Ipc_ConfigEntry *)entry->next;
    }

    return (status);
}

/*
 *  ======== Ipc_start ========
 */
Int Ipc_start()
{
    Int i;
    UInt16 baseId = MultiProc_getBaseIdOfCluster();
    SharedRegion_Entry entry;
    Ptr ipcSharedAddr;
    Ptr gateMPSharedAddr;
    GateMP_Params gateMPParams;
    Int status;

    /* Check whether Ipc_start has been called.  If so, succeed. */
    if (Ipc_module->ipcSharedAddr != NULL) {
        return (Ipc_S_ALREADYSETUP);
    }

    if (ti_sdo_ipc_Ipc_generateSlaveDataForHost) {
        /* get Ipc_sr0MemorySetup out of the cache */
        Cache_inv(&Ipc_sr0MemorySetup,
              sizeof(Ipc_sr0MemorySetup),
              Cache_Type_ALL,
              TRUE);

        /* check Ipc_sr0MemorySetup variable */
        if (Ipc_sr0MemorySetup == 0x0) {
            return (Ipc_E_NOTREADY);
        }
    }

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /* if entry is not valid then return */
    if (entry.isValid == FALSE) {
        return (Ipc_E_NOTREADY);
    }

    /*
     *  Need to reserve memory in region 0 for processor synchronization.
     *  This must done before SharedRegion_start().
     */
    ipcSharedAddr = ti_sdo_ipc_SharedRegion_reserveMemory(
            0, Ipc_getRegion0ReservedSize());

    /* must reserve memory for GateMP before SharedRegion_start() */
    gateMPSharedAddr = ti_sdo_ipc_SharedRegion_reserveMemory(0,
            ti_sdo_ipc_GateMP_getRegion0ReservedSize());

    /* Init params for default gate (must match those in GateMP_start()) */
    GateMP_Params_init(&gateMPParams);
    gateMPParams.localProtect  = GateMP_LocalProtect_TASKLET;

    if (ti_sdo_utils_MultiProc_numProcessors > 1) {
        gateMPParams.remoteProtect = GateMP_RemoteProtect_SYSTEM;
    }
    else {
        gateMPParams.remoteProtect = GateMP_RemoteProtect_NONE;
    }

    /* reserve memory for default gate before SharedRegion_start() */
    ti_sdo_ipc_SharedRegion_reserveMemory(0, GateMP_sharedMemReq(&gateMPParams));

    /* clear the reserved memory */
    ti_sdo_ipc_SharedRegion_clearReservedMemory();

    /* Set shared addresses */
    Ipc_module->ipcSharedAddr = ipcSharedAddr;
    Ipc_module->gateMPSharedAddr = gateMPSharedAddr;

    /* create default GateMP, must be called before SharedRegion start */
    status = ti_sdo_ipc_GateMP_start(Ipc_module->gateMPSharedAddr);
    if (status < 0) {
        return (status);
    }

    /* create HeapMemMP in each SharedRegion */
    status = ti_sdo_ipc_SharedRegion_start();
    if (status < 0) {
        return (status);
    }

    /* Call attach for all procs if procSync is ALL */
    if (ti_sdo_ipc_Ipc_procSync == ti_sdo_ipc_Ipc_ProcSync_ALL) {
        /* Must attach to owner first to get default GateMP and HeapMemMP */
        if (MultiProc_self() != entry.ownerProcId) {
            do {
                status = Ipc_attach(entry.ownerProcId);
            } while (status == Ipc_E_NOTREADY);

            if (status < 0) {
                /* Ipc_attach failed. Get out of Ipc_start */
                return (status);
            }
        }

        /* Loop to attach to all other processors in cluster */
        for (i = 0; i < ti_sdo_utils_MultiProc_numProcsInCluster; i++, baseId++) {
            if ((baseId == MultiProc_self()) || (baseId == entry.ownerProcId)) {
                continue;
            }

            /* Skip the processor if there are no interrupt lines to it */
            if (Notify_numIntLines(baseId) == 0) {
                continue;
            }

            /* call Ipc_attach for every remote processor */
            do {
                status = Ipc_attach(baseId);
            } while (status == Ipc_E_NOTREADY);

            if (status < 0) {
                /* Ipc_attach failed. Get out of Ipc_start */
                return (status);
            }
        }
    }

    return (status);
}

/*
 *  ======== Ipc_stop ========
 */
Int Ipc_stop()
{
    Int status;

    /* clear local module state */
    Ipc_module->gateMPSharedAddr = NULL;
    Ipc_module->ipcSharedAddr = NULL;

    /* reset Shared Region 0 reservedSize and heap handle */
    ti_sdo_ipc_SharedRegion_resetInternalFields(0);

    /* delete any HeapMemMP created by owner of SR0 */
    status = ti_sdo_ipc_SharedRegion_stop();
    if (status < 0) {
        return (status);
    }

    /* delete default GateMP created by owner of SR0 */
    status = ti_sdo_ipc_GateMP_stop();
    if (status < 0) {
        return (status);
    }

    /* set sr0MemorySetup back to 0 if needed by Host */
    if ((ti_sdo_ipc_Ipc_generateSlaveDataForHost) &&
        !(ti_sdo_ipc_Ipc_sr0MemorySetup)) {
        Ipc_sr0MemorySetup = 0;
        Cache_wbInv(&Ipc_sr0MemorySetup,
              sizeof(Ipc_sr0MemorySetup),
              Cache_Type_ALL,
              TRUE);
    }

    return (Ipc_S_SUCCESS);
}

/*
 *  ======== Ipc_writeConfig ========
 */
Int Ipc_writeConfig(UInt16 remoteProcId, UInt32 tag, Ptr cfg, SizeT size)
{
    Int status = Ipc_S_SUCCESS;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    SharedRegion_SRPtr curSRPtr, *prevSRPtr;
    ti_sdo_ipc_Ipc_ConfigEntry *entry;
    Error_Block eb;
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);

    /* Assert that the remoteProc in our cluster */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    Error_init(&eb);

    if (cfg == NULL) {
        status = Ipc_E_FAIL;

        /* get head of local config list and set prevSRPtr to it */
        prevSRPtr = (Ipc_module->procEntry[clusterId].localConfigList);

        /*
         *  When cfg is NULL, the last memory allocated from a previous
         *  Ipc_writeConfig call with the same remoteProcId, tag, and size
         *  is freed.
         */
        curSRPtr = *prevSRPtr;

        /* loop through list of config entries until matching entry is found */
        while (curSRPtr != ti_sdo_ipc_SharedRegion_INVALIDSRPTR) {
            /* convert Ptr associated with curSRPtr */
            entry = (ti_sdo_ipc_Ipc_ConfigEntry *)
                    (SharedRegion_getPtr(curSRPtr));

            /* make sure entry matches remoteProcId, tag, and size */
            if ((entry->remoteProcId == remoteProcId) &&
                (entry->tag == tag) &&
                (entry->size == size)) {
                /* Update the 'prev' next ptr */
                *prevSRPtr = (SharedRegion_SRPtr)entry->next;

                /* writeback the 'prev' ptr */
                if (cacheEnabled) {
                    Cache_wb(prevSRPtr,
                        sizeof(ti_sdo_ipc_Ipc_ConfigEntry),
                        Cache_Type_ALL,
                        FALSE);
                }

                /* free entry's memory back to shared heap */
                Memory_free(SharedRegion_getHeap(0),
                    entry,
                    size + sizeof(ti_sdo_ipc_Ipc_ConfigEntry));

                /* set the status to success */
                status = Ipc_S_SUCCESS;
                break;
            }

            /* set the 'prev' to the 'cur' SRPtr */
            prevSRPtr = (SharedRegion_SRPtr *)(&entry->next);

            /* point to next config entry */
            curSRPtr = (SharedRegion_SRPtr)entry->next;
        }

        /* return that status */
        return (status);
    }

    /* Allocate memory from the shared heap (System Heap) */
    entry = Memory_alloc(SharedRegion_getHeap(0),
                         size + sizeof(ti_sdo_ipc_Ipc_ConfigEntry),
                         SharedRegion_getCacheLineSize(0),
                         &eb);

    if (entry == NULL) {
        return (Ipc_E_FAIL);
    }

    /* set the entry */
    entry->remoteProcId = remoteProcId;
    entry->localProcId = MultiProc_self();
    entry->tag = tag;
    entry->size = size;
    memcpy((Ptr)((UInt32)entry + sizeof(ti_sdo_ipc_Ipc_ConfigEntry)), cfg,
                  size);

    /* point the entry's next to the first entry in the list */
    entry->next = *Ipc_module->procEntry[clusterId].localConfigList;

    /* first write-back the entry if cache is enabled */
    if (cacheEnabled) {
        Cache_wb(entry, size + sizeof(ti_sdo_ipc_Ipc_ConfigEntry),
                 Cache_Type_ALL,
                 FALSE);
    }

    /* set the entry as the new first in the list */
    *Ipc_module->procEntry[clusterId].localConfigList =
        SharedRegion_getSRPtr(entry, 0);

    /* write-back the config list */
    if (cacheEnabled) {
        Cache_wb(Ipc_module->procEntry[clusterId].localConfigList,
                 SharedRegion_getCacheLineSize(0),
                 Cache_Type_ALL,
                 FALSE);
    }

    return (status);
}

/*
 *************************************************************************
 *                       Module Functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_Ipc_dummy ========
 */
Void ti_sdo_ipc_Ipc_dummy()
{
}

/*
 *  ======== ti_sdo_ipc_Ipc_getEntry ========
 */
Void ti_sdo_ipc_Ipc_getEntry(ti_sdo_ipc_Ipc_Entry *entry)
{
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(entry->remoteProcId);

    /* Assert remoteProcId is in our cluster */
    Assert_isTrue(clusterId < ti_sdo_utils_MultiProc_numProcsInCluster,
                  ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    /* Get the setupNotify flag */
    entry->setupNotify =
        Ipc_module->procEntry[clusterId].entry.setupNotify;

    /* Get the setupMessageQ flag */
    entry->setupMessageQ =
        Ipc_module->procEntry[clusterId].entry.setupMessageQ;
}

/*
 *  ======== ti_sdo_ipc_Ipc_setEntry ========
 */
Void ti_sdo_ipc_Ipc_setEntry(ti_sdo_ipc_Ipc_Entry *entry)
{
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(entry->remoteProcId);

    /* Set the setupNotify flag */
    Ipc_module->procEntry[clusterId].entry.setupNotify =
        entry->setupNotify;

    /* Set the setupMessageQ flag */
    Ipc_module->procEntry[clusterId].entry.setupMessageQ =
        entry->setupMessageQ;
}

/*
 *************************************************************************
 *                       Internal Functions
 *************************************************************************
 */

/*
 *  ======== ti_sdo_ipc_Ipc_getMasterAddr ========
 */
Ptr ti_sdo_ipc_Ipc_getMasterAddr(UInt16 remoteProcId, Ptr sharedAddr)
{
    Int slot;
    UInt16 masterId;
    volatile ti_sdo_ipc_Ipc_Reserved *master;
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();

    /* determine the master's procId and slot */
    if (MultiProc_self() < remoteProcId) {
        masterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
        slot = ti_sdo_utils_MultiProc_getClusterId(MultiProc_self());
    }
    else {
        masterId = ti_sdo_utils_MultiProc_getClusterId(MultiProc_self());
        slot = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    }

    /* determine the reserve address for master between self and remote */
    master = (ti_sdo_ipc_Ipc_Reserved *)((UInt32)sharedAddr +
             ((masterId * reservedSize) +
             (slot * sizeof(ti_sdo_ipc_Ipc_Reserved))));

    return ((Ptr)master);
}

/*
 *  ======== ti_sdo_ipc_Ipc_getRegion0ReservedSize ========
 */
SizeT ti_sdo_ipc_Ipc_getRegion0ReservedSize(Void)
{
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();

    /* Calculate the total amount to reserve */
    reservedSize = reservedSize * ti_sdo_utils_MultiProc_numProcsInCluster;

    return (reservedSize);
}

/*
 *  ======== ti_sdo_ipc_Ipc_getSlaveAddr ========
 */
Ptr ti_sdo_ipc_Ipc_getSlaveAddr(UInt16 remoteProcId, Ptr sharedAddr)
{
    Int slot;
    UInt16 slaveId;
    volatile ti_sdo_ipc_Ipc_Reserved *slave;
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();

    /* determine the slave's procId and slot */
    if (MultiProc_self() < remoteProcId) {
        slaveId = ti_sdo_utils_MultiProc_getClusterId(MultiProc_self());
        slot = ti_sdo_utils_MultiProc_getClusterId(remoteProcId) - 1;
    }
    else {
        slaveId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
        slot = ti_sdo_utils_MultiProc_getClusterId(MultiProc_self()) - 1;
    }

    /* determine the reserve address for slave between self and remote */
    slave = (ti_sdo_ipc_Ipc_Reserved *)((UInt32)sharedAddr +
            ((slaveId * reservedSize) +
            (slot * sizeof(ti_sdo_ipc_Ipc_Reserved))));

    return ((Ptr)slave);
}

/*
 *  ======== ti_sdo_ipc_Ipc_procSyncStart ========
 *  The owner of SharedRegion 0 writes to its reserve memory address
 *  in region 0 to let the other processors know it has started.
 *  It then spins until the other processors start.
 *  The other processors write their reserve memory address in
 *  region 0 to let the owner processor know they've started.
 *  The other processors then spin until the owner processor writes
 *  to let them know that its finished the process of synchronization
 *  before continuing.
 */
Int ti_sdo_ipc_Ipc_procSyncStart(UInt16 remoteProcId, Ptr sharedAddr)
{
    volatile ti_sdo_ipc_Ipc_Reserved *self, *remote;
    ti_sdo_ipc_Ipc_ProcEntry *ipc;
    UInt16 clusterId = ti_sdo_utils_MultiProc_getClusterId(remoteProcId);
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);

    /* don't do any synchronization if procSync is NONE */
    if (ti_sdo_ipc_Ipc_procSync == ti_sdo_ipc_Ipc_ProcSync_NONE) {
        return (Ipc_S_SUCCESS);
    }

    /* determine self and remote pointers */
    if (MultiProc_self() < remoteProcId) {
        self = Ipc_getSlaveAddr(remoteProcId, sharedAddr);
        remote = ti_sdo_ipc_Ipc_getMasterAddr(remoteProcId, sharedAddr);
    }
    else {
        self = ti_sdo_ipc_Ipc_getMasterAddr(remoteProcId, sharedAddr);
        remote = Ipc_getSlaveAddr(remoteProcId, sharedAddr);
    }

    /* construct the config list */
    ipc = &(Ipc_module->procEntry[clusterId]);

    ipc->localConfigList = (Ptr)&self->configListHead;
    ipc->remoteConfigList = (Ptr)&remote->configListHead;

    *ipc->localConfigList = ti_sdo_ipc_SharedRegion_INVALIDSRPTR;

    if (cacheEnabled) {
        Cache_wbInv(ipc->localConfigList, reservedSize, Cache_Type_ALL, TRUE);
    }

    if (MultiProc_self() < remoteProcId) {
        /* set my processor's reserved key to start */
        self->startedKey = ti_sdo_ipc_Ipc_PROCSYNCSTART;

        /* write back my processor's reserve key */
        if (cacheEnabled) {
            Cache_wbInv((Ptr)self, reservedSize, Cache_Type_ALL, TRUE);
        }

        /* wait for remote processor to start */
        if (cacheEnabled) {
            Cache_inv((Ptr)remote, reservedSize, Cache_Type_ALL, TRUE);
        }

        if (remote->startedKey != ti_sdo_ipc_Ipc_PROCSYNCSTART) {
            return (Ipc_E_NOTREADY);
        }
    }
    else {
        /*  wait for remote processor to start */
        if (cacheEnabled) {
            Cache_inv((Ptr)remote, reservedSize, Cache_Type_ALL, TRUE);
        }

        if ((self->startedKey != ti_sdo_ipc_Ipc_PROCSYNCSTART) &&
            (remote->startedKey != ti_sdo_ipc_Ipc_PROCSYNCSTART)) {
            return (Ipc_E_NOTREADY);
        }

        /* set my processor's reserved key to start */
        self->startedKey = ti_sdo_ipc_Ipc_PROCSYNCSTART;

        /* write my processor's reserve key back */
        if (cacheEnabled) {
            Cache_wbInv((Ptr)self, reservedSize, Cache_Type_ALL, TRUE);

            /* wait for remote processor to finish */
            Cache_inv((Ptr)remote, reservedSize, Cache_Type_ALL, TRUE);
        }

        if (remote->startedKey != ti_sdo_ipc_Ipc_PROCSYNCFINISH) {
            return (Ipc_E_NOTREADY);
        }
    }

    return (Ipc_S_SUCCESS);
}

/*
 *  ======== ti_sdo_ipc_Ipc_procSyncFinish ========
 *  Each processor writes its reserve memory address in SharedRegion 0
 *  to let the other processors know its finished the process of
 *  synchronization.
 */
Int ti_sdo_ipc_Ipc_procSyncFinish(UInt16 remoteProcId, Ptr sharedAddr)
{
    volatile ti_sdo_ipc_Ipc_Reserved *self, *remote;
    SizeT reservedSize = ti_sdo_ipc_Ipc_reservedSizePerProc();
    Bool cacheEnabled = SharedRegion_isCacheEnabled(0);

    /* don't do any synchronization if procSync is NONE */
    if (ti_sdo_ipc_Ipc_procSync == ti_sdo_ipc_Ipc_ProcSync_NONE) {
        return (Ipc_S_SUCCESS);
    }

    /* determine self and remote pointers */
    if (MultiProc_self() < remoteProcId) {
        self = Ipc_getSlaveAddr(remoteProcId, sharedAddr);
        remote = ti_sdo_ipc_Ipc_getMasterAddr(remoteProcId, sharedAddr);
    }
    else {
        self = ti_sdo_ipc_Ipc_getMasterAddr(remoteProcId, sharedAddr);
        remote = Ipc_getSlaveAddr(remoteProcId, sharedAddr);
    }

    /* set my processor's reserved key to finish */
    self->startedKey = ti_sdo_ipc_Ipc_PROCSYNCFINISH;

    /* write back my processor's reserve key */
    if (cacheEnabled) {
        Cache_wbInv((Ptr)self, reservedSize, Cache_Type_ALL, TRUE);
    }

    /* if slave processor, wait for remote to finish sync */
    if (MultiProc_self() < remoteProcId) {

        /* wait for remote processor to finish */
        while (remote->startedKey != ti_sdo_ipc_Ipc_PROCSYNCFINISH &&
                remote->startedKey != ti_sdo_ipc_Ipc_PROCSYNCDETACH) {

            if (cacheEnabled) {
                Cache_inv((Ptr)remote, reservedSize, Cache_Type_ALL, TRUE);
            }
        }
    }

    return (Ipc_S_SUCCESS);
}

/*
 *  ======== ti_sdo_ipc_Ipc_reservedSizePerProc ========
 */
SizeT ti_sdo_ipc_Ipc_reservedSizePerProc(Void)
{
    SizeT reservedSize = sizeof(ti_sdo_ipc_Ipc_Reserved) *
            ti_sdo_utils_MultiProc_numProcsInCluster;
    SizeT cacheLineSize = SharedRegion_getCacheLineSize(0);

    /* Calculate amount to reserve per processor */
    if (cacheLineSize > reservedSize) {
        /* Use cacheLineSize if larger than reservedSize */
        reservedSize = cacheLineSize;
    }
    else {
        /* Round reservedSize to cacheLineSize */
        reservedSize = _Ipc_roundup(reservedSize, cacheLineSize);
    }

    return (reservedSize);
}
