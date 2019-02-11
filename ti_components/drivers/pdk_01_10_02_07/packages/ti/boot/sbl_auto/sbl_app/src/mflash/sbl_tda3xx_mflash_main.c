/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_tda3xx_mflash_main.c
 *
 *  \brief    This file contains SBL mflash main
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_rti.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_tda3xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda3xx.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/pm/pmhal.h>
#include <sbl_mflash_utils.h>
#include <sbl_mflash_uart_console.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macro to disable/enable RTI */
#define SBL_DISABLE_RTI                                ((uint32_t) TRUE)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function copies the vector table to IPU RAM.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblCopyVectorTable(void);

/**
 * \brief   This function does the SBL configuration needed before running
 *          IPU TESOC Tests.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigSoc(void);

/**
 * \brief   This function acts as a wrapper for SBL print function.
 *
 * \param   message       Message to be printed.
 *
 * \retval  None.
 *
 * \note    Below ifdef __cplusplus is added so that C++ build passes without
 *          typecasting. This is because the prototype is build as C type
 *          whereas this file is build as CPP file. Hence we get C++ build
 *          error. Also if typecasting is used, then we get MisraC error
 *          Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    sbllibInitParams_t sblInitPrms;
    /* Default initialization of SBL Lib Params */
    SBLLibInitParamsInit(&sblInitPrms);
    /* Assign SBL Params */
    sblInitPrms.printFxn       = &SblPrintFunction;
    sblInitPrms.printHexNumFxn = &SblPrintHexNumFunction;
    sblInitPrms.getcFxn        = &SblGetcFunction;
    sblInitPrms.getNumFxn      = &SblGetNumFunction;
    sblInitPrms.getHexNumFxn   = &SblGetHexNumFunction;
    sblInitPrms.putcFxn        = &SblPutcFunction;

    SBLLibInit(&sblInitPrms);
    SblConfigSoc();

    SBLMFlashRun();

    /* Resetting the clock value to 48MHz*/
    SBLLibUARTSetClock(CM_L4PER_UART3_CLKCTRL_CLKSEL_SEL_FUNC_48M_CLK);

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SblCopyVectorTable(void)
{
    uint32_t addr   = 0x8U, index = 0U;
    uint32_t length = NUM_ELEMENTS_VECTOR_TABLE;

    for (index = 2U; index < length; index++)
    {
        HW_WR_REG32(addr, vector_table[index]);
        addr = addr + 4U;
    }
}

static void SblConfigSoc(void)
{
    int32_t                retVal = STW_SOK;
    pmhalPrcmDpllConfig_t *dpllParams;
    pmhalPrcmSysClkVal_t   sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;
    uint32_t               siliconPackageType;
    volatile uint32_t      spin = 1U;
    siliconPackageType = PlatformGetSiliconPackageType();

    if (TRUE == SBL_DISABLE_RTI)
    {
        /* Configure DWWD Window size */
        RTIDwwdSetWindowSize(SOC_RTI1_BASE, RTI_DWWD_WINDOWSIZE_50_PERCENT);

        /* Service DWWD */
        RTIDwwdService(SOC_RTI1_BASE);

        /* Change RTI's action to interrupt */
        RTIDwwdSetReaction(SOC_RTI1_BASE, RTI_DWWD_REACTION_GENERATE_NMI);
    }

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Unlock the MMR registers */
    PlatformUnlockMMR();

    /* Get the Sys clock1 Frequency */
    sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* Configure DPLL CORE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_CORE,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    /* L3 clock = CORE CLK /2, L4 clock = L3 clock /2 */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L3_ICLK, (uint32_t) 2U);
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L4_ROOT_CLK, (uint32_t) 2U);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* Configure DPLL PER */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_PER,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /*Configuring the clock to 192Mz for the UART */
#ifdef BOARD_TYPE_TDA3XX_RVP
    ;
#else
    SBLLibUARTSetClock(CM_L4PER_UART3_CLKCTRL_CLKSEL_SEL_FUNC_192M_CLK);
#endif
    /* UART Initialization */

    /* Configure PRCM for UART instance */
    SBLUtilsUartPrcm(UART3_INST);

    /* Configure Pin Mux for UART instance */
    PlatformUARTSetPinMux(UART3_INST);

    /* Initialize UART Peripheral */
    /* The given configuratoins are specifies for a clock of 48MHz */
    /* If the specified is 192MHz, baud will be 4 times of specified baud*/
#ifdef BOARD_TYPE_TDA3XX_RVP
    SBLMFlashUARTConsoleConfigInit(UART3_INST,
                          (uint32_t) BAUD_RATE_921600,
                          (uint32_t) UART13x_OPER_MODE,
                          (uint32_t) UART_PARITY_NONE,
                          (uint32_t) UART_FRAME_WORD_LENGTH_8,
                          (uint32_t) UART_FRAME_NUM_STB_1
                          );
#else
    SBLMFlashUARTConsoleConfigInit(UART3_INST,
                          (uint32_t) BAUD_RATE_3000000,
                          (uint32_t) UART16x_OPER_MODE,
                          (uint32_t) UART_PARITY_NONE,
                          (uint32_t) UART_FRAME_WORD_LENGTH_8,
                          (uint32_t) UART_FRAME_NUM_STB_1
                          );
#endif

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n SBL DPLL Config Failed \n");
        SBLLibAbortBoot();
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n TDA3xx SBL Boot \n");

    if (PLATFORM_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 12X12 Silicon \n");
    }
    else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 15X15 Silicon \n");
    }

    /* Enable the Power Domains */
    SBLUtilsConfigPowerDomains();

    /* Configure DPLL DDR and DPLL GMAC */
    SBLUtilsConfigMultiOppDpll(SBLLIB_PRCM_DPLL_OPP_NOM);

    /* Enable the Clock Domains */
    SBLUtilsConfigClockDomains();

    /* Enable the Modules */
    SBLUtilsConfigModules();

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                 "\n TDA3xx SOC Init Completed \n");
}
