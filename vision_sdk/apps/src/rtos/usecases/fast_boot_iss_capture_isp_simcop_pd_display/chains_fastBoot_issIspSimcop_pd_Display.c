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
#include "chains_fastBoot_issIspSimcop_pd_Display_priv.h"
#include "chains_fastBoot_dspEvePowerDown.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>


/* This fast boot usecase supports two sensors OV10640 REV E and AR0140. There
 * is no way to select this through runtime menu since fast boot usecase doesn't
 * expose run time menu. Depending upon setup please choose following before
 * building usecase. By default its AR0140, making it 0 will choose OV10640.
 */
#define FAST_BOOT_SENSOR_TYPE_AR0140   (1)

#define ANALYTICS_AUTOMATIC_ON_OFF
/* Comment or uncomment the line below to automatically automatically switch
 * on and switch off the Analytics every ANALYTICS_TIME_ON_OFF ms.
 */
#undef ANALYTICS_AUTOMATIC_ON_OFF
#define ANALYTICS_TIME_ON_OFF     (9000U)

#define FEATUREPLANE_ALG_WIDTH    (640)
#define FEATUREPLANE_ALG_HEIGHT   (360)

#define IMAGE_UCLATE_OFFSET_QSPI    (0xA80000)
#define MAX_UCLATE_IMAGE_SIZE       (0x800000)

#define GRPX_BOOT_TIME_DISPLAY_DURATION (24*60*60*1000)
#define GRPX_BOOT_TIME_DISPLAY_FONTID   (5)
#define GRPX_BOOT_TIME_DISPLAY_ON_FONTID   (8)
#define GRPX_BOOT_TIME_DISPLAY_OFF_FONTID   (9)
#define GRPX_BOOT_TIME_DISPLAY_X_OFFSET (30)
#define GRPX_BOOT_TIME_DISPLAY_Y_OFFSET (25)
#define GRPX_ANALYTICS_STATE_DISPLAY_Y_OFFSET (235)

char gChains_FastBootIssIspSimcop_Pd_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n 1: Save Captured Frame"
"\r\n 2: Save SIMCOP Output Frame"
"\r\n 3: PD and TSR ON"
"\r\n 4: PD and TSR OFF"
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};


/**
 *******************************************************************************
 *
 * \brief   Set PD draw parameters
 *
 * \param   pPrm    [IN]    algorithm parameters
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_SetObjectDrawPrms(
                   chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj,
                   AlgorithmLink_ObjectDrawCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->imgFrameWidth    = width;
    pPrm->imgFrameHeight   = height;
    pPrm->numOutBuffers = 3;
    pPrm->objectRectThickness = 1;
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
Void chains_fastBoot_issIspSimcop_pd_Display_SetFeaturePlaneComputeAlgPrms(
                   chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj,
                   AlgorithmLink_FeaturePlaneComputationCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height)
{
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
    pPrm->numOutBuffers  = 3;

    pPrm->roiEnable      = FALSE;
    pPrm->roiCenterX     = width/2;
    pPrm->roiCenterY     = height/2;
    pPrm->roiWidth       = width;
    pPrm->roiHeight      = (height*30)/100;
    pPrm->numScales      = 17;
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
Void chains_fastBoot_issIspSimcop_pd_Display_SetObjectDetectPrm(
                   chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj,
                   AlgorithmLink_ObjectDetectionCreateParams *pPrm,
                   UInt32 width,
                   UInt32 height
                   )
{
    pPrm->numOutBuffers  = 2;
    pPrm->enablePD       = TRUE;
    if(System_isFastBootEnabled())
    {
        pPrm->enableTSR      = FALSE;
    }
    else
    {
        pPrm->enableTSR      = TRUE;
    }
    pPrm->imgFrameHeight = height;
    pPrm->imgFrameWidth  = width;
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
Void chains_fastBoot_issIspSimcop_pd_Display_SetSyncPrm(SyncLink_CreateParams *pPrm)

{
    pPrm->syncDelta = 1;
    /* This is done to allow cases where the Gate is switched off and the
     * sync buffer is not released.
     */
    pPrm->syncThreshold = 200;
}



