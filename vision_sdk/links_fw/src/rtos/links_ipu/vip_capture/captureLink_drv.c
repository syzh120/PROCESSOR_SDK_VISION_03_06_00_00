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
 * \file captureLink_drv.c
 *
 * \brief  This file communicates with driver for capture link.
 *
 *         This file calls the driver commands and APIs for the application
 *         commands and APIs. All application commands and APIs finally gets
 *         translated to driver APIs and commands by this file.
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 * \version 0.2 (Jul 2014) : [VT] Add subframe support
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "captureLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
static Int32 CaptureLink_InitSystemBuffer(const CaptureLink_Obj * pObj, const FVID2_FrameList *pFrameList,
                                          System_Buffer   *buffers,
                                          System_VideoFrameBuffer *videoFrames);

Int32 CaptureLink_drvCreateInst(CaptureLink_Obj * pObj, UInt16 instId);

Int32 CaptureLink_drvFlush(FVID2_Handle captureVipHandle, char *portName);

/**
 *******************************************************************************
 * \brief VIP PortID to Port Name mapping.
 *******************************************************************************
 */
char *gCaptureLink_portName[] = {
    "VIP1 Slice0 PortA", "VIP1 Slice0 PortB",
    "VIP1 Slice1 PortA", "VIP1 Slice1 PortB",
    "VIP2 Slice0 PortA", "VIP2 Slice0 PortB",
    "VIP2 Slice1 PortA", "VIP2 Slice1 PortB",
    "VIP3 Slice0 PortA", "VIP3 Slice0 PortB",
    "VIP3 Slice1 PortA", "VIP3 Slice1 PortB",
};

/**
 *******************************************************************************
 * \brief VIP interface width to name mapping.
 *******************************************************************************
 */
char *gCaptureLink_ifName[] = {
    " 8-bit", "10-bit", "12-bit", "14-bit", "16-bit", "18-bit", "20-bit",
    "24-bit", "30-bit","Invalid width",
};

