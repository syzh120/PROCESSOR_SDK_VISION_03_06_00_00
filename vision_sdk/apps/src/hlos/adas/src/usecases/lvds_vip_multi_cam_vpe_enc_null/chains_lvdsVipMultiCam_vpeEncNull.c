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

/**
 *******************************************************************************
 * \file chains_vipSingleCameraView.c
 *
 * \brief  Usecase file implementation of multi-ch capture display
 *
 *         The data flow daigram is shown below
 *
 *             Capture (VIP) 4CH 30fps 1280x720
 *                   |
 *                  Vpe
 *                   |
 *                  Enc
 *                   |
 *                 IPC OUT
 *                   |
 *                 IPC IN
 *                   |
 *                 Null (A15) -> with file write option
 *
 * \version 0.0 (Jun 2014) : [SS] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_lvdsVipMultiCam_vpeEncNull_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)
#define ENCDEC_FRAME_WIDTH        (1280)
#define ENCDEC_FRAME_HEIGHT       (800)

/**
 *******************************************************************************
 *
 *  \brief  MultiCameraVpeEncNullObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {
    /**< Link Id's and device IDs to use for this use-case */
    chains_lvdsVipMultiCam_vpeEncNullObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;
    UInt32  appCtrlLinkId;
    Char codecType;
    Chains_Ctrl *chainsCfg;
    Chains_CaptureSrc captureSrc;
} Chains_lvdsVipMultiCam_vpeEncNullAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVipMultiCam_vpeEncNull_SetVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 displayWidth,
                    UInt32 displayHeight,
                    UInt32 inputWidth,
                    UInt32 inputHeight
                    )
{
    UInt16 chId;

    pPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < numLvdsCh; chId++)
    {
        pPrm->chParams[chId].outParams[0].numBufsPerCh =
                                 VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;

        pPrm->chParams[chId].outParams[0].width = displayWidth;
        pPrm->chParams[chId].outParams[0].height = displayHeight;
        pPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->chParams[chId].scCfg.bypass       = FALSE;
        pPrm->chParams[chId].scCfg.nonLinear    = FALSE;
        pPrm->chParams[chId].scCfg.stripSize    = 0;

        pPrm->chParams[chId].scCropCfg.cropStartX = 0;
        pPrm->chParams[chId].scCropCfg.cropStartY = 0;
        pPrm->chParams[chId].scCropCfg.cropWidth = inputWidth;
        pPrm->chParams[chId].scCropCfg.cropHeight = inputHeight;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Enc Create Parameters
 *
 * \param   pPrm         [IN]  EncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVipMultiCam_vpeEncNull_SetEncPrms(
                   EncLink_CreateParams *pPrm,
                   Chains_lvdsVipMultiCam_vpeEncNullAppObj *pObj,
                   UInt32 numLvdsCh)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 4;
    }

    for (chId = 0; chId < numLvdsCh; chId++)
    {
        pLinkChPrm  = &pPrm->chCreateParams[chId];
        pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

        UTILS_assert (chId < ENC_LINK_MAX_CH);

        switch (pObj->codecType)
        {
          case '0': /* MJPEG */
            pLinkChPrm->format                 = SYSTEM_IVIDEO_MJPEG;
            pLinkChPrm->profile                = 0;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = 0;
            pLinkChPrm->encodingPreset         = 0;
            pLinkChPrm->rateControlPreset      = 0;
            pLinkChPrm->enableHighSpeed        = 0;
            pLinkChPrm->enableSVCExtensionFlag = 0;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;

            pLinkDynPrm->intraFrameInterval    = 0;
            pLinkDynPrm->targetBitRate         = 10*1000*1000;
            pLinkDynPrm->interFrameInterval    = 0;
            pLinkDynPrm->mvAccuracy            = 0;
            pLinkDynPrm->inputFrameRate        = 30;
            pLinkDynPrm->rcAlg                 = 0;
            pLinkDynPrm->qpMin                 = 0;
            pLinkDynPrm->qpMax                 = 0;
            pLinkDynPrm->qpInit                = -1;
            pLinkDynPrm->vbrDuration           = 0;
            pLinkDynPrm->vbrSensitivity        = 0;
            break;

          case '1': /* H264 */
            pLinkChPrm->format                 = SYSTEM_IVIDEO_H264HP;
            pLinkChPrm->profile                = 100;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = -1;
            pLinkChPrm->encodingPreset         = SYSTEM_XDM_MED_SPEED_HIGH_QUALITY;
            /* Set encodingPreset to SYSTEM_XDM_USER_DEFINED
               if SEI/meta data needs to be enabled */
            /* pLinkChPrm->encodingPreset         = SYSTEM_XDM_USER_DEFINED; */
            pLinkChPrm->rateControlPreset      = SYSTEM_IVIDEO_LOW_DELAY;
            pLinkChPrm->enableHighSpeed        = FALSE;
            pLinkChPrm->enableSVCExtensionFlag = FALSE;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;
            pLinkChPrm->IDRFrameInterval       = 1;

            pLinkDynPrm->intraFrameInterval    = 30;
            pLinkDynPrm->targetBitRate         = 10*1000*1000;
            pLinkDynPrm->interFrameInterval    = 1;
            pLinkDynPrm->mvAccuracy            = SYSTEM_IVIDENC2_MOTIONVECTOR_QUARTERPEL;
            pLinkDynPrm->inputFrameRate        = 30;
            pLinkDynPrm->rcAlg                 = 0;
            pLinkDynPrm->qpMin                 = 0;
            pLinkDynPrm->qpMax                 = 51;
            pLinkDynPrm->qpInit                = 25;
            pLinkDynPrm->vbrDuration           = 8;
            pLinkDynPrm->vbrSensitivity        = 0;
            /* Set maxPicSizeRatioI to 1 for IDR or I-Frame only mode */
            pLinkDynPrm->maxPicSizeRatioI      = 640;
            break;

          default: /* D1 */
            printf("\r\nCodec Type: %d, returning \n", pObj->codecType);
            UTILS_assert(FALSE);
            break;
        }
    }
}

