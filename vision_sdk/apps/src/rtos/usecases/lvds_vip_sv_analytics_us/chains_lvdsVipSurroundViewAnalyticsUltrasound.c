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
#include "chains_lvdsVipSurroundViewAnalyticsUltrasound_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_osal.h>

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

    chains_lvdsVipSurroundViewAnalyticsUltrasoundObj ucObj;

    Chains_Ctrl *chainsCfg;

} Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj;

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
Void chains_lvdsVipSurroundViewAnalyticsUltrasound_SetAppPrms(
            chains_lvdsVipSurroundViewAnalyticsUltrasoundObj *pUcObj, Void *appObj)
{
    Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj *pObj
        = (Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj*)appObj;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    UInt32 svOutWidth, svOutHeight;
    UInt32 displayWidth, displayHeight;

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    /* VIP Capture */
    ChainsCommon_MultiCam_StartCaptureDevice(
                                    CHAINS_CAPTURE_SRC_OV10635,
                                    portId,
                                    pObj->chainsCfg->numLvdsCh);

    ChainsCommon_MultiCam_SetCapturePrms(
                                    &pUcObj->CapturePrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    portId,
                                    pObj->chainsCfg->numLvdsCh);
    {
        UInt32 i;
        CaptureLink_VipInstParams *pInstPrm;

        for (i = 0U; i < SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pInstPrm = &pUcObj->CapturePrm.vipInst[i];
            pInstPrm->numBufs = 6;
        }
    }

    /* Select */
    ChainsCommon_SurroundView_SetSelectPrm(&pUcObj->SelectPrm);

    /* VPE */
    ChainsCommon_SurroundView_SetVpePrm(
                                    &pUcObj->VPE_sv_orgPrm,
                                    NULL,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT);

    /* Sync */
    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_svPrm, pObj->chainsCfg->numLvdsCh, 1); /* 1: Tight Sync */
    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_sv_orgPrm, pObj->chainsCfg->numLvdsCh, 1); /* 1: Tight Sync */
    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_algDisplayPrm, 2, 0);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                &pUcObj->Alg_SynthesisPrm,
                                SRV_LVDS_CAPTURE_WIDTH,
                                SRV_LVDS_CAPTURE_HEIGHT,
                                svOutWidth,
                                svOutHeight,
                                SRV_NUM_VIEWS,
                                SRV_CARBOX_WIDTH,
                                SRV_CARBOX_HEIGHT,
                                pObj->chainsCfg->svOutputMode,
                                pObj->chainsCfg->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlignParams(
                                &pUcObj->Alg_GeoAlignPrm,
                                SRV_LVDS_CAPTURE_WIDTH,
                                SRV_LVDS_CAPTURE_HEIGHT,
                                svOutWidth,
                                svOutHeight,
                                SRV_NUM_VIEWS,
                                SRV_CARBOX_WIDTH,
                                SRV_CARBOX_HEIGHT,
                                pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                &pUcObj->Alg_PhotoAlignPrm,
                                SRV_LVDS_CAPTURE_WIDTH,
                                SRV_LVDS_CAPTURE_HEIGHT,
                                svOutWidth,
                                svOutHeight,
                                SRV_NUM_VIEWS,
                                SRV_CARBOX_WIDTH,
                                SRV_CARBOX_HEIGHT,
                                pObj->chainsCfg->svOutputMode);

    ChainsCommon_SurroundView_SetAlgDmaSwMsPrm(
                                &pUcObj->Alg_DmaSwMs_sv_orgPrm,
                                SRV_NUM_VIEWS,
                                SVORG_SCALED_WIDTH,
                                SVORG_SCALED_HEIGHT,
                                0,
                                SVORG_MOSAIC_SPACING_HOR,
                                SVORG_MOSAIC_SPACING_VER);

    ChainsCommon_SurroundView_SetAlgDmaSwMsPrm(
                                &pUcObj->Alg_DmaSwMs_algPrm,
                                2,
                                FRONTCAM_SCALED_WIDTH,
                                FRONTCAM_SCALED_HEIGHT,
                                0,
                                FRONTCAM_MOSAIC_SPACING_HOR,
                                FRONTCAM_MOSAIC_SPACING_VER);

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                &pUcObj->GrpxSrcPrm,
                                displayWidth,
                                displayHeight,
                                pObj->chainsCfg->svOutputMode);

    ChainsCommon_SurroundView_SetDisplayPrm(
                                &pUcObj->Display_svPrm,
                                &pUcObj->Display_sv_orgPrm,
                                &pUcObj->Display_algPrm,
                                &pUcObj->Display_GrpxPrm,
                                displayWidth,
                                displayHeight);

    ChainsCommon_StartDisplayCtrl(
                                pObj->chainsCfg->displayType,
                                displayWidth,
                                displayHeight);

    ChainsCommon_SurroundView_SetFCVpePrm(
                                &pUcObj->VPE_algPdPrm,
                                SRV_FEATUREPLANE_ALG_WIDTH,
                                SRV_FEATUREPLANE_ALG_HEIGHT,
                                SRV_LVDS_CAPTURE_WIDTH,
                                SRV_LVDS_CAPTURE_HEIGHT,
                                SYSTEM_DF_YUV420SP_UV);

    ChainsCommon_SurroundView_SetFeaturePlaneComputeAlgPrms(
                                &pUcObj->Alg_FeaturePlaneComputationPrm,
                                SRV_FEATUREPLANE_ALG_WIDTH,
                                SRV_FEATUREPLANE_ALG_HEIGHT);

    ChainsCommon_SurroundView_SetObjectDetectPrm(
                                &pUcObj->Alg_ObjectDetectionPrm,
                                SRV_FEATUREPLANE_ALG_WIDTH,
                                SRV_FEATUREPLANE_ALG_HEIGHT);

    ChainsCommon_SurroundView_SetSyncFcPrm(&pUcObj->Sync_algPdPrm);

    //add setting parameters for ultrasound/pixelPerCm
    pUcObj->Alg_GeoAlignPrm.enablePixelsPerCm = 1;
    pUcObj->GrpxSrcPrm.ultrasonicParams.enable = TRUE;
    pUcObj->GrpxSrcPrm.ultrasonicParams.windowStartX = 25+320+10;
    pUcObj->GrpxSrcPrm.ultrasonicParams.windowStartY = 0;
    pUcObj->GrpxSrcPrm.ultrasonicParams.windowWidth = 880;
    pUcObj->GrpxSrcPrm.ultrasonicParams.windowHeight = 1080;
    /* ultrasonic results format is BGRA4444, match GrpxSrc format to this
     * to allow overlay of ultrasonic results on top of surround view output
     */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;
    pUcObj->Alg_UltrasonicFusionPrm.numOutputTables = 1;
    pUcObj->Alg_UltrasonicFusionPrm.numViews = 4;
    pUcObj->Alg_UltrasonicFusionPrm.numUltrasonic = 6;

    //Graphics Params
    pUcObj->GrpxSrcPrm.surroundViewEdgeDetectLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.surroundViewDOFLayoutEnable = FALSE;
    pUcObj->GrpxSrcPrm.surroundViewPdTsrLayoutEnable = TRUE;
    pUcObj->GrpxSrcPrm.surroundViewLdLayoutEnable = FALSE;

    //set parameters for PD/TSR Object Draw
    pUcObj->Alg_ObjectDraw_PdPrm.drawOption = ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD;
    pUcObj->Alg_ObjectDraw_PdPrm.imgFrameHeight = 360;
    pUcObj->Alg_ObjectDraw_PdPrm.imgFrameWidth = 640;
    pUcObj->Alg_ObjectDraw_PdPrm.numOutBuffers = 4;
    pUcObj->Alg_ObjectDraw_TsrPrm.drawOption = ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR;
    pUcObj->Alg_ObjectDraw_TsrPrm.imgFrameHeight = 360;
    pUcObj->Alg_ObjectDraw_TsrPrm.imgFrameWidth = 640;
    pUcObj->Alg_ObjectDraw_TsrPrm.numOutBuffers = 4;

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
 * \param   pObj  [IN] Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundViewAnalyticsUltrasound_StartApp(
                           Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_lvdsVipSurroundViewAnalyticsUltrasound_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundViewAnalyticsUltrasound_StopAndDeleteApp(
                           Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj *pObj)
{
    chains_lvdsVipSurroundViewAnalyticsUltrasound_Stop(&pObj->ucObj);
    chains_lvdsVipSurroundViewAnalyticsUltrasound_Delete(&pObj->ucObj);

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
Void Chains_lvdsVipSurroundViewAnalyticsUltrasound(Chains_Ctrl *chainsCfg)
{
    Int32 chDirRet;
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_lvdsVipSurroundViewAnalyticsUltrasoundAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chDirRet = ChainsCommon_Osal_fileChDir(SRV_DIR_2X);

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        chains_lvdsVipSurroundViewAnalyticsUltrasound_Create(&chainsObj.ucObj, &chainsObj);
        chains_lvdsVipSurroundViewAnalyticsUltrasound_StartApp(&chainsObj);

        while(!done)
        {
            ch = Chains_menuRunTime();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_lvdsVipSurroundViewAnalyticsUltrasound_printStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_lvdsVipSurroundViewAnalyticsUltrasound_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
    } while(chPrev!='3');

    if (SYSTEM_LINK_STATUS_SOK == chDirRet)
    {
        File_chDir("/\0");
    }
}

