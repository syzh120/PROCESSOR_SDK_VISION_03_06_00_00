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
 *  \file vpsdrv_capturePriv.c
 *
 *  \brief File containing the VPS capture driver functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <captdrv/src/vpsdrv_capturePriv.h>
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

static Int32 vpsDrvCaptCreateChQueues(const VpsDrv_CaptInstObj *instObj,
                                      VpsDrv_CaptChObj         *chObj);
static Int32 vpsDrvCaptDeleteChQueues(VpsDrv_CaptChObj *chObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

VpsDrv_CaptCommonObj gVpsCaptCommonObj;
VpsDrv_CaptInstObj   gVpsCaptInstObj[VPS_CFG_CAPT_NUM_INST_OBJS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS VIP capture driver private init function.
 */
Int32 vpsDrvCaptPrivInit(UInt32 numInst, const VpsDrv_CaptInitParams *initPrms)
{
    Int32  retVal = FVID2_SOK, initValue;
    UInt32 instCnt;
    VpsDrv_CaptInstObj   *instObj;
    VpsDrv_CaptCommonObj *pObj;

    /* Check for errors */
    GT_assert(VpsDrvCaptTrace, (numInst <= VPS_CFG_CAPT_NUM_INST_OBJS));
    GT_assert(VpsDrvCaptTrace, (NULL != initPrms));

    /* Init common object */

    pObj = &gVpsCaptCommonObj;
    BspUtils_memset(pObj, 0, sizeof (VpsDrv_CaptCommonObj));
    if (numInst > VPS_CFG_CAPT_NUM_INST_OBJS)
    {
        /* numInst exceeds the global var used to store the instObj */
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "numInst exceeds the global instObj array size!!\r\n");
        retVal = FVID2_EALLOC;
    }
    else
    {
        /* Initialize instance object members */
        pObj->instObj = &gVpsCaptInstObj[0];
        BspUtils_memset(pObj->instObj, 0, sizeof (gVpsCaptInstObj));
    }

    if (FVID2_SOK == retVal)
    {
        pObj->numInst = numInst;
        instObj       = pObj->instObj;
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Core should be present */
            GT_assert(VpsDrvCaptTrace, (NULL != initPrms->coreOps));

            /* Copy the information */
            instObj->drvInstId   = initPrms->drvInstId;
            instObj->coreInstObj = initPrms->coreInstObj;
            instObj->coreOps     = initPrms->coreOps;

            initValue = 1;
            /* Allocate instance semaphore */
            instObj->lockSem = BspOsal_semCreate(initValue, FALSE);
            if (NULL == instObj->lockSem)
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "Instance semaphore create failed!!\r\n");
                retVal = FVID2_EALLOC;
                break;
            }

            instObj->state        = VPS_CAPT_STATE_IDLE;
            instObj->getTimeStamp = &vpsDrvCaptClockGetTicks;

            initPrms++;
            instObj++;
        }
    }

    if (FVID2_SOK != retVal)
    {
        /* Uninitialize the internal objects if error occurs */
        vpsDrvCaptPrivDeInit();
    }

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver private deinit function.
 */
