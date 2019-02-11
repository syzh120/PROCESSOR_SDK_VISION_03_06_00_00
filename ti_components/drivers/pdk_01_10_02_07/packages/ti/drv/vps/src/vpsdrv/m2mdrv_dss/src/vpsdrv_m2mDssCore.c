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
 *  \file vpsdrv_m2mDssCore.c
 *
 *  \brief DSS core driver.
 *  This file implements DSS core APIs for the FVID2 APIs.
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

static Int32 vpsMdrvDssCheckPrms(const VpsMDrv_DssHandleObj *hObj,
                                 const Vps_M2mDssParams *dssPrms);
static void vpsMdrvDssCopyPrms(VpsMDrv_DssHandleObj *hObj,
                               const Vps_M2mDssParams *dssPrms);
static Int32 vpsMdrvDssSetPrmsInCore(VpsMDrv_DssHandleObj *hObj);
static Int32 vpsMdrvDssSetPrmsWbCore(VpsMDrv_DssHandleObj *hObj);
static Int32 vpsMdrvDssSetPrmsOvly(VpsMDrv_DssHandleObj *hObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                               Functions                                    */
/* ========================================================================== */

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1772) DOX_REQ_TAG(PDK-1773) DOX_REQ_TAG(PDK-1774)
 *          DOX_REQ_TAG(PDK-1775) DOX_REQ_TAG(PDK-1776)
 */
/**
 *  vpsMdrvDssOpenCores
 *  Opens all the cores required for this instance.
 */
Int32 vpsMdrvDssOpenCores(VpsMDrv_DssInstObj *instObj,
                          VpsMDrv_DssHandleObj *hObj)
{
    Int32                       retVal = FVID2_SOK, tempRetVal;
    UInt32                      pipeCnt;
    VpsCore_OpenPrms            coreOpenPrms;
    VpsCore_DssOpenParams       dssOpenPrms;
    VpsCore_DssOpenRetParams    dssRetPrms;
    VpsCore_DssWbOpenParams     wbOpenPrms;

    /* NULL pointer check */
    GT_assert(VpsMDrvDssTrace, (NULL != instObj));
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps));

    /* Reset the handles first */
    instObj->outCoreHandle = NULL;
    for (pipeCnt = 0U; pipeCnt < VPS_DSS_DISPC_PIPE_MAX; pipeCnt++)
    {
        instObj->inCoreHandle[pipeCnt] = NULL;
    }

    /* Initialize core open parameters */
    BspUtils_memset(&coreOpenPrms, 0x0, sizeof (coreOpenPrms));

    /* Open all input cores */
    for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
    {
        /* NULL pointer check */
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->open));

        /* Init drv data for the core */
        hObj->drvData[pipeCnt].instObj = instObj;
        hObj->drvData[pipeCnt].pipeIdx = pipeCnt;

        /* Open core */
        coreOpenPrms.drvData         = &hObj->drvData[pipeCnt];
        coreOpenPrms.reqFrmCb        = &vpsMdrvDssInCoreReqFrameCb;
        /* Not needed as we use WB callback for completion event */
        coreOpenPrms.frmDoneCb       = NULL;
        coreOpenPrms.frmDoneNotifyCb = NULL;
        dssOpenPrms.src       = hObj->createPrms.inPipeLines[pipeCnt];
        dssOpenPrms.isM2mMode = TRUE;
        instObj->inCoreHandle[pipeCnt] = instObj->inCoreOps->open(
            instObj->inCoreInstObj,
            &coreOpenPrms,
            &dssOpenPrms,
            &dssRetPrms);
        if (NULL == instObj->inCoreHandle[pipeCnt])
        {
            GT_1trace(VpsMDrvDssTrace, GT_ERR,
                      "Could not open input core %d!\r\n", pipeCnt);
            retVal = FVID2_EALLOC;
            break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Open output cores */
        coreOpenPrms.drvData         = instObj;
        coreOpenPrms.reqFrmCb        = &vpsMdrvDssOutCoreReqFrameCb;
        coreOpenPrms.frmDoneCb       = &vpsMdrvDssFrmDoneCb;
        coreOpenPrms.frmDoneNotifyCb = NULL;
        wbOpenPrms.src               = VPS_DSS_DISPC_PIPE_WB;
        wbOpenPrms.wbMode            = VPS_DSS_DISPC_WB_M2M;
        instObj->outCoreHandle = instObj->outCoreOps->open(
            instObj->outCoreInstObj,
            &coreOpenPrms,
            &wbOpenPrms,
            NULL);
        if (NULL == instObj->outCoreHandle)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR,
                      "Could not open output core!!\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    /* Close handles if error occurs */
    if (FVID2_SOK != retVal)
    {
        tempRetVal = vpsMdrvDssCloseCores(instObj);
        GT_assert(VpsMDrvDssTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

/**
 *  vpsMdrvDssCloseCores
 *  Closes all the cores opened for this instance.
 */
Int32 vpsMdrvDssCloseCores(VpsMDrv_DssInstObj *instObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 pipeCnt;

    /* NULL pointer check */
    GT_assert(VpsMDrvDssTrace, (NULL != instObj));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps));

    for (pipeCnt = 0U; pipeCnt < VPS_DSS_DISPC_PIPE_MAX; pipeCnt++)
    {
        if (NULL != instObj->inCoreHandle[pipeCnt])
        {
            GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->close));
            retVal = instObj->inCoreOps->close(instObj->inCoreHandle[pipeCnt]);
            GT_assert(VpsMDrvDssTrace, (FVID2_SOK == retVal));
            instObj->inCoreHandle[pipeCnt] = NULL;
        }
    }

    if (NULL != instObj->outCoreHandle)
    {
        GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps->close));
        retVal = instObj->outCoreOps->close(instObj->outCoreHandle);
        GT_assert(VpsMDrvDssTrace, (FVID2_SOK == retVal));
        instObj->outCoreHandle = NULL;
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1770)
 */
