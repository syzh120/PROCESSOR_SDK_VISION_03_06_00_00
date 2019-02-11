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
 *  \file isshal_ipipe.c
 *
 *  \brief File containing the ISS IPIPE HAL init, deinit and other common
 *  functions.
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
#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issipipe.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Bit Mask of all modules which are part of a given clock */
#define ISS_HAL_IPIPE_G0_CLK_MASK   (ISSHAL_IPIPE_MODULE_BOXCAR)

#define ISS_HAL_IPIPE_G1_CLK_MASK   (ISSHAL_IPIPE_MODULE_DPC_LUT |        \
                                     ISSHAL_IPIPE_MODULE_DPC_OTF |        \
                                     ISSHAL_IPIPE_MODULE_NOISE_FILTER_1 | \
                                     ISSHAL_IPIPE_MODULE_NOISE_FILTER_2 | \
                                     ISSHAL_IPIPE_MODULE_GIC |            \
                                     ISSHAL_IPIPE_MODULE_WB |             \
                                     ISSHAL_IPIPE_MODULE_CGS |            \
                                     ISSHAL_IPIPE_MODULE_HST)

#define ISS_HAL_IPIPE_G2_CLK_MASK   (ISSHAL_IPIPE_MODULE_CFA |        \
                                     ISSHAL_IPIPE_MODULE_GAMMA |      \
                                     ISSHAL_IPIPE_MODULE_RGB_RGB_1 |  \
                                     ISSHAL_IPIPE_MODULE_RGB_RGB_2 |  \
                                     ISSHAL_IPIPE_MODULE_3D_LUT |     \
                                     ISSHAL_IPIPE_MODULE_RGB_TO_YUV | \
                                     ISSHAL_IPIPE_MODULE_GBCE |       \
                                     ISSHAL_IPIPE_MODULE_BSC)

#define ISS_HAL_IPIPE_G3_CLK_MASK   (ISSHAL_IPIPE_MODULE_YEE | \
                                     ISSHAL_IPIPE_MODULE_CAR)

typedef enum isshalipipeGckClk
{
    ISSHAL_IPIPE_GCK_CLK_G0 = 0x0,
    /**< The on/off selection of the clk_pix_g0 which is used for the
     *   IPIPE processing of "Boxcar".*/
    ISSHAL_IPIPE_GCK_CLK_G1 = 0x1,
    /**< The on/off selection of the clk_pix_g1 which is used for the
     *   IPIPE processes of "DefectCorrection" to "WhiteBalance", and
     *   "Histogram(RAW input)" */
    ISSHAL_IPIPE_GCK_CLK_G2 = 0x2,
    /**< The on/off selection of the clk_pix_g2 which is use for the
     *   IPIPE processes of CFA to "422", "Histogram(YCbCrinput)", and
     *   "Boundary Signal Calculator" */
    ISSHAL_IPIPE_GCK_CLK_G3 = 0x3,
    /**< The on/off selection of the clk_pix_g3 which is use for the
     *   IPIPE processes of EE and "CAR" */
    ISSHAL_IPIPE_GCK_CLK_MAX = 0x4,
    /**< Should be the last enum */
    ISSHAL_IPIPE_GCK_CLK_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed, will always be contained in int */
} isshalipipeGckClk_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalipipeInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
    uint32_t gammaLutRedAddr;
    uint32_t gammaLutGreenAddr;
    uint32_t gammaLutBlueAddr;
    uint32_t lut3DBank0Addr;
    uint32_t lut3DBank1Addr;
    uint32_t lut3DBank2Addr;
    uint32_t lut3DBank3Addr;
    uint32_t yeeLutAddr;
    uint32_t yeeLutSize;
    uint32_t modClkMask[ISSHAL_IPIPE_GCK_CLK_MAX];
} isshalipipeInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Function for validating configuration
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
static void IpipeEnableSubModuleClk(
    isshalipipeInstObj_t *instObj,
    isshalipipeModuleId_t moduleId,
    uint32_t              enable);

static int32_t IpipeSetSrcConfig(
    const isshalipipeInstObj_t   *instObj,
    const isshalipipeSrcConfig_t *srcCfg);

static int32_t IpipeSetWbConfig(
    isshalipipeInstObj_t        *instObj,
    const isshalipipeWbConfig_t *wbCfg);

static int32_t IpipeSetCfaConfig(
    isshalipipeInstObj_t         *instObj,
    const isshalipipeCfaConfig_t *cfaCfg);

static int32_t IpipeSetRgb2RgbConfig(
    isshalipipeInstObj_t             *instObj,
    const isshalipipeRgb2RgbConfig_t *rgb2rgbCfg,
    isshalipipeModuleId_t             moduleId);

static int32_t IpipeSetRgb2YuvConfig(
    isshalipipeInstObj_t             *instObj,
    const isshalipipeRgb2YuvConfig_t *rgb2yuvCfg);

static int32_t IpipeSetChromaDsConfig(
    const isshalipipeInstObj_t      *instObj,
    const isshalipipeYuvPhsConfig_t *yuvPhsCfg);

static int32_t IpipeSetDpcOtfConfig(
    const isshalipipeInstObj_t      *instObj,
    const vpsissIpipeDpcOtfConfig_t *cfg);

static int32_t IpipeSetDpcLutConfig(
    const isshalipipeInstObj_t      *instObj,
    const vpsissIpipeDpcLutConfig_t *cfg);

static int32_t IpipeSetGammaConfig(
    isshalipipeInstObj_t           *instObj,
    const vpsissIpipeGammaConfig_t *cfg);

static int32_t IpipeSet3DLutConfig(
    isshalipipeInstObj_t           *instObj,
    const vpsissIpipe3DLutConfig_t *cfg);

static int32_t IpipeSetEeConfig(
    isshalipipeInstObj_t        *instObj,
    const vpsissIpipeEeConfig_t *cfg);

static int32_t IpipeSetGicConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeGicConfig_t *cfg);

static int32_t IpipeSetLscConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeLscConfig_t *cfg);

static int32_t IpipeSetNfConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeNf2Config_t *cfg,
    isshalipipeModuleId_t         moduleId);

static int32_t IpipeUpdateLut(
    const isshalipipeInstObj_t    *instObj,
    const vpsissIpipeLutFmtCnvt_t *fmtCnvt);

static int32_t IpipeEnableDisableEe(
    const isshalipipeInstObj_t  *instObj,
    const vpsissIpipeEeConfig_t *cmdArgs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalipipeInstObj_t      gIssHalIpipeInstObjs[ISSHAL_IPIPE_MAX_INST] =
{(uint32_t)FALSE};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalGlbceDefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const isshalipipeConfig_t gIssHalIpipeDefCfg =
{
    ISSHAL_IPIPE_MODULE_SRC_CFG |
    ISSHAL_IPIPE_MODULE_WB |
    ISSHAL_IPIPE_MODULE_CFA |
    ISSHAL_IPIPE_MODULE_RGB_RGB_1 |
    ISSHAL_IPIPE_MODULE_RGB_RGB_2 |
    ISSHAL_IPIPE_MODULE_RGB_TO_YUV |
    ISSHAL_IPIPE_MODULE_YUV444_YUV422,                       /* Module ID */
    /* Source Configuration */
    {
        FVID2_DF_BAYER_RGGB,
        VPS_ISS_IPIPE_DATA_PATH_RAW_YUV422,
        FVID2_CHROMA_POS_CENTERED,
        {0x0U,        0x0U,        720U, 480U},
        FALSE
    },
    /* White Balance Configuration */
    {
        {0x0U,        0x0U,        0x0U, 0x0U},
        {512U,        512U,        512U, 512U}
    },
    /* CFA Configuration */
    {
        VPS_ISS_IPIPE_CFA_MODE_2DIRAC,
        56U, 167U, 100U, 10U, 16U, 10U, 16U,
        {
            16U, 25U, 25U, 20U, 500U, 20U, 24U
        }
    },
    /* RGB2RGB 1 Configuration */
    {
        {
            {0x000001B0U, 0xFFFFFF5AU, 0xFFFFFFF6U},
            {0xFFFFFFA4U, 0x0000015FU, 0xFFFFFFFDU},
            {0xFFFFFFFDU, 0xFFFFFFA6U, 0x0000015DU}
        },
        {0U,          0U,          0U}
    },
    /* RGB2RGB 2 Configuration */
    {
        {
            {256U,        0U,          0U},
            {0U,          256U,        0U},
            {0U,          0U,          256U}
        },
        {0U,          0U,          0U}
    },
    /* RGB2YUV Configuration */
    {
        0U,                                     /* Brightness */
        16U,                                    /* Contrast */
        {
            {0x4DU,       0x96U,       0x1DU},
            {0xFD5U,      0xFABU,      0x80U},
            {0x80U,       0xF95U,      0xFEBU}
        },
        {0U,          0x80U,       0x80U}
    },
    {
        TRUE,
        FVID2_CHROMA_POS_COSITED
    },
    /* DPC OTF Config */
    {
        FALSE,
        VPS_ISS_IPIPE_DPC_OTF_METHOD_1,
        0x0U, 0x0U, 0x0U, 0x0U,
        0x0U, 0x0U, 0x0U, 0x0U,
        0x0U
    },
    /* DPC Lut based */
    {
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        0x0
    },
    /*  Gamma Correction */
    {
        VPS_ISS_IPIPE_GAMMA_TBL_ROM,
        VPS_ISS_IPIPE_GAMMA_TBL_SIZE_512,
        FALSE,
        FALSE,
        FALSE,
        NULL,
        NULL,
        NULL
    },
    {
        FALSE, NULL, NULL, NULL, NULL
    },
    {
        FALSE,
        VPS_ISS_IPIPE_EE_MERGE_METHOD_SUM,
        FALSE,
        0U,
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U, 0U},
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        NULL
    },
    {
        FALSE,
        VPS_ISS_IPIPE_GIC_ALG_TYPE_AVERAGE,
        0U,
        VPS_ISS_IPIPE_GIC_THR_SEL_GIC_REG,
        0U,
        0U,
        0U,
        0U
    },
    {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        {0U,          0U,          0U,   0U  },
        {0U,          0U,          0U,   0U  },
        0U, 0U
    },
    {
        FALSE,
        VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX,
        0U, 0U, 0U, 0U,
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        0U, 0U
    },
    {
        FALSE,
        VPS_ISS_IPIPE_NF2_GREEN_TYPE_BOX,
        0U, 0U, 0U, 0U,
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        {0U,          0U,          0U,   0U, 0U, 0U, 0U, 0U},
        0U, 0U
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issipipeInit(UInt32                         numInst,
                            const isshalipipeInstParams_t *instPrms,
                            Ptr                            arg)
{
    uint32_t instCnt;
    uint32_t cnt;
    isshalipipeInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_IPIPE_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (NULL != instPrms));
        GT_assert(VpsHalTrace,
                  (instPrms->instId < ISSHAL_IPIPE_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms->baseAddress));

        pInstObj = &gIssHalIpipeInstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt           = 0U;
            pInstObj->instId            = instPrms->instId;
            pInstObj->gammaLutRedAddr   = instPrms->gammaLutRedAddr;
            pInstObj->gammaLutGreenAddr = instPrms->gammaLutGreenAddr;
            pInstObj->gammaLutBlueAddr  = instPrms->gammaLutBlueAddr;
            pInstObj->lut3DBank0Addr    = instPrms->lut3DBank0Addr;
            pInstObj->lut3DBank1Addr    = instPrms->lut3DBank1Addr;
            pInstObj->lut3DBank2Addr    = instPrms->lut3DBank2Addr;
            pInstObj->lut3DBank3Addr    = instPrms->lut3DBank3Addr;
            pInstObj->yeeLutAddr        = instPrms->yeeLutAddr;
            pInstObj->yeeLutSize        = instPrms->yeeLutSize;

            pInstObj->baseAddress = instPrms->baseAddress;
            pInstObj->isInitDone  = (uint32_t)TRUE;

            for(cnt = 0U; cnt < ISSHAL_IPIPE_GCK_CLK_MAX; cnt++)
            {
                pInstObj->modClkMask[cnt] = 0U;
            }

            /* Enabling everything */
            IpipeEnableSubModuleClk(pInstObj, ISSHAL_IPIPE_MODULE_BOXCAR,
                                    (uint32_t) TRUE);
            IpipeEnableSubModuleClk(pInstObj, ISSHAL_IPIPE_MODULE_DPC_LUT,
                                    (uint32_t) TRUE);
            IpipeEnableSubModuleClk(pInstObj, ISSHAL_IPIPE_MODULE_CFA,
                                    (uint32_t) TRUE);
            IpipeEnableSubModuleClk(pInstObj, ISSHAL_IPIPE_MODULE_YEE,
                                    (uint32_t) TRUE);
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * ipipe number of instances. The size of this number of instances
         * is never more than ISSHAL_IPIPE_INST_MAX_ID.
         */
        instPrms++;
    }

    return (BSP_SOK);
}

