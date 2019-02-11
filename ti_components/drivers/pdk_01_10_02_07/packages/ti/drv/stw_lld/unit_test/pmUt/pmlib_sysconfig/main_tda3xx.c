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
 *  \file   main_tda3xx.c
 *
 *  \brief  System Config implementation example.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_wd_timer.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_timer.h>
#include <ti/drv/pm/pmhal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)
#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**<
 *  \brief Function to configure always enabled for all the modules.
 *
 *  \param  None
 *
 *  \return None
 */
void alwaysEnabledConfig(void);

/**<
 *  \brief Function to configure always disabled for all the modules.
 *
 *  \param  None
 *
 *  \return None
 */
void alwaysDisabledConfig(void);

/**<
 *  \brief Function to configure auto clock gated for all the modules.
 *
 *  \param  None
 *
 *  \return None
 */
void autoCgConfig(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

pmErrCode_t finalSuccess = PM_SUCCESS;

const char *moduleState[] = {
    "PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL",
    /**< Module is functional and can be accessed */
    "PMHAL_PRCM_MODULE_SIDLESTATE_INTRANSITION",
    /**< Module is performing transition: wakeup, or sleep,or sleep abortion */
    "PMHAL_PRCM_MODULE_SIDLESTATE_INTERFACE_IDLE",
    /**< Module is in Idle mode (only interface part). It is functional if it
     *   uses separate functional clock  */
    "PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED",
    "PMHAL_PRCM_MODULE_SIDLESTATE_DETERMINED_BY_CLK_STATE"
};

const char *gClockState[] = {
    "PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED",
    /**< Enum for Gated Module CLK Activity. */
    "PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_ENABLED"
};

const char *powerstate[] = {
    "PMHAL_PRCM_PD_STATE_OFF",
    /**< Power to the domain is off. */
    "PMHAL_PRCM_PD_STATE_RETENTION",
    /**< Power to the domain is in retention mode and it will not be functional
     *   but the memory will be retained. */
    "PMHAL_PRCM_PD_STATE_ON_INACTIVE",
    /**< Power to the domain is ON INACTIVE. */
    "PMHAL_PRCM_PD_STATE_ON_ACTIVE"
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(void)
{
    uint32_t            i = 0U;
    pmhalPrcmModuleId_t idx;
    uint32_t            sTimeCnt, eTimeCnt;
    pmErrCode_t         status = PM_SUCCESS;
    PlatformUART3SetPinMux();
    UARTStdioInit();
    UARTPuts("\nPM System Config Test App", -1);
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER4, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, (uint32_t) TIMER_FREE);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE,
                       (uint32_t) TIMER_AUTORLD_NOCMP_ENABLE);
    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
    PlatformUnlockMMR();
    for (i = 0U; i < 2U; i++)
    {
        /* Function to Test System Config */
        /* Enable Modules */
        UARTPuts("\n---------------------------------------------------", -1);
        UARTPuts("\nALWAYS ENABLED CONFIGURATION\n", -1);
        UARTPuts("---------------------------------------------------\n", -1);
        alwaysEnabledConfig();
        UARTPuts("---------------------------------------------------\n", -1);
        UARTPuts("\nALWAYS DISABLED CONFIGURATION\n", -1);
        UARTPuts("---------------------------------------------------\n", -1);
        alwaysDisabledConfig();
        UARTPuts("\n---------------------------------------------------", -1);
        UARTPuts("\nAUTOCG CONFIGURATION\n", -1);
        UARTPuts("---------------------------------------------------\n", -1);
        autoCgConfig();
        UARTPuts("---------------------------------------------------\n", -1);
    }
    UARTPuts("\n---------------------------------------------------", -1);
    UARTPuts("\nGET SYSCONFIG TEST\n", -1);
    UARTPuts("---------------------------------------------------\n", -1);
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        pmlibSysConfigPowerState_t    currState;
        pmlibSysConfigDetailedState_t detailedState;
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBSysConfigGetPowerState(idx, &currState, &detailedState);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("Time = ,%d, ", eTimeCnt - sTimeCnt);
        UARTPuts((char *) pmhalNodeList_names[idx], -1);
        UARTPuts(": ", -1);
        if (PM_SUCCESS == status)
        {
            if (PMLIB_SYS_CONFIG_INVALID == currState)
            {
                UARTPuts(" PMLIB_SYS_CONFIG_INVALID\n", -1);
                if (detailedState.moduleMode !=
                    PMHAL_PRCM_MODULE_SIDLESTATE_INTRANSITION)
                {
                    finalSuccess = PM_FAIL;
                }
            }
            else if (PMLIB_SYS_CONFIG_DISABLED == currState)
            {
                UARTPuts(" PMLIB_SYS_CONFIG_DISABLED\n", -1);
            }
            else if (PMLIB_SYS_CONFIG_AUTO_CG == currState)
            {
                UARTPuts(" PMLIB_SYS_CONFIG_AUTO_CG\n", -1);
            }
            else if (PMLIB_SYS_CONFIG_ALWAYS_ENABLED == currState)
            {
                UARTPuts(" PMLIB_SYS_CONFIG_ALWAYS_ENABLED\n", -1);
            }
            UARTPuts("        Module State: ", -1);
            UARTPuts((char *) moduleState[detailedState.moduleMode], -1);
            UARTPuts("\n        Clock State: ", -1);
            UARTPuts((char *) gClockState[detailedState.clockMode], -1);
            UARTPuts("\n        Power State: ", -1);
            UARTPuts((char *) powerstate[detailedState.pdMode], -1);
            UARTPuts("\n", -1);
        }
        else
        {
            UARTPuts(" API Returned Error. Error Code = ", -1);
            UARTPutNum(status);
            UARTPuts("\n", -1);
            finalSuccess = PM_FAIL;
        }
    }
    UARTPuts("---------------------------------------------------\n", -1);
    if (PM_SUCCESS == finalSuccess)
    {
        UARTPuts("Sysconfig Test case has passed\n", -1);
    }
    else
    {
        UARTPuts("Sysconfig Test case has failed\n", -1);
    }
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

