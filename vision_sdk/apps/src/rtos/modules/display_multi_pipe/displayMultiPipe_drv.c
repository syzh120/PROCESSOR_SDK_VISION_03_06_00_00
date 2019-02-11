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
 *******************************************************************************
 * \file displayMultiPipeLink_drv.c
 *
 * \brief  This file has the implementation of Display Multi Pipe Link
 *
 * \version 0.0 (Jun 2017) : [BJ] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "displayMultiPipe_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
static Void DisplayMpLink_drvCreateQueues(DisplayMpLink_Obj *pObj);
static Void DisplayMpLink_allocFrames(DisplayMpLink_Obj *pObj);
static Void DisplayMpLink_freeFrames(DisplayMpLink_Obj *pObj);
static Int32 DisplayMpLink_drvDisplayCreate(DisplayMpLink_Obj *pObj,
    UInt32 pipeId, UInt32 isRegisterCb);

Int32 DisplayMpLink_drvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved);


char *gDisplayMpLink_displayName[] = { "VID1", "VID2", "VID3", "GRPX1" };

/*
 *******************************************************************************
 *
 * This function is used to create queue's that will be used within this link
 *
 *******************************************************************************
 */
static Void DisplayMpLink_drvCreateQueues(DisplayMpLink_Obj *pObj)
{
    Int32 status;
    UInt32 i;

    status = Utils_queCreate(&pObj->freeQueue,
                             DISPLAY_MP_LINK_MAX_FRAMES_PER_HANDLE,
                             pObj->freeQueueMem,
                             UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_queCreate(&pObj->readyQueue,
                             DISPLAY_MP_LINK_MAX_FRAMES_PER_HANDLE,
                             pObj->readyQueueMem,
                             UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Enqueue all request objects to the free queue initially */
    for (i = 0U; i < DISPLAY_MP_LINK_MAX_FRAMES_PER_HANDLE; i++)
    {
        status = Utils_quePut(&pObj->freeQueue,
                              &pObj->reqObjs[i],
                              BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }
}

static Void DisplayMpLink_allocFrames(DisplayMpLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 pipeId, size, coffset = 0, frameId;
    Vps_DispDssParams *dssPrms;
    UInt8 *pBaseAddr;
    Fvid2_Frame *pFrame;

    for (pipeId = 1u; pipeId < pObj->numPipes; pipeId ++)
    {
        dssPrms = &pObj->dssPrms[pipeId];

        status = Utils_memFrameGetSize(&dssPrms->inFmt, &size, &coffset, 0);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

        pObj->bufSize[pipeId] = size * DISPLAY_MP_LINK_MAX_FRAMES_PER_HANDLE;

        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo) ==
            FALSE)
        {
            pObj->bufStartPtr[pipeId] = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pObj->bufSize[pipeId],
                            VPS_BUFFER_ALIGNMENT);
        }
        else
        {
            pObj->bufStartPtr[pipeId] =
                     System_allocLinkMemAllocInfo(
                            &pObj->createArgs.memAllocInfo,
                            pObj->bufSize[pipeId],
                            VPS_BUFFER_ALIGNMENT);
        }
        UTILS_assert(pObj->bufStartPtr[pipeId] != NULL);

        pBaseAddr = pObj->bufStartPtr[pipeId];

        for (frameId = 0u; frameId < DISPLAY_MP_LINK_MAX_FRAMES_PER_HANDLE;
                frameId ++)
        {
            pFrame = &pObj->reqObjs[frameId].frames[pipeId];

            memset(pFrame, 0, sizeof(FVID2_Frame));

            pFrame->chNum       = dssPrms->inFmt.chNum;
            pFrame->addr[0][0]  = pBaseAddr;
            pFrame->addr[0][1]  = pBaseAddr + coffset;
            pBaseAddr += size;
        }
    }
}

static Void DisplayMpLink_freeFrames(DisplayMpLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 pipeId;

    for (pipeId = 1u; pipeId < pObj->numPipes; pipeId ++)
    {
        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo) ==
            FALSE)
        {
            status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pObj->bufStartPtr[pipeId],
                pObj->bufSize[pipeId]);

            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }
    }
}


