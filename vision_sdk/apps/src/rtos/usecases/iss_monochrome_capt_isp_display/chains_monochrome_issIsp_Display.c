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
#include "chains_monochrome_issIsp_Display_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_iss.h>


#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

/**
 *******************************************************************************
 *
 *  \brief  chains_monochrome_capt_Isp_DisplayAppObj
 *
 *        Usecase App Object, contains ID of the links used,
 *        link's create Params and other global information.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_monochrome_issIsp_DisplayObj ucObj;

    IssIspConfigurationParameters ispConfig;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    IssM2mSimcopLink_OperatingMode simcopMode;
    Bool bypassVtnf;
    Bool bypassLdc;
} chains_monochrome_capt_Isp_DisplayAppObj;


/** \brief Runtime options for this usecase
 *         Currently it supports only saving captured frame
 */
char gChains_Iss_Monochrome_IspSimcop_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n 1: Toggle VTNF ON/OFF"
"\r\n 2: Toggle LDC  ON/OFF"
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

/**
 *******************************************************************************
 *
 *  \brief  Function to set Simcop Configuration
 *
 *        This function called at usecase runtime, to enable/disable LDC
 *        and VTNF.
 *
 *  \params pObj        [IN] Pointer to usecase App Object
 *
 *******************************************************************************
*/
Void chains_monochrome_issIsp_Display_SetSimcopConfig(
            chains_monochrome_capt_Isp_DisplayAppObj *pObj)
{
    ChainsCommon_SetIssSimcopLdcVtnfRtConfig(
        &pObj->ldcCfg,
        &pObj->vtnfCfg,
        pObj->bypassVtnf,
        pObj->bypassLdc);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* MUST be called after link create and before link start */
    System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function.
 *          It calculates and sets the display pipeline parameters, like
 *          its position and size in the display frame, based on the
 *          capture/resizer output frame size.
 *          It is advisable to have
 *          chains_issIspSimcop_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams for Video
 * \param   pPrm         [IN]    DisplayLink_CreateParams for Grpx
 * \param   displayType  [IN]    Type of the display ie standard/resolution
 * \param   displayWidth [IN]    Display Resolution Width
 * \param   displayHeight[IN]    Display Resolution Height
 * \param   captureWidth [IN]    Capture Resolution Width
 * \param   captureHeight[IN]    Capture Resolution Height
 *
 *******************************************************************************
*/
Void chains_monochrome_issIsp_Display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    Chains_DisplayType displayType,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    UInt32 dispWidth, dispHeight;

    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        /* If the display resolution is higher than the capture resolution,
           no change in display frame size ie frame will be displayed
           at the center of the display */
        if (displayWidth > captureWidth && displayHeight > captureHeight)
        {
            dispWidth = captureWidth;
            dispHeight = captureHeight;
        }
        else
        {
            /* If the display resolition is smaller than capture,
               Change the final display size such that capture aspect ratio
               is maintained. */
            dispWidth = captureWidth * displayHeight / captureHeight;
            dispHeight = displayHeight;

            if (dispWidth > displayWidth)
            {
                dispWidth = displayWidth;
                dispHeight = displayWidth * captureHeight / captureWidth;
            }

        }

        /* Set the display target frame size and position */
        pPrm_Video->rtParams.tarWidth  = dispWidth;
        pPrm_Video->rtParams.tarHeight = dispHeight;
        if (displayWidth > dispWidth)
        {
            pPrm_Video->rtParams.posX = (displayWidth - dispWidth) / 2U;
        }
        else
        {
            pPrm_Video->rtParams.posX = (dispWidth - displayWidth) / 2U;
        }
        if (displayHeight > dispHeight)
        {
            pPrm_Video->rtParams.posY = (displayHeight - dispHeight) / 2U;
        }
        else
        {
            pPrm_Video->rtParams.posY = (dispHeight - displayHeight) / 2U;
        }

        pPrm_Video->displayId = DISPLAY_LINK_INST_DSS_VID1;
    }

    /* Initialize Grpx parameters */
    if(pPrm_Grpx)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set ISP Configuration
 *
 *          This function uses the default configuration from video senser
 *          layer and sets it in the ISP link.
 *          It is called just before starting the application.
 *
 * \param pObj  [IN]    Pointer to Usecase Application Object containing
 *                      ISP configuration instance
 */
Void chains_monochrome_issIsp_Display_SetIspConfig(
            chains_monochrome_capt_Isp_DisplayAppObj *pObj)
{
    Int32 status;

    /* set default params */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);
    vpsissLdcCfg_init(&pObj->ldcCfg);
    vpsissVtnfCfg_init(&pObj->vtnfCfg);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Set the Default SimCop configuration,
        This could get overwriten by DCC */
    ChainsCommon_SetIssSimcopConfig(
        &pObj->simcopConfig,
        pObj->bypassVtnf,
        pObj->bypassLdc,
        0);

    ChainsCommon_IssGetDefaultIspSimcopConfig(
        ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME,
        &pObj->ispConfig,
        &pObj->simcopConfig,
        0U);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
            &pObj->ispConfig,
            sizeof(pObj->ispConfig),
            TRUE);
    UTILS_assert(0 == status);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
    UTILS_assert(0 == status);
}


