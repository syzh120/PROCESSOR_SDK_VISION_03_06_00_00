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

/**
 *******************************************************************************
 * \file system_ipc_msgq.c
 *
 * \brief  This file implements the function for the IPC message queue
 *         functionality
 *
 *         This files implements message queue functions. It wraps the
 *         IPC message queue functionality under helper function. It also
 *         performs book keeping like allocating and freeing up of messages.
 *         Its also creates queue for free message queues.
 *
 * \version 0.0 (Jun 2013) : [KC] First version taken from DVR RDK and
 *                                cleaned up for Vision_sdk
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

Int32 System_ipcMsgQTskCreate(void);

Int32 System_ipcMsgQTskDelete(void);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gSystem_tskMsgQStack, 32)
#pragma DATA_SECTION(gSystem_tskMsgQStack, ".bss:taskStackSection")
UInt8 gSystem_tskMsgQStack[SYSTEM_MSGQ_TSK_STACK_SIZE];

/**
 *******************************************************************************
 *
 * \brief   Create task for receiving IPC messages.
 *
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcMsgQTskCreate(void)
{
    Int32 status;

    gSystem_ipcObj.msgQLock = BspOsal_semCreate(1, (Bool)TRUE);
    UTILS_assert(gSystem_ipcObj.msgQLock != NULL);

    gSystem_ipcObj.msgQAck = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(gSystem_ipcObj.msgQAck != NULL);

    status = Utils_queCreate(
                &gSystem_ipcObj.msgQLocalQ,
                SYSTEM_IPC_MSGQ_MAX_ELEMENTS,
                gSystem_ipcObj.msgQLocalQueMem,
                UTILS_QUE_FLAG_BLOCK_QUE
                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Create task
     */
    gSystem_ipcObj.msgQTask = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)System_ipcMsgQTaskMain,
                                "System_ipcMsgQTaskMain",
                                (Int32)SYSTEM_MSGQ_TSK_PRI,
                                gSystem_tskMsgQStack,
                                sizeof(gSystem_tskMsgQStack),
                                NULL,
                                UTILS_TSK_AFFINITY_CORE0);
    /* MISRA.CAST.FUNC_PTR
     * MISRAC_2004 Rule_11.1
     * MISRAC_WAIVER:
     * Valid type-casting from function pointer to function pointer.
     */
    UTILS_assert(gSystem_ipcObj.msgQTask != NULL);

    {
        status = Utils_prfLoadRegister(gSystem_ipcObj.msgQTask, "SYSTEM_MSGQ");
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Message handler called from Notify handler
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
void System_ipcMsgQHandler(UInt32 payload)
{
    Uint32 type = SYSTEM_LINK_ID_GET_NOTIFY_TYPE(payload);

    if( type == SYSTEM_LINK_ID_NOTIFY_TYPE_MSG_ACK)
    {
        BspOsal_semPost(gSystem_ipcObj.msgQAck);
    }
    else if( type == SYSTEM_LINK_ID_NOTIFY_TYPE_MSG)
    {
        UInt32 procId = SYSTEM_GET_LINK_ID(payload);

        Utils_quePut(&gSystem_ipcObj.msgQLocalQ,
                    (Ptr)procId,
                     0);
                    /*
                    * MISRA.CAST.PTR_TO_INT
                    * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
                    * KW State: Defer -> Waiver -> Case by case
                    *
                    */
    }
    else
    {
        /* To avoid misra C
        will never enter here*/
    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief   Delete task created for receiving IPC messages.
 *
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcMsgQTskDelete(void)
{
    Vps_printf(" SYSTEM: IPC MsgQ Task Delete in progress !!!\n");

    /* unblock task */
    Utils_quePut(&gSystem_ipcObj.msgQLocalQ,
                    (Ptr)SYSTEM_PROC_MAX,
                    BSP_OSAL_WAIT_FOREVER);
    /*
    * MISRA.CAST.PTR_TO_INT
    * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
    * KW State: Defer -> Waiver -> Case by case
    *
    */

    /* wait for command to be received and task to be exited */
    BspOsal_sleep(1U);

    Utils_prfLoadUnRegister(gSystem_ipcObj.msgQTask);

    BspOsal_taskDelete(&gSystem_ipcObj.msgQTask);

    BspOsal_semDelete(&gSystem_ipcObj.msgQLock);
    BspOsal_semDelete(&gSystem_ipcObj.msgQAck);
    Utils_queDelete(&gSystem_ipcObj.msgQLocalQ);

    Vps_printf(" SYSTEM: IPC MsgQ Task Delete DONE !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Initialize the message queue sub-system.
 *
 *          Local processor creates message queues. All remote processors
 *          open the message queues of remote processors. Heap is create and
 *          registered with message queue. This is requirement of message Q.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcMsgQInit(void)
{
    System_ipcMsgQTskCreate();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   De-Initialize the message queue sub-system.
 *
 *          Local processor creates message queues. All remote processors
 *          open the message queues of remote processors. Heap is create and
 *          registered with message queue. This is requirement of message Q.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcMsgQDeInit(void)
{
    System_ipcMsgQTskDelete();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Task for receiving the messages on the local processor from
 *          remote processor.
 *
 *          Messages from the remote processors are received by this tasks.
 *          After that messages will be directed to tasks on local processors
 *          for which they are intended.
 * \param arg0 Reserved
 * \param arg1 Reserved
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Void System_ipcMsgQTaskMain(UArg arg0, UArg arg1)
{
    UInt32 prmSize;
    SystemIpcMsgQ_Msg *pMsgCommon;
    UInt32 procId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Void *pPrm;
    volatile UInt32 readValue;

    while (1)
    {
        status =
            Utils_queGet(&gSystem_ipcObj.msgQLocalQ, (Ptr *) &procId,
                         1U,
                         BSP_OSAL_WAIT_FOREVER);
        /*
        * MISRA.CAST.PTR
        * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
        * and a different pointer to object type
        * KW State: Defer -> Waiver -> Case by case
        */

        if(procId == SYSTEM_PROC_MAX )
        {
            break;
        }

        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" MSGQ: MsgQ get failed (procId=%d)!!!\n", procId);
            status = SYSTEM_LINK_STATUS_EFAIL;
        }

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            pMsgCommon = (SystemIpcMsgQ_Msg *)System_ipcGetMsg(procId);

            if(pMsgCommon==NULL)
            {
                Vps_printf(" MSGQ: MsgQ get failed (procId=%d) !!!\n", procId);
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
        }

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            if (pMsgCommon->waitAck!=1)
            {
                Vps_printf(" MSGQ: Invalid message, message MUST have ACK flag set (procId=%d)!!!\n", procId);
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
        }

        #ifdef A15_TARGET_OS_LINUX
            #ifdef BUILD_M4
        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            if(SYSTEM_LINK_ID_TEST_ROUTE_BIT_TRUE(pMsgCommon->linkId))
            {
                /* A15 message, clear the route bit and forward the message */
                SYSTEM_LINK_ID_CLEAR_ROUTE_BIT(pMsgCommon->linkId);

                #ifdef SYSTEM_IPC_MSGQ_DEBUG
                Vps_printf
                    (" MSGQ: Received command [0x%04x] (prmSize = %d)"
                     " for [%s][%02d] (waitAck=%d)  from [%s] .. forwarding it !!!\n",
                     pMsgCommon->cmd, pMsgCommon->prmSize,
                     System_getProcName(SYSTEM_GET_PROC_ID(pMsgCommon->linkId)),
                     SYSTEM_GET_LINK_ID(pMsgCommon->linkId), pMsgCommon->waitAck,
                     System_getProcName(procId)
                     );
                #endif
                /* Route bit can is only set by A15,
                 * hence source CPU is hard coded to A15
                 */

                status =
                    System_ipcSendNotify(
                        SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE
                            (
                                SYSTEM_GET_PROC_ID(pMsgCommon->linkId), /* destination CPU */
                                SYSTEM_PROC_A15_0, /* source CPU */
                                SYSTEM_LINK_ID_NOTIFY_TYPE_MSG /* ACK type */
                            )
                        );

                UTILS_assert (status == SYSTEM_LINK_STATUS_SOK);
                status = SYSTEM_LINK_STATUS_EFAIL;
                /* setting status = efail to continue to Utils_queGet
                   msg routing to eve is taken care by ipu itself */
            }
        }
            #endif
        #endif
        if(status == SYSTEM_LINK_STATUS_SOK)
        {
#ifdef SYSTEM_IPC_MSGQ_DEBUG
        Vps_printf
            (" MSGQ: Received command [0x%04x] (prmSize = %d)"
             " for [%s][%02d] (waitAck=%d) from [%s] \n",
             pMsgCommon->cmd, pMsgCommon->prmSize,
             System_getProcName(SYSTEM_GET_PROC_ID(pMsgCommon->linkId)),
             SYSTEM_GET_LINK_ID(pMsgCommon->linkId), pMsgCommon->waitAck,
             System_getProcName(procId)
             );
#endif

            prmSize = pMsgCommon->prmSize;
            pPrm = SystemIpcMsgqPayloadPtr(pMsgCommon);
           /*
            * MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
            * KW State: Defer -> Waiver -> Case by case
            *
            */

            if (pMsgCommon->cmd == SYSTEM_CMD_GET_INFO)
            {
                UTILS_assert(prmSize == sizeof(System_LinkInfo));

                pMsgCommon->status =
                    System_linkGetInfo_local(pMsgCommon->linkId, pPrm);
            }
            else
            {
                pMsgCommon->status = System_linkControl_local(pMsgCommon->linkId,
                                                              pMsgCommon->cmd,
                                                              pPrm,
                                                              prmSize,
                                                              pMsgCommon->waitAck);

            }

            /* dummay read to ensure, previous write to shared memory is complete */
            readValue = pMsgCommon->status;

            if (pMsgCommon->waitAck)
            {
#ifdef SYSTEM_IPC_MSGQ_DEBUG
            Vps_printf
                (" MSGQ: Acked command [0x%04x] (prmSize = %d)"
                 " for [%s][%02d] to [%s] (waitAck=%d)\n",
                 pMsgCommon->cmd, pMsgCommon->prmSize,
                 System_getProcName(SYSTEM_GET_PROC_ID(pMsgCommon->linkId)),
                 SYSTEM_GET_LINK_ID(pMsgCommon->linkId),
                 System_getProcName(procId),
                 pMsgCommon->waitAck
                 );
#endif

                status =
                    System_ipcSendNotify(
                        SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE
                            (
                                procId, /* destination CPU */
                                System_getSelfProcId(), /* source CPU */
                                SYSTEM_LINK_ID_NOTIFY_TYPE_MSG_ACK /* ACK type */
                            )
                        );


                UTILS_assert (status == SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                UTILS_assert((Bool)FALSE);
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Helper function to send messages to other links.
 *
 *          Allocates the message from free queue and send it to the link
 *          also waits for the acknowledgement for the message.
 *
 * \param  linkId    [IN] LinkId for which message is intended
 * \param  cmd       [IN] Command for message
 * \param  pPrm      [IN] Message parameter
 * \param  prmSize   [IN] Size of parameter
 * \param  waitAck   [IN] If True wait till ack is received, else proceed
 *                        without ack.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcMsgQSendMsg(UInt32 linkId, UInt32 cmd, Void * pPrm,
                            UInt32 prmSize, Bool waitAck)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    SystemIpcMsgQ_Msg *pMsgCommon;
    UInt32 procId;
    Void *pMsgPrm;
    volatile UInt32 readValue;
    UInt32 timeout;
    Bool semStatus;

    if (waitAck != (Bool)TRUE)
    {
        Vps_printf(" MSGQ: Warning!!! : Forcing waitAck = TRUE as waitAck ="
                   " FALSE is not supported."
                   "Fix send cmd [0x%x] to linkId [0x%x",cmd,linkId);
        waitAck = (Bool)TRUE;
    }

    UTILS_assert((Bool)TRUE == waitAck);

    if(prmSize > (SYSTEM_IPC_MSG_SIZE_MAX - sizeof(SystemIpcMsgQ_Msg)))
    {
        Vps_printf(" MSGQ: Parameter size of %d B is greater than max possible"
                   " parameter size of %d B !!!"
                   , prmSize, (UInt32)(SYSTEM_IPC_MSG_SIZE_MAX - sizeof(SystemIpcMsgQ_Msg)));
        UTILS_assert((Bool)FALSE);
    }

    procId = SYSTEM_GET_PROC_ID(linkId);

    UTILS_assert(procId < SYSTEM_PROC_MAX);

    BspOsal_semWait(gSystem_ipcObj.msgQLock, BSP_OSAL_WAIT_FOREVER);

    pMsgCommon = (SystemIpcMsgQ_Msg *)System_ipcGetMsg(System_getSelfProcId());
    /*
    * MISRA.CAST.PTR
    * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
    * and a different pointer to object type
    * KW State: Defer -> Waiver -> Case by case
    */

    UTILS_assert(pMsgCommon != NULL);

    if ((prmSize > 0) && (pPrm != NULL))
    {
        pMsgPrm = SystemIpcMsgqPayloadPtr(pMsgCommon);
        memcpy(pMsgPrm, pPrm, prmSize);
    }
     /*
      * MISRA.CAST.PTR_TO_INT
      * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
      * KW State: Defer -> Waiver -> Case by case
      *
      */
    if(pMsgCommon != NULL)
    {
        pMsgCommon->linkId = linkId;
        pMsgCommon->prmSize = prmSize;
        pMsgCommon->waitAck = (UInt32)waitAck;
        pMsgCommon->status = SYSTEM_LINK_STATUS_SOK;
        pMsgCommon->cmd = cmd;

        /* Dummy read to ensure previous writes to shared memory are complete */
        readValue = pMsgCommon->cmd;

    #ifdef SYSTEM_IPC_MSGQ_DEBUG
        Vps_printf
            (" MSGQ: Sending command [0x%04x] (prmSize = %d)"
             " to [%s][%02d] (waitAck=%d)\n",
             pMsgCommon->cmd, pMsgCommon->prmSize,
             System_getProcName(SYSTEM_GET_PROC_ID(pMsgCommon->linkId)),
             SYSTEM_GET_LINK_ID(pMsgCommon->linkId), pMsgCommon->waitAck);
    #endif

    #ifdef A15_TARGET_OS_LINUX
        #ifdef BUILD_ARP32
        /* IPU and DSPs should never call this function directly
         * They must use System_ipcSendMsg()
         */
        if(procId == SYSTEM_PROC_A15_0)
        {
            /* Set route bit and send it to IPU1 */
            SYSTEM_LINK_ID_SET_ROUTE_BIT(pMsgCommon->linkId);
            procId = SYSTEM_IPU_PROC_PRIMARY;
        }
        #endif
    #endif
    }

    /* clear any pending ACK's */
    BspOsal_semWait(gSystem_ipcObj.msgQAck, BSP_OSAL_NO_WAIT);

    status =
        System_ipcSendNotify(
            SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE
                (
                    procId, /* destination CPU */
                    System_getSelfProcId(), /* source CPU */
                    SYSTEM_LINK_ID_NOTIFY_TYPE_MSG /* message type */
                )
            );

    if (status != 0)
    {
        Vps_printf(" MSGQ: MsgQ put for [%s] failed !!!\n",
                   System_getProcName(procId));
        BspOsal_semPost(gSystem_ipcObj.msgQLock);
        if(System_getCoreState(procId) != SYSTEM_CORE_STATE_ACTIVE)
        {
            /* We might enter if a expired core is part of the use-case.
             * Don't return error in this case. This ensures use-cases can
             * still stop/start without any asserts.
             * Required for RTI_INCLUDE scenarios.
             */
            Vps_printf(" MSGQ: Not returning error since core is dead !!!\n");
            status = SYSTEM_LINK_STATUS_SOK;
            pMsgCommon = NULL;
        }
    }

    if((status == SYSTEM_LINK_STATUS_SOK) && (pMsgCommon != NULL))
    {
        if (waitAck)
        {
            /* Instead of using BSP_OSAL_WAIT_FOREVER, we use a large time-out
             * of 1 second. This is useful for RTI/WWDT use-cases, where
             * a core may not send an ACK after WWDT expiry.
             * This allows the system to continue and not hang waiting on an
             * ACK which will never come.
             */
            do
            {
                timeout = 1000U; /* Time-out of 1 sec for semWait */
                semStatus =
                    BspOsal_semWait(gSystem_ipcObj.msgQAck, timeout);
                if(semStatus != (Bool)TRUE)
                {
                    if(System_getCoreState(procId) != SYSTEM_CORE_STATE_ACTIVE)
                    {
                        Vps_printf(" MSGQ: Forcing ACK for dead core !!\n");
                        semStatus = (Bool)TRUE;
                        /* Force pMsgCommon to NULL to avoid further
                         * processing.
                         * Required for RTI_INCLUDE scenarios.
                         */
                        pMsgCommon = NULL;
                        break;
                    }
                }
            }while(semStatus != (Bool)TRUE);

            if(semStatus == (Bool)TRUE)
            {
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is error situation and should never execute.
            */
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf(" MSGQ: MsgQ Ack get from [%s] failed !!!\n",
                            System_getProcName(procId));
                BspOsal_semPost(gSystem_ipcObj.msgQLock);
            }
            else
            {
                /* pMsgCommon might be forced to NULL in case core is not
                 * active
                 */
                if(NULL != pMsgCommon)
                {
                    if ((prmSize > 0) && (pPrm != NULL))
                    {
                        pMsgPrm = SystemIpcMsgqPayloadPtr(pMsgCommon);
                        memcpy(pPrm, pMsgPrm, prmSize);
                    }

                    status = pMsgCommon->status;

#ifdef SYSTEM_IPC_MSGQ_DEBUG
                    Vps_printf
                        (" MSGQ: Recvd ack for command [0x%04x] (prmSize = %d)"
                         " form [%s][%02d] (waitAck=%d)\n",
                         pMsgCommon->cmd, pMsgCommon->prmSize,
                         System_getProcName(
                            SYSTEM_GET_PROC_ID(pMsgCommon->linkId)),
                         SYSTEM_GET_LINK_ID(pMsgCommon->linkId),
                         pMsgCommon->waitAck);
#endif
                }
            }
            BspOsal_semPost(gSystem_ipcObj.msgQLock);
        }
    }
    return status;
}
