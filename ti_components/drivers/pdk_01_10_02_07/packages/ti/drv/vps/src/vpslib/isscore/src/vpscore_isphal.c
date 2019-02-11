/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpscore_isphal.c
 *
 *  \brief ISP Mem2mem Core internal file containing HAL specific functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/isscore/src/vpscore_isppriv.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Initializes the function pointers in the instance object */
void IspInitHalStartStopFxns(vpscoreissM2mInstObj_t *instObj)
{
    uint32_t moduleCnt;

    for (moduleCnt = 0U; moduleCnt < VPSCORE_ISS_MAX_MODULE; moduleCnt++)
    {
        instObj->startModuleFxn[VCORE_ISP_MODULE_CAL] = NULL;
    }

    /* Initialize the function pointer for start/stop api of the
     * ISP submodules
     * There is no start function for H3A, it has two sub-modules AF and AEW.
     * these submodules will be started independently in putFrames,
     * based on their enabled status */
    instObj->startModuleFxn[VCORE_ISP_MODULE_CAL]     = VpsHal_isscalRdDmaStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_IPIPEIF] = VpsHal_issipipeifStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_NSF3]    = VpsHal_issnsf3Start;
    instObj->startModuleFxn[VCORE_ISP_MODULE_GLBCE]   = VpsHal_issglbceStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_ISIF]    = VpsHal_issisifStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_IPIPE]   = VpsHal_issipipeStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_RSZ]     = VpsHal_issrszStart;
    instObj->startModuleFxn[VCORE_ISP_MODULE_CNF]     = VpsHal_issnsf3Start;
}

/* H3A Set Config */
int32_t IspH3aSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissH3aCtrl_t          *h3aCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_H3A])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == h3aCtrl) ||
        ((VPS_ISS_H3A_MODULE_AF == h3aCtrl->module) &&
         (NULL == h3aCtrl->afCfg)) ||
        ((VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module) &&
         (NULL == h3aCtrl->aewbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_H3A_MODULE_AF == h3aCtrl->module)
        {
            status = VpsHal_issh3aControl(
                hObj->halHandles[VCORE_ISP_MODULE_H3A],
                ISSHAL_IOCTL_H3A_SET_AFCFG,
                h3aCtrl->afCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->h3aCfg.afCfg,
                    h3aCtrl->afCfg,
                    sizeof (hObj->h3aCfg.afCfg));
            }
        }
        else if (VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module)
        {
            status = VpsHal_issh3aControl(
                hObj->halHandles[VCORE_ISP_MODULE_H3A],
                ISSHAL_IOCTL_H3A_SET_AEWBCFG,
                h3aCtrl->aewbCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->h3aCfg.aewbCfg,
                    h3aCtrl->aewbCfg,
                    sizeof (hObj->h3aCfg.aewbCfg));
            }
        }
        else
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

/* H3A Get Config */
int32_t IspH3aGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissH3aCtrl_t          *h3aCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_H3A])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == h3aCtrl) ||
        ((VPS_ISS_H3A_MODULE_AF == h3aCtrl->module) &&
         (NULL == h3aCtrl->afCfg)) ||
        ((VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module) &&
         (NULL == h3aCtrl->aewbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_H3A_MODULE_AF == h3aCtrl->module)
        {
            BspUtils_memcpy(
                h3aCtrl->afCfg,
                &hObj->h3aCfg.afCfg,
                sizeof (hObj->h3aCfg.afCfg));
        }
        else if (VPS_ISS_H3A_MODULE_AEWB == h3aCtrl->module)
        {
            BspUtils_memcpy(
                h3aCtrl->aewbCfg,
                &hObj->h3aCfg.aewbCfg,
                sizeof (hObj->h3aCfg.aewbCfg));
        }
        else
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

/* ISIF Set Config */
int32_t IspIsifSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIsifCtrl_t         *isifCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_ISIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == isifCtrl) ||
        ((VPS_ISS_ISIF_MODULE_WB == isifCtrl->module) &&
         (NULL == isifCtrl->wbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_ISIF_MODULE_WB == isifCtrl->module)
        {
            status = VpsHal_issisifControl(
                hObj->halHandles[VCORE_ISP_MODULE_ISIF],
                ISSHAL_IOCTL_ISIF_SET_WBCFG,
                isifCtrl->wbCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->isifCfg.wbCfg,
                    isifCtrl->wbCfg,
                    sizeof (hObj->isifCfg.wbCfg));
            }
        }
    }
    return (status);
}