/**
 *******************************************************************************
 *
 * \brief   Set Gate Create Parameters
 *
 *          This function is used to set the Gate params.
 *          It is called in Create function. It is advisable to have
 *          chains_fastBoot_issIspSimcop_pd_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    GateLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_SetGatePrms(GateLink_CreateParams *pPrm_GateAlgFeatureCompute,
                                                         GateLink_CreateParams *pPrm_GateAlgCapture,
                                                         GateLink_CreateParams *pPrm_GateAlgDraw,
                                                         UInt32 inWidth,
                                                         UInt32 inHeight)
{

    pPrm_GateAlgFeatureCompute->prevLinkIsCreated = TRUE;

    pPrm_GateAlgCapture->prevLinkIsCreated = TRUE;

    pPrm_GateAlgDraw->prevLinkIsCreated = FALSE;
    pPrm_GateAlgDraw->prevLinkInfo.numQue = 1;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].numCh              = 1;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].flags    = 0;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].pitch[0] = SystemUtils_align(inWidth, 32);
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].pitch[1] = SystemUtils_align(inWidth, 32);
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].startX   = 0;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].startY   = 0;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].width    = inWidth;
    pPrm_GateAlgDraw->prevLinkInfo.queInfo[0].chInfo[0].height   = inHeight;

}

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_fastBoot_issIspSimcop_pd_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    DisplayLink_CreateParams *pPrm_VideoRszB,
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

        pPrm_Video->rtParams.tarWidth  = displayWidth;
        pPrm_Video->rtParams.tarHeight = displayHeight;
        pPrm_Video->rtParams.posX      = 0;
        pPrm_Video->rtParams.posY      = 0;

        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_VideoRszB)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_VideoRszB->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_VideoRszB->rtParams.tarWidth  = displayWidth/3;
        pPrm_VideoRszB->rtParams.tarHeight = displayHeight/3;
        pPrm_VideoRszB->rtParams.posX      = displayWidth - pPrm_VideoRszB->rtParams.tarWidth - 10;
        pPrm_VideoRszB->rtParams.posY      = displayHeight - pPrm_VideoRszB->rtParams.tarHeight - 10;
        pPrm_VideoRszB->displayId          = DISPLAY_LINK_INST_DSS_VID2;
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

Void chains_fastBoot_issIspSimcop_pd_Display_SetIssM2mRszPrms(
        IssRszLink_CreateParams *pRszPrms,
        UInt32 outWidth,
        UInt32 outHeight)
{
    IssRszLink_ChannelParams *chPrms;

    chPrms = pRszPrms->channelParams;

    chPrms->enableOut[0U] = TRUE;
    chPrms->outParams.heightRszA = outHeight;
    chPrms->outParams.widthRszA = outWidth;
    chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
}


Void chains_fastBoot_issIspSimcop_pd_Display_SetSimcopConfig(
            chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    IssUtils_SetimcopLdcVtnfRtConfig(
        &pObj->ldcCfg,
        &pObj->vtnfCfg,
        pObj->bypassVtnf,
        pObj->bypassLdc);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* MUST be called after link create and before link start */
    System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
}

Void chains_fastBoot_issIspSimcop_pd_Display_SetIspConfig(
            chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    Int32 status;

    /* ISP Config */
    appSetDefaultIspParams(&pObj->appObjPrms);
    appSetIspParamsFromDCC(&pObj->appObjPrms);

    /* Initialize Simcop Configuration */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Simcop/Dewarp Config */
    IssUtils_InitSimcopConfig(
            &pObj->simcopConfig,
            pObj->bypassLdc,
            pObj->bypassVtnf);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
    UTILS_assert(0 == status);
}