/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *          It initializes create parameters of the all links based on the
 *          usecase parameters.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_monochrome_issIsp_Display_SetAppPrms(
        chains_monochrome_issIsp_DisplayObj *pUcObj,
        Void *appObj)
{
    chains_monochrome_capt_Isp_DisplayAppObj *pObj
        = (chains_monochrome_capt_Isp_DisplayAppObj *)appObj;
    IssM2mIspLink_OperatingMode ispOpMode;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight);

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF;
    pObj->bypassVtnf = FALSE;
    pObj->bypassLdc  = FALSE;

    if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
        (pObj->chainsCfg->issVtnfEnable == TRUE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = FALSE;
        pObj->bypassLdc  = TRUE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == TRUE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = FALSE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = TRUE;
    }

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME;

    ChainsCommon_SingleCam_SetCapturePrms(&pUcObj->CapturePrm,
            CAPTURE_SENSOR_WIDTH,
            CAPTURE_SENSOR_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    ChainsCommon_SetIssCreatePrms(
        pObj->chainsCfg->sensorName,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        pObj->displayWidth,
        pObj->displayHeight,
        pObj->simcopMode,
        ispOpMode,
        NULL);

    pUcObj->CapturePrm.vipInst[0].numBufs = 5;

    ChainsCommon_SetIssIspPrms(
        &pUcObj->IssM2mIspPrm,
        CAPTURE_SENSOR_WIDTH,
        CAPTURE_SENSOR_HEIGHT,
        0U,0U,
        ispOpMode,
        NULL);
    pUcObj->IssM2mIspPrm.channelParams[0].enableOut[
        ISSM2MISP_LINK_OUTPUTQUE_H3A]  = 0;

    ChainsCommon_SetIssSimcopPrms(
        &pUcObj->IssM2mSimcopPrm,
        pObj->simcopMode);

    /* Initialize GRPX Parameters */
    ChainsCommon_SetGrpxSrcPrms(
        &pUcObj->GrpxSrcPrm,
        pObj->displayWidth,
        pObj->displayHeight);

    /* Set the Display Pipeline Parameters */
    chains_monochrome_issIsp_Display_SetDisplayPrms(
        &pUcObj->Display_VideoPrm,
        &pUcObj->Display_GrpxPrm,
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight,
        pObj->captureOutWidth,
        pObj->captureOutHeight);

    /* Start the display controller, at this point, VENC will start running */
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
 * \param   pObj  [IN] chains_monochrome_capt_Isp_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_monochrome_issIsp_Display_StartApp(
    chains_monochrome_capt_Isp_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Set Sensor specific ISP configuration */
    chains_monochrome_issIsp_Display_SetIspConfig(pObj);

    ChainsCommon_IssStopAndDeleteCaptureDevice();

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    /* Start Display pipeline */
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    /* Set the complete chain */
    chains_monochrome_issIsp_Display_Start(&pObj->ucObj);

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
 * \param   pObj   [IN]   chains_monochrome_capt_Isp_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_monochrome_issIsp_Display_StopAndDeleteApp(
    chains_monochrome_capt_Isp_DisplayAppObj *pObj)
{
    chains_monochrome_issIsp_Display_Stop(&pObj->ucObj);
    chains_monochrome_issIsp_Display_Delete(&pObj->ucObj);

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
 * \brief   Single Channel Monochrome ISS Capture -> ISP -> Display usecase
 *          function
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
Void Chains_monochrome_issIsp_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_monochrome_capt_Isp_DisplayAppObj chainsObj;

    if ((chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_AR0132MONOCHROME_PARALLEL) &&
        (chainsCfg->captureSrc != CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL))
    {
        Vps_printf(" CHAINS: Unsupported sensor for this usecase. !!!\n");
        return;
    }
    chainsCfg->captureSrc = CHAINS_CAPTURE_SRC_AR0132MONOCHROME_PARALLEL;
    chainsCfg->ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME;
    if(ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME != chainsCfg->ispOpMode)
    {
        Vps_printf(" CHAINS: WDR Mode is not supported for this usecase!!!\n");
        return;
    }

    chainsObj.chainsCfg = chainsCfg;

    chains_monochrome_issIsp_Display_Create(&chainsObj.ucObj, &chainsObj);
    chains_monochrome_issIsp_Display_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_Iss_Monochrome_IspSimcop_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                /* toogle VTNF ON/OFF */
                chainsObj.bypassVtnf ^= 1;
                chains_monochrome_issIsp_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassVtnf)
                {
                    Vps_printf(" CHAINS: VTNF is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: VTNF is ENABLED !!!\n");
                }
                break;
            case '2':
                /* toogle LDC ON/OFF */
                chainsObj.bypassLdc ^= 1;
                chains_monochrome_issIsp_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassLdc)
                {
                    Vps_printf(" CHAINS: LDC is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: LDC is ENABLED !!!\n");
                }
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_monochrome_issIsp_Display_printStatistics(
                    &chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_monochrome_issIsp_Display_StopAndDeleteApp(&chainsObj);

}

