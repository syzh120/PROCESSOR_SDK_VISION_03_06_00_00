/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vpsdrv_captureCore.c
 *
 *  \brief File containing the VPS capture driver functions related to core
 *  interactions.
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

#define VPS_ISS_CAL_TODO_DDR_MHz    (333U * (10U ^ 6U))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef VPS_VIP_BUILD
static Int32 vpsDrvCaptOpenVipCore(VpsDrv_CaptInstObj *instObj);
static UInt32 vpsDrvCaptGetVipCoreSrcId(const VpsDrv_CaptInstObj *instObj);
static void vpsDrvCaptCopyVipParams(VpsDrv_CaptInstObj      *instObj,
                                    const Vps_CaptVipParams *vipPrms);
static void vpsDrvCaptSetVipCoreSyncParams(UInt32             videoIfMode,
                                           UInt32             videoIfWidth,
                                           UInt32             numCh,
                                           Vps_VipPortConfig *portCfg);
static Int32 vpsDrvVipParamsToCaptVipParams(const VpsCore_VipParams *inpCfg,
                                            Vps_CaptVipParams       *outCfg);
#endif  /* VPS_VIP_BUILD */

#ifdef VPS_DSS_BUILD
static Int32 vpsDrvCaptOpenDssWbCore(VpsDrv_CaptInstObj *instObj);
#endif

#ifdef VPS_CAL_BUILD
static Int32 vpsDrvCaptOpenIssCore(VpsDrv_CaptInstObj *instObj);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 vpsDrvCaptGetPropCore(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->getProperty));

    /* Get core property */
    retVal = instObj->coreOps->getProperty(
        instObj->coreInstObj,
        &instObj->coreProperty);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Get core property failed!!\r\n");
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_017)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-991) DOX_REQ_TAG(PDK-992) DOX_REQ_TAG(PDK-994)
 */
/**
 *  \brief Open and configure the core connected to the driver instance.
 */
Int32 vpsDrvCaptOpenCore(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));

    instObj->coreHandle = NULL;
    instObj->intrHandle = NULL;
#ifdef VPS_VIP_BUILD
    BspUtils_memset(&instObj->vemHandle[0U], 0, sizeof (instObj->vemHandle));
#endif  /* VPS_VIP_BUILD */

    /* Call the respective core open function */
    switch (instObj->coreProperty.name)
    {
#ifdef VPS_VIP_BUILD
        case VPSCORE_CAPT_VIP:
            retVal = vpsDrvCaptOpenVipCore(instObj);
            break;
#endif

#ifdef VPS_DSS_BUILD
        case VPSCORE_DISP_DSSWB:
            retVal = vpsDrvCaptOpenDssWbCore(instObj);
            break;
#endif

#ifdef VPS_CAL_BUILD
        case VPSCORE_CAPT_ISS:
            retVal = vpsDrvCaptOpenIssCore(instObj);
            break;
#endif      /* VPS_CAL_BUILD */

        default:
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Unknown core!!\r\n");
            retVal = FVID2_EFAIL;
            break;
    }

    return (retVal);
}

Int32 vpsDrvCaptCloseCore(VpsDrv_CaptInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
#ifdef VPS_VIP_BUILD
    UInt32 chId;
#endif  /* VPS_VIP_BUILD */

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->close));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreHandle));

#ifdef VPS_VIP_BUILD
    for (chId = 0; chId < instObj->createPrms.numCh; chId++)
    {
        if (NULL != instObj->vemHandle[chId])
        {
            Vem_unRegister(instObj->vemHandle[chId]);
            instObj->vemHandle[chId] = NULL;
        }
    }
#endif  /* VPS_VIP_BUILD */

    if (NULL != instObj->intrHandle)
    {
        BspOsal_unRegisterIntr(&instObj->intrHandle);
        instObj->intrHandle = NULL;
    }

    if (NULL != instObj->coreHandle)
    {
        /* Close core */
        retVal = instObj->coreOps->close(instObj->coreHandle);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Core close failed!!\r\n");
        }
        instObj->coreHandle = NULL;
    }

    return (retVal);
}

