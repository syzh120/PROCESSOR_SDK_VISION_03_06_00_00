/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file bsp_platformTda2xx.c
 *
 *  \brief Implements the Tda2xx platform specific functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <bsp_platformTda2xx.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmlib.h>

#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined(SOC_AM571x)
#include <ti/csl/src/ip/ecap/V0/ecap.h>
#endif
#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/include/vps_capture.h>
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PRCM_ENABLE                     ((UInt32) 2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* For AM devices pinmux is done in board module */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
static Int32 Bsp_platformTda2xxSetPinMux(
    const Bsp_PlatformInitParams *initParams);
#endif

static Int32 Bsp_platformTda2xxEnableMcASP3(void);
static Int32 Bsp_platformTda2xxEnableMcASP6(void);

static Int32 Bsp_platformTda2xxEnableMcSPI1(void);
static Int32 Bsp_platformTda2xxEnableMcSPI2(void);
static Int32 Bsp_platformTda2xxEnableMcSPI3(void);
static Int32 Bsp_platformTda2xxEnableMcSPI4(void);
static void  Bsp_platformTda2xxXbarConfig(void);

#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (TDA2XX_MC_BUILD) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (BOARD_TYPE_TDA2XX_RVP)
static Int32 Bsp_platformTda2xxEnableI2C5(void);
#endif


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformTda2xxInit(const Bsp_PlatformInitParams *initParams)
{
    Int32          status = BSP_SOK;
    Bsp_PlatformId bspPlatformId;

    bspPlatformId = Bsp_platformGetId();

    if ((TRUE == initParams->isPinMuxSettingReq)
        && ((BSP_PLATFORM_ID_EVM == bspPlatformId)
            || (BSP_PLATFORM_ID_ZEBU == bspPlatformId)))
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
        status = Bsp_platformTda2xxSetPinMux(initParams);
#endif
    }

    /* Cross bar setup */
    if (TRUE == initParams->isIrqXBarSettingReq)
    {
        Bsp_platformTda2xxXbarConfig();
    }

    if (TRUE == initParams->isDmaXBarSettingReq)
    {
        /* Unlock MMR_LOCK_1  */
        Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);
#if defined (SOC_AM572x) || defined (SOC_AM574x) || defined(SOC_AM571x)
         /* XBAR MCASP_DREQ_RX to IPU1_15
          * XBAR MCASP_DREQ_TX to IPU1_14 */
        *((volatile UInt32 *) 0x4A002B94U) =
            ((UInt32) 132 << 16) | (UInt32) 133;
#endif
    }

    if (TRUE == initParams->isAllMcASPInitReq)
    {
        /* For audio on the CPU board */
        status += Bsp_platformTda2xxEnableMcASP3();
        /* For audio on JAMR3 */
        status += Bsp_platformTda2xxEnableMcASP6();
    }

    status += Bsp_platformTda2xxEnableMcSPI1();
    if (TRUE == initParams->isAllMcSPIInitReq)
    {
        status += Bsp_platformTda2xxEnableMcSPI2();
        status += Bsp_platformTda2xxEnableMcSPI3();
        status += Bsp_platformTda2xxEnableMcSPI4();
    }

#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (TDA2XX_MC_BUILD) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (BOARD_TYPE_TDA2XX_RVP)
    /* Enable I2C5 module */
    status += Bsp_platformTda2xxEnableI2C5();
#endif

    return (status);
}

Int32 Bsp_platformTda2xxDeInit(void)
{
    Int32 status = BSP_SOK;

    return (status);
}

Bsp_PlatformCpuRev Bsp_platformTda2xxGetCpuRev(void)
{
    UInt32 prodId, cpuRev;
    Bsp_PlatformCpuRev cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;

    prodId = HW_RD_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                         CTRL_WKUP_ID_CODE);
    cpuRev = (prodId & 0xF0000000U) >> 28U;
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
    switch (cpuRev)
    {
        case 0x0U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;
            break;
        case 0x1U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
        case 0x2U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_1;
            break;
        default:
            /* Default to last known version */
            GT_0trace(
                BspPlatTrace, GT_INFO,
                "PLATFORM: UNKNOWN CPU detected, defaulting to CPU REV 2.0\r\n");
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
    }
