/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file vpsdrv_displayPriv.c
 *
 *  \brief File containing the VPS display driver functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <dispdrv/src/vpsdrv_displayPriv.h>
#include <ti/drv/vps/include/vps_cfgMem.h>

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

VpsDrv_DispCommonObj gVpsDispCommonObj;
VpsDrv_DispInstObj   gVpsDispInstObj[VPS_CFG_MEM_DSS_NUM_FWD_PIPE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS display driver private init function.
 */
Int32 vpsDrvDispPrivInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    VpsDrv_DispInstObj   *instObj;
    VpsDrv_DispCommonObj *pObj;
    Int32  initValue;

    /* Check for errors */
    GT_assert(VpsDrvDispTrace, (numInst <= VPS_DISP_INST_MAX));
    GT_assert(VpsDrvDispTrace, (NULL != initPrms));

    /* Init common object */
    pObj = &gVpsDispCommonObj;
    BspUtils_memset(pObj, 0, sizeof (VpsDrv_DispCommonObj));

    /* Initialize instance object members */
    if (numInst > VPS_CFG_MEM_DSS_NUM_FWD_PIPE)
    {
        /* numInst exceeds the global var used to store the instObj */
        GT_0trace(VpsDrvDispTrace, GT_ERR,
                  "numInst exceeds the global instObj array size!!\r\n");
        retVal = FVID2_EALLOC;
    }
    else
    {
        pObj->instObj = &gVpsDispInstObj[0];
        BspUtils_memset(pObj->instObj, 0, sizeof (gVpsDispInstObj));
    }

    if (FVID2_SOK == retVal)
    {
        pObj->numInst = numInst;
        instObj       = pObj->instObj;
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Copy the information */
            instObj->drvInstId   = initPrms->drvInstId;
            instObj->coreInstObj = initPrms->coreInstObj;
            instObj->coreOps     = initPrms->coreOps;

            /* Allocate instance semaphore */
            initValue        = 1;
            instObj->lockSem = BspOsal_semCreate(initValue, FALSE);
            if (NULL == instObj->lockSem)
            {
                GT_0trace(VpsDrvDispTrace, GT_ERR,
                          "Instance semaphore create failed!!\r\n");
                retVal = FVID2_EALLOC;
                break;
            }

            instObj->state.isInit    = (UInt32) TRUE;
            instObj->state.isOpened  = (UInt32) FALSE;
            instObj->state.isStarted = (UInt32) FALSE;

            initPrms++;
            instObj++;
        }
    }

    if (FVID2_SOK != retVal)
    {
        /* Uninitialize the internal objects if error occurs */
        vpsDrvDispPrivDeInit();
    }

    return (retVal);
}

/**
 *  \brief VPS displaydisplay driver private deinit function.
 */
Int32 vpsDrvDispPrivDeInit(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    VpsDrv_DispInstObj   *instObj;
    VpsDrv_DispCommonObj *pObj;

    pObj = &gVpsDispCommonObj;
    if (NULL != pObj->instObj)
    {
        instObj = pObj->instObj;
        for (instCnt = 0U; instCnt < pObj->numInst; instCnt++)
        {
            if (instObj->state.isOpened == TRUE)
            {
                GT_0trace(VpsDrvDispTrace, GT_ERR,
                          "Can't deinit when an instance is active\r\n");
                retVal = FVID2_EFAIL;
                break;
            }

            /* Delete the instance semaphore */
            if (NULL != instObj->lockSem)
            {
                BspOsal_semDelete(&instObj->lockSem);
                instObj->lockSem = NULL;
            }

            instObj->state.isInit = (UInt32) FALSE;
            BspUtils_memset(pObj->instObj, 0, sizeof (VpsDrv_DispInstObj));

            instObj++;
        }
        if (retVal == FVID2_SOK)
        {
            pObj->instObj = NULL;
            pObj->numInst = 0U;
        }
    }
    return (retVal);
}

/**
 *  vpsDrvDispGetInstObj
 *  Returns the instance object pointer for the instance id.
 */
VpsDrv_DispInstObj *vpsDrvDispGetInstObj(UInt32 instId)
{
    UInt32 instCnt;
    VpsDrv_DispInstObj *instObj = NULL;
    VpsDrv_DispCommonObj *pObj;

    /* Find out the instance */
    pObj = &gVpsDispCommonObj;
    GT_assert(VpsDrvDispTrace, (NULL != pObj));
    GT_assert(VpsDrvDispTrace, (NULL != pObj->instObj));
    for (instCnt = 0U; instCnt < pObj->numInst; instCnt++)
    {
        if ((TRUE == pObj->instObj[instCnt].state.isInit) &&
            (pObj->instObj[instCnt].drvInstId == instId))
        {
            instObj = &pObj->instObj[instCnt];
            break;
        }
    }

    return (instObj);
}

/**
 *  vpsDrvDispCheckParams
 *  Checks for valid create parameters.
 */
Int32 vpsDrvDispCheckParams(const VpsDrv_DispInstObj   *instObj,
                            const Vps_DispCreateParams *createPrms)
{
    Int32 retVal = FVID2_SOK;

    /* NULL pointer check */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != createPrms));

    if (createPrms->instInQueueLength <= 0U)
    {
        GT_1trace(VpsDrvDispTrace, GT_ERR,
                  "Invalid in queue length(%d)\r\n",
                  createPrms->instInQueueLength);
        retVal = FVID2_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_006)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-774)
 */
