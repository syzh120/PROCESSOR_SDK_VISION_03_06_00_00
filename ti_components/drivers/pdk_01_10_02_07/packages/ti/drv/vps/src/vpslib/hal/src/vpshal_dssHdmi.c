/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *  \file vpshal_dssHdmi.c
 *
 *  \brief VPS Hdmi HAL file.
 *  This file implements the HAL APIs of the DSS DISPC Video pipelines.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dss.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dssHdmi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define FEAT_PARAM_HDMI_PCLK           (0U)
#define FEAT_PARAM_HDMIPLL_FINT        (1U)
#define FEAT_PARAM_HDMIPLL_REGM        (2U)
#define FEAT_PARAM_DCOFREQ_LOW         (3U)
#define FEAT_PARAM_DCOFREQ_HIGH        (4U)

/* ========================================================================== */
/*                       Function Declarations                             */
/* ========================================================================== */

static inline UInt16 DIV_ROUND_UP(UInt64 n, UInt16 d);
static Int32 halHdmiWpSetPllPwr(vpsHal_hdmiPllPwr pllPwr);
static Int32 halHdmiWpSetPhyPwr(vpsHal_hdmiPhyPwr status);
static Int32 halHdmiTimingsCompare(const VpsHal_DssHdmiTimingParam *inTiming,
                                   const VpsHal_DssHdmiTimingParam *stdTiming);
static Int32 halHdmiPllReset(void);
static Int32 halHdmiPllInit(const VpsHal_DssHdmiPllInfo *pllInfo);

static void halHdmiCoreVideoSamplerConfig(const VpsHal_DssHdmiParam *advHdmi);
static UInt32 halHdmiFindStdCode(const VpsHal_DssHdmiTimingParam *timing);
static void halHdmiCoreVideoPacketizerConfig(
    const VpsHal_DssHdmiParam *advParam);

static void halHdmiCoreVideoConfig(const VpsHal_DssHdmiTimingParam *timings,
                                   const VpsHal_DssHdmiOutputInfo  *outputInfo);
static void halHdmiCoreMaskInterrupts(void);

static void halHdmiCoreCscConfig(cscTable cscCoeff);

static void halHdmiCoreColorDepthConfig(const VpsHal_DssHdmiParam *advHdmi);

static void halHdmiCoreAuxInfoframeAviConfig(
    const vpsHal_hdmiCoreAviInfoframe *aviInfoFrame);

static UInt64 halHDMIGetParamMin(UInt32 index);
static UInt64 halHDMIGetParamMax(UInt32 index);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* GNU compiler does not allow initialization as {0U} for all the elements
 * Hence individual structure elements are initialized with seperate braces
 */
VpsHal_HdmiInfo     HdmiHalInfo = {{0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U},
                                   {0U,0U,0U,0U,VPSHAL_HDMI_PACKETMODERESERVEDVALUE},
                                   {0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U},
                                   {0U,0U,0U}};

static const HdVenc_StdModeInfo HdVencStdCeaModeInfo[] =
{
    {{640,  480,  0, 25200,  48,  96,  16, 33, 2,  10,
      VPSHAL_HDMI_HDMI}, 1},
    {{720,  480,  0, 27000,  16,  60,  62, 9,  30, 6,
      VPSHAL_HDMI_HDMI}, 2},
    {{1280, 720,  0, 74250,  110, 220, 40, 5,  20, 5,
      VPSHAL_HDMI_HDMI}, 4},
    {{1920, 540,  1, 74250,  88,  148, 44, 2,  15, 5,
      VPSHAL_HDMI_HDMI}, 5},
    {{1920, 1080, 0, 148500, 88,  148, 44, 4,  36, 5,
      VPSHAL_HDMI_HDMI}, 16},
    {{720,  576,  0, 27000,  12,  68,  64, 5,  39, 5,
      VPSHAL_HDMI_HDMI}, 17},
    {{1280, 720,  0, 74250,  440, 220, 40, 5,  20, 5,
      VPSHAL_HDMI_HDMI}, 19},
    {{1920, 1080, 0, 74250,  528, 148, 44, 4,  36, 5,
      VPSHAL_HDMI_HDMI}, 20},
};

static const HdVenc_StdModeInfo HdVencStdVesaModeInfo[] =
{
/* VESA From Here */
    {{640,  480,  0, 25175,  48, 96,  16,  31, 2,  11,
      VPSHAL_HDMI_DVI}, 4},
    {{1280, 1024, 0, 108000, 48, 248, 112, 1,  38, 3,
      VPSHAL_HDMI_DVI}, 0x23},
    {{1024, 768,  0, 65000,  24, 160, 136, 3,  29, 6,
      VPSHAL_HDMI_DVI}, 0x10},
    {{1920, 1080, 0, 148500, 80, 44,  148, 36, 5,  4,
      VPSHAL_HDMI_DVI}, 0x52},
    {{720,  480,  1, 27000,  19, 57,  62,  4,  15, 3,
      VPSHAL_HDMI_DVI}, 0x55}
};

const cscTable      cscHdmiTableDeepColor[4] = {
    /* HDMI_DEEP_COLOR_24BIT */
    {7036, 0, 0, 32,
     0, 7036, 0, 32,
     0, 0, 7036, 32},
    /* HDMI_DEEP_COLOR_30BIT */
    {7015, 0, 0, 128,
     0, 7015, 0, 128,
     0, 0, 7015, 128},
    /* HDMI_DEEP_COLOR_36BIT */
    {7010, 0, 0, 512,
     0, 7010, 0, 512,
     0, 0, 7010, 512},
    /* FULL RANGE */
    {8192, 0, 0, 0,
     0, 8192, 0, 0,
     0, 0, 8192, 0},
};

