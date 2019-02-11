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
#include "chains_issMultiInstCapture_Display_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>

#define NUM_CHANNELS           (4)
#define NUM_CHANNELS_ON_PHY1   (2)

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

    chains_issMultiInstCapture_DisplayObj  ucObj;

    vpsissldcConfig_t               ldcCfg;
    vpsissvtnfConfig_t              vtnfCfg;

    UInt32                          captureOutWidth;
    UInt32                          captureOutHeight;
    UInt32                          displayWidth;
    UInt32                          displayHeight;

    Chains_Ctrl                    *chainsCfg;

    Bool                            bypassVtnf;
    Bool                            bypassLdc;

    AppUtils_Obj             appSensInfo;
    IssM2mSimcopLink_ConfigParams simcopConfig;

} chains_issMultiInstCapture_DisplayAppObj;


char gChains_issMultiInstCapture_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n 1: Switch Channel"
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
 *          chains_issMultiInstCapture_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/

Void chains_issMultiInstCapture_Display_SetSelectParam(SelectLink_CreateParams* pPrm, UInt32 chId)
{
    pPrm->numOutQue = 1U;

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 1;
    pPrm->outQueChInfo[0].inChNum[0] = chId;

}

Void chains_issMultiInstCapture_Display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    Chains_DisplayType displayType,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    UInt32 dispWidth, dispHeight;

    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        /* To maintain the aspect ratio, change the display tarWidth */
        dispWidth = captureWidth * displayHeight / captureHeight;
        dispHeight = displayHeight;

        if (dispWidth > displayWidth)
        {
            dispWidth = displayWidth;
            dispHeight = displayWidth * captureHeight / captureWidth;
        }


        pPrm_Video->rtParams.tarWidth  = dispWidth;
        pPrm_Video->rtParams.tarHeight = dispHeight;
        pPrm_Video->rtParams.posX      = (displayWidth - dispWidth) / 2U;
        pPrm_Video->rtParams.posY      = (displayHeight - dispHeight) / 2U;

        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
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


Void chains_issMultiInstCapture_Display_SetIspConfig(
            chains_issMultiInstCapture_DisplayAppObj *pObj)
{
    appSetDefaultIspParams(&pObj->appSensInfo);
    appSetIspParamsFromDCC(&pObj->appSensInfo);

    /* Initialize Simcop Configuration */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Initializes ISP and Simcop Configurations to the default values,
       Mainly used for initializing LDC configuration */
    IssUtils_InitSimcopConfig(
            &pObj->simcopConfig,
            TRUE,       /* bypassLdc */
            TRUE);      /* bypassVtnf */
}

Void chains_issMultiInstCapture_Display_setMuxes(
            chains_issMultiInstCapture_DisplayAppObj *pObj)
{
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
}

Void setSyncLinkParams(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 syncPeriod)
{
    pPrm->syncDelta = 0x7FFFFFFF;
    pPrm->syncThreshold = 0x7FFFFFFF;
}

Void setDmaSwMsLinkParams(
                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 winWidth,
                    UInt32 winHeight,
                    UInt32 outWidth,
                    UInt32 outHeight)
{
    UInt32 algId, winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    useLocalEdma = FALSE;
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->baseClassCreate.algId   = algId;
#ifndef TDA3XX_128MB_DDR
    pPrm->numOutBuf               = 4U;
#else
    pPrm->numOutBuf               = 2U;
#endif
    pPrm->useLocalEdma            = useLocalEdma;
    pPrm->initLayoutParams.numWin = numCh;

    pPrm->maxOutBufWidth     = outWidth;
    pPrm->maxOutBufHeight    = outHeight;

    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
        pWinInfo->chId = winId;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width    = winWidth;
        pWinInfo->height   = winHeight;

        /*
         *  For 4x4 layout
         */
        switch(winId)
        {
            default:
            case 0:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = 0;
                break;
            case 1:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = 0;
                break;
            case 2:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = winHeight;
                break;
            case 3:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = winHeight;
                break;
        }
    }

    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;
}