/**
 *******************************************************************************
 *
 * \brief Callback function from driver to application
 *
 * Callback function gets called from Driver to application on every Vsync
 * interrupt.
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
Int32 CaptureLink_drvCallback(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    CaptureLink_InstObj *pInst = (CaptureLink_InstObj *)appData;
    CaptureLink_Obj *pObj = pInst->parent;

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    Utils_tskSendCmd(&pObj->tsk, (UInt32)SYSTEM_CMD_NEW_DATA, (Void *)pInst->instId);
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Passing pointer arguments to functions which
     * takes arguments as UInt32 for legacy reasons and viceversa
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function creates the driver instance
 *
 * Copy/map all the link parameters to driver parameters. Call the appropriate
 * driver IOCTls and FVID2_create for driver
 *
 * \param  pObj     [IN] Global link object
 * \param  instId   [IN] Instance ID of the capture driver to be created.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvCreateInst(CaptureLink_Obj * pObj, UInt16 instId)
{

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InstObj *pInst;
    Vps_CaptCreateParams *pVipCreateArgs;
    Vps_CaptVipParams *pVipPrms;
    Vps_CaptVipScParams *pScParams;
    Vps_CaptVipOutInfo *pVipOutPrm;
    Vps_VipPortConfig *pVipPortCfg;
    CaptureLink_OutParams *pOutPrm;
    System_LinkChInfo *pQueChInfo;
    UInt16 queId, queChId, outId;
    Int32 status;
    Int32 nRetVal = 0;
    Fvid2_DataFormat dataFormat;

    pInstPrm = &pObj->createArgs.vipInst[instId];
    pInst = &pObj->instObj[instId];
    pVipCreateArgs = &pInst->createArgs;

    /*
     * Map link parameters to driver create parameters
     */
    VpsCaptCreateParams_init(&pInst->createArgs);
    pVipCreateArgs->videoIfMode  = pInstPrm->videoIfMode;
    pVipCreateArgs->videoIfWidth = pInstPrm->videoIfWidth;
    pVipCreateArgs->bufCaptMode  = pInstPrm->bufCaptMode;
    pVipCreateArgs->numCh        = 1;
    pVipCreateArgs->numStream    = pInstPrm->numStream;

    /*
     * Map link parameters to VIP hardware parameters
     */
    pVipPrms = &pInst->vipPrms;
    VpsCaptVipParams_init(pVipPrms);
    pVipPrms->inFmt.width          = pInstPrm->inParams.width;
    pVipPrms->inFmt.height         = pInstPrm->inParams.height;
    pVipPrms->inFmt.dataFormat     = pInstPrm->inParams.dataFormat;
    pVipPrms->inFmt.scanFormat     = pInstPrm->inParams.scanFormat;

    /* For the input bayer data format, configure VIP in RAW16 bit mode */
    if (TRUE == Fvid2_isDataFmtBayer(pVipPrms->inFmt.dataFormat))
    {
        pVipPrms->inFmt.dataFormat = FVID2_DF_RAW16;
    }

    /*
     * Map link parameters to scalar hardware parameters
     */
    pVipPrms->scPrms = &pInst->scPrms;
    pScParams = pVipPrms->scPrms;
    VpsCaptVipScParams_init(pScParams);
    pScParams->inCropCfg.cropStartX     = pInstPrm->scPrms.inCropCfg.cropStartX;
    pScParams->inCropCfg.cropStartY     = pInstPrm->scPrms.inCropCfg.cropStartY;
    pScParams->inCropCfg.cropWidth      = pInstPrm->scPrms.inCropCfg.cropWidth;
    pScParams->inCropCfg.cropHeight     = pInstPrm->scPrms.inCropCfg.cropHeight;
    pScParams->scCfg.bypass             = pInstPrm->scPrms.scCfg.bypass;
    pScParams->scCfg.nonLinear          = pInstPrm->scPrms.scCfg.nonLinear;
    pScParams->scCfg.stripSize          = pInstPrm->scPrms.scCfg.stripSize;
    pScParams->scCfg.enableEdgeDetect   = TRUE;
    pScParams->scCfg.enablePeaking      = TRUE;
    pScParams->scCfg.advCfg             = NULL;
    if (TRUE == pInstPrm->scPrms.userCoeff)
    {
        System_ScCoeffParams scCoeff;
        scCoeff = pInstPrm->scPrms.scCoeffCfg;
        pScParams->scCoeffCfg->hScalingSet = scCoeff.hScalingSet;
        pScParams->scCoeffCfg->vScalingSet = scCoeff.vScalingSet;
    }
    else
    {
        pScParams->scCoeffCfg           = NULL;
    }
    pScParams->enableCoeffLoad      = FALSE;

    /*
     * Map link parameters to VIP port hardware parameters
     */
    pVipPrms->vipPortCfg = &pInst->vipPortCfg;
    pVipPortCfg = pVipPrms->vipPortCfg;
    VpsVipPortConfig_init(pVipPortCfg);
    pVipPortCfg->syncType           = pInstPrm->vipPortCfg.syncType;
    pVipPortCfg->actCropEnable      = pInstPrm->vipPortCfg.actCropEnable;
    pVipPortCfg->ancCropEnable      = pInstPrm->vipPortCfg.ancCropEnable;

    pVipPortCfg->intfCfg.clipActive = pInstPrm->vipPortCfg.intfCfg.clipActive;
    pVipPortCfg->intfCfg.clipBlank = pInstPrm->vipPortCfg.intfCfg.clipBlank;
    pVipPortCfg->intfCfg.intfWidth = pInstPrm->vipPortCfg.intfCfg.intfWidth;

    pVipPortCfg->embCfg.errCorrEnable   = TRUE;
    /*
     * Driver is defining as UInt32 and value of
     * VPS_VIP_SRC_NUM_POS_DONT_CARE is -1, typecasting to remove warning.
     */
    pVipPortCfg->embCfg.srcNumPos       = (UInt32)VPS_VIP_SRC_NUM_POS_DONT_CARE;
    pVipPortCfg->embCfg.reserved        = 0;


    pVipPortCfg->disCfg.fidSkewPostCnt =
        pInstPrm->vipPortCfg.disCfg.fidSkewPostCnt;
    pVipPortCfg->disCfg.fidSkewPreCnt =
        pInstPrm->vipPortCfg.disCfg.fidSkewPreCnt;
    pVipPortCfg->disCfg.lineCaptureStyle =
        pInstPrm->vipPortCfg.disCfg.lineCaptureStyle;
    pVipPortCfg->disCfg.fidDetectMode =
        pInstPrm->vipPortCfg.disCfg.fidDetectMode;
    pVipPortCfg->disCfg.actvidPol =
        pInstPrm->vipPortCfg.disCfg.actvidPol;
    pVipPortCfg->disCfg.vsyncPol =
        pInstPrm->vipPortCfg.disCfg.vsyncPol;
    pVipPortCfg->disCfg.hsyncPol =
        pInstPrm->vipPortCfg.disCfg.hsyncPol;
    pVipPortCfg->disCfg.discreteBasicMode =
        pInstPrm->vipPortCfg.disCfg.discreteBasicMode;

    pVipPortCfg->comCfg.ctrlChanSel     =
        pInstPrm->vipPortCfg.comCfg.ctrlChanSel;
    pVipPortCfg->comCfg.ancChSel8b     =
        pInstPrm->vipPortCfg.comCfg.ancChSel8b;
    pVipPortCfg->comCfg.pixClkEdgePol     =
        pInstPrm->vipPortCfg.comCfg.pixClkEdgePol;
    pVipPortCfg->comCfg.invertFidPol     =
        pInstPrm->vipPortCfg.comCfg.invertFidPol;
    pVipPortCfg->comCfg.enablePort     =
        pInstPrm->vipPortCfg.comCfg.enablePort;
    pVipPortCfg->comCfg.clrAsyncFifoRd     = FALSE;
    pVipPortCfg->comCfg.clrAsyncFifoWr     = FALSE;
    pVipPortCfg->comCfg.expectedNumLines     =
        pInstPrm->vipPortCfg.comCfg.expectedNumLines;
    pVipPortCfg->comCfg.expectedNumPix     =
        pInstPrm->vipPortCfg.comCfg.expectedNumPix;
    pVipPortCfg->comCfg.repackerMode     =
        pInstPrm->vipPortCfg.comCfg.repackerMode;

    pVipPortCfg->actCropCfg.srcNum =
        pInstPrm->vipPortCfg.actCropCfg.srcNum;
    pVipPortCfg->actCropCfg.cropCfg.cropStartX =
        pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartX;
    pVipPortCfg->actCropCfg.cropCfg.cropStartY =
        pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartY;
    pVipPortCfg->actCropCfg.cropCfg.cropWidth =
        pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropWidth;
    pVipPortCfg->actCropCfg.cropCfg.cropHeight =
        pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropHeight;

    pVipPortCfg->ancCropCfg.srcNum =
        pInstPrm->vipPortCfg.ancCropCfg.srcNum;
    pVipPortCfg->ancCropCfg.cropCfg.cropStartX =
        pInstPrm->vipPortCfg.ancCropCfg.cropCfg.cropStartX;
    pVipPortCfg->ancCropCfg.cropCfg.cropStartY =
        pInstPrm->vipPortCfg.ancCropCfg.cropCfg.cropStartY;
    pVipPortCfg->ancCropCfg.cropCfg.cropWidth =
        pInstPrm->vipPortCfg.ancCropCfg.cropCfg.cropWidth;
    pVipPortCfg->ancCropCfg.cropCfg.cropHeight =
        pInstPrm->vipPortCfg.ancCropCfg.cropCfg.cropHeight;
    pVipPrms->cscCfg = NULL;

    /*
     * Set the buffer format for the capture based on application parameter
     */
    pInst->instId = pInstPrm->vipInstId;
    /* the vip used for LVDS are not in sequence*/
    pObj->mapInstId[pInstPrm->vipInstId] = instId;

    pInst->numBufs =  pInstPrm->numBufs;
    for (outId = 0; outId < pVipCreateArgs->numStream; outId++)
    {
        pOutPrm = &pInstPrm->outParams[outId];
        pVipOutPrm = &pVipPrms->outStreamInfo[outId];

        if(pOutPrm->width > pOutPrm->maxWidth)
        {
            pOutPrm->maxWidth = pOutPrm->width;
        }

        if(pOutPrm->height > pOutPrm->maxHeight)
        {
            pOutPrm->maxHeight = pOutPrm->height;
        }

        pVipOutPrm->outFmt.width                = pOutPrm->width;
        pVipOutPrm->outFmt.height               = pOutPrm->height;
        pVipOutPrm->outFmt.dataFormat           = pOutPrm->dataFormat;
        pVipOutPrm->outFmt.fieldMerged[0]       = FALSE;
        pVipOutPrm->outFmt.fieldMerged[1]       = FALSE;
        pVipOutPrm->outFmt.fieldMerged[2]       = FALSE;
        pVipOutPrm->bufFmt                      = FVID2_BUF_FMT_FRAME;
        pVipOutPrm->memType                     = VPS_VPDMA_MT_NONTILEDMEM;

        /* For the input bayer data format, configure VIP in RAW16 bit mode */
        if (TRUE == Fvid2_isDataFmtBayer(pVipOutPrm->outFmt.dataFormat))
        {
            pVipOutPrm->outFmt.dataFormat = FVID2_DF_RAW16;
        }

        {
            Vps_VpdmaMaxSizeParams vipMaxSizePrms;

            VpsVpdmaMaxSizeParams_init(&vipMaxSizePrms);

            vipMaxSizePrms.instId = Vps_captGetVipId(pInst->instId);
            vipMaxSizePrms.maxOutWidth[0U]  = pOutPrm->maxWidth;
            vipMaxSizePrms.maxOutHeight[0U] = pOutPrm->maxHeight;
            vipMaxSizePrms.maxOutWidth[1U]  = pOutPrm->maxWidth;
            vipMaxSizePrms.maxOutHeight[1U] = pOutPrm->maxHeight/2U;
            vipMaxSizePrms.maxOutWidth[2U]  = 1U;
            vipMaxSizePrms.maxOutHeight[2U] = 1U;

            status = Fvid2_control(
                pObj->fvidHandleVipAll,
                IOCTL_VPS_CAPT_SET_VIP_MAX_SIZE,
                &vipMaxSizePrms,
                NULL);
            UTILS_assert(status == FVID2_SOK);
        }

        pInst->bufferWidth  = pOutPrm->maxWidth;
        pInst->bufferHeight[0] = pOutPrm->maxHeight;
        /* assume second plane will always be for YUV420SP data format */
        pInst->bufferHeight[1] = pOutPrm->maxHeight/2U;
        pInst->bufferHeight[2] = 0U;

        pVipOutPrm->maxOutWidth[0U]  = VPS_VPDMA_MAX_OUT_WIDTH_REG1;
        pVipOutPrm->maxOutHeight[0U] = VPS_VPDMA_MAX_OUT_HEIGHT_REG1;
        pVipOutPrm->maxOutWidth[1U]  = VPS_VPDMA_MAX_OUT_WIDTH_REG2;
        pVipOutPrm->maxOutHeight[1U] = VPS_VPDMA_MAX_OUT_HEIGHT_REG2;
        pVipOutPrm->maxOutWidth[2U]  = VPS_VPDMA_MAX_OUT_WIDTH_REG3;
        pVipOutPrm->maxOutHeight[2U] = VPS_VPDMA_MAX_OUT_HEIGHT_REG3;

        pVipOutPrm->scEnable = pOutPrm->scEnable;

        pInst->isSubframeEnabled = (Bool)pOutPrm->subFrmPrms.subFrameEnable;
        pVipOutPrm->subFrmPrms.subFrameEnable =
            pOutPrm->subFrmPrms.subFrameEnable;
        pVipOutPrm->subFrmPrms.numLinesPerSubFrame  =
            pOutPrm->subFrmPrms.numLinesPerSubFrame;
        pVipOutPrm->subFrmPrms.subFrameCb = NULL;

        /*
        * If Subframe is enabled then buffer capture mode should be circular
        * frame repeat; since it configures OCMC as circular buffer
        */
        if(pInst->isSubframeEnabled)
        {
            UTILS_assert(pVipCreateArgs->bufCaptMode
            == SYSTEM_CAPT_BCM_CIRCULAR_FRM_REPEAT);
        }

        if (Fvid2_isDataFmtSemiPlanar(pOutPrm->dataFormat))
        {
            pVipOutPrm->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
                VpsUtils_align(pInst->bufferWidth, VPS_BUFFER_ALIGNMENT);
            pVipOutPrm->outFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
                pVipOutPrm->outFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX];
        }
        else if (Fvid2_isDataFmtYuv422I(pOutPrm->dataFormat))
        {
            pVipOutPrm->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                VpsUtils_align(pInst->bufferWidth * 2U, VPS_BUFFER_ALIGNMENT);
        }
        else if (Fvid2_isDataFmtBayer(pOutPrm->dataFormat))
        {
            if ((SYSTEM_VIFW_10BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_12BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_14BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_16BIT == pInstPrm->videoIfWidth))
            {
                pVipOutPrm->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(
                        pInst->bufferWidth * 2U,
                        VPS_BUFFER_ALIGNMENT);
            }
            else
            {
                pVipOutPrm->outFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
                    VpsUtils_align(pInst->bufferWidth, (UInt32)VPS_BUFFER_ALIGNMENT);
            }
        }
        else if((pOutPrm->dataFormat == FVID2_DF_RGB24_888)
                    ||
                (pOutPrm->dataFormat == FVID2_DF_BGR24_888))
        {
            /*
             * Align the pitch to BPP boundary as well since the pitch
             * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
             * bytes (1 pixel)
             */
            pVipOutPrm->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                VpsUtils_align(
                        pInst->bufferWidth * 3U, ((UInt32)VPS_BUFFER_ALIGNMENT * 3U));
        }
        else
        {
            if ((SYSTEM_VIFW_10BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_12BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_14BIT == pInstPrm->videoIfWidth) ||
                (SYSTEM_VIFW_16BIT == pInstPrm->videoIfWidth))
            {
                pVipOutPrm->outFmt.pitch[FVID2_RAW_ADDR_IDX] =
                    VpsUtils_align(
                        pInst->bufferWidth * 2U,
                        ((UInt32)VPS_BUFFER_ALIGNMENT * 2U));
            }
            else
            {
                pVipOutPrm->outFmt.pitch[FVID2_RGB_ADDR_IDX] =
                    VpsUtils_align(
                            pInst->bufferWidth * 4U, ((UInt32)VPS_BUFFER_ALIGNMENT * 4U));
            }
        }

        /*
         * Initialize the channel information for the next link
         */
        queId = 0;
        queChId = pObj->info.queInfo[queId].numCh;

        pQueChInfo = &pObj->info.queInfo[0].chInfo[queChId];

        dataFormat = (Fvid2_DataFormat) pOutPrm->dataFormat;
        pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pQueChInfo->flags,
                dataFormat);

        pQueChInfo->width = pOutPrm->width;
        pQueChInfo->height = pOutPrm->height;

        pQueChInfo->startX      = 0;
        pQueChInfo->startY      = 0;
        pQueChInfo->pitch[0]    = pVipOutPrm->outFmt.pitch[0];
        pQueChInfo->pitch[1]    = pVipOutPrm->outFmt.pitch[1];
        pQueChInfo->pitch[2]    = pVipOutPrm->outFmt.pitch[2];

        pQueChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pQueChInfo->flags,
                pInstPrm->inParams.scanFormat);

        pVipCreateArgs->chNumMap[outId][0]  =
            pObj->info.queInfo[queId].numCh + pObj->fvid2DrvChNumOffset;

        pObj->info.queInfo[queId].numCh++;

        pObj->chToInstMap[queChId] = instId;
    }

    Fvid2CbParams_init(&pInst->cbPrm);
    pInst->cbPrm.appData = pInst;
    pInst->parent = pObj;

    /*
    * If subframe is enabled, then we are processing these interrupts in an
    * subframe copy algplugin, hence the callback function including frame data
    * processing is not required to be done on M4.
    */
    if(!pInst->isSubframeEnabled)
    {
        pInst->cbPrm.cbFxn = &CaptureLink_drvCallback;
    }
    else
    {
        pInst->cbPrm.cbFxn = NULL;
    }

    if (pVipCreateArgs->videoIfWidth < UTILS_ARRAYSIZE(gCaptureLink_ifName))
    {
        Vps_printf(" CAPTURE: %s capture mode is [%s] !!! \n",
                gCaptureLink_portName[pInstPrm->vipInstId],
                gCaptureLink_ifName[pVipCreateArgs->videoIfWidth]);
    }

    /*
     * Create the driver
     */
    pInst->captureVipHandle = FVID2_create((UInt32)FVID2_VPS_CAPT_VID_DRV,
                                           pInst->instId,
                                           pVipCreateArgs,
                                           &pInst->createStatus,
                                           &pInst->cbPrm);

    UTILS_assert(pInst->captureVipHandle != NULL);

    /*
     * Set VIP parameters
     */
    status = Fvid2_control( pInst->captureVipHandle,
                            IOCTL_VPS_CAPT_SET_VIP_PARAMS,
                            &pInst->vipPrms,
                            NULL );
    if (status != SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf(" CAPTURE: VIP Set Params IOCTL Failed!!!\n");
        nRetVal = SYSTEM_LINK_STATUS_EFAIL;
    }

    for (outId = 0; outId < pVipCreateArgs->numStream; outId++)
    {
        pOutPrm = &pInstPrm->outParams[outId];

        if(pOutPrm->frameSkipMask)
        {
            Vps_CaptFrameSkip frameSkipPrms;

            frameSkipPrms.chNum = pVipCreateArgs->chNumMap[outId][0];
            frameSkipPrms.frmSkipMask = pOutPrm->frameSkipMask;

            status = Fvid2_control( pInst->captureVipHandle,
                                IOCTL_VPS_CAPT_SET_FRAME_SKIP,
                                &frameSkipPrms,
                                NULL );
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf(" CAPTURE: VIP Frame Skip Params IOCTL Failed!!!\n");
                nRetVal = SYSTEM_LINK_STATUS_EFAIL;
            }
        }
    }

    /*
     * Allocate and queue frames to driver
     */
    if(pInst->isSubframeEnabled)
    {
        CaptureLink_subframe_drvAllocAndQueueFrames(pObj, pInst);
    }
    else
    {
        CaptureLink_drvAllocAndQueueFrames(pObj, pInst);
    }
    return nRetVal;
}

