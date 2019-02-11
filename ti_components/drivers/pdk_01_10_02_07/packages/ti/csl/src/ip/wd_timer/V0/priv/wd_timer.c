/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   wd_timer.c
 *
 *  \brief  WATCHDOG TIMER APIs.
 *
 *   This file contains the device abstraction layer APIs for Watchdog Timer.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_wd_timer.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define WD_TIMER_DISABLE_SEQ1           ((uint32_t) 0x0000AAAAU)
#define WD_TIMER_DISABLE_SEQ2           ((uint32_t) 0x00005555U)
#define WD_TIMER_ENABLE_SEQ1            ((uint32_t) 0x0000BBBBU)
#define WD_TIMER_ENABLE_SEQ2            ((uint32_t) 0x00004444U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void WDTIMEREnable(uint32_t baseAddr)
{
    /* Write the first value of the watchdog timer enabling sequence */
    HW_WR_REG32(baseAddr + WD_TIMER_WSPR, WD_TIMER_ENABLE_SEQ1);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /* Write the second value of the watchdog timer enabling sequence */
    HW_WR_REG32(baseAddr + WD_TIMER_WSPR, WD_TIMER_ENABLE_SEQ2);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

void WDTIMERDisable(uint32_t baseAddr)
{
    /* Write the first value of the watchdog timer disabling sequence */
    HW_WR_REG32(baseAddr + WD_TIMER_WSPR, WD_TIMER_DISABLE_SEQ1);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /* Write the second value of the watchdog timer disabling sequence */
    HW_WR_REG32(baseAddr + WD_TIMER_WSPR, WD_TIMER_DISABLE_SEQ2);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t WDTIMERRevisionIDGet(uint32_t baseAddr)
{
    /* Return the revision id to the called function */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WIDR));
}

void WDTIMERReset(uint32_t baseAddr)
{
    /* Reset the Watchdog timer module */
    HW_WR_FIELD32(
        baseAddr + WD_TIMER_WDSC,
        WD_TIMER_WDSC_SOFTRESET,
        WD_TIMER_WDSC_SOFTRESET_RESETCMD);

    /* Wait until the reset is done */
    while (0x0U ==
           (HW_RD_FIELD32(baseAddr + WD_TIMER_WDST, WD_TIMER_WDST_RESETDONE)))
    {
        /* Do nothing - Busy wait */
    }
}

void WDTIMERPreScalerClkEnable(uint32_t baseAddr, uint32_t ptv)
{
    uint32_t regVal;

    /* Clear the ptv field of WD_TIMER_WCLR register */
    HW_WR_FIELD32(baseAddr + WD_TIMER_WCLR, WD_TIMER_WCLR_PTV, 0U);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /*
    ** Set the ptv field of WD_TIMER_WCLR register with the ptv value and also
    ** enable the pre-scaler clock
    */
    regVal = HW_RD_REG32(baseAddr + WD_TIMER_WCLR);

    HW_SET_FIELD32(regVal, WD_TIMER_WCLR_PTV, ptv >> WD_TIMER_WCLR_PTV_SHIFT);
    HW_SET_FIELD32(regVal, WD_TIMER_WCLR_PRE, WD_TIMER_WCLR_PRE_ENABLED);

    HW_WR_REG32(baseAddr + WD_TIMER_WCLR, regVal);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

void WDTIMERPreScalerClkDisable(uint32_t baseAddr)
{
    /* Disable Pre-scaler clock */
    HW_WR_FIELD32(
        baseAddr + WD_TIMER_WCLR,
        WD_TIMER_WCLR_PRE,
        WD_TIMER_WCLR_PRE_DISABLED);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

void WDTIMERCounterSet(uint32_t baseAddr, uint32_t countVal)
{
    /* Set the WD_TIMER_WCRR register with the countVal */
    HW_WR_REG32(baseAddr + WD_TIMER_WCRR, countVal);

    /* Wait until write is successful to WD_TIMER_WCRR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WCRR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t WDTIMERCounterGet(uint32_t baseAddr)
{
    /* Read the counter value from WD_TIMER_WCRR register */
    /* Delay cannot be added in DAL layer,Application should
     * add delay of 2 timer interface clock cycles + 1 timer functional clock
     * cycle before reading WCRR register */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WCRR));
}

