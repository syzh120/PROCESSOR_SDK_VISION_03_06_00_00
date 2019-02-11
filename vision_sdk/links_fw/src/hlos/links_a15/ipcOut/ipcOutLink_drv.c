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
 * \file ipcOutLink_drv.c
 *
 * \brief  This file has the implementataion of IPC OUT Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcOutLink_priv.h"

/**
 *******************************************************************************
 * \brief Shared Region from where IPC buffers are allocated
 *
 *        For performance reasons it is assumed video frame buffers are always
 *        allocated from SR1. This saves a look up during address translation.
 *
 *        This can be changed to IPC_OUT_MEM_REGION_TYPE to support buffers
 *        from other SRs
 *******************************************************************************
 */
#define IPC_OUT_MEM_REGION_TYPE  OSA_MEM_REGION_TYPE_AUTO

/**
 *******************************************************************************
 *
 * \brief This function is called when next link send a notify or
 *        periodic timer expires
 *
 *        A command is sent to the IPC thread to read buffer's from IPC IN ->
 *        IPC OUT queue and release the buffers back to the previous link
 *
 * \param  pTsk     [IN]  Task Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void IpcOutLink_drvNotifyCb(OSA_TskHndl * pTsk)
{
    IpcOutLink_Obj * pObj = (IpcOutLink_Obj * )pTsk->appData;

    pObj->linkStats.notifyEventCount++;

    if(OSA_ipcQueIsEmpty(&pObj->ipcIn2OutQue)==FALSE)
    {
        /*
         * send command to release frames only if there are elements in the
         * que
         */
        System_sendLinkCmd(pObj->linkId,
                            IPC_OUT_LINK_CMD_RELEASE_FRAMES,
                            NULL);
    }
}

/**
 *******************************************************************************
 *
 * \brief Channel specific initialization
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvChCreate(IpcOutLink_Obj *pObj)
{
    IpcOutLink_ChObj *pChObj;
    UInt32 chId;

    for(chId=0; chId<SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pChObj = &pObj->chObj[chId];

        /* reset skip buf context to not skip any frames */
        OSA_resetSkipBufContext(&pChObj->bufSkipContext, 30, 30);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Create IPC Out link
 *
 *        Following happens during create phase,
 *        - Call 'get link info” on previous link.
 *          When IPC IN from other processers asks link info it gives back
 *          this link info to the next link (IPC IN)
 *        - IPC shared memory buffer information structures are allocated
 *          for non uni-cache IPC OUT/IN pair
 *        - IPC shared memory buffer information structure pointers
 *          are placed in internal local queue for non uni-cache
 *          IPC OUT/IN pair
 *        - Both IPC shared memory queue's
 *          (IPC OUT -> IPC IN, IPC IN -> IPC OUT) is reset to empty state.
 *
 * \param  pObj     [IN]  Link object
 * \param  pPrm     [IN]  Create arguments
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvCreate(IpcOutLink_Obj *pObj, IpcLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Create in progress !!!\n",
               pObj->linkInstId
              );
#endif

    /* keep a copy of create args */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* get previous link info */
    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId,
                    &pObj->prevLinkInfo
                );
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* validate previous link que ID */
    OSA_assert(
        pObj->createArgs.inQueParams.prevLinkQueId <
            pObj->prevLinkInfo.numQue
        );

    /*
     * Setup current link que information
     * Current queue is considered to have one output queue
     * with que information same as selected previous link queue
     */
    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0],
           &pObj->prevLinkInfo.queInfo
                [pObj->createArgs.inQueParams.prevLinkQueId],
           sizeof(pObj->linkInfo.queInfo[0])
          );

    /* reset IPC queue's */

    OSA_ipcQueReset(&pObj->ipcOut2InQue,
                        pObj->ipcOut2InSharedMemBaseAddr,
                        TRUE,
                        TRUE
                    );
    OSA_ipcQueReset(&pObj->ipcIn2OutQue,
                        pObj->ipcIn2OutSharedMemBaseAddr,
                        TRUE,
                        TRUE
                    );

    UInt32 elemId;

    /* create local queue */
    status = OSA_queCreate(&pObj->localQue,
                         SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);


    /* allocate memory for IPC data structure's in shared memory */
    for(elemId=0; elemId <SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS; elemId++)
    {
        /* queue to local queue
         * local que and IPC queue only stores index's, actual pointer to
         * IPC Buffer can be retrrieved via API System_ipcGetIpcBuffer
         * which takes IPC Out link ID and index as input
         */

        /* queue to local queue */
        status = OSA_quePut(&pObj->localQue,
                     (Int32)elemId,
                     0
                );
        OSA_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    /* TODO: statistics */

    IpcOutLink_drvChCreate(pObj);

    pObj->isFirstFrameRecv = FALSE;

    OSA_resetLatency(&pObj->linkLatency);
    OSA_resetLatency(&pObj->srcToLinkLatency);

    OSA_resetLinkStatistics(&pObj->linkStats,
                              pObj->linkInfo.queInfo[0].numCh,
                              1);

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Create Done !!!\n",
           pObj->linkInstId
          );