int32_t VpsHal_issipipeDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalipipeInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_IPIPE_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIssHalIpipeInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == pInstObj->openCnt));

        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

VpsHal_Handle VpsHal_issipipeOpen(const isshalOpenParams_t *openPrms,
                                  Ptr                       arg)
{
    uint32_t              instCnt;
    VpsHal_Handle         handle  = NULL;
    isshalipipeInstObj_t *instObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_IPIPE_MAX_INST; instCnt++)
    {
        instObj = &(gIssHalIpipeInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == instObj->instId)
        {
            handle = (VpsHal_Handle) (instObj);

            /* Enable Module clock on first open */
            if(0 == instObj->openCnt)
            {
                /* Enable IPIPE Module at the ISS level */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK == VpsHal_issEnableModule(
                         ISSHAL_ISS_MODULE_IPIPE,
                         (UInt32) TRUE)));

                /* Enable register access clocks */
                HW_WR_REG32(instObj->baseAddress + IPIPE_GCK_MMR,
                            HW_RD_REG32(instObj->baseAddress + IPIPE_GCK_MMR) |
                            IPIPE_GCK_MMR_REG_MASK);

                /* Enabling everything */
                IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_BOXCAR,
                                        (uint32_t) TRUE);
                IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_DPC_LUT,
                                        (uint32_t) TRUE);
                IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_CFA,
                                        (uint32_t) TRUE);
                IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_YEE,
                                        (uint32_t) TRUE);

                HW_WR_REG32(instObj->baseAddress + IPIPE_YUV_INP_OFST_Y, 16U);
                HW_WR_REG32(instObj->baseAddress + IPIPE_YUV_INP_OFST_CB,
                            0x180U);
                HW_WR_REG32(instObj->baseAddress + IPIPE_YUV_INP_OFST_CR,
                            0x180U);
            }

            instObj->openCnt++;
            break;
        }
    }

    return (handle);
}

int32_t VpsHal_issipipeClose(VpsHal_Handle handle,
                             Ptr           arg)
{
    int32_t status = FVID2_EFAIL;
    isshalipipeInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalipipeInstObj_t *) handle;

    /* Decrement the open count */
    if(instObj->openCnt > 0)
    {
        instObj->openCnt--;

        if(0U == instObj->openCnt)
        {
            /* Disable register access clocks */
            HW_WR_REG32(instObj->baseAddress + IPIPE_GCK_MMR,
                        (HW_RD_REG32(instObj->baseAddress + IPIPE_GCK_MMR) &
                         ~((UInt32) IPIPE_GCK_MMR_REG_MASK)));

            /* Disable IPIPE Module at the ISS level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK == VpsHal_issEnableModule(
                     ISSHAL_ISS_MODULE_IPIPE,
                     (uint32_t) FALSE)));
        }
        status = FVID2_SOK;
    }

    return (status);
}

int32_t VpsHal_issipipeSetConfig(VpsHal_Handle              handle,
                                 const isshalipipeConfig_t *cfg,
                                 Ptr                        arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t moduleId;
    isshalipipeInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instObj = (isshalipipeInstObj_t *) handle;

    moduleId = (uint32_t) cfg->moduleId;

    while(0U < moduleId)
    {
        if((ISSHAL_IPIPE_MODULE_SRC_CFG & moduleId) ==
           ISSHAL_IPIPE_MODULE_SRC_CFG)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_SRC_CFG);
            status    = IpipeSetSrcConfig(instObj, &cfg->srcCfg);
        }
        else if((ISSHAL_IPIPE_MODULE_WB & moduleId) ==
                ISSHAL_IPIPE_MODULE_WB)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_WB);
            status    = IpipeSetWbConfig(instObj, &cfg->wbCfg);
        }
        else if((ISSHAL_IPIPE_MODULE_CFA & moduleId) ==
                ISSHAL_IPIPE_MODULE_CFA)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_CFA);
            status    = IpipeSetCfaConfig(instObj, &cfg->cfaCfg);
        }
        else if((ISSHAL_IPIPE_MODULE_RGB_RGB_1 & moduleId) ==
                ISSHAL_IPIPE_MODULE_RGB_RGB_1)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_RGB_RGB_1);
            status    = IpipeSetRgb2RgbConfig(
                instObj,
                &cfg->rgb2Rgb1,
                ISSHAL_IPIPE_MODULE_RGB_RGB_1);
        }
        else if((ISSHAL_IPIPE_MODULE_RGB_RGB_2 & moduleId) ==
                ISSHAL_IPIPE_MODULE_RGB_RGB_2)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_RGB_RGB_2);
            status    = IpipeSetRgb2RgbConfig(
                instObj,
                &cfg->rgb2Rgb2,
                ISSHAL_IPIPE_MODULE_RGB_RGB_2);
        }
        else if((ISSHAL_IPIPE_MODULE_RGB_TO_YUV & moduleId) ==
                ISSHAL_IPIPE_MODULE_RGB_TO_YUV)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_RGB_TO_YUV);
            status    = IpipeSetRgb2YuvConfig(instObj, &cfg->rgb2Yuv);
        }
        else if((ISSHAL_IPIPE_MODULE_YUV444_YUV422 & moduleId) ==
                ISSHAL_IPIPE_MODULE_YUV444_YUV422)
        {
            moduleId &= ~((UInt32) ISSHAL_IPIPE_MODULE_YUV444_YUV422);
            status    = IpipeSetChromaDsConfig(instObj, &cfg->yuvPhs);
        }
        else
        {
            /* No matching module id */
            status = FVID2_EINVALID_PARAMS;
        }

        if(status != FVID2_SOK)
        {
            break;
        }
    }

    return (status);
}

int32_t VpsHal_issipipeGetConfig(VpsHal_Handle        handle,
                                 isshalipipeConfig_t *config)
{
    return (FVID2_SOK);
}

