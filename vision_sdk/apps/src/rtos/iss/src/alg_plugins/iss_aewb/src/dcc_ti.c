/******************************************************************************
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
******************************************************************************/

#include "../issAewb1Link_priv.h"
#include <TI_dcc.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include "dcc_defaults.h"

/* Used for dividing analog gain in the algorithms output, while
   selecting appropriate parameters */
#define ALGORITHMSLINK_AEWB_DCC_AG_DIVISOR          (1000U)

static vpsissIpipeRgb2RgbConfig_t* Dcc_switch_rgb2rgb_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj,
    UInt32 inst);

static vpsissIpipe3DLutConfig_t* Dcc_switch_3d_lut_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj);
static vpsissCnfConfig_t* Dcc_switch_cnf_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj);
static vpsissNsf3Config_t* Dcc_switch_nsf3_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj);


static Void dccInitDefaults(dcc_parser_output_params_t *pDccOutPrms);
static Void dccResetFlags(dcc_parser_output_params_t *pDccOutPrms);

Int32 Dcc_Create(AlgorithmLink_IssAewbObj *pAewbObj,
            System_LinkMemAllocInfo *pMemAllocInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 size = 0U, cnt;
    UInt8 *memPtr = NULL, *tempPtr = NULL;
    Dcc_Object *pDccObj = NULL;
    dcc_parser_output_params_t *pDccOutPrms = NULL;
    vpsissIpipe3DLutConfig_t *pLut3DCfg = NULL;

    UTILS_assert(NULL != pAewbObj);

    pDccObj = &pAewbObj->dccObj;
    pDccOutPrms = &pDccObj->dccOutPrms;

    memset(pDccObj, 0, sizeof(Dcc_Object));

    /* Allocate the buffer for the input */
    if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
    {
        pDccObj->dccInBuf = Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            ALGORITHM_AEWB1_DCC_IN_BUF_SIZE,
            256U);
    }
    else
    {
        pDccObj->dccInBuf =
            (Ptr)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                ALGORITHM_AEWB1_DCC_IN_BUF_SIZE,
                256U);
    }
    UTILS_assert(NULL != pDccObj->dccInBuf);
    memset(pDccObj->dccInBuf, 0x0, ALGORITHM_AEWB1_DCC_IN_BUF_SIZE);

    /* Allocate the buffer for output modules */
    size += DCC_RGB2RGB1_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipeRgb2RgbConfig_t);
    size += DCC_RGB2RGB2_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipeRgb2RgbConfig_t);
    size += DCC_NSF3V_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissNsf3Config_t);
    size += DCC_CNF_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissCnfConfig_t);
    size += ((DCC_3D_LUT_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipe3DLutConfig_t)) +
        (192U*4U*4U*DCC_3D_LUT_MAX_PHOTO_SPACE_INST));

    size += DCC_MESH_LDC_TABLE_SIZE;

    /* Table for ISIF 2D LSC Gain and Offset */
    size += DCC_ISIF_2D_LSC_GAIN_TABLE_SIZE * 2U;

    if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
    {
        memPtr = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                size,
                32);
    }
    else
    {
        memPtr =
            (UInt8*)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                size,
                32);
    }
    UTILS_assert(NULL != memPtr);
    memset(memPtr, 0x0, size);

    pDccObj->dccOutBuf = (Ptr)memPtr;
    pDccObj->dccOutBufSize = size;

    pDccOutPrms->ldcTable = memPtr;
    memPtr += DCC_MESH_LDC_TABLE_SIZE;

    pDccOutPrms->isif2DLscGainTbl = memPtr;
    memPtr += DCC_ISIF_2D_LSC_GAIN_TABLE_SIZE;
    pDccOutPrms->isif2DLscOffsetTbl = memPtr;
    memPtr += DCC_ISIF_2D_LSC_GAIN_TABLE_SIZE;

    /* Assign allocated pointers to members of the dcc_output object */
    pDccOutPrms->ipipeNumRgb2Rgb1Inst = 0U;
    pDccOutPrms->ipipeRgb2Rgb1Cfg = (vpsissIpipeRgb2RgbConfig_t*)memPtr;
    memPtr +=  DCC_RGB2RGB1_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipeRgb2RgbConfig_t);

    pDccOutPrms->ipipeNumRgb2Rgb2Inst = 0U;
    pDccOutPrms->ipipeRgb2Rgb2Cfg = (vpsissIpipeRgb2RgbConfig_t*)memPtr;
    memPtr +=  DCC_RGB2RGB2_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipeRgb2RgbConfig_t);

    pDccOutPrms->numNsf3vInst = 0U;
    pDccOutPrms->nsf3vCfg = (vpsissNsf3Config_t*)memPtr;
    memPtr +=  DCC_NSF3V_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissNsf3Config_t);

    pDccOutPrms->numCnfInst = 0U;
    pDccOutPrms->cnfCfg = (vpsissCnfConfig_t*)memPtr;
    memPtr +=  DCC_CNF_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissCnfConfig_t);

    pDccOutPrms->num3dLutInst = 0U;
    pDccOutPrms->ipipe3dLutCfg = (vpsissIpipe3DLutConfig_t*)memPtr;

    /* Initialize LUT Table pointers */
    tempPtr = memPtr;
    tempPtr += sizeof(vpsissIpipe3DLutConfig_t) *
                    DCC_3D_LUT_MAX_PHOTO_SPACE_INST;

    pLut3DCfg = pDccOutPrms->ipipe3dLutCfg;
    for (cnt = 0U; cnt < DCC_3D_LUT_MAX_PHOTO_SPACE_INST; cnt ++)
    {
        pLut3DCfg->b0Addr = (UInt32 *)tempPtr;
        tempPtr += 192U*4U;

        pLut3DCfg->b1Addr = (UInt32 *)tempPtr;
        tempPtr += 192U*4U;

        pLut3DCfg->b2Addr = (UInt32 *)tempPtr;
        tempPtr += 192U*4U;

        pLut3DCfg->b3Addr = (UInt32 *)tempPtr;
        tempPtr += 192U*4U;

        pLut3DCfg ++;
    }

    memPtr +=  ((DCC_3D_LUT_MAX_PHOTO_SPACE_INST *
        sizeof(vpsissIpipe3DLutConfig_t)) +
        (192U*4U*4U*DCC_3D_LUT_MAX_PHOTO_SPACE_INST));

    dccInitDefaults(pDccOutPrms);

    for (cnt = 0U; cnt < ISS_AEWB1_LINK_MAX_CH; cnt ++)
    {
        pAewbObj->chObj[cnt].prevRgb2Rgb1Idx = -1;
        pAewbObj->chObj[cnt].prevRgb2Rgb2Idx = -1;
        pAewbObj->chObj[cnt].prevCnfIdx = -1;
        pAewbObj->chObj[cnt].prevNsf3vIdx = -1;
        pAewbObj->chObj[cnt].prev3dLutIdx = -1;

        pAewbObj->chObj[cnt].analogGain = 0U;
        pAewbObj->chObj[cnt].expTime = 0U;
        pAewbObj->chObj[cnt].colorTemp = 0U;
    }

    return (status);
}

