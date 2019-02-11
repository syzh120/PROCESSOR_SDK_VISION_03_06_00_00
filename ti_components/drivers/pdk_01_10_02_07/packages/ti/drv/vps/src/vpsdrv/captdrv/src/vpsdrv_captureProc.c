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
 *  \file vpsdrv_captureProc.c
 *
 *  \brief File containing the VPS capture driver process related functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <captdrv/src/vpsdrv_capturePriv.h>

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
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef VPS_VIP_BUILD

void vpsDrvCaptVemIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    Int32  retVal;
    UInt32 streamId, chId;
    VpsDrv_CaptChObj   *chObj = (VpsDrv_CaptChObj *) arg;
    VpsDrv_CaptInstObj *instObj;

    GT_assert(VpsDrvCaptTrace, (NULL != chObj));
    instObj = chObj->instObj;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreHandle));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->proc));

    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));

    retVal = instObj->coreOps->proc(instObj->coreHandle, chObj->chIdx);
    if(FVID2_SOK == retVal)
    {
        /* For every stream for this channel */
        chId = chObj->chIdx;
        for(streamId = 0U; streamId < instObj->createPrms.numStream;
            streamId++)
        {
            /* Get channel object */
            chObj = &instObj->chObj[streamId][chId];

            /* Reset subframe count every frame complete interrupt */
            chObj->subFrameNum = 0U;

            /* Increment frame count and start from 0 if it reaches to 30 as
             * frameSkipMask can have only 30 bits */
            chObj->frmSkipCount = (chObj->frmSkipCount + 1U) % 30U;
        }
    }

    return;
}

void vpsDrvCaptVemOverflowIsr(const UInt32 *event, UInt32 numEvents,
                              Ptr arg)
{
    VpsDrv_CaptInstObj    *instObj = (VpsDrv_CaptInstObj *) arg;
    Vps_CaptVipOverflowFxn appCallbackFxn;

    GT_assert(VpsDrvCaptTrace, (NULL != event));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->overflowCbFxn));

    appCallbackFxn = instObj->overflowCbFxn;
    instObj->isOverflowOccured = (UInt32) TRUE;
    appCallbackFxn(instObj->appOverFlowCbPrms);
    return;
}

void vpsDrvCaptVemSubFrmIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    Int32 retVal;
    VpsDrv_CaptChObj       *chObj = (VpsDrv_CaptChObj *) arg;
    VpsDrv_CaptQueObj      *qObj;
    VpsCore_VipSubFrameInfo vipSubFrameInfo;

    GT_assert(VpsDrvCaptTrace, (NULL != chObj));
    GT_assert(VpsDrvCaptTrace, (TRUE == chObj->subFrmPrms.subFrameEnable));
    GT_assert(VpsDrvCaptTrace, (NULL != chObj->subFrmPrms.subFrameCb));
    GT_assert(VpsDrvCaptTrace, (NULL != chObj->instObj));

    /* Get the current frame being captured */
    qObj = (VpsDrv_CaptQueObj *) BspUtils_peakHead(chObj->bmObj.curQ);
    /* qObj could be NULL for frame drop mode */
    if(NULL != qObj)
    {
        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm->subFrameInfo));

        qObj->frm->subFrameInfo->subFrameNum = chObj->subFrameNum;
        qObj->frm->subFrameInfo->numInLines  = 0U;  /* Not valid for capture */
        qObj->frm->subFrameInfo->numOutLines =
            (chObj->subFrameNum + 1) * chObj->subFrmPrms.numLinesPerSubFrame;

        /* Control call to VIP Core to get the subFrameInfo. */
        vipSubFrameInfo.streamId  = chObj->streamId;
        vipSubFrameInfo.channelId = chObj->chIdx;
        retVal = chObj->instObj->coreOps->control(
            chObj->instObj->coreHandle,
            VPSCORE_VIP_IOCTL_GET_SUBFRM_INFO,
            NULL,
            &vipSubFrameInfo);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == retVal));
        if(qObj->frm->perFrameCfg != NULL)
        {
            Vps_CaptRtParams *rtParams = (Vps_CaptRtParams *) \
                                         qObj->frm->perFrameCfg;
            rtParams->capturedOutWidth  = vipSubFrameInfo.width;
            rtParams->capturedOutHeight = vipSubFrameInfo.height;
        }

        /* Update FID only for the first sub-frame */
        if(chObj->subFrameNum == 0U)
        {
            qObj->frm->fid = vipSubFrameInfo.currFid;
        }

        /* Issue the user callback */
        retVal = chObj->subFrmPrms.subFrameCb(
                    chObj->instObj->fdmCbPrms.handle, qObj->frm);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == retVal));

        /* Move to next sub frame */
        chObj->subFrameNum++;
    }

    return;
}

