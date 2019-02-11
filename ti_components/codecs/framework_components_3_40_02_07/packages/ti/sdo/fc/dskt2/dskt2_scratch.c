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
 *  ======== dskt2_scratch.c ========
 *  DSKT2 scratch sharing support functions
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

#include <ti/xdais/ialg.h>

#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <string.h>

#include <ti/sysbios/gates/GateMutexPri.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include "_dskt2.h"
#include <ti/sdo/fc/global/gt_dais.h>

#include "dskt2.h"
#include "dskt2_permute.h"

#include "dskt2_lock.h"
#include "dskt2_mem.h"


#define USESCRATCHOPT 1  /* Set to 1 to optimize scratch usage */

/*
 *  Set to 1 to allow allocation scratch heaps in DSKT2_allocScratch(), if
 *  they have not yet been allocated.
 */
#define ALLOCSCRATCH 1

/*
 *  ALLOC_ORIGSIZE = 1:
 *    if scratch heap has not been allocated yet when DSKT2_allocScratch()
 *    is called, a scratch heap of size desc->origSize will be allocated.
 *
 *  ALLOC_ORIGSIZE = 0:
 *    if scratch heap has not been allocated yet when DSKT2_allocScratch()
 *    is called, a scratch heap of size of the requested scratch memory
 *    will be allocated.
 */
#define ALLOC_ORIGSIZE 0

#define _DSKT2_NUM_INTERNAL_HEAPS 6
#define _DSKT2_MAX(x,y) ( ( (x) > (y) ) ? (x) : (y) )
#define _DSKT2_MIN(x,y) ( ( (x) < (y) ) ? (x) : (y) )

/*
 *  Initializes DSKT2 memory heaps. For programs using RTSC configuration,
 *  this is auto-generated. Otherwise, it will be linked in from the dskt2
 *  library.
 */
extern Void DSKT2_cfgInit();

/*
 * Global private module declarations.
 */
__FAR__ UInt DSKT2_allowExternalScratch;
__FAR__ _DSKT2_ScratchBufferDesc *_DSKT2_scratchDescTbl[DSKT2_NUM_SHAREDHEAPS];
__FAR__ _DSKT2_MemTabListNode *_DSKT2_memTabList = NULL;
__FAR__ IALG_Handle *_DSKT2_activeAlg = NULL;
__FAR__ IALG_Handle *_DSKT2_lastActiveAlg = NULL;
__FAR__ Int *_DSKT2_scratchShareRefCount = NULL;

__FAR__ _DSKT2_CreateCallbackFxn _DSKT2_createCallbackFxn = NULL;

__FAR__ UInt _DSKT2_NumYielded = 0;
__FAR__ UInt _DSKT2_yielded = 0;
__FAR__ Int  _DSKT2_initialized = 0;

/*
 * Private local functions
 */
static Bool _DSKT2_freeAllocatedMemory(Int scratchMutexId, IALG_MemRec *memTab,
        Int failedIndex, xdc_runtime_IHeap_Handle extHeap);
static Void _DSKT2_incrScratchReferenceCount(Int scratchMutexId);
static Void _DSKT2_decrScratchReferenceCount(Int scratchMutexId);
static Int  _DSKT2_exitScratch(Int scratchMutexId);
Bool _DSKT2_useSharedScratch(_DSKT2_ScratchBufferDesc *scrBuffDesc,
    IALG_MemRec *memTab);
static Bool _DSKT2_isSharedScratchAddr(Int scratchMutexId, Void *base);
static Void _DSKT2_initializeAndUseSharedScratch(Int scratchMutexId,
        IALG_MemRec *memTab, Int numRecs);
static Bool _DSKT2_allocateFromSharedScratch(Int scratchMutexId,
    IALG_MemRec *memTab);
static Bool _DSKT2_allocateInDesignatedSpace(IALG_MemRec memTab[], Int i,
    IALG_MemSpace ialgSpace, xdc_runtime_IHeap_Handle heap);
static Bool _DSKT2_allocateInInternal(IALG_MemRec memTab[], Int i,
        xdc_runtime_IHeap_Handle extHeap);
static Bool _DSKT2_usesInternalScratch(IALG_MemRec *memTab, Int numRecs);
static UInt32 _DSKT2_getScratchUsed(IALG_Handle alg, Int mutexId, Int heapId);

static Void *myMalloc(xdc_runtime_IHeap_Handle heap, SizeT size, SizeT align);

__FAR__ static Int _numAlgs = 0;


Bool DSKT2_allocScratch(IALG_Handle alg,Int mutexId, IALG_MemRec *memTab,
        Int numRecs);

Void DSKT2_freeScratch(Int mutexId, Void *addr, UInt size);

Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);

Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

__FAR__ IGateProvider_Handle _DSKT2_gate = NULL;

__FAR__ Registry_Desc ti_sdo_fc_dskt2_desc;


/*
 *  ======== _DSKT2_init ========
 */
Void _DSKT2_init()
{
    Int           i;
    IArg          key;
#ifndef xdc_runtime_Assert_DISABLE_ALL
    Registry_Result regResult;
#endif
    GateMutexPri_Handle h;
    static int _regInit = 0;

    if (!_DSKT2_initialized) {
        /*
         *  Register the module name for logging only once. Do this before any
         *  Log functions are called.
         */
        if (!(_regInit)) {
#ifndef xdc_runtime_Assert_DISABLE_ALL
            regResult =
#endif
                    Registry_addModule(&ti_sdo_fc_dskt2_desc, DSKT2_MODNAME);

            Assert_isTrue(regResult == Registry_SUCCESS, (Assert_Id)NULL);
            _regInit = 1;
        }

        /* Set diags mask to FC default */
        FCSettings_init();
        FCSettings_setDiags(DSKT2_MODNAME);

        /* Initialize DSKT2 memory segments */
        DSKT2_cfgInit();

        Log_print0(Diags_ENTRY, "[+E] _DSKT2_init> Enter");

        /*
         *  NOTE: There is the possibility that two threads could
         *  create the gate simultaneously.
         */
        if (_DSKT2_gate == NULL) {
            h = GateMutexPri_create(NULL, NULL);
            _DSKT2_gate = GateMutexPri_Handle_upCast(h);

            if (_DSKT2_gate == NULL) {
                Log_print0(Diags_USER7, "[+7] _DSKT2_init> Failed to create "
                        "gate");
                _DSKT2_throwMPUMemException("_DSKT2_gate");
            }
        }

        /* Enter critical section */
        key = IGateProvider_enter(_DSKT2_gate);

        if (_DSKT2_initialized == 1) {
            /*
             *  Another thread _DSKT2_initialized while we were waiting to enter
             *  the gate.
             */
            IGateProvider_leave(_DSKT2_gate, key);
            return;
        }

        /*
         *  Initialize the variable DSKT2_allowExternalScratch to the
         *  constant defined by DSKT2.xdc, _DSKT2_ALLOW_EXTERNAL_SCRATCH.
         *  The reason for not just using the constant is that we can write
         *  tests that change the value of DSKT2_allowExternalScratch,
         *  for testing different configurations.
         */
        DSKT2_allowExternalScratch = _DSKT2_ALLOW_EXTERNAL_SCRATCH;

        /* Dynamically allocate and initialize DSKT2 internal data
         * structures in the _DSKT2 heap segment
         */
        if ((_DSKT2_activeAlg = myMalloc(_DSKT2_heap,
                     sizeof(IALG_Handle) * DSKT2_NUM_SCRATCH_GROUPS, 0))
                == NULL){

            _DSKT2_throwMPUMemException("_DSKT2_activeAlg");
        }
        if ((_DSKT2_lastActiveAlg = myMalloc(_DSKT2_heap, sizeof(IALG_Handle) *
                     DSKT2_NUM_SCRATCH_GROUPS, 0)) == NULL) {

            _DSKT2_throwMPUMemException("_DSKT2_lastActiveAlg");
        }
        if ((_DSKT2_scratchShareRefCount = myMalloc(_DSKT2_heap, sizeof(Int) *
                     DSKT2_NUM_SCRATCH_GROUPS, 0)) == NULL) {

            _DSKT2_throwMPUMemException("_DSKT2_scratchShareRefCount");
        }

        /*
         * Allocate scratch-group heap descriptors
         */
        for (i = 0; i < DSKT2_NUM_SHAREDHEAPS; i++) {

            if ((_DSKT2_scratchDescTbl[i] = (_DSKT2_ScratchBufferDesc *)
                        myMalloc(_DSKT2_heap, sizeof(_DSKT2_ScratchBufferDesc)
                                * DSKT2_NUM_SCRATCH_GROUPS, 0)) == NULL) {

                _DSKT2_throwMPUMemException("_DSKT2_scratchDescTbl");
            }
        }

        /*
         * Initialize the scratch heap sizes for SARAM and DARAM for each
         * scratch-group using data obtained from DSKT2 configuration
         */
        for (i = 0; i < DSKT2_NUM_SCRATCH_GROUPS; i++) {
            _DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][i].origSize =
                _DSKT2_DARAM_SCRATCH_SIZES[i];
            _DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][i].origSize =
                _DSKT2_SARAM_SCRATCH_SIZES[i];
        }

        DSKT2_initLocks();

        /* Everything has been created */
        _DSKT2_initialized = 1;

        IGateProvider_leave(_DSKT2_gate, key);
    }
    else {
        Log_print0(Diags_ENTRY, "[+E] _DSKT2_init> Enter");
    }


    Log_print0(Diags_EXIT, "[+X] _DSKT2_init> Exit");
}

/*
 *  ======== DSKT2_throwMemException ========
 */
Void _DSKT2_throwMPUMemException(Char *msg)
{
    System_printf("** MPU Exception <can't allocate: %s> **\n", msg);
    System_abort("Aborting...\n");
}

/*
 *  ======== _DSKT2_assignInstanceMemory ========
 *
 * Allocates memory requested by the algorithm from configured IALG Memory
 * Space Heaps. For "scratch" memory requests, allocation is from a shared
 * scratch buffer for all algorithm instances belonging to the same scratch
 * group (whenever possible).
 *
 * TODO: Should be ok to protect this call with IGateProvider_enter(). Heaps
 * should have their own gates for protection (not the system gate), so it
 * should be ok to call Memory_calloc() inside of the DSKT2 gate. (The
 * comment below needs to be changed).
 *
 * NOTE on RE-ENTRANCY:

 * Since MEM_calloc cannot be used within a TSK_disable'd context
 * mutual exclusion needs to be enforced by the application framework
 * when executing this function. All algorithm instances created using
 * the same scratchMutexId must be guaranteed by the
 * framework/application to run mutually exclusively.  This means, we
 * are assuming create phase of XDAIS Socket Nodes at the same node
 * 'priority' cannot be scheduled concurrently.
 */
