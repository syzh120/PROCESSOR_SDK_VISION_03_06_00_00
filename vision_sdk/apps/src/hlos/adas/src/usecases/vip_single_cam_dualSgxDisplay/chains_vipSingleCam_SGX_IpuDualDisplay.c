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
 * \file chains_vip_single_cam_dualDisplay.c
 *
 * \brief  Usecase file implementation of capture display usecase.
 *
 *         Usecase file for single camere view usecase.
 *
 *         Capture --> SgxDisplay Link(A15)
 *
 *
 *         In this use-case we capture 1 CH of video from OV1063x 720p30
 *         and send it to A15 using IPC_OUT, IPC_IN. A15 is running SgxDisplay
 *         Link which will render the frames and display via DRM
 *
 *         The data flow daigram is shown below
 *
 *             Capture (VIP) 1CH 30fps 1280x720 or 60fp 1920x1080
 *                   |
 *           |-------------------- |
 *        FPD display on M4      IPC OUT
 *                                  |
 *                                IPC IN
 *                                  |
 *                              SgxDisplay (A15)
 *                                  |
 *                                IPC OUT
 *                                  |
 *                                IPC IN
 *                                  |
 *                                HDMI display on M4

 * \version 0.0 (Jun 2014) : [CM] First version ported for linux.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "chains_vipSingleCam_SGX_IpuDualDisplay_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>

#define OVI_CAPTURE_SENSOR_WIDTH      (1280)
#define OVI_CAPTURE_SENSOR_HEIGHT     (720)
#define HDMI_CAPTURE_SENSOR_WIDTH     (1920)
#define HDMI_CAPTURE_SENSOR_HEIGHT    (1080)
#define FPD_DISPLAY_WIDTH             (1280)
#define FPD_DISPLAY_HEIGHT            (800)
#define HDMI_DISPLAY_WIDTH            (1920)
#define HDMI_DISPLAY_HEIGHT           (1080)

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCam_SGX_IpuDualDisplayObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    /**< Link Id's and device IDs to use for this use-case */
    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    UInt32  displayWidthFPD;
    UInt32  displayHeightFPD;
    UInt32  displayWidthHDMI;
    UInt32  displayHeightHDMI;
    Chains_Ctrl *chainsCfg;

}chains_vipSingleCam_SGX_IpuDualDisplayAppObj;

static struct control_srv_egl_ctx chainsEglParams = {
   .get_egl_native_display = gbm_allocator_get_native_display,
   .get_egl_native_buffer = gbm_allocator_get_native_buffer,
   .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
   .wrap_native_buffers = gbm_wrap_native_buffers,
   .wrapper_get_next_buffer = gbm_wrapper_get_next_buffer,
   .wrapper_put_buffer = gbm_wrapper_put_buffer,
   .unwrap_native_buffers = gbm_unwrap_native_buffers,
};

