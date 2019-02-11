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
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <src/rtos/utils_common/include/utils_temperature.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <src/include/link_stats_monitor.h>

Chains_CommonObj gChains_commonObj;

/**
 *******************************************************************************
 *
 * \brief   Return W x H of a given display type
 *
 *******************************************************************************
*/
Void ChainsCommon_GetDisplayWidthHeight(
        Chains_DisplayType displayType,
        UInt32 *displayWidth,
        UInt32 *displayHeight
        )
{
    switch(displayType)
    {
        case CHAINS_DISPLAY_TYPE_LCD_7_INCH:
            *displayWidth = 800;
            *displayHeight = 480;
            break;
        case CHAINS_DISPLAY_TYPE_LCD_10_INCH:
            *displayWidth = 1280;
            *displayHeight = 800;
            break;
        case CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200:
            *displayWidth = 1920;
            *displayHeight = 1200;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_720P:
            *displayWidth = 1280;
            *displayHeight = 720;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_1080P:
            *displayWidth = 1920;
            *displayHeight = 1080;
            break;
        case CHAINS_DISPLAY_TYPE_SDTV_NTSC:
            *displayWidth = 720;
            *displayHeight = 480;
            break;
        case CHAINS_DISPLAY_TYPE_SDTV_PAL:
            *displayWidth = 720;
            *displayHeight = 576;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM:
            *displayWidth = 1024;
            *displayHeight = 768;
            break;
        case CHAINS_DISPLAY_TYPE_HDMI_WXGA:
            *displayWidth = 1280;
            *displayHeight = 800;
            break;
        default:
            UTILS_assert(0);
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Controller Create Parameters
 *
 * \param   pPrm         [IN]    DisplayCtrlLink_ConfigParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetDctrlConfig(
                                DisplayCtrlLink_ConfigParams *pPrm,
                                DisplayCtrlLink_OvlyParams *ovlyPrms,
                                DisplayCtrlLink_OvlyPipeParams *pipeOvlyPrms,
                                UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                )
{
    DisplayCtrlLink_VencInfo *pVInfo;

    pPrm->numVencs = 1;
    pPrm->tiedVencs = 0;

    pVInfo = &pPrm->vencInfo[0];

    pVInfo->tdmMode = DISPLAYCTRL_LINK_TDM_DISABLE;
    if(displayType == CHAINS_DISPLAY_TYPE_LCD_7_INCH)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
        }
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
        pVInfo->mInfo.pixelClock                =   29232u;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hFrontPorch               =   40u;
        pVInfo->mInfo.hBackPorch                =   40u;
        pVInfo->mInfo.hSyncLen                  =   48u;
        pVInfo->mInfo.vFrontPorch               =   13u;
        pVInfo->mInfo.vBackPorch                =   29u;
        pVInfo->mInfo.vSyncLen                  =   3u;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            pVInfo->vencDivisorInfo.divisorPCD      =   1;
        }
        else
        {
            pVInfo->vencDivisorInfo.divisorPCD      =   4;
        }

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                       = SYSTEM_DCTRL_DSS_VENC_LCD1;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            ovlyPrms->vencId                    = SYSTEM_DCTRL_DSS_VENC_LCD3;
        }
    }
    if(displayType == CHAINS_DISPLAY_TYPE_LCD_10_INCH)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
        }
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hFrontPorch               =   48U;
        pVInfo->mInfo.vBackPorch                =   12U;
        pVInfo->mInfo.vFrontPorch               =   6U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;

#ifdef ROBUST_RVC_INCLUDE
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* TDA2EX - 17x17 - J6Entry - AUO diplay */
            pVInfo->mInfo.pixelClock                =   69300U;
            pVInfo->mInfo.hSyncLen                  =   32U;
            pVInfo->mInfo.hBackPorch                =   48U;
            pVInfo->mInfo.vFrontPorch               =   4U;
            pVInfo->mInfo.vSyncLen                  =   4U;
            pVInfo->mInfo.vBackPorch                =   8U;
            pVInfo->vencDivisorInfo.divisorPCD      =   3;
        }
        else {
            pVInfo->mInfo.pixelClock                =   69300U;
            pVInfo->mInfo.hSyncLen                  =   32U;
            pVInfo->mInfo.hBackPorch                =   44U;
            pVInfo->mInfo.vFrontPorch               =   4U;
            pVInfo->mInfo.vSyncLen                  =   12U;
            pVInfo->mInfo.vBackPorch                =   7U;
            pVInfo->vencDivisorInfo.divisorPCD      =   3;
        }
