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
 *  \file vpsdrv_displayCore.c
 *
 *  \brief File containing the VPS display driver functions related to core
 *  interactions.
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

static Int32 vpsDrvDispOpenDssCore(VpsDrv_DispInstObj *instObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Open and configure the core connected to the driver instance.
 */
Int32 vpsDrvDispOpenCore(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->getProperty));

    instObj->coreHandle = NULL;

    /* Get core property */
    retVal = instObj->coreOps->getProperty(
        instObj->coreInstObj,
        &instObj->coreProperty);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Get core property failed!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Call the respective core open function */
        switch (instObj->coreProperty.name)
        {
            case VPSCORE_DISP_DSS:
                retVal = vpsDrvDispOpenDssCore(instObj);
                break;

            default:
                GT_0trace(VpsDrvDispTrace, GT_ERR, "Unknown core!!\r\n");
                retVal = FVID2_EFAIL;
                break;
        }
    }

    return (retVal);
}

Int32 vpsDrvDispCloseCore(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->close));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreHandle));

    if (NULL != instObj->coreHandle)
    {
        /* Close core */
        retVal = instObj->coreOps->close(instObj->coreHandle);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Core close failed!!\r\n");
        }
        instObj->coreHandle = NULL;
    }

    return (retVal);
}

Int32 vpsDrvDispStartCore(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->start));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreHandle));

    /* Start core */
    retVal = instObj->coreOps->start(instObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Core start failed!!\r\n");
    }

    return (retVal);
}

Int32 vpsDrvDispStopCore(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->stop));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreHandle));

    /* Stop core */
    retVal = instObj->coreOps->stop(instObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Core stop failed!!\r\n");
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-787)
 */
Int32 vpsDrvDispSetDssCoreParams(VpsDrv_DispInstObj      *instObj,
                                 const Vps_DispDssParams *dssPrms)
{
    Int32 retVal = FVID2_SOK;
    VpsCore_DispDssParams    dssCorePrms;
    Vps_DssDispcVidConfig    vidCoreCfg;
    Vps_DssDispcGfxConfig    gfxCoreCfg;
    Vps_DssDispcAdvDmaConfig advCoreDmaCfg;
    Vps_DssDispcVidVC1Config vc1CoreCfg;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->setParams));
    GT_assert(VpsDrvDispTrace, (NULL != dssPrms));

    if (VPSCORE_DISP_DSS != instObj->coreProperty.name)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR,
                  "Can't set DSS parameter to this core\r\n");
        retVal = FVID2_EFAIL;
    }
    if (FVID2_SOK == retVal)
    {
        dssCorePrms.memType     = dssPrms->memType;
        dssCorePrms.posX        = dssPrms->posX;
        dssCorePrms.posY        = dssPrms->posY;
        dssCorePrms.tarHeight   = dssPrms->tarHeight;
        dssCorePrms.tarWidth    = dssPrms->tarWidth;
        dssCorePrms.ovlyPipeCfg = NULL;
        dssCorePrms.channelOut  = 0U;
        dssCorePrms.channelOut2 = 0U;

        BspUtils_memcpy(
            &dssCorePrms.inFmt,
            &dssPrms->inFmt,
            sizeof (Fvid2_Format));

        if (Vps_dispIsVidInst(instObj->drvInstId) == (Bool) TRUE)
        {
            if (dssPrms->vidCfg != NULL)
            {
                dssCorePrms.vidCfg = &vidCoreCfg;
                BspUtils_memcpy(
                    &dssCorePrms.vidCfg->pipeCfg,
                    &dssPrms->vidCfg->pipeCfg,
                    sizeof (Vps_DssDispcVidPipeConfig));

                if (dssPrms->vidCfg->advDmaCfg != NULL)
                {
                    dssCorePrms.vidCfg->advDmaCfg = &advCoreDmaCfg;
                    BspUtils_memcpy(
                        dssCorePrms.vidCfg->advDmaCfg,
                        dssPrms->vidCfg->advDmaCfg,
                        sizeof (Vps_DssDispcAdvDmaConfig));
                }
                else
                {
                    dssCorePrms.vidCfg->advDmaCfg = NULL;
                }

                if (dssPrms->vidCfg->vc1Cfg != NULL)
                {
                    dssCorePrms.vidCfg->vc1Cfg = &vc1CoreCfg;
                    BspUtils_memcpy(
                        dssCorePrms.vidCfg->vc1Cfg,
                        dssPrms->vidCfg->vc1Cfg,
                        sizeof (Vps_DssDispcVidVC1Config));
                }
                else
                {
                    dssCorePrms.vidCfg->vc1Cfg = NULL;
                }
            }
            else
            {
                dssCorePrms.vidCfg = NULL;
            }
        }
        else if (Vps_dispIsGfxInst(instObj->drvInstId) == (Bool) TRUE)
        {
            if (dssPrms->gfxCfg != NULL)
            {
                dssCorePrms.gfxCfg = &gfxCoreCfg;
                BspUtils_memcpy(
                    &dssCorePrms.gfxCfg->pipeCfg,
                    &dssPrms->gfxCfg->pipeCfg,
                    sizeof (Vps_DssDispcGfxPipeConfig));

                if (dssPrms->gfxCfg->advDmaCfg != NULL)
                {
                    dssCorePrms.gfxCfg->advDmaCfg = &advCoreDmaCfg;
                    BspUtils_memcpy(
                        dssCorePrms.gfxCfg->advDmaCfg,
                        dssPrms->gfxCfg->advDmaCfg,
                        sizeof (Vps_DssDispcAdvDmaConfig));
                }
                else
                {
                    dssCorePrms.gfxCfg->advDmaCfg = NULL;
                }
            }
            else
            {
                dssCorePrms.gfxCfg = NULL;
            }
        }
        else
        {
            retVal = FVID2_EFAIL;
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Invalid Display Instance\r\n");
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Configure the core */
        retVal = instObj->coreOps->setParams(instObj->coreHandle,
                                             &dssCorePrms,
                                             NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Set DSS parameter failed\r\n");
        }
    }
    return (retVal);
}

