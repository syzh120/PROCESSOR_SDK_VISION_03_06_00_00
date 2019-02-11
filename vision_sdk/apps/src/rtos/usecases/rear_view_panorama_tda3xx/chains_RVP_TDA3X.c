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
#include <src/include/chains_common.h>
#include <src/include/chains_common_dewarp.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#include <src/include/chains_common_rsvp.h>
#include <src/include/chains_common_osal.h>
#include "chains_RVP_TDA3X_priv.h"
#include "chains_RVP_TDA3X.h"

/* Capture Resolution of AR0140 sensor */
#define RSVP_UC_3D_CAPT_SENSOR_AR140_WIDTH       (1280U)
#define RSVP_UC_3D_CAPT_SENSOR_AR140_HEIGHT      (800U)

/* Capture Resolution of OV10640 sensor */
#define RSVP_UC_3D_CAPT_SENSOR_OV10640_WIDTH     (1280U)
#define RSVP_UC_3D_CAPT_SENSOR_OV10640_HEIGHT    (720U)

#define TIGHT_SYNC_DELTA_IN_MSEC                                (16)
#define LOOSE_SYNC_DELTA_IN_MSEC                                (0x7FFFFFFF)

#define TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC                       (33)
#define LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC                       (0x7FFFFFFF)

#define CHAINS_COMMON_ISS_MESH_TABLE_PITCH(w, r) ((((((w)/(r))+1) + 15U) & ~15U) * (4U))

/*#pragma DATA_ALIGN(panoramaLeftLUT, 32)
static UInt8 panoramaLeftLUT[] =
{
    #include "panoramaLeftLUT.h"
};

#pragma DATA_ALIGN(panoramaCenterLUT, 32)
static UInt8 panoramaCenterLUT[] =
{
    #include "panoramaCenterLUT.h"
};

#pragma DATA_ALIGN(panoramaRightLUT, 32)
static UInt8 panoramaRightLUT[] =
{
    #include "panoramaRightLUT.h"
};

#pragma DATA_ALIGN(disparityLUT, 32)
static UInt8 disparityLUT[] =
{
    #include "disparityLUT.h"
};*/


#if 0
static char manualRSVPLUTGenMenu[] = {
"\n "
"\n =============================="
"\n Manual RSVP LDC LUT Generation"
"\n =============================="
"\n "
"\n 0: Exit"
"\n 1: Read the Calibration Matrix (CAL MAT) from file"
"\n 2: Compute LDC LUTs for RSVP"
"\n "
"\n Enter Choice: "
"\n "
};
#endif

static Chains_RVPAppObj chainsObj;