Bool _DSKT2_assignInstanceMemory(Int scratchMutexId, IALG_MemRec *memTab,
    Int numRecs, xdc_runtime_IHeap_Handle extHeap)
{
    Int i;
    Int failedIndex = 0;
    Bool succeeded = TRUE;

    Log_print3(Diags_ENTRY, "[+E] _DSKT2_assignInstanceMemory>"
            " Enter (scratchId=%d, numRecs=%d, extHeap=0x%x)",
            (IArg)scratchMutexId, (IArg)numRecs, (IArg)extHeap);

    if ( (scratchMutexId >= 0) &&
         (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS) &&
         _DSKT2_usesInternalScratch(memTab, numRecs) ) {

        Log_print1(Diags_USER2,
                "[+2] _DSKT2_assignInstanceMemory> Alg requires some Internal "
                "Scratch in group %d", (IArg)scratchMutexId);

        /*
         * If algo requests any internal scratch memory:
         * Prepare shared scratch area for use by current scratchMutexId
         */
        Log_print0(Diags_USER2,
                "[+2] _DSKT2_assignInstanceMemory> Allocate as much as possible in "
                "the memory space requested");

        _DSKT2_initializeAndUseSharedScratch(scratchMutexId, memTab, numRecs);
    }

    for (i = 0; i < numRecs; i++) {

        /* skip allocation if this memTab rec has been pre-allocated from
         * internal shared scratch
         */
        if ((memTab[i].attrs == IALG_SCRATCH) &&
                !(IALG_isOffChip(memTab[i].space)) && /* not requested as
                                                       * external scratch */
                (scratchMutexId >= 0) &&
                (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS) &&
                (_DSKT2_isSharedScratchAddr(scratchMutexId, memTab[i].base))) {
             Log_print3(Diags_USER2,
                     "[+2] _DSKT2_assignInstanceMemory> memTab[%d] already"
                     " allocated from Internal Scratch. Addr=0x%x, Attrs=%s",
                     (IArg)i, (IArg)(memTab[i].base),
                     (IArg)(gt_MemAttrs(memTab[i].attrs)));

            continue;
        }

        /*
         * If the requested buffer, 'i', is of "Internal Scratch" type apply
         * scratch sharing policy.
         */
        if ((memTab[i].attrs == IALG_SCRATCH) &&
                (scratchMutexId >= 0) &&
                (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS) &&
                (!(IALG_isOffChip(memTab[i].space))) ) {

            int usesDaram0Heap = 0;
            int usesSaram0Heap = 0;

            switch (memTab[i].space) {
                case IALG_DARAM1:
                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_DARAM1", (IArg)i);
                /* Fall through to next case */

                case IALG_DARAM2:
                    usesDaram0Heap = (_DSKT2_spaceToSeg(memTab[i].space)
                        == _DSKT2_spaceToSeg(IALG_DARAM0));

                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_DARAM2", (IArg)i);

                /* Fall through to next case */

                case IALG_SARAM1:
                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_SARAM1", (IArg)i);

                /* Fall through to next case */

                case IALG_SARAM2:
                    usesSaram0Heap = (_DSKT2_spaceToSeg(memTab[i].space)
                        == _DSKT2_spaceToSeg(IALG_SARAM0));

                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_SARAM2", (IArg)i);

                    /* If the requested SARAM (or DARAM) segment is mapped to
                     * the same MEM heap segment for SARAM0 (or DARAM0), then
                     * request is treated as SARAM0 (DARAM0). Otherwise it is
                     * a distinct segment and we try allocating as
                     * unshared scratch in the requested mem space.
                     * If allocation fails: we try  default 'sharing' policy
                     */
                    if (!usesSaram0Heap && !usesDaram0Heap) {

                        if (usesSaram0Heap) {
                            Log_print1(Diags_USER2,
                                    "[+2] _DSKT2_assignInstanceMemory> Requested "
                                    "memory is mapped to the same heap as "
                                    "IALG_SARAM0", (IArg)i);
                        }

                        if (usesDaram0Heap) {
                            Log_print1(Diags_USER2,
                                    "[+2] _DSKT2_assignInstanceMemory> Requested "
                                    "memory is mapped to the same heap as "
                                    "IALG_DARAM0", (IArg)i);
                        }

                        if (_DSKT2_allocateInDesignatedSpace(memTab, i,
                            memTab[i].space, extHeap)) {

                            Log_print3(Diags_USER2,
                                    "[+2] _DSKT2_assignInstanceMemory> memTab[%d]"
                                    " is allocated in persistent memory space:"
                                    " %s, Addr=0x%x",
                                    (IArg)i,
                                    (IArg)(gt_MemSpace(memTab[i].space)),
                                    (IArg)(memTab[i].base));

                            continue; /* succeeded */
                        }
                        else {
                            Log_print3(Diags_USER7,
                                    "[+7] _DSKT2_assignInstanceMemory> Allocation of"
                                    " persistent memory :%s for memTab[%d] "
                                    "size=0x%x failed",
                                    (IArg)(gt_MemSpace(memTab[i].space)),
                                    (IArg)i, (IArg)(memTab[i].size));
                        }
                    }

                /* Fall through to next case */

                case IALG_DARAM0:
                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_DARAM0", (IArg)i);
                /* Fall through to next case */


                case IALG_SARAM0:
                    Log_print1(Diags_USER2,
                            "[+2] _DSKT2_assignInstanceMemory> memTab[%d] requests "
                            "Internal Scratch of type IALG_DARAM0", (IArg)i);

                    /*
                     * Search for available shared scratch memory:
                     *    for IALG_DARAM0: first try DARAM then SARAM.
                     *    for IALG_SARAM0: first try SARAM then DARAM.
                     */
                    if (_DSKT2_allocateFromSharedScratch(scratchMutexId,
                            &memTab[i]) ) {

                        Log_print1(Diags_USER2,
                                "[+2] _DSKT2_assignInstanceMemory> memTab[%d] "
                                "allocated in shared scratch", (IArg)i);

                        continue; /* succeeded */

                    /*
                     * if unable to create in shared scratch area,
                     * try to allocate it in the requested heap without sharing
                     * before trying in "any" internal heap.
                     */
                    } else if (_DSKT2_allocateInDesignatedSpace(memTab, i,
                             memTab[i].space, extHeap)) {

                        Log_print3(Diags_USER2,
                                "[+2] _DSKT2_assignInstanceMemory> memTab[%d] "
                                "allocated in persistent memory in Internal "
                                "memory space:%s Addr=0x%x",
                                (IArg)i, (IArg)(gt_MemSpace(memTab[i].space)),
                                (IArg)(memTab[i].base));

                        continue; /* succeeded */

                    /*
                     * if unable to share existing scratch space, try to
                     * allocate as persistent buffer in Internal memory.
                     */
                    } else if (_DSKT2_allocateInInternal(memTab, i, extHeap)) {

                        Log_print3(Diags_USER2,
                                "[+2] _DSKT2_assignInstanceMemory> memTab[%d] "
                                "allocated in persistent memory in Internal "
                                "memory space:%s Addr = 0x%x",
                                (IArg)i, (IArg)(gt_MemSpace(memTab[i].space)),
                                (IArg)(memTab[i].base));

                        continue; /* succeeded */

                    } else if (DSKT2_allowExternalScratch) {
                        /*
                         * If configuration allows trying in External Memory
                         * try to allocate scratch as persistent in Ext Mem
                         */
                         if (_DSKT2_allocateInDesignatedSpace(memTab, i,
                                 IALG_ESDATA, extHeap)) {

                            Log_print3(Diags_USER2,
                                    "[+2] _DSKT2_assignInstanceMemory> memTab[%d] "
                                    "allocated in persistent memory in "
                                    "External memory space:%s Addr=0x%x",
                                    (IArg)i,
                                    (IArg)(gt_MemSpace(memTab[i].space)),
                                    (IArg)(memTab[i].base));

                             continue; /* succeeded */
                          }
                    }
                    /*  -- else --
                     * If configuration does not allow, creation fails here
                     * after not being able to share an existing scratch heap
                     * *and* not being able to allocate as non-shared
                     * (i.e. persistent internal scratch memory.
                     * (Fails without trying to allocate in External memory)
                     */

                /* Fall through to next case */

                default:  /* fail */

                    failedIndex = i;
                    succeeded = FALSE;

                    break;

            } /* end switch */

        } else {
            /*
             * Requested memory is not of type: "internal scratch".
             * Dynamically allocate it as Persistent memory.
             */

            /* First, try to allocate it in requested heap segment */
            if (_DSKT2_allocateInDesignatedSpace(memTab, i, memTab[i].space,
                        extHeap)

                    /* Next, try allocating it in ANY Internal heap */
                    || _DSKT2_allocateInInternal(memTab, i, extHeap)

                    /* Finally, try allocating it in External Memory Heap */
                    || _DSKT2_allocateInDesignatedSpace(memTab, i,
                            IALG_ESDATA, extHeap)){

                Log_print3(Diags_USER2,
                        "[+2] _DSKT2_assignInstanceMemory> memTab[%d] allocated in "
                        "persistent memory in Memory space:%s. Addr=0x%x",
                        (IArg)i, (IArg)(gt_MemSpace(memTab[i].space)),
                        (IArg)(memTab[i].base));

                continue;  /* succeeded */
            }
        }
        failedIndex = i;
        succeeded = FALSE;      /* return false on failure */

        break;
    }   /* for i ... */

    /* safe even if scratch is not in range, functions below check for range */
    if (!succeeded) {

        Log_print0(Diags_USER2,
                "[+2] _DSKT2_assignInstanceMemory> Memory could not be allocated");

        _DSKT2_freeAllocatedMemory(scratchMutexId, memTab, failedIndex,
                extHeap);
        _DSKT2_exitScratch(scratchMutexId);

        Log_print1(Diags_EXIT,
                "[+X] _DSKT2_assignInstanceMemory> Exit (returnVal=%d)",
                (IArg)succeeded);
        return (FALSE);
    }

    /* safe only if scratch group is in the range */
    if ( (scratchMutexId >= 0) &&
         (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS) &&
         _DSKT2_usesInternalScratch(memTab, numRecs)) {

        Log_print1(Diags_USER2,
                "[+2] _DSKT2_assignInstanceMemory> Increment scratch group %d`s "
                "reference count", (IArg)scratchMutexId);

        _DSKT2_incrScratchReferenceCount(scratchMutexId);
    }

    Log_print1(Diags_EXIT, "[+X] _DSKT2_assignInstanceMemory>"
            " Exit (returnVal=%d)", (IArg)succeeded);

    return (TRUE);
}