Void Dcc_delete(AlgorithmLink_IssAewbObj *pAewbObj,
        System_LinkMemAllocInfo *pMemAllocInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Dcc_Object *pDccObj = NULL;

    UTILS_assert(NULL != pAewbObj);

    pDccObj = &pAewbObj->dccObj;

    /* Free up the memory allocated to input buffer */
    if (NULL != pDccObj->dccInBuf)
    {
        if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
        {
            status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pDccObj->dccInBuf,
                    ALGORITHM_AEWB1_DCC_IN_BUF_SIZE);
            UTILS_assert(0 == status);
        }
    }

    /* Free up the memory allocated to output buffer */
    if (NULL != pDccObj->dccOutBuf)
    {
        if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
        {
            status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pDccObj->dccOutBuf,
                    pDccObj->dccOutBufSize);
            UTILS_assert(0 == status);
        }
    }

    memset(pDccObj, 0, sizeof(Dcc_Object));
}


Void Dcc_update_params(
    AlgorithmLink_IssAewbObj *pAlgObj,
    IssIspConfigurationParameters *pIspCfg,
    UInt32 chNum)
{
    Dcc_Object *pDccObj = NULL;
    dcc_parser_output_params_t *pDccOutPrms = NULL;

    UTILS_assert(NULL != pAlgObj);
    UTILS_assert(NULL != pIspCfg);

    pDccObj = &pAlgObj->dccObj;
    pDccOutPrms = &pDccObj->dccOutPrms;

    memset(pIspCfg, 0, sizeof(IssIspConfigurationParameters));

    pIspCfg->channelId = chNum;
    if ((0U != pDccOutPrms->ipipeNumRgb2Rgb1Inst) &&
        (NULL != pDccOutPrms->ipipeRgb2Rgb1Cfg))
    {
        pIspCfg->rgb2rgb1Cfg = Dcc_switch_rgb2rgb_photospace(
                pAlgObj,
                &pAlgObj->chObj[chNum],
                0U);
    }
    if ((0U != pDccOutPrms->ipipeNumRgb2Rgb2Inst) &&
        (NULL != pDccOutPrms->ipipeRgb2Rgb2Cfg))
    {
        pIspCfg->rgb2rgb2Cfg = Dcc_switch_rgb2rgb_photospace(
                pAlgObj,
                &pAlgObj->chObj[chNum],
                1U);
    }
    if ((0U != pDccOutPrms->num3dLutInst) &&
        (NULL != pDccOutPrms->ipipe3dLutCfg))
    {
        pIspCfg->lut3d = Dcc_switch_3d_lut_photospace(
                pAlgObj, &pAlgObj->chObj[chNum]);

        /* 3D Lut is already converted to bank format */
        pIspCfg->ipipe3dLutFormat = ISS_ISP_IPIPE_3D_LUT_FORMAT_BANK;
    }
    if ((0U != pDccOutPrms->numCnfInst) &&
        (NULL != pDccOutPrms->cnfCfg))
    {
        pIspCfg->cnfCfg = Dcc_switch_cnf_photospace(
                pAlgObj, &pAlgObj->chObj[chNum]);
    }
    if ((0U != pDccOutPrms->numNsf3vInst) &&
        (NULL != pDccOutPrms->nsf3vCfg))
    {
        pIspCfg->nsf3vCfg = Dcc_switch_nsf3_photospace(
                pAlgObj, &pAlgObj->chObj[chNum]);
    }
}

