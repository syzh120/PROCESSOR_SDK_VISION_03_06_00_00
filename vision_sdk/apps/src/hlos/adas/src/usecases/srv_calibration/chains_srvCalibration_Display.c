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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_srvCalibration_vip_priv.h"
#include "chains_srvCalibration_csi2Cal_priv.h"
#include "chains_srvCalibration_iss_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_srv_calib.h>
#include <osa_file.h>
#include <src/hlos/adas/include/chains_common_iss.h>

/* Crop parameters for the 2 MP resolution */
#define CAPTURE_CROP_2MP_STARTX             (20U)
#define CAPTURE_CROP_2MP_STARTY             (11U)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK            (800U)

#define SRV_CAPT_SENSOR_AR140_WIDTH             (1280U)
#define SRV_CAPT_SENSOR_AR140_HEIGHT            (800U)
#define SRV_CAPT_SENSOR_OV10640_WIDTH           (1280U)
#define SRV_CAPT_SENSOR_OV10640_HEIGHT          (720U)

/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH              (4U)

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
"\n 4: Save Capture Frames for all channels to MMC/SD card"
"\n "
"\r\n d: Save Display Frame to MMC/SD card"
"\n "
"\n "
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
"\n "
"\n Enter Choice: "
"\n "
};

static char calibUseCaseResolutionMenu[] = {
"\n "
"\n ===================="
"\n Resolution Menu"
"\n ===================="
"\n "
"\n 1: 1 MP (1280x720)"
"\n 2: 2 MP (1920x1080)"
"\n "
"\n Enter Choice: "
"\n "
};

/*******************************************************************************
 *  FUNCTION DEFINITIONS
 *******************************************************************************
 */
static Void capFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);

/**
 *******************************************************************************
 *
 *  \brief  chains_srvCalibration_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    chains_srvCalibration_vipObj ucVip;
    chains_srvCalibration_csi2CalObj ucCsi2Cal;
    chains_srvCalibration_issObj ucIss;

    UInt32  displayWidth;
    UInt32  displayHeight;
    Chains_Ctrl *chainsCfg;
    UInt32 yuvDumpCount;
    UInt32 imgSize;
    Ptr dumpFramesDmaObj;

    Chain_Common_SRV_CalibrationPrm calibrationPrm;

    Chains_CaptureIntf captureIntf;
    UInt32 grpxSrcLinkId;
    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */

    Bool is2mp;

    Chains_CaptureSrc captureSrc;

#ifdef ISS_INCLUDE
    AppCtrl_IssParams                   appCtrlIssPrms;
