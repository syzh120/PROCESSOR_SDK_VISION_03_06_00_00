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
 * \file utils_idle_a15.c
 *
 * \brief  APIs from this file are used to interface the CPU Idle functions
 *
 *         The APIs allow a user to enable CPU idle on a given processor.
 *
 * \version 0.0 (Sep 2014) : [SL] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <stdint.h>
#include <src/rtos/utils_common/include/utils_pm.h>
#include <src/rtos/utils_common/include/utils_idle.h>
#include <ti/sysbios/family/arm/a15/TimestampProvider.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
static Utils_idleCpuObj gUtils_idleCpuObj = {0};

extern uint32_t gUtils_startLoadCalc;
/**
 *******************************************************************************
 *
 * \brief Idle function to be plugged into Idle task.
 *        This function executes idle instruction and puts CPU into low power
 *        state. The targeted low power state is Retention.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idleFxn(Void)
{
#ifdef CPU_IDLE_ENABLED
    UInt32 key;
    Utils_idleCpuObj *pObj;
    Types_Timestamp64 startTimeStruct, endTimeStruct;
    UInt64 localStartTime64, localEndTime64, totalLocalTime64;
    UInt64 globalStartTime64, globalEndTime64, totalGlobalTime64;
    UInt64 tempDiff;
    uint64_t temp; /* Using uint64_t datatype as UInt64 datatype causes
                      MisraC issue while performing shift operation*/

    pObj = &gUtils_idleCpuObj;

    key = Hwi_disable();
    MPU_WUGEN_0_Interrupt_Lookup();
#ifdef DUAL_A15_SMP_BIOS_INCLUDE
    MPU_WUGEN_1_Interrupt_Lookup();
#endif
    Hwi_restore(key);
    if (0U != pObj->idleInitDone)
    {
        key = Hwi_disable();
        globalStartTime64 = Utils_getCurGlobalTimeInUsec();
        /* Get the time as measured by a a local (internal
         * timer will clock gate when the M4 goes to low power) timer.
         */
        TimestampProvider_get64(&startTimeStruct);
        Hwi_restore(key);

        /* Enter low power */
        PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);

        /* After coming out of low power measure the time from local timer.
         */
        key = Hwi_disable();
        TimestampProvider_get64(&endTimeStruct);
        globalEndTime64 = Utils_getCurGlobalTimeInUsec();
        Hwi_restore(key);

        /* Calculate the time taken shown by the local timer */
        temp = (uint64_t)startTimeStruct.hi & 0xFFFFFFFFU;
        temp  = temp << 32U;
        localStartTime64  = (UInt64)startTimeStruct.lo | temp;

        temp = (uint64_t)endTimeStruct.hi & 0xFFFFFFFFU;
        temp  = temp << 32U;
        localEndTime64  = (UInt64)endTimeStruct.lo | temp;

        /* Convert to micro seconds */
        if (localEndTime64 < localStartTime64)
        {
            tempDiff = (localEndTime64 - localStartTime64) + (UInt64)0x00FFFFFF;
        }
        else
        {
            tempDiff = localEndTime64 - localStartTime64;
        }
        totalLocalTime64 = (tempDiff * (UInt64) 1000) /
                           pObj->localTimerFrequency;

        totalGlobalTime64 = globalEndTime64 - globalStartTime64;
        /* This is done as the 32K timer runs much slowly than the CPU timer
         * with a difference of 1 cycle count the time difference can be of
         * 1/32786 sec = 30.5 us. Hence adding 30 to the difference if it is
         * negative to get approximate value of the time difference.
         */
        if (totalGlobalTime64 < totalLocalTime64)
        {
            totalGlobalTime64 = totalGlobalTime64 + (UInt64) 30;
        }
        /* Calculate the number of clocks for which the M4 was in low power
         * at sysclock time stamp counts */
        key = Hwi_disable();
        if ((uint32_t)TRUE == gUtils_startLoadCalc)
        {
            temp = totalGlobalTime64 - totalLocalTime64;
            Int64 timeInIdle = (Int64)temp;
            if (timeInIdle > 0)
            {
                pObj->timeInSleep = pObj->timeInSleep + (UInt64)(((UInt64) timeInIdle
                               * (UInt64)PMHALCMGetSysClockFreq())/(UInt64)1000);
            }
        }
        Hwi_restore(key);
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief Prepare the system configuration for CPU idle in IDLE Task.
 *        In case of A15, this function enables SR3-APG (HG / Fast Ramp-up).
 *        It also forces A15_1 to OFF.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_idlePrepare(Void)
{
    Utils_idleCpuObj *pObj;
#ifdef CPU_IDLE_ENABLED

    UInt32 procId;
    Int32 status = (Int32) PM_SUCCESS;
    pmhalPrcmModuleId_t moduleId;
    Types_FreqHz freq;
    uint64_t temp; /* Using uint64_t datatype as UInt64 datatype causes
                      MisraC issue while performing shift operation*/

    pmhalMpuPowerStatusParams_t mpuPowerState;
    pObj = &gUtils_idleCpuObj;

    procId = System_getSelfProcId();
    moduleId = (pmhalPrcmModuleId_t)Utils_pmGetModId(procId);

    status = PMLIBCpuModePrepare(moduleId,PMLIB_IDLE_CPU_MODE_AUTOCG);

    pObj->timeInSleep = (UInt64) 0;
    if (status == PM_SUCCESS)
    {
        MPU_WUGEN_Init();
        /* Make sure CPU1 is ON before forcing CPU1 off */
#ifndef DUAL_A15_SMP_BIOS_INCLUDE
        PMHALMpuLprmGetPowerStatus((UInt32)1u, &mpuPowerState);
        if (PMHAL_PRCM_PD_STATE_ON_ACTIVE == mpuPowerState.currPowerStatus)
        {
            PMLIBCpu1ForcedOff();
        }
#endif
        pObj->idleInitDone = 1U;
        TimestampProvider_getFreq(&freq);

        temp = (uint64_t)freq.hi & 0xFFFFFFFFU;
        temp  = temp << 32;
        pObj->localTimerFrequency = ((UInt64)freq.lo | temp)/(UInt64)1000;
    }
#else
    pObj = &gUtils_idleCpuObj;
    pObj->timeInSleep = (UInt64) 0;
#endif
}

/**
 *******************************************************************************
 *
 * \brief  This function is called during the load update call back to populate
 *         the amount of time in 20 MHz ticks the CPU has been in low power.
 *
 * \return None
 *
 *******************************************************************************
 */
UInt64 Utils_idleGetLowPowerTime(Void)
{
    UInt32 key;
    Utils_idleCpuObj *pObj;
    UInt64 timeInLowPower;

    pObj = &gUtils_idleCpuObj;

    timeInLowPower = pObj->timeInSleep;

    /* Reset the total time in sleep when read */
    key = Hwi_disable();
    pObj->timeInSleep = (UInt64) 0;
    Hwi_restore(key);

    return timeInLowPower;
}

/* Nothing beyond this point */