/*
 *  ======== _DSKT2_freeAllocatedMemory ========
 */
Bool _DSKT2_freeAllocatedMemory(Int scratchMutexId, IALG_MemRec *memTab, Int n,
        xdc_runtime_IHeap_Handle extHeap)
{
    Int i;
    xdc_runtime_IHeap_Handle heap;

    Log_print3(Diags_ENTRY, "[+E] _DSKT2_freeAllocatedMemory>"
            " Enter (scratchMutexId=%d, number=%d, extHeap=0x%x)",
            (IArg)scratchMutexId, (IArg)n, (IArg)extHeap);

    /* free previous successful allocations for first 'n' buffers: */
    for (i = 0; i < n; i++) {

        if (!_DSKT2_isSharedScratchAddr(scratchMutexId, memTab[i].base)) {

            /*
             *  Any IALG memory space that maps to the same segment as
             *  IALG_ESDATA, uses the external memory heap segment.
             */
            heap = _DSKT2_spaceToSeg(memTab[i].space);
            if (heap == _DSKT2_spaceToSeg(IALG_ESDATA)) {
                heap = extHeap;
            }

            Memory_free(heap, memTab[i].base, memTab[i].size);
        }
    }

    Log_print1(Diags_EXIT,
            "[+X] _DSKT2_freeAllocatedMemory> Exit (returnVal=%d)", (IArg)TRUE);

    return (TRUE);
}

/*
 *  ======== _DSKT2_freeInstanceMemory ========
 */
Bool _DSKT2_freeInstanceMemory(Int scratchMutexId, IALG_MemRec *memTab,
    Int numRecs, xdc_runtime_IHeap_Handle extHeap)
{
    Int fStatus = TRUE;

    Log_print3(Diags_ENTRY, "[+E] _DSKT2_freeInstanceMemory>"
            " Enter (scratchMutexId=%d, numRecs=%d, extHeap=0x%x)",
            (IArg)scratchMutexId, (IArg)numRecs, (IArg)extHeap);

    /*
     * Free allocated algorithm instance memory.
     * Use the scratch-group Id for determining shared scratch heap.
     */
    if (_DSKT2_freeAllocatedMemory(scratchMutexId, memTab, numRecs, extHeap) == FALSE) {
        fStatus = FALSE;
    }

    if ((scratchMutexId >= 0) &&
         (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS) &&
         _DSKT2_usesInternalScratch(memTab, numRecs) ) {

        _DSKT2_decrScratchReferenceCount(scratchMutexId);
        _DSKT2_exitScratch(scratchMutexId);
    }

    Log_print1(Diags_EXIT, "[+X] _DSKT2_freeInstanceMemory> Exit (returnVal=%d)",
            (IArg)fStatus);

    return (fStatus);
}

/*
 *  ======== _DSKT2_usesInternalScratch ========
 */
Bool _DSKT2_usesInternalScratch(IALG_MemRec *memTab, Int numRecs)
{
     Int i;
     Bool flag = FALSE;

     Log_print1(Diags_ENTRY, "[+E] _DSKT2_usesInternalScratch> "
             "Enter (numRecs=%d)", (IArg)numRecs);

     /* check memTab to see if algorithm requests internal scratch memory */
     for (i=0; i<numRecs; i++) {

         if ((memTab[i].attrs == IALG_SCRATCH) &&
                 (!(IALG_isOffChip(memTab[i].space))) ) {
             flag = TRUE;

             break;
         }
     }

     Log_print1(Diags_EXIT, "[+X] _DSKT2_usesInternalScratch> "
             "Exit (returnVal=%d)", (IArg)flag);

     return (flag);
}

/*
 *  ======== _DSKT2_getReqScratchSize ========
 */
UInt _DSKT2_getReqScratchSize(Int ialgSpace, IALG_MemRec *memTab, Int numRecs)
{
    Int i;
    UInt32 sum = 0;

    Log_print2(Diags_ENTRY, "[+E] _DSKT2_getReqScratchSize> "
            "Enter (ialgSpace=%s, numRecs=%d)",
            (IArg)(gt_MemSpace((IALG_MemSpace)ialgSpace)), (IArg)numRecs);

    /*
     * Sum up the sizes of all scratch buffers requested by this algorithm
     * that are mapped to the given 'ialgSpace' memory segment.
     */
    for (i = 0; i < numRecs; i++) {

        if ((memTab[i].attrs == IALG_SCRATCH) && (_DSKT2_spaceToSeg(ialgSpace)
                == _DSKT2_spaceToSeg(memTab[i].space)) ) {
            /*
             * Note: This has the effect of combinining  scratch requests
             * that are mapped by the configuration to the same MEM heap, but
             * might otherwise be requested in a different IALG Memory Space.
             */

            sum += memTab[i].size + (memTab[i].alignment);
        }
    }

    Log_print1(Diags_EXIT, "[+X] _DSKT2_getReqScratchSize> Exit (size=0x%x)",
            (IArg)((sum > DSKT2_MAX_MEM_ALLOCATION_SIZE) ?
            DSKT2_MAX_MEM_ALLOCATION_SIZE : sum));

    /* ensure requested combined size is not greater than the MAX allowed */
    return ((sum > DSKT2_MAX_MEM_ALLOCATION_SIZE)?
        DSKT2_MAX_MEM_ALLOCATION_SIZE : sum );
}

/*
 *  ======== _DSKT2_getScratchRequestInfo  ========
 */
Void _DSKT2_getScratchRequestInfo(Int ialgSpace, IALG_MemRec *memTab,
    Int numRecs, UInt *sizeBestCase, UInt *sizeWorstCase,
    Int *scratchRequestIndexes, Int *numScratchRecs)
{
    Int i;

     Log_print2(Diags_ENTRY,
             "[+E] _DSKT2_getScratchRequestInfo> Enter (ialgSpace=%s, numRecs=%d)",
             (IArg)(gt_MemSpace((IALG_MemSpace)ialgSpace)), (IArg)numRecs);

    *sizeBestCase =  *sizeWorstCase = 0;
    *numScratchRecs = 0;
    /*
     * Sum up the sizes of all scratch buffers requested by this algorithm
     * that are mapped to the given 'ialgSpace' memory segment.
     */
    for (i = 0; i < numRecs; i++) {

        if ((memTab[i].attrs == IALG_SCRATCH) && (_DSKT2_spaceToSeg(ialgSpace)
                == _DSKT2_spaceToSeg(memTab[i].space)) ) {
            /*
             * Note: This has the effect of combinining  scratch requests
             * that are mapped by the configuration to the same MEM heap, but
             * might otherwise be requested in a different IALG Memory Space.
             */
            *sizeBestCase  += memTab[i].size ;
            *sizeWorstCase += memTab[i].size + (memTab[i].alignment);
            scratchRequestIndexes[*numScratchRecs] = i;
            (*numScratchRecs)++;

            /*
             * limit the number of requests to be considered for optimal
             * allocation to the maximum supported.
             */
            if (*numScratchRecs >= _DSKT2_PERMUTE_MAXSIZE) {
                break;
            }
        }
    }

    /* ensure  sizes not greater than the MAX allowed */
    *sizeBestCase  = _DSKT2_MIN(DSKT2_MAX_MEM_ALLOCATION_SIZE, *sizeBestCase);
    *sizeWorstCase = _DSKT2_MIN(DSKT2_MAX_MEM_ALLOCATION_SIZE, *sizeWorstCase);

     Log_print3(Diags_EXIT,
             "[+X] _DSKT2_getScratchRequestInfo>"
             " Exit (sizeBestCase=%d, sizeWorstCase=%d, numScratchRecs=%d)",
             (IArg)(*sizeBestCase), (IArg)(*sizeWorstCase),
             (IArg)(*numScratchRecs));
}

/*
 *  ======== _DSKT2_initializeAndUseSharedScratch ========
 *
 * Prepares shared scratch area for use by current scratchMutexId level:
 *   -  allocates shared scratch heaps if currently heap is unallocated
 *   -  initializes scratch descriptor ptrs to this node's creation use.
 */
