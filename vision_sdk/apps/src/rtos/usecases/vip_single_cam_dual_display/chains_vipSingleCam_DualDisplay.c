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
#include "chains_vipSingleCam_DualDisplay_priv.h"
#include <src/include/chains_common.h>


#define CAPTURE_SENSOR_WIDTH    (1280)
#define CAPTURE_SENSOR_HEIGHT   (720)
#define HDMI_DISPLAY_WIDTH      (1920)
#define HDMI_DISPLAY_HEIGHT     (1080)


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

    chains_vipSingleCam_DualDisplayObj ucObj;

    UInt32                                  displayCtrlLinkId;
    DisplayCtrlLink_ConfigParams            dctrlCfgPrms;
    DisplayCtrlLink_OvlyParams              dctrlOvlyParamsLCD;
    DisplayCtrlLink_OvlyPipeParams          dctrlPipeOvlyParamsLCD;
    DisplayCtrlLink_OvlyParams              dctrlOvlyParamsHDMI;
    DisplayCtrlLink_OvlyPipeParams          dctrlPipeOvlyParamsHDMI;
    DisplayCtrlLink_OvlyPipeParams          dctrlPipeOvlyParamsGRPX;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidthLCD;
    UInt32  displayHeightLCD;
    UInt32  displayWidthHDMI;
    UInt32  displayHeightHDMI;

    Chains_Ctrl *chainsCfg;

} Chains_VipSingleCameraDualDisplayAppObj;


/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          Chains_VipSingleCameraDualDisplay_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_DualDisplay_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_HDMI,
                                    DisplayLink_CreateParams *pPrm_LCD,
                                    DisplayLink_CreateParams *pPrm_Grpx,
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
    else
    {

    }

    if(pPrm_LCD)
    {
        pPrm_LCD->rtParams.tarWidth         = displayWidthLCD;
        pPrm_LCD->rtParams.tarHeight        = displayHeightLCD;
        pPrm_LCD->displayId                 = DISPLAY_LINK_INST_DSS_VID2;
    }
    else
    {

    }

    if(pPrm_Grpx)
    {
        pPrm_Grpx->displayId                  = DISPLAY_LINK_INST_DSS_GFX1;
    }
    else
    {

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
Void chains_vipSingleCam_DualDisplay_SetAppPrms(chains_vipSingleCam_DualDisplayObj *pUcObj, Void *appObj)
{
    Chains_VipSingleCameraDualDisplayAppObj *pObj
        = (Chains_VipSingleCameraDualDisplayAppObj*)appObj;

    pObj->captureOutWidth   = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight  = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight
        (pObj->chainsCfg->displayType,
        &pObj->displayWidthLCD,
        &pObj->displayHeightLCD);

    pObj->displayWidthHDMI  = HDMI_DISPLAY_WIDTH;
    pObj->displayHeightHDMI = HDMI_DISPLAY_HEIGHT;

    ChainsCommon_SingleCam_SetCapturePrms(&pUcObj->CapturePrm,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidthHDMI,
                                               pObj->displayHeightHDMI
                                              );

    chains_vipSingleCam_DualDisplay_SetDisplayPrms(&pUcObj->Display_HDMIPrm,
                                                &pUcObj->Display_LCDPrm,
                                                &pUcObj->Display_GrpxPrm,
                                                pObj->displayWidthHDMI,
                                                pObj->displayHeightHDMI,
                                                pObj->displayWidthLCD,
                                                pObj->displayHeightLCD
                                                );

    //The displayType indicates which LCD model it is
    ChainsCommon_DualDisplay_StartDisplayCtrl(pObj->chainsCfg->displayType,
                                pObj->displayWidthLCD, pObj->displayHeightLCD);

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
 * \param   pObj  [IN] Chains_VipSingleCameraDualDisplayObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_DualDisplay_StartApp(Chains_VipSingleCameraDualDisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Explicitly start LCD device as it has to be powered up */
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    chains_vipSingleCam_DualDisplay_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_VipSingleCameraDualDisplayObj
 *
 *******************************************************************************
*/
Void chains_vipSingleCam_DualDisplay_StopAndDeleteApp(Chains_VipSingleCameraDualDisplayAppObj *pObj)
{
    chains_vipSingleCam_DualDisplay_Stop(&pObj->ucObj);
    chains_vipSingleCam_DualDisplay_Delete(&pObj->ucObj);

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
Void chains_vipSingleCam_DualDisplay(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_VipSingleCameraDualDisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_vipSingleCam_DualDisplay_Create(&chainsObj.ucObj, &chainsObj);

    chains_vipSingleCam_DualDisplay_StartApp(&chainsObj);

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
                chains_vipSingleCam_DualDisplay_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_vipSingleCam_DualDisplay_StopAndDeleteApp(&chainsObj);
}

