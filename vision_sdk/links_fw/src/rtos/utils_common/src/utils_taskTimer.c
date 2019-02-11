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
 * \file utils_taskTimer.c
 *
 * \brief Utility functions to profile/time stamp in multi-task environment
 *
 * \version 0.0 (Jan 2017) : [Suj] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/drv/vps/include/osal/bsp_osal.h>

#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_taskTimer.h>


/**
 *******************************************************************************
 *  \brief Object that defines stores start and accumulated time stamps.
 *******************************************************************************
 */

typedef struct Utils_taskTimerTsObj
{
    UInt64 startTs;
    UInt64 accumTs;
    UInt32 isTsActive;

} Utils_taskTimerTsObj_t;

typedef struct lProfileObj
{
    Utils_taskTimerTsObj_t tsObjs[UTILS_LPROFILE_MAX_PROFILE_POINTS];
    Task_Handle tskHndl;
    UInt32 isActive;
    UInt32 useTsObjInst; /* 0toUTILS_LPROFILE_MAX_PROFILE_POINTS_IN_A_TASK - 1*/

}Utils_taskTimerObj_t;

/**
 *******************************************************************************
 * Hook Prototypes
 *******************************************************************************
*/
Void Utils_taskTimerRegisterHook(Int hookSetId);
Void Utils_taskTimerCreateHook(Task_Handle task, Error_Block *eb);
Void Utils_taskTimerReadyHook(Task_Handle task);
Void Utils_taskTimerSwitchHook(Task_Handle prev, Task_Handle next);
Void Utils_taskTimerExitHook(Task_Handle task);
Void Utils_taskTimerDeleteHook(Task_Handle task);

/**
 *******************************************************************************
 * \brief Global variable to keep track of timestamps for each profile point
 *          for each task.
 *******************************************************************************
*/
Utils_taskTimerObj_t gProfileContext[UTILS_LPROFILE_MAX_TASKS];

/*******************************************************************************
 *  Local Functions Defination
 *******************************************************************************
 */
static Void localDelay(UInt32 delay);
static Void demoMultiProfilePoint_UsingTaskTimer(UInt32 seconds);
static inline UInt64 getElapsedTime(UInt64 currTs, UInt64 startTs);
static Void demoOneProfilePoint_UsingTaskTimer(UInt32 seconds);

 /*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static inline UInt64 getElapsedTime(UInt64 currTs, UInt64 startTs)
{
    UInt64 elapsedTime;

    if (currTs > startTs)
    {
        elapsedTime = currTs - startTs;
    }
    else
    {
        /* ( Max - Previous stamp ) + current */
        elapsedTime = 0xFFFFFFFFFFFFFFFFU - startTs;
        elapsedTime += currTs;
    }
    return (elapsedTime);
}

Void Utils_taskTimerInit(Void)
{
    memset(&gProfileContext, 0, sizeof(gProfileContext));
}

Int32 Utils_taskTimerRegister(Void)
{
    Int32 rtnVal = SYSTEM_LINK_STATUS_EFAIL;
    Utils_taskTimerObj_t *pObjInst = NULL;
    UInt32 cookie, i;

    cookie = Hwi_disable();

    for (i = 0; i < UTILS_LPROFILE_MAX_TASKS; i++)
    {
        if (0U == gProfileContext[i].isActive)
        {
            pObjInst = &gProfileContext[i];
            break;
        }
    }
    if (NULL != pObjInst)
    {
        pObjInst->tskHndl = BspOsal_taskGetSelfHandle();
        pObjInst->useTsObjInst = 0;
        pObjInst->isActive = 1U;
        memset(&pObjInst->tsObjs, 0, sizeof(pObjInst->tsObjs));

        Task_setEnv((Task_Handle)pObjInst->tskHndl, (Ptr) pObjInst);
        rtnVal = SYSTEM_LINK_STATUS_SOK;
    }

    Hwi_restore(cookie);

    return (rtnVal);
}

