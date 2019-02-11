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
#include "chains_earlyCaptureLateWeston_priv.h"
#include <src/include/chains.h>
#include <src/include/chains_common.h>

#define V_CONTROLLER_NAME         "/dev/vdrm-controller-0"
#define VDRM_CRTC                 (26)
#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

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

    chains_earlyCaptureLateWestonObj ucObj;

    Chains_Ctrl *chainsCfg;

} chains_earlyCaptureLateWestonAppObj;

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
Void chains_earlyCaptureLateWeston_SetAppPrms(chains_earlyCaptureLateWestonObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth, displayHeight;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];

    chains_earlyCaptureLateWestonAppObj *pObj
        = (chains_earlyCaptureLateWestonAppObj*)appObj;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &displayWidth,
        &displayHeight
        );
    Vps_printf("Display width %d, Display height %d\n",displayWidth,displayHeight);

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                CAPTURE_SENSOR_WIDTH,
                                CAPTURE_SENSOR_HEIGHT
                                );
    pUcObj->Display_VideoPrm.displayId = DISPLAY_LINK_INST_DSS_VID2;

    UInt32 i;
    CaptureLink_VipInstParams *pInstPrm;
    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pUcObj->CapturePrm.vipInst[i];
        pInstPrm->numBufs = 5;
        /* skip alternate frame to make it 15fps output for Front camera */
        if (i >= 4)
            pInstPrm->outParams[0].frameSkipMask = 0x2AAAAAAA;
    }
    
    ChainsCommon_MultiCam_StartCaptureDevice(pObj->chainsCfg->captureSrc,
            portId,
            pObj->chainsCfg->numLvdsCh);

    ChainsCommon_MultiCam_SetCapturePrms(
                    &pUcObj->CapturePrm,
                    CAPTURE_SENSOR_WIDTH,
                    CAPTURE_SENSOR_HEIGHT,
                    portId,
                    pObj->chainsCfg->numLvdsCh);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        displayWidth,
        displayHeight
        );
}

/*Set AppPrms for late part of the chain*/

Void chains_earlyCaptureLateWeston_SetAppPrmsLate(chains_earlyCaptureLateWestonObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth, displayHeight;
    displayWidth = 1920;
    displayHeight = 1080;
    DisplayLink_CreateParams *pPrm_display;
    sprintf((char *)pUcObj->DispDistSrc_westonPrm.vDrmControllerName, V_CONTROLLER_NAME);
    pUcObj->DispDistSrc_westonPrm.vDrmControllerObjectId = VDRM_CRTC;
    pUcObj->DispDistSrc_westonPrm.vDrmControllerObjectType = DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_CRTC;
    pUcObj->DispDistSrc_westonPrm.width = displayWidth;
    pUcObj->DispDistSrc_westonPrm.height = displayHeight;
    pUcObj->DispDistSrc_westonPrm.format = SYSTEM_DF_BGRX24_8888;

    pPrm_display = &pUcObj->Display_m4Prm;
    pPrm_display->rtParams.tarWidth         = displayWidth;
    pPrm_display->rtParams.tarHeight        = displayHeight;
    pPrm_display->rtParams.posX             = 0;
    pPrm_display->rtParams.posY             = 0;
    pPrm_display->displayId                 = DISPLAY_LINK_INST_DSS_VID1;
}
/**
 *******************************************************************************
 *
 * \brief   Start the early part of the use-case
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverse
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_VipSingleCameraViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_earlyCaptureLateWeston_StartApp(chains_earlyCaptureLateWestonAppObj *pObj)
{
    chains_earlyCaptureLateWeston_Start(&pObj->ucObj);
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
Void chains_earlyCaptureLateWeston_StopAndDeleteApp(chains_earlyCaptureLateWestonAppObj *pObj)
{
    chains_earlyCaptureLateWeston_Stop(&pObj->ucObj);
    chains_earlyCaptureLateWeston_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase and weston display use-case
 *`
 *          This functions executes the create, start functions
 *
 *          Function executes early part of the chain (capture -> display) by 
 *          default and waits for Linux init to complete to start the late part
 *          of the chain (displayDist -> display).
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/

Void chains_earlyCaptureLateWeston(Chains_Ctrl *chainsCfg)
{
    UInt32 done = FALSE;
    Bool printNotDone = TRUE;
    chains_earlyCaptureLateWestonAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_earlyCaptureLateWeston_Create(&chainsObj.ucObj, &chainsObj);

    chains_earlyCaptureLateWeston_StartApp(&chainsObj);

    while(!done)
    {
        Task_sleep(100);
        if(chainsCfg->linux_InitComplete && printNotDone)
        {
            chains_earlyCaptureLateWeston_CreateLate(&chainsObj.ucObj, &chainsObj);
            chains_earlyCaptureLateWeston_StartLate(&chainsObj.ucObj);
            printNotDone = FALSE;
            done = FALSE;
        }
    }

    chains_earlyCaptureLateWeston_StopAndDeleteApp(&chainsObj);
}