Int32 vpsMdrvDssSetPrmsIoctl(VpsMDrv_DssHandleObj *hObj, Ptr cmdArgs)
{
    Int32               retVal = FVID2_SOK;
    Vps_M2mDssParams   *dssPrms;

    /* Check for NULL pointers */
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Don't allow to set params when requests are pending with driver */
        if (0U != hObj->numPendReq)
        {
            GT_1trace(
                VpsMDrvDssTrace, GT_ERR,
                "Can't set params when %d requests are pending!!\r\n",
                hObj->numPendReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if (FVID2_SOK == retVal)
    {
        dssPrms = (Vps_M2mDssParams *) cmdArgs;
        retVal = vpsMdrvDssCheckPrms(hObj, dssPrms);
    }

    if (FVID2_SOK == retVal)
    {
        /* Deep copy */
        dssPrms = (Vps_M2mDssParams *) cmdArgs;
        vpsMdrvDssCopyPrms(hObj, dssPrms);

        /* Setup the core params */
        retVal  = vpsMdrvDssSetPrmsInCore(hObj);
        retVal += vpsMdrvDssSetPrmsWbCore(hObj);
        retVal += vpsMdrvDssSetPrmsOvly(hObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Core param setup failed\n");
        }
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1771)
 */
Int32 vpsMdrvDssSetCscCoeffIoctl(const VpsMDrv_DssHandleObj *hObj, Ptr cmdArgs)
{
    Int32                       retVal = FVID2_SOK;
    VpsMDrv_DssInstObj         *instObj;
    VpsCore_Handle              coreHandle;
    Vps_M2mDssCscCoeffParams   *coeffPrms;

    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->control));

    if (NULL == cmdArgs)
    {
        retVal = FVID2_EFAIL;
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "Null pointer argument!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        coeffPrms = (Vps_M2mDssCscCoeffParams *) cmdArgs;
        /* Get core handle for the in pipeline */
        coreHandle = vpsMdrvDssGetInCoreHandle(hObj, coeffPrms->inPipeId);
        if (NULL == coreHandle)
        {
            retVal = FVID2_EFAIL;
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Invalid input pipeline!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = instObj->inCoreOps->control(
            instObj->inCoreHandle,
            VCORE_DSS_SET_CSC_COEFF,
            &coeffPrms->cscCoeff,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Set CSC Params failed!!\r\n");
        }
    }

    return (retVal);
}

static Int32 vpsMdrvDssCheckPrms(const VpsMDrv_DssHandleObj *hObj,
                                 const Vps_M2mDssParams *dssPrms)
{
    UInt32  pipeCnt;
    Int32   retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    GT_assert(VpsMDrvDssTrace, (NULL != dssPrms));

    if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
    {
        /* Input pipeline target size should be less than overlay size */
        for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
        {
            if ((dssPrms->inPipePrms[pipeCnt].posX +
                    dssPrms->inPipePrms[pipeCnt].tarWidth) >
                        dssPrms->ovlyWidth)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Input pipeline width+posX greater than overlay\r\n");
            }
            if ((dssPrms->inPipePrms[pipeCnt].posY +
                    dssPrms->inPipePrms[pipeCnt].tarHeight) >
                        dssPrms->ovlyHeight)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Input pipeline height+posY greater than overlay\r\n");
            }
        }
    }

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    if (TRUE == dssPrms->outPipePrms.cropEnable)
    {
        retVal = FVID2_EINVALID_PARAMS;
        GT_0trace(
            VpsMDrvDssTrace, GT_ERR,
            "WB cropping not supported for TDA2xx/TDA2Ex platforms\r\n");
    }
#endif

    if (TRUE == dssPrms->outPipePrms.cropEnable)
    {
        /* Check crop size is less than input size */
        if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
        {
            if ((dssPrms->outPipePrms.cropCfg.cropStartX +
                    dssPrms->outPipePrms.cropCfg.cropWidth) >
                        dssPrms->ovlyWidth)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Writeback crop width+startX greater than overlay\r\n");
            }
            if ((dssPrms->outPipePrms.cropCfg.cropStartY +
                    dssPrms->outPipePrms.cropCfg.cropHeight) >
                        dssPrms->ovlyHeight)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Writeback crop height+startY greater than overlay\r\n");
            }
        }
        else
        {
            if ((dssPrms->outPipePrms.cropCfg.cropStartX +
                    dssPrms->outPipePrms.cropCfg.cropWidth) >
                        dssPrms->inPipePrms[0U].tarWidth)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Writeback crop width+startX greater than input pipe\r\n");
            }
            if ((dssPrms->outPipePrms.cropCfg.cropStartY +
                    dssPrms->outPipePrms.cropCfg.cropHeight) >
                        dssPrms->inPipePrms[0U].tarHeight)
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(
                    VpsMDrvDssTrace, GT_ERR,
                    "Writeback crop height+startY greater than input pipe\r\n");
            }
        }
    }
    return (retVal);
}

