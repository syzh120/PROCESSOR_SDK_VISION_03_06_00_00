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
 *  \file vpsdrv_m2mVpeReq.c
 *
 *  \brief VPS VPE M2M driver internal file used for processing the request.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <vpedrv/src/vpsdrv_m2mVpePriv.h>

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

static Int32 vpsMdrvVpeUpdateChDesc(VpsMdrv_VpeHandleObj    *hObj,
                                    VpsMdrv_VpeChObj        *chObj,
                                    const Fvid2_ProcessList *procList,
                                    UInt32                   frmCnt,
                                    UInt32                   descSet);
static Int32 vpsMdrvVpeUpdateRtParams(VpsMdrv_VpeHandleObj     *hObj,
                                      VpsMdrv_VpeChObj         *chObj,
                                      const Vps_M2mVpeRtParams *rtPrms,
                                      UInt32                    descSet);

static void vpsMdrvVpeRetErrProcList(VpsMdrv_VpeHandleObj *hObj,
                                     VpsMdrv_VpeQueueObj  *qObj);

static Int32 vpsMdrvVpeRotateCtxBuf(VpsMdrv_VpeChObj *chObj, UInt32 inFid);

static Int32 vpsMdrvVpeAgeCtxBufs(VpsMdrv_VpeChObj *chObj,
                                  Fvid2_Frame      *curFrame);
static Int32 vpsMdrvVpeReleaseAgedCtxBufs(const VpsMdrv_VpeHandleObj *hObj,
                                          VpsMdrv_VpeQueueObj        *qObj);

static Int32 vpsMdrvVpeClearInFrameList(Fvid2_FrameList *framesList,
                                        UInt32           numFrames);

static void vpsMdrvVpeSubFrmUpdate(const VpsMdrv_SubFrameChInst *slcData,
                                   Fvid2_Frame                  *inFrm,
                                   Fvid2_Frame                  *outFrm,
                                   const Vps_M2mVpeRtParams     *rtParams);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          FVID2 API Functions                               */
/* ========================================================================== */

/**
 *  VpsMdrv_vpeMlmCbFxn
 */
Int32 VpsMdrv_vpeMlmCbFxn(const Mlm_SubmitReqInfo *reqInfo)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeQueueObj  *qObj;
    VpsMdrv_VpeHandleObj *hObj;
    VpsMdrv_VpeInstObj   *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != reqInfo));
    qObj = (VpsMdrv_VpeQueueObj *) reqInfo->cbArg;
    GT_assert(VpsMdrvVpeTrace, (NULL != qObj));
    hObj = qObj->hObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Check whether the request type is frame or coefficient */
    if (VPSMDRV_QOBJ_TYPE_FRAMES == qObj->qObjType)
    {
        /* Free the descriptor set */
        vpsMdrvVpeFreeDescSet(hObj, qObj->descSetInUse);

        /* Get the field buffers that can be released to apps */
        retVal = vpsMdrvVpeReleaseAgedCtxBufs(hObj, qObj);

        if (0U != hObj->numUnProcessedReq)
        {
            hObj->numUnProcessedReq--;
        }

        /*  Queue the completed request to the Done Queue */
        BspUtils_queue(hObj->doneQ, &qObj->qElem, qObj);
        qObj = NULL;

        /* If callback is registered, intimate the application that a
         * request is completed and is ready to be dequeued */
        if (NULL != hObj->fdmCbPrms.fdmCbFxn)
        {
            hObj->fdmCbPrms.fdmCbFxn(hObj->fdmCbPrms.fdmData, NULL);
        }

        if (hObj->isStopped == FALSE)
        {
            /* Check if any request is pending */
            qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->reqQ);
            if (NULL != qObj)
            {
                /* Get a free descriptor to work with */
                qObj->descSetInUse = vpsMdrvVpeAllocDescSet(hObj);
                GT_assert(VpsMdrvVpeTrace,
                          (VPSMDRV_VPE_INVALID_DESC_SET != qObj->descSetInUse));
                GT_assert(VpsMdrvVpeTrace,
                          (VPSMDRV_VPE_MAX_DESC_SET == qObj->descSetInUse));

                /* We have a free descriptor set, update the descriptors,
                 * link the channels and queue it to MLM for processing */
                retVal = vpsMdrvVpeProcessReq(hObj, qObj);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                              "Process request failed\r\n");
                }
            }
        }
        else
        {
            /* Stop called when requests are being processed.
             * Signal the semaphore so that stop IOCTL can unblock */
            BspOsal_semPost(hObj->stopSyncSem);
        }

        /* If error occurs free objects */
        if (FVID2_SOK != retVal)
        {
            if (NULL != qObj)
            {
                /* Return process list to application using error callback */
                vpsMdrvVpeRetErrProcList(hObj, qObj);

                /* Return back the queue object to the free queue */
                BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
                qObj = NULL;
            }
        }
    }
    else if (VPSMDRV_QOBJ_TYPE_COEFF == qObj->qObjType)
    {
        /* Callback got for programming of coefficients. */
        /* Signal the semaphore */
        BspOsal_semPost(hObj->ctrlSem);
    }
    else
    {
        /* Do nothing - this won't happen */
    }

    return (FVID2_SOK);
}

/**
 *  vpsMdrvVpeProcessReq
 */