int32_t VpsHal_issipipeControl(VpsHal_Handle handle,
                               UInt32        cmd,
                               Ptr           cmdArgs,
                               Ptr           arg)
{
    int32_t               status  = FVID2_SOK;
    isshalipipeInstObj_t *instObj = NULL;
    volatile uint32_t     regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalipipeInstObj_t *) handle;

    switch(cmd)
    {
        /* Case is to set White Balance Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_WBCFG:
            status = IpipeSetWbConfig(
                instObj,
                (const isshalipipeWbConfig_t *) cmdArgs);
            break;
        /* Case is to set CFA Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_CFACFG:
            status = IpipeSetCfaConfig(
                instObj,
                (const isshalipipeCfaConfig_t *) cmdArgs);
            break;

        case ISSHAL_IOCTL_IPIPE_EE_ENABLE_DISABLE:
            status = IpipeEnableDisableEe(
                instObj,
                (const vpsissIpipeEeConfig_t *) cmdArgs);
            break;

        /* Case is to set RGB2RGB1 Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_RGB2RGB1CFG:
            status = IpipeSetRgb2RgbConfig(
                instObj,
                (const isshalipipeRgb2RgbConfig_t *) cmdArgs,
                ISSHAL_IPIPE_MODULE_RGB_RGB_1);
            break;

        /* Case is to set RGB2RGB2 Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_RGB2RGB2CFG:
            status = IpipeSetRgb2RgbConfig(
                instObj,
                (const isshalipipeRgb2RgbConfig_t *) cmdArgs,
                ISSHAL_IPIPE_MODULE_RGB_RGB_2);
            break;

        /* Case is to set RGB2YUV Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_RGB2YUVCFG:
            status = IpipeSetRgb2YuvConfig(
                instObj,
                (const isshalipipeRgb2YuvConfig_t *) cmdArgs);
            break;

        /* Case is to set RGB2YUV Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_DPCLUTCFG:
            status = IpipeSetDpcLutConfig(
                instObj,
                (const vpsissIpipeDpcLutConfig_t *) cmdArgs);
            break;

        /* Case is to set Gamma Correction Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_GAMMACFG:
            status = IpipeSetGammaConfig(
                instObj,
                (const vpsissIpipeGammaConfig_t *) cmdArgs);
            break;

        /* Case is to set Gamma Correction Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_3D_LUTCFG:
            status = IpipeSet3DLutConfig(
                instObj,
                (const vpsissIpipe3DLutConfig_t *) cmdArgs);
            break;

        /* Case is to set Edge Enhancer Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_EECFG:
            status = IpipeSetEeConfig(
                instObj,
                (const vpsissIpipeEeConfig_t *) cmdArgs);
            break;

        /* Case is to set GIC Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_GICCFG:
            status = IpipeSetGicConfig(
                instObj,
                (const vpsissIpipeGicConfig_t *) cmdArgs);
            break;

        /* Case is to set LSC Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_LSCCFG:
            status = IpipeSetLscConfig(
                instObj,
                (const vpsissIpipeLscConfig_t *) cmdArgs);
            break;

        /* Case is to set RGB2YUV Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_DPCOTFCFG:
            status = IpipeSetDpcOtfConfig(
                instObj,
                (const vpsissIpipeDpcOtfConfig_t *) cmdArgs);
            break;

        /* Case is to set YUV Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_YUVCFG:
            status = IpipeSetChromaDsConfig(
                instObj,
                (const isshalipipeYuvPhsConfig_t *) cmdArgs);
            break;

        /* Case is to set Noise filter1 Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_NF1CFG:
            status = IpipeSetNfConfig(
                instObj,
                (const vpsissIpipeNf2Config_t *) cmdArgs,
                ISSHAL_IPIPE_MODULE_NOISE_FILTER_1);
            break;

        /* Case is to set Noise filter2 Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_NF2CFG:
            status = IpipeSetNfConfig(
                instObj,
                (const vpsissIpipeNf2Config_t *) cmdArgs,
                ISSHAL_IPIPE_MODULE_NOISE_FILTER_2);
            break;

        /* Case is to set Noise filter2 Configuration */
        case ISSHAL_IOCTL_IPIPE_SET_SRCCFG:
            status = IpipeSetSrcConfig(
                instObj,
                (const isshalipipeSrcConfig_t *)cmdArgs);
            break;
        case ISSHAL_IOCTL_IPIPE_GET_DEFAULTCFG:
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    ((isshalipipeConfig_t *) cmdArgs),
                    &gIssHalIpipeDefCfg,
                    sizeof(gIssHalIpipeDefCfg));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
        {
            isshalipipeConfig_t     *cfg =
                (isshalipipeConfig_t *) arg;
            isshalissBlankingInfo_t *blankInfo =
                (isshalissBlankingInfo_t *) cmdArgs;

            GT_assert(VpsHalTrace, (NULL != cfg));
            GT_assert(VpsHalTrace, (NULL != blankInfo));

            /* TODO: Optimize the blanking requirement based
             *       on the configuration */
            if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == blankInfo->procMode)
            {
                blankInfo->hBlank = 8U;
                blankInfo->vBlank = 12U;
            }
            else
            {
                blankInfo->hBlank = 8U;
                blankInfo->vBlank = 4U;
            }
            break;
        }
        case VPS_HAL_ISS_IOCTL_START:
        {
            issCtrlProcMode_t procMode;

            /* NULL Parameter Check */
            GT_assert(VpsHalTrace, (NULL != cmdArgs));

            procMode = *(issCtrlProcMode_t *)cmdArgs;

            /* Set the processing mode */
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_MODE);
            regVal &= ~((UInt32) IPIPE_SRC_MODE_OST_MASK);
            if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
            {
                regVal |= IPIPE_SRC_MODE_OST_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_MODE, regVal);

            HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_EN,
                        HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_EN) |
                        IPIPE_SRC_EN_MASK);

            break;
        }
        case VPS_HAL_ISS_IOCTL_STOP:
        {
            /* Disable IPIPE */
            HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_EN,
                        (HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_EN) &
                         ~((UInt32) IPIPE_SRC_EN_MASK)));
            break;
        }
        case ISSHAL_IOCTL_IPIPE_UPDATE_LUT:
        {
            status = IpipeUpdateLut(
                instObj,
                (vpsissIpipeLutFmtCnvt_t *)cmdArgs);
            break;
        }
        default:
            status = FVID2_EUNSUPPORTED_CMD;
            break;
    }

    return (status);
}

int32_t VpsHal_issipipeStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    isshalipipeInstObj_t *instObj = NULL;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalipipeInstObj_t *) handle;

    regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_MODE);
    regVal &= ~((UInt32) IPIPE_SRC_MODE_OST_MASK);
    if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
    {
        regVal |= IPIPE_SRC_MODE_OST_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_MODE, regVal);

    HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_EN,
                HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_EN) |
                IPIPE_SRC_EN_MASK);

    return (FVID2_SOK);
}

int32_t VpsHal_issipipeStop(VpsHal_Handle handle, Ptr arg)
{
    isshalipipeInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalipipeInstObj_t *) handle;

    /* Disable IPIPE */
    HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_EN,
                (HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_EN) &
                 ~((UInt32) IPIPE_SRC_EN_MASK)));

    return (FVID2_SOK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t IpipeSetSrcConfig(
    const isshalipipeInstObj_t   *instObj,
    const isshalipipeSrcConfig_t *srcCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != srcCfg));

    /* Check if size or position required to be even */
    if(!((FVID2_DF_BAYER_GRBG == srcCfg->inputDataFormat) ||
         (FVID2_DF_BAYER_RGGB == srcCfg->inputDataFormat) ||
         (FVID2_DF_BAYER_BGGR == srcCfg->inputDataFormat) ||
         (FVID2_DF_BAYER_GBRG == srcCfg->inputDataFormat) ||
         ((int32_t)TRUE == Fvid2_isDataFmtYuv422(srcCfg->inputDataFormat))))
    {
        status = FVID2_EINVALID_PARAMS;
    }
    if((ISSHAL_IPIPE_DATA_PATH_YUV422_YUV422 == srcCfg->dataPath) &&
       ((int32_t)FALSE == Fvid2_isDataFmtYuv422(srcCfg->inputDataFormat)))
    {
        status = FVID2_EINVALID_PARAMS;
    }
    /* Size of the window must not be zero */
    if((0U == srcCfg->procWin.cropWidth) ||
       (0U == srcCfg->procWin.cropHeight) ||
       (0U != (srcCfg->procWin.cropWidth & 0x1U)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        /* Select the wrt enable flag in SRC_MODE register */
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_MODE);
        regVal &= ~((UInt32) IPIPE_SRC_MODE_WRT_MASK);
        if(1 == srcCfg->wrtEnable)
        {
            regVal |= IPIPE_SRC_MODE_WRT_MASK;
        }
        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_MODE, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_FMT);
        regVal &= ~((UInt32) IPIPE_SRC_FMT_MASK);
        regVal |= (((uint32_t) srcCfg->dataPath) << IPIPE_SRC_FMT_SHIFT) &
                  IPIPE_SRC_FMT_MASK;

#ifdef NOT_YET
        /* Set the chroma position for the YUV422 input data */
        /* ISS_TODO The YUV processing i.e. FMT2 should be set to 2 for FMT3
            to be effective
            right now, no interface to support FMT config.
            The core will have to set this based on other processing modules
            required. */
        if(ISSHAL_IPIPE_DATA_PATH_YUV422_YUV422 == srcCfg->dataPath)
        {
            regVal &= ~((UInt32) IPIPE_SRC_FMT_FMT3_MASK);
            if(FVID2_CHROMA_POS_CENTERED == srcCfg->chromaPos)
            {
                regVal |= IPIPE_SRC_FMT_FMT3_MASK;
            }
        }
#endif  /* NOT_YET */

        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_FMT, regVal);

        /* Set the Bayer Format */
        if((int32_t)FALSE == Fvid2_isDataFmtYuv422(srcCfg->inputDataFormat))
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_SRC_COL);
            regVal &= ~((UInt32) (IPIPE_SRC_COL_EE_MASK |
                                  IPIPE_SRC_COL_EO_MASK |
                                  IPIPE_SRC_COL_OE_MASK |
                                  IPIPE_SRC_COL_OO_MASK));
            if(FVID2_DF_BAYER_GRBG == srcCfg->inputDataFormat)
            {
                regVal = (IPIPE_SRC_COL_EE_NEWENUM2 |
                          IPIPE_SRC_COL_EO_NEWENUM1 |
                          IPIPE_SRC_COL_OE_NEWENUM4 |
                          IPIPE_SRC_COL_OO_NEWENUM3);
            }
            else if(FVID2_DF_BAYER_RGGB == srcCfg->inputDataFormat)
            {
                regVal = (IPIPE_SRC_COL_EE_NEWENUM1 |
                          IPIPE_SRC_COL_EO_NEWENUM2 |
                          IPIPE_SRC_COL_OE_NEWENUM3 |
                          IPIPE_SRC_COL_OO_NEWENUM4);
            }
            else if(FVID2_DF_BAYER_BGGR == srcCfg->inputDataFormat)
            {
                regVal = (IPIPE_SRC_COL_EE_NEWENUM4 |
                          IPIPE_SRC_COL_EO_NEWENUM3 |
                          IPIPE_SRC_COL_OE_NEWENUM2 |
                          IPIPE_SRC_COL_OO_NEWENUM1);
            }
            else /* FVID2_DF_BAYER_GBRG input data format */
            {
                regVal = (IPIPE_SRC_COL_EE_NEWENUM3 |
                          IPIPE_SRC_COL_EO_NEWENUM4 |
                          IPIPE_SRC_COL_OE_NEWENUM1 |
                          IPIPE_SRC_COL_OO_NEWENUM2);
            }
            HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_COL, regVal);
        }

        /* Set the Window to be processed in the registers */
        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_HSZ,
                    ((srcCfg->procWin.cropWidth - 1U) &
                     IPIPE_SRC_HSZ_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_HPS,
                    ((srcCfg->procWin.cropStartX <<
                      IPIPE_SRC_HPS_VAL_SHIFT) &
                     IPIPE_SRC_HPS_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_VSZ,
                    (((UInt32) ((srcCfg->procWin.cropHeight - 1U)) <<
                      IPIPE_SRC_VSZ_VAL_SHIFT) &
                     IPIPE_SRC_VSZ_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_SRC_VPS,
                    ((srcCfg->procWin.cropStartY <<
                      IPIPE_SRC_VPS_VAL_SHIFT) &
                     IPIPE_SRC_VPS_VAL_MASK));
    }

    return (status);
}

