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
#include <src/rtos/utils_common/include/utils_tsk.h>
#if defined (BUILD_ARP32)
#include <src/rtos/utils_common/include/utils_idle.h>
#endif

/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
Void Utils_tskMultiMbxMain(UArg arg0, UArg arg1);
Int32 Utils_tskMultiMbxTrigger(Void * pTsk, Int32 timeout);


/**
 *******************************************************************************
 *
 * \brief Multi-mbx Task main
 *
 *        This task is trigger whenever a message is sent to
 *        any of the possible mbx's registers with this task
 *
 * \param arg0         [IN]  Utils_TskMultiMbxHndl *
 * \param arg1         [IN]  NOT USED
 *
 *******************************************************************************
 */
Void Utils_tskMultiMbxMain(UArg arg0, UArg arg1)
{
    Utils_TskMultiMbxHndl *pMultiMbxTsk = NULL;
    Utils_MsgHndl *pMsg;
    Utils_MbxHndl *pMbx;
    Utils_TskHndl *pTskHndl;
    Int32 status;
    UInt32 i;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * MISRAC_WAIVER:
     * Generic Task Handler function expects the argument in UArg format,
     * Task Handle is private argument to this task, so type casting.
     */
    pMultiMbxTsk = (Utils_TskMultiMbxHndl *) arg0;

    UTILS_assert(pMultiMbxTsk != NULL);

    while (1U)
    {
        BspOsal_semWait(pMultiMbxTsk->semTskPend, BSP_OSAL_WAIT_FOREVER);
        if(pMultiMbxTsk->doExitTask)
        {
            /* task exit flag set, break from loop and exit task */
            break;
        }

        /* task is un-pended, see in which que message is recevied
         * starting with highest priority queue
         */
        for(i=0; i<pMultiMbxTsk->numPriQue; i++)
        {
            /* loop until all message's from a priority queue
             * are handled
             */
            while(1)
            {
                pMbx = NULL;
                /* MISRA.CAST.PTR
                 * MISRAC_2004_Rule_11.4
                 * MISRAC_WAIVER:
                 * Generic implementation of queGet requires argument in Ptr *
                 * format, so typecasting.
                 */
                status = Utils_queGet(
                            &pMultiMbxTsk->recvQue[i],
                            (Ptr*)&pMbx,
                            1U,
                            BSP_OSAL_NO_WAIT
                            );

                if(pMbx==NULL)
                {
                    /* nothing more in this queue
                     * goto next queue or pend on semaphore again
                     */
                    break;
                }

                /* recevied message in one of the mbx's, handle it */
                status = Utils_mbxRecvMsg(pMbx, &pMsg, BSP_OSAL_NO_WAIT);
                if (status == SYSTEM_LINK_STATUS_SOK)
                {
                    pTskHndl = (Utils_TskHndl *)pMbx->pTsk;

                    if (pTskHndl->funcMain)
                    {
                        pTskHndl->funcMain(pTskHndl, pMsg);
                    }
                }
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Function to trigger Multi-mbx to process messages
 *
 *        This function is registerd during Utils_tskMultiMbxCreate()
 *        This insert the message box to whom message is sent
 *
 *        into appropiate multi-mbx receive que
 *        A semaphore is set to wakeup the multi-mbx task
 *
 * \param pTsk         [IN]  Utils_TskHndl *
 * \param timeout      [IN]  pend timeout for que put
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
 */
Int32 Utils_tskMultiMbxTrigger(Void * pTsk, Int32 timeout)
{
    Int32 status=0;

    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Message box trigger callback function expects first argument in
     * as void *. This fisr argument is actually Task handle, so type casting.
     * There is a check to make sure that TaskHandle is not null
     */
    Utils_TskHndl *pTskHndl
        = (Utils_TskHndl *)pTsk;
    Utils_TskMultiMbxHndl * pMultiMbxTsk;

    if (NULL != pTskHndl)
    {
        pMultiMbxTsk = (Utils_TskMultiMbxHndl *)pTskHndl->pMultiMbxTsk;

        if (NULL != pMultiMbxTsk)
        {
            status = Utils_quePut(
                        &pMultiMbxTsk->recvQue[pTskHndl->tskPri],
                        (Ptr)&pTskHndl->mbx,
                        (UInt32)timeout);

            BspOsal_semPost(pMultiMbxTsk->semTskPend);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function init's values in multi-mbx task handle
 *
 *        This function MUST be called before calling Utils_tskMultiMbxCreate
 *        The multi-mbx handle init in this function MUST be provided as
 *        as input during Utils_tskMultiMbxCreate().
 *
 *        NOTE, task itself is not created here
 *
 * \param pMultiMbxTsk [OUT] Multi-mbx task handle
 * \param stackAddr    [IN]  Task stack address
 * \param stackSize    [IN]  Task stack size
 * \param tskPri       [IN]  Task priority as defined by BIOS
 * \param numPriQue    [IN]  Number of priorites possible
 *                           when servicing messages
 *                           MUST be <= UTILS_TASK_MULTI_MBX_RECV_QUE_MAX
 * \param tskName      [IN]  Task name
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
 */
Int32 Utils_tskMultiMbxSetupTskHndl(
                        Utils_TskMultiMbxHndl * pMultiMbxTsk,
                        UInt8 *stackAddr,
                        UInt32 stackSize,
                        UInt32 tskPri,
                        UInt32 numPriQue,
                        const char tskName[20U]
        )
{
    memset(pMultiMbxTsk, 0, sizeof(Utils_TskMultiMbxHndl));
    pMultiMbxTsk->doExitTask = (Bool)FALSE;
    pMultiMbxTsk->numRefs = 0;
    pMultiMbxTsk->stackAddr = stackAddr;
    pMultiMbxTsk->stackSize = stackSize;
    pMultiMbxTsk->tskPri = tskPri;
    pMultiMbxTsk->numPriQue = numPriQue;
    UTILS_assert(numPriQue<=UTILS_TASK_MULTI_MBX_RECV_QUE_MAX);
    strncpy(pMultiMbxTsk->tskName, tskName, sizeof(pMultiMbxTsk->tskName) - 1U);
    /* The maximum size of name permitted is 31 characters now.
        In cases where the name was exactly 32 characters, there would
        be no space for the string null terminator.
        Also, if the name was > 32 characters and dosent have a null
        terminator. The destination pMultiMbxTsk->tskName will be a non-null
        terminated string. */
    pMultiMbxTsk->tskName[sizeof(pMultiMbxTsk->tskName) - 1U] = (char)'\0';

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function Create a task which can receive messages from multiple
 *        mail box's
 *
 *        Multi-mbx task gets created when reference count is 0.
 *
 * \param pHndl        [OUT] Task handle
 * \param pMultiMbxTsk [IN]  Multi-mbx task handle, this MUST be setup via
 *                           Utils_tskMultiMbxSetupTskHndl() before calling
 *                           this function
 * \param funcMain     [IN]  Task main,
 *                           Note, this is different from BIOS Task, since
 *                           this function
 *                           is entered ONLY when a message is received.
 * \param tskMultiMbxPri [IN]  Receive que task priority
 *                           0 is higest priority,
 *                           pMultiMbxTsk->numPriQue - 1 is lowest priority.
 *                           Received mailbox are servied in this order
 *                           by the multi-mbx task
 * \param appData      [IN]  Application specific data
 * \param tskAffinity  [IN]  Core affinity for the task
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
 */
Int32 Utils_tskMultiMbxCreate(Utils_TskHndl * pHndl,
                              Utils_TskMultiMbxHndl * pMultiMbxTsk,
                              Utils_TskFuncMain funcMain,
                              UInt32 tskMultiMbxPri,
                              Ptr appData,
                              UInt32 tskAffinity)
{
    Int32 status;
    Utils_MbxCreatePrm mbxCreatePrm;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pMultiMbxTsk != NULL);
    UTILS_assert(funcMain != NULL);
    UTILS_assert(pMultiMbxTsk->numPriQue > 0);
    UTILS_assert(pMultiMbxTsk->numPriQue <= UTILS_TASK_MULTI_MBX_RECV_QUE_MAX);
    UTILS_assert(pMultiMbxTsk->stackAddr != NULL);
    UTILS_assert(pMultiMbxTsk->stackSize != 0);

    memset(pHndl, 0, sizeof(Utils_TskHndl));

    Utils_MbxCreatePrm_Init(&mbxCreatePrm);

    if(tskMultiMbxPri>=pMultiMbxTsk->numPriQue)
    {
        /* if priority is beyond valid range
         * then make it lowest priority
         */
        tskMultiMbxPri = pMultiMbxTsk->numPriQue-1U;
    }

    pHndl->funcMain  = funcMain;
    pHndl->stackSize = 0;
    pHndl->stackAddr = NULL;
    pHndl->tsk = NULL;
    pHndl->appData   = appData;
    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Utils_TskMultiMbxHndl and strunt Utils_TskMultiMbxHndl are same structure,
     * argument to this function is of type Utils_TskMultiMbxHndl and
     * variable is of struct Utils_TskMultiMbxHndl_t type, so typecasting
     */
    pHndl->pMultiMbxTsk = (struct Utils_TskMultiMbxHndl_t*)pMultiMbxTsk;
    pHndl->tskPri    = tskMultiMbxPri;
    pHndl->tskAffinity = tskAffinity;

    mbxCreatePrm.pTsk = pHndl;
    mbxCreatePrm.pFuncMultiMbxTrigger = &Utils_tskMultiMbxTrigger;

    status = Utils_mbxCreate(&pHndl->mbx, &mbxCreatePrm);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if(pMultiMbxTsk->numRefs==0)
    {
        /* Task is not created, create it */

        Int32 i;

        /* create task pend semaphore */
        pMultiMbxTsk->semTskPend = BspOsal_semCreate((Int32)0, (Bool)TRUE);

        UTILS_assert(pMultiMbxTsk->semTskPend != NULL);

        /* create task mbx queue's, one for each priority */
        for(i=0; i<pMultiMbxTsk->numPriQue; i++)
        {
            status = Utils_queCreate(
                        &pMultiMbxTsk->recvQue[i],
                        UTILS_TASK_MULTI_MBX_RECV_QUE_LEN_MAX,
                        pMultiMbxTsk->memRecvQue[i],
                        UTILS_QUE_FLAG_BLOCK_QUE
                        );

            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }

        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to task function pointer. this cannot be avoided as
         * task create function expects function pointer of this type.
         */
        /* create the task itself */
        pMultiMbxTsk->tsk = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)Utils_tskMultiMbxMain,
                                pMultiMbxTsk->tskName,
                                pMultiMbxTsk->tskPri,
                                pMultiMbxTsk->stackAddr,
                                pMultiMbxTsk->stackSize,
                                pMultiMbxTsk,
                                pHndl->tskAffinity
                              );
        UTILS_assert(pMultiMbxTsk->tsk != NULL);

        Utils_prfLoadRegister(pMultiMbxTsk->tsk, pMultiMbxTsk->tskName);
    }

    pMultiMbxTsk->numRefs++;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete the task and its associated mail box.
 *
 *        Multi-mbx task gets delete when reference count reaches 0.
 *
 * \param pHndl        [IN] Task handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
 */
Int32 Utils_tskMultiMbxDelete(Utils_TskHndl * pHndl)
{
    Utils_TskMultiMbxHndl *pMultiMbxTsk;

    Int32 status;
    UInt32 i;

    UTILS_assert(NULL != pHndl);
    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Utils_TskMultiMbxHndl and strunt Utils_TskMultiMbxHndl are same structure,
     * argument to this function is of type Utils_TskMultiMbxHndl and
     * variable is of struct Utils_TskMultiMbxHndl_t type, so typecasting
     */
    pMultiMbxTsk = (Utils_TskMultiMbxHndl *)pHndl->pMultiMbxTsk;
    UTILS_assert(NULL != pMultiMbxTsk);

    pMultiMbxTsk->numRefs--;

    if(pMultiMbxTsk->numRefs == 0U)
    {
        pMultiMbxTsk->doExitTask = (Bool)TRUE;

        /* post semaphore to unblock task */
        BspOsal_semPost(pMultiMbxTsk->semTskPend);

        /* wait for flag to be received and task to be exited */
        BspOsal_sleep(1U);

        Utils_prfLoadUnRegister(pMultiMbxTsk->tsk);

        BspOsal_taskDelete(&pMultiMbxTsk->tsk);

        for(i=0; i<pMultiMbxTsk->numPriQue; i++)
        {
            status = Utils_queDelete(&pMultiMbxTsk->recvQue[i]);
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }

        BspOsal_semDelete(&pMultiMbxTsk->semTskPend);
    }

    Utils_mbxDelete(&pHndl->mbx);

    return SYSTEM_LINK_STATUS_SOK;
}


/* Nothing beyond this point */
