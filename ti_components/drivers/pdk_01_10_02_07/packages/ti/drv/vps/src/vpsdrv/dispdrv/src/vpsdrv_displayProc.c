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
 *  \file vpsdrv_displayProc.c
 *
 *  \brief File containing the VPS display driver process related functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <dispdrv/src/vpsdrv_displayPriv.h>

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

/**
 *  \brief Extern function to be implemented by driver to provide a new frame
 *  buffers from application to the core.
 */
VpsCore_Frame *vpsDrvDispCoreReqFrameCb(void  *drvData,
                                        UInt32 streamId,
                                        UInt32 chId)
{
    UInt32 cookie;
    VpsDrv_DispInstObj *instObj;
    VpsDrv_DispQueObj  *qObj;
    VpsCore_Frame      *coreFrm = NULL;
    Fvid2_Frame        *newFrm;

    instObj = (VpsDrv_DispInstObj *) drvData;
    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (streamId == 0U));
    GT_assert(VpsDrvDispTrace, (chId == 0U));

    cookie = BspOsal_disableInterrupt();
    qObj   = (VpsDrv_DispQueObj *) BspUtils_dequeue(instObj->bmObj.reqQ);
    if (NULL != qObj)
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

        qObj->creditCnt++;
        coreFrm = &qObj->coreFrm;
        BspUtils_queue(instObj->bmObj.curQ, &qObj->qElem, qObj);
        instObj->isPrevBufRep = (UInt32) FALSE;
    }
    else
    {
        /*
         * No more buffers available in request queue.
         * Repeat the last frame queued to the core
         */
        /* Repeat the last frame queued to the core */
        qObj = (VpsDrv_DispQueObj *) BspUtils_peakTail(instObj->bmObj.curQ);
        /* This can't return NULL unless there is a bug in the buffer
         * management */
        GT_assert(VpsDrvDispTrace, (NULL != qObj));

        qObj->creditCnt++;
        coreFrm = &qObj->coreFrm;
        /* Mark the buffer as repeated */
        instObj->isPrevBufRep = (UInt32) TRUE;
    }

    GT_1trace(VpsDrvDispTrace, GT_DEBUG,
              "DispDrv: Queued buffer 0x%0.8x to core\r\n", coreFrm->addr[0]);

    BspOsal_restoreInterrupt(cookie);

    /* Call the user buffer program callback */
    if (NULL != instObj->bufPrgmCbFxn)
    {
        newFrm = instObj->bufPrgmCbFxn(
                     instObj->fdmCbPrms.handle,
                     qObj->frm,
                     instObj->isPrevBufRep,
                     qObj->creditCnt);
        if (NULL != newFrm)
        {
            /* Swap the current frame */
            qObj->frm = newFrm;

            /* Copy the address to core frames */
            qObj->coreFrm.addr[0][0] = qObj->frm->addr[0][0];
            qObj->coreFrm.addr[0][1] = qObj->frm->addr[0][1];
            qObj->coreFrm.addr[0][2] = qObj->frm->addr[0][2];

            qObj->coreFrm.addr[1][0] = qObj->frm->addr[1][0];
            qObj->coreFrm.addr[1][1] = qObj->frm->addr[1][1];
            qObj->coreFrm.addr[1][2] = qObj->frm->addr[1][2];

            qObj->coreFrm.rtParams   = qObj->frm->perFrameCfg;
        }
    }

    GT_assert(VpsDrvDispTrace, (NULL != coreFrm));
    return (coreFrm);
}

/**
 *  \brief Extern callback function to be implemented by driver to free
 *  up buffers to the application specified by the core.
 */