#else
    switch (cpuRev)
    {
        case 0x0U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_0;
            break;
        case 0x1U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_1_1;
            break;
        case 0x2U:
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
        default:
            /* Default to last known version */
            GT_0trace(
                BspPlatTrace, GT_INFO,
                "PLATFORM: UNKNOWN CPU detected, defaulting to CPU REV 2.0\r\n");
            cpuRevEnum = BSP_PLATFORM_CPU_REV_2_0;
            break;
    }
#endif
    return (cpuRevEnum);
}

Bsp_PlatformPackageType Bsp_platformTda2xxGetPackageType(void)
{
    Bsp_PlatformPackageType packageType = BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN;

    #if defined (SOC_TDA2EX)
    UInt32 regVal;
    regVal = HW_RD_FIELD32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE + CTRL_WKUP_STD_FUSE_DIE_ID_2,
        CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE);
    if (regVal == 0x1U)
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_17x17;
    }
    else if (regVal == 0x2U)
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_23x23;
    }
    else
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN;
    }
#endif

    return (packageType);
}

Int32 Bsp_platformTda2xxSetDispcFuncClkSrc(UInt32 fClkSrc)
{
    Int32 retVal = BSP_SOK;

    if (fClkSrc >= BSP_PLATFORM_CLKSRC_MAX)
    {
        GT_0trace(BspPlatTrace, GT_ERR, "clock source not valid \r\n");
        retVal = BSP_EBADARGS;
    }

    if (BSP_SOK == retVal)
    {
        retVal = PMLIBVideopllSetDispcFuncClkSrc(
            (pmlibVideoPllClkSrc_t) fClkSrc);
        if ((Int32) PM_BADARGS == retVal)
        {
            GT_0trace(BspPlatTrace, GT_ERR,
                      "clock source not valid \r\n");
        }
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms)
{
    Int32 retVal = BSP_SOK;

    retVal = PMLIBVideopllSetVencClkSrc(
        (pmlibVideoPllVenc_t) vencPrms->outputVenc,
        (pmlibVideoPllClkSrc_t) vencPrms->vencClkSrc);
    if ((Int32) PM_BADARGS == retVal)
    {
        GT_0trace(BspPlatTrace, GT_ERR,
                  "clock source not valid \r\n");
    }
    return retVal;
}

/**
 *  \brief  program_dss_video_pll function program the DSS video1,video2 & hdmi
 *          PLL
 *
 *          DSS PLL Programming steps
 *
 *          1) Enable PLL programming in CTRL_CORE_DSS_PLL_CONTROL
 *          2) Enable DSS SCP Interface - DSI_CLK_CTRL.CIO_CLK_ICG
 *          3) DSI Power enable - DSI_CLK_CTRL.PLL_PWR_CMD
 *          4) Check for PLL reset status -PLL_STATUS.PLLCTRL_RESET_DONE
 *          5) set the M,N & H-DIV
 *
 * \param   None.
 *
 * \return  error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.
 *
 **/
Int32 Bsp_platformTda2xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq)
{
    Int32  retVal    = BSP_SOK;
    UInt32 timeDelay = 0xFFFFFFFFU;
    pmhalPrcmNodeId_t videopllId;
    UInt32 maxorMinMN;

    if (pllFreq->videoPll == BSP_PLATFORM_PLL_VIDEO1)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    else if (pllFreq->videoPll == BSP_PLATFORM_PLL_VIDEO2)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO2;
    }
#endif
    else if (pllFreq->videoPll == BSP_PLATFORM_PLL_HDMI)
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_HDMI;
    }
    else
    {
        videopllId = PMHAL_PRCM_VIDEOPLL_UNDEF;
        retVal     = BSP_EBADARGS;
    }

    if (pllFreq->chooseMaxorMinMN == BSP_PLATFORM_VIDEO_PLL_CALC_MIN_MN)
    {
        maxorMinMN = PMLIB_VIDEO_PLL_CALC_MIN_MN;
    }
    else if (pllFreq->chooseMaxorMinMN == BSP_PLATFORM_VIDEO_PLL_CALC_MAX_MN)
    {
        maxorMinMN = PMLIB_VIDEO_PLL_CALC_MAX_MN;
    }
    else
    {
        retVal = BSP_EBADARGS;
    }

    if (BSP_SOK == retVal)
    {
        retVal = PMLIBVideopllSetFreq(videopllId,
                                      (uint32_t) pllFreq->pixelClk,
                                      (uint32_t) maxorMinMN,
                                      timeDelay);
    }

    if (PM_SUCCESS == retVal)
    {
        GT_0trace(BspPlatTrace, GT_DEBUG,
                  "\r\n DSS PLL Programming - completed");
    }
    else
    {
        GT_0trace(BspPlatTrace, GT_DEBUG, "\r\n DSS PLL Programming - Failed ");
    }

    return (retVal);
}