Int32 Utils_taskTimerStart(Void)
{
    UInt32 cookie;
    Task_Handle tskHndl;
    Int32 rtnVal;
    Utils_taskTimerObj_t *pObjInst;
    Utils_taskTimerTsObj_t *pTsObj;

    cookie = Hwi_disable();

    rtnVal = SYSTEM_LINK_STATUS_EFAIL;
    pObjInst = NULL;
    pTsObj = NULL;

    tskHndl = BspOsal_taskGetSelfHandle();
    UTILS_assert(NULL != tskHndl);

    pObjInst = (Utils_taskTimerObj_t *) Task_getEnv(tskHndl);

    UTILS_assert(NULL != pObjInst);
    /* Start Called without registering the task */
    UTILS_assert(pObjInst->tskHndl == tskHndl);

    if (pObjInst->useTsObjInst < UTILS_LPROFILE_MAX_PROFILE_POINTS)
    {
        if (0U == pObjInst->tsObjs[pObjInst->useTsObjInst].isTsActive)
        {
            pTsObj = &pObjInst->tsObjs[pObjInst->useTsObjInst];
        }
        else
        {
            /* Book keeping is broken, an TS object marked as available is not
                available */
            UTILS_assert(FALSE);
        }
    }

    if (NULL != pTsObj)
    {
        rtnVal = SYSTEM_LINK_STATUS_SOK;
        pObjInst->useTsObjInst++;
        pTsObj->isTsActive = 1U;
        pTsObj->accumTs = 0;
        pTsObj->startTs = Utils_getCurTimeInUsec();
    }
    Hwi_restore(cookie);

    return (rtnVal);
}

UInt64 Utils_taskTimerStop(Void)
{
    Task_Handle tskHndl;
    Utils_taskTimerObj_t *pObjInst;
    Utils_taskTimerTsObj_t *pTsObj;
    UInt32 cookie, tsInst;
    UInt64 elapsedTime, currTime;

    cookie = Hwi_disable();

    elapsedTime = 0;
    pObjInst = NULL;
    pTsObj = NULL;
    currTime = Utils_getCurTimeInUsec();

    tskHndl = BspOsal_taskGetSelfHandle();
    UTILS_assert(NULL != tskHndl);

    pObjInst = (Utils_taskTimerObj_t *) Task_getEnv(tskHndl);

    UTILS_assert(NULL != pObjInst);
    /* Stop called without registration */
    UTILS_assert(pObjInst->tskHndl == tskHndl);

    if (pObjInst->useTsObjInst > 0U)
    {
        tsInst = pObjInst->useTsObjInst - 1U;
        pObjInst->useTsObjInst--;
    }
    else
    {
        tsInst = 0U;
        pObjInst->useTsObjInst = 0U;
    }
    /* Guard */
    UTILS_assert(UTILS_LPROFILE_MAX_PROFILE_POINTS > tsInst);

    pTsObj = &pObjInst->tsObjs[tsInst];
    if (1U == pTsObj->isTsActive)
    {
        pTsObj->isTsActive = 0U;

        elapsedTime = getElapsedTime(currTime, pTsObj->startTs);
        elapsedTime += pTsObj->accumTs;
    }

    Hwi_restore(cookie);
    return (elapsedTime);
}

Int32 Utils_taskTimerDeRegister(Void)
{
    UInt32 cookie;
    Task_Handle tskHndl;
    Utils_taskTimerObj_t *pObjInst;

    cookie = Hwi_disable();

    pObjInst = NULL;

    tskHndl = BspOsal_taskGetSelfHandle();
    UTILS_assert(NULL != tskHndl);

    pObjInst = (Utils_taskTimerObj_t *) Task_getEnv(tskHndl);

    if (NULL != pObjInst)
    {
        /* De Register Called without registering the task */
        UTILS_assert(pObjInst->tskHndl == tskHndl);

        Task_setEnv(pObjInst->tskHndl, (Ptr) NULL);

        pObjInst->tskHndl = (Task_Handle)NULL;
        pObjInst->useTsObjInst = 0;
        pObjInst->isActive = 0U;
        memset(&pObjInst->tsObjs, 0, sizeof(pObjInst->tsObjs));
    }

    Hwi_restore(cookie);
    return (SYSTEM_LINK_STATUS_SOK);
}

