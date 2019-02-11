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
 * \file utils_mbx.c
 *
 * \brief  APIs from this file are used to exchange messages between two
 *         tasks in the links and chains examples.
 *
 *         A message consists of a 32-bit command and optional 32-bit parameter
 *         value.
 *
 *         The 32-bit command is defined by the user.
 *
 *         The 32-bit parameter could inturn point to a bigger data structure
 *         as defined by user.
 *
 *         The APIs allow a user to send a message and wait for ACK before
 *         proceeding further.
 *
 *         Internally message passing is implemented using queue's
 *
 * \version 0.0 First version
 * \version 0.1 Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_mbx.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
UInt32 Utils_mbxGetFreeMsgCount(void);
Utils_MsgHndl *Utils_mbxAllocMsg(UInt32 timeout);
Int32 Utils_mbxFreeMsg(Utils_MsgHndl * pMsg, UInt32 timeout);



/* @{ */

/**
 *******************************************************************************
 * \brief Maximum message pool
 *******************************************************************************
*/
#define UTILS_MBX_MSG_POOL_MAX   (1024U)

/* @} */

/**
 *******************************************************************************
 * \brief Global variables for messages.
 *
 *        Memory to create the free messages queue, handle to free message Q
*         and pointer to free message pool
 *
 *******************************************************************************
 */
static Utils_QueHandle gUtils_mbxMsgPoolFreeQue;
static Ptr gUtils_mbxMsgPoolFreeQueMem[UTILS_MBX_MSG_POOL_MAX];
static Utils_MsgHndl gUtils_mbxMsgPool[UTILS_MBX_MSG_POOL_MAX];

/**
 *******************************************************************************
 *
 * \brief Gives a count of number of free messages
 *
 * \return  Count of number of free messages
 *
 *******************************************************************************
*/
UInt32 Utils_mbxGetFreeMsgCount(void)
{
    UInt32 cookie;
    UInt32 freeMsg;

    cookie = Hwi_disable();

    freeMsg = gUtils_mbxMsgPoolFreeQue.count;

    Hwi_restore(cookie);

    return freeMsg;
}

/**
 *******************************************************************************
 *
 * \brief Allocate mail box message
 *
 * \param  timeout [IN] Timeout value
 *
 * \return  A message handle is returned
 *
 *******************************************************************************
*/
Utils_MsgHndl *Utils_mbxAllocMsg(UInt32 timeout)
{
    Utils_MsgHndl *pMsg = NULL;

    Utils_queGet((Utils_QueHandle *)&gUtils_mbxMsgPoolFreeQue, (Ptr *) &pMsg, 1U, timeout);

    return pMsg;
}