/* ISIF Get Config */
int32_t IspIsifGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIsifCtrl_t         *isifCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_ISIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == isifCtrl) ||
        ((VPS_ISS_ISIF_MODULE_WB == isifCtrl->module) &&
         (NULL == isifCtrl->wbCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_ISIF_MODULE_WB == isifCtrl->module)
        {
            BspUtils_memcpy(
                isifCtrl->wbCfg,
                &hObj->isifCfg.wbCfg,
                sizeof (isifCtrl->wbCfg));
        }
    }

    return (status);
}

/* IPIPE Set Config */
int32_t IspIpipeSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIpipeCtrl_t        *ipipeCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_IPIPE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == ipipeCtrl) ||
        ((VPS_ISS_IPIPE_MODULE_CFA == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->cfaCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_WB == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->wbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2RGB1 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2RgbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2RGB2 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2RgbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2YUV == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2YuvCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_YUV444_YUV422 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->yuvPhsCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_DPC_LUT == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->dpcLut)) ||
        ((VPS_ISS_IPIPE_MODULE_DPC_OTF == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->dpcOtf)) ||
        ((VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->gammaCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->eeCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_GIC == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->gicCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_NF1 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->nf1Cfg)) ||
        ((VPS_ISS_IPIPE_MODULE_NF2 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->nf2Cfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        switch (ipipeCtrl->module)
        {
            /* Case is to set CFA Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_CFA:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_CFACFG,
                    ipipeCtrl->cfaCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.cfaCfg,
                        ipipeCtrl->cfaCfg,
                        sizeof (hObj->ipipeCfg.cfaCfg));
                }
                break;

            /* Case is to set White Balance Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_WB:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_WBCFG,
                    ipipeCtrl->wbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.wbCfg,
                        ipipeCtrl->wbCfg,
                        sizeof (hObj->ipipeCfg.wbCfg));
                }
                break;

            /* Case is to set RGB2RGB 1 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB1:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2RGB1CFG,
                    ipipeCtrl->rgb2RgbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.rgb2Rgb1,
                        ipipeCtrl->rgb2RgbCfg,
                        sizeof (hObj->ipipeCfg.rgb2Rgb1));
                }
                break;

            /* Case is to set RGB2RGB 2 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB2:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2RGB2CFG,
                    ipipeCtrl->rgb2RgbCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.rgb2Rgb2,
                        ipipeCtrl->rgb2RgbCfg,
                        sizeof (hObj->ipipeCfg.rgb2Rgb2));
                }
                break;

            /* Case is to set RGB2YUV matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2YUV:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_RGB2YUVCFG,
                    ipipeCtrl->rgb2YuvCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.rgb2Yuv,
                        ipipeCtrl->rgb2YuvCfg,
                        sizeof (hObj->ipipeCfg.rgb2Yuv));
                }
                break;

            /* Case is to set YUV444 to YUV422 Parameters */
            case VPS_ISS_IPIPE_MODULE_YUV444_YUV422:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_YUVCFG,
                    ipipeCtrl->yuvPhsCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.yuvPhs,
                        ipipeCtrl->yuvPhsCfg,
                        sizeof (hObj->ipipeCfg.yuvPhs));
                }
                break;

            /* Case is to set DPC LUT Parameters */
            case VPS_ISS_IPIPE_MODULE_DPC_LUT:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_DPCLUTCFG,
                    ipipeCtrl->dpcLut,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.dpcLut,
                        ipipeCtrl->dpcLut,
                        sizeof (hObj->ipipeCfg.dpcLut));
                }
                break;

            /* Case is to set DPC OTF Parameters */
            case VPS_ISS_IPIPE_MODULE_DPC_OTF:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_DPCOTFCFG,
                    ipipeCtrl->dpcOtf,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.dpcOtf,
                        ipipeCtrl->dpcOtf,
                        sizeof (hObj->ipipeCfg.dpcOtf));
                }
                break;

            /* Case is to set DPC OTF Parameters */
            case VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_GAMMACFG,
                    ipipeCtrl->gammaCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.gammaCfg,
                        ipipeCtrl->gammaCfg,
                        sizeof (hObj->ipipeCfg.gammaCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_3D_LUT:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_3D_LUTCFG,
                    ipipeCtrl->colorConvert3DLutCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.colorConvert3DLutCfg,
                        ipipeCtrl->colorConvert3DLutCfg,
                        sizeof (hObj->ipipeCfg.colorConvert3DLutCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_EECFG,
                    ipipeCtrl->eeCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.eeCfg,
                        ipipeCtrl->eeCfg,
                        sizeof (hObj->ipipeCfg.eeCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_GIC:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_GICCFG,
                    ipipeCtrl->gicCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.gicCfg,
                        ipipeCtrl->gicCfg,
                        sizeof (hObj->ipipeCfg.gicCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_LSC:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_LSCCFG,
                    ipipeCtrl->lscCfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.lscCfg,
                        ipipeCtrl->lscCfg,
                        sizeof (hObj->ipipeCfg.lscCfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_NF1:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_NF1CFG,
                    ipipeCtrl->nf1Cfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.nf1Cfg,
                        ipipeCtrl->nf1Cfg,
                        sizeof (hObj->ipipeCfg.nf1Cfg));
                }
                break;

            case VPS_ISS_IPIPE_MODULE_NF2:
                status = VpsHal_issipipeControl(
                    hObj->halHandles[VCORE_ISP_MODULE_IPIPE],
                    ISSHAL_IOCTL_IPIPE_SET_NF2CFG,
                    ipipeCtrl->nf2Cfg,
                    NULL);

                /* Copy parameters to local structure, which will be used
                 * in GetConfig*/
                if (FVID2_SOK == status)
                {
                    BspUtils_memcpy(
                        &hObj->ipipeCfg.nf2Cfg,
                        ipipeCtrl->nf2Cfg,
                        sizeof (hObj->ipipeCfg.nf2Cfg));
                }
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* IPIPE Get Config */
int32_t IspIpipeGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIpipeCtrl_t        *ipipeCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_IPIPE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == ipipeCtrl) ||
        ((VPS_ISS_IPIPE_MODULE_CFA == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->cfaCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_WB == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->wbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2RGB1 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2RgbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2RGB2 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2RgbCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_RGB2YUV == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->rgb2YuvCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_YUV444_YUV422 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->yuvPhsCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_DPC_LUT == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->dpcLut)) ||
        ((VPS_ISS_IPIPE_MODULE_DPC_OTF == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->dpcOtf)) ||
        ((VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->gammaCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_3D_LUT == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->colorConvert3DLutCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->eeCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_GIC == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->gicCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_LSC == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->lscCfg)) ||
        ((VPS_ISS_IPIPE_MODULE_NF1 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->nf1Cfg)) ||
        ((VPS_ISS_IPIPE_MODULE_NF2 == ipipeCtrl->module) &&
         (NULL == ipipeCtrl->nf2Cfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        switch (ipipeCtrl->module)
        {
            /* Case is to get CFA Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_CFA:
                BspUtils_memcpy(
                    ipipeCtrl->cfaCfg,
                    &hObj->ipipeCfg.cfaCfg,
                    sizeof (hObj->ipipeCfg.cfaCfg));
                break;

            /* Case is to get YUV444 to YUV422 Parameters */
            case VPS_ISS_IPIPE_MODULE_YUV444_YUV422:
                BspUtils_memcpy(
                    ipipeCtrl->yuvPhsCfg,
                    &hObj->ipipeCfg.yuvPhs,
                    sizeof (hObj->ipipeCfg.yuvPhs));
                break;

            /* Case is to get RGB2YUV matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2YUV:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2YuvCfg,
                    &hObj->ipipeCfg.rgb2Yuv,
                    sizeof (hObj->ipipeCfg.rgb2Yuv));
                break;

            /* Case is to set RGB2RGB 1 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB1:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2RgbCfg,
                    &hObj->ipipeCfg.rgb2Rgb1,
                    sizeof (hObj->ipipeCfg.rgb2Rgb1));
                break;

            /* Case is to set RGB2RGB 2 matrix Parameters */
            case VPS_ISS_IPIPE_MODULE_RGB2RGB2:
                BspUtils_memcpy(
                    ipipeCtrl->rgb2RgbCfg,
                    &hObj->ipipeCfg.rgb2Rgb2,
                    sizeof (hObj->ipipeCfg.rgb2Rgb2));
                break;

            /* Case is to set White Balance Parameters of IPIPE */
            case VPS_ISS_IPIPE_MODULE_WB:
                BspUtils_memcpy(
                    ipipeCtrl->wbCfg,
                    &hObj->ipipeCfg.wbCfg,
                    sizeof (hObj->ipipeCfg.wbCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_DPC_OTF:
                BspUtils_memcpy(
                    ipipeCtrl->dpcOtf,
                    &hObj->ipipeCfg.dpcOtf,
                    sizeof (hObj->ipipeCfg.dpcOtf));
                break;

            case VPS_ISS_IPIPE_MODULE_DPC_LUT:
                BspUtils_memcpy(
                    ipipeCtrl->dpcLut,
                    &hObj->ipipeCfg.dpcLut,
                    sizeof (hObj->ipipeCfg.dpcLut));
                break;

            case VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION:
                BspUtils_memcpy(
                    ipipeCtrl->gammaCfg,
                    &hObj->ipipeCfg.gammaCfg,
                    sizeof (hObj->ipipeCfg.gammaCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_3D_LUT:
                BspUtils_memcpy(
                    ipipeCtrl->colorConvert3DLutCfg,
                    &hObj->ipipeCfg.colorConvert3DLutCfg,
                    sizeof (hObj->ipipeCfg.colorConvert3DLutCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER:
                BspUtils_memcpy(
                    ipipeCtrl->eeCfg,
                    &hObj->ipipeCfg.eeCfg,
                    sizeof (hObj->ipipeCfg.eeCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_GIC:
                BspUtils_memcpy(
                    ipipeCtrl->gicCfg,
                    &hObj->ipipeCfg.gicCfg,
                    sizeof (hObj->ipipeCfg.gicCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_LSC:
                BspUtils_memcpy(
                    ipipeCtrl->lscCfg,
                    &hObj->ipipeCfg.lscCfg,
                    sizeof (hObj->ipipeCfg.lscCfg));
                break;

            case VPS_ISS_IPIPE_MODULE_NF1:
                BspUtils_memcpy(
                    ipipeCtrl->nf1Cfg,
                    &hObj->ipipeCfg.nf1Cfg,
                    sizeof (hObj->ipipeCfg.nf1Cfg));
                break;

            case VPS_ISS_IPIPE_MODULE_NF2:
                BspUtils_memcpy(
                    ipipeCtrl->nf2Cfg,
                    &hObj->ipipeCfg.nf2Cfg,
                    sizeof (hObj->ipipeCfg.nf2Cfg));
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* Resizer Set Config */
int32_t IspRszSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissRszCtrl_t          *rszCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_RSZ])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == rszCtrl) ||
        ((VPS_ISS_RSZ_MODULE_RSZCFG == rszCtrl->module) &&
         (NULL == rszCtrl->rszCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* TODO: Avoid this copy since if the parameters are invalid,
         *       it will make current set of parameters also invalid. */
        /* Copy Resizer parameters */
        hObj->rszCfg.srcCfg.opMode =
            rszCtrl->rszCfg->inCfg.opMode;

        BspUtils_memcpy(
            &hObj->rszCfg.srcCfg.procWin,
            &rszCtrl->rszCfg->inCfg.procWin,
            sizeof (hObj->rszCfg.srcCfg.procWin));

        BspUtils_memcpy(
            &hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A],
            &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A],
            sizeof (hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A]));

        if (TRUE == hObj->params.enableRszBOutput)
        {
            BspUtils_memcpy(
                &hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B],
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B],
                sizeof (hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B]));
        }

        status = VpsHal_issrszSetConfig(
            hObj->halHandles[VCORE_ISP_MODULE_RSZ],
            &hObj->rszCfg,
            NULL);
    }

    return (status);
}

/* Resizer Get Config */
int32_t IspRszGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissRszCtrl_t          *rszCtrl)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_RSZ])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == rszCtrl) ||
        ((VPS_ISS_RSZ_MODULE_RSZCFG == rszCtrl->module) &&
         (NULL == rszCtrl->rszCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        rszCtrl->rszCfg->inCfg.opMode = hObj->rszCfg.srcCfg.opMode;
        BspUtils_memcpy(
            &rszCtrl->rszCfg->inCfg.procWin,
            &hObj->rszCfg.srcCfg.procWin,
            sizeof (rszCtrl->rszCfg->inCfg.procWin));

        BspUtils_memcpy(
            &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A],
            &hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_A],
            sizeof (rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_A]));

        if (TRUE == hObj->params.enableRszBOutput)
        {
            BspUtils_memcpy(
                &rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B],
                &hObj->rszCfg.instCfg[VPS_ISS_RSZ_SCALER_B],
                sizeof (rszCtrl->rszCfg->instCfg[VPS_ISS_RSZ_SCALER_B]));
        }
    }

    return (status);
}