/* min, max values*/
static const UInt64 gminmaxVal[5][2] =
{
    {1,          186000000   },
    {500000,     2500000     },
    {20,         2046        },
    {750000000,  1500000000  },
    {1250000000, 2500000000UL}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline UInt16 DIV_ROUND_UP(UInt64 n, UInt16 d)
{
    return (UInt16) (((n + d) - 1U) / d);
}

static UInt64 halHDMIGetParamMin(UInt32 index)
{
    UInt64 retval = 0;

    if (index < 5U)
    {
        retval = gminmaxVal[index][0];
    }

    return (retval);
}

static UInt64 halHDMIGetParamMax(UInt32 index)
{
    UInt64 retval = 0;

    if (index < 5U)
    {
        retval = gminmaxVal[index][1];
    }

    return (retval);
}

void halHdmiWpVideoTimingConfig(const VpsHal_DssHdmiTimingParam *timing)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_TIMING_H);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_H_HSW, (timing->hSyncLen));
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_H_HFP, timing->hFrontPorch);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_H_HBP, timing->hBackPorch);
    HW_WR_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_TIMING_H, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_TIMING_V);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_V_VSW, (timing->vSyncLen));
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_V_VFP, timing->vFrontPorch);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_TIMING_V_VBP, timing->vBackPorch);
    HW_WR_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_TIMING_V, regVal);

    return;
}

void halHdmiWpVideoFormatConfig(const VpsHal_DssHdmiTimingParam *timing,
                                const VpsHal_DssHdmiParam       *param,
                                const VpsHal_DssHdmiOutputInfo  *outputInfo)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_CFG);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_CFG_PACKING_MODE, param->packingMode);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_CFG_HSYNC_POL, outputInfo->hsPolarity);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_CFG_VSYNC_POL, outputInfo->vsPolarity);
    HW_SET_FIELD32(
        regVal,
        HDMI_WP_VIDEO_CFG_PROGRESSIVE_INTERLACE,
        timing->scanFormat);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_CFG_MODE, param->deepColor + 1U);
    HW_WR_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_CFG, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_SIZE);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_SIZE_LPP, timing->height);
    HW_SET_FIELD32(regVal, HDMI_WP_VIDEO_SIZE_PPL, timing->width);
    HW_WR_REG32(SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_SIZE, regVal);

    return;
}

void vpshal_HdmiWpVideoStart(UInt32 start)
{
    HW_WR_FIELD32(
        SOC_HDMI_WP_BASE + HDMI_WP_VIDEO_CFG,
        HDMI_WP_VIDEO_CFG_ENABLE,
        start);

    return;
}

void vpshal_HdmiReset(void)
{
    HW_WR_FIELD32(
        SOC_HDMI_WP_BASE + HDMI_WP_SYSCONFIG,
        HDMI_WP_SYSCONFIG_SOFTRESET,
        1U);

    /* softreset - wait till SOFTRESET == 1 */
    while (HW_RD_FIELD32(
               SOC_HDMI_WP_BASE + HDMI_WP_SYSCONFIG,
               HDMI_WP_SYSCONFIG_SOFTRESET) != 0)
    {}

    HW_WR_FIELD32(SOC_HDMI_WP_BASE + HDMI_WP_CLK, HDMI_WP_CLK_SFR_DIV, 0x0AU);

    /* assumption is OCP CLK is 266MHz */
    HW_WR_FIELD32(
        SOC_HDMI_WP_BASE + HDMI_WP_CLK,
        HDMI_WP_CLK_SCP_PWR_DIV,
        0x04U);
    /* assumption is OCP CLK is 266MHz, max SCP clk is 66.5MHz */

    return;
}

void vpshal_HdmiComputePll(Int32 pixelClock, VpsHal_DssHdmiPllInfo *pllInfo)

