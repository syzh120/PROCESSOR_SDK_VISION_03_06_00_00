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
#include "chains_vipSingleCameraSparseOpticalFlow_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_sfm.h>

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

#define SOF_NUM_OUT_BUF  (8)

#define SOF_ALG_WIDTH    (1280)
#define SOF_ALG_HEIGHT   (720)

#define ENABLE_SFM_INPUT_TEST

/**
 *******************************************************************************
 *
 *  \brief  Link Object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCameraSparseOpticalFlowObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

} Chains_VipSingleCameraSparseOpticalFlowAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set VPE Create Parameters
 *
 *          This function is used to set the VPE params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCameraSparseOpticalFlow_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *          Scaling parameters are set .
 *
 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraSparseOpticalFlow_SetVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 outWidth,
                    UInt32 outHeight,
                    UInt32 srcWidth,
                    UInt32 srcHeight,
                    System_VideoDataFormat dataFormat
                    )
{
    pPrm->enableOut[0] = TRUE;

    pPrm->chParams[0].outParams[0].width = SystemUtils_floor(outWidth, 4);
    pPrm->chParams[0].outParams[0].height = SystemUtils_floor(outHeight, 2);
    pPrm->chParams[0].outParams[0].numBufsPerCh = 3;

    pPrm->chParams[0].scCropCfg.cropStartX = 0;
    pPrm->chParams[0].scCropCfg.cropStartY = 0;
    pPrm->chParams[0].scCropCfg.cropWidth  = srcWidth;
    pPrm->chParams[0].scCropCfg.cropHeight = srcHeight;

    pPrm->chParams[0].outParams[0].dataFormat = dataFormat;
    pPrm->chParams[0].outParams[0].numBufsPerCh = 2;
}

/**
 *******************************************************************************
 *
 * \brief   Set Algorithm related parameters
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraSparseOpticalFlow_SetSparseOpticalFlowPrm(
                    AlgorithmLink_SparseOpticalFlowCreateParams *pAlgPrm,
                    AlgorithmLink_ObjectDrawCreateParams *pDrawPrm,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height
                    )
{

    ChainsCommon_SetSOFConfig(pAlgPrm,
                              startX,
                              startY,
                              width,
                              height,
                              600);

    #ifndef ENABLE_SFM_INPUT_TEST
        pAlgPrm->enableRoi      = FALSE;
    #endif


    pDrawPrm->imgFrameStartX = startX;
    pDrawPrm->imgFrameStartY = startY;
    pDrawPrm->imgFrameWidth  = width;
    pDrawPrm->imgFrameHeight  = height;

    pDrawPrm->numOutBuffers = 5;
    pDrawPrm->sofMaxTrackPoints = pAlgPrm->maxNumKeyPoints;
    pDrawPrm->numDrawAlg = 1;
    pDrawPrm->drawAlgId[0] = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SOF;
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Link Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraSparseOpticalFlow_SetSyncPrm(SyncLink_CreateParams *pPrm)

{
    pPrm->syncDelta = 1;
    pPrm->syncThreshold = 0xFFFF;
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
Void chains_vipSingleCameraSparseOpticalFlow_SetAppPrms(chains_vipSingleCameraSparseOpticalFlowObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraSparseOpticalFlowAppObj *pObj
        = (Chains_VipSingleCameraSparseOpticalFlowAppObj*)appObj;

    UInt32 startX=0, startY=0;

    ChainsCommon_Sfm_Init(FALSE);

    #ifdef ENABLE_SFM_INPUT_TEST
    pObj->captureOutWidth  = 1920;
    pObj->captureOutHeight = 1080;
    #else
    pObj->captureOutWidth  = SOF_ALG_WIDTH;
    pObj->captureOutHeight = SOF_ALG_HEIGHT;
    #endif

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(&pUcObj->CapturePrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    pUcObj->CapturePrm.vipInst[0].numBufs = 7;

    #ifdef ENABLE_SFM_INPUT_TEST
    ChainsCommon_Sfm_SetCaptureCallback(&pUcObj->CapturePrm);
    startX = 320;
    startY = 180;
    #endif

    chains_vipSingleCameraSparseOpticalFlow_SetSyncPrm(
                    &pUcObj->Sync_algPrm
                );

    chains_vipSingleCameraSparseOpticalFlow_SetSparseOpticalFlowPrm(
        &pUcObj->Alg_SparseOpticalFlowPrm,
        &pUcObj->Alg_ObjectDrawPrm,
        startX,
        startY,
        SOF_ALG_WIDTH,
        SOF_ALG_HEIGHT
        );

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_algPrm,
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
 * \param   pObj  [IN] Chains_VipSingleCameraSparseOpticalFlowObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraSparseOpticalFlow_StartApp(Chains_VipSingleCameraSparseOpticalFlowAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCameraSparseOpticalFlow_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_VipSingleCameraSparseOpticalFlowObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCameraSparseOpticalFlow_StopAndDeleteApp(Chains_VipSingleCameraSparseOpticalFlowAppObj *pObj)
{
    chains_vipSingleCameraSparseOpticalFlow_Stop(&pObj->ucObj);
    chains_vipSingleCameraSparseOpticalFlow_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_Sfm_DeInit();

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
Void Chains_vipSingleCameraSparseOpticalFlow(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraSparseOpticalFlowAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    #ifdef ENABLE_SFM_INPUT_TEST
    if(chainsObj.chainsCfg->captureSrc!=CHAINS_CAPTURE_SRC_HDMI_1080P)
    {
        Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
        Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
        return;
    }
    #endif

    chains_vipSingleCameraSparseOpticalFlow_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCameraSparseOpticalFlow_StartApp(&chainsObj);

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
                chains_vipSingleCameraSparseOpticalFlow_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCameraSparseOpticalFlow_StopAndDeleteApp(&chainsObj);
}

