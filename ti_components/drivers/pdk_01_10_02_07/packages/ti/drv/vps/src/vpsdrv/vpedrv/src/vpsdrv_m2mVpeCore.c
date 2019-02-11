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
 *  \file vpsdrv_m2mVpeCore.c
 *
 *  \brief VPS VPE M2M driver internal file used for core interactions.
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

static Int32 vpsMdrvVpeCfgVpeCore(const VpsMdrv_VpeHandleObj *hObj,
                                  VpsMdrv_VpeChObj           *chObj,
                                  Vcore_M2mHandle             coreHandle,
                                  const Vcore_M2mOps         *coreOps);
static Int32 vpsMdrvVpeCfgVpeWrbkCore(const VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj           *chObj,
                                      Vcore_M2mHandle             coreHandle,
                                      const Vcore_M2mOps         *coreOps);

static Int32 vpsMdrvVpeGetSocCh(VpsMdrv_VpeHandleObj *hObj,
                                VpsMdrv_VpeChObj     *chObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  vpsMdrvVpeOpenCores
 *  Opens and configures all the cores required for this handle.
 */
Int32 vpsMdrvVpeOpenCores(VpsMdrv_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Reset the handles first */
    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        hObj->coreHandle[coreCnt] = NULL;
    }

    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Open and configure core only if needed by that instance */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->open));

            /* Open core */
            hObj->coreHandle[coreCnt] = coreOps->open(
                instObj->coreInstId[coreCnt],
                hObj->createPrms.numCh);
            if (NULL == hObj->coreHandle[coreCnt])
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not open core %d!\r\n", coreCnt);
                retVal = FVID2_EALLOC;
                break;
            }
        }
    }

    /* Close handles if error occurs */
    if (FVID2_SOK != retVal)
    {
        vpsMdrvVpeCloseCores(hObj);
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeCloseCores
 *  Closes all the cores opened for this handle.
 */
Int32 vpsMdrvVpeCloseCores(VpsMdrv_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Close cores only if already opened for that instance */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->close));

            if (NULL != hObj->coreHandle[coreCnt])
            {
                retVal = coreOps->close(hObj->coreHandle[coreCnt]);
                GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == retVal));
                hObj->coreHandle[coreCnt] = NULL;
            }
        }
    }

    return (retVal);
}

