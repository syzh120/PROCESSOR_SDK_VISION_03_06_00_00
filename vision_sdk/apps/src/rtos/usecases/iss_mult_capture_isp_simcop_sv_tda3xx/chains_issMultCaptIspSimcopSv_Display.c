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
#include "chains_issMultCaptIspSimcopSv_Display_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>

#define SV_ISP_LDC_MESH_TABLE_PITCH(w, r) \
                                        ((((((w)/(r))+1) + 15U) & ~15U) * (4U))

/* Sensor Output Frm Size */
#define SV_CAPT_SENSOR_AR140_WIDTH      (1280U)
#define SV_CAPT_SENSOR_AR140_HEIGHT     (800U)

/* ISP Output Frm Size */
#define SV_ISP_OUTPUT_WIDTH             (SV_CAPT_SENSOR_AR140_WIDTH)
#define SV_ISP_OUTPUT_HEIGHT            (800U)

/* LDC Frm size and other parameters */
#define SV_CH0_CH2_LDC_OUTPUT_WIDTH     (1280U)
#define SV_CH0_CH2_LDC_OUTPUT_HEIGHT    (280U)
#define SV_CH0_CH2_LDC_BLOCK_WIDTH      (16U)
#define SV_CH0_CH2_LDC_BLOCK_HEIGHT     (20U)

#define SV_CH1_CH3_LDC_OUTPUT_WIDTH     (560U)
#define SV_CH1_CH3_LDC_OUTPUT_HEIGHT    (720U)
#define SV_CH1_CH3_LDC_BLOCK_WIDTH      (16U)
#define SV_CH1_CH3_LDC_BLOCK_HEIGHT     (20U)

#define SV_CH1_CH3_LDC_INPUT_WIDTH      (SV_CAPT_SENSOR_AR140_WIDTH)
#define SV_CH1_CH3_LDC_INPUT_HEIGHT     (SV_CH1_CH3_LDC_OUTPUT_HEIGHT)

/* SRV Car Box Size */
#define SV_CARBOX_WIDTH                 (160U)
#define SV_CARBOX_HEIGHT                (240U)

/* SRV Num Views/Channels */
#define SV_NUM_VIEWS                    (4U)

/* SRV Output Frm Size */
#define SV_HOR_WIDTH                    (1280U)
#define SV_HOR_HEIGHT                   (720U)

/* SRV Output Frm Size for LDC Lut calculation */
#define SV_LDC_LUT_FRM_WIDTH            (1280U)
#define SV_LDC_LUT_FRM_HEIGHT           (800U)

#define SV_ALGO_ALIGN_IGNORE_FIRST_N_FRAMES (50U)
#define SV_ALGO_ALIGN_DEFAULT_FOCAL_LENGTH  (407U)

#define SIMCOP_OUTPUT_NUM_BUFFERS       (6U)
#define ISP_OUTPUT_NUM_BUFFERS          (4U)

//#define ENABLE_WDR_MERGE_PARAMS_CFG

/**
 *******************************************************************************
 *
 *  \brief  chains_issMultCaptIspSimcopSv_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issMultCaptIspSimcopSv_DisplayObj ucObj;

    AppUtils_Obj                    appObjPrms;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;

    UInt32  numCh;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    /* Not used for now */
    IssM2mSimcopLink_OperatingMode simcopMode;
    Bool bypassVtnf;
    Bool bypassLdc;

} chains_issMultCaptIspSimcopSv_DisplayAppObj;


char gChains_IssMultCaptIspSimcopSv_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n 1: Camera Position Calibration"
"\r\n 2: Save a captured RAW frame from channel 0"
"\r\n 3: Save a Simcop Output Frame"
"\r\n "
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

static Void chains_issMultCaptIspSimcopSv_Display_SetSyncPrm(
                    SyncLink_CreateParams *pGaPrm,
                    SyncLink_CreateParams *pSyncPrm,
                    UInt32 numCh,
                    UInt32 syncPeriod)
{
    pGaPrm->syncDelta =35U; /* round up 1 / 27.0 */
    pGaPrm->syncThreshold = pGaPrm->syncDelta * 2U;

    pSyncPrm->syncDelta = 35U; /* round up 1 / 27.0 */
    pSyncPrm->syncThreshold = pSyncPrm->syncDelta * 2U;;
}

