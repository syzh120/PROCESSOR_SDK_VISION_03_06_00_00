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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains_common.h>
#include "chains_vipSingleCameraDenseOpticalFlow_4eve_priv.h"
#include "chains_vipSingleCameraDenseOpticalFlow_1eve_priv.h"

/* Below #define's can be change during development */

#define ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR    (6)

/* Below #define's should NOT be changed */

#define CAPTURE_SENSOR_WIDTH         (1280)
#define CAPTURE_SENSOR_HEIGHT        (720)


#define DENSE_OPT_FLOW_WIDTH_ALIGN   (64)
#define DENSE_OPT_FLOW_HEIGHT_ALIGN  (32)

#define DENSE_OPT_FLOW_ROI_ENABLE    (0)

#define NUM_OF_EVE_MAX               (4)

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCameraDenseOpticalFlow_4eveObj ucObj_4eve;
    chains_vipSingleCameraDenseOpticalFlow_1eveObj ucObj_1eve;

    Chains_Ctrl *chainsCfg;

    UInt32                                  displayWidth;
    UInt32                                  displayHeight;

    UInt32                                  denseOptFlowWidth;
    UInt32                                  denseOptFlowHeight;
    UInt32                                  denseOptFlowFps;

    AlgorithmLink_RoiParams                 roiPrm[NUM_OF_EVE_MAX];

    UInt32                                  vectorToColorLutId;

    UInt32                                  numOfEve;

    AlgorithmLink_DenseOptFlowLKnumPyr      numPyramids;

    Bool                                    isLutSize_129x129;

} Chains_VipSingleCameraDenseOpticalFlowAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_vipSingleCameraDenseOpticalFlow_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm,
                                    Chains_DisplayType displayType,
                                    UInt32 startX,
                                    UInt32 startY,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    DisplayLink_displayID displayId
                                    )
{
    if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
      (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
    {
        pPrm->displayScanFormat = SYSTEM_SF_INTERLACED;
    }

    pPrm->rtParams.posX             = startX;
    pPrm->rtParams.posY             = startY;
    pPrm->rtParams.tarWidth         = displayWidth;
    pPrm->rtParams.tarHeight        = displayHeight;

    pPrm->displayId                 = displayId;
}

/**
 *******************************************************************************
 *
 * \brief   Set Graphics Create Parameters
 *
 *
 *          This function is used to set the Grtaphics Link params.
 *          It is called in Create function.
 *
 * \param   pPrm         [IN]    GrpxSrcLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetGrpxSrcPrms(
                                                 GrpxSrcLink_CreateParams *pPrm,
                                                 UInt32 displayWidth,
                                                 UInt32 displayHeight,
                                                 UInt32 lutId,
                                                 UInt32 fps)
{
    pPrm->grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
    pPrm->grpxBufInfo.height   = displayHeight;
    pPrm->grpxBufInfo.width    = displayWidth;

    pPrm->opticalFlowLayoutEnable = TRUE;
    pPrm->opticalFlowParams.lutId  = lutId;
    pPrm->opticalFlowParams.fps = fps;

    pPrm->statsDisplayEnable = TRUE;
}

/**
 *******************************************************************************
 *
 * \brief   Set ROI parameters
 *
 * \param   pPrm    [IN]    algorithm ROI parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetRoiPrms(
                    AlgorithmLink_RoiParams *pPrm,
                    UInt32 width,
                    UInt32 height,
                    UInt32 numOfEve)
{
    UInt32 i;
    UInt32 roiHeight;

    roiHeight = SystemUtils_floor(height/numOfEve, DENSE_OPT_FLOW_HEIGHT_ALIGN);

    for(i=0; i<numOfEve; i++)
    {
        pPrm[i].startX   = 0;
        pPrm[i].startY   = roiHeight*i;
        pPrm[i].width    = width;
        if(i == numOfEve -1)
        {
            /* last EVE in ROI */
            pPrm[i].height   = height - pPrm[i].startY;
        }
        else
        {
            pPrm[i].height   = roiHeight;
            pPrm[i].height += DENSE_OPT_FLOW_HEIGHT_ALIGN;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Dense Optical Flow parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetDenseOptFlowAlgPrms(
                       AlgorithmLink_DenseOptFlowCreateParams *pPrm,
                       UInt32 width,
                       UInt32 height,
                       UInt32 eveId,
                       AlgorithmLink_RoiParams *pRoi,
                       UInt32 numOfEve,
                       AlgorithmLink_DenseOptFlowLKnumPyr numPyramids)
{
    #if DENSE_OPT_FLOW_ROI_ENABLE
    pPrm->processPeriodicity = 1;
    pPrm->processStartFrame  = 0;
    pPrm->roiEnable          = TRUE;
    pPrm->roiParams.startX   = pRoi->startX;
    pPrm->roiParams.startY   = pRoi->startY;
    pPrm->roiParams.width    = pRoi->width;
    pPrm->roiParams.height   = pRoi->height;
    #else
    pPrm->processPeriodicity = numOfEve;
    pPrm->processStartFrame  = eveId;
    pPrm->roiParams.width    = width;
    pPrm->roiParams.height   = height;
    #endif
    pPrm->algEnable          = TRUE;
    pPrm->numOutBuf          = 2;

    pPrm->numPyramids     = numPyramids;
    pPrm->enableSmoothing = TRUE;
    pPrm->smoothingSize   = ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_5x5;
    pPrm->maxVectorSizeX  = 16;
    pPrm->maxVectorSizeY  = 16;
}

/**
 *******************************************************************************
 *
 * \brief   Set Vector to image algorithm parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetVectorToImageAlgPrms(
                       AlgorithmLink_VectorToImageCreateParams *pPrm,
                       UInt32 width,
                       UInt32 height,
                       AlgorithmLink_RoiParams *pRoi,
                       UInt32 lutId,
                       Bool isLutSize_129x129,
                       UInt32 numOfEve)
{
    pPrm->maxWidth  = width;
    pPrm->maxHeight = height;
    pPrm->numOutputFrames = 4;
    pPrm->lutId   = lutId;
    pPrm->isLutSize_129x129   = isLutSize_129x129;
    pPrm->dataFormat = SYSTEM_DF_YUV422I_YUYV;

    #if DENSE_OPT_FLOW_ROI_ENABLE
    {
        UInt32 i;

        pPrm->numRoi = numOfEve;
        pPrm->roiEnable = TRUE;
        for(i=0; i<numOfEve; i++)
        {
            pPrm->roiParams[i].startX   = pRoi[i].startX;
            pPrm->roiParams[i].startY   = pRoi[i].startY;
            pPrm->roiParams[i].width    = pRoi[i].width;
            pPrm->roiParams[i].height   = pRoi[i].height;
        }
    }
    #endif
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          chains_vipSingleCameraDenseOpticalFlow_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 *          Scale each CH to 1/2x size
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 outWidth,
                    UInt32 outHeight,
                    UInt32 srcWidth,
                    UInt32 srcHeight,
                    System_VideoDataFormat dataFormat
                    )
{
    pPrm->enableOut[0] = TRUE;

    pPrm->chParams[0].outParams[0].width = SystemUtils_floor(outWidth, 4);
    pPrm->chParams[0].outParams[0].height = SystemUtils_floor(outHeight, 2);

    pPrm->chParams[0].scCropCfg.cropStartX = 0;
    pPrm->chParams[0].scCropCfg.cropStartY = 0;
    pPrm->chParams[0].scCropCfg.cropWidth  = srcWidth;
    pPrm->chParams[0].scCropCfg.cropHeight = srcHeight;

    pPrm->chParams[0].outParams[0].dataFormat
        = dataFormat;

    pPrm->chParams[0].outParams[0].numBufsPerCh = 4;
}

/**
 *******************************************************************************
 *
 * \brief   Sets use-case specific parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetAppPrmsCommon(
                                    Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj,
                                    CaptureLink_CreateParams *pCapturePrm,
                                    AlgorithmLink_DenseOptFlowCreateParams *pAlg_DenseOptFlow_1Prm,
                                    AlgorithmLink_DenseOptFlowCreateParams *pAlg_DenseOptFlow_2Prm,
                                    AlgorithmLink_DenseOptFlowCreateParams *pAlg_DenseOptFlow_3Prm,
                                    AlgorithmLink_DenseOptFlowCreateParams *pAlg_DenseOptFlow_4Prm,
                                    AlgorithmLink_VectorToImageCreateParams *pAlg_VectorToImagePrm,
                                    VpeLink_CreateParams *pVPE_capturePrm,
                                    GrpxSrcLink_CreateParams *pGrpxSrcPrm,
                                    DisplayLink_CreateParams *pDisplay_VideoDofPrm,
                                    DisplayLink_CreateParams *pDisplay_VideoOriginalPrm,
                                    DisplayLink_CreateParams *pDisplay_GrpxPrm
                                    )
{
    if((pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV10635) || (pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_DM388))
    {
        pObj->denseOptFlowWidth  = 1280;
        pObj->denseOptFlowHeight = 720;
        pObj->denseOptFlowFps    = 30;
    }
    else if(pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P)
    {
        pObj->denseOptFlowWidth  = 1280;
        pObj->denseOptFlowHeight = 720;
        pObj->denseOptFlowFps    = 60;

        if(pAlg_DenseOptFlow_2Prm==NULL
            &&
           pAlg_DenseOptFlow_2Prm==NULL
            &&
           pAlg_DenseOptFlow_2Prm==NULL
            )
        {
            pObj->denseOptFlowWidth  = 1280;
            pObj->denseOptFlowHeight =  720;
            pObj->denseOptFlowFps    =   30;
        }
    }
    else if(pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P)
    {
        pObj->denseOptFlowWidth  = 1920;
        pObj->denseOptFlowHeight = 1080;
        pObj->denseOptFlowFps    = 60;

        if(pObj->numPyramids == ALGLINK_DENSEOPTFLOW_LKNUMPYR_2)
        {
            pObj->denseOptFlowWidth  = 1280;
            pObj->denseOptFlowHeight = 720;
            pObj->denseOptFlowFps    = 60;
        }

        if(pAlg_DenseOptFlow_2Prm==NULL
            &&
           pAlg_DenseOptFlow_2Prm==NULL
            &&
           pAlg_DenseOptFlow_2Prm==NULL
            )
        {
            pObj->denseOptFlowWidth  = 1280;
            pObj->denseOptFlowHeight =  720;
            pObj->denseOptFlowFps    =   30;
        }

    }

    /* align to algorithm required W x H */
    pObj->denseOptFlowWidth
        = SystemUtils_floor(pObj->denseOptFlowWidth,
            DENSE_OPT_FLOW_WIDTH_ALIGN);

    pObj->denseOptFlowHeight
        = SystemUtils_floor(pObj->denseOptFlowHeight,
            DENSE_OPT_FLOW_HEIGHT_ALIGN*pObj->numOfEve);

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(pCapturePrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->denseOptFlowWidth,
            pObj->denseOptFlowHeight,
            pObj->chainsCfg->captureSrc
            );

    pCapturePrm->vipInst[0].numBufs = 5;

    chains_vipSingleCameraDenseOpticalFlow_SetRoiPrms(pObj->roiPrm,
                                    pObj->denseOptFlowWidth,
                                    pObj->denseOptFlowHeight,
                                    pObj->numOfEve);

    if(pAlg_DenseOptFlow_1Prm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetDenseOptFlowAlgPrms(
                                    pAlg_DenseOptFlow_1Prm,
                                    pObj->denseOptFlowWidth,
                                    pObj->denseOptFlowHeight,
                                    0,
                                    &pObj->roiPrm[0],
                                    pObj->numOfEve,
                                    pObj->numPyramids);
    }
    if(pAlg_DenseOptFlow_2Prm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetDenseOptFlowAlgPrms(
                                    pAlg_DenseOptFlow_2Prm,
                                    pObj->denseOptFlowWidth,
                                    pObj->denseOptFlowHeight,
                                    1,
                                    &pObj->roiPrm[1],
                                    pObj->numOfEve,
                                    pObj->numPyramids);
    }
    if(pAlg_DenseOptFlow_3Prm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetDenseOptFlowAlgPrms(
                                    pAlg_DenseOptFlow_3Prm,
                                    pObj->denseOptFlowWidth,
                                    pObj->denseOptFlowHeight,
                                    2,
                                    &pObj->roiPrm[2],
                                    pObj->numOfEve,
                                    pObj->numPyramids);
    }
    if(pAlg_DenseOptFlow_4Prm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetDenseOptFlowAlgPrms(
                                    pAlg_DenseOptFlow_4Prm,
                                    pObj->denseOptFlowWidth,
                                    pObj->denseOptFlowHeight,
                                    3,
                                    &pObj->roiPrm[3],
                                    pObj->numOfEve,
                                    pObj->numPyramids);
    }

    chains_vipSingleCameraDenseOpticalFlow_SetVectorToImageAlgPrms(
                                pAlg_VectorToImagePrm,
                                pObj->denseOptFlowWidth,
                                pObj->denseOptFlowHeight,
                                pObj->roiPrm,
                                pObj->vectorToColorLutId,
                                pObj->isLutSize_129x129,
                                pObj->numOfEve );

    if(pVPE_capturePrm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetVpePrm(pVPE_capturePrm,
         (pObj->displayWidth/ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR),
         (pObj->displayHeight/ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR),
         pObj->denseOptFlowWidth,
         pObj->denseOptFlowHeight,
         SYSTEM_DF_YUV422I_UYVY);
    }

    chains_vipSingleCameraDenseOpticalFlow_SetDisplayPrms(pDisplay_VideoDofPrm,
                                        pObj->chainsCfg->displayType,
                                        0,
                                        0,
                                        pObj->displayWidth,
                                        pObj->displayHeight,
                                        DISPLAY_LINK_INST_DSS_VID1
                                        );

    if(pDisplay_VideoOriginalPrm)
    {
        chains_vipSingleCameraDenseOpticalFlow_SetDisplayPrms(pDisplay_VideoOriginalPrm,
                  pObj->chainsCfg->displayType,
                  pObj->displayWidth - pObj->displayWidth/ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR - 20,
                  20,
                  pObj->displayWidth/ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR,
                  pObj->displayHeight/ORIGINAL_VIDEO_WIN_SCALE_DOWN_FACTOR,
                  DISPLAY_LINK_INST_DSS_VID2
              );
    }

    chains_vipSingleCameraDenseOpticalFlow_SetGrpxSrcPrms(pGrpxSrcPrm,
                                           pObj->displayWidth,
                                           pObj->displayHeight,
                                           pObj->vectorToColorLutId,
                                           pObj->denseOptFlowFps
                                          );

    chains_vipSingleCameraDenseOpticalFlow_SetDisplayPrms(pDisplay_GrpxPrm,
                                        pObj->chainsCfg->displayType,
                                        0,
                                        0,
                                        pObj->displayWidth,
                                        pObj->displayHeight,
                                        DISPLAY_LINK_INST_DSS_GFX1
                                         );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

}

