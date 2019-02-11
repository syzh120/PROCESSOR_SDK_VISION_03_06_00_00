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
#include "chains_dispDistSrc_Display_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>

#define V_CONTROLLER_NAME            "/dev/vdrm-controller-0"
#define VDRM_CRTC                    (26)

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

    chains_dispDistSrc_DisplayObj ucObj;

    Chains_Ctrl *chainsCfg;

} Chains_DispDistSrcDisplayAppObj;

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
Void chains_dispDistSrc_Display_SetAppPrms(chains_dispDistSrc_DisplayObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth, displayHeight;
    DisplayLink_CreateParams *pPrm_display;

    Chains_DispDistSrcDisplayAppObj *pObj
        = (Chains_DispDistSrcDisplayAppObj*)appObj;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &displayWidth,
        &displayHeight
        );

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
    pPrm_display->displayId                 = DISPLAY_LINK_INST_DSS_GFX1;

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        displayWidth,
        displayHeight
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
 * \param   pObj  [IN] Chains_VipSingleCameraViewObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_dispDistSrc_Display_StartApp(Chains_DispDistSrcDisplayAppObj *pObj)
{
    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    chains_dispDistSrc_Display_Start(&pObj->ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);
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
Void chains_dispDistSrc_Display_StopAndDeleteApp(Chains_DispDistSrcDisplayAppObj *pObj)
{
    chains_dispDistSrc_Display_Stop(&pObj->ucObj);
    chains_dispDistSrc_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *`
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
Void Chains_dispDistSrc_Display(Chains_Ctrl *chainsCfg)
{
    char ch = 'a';
    UInt32 done = FALSE;
    Chains_DispDistSrcDisplayAppObj chainsObj;

    chainsObj.chainsCfg = chainsCfg;

    chains_dispDistSrc_Display_Create(&chainsObj.ucObj, &chainsObj);

    chains_dispDistSrc_Display_StartApp(&chainsObj);

    done = FALSE;
    while(!done)
    {
        ch = '1';
        ch = Chains_menuRunTime();
        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_dispDistSrc_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_dispDistSrc_Display_StopAndDeleteApp(&chainsObj);
}