#ifdef VPS_VIP_BUILD
Int32 vpsDrvCaptSetVipCoreParams(VpsDrv_CaptInstObj      *instObj,
                                 const Vps_CaptVipParams *vipPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamCnt, plCnt;
    UInt32 streamId, chId;
    UInt32 event;
    VpsDrv_CaptChObj        *chObj;
    VpsCore_VipParams vipCorePrms;
    VpsCore_VipSetCfgRetPrms setCfgRetPrms;
    UInt32 numEvents = 1U;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->setParams));
    GT_assert(VpsDrvCaptTrace, (NULL != vipPrms));
    GT_assert(VpsDrvCaptTrace,
              (VPS_CAPT_VIP_STREAM_ID_MAX > instObj->createPrms.numStream));

    if (VPSCORE_CAPT_VIP != instObj->coreProperty.name)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "Can't set VIP parameter to this core\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy core parameters */
        if (NULL != vipPrms->vipPortCfg)
        {
            BspUtils_memcpy(
                &vipCorePrms.portCfg,
                vipPrms->vipPortCfg,
                sizeof (vipCorePrms.portCfg));
        }
        else
        {
            VpsVipPortConfig_init(&vipCorePrms.portCfg);
        }
        /* Set parameters passed through create params */
        vpsDrvCaptSetVipCoreSyncParams(
            instObj->createPrms.videoIfMode,
            instObj->createPrms.videoIfWidth,
            instObj->createPrms.numCh,
            &vipCorePrms.portCfg);

        if (NULL != vipPrms->scPrms)
        {
            BspUtils_memcpy(
                &vipCorePrms.scCfg,
                &vipPrms->scPrms->scCfg,
                sizeof (vipCorePrms.scCfg));
            BspUtils_memcpy(
                &vipCorePrms.inCropCfg,
                &vipPrms->scPrms->inCropCfg,
                sizeof (vipCorePrms.inCropCfg));
        }
        else
        {
            VpsScConfig_init(&vipCorePrms.scCfg);
        }
        if (NULL != vipPrms->cscCfg)
        {
            BspUtils_memcpy(
                &vipCorePrms.cscCfg,
                vipPrms->cscCfg,
                sizeof (vipCorePrms.cscCfg));
        }
        else
        {
            VpsCscConfig_init(&vipCorePrms.cscCfg);
        }
        vipCorePrms.srcColorSpace = vipPrms->inFmt.dataFormat;
        vipCorePrms.srcWidth      = vipPrms->inFmt.width;
        vipCorePrms.srcHeight     = vipPrms->inFmt.height;
        vipCorePrms.numStreams    = instObj->createPrms.numStream;
        for (streamCnt = 0U;
             streamCnt < instObj->createPrms.numStream;
             streamCnt++)
        {
            vipCorePrms.dstColorSpace[streamCnt] =
                vipPrms->outStreamInfo[streamCnt].outFmt.dataFormat;
            vipCorePrms.tarWidth[streamCnt] =
                vipPrms->outStreamInfo[streamCnt].outFmt.width;
            vipCorePrms.tarHeight[streamCnt] =
                vipPrms->outStreamInfo[streamCnt].outFmt.height;

            /* memType */
            vipCorePrms.memType[streamCnt] =
                vipPrms->outStreamInfo[streamCnt].memType;

            for (plCnt = 0U; plCnt < FVID2_MAX_PLANES; plCnt++)
            {
                vipCorePrms.pitch[streamCnt][plCnt] =
                    vipPrms->outStreamInfo[streamCnt].outFmt.pitch[plCnt];
                /* maxOutWidth */
                vipCorePrms.maxOutWidth[streamCnt][plCnt] =
                    vipPrms->outStreamInfo[streamCnt].maxOutWidth[plCnt];

                /* maxOutHeight */
                vipCorePrms.maxOutHeight[streamCnt][plCnt] =
                    vipPrms->outStreamInfo[streamCnt].maxOutHeight[plCnt];
            }
            vipCorePrms.scActive[streamCnt] =
                vipPrms->outStreamInfo[streamCnt].scEnable;

            vipCorePrms.subFrmPrms[streamCnt].subFrameEnable =
                vipPrms->outStreamInfo[streamCnt].subFrmPrms.subFrameEnable;
            vipCorePrms.subFrmPrms[streamCnt].numLinesPerSubFrame =
                vipPrms->outStreamInfo[streamCnt].subFrmPrms.
                numLinesPerSubFrame;
            vipCorePrms.subFrmPrms[streamCnt].interruptMode =
                vipPrms->outStreamInfo[streamCnt].subFrmPrms.interruptMode;
        }
        vipCorePrms.edgeInfoList.numEdges = 0U;
        vipCorePrms.edgeInfoList.list     = NULL;

        /* Configure the core */
        retVal = instObj->coreOps->setParams(instObj->coreHandle,
                                             &vipCorePrms,
                                             &setCfgRetPrms);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Set VIP parameter failed\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        vpsDrvCaptCopyVipParams(instObj, vipPrms);

        /* For every stream and every channel */
        for (streamId = 0U;
             streamId < instObj->createPrms.numStream;
             streamId++)
        {
            for (chId = 0U; chId < instObj->createPrms.numCh; chId++)
            {
                /* Get channel object */
                chObj = &instObj->chObj[streamId][chId];

                /* Unregister from VEM if subframe interrupt is already
                 * registered */
                if (NULL != chObj->vemSubFrmHandle)
                {
                    retVal = Vem_unRegister(chObj->vemSubFrmHandle);
                    GT_assert(VpsDrvCaptTrace, (FVID2_SOK == retVal));
                    chObj->vemSubFrmHandle = NULL;
                }

                /* Register subframe interrupt with event manager */
                if ((TRUE == chObj->subFrmPrms.subFrameEnable) &&
                    (NULL != chObj->subFrmPrms.subFrameCb))
                {
                    /*
                     * Note: Make subframe interrupt as highest priority
                     * compared to frame complete interrupt.
                     *
                     * Reason: If number of lines per frame is an integral
                     * multiple of sub frame size, then the sub frame interrupt
                     * and frame complete interrupt from VPDMA will happen back
                     * to back. In this case, to have proper software sync, VEM
                     * should handle sub frame interrupt first rather than
                     * frame complete. Hence make sub frame as 0th priority and
                     * frame complete as 1st priority.
                     */
                    event = setCfgRetPrms.subFrmVemEvent[streamId][0U];
                    chObj->vemSubFrmHandle = Vem_register(
                        setCfgRetPrms.subFrmVemInstId,
                        setCfgRetPrms.subFrmVemEventGroup,
                        &event,
                        numEvents,
                        VEM_PRIORITY0,
                        vpsDrvCaptVemSubFrmIsr,
                        chObj);
                    if (NULL == chObj->vemSubFrmHandle)
                    {
                        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                                  "VEM sub frame registeration failed!!\r\n");
                        retVal = FVID2_EFAIL;
                        break;
                    }
                }
            }

            /* Break if error */
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

