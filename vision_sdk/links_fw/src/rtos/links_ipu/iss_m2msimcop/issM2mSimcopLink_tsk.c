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
#include "issM2mSimcopLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
Void IssM2mSimcopLink_tskMain(Utils_TskHndl * pTsk, Utils_MsgHndl * pMsg);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_TSK_STACK_SIZE (SYSTEM_DEFAULT_TSK_STACK_SIZE)
#pragma DATA_ALIGN(gIssM2mSimcopLink_tskStack, 32)
#pragma DATA_SECTION(gIssM2mSimcopLink_tskStack, ".bss:taskStackSection")
UInt8 gIssM2mSimcopLink_tskStack[ISSM2MSIMCOP_LINK_OBJ_MAX][ISSM2MSIMCOP_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
IssM2mSimcopLink_Obj gIssM2mSimcopLink_obj[ISSM2MSIMCOP_LINK_OBJ_MAX];


/**
 *******************************************************************************
 *
 * \brief Link main function
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void IssM2mSimcopLink_tskMain(Utils_TskHndl * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done, stopDone;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssM2mSimcopLink_Obj *pObj;
    UInt32 flushCmds[2];

    /* IDLE state */

    pObj = (IssM2mSimcopLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
         * with error status */
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the driver */
        status = IssM2mSimcopLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

        /* ACK based on create status */
        Utils_tskAckOrFreeMsg(pMsg, status);
    }

    /* if create status is error then remain in IDLE state */
    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        /* create success, entering READY state */
        done = (Bool) FALSE;
        ackMsg = (Bool) FALSE;
        stopDone = (Bool) FALSE;

        /* READY state loop */
        while (!done)
        {
            /* wait for message */
            status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
            /* extract message command from message */
            cmd = Utils_msgGetCmd(pMsg);

            if((stopDone == (Bool) TRUE) && (cmd!=SYSTEM_CMD_DELETE))
            {
                /* once stop is done, only DELETE command should be accepted */
                Utils_tskAckOrFreeMsg(pMsg, status);
            }
            else
            {
                switch (cmd)
                {
                    case SYSTEM_CMD_NEW_DATA:
                        /* new data frames have been captured, process them */

                        /* ACK or free message before proceeding */
                        Utils_tskAckOrFreeMsg(pMsg, status);

                        flushCmds[0] = SYSTEM_CMD_NEW_DATA;
                        Utils_tskFlushMsg(pTsk, flushCmds, 1U);

                        IssM2mSimcopLink_drvProcessData(pObj);
                        break;

                    case ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG:

                        status = IssM2mSimcopLink_drvSetSimcopConfig(pObj,
                                        Utils_msgGetPrm(pMsg));
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case SYSTEM_CMD_PRINT_STATISTICS:
                        /* new data frames have been captured, process them */
                        IssM2mSimcopLink_drvPrintStatus(pObj);

                        /* ACK or free message before proceeding */
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME:
                    {
                        UInt32 chId;

                        chId = *(UInt32 *)Utils_msgGetPrm(pMsg);
                        IssM2mSimcopLink_drvSaveFrame(pObj, chId);

                        /* ACK or free message before proceeding */
                        Utils_tskAckOrFreeMsg(pMsg, status);

                        break;
                    }
                    case ISSM2MSIMCOP_LINK_CMD_GET_SAVE_FRAME_STATUS:

                        status = IssM2mSimcopLink_drvGetSaveFrameStatus(pObj,
                                    Utils_msgGetPrm(pMsg));

                        /* ACK or free message before proceeding */
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;

                    case SYSTEM_CMD_STOP:
                        /* Nothing to do, just ACK mesage */
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        stopDone = (Bool) TRUE;
                        break;

                    case SYSTEM_CMD_DELETE:

                        /* exit READY state */
                        done = (Bool) TRUE;
                        ackMsg = (Bool) TRUE;
                        break;
                    default:
                        /* invalid command for this state ACK it and continue READY
                         * loop */
                        Utils_tskAckOrFreeMsg(pMsg, status);
                        break;
                }
            }
        }
        /* exiting READY state, delete driver */
        IssM2mSimcopLink_drvDelete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
    }

    /* entering IDLE state */
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for link. BIOS task for the
 *  link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_init(void)
{
    Int32 status;
    UInt32 instId;

    System_LinkObj linkObj;
    IssM2mSimcopLink_Obj *pObj;

    /* register link with system API */
    for(instId = 0; instId < ISSM2MSIMCOP_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIssM2mSimcopLink_obj[instId];

        memset(pObj, 0, sizeof(IssM2mSimcopLink_Obj));

        pObj->linkId = SYSTEM_LINK_ID_ISSM2MSIMCOP_0 + instId;

        linkObj.pTsk                = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &IssM2mSimcopLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &IssM2mSimcopLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &IssM2mSimcopLink_getInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /* Create link task, task remains in IDLE state
         * IssM2mSimcopLink_tskMain is called when a message command is received
         */

        status = Utils_tskCreate(&pObj->tsk,
            IssM2mSimcopLink_tskMain,
            ISSM2MSIMCOP_LINK_TSK_PRI,
            &gIssM2mSimcopLink_tskStack[instId][0],
            ISSM2MSIMCOP_LINK_TSK_STACK_SIZE, pObj, "ISSM2MSIMCOP ",
            UTILS_TSK_AFFINITY_CORE0);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for capture link. BIOS task for capture
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IssM2mSimcopLink_deInit(void)
{
    IssM2mSimcopLink_Obj *pObj;
    UInt32 instId;

    for(instId = 0; instId < ISSM2MSIMCOP_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIssM2mSimcopLink_obj[instId];

        /*
         * Delete link task
         */
        Utils_tskDelete(&pObj->tsk);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get the buffer and queue information about link.
 *
 * \param  ptr  [IN] Task Handle
 * \param  info [IN] Pointer to link information handle

 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IssM2mSimcopLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    IssM2mSimcopLink_Obj *pObj = (IssM2mSimcopLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * Link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from this link
 * output queue.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IssM2mSimcopLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    IssM2mSimcopLink_Obj *pObj = (IssM2mSimcopLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 idx = 0;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    /* IssM2mSimcopLink_Obj uses a two queues. Hence queId is used here */
    if ((UInt32)TRUE != Utils_queIsEmpty(&pObj->fullBufQue))
    {
        for (idx = 0U; idx < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST; idx++)
        {
            /* MISRA.CAST.PTR:MISRAC_2004 Rule_11.4
               MISRAC_WAIVER:
               Generic implementation of queue expects data in Ptr* type,
               so typecasted it to Ptr *. */
            status = Utils_queGet(&pObj->fullBufQue,
                              (Ptr *) & pBufList->buffers[idx],
                              1U,
                              BSP_OSAL_NO_WAIT);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS;
    }

    pBufList->numBuf = idx;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IssM2mSimcopLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    Int32 status;
    Int32 idx;
    System_Buffer *pBuf;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    IssM2mSimcopLink_Obj *pObj = (IssM2mSimcopLink_Obj *) pTsk->appData;

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        pBuf = pBufList->buffers[idx];

        if((pBuf != NULL) && (pBuf->chNum < ISSM2MSIMCOP_LINK_MAX_CH))
        {
            status = Utils_quePut(&pObj->chObj[pBuf->chNum].emptyBufQue,
                               pBufList->buffers[idx],
                               BSP_OSAL_NO_WAIT);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}
