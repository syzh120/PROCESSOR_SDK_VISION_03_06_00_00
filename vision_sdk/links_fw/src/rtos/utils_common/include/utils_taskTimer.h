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
 *
 * \defgroup UTILS_API Utility functions
 *
 * \brief This module define APIs that could be used for profiling in multi-task
 *          environment.
 *
 *      Traditional / Wall Clock methods will not provide accurate method for
 *      determining the time spent in a function, which is used in task's
 *      context, in multi-task environment.
 *
 *      API's implemented in this, can used to determine the time spent in
 *      section of code (in a task context), in a multi-task environment.
 *
 *      Currently supported for IPU1_0, DSP1 and DSP2. To enable support for
 *      other cores (which hosts sysBios/TI_RTOS), follow steps below
 *      1. Enable the utility to be built for given core
 *          A. In file /links_fw/src/rtos/utils_common/src/SRC_FILES.MK
 *              include utils_taskTimer.c for the given core
 *              e.g. SRCS_ipu2 += utils_taskTimer.c
 *
 *      2. Add the task switch hook functions (TDA2x and core IPU2 used as e.g.)
 *          A. In file links_fw/src/rtos/bios_app_common/tda2xx/ipu2/Ipu2.cfg
 *          B. Install hooks by adding below code
 *
 *              var Task = xdc.useModule('ti.sysbios.knl.Task');
 *              Task.addHookSet({
 *                  registerFxn: '&Utils_taskTimerRegisterHook',
 *                  createFxn: '&Utils_taskTimerCreateHook',
 *                  readyFxn: '&Utils_taskTimerReadyHook',
 *                  switchFxn: '&Utils_taskTimerSwitchHook',
 *                  exitFxn: '&Utils_taskTimerExitHook',
 *                  deleteFxn: '&Utils_taskTimerDeleteHook',
 *                  });
 *
 *      3. Initialize / De Initialize this feature for a given core
 *          A. In file links_fw/src/rtos/links_common/system/system_common.c
 *          B. Add build macro for given core for function calls
 *              Utils_taskTimerDeInit () & Utils_taskTimerInit ()
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_taskTimer.h
 *
 * \brief Utility functions for profiling
 *
 * \version 0.0 (Jan 2017) : [Suj] First version
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * Expected Usage
 *
 * 1. Utils_taskTimerInit - At system initialization time
 * 2. Utils_taskTimerRegister - By Task which requires to use this utility
 * 3. Utils_taskTimerStart - A
 * 4. Utils_taskTimerStart - B
 *
 * 5. ...
 *
 * 6. Utils_taskTimerStop - Returns time spent in the task between 4 & 6
 * 7. Utils_taskTimerStop - Returns time spent in the task between 3 & 7
 *
 * 8. Utils_taskTimerDeRegister
 * 9. Utils_taskTimerDeInit - At system de initialization
 *
 *******************************************************************************
 */

#ifndef UTILS_TASK_TIMER_H_
#define UTILS_TASK_TIMER_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <stdio.h>
#include <xdc/runtime/Types.h>



/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Maximum number of individual profile points desired in a task.
 *
 *******************************************************************************
 */
#define UTILS_LPROFILE_MAX_PROFILE_POINTS    (5U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of Task that requires to be profiled
 *
 *******************************************************************************
 */
#define UTILS_LPROFILE_MAX_TASKS  (5U)

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*
 *******************************************************************************
 * \brief Init Task Timer utility. Should be called before any other API's of
 *          this utility can be called.
 *
 *        Called during system init. User application should not call this API.
 *
 * \return None
 *******************************************************************************
 */
Void Utils_taskTimerInit(Void);

/*
 *******************************************************************************
 * \brief Each task that requires to use this utility, should register with
 *          this function.
 *
 *
 * \return SYSTEM_LINK_STATUS_EFAIL when more than UTILS_LPROFILE_MAX_TASKS is
 *          registered.
 *******************************************************************************
 */
Int32 Utils_taskTimerRegister(Void);

/*
 *******************************************************************************
 * \brief Starts timer when the registered task is scheduled to run.
 *
 *      Stops, when the calling task is switched out and restarts the timer
 *      when the task is scheduled to run.
 *
 * \return SYSTEM_LINK_STATUS_EFAIL when called without registering.
 *******************************************************************************
 */
Int32 Utils_taskTimerStart(Void);

/*
 *******************************************************************************
 * \brief Stops the timer and total time between Start & Stop is returned.
 *
 *
 * \return Total time between between start and stop.
 *******************************************************************************
 */
UInt64 Utils_taskTimerStop(Void);

/*
 *******************************************************************************
 * \brief Used to de-register the task from this utility.
 *
 *
 * \return Total time between between start and stop.
 *******************************************************************************
 */
Int32 Utils_taskTimerDeRegister(Void);

Void Utils_taskTimerDeInit(Void);

/*
 *******************************************************************************
 * \brief Demo Application / Test
 *
 *
 * \return None
 *******************************************************************************
 */
Void Utils_taskTimerTestRun(Void);

#endif /* ifndef UTILS_TASK_TIMER_H_ */

/* @} */