Int32 Bsp_platformTda2xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk)
{
    Int32            retVal = BSP_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX)|| defined (SOC_AM574x)  || defined (SOC_DRA75x)
    volatile UInt32 *pRegs[6];
    UInt32           instId, portId;

    if (vipInstId >= 12U)
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        pRegs[0U] = (volatile UInt32 *) (SOC_VIP1_VIP_REGS_BASE + 0xE100U);
        pRegs[1U] = (volatile UInt32 *) (SOC_VIP1_VIP_REGS_BASE + 0xE200U);
        pRegs[2U] = (volatile UInt32 *) (SOC_VIP2_VIP_REGS_BASE + 0xE100U);
        pRegs[3U] = (volatile UInt32 *) (SOC_VIP2_VIP_REGS_BASE + 0xE200U);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
        pRegs[4U] = (volatile UInt32 *) (SOC_VIP3_VIP_REGS_BASE + 0xE100U);
        pRegs[5U] = (volatile UInt32 *) (SOC_VIP3_VIP_REGS_BASE + 0xE200U);
#endif

        instId = vipInstId / 2U;
        portId = vipInstId % 2U;
        /* MISRA.PTR.ARITH Does not exceed portId */
        pRegs[instId][0U + portId] = fileId;
        pRegs[instId][2U + portId] = pixelClk;
    }
#endif
    return (retVal);
}

/**
 *  \brief  Bsp_platformTda2xxGetFtRev function to Get FT Revision Number
 */
UInt32 Bsp_platformTda2xxGetFtRev(void)
{
    UInt32 ftRev;

    ftRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_STD_FUSE_DIE_ID_2);

    /* FT revision is found in bits [15:8] */
    ftRev &= (UInt32) 0x0000FF00;

    ftRev = (ftRev >> 0x8);

    return (ftRev);
}

/**
 *  \brief  Bsp_platformTda2xxEnableHdmiPll function to enable/disable HDMI PLL
 *          PLL
 *
 * \param   enable.
 *          1 -  enable PLL
 *          0 -   Disable PLL
 *
 * \return  error status.If error has occured it returns a non zero value.
 *             If no error has occured then return status will be zero.
 *
 **/
Int32 Bsp_platformTda2xxEnableHdmiPll(UInt32 enable)
{
    Int32 retVal;

    retVal = PMLIBVideopllEnableHdmiPll(enable);

    return retVal;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
static Int32 Bsp_platformTda2xxSetPinMux(
    const Bsp_PlatformInitParams *initParams)
{
    /* I2C1 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C1_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C1_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* I2C4 mux */
#if !defined(BOARD_TYPE_TDA2XX_RVP)
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#endif

#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_TDA2PX)
    /* I2C5 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 10, (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 10, (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#else
    /* I2C2 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
#endif

    /* UART1 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_RXD,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_TXD,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

    /* GPIO mux ( for OV,LI,Aptina, Multi Deserialiser and SIL9127 Sensor) */
    if (BSP_PLATFORM_ID_ZEBU != Bsp_platformGetId())
    {
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
        /* In TDA2XX EVM, needs to be configured as GPIO for mux programming
         * PAD=vin2a_d12, PIN=gpio4_13
         * PAD=vin2a_d13, PIN=gpio4_14
         * PAD=vin2a_d14, PIN=gpio4_15
         * PAD=vin2a_d15, PIN=gpio4_16 */
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));

        /* PAD=mcasp2_axr6, PIN=gpio2_29
         * PAD=mcasp2_axr4, PIN=gpio1_4
         * PAD=mcasp2_axr5, PIN=gpio6_7 */
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR6,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_MCASP2_AXR5,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
#endif
#if defined (SOC_TDA2PX)
        /* PAD=vin1a_fld0, PIN=gpio3_0  used for LCD power on */
        Bsp_platformSetPinmuxRegs((UInt32) 14,
                                  (UInt32) CTRL_CORE_PAD_VIN1A_FLD0,
                                  (BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE
                                   |
                                   BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN |
                                   BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT));
#endif
    }

    /* GPIO mux, OV_PWDN of vision board is connected to GPIO6_17
     * PAD=xref_clk0, PIN=gpio6_17 */
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_XREF_CLK0,
                              BSP_PLATFORM_IOPAD_CFG_DEFAULT);