Void Utils_taskTimerSwitchHook(Task_Handle prev, Task_Handle next)
{
    Utils_taskTimerObj_t *pObjInst;
    Utils_taskTimerTsObj_t *pTsObj;
    UInt32 cookie, tsInst;
    UInt64 currTime;

    cookie = Hwi_disable();

    pObjInst = NULL;
    pTsObj = NULL;
    currTime = Utils_getCurTimeInUsec();

    /* Updated accumulated time for task being switched out */
    if (NULL != prev)
    {
        pObjInst = (Utils_taskTimerObj_t *) Task_getEnv(prev);
        if (NULL != pObjInst)
        {
            if ((pObjInst->tskHndl == prev) &&
                (1U == pObjInst->isActive))
            {
                for (tsInst = 0U; tsInst < pObjInst->useTsObjInst; tsInst++)
                {
                    pTsObj = &pObjInst->tsObjs[tsInst];
                    if (pTsObj->isTsActive != 0)
                    {
                        pTsObj->accumTs += getElapsedTime(currTime,
                                                            pTsObj->startTs);
                    }
                }
            }
        } /* Other task's */
    }

    /* Update start time for task's being switched in */
    if (NULL != next) /* Check not required i guess */
    {
        pObjInst = (Utils_taskTimerObj_t *) Task_getEnv(next);
        if (NULL != pObjInst)
        {
            if ((pObjInst->tskHndl == next) &&
                (1U == pObjInst->isActive))
            {
                for (tsInst = 0U; tsInst < pObjInst->useTsObjInst; tsInst++)
                {
                    pTsObj = &pObjInst->tsObjs[tsInst];
                    if (pTsObj->isTsActive != 0)
                    {
                        pTsObj->startTs = currTime;
                    }
                }
            }
        }
    }
    Hwi_restore(cookie);
}


Void Utils_taskTimerDeInit(Void)
{
    UInt32 cookie;

    cookie = Hwi_disable();
    memset(&gProfileContext, 0, sizeof(gProfileContext));
    Hwi_restore(cookie);
}

Void Utils_taskTimerRegisterHook(Int hookSetId)
{
    /* nothing as of now */
    return;
}

Void Utils_taskTimerCreateHook(Task_Handle task, Error_Block *eb)
{
    /* nothing as of now */
    return;
}

Void Utils_taskTimerReadyHook(Task_Handle task)
{
    /* nothing as of now */
    return;
}

Void Utils_taskTimerExitHook(Task_Handle task)
{
    /* nothing as of now */
    return;
}

Void Utils_taskTimerDeleteHook(Task_Handle task)
{
    /* nothing as of now */
    return;
}

/*******************************************************************************
 *  Test Functions - Please call Utils_taskTimerTestRun from a task context
 *******************************************************************************
 */

/* Local Delay - emulating some CPU work */
static Void localDelay(UInt32 delay)
{
    volatile UInt32 loopcnt = 0;

    while (loopcnt < delay)
    {
        loopcnt++;
    }
}

