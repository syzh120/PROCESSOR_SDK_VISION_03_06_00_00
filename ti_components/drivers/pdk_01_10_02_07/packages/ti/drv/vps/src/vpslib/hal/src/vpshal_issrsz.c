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
 *  \file isshal_rsz.c
 *
 *  \brief File containing the ISS RSZ HAL init, deinit and other common
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
#include <ti/drv/vps/src/vpslib/hal/vpshal_issrsz.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* MISRA.DEFINE.FUNC
 * MISRAC_2004_Rule_19.7
 * Function Like Macro definition
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer is reconfigured almost every frame, so for performance reasons,
 * using macro instead of inline functions
 */
/**
 *  \brief Maximum LineWidth Supported
 */
#define RSZ_INST_MAX_WIDTH(n)       ((0U == (n)) ?                        \
                                     (RSZ_GNC_RSZA_MEM_LINE_SIZE_MASK >>  \
                                      RSZ_GNC_RSZA_MEM_LINE_SIZE_SHIFT) : \
                                     (RSZ_GNC_RSZB_MEM_LINE_SIZE_MASK >>  \
                                      RSZ_GNC_RSZB_MEM_LINE_SIZE_SHIFT))

/**
 *  \brief Macro for defining the difference between two same
 *         registers of instance A and B
 */
#define RSZ_INST_DIFF                               (RZB_EN - RZA_EN)

/**< Maximum Downscaling supported */
#define RSZ_DOWN_SCALE_MAX_SIZE                     (8U)

/**< Multiplier for calculating scaling factors */
#define RSZ_NORMAL_SCALE_MUL                        (256U)

/**< Minimum Scaling factor supported for Normal Scaling  */
#define RSZ_NORMAL_MAX_SCALE_FACTOR                 (4096U)

/**< Maximum Scaling factor supported for Normal Scaling  */
#define RSZ_NORMAL_MIN_SCALE_FACTOR                 (13U)

/* MISRA.DEFINE.FUNC
 * MISRAC_2004_Rule_19.7
 * Function Like Macro definition
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Resizer is reconfigured almost every frame, so for performance reasons,
 * using macro instead of inline functions
 */
/**
 *  \brief Register macros
 */
#define RSZ_INST_EN(n)                          (0x78U + RSZ_INST_DIFF * (n))
#define RSZ_INST_MODE(n)                        (0x7cU + RSZ_INST_DIFF * (n))
#define RSZ_INST_420(n)                         (0x80U + RSZ_INST_DIFF * (n))
#define RSZ_INST_I_VPS(n)                       (0x84U + RSZ_INST_DIFF * (n))
#define RSZ_INST_I_HPS(n)                       (0x88U + RSZ_INST_DIFF * (n))
#define RSZ_INST_O_VSZ(n)                       (0x8cU + RSZ_INST_DIFF * (n))
#define RSZ_INST_O_HSZ(n)                       (0x90U + RSZ_INST_DIFF * (n))
#define RSZ_INST_V_PHS_Y(n)                     (0x94U + RSZ_INST_DIFF * (n))
#define RSZ_INST_V_PHS_C(n)                     (0x98U + RSZ_INST_DIFF * (n))
#define RSZ_INST_V_DIF(n)                       (0x9cU + RSZ_INST_DIFF * (n))
#define RSZ_INST_V_TYP(n)                       (0xa0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_V_LPF(n)                       (0xa4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_H_PHS(n)                       (0xa8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_H_PHS_ADJ(n)                   (0xacU + RSZ_INST_DIFF * (n))
#define RSZ_INST_H_DIF(n)                       (0xb0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_H_TYP(n)                       (0xb4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_H_LPF(n)                       (0xb8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_DWN_EN(n)                      (0xbcU + RSZ_INST_DIFF * (n))
#define RSZ_INST_DWN_AV(n)                      (0xc0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_RGB_EN(n)                      (0xc4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_RGB_TYP(n)                     (0xc8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_RGB_BLD(n)                     (0xccU + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_BAD_H(n)                 (0xd0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_BAD_L(n)                 (0xd4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_SAD_H(n)                 (0xd8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_SAD_L(n)                 (0xdcU + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_OFT(n)                   (0xe0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_PTR_S(n)                 (0xe4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_Y_PTR_E(n)                 (0xe8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_BAD_H(n)                 (0xecU + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_BAD_L(n)                 (0xf0U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_SAD_H(n)                 (0xf4U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_SAD_L(n)                 (0xf8U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_OFT(n)                   (0xfcU + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_PTR_S(n)                 (0x100U + RSZ_INST_DIFF * (n))
#define RSZ_INST_SDR_C_PTR_E(n)                 (0x104U + RSZ_INST_DIFF * (n))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalrszInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
} isshalrszInstObj_t;

typedef struct RszSizeConfig
{
    uint32_t inWidth;
    uint32_t inHeight;
    uint32_t outWidth;
    uint32_t outHeight;
} RszSizeConfig_t;

typedef struct RszScaleFactor
{
    uint32_t hRatio;
    uint32_t vRatio;
    uint32_t hAvgSize;
    uint32_t vAvgSize;
} RszScaleFactor_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t RszCheckConfigErrors(
    const isshalrszInstObj_t *instObj,
    const isshalrszConfig_t  *cfg);

static int32_t RszSetSrcConfig(
    const isshalrszInstObj_t   *instObj,
    const isshalrszSrcConfig_t *srcCfg);

static void RszSetCropConfig(const isshalrszInstObj_t *instObj,
                             const Fvid2_CropConfig   *cropWin);

static void RszEnableRszClk(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   instId,
    uint32_t                  flag);

static int32_t RszSetInstConfig(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   scInstId,
    const isshalrszConfig_t  *cfg);

static void RszSetIntensityConfig(
    const isshalrszInstObj_t    *instObj,
    vpsissRszScalerInstId_t      instId,
    const vpsissRszIntsConfig_t *intsCfg);

static void RszSetFilterConfig(
    const isshalrszInstObj_t    *instObj,
    vpsissRszScalerInstId_t      instId,
    const vpsissRszFiltConfig_t *filtCfg);

static void RszSetFlipConfig(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   instId,
    vpsissRszFlipCtrl_t       flipCtrl);

static int32_t RszCalcScaleFactor(
    const RszSizeConfig_t *size,
    vpsissRszScaleMode_t   scaleMode,
    RszScaleFactor_t      *factor);

