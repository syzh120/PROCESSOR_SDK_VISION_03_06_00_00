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
#include "chains_networkStereoDisplay_priv.h"
#include <src/rtos/usecases/common/chains_common_stereo_defines.h>

#include <src/include/chains_common.h>

#define CAPTURE_SENSOR_WIDTH                                    1280
#define CAPTURE_SENSOR_HEIGHT                                   720

#define REMAP_WIDTH                                             896
#define REMAP_HEIGHT                                            384

#define STEREO_OUTPUT_WIDTH                                     640
#define STEREO_OUTPUT_HEIGHT                                    360

#define LIVE_CAMERA_DISPLAY_WIDTH                               640
#define LIVE_CAMERA_DISPLAY_HEIGHT                              360


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

    chains_networkStereoDisplayObj ucObj;

    Chains_Ctrl *chainsCfg;

} Chains_networkStereoDisplayAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
 */
Void chains_networkStereoDisplay_SetVpePrm(
        VpeLink_CreateParams *pPrm
)
{
    UInt16 chId;

    pPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < 2; chId++)
    {
        pPrm->chParams[chId].outParams[0].width = REMAP_WIDTH;
        pPrm->chParams[chId].outParams[0].height = REMAP_HEIGHT;
        pPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
        pPrm->chParams[chId].scCropCfg.cropStartX = 0;
        pPrm->chParams[chId].scCropCfg.cropStartY = 0;
        /* scCropCfg.cropWidth and scCropCfg.cropHeight should be equal to input resolution
         * to VPE for upscale/downscale to work properly
         */
        pPrm->chParams[chId].scCropCfg.cropWidth = REMAP_WIDTH;
        pPrm->chParams[chId].scCropCfg.cropHeight = REMAP_HEIGHT;
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
Void chains_networkStereoDisplay_SetAppPrms(
        chains_networkStereoDisplayObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth = 0, displayHeight = 0;
    Chains_networkStereoDisplayAppObj *pObj
    = (Chains_networkStereoDisplayAppObj*)appObj;

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



    ChainsCommon_SetNetworkRxPrms(
            &pUcObj->NetworkRxPrm,
            &pUcObj->DecodePrm,
            REMAP_WIDTH,
            REMAP_HEIGHT,
            2,
            30);

    ChainsCommon_Stereo_SetPrms(
            NULL,
            NULL,
            &pUcObj->VPE_orgdispPrm,
            &pUcObj->VPE_disparityPrm,
            NULL,
            NULL,
            &pUcObj->Alg_CensusPrm,
            &pUcObj->Alg_DisparityHamDistPrm,
            &pUcObj->Alg_StereoPostProcessPrm,
            &pUcObj->Sync_orgPrm,
            &pUcObj->Sync_dispPrm,
            &pUcObj->Alg_DmaSwMsPrm,
            &pUcObj->GrpxSrcPrm,
            &pUcObj->Display_orgPrm,
            &pUcObj->Display_disparityPrm,
            &pUcObj->Display_GrpxPrm,
            CHAINS_CAPTURE_SRC_MAX,
            pObj->chainsCfg->displayType,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            REMAP_WIDTH,
            REMAP_HEIGHT,
            STEREO_OUTPUT_WIDTH,
            STEREO_OUTPUT_HEIGHT,
            0,
            0,
            1280,
            720,
            0,
            720,
            LIVE_CAMERA_DISPLAY_WIDTH,
            LIVE_CAMERA_DISPLAY_HEIGHT,
            0
    );

    chains_networkStereoDisplay_SetVpePrm(&pUcObj->VPE_decodeOutPrm);

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
 * \param   pObj  [IN] Chains_networkStereoDisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void chains_networkStereoDisplay_StartApp(Chains_networkStereoDisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_networkStereoDisplay_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_networkStereoDisplayAppObj
 *
 *******************************************************************************
 */
Void chains_networkStereoDisplay_StopAndDeleteApp(Chains_networkStereoDisplayAppObj *pObj)
{
    chains_networkStereoDisplay_Stop(&pObj->ucObj);
    chains_networkStereoDisplay_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
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
Void chains_networkStereoDisplay(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_networkStereoDisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_networkStereoDisplay_Create(&chainsObj.ucObj, &chainsObj);

    chains_networkStereoDisplay_StartApp(&chainsObj);

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
            chains_networkStereoDisplay_printStatistics(&chainsObj.ucObj);
            break;
        default:
            Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
            break;
        }
    }

    chains_networkStereoDisplay_StopAndDeleteApp(&chainsObj);

}