Int32 vpsMdrvVpeProcessReq(VpsMdrv_VpeHandleObj *hObj,
                           VpsMdrv_VpeQueueObj  *qObj)
{
    Int32               retVal = FVID2_SOK;
    Bool                done[VPS_M2M_SCALER_ID_MAX] = {FALSE};
    UInt32              descSet, chNum;
    UInt32              frmCnt, numFrames;
    UInt32              rldSize, listPostSize;
    UInt32              scalerId, coreCnt;
    void               *descPtr = NULL, *listPostDesc = NULL;
    VpsMdrv_VpeChObj   *chObj;
    VpsMdrv_VpeInstObj *instObj;
    Fvid2_ProcessList  *procList;
    void               *rldDesc = NULL;
    Vps_M2mVpeRtParams *rtPrms  = NULL;
    /* for subframe processing */
    Vps_FrameParams     inFrmPrms;
    Vps_FrameParams     outFrmPrms;
    Fvid2_CropConfig    scCropCfg;
    Vps_ScRtConfig      scRtCfg;
    Vps_M2mVpeRtParams  locRtPrms;
    Ptr inAddrY, inAddrC, outAddr;
    Fvid2_Frame        *inFrm, *outFrm;

    /* Remove GCC warnings */
    inFrm   = outFrm  = (Fvid2_Frame *) NULL;
    inAddrY = inAddrC = outAddr = (Ptr) NULL;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != qObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Get the numFrames from in frame list */
    procList = &qObj->procList;
    GT_assert(VpsMdrvVpeTrace, (NULL != procList->inFrameList[0U]));
    numFrames = procList->inFrameList[0U]->numFrames;
    descSet   = qObj->descSetInUse;

    rldDesc      = NULL;
    listPostDesc = NULL;
    listPostSize = 0U;

    /* Update the descriptors of the requested channels and link them */
    for (frmCnt = 0U; frmCnt < numFrames; frmCnt++)
    {
        if (NULL == procList->inFrameList[0U]->frames[frmCnt])
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
            retVal = FVID2_EBADARGS;
        }

        if (FVID2_SOK == retVal)
        {
            /* Get the channel number from the in frame list's frame pointer */
            chNum = procList->inFrameList[0U]->frames[frmCnt]->chNum;

            /* Check if the channel number is within the allocated one */
            if (chNum >= hObj->createPrms.numCh)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
                retVal = FVID2_EOUT_OF_RANGE;
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Get the channel object */
            chObj = hObj->chObjs[chNum];
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

            if (TRUE != chObj->isParamSet)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Set the params before queuing request!!\r\n");
                retVal = FVID2_EFAIL;
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Update runtime params */
            /* Assign the runtime params if present in any of the core frame */
            rtPrms = (Vps_M2mVpeRtParams *)
                     procList->inFrameList[0U]->frames[frmCnt]->perFrameCfg;
        }

        /*
         * Do SubFrame processing if configured for this channel/frame:
         * 1. Initialise subframe instance memory of channel at first subframe
         *    and keep calling SubFrame pre and post calc functions for
         *    subsequent subFrame;
         * 2. Update rtPrms to configure subframe stuff to Descriptors by Core
         *    functions.
         * 3. Make a copy and update inFrm and outFrm addresses here
         *    considering offset values required for subframe Line memory and
         *    pass to VpsMdrvScUpdateDescs() to be programmed in Desc.
         *    These values are restored after VpsMdrvScUpdateDescs() function
         *    returns.
         *    This is needed as APP expects ProcList with No changes.
         *  NOTE: No support for runtime subframe enable/disable support, can be
         *  added later if needed
         */
        if ((FVID2_SOK == retVal) && (TRUE == chObj->slcChObj.subFrameEnable))
        {
            inFrm  = procList->inFrameList[0U]->frames[frmCnt];
            outFrm = procList->outFrameList[0U]->frames[frmCnt];

            chObj->slcChObj.subFrameNum     = inFrm->subFrameInfo->subFrameNum;
            chObj->slcChObj.slcLnsAvailable = inFrm->subFrameInfo->numInLines;

            if (chObj->slcChObj.subFrameNum == 0U)
            {
                vpsMdrvScSubFrameInitInfo(&chObj->slcChObj);
                chObj->slcChObj.filtType =
                    chObj->scFactor[VPS_M2M_VPE_SCALER_ID_SC0].vsType;
                outFrm->subFrameInfo->numOutLines = 0U;
            }
            vpsMdrvScSubFrameCalcInfo(&chObj->slcChObj);
            if (rtPrms == NULL)
            {
                /* use locally allocated rtPrms memory
                 * TODO: To avoid run-time cycles penalty in allocating and
                 * assigning the values/ check for NULL in all RtPrms sub
                 * structures,
                 * Allocate this as global static variable and use across all
                 * channels as this is just needed locally and all values are
                 * updated for every call */
                locRtPrms.inFrmPrms  = &inFrmPrms;
                locRtPrms.outFrmPrms = &outFrmPrms;
                locRtPrms.scCropCfg  = &scCropCfg;
                locRtPrms.scRtCfg    = &scRtCfg;
                locRtPrms.deiRtCfg   = NULL;
                rtPrms = &locRtPrms;
                /* initialise non subframe specific params in rtParams */
                inFrmPrms.memType     = chObj->vpePrms.inMemType;
                inFrmPrms.dataFormat  = chObj->vpePrms.inFmt.dataFormat;
                outFrmPrms.memType    = chObj->vpePrms.outMemType;
                outFrmPrms.dataFormat = chObj->vpePrms.outFmt.dataFormat;
            }
            else
            {
                /* TODO: frame level rtPrms change support in subframe mode*/
            }

            /* make local copy of inFrm and outFrm address */
            inAddrY =
                inFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_Y_ADDR_IDX];
            inAddrC =
                inFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_CBCR_ADDR_IDX];
            outAddr =
                outFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX];

            vpsMdrvVpeSubFrmUpdate(
                &chObj->slcChObj,
                inFrm,
                outFrm,
                rtPrms);
        }

        /* Update RT params if they have been provided in this process frames
         * call, OR if the descriptor set is dirty due to RT params being
         * previously provided, and now needs to be updated. */
        if ((FVID2_SOK == retVal) && ((NULL != rtPrms) ||
                                      ((UInt32) TRUE == chObj->isDescDirty[descSet])))
        {
            retVal = vpsMdrvVpeUpdateRtParams(hObj, chObj, rtPrms, descSet);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not update runtime params for channel %d!\r\n",
                          chNum);
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Update channel descriptors */
            retVal = vpsMdrvVpeUpdateChDesc(hObj, chObj, procList, frmCnt,
                                            descSet);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(
                    VpsMdrvVpeTrace, GT_ERR,
                    "Update of channel descriptor failed for channel %d\r\n",
                    chNum);
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* If Lazy Loading is enabled for any scaler and the scaler is not
             * in bypass, convert the dummy descriptors to coeff descriptors if
             * required. */
            for (scalerId = 0U; scalerId < VPS_M2M_SCALER_ID_MAX; scalerId++)
            {
                if (((UInt32) TRUE == instObj->lazyLoadingEnable[scalerId]) &&
                    ((Bool) TRUE != done[scalerId]))
                {
                    coreCnt = instObj->scalerCoreId[scalerId];
                    /* Check if the scaler is enabled. */
                    if (VPSMDRV_VPE_MAX_CORE != coreCnt)
                    {
                        /* Check if horizontal scaling coeff desc has to be
                         * created. */
                        if ((instObj->curScFactor[scalerId].hScalingSet !=
                             chObj->scFactor[scalerId].hScalingSet) &&
                            (chObj->scFactor[scalerId].hScalingSet !=
                             VPS_SC_SET_MAX))
                        {
                            VpsHal_vpdmaCreateConfigDesc(
                                chObj->coeffDesc
                                [descSet]
                                [VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC *
                                 scalerId],
                                chObj->coeffConfigDest[coreCnt],
                                VPSHAL_VPDMA_CPT_BLOCK_SET,
                                VPSHAL_VPDMA_CCT_INDIRECT,
                                chObj->horzCoeffOvlySize[coreCnt],
                                chObj->horzCoeffMemPtr[coreCnt],
                                0U,
                                (UInt16) chObj->horzCoeffOvlySize[coreCnt]);

                            /* Now set the current hScalingSet to that of
                             * this channel. */
                            instObj->curScFactor[scalerId].hScalingSet =
                                chObj->scFactor[scalerId].hScalingSet;
                        }
                        else /* Create dummy descriptor */
                        {
                            VpsHal_vpdmaCreateDummyDesc(
                                chObj->coeffDesc
                                [descSet]
                                [VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC *
                                 scalerId]);
                        }

                        /* Check if vertical scaling coeff desc has to be
                         * created. */
                        if ((instObj->curScFactor[scalerId].vScalingSet !=
                             chObj->scFactor[scalerId].vScalingSet) &&
                            (chObj->scFactor[scalerId].vScalingSet !=
                             VPS_SC_SET_MAX))
                        {
                            VpsHal_vpdmaCreateConfigDesc(
                                chObj->coeffDesc
                                [descSet]
                                [(VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC
                                  * scalerId) + 1U],
                                chObj->coeffConfigDest[coreCnt],
                                VPSHAL_VPDMA_CPT_BLOCK_SET,
                                VPSHAL_VPDMA_CCT_INDIRECT,
                                chObj->vertCoeffOvlySize[coreCnt],
                                chObj->vertCoeffMemPtr[coreCnt],
                                (Ptr) (chObj->horzCoeffOvlySize[coreCnt]),
                                (UInt16) chObj->vertCoeffOvlySize[coreCnt]);

                            /* Now set the current vsType and vScalingSet to
                             * that of this channel. */
                            instObj->curScFactor[scalerId].vScalingSet =
                                chObj->scFactor[scalerId].vScalingSet;
                        }
                        else /* Create dummy descriptor */
                        {
                            VpsHal_vpdmaCreateDummyDesc(
                                chObj->coeffDesc
                                [descSet]
                                [(VPSMDRV_VPE_RT_COEFF_CFG_DESC_PER_SC
                                  * scalerId) + 1U]);
                        }
                    }
                }
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Get the descriptor address and size to which the previous reload
             * descriptor should be linked */
            descPtr = chObj->firstDesc[descSet];
            rldSize = (UInt32) (chObj->totalDescMem / VPSMDRV_VPE_MAX_DESC_SET);

            if (rldDesc != NULL)
            {
                /* Link the reload descriptor of previous channel to the
                 * descriptor of this channel */
                VpsHal_vpdmaCreateRLCtrlDesc(rldDesc, descPtr, rldSize);
            }
            else
            {
                /* Per handle configuration, store the first channel's start
                 * addr */
                listPostDesc = descPtr;
                listPostSize = rldSize;
            }

            /* Store the reload descriptor of this channel, so that next channel
             * will link to it */
            rldDesc = chObj->rldDesc[descSet];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != rldDesc));
        }

        /*** Do subframe specific post processing ****/
        if ((FVID2_SOK == retVal) && (TRUE == chObj->slcChObj.subFrameEnable))
        {
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != inFrm));
            GT_assert(VpsMdrvVpeTrace, (NULL != outFrm));

            outFrm->subFrameInfo->subFrameNum  = chObj->slcChObj.subFrameNum;
            outFrm->subFrameInfo->numOutLines += chObj->slcChObj.tarH;

            vpsMdrvScSubFrameCalcPostProcInfo(&chObj->slcChObj);

            /* restore inFrm and outFrm addresses to pass processlist
             * intact to application */
            inFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_Y_ADDR_IDX]
                = inAddrY;
            inFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_CBCR_ADDR_IDX]
                = inAddrC;
            outFrm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX]
                = outAddr;
        }

        if (retVal != FVID2_SOK)
        {
            break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /*
         * Update the MLM parameters and submit the request to MLM
         */
        GT_assert(VpsMdrvVpeTrace, (NULL != listPostDesc));
        GT_assert(VpsMdrvVpeTrace, (NULL != rldDesc));

        /* Always handle descriptor is the start */
        qObj->mlmReqInfo.reqStartAddr     = listPostDesc;
        qObj->mlmReqInfo.firstChannelSize = listPostSize;
        /* Last channel reload descriptor */
        qObj->mlmReqInfo.lastRlDescAddr = rldDesc;
        /* We have already put SOCH for each channel in the driver,
         * so tell MLM not to put again */
        qObj->mlmReqInfo.numChannels = 0U;
        if (TRUE == hObj->filmMode)
        {
            qObj->mlmReqInfo.submitReqType = MLM_SRT_USE_SOR_NO_SOC;
        }
        else
        {
            qObj->mlmReqInfo.submitReqType = MLM_SRT_NO_SOC;
        }

        qObj->mlmReqInfo.cbArg = qObj;
        retVal = Mlm_submit(instObj->mlmHandle, &qObj->mlmReqInfo);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Submission to MLM failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeAllocDescSet
 */
UInt32 vpsMdrvVpeAllocDescSet(VpsMdrv_VpeHandleObj *hObj)
{
    UInt32 allocedDescSet = VPSMDRV_VPE_INVALID_DESC_SET;
    UInt32 descSet;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
    {
        if ((UInt32) TRUE == hObj->isDescSetFree[descSet])
        {
            /* Set flag as alloced */
            hObj->isDescSetFree[descSet] = (UInt32) FALSE;
            allocedDescSet = descSet;
            break;
        }
    }

    return (allocedDescSet);
}

/**
 *  vpsMdrvVpeFreeDescSet
 */
Int32 vpsMdrvVpeFreeDescSet(VpsMdrv_VpeHandleObj *hObj, UInt32 descSet)
{
    Int32 retVal = FVID2_SOK;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    /* Assert if index is more than the index */
    GT_assert(VpsMdrvVpeTrace, (descSet < VPSMDRV_VPE_MAX_DESC_SET));

    /* Set flag as free */
    hObj->isDescSetFree[descSet] = (UInt32) TRUE;

    return (retVal);
}

/**
 *  vpsMdrvVpeUpdateChDesc
 */
static Int32 vpsMdrvVpeUpdateChDesc(VpsMdrv_VpeHandleObj    *hObj,
                                    VpsMdrv_VpeChObj        *chObj,
                                    const Fvid2_ProcessList *procList,
                                    UInt32                   frmCnt,
                                    UInt32                   descSet)
{
    Int32        retVal = FVID2_SOK;
    UInt32       coreCnt;
    UInt32       frmListIdx;
    UInt32       fid;
    UInt32       firstOut = (UInt32) TRUE;
    Fvid2_Frame *frame;
    Fvid2_FrameList        *frmList;
    VpsMdrv_VpeInstObj     *instObj;
    const Vcore_M2mOps     *coreOps;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != procList));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    vpeCoreCtxBuf = &chObj->vpeCoreCtxBuf;

    frmListIdx = 0U;
    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Program cores only if needed for that instance */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->updateDesc));

            /* Get the frame list pointer and the frame pointer */
            if (coreCnt < VPSMDRV_VPE_MAX_INPUTS)
            {
                /* Get the frame list from in frame list */
                frmList = procList->inFrameList[frmListIdx];
                frmListIdx++;
            }
            else
            {
                /* Reset index for the first out frame list */
                if ((UInt32) TRUE == firstOut)
                {
                    frmListIdx = 0U;
                    firstOut   = (UInt32) FALSE;
                }
                /* Get the frame list from out frame list */
                frmList = procList->outFrameList[frmListIdx];
                frmListIdx++;
            }
            GT_assert(VpsMdrvVpeTrace, (NULL != frmList));
            frame = frmList->frames[frmCnt];
            GT_assert(VpsMdrvVpeTrace, (NULL != frame));

            fid = 0U;
            if ((FVID2_FID_BOTTOM == frame->fid) &&
                (coreCnt < VPSMDRV_VPE_MAX_INPUTS))
            {
                /* Use FID only for input frame. Output frame FID should always
                 * be 0. */
                fid = 1U;
            }

            /* In bypass mode FID should be 0 */
            if ((1U == fid) && (FALSE == chObj->vpeCoreCtxInfo.isDeinterlacing))
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "FID should be 0 for DEI bypass mode!!\r\n");
                /* Override and continue processing */
                fid = 0U;
            }

            /* In case of TI814x/TI813x/TI811x, When we do not have enough
             * contexts,
             * current field is treated as context fields. Also the DEI always
             * generates output based on N-1 field. Hence we should use the
             * input FID for N-1 and ^FID for N and N-2 inputs. Otherwise
             * the first frame output will move up/down depending on input
             * frame FID. */
            if ((FALSE == chObj->isCtxFieldInit) &&
                (TRUE == chObj->vpeCoreCtxInfo.isDeinterlacing) &&
                (coreCnt < VPSMDRV_VPE_MAX_INPUTS))
            {
                fid = fid ^ 0x1U;
            }

            /* Update the core descriptors for the FID and buffer address */
            retVal = coreOps->updateDesc(
                hObj->coreHandle[coreCnt],
                &chObj->coreDescMem[descSet][coreCnt],
                frame,
                fid);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not update desc for core %d!\r\n", coreCnt);
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        if ((TRUE == chObj->vpeCoreCtxInfo.isDeinterlacing) ||
            (TRUE == chObj->vpeCoreCtxInfo.isTnrMode))
        {
            /* Check if context buffers are set by application */
            if (TRUE != chObj->isDeiCtxBufSet)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "DEI context buffers are not set for channel %d!\r\n",
                          chObj->chNum);
                retVal = FVID2_EFAIL;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (TRUE == chObj->vpeCoreCtxInfo.isDeinterlacing)
        {
            coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->updateMode));

            /* Note: It is required to work in Line average mode until
             * enough previous fields are captured. After that, DEI will
             * work in configured mode. */
            if (chObj->prevFldState <= chObj->vpeCoreCtxInfo.numPrevFld)
            {
                retVal = coreOps->updateMode(
                    hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                    chObj->chNum,
                    &chObj->coreDescMem[descSet]
                    [VPSMDRV_VPE_VPE_CORE_IDX],
                    chObj->prevFldState);
            }

            retVal = vpsMdrvVpeRotateCtxBuf(
                chObj,
                procList->inFrameList[0U]->frames[frmCnt]->fid);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(
                    VpsMdrvVpeTrace, GT_ERR,
                    "Error rotating context buffers in normal DEI mode!\r\n");
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Age the fields even though interlacing is bypassed, as we require
         * to release the current field. This function would mark the current
         * field as completed, when de-interlacing is in bypass mode */
        retVal = vpsMdrvVpeAgeCtxBufs(
            chObj,
            procList->inFrameList[0U]->frames[frmCnt]);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Error ageing context buffers in normal DEI mode!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Update the context descriptors in deinterlacing mode */
        if ((TRUE == chObj->vpeCoreCtxInfo.isDeinterlacing) ||
            (TRUE == chObj->vpeCoreCtxInfo.isTnrMode))
        {
            coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->updateContext));

            /* Update the context descriptors */
            retVal = coreOps->updateContext(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                chObj->chNum,
                &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX],
                vpeCoreCtxBuf);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not update DEI context desc!\r\n");
            }
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeUpdateRtParams
 */