static int32_t IpipeSetWbConfig(
    isshalipipeInstObj_t        *instObj,
    const isshalipipeWbConfig_t *wbCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == wbCfg)
    {
        status = FVID2_EBADARGS;
    }

    for(cnt = 0U; ((status == FVID2_SOK) &&
                   (cnt < ISSHAL_ISS_BAYER_COLOR_COMP_MAX)); cnt++)
    {
        if((wbCfg->offset[cnt] > (IPIPE_WB2_OFT_R_VAL_MASK >>
                                  IPIPE_WB2_OFT_R_VAL_SHIFT)) ||
           (wbCfg->gain[cnt] > (IPIPE_WB2_WGN_R_VAL_MASK >>
                                IPIPE_WB2_WGN_R_VAL_SHIFT)))
        {
            status = FVID2_EINVALID_PARAMS;
            break;
        }
    }

    if(FVID2_SOK == status)
    {
        /* Enable Module Clk */
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_WB,
            (uint32_t) TRUE);

        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_WGN_R,
                    ((wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_R] <<
                      IPIPE_WB2_WGN_R_VAL_SHIFT) &
                     IPIPE_WB2_WGN_R_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_WGN_GR,
                    ((wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_GR] <<
                      IPIPE_WB2_WGN_GR_VAL_SHIFT) &
                     IPIPE_WB2_WGN_GR_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_WGN_GB,
                    ((wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_GB] <<
                      IPIPE_WB2_WGN_GB_VAL_SHIFT) &
                     IPIPE_WB2_WGN_GB_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_WGN_B,
                    ((wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_B] <<
                      IPIPE_WB2_WGN_B_VAL_SHIFT) &
                     IPIPE_WB2_WGN_B_VAL_MASK));

        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_OFT_R,
                    ((wbCfg->offset[ISSHAL_ISS_BAYER_COLOR_COMP_R] <<
                      IPIPE_WB2_OFT_R_VAL_SHIFT) &
                     IPIPE_WB2_OFT_R_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_OFT_GR,
                    ((wbCfg->offset[ISSHAL_ISS_BAYER_COLOR_COMP_GR] <<
                      IPIPE_WB2_OFT_GR_VAL_SHIFT) &
                     IPIPE_WB2_OFT_GR_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_OFT_GB,
                    ((wbCfg->offset[ISSHAL_ISS_BAYER_COLOR_COMP_GB] <<
                      IPIPE_WB2_OFT_GB_VAL_SHIFT) &
                     IPIPE_WB2_OFT_GB_VAL_MASK));
        HW_WR_REG32(instObj->baseAddress + IPIPE_WB2_OFT_B,
                    ((wbCfg->offset[ISSHAL_ISS_BAYER_COLOR_COMP_B] <<
                      IPIPE_WB2_OFT_B_VAL_SHIFT) &
                     IPIPE_WB2_OFT_B_VAL_MASK));
    }

    return (status);
}

static int32_t IpipeSetCfaConfig(
    isshalipipeInstObj_t         *instObj,
    const isshalipipeCfaConfig_t *cfaCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == cfaCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Enable Module Clk */
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_CFA,
            (uint32_t) TRUE);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MODE);
        regVal &= ~((UInt32) IPIPE_CFA_MODE_MASK);
        regVal |= (((uint32_t) cfaCfg->cfgMode) <<
                   IPIPE_CFA_MODE_SHIFT) &
                  IPIPE_CFA_MODE_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MODE, regVal);

        /* Set the 2DIR Parameter */
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_HPF_THR);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_HPF_THR_VAL_MASK);
        regVal |= (cfaCfg->hpfThreshold <<
                   IPIPE_CFA_2DIR_HPF_THR_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_HPF_THR_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_HPF_THR, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_HPF_SLP);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_HPF_SLP_VAL_MASK);
        regVal |= (cfaCfg->hpfSlope << IPIPE_CFA_2DIR_HPF_SLP_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_HPF_SLP_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_HPF_SLP, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_MIX_THR);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_MIX_THR_VAL_MASK);
        regVal |= (cfaCfg->mixThreshold << IPIPE_CFA_2DIR_MIX_THR_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_MIX_THR_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_MIX_THR, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_MIX_SLP);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_MIX_SLP_VAL_MASK);
        regVal |= (cfaCfg->mixSlope << IPIPE_CFA_2DIR_MIX_SLP_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_MIX_SLP_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_MIX_SLP, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_DIR_TRH);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_DIR_TRH_VAL_MASK);
        regVal |= (cfaCfg->dirThreshold << IPIPE_CFA_2DIR_DIR_TRH_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_DIR_TRH_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_DIR_TRH, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_DIR_SLP);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_DIR_SLP_VAL_MASK);
        regVal |= (cfaCfg->dirSlope << IPIPE_CFA_2DIR_DIR_SLP_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_DIR_SLP_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_DIR_SLP, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_NDWT);
        regVal &= ~((UInt32) IPIPE_CFA_2DIR_NDWT_VAL_MASK);
        regVal |= (cfaCfg->nonDirWeight << IPIPE_CFA_2DIR_NDWT_VAL_SHIFT) &
                  IPIPE_CFA_2DIR_NDWT_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_2DIR_NDWT, regVal);

        /* Set the Digital Anti-aliasing parameters */
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_HUE_FRA);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_HUE_FRA_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.hueFraction <<
                   IPIPE_CFA_MONO_HUE_FRA_VAL_SHIFT) &
                  IPIPE_CFA_MONO_HUE_FRA_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_HUE_FRA, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_EDG_THR);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_EDG_THR_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.edgeThreshold <<
                   IPIPE_CFA_MONO_EDG_THR_VAL_SHIFT) &
                  IPIPE_CFA_MONO_EDG_THR_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_EDG_THR, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_THR_MIN);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_THR_MIN_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.minThreshold <<
                   IPIPE_CFA_MONO_THR_MIN_VAL_SHIFT) &
                  IPIPE_CFA_MONO_THR_MIN_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_THR_MIN, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_THR_SLP);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_THR_SLP_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.slopeThreshold <<
                   IPIPE_CFA_MONO_THR_SLP_VAL_SHIFT) &
                  IPIPE_CFA_MONO_THR_SLP_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_THR_SLP, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_SLP_MIN);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_SLP_MIN_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.slopeMin <<
                   IPIPE_CFA_MONO_SLP_MIN_VAL_SHIFT) &
                  IPIPE_CFA_MONO_SLP_MIN_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_SLP_MIN, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_SLP);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_SLP_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.slopeSlope <<
                   IPIPE_CFA_MONO_SLP_VAL_SHIFT) &
                  IPIPE_CFA_MONO_SLP_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_SLP, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_CFA_MONO_LPWT);
        regVal &= ~((UInt32) IPIPE_CFA_MONO_LPWT_VAL_MASK);
        regVal |= (cfaCfg->daaCfg.lpWeight <<
                   IPIPE_CFA_MONO_LPWT_VAL_SHIFT) &
                  IPIPE_CFA_MONO_LPWT_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_CFA_MONO_LPWT, regVal);
    }

    return (status);
}

static int32_t IpipeSetRgb2RgbConfig(
    isshalipipeInstObj_t             *instObj,
    const isshalipipeRgb2RgbConfig_t *rgb2rgbCfg,
    isshalipipeModuleId_t             moduleId)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt0, cnt1;
    uint32_t mulRegAddr;
    uint32_t ofstRegAddr;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == rgb2rgbCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if((ISSHAL_IPIPE_MODULE_RGB_RGB_1 & moduleId) ==
           ISSHAL_IPIPE_MODULE_RGB_RGB_1)
        {
            mulRegAddr  = instObj->baseAddress + IPIPE_RGB1_MUL_RR;
            ofstRegAddr = instObj->baseAddress + IPIPE_RGB1_OFT_OR;

            /* Enable Module Clk */
            IpipeEnableSubModuleClk(
                instObj,
                ISSHAL_IPIPE_MODULE_RGB_RGB_1,
                (uint32_t) TRUE);
        }
        else
        {
            mulRegAddr  = instObj->baseAddress + IPIPE_RGB2_MUL_RR;
            ofstRegAddr = instObj->baseAddress + IPIPE_RGB2_OFT_OR;

            /* Enable Module Clk */
            IpipeEnableSubModuleClk(
                instObj,
                ISSHAL_IPIPE_MODULE_RGB_RGB_2,
                (uint32_t) TRUE);
        }

        for(cnt0 = 0U; cnt0 < ISSHAL_IPIPE_CSC_NUM_COEFF; cnt0++)
        {
            for(cnt1 = 0U; cnt1 < ISSHAL_IPIPE_CSC_NUM_COEFF; cnt1++)
            {
                HW_WR_REG32(mulRegAddr,
                            (((uint32_t)rgb2rgbCfg->mulCoeff[cnt0][cnt1] <<
                              IPIPE_RGB1_MUL_RR_VAL_SHIFT) &
                             IPIPE_RGB1_MUL_RR_VAL_MASK));

                mulRegAddr += 4U;
            }

            HW_WR_REG32(ofstRegAddr,
                        (((uint32_t)rgb2rgbCfg->addCoeff[cnt0] <<
                          IPIPE_RGB1_OFT_OR_VAL_SHIFT) &
                         IPIPE_RGB1_OFT_OR_VAL_MASK));
            ofstRegAddr += 4U;
        }
    }

    return (status);
}

static int32_t IpipeSetRgb2YuvConfig(
    isshalipipeInstObj_t             *instObj,
    const isshalipipeRgb2YuvConfig_t *rgb2yuvCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t cnt0, cnt1;
    uint32_t mulRegAddr;
    uint32_t ofstRegAddr;
    uint32_t regVal;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == rgb2yuvCfg)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if((rgb2yuvCfg->brightness >
            (IPIPE_YUV_ADJ_BRT_MASK >> IPIPE_YUV_ADJ_BRT_SHIFT)) ||
           (rgb2yuvCfg->contrast >
            (IPIPE_YUV_ADJ_CRT_MASK >> IPIPE_YUV_ADJ_CRT_SHIFT)))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == status)
    {
        /* Enable Module Clk */
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_RGB_TO_YUV,
            (uint32_t) TRUE);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_YUV_ADJ);

        regVal &= ~((UInt32) IPIPE_YUV_ADJ_CRT_MASK);
        regVal |= (rgb2yuvCfg->contrast << IPIPE_YUV_ADJ_CRT_SHIFT) &
                  IPIPE_YUV_ADJ_CRT_MASK;
        regVal &= ~((UInt32) IPIPE_YUV_ADJ_BRT_MASK);
        regVal |= (rgb2yuvCfg->brightness << IPIPE_YUV_ADJ_BRT_SHIFT) &
                  IPIPE_YUV_ADJ_BRT_MASK;

        HW_WR_REG32(instObj->baseAddress + IPIPE_YUV_ADJ, regVal);

        mulRegAddr  = instObj->baseAddress + IPIPE_YUV_MUL_RY;
        ofstRegAddr = instObj->baseAddress + IPIPE_YUV_OFT_Y;
        for(cnt0 = 0U; cnt0 < ISSHAL_IPIPE_CSC_NUM_COEFF; cnt0++)
        {
            for(cnt1 = 0U; cnt1 < ISSHAL_IPIPE_CSC_NUM_COEFF; cnt1++)
            {
                HW_WR_REG32(mulRegAddr, ((rgb2yuvCfg->mulCoeff[cnt0][cnt1] <<
                                          IPIPE_YUV_MUL_RY_VAL_SHIFT) &
                                         IPIPE_YUV_MUL_RY_VAL_MASK));

                mulRegAddr += 4U;
            }

            HW_WR_REG32(ofstRegAddr, ((rgb2yuvCfg->addCoeff[cnt0] <<
                                       IPIPE_YUV_OFT_Y_VAL_SHIFT) &
                                      IPIPE_YUV_OFT_Y_VAL_MASK));
            ofstRegAddr += 4U;
        }
    }

    return (status);
}

