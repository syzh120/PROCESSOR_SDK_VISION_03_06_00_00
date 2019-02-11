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
#include "system_priv_ipc.h"

static Void System_workLock(void);
static Void System_workUnlock(void);
static Int32 System_workResetAllObj(void);
static Void System_workDoCacheOpsBeforeSubmit(System_Work *pWork);
static Void System_workDoCacheOpsAfterAck(System_Work *pWork);

typedef struct {

    BspOsal_SemHandle lock;
    System_WorkIpcObj *pIpcObj;

} System_WorkObj;

System_WorkObj gSystem_workObj;

static Void System_workLock(void)
{
    BspOsal_semWait(gSystem_workObj.lock, BSP_OSAL_WAIT_FOREVER);
}

static Void System_workUnlock(void)
{
    BspOsal_semPost(gSystem_workObj.lock);
}

static Int32 System_workResetAllObj(void)
{
    System_Work *pWorkBase;
    System_Work *pWork;
    UInt32 i;
    UInt32 selfProcId = System_getSelfProcId();
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pWorkBase = System_workGetObj(
                    System_workMakeWorkObjId((UInt16)0, (UInt16)selfProcId)
                        );
    UTILS_assert(pWorkBase!=NULL);

    for(i=0; i < SYSTEM_WORK_MAX_OBJ_PER_CPU; i++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Pointer is accessed as an array.
         * For loop makes sure that the array is never accessed out of bound
         */
        pWork = &pWorkBase[i];
        /* clear work object */
        if(pWork != NULL)
        {
            memset(pWork, 0, sizeof(System_Work));
            System_workSetIsFree(pWork, (Bool)TRUE);
        }
    }

    return status;
}

static Void System_workDoCacheOpsBeforeSubmit(System_Work *pWork)
{
    if(pWork->pInArgs)
    {
        BspOsal_cacheWbInv(pWork->pInArgs, pWork->inArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    }
    if(pWork->pOutArgs)
    {
        BspOsal_cacheWbInv(pWork->pOutArgs, pWork->outArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    }
}

static Void System_workDoCacheOpsAfterAck(System_Work *pWork)
{
    if(pWork->pInArgs)
    {
        BspOsal_cacheInv(pWork->pInArgs, pWork->inArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    }
    if(pWork->pOutArgs)
    {
        BspOsal_cacheInv(pWork->pOutArgs, pWork->outArgsSize, BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    }
}

Int32 System_workInit(void)
{
    gSystem_workObj.lock = BspOsal_semCreate(1, (Bool)TRUE);
    UTILS_assert(gSystem_workObj.lock!=NULL);

    gSystem_workObj.pIpcObj = System_workQGetIpcObj();
    UTILS_assert(gSystem_workObj.pIpcObj!=NULL);

    System_workResetAllObj();

    System_workTskCreate();

    System_workQueueTestFxnsRegister();

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 System_workDeInit(void)
{
    System_workTskDelete();

    BspOsal_semDelete(&gSystem_workObj.lock);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 System_workHandlerRegister(UInt16 workFxnId, System_WorkHandler pHandler)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    status = System_workTskHandlerRegister(workFxnId, pHandler);

    return status;
}

Int32 System_workAllocObj(System_WorkObjId *workObjId, UInt32 allocFlags)
{
    System_WorkObjId workObj;
    System_Work *pWorkBase;
    System_Work *pWork;
    Bool found = FALSE;
    UInt32 i;
    UInt32 selfProcId = System_getSelfProcId();
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWorkBase = System_workGetObj(
                    System_workMakeWorkObjId((UInt16)0, (UInt16)selfProcId)
                        );
    UTILS_assert(pWorkBase!=NULL);

    *workObjId = SYSTEM_WORK_OBJ_INVALID;

    System_workLock();

    for(i=0; i < SYSTEM_WORK_MAX_OBJ_PER_CPU; i++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Pointer is accessed as an array.
         * For loop makes sure that the array is never accessed out of bound
         */
        pWork = &pWorkBase[i];
        if(pWork != NULL)
        {
            if(System_workGetIsFree(pWork))
            {
                found = (Bool)TRUE;
                break;
            }
        }
    }
    if(found)
    {
        status = SYSTEM_LINK_STATUS_SOK;

        workObj = System_workMakeWorkObjId((UInt16)i, (UInt16)selfProcId);

        if(allocFlags & SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM)
        {
            /* create semaphore for ACK post */
            pWork->pSemaphore = BspOsal_semCreate(0, (Bool)TRUE);
            if(pWork->pSemaphore != NULL)
            {
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
        }
        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            /* mark as allocated */
            System_workSetIsFree(pWork, FALSE);
            System_workResetObj(workObj);
            *workObjId = workObj;
            status = SYSTEM_LINK_STATUS_SOK;
        }
    }

    System_workUnlock();

    return status;
}

Int32 System_workFreeObj(System_WorkObjId *workObjId)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    System_workLock();

    pWork = System_workGetObj(*workObjId);

    if(pWork)
    {
        if( System_workGetIsFree(pWork) == FALSE)
        {
            if(pWork->pSemaphore)
            {
                BspOsal_semDelete(&pWork->pSemaphore);
            }
            System_workSetIsFree(pWork, (Bool)TRUE);
            *workObjId = SYSTEM_WORK_OBJ_INVALID;
            status = SYSTEM_LINK_STATUS_SOK;
        }
    }

    System_workUnlock();

    return status;
}

Int32 System_workResetObj(System_WorkObjId workObjId)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        pWork->status = 0;
        System_workSetIsAck(pWork, FALSE);
        System_workSetIsAckRequired(pWork, (Bool)TRUE);
        System_workSetInArgs(workObjId, NULL, 0);
        System_workSetOutArgs(workObjId, NULL, 0);
        System_workSetCommand(workObjId, 0, 0);
        System_workSetCallback(workObjId, NULL, NULL);
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

Int32 System_workSetInArgs(System_WorkObjId workObjId, Void *pInArgs, UInt32 inArgsSize)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        if(  ((inArgsSize     % SYSTEM_WORK_ARGS_ALIGN)== 0) &&

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule_11.3
         * MISRAC_WAIVER:
         * To check alignment need to convert to integer
         */
            (((UInt32)pInArgs % SYSTEM_WORK_ARGS_ALIGN)== 0)
            )
        {
            pWork->pInArgs = pInArgs;
            pWork->inArgsSize = inArgsSize;
            status = SYSTEM_LINK_STATUS_SOK;
        }
    }

    return status;
}

Int32 System_workSetOutArgs(System_WorkObjId workObjId, Void *pOutArgs, UInt32 outArgsSize)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        if(  ((outArgsSize     % SYSTEM_WORK_ARGS_ALIGN)== 0) &&

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule_11.3
         * MISRAC_WAIVER:
         * To check alignment need to convert to integer
         */
            (((UInt32)pOutArgs % SYSTEM_WORK_ARGS_ALIGN)== 0)
            )
        {
            pWork->pOutArgs = pOutArgs;
            pWork->outArgsSize = outArgsSize;
            status = SYSTEM_LINK_STATUS_SOK;
        }
    }

    return status;
}