static Int32 vpsMdrvVpeUpdateRtParams(VpsMdrv_VpeHandleObj     *hObj,
                                      VpsMdrv_VpeChObj         *chObj,
                                      const Vps_M2mVpeRtParams *rtPrms,
                                      UInt32                    descSet)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt, scalerId;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;
    Vcore_VpeRtParams   vpeRtPrms;
    Vcore_VwbRtParams   vwbRtPrms;
    Vcore_M2mDescMem   *coreDescMem;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Update the VPE runtime parameters if DEI is present */
    if ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VPE_CORE_IDX])
    {
        coreOps     = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
        coreDescMem = &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX];
        /* NULL pointer check */
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->updateRtMem));

        if ((NULL != rtPrms) &&
            ((NULL != rtPrms->inFrmPrms) ||
             (NULL != rtPrms->outFrmPrms) ||
             (NULL != rtPrms->scCropCfg) ||
             (NULL != rtPrms->scRtCfg) ||
             (NULL != rtPrms->deiRtCfg)))
        {
            /* Copy the VPE runtime parameters */
            vpeRtPrms.inFrmPrms  = rtPrms->inFrmPrms;
            vpeRtPrms.posCfg     = NULL;
            vpeRtPrms.outFrmPrms = rtPrms->outFrmPrms;
            vpeRtPrms.scCropCfg  = rtPrms->scCropCfg;
            vpeRtPrms.scRtCfg    = rtPrms->scRtCfg;
            vpeRtPrms.deiRtCfg   = rtPrms->deiRtCfg;

            /* Update the runtime configuration in core descriptors */
            retVal = coreOps->updateRtMem(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                coreDescMem,
                chObj->chNum,
                &vpeRtPrms,
                0U);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not update runtime desc for VPE core!\r\n");
            }

            /* Check DEI runtime configuration */
            if (NULL != rtPrms->deiRtCfg)
            {
                if (TRUE == rtPrms->deiRtCfg->resetDei)
                {
                    /* If the reset is required, initialize the prevFldState to
                     * zero again so that DEI will start working in Line
                     * average mode for first few fields and builds up the
                     * context again. */
                    chObj->prevFldState = 0U;
                }

                if (TRUE == rtPrms->deiRtCfg->fldRepeat)
                {
                    /* When the application repeats the input frame, don't
                     * rotate the context buffers so that the output will
                     * remain the same as the previous output. */
                    chObj->dontRotateCtxBuf = (UInt32) TRUE;
                }
            }
        }
        else if ((UInt32) TRUE == chObj->isDescDirty[descSet])
        {
            /* Descriptor is dirty, use the core to just update the
             * descriptors without providing any parameters */
            retVal = coreOps->updateRtMem(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                coreDescMem,
                chObj->chNum,
                NULL,
                0U);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not update runtime desc for VPE core!\r\n");
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Update the VWB runtime parameters if VWB path is present */
        if ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VWB_CORE_IDX])
        {
            coreOps     = instObj->coreOps[VPSMDRV_VPE_VWB_CORE_IDX];
            coreDescMem =
                &chObj->coreDescMem[descSet][VPSMDRV_VPE_VWB_CORE_IDX];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->updateRtMem));

            if ((NULL != rtPrms) && (NULL != rtPrms->outFrmPrms))
            {
                /* Copy the VWB runtime parameters */
                vwbRtPrms.outFrmPrms = rtPrms->outFrmPrms;

                /* Update the runtime configuration in core descriptors */
                retVal = coreOps->updateRtMem(
                    hObj->coreHandle[VPSMDRV_VPE_VWB_CORE_IDX],
                    coreDescMem,
                    chObj->chNum,
                    &vwbRtPrms,
                    0U);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                              "Could not update runtime desc for VWB core!\r\n");
                }
            }
            else if ((UInt32) TRUE == chObj->isDescDirty[descSet])
            {
                /* Descriptor is dirty, use the core to just update the
                 * descriptors without providing any parameters */
                retVal = coreOps->updateRtMem(
                    hObj->coreHandle[VPSMDRV_VPE_VWB_CORE_IDX],
                    coreDescMem,
                    chObj->chNum,
                    NULL,
                    0U);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                              "Could not update runtime desc for VWB core!\r\n");
                }
            }
            else
            {
                /* Do nothing */
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* If Lazy Loading is enabled, recalculate and set the scaling
         * factor config for the channel. */
        for (scalerId = 0U; scalerId < VPS_M2M_SCALER_ID_MAX; scalerId++)
        {
            if ((UInt32) TRUE == instObj->lazyLoadingEnable[scalerId])
            {
                /* To take care of the updated configuration due to RT
                 * params, go down into the core to get the scaling factor
                 * config for the channel.
                 */
                retVal = vpsMdrvVpeGetScFactorCfg(hObj, chObj, scalerId);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(
                        VpsMdrvVpeTrace, GT_ERR,
                        "EFAIL: Getting the Scaling Factor Config Failed\r\n");
                }
                /* The scaling ratio does not change for sub-frame scaling
                 * from what was set originally when the scaling factor
                 * config was calculated. The scaling ratio for each slice
                 * will be the same as that for the whole frame.
                 */
            }
        }

        if (NULL != rtPrms)
        {
            /* Update the dirty flags */
            /* Mark all other sets as dirty except the current descriptor set */
            for (cnt = 0U; cnt < VPSMDRV_VPE_MAX_DESC_SET; cnt++)
            {
                chObj->isDescDirty[cnt] = (UInt32) TRUE;
            }
        }

        /* Mark the current set as clean */
        chObj->isDescDirty[descSet] = (UInt32) FALSE;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeRetErrProcList
 */
