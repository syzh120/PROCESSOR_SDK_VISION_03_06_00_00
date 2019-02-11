/******************************************************************************
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
******************************************************************************/

/**
  ******************************************************************************
 * \file splitLink_tsk.c
 *
 * \brief  This file has the implementation of SPLIT Link API
 *
 *         Split link is a connector link. It takes each channel of higher res
 *         video and splits it not "numSplits" number of channels with lower
 *         resolution video.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "splitLink_priv.h"


/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
SplitLink_Obj gSplitLink_obj[SPLIT_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief SPLIT Link just splits incoming video buffers into "numSplits"
 *     channels and sends all the channels into same output queue.
 *     This function does the following,
 *
 *     - Copies the user passed create params into the link object create params
 *     - Creates new channels as required
 *     - Prepares output queues
 *
 * \param  pObj     [IN]  SPLIT link instance handle
 * \param  pPrm     [IN]  Create params for SPLIT link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SplitLink_drvCreate(SplitLink_Obj * pObj, SplitLink_CreateParams * pPrm)
{
    UInt32 bufId, chId, numCh, splitId;
    Int32 status;
    System_Buffer *pSysBuf;

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    UTILS_assert(pObj->createArgs.numSplits <= SPLIT_LINK_MAX_NUM_SPLITS);

    pObj->getFrameCount = 0;
    pObj->putFrameCount = 0;

    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId, &pObj->inTskInfo);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    pObj->info.numQue = 1;

    /*
     * Create numSplits*N channels in output queue based on N input channels.
     * SPLIT only modifies width in the channel info. All other information
     * is same as the previous link.
     */

    UTILS_assert(pObj->info.queInfo[0].numCh *
                 pObj->createArgs.numSplits <= SYSTEM_MAX_CH_PER_OUT_QUE);
    memcpy(&pObj->info.queInfo[0],
       &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
       sizeof(pObj->inTskInfo.queInfo));
    numCh = pObj->info.queInfo[0].numCh;
    for(chId = 0; chId < numCh; chId++)
    {
        pObj->info.queInfo[0].chInfo[chId].width /=
            pObj->createArgs.numSplits;
        for(splitId = 0; splitId < pObj->createArgs.numSplits; splitId++)
        {
            memcpy(&pObj->info.queInfo[0].chInfo[chId + numCh*splitId],
                   &pObj->info.queInfo[0].chInfo[chId],
                   sizeof(pObj->info.queInfo[0].chInfo[chId]));
        }
    }
    pObj->info.queInfo[0].numCh *= pObj->createArgs.numSplits;

    pObj->lock = BspOsal_semCreate(1u, TRUE);
    UTILS_assert(pObj->lock!=NULL);

    status = Utils_bufCreate(&pObj->outFrameQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (bufId = 0; bufId < SPLIT_LINK_MAX_FRAMES_PER_OUT_QUE *
                            SPLIT_LINK_MAX_NUM_SPLITS; bufId++)
    {
        pSysBuf = &pObj->sysBufs[bufId];
        pSysBuf->payload = &pObj->sysVidFrmBufs[bufId];

        status = Utils_bufPutEmptyBuffer(&pObj->outFrameQue,
                                         pSysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    memset(&pObj->stats, 0, sizeof(pObj->stats));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief SPLIT Link processing
 *       This function does the following,
 *
 *     - Sends N=numSplits output channels for one input channel
 *     - Send SYSTEM_CMD_NEW_DATA to all it's connected links
 *
 * \param  pObj     [IN]  SPLIT link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SplitLink_drvProcessData(SplitLink_Obj * pObj)
{
    UInt32 bufId, offset, planes, splitId, chOffset;
    Fvid2_DataFormat dataFormat;
    Int32 status;
    System_LinkChInfo *pQueChInfo;
    SplitLink_CreateParams *pCreateArgs;
    System_Buffer *pBuf, *pOrgBuf;
    System_VideoFrameBuffer *pSysVidFrmBufs;
    Void *payloadBkp;


    pCreateArgs = &pObj->createArgs;
    System_getLinksFullBuffers(pCreateArgs->inQueParams.prevLinkId,
                               pCreateArgs->inQueParams.prevLinkQueId,
                               &pObj->inBufList);

    if (pObj->inBufList.numBuf)
    {
        pObj->getFrameCount += pObj->inBufList.numBuf;
        pObj->stats.recvCount += pObj->inBufList.numBuf;

        pObj->outBufList.numBuf = 0;

        for (bufId = 0; bufId < pObj->inBufList.numBuf; bufId++)
        {
            pOrgBuf = pObj->inBufList.buffers[bufId];

            if(pOrgBuf == NULL)
                continue;

            pOrgBuf->splitCount = pCreateArgs->numSplits;

            for (splitId = 0; splitId < pCreateArgs->numSplits; splitId++)
            {
                status = Utils_bufGetEmptyBuffer(&pObj->outFrameQue,
                                                 &pBuf,
                                                 BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                UTILS_assert(pBuf != NULL);

                payloadBkp = pBuf->payload;
                memcpy(pBuf, pOrgBuf, sizeof(*pBuf));
                pBuf->payload = payloadBkp;
                memcpy(pBuf->payload,
                       pOrgBuf->payload,
                       sizeof(System_VideoFrameBuffer));

                pBuf->pSplitOrgFrame = (System_Buffer *)pOrgBuf;

                pObj->outBufList.buffers[pObj->outBufList.numBuf] = pBuf;
                if(splitId > 0)
                {
                    chOffset = pObj->info.queInfo[0].numCh /
                               pCreateArgs->numSplits;
                    pBuf->chNum = pBuf->chNum + chOffset*splitId;
                    pSysVidFrmBufs = pBuf->payload;
                    pQueChInfo =
                        &pObj->info.queInfo[0].chInfo[pBuf->chNum];

                    dataFormat = (Fvid2_DataFormat)
                        System_Link_Ch_Info_Get_Flag_Data_Format(
                            pQueChInfo->flags);

                    if(Fvid2_isDataFmtSemiPlanar(dataFormat))
                    {
                        offset = pQueChInfo->width;
                    }
                    else
                    {
                        offset = pQueChInfo->width*2;
                    }
                    for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
                    {
                        pSysVidFrmBufs->bufAddr[planes] =
                            (void*) ((UInt32)pSysVidFrmBufs->bufAddr[
                                        planes] + offset);
                    }
                }
                pObj->outBufList.numBuf++;
            }
        }

        status = Utils_bufPutFull(&pObj->outFrameQue,
                                  &pObj->outBufList);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        System_sendLinkCmd(pCreateArgs->outQueParams.nextLink,
                                                SYSTEM_CMD_NEW_DATA, NULL);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to SPLIT link to get data from
 *    the output queue of SPLIT link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SplitLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Int32 status;
    SplitLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    pObj = (SplitLink_Obj *) pTsk->appData;

    status = Utils_bufGetFull(&pObj->outFrameQue, pBufList,
                              BSP_OSAL_NO_WAIT);

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->stats.forwardCount += pBufList->numBuf;
    }
    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to SPLIT link to get output queue
 *    Information of SPLIT link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of SPLIT link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SplitLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    SplitLink_Obj *pObj = (SplitLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to SPLIT link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to SPLIT link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SplitLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    UInt32 bufId;
    Int32 status;
    System_BufferList freeBufferList;
    System_Buffer *pBuf, *pOrgBuf;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    SplitLink_Obj *pObj = (SplitLink_Obj *) pTsk->appData;

    freeBufferList.numBuf = 0;

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    pObj->stats.releaseCount += pBufList->numBuf;

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];

        if (pBuf == NULL)
           continue;

        pOrgBuf = (System_Buffer *)pBuf->pSplitOrgFrame;
        UTILS_assert(pOrgBuf != NULL);

        pOrgBuf->splitCount--;

        if (pOrgBuf->splitCount == 0)
        {
            freeBufferList.buffers[freeBufferList.numBuf] = pOrgBuf;
            freeBufferList.numBuf++;
        }
    }
    pObj->putFrameCount += freeBufferList.numBuf;

    System_putLinksEmptyBuffers(pObj->createArgs.inQueParams.prevLinkId,
                               pObj->createArgs.inQueParams.prevLinkQueId,
                               &freeBufferList);
    BspOsal_semPost(pObj->lock);

    status = Utils_bufPutEmpty(&pObj->outFrameQue, pBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 * \brief Function to delete SPLIT link. This will simply delete all output
 *    queues and the semaphore
 *
 * \param  pObj     [IN]  SPLIT link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SplitLink_drvDelete(SplitLink_Obj * pObj)
{
    Int32 status;

    status = Utils_bufDelete(&pObj->outFrameQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    BspOsal_semDelete(&pObj->lock);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating SPLIT link
 *     - Arrival of new data
 *     - Deleting SPLIT link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void SplitLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Int32 status = 0;

    SplitLink_Obj *pObj = (SplitLink_Obj*) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = SplitLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));
                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    pObj->state = SYSTEM_LINK_STATE_RUNNING;
                }
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_NEW_DATA:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                status = SplitLink_drvProcessData(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                SplitLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        default:
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for SPLIT link. This function does the following for each
 *   SPLIT link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SplitLink_init()
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 splitId;
    SplitLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for(splitId = 0; splitId < SPLIT_LINK_OBJ_MAX; splitId++)
    {
        pObj = &gSplitLink_obj[splitId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_SPLIT_0 + splitId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers = SplitLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = SplitLink_putEmptyBuffers;
        linkObj.getLinkInfo = SplitLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        status = SplitLink_tskCreate(splitId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for SPLIT link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SplitLink_deInit()
 {
    UInt32 splitId;

    for(splitId = 0; splitId < SPLIT_LINK_OBJ_MAX; splitId++)
    {
        Utils_tskDelete(&gSplitLink_obj[splitId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
 }