Void _DSKT2_initializeAndUseSharedScratch(Int scrGrpId, IALG_MemRec *memTab,
    Int numRecs)
{
    _DSKT2_ScratchBufferDesc *scrBufDesc;
    Int heapId;
    Int ialgHeap;
    xdc_runtime_IHeap_Handle heap;
    UInt thisAlgScrRequestSizeBestCase;
    UInt thisAlgScrRequestSizeWorstCase;
    Bool createdNewSharedScratchBuffer;
    Memory_Stats stats;

    typedef struct _Locals {
        Int scratchRecIdList[_DSKT2_PERMUTE_MAXSIZE];
        Int optimalRecIdList[_DSKT2_PERMUTE_MAXSIZE];
        Int maximalRecIdList[_DSKT2_PERMUTE_MAXSIZE];
        Int *permutationList[_DSKT2_PERMUTE_MAXSIZE];
        _DSKT2_PERMUTE_Enumeration enumeration;
    } _Locals;

    _Locals *_locals;
    Int numScratchRecs;
    Int * **recIdList;
    Int i, id;
    UInt32 sharedAllocationSize;
    UInt32 netAllocationSize;
    UInt32 smallestTotalAllocationSize;
    UInt32 largestNetAllocationSize;
    UInt32 minSharedAllocationSize;

    Log_print2(Diags_ENTRY,
            "[+E] _DSKT2_initializeAndUseSharedScratch> Enter (scratchGroupId=%d, "
            "numRecs=%d)", (IArg)scrGrpId, (IArg)numRecs);

    Assert_isTrue((scrGrpId >= 0) && (scrGrpId < DSKT2_NUM_SCRATCH_GROUPS),
            (Assert_Id)NULL);

    /* allocate locals dynamically to reduce stack requirements */
    if ((_locals = myMalloc(_DSKT2_heap, sizeof(_Locals), 0)) == NULL) {
        Log_print0(Diags_EXIT,
                "[+X] _DSKT2_initializeAndUseSharedScratch> Exit");

        return;
    }

    for (heapId = 0; heapId < DSKT2_NUM_SHAREDHEAPS; heapId++) {
        scrBufDesc = &_DSKT2_scratchDescTbl[heapId][scrGrpId];
        ialgHeap = (heapId == 0) ? IALG_DARAM0: IALG_SARAM0;
        createdNewSharedScratchBuffer = FALSE;

        /*
         * If configuration maps both SARAM0 and DARAM0 heaps to the same
         * BIOS MEM segment than DSKT2 uses DARAM as the single primary shared
         * heap. Everything still works since SARAM scratch sharing policy
         * uses DARAM as its alternate heap.
         */
        if ((ialgHeap == IALG_SARAM0) &&  (_DSKT2_spaceToSeg(IALG_DARAM0)
                == _DSKT2_spaceToSeg(IALG_SARAM0)) ) {

            continue; /* skip SARAM0 when both heaps are mapped to same seg */
            /*
             * Note: this test is necessary, otherwise we would allocate twice
             * the shared scratch memory due to the 'getReqScratchSize'
             * call (below), which would return the same size for both
             * IALG_DARAM0 and IALG_SARAM0 heaps.
             */
        }

        /*
         * Get aggregate scratch requirement for the current algorithm
         * for this IALG memory space.
         *
         * 'thisAlgScrRequestSizeWorstCase' => each requested scratch buffer
         *          will be allocated with full padding to meet its alignment
         * 'thisAlgScrRequestSizeBestCase' => each requested scratch buffer
         *          will be allocated with no padding for alignment
         *          'scratchRecIdList' will be initialized with the indexes of
         *          memTab entries containing "Scratch" type memory requests
         *          in memory spaces associated with the ialgHeap.
         *          'numScratchRecs' will be initialized with the number of
         *          such memTab entries
         */
        _DSKT2_getScratchRequestInfo(ialgHeap, memTab, numRecs,
               &thisAlgScrRequestSizeBestCase,
               &thisAlgScrRequestSizeWorstCase,
                       (Int *)_locals->scratchRecIdList,
                       &numScratchRecs);

        if (scrBufDesc->base == NULL) {
            /*
             * If this request is larger than configuration provided scratch
             * buffer size for this group-id & heap AND the shared buffer
             * has not been allocated yet: bump up the configured size info
             * to satisfy current algo's requirements (for this scratch-group)
             */
            scrBufDesc->size = _DSKT2_MAX (scrBufDesc->origSize,
                                    thisAlgScrRequestSizeWorstCase);
        }

        /*
         * allocate shared scratch heap for the 'ialgHeap' only if
         * 'this algorithm' requests a shared scratch in this heap, and
         * a shared buffer for this type of heap is not already allocated.
         */
        if ((scrBufDesc->size > 0) && (scrBufDesc->base == NULL)
                && (thisAlgScrRequestSizeWorstCase > 0)) {

            /*
             * Check the size of largest free contiguous block that can be
             * allocated in the requested heap, and cap the allocation size
             */
            Memory_getStats(_DSKT2_spaceToSeg(ialgHeap), &stats);

            /*
             * if not enough heap to allocate worst case size shared scratch
             * area try an optimistic approach.
             */
            scrBufDesc->size = _DSKT2_MIN(stats.largestFreeSize,
                    scrBufDesc->size);

            if (scrBufDesc->size <= 0) {
                /*
                 * No Shared scratch buffer can be allocated for this heap &
                 * and scratch-group, likely out of heap memory. So, skip.
                 */
                Log_print4(Diags_USER4,
                        "[+4] _DSKT2_initializeAndUseSharedScratch> could not "
                        "allocate scratch heap in %s for group %d. Size "
                        "needed: 0x%x, largest blocksize available: 0x%x",
                        (IArg)((heapId == 0) ? "DARAM": "SARAM0"),
                        (IArg)scrGrpId,
                        (IArg)(_DSKT2_MAX(scrBufDesc->origSize,
                                thisAlgScrRequestSizeWorstCase)),
                        (IArg)(stats.largestFreeSize));
                continue;
            } else {
                /*
                 * otherwise, continue and allocate new shared scratch buffer
                 */
                heap = _DSKT2_spaceToSeg(ialgHeap);

                scrBufDesc->scratchPtr = scrBufDesc->base =
                    myMalloc(heap, scrBufDesc->size, 0);

                if (scrBufDesc->base == NULL) {
                    /*
                     *  Do nothing special if unable to allocate frome scratch
                     *  area (nice try). BUT this is unlikely to happen, due to
                     *  Memory_getStats check and if there are no other tasks
                     *  which can preempt this task AND do Memory_alloc/free
                     *  using this heap, then it should never happen.
                     */
                    continue;
                } else {
                    createdNewSharedScratchBuffer = TRUE;
                }
            }
        }

        /* start sharing at 'base' */
        scrBufDesc->scratchPtr = scrBufDesc->base;

        /*
         * If there is a shared scratch buffer for this 'ialgHeap', and
         * 'this algorithm' requests a shared scratch in this heap,
         * try to satisfy the requested scratch buffers from the shared buffer.
         *
         * Find the optimal placement by considering all permutations of
         * memTab scratch request records, finding the order that results in
         * the minimal size using DSKT2's sequential allocation policy.
         */
        if ((scrBufDesc->size > 0) && (scrBufDesc->base != NULL)
                && (thisAlgScrRequestSizeWorstCase > 0)) {

            /*
             * initialize permutationList as the original ordering
             * of the scratch memTab entries stored in scratchRecIdList
             */
            for (i=0; i<numScratchRecs; i++) {
                _locals->permutationList[i] = &(_locals->scratchRecIdList[i]);
                _locals->optimalRecIdList[i] = _locals->scratchRecIdList[i];
            }
            _DSKT2_Permute_setInitialState(&(_locals->enumeration),
                        (void **)&(_locals->permutationList), numScratchRecs);

            smallestTotalAllocationSize = 0; /* nothing initially */
            minSharedAllocationSize = 0;  /* nothing initially */
            largestNetAllocationSize = 0; /* nothing initially */

            /*
             * iterate through all permutations of the memTab scratch
             * request records until best-case is established or all
             * permutations evaluated, noting the optimal order.
             */
            while (NULL != (recIdList = (int ***)
                    _DSKT2_Permute_iterateNext(&(_locals->enumeration))) ) {

                _DSKT2_ScratchBufferDesc tmpBuffDesc;
                Bool allocatedAll = FALSE;
                Bool allocatedSome = FALSE;
                Int  numRecsAllocated = 0;

                tmpBuffDesc.scratchPtr =  scrBufDesc->base;
                tmpBuffDesc.size =  scrBufDesc->size;
                tmpBuffDesc.base = scrBufDesc->base;

                for (i=0; i<numScratchRecs; i++) {

                    /* Reset memTab base before trying this iteration */
                    memTab[*recIdList[i][0]].base = NULL;

                    /*
                     * Try to allocate current ordering of memTab recs
                     * using the shared scratch buffer.
                     */
                    if (_DSKT2_useSharedScratch(&tmpBuffDesc,
                            &memTab[*recIdList[i][0]]) ) {
                        allocatedSome = TRUE;
                        numRecsAllocated++;
                    }
                }

                if (numRecsAllocated == numScratchRecs) {
                        allocatedAll = TRUE;
                }

                /*
                 *
                 */
                if (allocatedSome) {
                    sharedAllocationSize = (UInt32)(tmpBuffDesc.scratchPtr) -
                            (UInt32)(scrBufDesc->base);

                    /*
                     * If all scratch records fit into shared scratch buffer
                     * check if 'this' permutation is better than previous best
                     * (note: smallestTotalAllocationSize==0 ensures the
                     *        first total allocation sets it.)
                     */
                    if ( allocatedAll && ((smallestTotalAllocationSize == 0)
                        /* first time */ ||
                        (sharedAllocationSize < smallestTotalAllocationSize))) {

                        smallestTotalAllocationSize = sharedAllocationSize;

                        /* this permutation becomes the optimalRecIdList */
                        for (i=0; i<numScratchRecs; i++) {
                            _locals->optimalRecIdList[i] = *recIdList[i][0];
                        }
                    }

                    /*
                     * if unable to allocate 'all' scratch buffers inside the
                     * shared buffer (but allocated 'some'), then save the
                     * permutation that results in utilizing the  shared
                     * with best fit of the subset of memTab entries.
                     * Record bestfit memTab permutation in maximalRecIdList
                     */
                    if ( !allocatedAll ) {

                        /* sum up the 'sizes' of those sharing scratch */
                        netAllocationSize = 0;
                        for (i=0; i<numScratchRecs; i++) {
                            id = *recIdList[i][0];
                            netAllocationSize += ((memTab[id].base == NULL) ?
                                    0 : memTab[id].size);
                        }

                        /* if better fit then previous best, update best */
                        if (netAllocationSize >= largestNetAllocationSize) {

                            /* when tie, pick the one which uses least shared*/
                            if((netAllocationSize == largestNetAllocationSize)
                                &&
                               (sharedAllocationSize > minSharedAllocationSize))
                            {
                                /* do nothing, when there is better fit */
                            } else {
                                largestNetAllocationSize = netAllocationSize;
                                minSharedAllocationSize = sharedAllocationSize;

                                /* this permutation is the maximalRecIdList */
                                for (i=0; i<numScratchRecs; i++) {
                                    _locals->maximalRecIdList[i] =
                                            *recIdList[i][0];
                                }
                            }
                        }
                    }
                    /*
                     * if smallestTotalAllocationSize is the best possible
                     * stop evaluating other permutations, optimal order
                     * of granting shared scratch memory has been found!
                     */
                    if (smallestTotalAllocationSize ==
                            thisAlgScrRequestSizeBestCase) {

                        break;
                    }
                }
            }
            /* TODO: may free & realloc shared buff with optimalSize, as long
             * as reallocation has the same base/alignment as free'd one.
             */

            /* Now really assign scratch buffers using shared scratch*/
            for (i = 0; i < numScratchRecs; i++) {
                memTab[_locals->scratchRecIdList[i]].base = NULL;
            }

            /* Now really assign scratch buffers using shared scratch*/
            if (smallestTotalAllocationSize > 0) {

                /*
                 * Optimal allocation order has been found, use it to alloc
                 */
                for (i=0; i<numScratchRecs; i++) {

                    _DSKT2_useSharedScratch(scrBufDesc,
                            &memTab[_locals->optimalRecIdList[i]]);
                }
            }
            else if (largestNetAllocationSize > 0) {
                /*
                 * Otherwise, share the scratch buffer as fully as possible.
                 */
                for (i=0; i<numScratchRecs; i++) {

                    _DSKT2_useSharedScratch(scrBufDesc,
                            &memTab[_locals->maximalRecIdList[i]]);
                }
            }
            else if (createdNewSharedScratchBuffer) {
                /*
                 * We have NO scratch buffer requests that can be allocated
                 * using the shared scratch buffer that we just created!!!
                 * It was a nice try, BUT now free it.
                 * Note: no-one else in this scratch group is sharing it yet
                 */
                heap = _DSKT2_spaceToSeg(ialgHeap);

                Memory_free(heap, scrBufDesc->base, scrBufDesc->size);
                scrBufDesc->scratchPtr = scrBufDesc->base = NULL;
                scrBufDesc->size = 0;
            }
        } /* end if -- no scratch memory request for this alg in this heap */
    }

    /* free locals on exit */
    Memory_free(_DSKT2_heap, _locals, sizeof(_Locals));

    Log_print0(Diags_EXIT, "[+X] _DSKT2_initializeAndUseSharedScratch> Exit");
}