#ifdef ENABLE_WDR_MERGE_PARAMS_CFG
/* Function to get the exposure parameters from the sensor and update
   the merge parameters in the ISP. Called only when WDR merge is enabled. */
static Void chains_issMultCaptIspSimcopSv_Display_Config_Merge(
    AlgorithmLink_IssAewbOutParams *pAewbAlgOut, Ptr pIspCfg, Void *appData)
{
    chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj =
        (chains_issMultCaptIspSimcopSv_DisplayAppObj *)appData;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pAewbAlgOut);

    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    /* Get Exposure ratio parameters from the sensor */
    ChainsCommon_IssGetExposureParams(pAewbAlgOut);

    /* When dgain is applied only to long after split, there is a
        different ratio for split and merge */
    /* setting up merge parameters even for 2 pass wdr mode when AE is
       not enabled because merge parameter calculation uses digital gain
       for the calculation */
    if ((TRUE == pAewbAlgOut->outPrms[0].useAeCfg) ||
        ((TRUE == IssM2mIspLink_IsWdrMergeMode(
            pIssM2mIspPrm->channelParams[0].operatingMode)) &&
         (ALGORITHMS_ISS_AEWB_MODE_AWB == pAlg_IssAewbPrm->mode)))
    {
        System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS,
            pAewbAlgOut,
            sizeof(IssAewbAlgOutParams),
            TRUE);
    }
}
#endif


