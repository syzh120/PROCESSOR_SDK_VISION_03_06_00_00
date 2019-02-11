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
 *  ======== dskt2_yield.c ========
 *  Implementation of RMAN's DSKT2 dependent yield function
 *  This function provides support for cooperative preemption. Algorithms can
 *  call the yield function (provided to them through their IRES handle) when
 *  they want to yield to another algorithm of same (if configured) or higher
 *  priority algorithm.
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_dskt2_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/dskt2/dskt2_lock.h>

/**
 *  @brief      Yield Arguments passed to the algorithms that support DSKT2
 *              yield. These arguments are used by the yield function
 *              set/get context and release/acquire locks for a particular
 *              scratch group.
 */
typedef struct DSKT2_YieldArgs {

    /*
     *  @brief      groupId of the resource
     */
    Int groupId;

    /*
     *  @brief      Flag indicating if same-priority yields should occur.
     */
    Bool yieldFlag;

} DSKT2_YieldArgs;


/* Array holding yield functions for each scratch group */
__FAR__ static DSKT2_YieldArgs _yieldArgs[DSKT2_NUM_SCRATCH_GROUPS + 1] = {{0,FALSE},
        {1, FALSE}, {2, FALSE}, {3, FALSE}, {4, FALSE}, {5, FALSE}, {6, FALSE},
        {7, FALSE}, {8, FALSE}, {9, FALSE}, {10, FALSE}, {11, FALSE},
        {12, FALSE}, {13, FALSE}, {14, FALSE}, {16, FALSE}, {17, FALSE},
        {18, FALSE},{19, FALSE}, {-1, FALSE}};

