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
 *  \file vpsdrv_captureApi.c
 *
 *  \brief File containing the VPS capture driver APIs.
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
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Capture API's
 */
static Fdrv_Handle VpsDrv_captCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsDrv_captDelete(Fdrv_Handle handle, Ptr reserved);
static Int32 VpsDrv_captQueue(Fdrv_Handle      handle,
                              Fvid2_FrameList *frmList,
                              UInt32           streamId);
static Int32 VpsDrv_captDequeue(Fdrv_Handle      handle,
                                Fvid2_FrameList *frmList,
                                UInt32           streamId,
                                UInt32           timeout);
static Int32 VpsDrv_captControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);

#ifdef __cplusplus
}
#endif

/*
 * Capture IOCTLs
 */
static Int32 vpsDrvCaptStartIoctl(VpsDrv_CaptInstObj *instObj);
static Int32 vpsDrvCaptStopIoctl(VpsDrv_CaptInstObj *instObj);
static Int32 vpsDrvCaptGetStatusIoctl(const VpsDrv_CaptInstObj *instObj,
                                      Vps_CaptStatus           *captStat);
static Int32 vpsDrvCaptGetChStatusIoctl(const VpsDrv_CaptInstObj   *instObj,
                                        const Vps_CaptChStatusArgs *chStatArgs,
                                        Vps_CaptChStatus           *chStat);
static Int32 vpsDrvCaptSetFrmSkipIoctl(VpsDrv_CaptInstObj      *instObj,
                                       const Vps_CaptFrameSkip *frmSkipPrms);
static Int32 vpsDrvCaptRegisterTimeStampIoctl(
    VpsDrv_CaptInstObj        *instObj,
    const Vps_TimeStampParams *timeStampPrms);

static Int32 vpsDrvCaptRegisterOvfIntr(
    VpsDrv_CaptInstObj *pObj,
    const Vps_CaptOverflowParams *
    overflowParams);

#ifdef VPS_VIP_BUILD
static Int32 vpsDrvCaptPortReset(VpsDrv_CaptInstObj *pObj);
#endif /* VPS_VIP_BUILD */

static Int32 vpsDrvCaptCheckOverflow(
    VpsDrv_CaptInstObj          *instObj,
    Vps_CaptOverflowCheckParams *overflowCheck);
static Int32 vpsDrvCaptUnregisterOvfIntr(VpsDrv_CaptInstObj *instObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS VIP capture driver init function.
 */
Int32 VpsDrv_captInit(UInt32 numInst, const VpsDrv_CaptInitParams *initPrms)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CaptCommonObj *pObj;

    retVal = vpsDrvCaptPrivInit(numInst, initPrms);
    if (FVID2_SOK == retVal)
    {
        pObj = &gVpsCaptCommonObj;
        /* Initialize Driver operations */
        Fvid2DrvOps_init(&pObj->fvidDrvOps);

        pObj->fvidDrvOps.drvId      = FVID2_VPS_CAPT_VID_DRV;
        pObj->fvidDrvOps.createFxn  = &VpsDrv_captCreate;
        pObj->fvidDrvOps.deleteFxn  = &VpsDrv_captDelete;
        pObj->fvidDrvOps.controlFxn = &VpsDrv_captControl;
        pObj->fvidDrvOps.queueFxn   = &VpsDrv_captQueue;
        pObj->fvidDrvOps.dequeueFxn = &VpsDrv_captDequeue;

        retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(
                VpsDrvCaptTrace, GT_ERR,
                "Registering to FVID2 driver manager failed\r\n");
            /* Uninitialize the internal objects if error occurs */
            vpsDrvCaptPrivDeInit();
        }
        else
        {
            /* Init successful */
            pObj->isRegistered = (UInt32) TRUE;
            pObj->numInst      = numInst;
        }
    }

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver deinit function.
 */
Int32 VpsDrv_captDeInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CaptCommonObj *pObj;

    pObj = &gVpsCaptCommonObj;
    if (TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(
                VpsDrvCaptTrace, GT_ERR,
                "Unregistering from FVID2 driver manager failed\r\n");
        }
        pObj->isRegistered = (UInt32) FALSE;
    }

    retVal += vpsDrvCaptPrivDeInit();

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver create function.
 */