static void vpsMdrvDssCopyPrms(VpsMDrv_DssHandleObj *hObj,
                               const Vps_M2mDssParams *dssPrms)
{
    UInt32  pipeCnt;

    /* Check for NULL pointers */
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    GT_assert(VpsMDrvDssTrace, (NULL != dssPrms));

    BspUtils_memcpy(&hObj->dssPrms, dssPrms, sizeof(Vps_M2mDssParams));

    /* Deep copy - Replace user pointer with local pointer */
    for (pipeCnt = 0U; pipeCnt < VPS_DSS_DISPC_PIPE_MAX; pipeCnt++)
    {
        if (hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.advDmaCfg != NULL)
        {
            BspUtils_memcpy(
                &hObj->advDmaCfg[pipeCnt],
                hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.advDmaCfg,
                sizeof(Vps_DssDispcAdvDmaConfig));
            hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.advDmaCfg =
                &hObj->advDmaCfg[pipeCnt];
        }
        if (hObj->dssPrms.inPipePrms[pipeCnt].gfxCfg.advDmaCfg != NULL)
        {
            BspUtils_memcpy(
                &hObj->advDmaCfg[pipeCnt],
                hObj->dssPrms.inPipePrms[pipeCnt].gfxCfg.advDmaCfg,
                sizeof(Vps_DssDispcAdvDmaConfig));
            hObj->dssPrms.inPipePrms[pipeCnt].gfxCfg.advDmaCfg =
                &hObj->advDmaCfg[pipeCnt];
        }
        if (hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.vc1Cfg != NULL)
        {
            BspUtils_memcpy(
                &hObj->vc1Cfg[pipeCnt],
                hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.vc1Cfg,
                sizeof(Vps_DssDispcVidVC1Config));
            hObj->dssPrms.inPipePrms[pipeCnt].vidCfg.vc1Cfg =
                &hObj->vc1Cfg[pipeCnt];
        }
    }
    if (hObj->dssPrms.outPipePrms.advDmaCfg != NULL)
    {
        BspUtils_memcpy(
            &hObj->advDmaCfgWb,
            hObj->dssPrms.outPipePrms.advDmaCfg,
            sizeof(Vps_DssDispcAdvDmaConfig));
        hObj->dssPrms.outPipePrms.advDmaCfg = &hObj->advDmaCfgWb;
    }

    return;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_020)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1777) DOX_REQ_TAG(PDK-1778)
 */