{
    UInt64 clkin, refclk = 0U;
    Int32  phy_calc;
    UInt64 regn_max, regn_min, regm_min, regm_max;
    UInt64 fint_min, fint_max;
    UInt64 dco_low_min, dco_high_min;
    UInt64 dco_high_min_value;
    Bool   found = FALSE;
    UInt32 mf;
    UInt64 value3;
    Int32  value4;

    /* clkin is in (Mhz * 100) */
    clkin = 2000U;

    fint_min = halHDMIGetParamMin((UInt32) FEAT_PARAM_HDMIPLL_FINT) / 10000U;
    fint_max = halHDMIGetParamMax((UInt32) FEAT_PARAM_HDMIPLL_FINT) / 10000U;

    fint_min = halHDMIGetParamMin((UInt32) FEAT_PARAM_HDMIPLL_FINT) / 10000U;
    fint_max = halHDMIGetParamMax((UInt32) FEAT_PARAM_HDMIPLL_FINT) / 10000U;

    /* clkin limits */
    /* .62 MHz < CLKIN/REGN < 2.5MHz */
    regn_min = (clkin / fint_max) + 1U;
    regn_max = clkin / fint_min;

    /* Fractional limits on REGM */
    regm_min = halHDMIGetParamMin((UInt32) FEAT_PARAM_HDMIPLL_REGM);
    regm_max = halHDMIGetParamMax((UInt32) FEAT_PARAM_HDMIPLL_REGM);

    /* DCO frequency ranges */

    /* DCO lowest frequency supported */
    dco_low_min = halHDMIGetParamMin((UInt32) FEAT_PARAM_DCOFREQ_LOW) / 10000U;

    /* Starting frequency of high frequency range(in Mhz) */
    dco_high_min = halHDMIGetParamMin((UInt32) FEAT_PARAM_DCOFREQ_HIGH);

    /* set dcofreq to 1 if required clock is > 1.25GHz */
    dco_high_min_value = dco_high_min / 10000U;
    pllInfo->dcofreq   = (UInt16) (pixelClock > (Int32) dco_high_min_value);

    if (pixelClock < (Int32) dco_low_min)
    {
        /* Calculate CLKOUTLDO - low frequency */
        for (pllInfo->regn = regn_min; pllInfo->regn < regn_max;
             pllInfo->regn++)
        {
            GT_assert(VpsHalTrace, pllInfo->regn != 0U);
            refclk = clkin / pllInfo->regn;

            regm_min = ((dco_low_min / refclk) < regm_min) ?
                       regm_min : (dco_low_min / refclk);

            for (pllInfo->regm2 = 3; pllInfo->regm2 <= 127; pllInfo->regm2++)
            {
                Int32  value1;
                UInt64 value2;

                value1        = pixelClock * (Int32) pllInfo->regm2;
                pllInfo->regm = (UInt64) value1 / refclk;
                if (!((pllInfo->regm < regm_min) || (pllInfo->regm > regm_max)))
                {
                    pllInfo->regsd =
                        DIV_ROUND_UP((UInt64) ((pllInfo->regm * clkin) / 100U),
                                     (UInt16) pllInfo->regn * 250U);

                    value2 = (UInt64) (clkin * pllInfo->regm) / pllInfo->regn
                             / pllInfo->regm2;
                    phy_calc = (Int32) value2;

                    if (((Bool) pllInfo->regsd) &&
                        ((Bool) (pllInfo->regsd < 255U)) &&
                        ((Bool) (phy_calc <= pixelClock)))
                    {
                        found = TRUE;
                        break;
                    }
                }
            }

            if (found)
            {
                break;
            }
        }
    }
    else
    {
        pllInfo->regm2 = 1;

        /* CLKDCOLDO - high frequency */
        for (pllInfo->regn = regn_min; pllInfo->regn < regn_max;
             pllInfo->regn++)
        {
            UInt64 value2;
            refclk        = clkin / pllInfo->regn;
            pllInfo->regm = (UInt64) pixelClock / refclk;

            if (!((pllInfo->regm < regm_min) || (pllInfo->regm > regm_max)))
            {
                pllInfo->regsd =
                    DIV_ROUND_UP((UInt64) ((pllInfo->regm * clkin) / 100U),
                                 (UInt16) pllInfo->regn * 250U);
                value2 = (UInt64) (clkin * pllInfo->regm) / pllInfo->regn;

                phy_calc = (Int32) value2;

                if ((pllInfo->regsd < 255) && (phy_calc <= pixelClock))
                {
                    found = TRUE;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Failed to find pll settings\r\n");
    }

    /*
     * fractional multiplier is remainder of the difference between
     * multiplier and actual phy(required pixel clock thus should be
     * multiplied by 2^18(262144) divided by the reference clock
     */
    value3         = (UInt64) ((refclk * pllInfo->regm) / pllInfo->regm2);
    value4         = (pixelClock - (Int32) value3);
    mf             = (UInt32) value4 * 262144U;
    value3         = (UInt64) pllInfo->regm2 * (UInt64) mf;
    GT_assert(VpsHalTrace, refclk != 0U);
    pllInfo->regmf = value3 / refclk;

    if (pllInfo->regmf > 262144)
    {
        pllInfo->regmf = 0;
    }

    /* Above logic of finiding dividers is not working for 74.25Mhz frequency,
     * so hardcoding the values for now */
    if (74250 == pixelClock)
    {
        pllInfo->regm  = 0x252;
        pllInfo->regmf = 0;
        pllInfo->regn  = 0x10;
        pllInfo->regm2 = 1;
    }
    /* Set the reference clock to sysclk reference */
    pllInfo->refSel = VPSHAL_HDMI_REFSEL_SYSCLK;

    return;
}

static Int32 halHdmiPllInit(const VpsHal_DssHdmiPllInfo *pllInfo)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt    = 0;
    UInt32 regVal;
    UInt16 value1;

    /* PLL start always use manual mode */
    regVal = HW_RD_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONTROL);
    HW_SET_FIELD32(
        regVal,
        HDMI_PLL_CONTROL_AUTOMODE,
        HDMI_PLL_CONTROL_AUTOMODE_MAN_MODE);
    HW_WR_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONTROL, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION1);
    HW_SET_FIELD32(regVal, HDMI_PLL_CONFIGURATION1_REGM, pllInfo->regm);
    value1 = pllInfo->regn - (UInt16) 1U;
    HW_SET_FIELD32(regVal, HDMI_PLL_CONFIGURATION1_REGN, value1);
    HW_WR_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION1, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION2);
    HW_SET_FIELD32(
        regVal,
        HDMI_PLL_CONFIGURATION2_PHY_CLKINEN,
        HDMI_PLL_CONFIGURATION2_PHY_CLKINEN_CLK_DIS);
    HW_SET_FIELD32(
        regVal,
        HDMI_PLL_CONFIGURATION2_HIGHFREQ,
        HDMI_PLL_CONFIGURATION2_HIGHFREQ_DIV_BY_1);
    HW_SET_FIELD32(
        regVal,
        HDMI_PLL_CONFIGURATION2_REFEN,
        HDMI_PLL_CONFIGURATION2_REFEN_REF_EN);
    HW_SET_FIELD32(regVal, HDMI_PLL_CONFIGURATION2_REFSEL, pllInfo->refSel);
    HW_WR_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION2, regVal);

    if (0U != pllInfo->dcofreq)
    {
        /* divider programming for frequency beyond 1000Mhz */
        HW_WR_FIELD32(
            SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION3,
            HDMI_PLL_CONFIGURATION3_SD,
            pllInfo->regsd);

        /* 1000MHz and 2000MHz */
        HW_WR_FIELD32(
            SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION2,
            HDMI_PLL_CONFIGURATION2_SELFREQDCO,
            0x04U);
    }
    else
    {
        /* 500MHz and 1000MHz */
        HW_WR_FIELD32(
            SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION2,
            HDMI_PLL_CONFIGURATION2_SELFREQDCO,
            0x02U);
    }

    regVal = HW_RD_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION4);
    HW_SET_FIELD32(regVal, HDMI_PLL_CONFIGURATION4_REGM2, pllInfo->regm2);
    HW_SET_FIELD32(regVal, HDMI_PLL_CONFIGURATION4_REGM_F, pllInfo->regmf);
    HW_WR_REG32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONFIGURATION4, regVal);

    /* go now */
    HW_WR_FIELD32(
        SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_GO,
        HDMI_PLL_GO,
        HDMI_PLL_GO_GO);

    /* wait for bit change */
    cnt = 0;
    regVal = HW_RD_FIELD32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_GO, HDMI_PLL_GO);
    while ((regVal == HDMI_PLL_GO_GO) && (cnt < 1000U))
    {
        BspOsal_sleep((UInt32) 1U);
        regVal = HW_RD_FIELD32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_GO, HDMI_PLL_GO);
        cnt++;
    }
    if (cnt >= 1000U)
    {
        retVal = BSP_ETIMEOUT;
    }

    if (retVal == BSP_SOK)
    {
        /* Wait till the lock bit is set in PLL status */
        cnt = 0U;
        regVal = HW_RD_FIELD32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_STATUS,
                               HDMI_PLL_STATUS_LOCK);
        while ((regVal != HDMI_PLL_STATUS_LOCK_DSI_LOCK) &&
               (cnt < 1000U))
        {
            BspOsal_sleep((UInt32) 1U);
            regVal = HW_RD_FIELD32(SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_STATUS,
                                   HDMI_PLL_STATUS_LOCK);
            cnt++;
        }
        if (cnt >= 1000U)
        {
            retVal = BSP_ETIMEOUT;
        }
    }

    return (retVal);
}