static Int32 vpsDrvVipParamsToCaptVipParams(const VpsCore_VipParams *inpCfg,
                                            Vps_CaptVipParams       *outCfg)
{
    UInt32 strm, pl;
    Int32  retVal = BSP_SOK;
    Vps_CaptVipParams   *captVipParams;
    Vps_CaptVipScParams *captVipScParams;
    Vps_VipPortConfig   *captVipPortCfg;
    Vps_CscConfig       *captVipCscCfg;

    GT_assert(VpsDrvCaptTrace, (NULL != inpCfg));
    GT_assert(VpsDrvCaptTrace, (NULL != outCfg));

    captVipParams   = outCfg;
    captVipScParams = outCfg->scPrms;
    captVipPortCfg  = outCfg->vipPortCfg;
    captVipCscCfg   = outCfg->cscCfg;

    GT_assert(VpsDrvCaptTrace, (NULL != captVipParams));

    /* Updating Source info */
    captVipParams->inFmt.chNum  = 0;     /* TODO: Check this */
    captVipParams->inFmt.width  = inpCfg->srcWidth;
    captVipParams->inFmt.height = inpCfg->srcHeight;
    for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
    {
        captVipParams->inFmt.pitch[pl]       = 0;
        captVipParams->inFmt.fieldMerged[pl] = 0;
    }
    captVipParams->inFmt.dataFormat = inpCfg->srcColorSpace;
    /* captVipParams->inFmt.scanFormat is maintained by driver */
    captVipParams->inFmt.bpp      = 0;      /* Unused */
    captVipParams->inFmt.reserved = NULL;   /* Unused */

    /* Updating output stream info */
    for (strm = 0; strm < inpCfg->numStreams; strm++)
    {
        Vps_CaptVipOutInfo *outStrmInfo =
            &(captVipParams->outStreamInfo[strm]);
        outStrmInfo->outFmt.chNum  = 0;     /* TODO: Check this */
        outStrmInfo->outFmt.width  = inpCfg->tarWidth[strm];
        outStrmInfo->outFmt.height = inpCfg->tarHeight[strm];
        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            outStrmInfo->outFmt.pitch[pl] = inpCfg->pitch[strm][pl];
            /* outStrmInfo->outFmt.fieldMerged[pl] is maintained by
             * driver */
        }
        outStrmInfo->outFmt.dataFormat = inpCfg->dstColorSpace[strm];
        /* outStrmInfo->outFmt.scanFormat maintained by driver */
        outStrmInfo->outFmt.bpp      = 0;      /* Unused */
        outStrmInfo->outFmt.reserved = NULL;   /* Unused */

        /* outStrmInfo->bufFmt is maintained by driver */
        outStrmInfo->memType = inpCfg->memType[strm];

        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            outStrmInfo->maxOutWidth[pl]  = inpCfg->maxOutWidth[strm][pl];
            outStrmInfo->maxOutHeight[pl] = inpCfg->maxOutHeight[strm][pl];
        }
        outStrmInfo->scEnable = inpCfg->scActive[strm];

        for (pl = 0; pl < FVID2_MAX_PLANES; pl++)
        {
            outStrmInfo->subFrmPrms.subFrameEnable =
                inpCfg->subFrmPrms[pl].subFrameEnable;
            outStrmInfo->subFrmPrms.numLinesPerSubFrame =
                inpCfg->subFrmPrms[pl].numLinesPerSubFrame;
            /* outStrmInfo->subFrmPrms.subFrameCb is maintained by driver */
        }
    }

    /* Update Vps_CaptVipScParams */
    if (NULL != captVipScParams)
    {
        BspUtils_memcpy((void *) &(captVipScParams->inCropCfg),
                        (void *) &(inpCfg->inCropCfg),
                        sizeof (Fvid2_CropConfig));
        captVipScParams->scCfg.bypass           = inpCfg->scCfg.bypass;
        captVipScParams->scCfg.nonLinear        = inpCfg->scCfg.nonLinear;
        captVipScParams->scCfg.stripSize        = inpCfg->scCfg.stripSize;
        captVipScParams->scCfg.enableEdgeDetect =
            inpCfg->scCfg.enableEdgeDetect;
        captVipScParams->scCfg.enablePeaking =
            inpCfg->scCfg.enablePeaking;
        if ((NULL != captVipScParams->scCfg.advCfg) &&
            (NULL != inpCfg->scCfg.advCfg))
        {
            BspUtils_memcpy((void *) captVipScParams->scCfg.advCfg,
                            (void *) inpCfg->scCfg.advCfg,
                            sizeof (Vps_ScAdvConfig));
        }
        /* captVipScParams->scCoeffCfg is maintained by driver */
        /* captVipScParams->enableCoeffLoad is maintained by driver */
    }

    /* Update Vps_VipPortConfig */
    if (NULL != captVipPortCfg)
    {
        BspUtils_memcpy((void *) captVipPortCfg,
                        (void *) &inpCfg->portCfg,
                        sizeof (Vps_VipPortConfig));
    }

    /* Update Vps_CscConfig */
    if (NULL != captVipCscCfg)
    {
        captVipCscCfg->bypass = inpCfg->cscCfg.bypass;
        captVipCscCfg->mode   = inpCfg->cscCfg.mode;
        if ((NULL != captVipCscCfg->coeff) &&
            (NULL != inpCfg->cscCfg.coeff))
        {
            BspUtils_memcpy((void *) captVipCscCfg->coeff,
                            (void *) inpCfg->cscCfg.coeff,
                            sizeof (Vps_CscCoeff));
        }
    }

    return retVal;
}

