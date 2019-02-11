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
#include "chains_vipSingleCameraObjectDetect2Tda3xx_priv.h"
#include <src/include/chains_common.h>

/* Uncomment below to enable 1MP processing mode on object detect */
#define ENABLE_1MP_MODE

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

#ifdef ENABLE_1MP_MODE
#define FEATUREPLANE_ALG_WIDTH    (1280)
#define FEATUREPLANE_ALG_HEIGHT   ( 720)
#else
#define FEATUREPLANE_ALG_WIDTH    (640)
#define FEATUREPLANE_ALG_HEIGHT   (360)
#endif


#define ENABLE_ROI_PERCENTAGE     (32)
#define NUM_SCALES                (14)
#define NUM_STEPS                 (4)

#define FRAMES_DUMP_TO_MEMORY_ENABLE    (0)
#define FRAMES_DUMP_TO_MEMORY_ADDR      (0xA1000000)
#define FRAMES_DUMP_TO_MEMORY_SIZE      (496*MB)

static char usecase_menu[] = {
    "\r\n "
    "\r\n Select use-case options,"
    "\r\n ------------------------"
    "\r\n 1: Enable Pedestrain Detect (PD)"
    "\r\n 2: Enable Traffic Sign Regonition (TSR)"
    "\r\n 3: Enable Vehicle Detect (VD)"
    "\r\n 4: Enable PD+TSR+VD"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraObjectDetectObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCameraObjectDetect2Tda3xxObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;
    UInt32  startX;
    UInt32  startY;

    Bool    enablePD;
    Bool    enableTSR;
    Bool    enableVD;

    Chains_Ctrl *chainsCfg;

} Chains_VipSingleCameraObjectDetectAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set PD draw parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectDrawPrms(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_ObjectDrawCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->imgFrameStartX   = 0;
    pPrm->imgFrameStartY   = 0;
    pPrm->imgFrameWidth    = width;
    pPrm->imgFrameHeight   = height;
    pPrm->numOutBuffers    = 3;
    pPrm->objectRectThickness  = 1;
    pPrm->objectTsrDrawTrafficSigns = TRUE;
}


/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Compute Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetImagePreProcessAlgPrms(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_ImagePreProcessCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->imgFrameStartX = pObj->startX;
    pPrm->imgFrameStartY = pObj->startY;
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
    pPrm->imgFrameStartX   = pObj->startX;
    pPrm->imgFrameStartY   = pObj->startY;
    pPrm->numOutBuffers  = 3;
}

/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Compute Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetImgPyramidAlgPrms(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_ImgPyramidCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->numOutBuffers  = 3;

    #ifdef ENABLE_1MP_MODE
    pPrm->enableRoi     = TRUE;
    #else
    pPrm->enableRoi     = FALSE;
    #endif
    pPrm->roiWidth      = width;
    pPrm->roiHeight     = SystemUtils_align( (height*ENABLE_ROI_PERCENTAGE)/100, 2);
    pPrm->roiStartX     = 0;
    pPrm->roiStartY     = SystemUtils_align( (height - pPrm->roiHeight)/2, 2);
    pPrm->numScales     = NUM_SCALES;
    pPrm->scaleSteps    = NUM_STEPS;

#ifdef TDA3XX_BUILD
    pPrm->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_ISS;
#else
    pPrm->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_VPE;
#endif

}

/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Compute Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetFPComputeAlgPrms(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_FPComputeCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
    pPrm->numOutBuffers  = 3;

}

/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Classify Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectDetectPrm(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_ObjectDetectionCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height
                   )
{
    pPrm->numOutBuffers  = 3;
    pPrm->enablePD       = pObj->enablePD;
    pPrm->enableTSR      = pObj->enableTSR;
    pPrm->enableVD       = pObj->enableVD;
    pPrm->imgFrameWidth    = width;
    pPrm->imgFrameHeight   = height;
}