/**
 *******************************************************************************
 *
 * \brief Create API for link. Link gets created using this function.
 *
 * Creates driver instance, sets up link data structure, allocates and
 * queue frames to driver. Make link and driver ready for operation.
 *
 * \param  pObj     [IN] Capture link global handle
 * \param  pPrm     [IN] Capture link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvCreate(CaptureLink_Obj * pObj,
                           const CaptureLink_CreateParams * pPrm)
{
    Int32 status;
    UInt32 queId;
    UInt16 instId;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Create in progress !!!\n");
#endif

    UTILS_MEMLOG_USED_START();
    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    queId = 0;

    /*
     * INST 0, offset = 0
     * INST 1, offset = SYSTEM_MAX_CH_PER_OUT_QUE
     * INST 2, offset = 2*SYSTEM_MAX_CH_PER_OUT_QUE
     * ...
     */
    pObj->fvid2DrvChNumOffset = (pObj->linkId - SYSTEM_LINK_ID_CAPTURE_0)*SYSTEM_MAX_CH_PER_OUT_QUE;

    pObj->info.numQue = CAPTURE_LINK_MAX_OUT_QUE;

    System_resetLinkMemAllocInfo(&pObj->createArgs.memAllocInfo);

    status = Utils_bufCreate(&pObj->bufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    pObj->info.queInfo[queId].numCh = 0;

    if (pPrm->numVipInst)
    {
        /*
         * Create global VIP capture handle, used for dequeue,
         * queue from all active captures
         */
        pObj->fvidHandleVipAll = FVID2_create(FVID2_VPS_CAPT_VID_DRV,
                                              VPS_CAPT_INST_ALL,
                                              NULL,
                                              NULL,
                                              NULL);
        UTILS_assert(pObj->fvidHandleVipAll != NULL);
    }

    for (instId = 0U; instId < pPrm->numVipInst; instId++)
    {
        CaptureLink_drvCreateInst(pObj, instId);
    }
    for (instId = 0U; instId < pPrm->numDssWbInst; instId++)
    {
        CaptureLink_dispWbCreateInst(pObj, instId);
    }

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, "CAPTURE");
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->isFirstFrameRecv = (Bool)FALSE;

    System_assertLinkMemAllocOutOfMem(
        &pObj->createArgs.memAllocInfo,
        "CAPTURE"
        );

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("CAPTURE:",
                       pObj->memUsed,
                       UTILS_ARRAYSIZE(pObj->memUsed));
