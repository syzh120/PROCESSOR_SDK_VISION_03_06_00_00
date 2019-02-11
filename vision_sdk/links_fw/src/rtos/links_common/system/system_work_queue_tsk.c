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
#include "system_work_queue_if_priv.h"
#include <src/rtos/utils_common/include/utils_que.h>
#if defined (BUILD_ARP32)
#include <src/rtos/utils_common/include/utils_idle.h>
#endif

static void System_workTskMain(UInt32 arg0, UInt32 arg1);

typedef struct {

    BspOsal_TaskHandle task;
    Utils_QueHandle workQueue;
    UInt32 workQueueMem[SYSTEM_WORK_MAX_QUEUE_ELEMENTS];
    Bool isDone;
    Bool isExitDone;
    System_WorkHandler workHandler[SYSTEM_WORK_MAX_WORK_FXNS];

} System_WorkTskObj;

System_WorkTskObj gSystem_workTskObj;

/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * Non-documented pragma directive.
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#ifndef BUILD_A15
#pragma DATA_ALIGN(gSystem_workTaskStack, 32)
#pragma DATA_SECTION(gSystem_workTaskStack, ".bss:taskStackSection:workQueueTsk")
#endif
UInt8 gSystem_workTaskStack[SYSTEM_WORK_TSK_STACK_SIZE]
#ifdef BUILD_A15
__attribute__ ((section(".bss:taskStackSection:workQueueTsk")))
__attribute__ ((aligned(4)))
#endif
;

static void System_workTskMain(UInt32 arg0, UInt32 arg1)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * BSP OSAL main entry function takes UInt32 as argument
     * Need to convert to pointer to retrieve context
     */
    System_WorkTskObj *pTsk = (System_WorkTskObj *)arg0;
    System_Work *pWork;
    System_WorkObjId workObjId;
    UInt16 fxnId, cmdId;
    UInt32 value;
    System_WorkHandler fxns = NULL;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    while(pTsk->isDone==(Bool)FALSE)
    {
        pWork = NULL;

        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * This is a generic queue implementation which supports all dataTypes.
         * This typecasting is necessary.
         */
        status = Utils_queGet(&pTsk->workQueue, (Ptr*)&value, 1U, BSP_OSAL_WAIT_FOREVER);

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            workObjId = (System_WorkObjId)value;

            pWork = System_workGetObj(workObjId);
            if(pWork)
            {
                fxnId = System_workGetFxnId(pWork);
                cmdId = System_workGetCmdId(pWork);

                if(fxnId < SYSTEM_WORK_MAX_WORK_FXNS)
                {
                    fxns = pTsk->workHandler[fxnId];
                    if(fxns)
                    {
                        #ifndef BUILD_ARP32
                        if(pWork->pInArgs)
                        {
                            BspOsal_cacheInv(pWork->pInArgs, pWork->inArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
                        }
                        if(pWork->pOutArgs)
                        {
                            BspOsal_cacheInv(pWork->pOutArgs, pWork->outArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
                        }
                        #endif
                        #if defined (BUILD_ARP32)
                        Utils_idleEnableEveDMA();
                        #endif

                        pWork->status = fxns(fxnId, cmdId, pWork->pInArgs, pWork->inArgsSize, pWork->pOutArgs, pWork->outArgsSize);

                        #if defined (BUILD_ARP32)
                        Utils_idleDisableEveDMA();
                        #endif

                        #ifndef BUILD_ARP32
                        if(pWork->pInArgs)
                        {
                            BspOsal_cacheWbInv(pWork->pInArgs, pWork->inArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
                        }
                        if(pWork->pOutArgs)
                        {
                            BspOsal_cacheWbInv(pWork->pOutArgs, pWork->outArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
                        }
                        #endif
                    }
                }

                if(System_workGetIsAckRequired(pWork))
                {
                    UInt32 cpuId;

                    System_workSetIsAck(pWork, (Bool)TRUE);

                    cpuId = System_workGetWorkObjSrcCpu(workObjId);

                    System_workSendMsg(workObjId, cpuId);
                }
            }
        }
    }
    pTsk->isExitDone = (Bool)TRUE;
}

Int32 System_workTskCreate(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;

    gSystem_workTskObj.isDone = FALSE;
    gSystem_workTskObj.isExitDone = FALSE;

    for(i=0; i<SYSTEM_WORK_MAX_WORK_FXNS; i++)
    {
        gSystem_workTskObj.workHandler[i] = NULL;
    }

    status = Utils_queCreate(
                &gSystem_workTskObj.workQueue,
                SYSTEM_WORK_MAX_QUEUE_ELEMENTS,
                gSystem_workTskObj.workQueueMem,
                UTILS_QUE_FLAG_BLOCK_QUE_GET
            );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    gSystem_workTskObj.task = BspOsal_taskCreate(
                System_workTskMain,
                "System_workTskMain",
                (Int32)SYSTEM_WORK_TSK_PRI,
                gSystem_workTaskStack,
                sizeof(gSystem_workTaskStack),
                &gSystem_workTskObj,
                0
        );
    UTILS_assert(gSystem_workTskObj.task!=NULL);

    return status;
}

Int32 System_workTskDelete(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    gSystem_workTskObj.isDone = (Bool)TRUE;

    /* unblock queue */
    System_workTskQueueWorkObj(SYSTEM_WORK_OBJ_INVALID);
    while(!gSystem_workTskObj.isExitDone)
    {
        BspOsal_sleep(1U);
    }
    BspOsal_taskDelete(&gSystem_workTskObj.task);
    Utils_queDelete(&gSystem_workTskObj.workQueue);

    return status;
}

Int32 System_workTskHandlerRegister(UInt16 workFxnId, System_WorkHandler pHandler)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if(workFxnId < SYSTEM_WORK_MAX_WORK_FXNS)
    {
        gSystem_workTskObj.workHandler[workFxnId] = pHandler;
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

Int32 System_workTskQueueWorkObj(System_WorkObjId workObjId)
{
    Int32 status;
    UInt32 value = (UInt32)workObjId;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic queue implementation and here we need to pass UInt32 value
     * hence this typecast is needed
     */
    status = Utils_quePut(&gSystem_workTskObj.workQueue, (Ptr)value, BSP_OSAL_NO_WAIT);

    return status;
}