static Int32 vpsMdrvDssSetPrmsInCore(VpsMDrv_DssHandleObj *hObj)
{
    Int32                   retVal = FVID2_SOK;
    UInt32                  pipeCnt;
    VpsCore_Handle          coreHandle;
    VpsMDrv_DssInstObj     *instObj;
    Vps_M2mDssInPipeParams *inPipePrms;
    VpsCore_DispDssParams   dssCorePrms;

    /* Check for NULL pointers */
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->inCoreOps->setParams));

    /* Input core setup */
    for (pipeCnt = 0U; pipeCnt < hObj->createPrms.numInPipeLines; pipeCnt++)
    {
        inPipePrms = &hObj->dssPrms.inPipePrms[pipeCnt];

        BspUtils_memcpy(
            &dssCorePrms.inFmt, &inPipePrms->inFmt, sizeof (Fvid2_Format));
        dssCorePrms.tarHeight   = inPipePrms->tarHeight;
        dssCorePrms.tarWidth    = inPipePrms->tarWidth;
        dssCorePrms.posX        = inPipePrms->posX;
        dssCorePrms.posY        = inPipePrms->posY;
        dssCorePrms.memType     = inPipePrms->memType;
        dssCorePrms.vidCfg      = &inPipePrms->vidCfg;
        dssCorePrms.gfxCfg      = &inPipePrms->gfxCfg;
        dssCorePrms.ovlyPipeCfg = &inPipePrms->ovlyPipeCfg;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        dssCorePrms.channelOut  = 0x0U;     /* LCD */
        if (VPS_DSS_DISPC_WB_IN_NODE_LCD1 == hObj->createPrms.wbInNode)
        {
            dssCorePrms.channelOut2 = 0x0U; /* LCD1 */
        }
        else if (VPS_DSS_DISPC_WB_IN_NODE_LCD2 == hObj->createPrms.wbInNode)
        {
            dssCorePrms.channelOut2 = 0x1U; /* LCD2 */
        }
        else if (VPS_DSS_DISPC_WB_IN_NODE_LCD3 == hObj->createPrms.wbInNode)
        {
            dssCorePrms.channelOut2 = 0x2U; /* LCD3 */
        }
        else
        {
            dssCorePrms.channelOut2 = 0x3U; /* default to WB */
        }
#endif
#if defined (SOC_TDA3XX)
        dssCorePrms.channelOut2 = 0x0U;     /* Not used */
        if (VPS_DSS_DISPC_WB_IN_NODE_LCD1 == hObj->createPrms.wbInNode)
        {
            dssCorePrms.channelOut  = 0x0U; /* OVR1/VP1 */
        }
        else if (VPS_DSS_DISPC_WB_IN_NODE_LCD2 == hObj->createPrms.wbInNode)
        {
            dssCorePrms.channelOut  = 0x1U; /* OVR2 */
        }
        else
        {
            dssCorePrms.channelOut  = 0x4U; /* default to WB */
        }
#endif

        /* Get core handle for the in pipeline */
        coreHandle = vpsMdrvDssGetInCoreHandle(hObj, inPipePrms->inPipeId);
        if (NULL == coreHandle)
        {
            retVal = FVID2_EFAIL;
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Invalid input pipeline!!\r\n");
            break;
        }

        /* Configure the core */
        retVal =
            instObj->inCoreOps->setParams(coreHandle, &dssCorePrms, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR,
                "Set DSS input core parameter failed\r\n");
        }
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_020)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1779) DOX_REQ_TAG(PDK-1780)
 */
