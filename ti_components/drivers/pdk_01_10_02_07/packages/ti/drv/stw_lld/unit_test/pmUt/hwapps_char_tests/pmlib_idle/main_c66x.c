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
 *  \file main_c66x.c
 *
 *  \brief DSP CPU Idle Example Application for DSP Idle
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
#include <c6x.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>

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
    uint32_t    coreId = DNUM;

    if (0U == coreId)
    {
        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP1, PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP1,
                              PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                              PM_TIMEOUT_NOWAIT);
    }
#if !defined (SOC_TDA2EX)
    else
    {
        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP2, PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                           PM_TIMEOUT_NOWAIT);
        PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP2,
                              PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                              PM_TIMEOUT_NOWAIT);
    }
#endif
    printf("Enter Idle. Please measure power...\n");

    status = PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_ON_INACTIVE);

    if (status == PM_SUCCESS)
    {
        printf("Enter Targeted Power State successfully\n");
    }
    else
    {
        printf("Enter Targeted Power State failed\n");
    }
}

int32_t main(void)
{
    printf("PM DSP CPUIdle Test App\n");

    /* Function to Test CPU Idle */
    CpuIdleTest();

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

