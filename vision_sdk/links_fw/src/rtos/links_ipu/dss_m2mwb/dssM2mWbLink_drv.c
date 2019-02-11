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
 * \file dssM2mWbLink_drv.c
 *
 * \brief  This file has the implementation of DSSM2MWB Link
 *
 *   DSSM2MWB Link can be used to do processing on video input frames. These
 *   frames may be from capture or decoded video frames coming over network.
 *
 *   DSSM2MWB can do
 *   - Color space conversion on input frames.
 *   - Color space conversion while outputting the frame to memory.
 *   - Scaling on input frames.
 *   - De-Interlacing, (conversion from field to frames )
 *
 *     The DSSM2MWB link receives the input frames, submitted/queued them into VPS
 *     DSSM2MWB driver along with a set of output frames to which the DSSM2MWB driver
 *     write the de-interlaced/scaled output. once the processing is over
 *     the driver invoke a call back. On call back DSSM2MWB Link reclaim these
 *     frames which are already processed and send back to the previous link.
 *     Also send out the output frames to the next link
 *
 *     DSSM2MWB is validated only for DEI in Bypass mode (Bypass = TRUE).  This
 *     is because no HW set-up available currently to feed interlaced input
 *
 *     DSSM2MWB link also supports the run time input and output resolution
 *     change - This feature is NOT verified in this version.
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "dssM2mWbLink_priv.h"

/*******************************************************************************
 *  Local Functions Defination
 *******************************************************************************
 */
static Fvid2_DataFormat getDisFormat(System_VideoDataFormat inDataFmt);
static Void fvid2DrvCreate(DssM2mWbLink_Obj *pObj);
static Void fvid2DrvDelete(DssM2mWbLink_Obj *pObj);
static Void freeAndDeQueOutBuf(DssM2mWbLink_Obj *pObj);
static Vps_DssDispcWbInNode getDriverWbInNode(DssM2mWbLink_DssDispcWbInNode linkWbInNode);
static Void allocAndQueOutBuf(DssM2mWbLink_Obj *pObj);
static Vps_DssDispcPipes getDriverDispcPipe(DssM2mWbLink_DssDispcPipes linkDispcPipe);