static Void DisplayMpLink_setMetaData(DisplayMpLink_Obj *pObj, UInt32 pipeId,
    UInt8 *addr, System_Buffer *sysBuff)
{
    if ((NULL != pObj) && (NULL != addr) && (NULL != sysBuff))
    {
        *(UInt32*)addr = sysBuff->frameId;
        addr += sizeof(UInt32);
        *(UInt64*)addr = sysBuff->srcTimestamp;
        addr += sizeof(UInt64);
        *(UInt64*)addr = sysBuff->linkLocalTimestamp;

        Cache_wb(
            addr,
            pObj->bufSize[pipeId],
            Cache_Type_ALLD,
            TRUE);
    }
}
/*
 *******************************************************************************
 *
 * This function is the callback that is called by the driver at every
 * display Vsync
 *
 * In this callback, we do the below
 * - Ignore first callback to make all the pipelines in sync
 * - Dequeue a frame from ready queue and enqueue a fvid2 frame to
 *   all the pipelines
 * - Sends command to display link to release/dequeue frames
 *
 *******************************************************************************
 */
Int32 DisplayMpLink_drvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32 status;
    DisplayMpLink_Obj *pObj = (DisplayMpLink_Obj *) appData;
    FVID2_FrameList frameList;
    UInt32 i;
    DisplayMpLink_ReqObj *pReqObj;

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    /* ignore the first callback so that all pipelines are in sync */
    if ((pObj->linkStatsInfo->linkStats.notifyEventCount > 1u) &&
        (FALSE == Utils_queIsEmpty(&pObj->readyQueue)))
    {
        status = Utils_queGet(&pObj->readyQueue,
                     (Ptr*)&pReqObj,
                     1U,
                     BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        for (i = 0u; i < pObj->numPipes; i ++)
        {
            frameList.frames[0] = &pReqObj->frames[i];
            frameList.numFrames = 1u;

            status = FVID2_queue(
                        pObj->displayHndl[i],
                        &frameList,
                        0);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

        /* Dequeue a frame from the display driver */
        Utils_tskSendCmd(&pObj->tsk, DISPLAY_MP_LINK_CMD_DEQUEUE_FRAMES, NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/*
 *******************************************************************************
 *
 * This function creates the FVID2 driver
 *
 *******************************************************************************
 */
static Int32 DisplayMpLink_drvDisplayCreate(DisplayMpLink_Obj *pObj,
    UInt32 pipeId, UInt32 isRegisterCb)
{
    Int32 status;
    FVID2_CbParams cbParams;
    Vps_DispDssParams *dssPrms;
    System_LinkChInfo *pInChInfo;
    Vps_DispCreateStatus displayCreateStatus;

    pInChInfo = &pObj->inQueInfo.chInfo[pObj->curDisplayChannelNum];
    dssPrms = &pObj->dssPrms[pipeId];

    switch (pObj->createArgs.displayId[pipeId])
    {
        case DISPLAY_MP_LINK_INST_DSS_VID1:
            pObj->displayInstId[pipeId] = VPS_DISP_INST_DSS_VID1;
            break;
        case DISPLAY_MP_LINK_INST_DSS_VID2:
            pObj->displayInstId[pipeId] = VPS_DISP_INST_DSS_VID2;
            break;
        case DISPLAY_MP_LINK_INST_DSS_VID3:
            pObj->displayInstId[pipeId] = VPS_DISP_INST_DSS_VID3;
            if(Bsp_platformIsTda3xxFamilyBuild())
            {
                Vps_printf(" DISPLAY: DSS_VID3_PIPE NOT supported on TDA3xx"
                       " !!!\n"
                       );
                UTILS_assert((Bool)0U);
            }
            break;
        case DISPLAY_MP_LINK_INST_DSS_GFX1:
            pObj->displayInstId[pipeId] = VPS_DISP_INST_DSS_GFX1;
            break;
        default:
            pObj->displayInstId[pipeId] = VPS_DISP_INST_DSS_VID1;
            break;
    }

    Fvid2CbParams_init(&cbParams);
    if (isRegisterCb)
    {
        cbParams.cbFxn = &DisplayMpLink_drvFvidCb;
    }
    else
    {
        /* Callback is registered only for the first/primary pipe,
           which is at the index-0 */
        cbParams.cbFxn = NULL;
    }
    cbParams.appData = pObj;

    VpsDispCreateParams_init(&pObj->displayCreateArgs[pipeId]);
    pObj->displayCreateArgs[pipeId].periodicCbEnable = TRUE;

    pObj->displayHndl[pipeId] = FVID2_create(FVID2_VPS_DISP_DRV,
                                     pObj->displayInstId[pipeId],
                                     &pObj->displayCreateArgs[pipeId],
                                     &displayCreateStatus, &cbParams);
    UTILS_assert(pObj->displayHndl[pipeId] != NULL);

    VpsDispDssParams_init(dssPrms);

    VpsDssDispcVidConfig_init(&pObj->vidCfg[pipeId]);
    VpsDssDispcGfxConfig_init(&pObj->gfxCfg[pipeId]);

    if (Vps_dispIsVidInst(pObj->displayInstId[pipeId]))
    {
        dssPrms->vidCfg = &pObj->vidCfg[pipeId];
    }
    if (Vps_dispIsGfxInst(pObj->displayInstId[pipeId]))
    {
        dssPrms->gfxCfg = &pObj->gfxCfg[pipeId];
    }

    dssPrms->inFmt.chNum           = 0;

    if (pObj->createArgs.prms[pipeId].overrideSrcSize)
    {
        dssPrms->inFmt.width      = pObj->createArgs.prms[pipeId].srcWidth;
        dssPrms->inFmt.height     = pObj->createArgs.prms[pipeId].srcHeight;
        dssPrms->inFmt.pitch[0u]  = pObj->createArgs.prms[pipeId].srcPitch[0U];
        dssPrms->inFmt.pitch[1u]  = pObj->createArgs.prms[pipeId].srcPitch[1U];
        dssPrms->inFmt.pitch[2u]  = pObj->createArgs.prms[pipeId].srcPitch[2U];
        dssPrms->inFmt.dataFormat = pObj->createArgs.prms[pipeId].srcDataFormat;
    }
    else
    {
        dssPrms->inFmt.width           = pInChInfo->width;
        dssPrms->inFmt.height          = pInChInfo->height;
        dssPrms->inFmt.pitch[0u]       = pInChInfo->pitch[0];
        dssPrms->inFmt.pitch[1u]       = pInChInfo->pitch[1];
        dssPrms->inFmt.pitch[2u]       = pInChInfo->pitch[2];
        dssPrms->inFmt.dataFormat      =
            System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
    }

    if(dssPrms->inFmt.dataFormat == SYSTEM_DF_ABGR32_8888)
    {
        /* Convert to equivalent Display format */
        dssPrms->inFmt.dataFormat = SYSTEM_DF_BGRA32_8888;
    }
    dssPrms->inFmt.fieldMerged[0] = FALSE;
    dssPrms->inFmt.scanFormat = FVID2_SF_PROGRESSIVE;
    if (pObj->createArgs.displayScanFormat == SYSTEM_SF_INTERLACED)
    {
        dssPrms->inFmt.fieldMerged[0] = (UInt32)TRUE;
        dssPrms->inFmt.scanFormat = FVID2_SF_INTERLACED;
    }
    dssPrms->inFmt.fieldMerged[1] = dssPrms->inFmt.fieldMerged[0];
    dssPrms->inFmt.fieldMerged[2] = dssPrms->inFmt.fieldMerged[0];
    dssPrms->inFmt.bpp = FVID2_BPP_BITS16;
    dssPrms->inFmt.reserved = NULL;

    if (pObj->createArgs.prms[pipeId].tarWidth == 0)
    {
       pObj->createArgs.prms[pipeId].tarWidth = dssPrms->inFmt.width;
    }
    if (pObj->createArgs.prms[pipeId].tarHeight == 0)
    {
       pObj->createArgs.prms[pipeId].tarHeight = dssPrms->inFmt.height;
    }

    dssPrms->tarWidth  = pObj->createArgs.prms[pipeId].tarWidth;
    dssPrms->tarHeight = pObj->createArgs.prms[pipeId].tarHeight;
    dssPrms->posX      = pObj->createArgs.prms[pipeId].posX;
    dssPrms->posY      = pObj->createArgs.prms[pipeId].posY;
    dssPrms->memType   = VPS_VPDMA_MT_NONTILEDMEM;

    pObj->vidCfg[pipeId].pipeCfg.scEnable = TRUE;
    if ((dssPrms->inFmt.width == dssPrms->tarWidth) &&
         (dssPrms->inFmt.height == dssPrms->tarHeight))
    {
        pObj->vidCfg[pipeId].pipeCfg.scEnable = FALSE;
    }

    status = FVID2_control(
                 pObj->displayHndl[pipeId],
                 IOCTL_VPS_DISP_SET_DSS_PARAMS,
                 dssPrms,
                 NULL);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Display link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - Set the internal data structures
 *        - Set the default display channel number
 *        - Call the driver create and control functions
 *
 * \param   pObj     [IN] Display Link Instance handle
 * \param   pPrm     [IN] Display link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DisplayMpLink_drvCreate(DisplayMpLink_Obj *pObj,
                              const DisplayMpLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 pipeId;
    UInt32 isRegisterCb = 1;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Create in progress !!!\n");
#endif

    if (DISPLAY_MP_LINK_MAX_PIPE < pPrm->numPipes)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        UTILS_MEMLOG_USED_START();

        pObj->isDisplayRunning = FALSE;
        pObj->queueCount = pObj->dqCount = 0;

        memcpy(&pObj->createArgs, pPrm, sizeof(DisplayMpLink_CreateParams));

        status = System_linkGetInfo(pPrm->inQueParams.prevLinkId,
                                    &pObj->inTskInfo);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

        memcpy(&pObj->inQueInfo,
               &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
               sizeof(pObj->inQueInfo));

        pObj->numPipes = pPrm->numPipes;

        for (pipeId = 0U; pipeId < pPrm->numPipes; pipeId ++)
        {
            if (pObj->createArgs.displayScanFormat == SYSTEM_SF_INTERLACED)
            {
                    pObj->createArgs.prms[pipeId].posY =
                        pObj->createArgs.prms[pipeId].posY / 2U;
            }
            if (0U == pipeId)
            {
                isRegisterCb = 1U;
            }
            else
            {
                isRegisterCb = 0U;
            }
            /* Assume channel 0 will be display as default in the create time*/
            DisplayMpLink_drvDisplayCreate(pObj, pipeId, isRegisterCb);
        }
        DisplayMpLink_allocFrames(pObj);
        DisplayMpLink_drvCreateQueues(pObj);

        /* Assign pointer to link stats object */
        pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->tskId,
            "DISPLAY_MultiPipe");
        UTILS_assert(NULL != pObj->linkStatsInfo);

        pObj->isFirstFrameRecv = (Bool)FALSE;

        UTILS_MEMLOG_USED_END(pObj->memUsed);
        UTILS_MEMLOG_PRINT("DISPLAY_MultiPipe:",
                           pObj->memUsed,
                           UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_DISPLAY
        Vps_printf(" DISPLAY: Create Done !!!\n");
#endif
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function prints the Link status
 *
 *        prints the Link status, such as
 *        - FPS
 *        - Callback Intervals
 *        - Input DropCount
 *        - etc
 *
 * \param   pObj        [IN] Display Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DisplayMpLink_drvPrintStatistics(DisplayMpLink_Obj *pObj)
{
    Vps_DispStatus dispStaus;
    UInt32 pipeId, dispId;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
        "DISPLAY_MultiPipe", (Bool)TRUE);

    Utils_printLatency("DISPLAY_MultiPipe",
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       (Bool)TRUE);

    for (pipeId = 0u; pipeId < pObj->createArgs.numPipes; pipeId ++)
    {
        dispId = pObj->displayInstId[pipeId];
        if (pObj->displayHndl[pipeId])
        {
            Int32 status;

            status =
            FVID2_control(pObj->displayHndl[pipeId],
                          IOCTL_VPS_DISP_GET_STATUS,
                          &dispStaus,NULL);
            if (SYSTEM_LINK_STATUS_SOK == status)
            {
                Vps_printf(" \n");
                Vps_printf(" [ DISPLAY %5s ] Additional Statistics,\n",
                    gDisplayMpLink_displayName[dispId]);
                Vps_printf(" ************************************\n");
                Vps_printf(" Driver Queued    = %6d frames \n",
                                dispStaus.queueCount);
                Vps_printf(" Driver De-Queued = %6d frames \n",
                                dispStaus.dequeueCount);
                Vps_printf(" Driver Displayed = %6d frames \n",
                                dispStaus.dispFrmCount);
                Vps_printf(" Driver Repeated  = %6d frames \n",
                                dispStaus.repeatFrmCount);
                Vps_printf(" \n");
                Vps_printf(" ##### DSS DISPC Underflow Count  = %6d #####\n",
                                dispStaus.underflowCount);
                Vps_printf(" \n");
            }
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * This function releases System_Buffer's queued from ISR context to the
 * previous link
 *
 *******************************************************************************
 */
Int32 DisplayMpLink_drvReleaseData(DisplayMpLink_Obj *pObj)
{
    Int32 status;
    UInt32 pipeId, i, numDeqBufs;
    Fvid2_FrameList frameList;
    Fvid2_Frame *pFrame;
    System_BufferList bufList;
    System_LinkInQueParams *pInQueParams;
    DisplayMpLink_ReqObj *pReqObj;

    bufList.numBuf = 0u;
    for (pipeId = 0u; pipeId < pObj->numPipes; pipeId ++)
    {
        frameList.numFrames = 0u;

        status = FVID2_dequeue(
                    pObj->displayHndl[pipeId],
                    &frameList,
                    0u,
                    BSP_OSAL_NO_WAIT);

        if (0U == pipeId)
        {
            numDeqBufs = frameList.numFrames;

            pObj->dqCount += numDeqBufs;
            for(i = 0U; i < frameList.numFrames; i++)
            {
                pFrame = frameList.frames[i];

                pReqObj = (DisplayMpLink_ReqObj *)pFrame->appData;

                UTILS_assert(NULL != pReqObj);

                UTILS_assert(NULL != pReqObj->sysBuff);

                bufList.buffers[bufList.numBuf] = pReqObj->sysBuff;
                bufList.numBuf++;

                /* Put back the buffers to free queue */
                status = Utils_quePut(&pObj->freeQueue,
                                      pReqObj,
                                      BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
        else
        {
            /* Release Data runs on task context, so absolute difference
               between these two pipes should be at max 1 */
            if (abs(numDeqBufs - frameList.numFrames) > 1u)
            {
                Vps_printf(
                    "DisplayMultiPipeLink: Displays are running out of sync\n");
                UTILS_assert(FALSE);
            }
        }
    }

    /* release buffers to previous link */
    if (bufList.numBuf)
    {
        pInQueParams = &pObj->createArgs.inQueParams;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId,
                                    &bufList);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * This function get buffer's from previous link and display's the buffer
 * associated with current active channel
 *
 * All other CH buffer's are released as
 *
 *******************************************************************************
 */
Int32 DisplayMpLink_drvProcessData(DisplayMpLink_Obj *pObj)
{
    System_BufferList bufList;
    System_BufferList freeBufList;
    FVID2_FrameList displayFrameList;
    System_LinkInQueParams *pInQueParams;
    FVID2_Frame *pFrame;
    System_Buffer *pBuffer = NULL;
    Int32 status;
    UInt32 frameIdx, pipeId;
    System_LinkStatistics *linkStatsInfo;
    System_VideoFrameBuffer *pVideoFrame;
    UInt32 offsetY, offsetUV;
    DisplayMpLink_ReqObj *pReqObj;
    UInt32 temp32;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams;

    /* get frames from previous link */
    bufList.numBuf = 0u;
    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId,
                               &bufList);

    if(pObj->isDisplayRunning)
    {
        /* init number of frames to be released to 0 */
        freeBufList.numBuf = 0;

        /* handle each received frame */
        for(frameIdx = 0U;  frameIdx < bufList.numBuf; frameIdx++)
        {
            /* reset stats counter if this is first frame that is recived */
            if(FALSE == pObj->isFirstFrameRecv)
            {
                pObj->isFirstFrameRecv = (Bool)TRUE;

                Utils_resetLinkStatistics(
                        &linkStatsInfo->linkStats,
                        pObj->inQueInfo.numCh,
                        0);

                Utils_resetLatency(&linkStatsInfo->linkLatency);
                Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
            }

            pBuffer = bufList.buffers[frameIdx];

            UTILS_assert(pBuffer->chNum < pObj->inQueInfo.numCh);

            if (pBuffer->chNum != pObj->curDisplayChannelNum)
            {
                /* if this is not the current channel to be displayed
                 * put buffer in buffer list to be released
                 */
                freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                freeBufList.numBuf++;
                linkStatsInfo->linkStats.chStats[pBuffer->chNum].
                    inBufDropCount++;
            }
            else
            {
                /* display this frame */

                linkStatsInfo->linkStats.chStats[pBuffer->chNum].
                    inBufRecvCount++;

                pBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                /* get FVID2 frame to queue to the driver
                 * This should not fail.
                 */
                status  = Utils_queGet(&pObj->freeQueue,
                                       (Ptr *)&pReqObj,
                                       1U,
                                       BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                UTILS_assert(pReqObj != NULL);

                pReqObj->sysBuff = pBuffer;
                for (pipeId = 0u; pipeId < pObj->numPipes; pipeId ++)
                {
                    pFrame = &pReqObj->frames[pipeId];

                    if (0U == pipeId)
                    {
                        pVideoFrame = pBuffer->payload;
                        UTILS_assert(pVideoFrame != NULL);

                        /* copy info from System buffer to FVID2 frame */
                        status = Utils_bufInitFrame(pFrame, pBuffer);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                        if ((pVideoFrame->chInfo.startX != 0u) ||
                            (pVideoFrame->chInfo.startY != 0u))
                        {
                            offsetY  = ((pVideoFrame->chInfo.pitch[0] *
                                         pVideoFrame->chInfo.startY) +
                                         pVideoFrame->chInfo.startX);
                            offsetUV = offsetY;
                            if (SYSTEM_DF_YUV420SP_UV ==
                                    pObj->dssPrms[pipeId].inFmt.dataFormat)
                            {
                                offsetUV = ((pVideoFrame->chInfo.pitch[1] *
                                    (pVideoFrame->chInfo.startY/2U)) +
                                    pVideoFrame->chInfo.startX);
                            }

                            temp32 = ((UInt32)pFrame->addr[0U][0U] + offsetY);
                            pFrame->addr[0U][0U] = (UInt8 *) (temp32);
                            temp32 = ((UInt32)pFrame->addr[0U][1U] + offsetUV);
                            pFrame->addr[0U][1U] = (UInt8 *) (temp32);
                        }

                        /* Set FVID2 plane address for odd field's */
                        pFrame->addr[1U][0U] =
                            (UInt8 *) pFrame->addr[0U][0U] +
                            pObj->dssPrms[pipeId].inFmt.pitch[0U];
                        pFrame->addr[1U][1U] =
                            (UInt8 *) pFrame->addr[0U][1U] +
                            pObj->dssPrms[pipeId].inFmt.pitch[1U];

                        pFrame->appData = pReqObj;
                    }
                    else
                    {
                        pVideoFrame = pBuffer->payload;
                        UTILS_assert(pVideoFrame != NULL);

                        pFrame->chNum     = pBuffer->chNum;
                        pFrame->timeStamp = pBuffer->linkLocalTimestamp;
                        pFrame->fid =
                            System_Video_Frame_Get_Flag_Fid(pVideoFrame->flags);
                        pFrame->appData = NULL;

                        DisplayMpLink_setMetaData(pObj, pipeId,
                            pFrame->addr[0u][0u], pBuffer);
                    }

                    if (0 == pObj->queueCount)
                    {
                        /* queue frame for display */
                        displayFrameList.numFrames = 1U;
                        displayFrameList.frames[0U] = pFrame;
                        displayFrameList.perListCfg = NULL;

                        status = FVID2_queue(pObj->displayHndl[pipeId],
                                             &displayFrameList,
                                             0U);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }
                }

                if (0 != pObj->queueCount)
                {
                    status = Utils_quePut(&pObj->readyQueue, (Ptr)pReqObj,
                        BSP_OSAL_NO_WAIT);

                    if(status != SYSTEM_LINK_STATUS_SOK)
                    {
                        /* if frame could not be queued to driver
                         *   then release the frame
                         */
                        Vps_printf(
                        " DISPLAY_MultiPipe: Failed to queue buffer to "
                          "fullqueue !!\n");

                        /* Return this system buffer back to previous link */
                        freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                        freeBufList.numBuf++;

                        /* Keep request object back in free queue */
                        Utils_quePut(&pObj->freeQueue,
                                     (Ptr)pReqObj,
                                     BSP_OSAL_NO_WAIT);

                        linkStatsInfo->linkStats.chStats[pBuffer->chNum].
                            inBufDropCount++;
                    }
                    else
                    {
                        linkStatsInfo->linkStats.chStats[pBuffer->chNum].
                                inBufProcessCount++;

                        Utils_updateLatency(&linkStatsInfo->linkLatency,
                                                pBuffer->linkLocalTimestamp);
                        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                                pBuffer->srcTimestamp);
                    }
                }
                else /* On the first frame, queue it to the driver and
                       start the driver */
                {
                    for (pipeId = 0u; pipeId < pObj->numPipes; pipeId ++)
                    {
                        status = FVID2_start(pObj->displayHndl[pipeId], NULL);
                        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                    }
                }

                if (SYSTEM_LINK_STATUS_SOK == status)
                {
                    pObj->queueCount ++;
                }
            }
        }

        if (freeBufList.numBuf)
        {
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId,
                                        &freeBufList);
        }
    }
    else
    {
        /* display is not running, release all frames to previous link */
        if (bufList.numBuf)
        {
            System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                        pInQueParams->prevLinkQueId,
                                        &bufList);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 DisplayMpLink_drvDelete(DisplayMpLink_Obj *pObj)
{
    FVID2_FrameList frameList;
    Int32 status;
    UInt32 pipeId;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Delete in progress !!!\n");
#endif

    for (pipeId = 0u; pipeId < pObj->createArgs.numPipes; pipeId ++)
    {
        do
        {
            /* de-queue queued buffer's */
            status = FVID2_dequeue(pObj->displayHndl[pipeId], &frameList, 0,
                BSP_OSAL_NO_WAIT);
        } while (status == SYSTEM_LINK_STATUS_SOK);

        status = FVID2_delete(pObj->displayHndl[pipeId], NULL);
        if (SYSTEM_LINK_STATUS_SOK != status)
        {
            Vps_printf(" DISPLAY: Delete ERROR !!!\n");
        }
    }

    DisplayMpLink_freeFrames(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_queDelete(&pObj->freeQueue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_queDelete(&pObj->readyQueue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Delete Done !!!\n");
#endif

    return status;
}

Int32 DisplayMpLink_drvStart(DisplayMpLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Start in progress !!!\n");
#endif

    pObj->isDisplayRunning = TRUE;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Start Done !!!\n");
#endif

    return status;
}

Int32 DisplayMpLink_drvStop(DisplayMpLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 pipeId;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Stop in progress !!!\n");
#endif

    for (pipeId = 0u; pipeId < pObj->createArgs.numPipes; pipeId ++)
    {
        status = FVID2_stop(pObj->displayHndl[pipeId], NULL);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pObj->isDisplayRunning = FALSE;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" DISPLAY: Stop Done !!!\n");
#endif

    return status;
}

Int32 DisplayMpLink_drvGetStatistics(const DisplayMpLink_Obj *pObj,
                                   DisplayMpLink_Statistics *pPrm)
{
    UInt16 chNum = pObj->curDisplayChannelNum;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pPrm->elaspedTimeInMsec =
        Utils_getCurGlobalTimeInMsec()
            - linkStatsInfo->linkStats.statsStartTime;

    pPrm->displayIsrCount =
        linkStatsInfo->linkStats.notifyEventCount;

    if(chNum < linkStatsInfo->linkStats.numCh)
    {
        pPrm->inBufRecvCount =
            linkStatsInfo->linkStats.chStats[chNum].inBufRecvCount;

        pPrm->inBufDropCount =
            linkStatsInfo->linkStats.chStats[chNum].inBufDropCount;

        pPrm->inBufDisplayCount =
            linkStatsInfo->linkStats.chStats[chNum].inBufProcessCount;
    }
    else
    {
        pPrm->inBufRecvCount = 0;
        pPrm->inBufDropCount = 0;
        pPrm->inBufDisplayCount = 0;
    }

    if(pPrm->resetStatistics==TRUE)
    {
        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pObj->inQueInfo.numCh,
            0);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */

