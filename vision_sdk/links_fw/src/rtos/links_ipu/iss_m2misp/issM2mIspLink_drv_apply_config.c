/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

 /**
 *******************************************************************************
 * \file issM2mIspLink_drv_aply_config.c
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issM2mIspLink_priv.h"

/**
 *******************************************************************************
 *
 * \brief Applies ISP configuration
 *
 *  In this function, configuration recorded in the link object is taken and
 *  control calls are performed to driver, to apply the configuration.
 *  Control calls are done conditionally, if that configuration needs to be
 *  applied, as indicated by applyCfg variable associated with each config
 *  structure. Note that the method in which applyCfg is set is outside
 *  purview of this function. After applying configuration applyCfg flag is
 *  made FALSE
 *
 * \param  pObj          [IN]
 * \param  passId        [IN]
 * \param  chId          [IN]
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_drvApplyRszConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;
    IssM2mIspLink_OperatingMode operatingMode;

    pChObj = &pObj->chObj[chId];
    pPassCfg = &pChObj->passCfg[passId];
    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_RSZ] == (UInt32)TRUE)
    {
        pChObj->rszCtrl.module = VPS_ISS_RSZ_MODULE_RSZCFG;
        pChObj->rszCtrl.rszCfg = &pPassCfg->rszCfg;

        pPassCfg->rszCfg.instCfg[0].enable =
            (UInt32)enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A];
        pPassCfg->rszCfg.instCfg[1].enable =
            (UInt32)enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B];

        if(((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
           (passId == (UInt32)ISSM2MISP_LINK_FIRST_PASS))
        {
            pPassCfg->rszCfg.instCfg[0].enable = TRUE;
            pPassCfg->rszCfg.instCfg[1].enable = FALSE;
        }

#ifdef ISS_ENABLE_DEBUG_TAPS
        if ((pChObj->outputTapModule != ISSM2MISP_LINK_ISP_TAP_RESIZER_OUTPUT) &&
            (pChObj->outputTapModule != ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT))
        {
            if((((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
                (passId == ISSM2MISP_LINK_SECOND_PASS)) ||
                (ISSM2MISP_LINK_OPMODE_1PASS_WDR == operatingMode))
            {
                /* Bypassing resizer output */
                pPassCfg->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_BYPASS;
                pPassCfg->rszCfg.instCfg[0].outFmt.pitch[0] =
                    pPassCfg->rszCfg.instCfg[0].outFmt.width * 2;
            }
        }
        else
        {
            if((((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
                (passId == ISSM2MISP_LINK_SECOND_PASS)) ||
                (ISSM2MISP_LINK_OPMODE_1PASS_WDR == operatingMode))
            {
                /* Enabling Resizer,
                   only these two fields were modified, so updating
                   only these two fields */
                pPassCfg->rszCfg.inCfg.opMode = VPS_ISS_RSZ_OP_MODE_RESIZING;
                pPassCfg->rszCfg.instCfg[0].outFmt.pitch[0] =
                    pObj->linkInfo.queInfo
                    [ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A].chInfo[chId].
                    pitch[0];
            }
        }
#endif

        status = Fvid2_control(
            pPassCfg->drvHandle,
            VPS_ISS_RSZ_IOCTL_SET_CONFIG,
            &pChObj->rszCtrl,
            NULL);
        UTILS_assert(status == FVID2_SOK);
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyCnfConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_CNF] == (UInt32)TRUE)
    {
        if(pIspConfigParams->cnfCfg != NULL)
        {
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_CNF_IOCTL_SET_CONFIG,
                pIspConfigParams->cnfCfg,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyGlbceConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_GLBCE] == (UInt32)TRUE)
    {
        if(pIspConfigParams->glbceCfg != NULL)
        {
            pChObj->glbceCtrl.module    = VPS_ISS_GLBCE_MODULE_GLBCE;
            pChObj->glbceCtrl.glbceCfg  = pIspConfigParams->glbceCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
                &pChObj->glbceCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->glbceFwdPerCfg != NULL)
        {
            pChObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_FWD_PERCEPT;
            pChObj->glbceCtrl.fwdPrcptCfg = pIspConfigParams->glbceFwdPerCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
                &pChObj->glbceCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->glbceRevPerCfg != NULL)
        {
            pChObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_REV_PERCEPT;
            pChObj->glbceCtrl.revPrcptCfg = pIspConfigParams->glbceRevPerCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
                &pChObj->glbceCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->glbceWdrCfg != NULL)
        {
            pChObj->glbceCtrl.module      = VPS_ISS_GLBCE_MODULE_WDR;
            pChObj->glbceCtrl.wdrCfg      = pIspConfigParams->glbceWdrCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_GLBCE_IOCTL_SET_CONFIG,
                &pChObj->glbceCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyH3aConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_H3A] == (UInt32)TRUE)
    {
        if(pIspConfigParams->aewbCfg != NULL)
        {
            pChObj->h3aCtrl.module    = VPS_ISS_H3A_MODULE_AEWB;
            pChObj->h3aCtrl.aewbCfg  = pIspConfigParams->aewbCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_H3A_IOCTL_SET_CONFIG,
                &pChObj->h3aCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->afCfg != NULL)
        {
            pChObj->h3aCtrl.module    = VPS_ISS_H3A_MODULE_AF;
            pChObj->h3aCtrl.afCfg  = pIspConfigParams->afCfg;

            status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_H3A_IOCTL_SET_CONFIG,
                    &pChObj->h3aCtrl,
                    NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }
    return status;
}