Int32 vpsDrvCaptGetVipCoreParams(VpsDrv_CaptInstObj *instObj,
                                 Vps_CaptVipParams  *vipPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 streamCnt;
    VpsCore_VipParams     vipCorePrms;
    VpsDrv_CaptChObj     *chObj;
    VpsDrv_CaptBufManObj *bmObj;
    Vps_CaptVipOutInfo   *outStreamInfo;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->getParams));
    GT_assert(VpsDrvCaptTrace, (NULL != vipPrms));

    if (VPSCORE_CAPT_VIP != instObj->coreProperty.name)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "Can't set VIP parameter to this core\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        vipCorePrms.scCfg.advCfg = vipPrms->scPrms->scCfg.advCfg;
        vipCorePrms.cscCfg.coeff = vipPrms->cscCfg->coeff;
        /* Get Configuration from core */
        retVal = instObj->coreOps->getParams(instObj->coreHandle,
                                             &vipCorePrms);
        vpsDrvVipParamsToCaptVipParams(&vipCorePrms, vipPrms);

        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Get VIP parameter failed\r\n");
        }

        /* Fill the info maintained by the driver */
        /* TODO: Check that if this still works if no setConfig is done */
        for (streamCnt = 0U;
             streamCnt < instObj->createPrms.numStream;
             streamCnt++)
        {
            /* Get channel object */
            chObj         = &instObj->chObj[streamCnt][0U];
            bmObj         = &chObj->bmObj;
            outStreamInfo = &vipPrms->outStreamInfo[streamCnt];

            vipPrms->inFmt.scanFormat = bmObj->isProgressive;

            outStreamInfo->outFmt.fieldMerged[FVID2_GENERIC_ADDR_IDX] =
                bmObj->fieldMerged;
            /* TODO: Need to fix this for FIELD merged cases */
            outStreamInfo->outFmt.scanFormat = FVID2_SF_PROGRESSIVE;
            outStreamInfo->bufFmt = bmObj->bufFmt;
            outStreamInfo->subFrmPrms.subFrameCb = chObj->subFrmPrms.subFrameCb;
        }
        if (NULL != vipPrms->scPrms->scCoeffCfg)
        {
            /* TODO: Check this - possible reinitializing a variable */
            instObj->vipPrms.scPrms->scCoeffCfg = &instObj->scCoeffCfg;
            BspUtils_memcpy(
                vipPrms->scPrms->scCoeffCfg,
                instObj->vipPrms.scPrms->scCoeffCfg,
                sizeof (instObj->scCoeffCfg));
        }
        vipPrms->scPrms->enableCoeffLoad = (UInt32) FALSE;
        /* Not supported currently */
    }

    return (retVal);
}

Int32 vpsDrvCaptSetVipMaxSizePrmsIoctl(
    const VpsDrv_CaptCommonObj *drvObj,
    Vps_VpdmaMaxSizeParams     *vipMaxFrmPrms)
{
    Int32  retVal = FVID2_SOK;

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    retVal = FVID2_EUNSUPPORTED_CMD;
#else
    UInt32 instCnt, vipInstId;

    GT_assert(VpsDrvCaptTrace, (NULL != drvObj));
    GT_assert(VpsDrvCaptTrace, (NULL != drvObj->instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != vipMaxFrmPrms));

    /* Based on the vipInstId which is derived from the drvInstId
     * the driver instance handle is obtained from which the VIP
     * core instance handle.
     * This VIP core instance handle shall give the VPDMA handle. */
    for (instCnt = 0U; instCnt < drvObj->numInst; instCnt++)
    {
        /* Get the VIP ID from the driverInstId */
        vipInstId =
            Vps_captGetVipId(drvObj->instObj[instCnt].drvInstId);
        if (vipInstId == vipMaxFrmPrms->instId)
        {
            /* Found the VIP VpsCore_Inst Handle. */
            GT_assert(VpsDrvCaptTrace,
                      (NULL != drvObj->instObj[instCnt].coreInstObj));
            break;
        }
    }

    retVal = drvObj->instObj[instCnt].coreOps->control(
        (VpsCore_Handle) VPSCORE_COMMON_HANDLE,
        VPSCORE_VIP_IOCTL_SET_MF_CFG,
        vipMaxFrmPrms,
        (Ptr) drvObj->instObj[instCnt].coreInstObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "Core control: Set Max Frame Size failed!!\r\n");
    }
#endif

    return (retVal);
}