Int32 vpsMdrvVpeConfigCores(VpsMdrv_VpeHandleObj *hObj,
                            VpsMdrv_VpeChObj     *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    UInt32 scalerId;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;
    Vcore_M2mProperty   property;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Open and configure core only if needed by that instance */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getProperty));

            /* Get core property */
            retVal = coreOps->getProperty(hObj->coreHandle[coreCnt], &property);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not get property of core %d!\r\n", coreCnt);
            }

            if (FVID2_SOK == retVal)
            {
                /* Configure the core */
                if (VCORE_M2M_VPE == property.name)
                {
                    /* Configure VPE core */
                    retVal = vpsMdrvVpeCfgVpeCore(
                        hObj,
                        chObj,
                        hObj->coreHandle[coreCnt],
                        coreOps);
                }
                else if (VCORE_M2M_DWB == property.name)
                {
                    /* Configure VPE writeback core */
                    retVal = vpsMdrvVpeCfgVpeWrbkCore(
                        hObj,
                        chObj,
                        hObj->coreHandle[coreCnt],
                        coreOps);
                }
                else
                {
                    GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                              "Core type %d not supported\r\n", property.type);
                    retVal = FVID2_EFAIL;
                }
            }

            if (FVID2_SOK != retVal)
            {
                GT_2trace(VpsMdrvVpeTrace, GT_ERR,
                          "Config of core %d for channel %d failed.\r\n",
                          coreCnt, chObj->chNum);
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the VPDMA channels for which to program the sync on client */
        retVal = vpsMdrvVpeGetSocCh(hObj, chObj);
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the scaling ratio and coeff pointers */
        for (scalerId = 0U; scalerId < VPS_M2M_SCALER_ID_MAX; scalerId++)
        {
            retVal = vpsMdrvVpeGetScFactorCfg(hObj, chObj, scalerId);
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

Int32 vpsMdrvVpeGetScFactorCfg(VpsMdrv_VpeHandleObj *hObj,
                               VpsMdrv_VpeChObj     *chObj,
                               UInt32                scalerId)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    VpsMdrv_VpeInstObj       *instObj;
    const Vcore_M2mOps       *coreOps;
    Vcore_M2mScGetCoeffParams getCoeffPrms;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Get the core to which the scaler ID matches */
    coreCnt = instObj->scalerCoreId[scalerId];
    GT_assert(VpsMdrvVpeTrace, (VPSMDRV_VPE_MAX_CORE != coreCnt));
    coreOps = instObj->coreOps[coreCnt];
    /* Check if the scaler ID is valid */
    if (NULL == coreOps)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid Scaler ID\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the current scaling factor */
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getScFactorConfig));
        retVal = coreOps->getScFactorConfig(
            hObj->coreHandle[coreCnt],
            chObj->chNum,
            &(chObj->scFactor[scalerId]));
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "EFAIL: Getting the Scaling Factor Config Failed!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the coeff memory for the current SC factor */
        getCoeffPrms.hScalingSet =
            chObj->scFactor[scalerId].hScalingSet;
        getCoeffPrms.vScalingSet =
            chObj->scFactor[scalerId].vScalingSet;
        /* Returned by core */
        getCoeffPrms.horzCoeffMemPtr         = NULL;
        getCoeffPrms.vertCoeffMemPtr         = NULL;
        getCoeffPrms.vertBilinearCoeffMemPtr = NULL;
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getScCoeff));
        retVal = coreOps->getScCoeff(
            hObj->coreHandle[coreCnt],
            chObj->chNum,
            &getCoeffPrms);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "EFAIL: Getting the Scaling Factor Config Failed!!\r\n");
        }
        else
        {
            /* Note: Coeff mem could be NULL as well in case of RAV or bypass
             * modes. Hence NULL check is not performed */
            chObj->horzCoeffMemPtr[coreCnt] = getCoeffPrms.horzCoeffMemPtr;
            chObj->vertCoeffMemPtr[coreCnt] = getCoeffPrms.vertCoeffMemPtr;
        }
    }

    return (retVal);
}

Int32 vpsMdrvVpeDeiRdAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeInstObj *instObj;
    Vps_DeiRdWrAdvCfg  *advCfg;
    Vcore_M2mProperty   property;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getProperty));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        advCfg = (Vps_DeiRdWrAdvCfg *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (advCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get core property */
        retVal = coreOps->getProperty(
            hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
            &property);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not get VPE core property\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if ((VCORE_M2M_VPE == property.name) &&
            ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VPE_CORE_IDX]) &&
            (NULL != coreOps->control))
        {
            retVal = coreOps->control(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                VCORE_M2M_IOCTL_GET_DEI_CFG,
                advCfg);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Get DEI Adv IOCTL failed\r\n");
            }
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "IOCTL not supported for this instance\r\n");
            retVal = FVID2_EUNSUPPORTED_CMD;
        }
    }

    return (retVal);
}

Int32 vpsMdrvVpeDeiWrAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 descSet;
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeChObj   *chObj;
    VpsMdrv_VpeInstObj *instObj;
    Vps_DeiRdWrAdvCfg  *advCfg;
    Vcore_M2mProperty   property;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getProperty));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programReg));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        advCfg = (Vps_DeiRdWrAdvCfg *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (advCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get core property */
        retVal = coreOps->getProperty(
            hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
            &property);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not get VPE core property\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        if ((VCORE_M2M_VPE == property.name) &&
            ((UInt32) TRUE == instObj->isCoreReq[VPSMDRV_VPE_VPE_CORE_IDX]) &&
            (NULL != coreOps->control))
        {
            retVal = coreOps->control(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                VCORE_M2M_IOCTL_SET_DEI_CFG,
                advCfg);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Get DEI Adv IOCTL failed\r\n");
            }
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "IOCTL not supported for this instance\r\n");
            retVal = FVID2_EUNSUPPORTED_CMD;
        }
    }

    if (FVID2_SOK == retVal)
    {
        chObj = hObj->chObjs[advCfg->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            retVal += coreOps->programReg(
                hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                chObj->chNum,
                &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX]);
        }
    }

    return (retVal);
}

/* TODO */
#if 0
Int32 vpsMdrvVpeScRdAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    const Vcore_M2mOps  *coreOps = NULL;
    VpsMdrv_VpeChObj    *chObj;
    VpsMdrv_VpeInstObj  *instObj;
    Vps_ScRdWrAdvCfg    *advCfg;
    Vcore_M2mScCfgParams scCfgPrms;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        advCfg = (Vps_ScRdWrAdvCfg *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (advCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the core to which the scaler ID matches */
        coreCnt = instObj->scalerCoreId[advCfg->scalerId];
        GT_assert(VpsMdrvVpeTrace, (VPSMDRV_VPE_MAX_CORE != coreCnt));
        coreOps = instObj->coreOps[coreCnt];
        /* Check if the scaler ID is valid */
        if (NULL == coreOps)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid Scaler ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (NULL != coreOps->control)
        {
            chObj = hObj->chObjs[advCfg->chNum];
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

            scCfgPrms.chNum    = advCfg->chNum;
            scCfgPrms.scAdvCfg = &advCfg->scAdvCfg;
            /* Since config memory is same for both the sets, using 0th set. */
            scCfgPrms.descMem = &chObj->coreDescMem[0U][coreCnt];
            retVal = coreOps->control(
                hObj->coreHandle[coreCnt],
                VCORE_M2M_IOCTL_GET_SC_CFG,
                &scCfgPrms);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Get SC Adv IOCTL failed\r\n");
            }
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "IOCTL not supported for this instance\r\n");
            retVal = FVID2_EUNSUPPORTED_CMD;
        }
    }

    return (retVal);
}

Int32 vpsMdrvVpeScWrAdvCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    const Vcore_M2mOps  *coreOps = NULL;
    VpsMdrv_VpeChObj    *chObj;
    VpsMdrv_VpeInstObj  *instObj;
    Vps_ScRdWrAdvCfg    *advCfg;
    Vcore_M2mScCfgParams scCfgPrms;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        advCfg = (Vps_ScRdWrAdvCfg *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (advCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Get the core to which the scaler ID matches */
        coreCnt = instObj->scalerCoreId[advCfg->scalerId];
        GT_assert(VpsMdrvVpeTrace, (VPSMDRV_VPE_MAX_CORE != coreCnt));
        coreOps = instObj->coreOps[coreCnt];
        /* Check if the scaler ID is valid */
        if (NULL == coreOps)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid Scaler ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (NULL != coreOps->control)
        {
            chObj = hObj->chObjs[advCfg->chNum];
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

            scCfgPrms.chNum    = advCfg->chNum;
            scCfgPrms.scAdvCfg = &advCfg->scAdvCfg;
            /* Since config memory is same for both the sets, using 0th set. */
            scCfgPrms.descMem = &chObj->coreDescMem[0U][coreCnt];
            retVal = coreOps->control(
                hObj->coreHandle[coreCnt],
                VCORE_M2M_IOCTL_SET_SC_CFG,
                &scCfgPrms);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Set SC Adv IOCTL failed\r\n");
            }
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "IOCTL not supported for this instance\r\n");
            retVal = FVID2_EUNSUPPORTED_CMD;
        }
    }

    return (retVal);
}

#endif

