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
 *  \file     rti.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of RTI.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/cslr_rti.h>
#include <ti/csl/csl_rti.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define RTI_DWWDPRLD_MULTIPLIER_SHIFT    (13U)
#define RTI_RTIWDKEY_WDKEY_INVALID_WRITE (0x4444U)

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
int32_t RTIDwwdWindowConfig(uint32_t baseAddr,
                            uint32_t dwwdReaction,
                            uint32_t dwwdPreloadVal,
                            uint32_t dwwdWindowSize)
{
    int32_t configStatus = STW_EFAIL;

    /* Configure window in which watch-dog should be serviced */
    RTIDwwdSetWindowSize(baseAddr, dwwdWindowSize);
    /* Initialize DWD Expiration Period */
    configStatus = RTIDwwdSetPreload(baseAddr, dwwdPreloadVal);
    /* Configure Digital Windowed Watchdog Reaction */
    RTIDwwdSetReaction(baseAddr, dwwdReaction);
    return configStatus;
}

void RTIDwwdCounterEnable(uint32_t baseAddr)
{
    /* Enable DWWD by writing pre-defined value '0xA98559DA' to RTIDWDCTRL    */
    HW_WR_REG32(baseAddr + RTI_RTIDWDCTRL,
                RTI_RTIDWDCTRL_DWDCTRL_ENABLE);
}

uint32_t RTIDwwdIsCounterEnabled(uint32_t baseAddr)
{
    uint32_t retVal;

    /* Enable DWWD by writing pre-defined value '0xA98559DA' to RTIDWDCTRL    */
    if(RTI_RTIDWDCTRL_DWDCTRL_ENABLE == HW_RD_REG32(baseAddr + RTI_RTIDWDCTRL))
    {
        retVal = (uint32_t)TRUE;
    }
    else
    {
        retVal = (uint32_t)FALSE;
    }

    return retVal;
}

void RTIDwwdService(uint32_t baseAddr)
{
    HW_WR_FIELD32(baseAddr + RTI_RTIWDKEY,
                  RTI_RTIWDKEY_WDKEY,
                  RTI_RTIWDKEY_WDKEY_FIRST_WRITE);
    HW_WR_FIELD32(baseAddr + RTI_RTIWDKEY,
                  RTI_RTIWDKEY_WDKEY,
                  RTI_RTIWDKEY_WDKEY_SECOND_WRITE);
}

rtiDwwdResetStatus_t RTIDwwdGetLastResetStatus(uint32_t baseAddr)
{
    rtiDwwdResetStatus_t resetStatus;

    if (1U == HW_RD_FIELD32(baseAddr + RTI_RTIWDSTATUS,
                            RTI_RTIWDSTATUS_DWDST))
    {
        resetStatus = RTI_DWWD_RESET_STATUS_GENERATED;
    }
    else
    {
        resetStatus = RTI_DWWD_RESET_STATUS_NOT_GENERATED;
    }
    return resetStatus;
}

int32_t RTIDwwdSetPreload(uint32_t baseAddr, uint32_t dwwdPreloadVal)
{
    int32_t preloadConfigStatus = STW_EFAIL;

    dwwdPreloadVal = (dwwdPreloadVal >>
                      ((uint32_t) RTI_DWWDPRLD_MULTIPLIER_SHIFT));
    if ((uint32_t) RTI_RTIDWDPRLD_DWDPRLD_MAX > dwwdPreloadVal)
    {
        /* Initialize DWD Expiration Period */
        HW_WR_FIELD32(baseAddr + RTI_RTIDWDPRLD,
                      RTI_RTIDWDPRLD_DWDPRLD,
                      dwwdPreloadVal);
        preloadConfigStatus = STW_SOK;
    }
    else
    {
        preloadConfigStatus = STW_EFAIL;
    }
    return preloadConfigStatus;
}

void RTIDwwdSetReaction(uint32_t baseAddr, uint32_t dwwdReaction)
{
    /* Configuring Digital Windowed Watchdog Reaction */
    HW_WR_FIELD32(baseAddr + RTI_RTIDWWDRXNCTRL,
                  RTI_RTIDWWDRXNCTRL_DWWDRXN,
                  dwwdReaction);
}

void RTIDwwdSetWindowSize(uint32_t baseAddr, uint32_t dwwdWindowSize)
{
    /* Configure window in which watch-dog should be serviced */
    HW_WR_FIELD32(baseAddr + RTI_RTIDWWDSIZECTRL,
                  RTI_RTIDWWDSIZECTRL_DWWDSIZE,
                  dwwdWindowSize);
}