static int32_t RszSetChromaConfig(
    const isshalrszInstObj_t *instObj,
    const isshalrszConfig_t  *cfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalrszInstObj_t      gIssHalRszInstObjs[ISSHAL_RSZ_MAX_INST] =
{(uint32_t)FALSE};

static const uint32_t          gIssHalRszAverageOut[RSZ_DOWN_SCALE_MAX_SIZE] =
{2, 4, 8, 16, 32, 64, 128, 256};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalRszDefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const isshalrszConfig_t gIssHalRszDefCfg =
{
    {
        FVID2_DF_BAYER_RAW,                    /* Input DataFormat */
        VPS_ISS_RSZ_OP_MODE_BYPASS,            /* Operation Mode */
        ISSHAL_RSZ_INP_SRC_IPIPE,              /* Input Source */
        {0x0U,  0x0U,  720U, 480U},            /* Input Crop Configuration */
        FALSE,                                 /* Write Enable */
        {0x0U,  0xFFU},                        /* Luma Clip */
        {0x0U,  0xFFU},                        /* chroma clip */
        FVID2_CHROMA_POS_COSITED,              /* Chroma Position */
        0U,                                    /* LowThr */
        0U,                                    /* HighThr */
        FALSE,                                 /* RszLuma */
    },
    1U,                                        /* Number of instances */
    {
        {
            TRUE,                              /* RSZ Instance */
            /* Output DataFormat*/
            {
                0U,
                720U, 480U,
                {1440U, 1440U, 1440U},
                {FALSE, FALSE, FALSE},
                FVID2_DF_YUV422I_UYVY,
                FVID2_SF_PROGRESSIVE,
                FVID2_BPP_BITS16,
                NULL
            },
            VPS_ISS_RSZ_STR_MODE_NORMAL,   /* No Flip */
            {0x0U,  0x0U},                 /* Start Position */
            VPS_ISS_RSZ_SCALE_MODE_NORMAL, /* Normal Scale mode */
            /* Filter Type */
            {
                VPS_ISS_RSZ_FILTER_4TAP_CUBIC, VPS_ISS_RSZ_FILTER_4TAP_CUBIC,
                VPS_ISS_RSZ_FILTER_4TAP_CUBIC, VPS_ISS_RSZ_FILTER_4TAP_CUBIC
            },
            /* Luma/Chroma Intensity */
            {0x0U,  0x0U,  0x0U, 0x0U},
            0xFF,                                /* Alpha */
            VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_AND_CHROMA
        },
        {
            FALSE,                              /* RSZ Instance */
            /* Output DataFormat*/
            {
                0U,
                720U, 480U,
                {1440U, 1440U, 1440U},
                {FALSE, FALSE, FALSE},
                FVID2_DF_YUV422I_UYVY,
                FVID2_SF_PROGRESSIVE,
                FVID2_BPP_BITS16,
                NULL
            },
            VPS_ISS_RSZ_STR_MODE_NORMAL,   /* No Flip */
            {0x0U,  0x0U},                 /* Start Position */
            VPS_ISS_RSZ_SCALE_MODE_NORMAL, /* Normal Scale mode */
            /* Filter Type */
            {
                VPS_ISS_RSZ_FILTER_4TAP_CUBIC, VPS_ISS_RSZ_FILTER_4TAP_CUBIC,
                VPS_ISS_RSZ_FILTER_4TAP_CUBIC, VPS_ISS_RSZ_FILTER_4TAP_CUBIC
            },
            /* Luma/Chroma Intensity */
            {0x0U,  0x0U,  0x0U, 0x0U},
            0xFF,                                /* Alpha */
            VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_AND_CHROMA
        }
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issrszInit(UInt32                       numInst,
                          const isshalrszInstParams_t *instPrms,
                          Ptr                          arg)
{
    uint32_t instCnt;
    isshalrszInstObj_t *instObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_RSZ_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (NULL != instPrms));
        GT_assert(VpsHalTrace,
                  (instPrms->instId < ISSHAL_RSZ_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms->baseAddress));

        instObj = &gIssHalRszInstObjs[instCnt];

        if((uint32_t)FALSE == instObj->isInitDone)
        {
            instObj->openCnt     = 0U;
            instObj->instId      = instPrms->instId;
            instObj->baseAddress = instPrms->baseAddress;
            instObj->isInitDone  = (uint32_t)TRUE;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * rsz number of instances. The size of this number of instances
         * is never more than ISSHAL_RSZ_INST_MAX_ID.
         */
        instPrms++;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_issrszDeInit
 *  \brief RSZ HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issrszDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalrszInstObj_t *instObj;

    for(instCnt = 0U; instCnt < ISSHAL_RSZ_INST_MAX_ID; instCnt++)
    {
        instObj = &gIssHalRszInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == instObj->openCnt));

        instObj->instId      = 0x0U;
        instObj->baseAddress = 0x0U;
        instObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

/**
 *  VpsHal_issrszOpen
 *  \brief This function should be called prior to calling any of the RSZ HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issrszOpen(const isshalOpenParams_t *openPrms,
                                Ptr                       arg)
{
    uint32_t            instCnt;
    VpsHal_Handle       handle  = NULL;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_RSZ_MAX_INST; instCnt++)
    {
        instObj = &(gIssHalRszInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == instObj->instId)
        {
            handle = (VpsHal_Handle) (instObj);

            /* Enable the Module clock when opened first time */
            if(0 == instObj->openCnt)
            {
                /* Enable Resizer clk at ISS */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK ==
                     VpsHal_issEnableModule(ISSHAL_ISS_MODULE_RSZ,
                                            (uint32_t) TRUE)));

                /* Enable register access clocks */
                HW_WR_REG32(instObj->baseAddress + RSZ_GCK_MMR,
                            RSZ_GCK_MMR_MASK);

                /* Set the clock to be free running
                 * TODO: Change it according to power requirement */
                HW_WR_REG32(instObj->baseAddress + RSZ_SYSCONFIG,
                            HW_RD_REG32(instObj->baseAddress + RSZ_SYSCONFIG) &
                            ~((UInt32) RSZ_SYSCONFIG_AUTOGATING_MASK));
            }

            instObj->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_issrszClose
 *  \brief This functions closes the rsz handle and after call to this
 *  function, rsz handle is not valid.
 *
 *  \param handle         Requested RSZ instance
 */
int32_t VpsHal_issrszClose(VpsHal_Handle handle,
                           Ptr           arg)
{
    int32_t  status = FVID2_EFAIL;
    isshalrszInstObj_t *instObj = NULL;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    /* Decrement the open count */
    if(instObj->openCnt > 0)
    {
        instObj->openCnt--;

        if(0U == instObj->openCnt)
        {
            /* Disable both the Resizer instance */
            regVal  = HW_RD_REG32(instObj->baseAddress + RZA_EN);
            regVal &= ~((UInt32) RZA_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + RZA_EN, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + RZB_EN);
            regVal &= ~((UInt32) RZB_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + RZB_EN, regVal);

            regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_EN);
            regVal &= ~((UInt32) RSZ_SRC_EN_MASK);
            HW_WR_REG32(instObj->baseAddress + RSZ_SRC_EN, regVal);

            RszEnableRszClk(instObj, VPS_ISS_RSZ_SCALER_A, (uint32_t) FALSE);
            RszEnableRszClk(instObj, VPS_ISS_RSZ_SCALER_B, (uint32_t) FALSE);

            /* Disable register access clocks */
            regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_GCK_MMR);
            regVal &= ~((UInt32) RSZ_GCK_MMR_MASK);
            HW_WR_REG32(instObj->baseAddress + RSZ_GCK_MMR, regVal);

            /* Disable Resizer Module at the ISS level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK ==
                 VpsHal_issEnableModule(ISSHAL_ISS_MODULE_RSZ,
                                        (uint32_t) FALSE)));
        }

        status = FVID2_SOK;
    }

    return (status);
}

/**
 *  \brief Sets the entire RSZ configuration to the RSZ registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issrszConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issrszSetConfig(VpsHal_Handle            handle,
                               const isshalrszConfig_t *cfg,
                               Ptr                      arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t instCnt;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instObj = (isshalrszInstObj_t *) handle;

    /* Check For Errors */
    status = RszCheckConfigErrors(instObj, cfg);

    if(FVID2_SOK == status)
    {
        status = RszSetSrcConfig(instObj, &cfg->srcCfg);
    }

    if(FVID2_SOK == status)
    {
        for(instCnt = 0U; instCnt < VPS_ISS_RSZ_SCALER_MAX; instCnt++)
        {
            if(TRUE == cfg->instCfg[instCnt].enable)
            {
                status = RszSetInstConfig(
                    instObj,
                    (vpsissRszScalerInstId_t)instCnt,
                    cfg);
            }
        }
    }

    return (status);
}

int32_t VpsHal_issrszGetConfig(VpsHal_Handle handle, isshalrszConfig_t *config)
{
    return (FVID2_SOK);
}

int32_t VpsHal_issrszControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalrszInstObj_t *instObj = NULL;
    isshalrszInputSrc_t inSrc;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    switch(cmd)
    {
        case ISSHAL_IOCTL_RSZ_SET_INSRC:
            if(NULL != cmdArgs)
            {
                inSrc = *(isshalrszInputSrc_t *) cmdArgs;

                /* Set the input Source in the FMT0 register */
                regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0);
                regVal &= ~((UInt32) RSZ_SRC_FMT0_SEL_MASK);
                if(ISSHAL_RSZ_INP_SRC_IPIPEIF == inSrc)
                {
                    regVal |= RSZ_SRC_FMT0_SEL_MASK;
                }
                HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0, regVal);
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        case ISSHAL_IOCTL_RSZ_SET_CHROMA_PROCCFG:
            status = RszSetChromaConfig(instObj, (isshalrszConfig_t *) cmdArgs);
            break;

        case ISSHAL_IOCTL_RSZ_GET_DEFAULTCFG:
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    ((isshalrszConfig_t *) cmdArgs),
                    &gIssHalRszDefCfg,
                    sizeof(isshalrszConfig_t));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
        {
            isshalissBlankingInfo_t *blankInfo =
                (isshalissBlankingInfo_t *) cmdArgs;
            isshalrszConfig_t       *cfg = (isshalrszConfig_t *) arg;

            GT_assert(VpsHalTrace, (NULL != cfg));
            GT_assert(VpsHalTrace, (NULL != blankInfo));

            /* TODO: change this blanking requirement based
             *       on the configuration.
             *       Currently Set to maximm */
            blankInfo->hBlank = 8U;
            blankInfo->vBlank = 4U;

            break;
        }
        case VPS_HAL_ISS_IOCTL_START:
        {
            issCtrlProcMode_t procMode;

            /* NULL Parameter Check */
            GT_assert(VpsHalTrace, (NULL != cmdArgs));

            procMode = *(issCtrlProcMode_t *)cmdArgs;

            /* Set the processing mode */
            regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_MODE);
            regVal &= ~((UInt32) RSZ_SRC_MODE_OST_MASK);
            if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
            {
                regVal |= RSZ_SRC_MODE_OST_MASK;
            }
            HW_WR_REG32(instObj->baseAddress + RSZ_SRC_MODE, regVal);

            HW_WR_REG32(instObj->baseAddress + RSZ_SRC_EN,
                        HW_RD_REG32(instObj->baseAddress + RSZ_SRC_EN) |
                        RSZ_SRC_EN_MASK);
            break;
        }
        case VPS_HAL_ISS_IOCTL_STOP:
        {
            /* Disable RSZ */
            HW_WR_REG32(instObj->baseAddress + RSZ_SRC_EN,
                        HW_RD_REG32(instObj->baseAddress + RSZ_SRC_EN) &
                        ~((UInt32) RSZ_SRC_EN_MASK));
            break;
        }
        default:
            status = FVID2_EUNSUPPORTED_CMD;
            break;
    }

    return (status);
}