/**
 * vpsMdrvVpeDeiSetFmdCfgIoctl
 * Set FMD configuration register to overlay memory.
 * This IOCTL call actually writes to the overlay memory.
 */
Int32 vpsMdrvVpeDeiSetFmdCfgIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 descSet;
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeChObj   *chObj;
    VpsMdrv_VpeInstObj *instObj;
    Vps_DeiFmdConfig   *fmdCfg;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programFmdReg));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        fmdCfg = (Vps_DeiFmdConfig *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (fmdCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        chObj = hObj->chObjs[fmdCfg->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

        if (TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            retVal +=
                coreOps->programFmdReg(
                    hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                    fmdCfg,
                    &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX]);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Ensure the DEI handle-level FMD flag is the same as the register */
        hObj->filmMode = fmdCfg->filmMode;
    }

    return (retVal);
}

/**
 * vpsMdrvVpeDeiUpdateFmdIoctl
 * Write FMD Update register to overlay memory.
 * This IOCTL call actually writes to the overlay memory
 */
Int32 vpsMdrvVpeDeiUpdateFmdIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 descSet;
    const Vcore_M2mOps     *coreOps;
    VpsMdrv_VpeChObj       *chObj;
    VpsMdrv_VpeInstObj     *instObj;
    Vps_DeiFmdUpdateConfig *fmdUpdateCfg;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programFmdUpdateReg));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        fmdUpdateCfg = (Vps_DeiFmdUpdateConfig *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (fmdUpdateCfg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        chObj = hObj->chObjs[fmdUpdateCfg->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

        if (TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        for (descSet = 0U; descSet < VPSMDRV_VPE_MAX_DESC_SET; descSet++)
        {
            retVal +=
                coreOps->programFmdUpdateReg(
                    hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
                    fmdUpdateCfg,
                    &chObj->coreDescMem[descSet][VPSMDRV_VPE_VPE_CORE_IDX]);
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeDeiRdFmdStatIoctl
 *  FMD Status register read IOCTL.
 */
Int32 vpsMdrvVpeDeiRdFmdStatIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    const Vcore_M2mOps  *coreOps;
    VpsMdrv_VpeInstObj  *instObj;
    Vps_DeiFmdStatusReg *fmdStatusReg;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->control));
    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        fmdStatusReg = (Vps_DeiFmdStatusReg *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if (fmdStatusReg->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        retVal = coreOps->control(
            hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
            VCORE_M2M_IOCTL_GET_DEI_FMD_STAT,
            fmdStatusReg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Get DEI FMD Status Reg IOCTL failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeCfgDeiCore
 *  Configures the VPE core according to the channel parameters.
 */
static Int32 vpsMdrvVpeCfgVpeCore(const VpsMdrv_VpeHandleObj *hObj,
                                  VpsMdrv_VpeChObj           *chObj,
                                  Vcore_M2mHandle             coreHandle,
                                  const Vcore_M2mOps         *coreOps)
{
    Int32                retVal = FVID2_SOK;
    Vcore_VpeParams      vpeCorePrms;
    Vcore_M2mDeiCtxInfo *vpeCoreCtxInfo;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreHandle));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->setParams));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getDeiCtxInfo));

    /* Copy the VPE buffer format */
    BspUtils_memcpy(
        &vpeCorePrms.fmt,
        &chObj->vpePrms.inFmt,
        sizeof (Fvid2_Format));

    /* Fill other VPE core parameters */
    vpeCorePrms.frameWidth  = chObj->vpePrms.inFmt.width;
    vpeCorePrms.frameHeight = chObj->vpePrms.inFmt.height;
    vpeCorePrms.startX      = 0U;
    vpeCorePrms.startY      = 0U;

    vpeCorePrms.secScanFmt = chObj->vpePrms.outFmt.scanFormat;
    vpeCorePrms.memType    = chObj->vpePrms.inMemType;
    vpeCorePrms.tarWidth   = chObj->vpePrms.outFmt.width;
    vpeCorePrms.tarHeight  = chObj->vpePrms.outFmt.height;

    /* Copy the DEI parameters */
    BspUtils_memcpy(
        &vpeCorePrms.deiCfg,
        &chObj->vpePrms.deiCfg,
        sizeof (Vps_DeiConfig));

    /* Copy the scaler parameters */
    BspUtils_memcpy(
        &vpeCorePrms.scCfg,
        &chObj->vpePrms.scCfg,
        sizeof (Vps_ScConfig));

    /* Copy the scaler crop parameters */
    BspUtils_memcpy(
        &vpeCorePrms.cropCfg,
        &chObj->vpePrms.scCropCfg,
        sizeof (Fvid2_CropConfig));

    /* Set the VPE core parameter */
    retVal = coreOps->setParams(coreHandle, chObj->chNum, &vpeCorePrms);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "Set params for VPE core failed!\r\n");
    }

    /* Get the descriptor info of VPE core */
    vpeCoreCtxInfo = &chObj->vpeCoreCtxInfo;
    retVal         =
        coreOps->getDeiCtxInfo(coreHandle, chObj->chNum, vpeCoreCtxInfo);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "Could not get context info for VPE core!\r\n");
    }
    else
    {
        /* Assert if info more than array size */
        GT_assert(VpsMdrvVpeTrace,
                  (vpeCoreCtxInfo->numPrevFld <= VCORE_VPE_MAX_PREV_FLD));
        GT_assert(VpsMdrvVpeTrace,
                  (vpeCoreCtxInfo->numCurFldOut <= 1U));
        GT_assert(VpsMdrvVpeTrace,
                  (vpeCoreCtxInfo->numMvIn <= VCORE_VPE_MAX_MV_IN));
        GT_assert(VpsMdrvVpeTrace, (vpeCoreCtxInfo->numMvOut <= 1U));
        GT_assert(VpsMdrvVpeTrace,
                  (vpeCoreCtxInfo->numMvstmIn <=
                   (VCORE_VPE_MAX_MVSTM_IN + 1U)));
        GT_assert(VpsMdrvVpeTrace, (vpeCoreCtxInfo->numMvstmOut <= 1U));
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeCfgVpeWrbkCore
 *  Configures the VPE Wrbk core according to the channel parameters.
 */
static Int32 vpsMdrvVpeCfgVpeWrbkCore(const VpsMdrv_VpeHandleObj *hObj,
                                      VpsMdrv_VpeChObj           *chObj,
                                      Vcore_M2mHandle             coreHandle,
                                      const Vcore_M2mOps         *coreOps)
{
    Int32           retVal = FVID2_SOK;
    Vcore_M2mFormat vwbFmt;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreHandle));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->setFormat));

    /* Copy the VPE writeback out buffer format */
    BspUtils_memcpy(
        &vwbFmt.fmt,
        &chObj->vpePrms.outFmt,
        sizeof (Fvid2_Format));

    /* Fill other VPE WRBK core formats */
    vwbFmt.frameWidth  = vwbFmt.fmt.width;
    vwbFmt.frameHeight = vwbFmt.fmt.height;
    vwbFmt.startX      = 0U;
    vwbFmt.startY      = 0U;
    vwbFmt.secScanFmt  = vwbFmt.fmt.scanFormat;
    vwbFmt.memType     = chObj->vpePrms.outMemType;

    /* Set the VPE WRBK core format */
    retVal = coreOps->setFormat(coreHandle, chObj->chNum, &vwbFmt);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "Set format for VPE WRBK core failed!\r\n");
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeGetSocCh
 */