#ifdef TDA2XX_MC_BUILD
    /* UART3 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART3_TXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_UART3_RXD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /* I2C3 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    /* I2C4 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    /* I2C5 mux */
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_GPMC_A5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_GPMC_A4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* UART1_CTSN  => (gpio7_24) CAM_S1_GPIO_0*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* UART1_RTSN  => (gpio7_25) CAM_S1_GPIO_0*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* I2C2_SDA  => HDMI_SDA*/
    Bsp_platformSetPinmuxRegs((UInt32) 1, (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* I2C2_SCL  => HDMI_SCL*/
    Bsp_platformSetPinmuxRegs((UInt32) 1, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* GPIO6_11  => (GPIO6_11) CAM_S1_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_GPIO6_11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_UP);

    /* CTRL_CORE_PAD_MCASP1_AXR4  => (gpio5_6) CAM_S2_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*VIN5A Configuration*/
    /*CAM_S1_D7*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D6*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D5*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D4*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D3*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D2*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D1*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D0*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D8*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D9*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D10*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D11*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP5_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D12*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D13*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D14*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_D15*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_HS*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_VS*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_PCLK*/
    Bsp_platformSetPinmuxRegs((UInt32) 9, (UInt32) CTRL_CORE_PAD_GPIO6_10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S1_RESET*/
    Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_GPIO6_11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_2*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP2_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*VIN6A Configuration*/
    /*CAM_S2_RESET -> MCASP1_AXR4 (gpio5_6)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR4,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_PCLK -> XREF_CLK1 (vin6a_clk0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_VS -> MCASP1_AXR0 (vin6a_vsync0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_HS -> MCASP1_AXR1 (vin6a_hsync0)*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_0 -> MCASP1_AXR5 (gpio5_7)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR5,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_1 -> MCASP1_AXR6 (gpio5_8)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR6,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_GPIO_2 -> MCASP1_AXR7 (gpio5_9)*/
    Bsp_platformSetPinmuxRegs((UInt32) 14, (UInt32) CTRL_CORE_PAD_MCASP1_AXR7,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_OUT |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_ENABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*CAM_S2_D7*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D6*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D5*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_AXR2,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D4*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP2_AXR3,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D3*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D2*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D1*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D0*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

    /*CAM_S2_D8*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR15,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D9*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR14,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D10*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR13,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D11*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR12,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D12*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D13*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D14*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);
    /*CAM_S2_D15*/
    Bsp_platformSetPinmuxRegs((UInt32) 7, (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                              BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI |
                              BSP_PLATFORM_IOPAD_CFG_PULLUDENABLE_DISABLE |
                              BSP_PLATFORM_IOPAD_CFG_PULLTYPESELECT_DOWN);

#endif /* TDA2XX_MC_BUILD */
    return (BSP_SOK);
}
#endif

static Int32 Bsp_platformTda2xxEnableMcASP6(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x204, 0x2);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x204) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcASP3(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x168, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x168) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI1(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0xF0, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0xF0) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

#if defined (__ARM_ARCH_7A__)
static void Bsp_platformTda2xxXbarConfig(void)
{
    UInt32 cookie;
    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();
    /* XBAR VIP1_IRQ1 to MPU_49 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_49, CSL_XBAR_VIP1_IRQ);

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    /* XBAR VIP2_IRQ1 to MPU_50 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_50, CSL_XBAR_VIP2_IRQ);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    /* XBAR VIP3_IRQ1 to MPU_51 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_51, CSL_XBAR_VIP3_IRQ);
#endif

    /* XBAR VPE1_IRQ1 to MPU_52 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_52, CSL_XBAR_VPE_IRQ);
    /* XBAR DISPC_IRQ at MPU_25 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_25, CSL_XBAR_DISPC_IRQ);
    /* XBAR HDMI_IRQ at MPU_101 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_101, CSL_XBAR_HDMI_IRQ);

    /* XBAR I2C1_IRQ to MPU_56
     * XBAR I2C2_IRQ to MPU_57 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_56, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_57, CSL_XBAR_I2C2_IRQ);

    /* XBAR I2C5_IRQ to MPU_60
     * XBAR I2C3_IRQ to MPU_61
     * XBAR I2C4_IRQ to MPU_62 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_60, CSL_XBAR_I2C5_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_61, CSL_XBAR_I2C3_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_62, CSL_XBAR_I2C4_IRQ);

    /* XBAR UART1_IRQ to MPU_72 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_MPU_IRQ_72, CSL_XBAR_UART1_IRQ);
    BspOsal_restoreInterrupt(cookie);

    return;
}
#endif /* #if defined (__ARM_ARCH_7A__) */

#if defined (__TI_ARM_V7M4__)

static void Bsp_platformTda2xxXbarConfig(void)
{
    UInt32 cookie;
    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();
    /* XBAR VIP1_IRQ1 to IPU1_27 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_27, CSL_XBAR_VIP1_IRQ);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
    /* XBAR VIP2_IRQ1 to IPU1_28 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_28, CSL_XBAR_VIP2_IRQ);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    /* XBAR VIP3_IRQ1 to IPU1_29 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_29, CSL_XBAR_VIP3_IRQ);
#endif
    /* XBAR VPE1_IRQ1 to IPU1_30 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_30, CSL_XBAR_VPE_IRQ);
    /* XBAR DISPC_IRQ at IPU1_23 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_23, CSL_XBAR_DISPC_IRQ);
    /* XBAR HDMI_IRQ at IPU1_26 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_26, CSL_XBAR_HDMI_IRQ);
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C5_IRQ to IPU1_42 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_41, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_42, CSL_XBAR_I2C5_IRQ);
#else
    /* XBAR I2C1_IRQ to IPU1_41
     * XBAR I2C2_IRQ to IPU1_42 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_41, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_42, CSL_XBAR_I2C2_IRQ);
#endif
    /* XBAR UART1_IRQ to IPU1_44
     * XBAR I2C3_IRQ to IPU1_43 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_43, CSL_XBAR_I2C3_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_44, CSL_XBAR_UART1_IRQ);
#if defined (TDA2XX_MC_BUILD) || defined (SOC_AM572x) || defined (SOC_AM574x)
    /* XBAR I2C5_IRQ to IPU1_48 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_48, CSL_XBAR_I2C5_IRQ);
#else
    /* XBAR I2C4_IRQ to IPU1_48 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_48, CSL_XBAR_I2C4_IRQ);
#endif
#if defined (SOC_TDA2PX) || defined (BOARD_TYPE_TDA2XX_RVP)
    /* XBAR I2C5_IRQ to IPU1_49 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_49, CSL_XBAR_I2C5_IRQ);
#endif
#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
    /* XBAR CAL_IRQ to IPU1_71 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_71, CSL_XBAR_CAL_IRQ);
#endif

#if defined (SOC_TDA2PX)
#if defined (VPS_ISS_BUILD)
        /* XBAR CSL_XBAR_ISS_IRQ_INT0 to IPU1_32 */
        BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_32, CSL_XBAR_EVE3_IRQ_OUT0);
#endif
#if defined (VPS_CAL_BUILD)
        BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_71, CSL_XBAR_CAL_IRQ);
#endif
#endif

    BspOsal_restoreInterrupt(cookie);

    return;
}
#endif /* #if defined (__TI_ARM_V7M4__) */

#if defined (_TMS320C6X)
static void Bsp_platformTda2xxXbarConfig(void)
{
    UInt32 cookie;
    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();
#if defined (SOC_AM572x) || defined (SOC_AM574x)
    /* XBAR VIP1_IRQ1 to DSP1_44 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_44, CSL_XBAR_VIP1_IRQ);
    /* XBAR VIP2_IRQ1 to DSP1_45 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_45, CSL_XBAR_VIP2_IRQ);
#if defined (SOC_AM572x)
    /* XBAR VIP3_IRQ1 to DSP1_46 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_46, CSL_XBAR_VIP3_IRQ);
#endif

    /* XBAR VPE1_IRQ1 to DSP1_47 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_47, CSL_XBAR_VPE_IRQ);
    /* XBAR DISPC_IRQ at DSP1_50 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_51, CSL_XBAR_DISPC_IRQ);
    /* XBAR HDMI_IRQ at DSP1_58 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_58, CSL_XBAR_HDMI_IRQ);

    /* XBAR I2C1_IRQ to DSP1_82
     * XBAR I2C5_IRQ to DSP1_86 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_82, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_86, CSL_XBAR_I2C5_IRQ);
    /* XBAR UART1_IRQ to DSP1_54
     * XBAR I2C3_IRQ to DSP1_53 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_87, CSL_XBAR_I2C3_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_53, CSL_XBAR_UART1_IRQ);
#elif defined (SOC_AM571x)
    /* XBAR VIP1_IRQ1 to DSP1_44 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_44, CSL_XBAR_VIP1_IRQ);
    /* XBAR VPE1_IRQ1 to DSP1_47 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_47, CSL_XBAR_VPE_IRQ);
    /* XBAR DISPC_IRQ at DSP1_51 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_51, CSL_XBAR_DISPC_IRQ);
    /* XBAR HDMI_IRQ at DSP1_58 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_58, CSL_XBAR_HDMI_IRQ);

    /* XBAR I2C1_IRQ to DSP1_82
     * XBAR I2C2_IRQ to DSP1_83 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_82, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_83, CSL_XBAR_I2C2_IRQ);

    /* XBAR UART1_IRQ to DSP1_87
     * XBAR I2C3_IRQ to DSP1_53 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_87, CSL_XBAR_I2C3_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_53, CSL_XBAR_UART1_IRQ);
#elif defined (SOC_TDA2EX)
    /* XBAR I2C1_IRQ to DSP1_82
     * XBAR I2C5_IRQ to DSP1_83 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_82, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_83, CSL_XBAR_I2C5_IRQ);
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    /* XBAR I2C1_IRQ to DSP1_82
     * XBAR I2C2_IRQ to DSP1_83 */
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_82, CSL_XBAR_I2C1_IRQ);
    BspOsal_irqXbarConnect(CSL_XBAR_INST_DSP1_IRQ_83, CSL_XBAR_I2C2_IRQ);
#endif
    BspOsal_restoreInterrupt(cookie);

    return;
}


#endif /* #if defined (_TMS320C6X) */

#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (TDA2XX_MC_BUILD) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (BOARD_TYPE_TDA2XX_RVP)
static Int32 Bsp_platformTda2xxEnableI2C5(void)
{
    HW_WR_REG32(
        SOC_IPU_CM_CORE_AON_BASE + CM_IPU_I2C5_CLKCTRL, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_IPU_CM_CORE_AON_BASE +
                        CM_IPU_I2C5_CLKCTRL) & ((UInt32) (0x00030000)))
           != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}