Void chains_RVP_TDA3X_Display_SetIspConfig(
            Chains_RVPAppObj *pObj)
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

    pObj->simcopConfig.chNum = 0;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;
    pObj->ldcCfg.advCfg.outputBlockWidth = IMAGETRANSFORM_LDC_BLOCK_WIDTH;
    pObj->ldcCfg.advCfg.outputBlockHeight = IMAGETRANSFORM_LDC_BLOCK_HEIGHT;
    pObj->ldcCfg.advCfg.outputFrameWidth = SIMCOP_OUTPUT_WIDTH;
    pObj->ldcCfg.advCfg.outputFrameHeight = SIMCOP_OUTPUT_HEIGHT;
    pObj->ldcCfg.lutCfg.downScaleFactor  = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
    pObj->ldcCfg.lutCfg.lineOffset       = CHAINS_COMMON_ISS_MESH_TABLE_PITCH(SIMCOP_OUTPUT_WIDTH,
                1 << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8);

    pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
    pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
    pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;
    pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
    pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);

    status = System_linkControl(pObj->ucObj.Alg_DeWarp_ImageTransformLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pObj->simcopConfig.chNum = 1;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;
    pObj->ldcCfg.advCfg.outputBlockWidth = IMAGETRANSFORM_LDC_BLOCK_WIDTH_STEREO_L;
    pObj->ldcCfg.advCfg.outputBlockHeight = IMAGETRANSFORM_LDC_BLOCK_HEIGHT_STEREO_L;
    pObj->ldcCfg.advCfg.outputFrameWidth = SIMCOP_OUTPUT_WIDTH;
    pObj->ldcCfg.advCfg.outputFrameHeight = SIMCOP_OUTPUT_HEIGHT;
    pObj->ldcCfg.lutCfg.downScaleFactor  = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
    pObj->ldcCfg.lutCfg.lineOffset       = CHAINS_COMMON_ISS_MESH_TABLE_PITCH(SIMCOP_OUTPUT_WIDTH,
                1 << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8);

    pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
    pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
    pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;
    pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
    pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);

    status = System_linkControl(pObj->ucObj.Alg_DeWarp_ImageTransformLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pObj->simcopConfig.chNum = 2;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;
    pObj->ldcCfg.advCfg.outputBlockWidth = IMAGETRANSFORM_LDC_BLOCK_WIDTH;
    pObj->ldcCfg.advCfg.outputBlockHeight = IMAGETRANSFORM_LDC_BLOCK_HEIGHT;
    pObj->ldcCfg.advCfg.outputFrameWidth = SIMCOP_OUTPUT_WIDTH;
    pObj->ldcCfg.advCfg.outputFrameHeight = SIMCOP_OUTPUT_HEIGHT;
    pObj->ldcCfg.lutCfg.downScaleFactor  = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
    pObj->ldcCfg.lutCfg.lineOffset       = CHAINS_COMMON_ISS_MESH_TABLE_PITCH(SIMCOP_OUTPUT_WIDTH,
                1 << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8);
    pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
    pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
    pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;
    pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
    pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);

    status = System_linkControl(pObj->ucObj.Alg_DeWarp_ImageTransformLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pObj->simcopConfig.chNum = 3;
    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;
    pObj->ldcCfg.advCfg.outputBlockWidth = SIMCOP_STEREO_LDC_BLOCK_WIDTH;
    pObj->ldcCfg.advCfg.outputBlockHeight = SIMCOP_STEREO_LDC_BLOCK_HEIGHT;
    pObj->ldcCfg.advCfg.outputFrameWidth = SIMCOP_STEREO_OUTPUT_WIDTH;
    pObj->ldcCfg.advCfg.outputFrameHeight = SIMCOP_STEREO_OUTPUT_HEIGHT;
    pObj->ldcCfg.lutCfg.downScaleFactor  = VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
    pObj->ldcCfg.lutCfg.lineOffset       = CHAINS_COMMON_ISS_MESH_TABLE_PITCH(SIMCOP_STEREO_OUTPUT_WIDTH,
                1 << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8);

    pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
    pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
    pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;
    pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
    pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);

    status = System_linkControl(pObj->ucObj.Alg_DeWarp_ImageTransformLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    pObj->ldcCfg.lumeIntrType = VPS_ISS_LDC_LUMA_INTRP_BILINEAR;

    for (numCh = 0U; numCh < STEREO_DEWARP_MAX_CH; numCh++)
    {
        pObj->simcopConfig.chNum = numCh;

        pObj->ldcCfg.lutCfg.downScaleFactor = \
                                            VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8;
        pObj->ldcCfg.lutCfg.lineOffset = \
                STEREO_ISP_LDC_MESH_TABLE_PITCH(REMAP_WIDTH, \
                        (1U << pObj->ldcCfg.lutCfg.downScaleFactor));

        pObj->ldcCfg.advCfg.outputFrameWidth = REMAP_WIDTH;
        pObj->ldcCfg.advCfg.outputFrameHeight = REMAP_HEIGHT;

        pObj->ldcCfg.advCfg.outputBlockWidth = STEREO_LDC_BLOCK_WIDTH;
        pObj->ldcCfg.advCfg.outputBlockHeight = STEREO_LDC_BLOCK_HEIGHT;

        pObj->deWarpSimcopCfg.chNum       = pObj->simcopConfig.chNum;
        pObj->deWarpSimcopCfg.ldcConfig   = pObj->simcopConfig.ldcConfig;
        pObj->deWarpSimcopCfg.vtnfConfig  = pObj->simcopConfig.vtnfConfig;
        /* Frame a plugin command and sent it out */
        pObj->deWarpSimcopCfg.baseClassControl.controlCmd
                                            = ALG_LINK_DEWARP_CMD_SET_LDCCONFIG;
        pObj->deWarpSimcopCfg.baseClassControl.size
                                            = sizeof(pObj->deWarpSimcopCfg);
        status = System_linkControl(pObj->ucObj.Alg_DeWarp_RemapLinkID,
                                    ALGORITHM_LINK_CMD_CONFIG,
                                    &pObj->deWarpSimcopCfg,
                                    sizeof(pObj->deWarpSimcopCfg),
                                    TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }
}

static AlgLink_DeWarpViewPointParams *provideViewParams (UInt32 processedCount)
{

    /*
     * Always provide the first view points
     */
    return (&chainsObj.algViewParams[0U]);

}

static AlgLink_DeWarpViewPointParams *provideViewParamsImageTransform (UInt32 processedCount)
{
    return (&chainsObj.algViewParamsImageTransform[0U]);
}

static void setSelectLinkParams(SelectLink_CreateParams *pSelect_VPEPrm,
                                SelectLink_CreateParams *pSelect_PanoramaLeftPrm,
                                SelectLink_CreateParams *pSelect_PanoramaCenterPrm,
                                SelectLink_CreateParams *pSelect_PanoramaRightPrm,
                                SelectLink_CreateParams *pSelect_CapturePrm,
                                SelectLink_CreateParams *pSelect_InitialPrm)
{
    SelectLink_CreateParams *pPrm;

    if(pSelect_VPEPrm){
        pPrm                             = pSelect_VPEPrm;
        pPrm->numOutQue                  = 1U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 1;
        pPrm->outQueChInfo[0].inChNum[0] = 1;}
    if(pSelect_PanoramaLeftPrm){
        pPrm                             = pSelect_PanoramaLeftPrm;
        pPrm->numOutQue                  = 1U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 1;
        pPrm->outQueChInfo[0].inChNum[0] = 0;
        }
    if(pSelect_PanoramaCenterPrm){
        pPrm                             = pSelect_PanoramaCenterPrm;
        pPrm->numOutQue                  = 1U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 1;
        pPrm->outQueChInfo[0].inChNum[0] = 1;
        }
    if(pSelect_PanoramaRightPrm){
        pPrm                             = pSelect_PanoramaRightPrm;
        pPrm->numOutQue                  = 1U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 1;
        pPrm->outQueChInfo[0].inChNum[0] = 3;
        }
    if(pSelect_CapturePrm){
        pPrm                             = pSelect_CapturePrm;
        pPrm->numOutQue                  = 1U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 1;
        pPrm->outQueChInfo[0].inChNum[0] = 2;
    }
    if(pSelect_InitialPrm){
        pPrm                             = pSelect_InitialPrm;
        pPrm->numOutQue                  = 2U;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 4;
        pPrm->outQueChInfo[0].inChNum[0] = 0;
        pPrm->outQueChInfo[0].inChNum[1] = 1;
        pPrm->outQueChInfo[0].inChNum[2] = 2;
        pPrm->outQueChInfo[0].inChNum[3] = 3;

        pPrm->outQueChInfo[1].outQueId   = 1;
        pPrm->outQueChInfo[1].numOutCh   = 1;
        pPrm->outQueChInfo[1].inChNum[0] = 5;
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
            Chains_RVPAppObj *pObj,
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
static setMuxes(Chains_RVPAppObj *pObj)
{
#ifndef BOARD_TYPE_TDA3XX_RVP
    /* Mux is configured only on TDA3X EVM */
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
#endif
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
Void chains_RVP_TDA3X_SetAppPrms( chains_RVP_TDA3XObj *pUcObj, Void *appObj)
{
    Chains_RVPAppObj *pObj = (Chains_RVPAppObj*)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;
    //IssM2mIspLink_WdrOffsetParams_t wdrOffsetPrms;
    UInt32 chId;

    pObj->captureOutWidth  = RSVP_UC_3D_CAPT_SENSOR_OV10640_WIDTH;
    pObj->captureOutHeight = RSVP_UC_3D_CAPT_SENSOR_OV10640_HEIGHT;

    if(0 == strcmp(pObj->chainsCfg->sensorName, SENSOR_APTINA_AR0140_TIDA262))
    {
        pObj->captureOutWidth  = RSVP_UC_3D_CAPT_SENSOR_AR140_WIDTH;
        pObj->captureOutHeight = RSVP_UC_3D_CAPT_SENSOR_AR140_HEIGHT;
    }

    ispOpMode = pObj->chainsCfg->ispOpMode;

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;
    pObj->bypassVtnf = TRUE;
    pObj->bypassLdc  = FALSE;

    ChainsCommon_GetDisplayWidthHeight(pObj->chainsCfg->displayType,
                                       &pObj->displayWidth,
                                       &pObj->displayHeight);

    /* Create the sensor now */
    strncpy(pObj->appObjPrms.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appObjPrms.numCh = pObj->numCh;
    pObj->appObjPrms.ispOpMode = ispOpMode;
    pObj->appObjPrms.simcopOpMode = pObj->simcopMode;
    pObj->appObjPrms.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appObjPrms);

    appInitIssCaptParams(&pObj->appObjPrms, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appObjPrms, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssAewbParams(&pObj->appObjPrms, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    /*  Override the capture and ISP parameters for multi channel and
        disable resizer B */
    updateCaptureIspPrm(
                pObj,
                pObj->captureOutWidth,
                pObj->captureOutHeight);

    // TRUE - will set it only for one channel to be master and control other channels. Currently it is by default camera on chid = 0
    pUcObj->Alg_IssAewbPrm.runAewbOnlyForOneCh = TRUE;
    pUcObj->Alg_IssAewbPrm.chId = 0U;

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    /* deWarp create params */
    pUcObj->Alg_DeWarp_RemapPrm.allocBufferForDump = FALSE;
    for(chId = 0U; chId < STEREO_DEWARP_MAX_CH; chId++)
    {
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].operatingMode
                                                    = ALGLINK_DEWARP_OPMODE_LDC;
    }

    /* deWarp create params */
    pUcObj->Alg_DeWarp_ImageTransformPrm.allocBufferForDump = TRUE;
    for(chId = 0U; chId < IMAGETRANSFORM_MAX_CH; chId++)
    {
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].operatingMode
                                                    = ALGLINK_DEWARP_OPMODE_LDC;
    }

    setSelectLinkParams(NULL,
                        &pUcObj->Select_PanoramaLeftPrm,
                        &pUcObj->Select_PanoramaCenterPrm,
                        &pUcObj->Select_PanoramaRightPrm,
                        NULL,
                        NULL);

    ChainsCommon_RVP_SetParams(NULL, //&pUcObj->CapturePrm,
                                   &pUcObj->Select_SDAInPrm,
                                   NULL, //&pUcObj->Select_ImgTransInPrm,
                                   &pUcObj->Sync_ImageTransformPrm,
                                   &pUcObj->Sync_RemapOutPrm,
                                   NULL, //&pUcObj->VPE_RemapInPrm,
                                   NULL, //&pUcObj->VPE_PostProcOutPrm,
                                   NULL, //&pUcObj->VPE_ImgTransOutPrm,
                                   NULL, //&pUcObj->VPE_ImgTransformInPrm,
                                   &pUcObj->GrpxSrcPrm,
                                   &pUcObj->Display_PanoramaPrm,
                                   NULL,
                                   &pUcObj->Display_GrpxPrm,
                                   NULL, //&pUcObj->Alg_ImageTransformPrm,
                                   &pUcObj->Alg_SeamDetectionPrm,
                                   &pUcObj->Alg_StitchingPrm,
                                   NULL, //&pUcObj->Alg_RemapMergePrm,
                                   &pUcObj->Alg_CensusPrm,
                                   &pUcObj->Alg_DisparityHamDistPrm,
                                   &pUcObj->Alg_StereoPostProcessPrm,
                                   NULL, // Alg_DmaSwMPrm
                                   pObj->chainsCfg->captureSrc,
                                   pObj->chainsCfg->displayType,
                                   1, // stitchingMode
                                   3, // seamDetectionMode
                                   1, // imageTransformMode
                                   TRUE, //enableDisparityLayout
                                   FALSE,
                                   SIMCOP_OUTPUT_WIDTH,
                                   SIMCOP_OUTPUT_HEIGHT); //enableCarOverlay

    /* De Warp */
    pUcObj->Alg_DeWarp_RemapPrm.provideViewPointParams = &provideViewParams;

    pUcObj->Alg_DeWarp_ImageTransformPrm.provideViewPointParams = &provideViewParamsImageTransform;

    /* ISP */
    for (chId = 0U; chId < pUcObj->IssCapturePrm.numCh; chId ++)
    {
        pUcObj->IssM2mIspPrm.channelParams[chId].useBufSizePrmsFlag = TRUE;
        pUcObj->IssM2mIspPrm.channelParams[chId].maxBufWidth =
                                            1280;
        pUcObj->IssM2mIspPrm.channelParams[chId].maxBufHeight =
                                            720;

        pUcObj->IssM2mIspPrm.channelParams[chId].numBuffersPerCh =
            STEREO_ISP_NUM_OUTPUT_BUFS;
    }


    for (chId = 0U; chId < STEREO_DEWARP_MAX_CH; chId ++)
    {
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].numBuffersPerCh =
            STEREO_DEWARP_NUM_OUTPUT_BUFS;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].overrideInFrmSize = TRUE;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].inputFrameWidth =
                                            1280;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].inputFrameHeight =
                                            720;

        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].useMaxOutputFrameSize = FALSE;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].maxOutputFrameWidth =
                                                STEREO_LDC_OUTPUT_WIDTH_MAX;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].maxOutputFrameHeight =
                                                STEREO_LDC_OUTPUT_HEIGHT_MAX;

        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].useOutputFrameSize = FALSE;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].outputFrameWidth =
                                        REMAP_WIDTH;
        pUcObj->Alg_DeWarp_RemapPrm.channelParams[chId].outputFrameHeight =
                                        REMAP_HEIGHT;

    }

    for (chId = 0U; chId < STEREO_DEWARP_MAX_CH; chId ++)
    {
        /* Enable filling of output buffers for the dewarp algorithm */
        /* The filling can be enabled based on the camera */
        pUcObj->Alg_DeWarp_RemapPrm.fillOutBuf[chId] = ALGLINK_DEWARP_FILLTYPE_NONE; //TRUE;
    }

    pUcObj->Alg_DeWarp_RemapPrm.fillValueY = 0x00;
    pUcObj->Alg_DeWarp_RemapPrm.fillValueUV = 0x80;

    /*
     *  A strip which is portion of the output buffer is filled.
     *  1: Whole buffer,2: half of the buffer,4:quarter of the buffer
     */
    pUcObj->Alg_DeWarp_RemapPrm.fillRatio = 8;

    for (chId = 0U; chId < IMAGETRANSFORM_MAX_CH; chId ++)
    {
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].numBuffersPerCh =
            STEREO_DEWARP_NUM_OUTPUT_BUFS;

        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].overrideInFrmSize = TRUE;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].inputFrameWidth =
                                            SIMCOP_INPUT_WIDTH;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].inputFrameHeight =
                                            SIMCOP_INPUT_HEIGHT;

        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].useMaxOutputFrameSize = TRUE;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].maxOutputFrameWidth =
                                                SIMCOP_OUTPUT_WIDTH;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].maxOutputFrameHeight =
                                                SIMCOP_OUTPUT_HEIGHT;

        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].useOutputFrameSize = TRUE;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].outputFrameWidth =
                                        SIMCOP_OUTPUT_WIDTH;
        pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].outputFrameHeight =
                                        SIMCOP_OUTPUT_HEIGHT;

        // Commented out for disparity output of 480x960 (transposed)
        if (chId == 3)
        {
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].overrideInFrmSize = TRUE;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].inputFrameWidth =
                    STEREO_OUTPUT_WIDTH;//REMAP_WIDTH;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].inputFrameHeight =
                    SIMCOP_STEREO_OUTPUT_HEIGHT;//STEREO_OUTPUT_HEIGHT;//REMAP_HEIGHT;

            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].useMaxOutputFrameSize = TRUE;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].maxOutputFrameWidth =
                    SIMCOP_STEREO_OUTPUT_WIDTH;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].maxOutputFrameHeight =
                    SIMCOP_STEREO_OUTPUT_HEIGHT;

            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].useOutputFrameSize = TRUE;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].outputFrameWidth =
                    SIMCOP_STEREO_OUTPUT_WIDTH;
            pUcObj->Alg_DeWarp_ImageTransformPrm.channelParams[chId].outputFrameHeight =
                    SIMCOP_STEREO_OUTPUT_HEIGHT;
        }

        /* Enable filling of output buffers for the dewarp algorithm */
        /* The filling can be enabled based on the camera */
        pUcObj->Alg_DeWarp_ImageTransformPrm.fillOutBuf[chId] = ALGLINK_DEWARP_FILLTYPE_NONE; //ALGLINK_DEWARP_FILLTYPE_NONE;

    }

    pUcObj->Alg_DeWarp_ImageTransformPrm.fillValueY = 0x00;
    pUcObj->Alg_DeWarp_ImageTransformPrm.fillValueUV = 0x80;

    /*
     *  A strip which is portion of the output buffer is filled.
     *  1: Whole buffer,2: half of the buffer,4:quarter of the buffer
     */
    pUcObj->Alg_DeWarp_ImageTransformPrm.fillRatio = 8;
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
 * \param   pObj  [IN] Chains_RVPAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_RVP_TDA3X_StartApp(Chains_RVPAppObj *pObj)
{
    Chains_memPrintHeapStatus();
    chains_RVP_TDA3X_Display_SetIspConfig(pObj);
    setMuxes(pObj);
    appStartIssSensorSerDes(&pObj->appObjPrms);
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    chains_RVP_TDA3X_Start(&pObj->ucObj);
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
 * \param   pObj   [IN]   Chains_RVPAppObj
 *
 *******************************************************************************
*/
Void chains_RVP_TDA3X_StopAndDeleteApp(Chains_RVPAppObj *pObj)
{
    chains_RVP_TDA3X_Stop(&pObj->ucObj);
    chains_RVP_TDA3X_Delete(&pObj->ucObj);
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
Void Chains_RVP_TDA3X(Chains_Ctrl *chainsCfg)
{
    char ch;
    Int32 status;
    UInt32 done = FALSE;
    chainsObj.chainsCfg = chainsCfg;
    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */
    chainsObj.numViewPoints = 1U;
    chainsObj.numViewPointsImageTransform = 1U;
    chainsObj.numCh = 4U;

    // Dewarp for only one view, i.e. right camera in stereo
    memset((void*) &chainsObj.algViewParams, 0,
                    sizeof(AlgLink_DeWarpViewPointParams) * STEREO_MAX_NUM_VIEW_POINTS);
    memset((void*) &chainsObj.ldcMeshTableContainer, 0,
                        sizeof(System_VideoFrameCompositeBuffer) * STEREO_MAX_NUM_VIEW_POINTS);

    // Dewarp for RSVP views
    memset((void*) &chainsObj.algViewParamsImageTransform, 0,
                    sizeof(AlgLink_DeWarpViewPointParams) * IMAGETRANSFORM_MAX_NUM_VIEW_POINTS);
    memset((void*) &chainsObj.ldcMeshTableContainerImageTransform, 0,
                        sizeof(System_VideoFrameCompositeBuffer) * IMAGETRANSFORM_MAX_NUM_VIEW_POINTS);
    Vps_printf(" CHAINS: Initiating read of LDC Look Up Tables from MMC/SD \n");

    /*
     *  The LUT files are present in the RSVP folder
     */
    status = File_chDir(STEREO_DIR_NAME);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: RSVP Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Requires Stereo LDC LUT in RSVP folder \n");
        return;
    }

    // Performs Stereo LDC LUT
    chains_RVP_TDA3X_MediaTask_Stereo(&chainsObj);

    status = File_chDir(RSVP_DIR_NAME);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: RSVP Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Requires RSVP LDC LUTs in RSVP folder \n");
        return;
    }

    // Performs Stereo LDC LUT
    chains_RVP_TDA3X_MediaTask_RSVP(&chainsObj);

    chains_RVP_TDA3X_Create(&chainsObj.ucObj, &chainsObj);
    chains_RVP_TDA3X_StartApp(&chainsObj);
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
                chains_RVP_TDA3X_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
    chains_RVP_TDA3X_StopAndDeleteApp(&chainsObj);

    chains_RVP_TDA3X_FreeBufs(&chainsObj);

    chains_RVP_TDA3X_FreeBufs_RSVP(&chainsObj);

    status = File_chDir("/\0");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}