/**
 *******************************************************************************
 * *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_lvdsVipMultiCam_vpeEncNull_SetAppPrms(
            chains_lvdsVipMultiCam_vpeEncNullObj *pUcObj, Void *appObj)
{

    Chains_lvdsVipMultiCam_vpeEncNullAppObj *pObj
            = (Chains_lvdsVipMultiCam_vpeEncNullAppObj*)appObj;

    pObj->vidSensorPrm.captureSrcId =  pObj->captureSrc;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                                &pObj->vidSensorPrm,
                                sizeof(VideoSensorCreateAndStartAppPrm),
                                TRUE);

    ChainsCommon_MultiCam_SetCapturePrms(
                    &pUcObj->CapturePrm,
                    pObj->chainsCfg->numLvdsCh);

    chains_lvdsVipMultiCam_vpeEncNull_SetVpePrm(&pUcObj->VPEPrm,
                                                pObj->chainsCfg->numLvdsCh,
                                                ENCDEC_FRAME_WIDTH,
                                                ENCDEC_FRAME_HEIGHT,
                                                CAPTURE_SENSOR_WIDTH,
                                                CAPTURE_SENSOR_HEIGHT);

    chains_lvdsVipMultiCam_vpeEncNull_SetEncPrms(&pUcObj->EncodePrm,
                                                 pObj,
                                                 pObj->chainsCfg->numLvdsCh);

#if 0
    pUcObj->NullPrm.dumpDataType = NULL_LINK_COPY_TYPE_BITSTREAM_FILE;

    switch (pObj->codecType)
    {
      case '0': /* MJPEG */
        strncpy(pUcObj->NullPrm.nameDataFile[0], "/home/stream0.mpeg", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[1], "/home/stream1.mpeg", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[2], "/home/stream2.mpeg", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[3], "/home/stream3.mpeg", 260U);
        break;
      case '1': /* H264 */
        strncpy(pUcObj->NullPrm.nameDataFile[0], "/home/stream0.h264", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[1], "/home/stream1.h264", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[2], "/home/stream2.h264", 260U);
        strncpy(pUcObj->NullPrm.nameDataFile[3], "/home/stream3.h264", 260U);
        break;
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief   Start the Links
 *
 *          Function sends a control command to capture and other link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_lvdsVipMultiCam_vpeEncNullAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_vpeEncNull_StartApp(Chains_lvdsVipMultiCam_vpeEncNullAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();
    chains_lvdsVipMultiCam_vpeEncNull_Start(&pObj->ucObj);

}

/**
 *******************************************************************************
 *
 * \brief   Delete the Links
 *
 *          Function sends a control command to capture and other link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_lvdsVipMultiCam_vpeEncNullAppObj
 *
 *******************************************************************************
*/
void chains_lvdsVipMultiCam_vpeEncNull_StopApp(Chains_lvdsVipMultiCam_vpeEncNullAppObj *pObj)
{
     chains_lvdsVipMultiCam_vpeEncNull_Stop(&pObj->ucObj);

     chains_lvdsVipMultiCam_vpeEncNull_Delete(&pObj->ucObj);

     ChainsCommon_StopDisplayCtrl();

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);
     ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);

}
/**
 *******************************************************************************
 * \brief Run Time Menu string for codec Type Selection.
 *******************************************************************************
 */
char chains_lvdsVipMultiCam_vpeEncNull_codecTypeSelectMenu[] = {
    "\r\n "
    "\r\n ========================================="
    "\r\n Chains Run-time Codec Type Selection Menu"
    "\r\n ========================================="
    "\r\n "
    "\r\n Enter '0' for MJPEG "
    "\r\n "
    "\r\n Enter '1' for H.264 "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Multi Channel Capture Scale Encode Null usecase function
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
Void chains_lvdsVipMultiCam_vpeEncNull(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_lvdsVipMultiCam_vpeEncNullAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    done = FALSE;
    while(!done)
    {
        Vps_printf(chains_lvdsVipMultiCam_vpeEncNull_codecTypeSelectMenu);
        chainsObj.codecType = getchar();

        switch(chainsObj.codecType)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                           chainsObj.codecType);
                break;
        }
    }

    chainsObj.captureSrc = chainsCfg->captureSrc;

    chains_lvdsVipMultiCam_vpeEncNull_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipMultiCam_vpeEncNull_StartApp(&chainsObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    done = FALSE;
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
                chains_lvdsVipMultiCam_vpeEncNull_printStatistics(&chainsObj.ucObj);
                chains_lvdsVipMultiCam_vpeEncNull_printBufferStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVipMultiCam_vpeEncNull_StopApp(&chainsObj);

}


