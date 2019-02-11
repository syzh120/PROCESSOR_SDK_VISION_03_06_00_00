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
#include "chains_vipSingleCameraLaneDetect_priv.h"
#include <src/include/chains_common.h>


#define CAPTURE_FRAME_WIDTH        (1920)
#define CAPTURE_FRAME_HEIGHT       (1080)

#define CAPTURE_IN_WIDTH           (1280)
#define CAPTURE_IN_HEIGHT          (720)

#define CAPTURE_FRAME_STARTX       (320)
#define CAPTURE_FRAME_STARTY       (180)

#define LD_NUM_OUT_BUF             (8)

#define IMG_PMD_ROI_PERCENTAGE     (32)
#define IMG_PMD_SCALE_STEPS        (4)
#define IMG_PMD_NUM_SCALES         (14)


#define LD_ALG_WIDTH               (640)
#define LD_ALG_HEIGHT              (480)

/**
 *******************************************************************************
 *
 *  \brief  Link Object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCameraLaneDetectObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

} Chains_VipSingleCameraLaneDetectAppObj;



Void chains_vipSingleCameraLaneDetect_SetLaneDetectPrm(
            AlgorithmLink_ImagePreProcessCreateParams  *pImgPreProcPrm,
            AlgorithmLink_ImgPyramidCreateParams *pImgPmd,
            AlgorithmLink_LaneDetectCreateParams *pLdPrm,
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm,
            UInt32 inStartX,
            UInt32 inStartY,
            UInt32 inWidth,
            UInt32 inHeight)
{
    pImgPreProcPrm->imgFrameStartX = inStartX;
    pImgPreProcPrm->imgFrameStartY = inStartY;
    pImgPreProcPrm->imgFrameWidth  = inWidth;
    pImgPreProcPrm->imgFrameHeight = inHeight;
    pImgPreProcPrm->numOutBuffers  = 8;

#ifdef TDA3XX_BUILD
    pImgPmd->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_ISS;
#else
    pImgPmd->rszModule      = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_VPE;
#endif
    pImgPmd->numOutBuffers  = 8;
    pImgPmd->enableRoi      = TRUE;
    pImgPmd->roiWidth       = inWidth;
    pImgPmd->roiHeight      = ((inHeight*IMG_PMD_ROI_PERCENTAGE)/100) & (~1);
    pImgPmd->roiStartX      = 0;
    pImgPmd->roiStartY      = ((inHeight - pImgPmd->roiHeight)/2) & (~1);
    pImgPmd->numScales      = IMG_PMD_NUM_SCALES;
    pImgPmd->scaleSteps     = IMG_PMD_SCALE_STEPS;

    pLdPrm->imgFrameStartX = 0;
    pLdPrm->imgFrameStartY = 0;
    pLdPrm->imgFrameWidth  = LD_ALG_WIDTH;
    pLdPrm->imgFrameHeight = LD_ALG_HEIGHT;

    pLdPrm->roiStartX    = 190U;
    pLdPrm->roiStartY    = 210U;
    pLdPrm->roiWidth     = 222U;
    pLdPrm->roiHeight    = 70U;

    pLdPrm->numOutBuffers  = 8;

    pLdPrm->isImgPmdInputType = TRUE;
    pLdPrm->imgPmdScaleIdx    = pImgPmd->scaleSteps;

    pOdDrawPrm->imgFrameStartX  = inStartX;
    pOdDrawPrm->imgFrameStartY  = inStartY;
    pOdDrawPrm->imgFrameWidth   = inWidth;
    pOdDrawPrm->imgFrameHeight  = inHeight;

    pOdDrawPrm->numOutBuffers   = 8;

    pOdDrawPrm->laneThickness = 2;
    pOdDrawPrm->laneDrawLines = FALSE;
    pOdDrawPrm->laneScaleX    = 2.0;
    pOdDrawPrm->laneScaleY    = 2.0;
    pOdDrawPrm->laneRoiStartY = pLdPrm->roiStartY;
    pOdDrawPrm->laneRoiHeight = pLdPrm->roiHeight;
    pOdDrawPrm->laneRoiWidth  = pLdPrm->roiWidth;

    pOdDrawPrm->numDrawAlg = 1;
    pOdDrawPrm->drawAlgId[0] = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_LD;


}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Link Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraLaneDetect_SetSyncPrm(SyncLink_CreateParams *pPrm)

{
    pPrm->syncDelta = 1;
    pPrm->syncThreshold = 0xFFFF;
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
Void chains_vipSingleCameraLaneDetect_SetAppPrms(chains_vipSingleCameraLaneDetectObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraLaneDetectAppObj *pObj
        = (Chains_VipSingleCameraLaneDetectAppObj*)appObj;
    UInt32 startX, startY;

    startX = CAPTURE_FRAME_STARTX;
    startY = CAPTURE_FRAME_STARTY;
    pObj->captureOutWidth  = CAPTURE_FRAME_WIDTH;
    pObj->captureOutHeight = CAPTURE_FRAME_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(&pUcObj->CapturePrm,
            CAPTURE_FRAME_WIDTH,
            CAPTURE_FRAME_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    chains_vipSingleCameraLaneDetect_SetSyncPrm(
                    &pUcObj->Sync_algPrm
                );

    chains_vipSingleCameraLaneDetect_SetLaneDetectPrm(
        &pUcObj->Alg_ImagePreProcessPrm,
        &pUcObj->Alg_ImgPyramidPrm,
        &pUcObj->Alg_LaneDetectPrm,
        &pUcObj->Alg_ObjectDrawPrm,
        startX,
        startY,
        CAPTURE_IN_WIDTH,
        CAPTURE_IN_HEIGHT
        );



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
 * \param   pObj  [IN] Chains_VipSingleCameraLaneDetectObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraLaneDetect_StartApp(Chains_VipSingleCameraLaneDetectAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCameraLaneDetect_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_VipSingleCameraLaneDetectObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraLaneDetect_StopAndDeleteApp(Chains_VipSingleCameraLaneDetectAppObj *pObj)
{
    chains_vipSingleCameraLaneDetect_Stop(&pObj->ucObj);
    chains_vipSingleCameraLaneDetect_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
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
Void Chains_vipSingleCameraLaneDetect(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraLaneDetectAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCameraLaneDetect_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCameraLaneDetect_StartApp(&chainsObj);

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
                chains_vipSingleCameraLaneDetect_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCameraLaneDetect_StopAndDeleteApp(&chainsObj);
}