static Int32 vpsDrvCaptOpenVipCore(VpsDrv_CaptInstObj *instObj)
{
    Int32                    retVal = FVID2_SOK, tempRetVal;
    UInt32                   event, chId;
    VpsCore_OpenPrms         openPrms;
    VpsCore_VipOpenParams    vipOpenPrms;
    VpsCore_VipOpenRetParams vipRetPrms;
    UInt32                   numEvents = 1U;
    VpsDrv_CaptChObj        *chObj;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->open));

    /* Init parameters */
    instObj->coreHandle = NULL;
    BspUtils_memset(&instObj->vemHandle[0U], 0, sizeof (instObj->vemHandle));
    instObj->intrHandle          = NULL;
    openPrms.drvData             = instObj;
    openPrms.reqFrmCb            = &vpsDrvCaptCoreReqFrameCb;
    openPrms.frmDoneCb           = &vpsDrvCaptCoreFrameDoneCb;
    vipOpenPrms.src              = vpsDrvCaptGetVipCoreSrcId(instObj);
    vipOpenPrms.numChannels      = instObj->createPrms.numCh;
    vipOpenPrms.muxModeStartChId = instObj->createPrms.muxModeStartChId;

    /* Open the core instance */
    instObj->coreHandle = instObj->coreOps->open(
        instObj->coreInstObj,
        &openPrms,
        &vipOpenPrms,
        &vipRetPrms);
    if (NULL == instObj->coreHandle)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "VIP core open failed!!\r\n");
        retVal = FVID2_EFAIL;
    }
    else
    {
        for (chId = 0; chId < instObj->createPrms.numCh; chId++)
        {
            /* Get channel object - 0th stream is sufficient */
            chObj = &instObj->chObj[0U][chId];

            if (VPSCORE_VIP_INTRTYPE_VEM == vipRetPrms.intrType[chId])
            {
                event = vipRetPrms.vemEvent[chId];
                instObj->vemHandle[chId] = Vem_register(
                    vipRetPrms.vemInstId[chId],
                    vipRetPrms.vemEventGroup[chId],
                    &event,
                    numEvents,
                    VEM_PRIORITY1,
                    vpsDrvCaptVemIsr,
                    chObj);
                if (NULL == instObj->vemHandle[chId])
                {
                    GT_0trace(VpsDrvCaptTrace, GT_ERR,
                              "VEM registeration failed!!\r\n");
                    retVal = FVID2_EFAIL;
                    break;
                }
            }
            else
            {
                GT_assert(VpsDrvCaptTrace, FALSE);
            }
        }
    }

    /* Close core if error occurs */
    if ((FVID2_SOK != retVal) && (NULL != instObj->coreHandle))
    {
        tempRetVal = vpsDrvCaptCloseCore(instObj);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

static UInt32 vpsDrvCaptGetVipCoreSrcId(const VpsDrv_CaptInstObj *instObj)
{
    UInt32 srcId, sliceId, portId;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    sliceId = Vps_captGetVipSliceId(instObj->drvInstId);
    portId  = Vps_captGetPortId(instObj->drvInstId);

    if ((VPS_VIP_S0 == sliceId) && (VPS_VIP_PORTA == portId))
    {
        switch (instObj->createPrms.videoIfWidth)
        {
            case FVID2_VIFW_8BIT:
                srcId = S0_PORTA_08;
                break;

            case FVID2_VIFW_16BIT:
                srcId = S0_PORTA_16;
                break;

            case FVID2_VIFW_24BIT:
                srcId = S0_PORTA_24;
                break;

            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR,
                          "Invalid interface mode!! Defaulting to 16-bit!!\r\n");
                srcId = S0_PORTA_16;
                break;
        }
    }
    else if ((VPS_VIP_S0 == sliceId) && (VPS_VIP_PORTB == portId))
    {
        switch (instObj->createPrms.videoIfWidth)
        {
            case FVID2_VIFW_8BIT:
                srcId = S0_PORTB_08;
                break;

            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR,
                          "Invalid interface mode!! Defaulting to 8-bit!!\r\n");
                srcId = S0_PORTB_08;
                break;
        }
    }
    else if ((VPS_VIP_S1 == sliceId) && (VPS_VIP_PORTA == portId))
    {
        switch (instObj->createPrms.videoIfWidth)
        {
            case FVID2_VIFW_8BIT:
                srcId = S1_PORTA_08;
                break;

            case FVID2_VIFW_16BIT:
                srcId = S1_PORTA_16;
                break;

            case FVID2_VIFW_24BIT:
                srcId = S1_PORTA_24;
                break;

            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR,
                          "Invalid interface mode!! Defaulting to 16-bit!!\r\n");
                srcId = S1_PORTA_16;
                break;
        }
    }
    else if ((VPS_VIP_S1 == sliceId) && (VPS_VIP_PORTB == portId))
    {
        switch (instObj->createPrms.videoIfWidth)
        {
            case FVID2_VIFW_8BIT:
                srcId = S1_PORTB_08;
                break;

            default:
                GT_0trace(VpsDrvCaptTrace, GT_ERR,
                          "Invalid interface mode!! Defaulting to 8-bit!!\r\n");
                srcId = S1_PORTB_08;
                break;
        }
    }
    else
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "Invalid driver instance ID!! This can't happen!!\r\n");
        srcId = S0_PORTA_16;
    }

    return (srcId);
}

/**
 *  vpsDrvCaptCopyVipParams
 *  Copy the user provided VIP parameters.
 */
static void vpsDrvCaptCopyVipParams(VpsDrv_CaptInstObj      *instObj,
                                    const Vps_CaptVipParams *vipPrms)
{
    UInt32 streamId, chId;
    VpsDrv_CaptChObj         *chObj;
    VpsDrv_CaptBufManObj     *bmObj;
    const Vps_CaptVipOutInfo *outStreamInfo;

    /* NULL pointer check */
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != vipPrms));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_STREAM_ID_MAX));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numCh <= VPS_CAPT_CH_PER_PORT_MAX));

    BspUtils_memcpy(
        &instObj->vipPrms,
        vipPrms,
        sizeof (instObj->vipPrms));

    /* Use local memory for pointer parameters */
    if (NULL != vipPrms->scPrms)
    {
        instObj->vipPrms.scPrms = &instObj->scPrms;
        BspUtils_memcpy(
            instObj->vipPrms.scPrms,
            vipPrms->scPrms,
            sizeof (instObj->scPrms));
        if (NULL != vipPrms->scPrms->scCoeffCfg)
        {
            instObj->vipPrms.scPrms->scCoeffCfg = &instObj->scCoeffCfg;
            BspUtils_memcpy(
                instObj->vipPrms.scPrms->scCoeffCfg,
                vipPrms->scPrms->scCoeffCfg,
                sizeof (instObj->scCoeffCfg));
        }
    }
    if (NULL != vipPrms->vipPortCfg)
    {
        instObj->vipPrms.vipPortCfg = &instObj->vipPortCfg;
        BspUtils_memcpy(
            instObj->vipPrms.vipPortCfg,
            vipPrms->vipPortCfg,
            sizeof (instObj->vipPortCfg));
    }
    if (NULL != vipPrms->cscCfg)
    {
        instObj->vipPrms.cscCfg = &instObj->cscCfg;
        BspUtils_memcpy(
            instObj->vipPrms.cscCfg,
            vipPrms->cscCfg,
            sizeof (instObj->cscCfg));
    }

    /* For every stream and every channel */
    for (streamId = 0U; streamId < instObj->createPrms.numStream; streamId++)
    {
        outStreamInfo = &vipPrms->outStreamInfo[streamId];
        for (chId = 0; chId < instObj->createPrms.numCh; chId++)
        {
            /* Get channel object */
            chObj = &instObj->chObj[streamId][chId];
            bmObj = &chObj->bmObj;

            chObj->subFrmPrms.subFrameEnable =
                outStreamInfo->subFrmPrms.subFrameEnable;
            chObj->subFrmPrms.numLinesPerSubFrame =
                outStreamInfo->subFrmPrms.numLinesPerSubFrame;
            chObj->subFrmPrms.subFrameCb =
                outStreamInfo->subFrmPrms.subFrameCb;
            bmObj->isProgressive = vipPrms->inFmt.scanFormat;
            bmObj->bufFmt        =
                (Fvid2_BufferFormat) outStreamInfo->bufFmt;
            bmObj->fieldMerged =
                outStreamInfo->outFmt.fieldMerged[FVID2_GENERIC_ADDR_IDX];
        }
    }

    return;
}

