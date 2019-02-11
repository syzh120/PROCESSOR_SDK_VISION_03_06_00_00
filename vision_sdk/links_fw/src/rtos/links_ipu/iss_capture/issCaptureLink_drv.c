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
 * \file issCaptureLink_drv.c
 *
 * \brief  This file communicates with driver for iss capture link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (Apr 2014) : [PS] First version
 * \version 0.1 (Apr 2015) : [SUJ] Updated for multi-channel support
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issCaptureLink_priv.h"

/* ========================================================================== */
/*                          Local Function Prototypes                         */
/* ========================================================================== */
Void IssCaptureLink_drvSetDrvCfg(IssCaptureLink_Obj *pObj);
Int32 IssCaptureLink_drvCreateDrv(IssCaptureLink_Obj *pObj);
Int32 IssCaptureLink_drvDeleteDrv(IssCaptureLink_Obj *pObj);
Int32 IssCaptureLink_drvAllocFrames(IssCaptureLink_Obj *pObj);
Int32 IssCaptureLink_drvFreeFrames(IssCaptureLink_Obj *pObj);
static UInt32 getPitchMultiplier(const IssCaptureLink_OutParams *pOutPrm,
                            System_VideoIfMode ifMode,
                            System_VideoIfWidth ifWidth);
static Int32 issCaptDrvCallback(FVID2_Handle handle, Ptr appData, Ptr reserved);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 IssCaptureLink_drvAllocFrames(IssCaptureLink_Obj *pObj)
{
    Int32 status = FVID2_SOK;
    Fvid2_Frame *fvid2Frame;
    System_Buffer *sysBuffer;
    System_VideoFrameBuffer *videoFrame;
    Fvid2_FrameList frmList;
    UInt32 frameId, strmId, numFramesPerCh;
    Utils_DmaChCreateParams dmaParams;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);

    for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
    {
        pObj->outBufSize = pObj->info.queInfo[0U].chInfo[strmId].pitch[0U] *
                            pObj->createArgs.outParams[strmId].maxHeight;

        if(pObj->createArgs.outParams[strmId].numOutBuf >
                ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE)
        {
            pObj->createArgs.outParams[strmId].numOutBuf =
                ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE;
        }

        frameId = SYSTEM_LINK_MAX_FRAMES_PER_CH * strmId;
        frmList.numFrames = 0U;
        numFramesPerCh = pObj->createArgs.outParams[strmId].numOutBuf;

        for(; frameId <
                (numFramesPerCh + (strmId * SYSTEM_LINK_MAX_FRAMES_PER_CH));
                frameId++)
        {
            if (ISSCAPTURE_LINK_MAX_FRAMES_PER_HANDLE <= frameId)
            {
                /* This should not happen */
                UTILS_assert((Bool) 0U);
            }

            sysBuffer  = &pObj->buffers[frameId];
            videoFrame = &pObj->videoFrames[frameId];
            fvid2Frame = &pObj->fvid2Frames[frameId];

            memset(sysBuffer, 0, sizeof(System_Buffer));
            memset(videoFrame, 0, sizeof(System_VideoFrameBuffer));
            memset(fvid2Frame, 0, sizeof(Fvid2_Frame));

            fvid2Frame->perFrameCfg = NULL;
            fvid2Frame->subFrameInfo = NULL;
            fvid2Frame->appData = sysBuffer;
            fvid2Frame->reserved = NULL;
            fvid2Frame->chNum = Vps_captMakeChNum(pObj->drvInstId, strmId, 0U);

            sysBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
            sysBuffer->chNum       = strmId;
            sysBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
            sysBuffer->payload     = videoFrame;

            if(System_useLinkMemAllocInfo(
                    &pObj->createArgs.memAllocInfo)==FALSE)
            {
                fvid2Frame->addr[0][0] =
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->outBufSize,
                        SYSTEM_BUFFER_ALIGNMENT
                        );
            }
            else
            {
                fvid2Frame->addr[0][0] =
                     System_allocLinkMemAllocInfo(
                            &pObj->createArgs.memAllocInfo,
                            pObj->outBufSize,
                            SYSTEM_BUFFER_ALIGNMENT
                        );
            }
            UTILS_assert(fvid2Frame->addr[0][0]!=NULL);

            /*
             * Link the frame to the system buffer. Note that the Frame's
             * appData already points to the system buffer.
             */
            sysBuffer->pCaptureOrgBufferPtr = fvid2Frame;

            videoFrame->bufAddr[0] = fvid2Frame->addr[0][0];

            frmList.frames[frmList.numFrames] = fvid2Frame;
            frmList.numFrames++;
        }

        status = FVID2_queue(pObj->drvHandle, &frmList, strmId);
        if (FVID2_SOK != status)
        {
            Vps_printf(" ISSCAPTURE: ERROR: FVID2 Queue Stream %d Failed !!!\n"
                        , strmId);
            UTILS_assert((Bool) 0U);
        }
    }

    /* Allocate Extra frame for saving captured frame */
    if (pObj->createArgs.allocBufferForRawDump != 0U)
    {
            if(System_useLinkMemAllocInfo(
                    &pObj->createArgs.memAllocInfo)==FALSE)
            {
                pObj->saveFrameBufAddr =
                    Utils_memAlloc(
                        (Utils_HeapId) UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->outBufSize,
                        SYSTEM_BUFFER_ALIGNMENT);
            }
            else
            {
                pObj->saveFrameBufAddr =
                    System_allocLinkMemAllocInfo(
                        &pObj->createArgs.memAllocInfo,
                        pObj->outBufSize,
                        SYSTEM_BUFFER_ALIGNMENT);
            }
            UTILS_assert(pObj->saveFrameBufAddr != NULL);

        /* Initialize DMA parameters and create object for Frame Dumping */
        Utils_DmaChCreateParams_Init(&dmaParams);
        status = Utils_dmaCreateCh(
                        &pObj->dumpFramesDmaObj,
                        &dmaParams
                        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        pObj->saveFrame = 0xFF;
    }

    return status;
}

