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
 *  \file vpsdrv_captureApi.c
 *
 *  \brief File containing the VPS capture driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static inline Bool Vps_dssIsVidInst(UInt32 instId);
static inline Bool Vps_dssIsGfxInst(UInt32 instId);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_DispInstObj     gDispDrvObj[VPS_DISP_INST_MAX];
UInt32 gDssDrvInit = 0;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
static VpsDrv_DssPlatformData gVpsDssDrvPlatDataTda2xx =
{
    /* Display driver */
    {
        /*  dispDrvInitPrms:drvInstId,
         *  dispDrvInitPrms:coreInstObj,    dispDrvInitPrms:coreOps */
        {
            VPSDRV_DISP_INST_DSS_VID1,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID2,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID3,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_GFX1,
            NULL, NULL
        }
    },
};
#endif
#if defined (SOC_TDA3XX)
static VpsDrv_DssPlatformData gVpsDssDrvPlatDataTda3xx =
{
    /* Display driver */
    {
        /*  dispDrvInitPrms:drvInstId,
         *  dispDrvInitPrms:coreInstObj,    dispDrvInitPrms:coreOps */
        {
            VPSDRV_DISP_INST_DSS_VID1,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID2,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_GFX1,
            NULL, NULL
        },
        {
            0U,
            NULL, NULL
        }
    },
};
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsDrv_dssInit
 *  \brief VPS DSS driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms);

/**
 *  VpsDrv_dssDeInit
 *  \brief VPS DSS driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssDeInit(void);

const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void);

/**
 *  VpsDrv_dssGetInst
 *  \brief Get Handle to the Dss Driver instance as per specified ID
 *
 *  \param instId             Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_DispInstObj *VpsDrv_dssGetInst(UInt32 instId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  VpsDrv_dispInit
 *  \brief VPS DSS capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms)
{
    UInt32 i;

    for (i = 0; i < numInst; i++)
    {
        gDispDrvObj[i].drvInstId   = initPrms[i].drvInstId;
        gDispDrvObj[i].coreInstObj = initPrms[i].coreInstObj;
        gDispDrvObj[i].coreOps     = initPrms[i].coreOps;
    }

    return BSP_SOK;
}

/**
 *  VpsDrv_dispDeInit
 *  \brief VPS DSS capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssDeInit(void)
{
    UInt32 i;
    for (i = 0; i < VPS_DISP_INST_MAX; i++)
    {
        gDispDrvObj[i].drvInstId   = 0U;
        gDispDrvObj[i].coreInstObj = NULL;
        gDispDrvObj[i].coreOps     = NULL;
    }
    return BSP_SOK;
}

/**
 *  VpsDrv_dssGetInst
 *  \brief Get Handle to the capture Driver instance as per specified ID
 *
 *  \param instId             Capture Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_DispInstObj *VpsDrv_dssGetInst(UInt32 instId)
{
    VpsDrv_DispInstObj *pObj = NULL;
    if (gDssDrvInit)
    {
        if (NULL != gDispDrvObj[instId].coreInstObj)
        {
            pObj = &gDispDrvObj[instId];
        }
    }
    return pObj;
}

/**
 *  VpsDrv_dssOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param dssInstId         DSS Instance ID #dssInstId
 *  \param OpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param dssOpenParams     VIP specific parameters #VpsCore_DssOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DispInstObj *VpsDrv_dssOpen(
    UInt32                 dssInstId,
    VpsCore_OpenPrms      *OpenParams,
    VpsCore_DssOpenParams *dssOpenParams)
{
    VpsDrv_DispInstObj      *pObj = NULL;
    Int32 retVal = BSP_SOK;
    VpsCore_DssOpenRetParams dssRetParams;
    BspUtils_memset((void *) (&dssRetParams), 0,
                    sizeof (VpsCore_DssOpenRetParams));

    pObj = (VpsDrv_DispInstObj *) VpsDrv_dssGetInst(dssInstId);
    if (pObj != NULL)
    {
        OpenParams->drvData = pObj;

        /* Open the core instance */
        switch (pObj->drvInstId)
        {
            case VPSDRV_DISP_INST_DSS_VID1:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID1;
                break;

            case VPSDRV_DISP_INST_DSS_VID2:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID2;
                break;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
            case VPSDRV_DISP_INST_DSS_VID3:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID3;
                break;
#endif
            case VPSDRV_DISP_INST_DSS_GFX1:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_GFX1;
                break;

            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }

        dssOpenParams->isM2mMode = FALSE;
        pObj->coreHandle = pObj->coreOps->open(
            pObj->coreInstObj,
            (const VpsCore_OpenPrms *) OpenParams,
            dssOpenParams,
            &dssRetParams);
        if (NULL == pObj->coreHandle)
        {
            retVal = BSP_EFAIL;
        }

        if (BSP_SOK == retVal)
        {
            pObj->standard   = dssRetParams.standard;
            pObj->dispWidth  = dssRetParams.dispWidth;
            pObj->dispHeight = dssRetParams.dispHeight;
            pObj->vencId     = dssRetParams.vencId;
        }
        else
        {
            pObj = NULL;
        }
    }
    return pObj;
}