/**
 *  \brief Sets the VIP port sync parameters as per the user provided create
 *  params.
 */
static void vpsDrvCaptSetVipCoreSyncParams(UInt32             videoIfMode,
                                           UInt32             videoIfWidth,
                                           UInt32             numCh,
                                           Vps_VipPortConfig *portCfg)
{
    UInt32 syncType;
    UInt32 lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_AVID;
    UInt32 discreteBasicMode = (UInt32) TRUE;

    switch (videoIfMode)
    {
        case FVID2_VIFM_SCH_ES:
            syncType = VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV;
            break;

        case FVID2_VIFM_MCH_LINE_MUX_ES:
            syncType = VPS_VIP_SYNC_TYPE_EMB_LINE_YUV;
            break;

        case FVID2_VIFM_MCH_PIXEL_MUX_ES:
            syncType = VPS_VIP_SYNC_TYPE_EMB_4X_422_YUV;
            if (2U == numCh)
            {
                syncType = VPS_VIP_SYNC_TYPE_EMB_2X_422_YUV;
            }
            break;

        case FVID2_VIFM_SCH_DS_HSYNC_VBLK:
            syncType          = VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
            lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_HSYNC;
            discreteBasicMode = (UInt32) FALSE;
            break;

        case FVID2_VIFM_SCH_DS_HSYNC_VSYNC:
            syncType          = VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
            lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_HSYNC;
            discreteBasicMode = (UInt32) TRUE;
            break;

        case FVID2_VIFM_SCH_DS_AVID_VBLK:
            syncType          = VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
            lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_AVID;
            discreteBasicMode = (UInt32) FALSE;
            break;

        case FVID2_VIFM_SCH_DS_AVID_VSYNC:
            syncType          = VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
            lineCaptureStyle  = VPS_VIP_LINE_CAPTURE_STYLE_AVID;
            discreteBasicMode = (UInt32) TRUE;
            break;

        case FVID2_VIFM_MCH_LINE_MUX_SPLIT_LINE_ES:
            syncType = VPS_VIP_SYNC_TYPE_EMB_LINE_YUV;
            break;

        default:
            syncType = VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV;
            break;
    }

    portCfg->syncType                 = syncType;
    portCfg->intfCfg.intfWidth        = videoIfWidth;
    portCfg->disCfg.lineCaptureStyle  = lineCaptureStyle;
    portCfg->disCfg.discreteBasicMode = discreteBasicMode;

    return;
}

#endif  /* VPS_VIP_BUILD */

Int32 vpsDrvCaptStartCore(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->start));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreHandle));

    /* Start core */
    retVal = instObj->coreOps->start(instObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Core start failed!!\r\n");
    }

    return (retVal);
}

Int32 vpsDrvCaptStopCore(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->stop));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreHandle));

    /* Stop core */
    retVal = instObj->coreOps->stop(instObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "Core stop failed!!\r\n");
    }

    return (retVal);
}

#ifdef VPS_DSS_BUILD

static Int32 vpsDrvCaptOpenDssWbCore(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = FVID2_SOK, tempRetVal;
    VpsCore_OpenPrms        openPrms;
    VpsCore_DssWbOpenParams dssWbOpenPrms;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->open));

    /* Init parameters */
    instObj->coreHandle = NULL;
#ifdef VPS_VIP_BUILD
    BspUtils_memset(&instObj->vemHandle[0U], 0, sizeof (instObj->vemHandle));
#endif
    instObj->intrHandle     = NULL;
    openPrms.drvData        = instObj;
    openPrms.reqFrmCb       = &vpsDrvCaptCoreReqFrameCb;
    openPrms.frmDoneCb      = &vpsDrvCaptCoreFrameDoneCb;
    dssWbOpenPrms.src       = VPS_DSS_DISPC_PIPE_WB;
    dssWbOpenPrms.wbMode    = VPS_DSS_DISPC_WB_CAPT;
    /* Open the core instance */
    instObj->coreHandle = instObj->coreOps->open(
        instObj->coreInstObj,
        &openPrms,
        &dssWbOpenPrms,
        NULL);
    if (NULL == instObj->coreHandle)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "DSS WB core open failed!!\r\n");
        retVal = FVID2_EFAIL;
    }

    /* Close core if error occurs */
    if ((FVID2_SOK != retVal) && (NULL != instObj->coreHandle))
    {
        tempRetVal = instObj->coreOps->close(instObj->coreHandle);
        GT_assert(VpsDrvCaptTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}


/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_017)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-993)
 */