Int32 vpsDrvDispCreateInstObj(VpsDrv_DispInstObj *instObj)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 qCnt;
    VpsDrv_DispBufManObj *bmObj;
    VpsDrv_DispQueObj    *qObj;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    bmObj = &instObj->bmObj;

    instObj->bufPrgmCbFxn        = NULL;
    instObj->stat.queueCount     = 0U;
    instObj->stat.dequeueCount   = 0U;
    instObj->stat.dispFrmCount   = 0U;
    instObj->stat.repeatFrmCount = 0U;

    bmObj->isProgressive         = (UInt32) TRUE;
    bmObj->bypassLowLatencyCheck = (UInt32) FALSE;
    bmObj->curFid      = 0U;
    bmObj->expectedFid = 0U;
    bmObj->fieldMerged = (UInt32) TRUE;
    bmObj->freeQ       = NULL;
    bmObj->reqQ        = NULL;
    bmObj->curQ        = NULL;
    bmObj->doneQ       = NULL;

    /* Create Queues */
    retVal = BspUtils_constructQ(&bmObj->freeLlObj);
    GT_assert(VpsDrvDispTrace, (retVal == BSP_SOK));
    bmObj->freeQ = &bmObj->freeLlObj;

    retVal = BspUtils_constructQ(&bmObj->reqLlObj);
    GT_assert(VpsDrvDispTrace, (retVal == BSP_SOK));
    bmObj->reqQ = &bmObj->reqLlObj;

    retVal = BspUtils_constructQ(&bmObj->curLlObj);
    GT_assert(VpsDrvDispTrace, (retVal == BSP_SOK));
    bmObj->curQ = &bmObj->curLlObj;

    retVal = BspUtils_constructQ(&bmObj->doneLlObj);
    GT_assert(VpsDrvDispTrace, (retVal == BSP_SOK));
    bmObj->doneQ = &bmObj->doneLlObj;

    if (retVal == FVID2_SOK)
    {
        if (instObj->createPrms.instInQueueLength >
            BSP_CFG_DISP_QUEUE_LEN_PER_INST)
        {
            GT_2trace(
                VpsDrvDispTrace, GT_ERR,
                "Cant create %d display queue objects!!. Maximum supported display queue objects are %d\r\n",
                instObj->createPrms.instInQueueLength,
                VPS_DISP_DEF_QUEUE_LEN_PER_INST);
            retVal = FVID2_EALLOC;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Initialize and queue the allocate queue object to free Q */
        for (qCnt = 0U; qCnt < instObj->createPrms.instInQueueLength; qCnt++)
        {
            qObj          = &bmObj->dispQObj[qCnt];
            qObj->instObj = instObj;
            qObj->frm     = NULL;
            BspUtils_memset(&qObj->coreFrm, 0, sizeof (qObj->coreFrm));
            qObj->coreFrm.streamId  = 0U;
            qObj->coreFrm.chId      = 0U;
            qObj->coreFrm.dropFrm   = (UInt32) FALSE;
            qObj->coreFrm.drvData   = qObj;
            qObj->coreFrm.coreStats = NULL;
            qObj->coreFrm.rtParams  = NULL;
            qObj->creditCnt         = 0U;

            BspUtils_queue(bmObj->freeQ, &qObj->qElem, qObj);
        }
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        tempRetVal = vpsDrvDispDeleteInstObj(instObj);
        GT_assert(VpsDrvDispTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

Int32 vpsDrvDispDeleteInstObj(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_DispQueObj    *qObj;
    VpsDrv_DispBufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    bmObj = &instObj->bmObj;

    bmObj->isProgressive = (UInt32) TRUE;
    bmObj->curFid        = 0U;
    bmObj->expectedFid   = 0U;
    bmObj->fieldMerged   = (UInt32) TRUE;

    if (NULL != bmObj->freeQ)
    {
        /* Free-up all the queued free queue objects */
        while (1U)
        {
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->freeQ);
            if (NULL == qObj)
            {
                /* No more in queue */
                break;
            }
        }

        /* Delete the free Q */
        BspUtils_destructQ(bmObj->freeQ);
        bmObj->freeQ = NULL;
    }

    if (NULL != bmObj->reqQ)
    {
        /* Free-up all object from request queue */
        while (1U)
        {
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->reqQ);
            if (NULL == qObj)
            {
                /* No more in queue */
                break;
            }
        }

        /* Delete the request Q */
        BspUtils_destructQ(bmObj->reqQ);
        bmObj->reqQ = NULL;
    }

    if (NULL != bmObj->curQ)
    {
        /* Free-up all object from current queue */
        while (1U)
        {
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->curQ);
            if (NULL == qObj)
            {
                /* No more in queue */
                break;
            }
        }

        /* Delete the free Q */
        BspUtils_destructQ(bmObj->curQ);
        bmObj->curQ = NULL;
    }

    if (NULL != bmObj->doneQ)
    {
        /* Free-up all object from done queue */
        while (1U)
        {
            qObj = (VpsDrv_DispQueObj *) BspUtils_dequeue(bmObj->doneQ);
            if (NULL == qObj)
            {
                /* No more in queue */
                break;
            }
        }

        /* Delete the done Q */
        BspUtils_destructQ(bmObj->doneQ);
        bmObj->doneQ = NULL;
    }

    return (retVal);
}