static Int32 vpsMdrvDssSetPrmsWbCore(VpsMDrv_DssHandleObj *hObj)
{
    Int32                       retVal = FVID2_SOK;
    VpsCore_DispDssWbParams     dssWbCorePrms;
    VpsMDrv_DssInstObj         *instObj;
    Vps_M2mDssOutPipeParams    *outPipePrms;

    /* Check for NULL pointers */
    GT_assert(VpsMDrvDssTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps));
    GT_assert(VpsMDrvDssTrace, (NULL != instObj->outCoreOps->setParams));

    outPipePrms = &hObj->dssPrms.outPipePrms;
    BspUtils_memcpy(
        &dssWbCorePrms.outFmt, &outPipePrms->outFmt, sizeof (Fvid2_Format));
    dssWbCorePrms.memType                   = outPipePrms->memType;
    dssWbCorePrms.wbCfg.pipeCfg.scEnable    = outPipePrms->scEnable;
    dssWbCorePrms.wbCfg.pipeCfg.cropEnable  = outPipePrms->cropEnable;
    dssWbCorePrms.inPosX                    = outPipePrms->cropCfg.cropStartX;
    dssWbCorePrms.inPosY                    = outPipePrms->cropCfg.cropStartY;
    dssWbCorePrms.inNode                    = hObj->createPrms.wbInNode;
    dssWbCorePrms.wbMode                    = VPS_DSS_DISPC_WB_M2M;
    dssWbCorePrms.wbCfg.advDmaCfg           = outPipePrms->advDmaCfg;
    /* Here for WB pipeline, the cropping is done in the overlay itself
     * for region based write back input width is equal to cropwidth
     * itself.Same for cropHeight.*/
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    /* For tda2xx inCropCfg is not valid.
     * writeback inHeight and inWidth is derived from inFmt or overlay. */
    if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
    {
        dssWbCorePrms.inWidth   = hObj->dssPrms.ovlyWidth;
        dssWbCorePrms.inHeight  = hObj->dssPrms.ovlyHeight;
    }
    else
    {
        dssWbCorePrms.inWidth   = hObj->dssPrms.inPipePrms[0U].tarWidth;
        dssWbCorePrms.inHeight  = hObj->dssPrms.inPipePrms[0U].tarHeight;
    }