/**
 *******************************************************************************
 *
 * \brief This is the Call back function registered with DSSM2MWB driver
 *
 *        This call back function will be invoked by DSSM2MWB driver once it
 *        processed the frames from a FVID2_frame list
 *
 * \param  handle    [IN] DSSM2MWB driver handle
 * \param  appData   [IN] Set with link instance handle address
 * \param  reserved  [IN] Not used
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 dssM2mWbDrvCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    DssM2mWbLink_Obj *pObj = (DssM2mWbLink_Obj*)appData;

    BspOsal_semPost(pObj->complete);

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    return SYSTEM_LINK_STATUS_SOK;
}

/* Local function definitions */
static Void allocAndQueOutBuf(DssM2mWbLink_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    UInt32 tempBuffAddr = 0;
    System_VideoFrameBuffer *pVidBuf;

    /* Out queue */
    status = Utils_bufCreate(
                    &pObj->bufOutQue,
                    FALSE,                  /* blockOnGet */
                    FALSE);                 /* blockOnPut */
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Pitch and output buffer size calculation */
    if(TRUE == Fvid2_isDataFmtSemiPlanar(pObj->createArgs.outDataFmt))
    {
        /* YUV420SP */
        pObj->outPitch[0U] = VpsUtils_align(
                            pObj->createArgs.outWidth, VPS_BUFFER_ALIGNMENT);
        pObj->outPitch[1U] = pObj->outPitch[0U];

        pObj->outBufSize = (pObj->outPitch[0U] * pObj->createArgs.outHeight) + \
                        (pObj->outPitch[1U] * (pObj->createArgs.outHeight >> 1U));
    }
    else if(TRUE == Fvid2_isDataFmtYuv422I(pObj->createArgs.outDataFmt))
    {
        /* YUV422I */
        pObj->outPitch[0U] = VpsUtils_align(
                            pObj->createArgs.outWidth * 2U, VPS_BUFFER_ALIGNMENT);

        pObj->outBufSize = pObj->outPitch[0U] * pObj->createArgs.outHeight;
    }
    else if(TRUE == Fvid2_isDataFmtRgb16bit(pObj->createArgs.outDataFmt))
    {
        /* RGB 16bit */
        pObj->outPitch[0U] = VpsUtils_align(
                            pObj->createArgs.outWidth * 2U, VPS_BUFFER_ALIGNMENT);

        pObj->outBufSize = pObj->outPitch[0U] * pObj->createArgs.outHeight;
    }
    else if(TRUE == Fvid2_isDataFmtRgb24bit(pObj->createArgs.outDataFmt))
    {
        /* RGB 24bits */
        pObj->outPitch[0U] = VpsUtils_align(
                            pObj->createArgs.outWidth * 3U, VPS_BUFFER_ALIGNMENT);

        pObj->outBufSize = pObj->outPitch[0U] * pObj->createArgs.outHeight;
    }
    else if(TRUE == Fvid2_isDataFmtRgb32bit(pObj->createArgs.outDataFmt))
    {
        /* RGB 32bits */
        pObj->outPitch[0U] = VpsUtils_align(
                            pObj->createArgs.outWidth * 4U, VPS_BUFFER_ALIGNMENT);

        pObj->outBufSize = pObj->outPitch[0U] * pObj->createArgs.outHeight;
    }
    else
    {
        /* Invalid outDataFmt */
        UTILS_assert(FALSE);
    }

    for (cnt = 0;cnt < DSSM2MWB_LINK_NUM_BUFS_PER_CH_DEFAULT;cnt++)
    {
        pVidBuf = &pObj->vidFrame[cnt];
        pObj->sysBuf[cnt].bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pObj->sysBuf[cnt].payload = (Void*)pVidBuf;
        pObj->sysBuf[cnt].payloadSize = sizeof(System_VideoFrameBuffer);
        pVidBuf->flags = \
                System_Video_Frame_Set_Flag_Fid(pVidBuf->flags, SYSTEM_FID_FRAME);

        if((UInt32)FALSE == System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo))
        {
            pVidBuf->bufAddr[0U] = Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObj->outBufSize,
                                        SYSTEM_BUFFER_ALIGNMENT);
            UTILS_assert(NULL != pVidBuf->bufAddr[0U]);
        }
        else
        {
            pVidBuf->bufAddr[0U] = System_allocLinkMemAllocInfo(
                                        &pObj->createArgs.memAllocInfo,
                                        pObj->outBufSize,
                                        SYSTEM_BUFFER_ALIGNMENT);
            UTILS_assert(NULL != pVidBuf->bufAddr[0U]);
        }

        if(TRUE == Fvid2_isDataFmtSemiPlanar(pObj->createArgs.outDataFmt))
        {
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule 11.3
             * Cast between a pointer and an integral type
             * MISRAC_WAIVER:
             * Pointer address is typecasted to int to calculate and to
             * get the offset
             */
            tempBuffAddr = ((UInt32)pVidBuf->bufAddr[0U] + \
                                    (pObj->outPitch[0U] * pObj->createArgs.outHeight));
            pVidBuf->bufAddr[1U] = (Void*)tempBuffAddr;
        }

        /* Put the allocated buffer to the empty queue */
        status = Utils_bufPutEmptyBuffer(&pObj->bufOutQue, &pObj->sysBuf[cnt]);
    }
}

static Void freeAndDeQueOutBuf(DssM2mWbLink_Obj *pObj)
{
    Int32 status;
    UInt32 cnt;
    System_VideoFrameBuffer *pVidBuf;

    for (cnt = 0;cnt < DSSM2MWB_LINK_NUM_BUFS_PER_CH_DEFAULT;cnt++)
    {
        pVidBuf = &pObj->vidFrame[cnt];

        if((UInt32)FALSE == System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo))
        {
            status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pVidBuf->bufAddr[0U],
                        pObj->outBufSize);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

            pVidBuf->bufAddr[0U] = NULL;
            pVidBuf->bufAddr[1U] = NULL;
        }
    }

    Utils_bufDelete(&pObj->bufOutQue);
}