static Int32 vpsMdrvVpeGetSocCh(VpsMdrv_VpeHandleObj *hObj,
                                VpsMdrv_VpeChObj     *chObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 coreCnt;
    UInt32 numSocCh;
    UInt32 chCnt;
    Vcore_M2mDescInfo   descInfo;
    Vcore_M2mProperty   property;
    const Vcore_M2mOps *coreOps;
    VpsMdrv_VpeInstObj *instObj;

    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    numSocCh = 0U;
    for (coreCnt = 0U; coreCnt < VPSMDRV_VPE_MAX_CORE; coreCnt++)
    {
        /* Get the Descriptor Information for this core */
        if ((UInt32) TRUE == instObj->isCoreReq[coreCnt])
        {
            coreOps = instObj->coreOps[coreCnt];
            /* NULL pointer check */
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
            GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getDescInfo));

            /* Get the descriptor info of each core */
            retVal = coreOps->getDescInfo(
                hObj->coreHandle[coreCnt],
                chObj->chNum,
                &descInfo);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "Could not get core info for core %d!\r\n", coreCnt);
            }

            if (FVID2_SOK == retVal)
            {
                /* Get the Property info to see if it is input ot output core */
                retVal = coreOps->getProperty(
                    hObj->coreHandle[coreCnt],
                    &property);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                              "Could not get property for core %d!\r\n", coreCnt);
                }
            }

            if (FVID2_SOK == retVal)
            {
                GT_assert(VpsMdrvVpeTrace,
                          (descInfo.numChannels < VCORE_M2M_MAX_VPDMA_CH));
                for (chCnt = 0U; chCnt < descInfo.numChannels; chCnt++)
                {
                    GT_assert(VpsMdrvVpeTrace,
                              (numSocCh < VCORE_M2M_MAX_VPDMA_CH));
                    chObj->socChNum[numSocCh] = descInfo.socChNum[chCnt];
                    numSocCh++;
                }
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        chObj->numVpdmaChannels = numSocCh;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeSetRangMapRedtCfgIoctl
 */
Int32 vpsMdrvVpeSetRangMapRedtCfgIoctl(VpsMdrv_VpeHandleObj *hObj,
                                       Ptr                   cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    Vps_RngMapRdtCfg   *rngMapRdtCfg;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->control));

    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Don't allow to set Range Mapping or Range reduction cfg params when
         * requests are pending with driver */
        if (0U != hObj->numUnProcessedReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't Set Range Mapping or Range reduction cfg params when "
                "%d requests are pending!!\r\n", hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if (FVID2_SOK == retVal)
    {
        rngMapRdtCfg = (Vps_RngMapRdtCfg *) cmdArgs;

        retVal = coreOps->control(
            hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
            VCORE_M2M_IOCTL_SET_RANGE_MAP_REDUCT_CFG,
            rngMapRdtCfg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "SET RANGE MAP and RANGE REDUCTION CFG IOCTL failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeGetRangMapRedtCfgIoctl
 */
Int32 vpsMdrvVpeGetRangMapRedtCfgIoctl(VpsMdrv_VpeHandleObj *hObj,
                                       Ptr                   cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    Vps_RngMapRdtCfg   *rngMapRdtCfg;
    VpsMdrv_VpeInstObj *instObj;
    const Vcore_M2mOps *coreOps;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));
    coreOps = instObj->coreOps[VPSMDRV_VPE_VPE_CORE_IDX];
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps));
    GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->control));

    if (NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Don't allow to get Range Mapping or Range reduction  cfg params when
         * requests are pending with driver */
        if (0U != hObj->numUnProcessedReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't Get Range Mapping or Range reduction cfg params when "
                "%d requests are pending!!\r\n", hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if (FVID2_SOK == retVal)
    {
        rngMapRdtCfg = (Vps_RngMapRdtCfg *) cmdArgs;

        retVal = coreOps->control(
            hObj->coreHandle[VPSMDRV_VPE_VPE_CORE_IDX],
            VCORE_M2M_IOCTL_GET_RANGE_MAP_REDUCT_CFG,
            rngMapRdtCfg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "GET RANGE MAP and RANGE REDUCTION CFG IOCTL failed\r\n");
        }
    }

    return (retVal);
}