/**
 *******************************************************************************
 *
 * \brief   Manual RSVP LDC LUT generation
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void manualRSVPLUTGen(Chains_Ctrl *chainsCfg)
{
    char ch;
    Int32 status;
    Bool done = FALSE;
    chainsObj.chainsCfg = chainsCfg;
    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */
    chainsObj.numViewPoints = 1U;
    chainsObj.numViewPointsImageTransform = 1U;
    chainsObj.numCh = 4U;

    // Dewarp for only one view, i.e. right camera in stereo
    memset((void*) &chainsObj.algViewParams, 0,
                    sizeof(AlgLink_DeWarpViewPointParams) * STEREO_MAX_NUM_VIEW_POINTS);
    memset((void*) &chainsObj.ldcMeshTableContainer, 0,
                        sizeof(System_VideoFrameCompositeBuffer) * STEREO_MAX_NUM_VIEW_POINTS);

    // Dewarp for RSVP views
    memset((void*) &chainsObj.algViewParamsImageTransform, 0,
                    sizeof(AlgLink_DeWarpViewPointParams) * IMAGETRANSFORM_MAX_NUM_VIEW_POINTS);
    memset((void*) &chainsObj.ldcMeshTableContainerImageTransform, 0,
                        sizeof(System_VideoFrameCompositeBuffer) * IMAGETRANSFORM_MAX_NUM_VIEW_POINTS);
    Vps_printf(" CHAINS: Initiating read of LDC Look Up Tables from MMC/SD \n");

    /*
     *  The LUT files are present in the RSVP folder
     */
    status = File_chDir(STEREO_DIR_NAME);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: RSVP Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Requires Stereo LDC LUT in RSVP folder \n");
        return;
    }

    // Performs Stereo LDC LUT
    chains_RVP_TDA3X_MediaTask_Stereo(&chainsObj);

    status = File_chDir(RSVP_DIR_NAME);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" CHAINS: RSVP Folder not present in MMC/SD \n");
        Vps_printf(" CHAINS: Requires RSVP LDC LUTs in RSVP folder \n");
        return;
    }

    // Performs Stereo LDC LUT
    chains_RVP_TDA3X_MediaTask_RSVP(&chainsObj);

    chains_RVP_TDA3X_Create(&chainsObj.ucObj, &chainsObj);

    allocRSVPCalibUseCaseBufs(&chainsObj);

    chains_RVP_TDA3X_StartApp(&chainsObj);