#endif /* VPS_VIP_BUILD */

/**
 *  \brief Extern function to be implemented by driver to provide a new frame
 *  buffers from application to the core.
 */
VpsCore_Frame *vpsDrvCaptCoreReqFrameCb(void  *drvData,
                                        UInt32 streamId,
                                        UInt32 chId)
{
    UInt32 cookie;
    VpsDrv_CaptChObj   *chObj;
    VpsDrv_CaptInstObj *instObj;
    VpsDrv_CaptQueObj  *qObj;
    VpsCore_Frame      *coreFrm = NULL;

    instObj = (VpsDrv_CaptInstObj *) drvData;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (streamId < VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace, (chId < instObj->createPrms.numCh));

    /* Get channel specific object in the required instance */
    chObj = &instObj->chObj[streamId][chId];

    cookie = BspOsal_disableInterrupt();

    /* Check whether we need to skip this frame */
    if((VPS_CAPT_BCM_FRM_DROP == instObj->createPrms.bufCaptMode) &&
       (((chObj->frmSkipMask >> chObj->frmSkipCount) & 0x01U) != 0U))
    {
        /* Drop frames, return special core frame to the core so that the
         * core could drop frame using hardware drop data feature */
        coreFrm = &chObj->bmObj.dropCoreFrm;
    }
    else
    {
        qObj = (VpsDrv_CaptQueObj *) BspUtils_dequeue(chObj->bmObj.reqQ);
        if(NULL != qObj)
        {
            /*
             * Buffer available in request queue
             */
            /* Copy the address and increment credit */
            qObj->coreFrm.addr[0][0] = qObj->frm->addr[0][0];
            qObj->coreFrm.addr[0][1] = qObj->frm->addr[0][1];
            qObj->coreFrm.addr[0][2] = qObj->frm->addr[0][2];
            qObj->coreFrm.addr[1][0] = qObj->frm->addr[1][0];
            qObj->coreFrm.addr[1][1] = qObj->frm->addr[1][1];
            qObj->coreFrm.addr[1][2] = qObj->frm->addr[1][2];
            qObj->coreFrm.rtParams   = qObj->frm->perFrameCfg;
            qObj->coreFrm.dropFrm = (UInt32) FALSE;
            /* If app passes NULL pointer, then drop the frame */
            if (NULL == qObj->coreFrm.addr[0][0])
            {
                qObj->coreFrm.dropFrm = (UInt32) TRUE;
            }

            qObj->creditCnt++;
            coreFrm = &qObj->coreFrm;
            BspUtils_queue(chObj->bmObj.curQ, &qObj->qElem, qObj);
        }
        else
        {
            /*
             * No more buffers available in request queue - decide what to do
             * based on buffer capture mode
             */
            if(VPS_CAPT_BCM_FRM_DROP == instObj->createPrms.bufCaptMode)
            {
                /* Drop frames, return special core frame to the core so that
                 * the core could drop frame using hardware drop data feature */
                coreFrm = &chObj->bmObj.dropCoreFrm;
            }
            else if(VPS_CAPT_BCM_LAST_FRM_REPEAT ==
                    instObj->createPrms.bufCaptMode)
            {
                /* Repeat the last frame queued to the core */
                qObj = (VpsDrv_CaptQueObj *)
                       BspUtils_peakTail(chObj->bmObj.curQ);
                /* This can't return NULL unless there is a bug in the buffer
                 * management */
                GT_assert(VpsDrvCaptTrace, (NULL != qObj));
                qObj->creditCnt++;
                coreFrm = &qObj->coreFrm;
            }
            else if(VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT ==
                    instObj->createPrms.bufCaptMode)
            {
                /*
                 * Repeat the oldest frame queued to the core and make it at
                 * the last element in the current queue
                 */
                qObj = (VpsDrv_CaptQueObj *)
                       BspUtils_dequeue(chObj->bmObj.curQ);
                /* This can't return NULL unless there is a bug in the buffer
                 * management */
                GT_assert(VpsDrvCaptTrace, (NULL != qObj));
                qObj->creditCnt++;
                coreFrm = &qObj->coreFrm;

                /* Queue back to the start */
                BspUtils_queue(chObj->bmObj.curQ, &qObj->qElem, qObj);
            }
            else
            {
                GT_assert(VpsDrvCaptTrace, FALSE);
            }
        }
    }

    GT_1trace(VpsDrvCaptTrace, GT_DEBUG,
              "CaptDrv: Queued buffer 0x%0.8x to core\r\n", coreFrm->addr[0]);

    BspOsal_restoreInterrupt(cookie);

    GT_assert(VpsDrvCaptTrace, (NULL != coreFrm));
    return (coreFrm);
}