Int32 Dcc_parse_and_save_params(
    AlgorithmLink_IssAewbObj *pAlgObj,
    IssIspConfigurationParameters *pIspCfg,
    IssM2mSimcopLink_ConfigParams *pSimcopCfg,
    UInt32 dccBufSize)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Dcc_Object *pDccObj = NULL;
    dcc_parser_output_params_t *pDccOutPrms = NULL;

    UTILS_assert(NULL != pAlgObj);
    UTILS_assert(NULL != pIspCfg);
    UTILS_assert(NULL != pSimcopCfg);

    pDccObj = &pAlgObj->dccObj;
    pDccOutPrms = &pDccObj->dccOutPrms;

    /* Reset all Flags */
    dccResetFlags(pDccOutPrms);

    pDccObj->dccInPrms.dcc_buf = (UInt8 *)pDccObj->dccInBuf;
    pDccObj->dccInPrms.dcc_buf_size = dccBufSize;
    pDccObj->dccInPrms.color_temparature = pAlgObj->aewbOut[0].colorTemp;
    pDccObj->dccInPrms.exposure_time = pAlgObj->aewbOut[0].expTime;
    pDccObj->dccInPrms.analog_gain = pAlgObj->aewbOut[0].analogGain;
    pDccObj->dccInPrms.cameraId = pAlgObj->algLinkCreateParams.dccCameraId;

    status = dcc_update(&pDccObj->dccInPrms, &pDccObj->dccOutPrms);

    if (0 == status)
    {
        /* Update the ISP configuration based on the parsed parameters */
        if (TRUE == pDccOutPrms->useDpcOtfCfg)
        {
            pIspCfg->dpcOtfCfg = &pDccOutPrms->ipipeDpcOtfCfg;
        }
        if (TRUE == pDccOutPrms->useNf1Cfg)
        {
            pIspCfg->nf1Cfg = &pDccOutPrms->ipipeNf1Cfg;
        }
        if (TRUE == pDccOutPrms->useNf2Cfg)
        {
            pIspCfg->nf2Cfg = &pDccOutPrms->ipipeNf2Cfg;
        }
        if (TRUE == pDccOutPrms->useCfaCfg)
        {
            pIspCfg->cfaCfg = &pDccOutPrms->ipipeCfaCfg;
        }
        if (TRUE == pDccOutPrms->useGicCfg)
        {
            pIspCfg->gicCfg = &pDccOutPrms->ipipeGicCfg;
        }
        if (TRUE == pDccOutPrms->useGammaCfg)
        {
            pIspCfg->gammaCfg = &pDccOutPrms->ipipeGammaCfg;
        }
        if (TRUE == pDccOutPrms->useRgb2YuvCfg)
        {
            pIspCfg->rgb2yuvCfg = &pDccOutPrms->ipipeRgb2YuvCfg;
        }
        if (TRUE == pDccOutPrms->useYeeCfg)
        {
            pIspCfg->eeCfg = &pDccOutPrms->ipipeYeeCfg;
        }
        if (TRUE == pDccOutPrms->useBlackClampCfg)
        {
            pIspCfg->isifBlkClampCfg = &pDccOutPrms->blkClampCfg;
        }
        if (TRUE == pDccOutPrms->useBlackClampCfg)
        {
            pIspCfg->isifBlkClampCfg = &pDccOutPrms->blkClampCfg;
        }
        if (TRUE == pDccOutPrms->useIpipeifWdrCfg)
        {
            pIspCfg->ipipeifWdrCfg = &pDccOutPrms->ipipeifWdrCfg;
        }
        if ((TRUE == pDccOutPrms->useIpipeifVpDeComp) ||
            (TRUE == pDccOutPrms->useIpipeifWdrCompCfg))
        {
            pIspCfg->ipipeifCmpDecmpCfg = &pDccOutPrms->ipipeifCmpDecmpCfg;
            pIspCfg->ipipeifLut = &pDccOutPrms->ipipeifLutCfg;
        }

        if (TRUE == pDccOutPrms->useGlbceCfg)
        {
            pIspCfg->glbceCfg = &pDccOutPrms->glbceCfg;
        }

        if (TRUE == pDccOutPrms->useAewbCfg)
        {
            pIspCfg->aewbCfg = &pDccOutPrms->aewbCfg;
        }

        if (TRUE == pDccOutPrms->useMeshLdcCfg)
        {
            pSimcopCfg->ldcConfig = &pDccOutPrms->ldcCfg;
        }

        if (TRUE == pDccOutPrms->useIsif2DLscCfg)
        {
            pIspCfg->isif2DLscCfg = &pDccOutPrms->isif2DLscCfg;
        }
    }

    return (status);
}