#if 0

    do{
        Vps_printf(manualRSVPLUTGenMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                // TBD Write RSVP Function
                readRSVPCalMat(&chainsObj);
                break;
            case '2':
                // TBD Write RSVP Function
                RSVP_generateLDCLUT(&chainsObj);
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    }while (done == FALSE);
#endif

    Vps_printf("RSVP_CALIB: *************************************\n");
    Vps_printf("RSVP_CALIB: Manual Calibration start          ...\n");
    Vps_printf("RSVP_CALIB: *************************************\n");

    // Read Calmat from SD card
    readRSVPCalMat(&chainsObj);

    // Generate LDC LUT for RSVP and store in SD card
    RSVP_generateLDCLUT(&chainsObj);

    Vps_printf("RSVP_CALIB: *************************************\n");
    Vps_printf("RSVP_CALIB: Manual Calibration is completed   ...\n");
    Vps_printf("RSVP_CALIB: *************************************\n");

    Vps_printf("\n Enter '0' to Exit");

    do{
            ch = Chains_readChar();

            switch(ch)
            {
                case '0':
                    done = TRUE;
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n",
                                ch);
                    break;
            }
        }while (done == FALSE);

    chains_RVP_TDA3X_StopAndDeleteApp(&chainsObj);

    freeRSVPCalibUseCaseBufs(&chainsObj);

    chains_RVP_TDA3X_FreeBufs(&chainsObj);

    chains_RVP_TDA3X_FreeBufs_RSVP(&chainsObj);

    status = File_chDir("/\0");
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
}


