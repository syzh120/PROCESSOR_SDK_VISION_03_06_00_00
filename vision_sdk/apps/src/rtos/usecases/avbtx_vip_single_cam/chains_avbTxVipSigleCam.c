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
#include "chains_avbTxVipSigleCam_priv.h"
#include <src/include/chains_common.h>
#ifdef TDA3XX_BUILD
#include <include/link_api/rtiLink.h>
#include <src/rtos/utils_common/include/utils_dcc.h>
#endif

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)
#define MAX_NUMBER_OF_CHANNELS    (1)
/**
 *******************************************************************************
 *
 *  \brief  AvbTxSingleCameraObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_avbTxVipSigleCamObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;
    System_IVideoFormat codecType;
    UInt32  netProcId;
    Chains_Ctrl *chainsCfg;

} Chains_AvbTxVipSigleCamAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set Save Display Frame Use case Link Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_avbTxVipSigleCam_SetDispWbPrms(
                                CaptureLink_CreateParams *pPrm,
                                Chains_AvbTxVipSigleCamAppObj *pObj)
{
    /* Capture DSS WB params */
    pPrm->numVipInst = 0;
    pPrm->numDssWbInst = 1;

    pPrm->dssWbInst[0].dssWbInstId = 33U; /* Only supported id */
    System_VideoScanFormat scanFormat = SYSTEM_SF_PROGRESSIVE;

    pPrm->dssWbInst[0].dssWbInputPrms.inNode = SYSTEM_WB_IN_NODE_TV;

    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceWidth = pObj->displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceHeight = pObj->displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInWidth = pObj->displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInHeight = pObj->displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosx = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosy = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceDataFmt = SYSTEM_DF_BGR24_888;
    pPrm->dssWbInst[0].dssWbInputPrms.wbScanFormat = scanFormat;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbWidth = 1280;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbHeight = 720;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbDataFmt = SYSTEM_DF_YUV420SP_UV;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbScanFormat = scanFormat;

    pPrm->dssWbInst[0].numBufs = 4U;

}

