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

#define OV490_SENSOR_WIDTH              (1280)
#define OV490_SENSOR_HEIGHT             (1080)

#define ENABLE_CODEC_SELECTION           (0)

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "srv_calib_usecase_iss/chains_srvCalibration_iss_priv.h"
#include "srv_calib_usecase_vip/chains_srvCalibration_vip_priv.h"
#include "srv_calib_usecase_csi2Cal/chains_srvCalibration_csi2Cal_priv.h"
#include "srv_calib_usecase_avb/chains_srvCalibration_avb_priv.h"
#include "srv_calib_usecase_csi2Cal_issRsz/chains_srvCalibration_csi2Cal_issRsz_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/include/chains_common_osal.h>
#ifdef ISS_INCLUDE
    #include <src/rtos/iss/include/iss_sensors.h>
    #include <src/rtos/iss/include/iss_utils.h>
    #include <src/rtos/iss/include/app_util_iss.h>
#endif
#include "chains_srvCalibration_Display.h"

static char calibUseCaseRunTimeMenu[] = {
"\n "
"\n ===================="
"\n Chains Run-time Menu"
"\n ===================="
"\n "
"\n 0: Stop Chain"
"\n "
"\n 1: Auto Calibration"
"\n 2: Manual Calibration"
"\n 3: Default Calibration (Using Default Cal Mat)"
"\n "
#ifndef TDA3XX_128MB_DDR
"\n 4: Save Capture Frames for all channels to MMC/SD card"
#endif
"\n 5: Unmount File System before removing MMC/SD card"
"\n 6: Mount File System after inserting MMC/SD card"
"\n "
#ifndef TDA3XX_128MB_DDR
"\n 7: Update 2D Pers Mat (after auto/manual calibration if required)"
#endif
"\n "
"\r\n d: Save Display Frame to MMC/SD card"
"\n "
#ifdef ISS_INCLUDE
"\r\n t: Print UB96x debug registers "
"\n "
#endif
"\n p: Print Performance Statistics "
"\n "
"\n Enter Choice: "
"\n "
};

static char automaticCalibMenu[] = {
    "\n "
    "\n ===================="
    "\n Automatic Calibration"
    "\n ===================="
    "\n "
    "\n 0: Exit"
    "\n "
    "\n 1: Default"
    "\n 2: Include Close Operation"
    "\n "
    "\n Enter Choice: "
    "\n "
};

static char manualCalibMenu[] = {
"\n "
"\n ===================="
"\n Manual Calibration"
"\n ===================="
"\n "
"\n 0: Exit"
"\n 1: Save ISP output frames (Will be saved in MMC/SD : All channels)"
"\n 2: Read the Calibration Matrix (CAL MAT) from file"
"\n 3: Compute LDC/GPU LUTs for 3D SRV (All view points)"
"\n 4: Unmount File System before removing MMC/SD card"
"\n 5: Mount File System after inserting MMC/SD card"
"\n "
"\n Enter Choice: "
"\n "
};

/**
 *******************************************************************************
 * \brief Run Time Menu string for codec Type Selection.
 *******************************************************************************
 */
char chains_srvCalibration_avb_codecTypeSelectMenu[] = {
    "\r\n "
    "\r\n ========================================="
    "\r\n Chains Run-time Codec Type Selection Menu"
    "\r\n ========================================="
    "\r\n "
    "\r\n Enter '0' for MJPEG "
    "\r\n "
    "\r\n Enter '1' for H.264 "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/*******************************************************************************
 *  FUNCTION DEFINITIONS
 *******************************************************************************
 */
static Void capFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);

/**
 *******************************************************************************
 *
 * \brief   Set the Sync Link Paremeters
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Void setSyncLinkParams(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 syncPeriod)
{
    pPrm->syncDelta = 0x7FFFFFFF;
    pPrm->syncThreshold = 0x7FFFFFFF;
}

/**
 *******************************************************************************
 *
 * \brief   Set DMA SW Mosaic Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setDmaSwMsLinkParams(
                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 winWidth,
                    UInt32 winHeight,
                    UInt32 outWidth,
                    UInt32 outHeight)
{
    UInt32 algId, winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    useLocalEdma = FALSE;
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->baseClassCreate.algId   = algId;
#ifndef TDA3XX_128MB_DDR
    pPrm->numOutBuf               = 4U;
#else
    pPrm->numOutBuf               = 2U;
#endif
    pPrm->useLocalEdma            = useLocalEdma;
    pPrm->initLayoutParams.numWin = numCh;

    pPrm->maxOutBufWidth     = outWidth;
    pPrm->maxOutBufHeight    = outHeight;

    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
        pWinInfo->chId = winId;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width    = winWidth;
        pWinInfo->height   = winHeight;

        /*
         *  For 4x4 layout
         */
        switch(winId)
        {
            default:
            case 0:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = 0;
                break;
            case 1:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = 0;
                break;
            case 2:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = winHeight;
                break;
            case 3:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = winHeight;
                break;
        }
    }

    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE Link Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setVpeLinkParams(
                        VpeLink_CreateParams *pPrm,
                        UInt32 numCh,
                        UInt32 OutWidth,
                        UInt32 OutHeight,
                        UInt32 inCropWidth,
                        UInt32 inCropHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;

    for (chId = 0; chId < numCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
#ifndef TDA3XX_128MB_DDR
        chPrms->outParams[outId].numBufsPerCh =
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
#else
        chPrms->outParams[outId].numBufsPerCh = 2U;
#endif
        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;

        chPrms->scCropCfg.cropStartX = 0;
        chPrms->scCropCfg.cropStartY = 0;
        chPrms->scCropCfg.cropWidth  = inCropWidth;
        chPrms->scCropCfg.cropHeight = inCropHeight;
    }
}