Int32 Dcc_init_isp_config(
    AlgorithmLink_IssAewbObj *pAlgObj,
    IssIspConfigurationParameters *pIspCfg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    Dcc_Object *pDccObj = NULL;
    dcc_parser_output_params_t *pDccOutPrms = NULL;

    UTILS_assert(NULL != pAlgObj);
    UTILS_assert(NULL != pIspCfg);

    pDccObj = &pAlgObj->dccObj;
    pDccOutPrms = &pDccObj->dccOutPrms;

    if (NULL != pIspCfg->nsf3vCfg)
    {
        vpsissNsf3Config_t *nsf3Cfg = pDccOutPrms->nsf3vCfg;

        for (cnt = 0U; cnt < DCC_NSF3V_MAX_PHOTO_SPACE_INST; cnt ++)
        {
            UTILS_assert(NULL != nsf3Cfg);

            memcpy(nsf3Cfg, pIspCfg->nsf3vCfg, sizeof(vpsissNsf3Config_t));
            nsf3Cfg ++;
        }
    }

    if (NULL != pIspCfg->cnfCfg)
    {
        vpsissCnfConfig_t *cnfCfg = pDccOutPrms->cnfCfg;

        for (cnt = 0U; cnt < DCC_CNF_MAX_PHOTO_SPACE_INST; cnt ++)
        {
            UTILS_assert(NULL != cnfCfg);

            memcpy(cnfCfg, pIspCfg->cnfCfg, sizeof(vpsissCnfConfig_t));
            cnfCfg ++;
        }
    }

    if (NULL != pIspCfg->isifBlkClampCfg)
    {
        memcpy(&pDccOutPrms->blkClampCfg, pIspCfg->isifBlkClampCfg,
            sizeof(vpsissIsifBlackClampConfig_t));
    }

    if (NULL != pIspCfg->ipipeifCmpDecmpCfg)
    {
        memcpy(&pDccOutPrms->ipipeifCmpDecmpCfg, pIspCfg->ipipeifCmpDecmpCfg,
            sizeof(vpsissIpipeifDeCompandInsts_t));
    }

    if (NULL != pIspCfg->ipipeifWdrCfg)
    {
        memcpy(&pDccOutPrms->ipipeifWdrCfg, pIspCfg->ipipeifWdrCfg,
            sizeof(vpsissIpipeifWdrCfg_t));
    }

    if (NULL != pIspCfg->nf2Cfg)
    {
        memcpy(&pDccOutPrms->ipipeNf2Cfg, pIspCfg->nf2Cfg,
            sizeof(vpsissIpipeNf2Config_t));
    }
    if (NULL != pIspCfg->nf1Cfg)
    {
        memcpy(&pDccOutPrms->ipipeNf1Cfg, pIspCfg->nf1Cfg,
            sizeof(vpsissIpipeNf2Config_t));
    }
    /*if (NULL != pIspCfg->lscCfg)
    {
        memcpy(&pDccOutPrms->lscCfg, pIspCfg->lscCfg,
            sizeof(vpsissIpipeLscConfig_t));
    }*/
    if (NULL != pIspCfg->gicCfg)
    {
        memcpy(&pDccOutPrms->ipipeGicCfg, pIspCfg->gicCfg,
            sizeof(vpsissIpipeGicConfig_t));
    }
    if (NULL != pIspCfg->eeCfg)
    {
        memcpy(&pDccOutPrms->ipipeYeeCfg, pIspCfg->eeCfg,
            sizeof(vpsissIpipeEeConfig_t));
    }
    /*if (NULL != pIspCfg->dpcLutCfg)
    {
        memcpy(&pDccOutPrms->dpcLutCfg, pIspCfg->dpcLutCfg,
            sizeof(vpsissIpipeDpcLutConfig_t));
    }*/
    if (NULL != pIspCfg->dpcOtfCfg)
    {
        memcpy(&pDccOutPrms->ipipeDpcOtfCfg, pIspCfg->dpcOtfCfg,
            sizeof(vpsissIpipeDpcOtfConfig_t));
    }
    if (NULL != pIspCfg->cfaCfg)
    {
        memcpy(&pDccOutPrms->ipipeCfaCfg, pIspCfg->cfaCfg,
            sizeof(vpsissIpipeCfaConfig_t));
    }
    /*if (NULL != pIspCfg->yuvPhsCfg)
    {
        memcpy(&pDccOutPrms->yuvPhsCfg, pIspCfg->yuvPhsCfg,
            sizeof(vpsissIpipeYuvPhsConfig_t));
    }*/

    if (NULL != pIspCfg->aewbCfg)
    {
        memcpy(&pDccOutPrms->aewbCfg, pIspCfg->aewbCfg,
            sizeof(vpsissH3aAewbConfig_t));
    }

    if (NULL != pIspCfg->glbceWdrCfg)
    {
        memcpy(&pDccOutPrms->glbceWdrCfg, pIspCfg->glbceWdrCfg,
            sizeof(vpsissGlbceWdrConfig_t));
    }
    if (NULL != pIspCfg->glbceRevPerCfg)
    {
        memcpy(&pDccOutPrms->glbceRevPerCfg, pIspCfg->glbceRevPerCfg,
            sizeof(vpsissGlbcePerceptConfig_t));
    }
    if (NULL != pIspCfg->glbceFwdPerCfg)
    {
        memcpy(&pDccOutPrms->glbceFwdPerCfg, pIspCfg->glbceFwdPerCfg,
            sizeof(vpsissGlbcePerceptConfig_t));
    }
    if (NULL != pIspCfg->glbceCfg)
    {
        memcpy(&pDccOutPrms->glbceCfg, pIspCfg->glbceCfg,
            sizeof(vpsissGlbceConfig_t));
    }

    return (status);
}