Int32 vpsDrvCaptSetDssWbCoreParams(VpsDrv_CaptInstObj        *instObj,
                                   const Vps_CaptDssWbParams *dssWbPrms)
{
    Int32 retVal = FVID2_SOK;
    VpsCore_DispDssWbParams dssWbCorePrms;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->setParams));
    GT_assert(VpsDrvCaptTrace, (NULL != dssWbPrms));
    GT_assert(VpsDrvCaptTrace,
              (instObj->createPrms.numStream <= VPS_CAPT_DSSWB_STREAM_ID_MAX));

    if (VPSCORE_DISP_DSSWB != instObj->coreProperty.name)
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR,
                  "Can't set DSSWB parameter to this core\r\n");
        retVal = FVID2_EFAIL;
    }

    if (retVal == FVID2_SOK)
    {
        /* Copy core parameters */
        /* Only one stream is supported as of now */
        BspUtils_memcpy(
            &dssWbCorePrms.outFmt,
            &dssWbPrms->outStreamInfo[0].outFmt,
            sizeof (Fvid2_Format));

        /* Here for WB pipeline, the cropping is done in the overlay itself
         * for region based write back input width is equal to cropwidth
         * itself.Same for cropHeight.*/
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        /* For tda2xx inCropCfg is not valid.
         * writeback inHeight and inWidth is derived from inFmt.
         * inFmt holds the overlay height and width */
        dssWbCorePrms.inHeight = dssWbPrms->inFmt.height;
        dssWbCorePrms.inWidth  = dssWbPrms->inFmt.width;
        dssWbCorePrms.inPosX   = 0;
        dssWbCorePrms.inPosY   = 0;
#else
        dssWbCorePrms.inHeight = dssWbPrms->inCropCfg.cropHeight;
        dssWbCorePrms.inWidth  = dssWbPrms->inCropCfg.cropWidth;
        dssWbCorePrms.inPosX   = dssWbPrms->inCropCfg.cropStartX;
        dssWbCorePrms.inPosY   = dssWbPrms->inCropCfg.cropStartY;
#endif
        dssWbCorePrms.indataFormat = dssWbPrms->inFmt.dataFormat;
        dssWbCorePrms.sourceHeight = dssWbPrms->inFmt.height;
        dssWbCorePrms.sourceWidth  = dssWbPrms->inFmt.width;

        dssWbCorePrms.memType =
            dssWbPrms->outStreamInfo[0].memType;
        dssWbCorePrms.wbCfg.pipeCfg.scEnable =
            dssWbPrms->outStreamInfo[0].scEnable;
        dssWbCorePrms.wbCfg.pipeCfg.cropEnable =
            dssWbPrms->outStreamInfo[0].cropEnable;

        /* TODO - Expose it via interface */
        dssWbCorePrms.wbCfg.pipeCfg.cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;

        /* TODO - Expose it via interface */
        dssWbCorePrms.wbCfg.advDmaCfg = NULL;

        dssWbCorePrms.inNode = dssWbPrms->inNode;
        dssWbCorePrms.wbMode = dssWbPrms->wbMode;

        /* Configure the core */
        retVal = instObj->coreOps->setParams(instObj->coreHandle,
                                             &dssWbCorePrms,
                                             NULL);

        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR, "Set DSSWB parameter failed\r\n");
        }
    }

    return (retVal);
}

Int32 vpsDrvCaptSetDssWbCscCoeff(VpsDrv_CaptInstObj *instObj,
                                 void               *cscCoeff)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));
    GT_assert(VpsDrvCaptTrace, (NULL != cscCoeff));
    retVal = instObj->coreOps->control(
        instObj->coreHandle,
        VCORE_DSS_WB_SET_CSC_COEFF,
        cscCoeff,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Set CSC Params failed!!\r\n");
    }

    return (retVal);
}

#endif /* VPS_DSS_BUILD */

#ifdef VPS_CAL_BUILD
static Int32 vpsDrvCaptOpenIssCore(VpsDrv_CaptInstObj *instObj)
{
    Int32                       retVal = FVID2_SOK;
    UInt32                      index;
    VpsCore_OpenPrms            openPrms;
    Vps_CaptIssOpenParams_t    *issSpecificOpenParms;
    vcoreissCaptOpenParams_t    issCaptCoreOpenPrms;
    vcoreissCaptOpenRetParams_t issCaptOpenRtnPrms;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->open));

    issSpecificOpenParms = (Vps_CaptIssOpenParams_t *)
                           instObj->createPrms.pAdditionalArgs;
    GT_assert(VpsDrvCaptTrace, (NULL != issSpecificOpenParms));

    issCaptCoreOpenPrms.arg          = NULL;
    issCaptCoreOpenPrms.numStreams   = instObj->createPrms.numStream;

    if (FVID2_VIFM_SCH_CSI2 == instObj->createPrms.videoIfMode)
    {
        issCaptCoreOpenPrms.captIf = VPSCORE_ISS_CAPT_IF_CSI2;
    }
    if (FVID2_VIFM_SCH_CPI == instObj->createPrms.videoIfMode)
    {
        issCaptCoreOpenPrms.captIf = VPSCORE_ISS_CAPT_IF_CPI;
    }

    for (index = 0; index < issCaptCoreOpenPrms.numStreams; index++)
    {
        issCaptCoreOpenPrms.subModules[index] =
            issSpecificOpenParms->subModules[index];
    }
    for (index = 0; index < CSL_CAL_CMPLXIO_CNT; index++)
    {
        issCaptCoreOpenPrms.csi2PhyClock[index] =
                                    issSpecificOpenParms->csi2PhyClock[index];
        if (TRUE == issSpecificOpenParms->isCmplxIoCfgValid[index])
        {
            BspUtils_memcpy(
                &issCaptCoreOpenPrms.cmplxIoCfg[index],
                &issSpecificOpenParms->cmplxIoCfg[index],
                sizeof (vpsissCalCmplxIoCfg_t));
        }
        issCaptCoreOpenPrms.isCmplxIoCfgValid[index] =
                                issSpecificOpenParms->isCmplxIoCfgValid[index];
    }

    issCaptCoreOpenPrms.otfOpenPrms = issSpecificOpenParms->otfOpenPrms;

    instObj->coreHandle = NULL;
    instObj->intrHandle = NULL;

    BspUtils_memset(&instObj->frmEvtNotifyPrms, 0,
                    sizeof (vpsissCalFrameEventNotifyCfg_t));

#ifdef VPS_VIP_BUILD
    BspUtils_memset(&instObj->vemHandle[0U], 0, sizeof (instObj->vemHandle));
#endif

    openPrms.drvData   = instObj;
    openPrms.reqFrmCb  = &vpsDrvCaptCoreReqFrameCb;
    openPrms.frmDoneCb = &vpsDrvCaptCoreFrameDoneCb;

    /* Open the core instance */
    instObj->coreHandle = instObj->coreOps->open(
        instObj->coreInstObj,
        &openPrms,
        &issCaptCoreOpenPrms,
        &issCaptOpenRtnPrms);
    if (NULL != instObj->coreHandle)
    {
        for (index = 0; index < issCaptCoreOpenPrms.numStreams; index++)
        {
            instObj->chObj[index][0U].isStreamByPassed =
                issCaptOpenRtnPrms.isStreamOpt[index];
        }
    }
    else
    {
        GT_0trace(VpsDrvCaptTrace, GT_ERR, "ISS Capture core open failed!!\r\n");
        retVal = FVID2_EFAIL;
    }
    return (retVal);
}