/**
 *******************************************************************************
 *
 * \brief   Read RSVP Cal Mat from file
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void readRSVPCalMat(
        Chains_RVPAppObj *pObj)
{
    Int32 fp;
    UInt32 cnt, readSize, numCameras;
    UInt32 calMatSize[RSVP_NUM_CAMERAS];
    UInt8 *readAddr;
    char RSVPCalmat_FileName[128U];

    sprintf(RSVPCalmat_FileName,"/%s/%s",\
                    RSVP_DIR_NAME, RSVPCALMAT_FILE);

    Vps_printf("RSVP: => Reading RSVP Cal Mat from %s file ...\n",\
            RSVPCALMAT_FILE);

    fp = ChainsCommon_Osal_fileOpen(RSVPCALMAT_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
    if (-1 != fp)
    {
        ChainsCommon_Osal_fileRead(
                            fp,
                            (UInt8*)&numCameras,
                            4U,
                            &readSize);

        for (cnt = 0U;cnt < numCameras;cnt ++)
        {
            ChainsCommon_Osal_fileRead(
                                fp,
                                (UInt8*)&calMatSize[cnt],
                                4U,
                                &readSize);
        }

        ChainsCommon_Osal_fileSeek(
            fp,
            RSVP_MEDIA_SIZE_METADATA);

        readAddr = (UInt8*)ChainsCommon_Osal_getVirtAddr(
                                    (Int32)pObj->pRVPLdcLutPrm.calmatBuffer);

        for (cnt = 0U;cnt < numCameras;cnt ++)
        {
            ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)readAddr,
                        calMatSize[cnt],
                        &readSize);

            readAddr += calMatSize[cnt];
        }

        ChainsCommon_Osal_fileClose(fp);

        pObj->pRVPLdcLutPrm.isCalMatGenerated = TRUE;
    }
    else
    {
        Vps_printf("RSVP: => RSVPCALMAT.BIN file is NOT present ...\n");
    }
}

/**
 *******************************************************************************
 *
 * \brief   Generate the RSVP LDC LUT from the Cal mat
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Int32 RSVP_generateLDCLUT(
        Chains_RVPAppObj *pObj)
{
    Int32 fp, retVal;
    Int32 status;
    UInt32 lineOffset, lineOffset_trans, ldcLutSize_trans, ldcLutSize;
    UInt32 alignedLdcLutSize_trans, alignedLdcLutSize, rsvpldclutsize;
    char RSVPLUT_FileName[128U];


    sprintf(RSVPLUT_FileName,"/%s/%s",\
                RSVP_DIR_NAME, RSVP_FILENAME_LUT);

    if (TRUE == pObj->pRVPLdcLutPrm.isCalMatGenerated)
    {

        Vps_printf("RSVP: Entering System Link Control ...\n");

        status = System_linkControl(
                SYSTEM_LINK_ID_DSP1,
                TDA3X_RVP_GEN_LDCLUT,
                &pObj->pRVPLdcLutPrm,
                sizeof(AlgorithmLink_ldcLutGenPrm_RVP),
                TRUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        ChainsCommon_Osal_cacheWb(
                            (UInt32)&pObj->pRVPLdcLutPrm,
                            sizeof(AlgorithmLink_ldcLutGenPrm_RVP));

        Vps_printf("RSVP: Writing LDC LUT to file ...\n");

        fp = ChainsCommon_Osal_fileOpen(RSVP_FILENAME_LUT, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
        UTILS_assert (-1 != fp);


        lineOffset = (SIMCOP_OUTPUT_WIDTH /
                        (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
        lineOffset += 15;
        lineOffset &= ~0xF;
        lineOffset *= 4;

        ldcLutSize = lineOffset * ((SIMCOP_OUTPUT_HEIGHT /
                                        (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                        + 1U);

        alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);

        rsvpldclutsize = (alignedLdcLutSize * (RSVP_NUM_CAMERAS-1));

        // Add transposed stereo disparity dewarp table size to rawmemsize
        lineOffset_trans = (SIMCOP_STEREO_OUTPUT_WIDTH /
                                  (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
        lineOffset_trans += 15;
        lineOffset_trans &= ~0xF;
        lineOffset_trans *= 4;

        ldcLutSize_trans = lineOffset_trans * ((SIMCOP_STEREO_OUTPUT_HEIGHT /
                                  (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                  + 1U);

        alignedLdcLutSize_trans = SystemUtils_align(ldcLutSize_trans, 128U);

        /* raw mem size */
        rsvpldclutsize += (alignedLdcLutSize_trans); // Add size of LUT used for transposed stereo right camera


        /* Write the RSVP LDC LUT on MMC/SD card */
        ChainsCommon_Osal_fileWrite(
                fp,
                (UInt8*)ChainsCommon_Osal_getVirtAddr((UInt32)pObj->pRVPLdcLutPrm.combinedLDCLUTRVP),
                2*rsvpldclutsize*sizeof(Int16));

        ChainsCommon_Osal_fileClose(fp);

        Vps_printf("RSVP: Writing RSVP LDC LUT to file DONE\n");

        retVal = 0;
    }
    else
    {
        Vps_printf("RSVP: The CAL MAT is not generated\n");
        Vps_printf("RSVP: Use option # 1 to generate CAL MAT\n");

        retVal = -1;
    }

    return (retVal);
}