int32_t VpsHal_issrszSetAddress(VpsHal_Handle           handle,
                                vpsissRszScalerInstId_t instId,
                                Ptr                     lumaAddr,
                                Ptr                     chromaAddr,
                                uint32_t                lumaPitch,
                                uint32_t                chromaPitch)
{
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for  setting memory
     * mapped register
     */
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_BAD_H(instId),
                ((uint32_t) lumaAddr >> 16U) & RZA_SDR_Y_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_BAD_L(instId),
                (uint32_t) lumaAddr & RZA_SDR_Y_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_SAD_H(instId),
                ((uint32_t) lumaAddr >> 16U) & RZA_SDR_Y_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_SAD_L(instId),
                (uint32_t) lumaAddr & RZA_SDR_Y_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_PTR_S(instId), 0x0U);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_PTR_E(instId),
                RZA_SDR_Y_PTR_E_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_Y_OFT(instId),
                (lumaPitch << RZA_SDR_Y_OFT_SHIFT) & RZA_SDR_Y_OFT_MASK);

    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_BAD_H(instId),
                ((uint32_t) chromaAddr >> 16U) & RZA_SDR_C_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_BAD_L(instId),
                (uint32_t) chromaAddr & RZA_SDR_C_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_SAD_H(instId),
                ((uint32_t) chromaAddr >> 16U) & RZA_SDR_C_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_SAD_L(instId),
                (uint32_t) chromaAddr & RZA_SDR_C_BAD_H_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_PTR_S(instId), 0x0U);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_PTR_E(instId),
                RZA_SDR_C_PTR_E_MASK);
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_SDR_C_OFT(instId),
                (chromaPitch << RZA_SDR_C_OFT_SHIFT) & RZA_SDR_C_OFT_MASK);

    return (FVID2_SOK);
}

int32_t VpsHal_issrszStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    uint32_t regVal;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_MODE);
    regVal &= ~((UInt32) RSZ_SRC_MODE_OST_MASK);
    if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
    {
        regVal |= RSZ_SRC_MODE_OST_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_MODE, regVal);

    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_EN,
                HW_RD_REG32(instObj->baseAddress + RSZ_SRC_EN) |
                RSZ_SRC_EN_MASK);

    return (FVID2_SOK);
}

int32_t VpsHal_issrszStartInst(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t instId,
    issCtrlProcMode_t       procMode,
    Ptr                     arg)
{
    uint32_t regVal;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_MODE(instId));
    regVal &= ~((UInt32) RZA_MODE_MASK);
    if(ISSHAL_ISS_PROC_MODE_ONE_SHOT == procMode)
    {
        regVal |= RZA_MODE_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_MODE(instId), regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_EN(instId));
    regVal |= RZA_EN_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_EN(instId), regVal);

    return (FVID2_SOK);
}

