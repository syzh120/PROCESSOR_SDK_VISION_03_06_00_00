/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <app_dctrlConfigure.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/csl/soc.h>

extern int32_t gTestStatus;

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk);

/**
 * Open Dctrl Handle
 */
VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;

    pObj = VpsDrv_dctrlOpen();

    return pObj;
}

Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj)
{
    return VpsDrv_dctrlClose(pObj);
}

Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DctrlConfig             dctrlCfg;
    Vps_DssDispcOvlyPanelConfig panelCfg;
    Vps_DctrlVencDivisorInfo    vencDivisors;
    Int32  retVal, idx = 0;
    UInt32 pixelClock;
    UInt32 blenderNode, dpiOutputNode, vencId;

    blenderNode     = VPS_DCTRL_DSS_LCD1_BLENDER;
    dpiOutputNode   = VPS_DCTRL_DSS_DPI1_OUTPUT;
    vencId          = VPS_DCTRL_DSS_VENC_LCD1;
#if defined (SOC_TDA2EX)
    if (CSL_getSocSiliconPackageType() == CSL_SOC_SILICON_PACKAGE_TYPE_17X17)
    {
        blenderNode     = VPS_DCTRL_DSS_LCD3_BLENDER;
        dpiOutputNode   = VPS_DCTRL_DSS_DPI3_OUTPUT;
        vencId          = VPS_DCTRL_DSS_VENC_LCD3;
    }

#endif
    dctrlCfg.useCase = VPS_DCTRL_USERSETTINGS;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID2_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (OMAP5X_BUILD)
    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID3_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;
#endif

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_GFX1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = blenderNode;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = blenderNode;
    dctrlCfg.edgeInfo[idx].endNode   = dpiOutputNode;
    idx++;

    dctrlCfg.numEdges = (UInt32) idx;

    dctrlCfg.vencInfo.numVencs = (UInt32) 1U;
    dctrlCfg.vencInfo.modeInfo[0U].vencId = vencId;

    /* Configure custom timings */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.standard = FVID2_STD_CUSTOM;

#if defined (SOC_TDA2XX) || defined (OMAP5X_BUILD)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 480;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(Three 7 LCD)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 29232U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 13U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 29U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 3U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif

#if defined (SOC_TDA3XX) || defined (SOC_TDA2EX)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 1280;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(10 Inch LG)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 74500U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 80U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 62U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 12U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 35U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 6U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif

#if defined (SOC_TDA2PX)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 1280U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 720U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per 720P
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 74250U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 72U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 216U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 80U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 3U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 22U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 5U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif
    retVal = vpsDrv_DctrlSetConfig(pObj, &dctrlCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Config Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    panelCfg.vencId = vencId;
    panelCfg.alphaBlenderEnable = (UInt32) 0;
    panelCfg.backGroundColor    = 0x101010;
    panelCfg.colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg.colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg.deltaLinesPerPanel = (UInt32) 0;
    panelCfg.transColorKey      = 0x00;

    vpsDrv_DctrlSetOvlyParams(pObj, &panelCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    /* Setting LCD and PCD values to 1 */
    vencDivisors.vencId     = vencId;
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (OMAP5X_BUILD)
    /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
     * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to
     * output 29.232 * 4 MHz and set PCD as 4. */
    if (29232U == dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock)
    {
        vencDivisors.divisorPCD = 4U;
    }
#endif
    vpsDrv_DctrlSetVencDivisor(pObj, &vencDivisors);
    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Venc Divisors Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

    pixelClock = dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock *
                 vencDivisors.divisorPCD;
    DispApp_configureVideoPllAndClkSrc(pixelClock);

    return retVal;
}

Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DssDispcOvlyPipeConfig ovlpipecfg;
    Int32 retVal = BSP_SOK;

    ovlpipecfg.pipeLine    = VPS_DSS_DISPC_PIPE_VID1;
    ovlpipecfg.globalAlpha = 0xFF;
    /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
    ovlpipecfg.zorder = VPS_DSS_DISPC_PIPE_VID1;

    ovlpipecfg.zorderEnable     = 1;
    ovlpipecfg.preMultiplyAlpha = 0;

    retVal = vpsDrv_DctrlSetPipelineParams(pObj, &ovlpipecfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config IOCTL Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }
    return retVal;
}

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk)
{
    Int32  retVal = BSP_EFAIL;
    pmhalPrcmNodeId_t videopllId;
    UInt32 timeDelay = 0xFFFFFFFFU;

#if defined (SOC_TDA3XX)
    videopllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
#else
    videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
#endif
    retVal = PMLIBVideopllSetFreq(videopllId, pixelClk,
                                  PMLIB_VIDEO_PLL_CALC_MAX_MN, timeDelay);
    if (retVal != FVID2_SOK)
    {
        Bsp_printf("Configuring Pll Failed!!!\r\n");
        gTestStatus = STW_EFAIL;
    }

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (FVID2_SOK == retVal)
    {
        pmlibVideoPllVenc_t vidPllVencId = PMLIB_VIDEOPLL_VENC_LCD1;
        pmlibVideoPllClkSrc_t vidPllClkSrc =
            PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1;
#if defined (SOC_TDA2EX)
        if (CSL_getSocSiliconPackageType() == CSL_SOC_SILICON_PACKAGE_TYPE_17X17)
        {
            vidPllVencId = PMLIB_VIDEOPLL_VENC_LCD3;
            vidPllClkSrc = PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT3;
        }
#endif
        retVal = PMLIBVideopllSetVencClkSrc(vidPllVencId, vidPllClkSrc);
    }
#endif

    return retVal;
}