#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Create Done !!!\n");
#endif

    return status;
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
 * \param  instId         [IN] Capture instance id for which data needs to be
 *                             processed.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvProcessData(CaptureLink_Obj * pObj, UInt32 instId)
{
    UInt32 frameId, streamId, mapInstId;
    FVID2_FrameList frameList;
    FVID2_FrameList dropFrameList;
    FVID2_Frame *pFrame;
    Bool sendMsgToTsk = (Bool)FALSE;
    Int32 status;
    System_Buffer *sysBuf;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /* the vip used for LVDS are not in sequence*/
    mapInstId = pObj->mapInstId[instId];
    instId = mapInstId;
    /* Make sure that the instId is properly maped and VipHandle is not NULL */
    UTILS_assert(pObj->instObj[instId].captureVipHandle != NULL);

    /* Dequeue frames from the capture driver. Get the system buffer out of the
     * FVID2_frame->appdata. Queue system buffer in the output queue of the link
     */

    for (streamId = 0U; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST; streamId++)
    {
        FVID2_dequeue(pObj->instObj[instId].captureVipHandle,
                      &frameList,
                      streamId,
                      BSP_OSAL_NO_WAIT);

        if (frameList.numFrames)
        {
            if(pObj->isFirstFrameRecv==FALSE)
            {
                pObj->isFirstFrameRecv = (Bool)TRUE;
                Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pObj->info.queInfo[0].numCh,
                    1U);
            }
            for (frameId = 0; frameId < frameList.numFrames; frameId++)
            {
                pFrame = frameList.frames[frameId];

                pFrame->perFrameCfg = NULL;

                sysBuf = pFrame->appData;

                UTILS_assert(sysBuf->chNum < CAPTURE_LINK_MAX_CH_PER_OUT_QUE);

                /* Setting the top or bottom field into payload->flags */
                ((System_VideoFrameBuffer*) (sysBuf->payload))->flags =
                    System_Video_Frame_Set_Flag_Fid(((System_VideoFrameBuffer*) (sysBuf->payload))->flags, pFrame->fid);

                /* Update the timestamp at this point when frame is available
                 * from driver
                 */
                sysBuf->srcTimestamp = Utils_getCurGlobalTimeInUsec();
                pObj->instObj[instId].frameId = (pObj->instObj[instId].frameId + 1U);
                sysBuf->frameId = pObj->instObj[instId].frameId;
                sysBuf->linkLocalTimestamp = sysBuf->srcTimestamp;

                status = SYSTEM_LINK_STATUS_SOK;

                if(pObj->createArgs.callback)
                {
                    status = pObj->createArgs.callback(
                        pObj->createArgs.appObj,
                        sysBuf
                        );
                }

                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    sendMsgToTsk = (Bool)TRUE;

                    linkStatsInfo->linkStats.chStats[sysBuf->chNum].
                        outBufCount[0]++;

                    status = Utils_bufPutFullBuffer(&pObj->bufQue, pFrame->appData);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    /* drop buffer */
                    linkStatsInfo->linkStats.chStats[sysBuf->chNum].
                        outBufDropCount[0]++;

                    dropFrameList.frames[0] = pFrame;
                    dropFrameList.numFrames  = 1;

                    status = FVID2_queue(pObj->instObj[instId].captureVipHandle,
                                &dropFrameList,
                                 VPS_CAPT_STREAM_ID_ANY);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
            }
        }
    }

    /*
     * Send command to link for putting the buffer in output queue of the buffer
     */
    if (sendMsgToTsk == (Bool)TRUE)
    {
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA,
                           NULL);
    }

    return SYSTEM_LINK_STATUS_SOK;
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
Int32 CaptureLink_drvPutEmptyBuffers(CaptureLink_Obj * pObj,
                                     const System_BufferList * pBufList)
{
    UInt32 idx, instId;
    FVID2_FrameList frameList;
    FVID2_Frame *pFrame;
    System_Buffer *pBuf;
    Int32 status= SYSTEM_LINK_STATUS_SOK;
    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    linkStatsInfo->linkStats.putEmptyBufCount++;

    memset(&frameList, 0, sizeof(frameList));
    if (pBufList->numBuf != 0)
    {
        /*
         * Iterate through list of buffers provided from previous link.
         * Get FVID2_Frame out of bufferlist. Queue empty frames to the
         * driver queue for capturing new data
         */
        for (idx = 0; idx < pBufList->numBuf; idx++)
        {
            pBuf   = pBufList->buffers[idx];
            pFrame = pBuf->pCaptureOrgBufferPtr;

            UTILS_assert(pFrame != NULL);

            pFrame->perFrameCfg = NULL;
            frameList.frames[0] = pFrame;
            frameList.numFrames  = 1;

            UTILS_assert(pBuf->chNum < CAPTURE_LINK_MAX_CH_PER_OUT_QUE);

            instId = pObj->chToInstMap[pBuf->chNum];

            linkStatsInfo->linkStats.chStats[pBuf->chNum].inBufRecvCount++;
            linkStatsInfo->linkStats.chStats[pBuf->chNum].inBufProcessCount++;

            status = FVID2_queue(pObj->instObj[instId].captureVipHandle,
                    &frameList, VPS_CAPT_STREAM_ID_ANY);
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
 * this call VIP capture hardware is ready to receive frames.
 *
 * \param  pObj           [IN] Capture link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvStart(CaptureLink_Obj * pObj)
{
    UInt32 instId;
    CaptureLink_InstObj *pInstObj;
    UInt32 numDrvInst;

    numDrvInst = pObj->createArgs.numVipInst + pObj->createArgs.numDssWbInst;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Start in progress !!!\n");
#endif

    for (instId = 0; instId < numDrvInst; instId++)
    {
        pInstObj = &pObj->instObj[instId];

        pInstObj->frameId = 0;
        FVID2_start(pInstObj->captureVipHandle, NULL);
    }

    pObj->statsStartTime = Utils_getCurGlobalTimeInMsec();

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Start Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to Flush the buffers in driver after stopping it.
 *
 * All the frames queued inside driver is flushed by this function. Frames
 * queued inside driver needs to be flushed after stopping driver.
 *
 * \param  captureVipHandle    [IN] Handle to capture driver.
 * \param  *portName           [IN] Name of the port for which frames are
 *                                  getting flushed
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvFlush(FVID2_Handle captureVipHandle, char *portName)
{
    Int32 status;
    UInt32 streamId;
    FVID2_FrameList frameList;

    /*
     * Call FVID2_dequeue till we get all frames out of capture
     */
    for (streamId = 0U; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST; streamId++)
    {
        do
        {
                status = FVID2_dequeue(captureVipHandle,
                    &frameList, streamId, (UInt32)BSP_OSAL_NO_WAIT);

        } while ((frameList.numFrames != 0U) &&
                    (status == SYSTEM_LINK_STATUS_SOK));
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to stop driver and link.
 *
 * VIP capture hardware stops receiving frames after this call.
 *
 * \param  pObj         [IN] Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvStop(CaptureLink_Obj * pObj)
{
    UInt32 instId, frameId, streamId;
    CaptureLink_InstObj *pInstObj;
    Int32 status;
    FVID2_FrameList frameListDQ, frameListQ;
    UInt32 numDrvInst;

    numDrvInst = pObj->createArgs.numVipInst + pObj->createArgs.numDssWbInst;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Stop in progress !!!\n");
#endif

    memset(&frameListDQ, 0, sizeof(frameListDQ));
    memset(&frameListQ, 0, sizeof(frameListQ));

    for (instId = 0; instId < numDrvInst; instId++)
    {
        pInstObj = &pObj->instObj[instId];
        frameListQ.numFrames = 0;

        FVID2_stop(pInstObj->captureVipHandle, NULL);

        /*
         * Call FVID2_dequeue till we get all frames out of capture
         */
        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST; streamId++)
        {
            do
            {
                status = FVID2_dequeue(pInstObj->captureVipHandle,
                        &frameListDQ, streamId, BSP_OSAL_NO_WAIT);

                if((status==SYSTEM_LINK_STATUS_SOK) &&
                    (0U != frameListDQ.numFrames))
                {
                    /* copy the frames from DQ frame list to Q frame list */
                    for(frameId=0; frameId<frameListDQ.numFrames; frameId++)
                    {
                        frameListQ.frames[frameListQ.numFrames]
                            =
                            frameListDQ.frames[frameId];

                        frameListQ.numFrames++;
                    }
                }
            } while ((frameListDQ.numFrames != 0) && (status == SYSTEM_LINK_STATUS_SOK));
        }

        /* Q frames back to the capture drivers so that when capture resumes
         * These frames can be used for capture
         *
         */
        if(frameListQ.numFrames)
        {
            status = FVID2_queue(pInstObj->captureVipHandle,
                        &frameListQ, VPS_CAPT_STREAM_ID_ANY);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Stop Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Delete capture link and driver handle.
 *
 *
 * \param  pObj         [IN] Capture link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvDelete(CaptureLink_Obj * pObj)
{
    UInt32 instId;
    UInt32 queId;
    CaptureLink_InstObj *pInstObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 numDrvInst;

    numDrvInst = pObj->createArgs.numVipInst + pObj->createArgs.numDssWbInst;

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Delete in progress !!!\n");
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status==0);

    for (instId = 0; instId < numDrvInst; instId++)
    {
        pInstObj = &pObj->instObj[instId];

        CaptureLink_drvFlush(pInstObj->captureVipHandle,
                gCaptureLink_portName[pInstObj->instId]);

        FVID2_delete(pInstObj->captureVipHandle, NULL);

        if(pInstObj->isSubframeEnabled == TRUE)
        {
            CaptureLink_subframe_drvFreeFrames(pObj, pInstObj);
        }
        else
        {
            CaptureLink_drvFreeFrames(pObj, pInstObj);
        }
    }

    if (pObj->createArgs.numVipInst)
    {
        status = FVID2_delete(pObj->fvidHandleVipAll, NULL);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    for (queId = 0U; queId < CAPTURE_LINK_MAX_OUT_QUE; queId++)
    {
        Utils_bufDelete(&pObj->bufQue);
    }

#ifdef SYSTEM_DEBUG_CAPTURE
    Vps_printf(" CAPTURE: Delete Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Initialize the given System_Buffer array using the given Frame List.
 *
 *      The links communicate with each other using the System_Buffer. However,
 *      the driver interface uses FVID2_Frame. This function converts the
 *      given FVID2_Frame list into System_Buffer array. Also, it initializes
 *      the System_Buffer payload and other required fields. The caller must
 *      ensure that the number of frames in the FrameList match the number of
 *      elements in the system buffer and payload array.
 *
 *  \param pFrameList   [IN] FVID2 Frame List used to initialize System_Buffer
 *  \param buffers      [IN] an array of System_Buffers to be initialized
 *  \param videoFrames  [IN] an arry of Syst3em_Buffer payload
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 CaptureLink_InitSystemBuffer(const CaptureLink_Obj * pObj,
                                          const FVID2_FrameList *pFrameList,
                                          System_Buffer   *buffers,
                                          System_VideoFrameBuffer *videoFrames)
{
    UInt32 idx, planes, numFrames = pFrameList->numFrames,chNum = 0U,fvid2DrvChNumOffset = 0U;

    /*
     * buffers and videoFrames point to contiguous buffers and video frame
     * buffers respectively. Initialize all the buffers and video frame
     * buffers.
     */
    memset(buffers, 0, sizeof(*buffers)*numFrames);
    memset(videoFrames, 0, sizeof(*videoFrames)*numFrames);

    /*
     * Initialize System Buffer using the FVID2 frame information and
     * associate the System_VideoFrameBuffer as payload to the
     * System_Buffer.
     */

    for (idx = 0; idx < numFrames; idx++)
    {
        chNum = pFrameList->frames[idx]->chNum;
        fvid2DrvChNumOffset = pObj->fvid2DrvChNumOffset;
        buffers[idx].bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        buffers[idx].chNum       = chNum - fvid2DrvChNumOffset;
        buffers[idx].payloadSize = sizeof(System_VideoFrameBuffer);
        buffers[idx].payload     = &videoFrames[idx];

        /*
         * Link the frame to the system buffer. Note that the Frame's
         * appData already points to the system buffer.
         */
        buffers[idx].pCaptureOrgBufferPtr = pFrameList->frames[idx];

        for (planes = 0U; planes < SYSTEM_MAX_PLANES; planes++)
        {
            videoFrames[idx].bufAddr[planes] =
                pFrameList->frames[idx]->addr[0][planes];
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
         *                       arithmetic or array index expression
         * KW State: Defer -> Waiver -> Case by case
         *
         * Pointer arithmetic is required for performance like auto increment in loop.
         * The harmful side effect of violating this rule (accessing outside valid memory)
         * shall be checked by another code checker like Klocwork.
         */

    }

    return SYSTEM_LINK_STATUS_SOK;
}



/**
 *******************************************************************************
 *
 * \brief Allocate frames for capture. Queue allocated frames to capture driver
 *
 *
 *  \param pObj         [IN] Capture link object
 *  \param pDrvObj      [IN] Capture link instance object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvAllocAndQueueFrames(CaptureLink_Obj * pObj,
                                         CaptureLink_InstObj * pDrvObj)
{
    Int32 status;
    UInt32 idx,streamId, frameId;
    Vps_CaptVipOutInfo *pOutInfo;
    FVID2_Frame *frames;
    FVID2_FrameList frameList;
    System_Buffer *buffers;
    System_VideoFrameBuffer *videoFrames;
    UInt32 numFrames, cOffset, frameSize;
    UInt8 *pBaseAddr;

    /*
     * init frameList for list of frames that are queued per CH to driver
     */
    frameList.perListCfg = NULL;
    frameList.reserved = NULL;

    if (pDrvObj->numBufs > CAPTURE_LINK_MAX_FRAMES_PER_CH)
    {
        Vps_printf(" CAPTURE: WARNING: Create args numBufs[%d] > max[%d]."
                   " Overriding create args !!!",
                    pDrvObj->numBufs,
                    CAPTURE_LINK_MAX_FRAMES_PER_CH);
        pDrvObj->numBufs = CAPTURE_LINK_MAX_FRAMES_PER_CH;
    }

    /*
     * Bound the numBufs between min and max supported
     */
    if (pDrvObj->numBufs < CAPTURE_LINK_MIN_FRAMES_PER_CH)
    {
        Vps_printf(" CAPTURE: WARNING: Create args numBufs[%d] < min[%d]."
                   " Overriding create args !!!",
                   pDrvObj->numBufs,
                   CAPTURE_LINK_MIN_FRAMES_PER_CH);
        pDrvObj->numBufs = CAPTURE_LINK_MIN_FRAMES_PER_CH;
    }

    numFrames = pDrvObj->numBufs;

    UTILS_assert(pDrvObj->createArgs.numStream
                    <=CAPTURE_LINK_MAX_STREAMS_PER_HANDLE);

    /*
     * for every stream and channel in a capture handle
     */
    for (streamId = 0U; streamId < pDrvObj->createArgs.numStream; streamId++)
    {
        pOutInfo = &pDrvObj->vipPrms.outStreamInfo[streamId];

        /*
         * base index for pDrvObj->frames[], pDrvObj->buffers[] and
         * pDrvObj->videoFrames[];
         */
        idx = CAPTURE_LINK_MAX_CH_PER_HANDLE * numFrames * streamId;
        if (idx >= CAPTURE_LINK_MAX_FRAMES_PER_HANDLE)
        {
            Vps_printf(" CAPTURE: ERROR: Array out of bounds detected in"
                       " CaptureLink_drvAllocAndQueueFrames() !!!\n" );
            UTILS_assert((Bool)0U);
        }

        buffers     = &pDrvObj->buffers[idx];
        videoFrames = &pDrvObj->videoFrames[idx];
        frames      = &pDrvObj->frames[idx];

        /*
         * fill format with channel specific values
         */

        frameSize = pOutInfo->outFmt.pitch[0] * pDrvObj->bufferHeight[0];
        cOffset   = 0;

        if(pOutInfo->outFmt.dataFormat==FVID2_DF_YUV420SP_UV)
        {
            cOffset    = frameSize;
            frameSize += (pOutInfo->outFmt.pitch[1] * pDrvObj->bufferHeight[1]);
        }


        for (frameId = 0; frameId < numFrames; frameId++)
        {
            pDrvObj->bufSize[streamId][frameId] = frameSize;
            if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
            {
                pDrvObj->bufBaseAddr[streamId][frameId] = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pDrvObj->bufSize[streamId][frameId],
                            SYSTEM_BUFFER_ALIGNMENT
                            );
            }
            else
            {
                pDrvObj->bufBaseAddr[streamId][frameId] =
                        System_allocLinkMemAllocInfo(
                                &pObj->createArgs.memAllocInfo,
                                pDrvObj->bufSize[streamId][frameId],
                                SYSTEM_BUFFER_ALIGNMENT
                                );
            }
            UTILS_assert(pDrvObj->bufBaseAddr[streamId][frameId] != NULL);

            pBaseAddr = pDrvObj->bufBaseAddr[streamId][frameId];
            /*
            * Set rtParams and appData for every frame
            */
            memset(&frames[frameId], 0, sizeof(frames[frameId]));

            frames[frameId].chNum      =
                pDrvObj->createArgs.chNumMap[streamId][0];
            frames[frameId].addr[0][0] = pBaseAddr;
            frames[frameId].addr[0][1] = pBaseAddr + cOffset;

            /* Set the Buffer Addr for interlace case also, This will
            be ignored in case of progressive capture. Please note
            that the Assumption here is both fields (Top & bottom)
            are captured into the same buffer with Field seperated mode */
            /* MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004 Rule_17.4:
            * Pointer is used in arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            */
            frames[frameId].addr[1][0] = pBaseAddr +
                ((pOutInfo->outFmt.pitch[0] * pDrvObj->bufferHeight[0])/2U);
            frames[frameId].addr[1][1] = pBaseAddr + cOffset +
                ((pOutInfo->outFmt.pitch[1] * pDrvObj->bufferHeight[1])/2U);

            frames[frameId].appData    = &buffers[frameId];

            frameList.frames[frameId] = &frames[frameId];

            /* MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
            *                       arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            *
            * Pointer arithmetic is required for performance like auto increment in loop.
            * The harmful side effect of violating this rule (accessing outside valid memory)
            * shall be checked by another code checker like Klocwork.
            */

#ifdef SYSTEM_VERBOSE_PRINTS
            {
                Vps_printf(" CAPTURE: Frame %d: FVID2 CH %d: Link CH %d: 0x%08x, 0x%08x, %d B \n",
                        frameId,
                        frames[frameId].chNum,
                        frames[frameId].chNum - pObj->fvid2DrvChNumOffset,
                        frames[frameId].addr[0][0],
                        frames[frameId].addr[0][1],
                        frameSize
                        );
            }
#endif
        }

        /*
         * Set number of frame in frame list
         */
        frameList.numFrames = numFrames;

        /*
         * Initialize the system buffer with the video frame buffer
         * payload and initialize the payload with the frame data pointer
         */
        CaptureLink_InitSystemBuffer(pObj, &frameList, buffers, videoFrames);

        /*
         * queue the frames in frameList
         * All allocate frames are queued here as an example.
         * In general atleast 2 frames per channel need to queued
         * before starting capture,
         * else frame will get dropped until frames are queued
         */
        status =
            FVID2_queue(pDrvObj->captureVipHandle, &frameList, streamId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Free the allocated frames
 *
 *
 *  \param pObj         [IN] Capture link object
 *  \param pDrvObj      [IN] Capture link instance object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvFreeFrames(const CaptureLink_Obj * pObj,
                                CaptureLink_InstObj * pDrvObj)
{
    UInt16 streamId,frameId;
    Int32 status;

    UTILS_assert(pDrvObj->createArgs.numStream
                    <=CAPTURE_LINK_MAX_STREAMS_PER_HANDLE);

    for (streamId = 0; streamId < pDrvObj->createArgs.numStream; streamId++)
    {
        if(System_useLinkMemAllocInfo(&pObj->createArgs.memAllocInfo)==FALSE)
        {
            for(frameId = 0; frameId < pDrvObj->numBufs ; frameId++)
            {
                status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pDrvObj->bufBaseAddr[streamId][frameId],
                        pDrvObj->bufSize[streamId][frameId]);
                UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                pDrvObj->bufBaseAddr[streamId][frameId] = NULL;
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
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvPrintStatus(CaptureLink_Obj * pObj)
{
    UInt32 i;
    UInt64 exeTime;
    Uint8 str[32];
    CaptureLink_InstObj *pInstObj;
    UInt32 numDrvInst;

    numDrvInst = pObj->createArgs.numVipInst + pObj->createArgs.numDssWbInst;

    UTILS_assert(NULL != pObj->linkStatsInfo);

    for ( i = 0; i < numDrvInst; i++)
    {
        pInstObj = &pObj->instObj[i];
        if(pInstObj->isSubframeEnabled == TRUE)
        {
            snprintf ((char *) str,32U, "SUBFRAME MODE");
        }
        else
        {
            snprintf ((char *) str,32U, "FRAME MODE");
        }
        Vps_printf(" CAPTURE: %s %s\r\n",
                    gCaptureLink_portName[pObj->instObj[i].instId], str);
        if(pInstObj->isSubframeEnabled == TRUE)
        {
            Vps_printf(" \r\n");
            Vps_printf(" As subframe mode is enabled for this VIP instance"
                    " some of the statistics will appear empty\r\n");
            Vps_printf(" When subframe mode is enabled Capture Link does not"
                    " process frame data\r\n");
            Vps_printf(" **************************************************"
                    "*******************************************\r\n");

        }
    }

    exeTime = Utils_getCurGlobalTimeInMsec() - pObj->statsStartTime;

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats, "CAPTURE",(Bool) TRUE);

    CaptureLink_printDetailedStatistics(pObj, (UInt32)exeTime);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Print capture link buffer statistics
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_printBufferStatus(CaptureLink_Obj * pObj)
{
    Uint8 str[32];

    snprintf ((char *) str, 32U, "CAPTURE");
    Utils_bufPrintStatus(str, &pObj->bufQue);
    return 0;
}


/**
 *******************************************************************************
 *
 * \brief Print capture driver detailed statistics
 *
 *  \param pObj         [IN] Capture link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void CaptureLink_printDetailedStatistics(
                                CaptureLink_Obj * pObj,
                                 UInt32       execTime)
{
    Int32                retVal;
    UInt32               streamId, chId;
    Vps_CaptStatus       captStat;
    Vps_CaptChStatusArgs chStatArgs;
    Vps_CaptChStatus     chStat;
    Char                 buf[300];
    Fvid2_Handle         fvidHandle;
    UInt32               instId;
    UInt32               numStream;
    UInt32               numCh;
    UInt32               i;
    CaptureLink_InstObj *pInstObj;
    UInt32               drvChId;
    UInt32 numDrvInst;

    drvChId = 0;
    numDrvInst = pObj->createArgs.numVipInst + pObj->createArgs.numDssWbInst;

    for (i = 0; i < numDrvInst; i++)
    {
        pInstObj = &pObj->instObj[i];

        if(pInstObj->isSubframeEnabled != TRUE)
        {
            fvidHandle  = pInstObj->captureVipHandle;
            instId      = pInstObj->instId;
            numStream   = pInstObj->createArgs.numStream;
            numCh       = pInstObj->createArgs.numCh;

            retVal = Fvid2_control(
                fvidHandle,
                IOCTL_VPS_CAPT_GET_STATUS,
                &captStat,
                NULL);
            if (FVID2_SOK != retVal)
            {
                Vps_printf(
                          " CAPTURE: ERROR: IOCTL_VPS_CAPT_GET_STATUS failed !!!\n");
                break;
            }
            else
            {

                Vps_printf(" \r\n");
                Vps_printf(
                        " [%s] Statistics\r\n", gCaptureLink_portName[instId]);
                Vps_printf(
                        " ==============================\r\n");
                Vps_printf(
                        " Number of request queued  : %d\n",
                        captStat.queueCount);
                Vps_printf(
                        " Number of request dequeued: %d\n",
                        captStat.dequeueCount);
                Vps_printf(
                        " Overflow Count            : %d\r\n",
                        captStat.overflowCount);
                Vps_printf( " \r\n");

                Vps_printf(
                    "    CH    |     Q      DQ     Total   Top     Bot    Total  Top    "
                    "Bot   Min/Max     Min/Max   Dropped  Repeat   Fid   Desc \r\n");
                Vps_printf(
                    " (I/S/CH) |   Count   Count  Fields  Fields  Fields   FPS   FPS    "
                    "FPS    Width       Height   Frames   Frames  Repeat Error\r\n");
                Vps_printf(
                    " ------------------------------------------------------------------"
                    "---------------------------------------------------------\r\n");

                VpsCaptChStatusArgs_init(&chStatArgs);
                for (streamId = 0u; streamId < numStream; streamId++)
                {
                    for (chId = 0u; chId < numCh; chId++)
                    {
                        chStatArgs.chNum = drvChId + pObj->fvid2DrvChNumOffset;

                        drvChId++;

                        chStatArgs.frameInterval = 33;

                        retVal = Fvid2_control(
                            fvidHandle,
                            IOCTL_VPS_CAPT_GET_CH_STATUS,
                            &chStatArgs,
                            &chStat);
                        if (FVID2_SOK != retVal)
                        {
                            Vps_printf( " CAPTURE: ERROR: IOCTL_VPS_CAPT_GET_CH_STATUS failed !!\n");
                            break;
                        }
                        else
                        {

                            snprintf(buf, sizeof (buf),
                                    " %0.2d.%d.%0.2d | %7d %7d %7d %7d %7d %6d %5d "
                                    "%5d %5d/%-5d %5d/%-5d %7d %7d %7d %5d\r\n",
                                    instId,
                                    streamId,
                                    chId,
                                    chStat.queueCount,
                                    chStat.dequeueCount,
                                    chStat.captFrmCount,
                                    chStat.fldCount[FVID2_FID_TOP],
                                    chStat.fldCount[FVID2_FID_BOTTOM],
                                    Utils_calcFps(chStat.captFrmCount,execTime)/100U,
                                    Utils_calcFps(chStat.fldCount[FVID2_FID_TOP], execTime)/100U,
                                    Utils_calcFps(chStat.fldCount[FVID2_FID_BOTTOM], execTime)/100U,
                                    chStat.minRecvFrmWidth,
                                    chStat.maxRecvFrmWidth,
                                    chStat.minRecvFrmHeight,
                                    chStat.maxRecvFrmHeight,
                                    chStat.droppedFrmCount,
                                    chStat.repeatFrmCount,
                                    chStat.fidRepeatCount,
                                    chStat.descErrCount);

                            Vps_printf( " %s\r\n", buf);
                        }
                    }
                }
                Vps_printf( " \r\n");
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Update the Frame Skip Parameter of the VIP capture driver. Used when
 *        Temperature of the device is high to reduce power dissipation.
 *
 *  \param pObj         [IN] Capture link object
 *  \param frmSkipInp   [IN] Frame Skip mask
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_drvUpdateFrmSkip(CaptureLink_Obj * pObj, UInt32 frmSkipInp)
{
    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InstObj *pInst;
    Vps_CaptCreateParams *pVipCreateArgs;
    CaptureLink_OutParams *pOutPrm;
    UInt16 outId, idx;
    Int32 status;
    Int32 nRetVal = 0;

    for (idx = 0; idx < pObj->createArgs.numVipInst; idx++)
    {
        pInstPrm = &pObj->createArgs.vipInst[idx];
        pInst = &pObj->instObj[idx];
        pVipCreateArgs = &pInst->createArgs;
        for (outId = 0; outId < pVipCreateArgs->numStream; outId++)
        {
            Vps_CaptFrameSkip frameSkipPrms;
            pOutPrm = &pInstPrm->outParams[outId];

            pOutPrm->frameSkipMask = frmSkipInp;

            frameSkipPrms.chNum = pVipCreateArgs->chNumMap[outId][0];
            frameSkipPrms.frmSkipMask = pOutPrm->frameSkipMask;

            status = Fvid2_control( pInst->captureVipHandle,
                                IOCTL_VPS_CAPT_SET_FRAME_SKIP,
                                &frameSkipPrms,
                                NULL );
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf(" CAPTURE: VIP Frame Skip Params IOCTL Failed!!!\n");
                nRetVal = SYSTEM_LINK_STATUS_EFAIL;
            }
#ifdef SYSTEM_DEBUG_CAPTURE
            else
            {
                Vps_printf(" CAPTURE: Changed the skip mask to %x\n",  pOutPrm->frameSkipMask);
            }
#endif
        } /* for (outId = 0; outId < pVipCreateArgs->numStream; outId++) */
    } /* for (idx = 0; idx < &pObj->createArgs.numVipInst; idx++) */
    return nRetVal;

}