/* PLL_PWR_CMD */
static Int32 halHdmiWpSetPllPwr(vpsHal_hdmiPllPwr pllPwr)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;

    /* Command for power control of HDMI PLL */
    HW_WR_FIELD32(
        SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
        HDMI_WP_PWR_CTRL_PLL_CMD,
        pllPwr);

    /* wait till PLL_PWR_STATUS is set */
    cnt = 0;
    while ((HW_RD_FIELD32(
                SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
                HDMI_WP_PWR_CTRL_PLL_STATUS) != pllPwr) &&
           (cnt < 10U))
    {
        BspOsal_sleep((UInt32) 1U);
        cnt++;
    }
    if (cnt >= 10U)
    {
        retVal = BSP_ETIMEOUT;
    }

    return (retVal);
}

static Int32 halHdmiPllReset(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;

    /* SYSRESET  controlled by power FSM */
    HW_WR_FIELD32(
        SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_CONTROL,
        HDMI_PLL_CONTROL_SYSRESETN,
        0x1U);

    /* READ 0x0 reset is in progress */
    cnt = 0;
    while ((HW_RD_FIELD32(
                SOC_HDMI_PLLCTRL_BASE + HDMI_PLL_STATUS,
                HDMI_PLL_STATUS_PLLCTRL_RESET_DONE) !=
            HDMI_PLL_STATUS_PLLCTRL_RESET_DONE_RDONE) &&
           (cnt < 10U))
    {
        BspOsal_sleep((UInt32) 1U);
        cnt++;
    }
    if (cnt >= 10U)
    {
        retVal = BSP_ETIMEOUT;
    }

    return (retVal);
}

Int32 VpsHal_hdmiGetTiming(UInt32                     standard,
                           VpsHal_DssHdmiTimingParam *hdmiConf)
{
    Int32  retVal = BSP_SOK;
    UInt32 idx;

    switch (standard)
    {
        case FVID2_STD_1080P_60:
            idx = 4U;
            break;

        case FVID2_STD_720P_60:
            idx = 2U;
            break;

        case FVID2_STD_1080I_60:
            idx = 3U;
            break;

        case FVID2_STD_480P:
            idx = 1U;
            break;

        default:
            retVal = BSP_EUNSUPPORTED_CMD;
            break;
    }

    if (BSP_SOK == retVal)
    {
        hdmiConf->width       = HdVencStdCeaModeInfo[idx].timing.width;
        hdmiConf->height      = HdVencStdCeaModeInfo[idx].timing.height;
        hdmiConf->pixel_clock = HdVencStdCeaModeInfo[idx].timing.pixel_clock;
        hdmiConf->scanFormat  = HdVencStdCeaModeInfo[idx].timing.scanFormat;
        hdmiConf->hBackPorch  = HdVencStdCeaModeInfo[idx].timing.hBackPorch;
        hdmiConf->hSyncLen    = HdVencStdCeaModeInfo[idx].timing.hSyncLen;
        hdmiConf->hFrontPorch = HdVencStdCeaModeInfo[idx].timing.hFrontPorch;
        hdmiConf->vBackPorch  = HdVencStdCeaModeInfo[idx].timing.vBackPorch;
        hdmiConf->vSyncLen    = HdVencStdCeaModeInfo[idx].timing.vSyncLen;
        hdmiConf->vFrontPorch = HdVencStdCeaModeInfo[idx].timing.vFrontPorch;
        hdmiConf->mode        = HdVencStdCeaModeInfo[idx].timing.mode;
    }

    return (retVal);
}

Int32 vpshal_HdmiPllEnable(const VpsHal_DssHdmiPllInfo *pllInfo)
{
    Int32 retVal = BSP_SOK;

    retVal = halHdmiWpSetPllPwr(VPSHAL_HDMI_PLLPWRCMD_ALLOFF);

    if (retVal == BSP_SOK)
    {
        retVal = halHdmiWpSetPllPwr(VPSHAL_HDMI_PLLPWRCMD_BOTHON_ALLCLKS);
        if (retVal == BSP_SOK)
        {
            retVal = halHdmiPllReset();

            if (retVal == BSP_SOK)
            {
                retVal = halHdmiPllInit(pllInfo);
            }
        }
    }

    return (retVal);
}

void vpshal_HdmiPllDisable(void)
{
    halHdmiWpSetPllPwr(VPSHAL_HDMI_PLLPWRCMD_ALLOFF);

    return;
}

/* PHY_PWR_CMD */
static Int32 halHdmiWpSetPhyPwr(vpsHal_hdmiPhyPwr status)
{
    Int32  retVal = BSP_SOK;
    UInt32 cnt;
    UInt32 regVal;

    /* Command for power control of HDMI PHY */
    HW_WR_FIELD32(
        SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
        HDMI_WP_PWR_CTRL_PHY_CMD,
        status);

    /* Status of the power control of HDMI PHY */
    regVal = HW_RD_FIELD32(SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
                           HDMI_WP_PWR_CTRL_PHY_STATUS);
    cnt = 0;
    while ((regVal != status) && (cnt < 1000U))
    {
        BspOsal_sleep((UInt32) 1U);
        regVal = HW_RD_FIELD32(SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
                            HDMI_WP_PWR_CTRL_PHY_STATUS);
        cnt++;
    }
    if (cnt >= 1000U)
    {
        if (VPSHAL_HDMI_PHYPWRCMD_TXON == status)
        {
            /* In case HDMI cable is not connected PHYPWR status wont change to
             * TxOn till cable is connected. Donot return error here */
        }
        else
        {
            retVal = BSP_ETIMEOUT;
        }
    }

    return (retVal);
}