Int32 IssM2mIspLink_drvApplyIpipeConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;
    IssM2mIspLink_OperatingMode operatingMode;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];
    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;
    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPE] == (UInt32)TRUE)
    {
        if(pIspConfigParams->ipipeInputCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_INPUT;
            pChObj->ipipeCtrl.inCfg = pIspConfigParams->ipipeInputCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->yuvPhsCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_YUV444_YUV422;
            pChObj->ipipeCtrl.yuvPhsCfg = pIspConfigParams->yuvPhsCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->rgb2rgb1Cfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
            pChObj->ipipeCtrl.rgb2RgbCfg = pIspConfigParams->rgb2rgb1Cfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
            pPassCfg->rgb2rgb1 = *pIspConfigParams->rgb2rgb1Cfg;
        }

        if(pIspConfigParams->rgb2rgb2Cfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_RGB2RGB2;
            pChObj->ipipeCtrl.rgb2RgbCfg = pIspConfigParams->rgb2rgb2Cfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
            pPassCfg->rgb2rgb2 = *pIspConfigParams->rgb2rgb2Cfg;
        }

        if(pIspConfigParams->rgb2yuvCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_RGB2YUV;
            pChObj->ipipeCtrl.rgb2YuvCfg = pIspConfigParams->rgb2yuvCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        /* White balance is applied in IPIPE for all modes except for
           two pass wdr modes */
        if (FALSE == IssM2mIspLink_isWdrMode(operatingMode))
        {
            /* apply 2A WB config */
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
            pChObj->ipipeCtrl.wbCfg = &pPassCfg->ipipeWbCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);
            UTILS_assert(status == FVID2_SOK);
        }

        /* Apply RGB2 RGB Gains only in second pass for two pass wdr mode,
           or in all modes except for two pass wdr modes */
        if ((ISSM2MISP_LINK_SECOND_PASS == passId) ||
            (FALSE == IssM2mIspLink_isWdrMode(operatingMode)))
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_RGB2RGB1;
            pChObj->ipipeCtrl.rgb2RgbCfg = &pPassCfg->rgb2rgb1;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);

            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_RGB2RGB2;
            pChObj->ipipeCtrl.rgb2RgbCfg = &pPassCfg->rgb2rgb2;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->wbCfg != NULL)
        {
            /* override with user defined one's if specified */
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_WB;
            pChObj->ipipeCtrl.wbCfg = pIspConfigParams->wbCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->cfaCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_CFA;
            pChObj->ipipeCtrl.cfaCfg = pIspConfigParams->cfaCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
        if(pIspConfigParams->dpcOtfCfg != NULL)
        {
            pChObj->ipipeCtrl.module  = VPS_ISS_IPIPE_MODULE_DPC_OTF;
            pChObj->ipipeCtrl.dpcOtf  = pIspConfigParams->dpcOtfCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
        if(pIspConfigParams->dpcLutCfg != NULL)
        {
            pChObj->ipipeCtrl.module  = VPS_ISS_IPIPE_MODULE_DPC_LUT;
            pChObj->ipipeCtrl.dpcLut  = pIspConfigParams->dpcLutCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);

        }
        if(pIspConfigParams->gammaCfg != NULL)
        {
            vpsissIpipeGammaConfig_t gammaCfgTemp;
            UInt32 gammaLUTRedTemp[2*512];
            UInt32 gammaLUTGreenTemp[2*512];
            UInt32 gammaLUTBlueTemp[2*512];

            memcpy(&gammaCfgTemp,
                   pIspConfigParams->gammaCfg,
                   sizeof(vpsissIpipeGammaConfig_t));
            gammaCfgTemp.lutRed   = gammaLUTRedTemp;
            gammaCfgTemp.lutGreen = gammaLUTGreenTemp;
            gammaCfgTemp.lutBlue  = gammaLUTBlueTemp;

            /*
             * Format conversion from user specific manner to HW required manner
             * Performed into temporary arrays/structures which are owned by the link
             */
            pChObj->lutFmtCnvt.moduleId = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
            pChObj->lutFmtCnvt.gammaLutIn  = pIspConfigParams->gammaCfg->lutRed;
            pChObj->lutFmtCnvt.gammaLutOut = gammaCfgTemp.lutRed;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
                &pChObj->lutFmtCnvt,
                NULL);
            UTILS_assert(status == FVID2_SOK);

            pChObj->lutFmtCnvt.gammaLutIn =
                pIspConfigParams->gammaCfg->lutGreen;
            pChObj->lutFmtCnvt.gammaLutOut = gammaCfgTemp.lutGreen;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
                &pChObj->lutFmtCnvt,
                NULL);
            UTILS_assert(status == FVID2_SOK);

            pChObj->lutFmtCnvt.gammaLutIn = pIspConfigParams->gammaCfg->lutBlue;
            pChObj->lutFmtCnvt.gammaLutOut = gammaCfgTemp.lutBlue;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
                &pChObj->lutFmtCnvt,
                NULL);
            UTILS_assert(status == FVID2_SOK);

            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION;
            pChObj->ipipeCtrl.gammaCfg = &gammaCfgTemp;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->lut3d != NULL)
        {
            if (ISS_ISP_IPIPE_3D_LUT_FORMAT_RGB ==
                pIspConfigParams->ipipe3dLutFormat)
            {
                /* This format requires conversion */
                vpsissIpipe3DLutConfig_t lut3dTemp;
                UInt32 lutBankAddrTemp[4U][192U];

                pChObj->lutFmtCnvt.moduleId = VPS_ISS_IPIPE_MODULE_3D_LUT;
                pChObj->lutFmtCnvt.lut3DRed = pIspConfigParams->lut3d->b0Addr;
                pChObj->lutFmtCnvt.lut3DBlue = pIspConfigParams->lut3d->b1Addr;
                pChObj->lutFmtCnvt.lut3DGreen = pIspConfigParams->lut3d->b2Addr;
                pChObj->lutFmtCnvt.out3DB0Addr = lutBankAddrTemp[0U];
                pChObj->lutFmtCnvt.out3DB1Addr = lutBankAddrTemp[1U];
                pChObj->lutFmtCnvt.out3DB2Addr = lutBankAddrTemp[2U];
                pChObj->lutFmtCnvt.out3DB3Addr = lutBankAddrTemp[3U];
                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
                    &pChObj->lutFmtCnvt,
                    NULL);
                UTILS_assert(status == FVID2_SOK);

                memcpy(&lut3dTemp,
                        pIspConfigParams->lut3d,
                        sizeof(vpsissIpipe3DLutConfig_t));
                lut3dTemp.b0Addr = lutBankAddrTemp[0U];
                lut3dTemp.b1Addr = lutBankAddrTemp[1U];
                lut3dTemp.b2Addr = lutBankAddrTemp[2U];
                lut3dTemp.b3Addr = lutBankAddrTemp[3U];

                pChObj->ipipeCtrl.module   = VPS_ISS_IPIPE_MODULE_3D_LUT;
                pChObj->ipipeCtrl.colorConvert3DLutCfg = &lut3dTemp;
            }
            else    /* The other format is Bank format, where there is
                       no conversion required */
            {
                pChObj->ipipeCtrl.module   = VPS_ISS_IPIPE_MODULE_3D_LUT;
                pChObj->ipipeCtrl.colorConvert3DLutCfg =
                    pIspConfigParams->lut3d;
            }

            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->eeCfg != NULL)
        {
            vpsissIpipeEeConfig_t       eeCfgTemp;
            UInt32 yee_tableTemp[1024];

            memcpy(&eeCfgTemp,
                    pIspConfigParams->eeCfg,
                    sizeof(vpsissIpipeEeConfig_t));
            eeCfgTemp.lutAddr = yee_tableTemp;

            pChObj->lutFmtCnvt.moduleId  = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
            pChObj->lutFmtCnvt.yeeLutIn  = pIspConfigParams->eeCfg->lutAddr;
            pChObj->lutFmtCnvt.yeeLutOut = yee_tableTemp;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_UPDATE_LUT_FMT,
                &pChObj->lutFmtCnvt,
                NULL);
            UTILS_assert(status == FVID2_SOK);

            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER;
            pChObj->ipipeCtrl.eeCfg  = &eeCfgTemp;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->gicCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_GIC;
            pChObj->ipipeCtrl.gicCfg  = pIspConfigParams->gicCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->lscCfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_LSC;
            pChObj->ipipeCtrl.lscCfg  = pIspConfigParams->lscCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->nf1Cfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF1;
            pChObj->ipipeCtrl.nf1Cfg  = pIspConfigParams->nf1Cfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }

        if(pIspConfigParams->nf2Cfg != NULL)
        {
            pChObj->ipipeCtrl.module = VPS_ISS_IPIPE_MODULE_NF2;
            pChObj->ipipeCtrl.nf2Cfg  = pIspConfigParams->nf2Cfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPE_IOCTL_SET_CONFIG,
                &pChObj->ipipeCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyIpipeifConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;
    IssM2mIspLink_OperatingMode operatingMode;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];
    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_IPIPEIF] == (UInt32)TRUE)
    {
        if(pIspConfigParams->ipipeifLut != NULL)
        {
            pChObj->ipipeifCtrl.module  =
                (vpsissIpipeifModule_t)VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT;
            pChObj->ipipeifCtrl.pLutCfg = pIspConfigParams->ipipeifLut;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                &pChObj->ipipeifCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
        if(pPassCfg->ispPrms.enableWdrMerge==TRUE)
        {
            if(pIspConfigParams->ipipeifWdrCfg != NULL)
            {
                pChObj->ipipeifCtrl.module  =
                    (vpsissIpipeifModule_t)VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
                pChObj->ipipeifCtrl.pWdrCfg = pIspConfigParams->ipipeifWdrCfg;

                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                    &pChObj->ipipeifCtrl,
                    NULL);

                UTILS_assert(status == FVID2_SOK);

                memcpy(&pPassCfg->wdrCfg, pIspConfigParams->ipipeifWdrCfg,
                    sizeof(pPassCfg->wdrCfg));
            }

        }

        pChObj->ipipeifCtrl.module  =
            (vpsissIpipeifModule_t)VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG;
        pChObj->ipipeifCtrl.pSatCfg = &pPassCfg->satCfg;
        status = Fvid2_control(
            pPassCfg->drvHandle,
            VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
            &pChObj->ipipeifCtrl,
            NULL);
        UTILS_assert(status == FVID2_SOK);

        if (((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) ||
            (ISSM2MISP_LINK_OPMODE_1PASS_WDR == operatingMode))
        {
            if(pIspConfigParams->ipipeifCmpDecmpCfg != NULL)
            {
                pChObj->ipipeifCtrl.module = (vpsissIpipeifModule_t)
                    VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
                pChObj->ipipeifCtrl.pCompDecompCfg =
                    pIspConfigParams->ipipeifCmpDecmpCfg;
                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                    &pChObj->ipipeifCtrl,
                    NULL);

                UTILS_assert(status == FVID2_SOK);

                if ((ISSM2MISP_LINK_SECOND_PASS == passId) ||
                    ((ISSM2MISP_LINK_FIRST_PASS == passId) &&
                     (ISSM2MISP_LINK_OPMODE_1PASS_WDR == operatingMode)))
                {
                    /* Copy Default Companding Configuration */
                    pPassCfg->compDecompCfg =
                        *pIspConfigParams->ipipeifCmpDecmpCfg;
                }
            }

            if (ISSM2MISP_LINK_OPMODE_1PASS_WDR == operatingMode)
            {
                /* Apply Companding Configuration,
                   This changes only Companding block configuration,
                   so calling only for the second pass */
                pChObj->ipipeifCtrl.module  =
                    VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
                pChObj->ipipeifCtrl.pCompDecompCfg = &pPassCfg->compDecompCfg;
                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                    &pChObj->ipipeifCtrl,
                    NULL);

                UTILS_assert(status == FVID2_SOK);
            }
            /* Apply White balance gains in the IPIPEIF only for 20bit wdr
               mode and only for the second pass */
            if (ISSM2MISP_LINK_SECOND_PASS == passId)
            {
                pChObj->ipipeifCtrl.module  =
                    (vpsissIpipeifModule_t)VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG;
                pChObj->ipipeifCtrl.pWdrCfg = &pPassCfg->wdrCfg;

                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                    &pChObj->ipipeifCtrl,
                    NULL);

                UTILS_assert(status == FVID2_SOK);

                /* Apply Companding Configuration,
                   This changes only Companding block configuration,
                   so calling only for the second pass */
                pChObj->ipipeifCtrl.module  =
                    VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG;
                pChObj->ipipeifCtrl.pCompDecompCfg = &pPassCfg->compDecompCfg;
                status = Fvid2_control(
                    pPassCfg->drvHandle,
                    VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG,
                    &pChObj->ipipeifCtrl,
                    NULL);

                UTILS_assert(status == FVID2_SOK);
            }
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyNsf3vConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_NSF3] == (UInt32)TRUE)
    {
        if(pIspConfigParams->nsf3vCfg != NULL)
        {
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_NSF3_IOCTL_SET_CONFIG,
                pIspConfigParams->nsf3vCfg,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyIsifConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_PassObj *pPassCfg;
    IssM2mIspLink_OperatingMode operatingMode;
    Int32 tempS32, dcOffset;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    pPassCfg = &pChObj->passCfg[passId];

    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    if (pPassCfg->openPrms.isModuleReq[VPS_ISS_ISP_MODULE_ISIF] == (UInt32)TRUE)
    {
        /* apply AWB results at ISIF */
        pChObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_WB;
        pChObj->isifCtrl.wbCfg  = &pPassCfg->isifWbCfg;

        if (((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)) &&
            (pChObj->isifCtrl.wbCfg->gain > 0) )
        {
            if(ISSM2MISP_LINK_FIRST_PASS == passId)
            {
                /* Do not apply digital gain to short channel */
                pChObj->isifCtrl.wbCfg->gain[0] =
                pChObj->isifCtrl.wbCfg->gain[1] =
                pChObj->isifCtrl.wbCfg->gain[2] =
                pChObj->isifCtrl.wbCfg->gain[3] = 0x200U;
            }
        }

        status = Fvid2_control(
            pPassCfg->drvHandle,
            VPS_ISS_ISIF_IOCTL_SET_CONFIG,
            &pChObj->isifCtrl,
            NULL);

        UTILS_assert(status == FVID2_SOK);


        /* apply DC Offset at ISIF */

        if(pIspConfigParams->isifWbCfg != NULL)
        {
            pChObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_WB;
            pChObj->isifCtrl.wbCfg  = pIspConfigParams->isifWbCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_ISIF_IOCTL_SET_CONFIG,
                &pChObj->isifCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);

            memcpy(&pPassCfg->isifWbCfg,
                   pIspConfigParams->isifWbCfg,
                   sizeof(vpsissIsifGainOfstConfig_t));
        }

        if(pIspConfigParams->isifBlkClampCfg != NULL)
        {

            /* Copy Black Level Config */
            if ((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode))
            {
                if (ISSM2MISP_LINK_SECOND_PASS == passId)
                {
                    memcpy(&pPassCfg->isifBlkClampCfg,
                           pIspConfigParams->isifBlkClampCfg,
                           sizeof(vpsissIsifBlackClampConfig_t));
                }
                else
                {
                    /* Recalculate the dcOffset */
                    tempS32 =
                      (Int32)(pIspConfigParams->isifBlkClampCfg->dcOffset * - ((Int32)1));
                    dcOffset = (Int32) ((Int32)tempS32/(Int32)pChObj->expRatio);
                    dcOffset = (Int32)(dcOffset * - ((Int32)1));

                    pPassCfg->isifBlkClampCfg.dcOffset = dcOffset;
                }
            }
            else
            {
                memcpy(&pPassCfg->isifBlkClampCfg,
                       pIspConfigParams->isifBlkClampCfg,
                       sizeof(vpsissIsifBlackClampConfig_t));
            }
        }

        /* apply DC Offset at ISIF */
        pChObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_BLACK_CLAMP;
        pChObj->isifCtrl.blkClampCfg  = &pPassCfg->isifBlkClampCfg;
        status = Fvid2_control(
            pPassCfg->drvHandle,
            VPS_ISS_ISIF_IOCTL_SET_CONFIG,
            &pChObj->isifCtrl,
            NULL);
        UTILS_assert(status == FVID2_SOK);

        if(pIspConfigParams->isif2DLscCfg != NULL)
        {
            pChObj->isifCtrl.module = VPS_ISS_ISIF_MODULE_2D_LSC;
            pChObj->isifCtrl.lscCfg  = pIspConfigParams->isif2DLscCfg;
            status = Fvid2_control(
                pPassCfg->drvHandle,
                VPS_ISS_ISIF_IOCTL_SET_CONFIG,
                &pChObj->isifCtrl,
                NULL);

            UTILS_assert(status == FVID2_SOK);
        }
    }

    return status;
}