static Vps_DssDispcWbInNode getDriverWbInNode(DssM2mWbLink_DssDispcWbInNode linkWbInNode)
{
    Vps_DssDispcWbInNode drvWbInNode;

    switch(linkWbInNode)
    {
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_VID2:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_VID2;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_VID3:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_VID3;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_GFX:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_GFX;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD1:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_LCD1;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD2:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_LCD2;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD3:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_LCD3;
            break;
        case DSSM2MWBLINK_DISPC_WB_IN_NODE_TV:
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_TV;
            break;
        default:
        /* default case DSSM2MWBLINK_DISPC_WB_IN_NODE_VID1: */
            drvWbInNode = VPS_DSS_DISPC_WB_IN_NODE_VID1;
            break;
    }

    return drvWbInNode;
}

static Vps_DssDispcPipes getDriverDispcPipe(DssM2mWbLink_DssDispcPipes linkDispcPipe)
{
    Vps_DssDispcPipes drvDispcPipe;

    switch(linkDispcPipe)
    {
        case DSSM2MWBLINK_DISPC_PIPE_VID2:
            drvDispcPipe = VPS_DSS_DISPC_PIPE_VID2;
            break;
        case DSSM2MWBLINK_DISPC_PIPE_VID3:
            drvDispcPipe = VPS_DSS_DISPC_PIPE_VID3;
            break;
        case DSSM2MWBLINK_DISPC_PIPE_GFX1:
            drvDispcPipe = VPS_DSS_DISPC_PIPE_GFX1;
            break;
        case DSSM2MWBLINK_DISPC_PIPE_WB:
            drvDispcPipe = VPS_DSS_DISPC_PIPE_WB;
            break;
        default:
        /* default case DSSM2MWBLINK_DISPC_PIPE_VID1: */
            drvDispcPipe = VPS_DSS_DISPC_PIPE_VID1;
            break;
    }

    return drvDispcPipe;
}

static Fvid2_DataFormat getDisFormat(System_VideoDataFormat inDataFmt)
{
    Fvid2_DataFormat disDataFmt;

    if(TRUE == Fvid2_isDataFmtRgb32bit((Fvid2_DataFormat)inDataFmt))
    {
        /* For the 32 bit RGB formats the driver requires the format to be inversed */
        switch(inDataFmt)
        {
            case SYSTEM_DF_ABGR32_8888:
                disDataFmt = FVID2_DF_RGBA32_8888;
                break;
            case SYSTEM_DF_BGRA32_8888:
                disDataFmt = FVID2_DF_ARGB32_8888;
                break;
            case SYSTEM_DF_XRGB32_8888:
                disDataFmt = FVID2_DF_BGRX32_8888;
                break;
            case SYSTEM_DF_BGRX24_8888:
                disDataFmt = FVID2_DF_RGBX24_8888;
                break;
            case SYSTEM_DF_XBGR24_8888:
                disDataFmt = FVID2_DF_RGBX24_8888;
                break;
            default:
            /* default case SYSTEM_DF_ARGB32_8888: */
                disDataFmt = FVID2_DF_BGRA32_8888;
                break;
        }
    }
    else
    {
        disDataFmt = (Fvid2_DataFormat)inDataFmt;
    }

    return disDataFmt;
}

