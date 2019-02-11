/*
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     dcc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of DCC.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dcc.h>
#include <ti/csl/csl_dcc.h>

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
int32_t DCCSetConfig(uint32_t baseAddr, const dccConfigParams_t *configParams)
{
    int32_t status = STW_EFAIL;
    if ((DCC_SRC0_COUNT_MAX >= configParams->seedSrc0) &&
        (DCC_SRC0_VALID_MAX >= configParams->seedValid0) &&
        (DCC_SRC1_COUNT_MAX >= configParams->seedSrc1))
    {
        /* Configure DCC mode of operation */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_SINGLESHOT,
                      configParams->mode);
        /* Select clock source for COUNT0 */
        HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC0, DCC_DCCCLKSRC0_CLKSRC0,
                      configParams->clkSrc0);

        if(configParams->alternateClkSrc1 == (uint32_t)TRUE)
        {
            /* Enable alternate clock source selection for COUNT1 */
            HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC1, DCC_DCCCLKSRC1_KEY,
                          DCC_DCCCLKSRC1_KEY_DISABLE);
        }
        else
        {
            /* Select clock source for COUNT1*/
            HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC1, DCC_DCCCLKSRC1_CLKSRC,
                          (configParams->clkSrc1 % 16));
            /* Enable clock source selection for COUNT1 */
            HW_WR_FIELD32(baseAddr + DCC_DCCCLKSRC1, DCC_DCCCLKSRC1_KEY,
                          DCC_DCCCLKSRC1_KEY_ENABLE);
        }
        /* Configure COUNT0 preload/seed value */
        HW_WR_FIELD32(baseAddr + DCC_DCCCNTSEED0, DCC_DCCCNT0_COUNT0,
                      configParams->seedSrc0);
        if(configParams->seedValid0 < 4U)
        {
            /* Configure VALID0 preload/seed value */
            HW_WR_FIELD32(baseAddr + DCC_DCCVALIDSEED0, DCC_DCCVALID0_VALID0,
                          4U);
        }
        else
        {
            /* Configure VALID0 preload/seed value */
            HW_WR_FIELD32(baseAddr + DCC_DCCVALIDSEED0, DCC_DCCVALID0_VALID0,
                          configParams->seedValid0);
        }
        /* Configure COUNT1 preload/seed value */
        HW_WR_FIELD32(baseAddr + DCC_DCCCNTSEED1, DCC_DCCCNT1_COUNT1,
                      configParams->seedSrc1);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

void DCCEnable(uint32_t baseAddr, uint32_t enable)
{
    if ((uint32_t) TRUE == enable)
    {
        /* Enable DCC */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_ENABLE);
    }
    else
    {
        /* Disable DCC */
        HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DCCENA,
                      DCC_DCCGCTRL_DCCENA_DISABLE);
    }
}

int32_t DCCEnableIntr(uint32_t baseAddr, uint32_t intrType)
{
    int32_t status = STW_EFAIL;
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            /* Enable ERROR interrupt */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                          DCC_DCCGCTRL_ERRENA_ENABLE);
            status = STW_SOK;
            break;
        case DCC_INTERRUPTS_DONE:
            /* Enable DONE interrupt(only for single shot mode) */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                          DCC_DCCGCTRL_DONEENA_ENABLE);
            status = STW_SOK;
            break;
        default:
            status = STW_EBADARGS;
            break;
    }
    return status;
}

int32_t DCCDisableIntr(uint32_t baseAddr, uint32_t intrType)
{
    int32_t status = STW_EFAIL;
    switch (intrType)
    {
        case DCC_INTERRUPTS_ERROR:
            /* Disable ERROR interrupt */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_ERRENA,
                          DCC_DCCGCTRL_ERRENA_DISABLE);
            status = STW_SOK;
            break;
        case DCC_INTERRUPTS_DONE:
            /* Disable DONE interrupt(only for single shot mode) */
            HW_WR_FIELD32(baseAddr + DCC_DCCGCTRL, DCC_DCCGCTRL_DONEENA,
                          DCC_DCCGCTRL_DONEENA_DISABLE);
            status = STW_SOK;
            break;
        default:
            status = STW_EBADARGS;
            break;
    }
    return status;
}

uint32_t DCCGetIntrStatus(uint32_t baseAddr)
{
    /* Read and return DCC status register */
    return (HW_RD_REG32(baseAddr + DCC_DCCSTAT));
}

void DCCClearIntrStatus(uint32_t baseAddr, uint32_t intrMask)
{
    /* Clear status of given interrupt */
    HW_WR_REG32(baseAddr + DCC_DCCSTAT, ((uint32_t) 0x1U << intrMask));
}

void DCCGetConfig(uint32_t baseAddr, dccConfigParams_t *configParams)
{
    /* Get the configured mode of operation for DCC module */
    configParams->mode = HW_RD_FIELD32(baseAddr + DCC_DCCGCTRL,
                                       DCC_DCCGCTRL_SINGLESHOT);
    /* Get the clock source for COUNT0 */
    configParams->clkSrc0 = HW_RD_FIELD32(baseAddr + DCC_DCCCLKSRC0,
                                          DCC_DCCCLKSRC0_CLKSRC0);
    /* Get the clock source for COUNT1 */
    configParams->clkSrc1 = HW_RD_FIELD32(baseAddr + DCC_DCCCLKSRC1,
                                          DCC_DCCCLKSRC1_CLKSRC);
    /* Get the current value of COUNT0 */
    configParams->seedSrc0 = HW_RD_FIELD32(baseAddr + DCC_DCCCNTSEED0,
                                           DCC_DCCCNT0_COUNT0);
    /* Get the current value of VALID0 */
    configParams->seedValid0 = HW_RD_FIELD32(baseAddr + DCC_DCCVALIDSEED0,
                                             DCC_DCCVALID0_VALID0);
    /* Get the current value of COUNT1 */
    configParams->seedSrc1 = HW_RD_FIELD32(baseAddr + DCC_DCCCNTSEED1,
                                           DCC_DCCCNT1_COUNT1);
}

void DCCGetRevisionId(uint32_t baseAddr, dccRevisionId_t *revId)
{
    /* Get the scheme */
    revId->scheme = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_SCHEME);
    /* Get the Functional release number*/
    revId->func = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_FUNC);
    /* Get the Design Release Number */
    revId->rtlReleaseNum = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_RTL);
    /* Get the Major Revision Number */
    revId->major = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_MAJOR);
    /* Get a special version of the module */
    revId->custom = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_CUSTOM);
    /* Get the Minor revision number */
    revId->minor = HW_RD_FIELD32(baseAddr + DCC_DCCREV, DCC_DCCREV_MINOR);
}