/* NSF3 Set Config */
int32_t IspNsf3SetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissNsf3Config_t       *nsf3Cfg,
    vcoreIspModuleId_t        modId)
{
    int32_t  status = FVID2_SOK;
    uint32_t instId;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[modId])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if (VCORE_ISP_MODULE_NSF3 == modId)
    {
        instId = 0U;
    }
    else
    {
        instId = 1U;
    }

    if (NULL != nsf3Cfg)
    {
        status = VpsHal_issnsf3SetConfig(
            hObj->halHandles[modId],
            nsf3Cfg,
            NULL);

        if (FVID2_SOK == status)
        {
            BspUtils_memcpy(
                &hObj->nsf3Cfg[instId],
                nsf3Cfg,
                sizeof (hObj->nsf3Cfg));
        }
    }
    else
    {
        status = FVID2_EBADARGS;
    }

    return (status);
}

/* NSF3 Get Config */
int32_t IspNsf3GetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissNsf3Config_t       *nsf3Cfg,
    vcoreIspModuleId_t        modId)
{
    int32_t  status = FVID2_SOK;
    uint32_t instId;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[modId])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if (VCORE_ISP_MODULE_NSF3 == modId)
    {
        instId = 0U;
    }
    else
    {
        instId = 1U;
    }

    if (NULL != nsf3Cfg)
    {
        BspUtils_memcpy(
            nsf3Cfg,
            &hObj->nsf3Cfg[instId],
            sizeof (*nsf3Cfg));
    }
    else
    {
        status = FVID2_EBADARGS;
    }

    return (status);
}

