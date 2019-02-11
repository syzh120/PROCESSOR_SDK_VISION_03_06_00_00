/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_global_time.c
 *
 * \brief  This file implements the global timer.
 *
 *          This file implements the periodic timer task for local M4. It
 *          increments the shared region with current M4 time stamp every 1ms
 *          Provides helper function to read this time stamp. This function can
 *          be called by all the CPUs. So that every CPU will get the
 *          same time reference for latency and debug print calculation.
 *
 *
 * \version 0.1 (Aug 2013) : [HS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>


/*******************************************************************************
 * Setup a low frequency clock periodic function
 * to call the CLK32KHZ counter function
 * in order to track overflow condition
 *
 * CLK32KHZ will roughly overflow after 1 day of operation
 * so calling this periodic function once in one hour is enough to
 * guard against overflow condition
 *******************************************************************************
 */
#define  COUNTER_32K_OVERFLOW_CHECK_TIMER_PERIOD_IN_MS          (1000U*60U*60U)


#define COUNTER_32K_CR          (*(volatile UInt32*)0x4AE04030U)
#define COUNTER_32K_CR_REF_CLK   (32786U) /* Actual value used on 20M/610
                                            610 is post div in clock tree*/

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Global timer data structure.
 *
 *            This holds the handle to clock started.
 *
 *******************************************************************************
*/
typedef struct
{
    /**<  Periodic Clock object */
    BspOsal_ClockHandle clkHandle;
    /**<  Periodic Clock object handle */
    UInt32 oldClk32KhzValue;
    /**< Last value of CLK 32Khz timer to check overflow */
    UInt32 clk32KhzOverflow;
    /**< CLK 32Khz overflow count */
} Utils_GlobalTimerObj;


/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
static void Utils_globalTimerPrdFunc(UInt32 arg);

/**
 *******************************************************************************
 *
 *   \brief Global timer object
 *
 *          This holds the timer handle. This is for local processor.
 *
 *******************************************************************************
*/
Utils_GlobalTimerObj gUtils_GlobalTimerObj = { 0 };

/**
 *******************************************************************************
 *
 * \brief Periodic timer function
 *
 *        It get the current time and copies it into shared memory. For all
 *        cores this time is used as reference. This timer runs only for
 *        local core.
 *
 * \param   arg     [IN] Not used.
 *
 *******************************************************************************
 */
static void Utils_globalTimerPrdFunc(UInt32 arg)
{
    Utils_getCurGlobalTimeInUsec();
}

/**
 *******************************************************************************
 *
 * \brief Initializes the global timer for 1ms period.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
Int32 Utils_globalTimerInit(void)
{
    Utils_GlobalTimerObj *pClkObj;

    pClkObj = &gUtils_GlobalTimerObj;

    pClkObj->clkHandle = BspOsal_clockCreate(
                            &Utils_globalTimerPrdFunc,
                            COUNTER_32K_OVERFLOW_CHECK_TIMER_PERIOD_IN_MS,
                            (Bool)FALSE,
                            pClkObj
                            );
    UTILS_assert(pClkObj->clkHandle!=NULL);

    BspOsal_clockStart(pClkObj->clkHandle);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get current Global time across all cores
 *        Its important to have a global time across all cores to identify
 *        certain things like latency/delay etc. All link should use this
 *        function to insert timestamp or calculate latency/delay etc.
 *
 * \return current Global time in units of micro sec's
 *
 *******************************************************************************
 */
UInt64 Utils_getCurGlobalTimeInMsec(void)
{
    return Utils_getCurGlobalTimeInUsec()/1000U;
}

/**
 *******************************************************************************
 *
 * \brief Get current Global time across all cores
 *        Its important to have a global time across all cores to identify
 *        certain things like latency/delay etc. All link should use this
 *        function to insert timestamp or calculate latency/delay etc.
 *
 * \return current Global time in units of micro sec's
 *
 *******************************************************************************
 */
UInt64 Utils_getCurGlobalTimeInUsec(void)
{
    UInt64 curGblTime;
    UInt32 oldIntState;
    UInt64 clk32KhzValue;
    UInt64 clk32KhzValue64;
    uint64_t temp; /* Using uint64_t datatype as UInt64 datatype causes
                      MisraC issue while performing shift operation*/

    oldIntState = Hwi_disable();

    clk32KhzValue = COUNTER_32K_CR;

    if(clk32KhzValue < gUtils_GlobalTimerObj.oldClk32KhzValue)
    {
        gUtils_GlobalTimerObj.clk32KhzOverflow++;
    }

    temp = (uint64_t)gUtils_GlobalTimerObj.clk32KhzOverflow &
        0xFFFFFFFFU;
    temp  = temp << 32U;
    clk32KhzValue64  = (UInt64)clk32KhzValue | temp;

    curGblTime = (1000000U*clk32KhzValue64)/COUNTER_32K_CR_REF_CLK;

    gUtils_GlobalTimerObj.oldClk32KhzValue = clk32KhzValue;

    Hwi_restore(oldIntState);

    return (curGblTime);
}

Void Utils_getGlobalTimeCounterValue(UInt32 *valueH, UInt32 *valueL)
{
    UInt32 oldIntState;

    oldIntState = Hwi_disable();

    Utils_getCurGlobalTimeInUsec();

    *valueL = gUtils_GlobalTimerObj.oldClk32KhzValue;
    *valueH = gUtils_GlobalTimerObj.clk32KhzOverflow;

    Hwi_restore(oldIntState);
}