/*
 *  ======== _DSKT2_allocateInDesignatedSpace ========
 *
 * Allocate as "persistent" in the designated IALG MemSpace.
 */
Bool _DSKT2_allocateInDesignatedSpace(IALG_MemRec memTab[], Int i,
         IALG_MemSpace ialgSpace, xdc_runtime_IHeap_Handle extHeap)
{
    xdc_runtime_IHeap_Handle heap;
    Bool                     status = TRUE;

    Log_print3(Diags_ENTRY,
            "[+E] _DSKT2_allocateInDesignatedSpace> Enter (index=%d, ialgSpace=%s, "
            "extHeap=0x%x)",
            (IArg)i, (IArg)(gt_MemSpace(ialgSpace)), (IArg)extHeap);

    heap = _DSKT2_spaceToSeg(ialgSpace);

    /*
     *  All IALG memory types that are mapped to the same segment as
     *  IALG_ESDATA will use the external heap segment specified by
     *  extHeapId.
     */
    if (heap == _DSKT2_spaceToSeg(IALG_ESDATA)) {
        heap = extHeap;
    }

    /* GUNTODO Make address globally recognizable (on MC)  */
    memTab[i].base = myMalloc(heap, memTab[i].size, memTab[i].alignment);
    if (memTab[i].base == NULL) {
        status = FALSE; /* return false on failure */

    } else {
        memTab[i].space = ialgSpace;
        if (memTab[i].attrs == IALG_SCRATCH) {
            memTab[i].attrs = IALG_PERSIST;
        }
    }

    Log_print1(Diags_EXIT,
            "[+X] _DSKT2_allocateInDesignatedSpace> Exit (returnVal=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== _DSKT2_allocateInInternal ========
 *
 *  Allocate as "persistent" in one of the available "internal" heaps
 */
Bool _DSKT2_allocateInInternal(IALG_MemRec memTab[], Int i,
        xdc_runtime_IHeap_Handle extHeap)
{
    Int                      heapId;
    xdc_runtime_IHeap_Handle heap;

    IALG_MemSpace INTERNAL_HEAPS[] = {IALG_DARAM0, IALG_DARAM1, IALG_DARAM2,
                                      IALG_SARAM0, IALG_SARAM2, IALG_SARAM2};

    Log_print2(Diags_ENTRY, "[+E] _DSKT2_allocateInInternal> "
            "Enter (index=%d, extHeap=0x%x)", (IArg)i, (IArg)extHeap);

    for (heapId = 0; heapId < _DSKT2_NUM_INTERNAL_HEAPS; heapId++) {

        heap = _DSKT2_spaceToSeg(INTERNAL_HEAPS[heapId]);

        if (heap == _DSKT2_spaceToSeg(IALG_ESDATA)) {
            heap = extHeap;
        }

        if ((memTab[i].base = myMalloc(heap, memTab[i].size,
                     memTab[i].alignment)) != NULL) {

            memTab[i].space = INTERNAL_HEAPS[heapId];

            if (memTab[i].attrs == IALG_SCRATCH) {
                memTab[i].attrs = IALG_PERSIST;
            }

            Log_print0(Diags_EXIT,
                    "[+X] _DSKT2_allocateInInternal> Exit (status=TRUE)");

            return (TRUE);
        }
    }

    Log_print0(Diags_EXIT,
            "[+X] _DSKT2_allocateInInternal> Exit (status=FALSE)");

    return (FALSE);
}


/*
 *  ======== _DSKT2_exitScratch ========
 */
Int _DSKT2_exitScratch(Int scratchMutexId)
{
    /*
     * If ref-count for sharing scratch at this scratchMutexId dropped to zero
     * free any shared heap's that are allocated for share
     */

    _DSKT2_ScratchBufferDesc *scrBufDesc;
    Int heapId;
    Int ialgHeap;
    xdc_runtime_IHeap_Handle heap;
    Int status = _DSKT2_OK;

    Log_print1(Diags_ENTRY, "[+E] _DSKT2_exitScratch> Enter (scratchMutexId=%d)",
            (IArg)scratchMutexId);

    if ((scratchMutexId < 0) || (scratchMutexId >= DSKT2_NUM_SCRATCH_GROUPS)) {
        return (status);
    }

    if (_DSKT2_scratchShareRefCount[scratchMutexId] > 0) {
        return (status);
    }

    for (heapId = 0; heapId < DSKT2_NUM_SHAREDHEAPS; heapId++) {
        scrBufDesc = &_DSKT2_scratchDescTbl[heapId][scratchMutexId];
        ialgHeap = (heapId == 0) ? IALG_DARAM0: IALG_SARAM0;

        if ((scrBufDesc->size > 0) && (scrBufDesc->base != NULL )) {
            heap = _DSKT2_spaceToSeg(ialgHeap);
            Memory_free(heap, scrBufDesc->base, scrBufDesc->size);
            scrBufDesc->base = NULL;
         }
    }

    Log_print1(Diags_EXIT, "[+X] _DSKT2_exitScratch> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== _DSKT2_incrScratchReferenceCount ========
 */
Void _DSKT2_incrScratchReferenceCount(Int scratchMutexId)
{
    IArg key;

    Log_print1(Diags_ENTRY,
            "[+E] _DSKT2_incrScratchReferenceCount> Enter (scratchMutexId=%d)",
            (IArg)scratchMutexId);

    Assert_isTrue((scratchMutexId >= 0) &&
            (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS), (Assert_Id)NULL);

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);
    _DSKT2_scratchShareRefCount[scratchMutexId]++;

    /* restore critical section before return */
    IGateProvider_leave(_DSKT2_gate, key);

    Log_print0(Diags_EXIT, "[+X] _DSKT2_incrScratchReferenceCount> Exit");
}

/*
 *  ======== _DSKT2_decrScratchReferenceCount ========
 */
Void _DSKT2_decrScratchReferenceCount(Int scratchMutexId)
{
    IArg key;

    Log_print1(Diags_ENTRY,
            "[+E] _DSKT2_decrScratchReferenceCount> Enter (scratchMutexId=%d)",
            (IArg)scratchMutexId);

    Assert_isTrue((scratchMutexId >= 0) &&
            (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS), (Assert_Id)NULL);

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);

    _DSKT2_scratchShareRefCount[scratchMutexId]--;

    /* restore critical section before return */
    IGateProvider_leave(_DSKT2_gate, key);

    Assert_isTrue(_DSKT2_scratchShareRefCount[scratchMutexId] >= 0,
            (Assert_Id)NULL);

    Log_print0(Diags_EXIT, "[+X] _DSKT2_decrScratchReferenceCount> Exit");
}

/*
 *  ======== _DSKT2_allocateFromSharedScratch ========
 */
Bool _DSKT2_allocateFromSharedScratch(Int mutexId, IALG_MemRec *memTab)
{

    Bool status;
    _DSKT2_ScratchBufferDesc *primaryScrBufDesc;
    _DSKT2_ScratchBufferDesc *secondaryScrBufDesc;

    Log_print1(Diags_ENTRY,
            "[+E] _DSKT2_allocateFromSharedScratch> Enter (scratchMutexId=%d \n)",
            (IArg)mutexId);

    Assert_isTrue((mutexId >= 0) && (mutexId < DSKT2_NUM_SCRATCH_GROUPS),
            (Assert_Id)NULL);

    if ((memTab->space == IALG_DARAM0) || (memTab->space == IALG_DARAM1) ||
            (memTab->space == IALG_DARAM2)) {
        primaryScrBufDesc  = &_DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId];
        secondaryScrBufDesc= &_DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId];

    } else {
        primaryScrBufDesc  = &_DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId];
        secondaryScrBufDesc= &_DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId];
    }


    status = (_DSKT2_useSharedScratch(primaryScrBufDesc, memTab) ||
            _DSKT2_useSharedScratch(secondaryScrBufDesc, memTab) );

    Log_print1(Diags_EXIT,
            "[+X] _DSKT2_allocateFromSharedScratch> Exit (status=%d\n)",
            (IArg)status);

    return (status);
}

/*
 *  ======== _DSKT2_isSharedScratchAddr ========
 */