#endif


    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete IPC Out link
 *
 *        This function free's resources allocated during create
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvDelete(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Delete in progress !!!\n", pObj->linkInstId);
#endif

    /* delete local queue */
    OSA_queDelete(&pObj->localQue);

    /* no need for any channel delete logic */

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Delete Done !!!\n",
           pObj->linkInstId
          );
#endif

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Translates pointers in the payload of ipc buffer to physical addr
 *        based on buffer type. This is essential step before buffers
 *        can be forwarded to next link out of A15 in the chain.
 *
 * \param  pBuffer     [IN]  Pointer to ipc buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Void IpcOutLink_drvTranslateIpcBufferPayloadPtrsVirt2Phys(System_IpcBuffer *pBuffer)
{
    UInt32 planes = 0;
    UInt32 frames = 0;
    System_VideoFrameBuffer * pVideoFrameBuffer                   = NULL;
    System_EglPixmapVideoFrameBuffer *pEglPixmapBuffer            = NULL;
    System_BitstreamBuffer * pBitstreamBuffer                     = NULL;
    System_MetaDataBuffer * pVideoMetaDataBuffer                  = NULL;
    System_VideoFrameCompositeBuffer * pVideoFrameCompositeBuffer = NULL;

    OSA_assert(pBuffer != NULL);

    switch((System_BufferType)System_Buffer_Flag_Get_Buf_Type(pBuffer->flags))
    {
        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

            pVideoFrameBuffer = (System_VideoFrameBuffer *)pBuffer->payload;
            for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
            {
                if(pVideoFrameBuffer->bufAddr[planes] != NULL)
                {
                    pVideoFrameBuffer->bufAddr[planes] =
                                       (Void *)OSA_memVirt2Phys(
                                               (UInt32)pVideoFrameBuffer->bufAddr[planes],
                                                IPC_OUT_MEM_REGION_TYPE);
                }
            }
            if(pVideoFrameBuffer->metaBufAddr != NULL)
            {
                pVideoFrameBuffer->metaBufAddr =
                                       (Void *)OSA_memVirt2Phys(
                                               (UInt32) pVideoFrameBuffer->metaBufAddr,
                                                IPC_OUT_MEM_REGION_TYPE);
            }
        break;
        case SYSTEM_BUFFER_TYPE_BITSTREAM:

            pBitstreamBuffer = (System_BitstreamBuffer *)pBuffer->payload;
            if(pBitstreamBuffer->bufAddr != NULL)
            {
                pBitstreamBuffer->bufAddr =
                                        (Void *)OSA_memVirt2Phys(
                                                (UInt32)pBitstreamBuffer->bufAddr,
                                                 IPC_OUT_MEM_REGION_TYPE);
            }

            if(pBitstreamBuffer->metaBufAddr != NULL)
            {
                pBitstreamBuffer->metaBufAddr =
                                        (Void *)OSA_memVirt2Phys(
                                                (UInt32) pBitstreamBuffer->metaBufAddr,
                                                IPC_OUT_MEM_REGION_TYPE);
            }
        break;
        case SYSTEM_BUFFER_TYPE_METADATA:

            pVideoMetaDataBuffer = (System_MetaDataBuffer *)pBuffer->payload;
            for (planes = 0; planes < pVideoMetaDataBuffer->numMetaDataPlanes; planes++)
            {
                if(pVideoMetaDataBuffer->bufAddr[planes] != NULL)
                {
                    pVideoMetaDataBuffer->bufAddr[planes] =
                                         (Void *)OSA_memVirt2Phys(
                                                 (UInt32)pVideoMetaDataBuffer->bufAddr[planes],
                                                 IPC_OUT_MEM_REGION_TYPE);
                }

            }
        break;
        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER:

            pVideoFrameCompositeBuffer = (System_VideoFrameCompositeBuffer *)pBuffer->payload;
            for (frames = 0; frames < pVideoFrameCompositeBuffer->numFrames; frames++)
            {
                for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
                {
                    pVideoFrameCompositeBuffer->bufAddr[planes][frames] =
                                (Void *)OSA_memVirt2Phys(
                                       (UInt32)pVideoFrameCompositeBuffer->bufAddr[planes][frames],
                                        IPC_OUT_MEM_REGION_TYPE);

                }

                pVideoFrameCompositeBuffer->metaBufAddr[frames] =
                                (Void *)OSA_memVirt2Phys(
                                        (UInt32)pVideoFrameCompositeBuffer->metaBufAddr[frames],
                                        IPC_OUT_MEM_REGION_TYPE);

            }
        break;
        case SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME:

            pEglPixmapBuffer = (System_EglPixmapVideoFrameBuffer *)pBuffer->payload;
            for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
            {
                if(pEglPixmapBuffer->bufAddr[planes] != NULL)
                {
                    pEglPixmapBuffer->bufAddr[planes] =
                                       (Void *)OSA_memVirt2Phys(
                                               (UInt32)pEglPixmapBuffer->bufAddr[planes],
                                                IPC_OUT_MEM_REGION_TYPE);
                }
            }
        break;

        default:
            Vps_printf("\nUnsupported System Buffer received on A15!!\n");
            OSA_assert(0);
        break;
    }
}