/* IPIPEIF Set Config */
int32_t IspIpipeifSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIpipeifCtrl_t      *cfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cmd;
    Ptr      arg = NULL;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_IPIPEIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == cfg) ||
        ((VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT == cfg->module) &&
         (NULL == cfg->lutCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG == cfg->module) &&
         (NULL == cfg->compDecompCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG == cfg->module) &&
         (NULL == cfg->satCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG == cfg->module) &&
         (NULL == cfg->wdrCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        switch (cfg->module)
        {
            /* Case is to update the Companding and Decompanding lut tables */
            case VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT;
                arg = (Ptr) cfg->lutCfg;
                break;

            /* Case is to update the Companding and Decompanding
             * configuration */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG;
                arg = (Ptr) cfg->compDecompCfg;
                break;

            /* Case is to update the saturation configuration */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG;
                arg = (Ptr) cfg->satCfg;
                break;

            /* Case is to update the WDR Merge configuration */
            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                cmd = VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG;
                arg = (Ptr) cfg->wdrCfg;
                break;

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    if (FVID2_SOK == status)
    {
        status = VpsHal_issipipeifControl(
            hObj->halHandles[VCORE_ISP_MODULE_IPIPEIF],
            cmd,
            arg,
            NULL);
    }

    if (FVID2_SOK == status)
    {
        switch (cfg->module)
        {
            /* Case is to update the Companding and Decompanding
             * configuration */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                BspUtils_memcpy(
                    &hObj->ipipeifCfg.compDecompCfg,
                    cfg->compDecompCfg,
                    sizeof (vpsissIpipeifDeCompandInsts_t));
                break;

            /* Case is to update the saturation configuration */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                BspUtils_memcpy(
                    &hObj->ipipeifCfg.satCfg,
                    cfg->satCfg,
                    sizeof (vpsissIpipeifSaturaInsts_t));
                break;

            /* Case is to update the WDR Merge configuration */
            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                BspUtils_memcpy(
                    &hObj->ipipeifCfg.wdrCfg,
                    cfg->wdrCfg,
                    sizeof (vpsissIpipeifWdrCfg_t));
                break;
        }
    }

    return (status);
}

/* IPIPEIF Get Config */
int32_t IspIpipeifGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissIpipeifCtrl_t      *cfg)
{
    int32_t status = FVID2_SOK;

    /* Check for the null pointers */
    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_IPIPEIF])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    /* Check for the null pointers */
    if ((NULL == cfg) ||
        ((VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT == cfg->module) &&
         (NULL == cfg->lutCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG == cfg->module) &&
         (NULL == cfg->compDecompCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG == cfg->module) &&
         (NULL == cfg->satCfg)) ||
        ((VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG == cfg->module) &&
         (NULL == cfg->wdrCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        switch (cfg->module)
        {
            /* Case is to get Companding/Decompanding parameters of IPIPEIF */
            case VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG:
                BspUtils_memcpy(
                    cfg->compDecompCfg,
                    &hObj->ipipeifCfg.compDecompCfg,
                    sizeof (vpsissIpipeifDeCompandInsts_t));
                break;

            /* Case is to get Saturation parameters of IPIPEIF */
            case VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG:
                BspUtils_memcpy(
                    cfg->satCfg,
                    &hObj->ipipeifCfg.satCfg,
                    sizeof (vpsissIpipeifSaturaInsts_t));
                break;

            case VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG:
                BspUtils_memcpy(
                    cfg->wdrCfg,
                    &hObj->ipipeifCfg.wdrCfg,
                    sizeof (vpsissIpipeifWdrCfg_t));
                break;

            /* Case is to get LUT Parameters of IPIPE */
            case VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT:
            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
    }

    return (status);
}

/* GLBCE Set Config */
int32_t IspGlbceSetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissGlbceCtrl_t        *glbceCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_GLBCE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == glbceCtrl) ||
        ((VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module) &&
         (NULL == glbceCtrl->glbceCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module) &&
         (NULL == glbceCtrl->fwdPrcptCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module) &&
         (NULL == glbceCtrl->revPrcptCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module) &&
         (NULL == glbceCtrl->wdrCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hObj->halHandles[VCORE_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_GLBCECFG,
                glbceCtrl->glbceCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->glbceCfg.glbceCfg,
                    glbceCtrl->glbceCfg,
                    sizeof (hObj->glbceCfg.glbceCfg));
            }
        }
        else if (VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hObj->halHandles[VCORE_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_FWDPRCPT_CFG,
                glbceCtrl->fwdPrcptCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->glbceCfg.fwdPrcptCfg,
                    glbceCtrl->fwdPrcptCfg,
                    sizeof (hObj->glbceCfg.fwdPrcptCfg));
            }
        }
        else if (VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hObj->halHandles[VCORE_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_REVPRCPT_CFG,
                glbceCtrl->revPrcptCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->glbceCfg.revPrcptCfg,
                    glbceCtrl->revPrcptCfg,
                    sizeof (hObj->glbceCfg.revPrcptCfg));
            }
        }
        else if (VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module)
        {
            status = VpsHal_issglbceControl(
                hObj->halHandles[VCORE_ISP_MODULE_GLBCE],
                ISSHAL_IOCTL_GLBCE_SET_WDRCFG,
                glbceCtrl->wdrCfg,
                NULL);

            if (FVID2_SOK == status)
            {
                BspUtils_memcpy(
                    &hObj->glbceCfg.wdrCfg,
                    glbceCtrl->wdrCfg,
                    sizeof (hObj->glbceCfg.wdrCfg));
            }
        }
        else
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

