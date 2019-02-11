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
 *  ======== dskt2free.c ========
 *  DSKT2 API to free the memory used by an XDAIS algorithm instance, and then
 *  delete the instance.
 *
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_dskt2_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/Registry.h>
#include <ti/sysbios/gates/GateMutexPri.h>

#include <ti/xdais/ialg.h>

#include <xdc/runtime/Memory.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include "dskt2.h"
#include "_dskt2.h"

#include "dskt2_lock.h"

static Void _DSKT2_exit();

extern __FAR__ Registry_Desc ti_sdo_fc_dskt2_desc;

extern __FAR__ IGateProvider_Handle _DSKT2_gate;
extern __FAR__ Int _DSKT2_algReferenceCount;

extern __FAR__ Bool ti_sdo_fc_useDNUM;

extern __FAR__ _DSKT2_ScratchBufferDesc *_DSKT2_scratchDescTbl[DSKT2_NUM_SHAREDHEAPS];
extern __FAR__ _DSKT2_MemTabListNode *_DSKT2_memTabList;
extern __FAR__ IALG_Handle *_DSKT2_activeAlg;
extern __FAR__ IALG_Handle *_DSKT2_lastActiveAlg;
extern __FAR__ Int *_DSKT2_scratchShareRefCount;


#ifdef xdc_target__isaCompatible_64P
extern __FAR__ Bool ti_sdo_fc_dskt2_DSKT2_convertAddr;
extern __cregister volatile Uns DNUM;
static inline Uns MC_ADDR_GLOB_TO_LOC(Uns glob_addr);
#else
#define MC_ADDR_GLOB_TO_LOC(addr) (addr)
#endif


/*
 *  ======== DSKT2_freeAlg ========
 */
Bool DSKT2_freeAlg(Int scratchMutexId, IALG_Handle alg)
{
    Int         numRecs;
    Int         memTabSize;
    IALG_MemRec *memTab;
    xdc_runtime_IHeap_Handle extHeap;
    Int         status = TRUE;
    IArg        key;
    Int         i = 0;
    Int         scratchId;

    Log_print2(Diags_ENTRY, "[+E] DSKT2_freeAlg> Enter "
            "(scratchMutexId=%d, alg=0x%x)", (IArg)scratchMutexId, (IArg)alg);

#ifndef DSKT2_DISABLELAZYD
    /*
     * If alg instance is currently active remove info from active table.
     * (No need to actually 'deactivate' the instance.)
     *
     * We need to do this early so pre-empting tasks know not to deactivate
     * alg.
     */
    if ((scratchMutexId >= 0) && (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS)) {
        key = IGateProvider_enter(_DSKT2_gate);

        if (_DSKT2_activeAlg[scratchMutexId] == alg) {
            _DSKT2_activeAlg[scratchMutexId] = NULL;
        }
        else if (_DSKT2_lastActiveAlg[scratchMutexId] == alg) {
            _DSKT2_lastActiveAlg[scratchMutexId] = NULL;
        }

        IGateProvider_leave(_DSKT2_gate, key);
    }
#endif

    /*
     *  Use the memTab stored during create phase to deallocate instance
     *  memory, as well as the memTab structure itself.
     *  No need to call alg's algFree function anymore.
     */
    Log_print0(Diags_USER2, "[+2] DSKT2_freeAlg> Dequeue alg information");

    memTab =_DSKT2_dequeueMemTab(_DSKT2_heap, alg, &memTabSize,
            &numRecs, &extHeap, &scratchId);

    if (memTab == NULL) {
        Log_print0(Diags_USER7, "[+7] DSKT2_freeAlg> Illegal Memory");

        /* return without freeing any memory */
        return (FALSE);
    }

    Assert_isTrue(scratchId == scratchMutexId, (Assert_Id)NULL);

    Log_print4(Diags_USER2, "[+2] DSKT2_freeAlg> Dequeued alg information, "
            "memTab 0x%x memTabSize %d, numRecs %d, extHeap 0x%x",
            (IArg)memTab, (IArg)memTabSize, (IArg)numRecs, (IArg)extHeap);

    for(i = 0; i < numRecs; i++) {

        /* TODO:- Plaform support should do this */
        if (ti_sdo_fc_useDNUM) {
            memTab[i].base = (void *)MC_ADDR_GLOB_TO_LOC((Uns)memTab[i].base);
        }
    }

    /*
     * free algorithm's memory, using the scratch-group Id for determining
     * shared scratch heap.
     */

    Log_print0(Diags_USER2,"[+2] DSKT2_freeAlg> Free instance memory");

    status = _DSKT2_freeInstanceMemory(scratchMutexId, memTab, numRecs,
            extHeap);

    /* done with stashed away memTab, free it */
    Memory_free(_DSKT2_heap, memTab, memTabSize);


        /* Enter critical section */
    key = IGateProvider_enter(_DSKT2_gate);
    _DSKT2_algReferenceCount--;
    IGateProvider_leave(_DSKT2_gate, key);

    if (0 == _DSKT2_algReferenceCount) {
        _DSKT2_exit();
    }

    Log_print0(Diags_EXIT, "[+X] DSKT2_freeAlg> Exit");

    return (status);
}

static Void _DSKT2_exit()
{
    Int           i;
    GateMutexPri_Handle h;

    if (_DSKT2_initialized) {

        Log_print0(Diags_ENTRY, "[+E] _DSKT2_exit> Enter");

        /* Free allocated DSKT2 internal data
         * structures to the _DSKT2 heap segment
         */
        Memory_free(_DSKT2_heap, _DSKT2_activeAlg,
                sizeof(IALG_Handle) * DSKT2_NUM_SCRATCH_GROUPS);

        Memory_free(_DSKT2_heap, _DSKT2_lastActiveAlg, sizeof(IALG_Handle) *
                DSKT2_NUM_SCRATCH_GROUPS);

        Memory_free(_DSKT2_heap, _DSKT2_scratchShareRefCount, sizeof(Int) *
                DSKT2_NUM_SCRATCH_GROUPS);

        /*
         * Free scratch-group heap descriptors
         */
        for (i = 0; i < DSKT2_NUM_SHAREDHEAPS; i++) {

            Memory_free(_DSKT2_heap, _DSKT2_scratchDescTbl[i],
                    sizeof(_DSKT2_ScratchBufferDesc)
                    * DSKT2_NUM_SCRATCH_GROUPS);
        }

        DSKT2_exitLocks();

        /* Everything has been created */
        _DSKT2_initialized = 0;

        if (_DSKT2_gate != NULL) {
            h = GateMutexPri_Handle_downCast(_DSKT2_gate);
            GateMutexPri_delete(&h);

            _DSKT2_gate= NULL;
        }

        FCSettings_exit();

    }
    else {
        Log_print0(Diags_ENTRY, "[+E] _DSKT2_exit> Enter");
    }


    Log_print0(Diags_EXIT, "[+X] _DSKT2_exit> Exit");
}

#ifdef xdc_target__isaCompatible_64P
static inline Uns MC_ADDR_GLOB_TO_LOC(Uns glob_addr)
{

   Uns tmp = glob_addr;

    /* If conversion flag is set to TRUE, some addresses on this core were
       converted to global, so convert them back */
    if ((ti_sdo_fc_dskt2_DSKT2_convertAddr) &&
            /* This is a global address on the same core */
            ((tmp >> 24) == ((1 << 4)|DNUM))) {
        return (tmp & 0x00FFFFFF);
    }
    else {
        return glob_addr;
    }
}
#endif
