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
#include "chains_lvdsVipSingleStereo_priv.h"

#include "../common/chains_common_stereo_defines.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_dewarp.h>


/*
#define CAPTURE_SENSOR_WIDTH                                    1280
#define CAPTURE_SENSOR_HEIGHT                                   720
*/

#define REMAP_WIDTH                                             896
#define REMAP_HEIGHT                                            384

#define STEREO_OUTPUT_WIDTH                                     640
#define STEREO_OUTPUT_HEIGHT                                    360

#define LIVE_CAMERA_DISPLAY_WIDTH                               640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              360


#define CROP_CAPTURE_SENSOR_WIDTH                               1280
#define CROP_CAPTURE_SENSOR_HEIGHT                              720


/*
#define REMAP_WIDTH                                             448
#define REMAP_HEIGHT                                            264

#define STEREO_OUTPUT_WIDTH                                     320
#define STEREO_OUTPUT_HEIGHT                                    240

#define LIVE_CAMERA_DISPLAY_WIDTH                               640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              360

#define CROP_CAPTURE_SENSOR_WIDTH                               1216 // 1222
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

	chains_lvdsVipSingleStereoObj ucObj;

    Chains_Ctrl *chainsCfg;

    Int8  * steroParamsBuffer;
    /**< Stereo params buffer */

} Chains_LvdsVipSingleStereoAppObj;


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
Void chains_lvdsVipSingleStereo_SetVpePrm(
        VpeLink_CreateParams *pOrgCapturePrm,
        VpeLink_CreateParams *pOrgPrm,
        VpeLink_CreateParams *pDisparityPrm,
        StereoImageDims *imDims,
        UInt32 cropCaptureSensorWidth,
        UInt32 cropCaptureSensorHeight,
        UInt32 disparityWinWidth,
        UInt32 disparityWinHeight,
        UInt32 orgVideoWinWidth,
        UInt32 orgVideoWinHeight
)
{
    UInt16 chId;

    if(pOrgCapturePrm)
        pOrgCapturePrm->enableOut[0] = TRUE;

    if(pOrgPrm)
        pOrgPrm->enableOut[0] = TRUE;

    if(pDisparityPrm)
        pDisparityPrm->enableOut[0] = TRUE;

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

    if(pDisparityPrm)
    {

        for(chId = 0; chId < 2; chId++)
        {
            pDisparityPrm->chParams[chId].outParams[0].width = disparityWinWidth;
            pDisparityPrm->chParams[chId].outParams[0].height = disparityWinHeight;
            pDisparityPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
            pDisparityPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
            pDisparityPrm->chParams[chId].scCropCfg.cropStartX = 0;
            pDisparityPrm->chParams[chId].scCropCfg.cropStartY = 0;
            pDisparityPrm->chParams[chId].scCropCfg.cropWidth = imDims->disparityOutputRoiWidth;
            pDisparityPrm->chParams[chId].scCropCfg.cropHeight = imDims->disparityOutputRoiHeight;
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
Void chains_lvdsVipSingleStereo_SetAppPrms(
        chains_lvdsVipSingleStereoObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth = 0, displayHeight = 0;
    Chains_LvdsVipSingleStereoAppObj *pObj
        = (Chains_LvdsVipSingleStereoAppObj*)appObj;

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

#if READ_SPARAMS_FROM_SD
    ChainsCommon_Stereo_Read_Params((Int32 *)pObj->steroParamsBuffer);
#endif

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
            &pUcObj->Display_disparityPrm,
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
            &pUcObj->Alg_DmaSwMsPrm,
            2,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0);

    ChainsCommon_Stereo_SetSyncPrm(
            &pUcObj->Sync_orgPrm,
            &pUcObj->Sync_dispPrm,
            2);

    ChainsCommon_TDA2x_Stereo_AlgoParams(
            &pUcObj->Alg_RemapMergePrm,
            &pUcObj->Alg_CensusPrm,
            &pUcObj->Alg_DisparityHamDistPrm,
            &pUcObj->Alg_StereoPostProcessPrm);


    chains_lvdsVipSingleStereo_SetVpePrm(
            &pUcObj->VPE_capturePrm,
            &pUcObj->VPE_orgdispPrm,
            &pUcObj->VPE_disparityPrm,
            &gStereoImDims,
            CROP_CAPTURE_SENSOR_WIDTH,
            CROP_CAPTURE_SENSOR_HEIGHT,
            1280,
            720,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT
    );


    // control frame rate
    for(i=0; i < 2; i++)
    {
        pUcObj->CapturePrm.vipInst[i].outParams[0].frameSkipMask
                = frameSkipMask;
    }

    pUcObj->Alg_RemapMergePrm.allocBufferForRawDump = FALSE;
    
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
 * \param   pObj  [IN] Chains_LvdsVipSingleStereoAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereo_StartApp(Chains_LvdsVipSingleStereoAppObj *pObj)
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

    chains_lvdsVipSingleStereo_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVipSingleStereoAppObj
 *
 *******************************************************************************
*/
Void chains_lvdsVipSingleStereo_StopAndDeleteApp(Chains_LvdsVipSingleStereoAppObj *pObj)
{
	chains_lvdsVipSingleStereo_Stop(&pObj->ucObj);
	chains_lvdsVipSingleStereo_Delete(&pObj->ucObj);
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
Void Chains_lvdsVipSingleStereo(Chains_Ctrl *chainsCfg)
{
    char ch;
#if READ_SPARAMS_FROM_SD
    Int32 status;
#endif
    UInt32 done = FALSE;
    Chains_LvdsVipSingleStereoAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

#if READ_SPARAMS_FROM_SD
    status = File_chDir("/TDA2x");
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: TDA3x Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Requires LDC LUTs in TDA2x folder \n");
        return;
    }

    chainsObj.steroParamsBuffer = ChainsCommon_DeWarp_memAlloc(
                                            STEREO_PARAM_SIZE,
                                            128U);
#endif

    chains_lvdsVipSingleStereo_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipSingleStereo_StartApp(&chainsObj);

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
                chains_lvdsVipSingleStereo_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVipSingleStereo_StopAndDeleteApp(&chainsObj);


#if READ_SPARAMS_FROM_SD
    /* free memory to read stereo params from SD */
    ChainsCommon_DeWarp_memFree(chainsObj.steroParamsBuffer,
            STEREO_PARAM_SIZE);

    /*
     *  Change to the root dir
     */
    status = File_chDir("/\0");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
#endif

}