Int32 System_workSetCommand(System_WorkObjId workObjId, UInt16 workFxnId, UInt16 cmdId)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        System_workMakeFxnIdCmdId(pWork, workFxnId, cmdId);
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

Int32 System_workSetCallback(System_WorkObjId workObjId,
                        System_WorkUserCallback callback, Void *pUserObj)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        pWork->userCallback = callback;
        pWork->pUserObj = pUserObj;
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

Int32 System_workGetStatus(System_WorkObjId workObjId, UInt32 *workStatus)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        *workStatus = pWork->status;
        status = SYSTEM_LINK_STATUS_SOK;
    }
    return status;
}

Int32 System_workSubmit(System_WorkObjId workObjId, UInt32 dstCpuId)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        System_workDoCacheOpsBeforeSubmit(pWork);
        System_workSetIsAck(pWork, FALSE);

        status = System_workSendMsg(workObjId, dstCpuId);
    }
    return status;
}

Int32 System_workWaitComplete(System_WorkObjId workObjId, UInt32 timeout)
{
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    Bool isOk;

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        if(pWork->pSemaphore)
        {
            isOk = BspOsal_semWait(pWork->pSemaphore, timeout);
            if(isOk)
            {
                if(pWork->userCallback==NULL)
                {
                    /* if user callback is registered (NOT NULL),
                     * then cache operations happened before calling user callback,
                     * so dont do it again, cache is in valid state already
                     */
                    System_workDoCacheOpsAfterAck(pWork);
                }
                status = SYSTEM_LINK_STATUS_SOK;
            }
        }
    }

    return status;
}


System_Work *System_workGetObj(System_WorkObjId workObj)
{
    System_Work *pWork = NULL;
    UInt16 workObjInstId, srcCpuId;

    workObjInstId = System_workGetWorkObjInst(workObj);

    if(workObjInstId < SYSTEM_WORK_MAX_OBJ_PER_CPU)
    {
        srcCpuId = System_workGetWorkObjSrcCpu(workObj);
        if(srcCpuId < SYSTEM_PROC_MAX)
        {
            pWork = &gSystem_workObj.pIpcObj->obj[srcCpuId][workObjInstId];
        }
    }
    return pWork;
}

Int32 System_workSendMsg(System_WorkObjId workObjId, UInt32 dstCpuId)
{
    UInt32 selfProcId;
    UInt32 linkId;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    selfProcId = System_getSelfProcId();

    linkId = SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE(
                    dstCpuId,
                    workObjId,
                    SYSTEM_LINK_ID_NOTIFY_TYPE_WORK_QUEUE
            );

    if(selfProcId != dstCpuId)
    {
        status = System_ipcSendNotify(linkId);
    }
    else
    {
        status = System_workMsgHandler(linkId);
    }

    return status;
}

Int32 System_workMsgHandler(UInt32 linkId)
{
    System_WorkObjId workObjId;
    System_Work *pWork;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    workObjId = (System_WorkObjId)SYSTEM_GET_LINK_ID(linkId);

    pWork = System_workGetObj(workObjId);
    if(pWork)
    {
        if(System_workGetIsAck(pWork))
        {
            if(pWork->userCallback)
            {
                System_workDoCacheOpsAfterAck(pWork);
                pWork->userCallback(workObjId, pWork->pUserObj);
            }
            if(pWork->pSemaphore)
            {
                BspOsal_semPost(pWork->pSemaphore);
            }
        }
        else
        {
            status = System_workTskQueueWorkObj(workObjId);
        }
    }

    return status;
}