Int32 vpshal_HdmiPhyPowerOn(const VpsHal_DssHdmiTimingParam *timing)
{
    Int32  retVal  = BSP_SOK;
    UInt16 freqout = 1U;

    /* enable divby2 */
    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_BIST_CONTROL,
        HDMI_BIST_CONTROL_DIV2EN_HFBITCLK,
        0x01U);

    retVal = halHdmiWpSetPhyPwr(VPSHAL_HDMI_PHYPWRCMD_LDOON);

    /*
     *  HDMI_WP_PWR_CTRL doesn't seem to reflect the change in power states,
     *  ignore the error for now - It should be on HPD else might burn out
     */

    /*
     * Read address 0 in order to get the SCP reset done completed
     * Dummy access performed to make sure reset is done
     */
    HW_RD_REG32(SOC_HDMI_PHY_BASE + HDMI_TX_CONTROL);

    /*
     * Write to phy address 0 to configure the clock
     * use HFBITCLK write HDMI_TXPHY_TX_CONTROL_FREQOUT field
     */
    if (timing->pixel_clock < 62500)
    {
        freqout = 0U;
    }
    else if ((timing->pixel_clock >= 62500) && (timing->pixel_clock < 185000))
    {
        freqout = 1U;
    }
    else
    {
        /* clock frequency > 185MHz */
        freqout = 2U;
    }

    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_TX_CONTROL,
        HDMI_TX_CONTROL_FREQOUT,
        freqout);

    /* Write to phy address 1 to start HDMI line (TXVALID and TMDSCLKEN) */
    HW_WR_REG32(SOC_HDMI_PHY_BASE + HDMI_DIGITAL_CONTROL, 0xF0000000U);

    /* Write to phy address 3 to change the polarity control */
    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_PAD_CONFIG_CONTROL,
        HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_CLK,
        0x01U);

    retVal += halHdmiWpSetPhyPwr(VPSHAL_HDMI_PHYPWRCMD_TXON);

    return (retVal);
}

Int32 vpshal_HdmiPhyEnable(UInt32 enable)
{
    Int32 retVal = BSP_SOK;

    if (enable == 1U)
    {
        retVal = halHdmiWpSetPhyPwr(VPSHAL_HDMI_PHYPWRCMD_LDOON);
    }
    else
    {
        retVal = halHdmiWpSetPhyPwr(VPSHAL_HDMI_PHYPWRCMD_OFF);
    }

    return (retVal);
}

/* DSS_HDMI_CORE_VIDEO_CONFIG */
static void halHdmiCoreVideoConfig(const VpsHal_DssHdmiTimingParam *timings,
                                   const VpsHal_DssHdmiOutputInfo  *outputInfo)
{
    UInt32 hBlank;
    UInt32 vBlank;
    UInt32 regVal;

    hBlank = timings->hBackPorch + timings->hFrontPorch + timings->hSyncLen;
    vBlank = timings->vBackPorch + timings->vFrontPorch + timings->vSyncLen;

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INVIDCONF);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_INVIDCONF_VSYNC_IN_POLARITY,
        outputInfo->vsPolarity);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_INVIDCONF_HSYNC_IN_POLARITY,
        outputInfo->hsPolarity);
    /* It is always 1 */
    HW_SET_FIELD32(regVal, HDMI_DWC_TX_FC_INVIDCONF_DE_IN_POLARITY, 1U);
    /* Always 0 need to confirm */
    HW_SET_FIELD32(regVal, HDMI_DWC_TX_FC_INVIDCONF_R_V_BLANK_IN_OSC, 0U);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_INVIDCONF_IN_I_P,
        timings->scanFormat);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_INVIDCONF_DVI_MODEZ,
        timings->mode);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INVIDCONF, regVal);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INHACTIV0,
        HDMI_DWC_TX_FC_INHACTIV0_H_IN_ACTIV_0,
        (timings->width & 0xFFU));
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INHACTIV1,
        HDMI_DWC_TX_FC_INHACTIV1_H_IN_ACTIV_1,
        (timings->width >> 8U));

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INVACTIV0,
        HDMI_DWC_TX_FC_INVACTIV0_V_IN_ACTIV_0,
        (timings->height & 0xFFU));
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INVACTIV1,
        HDMI_DWC_TX_FC_INVACTIV1_V_IN_ACTIV_1,
        (timings->height >> 8U));

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INHBLANK0,
        HDMI_DWC_TX_FC_INHBLANK0_H_IN_BLANK_0,
        (hBlank & 0xFFU));
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INHBLANK1,
        HDMI_DWC_TX_FC_INHBLANK1_H_IN_BLANK_1,
        (hBlank >> 8U));

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_INVBLANK,
        HDMI_DWC_TX_FC_INVBLANK_V_IN_BLANK,
        vBlank);

    /* right_margin */
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_HSYNCINDELAY1,
        HDMI_DWC_TX_FC_HSYNCINDELAY1_H_IN_DELAY_1,
        (timings->hFrontPorch >> 8));
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_HSYNCINDELAY0,
        HDMI_DWC_TX_FC_HSYNCINDELAY0_H_IN_DELAY_0,
        (timings->hFrontPorch & 0xFFU));

    /* Lower margin */
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_VSYNCINDELAY,
        HDMI_DWC_TX_FC_VSYNCINDELAY_V_IN_DELAY,
        timings->vFrontPorch);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_HSYNCINWIDTH1,
        HDMI_DWC_TX_FC_HSYNCINWIDTH1_H_IN_WIDTH_1,
        (timings->hSyncLen >> 8));
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_HSYNCINWIDTH0,
        HDMI_DWC_TX_FC_HSYNCINWIDTH0_H_IN_WIDTH_0,
        (timings->hSyncLen & 0xFFU));

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_VSYNCINWIDTH,
        HDMI_DWC_TX_FC_VSYNCINWIDTH_V_IN_WIDTH,
        timings->vSyncLen);

    return;
}

static void halHdmiCoreVideoPacketizerConfig(
    const VpsHal_DssHdmiParam *advParam)
{
    UInt32 clrDepth = 0; /* Deep color is assumed to be 24bit*/
    UInt32 regVal;

    switch (advParam->deepColor)
    {
        case VPSHAL_HDMI_DEEP_COLOR_30BIT:
            clrDepth = 5U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_36BIT:
            clrDepth = 6U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_24BIT:
        default:
            clrDepth = 0;
            break;
    }

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_PR_CD,
        HDMI_DWC_TX_VP_PR_CD_COLOR_DEPTH,
        clrDepth);

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_CONF);
    if (clrDepth != 0U)
    {
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_BYPASS_EN, 0U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_PP_EN, 1U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_YCC422_EN, 0U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_OUTPUT_SELECTOR, 0U);
    }
    else
    {
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_BYPASS_EN, 1U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_PP_EN, 0U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_YCC422_EN, 0U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_CONF_OUTPUT_SELECTOR, 0x02U);
    }
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_CONF, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_STUFF);
    if (clrDepth != 0U)
    {
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_STUFF_PP_STUFFING, 0U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_STUFF_YCC422_STUFFING, 1U);
    }
    else
    {
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_STUFF_PP_STUFFING, 1U);
        HW_SET_FIELD32(regVal, HDMI_DWC_TX_VP_STUFF_YCC422_STUFFING, 1U);
    }
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_STUFF, regVal);

    return;
}

