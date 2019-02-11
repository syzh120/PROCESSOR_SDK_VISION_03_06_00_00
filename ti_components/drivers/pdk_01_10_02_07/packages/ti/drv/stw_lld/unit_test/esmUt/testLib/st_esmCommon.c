/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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

/**
 *  \file st_esmCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_esm.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_dcc.h>
#include <st_esm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for ESM module.
 *
 * \retval  status          configuration status.
 */
void ESMPlatformUARTInit(void);

/**
 * \brief   This API to enable the clock for ESM module.
 *
 * \retval  status          configuration status.
 */
int32_t ESMClockEnable(void);

/**
 * \brief   This API is used to introduce error.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \retvsl  status            Run status
 */
int32_t ESMTestFunc(st_ESMTestcaseParams_t *testParams);

void cntrl_core_pad_configuration1(uint32_t            baseAdd,
                                   const pad_config_t *pad_config);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void ESMPlatformUARTInit(void)
{
    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
}

int32_t ESMClockEnable(void)
{
    int32_t status = STW_EFAIL, configStatus;

    /* Enable ESM module */
    configStatus = PMHALModuleModeSet(PMHAL_PRCM_MOD_ESM,
                                      PMHAL_PRCM_MODULE_MODE_ENABLED,
                                      PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS == configStatus)
    {
        status = STW_SOK;
    }
    return status;
}

int32_t ESMTestFunc(st_ESMTestcaseParams_t *testParams)
{
    int32_t           status = STW_SOK;
    uint32_t          timeStamp1, timeStamp2;

    switch (testParams->testcaseId)
    {
        case 1:
            UARTprintf("Generating EVE reset....\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            break;
        case 2:
            UARTprintf("Generating EVE reset....\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            break;
        case 4:
            ESMResetErrPin(testParams->esmConfigParams.esmModule);
            UARTprintf("Generating EVE reset....\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while (1U ==
                   ESMGetErrPinStatus(testParams->esmConfigParams.esmModule))
            {}
            timeStamp1 = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
            while (0U ==
                   ESMGetErrPinStatus(testParams->esmConfigParams.esmModule))
            {}
            timeStamp2 = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
            UARTprintf("ESM ERROR Pin was Low for %d cycles of 32kHz clock.\n",
                   (timeStamp2 - timeStamp1));
            break;
        case 5:
            UARTprintf("esm_error pin is HIGH.\n");
            UARTprintf("Generating EVE reset....\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while (1U ==
                   ESMGetErrPinStatus(testParams->esmConfigParams.esmModule))
            {}
            UARTprintf("esm_error pin is LOW.\n");
            while ((0U ==
                    ESMGetErrPinStatus(testParams->esmConfigParams.esmModule))
                   &&
                   (0U !=
                    ESMGetCurrErrPinLowTimeCnt(testParams->esmConfigParams.
                                               esmModule)))
            {}
            UARTprintf("Generating EVE reset... Again...\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while ((0U ==
                    ESMGetCurrErrPinLowTimeCnt(testParams->esmConfigParams.
                                               esmModule)))
            {}
            if (!(0U <
                  ESMGetCurrErrPinLowTimeCnt(testParams->esmConfigParams.
                                             esmModule)))
            {
                status = STW_EFAIL;
            }
            else
            {
                UARTprintf("esm_error pin Low Time Counter reloaded.\n");
                UARTprintf("esm_error pin is LOW.\n");
                ESMResetErrPin(testParams->esmConfigParams.esmModule);
                ESMClearIntrStatus(testParams->esmConfigParams.esmModule,
                                   testParams->esmConfigParams.esmChannels[1U][
                                       0U]);
                while (0U ==
                       ESMGetErrPinStatus(testParams->esmConfigParams.esmModule))
                {}
                UARTprintf("esm_error pin is HIGH.\n");
            }
            break;
        case 6:
            UARTprintf("Generating EVE reset... or generate DCC 4/5 Error interrupt.\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            break;
        case 7:
            UARTprintf("Generating EVE reset... or generate DCC 4/5 Error interrupt.\n");
            /* Reset EVE */
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            while(0x0U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x1U);
            while(0x1U != (HW_RD_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL) & 0x1U));
            HW_WR_REG32(SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL, 0x0U);
            break;
        default:

            break;
    }
    return status;
}

void cntrl_core_pad_configuration1(uint32_t            baseAdd,
                                   const pad_config_t *pad_config)
{
    uint32_t reg_val;

    PlatformUnlockMMR();
    reg_val = HW_RD_REG32(baseAdd + (pad_config->pin_num));

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)

    if (pad_config->pullud_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_MASK;
        reg_val |= (uint32_t) pad_config->pullud_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLUDENABLE_SHIFT;
    }
    if (pad_config->pull_typeselect != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_MASK;
        reg_val |= (uint32_t) pad_config->pull_typeselect <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_PULLTYPESELECT_SHIFT;
    }
    if (pad_config->input_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_MASK;
        reg_val |= (uint32_t) pad_config->input_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_INPUTENABLE_SHIFT;
    }
    if (pad_config->slewcontrol != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_MASK;
        reg_val |= (uint32_t) pad_config->slewcontrol <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_SLEWCONTROL_SHIFT;
    }
    if (pad_config->wakeup_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_MASK;
        reg_val |= (uint32_t) pad_config->wakeup_enable <<
                   CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_WAKEUPENABLE_SHIFT;
    }
#elif defined (SOC_TDA3XX)

    if (pad_config->pullud_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_MASK;
        reg_val |= (uint32_t) pad_config->pullud_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_PULLUDENABLE_SHIFT;
    }
    if (pad_config->pull_typeselect != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_MASK;
        reg_val |= (uint32_t) pad_config->pull_typeselect <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_PULLTYPESELECT_SHIFT;
    }
    if (pad_config->input_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_MASK;
        reg_val |= (uint32_t) pad_config->input_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_INPUTENABLE_SHIFT;
    }
    if (pad_config->slewcontrol != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_MASK;
        reg_val |= (uint32_t) pad_config->slewcontrol <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_SLEWCONTROL_SHIFT;
    }
/* Todo : Please check before use - Why
 * CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_MASK is undefined for TDA3XX */
#if 0
    if (pad_config->wakeup_enable != 0xFF)
    {
        reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_MASK;
        reg_val |= (uint32_t) pad_config->wakeup_enable <<
                   CTRL_CORE_PAD_IO_GPMC_AD0_WAKEUPENABLE_SHIFT;
    }
#endif
#endif
    HW_WR_REG32(baseAdd + (pad_config->pin_num), reg_val);

    /* IO input glitches may occur when switching pull type and
     * mux mode simultaneously. To avoid such glitches it is expected
     * two separate register writes to transition to the desired state */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    reg_val &= ~CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_MASK;
    reg_val |= (uint32_t) pad_config->muxmode <<
               CTRL_CORE_PAD_GPMC_AD0_GPMC_AD0_MUXMODE_SHIFT;
#elif defined (SOC_TDA3XX)
    reg_val &= ~CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_MASK;

    reg_val |= (uint32_t) pad_config->muxmode <<
               CTRL_CORE_PAD_IO_GPMC_AD0_MUXMODE_SHIFT;
#endif

    HW_WR_REG32(baseAdd + (pad_config->pin_num), reg_val);
    PlatformLockMMR();
}
