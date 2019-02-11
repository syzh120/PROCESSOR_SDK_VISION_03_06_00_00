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
#include "chains_lvdsVipSurroundView_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_surround_view.h>
#include <src/include/chains_common_osal.h>


#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

#define SV_WIDTH                  (SRV_OUTPUT_WIDTH_TDA3X_2D)
#define SV_HEIGHT                 (SRV_OUTPUT_HEIGHT_TDA3X_2D)

#define SV_NUM_VIEWS              (4)

#define SV_CARBOX_WIDTH           (160)
#define SV_CARBOX_HEIGHT          (240)

#define SV_DISPLAY_HEIGHT         (768)
#define SV_DISPLAY_WIDTH          (SV_WIDTH * SV_DISPLAY_HEIGHT)/SV_HEIGHT
#define SV_DISPLAY_STARTX         (1024 - SV_DISPLAY_WIDTH)/2
#define SV_DISPLAY_STARTY         (0)

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

    chains_lvdsVipSurroundViewObj ucObj;
    UInt32 captureOutWidth;
    UInt32 captureOutHeight;
    UInt32 displayWidth;
    UInt32 displayHeight;

    Chains_Ctrl *chainsCfg;

} Chains_LvdsVipSurroundViewAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          chains_lvdsVipMultiCam_Display_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundView_SetSyncPrm(
                    SyncLink_CreateParams *pPrm1
                    )
{
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

    pPrm1->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm1->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

Void chains_lvdsVipSurroundView_SetVPEParams(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numChannels,
                    UInt32 outWidth,
                    UInt32 outHeight
                    )
{
    UInt16 chId;
    pPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < numChannels; chId++)
    {
        pPrm->chParams[chId].outParams[0].width
            = SystemUtils_floor(outWidth, 16);

        pPrm->chParams[chId].outParams[0].height
            = outHeight;

        pPrm->chParams[chId].outParams[0].dataFormat
            = SYSTEM_DF_YUV420SP_UV;
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 4;
    }
}

