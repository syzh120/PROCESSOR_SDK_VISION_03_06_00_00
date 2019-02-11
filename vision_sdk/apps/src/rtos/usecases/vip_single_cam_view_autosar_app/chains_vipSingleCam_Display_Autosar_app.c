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
#include "chains_vipSingleCam_Display_Autosar_app_priv.h"
#include <src/include/chains_common.h>

#include <src/rtos/utils_common/include/utils_taskTimer.h>

#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

/*******************************************************************************
 *  Function Prototype's
 *******************************************************************************
 */
 
Void Autosar_sendMsg(UInt32 linkId);
Void Autosar_createBuffer(Void);
Void Autosar_deleteBuffer(Void);

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

    chains_vipSingleCam_Display_Autosar_appObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

} Chains_VipSingleCameraViewAutosarAppObj;

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
Void chains_vipSingleCam_Display_Autosar_app_SetAppPrms(chains_vipSingleCam_Display_Autosar_appObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraViewAutosarAppObj *pObj
        = (Chains_VipSingleCameraViewAutosarAppObj*)appObj;

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

    pUcObj->CapturePrm.vipInst[0].numBufs = 5;

    /*
     * This code snippet shows an example of allocating memory for
     * a link from within the use-case instead of from within the link
     *
     * This allows user's to potentially allocate memory statically outside of
     * link implementation and then pass the memory to the link during use-case
     * create.
     *
     * If user wants the link to allocate memory then dont set below parameters
     * <link create params>.memAllocInfo.memSize,
     * <link create params>.memAllocInfo.memAddr
     */
    /* memory for YUV420SP buffer's */
    pUcObj->CapturePrm.memAllocInfo.memSize =
       (CAPTURE_SENSOR_WIDTH * CAPTURE_SENSOR_HEIGHT *
        pUcObj->CapturePrm.vipInst[0].numBufs * 3) / 2 ;

    pUcObj->CapturePrm.memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pUcObj->CapturePrm.memAllocInfo.memSize,
                128
            );
    UTILS_assert(pUcObj->CapturePrm.memAllocInfo.memAddr!=NULL);

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

	Autosar_createBuffer();
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
Void chains_vipSingleCam_Display_Autosar_StartApp(Chains_VipSingleCameraViewAutosarAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* If Required : Override the display data-format here : Start */
    DisplayLink_SetCfgParams chPrms;

    chPrms.isChInfoChangeValid  = 0x01U;
    chPrms.chInfo.width         = CAPTURE_SENSOR_WIDTH;
    chPrms.chInfo.height        = CAPTURE_SENSOR_HEIGHT;
    chPrms.chInfo.pitch[0U]     = CAPTURE_SENSOR_WIDTH;
    chPrms.chInfo.pitch[1U]     = chPrms.chInfo.pitch[0U];
    chPrms.chInfo.pitch[2U]     = chPrms.chInfo.pitch[0U];
    chPrms.chInfo.flags         =
            System_Link_Ch_Info_Set_Flag_Data_Format(chPrms.chInfo.flags,
                                                    SYSTEM_DF_YUV420SP_UV);

    System_linkControl(pObj->ucObj.Display_VideoLinkID,
                       DISPLAY_LINK_CMD_SET_CFG_PARAMS,
                       &chPrms,
                       sizeof(DisplayLink_SetCfgParams),
                       TRUE);
    /* If Required : Override the display data-format here : End */

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCam_Display_Autosar_app_Start(&pObj->ucObj);

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
Void chains_vipSingleCam_Display_Autosar_StopAndDeleteApp(Chains_VipSingleCameraViewAutosarAppObj *pObj)
{
    chains_vipSingleCam_Display_Autosar_app_Stop(&pObj->ucObj);
    chains_vipSingleCam_Display_Autosar_app_Delete(&pObj->ucObj);

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
char gChains_vipSingleCamAutosar_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 2: Pause Capture"
    "\r\n 3: Resume Capture"
#ifdef ENABLE_TASK_PROFILE_UTIL
    "\r\n 4: Demonstrate Task Timer utility"
#endif
    "\r\n m: Send a messgae to Autosar"
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
Void Chains_vipSingleCam_Display_Autosar(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraViewAutosarAppObj chainsObj;
    Int32 status;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCam_Display_Autosar_app_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_Display_Autosar_StartApp(&chainsObj);

#ifdef ENABLE_TASK_PROFILE_UTIL

    status = Utils_taskTimerRegister();
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#endif /* ENABLE_TASK_PROFILE_UTIL */

    while(!done)
    {
        Vps_printf(gChains_vipSingleCamAutosar_runTimeMenu);

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

#ifdef ENABLE_TASK_PROFILE_UTIL
            case '4':
                Utils_taskTimerTestRun();
                status = SYSTEM_LINK_STATUS_SOK;
                break;
#endif /* ENABLE_TASK_PROFILE_UTIL */

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_vipSingleCam_Display_Autosar_app_printStatistics(&chainsObj.ucObj);
                break;

            case 'm':
            case 'M':
                Autosar_sendMsg(chainsObj.ucObj.AutosarIpcOutLinkID);
                break;

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

	Autosar_deleteBuffer();
#ifdef ENABLE_TASK_PROFILE_UTIL
    status = Utils_taskTimerDeRegister();
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
#endif /* ENABLE_TASK_PROFILE_UTIL */

    chains_vipSingleCam_Display_Autosar_StopAndDeleteApp(&chainsObj);
}