#endif
} chains_srvCalibration_DisplayAppObj;

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
    pPrm->numOutBuf               = 4;
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
        chPrms->scCropCfg.cropWidth  = inCropWidth;
        chPrms->scCropCfg.cropHeight = inCropHeight;
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
static Void setCaptureParams(chains_srvCalibration_DisplayAppObj *pObj)
{
    UInt32 idx;
    IssCaptureLink_CreateParams *pCaptPrm;
    IssCaptureLink_Csi2Params *pCsi2Prm;
    IssCaptureLink_OutParams *pOutPrm;
    System_VideoDataFormat inOutDataFormat;

    pCaptPrm = &pObj->ucCsi2Cal.IssCapturePrm;
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

/**
 *******************************************************************************
 *
 * \brief   Set Calibration Use case Link Parameters for TDA2X
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
    pObj->calibrationPrm.numCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_MultiCam_SetCapturePrms(
                                &pUcObj->CapturePrm,
                                pObj->calibrationPrm.numCh);

    for(cnt = 0; cnt < SYSTEM_CAPTURE_VIP_INST_MAX; cnt++)
    {
        UInt32 streamId;
        pInstPrm = &pUcObj->CapturePrm.vipInst[cnt];
        pInstPrm->numBufs = 6U;

        /* 2 MP resolution */
        if((SRV_TDA2X_CAPTURE_WIDTH_2MP == pObj->calibrationPrm.captureOutWidth) &&
           (SRV_TDA2X_CAPTURE_HEIGHT_2MP == pObj->calibrationPrm.captureOutHeight))
        {
            pInstPrm->inParams.width = SRV_TDA2X_CAPTURE_WIDTH_2MP;
            pInstPrm->inParams.height = SRV_TDA2X_CAPTURE_HEIGHT_2MP;

            for(streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST; streamId++)
            {
                pInstPrm->outParams[streamId].width = SRV_TDA2X_CAPTURE_WIDTH_2MP;
                pInstPrm->outParams[streamId].height = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
                pInstPrm->outParams[streamId].maxWidth = SRV_TDA2X_CAPTURE_WIDTH_2MP;
                pInstPrm->outParams[streamId].maxHeight = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
            }

            pInstPrm->scPrms.inCropCfg.cropWidth = SRV_TDA2X_CAPTURE_WIDTH_2MP;
            pInstPrm->scPrms.inCropCfg.cropHeight = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
            pInstPrm->vipPortCfg.comCfg.expectedNumLines = SRV_TDA2X_CAPTURE_WIDTH_2MP;
            pInstPrm->vipPortCfg.comCfg.expectedNumPix = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropWidth = SRV_TDA2X_CAPTURE_WIDTH_2MP;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropHeight = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartX = CAPTURE_CROP_2MP_STARTX;
            pInstPrm->vipPortCfg.actCropCfg.cropCfg.cropStartY = CAPTURE_CROP_2MP_STARTY;
        }
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
    if (pObj->is2mp == TRUE)
    {
        pUcObj->GrpxSrcPrm.is2mp = TRUE;
    }
    else
    {
        pUcObj->GrpxSrcPrm.is2mp = FALSE;
    }
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
 * \brief   Set Calibration Use case Link Parameters for TDA2X
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

    pObj->calibrationPrm.numCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_GetDisplayWidthHeight(
                        pObj->chainsCfg->displayType,
                        &pObj->displayWidth,
                        &pObj->displayHeight);

    setCaptureParams(pObj);

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
    if (pObj->is2mp == TRUE)
    {
        pUcObj->GrpxSrcPrm.is2mp = TRUE;
    }
    else
    {
        pUcObj->GrpxSrcPrm.is2mp = FALSE;
    }

    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;

    /* Enable clock for the CAL and CSI2 */
    system("omapconf write 0x4A009028 0x00040001");
    system("msleep 10");
    system("omapconf write 0x4A009038 0x00030000");
    system("msleep 10");
}

#ifdef ISS_INCLUDE
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

