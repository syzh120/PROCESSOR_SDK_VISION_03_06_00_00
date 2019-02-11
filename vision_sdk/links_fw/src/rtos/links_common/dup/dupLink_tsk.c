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
 * \file dupLink_tsk.c
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
#include "dupLink_priv.h"


/*******************************************************************************
 *  FUNCTION DECLARATIONS
 *******************************************************************************
 */
Int32 DupLink_drvCreate(DupLink_Obj * pObj, const DupLink_CreateParams * pPrm);
Int32 DupLink_drvProcessData(DupLink_Obj * pObj);
Int32 DupLink_getFullBuffers(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList);
Int32 DupLink_getLinkInfo(Void * ptr, System_LinkInfo * info);
Int32 DupLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList);
Int32 DupLink_drvDelete(DupLink_Obj * pObj);


/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
DupLink_Obj gDupLink_obj[DUP_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief DUP Link just duplicates incoming buffers and sends across all output
 *     queues. There is no driver involved in duplicating the buffers. To keep
 *     code across all links consistent we use the same convention as
 *     DupLink_drvCreate. This function does the following,
 *
 *     - Copies the user passed create params into the link object create params
 *     - Prepares output queues
 *
 *      DES_ID: DOX_DES_TAG(DES_DUP_001)
 *      REQ_ID: DOX_REQ_TAG(ADASVISION-1519)
 *
 * \param  pObj     [IN]  DUP link instance handle
 * \param  pPrm     [IN]  Create params for DUP link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DupLink_drvCreate(DupLink_Obj * pObj, const DupLink_CreateParams * pPrm)
{
    UInt32 outId, bufId;
    Int32 status;
    System_Buffer *pSysBuf;

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    UTILS_assert(pObj->createArgs.numOutQue <= DUP_LINK_MAX_OUT_QUE);

    pObj->getFrameCount = 0U;
    pObj->putFrameCount = 0U;

    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId, &pObj->inTskInfo);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    pObj->info.numQue = pObj->createArgs.numOutQue;

    /*
     * Copy the output queue information of previous link into the DUP link
     * output queues. Since DUP does not modify any information we need to
     * have the same output queue information as the previous link that DUP
     * link is connected to.
    */

    UTILS_assert(pObj->info.numQue <= SYSTEM_MAX_OUT_QUE);
    for (outId = 0U; outId < pObj->info.numQue; outId++)
    {
        memcpy(&pObj->info.queInfo[outId],
           &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
           sizeof(pObj->inTskInfo.queInfo[outId]));
    }

    pObj->lock = BspOsal_semCreate(1, (Bool)TRUE);

    for (outId = 0U; outId < DUP_LINK_MAX_OUT_QUE; outId++)
    {
        status = Utils_bufCreate(&pObj->outFrameQue[outId], FALSE, FALSE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        for (bufId = 0U; bufId < DUP_LINK_MAX_FRAMES_PER_OUT_QUE; bufId++)
        {
            pSysBuf = &pObj->sysBufs[(DUP_LINK_MAX_FRAMES_PER_OUT_QUE * outId) +
                                     bufId];
            status = Utils_bufPutEmptyBuffer(&pObj->outFrameQue[outId],
                                             pSysBuf);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    memset(&pObj->stats, 0, sizeof(pObj->stats));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief DUP Link just duplicates incoming buffers and sends across all output
 *      queues. This function does the following,
 *
 *     - Duplicates buffers and sends across it's output queues
 *     - Send SYSTEM_CMD_NEW_DATA to all it's connected links
 *
 * \param  pObj     [IN]  DUP link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DupLink_drvProcessData(DupLink_Obj * pObj)
{
    UInt32 outId, bufId;
    Int32 status;
    DupLink_CreateParams *pCreateArgs;
    System_Buffer *pBuf, *pOrgBuf;

    pCreateArgs = &pObj->createArgs;
    System_getLinksFullBuffers(pCreateArgs->inQueParams.prevLinkId,
                               pCreateArgs->inQueParams.prevLinkQueId,
                               &pObj->inBufList);

    if (pObj->inBufList.numBuf)
    {
        pObj->getFrameCount += pObj->inBufList.numBuf;
        pObj->stats.recvCount += pObj->inBufList.numBuf;

        for (outId = 0U; outId < pCreateArgs->numOutQue; outId++)
        {
            pObj->outBufList[outId].numBuf = 0U;
        }

        for (bufId = 0U; bufId < pObj->inBufList.numBuf; bufId++)
        {
            pOrgBuf = pObj->inBufList.buffers[bufId];

            if(pOrgBuf != NULL)
            {

                pOrgBuf->dupCount = pCreateArgs->numOutQue;

                for (outId = 0U; outId < pCreateArgs->numOutQue; outId++)
                {
                    status = Utils_bufGetEmptyBuffer(&pObj->outFrameQue[outId],
                                                     &pBuf,
                                                     BSP_OSAL_NO_WAIT);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    UTILS_assert(pBuf != NULL);

                    memcpy(pBuf, pOrgBuf, sizeof(System_Buffer));

                    pBuf->pDupOrgFrame = (System_Buffer *)pOrgBuf;

                    pObj->outBufList[outId].buffers[pObj->outBufList[outId].
                                                        numBuf] = pBuf;

                    pObj->outBufList[outId].numBuf++;
                }
            }
        }

        for (outId = 0U; outId < pCreateArgs->numOutQue; outId++)
        {
            status = Utils_bufPutFull(&pObj->outFrameQue[outId],
                                      &pObj->outBufList[outId]);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            if (pCreateArgs->notifyNextLink)
            {
                System_sendLinkCmd(pCreateArgs->outQueParams[outId].nextLink,
                                   SYSTEM_CMD_NEW_DATA, NULL);
            }
        }
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to DUP link to get data from
 *    the output queue of DUP link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 DupLink_getFullBuffers(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList)
{
    Int32 status;
    DupLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    pObj = (DupLink_Obj *) pTsk->appData;
    UTILS_assert(queId < DUP_LINK_MAX_OUT_QUE);

    status = Utils_bufGetFull(&pObj->outFrameQue[queId], pBufList,
                              BSP_OSAL_NO_WAIT);

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->stats.forwardCount[queId] += pBufList->numBuf;
    }
    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to DUP link to get output queue
 *    Information of DUP link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of DUP link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 DupLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    DupLink_Obj *pObj = (DupLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to DUP link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to DUP link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 DupLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    UInt32 bufId;
    Int32 status;
    System_BufferList freeBufferList;
    System_Buffer *pBuf, *pOrgBuf;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    DupLink_Obj *pObj = (DupLink_Obj *) pTsk->appData;

    UTILS_assert(queId < DUP_LINK_MAX_OUT_QUE);
    UTILS_assert(queId < pObj->createArgs.numOutQue);

    freeBufferList.numBuf = 0U;

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    pObj->stats.releaseCount[queId] += pBufList->numBuf;

    for (bufId = 0U; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];

        if (pBuf != NULL)
        {
            pOrgBuf = (System_Buffer *)pBuf->pDupOrgFrame;
            UTILS_assert(pOrgBuf != NULL);

            pOrgBuf->dupCount--;

            if (pOrgBuf->dupCount == 0)
            {
                freeBufferList.buffers[freeBufferList.numBuf] = pOrgBuf;
                freeBufferList.numBuf++;
            }
        }
    }
    pObj->putFrameCount += freeBufferList.numBuf;

    System_putLinksEmptyBuffers(pObj->createArgs.inQueParams.prevLinkId,
                               pObj->createArgs.inQueParams.prevLinkQueId,
                               &freeBufferList);
    BspOsal_semPost(pObj->lock);

    status = Utils_bufPutEmpty(&pObj->outFrameQue[queId], pBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 * \brief Function to delete DUP link. This will simply delete all output
 *    queues and the semaphore
 *
 * \param  pObj     [IN]  DUP link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 DupLink_drvDelete(DupLink_Obj * pObj)
{
    UInt32 outId;
    Int32 status;

    for (outId = 0U; outId < DUP_LINK_MAX_OUT_QUE; outId++)
    {
        status = Utils_bufDelete(&pObj->outFrameQue[outId]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    BspOsal_semDelete(&pObj->lock);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating DUP link
 *     - Arrival of new data
 *     - Deleting DUP link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void DupLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
	/*
	* MISRA.PPARAM.NEEDS.CONS
	* MISRAC_2004_Rule_16.7
	* Function parameter is not declared as a pointer to const.
	* In Other Links it calls Utils_tskRecvMsg where the memory
	* pointed by pTsk will be updated .So ptask cannot be made const
	* KW State: Defer -> Waiver -> Case by case
	*/


    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    DupLink_Obj *pObj = (DupLink_Obj*) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = DupLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));
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
                status = DupLink_drvProcessData(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                DupLink_drvDelete(pObj);
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
 * \brief Init function for DUP link. This function does the following for each
 *   DUP link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DupLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 dupId;
    DupLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for(dupId = 0U; dupId < DUP_LINK_OBJ_MAX; dupId++)
    {
        pObj = &gDupLink_obj[dupId];

        memset(pObj, 0, sizeof(DupLink_Obj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_DUP_0 + dupId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers = &DupLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &DupLink_putEmptyBuffers;
        linkObj.getLinkInfo = &DupLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        status = DupLink_tskCreate(dupId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for DUP link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DupLink_deInit(void)
 {
    UInt32 dupId;

    for(dupId = 0U; dupId < DUP_LINK_OBJ_MAX; dupId++)
    {
        Utils_tskDelete(&gDupLink_obj[dupId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
 }
