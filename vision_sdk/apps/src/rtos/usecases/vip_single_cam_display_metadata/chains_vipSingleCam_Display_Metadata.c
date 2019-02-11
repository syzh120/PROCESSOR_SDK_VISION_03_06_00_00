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
#include "chains_vipSingleCam_Display_Metadata_priv.h"
#include <src/include/chains_common.h>


#define CAPTURE_SENSOR_WIDTH      (1280u)
#define CAPTURE_SENSOR_HEIGHT     (720u)

#define MATA_DATA_SIZE            (2u)
#define MAX_LATENCY               (10u)


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

    chains_vipSingleCam_Display_MetadataObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    UInt32 isFrmRecd;
    UInt32 lastFrmId;

} Chains_VipSingleCameraMdViewAppObj;

Void Chains_VipSingleCameraMdView_SetDisplayPrms(
                                DisplayMpLink_CreateParams *pPrm_Video,
                                DisplayLink_CreateParams *pPrm_Grpx,
                                Chains_DisplayType displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                )
{
    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Video->numPipes = 2u;
        pPrm_Video->displayId[0u] = DISPLAY_LINK_INST_DSS_VID1;

        pPrm_Video->prms[0u].tarWidth         = displayWidth;
        pPrm_Video->prms[0u].tarHeight        = displayHeight - MATA_DATA_SIZE;
        pPrm_Video->prms[0u].posX             = 0u;
        pPrm_Video->prms[0u].posY             = MATA_DATA_SIZE;
        pPrm_Video->prms[0u].overrideSrcSize  = 0u;

        pPrm_Video->displayId[1u] = DISPLAY_LINK_INST_DSS_VID2;

        pPrm_Video->prms[1u].tarWidth         = displayWidth;
        pPrm_Video->prms[1u].tarHeight        = MATA_DATA_SIZE;
        pPrm_Video->prms[1u].overrideSrcSize  = 1u;
        pPrm_Video->prms[1u].srcWidth         = displayWidth;
        pPrm_Video->prms[1u].srcHeight        = MATA_DATA_SIZE;
        pPrm_Video->prms[1u].posX             = 0u;
        pPrm_Video->prms[1u].posY             = 0u;
        pPrm_Video->prms[1u].srcPitch[0u]     = displayWidth*3u;
        pPrm_Video->prms[1u].srcPitch[1u]     = displayWidth*3u;
        pPrm_Video->prms[1u].srcPitch[2u]     = displayWidth*3u;
        pPrm_Video->prms[1u].srcDataFormat    = SYSTEM_DF_BGR24_888;
    }

    if(pPrm_Grpx)
    {
        pPrm_Grpx->displayId                  = DISPLAY_LINK_INST_DSS_GFX1;

        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

    }
}

Void Chains_VipSingleCameraMdView_NullCb(System_LinkChInfo *pChInfo,
    Void *pBuf, Void *arg)
{
    System_Buffer *pBuffer;
    System_VideoFrameBuffer *pVideoFrame;
    Chains_VipSingleCameraMdViewAppObj *pObj =
        (Chains_VipSingleCameraMdViewAppObj *)arg;
    UInt32 frameId, latency;
    UInt64 srcTime, dstTime;
    UInt8 *frmAddr;

    if ((NULL != pBuf) && (NULL != pObj))
    {
        pBuffer = (System_Buffer *)pBuf;

        pVideoFrame = pBuffer->payload;
        UTILS_assert(pVideoFrame != NULL);

        Cache_inv(
            pVideoFrame->bufAddr[0],
            pChInfo->pitch[0u]*pChInfo->height,
            Cache_Type_ALLD,
            TRUE);

        frmAddr = (UInt8 *)pVideoFrame->bufAddr[0];
        frameId = *(UInt32 *)frmAddr;
        frmAddr += sizeof(UInt32);
        srcTime = *(UInt64 *)frmAddr;
        frmAddr += sizeof(UInt64);
        dstTime = *(UInt64 *)frmAddr;

        /* Latency in msec*/
        latency = (dstTime - srcTime)/1000u;

        if (0u == pObj->isFrmRecd)
        {
            if (0U != frameId)
            {
                pObj->isFrmRecd = 1U;
                pObj->lastFrmId = frameId;
            }
        }
        else
        {
            if (abs(frameId - pObj->lastFrmId) > 1u)
            {
                Vps_printf("========= Frame Id mismatch =========\n");
                pObj->lastFrmId = frameId;
            }
            else
            {
                pObj->lastFrmId = frameId;
            }

            if (latency > MAX_LATENCY)
            {
                Vps_printf("Frame %d has latency %d \n", frameId, latency);
            }
        }
    }
}