#endif


Int32 Bsp_platformTda2xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;
    UInt32 cookie;

    /* Convert FVID2 polarity values to DSS specific */
    if (polarity == FVID2_POL_LOW)
    {
        polarity = 1U;
    }
    else if (polarity == FVID2_POL_HIGH)
    {
        polarity = 0U;
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    if (BSP_SOK == retVal)
    {
        regVal = HW_RD_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_SMA_SW_1);
        switch (vencId)
        {
            case BSP_PLATFORM_VENC_LCD1:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_IPC, polarity);
                break;
            case BSP_PLATFORM_VENC_LCD2:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_IPC, polarity);
                break;
            case BSP_PLATFORM_VENC_LCD3:
                HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_IPC, polarity);
                break;
            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

Int32 Bsp_platformTda2xxSetLcdSyncPolarity(UInt32 vencId,
                                           UInt32 ctrlEnable,
                                           UInt32 edgePolarity)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;
    UInt32 cookie;

    /* Convert FVID2 polarity values to DSS specific */
    if (edgePolarity == FVID2_EDGE_POL_RISING)
    {
        edgePolarity = 1U;
    }
    else if (edgePolarity == FVID2_EDGE_POL_FALLING)
    {
        edgePolarity = 0U;
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    if (BSP_SOK == retVal)
    {
        regVal = HW_RD_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_SMA_SW_1);
        switch (vencId)
        {
            case BSP_PLATFORM_VENC_LCD1:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_RF, edgePolarity);
                break;
            case BSP_PLATFORM_VENC_LCD2:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH1_RF, edgePolarity);
                break;
            case BSP_PLATFORM_VENC_LCD3:
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_ON_OFF, ctrlEnable);
                HW_SET_FIELD32(
                    regVal, CTRL_CORE_SMA_SW_1_DSS_CH2_RF, edgePolarity);
                break;
            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