/**
 *******************************************************************************
 *
 * \brief Free up a message
 *
 * \param  pMsg    [IN] Message Handle
 * \param  timeout [IN] Timeout value
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Utils_mbxFreeMsg(Utils_MsgHndl * pMsg, UInt32 timeout)
{
    Int32 status;

    status = Utils_quePut(&gUtils_mbxMsgPoolFreeQue, pMsg, timeout);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief One-time system init for mailbox subsystem
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Utils_mbxInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 msgId;

    status = Utils_queCreate(&gUtils_mbxMsgPoolFreeQue,
                             UTILS_MBX_MSG_POOL_MAX,
                             gUtils_mbxMsgPoolFreeQueMem,
                             UTILS_QUE_FLAG_BLOCK_QUE);

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        for (msgId = 0U; msgId < UTILS_MBX_MSG_POOL_MAX; msgId++)
        {
            status = Utils_mbxFreeMsg(&gUtils_mbxMsgPool[msgId], BSP_OSAL_NO_WAIT);

            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                Utils_mbxDeInit();
                break;
            }
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Free's resources allocated during Utils_mbxInit()
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Utils_mbxDeInit(void)
{
    Int32 status;

    status = Utils_queDelete(&gUtils_mbxMsgPoolFreeQue);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Creates a message box and related resources
 *
 * \param pMbx    [OUT] Created handle pMbx
 * \param pPrm    [IN]  Create parameters
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
*/
Int32 Utils_mbxCreate(Utils_MbxHndl * pMbx, const Utils_MbxCreatePrm *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;

    pMbx->pTsk = pPrm->pTsk;
    pMbx->pFuncMultiMbxTrigger = pPrm->pFuncMultiMbxTrigger;

    /*
     * Create queues
     */
    status = Utils_queCreate((Utils_QueHandle *)&(pMbx->recvQue),
                             UTILS_MBX_RECV_QUE_LEN_MAX,
                             pMbx->memRecvQue,
                             UTILS_QUE_FLAG_BLOCK_QUE);

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        for (i = 0U; i < UTILS_MBX_ACK_QUE_CNT_MAX; i++)
        {
            memset(&(pMbx->ackQue[i]), 0, sizeof(Utils_QueHandle));
        }

        for (i = 0U; i < UTILS_MBX_ACK_QUE_CNT_MAX; i++)
        {
            status = Utils_queCreate((Utils_QueHandle *)&(pMbx->ackQue[i]),
                                     UTILS_MBX_ACK_QUE_LEN_MAX,
                                     pMbx->memAckQue[i],
                                     UTILS_QUE_FLAG_BLOCK_QUE);
            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is error situation and should never execute.
            */
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
            pMbx->ackQueInUse[i] = (Bool)FALSE;
        }
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is kept to ensure future updates to macro .
        */
        if (i < UTILS_MBX_ACK_QUE_CNT_MAX)
        {
            /*
             * intial value for i is unmodified
             */
            for ( ; i != 0; i--)
            {
                Utils_queDelete(&pMbx->ackQue[i]);
            }
            Utils_queDelete(&pMbx->recvQue);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Free's resources allocated during Utils_mbxCreate()
 *
 * \param pMbx    [IN] Mail box handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
*/
Int32 Utils_mbxDelete(Utils_MbxHndl * pMbx)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;

    /*
     * Delete queues
     */
    status = Utils_queDelete(&pMbx->recvQue);
    for (i = 0U; i < UTILS_MBX_ACK_QUE_CNT_MAX; i++)
    {
        status = Utils_queDelete(&(pMbx->ackQue[i]));
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Send command to another mail box
 *
 *        Same as Utils_mbxSendMsg() except,
 *        - it can be called from interrupt context as well as task, SWI context
 *        - ACK message cannot received
 *
 * \param pTo      [IN] Receiver mail box handle
 * \param cmd      [IN] Command to be sent to the receiver
 * \param payload  [IN] Pointer to the payload to be sent to the receiver
 *
 * \return FVID2_EFAIL in case message could not be sent
 *
 *******************************************************************************
*/
Int32 Utils_mbxSendCmd(Utils_MbxHndl * pTo, UInt32 cmd, Void *payload)
{
    Utils_MsgHndl *pSentMsg;
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    if (pTo != NULL)
    {
        /* alloc message */
        pSentMsg = Utils_mbxAllocMsg(BSP_OSAL_NO_WAIT);
        if (pSentMsg != NULL)
        {
            /* set message fields */
            pSentMsg->pFrom = NULL;
            pSentMsg->flags = 0;
            pSentMsg->cmd = cmd;
            pSentMsg->result = 0;
            pSentMsg->pPrm = payload;
            pSentMsg->ackQue = NULL;

            /* send message */
            retVal = Utils_quePut(&pTo->recvQue, pSentMsg, BSP_OSAL_NO_WAIT);

            if (retVal != 0)
            {
                retVal = Utils_mbxFreeMsg(pSentMsg, BSP_OSAL_NO_WAIT);
            }
            else
            {
                /* Misra C fix */
            }

            if(pTo->pFuncMultiMbxTrigger)
            {
                retVal = pTo->pFuncMultiMbxTrigger(pTo->pTsk, BSP_OSAL_NO_WAIT);
            }
            else
            {
                /* Misra C fix */
            }

        }
        else
        {
#ifndef BUILD_A15
            Vps_printf(" UTILS: MBX: Utils_mbxSendCmd(): Msg Alloc Failed "
                       "(%d)!!!\n", Utils_mbxGetFreeMsgCount());
#endif
            retVal = SYSTEM_LINK_STATUS_EFAIL;
        }

    }
    else
    {
       retVal =  SYSTEM_LINK_STATUS_EFAIL;
    }


    return retVal;
}

/**
 *******************************************************************************
 *
 *  \brief Send message from one mailbox to another mailbox
 *
 *          When 'msgFlags' is UTILS_MBX_FLAG_WAIT_ACK,
 *          the function waits until an ack is received
 *
 *          When 'msgFlags' is 0,
 *          the function returns after message is sent to the receiver
 *
 *          User can use 'pPrm' to pass a parameter pointer to the receiver.
 *          Its upto user to manage the memory for this parameter pointer.
 *
 *          'cmd' can be any 32-bit value that is sent to the receiver
 *
 *          When UTILS_MBX_FLAG_WAIT_ACK is set,
 *          return value is the value sent via 'result' by the
 *          receiver when the receiver calls Utils_mbxAckOrFreeMsg()
 *
 *          When UTILS_MBX_FLAG_WAIT_ACK is not set,
 *          return value is message send status
 *
 *  \param pFrom    [IN] Sender Mail box handle
 *  \param pTo      [IN] Receiver mail box handle
 *  \param cmd      [IN] 32-bit command
 *  \param pPrm     [IN] 32-bit parameter pointer
 *  \param msgFlags [IN] UTILS_MBX_FLAG_xxxx
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success else failure
 *******************************************************************************
*/
Int32 Utils_mbxSendMsg(Utils_MbxHndl *pFrom,
                       Utils_MbxHndl *pTo,
                       UInt32         cmd,
                       Void          *pPrm,
                       UInt32         msgFlags)
{
    Utils_MsgHndl *pSentMsg, *pRcvMsg;
    Bool waitAck;
    Int32 retVal = SYSTEM_LINK_STATUS_SOK, retVal1 = SYSTEM_LINK_STATUS_SOK;
    Utils_QueHandle *ackQue;
    UInt32 i;
    UInt32 cookie;
    UInt32 ackQIdx = 0;

    if (pTo != NULL)
    {

        /*
         * set ACK que
         */
        if (pFrom == NULL)
        {
            /*
             * sender mailbox not specified by user
             */
            if (msgFlags & UTILS_MBX_FLAG_WAIT_ACK)
            {
                /*
                 * ERROR: if sender mail box is NULL, then cannot wait for ACK
                 */
                retVal = SYSTEM_LINK_STATUS_EFAIL;
            }
            ackQue = NULL;
        }
        else
        {
            ackQue = NULL;
            cookie = Hwi_disable();
            for (i = 0U; i < UTILS_MBX_ACK_QUE_CNT_MAX; i++)
            {
                if (pFrom->ackQueInUse[i] == FALSE)
                {
                    /*
                     * sender mail box
                     */
                    ackQue = &(pFrom->ackQue[i]);
                    pFrom->ackQueInUse[i] = (Bool)TRUE;
                    break;
                }
            }
            Hwi_restore(cookie);
            if (i == (UInt32)UTILS_MBX_ACK_QUE_CNT_MAX)
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
            }
            UTILS_assert(ackQue != NULL);
        }

        if(retVal == SYSTEM_LINK_STATUS_SOK)
        {
            /*
             * alloc message
             */
            pSentMsg = Utils_mbxAllocMsg(BSP_OSAL_WAIT_FOREVER);
            if(pSentMsg != NULL)
            {
                /*
                 * set message fields
                 */
                pSentMsg->pFrom = pFrom;
                pSentMsg->flags = msgFlags;
                pSentMsg->cmd = cmd;
                pSentMsg->result = 0U;
                pSentMsg->pPrm = pPrm;
                pSentMsg->ackQue = ackQue;

                /*
                 * send message
                 */
                retVal = Utils_quePut(&pTo->recvQue, pSentMsg, BSP_OSAL_WAIT_FOREVER);

                if (retVal == 0)
                {

                    if(pTo->pFuncMultiMbxTrigger)
                    {
                        retVal = pTo->pFuncMultiMbxTrigger(pTo->pTsk, BSP_OSAL_WAIT_FOREVER);
                    }

                    if (msgFlags & UTILS_MBX_FLAG_WAIT_ACK)
                    {
                        if(ackQue != NULL)
                        {
                            /*
                             * need to wait for ACK
                             */
                            waitAck = (Bool)TRUE;

                            do
                            {
                                /*
                                 * wait for ACK
                                 */
                                retVal = Utils_queGet(ackQue,
                                                      (Ptr *) &pRcvMsg, 1U, BSP_OSAL_WAIT_FOREVER);
                                if (retVal == 0)
                                {

                                    if (pRcvMsg == pSentMsg)
                                    {
                                        /*
                                         * ACK received for sent MSG
                                         */
                                        waitAck = (Bool)FALSE;

                                        /*
                                         * copy ACK status to return value
                                         */
                                        retVal = pRcvMsg->result;
                                    }

                                    /*
                                     * else ACK received for some other message
                                     */
                                    else
                                    {
                                        Vps_printf(" UTILS: MBX: WARNING: Received unexpected ack msg"
                                                     ". Expected: %p, Received: %p !!!\n",
                                                     pSentMsg,
                                                     pRcvMsg);
                                    }

                                    /*
                                     * free message
                                     */
                                    retVal1 = Utils_mbxFreeMsg(pRcvMsg, BSP_OSAL_WAIT_FOREVER);
                                }
                                else
                                {
                                    break;
                                }

                            } while (waitAck);
                        }
                    }

                    if (ackQue)
                    {
                        cookie = Hwi_disable();
                        ackQIdx = ackQue - &(pFrom->ackQue[0U]);
                        UTILS_assert((ackQIdx < UTILS_MBX_ACK_QUE_CNT_MAX) && (pFrom->ackQueInUse[ackQIdx] == (Bool)TRUE));
                        pFrom->ackQueInUse[ackQIdx] = (Bool)FALSE;
                        Hwi_restore(cookie);
                    }

                }

            }
            else
            {
                Vps_printf(" UTILS: MBX: Utils_mbxSendMsg(): Msg Alloc Failed "
                           "(%d)!!!\n", Utils_mbxGetFreeMsgCount());
                retVal = SYSTEM_LINK_STATUS_EFAIL;
            }

        }

    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }

    if ((SYSTEM_LINK_STATUS_SOK == retVal) &&
        (SYSTEM_LINK_STATUS_SOK != retVal1))
    {
        retVal = retVal1;
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 *  \brief Waits for a message to arrive
 *
 *         When 'timeout' is BSP_OSAL_WAIT_FOREVER, it waits until atleast one
 *         message arrives
 *
 *         When 'timeout' is BSP_OSAL_NO_WAIT, it just checks for any available
 *         message. If no message is received then it return's with error
 *
 *         User MUST call Utils_mbxAckOrFreeMsg() for every received message,
 *         else message will not be free'ed and there will be memory leak.
 *
 *  \param pMbxHndl       [IN] Receiver mail box
 *  \param pMsg           [OUT] received message
 *  \param timeout        [IN] BSP_OSAL_WAIT_FOREVER or BSP_OSAL_NO_WAIT
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
*/
Int32 Utils_mbxRecvMsg(Utils_MbxHndl * pMbxHndl,
                       Utils_MsgHndl ** pMsg,
                       UInt32 timeout)
{
    Int32 retVal;

    /*
     * wait for message to arrive
     */
    retVal = Utils_queGet(&pMbxHndl->recvQue, (Ptr *) pMsg, 1U, timeout);

    return retVal;
}

/**
 *******************************************************************************
 *
 *  \brief Peek message
 *
 *  \param pMbxHndl       [IN] Mail box Handle
 *  \param pMsg           [OUT] Message handle pointer
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
*/
Int32 Utils_mbxPeekMsg(const Utils_MbxHndl * pMbxHndl,
                       Utils_MsgHndl ** pMsg)
{
    Int32 retVal;

    /*
     * wait for message to arrive
     */
    retVal = Utils_quePeek(&pMbxHndl->recvQue, (Ptr *) pMsg);

    return retVal;
}

/**
 *******************************************************************************
 *
 *  \brief Acks or frees a message depending on flags set in the message
 *
 *         If UTILS_MBX_FLAG_WAIT_ACK is set, then an ack message is sent
 *         to the sender
 *
 *         If UTILS_MBX_FLAG_WAIT_ACK is not set,
 *         then it frees the memory associated with this message
 *
 *         User MUST call this API for every message received using
 *         Utils_mbxRecvMsg() or Utils_mbxWaitCmd()
 *         else message will not be free'ed and there will be memory leak.
 *
 *  \param pMsg       [IN] Message to ACK'ed or free'ed
 *  \param ackRetVal     [IN] return code that is sent to the sender if an ack
 *                         message is sent to the sender
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *
 *******************************************************************************
*/
Int32 Utils_mbxAckOrFreeMsg(Utils_MsgHndl * pMsg, Int32 ackRetVal)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    if (pMsg != NULL)
    {
        if (pMsg->flags & UTILS_MBX_FLAG_WAIT_ACK)
        {
            pMsg->result = ackRetVal;

            /*
             * Send ACK to sender
             */
            if (pMsg->pFrom == NULL)
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                retVal = Utils_mbxFreeMsg(pMsg, BSP_OSAL_WAIT_FOREVER);
            }
            else
            {
                retVal = Utils_quePut(pMsg->ackQue, pMsg, BSP_OSAL_WAIT_FOREVER);
            }
        }
        else
        {
            /*
             * free message
             */
            retVal = Utils_mbxFreeMsg(pMsg, BSP_OSAL_WAIT_FOREVER);
        }
    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }



    return retVal;
}

/**
 *******************************************************************************
 *
 *  \brief Waits until command of value 'cmdToWait' is received
 *
 *         If 'pMsg' is NULL it frees the msg internally when it is received
 *         and returns
 *
 *         If 'pMsg' is NOT NULL then it returns the received message to user.
 *         User needs to free the received message using Utils_mbxAckOrFreeMsg()
 *
 *  \param pMbxHndl       [IN] Receiver mail box
 *  \param pMsg       [OUT] received message
 *  \param waitCmd  [IN] command to wait for
 *
 * \return SYSTEM_LINK_STATUS_SOK on success else failure
 *******************************************************************************
*/
Int32 Utils_mbxWaitCmd(Utils_MbxHndl * pMbxHndl, Utils_MsgHndl ** pMsg,
                       UInt32 waitCmd)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    Utils_MsgHndl *pRcvMsg;

    while (1U)
    {
        /*
         * wait for message
         */
        retVal = Utils_mbxRecvMsg(pMbxHndl, &pRcvMsg, BSP_OSAL_WAIT_FOREVER);
        /*
         * Is message command ID same as expected command ID,
         * If yes, exit loop
         */
        if (retVal == SYSTEM_LINK_STATUS_SOK)
        {
            if((Utils_msgGetCmd(pRcvMsg) == waitCmd))
            {
                /*
                 * no, ACK or free received message
                 */
                retVal = Utils_mbxAckOrFreeMsg(pRcvMsg, 0);
            }
        }
        else
        {
            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is error situation and should never execute.
            */
            /* Misra C fix */
        }

        if (retVal != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
        else
        {
            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is error situation and should never execute
            */
            /* Misra C fix */
        }

    }

    if (retVal == SYSTEM_LINK_STATUS_SOK)
    {
        if (pMsg == NULL)
        {
            /* user does not want to examine the message, so free it here */
            retVal = Utils_mbxAckOrFreeMsg(pRcvMsg, 0);
        }
        else
        {
            /* user wants to examine the message to return it to user */
            *pMsg = pRcvMsg;
        }
    }

    return retVal;
}