void alwaysEnabledConfig(void)
{
    pmlibSysConfigPowerStateParams_t inputTable;
    pmlibSysConfigErrReturn_t        resultReturn;
    pmhalPrcmModuleId_t idx;
    pmlibSysConfigPowerState_t       pwrSt;
    pmErrCode_t status = PM_SUCCESS;
    pwrSt = PMLIB_SYS_CONFIG_ALWAYS_ENABLED;
    uint32_t    sTimeCnt, eTimeCnt;
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        PMLIBSysConfigPowerStateParams_init(&inputTable, (uint32_t) 1U);
        inputTable.modId    = idx;
        inputTable.pwrState = pwrSt;
        if ((PMHAL_PRCM_MOD_IPU1 == idx) || (PMHAL_PRCM_MOD_TIMER4 == idx))
        {
            continue;
        }
        UARTPuts((char *) pmhalNodeList_names[idx], -1);
        UARTPuts(": ", -1);
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBSysConfigSetPowerState(&inputTable, (uint32_t) 1U,
                                               PM_TIMEOUT_INFINITE,
                                               &resultReturn);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (PM_SUCCESS == status)
        {
            UARTPuts("PASS\n", -1);
        }
        else
        {
            if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                resultReturn.failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_ALWAYS_ENABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn.failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
}

void alwaysDisabledConfig(void)
{
    pmlibSysConfigPowerStateParams_t inputTable;
    pmlibSysConfigErrReturn_t        resultReturn;
    pmhalPrcmModuleId_t idx;
    pmlibSysConfigPowerState_t       pwrSt;
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    sTimeCnt, eTimeCnt;
    pwrSt = PMLIB_SYS_CONFIG_DISABLED;
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        PMLIBSysConfigPowerStateParams_init(&inputTable, (uint32_t) 1U);
        inputTable.modId    = idx;
        inputTable.pwrState = pwrSt;
        if ((idx >= PMHAL_PRCM_MOD_DLL) && (idx <= PMHAL_PRCM_MOD_EMIF1))
        {
            continue;
        }
        else if (idx == PMHAL_PRCM_MOD_UART3)
        {
            continue;
        }
        else if ((PMHAL_PRCM_MOD_IPU1 == idx) || (PMHAL_PRCM_MOD_TIMER4 == idx))
        {
            continue;
        }
        /* TODO: PD_L3INIT is not powering down */
        else if (PMHAL_PRCM_MOD_IEEE1500_2_OCP == idx)
        {
            continue;
        }
        else if (PMHAL_PRCM_MOD_DEBUG_LOGIC == idx)
        {
            continue;
        }
        /* Can't access EVE SYSCONFIG as it is mapped in M4 bit band */
        else if (PMHAL_PRCM_MOD_EVE1 == idx)
        {
#ifndef _TMS320C6X
            continue;
#endif
        }
        UARTPuts((char *) pmhalNodeList_names[idx], -1);
        UARTPuts(": ", -1);
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBSysConfigSetPowerState(&inputTable, (uint32_t) 1U,
                                               PM_TIMEOUT_INFINITE,
                                               &resultReturn);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (PM_SUCCESS == status)
        {
            UARTPuts("PASS\n", -1);
        }
        else
        {
            if (PM_SYS_CONFIG_MODULE_CANNOT_BE_DISABLED ==
                resultReturn.failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be disabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been disabled\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_HAS_DEPENDENCIES ==
                     resultReturn.failCause)
            {
                UARTPuts("Module has dependencies\n", -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_DISABLED FAIL :Error Code Returned : ",
                    -1);
                UARTPutNum(resultReturn.failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
}

void autoCgConfig(void)
{
    pmlibSysConfigPowerStateParams_t inputTable;
    pmlibSysConfigErrReturn_t        resultReturn;
    pmhalPrcmModuleId_t idx;
    pmlibSysConfigPowerState_t       pwrSt;
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    sTimeCnt, eTimeCnt;
    pwrSt = PMLIB_SYS_CONFIG_AUTO_CG;
    for (idx = (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MIN;
         idx <= (pmhalPrcmModuleId_t) PMHAL_PRCM_MOD_MAX;
         idx = (pmhalPrcmModuleId_t) ((uint32_t) idx + 1U))
    {
        PMLIBSysConfigPowerStateParams_init(&inputTable, (uint32_t) 1U);
        inputTable.modId    = idx;
        inputTable.pwrState = pwrSt;
        if ((PMHAL_PRCM_MOD_IPU1 == idx) || (PMHAL_PRCM_MOD_TIMER4 == idx))
        {
            continue;
        }

        UARTPuts((char *) pmhalNodeList_names[idx], -1);
        UARTPuts(": ", -1);
        sTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        status   = PMLIBSysConfigSetPowerState(&inputTable, (uint32_t) 1U,
                                               PM_TIMEOUT_INFINITE,
                                               &resultReturn);
        eTimeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
        UARTprintf("Time = ,%d, ", eTimeCnt - sTimeCnt);
        if (PM_SUCCESS == status)
        {
            UARTPuts("PASS\n", -1);
        }
        else
        {
            if (PM_SYS_CONFIG_MODULE_CANNOT_BE_ENABLED ==
                resultReturn.failCause)
            {
                UARTPuts(
                    "No Valid Module Mode, Cannot be enabled from software\n",
                    -1);
                UARTPuts("Optional Clocks if any have been enabled\n", -1);
            }
            else if (PM_SYS_CONFIG_MODULE_CANNOT_BE_AUTOCG ==
                     resultReturn.failCause)
            {
                UARTPuts(
                    "Cannot be auto clock gated\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "PMLIB_SYS_CONFIG_AUTO_CG FAIL :Error Code Returned : ", -1);
                UARTPutNum(resultReturn.failCause);
                UARTPuts("\n", -1);
                finalSuccess = PM_FAIL;
            }
        }
    }
}

