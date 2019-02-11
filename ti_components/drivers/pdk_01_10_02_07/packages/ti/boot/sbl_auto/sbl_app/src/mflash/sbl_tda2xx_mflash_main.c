/*
 *  Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_tda2xx_mflash_main.c
 *
 *  \brief    This file contains the SBL main function which calls the SOC Init
 *            and slave core boot up functions in sequence.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda2xx.h>
#include <sbl_tda2xx_priv.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <sbl_mflash_uart_console.h>
#include <sbl_mflash_utils.h>
#include <ti/csl/csl_wd_timer.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function acts as a wrapper for SBL print function.
 *
 * \param   message       Message to be printed.
 *
 * \retVal  None.
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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t                     retVal = STW_SOK;
    pmhalPrcmDpllConfig_t      *dpllParams;
    pmhalPrcmSysClkVal_t        sysClkFreq = PMHALCMGetSysClockFreqEnum();
    sbllibInitParams_t          sblInitPrms;
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

#ifdef SBL_DEV_BUILD
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_DEV;
#endif

    /* PMU Clock counter reset */
    ARM_CCNT_Enable();

    retVal = SBLUtilsConfigPowerDomains();

    /* Unlock MMR registers */
    SBLLibUnlockControlModuleMMR();

    /* Refresh the WDT to 3 mins & enable delay interrupt */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /* Configure DPLL CORE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_CORE,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    /* This selects CORE_IPU_ISS_BOOST_CLK as IPU functional clock */
    PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX, PMHAL_PRCM_DPLL_CORE);

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

    if (retVal == STW_SOK)
    {
      /* UART Initialization */
      /* Configure PRCM for UART instance */
      SBLUtilsUartPrcm(UART3_INST);

      /* Configure Pin Mux for UART instance */
      PlatformUARTSetPinMux(UART3_INST);

      /* Initialize UART Peripheral */
      /* The given configuratoins are specifies for a clock of 48MHz */
      /* If the specified is 192MHz, baud will be 4 times of specified baud*/
      retVal = SBLMFlashUARTConsoleConfigInit(UART3_INST,
                            (uint32_t) BAUD_RATE_921600,
                            (uint32_t) UART13x_OPER_MODE,
                            (uint32_t) UART_PARITY_NONE,
                            (uint32_t) UART_FRAME_WORD_LENGTH_8,
                            (uint32_t) UART_FRAME_NUM_STB_1
                            );

      /* Configure DPLLs */
      SBLUtilsConfigMultiOppDpll(SBLLIB_PRCM_DPLL_OPP_NOM);
      SBLUtilsConfigSingleOppDpll();

      /* Enable the Clock Domains */
      SBLUtilsConfigClockDomains();

      /* Enable the Modules */
      SBLUtilsConfigModules();
    }

    if (retVal == STW_SOK)
    {
      /*Start the mflash*/
      SBLMFlashRun();
    }
    return 0;
}
