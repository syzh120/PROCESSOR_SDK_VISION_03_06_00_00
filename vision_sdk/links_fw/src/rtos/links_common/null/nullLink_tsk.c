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
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "nullLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
Int32 NullLink_drvCreateDumpFramesObj(NullLink_Obj * pObj);

Int32 NullLink_drvDumpFrames(NullLink_Obj * pObj, UInt32 inQue,const System_Buffer *pBuf);

Int32 NullLink_drvCreate(NullLink_Obj * pObj,const NullLink_CreateParams * pPrm);

Int32 NullLink_drvProcessFrames(NullLink_Obj * pObj);

Int32 NullLink_drvDeleteDumpFramesObj(NullLink_Obj * pObj);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gNullLink_tskStack, 32)
#pragma DATA_SECTION(gNullLink_tskStack, ".bss:taskStackSection")
UInt8 gNullLink_tskStack[NULL_LINK_OBJ_MAX][NULL_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
NullLink_Obj gNullLink_obj[NULL_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief Create resources and setup info required to dump frames to memory
 *
 * \param  pObj     [IN]  Null link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullLink_drvCreateDumpFramesObj(NullLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Utils_DmaChCreateParams dmaParams;
    NullLink_DumpFramesObj  *pDumpFramesObj;
    UInt16 inQue, chId;
    System_LinkQueInfo *pInQueInfo;
    NullLink_CreateParams * pPrm;
    UInt32 inQueMemSize, chMemSize;

    pPrm = &pObj->createArgs;

    if(pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_2D_MEMORY)
    {
        Utils_DmaChCreateParams_Init(&dmaParams);

        status = Utils_dmaCreateCh(
                        &pObj->dumpFramesDmaObj,
                        &dmaParams
                        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        inQueMemSize =
            pPrm->dumpFramesMemorySize/pPrm->numInQue;

        for (inQue = 0; inQue < pPrm->numInQue; inQue++)
        {
            pInQueInfo = &pObj->inQueInfo[inQue];

            chMemSize = inQueMemSize/pInQueInfo->numCh;

            UTILS_assert(pInQueInfo->numCh <= SYSTEM_MAX_CH_PER_OUT_QUE);
            for (chId = 0; chId < pInQueInfo->numCh; chId++)
            {
                pDumpFramesObj = &pObj->dumpFramesObj[inQue][chId];
                pDumpFramesObj->inQueId = inQue;
                pDumpFramesObj->numFrames = 0;
            /* MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
            * State: Defer -> Waiver -> Case by case
            * Passing pointer arguments to functions which
            * takes arguments as UInt32 for legacy reasons and viceversa
            */
                pDumpFramesObj->memAddr =
                    (UInt32)(pPrm->dumpFramesMemoryAddr
                        + (inQueMemSize*inQue)
                        + (chMemSize*chId));

                pDumpFramesObj->memSize = chMemSize;

                pDumpFramesObj->curMemOffset = 0;
            }
        }
    }
    else if(pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_BITSTREAM_MEMORY)
    {
        /* Memory has to be allocated by the user in the usecase */
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
 * \brief Delete null link
 *
 *
 * \param  pObj         [IN] Null link object
 *
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 NullLink_drvDeleteDumpFramesObj(NullLink_Obj * pObj)
{
    Int32 status;

    if(pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_2D_MEMORY)
    {
        Utils_dmaDeleteCh(&pObj->dumpFramesDmaObj);
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
 * \param  pObj     [IN]  Null link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 NullLink_drvDumpFrames(NullLink_Obj * pObj,
                            UInt32 inQue,
                            const System_Buffer *pBuf)
{
    System_LinkChInfo *pChInfo;
    Int32 status;
    UInt32 offsetUV = 0U;
    UInt32 dataFormat, memCopySize = 0;
    UInt32 memAddr = 0x00U;
    System_LinkStatistics *linkStatsInfo = pObj->linkStatsInfo;

    if((pObj->createArgs.dumpDataType > 0U)
            &&
       (pBuf!=NULL)
            &&
       (inQue < NULL_LINK_MAX_IN_QUE)
            &&
       (pBuf->chNum < SYSTEM_MAX_CH_PER_OUT_QUE)
            &&
       (inQue < pObj->createArgs.numInQue)
            &&
       (pBuf->chNum < pObj->inQueInfo[inQue].numCh))
    {
        NullLink_DumpFramesObj  *pDumpFramesObj;

        pDumpFramesObj = &pObj->dumpFramesObj[inQue][pBuf->chNum];

        pChInfo = &pObj->inQueInfo[inQue].chInfo[pBuf->chNum];

        linkStatsInfo->linkStats.chStats[pBuf->chNum].
                inBufProcessCount++;

        Utils_updateLatency(&linkStatsInfo->linkLatency,
                                pBuf->linkLocalTimestamp);
        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pBuf->srcTimestamp);

        if((pBuf->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME) &&
           (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_2D_MEMORY))
        {
            System_VideoFrameBuffer *pVidFrame =
                (System_VideoFrameBuffer *)pBuf->payload;

            Utils_DmaCopyFill2D dmaPrm;

            dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

            if((dataFormat==SYSTEM_DF_YUV422I_YUYV)
                ||
                (dataFormat==SYSTEM_DF_YUV422I_UYVY)
                ||
                (dataFormat==SYSTEM_DF_RGB16_565)
                ||
                (dataFormat==SYSTEM_DF_BGR16_565))
            {
                memCopySize = pChInfo->pitch[0]*pChInfo->height*2U;

                dmaPrm.dataFormat = SYSTEM_DF_RAW16;
            }
            if(dataFormat==SYSTEM_DF_YUV420SP_UV)
            {
                offsetUV = pChInfo->pitch[0]*pChInfo->height;

                memCopySize = (offsetUV*3U)/2U;

                dmaPrm.dataFormat = SYSTEM_DF_YUV420SP_UV;
            }

            if((pDumpFramesObj->curMemOffset+memCopySize)
                    >= pDumpFramesObj->memSize
               )
            {
                Vps_printf(
                    " NULL: Q%d: CH%d: Dumped %d frames @ 0x%08x, size: %d bytes !!!\n",
                        pDumpFramesObj->inQueId,
                        pDumpFramesObj->numFrames,
                        pDumpFramesObj->memAddr,
                        pDumpFramesObj->curMemOffset
                );

                pDumpFramesObj->curMemOffset = 0;
                pDumpFramesObj->numFrames = 0;
            }
            /* MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
            * State: Defer -> Waiver -> Case by case
            * Passing pointer arguments to functions which
            * takes arguments as UInt32 for legacy reasons and viceversa
            */

            memAddr = pDumpFramesObj->memAddr + pDumpFramesObj->curMemOffset;
            dmaPrm.destAddr[0]= (Ptr)memAddr;
            memAddr = (UInt32)dmaPrm.destAddr[0] + offsetUV;
            dmaPrm.destAddr[1]= (Ptr)memAddr;
            dmaPrm.destPitch[0] = pChInfo->pitch[0];
            dmaPrm.destPitch[1] = pChInfo->pitch[1];
            dmaPrm.destStartX   = 0;
            dmaPrm.destStartY   = 0;
            dmaPrm.width        = pChInfo->width;
            dmaPrm.height       = pChInfo->height;
            dmaPrm.srcAddr[0]   = pVidFrame->bufAddr[0];
            dmaPrm.srcAddr[1]   = pVidFrame->bufAddr[1];
            dmaPrm.srcPitch[0]  = pChInfo->pitch[0];
            dmaPrm.srcPitch[1]  = pChInfo->pitch[1];
            dmaPrm.srcStartX    = pChInfo->startX;
            dmaPrm.srcStartY    = pChInfo->startY;

            status = Utils_dmaCopy2D(&pObj->dumpFramesDmaObj, &dmaPrm, 1U);
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

            pDumpFramesObj->curMemOffset += memCopySize;
            pDumpFramesObj->numFrames++;

        }else if((pBuf->bufType == SYSTEM_BUFFER_TYPE_BITSTREAM) &&
                 (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_BITSTREAM_MEMORY))
        {
            System_BitstreamBuffer *bitstreamBuf;
            bitstreamBuf = ((System_BitstreamBuffer *)pBuf->payload);
            if ((pObj->dataDumpSize + bitstreamBuf->fillLength) <
                 pObj->createArgs.dumpFramesMemorySize)
            {
                memcpy(pObj->dataDumpPtr,
                       bitstreamBuf->bufAddr,
                       bitstreamBuf->fillLength);
                pObj->dataDumpPtr += bitstreamBuf->fillLength;
                pObj->dataDumpSize += bitstreamBuf->fillLength;
            }
        }
        else if(pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
        {
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

            if(pBuf->bufType == SYSTEM_BUFFER_TYPE_BITSTREAM)
            {
                System_BitstreamBuffer *bitstreamBuf;

                bitstreamBuf = ((System_BitstreamBuffer *)pBuf->payload);
                /* Cache invalidate required as CPU copy is used */
                Cache_inv(
                        bitstreamBuf->bufAddr,
                        bitstreamBuf->fillLength,
                        (UInt16)Cache_Type_ALLD,
                        (Bool)TRUE
                        );

                    File_write(pObj->fpDataStream[pBuf->chNum], bitstreamBuf->bufAddr, bitstreamBuf->fillLength);
                    File_write(pObj->fpDataStreamHdr[pBuf->chNum], (UInt8 *)&bitstreamBuf->fillLength,sizeof(bitstreamBuf->fillLength));
            }
            else if(pBuf->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
            {
                System_VideoFrameBuffer *pVidFrame =
                    (System_VideoFrameBuffer *)pBuf->payload;

                pChInfo = &pObj->inQueInfo[inQue].chInfo[pBuf->chNum];

                dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

                if((dataFormat==SYSTEM_DF_YUV422I_YUYV)
                    ||
                    (dataFormat==SYSTEM_DF_YUV422I_UYVY)
                    ||
                    (dataFormat==SYSTEM_DF_RGB16_565)
                    ||
                    (dataFormat==SYSTEM_DF_BGR16_565))
                {
                    memCopySize = pChInfo->pitch[0]*pChInfo->height*2U;
                }
                if(dataFormat==SYSTEM_DF_YUV420SP_UV)
                {
                    memCopySize = (pChInfo->pitch[0]*pChInfo->height*3U)/2U;
                }

                Cache_inv(
                        pVidFrame->bufAddr[0],
                        memCopySize,
                        (UInt16)Cache_Type_ALLD,
                        (Bool)TRUE
                        );

                    File_write(pObj->fpDataStream[pBuf->chNum],
                                pVidFrame->bufAddr[0],
                                memCopySize);
            }
#else
        Vps_printf(" \n FATFS_PROC_TO_USE is not in the same core as null link \n ");
#endif
        }
        else
        {
            /* MISRA-C Fix */
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}


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
Int32 NullLink_drvCreate(NullLink_Obj * pObj,const NullLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt16 inQue;
    System_LinkInfo inTskInfo;

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    UTILS_assert(pObj->createArgs.numInQue < NULL_LINK_MAX_IN_QUE);

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

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId, "NULL");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool)FALSE;

    /*
     * Create resources and setup info required for NULL link as per data
     * dump type
     */
    NullLink_drvCreateDumpFramesObj(pObj);

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
                    * Reset the null link statistics when first buffer is received from the
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

                NullLink_drvDumpFrames(pObj, queId, bufList.buffers[bufId]);

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
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Null link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NullLink_printLinkStats(const NullLink_Obj * pObj)
{
    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                              "NULL_SRC",
                              (Bool)TRUE);
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

Void NullLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    UInt32 chId;
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    NullLink_Obj *pObj = (NullLink_Obj *) pTsk->appData;
    UInt32 flushCmds[1];
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    char hdrFileName[260] = { 0 };
#endif

    if (cmd != SYSTEM_CMD_CREATE)
    {
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        status = NullLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

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
                    if (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_BITSTREAM_MEMORY)
                    {
                        pObj->dataDumpPtr = pObj->createArgs.dumpFramesMemoryAddr;
                        UTILS_assert (pObj->createArgs.dumpFramesMemorySize != 0);
                        pObj->dataDumpSize = 0;
                    }
                    if (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
                    {
                        for (chId=0; chId<pObj->inQueInfo[0].numCh; chId++)
                        {
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )
                            Vps_printf(" NULL LINK: Opening file for Dump \n");
                            pObj->fpDataStream[chId] = File_open((char *)pObj->createArgs.nameDataFile[chId], "wb");
                            UTILS_assert(pObj->fpDataStream[chId] != -1);

                            sprintf(hdrFileName, "%s.hdr",(char *)pObj->createArgs.nameDataFile[chId]);
                            pObj->fpDataStreamHdr[chId] = File_open((char *)hdrFileName, "w");
                            UTILS_assert(pObj->fpDataStreamHdr[chId] != -1);
                            Vps_printf(" NULL LINK: Opened file for Dump \n");
#endif
                        }
                    }
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
                case SYSTEM_CMD_STOP:
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    if (pObj->createArgs.dumpDataType == NULL_LINK_COPY_TYPE_FILE)
                    {
                        for (chId=0; chId<pObj->inQueInfo[0].numCh; chId++)
                        {
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )
                            Vps_printf(" NULL LINK: Closing Dump file \n");
                            if(pObj->fpDataStream[chId] != -1)
                            {
                                File_flush(pObj->fpDataStream[chId]);
                                File_close(pObj->fpDataStream[chId]);

                                if(pObj->fpDataStreamHdr[chId] != -1)
                                {    File_flush(pObj->fpDataStreamHdr[chId]);
                                    File_close(pObj->fpDataStreamHdr[chId]);
                                }
                            }
                            Vps_printf(" NULL LINK: Closed dump file \n");
#endif
                        }
                    }
                    break;
                case SYSTEM_CMD_PRINT_STATISTICS:
                    /* print the null link statistics*/
                    NullLink_printLinkStats(pObj);
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

                    NullLink_drvProcessFrames(pObj);
                    break;
                default:
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        NullLink_drvDeleteDumpFramesObj(pObj);

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

        snprintf(pObj->name, 32U, "NULL%d  ", (UInt32)nullId);

        status = Utils_tskCreate(&pObj->tsk,
                                 NullLink_tskMain,
                                 NULL_LINK_TSK_PRI,
                                 gNullLink_tskStack[nullId],
                                 NULL_LINK_TSK_STACK_SIZE, pObj, pObj->name,
                                 UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
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
        Utils_tskDelete(&gNullLink_obj[nullId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