Int32 vpsDrvDispCoreFrameDoneCb(void *drvData, const VpsCore_Frame *coreFrm)
{
    UInt32 cookie;
    UInt32 curQCnt, reqQCnt;
    Bool   frmQueuedToDoneQ = FALSE;
    VpsDrv_DispInstObj *instObj;
    VpsDrv_DispQueObj  *qObj, *qObjTemp;
    UInt64 curTimeStamp;

    instObj = (VpsDrv_DispInstObj *) drvData;
    GT_assert(VpsDrvDispTrace, (NULL != instObj));

    /* The first VSYNC interrupt has NULL pointer as there is no frame to deQ */
    if (coreFrm != NULL)
    {
        GT_assert(VpsDrvDispTrace, (coreFrm->streamId == 0U));
        GT_assert(VpsDrvDispTrace, (coreFrm->chId == 0U));
        GT_assert(VpsDrvDispTrace, (coreFrm->fid < FVID2_MAX_FIELDS));

        cookie = BspOsal_disableInterrupt();
        curTimeStamp = BspOsal_getCurTimeInUsec();

        GT_1trace(VpsDrvDispTrace, GT_DEBUG,
                  "DispDrv: Buffer 0x%0.8x display done\r\n", coreFrm->addr[0]);

        /* Update channel statistics */
        instObj->stat.dispFrmCount++;

        /* Get reference of the queue head */
        qObj = (VpsDrv_DispQueObj *) coreFrm->drvData;
        GT_assert(VpsDrvDispTrace, (NULL != qObj));

        /* Decrement credit count as frame display is complete - credit can't
         * be zero */
        GT_assert(VpsDrvDispTrace, (qObj->creditCnt > 0U));
        qObj->creditCnt--;
        if (qObj->creditCnt > 0U)
        {
            instObj->stat.repeatFrmCount++;
        }

        /* Get the current queue counts */
        curQCnt = BspUtils_getNumQElem(instObj->bmObj.curQ);
        reqQCnt = BspUtils_getNumQElem(instObj->bmObj.reqQ);

        if (0U == qObj->creditCnt)
        {
            qObjTemp = (VpsDrv_DispQueObj *) BspUtils_dequeue(instObj->bmObj.curQ);
            /* Head node and core frame should match */
            GT_assert(VpsDrvDispTrace, (qObj == qObjTemp));

            /* In last frame repeat mode, we could return all the frames to
             * the application if credit becomes 0 and there are some more
             * request in the current or request queue. Current queue is
             * checked for 1 element as the current frame is still present
             * in the queue. */
            if ((curQCnt > 1U) || (reqQCnt > 0U))
            {
                GT_1trace(VpsDrvDispTrace, GT_DEBUG,
                          "DispDrv: Dequeued buffer 0x%0.8x\r\n",
                          coreFrm->addr[0]);

                qObj->coreFrm.addr[0][0] = NULL;
                qObj->coreFrm.addr[0][1] = NULL;
                qObj->coreFrm.addr[0][2] = NULL;

                qObj->coreFrm.addr[1][0] = NULL;
                qObj->coreFrm.addr[1][1] = NULL;
                qObj->coreFrm.addr[1][2] = NULL;

                /* Return the frame to done queue */
                GT_assert(VpsDrvDispTrace, (NULL != qObj->frm));
                /* Convert to msec for 32-bit timestamp */
                qObj->frm->timeStamp   = (UInt32) (curTimeStamp / 1000U);
                qObj->frm->timeStamp64 = curTimeStamp;
                BspUtils_queue(instObj->bmObj.doneQ, &qObj->qElem, qObj);
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
            else if ((curQCnt == 1U) && (reqQCnt == 0U))
            {
                instObj->stat.repeatFrmCount++;
                BspUtils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
            }
            else
            {
                /* This can't happen as curQCnt can't be zero!! */
                GT_assert(VpsDrvDispTrace, FALSE);
            }
        }
        BspOsal_restoreInterrupt(cookie);
    }

    if (NULL != instObj->fdmCbPrms.fdmCbFxn)
    {
        /* Give callback to application if periodic call back is enabled or
         * if frame is put in done queue */
        if ((TRUE == instObj->createPrms.periodicCbEnable) ||
            ((Bool) TRUE == frmQueuedToDoneQ))
        {
            instObj->isInIsrContext = (UInt32) TRUE;
            instObj->fdmCbPrms.fdmCbFxn(instObj->fdmCbPrms.fdmData, NULL);
            instObj->isInIsrContext = (UInt32) FALSE;
        }
    }

    return (BSP_SOK);
}