/**
 *******************************************************************************
 *
 * \brief   Sets use-case specific parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_4eve_SetAppPrms(
                                    chains_vipSingleCameraDenseOpticalFlow_4eveObj *pUcObj,
                                    Void *appObj)
{
    Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj
        = (Chains_VipSingleCameraDenseOpticalFlowAppObj*)appObj;

    chains_vipSingleCameraDenseOpticalFlow_SetAppPrmsCommon(
        pObj,
        &pUcObj->CapturePrm,
        &pUcObj->Alg_DenseOptFlow_1Prm,
        &pUcObj->Alg_DenseOptFlow_2Prm,
        &pUcObj->Alg_DenseOptFlow_3Prm,
        &pUcObj->Alg_DenseOptFlow_4Prm,
        &pUcObj->Alg_VectorToImagePrm,
        &pUcObj->VPE_capturePrm,
        &pUcObj->GrpxSrcPrm,
        &pUcObj->Display_VideoDofPrm,
        &pUcObj->Display_VideoOriginalPrm,
        &pUcObj->Display_GrpxPrm
    );

    pUcObj->CapturePrm.vipInst[0].numBufs = 12;

    if(pObj->chainsCfg->captureSrc==CHAINS_CAPTURE_SRC_HDMI_720P
        ||
       pObj->chainsCfg->captureSrc==CHAINS_CAPTURE_SRC_HDMI_1080P
    )
    {
        /* dont skip alternate frames, keep it 60fps  */
        pUcObj->CapturePrm.vipInst[0].outParams[0].frameSkipMask
            = 0;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Sets use-case specific parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_1eve_SetAppPrms(
                                    chains_vipSingleCameraDenseOpticalFlow_1eveObj *pUcObj,
                                    Void *appObj)
{
    Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj
        = (Chains_VipSingleCameraDenseOpticalFlowAppObj*)appObj;

    chains_vipSingleCameraDenseOpticalFlow_SetAppPrmsCommon(
        pObj,
        &pUcObj->CapturePrm,
        &pUcObj->Alg_DenseOptFlow_1Prm,
        NULL,
        NULL,
        NULL,
        &pUcObj->Alg_VectorToImagePrm,
        NULL,
        &pUcObj->GrpxSrcPrm,
        &pUcObj->Display_VideoDofPrm,
        NULL,
        &pUcObj->Display_GrpxPrm
    );
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_VipSingleCameraDenseOpticalFlowObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_StartApp(Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->denseOptFlowWidth,
        pObj->denseOptFlowHeight
        );

    if(pObj->numOfEve==4)
    {

        chains_vipSingleCameraDenseOpticalFlow_4eve_Start(&pObj->ucObj_4eve);
    }
    else
    {
        chains_vipSingleCameraDenseOpticalFlow_1eve_Start(&pObj->ucObj_1eve);
    }

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_VipSingleCameraDenseOpticalFlowObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_StopAndDeleteApp(Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj)
{
    if(pObj->numOfEve==4)
    {
        chains_vipSingleCameraDenseOpticalFlow_4eve_Stop(&pObj->ucObj_4eve);
        chains_vipSingleCameraDenseOpticalFlow_4eve_Delete(&pObj->ucObj_4eve);
    }
    else
    {
        chains_vipSingleCameraDenseOpticalFlow_1eve_Stop(&pObj->ucObj_1eve);
        chains_vipSingleCameraDenseOpticalFlow_1eve_Delete(&pObj->ucObj_1eve);
    }

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gRunTimeNumPyramids[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Alg Settings        "
    "\r\n ===================="
    "\r\n "
    "\r\n 1: Use Alg with One Pyramid Mode"
    "\r\n 2: Use Alg with Two Pyramid Mode"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};
/**
 *******************************************************************************
 *
 * \brief   Function to set optical flow settings.
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraDenseOpticalFlow_SetNumOfPyramid(Chains_VipSingleCameraDenseOpticalFlowAppObj *pObj, Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool selectDone;

    selectDone = FALSE;

    do
    {
    if(chainsCfg->numPyramids == 0)
    {
            /* User I/P required for example usecase,select alg with One/Two Pyramid Mode in Dense Optical Flow*/
            Vps_printf(gRunTimeNumPyramids);
            ch = Chains_readChar();
    }
    else if(chainsCfg->numPyramids == 1)
    {
            /* Voiding user I/P for testsuite and select alg with ONE Pyramid Mode in Dense Optical Flow */
        ch = '1';
    }
    else
    {
            /* Voiding user I/P for testsuite and select alg with TWO Pyramid Mode in Dense Optical Flow */
        ch = '2';
    }

        switch(ch)
        {
            case '1':
                pObj->numPyramids = ALGLINK_DENSEOPTFLOW_LKNUMPYR_1;
                pObj->isLutSize_129x129 = TRUE;
                selectDone = TRUE;
                break;
            case '2':
                pObj->numPyramids = ALGLINK_DENSEOPTFLOW_LKNUMPYR_2;
                pObj->isLutSize_129x129 = FALSE;
                selectDone = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }while(selectDone == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
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
Void Chains_vipSingleCameraDenseOpticalFlow(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraDenseOpticalFlowAppObj chainsObj;
    UInt32 i;
    UInt32 exitUsecase;
    
    chainsObj.numOfEve = 0; /* KW error fix */

    exitUsecase = FALSE;

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        chainsObj.numOfEve = 4;
    }
    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        chainsObj.numOfEve = 1;
    }

    chainsObj.vectorToColorLutId = 1;
    chainsObj.numPyramids = ALGLINK_DENSEOPTFLOW_LKNUMPYR_1;
    chainsObj.isLutSize_129x129 = TRUE;

    for(i=0; i< chainsObj.numOfEve; i++)
    {
        if(System_isProcEnabled(SYSTEM_PROC_EVE1+i)==FALSE)
        {
            Vps_printf(" \n");
            Vps_printf(" CHAINS: ERROR: %s, required for this use-ucase is "
                       "NOT ENABLED in this executable BUILD. !!!\n",
                System_getProcName(SYSTEM_PROC_EVE1)
                );
            Vps_printf(" \n");
            exitUsecase = TRUE;
        }
    }

    if(exitUsecase)
    {
        return;
    }

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCameraDenseOpticalFlow_SetNumOfPyramid(&chainsObj,chainsCfg);

    if(chainsObj.numOfEve==4)
    {
        chains_vipSingleCameraDenseOpticalFlow_4eve_Create(
                    &chainsObj.ucObj_4eve, &chainsObj
                );
    }
    else
    {
        chains_vipSingleCameraDenseOpticalFlow_1eve_Create(
                    &chainsObj.ucObj_1eve, &chainsObj
                );
    }

    chains_vipSingleCameraDenseOpticalFlow_StartApp(&chainsObj);

    while(!done)
    {
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                if(chainsObj.numOfEve==4)
                {
                    chains_vipSingleCameraDenseOpticalFlow_4eve_printStatistics(
                                        &chainsObj.ucObj_4eve
                                    );
                }
                else
                {
                    chains_vipSingleCameraDenseOpticalFlow_1eve_printStatistics(
                                        &chainsObj.ucObj_1eve
                                    );
                }
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCameraDenseOpticalFlow_StopAndDeleteApp(&chainsObj);
}