int32_t VpsHal_issrszStop(VpsHal_Handle handle, Ptr arg)
{
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_EN,
                HW_RD_REG32(instObj->baseAddress + RSZ_SRC_EN) &
                    ~((UInt32) RSZ_SRC_EN_MASK));

    return (FVID2_SOK);
}

int32_t VpsHal_issrszStopInst(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t instId)
{
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    HW_WR_REG32(instObj->baseAddress + RSZ_INST_EN(instId),
                HW_RD_REG32(instObj->baseAddress + RSZ_INST_EN(
                                instId)) & ~((UInt32) RZA_EN_MASK));

    return (FVID2_SOK);
}

int32_t VpsHal_issrszSetFractClkDiv(VpsHal_Handle handle, uint32_t fractClk)
{
    int32_t status = FVID2_SOK;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    if(fractClk > (RSZ_FRACDIV_MASK >> RSZ_FRACDIV_SHIFT))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        HW_WR_REG32(instObj->baseAddress + RSZ_FRACDIV,
                    (fractClk << RSZ_FRACDIV_SHIFT) & RSZ_FRACDIV_MASK);
    }

    return (status);
}

/* Function to Fifo threshold level, depending on this level, stall signal
 * is generated */
int32_t VpsHal_issrszSetFifoThresholdLevel(
    VpsHal_Handle handle,
    uint32_t      highThrLevel,
    uint32_t      lowThrLevel)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    if((highThrLevel >
        (RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK >>
         RSZ_IN_FIFO_CTRL_THRLD_HIGH_SHIFT)) ||
       (lowThrLevel >
        (RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK >>
         RSZ_IN_FIFO_CTRL_THRLD_LOW_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_IN_FIFO_CTRL);
        regVal &= ~(RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK |
                    RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK);
        regVal |= (lowThrLevel << RSZ_IN_FIFO_CTRL_THRLD_LOW_SHIFT) &
                  RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK;
        regVal |= (highThrLevel << RSZ_IN_FIFO_CTRL_THRLD_HIGH_SHIFT) &
                  RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK;
        HW_WR_REG32(instObj->baseAddress + RSZ_IN_FIFO_CTRL, regVal);
    }

    return (status);
}

