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
  ******************************************************************************
 * \file networkTxLink_tsk.c
 *
 * \brief  This file has the implementation of DUP Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "networkTxLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
Int32 NetworkTxLink_drvCreateDumpFramesObj(NetworkTxLink_Obj * pObj);

Int32 NetworkTxLink_drvDumpFrames(NetworkTxLink_Obj * pObj, UInt32 inQue,const System_Buffer *pBuf);

Int32 NetworkTxLink_Create(NetworkTxLink_Obj * pObj,const NetworkTxLink_CreateParams * pPrm);

Int32 NetworkTxLink_drvProcessFrames(NetworkTxLink_Obj * pObj);

Int32 NetworkTxLink_drvDeleteDumpFramesObj(NetworkTxLink_Obj * pObj);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gNetworkTxLink_tskStack, 32)
#pragma DATA_SECTION(gNetworkTxLink_tskStack, ".bss:taskStackSection")
UInt8 gNetworkTxLink_tskStack[NETWORK_TX_LINK_OBJ_MAX][NETWORK_TX_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
NetworkTxLink_Obj gNetworkTxLink_obj[NETWORK_TX_LINK_OBJ_MAX];



/**
 *******************************************************************************
 * \brief Create resources and setup info required to dump frames to memory
 *
 * \param  pObj     [IN]  NetworkTx link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkTxLink_drvCreateDumpFramesObj(NetworkTxLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if ( (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP)
        ||
         (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP) )
    {
        NetworkTxLink_drvCreate(pObj);
    }
    else
    {
        /* MISRA-C Fix */
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Delete networkTx link
 *
 *
 * \param  pObj         [IN] NetworkTx link object
 *
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NetworkTxLink_drvDeleteDumpFramesObj(NetworkTxLink_Obj * pObj)
{
    Int32 status;

    if ( (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP)
            ||
              (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP) )
    {
        NetworkTxLink_drvDelete(pObj);
    }
    else
    {
        /* MISRA-C Fix */
    }

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 * \brief Delete resources required to dump frames to memory
 *
 * \param  pObj     [IN]  NetworkTx link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NetworkTxLink_drvDumpFrames(NetworkTxLink_Obj * pObj,
                            UInt32 inQue,
                            const System_Buffer *pBuf)
{
    System_LinkStatistics *linkStatsInfo = pObj->linkStatsInfo;

    if((pBuf!=NULL)
            &&
       (inQue < NETWORK_TX_LINK_MAX_IN_QUE)
            &&
       (pBuf->chNum < SYSTEM_MAX_CH_PER_OUT_QUE)
            &&
       (inQue < pObj->createArgs.numInQue)
            &&
       (pBuf->chNum < pObj->inQueInfo[inQue].numCh))
    {
        linkStatsInfo->linkStats.chStats[pBuf->chNum].
                inBufProcessCount++;

        Utils_updateLatency(&linkStatsInfo->linkLatency,
                                pBuf->linkLocalTimestamp);
        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pBuf->srcTimestamp);

        NetworkTxLink_drvSendData(
                pObj,
                inQue,
                pBuf->chNum,
                pBuf
            );
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 * \brief NetworkTx Link can be used to take input from a link and then without doing
 *   anything return it back to the same link. This useful when a link output
 *   cannot be given to any other link for testing purpose we just want to run
 *   a given link but not really use the output. In such cases the output queue
 *   of link can be connected to a NetworkTx link. The networkTx link will operate like
 *   any other link from interface point of view. But it wont do anything with
 *   the frames it gets. It will simply return it back to the sending link. This
 *   function simply does the following
 *
 *     - Copies the user passed create params into the link object create params
 *     - resets received frame count to zero
 *
 * \param  pObj     [IN]  NetworkTx link instance handle
 * \param  pPrm     [IN]  Create params for NetworkTx link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NetworkTxLink_Create(NetworkTxLink_Obj * pObj,const NetworkTxLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt16 inQue;
    System_LinkInfo inTskInfo;

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    UTILS_assert(pObj->createArgs.numInQue < NETWORK_TX_LINK_MAX_IN_QUE);

    pObj->recvCount= 0;

    for (inQue = 0; inQue < pPrm->numInQue; inQue++)
    {
        status =
            System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                               &inTskInfo);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        UTILS_assert(pPrm->inQueParams[inQue].prevLinkQueId <
                     inTskInfo.numQue);

        pObj->inQueInfo[inQue]
            =
                inTskInfo.queInfo
            [pPrm->inQueParams[inQue].prevLinkQueId];
    }

    if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
    {
        /* Check if TFDTP build is enabled to use TFDTP */
#if !(defined(NSP_TFDTP_INCLUDE))
        Vps_printf(" NETWORK TX: NETWORK_TFDTP_TX: NSP TFDTP build not enabled !!!\n");
        UTILS_assert(FALSE);
#endif
    }
    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "NETWORK TX");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool)FALSE;

    /*
     * Create resources and setup info required for NetworkTX link as per data
     * dump type
     */
    NetworkTxLink_drvCreateDumpFramesObj(pObj);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief NetworkTx Link just receives incoming buffers and returns back to the
 *   sending link. This function does the same
 *
 * \param  pObj     [IN]  NetworkTx link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NetworkTxLink_drvProcessFrames(NetworkTxLink_Obj * pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList, retBufList;
    UInt32 queId, bufId;
    System_LinkStatistics *linkStatsInfo;
    System_LinkChInfo *pChInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    for (queId = 0; queId < pObj->createArgs.numInQue; queId++)
    {
        pInQueParams = &pObj->createArgs.inQueParams[queId];

        System_getLinksFullBuffers(pInQueParams->prevLinkId,
                                  pInQueParams->prevLinkQueId, &bufList);

        if (bufList.numBuf)
        {
            pObj->recvCount += bufList.numBuf;

            for (bufId = 0; bufId < bufList.numBuf; bufId++)
            {
                /* reset stats counter if this is first frame that is recived */
                if(FALSE == pObj->isFirstFrameRecv)
                {
                    pObj->isFirstFrameRecv = (Bool)TRUE;

                    /*
                    * Reset the networkTx link statistics when first buffer is received from the
                    * previous link.
                    */
                    Utils_resetLinkStatistics(
                            &linkStatsInfo->linkStats,
                            pObj->inQueInfo[queId].numCh,
                            0);

                    Utils_resetLatency(&linkStatsInfo->linkLatency);
                    Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
                }

                linkStatsInfo->linkStats.chStats[bufList.buffers[bufId]->chNum].inBufRecvCount++;

                pChInfo = \
                &pObj->inQueInfo[queId].chInfo[bufList.buffers[bufId]->chNum];

                NetworkTxLink_drvDumpFrames(pObj, queId, bufList.buffers[bufId]);

                if (NULL != pObj->createArgs.appCb)
                {
                    pObj->createArgs.appCb(
                                    pChInfo,
                                    (Void*)bufList.buffers[bufId],
                                    pObj->createArgs.appCbArg);
                }

                if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
                {
                    retBufList.numBuf = 1;
                    retBufList.buffers[0] = bufList.buffers[bufId];
                    System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                           pInQueParams->prevLinkQueId, &retBufList);
                }

            }

            if (pObj->createArgs.transmitDataType != NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
            {
                System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                       pInQueParams->prevLinkQueId, &bufList);
            }

        }

    }
    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] NetworkTx link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkTxLink_printLinkStats(const NetworkTxLink_Obj * pObj)
{
    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                              "NETWORK TX",
                              (Bool)TRUE);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating NetworkTx link
 *     - Arrival of new data
 *     - Deleting NetworkTx link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */

Void NetworkTxLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    NetworkTxLink_Obj *pObj = (NetworkTxLink_Obj *) pTsk->appData;
    UInt32 flushCmds[1];

    if (cmd != SYSTEM_CMD_CREATE)
    {
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        status = NetworkTxLink_Create(pObj, Utils_msgGetPrm(pMsg));

        Utils_tskAckOrFreeMsg(pMsg, status);
    }

    if (status == SYSTEM_LINK_STATUS_SOK)
    {

        done = (Bool)FALSE;
        ackMsg = (Bool)FALSE;

        while (!done)
        {
            status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            cmd = Utils_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
                case SYSTEM_CMD_PRINT_STATISTICS:
                    /* print the networkTx link statistics*/
                    NetworkTxLink_printLinkStats(pObj);
                    /* ACK or free message before proceding */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
                case SYSTEM_CMD_DELETE:
                    done = (Bool)TRUE;
                    ackMsg = (Bool)TRUE;
                    break;
                case SYSTEM_CMD_NEW_DATA:
                    Utils_tskAckOrFreeMsg(pMsg, status);

                    flushCmds[0] = SYSTEM_CMD_NEW_DATA;
                    Utils_tskFlushMsg(pTsk, flushCmds, 1U);

                    NetworkTxLink_drvProcessFrames(pObj);
                    break;
                default:
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        NetworkTxLink_drvDeleteDumpFramesObj(pObj);

        if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for NetworkTx link. This function does the following for each
 *   NetworkTx link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */

Int32 NetworkTxLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 netTxId;
    NetworkTxLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (netTxId = 0; netTxId < NETWORK_TX_LINK_OBJ_MAX; netTxId++)
    {
        pObj = &gNetworkTxLink_obj[netTxId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_NETWORK_TX_0 + netTxId);
        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers= NULL;
        linkObj.linkPutEmptyBuffers= NULL;
        linkObj.getLinkInfo = NULL;

        System_registerLink(pObj->tskId, &linkObj);

        snprintf(pObj->name, 32U, "NETWORK TX%d  ", (UInt32)netTxId);

        status = Utils_tskCreate(&pObj->tsk,
                                 NetworkTxLink_tskMain,
                                 NETWORK_TX_LINK_TSK_PRI,
                                 gNetworkTxLink_tskStack[netTxId],
                                 NETWORK_TX_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for NetworkTx link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NetworkTxLink_deInit(void)
{
    UInt32 netTxId;

    for (netTxId = 0; netTxId < NETWORK_TX_LINK_OBJ_MAX; netTxId++)
    {
        Utils_tskDelete(&gNetworkTxLink_obj[netTxId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