#else
        pVInfo->mInfo.pixelClock                =   74500U;
        pVInfo->mInfo.hBackPorch                =   80U;
        pVInfo->mInfo.hSyncLen                  =   62U;
        pVInfo->mInfo.vSyncLen                  =   35U;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
#endif

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */
        ovlyPrms->vencId                        = SYSTEM_DCTRL_DSS_VENC_LCD1;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            ovlyPrms->vencId                    = SYSTEM_DCTRL_DSS_VENC_LCD3;
        }
    }
    else if (displayType ==
        CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200)
    {
        pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
        }
        pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_LOW;

        /* Below are of dont care for EVM LCD */
        pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
        pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

        pVInfo->mInfo.standard                  =   SYSTEM_STD_CUSTOM;
        pVInfo->mInfo.width                     =   displayWidth;
        pVInfo->mInfo.height                    =   displayHeight;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_PROGRESSIVE;
    #ifdef TDA3XX_FAMILY_BUILD
        pVInfo->mInfo.pixelClock                =   147000U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   32U;
        pVInfo->mInfo.hSyncLen                  =   16U;
        pVInfo->mInfo.hFrontPorch               =   32U;
        pVInfo->mInfo.vBackPorch                =   16U;
        pVInfo->mInfo.vSyncLen                  =   2U;
        pVInfo->mInfo.vFrontPorch               =   7U;
    #else
        pVInfo->mInfo.pixelClock                =   78000U;
        pVInfo->mInfo.fps                       =   32U;
        pVInfo->mInfo.hBackPorch                =   32U;
        pVInfo->mInfo.hSyncLen                  =   16U;
        pVInfo->mInfo.hFrontPorch               =   112U;
        pVInfo->mInfo.vBackPorch                =   16U;
        pVInfo->mInfo.vSyncLen                  =   2U;
        pVInfo->mInfo.vFrontPorch               =   17U;
    #endif
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;

        pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
        pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
        pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

        pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
        pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

        /* Configure overlay params */

        ovlyPrms->vencId                       = SYSTEM_DCTRL_DSS_VENC_LCD1;
        if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
            (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
        {
            /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
            ovlyPrms->vencId                    = SYSTEM_DCTRL_DSS_VENC_LCD3;
        }
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P
            || displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P
            || displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA)
    {
        if(Bsp_platformIsTda2xxFamilyBuild())
        {
            pPrm->deviceId = DISPLAYCTRL_LINK_USE_HDMI;
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_HDMI;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_HDMI_OUTPUT;
            pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            /* Below are of dont care for EVM LCD */
            pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
            pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
            pVInfo->vencOutputInfo.dvoFormat        =
                                        SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
            pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

            pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

            /* Configure overlay params */

            ovlyPrms->vencId                        = SYSTEM_DCTRL_DSS_VENC_HDMI;
        }
        else if(Bsp_platformIsTda3xxFamilyBuild())
        {
            pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
            pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            /* Below are of dont care for EVM LCD */
            pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
            pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
            pVInfo->vencOutputInfo.dvoFormat        =
                                        SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
            pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

            pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

            pVInfo->vencDivisorInfo.divisorLCD      =   1;
            pVInfo->vencDivisorInfo.divisorPCD      =   1;

            /* Configure overlay params */

            ovlyPrms->vencId                        = SYSTEM_DCTRL_DSS_VENC_LCD1;
        }
    }
    else if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
            (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
    {
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_SDTV;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;

            pVInfo->vencOutputInfo.vsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.hsPolarity    =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            /* Below are of dont care for EVM LCD */
            pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            pVInfo->vencDivisorInfo.divisorLCD      =   1;
            pVInfo->vencDivisorInfo.divisorPCD      =   1;

            pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
            pVInfo->vencOutputInfo.dvoFormat        =
                                    SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
            pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

            pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

            ovlyPrms->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
        }
        else
        {
            UTILS_assert(0);
        }
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM)
    {
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            pPrm->deviceId = DISPLAYCTRL_LINK_USE_LCD;
            pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD1;
            pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;
            pVInfo->vencOutputInfo.vsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.hsPolarity       =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            /* Below are of dont care for EVM LCD */
            pVInfo->vencOutputInfo.fidPolarity      =   SYSTEM_DCTRL_POLARITY_ACT_LOW;
            pVInfo->vencOutputInfo.actVidPolarity   =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;

            pVInfo->vencOutputInfo.dataFormat       =   SYSTEM_DF_RGB24_888;
            pVInfo->vencOutputInfo.dvoFormat        =
                                        SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
            pVInfo->vencOutputInfo.videoIfWidth     =   SYSTEM_VIFW_24BIT;

            pVInfo->vencOutputInfo.pixelClkPolarity =   SYSTEM_DCTRL_POLARITY_ACT_HIGH;
            pVInfo->vencOutputInfo.aFmt             =   SYSTEM_DCTRL_A_OUTPUT_MAX;

            pVInfo->vencDivisorInfo.divisorLCD      =   1;
            pVInfo->vencDivisorInfo.divisorPCD      =   1;

            /* Configure overlay params */

            ovlyPrms->vencId                        = SYSTEM_DCTRL_DSS_VENC_LCD1;

            pVInfo->tdmMode = DISPLAYCTRL_LINK_TDM_24BIT_TO_8BIT;
        }
        else
        {
            UTILS_assert(0);
        }
    }

    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_720P_60;

    }
    else if (displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_1080P_60;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_NTSC;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_INTERLACED;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_PAL;
        pVInfo->mInfo.scanFormat                =   SYSTEM_SF_INTERLACED;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_XGA_DSS_TDM_60;
    }
    else if(displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA)
    {
        pVInfo->mInfo.standard                  =   SYSTEM_STD_WXGA_60;
    }

    /* TODO Dont know what to set here */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0] =
                    TRUE;
    pVInfo->isInputPipeConnected[1] =
                    TRUE;
    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        pVInfo->isInputPipeConnected[2] =
                    TRUE;
    }
    else
    {
        pVInfo->isInputPipeConnected[2] =
                    FALSE;
    }
    pVInfo->isInputPipeConnected[3] =
                    TRUE;
    pVInfo->writeBackEnabledFlag = FALSE;


    /* Setting other overlay parameters common to both Venc */

    ovlyPrms->deltaLinesPerPanel   = 0;
    ovlyPrms->alphaBlenderEnable   = 0;
    ovlyPrms->backGroundColor      = 0x0;
    ovlyPrms->colorKeyEnable       = 1;
    ovlyPrms->colorKeySel          = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
