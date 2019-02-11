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
 *  \file vpsdrv_m2mDssProc.c
 *
 *  \brief VPS DSS M2M driver process file.
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
 *  \brief Extern function to be implemented by driver to provide a new frame
 *  buffers from application to the core.
 */
VpsCore_Frame *vpsMdrvDssInCoreReqFrameCb(void  *drvData,
                                          UInt32 streamId,
                                          UInt32 chId)
{
    UInt32                  cookie, coreIdx, frmIdx;
    VpsCore_Frame          *coreFrm = NULL;
    Fvid2_Frame            *inFrm;
    VpsMDrv_DssInstObj     *instObj;
    VpsMDrv_DssCoreDrvData *coreDrvData;

    coreDrvData = (VpsMDrv_DssCoreDrvData *) drvData;
    GT_assert(VpsMDrvDssTrace, (NULL != coreDrvData));
    instObj = coreDrvData->instObj;
    GT_assert(VpsMDrvDssTrace, (NULL != instObj));
    GT_assert(VpsMDrvDssTrace, (streamId == 0U));
    GT_assert(VpsMDrvDssTrace, (chId == 0U));

    cookie = BspOsal_disableInterrupt();

    GT_assert(VpsMDrvDssTrace, (NULL != instObj->activeQObj));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->activeQObj->hObj));
    GT_assert(VpsMDrvDssTrace,
        (coreDrvData->pipeIdx <
            instObj->activeQObj->hObj->createPrms.numInPipeLines));
    frmIdx = coreDrvData->pipeIdx;
    coreIdx = coreDrvData->pipeIdx;
    inFrm   = instObj->activeQObj->inFrmList.frames[coreIdx];
    coreFrm = &instObj->activeQObj->coreFrm[frmIdx];
    coreFrm->addr[0][0] = inFrm->addr[0][0];
    coreFrm->addr[0][1] = inFrm->addr[0][1];
    coreFrm->addr[0][2] = inFrm->addr[0][2];
    coreFrm->addr[1][0] = inFrm->addr[1][0];
    coreFrm->addr[1][1] = inFrm->addr[1][1];
    coreFrm->addr[1][2] = inFrm->addr[1][2];
    coreFrm->rtParams   = inFrm->perFrameCfg;

    BspOsal_restoreInterrupt(cookie);

    GT_assert(VpsMDrvDssTrace, (NULL != coreFrm));
    return (coreFrm);
}

VpsCore_Frame *vpsMdrvDssOutCoreReqFrameCb(void  *drvData,
                                           UInt32 streamId,
                                           UInt32 chId)
{
    UInt32              cookie, frmIdx;
    VpsMDrv_DssInstObj *instObj;
    VpsCore_Frame      *coreFrm = NULL;
    Fvid2_Frame        *outFrm;

    instObj = (VpsMDrv_DssInstObj *) drvData;
    GT_assert(VpsMDrvDssTrace, (NULL != instObj) );
    GT_assert(VpsMDrvDssTrace, (streamId == 0U));
    GT_assert(VpsMDrvDssTrace, (chId == 0U));

    cookie = BspOsal_disableInterrupt();

    GT_assert(VpsMDrvDssTrace, (NULL != instObj->activeQObj));
    frmIdx  = VPS_DSS_DISPC_PIPE_MAX - 1U;                  /* Always last */
    outFrm  = instObj->activeQObj->outFrmList.frames[0U];   /* Always first */
    coreFrm = &instObj->activeQObj->coreFrm[frmIdx];
    coreFrm->addr[0][0] = outFrm->addr[0][0];
    coreFrm->addr[0][1] = outFrm->addr[0][1];
    coreFrm->addr[0][2] = outFrm->addr[0][2];
    coreFrm->addr[1][0] = outFrm->addr[1][0];
    coreFrm->addr[1][1] = outFrm->addr[1][1];
    coreFrm->addr[1][2] = outFrm->addr[1][2];
    coreFrm->rtParams   = outFrm->perFrameCfg;

    BspOsal_restoreInterrupt(cookie);

    GT_assert(VpsMDrvDssTrace, (NULL != coreFrm));
    return (coreFrm);
}

