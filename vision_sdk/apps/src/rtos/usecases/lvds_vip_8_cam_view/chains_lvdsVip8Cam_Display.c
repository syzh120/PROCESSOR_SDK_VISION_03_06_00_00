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
#include "chains_lvdsVip8Cam_Display_priv.h"
#include <src/include/chains_common.h>

#define OV490_SENSOR_WIDTH                      (1280U)
#define OV490_SENSOR_HEIGHT                     (1080U)

#define CAPTURE_OUTPUT_WIDTH                    (1280U)
#define CAPTURE_OUTPUT_HEIGHT                   (720U)

// Number of cameras displayed at a given time
#define NUM_MOSAIC_CHANNELS                     (4U)


/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (16)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (33)

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_lvdsVip8Cam_DisplayObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    SelectLink_OutQueChInfo *pOutQueChInfo;

    UInt32  numLvdsCh;
    /**< Number of channels of LVDS to enable */

    Chains_Ctrl *chainsCfg;

} Chains_LvdsVip8Cam_DisplayAppObj;

static Void chains_lvdsVip8Cam_Display_SetSelectPrm(
                    SelectLink_CreateParams *pPrm,
                    UInt32 outChannels
                    )
{
    UInt16 chId;

    pPrm->numOutQue = 1;

    pPrm->outQueChInfo[0].outQueId = 0;
    pPrm->outQueChInfo[0].numOutCh = outChannels;
    for(chId = 0; chId < outChannels; chId++)
    {
        pPrm->outQueChInfo[0].inChNum[chId] = chId;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          chains_lvdsVip8Cam_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVip8Cam_Display_SetSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh
                    )
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

/**
 *******************************************************************************
 *
 * \brief   Set DMA SW Mosaic Create Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.

 * \param   pPrm    [OUT]    VpeLink_CreateParams
 *
 *******************************************************************************
*/
static Void chains_lvdsVip8Cam_Display_SetAlgVpeSwMsPrm(
                    AlgorithmLink_VpeSwMsCreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 displayWidth,
                    UInt32 displayHeight
                   )
{
    UInt32 winId,chId;
    AlgorithmLink_VpeSwMsLayoutWinInfo *pWinInfo;
    UInt32 widthFactor, heightFactor;

    pPrm->maxOutBufWidth     = displayWidth;
    pPrm->maxOutBufHeight    = displayHeight;
    pPrm->numOutBuf          = 4;
    pPrm->numInputCh          = numLvdsCh;

    pPrm->initLayoutParams.numWin = numLvdsCh;
    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;
    pPrm->enableOut[0] = TRUE;

    switch (numLvdsCh)
    {
        case 1:
            widthFactor  = 1;
            heightFactor = 1;
            pPrm->initLayoutParams.numWin = 1;
            break;
        case 2:
            widthFactor  = 2;
            heightFactor = 1;
            pPrm->initLayoutParams.numWin = 2;
            break;
        case 3:
        case 4:
            widthFactor  = 2;
            heightFactor = 2;
            pPrm->initLayoutParams.numWin = 4;
            break;
        case 5:
        case 6:
            widthFactor  = 2;
            heightFactor = 3;
            pPrm->initLayoutParams.numWin = 6;
            break;
        default:
            widthFactor  = 2;
            heightFactor = 2;
            pPrm->initLayoutParams.numWin = 4;
            break;
    }

    /* assuming 4Ch LVDS and 2x2 layout */
    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];

        pWinInfo->chId = winId;

        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;

        pWinInfo->width     =
            SystemUtils_floor(pPrm->initLayoutParams.outBufWidth/widthFactor, 16);
        pWinInfo->height    =
            pPrm->initLayoutParams.outBufHeight/heightFactor;

        /* winId == 0 */
        pWinInfo->outStartX = 0;
        pWinInfo->outStartY = 0;

        if(winId==1)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = 0;
        } else
        if(winId==2)
        {
            pWinInfo->outStartX = 0;
            pWinInfo->outStartY = pWinInfo->height;
        } else
        if(winId==3)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = pWinInfo->height;
        } else
        if(winId==4)
        {
            pWinInfo->outStartX = 0;
            pWinInfo->outStartY = 2 * pWinInfo->height;
        } else
        if(winId==5)
        {
            pWinInfo->outStartX = pWinInfo->width;
            pWinInfo->outStartY = 2 * pWinInfo->height;
        }
    }

    for(chId = 0; chId < numLvdsCh; chId++)
    {

        pWinInfo = &pPrm->initLayoutParams.winInfo[chId];
        pPrm->chParams[chId].outParams[0].width
            = pWinInfo->width ;

        pPrm->chParams[chId].outParams[0].height
            = pWinInfo->height ;

        pPrm->chParams[chId].outParams[0].dataFormat
            = SYSTEM_DF_YUV420SP_UV;
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 4;


        /* Setting Crop parameter */
        pPrm->chParams[chId].scCropCfg.cropStartX  = 0;
        pPrm->chParams[chId].scCropCfg.cropStartY  = 0;

        pPrm->chParams[chId].scCropCfg.cropWidth    = displayWidth;
        pPrm->chParams[chId].scCropCfg.cropHeight   = displayHeight;
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
Void chains_lvdsVip8Cam_Display_SetAppPrms(chains_lvdsVip8Cam_DisplayObj *pUcObj, Void *appObj)
{
    Chains_LvdsVip8Cam_DisplayAppObj *pObj
        = (Chains_LvdsVip8Cam_DisplayAppObj*)appObj;

    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];

    pObj->numLvdsCh = pObj->chainsCfg->numLvdsCh;

    pObj->captureOutWidth  = CAPTURE_OUTPUT_WIDTH;
    pObj->captureOutHeight = CAPTURE_OUTPUT_HEIGHT;
    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_MultiCam_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        portId,
        pObj->numLvdsCh
        );

    ChainsCommon_MultiCam_SetCapturePrms(&pUcObj->CapturePrm,
            CAPTURE_OUTPUT_WIDTH,
            CAPTURE_OUTPUT_HEIGHT,
            portId,
            pObj->numLvdsCh
            );

    if (pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV490)
    {
         ChainsCommon_MultiCam_SetCroppingPrms(&pUcObj->CapturePrm,
            OV490_SENSOR_WIDTH,
            OV490_SENSOR_HEIGHT,
            CAPTURE_OUTPUT_WIDTH,
            CAPTURE_OUTPUT_HEIGHT
            );
    }

    chains_lvdsVip8Cam_Display_SetSelectPrm(
            &pUcObj->SelectPrm,
            NUM_MOSAIC_CHANNELS
    );
    pObj->pOutQueChInfo = &pUcObj->SelectPrm.outQueChInfo[0];

    chains_lvdsVip8Cam_Display_SetSyncPrm(
                &pUcObj->SyncPrm,
                NUM_MOSAIC_CHANNELS
        );

    chains_lvdsVip8Cam_Display_SetAlgVpeSwMsPrm(
                            &pUcObj->Alg_VpeSwMsPrm,
                            NUM_MOSAIC_CHANNELS,
                            CAPTURE_OUTPUT_WIDTH,
                            CAPTURE_OUTPUT_HEIGHT
                            );

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_videoPrm,
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
 * \param   pObj  [IN] Chains_LvdsVip8Cam_DisplayObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_lvdsVip8Cam_Display_StartApp(Chains_LvdsVip8Cam_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_lvdsVip8Cam_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVip8Cam_DisplayObj
 *
 *******************************************************************************
*/
static Void chains_lvdsVip8Cam_Display_StopAndDeleteApp(Chains_LvdsVip8Cam_DisplayAppObj *pObj)
{
    chains_lvdsVip8Cam_Display_Stop(&pObj->ucObj);
    chains_lvdsVip8Cam_Display_Delete(&pObj->ucObj);

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
 * \brief   Switch Display Channel
 *
 *          Function sends a control command to display link to
 *          switch the input channel to display
 *          System_linkControl is called with linkId , displayActiveChId
 *          and the cmd DISPLAY_LINK_CMD_SWITCH_CH.
 *
 * \param   pObj    [IN]   Chains_LvdsMultiVipCaptureDisplayObj
 *
 *******************************************************************************
*/
static Void chains_lvdsVip8Cam_Display_SwitchDisplayChannel(
                                    Chains_LvdsVip8Cam_DisplayAppObj *pObj)
{
    UInt32 outId, chanId;

    for (outId = 0; outId < pObj->pOutQueChInfo->numOutCh; outId++)
    {
        chanId =  pObj->pOutQueChInfo->inChNum[outId]; 
        chanId = (chanId + NUM_MOSAIC_CHANNELS) % pObj->numLvdsCh;
        pObj->pOutQueChInfo->inChNum[outId] = chanId;
    }

    System_linkControl(pObj->ucObj.SelectLinkID,
                       SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO,
                       pObj->pOutQueChInfo,
                       sizeof(*(pObj->pOutQueChInfo)),
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
Void Chains_lvdsVip8Cam_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_LvdsVip8Cam_DisplayAppObj chainsObj;

    chainsObj.numLvdsCh         = 0; /* KW error fix */
    chainsObj.chainsCfg = chainsCfg;

    chains_lvdsVip8Cam_Display_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVip8Cam_Display_StartApp(&chainsObj);

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
                chains_lvdsVip8Cam_Display_printStatistics(&chainsObj.ucObj);
                break;
            case '1':
                chains_lvdsVip8Cam_Display_SwitchDisplayChannel(&chainsObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVip8Cam_Display_StopAndDeleteApp(&chainsObj);
}