static Fdrv_Handle VpsDrv_captCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32                 retVal = FVID2_SOK, tempRetVal;
    UInt32                streamId;
    UInt32                chCreateFlag = FALSE, coreCreateFlag = FALSE;
    Fdrv_Handle           drvHandle    = NULL;
    VpsDrv_CaptInstObj   *instObj      = NULL;
    Vps_CaptCreateParams *createPrms;
    Vps_CaptCreateStatus *createStatus;

    if ((UInt32) VPS_CAPT_INST_ALL == instId)
    {
        /*
         * gloabl handle open requested, no action required,
         * just return a special handle ID
         */
        if (NULL != createStatusArgs)
        {
            createStatus         = (Vps_CaptCreateStatus *) createStatusArgs;
            createStatus->retVal = FVID2_SOK;
        }
        drvHandle = ((Fdrv_Handle) & gVpsCaptCommonObj);
    }
    else
    {
        /* Check for NULL pointers and invalid arguments */
        if ((NULL == createArgs) ||
            (NULL == createStatusArgs) ||
            (NULL == fdmCbPrms) ||
            (FVID2_VPS_CAPT_VID_DRV != drvId))
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid arguments\r\n");
            retVal = FVID2_EBADARGS;
        }
        else
        {
            /* Get the instance object for this instance */
            instObj = vpsDrvCaptGetInstObj(instId);
            if (NULL == instObj)
            {
                GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid instance ID\r\n");
                retVal = FVID2_EINVALID_PARAMS;
            }
        }

        if (NULL != instObj)
        {
            /* Take the instance semaphore */
            BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

            /* Check if the instance is already opened */
            if (VPS_CAPT_STATE_IDLE != instObj->state)
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "DEVICE_INUSE: Driver instance already created!!\r\n");
                retVal = FVID2_EDEVICE_INUSE;
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Check for valid create parameters and copy them */
            createPrms = (Vps_CaptCreateParams *) createArgs;
            retVal     = vpsDrvCaptCheckParams(instObj, createPrms);
            if (FVID2_SOK == retVal)
            {
                BspUtils_memcpy(
                    &instObj->createPrms,
                    createPrms,
                    sizeof (instObj->createPrms));
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Get core property */
            retVal = vpsDrvCaptGetPropCore(instObj);
        }

        if (FVID2_SOK == retVal)
        {
            retVal = vpsDrvCaptCreateChObj(instObj);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "Channel object create failed!!\r\n");
            }
            else
            {
                chCreateFlag = (UInt32) TRUE;
            }
        }

        if (FVID2_SOK == retVal)
        {
            retVal = vpsDrvCaptOpenCore(instObj);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsDrvCaptTrace, GT_ERR, "Core open failed!!\r\n");
            }
            else
            {
                coreCreateFlag = (UInt32) TRUE;
            }
        }

        if (FVID2_SOK == retVal)
        {
            for (streamId = 0U; streamId < VPS_CAPT_STREAM_ID_MAX; streamId++)
            {
                instObj->doneQ[streamId] = NULL;
            }

            for (streamId = 0U;
                 streamId < instObj->createPrms.numStream;
                 streamId++)
            {
                /* Create done Queue */
                tempRetVal = BspUtils_constructQ(&instObj->doneLlObj[streamId]);
                GT_assert(VpsDrvCaptTrace, (tempRetVal == BSP_SOK));
                instObj->doneQ[streamId] = &instObj->doneLlObj[streamId];
            }

            BspUtils_memcpy(
                &instObj->fdmCbPrms,
                fdmCbPrms,
                sizeof (instObj->fdmCbPrms));

            instObj->queueCount            = 0U;
            instObj->dequeueCount          = 0U;
            instObj->overflowCount         = 0U;
            instObj->asynOverflowCount     = 0U;
            instObj->actProtViolationCount = 0U;
            instObj->ancProtViolationCount = 0U;
            instObj->state = VPS_CAPT_STATE_CREATED;
            drvHandle      = instObj;
        }

        /* Return the status if possible */
        if (NULL != createStatusArgs)
        {
            createStatus         = (Vps_CaptCreateStatus *) createStatusArgs;
            createStatus->retVal = retVal;
        }

        if (NULL != instObj)
        {
            /* Deallocate if error occurs */
            if (FVID2_SOK != retVal)
            {
                if ((UInt32) TRUE == coreCreateFlag)
                {
                    tempRetVal = vpsDrvCaptCloseCore(instObj);
                    GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
                }

                if ((UInt32) TRUE == chCreateFlag)
                {
                    tempRetVal = vpsDrvCaptDeleteChObj(instObj);
                    GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
                }
            }

            /* Post the instance semaphore */
            BspOsal_semPost(instObj->lockSem);
        }
    }
    return (drvHandle);
}

/**
 *  \brief VPS VIP capture driver delete function.
 */
static Int32 VpsDrv_captDelete(Fdrv_Handle handle, Ptr reserved)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamId;
    VpsDrv_CaptInstObj *instObj = NULL;

    /* Global handle - do nothing */
    if (((Fdrv_Handle) & gVpsCaptCommonObj) == handle)
    {
        retVal = (FVID2_SOK);
    }
    else
    {
        /* Check for NULL pointers and invalid arguments */
        if (NULL == handle)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid arguments\r\n");
            retVal = FVID2_EBADARGS;
        }
        else
        {
            instObj = (VpsDrv_CaptInstObj *) handle;
        }

        if (NULL != instObj)
        {
            /* Take the instance semaphore */
            BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

            /* Check if the instance is already opened and in a stopped state */
            if ((instObj->state == VPS_CAPT_STATE_STOPPED) ||
                (instObj->state == VPS_CAPT_STATE_CREATED))
            {
                retVal = vpsDrvCaptCloseCore(instObj);
                GT_assert(VpsDrvCaptTrace, (FVID2_SOK == retVal));

                retVal = vpsDrvCaptDeleteChObj(instObj);
                GT_assert(VpsDrvCaptTrace, (FVID2_SOK == retVal));

                for (streamId = 0U;
                     streamId < instObj->createPrms.numStream;
                     streamId++)
                {
                    if (NULL != instObj->doneQ[streamId])
                    {
                        /* Delete the done Q */
                        BspUtils_destructQ(instObj->doneQ[streamId]);
                        instObj->doneQ[streamId] = NULL;
                    }
                }

                /* Mark state as idle */
                instObj->state = VPS_CAPT_STATE_IDLE;
            }
            else
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "Driver not in a state to delete. Try stopping it!!\r\n");
                retVal = FVID2_EFAIL;
            }
        }

        if (NULL != instObj)
        {
            /* Post the instance semaphore */
            BspOsal_semPost(instObj->lockSem);
        }
    }

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver queue function.
 */