Int32 IssCaptureLink_drvFreeFrames(IssCaptureLink_Obj *pObj)
{
    Int32 status = FVID2_SOK;
    Fvid2_Frame *fvid2Frame;
    UInt32 frameId, strmId, numFramesPerCh;

    if (System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo) == FALSE)
    {
        for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
        {
            frameId = SYSTEM_LINK_MAX_FRAMES_PER_CH * strmId;
            numFramesPerCh = pObj->createArgs.outParams[strmId].numOutBuf;

            for(; frameId <
                    (numFramesPerCh + (strmId * SYSTEM_LINK_MAX_FRAMES_PER_CH));
                    frameId++)
            {
                fvid2Frame = &pObj->fvid2Frames[frameId];

                status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            fvid2Frame->addr[0][0],
                            pObj->outBufSize
                            );
                UTILS_assert(status==0);
            }
        }
    }

    /* Free up Extra frame for saving captured frame */
    if (pObj->createArgs.allocBufferForRawDump != 0U)
    {
        /* Initialize this flag to 0 so that it can't be used */
        pObj->saveFrame = 0xFF;

        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
        {
            /* Free up the extra buffer memory space */
            status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->saveFrameBufAddr,
                        pObj->outBufSize
                        );
            UTILS_assert(status==0);
        }
        pObj->saveFrameBufAddr = NULL;

        /* Free up the DMA channel object */
        Utils_dmaDeleteCh(&pObj->dumpFramesDmaObj);
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Process the captured data in response to driver callback.
 *
 * This function gets called in response to driver callback. It dequeues the
 * captured frame from driver, puts it into link output queue and sends message
 * to next link
 *
 * \param  pObj           [IN] Capture link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvProcessData(IssCaptureLink_Obj * pObj)
{
    UInt32 frameId, strmId;
    Fvid2_FrameList frmList, errFrmList;
    FVID2_Frame     *fvid2Frame;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_Buffer *sysBuffer;
    System_LinkStatistics *linkStatsInfo;
    System_VideoFrameStatus frameStatus;
    Bool notifyNextLink;
    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
    {
        status = Fvid2_dequeue(
                    pObj->drvHandle,
                    &frmList,
                    strmId,
                    FVID2_TIMEOUT_NONE);

        if ((0U != frmList.numFrames) && (FVID2_SOK == status))
        {
            notifyNextLink = (Bool)FALSE;
            errFrmList.numFrames = 0U;

            if (pObj->isFirstFrameRecv == FALSE)
            {
                pObj->isFirstFrameRecv = (Bool) TRUE;

                Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pObj->info.queInfo[0].numCh,
                    1U);
            }

            /* Dumping of frame is expected to used for debug, In case there
             *  were errors, ignore them and print them as warning
             */
            if (((TRUE == pObj->createArgs.allocBufferForRawDump) &&
                (TRUE == pObj->saveFrame)) && (pObj->saveChId == strmId))
            {
                Utils_DmaCopyFill2D dmaPrm;

                /* This functionality typically will be used for saving
                   RAW frames, which will be typically be more that 8bpp size,
                   so hard coding dataformat for the DMA to be RAW16 */
                dmaPrm.dataFormat = SYSTEM_DF_RAW16;

                dmaPrm.destAddr[0]  = pObj->saveFrameBufAddr;
                dmaPrm.destPitch[0] = pObj->drvCalCfg.inFmt[0].pitch[0];
                dmaPrm.destStartX   = 0;
                dmaPrm.destStartY   = 0;
                dmaPrm.width        = pObj->createArgs.outParams[0U].width;
                dmaPrm.height       = pObj->createArgs.outParams[0U].height;
                dmaPrm.srcAddr[0]   = frmList.frames[0]->addr[0][0];
                dmaPrm.srcPitch[0]  = pObj->drvCalCfg.inFmt[0].pitch[0];
                dmaPrm.srcStartX    = 0;
                dmaPrm.srcStartY    = 0;

                status = Utils_dmaCopy2D(&pObj->dumpFramesDmaObj, &dmaPrm, 1U);
                UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

                /* Reset the flag */
                pObj->saveFrame = FALSE;

                Vps_printf(" ********************************************* \n");
                Vps_printf(" ####### Save Frame from location 0x%x ####### \n",
                    pObj->saveFrameBufAddr);
                Vps_printf(" saveRaw(0, 0x%x, filename, %d, 32, false); ",
                    pObj->saveFrameBufAddr,
                    (pObj->drvCalCfg.inFmt[0].pitch[0] *
                    pObj->createArgs.outParams[0U].height) / 4U);
                if (FVID2_FRAME_STATUS_COMPLETED != frmList.frames[0]->status)
                {
                    switch (frmList.frames[0]->status)
                    {
                        case FVID2_FRAME_STATUS_CRC_ERROR:
                            Vps_printf(" WARNING : CRC error were detected \n");
                        break;

                        case FVID2_FRAME_STATUS_ECC_CORRECTED:
                            Vps_printf(" WARNING : 1 bit ECC error were "
                                        "detected & corrected \n");
                        break;

                        case FVID2_FRAME_STATUS_OVERFLOW:
                            Vps_printf(" WARNING : CAL internal FIFO overflows"
                                        " were detected \n");
                        break;
                        case FVID2_FRAME_STATUS_ECC_ERROR:
                            Vps_printf(" WARNING : ECC error were detected \n");
                        break;
                        default:
                            /* This should not happen */
                            Vps_printf(" WARNING : Frame Status is invalid \n");
                        break;
                    }
                }
                Vps_printf(" ********************************************* \n");
            }

            for (frameId = 0; frameId < frmList.numFrames; frameId++)
            {
                fvid2Frame = frmList.frames[frameId];
                sysBuffer = fvid2Frame->appData;

                frameStatus = SYSTEM_FRAME_STATUS_COMPLETED;
                if (FVID2_FRAME_STATUS_COMPLETED != fvid2Frame->status)
                {
                    if (NULL != pObj->errCfg.errorCallback)
                    {
                        frameStatus = pObj->errCfg.errorCallback(
                                                    pObj->errCfg.appObj,
                                                    sysBuffer,
                                (System_VideoFrameStatus) fvid2Frame->status);
                    }
                }

                if(SYSTEM_FRAME_STATUS_COMPLETED == frameStatus)
                {
                    notifyNextLink = (Bool)TRUE;
                    /* Update the timestamp at this point when frame is
                     * available from driver
                     */
                    sysBuffer->srcTimestamp = Utils_getCurGlobalTimeInUsec();
                    sysBuffer->frameId      = 0;
                    sysBuffer->linkLocalTimestamp = sysBuffer->srcTimestamp;

                    linkStatsInfo->linkStats.chStats[
                        sysBuffer->chNum].outBufCount[0]++;

                    if(pObj->createArgs.callback != NULL)
                    {
                        pObj->createArgs.callback(
                            pObj->createArgs.appObj,
                            sysBuffer);
                    }

                    status = Utils_bufPutFullBuffer(&pObj->bufQue, sysBuffer);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    errFrmList.frames[errFrmList.numFrames] = fvid2Frame;
                    errFrmList.numFrames++;
                }
            }

            /*
             * Send command to link for putting the buffer in output queue
             *  of the buffer
             */
            if ((Bool)TRUE == notifyNextLink)
            {
                status = System_sendLinkCmd(
                                    pObj->createArgs.outQueParams.nextLink,
                                    SYSTEM_CMD_NEW_DATA,
                                    NULL);
            }
            /* If there were error frames, put it back into drivers Q */
            if (0U != errFrmList.numFrames)
            {
                status = FVID2_queue(pObj->drvHandle, &errFrmList, strmId);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }

        /* No buffer to dequeue, so returning ok here */
        if (FVID2_EAGAIN == status)
        {
            status = FVID2_SOK;
        }
    }

    return status;
}


