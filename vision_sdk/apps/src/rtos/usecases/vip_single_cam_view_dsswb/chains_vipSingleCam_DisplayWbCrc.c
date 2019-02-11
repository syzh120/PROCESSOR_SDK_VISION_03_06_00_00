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
#include "chains_vipSingleCam_DisplayWbCrc_priv.h"
#include <src/include/chains_common.h>


#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

#define FRAME_FREEZE_CRC_PREV_OBJ_MAX      (10)
#define FRAME_FREEZE_DISPLAY_DURATION_MS   (24*60*60*1000)
#define FRAME_FREEZE_DISPLAY_FONTID        (5)

/* Display writes two pixels extra for the interlaced modes, so
   DSS write back should allocate memory for extra two pixels.
   This macro is used for providing extra pixels to the display write back path
   And also for configuring CRC modules ROI correctly. */
#define DISPLAY_WB_EXTRA_PIXELS             (2U)

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

    chains_vipSingleCam_DisplayWbCrcObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;
    Chains_Ctrl *chainsCfg;

    AlgorithmLink_CrcSig_Obj prevSig[FRAME_FREEZE_CRC_PREV_OBJ_MAX];
    UInt32  prevSigIndex;
    UInt32  isFrameFreezeDetected;

} Chains_VipSingleCameraViewDssWbCrcAppObj;

/*******************************************************************************
 *  \brief CRC Algorithm Callback function to get the CRC signature
 *
 *         Use this function to add the logic for Frame freeze decision making.
 *         CRC Alg only return the CRC signature for each frame.
 *         The implementation in SDK example detect "frame freeze" scenario
 *         if the CRC signature of 5 consecutive frames are the same.
 *         Also sends the frame freeze detect notification to GRPX link Once
 *         it detect the frame Freeze
 *
 *******************************************************************************
 */