Bool _DSKT2_isSharedScratchAddr(Int mutexId, Void *addr)
{
    Bool status;

    Log_print2(Diags_ENTRY, "[+E] _DSKT2_isSharedScratchAddr> "
            "Enter (scratchMutexId=%d, addr=0x%x)", (IArg)mutexId, (IArg)addr);

    if ((mutexId < 0) || (mutexId >= DSKT2_NUM_SCRATCH_GROUPS)) {

        Log_print0(Diags_EXIT,
                "[+X] _DSKT2_isSharedScratchAddr> Exit (status=FALSE)");

        return (FALSE);
    }

    status = (
        ((_DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId].base != NULL)
                &&
            (addr >= _DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId].base)  &&
            ( (UInt32) addr <
            ( (UInt32) _DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId].base +
                      _DSKT2_scratchDescTbl[_DSKT2_DARAMHEAP][mutexId].size)))
            ||

        ((_DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId].base != NULL)
                &&
            (addr >= _DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId].base)  &&
            ( (UInt32) addr <
            ( (UInt32) _DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId].base +
                      _DSKT2_scratchDescTbl[_DSKT2_SARAMHEAP][mutexId].size))));

    Log_print1(Diags_EXIT, "[+X] _DSKT2_isSharedScratch> Exit (status=%d )",
            (IArg)status);

    return (status);
}

/*
 *  ======== _DSKT2_useSharedScratch ========
 */
Bool _DSKT2_useSharedScratch(_DSKT2_ScratchBufferDesc *scrBuffDesc,
         IALG_MemRec *memTab)
{
    UInt reqBuffSize;  /* in MAUs */
#if USESCRATCHOPT
    UInt align;
    UInt offset;
#endif
    /* TODO: optimize size of shared region if already aligned */

    if (scrBuffDesc->base == NULL) {

        return (FALSE);
    }

#if USESCRATCHOPT
    /* Minimize scratch usage if scratchPtr is already aligned */
    align = memTab->alignment;
    if (align < sizeof(UInt)) {
        align = sizeof(UInt);
    }

    /* # of MAUs from last aligned address */
    offset = 0;
    if ((UInt32)scrBuffDesc->scratchPtr & (align - 1)) {
        offset = (UInt)((UInt32)scrBuffDesc->scratchPtr & (align - 1));
        offset = align - offset;
    }

    reqBuffSize = memTab->size + offset;

#else
    /* Allocating more than necessary if scratchPtr is already aligned */
    reqBuffSize = (memTab->alignment > 1) ?
                      memTab->size + memTab->alignment :
                      memTab->size;
#endif
    /* Fail if current scratch req is greater than remaining scratch */
    if (reqBuffSize > (scrBuffDesc->size -
            ((UInt32)scrBuffDesc->scratchPtr - (UInt32)scrBuffDesc->base))) {

        return (FALSE);
    }

#if USESCRATCHOPT
    memTab->base = (Void *)((UInt32)scrBuffDesc->scratchPtr + offset);
#else
    /*
     *  Assign shared scratch memory address at the current free pointer
     *  plus any adjustment to create the correct alignment.
     */
    if (memTab->alignment > 1) {
        memTab->base = (Void *)
            ( ((UInt32)scrBuffDesc->scratchPtr + memTab->alignment) &
            (~((UInt32)memTab->alignment - 1)) );
    }
    else {
        memTab->base =  scrBuffDesc->scratchPtr;
    }
#endif

    /* advance free scratch pointer past current allocation */
    scrBuffDesc->scratchPtr = (Void *) ((UInt32)scrBuffDesc->scratchPtr +
                                        reqBuffSize);

    return (TRUE);
}

/*
 *  ======== _DSKT2_enqueueMemTab ========
 */
Bool _DSKT2_enqueueMemTab(xdc_runtime_IHeap_Handle heap, IALG_MemRec *memTab,
        Int memTabSize, Int numRecs, xdc_runtime_IHeap_Handle extHeap,
        Int scratchId)
{
    _DSKT2_MemTabListNode *listNodePtr;
    IArg                   key;

    Log_print4(Diags_ENTRY, "[+E] _DSKT2_enqueueMemTab> "
            "Enter (heap=0x%x, memTabSize=%d, numRecs=%d, extHeapId=0x%x)",
            (IArg)heap, (IArg)memTabSize, (IArg)numRecs, (IArg)extHeap);

    Assert_isTrue(extHeap != NULL, (Assert_Id)NULL);

    /* allocate the linked list node to store the memTab associated with alg*/
    if ((listNodePtr = myMalloc(heap, sizeof(_DSKT2_MemTabListNode), 0))
            == NULL) {
        Log_print0(Diags_EXIT, "[+X] _DSKT2_enqueueMemTab> Exit (status=FALSE)");

       return (FALSE);
    }

    /* add to the front of the list */
    listNodePtr->memTab  = memTab;
    listNodePtr->memTabSize = memTabSize;
    listNodePtr->numRecs = numRecs;
    listNodePtr->extHeap = extHeap;
    listNodePtr->scratchId = scratchId;
    /* record the scratchPtr set for the current alg allocation */
    listNodePtr->scratchPtr[0] = _DSKT2_scratchDescTbl[0][scratchId].scratchPtr;
    listNodePtr->scratchPtr[1] = _DSKT2_scratchDescTbl[1][scratchId].scratchPtr;

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);

    listNodePtr->next    = _DSKT2_memTabList;
    _DSKT2_memTabList = listNodePtr;
    _numAlgs++;

    /* restore critical section before return */
    IGateProvider_leave(_DSKT2_gate, key);

    Log_print0(Diags_EXIT, "[+X] _DSKT2_enqueueMemTab> Exit (status=TRUE)");

    return (TRUE);
}

/*
 *  ======== _DSKT2_dequeueMemTab ========
 */
IALG_MemRec *_DSKT2_dequeueMemTab(xdc_runtime_IHeap_Handle heap,
        IALG_Handle alg, Int *memTabSize, Int *numRecs,
        xdc_runtime_IHeap_Handle *extHeap, Int *scratchId)
{
    _DSKT2_MemTabListNode *listNodePtr, *prev;
    IALG_MemRec *memTab;
    IArg         key;

    Log_print2(Diags_ENTRY, "[+E] _DSKT2_dequeueMemTab> "
            "Enter (heap=0x%x, alg=0x%x)", (IArg)heap, (IArg)alg);

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);

    /* first find the saved memTab entry for the alg Handle */
    prev = listNodePtr = _DSKT2_memTabList;

    while (listNodePtr != NULL) {

        if (listNodePtr->memTab[0].base == alg) {
            prev->next  = listNodePtr->next;
            memTab      = listNodePtr->memTab;
            *memTabSize = listNodePtr->memTabSize;
            *numRecs    = listNodePtr->numRecs;
            *extHeap  = listNodePtr->extHeap;
            *scratchId = listNodePtr->scratchId;

            Assert_isTrue(listNodePtr->extHeap != NULL, (Assert_Id)NULL);

            if (_DSKT2_memTabList == listNodePtr) {
                _DSKT2_memTabList = listNodePtr->next;
            }

            _numAlgs--;

             /* restore critical section before calling MEM_free & return*/
            IGateProvider_leave(_DSKT2_gate, key);

            /* free the list node but not the actual memTab[] */
            Memory_free(heap, listNodePtr, sizeof(_DSKT2_MemTabListNode));

            Log_print1(Diags_EXIT,
                    "[+X] _DSKT2_dequeueMemTab> Exit (memTab=0x%x)",
                    (IArg)memTab);

            return (memTab);
        }
        prev = listNodePtr;
        listNodePtr = listNodePtr->next;
    }

    IGateProvider_leave(_DSKT2_gate, key); /* leave critical section */

    Log_print0(Diags_EXIT, "[+X] _DSKT2_dequeueMemTab> Exit (memTab=NULL)");

    return (NULL);
}

/*
 *  ======== _DSKT2_registerCreationCallbackFxn ========
 */
Void _DSKT2_registerCreationCallbackFxn(_DSKT2_CreateCallbackFxn fxn)
{
    _DSKT2_createCallbackFxn = fxn;
}

/*
 *  ======== _DSKT2_unRegisterCreationCallbackFxn ========
 */
/* ARGSUSED */
Void _DSKT2_unRegisterCreationCallbackFxn(_DSKT2_CreateCallbackFxn fxn)
{
    _DSKT2_createCallbackFxn = NULL;
}

/*
 *  ======== _DSKT2_getAlgCreationData ========
 */
_DSKT2_MemTabListNode *_DSKT2_getAlgCreationData(IALG_Handle alg)
{
    _DSKT2_MemTabListNode    *listNodePtr = NULL;
    IArg                      key;
    Int                       found = 0;

    key = IGateProvider_enter(_DSKT2_gate);

    /* Find alg in memTab queue */
    if (alg) {
        listNodePtr = _DSKT2_memTabList;

        while (listNodePtr != NULL) {
            if (listNodePtr->memTab[0].base == alg) {
                /* found */
                found = 1;

                break;
            }
            listNodePtr = listNodePtr->next;
        }
    }

    IGateProvider_leave(_DSKT2_gate, key);

    if (found) {
       return listNodePtr;

    } else {
       return (_DSKT2_MemTabListNode *)NULL;
    }
}

/*
 *  ======== _DSKT2_getScratchId ========
 */
Int DSKT2_getScratchId(IALG_Handle alg)
{
    _DSKT2_MemTabListNode    *listNodePtr = NULL;
    IArg                      key;
    Int                       scratchId = -1;

    Log_print1(Diags_ENTRY, "[+E] _DSKT2_getScratchId> "
            "Enter (alg=0x%x)", (IArg)alg );

    key = IGateProvider_enter(_DSKT2_gate);

    /* Find alg in memTab queue */
    if (alg) {
        listNodePtr = _DSKT2_memTabList;

        while (listNodePtr != NULL) {
            if (listNodePtr->memTab[0].base == alg) {
                /* found */
                scratchId = listNodePtr->scratchId;

                break;
            }
            listNodePtr = listNodePtr->next;
        }
    }

    IGateProvider_leave(_DSKT2_gate, key);

    /* Nothing found return -1 */
    Log_print1(Diags_EXIT, "[+X] _DSKT2_getScratchId> Exit (scratchId= %d )",
               scratchId);

    return scratchId;
}
/*
 *  ======== _DSKT2_getScratchUsed ========
 */