static void vpsMdrvVpeRetErrProcList(VpsMdrv_VpeHandleObj *hObj,
                                     VpsMdrv_VpeQueueObj  *qObj)
{
    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != qObj));

    if ((NULL != hObj->fdmCbPrms.fdmErrCbFxn) &&
        (NULL != hObj->fdmCbPrms.errList))
    {
        /* Copy the driver's process list to application's error process list */
        Fvid2_copyProcessList(
            (Fvid2_ProcessList *) hObj->fdmCbPrms.errList,
            (Fvid2_ProcessList *) &qObj->procList);

        /* Call the application's error call back function */
        hObj->fdmCbPrms.fdmErrCbFxn(
            hObj->fdmCbPrms.fdmData,
            hObj->fdmCbPrms.errList,
            NULL);
    }

    /* Decrement the pending request count */
    if (0U != hObj->numPendReq)
    {
        hObj->numPendReq--;
    }

    return;
}

/**
 * Rotate context buffers
 */
static Int32 vpsMdrvVpeRotateCtxBuf(VpsMdrv_VpeChObj *chObj, UInt32 inFid)
{
    Int32  retVal = FVID2_SOK;
    UInt32 bCnt;
    UInt32 tempIdx, tempFid, fid;
    UInt8 *tempPtr;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    vpeCoreCtxBuf = &chObj->vpeCoreCtxBuf;

    /* Rotate context buffers */
    if (FALSE == chObj->dontRotateCtxBuf)
    {
        /* Rotate only if no invalid frame size error occurs */
        if (0U == chObj->fldIdx)
        {
            if (chObj->deiCtxInfo.numFld > 0U)
            {
                chObj->fldIdx = chObj->deiCtxInfo.numFld - 1U;
            }
        }
        else
        {
            chObj->fldIdx--;
        }
        if (0U == chObj->mvIdx)
        {
            if (chObj->deiCtxInfo.numMv > 0U)
            {
                chObj->mvIdx = chObj->deiCtxInfo.numMv - 1U;
            }
        }
        else
        {
            chObj->mvIdx--;
        }
        if (0U == chObj->mvstmIdx)
        {
            if (chObj->deiCtxInfo.numMvstm > 0U)
            {
                chObj->mvstmIdx = chObj->deiCtxInfo.numMvstm - 1U;
            }
        }
        else
        {
            chObj->mvstmIdx--;
        }
    }

    if (FVID2_FID_BOTTOM == inFid)
    {
        fid = 1U;
    }
    else
    {
        fid = 0U;
    }

    tempIdx = chObj->mvIdx;
    tempFid = fid;
    for (bCnt = 0U; bCnt < chObj->vpeCoreCtxInfo.numMvIn; bCnt++)
    {
        tempPtr = (UInt8 *) chObj->deiCtxBuf.mvBuf[tempIdx];
        GT_assert(VpsMdrvVpeTrace, (NULL != tempPtr));

        /* Assign the MV buffer pointer */
        vpeCoreCtxBuf->mvInBuf[bCnt] = tempPtr;

        /* Assign field ID - alternatively */
        tempFid = tempFid ^ 1U;
        vpeCoreCtxBuf->mvInFid[bCnt] = tempFid;

        /* Move to the next buffer */
        tempIdx++;
        if (tempIdx >= chObj->deiCtxInfo.numMv)
        {
            tempIdx = 0U;
        }
    }
    if (chObj->vpeCoreCtxInfo.numMvOut > 0U)
    {
        tempPtr = (UInt8 *) chObj->deiCtxBuf.mvBuf[tempIdx];
        GT_assert(VpsMdrvVpeTrace, (NULL != tempPtr));

        /* Assign the MV buffer pointer */
        vpeCoreCtxBuf->mvOutBuf = tempPtr;

        /* Move to the next buffer */
        tempIdx++;
        if (tempIdx >= chObj->deiCtxInfo.numMv)
        {
            tempIdx = 0U;
        }
    }

    if (chObj->prevFldState <= chObj->vpeCoreCtxInfo.numPrevFld)
    {
        /* If error occurs at the start-up don't move ahead - remain in
         * start-up condition only!! */
        if (FALSE == chObj->dontRotateCtxBuf)
        {
            chObj->prevFldState++;
        }
    }

    /* Reset the flag - rotation should be skipped only once for every error */
    chObj->dontRotateCtxBuf = (UInt32) FALSE;

    return (retVal);
}

