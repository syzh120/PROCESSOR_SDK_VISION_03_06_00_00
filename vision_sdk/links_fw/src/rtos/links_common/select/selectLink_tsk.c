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
 * \file selectLink_tsk.c
 *
 * \brief  This file has the implementation of Select Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Nov 2013) : [CM] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "selectLink_priv.h"


/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
SelectLink_Obj gSelectLink_obj[SELECT_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief
 *
 *     - Gets the out queue channel information
 *     - Prepares output queues
 *
 * \param  pObj     [IN]  Select link instance handle
 * \param  pPrm     [IN]  Create params for SELECT link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

Int32 SelectLink_drvGetOutQueChInfo(SelectLink_Obj * pObj,
                                    SelectLink_OutQueChInfo *pPrm)
{
    UInt32 outChNum;
    SelectLink_OutQueChInfo *pPrevPrm;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pPrm->numOutCh = 0;

    if(pPrm->outQueId <= pObj->createArgs.numOutQue)
    {
        pPrevPrm = &pObj->prevOutQueChInfo[pPrm->outQueId];

        /* copy current output que info to user supplied pointer */
        pPrm->numOutCh = pPrevPrm->numOutCh;

        if(pPrm->numOutCh <= SYSTEM_MAX_CH_PER_OUT_QUE)
        {
            for(outChNum=0; outChNum<pPrevPrm->numOutCh; outChNum++)
            {
                pPrm->inChNum[outChNum] = pPrevPrm->inChNum[outChNum];
            }
        }
        else
        {
            pPrm->numOutCh = 0;
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

/**
 *******************************************************************************
 * \brief
 *
 *     - Sets the out queue channel information
 *     - Prepares output queues
 *
 * \param  pObj     [IN]  Select link instance handle
 * \param  pPrm     [IN]  Create params for SELECT link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SelectLink_drvSetOutQueChInfo(SelectLink_Obj *pObj,
                                    const SelectLink_OutQueChInfo *pPrm)
{
    UInt32 inChNum, outChNum;
    SelectLink_ChInfo *pChInfo;
    SelectLink_OutQueChInfo *pPrevPrm;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if((pPrm->numOutCh > SYSTEM_MAX_CH_PER_OUT_QUE) ||
       (pPrm->outQueId > pObj->createArgs.numOutQue))
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        pPrevPrm = &pObj->prevOutQueChInfo[pPrm->outQueId];

        /* remove prev output queue channel mapping */
        for(outChNum = 0U; outChNum < pPrevPrm->numOutCh; outChNum++)
        {
            inChNum = pPrevPrm->inChNum[outChNum];

            if(inChNum < SYSTEM_MAX_CH_PER_OUT_QUE)
            {
                pChInfo = &pObj->inChInfo[inChNum];

                pChInfo->queId = SELECT_LINK_CH_NOT_MAPPED;
                pChInfo->outChNum = 0U;
                pChInfo->rtChInfoUpdate = (Bool)FALSE;
            }
            else
            {
                Vps_printf(" SELECT   : Invalid input channel number (%d) \n",
                        inChNum
                    );
            }

        }

        /* mapped input to output channels */
        for(outChNum = 0U; outChNum < pPrm->numOutCh; outChNum++)
        {
            inChNum = pPrm->inChNum[outChNum];

            if(inChNum < SYSTEM_MAX_CH_PER_OUT_QUE)
            {
                pChInfo = &pObj->inChInfo[inChNum];

                pChInfo->queId = pPrm->outQueId;
                pChInfo->outChNum = outChNum;
                pChInfo->rtChInfoUpdate = (Bool)TRUE;

                Vps_printf(" SELECT: OUT QUE%d: OUT CH%d: IN CH%d: %d x %d,"
                           " pitch = (%d, %d) \n",
                        pChInfo->queId ,
                        outChNum,
                        inChNum,
                        pChInfo->rtChInfo.width,
                        pChInfo->rtChInfo.height,
                        pChInfo->rtChInfo.pitch[0],
                        pChInfo->rtChInfo.pitch[1]
                    );
            }
            else
            {
                Vps_printf(" SELECT   : Invalid input channel number (%d) \n",
                        inChNum
                    );
            }
        }

        *pPrevPrm = *pPrm;
    }

    return status;
}

/**
 *******************************************************************************
 * \brief
 *
 *     - Copies the user passed create params into the link object create params
 *     - Prepares output queues
 *
 * \param  pObj     [IN]  Select link instance handle
 * \param  pPrm     [IN]  Create params for SELECT link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SelectLink_drvCreate(SelectLink_Obj * pObj,
                           const SelectLink_CreateParams * pPrm)
{
    UInt32 outQueId, inChId, outChId;
    Int32 status;
    System_LinkQueInfo *pInQueInfo;
    System_LinkQueInfo *pOutQueInfo;
    SelectLink_ChInfo  *pInChInfo;
    SelectLink_OutQueChInfo *pOutQueChInfo;


    /* copy create args */
    memcpy(&pObj->createArgs, pPrm, sizeof(SelectLink_CreateParams));

    UTILS_assert(pObj->createArgs.numOutQue <= SELECT_LINK_MAX_OUT_QUE);

    /* get previous link info */
    status = System_linkGetInfo(pObj->createArgs.inQueParams.prevLinkId,
                                    &pObj->inTskInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    /* point to correct previous link output que info */
    pInQueInfo = &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId];

    /* mark all Chs as not mapped */
    for(inChId = 0U; inChId < SYSTEM_MAX_CH_PER_OUT_QUE; inChId++)
    {
        pInChInfo = &pObj->inChInfo[inChId];

        pInChInfo->queId = SELECT_LINK_CH_NOT_MAPPED;
        pInChInfo->outChNum = 0U;
        pInChInfo->rtChInfoUpdate = (Bool)FALSE;

        memset((Ptr)&(pInChInfo->rtChInfo), 0, sizeof(System_LinkChInfo));
    }

    /* copy previous link channel info to local params */
    for(inChId = 0U; inChId < pInQueInfo->numCh; inChId++)
    {
        pInChInfo = &pObj->inChInfo[inChId];

        pInChInfo->rtChInfo = pInQueInfo->chInfo[inChId];
    }

    /* create out que info */
    pObj->info.numQue = pObj->createArgs.numOutQue;

    for (outQueId = 0U; outQueId < pObj->createArgs.numOutQue; outQueId++)
    {
        status = Utils_bufCreate(&pObj->outFrameQue[outQueId], FALSE, FALSE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pObj->prevOutQueChInfo[outQueId].outQueId = outQueId;
        pObj->prevOutQueChInfo[outQueId].numOutCh = 0U;

        pOutQueChInfo = &pObj->createArgs.outQueChInfo[outQueId];
        pOutQueInfo   = &pObj->info.queInfo[outQueId];

        pOutQueChInfo->outQueId = outQueId;

        status = SelectLink_drvSetOutQueChInfo(pObj, pOutQueChInfo);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        pOutQueInfo->numCh = pOutQueChInfo->numOutCh;

        for(outChId=0; outChId<pOutQueInfo->numCh; outChId++)
        {
            inChId = pOutQueChInfo->inChNum[outChId];

            if(inChId < SYSTEM_MAX_CH_PER_OUT_QUE)
            {
                pInChInfo = &pObj->inChInfo[inChId];

                pOutQueInfo->chInfo[outChId] = pInChInfo->rtChInfo;
            }
            else
            {
                Vps_printf(" SELECT   : Invalid input channel number (%d)"
                           " specified, ignoring it !!!\n",inChId);
            }
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief SELECT Link just duplicates incoming buffers and sends across all output
 *      queues. This function does the following,
 *
 *     - Send SYSTEM_CMD_NEW_DATA to all it's connected links
 *
 *
 *          DES_ID: DOX_DES_TAG(DES_Select_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1521)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1302)
 *
 * \param  pObj     [IN]  SELECT link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SelectLink_drvProcessData(SelectLink_Obj * pObj)
{

    SelectLink_CreateParams *pCreateArgs;
    SelectLink_ChInfo       *pChInfo;
    UInt32 bufId, queId;
    Int32 status;
    System_Buffer *pBuf;
    System_BufferList freeBufferList;
    System_BufferList inBufList;
    UInt32 newDataAvailable;
    newDataAvailable = 0U;

    freeBufferList.numBuf = 0U;

    pCreateArgs = &pObj->createArgs;

    System_getLinksFullBuffers(pCreateArgs->inQueParams.prevLinkId,
                              pCreateArgs->inQueParams.prevLinkQueId,
                              &inBufList);

    if (inBufList.numBuf)
    {
        for (bufId = 0; bufId < inBufList.numBuf; bufId++)
        {
            /* remap channel number */
            pBuf = inBufList.buffers[bufId];

            UTILS_assert(pBuf->chNum < SYSTEM_MAX_CH_PER_OUT_QUE);

            pChInfo = &pObj->inChInfo[pBuf->chNum];

            if(pChInfo->queId >= pCreateArgs->numOutQue)
            {
                /* input ch not mapped to any output que,release the frame */
                freeBufferList.buffers[freeBufferList.numBuf] = pBuf;
                freeBufferList.numBuf++;
            }
            else
            {
                /* save original channelNum so that we can restore it
                later while releasing the frame */
                pBuf->selectOrgChNum = pBuf->chNum;

                /* change ch number according to output que channel number */
                pBuf->chNum = pChInfo->outChNum;

                /* put the frame in output que */
                status = Utils_bufPutFullBuffer(
                                    &pObj->outFrameQue[pChInfo->queId], pBuf);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /* mark as data put in output que so that we can send a
                            notification to next link */
                newDataAvailable |= (UInt32)1 << pChInfo->queId;
            }
        }

        if(freeBufferList.numBuf)
        {
            /* free channels not mapped to any output queue */
            System_putLinksEmptyBuffers(pObj->createArgs.inQueParams.prevLinkId,
                                     pObj->createArgs.inQueParams.prevLinkQueId,
                                     &freeBufferList);

        }

        for(queId = 0; queId < pCreateArgs->numOutQue; queId++)
        {
            /* send notification if needed */
            if (newDataAvailable & ((UInt32)1 << queId))
            {
                System_sendLinkCmd(pCreateArgs->outQueParams[queId].nextLink,
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
Int32 SelectLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Int32 status;
    SelectLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    pObj = (SelectLink_Obj *) pTsk->appData;
    UTILS_assert(queId < (UInt32)SELECT_LINK_MAX_OUT_QUE);

    status = Utils_bufGetFull(&pObj->outFrameQue[queId], pBufList,
                              BSP_OSAL_NO_WAIT);

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->linkStats.getFullBufCount++;
    }
    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Select link to get output queue
 *    Information of Select link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of SELECT link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SelectLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    SelectLink_Obj *pObj = (SelectLink_Obj *) pTsk->appData;

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
Int32 SelectLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{

    UInt32 bufId;
    System_BufferList freeBufferList;
    System_Buffer *pBuf;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    SelectLink_Obj *pObj = (SelectLink_Obj *) pTsk->appData;

    pObj->linkStats.putEmptyBufCount++;

    freeBufferList.numBuf = 0U;
    for (bufId = 0U; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];

        if(pBuf != NULL)
        {
            pBuf->chNum = pBuf->selectOrgChNum;
            freeBufferList.buffers[freeBufferList.numBuf] = pBuf;
            freeBufferList.numBuf++;
        }
        else
        {
           /* Misra C: Fixed continue */
        }
    }

    pObj->putFrameCount += freeBufferList.numBuf;

    if(freeBufferList.numBuf)
    {
        System_putLinksEmptyBuffers(pObj->createArgs.inQueParams.prevLinkId,
                               pObj->createArgs.inQueParams.prevLinkQueId,
                               &freeBufferList);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function to delete Select link. This will simply delete all created
 *        output queues
 *
 * \param  pObj     [IN]  DUP link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 SelectLink_drvDelete(SelectLink_Obj * pObj)
{
    UInt32 outQueId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    for(outQueId = 0U; outQueId < pObj->createArgs.numOutQue; outQueId++)
    {
        status = Utils_bufDelete(&pObj->outFrameQue[outQueId]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating Select link
 *     - Arrival of new data
 *     - Get Output queue information
 *     - Set Output queue information
 *     - Deleting Select link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void SelectLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    /* MISRA.PPARAM.NEEDS.CONST
     * MISRAC_2004 Rule_16.7
     * MISRAC_WAIVER:
     * Generic function prototype.
     */

    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Int32 status = 0;

    SelectLink_Obj *pObj = (SelectLink_Obj *) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = SelectLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));
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
                status = SelectLink_drvProcessData(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                SelectLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                SelectLink_drvSetOutQueChInfo( pObj,
                    (SelectLink_OutQueChInfo*)Utils_msgGetPrm(pMsg));
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SELECT_LINK_CMD_GET_OUT_QUE_CH_INFO:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                SelectLink_drvGetOutQueChInfo(pObj,
                (SelectLink_OutQueChInfo*)Utils_msgGetPrm(pMsg));
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
 * \brief Init function for Select link. This function does the following for
 *   every select link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SelectLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 selectId;
    SelectLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for(selectId = 0U; selectId < SELECT_LINK_OBJ_MAX; selectId++)
    {
        pObj = &gSelectLink_obj[selectId];

        memset(pObj, 0, sizeof(SelectLink_Obj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_SELECT_0 + selectId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers = &SelectLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &SelectLink_putEmptyBuffers;
        linkObj.getLinkInfo = &SelectLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * SelectLink_tskMain is called when a message command is received.
         */
        status = SelectLink_tskCreate(selectId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for Select link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
 Int32 SelectLink_deInit(void)
 {
    UInt32 selectId;

    for(selectId = 0; selectId < SELECT_LINK_OBJ_MAX; selectId++)
    {
        Utils_tskDelete(&gSelectLink_obj[selectId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
 }