/* GLBCE Get Config */
int32_t IspGlbceGetConfig(
    vpscoreissM2mHandleObj_t *hObj,
    vpsissGlbceCtrl_t        *glbceCtrl)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsIssCoreTrace, (NULL != hObj));

    if (FALSE == hObj->isModuleReq[VCORE_ISP_MODULE_GLBCE])
    {
        status = FVID2_EUNSUPPORTED_OPS;
    }

    if ((NULL == glbceCtrl) ||
        ((VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module) &&
         (NULL == glbceCtrl->glbceCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module) &&
         (NULL == glbceCtrl->fwdPrcptCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module) &&
         (NULL == glbceCtrl->revPrcptCfg)) ||
        ((VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module) &&
         (NULL == glbceCtrl->wdrCfg)))
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        if (VPS_ISS_GLBCE_MODULE_GLBCE == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->glbceCfg,
                &hObj->glbceCfg.glbceCfg,
                sizeof (hObj->glbceCfg.glbceCfg));
        }
        else if (VPS_ISS_GLBCE_MODULE_FWD_PERCEPT == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->fwdPrcptCfg,
                &hObj->glbceCfg.fwdPrcptCfg,
                sizeof (hObj->glbceCfg.fwdPrcptCfg));
        }
        else if (VPS_ISS_GLBCE_MODULE_REV_PERCEPT == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->revPrcptCfg,
                &hObj->glbceCfg.revPrcptCfg,
                sizeof (hObj->glbceCfg.revPrcptCfg));
        }
        else if (VPS_ISS_GLBCE_MODULE_WDR == glbceCtrl->module)
        {
            BspUtils_memcpy(
                glbceCtrl->wdrCfg,
                &hObj->glbceCfg.wdrCfg,
                sizeof (hObj->glbceCfg.wdrCfg));
        }
        else
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