/**
 *  \brief Extern callback function to be implemented by driver to free
 *  up buffers to the application specified by the core.
 */
Int32 vpsDrvCaptCoreFrameDoneCb(void *drvData, const VpsCore_Frame *coreFrm)
{
    UInt32 cookie;
    UInt32 curQCnt, reqQCnt;
    UInt64 curTimeStamp;
    Bool   frmQueuedToDoneQ = FALSE;
    VpsDrv_CaptChObj   *chObj;
    VpsDrv_CaptInstObj *instObj;
    VpsDrv_CaptQueObj  *qObj, *qObjTemp;
    Vps_CaptRtParams   *rtPrms;
    UInt32              isWrDescValid;

    instObj = (VpsDrv_CaptInstObj *) drvData;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != coreFrm));
    GT_assert(VpsDrvCaptTrace, (coreFrm->streamId < VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace, (coreFrm->chId < instObj->createPrms.numCh));
    GT_assert(VpsDrvCaptTrace, (coreFrm->fid < FVID2_MAX_FIELDS));

    /* Get channel specific object in the required instance */
    chObj = &instObj->chObj[coreFrm->streamId][coreFrm->chId];

    cookie = BspOsal_disableInterrupt();

    GT_assert(VpsDrvCaptTrace, (NULL != instObj->getTimeStamp));
    curTimeStamp = instObj->getTimeStamp(NULL);
    GT_1trace(VpsDrvCaptTrace, GT_DEBUG,
              "CaptDrv: Buffer 0x%0.8x capture done\r\n", coreFrm->addr[0]);

    /* Update channel statistics */
    chObj->stat.captFrmCount++;
    chObj->stat.fldCount[coreFrm->fid]++;
    if((chObj->bmObj.isProgressive == FALSE) &&
       (chObj->stat.lastFid == coreFrm->fid))
    {
        chObj->stat.fidRepeatCount++;
    }
    chObj->stat.lastFid = coreFrm->fid;
    chObj->stat.lastFrmTimeStamp = (UInt32) (curTimeStamp / 1000U);
    isWrDescValid = (UInt32) TRUE;
#ifdef VPS_VIP_BUILD
    /* In case of VIP, width/height is valid only when write descriptor is
     * valid. So collect stats only when write descirptor is valid */
    if(coreFrm->coreStats != NULL)
    {
        isWrDescValid =
            ((VpsCore_VipCoreStats *) coreFrm->coreStats)->isWrDescValid;
    }
#endif
    if ((UInt32) TRUE == isWrDescValid)
    {
        if(coreFrm->width > chObj->stat.maxRecvFrmWidth)
        {
            chObj->stat.maxRecvFrmWidth = coreFrm->width;
        }
        if(coreFrm->height > chObj->stat.maxRecvFrmHeight)
        {
            chObj->stat.maxRecvFrmHeight = coreFrm->height;
        }
        /* Init min values for the first frame capture */
        if(chObj->stat.captFrmCount == 1U)
        {
            chObj->stat.minRecvFrmWidth  = coreFrm->width;
            chObj->stat.minRecvFrmHeight = coreFrm->height;
        }
        else
        {
            if(coreFrm->width < chObj->stat.minRecvFrmWidth)
            {
                chObj->stat.minRecvFrmWidth = coreFrm->width;
            }
            if(coreFrm->height < chObj->stat.minRecvFrmHeight)
            {
                chObj->stat.minRecvFrmHeight = coreFrm->height;
            }
        }
        chObj->stat.lastFrmWidth     = coreFrm->width;
        chObj->stat.lastFrmHeight    = coreFrm->height;
    }

#ifdef VPS_VIP_BUILD
    if(coreFrm->coreStats != NULL)
    {
        if(((VpsCore_VipCoreStats *) coreFrm->coreStats)->isWrDescValid ==
           FALSE)
        {
            chObj->stat.descErrCount++;
        }
        instObj->overflowCount +=
            ((VpsCore_VipCoreStats *) coreFrm->coreStats)->isOutputOverflow;
        instObj->asynOverflowCount +=
            ((VpsCore_VipCoreStats *) coreFrm->coreStats)->isAsyncOverflow;
        instObj->actProtViolationCount +=
            ((VpsCore_VipCoreStats *) coreFrm->coreStats)->isActProtViolation;
        instObj->ancProtViolationCount +=
            ((VpsCore_VipCoreStats *) coreFrm->coreStats)->isAncProtViolation;
    }
#endif

    /* Check if this is drop frame */
    if(coreFrm == &chObj->bmObj.dropCoreFrm)
    {
        /* Do nothing. Just give callback to app in case of periodic callback */
        chObj->stat.droppedFrmCount++;
    }
    else
    {
        /* Get reference of the queue head */
        qObj = (VpsDrv_CaptQueObj *) coreFrm->drvData;
        GT_assert(VpsDrvCaptTrace, (NULL != qObj));

        /* Decrement credit count as frame capture is complete - credit can't
         * be zero */
        GT_assert(VpsDrvCaptTrace, (qObj->creditCnt > 0U));
        qObj->creditCnt--;
        if(qObj->creditCnt > 0U)
        {
            chObj->stat.repeatFrmCount++;
        }

        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
        qObj->frm->status = coreFrm->status;

        if(VPS_CAPT_BCM_FRM_DROP == instObj->createPrms.bufCaptMode)
        {
            /* In frame drop mode, we could return all the frames to the
             * application if credit becomes 0 */
            if(0U == qObj->creditCnt)
            {
                qObjTemp = (VpsDrv_CaptQueObj *)
                           BspUtils_dequeue(chObj->bmObj.curQ);
                /* Head node and core frame should match */
                GT_assert(VpsDrvCaptTrace, (qObj == qObjTemp));

                GT_1trace(VpsDrvCaptTrace, GT_DEBUG,
                          "CaptDrv: Dequeued buffer 0x%0.8x\r\n",
                          coreFrm->addr[0]);

                qObj->coreFrm.addr[0][0] = NULL;
                qObj->coreFrm.addr[0][1] = NULL;
                qObj->coreFrm.addr[0][2] = NULL;
                qObj->coreFrm.dropFrm    = (UInt32) FALSE;

                /* Updated runtime parameters */
                GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                qObj->frm->fid = qObj->coreFrm.fid;
                if((NULL != qObj->frm->perFrameCfg) &&
                   (instObj->drvInstId != VPS_CAPT_INST_DSS_WB1))
                {
                    rtPrms = (Vps_CaptRtParams *) qObj->frm->perFrameCfg;
                    rtPrms->capturedOutWidth  = qObj->coreFrm.width;
                    rtPrms->capturedOutHeight = qObj->coreFrm.height;
                }

#ifdef VPS_VIP_BUILD
                /* Update slice info in case of sub-frame mode at EOF */
                if(TRUE == chObj->subFrmPrms.subFrameEnable)
                {
                    GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                    GT_assert(VpsDrvCaptTrace,
                              (NULL != qObj->frm->subFrameInfo));

                    qObj->frm->subFrameInfo->subFrameNum = chObj->subFrameNum;
                    /* Not valid for capture */
                    qObj->frm->subFrameInfo->numInLines = 0U;
                    /* Set actual captured height instead of subframe
                     * height calculation */
                    qObj->frm->subFrameInfo->numOutLines = qObj->coreFrm.height;
                }
#endif          /* VPS_VIP_BUILD */

                /* Return the frame to done queue */
                GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                /* Convert to msec for 32-bit timestamp */
                qObj->frm->timeStamp   = (UInt32) (curTimeStamp / 1000U);
                qObj->frm->timeStamp64 = curTimeStamp;
                BspUtils_queue(
                    instObj->doneQ[coreFrm->streamId],
                    &qObj->qElem,
                    qObj);
                frmQueuedToDoneQ = (Bool) TRUE;
            }
        }
        else if(VPS_CAPT_BCM_LAST_FRM_REPEAT ==
                instObj->createPrms.bufCaptMode)
        {
            /* Get the current queue counts */
            curQCnt = BspUtils_getNumQElem(chObj->bmObj.curQ);
            reqQCnt = BspUtils_getNumQElem(chObj->bmObj.reqQ);

            if(0U == qObj->creditCnt)
            {
                qObjTemp = (VpsDrv_CaptQueObj *)
                           BspUtils_dequeue(chObj->bmObj.curQ);
                /* Head node and core frame should match */
                GT_assert(VpsDrvCaptTrace, (qObj == qObjTemp));

                /* In last frame repeat mode, we could return all the frames to
                 * the application if credit becomes 0 and there are some more
                 * request in the current or request queue. Current queue is
                 * checked for 1 element as the current frame is still present
                 * in the queue. */
                if((curQCnt > 1U) || (reqQCnt > 0U))
                {
                    GT_1trace(VpsDrvCaptTrace, GT_DEBUG,
                              "CaptDrv: Dequeued buffer 0x%0.8x\r\n",
                              coreFrm->addr[0]);

                    qObj->coreFrm.addr[0][0] = NULL;
                    qObj->coreFrm.addr[0][1] = NULL;
                    qObj->coreFrm.addr[0][2] = NULL;
                    qObj->coreFrm.dropFrm    = (UInt32) FALSE;

                    /* Updated runtime parameters */
                    GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                    qObj->frm->fid = qObj->coreFrm.fid;
                    if((NULL != qObj->frm->perFrameCfg) &&
                       (instObj->drvInstId != VPS_CAPT_INST_DSS_WB1))
                    {
                        rtPrms = (Vps_CaptRtParams *) qObj->frm->perFrameCfg;
                        rtPrms->capturedOutWidth  = qObj->coreFrm.width;
                        rtPrms->capturedOutHeight = qObj->coreFrm.height;
                    }

#ifdef VPS_VIP_BUILD
                    /* Update slice info in case of sub-frame mode at EOF */
                    if(TRUE == chObj->subFrmPrms.subFrameEnable)
                    {
                        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                        GT_assert(VpsDrvCaptTrace,
                                  (NULL != qObj->frm->subFrameInfo));

                        qObj->frm->subFrameInfo->subFrameNum =
                            chObj->subFrameNum;
                        /* Not valid for capture */
                        qObj->frm->subFrameInfo->numInLines = 0U;
                        /* Set actual captured height instead of subframe
                         * height calculation */
                        qObj->frm->subFrameInfo->numOutLines =
                            qObj->coreFrm.height;
                    }
#endif              /* VPS_VIP_BUILD */

                    /* Return the frame to done queue */
                    GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                    /* Convert to msec for 32-bit timestamp */
                    qObj->frm->timeStamp   = (UInt32) (curTimeStamp / 1000U);
                    qObj->frm->timeStamp64 = curTimeStamp;
                    BspUtils_queue(
                        instObj->doneQ[coreFrm->streamId],
                        &qObj->qElem,
                        qObj);
                    frmQueuedToDoneQ = (Bool) TRUE;
                }
                /* In last frame repeat mode, if credit becomes 0 and there are
                 * no more request in the current and request queues, take this
                 * request and queue it back to request queue so that when
                 * the core asks for next buffer, we repeat the frame
                 * automatically. This is needed because the user could
                 * queue a request in between and this frame will end-up
                 * in the current queue!!
                 * Also increment the repeat frame counter here. */
                else if((curQCnt == 1U) && (reqQCnt == 0U))
                {
                    chObj->stat.repeatFrmCount++;
                    BspUtils_queue(chObj->bmObj.reqQ, &qObj->qElem, qObj);
                }
                else
                {
                    /* This can't happen as curQCnt can't be zero!! */
                    GT_assert(VpsDrvCaptTrace, FALSE);
                }
            }
        }
        else if(VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT ==
                instObj->createPrms.bufCaptMode)
        {
            /* Do nothing, just increment repeat count */
            if(0U == qObj->creditCnt)
            {
                chObj->stat.repeatFrmCount++;
            }
        }
        else
        {
            GT_assert(VpsDrvCaptTrace, FALSE);
        }
    }

    BspOsal_restoreInterrupt(cookie);

    if(NULL != instObj->fdmCbPrms.fdmCbFxn)
    {
        /* Give callback to application if periodic call back is enabled or
         * if frame is put in done queue */
        /* TODO - handle multi-channel case!! */
        if(((UInt32) TRUE == instObj->createPrms.periodicCbEnable) ||
           ((Bool) TRUE == frmQueuedToDoneQ))
        {
            instObj->fdmCbPrms.fdmCbFxn(instObj->fdmCbPrms.fdmData, NULL);
        }
    }

    return (BSP_SOK);
}