Int32 IssM2mIspLink_drvApplyConfig(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssIspConfigurationParameters *pIspConfigParams;
    IssM2mIspLink_ChannelObject *pChObj;
    IssM2mIspLink_OperatingMode operatingMode;

    pChObj = &pObj->chObj[chId];
    pIspConfigParams = &pChObj->ispCfgParams;
    operatingMode = pObj->createArgs.channelParams[chId].operatingMode;

    IssM2mIspLink_drvApplyRszConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyCnfConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyGlbceConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyIpipeConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyIpipeifConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyNsf3vConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyIsifConfig(pObj, chId, passId, enableOut);
    IssM2mIspLink_drvApplyH3aConfig(pObj, chId, passId, enableOut);

    if ((passId == ISSM2MISP_LINK_FIRST_PASS) &&
        ((Bool)TRUE == IssM2mIspLink_isWdrMode(operatingMode)))
    {
        /* Dont set config structure to NULL since it will be needed in
         * second pass
         */
    }
    else
    {
        /* set config structure's to NULL
         * so that the parameters are not set again unless they
         * are modified
         */
        memset(pIspConfigParams, 0, sizeof(IssIspConfigurationParameters));
    }

    return status;
}

Int32 IssM2mIspLink_drvSaveContext(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssM2mIspLink_ChannelObject *pChObj;
    Utils_DmaCopy1D dmaPrm;

    pChObj = &pObj->chObj[chId];

    if ((NULL != pChObj->pGlbceStatsBuffer) &&
        (0U != pObj->glbceStatsInfo.addr))
    {
        dmaPrm.destAddr = pChObj->pGlbceStatsBuffer;
        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
           MISRAC_WAIVER:
           GLBCE start address typecast to Pointer since dma params expects
           address in pointer format. */
        dmaPrm.srcAddr = (Ptr)pObj->glbceStatsInfo.addr;
        dmaPrm.length = pObj->glbceStatsInfo.size;

        status = Utils_dmaCopy1D(&pObj->saveCtxDmaObj, &dmaPrm);
        UTILS_assert(status == EDMA3_DRV_SOK);
    }

    return (status);
}

Int32 IssM2mIspLink_drvRestoreContext(
    IssM2mIspLink_Obj * pObj,
    UInt32 chId,
    UInt32 passId,
    Bool enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    IssM2mIspLink_ChannelObject *pChObj;
    Utils_DmaCopy1D dmaPrm;

    pChObj = &pObj->chObj[chId];

    if ((NULL != pChObj->pGlbceStatsBuffer) &&
        (0U != pObj->glbceStatsInfo.addr))
    {
        dmaPrm.srcAddr = pChObj->pGlbceStatsBuffer;
        /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
           MISRAC_WAIVER:
           GLBCE start address typecast to Pointer since dma params expects
           address in pointer format. */
        dmaPrm.destAddr = (Ptr)pObj->glbceStatsInfo.addr;
        dmaPrm.length = pObj->glbceStatsInfo.size;

        status = Utils_dmaCopy1D(&pObj->saveCtxDmaObj, &dmaPrm);
        UTILS_assert(status == EDMA3_DRV_SOK);
    }

    return (status);
}