UInt32 _DSKT2_getScratchUsed(IALG_Handle alg, Int mutexId, Int heapId)
{
    UInt32                    size = 0;
    Int                       i;
    _DSKT2_ScratchBufferDesc *desc;
    IALG_MemRec               memTab;
    _DSKT2_MemTabListNode    *listNodePtr = NULL;
    UInt32                    scratchBase = NULL;
    UInt32                    scratchEnd;
    IArg                      key;

    Log_print3(Diags_ENTRY, "[+E] _DSKT2_getScratchUsed> "
            "Enter (alg=0x%x, mutexId=%d, heapId=%d)",
            (IArg)alg, (IArg)mutexId, (IArg)heapId);

    key = IGateProvider_enter(_DSKT2_gate);

    /* Find alg in memTab queue */
    if (alg) {
        listNodePtr = _DSKT2_memTabList;
        while (listNodePtr != NULL) {
            if (listNodePtr->memTab[0].base == alg) {
                /* found */
                break;
            }
            listNodePtr = listNodePtr->next;
        }
    }

    IGateProvider_leave(_DSKT2_gate, key);

    if (listNodePtr != NULL) {
        desc = &_DSKT2_scratchDescTbl[heapId][mutexId];

        if (desc->base != NULL) {
            scratchBase = (UInt32)(desc->base);
            scratchEnd = (UInt32)(desc->base) + desc->size;

           /*
            *  Compute the scratch memory used - Find the largest memTab
            *  base from the scratch base, and add the size for that
            *  memTab. This accounts for holes left by alignment.
            */
            for (i = 0; i < listNodePtr->numRecs; i++) {
                memTab = listNodePtr->memTab[i];
                if (((UInt32)(memTab.base) >= scratchBase) &&
                        ((UInt32)(memTab.base) < scratchEnd)) {
                    scratchBase = (UInt32)(memTab.base);
                    size = memTab.size;
                }
            }
        }
        size += (scratchBase - (UInt32)desc->base);
    }

    Log_print1(Diags_EXIT, "[+X] _DSKT2_getScratchUsed> Exit (size=0x%x)",
            (IArg)size);

    return (size);
}

/*
 *  ======== DSKT2_allocScratch ========
 *  Allocate from scratch memory for alg.
 *  If alg != NULL, allocate after scratch that was allocated to alg when
 *  it was created. If alg == NULL, start allocating from the beginning of
 *  scratch space for this scratch group (mutexId).
 */
Bool DSKT2_allocScratch(IALG_Handle alg, Int mutexId, IALG_MemRec *memTab,
        Int numRecs)
{
    UInt32                     scratchUsed = 0;
    IALG_MemRec               dummyMem;
    Int                       heapId = _DSKT2_DARAMHEAP;
    Int                       i;
    _DSKT2_ScratchBufferDesc *desc;
    IALG_MemSpace             space = IALG_DARAM0;
    xdc_runtime_IHeap_Handle  daram0Seg;
    xdc_runtime_IHeap_Handle  saram0Seg;
    UInt                      size = 0;
    Bool                      retVal = TRUE;


    Log_print3(Diags_ENTRY, "[+E] DSKT2_allocScratch> "
            "Enter (alg=0x%x, mutexId=%d, numRecs=%d)",
            (IArg)alg, (IArg)mutexId, (IArg)numRecs);

    if ((mutexId < 0) || (mutexId >= DSKT2_NUM_SCRATCH_GROUPS)) {

        Log_print0(Diags_EXIT, "[+X] DSKT2_allocScratch Exit (status=FALSE)");

        return (FALSE);
    }

    /*
     *  Determine which scratch heap to use by looking at the space of the
     *  first request for scratch.
     *  Pass space as an argument to DSKT2_allocScratch()? Then it would
     *  be clear which space is being used.
     */
    daram0Seg = _DSKT2_spaceToSeg(IALG_DARAM0);
    saram0Seg = _DSKT2_spaceToSeg(IALG_SARAM0);

    for (i = 0; i < numRecs; i++) {
        if (memTab[i].attrs == IALG_SCRATCH) {
            space = memTab[i].space;
            if (_DSKT2_spaceToSeg(space) == daram0Seg) {
                space = IALG_DARAM0;
                heapId = _DSKT2_DARAMHEAP;
                break;
            }
            if (_DSKT2_spaceToSeg(space) == saram0Seg) {
                space = IALG_SARAM0;
                heapId = _DSKT2_SARAMHEAP;
                break;
            }
        }
    }

    /*
     *  If none of the memory requests were for scratch DARAM0 or SARAM0
     *  memory, there is nothing to do.
     */
    if (i == numRecs) {

        Log_print0(Diags_EXIT, "[+X] DSKT2_allocScratch Exit (status=TRUE)");

        return (TRUE);
    }

    /*
     *  Make sure alignment is 0 if size is 0, so we don't allocate a scratch
     *  heap if all sizes in the memTab array are 0.
     */
    for (i = 0; i < numRecs; i++) {
        if (memTab[i].size == 0) {
            memTab[i].alignment = 0;
        }
    }

    desc = &_DSKT2_scratchDescTbl[heapId][mutexId];

#if ALLOCSCRATCH
    /*
     *  Set up a dummy memTab to force scratch heap to be allocated, if not
     *  allready allocated and the configured size for the scratch group is
     *  non-zero. _DSKT2_initializeAndUseSharedScratch() will also reset the
     *  scratch pointer to the start of the scratch heap.
     *
     *  Or, should we not allocate the scratch memory if it has not been
     *  allocated yet????
     */
    size = _DSKT2_getReqScratchSize(space, memTab, numRecs);
#if ALLOC_ORIGSIZE
    dummyMem.size = _DSKT2_MAX(desc->origSize, size);
#else
    /*
     *  If the scratch heap has not been created, only make it big enough
     *  for this request.
     */
    dummyMem.size = size;
#endif
    dummyMem.alignment = 0;
    dummyMem.space = space;
    dummyMem.attrs = IALG_SCRATCH;

    _DSKT2_initializeAndUseSharedScratch(mutexId, &dummyMem, 1);
#endif

    if (alg != NULL) {
        /*
         *  Set the base pointer to the end of the scratch memory that was
         *  already allocated (if any) for this alg.
         */
        scratchUsed = _DSKT2_getScratchUsed(alg, mutexId, heapId);
    }

    desc->scratchPtr = (Void *)((UInt32)desc->base + scratchUsed);

    for (i = 0; i < numRecs; i++) {
        if ((memTab[i].size > 0) && (memTab[i].attrs == IALG_SCRATCH)) {
            retVal = _DSKT2_useSharedScratch(desc, &memTab[i]);
            if (!retVal) {
                break;
            }
        }
    }

    if (retVal) {
        /* Increment scratch ref count for all scratch buffers allocted */
        for (i = 0; i < numRecs; i++) {
            if ((memTab[i].size > 0) && (memTab[i].attrs == IALG_SCRATCH)) {
                _DSKT2_incrScratchReferenceCount(mutexId);
            }
        }
    }

    Log_print1(Diags_EXIT, "[+X] DSKT2_allocScratch Exit (status=%d)",
            (IArg)retVal);

    return (retVal);
}

/*
 *  ======== DSKT2_allocScratchr2 ========
 *  Allocate from scratch memory for alg.
 *  If alg != NULL, allocate after scratch that was allocated to alg when
 *  it was created. If alg == NULL, start allocating from the beginning of
 *  scratch space for this scratch group (mutexId).
 */
Bool DSKT2_allocScratch2(IALG_Handle alg, Int mutexId, IALG_MemRec *memTab,
        Int numRecs)
{
    IALG_MemRec               dummyMem;
    Int                       heapId = _DSKT2_DARAMHEAP;
    Int                       i;
    _DSKT2_ScratchBufferDesc *desc;
    _DSKT2_ScratchBufferDesc  descClone;
    IALG_MemSpace             space = IALG_DARAM0;
    xdc_runtime_IHeap_Handle  daram0Seg;
    xdc_runtime_IHeap_Handle  saram0Seg;
    UInt                      size = 0;
    Bool                      retVal = TRUE;
    _DSKT2_MemTabListNode *listNodePtr;


    Log_print3(Diags_ENTRY, "[+E] DSKT2_allocScratch2> "
            "Enter (alg=0x%x, mutexId=%d, numRecs=%d)",
            (IArg)alg, (IArg)mutexId, (IArg)numRecs);

    if ((mutexId < 0) || (mutexId >= DSKT2_NUM_SCRATCH_GROUPS) ||
        (alg == NULL)) {

        Log_print0(Diags_EXIT, "[+X] DSKT2_allocScratch2 Exit (status=FALSE)");

        return (FALSE);
    }

    /*
     *  Determine which scratch heap to use by looking at the space of the
     *  first request for scratch.
     *  Pass space as an argument to DSKT2_allocScratch()? Then it would
     *  be clear which space is being used.
     */
    daram0Seg = _DSKT2_spaceToSeg(IALG_DARAM0);
    saram0Seg = _DSKT2_spaceToSeg(IALG_SARAM0);

    for (i = 0; i < numRecs; i++) {
        if (memTab[i].attrs == IALG_SCRATCH) {
            space = memTab[i].space;
            if (_DSKT2_spaceToSeg(space) == daram0Seg) {
                space = IALG_DARAM0;
                heapId = _DSKT2_DARAMHEAP;
                break;
            }
            if (_DSKT2_spaceToSeg(space) == saram0Seg) {
                space = IALG_SARAM0;
                heapId = _DSKT2_SARAMHEAP;
                break;
            }
        }
    }

    /*
     *  If none of the memory requests were for scratch DARAM0 or SARAM0
     *  memory, there is nothing to do.
     */
    if (i == numRecs) {

        Log_print0(Diags_EXIT, "[+X] DSKT2_allocScratch Exit (status=TRUE)");

        return (TRUE);
    }

    /*
     *  Make sure alignment is 0 if size is 0, so we don't allocate a scratch
     *  heap if all sizes in the memTab array are 0.
     */
    for (i = 0; i < numRecs; i++) {
        if (memTab[i].size == 0) {
            memTab[i].alignment = 0;
        }
    }

    desc = &_DSKT2_scratchDescTbl[heapId][mutexId];

#if ALLOCSCRATCH
    /*
     *  Set up a dummy memTab to force scratch heap to be allocated, if not
     *  allready allocated and the configured size for the scratch group is
     *  non-zero. _DSKT2_initializeAndUseSharedScratch() will also reset the
     *  scratch pointer to the start of the scratch heap.
     *
     *  Or, should we not allocate the scratch memory if it has not been
     *  allocated yet????
     */
    size = _DSKT2_getReqScratchSize(space, memTab, numRecs);
#if ALLOC_ORIGSIZE
    dummyMem.size = _DSKT2_MAX(desc->origSize, size);
#else
    /*
     *  If the scratch heap has not been created, only make it big enough
     *  for this request.
     */
    dummyMem.size = size;
#endif
    dummyMem.alignment = 0;
    dummyMem.space = space;
    dummyMem.attrs = IALG_SCRATCH;

    _DSKT2_initializeAndUseSharedScratch(mutexId, &dummyMem, 1);
#endif
    /* Make a copy of the descriptor for internal use */
    memcpy(&descClone, desc, sizeof (_DSKT2_ScratchBufferDesc));

    listNodePtr = _DSKT2_getAlgCreationData(alg);

    /*
     * at this point listNodePtr->scratchPtr[heapId] contains the pointer
     * recoreded during 'alg's creation, i.e. past its internal scratch
     * allocations for its IALG use.
     */
    if (listNodePtr->scratchPtr[heapId] == 0) {
        /*
         * Looks like the alg did not request any scratch memory and none
         * was allocated for the scratch group until just now. In that case
         * record current allocation for future calls.
         */
        listNodePtr->scratchPtr[heapId] = desc->base;
    }
    descClone.scratchPtr = (Void *) listNodePtr->scratchPtr[heapId];

    for (i = 0; i < numRecs; i++) {
        if ((memTab[i].size > 0) && (memTab[i].attrs == IALG_SCRATCH)) {
            retVal = _DSKT2_useSharedScratch(&descClone, &memTab[i]);
            if (!retVal) {
                break;
            } else {
                listNodePtr->scratchPtr[heapId] = descClone.scratchPtr;
            }
        }
    }

    if (retVal) {
        /* Increment scratch ref count for all scratch buffers allocted */
        for (i = 0; i < numRecs; i++) {
            if ((memTab[i].size > 0) && (memTab[i].attrs == IALG_SCRATCH)) {
                _DSKT2_incrScratchReferenceCount(mutexId);
            }
        }
    }

    Log_print1(Diags_EXIT, "[+X] DSKT2_allocScratch Exit (status=%d)",
            (IArg)retVal);

    return (retVal);
}