Int32 vpsDrvCaptSetIssCoreParams(VpsDrv_CaptInstObj   *instObj,
                                 const vpsissCalCfg_t *pPrms)
{
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));
    return (instObj->coreOps->control(instObj->coreHandle,
                                      VCORE_ISS_CAPT_CAL_SET_PARAMS,
                                      (void *) pPrms, NULL));
}

Int32 vpsDrvCaptSetIssErrorParams(VpsDrv_CaptInstObj        *instObj,
                                  const vpsissCalErrorCfg_t *pPrms)
{
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));
    return (instObj->coreOps->control(instObj->coreHandle,
                                      VCORE_ISS_CAPT_CAL_SET_ERR_PRMS,
                                      (void *) pPrms, NULL));
}

Int32 vpsDrvCaptIssSubFrmCbFxn (void *drvData,
                                const VpsCore_Frame *coreFrm,
                                Fvid2_SubFrameInfo  *subFrmInfo)
{
    UInt32 cookie;
    UInt64 curTimeStamp;
    VpsDrv_CaptInstObj *instObj;
    VpsDrv_CaptQueObj  *qObj;

    instObj = (VpsDrv_CaptInstObj *) drvData;
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));

    /* Valid frame event notification */
    if (0U != instObj->frmEvtNotifyPrms.numStream)
    {
        GT_assert(VpsDrvCaptTrace, (NULL != coreFrm));
        GT_assert(VpsDrvCaptTrace, (NULL != subFrmInfo));
        GT_assert(VpsDrvCaptTrace, (coreFrm->streamId < VPS_CAPT_STREAM_ID_MAX));
        GT_assert(VpsDrvCaptTrace, (coreFrm->chId < instObj->createPrms.numCh));


        cookie = BspOsal_disableInterrupt();

        GT_assert(VpsDrvCaptTrace, (NULL != instObj->getTimeStamp));
        curTimeStamp = instObj->getTimeStamp(NULL);

        /* Get reference of the queue head */
        qObj = (VpsDrv_CaptQueObj *) coreFrm->drvData;
        GT_assert(VpsDrvCaptTrace, (NULL != qObj));
        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm));
        GT_assert(VpsDrvCaptTrace, (NULL != qObj->frm->subFrameInfo));

        /* Convert to msec for 32-bit timestamp */
        qObj->frm->timeStamp   = (UInt32) (curTimeStamp / 1000U);
        qObj->frm->timeStamp64 = curTimeStamp;

        qObj->frm->subFrameInfo->subFrameNum = subFrmInfo->subFrameNum;
        qObj->frm->subFrameInfo->numOutLines = subFrmInfo->numOutLines;
        qObj->frm->subFrameInfo->numInLines  = 0U;

        /* Let Apps know */
        instObj->frmEvtNotifyPrms.appCb((Fdrv_Handle) instObj, qObj->frm);

        BspOsal_restoreInterrupt(cookie);
    }
    return (FVID2_SOK);
}

Int32 vpsDrvCaptSetIssSubFrmParams(VpsDrv_CaptInstObj        *instObj,
                                  const vpsissCalFrameEventNotifyCfg_t *pPrms)
{
    Int32 rtnVal;

    UInt32 cookie;
    UInt32 streamId;
    static vcoreissCaptSubFrameCfg_t corePrms;

    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));

    cookie = BspOsal_disableInterrupt();
    instObj->frmEvtNotifyPrms.numStream = 0U;

    corePrms.numStream = pPrms->numStream;
    for (streamId = 0U; streamId < pPrms->numStream; streamId++)
    {
        corePrms.streamId[streamId] = pPrms->streamId[streamId];
        corePrms.notifyAfterFirstXLines[streamId] =
                                        pPrms->notifyAfterFirstXLines[streamId];
        corePrms.notifyAfterEndOfFrame[streamId]  =
                                        pPrms->notifyAfterEndOfFrame[streamId];
        corePrms.streamId[streamId] = pPrms->streamId[streamId];
    }
    corePrms.appCb = (VpsCore_SubFrameCbFxn) &vpsDrvCaptIssSubFrmCbFxn;
    corePrms.pAppCbArgs = (Ptr)instObj;
    corePrms.pAdditionalArgs = (Ptr)NULL;

    rtnVal = instObj->coreOps->control(instObj->coreHandle,
                                      VCORE_ISS_CAPT_CAL_SET_SUB_FRM_PRMS,
                                      (void *) &corePrms, NULL);
    if (FVID2_SOK == rtnVal)
    {
        BspUtils_memcpy(&instObj->frmEvtNotifyPrms,
                        pPrms,
                        sizeof (vpsissCalFrameEventNotifyCfg_t));
    }
    BspOsal_restoreInterrupt(cookie);
    return (rtnVal);
}

#ifdef VPS_ISS_BUILD
Int32 vpsDrvCaptSetIssStreamMap(VpsDrv_CaptInstObj               *instObj,
                                const vpsissCalOtfStreamMapCfg_t *pPrms)
{
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));
    return (instObj->coreOps->control(instObj->coreHandle,
                                      VCORE_ISS_CAPT_CAL_SET_STREAMS_MAP,
                                      (void *) pPrms, NULL));
}

Int32 vpsDrvCaptOtfControl(VpsDrv_CaptInstObj *instObj,
                           UInt32 cmd, Ptr cmdArgs)
{
    GT_assert(VpsDrvCaptTrace, (NULL != instObj));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvCaptTrace, (NULL != instObj->coreOps->control));
    return (instObj->coreOps->control(instObj->coreHandle,
                                      cmd, (void *) cmdArgs, NULL));
}

#endif /* VPS_ISS_BUILD */
#endif /* VPS_CAL_BUILD */