Int32 vpsDrvDispGetDssCoreParams(VpsDrv_DispInstObj *instObj,
                                 Vps_DispDssParams  *dssPrms)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->getParams));
    GT_assert(VpsDrvDispTrace, (NULL != dssPrms));

    if (VPSCORE_DISP_DSS != instObj->coreProperty.name)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR,
                  "Can't set DSS parameter to this core\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Get Configuration from core */
        retVal = instObj->coreOps->getParams(instObj->coreHandle,
                                             dssPrms);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvDispTrace, GT_ERR, "Get DSS parameter failed\r\n");
        }
    }

    return (retVal);
}

Int32 vpsDrvDispGetCoreErrStat(VpsDrv_DispInstObj        *instObj,
                               VpsCore_DssVidErrorStatus *errStatus)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->getErrorStat));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreHandle));

    /* Get Error Count */
    retVal = instObj->coreOps->getErrorStat(instObj->coreHandle, errStatus);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Get Error Status failed!!\r\n");
    }

    return (retVal);
}

static Int32 vpsDrvDispOpenDssCore(VpsDrv_DispInstObj *instObj)
{
    Int32 retVal = FVID2_SOK, tempRetVal;
    VpsCore_OpenPrms         openPrms;
    VpsCore_DssOpenParams    dssOpenPrms;
    VpsCore_DssOpenRetParams dssRetPrms;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->open));

    /* Init parameters */
    instObj->coreHandle = NULL;
    openPrms.drvData    = instObj;
    openPrms.reqFrmCb   = &vpsDrvDispCoreReqFrameCb;
    openPrms.frmDoneCb  = &vpsDrvDispCoreFrameDoneCb;

    /* Open the core instance */
    switch (instObj->drvInstId)
    {
        case VPS_DISP_INST_DSS_VID1:
            dssOpenPrms.src = VPS_DSS_DISPC_PIPE_VID1;
            break;

        case VPS_DISP_INST_DSS_VID2:
            dssOpenPrms.src = VPS_DSS_DISPC_PIPE_VID2;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (OMAP5430_BUILD)
        case VPS_DISP_INST_DSS_VID3:
            dssOpenPrms.src = VPS_DSS_DISPC_PIPE_VID3;
            break;
#endif

        case VPS_DISP_INST_DSS_GFX1:
            dssOpenPrms.src = VPS_DSS_DISPC_PIPE_GFX1;
            break;

        default:
            GT_assert(VpsDrvDispTrace, FALSE);
            break;
    }

    dssOpenPrms.isM2mMode = FALSE;
    instObj->coreHandle = instObj->coreOps->open(
        instObj->coreInstObj,
        &openPrms,
        &dssOpenPrms,
        &dssRetPrms);
    if (NULL == instObj->coreHandle)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Dss core open failed!!\r\n");
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        instObj->standard   = dssRetPrms.standard;
        instObj->dispWidth  = dssRetPrms.dispWidth;
        instObj->dispHeight = dssRetPrms.dispHeight;
        instObj->vencId     = dssRetPrms.vencId;
    }

    /* Close core if error occurs */
    if ((FVID2_SOK != retVal) && (NULL != instObj->coreHandle))
    {
        tempRetVal = vpsDrvDispCloseCore(instObj);
        GT_assert(VpsDrvDispTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

Int32 vpsDrvDispSetDssCscCoeff(VpsDrv_DispInstObj    *instObj,
                               Vps_DssCscCoeff       *cscCoeff)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDispTrace, (NULL != instObj));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDispTrace, (NULL != instObj->coreOps->control));
    GT_assert(VpsDrvDispTrace, (NULL != cscCoeff));

    retVal = instObj->coreOps->control(
        instObj->coreHandle,
        VCORE_DSS_SET_CSC_COEFF,
        (void *) cscCoeff,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDispTrace, GT_ERR, "Set CSC Params failed!!\r\n");
    }

    return (retVal);
}

