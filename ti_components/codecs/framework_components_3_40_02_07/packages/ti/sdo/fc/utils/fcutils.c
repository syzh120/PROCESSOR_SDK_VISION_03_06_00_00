/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== fcutils.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>

#include "fcutils.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>

extern IRES_Fxns * RMAN_getIresEntry(IALG_Handle alg);
extern IALG_Fxns * RMAN_getIAlgEntry(IRES_Fxns * alg);
extern Int RMAN_getNumResources(IALG_Handle alg, IRES_Fxns * resFxns);
extern Int RMAN_getResman(IALG_Handle alg, IRES_Fxns * resFxns,
        IRESMAN_Fxns ** resmanList);

extern xdc_runtime_IHeap_Handle _DSKT2_heap;

/* TODO: Okay if we reuse the DSKT2 heap ? */
xdc_runtime_IHeap_Handle _FC_heap;

static Void *myMalloc(xdc_runtime_IHeap_Handle heap, SizeT size, SizeT align);
static Void myFree(xdc_runtime_IHeap_Handle heap, Void * addr, SizeT size);


/*
 *  ======== FC_suspend ========
 *  Suspend FC usage by waiting for all algorithms to get deactivated and
 *  then doing a 'real deactivate' of lazily deactivated resources acquired
 *  acquired by all the algorithms.
 *  Leaves the system in a deactivated state.
 */
Void FC_suspend()
{
    int numAlgs = 0;
    IALG_Handle * algList;
    int * scratchIds;
    int i = 0;
    int n = 0;
    IRES_Fxns * resFxns = NULL;
    int numResman = 0;
    IRESMAN_Fxns ** resmanList;
    int numFxns = 0;

    _FC_heap = (xdc_runtime_IHeap_Handle)_DSKT2_heap ;

    numAlgs = DSKT2_getNumAlgs();
    if (0 == numAlgs) {
        return;
    }

    /* Wait for all algs to be DSKT2 - deactivated */
    while (0 != DSKT2_deactivateAll()) {
        Task_yield();
    }

    /* Allocate memory for algList and scratchIds */
    algList = myMalloc(_FC_heap, sizeof(algList) * numAlgs, 0);
    if (algList == NULL) {
        /* error */
    }
    scratchIds = myMalloc(_FC_heap, sizeof(scratchIds) * numAlgs, 0);
    if (scratchIds == NULL) {
        /* error */
    }

    /* Get a list of all algorithms in the system */
    numAlgs = DSKT2_getAlgList(algList, scratchIds);

    for (i = 0; i < numAlgs; i++) {

        /* Activate alg */
        DSKT2_activateAlg(scratchIds[i], algList[i]);

        /* get it's IRES Fxns */
        resFxns = RMAN_getIresEntry(algList[i]);

       if (NULL == resFxns) {
            /* This alg doesn't have any IRES resources,
               deactivate it, and move on to next alg */
            DSKT2_deactivateAlg(scratchIds[i], algList[i]);
            continue;
        }

        numFxns = RMAN_getNumResources(algList[i], resFxns);
        resmanList = myMalloc(_FC_heap, sizeof(IRESMAN_Fxns *) * numFxns, 0);
        if (resmanList == NULL) {
            /* Unable to allocate resmanList, so we can't
             * deactivate the resources. Deactivate the alg
             * and move on to the next one */
            DSKT2_deactivateAlg(scratchIds[i], algList[i]);
            continue;
        }

        /* RMAN_activateAllResources */
        RMAN_activateAllResources(algList[i], resFxns, scratchIds[i]);

        /* Get resman */
        numResman = RMAN_getResman(algList[i], resFxns, resmanList);

        for (n = 0; n < numResman; n++) {
            /* For each resource manager assocaited with each algorithm,
               need to call deactivate resource */
            if (resmanList[n]->deactivateResource != NULL) {
                resmanList[n]->deactivateResource(algList[i], resFxns/* etc*/ );
            }

        }

        myFree(_FC_heap, resmanList, sizeof(IRESMAN_Fxns *) * numFxns);
        resmanList = NULL;

        /* Deactivate these again */
        RMAN_deactivateAllResources(algList[i], resFxns, scratchIds[i]);

        /* De-activate the alg again */
        /* Instead of this, should we do a DSKT2_deactivateAll at the end */
        DSKT2_deactivateAlg(scratchIds[i], algList[i]);

    }

    /* Free memory */
    myFree(_FC_heap, algList, sizeof(algList) * numAlgs);
    myFree(_FC_heap, scratchIds, sizeof(scratchIds) * numAlgs);

    /* This should deactivate everything that was lazily deactivated */
    /* Wait for all algs to be DSKT2 - deactivated */
    while (0 != DSKT2_deactivateAll());
    /* No yield is required here */

}

/*
 *  ======== FC_resume ========
 *  Resume after an FC suspend.
 */

Void FC_resume()
{
}


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


static Void myFree(xdc_runtime_IHeap_Handle heap, Void * addr, SizeT size)
{
    Memory_free(heap, addr, size);
}