/**
 *******************************************************************************
 *
 * \brief   Set Encoder Create Parameters
 *
 * \param   pPrm         [IN]  EncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_avbTxVipSigleCam_SetEncPrms(
                   EncLink_CreateParams *pPrm,
                   Chains_AvbTxVipSigleCamAppObj *pObj)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 4;
    }

    for (chId = 0; chId < MAX_NUMBER_OF_CHANNELS; chId++)
    {
        pLinkChPrm  = &pPrm->chCreateParams[chId];
        pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

        UTILS_assert (chId < ENC_LINK_MAX_CH);

        switch (pObj->codecType)
        {
          case SYSTEM_IVIDEO_MJPEG: /* MJPEG */
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
            Vps_printf(" \n Codec is MJPEG \n");
            break;

          case SYSTEM_IVIDEO_H264HP: /* H264 */
            pLinkChPrm->format                 = SYSTEM_IVIDEO_H264HP;
            pLinkChPrm->profile                = 100;
            pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
            pLinkChPrm->fieldMergeEncodeEnable = FALSE;
            pLinkChPrm->enableAnalyticinfo     = 0;
            pLinkChPrm->enableWaterMarking     = 0;
            pLinkChPrm->maxBitRate             = -1;
            pLinkChPrm->encodingPreset         = SYSTEM_XDM_MED_SPEED_HIGH_QUALITY;
            /* Set to SYSTEM_XDM_USER_DEFINED if SEI/meta data needs to be enabled */
            pLinkChPrm->encodingPreset         = SYSTEM_XDM_USER_DEFINED;
            pLinkChPrm->rateControlPreset      = SYSTEM_IVIDEO_LOW_DELAY;
            pLinkChPrm->enableHighSpeed        = FALSE;
            pLinkChPrm->enableSVCExtensionFlag = FALSE;
            pLinkChPrm->numTemporalLayer       = 0;
            pLinkChPrm->overrideInputScanFormat= 0;
            pLinkChPrm->fieldPicEncode         = 0;
            pLinkChPrm->IDRFrameInterval       = 30;

            pLinkDynPrm->intraFrameInterval    = 1;
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
            pLinkDynPrm->maxPicSizeRatioI      = 1;
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
Void chains_avbTxVipSigleCam_SetAppPrms(chains_avbTxVipSigleCamObj *pUcObj, Void *appObj)
{
    Chains_AvbTxVipSigleCamAppObj *pObj
        = (Chains_AvbTxVipSigleCamAppObj*)appObj;

    /*
     * In use-case.txt AVB is configured on IPU1_1. This needs change/tweak it
     * to run on core where networking(NDK) is enabled by user via config file
     * (cfg.mk). Below code connects links such a way that AVB links gets assigned
     * to core running networking stack. This way user don’t have to change
     * use-case every time networking is moved.
     */
    pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCIn_IPU1_1_IPU1_0_0LinkID);

    pUcObj->AvbTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->AvbTxLinkID);

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;
    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(&(pUcObj->CapturePrm),
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                               &pUcObj->Display_GrpxPrm,
                                               pObj->chainsCfg->displayType,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                                );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    pObj->codecType = SYSTEM_IVIDEO_H264HP;

    ChainsCommon_SetAvbTxPrm(&pUcObj->AvbTxPrm,
                             AVB_TX_LINK_MAX_TALKERS_DEFAULT,
                             pObj->codecType);

    chains_avbTxVipSigleCam_SetDispWbPrms(&pUcObj->Capture_dsswbPrm, pObj);

    chains_avbTxVipSigleCam_SetEncPrms(&pUcObj->EncodePrm, pObj);
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
 * \param   pObj  [IN] Chains_AvbTxVipSigleCamAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_avbTxVipSigleCam_StartApp(Chains_AvbTxVipSigleCamAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_avbTxVipSigleCam_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_AvbTxVipSigleCamAppObj
 *
 *******************************************************************************
*/
Void chains_avbTxVipSigleCam_StopAndDeleteApp(Chains_AvbTxVipSigleCamAppObj *pObj)
{
    chains_avbTxVipSigleCam_Stop(&pObj->ucObj);
    chains_avbTxVipSigleCam_Delete(&pObj->ucObj);

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
Void Chains_avbTxVipSigleCam(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_AvbTxVipSigleCamAppObj chainsObj;

#ifdef DCC_ESM_INCLUDE
    System_dccInit();
#endif

    chainsObj.chainsCfg = chainsCfg;
    chainsObj.netProcId = Utils_netGetProcId();
    if(chainsObj.netProcId==System_getSelfProcId())
    {
        Vps_printf(" \n");
        Vps_printf(" CHAINS: ERROR: Networking/NDK MUST be run on different CPU"
                   " than IPU1-0.\n");
        Vps_printf(" CHAINS: ERROR: If you need to run this use-case with NDK"
                   " on IPU1-0 then regenerate the use-case with NullSrc/Null"
                   " links on IPU1-0.\n"
                   );
        Vps_printf(" \n");
        return;
    }
    chains_avbTxVipSigleCam_Create(&chainsObj.ucObj, &chainsObj);
    chains_avbTxVipSigleCam_StartApp(&chainsObj);

#ifdef RTI_INCLUDE
    System_rtiEnableAll();
#endif

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
                chains_avbTxVipSigleCam_printStatistics(&chainsObj.ucObj);
                /* Show IVA load */
                System_linkControl(SYSTEM_LINK_ID_VENC_0,
                                   SYSTEM_CMD_PRINT_STATISTICS, NULL, 0, TRUE);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
#ifdef RTI_INCLUDE
    System_rtiDisableAll();
#endif

    chains_avbTxVipSigleCam_StopAndDeleteApp(&chainsObj);

#ifdef DCC_ESM_INCLUDE
    System_dccDeInit();
#endif
}