static vpsissIpipeRgb2RgbConfig_t* Dcc_switch_rgb2rgb_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj,
    UInt32 inst)
{
    UInt32 i, j, found;
    UInt32 phPrms[DCC_MAX_PHOTO_SPACE];
    dcc_parser_output_params_t *pDccOutPrms;
    vpsissIpipeRgb2RgbConfig_t *rgbOutCfg = NULL, *rgbCfg = NULL;

    /* Assuming Number of instances are same for RGB2RGB1 and RGB2RGB2 */
    phPrms[DCC_PHOTOSPACE_AG] = pChObj->analogGain/
                                ALGORITHMSLINK_AEWB_DCC_AG_DIVISOR;
    phPrms[DCC_PHOTOSPACE_CT] = pChObj->colorTemp;
    phPrms[DCC_PHOTOSPACE_ET] = pChObj->expTime;

    pDccOutPrms = &pAlgObj->dccObj.dccOutPrms;

    if (0 == inst)
    {
        rgbCfg = pDccOutPrms->ipipeRgb2Rgb1Cfg;
        for (i = 0U; i < pDccOutPrms->ipipeNumRgb2Rgb1Inst; i ++)
        {
            found = 0U;
            for (j = 0U; j < DCC_MAX_PHOTO_SPACE; j ++)
            {
                if ((phPrms[j] >= pDccOutPrms->phPrmsRgb2Rgb1[i][j].min) &&
                    (phPrms[j] <= pDccOutPrms->phPrmsRgb2Rgb1[i][j].max))
                {
                    found |= (1U << j);
                }
            }

            if (0x7 == found)
            {
                rgbOutCfg = rgbCfg;
                break;
            }
            rgbCfg ++;
        }

        if (i == pChObj->prevRgb2Rgb1Idx)
        {
            /* No Need to change parameter */
            rgbOutCfg = NULL;
        }
        else
        {
            if (NULL != rgbOutCfg)
            {
                /* Parameter change */
                pChObj->prevRgb2Rgb1Idx = i;
            }
        }

    }
    else
    {
        rgbCfg = pDccOutPrms->ipipeRgb2Rgb2Cfg;
        for (i = 0U; i < pDccOutPrms->ipipeNumRgb2Rgb2Inst; i ++)
        {
            found = 0U;
            for (j = 0U; j < DCC_MAX_PHOTO_SPACE; j ++)
            {
                if ((phPrms[j] >= pDccOutPrms->phPrmsRgb2Rgb2[i][j].min) &&
                    (phPrms[j] <= pDccOutPrms->phPrmsRgb2Rgb2[i][j].max))
                {
                    found |= (1U << j);
                }
            }

            if (0x7 == found)
            {
                rgbOutCfg = rgbCfg;
                break;
            }

            rgbCfg ++;
        }

        if (i == pChObj->prevRgb2Rgb2Idx)
        {
            /* No Need to change parameter */
            rgbOutCfg = NULL;
        }
        else
        {
            if (NULL != rgbOutCfg)
            {
                /* Parameter change */
                pChObj->prevRgb2Rgb2Idx = i;
            }
        }
    }

    return rgbOutCfg;
}