static int32_t IpipeSetDpcOtfConfig(
    const isshalipipeInstObj_t      *instObj,
    const vpsissIpipeDpcOtfConfig_t *cfg)
{
    int32_t           status;
    uint32_t          type, alg;
    volatile uint32_t regVal;

    status = FVID2_EBADARGS;
    if((NULL != cfg) && (NULL != instObj))
    {
        status = FVID2_SOK;
        if(TRUE == cfg->enableOtfDpc)
        {
            if((VPS_ISS_IPIPE_DPC_OTF_METHOD_MIN == cfg->method) ||
               (VPS_ISS_IPIPE_DPC_OTF_METHOD_MAX <= cfg->method))
            {
                status = FVID2_EBADARGS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_OTF_EN);
        regVal &= ~((UInt32) IPIPE_DPC_OTF_EN_MASK);
        HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_EN, regVal);
        if(TRUE == cfg->enableOtfDpc)
        {
            type = 0x1U; alg = 0x0U;
            if(VPS_ISS_IPIPE_DPC_OTF_METHOD_1 == cfg->method)
            {
                type = 0x1U; alg = 0x0U;
            }
            else if(VPS_ISS_IPIPE_DPC_OTF_METHOD_2 == cfg->method)
            {
                type = 0x0U; alg = 0x0U;
            }
            else /* Method = 3*/
            {
                type = 0x0U; alg = 0x1U;
            }
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_OTF_TYP);
            regVal &= ~((UInt32) (IPIPE_DPC_OTF_TYP_ALG_MASK |
                                  IPIPE_DPC_OTF_TYP_MASK));
            regVal |= IPIPE_DPC_OTF_TYP_ALG_MASK &
                      (alg << IPIPE_DPC_OTF_TYP_ALG_SHIFT);
            regVal |= IPIPE_DPC_OTF_TYP_MASK &
                      (type << IPIPE_DPC_OTF_TYP_SHIFT);
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_TYP, regVal);

            if(VPS_ISS_IPIPE_DPC_OTF_METHOD_2 == cfg->method)
            {
                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_D_THR_R);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_D_THR_R_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_D_THR_R_VAL_MASK & cfg->dThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_D_THR_R,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_D_THR_GR);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_D_THR_GR_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_D_THR_GR_VAL_MASK & cfg->grThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_D_THR_GR,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_D_THR_GB);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_D_THR_GB_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_D_THR_GB_VAL_MASK & cfg->gbThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_D_THR_GB,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_D_THR_B);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_D_THR_B_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_D_THR_B_VAL_MASK & cfg->bThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_D_THR_B,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_C_THR_R);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_C_THR_R_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_C_THR_R_VAL_MASK & cfg->rCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_C_THR_R,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_C_THR_GR);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_C_THR_GR_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_C_THR_GR_VAL_MASK & cfg->grCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_C_THR_GR,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_C_THR_GB);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_C_THR_GB_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_C_THR_GB_VAL_MASK & cfg->gbCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_C_THR_GB,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_2_C_THR_B);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_2_C_THR_B_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_2_C_THR_B_VAL_MASK & cfg->bCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_2_C_THR_B,
                            regVal);
            }

            if((VPS_ISS_IPIPE_DPC_OTF_METHOD_3 == cfg->method) ||
               (VPS_ISS_IPIPE_DPC_OTF_METHOD_1 == cfg->method))
            {
                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_D_THR);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_D_THR_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_D_THR_VAL_MASK &
                          (cfg->dThr << IPIPE_DPC_OTF_3_D_THR_VAL_SHIFT);
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_D_THR,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_D_SPL);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_D_SPL_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_D_SPL_VAL_MASK & cfg->grThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_D_SPL,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_D_MIN);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_D_MIN_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_D_MIN_VAL_MASK & cfg->gbThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_D_MIN,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_D_MAX);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_D_MAX_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_D_MAX_VAL_MASK & cfg->bThr;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_D_MAX,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_C_THR);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_C_THR_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_C_THR_VAL_MASK &
                          (cfg->rCor << IPIPE_DPC_OTF_3_C_THR_VAL_SHIFT);
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_C_THR,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_C_SLP);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_C_SLP_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_C_SLP_VAL_MASK & cfg->grCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_C_SLP,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_C_MIN);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_C_MIN_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_C_MIN_VAL_MASK & cfg->gbCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_C_MIN,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_C_MAX);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_C_MAX_VAL_MASK);
                regVal |= IPIPE_DPC_OTF_3_C_MAX_VAL_MASK & cfg->bCor;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_C_MAX,
                            regVal);

                regVal = HW_RD_REG32(instObj->baseAddress +
                                     IPIPE_DPC_OTF_3_SHF);
                regVal &= ~((UInt32) IPIPE_DPC_OTF_3_SHF_MASK);
                regVal |= IPIPE_DPC_OTF_3_SHF_MASK & cfg->shiftValue;
                HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_3_SHF, regVal);
            }

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_OTF_EN);
            regVal |= IPIPE_DPC_OTF_EN_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_OTF_EN, regVal);
        }
    }
    return status;
}

static int32_t IpipeSetDpcLutConfig(
    const isshalipipeInstObj_t      *instObj,
    const vpsissIpipeDpcLutConfig_t *cfg)
{
    int32_t           status;
    volatile uint32_t regVal;

    status = FVID2_EBADARGS;
    if((NULL != cfg) && (NULL != instObj))
    {
        status = FVID2_SOK;
        /*if ((0x0 == cfg->lutAddr) || (0x0 == cfg->lutSize))
         * {
         *  status = FVID2_EBADARGS;
         * }*/
    }

    if(FVID2_SOK == status)
    {
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_LUT_EN);
        regVal &= ~((UInt32) IPIPE_DPC_LUT_EN_MASK);
        if(TRUE == cfg->enableLutDpc)
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_LUT_SEL);
            regVal &= ~((UInt32) IPIPE_DPC_LUT_SEL_TBL_MASK);
            if(TRUE == cfg->lutMode)
            {
                /* infinite entries in LUT */
                regVal |= IPIPE_DPC_LUT_SEL_TBL_MASK;
            }
            regVal &= ~((UInt32) IPIPE_DPC_LUT_SEL_DOT_MASK);
            if(TRUE == cfg->blackOrWhite)
            {
                /* Replace with white */
                regVal |= IPIPE_DPC_LUT_SEL_DOT_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_LUT_SEL, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_LUT_ADR);
            regVal &= ~((UInt32) IPIPE_DPC_LUT_ADR_MASK);
            regVal |= IPIPE_DPC_LUT_ADR_MASK & cfg->lutAddr;
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_LUT_ADR, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_LUT_SIZ);
            regVal &= ~((UInt32) IPIPE_DPC_LUT_SIZ_MASK);
            regVal |= IPIPE_DPC_LUT_SIZ_MASK & cfg->lutSize;
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_LUT_SIZ, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_DPC_LUT_EN);
            regVal |= IPIPE_DPC_LUT_EN_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_LUT_EN, regVal);
        }
        else
        {
            HW_WR_REG32(instObj->baseAddress + IPIPE_DPC_LUT_EN, regVal);
        }
    }
    return status;
}

static int32_t IpipeSetGammaConfig(
    isshalipipeInstObj_t           *instObj,
    const vpsissIpipeGammaConfig_t *cfg)
{
    int32_t           status = FVID2_SOK;
    volatile uint32_t regVal;
    uint32_t          ramTblSize;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (0U != instObj->gammaLutRedAddr));
    GT_assert(VpsHalTrace, (0U != instObj->gammaLutGreenAddr));
    GT_assert(VpsHalTrace, (0U != instObj->gammaLutBlueAddr));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if(((TRUE == cfg->enableRed) && (NULL == cfg->lutRed)) ||
           ((TRUE == cfg->enableGreen) && (NULL == cfg->lutGreen)) ||
           ((TRUE == cfg->enableBlue) && (NULL == cfg->lutBlue)))
        {
            status = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == status)
    {
        /* TODO: Turn off the sub-module clock when all modules
         *       using this clock are off */
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_GAMMA,
            (uint32_t) TRUE);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_GMM_CFG);

        regVal &= ~((UInt32) (IPIPE_GMM_CFG_SIZ_MASK |
                              IPIPE_GMM_CFG_TBL_MASK));

        regVal |= IPIPE_GMM_CFG_BYPR_MASK | IPIPE_GMM_CFG_BYPG_MASK |
                  IPIPE_GMM_CFG_BYPB_MASK;

        regVal |= (cfg->tbl << IPIPE_GMM_CFG_TBL_SHIFT) &
                  IPIPE_GMM_CFG_TBL_MASK;
        regVal |= (cfg->tblSize << IPIPE_GMM_CFG_SIZ_SHIFT) &
                  IPIPE_GMM_CFG_SIZ_MASK;

        switch(cfg->tblSize)
        {
            case VPS_ISS_IPIPE_GAMMA_TBL_SIZE_64:
                ramTblSize = 64U * 4U;
                break;
            case VPS_ISS_IPIPE_GAMMA_TBL_SIZE_128:
                ramTblSize = 128U * 4U;
                break;
            case VPS_ISS_IPIPE_GAMMA_TBL_SIZE_256:
                ramTblSize = 256U * 4U;
                break;
            case VPS_ISS_IPIPE_GAMMA_TBL_SIZE_512:
                ramTblSize = 512U * 4U;
                break;
            default:
                ramTblSize = 512U * 4U;
                break;
        }

        if(TRUE == cfg->enableRed)
        {
            regVal &= ~((UInt32) IPIPE_GMM_CFG_BYPR_MASK);

            if(VPS_ISS_IPIPE_GAMMA_TBL_RAM == cfg->tbl)
            {
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3
                 * Casting between a pointer to an integral type
                 * KW State: Ignore -> Waiver -> Case by case
                 * MISRAC_WAIVER:
                 * Variable contains Lut's memory mapped address,
                 * type casted to Ptr since memcpy expects Ptr as
                 * first argument.
                 * lutReg and gammaLutRedAddr both variables are checked for
                 * NULL/0 value.
                 */
                BspUtils_memcpy(
                    (Ptr)instObj->gammaLutRedAddr,
                    cfg->lutRed,
                    ramTblSize);
            }
        }

        if(TRUE == cfg->enableGreen)
        {
            regVal &= ~((UInt32) IPIPE_GMM_CFG_BYPG_MASK);

            if(VPS_ISS_IPIPE_GAMMA_TBL_RAM == cfg->tbl)
            {
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3
                 * Casting between a pointer to an integral type
                 * KW State: Ignore -> Waiver -> Case by case
                 * MISRAC_WAIVER:
                 * Variable contains Lut's memory mapped address,
                 * type casted to Ptr since memcpy expects Ptr as
                 * first argument.
                 * lutGreen and gammaLutGreenAddr both variables are checked for
                 * NULL/0 value.
                 */
                BspUtils_memcpy(
                    (Ptr)instObj->gammaLutGreenAddr,
                    cfg->lutGreen,
                    ramTblSize);
            }
        }

        if(TRUE == cfg->enableBlue)
        {
            regVal &= ~((UInt32) IPIPE_GMM_CFG_BYPB_MASK);

            if(VPS_ISS_IPIPE_GAMMA_TBL_RAM == cfg->tbl)
            {
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004_Rule_11.3
                 * Casting between a pointer to an integral type
                 * KW State: Ignore -> Waiver -> Case by case
                 * MISRAC_WAIVER:
                 * Variable contains Lut's memory mapped address,
                 * type casted to Ptr since memcpy expects Ptr as
                 * first argument.
                 * lutBlue and gammaLutBlueAddr both variables are checked for
                 * NULL/0 value.
                 */
                BspUtils_memcpy(
                    (Ptr)instObj->gammaLutBlueAddr,
                    cfg->lutBlue,
                    ramTblSize);
            }
        }

        HW_WR_REG32(instObj->baseAddress + IPIPE_GMM_CFG, regVal);
    }

    return (status);
}