/**
 *******************************************************************************
 *
 * \brief   Set Feature Plane Classify Alg parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectClassificationPrm(
                   Chains_VipSingleCameraObjectDetectAppObj *pObj,
                   AlgorithmLink_ObjectClassificationCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height
                   )
{
    pPrm->numOutBuffers    = 3;
    pPrm->imgFrameWidth    = width;
    pPrm->imgFrameHeight   = height;
    pPrm->numScales        = NUM_SCALES;
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Link Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipObjectDetection_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetSyncPrm(SyncLink_CreateParams *pPrm)

{
    pPrm->syncDelta = 1;
    pPrm->syncThreshold = 0xFFFF;
}

/**
 *******************************************************************************
 *
 * \brief   Set frame-rate to a fixed value instead of capture frame-rate
 *
 *******************************************************************************
 */
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetFrameRatePrms(
                    Chains_VipSingleCameraObjectDetectAppObj *pObj)
{
    IpcLink_FrameRateParams frameRatePrms;

    frameRatePrms.chNum = 0;

    frameRatePrms.inputFrameRate = 30;
    frameRatePrms.outputFrameRate = 30;

    System_linkControl(
        pObj->ucObj.IPCOut_IPU1_0_EVE1_0LinkID,
        IPC_OUT_LINK_CMD_SET_FRAME_RATE,
        &frameRatePrms,
        sizeof(frameRatePrms),
        TRUE
        );
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetAppPrms(chains_vipSingleCameraObjectDetect2Tda3xxObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraObjectDetectAppObj *pObj
        = (Chains_VipSingleCameraObjectDetectAppObj*)appObj;

    #ifdef ENABLE_1MP_MODE
    if(pObj->chainsCfg->captureSrc==CHAINS_CAPTURE_SRC_HDMI_1080P)
    {
        pObj->captureOutWidth = 1920;
        pObj->captureOutHeight = 1080;
        pObj->startX = 320;
        pObj->startY = 180;
    }
    else
    {
        pObj->captureOutWidth = 1280;
        pObj->captureOutHeight = 720;
        pObj->startX = 0;
        pObj->startY = 0;
    }
    #else
    pObj->startX = 0;
    pObj->startY = 0;
    pObj->captureOutWidth  = FEATUREPLANE_ALG_WIDTH;
    pObj->captureOutHeight = FEATUREPLANE_ALG_HEIGHT;
    #endif

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(&(pUcObj->CapturePrm),
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    /* skip alternate frame to make it 15fps output for sensor and 30fps for HDMI */
    pObj->ucObj.CapturePrm.vipInst[0].outParams[0].frameSkipMask
        = 0x2AAAAAAA;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );


    ChainsCommon_SetDisplayPrms(&pUcObj->Display_algPrm,
                                               &pUcObj->Display_GrpxPrm,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                                );

    /* 1:1 window and center it */
    pUcObj->Display_algPrm.rtParams.tarWidth = FEATUREPLANE_ALG_WIDTH;
    pUcObj->Display_algPrm.rtParams.tarHeight = FEATUREPLANE_ALG_HEIGHT;
    pUcObj->Display_algPrm.rtParams.posX = (pObj->displayWidth - pUcObj->Display_algPrm.rtParams.tarWidth)/2;
    pUcObj->Display_algPrm.rtParams.posY = (pObj->displayHeight - pUcObj->Display_algPrm.rtParams.tarHeight)/2;

    chains_vipSingleCameraObjectDetect2Tda3xx_SetImagePreProcessAlgPrms(
                    pObj,
                    &pUcObj->Alg_ImagePreProcessPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetImgPyramidAlgPrms(
                    pObj,
                    &pUcObj->Alg_ImgPyramidPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetFPComputeAlgPrms(
                    pObj,
                    &pUcObj->Alg_FPComputePrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );


    chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectDetectPrm(
                    pObj,
                    &pUcObj->Alg_ObjectDetectionPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectClassificationPrm(
                    pObj,
                    &pUcObj->Alg_ObjectClassificationPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetSyncPrm(
                    &pUcObj->Sync_objectDetectPrm
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetSyncPrm(
                    &pUcObj->Sync_algPrm
                );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetObjectDrawPrms(
                    pObj,
                    &pUcObj->Alg_ObjectDrawPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
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
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_VipSingleCameraObjectDetectAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_StartApp(Chains_VipSingleCameraObjectDetectAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCameraObjectDetect2Tda3xx_SetFrameRatePrms(pObj);

    chains_vipSingleCameraObjectDetect2Tda3xx_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_VipSingleCameraObjectDetectAppObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraObjectDetect2Tda3xx_StopAndDeleteApp(Chains_VipSingleCameraObjectDetectAppObj *pObj)
{
    chains_vipSingleCameraObjectDetect2Tda3xx_Stop(&pObj->ucObj);
    chains_vipSingleCameraObjectDetect2Tda3xx_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_SelectOption(Chains_VipSingleCameraObjectDetectAppObj *pObj)
{
    Bool done = FALSE;
    char ch;

    while(!done)
    {
        Vps_printf(usecase_menu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                pObj->enablePD = TRUE;
                pObj->enableTSR = FALSE;
                pObj->enableVD = FALSE;
                done = TRUE;
                break;
            case '2':
                pObj->enablePD = FALSE;
                pObj->enableTSR = TRUE;
                pObj->enableVD = FALSE;
                done = TRUE;
                break;
            case '3':
                pObj->enablePD = FALSE;
                pObj->enableTSR = FALSE;
                pObj->enableVD = TRUE;
                done = TRUE;
                break;
            case '4':
                pObj->enablePD = TRUE;
                pObj->enableTSR = TRUE;
                pObj->enableVD = TRUE;
                done = TRUE;
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
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
Void Chains_vipSingleCameraObjectDetect2Tda3xx(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done  = FALSE;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Chains_VipSingleCameraObjectDetectAppObj chainsObj;
    chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj;

    AlgorithmLink_ImgPyramidImgPyramidInfoControlParams imgPyramidCtrlPrms;

    chainsObj.enablePD = TRUE;
    chainsObj.enableTSR = TRUE;
    chainsObj.enableVD = TRUE;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCameraObjectDetect2Tda3xx_SelectOption(&chainsObj);

    chains_vipSingleCameraObjectDetect2Tda3xx_Create(&chainsObj.ucObj, &chainsObj);

    /* Place for IOCTL on Img pyramid info and FP Compute */
    pObj = &chainsObj.ucObj;

    imgPyramidCtrlPrms.baseClassControl.controlCmd =
        ALGORITHM_LINK_IMAGE_PYRAMID_CMD_GET_PYRAMID_INFO;
    imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

    /* get results */
    status = System_linkControl(
        pObj->Alg_ImgPyramidLinkID,
        ALGORITHM_LINK_CMD_CONFIG,
        &imgPyramidCtrlPrms,
        sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
        TRUE);

    imgPyramidCtrlPrms.baseClassControl.controlCmd =
        ALGORITHM_LINK_FPCOMPUTE_CMD_CREATE_ALG;
    imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

    /* set image pyramid info */
    status = System_linkControl(
        pObj->Alg_FPComputeLinkID,
        ALGORITHM_LINK_CMD_CONFIG,
        &imgPyramidCtrlPrms,
        sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
        TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    imgPyramidCtrlPrms.baseClassControl.controlCmd =
        ALGORITHM_LINK_OBJECTCLASSIFICATION_CMD_CREATE_ALG;
    imgPyramidCtrlPrms.baseClassControl.size = sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams);

    /* set image pyramid info */
    status = System_linkControl(
        pObj->Alg_ObjectClassificationLinkID,
        ALGORITHM_LINK_CMD_CONFIG,
        &imgPyramidCtrlPrms,
        sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams),
        TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    chains_vipSingleCameraObjectDetect2Tda3xx_StartApp(&chainsObj);

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
                chains_vipSingleCameraObjectDetect2Tda3xx_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCameraObjectDetect2Tda3xx_StopAndDeleteApp(&chainsObj);

}