static void halHdmiCoreVideoSamplerConfig(const VpsHal_DssHdmiParam *advHdmi)
{
    UInt32 videoMapping;

    switch (advHdmi->deepColor)
    {
        case VPSHAL_HDMI_DEEP_COLOR_30BIT:
            videoMapping = 3U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_36BIT:
            videoMapping = 5U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_24BIT:
        default:
            videoMapping = 1U;
            break;
    }

    /* VIDEO_MAPPING */
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_TX_INVID0,
        HDMI_DWC_TX_TX_INVID0_VIDEO_MAPPING,
        videoMapping);

    return;
}

static void halHdmiCoreAuxInfoframeAviConfig(
    const vpsHal_hdmiCoreAviInfoframe *aviInfoFrame)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF0);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF0_RGB_YCC_INDICATOR,
        aviInfoFrame->db1Format);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF0_BAR_INFO,
        aviInfoFrame->db1BarInfoDv);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF0_SCAN_INFORMATION,
        aviInfoFrame->db1ScanInfo);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF0_ACTIVE_FORMAT_INFO,
        aviInfoFrame->db1ActiveInfo);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF0, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF1);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF1_ACTIVE_ASPEC_RATIO,
        aviInfoFrame->db2AspectRatio);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF1_COLORIMETRY,
        aviInfoFrame->db2Colorimetry);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF1_PICTURE_ASPECT_RATIO,
        aviInfoFrame->db2ActiveFmtAr);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF1, regVal);

    regVal = HW_RD_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF2);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF2_ITCONTENT,
        aviInfoFrame->db3Itc);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF2_EC,
        aviInfoFrame->db3Ec);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF2_QUANTIZATION_RANGE,
        aviInfoFrame->db3QRange);
    HW_SET_FIELD32(
        regVal,
        HDMI_DWC_TX_FC_AVICONF2_NON_PICTURE_SCALING,
        aviInfoFrame->db3NupScaling);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVICONF2, regVal);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_AVIVID,
        HDMI_DWC_TX_FC_AVIVID_VID,
        aviInfoFrame->db4Videocode);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_PRCONF,
        HDMI_DWC_TX_FC_PRCONF_OUTPUT_PR_FACTOR,
        aviInfoFrame->db5PixelRepeat);

    return;
}

static void halHdmiCoreCscConfig(cscTable cscCoeff)
{
    UInt16 value1;

    value1 = cscCoeff.a1 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A1_MSB,
        HDMI_DWC_TX_CSC_COEF_A1_MSB_A1COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A1_LSB,
        HDMI_DWC_TX_CSC_COEF_A1_LSB_A1COEF_LSB,
        cscCoeff.a1);

    value1 = cscCoeff.a2 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A2_MSB,
        HDMI_DWC_TX_CSC_COEF_A2_MSB_A2COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A2_LSB,
        HDMI_DWC_TX_CSC_COEF_A2_LSB_A2COEF_LSB,
        cscCoeff.a2);

    value1 = cscCoeff.a3 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A3_MSB,
        HDMI_DWC_TX_CSC_COEF_A3_MSB_A3COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A3_LSB,
        HDMI_DWC_TX_CSC_COEF_A3_LSB_A3COEF_LSB,
        cscCoeff.a3);

    value1 = cscCoeff.a4 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A4_MSB,
        HDMI_DWC_TX_CSC_COEF_A4_MSB_A4COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_A4_LSB,
        HDMI_DWC_TX_CSC_COEF_A4_LSB_A4COEF_LSB,
        cscCoeff.a4);

    value1 = cscCoeff.b1 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B1_MSB,
        HDMI_DWC_TX_CSC_COEF_B1_MSB_B1COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B1_LSB,
        HDMI_DWC_TX_CSC_COEF_B1_LSB_B1COEF_LSB,
        cscCoeff.b1);

    value1 = cscCoeff.b2 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B2_MSB,
        HDMI_DWC_TX_CSC_COEF_B2_MSB_B2COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B2_LSB,
        HDMI_DWC_TX_CSC_COEF_B2_LSB_B2COEF_LSB,
        cscCoeff.b2);

    value1 = cscCoeff.b3 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B3_MSB,
        HDMI_DWC_TX_CSC_COEF_B3_MSB_B3COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B3_LSB,
        HDMI_DWC_TX_CSC_COEF_B3_LSB_B3COEF_LSB,
        cscCoeff.b3);

    value1 = cscCoeff.b4 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B4_MSB,
        HDMI_DWC_TX_CSC_COEF_B4_MSB_B4COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_B4_LSB,
        HDMI_DWC_TX_CSC_COEF_B4_LSB_B4COEF_LSB,
        cscCoeff.b4);

    value1 = cscCoeff.c1 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C1_MSB,
        HDMI_DWC_TX_CSC_COEF_C1_MSB_C1COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C1_LSB,
        HDMI_DWC_TX_CSC_COEF_C1_LSB_C1COEF_LSB,
        cscCoeff.c1);

    value1 = cscCoeff.c2 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C2_MSB,
        HDMI_DWC_TX_CSC_COEF_C2_MSB_C2COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C2_LSB,
        HDMI_DWC_TX_CSC_COEF_C2_LSB_C2COEF_LSB,
        cscCoeff.c2);

    value1 = cscCoeff.c3 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C3_MSB,
        HDMI_DWC_TX_CSC_COEF_C3_MSB_C3COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEF_C3_LSB,
        HDMI_DWC_TX_CSC_COEF_C3_LSB_C3COEF_LSB,
        cscCoeff.c3);

    value1 = cscCoeff.c4 >> (UInt16) 8U;
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEFC4_MSB,
        HDMI_DWC_TX_CSC_COEFC4_MSB_C4COEF_MSB,
        value1);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_COEFC4_LSB,
        HDMI_DWC_TX_CSC_COEFC4_LSB_C4COEF_LSB,
        cscCoeff.c4);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_MC_FLOWCTRL,
        HDMI_DWC_TX_MC_FLOWCTRL_CSC_FEED_THROUGH_OFF,
        0x1);

    return;
}

