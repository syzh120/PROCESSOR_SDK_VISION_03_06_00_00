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
 * \file osa_global_time.c
 *
 * \brief  This file implements the global timer.
 *
 * \version 0.1 (Aug 2013) : [HS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <osa.h>
#include <osa_mem.h>
#include <osa_mutex.h>

#define COUNTER_32K_CR_REG_PHYS_ADDR        (0x4AE04030)
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
 *			This holds the handle to clock started.
 *
 *******************************************************************************
*/
typedef struct
{
    OSA_MutexHndl lock;
    /**< lock to serialize access to counter */

    unsigned int COUNTER_32K_CR_REG_VIRT_ADDR;
    /**< CLK32KHZ virtual address */

    UInt32 oldClk32KhzValue;
    /**< Last value of CLK 32Khz timer to check overflow */

    UInt32 clk32KhzOverflow;
    /**< CLK 32Khz overflow count */
    
} OSA_GlobalTimerObj;

/**
 *******************************************************************************
 *
 *   \brief Global timer object
 *
 *          This holds the timer handle. This is for local processor.
 *
 *******************************************************************************
*/
OSA_GlobalTimerObj gOSA_GlobalTimerObj;

/**
 *******************************************************************************
 *
 * \brief Initializes the global timer for 1ms period.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
int OSA_globalTimerInit(void)
{
    Int32 status;

    memset(&gOSA_GlobalTimerObj, 0, sizeof(gOSA_GlobalTimerObj));
    
    status = OSA_mutexCreate(&gOSA_GlobalTimerObj.lock);
    OSA_assertSuccess(status);

    gOSA_GlobalTimerObj.COUNTER_32K_CR_REG_VIRT_ADDR
        = OSA_memMap(COUNTER_32K_CR_REG_PHYS_ADDR, sizeof(UInt32));

    return 0;
}

void OSA_setGlobalTimeH(UInt32 timeH)
{
    OSA_mutexLock(&gOSA_GlobalTimerObj.lock);

    gOSA_GlobalTimerObj.clk32KhzOverflow = timeH;

    OSA_mutexUnlock(&gOSA_GlobalTimerObj.lock);
}

int OSA_syncGlobalTime()
{
    SystemCommon_GlobalTime prm;
    Int32 status = 0;
    UInt32 timeL;

    while(1)
    {
        OSA_getCurGlobalTimeInUsec();

        OSA_mutexLock(&gOSA_GlobalTimerObj.lock);
        timeL = gOSA_GlobalTimerObj.oldClk32KhzValue;
        OSA_mutexUnlock(&gOSA_GlobalTimerObj.lock);

        if(timeL > 0xFFFFFFC0)
        {
            /* too close to overflow, race condition could occur if
               we try to get overflow count form remote core.
               Wait few msecs and check again
             */
           OSA_waitMsecs(2);
        }
        else
        {
            status = System_linkControl(
                SYSTEM_LINK_ID_IPU1_0,
                SYSTEM_COMMON_CMD_GET_GLOBAL_TIME,
                &prm,
                sizeof(prm),
                TRUE
                );
            if(status==0) {
                
                OSA_setGlobalTimeH(prm.timeH);
        
                #if 1
                Vps_printf(" OSA: Adjusting global time, timeH by %d units!!!\n", 
                    prm.timeH
                );
                #endif
            }
            break;
        }
    }
    return status;
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
int OSA_globalTimerDeInit(void)
{
    Int32 status;

    status = OSA_mutexDelete(&gOSA_GlobalTimerObj.lock);
    OSA_assertSuccess(status);

    OSA_memUnMap(gOSA_GlobalTimerObj.COUNTER_32K_CR_REG_VIRT_ADDR, sizeof(UInt32));

    return 0;
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
UInt64 OSA_getCurGlobalTimeInMsec(void)
{
    return OSA_getCurGlobalTimeInUsec()/1000;
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
UInt64 OSA_getCurGlobalTimeInUsec(void)
{
    UInt64 curGblTime;
    UInt32 clk32KhzValue;
    UInt64 clk32KhzValue64;

    OSA_mutexLock(&gOSA_GlobalTimerObj.lock);

    clk32KhzValue = *(volatile UInt32*)gOSA_GlobalTimerObj.COUNTER_32K_CR_REG_VIRT_ADDR;

    if(clk32KhzValue < gOSA_GlobalTimerObj.oldClk32KhzValue)
        gOSA_GlobalTimerObj.clk32KhzOverflow++;

    clk32KhzValue64 = ((UInt64)clk32KhzValue | ((UInt64)gOSA_GlobalTimerObj.clk32KhzOverflow << 32));

    curGblTime = (1000000*clk32KhzValue64)/COUNTER_32K_CR_REF_CLK;

    gOSA_GlobalTimerObj.oldClk32KhzValue = clk32KhzValue;

    OSA_mutexUnlock(&gOSA_GlobalTimerObj.lock);

    return (curGblTime);
}

