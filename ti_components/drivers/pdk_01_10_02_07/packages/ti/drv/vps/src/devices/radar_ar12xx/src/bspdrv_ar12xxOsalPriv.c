/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 */

/**
 *  \file   bspdrv_ar12xxOsalCbPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver OSAL callbacks.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Clock Tick rate in milli seconds. Assume M4 clock tick is 1ms */
#define BSP_AR12XX_TICK_RATE_MS          (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#ifndef __cplusplus
#pragma DATA_ALIGN(gRadarDevTskStack, 32);
#pragma DATA_SECTION(gRadarDevTskStack, ".bss");
#else
#pragma DATA_ALIGN(32);
#pragma DATA_SECTION(".bss");
#endif
static UInt8  gRadarDevTskStack[4096];

/** \brief Place holder for storing the devices which are returned through the
 *         Bsp_ar12xxRadarTaskPost call back.
 */
static UInt32 gDeviceIdList[BSP_AR12XX_MAX_ASYNC_MESSAGES_SUPPORTED];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Radar driver task which runs the callback which the radar interface
 *          functions will return.
 *
 *  \return None
 */
static void Bsp_ar12xxRadarDevTask(UInt32 arg0, UInt32 arg1);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxCreateCommInfra(void)
{
    Int32 retVal = BSP_SOK;

    gBspAr12xxObj.radarDevTskHndl = NULL;

    /* Create a queue to hold the device Ids for which the host interrupt
     * is recieved.
     */
    gBspAr12xxObj.messageId = 0U;
    BspUtils_queCreate(&gBspAr12xxObj.gpioAsyncEvtQueHandle,
                        BSP_AR12XX_MAX_ASYNC_MESSAGES_SUPPORTED,
                        &gBspAr12xxObj.asyncEvtDevQue,
                        BSPUTILS_QUE_FLAG_BLOCK_QUE_GET
                        );
    /* Create the radar driver task */
    gBspAr12xxObj.stopRadarDevTsk = 0U;
    gBspAr12xxObj.pauseRadarDevTsk = 0U;
    gBspAr12xxObj.radarDevTskHndl = BspOsal_taskCreate(
            &Bsp_ar12xxRadarDevTask,
            "BspAr12xxDevTask",
            gBspAr12xxObj.initPrmsCopy.tskPriority,
            &gRadarDevTskStack,
            sizeof (gRadarDevTskStack),
            NULL,
            0U
            );
    if (gBspAr12xxObj.radarDevTskHndl == NULL)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

Int32 Bspdrv_A12xxSemObjCreateCb(void **pLockObj, Char *name)
{
    Int32 retVal = BSP_SOK;
    *pLockObj = (void *) BspOsal_semCreate((Int32) 1, (Bool) TRUE);
    return retVal;
}

Int32 Bsp_ar12xxSemObjWaitCb(void **pLockObj, UInt32 timeout)
{
    Int32 retVal = BSP_SOK;
    switch (timeout)
    {
        case RL_OSI_NO_WAIT:
            timeout = BSP_OSAL_NO_WAIT;
            break;
        case RL_OSI_WAIT_FOREVER:
            timeout = BSP_OSAL_WAIT_FOREVER;
            break;
        default:
            timeout = timeout / BSP_AR12XX_TICK_RATE_MS;
            break;
    }
    BspOsal_semWait((BspOsal_SemHandle) * pLockObj, timeout);
    return retVal;
}

Int32 Bsp_ar12xxSemObjPendCb(void **pLockObj)
{
    BspOsal_semPost((BspOsal_SemHandle) * pLockObj);
    return BSP_SOK;
}

Int32 Bsp_ar12xxSemObjDeleteCb(void **pLockObj)
{
    BspOsal_semDelete((BspOsal_SemHandle *) pLockObj);
    return BSP_SOK;
}

Int32 Bsp_ar12xxSleepCb(UInt32 milliSecs)
{
    /* Need a wrapper as the return type of Bsp_Osal is void */
    BspOsal_sleep(milliSecs);
    return BSP_SOK;
}

Int32 Bsp_ar12xxRadarTaskPost(BspDrv_ar12xxSpawnCallBack pEntry,
                              const void                *pValue,
                              UInt32                     flags)
{
    Int32        retVal   = BSP_SOK;
    const UInt32 deviceId = (UInt32) (*(const UInt8 *) pValue);
    /* Assume one device gives only one message at a time */
    gDeviceIdList[gBspAr12xxObj.messageId] = deviceId;
    /* Register the callback */
    gBspAr12xxObj.appSpawnCb = pEntry;
    /* Place the device Id in the queue. This will be dequeued by the
     * Bsp_ar12xxRadarDevTask task.
     */
    retVal = BspUtils_quePut(&gBspAr12xxObj.gpioAsyncEvtQueHandle,
                             &gDeviceIdList[gBspAr12xxObj.messageId],
                             BSP_OSAL_NO_WAIT);
    gBspAr12xxObj.messageId = (gBspAr12xxObj.messageId + 1U) %
                               BSP_AR12XX_MAX_ASYNC_MESSAGES_SUPPORTED;
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void Bsp_ar12xxRadarDevTask(UInt32 arg0, UInt32 arg1)
{
    Int32 retVal   = BSP_EFAIL;
    Ptr  deviceId = NULL;

    while (gBspAr12xxObj.stopRadarDevTsk == 0U)
    {
        /* Wait for the next queued deviceId */
        retVal = BspUtils_queGet(&gBspAr12xxObj.gpioAsyncEvtQueHandle,
                                 &deviceId, 1U, BSP_OSAL_WAIT_FOREVER);
        if ((retVal == BSP_SOK) && (gBspAr12xxObj.appSpawnCb != NULL)
            && (gBspAr12xxObj.stopRadarDevTsk == 0U)
            && (gBspAr12xxObj.pauseRadarDevTsk == 0U))
        {
            /* Execute the function which is given when during the Task Post
             * Callback.
             */
             gBspAr12xxObj.appSpawnCb(deviceId);
        }
    }
}