static int32_t IpipeSet3DLutConfig(
    isshalipipeInstObj_t           *instObj,
    const vpsissIpipe3DLutConfig_t *cfg)
{
    int32_t           status = FVID2_SOK;
    volatile uint32_t regVal;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (0U != instObj->lut3DBank0Addr));
    GT_assert(VpsHalTrace, (0U != instObj->lut3DBank1Addr));
    GT_assert(VpsHalTrace, (0U != instObj->lut3DBank2Addr));
    GT_assert(VpsHalTrace, (0U != instObj->lut3DBank3Addr));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(TRUE == cfg->enable)
        {
            if((NULL == cfg->b0Addr) || (NULL == cfg->b1Addr) ||
               (NULL == cfg->b2Addr) || (NULL == cfg->b3Addr))
            {
                status = FVID2_EBADARGS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_3D_LUT,
            (uint32_t) TRUE);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_3DLUT_EN);

        if(TRUE == cfg->enable)
        {
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * Casting between a pointer to an integral type
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Variable contains Lut's memory mapped address,
             * type casted to Ptr since memcpy expects Ptr as
             * first argument.
             * all variables containing bank addresses are checked for
             * NULL/0 value.
             */
            /* Copy Lut to the bank memories */
            BspUtils_memcpy(
                (Ptr)instObj->lut3DBank0Addr,
                cfg->b0Addr,
                192U*4U);
            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * Casting between a pointer to an integral type
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Variable contains Lut's memory mapped address,
             * type casted to Ptr since memcpy expects Ptr as
             * first argument.
             * all variables containing bank addresses are checked for
             * NULL/0 value.
             */
            BspUtils_memcpy(
                (Ptr)instObj->lut3DBank1Addr,
                cfg->b1Addr,
                192U*4U);

            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * Casting between a pointer to an integral type
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Variable contains Lut's memory mapped address,
             * type casted to Ptr since memcpy expects Ptr as
             * first argument.
             * all variables containing bank addresses are checked for
             * NULL/0 value.
             */
            /* Bank 2 and 3 have only 181 entries,
               because LUT beyond 729 index are not used */
            BspUtils_memcpy(
                (Ptr)instObj->lut3DBank2Addr,
                cfg->b2Addr,
                192U*4U);
            BspUtils_memcpy(
                (Ptr)instObj->lut3DBank3Addr,
                cfg->b3Addr,
                192U*4U);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_3DLUT_EN);
            regVal |= IPIPE_3DLUT_EN_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_3DLUT_EN, regVal);
        }
        else
        {
            regVal &= ~((UInt32) IPIPE_3DLUT_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + IPIPE_3DLUT_EN, regVal);
        }
    }

    return (status);
}

static int32_t IpipeSetEeConfig(
    isshalipipeInstObj_t        *instObj,
    const vpsissIpipeEeConfig_t *cfg)
{
    int32_t           status = FVID2_SOK;
    volatile uint32_t regVal;
    volatile uint32_t regAddr;
    uint32_t          cnt;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != instObj->yeeLutAddr));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if((TRUE == cfg->enable) && (NULL == cfg->lutAddr))
        {
            status = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == status)
    {
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_YEE,
            (uint32_t) TRUE);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_EN);

        if(TRUE == cfg->enable)
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_TYP);
            regVal &= ~((UInt32) (IPIPE_YEE_TYP_SEL_MASK |
                                  IPIPE_YEE_TYP_HAL_MASK));

            if(TRUE == cfg->enableHaloReduction)
            {
                regVal |= IPIPE_YEE_TYP_HAL_MASK;
            }
            if(VPS_ISS_IPIPE_EE_MERGE_METHOD_MAX == cfg->method)
            {
                regVal |= IPIPE_YEE_TYP_SEL_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_TYP, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_SHF);
            regVal &= ~((UInt32) IPIPE_YEE_SHF_MASK);
            regVal |= (cfg->hpfDs << IPIPE_YEE_SHF_SHIFT) & IPIPE_YEE_SHF_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_SHF, regVal);

            regAddr = (instObj->baseAddress + IPIPE_YEE_MUL_00);
            for(cnt = 0u; cnt < VPS_ISS_IPIPE_YEE_MAX_HPF_COEFF; cnt++)
            {
                regVal  = HW_RD_REG32(regAddr);
                regVal &= ~((UInt32) IPIPE_YEE_MUL_00_VAL_MASK);
                regVal |=
                    (cfg->hpfMulCoeff[cnt] << IPIPE_YEE_MUL_00_VAL_SHIFT) &
                    IPIPE_YEE_MUL_00_VAL_MASK;
                HW_WR_REG32(regAddr, regVal);

                regAddr += 4u;
            }

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_THR);
            regVal &= ~((UInt32) IPIPE_YEE_THR_VAL_MASK);
            regVal |= (cfg->hpfThreshold << IPIPE_YEE_THR_VAL_SHIFT) &
                      IPIPE_YEE_THR_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_THR, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_E_GAN);
            regVal &= ~((UInt32) IPIPE_YEE_E_GAN_VAL_MASK);
            regVal |= (cfg->gain << IPIPE_YEE_E_GAN_VAL_SHIFT) &
                      IPIPE_YEE_E_GAN_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_E_GAN, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_E_THR_1);
            regVal &= ~((UInt32) IPIPE_YEE_E_THR_1_VAL_MASK);
            regVal |= (cfg->hpfThresholdLow << IPIPE_YEE_E_THR_1_VAL_SHIFT) &
                      IPIPE_YEE_E_THR_1_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_E_THR_1, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_E_THR_2);
            regVal &= ~((UInt32) IPIPE_YEE_E_THR_2_VAL_MASK);
            regVal |= (cfg->hpfThresholdHigh << IPIPE_YEE_E_THR_2_VAL_SHIFT) &
                      IPIPE_YEE_E_THR_2_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_E_THR_2, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_G_GAN);
            regVal &= ~((UInt32) IPIPE_YEE_G_GAN_VAL_MASK);
            regVal |= (cfg->gradientGain << IPIPE_YEE_G_GAN_VAL_SHIFT) &
                      IPIPE_YEE_G_GAN_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_G_GAN, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_G_OFT);
            regVal &= ~((UInt32) IPIPE_YEE_G_OFT_VAL_MASK);
            regVal |= (cfg->gradientOffset << IPIPE_YEE_G_OFT_VAL_SHIFT) &
                      IPIPE_YEE_G_OFT_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_G_OFT, regVal);

            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * Casting between a pointer to an integral type
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Variable contains Lut's memory mapped address,
             * type casted to Ptr since memcpy expects Ptr as
             * first argument.
             * both lutAddr and yeeLutAddr are checked for
             * NULL/0 value.
             */
            BspUtils_memcpy(
                (Ptr)instObj->yeeLutAddr,
                cfg->lutAddr,
                512U*4U);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_EN);
            regVal |= IPIPE_YEE_EN_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_EN, regVal);
        }
        else
        {
            regVal &= ~((UInt32) IPIPE_YEE_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_EN, regVal);
        }
    }
    return (FVID2_SOK);
}

static int32_t IpipeSetGicConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeGicConfig_t *cfg)
{
    int32_t           status = FVID2_SOK;
    volatile uint32_t regVal;
    volatile uint32_t regAddr;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_GIC,
            (uint32_t) TRUE);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_EN);

        if(TRUE == cfg->enable)
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_GAN);
            regVal &= ~((UInt32) IPIPE_GIC_GAN_VAL_MASK);
            regVal |= (cfg->gain << IPIPE_GIC_GAN_VAL_SHIFT) &
                      IPIPE_GIC_GAN_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_GAN, regVal);

            /* NFGain is used only if threshold is selected from the
             * NF2 block */
            if(VPS_ISS_IPIPE_GIC_THR_SEL_NF2 == cfg->thrSel)
            {
                regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_NFGAIN);
                regVal &= ~((UInt32) IPIPE_GIC_NFGAIN_VAL_MASK);
                regVal |= (cfg->nfGain << IPIPE_GIC_NFGAIN_VAL_SHIFT) &
                          IPIPE_GIC_NFGAIN_VAL_MASK;
                HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_NFGAIN, regVal);
            }
            /* GIC Registers are used for selecting threshold */
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_THR);
            regVal &= ~((UInt32) IPIPE_GIC_THR_VAL_MASK);
            regVal |= (cfg->threshold << IPIPE_GIC_THR_VAL_SHIFT) &
                      IPIPE_GIC_THR_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_THR, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_SLP);
            regVal &= ~((UInt32) IPIPE_GIC_SLP_VAL_MASK);
            regVal |= (cfg->slope << IPIPE_GIC_SLP_VAL_SHIFT) &
                      IPIPE_GIC_SLP_VAL_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_SLP, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_TYP);
            regVal &= ~((UInt32) (IPIPE_GIC_TYP_MASK | IPIPE_GIC_TYP_SEL_MASK |
                                  IPIPE_GIC_TYP_LSC_MASK));

            if(VPS_ISS_IPIPE_GIC_ALG_TYPE_ADAPT == cfg->type)
            {
                regVal |= IPIPE_GIC_TYP_MASK;
            }
            if(TRUE == cfg->enableLscGain)
            {
                regVal |= IPIPE_GIC_TYP_LSC_MASK;
            }
            if(VPS_ISS_IPIPE_GIC_THR_SEL_NF2 == cfg->thrSel)
            {
                regVal |= IPIPE_GIC_TYP_SEL_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_TYP, regVal);

            /* Enable GIC module */
            regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_GIC_EN);
            regVal |= IPIPE_GIC_EN_MASK;
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_EN, regVal);
        }
        else /* Disable GIC */
        {
            regVal &= ~((UInt32) IPIPE_GIC_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + IPIPE_GIC_EN, regVal);
        }
    }

    return (status);
}

