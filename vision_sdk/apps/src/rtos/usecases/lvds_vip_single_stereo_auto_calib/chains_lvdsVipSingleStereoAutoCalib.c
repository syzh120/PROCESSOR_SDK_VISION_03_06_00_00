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
#include "chains_lvdsVipSingleStereoAutoCalib_priv.h"

#include "../common/chains_common_stereo_defines.h"
#include <src/include/chains_common.h>




#define REMAP_WIDTH                                             (896U)
#define REMAP_HEIGHT                                            (384U)

#define STEREO_OUTPUT_WIDTH                                     (640U)
#define STEREO_OUTPUT_HEIGHT                                    (360U)

#define LIVE_CAMERA_DISPLAY_WIDTH                               (960U)
#define LIVE_CAMERA_DISPLAY_HEIGHT                              (540U)


#define CROP_CAPTURE_SENSOR_WIDTH                               (1280U)
#define CROP_CAPTURE_SENSOR_HEIGHT                              (720U)


/*
#define REMAP_WIDTH                                             448
#define REMAP_HEIGHT                                            264

#define STEREO_OUTPUT_WIDTH                                     320
#define STEREO_OUTPUT_HEIGHT                                    240

#define LIVE_CAMERA_DISPLAY_WIDTH                               960 //640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              540 //360

#define CROP_CAPTURE_SENSOR_WIDTH                               1216 // 1222
#define CROP_CAPTURE_SENSOR_HEIGHT                              720
*/

#define ORG_VIDEO_DISPLAY_START_X                               (0U)
#define ORG_VIDEO_DISPLAY_START_Y                               (270U)


// RANSAC configs
#define USE_RANSAC                                              (0U)
#define NUM_RANSAC_ITERS                                        (2000U)
#define NUM_RANSAC_DATA                                         (5U)

#define ROI_REGION_AROUND_CENTER                                (0.5) // (0.375)

#define FISH_EYE_RECT                                           (0)



/**
 *******************************************************************************
 *
 *  \brief  StereoCameraDisplayObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_lvdsVipSingleStereoAutoCalibObj ucObj;

    Chains_Ctrl *chainsCfg;

} Chains_LvdsVipSingleStereoAutoCalibAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters for auto rectification
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          chains_lvdsVipMultiCam_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 *          Scale each CH to 1/2x size
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
 */
