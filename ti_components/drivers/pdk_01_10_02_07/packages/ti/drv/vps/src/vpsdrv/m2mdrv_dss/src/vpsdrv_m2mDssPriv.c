/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file vpsdrv_m2mDssPriv.c
 *
 *  \brief VPS DSS M2M driver utility file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <m2mdrv_dss/src/vpsdrv_m2mDssPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          FVID2 API Functions                               */
/* ========================================================================== */

/**
 *  vpsMdrvDssGetInstObj
 *  Returns the instance object pointer for the instance id.
 */
VpsMDrv_DssInstObj *vpsMdrvDssGetInstObj(UInt32 instId)
{
    UInt32 instCnt;
    VpsMDrv_DssInstObj *instObj = NULL;

    /* Find out the instance to which this channel belongs to */
    for (instCnt = 0U; instCnt < gVpsMDrvDssCommonObj.numInsts; instCnt++)
    {
        if (gVpsMDrvDssCommonObj.instObj[instCnt].drvInstId == instId)
        {
            instObj = &gVpsMDrvDssCommonObj.instObj[instCnt];
            break;
        }
    }

    return (instObj);
}

Int32 vpsMdrvCheckCreateArgs(const VpsMDrv_DssInstObj     *instObj,
                             const Vps_M2mDssCreateParams *createPrms)
{
    UInt32  i;
    Int32   retVal = FVID2_SOK;

    if ((NULL == instObj) || (NULL == createPrms))
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        if (createPrms->wbInNode >= VPS_DSS_DISPC_WB_IN_NODE_MAX)
        {
            GT_1trace(VpsDrvCaptTrace, GT_ERR,
                "Invalid input node %d\r\n", createPrms->wbInNode);
            retVal = FVID2_EINVALID_PARAMS;
        }

#if defined (SOC_TDA3XX)
        if ((createPrms->wbInNode == VPS_DSS_DISPC_WB_IN_NODE_VID3) ||
            (createPrms->wbInNode == VPS_DSS_DISPC_WB_IN_NODE_LCD3) ||
            (createPrms->wbInNode == VPS_DSS_DISPC_WB_IN_NODE_TV))
        {
            GT_1trace(VpsDrvCaptTrace, GT_ERR,
                "TDA3xx doesn't support WB input node %d\r\n",
                createPrms->wbInNode);
            retVal = FVID2_EINVALID_PARAMS;
        }
#endif

        if ((createPrms->numInPipeLines <= 0U) ||
            (createPrms->numInPipeLines > VPS_DSS_DISPC_PIPE_MAX))
        {
            GT_1trace(VpsDrvCaptTrace, GT_ERR,
                "Invalid number of input pipelines(%d)\r\n",
                createPrms->numInPipeLines);
            retVal = FVID2_EINVALID_PARAMS;
        }

        for (i = 0U; i < createPrms->numInPipeLines; i++)
        {
            if ((createPrms->inPipeLines[i] >= VPS_DSS_DISPC_PIPE_MAX) ||
                (createPrms->inPipeLines[i] == VPS_DSS_DISPC_PIPE_WB))
            {
                GT_1trace(VpsDrvCaptTrace, GT_ERR,
                    "Invalid input pipe ID %d\r\n", createPrms->inPipeLines[i]);
                retVal = FVID2_EINVALID_PARAMS;
            }

#if defined (SOC_TDA3XX)
            if (createPrms->inPipeLines[i] == VPS_DSS_DISPC_PIPE_VID3)
            {
                GT_1trace(VpsDrvCaptTrace, GT_ERR,
                    "TDA3xx doesn't support input pipe ID %d\r\n",
                    createPrms->inPipeLines[i]);
                retVal = FVID2_EINVALID_PARAMS;
            }
#endif
        }

        if ((createPrms->inQueueLength <= 0U) ||
            (createPrms->inQueueLength > VPS_M2M_DSS_DEF_QUEUE_LEN))
        {
            GT_1trace(VpsDrvCaptTrace, GT_ERR,
                "Invalid in queue length %d\r\n", createPrms->inQueueLength);
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvDssAllocHandleObj
 *  Allocates handle object and all other memories of the handle like handle
 *  queues etc.
 *  Returns the handle object pointer on success else returns NULL.
 */
VpsMDrv_DssHandleObj *vpsMdrvDssAllocHandleObj(
    VpsMDrv_DssInstObj           *instObj,
    const Vps_M2mDssCreateParams *createPrms,
    const Fvid2_DrvCbParams      *fdmCbPrms)
{
    Int32                   retVal = FVID2_SOK;
    UInt32                  qCnt;
    VpsMDrv_DssQueueObj    *qObj;
    VpsMDrv_DssHandleObj   *hObj = NULL;

    /* NULL pointer check */
    if ((NULL == createPrms) ||
        (NULL == instObj) ||
        (NULL == fdmCbPrms))
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Allocate handle memory */
        hObj = (VpsMDrv_DssHandleObj *) BspUtils_alloc(
            &gVpsMDrvDssCommonObj.handlePoolPrm,
            sizeof (VpsMDrv_DssHandleObj),
            VpsMDrvDssTrace);
        if (NULL == hObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR,
                      "Handle object memory alloc failed!!\r\n");
            retVal = FVID2_EALLOC;
        }
        else
        {
            BspUtils_memset(hObj, 0x0, sizeof (VpsMDrv_DssHandleObj));
            hObj->instObj = instObj;
            VpsM2mDssParams_init(&hObj->dssPrms);
        }
    }

    /* Create Queues */
    if (FVID2_SOK == retVal)
    {
        /* Create Output Queue for the completed frames
         * and freeQ for the free queue objects */
        retVal = BspUtils_constructQ(&hObj->freeLlObj);
        GT_assert(VpsMDrvDssTrace, (retVal == BSP_SOK));
        hObj->freeQ = &hObj->freeLlObj;

        retVal = BspUtils_constructQ(&hObj->outLlObj);
        GT_assert(VpsMDrvDssTrace, (retVal == BSP_SOK));
        hObj->outQ = &hObj->outLlObj;
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate queue object memory and queue them to free queue */
        for (qCnt = 0U; qCnt < createPrms->inQueueLength; qCnt++)
        {
            /* Assign queue object memory */
            qObj = &hObj->m2mDssQObj[qCnt];
            /* Enqueue queue object to free queue of handle */
            qObj->hObj = hObj;
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy create parameters in handle object */
        BspUtils_memcpy(
            &hObj->createPrms, createPrms, sizeof (hObj->createPrms));

        /* Copy the callback params */
        BspUtils_memcpy(&hObj->fdmCbPrms, fdmCbPrms, sizeof (hObj->fdmCbPrms));
    }
    else /* Deallocate if error occurs */
    {
        if (NULL != hObj)
        {
            vpsMdrvDssFreeHandleObj(hObj);
            hObj = NULL;
        }
    }

    return (hObj);
}

/**
 *  vpsMdrvDssFreeHandleObj
 *  Frees the handle object and all other memories of the handle like handle
 *  objects, queues etc.
 */
Int32 vpsMdrvDssFreeHandleObj(VpsMDrv_DssHandleObj *hObj)
{
    Int32                 retVal = FVID2_SOK;
    volatile UInt32       qObjCnt;
    VpsMDrv_DssQueueObj *qObj = NULL;

    /* NULL pointer check */
    if (NULL == hObj)
    {
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        if (NULL != hObj->outQ)
        {
            /* Output queue must be empty
             * asserting here since numPendReq checks for the un-dequeued
             * frames. numPendReq and size of the outQ are same. */
            GT_assert(VpsMDrvDssTrace,
                      ((UInt32) TRUE == BspUtils_isQEmpty(hObj->outQ)));

            /* Delete the output/done Q */
            BspUtils_destructQ(hObj->outQ);
            hObj->outQ = NULL;
        }

        if (NULL != hObj->freeQ)
        {
            qObjCnt = 0U;
            /* Free-up all the queued free queue objects */
            while (1U)
            {
                qObj = (VpsMDrv_DssQueueObj *) BspUtils_dequeue(hObj->freeQ);
                if ((qObjCnt >= hObj->createPrms.inQueueLength) ||
                    (NULL == qObj))
                {
                    /* No more in queue or QObject is not null, but all
                     * enqueued elements are dequeued */
                    break;
                }

                /* Free queue object memory */
                BspUtils_memset(qObj, 0x0, sizeof (VpsMDrv_DssQueueObj));
                qObj = NULL;

                qObjCnt++;
            }
            /* QObject should be null, otherwise, request queue has
             * more element than allocated */
            GT_assert(VpsMDrvDssTrace, (NULL == qObj));

            /* Delete the free Queue */
            BspUtils_destructQ(hObj->freeQ);
            hObj->freeQ = NULL;
        }

        /* Free handle object memory */
        BspUtils_free(
            &gVpsMDrvDssCommonObj.handlePoolPrm,
            (void *) hObj,
            VpsMDrvDssTrace);

        /* Reset the variables */
        hObj->instObj = NULL;
        hObj->fdmCbPrms.fdmCbFxn    = NULL;
        hObj->fdmCbPrms.fdmData     = NULL;
        hObj->fdmCbPrms.fdmErrCbFxn = NULL;
        hObj->fdmCbPrms.handle      = NULL;
        hObj->fdmCbPrms.errList     = NULL;
    }

    return (retVal);
}

VpsCore_Handle vpsMdrvDssGetInCoreHandle(const VpsMDrv_DssHandleObj *hObj,
                                         UInt32 inPipeId)
{
    UInt32         pipeCnt;
    VpsCore_Handle coreHandle = NULL;

    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    GT_assert(VpsMDrvDssTrace, (NULL != hObj->instObj));

    for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
    {
        if (hObj->createPrms.inPipeLines[pipeCnt] == inPipeId)
        {
            coreHandle = hObj->instObj->inCoreHandle[pipeCnt];
            break;
        }
    }

    return (coreHandle);
}