Void chains_srvCalibration_iss_SetAppPrms(
                chains_srvCalibration_issObj *pUcObj, Void *appObj)
{
    chains_srvCalibration_DisplayAppObj *pObj
        = (chains_srvCalibration_DisplayAppObj*)appObj;
    UInt32 swMsWinWidth,swMsWinHeight;
    UInt32 ch;
    AppCtrl_IssParams *pAppCtrlIssPrms;

    pObj->calibrationPrm.numCh = 4U;

    pObj->calibrationPrm.captureOutWidth  = SRV_CAPT_SENSOR_OV10640_WIDTH;
    pObj->calibrationPrm.captureOutHeight = SRV_CAPT_SENSOR_OV10640_HEIGHT;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pObj->calibrationPrm.captureOutWidth  = SRV_CAPT_SENSOR_AR140_WIDTH;
        pObj->calibrationPrm.captureOutHeight = SRV_CAPT_SENSOR_AR140_HEIGHT;
    }

    ChainsCommon_GetDisplayWidthHeight(
                        pObj->chainsCfg->displayType,
                        &pObj->displayWidth,
                        &pObj->displayHeight);

    pAppCtrlIssPrms = &pObj->appCtrlIssPrms;

    AppCtrlLink_IssParams_Init(pAppCtrlIssPrms);

    strncpy(pAppCtrlIssPrms->issSensorInfo.sensorName,
        pObj->chainsCfg->sensorName, ISS_SENSORS_MAX_NAME);
    pAppCtrlIssPrms->issSensorInfo.numCh = pObj->calibrationPrm.numCh;
    pAppCtrlIssPrms->issSensorInfo.ispOpMode = pObj->chainsCfg->ispOpMode;
    pAppCtrlIssPrms->issSensorInfo.simcopOpMode =
        ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;

    pAppCtrlIssPrms->issCaptLinkId = pUcObj->IssCaptureLinkID;
    pAppCtrlIssPrms->issIspLinkId = pUcObj->IssM2mIspLinkID;
    pAppCtrlIssPrms->issAewbLinkId = pUcObj->Alg_IssAewbLinkID;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_CREATE,
        &pObj->appCtrlIssPrms.issSensorInfo, sizeof(AppUtils_Obj), TRUE);

    memcpy(&pAppCtrlIssPrms->issCaptLinkPrms, &pUcObj->IssCapturePrm,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issIspLinkPrms, &pUcObj->IssM2mIspPrm,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issAewbLinkPrms, &pUcObj->Alg_IssAewbPrm,
        sizeof(AlgorithmLink_IssAewbCreateParams));

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_INIT_ISS_PARAMS, pAppCtrlIssPrms,
        sizeof(AppCtrl_IssParams), TRUE);

    memcpy(&pUcObj->IssCapturePrm, &pAppCtrlIssPrms->issCaptLinkPrms,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pUcObj->IssM2mIspPrm, &pAppCtrlIssPrms->issIspLinkPrms,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pUcObj->Alg_IssAewbPrm, &pAppCtrlIssPrms->issAewbLinkPrms,
        sizeof(AlgorithmLink_IssAewbCreateParams));

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    /* if SENSOR_SONY_IMX390_UB953_D3 sensor is used, set horizontal and vertical flip */
    if(strcmp(SENSOR_SONY_IMX390_UB953_D3, pObj->chainsCfg->sensorName) == 0)
    {
        for(ch = 0; ch < ISSM2MISP_LINK_MAX_CH; ch++)
        {
            pUcObj->IssM2mIspPrm.channelParams[ch].horizontalFlip = TRUE;
            pUcObj->IssM2mIspPrm.channelParams[ch].verticalFlip   = TRUE;
        }
    }

    pObj->calibrationPrm.captureOutWidth  =
        pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->calibrationPrm.captureOutHeight =
        pUcObj->IssCapturePrm.outParams[0U].height;

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

    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = FALSE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    /* Null link call back for M2M ISP frame buffer */
    pUcObj->Null_ispPrm.appCb = capFrameCb;
    pUcObj->Null_ispPrm.appCbArg = pObj;

    setSyncLinkParams(&pUcObj->SyncPrm, pObj->calibrationPrm.numCh, 0x0);

    /* SW MS link params */
    setDmaSwMsLinkParams(&pUcObj->Alg_DmaSwMsPrm, pObj->calibrationPrm.numCh,
        swMsWinWidth, swMsWinHeight, pObj->displayWidth, pObj->displayHeight);

    /* Graphics */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = pObj->displayWidth;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = pObj->displayHeight;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = TRUE;
    pUcObj->GrpxSrcPrm.srvCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->calibrationPrm.captureOutWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->calibrationPrm.captureOutHeight;
    if (pObj->is2mp == TRUE)
    {
        pUcObj->GrpxSrcPrm.is2mp = TRUE;
    }
    else
    {
        pUcObj->GrpxSrcPrm.is2mp = FALSE;
    }
    /* Garphics Display */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = 0;
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->displayWidth;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->displayHeight;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                        pObj->chainsCfg->displayType,
                        pObj->displayWidth,
                        pObj->displayHeight);
}
#endif

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
static Void saveCaptureFrames(chains_srvCalibration_DisplayAppObj *pObj)
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
                snprintf(fileName, sizeof(fileName), "%s_%d.YUV",
                        SRV_IMG_FILE_FRONT,pObj->yuvDumpCount);
                break;
            case 1:
                snprintf(fileName, sizeof(fileName), "%s_%d.YUV",
                        SRV_IMG_FILE_RIGHT,pObj->yuvDumpCount);
                break;
            case 2:
                snprintf(fileName, sizeof(fileName), "%s_%d.YUV",
                        SRV_IMG_FILE_BACK,pObj->yuvDumpCount);
                break;
            case 3:
                snprintf(fileName, sizeof(fileName), "%s_%d.YUV",
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

Void allocCalibUseCaseBufs(chains_srvCalibration_DisplayAppObj *pObj)
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
Void freeCalibUseCaseBufs(chains_srvCalibration_DisplayAppObj *pObj)
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
    char cmd[128U];

    snprintf(cmd, sizeof(cmd), "umount /%s",MMCSD_MOUNT_PT);

    /* Unmount the SD card */
    system(cmd);
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
static Void mountFatFs()
{
    char cmd[128U];

    snprintf(cmd, sizeof(cmd), "mount /dev/disk/by-path/platform-4809c000.mmc-part1 /%s",\
                                                            MMCSD_MOUNT_PT);

    /* Mount the SD card */
    system(cmd);
}

/**
 *******************************************************************************
 *
 * \brief   Write Buffers to the file
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void writeBuffer(chains_srvCalibration_DisplayAppObj *pObj)
{
    #define CALMAT_FILE_NAME    "/opt/vision_sdk/CALMAT.BIN"

    UInt32 value;

    /* Force create the calibration file */
    OSA_fileCreateFile(
            CALIBDATA_FILENAME,
            GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D + \
                                                GA_PERSPECTIVE_MATRIX_SIZE_2D,
            TRUE);

    /*
     *  Write the SGX GA LUT
     *  Write the LUT first and then the magic no
     */
    OSA_fileWriteFileOffset(
                        CALIBDATA_FILENAME,
                        (UInt8*)ChainsCommon_Osal_getVirtAddr(
                                    (UInt32)pObj->calibrationPrm.gpuLut3DBuf),
                        pObj->calibrationPrm.gpuLutSize,
                        GA_OUTPUT_LUT_FLASHMEM_OFFSET + \
                                GA_MAGIC_PATTERN_SIZE_IN_BYTES);

    value = GA_OUTPUT_LUT_MAGIC_SEQUENCE;
    OSA_fileWriteFileOffset(
                        CALIBDATA_FILENAME,
                        (UInt8*)&value,
                        GA_MAGIC_PATTERN_SIZE_IN_BYTES,
                        GA_OUTPUT_LUT_FLASHMEM_OFFSET);

    /*
     *  Write the Calibration Matrix
     *  Write 0x1 at the beginning so that the GA alg will identify it as
     *  user Cal Mat
     */
    value = 1U;
    OSA_fileWriteFileOffset(
                        CALIBDATA_FILENAME,
                        (UInt8*)&value,
                        4U,
                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET + \
                                    GA_MAGIC_PATTERN_SIZE_IN_BYTES);

    OSA_fileWriteFileOffset(
            CALIBDATA_FILENAME,
            (UInt8*)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            SRV_CALMAT_SIZE * SRV_NUM_CAMERAS,
            GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET + \
                                        GA_MAGIC_PATTERN_SIZE_IN_BYTES + 4U);

    value = GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE;
    OSA_fileWriteFileOffset(
                        CALIBDATA_FILENAME,
                        (UInt8*)&value,
                        GA_MAGIC_PATTERN_SIZE_IN_BYTES,
                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET);

    /*
     *  Write the Perspective Matrix for 2D SRV
     */
    OSA_fileWriteFileOffset(
            CALIBDATA_FILENAME,
            (UInt8*)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.persMatBuf),
            SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS,
            GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D + \
                                        GA_MAGIC_PATTERN_SIZE_IN_BYTES);

    value = GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE;
    OSA_fileWriteFileOffset(
                        CALIBDATA_FILENAME,
                        (UInt8*)&value,
                        GA_MAGIC_PATTERN_SIZE_IN_BYTES,
                        GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D);

    /* Write Calmat to CALMAT.BIN file in the /opt/vision_sdk */
    OSA_fileCreateFile(
            CALMAT_FILE_NAME,
            (128 + (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS)),
            TRUE);
    value = SRV_NUM_CAMERAS;
    OSA_fileWriteFileOffset(CALMAT_FILE_NAME,(Uint8*)&value,4,0);
    value = SRV_CALMAT_SIZE;
    OSA_fileWriteFileOffset(CALMAT_FILE_NAME,(Uint8*)&value,4,4);
    value = SRV_CALMAT_SIZE;
    OSA_fileWriteFileOffset(CALMAT_FILE_NAME,(Uint8*)&value,4,8);
    value = SRV_CALMAT_SIZE;
    OSA_fileWriteFileOffset(CALMAT_FILE_NAME,(Uint8*)&value,4,12);
    value = SRV_CALMAT_SIZE;
    OSA_fileWriteFileOffset(CALMAT_FILE_NAME,(Uint8*)&value,4,16);
    OSA_fileWriteFileOffset(
            CALMAT_FILE_NAME,
            (UInt8*)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
            SRV_CALMAT_SIZE * SRV_NUM_CAMERAS,
            128);
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
    char ch;
    Bool done = FALSE;
    Bool noSupport;
    pObj->calibrationPrm.thresholdMode = pObj->chainsCfg->calibrationParams.thresholdMode;
    pObj->calibrationPrm.windowMode = pObj->chainsCfg->calibrationParams.windowMode;
    pObj->calibrationPrm.Ransac = pObj->chainsCfg->calibrationParams.Ransac;
    pObj->calibrationPrm.PoseRansac = pObj->chainsCfg->calibrationParams.PoseRansac;
    pObj->calibrationPrm.SingleChartPose = pObj->chainsCfg->calibrationParams.SingleChartPose;

    if (pObj->calibrationPrm.thresholdMode == 0)
        Vps_printf("Threshold set to Default");
    else if (pObj->calibrationPrm.thresholdMode == 1)
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
    if (pObj->calibrationPrm.SingleChartPose == 0)
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

            pObj->calibrationPrm.calMatGenPrm3DSrv.displayWidth = \
                SRV_OUTPUT_WIDTH_TDA2X_2D;
            pObj->calibrationPrm.calMatGenPrm3DSrv.displayHeight = \
                SRV_OUTPUT_HEIGHT_TDA2X_2D;

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

            /* 2. Generate the GPU LUTs for all the views */
            Vps_printf("SRV_CALIB_UC: 2.Generating the GPU LUT ...\n");

            /*
             *  Write the GPU LUT into the file in Linux file system which is read
             *  by the 3D SRV use case
             */
            writeBuffer(pObj);
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

    do{
        Vps_printf(manualCalibMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                saveCaptureFrames(pObj);
                break;
            case '2':
                pObj->calibrationPrm.calMatGenPrm3DSrv.displayWidth = \
                                                    SRV_OUTPUT_WIDTH_TDA2X_2D;
                pObj->calibrationPrm.calMatGenPrm3DSrv.displayHeight = \
                                                    SRV_OUTPUT_HEIGHT_TDA2X_2D;
                Chain_Common_SRV_generateCalMat(&pObj->calibrationPrm,\
                                                        SRV_CALIB_TYPE_MANUAL);
                break;
            case '3':
                /*
                 *  Write the GPU LUT into the file in Linux file system which
                 *  is read by the 3D SRV use case
                 */
                writeBuffer(pObj);

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
Void defaultCalibration(chains_srvCalibration_DisplayAppObj *pObj)
{
    Int32 defaultCalMat[] = {
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

    Int32 defaultPersMat[] = {
        1526160, 42266, -107953821, -50364, 1784019,
        20033216, -2578, -34, 1048576, 1914092, 27589,
        -62553600, -46057, 1497130, 99178447, 134, 2170,
        1048576, 1579176, 26982, 21179348, -40733, 1828445,
        -12097588, 2717, 134, 1048576, 1957089, 60164,
        -84390275, -6674, 1034789, 113570362, 194, -3257,
        1048576};

    /* Cal Mat for 3D SRV */
    memcpy(
        (Ptr)ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
        defaultCalMat,
        (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

    ChainsCommon_Osal_cacheWb(
        ChainsCommon_Osal_getVirtAddr(
                    (UInt32)pObj->calibrationPrm.calMatGenPrm3DSrv.calMatBuf),
        (SRV_CALMAT_SIZE * SRV_NUM_CAMERAS));

    /* Pers Mat for 2D SRV */
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

    /*
     *  Write the GPU LUT into the file in Linux file system which is read
     *  by the 3D SRV use case
     */
    writeBuffer(pObj);

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
        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_Create(&pObj->ucVip, pObj);
            pObj->grpxSrcLinkId = pObj->ucVip.GrpxSrcLinkID;
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            /*  On TDA2EX
                4 Channels of 1.2 MP video could be received on 2 lanes, following
                changes would be required
                1. Set numLanesOnPhy0Csi2 to 2
                2. Set UB960 to stream on 2 lanes

                On J6 Entry
                There are only 2 lanes available, set numLanesOnPhy0Csi2 to 2
                UB960 is configured for 2 lanes for J6 E
             */
#ifdef TDA2EX_17X17
            pObj->numLanesOnPhy0Csi2 = 2U;
#else
            pObj->numLanesOnPhy0Csi2 = 4U;
#endif
            pObj->numCsi2Ch = pObj->chainsCfg->numLvdsCh;
            chains_srvCalibration_csi2Cal_Create(&pObj->ucCsi2Cal, pObj);
            pObj->grpxSrcLinkId = pObj->ucCsi2Cal.GrpxSrcLinkID;
            break;

        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_Create(&pObj->ucIss, pObj);
            pObj->grpxSrcLinkId = pObj->ucIss.GrpxSrcLinkID;
#endif

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
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    vidSensorPrm.isLVDSCaptMode = TRUE;
    vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_VIP:

        if(SRV_TDA2X_CAPTURE_WIDTH_2MP == pObj->calibrationPrm.captureOutWidth)
        {
            vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_IMX290ISP;
        }
        else
        {
            vidSensorPrm.captureSrcId = pObj->captureSrc;
        }
            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                        &vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

            chains_srvCalibration_vip_Start(&pObj->ucVip);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            /* UB964 Init */
            vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;

            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                        &vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

            chains_srvCalibration_csi2Cal_Start(&pObj->ucCsi2Cal);
            break;

        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            /* Sets Default ISP/SIMCOP Config from DCC */
            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                APP_CTRL_LINK_CMD_ISS_DEFAULT_CONFIG,
                &pObj->appCtrlIssPrms,
                sizeof(pObj->appCtrlIssPrms), TRUE);

            ChainsCommon_ReadAndParseDcc(&pObj->appCtrlIssPrms);

            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                APP_CTRL_LINK_CMD_SET_BOARD_MUXES,
                &pObj->appCtrlIssPrms.issSensorInfo,
                sizeof(pObj->appCtrlIssPrms.issSensorInfo), TRUE);

            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                APP_CTRL_LINK_CMD_ISS_SENSOR_START,
                &pObj->appCtrlIssPrms.issSensorInfo,
                sizeof(pObj->appCtrlIssPrms.issSensorInfo),
                TRUE);

            /* Start ISS use case */
            chains_srvCalibration_iss_Start(&pObj->ucIss);
#endif
            break;

    }

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
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    vidSensorPrm.isLVDSCaptMode = TRUE;
    vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    switch(pObj->captureIntf)
    {
        case CHAINS_CAPTURE_INTF_VIP:
        if(SRV_TDA2X_CAPTURE_WIDTH_2MP == pObj->calibrationPrm.captureOutWidth)
        {
            vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_IMX290ISP;
        }
        else
        {
            vidSensorPrm.captureSrcId = pObj->captureSrc;
        }
        chains_srvCalibration_vip_Stop(&pObj->ucVip);
            chains_srvCalibration_vip_Delete(&pObj->ucVip);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;
            chains_srvCalibration_csi2Cal_Stop(&pObj->ucCsi2Cal);
            chains_srvCalibration_csi2Cal_Delete(&pObj->ucCsi2Cal);
            break;
        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_Stop(&pObj->ucIss);
            chains_srvCalibration_iss_Delete(&pObj->ucIss);

            System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                APP_CTRL_LINK_CMD_ISS_SENSOR_STOP_AND_DELETE,
                &pObj->appCtrlIssPrms.issSensorInfo,
                sizeof(pObj->appCtrlIssPrms.issSensorInfo),
                TRUE);
#endif
            break;
    }

    ChainsCommon_StopDisplayCtrl();

    if ((CHAINS_CAPTURE_INTF_VIP == pObj->captureIntf) ||
        (CHAINS_CAPTURE_INTF_CSI2CAL == pObj->captureIntf))
    {
        System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                            APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                            &vidSensorPrm,
                            sizeof(VideoSensorCreateAndStartAppPrm),
                            TRUE);
    }

    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);

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
        case CHAINS_CAPTURE_INTF_VIP:
            chains_srvCalibration_vip_printStatistics(&pObj->ucVip);
            break;

        case CHAINS_CAPTURE_INTF_CSI2CAL:
            chains_srvCalibration_csi2Cal_printStatistics(&pObj->ucCsi2Cal);
            break;

        case CHAINS_CAPTURE_INTF_ISS:
#ifdef ISS_INCLUDE
            chains_srvCalibration_iss_printStatistics(&pObj->ucIss);
#endif
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
    char ch, chPrev = 0U;
    UInt32 done = FALSE;
    chains_srvCalibration_DisplayAppObj chainsObj;
    char chartFileName[128U];
    char cmd[128U];

    chainsObj.chainsCfg = chainsCfg;
    chainsObj.yuvDumpCount = 0U;
    chainsObj.calibrationPrm.saveFrame = FALSE;
    chainsObj.captureIntf = captureIntf;

    mountFatFs();

    /* Copy the lesn file from MMC/SD card to target file system */
    snprintf(cmd, sizeof(cmd), "cp /%s/TDA2X/LENS.BIN LENS.BIN",MMCSD_MOUNT_PT);
    system(cmd);

    /* Check if CHARTPOS.BIN file is present in TDA2X folder */
    snprintf(chartFileName, sizeof(chartFileName), "/%s/%s/%s",\
                            MMCSD_MOUNT_PT, SRV_DIR_2X, SRV_CHARTPOS_FILE);
    if(0 != access(chartFileName, F_OK))
    {
        Vps_printf(" CHAINS: -------------------------------------------------- \n");
        Vps_printf(" CHAINS: TDA2X Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Create TDA2X folder and copy the following files from\n");
        Vps_printf(" CHAINS: '/vision_sdk/tools/surround_vision_tools/Srv_LUTs':\n");
        Vps_printf(" CHAINS:     1. CHARTPOS.BIN  \n");
        Vps_printf(" CHAINS:     2. LENS.BIN  \n");
        Vps_printf(" CHAINS:     3. LENS_2D.BIN  \n");
        Vps_printf(" CHAINS: -------------------------------------------------- \n");

        return;
    }

    ch = 'a';
    Vps_printf(calibUseCaseResolutionMenu);
    ch = Chains_readChar();

    switch(ch)
    {
        default:
        case '1':
            chainsObj.captureSrc = chainsCfg->captureSrc;
            chainsObj.calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH;
            chainsObj.calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT;
            chainsObj.calibrationPrm.is2mp  = FALSE;
            chainsObj.is2mp  = FALSE;
            break;
        case '2':
            chainsObj.calibrationPrm.captureOutWidth  = SRV_TDA2X_CAPTURE_WIDTH_2MP;
            chainsObj.calibrationPrm.captureOutHeight = SRV_TDA2X_CAPTURE_HEIGHT_2MP;
            chainsObj.calibrationPrm.is2mp  = TRUE;
            chainsObj.is2mp  = TRUE;
            break;
    }

    done = FALSE;

    /* Create use case */
    createCalibUseCase(&chainsObj);

    /* Allocate Buffers */
    allocCalibUseCaseBufs(&chainsObj);

    /* Start the use case */
    startCalibUseCase(&chainsObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ENABLE_CSI_OUTPUT,
        NULL, 0, TRUE);

    ch = 'a';

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
                saveCaptureFrames(&chainsObj);
                break;

            case 'p':
            case 'P':
                printStatistics(&chainsObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    } while ((chPrev!='3') && (FALSE == done));

    /* Stop and Delete the use case */
    stopAndDeleteCalibUseCase(&chainsObj);

    /* Free the buffers */
    freeCalibUseCaseBufs(&chainsObj);

    Vps_printf("\n Restarting...\n");

    unmountFatFs();
}