/**
 *******************************************************************************
 *
 * \brief   Set SGXDISPLAY Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/

Void chains_vipSingleCam_SGX_IpuDualDisplay_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_HDMI,
                                    DisplayLink_CreateParams *pPrm_FPD,
                                    UInt32 displayWidthHDMI,
                                    UInt32 displayHeightHDMI,
                                    UInt32 displayWidthLCD,
                                    UInt32 displayHeightLCD
                                    )
{
    if(pPrm_HDMI)
    {
        pPrm_HDMI->rtParams.tarWidth         = displayWidthHDMI;
        pPrm_HDMI->rtParams.tarHeight        = displayHeightHDMI;
        pPrm_HDMI->displayId                 = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_FPD)
    {
        pPrm_FPD->rtParams.tarWidth         = displayWidthLCD;
        pPrm_FPD->rtParams.tarHeight        = displayHeightLCD;
        pPrm_FPD->displayId                 = DISPLAY_LINK_INST_DSS_VID2;
    }

}

Void chains_vipSingleCam_SGX_IpuDualDisplay_SetSgxDisplayLinkPrms (
                                  SgxFrmcpyLink_CreateParams *prms,
                                  UInt32 width, UInt32 height)
{
    prms->displayWidth = width;
    prms->displayHeight = height;
    prms->renderType = SGXFRMCPY_RENDER_TYPE_1x1;
    prms->inBufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
    prms->bEglInfoInCreate = TRUE;
    prms->EglInfo = (void *)&chainsEglParams;
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
Void chains_vipSingleCam_SGX_IpuDualDisplay_SetAppPrms(chains_vipSingleCam_SGX_IpuDualDisplayObj *pUcObj,Void *appObj)
{
    UInt32 captureWidth = 0U, captureHeight = 0U;
    UInt32 captureOutWidth = 0U, captureOutHeight = 0U;

    chains_vipSingleCam_SGX_IpuDualDisplayAppObj *pObj
            = (chains_vipSingleCam_SGX_IpuDualDisplayAppObj*)appObj;

    if(pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P)
    {
        captureWidth  = HDMI_CAPTURE_SENSOR_WIDTH;
        captureHeight = HDMI_CAPTURE_SENSOR_HEIGHT;
        captureOutWidth  = HDMI_CAPTURE_SENSOR_WIDTH;
        captureOutHeight = HDMI_CAPTURE_SENSOR_HEIGHT;
    }
    else if(pObj->chainsCfg->captureSrc == CHAINS_CAPTURE_SRC_OV10635)
    {
        captureWidth  = OVI_CAPTURE_SENSOR_WIDTH;
        captureHeight = OVI_CAPTURE_SENSOR_HEIGHT;
        captureOutWidth  = OVI_CAPTURE_SENSOR_WIDTH;
        captureOutHeight = OVI_CAPTURE_SENSOR_HEIGHT;

        pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_OV10635;
        pObj->vidSensorPrm.isLVDSCaptMode = FALSE;
            pObj->vidSensorPrm.numLvdsCh = 1;

        System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                    APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                                    &pObj->vidSensorPrm,
                                    sizeof(VideoSensorCreateAndStartAppPrm),
                                    TRUE);
    }

    ChainsCommon_SingleCam_SetCapturePrms(&(pUcObj->CapturePrm),
            captureWidth,
            captureHeight,
            captureOutWidth,
            captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    /*ChainsCommon_GetDisplayWidthHeight(
        CHAINS_DISPLAY_TYPE_FPD,
        &displayWidth,
        &displayHeight
        );
    */

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                 HDMI_DISPLAY_WIDTH,
                                 HDMI_DISPLAY_HEIGHT
                                );

    pUcObj->Display_GrpxPrm.rtParams.tarWidth       = HDMI_DISPLAY_WIDTH;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight      = HDMI_DISPLAY_HEIGHT;
    pUcObj->Display_GrpxPrm.rtParams.posX           = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY           = 0;
    pUcObj->Display_GrpxPrm.displayId               = DISPLAY_LINK_INST_DSS_GFX1;

    chains_vipSingleCam_SGX_IpuDualDisplay_SetSgxDisplayLinkPrms
                                        (&pUcObj->SgxFrmcpyPrm,
                                            HDMI_DISPLAY_WIDTH,
                                            HDMI_DISPLAY_HEIGHT
                                            );

    chains_vipSingleCam_SGX_IpuDualDisplay_SetDisplayPrms(&pUcObj->Display_M4Prm,
                                                &pUcObj->Display_M4_FPDPrm,
                                                HDMI_DISPLAY_WIDTH,
                                                HDMI_DISPLAY_HEIGHT,
                                                FPD_DISPLAY_WIDTH,
                                                FPD_DISPLAY_HEIGHT
                                                );
    ChainsCommon_DualDisplay_StartDisplayCtrl(CHAINS_DISPLAY_TYPE_FPD,
                                FPD_DISPLAY_WIDTH, FPD_DISPLAY_HEIGHT);

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
 * \param   pObj  [IN] chains_vipSingleCam_SGX_IpuDualDisplayAppObj
 *
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_SGX_IpuDualDisplay_StartApp(chains_vipSingleCam_SGX_IpuDualDisplayAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    chains_vipSingleCam_SGX_IpuDualDisplay_Start(&pObj->ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Stop the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_vipSingleCam_SGX_IpuDualDisplayAppObj
 *
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_SGX_IpuDualDisplay_StopApp(chains_vipSingleCam_SGX_IpuDualDisplayAppObj *pObj)
{
    chains_vipSingleCam_SGX_IpuDualDisplay_Stop(&pObj->ucObj);

    chains_vipSingleCam_SGX_IpuDualDisplay_Delete(&pObj->ucObj);

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
Void chains_vipSingleCam_SGX_IpuDualDisplay(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_vipSingleCam_SGX_IpuDualDisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCam_SGX_IpuDualDisplay_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_SGX_IpuDualDisplay_StartApp(&chainsObj);

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
                chains_vipSingleCam_SGX_IpuDualDisplay_printStatistics(&chainsObj.ucObj);
                chains_vipSingleCam_SGX_IpuDualDisplay_printBufferStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCam_SGX_IpuDualDisplay_StopApp(&chainsObj);

}