static int32_t IpipeSetLscConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeLscConfig_t *cfg)
{
    int32_t           status = FVID2_SOK;
    uint32_t          cnt;
    volatile uint32_t regVal;
    volatile uint32_t gainRegAddr, offRegAddr;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        IpipeEnableSubModuleClk(instObj, ISSHAL_IPIPE_MODULE_LSC,
            (uint32_t) TRUE);

        /* Set the Vertical Coefficients and Shifts */
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_VOFT);
        regVal &= ~((UInt32) IPIPE_LSC_VOFT_MASK);
        regVal |= (cfg->vertOffset << IPIPE_LSC_VOFT_SHIFT) &
                  IPIPE_LSC_VOFT_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_VOFT, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_VA1);
        regVal &= ~((UInt32) IPIPE_LSC_VA1_VAL_MASK);
        regVal |= (cfg->vertLinCoeff << IPIPE_LSC_VA1_VAL_SHIFT) &
                  IPIPE_LSC_VA1_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_VA1, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_VA2);
        regVal &= ~((UInt32) IPIPE_LSC_VA2_VAL_MASK);
        regVal |= (cfg->vertQdrCoeff << IPIPE_LSC_VA2_VAL_SHIFT) &
                  IPIPE_LSC_VA2_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_VA2, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_VS);
        regVal &= ~((UInt32) (IPIPE_LSC_VS_VS1_MASK | IPIPE_LSC_VS_VS2_MASK));
        regVal |= (cfg->vertLinShift << IPIPE_LSC_VS_VS1_SHIFT) &
                  IPIPE_LSC_VS_VS1_MASK;
        regVal |= (cfg->vertQdrShift << IPIPE_LSC_VS_VS2_SHIFT) &
                  IPIPE_LSC_VS_VS2_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_VS, regVal);

        /* Set the Horizontal Coefficients and Shifts */
        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_HOFT);
        regVal &= ~((UInt32) IPIPE_LSC_HOFT_VAL_MASK);
        regVal |= (cfg->horzOffset << IPIPE_LSC_HOFT_VAL_SHIFT) &
                  IPIPE_LSC_HOFT_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_HOFT, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_HA1);
        regVal &= ~((UInt32) IPIPE_LSC_HA1_VAL_MASK);
        regVal |= (cfg->horzLinCoeff << IPIPE_LSC_HA1_VAL_SHIFT) &
                  IPIPE_LSC_HA1_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_HA1, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_HA2);
        regVal &= ~((UInt32) IPIPE_LSC_HA2_VAL_MASK);
        regVal |= (cfg->horzQdrCoeff << IPIPE_LSC_HA2_VAL_SHIFT) &
                  IPIPE_LSC_HA2_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_HA2, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_HS);
        regVal &= ~((UInt32) (IPIPE_LSC_HS_HS1_MASK | IPIPE_LSC_HS_HS2_MASK));
        regVal |= (cfg->horzLinShift << IPIPE_LSC_HS_HS1_SHIFT) &
                  IPIPE_LSC_HS_HS1_MASK;
        regVal |= (cfg->horzQdrShift << IPIPE_LSC_HS_HS2_SHIFT) &
                  IPIPE_LSC_HS_HS2_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_HS, regVal);

        gainRegAddr = instObj->baseAddress + IPIPE_LSC_GAN_R;
        offRegAddr  = instObj->baseAddress + IPIPE_LSC_OFT_R;
        /* Set the Color Gain and Offset */
        for(cnt = 0u; cnt < FVID2_BAYER_COLOR_COMP_MAX; cnt++)
        {
            regVal  = HW_RD_REG32(gainRegAddr);
            regVal &= ~((UInt32) IPIPE_LSC_GAN_R_VAL_MASK);
            regVal |= (cfg->gain[cnt] << IPIPE_LSC_GAN_R_VAL_SHIFT) &
                      IPIPE_LSC_GAN_R_VAL_MASK;
            HW_WR_REG32(gainRegAddr, regVal);
            gainRegAddr += 4u;

            regVal  = HW_RD_REG32(offRegAddr);
            regVal &= ~((UInt32) IPIPE_LSC_OFT_R_VAL_MASK);
            regVal |= (cfg->offset[cnt] << IPIPE_LSC_OFT_R_VAL_SHIFT) &
                      IPIPE_LSC_OFT_R_VAL_MASK;
            HW_WR_REG32(offRegAddr, regVal);
            offRegAddr += 4u;
        }

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_SHF);
        regVal &= ~((UInt32) IPIPE_LSC_SHF_VAL_MASK);
        regVal |= (cfg->shift << IPIPE_LSC_SHF_VAL_SHIFT) &
                  IPIPE_LSC_SHF_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_SHF, regVal);

        regVal  = HW_RD_REG32(instObj->baseAddress + IPIPE_LSC_MAX);
        regVal &= ~((UInt32) IPIPE_LSC_MAX_VAL_MASK);
        regVal |= (cfg->max << IPIPE_LSC_MAX_VAL_SHIFT) &
                  IPIPE_LSC_MAX_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_LSC_MAX, regVal);
    }

    return (status);
}

static int32_t IpipeSetChromaDsConfig(
    const isshalipipeInstObj_t      *instObj,
    const isshalipipeYuvPhsConfig_t *yuvPhsCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == yuvPhsCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_YUV_PHS);

        regVal &= ~((UInt32) IPIPE_YUV_PHS_LPF_MASK);
        if(1U == yuvPhsCfg->enableLpf)
        {
            regVal |= IPIPE_YUV_PHS_LPF_MASK;
        }

        regVal &= ~((UInt32) IPIPE_YUV_PHS_POS_MASK);
        if(FVID2_CHROMA_POS_CENTERED == yuvPhsCfg->chromaPos)
        {
            regVal |= IPIPE_YUV_PHS_POS_MASK;
        }

        HW_WR_REG32(instObj->baseAddress + IPIPE_YUV_PHS, regVal);
    }

    return (status);
}

static int32_t IpipeSetNfConfig(
    isshalipipeInstObj_t         *instObj,
    const vpsissIpipeNf2Config_t *cfg,
    isshalipipeModuleId_t         moduleId)
{
    int32_t           status = FVID2_SOK;
    uint32_t          cnt;
    volatile uint32_t regVal;
    volatile uint32_t regAddr;
    volatile uint32_t regOff;
    volatile uint32_t thrOff, strOff, sprOff;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL == cfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        IpipeEnableSubModuleClk(instObj, moduleId, (uint32_t) TRUE);

        if(ISSHAL_IPIPE_MODULE_NOISE_FILTER_1 == moduleId)
        {
            regOff = 0U;
        }
        else
        {
            regOff = IPIPE_D2F_2ND_EN - IPIPE_D2F_1ST_EN;
        }

        /* Configuring all thresholds even in case NF is enabled,
         * since these thresholds could be used in other modules like GIC */
        /* Set the Noise Filter Threshold, intensity and stread Factor */
        thrOff = instObj->baseAddress + IPIPE_D2F_1ST_THR_00 + regOff;
        strOff = instObj->baseAddress + IPIPE_D2F_1ST_STR_00 + regOff;
        sprOff = instObj->baseAddress + IPIPE_D2F_1ST_SPR_00 + regOff;
        for(cnt = 0U; cnt < VPS_ISS_IPIPE_NF2_MAX_THR; cnt++)
        {
            regVal  = HW_RD_REG32(thrOff);
            regVal &= ~((UInt32) IPIPE_D2F_1ST_THR_00_VAL_MASK);
            regVal |= (cfg->threshold[cnt] <<
                       IPIPE_D2F_1ST_THR_00_VAL_SHIFT) &
                      IPIPE_D2F_1ST_THR_00_VAL_MASK;
            HW_WR_REG32(thrOff, regVal);

            regVal  = HW_RD_REG32(strOff);
            regVal &= ~((UInt32) IPIPE_D2F_1ST_STR_00_VAL_MASK);
            regVal |= (cfg->intensity[cnt] <<
                       IPIPE_D2F_1ST_STR_00_VAL_SHIFT) &
                      IPIPE_D2F_1ST_STR_00_VAL_MASK;
            HW_WR_REG32(strOff, regVal);

            regVal  = HW_RD_REG32(sprOff);
            regVal &= ~((UInt32) IPIPE_D2F_1ST_SPR_00_VAL_MASK);
            regVal |= (cfg->sprFactor[cnt] <<
                       IPIPE_D2F_1ST_SPR_00_VAL_SHIFT) &
                      IPIPE_D2F_1ST_SPR_00_VAL_MASK;
            HW_WR_REG32(sprOff, regVal);

            thrOff += 4U;
            sprOff += 4U;
            strOff += 4U;
        }

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EDG_MIN +
                             regOff);
        regVal &= ~((UInt32) IPIPE_D2F_1ST_EDG_MIN_VAL_MASK);
        regVal |= (cfg->edgeMin << IPIPE_D2F_1ST_EDG_MIN_VAL_SHIFT) &
                  IPIPE_D2F_1ST_EDG_MIN_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EDG_MIN + regOff,
                    regVal);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EDG_MAX +
                             regOff);
        regVal &= ~((UInt32) IPIPE_D2F_1ST_EDG_MAX_VAL_MASK);
        regVal |= (cfg->edgeMax << IPIPE_D2F_1ST_EDG_MAX_VAL_SHIFT) &
                  IPIPE_D2F_1ST_EDG_MAX_VAL_MASK;
        HW_WR_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EDG_MAX + regOff,
                    regVal);

        /* Set other configuration like green color sampling type,
         * SPR source, LSC Enable etc. */
        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_D2F_1ST_TYP +
                             regOff);
        regVal &= ~((UInt32) (IPIPE_D2F_1ST_TYP_SPR_MASK |
                              IPIPE_D2F_1ST_TYP_SHF_MASK |
                              IPIPE_D2F_1ST_TYP_MASK |
                              IPIPE_D2F_1ST_TYP_LSC_MASK |
                              IPIPE_D2F_1ST_TYP_SEL_MASK));

        regVal |= (cfg->spreadVal << IPIPE_D2F_1ST_TYP_SPR_SHIFT) &
                  IPIPE_D2F_1ST_TYP_SPR_MASK;
        regVal |= (cfg->downShift << IPIPE_D2F_1ST_TYP_SHF_SHIFT) &
                  IPIPE_D2F_1ST_TYP_SHF_MASK;
        if(TRUE == cfg->enableLscGain)
        {
            regVal |= IPIPE_D2F_1ST_TYP_LSC_MASK;
        }
        if(TRUE == cfg->useLutSpr)
        {
            regVal |= IPIPE_D2F_1ST_TYP_SEL_MASK;
        }
        if(VPS_ISS_IPIPE_NF2_GREEN_TYPE_DIAMOND == cfg->grPixType)
        {
            regVal |= IPIPE_D2F_1ST_TYP_MASK;
        }
        HW_WR_REG32(instObj->baseAddress + IPIPE_D2F_1ST_TYP + regOff, regVal);

        regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EN + regOff);
        if(TRUE == cfg->enable)
        {
            regVal |= IPIPE_D2F_1ST_EN_MASK;
        }
        else
        {
            regVal &= ~((UInt32) IPIPE_D2F_1ST_EN_MASK);
        }
        HW_WR_REG32(instObj->baseAddress + IPIPE_D2F_1ST_EN + regOff, regVal);
    }

    return (status);
}

