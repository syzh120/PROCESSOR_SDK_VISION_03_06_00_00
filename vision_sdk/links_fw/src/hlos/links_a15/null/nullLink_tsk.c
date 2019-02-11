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
 * \file nullLink_tsk.c
 *
 * \brief  This file has the implementation of DUP Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Jun 2014) : [YM] First version ported to Linux
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "nullLink_priv.h"

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
NullLink_Obj gNullLink_obj[NULL_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief Null Link can be used to take input from a link and then without doing
 *   anything return it back to the same link. This useful when a link output
 *   cannot be given to any other link for testing purpose we just want to run
 *   a given link but not really use the output. In such cases the output queue
 *   of link can be connected to a Null link. The null link will operate like
 *   any other link from interface point of view. But it wont do anything with
 *   the frames it gets. It will simply return it back to the sending link. This
 *   function simply does the following
 *
 *     - Copies the user passed create params into the link object create params
 *     - resets received frame count to zero
 *
 * \param  pObj     [IN]  Null link instance handle
 * \param  pPrm     [IN]  Create params for Null link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NullLink_drvCreate(NullLink_Obj * pObj, NullLink_CreateParams * pPrm)
{
    Int32 status;
    UInt16 inQue;
    System_LinkInfo inTskInfo;

    Vps_printf(" NULL Link: Create in progress !!!\n");

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    OSA_assert(pObj->createArgs.numInQue < NULL_LINK_MAX_IN_QUE);

    pObj->recvCount= 0;

    for (inQue = 0; inQue < pPrm->numInQue; inQue++)
    {
        status =
            System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                               &inTskInfo);
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
        OSA_assert(pPrm->inQueParams[inQue].prevLinkQueId <
                     inTskInfo.numQue);

        pObj->inQueInfo[inQue]
            =
                inTskInfo.queInfo
            [pPrm->inQueParams[inQue].prevLinkQueId];
    }

    Vps_printf(" NULL Link: Create done !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Null Link just receives incoming buffers and returns back to the
 *   sending link. This function does the same
 *
 * \param  pObj     [IN]  Null link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NullLink_drvProcessFrames(NullLink_Obj * pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;
    UInt32 queId, bufId, chNum;
    System_LinkChInfo *pChInfo;

    for (queId = 0; queId < pObj->createArgs.numInQue; queId++)
    {
        pInQueParams = &pObj->createArgs.inQueParams[queId];

        System_getLinksFullBuffers(pInQueParams->prevLinkId,
                                  pInQueParams->prevLinkQueId, &bufList);

        if (bufList.numBuf)
        {
            System_BitstreamBuffer *bitstreamBuf;
            pObj->recvCount += bufList.numBuf;
            /* File Write enabled for channels only from first inputQ (Q0) */
            if ((pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
                &&
               (queId == 0))
            {
                for (bufId = 0; bufId < bufList.numBuf; bufId++)
                {
                  chNum = bufList.buffers[bufId]->chNum;
                  OSA_assert (chNum < SYSTEM_MAX_CH_PER_OUT_QUE);
                  bitstreamBuf = ((System_BitstreamBuffer *)bufList.buffers[bufId]->payload);
                  /* Cache invalidate required as CPU copy is used */
                  OSA_memCacheInv((UInt32)bitstreamBuf->bufAddr, bitstreamBuf->fillLength);

                  fwrite(bitstreamBuf->bufAddr, bitstreamBuf->fillLength, 1, pObj->fpDataStream[chNum]);
                }
            }

            for (bufId = 0; bufId < bufList.numBuf; bufId++)
            {
                pChInfo = \
                &pObj->inQueInfo[queId].chInfo[bufList.buffers[bufId]->chNum];

                if (NULL != pObj->createArgs.appCb)
                {
                    pObj->createArgs.appCb(
                                    pChInfo,
                                    (Void*)bufList.buffers[bufId],
                                    pObj->createArgs.appCbArg);
                }
            }

            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                       pInQueParams->prevLinkQueId, &bufList);
        }

    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating Null link
 *     - Arrival of new data
 *     - Deleting Null link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Int32 NullLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 chId, status = SYSTEM_LINK_STATUS_SOK;
    NullLink_Obj *pObj = (NullLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        OSA_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EFAIL);
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    status = NullLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));

    OSA_tskAckOrFreeMsg(pMsg, status);

    if (status != SYSTEM_LINK_STATUS_SOK)
        return status;

    done = FALSE;
    ackMsg = FALSE;

    while (!done)
    {
        status = OSA_tskWaitMsg(pTsk, &pMsg);
        if (status != OSA_SOK)
            break;

        cmd = OSA_msgGetCmd(pMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_START:
                OSA_tskAckOrFreeMsg(pMsg, status);
                if (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
                {
                   /* File Write enabled for channels only from first inputQ (Q0) */
                   for (chId=0; chId<pObj->inQueInfo[0].numCh; chId++)
                   {
                     Vps_printf(" NULL LINK: Opening file for Dump \n");
                     pObj->fpDataStream[chId] = fopen((char *)pObj->createArgs.nameDataFile[chId], "wb");
                     OSA_assert(pObj->fpDataStream[chId] != NULL);
                     Vps_printf(" NULL LINK: Opened file for Dump \n");
                   }
                }
                break;
            case SYSTEM_CMD_STOP:
                OSA_tskAckOrFreeMsg(pMsg, status);
                if (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
                {
                   for (chId=0; chId<pObj->inQueInfo[0].numCh; chId++)
                   {
                     Vps_printf(" NULL LINK: Closing Dump file \n");
                     if(pObj->fpDataStream[chId])
                     {
                         fflush(pObj->fpDataStream[chId]);
                         fclose(pObj->fpDataStream[chId]);
                     }
                     Vps_printf(" NULL LINK: Closed dump file \n");
                   }
                }
                break;
            case SYSTEM_CMD_DELETE:
                done = TRUE;
                ackMsg = TRUE;
                break;
            case SYSTEM_CMD_NEW_DATA:
                OSA_tskAckOrFreeMsg(pMsg, status);

                NullLink_drvProcessFrames(pObj);
                break;
            default:
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    if (ackMsg && pMsg != NULL)
        OSA_tskAckOrFreeMsg(pMsg, status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Init function for Null link. This function does the following for each
 *   Null link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */

Int32 NullLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 nullId;
    NullLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for (nullId = 0; nullId < NULL_LINK_OBJ_MAX; nullId++)
    {
        pObj = &gNullLink_obj[nullId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_NULL_0 + nullId);
        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers= NULL;
        linkObj.linkPutEmptyBuffers= NULL;
        linkObj.getLinkInfo = NULL;

        System_registerLink(pObj->tskId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * ipcOutLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "NULL_%u", (unsigned int)nullId);
        status = OSA_tskCreate(&pObj->tsk,
                               NullLink_tskMain,
                               NULL_LINK_TSK_PRI,
                               NULL_LINK_TSK_STACK_SIZE,
                               0,
                               pObj,
                               pObj->tskName);
        OSA_assert(status == OSA_SOK);
        Vps_printf(" %s : Init done - linkid-0x%x\n", pObj->tskName, pObj->tskId);

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for Null link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NullLink_deInit(void)
{
    UInt32 nullId;

    for (nullId = 0; nullId < NULL_LINK_OBJ_MAX; nullId++)
    {
        OSA_tskDelete(&gNullLink_obj[nullId].tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
            gNullLink_obj[nullId].tskName, gNullLink_obj[nullId].tskId);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
