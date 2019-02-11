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
#include "chains_issIspSimcop_Display_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/adas/include/chains_common_iss.h>

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraFrameCopyObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issIspSimcop_DisplayObj  ucObj;

    UInt32                          displayWidth;
    UInt32                          displayHeight;

    Chains_Ctrl                    *chainsCfg;

    AppCtrl_IssParams               appCtrlIssPrms;

} chains_issIspSimcop_DisplayAppObj;


char gChains_IssIspSimcop_Display_runTimeMenu[] = {
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
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_issIspSimcop_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_SetDisplayPrms(
                                    Chains_DisplayType displayType,
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    UInt32 dispWidth, dispHeight;

    if(pPrm_Video)
    {
        /* To maintain the aspect ratio, change the display tarWidth */
        dispWidth = captureWidth * displayHeight / captureHeight;
        dispHeight = displayHeight;

        if (dispWidth > displayWidth)
        {
            dispWidth = displayWidth;
            dispHeight = displayWidth * captureHeight / captureWidth;
        }


        pPrm_Video->rtParams.tarWidth  = dispWidth;
        pPrm_Video->rtParams.tarHeight = dispHeight;
        pPrm_Video->rtParams.posX      = (displayWidth - dispWidth) / 2U;
        pPrm_Video->rtParams.posY      = (displayHeight - dispHeight) / 2U;

        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }

    if (pPrm_Grpx)
    {
        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
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
Void chains_issIspSimcop_Display_SetAppPrms(
    chains_issIspSimcop_DisplayObj *pUcObj, Void *appObj)
{
    chains_issIspSimcop_DisplayAppObj *pObj
        = (chains_issIspSimcop_DisplayAppObj*)appObj;
    AppCtrl_IssParams *pAppCtrlIssPrms;

    if ((strncmp(pObj->chainsCfg->sensorName,
         SENSOR_OMNIVISION_OV2775_TIDA1130, ISS_SENSORS_MAX_NAME) != 0) &&
        (strncmp(pObj->chainsCfg->sensorName,
         SENSOR_SONY_IMX390_UB953_D3, ISS_SENSORS_MAX_NAME) != 0))
    {
        Vps_printf("Sensor %s is not support for this usecase \n",
            pObj->chainsCfg->sensorName);
        return;
    }

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType, &pObj->displayWidth,
        &pObj->displayHeight);

    pAppCtrlIssPrms = &pObj->appCtrlIssPrms;

    AppCtrlLink_IssParams_Init(pAppCtrlIssPrms);

    strncpy(pAppCtrlIssPrms->issSensorInfo.sensorName,
        pObj->chainsCfg->sensorName, ISS_SENSORS_MAX_NAME);
    pAppCtrlIssPrms->issSensorInfo.numCh = 1;
    pAppCtrlIssPrms->issSensorInfo.ispOpMode = pObj->chainsCfg->ispOpMode;
    pAppCtrlIssPrms->issSensorInfo.simcopOpMode =
        ISSM2MSIMCOP_LINK_OPMODE_MAXNUM;

    pAppCtrlIssPrms->issCaptLinkId = pUcObj->IssCaptureLinkID;
    pAppCtrlIssPrms->issIspLinkId = pUcObj->IssM2mIspLinkID;
    pAppCtrlIssPrms->issAewbLinkId = pUcObj->Alg_IssAewbLinkID;
    pAppCtrlIssPrms->issSimcopLinkId = pUcObj->IssM2mSimcopLinkID;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_CREATE,
        &pAppCtrlIssPrms->issSensorInfo, sizeof(AppUtils_Obj), TRUE);

    memcpy(&pAppCtrlIssPrms->issCaptLinkPrms, &pUcObj->IssCapturePrm,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issIspLinkPrms, &pUcObj->IssM2mIspPrm,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pAppCtrlIssPrms->issAewbLinkPrms, &pUcObj->Alg_IssAewbPrm,
        sizeof(AlgorithmLink_IssAewbCreateParams));
    memcpy(&pAppCtrlIssPrms->issSimcopLinkPrms, &pUcObj->IssM2mSimcopPrm,
        sizeof(IssM2mSimcopLink_CreateParams));

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_INIT_ISS_PARAMS, pAppCtrlIssPrms,
        sizeof(AppCtrl_IssParams), TRUE);

    memcpy(&pUcObj->IssCapturePrm, &pAppCtrlIssPrms->issCaptLinkPrms,
        sizeof(IssCaptureLink_CreateParams));
    memcpy(&pUcObj->IssM2mIspPrm, &pAppCtrlIssPrms->issIspLinkPrms,
        sizeof(IssM2mIspLink_CreateParams));
    memcpy(&pUcObj->Alg_IssAewbPrm, &pAppCtrlIssPrms->issAewbLinkPrms,
        sizeof(AlgorithmLink_IssAewbCreateParams));
    memcpy(&pUcObj->IssM2mSimcopPrm, &pAppCtrlIssPrms->issSimcopLinkPrms,
        sizeof(IssM2mSimcopLink_CreateParams));

    pUcObj->IssM2mSimcopPrm.channelParams[0u].operatingMode =
        ISSM2MSIMCOP_LINK_OPMODE_VTNF;

    pUcObj->IssM2mIspPrm.channelParams[0u].
        enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0;

    /* Display requires around 4 buffers for 60fps chain, so increasing
       simcop output buffers to 4 */
    pUcObj->IssM2mIspPrm.channelParams[0].numBuffersPerCh = 4u;

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    pUcObj->IssM2mSimcopPrm.allocBufferForDump = TRUE;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight);

    chains_issIspSimcop_Display_SetDisplayPrms(
        pObj->chainsCfg->displayType, &pUcObj->Display_VideoPrm,
        &pUcObj->Display_GrpxPrm,
        pObj->displayWidth, pObj->displayHeight,
        pUcObj->IssM2mIspPrm.channelParams[0U].outParams.widthRszA,
        pUcObj->IssM2mIspPrm.channelParams[0U].outParams.heightRszA);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight);
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
 * \param   pObj  [IN] chains_issIspSimcop_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StartApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_START,
        &pObj->appCtrlIssPrms.issSensorInfo, sizeof(AppUtils_Obj), TRUE);

    /* Sets Default ISP/SIMCOP Config from DCC */
    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_DEFAULT_CONFIG,
        &pObj->appCtrlIssPrms.issSensorInfo, sizeof(AppUtils_Obj), TRUE);

    ChainsCommon_ReadAndParseDcc(&pObj->appCtrlIssPrms);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_SET_BOARD_MUXES, &pObj->appCtrlIssPrms.issSensorInfo,
        sizeof(AppUtils_Obj), TRUE);

    chains_issIspSimcop_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_issIspSimcop_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StopAndDeleteApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    chains_issIspSimcop_Display_Stop(&pObj->ucObj);
    chains_issIspSimcop_Display_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ISS_SENSOR_STOP_AND_DELETE,
        &pObj->appCtrlIssPrms.issSensorInfo, sizeof(AppUtils_Obj), TRUE);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);
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
Void Chains_issIspSimcop_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_issIspSimcop_DisplayAppObj chainsObj;

    Vps_printf(" Entered Chains_issIspSimcop_Display \n");

    chainsObj.chainsCfg = chainsCfg;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_issIspSimcop_Display_Create(&chainsObj.ucObj, &chainsObj);
    chains_issIspSimcop_Display_StartApp(&chainsObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
        APP_CTRL_LINK_CMD_ENABLE_CSI_OUTPUT,
        NULL, 0, TRUE);

    while(!done)
    {
        Vps_printf(gChains_IssIspSimcop_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_issIspSimcop_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_issIspSimcop_Display_StopAndDeleteApp(&chainsObj);

}

