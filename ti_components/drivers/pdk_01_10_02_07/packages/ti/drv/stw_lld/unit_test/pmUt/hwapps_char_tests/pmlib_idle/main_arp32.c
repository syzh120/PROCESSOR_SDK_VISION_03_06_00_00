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
 *  \file  main_arp32.c
 *
 *  \brief ARP32 CPU Idle Example Application
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <arp32.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#endif
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmlib.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void CpuIdleTest(void)
{
    pmErrCode_t status;
    uint32_t    coreId = _get_cpunum();

    if (0U == coreId)
    {
        HW_WR_FIELD32(SOC_EVE1_PRM_BASE + PM_EVE1_PWRSTCTRL,
                      PM_EVE1_PWRSTCTRL_POWERSTATE,
                      0x3);
        HW_WR_FIELD32(SOC_EVE1_CM_CORE_AON_BASE + CM_EVE1_CLKSTCTRL,
                      CM_EVE1_CLKSTCTRL_CLKTRCTRL,
                      0x2);
    }
    #if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (1U == coreId)
    {
        HW_WR_FIELD32(SOC_EVE2_PRM_BASE + PM_EVE2_PWRSTCTRL,
                      PM_EVE2_PWRSTCTRL_POWERSTATE,
                      0x3);
        HW_WR_FIELD32(SOC_EVE2_CM_CORE_AON_BASE + CM_EVE2_CLKSTCTRL,
                      CM_EVE2_CLKSTCTRL_CLKTRCTRL,
                      0x2);
    }
    if (2U == coreId)
    {
        HW_WR_FIELD32(SOC_EVE3_PRM_BASE + PM_EVE3_PWRSTCTRL,
                      PM_EVE3_PWRSTCTRL_POWERSTATE,
                      0x3);
        HW_WR_FIELD32(SOC_EVE3_CM_CORE_AON_BASE + CM_EVE3_CLKSTCTRL,
                      CM_EVE3_CLKSTCTRL_CLKTRCTRL,
                      0x2);
    }
    if (3U == coreId)
    {
        HW_WR_FIELD32(SOC_EVE4_PRM_BASE + PM_EVE4_PWRSTCTRL,
                      PM_EVE4_PWRSTCTRL_POWERSTATE,
                      0x3);
        HW_WR_FIELD32(SOC_EVE4_CM_CORE_AON_BASE + CM_EVE4_CLKSTCTRL,
                      CM_EVE4_CLKSTCTRL_CLKTRCTRL,
                      0x2);
    }
    #endif

    printf("EVE executing IDLE Instruction, will go into IDLE\n");
    status = PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_ON_ACTIVE);
    if (status == PM_SUCCESS)
    {
        printf("Enter Targeted Power State successfully\n");
    }
    else
    {
        printf("Enter Targeted Power State failed\n");
    }

    printf("Test Completed!!\n");
}

int32_t main(void)
{
    printf("EVE IDLE Test\n");
    /* Function to Test CPU Idle */
    CpuIdleTest();

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