/**
 * vpsMdrvVpeAgeCtxBufs
 * Age stored context buffers - This function is responsible for releasing
 * context fields held by the driver back to application, when dequeued
 * and also for storing required fields for context
 */
static Int32 vpsMdrvVpeAgeCtxBufs(VpsMdrv_VpeChObj *chObj,
                                  Fvid2_Frame      *curFrame)
{
    Int32        retVal = FVID2_SOK;
    UInt32       ctxFldIdx;
    UInt32       currFid = 0U, agedTth;
    Fvid2_Frame *agedField, *ctxField;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    vpeCoreCtxBuf = &chObj->vpeCoreCtxBuf;

    ctxField  = NULL;
    agedField = NULL;

    /* If we are not de-interlacing - just put the current input field
     * in the aged Q, when completed, the same would be populated in the
     * inFrameList */
    if (FALSE == chObj->vpeCoreCtxInfo.isDeinterlacing)
    {
        retVal = BspUtils_quePut(&chObj->agedCtxFieldQ,
                                 (Ptr) curFrame,
                                 BSP_OSAL_NO_WAIT);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not put aged fields into channels Q\r\n");
        }
    }
    else
    {
        /* Determine the field indexs of context buffer - based on current
         *  fields fid. Requires the context fields fid to be in sync with
         *  current fields fid. */
        if (FVID2_FID_BOTTOM == curFrame->fid)
        {
            currFid = 1U;
        }
        else
        {
            currFid = 0U;
        }

        /* Ageing of context fields
         * 1. If context buffer are initialized
         *      1.1. Pull out the last context field, put into Q if not
         *              duplicated field.
         *      1.2. Age others and move privious N field into N - 1,
         *              N - 1 to N - 2, etc...
         * 2. Otherwise
         *      2.1 Initialize context field with current field with TTH huge no
         *      2.2 Remmember current field with tth as
         *          VPSMDRV_VPE_MAX_FIELD_CONTEXT
         */
        if (TRUE == chObj->isCtxFieldInit)
        {
            /* Age fields */
            agedField =
                chObj->ctxFieldFifo[VPSMDRV_VPE_MAX_FIELD_CONTEXT].fieldCtxBuf;
            agedTth = chObj->ctxFieldFifo[VPSMDRV_VPE_MAX_FIELD_CONTEXT].tth;

            for (ctxFldIdx = VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                 ctxFldIdx > 0U;
                 ctxFldIdx--)
            {
                chObj->ctxFieldFifo[ctxFldIdx].fieldCtxBuf =
                    chObj->ctxFieldFifo[ctxFldIdx - 1U].fieldCtxBuf;
                chObj->ctxFieldFifo[ctxFldIdx].tth =
                    chObj->ctxFieldFifo[ctxFldIdx - 1U].tth;
                chObj->ctxFieldFifo[ctxFldIdx].tth--;
            }
            /* Release aged field
             * Do not release duped fields - For a valid context field the tth
             * would be 0. As current field has tth of value
             * VPSMDRV_VPE_MAX_FIELD_CONTEXT, and reduced every time new fields
             * are available for de-interlacing */
            if (0U == agedTth)
            {
                if (agedField != NULL)
                {
                    retVal = BspUtils_quePut(
                        &chObj->agedCtxFieldQ,
                        (Ptr) agedField,
                        BSP_OSAL_NO_WAIT);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(
                            VpsMdrvVpeTrace, GT_ERR,
                            "Could not put aged fields into channels Q\r\n");
                    }
                }
            } /* Otherwise field is duplicate field - ignore them */
            else
            {
                /* Why would this happen... */
                if ((agedTth != (VPSMDRV_VPE_DUPE_FIELD_CONTEXT - 1U)) &&
                    (agedTth != (VPSMDRV_VPE_DUPE_FIELD_CONTEXT - 2U)) &&
                    (agedTth != (VPSMDRV_VPE_DUPE_FIELD_CONTEXT)))
                {
                    GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                              "Fields Age is in-correct %d", agedTth);
                }
            }
        }
        else
        {
            /* When we do not have enough contexts, current field is treated as
             * context fields. */
            for (ctxFldIdx = 1U;
                 ctxFldIdx <= VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                 ctxFldIdx++)
            {
                chObj->ctxFieldFifo[ctxFldIdx].fieldCtxBuf = curFrame;
                chObj->ctxFieldFifo[ctxFldIdx].tth         =
                    VPSMDRV_VPE_DUPE_FIELD_CONTEXT;
            }

            /* Also invert the field ID so that the deinterlaced output of the
             * first frame is not shifted up/down. */
            currFid = currFid ^ 1U;

            chObj->isCtxFieldInit = (UInt32) TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Remmember the current field, used as N - 1 context field for the
         * field to be de-interlaced */
        chObj->ctxFieldFifo[0U].fieldCtxBuf = curFrame;
        chObj->ctxFieldFifo[0U].tth         = VPSMDRV_VPE_MAX_FIELD_CONTEXT;

        /* Update the cores context information with latest context fields */
        for (ctxFldIdx = 0U;
             ctxFldIdx < chObj->vpeCoreCtxInfo.numPrevFld;
             ctxFldIdx++)
        {
            ctxField = chObj->ctxFieldFifo[ctxFldIdx + 1U].fieldCtxBuf;
            GT_assert(VpsMdrvVpeTrace, (NULL != ctxField));

            /* Assign the field Y and CbCr buffer pointers */
            vpeCoreCtxBuf->prevInBuf[ctxFldIdx][FVID2_YUV_SP_Y_ADDR_IDX] =
                ctxField->addr[FVID2_FIELD_MODE_ADDR_IDX]
                [FVID2_YUV_SP_Y_ADDR_IDX];
            vpeCoreCtxBuf->prevInBuf[ctxFldIdx][FVID2_YUV_SP_CBCR_ADDR_IDX] =
                ctxField->addr[FVID2_FIELD_MODE_ADDR_IDX]
                [FVID2_YUV_SP_CBCR_ADDR_IDX];

            /* Assign field ID - alternatively */
            currFid = currFid ^ 1U;
            vpeCoreCtxBuf->prevInFid[ctxFldIdx] = currFid;
        }
    }

    return (retVal);
}