Void DSKT2_contextRelease(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

Void DSKT2_contextAcquire(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

extern Registry_Desc ti_sdo_fc_dskt2_desc;


/*
 *  ======== DSKT2_yield ========
 *  Yields execution to another algorithm of higher or same (if configured)
 *  priority.
 *  Currently only supports yield of ALL resources.
 */
/* ARGSUSED */
Void DSKT2_yield(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)
{
    Log_print3(Diags_ENTRY, "[+E] DSKT2_yield> Enter "
            "(resource=%d, algYieldContext=0x%x, yieldArgs=0x%x)",
            (IArg)resource, (IArg)algYieldContext, (IArg)yieldArgs);

    if (NULL == algYieldContext) {

        Log_print0(Diags_USER4, "[+4] DSKT2_yield> Yield context is NULL, "
                "not yielding..");

        Log_print0(Diags_EXIT, "[+X] DSKT2_yield> Exit");

        return;
    }

    DSKT2_contextRelease(resource, algYieldContext, yieldArgs);
    DSKT2_contextAcquire(resource, algYieldContext, yieldArgs);

    Log_print0(Diags_EXIT, "[+X] DSKT2_yield> Exit");
}

/*
 *  ======== DSKT2_contextRelease ========
 */
Void DSKT2_contextRelease(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)
{
    Int groupId;

    DSKT2_YieldArgs * args = (DSKT2_YieldArgs *)yieldArgs;

    Log_print3(Diags_ENTRY, "[+E] DSKT2_contextRelease> Enter "
            "(resource=%d, algYieldContext=0x%x, yieldArgs=0x%x)",
            (IArg)resource, (IArg)algYieldContext, (IArg)yieldArgs);

    Assert_isTrue(IRES_ALL == resource, (Assert_Id)NULL);

    groupId = args->groupId;
    Assert_isTrue(groupId < DSKT2_NUM_SCRATCH_GROUPS, (Assert_Id)NULL);

    DSKT2_setContext(groupId, algYieldContext);

    Log_print2(Diags_USER4, "[+4] DSKT2_contextRelease> Group Id %d "
            "yielding current context 0x%x",
            (IArg)groupId, (IArg)algYieldContext);

    Log_print1(Diags_USER4, "[+4] DSKT2_contextRelease> Group Id %d "
            "releasing lock", (IArg)groupId);

    /* Release group lock */
    DSKT2_releaseLock(groupId);

    /*
     * Depending on what kind of argument is supplied do yield or not
     */
    if (args->yieldFlag) {

        Log_print1(Diags_USER4, "[+4] DSKT2_contextRelease> Group Id "
                "%d Yielding to same priority task", (IArg)groupId);

        /* TODO:- How do we make this generic ? Could try Thread_sleep(0); */
        Task_yield();
    }

    Log_print0(Diags_EXIT, "[+X] DSKT2_contextRelease> Exit");
}

Void DSKT2_contextAcquire(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)
{
    IRES_YieldContextHandle yieldingContext;
    Int groupId;
    DSKT2_YieldArgs * args = (DSKT2_YieldArgs *)yieldArgs;

    groupId = args->groupId;
    Assert_isTrue(groupId < DSKT2_NUM_SCRATCH_GROUPS, (Assert_Id)NULL);

    DSKT2_acquireLock(groupId);

    yieldingContext = DSKT2_getContext(groupId);

    Log_print2(Diags_USER4, "[+4] DSKT2_contextAcquire> Group Id %d "
            "acquired lock, yieldingContext 0x%x",
            (IArg)groupId, (IArg)yieldingContext);

    if (yieldingContext != NULL) {

            /*
             * Could have been a yield to same priority task
             */
            if (yieldingContext->algHandle != algYieldContext->algHandle) {

                /*
                 * Yield to same priority task occured and a yield back happened
                 * so context is not NULL, save their context and restore own.
                 */
                Log_print2(Diags_USER4, "[+4] DSKT2_contextAcquire> "
                        "Yielded to same priority task, Save context of "
                        "yielding task 0x%x, restore own context 0x%x",
                        (IArg)yieldingContext, (IArg)algYieldContext);

                /* TODO: Could these functions be NULL */
                if (NULL != yieldingContext->contextSave) {
                    yieldingContext->contextSave(yieldingContext->algHandle,
                            yieldingContext->contextArgs);
                }

                if (NULL != algYieldContext->contextRestore) {
                    algYieldContext->contextRestore(algYieldContext->algHandle,
                            algYieldContext->contextArgs);
                }
            }
    }
    else {

        /*
         * Yielding context is NULL, so context switch occured and task ran to
         * completion
         */

        /*
         * Make sure the algorithm is truly deactivated, so that if it is
         * activated again, we don't trample its context.
         */

#ifndef DSKT2_DISABLELAZYD
        DSKT2_deactivateAll();
#endif

        /* Restore own context */
         Log_print1(Diags_USER4, "[+4] DSKT2_contextAcquire> "
                 "Previously yielded-to task, ran to completion. Restore own "
                 "context 0x%x", (IArg)algYieldContext);

         if (NULL != algYieldContext->contextRestore) {
            algYieldContext->contextRestore(algYieldContext->algHandle,
                    algYieldContext->contextArgs);
         }
    }

    Log_print1(Diags_USER4, "[+4] DSKT2_contextAcquire> Yielding "
            "context set to NULL for group Id %d", (IArg)groupId);

    DSKT2_setContext(groupId, NULL);

    Log_print0(Diags_EXIT, "[+X] DSKT2_contextAcquire> Exit");
}

IRES_YieldArgs DSKT2_getYieldArgs(Int scratchId)
{
    int index = scratchId;
    Assert_isTrue(scratchId < DSKT2_NUM_SCRATCH_GROUPS, (Assert_Id)NULL);

    if (index == -1) {
        index = DSKT2_NUM_SCRATCH_GROUPS;
    }

    return ((IRES_YieldArgs)(&_yieldArgs[index]));
}


IRES_YieldArgs DSKT2_setYieldArgs(Int scratchId, Bool yieldFlag)
{
    int index = scratchId;
    Assert_isTrue(scratchId < DSKT2_NUM_SCRATCH_GROUPS, (Assert_Id)NULL);

    if (index == -1) {
        index = DSKT2_NUM_SCRATCH_GROUPS;
    }

    _yieldArgs[index].yieldFlag = yieldFlag;


    return ((IRES_YieldArgs )(&_yieldArgs[index]));
}
