/*
 *  Copyright (C) 2018 Texas Instruments Incorporated
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
 *  \file   main.c
 *
 *  \brief  pmhal example which will program fractional multiplier for DPLL ABE.
 *          Applicable only for TDA2PX.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/csl/soc.h>

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

int32_t INIT(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(void)
{
    int32_t  status;
    volatile uint32_t loopForever = 1U;
    /* Arrays given below are defined for 20 MHz */
    pmhalPrcmPllPostDivValue_t dpllAbePostDivCfgAllOpp_20[] =
    {
        {PMHAL_PRCM_DPLL_POST_DIV_M2, 1}, /* Div_m2_clkcfg */
        {PMHAL_PRCM_DPLL_POST_DIV_M3, 1}  /* Div_m3_clkcfg */
    };
    pmhalPrcmDpllConfig_t      dpllAbeCfgAllOpp_20 =
    {
        207,
        9,
        0,
        dpllAbePostDivCfgAllOpp_20,
        (sizeof (dpllAbePostDivCfgAllOpp_20) / sizeof (pmhalPrcmPllPostDivValue_t)),
        0x20000
    };

    PlatformUART1SetPinMux();
    UARTStdioInit();
    UARTPuts("\nPMHAL TDA2Px Test for DPLL ABE Frac Multiplier", -1);
    INIT();
    status = PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
                                    PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1);
    if (status == STW_SOK)
    {
        status = PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_ABE,
                                      &dpllAbeCfgAllOpp_20, PM_TIMEOUT_INFINITE);
    }
    if (status == STW_SOK)
    {
        UARTPuts("\nPLL Configuration Passed. Check the output clock at TP55\n", -1);
        UARTPuts("\nYou should get 51.875 MHz\n", -1);
        while(loopForever){;}
    }
    else
    {
        UARTPuts("\n Test case Failed \n", -1);
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

int32_t INIT(void)
{
    pmErrCode_t    retVal = PM_SUCCESS;
    /* Set the pin Mux for Clock out. Can use to check the clock out using
     * an oscilloscope. Tap TP55 on the TDA2px-evm.
     */
    retVal = (pmErrCode_t) PMHALCMMuxParentSelect(
        PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX,
        PMHAL_PRCM_DIV_PER_ABE_X1_DCLK);
    retVal = (pmErrCode_t) PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_DUMMY_MODULE1);
    if (retVal == STW_SOK)
    {
        PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_PER_ABE_X1_DCLK , 0x8);
        /* Set the pad configuration */
        PLATFORMSetPinmuxRegs(CTRL_CORE_PAD_GPMC_CLK, 0x2U);
    }
    return (int32_t) retVal;
}