static Void fvid2DrvCreate(DssM2mWbLink_Obj *pObj)
{
    Int32 status;
    UInt32 pipeId;
    DssM2mWbLink_CreateParams *pCreatePrm = &pObj->createArgs;
    Vps_M2mDssParams *dssPrms;
    System_LinkChInfo *pChInfo;
    Fvid2_Format *inFmt,*outFmt;

    pObj->drvHndl = NULL;

    Fvid2CbParams_init(&pObj->drvCbPrm);
    pObj->drvCbPrm.cbFxn = &dssM2mWbDrvCb;
    pObj->drvCbPrm.appData = pObj;

    /* Init create params */
    VpsM2mDssCreateParams_init(&pObj->drvCreatePrm);

    pObj->drvCreatePrm.wbInNode = pObj->drvWbInNode;
    pObj->drvCreatePrm.numInPipeLines = pCreatePrm->numInPipeLines;

    /* Init DSS params */
    dssPrms = &pObj->dssPrms;
    VpsM2mDssParams_init(dssPrms);
    dssPrms->ovlyWidth = pCreatePrm->ovlyWidth;
    dssPrms->ovlyHeight = pCreatePrm->ovlyHeight;

    /* Init DSS out params */
    Fvid2CropConfig_init(&dssPrms->outPipePrms.cropCfg);
    dssPrms->outPipePrms.memType = VPS_VPDMA_MT_NONTILEDMEM;
    dssPrms->outPipePrms.scEnable = FALSE;

    if (VpsDss_isWbInNodeFromOvly(pObj->drvWbInNode))
    {
        if((pCreatePrm->ovlyWidth != pCreatePrm->outWidth) ||
           (pCreatePrm->ovlyHeight != pCreatePrm->outHeight))
        {
            dssPrms->outPipePrms.scEnable = TRUE;
        }
    }
    else
    {
        /* If there is no ovelay then there is only one input hence comparing
            against the first channel width and height */
        if ((pCreatePrm->inTarWidth[0U] != pCreatePrm->outWidth) ||
            (pCreatePrm->inTarHeight[0U] != pCreatePrm->outHeight))
        {
            dssPrms->outPipePrms.scEnable = TRUE;
        }
    }

    dssPrms->outPipePrms.cscFullRngEnable = TRUE;
    dssPrms->outPipePrms.cropEnable = FALSE;
    dssPrms->outPipePrms.advDmaCfg = NULL;

    outFmt = &dssPrms->outPipePrms.outFmt;
    outFmt->dataFormat = getDisFormat(pCreatePrm->outDataFmt);
    outFmt->width = pCreatePrm->outWidth;
    outFmt->height = pCreatePrm->outHeight;
    outFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] = pObj->outPitch[0U];

    if(TRUE == Fvid2_isDataFmtSemiPlanar(pCreatePrm->outDataFmt))
    {
        outFmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] = pObj->outPitch[1U];
    }

    for(pipeId = 0U; pipeId < pCreatePrm->numInPipeLines; pipeId++)
    {
        pChInfo = &pObj->inQueInfo.chInfo[pipeId];

        pObj->drvCreatePrm.inPipeLines[pipeId] = pObj->drvInPipelines[pipeId];
        dssPrms->inPipePrms[pipeId].inPipeId = pObj->drvInPipelines[pipeId];

        inFmt = &dssPrms->inPipePrms[pipeId].inFmt;
        inFmt->width = pChInfo->width;
        inFmt->height = pChInfo->height;
        inFmt->dataFormat = \
        getDisFormat(
        (System_VideoDataFormat)System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags));

        dssPrms->inPipePrms[pipeId].tarWidth = pCreatePrm->inTarWidth[pipeId];
        dssPrms->inPipePrms[pipeId].tarHeight = pCreatePrm->inTarHeight[pipeId];
        dssPrms->inPipePrms[pipeId].posX = pCreatePrm->inPosX[pipeId];
        dssPrms->inPipePrms[pipeId].posY = pCreatePrm->inPosY[pipeId];
        dssPrms->inPipePrms[pipeId].memType = VPS_VPDMA_MT_NONTILEDMEM;

        inFmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX] = pChInfo->pitch[0U];

        if(TRUE == Fvid2_isDataFmtSemiPlanar(inFmt->dataFormat))
        {
            inFmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] = pChInfo->pitch[1U];
        }

        /* Enable/disable scaling based on target size in overlay */
        dssPrms->inPipePrms[pipeId].vidCfg.pipeCfg.scEnable = FALSE;
        if((inFmt->width != pCreatePrm->inTarWidth[pipeId]) ||
           (inFmt->height != pCreatePrm->inTarHeight[pipeId]))
        {
            dssPrms->inPipePrms[pipeId].vidCfg.pipeCfg.scEnable = TRUE;
        }

        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.pipeLine = \
                                                        pObj->drvInPipelines[pipeId];

        /* Each pipe should have different Z-order */
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.zorder = pipeId;
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.zorderEnable = TRUE;
        dssPrms->inPipePrms[pipeId].ovlyPipeCfg.globalAlpha = 0xFFU;

        if (((UInt32)TRUE == VpsDss_isWbInNodeFromOvly(pObj->drvWbInNode)) &&
            (VPS_DSS_DISPC_PIPE_GFX1 == dssPrms->inPipePrms[pipeId].inPipeId))
        {
            /* Use 50% transparency for GRPX pipeline going to overlay */
            dssPrms->inPipePrms[pipeId].ovlyPipeCfg.globalAlpha = 0x7FU;

            /* Enable color keying */
            dssPrms->ovlyCfg.colorKeyEnable = TRUE;
            dssPrms->ovlyCfg.colorKeySel = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
            dssPrms->ovlyCfg.transColorKey = 0x00000000U;
            dssPrms->ovlyCfg.backGroundColor = 0x00000000U;
            dssPrms->ovlyCfg.alphaBlenderEnable = FALSE;
        }
    }

    pObj->drvHndl = Fvid2_create(
                        FVID2_VPS_DSS_M2M_DRV,
                        VPS_M2M_DSS_INST_WB1,
                        &pObj->drvCreatePrm,
                        &pObj->drvCreateStatus,
                        &pObj->drvCbPrm);
    UTILS_assert(NULL != pObj->drvHndl);

    status = Fvid2_control(
                        pObj->drvHndl,
                        IOCTL_VPS_M2M_DSS_SET_PARAMS,
                        dssPrms,
                        NULL);
    UTILS_assert(FVID2_SOK == status);
}