Int32 Bsp_platformTda2xxSetVipClkInversion(UInt32 instId, UInt32 invEnable)
{
    Int32  status = BSP_SOK;
#ifdef VPS_VIP_BUILD
    UInt32 regVal;
    UInt32 cookie;

    /* Disable interrupts when updating control module registers shared between
     * different modules. This will protect only simultaneous accesses within
     * core. If they have to be updated for simultanious accesses across
     * different cores, application is expected to call these APIs with access
     * protection.
     */
    cookie = BspOsal_disableInterrupt();

    /* Unlock MMR_1 */
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_1);

    regVal = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1);
    switch (instId)
    {
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B, invEnable);
            break;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1B, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B, invEnable);
            break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_1A, invEnable);
            break;
        case VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA):
            HW_SET_FIELD32(
                regVal, CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_2A, invEnable);
            break;
#endif
#endif
        default:
            status = BSP_EINVALID_PARAMS;
            break;
    }

    if (BSP_SOK == status)
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
            regVal);
    }
    BspOsal_restoreInterrupt(cookie);
#endif  /* #ifdef VPS_VIP_BUILD */

    return (status);
}

static Int32 Bsp_platformTda2xxEnableMcSPI2(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0xF8, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0xF8) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI3(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x100, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x100) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

static Int32 Bsp_platformTda2xxEnableMcSPI4(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + (UInt32) 0x108, PRCM_ENABLE);
    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        (UInt32) 0x108) & ((UInt32) (0x00030000))) != 0x0)
    {
        /* Do nothing - Busy wait */
    }

    return (BSP_SOK);
}

