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
 * \file main.c
 *
 * \brief   PMHAL Global Cold Reset test.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/src/pmhal/prcm/common/hw_pmhal_data.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PMHAL_PRCM_MOD_MIN (PMHAL_PRCM_MOD_LOWER_BOUND + 1U)

#define PMHAL_PRCM_MOD_MAX (PMHAL_PRCM_MOD_COUNT - 1U)

#define GET_MODULE_ID(x) (x - PMHAL_PRCM_MOD_MIN)

#define SAR_RAM_LOC     0x4AE26000
#define PASS_STATUS     0x00800000
#define FAIL_STATUS     0x00000000
#define OVERNIGHT_RUN   0x00400000

#define LOOP_MAX_OVERNIGHT  0xffffffff
#define LOOP_MAX_REGRESSION 10

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
#if !defined (SOC_TDA3XX)
    uint32_t rstCount;
#endif
    int32_t  retVal;
    uint32_t rGlbStatusMask;
    pmhalPrcmGlobalResetGroupId_t glbResetId;
    /* Do Pad Config for UART */
#if !defined (SOC_TDA3XX)
    PlatformUART1SetPinMux();
#else
    PlatformUART3SetPinMux();
#endif

    /* Initialize the UART Instance */
    UARTStdioInit();
    UARTPuts("\n Global Cold reset Application Running on A15", -1);

    retVal = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST,
                                       &rGlbStatusMask);

    if ((pmErrCode_t) retVal == PM_SUCCESS)
    {
        if (rGlbStatusMask)
        {
            UARTPuts("\n Global reset happens", -1);
        }
        else
        {
            UARTPuts("\n Reset bit not set", -1);
        }
    }
    else
    {
        UARTPuts("\n PMHALResetGetGlobalStatus() returned Error", -1);
    }

    UARTPuts("\nClearing all reset status bits...  ", -1);

    for (glbResetId = PMHAL_PRCM_GLB_RG_MIN;
         glbResetId <= PMHAL_PRCM_GLB_RG_MAX;
         glbResetId = (pmhalPrcmGlobalResetGroupId_t) ((int32_t) glbResetId + 1))
    {
        retVal = PMHALResetClearGlobalStatus(glbResetId);
        if ((pmErrCode_t) retVal == PM_SUCCESS)
        {}
        else
        {
            UARTPuts("\n Unable to clear reset %d", glbResetId);
        }
    }
#if !defined (SOC_TDA3XX)
    rstCount = HW_RD_REG32(SAR_RAM_LOC);

    if ((rstCount & 0xFF000000) != 0xED000000)
    {
        /* First reset */

        rstCount = 0xED000000 |
                   ((pmErrCode_t) retVal ==
                    PM_SUCCESS ? PASS_STATUS : FAIL_STATUS);
        HW_WR_REG32(SAR_RAM_LOC, rstCount);
    }
    else
    {
        /* Subsequent reset */

        if ((rstCount & 0x00800000) == FAIL_STATUS)
        {
            UARTPuts(
                "\r\nSetting test status to RET_FAIL (previous reset failed)\r\n ",
                -1);
            retVal = PM_BADARGS;
        }

        rstCount = 0xED000000 |
                   ((pmErrCode_t) retVal ==
                    PM_SUCCESS ? PASS_STATUS : FAIL_STATUS) |
                   (rstCount & OVERNIGHT_RUN) |
                   ((rstCount + 1) & 0x003FFFFF);
        HW_WR_REG32(SAR_RAM_LOC, rstCount);

        UARTprintf("Reset count = %d\r\n ", rstCount & 0x003FFFFF);
    }
#endif
    UARTPuts("\r\nAsserting Global Cold SW Reset\r\n ", -1);
    retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
    if ((pmErrCode_t) retVal == PM_SUCCESS)
    {
        while (1) ;  /* wait reset assertion */
    }
    else
    {
        UARTPuts(" \r\n[HAL ERROR] prcm_assert_reset() returned %d \r\n",
                 retVal);
    }

    /* clear rstCount */
    HW_WR_REG32(SAR_RAM_LOC, 0);

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