static void IpipeEnableSubModuleClk(
    isshalipipeInstObj_t *instObj,
    isshalipipeModuleId_t moduleId,
    uint32_t              enable)
{
    uint32_t bitMask = 0x0U;

    if((ISS_HAL_IPIPE_G0_CLK_MASK & moduleId) == moduleId)
    {
        if(TRUE == enable)
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G0] |= moduleId;
            bitMask = IPIPE_GCK_PIX_G0_MASK;
        }
        else
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G0] &= ~((UInt32) moduleId);

            if(0U == instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G0])
            {
                bitMask = IPIPE_GCK_PIX_G0_MASK;
            }
        }
    }
    else if((ISS_HAL_IPIPE_G1_CLK_MASK & moduleId) == moduleId)
    {
        if(TRUE == enable)
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G1] |= moduleId;
            bitMask = IPIPE_GCK_PIX_G1_MASK;
        }
        else
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G1] &= ~((UInt32) moduleId);

            if(0U == instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G1])
            {
                bitMask = IPIPE_GCK_PIX_G1_MASK;
            }
        }
    }
    else if((ISS_HAL_IPIPE_G2_CLK_MASK & moduleId) == moduleId)
    {
        if(TRUE == enable)
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G2] |= moduleId;
            bitMask = IPIPE_GCK_PIX_G2_MASK;
        }
        else
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G2] &= ~((UInt32) moduleId);

            if(0U == instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G2])
            {
                bitMask = IPIPE_GCK_PIX_G2_MASK;
            }
        }
    }
    else
    {
        if(TRUE == enable)
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G3] |= moduleId;
            bitMask = IPIPE_GCK_PIX_G3_MASK;
        }
        else
        {
            instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G3] &= ~((UInt32) moduleId);

            if(0U == instObj->modClkMask[ISSHAL_IPIPE_GCK_CLK_G3])
            {
                bitMask = IPIPE_GCK_PIX_G3_MASK;
            }
        }
    }

    if(TRUE == enable)
    {
        HW_WR_REG32(instObj->baseAddress + IPIPE_GCK_PIX,
                    HW_RD_REG32(instObj->baseAddress + IPIPE_GCK_PIX) | bitMask);
    }
    else
    {
        HW_WR_REG32(instObj->baseAddress + IPIPE_GCK_PIX,
                    HW_RD_REG32(
                        instObj->baseAddress + IPIPE_GCK_PIX) & ~bitMask);
    }
}

static int32_t IpipeUpdateLut(
    const isshalipipeInstObj_t    *instObj,
    const vpsissIpipeLutFmtCnvt_t *fmtCnvt)
{
    int32_t   status = FVID2_EBADARGS;
    uint32_t  cnt;
    uint32_t  regVal, idx;
    uint32_t *b0, *b1, *b2, *b3;
    uint32_t  b0Set, b1Set, b2Set;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));

    if(NULL != fmtCnvt)
    {
        if(VPS_ISS_IPIPE_MODULE_3D_LUT == fmtCnvt->moduleId)
        {
            if((NULL == fmtCnvt->lut3DRed) || (NULL == fmtCnvt->lut3DGreen) ||
               (NULL == fmtCnvt->lut3DBlue) ||
               (NULL == fmtCnvt->out3DB0Addr) ||
               (NULL == fmtCnvt->out3DB1Addr) ||
               (NULL == fmtCnvt->out3DB2Addr) ||
               (NULL == fmtCnvt->out3DB3Addr))
            {
                status = FVID2_EBADARGS;
            }
            else
            {
                b0 = fmtCnvt->out3DB0Addr;
                b1 = fmtCnvt->out3DB1Addr;
                b2 = fmtCnvt->out3DB2Addr;
                b3 = fmtCnvt->out3DB3Addr;

                b0Set = (uint32_t)TRUE;
                b1Set = (uint32_t)FALSE;
                b2Set = (uint32_t)FALSE;
/* MISRA.PTR.ARITH
 * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
 * Pointer is accessed as an array
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Pointer is accessed as an array. lut3DRed, lut3DGreen,
 *                  lut3DBlue.
 */

/* MISRA.PTR.ARITH
 * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
 * Pointer is accessed as an array
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: Pointer is accessed as an array. b0, b1, b2 & b3
 */
                /* Copy the LUT in the Banks */
                for(cnt = 0u; cnt < 729u; cnt++)
                {
                    regVal = ((fmtCnvt->lut3DRed[cnt] & 0x3FFu) << 20u) |
                             ((fmtCnvt->lut3DGreen[cnt] & 0x3FFu) << 10u) |
                             ((fmtCnvt->lut3DBlue[cnt] & 0x3FFu) << 0u);
                    if(TRUE == b0Set)
                    {
                        *b0 = regVal;
                        b0 += 1U;

                        b0Set = (uint32_t)FALSE;
                        b1Set = (uint32_t)TRUE;
                    }
                    else if(TRUE == b1Set)
                    {
                        *b1 = regVal;
                        b1 += 1U;

                        b1Set = (uint32_t)FALSE;
                        b2Set = (uint32_t)TRUE;
                    }
                    else if(TRUE == b2Set)
                    {
                        *b2 = regVal;
                        b2 += 1U;

                        b2Set = (uint32_t)FALSE;
                    }
                    else
                    {
                        *b3 = regVal;
                        b3 += 1U;

                        b0Set = (uint32_t)TRUE;
                    }
                }
                status = FVID2_SOK;
            }
        }
        else if(VPS_ISS_IPIPE_MODULE_EDGE_ENHANCER == fmtCnvt->moduleId)
        {
            if((NULL == fmtCnvt->yeeLutOut) ||
               (NULL == fmtCnvt->yeeLutIn))
            {
                status = FVID2_EBADARGS;
            }
            else
            {
                for(cnt = 0U; cnt < 512U; cnt++)
                {
                    /* MISRA.PTR.ARITH
                     * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                     * Pointer is accessed as an array.
                     * MISRAC_WAIVER: Yee input table is either allocated
                     * by DCC or by video sensor layer in vsdk. Even in
                     * sample app, an array of 512 entry is used for input
                     * and array of 1024 bytes is used for the output. So this
                     * access will not go out of bound for both the input
                     * and output pointers.
                     */
                    fmtCnvt->yeeLutOut[cnt] =
                        ((fmtCnvt->yeeLutIn[(2U * cnt) + 1U] & 0x1FFU) << 9U) |
                        ((fmtCnvt->yeeLutIn[(2U * cnt)] & 0x1FFU) << 0U);
                }
                status = FVID2_SOK;
            }
        }
        else if(VPS_ISS_IPIPE_MODULE_GAMMA_CORRECTION == fmtCnvt->moduleId)
        {
            if((NULL == fmtCnvt->gammaLutOut) ||
               (NULL == fmtCnvt->gammaLutIn))
            {
                status = FVID2_EBADARGS;
            }
            else
            {
                idx = 0u;
                for(cnt = 0; cnt < 512U; cnt++)
                {
                    /* MISRA.PTR.ARITH
                     * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                     * Pointer is accessed as an array.
                     * MISRAC_WAIVER: Gamma input table is either allocated
                     * by DCC or by video sensor layer in vsdk. Even in
                     * sample app, an array of 1024 entry is used. So this
                     * access will not go out of bound.
                     */
                    regVal =
                        ((fmtCnvt->gammaLutIn[idx] & 0x3FFu) << 10u) |
                        ((fmtCnvt->gammaLutIn[idx + 1U] & 0x3FFu) << 0u);

                    /* MISRA.PTR.ARITH
                     * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                     * Pointer is accessed as an array.
                     * MISRAC_WAIVER: This is only used when gamma table in
                     * two column format is used. This is the case where
                     * gamma table from vision sensor layer is used in vsdk.
                     * In that case, link pass allocates the array and passes
                     * pointer to it.
                     * in other cases, DCC will take care of converting, so
                     * this ioctl will not be called.
                     * In all case, this out pointer will not go out of bound.
                     */
                    fmtCnvt->gammaLutOut[cnt] = regVal;
                    idx += 2u;
                }

                status = FVID2_SOK;
            }
        }
        else
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

static int32_t IpipeEnableDisableEe(
    const isshalipipeInstObj_t  *instObj,
    const vpsissIpipeEeConfig_t *cmdArgs)
{
    volatile uint32_t regVal;

    /* Check For Null Pointers */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != cmdArgs));

    regVal = HW_RD_REG32(instObj->baseAddress + IPIPE_YEE_EN);

    if(TRUE == cmdArgs->enable)
    {
        regVal |= IPIPE_YEE_EN_MASK;
    }
    else
    {
        regVal &= ~((UInt32) IPIPE_YEE_EN_MASK);
    }
    HW_WR_REG32(instObj->baseAddress + IPIPE_YEE_EN, regVal);

    return (FVID2_SOK);
}