/* Function to set two consecutive two read dma interval */
int32_t VpsHal_issrszSetBwLimit(
    VpsHal_Handle           handle,
    vpsissRszScalerInstId_t scaleInstId,
    uint32_t                dmaInt)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalrszInstObj_t *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instObj = (isshalrszInstObj_t *) handle;

    if(dmaInt > ((RSZ_DMA_RZA_MASK >> RSZ_DMA_RZA_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        if(VPS_ISS_RSZ_SCALER_A == scaleInstId)
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_DMA_RZA);
            regVal &= ~((UInt32) RSZ_DMA_RZA_MASK);
            regVal |= (dmaInt << RSZ_DMA_RZA_SHIFT) & RSZ_DMA_RZA_MASK;
            HW_WR_REG32(instObj->baseAddress + RSZ_DMA_RZA, regVal);
        }
        else /* Resizer Instance B */
        {
            regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_DMA_RZB);
            regVal &= ~((UInt32) RSZ_DMA_RZB_MASK);
            regVal |= (dmaInt << RSZ_DMA_RZB_SHIFT) & RSZ_DMA_RZB_MASK;
            HW_WR_REG32(instObj->baseAddress + RSZ_DMA_RZB, regVal);
        }
    }

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t RszCheckConfigErrors(
    const isshalrszInstObj_t *instObj,
    const isshalrszConfig_t  *cfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t instCnt;
    uint32_t isRgbOutput;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != cfg));

    if(VPS_ISS_RSZ_SCALER_MAX < cfg->numInst)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((FVID2_DF_YUV420SP_UV != cfg->srcCfg.inputDataFormat) &&
       ((int32_t)FALSE == Fvid2_isDataFmtBayer(cfg->srcCfg.inputDataFormat)) &&
       (FVID2_DF_YUV422I_UYVY != cfg->srcCfg.inputDataFormat))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((0U == cfg->srcCfg.procWin.cropWidth) ||
       (0U == cfg->srcCfg.procWin.cropHeight))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((0U != (cfg->srcCfg.procWin.cropStartX % 2U)) ||
       (0U != (cfg->srcCfg.procWin.cropWidth % 2U)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(((int32_t)TRUE == Fvid2_isDataFmtBayer(cfg->srcCfg.inputDataFormat)) &&
       (VPS_ISS_RSZ_OP_MODE_RESIZING == cfg->srcCfg.opMode))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    /* RGB output can be enabled only for YUV422 input */
    isRgbOutput = (uint32_t)FALSE;
    for(instCnt = 0U; instCnt < VPS_ISS_RSZ_SCALER_MAX; instCnt++)
    {
        if(TRUE == cfg->instCfg[instCnt].enable)
        {
            if(((int32_t)TRUE ==
                Fvid2_isDataFmtBayer(cfg->instCfg[instCnt].outFmt.
                                     dataFormat)) &&
               ((int32_t)FALSE ==
                Fvid2_isDataFmtBayer(cfg->srcCfg.inputDataFormat)))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if(((int32_t)FALSE ==
                Fvid2_isDataFmtBayer(cfg->instCfg[instCnt].outFmt.
                                     dataFormat)) &&
               (FVID2_DF_YUV422I_UYVY !=
                cfg->instCfg[instCnt].outFmt.dataFormat) &&
               (FVID2_DF_YUV420SP_UV != cfg->instCfg[instCnt].outFmt.
                dataFormat) &&
               (FVID2_DF_RGB16_565 != cfg->instCfg[instCnt].outFmt.
                dataFormat) &&
               (FVID2_DF_ARGB32_8888 != cfg->instCfg[instCnt].outFmt.
                dataFormat))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if((FVID2_DF_RGB16_565 == cfg->instCfg[instCnt].outFmt.
                dataFormat) ||
               (FVID2_DF_ARGB32_8888 == cfg->instCfg[instCnt].outFmt.
                dataFormat))
            {
                isRgbOutput = (uint32_t)TRUE;
            }

            /* Output Frame width has to be even */
            if(0U != (cfg->instCfg[instCnt].outFmt.width % 2U))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if(RSZ_INST_MAX_WIDTH(instCnt) <
               cfg->instCfg[instCnt].outFmt.width)
            {
                status = FVID2_EINVALID_PARAMS;
            }

            /* Flipping is not supported on RGB Formats */
            if((VPS_ISS_RSZ_STR_MODE_NORMAL != cfg->instCfg[instCnt].flipCtrl)
               &&
               ((FVID2_DF_RGB16_565 == cfg->instCfg[instCnt].outFmt.
                 dataFormat) ||
                (FVID2_DF_ARGB32_8888 == cfg->instCfg[instCnt].outFmt.
                 dataFormat)))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if(((uint32_t)TRUE == isRgbOutput) &&
       (FVID2_DF_YUV422I_UYVY != cfg->srcCfg.inputDataFormat))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    return (status);
}

static int32_t RszSetInstConfig(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   scInstId,
    const isshalrszConfig_t  *cfg)
{
    int32_t          status = FVID2_SOK;
    uint32_t         instId;
    uint32_t         regVal;
    const vpsissRszInstConfig_t    *instCfg;
    RszSizeConfig_t  sizeCfg;
    RszScaleFactor_t factorCfg;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instCfg = &cfg->instCfg[scInstId];

    sizeCfg.inWidth = cfg->srcCfg.procWin.cropWidth -
                      instCfg->startPos.startX;
    sizeCfg.inHeight = cfg->srcCfg.procWin.cropHeight -
                       instCfg->startPos.startY;
    sizeCfg.outWidth  = instCfg->outFmt.width;
    sizeCfg.outHeight = instCfg->outFmt.height;

    status = RszCalcScaleFactor(&sizeCfg, instCfg->scaleMode, &factorCfg);

    if((uint32_t)TRUE == instCfg->overrideScaleFactor)
    {
        if((instCfg->hRatio > RSZ_NORMAL_MAX_SCALE_FACTOR) ||
           (instCfg->vRatio > RSZ_NORMAL_MAX_SCALE_FACTOR))
        {
            status = FVID2_EOUT_OF_RANGE;
        }
        else
        {
            factorCfg.hRatio = instCfg->hRatio;
            factorCfg.vRatio = instCfg->vRatio;
        }
    }
    if(FVID2_SOK == status)
    {
        /* Enable Resizer instance clock */
        RszEnableRszClk(instObj, scInstId, (uint32_t) TRUE);

        instId = scInstId;

        /* Set the Luma/Chroma Horizontal/Vertical Intensity */
        RszSetIntensityConfig(instObj, scInstId, &instCfg->intensityCfg);

        /* Set the algo type for luma/chroma on horizontal/vertical direction */
        RszSetFilterConfig(instObj, scInstId, &instCfg->filtCfg);

        /* Enable RGB Output */
        if((FVID2_DF_RGB16_565 == instCfg->outFmt.dataFormat) ||
           (FVID2_DF_ARGB32_8888 == instCfg->outFmt.dataFormat))
        {
            HW_WR_REG32(instObj->baseAddress + RSZ_INST_RGB_EN(instId),
                        HW_RD_REG32(instObj->baseAddress +
                                    RSZ_INST_RGB_EN(instId)) |
                        RZA_RGB_EN_MASK);

            if(FVID2_DF_ARGB32_8888 == instCfg->outFmt.dataFormat)
            {
                HW_WR_REG32(instObj->baseAddress + RSZ_INST_RGB_TYP(instId),
                            HW_RD_REG32(
                                instObj->baseAddress + RSZ_INST_RGB_TYP(
                                    instId)) &
                            ~((UInt32) RZA_RGB_TYP_MASK));

                HW_WR_REG32(instObj->baseAddress + RSZ_INST_RGB_BLD(instId),
                            (instCfg->alpha << RZA_RGB_BLD_SHIFT) &
                            RZA_RGB_BLD_MASK);
            }
            else
            {
                HW_WR_REG32(instObj->baseAddress + RSZ_INST_RGB_TYP(instId),
                            HW_RD_REG32(instObj->baseAddress +
                                        RSZ_INST_RGB_TYP(instId)) |
                            RZA_RGB_TYP_MASK);
            }
        }
        else
        {
            HW_WR_REG32(instObj->baseAddress + RSZ_INST_RGB_EN(instId),
                        HW_RD_REG32(instObj->baseAddress +
                                    RSZ_INST_RGB_EN(instId)) &
                        ~((UInt32) RZA_RGB_EN_MASK));
        }

        /* Select the flip parameters */
        RszSetFlipConfig(instObj, scInstId, instCfg->flipCtrl);

        if(FVID2_DF_YUV420SP_UV == cfg->srcCfg.inputDataFormat)
        {
            /* Output should be YUV420 only */
            GT_assert(VpsHalTrace,
                      (FVID2_DF_YUV420SP_UV == instCfg->outFmt.dataFormat));

            if((TRUE == cfg->srcCfg.rszLuma) ||
               (VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_ONLY == instCfg->yuvRszMode))
            {
                regVal = HW_RD_REG32(instObj->baseAddress +
                                     RSZ_INST_420(instId));
                regVal &= ~((UInt32) (RZA_420_YEN_MASK | RZA_420_CEN_MASK));
                regVal |= RZA_420_YEN_MASK;
                HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                            regVal);
            }
            else
            {
                regVal = HW_RD_REG32(instObj->baseAddress +
                                     RSZ_INST_420(instId));
                regVal &= ~((UInt32) (RZA_420_YEN_MASK | RZA_420_CEN_MASK));
                regVal |= RZA_420_CEN_MASK;
                HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                            regVal);
            }
        }
        else
        {
            /* Select the YUV420 output */
            if(FVID2_DF_YUV420SP_UV == instCfg->outFmt.dataFormat)
            {
                if(VPS_ISS_RSZ_YUV_RSZ_MODE_LUMA_ONLY == instCfg->yuvRszMode)
                {
                    HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                                HW_RD_REG32(instObj->baseAddress +
                                            RSZ_INST_420(instId)) |
                                RZA_420_YEN_MASK);
                }
                else if(VPS_ISS_RSZ_YUV_RSZ_MODE_CHROMA_ONLY ==
                        instCfg->yuvRszMode)
                {
                    HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                                HW_RD_REG32(instObj->baseAddress +
                                            RSZ_INST_420(instId)) |
                                RZA_420_CEN_MASK);
                }
                else
                {
                    HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                                HW_RD_REG32(instObj->baseAddress +
                                            RSZ_INST_420(instId)) |
                                RZA_420_YEN_MASK | RZA_420_CEN_MASK);
                }
            }
            else
            {
                HW_WR_REG32(instObj->baseAddress + RSZ_INST_420(instId),
                            HW_RD_REG32(instObj->baseAddress +
                                        RSZ_INST_420(instId)) &
                            ~((UInt32) (RZA_420_YEN_MASK | RZA_420_CEN_MASK)));
            }
        }

        /* Set the start position */
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_I_VPS(
                        instId),
                    (instCfg->startPos.startY <<
                     RZA_I_VPS_SHIFT) & RZA_I_VPS_MASK);
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_I_HPS(
                        instId),
                    (instCfg->startPos.startX <<
                     RZA_I_HPS_SHIFT) & RZA_I_HPS_MASK);

        /* Set the output size */
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_O_VSZ(instId),
                    (((UInt32) (instCfg->outFmt.height - 1U)) <<
                     RZA_O_VSZ_SHIFT) &
                    RZA_O_VSZ_MASK);
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_O_HSZ(instId),
                    (instCfg->outFmt.width - 1U) &
                    RZA_O_HSZ_MASK);

        /* Select the Horizontal/Vertical Ratio */
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_V_DIF(instId),
                    (factorCfg.vRatio << RZA_V_DIF_SHIFT) & RZA_V_DIF_MASK);
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_H_DIF(instId),
                    (factorCfg.hRatio << RZA_H_DIF_SHIFT) & RZA_H_DIF_MASK);

        /* Set the Down Scale Average Size */
        regVal = (factorCfg.hAvgSize << RZA_DWN_AV_H_SHIFT) &
                 RZA_DWN_AV_H_MASK;
        regVal |= (factorCfg.vAvgSize << RZA_DWN_AV_V_SHIFT) &
                  RZA_DWN_AV_V_MASK;
        HW_WR_REG32(instObj->baseAddress + RSZ_INST_DWN_AV(instId), regVal);

        /* TODO: Select the down scale rescale method */
        if(VPS_ISS_RSZ_SCALE_MODE_NORMAL == instCfg->scaleMode)
        {
            HW_WR_REG32(instObj->baseAddress + RSZ_INST_DWN_EN(instId),
                        HW_RD_REG32(instObj->baseAddress +
                                    RSZ_INST_DWN_EN(instId)) &
                        ~((UInt32) RZA_DWN_EN_MASK));
        }
        else
        {
            HW_WR_REG32(instObj->baseAddress + RSZ_INST_DWN_EN(instId),
                        HW_RD_REG32(instObj->baseAddress +
                                    RSZ_INST_DWN_EN(instId)) |
                        RZA_DWN_EN_MASK);
        }
    }

    return (status);
}