/**
 *******************************************************************************
 *
 * \brief Copy information from system buffer to IPC buffer
 *
 * \param  pObj        [IN]  Link object
 * \param  pBuffer     [IN]  Pointer to system buffer information
 * \param  pIpcBuffer  [IN]  Pointer to IPC buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void  IpcOutLink_drvCopySystemBufferToIpcBuffer(
                    IpcOutLink_Obj *pObj,
                    System_Buffer *pBuffer,
                    System_IpcBuffer *pIpcBuffer
                    )
{
    UInt32 flags = 0;

    flags = System_Buffer_Flag_Set_Buf_Type(flags, pBuffer->bufType);
    flags = System_Buffer_Flag_Set_Ch_Num(flags, pBuffer->chNum);
    flags = System_Buffer_Flag_Set_Payload_Size(flags, pBuffer->payloadSize);

    pIpcBuffer->flags               = flags;
    pIpcBuffer->orgSystemBufferPtr  = (UInt32)pBuffer;
    pIpcBuffer->srcTimestamp        = pBuffer->srcTimestamp;
    pIpcBuffer->frameId             = pBuffer->frameId;
    pIpcBuffer->linkLocalTimestamp  = pBuffer->linkLocalTimestamp;

    pIpcBuffer->ipcPrfTimestamp64[0] = pBuffer->ipcPrfTimestamp64[0];

    OSA_assert(pBuffer->payloadSize <= SYSTEM_MAX_PAYLOAD_SIZE );

    memcpy(pIpcBuffer->payload, pBuffer->payload, pBuffer->payloadSize);
    if(pBuffer->hlosTranslationDisable == FALSE)
        IpcOutLink_drvTranslateIpcBufferPayloadPtrsVirt2Phys(pIpcBuffer);
}

/**
 *******************************************************************************
 *
 * \brief Check if frame needs to be skipped
 *
 * \param  pObj     [IN] Link object
 * \param  chNum    [IN] channel Id
 *
 * \return TRUE: skip frame, FALSE: process frame
 *
 *******************************************************************************
 */
Bool IpcOutLink_drvDoFrameSkip(IpcOutLink_Obj *pObj, UInt32 chNum)
{
    System_LinkQueInfo *pLinkQueInfo;
    IpcOutLink_ChObj *pChObj;

    pLinkQueInfo = &pObj->linkInfo.queInfo[0];

    if(chNum >=  pLinkQueInfo->numCh )
        return TRUE; /* invalid channel, skip frame */

    pChObj = &pObj->chObj[chNum];

    return OSA_doSkipBuf(&pChObj->bufSkipContext);
}

