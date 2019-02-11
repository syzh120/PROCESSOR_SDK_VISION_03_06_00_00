/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system_work_queue_if.h>
#include <src/rtos/utils_common/include/utils_mem_if.h>

#define SYSTEM_WORK_QUEUE_TEST_FXN_ID   (0)
#define SYSTEM_WORK_QUEUE_TEST_CMD_ID   (0)

typedef struct {

    UInt32 value;

} System_WorkQueueTestFxnInArgs;

typedef struct {

    UInt32 value;

} System_WorkQueueTestFxnOutArgs;

static UInt32 System_workQueueTestFxn(
                UInt16 workFxnId,
                UInt16 workCmdId,
                Void *pInArgs,
                UInt32 inArgsSize,
                Void *pOutArgs,
                UInt32 outArgsSize);
static Void System_workQueueTestCallback(System_WorkObjId workObjId, Void *pUserObj);
static Void System_workQueueTestExecute(UInt32 dstCpuId, UInt32 numIterations,
        System_WorkQueueTestFxnInArgs *pInArgs,const System_WorkQueueTestFxnOutArgs *pOutArgs,
        System_WorkObjId workObjId);

Void System_workQueueTestFxnsRegister(void);
Void System_workQueueTestRun(void);


static UInt32 System_workQueueTestFxn(
                UInt16 workFxnId,
                UInt16 workCmdId,
                Void *pInArgs,
                UInt32 inArgsSize,
                Void *pOutArgs,
                UInt32 outArgsSize)
{
    System_WorkQueueTestFxnInArgs *pIn;
    System_WorkQueueTestFxnInArgs *pOut;

    pIn = (System_WorkQueueTestFxnInArgs *)pInArgs;
    pOut = (System_WorkQueueTestFxnInArgs *)pOutArgs;

    pOut->value = pIn->value + 1;

    return (UInt32)0U;
}

static Void System_workQueueTestCallback(System_WorkObjId workObjId, Void *pUserObj)
{
    UInt32 *pUInt32 = (UInt32 *)pUserObj;

    (*pUInt32)++;
}

Void System_workQueueTestFxnsRegister(void)
{
    System_workHandlerRegister(SYSTEM_WORK_QUEUE_TEST_FXN_ID, System_workQueueTestFxn);
}

static Void System_workQueueTestExecute(UInt32 dstCpuId, UInt32 numIterations,
        System_WorkQueueTestFxnInArgs *pInArgs,const System_WorkQueueTestFxnOutArgs *pOutArgs,
        System_WorkObjId workObjId)
{
    UInt32 i;
    UInt64 curTime;
    static UInt32 workQueueTestFlag;

    if(System_isProcEnabled(dstCpuId))
    {
        Vps_printf(" SYSTEM: WORKQ: Run Started for [%s] !!!\n", System_getProcName(dstCpuId));

        pInArgs->value = 0;

        workQueueTestFlag = 0;

        System_workSetCallback(workObjId, System_workQueueTestCallback, (Void*)&workQueueTestFlag);

        curTime = Utils_getCurGlobalTimeInUsec();

        for(i=0; i<numIterations; i++)
        {
            System_workSubmit(workObjId, dstCpuId);
            System_workWaitComplete(workObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

            pInArgs->value = pOutArgs->value;

            if(pInArgs->value != (i+1U))
            {
                Vps_printf(" SYSTEM: WORKQ: Failed on iteration %d\n", i);
            }
            if(workQueueTestFlag != (i+1U))
            {
                Vps_printf(" SYSTEM: WORKQ: User Callback Test Failed on iteration %d\n", i);
            }
        }

        curTime = Utils_getCurGlobalTimeInUsec() - curTime;

        Vps_printf(" SYSTEM: WORKQ: Run Done (Total time = %d usec, Per iteration time = %d usec)!!!\n", (UInt32)(curTime), (UInt32)(curTime/numIterations));
    }
}

Void System_workQueueTestRun(void)
{
    System_WorkObjId workObjId;
    System_WorkQueueTestFxnInArgs *pInArgs;
    System_WorkQueueTestFxnOutArgs *pOutArgs;
    UInt32 inArgsSize;
    UInt32 outArgsSize;
    UInt32 numIterations;
    Int32 status;

    Vps_printf(" SYSTEM: WORKQ: Unit Test ... Start !!!\n");
    Vps_printf(" \n");

    /* test case config parameters */
    numIterations = 10000U;

    /* create phase - one time setup */
    inArgsSize = SystemUtils_align(sizeof(System_WorkQueueTestFxnInArgs), SYSTEM_WORK_ARGS_ALIGN);
    outArgsSize = SystemUtils_align(sizeof(System_WorkQueueTestFxnOutArgs), SYSTEM_WORK_ARGS_ALIGN);

    pInArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, inArgsSize, SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pInArgs!=NULL);

    pOutArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, outArgsSize, SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pOutArgs!=NULL);

    status = System_workAllocObj(&workObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(workObjId, pInArgs, inArgsSize);
    System_workSetOutArgs(workObjId, pOutArgs, outArgsSize);
    System_workSetCommand(workObjId, SYSTEM_WORK_QUEUE_TEST_FXN_ID, SYSTEM_WORK_QUEUE_TEST_CMD_ID);

    Vps_printf(" SYSTEM: WORKQ: Create Done !!!\n");

    /* run phase - execute work function */

    System_workQueueTestExecute(SYSTEM_PROC_EVE1, numIterations, pInArgs, pOutArgs, workObjId);
    System_workQueueTestExecute(SYSTEM_PROC_DSP1, numIterations, pInArgs, pOutArgs, workObjId);
    System_workQueueTestExecute(SYSTEM_PROC_DSP2, numIterations, pInArgs, pOutArgs, workObjId);
    System_workQueueTestExecute(SYSTEM_PROC_IPU1_0, numIterations, pInArgs, pOutArgs, workObjId);
    System_workQueueTestExecute(SYSTEM_PROC_IPU1_1, numIterations, pInArgs, pOutArgs, workObjId);

    /* delete phase - free allocated resources */

    System_workFreeObj(&workObjId);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pInArgs, inArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pOutArgs, outArgsSize);

    Vps_printf(" SYSTEM: WORKQ: Delete Done !!!\n");
    Vps_printf(" \n");
    Vps_printf(" SYSTEM: WORKQ: Unit Test ... DONE !!!\n");
}