static int32_t RszSetSrcConfig(
    const isshalrszInstObj_t   *instObj,
    const isshalrszSrcConfig_t *srcCfg)
{
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != srcCfg));

    /* Select the input source */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0);
    regVal &= ~((UInt32) RSZ_SRC_FMT0_SEL_MASK);
    if(ISSHAL_RSZ_INP_SRC_IPIPEIF == srcCfg->inpSrc)
    {
        regVal |= RSZ_SRC_FMT0_SEL_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0, regVal);

    /* Configure the cropping/processing window */
    RszSetCropConfig(instObj, &srcCfg->procWin);

    /* Set the write enable signal */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_MODE);
    regVal &= ~((UInt32) RSZ_SRC_MODE_WRT_MASK);
    if(TRUE == srcCfg->wrtEnable)
    {
        regVal |= RSZ_SRC_MODE_WRT_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_MODE, regVal);

    /* Set the clipping value for the luma */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_YUV_Y_MIN);
    regVal &= ~((UInt32) RSZ_YUV_Y_MIN_MASK);
    regVal |= (srcCfg->lumaClip.min << RSZ_YUV_Y_MIN_SHIFT) &
              RSZ_YUV_Y_MIN_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_YUV_Y_MIN, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_YUV_Y_MAX);
    regVal &= ~((UInt32) RSZ_YUV_Y_MAX_MASK);
    regVal |= (srcCfg->lumaClip.max << RSZ_YUV_Y_MAX_SHIFT) &
              RSZ_YUV_Y_MAX_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_YUV_Y_MAX, regVal);

    /* Set the clipping value for the luma */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_YUV_C_MIN);
    regVal &= ~((UInt32) RSZ_YUV_C_MIN_MASK);
    regVal |= (srcCfg->chromaClip.min << RSZ_YUV_C_MIN_SHIFT) &
              RSZ_YUV_C_MIN_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_YUV_C_MIN, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_YUV_C_MAX);
    regVal &= ~((UInt32) RSZ_YUV_C_MAX_MASK);
    regVal |= (srcCfg->chromaClip.max << RSZ_YUV_C_MAX_SHIFT) &
              RSZ_YUV_C_MAX_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_YUV_C_MAX, regVal);

    /* Set the Resizer Operation Mode */
    if(VPS_ISS_RSZ_OP_MODE_BYPASS == srcCfg->opMode)
    {
        HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0,
                    HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0) &
                    ~((UInt32) RSZ_SRC_FMT0_BYPASS_MASK));
        HW_WR_REG32(instObj->baseAddress + RSZ_GCK_SDR,
                    HW_RD_REG32(instObj->baseAddress + RSZ_GCK_SDR) &
                    ~((UInt32) RSZ_GCK_SDR_CORE_MASK));
    }
    else if(VPS_ISS_RSZ_OP_MODE_PASSTHRU == srcCfg->opMode)
    {
        HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0,
                    HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0) |
                    RSZ_SRC_FMT0_BYPASS_MASK);
        HW_WR_REG32(instObj->baseAddress + RSZ_GCK_SDR,
                    HW_RD_REG32(instObj->baseAddress + RSZ_GCK_SDR) &
                    ~((UInt32) RSZ_GCK_SDR_CORE_MASK));
    }
    else
    {
        HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0,
                    HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0) &
                    ~((UInt32) RSZ_SRC_FMT0_BYPASS_MASK));
        HW_WR_REG32(instObj->baseAddress + RSZ_GCK_SDR,
                    HW_RD_REG32(instObj->baseAddress + RSZ_GCK_SDR) |
                    RSZ_GCK_SDR_CORE_MASK);
    }

    /* Set the YUV420 input format */
    regVal = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT1);

    /*  IN420   COL
        1       0       Y is valid and processed
        1       1       UV is valid and processed */
    regVal &= ~((UInt32) (RSZ_SRC_FMT1_IN420_MASK | RSZ_SRC_FMT1_COL_MASK));
    if(FVID2_DF_YUV420SP_UV == srcCfg->inputDataFormat)
    {
        if(FALSE == srcCfg->rszLuma)
        {
            regVal |= RSZ_SRC_FMT1_COL_MASK;
        }
        regVal |= RSZ_SRC_FMT1_IN420_MASK;
    }

    regVal &= ~((UInt32) RSZ_SRC_FMT1_RAW_MASK);
    if((int32_t)TRUE == Fvid2_isDataFmtBayer(srcCfg->inputDataFormat))
    {
        regVal |= RSZ_SRC_FMT1_RAW_MASK;
    }

    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT1, regVal);

    /* Set the Chroma Position */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_YUV_PHS);
    regVal &= ~((UInt32) RSZ_YUV_PHS_POS_MASK);
    if(FVID2_CHROMA_POS_CENTERED == srcCfg->chromaPos)
    {
        regVal |= RSZ_YUV_PHS_POS_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_YUV_PHS, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_IN_FIFO_CTRL);
    regVal &= ~(RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK|
                RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK);
    regVal |= (srcCfg->thrHigh << RSZ_IN_FIFO_CTRL_THRLD_HIGH_SHIFT) &
              RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK;
    regVal |= (srcCfg->thrLow << RSZ_IN_FIFO_CTRL_THRLD_LOW_SHIFT)  &
              RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_IN_FIFO_CTRL, regVal);

    return (FVID2_SOK);
}