/**
 *******************************************************************************
 *
 * \brief Process buffer's
 *
 *        - Previous link will send a command NEW_DATA to IPC out link when
 *          buffers are available to be sent across processors
 *
 *        - IPC Out link will call 'get full buffer' to get the buffer
 *           information pointers
 *
 *        - For each buffer information pointer it will
 *          -  Apply frame-rate control and release frame immediately if this
 *             frame needs to be dropped
 *             - continue to next buffer pointer
 *          -  If uni-cache operation
 *             - Insert the pointer into the IPC queue (IPC OUT-> IPC IN Q)
 *             - continue to next buffer pointer
 *          -  If non-uni-cache operation
 *             - Get a IPC shared memory buffer information structures
 *               pointer from local queue
 *             - If no buffer information structures pointer in local queue
 *               then release incoming buffer immediately to previous link
 *               and continue. This should normally not happen but idea is
 *               to let processing continue even in this case
 *             - Translate the information from previous link buffer pointer
 *               to a IPC shared memory buffer information structure
 *             - This is where address is translated if required in case
 *               address space between the two core’s is different
 *             - The original system buffer pointer is also set in the IPC
 *               shared memory buffer information structure
 *             - Insert the IPC shared memory buffer information structure
 *               pointer in the IPC queue (IPC OUT-> IPC IN Q)
 *             - continue to next buffer pointer
 *
 *        - If notify is enabled and at least one element was put into
 *          IPC queue then send a notify to the other processor with
 *          IPC IN link ID as the notify payload. The next processor ID
 *          is embedded inside the next link ID
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvProcessBuffers(IpcOutLink_Obj *pObj)
{
    Int32             status      = SYSTEM_LINK_STATUS_SOK;
    System_Buffer     *pBuffer;
    System_BufferList bufList;
    System_BufferList freeBufList;
    Bool              sendNotify  = FALSE;
    UInt32            bufId;

    if(pObj->isFirstFrameRecv == FALSE)
    {
        OSA_resetLatency(&pObj->linkLatency);
        OSA_resetLatency(&pObj->srcToLinkLatency);

        OSA_resetLinkStatistics(&pObj->linkStats,
                          pObj->linkInfo.queInfo[0].numCh,
                          1);

        pObj->isFirstFrameRecv = TRUE;
    }

    pObj->linkStats.newDataCmdCount++;

    bufList.numBuf = 0;
    System_getLinksFullBuffers(
                    pObj->createArgs.inQueParams.prevLinkId,
                    pObj->createArgs.inQueParams.prevLinkQueId,
                    &bufList);

    freeBufList.numBuf = 0;

    if(bufList.numBuf)
    {
        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {

            pBuffer = bufList.buffers[bufId];
            if(pBuffer==NULL
                ||
               pBuffer->chNum >= pObj->linkInfo.queInfo[0].numCh)
            {
                pObj->linkStats.inBufErrorCount++;
                continue; /* invalid buffer pointer, skip it */
            }
            pBuffer->ipcPrfTimestamp64[0] = OSA_getCurGlobalTimeInUsec();

            pBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

            pObj->linkStats.chStats[pBuffer->chNum].inBufRecvCount++;

            if(IpcOutLink_drvDoFrameSkip(pObj, pBuffer->chNum))
            {
                pObj->linkStats.chStats[pBuffer->chNum].inBufUserDropCount++;

                /* skip frame */
                OSA_assert(freeBufList.numBuf <
                                SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                freeBufList.numBuf++;

                continue;
            }

            OSA_updateLatency(&pObj->linkLatency,
                                pBuffer->linkLocalTimestamp);
            OSA_updateLatency(&pObj->srcToLinkLatency,
                                pBuffer->srcTimestamp);

            System_IpcBuffer *pIpcBuffer;
            Int32 index = -1;

            status =
                OSA_queGet(&pObj->localQue,
                            (Int32 *) &index,
                            OSA_TIMEOUT_FOREVER
                            );

            pIpcBuffer = System_ipcGetIpcBuffer(pObj->linkId, index);

            if(status!=SYSTEM_LINK_STATUS_SOK || pIpcBuffer == NULL)
            {
                pObj->linkStats.chStats[pBuffer->chNum].inBufDropCount++;

                /* if could not get free element from local queue,
                 * then free the system buffer
                 */

                OSA_assert(freeBufList.numBuf <
                                SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                freeBufList.numBuf++;

                continue;
            }

            IpcOutLink_drvCopySystemBufferToIpcBuffer(
                pObj,
                pBuffer,
                pIpcBuffer
                );

            pIpcBuffer->ipcPrfTimestamp64[1] = OSA_getCurGlobalTimeInUsec();

            status = OSA_ipcQueWrite(
                            &pObj->ipcOut2InQue,
                            (UInt8*)&index,
                            sizeof(UInt32)
                            );

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                pObj->linkStats.chStats[pBuffer->chNum].inBufDropCount++;

                /* if could not add element to queue, then free the
                 * system buffer
                 */

                OSA_assert(freeBufList.numBuf <
                                SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                freeBufList.numBuf++;

                /* queue to local queue */
                status = OSA_quePut(&pObj->localQue,
                         (Int32)index,
                         OSA_TIMEOUT_NONE
                    );
                OSA_assert(status==SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                pObj->linkStats.chStats[pBuffer->chNum].inBufProcessCount++;

                pObj->linkStats.chStats[pBuffer->chNum].outBufCount[0]++;

                /* atleast one element successfuly inserted in the IPC que
                 * So send notify to next link
                 */
                sendNotify = TRUE;
            }
        }

        if(freeBufList.numBuf)
        {
            System_putLinksEmptyBuffers(
                pObj->createArgs.inQueParams.prevLinkId,
                pObj->createArgs.inQueParams.prevLinkQueId,
                &freeBufList
                );
        }

        /* if notify mode is enabled and atleast one element added to que
         * then send notify
         */
        if(sendNotify)
        {
            System_ipcSendNotify(pObj->createArgs.outQueParams.nextLink);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Release buffer returned by IPC IN link to previous link
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvReleaseBuffers(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 queStatus = SYSTEM_LINK_STATUS_SOK;
    System_Buffer    *pBuffer;
    Int32 index;
    System_BufferList freeBufList;

    pObj->linkStats.releaseDataCmdCount++;

    freeBufList.numBuf = 0;

    while(queStatus == SYSTEM_LINK_STATUS_SOK)
    {
        while(1)
        {
            index = -1;

            queStatus = OSA_ipcQueRead(
                    &pObj->ipcIn2OutQue,
                    (UInt8*)&index,
                    sizeof(UInt32)
                    );

            if(queStatus!=SYSTEM_LINK_STATUS_SOK)
                break; /* no more data to read from IPC queue */

            System_IpcBuffer *pIpcBuffer;

            pIpcBuffer = System_ipcGetIpcBuffer(pObj->linkId, index);

            if(pIpcBuffer == NULL)
            {
                pObj->linkStats.inBufErrorCount++;
                continue; /* this condition will not happen */
            }

            pBuffer = (System_Buffer*)pIpcBuffer->orgSystemBufferPtr;

            /* queue to local queue */
            status = OSA_quePut(&pObj->localQue,
                         (Int32)index,
                         OSA_TIMEOUT_NONE
                    );
            OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

            if(pBuffer==NULL)
            {
                pObj->linkStats.inBufErrorCount++;
                continue; /* this condition will not happen */
            }

            freeBufList.buffers[freeBufList.numBuf] = pBuffer;
            freeBufList.numBuf++;

            if(freeBufList.numBuf>=SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST)
                break;
        }

        if(freeBufList.numBuf)
        {
            System_putLinksEmptyBuffers(
                pObj->createArgs.inQueParams.prevLinkId,
                pObj->createArgs.inQueParams.prevLinkQueId,
                &freeBufList
                );
        }
    }
    return queStatus;
}

/**
 *******************************************************************************
 *
 * \brief Stop buffer processing
 *
 *        This function must be called before calling delete
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvStop(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Stop Done !!!\n", pObj->linkInstId);
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Set frame-rate
 *
 *        This function controls the rate at which buffers are
 *        processed and dropped
 *
 * \param  pObj     [IN] Link object
 * \param  pPrm     [IN] Frame rate control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvSetFrameRate(IpcOutLink_Obj *pObj,
                              IpcLink_FrameRateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkQueInfo *pLinkQueInfo;
    IpcOutLink_ChObj *pChObj;

    pLinkQueInfo = &pObj->linkInfo.queInfo[0];

    if(pPrm->chNum >=  pLinkQueInfo->numCh )
        return SYSTEM_LINK_STATUS_EINVALID_PARAMS;

    pChObj = &pObj->chObj[pPrm->chNum];

    OSA_resetSkipBufContext(
            &pChObj->bufSkipContext,
            pPrm->inputFrameRate,
            pPrm->outputFrameRate
            );

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print IPC link related statistics
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvPrintStatistics(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

    snprintf(tskName, sizeof(tskName), "IPC_OUT_%u", (unsigned int)pObj->linkInstId);

    OSA_printLinkStatistics(&pObj->linkStats, tskName, TRUE);

    OSA_printLatency( tskName,
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );

    return status;
}

