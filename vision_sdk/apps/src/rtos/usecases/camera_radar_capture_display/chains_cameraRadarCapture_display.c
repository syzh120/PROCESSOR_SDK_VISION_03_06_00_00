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
#include "chains_cameraRadarCapture_display_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>
#include <include/common/chains_radar.h>

/*
 * AEWB algorithm memory requirement cannot be calculated upfront.
 * This size is known by running the use-case once with large size
 * and then checking the log for unused memory in AEWB algorithm
 */
#define ALG_AEWB_MEM_SIZE                           (896*1024)

#define CAPTURE_SENSOR_WIDTH      (1920)
#define CAPTURE_SENSOR_HEIGHT     (1080)

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraFrameCopyObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_cameraRadarCapture_displayObj  ucObj;

    IssM2mSimcopLink_ConfigParams   simcopConfig;
    vpsissldcConfig_t               ldcCfg;
    vpsissvtnfConfig_t              vtnfCfg;

    UInt32                          captureOutWidth;
    UInt32                          captureOutHeight;
    UInt32                          displayWidth;
    UInt32                          displayHeight;

    Chains_Ctrl                    *chainsCfg;

    IssM2mSimcopLink_OperatingMode  simcopMode;
    Bool                            bypassVtnf;
    Bool                            bypassLdc;

    AppUtils_Obj             appSensInfo;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;
    /* Algorithm Function Create Parameters */
    AlgorithmFxn_RadarFftCreateParams radarFftParams;
    AlgorithmFxn_RadarPkDetectCreateParams radarPkDetectParams;
    AlgorithmFxn_RadarBeamFormCreateParams radarBeamFormParams;
    AlgorithmFxn_RadarDrawCreateParams radarDrawParams;

} chains_cameraRadarCapture_displayAppObj;


char gChains_CameraRadarCapture_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_cameraRadarCapture_display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_cameraRadarCapture_display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    DisplayLink_CreateParams *pPrm_Radar,
                                    Chains_DisplayType displayType,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Video->rtParams.tarWidth  = captureWidth;
        pPrm_Video->rtParams.tarHeight = captureHeight;
        pPrm_Video->rtParams.posX      = 0;
        pPrm_Video->rtParams.posY      = (displayHeight - captureHeight) / 2U;
        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_Radar)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Radar->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Radar->rtParams.tarWidth  = displayWidth - captureWidth;
        pPrm_Radar->rtParams.tarHeight = captureHeight;
        pPrm_Radar->rtParams.posX = captureWidth;
        pPrm_Radar->rtParams.posY = (displayHeight - captureHeight) / 2U;
        pPrm_Radar->displayId = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pPrm_Grpx)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

Void chains_cameraRadarCapture_display_SetIspConfig(
            chains_cameraRadarCapture_displayAppObj *pObj)
{
    appSetDefaultIspParams(&pObj->appSensInfo);
    appSetIspParamsFromDCC(&pObj->appSensInfo);
}

Void chains_cameraRadarCapture_display_setMuxes(
            chains_cameraRadarCapture_displayAppObj *pObj)
{
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
}