Void Chains_VipSingleCameraMdView_SetNullPrms(
    Chains_VipSingleCameraMdViewAppObj *pObj, NullLink_CreateParams *pNullPrm)
{
    pNullPrm->appCb = Chains_VipSingleCameraMdView_NullCb;
    pNullPrm->appCbArg = (Void *)pObj;
}

static void Chains_VipSingleCameraMdView_SetCaptureDssWbPrms(
                                   CaptureLink_CreateParams *pPrm,
                                   UInt32 displayWidth,
                                   UInt32 displayHeight,
                                   Chains_DisplayType displayType)
{
    pPrm->numVipInst = 0;
    pPrm->numDssWbInst = 1;
    pPrm->dssWbInst[0].dssWbInstId = VPS_CAPT_INST_DSS_WB1;
    System_VideoScanFormat scanFormat = SYSTEM_SF_PROGRESSIVE;

    if ((CHAINS_DISPLAY_TYPE_SDTV_PAL  == displayType) ||
        (CHAINS_DISPLAY_TYPE_SDTV_NTSC == displayType))
        {
             scanFormat = SYSTEM_SF_INTERLACED;
        }

    pPrm->dssWbInst[0].dssWbInputPrms.inNode = SYSTEM_WB_IN_NODE_LCD1;
    /* Set this to SYSTEM_WB_IN_NODE_TV for TDA2xx platform
       and to SYSTEM_WB_IN_NODE_LCD1 for TDA3xx platform */
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceWidth = displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceHeight = displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInWidth = displayWidth;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInHeight = displayHeight;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosx = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbPosy = 0;
    pPrm->dssWbInst[0].dssWbInputPrms.wbInSourceDataFmt = SYSTEM_DF_BGR24_888;
    pPrm->dssWbInst[0].dssWbInputPrms.wbScanFormat = scanFormat;

    pPrm->dssWbInst[0].dssWbOutputPrms.wbWidth = displayWidth;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbHeight = displayHeight;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbDataFmt = SYSTEM_DF_BGR24_888;
    pPrm->dssWbInst[0].dssWbOutputPrms.wbScanFormat = scanFormat;

    pPrm->dssWbInst[0].numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
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
Void chains_vipSingleCam_Display_Metadata_SetAppPrms(
    chains_vipSingleCam_Display_MetadataObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraMdViewAppObj *pObj
        = (Chains_VipSingleCameraMdViewAppObj*)appObj;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

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

    pUcObj->CapturePrm.vipInst[0].numBufs = 6;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;

    Chains_VipSingleCameraMdView_SetDisplayPrms(&pUcObj->DisplayMultiPipe_VideoPrm,
                                &pUcObj->Display_GrpxPrm,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight
                               );

    Chains_VipSingleCameraMdView_SetCaptureDssWbPrms(
                              &pUcObj->Capture_dsswbPrm,
                              pObj->displayWidth,
                              pObj->displayHeight,
                              pObj->chainsCfg->displayType);


    Chains_VipSingleCameraMdView_SetNullPrms(pObj, &pUcObj->NullPrm);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    pObj->isFrmRecd = 0;
    pObj->lastFrmId = 0;
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
 * \param   pObj  [IN] Chains_VipSingleCameraViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_Display_Metadata_StartApp(
    Chains_VipSingleCameraMdViewAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCam_Display_Metadata_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_VipSingleCameraViewObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_Display_Metadata_StopAndDeleteApp(Chains_VipSingleCameraMdViewAppObj *pObj)
{
    chains_vipSingleCam_Display_Metadata_Stop(&pObj->ucObj);
    chains_vipSingleCam_Display_Metadata_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_vipSingleCamMd_runTimeMenu[] = {
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
Void Chains_vipSingleCam_Display_Metadata(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraMdViewAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCam_Display_Metadata_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_Display_Metadata_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_vipSingleCamMd_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_vipSingleCam_Display_Metadata_printStatistics(
                    &chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCam_Display_Metadata_StopAndDeleteApp(&chainsObj);
}

