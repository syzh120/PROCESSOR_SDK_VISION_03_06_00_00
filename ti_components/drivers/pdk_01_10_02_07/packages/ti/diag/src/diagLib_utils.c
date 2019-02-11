/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_utils.c
 * \brief    This file contains the utility APIs used by diagLib sources.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_synctimer.h>
#include <diagLib_utils.h>

/* ========================================================================== */
/*                   Macros and Typedefs                                      */
/* ========================================================================== */
/** brief Counter frequency */
#define DIAGLIB_UTILS_CFG_COUNTER_FREQ       (32000U)
#define DIAGLIB_UTILS_COUNTER_MAX_COUNT      (0xFFFFFFFFU)
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint32_t DiagLibUtils_getCurTimeInMsec(void)
{
    uint32_t timerCount, curTimeMsec = 0U;

    timerCount = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    curTimeMsec = ((timerCount * 1000U) / DIAGLIB_UTILS_CFG_COUNTER_FREQ);

    return (curTimeMsec);
}

uint32_t DiagLibUtils_getElapsedTimeInMsec(uint32_t startTime)
{
    uint32_t elapsedTimeMsec = 0U;
    uint32_t startCount, elapsedCount, currVal;

    startCount = (startTime * (DIAGLIB_UTILS_CFG_COUNTER_FREQ / 1000U));

    currVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (currVal < startCount)
    {
        /* Counter overflow occured */
        elapsedCount = (DIAGLIB_UTILS_COUNTER_MAX_COUNT - startCount) + currVal + 1U;
    }
    else
    {
        elapsedCount = currVal - startCount;
    }
    elapsedTimeMsec = ((elapsedCount * 1000U) / DIAGLIB_UTILS_CFG_COUNTER_FREQ);

    return (elapsedTimeMsec);
}