static void RszSetCropConfig(const isshalrszInstObj_t *instObj,
                             const Fvid2_CropConfig   *cropWin)
{
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != cropWin));

    /* Below Register is not shadowed */
    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_VPS);
    regVal &= ~((UInt32) RSZ_SRC_VPS_MASK);
    regVal |= (cropWin->cropStartY << RSZ_SRC_VPS_SHIFT) &
              RSZ_SRC_VPS_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_VPS, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_VSZ);
    regVal &= ~((UInt32) RSZ_SRC_VSZ_MASK);
    regVal |= (((UInt32) (cropWin->cropHeight - 1U)) << RSZ_SRC_VSZ_SHIFT) &
              RSZ_SRC_VSZ_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_VSZ, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_HPS);
    regVal &= ~((UInt32) RSZ_SRC_HPS_MASK);
    regVal |= (cropWin->cropStartX << RSZ_SRC_HPS_SHIFT) &
              RSZ_SRC_HPS_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_HPS, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_HSZ);
    regVal &= ~((UInt32) RSZ_SRC_HSZ_MASK);
    regVal |= (((UInt32) (cropWin->cropWidth - 1U)) << RSZ_SRC_HSZ_SHIFT) &
              RSZ_SRC_HSZ_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_HSZ, regVal);
}

static void RszEnableRszClk(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   instId,
    uint32_t                  flag)
{
    uint32_t regVal;

    if(VPS_ISS_RSZ_SCALER_A == instId)
    {
        regVal = HW_RD_REG32(instObj->baseAddress + RSZ_SYSCONFIG);

        if(TRUE == flag)
        {
            regVal |= RSZ_SYSCONFIG_RSZA_CLK_EN_MASK;
        }
        else
        {
            regVal &= ~((UInt32) RSZ_SYSCONFIG_RSZA_CLK_EN_MASK);
        }

        HW_WR_REG32(instObj->baseAddress + RSZ_SYSCONFIG, regVal);
    }
    else
    {
        regVal = HW_RD_REG32(instObj->baseAddress + RSZ_SYSCONFIG);

        if(TRUE == flag)
        {
            regVal |= RSZ_SYSCONFIG_RSZB_CLK_EN_MASK;
        }
        else
        {
            regVal &= ~((UInt32) RSZ_SYSCONFIG_RSZB_CLK_EN_MASK);
        }

        HW_WR_REG32(instObj->baseAddress + RSZ_SYSCONFIG, regVal);
    }
}

static void RszSetFlipConfig(
    const isshalrszInstObj_t *instObj,
    vpsissRszScalerInstId_t   instId,
    vpsissRszFlipCtrl_t       flipCtrl)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(instObj->baseAddress + RSZ_SEQ);
    if(VPS_ISS_RSZ_SCALER_A == instId)
    {
        regVal &= ~((UInt32) (RSZ_SEQ_HRVA_MASK | RSZ_SEQ_VRVA_MASK));

        if(VPS_ISS_RSZ_STR_MODE_HFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_HRVA_MASK;
        }
        else if(VPS_ISS_RSZ_STR_MODE_VFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_VRVA_MASK;
        }
        else if(VPS_ISS_RSZ_STR_MODE_HFLIP_VFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_HRVA_MASK | RSZ_SEQ_VRVA_MASK;
        }
        else
        {
            regVal &= ~((UInt32) (RSZ_SEQ_HRVA_MASK | RSZ_SEQ_VRVA_MASK));
        }
    }
    else
    {
        regVal &= ~((UInt32) (RSZ_SEQ_HRVB_MASK | RSZ_SEQ_VRVB_MASK));

        if(VPS_ISS_RSZ_STR_MODE_HFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_HRVB_MASK;
        }
        else if(VPS_ISS_RSZ_STR_MODE_VFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_VRVB_MASK;
        }
        else if(VPS_ISS_RSZ_STR_MODE_HFLIP_VFLIP == flipCtrl)
        {
            regVal |= RSZ_SEQ_HRVB_MASK | RSZ_SEQ_VRVB_MASK;
        }
        else
        {
            regVal &= ~((UInt32) (RSZ_SEQ_HRVB_MASK | RSZ_SEQ_VRVB_MASK));
        }
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_SEQ, regVal);
}

static void RszSetIntensityConfig(
    const isshalrszInstObj_t    *instObj,
    vpsissRszScalerInstId_t      instId,
    const vpsissRszIntsConfig_t *intsCfg)
{
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != intsCfg));

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_V_LPF(instId));
    regVal &= ~((UInt32) (RZA_V_LPF_Y_MASK | RZA_V_LPF_C_MASK));
    regVal |= (intsCfg->vertLumaIntensity << RZA_V_LPF_Y_SHIFT) &
              RZA_V_LPF_Y_MASK;
    regVal |= (intsCfg->vertChromaIntensity << RZA_V_LPF_C_SHIFT) &
              RZA_V_LPF_C_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_V_LPF(instId), regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_H_LPF(instId));
    regVal &= ~((UInt32) (RZA_H_LPF_Y_MASK | RZA_H_LPF_C_MASK));
    regVal |= (intsCfg->horzLumaIntensity << RZA_H_LPF_Y_SHIFT) &
              RZA_H_LPF_Y_MASK;
    regVal |= (intsCfg->horzChromaIntensity << RZA_H_LPF_C_SHIFT) &
              RZA_H_LPF_C_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_H_LPF(instId), regVal);
}

static void RszSetFilterConfig(
    const isshalrszInstObj_t    *instObj,
    vpsissRszScalerInstId_t      instId,
    const vpsissRszFiltConfig_t *filtCfg)
{
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instObj));
    GT_assert(VpsHalTrace, (NULL != filtCfg));

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_H_TYP(instId));
    regVal &= ~((UInt32) (RZA_H_TYP_Y_MASK | RZA_H_TYP_C_MASK));
    if(VPS_ISS_RSZ_FILTER_2TAP_LINEAR == filtCfg->horzLumaFilter)
    {
        regVal |= RZA_H_TYP_Y_MASK;
    }
    if(VPS_ISS_RSZ_FILTER_2TAP_LINEAR == filtCfg->horzChromaFilter)
    {
        regVal |= RZA_H_TYP_C_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_H_TYP(instId), regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_INST_V_TYP(instId));
    regVal &= ~((UInt32) (RZA_V_TYP_Y_MASK | RZA_V_TYP_C_MASK));
    if(VPS_ISS_RSZ_FILTER_2TAP_LINEAR == filtCfg->vertLumaFilter)
    {
        regVal |= RZA_V_TYP_Y_MASK;
    }
    if(VPS_ISS_RSZ_FILTER_2TAP_LINEAR == filtCfg->vertChromaFilter)
    {
        regVal |= RZA_V_TYP_C_MASK;
    }
    HW_WR_REG32(instObj->baseAddress + RSZ_INST_V_TYP(instId), regVal);
}