Void chains_fastBoot_issIspSimcop_pd_Display_setMuxes(
            chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
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
Void chains_fastBoot_issIspSimcop_pd_Display_SetAppPrms(chains_fastBoot_issIspSimcop_pd_DisplayObj *pUcObj, Void *appObj)
{
    chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj
        = (chains_fastBoot_issIspSimcop_pd_DisplayAppObj*)appObj;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF;
    pObj->bypassVtnf = FALSE;
    /* bypassLdc should be set to FALSE if you have fish eye lens */
    pObj->bypassLdc  = TRUE;

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

#if FAST_BOOT_SENSOR_TYPE_AR0140
    strncpy(
        pObj->chainsCfg->sensorName,
        SENSOR_APTINA_AR0140,
        ISS_SENSORS_MAX_NAME);
#else
    strncpy(
        pObj->chainsCfg->sensorName,
        SENSOR_OMNIVISION_OV10640_CSI2,
        ISS_SENSORS_MAX_NAME);
#endif

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = 1;
    pObj->appObjPrms.ispOpMode = pObj->chainsCfg->ispOpMode;
    pObj->appObjPrms.simcopOpMode = pObj->simcopMode;
    pObj->appObjPrms.numCSI2Inst  = 1;
    appCreateISSSensor(&pObj->appObjPrms);

    appInitIssCaptParams(&pObj->appObjPrms, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appObjPrms, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appObjPrms, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);
    appInitIssSimcopParams(&pObj->appObjPrms, pUcObj->IssM2mSimcopLinkID,
        &pUcObj->IssM2mSimcopPrm);

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    /* Disable Resizer B */
    pUcObj->IssM2mIspPrm.channelParams[0].enableOut[
                ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;

    chains_fastBoot_issIspSimcop_pd_Display_SetFeaturePlaneComputeAlgPrms(
                    pObj,
                    &pUcObj->Alg_FeaturePlaneComputationPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_fastBoot_issIspSimcop_pd_Display_SetObjectDetectPrm(
                    pObj,
                    &pUcObj->Alg_ObjectDetectionPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_fastBoot_issIspSimcop_pd_Display_SetSyncPrm(
                    &pUcObj->Sync_algPrm
                );

    chains_fastBoot_issIspSimcop_pd_Display_SetObjectDrawPrms(
                    pObj,
                    &pUcObj->Alg_ObjectDrawPrm,
                    FEATUREPLANE_ALG_WIDTH,
                    FEATUREPLANE_ALG_HEIGHT
                );

    chains_fastBoot_issIspSimcop_pd_Display_SetGatePrms(&pUcObj->Gate_algFeatureComputePrm,
                                                        &pUcObj->Gate_algCapturePrm,
                                                        &pUcObj->Gate_algDrawPrm,
                                                        FEATUREPLANE_ALG_WIDTH,
                                                        FEATUREPLANE_ALG_HEIGHT);

    chains_fastBoot_issIspSimcop_pd_Display_SetIssM2mRszPrms(&pUcObj->IssM2mRszPrm,
                                                        FEATUREPLANE_ALG_WIDTH,
                                                        FEATUREPLANE_ALG_HEIGHT);


    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                 pObj->displayWidth,
                                 pObj->displayHeight);


    if (pObj->chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_IMX224_CSI2)
    {
        chains_fastBoot_issIspSimcop_pd_Display_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                               &pUcObj->Display_GrpxPrm,
                                               NULL,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight,
                                               pObj->captureOutWidth,
                                               pObj->captureOutHeight
                                               );
    }
    else
    {
        chains_fastBoot_issIspSimcop_pd_Display_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                               &pUcObj->Display_GrpxPrm,
                                               NULL,
                                               //NULL,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight,
                                               pObj->captureOutWidth,
                                               pObj->captureOutHeight
                                               );
    }

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
 * \param   pObj  [IN] chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_StartApp_UcEarly(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    /* Sets the Simcop Config also */
    chains_fastBoot_issIspSimcop_pd_Display_SetIspConfig(pObj);

    chains_fastBoot_issIspSimcop_pd_Display_setMuxes(pObj);

    appStartISSSensor(&pObj->appObjPrms,0);

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_fastBoot_issIspSimcop_pd_Display_Start_UcEarly(&pObj->ucObj);

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
 * \param   pObj  [IN] chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_StartApp_UcLate(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    chains_fastBoot_issIspSimcop_pd_Display_Start_UcLate(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_StopAndDeleteApp(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    chains_fastBoot_issIspSimcop_pd_Display_Stop(&pObj->ucObj);
    chains_fastBoot_issIspSimcop_pd_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    appStopISSSensor(&pObj->appObjPrms);

    appDeleteISSSensor(&pObj->appObjPrms);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    if (ANALYTICS_ON == pObj->analyticsState)
    {
        /* Print the HWI, SWI and all tasks load */
        /* Reset the accumulated timer ticks */
        Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
    }
    else
    {
        /* Disable on IPU's CPU load calculation when the analytics is
         * already off.
         */
        chains_fastBoot_stopIpuLoadCalculation();
    }
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links for UC Late Analytics Part
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_fastBoot_issIspSimcop_pd_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_fastBoot_issIspSimcop_pd_Display_StopAndDeleteApp_UcLate(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    chains_fastBoot_issIspSimcop_pd_Display_Stop_UcLate(&pObj->ucObj);
    chains_fastBoot_issIspSimcop_pd_Display_Delete_UcLate(&pObj->ucObj);

    /* Ensure that the CPU Load calculation for DSP and EVE are stopped */
    chains_fastBoot_stopDspEveLoadCalculation();
}

Void chains_fastBootDisplayAnalyticsState(chains_fastBoot_issIspSimcop_pd_DisplayAppObj *pObj)
{
    GrpxSrcLink_StringRunTimePrintParams printPrms;
    printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
    printPrms.duration_ms = GRPX_BOOT_TIME_DISPLAY_DURATION;
    printPrms.stringInfo.fontType = GRPX_BOOT_TIME_DISPLAY_ON_FONTID;
    printPrms.stringInfo.startX   = GRPX_BOOT_TIME_DISPLAY_X_OFFSET;
    printPrms.stringInfo.startY   = pObj->displayHeight-
                                    GRPX_ANALYTICS_STATE_DISPLAY_Y_OFFSET;
    if (ANALYTICS_ON == pObj->analyticsState)
    {
        printPrms.stringInfo.fontType = GRPX_BOOT_TIME_DISPLAY_ON_FONTID;
        snprintf(printPrms.stringInfo.string,
                 sizeof(printPrms.stringInfo.string) - 1,
                 "Object Detection : ON  ");
    }
    else
    {
        printPrms.stringInfo.fontType = GRPX_BOOT_TIME_DISPLAY_OFF_FONTID;
        snprintf(printPrms.stringInfo.string,
                 sizeof(printPrms.stringInfo.string) - 1,
                 "Object Detection : OFF ");
    }
    System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                       GRPX_SRC_LINK_CMD_PRINT_STRING_WO_CLEAR,
                       &printPrms,
                       sizeof(printPrms),
                       TRUE);
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
Void Chains_fastBootIssIspSimcop_pd_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Ptr ddrAddress;
    chains_fastBoot_issIspSimcop_pd_DisplayAppObj chainsObj;
    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 1; /* KW error fix */
    chainsObj.analyticsState = ANALYTICS_ON;
    DisplayLink_SwitchChannelParams displayPrm;
    Utils_BootSlaves_Params bootParams;
    GrpxSrcLink_StringRunTimePrintParams printPrms;
    UInt32 poweOnToDisplay, poweOnToAlg;

    if(chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_OV10640_CSI2
        &&
       chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_IMX224_CSI2
        &&
       chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_OV10640_PARALLEL
        &&
       chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL
        &&
       chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_AR0140BAYER_PARALLEL
        )
    {
        Vps_printf(" CHAINS: Unsupported sensor for this usecase. Cannot run use-case !!!\n");
        return;
    }

    if ((chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL) &&
        (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode)))
    {
        Vps_printf(" CHAINS: WDR Mode is not supported for AR132 sensor !!!\n");
        return;
    }
    if ((chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_AR0140BAYER_PARALLEL) &&
        (ISSM2MISP_LINK_OPMODE_1PASS_WDR == chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Single Pass WDR is only support on AR0140 !!!\n");
        return;
    }

    if (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Please make sure BSP is build with WDR and LDC enabled !!!\n");
    }

    chainsObj.chainsCfg = chainsCfg;

    chains_fastBoot_issIspSimcop_pd_Display_Create_UcEarly(&chainsObj.ucObj, &chainsObj);
    chains_fastBoot_issIspSimcop_pd_Display_StartApp_UcEarly(&chainsObj);
    poweOnToDisplay = Utils_getCurGlobalTimeInMsec();
    /* boot & sync other cores here */
    ddrAddress = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, MAX_UCLATE_IMAGE_SIZE, 4U);
    Utils_bootSlaves_paramsInit(&bootParams);
    bootParams.uclateOffset  = IMAGE_UCLATE_OFFSET_QSPI;
    bootParams.ddrAddress  = (UInt32)(ddrAddress);
    bootParams.useEdma = TRUE;
    bootParams.loadCode = TRUE;
    bootParams.maxDdrBuffSize = MAX_UCLATE_IMAGE_SIZE;
    bootParams.enableCrc = TRUE;
    Utils_bootSlaves(&bootParams);
    Utils_syncSlaves();
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, ddrAddress, MAX_UCLATE_IMAGE_SIZE);

    /* create & start late usecase */
    chains_fastBoot_issIspSimcop_pd_Display_Create_UcLate(&chainsObj.ucObj, &chainsObj);
    chains_fastBoot_issIspSimcop_pd_Display_StartApp_UcLate(&chainsObj);

    /* Send command to toggle operation status to all gates */
    System_linkControl(
            chainsObj.ucObj.Gate_algFeatureComputeLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    System_linkControl(
            chainsObj.ucObj.Gate_algCaptureLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    System_linkControl(
            chainsObj.ucObj.Gate_algDrawLinkID,
            GATE_LINK_CMD_SET_OPERATION_MODE_ON,
            NULL,
            0,
            TRUE);

    /* Switch channel from UcEarly to output of the algorithm */
    displayPrm.activeChId = 1;
    System_linkControl(chainsObj.ucObj.Display_VideoLinkID,
                    DISPLAY_LINK_CMD_SWITCH_CH,
                    &displayPrm,
                    sizeof(displayPrm),
                    TRUE);
    poweOnToAlg = Utils_getCurGlobalTimeInMsec();

    snprintf(printPrms.stringInfo.string,
             sizeof(printPrms.stringInfo.string) - 1,
             "Boot Time: Power On To Preview %d ms, Power On To Obj Detect %d ms!!!", poweOnToDisplay, poweOnToAlg);

    chains_fastBoot_issIspSimcop_pd_Display_CreateAndStart_GrpxSrc(&chainsObj.ucObj);
    printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
    printPrms.duration_ms = GRPX_BOOT_TIME_DISPLAY_DURATION;
    printPrms.stringInfo.fontType = GRPX_BOOT_TIME_DISPLAY_FONTID;
    printPrms.stringInfo.startX   = GRPX_BOOT_TIME_DISPLAY_X_OFFSET;
    printPrms.stringInfo.startY   = chainsObj.displayHeight-GRPX_BOOT_TIME_DISPLAY_Y_OFFSET;

    System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                       GRPX_SRC_LINK_CMD_PRINT_STRING,
                       &printPrms,
                       sizeof(printPrms),
                       TRUE);
    chains_fastBootDisplayAnalyticsState (&chainsObj);
    /* Post this point do not load code when the DSP and EVE are being rebooted */
    bootParams.loadCode = (Bool)FALSE;
#ifdef ANALYTICS_AUTOMATIC_ON_OFF
    ch = '3';
#endif
    while(!done)
    {
#ifndef ANALYTICS_AUTOMATIC_ON_OFF
        Vps_printf(gChains_FastBootIssIspSimcop_Pd_Display_runTimeMenu);
        ch = Chains_readChar();
#else
        if (ch == '3')
            ch = '4';
        else
            ch = '3';
        BspOsal_sleep(ANALYTICS_TIME_ON_OFF);
#endif
        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                {
                /* Send command to Capture Link to save a frame */
                UInt32 chId = 0U;
                System_linkControl(
                        chainsObj.ucObj.IssCaptureLinkID,
                        ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                        &chId,
                        sizeof(chId),
                        TRUE);
                break;
                }
            case '2':
                /* Send command to Capture Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mSimcopLinkID,
                        ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                break;
            case '3':
                /* Only if the analytics is off then start the power up */
                if (ANALYTICS_OFF == chainsObj.analyticsState)
                {
                    chains_fastBoot_switchDspEveOn(&chainsObj, &bootParams);
                    chains_fastBootDisplayAnalyticsState(&chainsObj);
                }
                else
                {
                    Vps_printf(" CHAINS: Object Detection already enabled\n\r");
                }
                break;
            case '4':
                if (ANALYTICS_ON == chainsObj.analyticsState)
                {
                    chains_fastBoot_switchDspEveOff(&chainsObj);
                    chains_fastBootDisplayAnalyticsState(&chainsObj);
                }
                else
                {
                    Vps_printf(" CHAINS: Object Detection already disabled\n\r");
                }
            break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_fastBoot_issIspSimcop_pd_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    if (ANALYTICS_ON == chainsObj.analyticsState)
    {
        chains_fastBoot_issIspSimcop_pd_Display_StopAndDeleteApp_UcLate(&chainsObj);
    }

    chains_fastBoot_issIspSimcop_pd_Display_StopAndDeleteApp(&chainsObj);

}