Int32 Bsp_platformTda2xxSetPinmuxRegs(UInt32 mode_index,
                                      UInt32 offset,
                                      UInt32 pupd_info)
{
    Int32  retVal = BSP_SOK;
    UInt32 muxVal;

    /* Unlock MMR_5 for pin muxing*/
    Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_5);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */

    if (offset != (UInt32) 0xffff)
    {
        muxVal = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        if (pupd_info != BSP_PLATFORM_IOPAD_CFG_DEFAULT)
        {
            muxVal &= ~(0x70000U);
            muxVal |= ((pupd_info & 0x07U) << 16U);
            HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
        }
        muxVal &= ~((UInt32) 0x0FU);
        muxVal |= (mode_index & 0x0000000FU);
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    /* Lock MMR_5 for pin muxing*/
    Bsp_platformLockRegion(BSP_PLATFORM_MMR_REG_5);

    return retVal;
}

Int32 Bsp_platformTda2xxLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

#ifdef BSP_PLATFORM_MMR_REG_LOCK_ENABLE
    switch (region)
    {
        case BSP_PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x1A1C8144U);
            break;
        case BSP_PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xFDF45530U);
            break;
        case BSP_PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0x1AE6E320U);
            break;
        case BSP_PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x2FFA927CU);
            break;
        case BSP_PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x143F832CU);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }
#endif
    return (retVal);
}

Int32 Bsp_platformTda2xxUnLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

    switch (region)
    {
        case BSP_PLATFORM_MMR_REG_1:
            HW_WR_REG32(0x4A002540U, 0x2FF1AC2BU);
            break;
        case BSP_PLATFORM_MMR_REG_2:
            HW_WR_REG32(0x4A002544U, 0xF757FDC0U);
            break;
        case BSP_PLATFORM_MMR_REG_3:
            HW_WR_REG32(0x4A002548U, 0xE2BC3A6DU);
            break;
        case BSP_PLATFORM_MMR_REG_4:
            HW_WR_REG32(0x4A00254CU, 0x1EBF131DU);
            break;
        case BSP_PLATFORM_MMR_REG_5:
            HW_WR_REG32(0x4A002550U, 0x6F361E05U);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