static int32_t RszCalcScaleFactor(
    const RszSizeConfig_t *size,
    vpsissRszScaleMode_t   scaleMode,
    RszScaleFactor_t      *factor)
{
    int32_t status = FVID2_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != size));
    GT_assert(VpsHalTrace, (NULL != factor));

    if(VPS_ISS_RSZ_SCALE_MODE_NORMAL == scaleMode)
    {
        factor->hAvgSize = 0;
        factor->vAvgSize = 0;
        factor->hRatio   = (RSZ_NORMAL_SCALE_MUL * size->inWidth) /
                           size->outWidth;
        factor->vRatio = (RSZ_NORMAL_SCALE_MUL * size->inHeight) /
                         size->outHeight;

        if((factor->hRatio > RSZ_NORMAL_MAX_SCALE_FACTOR) ||
           (factor->vRatio > RSZ_NORMAL_MAX_SCALE_FACTOR))
        {
            status = FVID2_EOUT_OF_RANGE;
        }
    }
    else
    {
        factor->hAvgSize = 0;
        factor->vAvgSize = 0;

        do
        {
            factor->hRatio = ((RSZ_NORMAL_SCALE_MUL * size->inWidth) /
                              size->outWidth) /
                             gIssHalRszAverageOut[factor->hAvgSize];
            factor->hAvgSize++;
        } while((factor->hRatio > RSZ_NORMAL_MAX_SCALE_FACTOR) &&
                (factor->hAvgSize < RSZ_DOWN_SCALE_MAX_SIZE));

        do
        {
            factor->vRatio = ((RSZ_NORMAL_SCALE_MUL * size->inHeight) /
                              size->outHeight) /
                             gIssHalRszAverageOut[factor->vAvgSize];
            factor->vAvgSize++;
        } while((factor->vRatio > RSZ_NORMAL_MAX_SCALE_FACTOR) &&
                (factor->vAvgSize < RSZ_DOWN_SCALE_MAX_SIZE));
    }

    if(factor->hRatio > RSZ_NORMAL_MAX_SCALE_FACTOR)
    {
        factor->hRatio = RSZ_NORMAL_MAX_SCALE_FACTOR;
    }
    if(factor->hRatio < RSZ_NORMAL_MIN_SCALE_FACTOR)
    {
        factor->hRatio = RSZ_NORMAL_MIN_SCALE_FACTOR;
    }
    if(factor->vRatio > RSZ_NORMAL_MAX_SCALE_FACTOR)
    {
        factor->vRatio = RSZ_NORMAL_MAX_SCALE_FACTOR;
    }
    if(factor->vRatio < RSZ_NORMAL_MIN_SCALE_FACTOR)
    {
        factor->vRatio = RSZ_NORMAL_MIN_SCALE_FACTOR;
    }

    return (status);
}

static int32_t RszSetChromaConfig(
    const isshalrszInstObj_t *instObj,
    const isshalrszConfig_t  *cfg)
{
    uint32_t regVal;

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_VSZ);
    regVal &= ~((UInt32) RSZ_SRC_VSZ_MASK);
    regVal |= (((UInt32) (cfg->srcCfg.procWin.cropHeight - 1U)) <<
               RSZ_SRC_VSZ_SHIFT) &
              RSZ_SRC_VSZ_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_VSZ, regVal);

    regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_VPS);
    regVal &= ~((UInt32) RSZ_SRC_VPS_MASK);
    regVal |= (cfg->srcCfg.procWin.cropStartY << RSZ_SRC_VPS_SHIFT) &
              RSZ_SRC_VPS_MASK;
    HW_WR_REG32(instObj->baseAddress + RSZ_SRC_VPS, regVal);

    GT_assert(VpsHalTrace, (FALSE == cfg->srcCfg.rszLuma));
    if(FALSE == cfg->srcCfg.rszLuma)
    {
        /* Select the input source */
        regVal  = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT0);
        regVal &= ~((UInt32) RSZ_SRC_FMT0_SEL_MASK);
        if(ISSHAL_RSZ_INP_SRC_IPIPEIF == cfg->srcCfg.inpSrc)
        {
            regVal |= RSZ_SRC_FMT0_SEL_MASK;
        }
        HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT0, regVal);

        /* Set the YUV420 input format */
        regVal = HW_RD_REG32(instObj->baseAddress + RSZ_SRC_FMT1);

        /*  IN420   COL
            1       0       Y is valid and processed
            1       1       UV is valid and processed */
        regVal &= ~((UInt32) (RSZ_SRC_FMT1_IN420_MASK | RSZ_SRC_FMT1_COL_MASK));
        regVal &= ~((UInt32) RSZ_SRC_FMT1_RAW_MASK);
        regVal |= (RSZ_SRC_FMT1_IN420_MASK | RSZ_SRC_FMT1_COL_MASK);
        HW_WR_REG32(instObj->baseAddress + RSZ_SRC_FMT1, regVal);

        if(TRUE == cfg->instCfg[VPS_ISS_RSZ_SCALER_A].enable)
        {
            regVal = HW_RD_REG32(instObj->baseAddress +
                                 RSZ_INST_420(VPS_ISS_RSZ_SCALER_A));
            regVal &= ~((UInt32) (RZA_420_YEN_MASK | RZA_420_CEN_MASK));
            regVal |= RZA_420_CEN_MASK;
            HW_WR_REG32(instObj->baseAddress +
                        RSZ_INST_420(VPS_ISS_RSZ_SCALER_A),
                        regVal);

            HW_WR_REG32(instObj->baseAddress +
                RSZ_INST_O_VSZ(VPS_ISS_RSZ_SCALER_A),
                (((UInt32) (cfg->instCfg[VPS_ISS_RSZ_SCALER_A].outFmt.height - 1U))
                 << RZA_O_VSZ_SHIFT) & RZA_O_VSZ_MASK);

            HW_WR_REG32(instObj->baseAddress + RSZ_INST_I_VPS(
                VPS_ISS_RSZ_SCALER_A),
                        (cfg->instCfg[VPS_ISS_RSZ_SCALER_A].startPos.startY <<
                         RZA_I_VPS_SHIFT) & RZA_I_VPS_MASK);

        }
        if(TRUE == cfg->instCfg[VPS_ISS_RSZ_SCALER_B].enable)
        {
            regVal = HW_RD_REG32(instObj->baseAddress +
                                 RSZ_INST_420(VPS_ISS_RSZ_SCALER_B));
            regVal &= ~((UInt32) (RZA_420_YEN_MASK | RZA_420_CEN_MASK));
            regVal |= RZA_420_CEN_MASK;
            HW_WR_REG32(instObj->baseAddress +
                        RSZ_INST_420(VPS_ISS_RSZ_SCALER_B),
                        regVal);
            HW_WR_REG32(instObj->baseAddress +
                RSZ_INST_O_VSZ(VPS_ISS_RSZ_SCALER_B),
                (((UInt32) (cfg->instCfg[VPS_ISS_RSZ_SCALER_B].outFmt.height - 1U))
                 << RZA_O_VSZ_SHIFT) & RZA_O_VSZ_MASK);

            HW_WR_REG32(instObj->baseAddress + RSZ_INST_I_VPS(
                VPS_ISS_RSZ_SCALER_B),
                        (cfg->instCfg[VPS_ISS_RSZ_SCALER_B].startPos.startY <<
                         RZB_I_VPS_SHIFT) & RZB_I_VPS_MASK);
        }
    }

    return FVID2_SOK;
}