static Void setVpeUpscaleLinkParams(
                        VpeLink_CreateParams *pPrm,
                        UInt32 numCh,
                        UInt32 OutWidth,
                        UInt32 OutHeight,
                        UInt32 inCropWidth,
                        UInt32 inCropHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;

    for (chId = 0; chId < numCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
#ifndef TDA3XX_128MB_DDR
        chPrms->outParams[outId].numBufsPerCh =
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
#else
        chPrms->outParams[outId].numBufsPerCh = 2U;
#endif
        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;


        chPrms->scCropCfg.cropStartX = 32;
        chPrms->scCropCfg.cropStartY = 24;
        chPrms->scCropCfg.cropWidth  = inCropWidth - 32;
        chPrms->scCropCfg.cropHeight = inCropHeight - 24;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Call back function from Null_isp link for saving the ISP output
 *          frames
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void capFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{
    UInt32 chId, dstPitch, dataFormat, dstAddr0, dstAddr1;
    System_Buffer *pFrameBuf = (System_Buffer*)pBuf;
    System_VideoFrameBuffer *pVidFrame = \
                                (System_VideoFrameBuffer*)pFrameBuf->payload;
    chains_srvCalibration_DisplayAppObj *pObj = \
                        (chains_srvCalibration_DisplayAppObj*)arg;

    if (TRUE == pObj->calibrationPrm.saveFrame)
    {
        chId = pObj->calibrationPrm.saveFrameChId;

        if (chId == pFrameBuf->chNum)
        {
            pObj->calibrationPrm.saveFrame = FALSE;

            dataFormat = \
                    System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

            /*
             *  Making sure to copy the frame with pitch equal to the capture
             *  width
             */
            if ((SYSTEM_DF_YUV422I_YUYV == dataFormat)   ||
                (SYSTEM_DF_YUV422I_UYVY == dataFormat))
            {
                dstPitch = (pObj->calibrationPrm.captureOutWidth << 1);
            }
            else
            {
                dstPitch = pObj->calibrationPrm.captureOutWidth;
            }

            dstAddr0 = \
                (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[chId];
            dstAddr1 = \
            (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[chId] + \
                            (dstPitch * pObj->calibrationPrm.captureOutHeight);

            ChainsCommon_Osal_dmaCopy2D(
                pObj->dumpFramesDmaObj,
                dataFormat,
                ChainsCommon_Osal_getVirtAddr(dstAddr0),
                ChainsCommon_Osal_getVirtAddr(dstAddr1),
                dstPitch,
                0U,
                0U,
                pChInfo->width,
                pChInfo->height,
                (UInt32)pVidFrame->bufAddr[0],
                (UInt32)pVidFrame->bufAddr[1],
                pChInfo->pitch[0],
                pChInfo->pitch[1],
                pChInfo->startX,
                pChInfo->startY);

            ChainsCommon_Osal_mutexPost(pObj->calibrationPrm.saveFrameSync);
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set ISS Capture parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setCaptureParams(
    chains_srvCalibration_DisplayAppObj *pObj,
    IssCaptureLink_CreateParams *pCaptPrm)
{
    UInt32 idx;
    IssCaptureLink_Csi2Params *pCsi2Prm;
    IssCaptureLink_OutParams *pOutPrm;
    System_VideoDataFormat inOutDataFormat;

    memset((void*) pCaptPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pCaptPrm->videoIfMode = SYSTEM_VIFM_SCH_CSI2;
    pCaptPrm->videoIfWidth = SYSTEM_VIFW_4LANES;
    pCaptPrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;

    for (idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
    {
        pCsi2Prm = &pCaptPrm->csi2Params[idx];

        pCsi2Prm->isCmplxIoCfgValid = FALSE;
        pCsi2Prm->csi2PhyClk = CAPTURE_UB964_CSI2_CLOCK;

        pCsi2Prm->cmplxIoCfg.clockLane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.clockLane.position = 1U;
        pCsi2Prm->cmplxIoCfg.data1Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data1Lane.position = 2U;
        pCsi2Prm->cmplxIoCfg.data2Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data2Lane.position = 3U;
        pCsi2Prm->cmplxIoCfg.data3Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data3Lane.position = 4U;
        pCsi2Prm->cmplxIoCfg.data4Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data4Lane.position = 5U;
    }
    /* UB964 Can support only 1 interface*/
    pCaptPrm->csi2Params[0U].isCmplxIoCfgValid = TRUE;

    if (2U == pObj->numLanesOnPhy0Csi2)
    {
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data3Lane.position = 0U;
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data4Lane.position = 0U;
    }

    pCaptPrm->numCh = pObj->numCsi2Ch;

    inOutDataFormat = SYSTEM_DF_YUV422I_YUYV;
    if (BSP_PLATFORM_SOC_ID_TDA3XX == Bsp_platformGetSocId())
    {
        inOutDataFormat = SYSTEM_DF_YUV422I_UYVY;
    }

    for (idx = 0U; idx < pCaptPrm->numCh; idx++)
    {
        pOutPrm = &pCaptPrm->outParams[idx];
        pOutPrm->width          = pObj->calibrationPrm.captureOutWidth;
        pOutPrm->height         = pObj->calibrationPrm.captureOutHeight;
        pOutPrm->dataFormat     = inOutDataFormat;
        pOutPrm->inCsi2DataFormat       = SYSTEM_CSI2_YUV422_8B;
        pOutPrm->inCsi2VirtualChanNum   = idx;
        pOutPrm->maxWidth       = pObj->calibrationPrm.captureOutWidth;
        pOutPrm->maxHeight      = pObj->calibrationPrm.captureOutHeight;
        pOutPrm->numOutBuf      = CAPTURE_NUM_BUF_PER_CH;
        pOutPrm->outDataFormat  = inOutDataFormat;
        pOutPrm->outBpp         = SYSTEM_BPP_BITS16;
    }

    pCaptPrm->allocBufferForRawDump  = FALSE;

    return;
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE for CSC parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setVpeSv_CscPrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 OutWidth,
                    UInt32 OutHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;
    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
        chPrms->outParams[outId].numBufsPerCh =
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;

        chPrms->scCropCfg.cropStartX = 0;
        chPrms->scCropCfg.cropStartY = 0;
        chPrms->scCropCfg.cropWidth  = OutWidth;
        chPrms->scCropCfg.cropHeight = OutHeight;
    }
}

#ifdef ISS_INCLUDE
/**
 *******************************************************************************
 *
 * \brief   Set ISS Resizer for CSC parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setIssResizerSv(
                    IssRszLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 OutWidthRszA,
                    UInt32 OutHeightRszA,
                    UInt32 OutWidthRszB,
                    UInt32 OutHeightRszB)
{
    UInt32 chId;
    IssRszLink_ChannelParams *chPrms;

    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->channelParams[chId];

        chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = TRUE;
        chPrms->outParams.widthRszA   = OutWidthRszA;
        chPrms->outParams.heightRszA  = OutHeightRszA;
        chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B] = TRUE;
        chPrms->outParams.widthRszB   = OutWidthRszB;
        chPrms->outParams.heightRszB  = OutHeightRszB;
        chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;

#ifndef TDA3XX_128MB_DDR
        chPrms->numBuffersPerCh = 2U;
#else
        chPrms->numBuffersPerCh = 4U;
#endif
    }
}
#endif

#ifdef ISS_INCLUDE
/**
 *******************************************************************************
 *
 * \brief   Do the ISP Set Config
 *
 *******************************************************************************
*/
static Void setIspConfig(chains_srvCalibration_DisplayAppObj *pObj)
{
    appSetDefaultIspParams(&pObj->appSensInfo);
    appSetIspParamsFromDCC(&pObj->appSensInfo);

    /* Initialize Simcop Configuration */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Initializes ISP and Simcop Configurations to the default values,
       Mainly used for initializing LDC configuration */
    IssUtils_InitSimcopConfig(
            &pObj->simcopConfig,
            TRUE,       /* bypassLdc */
            TRUE);      /* bypassVtnf */
}

/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_srvCalibration_DisplayAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight,
            UInt32 rszBOutWidth,
            UInt32 rszBOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucIss.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucIss.IssM2mIspPrm;

    pCapturePrm->numCh = pObj->calibrationPrm.numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;
    pIspPrm->channelParams[0U].outParams.widthRszB = rszBOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszB = rszBOutHeight;

    for(ch = 1;ch < pCapturePrm->numCh;ch++)
    {
        pOutPrm = &pCapturePrm->outParams[ch];

        pOutPrm->dataFormat = pOutPrm0->dataFormat;
        pOutPrm->width = pOutPrm0->width;
        pOutPrm->height = pOutPrm0->height;
        pOutPrm->maxWidth = pOutPrm0->maxWidth;
        pOutPrm->maxHeight = pOutPrm0->maxHeight;
        pOutPrm->numOutBuf = pOutPrm0->numOutBuf;
        pOutPrm->inCsi2DataFormat = pOutPrm0->inCsi2DataFormat;
        pOutPrm->inCsi2VirtualChanNum = ch;

        pIspPrm->channelParams[ch].outParams.widthRszA = rszAOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszA = rszAOutHeight;
        pIspPrm->channelParams[ch].outParams.widthRszB = rszBOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszB = rszBOutHeight;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set the pin mux for the TDA3X EVM
 *
 *******************************************************************************
*/
static setMuxes(chains_srvCalibration_DisplayAppObj *pObj)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    /* Mux is configured only on TDA3X EVM */
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for ISS Capture
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_srvCalibration_iss_SetAppPrms(
                chains_srvCalibration_issObj *pUcObj, Void *appObj)
{
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;
    UInt32 numCh;
    UInt32 swMsWinWidth,swMsWinHeight;

    ChainsCommon_GetDisplayWidthHeight(
                        pObj->chainsCfg->displayType,
                        &pObj->displayWidth,
                        &pObj->displayHeight);

    pObj->calibrationPrm.captureOutWidth  = SRV_CAPT_SENSOR_OV10640_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_CAPT_SENSOR_OV10640_HEIGHT;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pObj->calibrationPrm.captureOutWidth  = SRV_CAPT_SENSOR_AR140_WIDTH;
         pObj->calibrationPrm.captureOutHeight = SRV_CAPT_SENSOR_AR140_HEIGHT;
    }

    pObj->calibrationPrm.numCh = 4U;
    ispOpMode = pObj->chainsCfg->ispOpMode;

    /* Create the sensor now */
    strncpy(pObj->appSensInfo.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appSensInfo.numCh = pObj->calibrationPrm.numCh;
    pObj->appSensInfo.ispOpMode = ispOpMode;
    pObj->appSensInfo.simcopOpMode = ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;
    pObj->appSensInfo.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appSensInfo);

    appInitIssCaptParams(&pObj->appSensInfo, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appSensInfo, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appSensInfo, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    pObj->calibrationPrm.captureOutWidth  = pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->calibrationPrm.captureOutHeight = pUcObj->IssCapturePrm.outParams[0U].height;

    /*  Override the capture and ISP parameters for multi channel and
        eanbling resizer B */
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;
    updateCaptureIspPrm(
                pObj,
                pObj->calibrationPrm.captureOutWidth,
                pObj->calibrationPrm.captureOutHeight,
                swMsWinWidth,
                swMsWinHeight);

    for (numCh = 0U; numCh < pObj->calibrationPrm.numCh; numCh ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
            ISP_OUTPUT_NUM_BUFFERS;
    }

    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = FALSE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_ispPrm.appCb = capFrameCb;
    pUcObj->Null_ispPrm.appCbArg = pObj;

    setSyncLinkParams(
                        &pUcObj->SyncPrm,
                        pObj->calibrationPrm.numCh,
                        0x0);

    /* SW MS link params */
    setDmaSwMsLinkParams(
                        &pUcObj->Alg_DmaSwMsPrm,
                        pObj->calibrationPrm.numCh,
                        swMsWinWidth,
                        swMsWinHeight,
                        pObj->displayWidth,
                        pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                        pObj->chainsCfg->displayType,
                        pObj->displayWidth,
                        pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    pUcObj->GrpxSrcPrm.is2mp = FALSE;

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;

#ifndef TDA3XX_128MB_DDR
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
#else
    pUcObj->IssCapturePrm.allocBufferForRawDump = FALSE;
    pUcObj->IssM2mIspPrm.allocBufferForDump = FALSE;
#endif
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for VIP Capture
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_srvCalibration_vip_SetAppPrms(
                chains_srvCalibration_vipObj *pUcObj, Void *appObj)
{
    UInt32 cnt;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    CaptureLink_VipInstParams *pInstPrm;
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    UInt32 swMsWinWidth,swMsWinHeight;

    ChainsCommon_GetDisplayWidthHeight(
                        pObj->chainsCfg->displayType,
                        &pObj->displayWidth,
                        &pObj->displayHeight);

    /*
     *  VIP Capture create on TDA2XX
     */
    pObj->calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT;
    pObj->calibrationPrm.numCh = 4U;

    ChainsCommon_MultiCam_StartCaptureDevice(
                        pObj->chainsCfg->captureSrc,
                        portId,
                        pObj->calibrationPrm.numCh);

    ChainsCommon_MultiCam_SetCapturePrms(
                        &pUcObj->CapturePrm,
                        pObj->calibrationPrm.captureOutWidth,
                        pObj->calibrationPrm.captureOutHeight,
                        portId,
                        pObj->calibrationPrm.numCh);
    if (pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV490)
    {
         ChainsCommon_MultiCam_SetCroppingPrms(&pUcObj->CapturePrm,
            OV490_SENSOR_WIDTH,
            OV490_SENSOR_HEIGHT,
            SRV_TDA2X_CAPTURE_WIDTH,
            SRV_TDA2X_CAPTURE_HEIGHT
            );
    }

    for (cnt = 0; cnt < SYSTEM_CAPTURE_VIP_INST_MAX; cnt++)
    {
        pInstPrm = &pUcObj->CapturePrm.vipInst[cnt];
        pInstPrm->numBufs = 6U;
    }

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_capturePrm.appCb = capFrameCb;
    pUcObj->Null_capturePrm.appCbArg = pObj;

    /* SW MS link params */
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;

    /*
     *  Resize to the SW Mosaic 4x4 layout window size
     */
    setVpeLinkParams(
                    &pUcObj->VPEPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->calibrationPrm.captureOutWidth,
                    pObj->calibrationPrm.captureOutHeight);

    setSyncLinkParams(
                    &pUcObj->SyncPrm,
                    pObj->calibrationPrm.numCh, 0x0);


    setDmaSwMsLinkParams(
                    &pUcObj->Alg_DmaSwMsPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->displayWidth,
                    pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                    pObj->chainsCfg->displayType,
                    pObj->displayWidth,
                    pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    pUcObj->GrpxSrcPrm.is2mp = FALSE;

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for CSI2CAL Capture
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_srvCalibration_csi2Cal_SetAppPrms(
                chains_srvCalibration_csi2CalObj *pUcObj, Void *appObj)
{
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    UInt32 swMsWinWidth,swMsWinHeight;

    pObj->calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT;
    pObj->calibrationPrm.numCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_GetDisplayWidthHeight(
                    pObj->chainsCfg->displayType,
                    &pObj->displayWidth,
                    &pObj->displayHeight);

    setCaptureParams(pObj, &pUcObj->IssCapturePrm);

    setVpeSv_CscPrm(
                    &pUcObj->VPE_sv_cscPrm,
                    pObj->chainsCfg->numLvdsCh,
                    pObj->calibrationPrm.captureOutWidth,
                    pObj->calibrationPrm.captureOutHeight);

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_capturePrm.appCb = capFrameCb;
    pUcObj->Null_capturePrm.appCbArg = pObj;

    /* SW MS link params */
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;

    /*
     *  Resize to the SW Mosaic 4x4 layout window size
     */
    setVpeLinkParams(
                    &pUcObj->VPEPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->calibrationPrm.captureOutWidth,
                    pObj->calibrationPrm.captureOutHeight);

    setSyncLinkParams(
                    &pUcObj->SyncPrm,
                    pObj->calibrationPrm.numCh, 0x0);


    setDmaSwMsLinkParams(
                    &pUcObj->Alg_DmaSwMsPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->displayWidth,
                    pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                    pObj->chainsCfg->displayType,
                    pObj->displayWidth,
                    pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    pUcObj->GrpxSrcPrm.is2mp = FALSE;

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

void chains_srvCalibration_avb_SetUseCaseCfg(System_IVideoFormat *codecType)
{

#if (1 == ENABLE_CODEC_SELECTION)
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {

        Vps_printf(chains_srvCalibration_avb_codecTypeSelectMenu);
        ch = Chains_readChar();
        switch(ch)
        {
            case '0':
                *codecType = SYSTEM_IVIDEO_MJPEG;
                done = TRUE;
            break;
            case '1':
                *codecType = SYSTEM_IVIDEO_H264HP;
                done = TRUE;
            break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                       *codecType);
            break;
        }
    }
#else
    *codecType = SYSTEM_IVIDEO_H264HP;
#endif

    return;
}

/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for AVB Capture
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_srvCalibration_avb_SetAppPrms(
                chains_srvCalibration_avbObj *pUcObj, Void *appObj)
{
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    UInt32 swMsWinWidth,swMsWinHeight;
    System_IVideoFormat codecType;

    ChainsCommon_GetDisplayWidthHeight(
                        pObj->chainsCfg->displayType,
                        &pObj->displayWidth,
                        &pObj->displayHeight);

    /*
     *  VIP Capture create on TDA2XX
     */
    pObj->calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT;
    pObj->calibrationPrm.numCh = 4U;

#if defined(TDA2EX_ETHSRV_BOARD)
    /* For Eth camera we don't use captureOutHeight and captureOutWidth params */
    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        0U /* captureOutWidth */,
        0U /* captureOutHeight */
        );
#endif

    ChainsCommon_SetAvbRxPrm(
        &pUcObj->AvbRxPrm,
        SRV_TDA2X_CAPTURE_WIDTH,
        SRV_TDA2X_CAPTURE_HEIGHT,
        pObj->calibrationPrm.numCh
            );

    chains_srvCalibration_avb_SetUseCaseCfg(&codecType);

    ChainsCommon_SetDecodePrm(
                            &pUcObj->DecodePrm,
                            SRV_TDA2X_CAPTURE_WIDTH,
                            SRV_TDA2X_CAPTURE_HEIGHT,
                            pObj->calibrationPrm.numCh,
                            codecType);

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_capturePrm.appCb = capFrameCb;
    pUcObj->Null_capturePrm.appCbArg = pObj;

    /* SW MS link params */
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;

    /*
     *  Resize to the SW Mosaic 4x4 layout window size
     */
    setVpeLinkParams(
                    &pUcObj->VPEPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->calibrationPrm.captureOutWidth,
                    pObj->calibrationPrm.captureOutHeight);

    if (SYSTEM_IVIDEO_H264HP == codecType)
    {
        /*
         *  In case of H264, we need to remove decoder padding
         */
        setVpeUpscaleLinkParams(
                        &pUcObj->VPE_UpscalePrm,
                        pObj->calibrationPrm.numCh,
                        1280/* swMsWinWidth */,
                        720 /* swMsWinHeight */,
                        pObj->calibrationPrm.captureOutWidth,
                        pObj->calibrationPrm.captureOutHeight);
    }

    setSyncLinkParams(
                    &pUcObj->SyncPrm,
                    pObj->calibrationPrm.numCh, 0x0);


    setDmaSwMsLinkParams(
                    &pUcObj->Alg_DmaSwMsPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->displayWidth,
                    pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                    pObj->chainsCfg->displayType,
                    pObj->displayWidth,
                    pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    pUcObj->GrpxSrcPrm.is2mp = FALSE;

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

#ifdef ISS_INCLUDE
/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for CSI2CAL Capture
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_srvCalibration_csi2Cal_issRsz_SetAppPrms(
                chains_srvCalibration_csi2Cal_issRszObj *pUcObj, Void *appObj)
{
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    UInt32 swMsWinWidth,swMsWinHeight;

    pObj->calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT;
    pObj->calibrationPrm.numCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_GetDisplayWidthHeight(
                    pObj->chainsCfg->displayType,
                    &pObj->displayWidth,
                    &pObj->displayHeight);

    setCaptureParams(pObj, &pUcObj->IssCapturePrm);

    /* SW MS link params */
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;

    setIssResizerSv(
                    &pUcObj->IssM2mResizerPrm,
                    pObj->chainsCfg->numLvdsCh,
                    pObj->calibrationPrm.captureOutWidth,
                    pObj->calibrationPrm.captureOutHeight,
                    swMsWinWidth,
                    swMsWinHeight);

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_capturePrm.appCb = capFrameCb;
    pUcObj->Null_capturePrm.appCbArg = pObj;

    setSyncLinkParams(
                    &pUcObj->SyncPrm,
                    pObj->calibrationPrm.numCh, 0x0);


    setDmaSwMsLinkParams(
                    &pUcObj->Alg_DmaSwMsPrm,
                    pObj->calibrationPrm.numCh,
                    swMsWinWidth,
                    swMsWinHeight,
                    pObj->displayWidth,
                    pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                    pObj->chainsCfg->displayType,
                    pObj->displayWidth,
                    pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    pUcObj->GrpxSrcPrm.is2mp = FALSE;

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Dump YUV frames from the ISP output to DDR and save to MMCSD
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void saveIspOutFrames(
                chains_srvCalibration_DisplayAppObj *pObj)
{
    /*
     *  Define this to dump multiple sets of YUV frames
     */
#define DUMP_MULTI_FRAMES

    UInt32 cnt;
    char fileName[128U];
    Int32 fp;

    for(cnt = 0U;cnt < pObj->calibrationPrm.numCh;cnt ++)
    {
        /*
         *  Initiate the frame save and wait for completion
         */
        pObj->calibrationPrm.saveFrameChId = cnt;
        pObj->calibrationPrm.saveFrame = TRUE;
        ChainsCommon_Osal_mutexWait(pObj->calibrationPrm.saveFrameSync);

        switch(cnt)
        {
            default:
            case 0:
                sprintf(fileName,"%s_%d.YUV",
                        SRV_IMG_FILE_FRONT,pObj->yuvDumpCount);
                break;
            case 1:
                sprintf(fileName,"%s_%d.YUV",
                        SRV_IMG_FILE_RIGHT,pObj->yuvDumpCount);
                break;
            case 2:
                sprintf(fileName,"%s_%d.YUV",
                        SRV_IMG_FILE_BACK,pObj->yuvDumpCount);
                break;
            case 3:
                sprintf(fileName,"%s_%d.YUV",
                        SRV_IMG_FILE_LEFT,pObj->yuvDumpCount);
                break;
        }

        fp = ChainsCommon_Osal_fileOpen(fileName,\
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
        UTILS_assert(-1 != fp);

        Vps_printf("SRV_CALIB_UC: Writing YUV image %d to the file %s ...\n",\
                    cnt, fileName);

        ChainsCommon_Osal_fileWrite(
            fp,
            (UInt8*)ChainsCommon_Osal_getVirtAddr(
                (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[cnt]),
            pObj->imgSize);

        ChainsCommon_Osal_fileClose(fp);

        Vps_printf("SRV_CALIB_UC: Writing YUV image %d to the file %s DONE\n",\
                    cnt, fileName);
    }

#ifdef DUMP_MULTI_FRAMES
    pObj->yuvDumpCount ++;
#endif

    Vps_printf("SRV_CALIB_UC: Writing YUV image is completed\n");
}

/**
 *******************************************************************************
 *
 * \brief   Allocate the buffers used in the Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void allocCalibUseCaseBufs(chains_srvCalibration_DisplayAppObj *pObj)
{
    UInt32 cnt;
    UInt32 quadrantSizeInBytes;

    pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf = \
        ChainsCommon_Osal_memAlloc((SRV_CALMAT_SIZE * SRV_NUM_CAMERAS),128U);
    UTILS_assert(NULL != pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf);

    pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf = \
        ChainsCommon_Osal_memAlloc((SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS),128U);
    UTILS_assert(NULL != pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf);
    pObj->calibrationPrm.update2DPersMat.persMatBuf = \
                        pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf;

    pObj->imgSize = (pObj->calibrationPrm.captureOutWidth * \
                                pObj->calibrationPrm.captureOutHeight * 3)/2;
    for (cnt = 0;cnt < pObj->calibrationPrm.numCh;cnt++)
    {
        pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[cnt] = \
                            ChainsCommon_Osal_memAlloc(
                                                    pObj->imgSize,
                                                    128U);
        pObj->calibrationPrm.update2DPersMat.inImgPtr[cnt] = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[cnt];
    }

    pObj->calibrationPrm.inChartPosBuf = ChainsCommon_Osal_memAlloc(
                                                            SRV_CHARTPOS_SIZE,
                                                            128U);

    pObj->calibrationPrm.calMatGenPrm3DSrv.cornerPointsBuf = \
                            ChainsCommon_Osal_memAlloc(
                                                    SRV_CORNERPOINT_SIZE,
                                                    128U);

    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentBaseAddr =
                            ChainsCommon_Osal_memAlloc(
                                                    SRV_PERSISTENT_BUF_SIZE,
                                                    128U);
    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentMemSize = \
                                                    SRV_PERSISTENT_BUF_SIZE;
    pObj->calibrationPrm.update2DPersMat.persistentBaseAddr = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentBaseAddr;
    pObj->calibrationPrm.update2DPersMat.persistentMemSize = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentMemSize;
    pObj->calibrationPrm.blendTableGenPrm.persistentBaseAddr = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentBaseAddr;
    pObj->calibrationPrm.blendTableGenPrm.persistentMemSize = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentMemSize;

    pObj->calibrationPrm.calMatGenPrm3DSrv.scratchBaseAddr =
                            ChainsCommon_Osal_memAlloc(
                                                    SRV_SRCATCH_BUF_SIZE,
                                                    128U);
    pObj->calibrationPrm.calMatGenPrm3DSrv.srcatchMemSize = \
                                                    SRV_SRCATCH_BUF_SIZE;
    pObj->calibrationPrm.update2DPersMat.scratchBaseAddr = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.scratchBaseAddr;
    pObj->calibrationPrm.update2DPersMat.srcatchMemSize = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.srcatchMemSize;
    pObj->calibrationPrm.blendTableGenPrm.scratchBaseAddr = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.scratchBaseAddr;
    pObj->calibrationPrm.blendTableGenPrm.srcatchMemSize = \
                    pObj->calibrationPrm.calMatGenPrm3DSrv.srcatchMemSize;

    /* GPU LUT buffer */
    quadrantSizeInBytes = \
    (9U * (1U + (SRV_OUTPUT_WIDTH_TDA2X_3D/(2U * SRV_3D_GPU_SUB_SAMPLE_RATIO))) *\
    (1U + (SRV_OUTPUT_HEIGHT_TDA2X_3D/(2U * SRV_3D_GPU_SUB_SAMPLE_RATIO)))) * 2U;

    pObj->calibrationPrm.gpuLutSize = quadrantSizeInBytes * 4U;

    pObj->calibrationPrm.gpuLut3DBuf = ChainsCommon_Osal_memAlloc(
                                                pObj->calibrationPrm.gpuLutSize,
                                                128U);

    quadrantSizeInBytes = \
    (SRV_OUTPUT_WIDTH_TDA2X_3D/SRV_3D_GPU_SUB_SAMPLE_RATIO)* \
    (SRV_OUTPUT_HEIGHT_TDA2X_3D/SRV_3D_GPU_SUB_SAMPLE_RATIO);

    pObj->calibrationPrm.gpuLutXYZSize = quadrantSizeInBytes * 3U * 4U; /* Matching image */


    pObj->calibrationPrm.gpuLut3D_XYZBuf = ChainsCommon_Osal_memAlloc(
                                                pObj->calibrationPrm.gpuLutXYZSize,
                                                128U);

    /* Only need enough for one line in one quadrant */
    quadrantSizeInBytes = \
    (1U + (SRV_OUTPUT_WIDTH_TDA2X_3D/(2U * SRV_3D_GPU_SUB_SAMPLE_RATIO))) * 4U;

    pObj->calibrationPrm.gpuLutundistSize = quadrantSizeInBytes * 4U;


    pObj->calibrationPrm.gpuLut3D_undistBuf = ChainsCommon_Osal_memAlloc(
                                                pObj->calibrationPrm.gpuLutundistSize,
                                                128U);
    /* DMA Init */
    pObj->dumpFramesDmaObj = ChainsCommon_Osal_dmaCreate();

    pObj->calibrationPrm.isCalMatGenerated = FALSE;

    /* Semaphore for frame save sync */
    pObj->calibrationPrm.saveFrameSync = ChainsCommon_Osal_mutexCreate();
    UTILS_assert(NULL != pObj->calibrationPrm.saveFrameSync);
}

/**
 *******************************************************************************
 *
 * \brief   Free the buffers used in the Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void freeCalibUseCaseBufs(chains_srvCalibration_DisplayAppObj *pObj)
{
    UInt32 cnt;

    if(pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf,
                        (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));
    }

    if(pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf,
                        (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));
    }

    for (cnt = 0;cnt < pObj->calibrationPrm.numCh;cnt++)
    {
        if (pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[cnt] != NULL)
        {
            ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.inImgPtr[cnt],
                        pObj->imgSize);
        }
    }

    if (pObj->calibrationPrm.inChartPosBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.inChartPosBuf,
                        SRV_CHARTPOS_SIZE);
    }

    if (pObj->calibrationPrm.calMatGenPrm3DSrv.cornerPointsBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.cornerPointsBuf,
                        SRV_CORNERPOINT_SIZE);
    }

    if (pObj->calibrationPrm.calMatGenPrm3DSrv.persistentBaseAddr != NULL)
    {
        ChainsCommon_Osal_memFree(
                    pObj->calibrationPrm.calMatGenPrm3DSrv.persistentBaseAddr,
                    SRV_PERSISTENT_BUF_SIZE);
    }

    if (pObj->calibrationPrm.calMatGenPrm3DSrv.scratchBaseAddr != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.calMatGenPrm3DSrv.scratchBaseAddr,
                        SRV_SRCATCH_BUF_SIZE);
    }

    if (pObj->calibrationPrm.gpuLut3DBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.gpuLut3DBuf,
                        pObj->calibrationPrm.gpuLutSize);
    }

    if (pObj->calibrationPrm.gpuLut3D_XYZBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.gpuLut3D_XYZBuf,
                        pObj->calibrationPrm.gpuLutXYZSize);
    }

    if (pObj->calibrationPrm.gpuLut3D_undistBuf != NULL)
    {
        ChainsCommon_Osal_memFree(
                        pObj->calibrationPrm.gpuLut3D_undistBuf,
                        pObj->calibrationPrm.gpuLutundistSize);
    }

    /* DMA Deinit */
    ChainsCommon_Osal_dmaDelete(pObj->dumpFramesDmaObj);

    /* Frame save sync semaphore */
    ChainsCommon_Osal_mutexDelete(pObj->calibrationPrm.saveFrameSync);
}

/**
 *******************************************************************************
 *
 * \brief   Unmount FAT File System
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void unmountFatFs()
{
    Int32 retVal;

    retVal = ChainsCommon_Osal_fileChDir("\0");
    UTILS_assert(0 == retVal);

    File_unmountFs();
    Vps_printf("SRV_CALIB_UC: File system Unmounted\n");
}

/**
 *******************************************************************************
 *
 * \brief   Mount the FAT File System
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void mountFatFs(chains_srvCalibration_DisplayAppObj *pObj)
{
    Int32 retVal;

    File_mountFs();
    Vps_printf("SRV_CALIB_UC: File System Mounted\n");

    if (BSP_PLATFORM_SOC_ID_TDA3XX == pObj->socId)
    {
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_3X);
        UTILS_assert(0 == retVal);
    }
    else if (BSP_PLATFORM_SOC_ID_TDA2PX == pObj->socId)
    {
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_2PX);
        UTILS_assert(0 == retVal);
    }
    else
    {
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_2X);
        UTILS_assert(0 == retVal);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Auto Calibration
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void autoCalibration(chains_srvCalibration_DisplayAppObj *pObj)
{
#ifndef TDA3XX_128MB_DDR
    Int32 result;
    UInt32 cnt;
#endif

    char ch;
    Bool done = FALSE;
    Bool noSupport;
    UInt32 srv2DWidth, srv2DHeight;

    pObj->calibrationPrm.thresholdMode = pObj->chainsCfg->calibrationParams.thresholdMode;
    pObj->calibrationPrm.windowMode = pObj->chainsCfg->calibrationParams.windowMode;
    pObj->calibrationPrm.Ransac = pObj->chainsCfg->calibrationParams.Ransac;
    pObj->calibrationPrm.PoseRansac = pObj->chainsCfg->calibrationParams.PoseRansac;
    pObj->calibrationPrm.SingleChartPose = pObj->chainsCfg->calibrationParams.SingleChartPose;

    if (pObj->calibrationPrm.thresholdMode == 0)
        Vps_printf("Threshold set to Default");
    else if (pObj->calibrationPrm.thresholdMode == 1 )
        Vps_printf("Threshold set to White Bias");
    else if (pObj->calibrationPrm.thresholdMode == 2)
        Vps_printf("Threshold set to No Bias");
    else if (pObj->calibrationPrm.thresholdMode == 3)
        Vps_printf("Threshold set to Black Bias 1");
    else if (pObj->calibrationPrm.thresholdMode == 4)
        Vps_printf("Threshold set to Black Bias 2");
    if (pObj->calibrationPrm.windowMode == 0)
        Vps_printf("Default Window");
    else
        Vps_printf("Original Window");
    if (pObj->calibrationPrm.Ransac == 1)
        Vps_printf("RANSAC for Corner Detection: on");
    else
        Vps_printf("Ransac for Corner Detection off");
    if (pObj->calibrationPrm.PoseRansac == 0)
        Vps_printf("RANSAC for Pose Estimation: off");
    else
        Vps_printf("RANSAC for Pose Estimation: on");
    if(pObj->calibrationPrm.SingleChartPose == 0)
        Vps_printf("Single Chart Pose Estimation: off");
    else
        Vps_printf("Single Chart Pose Estimation: on");

    do {
        noSupport = FALSE;
        Vps_printf(automaticCalibMenu);
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            pObj->calibrationPrm.binarizationMode = 0;
            break;
        case '2':
            pObj->calibrationPrm.binarizationMode = 1;
            break;
        default:
            Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
            noSupport = TRUE;
            break;
        }

        if (FALSE == done && noSupport == FALSE) {

            GrpxSrcLink_SrvCalibPrm grpxSrcSrvCalibPrm;

            /* 1.Generate the Calibration Matrix */
            Vps_printf("SRV_CALIB_UC: 1.Generating the calibration Matrix ...\n");

            ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    ALGORITHM_LINK_SRV_OUTPUT_2D,
                                    &srv2DWidth,
                                    &srv2DHeight);
            pObj->calibrationPrm.calMatGenPrm3DSrv.displayWidth = srv2DWidth;
            pObj->calibrationPrm.calMatGenPrm3DSrv.displayHeight = srv2DHeight;

            Chain_Common_SRV_generateCalMat(
                &pObj->calibrationPrm,
                SRV_CALIB_TYPE_AUTO);

            /*
             *  The auto detected chart positions are plotted on the Graphics display
             */
            grpxSrcSrvCalibPrm.cornerPointsBuf = \
                pObj->calibrationPrm.calMatGenPrm3DSrv.cornerPointsBuf;
            grpxSrcSrvCalibPrm.cornerPointBufSize = SRV_CORNERPOINT_SIZE;

            System_linkControl(
                pObj->grpxSrcLinkId,
                GRPX_SRC_LINK_CMD_SRV_CALIB_PARAM,
                &grpxSrcSrvCalibPrm,
                sizeof(GrpxSrcLink_SrvCalibPrm),
                TRUE);

            if ((BSP_PLATFORM_SOC_ID_TDA3XX == pObj->socId) ||
                (BSP_PLATFORM_SOC_ID_TDA2PX == pObj->socId))
            {
                /* 2. Generate the LDC LUTs for all the views */
                Vps_printf("SRV_CALIB_UC: 2.Generating the LDC LUTs ...\n");
                Chain_Common_SRV_generateLdcLut4ViewPoints(&pObj->calibrationPrm);
            }
            else
            {
                /* 2. Generate the GPU LUTs for all the views */
                Vps_printf("SRV_CALIB_UC: 2.Generating the GPU LUT ...\n");
                Chain_Common_SRV_generateGpuLut(&pObj->calibrationPrm);
            }

            /*
             *  For 128 MB DDR memory config the 2D pers mat updation is disabled.
             */
#ifndef TDA3XX_128MB_DDR
            for (cnt = 0; cnt < MAX_NUM_2D_PERSMAT_UPDATE; cnt++)
            {
                ChainsCommon_SurroundView_GetSrvOutputResolution(
                                        ALGORITHM_LINK_SRV_OUTPUT_2D,
                                        &srv2DWidth,
                                        &srv2DHeight);
                pObj->calibrationPrm.update2DPersMat.SVOutDisplayWidth = srv2DWidth;
                pObj->calibrationPrm.update2DPersMat.SVOutDisplayHeight = srv2DHeight;

                result = Chain_Common_SRV_update2DPersMat(&pObj->calibrationPrm);

                if (0 == result)
                {
                    Vps_printf(" 2D Pers Mat Update Success\n");
                    break;
                }
                else
                {
                    Vps_printf(" 2D Pers Mat Update Failed\n");
                }
            }
#endif
        }
    } while (FALSE == done);

    Vps_printf("SRV_CALIB_UC: *************************************\n");
    Vps_printf("SRV_CALIB_UC: 3.Auto Calibration is completed   ...\n");
    Vps_printf("SRV_CALIB_UC: *************************************\n");
}

/**
 *******************************************************************************
 *
 * \brief   Manual Calibration
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void manualCalibration(chains_srvCalibration_DisplayAppObj *pObj)
{
    char ch;
    Bool done = FALSE;
    UInt32 srv2DWidth, srv2DHeight;

    do{
        Vps_printf(manualCalibMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                saveIspOutFrames(pObj);
                break;
            case '2':
                ChainsCommon_SurroundView_GetSrvOutputResolution(
                                        ALGORITHM_LINK_SRV_OUTPUT_2D,
                                        &srv2DWidth,
                                        &srv2DHeight);
                pObj->calibrationPrm.calMatGenPrm3DSrv.displayWidth = srv2DWidth;
                pObj->calibrationPrm.calMatGenPrm3DSrv.displayHeight = srv2DHeight;

                Chain_Common_SRV_generateCalMat(&pObj->calibrationPrm, \
                                                        SRV_CALIB_TYPE_MANUAL);
                break;
            case '3':
                if ((BSP_PLATFORM_SOC_ID_TDA3XX == pObj->socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA2PX == pObj->socId))
                {
                    Chain_Common_SRV_generateLdcLut4ViewPoints(
                                                        &pObj->calibrationPrm);
                }
                else if (BSP_PLATFORM_SOC_ID_TDA2XX == pObj->socId)
                {
                    Chain_Common_SRV_generateGpuLut(&pObj->calibrationPrm);
                }
                break;
            case '4':
                unmountFatFs();
                break;
            case '5':
                mountFatFs(pObj);
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    }while (FALSE == done);

    Vps_printf("SRV_CALIB_UC: *************************************\n");
    Vps_printf("SRV_CALIB_UC: Manual Calibration is completed   ...\n");
    Vps_printf("SRV_CALIB_UC: *************************************\n");
}

/**
 *******************************************************************************
 *
 * \brief   Default Calibration
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void defaultCalibration(chains_srvCalibration_DisplayAppObj *pObj)
{
    Int32 fp;
    UInt8 *writeAddr;
    Int32 defaultCalMat_tda2x[] = {
                    0x3fe3d380, 0xfc98e9df, 0x0183b1fc, 0xfc790aa9, 0xcb952369,
                    0x248dc121, 0xff4c0220, 0xdb6cf86b, 0xcb7c34b0, 0xfffa7af1,
                    0x000ba256, 0xfffbbeed, 0xfe34029e, 0xcbc583e6, 0x24f4787d,
                    0xc005d487, 0x017bbde2, 0x0007019c, 0xff1f02ec, 0xdb0f17af,
                    0xcbbf9c92, 0x0007df30, 0x000845a0, 0xfffe78dc, 0xc084b8cf,
                    0x02ed3bdc, 0xf869ff11, 0x0667685c, 0x31f7d700, 0xd886ccb9,
                    0x041e1dc6, 0xd81656d0, 0xce24d047, 0x00054fe5, 0xfffed221,
                    0x0005fc0a, 0x00dde42f, 0x31660223, 0xd74f4579, 0x3ff9f9ed,
                    0xfe7da513, 0xffbcd725, 0xfed685f9, 0xd75402bf, 0xce996899,
                    0xfff8466c, 0xffff46c4, 0x0005b088};
    Int32 defaultCalMat_tda3x[] = {
                    0x40017ebd, 0xfef62041, 0xff7b5a64, 0xffb85675, 0xd0869c35,
                    0x2ae54252, 0xfeeb678c, 0xd51a51ad, 0xd0845697, 0xfffa9059,
                    0x000a417e, 0xfff90818, 0x0063aaee, 0xd38df57f, 0x2e0b8571,
                    0xc016b06e, 0xfd44dccb, 0xfdf457d3, 0x0362a7e3, 0xd207fcf2,
                    0xd3997672, 0x00083573, 0x0007e739, 0xfffd1ead, 0xc00e84a1,
                    0x00df1674, 0x028ef8a1, 0xfecfaaa4, 0x2fe48796, 0xd5905857,
                    0xfd81f2b8, 0xd58dce2e, 0xd02a7a7b, 0x0005e65d, 0xfffe8ab7,
                    0x00057027, 0x022a148b, 0x32944e4d, 0xd8d83405, 0x3f7753df,
                    0xf93f19b3, 0xfb460d92, 0xf8220767, 0xd954bd04, 0xcd9d3ced,
                    0xfff7f557, 0xffffb1b6, 0x000582cf};
    Int32 defaultPersMat[] = {
                    0x001d724e, 0xffff69b0, 0xfce54791, 0xffff730b, 0x00219b17,
                    0x01399fcf, 0xffffebbc, 0xffffff7a, 0x00100000, 0x00193522,
                    0x000005eb, 0x00484ae9, 0xfffefe78, 0x00108bde, 0xfc287b51,
                    0x0000015c, 0x00000df5, 0x00100000, 0x0011d7c2, 0xffffa19c,
                    0xfdcd2f6b, 0xffff71b2, 0x00168bde, 0xff8e89d4, 0x00000c26,
                    0x00000082, 0x00100000, 0x001999ae, 0xffff6519, 0xff2c28a3,
                    0x0002683e, 0x0012b630, 0x0153fdfb, 0x000001fa, 0xfffff41f,
                    0x00100000};

    if ((BSP_PLATFORM_SOC_ID_TDA3XX == pObj->socId) ||
        (BSP_PLATFORM_SOC_ID_TDA2PX == pObj->socId))
    {
        memcpy(
            (Ptr)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            defaultCalMat_tda3x,
            (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

        ChainsCommon_Osal_cacheWb(
            ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

        memcpy(
            (Ptr)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf),
            defaultPersMat,
            (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

        ChainsCommon_Osal_cacheWb(
            ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf),
            (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

        pObj->calibrationPrm.isCalMatGenerated = TRUE;

        Chain_Common_SRV_generateLdcLut4ViewPoints(
                                            &pObj->calibrationPrm);
    }
    else
    {
        memcpy(
            (Ptr)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            defaultCalMat_tda2x,
            (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

        ChainsCommon_Osal_cacheWb(
            ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

        pObj->calibrationPrm.isCalMatGenerated = TRUE;

        Chain_Common_SRV_generateGpuLut(&pObj->calibrationPrm);
    }

    /*
     *  Write the Pers mat to the file
     */

    Vps_printf("SRV_CALIB_UC: Writing Pers Mat to the file ...\n");

    fp = ChainsCommon_Osal_fileOpen(SRV_PERSMAT_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
    UTILS_assert (-1 != fp);

    /* Write the calMat for each camera */
    writeAddr = (UInt8*)defaultPersMat;

    /* Write Pers mat to the file */
    ChainsCommon_Osal_fileWrite(
                    fp,
                    writeAddr,
                    (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

    ChainsCommon_Osal_fileClose(fp);

    Vps_printf("SRV_CALIB_UC: *************************************\n");
    Vps_printf("SRV_CALIB_UC: Default Calibration is completed  ...\n");
    Vps_printf("SRV_CALIB_UC: *************************************\n");
}

/**
 *******************************************************************************
 *
 * \brief   Create the use case based on the capture source
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Int32 createCalibUseCase(chains_srvCalibration_DisplayAppObj *pObj)
{
    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_Create(&pObj->ucIss, pObj);
            pObj->grpxSrcLinkId = pObj->ucIss.GrpxSrcLinkID;
#endif
            break;

        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_Create(&pObj->ucVip, pObj);
            pObj->grpxSrcLinkId = pObj->ucVip.GrpxSrcLinkID;
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            pObj->numLanesOnPhy0Csi2 = 4U;
            if (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType())
            {
                /* J6 Eco has 2 lanes */
                pObj->numLanesOnPhy0Csi2 = 2U;
            }
            pObj->numCsi2Ch = pObj->chainsCfg->numLvdsCh;

            if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
            {
                /* TDA2EX will use the VPE */
                chains_srvCalibration_csi2Cal_Create(&pObj->ucCsi2Cal, pObj);
                pObj->grpxSrcLinkId = pObj->ucCsi2Cal.GrpxSrcLinkID;
            }
            else
            {
#ifdef ISS_INCLUDE
                /* TDA2PX and TDA3X will use ISS Resizer */
                chains_srvCalibration_csi2Cal_issRsz_Create(&pObj->ucCsi2CalIssRsz, pObj);
                pObj->grpxSrcLinkId = pObj->ucCsi2CalIssRsz.GrpxSrcLinkID;
#endif
            }
            break;
        case CHAINS_CAPTURE_INTF_AVB:
            chains_srvCalibration_avb_Create(&pObj->ucAvb, pObj);
            pObj->grpxSrcLinkId = pObj->ucAvb.GrpxSrcLinkID;
            break;
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief   Start the Calibration Use case
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issMultCaptIspSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 startCalibUseCase(chains_srvCalibration_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            /* Sets the Simcop Config also */
            setIspConfig(pObj);
            setMuxes(pObj);
            appStartIssSensorSerDes(&pObj->appSensInfo);

            /* Start ISS use case */
            chains_srvCalibration_iss_Start(&pObj->ucIss);
#endif
            break;

        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_Start(&pObj->ucVip);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            ChainsCommon_MultiCam_StartCaptureDevice(pObj->chainsCfg->captureSrc,
                                                    NULL,
                                                    pObj->numCsi2Ch);

            if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
            {
                chains_srvCalibration_csi2Cal_Start(&pObj->ucCsi2Cal);
            }
            else
            {
#ifdef ISS_INCLUDE
                chains_srvCalibration_csi2Cal_issRsz_Start(&pObj->ucCsi2CalIssRsz);
#endif
            }
            break;
        case CHAINS_CAPTURE_INTF_AVB:
            chains_srvCalibration_avb_Start(&pObj->ucAvb);
            break;
    }

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete the Calibration Use case
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Int32 stopAndDeleteCalibUseCase(chains_srvCalibration_DisplayAppObj *pObj)
{
    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_Stop(&pObj->ucIss);
            chains_srvCalibration_iss_Delete(&pObj->ucIss);
            appStopISSSensor(&pObj->appSensInfo);
            appDeleteISSSensor(&pObj->appSensInfo);
#endif
            break;

        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_Stop(&pObj->ucVip);
            chains_srvCalibration_vip_Delete(&pObj->ucVip);
            ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
            {
                chains_srvCalibration_csi2Cal_Stop(&pObj->ucCsi2Cal);
                chains_srvCalibration_csi2Cal_Delete(&pObj->ucCsi2Cal);
            }
            else
            {
#ifdef ISS_INCLUDE
                chains_srvCalibration_csi2Cal_issRsz_Stop(&pObj->ucCsi2CalIssRsz);
                chains_srvCalibration_csi2Cal_issRsz_Delete(&pObj->ucCsi2CalIssRsz);
#endif
            }
            ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
            break;
        case CHAINS_CAPTURE_INTF_AVB:
            chains_srvCalibration_avb_Stop(&pObj->ucAvb);
            chains_srvCalibration_avb_Delete(&pObj->ucAvb);
#if defined(TDA2EX_ETHSRV_BOARD)
            /*
             * For Eth camera we don't use captureOutHeight and captureOutWidth
             * params
             */
            ChainsCommon_StopCaptureDevice( pObj->chainsCfg->captureSrc );
#endif
            break;
    }

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);


    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Statistics
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issMultCaptIspSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Int32 printStatistics(chains_srvCalibration_DisplayAppObj *pObj)
{
    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_printStatistics(&pObj->ucIss);
#endif
            break;

        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_printStatistics(&pObj->ucVip);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            if(BSP_PLATFORM_SOC_ID_TDA2EX == pObj->socId)
            {
                chains_srvCalibration_csi2Cal_printStatistics(&pObj->ucCsi2Cal);
            }
            else
            {
#ifdef ISS_INCLUDE
                chains_srvCalibration_csi2Cal_issRsz_printStatistics(&pObj->ucCsi2CalIssRsz);
#endif
            }
            break;
        case CHAINS_CAPTURE_INTF_AVB:
            chains_srvCalibration_avb_printStatistics(&pObj->ucAvb);
            break;
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   4 Channel surround view usecase entry function
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_srvCalibration_Display(
                        Chains_Ctrl *chainsCfg,
                        Chains_CaptureIntf captureIntf)
{
    Int32 retVal;
    char ch;
    UInt32 done = FALSE;
    chains_srvCalibration_DisplayAppObj chainsObj;
#ifndef TDA3XX_128MB_DDR
    UInt32 srv2DWidth, srv2DHeight;
#endif
    chainsObj.chainsCfg = chainsCfg;
    chainsObj.yuvDumpCount = 0U;
    chainsObj.calibrationPrm.saveFrame = FALSE;
    /* Hardcoding parameters to be 1MP */
    chainsObj.calibrationPrm.is2mp = FALSE;
    chainsObj.captureIntf = captureIntf;

    chainsObj.socId = Bsp_platformGetSocId();
    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;

    /* Check if the required files are present in the MMC/SD card */
    if (BSP_PLATFORM_SOC_ID_TDA3XX == chainsObj.socId)
    {
        /* TDA3X */
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_3X);
        if (SYSTEM_LINK_STATUS_SOK != retVal)
        {
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Vps_printf(" CHAINS: TDA3x Folder not present in MMC/SD \n");
            Vps_printf(" CHAINS: Create TDA3X folder and copy the following files from\n");
            Vps_printf(" CHAINS: '/vision_sdk/tools/surround_vision_tools/Srv_LUTs':\n");
            Vps_printf(" CHAINS:     1. V2W.LZ4  \n");
            Vps_printf(" CHAINS:     2. V2W_IDX.BIN  \n");
            Vps_printf(" CHAINS:     3. CHARTPOS.BIN  \n");
            Vps_printf(" CHAINS:     4. LENS.BIN  \n");
            Vps_printf(" CHAINS:     5. LENS_2D.BIN  \n");
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Task_sleep (100U);

            return;
        }

        if(CHAINS_CAPTURE_INTF_VIP == chainsObj.captureIntf)
        {
            /* LVDS capture on TDA3X supports only XGA TDM display mode */
            chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM;
        }
    }
    else if ( (BSP_PLATFORM_SOC_ID_TDA2XX == chainsObj.socId) ||
              (BSP_PLATFORM_SOC_ID_TDA2EX == chainsObj.socId) )
    {
        /* TDA2X & TDA2EX */
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_2X);
        if (SYSTEM_LINK_STATUS_SOK != retVal)
        {
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Vps_printf(" CHAINS: TDA2X Folder not present in MMC/SD \n");
            Vps_printf(" CHAINS: Create TDA2X folder and copy the following files from\n");
            Vps_printf(" CHAINS: '/vision_sdk/tools/surround_vision_tools/Srv_LUTs':\n");
            Vps_printf(" CHAINS:     1. CHARTPOS.BIN  \n");
            Vps_printf(" CHAINS:     2. LENS.BIN  \n");
            Vps_printf(" CHAINS:     3. LENS_2D.BIN  \n");
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Task_sleep (100U);

            return;
        }
    }
    else
    {
        /* TDA2PX */
        retVal = ChainsCommon_Osal_fileChDir(SRV_DIR_2PX);
        if (SYSTEM_LINK_STATUS_SOK != retVal)
        {
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Vps_printf(" CHAINS: TDA2PX Folder not present in MMC/SD \n");
            Vps_printf(" CHAINS: Create TDA2PX folder and copy the following files from\n");
            Vps_printf(" CHAINS: '/vision_sdk/tools/surround_vision_tools/Srv_LUTs':\n");
            Vps_printf(" CHAINS:     1. CHARTPOS.BIN  \n");
            Vps_printf(" CHAINS:     2. LENS.BIN  \n");
            Vps_printf(" CHAINS:     3. LENS_2D.BIN  \n");
            Vps_printf(" CHAINS:     4. V2W.LZ4  \n");
            Vps_printf(" CHAINS:     4. V2W_IDX.BIN  \n");
            Vps_printf(" CHAINS: -------------------------------------------------- \n");
            Task_sleep (100U);

            return;
        }
    }

    /* Create use case */
    createCalibUseCase(&chainsObj);

    /* Allocate Buffers */
    allocCalibUseCaseBufs(&chainsObj);

    /* Start the use case */
    startCalibUseCase(&chainsObj);

    do
    {
        Vps_printf(calibUseCaseRunTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':
                autoCalibration(&chainsObj);
                break;

            case '2':
                manualCalibration(&chainsObj);
                break;

            case '3':
                defaultCalibration(&chainsObj);
                break;

            case '4':
                saveIspOutFrames(&chainsObj);
                break;

            case '5':
                unmountFatFs();
                break;

            case '6':
                mountFatFs(&chainsObj);
                break;

            case '7':
#ifndef TDA3XX_128MB_DDR
                ChainsCommon_SurroundView_GetSrvOutputResolution(
                                        ALGORITHM_LINK_SRV_OUTPUT_2D,
                                        &srv2DWidth,
                                        &srv2DHeight);
                chainsObj.calibrationPrm.update2DPersMat.SVOutDisplayWidth = srv2DWidth;
                chainsObj.calibrationPrm.update2DPersMat.SVOutDisplayHeight = srv2DHeight;

                retVal = Chain_Common_SRV_update2DPersMat(&chainsObj.calibrationPrm);

                if(0 == retVal)
                {
                    Vps_printf(" 2D Pers Mat Update Success\n");
                }
                else
                {
                    Vps_printf(" 2D Pers Mat Update Failed\n");
                }
#endif
                break;

            case 'd':
            case 'D':
            {
                #define NUM_DISPLAY_FRAMES       (1U)
                Void chains_saveDisFrame(
                                    char *fileName,
                                    UInt32 numSaveFrames,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight);

                chains_saveDisFrame(
                        "DISFR.YUV",
                        NUM_DISPLAY_FRAMES,
                        chainsObj.displayWidth,
                        chainsObj.displayHeight);
                break;
            }

#ifdef ISS_INCLUDE
            case 't':
            case 'T':
                appGetUB96xRegVal(&chainsObj.appSensInfo);
                break;
#endif
            case 'p':
            case 'P':
                printStatistics(&chainsObj);
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    } while (FALSE == done);

    /* Stop and Delete the use case */
    stopAndDeleteCalibUseCase(&chainsObj);

    /* Free the buffers */
    freeCalibUseCaseBufs(&chainsObj);

    /* Change to the root dir */
    retVal = ChainsCommon_Osal_fileChDir("\0");
    UTILS_assert(0 == retVal);
}