Void chains_cameraRadarCapture_display_SetIssRszPrms(
        IssRszLink_CreateParams *issRszPrms,
        UInt32 outWidth,
        UInt32 outHeight)
{
    IssRszLink_ChannelParams *chPrms;

    chPrms = issRszPrms->channelParams;

    chPrms->enableOut[0U] = TRUE;
    chPrms->outParams.heightRszA = outHeight;
    chPrms->outParams.widthRszA = outWidth;
    chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
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
Void chains_cameraRadarCapture_display_SetAppPrms(
    chains_cameraRadarCapture_displayObj *pUcObj, Void *appObj)
{
    chains_cameraRadarCapture_displayAppObj *pObj
        = (chains_cameraRadarCapture_displayAppObj*)appObj;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = TRUE;

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Create the sensor now */
    strncpy(pObj->appSensInfo.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appSensInfo.numCh = 1;
    pObj->appSensInfo.ispOpMode = pObj->chainsCfg->ispOpMode;
    pObj->appSensInfo.simcopOpMode = pObj->simcopMode;
    pObj->appSensInfo.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appSensInfo);

    appInitIssCaptParams(&pObj->appSensInfo, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appSensInfo, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appSensInfo, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    /* Display requires around 4 buffers for 60fps chain, so increasing
       simcop output buffers to 4 */
    pUcObj->IssM2mIspPrm.channelParams[0u].numBuffersPerCh = 4U;
    pUcObj->IssM2mIspPrm.channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
    pUcObj->IssM2mIspPrm.channelParams[0].outParams.widthRszA = (pObj->displayWidth/3) & ~0x1;
    pUcObj->IssM2mIspPrm.channelParams[0].outParams.heightRszA = pObj->displayHeight/3;

    if (strcmp(SENSOR_SONY_IMX390_AWR1243_UB953_D3, pObj->chainsCfg->sensorName) == 0)
    {
        pUcObj->IssM2mIspPrm.channelParams[0U].horizontalFlip = TRUE;
        pUcObj->IssM2mIspPrm.channelParams[0U].verticalFlip   = TRUE;
    }

    chains_cameraRadarCapture_display_SetIssRszPrms(
        &pUcObj->IssM2mResizerPrm,
        ((pObj->displayWidth/2) & ~0x1), /* Even value needed */
        (pObj->displayHeight/2));

    pObj->captureOutWidth = pUcObj->IssM2mResizerPrm.channelParams[0].outParams.widthRszA;
    pObj->captureOutHeight = pUcObj->IssM2mResizerPrm.channelParams[0].outParams.heightRszA;

    pUcObj->SelectPrm.numOutQue = 2;
    pUcObj->SelectPrm.outQueChInfo[0].outQueId   = 0;
    pUcObj->SelectPrm.outQueChInfo[0].numOutCh   = 1;
    pUcObj->SelectPrm.outQueChInfo[0].inChNum[0] = 0;
    pUcObj->SelectPrm.outQueChInfo[1].outQueId   = 1;
    pUcObj->SelectPrm.outQueChInfo[1].numOutCh   = 1;
    pUcObj->SelectPrm.outQueChInfo[1].inChNum[0] = 1;

    appStartIssSensorSerDes(&pObj->appSensInfo);

    /* Radar Configurations */
    Chains_ar12xxGetSampleConfig(&pObj->ar12xxCfg, 1U);
    ChainsCommon_ar12xxConfig(&pObj->ar12xxCfg);
    ChainsCommon_ar12xxSetIssCaptureParams(&pUcObj->IssCapturePrm, &pObj->ar12xxCfg);

    ChainsCommon_ar12xxSetFFTParams(
        &pObj->radarFftParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetPkDetectParams(
        &pObj->radarPkDetectParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetBeamFormParams(
        &pObj->radarBeamFormParams,
        &pObj->ar12xxCfg
        );
    ChainsCommon_ar12xxSetRadarDrawParams(
        &pObj->radarDrawParams,
        &pObj->ar12xxCfg,
        pObj->displayWidth/2,
        pObj->displayHeight/2);

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight);

    chains_cameraRadarCapture_display_SetDisplayPrms(
            &pUcObj->Display_VideoPrm,
            &pUcObj->Display_GrpxPrm,
            &pUcObj->Display_RadarPrm,
            pObj->chainsCfg->displayType,
            pObj->displayWidth,
            pObj->displayHeight,
            pObj->captureOutWidth,
            pObj->captureOutHeight);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight);
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
 * \param   pObj  [IN] chains_cameraRadarCapture_displayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_cameraRadarCapture_display_StartApp(chains_cameraRadarCapture_displayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_cameraRadarCapture_display_SetIspConfig(pObj);
    chains_cameraRadarCapture_display_setMuxes(pObj);

    ChainsCommon_ar12xxStart();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_cameraRadarCapture_display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_cameraRadarCapture_displayAppObj
 *
 *******************************************************************************
*/
Void chains_cameraRadarCapture_display_StopAndDeleteApp(chains_cameraRadarCapture_displayAppObj *pObj)
{
    chains_cameraRadarCapture_display_Stop(&pObj->ucObj);
    chains_cameraRadarCapture_display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    ChainsCommon_ar12xxStop(&pObj->ar12xxCfg);

    appStopISSSensor(&pObj->appSensInfo);

    appDeleteISSSensor(&pObj->appSensInfo);

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
Void Chains_cameraRadarCapture_display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_cameraRadarCapture_displayAppObj chainsObj;

    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */

    Vps_printf(" Entered Chains_CameraRadarCapture_Display \n");

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.ucObj.Alg_RadarProcess_fftPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams;

    chainsObj.ucObj.Alg_RadarProcess_pkDetectPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarPkDetectParams;
    chainsObj.ucObj.Alg_RadarProcess_beamFormPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarBeamFormParams;
    chainsObj.ucObj.Alg_RadarProcess_drawObjsPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarDrawParams;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_cameraRadarCapture_display_Create(&chainsObj.ucObj, &chainsObj);
    ChainsCommon_SetIssCaptureErrorHandlingCb(chainsObj.ucObj.IssCaptureLinkID);

    chains_cameraRadarCapture_display_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_CameraRadarCapture_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_cameraRadarCapture_display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_cameraRadarCapture_display_StopAndDeleteApp(&chainsObj);

}