static Void updateCaptureIspPrm(
            chains_issMultiInstCapture_DisplayAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight,
            UInt32 rszBOutWidth,
            UInt32 rszBOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucObj.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucObj.IssM2mIspPrm;
    UInt32 inCsi2_0VirtualChNum = 0;
    UInt32 inCsi2_1VirtualChNum = 0;

    pCapturePrm->numCh = NUM_CHANNELS;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;
    pIspPrm->channelParams[0U].outParams.widthRszB = rszBOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszB = rszBOutHeight;

    for(ch = 0;ch < pCapturePrm->numCh;ch++)
    {
        pOutPrm = &pCapturePrm->outParams[ch];

        pOutPrm->dataFormat = pOutPrm0->dataFormat;
        pOutPrm->width = pOutPrm0->width;
        pOutPrm->height = pOutPrm0->height;
        pOutPrm->maxWidth = pOutPrm0->maxWidth;
        pOutPrm->maxHeight = pOutPrm0->maxHeight;
        pOutPrm->numOutBuf = pOutPrm0->numOutBuf;
        pOutPrm->inCsi2DataFormat = pOutPrm0->inCsi2DataFormat;
        pOutPrm->inCsi2VirtualChanNum = ch;

        if(ch >= pCapturePrm->numCh - NUM_CHANNELS_ON_PHY1)
        {
            /*
             * Set the phyInstance to 1 and set csi2 virtual channel number
             * when we are using second csi2 phy instance.
             */
            pOutPrm->phyInstance = 1U;
            pOutPrm->inCsi2VirtualChanNum = inCsi2_1VirtualChNum++;
        }
        else
        {
            pOutPrm->phyInstance = 0U;
            pOutPrm->inCsi2VirtualChanNum = inCsi2_0VirtualChNum++;
        }

        pIspPrm->channelParams[ch].outParams.widthRszA = rszAOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszA = rszAOutHeight;
        pIspPrm->channelParams[ch].outParams.widthRszB = rszBOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszB = rszBOutHeight;
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
Void chains_issMultiInstCapture_Display_SetAppPrms(
    chains_issMultiInstCapture_DisplayObj *pUcObj, Void *appObj)
{
    UInt32 numCh =0;
    chains_issMultiInstCapture_DisplayAppObj *pObj
        = (chains_issMultiInstCapture_DisplayAppObj*)appObj;

//    UInt32 swMsWinWidth,swMsWinHeight;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->bypassVtnf = FALSE;
    pObj->bypassLdc  = FALSE;

    if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
        (pObj->chainsCfg->issVtnfEnable == TRUE))
    {
        pObj->bypassVtnf = FALSE;
        pObj->bypassLdc  = TRUE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == TRUE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = FALSE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = TRUE;
    }

    /* Create the sensor now */
    strncpy(pObj->appSensInfo.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appSensInfo.numCh = NUM_CHANNELS;
    pObj->appSensInfo.ispOpMode = pObj->chainsCfg->ispOpMode;
    pObj->appSensInfo.simcopOpMode = ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;
    pObj->appSensInfo.numCSI2Inst = 2;
    appCreateISSSensor(&pObj->appSensInfo);

    appInitIssCaptParams(&pObj->appSensInfo, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appSensInfo, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appSensInfo, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight);

    pObj->captureOutWidth = pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->captureOutHeight = pUcObj->IssCapturePrm.outParams[0U].height;

    pUcObj->IssCapturePrm.outParams[0U].phyInstance = 1U;

    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight,
                1280,
                720);

    chains_issMultiInstCapture_Display_SetSelectParam(&pUcObj->SelectPrm, 0);

#if 0
    swMsWinWidth = pObj->displayWidth/2;
    swMsWinHeight = pObj->displayHeight/2;


    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight,
                swMsWinWidth,
                swMsWinHeight);


    //Select Params
    pUcObj->SelectPrm.outQueChInfo[0].numOutCh = 1;
    pUcObj->SelectPrm.outQueChInfo[0].outQueId = 0;
    pUcObj->SelectPrm.outQueChInfo[0].inChNum[0] = 0;



    setSyncLinkParams(
                        &pUcObj->SyncPrm,
                        4,
                        0x0);

    /* SW MS link params */
    setDmaSwMsLinkParams(
                        &pUcObj->Alg_DmaSwMsPrm,
                        4,
                        swMsWinWidth,
                        swMsWinHeight,
                        pObj->displayWidth,
                        pObj->displayHeight);
#endif

    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    for (numCh = 0U; numCh < NUM_CHANNELS; numCh ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh = 4;
    }

    chains_issMultiInstCapture_Display_SetDisplayPrms(
        &pUcObj->Display_VideoPrm,
            &pUcObj->Display_GrpxPrm,
            pObj->chainsCfg->displayType,
            pObj->displayWidth,
            pObj->displayHeight,
            pUcObj->IssM2mIspPrm.channelParams[0U].outParams.widthRszA,
            pUcObj->IssM2mIspPrm.channelParams[0U].outParams.heightRszA);

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
 * \param   pObj  [IN] chains_issMultiInstCapture_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_issMultiInstCapture_Display_StartApp(chains_issMultiInstCapture_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_issMultiInstCapture_Display_SetIspConfig(pObj);

    chains_issMultiInstCapture_Display_setMuxes(pObj);

    appStartIssSensorSerDes(&pObj->appSensInfo);

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultiInstCapture_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_issMultiInstCapture_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_issMultiInstCapture_Display_StopAndDeleteApp(chains_issMultiInstCapture_DisplayAppObj *pObj)
{
    chains_issMultiInstCapture_Display_Stop(&pObj->ucObj);
    chains_issMultiInstCapture_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

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
Void Chains_iss_multi_inst_capture_display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_issMultiInstCapture_DisplayAppObj chainsObj;

    UInt32 nextChannel = 0;
    SelectLink_OutQueChInfo  ChannelInfo;


    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */


    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;

    if (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Please make sure BSP is build with WDR and LDC enabled !!!\n");
    }

    chainsObj.chainsCfg = chainsCfg;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_issMultiInstCapture_Display_Create(&chainsObj.ucObj, &chainsObj);
    ChainsCommon_SetIssCaptureErrorHandlingCb(chainsObj.ucObj.IssCaptureLinkID);
    chains_issMultiInstCapture_Display_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_issMultiInstCapture_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                nextChannel = (nextChannel + 1) % NUM_CHANNELS;

                ChannelInfo.outQueId = 0;
                ChannelInfo.numOutCh = 1;
                ChannelInfo.inChNum[0] = nextChannel;

                System_linkControl( chainsObj.ucObj.SelectLinkID,
                                    SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO,
                                    &ChannelInfo, sizeof(SelectLink_OutQueChInfo), TRUE);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_issMultiInstCapture_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_issMultiInstCapture_Display_StopAndDeleteApp(&chainsObj);

}