/** \brief Frame Done callback */
Int32 vpsMdrvDssFrmDoneCb(void *drvData, const VpsCore_Frame *frm)
{
    Int32                   retVal;
    UInt32                  cookie, pipeCnt;
    VpsMDrv_DssHandleObj   *hObj, *hObjNew;
    VpsMDrv_DssInstObj     *instObj = (VpsMDrv_DssInstObj *) drvData;
    VpsMDrv_DssQueueObj    *qObj;

    /* NULL pointer check */
    GT_assert(VpsMDrvDssTrace, (NULL != instObj));
    qObj = instObj->activeQObj;
    GT_assert(VpsMDrvDssTrace, (NULL != qObj));
    hObj = qObj->hObj;
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));

    cookie = BspOsal_disableInterrupt();

    /* Move completed request to output queue */
    hObj->numProcessedReq++;
    BspUtils_queue(hObj->outQ, &qObj->qElem, qObj);
    instObj->activeQObj = NULL;

    /* Stop all cores */
    for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
    {
        /* NULL pointer check */
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->stop));

        retVal = instObj->inCoreOps->stop(instObj->inCoreHandle[pipeCnt]);
        GT_assert(VpsMDrvDssTrace, (FVID2_SOK == retVal));
    }
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps->stop));
    retVal = instObj->outCoreOps->stop(instObj->outCoreHandle);
    GT_assert(VpsMDrvDssTrace, (FVID2_SOK == retVal));

    /* Check for any new requests */
    qObj = (VpsMDrv_DssQueueObj *) BspUtils_dequeue(instObj->inQueue);
    if (NULL == qObj)
    {
        GT_0trace(VpsMDrvDssTrace, GT_DEBUG, "No More Buffer to process!!\r\n");
    }
    else
    {
        /* There are more request pending for this instance
         * Ensure to use the handle that this request is associated with */
        GT_assert(VpsMDrvDssTrace, (NULL != qObj->hObj));
        hObjNew = qObj->hObj;

        /* Driver specific submit request */
        instObj->activeQObj = qObj;
        retVal = vpsMdrvDssProcessReq(instObj, qObj);
        if (FVID2_SOK != retVal)
        {
            /* Free the request */
            /* TODO: Set status as fail */
            hObjNew->numProcessedReq++;
            BspUtils_queue(hObjNew->outQ, &qObj->qElem, qObj);
            instObj->activeQObj = NULL;
        }
    }

    BspOsal_restoreInterrupt(cookie);

    /* Calling application callback at the last, so that if there is
     * any request in the input queue, it can be submitted before calling
     * this callback, this can maximize hardware usage. */
    retVal = hObj->fdmCbPrms.fdmCbFxn(hObj->fdmCbPrms.fdmData, NULL);

    return (FVID2_SOK);
}

Int32 vpsMdrvDssProcessReq(VpsMDrv_DssInstObj *instObj,
                           const VpsMDrv_DssQueueObj *qObj)
{
    Int32                   retVal = FVID2_SOK, tempRetVal;
    UInt32                  pipeCnt, numInPipesStarted = 0U;
    VpsMDrv_DssHandleObj   *hObj;

    /* NULL pointer check */
    GT_assert(VpsMDrvDssTrace, (NULL != instObj));
    GT_assert(VpsMDrvDssTrace, (NULL != qObj));
    hObj = qObj->hObj;
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));

    /* Start all input cores */
    for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
    {
        /* NULL pointer check */
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->start));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreHandle[pipeCnt]));

        retVal = instObj->inCoreOps->start(instObj->inCoreHandle[pipeCnt]);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "In Core start failed!!\r\n");
            break;
        }
        numInPipesStarted++;
    }

    /* Start writeback core at the end - this triggers the WB operation */
    if (FVID2_SOK == retVal)
    {
        /* NULL pointer check */
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps->start));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreHandle));

        retVal = instObj->outCoreOps->start(instObj->outCoreHandle);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Out Core start failed!!\r\n");
        }
    }

    if (FVID2_SOK != retVal)
    {
        /* Stop all started input cores */
        for (pipeCnt = 0U; pipeCnt < numInPipesStarted; pipeCnt++)
        {
            /* NULL pointer check */
            GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->stop));

            tempRetVal =
                instObj->inCoreOps->stop(instObj->inCoreHandle[pipeCnt]);
            GT_assert(VpsMDrvDssTrace, (FVID2_SOK == tempRetVal));
        }
    }

    return (retVal);
}