/**
 *******************************************************************************
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundView_SetAppPrms(chains_lvdsVipSurroundViewObj *pUcObj, Void *appObj)
{
    Chains_LvdsVipSurroundViewAppObj *pObj
        = (Chains_LvdsVipSurroundViewAppObj*)appObj;

    Int16 carBoxWidth;
    Int16 carBoxHeight;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight);

    /* VIP Capture */
    ChainsCommon_MultiCam_StartCaptureDevice(
                                    CHAINS_CAPTURE_SRC_OV10635,
                                    portId,
                                    pObj->chainsCfg->numLvdsCh);

    ChainsCommon_MultiCam_SetCapturePrms(
                                    &pUcObj->CapturePrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    portId,
                                    pObj->chainsCfg->numLvdsCh);
    {
        UInt32 i;
        CaptureLink_VipInstParams *pInstPrm;

        for (i = 0U; i < SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pInstPrm = &pUcObj->CapturePrm.vipInst[i];
            pInstPrm->numBufs = 6;
        }
    }

    ChainsCommon_SurroundView_SetSyncPrm(
        &pUcObj->Sync_svPrm, pObj->chainsCfg->numLvdsCh, 1); /* 1: Tight Sync */

            /* Graphics Source */
    ChainsCommon_SurroundView_SetGrpxSrcPrms(
                                    &pUcObj->GrpxSrcPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight,
                                    pObj->chainsCfg->svOutputMode);

    /* Display */
    ChainsCommon_SurroundView_SetDisplayPrm(
                                    &pUcObj->Display_svPrm,
                                    NULL,
                                    NULL,
                                    &pUcObj->Display_GrpxPrm,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    ChainsCommon_StartDisplayCtrl(
                                    pObj->chainsCfg->displayType,
                                    pObj->displayWidth,
                                    pObj->displayHeight);

    pUcObj->GrpxSrcPrm.tda3xxSvFsRotLayoutEnable = TRUE;

    carBoxWidth = SV_CARBOX_WIDTH;
    carBoxHeight = SV_CARBOX_HEIGHT;

    pUcObj->Display_svPrm.rtParams.tarWidth   = SV_DISPLAY_WIDTH;
    pUcObj->Display_svPrm.rtParams.tarHeight  = SV_DISPLAY_HEIGHT;
    pUcObj->Display_svPrm.rtParams.posX       = SV_DISPLAY_STARTX;
    pUcObj->Display_svPrm.rtParams.posY       = SV_DISPLAY_STARTY;
    pUcObj->Display_svPrm.displayId           = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                            CAPTURE_SENSOR_WIDTH,
                                            CAPTURE_SENSOR_HEIGHT,
                                            SV_WIDTH,
                                            SV_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            pObj->chainsCfg->svOutputMode,
                                            pObj->chainsCfg->enableCarOverlayInAlg);

    ChainsCommon_SurroundView_SetGAlignParams(&pUcObj->Alg_GeoAlignPrm,
                                            CAPTURE_SENSOR_WIDTH,
                                            CAPTURE_SENSOR_HEIGHT,
                                            SV_WIDTH,
                                            SV_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            pObj->chainsCfg->svOutputMode);

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                            CAPTURE_SENSOR_WIDTH,
                                            CAPTURE_SENSOR_HEIGHT,
                                            SV_WIDTH,
                                            SV_HEIGHT,
                                            SV_NUM_VIEWS,
                                            carBoxWidth,
                                            carBoxHeight,
                                            pObj->chainsCfg->svOutputMode);

    pUcObj->GrpxSrcPrm.displaySrv2D.startX = SV_DISPLAY_STARTX;
    pUcObj->GrpxSrcPrm.displaySrv2D.startY = SV_DISPLAY_STARTY;
    pUcObj->GrpxSrcPrm.displaySrv2D.width = SV_DISPLAY_WIDTH;
    pUcObj->GrpxSrcPrm.displaySrv2D.height = SV_DISPLAY_HEIGHT;
    pUcObj->GrpxSrcPrm.displaySrv2D.srvOutWidth = SV_WIDTH;
    pUcObj->GrpxSrcPrm.displaySrv2D.srvOutHeight = SV_HEIGHT;
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
 * \param   pObj  [IN] Chains_LvdsVipSurroundViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundView_StartApp(Chains_LvdsVipSurroundViewAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_lvdsVipSurroundView_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVipSurroundViewObj
 *
 *******************************************************************************
*/
Void chains_lvdsVipSurroundView_StopAndDeleteApp(Chains_LvdsVipSurroundViewAppObj *pObj)
{
    chains_lvdsVipSurroundView_Stop(&pObj->ucObj);
    chains_lvdsVipSurroundView_Delete(&pObj->ucObj);

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
Void Chains_lvdsVipSurroundView(Chains_Ctrl *chainsCfg)
{
    Int32 chDirRet;
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_LvdsVipSurroundViewAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chDirRet = ChainsCommon_Osal_fileChDir(SRV_DIR_3X);

    do
    {
        done = FALSE;
        /* Set startWithCalibration = TRUE to start the demo with calibration.
           Else it will use the previously calibrated LUTs */
        startWithCalibration = TRUE;
        ChainsCommon_SurroundView_CalibInit(
                                    startWithCalibration,
                                    chainsObj.chainsCfg->svOutputMode);

        chains_lvdsVipSurroundView_Create(&chainsObj.ucObj, &chainsObj);
        chains_lvdsVipSurroundView_StartApp(&chainsObj);

        while(!done)
        {
            ch = Chains_menuRunTime();

            switch(ch)
            {
                case '0':
                    chPrev = ChainsCommon_SurroundView_MenuCalibration();
                    done = TRUE;
                    break;
                case 'p':
                case 'P':
                    ChainsCommon_PrintStatistics();
                    chains_lvdsVipSurroundView_printStatistics(&chainsObj.ucObj);
                    break;
                default:
                    Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                    break;
            }
        }

        chains_lvdsVipSurroundView_StopAndDeleteApp(&chainsObj);
        ChainsCommon_SurroundView_CalibDeInit();
    } while(chPrev!='3');

    if (SYSTEM_LINK_STATUS_SOK == chDirRet)
    {
        File_chDir("/\0");
    }
}