/*
 *  ======== DSKT2_freeScratch ========
 *  Free scratch memory allocated with DSKT2_allocScratch. This will
 *  only decrement the reference count of the scratch buffer, and not change
 *  the amount of scratch used by the alg.
 */
Void DSKT2_freeScratch(Int mutexId, Void *addr, UInt size)
{
    Int                       heapId;
    UInt32                    base;
    UInt32                    end;
    _DSKT2_ScratchBufferDesc *desc;


    Log_print3(Diags_ENTRY, "[+E] DSKT2_freeScratch "
            "Enter (mutexId=%d, addr=0x%x, size=0x%x)",
            (IArg)mutexId, (IArg)addr, (IArg)size);

    if ((mutexId < 0) || (mutexId >= DSKT2_NUM_SCRATCH_GROUPS) ||
            (size == 0)) {
        return;
    }

    /* Make sure base address is in a scratch region */
    for (heapId = 0; heapId < DSKT2_NUM_SHAREDHEAPS; heapId++) {
        desc = &_DSKT2_scratchDescTbl[heapId][mutexId];

        base = (UInt32)desc->base;
        end = (UInt32)desc->base + desc->size;
        if (((UInt32)addr >= base) && ((UInt32)addr + size <= end)) {
            break;
        }
    }

    if (heapId < DSKT2_NUM_SHAREDHEAPS) {
        _DSKT2_decrScratchReferenceCount(mutexId);
        _DSKT2_exitScratch(mutexId);
    }

    Log_print0(Diags_EXIT, "[+X] DSKT2_freeScratch Exit");
}

/*
 *  =========DSKT2_allocPersistent ========
 *  Allocate from persistent memory for alg.
 */
Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs)
{
    xdc_runtime_IHeap_Handle extHeap;
    Int                      i = 0;
    Bool                     status;


    Log_print1(Diags_ENTRY, "[+E] DSKT2_allocPersistent> Enter (numRecs=%d)",
            (IArg)numRecs);

    Assert_isTrue(numRecs >= 1, (Assert_Id)NULL);


    _DSKT2_init();

    for (i = 0; i < numRecs; i++) {

        if (IALG_PERSIST != memTab[i].attrs) {

            Log_print1(Diags_EXIT,
                    "[+X] DSKT2_allocPersistent> Exit (status=%d)", (IArg)FALSE);

            return(FALSE);
        }
    }

    extHeap = _DSKT2_spaceToSeg(IALG_ESDATA);

    status = _DSKT2_assignInstanceMemory(-1, memTab, numRecs, extHeap);

    Log_print1(Diags_EXIT, "[+X] DSKT2_allocPersistent> Exit (status=%d)",
            (IArg)status);

    return (status);
}

/*
 *  ======== DSKT2_freePersistent ========
 *  Free persistent memory allocated with DSKT2_allocPersistent.
 */
Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs)
{
    Int                      i;
    xdc_runtime_IHeap_Handle extHeap;


    Log_print1(Diags_ENTRY, "[+E] DSKT2_freePersistent> Enter (numRecs=%d)",
            (IArg)numRecs);

    Assert_isTrue(numRecs >= 1, (Assert_Id)NULL);


    for (i = 0; i < numRecs; i++) {
        if (IALG_PERSIST != memTab[i].attrs) {

            Log_print0(Diags_EXIT, "[+X] DSKT2_freePersistent> Exit");

            return ;
        }
    }

    extHeap = _DSKT2_spaceToSeg(IALG_ESDATA);

    _DSKT2_freeAllocatedMemory(-1, memTab, numRecs, extHeap);

     Log_print0(Diags_EXIT, "[+X] DSKT2_freePersistent> Exit");
}

/*
 *  ======== DSKT2_getMemRecs ========
 */
Int DSKT2_getMemRecs(IALG_Handle alg, IALG_MemRec *memTab, Int nRecs)
{
    _DSKT2_MemTabListNode *listNodePtr;
    IALG_MemRec *algMemTab;
    Int          numRecs = 0;
    Int          i;
    IArg         key;

    Log_print3(Diags_ENTRY, "[+E] DSKT2_getMemRecs> "
            "Enter (alg=0x%x, memTab=0x%x, nRecs=%d)",
            (IArg)alg, (IArg)memTab, (IArg)nRecs);

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);

    /* first find the saved memTab entry for the alg Handle */
    listNodePtr = _DSKT2_memTabList;

    while (listNodePtr != NULL) {

        if (listNodePtr->memTab[0].base == alg) {
            algMemTab   = listNodePtr->memTab;
            numRecs    = listNodePtr->numRecs;

            /* Don't copy more than will fit in array */
            if (numRecs > nRecs) {
                Log_print3(Diags_USER4,
                        "[+4] DSKT2_getMemRecs> Warning: alg (0x%x) uses more "
                        "mem recs (%d) than can be copied (%d) to memTab.",
                        (IArg)alg, (IArg)numRecs, (IArg)nRecs);
                numRecs = nRecs;
            }

            for (i = 0; i < numRecs; i++) {
                memTab[i] = algMemTab[i];
            }
            break;
        }
        listNodePtr = listNodePtr->next;
    }

    IGateProvider_leave(_DSKT2_gate, key); /* restore critical section before return */

    Log_print1(Diags_EXIT, "[+X] DSKT2_getMemRecs> Exit (numRecs=%d)",
            (IArg)numRecs);

    return (numRecs);
}

/*
 *  ======== DSKT2_getNumMemRecs ========
 */
Int DSKT2_getNumMemRecs(IALG_Handle alg)
{
    _DSKT2_MemTabListNode *listNodePtr;
    Int          numRecs = 0;
    IArg         key;

    Log_print1(Diags_ENTRY, "[+E] DSKT2_getMemRecs> Enter (alg=0x%x)",
            (IArg)alg);

    /* critical section around access to global data structure */
    key = IGateProvider_enter(_DSKT2_gate);

    /* first find the saved memTab entry for the alg Handle */
    listNodePtr = _DSKT2_memTabList;

    while (listNodePtr != NULL) {

        if (listNodePtr->memTab[0].base == alg) {
            numRecs    = listNodePtr->numRecs;
            break;
        }
        listNodePtr = listNodePtr->next;
    }

    IGateProvider_leave(_DSKT2_gate, key); /* leave critical section */

    Log_print1(Diags_EXIT, "[+X] DSKT2_getMemRecs> Exit (numRecs=%d)",
            (IArg)numRecs);

    return (numRecs);
}

/*
 *  ======== myMalloc ========
 */
static Void *myMalloc(xdc_runtime_IHeap_Handle heap, SizeT size, SizeT align)
{
    Void       *buf;
    Error_Block eb;

    /* Must initialize prior to first use */
    Error_init(&eb);

    /*
     *  We need to pass a non-NULL error block to Memory_calloc(), in order
     *  not to abort on allocation failure. Since DSKT2 may try allocating
     *  from another heap if allocation in the first heap failed, we definitely
     *  don't want to abort here.
     */
    buf = Memory_calloc(heap, size, align, &eb);

    /* Writeback and invalidate cache, if function is specified */
    if ((DSKT2_cacheWBInvFxn != NULL)  && (buf != NULL)){
            (DSKT2_cacheWBInvFxn)(buf, size, TRUE);
    }

    /*
     *  Error_check() returns TRUE if an error occurred. (Memory_calloc() will
     *  also return NULL if an error occurred.)
     */
    if (Error_check(&eb)) {
        return (NULL);
    }
    else {
        return (buf);
    }
}

/*
 *  ======== DSKT2_numAlg ========
 *  Returns the number of algorithms that were created using DSKT2
 */
Int DSKT2_getNumAlgs()
{
    return (_numAlgs);
}

/*
 *  ======== DSKT2_getAlgList ========
 *  Returns the list of algorithms created using DSKT2 and the corresponding
 *  scratch Ids.
 */
Int DSKT2_getAlgList(IALG_Handle * algList, Int * scratchIds)
{
    _DSKT2_MemTabListNode *listNodePtr;
    int count = 0;

    /* first find the saved memTab entry for the alg Handle */
    listNodePtr = _DSKT2_memTabList;

    while (listNodePtr != NULL) {

        algList[count] = listNodePtr->memTab[0].base;
        scratchIds[count] = listNodePtr->scratchId;
        listNodePtr  = listNodePtr->next;
        count++;
    }

    Assert_isTrue(count == _numAlgs, (Assert_Id)NULL);
    return (count);
}