static Void fvid2DrvDelete(DssM2mWbLink_Obj *pObj)
{
    Int32 status;

    status = Fvid2_delete(pObj->drvHndl, NULL);
    UTILS_assert(FVID2_SOK == status);
}

/**
 *******************************************************************************
 *
 * \brief DSSM2MWB link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - create the semaphore required for DSSM2MWB link
 *        - Set the internal data structures
 *        - Create the output object per output queue
 *        - Create the Link channel object per channel
 *        - Create the DSSM2MWB driver instance
 *        - Allocate the DEI context buffers
 *        - Choose the scalar coefficients and configure the driver
 *        - Create the link intermediate request object
 *
 *          DES_ID: DOX_DES_TAG(DES_DssM2mWb_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1319)
 *
 * \param   pObj     [IN] DSSM2MWB Link Instance handle
 * \param   pPrm     [IN] DSSM2MWB link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_drvCreate(
                DssM2mWbLink_Obj *pObj,
                const DssM2mWbLink_CreateParams *pPrm)
{
    Int32 status;
    UInt32 pipeId;

#ifdef SYSTEM_DEBUG_DSSM2MWB
    Vps_printf(" DSSM2MWB: Create in progress !!!\n");
#endif

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(DssM2mWbLink_CreateParams));

    System_resetLinkMemAllocInfo(&pObj->createArgs.memAllocInfo);

    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId, &pObj->inTskInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    UTILS_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    memcpy(&pObj->inQueInfo,
           &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
           sizeof(pObj->inQueInfo));

    pObj->drvWbInNode = getDriverWbInNode(pObj->createArgs.wbInNode);

    for(pipeId = 0U; pipeId < pObj->createArgs.numInPipeLines; pipeId++)
    {
        pObj->drvInPipelines[pipeId] = \
                                getDriverDispcPipe(pObj->createArgs.inPipelines[pipeId]);
    }

    /* Create semaphores */
    pObj->complete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(NULL != pObj->complete);

    /* Allocate and queue output buffers */
    allocAndQueOutBuf(pObj);

    /* Create the FVID2 driver */
    fvid2DrvCreate(pObj);

    System_assertLinkMemAllocOutOfMem(
                        &pObj->createArgs.memAllocInfo,
                        "DSSM2MWB");

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT(
                        "DSSM2MWB",
                        pObj->memUsed,
                        UTILS_ARRAYSIZE(pObj->memUsed));

    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId,"DSSM2MWB");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = FALSE;

    /* info structure used by the next link */
    pObj->info.numQue = 1U;
    pObj->info.queInfo[0U].numCh = 1U;
    pObj->info.queInfo[0U].chInfo[0U].flags = \
        System_Link_Ch_Info_Set_Flag_Buf_Type(pObj->info.queInfo[0U].chInfo[0U].flags,
        SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    pObj->info.queInfo[0U].chInfo[0U].flags = \
        System_Link_Ch_Info_Set_Flag_Data_Format(pObj->info.queInfo[0U].chInfo[0U].flags,
        pObj->createArgs.outDataFmt);
    pObj->info.queInfo[0U].chInfo[0U].flags = \
        System_Link_Ch_Info_Set_Flag_Scan_Format(pObj->info.queInfo[0U].chInfo[0U].flags,
        SYSTEM_SF_PROGRESSIVE);
    pObj->info.queInfo[0U].chInfo[0U].pitch[0U] = pObj->outPitch[0U];
    pObj->info.queInfo[0U].chInfo[0U].pitch[1U] = pObj->outPitch[1U];
    pObj->info.queInfo[0U].chInfo[0U].startX = 0U;
    pObj->info.queInfo[0U].chInfo[0U].startY = 0U;
    pObj->info.queInfo[0U].chInfo[0U].width = pObj->createArgs.outWidth;
    pObj->info.queInfo[0U].chInfo[0U].height = pObj->createArgs.outHeight;

#ifdef SYSTEM_DEBUG_DSSM2MWB
    Vps_printf(" DSSM2MWB: Create Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to Delete the DSSM2MWB link
 *
 *        - Free-up the DEI context buffers
 *        - Delete the DSSM2MWB driver (FVID2_delete)
 *        - Delete the Link "process complete" semaphore
 *        - Remove the output buffer queue
 *        - De-allocate the output video frame memory
 *        - Delete the output buffer empty buffer queue
 *        - Delete the FVID2_frame freeQ
 *        - Delete the Link intermediate channel specific input queue
 *        - Delete the link internal request object queue
 *
 * \param   pObj     [IN] DSSM2MWB Link Instance handle
 *
 * \return  rtnValue [OUT] return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_drvDelete(DssM2mWbLink_Obj *pObj)
{
    Int32 status;

#ifdef SYSTEM_DEBUG_DSSM2MWB
    Vps_printf(" DSSM2MWB: Delete in progress !!!\n");
#endif

    fvid2DrvDelete(pObj);

    BspOsal_semDelete(&pObj->complete);

    freeAndDeQueOutBuf(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

#ifdef SYSTEM_DEBUG_DSSM2MWB
    Vps_printf(" DSSM2MWB: Delete Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function submit the job to the DSSM2MWB driver
 *
 *        VPS driver defines certain input and output frame data structure
 *        and this need to be populated to submit any job to the driver
 *        - Call DssM2mWbLink_drvQueueFramesToChQue to put the input buffers
 *          into the link internal input buffer queue
 *        - Get the input frame list
 *        - Get the output frame List
 *        - Populate VPS driver the process List
 *        - Call the function to create the in/out frame List
 *        - Call IOCTL if useOverridePrevFldBuf == TRUE
 *        - Submit the job to driver by invoking FVID2_processFrames
 *        - Wait for the process/job completion
 *        - Call FVID2_getProcessedFrames once the completion
 *          Repeat above until all input frames are processed
 *
 *          DES_ID: DOX_DES_TAG(DES_DssM2mWb_001)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1319)
 *
 * \param   pObj   [IN]  DSSM2MWB Link Instance handle
 *
 * \param   status [OUT] Return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_drvProcessData(DssM2mWbLink_Obj *pObj)
{
    Int32 status;
    UInt32 bufId, pipeId;
    System_LinkInQueParams *pInQueParams;
    System_BufferList inBufList;
    System_Buffer *pInBuffer, *pOutBuf;
    System_LinkStatistics *linkStatsInfo;
    System_VideoFrameCompositeBuffer *pInCompBuf;
    System_VideoFrameBuffer *pInVidBuf;
    System_VideoFrameBuffer *pOutVidBuf;
    Fvid2_FrameList inDrvFrmList, outDrvFrmList;
    System_LinkChInfo *pChInfo;
    DssM2mWbLink_CreateParams *pCreatePrm = &pObj->createArgs;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstFrameRecv == (Bool)FALSE)
    {
        pObj->isFirstFrameRecv = (Bool)TRUE;

        Utils_resetLinkStatistics(
                        &linkStatsInfo->linkStats,
                        pObj->inQueInfo.numCh,          /* numCh */
                        1U);                            /* numOut */
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams;

    System_getLinksFullBuffers(
                    pInQueParams->prevLinkId,
                    pInQueParams->prevLinkQueId,
                    &inBufList);

    if(inBufList.numBuf)
    {
        linkStatsInfo->linkStats.chStats[0U].inBufRecvCount += inBufList.numBuf;

        if(TRUE == pObj->createArgs.enableOut)
        {
            for(bufId = 0; bufId < inBufList.numBuf; bufId++)
            {
                pInBuffer = inBufList.buffers[bufId];

                if(1U < pCreatePrm->numInPipeLines)
                {
                    /* If the no of input pipelines is more than 1 then composite
                        buffer is expected */
                    UTILS_assert(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == \
                                                                    pInBuffer->bufType);
                }
                else
                {
                    /* If the no of input pipelines is 1 then input buffer can be either
                        composite or video frame */
                    UTILS_assert(
                    (SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pInBuffer->bufType) ||
                    (SYSTEM_BUFFER_TYPE_VIDEO_FRAME == pInBuffer->bufType) ||
                    (SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME == pInBuffer->bufType));
                }

                /* Get free output buffer */
                status = Utils_bufGetEmptyBuffer(
                                    &pObj->bufOutQue,
                                    &pOutBuf,
                                    BSP_OSAL_NO_WAIT);
                if(SYSTEM_LINK_STATUS_SOK != status)
                {
                    /* Free output buffer is not available so break loop */
                    linkStatsInfo->linkStats.chStats[0U].outBufDropCount[0U]++;

                    break;
                }
                else
                {
                    pOutBuf->srcTimestamp = pInBuffer->srcTimestamp;
                    pOutBuf->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pInBuffer->bufType)
                    {
                        pInCompBuf = \
                                (System_VideoFrameCompositeBuffer*)pInBuffer->payload;
                    }
                    else
                    {
                        pInVidBuf = (System_VideoFrameBuffer*)pInBuffer->payload;
                    }

                    pOutVidBuf = (System_VideoFrameBuffer*)pOutBuf->payload;

                    Fvid2FrameList_init(&inDrvFrmList);
                    Fvid2FrameList_init(&outDrvFrmList);

                    inDrvFrmList.numFrames = pObj->createArgs.numInPipeLines;
                    for(pipeId = 0;pipeId < inDrvFrmList.numFrames;pipeId++)
                    {
                        pChInfo = &pObj->inQueInfo.chInfo[pipeId];
                        inDrvFrmList.frames[pipeId] = &pObj->inFrame[pipeId];

                        Fvid2Frame_init(inDrvFrmList.frames[pipeId]);
                        inDrvFrmList.frames[pipeId]->chNum = 0U;
                        inDrvFrmList.frames[pipeId]->fid = FVID2_FID_FRAME;

                        if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pInBuffer->bufType)
                        {
                            inDrvFrmList.frames[pipeId]->addr[0U][0U] = \
                                                        pInCompBuf->bufAddr[0U][pipeId];
                        }
                        else
                        {
                            inDrvFrmList.frames[pipeId]->addr[0U][0U] = \
                                                                pInVidBuf->bufAddr[0U];
                        }

                        if(TRUE == Fvid2_isDataFmtSemiPlanar(
                                System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags)))
                        {
                            if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == \
                                                                    pInBuffer->bufType)
                            {
                                inDrvFrmList.frames[pipeId]->addr[0U][1U] = \
                                                        pInCompBuf->bufAddr[1U][pipeId];
                            }
                            else
                            {
                                inDrvFrmList.frames[pipeId]->addr[0U][1U] = \
                                                                pInVidBuf->bufAddr[1U];
                            }
                        }
                    }

                    outDrvFrmList.numFrames = 1U;
                    outDrvFrmList.frames[0U] = &pObj->outFrame;

                    Fvid2Frame_init(outDrvFrmList.frames[0U]);
                    outDrvFrmList.frames[0U]->chNum = 0U;
                    outDrvFrmList.frames[0U]->fid = FVID2_FID_FRAME;
                    outDrvFrmList.frames[0U]->addr[0U][0U] = pOutVidBuf->bufAddr[0U];
                    if(TRUE == Fvid2_isDataFmtSemiPlanar(pObj->createArgs.outDataFmt))
                    {
                        outDrvFrmList.frames[0U]->addr[0U][1U] = pOutVidBuf->bufAddr[1U];
                    }

                    status = Fvid2_processRequest(
                                            pObj->drvHndl,
                                            &inDrvFrmList,
                                            &outDrvFrmList);
                    UTILS_assert(FVID2_SOK == status);

                    linkStatsInfo->linkStats.chStats[0U].inBufProcessCount++;

                    /* Wait till frames get processed */
                    BspOsal_semWait(pObj->complete, BIOS_WAIT_FOREVER);

                    status = Fvid2_getProcessedRequest(
                                            pObj->drvHndl,
                                            &inDrvFrmList,
                                            &outDrvFrmList,
                                            FVID2_TIMEOUT_NONE);
                    UTILS_assert(status == FVID2_SOK);

                    Utils_updateLatency(
                                    &linkStatsInfo->linkLatency,
                                    pOutBuf->linkLocalTimestamp);
                    Utils_updateLatency(
                                    &linkStatsInfo->srcToLinkLatency,
                                    pOutBuf->srcTimestamp);
                    linkStatsInfo->linkStats.chStats[0U].outBufCount[0U]++;

                    /* Put the full output buffer */
                    status = Utils_bufPutFullBuffer(&pObj->bufOutQue, pOutBuf);
                    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                    /* Notify next link */
                    System_sendLinkCmd(
                                pObj->createArgs.outQueParams.nextLink,
                                SYSTEM_CMD_NEW_DATA,
                                NULL);
                }
            }
        }
        else
        {
            /* Output is not enabled */
            linkStatsInfo->linkStats.chStats[0U].inBufDropCount +=
                                                            inBufList.numBuf;
        }

        System_putLinksEmptyBuffers(
                    pInQueParams->prevLinkId,
                    pInQueParams->prevLinkQueId,
                    &inBufList);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to prints the DSSM2MWB link statistics
 *
 *        Also reset the Link statistics after the print controlled by a flag
 *
 * \param   pObj            [IN] Display Link Instance handle
 * \param   resetAfterPrint [IN] Flag to reset the statistics after print
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_printStatistics(const DssM2mWbLink_Obj *pObj, Bool resetAfterPrint)
{
    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "DSSM2MWB", (Bool)TRUE);

    Utils_printLatency(
                    "DSSM2MWB",
                    &pObj->linkStatsInfo->linkLatency,
                    &pObj->linkStatsInfo->srcToLinkLatency,
                    (Bool)TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to prints the DSSM2MWB link output buffer status
 *
 * \param   pObj            [IN] Display Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_printBufferStatus(DssM2mWbLink_Obj *pObj)
{
    Utils_bufPrintStatus("DSSM2MWB OUT0", &pObj->bufOutQue);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to run time enable/disable a channel
 *
 *        Set run time enable/disable a channel of a specific output queue
 *
 * \param   pObj     [IN] VPE Link Instance handle
 * \param   DssM2mWbLink_ChannelInfo* [IN] VPE channel info parameters
 *
 * \return  status   [OUT] return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_drvSetChannelInfo(DssM2mWbLink_Obj *pObj,
                                const DssM2mWbLink_ChannelInfo *channelInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    pObj->createArgs.enableOut = (Bool)channelInfo->enable;
    return status;
}