/**
 * vpsMdrvVpeReleaseAgedCtxBufs
 * Updates the inFrame list with the inFrames that are no longer need by the
 * driver for context.
 */
static Int32 vpsMdrvVpeReleaseAgedCtxBufs(const VpsMdrv_VpeHandleObj *hObj,
                                          VpsMdrv_VpeQueueObj        *qObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chNum;
    VpsMdrv_VpeChObj *chObj;
    Fvid2_Frame      *agedField    = NULL;
    Fvid2_FrameList  *inFramesList = NULL;
    UInt32 minCount;

    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != qObj));

    /* We will have to update only one instance of frame list. */
    inFramesList =
        qObj->procList.inFrameList[VPSMDRV_VPE_INST_IN_FRAME_LIST_USED];
    /* Inframe list will point to apps given fields, currently might be stored
     * context fields, ensure they stand cleared */
    retVal = vpsMdrvVpeClearInFrameList(inFramesList, hObj->createPrms.numCh);
    /* Though we do not return any field contexts, set the numInList to 1
     * to ensure inFrameList pointer of type Fvid2_FrameList allocated by the
     * application is not lost */
    qObj->procList.numInLists = 1U;

    for (chNum = 0U; chNum < hObj->createPrms.numCh; chNum++)
    {
        chObj = hObj->chObjs[chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        minCount = 1U;
        retVal   = BspUtils_queGet(
            &chObj->agedCtxFieldQ,
            (Ptr *) &agedField,
            minCount,
            BSP_OSAL_NO_WAIT);
        if (FVID2_SOK == retVal)
        {
            GT_assert(VpsMdrvVpeTrace, (NULL != agedField));

            inFramesList->frames[chNum] = agedField;
        } /* Otherwise, there were no aged fields available for this channel
           * ignore, move on to next channel */
    }

    /* Ensure to update the no of frames - set it to max, apps are expected
     * to look for valid frames */
    inFramesList->numFrames = hObj->createPrms.numCh;
    retVal = FVID2_SOK; /* Require to let know that everything went well
                         * even in case there were no aged fields */

    return (retVal);
}