Int32 halHdmiCoreConfigureRange(const VpsHal_DssHdmiParam   *advHdmi,
                                vpsHal_hdmiCoreAviInfoframe *aviInfoFrame)
{
    cscTable cscCoeff = {0};
    Int32    retval   = BSP_SOK;

    switch (advHdmi->Range) {
        case VPSHAL_HDMI_LIMITED_RANGE:
            cscCoeff = cscHdmiTableDeepColor[advHdmi->deepColor];
            aviInfoFrame->db3QRange = VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_LR;
            break;
        case VPSHAL_HDMI_FULL_RANGE:
            cscCoeff = cscHdmiTableDeepColor[3]; /* full range */
            aviInfoFrame->db3QRange = VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_FR;
            break;
        default:
            retval = BSP_EINVALID_PARAMS;
            break;
    }
    halHdmiCoreCscConfig(cscCoeff);
    return (retval);
}

void halHdmiVideoPathEnable(void)
{
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_CTRLDUR, (UInt32) 0x0CU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_EXCTRLDUR, (UInt32) 0x20U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_EXCTRLSPAC,
        HDMI_DWC_TX_FC_EXCTRLSPAC_EXTCTRLPERIODSPACING,
        0x01U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_CH0PREAM,
        HDMI_DWC_TX_FC_CH0PREAM_CH0_PREAMBLE_FILTER,
        0x0BU);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_CH1PREAM,
        HDMI_DWC_TX_FC_CH1PREAM_CH1_PREAMBLE_FILTER,
        0x16U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_CH2PREAM,
        HDMI_DWC_TX_FC_CH2PREAM_CH2_PREAMBLE_FILTER,
        0x21U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_MC_CLKDIS,
        HDMI_DWC_TX_MC_CLKDIS_PIXELCLK_DISABLE,
        0U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_MC_CLKDIS,
        HDMI_DWC_TX_MC_CLKDIS_PIXELCLK_DISABLE,
        0U);

    return;
}

static void halHdmiCoreColorDepthConfig(const VpsHal_DssHdmiParam *advHdmi)

{
    UInt16 clrDepth;

    switch (advHdmi->deepColor)
    {
        case VPSHAL_HDMI_DEEP_COLOR_30BIT:
            clrDepth = 5U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_36BIT:
            clrDepth = 6U;
            break;
        case VPSHAL_HDMI_DEEP_COLOR_24BIT:
        default:
            clrDepth = 0;
            break;
    }

    /* CSC_COLORDEPTH */
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CSC_SCALE,
        HDMI_DWC_TX_CSC_SCALE_CSC_COLORDEPTH,
        clrDepth);

    return;
}

static void halHdmiCoreMaskInterrupts(void)
{
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_VP_MASK, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_MASK0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_MASK1, (UInt32) 0xFBU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_FC_MASK2, (UInt32) 0x3U);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_PHY_MASK0, (UInt32) 0xF3U);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_CEC_MASK, (UInt32) 0xffU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_GP_MASK, (UInt32) 0x3U);
    /* HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + 0x1F408, 0xFF); / *
     * HDMI_CORE_CEC_MAGIC_MASK * /
     **/
    /* HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + 0x1F814, 0xFB); / *
     *HDMI_CORE_I2C1_MASK * / */
    /* HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + 0x1F818, 0x3); / * HDMI_CORE_I2C2_MASK
    ** / */
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_FC_STAT0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_FC_STAT1, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_FC_STAT2, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_AS_STAT0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_PHY_STAT0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_I2CM_STAT0,
                (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_CEC_STAT0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_VP_STAT0, (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_I2CMPHY_STAT0,
                (UInt32) 0xFFU);
    HW_WR_REG32(SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_IH_MUTE, (UInt32) 0x3U);

    return;
}

static Int32 halHdmiTimingsCompare(const VpsHal_DssHdmiTimingParam *inTiming,
                                   const VpsHal_DssHdmiTimingParam *stdTiming)
{
    UInt32 inTimingVsync, inTimingHsync, stdTimingVsync, stdTimingHsync;
    Int32  retVal = BSP_EFAIL;

    if ((stdTiming->pixel_clock == inTiming->pixel_clock) &&
        (stdTiming->width == inTiming->width) &&
        (stdTiming->height == inTiming->height))
    {
        stdTimingHsync = stdTiming->hFrontPorch + stdTiming->hSyncLen +
                         stdTiming->hBackPorch;
        inTimingHsync = inTiming->hFrontPorch + inTiming->hSyncLen +
                        inTiming->hBackPorch;
        stdTimingVsync = stdTiming->vFrontPorch + stdTiming->vSyncLen +
                         stdTiming->vBackPorch;
        inTimingVsync = stdTiming->vFrontPorch + stdTiming->vSyncLen +
                        stdTiming->vBackPorch;

        if ((inTimingHsync == stdTimingHsync) &&
            (inTimingVsync == stdTimingVsync))
        {
            retVal = BSP_SOK;
        }
    }

    return (retVal);
}

static UInt32 halHdmiFindStdCode(const VpsHal_DssHdmiTimingParam *timing)

{
    UInt32 i, stdCode = 0;

    if (timing->mode == VPSHAL_HDMI_HDMI)
    {
        for (i = 0;
             i < (sizeof (HdVencStdCeaModeInfo) / sizeof (HdVenc_StdModeInfo));
             i++)
        {
            if (halHdmiTimingsCompare(timing,
                                      &HdVencStdCeaModeInfo[i].timing) ==
                BSP_SOK)
            {
                stdCode = HdVencStdCeaModeInfo[i].stdCode;
                break;
            }
        }
    }
    else
    {
        for (i = 0;
             i < (sizeof (HdVencStdVesaModeInfo) / sizeof (HdVenc_StdModeInfo));
             i++)
        {
            if (halHdmiTimingsCompare(timing,
                                      &HdVencStdVesaModeInfo[i].timing) ==
                BSP_SOK)
            {
                stdCode = HdVencStdVesaModeInfo[i].stdCode;
                break;
            }
        }
    }

    return stdCode;
}