/**
 *******************************************************************************
 *
 * \brief   Allocate the buffers used in the RSVP Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/

Void allocRSVPCalibUseCaseBufs(Chains_RVPAppObj *pObj)
{
    UInt32 cnt;
    //Int32 defaultcalmatin_rsvp[] = {-9.055417e-01, 8.080694e-02, 4.164906e-01, -4.175938e-01, 3.538566e-03, -9.086269e-01, -7.489714e-02, -9.967235e-01, 3.054016e-02, 6.492114e+02, 7.909068e+01, 4.580658e+02, -9.999880e-01, -4.661520e-03, -1.487944e-03, 1.613877e-03, -2.712922e-02, -9.996306e-01, 4.619431e-03, -9.996211e-01, 2.713642e-02, 2.886056e+02, 1.154385e+02, 3.957130e+02, -9.079233e-01, -8.471370e-02, -4.104861e-01, 4.081010e-01, 4.457817e-02, -9.118478e-01, 9.554472e-02, -9.954076e-01, -5.901817e-03, -1.075604e+02, 9.596374e+01, 7.102587e+02, -9.998497e-01, 6.463793e-03, 1.608549e-02, -1.626361e-02, -2.852053e-02, -9.994609e-01, -6.001542e-03, -9.995723e-01, 2.862137e-02, 3.086221e+02, 1.136188e+02, 3.927761e+02};
    Int32 defaultcalmatin_rsvp[] = {-1015414148, 43762898, 346324158, -347293783, -19074027, -1015846797, -35251121, -1072680052, 32192673, 617831, 112477, 538155, -1073692905, -8622119, -5541515, 5711136, -21235789, -1073516618, 8510714, -1073497184, 21280681, 285798, 117090, 407788, -1018756899, -81844565, -329176781, 331284462, -16296768, -1021227950, 72845667, -1070493992, 40713956, -55516, 143961, 722636, -1073633325, 107884, 15263544, -15262346, -23030273, -1073386311, 219533, -1073494806, 23029479, 306924, 117346, 403351};
    UInt32 lineOffset, lineOffset_trans, ldcLutSize_trans, ldcLutSize;
    UInt32 alignedLdcLutSize_trans, alignedLdcLutSize, rsvpldclutsize;


    // Initializing structure variables

    // RSVP Output Size
    pObj->pRVPLdcLutPrm.numCameras = RSVP_NUM_CAMERAS;
    pObj->pRVPLdcLutPrm.LDC_subsamplefactor = LDCSUBSAMPLEFACTOR;


    //Input frame size
    pObj->pRVPLdcLutPrm.RVPInCamFrmHeight = RSVP_INPUT_HEIGHT;
    pObj->pRVPLdcLutPrm.RVPInCamFrmWidth = RSVP_INPUT_WIDTH;

    //output frame size
    pObj->pRVPLdcLutPrm.RVPOutDisplayHeight = RSVP_OUTPUT_HEIGHT;
    pObj->pRVPLdcLutPrm.RVPOutDisplayWidth = RSVP_OUTPUT_WIDTH;

    // Disparity map input size
    pObj->pRVPLdcLutPrm.RVPDisparityHeight = REMAP_HEIGHT;
    pObj->pRVPLdcLutPrm.RVPDisparityWidth = REMAP_WIDTH;

    for (cnt = 0;cnt < (RSVP_NUM_CAMERAS+1);cnt++)
        {
        /**< Width of individual cameras, output */
        pObj->pRVPLdcLutPrm.Trans_RVP_width[cnt] = pObj->pRVPLdcLutPrm.RVPOutDisplayWidth/2;

        /**< Height of individual cameras, output */
        pObj->pRVPLdcLutPrm.Trans_RVP_height[cnt] = pObj->pRVPLdcLutPrm.RVPOutDisplayHeight/2;
        }

    /**< Start location for each camera transformed image in RSVP output */
    // Swapped channels 0 and 2 for mirror image RSVP output (10 Jan 2017 VAV)
    pObj->pRVPLdcLutPrm.start_x_in_op[2] = 0;
    pObj->pRVPLdcLutPrm.start_x_in_op[1] = pObj->pRVPLdcLutPrm.RVPOutDisplayWidth / 4;
    pObj->pRVPLdcLutPrm.start_x_in_op[0] = pObj->pRVPLdcLutPrm.RVPOutDisplayWidth / 2;
    pObj->pRVPLdcLutPrm.start_x_in_op[3] = pObj->pRVPLdcLutPrm.RVPOutDisplayWidth / 4;
    pObj->pRVPLdcLutPrm.start_x_in_op[4] = pObj->pRVPLdcLutPrm.RVPOutDisplayWidth / 4;


    /**< Size of LDC LUTs in bytes */
    pObj->pRVPLdcLutPrm.ldcLutSize = \
            (pObj->pRVPLdcLutPrm.Trans_RVP_width[0] / LDCSUBSAMPLEFACTOR + 1) * (pObj->pRVPLdcLutPrm.Trans_RVP_height[0] / LDCSUBSAMPLEFACTOR + 1) * 2;


    /**< Size of calibaration matrix in bytes */
    pObj->pRVPLdcLutPrm.calMatSize = RSVP_CALMAT_SIZE;

    /* Default CalMat for RSVP */
    memcpy(
    (Ptr)ChainsCommon_Osal_getVirtAddr(
               (Int32)pObj->pRVPLdcLutPrm.calmatBuffer),
               defaultcalmatin_rsvp,
               RSVP_CALMAT_SIZE);

    //Other RVP Parameters:

            //scale virtual camera default physical location (midpoint between mirror cameras)
    pObj->pRVPLdcLutPrm.vc_scale_height = VC_SCALE_HEIGHT; //scale in z-direction
    pObj->pRVPLdcLutPrm.vc_scale_depth = VC_SCALE_DEPTH; //scale in y-direction

    pObj->pRVPLdcLutPrm.vc_wall_distance = VC_WALL_DISTANCE; //distance of wall from virtual camera
    pObj->pRVPLdcLutPrm.vc_vf = VC_VF; //virtual camera focal length
    pObj->pRVPLdcLutPrm.vc_rotx = VC_ROTX; //rotation of virtual camera about x-axis
    pObj->pRVPLdcLutPrm.vc_roty = VC_ROTY;
    pObj->pRVPLdcLutPrm.vc_rotz = VC_ROTZ;

    pObj->pRVPLdcLutPrm.focalLength = FOCAL_LENGTH; // Input camera focal length

    // LDC output dimensions
    pObj->pRVPLdcLutPrm.LDC_op_width = SIMCOP_OUTPUT_WIDTH;
    pObj->pRVPLdcLutPrm.LDC_op_height = SIMCOP_OUTPUT_HEIGHT;


    // Calmat Flag (Set to 0 for now, may need to change if we enable default calmat without reading from SD card in the future)
    pObj->pRVPLdcLutPrm.isCalMatGenerated = FALSE;

    // Stereo parameters decided by max disparity/downsampling factor, census transform on stereo engine
    pObj->pRVPLdcLutPrm.stereo_offsetX = STEREO_OFFSETX;
    pObj->pRVPLdcLutPrm.stereo_offsetY = STEREO_OFFSETY;

    pObj->pRVPLdcLutPrm.scratch_mem = \
            ChainsCommon_Osal_memAlloc(4*4096,128U);
        UTILS_assert(NULL != pObj->pRVPLdcLutPrm.scratch_mem);

    pObj->pRVPLdcLutPrm.cam_world_loc = \
        ChainsCommon_Osal_memAlloc((3 * (RSVP_NUM_CAMERAS+1))*sizeof(float),128U);
    UTILS_assert(NULL != pObj->pRVPLdcLutPrm.cam_world_loc);

    pObj->pRVPLdcLutPrm.vcam_proj_mat = \
        ChainsCommon_Osal_memAlloc((VCAM_PROJ_MAT_SIZE)*sizeof(float),128U);
    UTILS_assert(NULL != pObj->pRVPLdcLutPrm.vcam_proj_mat);


    pObj->pRVPLdcLutPrm.perstransform = \
            ChainsCommon_Osal_memAlloc((RSVP_PERSMAT_SIZE)*sizeof(float),128U);
        UTILS_assert(NULL != pObj->pRVPLdcLutPrm.perstransform);


    lineOffset = (SIMCOP_OUTPUT_WIDTH /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((SIMCOP_OUTPUT_HEIGHT /
                                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                    + 1U);

    alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);

    rsvpldclutsize = (alignedLdcLutSize * (RSVP_NUM_CAMERAS-1));

    // RSVP LDCLUT tables for 3 cameras
        for (cnt = 0;cnt < (RSVP_NUM_CAMERAS);cnt++)
        {
            pObj->pRVPLdcLutPrm.LDCLUTRVP[cnt] = ChainsCommon_Osal_memAlloc(2*alignedLdcLutSize*sizeof(Int16),128U);
            UTILS_assert(NULL != pObj->pRVPLdcLutPrm.LDCLUTRVP[cnt]);
        }

    // Add transposed stereo disparity dewarp table size to rawmemsize
    lineOffset_trans = (SIMCOP_STEREO_OUTPUT_WIDTH /
                              (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset_trans += 15;
    lineOffset_trans &= ~0xF;
    lineOffset_trans *= 4;

    ldcLutSize_trans = lineOffset_trans * ((SIMCOP_STEREO_OUTPUT_HEIGHT /
                              (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                              + 1U);

    alignedLdcLutSize_trans = SystemUtils_align(ldcLutSize_trans, 128U);

    // RSVP LDCLUT tables for Stereo disparity transpose
    pObj->pRVPLdcLutPrm.LDCLUTRVP[RSVP_NUM_CAMERAS] = ChainsCommon_Osal_memAlloc(2*alignedLdcLutSize_trans*sizeof(Int16),128U);
    UTILS_assert(NULL != pObj->pRVPLdcLutPrm.LDCLUTRVP[RSVP_NUM_CAMERAS]);

    /* raw mem size */
    rsvpldclutsize += (alignedLdcLutSize_trans); // Add size of LUT used for transposed stereo right camera

    Vps_printf(" chains_RVP_TDA3X: alloc buffers : rsvpldclutsize = %d", rsvpldclutsize);

    pObj->pRVPLdcLutPrm.combinedLDCLUTRVP = \
                ChainsCommon_Osal_memAlloc(2*rsvpldclutsize*sizeof(Int16),128U);
    UTILS_assert(NULL != pObj->pRVPLdcLutPrm.combinedLDCLUTRVP);

}

/**
 *******************************************************************************
 *
 * \brief   Free the buffers used in the RSVP Calibration Use case
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void freeRSVPCalibUseCaseBufs(Chains_RVPAppObj *pObj)
{
    UInt32 cnt;
    UInt32 lineOffset, lineOffset_trans, ldcLutSize_trans, ldcLutSize;
    UInt32 alignedLdcLutSize_trans, alignedLdcLutSize, rsvpldclutsize;

    if(pObj->pRVPLdcLutPrm.cam_world_loc != NULL)
    {
        ChainsCommon_Osal_memFree(
                pObj->pRVPLdcLutPrm.cam_world_loc,
                3 * (RSVP_NUM_CAMERAS+1)*sizeof(float)) ;
    }

    if(pObj->pRVPLdcLutPrm.vcam_proj_mat != NULL)
    {
        ChainsCommon_Osal_memFree(
                pObj->pRVPLdcLutPrm.vcam_proj_mat,
                (VCAM_PROJ_MAT_SIZE)*sizeof(float));
    }

    if(pObj->pRVPLdcLutPrm.perstransform != NULL)
    {
        ChainsCommon_Osal_memFree(
                pObj->pRVPLdcLutPrm.perstransform,
                (RSVP_PERSMAT_SIZE)*sizeof(float));
    }

    lineOffset = (SIMCOP_OUTPUT_WIDTH /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((SIMCOP_OUTPUT_HEIGHT /
                                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                    + 1U);

    alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);

    for (cnt = 0;cnt < pObj->pRVPLdcLutPrm.numCameras;cnt++)
    {
        if (pObj->pRVPLdcLutPrm.LDCLUTRVP[cnt] != NULL)
        {
            ChainsCommon_Osal_memFree(
                    pObj->pRVPLdcLutPrm.LDCLUTRVP[cnt],
                    2*alignedLdcLutSize*sizeof(Int16));
        }
    }

    rsvpldclutsize = (alignedLdcLutSize * (RSVP_NUM_CAMERAS-1));

    // Add transposed stereo disparity dewarp table size to rawmemsize
    lineOffset_trans = (SIMCOP_STEREO_OUTPUT_WIDTH /
                              (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset_trans += 15;
    lineOffset_trans &= ~0xF;
    lineOffset_trans *= 4;

    ldcLutSize_trans = lineOffset_trans * ((SIMCOP_STEREO_OUTPUT_HEIGHT /
                              (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                              + 1U);

    alignedLdcLutSize_trans = SystemUtils_align(ldcLutSize_trans, 128U);

    /* raw mem size */
    rsvpldclutsize += (alignedLdcLutSize_trans); // Add size of LUT used for transposed stereo right camera

    if(pObj->pRVPLdcLutPrm.combinedLDCLUTRVP != NULL)
    {
        ChainsCommon_Osal_memFree(
                pObj->pRVPLdcLutPrm.combinedLDCLUTRVP,
                2*rsvpldclutsize*sizeof(Int16));
    }

    if (pObj->pRVPLdcLutPrm.LDCLUTRVP[pObj->pRVPLdcLutPrm.numCameras] != NULL)
    {
        ChainsCommon_Osal_memFree(
                pObj->pRVPLdcLutPrm.LDCLUTRVP[pObj->pRVPLdcLutPrm.numCameras],
                2*alignedLdcLutSize_trans*sizeof(Int16));
    }

}
