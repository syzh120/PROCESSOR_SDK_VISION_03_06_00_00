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
#include "chains_lvdsVipSingleStereoCalibration_priv.h"

#include "../common/chains_common_stereo_defines.h"
#include <src/include/chains_common.h>

#define CAPTURE_SENSOR_WIDTH                                    1280
#define CAPTURE_SENSOR_HEIGHT                                   720




#define REMAP_WIDTH                                             896
#define REMAP_HEIGHT                                            384

#define STEREO_OUTPUT_WIDTH                                     640
#define STEREO_OUTPUT_HEIGHT                                    360

#define LIVE_CAMERA_DISPLAY_WIDTH                               640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              360


#define CROP_CAPTURE_SENSOR_WIDTH                               1280
#define CROP_CAPTURE_SENSOR_HEIGHT                              720


/*
// to capture original resolution of image
#define REMAP_WIDTH                                             1280
#define REMAP_HEIGHT                                            720

#define STEREO_OUTPUT_WIDTH                                     1280
#define STEREO_OUTPUT_HEIGHT                                    720

#define LIVE_CAMERA_DISPLAY_WIDTH                               640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              360

#define CROP_CAPTURE_SENSOR_WIDTH                               1280
#define CROP_CAPTURE_SENSOR_HEIGHT                              720
*/


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

	chains_lvdsVipSingleStereoCalibrationObj ucObj;

    Chains_Ctrl *chainsCfg;

} Chains_LvdsVipSingleStereoCalibrationAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
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
Void chains_lvdsVipSingleStereoCalibration_SetVpePrm(
        VpeLink_CreateParams *pOrgCapturePrm,
        VpeLink_CreateParams *pOrgPrm,
        StereoImageDims *imDims,
        UInt32 cropCaptureSensorWidth,
        UInt32 cropCaptureSensorHeight,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight
)
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

            pOrgCapturePrm->chParams[chId].outParams[0].width   = imDims->remapImageWidth;
            pOrgCapturePrm->chParams[chId].outParams[0].height  = imDims->remapImageHeight;
            pOrgCapturePrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
            pOrgCapturePrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropStartX = (CAPTURE_SENSOR_WIDTH - cropCaptureSensorWidth) >> 1;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropStartY = (CAPTURE_SENSOR_HEIGHT - cropCaptureSensorHeight) >> 1;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pOrgCapturePrm->chParams[chId].scCropCfg.cropWidth  = cropCaptureSensorWidth;
            pOrgCapturePrm->chParams[chId].scCropCfg.cropHeight = cropCaptureSensorHeight;

            Vps_printf("remap:%d, %d - %d, %d\n", imDims->remapImageWidth, imDims->remapImageHeight, CAPTURE_SENSOR_WIDTH - cropCaptureSensorWidth, CAPTURE_SENSOR_HEIGHT - cropCaptureSensorHeight);

        }
    }

    if(pOrgPrm)
    {
        Vps_printf("--- crop Wid:%d, hiegh:%d, org (%d, %d)\n ",
                imDims->disparityOutputRoiWidth, imDims->disparityOutputRoiHeight,
                orgVideoWinWidth, orgVideoWinHeight);

        for(chId = 0; chId < 2; chId++)
        {
            pOrgPrm->chParams[chId].outParams[0].width   = orgVideoWinWidth;
            pOrgPrm->chParams[chId].outParams[0].height  = orgVideoWinHeight;
            pOrgPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
            pOrgPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pOrgPrm->chParams[chId].scCropCfg.cropStartX = imDims->origRoiStartX;
            pOrgPrm->chParams[chId].scCropCfg.cropStartY = imDims->origRoiStartY;
            /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
             * to VPE for upscale/downscale to work properly
             */
            pOrgPrm->chParams[chId].scCropCfg.cropWidth  = imDims->disparityOutputRoiWidth;
            pOrgPrm->chParams[chId].scCropCfg.cropHeight = imDims->disparityOutputRoiHeight;
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
Void chains_lvdsVipSingleStereoCalibration_SetAppPrms(
        chains_lvdsVipSingleStereoCalibrationObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth = 0, displayHeight = 0;
    Chains_LvdsVipSingleStereoCalibrationAppObj *pObj
        = (Chains_LvdsVipSingleStereoCalibrationAppObj*)appObj;

    Int i;

    UInt32 frameSkipMask = 0x24924924;    // 20 fps


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


    ChainsCommon_Stereo_SetGlobalParams(
            REMAP_WIDTH,
            REMAP_HEIGHT,
            STEREO_OUTPUT_WIDTH,
            STEREO_OUTPUT_HEIGHT);

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
            1280,                       // disparityWinWidth,
            720,                        // disparityWindHeight
            0,                          // orgVideoWinStartX
            720,                        // orgVideoWinStartY
            LIVE_CAMERA_DISPLAY_WIDTH,  // orgVideoWinWidth (640)
            LIVE_CAMERA_DISPLAY_HEIGHT, // orgVideoWinWidth (360)
            0                           // orgVideoWinGap
            );

    ChainsCommon_Stereo_SetAlgDmaSwMsPrm(
            &pUcObj->Alg_DmaSwMs_orgPrm,
            2,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0);

    ChainsCommon_Stereo_SetSyncPrm(
            &pUcObj->Sync_orgPrm,
            NULL,
            2);


    ChainsCommon_TDA2x_Stereo_AlgoParams(
            &pUcObj->Alg_RemapMergePrm,
            NULL,
            NULL,
            NULL);

    // do not read QSPI
    pUcObj->Alg_RemapMergePrm.calibLUTBufPrms.isValid= FALSE;

    chains_lvdsVipSingleStereoCalibration_SetVpePrm(
            &pUcObj->VPE_capturePrm,
            &pUcObj->VPE_orgPrm,
            &gStereoImDims,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT);

    /*
    // Overwrite original input VPE params
    // show entire input images without cropping
    for(i = 0; i < pObj->chainsCfg->numLvdsCh; i++)
    {
        pUcObj->VPE_orgPrm.chParams[i].scCropCfg.cropStartX = 0;
        pUcObj->VPE_orgPrm.chParams[i].scCropCfg.cropStartY = 0;

        pUcObj->VPE_orgPrm.chParams[i].scCropCfg.cropWidth  = CAPTURE_SENSOR_WIDTH;
        pUcObj->VPE_orgPrm.chParams[i].scCropCfg.cropHeight = CAPTURE_SENSOR_HEIGHT;
    }
    */

    // control frame rate
    for(i=0; i < pObj->chainsCfg->numLvdsCh; i++)
    {
        pUcObj->CapturePrm.vipInst[i].outParams[0].frameSkipMask
                = frameSkipMask;
    }

    // to dump image in Remap link
    pUcObj->Alg_RemapMergePrm.allocBufferForRawDump = TRUE;

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
 * \param   pObj  [IN] Chains_LvdsVipSingleStereoCalibrationAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereoCalibration_StartApp(Chains_LvdsVipSingleStereoCalibrationAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);


    chains_lvdsVipSingleStereoCalibration_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVipSingleStereoCalibrationAppObj
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereoCalibration_StopAndDeleteApp(Chains_LvdsVipSingleStereoCalibrationAppObj *pObj)
{
	chains_lvdsVipSingleStereoCalibration_Stop(&pObj->ucObj);
	chains_lvdsVipSingleStereoCalibration_Delete(&pObj->ucObj);
	ChainsCommon_Stereo_Delete(&pObj->ucObj.Alg_RemapMergePrm);


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
 * \brief   Multi Channel Capture Display usecase function
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
Void Chains_lvdsVipSingleStereoCalibration(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_LvdsVipSingleStereoCalibrationAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_lvdsVipSingleStereoCalibration_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipSingleStereoCalibration_StartApp(&chainsObj);

    while(!done)
    {
        //MM 141223 from Chaitanya
        *(volatile unsigned int*)(0x4A002534) |= 0x6FF;
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_lvdsVipSingleStereoCalibration_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVipSingleStereoCalibration_StopAndDeleteApp(&chainsObj);

}