Int32 vpsDrvCaptPrivDeInit(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    VpsDrv_CaptInstObj   *instObj;
    VpsDrv_CaptCommonObj *pObj;

    pObj = &gVpsCaptCommonObj;
    if (NULL != pObj->instObj)
    {
        instObj = pObj->instObj;
        for (instCnt = 0U; instCnt < pObj->numInst; instCnt++)
        {
            if (instObj->state != VPS_CAPT_STATE_IDLE)
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
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
            BspUtils_memset(pObj->instObj, 0, sizeof (VpsDrv_CaptInstObj));

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
 *  vpsDrvCaptGetInstObj
 *  Returns the instance object pointer for the instance id.
 */
VpsDrv_CaptInstObj *vpsDrvCaptGetInstObj(UInt32 instId)
{
    UInt32 instCnt;
    VpsDrv_CaptInstObj *instObj = NULL;
    VpsDrv_CaptCommonObj *pObj;

    /* Find out the instance to which this channel belongs to */
    pObj = &gVpsCaptCommonObj;
    GT_assert(VpsDrvCaptTrace, (NULL != pObj));
    GT_assert(VpsDrvCaptTrace, (NULL != pObj->instObj));
    for (instCnt = 0U; instCnt < pObj->numInst; instCnt++)
    {
        if (pObj->instObj[instCnt].drvInstId == instId)
        {
            instObj = &pObj->instObj[instCnt];
            break;
        }
    }

    return (instObj);
}

/**
 *  vpsDrvCaptCheckParams
 *  Checks for valid create parameters.
 */
Int32 vpsDrvCaptCheckParams(const VpsDrv_CaptInstObj   *instObj,
                            const Vps_CaptCreateParams *createPrms)
{
    Int32 retVal = FVID2_SOK;

    /* NULL pointer check */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != createPrms));

    if (createPrms->chInQueueLength <= 0U)
    {
        GT_1trace(
            VpsDrvCaptTrace, GT_ERR,
            "Invalid in queue length(%d)\r\n",
            createPrms->chInQueueLength);
        retVal = FVID2_EINVALID_PARAMS;
    }

    if ((createPrms->numCh > VPS_CAPT_CH_PER_PORT_MAX) ||
        (createPrms->numCh <= 0U))
    {
        GT_2trace(
            VpsDrvCaptTrace, GT_ERR,
            "Invalid number of channels(%d) - Supported max channels %d\r\n",
            createPrms->numCh,
            VPS_CAPT_CH_PER_PORT_MAX);
        retVal = FVID2_EINVALID_PARAMS;
    }

    if ((createPrms->numStream > VPS_CAPT_STREAM_ID_MAX) ||
        (createPrms->numStream <= 0U))
    {
        GT_2trace(
            VpsDrvCaptTrace, GT_ERR,
            "Invalid number of streams(%d) - Supported max streams %d\r\n",
            createPrms->numStream,
            VPS_CAPT_STREAM_ID_MAX);
        retVal = FVID2_EINVALID_PARAMS;
    }

    if (createPrms->bufCaptMode >= VPS_CAPT_BCM_MAX)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid buffer capture mode\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    return (retVal);
}

Int32 vpsDrvCaptCreateChObj(VpsDrv_CaptInstObj *instObj)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 streamId, chId;
    VpsDrv_CaptChObj     *chObj;
    VpsDrv_CaptCommonObj *pObj;

    pObj = &gVpsCaptCommonObj;
    GT_assert(VpsDrvCaptTrace, (NULL != pObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));

    /* For every stream and every channel */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
        {
            /* Get channel object */
            chObj = &instObj->chObj[streamId][chId];

            /* Make driver channel number from instance ID, stream ID,
             * thus given driver channel number we can know which
             * instance, stream, channel it belongs to chId */
            chObj->lChNum =
                Vps_captMakeChNum(instObj->drvInstId, streamId, chId);
            chObj->chNum = instObj->createPrms.chNumMap[streamId][chId];

            /* Make user channel number to driver channel number mapping */
            pObj->fvidChNumToLogChNumMap[chObj->chNum] = chObj->lChNum;

            /* Init other variables */
            chObj->instObj  = instObj;
            chObj->streamId = streamId;
            chObj->chIdx    = chId;
            /* Don't skip any frames */
            chObj->frmSkipMask      = 0U;
            chObj->frmSkipCount     = 0U;
            chObj->isStreamByPassed = (UInt32) FALSE;

#ifdef VPS_VIP_BUILD
            chObj->vemSubFrmHandle                = NULL;
            chObj->subFrameNum                    = 0U;
            chObj->subFrmPrms.subFrameEnable      = (UInt32) FALSE;
            chObj->subFrmPrms.numLinesPerSubFrame = 0U;
            chObj->subFrmPrms.interruptMode       =
                VPS_INTR_END_OF_EVERY_NTH_LINE;
            chObj->subFrmPrms.subFrameCb = NULL;
#endif      /* VPS_VIP_BUILD */

            BspUtils_memset(&chObj->stat, 0, sizeof (chObj->stat));

            /* Create channel queues */
            retVal = vpsDrvCaptCreateChQueues(instObj, chObj);
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        tempRetVal = vpsDrvCaptDeleteChObj(instObj);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

Int32 vpsDrvCaptDeleteChObj(VpsDrv_CaptInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId, chId;
    VpsDrv_CaptChObj *chObj;

    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));

    /* For every stream and every channel */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0; chId < instObj->createPrms.numCh; chId++)
        {
            chObj  = &instObj->chObj[streamId][chId];
            retVal = vpsDrvCaptDeleteChQueues(chObj);

#ifdef VPS_VIP_BUILD
            if ((NULL != chObj->vemSubFrmHandle) &&
                (FVID2_SOK == retVal))
            {
                retVal = Vem_unRegister(chObj->vemSubFrmHandle);
                if (FVID2_SOK == retVal)
                {
                    chObj->vemSubFrmHandle = NULL;
                }
            }
#endif      /* VPS_VIP_BUILD */

            if (FVID2_SOK != retVal)
            {
                break;
            }
        }

        /* Break if error */
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  \brief A simple wrapper function for DSP/BIOS clock get ticks.
 */
UInt64 vpsDrvCaptClockGetTicks(void *args)
{
    return BspOsal_getCurTimeInUsec();
}