static Void demoMultiProfilePoint_UsingTaskTimer(UInt32 seconds)
{
    UInt64 wallClkPre, wallClkPost0, wallClkMid0, taskTimerPost0;
    UInt64 wallClkPost1, wallClkMid1, taskTimerPost1;

    Vps_printf("      Exercising dummyOperation and task sleep : with multi profile points\r\n");

    wallClkPre = Utils_getCurTimeInUsec();
    Utils_taskTimerStart(); /* Profile point 1 start */
    Utils_taskTimerStart(); /* Profile point 2 start */
    /* Some operation, sleeping to demonstrate task-switch & load */

    /* 1St operation */
    localDelay (9000U);
    wallClkMid0 = Utils_getCurTimeInUsec();
    /* Task should be switched out */
    BspOsal_sleep(seconds * 1000U);

    wallClkPost0 = Utils_getCurTimeInUsec();
    taskTimerPost0 = Utils_taskTimerStop();

    /* 2nd operation */
    localDelay (9000U);
    wallClkMid1 = Utils_getCurTimeInUsec();
    /* Task should be switched out */
    BspOsal_sleep(seconds * 1000U);
    wallClkPost1 = Utils_getCurTimeInUsec();
    taskTimerPost1 = Utils_taskTimerStop();


    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Option Global Time Stamp | Time in micro seconds\r\n");
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Dummy Op 1 Only          | %d\r\n",
            (UInt32) ((wallClkMid0 & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      | Dummy Op 1 & 1X TaskDelay| %d\r\n",
            (UInt32) ((wallClkPost0 & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      | Dummy Op 2 Only          | %d\r\n",
            (UInt32) ((wallClkMid1 & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      | Dummy Op 2 & 2X TaskDelay| %d\r\n",
            (UInt32) ((wallClkPost1 & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Option TimeStamp Utility | Time in micro seconds\r\n");
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Dummy Op 1 & 1X TaskDelay| %d\r\n",
            (UInt32) (taskTimerPost0 & 0xFFFFFFFFU));
    Vps_printf("      | Dummy Op 2 & 2X TaskDelay| %d\r\n",
            (UInt32) (taskTimerPost1 & 0xFFFFFFFFU));
}

static Void demoOneProfilePoint_UsingTaskTimer(UInt32 seconds)
{
    UInt64 wallClkPre, wallClkPost, wallClkMid, taskTimerPost;

    Vps_printf("      Exercising dummyOperation and task sleep : with single profile points\r\n");

    wallClkPre = Utils_getCurTimeInUsec();
    Utils_taskTimerStart();

    /* Some operation, sleeping to demonstrate task-switch & load */

    /* CPU Load */
    localDelay (9000U);

    wallClkMid = Utils_getCurTimeInUsec();
    /* Task should be switched out */
    BspOsal_sleep(seconds * 1000U);

    wallClkPost = Utils_getCurTimeInUsec();
    taskTimerPost = Utils_taskTimerStop();

    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Option Global Time Stamp | Time in micro seconds\r\n");
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Dummy Op Only            | %d\r\n",
            (UInt32) ((wallClkMid & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      | Dummy Op & Task Delay    | %d\r\n",
            (UInt32) ((wallClkPost & 0xFFFFFFFFU) - (wallClkPre & 0xFFFFFFFFU)));
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Option TimeStamp Utility | Time in micro seconds\r\n");
    Vps_printf("      + -------------------------+-------------------\r\n");
    Vps_printf("      | Dummy Op & Task Delay    | %d\r\n",
            (UInt32) (taskTimerPost & 0xFFFFFFFFU));
    Vps_printf("      + -------------------------+-------------------\r\n");
}

Void Utils_taskTimerTestRun(Void)
{
    Int32 status;
    UInt32 idx, count, timeDur[]={4, 5, 6, 1};

    status = Utils_taskTimerRegister();
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    count = sizeof (timeDur) / sizeof(UInt32);

    Vps_printf("      This test simulates an CPU operation followed by Task Sleep\r\n");
    Vps_printf("      The time required for CPU operation with Task_Sleep is measured using wall clock method \r\n");
    Vps_printf("      And also measured using TaskTimer utility and printed\r\n");

    Vps_printf("      Two seperate test for single profile point and multi profile points\r\n");

    for (idx = 0; idx < count; idx++)
    {
        Vps_printf("\r\n");
        Vps_printf("      Iteration %d / of %d with taskSleep of %d seconds\r\n",
            (idx + 1U), count, timeDur[idx]);
        Vps_printf("\r\n");
        demoOneProfilePoint_UsingTaskTimer(timeDur[idx]);
        demoMultiProfilePoint_UsingTaskTimer(timeDur[idx]);
        Vps_printf("\r\n");
    }

    status = Utils_taskTimerDeRegister();
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}