#ifdef ROBUST_RVC_INCLUDE
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_OPTIMIZED;
#else
    ovlyPrms->ovlyOptimization     = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
#endif
    ovlyPrms->transColorKey        = DRAW2D_TRANSPARENT_COLOR;

    /* Setting overlay pipe parameters */

    pipeOvlyPrms[0].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID1;
    pipeOvlyPrms[0].globalAlpha = 0xFF;
    pipeOvlyPrms[0].preMultiplyAlpha = 0;
    pipeOvlyPrms[0].zorderEnable = TRUE;
    pipeOvlyPrms[0].zorder = SYSTEM_DSS_DISPC_ZORDER0;

    pipeOvlyPrms[1].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID2;
    pipeOvlyPrms[1].globalAlpha = 0xFF;
    pipeOvlyPrms[1].preMultiplyAlpha = 0;
    pipeOvlyPrms[1].zorderEnable = TRUE;
    pipeOvlyPrms[1].zorder = SYSTEM_DSS_DISPC_ZORDER1;

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        pipeOvlyPrms[2].pipeLine = SYSTEM_DSS_DISPC_PIPE_VID3;
        pipeOvlyPrms[2].globalAlpha = 0xFF;
        pipeOvlyPrms[2].preMultiplyAlpha = 0;
        pipeOvlyPrms[2].zorderEnable = TRUE;
        pipeOvlyPrms[2].zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }

    pipeOvlyPrms[3].pipeLine = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pipeOvlyPrms[3].globalAlpha = 0xFF;
    pipeOvlyPrms[3].preMultiplyAlpha = 0;
    pipeOvlyPrms[3].zorderEnable = TRUE;
    pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER3;
    if(Bsp_platformIsTda3xxFamilyBuild())
    {
        pipeOvlyPrms[3].zorder = SYSTEM_DSS_DISPC_ZORDER2;
    }

}