#else
    if (TRUE == outPipePrms->cropEnable)
    {
        dssWbCorePrms.inWidth   = outPipePrms->cropCfg.cropWidth;
        dssWbCorePrms.inHeight  = outPipePrms->cropCfg.cropHeight;
    }
    else
    {
        if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
        {
            dssWbCorePrms.inWidth   = hObj->dssPrms.ovlyWidth;
            dssWbCorePrms.inHeight  = hObj->dssPrms.ovlyHeight;
        }
        else
        {
            dssWbCorePrms.inWidth   = hObj->dssPrms.inPipePrms[0U].tarWidth;
            dssWbCorePrms.inHeight  = hObj->dssPrms.inPipePrms[0U].tarHeight;
        }
    }
#endif
    dssWbCorePrms.wbCfg.pipeCfg.cscFullRngEnable =
        outPipePrms->cscFullRngEnable;
    if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
    {
        /* Output from overlay - always RGB888 */
        dssWbCorePrms.indataFormat = FVID2_DF_BGR24_888;
        dssWbCorePrms.sourceWidth  = hObj->dssPrms.ovlyWidth;
        dssWbCorePrms.sourceHeight = hObj->dssPrms.ovlyHeight;
    }
    else
    {
        /* Output from input pipe - force to RGB888 so that core/HAL
         * implementation is same as when in display mode i.e. pipeline
         * is always converted to RGB (like in overlay) and then converted back
         * to YUV/RGB */
        dssWbCorePrms.indataFormat = FVID2_DF_BGR24_888;
        dssWbCorePrms.sourceWidth  = hObj->dssPrms.inPipePrms[0U].tarWidth;
        dssWbCorePrms.sourceHeight = hObj->dssPrms.inPipePrms[0U].tarHeight;
    }

    /* Configure the core */
    retVal = instObj->outCoreOps->setParams(
                    instObj->outCoreHandle, &dssWbCorePrms, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "Set DSSWB parameter failed\r\n");
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_020)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1781)
 */
static Int32 vpsMdrvDssSetPrmsOvly(VpsMDrv_DssHandleObj *hObj)
{
    Int32           retVal = FVID2_SOK;
    UInt32          ovlyId;
    VpsHal_Handle   ovlyHandle;

    /* In case of writeback from overlay, the overlay size should be set */
    if (TRUE == VpsDss_isWbInNodeFromOvly(hObj->createPrms.wbInNode))
    {
        if (VPS_DSS_DISPC_WB_IN_NODE_LCD1 == hObj->createPrms.wbInNode)
        {
            ovlyId = VPSHAL_DSS_DISPC_LCD1;
        }
        else if (VPS_DSS_DISPC_WB_IN_NODE_LCD2 == hObj->createPrms.wbInNode)
        {
            ovlyId = VPSHAL_DSS_DISPC_LCD2;
        }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        else if (VPS_DSS_DISPC_WB_IN_NODE_LCD3 == hObj->createPrms.wbInNode)
        {
            ovlyId = VPSHAL_DSS_DISPC_LCD3;
        }
        else if (VPS_DSS_DISPC_WB_IN_NODE_TV == hObj->createPrms.wbInNode)
        {
            ovlyId = VPSHAL_DSS_DISPC_HDMI;
        }
#endif
        else
        {
            retVal = FVID2_EFAIL;
        }

        if (FVID2_SOK == retVal)
        {
            retVal = VpsHal_dssOvlySetSize(
                ovlyId, hObj->dssPrms.ovlyWidth, hObj->dssPrms.ovlyHeight);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMDrvDssTrace, GT_ERR, "Set Ovly Size failed\r\n");
            }
        }

        if (FVID2_SOK == retVal)
        {
            ovlyHandle = VpsHal_dssOvlyGetHandle(ovlyId);
            GT_assert(VpsMDrvDssTrace, (NULL != ovlyHandle));

            retVal = VpsHal_dssOvlyPanelConf(
                            ovlyHandle, &hObj->dssPrms.ovlyCfg);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMDrvDssTrace, GT_ERR, "Set Ovly Cfg failed\r\n");
            }
        }
    }

    return (retVal);
}
