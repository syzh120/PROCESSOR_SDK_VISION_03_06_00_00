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
 *  ======== dskt2crea.c ========
 *  DSKT2 API to instantiate an XDAIS algorithm instance.
 *
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_dskt2_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>

#include <ti/xdais/ialg.h>

#include "dskt2.h"
#include "_dskt2.h"
#include <ti/sdo/fc/global/gt_dais.h>

extern __FAR__ Bool ti_sdo_fc_useDNUM;

#ifdef xdc_target__isaCompatible_64P
__FAR__ Bool ti_sdo_fc_dskt2_DSKT2_convertAddr = FALSE;
extern __cregister volatile unsigned int DNUM;
static inline Uns MC_ADDR_LOC_TO_GLOB(Uns loc_addr);
#else
#define MC_ADDR_LOC_TO_GLOB(addr) (addr)
#endif

__FAR__ Int _DSKT2_algReferenceCount = 0;

/*
 *  ======== DSKT2_ALGATTRS ========
 */
__FAR__ DSKT2_AlgAttrs DSKT2_ALGATTRS = {
    NULL,   /**< extHeap */
    FALSE   /**< singleHeap */
};

extern __FAR__ Registry_Desc ti_sdo_fc_dskt2_desc;


/*
 *  ======== DSKT_createAlg ========
 *
 * Creates an instance of a xDAIS algorithm using its IALG interface.
 * Instances created with the same scratch-group Id share the same DARAM and/or
 * SARAM scratch buffers (as mapped to BIOS heaps in configuration).
 * Scratch Group Id: -1 is used to turn OFF scratch sharing for this instance,
 * and allocate all scratch memory persistently.
 *
 * NOTE on RE-ENTRANCY:
 *
 * Since MEM_calloc() cannot be used within a TSK_disable()'d context
 * mutual exclusion needs to be enforced by the application framework
 * when executing this function. All algorithm instances created using
 * the same scratchId must be guaranteed by the
 * framework/application to run mutually exclusively.  This means, we
 * are assuming create phase of xDAIS Socket Nodes at the same node
 * 'priority' cannot be scheduled concurrently.
 */
IALG_Handle DSKT2_createAlg(Int scratchId, IALG_Fxns * fxns,
        IALG_Handle parent, IALG_Params * params)
{
    IALG_Handle     alg;

    _DSKT2_init();

    Log_print4(Diags_ENTRY, "[+E] DSKT2_createAlg> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x)",
            (IArg)scratchId, (IArg)fxns, (IArg)parent, (IArg)params);

    /* Use default DSKT2_AlgAttrs */
    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, NULL);

    Log_print1(Diags_EXIT,"[+X] DSKT2_createAlg> Exit (algHandle=0x%x)",
            (IArg)alg);
    return (alg);
}

/*
 *  ======== DSKT_createAlgExt ========
 *  Create alg with all memory allocated in external memory.
 */
IALG_Handle DSKT2_createAlgExt(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params)
{
    IALG_Handle     alg;
    DSKT2_AlgAttrs  attrs = DSKT2_ALGATTRS;

    _DSKT2_init();

    Log_print4(Diags_ENTRY, "[+E] DSKT2_createAlgExt> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x)",
            (IArg)scratchId, (IArg)fxns, (IArg)parent, (IArg)params);

    attrs.singleHeap = TRUE;

    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, &attrs);

    Log_print1(Diags_EXIT,"[+X] DSKT2_createAlgExt> Exit (algHandle=0x%x)",
            (IArg)alg);

    return (alg);
}

/*
 *  ======== DSKT_createAlg2 ========
 */
IALG_Handle DSKT2_createAlg2(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params, xdc_runtime_IHeap_Handle extHeap)
{
    DSKT2_AlgAttrs  attrs;
    IALG_Handle     alg;

    _DSKT2_init();

    Log_print5(Diags_ENTRY, "[+E] DSKT2_createAlg2> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
            "extHeap=0x%x)",
            (IArg)scratchId, (IArg)fxns, (IArg)parent, (IArg)params,
            (IArg)extHeap);

    Assert_isTrue(extHeap != NULL, (Assert_Id)NULL);

    attrs.singleHeap = FALSE;
    attrs.extHeap = extHeap;

    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, &attrs);

    Log_print1(Diags_EXIT,"[+X] DSKT2_createAlg2> Exit (algHandle=0x%x)",
            (IArg)alg);

    return (alg);
}

/*
 *  ======== DSKT_createAlg3 ========
 */