/**
 *******************************************************************************
 *
 * \brief   Set LCD Create Parameters
 *
 *          It is called in Create function.
 *          Lcd parameters like the device id and brightnessvalue are set here.
 *
 * \param   pPrm    [IN]    Lcd_CreateParams
 *
 *******************************************************************************
*/
static Void ChainsCommon_SetLcdPrms(Lcd_CreateParams *pPrm)
{
    pPrm->drvId = LCD_CNTR_DRV;
    pPrm->brightnessValue = 100;
}


/**
 *******************************************************************************
 *
 * \brief   Setups Display Controller to dual display on On-chip HDMI and
 *          LCD
 *
 *          Configure such that VID2 and VID3 pipe goto LCD
 *          And VID1 and GRPX pipe goes to HDMI
 *
 *          HDMI is hardcoded to 1080p60 resolution
 *          LCD is hardcoded to 800x480 resolution
 *
 *          NOTE, this is just a sample config use by example use-cases
 *          User's can configure it different in their use-case
 *
 *******************************************************************************
*/
Int32 ChainsCommon_DualDisplay_StartDisplayCtrl(
Chains_DisplayType lcdType, UInt32 displayLCDWidth, UInt32 displayLCDHeight)
{
    Int32 status;
    DisplayCtrlLink_ConfigParams *pPrm = &gChains_commonObj.dctrlCfgPrms;
    DisplayCtrlLink_VencInfo *pVInfo;
    DisplayCtrlLink_OvlyParams *pOvlyPrms;
    DisplayCtrlLink_OvlyPipeParams *pPipeOvlyPrms;
    DisplayCtrlLink_OvlyParams ovlyPrms[2];

    /* Set the link id */
    gChains_commonObj.displayCtrlLinkId = SYSTEM_LINK_ID_DISPLAYCTRL;

    /* Number of valid entries in vencInfo array */
    pPrm->numVencs = 2;
    /* Bitmask of tied vencs. Two vencs, which uses same pixel clock and whose vsync are synchronized, can be tied together. */
    pPrm->tiedVencs = 0;
    /* Activate the HDMI BSP layer in the Dctrl link. This is not required if there is no HDMI display in use. */
    pPrm->deviceId = DISPLAYCTRL_LINK_USE_HDMI;

    /* Configure HDMI display */
    pVInfo                                  = &pPrm->vencInfo[0];
    pVInfo->vencId                          = SYSTEM_DCTRL_DSS_VENC_HDMI;
    pVInfo->outputPort                      = SYSTEM_DCTRL_DSS_HDMI_OUTPUT;
    pVInfo->vencOutputInfo.vsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.hsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    /* Below are of dont care for EVM LCD */
    pVInfo->vencOutputInfo.fidPolarity      = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.actVidPolarity   = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    /* We use 1080p60 - set to SYSTEM_STD_720P_60 for 720p! */
    pVInfo->mInfo.standard                  = SYSTEM_STD_1080P_60;

    /* Configure HDMI overlay parameters */
    pVInfo->mode                            = 0;
    pVInfo->isInputPipeConnected[0]         = TRUE;
    pVInfo->isInputPipeConnected[1]         = FALSE;
    pVInfo->isInputPipeConnected[2]         = FALSE;
    pVInfo->isInputPipeConnected[3]         = TRUE;
    pVInfo->writeBackEnabledFlag            = FALSE;

    pVInfo->vencOutputInfo.dataFormat       = SYSTEM_DF_RGB24_888;
    pVInfo->vencOutputInfo.dvoFormat        = SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    pVInfo->vencOutputInfo.videoIfWidth     = SYSTEM_VIFW_24BIT;

    pVInfo->vencOutputInfo.pixelClkPolarity = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.aFmt             = SYSTEM_DCTRL_A_OUTPUT_MAX;

    pOvlyPrms                               = &ovlyPrms[0];
    pOvlyPrms->vencId                       = pVInfo->vencId;
    pOvlyPrms->deltaLinesPerPanel           = 0;
    pOvlyPrms->alphaBlenderEnable           = 0;
    pOvlyPrms->backGroundColor              = 0x0;
    pOvlyPrms->colorKeyEnable               = 1;
    pOvlyPrms->colorKeySel                  = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    pOvlyPrms->ovlyOptimization             = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
    pOvlyPrms->transColorKey                = DRAW2D_TRANSPARENT_COLOR;

    /* Configure LCD */
    pVInfo                                  = &pPrm->vencInfo[1];
    pVInfo->vencId                          = SYSTEM_DCTRL_DSS_VENC_LCD1;
    pVInfo->outputPort                      = SYSTEM_DCTRL_DSS_DPI1_OUTPUT;

    if ((BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()) &&
        (BSP_PLATFORM_PACKAGE_TYPE_17x17 == Bsp_platformGetPackageType()))
    {
        /* In case of TDA2EX and Package is 17 X 17, LCD is on DPI 3 */
        pVInfo->vencId = SYSTEM_DCTRL_DSS_VENC_LCD3;
        pVInfo->outputPort = SYSTEM_DCTRL_DSS_DPI3_OUTPUT;
    }

    pVInfo->vencOutputInfo.vsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.hsPolarity       = SYSTEM_DCTRL_POLARITY_ACT_LOW;

    /* Below are of dont care for EVM LCD */
    pVInfo->vencOutputInfo.fidPolarity      = SYSTEM_DCTRL_POLARITY_ACT_HIGH;
    pVInfo->vencOutputInfo.actVidPolarity   = SYSTEM_DCTRL_POLARITY_ACT_HIGH;

    pVInfo->mInfo.standard                  = SYSTEM_STD_CUSTOM;
    pVInfo->mInfo.scanFormat                = SYSTEM_SF_PROGRESSIVE;
    pVInfo->mInfo.width                     = displayLCDWidth;
    pVInfo->mInfo.height                    = displayLCDHeight;

    if(lcdType == CHAINS_DISPLAY_TYPE_LCD_7_INCH)
    {
    pVInfo->mInfo.pixelClock                = 29232u;
    pVInfo->mInfo.fps                       =   60U;
    pVInfo->mInfo.hFrontPorch               = 40u;
    pVInfo->mInfo.hBackPorch                = 40u;
    pVInfo->mInfo.hSyncLen                  = 48u;
    pVInfo->mInfo.vFrontPorch               = 13u;
    pVInfo->mInfo.vBackPorch                = 29u;
    pVInfo->mInfo.vSyncLen                  = 3u;
    pVInfo->vencDivisorInfo.divisorLCD      = 1;
    pVInfo->vencDivisorInfo.divisorPCD      = 4;
    }
    else if(lcdType == CHAINS_DISPLAY_TYPE_LCD_10_INCH)
    {
        pVInfo->mInfo.pixelClock                =   74500U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   80U;
        pVInfo->mInfo.hSyncLen                  =   62U;
        pVInfo->mInfo.hFrontPorch               =   48U;
        pVInfo->mInfo.vBackPorch                =   12U;
        pVInfo->mInfo.vSyncLen                  =   35U;
        pVInfo->mInfo.vFrontPorch               =   6U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
    }
    else if (lcdType ==
    CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200)
    {
        pVInfo->mInfo.pixelClock                =   147000U;
        pVInfo->mInfo.fps                       =   60U;
        pVInfo->mInfo.hBackPorch                =   30U;
        pVInfo->mInfo.hSyncLen                  =   16U;
        pVInfo->mInfo.hFrontPorch               =   32U;
        pVInfo->mInfo.vBackPorch                =   16U;
        pVInfo->mInfo.vSyncLen                  =   2U;
        pVInfo->mInfo.vFrontPorch               =   7U;
        pVInfo->vencDivisorInfo.divisorLCD      =   1;
        pVInfo->vencDivisorInfo.divisorPCD      =   1;
    }
    else
        UTILS_assert(NULL);

    /* Configure LCD overlay params */
    pVInfo->mode = 0;
    pVInfo->isInputPipeConnected[0]         = FALSE;
    pVInfo->isInputPipeConnected[1]         = TRUE;
    pVInfo->isInputPipeConnected[2]         = TRUE;
    pVInfo->isInputPipeConnected[3]         = FALSE;
    pVInfo->writeBackEnabledFlag            = FALSE;

    pVInfo->vencOutputInfo.dataFormat       = SYSTEM_DF_RGB24_888;
    pVInfo->vencOutputInfo.dvoFormat        = SYSTEM_DCTRL_DVOFMT_GENERIC_DISCSYNC;
    pVInfo->vencOutputInfo.videoIfWidth     = SYSTEM_VIFW_24BIT;

    pVInfo->vencOutputInfo.pixelClkPolarity = SYSTEM_DCTRL_POLARITY_ACT_LOW;
    pVInfo->vencOutputInfo.aFmt             = SYSTEM_DCTRL_A_OUTPUT_MAX;

    pOvlyPrms                               = &ovlyPrms[1];
    pOvlyPrms->vencId                       = pVInfo->vencId;
    pOvlyPrms->deltaLinesPerPanel           = 0;
    pOvlyPrms->alphaBlenderEnable           = 0;
    pOvlyPrms->backGroundColor              = 0x0;
    pOvlyPrms->colorKeyEnable               = 1;
    pOvlyPrms->colorKeySel                  = SYSTEM_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    pOvlyPrms->ovlyOptimization             = SYSTEM_DSS_DISPC_OVLY_FETCH_ALLDATA;
    pOvlyPrms->transColorKey                = DRAW2D_TRANSPARENT_COLOR;

    /* Setting HDMI overlay pipe parameters */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[0];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID1;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER0;

    /* Setting LCD overlay pipe parameters */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[1];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID2;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER0;

    /* Setting PIP overlay pipe parameters on LCD */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[2];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_VID3;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER2;

    /* Configure graphics overlay for HDMI */
    pPipeOvlyPrms                           = &gChains_commonObj.pipeParams[3];
    pPipeOvlyPrms->pipeLine                 = SYSTEM_DSS_DISPC_PIPE_GFX1;
    pPipeOvlyPrms->globalAlpha              = 0xFF;
    pPipeOvlyPrms->preMultiplyAlpha         = 0;
    pPipeOvlyPrms->zorderEnable             = TRUE;
    pPipeOvlyPrms->zorder                   = SYSTEM_DSS_DISPC_ZORDER3;

/* Create, configure and start the Display Ctrl link */
    status = System_linkCreate(gChains_commonObj.displayCtrlLinkId,
                                NULL,
                                0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &ovlyPrms[0],
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &ovlyPrms[1],
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[2],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Set display link parameters in the case of single video pipe
 *          and one graphics pipe
 *
 *******************************************************************************
*/
Void ChainsCommon_SetGrpxSrcPrms(
                                GrpxSrcLink_CreateParams *pPrm,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                )
{
    pPrm->grpxBufInfo.dataFormat  = SYSTEM_DF_BGR16_565;
    pPrm->grpxBufInfo.height   = displayHeight;
    pPrm->grpxBufInfo.width    = displayWidth;

    pPrm->logoDisplayEnable = TRUE;
    pPrm->logoParams.startX = 40;
    pPrm->logoParams.startY = 40;

    pPrm->statsDisplayEnable = TRUE;

    pPrm->statsPrintParams.startX = pPrm->logoParams.startX;
    pPrm->statsPrintParams.startY = displayHeight - 134 - pPrm->logoParams.startY;
}

/**
 *******************************************************************************
 *
 * \brief   Set display link parameters in the case of single video pipe
 *          and one graphics pipe
 *
 *******************************************************************************
*/
Void ChainsCommon_SetDisplayPrms(
                                DisplayLink_CreateParams *pPrm_Video,
                                DisplayLink_CreateParams *pPrm_Grpx,
                                Chains_DisplayType displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight
                                )
{
    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Video->rtParams.tarWidth         = displayWidth;
        pPrm_Video->rtParams.tarHeight        = displayHeight;
        pPrm_Video->displayId                 = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_Grpx)
    {
        pPrm_Grpx->displayId                  = DISPLAY_LINK_INST_DSS_GFX1;

        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

    }
}


/**
 *******************************************************************************
 *
 * \brief   Configure and start display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartDisplayCtrl(UInt32 displayType,
                                UInt32 displayWidth,
                                UInt32 displayHeight
)
{
    Int32 status=0;

    gChains_commonObj.displayCtrlLinkId = SYSTEM_LINK_ID_DISPLAYCTRL;

    ChainsCommon_SetDctrlConfig(
        &gChains_commonObj.dctrlCfgPrms,
        &gChains_commonObj.ovlyParams,
        &gChains_commonObj.pipeParams[0],
        displayType,
        displayWidth,
        displayHeight
        );

    /* There are no createtime Params for display controller */
    status = System_linkCreate(gChains_commonObj.displayCtrlLinkId,
                                NULL,
                                0);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS,
                                &gChains_commonObj.ovlyParams,
                                sizeof(DisplayCtrlLink_OvlyParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[0],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[1],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if(Bsp_platformIsTda2xxFamilyBuild())
    {
        status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[2],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS,
                                &gChains_commonObj.pipeParams[3],
                                sizeof(DisplayCtrlLink_OvlyPipeParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Stop and Delete display controller
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopDisplayCtrl()
{
    Int32 status=0;

    status = System_linkControl(gChains_commonObj.displayCtrlLinkId,
                                DISPLAYCTRL_LINK_CMD_CLR_CONFIG,
                                &gChains_commonObj.dctrlCfgPrms,
                                sizeof(DisplayCtrlLink_ConfigParams),
                                TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_linkDelete(gChains_commonObj.displayCtrlLinkId);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Start Display device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartDisplayDevice(UInt32 displayType)
{
    Int32 status=0;

    if (displayType == CHAINS_DISPLAY_TYPE_LCD_7_INCH
        ||
        displayType == CHAINS_DISPLAY_TYPE_LCD_10_INCH
        ||
        displayType == CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200
    )
    {
        ChainsCommon_SetLcdPrms(&gChains_commonObj.lcdPrm);

        gChains_commonObj.lcdInstId = gChains_commonObj.lcdPrm.drvId;

        status = Lcd_turnOn(gChains_commonObj.lcdInstId, &gChains_commonObj.lcdPrm);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA
        )
    {
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            HdmiTx_CreateStatus hdmiTxStatus;

            HdmiTx_CreateParams_Init(&gChains_commonObj.hdmiTxPrm);

            if(displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P)
            {
                gChains_commonObj.hdmiTxPrm.standard = SYSTEM_STD_1080P_60;
            }
            if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P)
            {
                gChains_commonObj.hdmiTxPrm.standard = SYSTEM_STD_720P_60;
            }
            if(displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA)
            {
                gChains_commonObj.hdmiTxPrm.standard = SYSTEM_STD_WXGA_60;
            }
            if(displayType == CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM)
            {
                gChains_commonObj.hdmiTxPrm.standard = SYSTEM_STD_XGA_DSS_TDM_60;
                gChains_commonObj.hdmiTxPrm.boardMode = BSP_BOARD_MODE_VIDEO_8BIT_TDM;
            }

            status = HdmiTx_create(&gChains_commonObj.hdmiTxPrm, &hdmiTxStatus);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            status = HdmiTx_control(&gChains_commonObj.hdmiTxPrm,
                                    HDMI_TX_CMD_START,
                                    NULL,
                                    NULL);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Start Display device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopDisplayDevice(UInt32 displayType)
{
    Int32 status=0;

    if (displayType == CHAINS_DISPLAY_TYPE_LCD_7_INCH
        ||
        displayType == CHAINS_DISPLAY_TYPE_LCD_10_INCH
        ||
        displayType == CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200
        )
    {
        Lcd_turnOff(gChains_commonObj.lcdInstId);
    }
    if(displayType == CHAINS_DISPLAY_TYPE_HDMI_720P
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_1080P
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM
        ||
      displayType == CHAINS_DISPLAY_TYPE_HDMI_WXGA
        )
    {
        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            status = HdmiTx_control(&gChains_commonObj.hdmiTxPrm,
                                    HDMI_TX_CMD_STOP,
                                    NULL,
                                    NULL);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            status = HdmiTx_delete(&gChains_commonObj.hdmiTxPrm,
                                    NULL);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Set L3/DMM priority related registers
 *
 *******************************************************************************
*/
Void ChainsCommon_SetSystemL3DmmPri()
{
    /* enable usage of Mflag at DMM */
    Utils_setDmmMflagEmergencyEnable(TRUE);

    /* Set DMM as higest priority at DMM and EMIF */
    Utils_setDmmPri(UTILS_DMM_INITIATOR_ID_DSS, 0);
}

/**
 *******************************************************************************
 *
 * \brief   Print Statistics
 *
 *******************************************************************************
*/
Void ChainsCommon_PrintStatistics()
{
    System_linkControl(
        SYSTEM_LINK_ID_IPU1_0,
        SYSTEM_LINK_CMD_PRINT_CORE_PRF_LOAD,
        NULL,
        0,
        TRUE);

    Utils_prcmPrintAllVDTempValues();
    Utils_prcmPrintPowerConsumption();
    Chains_statCollectorPrint();
    System_printDisplayErrorStats();
}

/**
 *******************************************************************************
 *
 * \brief   Load Calculation enable/disable
 *
 *          This functions enables load profiling. A control command
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START is passed to chianed links.
 *          If parameter Enable is set true Load profiling is enabled.
 *          If printStatus is set true a System CMD to Print CPU load,
 *          Task Laod and Heap status information is sent
 *          While creating enable = TRUE , printStatus & printTskLoad = FALSE
 *          While deleting enable = FALSE , printStatus & printTskLoad = TRUE
 *
 * \param   enable               [IN]   is set true Load profiling
 *
 * \param   printStatus          [IN] true a System CMD
 *
 * \param   printTskLoad         [IN]  true a Print CPU load
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad)
{
    UInt32 procId, linkId;


    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        if(enable)
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START,
                NULL,
                0,
                TRUE
            );
        }
        else
        {
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP,
                NULL,
                0,
                TRUE
            );
            if(printStatus)
            {
                SystemCommon_PrintStatus printStatus;

                memset(&printStatus, 0, sizeof(printStatus));

                printStatus.printCpuLoad = TRUE;
                printStatus.printTskLoad = printTskLoad;
                System_linkControl(
                    linkId,
                    SYSTEM_COMMON_CMD_PRINT_STATUS,
                    &printStatus,
                    sizeof(printStatus),
                    TRUE
                );
                Task_sleep(100);
            }
            System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET,
                NULL,
                0,
                TRUE
            );
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Load Calculation.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfCpuLoadPrint()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printCpuLoad = TRUE;
    printStatus.printTskLoad = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STATUS,
            &printStatus,
            sizeof(printStatus),
            TRUE
        );
        Task_sleep(100);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   Print Memory Heap Statistics
 *
 *          This function send a system control message
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_memPrintHeapStatus()
{
    UInt32 procId, linkId;
    SystemCommon_PrintStatus printStatus;

    memset(&printStatus, 0, sizeof(printStatus));

    printStatus.printHeapStatus = TRUE;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
                linkId,
                SYSTEM_COMMON_CMD_PRINT_STATUS,
                &printStatus,
                sizeof(printStatus),
                TRUE
            );
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Print the statCollector output
 *          SYSTEM_COMMON_CMD_PRINT_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_statCollectorPrint()
{
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_PRINT_STAT_COLL,
            NULL,
            0,
            TRUE
        );
        Task_sleep(100);


    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_statCollectorReset()
{
    UInt32 linkId;

    linkId = IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_RESET_STAT_COLL,
            NULL,
            0,
            TRUE
        );

    return SYSTEM_LINK_STATUS_SOK;
}