Void chains_lvdsVipSingleStereoAutoCalib_SetVpePrm(
        VpeLink_CreateParams *pOrgCapturePrm,
        VpeLink_CreateParams *pOrgPrm,
        UInt32 captureSensorWidth,
        UInt32 captureSensorHeight,
        UInt32 cropCaptureSensorWidth,
        UInt32 cropCaptureSensorHeight)
{
    UInt16 chId;

    if(pOrgCapturePrm)
        pOrgCapturePrm->enableOut[0] = TRUE;

    if(pOrgPrm)
        pOrgPrm->enableOut[0] = TRUE;

    if(pOrgCapturePrm)
    {
        for(chId = 0; chId < 2; chId++)
        {
            pOrgCapturePrm->chParams[chId].outParams[0].width   = cropCaptureSensorWidth;
            pOrgCapturePrm->chParams[chId].outParams[0].height  = cropCaptureSensorHeight;
            pOrgCapturePrm->chParams[chId].outParams[0].dataFormat
                                                            = SYSTEM_DF_YUV420SP_UV;
            pOrgCapturePrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropStartX = (captureSensorWidth - cropCaptureSensorWidth) >> 1;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropStartY = (captureSensorWidth - cropCaptureSensorHeight) >> 1;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pOrgCapturePrm->chParams[chId].scCropCfg.cropWidth  = cropCaptureSensorWidth;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropHeight = cropCaptureSensorHeight;

            //Vps_printf("orgCapture:%d, %d  - %d, %d\n", CAPTURE_SENSOR_WIDTH, CAPTURE_SENSOR_HEIGHT, cropCaptureSensorWidth, cropCaptureSensorHeight);
        }
    }

    if(pOrgPrm)
    {
        for(chId = 0; chId < 2; chId++)
        {
            pOrgPrm->chParams[chId].outParams[0].width   = LIVE_CAMERA_DISPLAY_WIDTH;
            pOrgPrm->chParams[chId].outParams[0].height  = LIVE_CAMERA_DISPLAY_HEIGHT;
            pOrgPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
            pOrgPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pOrgPrm->chParams[chId].scCropCfg.cropStartX = 0;
            pOrgPrm->chParams[chId].scCropCfg.cropStartY = 0;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pOrgPrm->chParams[chId].scCropCfg.cropWidth  = cropCaptureSensorWidth;
            pOrgPrm->chParams[chId].scCropCfg.cropHeight = cropCaptureSensorHeight;

            //Vps_printf("orgDisplay:%d, %d - %d %d \n", cropCaptureSensorWidth, cropCaptureSensorHeight, orgVideoWinWidth, orgVideoWinHeight);
        }
    }

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
Void chains_lvdsVipSingleStereoAutoCalib_SetAppPrms(
        chains_lvdsVipSingleStereoAutoCalibObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth = 0, displayHeight = 0;
    Chains_LvdsVipSingleStereoAutoCalibAppObj *pObj
        = (Chains_LvdsVipSingleStereoAutoCalibAppObj*)appObj;

	Int i;

	UInt32 frameSkipMask = 0x24924924;   // 20 fps


    if(pObj->chainsCfg->displayType==CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        displayWidth     = 1280;
        displayHeight    = 720;
    }
    else
    if(pObj->chainsCfg->displayType==CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        displayWidth     = 1920;
        displayHeight    = 1080;
    }


    ChainsCommon_TDA2x_Stereo_SetCapturePrms(
            &pUcObj->CapturePrm,
            pObj->chainsCfg->captureSrc,
            pObj->chainsCfg->displayType,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT);

    ChainsCommon_Stereo_SetGrpxSrcPrms(
            &pUcObj->GrpxSrcPrm,
            displayWidth,
            displayHeight);

    ChainsCommon_Stereo_SetDisplayPrms(
            &pUcObj->Display_orgPrm,
            NULL,
            &pUcObj->Display_GrpxPrm,
            0,                          // disparityWinStartX
            0,                          // disparityWinStartY
            0,                          // disparityWinWidth,
            0,                          // disparityWindHeight
            ORG_VIDEO_DISPLAY_START_X,  // orgVideoWinStartX
            ORG_VIDEO_DISPLAY_START_Y,  // orgVideoWinStartY
            LIVE_CAMERA_DISPLAY_WIDTH,  // orgVideoWinWidth
            LIVE_CAMERA_DISPLAY_HEIGHT, // orgVideoWinWidth
            0                           // orgVideoWinGap
            );

    ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMsPrm,
            2,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0);

    ChainsCommon_Stereo_SetSyncPrm(
            &pUcObj->Sync_orgPrm,
            &pUcObj->Sync_arPrm,
            2);

    chains_lvdsVipSingleStereoAutoCalib_SetVpePrm(
            &pUcObj->VPE_capturePrm,
            &pUcObj->VPE_orgPrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT);

    ChainsCommon_Single_Stereo_AutoRemapAlgPrms(
            &pUcObj->Alg_AutoRemapPrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT,
            REMAP_WIDTH,
            REMAP_HEIGHT,
            USE_RANSAC,
            NUM_RANSAC_ITERS,
            NUM_RANSAC_DATA,
            ROI_REGION_AROUND_CENTER,
            FISH_EYE_RECT,
            1);

    // disable stereo display format
    pUcObj->GrpxSrcPrm.stereoDisparityLayoutEnable = FALSE;

    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibLayout = TRUE;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibCaptureWidth = CROP_CAPTURE_SENSOR_WIDTH;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibCaptureHeight = CROP_CAPTURE_SENSOR_HEIGHT;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibDisplayWidth = LIVE_CAMERA_DISPLAY_WIDTH;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibDisplayHeight = LIVE_CAMERA_DISPLAY_HEIGHT;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibDisplayStartX = ORG_VIDEO_DISPLAY_START_X;
    pUcObj->GrpxSrcPrm.stereoCalibDisplayPrms.stereoCalibDisplayStartY = ORG_VIDEO_DISPLAY_START_Y;


    // control frame rate
    for(i=0; i < 2; i++)
    {
        pUcObj->CapturePrm.vipInst[i].outParams[0].frameSkipMask
                = frameSkipMask;
    }
    

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        displayWidth,
        displayHeight
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
 * \param   pObj  [IN] Chains_LvdsVipSingleStereoAutoCalibAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereoAutoCalib_StartApp(Chains_LvdsVipSingleStereoAutoCalibAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    /*
    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        CAPTURE_SENSOR_WIDTH,
        CAPTURE_SENSOR_HEIGHT
        );
    */

    chains_lvdsVipSingleStereoAutoCalib_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVipSingleStereoAutoCalibAppObj
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereoAutoCalib_StopAndDeleteApp(Chains_LvdsVipSingleStereoAutoCalibAppObj *pObj)
{
    chains_lvdsVipSingleStereoAutoCalib_Stop(&pObj->ucObj);
    chains_lvdsVipSingleStereoAutoCalib_Delete(&pObj->ucObj);
    ChainsCommon_Stereo_AutoRemap_Delete(&pObj->ucObj.Alg_AutoRemapPrm);

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
Void Chains_lvdsVipSingleStereoAutoCalib(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_LvdsVipSingleStereoAutoCalibAppObj chainsObj;

    Int16 * featureHeader;
    //GrpxSrcLink_StereoCalibPrm grpxSrcStereoCalibPrm;

    chainsObj.chainsCfg = chainsCfg;

    chains_lvdsVipSingleStereoAutoCalib_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipSingleStereoAutoCalib_StartApp(&chainsObj);

    // feature point buffer
    featureHeader = (Int16 *) chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.pFeatureBuf;

    /*
    grpxSrcStereoCalibPrm.featurePointBuf =
            (Int16 *)(chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.pFeatureBuf +
                      chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.featureHeaderSize);
    grpxSrcStereoCalibPrm.featurePointBufSize =
            chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.featureBufSize -
            chainsObj.ucObj.Alg_AutoRemapPrm.featureBufPrms.featureHeaderSize;
    */


    while(!done)
    {
        //ch = Chains_menuRunTime();
        ch = ChainsCommon_Stereo_AutoRemap_Menu();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':

                // feature point detection is not done yet
                featureHeader[0] = 1;

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_FEATURE_COLLECT_NEW,
                        NULL,
                        0,
                        TRUE);

                /*
                Vps_printf("--------------- Feature Header:%d\n", featureHeader[0]);


                // wait until feature detection is completed
                while(featureHeader[0] != -1)
                {
                	;
                }

                Vps_printf("------------ 1. Run GRpx :%d, %d ,%d\n", featureHeader[0], featureHeader[1], featureHeader[2]);
                grpxSrcStereoCalibPrm.startIdx = featureHeader[1];
                grpxSrcStereoCalibPrm.endIdx = featureHeader[2];


                // overlay detected feature points
                System_linkControl(
                        chainsObj.ucObj.GrpxSrcLinkID,
                        GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM,
                        &grpxSrcStereoCalibPrm,
                        sizeof(GrpxSrcLink_StereoCalibPrm),
                        TRUE);
                 */
                break;

            case '2':

                // feature point detection is not done yet
                featureHeader[0] = 2;

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_FEATURE_COLLECT,
                        NULL,
                        0,
                        TRUE);

                /*
                // wait until feature detection is completed
                while(featureHeader[0] != -1)
                {
                	;
                }


                grpxSrcStereoCalibPrm.startIdx = featureHeader[1];
                grpxSrcStereoCalibPrm.endIdx = featureHeader[2];


                // overlay detected feature points
                System_linkControl(
                        chainsObj.ucObj.GrpxSrcLinkID,
                        GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM,
                        &grpxSrcStereoCalibPrm,
                        sizeof(GrpxSrcLink_StereoCalibPrm),
                        TRUE);
                */

                break;

            case '3':

                System_linkControl(
                        chainsObj.ucObj.Alg_AutoRemapLinkID,
                        AUTO_REMAP_LINK_CMD_PERSMAT_CAL,
                        NULL,
                        0,
                        TRUE);

                break;

#if 0
            case '4':


                /*
                Vps_printf("------------ 1. Run GRpx :%d, %d ,%d\n", featureHeader[0], featureHeader[1], featureHeader[2]);

                Vps_printf("data Addr:%x, ----- %d, %d, %d, %d\n", grpxSrcStereoCalibPrm.featurePointBuf, grpxSrcStereoCalibPrm.featurePointBuf[0],
                        grpxSrcStereoCalibPrm.featurePointBuf[1],
                        grpxSrcStereoCalibPrm.featurePointBuf[2],
                        grpxSrcStereoCalibPrm.featurePointBuf[3]);
                */
                grpxSrcStereoCalibPrm.startIdx = featureHeader[1];
                grpxSrcStereoCalibPrm.endIdx = featureHeader[2];


                // overlay detected feature points
                System_linkControl(
                        chainsObj.ucObj.GrpxSrcLinkID,
                        GRPX_SRC_LINK_CMD_STEREO_CALIB_PARAM,
                        &grpxSrcStereoCalibPrm,
                        sizeof(GrpxSrcLink_StereoCalibPrm),
                        TRUE);

                break;
#endif

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_lvdsVipSingleStereoAutoCalib_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }


    chains_lvdsVipSingleStereoAutoCalib_StopAndDeleteApp(&chainsObj);

}