/**
 * vpsMdrvVpeClearInFrameList
 * Set the frames held by inFrameList to NULL
 */
static Int32 vpsMdrvVpeClearInFrameList(Fvid2_FrameList *framesList,
                                        UInt32           numFrames)
{
    Int32  retVal = FVID2_SOK;
    UInt32 frmCnt;

    GT_assert(VpsMdrvVpeTrace, (NULL != framesList));

    for (frmCnt = 0U; frmCnt < numFrames; frmCnt++)
    {
        framesList->frames[frmCnt] = NULL;
    }

    return (retVal);
}

/*
 * Update processList Rtparams with subframe info calculated
 */
static void vpsMdrvVpeSubFrmUpdate(const VpsMdrv_SubFrameChInst *slcData,
                                   Fvid2_Frame                  *inFrm,
                                   Fvid2_Frame                  *outFrm,
                                   const Vps_M2mVpeRtParams     *rtParams)
{
    Vps_FrameParams  *inFrmPrms  = rtParams->inFrmPrms;
    Vps_FrameParams  *outFrmPrms = rtParams->outFrmPrms;
    Vps_ScRtConfig   *scRtparams = rtParams->scRtCfg;
    Fvid2_CropConfig *srcCropCfg = rtParams->scCropCfg;

    /* update outFrm start address with required offsets for current subframe */
    outFrm->addr[FVID2_FRAME_ADDR_IDX]
    [FVID2_YUV_INT_ADDR_IDX] =
        (Char *) outFrm->addr[FVID2_FRAME_ADDR_IDX]
        [FVID2_YUV_INT_ADDR_IDX]
        + (slcData->tarFrmW * slcData->tarBufOffset * 2);

    /* update inFrm start addresses with required offsets for current
     * subframe */
    if ((slcData->dataFmt == FVID2_DF_YUV420SP_UV) ||
        (slcData->dataFmt == FVID2_DF_YUV422SP_UV))
    {
        inFrm->addr[FVID2_FRAME_ADDR_IDX]
        [FVID2_YUV_SP_Y_ADDR_IDX] =
            (Char *) inFrm->addr[FVID2_FRAME_ADDR_IDX]
            [FVID2_YUV_SP_Y_ADDR_IDX]
            + (slcData->srcFrmW * slcData->srcBufOffset);
        inFrm->addr[FVID2_FRAME_ADDR_IDX]
        [FVID2_YUV_SP_CBCR_ADDR_IDX] =
            (Char *) inFrm->addr[FVID2_FRAME_ADDR_IDX]
            [FVID2_YUV_SP_CBCR_ADDR_IDX]
            + (slcData->srcFrmW * ((slcData->srcBufOffset) >> 1));
        inFrmPrms->pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            slcData->srcFrmW;
        inFrmPrms->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            slcData->srcFrmW;
    }
    else   /* 422 input case*/
    {
        inFrm->addr[FVID2_FRAME_ADDR_IDX]
        [FVID2_YUV_INT_ADDR_IDX] =
            (Char *) inFrm->addr[FVID2_FRAME_ADDR_IDX]
            [FVID2_YUV_INT_ADDR_IDX]
            + (slcData->srcFrmW * slcData->srcBufOffset * 2U);
        inFrmPrms->pitch[FVID2_YUV_INT_ADDR_IDX] =
            slcData->srcFrmW * 2U;
    }

    /* update rtPrms with calculated values for current subframe */
    inFrmPrms->width = slcData->srcFrmW;
    /* ?? 3 for RAV, how it handles for chroma */
    inFrmPrms->height = slcData->srcH +
                        (slcData->chrUsLnMemSlcTop + slcData->chrUsLnMemSlcBtm);

    outFrmPrms->width  = slcData->tarFrmW;
    outFrmPrms->height = slcData->tarH;
    outFrmPrms->pitch[FVID2_YUV_INT_ADDR_IDX] =
        slcData->tarFrmW * 2U;

    scRtparams->scBypass    = (UInt32) FALSE;
    scRtparams->scSetPhInfo = (UInt32) TRUE;

    if (slcData->filtType == VPS_SC_VST_POLYPHASE)
    {
        scRtparams->rowAccInc     = slcData->rowAccIncr;
        scRtparams->rowAccOffset  = slcData->rowAccOffset;
        scRtparams->rowAccOffsetB = slcData->rowAccOffsetB;
    }
    else
    {
        scRtparams->ravScFactor    = slcData->ravScFactor;
        scRtparams->ravRowAccInit  = slcData->ravRowAccInit;
        scRtparams->ravRowAccInitB = slcData->ravRowAccInitB;
    }
    srcCropCfg->cropHeight = slcData->srcH;
    srcCropCfg->cropWidth  = slcData->srcFrmW;
    srcCropCfg->cropStartX = 0U;
    srcCropCfg->cropStartY = slcData->scCropLnsTop;

    return;
}