static vpsissIpipe3DLutConfig_t* Dcc_switch_3d_lut_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj)
{
    UInt32 i, j, found;
    UInt32 phPrms[DCC_MAX_PHOTO_SPACE];
    dcc_parser_output_params_t *pDccOutPrms;
    vpsissIpipe3DLutConfig_t *p3dLutCfg = NULL, *p3dLut = NULL;

    /* Assuming Number of instances are same for RGB2RGB1 and RGB2RGB2 */
    phPrms[DCC_PHOTOSPACE_AG] = pChObj->analogGain /
                                ALGORITHMSLINK_AEWB_DCC_AG_DIVISOR;
    phPrms[DCC_PHOTOSPACE_CT] = pChObj->colorTemp;
    phPrms[DCC_PHOTOSPACE_ET] = pChObj->expTime;

    pDccOutPrms = &pAlgObj->dccObj.dccOutPrms;

    p3dLut = pDccOutPrms->ipipe3dLutCfg;
    for (i = 0U; i < pDccOutPrms->num3dLutInst; i ++)
    {
        found = 0U;
        for (j = 0U; j < DCC_MAX_PHOTO_SPACE; j ++)
        {
            if ((phPrms[j] >= pDccOutPrms->phPrms3dLut[i][j].min) &&
                (phPrms[j] <= pDccOutPrms->phPrms3dLut[i][j].max))
            {
                found |= (1U << j);
            }
        }

        if (0x7U == found)
        {
            p3dLutCfg = p3dLut;
            break;
        }
        p3dLut ++;
    }

    if (i == pChObj->prev3dLutIdx)
    {
        /* No Need to change parameter */
        p3dLutCfg = NULL;
    }
    else
    {
        if (NULL != p3dLutCfg)
        {
            /* Parameter change */
            pChObj->prev3dLutIdx = i;
        }
    }

    return p3dLutCfg;
}

