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

#define OV10635_SENSOR_WIDTH            (1280)
#define OV10635_SENSOR_HEIGHT           (720)

#define OV490_SENSOR_WIDTH              (1280)
#define OV490_SENSOR_HEIGHT             (1080)

#define CAPTURE_OUTPUT_WIDTH            (1280)
#define CAPTURE_OUTPUT_HEIGHT           (720)

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_lvdsVipSingleCam_Display_priv.h"
#include <src/include/chains_common.h>
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

    chains_lvdsVipSingleCam_DisplayObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    UInt32  numLvdsCh;
    /**< Number of channels of LVDS to enable */

    UInt32  netProcId;


    Chains_Ctrl *chainsCfg;

} Chains_LvdsVipSingleCam_DisplayAppObj;

/**
 *******************************************************************************
 * \brief   Set create parameters for NullSrc
 *******************************************************************************
*/
Void chains_lvdsVipSingleCam_Display_SetNetworkTxPrms(chains_lvdsVipSingleCam_DisplayObj *pObj,
                        NetworkTxLink_CreateParams *pPrm)
{
    pPrm->networkServerPort = NETWORK_TX_SERVER_PORT;

    /* Select network mode for null link */
    ChainsCommon_networkTxSetMode(pPrm);
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
Void chains_lvdsVipSingleCam_Display_SetAppPrms(chains_lvdsVipSingleCam_DisplayObj *pUcObj, Void *appObj)
{
    Chains_LvdsVipSingleCam_DisplayAppObj *pObj
        = (Chains_LvdsVipSingleCam_DisplayAppObj*)appObj;

    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];

    pUcObj->IPCIn_A15_0_IPU1_0_0LinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->IPCIn_A15_0_IPU1_0_0LinkID);

    pUcObj->NetworkTxLinkID
        = SYSTEM_MAKE_LINK_ID(
            pObj->netProcId,
            pUcObj->NetworkTxLinkID);

    pObj->numLvdsCh = pObj->chainsCfg->numLvdsCh;

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
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            portId,
            pObj->numLvdsCh
            );
    ChainsCommon_MultiCam_SetCroppingPrms(&pUcObj->CapturePrm,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            CAPTURE_OUTPUT_WIDTH,
            CAPTURE_OUTPUT_HEIGHT
            );

    chains_lvdsVipSingleCam_Display_SetNetworkTxPrms(
        pUcObj,
        &pUcObj->NetworkTxPrm
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
 * \param   pObj  [IN] Chains_LvdsVipSingleCam_DisplayObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Void chains_lvdsVipSingleCam_Display_StartApp(Chains_LvdsVipSingleCam_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_lvdsVipSingleCam_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   Chains_LvdsVipSingleCam_DisplayObj
 *
 *******************************************************************************
*/
static Void chains_lvdsVipSingleCam_Display_StopAndDeleteApp(Chains_LvdsVipSingleCam_DisplayAppObj *pObj)
{
    chains_lvdsVipSingleCam_Display_Stop(&pObj->ucObj);
    chains_lvdsVipSingleCam_Display_Delete(&pObj->ucObj);

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
Void Chains_lvdsVipSingleCam_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Chains_LvdsVipSingleCam_DisplayAppObj chainsObj;

    chainsObj.netProcId = Utils_netGetProcId();
    if(chainsObj.netProcId==System_getSelfProcId())
    {
        Vps_printf(" \n");
        Vps_printf(" CHAINS: ERROR: Networking/NDK MUST be run on different CPU"
                   " than IPU1-0.\n");
        Vps_printf(" CHAINS: ERROR: If you need to run this use-case with NDK"
                   " on IPU1-0 then regenerate the use-case with NullSrc/Null"
                   " links on IPU1-0.\n"
                   );
        Vps_printf(" \n");
        return;
    }

    switch (chainsCfg->captureSrc) {
        case CHAINS_CAPTURE_SRC_OV490:
            chainsObj.captureOutWidth = OV490_SENSOR_WIDTH;
            chainsObj.captureOutHeight = OV490_SENSOR_HEIGHT;
            break;
        case CHAINS_CAPTURE_SRC_OV10635:
            chainsObj.captureOutWidth = OV10635_SENSOR_WIDTH;
            chainsObj.captureOutHeight = OV10635_SENSOR_HEIGHT;
            break;        
        default:
            Vps_printf("\n Unsupported capture source: %s\n", chainsCfg->sensorName);
            return;
    }
    chainsObj.chainsCfg = chainsCfg;
    
    chains_lvdsVipSingleCam_Display_Create(&chainsObj.ucObj, &chainsObj);

    chains_lvdsVipSingleCam_Display_StartApp(&chainsObj);

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
                chains_lvdsVipSingleCam_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_lvdsVipSingleCam_Display_StopAndDeleteApp(&chainsObj);
}

