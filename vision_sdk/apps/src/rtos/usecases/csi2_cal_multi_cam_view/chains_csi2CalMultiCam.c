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
#include "chains_csi2CalMultiCam_priv.h"
#include <src/include/chains_common.h>

#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/examples/utility/bsputils_ub960.h>


/*******************************************************************************
 *  Constants
 *******************************************************************************
 */
/**< Width & Height */
#define CAPTURE_SENSOR_WIDTH        (1280)
/**< Width & Height */
#define CAPTURE_SENSOR_HEIGHT       (720)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK_PHY_0  (800U)
/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK_PHY_1  (800U)
/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH          (5U)

/**
 *******************************************************************************
 *
 *  \brief  CAL Multichannel Capture & Display Object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_csi2CalMultiCamObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;
    UInt32  displayActiveChId;
    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
    UInt32  numLanesOnPhy1Csi2; /* Valid value is 2 only, H/W limit */
    VidSensor_CreateParams sensorCreateParam;
    VidSensor_CreateStatus sensorCreateStatus;

    Chains_Ctrl *chainsCfg;

} Chains_csi2CalMultiCamAppObj;

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static Void setCaptureParams(Chains_csi2CalMultiCamAppObj *pObj)
{
    UInt32 idx;
    IssCaptureLink_CreateParams *pCaptPrm;
    IssCaptureLink_Csi2Params   *pCsi2Prm;
    IssCaptureLink_OutParams    *pOutPrm;
    System_VideoDataFormat      inOutDataFormat;

    pCaptPrm = &pObj->ucObj.IssCapturePrm;
    memset((void*) pCaptPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pCaptPrm->videoIfMode            = SYSTEM_VIFM_SCH_CSI2;
    pCaptPrm->videoIfWidth           = SYSTEM_VIFW_4LANES;
    pCaptPrm->bufCaptMode            = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;

    for (idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
    {
        pCsi2Prm = &pCaptPrm->csi2Params[idx];

        pCsi2Prm->isCmplxIoCfgValid = FALSE;
        pCsi2Prm->csi2PhyClk        = CAPTURE_UB964_CSI2_CLOCK_PHY_0;

        pCsi2Prm->cmplxIoCfg.clockLane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.clockLane.position = 1U;
        pCsi2Prm->cmplxIoCfg.data1Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data1Lane.position = 2U;
        pCsi2Prm->cmplxIoCfg.data2Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data2Lane.position = 3U;
        pCsi2Prm->cmplxIoCfg.data3Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data3Lane.position = 4U;
        pCsi2Prm->cmplxIoCfg.data4Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data4Lane.position = 5U;
    }
    /* UB964 Can support only 1 interface*/
    pCaptPrm->csi2Params[0U].isCmplxIoCfgValid = TRUE;

    if (2U == pObj->numLanesOnPhy0Csi2)
    {
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data3Lane.position = 0U;
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data4Lane.position = 0U;
    }
    if (2U == pObj->numLanesOnPhy1Csi2)
    {
        pCaptPrm->csi2Params[1U].isCmplxIoCfgValid = TRUE;
        pCaptPrm->csi2Params[1U].csi2PhyClk = CAPTURE_UB964_CSI2_CLOCK_PHY_1;

        pCaptPrm->csi2Params[1U].cmplxIoCfg.data3Lane.position = 0U;
        pCaptPrm->csi2Params[1U].cmplxIoCfg.data4Lane.position = 0U;
    }

    pCaptPrm->numCh = pObj->numCsi2Ch;

    inOutDataFormat = SYSTEM_DF_YUV422I_YUYV;
    if (BSP_PLATFORM_SOC_ID_TDA3XX == Bsp_platformGetSocId())
    {
        inOutDataFormat = SYSTEM_DF_YUV422I_UYVY;
    }
    for (idx = 0U; idx < pCaptPrm->numCh; idx++)
    {
        pOutPrm = &pCaptPrm->outParams[idx];
        pOutPrm->phyInstance    = 0U;
        pOutPrm->width          = pObj->captureOutWidth;
        pOutPrm->height         = pObj->captureOutHeight;
        pOutPrm->dataFormat     = inOutDataFormat;
        pOutPrm->inCsi2DataFormat       = SYSTEM_CSI2_YUV422_8B;
        pOutPrm->inCsi2VirtualChanNum   = idx;
        pOutPrm->maxWidth       = pObj->captureOutWidth;
        pOutPrm->maxHeight      = pObj->captureOutHeight;
        pOutPrm->numOutBuf      = CAPTURE_NUM_BUF_PER_CH;
        pOutPrm->outDataFormat  = inOutDataFormat;
        pOutPrm->outBpp         = SYSTEM_BPP_BITS16;
        if (idx >= 4)
        {
            pOutPrm->phyInstance    = 1U;
        }
    }
    pCaptPrm->allocBufferForRawDump  = FALSE;

    return;
}

static Void switchDisplayChannel(Chains_csi2CalMultiCamAppObj *pObj)
{
    DisplayLink_SwitchChannelParams displayPrm;

    pObj->displayActiveChId++;
    if(pObj->displayActiveChId >= pObj->numCsi2Ch)
        pObj->displayActiveChId = 0;

    displayPrm.activeChId = pObj->displayActiveChId;

    Vps_printf(" Switching Display to channel %d ", pObj->displayActiveChId);

    System_linkControl(pObj->ucObj.Display_VideoLinkID,
                                DISPLAY_LINK_CMD_SWITCH_CH,
                                &displayPrm,
                                sizeof(displayPrm),
                                TRUE);
}

/*******************************************************************************
 *  Function to apply Link configurations.
 *******************************************************************************
 */
Void chains_csi2CalMultiCam_SetAppPrms(chains_csi2CalMultiCamObj *pObj,
                                        Void *appObj)
{
    Chains_csi2CalMultiCamAppObj *pAppObj =
                                        (Chains_csi2CalMultiCamAppObj*) appObj;

    setCaptureParams(pAppObj);

    ChainsCommon_SetGrpxSrcPrms(&pAppObj->ucObj.GrpxSrcPrm,
                                pAppObj->displayWidth,
                                pAppObj->displayHeight);

    ChainsCommon_SetDisplayPrms(&pAppObj->ucObj.Display_VideoPrm,
                                &pAppObj->ucObj.Display_GrpxPrm,
                                pAppObj->chainsCfg->displayType,
                                pAppObj->displayWidth,
                                pAppObj->displayHeight);

    ChainsCommon_StartDisplayCtrl(pAppObj->chainsCfg->displayType,
                                    pAppObj->displayWidth,
                                    pAppObj->displayHeight);

    return;
}

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
Void chains_csi2CalMultiCam_StartApp(Chains_csi2CalMultiCamAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    ChainsCommon_MultiCam_StartCaptureDevice(pObj->chainsCfg->captureSrc,
                                            NULL,
                                            pObj->numCsi2Ch);

    chains_csi2CalMultiCam_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
    return;
}

Void chains_csi2CalMultiCam_StopAndDeleteApp(Chains_csi2CalMultiCamAppObj *pObj)
{
    chains_csi2CalMultiCam_Stop(&pObj->ucObj);
    chains_csi2CalMultiCam_Delete(&pObj->ucObj);

    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}


Void Chains_csi2CalMultiCam(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    Bsp_PlatformSocId socId;
    Chains_csi2CalMultiCamAppObj chainsObj;
    Bool ucCreated = FALSE;

    chainsObj.chainsCfg = chainsCfg;
    chainsObj.displayActiveChId = 0U;

    socId = Bsp_platformGetSocId();
    if ((BSP_PLATFORM_SOC_ID_TDA3XX != socId) &&
        (BSP_PLATFORM_SOC_ID_TDA2EX != socId) &&
        (BSP_PLATFORM_SOC_ID_TDA2PX != socId))
    {
        Vps_printf("\n CSI2 Based usecases not supported on this SoC \n");
        done = TRUE;
    }

    chainsObj.numLanesOnPhy1Csi2 = 0U;
    if (FALSE == chainsCfg->byPassSensorCfg)
    {
        if (((CHAINS_CAPTURE_SRC_UB964_OV1063X != chainsCfg->captureSrc) ||
             (4U != chainsCfg->numLvdsCh)) ||
            (CHAINS_DISPLAY_TYPE_HDMI_1080P != chainsCfg->displayType))
        {
            Vps_printf("\n Camera Selected or Number of LVDS Channels or Display is "
                        " not 1080P60, Please try again \n");
            done = TRUE;
        }

        if (BSPUTILS_UB964_VERSION_ID != BspUtils_appGetUb96xVersion(0U))
        {
            Vps_printf("\n Requires an UB964!!! Cannot stream out YUV422I (8 bit)");
            done = TRUE;
        }
    }
    else
    {
        if (BSP_PLATFORM_SOC_ID_TDA2EX == socId)
        {
            chainsCfg->numLvdsCh = 8U;
            chainsObj.numLanesOnPhy1Csi2 = 2U;
        }
    }

    if (FALSE == done)
    {
        /*  On TDA2EX
            4 Channels of 1.2 MP video could be received on 2 lanes, following
            changes would be required
            1. Set numLanesOnPhy0Csi2 to 2
            2. Set UB960 to stream on 2 lanes

            On J6 Entry
            There are only 2 lanes available, set numLanesOnPhy0Csi2 to 2
            UB960 is configured for 2 lanes for J6 E
         */
        chainsObj.numLanesOnPhy0Csi2 = 4U;
        if (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType())
        {
            chainsObj.numLanesOnPhy0Csi2 = 2U;
        }

        /* Set Display Width & Height, capture width & height
            Call Sensor program */
        ChainsCommon_GetDisplayWidthHeight(
                chainsObj.chainsCfg->displayType,
                &chainsObj.displayWidth,
                &chainsObj.displayHeight);

        chainsObj.captureOutWidth   = CAPTURE_SENSOR_WIDTH;
        chainsObj.captureOutHeight  = CAPTURE_SENSOR_HEIGHT;
        chainsObj.numCsi2Ch         = chainsCfg->numLvdsCh;

        chains_csi2CalMultiCam_Create(&chainsObj.ucObj, &chainsObj);
        /* Function chains_csi2CalMultiCam_SetAppPrms would be called by
            above create function */
        chains_csi2CalMultiCam_StartApp(&chainsObj);

        ucCreated = TRUE;
    }

    while(!done)
    {
        ch = Chains_menuRunTime();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                switchDisplayChannel(&chainsObj);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_csi2CalMultiCam_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    if(TRUE == ucCreated)
    {
        chains_csi2CalMultiCam_StopAndDeleteApp(&chainsObj);
    }

    return;
}