static vpsissCnfConfig_t* Dcc_switch_cnf_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj)
{
    UInt32 i, j, found;
    UInt32 phPrms[DCC_MAX_PHOTO_SPACE];
    dcc_parser_output_params_t *pDccOutPrms;
    vpsissCnfConfig_t *pCnfCfg = NULL, *pTempCnfCfg = NULL;

    /* Assuming Number of instances are same for RGB2RGB1 and RGB2RGB2 */
    phPrms[DCC_PHOTOSPACE_AG] = pChObj->analogGain /
                                ALGORITHMSLINK_AEWB_DCC_AG_DIVISOR;
    phPrms[DCC_PHOTOSPACE_CT] = pChObj->colorTemp;
    phPrms[DCC_PHOTOSPACE_ET] = pChObj->expTime;

    pDccOutPrms = &pAlgObj->dccObj.dccOutPrms;

    pTempCnfCfg = pDccOutPrms->cnfCfg;
    for (i = 0U; i < pDccOutPrms->numCnfInst; i ++)
    {
        found = 0U;
        for (j = 0U; j < DCC_MAX_PHOTO_SPACE; j ++)
        {
            if ((phPrms[j] >= pDccOutPrms->phPrmsCnf[i][j].min) &&
                (phPrms[j] <= pDccOutPrms->phPrmsCnf[i][j].max))
            {
                found |= (1U << j);
            }
        }

        if (0x7U == found)
        {
            pCnfCfg = pTempCnfCfg;
            break;
        }
        pTempCnfCfg ++;
    }

    if (i == pChObj->prevCnfIdx)
    {
        /* No Need to change parameter */
        pCnfCfg = NULL;
    }
    else
    {
        if (NULL != pCnfCfg)
        {
            /* Parameter change */
            pChObj->prevCnfIdx = i;
        }
    }

    return pCnfCfg;
}

static vpsissNsf3Config_t* Dcc_switch_nsf3_photospace(
    AlgorithmLink_IssAewbObj *pAlgObj,
    AlgorithmLnk_IssAewbChObj *pChObj)
{
    UInt32 i, j, found;
    UInt32 phPrms[DCC_MAX_PHOTO_SPACE];
    dcc_parser_output_params_t *pDccOutPrms;
    vpsissNsf3Config_t *pNsf3Cfg = NULL, *pTempNsf3Cfg = NULL;

    /* Assuming Number of instances are same for RGB2RGB1 and RGB2RGB2 */
    phPrms[DCC_PHOTOSPACE_AG] = pChObj->analogGain /
                                    ALGORITHMSLINK_AEWB_DCC_AG_DIVISOR;
    phPrms[DCC_PHOTOSPACE_CT] = pChObj->colorTemp;
    phPrms[DCC_PHOTOSPACE_ET] = pChObj->expTime;

    pDccOutPrms = &pAlgObj->dccObj.dccOutPrms;

    pTempNsf3Cfg = pDccOutPrms->nsf3vCfg;
    for (i = 0U; i < pDccOutPrms->numNsf3vInst; i ++)
    {
        found = 0U;
        for (j = 0U; j < DCC_MAX_PHOTO_SPACE; j ++)
        {
            if ((phPrms[j] >= pDccOutPrms->phPrmsNsf3v[i][j].min) &&
                (phPrms[j] <= pDccOutPrms->phPrmsNsf3v[i][j].max))
            {
                found |= (1U << j);
            }
        }

        if (0x7U == found)
        {
            pNsf3Cfg = pTempNsf3Cfg;
            break;
        }
        pTempNsf3Cfg ++;
    }

    if (i == pChObj->prevNsf3vIdx)
    {
        /* No Need to change parameter */
        pNsf3Cfg = NULL;
    }
    else
    {
        if (NULL != pNsf3Cfg)
        {
            /* Parameter change */
            pChObj->prevNsf3vIdx = i;
        }
    }

    return pNsf3Cfg;
}