Void IssCaptureLink_drvSetDrvCfg(IssCaptureLink_Obj *pObj)
{
    Vps_CaptCreateParams        *drvCreatePrms;
    vpsissCalCmplxIoCfg_t       *drvCmplxIoCfg;
    IssCaptureLink_Csi2Params   *csi2Params;
    vpsissCalCfg_t              *drvCalCfg;
    IssCaptureLink_OutParams    *outPrms;
    UInt32 strmId, cmplxIoId, numPixProcUsed;

    drvCreatePrms = &pObj->drvCreatePrms;

    Fvid2CbParams_init(&pObj->drvCbPrms);
    VpsCaptCreateParams_init(drvCreatePrms);
    vpsissCalCfg_t_init(&pObj->drvCalCfg);

    pObj->drvInstId    = VPS_CAPT_INST_ISS_CAL_A;

    pObj->drvCbPrms.cbFxn   = &issCaptDrvCallback;
    pObj->drvCbPrms.appData = pObj;

    drvCreatePrms->videoIfMode     = pObj->createArgs.videoIfMode;
    drvCreatePrms->videoIfWidth    = pObj->createArgs.videoIfWidth;
    drvCreatePrms->bufCaptMode     = pObj->createArgs.bufCaptMode;
    drvCreatePrms->numCh           = 1U;
    /* CAL Treats channels as streams with in CAL */
    drvCreatePrms->numStream       = pObj->createArgs.numCh;
    drvCreatePrms->pAdditionalArgs = &pObj->drvIssCaptureCreatePrms;


    for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
    {
        drvCreatePrms->chNumMap[strmId][0U] =
                Vps_captMakeChNum(pObj->drvInstId, strmId, 0U);
    }

    memset(&pObj->drvIssCaptureCreatePrms, (Int32) 0,
            sizeof(pObj->drvIssCaptureCreatePrms));

    pObj->drvCalCfg.numStream = pObj->createArgs.numCh;

    numPixProcUsed = 0U;

    for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
    {
        drvCalCfg = &pObj->drvCalCfg;
        outPrms   = &pObj->createArgs.outParams[strmId];

        drvCalCfg->streamId[strmId] = strmId;
        drvCalCfg->inFmt[strmId].width  = outPrms->width;
        drvCalCfg->inFmt[strmId].height = outPrms->height;
        drvCalCfg->inFmt[strmId].pitch[0U] =
                                pObj->info.queInfo[0].chInfo[strmId].pitch[0];
        drvCalCfg->inFmt[strmId].bpp = outPrms->outBpp;
        drvCalCfg->inFmt[strmId].dataFormat = 0U;
        drvCalCfg->writeToMem[strmId] = (UInt32)TRUE;
        drvCalCfg->streamType[strmId] = VPS_ISS_CAL_TAG_PIX_DATA;
        drvCalCfg->isPixProcCfgValid[strmId] = (UInt32)FALSE;
        drvCalCfg->isBysOutCfgValid[strmId]  = (UInt32)FALSE;
        drvCalCfg->bysInEnable[strmId]       = (UInt32)FALSE;
        drvCalCfg->isVportCfgValid[strmId]   = (UInt32)FALSE;

        if(SYSTEM_VIFM_SCH_CPI == pObj->createArgs.videoIfMode)
        {
            UTILS_assert(0U == strmId);
            drvCreatePrms->numCh = 1U;

            pObj->drvIssCaptureCreatePrms.subModules[strmId] =
                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID |
                VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID;

            drvCalCfg->bysInEnable[strmId] = (UInt32)TRUE;

            if(pObj->createArgs.videoIfWidth == SYSTEM_VIFW_10BIT)
            {
                drvCalCfg->csi2DataFormat[strmId] = VPS_ISS_CAL_CSI2_RAW10;
            }
            else if(pObj->createArgs.videoIfWidth == SYSTEM_VIFW_12BIT)
            {
                drvCalCfg->csi2DataFormat[strmId] = VPS_ISS_CAL_CSI2_RAW12;
            }
            else if(pObj->createArgs.videoIfWidth == SYSTEM_VIFW_14BIT)
            {
                drvCalCfg->csi2DataFormat[strmId] = VPS_ISS_CAL_CSI2_RAW14;
            }
            else
            {
                drvCalCfg->csi2DataFormat[strmId] = VPS_ISS_CAL_CSI2_RAW12;
            }
        }
        else if(SYSTEM_VIFM_SCH_CSI2 == pObj->createArgs.videoIfMode)
        {
            pObj->drvIssCaptureCreatePrms.subModules[strmId] =
                                VPS_ISS_CAPT_CAL_SUB_CSI2_ID |
                                VPS_ISS_CAPT_CAL_SUB_CPORT_ID |
                                VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID |
                                VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                                VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                                VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                                VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID;

            if (0U == outPrms->phyInstance)
            {
                pObj->drvIssCaptureCreatePrms.subModules[strmId] |=
                                VPS_ISS_CAPT_CAL_SUB_PPI_ID_0;
                drvCalCfg->cmplxIoId[strmId] = 0U;
            }
            else if (1U == outPrms->phyInstance)
            {
                pObj->drvIssCaptureCreatePrms.subModules[strmId] |=
                                VPS_ISS_CAPT_CAL_SUB_PPI_ID_1;
                drvCalCfg->cmplxIoId[strmId] = 1U;
            }
            else
            {
                /* Illelagl PHY instance ID */
                UTILS_assert((Bool) 0U);
            }

            drvCalCfg->csi2DataFormat[strmId] =
                            (vpsissCalCsi2DataFormat) outPrms->inCsi2DataFormat;
        }
        else
        {
            /* Illegal interface */
            UTILS_assert((Bool) 0U);
        }

        drvCalCfg->csi2VirtualChanNo[strmId] = outPrms->inCsi2VirtualChanNum;

        if (SYSTEM_BPP_BITS12_PACKED_MIPI == drvCalCfg->inFmt[strmId].bpp)
        {
            drvCalCfg->isPixProcCfgValid[strmId] = (UInt32)FALSE;

            /* These modules are not required */
            pObj->drvIssCaptureCreatePrms.subModules[strmId] &=
                                    (UInt32)
                                    (~ (VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                                        VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                                        VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                                        VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID));

            drvCalCfg->inFmt[strmId].width =
                (drvCalCfg->inFmt[strmId].width * 3u) / 2u;
        }
        else
        {
            drvCalCfg->isPixProcCfgValid[strmId] = (UInt32)TRUE;
        }
        drvCalCfg->pixProcCfg[strmId].decCodec = VPS_ISS_CAL_DPCM_DEC_BYPASS;
        drvCalCfg->pixProcCfg[strmId].enableDpcmInitContext = (UInt32)FALSE;
        drvCalCfg->pixProcCfg[strmId].encCodec = VPS_ISS_CAL_DPCM_ENC_BYPASS;
        drvCalCfg->pixProcCfg[strmId].pack     = VPS_ISS_CAL_PIX_PACK_B16;

        if (((UInt32) TRUE == drvCalCfg->isPixProcCfgValid[strmId]) &&
            (VPS_ISS_CAL_MAX_PIX_PROC_CONTEXT <= numPixProcUsed))
        {
            drvCalCfg->isPixProcCfgValid[strmId] = FALSE;
            pObj->drvIssCaptureCreatePrms.subModules[strmId] &=
                                    (UInt32)
                                    (~ (VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID |
                                        VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID |
                                        VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID |
                                        VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID));

            Vps_printf(" ISSCAPTURE: Warning: Available pixel processing "
                        "contexts is %d, "
                    "Turning OFF pixel processing contexts for streams %d \n",
                    VPS_ISS_CAL_MAX_PIX_PROC_CONTEXT, strmId);
        }

        switch((System_Csi2DataFormat)(drvCalCfg->csi2DataFormat[strmId]))
        {
            case SYSTEM_CSI2_RAW10:
                drvCalCfg->pixProcCfg[strmId].extract = VPS_ISS_CAL_PIX_EXRCT_B10_MIPI;
                if (((SYSTEM_DF_YUV422I_UYVY == outPrms->outDataFormat) ||
                     ((SYSTEM_DF_YUV422I_YUYV == outPrms->outDataFormat))) ||
                    ((SYSTEM_DF_YUV422I_YVYU == outPrms->outDataFormat) ||
                     ((SYSTEM_DF_YUV422I_VYUY == outPrms->outDataFormat))))
                {
                    drvCalCfg->pixProcCfg[strmId].extract =
                                                    VPS_ISS_CAL_PIX_EXRCT_B8;
                    drvCalCfg->pixProcCfg[strmId].pack =
                                                    VPS_ISS_CAL_PIX_PACK_B8;
                }
                break;
            case SYSTEM_CSI2_RAW12:
                drvCalCfg->pixProcCfg[strmId].extract = VPS_ISS_CAL_PIX_EXRCT_B12_MIPI;
                break;
            case SYSTEM_CSI2_RAW14:
                drvCalCfg->pixProcCfg[strmId].extract = VPS_ISS_CAL_PIX_EXRCT_B14_MIPI;
                break;
           case SYSTEM_CSI2_RAW8:
                drvCalCfg->pixProcCfg[strmId].extract = VPS_ISS_CAL_PIX_EXRCT_B8;
                drvCalCfg->pixProcCfg[strmId].pack = VPS_ISS_CAL_PIX_PACK_B8;
                break;
           case SYSTEM_CSI2_YUV422_8B:
                drvCalCfg->pixProcCfg[strmId].extract = VPS_ISS_CAL_PIX_EXRCT_B16_LE;
                drvCalCfg->pixProcCfg[strmId].pack = VPS_ISS_CAL_PIX_PACK_B16;
                break;

            default:
                UTILS_assert((Bool) 0U);
                break;
        }
        if ((Bool)TRUE == drvCalCfg->isPixProcCfgValid[strmId])
        {
            numPixProcUsed++;
        }
    }

    for (cmplxIoId = 0U; cmplxIoId < VPS_ISS_CAL_MAX_CMPLXIO_INST; cmplxIoId ++)
    {
        csi2Params = &pObj->createArgs.csi2Params[cmplxIoId];
        drvCmplxIoCfg = &pObj->drvIssCaptureCreatePrms.cmplxIoCfg[cmplxIoId];

        pObj->drvIssCaptureCreatePrms.isCmplxIoCfgValid[cmplxIoId] =
                                                csi2Params->isCmplxIoCfgValid;

        pObj->drvIssCaptureCreatePrms.csi2PhyClock[cmplxIoId] =
                                                csi2Params->csi2PhyClk;

        if ((UInt32)TRUE == csi2Params->isCmplxIoCfgValid)
        {
            drvCmplxIoCfg->enable             = (UInt32)TRUE;
            drvCmplxIoCfg->pwrAuto            = (UInt32)TRUE;
            drvCmplxIoCfg->clockLane.pol      =
                                    csi2Params->cmplxIoCfg.clockLane.pol;
            drvCmplxIoCfg->clockLane.position =
                                    csi2Params->cmplxIoCfg.clockLane.position;
            drvCmplxIoCfg->data1Lane.pol      =
                                    csi2Params->cmplxIoCfg.data1Lane.pol;
            drvCmplxIoCfg->data1Lane.position =
                                    csi2Params->cmplxIoCfg.data1Lane.position;
            drvCmplxIoCfg->data2Lane.pol      =
                                    csi2Params->cmplxIoCfg.data2Lane.pol;
            drvCmplxIoCfg->data2Lane.position =
                                    csi2Params->cmplxIoCfg.data2Lane.position;
            drvCmplxIoCfg->data3Lane.pol      =
                                    csi2Params->cmplxIoCfg.data3Lane.pol;
            drvCmplxIoCfg->data3Lane.position =
                                    csi2Params->cmplxIoCfg.data3Lane.position;
            drvCmplxIoCfg->data4Lane.pol      =
                                    csi2Params->cmplxIoCfg.data4Lane.pol;
            drvCmplxIoCfg->data4Lane.position =
                                    csi2Params->cmplxIoCfg.data4Lane.position;
        }
        else
        {
            drvCmplxIoCfg->enable             = (UInt32)FALSE;
            drvCmplxIoCfg->pwrAuto            = (UInt32)FALSE;
        }
    }
}