static Int32 VpsDrv_captQueue(Fdrv_Handle      handle,
                              Fvid2_FrameList *frmList,
                              UInt32           streamId)
{
    Int32  retVal = FVID2_SOK;
    UInt32 frmCnt, chId, instId, lChNum, drvStreamId;
    UInt32 cookie;
    Fvid2_Frame          *frm;
    VpsDrv_CaptChObj     *chObj;
    VpsDrv_CaptInstObj   *instObj;
    VpsDrv_CaptCommonObj *pObj;
    VpsDrv_CaptQueObj    *qObj;

    pObj = &gVpsCaptCommonObj;

    /* Check for NULL pointers */
    if ((NULL == handle) || (NULL == frmList))
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else if (handle == ((Fdrv_Handle) & gVpsCaptCommonObj))
    {
        GT_0trace(
            VpsDrvCaptTrace, GT_ERR,
            "Queue not supported for global handle!!\r\n");
        retVal = FVID2_EFAIL;
    }
    else
    {
        instObj = (VpsDrv_CaptInstObj *) handle;

        /* Check framelist for error and NULL pointer check */
        retVal = Fvid2_checkFrameList(frmList, (UInt32) FVID2_MAX_FRAME_PTR);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Check frame list error\n");
        }

        if (VPS_CAPT_STATE_IDLE == instObj->state)
        {
            /* If driver handle is not open then skip this frame queue */
            GT_0trace(
                VpsDrvCaptTrace, GT_ERR,
                "Invalid state: Can't queue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }

        if ((VPS_CAPT_STATE_RUNNING == instObj->state) &&
            (VPS_CAPT_BCM_CIRCULAR_FRM_REPEAT ==
             instObj->createPrms.bufCaptMode))
        {
            GT_0trace(
                VpsDrvCaptTrace, GT_ERR,
                "Invalid state: Can't queue after capture starts in circular "
                "frame repeat mode!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->queueCount++;

        /* for all frames that need to be queued */
        for (frmCnt = 0; frmCnt < frmList->numFrames; frmCnt++)
        {
            /* Get FVID2 frame pointer - NULL check is already done in
             * check frame list function */
            frm = frmList->frames[frmCnt];
            GT_assert(VpsDrvCaptTrace, (NULL != frm));

            if (retVal == FVID2_SOK)
            {
                /* Map user channel number to driver channel number */
                lChNum = pObj->fvidChNumToLogChNumMap[frm->chNum];

                /* extract driver instance ID from driver channel number */
                instId = Vps_captGetInstId(lChNum);
            }
            if (retVal == FVID2_SOK)
            {
                if (instId != instObj->drvInstId)
                {
                    /* If mismatch then chNum in FVID2 Frame is not correct,
                     * skip this frame queue */
                    GT_0trace(
                        VpsDrvCaptTrace, GT_ERR, "Instance ID mismatch\r\n");
                    retVal = FVID2_EFAIL;
                }
            }
            if (retVal == FVID2_SOK)
            {
                if (VPS_CAPT_STREAM_ID_ANY == streamId)
                {
                    drvStreamId = Vps_captGetStreamId(lChNum);
                }
                else
                {
                    drvStreamId = streamId;
                }
                streamId = Vps_captGetStreamId(lChNum);

                if ((drvStreamId >= instObj->createPrms.numStream) ||
                    (drvStreamId != streamId))
                {
                    /* invalid stream ID skip this frame queue */
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "Stream ID mismatch\r\n");
                    retVal = FVID2_EFAIL;
                }
            }
            if (retVal == FVID2_SOK)
            {
                /* Get channel ID */
                chId = Vps_captGetChId(lChNum);
                if (chId >= instObj->createPrms.numCh)
                {
                    /* Invalid channel ID skip this frame queue */
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid channel ID\r\n");
                    retVal = FVID2_EFAIL;
                }
            }
            if (retVal == FVID2_SOK)
            {
                /*
                 * valid instance, stream and channel
                 */
                /* Get channel specific object in the required instance */
                chObj = &instObj->chObj[drvStreamId][chId];

                cookie = BspOsal_disableInterrupt();

                /* Allocate a free queue object from the pool */
                qObj =
                    (VpsDrv_CaptQueObj *) BspUtils_dequeue(chObj->bmObj.freeQ);
                if (NULL == qObj)
                {
                    BspOsal_restoreInterrupt(cookie);
                    GT_0trace(
                        VpsDrvCaptTrace, GT_ERR,
                        "ALLOC: Q object allocation failed\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
            if (retVal == FVID2_SOK)
            {
                /* Copy the frame to the driver's queue object */
                qObj->frm = frm;
                /* Initial credit count should be zero!! */
                GT_assert(VpsDrvCaptTrace, (0U == qObj->creditCnt));

                /* Add the queue object in driver's request queue */
                BspUtils_queue(chObj->bmObj.reqQ, &qObj->qElem, qObj);
                chObj->stat.queueCount++;

                BspOsal_restoreInterrupt(cookie);

                /* Mark frame in frmList as NULL */
                frmList->frames[frmCnt] = NULL;
            }
            if (retVal != FVID2_SOK)
            {
                break;
            }
        }
    }

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver dequeue function.
 */
static Int32 VpsDrv_captDequeue(Fdrv_Handle      handle,
                                Fvid2_FrameList *frmList,
                                UInt32           streamId,
                                UInt32           timeout)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chCnt;
    UInt32 cookie;
    VpsDrv_CaptChObj   *chObj;
    VpsDrv_CaptInstObj *instObj;
    VpsDrv_CaptQueObj  *qObj;

    /* Check for NULL pointers */
    if ((NULL == handle) ||
        (NULL == frmList) ||
        (streamId >= VPS_CAPT_STREAM_ID_MAX))
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else if (handle == ((Fdrv_Handle) & gVpsCaptCommonObj))
    {
        GT_0trace(
            VpsDrvCaptTrace, GT_ERR,
            "Dequeue not supported for global handle!!\r\n");
        retVal = FVID2_EFAIL;
    }
    else
    {
        instObj = (VpsDrv_CaptInstObj *) handle;
        if (instObj->state == VPS_CAPT_STATE_IDLE)
        {
            GT_0trace(
                VpsDrvCaptTrace, GT_ERR,
                "Invalid state: Can't dequeue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }

        /* validate stream ID */
        if (streamId >= instObj->createPrms.numStream)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid stream ID!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* init frame list fields */
        frmList->numFrames  = 0U;
        frmList->perListCfg = NULL;

        /* Extract done frames from queue till the queue
         * is empty or framelist runs out of space!! */
        do
        {
            cookie = BspOsal_disableInterrupt();
            qObj   = (VpsDrv_CaptQueObj *)
                     BspUtils_dequeue(instObj->doneQ[streamId]);
            if (NULL == qObj)
            {
                /* No more buffers in instance object */
                BspOsal_restoreInterrupt(cookie);
            }
            else
            {
                GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                frmList->frames[frmList->numFrames] = qObj->frm;
                frmList->numFrames++;

                /* Give back the queue object back to the free pool */
                qObj->frm = NULL;
                /* At time of deqeue, credit should be zero!! */
                GT_assert(VpsDrvCaptTrace, (0U == qObj->creditCnt));
                chObj = qObj->chObj;
                GT_assert(VpsDrvCaptTrace, (NULL != chObj));
                BspUtils_queue(chObj->bmObj.freeQ, &qObj->qElem, qObj);
                chObj->stat.dequeueCount++;

                BspOsal_restoreInterrupt(cookie);
            }

            /* Max frames limit exceeded exit */
            if ((frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
                (NULL == qObj))
            {
                break;
            }

            /* TODO: Break for oneCallBackPerFrm */
        } while (1U);
    }

    /* If no frame is dequeued, then check if we could return frames from input
     * and current queue for stopped instances */
    if ((FVID2_SOK == retVal) && (0U == frmList->numFrames))
    {
        /* When an instance is stopped, return all the request in
         * channel's input and current queue as well. */
        GT_assert(VpsDrvCaptTrace, (NULL != instObj));
        if ((VPS_CAPT_STATE_CREATED == instObj->state) ||
            (VPS_CAPT_STATE_STOPPED == instObj->state))
        {
            cookie = BspOsal_disableInterrupt();

            for (chCnt = 0U; chCnt < instObj->createPrms.numCh; chCnt++)
            {
                chObj = &instObj->chObj[streamId][chCnt];

                /* Extract frames from queue till the queue
                 * is empty or framelist runs out of space!! */
                do
                {
                    /* Give the buffers in current state */
                    qObj = (VpsDrv_CaptQueObj *)
                           BspUtils_dequeue(chObj->bmObj.curQ);
                    if (NULL == qObj)
                    {
                        /* At last give back buffers in request queue as well */
                        qObj = (VpsDrv_CaptQueObj *)
                               BspUtils_dequeue(chObj->bmObj.reqQ);
                    }

                    if (NULL != qObj)
                    {
                        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
                        frmList->frames[frmList->numFrames] = qObj->frm;
                        frmList->numFrames++;

                        /* Give back the queue object back to the free pool */
                        qObj->frm = NULL;
                        /* At time of deqeue, credit should be zero!! */
                        GT_assert(VpsDrvCaptTrace, (0U == qObj->creditCnt));
                        GT_assert(VpsDrvCaptTrace, (chObj == qObj->chObj));
                        BspUtils_queue(chObj->bmObj.freeQ, &qObj->qElem, qObj);
                        chObj->stat.dequeueCount++;
                    }

                    /* Max frames limit exceeded exit or no more frames for this
                     * channel, continue with next channel */
                    if ((frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
                        (NULL == qObj))
                    {
                        break;      /* do () */
                    }

                    /* TODO: Break for oneCallBackPerFrm */
                } while (1U);

                /* Max frames limit exceeded exit */
                if (frmList->numFrames >= FVID2_MAX_FRAME_PTR)
                {
                    break;      /* for (chCnt) */
                }
            }

            BspOsal_restoreInterrupt(cookie);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* If no frame is dequeued, then return appropriate error */
        if (0U == frmList->numFrames)
        {
            if ((VPS_CAPT_STATE_CREATED == instObj->state) ||
                (VPS_CAPT_STATE_STOPPED == instObj->state))
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_DEBUG,
                    "NO_MORE_BUFFERS: No more buffers with driver\n");
                retVal = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                GT_0trace(
                    VpsDrvCaptTrace, GT_DEBUG,
                    "AGAIN: Out queue Empty. Try again\r\n");
                retVal = FVID2_EAGAIN;
            }
        }
        else
        {
            instObj->dequeueCount++;
        }
    }

    return (retVal);
}

/**
 *  \brief VPS VIP capture driver control function.
 */
static Int32 VpsDrv_captControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CaptInstObj *instObj;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else if (handle == (Fdrv_Handle) & gVpsCaptCommonObj)
    {
        switch (cmd)
        {
#ifdef VPS_VIP_BUILD
            case IOCTL_VPS_CAPT_SET_VIP_MAX_SIZE:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCaptSetVipMaxSizePrmsIoctl(
                        (VpsDrv_CaptCommonObj *) handle,
                        (Vps_VpdmaMaxSizeParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
#endif
            default:
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "UNSUPPORTED_CMD: IOCTL not supported for global handle\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }
    else
    {
        instObj = (VpsDrv_CaptInstObj *) handle;
        switch (cmd)
        {
            case FVID2_START:
                retVal = vpsDrvCaptStartIoctl(instObj);
                break;

            case FVID2_STOP:
                retVal = vpsDrvCaptStopIoctl(instObj);
                break;

#ifdef VPS_DSS_BUILD
            case IOCTL_VPS_CAPT_SET_DSSWB_PARAMS:
            {
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCaptSetDssWbCoreParams(
                        instObj,
                        (Vps_CaptDssWbParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
            }
            case IOCTL_VPS_CAPT_DSSWB_SET_CSC_COEFF:
            {
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCaptSetDssWbCscCoeff(
                        instObj,
                        (void *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
            }
#endif

#ifdef VPS_VIP_BUILD
            case IOCTL_VPS_CAPT_SET_VIP_PARAMS:
            {
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCaptSetVipCoreParams(
                        instObj,
                        (Vps_CaptVipParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
            }

            case IOCTL_VPS_CAPT_GET_VIP_PARAMS:
            {
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCaptGetVipCoreParams(
                        instObj,
                        (Vps_CaptVipParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
            }

            case IOCTL_VPS_CAPT_RESET_VIP:
            {
                instObj->isOverflowOccured = (UInt32) FALSE;
                vpsDrvCaptPortReset(instObj);
                break;
            }

            case IOCTL_VPS_CAPT_RESET_VIP_PORT:
            {
                instObj->coreOps->control(
                    instObj->coreHandle,
                    VPSCORE_VIP_IOCTL_RESET_VIP_PORT,
                    NULL, NULL);

                break;
            }
#endif      /* VPS_VIP_BUILD */

            case IOCTL_VPS_CAPT_GET_STATUS:
            {
                retVal = vpsDrvCaptGetStatusIoctl(
                    instObj,
                    (Vps_CaptStatus *) cmdArgs);
                break;
            }

            case IOCTL_VPS_CAPT_GET_CH_STATUS:
            {
                retVal = vpsDrvCaptGetChStatusIoctl(
                    instObj,
                    (const Vps_CaptChStatusArgs *) cmdArgs,
                    (Vps_CaptChStatus *) cmdStatusArgs);
                break;
            }

            case IOCTL_VPS_CAPT_SET_FRAME_SKIP:
            {
                retVal = vpsDrvCaptSetFrmSkipIoctl(
                    instObj,
                    (const Vps_CaptFrameSkip *) cmdArgs);
                break;
            }

            case IOCTL_VPS_CAPT_REGISTER_OVF_INTR:
            {
                retVal = vpsDrvCaptRegisterOvfIntr(
                    instObj,
                    (Vps_CaptOverflowParams *)
                    cmdArgs);
                break;
            }

            case IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR:
            {
                retVal = vpsDrvCaptUnregisterOvfIntr(instObj);
                break;
            }

            case IOCTL_VPS_CAPT_CHECK_OVERFLOW:
            {
                vpsDrvCaptCheckOverflow(
                    instObj,
                    (Vps_CaptOverflowCheckParams *) cmdArgs);
                break;
            }

            case IOCTL_VPS_REGISTER_TIMESTAMP_FXN:
            {
                retVal = vpsDrvCaptRegisterTimeStampIoctl(
                    instObj,
                    (const Vps_TimeStampParams *) cmdArgs);
                break;
            }

#ifdef VPS_CAL_BUILD
            case IOCTL_VPS_CAPT_SET_ISS_PARAMS:
            {
                retVal = vpsDrvCaptSetIssCoreParams(instObj,
                                                    (vpsissCalCfg_t *) cmdArgs);
                break;
            }
#ifdef VPS_ISS_BUILD
            case IOCTL_VPS_CAPT_SET_ISS_STREAM_MAP:
            {
                retVal = vpsDrvCaptSetIssStreamMap(instObj,
                                                   (vpsissCalOtfStreamMapCfg_t
                                                    *) cmdArgs);
                break;
            }
            case IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS:
            {
                retVal = vpsDrvCaptSetIssErrorParams(instObj,
                                                    (vpsissCalErrorCfg_t*)
                                                        cmdArgs);
                break;
            }
            case IOCTL_VPS_CAPT_SET_FRAME_EVENT_NOTIFY_PRMS:
            {
                retVal = vpsDrvCaptSetIssSubFrmParams(instObj,
                                    (vpsissCalFrameEventNotifyCfg_t*) cmdArgs);
                break;
            }
            /* When ISS Capture is operating in OTF mode, all sub-blocks of ISP
             *  are configurable via IOCTL. Its better the capture core / ISP
             *  core to handle these IOTCLs. */
            default:
                retVal = vpsDrvCaptOtfControl(instObj, cmd, cmdArgs);
                break;
#else /* VPS_ISS_BUILD */
            case IOCTL_VPS_CAPT_SET_ISS_ERR_PRMS:
            {
                retVal = vpsDrvCaptSetIssErrorParams(instObj,
                                                    (vpsissCalErrorCfg_t*)
                                                        cmdArgs);
                break;
            }
            case IOCTL_VPS_CAPT_SET_FRAME_EVENT_NOTIFY_PRMS:
            {
                retVal = vpsDrvCaptSetIssSubFrmParams(instObj,
                                    (vpsissCalFrameEventNotifyCfg_t*) cmdArgs);
                break;
            }
            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR,
                            "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
#endif /* VPS_ISS_BUILD */
#else /* VPS_CAL_BUILD */

            default:
                GT_0trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;

#endif      /* VPS_CAL_BUILD */
        }
    }

    return (retVal);
}

/*
 *  \brief Function unregister from the overflow interrupt.
 */

static Int32 vpsDrvCaptUnregisterOvfIntr(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

#ifdef VPS_VIP_BUILD
    retVal = Vem_unRegister(instObj->overflowVemHandle);
#endif /* VPS_VIP_BUILD */

    return retVal;
}

/*
 *  \brief Function to check if overflow has occured or not..
 */

static Int32 vpsDrvCaptCheckOverflow(VpsDrv_CaptInstObj          *instObj,
                                     Vps_CaptOverflowCheckParams *overflowCheck)
{
#ifdef VPS_VIP_BUILD    /*To avoid warning for non VIP build*/
    UInt32 regErrorStatus = FALSE;
#endif
    Int32  retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != overflowCheck));

    /* Get core property */
    retVal = instObj->coreOps->getProperty(
        instObj->coreInstObj,
        &instObj->coreProperty);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Get core property failed!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Call the respective core open function */
        switch (instObj->coreProperty.name)
        {
#ifdef VPS_VIP_BUILD
            case VPSCORE_CAPT_VIP:
                retVal = instObj->coreOps->control(
                    instObj->coreHandle,
                    VPSCORE_VIP_IOCTL_GET_OVERFLOW_REG_STATUS,
                    NULL,
                    &regErrorStatus);
                if ((instObj->isOverflowOccured == TRUE) ||
                    (0U != regErrorStatus))
                {
                    overflowCheck->isOverflowOccured = (UInt32) TRUE;
                }
                else
                {
                    overflowCheck->isOverflowOccured = (UInt32) FALSE;
                }
                break;
#endif
            case VPSCORE_CAPT_ISS:
                GT_0trace(VpsDrvCaptTrace, GT_ERR, "ISS core not supported\r\n");
                retVal = FVID2_EFAIL;
                break;

            case VPSCORE_DISP_DSSWB:
                GT_0trace(VpsDrvCaptTrace, GT_ERR, "DSS core not supported\r\n");
                retVal = FVID2_EFAIL;
                break;

            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR, "Unknown core!!\r\n");
                retVal = FVID2_EFAIL;
                break;
        }
    }
    return retVal;
}

/**
 *  \brief overflow enable function.
 */

static Int32 vpsDrvCaptRegisterOvfIntr(
    VpsDrv_CaptInstObj *pObj,
    const Vps_CaptOverflowParams *
    overflowParams)
{
    Int32 retVal = FVID2_SOK;

#ifdef VPS_VIP_BUILD
    VpsCore_VipOpenRetParams vipRetPrms;
#endif

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != pObj));
    GT_assert(VpsDrvCaptTrace, (NULL != overflowParams));

#ifdef VPS_VIP_BUILD
    vipRetPrms.intrType[0U] = VPSCORE_VIP_INTRTYPE_VEM;
    retVal = pObj->coreOps->control(
        pObj->coreHandle,
        VPSCORE_VIP_IOCTL_GET_VEM_PARAMS,
        pObj->coreInstObj,
        &vipRetPrms);

    if (retVal == FVID2_SOK)
    {
        pObj->overflowCbFxn     = overflowParams->overflowCbFxn;
        pObj->appOverFlowCbPrms = overflowParams->retParams;
        pObj->overflowVemHandle = Vem_register(
            vipRetPrms.vemInstId[0U],
            vipRetPrms.vemEventGroup[0U],
            &vipRetPrms.vemEvent[0U],
            (UInt32) 1U,
            VEM_PRIORITY1,
            (Vem_ClientCbFxn) & vpsDrvCaptVemOverflowIsr,
            (void *) pObj);
        if (NULL == pObj->overflowVemHandle)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR,
                      "VEM  registeration failed!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }
#endif

    return retVal;
}

/**
 *  \brief Function to reset the VIP port.
 */
#ifdef VPS_VIP_BUILD

static Int32 vpsDrvCaptPortReset(VpsDrv_CaptInstObj *pObj)
{
    Int32 retVal = BSP_EFAIL;

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != pObj));

    pObj->isOverflowOccured = (UInt32) FALSE;
    retVal = pObj->coreOps->control(pObj->coreHandle,
                                    VPSCORE_VIP_IOCTL_RESET_PORT,
                                    NULL, NULL);

    return retVal;
}

#endif /* VPS_VIP_BUILD */

static Int32 vpsDrvCaptStartIoctl(VpsDrv_CaptInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 numElemInReqQ;
    UInt32 streamId, chId;
    VpsDrv_CaptChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));
    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Initialize the overflow to false at start. */
    instObj->isOverflowOccured = (UInt32) FALSE;
    /* For every stream and every channel */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        for (chId = 0; chId < instObj->createPrms.numCh; chId++)
        {
            /* Get channel object */
            chObj = &instObj->chObj[streamId][chId];

            /* Check if the number of elements in the queue is sufficient to */
            numElemInReqQ = BspUtils_getNumQElem(chObj->bmObj.reqQ);
            /* Check if the primed buffers are sufficient - For frame drop no
             * frames need to be queued!! */
            if (((VPS_CAPT_BCM_FRM_DROP != instObj->createPrms.bufCaptMode) &&
                 (numElemInReqQ == 0U)) &&
                (FALSE == chObj->isStreamByPassed))
            {
                GT_2trace(
                    VpsDrvCaptTrace, GT_ERR,
                    "Insufficient buffers queued for stream %d channel %d\r\n",
                    streamId, chId);
                retVal = FVID2_EFAIL;
                break;
            }

#ifdef VPS_VIP_BUILD
            /* Reset subframe count every start */
            chObj->subFrameNum = 0U;
#endif
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->overflowCount = 0U;
        retVal = vpsDrvCaptStartCore(instObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Core start failed!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        instObj->state = VPS_CAPT_STATE_RUNNING;
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvCaptStopIoctl(VpsDrv_CaptInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    UInt32 streamId, chId;
    VpsDrv_CaptChObj  *chObj;
    VpsDrv_CaptQueObj *qObj;

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    retVal = vpsDrvCaptStopCore(instObj);
    if (FVID2_SOK == retVal)
    {
        cookie = BspOsal_disableInterrupt();

        instObj->state = VPS_CAPT_STATE_STOPPED;

        /* For every stream and every channel */
        for (streamId = 0U;
             streamId < instObj->createPrms.numStream;
             streamId++)
        {
            for (chId = 0; chId < instObj->createPrms.numCh; chId++)
            {
                /* Get channel object */
                chObj = &instObj->chObj[streamId][chId];

                /* Dequeue all the current frames and put back in
                 * request queue */
                while (1U)
                {
                    qObj = (VpsDrv_CaptQueObj *)
                           BspUtils_dequeue(chObj->bmObj.curQ);
                    if (NULL == qObj)
                    {
                        break;
                    }
                    qObj->creditCnt = 0U;
                    BspUtils_queueBack(chObj->bmObj.reqQ, &qObj->qElem, qObj);
                }
            }
        }

        BspOsal_restoreInterrupt(cookie);
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvCaptGetStatusIoctl(const VpsDrv_CaptInstObj *instObj,
                                      Vps_CaptStatus           *captStat)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    if (NULL == captStat)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        captStat->queueCount    = instObj->queueCount;
        captStat->dequeueCount  = instObj->dequeueCount;
        captStat->overflowCount = instObj->overflowCount;
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvCaptGetChStatusIoctl(const VpsDrv_CaptInstObj   *instObj,
                                        const Vps_CaptChStatusArgs *chStatArgs,
                                        Vps_CaptChStatus           *chStat)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chId, lChNum, drvStreamId;
    UInt64 curTime, curTimeMs;
    const VpsDrv_CaptChObj *chObj;
    VpsDrv_CaptCommonObj   *pObj;

    pObj = &gVpsCaptCommonObj;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Check for NULL pointers */
    if ((NULL == chStatArgs) || (NULL == chStat))
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Map user channel number to driver channel number */
        lChNum = (UInt32) pObj->fvidChNumToLogChNumMap[chStatArgs->chNum];

        /* Get channel and stream ID */
        chId        = Vps_captGetChId(lChNum);
        drvStreamId = Vps_captGetStreamId(lChNum);
        if (chId >= instObj->createPrms.numCh)
        {
            /* Invalid channel ID */
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid channel ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        if (drvStreamId >= instObj->createPrms.numStream)
        {
            /* Invalid stream ID */
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid stream ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /*
         * valid instance, stream and channel
         */
        /* Get channel specific object in the required instance */
        chObj = &instObj->chObj[drvStreamId][chId];
        BspUtils_memcpy(chStat, &chObj->stat, sizeof (*chStat));

        /*
         * Detect video
         */
        if (instObj->state == VPS_CAPT_STATE_RUNNING)
        {
            /* get current time */
            GT_assert(VpsDrvCaptTrace, (NULL != instObj->getTimeStamp));
            curTime   = instObj->getTimeStamp(NULL);
            curTimeMs = (curTime / 1000U);
            if (curTimeMs < (chObj->stat.lastFrmTimeStamp + curTimeMs))
            {
                chStat->isVideoDetected = (UInt32) TRUE;
            }
            else
            {
                chStat->isVideoDetected = (UInt32) FALSE;
            }
        }
        else
        {
            /* If captrue is stopped return video is detected as the IOCTL
             * could be called very late after stopping */
            chStat->isVideoDetected = (UInt32) TRUE;
        }
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvCaptSetFrmSkipIoctl(VpsDrv_CaptInstObj      *instObj,
                                       const Vps_CaptFrameSkip *frmSkipPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chId, lChNum, drvStreamId;
    VpsDrv_CaptChObj     *chObj;
    VpsDrv_CaptCommonObj *pObj;

    pObj = &gVpsCaptCommonObj;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    /* Take the instance semaphore */
    BspOsal_semWait(instObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Check for NULL pointers */
    if (NULL == frmSkipPrms)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    if (instObj->state == VPS_CAPT_STATE_IDLE)
    {
        GT_0trace(
            VpsDrvCaptTrace, GT_ERR,
            "Invalid state: Can't dequeue to an un-opened instance!!\r\n");
        retVal = FVID2_EFAIL;
    }
    if (instObj->createPrms.bufCaptMode != VPS_CAPT_BCM_FRM_DROP)
    {
        GT_0trace(
            VpsDrvCaptTrace, GT_ERR,
            "Frame skip supported only for frame drop mode!!\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Map user channel number to driver channel number */
        lChNum = (UInt32) pObj->fvidChNumToLogChNumMap[frmSkipPrms->chNum];

        /* Get channel and stream ID */
        chId        = Vps_captGetChId(lChNum);
        drvStreamId = Vps_captGetStreamId(lChNum);
        if (chId >= instObj->createPrms.numCh)
        {
            /* Invalid channel ID */
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid channel ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        if (drvStreamId >= instObj->createPrms.numStream)
        {
            /* Invalid stream ID skip this frame queue */
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid stream ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /*
         * valid instance, stream and channel
         */
        /* Get channel specific object in the required instance */
        chObj = &instObj->chObj[drvStreamId][chId];

        /* Change frame skip mask */
        chObj->frmSkipMask = frmSkipPrms->frmSkipMask;
    }

    /* Post the instance semaphore */
    BspOsal_semPost(instObj->lockSem);

    return (retVal);
}

static Int32 vpsDrvCaptRegisterTimeStampIoctl(
    VpsDrv_CaptInstObj        *instObj,
    const Vps_TimeStampParams *timeStampPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    /* Check for NULL pointers */
    if (NULL == timeStampPrms)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* ISR might be still happening while we change pointers */
        cookie = BspOsal_disableInterrupt();

        if (NULL == timeStampPrms->timeStampFxn)
        {
            instObj->getTimeStamp = &vpsDrvCaptClockGetTicks;
        }
        else
        {
            instObj->getTimeStamp = timeStampPrms->timeStampFxn;
        }

        BspOsal_restoreInterrupt(cookie);
    }

    return (retVal);
}