Void dccInitDefaults(dcc_parser_output_params_t *pDccOutPrms)
{
    UInt32 cnt;
    vpsissNsf3Config_t *nsf3vCfg = NULL;
    vpsissCnfConfig_t *cnfCfg = NULL;

    dccResetFlags(pDccOutPrms);

    /* Initialize WDR Parameters */
    memcpy(&pDccOutPrms->ipipeifWdrCfg, &gIssDccDefWdrCfg,
           sizeof(vpsissIpipeifWdrCfg_t));

    /* Initialize GLBCE Config */
    memcpy(&pDccOutPrms->glbceCfg, &gIssDccDefGlbceCfg,
        sizeof(vpsissGlbceConfig_t));

    /* Initialize AEWB Configuration */
    memcpy(&pDccOutPrms->aewbCfg, &gIssDccAewbDefCfg,
        sizeof(vpsissH3aAewbConfig_t));

    /* Initialize NSF3 Configuration */
    nsf3vCfg = pDccOutPrms->nsf3vCfg;
    for (cnt = 0U; cnt < DCC_NSF3V_MAX_PHOTO_SPACE_INST; cnt ++)
    {
        UTILS_assert(NULL != nsf3vCfg);

        memcpy(nsf3vCfg, &gIssDccNsf3DefCfg, sizeof(vpsissNsf3Config_t));

        nsf3vCfg ++;
    }

    /* Initialize CNF Configuration */
    cnfCfg = pDccOutPrms->cnfCfg;
    for (cnt = 0U; cnt < DCC_CNF_MAX_PHOTO_SPACE_INST; cnt ++)
    {
        UTILS_assert(NULL != cnfCfg);

        memcpy(&cnfCfg->nsf3Cfg, &gIssDccNsf3DefCfg,
            sizeof(vpsissNsf3Config_t));

        cnfCfg ++;
    }
}

Void dccResetFlags(dcc_parser_output_params_t *pDccOutPrms)
{
    /* Setup the Update flag to FALSE for all modules */
    pDccOutPrms->useDpcOtfCfg = FALSE;
    pDccOutPrms->useNf1Cfg = FALSE;
    pDccOutPrms->useNf2Cfg = FALSE;
    pDccOutPrms->useCfaCfg = FALSE;
    pDccOutPrms->useGicCfg = FALSE;
    pDccOutPrms->useGammaCfg = FALSE;
    pDccOutPrms->useRgb2YuvCfg = FALSE;
    pDccOutPrms->useYeeCfg = FALSE;
    pDccOutPrms->useBlackClampCfg = FALSE;
    pDccOutPrms->useAwbCalbCfg = FALSE;
    pDccOutPrms->useIpipeifVpDeComp = FALSE;
    pDccOutPrms->useIpipeifWdrCompCfg = FALSE;
    pDccOutPrms->useIpipeifWdrCfg = FALSE;
    pDccOutPrms->useRgb2Rgb1Cfg = FALSE;
    pDccOutPrms->useRgb2Rgb2Cfg = FALSE;
    pDccOutPrms->useNsf3vCfg = FALSE;
    pDccOutPrms->useCnfCfg = FALSE;
    pDccOutPrms->use3dLutCfg = FALSE;
    pDccOutPrms->useGlbceWdrCfg = FALSE;
    pDccOutPrms->useGlbceRevPerCfg = FALSE;
    pDccOutPrms->useGlbceFwdPerCfg = FALSE;
    pDccOutPrms->useGlbceCfg = FALSE;
    pDccOutPrms->useAewbCfg = FALSE;
    pDccOutPrms->ipipeifCmpDecmpCfg.modInstId =
        (vpsissIpipeifCompDecompInst_t)0U;
    pDccOutPrms->useMeshLdcCfg = FALSE;
    pDccOutPrms->useIsif2DLscCfg = NULL;
}