static Void chains_issMultCaptIspSimcopSv_Display_SetIspConfig(
            chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj)
{
    Int32 status;
    UInt32 numCh;

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

    /* Changing Simcop Configuration as required for this usecase */
    if (pObj->bypassLdc == TRUE)
    {
        pObj->ldcCfg.pixelPad = 0;
    }
    else
    {
        pObj->ldcCfg.pixelPad = 4U;
    }
    pObj->ldcCfg.advCfg.outputBlockWidth = 64;
    pObj->ldcCfg.advCfg.outputBlockHeight = 32;
    //pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BICUBIC;

    /* MUST be called after link create and before link start */
    /* Apply the same config to all channel,
        right now the sensor are the same so its fine. */
    for (numCh = 0U; numCh < pObj->ucObj.IssCapturePrm.numCh; numCh++)
    {
        pObj->simcopConfig.chNum = numCh;

        pObj->ldcCfg.lutCfg.downScaleFactor =
                                            VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
        pObj->ldcCfg.lutCfg.lineOffset =
                    SV_ISP_LDC_MESH_TABLE_PITCH(SV_ISP_OUTPUT_WIDTH, \
                                (1U << pObj->ldcCfg.lutCfg.downScaleFactor));

        if (numCh == 0 || numCh == 2)
        {
            pObj->ldcCfg.advCfg.outputFrameWidth = SV_CH0_CH2_LDC_OUTPUT_WIDTH;
            pObj->ldcCfg.advCfg.outputFrameHeight = SV_CH0_CH2_LDC_OUTPUT_HEIGHT;
            pObj->ldcCfg.advCfg.outputBlockWidth = SV_CH0_CH2_LDC_BLOCK_WIDTH;
            pObj->ldcCfg.advCfg.outputBlockHeight = SV_CH0_CH2_LDC_BLOCK_HEIGHT;

        }
        else
        {
            pObj->ldcCfg.advCfg.outputFrameWidth = SV_CH1_CH3_LDC_OUTPUT_WIDTH;
            pObj->ldcCfg.advCfg.outputFrameHeight = SV_CH1_CH3_LDC_OUTPUT_HEIGHT;
            pObj->ldcCfg.advCfg.outputBlockWidth = SV_CH1_CH3_LDC_BLOCK_WIDTH;
            pObj->ldcCfg.advCfg.outputBlockHeight = SV_CH1_CH3_LDC_BLOCK_HEIGHT;

        }

        /* MUST be called after link create and before link start */
        status = System_linkControl(
                pObj->ucObj.IssM2mSimcopLinkID,
                ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
                &pObj->simcopConfig,
                sizeof(pObj->simcopConfig),
                TRUE);
        UTILS_assert(0 == status);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Update ISS Capture and ISP parameters for multi channel support
 *
 *******************************************************************************
*/
static Void updateCaptureIspPrm(
            chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj,
            UInt32 rszAOutWidth,
            UInt32 rszAOutHeight)
{
    UInt32 ch;
    IssCaptureLink_CreateParams *pCapturePrm = &pObj->ucObj.IssCapturePrm;
    IssCaptureLink_OutParams *pOutPrm0, *pOutPrm;
    IssM2mIspLink_CreateParams *pIspPrm = &pObj->ucObj.IssM2mIspPrm;

    pCapturePrm->numCh = pObj->numCh;
    pOutPrm0 = &pCapturePrm->outParams[0U];

    pIspPrm->channelParams[0U].outParams.widthRszA = rszAOutWidth;
    pIspPrm->channelParams[0U].outParams.heightRszA = rszAOutHeight;

    /* Disable Resizer B */
    pIspPrm->channelParams[0U].\
                        enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;

    for(ch = 1;ch < pCapturePrm->numCh;ch++)
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

        pIspPrm->channelParams[ch].outParams.widthRszA = rszAOutWidth;
        pIspPrm->channelParams[ch].outParams.heightRszA = rszAOutHeight;

        /* Disable Resizer B */
        pIspPrm->channelParams[ch].\
                            enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set the pin mux for the TDA3X EVM
 *
 *******************************************************************************
*/
static setMuxes(chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    /* Mux is configured only on TDA3X EVM */
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
#endif
}

Void chains_issMultCaptIspSimcopSv_Display_SetAppPrms(chains_issMultCaptIspSimcopSv_DisplayObj *pUcObj, Void *appObj)
{
    UInt32 numCh;
    chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj
        = (chains_issMultCaptIspSimcopSv_DisplayAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;
    Int16 carBoxWidth;
    Int16 carBoxHeight;

    pObj->captureOutWidth  = SV_CAPT_SENSOR_AR140_WIDTH;
    pObj->captureOutHeight = SV_CAPT_SENSOR_AR140_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC;
    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = FALSE;

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    ispOpMode = pObj->chainsCfg->ispOpMode;

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = pObj->numCh;
    pObj->appObjPrms.ispOpMode = ispOpMode;
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

    /*  Override the capture and ISP parameters for multi channel and
        disable resizer B */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight);


    /* AEWB parameters */
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_gaPrm, pUcObj->IssCapturePrm.numCh, 1); /* 1: Tight Sync */

    /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight,
                                    ALGORITHM_LINK_SRV_OUTPUT_2D_LDC);

    /* Display */
    ChainsCommon_SurroundView_SetDisplayPrm(
                                    &pUcObj->Display_VideoPrm,
                                    NULL,
                                    NULL,
                                    &pUcObj->Display_GrpxPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    ChainsCommon_StartDisplayCtrl(
                                    pObj->chainsCfg->displayType,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    carBoxWidth = SV_CARBOX_WIDTH;
    carBoxHeight = SV_CARBOX_HEIGHT;

    chains_issMultCaptIspSimcopSv_Display_SetSyncPrm(
                    &pUcObj->Sync_gaPrm,
                    &pUcObj->Sync_synPrm,
                    pUcObj->IssCapturePrm.numCh, 0x0); /* Sync period not used
                                                            in this func now */

    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                            SV_ISP_OUTPUT_WIDTH,
                                            SV_ISP_OUTPUT_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D_LDC,
                                            TRUE); /* Enable CAR overlay */
    /* Set the LDC Input Frame size parameters in Synthesys */
    for (numCh = 0U; numCh < pUcObj->IssCapturePrm.numCh; numCh ++)
    {
        if (numCh == 0 || numCh == 2)
        {
            pUcObj->Alg_SynthesisPrm.ldcFrmWidth[numCh] =
                SV_CH0_CH2_LDC_OUTPUT_WIDTH;
            pUcObj->Alg_SynthesisPrm.ldcFrmHeight[numCh] =
                SV_CH0_CH2_LDC_OUTPUT_HEIGHT;
        }
        else
        {
            pUcObj->Alg_SynthesisPrm.ldcFrmWidth[numCh] =
                SV_CH1_CH3_LDC_OUTPUT_WIDTH;
            pUcObj->Alg_SynthesisPrm.ldcFrmHeight[numCh] =
                SV_CH1_CH3_LDC_OUTPUT_HEIGHT;
        }
    }

    ChainsCommon_SurroundView_SetGAlignParams(&pUcObj->Alg_GeoAlignPrm,
                                            SV_ISP_OUTPUT_WIDTH,
                                            SV_ISP_OUTPUT_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D_LDC);
    pUcObj->Alg_GeoAlignPrm.ldcLutOnlyMode = TRUE;
    pUcObj->Alg_GeoAlignPrm.ldcOutFrmWidth = SV_LDC_LUT_FRM_WIDTH;
    pUcObj->Alg_GeoAlignPrm.ldcOutFrmHeight = SV_LDC_LUT_FRM_HEIGHT;
    pUcObj->Alg_GeoAlignPrm.ldcDownScaleFactor =
        VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
    pUcObj->Alg_GeoAlignPrm.numOutputTables = 2U;

    /* Override parameters specific to this use case */
    pUcObj->Alg_GeoAlignPrm.ignoreFirstNFrames =
                                    SV_ALGO_ALIGN_IGNORE_FIRST_N_FRAMES;
    pUcObj->Alg_GeoAlignPrm.defaultFocalLength =
                                    SV_ALGO_ALIGN_DEFAULT_FOCAL_LENGTH;

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                            /*SV_CAPT_SENSOR_AR140_WIDTH,
                                            SV_ISP_OUTPUT_HEIGHT,*/
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_HOR_WIDTH,
                                            SV_HOR_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D_LDC);


    for (numCh = 0U; numCh < pUcObj->IssCapturePrm.numCh; numCh ++)
    {
        pUcObj->IssM2mSimcopPrm.channelParams[numCh].useOutputFrameSize = TRUE;

        if (numCh == 0 || numCh == 2)
        {
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].outputFrameWidth =
                SV_CH0_CH2_LDC_OUTPUT_WIDTH;
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].outputFrameHeight =
                SV_CH0_CH2_LDC_OUTPUT_HEIGHT;
        }
        else
        {
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].outputFrameWidth =
                SV_CH1_CH3_LDC_OUTPUT_WIDTH;
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].outputFrameHeight =
                SV_CH1_CH3_LDC_OUTPUT_HEIGHT;

            /* Change input frame size also for channel 1 and 3 */
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].overrideInFrmSize =
                FALSE;

            pUcObj->IssM2mSimcopPrm.channelParams[numCh].inputFrameWidth =
                SV_CH1_CH3_LDC_INPUT_WIDTH;
            pUcObj->IssM2mSimcopPrm.channelParams[numCh].inputFrameHeight =
                SV_CH1_CH3_LDC_INPUT_HEIGHT;

            /* Change maximum output buffer size in the ISP link as well */
            pUcObj->IssM2mIspPrm.channelParams[numCh].useBufSizePrmsFlag = FALSE;
            pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufWidth = SV_CH1_CH3_LDC_INPUT_WIDTH;
            pUcObj->IssM2mIspPrm.channelParams[numCh].maxBufHeight = SV_CH1_CH3_LDC_INPUT_HEIGHT;
        }

        pUcObj->IssM2mSimcopPrm.channelParams[numCh].numBuffersPerCh =
            SIMCOP_OUTPUT_NUM_BUFFERS;
        pUcObj->IssM2mIspPrm.channelParams[numCh].numBuffersPerCh =
            ISP_OUTPUT_NUM_BUFFERS;
    }

    pUcObj->GrpxSrcPrm.displaySrv2D.startX = 0U;
    pUcObj->GrpxSrcPrm.displaySrv2D.startY = 0U;
    pUcObj->GrpxSrcPrm.displaySrv2D.width = SV_HOR_WIDTH;
    pUcObj->GrpxSrcPrm.displaySrv2D.height = SV_HOR_HEIGHT;
    pUcObj->GrpxSrcPrm.displaySrv2D.srvOutWidth = SV_HOR_WIDTH;
    pUcObj->GrpxSrcPrm.displaySrv2D.srvOutHeight = SV_HOR_HEIGHT;
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
 * \param   pObj  [IN] chains_issMultCaptIspSimcopSv_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspSimcopSv_Display_StartApp(chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_issMultCaptIspSimcopSv_Display_SetIspConfig(pObj);

    setMuxes(pObj);

    appStartIssSensorSerDes(&pObj->appObjPrms);

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issMultCaptIspSimcopSv_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_issMultCaptIspSimcopSv_DisplayAppObj
 *
 *******************************************************************************
*/
static Void chains_issMultCaptIspSimcopSv_Display_StopAndDeleteApp(chains_issMultCaptIspSimcopSv_DisplayAppObj *pObj)
{
    chains_issMultCaptIspSimcopSv_Display_Stop(&pObj->ucObj);
    chains_issMultCaptIspSimcopSv_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    appStopISSSensor(&pObj->appObjPrms);
    appDeleteISSSensor(&pObj->appObjPrms);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   4 Channel surround view usecase entry function
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void Chains_issMultCaptIspSimcopSv_Display(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE, chId, validChId = 0;
    Bool startWithCalibration;
    chains_issMultCaptIspSimcopSv_DisplayAppObj chainsObj;

    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */
    chainsObj.numCh = 4U;

    if ((ISSM2MISP_LINK_OPMODE_1PASS_WDR != chainsCfg->ispOpMode) &&
        (ISSM2MISP_LINK_OPMODE_12BIT_LINEAR != chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: WDR should either be disabled or "
                    "in One Pass mode!!!\n");
        return;
    }

    chainsCfg->displayType = CHAINS_DISPLAY_TYPE_HDMI_720P;
    chainsObj.chainsCfg = chainsCfg;

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);
        chains_issMultCaptIspSimcopSv_Display_Create(&chainsObj.ucObj, &chainsObj);
        chains_issMultCaptIspSimcopSv_Display_StartApp(&chainsObj);

        ch = 'a';
        chPrev = '1';
        do
        {
            Vps_printf(gChains_IssMultCaptIspSimcopSv_Display_runTimeMenu);

            ch = Chains_readChar();

            switch(ch)
            {
                case '0':
                    done = TRUE;
                    chPrev = '3';
                    break;
                case '1':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case '2':
                    chId = 0U;
                    System_linkControl(
                            chainsObj.ucObj.IssCaptureLinkID,
                            ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                            &chId,
                            sizeof(chId),
                            TRUE);
                    break;

                case '3':
                    validChId = 0U;
                    do
                    {
                        Vps_printf("Enter Channel Id [0:%d]:",
                            chainsObj.ucObj.IssCapturePrm.numCh - 1);
                        ch = Chains_readChar();

                        chId = ch - '0';

                        if (chId < chainsObj.ucObj.IssCapturePrm.numCh)
                        {
                            validChId = 1U;
                        }
                    } while (!validChId);

                    /* Send command to Capture Link to save a frame */
                    System_linkControl(
                            chainsObj.ucObj.IssM2mSimcopLinkID,
                            ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME,
                            &chId,
                            0,
                            TRUE);
                    break;

                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_issMultCaptIspSimcopSv_Display_printStatistics(
                                    &chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        } while ((chPrev!='3') && (FALSE == done));

        chains_issMultCaptIspSimcopSv_Display_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
        Task_sleep(100);
        Vps_printf("\n Restarting...\n");

    } while (chPrev!='3');
}