Int32 IssCaptureLink_drvCreateDrv(IssCaptureLink_Obj *pObj)
{
    Int32 status = FVID2_SOK;

    pObj->drvHandle = Fvid2_create(
        FVID2_VPS_CAPT_VID_DRV,
        pObj->drvInstId,
        &pObj->drvCreatePrms,
        &pObj->drvCreateStatus,
        &pObj->drvCbPrms);

    if ((NULL == pObj->drvHandle) ||
        (pObj->drvCreateStatus.retVal != FVID2_SOK))
    {
        Vps_printf(" ISSCAPTURE: ERROR: FVID2 Create Failed !!!\n");
        status = pObj->drvCreateStatus.retVal;
    }

    if(status==FVID2_SOK)
    {
        status = Fvid2_control(pObj->drvHandle,
                                IOCTL_VPS_CAPT_SET_ISS_PARAMS,
                                &pObj->drvCalCfg, NULL);
        if (FVID2_SOK != status)
        {
            Vps_printf(
              " ISSCAPTURE: ERROR: IOCTL_VPS_CAPT_SET_ISS_PARAMS Failed !!!\n");
        }
    }

    return (status);
}

Int32 IssCaptureLink_drvDeleteDrv(IssCaptureLink_Obj *pObj)
{
    Int32   status = FVID2_SOK;
    UInt32  strmId;
    Fvid2_FrameList frmList;

    /* Dequeue all the request from the driver */
    for (strmId = 0U; strmId < pObj->createArgs.numCh; strmId++)
    {
        do
        {
            status = Fvid2_dequeue(
                pObj->drvHandle,
                &frmList,
                strmId,
                FVID2_TIMEOUT_NONE);
        } while (FVID2_SOK == status);
    }

    status = Fvid2_delete(pObj->drvHandle, NULL);
    if (FVID2_SOK != status)
    {
        Vps_printf(" ISSCAPTURE: ERROR: FVID2 Delete Failed !!!\n");
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Create API for link.
 *
 *      Creates & configures the driver, allocates required memory to store the
 *      received frames and other infrasture required by capture link.
 *
 * \param  pObj     [IN] Capture link global handle
 * \param  pPrm     [IN] Capture link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvCreate(IssCaptureLink_Obj          *pObj,
                               const IssCaptureLink_CreateParams *pPrm)
{
    Int32 status;
    System_LinkChInfo *pQueChInfo;
    UInt32 chIdx, pitchMul;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Create in progress !!!\n");
#endif

    UTILS_assert(NULL != pPrm);
    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof (IssCaptureLink_CreateParams));

    System_resetLinkMemAllocInfo(&pObj->createArgs.memAllocInfo);

    status = Utils_bufCreate(&pObj->bufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(ISSCAPT_LINK_MAX_CH >= pPrm->numCh);
    pObj->info.numQue = ISSCAPTURE_LINK_MAX_OUT_QUE;
    pObj->info.queInfo[0U].numCh = pPrm->numCh;

    for (chIdx = 0U; chIdx < pPrm->numCh; chIdx++)
    {
        pitchMul = getPitchMultiplier(&pPrm->outParams[chIdx],
                                        pObj->createArgs.videoIfMode,
                                        pObj->createArgs.videoIfWidth);

        pQueChInfo = &pObj->info.queInfo[0U].chInfo[chIdx];
        pQueChInfo->width       = pPrm->outParams[chIdx].width;
        pQueChInfo->height      = pPrm->outParams[chIdx].height;
        pQueChInfo->startX      = 0;
        pQueChInfo->startY      = 0;
        pQueChInfo->pitch[0]    =
            SystemUtils_align(pObj->createArgs.outParams[chIdx].maxWidth *
                                    pitchMul, ISSCAPTURE_LINK_BUF_ALIGNMENT);
        pQueChInfo->pitch[1]    = 0;
        pQueChInfo->pitch[2]    = 0;
        pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pQueChInfo->flags,
                    pObj->createArgs.outParams[chIdx].dataFormat);
        pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pQueChInfo->flags,
                SYSTEM_SF_PROGRESSIVE);
        /* Using complex IO cont flag instead of PHY/PPI, as CAL would require
            an instance of complex io for an instance of PHY */
        UTILS_assert(VPS_ISS_CAL_MAX_CMPLXIO_INST >
                            pObj->createArgs.outParams[chIdx].phyInstance);
    }

    IssCaptureLink_drvSetDrvCfg(pObj);
    IssCaptureLink_drvCreateDrv(pObj);
    IssCaptureLink_drvAllocFrames(pObj);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "ISSCAPTURE");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool) FALSE;

    System_assertLinkMemAllocOutOfMem(
        &pObj->createArgs.memAllocInfo,
        "ISSCAPTURE"
        );

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("ISSCAPTURE:",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));
#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Create Done !!!\n");
#endif
    pObj->info.queInfo[0U].numCh = pPrm->numCh;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Link callback for putting empty buffers into link input queue
 *
 *
 * \param  pObj           [IN] Capture link global handle
 * \param  pBufList       [IN] List of buffers to be kept back into link queue
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvPutEmptyBuffers(IssCaptureLink_Obj *pObj,
                                        const System_BufferList  *pBufList)
{
    UInt32 idx;
    FVID2_FrameList frameList;
    FVID2_Frame *pFrame;
    System_Buffer *pBuf;
    Int32 status= SYSTEM_LINK_STATUS_SOK;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    linkStatsInfo->linkStats.putEmptyBufCount++;

    if (pBufList->numBuf != 0U)
    {
        /*
         * Iterate through list of buffers provided from previous link.
         * Get FVID2_Frame out of bufferlist. Queue empty frames to the
         * driver queue for capturing new data
         */
        for (idx = 0; idx < pBufList->numBuf; idx++)
        {
            pBuf   = pBufList->buffers[idx];
            UTILS_assert(pBuf != NULL);

            pFrame = pBuf->pCaptureOrgBufferPtr;

            UTILS_assert(pFrame != NULL);

            frameList.frames[0] = pFrame;
            frameList.numFrames  = 1;

            linkStatsInfo->linkStats.chStats[
                pBuf->chNum].inBufRecvCount++;
            linkStatsInfo->linkStats.chStats[
                pBuf->chNum].inBufProcessCount++;

            status = FVID2_queue(pObj->drvHandle,
                                &frameList, pBuf->chNum);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to start the link.
 *
 * This function calls the driver function to start the driver. As a part of
 * this call iss capture hardware is ready to receive frames.
 *
 * \param  pObj           [IN] Iss Capture link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvStart(IssCaptureLink_Obj *pObj)
{
    Int32         status;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Start in progress !!!\n");
#endif

    status = Fvid2_start(pObj->drvHandle, NULL);
    if (FVID2_SOK != status)
    {
        Vps_printf(" ISSCAPTURE: ERROR: FVID2 Start Failed !!!\n");
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        pObj->statsStartTime = Utils_getCurGlobalTimeInMsec();

#ifdef SYSTEM_DEBUG_CAPTURE
        Vps_printf(" ISSCAPTURE: Start Done !!!\n");
#endif
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to stop driver and link.
 *
 * Iss capture hardware stops receiving frames after this call.
 *
 * \param  pObj         [IN] ISS Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvStop(IssCaptureLink_Obj *pObj)
{
    Int32         status;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Stop in progress !!!\n");
#endif

    status = Fvid2_stop(pObj->drvHandle, NULL);
    if (FVID2_SOK != status)
    {
        Vps_printf(" ISSCAPTURE: ERROR: FVID2 Stop Failed !!!\n");
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
#ifdef SYSTEM_DEBUG_CAPTURE
        Vps_printf(" ISSCAPTURE: Stop Done !!!\n");
#endif
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete iss capture link and driver handle.
 *
 *
 * \param  pObj         [IN] Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvDelete(IssCaptureLink_Obj *pObj)
{
    Int32         status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status==0);

    IssCaptureLink_drvDeleteDrv(pObj);
    IssCaptureLink_drvFreeFrames(pObj);

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" ISSCAPTURE: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvPrintStatus(const IssCaptureLink_Obj *pObj)
{
    UTILS_assert(NULL != pObj->linkStatsInfo);
    Utils_printLinkStatistics(
        &pObj->linkStatsInfo->linkStats, "ISSCAPTURE", (Bool) TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Print iss capture link buffer statistics
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvPrintBufferStatus(IssCaptureLink_Obj *pObj)
{
    char str[32];

    snprintf((char *) str, 32U, "ISSCAPTURE");
    Utils_bufPrintStatus((UInt8 *) str, &pObj->bufQue);
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function save a raw frame into a fixed location
 *
 * \param   pObj     [IN] Capture Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */

Int32 IssCaptureLink_drvSaveFrame(IssCaptureLink_Obj *pObj, UInt32 *chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    if (pObj->createArgs.allocBufferForRawDump != 0U)
    {
        pObj->saveFrame = TRUE;
        pObj->saveChId = *chId;
        status = SYSTEM_LINK_STATUS_SOK;
    }
    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function returns information about the saved raw frame
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_drvGetSaveFrameStatus(const IssCaptureLink_Obj *pObj,
                    IssCaptureLink_GetSaveFrameStatus *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pPrm->isSaveFrameComplete = FALSE;
    pPrm->bufAddr = 0;
    pPrm->bufSize = 0;

    if (pObj->createArgs.allocBufferForRawDump != 0U)
    {
        if(pObj->saveFrame == FALSE)
        {
            pPrm->isSaveFrameComplete = TRUE;
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule 11.3
             * Cast between a pointer and an integral type
             * KW State: Defer -> Waiver -> Case by case
             * MISRAC_WAIVER:  The pointer addresses are stored in the form of
             * UInt32. The pointer address is checked after it is allocated so
             * it contains only valid address from the heap.
             */
            pPrm->bufAddr = (UInt32)pObj->saveFrameBufAddr;
            pPrm->bufSize = pObj->drvCalCfg.inFmt[0].pitch[0] *
                            pObj->createArgs.outParams[0U].height;

        }

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

/**
 *******************************************************************************
 * \brief This function applies the application supplied error handling
 *          configurations.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success, appropriate error code otherwise
 *******************************************************************************
 */
Int32 IssCaptureLink_cfgErrorHandling(IssCaptureLink_Obj * pObj,
    const IssCaptureLink_SetErrorNotification *pErrCfg)
{
    Bool enableCrcChk, enableEccCorrectChk;
    UInt32 strmId, phy1En, phy2En;
    vpsissCalErrorCfg_t *pDrvErrCfg = NULL;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    /* POLICY :
            We do not enable driver to notify us on error in intraframe
            boundary. We rely on the frame status to determine if an error was
            encountered.
            Similarly the application will be notified at the frame boundary and
            not at intraframe boundary. */

    if ((NULL == pObj) || (NULL == pErrCfg))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    if ((SYSTEM_LINK_STATUS_SOK == status) && (0 == pErrCfg->errorsToDetect))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        pDrvErrCfg = &pObj->drvErrCfg;
        pDrvErrCfg->numErrorsToMonitor = 0U;
        enableCrcChk = (Bool)FALSE;
        enableEccCorrectChk = (Bool)FALSE;
        /* For each virtual channel enabled, map CRC mismatch and ECC corrected
            to appropriate virtual channel error */
        if (ISSCAPTURE_LINK_ENABLE_ERROR_CRC_MISMATCH ==
          (pErrCfg->errorsToDetect & ISSCAPTURE_LINK_ENABLE_ERROR_CRC_MISMATCH))
        {
            enableCrcChk = (Bool)TRUE;
        }
        if (ISSCAPTURE_LINK_ENABLE_ERROR_ECC_CORRECTED ==
         (pErrCfg->errorsToDetect & ISSCAPTURE_LINK_ENABLE_ERROR_ECC_CORRECTED))
        {
            enableEccCorrectChk = (Bool)TRUE;
        }

        phy1En = 0U;
        phy2En = 0U;
        for (strmId = 0U; ((strmId < pObj->createArgs.numCh) &&
                           (SYSTEM_LINK_STATUS_SOK == status)); strmId++)
        {
            switch (pObj->drvCalCfg.csi2VirtualChanNo[strmId])
            {
                case 0U:
                    if ((Bool)TRUE == enableCrcChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                    if ((Bool)TRUE == enableEccCorrectChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                break;
                case 1U:
                    if ((Bool)TRUE == enableCrcChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC2;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                    if ((Bool)TRUE == enableEccCorrectChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC2;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                break;
                case 2U:
                    if ((Bool)TRUE == enableCrcChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC3;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                    if ((Bool)TRUE == enableEccCorrectChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC3;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                break;
                case 3U:
                    if ((Bool)TRUE == enableCrcChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC4;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                    if ((Bool)TRUE == enableEccCorrectChk)
                    {
                        pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                            VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC4;
                        pDrvErrCfg->numErrorsToMonitor++;
                    }
                break;
                default:
                    /* This should not occur at all !!! */
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                break;
            }
            if (VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 ==
                (pObj->drvIssCaptureCreatePrms.subModules[strmId] &
                 VPS_ISS_CAPT_CAL_SUB_PPI_ID_0))
            {
                phy1En = 1U;
            }
            if (VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 ==
                (pObj->drvIssCaptureCreatePrms.subModules[strmId] &
                 VPS_ISS_CAPT_CAL_SUB_PPI_ID_0))
            {
                phy2En = 1U;
            }
        }
        if (ISSCAPTURE_LINK_ENABLE_ERROR_FIFO_OVERFLOW ==
                                    (pErrCfg->errorsToDetect &
                                    ISSCAPTURE_LINK_ENABLE_ERROR_FIFO_OVERFLOW))
        {
            pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                VPS_CAL_CSI2_PPI_CMPLXIO_FIFO_OVR;
            pDrvErrCfg->numErrorsToMonitor++;
        }
        if (ISSCAPTURE_LINK_ENABLE_ERROR_ECC_NO_CORRECTION ==
                                (pErrCfg->errorsToDetect &
                                ISSCAPTURE_LINK_ENABLE_ERROR_ECC_NO_CORRECTION))
        {
            pDrvErrCfg->errSrc[pDrvErrCfg->numErrorsToMonitor] =
                VPS_CAL_CSI2_PPI_CMPLXIO_ECC_NO_CORRECTION;
            pDrvErrCfg->numErrorsToMonitor++;
        }
    }

    if ((SYSTEM_LINK_STATUS_SOK == status) && (0U != phy1En))
    {
        pDrvErrCfg = &pObj->drvErrCfg;
        if (VPS_ISS_CAL_MAX_ERROR_INTERRUPTS > pDrvErrCfg->numErrorsToMonitor)
        {
            pDrvErrCfg->cmplxIoId = 0U;
            pDrvErrCfg->appCb = NULL;
            pDrvErrCfg->pAppCbArgs = NULL;
            status = Fvid2_control(pObj->drvHandle,
                                    IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS,
                                    pDrvErrCfg, NULL);
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
    }
    if ((SYSTEM_LINK_STATUS_SOK == status) && (0U != phy2En))
    {
        pDrvErrCfg->cmplxIoId = 1U;
        if (VPS_ISS_CAL_MAX_ERROR_INTERRUPTS > pDrvErrCfg->numErrorsToMonitor)
        {
            pDrvErrCfg->appCb = NULL;
            pDrvErrCfg->pAppCbArgs = NULL;
            status = Fvid2_control(pObj->drvHandle,
                                    IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS,
                                    pDrvErrCfg, NULL);
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
    }
    /* Check if second PHY is enabled, if so, enable error CB */
    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        memcpy(&pObj->errCfg, pErrCfg,
                            sizeof(IssCaptureLink_SetErrorNotification));
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief This function determines the required pitch.
 *          Does not support all data types and multiple planes.
 *
 * \return  A Positive non-zero number
 *******************************************************************************
 */
static UInt32 getPitchMultiplier(const IssCaptureLink_OutParams *pOutPrm,
                                    System_VideoIfMode ifMode,
                                    System_VideoIfWidth ifWidth)
{
    UInt32 mulVal = 1U;

    UTILS_assert(NULL != pOutPrm);

    if (SYSTEM_VIFM_SCH_CPI == ifMode)
    {
        if (SYSTEM_VIFW_8BIT < ifWidth)
        {
            /* Requires 2 bytes per pixel */
            mulVal++;

            /* ISS dosent support more than 16b Parallel interface */
            if (SYSTEM_VIFW_16BIT < ifWidth)
            {
                mulVal++;
            }
        }
    }
    else if (SYSTEM_VIFM_SCH_CSI2 == ifMode)
    {
        switch (pOutPrm->inCsi2DataFormat)
        {
            case SYSTEM_CSI2_RAW12:
            case SYSTEM_CSI2_RAW10:
            case SYSTEM_CSI2_RAW14:
                mulVal = 2U;
            break;

            case SYSTEM_CSI2_RAW6:
            case SYSTEM_CSI2_RAW7:
            case SYSTEM_CSI2_RAW8:
                mulVal = 1U;
            break;

            case SYSTEM_CSI2_YUV422_8B:
            case SYSTEM_CSI2_RGB444:
            case SYSTEM_CSI2_RGB555:
            case SYSTEM_CSI2_RGB565:
                mulVal = 2U;
            break;

            case SYSTEM_CSI2_RGB666:
            case SYSTEM_CSI2_RGB888:
            case SYSTEM_CSI2_ANY:
                mulVal = 3U;
            break;

            default :
                /* Illegal data type */
                UTILS_assert((Bool) 0U);
            break;
        }
    }
    else
    {
        /* Interface not supported by ISS. */
        UTILS_assert((Bool) 0U);
    }

    return (mulVal);
}

/**
 *******************************************************************************
 *
 * \brief Callback function from driver to application
 *
 * Callback function gets called from Driver to application on reception of
 * a frame
 *
 * \param  handle       [IN] Driver handle for which callback has come.
 * \param  appData      [IN] Application specific data which is registered
 *                           during the callback registration.
 * \param  reserved     [IN] Reserved.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 issCaptDrvCallback(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    IssCaptureLink_Obj *pObj = (IssCaptureLink_Obj*)appData;

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    Utils_tskSendCmd(&pObj->tsk, SYSTEM_CMD_NEW_DATA, NULL);

    return SYSTEM_LINK_STATUS_SOK;
}