void chains_vipSingleCam_DisplayWbCrc_CbFxn(
                         AlgorithmLink_CrcSig_Obj *crcSig,
                         Void *appData)
{
    UInt32 i, index;
    Bool isFrameFreezeDetect;
    GrpxSrcLink_StringRunTimePrintParams printPrms;
    Chains_VipSingleCameraViewDssWbCrcAppObj *pObj;
    Int32 heightOffset = 200;

    pObj = (Chains_VipSingleCameraViewDssWbCrcAppObj*) appData;

    pObj->prevSig[pObj->prevSigIndex].crcVal_L = crcSig->crcVal_L;
    pObj->prevSig[pObj->prevSigIndex].crcVal_H = crcSig->crcVal_H;
    pObj->prevSigIndex++;
    pObj->prevSigIndex %= FRAME_FREEZE_CRC_PREV_OBJ_MAX;

    index = 1;
    isFrameFreezeDetect = FALSE;
    /* Compare CRC signature value against previous CRC signatures */
    for (i = 0; i < FRAME_FREEZE_CRC_PREV_OBJ_MAX-index; i++)
    {
        if ((pObj->prevSig[i].crcVal_H == pObj->prevSig[i+index].crcVal_H) &&
            (pObj->prevSig[i].crcVal_L == pObj->prevSig[i+index].crcVal_L))
        {
            isFrameFreezeDetect = TRUE;
        }
        else
        {
            isFrameFreezeDetect = FALSE;
            break;
        }
    }

    if (isFrameFreezeDetect != pObj->isFrameFreezeDetected)
    {
        Int32 status = SYSTEM_LINK_STATUS_SOK;

        if (isFrameFreezeDetect)
        {
            snprintf(printPrms.stringInfo.string,
                     sizeof(printPrms.stringInfo.string) - 1,
                     "Frame Freeze Detected !!! \n");
        }
        else
        {
            snprintf(printPrms.stringInfo.string,
                     sizeof(printPrms.stringInfo.string) - 1,
                     " \n");
        }
        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
        printPrms.duration_ms = FRAME_FREEZE_DISPLAY_DURATION_MS;
        printPrms.stringInfo.fontType = FRAME_FREEZE_DISPLAY_FONTID;
        printPrms.stringInfo.startX  = 50;
        printPrms.stringInfo.startY  = pObj->displayHeight-heightOffset;

        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            Vps_printf(" ALG CRC: Send Command for Frame Freeze Detect failed \n");
        }
        pObj->isFrameFreezeDetected = isFrameFreezeDetect;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters of the DSS WB capture
 *
 *******************************************************************************
*/
static void chains_vipSingleCam_DisplayWbCrc_SetCaptureDssWbPrms(
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
 * \brief   Set link Parameters of ALG CRC link
 *
 *******************************************************************************
*/
static Void chains_vipSingleCam_DisplayWbCrc_SetcrcAlgPrms(
                                Chains_VipSingleCameraViewDssWbCrcAppObj *pObj,
                                AlgorithmLink_CrcCreateParams *pPrm,
                                UInt32 displayWidth,
                                UInt32 displayHeight,
                                Chains_DisplayType displayType)
{
    Int32 i;
    Int32 heightOffset = 200;

    if ((CHAINS_DISPLAY_TYPE_SDTV_PAL  == displayType) ||
        (CHAINS_DISPLAY_TYPE_SDTV_NTSC == displayType))
        {
             displayHeight /= 2;
             heightOffset  /= 2;
        }

    /* Currently, there is no API to get the Logo size or Grpx size,
       so hardcoding start offset and size for the grpx */

    /* Logo Width is 220, so keeping startX at 250 pixels */
    pPrm->startX    = 250;
    pPrm->startY    = 0;
    pPrm->roiWidth  = displayWidth - pPrm->startX;

    /* Bottom 174 lines are for the performance information of each core,
        so leaving 200 lines from bottom */
    pPrm->roiHeight = displayHeight - heightOffset;

    pPrm->roiWidth = (pPrm->roiWidth * 2) / 3;
    pPrm->roiHeight = (pPrm->roiHeight * 2) / 3;

    pPrm->appData  = pObj;
    pPrm->cfgCbFxn = chains_vipSingleCam_DisplayWbCrc_CbFxn;
    pObj->prevSigIndex          = 0;
    pObj->isFrameFreezeDetected = FALSE;
    for (i=0; i<FRAME_FREEZE_CRC_PREV_OBJ_MAX; i++)
    {
        pObj->prevSig[i].crcVal_L = i;
        pObj->prevSig[i].crcVal_H = i;
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
Void chains_vipSingleCam_DisplayWbCrc_SetAppPrms(chains_vipSingleCam_DisplayWbCrcObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraViewDssWbCrcAppObj *pObj
        = (Chains_VipSingleCameraViewDssWbCrcAppObj*)appObj;

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

    pUcObj->CapturePrm.vipInst[0].numBufs = 6U;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;

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

    if ((CHAINS_DISPLAY_TYPE_SDTV_PAL  == pObj->chainsCfg->displayType) ||
        (CHAINS_DISPLAY_TYPE_SDTV_NTSC == pObj->chainsCfg->displayType))
    {
         chains_vipSingleCam_DisplayWbCrc_SetCaptureDssWbPrms(
                                       &pUcObj->Capture_dsswbPrm,
                                       pObj->displayWidth + DISPLAY_WB_EXTRA_PIXELS,
                                       pObj->displayHeight,
                                       pObj->chainsCfg->displayType);

         chains_vipSingleCam_DisplayWbCrc_SetcrcAlgPrms(
                                       pObj,
                                       &pUcObj->Alg_CrcPrm,
                                       pObj->displayWidth + DISPLAY_WB_EXTRA_PIXELS,
                                       pObj->displayHeight,
                                       pObj->chainsCfg->displayType);
    }
    else
    {
         chains_vipSingleCam_DisplayWbCrc_SetCaptureDssWbPrms(
                                       &pUcObj->Capture_dsswbPrm,
                                       pObj->displayWidth,
                                       pObj->displayHeight,
                                       pObj->chainsCfg->displayType);

         chains_vipSingleCam_DisplayWbCrc_SetcrcAlgPrms(
                                       pObj,
                                       &pUcObj->Alg_CrcPrm,
                                       pObj->displayWidth,
                                       pObj->displayHeight,
                                       pObj->chainsCfg->displayType);
    }
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
Void chains_vipSingleCam_DisplayWbCrc_StartApp(Chains_VipSingleCameraViewDssWbCrcAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCam_DisplayWbCrc_Start(&pObj->ucObj);

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
Void chains_vipSingleCam_DisplayWbCrc_StopAndDeleteApp(Chains_VipSingleCameraViewDssWbCrcAppObj *pObj)
{
    chains_vipSingleCam_DisplayWbCrc_Stop(&pObj->ucObj);
    chains_vipSingleCam_DisplayWbCrc_Delete(&pObj->ucObj);

    if(pObj->ucObj.CapturePrm.memAllocInfo.memAddr)
    {
        Int32 status;

        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pObj->ucObj.CapturePrm.memAllocInfo.memAddr,
                    pObj->ucObj.CapturePrm.memAllocInfo.memSize);
        UTILS_assert(status==0);
    }

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
char gChains_vipSingleCamWbCrc_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 2: Pause Capture"
    "\r\n 3: Resume Capture"
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
Void Chains_vipSingleCam_DisplayWbCrc(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraViewDssWbCrcAppObj chainsObj;
    Int32 status;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCam_DisplayWbCrc_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_DisplayWbCrc_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_vipSingleCamWbCrc_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '2':
                status = System_linkStop(chainsObj.ucObj.CaptureLinkID);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                break;

            case '3':
                status = System_linkStart(chainsObj.ucObj.CaptureLinkID);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_vipSingleCam_DisplayWbCrc_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCam_DisplayWbCrc_StopAndDeleteApp(&chainsObj);
}