void WDTIMERReloadSet(uint32_t baseAddr, uint32_t reloadVal)
{
    /* Load the WD_TIMER_WLDR register with the re-load value */
    HW_WR_REG32(baseAddr + WD_TIMER_WLDR, reloadVal);

    /* Wait until write is successful to the WD_TIMER_WLDR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WLDR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t WDTIMERReloadGet(uint32_t baseAddr)
{
    /* Return the contents of WD_TIMER_WLDR */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WLDR));
}

void WDTIMERTriggerSet(uint32_t baseAddr, uint32_t trigVal)
{
    /* Set the WD_TIMER_WTGR register with the trigVal*/
    HW_WR_REG32(baseAddr + WD_TIMER_WTGR, trigVal);

    /* Wait till write is successful to WD_TIMER_WTGR register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WTGR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

void WDTIMERDelaySet(uint32_t baseAddr, uint32_t delayVal)
{
    /* Set the WD_TIMER_WDLY register with the delayVal */
    HW_WR_REG32(baseAddr + WD_TIMER_WDLY, delayVal);

    /* Wait until write is successful to the WD_TIMER_WDLY register */
    while (WDTIMERWritePostedStatusGet(baseAddr, WD_TIMER_WRITE_PENDING_WDLY)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t WDTIMERDelayGet(uint32_t baseAddr)
{
    /* Return the WD_TIMER_WDLY register value */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WDLY));
}

void WDTIMERIntRawStatusSet(uint32_t baseAddr, uint32_t intFlags)
{
    /* Set the status in the WD_TIMER_WIRQSTATRAW register */
    HW_WR_REG32(
        baseAddr + WD_TIMER_WIRQSTATRAW,
        intFlags & (WD_TIMER_INT_OVERFLOW | WD_TIMER_INT_DELAY));
}

uint32_t WDTIMERIntRawStatusGet(uint32_t baseAddr)
{
    /* Return the status of the WD_TIMER_WIRQSTATRAW register */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WIRQSTATRAW));
}

uint32_t WDTIMERIntStatusGet(uint32_t baseAddr)
{
    /* Return the status of WD_TIMER_WIRQSTAT register */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WIRQSTAT));
}

void WDTIMERIntStatusClear(uint32_t baseAddr, uint32_t intFlags)
{
    /* Clear the status in the WD_TIMER_WIRQSTAT register */
    HW_WR_REG32(
        baseAddr + WD_TIMER_WIRQSTAT,
        intFlags & (WD_TIMER_INT_OVERFLOW | WD_TIMER_INT_DELAY));
}

void WDTIMERIntEnable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Enable the watchdog timer interrupts */
    HW_WR_REG32(
        baseAddr + WD_TIMER_WIRQENSET,
        intFlags & (WD_TIMER_INT_ENABLE_OVRFLW | WD_TIMER_INT_ENABLE_DELAY));
}

uint32_t WDTIMERIntEnableStatusGet(uint32_t baseAddr)
{
    /* Return the status of WD_TIMER_WIRQENSET register */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WIRQENSET));
}

void WDTIMERIntDisable(uint32_t baseAddr, uint32_t intFlags)
{
    /* Disable the Watchdog timer interrupts */
    HW_WR_REG32(
        baseAddr + WD_TIMER_WIRQENCLR,
        intFlags & (WD_TIMER_INT_DISABLE_DELAY | WD_TIMER_INT_DISABLE_OVRFLW));
}

uint32_t WDTIMERWritePostedStatusGet(uint32_t baseAddr, uint32_t flags)
{
    /* Return the status of WD_TIMER_WWPS register addressed by flags */
    return (HW_RD_REG32(baseAddr + WD_TIMER_WWPS) & flags);
}
/********************************* End of file ******************************/