/**
 *  VpsDrv_dssClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Dss Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssClose(VpsDrv_DispInstObj *pObj)
{
    Int32 retVal = BSP_SOK;
    if (NULL != pObj->coreHandle)
    {
        /* Close core */
        retVal = pObj->coreOps->close(pObj->coreHandle);
        if (BSP_SOK != retVal)
        {
            retVal = BSP_EFAIL;
        }
        pObj->coreHandle = NULL;
    }
    return retVal;
}

/**
 *  VpsDrv_dssStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStart(VpsDrv_DispInstObj *pObj)
{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->start(pObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

/**
 *  VpsDrv_dispStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStop(VpsDrv_DispInstObj *pObj)
{
    return pObj->coreOps->stop(pObj->coreHandle);
}

static inline Bool Vps_dssIsVidInst(UInt32 instId)
{
    Bool isVidInst = FALSE;
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    if ((VPSDRV_DISP_INST_DSS_VID1 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID2 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID3 == instId))
#elif defined (SOC_TDA3XX)
    if ((VPSDRV_DISP_INST_DSS_VID1 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID2 == instId))

#endif
    {
        isVidInst = TRUE;
    }

    return (isVidInst);
}

static inline Bool Vps_dssIsGfxInst(UInt32 instId)
{
    Bool isGfxInst = FALSE;

    if (VPSDRV_DISP_INST_DSS_GFX1 == instId)
    {
        isGfxInst = TRUE;
    }

    return (isGfxInst);
}

/**
 *  VpsDrv_dispSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param instObj           Capture Handle #VpsDrv_DispInstObj
 *  \param DssParams         Path configuration #VpsDrv_DispDssParams
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */

Int32 VpsDrv_dssSetParams(VpsDrv_DispInstObj         *instObj,
                          const VpsDrv_DispDssParams *dssPrms)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DispDssParams    dssCorePrms;
    Vps_DssDispcVidConfig    vidCoreCfg;
    Vps_DssDispcGfxConfig    gfxCoreCfg;
    Vps_DssDispcAdvDmaConfig advCoreDmaCfg;
    Vps_DssDispcVidVC1Config vc1CoreCfg;

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

    if (Vps_dssIsVidInst(instObj->drvInstId) == TRUE)
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
    else if (Vps_dssIsGfxInst(instObj->drvInstId) == TRUE)
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
        GT_assert(VpsDctrlCoreTrace, FALSE);
    }

    if (BSP_SOK == retVal)
    {
        /* Configure the core */
        retVal = instObj->coreOps->setParams(instObj->coreHandle,
                                             &dssCorePrms,
                                             NULL);
        if (BSP_SOK != retVal)
        {
            retVal = BSP_EFAIL;
        }
    }
    return (retVal);
}

/**
 *  VpsDrv_dispGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *  \param vipParams    Pointer to #VpsCore_DispDssParams where configuration
 *                                     will be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssGetParams(VpsDrv_DispInstObj    *pObj,
                          VpsCore_DispDssParams *dssParams)
{
    return pObj->coreOps->getParams(pObj->coreHandle,
                                    &dssParams);
}

const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    return &gVpsDssDrvPlatDataTda2xx;
#elif defined (SOC_TDA3XX)
    return &gVpsDssDrvPlatDataTda3xx;
#else
    return NULL;
#endif
}