void VpsHal_hdmiVencOuptputConfig(const VpsHal_DssHdmiOutputInfo *opInfo)
{
    HdmiHalInfo.outputInfo.dataFormat = opInfo->dataFormat;
    HdmiHalInfo.outputInfo.hsPolarity = opInfo->hsPolarity;
    HdmiHalInfo.outputInfo.vsPolarity = opInfo->vsPolarity;

    return;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_010)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-864) DOX_REQ_TAG(PDK-865) DOX_REQ_TAG(PDK-866)
 *          DOX_REQ_TAG(PDK-867) DOX_REQ_TAG(PDK-868)
 */
/**
 *  VpsHal_hdmiBasicConfigure
 *  \brief Sets the buffer address for a particular pipeline
 *
 *  This function will program the buffer address for a pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *  \param field            Top or bottom field.0-top field, 1-bottom field
 *                          For progressive buffers always use 0.
 *  \param baseAddRGBY      Base address of RGB or Y plane depending on format.
 *  \param baseAddCbCr      Valid only for YUV420-NV12 format.
 *
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
void VpsHal_hdmiBasicConfigure(const VpsHal_DssHdmiTimingParam *hdmiCfg)
{
    vpsHal_hdmiCoreAviInfoframe *aviCfg = &HdmiHalInfo.aviInfo;

    halHdmiCoreMaskInterrupts();

    halHdmiWpVideoTimingConfig(hdmiCfg);

    HdmiHalInfo.timing = *hdmiCfg;

    HdmiHalInfo.advParam.deepColor = 0;
    /* video config */
    HdmiHalInfo.advParam.packingMode = VPSHAL_HDMI_PACK_24b_RGB_YUV444_YUV422;

    halHdmiWpVideoFormatConfig(&HdmiHalInfo.timing,
                               &HdmiHalInfo.advParam,
                               &HdmiHalInfo.outputInfo);

    HdmiHalInfo.advParam.standardCode = halHdmiFindStdCode(&HdmiHalInfo.timing);

    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_PHY_CONF0,
        HDMI_DWC_TX_PHY_CONF0_PDZ,
        1U);
    HW_WR_FIELD32(
        SOC_HDMI_DWC_TX_BASE + HDMI_DWC_TX_PHY_CONF0,
        HDMI_DWC_TX_PHY_CONF0_ENTMDS,
        1U);

    if (hdmiCfg->outputRange == VPS_DCTRL_VENC_OUTPUT_LIMITED_RANGE)
    {
        HdmiHalInfo.advParam.Range = VPSHAL_HDMI_LIMITED_RANGE;
    }
    else
    {
        /* Default configure full range color */
        HdmiHalInfo.advParam.Range = VPSHAL_HDMI_FULL_RANGE;
    }

    if (HdmiHalInfo.advParam.standardCode != 0)
    {
        /* configure packet
         * info frame video see doc CEA861-D page 65
         */
        aviCfg->db1Format     = VPSHAL_HDMI_INFOFRAME_AVI_DB1Y_RGB;
        aviCfg->db1ActiveInfo =
            VPSHAL_HDMI_INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_OFF;
        aviCfg->db1BarInfoDv   = VPSHAL_HDMI_INFOFRAME_AVI_DB1B_NO;
        aviCfg->db1ScanInfo    = VPSHAL_HDMI_INFOFRAME_AVI_DB1S_0;
        aviCfg->db2Colorimetry = VPSHAL_HDMI_INFOFRAME_AVI_DB2C_NO;
        aviCfg->db2AspectRatio = VPSHAL_HDMI_INFOFRAME_AVI_DB2M_NO;
        aviCfg->db2ActiveFmtAr = VPSHAL_HDMI_INFOFRAME_AVI_DB2R_SAME;
        aviCfg->db3Itc         = VPSHAL_HDMI_INFOFRAME_AVI_DB3ITC_NO;
        aviCfg->db3Ec          =
            VPSHAL_HDMI_INFOFRAME_AVI_DB3EC_XVYUV601;
        aviCfg->db3QRange =
            VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_DEFAULT;
        aviCfg->db3NupScaling           = VPSHAL_HDMI_INFOFRAME_AVI_DB3SC_NO;
        aviCfg->db4Videocode            = HdmiHalInfo.advParam.standardCode;
        aviCfg->db5PixelRepeat          = VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_NO;
        aviCfg->db67LineEndofTop        = 0;
        aviCfg->db89LineStartofBottom   = 0;
        aviCfg->db1011PixelEofLeft      = 0;
        aviCfg->db1213PixelStartofRight = 0;

        halHdmiCoreConfigureRange(&HdmiHalInfo.advParam, &HdmiHalInfo.aviInfo);
        halHdmiCoreAuxInfoframeAviConfig(&HdmiHalInfo.aviInfo);
    }
    else
    {
        halHdmiCoreConfigureRange(&HdmiHalInfo.advParam, &HdmiHalInfo.aviInfo);
    }
    halHdmiCoreAuxInfoframeAviConfig(&HdmiHalInfo.aviInfo);
    /*
     * configure core video part
     * set software reset in the core
     */
    HdmiHalInfo.advParam.pktMode = VPSHAL_HDMI_PACKETMODE24BITPERPIXEL;

    halHdmiCoreVideoConfig(&HdmiHalInfo.timing,
                           &HdmiHalInfo.outputInfo);
    halHdmiCoreVideoPacketizerConfig(&HdmiHalInfo.advParam);

    halHdmiCoreColorDepthConfig(&HdmiHalInfo.advParam);

    halHdmiCoreVideoSamplerConfig(&HdmiHalInfo.advParam);

    halHdmiVideoPathEnable();

    return;
}

void vpshal_HdmiFlipDataPnOrder(void)
{
    /* Flip Data line polarity */
    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_PAD_CONFIG_CONTROL,
        HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D0,
        0x01U);
    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_PAD_CONFIG_CONTROL,
        HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D1,
        0x01U);
    HW_WR_FIELD32(
        SOC_HDMI_PHY_BASE + HDMI_PAD_CONFIG_CONTROL,
        HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D2,
        0x01U);

    return;
}