uint32_t RTIDwwdIsClosedWindow(uint32_t baseAddr)
{
    uint32_t closedWindowstatus, currentDownCounter, windowSizeShift;
    uint32_t windowStartTime, timeOutValue, windowSize;

    closedWindowstatus = (uint32_t) FALSE;
    windowSizeShift    = (uint32_t)
                         RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
    /* Get configured Window Size */
    windowSize = RTIDwwdGetWindowSize(baseAddr);
    switch (windowSize)
    {
        case RTI_DWWD_WINDOWSIZE_100_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_50_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_25_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_12_5_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_6_25_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_3_125_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT_SHIFT;
            break;
        default:
            break;
    }
    timeOutValue    = RTIDwwdGetTimeOut(baseAddr);
    windowStartTime = (timeOutValue /
                       (uint32_t) ((uint32_t) 0x1U << windowSizeShift));
    /* Get current down counter */
    currentDownCounter = HW_RD_REG32(baseAddr + RTI_RTIDWDCNTR);
    if (currentDownCounter > windowStartTime)
    {
        closedWindowstatus = (uint32_t) TRUE;
    }
    else
    {
        closedWindowstatus = (uint32_t) FALSE;
    }
    return closedWindowstatus;
}

void RTIDwwdGenerateSysReset(uint32_t baseAddr)
{
    /* Generate system reset by writing value other than pre-defined
     *  second write value '0x0000A35C' to RTI_RTIWDKEY */
    HW_WR_FIELD32(baseAddr + RTI_RTIWDKEY,
                  RTI_RTIWDKEY_WDKEY,
                  RTI_RTIWDKEY_WDKEY_FIRST_WRITE);
    HW_WR_FIELD32(baseAddr + RTI_RTIWDKEY,
                  RTI_RTIWDKEY_WDKEY,
                  RTI_RTIWDKEY_WDKEY_INVALID_WRITE);
}

uint32_t RTIDwwdGetStatus(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + RTI_RTIWDSTATUS);
}

void RTIDwwdClearStatus(uint32_t baseAddr, uint32_t status)
{
    HW_WR_REG32(baseAddr + RTI_RTIWDSTATUS, status);
}

uint32_t RTIDwwdGetCurrentDownCounter(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + RTI_RTIDWDCNTR);
}

uint32_t RTIIsDwwdKeySequenceCorrect(uint32_t baseAddr)
{
    uint32_t keySequencestatus;

    if (1U == (HW_RD_FIELD32(baseAddr + RTI_RTIWDSTATUS,
                             RTI_RTIWDSTATUS_KEYST)))
    {
        keySequencestatus = (uint32_t) RTI_RTIWDSTATUS_KEYST_INCORRECT_KEY;
    }
    else
    {
        keySequencestatus = (uint32_t) RTI_RTIWDSTATUS_KEYST_CORRECT_KEY;
    }
    return (keySequencestatus);
}

uint32_t RTIDwwdGetPreload(uint32_t baseAddr)
{
    uint32_t preloadVal;

    preloadVal = HW_RD_FIELD32(baseAddr + RTI_RTIDWDPRLD,
                               RTI_RTIDWDPRLD_DWDPRLD);
    return preloadVal;
}

uint32_t RTIDwwdGetWindowSize(uint32_t baseAddr)
{
    uint32_t windowSize;

    /* Get configured Window Size */
    windowSize = HW_RD_REG32(baseAddr + RTI_RTIDWWDSIZECTRL);

    return windowSize;
}

uint32_t RTIDwwdGetTimeOut(uint32_t baseAddr)
{
    uint32_t timeOutValue;

    timeOutValue = ((HW_RD_REG32(baseAddr + RTI_RTIDWDPRLD)
                     << RTI_DWWDPRLD_MULTIPLIER_SHIFT) |
                    RTI_DWD_MIN_PRELOAD_VAL);

    return timeOutValue;
}

uint32_t RTIDwwdGetTicksToOpenWindow(uint32_t baseAddr)
{
    uint32_t currentDownCounter, windowSizeShift, timeOutValue;
    uint32_t windowStartTime, clkTicks, windowSize;

    clkTicks        = 0U;
    windowSizeShift = (uint32_t)
                      RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
    /* Get configured Window Size */
    windowSize = HW_RD_REG32(baseAddr + RTI_RTIDWWDSIZECTRL);
    switch (windowSize)
    {
        case RTI_DWWD_WINDOWSIZE_100_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_100_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_50_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_50_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_25_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_25_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_12_5_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_12_5_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_6_25_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_6_25_PERCENT_SHIFT;
            break;
        case RTI_DWWD_WINDOWSIZE_3_125_PERCENT:
            windowSizeShift = (uint32_t)
                              RTI_RTIDWWDSIZECTRL_DWWDSIZE_3_125_PERCENT_SHIFT;
            break;
        default:
            break;
    }
    timeOutValue    = RTIDwwdGetTimeOut(baseAddr);
    windowStartTime = (timeOutValue /
                       (uint32_t) ((uint32_t) 0x1U << windowSizeShift));
    /* Get current down counter */
    currentDownCounter = RTIDwwdGetCurrentDownCounter(baseAddr);
    if (currentDownCounter > windowStartTime)
    {
        clkTicks = (currentDownCounter - windowStartTime);
    }

    return clkTicks;
}

uint32_t RTIDwwdGetReaction(uint32_t baseAddr)
{
    uint32_t dwwdReaction;

    /* Get Windowed Watchdog Reaction */
    dwwdReaction = HW_RD_FIELD32(baseAddr + RTI_RTIDWWDRXNCTRL,
                                 RTI_RTIDWWDRXNCTRL_DWWDRXN);

    return dwwdReaction;
}