static Int32 vpsDrvCaptCreateChQueues(const VpsDrv_CaptInstObj *instObj,
                                      VpsDrv_CaptChObj         *chObj)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 qCnt, plCnt;
    VpsDrv_CaptQueObj    *qObj;
    VpsDrv_CaptBufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != chObj));
    bmObj = &chObj->bmObj;

    bmObj->freeQ         = NULL;
    bmObj->reqQ          = NULL;
    bmObj->curQ          = NULL;
    bmObj->isProgressive = (UInt32) TRUE;
    bmObj->bufFmt        = FVID2_BUF_FMT_FRAME;
    bmObj->fieldMerged   = (UInt32) TRUE;
    bmObj->curFid        = 0U;
    bmObj->expectedFid   = 0U;
    BspUtils_memset(&bmObj->dropCoreFrm, 0, sizeof (bmObj->dropCoreFrm));
    bmObj->dropCoreFrm.streamId = chObj->streamId;
    bmObj->dropCoreFrm.chId     = chObj->chIdx;
    for (plCnt = 0U; plCnt < FVID2_MAX_PLANES; plCnt++)
    {
        bmObj->dropCoreFrm.addr[0][plCnt] = NULL;
    }
    bmObj->dropCoreFrm.dropFrm = (UInt32) TRUE;
    bmObj->dropCoreFrm.drvData = NULL;
    bmObj->dropCoreFrm.fid     = FVID2_FID_TOP;

#ifdef VPS_VIP_BUILD
    BspUtils_memset(
        &bmObj->vipCoreStatDropFrm,
        0,
        sizeof (bmObj->vipCoreStatDropFrm));
    bmObj->dropCoreFrm.coreStats = NULL;
    if (VPSCORE_CAPT_VIP == instObj->coreProperty.name)
    {
        bmObj->dropCoreFrm.coreStats = &bmObj->vipCoreStatDropFrm;
    }
#endif /* VPS_VIP_BUILD */

    /* Create Queues */
    retVal = BspUtils_constructQ(&bmObj->freeLlObj);
    GT_assert(VpsDrvCaptTrace, (retVal == BSP_SOK));
    bmObj->freeQ = &bmObj->freeLlObj;

    retVal = BspUtils_constructQ(&bmObj->reqLlObj);
    GT_assert(VpsDrvCaptTrace, (retVal == BSP_SOK));
    bmObj->reqQ = &bmObj->reqLlObj;

    retVal = BspUtils_constructQ(&bmObj->curLlObj);
    GT_assert(VpsDrvCaptTrace, (retVal == BSP_SOK));
    bmObj->curQ = &bmObj->curLlObj;

    if (FVID2_SOK == retVal)
    {
        if (instObj->createPrms.chInQueueLength > BSP_CFG_CAPT_QUEUE_LEN_PER_CH)
        {
            GT_2trace(
                VpsDrvCaptTrace, GT_ERR,
                "Cant create %d capture queue objects!!. Maximum supported capture queue objects are %d\r\n",
                instObj->createPrms.chInQueueLength,
                VPS_CAPT_DEF_QUEUE_LEN_PER_CH);
            retVal = FVID2_EALLOC;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Initialize and queue the allocate queue object to free Q */
        for (qCnt = 0U; qCnt < instObj->createPrms.chInQueueLength; qCnt++)
        {
            qObj        = &bmObj->captQObj[qCnt];
            qObj->chObj = chObj;
            qObj->frm   = NULL;
            BspUtils_memset(&qObj->coreFrm, 0, sizeof (qObj->coreFrm));
            qObj->coreFrm.streamId = chObj->streamId;
            qObj->coreFrm.chId     = chObj->chIdx;
            qObj->coreFrm.dropFrm  = (UInt32) FALSE;
            qObj->coreFrm.rtParams = NULL;
            qObj->coreFrm.drvData  = qObj;

#ifdef VPS_VIP_BUILD
            BspUtils_memset(&qObj->vipCoreStat, 0, sizeof (qObj->vipCoreStat));
            qObj->coreFrm.coreStats = NULL;
            if (VPSCORE_CAPT_VIP == instObj->coreProperty.name)
            {
                qObj->coreFrm.coreStats = &qObj->vipCoreStat;
            }
#endif      /* VPS_VIP_BUILD */
            qObj->creditCnt = 0U;

            BspUtils_queue(bmObj->freeQ, &qObj->qElem, qObj);
        }
    }

    /* Deallocate if error occurs */
    if (FVID2_SOK != retVal)
    {
        tempRetVal = vpsDrvCaptDeleteChQueues(chObj);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

static Int32 vpsDrvCaptDeleteChQueues(VpsDrv_CaptChObj *chObj)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CaptQueObj    *qObj;
    VpsDrv_CaptBufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(VpsDrvCaptTrace, (NULL != chObj));
    bmObj = &chObj->bmObj;

    if (NULL != bmObj->freeQ)
    {
        /* Free-up all the queued free queue objects */
        while (1U)
        {
            qObj = (VpsDrv_CaptQueObj *) BspUtils_dequeue(bmObj->freeQ);
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
        /* Delete the request Q */
        BspUtils_destructQ(bmObj->reqQ);
        bmObj->reqQ = NULL;
    }

    if (NULL != bmObj->curQ)
    {
        /* Delete the free Q */
        BspUtils_destructQ(bmObj->curQ);
        bmObj->curQ = NULL;
    }

    return (retVal);
}