/* ARGSUSED */
IALG_Handle DSKT2_createAlg3(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params, DSKT2_AlgAttrs *attrs)
{
    IALG_Fxns *fxnsPtr;
    IALG_Handle alg;
    Int numRecs;
    Int sizeofMemTab;
    IALG_MemRec *memTab;
    Int i;
    xdc_runtime_IHeap_Handle extHeap;
    Bool singleHeap;
    Bool retVal = FALSE;
    Int  status;
    Bool scratchUsed = FALSE;

    _DSKT2_init();

    if (attrs == NULL) {
        Log_print4(Diags_ENTRY, "[+E] DSKT2_createAlg3> Enter "
                "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x",
                (IArg)scratchId, (IArg)fxns, (IArg)parent, (IArg)params);
    }
    else {
        Log_print6(Diags_ENTRY, "[+E] DSKT2_createAlg3> Enter "
                "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
                "extHeap=0x%x, singleHeap=%d)",
                (IArg)scratchId, (IArg)fxns, (IArg)parent, (IArg)params,
                (IArg)(attrs->extHeap), (IArg)(attrs->singleHeap));
    }

    if (fxns == NULL) {

        Log_print0(Diags_USER7, "[+7] DSKT2_createAlg3> IALG_Fxns are NULL");

        return (NULL);
    }

    if (attrs == NULL) {
        attrs = &DSKT2_ALGATTRS;

        Log_print2(Diags_USER2,
                "[+2] DSKT2_createAlg3> DSKT2_AlgAttrs extHeap 0x%x and singleHeap "
                "%d", (IArg)(attrs->extHeap), (IArg)(attrs->singleHeap));
    }
    extHeap = attrs->extHeap;
    singleHeap = attrs->singleHeap;

    if (extHeap == NULL) {
        extHeap = _DSKT2_spaceToSeg(IALG_ESDATA);
    }
    Assert_isTrue(extHeap != NULL, (Assert_Id)NULL);

    /* determine size of the memTab structure */
    if (fxns->algNumAlloc != NULL) {
        numRecs = fxns->algNumAlloc();

        Log_print1((Diags_USER4|Diags_USER2),
                "[+4] DSKT2_createAlg3> Num memory recs requested %d",
                (IArg)numRecs);
    }
    else {
        /*
         * Note: as per xDAIS Spec (SPRU360) algNumAlloc() is optional
         * and if it is not implemented, the maximum number of memory
         * records for algAlloc() must be less than IALG_DEFMEMRECS.
         */
        numRecs = IALG_DEFMEMRECS;

        Log_print0(Diags_USER2,
                "[+2] DSKT2_createAlg3> AlgNumAlloc not implemented");
    }

    /* allocate a memTab based on number of records alg specified */
    sizeofMemTab = numRecs * sizeof(IALG_MemRec);

    memTab = Memory_calloc(_DSKT2_heap, sizeofMemTab, 0, NULL);

    if (memTab == NULL) {

        Log_print2(Diags_USER7, "[+7] DSKT2_createAlg3> "
                "memTab allocation failed in memory heap 0x%x size=%d",
                (IArg)_DSKT2_heap, (IArg)sizeofMemTab);

        return (NULL);
    }
    else {
        Log_print2(Diags_USER2,
                "[+2] DSKT2_createAlg3> memTab allocated at 0x%x size=0x%x",
                (IArg)memTab, (IArg)sizeofMemTab);
    }

    /* call alg's algAlloc fxn to fill in memTab[]  */
    numRecs = fxns->algAlloc((IALG_Params *)params, &fxnsPtr, memTab);

    /* allocate memory for alg */
    if (numRecs > 0) {

        Log_print1((Diags_USER4 | Diags_USER2),
                "[+4] DSKT2_createAlg3> Num memory recs requested %d",
                (IArg)numRecs);

        for (i = 0; i < numRecs; i++) {

            Log_print5(Diags_USER4, "[+4] DSKT2_createAlg3> "
                    "Requested memTab[%d]: size=0x%x, align=0x%x, "
                    "space=%s, attrs=%s",
                    (IArg)i, (IArg)(memTab[i].size),
                    (IArg)(memTab[i].alignment),
                    (IArg)(gt_MemSpace(memTab[i].space)),
                    (IArg)(gt_MemAttrs(memTab[i].attrs)));

            if ( memTab[i].attrs == IALG_SCRATCH) {
                scratchUsed = TRUE;
            }
        }

        if (TRUE == scratchUsed) {

            if ((NULL == fxns->algActivate) || (NULL == fxns->algDeactivate)) {
                Log_print0(Diags_USER6 ,
                        "[+6] DSKT2_createAlg3> Scratch Memory requested by "
                        "algorithm, but algActivate, algDeactivate functions "
                        "not implemented.");
            }
        }

        if (singleHeap) {

            Log_print1(Diags_USER4 | Diags_USER2,
                    "[+4] DSKT2_createAlg3> Requested all memory in external memory"
                    " space %d", (IArg)IALG_ESDATA);

            /* Change all memTab space fields to IALG_ESDATA */
            for (i = 0; i < numRecs; i++) {
                memTab[i].space = IALG_ESDATA;
            }
        }

        if (!(retVal = _DSKT2_assignInstanceMemory(scratchId, memTab, numRecs,
            extHeap))) {

            Log_print0(Diags_USER7, "[+7] DSKT2_createAlg3> "
                    "Instance memory allocation failed");
        }
        else {

            for(i = 0; i < numRecs; i++) {

    /* TODO:- Platform support should do this */
                if (ti_sdo_fc_useDNUM) {
                    memTab[i].base = (void *)MC_ADDR_LOC_TO_GLOB(
                            (Uns)memTab[i].base);
                }


                Log_print6(Diags_USER4,"[+4] DSKT2_createAlg3>"
                        " Allocated memTab[%d]: base=0x%x, size=0x%x, "
                        "align=0x%x, space=%s, attrs=%s",
                        (IArg)i, (IArg)(memTab[i].base),
                        (IArg)(memTab[i].size), (IArg)(memTab[i].alignment),
                        (IArg)(gt_MemSpace(memTab[i].space)),
                        (IArg)(gt_MemAttrs(memTab[i].attrs)));
            }
        }
    }
    else {
        /* Number of mem recs <= 0 */

        Log_print1(Diags_USER7, "[+7] DSKT2_createAlg3> "
                "algAlloc returned numRecs=%d", (IArg)numRecs);
    }

    /* Free memTab and return if memory was not assigned. */
    if (retVal == FALSE) {
        Memory_free(_DSKT2_heap, memTab, sizeofMemTab);
        Log_print2(Diags_USER2,
                "[+2] DSKT2_createAlg3> memTab memory freed from 0x%x, size=%d",
                (IArg)memTab, (IArg)sizeofMemTab);
        return (NULL);
    }

    /* set alg object handle, and set instance's function pointer */
    alg = ((IALG_Handle)memTab[0].base);
    alg->fxns = fxns;

    /* stash away memTab (to an ext.mem queue) til delete phase */
    if (!_DSKT2_enqueueMemTab(_DSKT2_heap, memTab, sizeofMemTab,
                numRecs, extHeap, scratchId)) {

        /* if 'enqueue' fails abort create phase. */

        Log_print0(Diags_USER7, "[+7] DSKT2_createAlg3> enqueue memTab failed");

        /* Can't call DSKT2_freeAlg() since memTab was not enqueued. */
        _DSKT2_freeInstanceMemory(scratchId, memTab, numRecs, extHeap);

        Log_print0(Diags_USER4, "[+4] DSKT2_createAlg3> "
                "Freeing algorithm memory");

        Memory_free(_DSKT2_heap, memTab, sizeofMemTab);

        Log_print0(Diags_USER7, "[+7] DSKT2_createAlg3> Enqueue memtab failed");

        Log_print1(Diags_EXIT,"[+X] DSKT2_createAlg3> Exit (algHandle=0x%x)",
                (IArg)alg);

        return (NULL);
    }


    /* call alg initialize function with the memory it requested */
    /* if algInit successful return the alg object's handle */
    status = fxns->algInit(alg, memTab, NULL, (IALG_Params *)params) ;
    if (status == IALG_EOK) {

        Log_print0(Diags_USER4, "[+4] DSKT2_createAlg3> "
                "Algorithm init successful.");

        if (_DSKT2_createCallbackFxn != NULL) {
            _DSKT2_createCallbackFxn(alg, memTab, numRecs, scratchId);
        }

        Log_print1(Diags_EXIT,"[+X] DSKT2_createAlg3> Exit (algHandle=0x%x)",
                (IArg)alg);

        _DSKT2_algReferenceCount++;

        return ((IALG_Handle)alg);
    }
    else {

        Log_print1(Diags_USER7, "[+7] DSKT2_createAlg3> algInit call failed %d",
                (IArg)status);

        /*
         * Call freeAlg to free all instance memory, saved memTab recs
         * and maintain the shared scratch data structures.
         */
        DSKT2_freeAlg(scratchId, (IALG_Handle) alg);
    }

    Log_print0(Diags_EXIT, "[+X] DSKT2_createAlg3> Exit (algHandle=NULL)");

    return (NULL);
}


#ifdef xdc_target__isaCompatible_64P
static inline Uns MC_ADDR_LOC_TO_GLOB(Uns loc_addr)
{

   Uns tmp = loc_addr;


   if ((tmp & 0xFF000000) == 0) {

        /* Need to keep track that addresses are being converted */
        ti_sdo_fc_dskt2_DSKT2_convertAddr = TRUE;

        /* TODO: This flag assumes all internal addresses (for this core) are
           either defined as local or chip specific, cannot have a
           mix-n-match */

        return ((1 << 28) | (DNUM << 24) | tmp);
    }
    else {
        return loc_addr;
    }
}
#endif
