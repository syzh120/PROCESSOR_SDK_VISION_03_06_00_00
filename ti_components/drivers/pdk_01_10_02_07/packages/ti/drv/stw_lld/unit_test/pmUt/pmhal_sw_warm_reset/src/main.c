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
 * \brief   PMHAL Reset Test for global software warm reset.
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

int32_t WARM_CheckNoWarmRst(void);
int32_t WARM_CheckWarmRst(int rst_idx);
int32_t WARM_ClearAllRst(void);
int32_t WARM_AssertSW_WARMRst(void);

int32_t WARM_AssertWarmRst();

int32_t WARM_GetWarmRstIndex(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    int32_t  retVal;
    uint32_t rGlbStatusMask, rst_idx;
    int32_t  error_cnt;
    /* Do Pad Config for UART */
#if !defined (SOC_TDA3XX)
    PlatformUART1SetPinMux();
#else
    PlatformUART3SetPinMux();
#endif

    /* Initialize the UART Instance */
    UARTStdioInit();
    UARTPuts("\n Global Warm reset Application Running on A15", -1);
    retVal = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST,
                                       &rGlbStatusMask);

    if ((pmErrCode_t) retVal == PM_SUCCESS)
    {
        if (0U == rGlbStatusMask)
        {
            UARTPuts("\n Power on reset detected", -1);
            if (WARM_CheckNoWarmRst() != PM_SUCCESS)
            {
                retVal = PM_BADARGS;
            }
            HW_WR_REG32(0x88888888, 0x000000);
            rst_idx = HW_RD_REG32(0x88888888);
        }
        else
        {
            rst_idx = HW_RD_REG32(0x88888888);
            UARTPuts("\n Global warm reset detected", -1);
            error_cnt = 0;
            if (WARM_CheckWarmRst((rst_idx - 1)) != PM_SUCCESS)
            {
                retVal = PM_BADARGS;
                error_cnt++;
                UARTPuts("\n ERROR", -1);
            }
            else
            {
                UARTPuts("\n OK", -1);
            }
        }
    }
    retVal |= PMHALResetClearGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
    retVal |= PMHALResetClearGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST);
    if ((pmErrCode_t) retVal == PM_SUCCESS)
    {
        if (rst_idx == 0)
        {
            UARTPuts("\n Loop starts", -1);
        }

        while (rst_idx < 3)
        {
            HW_WR_REG32(0x88888888, (rst_idx + 1));
            retVal = WARM_AssertSW_WARMRst();
        }
        UARTPuts("\n Test Case Done!!", -1);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

int32_t WARM_CheckNoWarmRst(void)
{
    int32_t     prcmReturn;
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    rGlbStatusMask;

    prcmReturn = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST,
                                           &rGlbStatusMask);
    if ((pmErrCode_t) prcmReturn == PM_SUCCESS)
    {
        if (rGlbStatusMask)
        {
            UARTPuts("\r\n[Error] Unexpected reset status is set", -1);
            retVal = PM_BADARGS;
        }
    }
    else
    {
        retVal = (pmErrCode_t) prcmReturn;
    }
    return (int32_t) retVal;
}

int32_t WARM_ClearAllRst(void)
{
    int32_t     prcmReturn;
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t    rGlbStatusMask;

    prcmReturn = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST,
                                           &rGlbStatusMask);

    prcmReturn = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST,
                                           &rGlbStatusMask);
    if ((pmErrCode_t) prcmReturn == PM_SUCCESS)
    {
        if (rGlbStatusMask)
        {
            UARTPuts("\r\n[Error] Unble to clear reset status ", -1);
            retVal = PM_BADARGS;
        }
    }

    return (int32_t) retVal;
}

int32_t WARM_AssertSW_WARMRst(void)
{
    pmErrCode_t retVal;
    int32_t     prcmReturn;
    UARTPuts("\r\nAsserting warm reset ", -1);

    prcmReturn = PMHALResetAssertGlobal(
        PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST);
    if ((pmErrCode_t) prcmReturn == PM_SUCCESS)
    {
        while (1) ;  /* wait reset assertion */
    }
    else
    {
        UARTPuts(" \n[ERROR] PMHALResetAssertGlobal() returned error \n", -1);
        retVal = PM_BADARGS;
    }
    return (int32_t) retVal;
}

int32_t WARM_CheckWarmRst(int rst_idx)
{
    pmErrCode_t retVal = PM_SUCCESS;
    int32_t     prcmReturn, i;
    uint32_t    rGlbStatusMask;
    prcmReturn = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST,
                                           &rGlbStatusMask);
    if (prcmReturn == PM_SUCCESS)
    {
        if (rGlbStatusMask)
        {
            UARTPuts(
                " \r\n[Error] global cold reset status is set when generating global warm reset",
                -1);
            retVal = PM_BADARGS;
        }
    }

    for (i = 0; i < 2; i++)
    {
        prcmReturn =
            PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST,
                                      &rGlbStatusMask);
        if (prcmReturn == PM_SUCCESS)
        {
            if (i == rst_idx)
            {
                if (!rGlbStatusMask)
                {
                    UARTPuts(" \r\n[Error] reset status %s is not set", -1);
                    retVal = PM_BADARGS;
                }
                else
                {
                    UARTPuts("\r\n[OK] Warm reset status  is set", -1);
                }
            }
        }
    }

    return retVal;
}

