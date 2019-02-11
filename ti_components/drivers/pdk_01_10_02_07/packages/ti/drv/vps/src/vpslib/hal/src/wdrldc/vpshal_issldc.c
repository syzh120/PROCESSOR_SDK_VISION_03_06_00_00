/*
 *  Copyright (c) Texas Instruments Incorporated 2013
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
 *  \file vpshal_issldc.c
 *
 *  \brief File containing the ISS LDC HAL init, deinit and other common
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
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include "hw_iss_ldc.h"
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issldc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Max slice size supported by codec statistics collector
 */
#define LDC_SCS_MAX_SLICE_SIZE          (0x1FF0U)

/**
 *  \brief Max regionds supported by codec statistics collector
 */
#define LDC_SCS_MAX_REGION              (3U)

/**
 *  \brief Macro to check width alignment by 8
 */
#define LDC_BLOCK_WTH_ALIGN_8           (8U)

/**
 *  \brief Macro to check width alignment by 16
 */
#define LDC_BLOCK_WTH_ALIGN_16          (16U)

/**
 *  \brief Macro to check width alignment by 32
 */
#define LDC_BLOCK_WTH_ALIGN_32          (32U)

/**
 *  \brief Macro for max LDC Lut block size
 */
#define LDC_MAX_LDC_LUT_BLK_SIZE        (4U*1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief LDC instance parameters like BaseAddress
 */
typedef struct isshalldcInstParms
{
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
} isshalldcInstParms_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Function to check configuration, checks all parameters of
 *          ldcconfig and returns status.
 *
 * \param   instInfo           Pointer to instance Information.
 * \param   cfg                Pointer to ldcConfig structure
 *
 * \return  BSP_SOK on success else error code.
 *
 **/
int32_t LdcCheckCfg(const isshalldcInstParms_t *instInfo,
                    const vpsissldcConfig_t    *cfg);

static int32_t LdcSetAffineTransformCfg(
    const isshalldcInstParms_t               *instInfo,
    const vpsissldcPerspectiveTransformCfg_t *cfg);
static int32_t LdcGetAffineTransformCfg(
    const isshalldcInstParms_t         *instInfo,
    vpsissldcPerspectiveTransformCfg_t *cfg);

#if 0
static int32_t LdcSetCodecStatsCfg(
    isshalldcInstParms_t                *instInfo,
    const isshalldcSmartCodecStatsCfg_t *cfg);
static int32_t LdcGetCodecStatsCfg(
    isshalldcInstParms_t          *instInfo,
    isshalldcSmartCodecStatsCfg_t *cfg);
#endif

static int32_t LdcSetOutFrameSize(
    const isshalldcInstParms_t *instInfo,
    const vpsissldcConfig_t    *cfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalldcInstParms_t gIssHalLdcInstPrms[ISSHAL_LDC_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_issldcInit
 *  \brief LDC init function.
 *
 *  Initializes LDC objects.
 *  This function should be called before calling any of LDC HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalldcInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issldcInit(UInt32                       numInst,
                          const isshalldcInstParams_t *instPrms,
                          Ptr                          arg)
{
    uint32_t instCnt;
    isshalldcInstParms_t *pInstPrm;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_LDC_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * ldc number of instances. The size of this number of instances
         * is never more than ISSHAL_LDC_INST_MAX_ID.
         */
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].instId < ISSHAL_LDC_INST_MAX_ID));

        pInstPrm = &gIssHalLdcInstPrms[instCnt];

        pInstPrm->openCnt     = 0U;
        pInstPrm->instId      = instPrms[instCnt].instId;
        pInstPrm->baseAddress = instPrms[instCnt].baseAddress;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_issldcDeInit
 *  \brief LDC HAL exit function.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issldcDeInit(Ptr arg)
{
    return (BSP_SOK);
}

/**
 *  VpsHal_issldcOpen
 *  \brief This function should be called prior to calling any of the LDC HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issldcOpen(const isshalldcOpenParams_t *openPrms)
{
    uint32_t              instCnt;
    VpsHal_Handle         handle   = NULL;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_LDC_MAX_INST; instCnt++)
    {
        instInfo = &(gIssHalLdcInstPrms[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == instInfo->instId)
        {
            handle = (VpsHal_Handle) (instInfo);

            /* Check whether some one has already opened this instance */
            if(0 == instInfo->openCnt)
            {
                handle = (VpsHal_Handle) (instInfo);
                instInfo->openCnt++;
            }

            instInfo->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_issldcClose
 *  \brief This functions closes the ldc handle and after call to this
 *  function, ldc handle is not valid.
 *
 *  \param handle         Requested LDC instance
 */
int32_t VpsHal_issldcClose(VpsHal_Handle handle)
{
    int32_t status = (-(int32_t)1);
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instInfo = (isshalldcInstParms_t *) handle;

    /* Decrement the open count */
    if(instInfo->openCnt > 0)
    {
        instInfo->openCnt--;
        status = 0;
    }

    return (status);
}

/**
 *  \brief Sets the entire LDC configuration to the LDC registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issldcConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetConfig(VpsHal_Handle            handle,
                               const vpsissldcConfig_t *cfg,
                               Ptr                      arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (FALSE != cfg->isAdvCfgValid));

    instInfo = (isshalldcInstParms_t *) handle;

    /* Check for Error */
    status = LdcCheckCfg(instInfo, cfg);

    /* Set the input frame size in */
    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_INPUT_FRAME_SIZE);
    regVal &= ~(LDC_INPUT_FRAME_SIZE_W_MASK | LDC_INPUT_FRAME_SIZE_H_MASK);
    regVal |= (cfg->inputFrameWidth << LDC_INPUT_FRAME_SIZE_W_SHIFT) &
              LDC_INPUT_FRAME_SIZE_W_MASK;
    regVal |= (cfg->inputFrameHeight << LDC_INPUT_FRAME_SIZE_H_SHIFT) &
              LDC_INPUT_FRAME_SIZE_H_MASK;
    HW_WR_REG32(instInfo->baseAddress + LDC_INPUT_FRAME_SIZE, regVal);

    /* Set the output frame parameters */
    LdcSetOutFrameSize(instInfo, cfg);

    /* Set the transformation configuration */
    LdcSetAffineTransformCfg(instInfo, &cfg->perspTrnsformCfg);

    /* Set the Codec Statistics collector configuration */
#if 0
    LdcSetCodecStatsCfg(instInfo, &cfg->smartCodecStatsCfg);
#endif

    /* Set the interpolation and init color component
     * for bayer and YUV data in the LDC_CONFIG Register */
    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_CONFIG);

    regVal &= ~((UInt32) LDC_CONFIG_CNST_MD_MASK);
    if(1U == cfg->advCfg.enableConstOutAddr)
    {
        regVal |= LDC_CONFIG_CNST_MD_MASK;
    }
    if(VPS_ISS_LDC_MODE_BAYER_CHROMA_ABBERATION == cfg->mode)
    {
        regVal &= ~((UInt32) LDC_CONFIG_INITC_MASK);
        regVal |= ((uint32_t) cfg->bayerInitColor << LDC_CONFIG_INITC_SHIFT) &
                  LDC_CONFIG_INITC_MASK;
    }
    else
    {
        regVal &= ~((UInt32) LDC_CONFIG_YINT_TYP_MASK);
        if(1U == cfg->lumeIntrType)
        {
            regVal |= LDC_CONFIG_YINT_TYP_MASK;
        }
    }
    HW_WR_REG32(instInfo->baseAddress + LDC_CONFIG, regVal);

    /* Set the LDC_PCR Register */
    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);

    regVal &= ~((UInt32) LDC_PCR_MODE_MASK);
    regVal |= ((uint32_t) cfg->mode << LDC_PCR_MODE_SHIFT) & LDC_PCR_MODE_MASK;

    if(VPS_ISS_LDC_MODE_BAYER_CHROMA_ABBERATION == cfg->mode)
    {
        regVal &= ~((UInt32) LDC_PCR_BMODE_MASK);
        regVal |= ((uint32_t) cfg->bayerDataFormat << LDC_PCR_BMODE_SHIFT) &
                  LDC_PCR_BMODE_MASK;
    }
    regVal &= ~((UInt32) LDC_PCR_LDMAPEN_MASK);
    if(1U == cfg->enableBackMapping)
    {
        regVal |= LDC_PCR_LDMAPEN_MASK;
    }

    regVal &= ~((UInt32) LDC_PCR_CIRCEN_MASK);
    if(1U == cfg->advCfg.enableCircAddrMode)
    {
        HW_WR_REG32(instInfo->baseAddress + LDC_RD_OFST,
                    HW_RD_REG32(instInfo->baseAddress + LDC_RD_OFST) &
                    ~LDC_RD_OFST_MOD_MASK);

        HW_WR_REG32(instInfo->baseAddress + LDC_RD_OFST,
                    HW_RD_REG32(instInfo->baseAddress + LDC_RD_OFST) |
                    ((cfg->advCfg.circBuffSize << LDC_RD_OFST_MOD_SHIFT) &
                     LDC_RD_OFST_MOD_MASK));

        regVal |= LDC_PCR_CIRCEN_MASK;
    }
    HW_WR_REG32(instInfo->baseAddress + LDC_PCR, regVal);

    if(BSP_SOK == status)
    {
        VpsHal_issldcSetLutConfig(handle, &(cfg->lutCfg));
    }

    return (status);
}

/**
 *  \brief Sets the entire LDC configuration to the LDC registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issldcConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcGetConfig(VpsHal_Handle      handle,
                               vpsissldcConfig_t *cfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    instInfo = (isshalldcInstParms_t *) handle;

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_INPUT_FRAME_SIZE);
    cfg->inputFrameWidth = (regVal & LDC_INPUT_FRAME_SIZE_W_MASK) >>
                           LDC_INPUT_FRAME_SIZE_W_SHIFT;
    cfg->inputFrameHeight = (regVal & LDC_INPUT_FRAME_SIZE_H_MASK) >>
                            LDC_INPUT_FRAME_SIZE_H_SHIFT;

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_BLOCK);
    cfg->advCfg.outputBlockWidth = (regVal & LDC_BLOCK_OBW_MASK) >>
                                   LDC_BLOCK_OBW_SHIFT;
    cfg->advCfg.outputBlockHeight = (regVal & LDC_BLOCK_OBH_MASK) >>
                                    LDC_BLOCK_OBH_SHIFT;
    cfg->pixelPad = (regVal & LDC_BLOCK_PIXPAD_MASK) >>
                    LDC_BLOCK_PIXPAD_SHIFT;

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_INITXY);
    cfg->advCfg.outputStartX = (regVal & LDC_INITXY_INITX_MASK) >>
                               LDC_INITXY_INITX_SHIFT;
    cfg->advCfg.outputStartY = (regVal & LDC_INITXY_INITY_MASK) >>
                               LDC_INITXY_INITY_SHIFT;

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_FRAME_SIZE);
    cfg->advCfg.outputFrameWidth = (regVal & LDC_FRAME_SIZE_W_MASK) >>
                                   LDC_FRAME_SIZE_W_SHIFT;
    cfg->advCfg.outputFrameHeight = (regVal & LDC_FRAME_SIZE_H_MASK) >>
                                    LDC_FRAME_SIZE_H_SHIFT;

    /* Get the transformation configuration */
    LdcGetAffineTransformCfg(instInfo, &cfg->perspTrnsformCfg);

    /* Get the Codec Statistics collector configuration */
#if 0
    LdcGetCodecStatsCfg(instInfo, &cfg->smartCodecStatsCfg);
#endif
    /* Get the interpolation and init color component
     * for bayer and YUV data in the LDC_CONFIG Register */
    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_CONFIG);

    cfg->advCfg.enableConstOutAddr = (regVal & LDC_CONFIG_CNST_MD_MASK) >>
                                     LDC_CONFIG_CNST_MD_SHIFT;
    cfg->bayerInitColor = (vpsissldcBayerInitColor_t)
                          ((regVal & LDC_CONFIG_INITC_MASK) >>
                           LDC_CONFIG_INITC_SHIFT);
    cfg->lumeIntrType = (vpsissldcLumaIntrType_t)
                        ((regVal & LDC_CONFIG_YINT_TYP_MASK) >>
                         LDC_CONFIG_YINT_TYP_SHIFT);

    /* Set the LDC_PCR Register */
    regVal    = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);
    cfg->mode = (vpsissldcMode_t)
                ((regVal & LDC_PCR_MODE_MASK) >> LDC_PCR_MODE_SHIFT);
    cfg->bayerDataFormat = (vpsissldcBayerDataFormat_t)
                           ((regVal & LDC_PCR_BMODE_MASK) >>
                            LDC_PCR_BMODE_SHIFT);
    cfg->enableBackMapping = (regVal & LDC_PCR_LDMAPEN_MASK) >>
                             LDC_PCR_LDMAPEN_SHIFT;
    cfg->advCfg.enableCircAddrMode = (regVal & LDC_PCR_CIRCEN_MASK) >>
                                     LDC_PCR_CIRCEN_SHIFT;
    cfg->advCfg.circBuffSize = (regVal & LDC_RD_OFST_MOD_MASK) >>
                               LDC_RD_OFST_MOD_SHIFT;

    return (status);
}

/**
 *  VpsHal_issldcControl
 *  \brief LDC specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg)
{
    return (BSP_SOK);
}

/**
 *  VpsHal_issldcSetInFrameAddress
 *  \brief LDC Api for setting input address.
 *
 *  \param handle           Instance handle
 *  \param addrLuma         Input Luma address, must be 16byte aligned
 *  \param addrChroma       Input Chroma address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input buffers
 *                          must be even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetInFrameAddress(VpsHal_Handle   handle,
                                       vpsissldcMode_t mode,
                                       uint32_t        addrLuma,
                                       uint32_t        addrChroma,
                                       uint32_t        lineOffset)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (0U != addrLuma));
    GT_assert(VpsHalTrace, (0U != lineOffset));

    if(VPS_ISS_LDC_MODE_YUV420_LDC == mode)
    {
        GT_assert(VpsHalTrace, (0U != addrChroma));
    }

    /* TODO: Address and Line offset alignment checking */

    instInfo = (isshalldcInstParms_t *) handle;

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_RD_OFST);
    regVal &= ~((UInt32) LDC_RD_OFST_ROFST_MASK);
    regVal  = regVal | ((lineOffset << LDC_RD_OFST_ROFST_SHIFT) &
              LDC_RD_OFST_ROFST_MASK);
    HW_WR_REG32(instInfo->baseAddress + LDC_RD_OFST, regVal);

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for  setting memory
     * mapped register
     */
    HW_WR_REG32(instInfo->baseAddress + LDC_RD_BASE, addrLuma);

    HW_WR_REG32(instInfo->baseAddress + LDC_420C_RD_BASE, addrChroma);

    return (status);
}

/**
 *  VpsHal_issldcSetOutFrameAddress
 *  \brief LDC Api for setting output address.
 *
 *  \param handle           Instance handle
 *  \param addrLuma         Output Luma address, must be 16byte aligned
 *  \param addrChroma       Output Chroma address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input buffers
 *                          must be even and 16byte aligned
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetOutFrameAddress(VpsHal_Handle   handle,
                                        vpsissldcMode_t mode,
                                        uint32_t        addrLuma,
                                        uint32_t        addrChroma,
                                        uint32_t        lineOffset)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    /* GT_assert(VpsHalTrace, (NULL != addrLuma)); */
    GT_assert(VpsHalTrace, (0U != lineOffset));

    if(VPS_ISS_LDC_MODE_YUV420_LDC == mode)
    {
        GT_assert(VpsHalTrace, (0U != addrChroma));
    }

    /* TODO: Address and Line offset alignment checking */

    instInfo = (isshalldcInstParms_t *) handle;

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_WR_OFST);
    regVal &= ~((UInt32) LDC_WR_OFST_WOFST_MASK);
    regVal  = regVal | ((lineOffset << LDC_WR_OFST_WOFST_SHIFT) &
              LDC_WR_OFST_WOFST_MASK);
    HW_WR_REG32(instInfo->baseAddress + LDC_WR_OFST, regVal);

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for  setting memory
     * mapped register
     */
    HW_WR_REG32(instInfo->baseAddress + LDC_WR_BASE, addrLuma);

    HW_WR_REG32(instInfo->baseAddress + LDC_420C_WR_BASE, addrChroma);

    return (status);
}

/**
 *  VpsHal_issldcStart
 *  \brief LDC Api for enabling LDC module.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t status = FVID2_SOK;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instInfo = (isshalldcInstParms_t *) handle;

    HW_WR_REG32(instInfo->baseAddress + LDC_PCR,
                HW_RD_REG32(instInfo->baseAddress + LDC_PCR) | LDC_PCR_EN_MASK);

    return (status);
}

/**
 *  VpsHal_issldcStop
 *  \brief LDC Api for disabling LDC module.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcStop(VpsHal_Handle handle)
{
    int32_t status = FVID2_SOK;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    instInfo = (isshalldcInstParms_t *) handle;

    HW_WR_REG32(instInfo->baseAddress + LDC_PCR,
                HW_RD_REG32(instInfo->baseAddress + LDC_PCR) &
                ~((UInt32) LDC_PCR_EN_MASK));

    return (status);
}

/**
 *  VpsHal_issldcSetLutConfig
 *  \brief API for setting LUT configuration.
 *
 *  \param handle           Instance handle
 *  \param lutCfg           Pointer to LUT configuration structure
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issldcSetLutConfig(VpsHal_Handle            handle,
                                  const vpsissldcLutCfg_t *lutCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshalldcInstParms_t *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lutCfg));

    instInfo = (isshalldcInstParms_t *) handle;

    /* TODO: Check for alignment requiremet */

    HW_WR_REG32(instInfo->baseAddress + LDC_MESHTABLE_BASE, lutCfg->address);
    HW_WR_REG32(instInfo->baseAddress + LDC_MESHTABLE_OFST, lutCfg->lineOffset);

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_MESHTABLE_CONFIG);
    regVal &= ~((UInt32) LDC_MESHTABLE_CONFIG_M_MASK);

    regVal |= (lutCfg->downScaleFactor << LDC_MESHTABLE_CONFIG_M_SHIFT) &
              LDC_MESHTABLE_CONFIG_M_MASK;
    HW_WR_REG32(instInfo->baseAddress + LDC_MESHTABLE_CONFIG, regVal);

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/**
 * \brief   Demonstrates how to define an internal function without Doxygen
 *          tags.
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
static int32_t LdcSetAffineTransformCfg(
    const isshalldcInstParms_t *instInfo,
    const vpsissldcPerspectiveTransformCfg_t
                               *cfg)
{
    int32_t  status = BSP_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    /* Set all perspective transformation parameters */
    HW_WR_REG32(instInfo->baseAddress + LDC_AB,
                ((cfg->coeffA << LDC_AB_A_SHIFT) & LDC_AB_A_MASK) |
                ((cfg->coeffB << LDC_AB_B_SHIFT) & LDC_AB_B_MASK));
    HW_WR_REG32(instInfo->baseAddress + LDC_CD,
                ((cfg->coeffC << LDC_CD_C_SHIFT) & LDC_CD_C_MASK) |
                ((cfg->coeffD << LDC_CD_D_SHIFT) & LDC_CD_D_MASK));
    HW_WR_REG32(instInfo->baseAddress + LDC_EF,
                ((cfg->coeffE << LDC_EF_E_SHIFT) & LDC_EF_E_MASK) |
                ((cfg->coeffF << LDC_EF_F_SHIFT) & LDC_EF_F_MASK));
    HW_WR_REG32(instInfo->baseAddress + LDC_GH,
                ((cfg->coeffG << LDC_GH_G_SHIFT) & LDC_GH_G_MASK) |
                ((cfg->coeffH << LDC_GH_H_SHIFT) & LDC_GH_H_MASK));

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);

    regVal &= ~((UInt32) LDC_PCR_AFF_EXPANDEN_MASK);
    if(1U == cfg->enableExpandFmt)
    {
        regVal |= LDC_PCR_AFF_EXPANDEN_MASK;
    }

    if(1U == cfg->enableWarp)
    {
        regVal |= LDC_PCR_PWARPEN_MASK;
    }
    else
    {
        /* Disable Perspective transformation and set GH parameters to be 0 */
        regVal &= ~((UInt32) LDC_PCR_PWARPEN_MASK);
        HW_WR_REG32(instInfo->baseAddress + LDC_GH, 0U);
    }
    HW_WR_REG32(instInfo->baseAddress + LDC_PCR, regVal);

    return (status);
}

/**
 * \brief   Demonstrates how to define an internal function without Doxygen
 *          tags.
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
static int32_t LdcGetAffineTransformCfg(
    const isshalldcInstParms_t         *instInfo,
    vpsissldcPerspectiveTransformCfg_t *cfg)
{
    int32_t  status = BSP_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);
    if(1U == (uint32_t)(regVal & LDC_PCR_PWARPEN_MASK))
    {
        cfg->enableWarp = 1U;
    }
    else
    {
        cfg->enableWarp = 0U;
    }
    if(1U == (uint32_t)(regVal & LDC_PCR_PWARPEN_MASK))
    {
        cfg->enableExpandFmt = 1U;
    }
    else
    {
        cfg->enableExpandFmt = 0U;
    }

    regVal      = HW_RD_REG32(instInfo->baseAddress + LDC_AB);
    cfg->coeffA = (regVal & LDC_AB_A_MASK) >> LDC_AB_A_SHIFT;
    cfg->coeffB = (regVal & LDC_AB_B_MASK) >> LDC_AB_B_SHIFT;
    cfg->coeffC = (regVal & LDC_CD_C_MASK) >> LDC_CD_C_SHIFT;
    cfg->coeffD = (regVal & LDC_CD_D_MASK) >> LDC_CD_D_SHIFT;
    cfg->coeffE = (regVal & LDC_EF_E_MASK) >> LDC_EF_E_SHIFT;
    cfg->coeffF = (regVal & LDC_EF_F_MASK) >> LDC_EF_F_SHIFT;
    cfg->coeffG = (regVal & LDC_GH_G_MASK) >> LDC_GH_G_SHIFT;
    cfg->coeffH = (regVal & LDC_GH_H_MASK) >> LDC_GH_H_SHIFT;

    return (status);
}

/**
 * \brief   Demonstrates how to define an internal function without Doxygen
 *          tags.
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
#if 0
static int32_t LdcSetCodecStatsCfg(
    isshalldcInstParms_t                *instInfo,
    const isshalldcSmartCodecStatsCfg_t *cfg)
{
    int32_t  status = BSP_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    if(cfg->numRegions > LDC_SCS_MAX_REGION)
    {
        status = FVID2_EINVALID_PARAMS;
    }
    if(cfg->sliceSize > LDC_SCS_MAX_SLICE_SIZE)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(BSP_SOK == status)
    {
        regVal = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);

        regVal &= ~LDC_PCR_SCSEN_MASK;
        if(1U == cfg->enable)
        {
            HW_WR_REG32(instInfo->baseAddress + LDC_SCS_CTL, 0x0U);

            HW_WR_REG32(instInfo->baseAddress + LDC_SCS_CTL,
                        (((cfg->sliceSize << LDC_SCS_CTL_SLICE_SIZE_SHIFT) &
                          LDC_SCS_CTL_SLICE_SIZE_MASK) |
                         ((cfg->numRegions << LDC_SCS_CTL_REGION_SHIFT) &
                          LDC_SCS_CTL_REGION_MASK) |
                         ((cfg->accShift << LDC_SCS_CTL_ACCSHIFT_SHIFT) &
                          LDC_SCS_CTL_ACCSHIFT_MASK)));

            regVal |= LDC_PCR_SCSEN_MASK;
        }
    }

    return (status);
}

/**
 * \brief   TBD: Demonstrates how to define an internal function without Doxygen
 *          tags.
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
static int32_t LdcGetCodecStatsCfg(isshalldcInstParms_t          *instInfo,
                                   isshalldcSmartCodecStatsCfg_t *cfg)
{
    int32_t  status = BSP_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_PCR);
    if(1U == (regVal & LDC_PCR_SCSEN_MASK))
    {
        cfg->enable = 1U;
    }
    else
    {
        cfg->enable = 0U;
    }

    regVal = HW_RD_REG32(instInfo->baseAddress + LDC_SCS_CTL);

    cfg->accShift = (regVal & LDC_SCS_CTL_ACCSHIFT_MASK) >>
                    LDC_SCS_CTL_ACCSHIFT_SHIFT;
    cfg->numRegions = (regVal & LDC_SCS_CTL_REGION_MASK) >>
                      LDC_SCS_CTL_REGION_SHIFT;
    cfg->sliceSize = (regVal & LDC_SCS_CTL_SLICE_SIZE_MASK) >>
                     LDC_SCS_CTL_SLICE_SIZE_SHIFT;

    return (status);
}

#endif

static int32_t LdcSetOutFrameSize(
    const isshalldcInstParms_t *instInfo,
    const vpsissldcConfig_t    *cfg)
{
    uint32_t regVal;

    /* Check for NULL Values */
    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_BLOCK);
    regVal &=
        ~(LDC_BLOCK_PIXPAD_MASK | LDC_BLOCK_OBH_MASK | LDC_BLOCK_OBW_MASK);

    regVal |= (cfg->advCfg.outputBlockWidth << LDC_BLOCK_OBW_SHIFT) &
              LDC_BLOCK_OBW_MASK;
    regVal |= (cfg->advCfg.outputBlockHeight << LDC_BLOCK_OBH_SHIFT) &
              LDC_BLOCK_OBH_MASK;
    regVal |= (cfg->pixelPad << LDC_BLOCK_PIXPAD_SHIFT) &
              LDC_BLOCK_PIXPAD_MASK;
    HW_WR_REG32(instInfo->baseAddress + LDC_BLOCK, regVal);

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_INITXY);
    regVal &= ~(LDC_INITXY_INITY_MASK | LDC_INITXY_INITX_MASK);

    regVal |= (cfg->advCfg.outputStartX << LDC_INITXY_INITX_SHIFT) &
              LDC_INITXY_INITX_MASK;
    regVal |= (cfg->advCfg.outputStartY << LDC_INITXY_INITY_SHIFT) &
              LDC_INITXY_INITY_MASK;
    HW_WR_REG32(instInfo->baseAddress + LDC_INITXY, regVal);

    regVal  = HW_RD_REG32(instInfo->baseAddress + LDC_FRAME_SIZE);
    regVal &= ~(LDC_FRAME_SIZE_W_MASK | LDC_FRAME_SIZE_H_MASK);

    regVal |= (cfg->advCfg.outputFrameWidth << LDC_FRAME_SIZE_W_SHIFT) &
              LDC_FRAME_SIZE_W_MASK;
    regVal |= (cfg->advCfg.outputFrameHeight << LDC_FRAME_SIZE_H_SHIFT) &
              LDC_FRAME_SIZE_H_MASK;
    HW_WR_REG32(instInfo->baseAddress + LDC_FRAME_SIZE, regVal);

    return (BSP_SOK);
}

int32_t LdcCheckCfg(
    const isshalldcInstParms_t *instInfo,
    const vpsissldcConfig_t    *cfg)
{
    int32_t status = BSP_SOK;

    GT_assert(VpsHalTrace, (NULL != instInfo));
    GT_assert(VpsHalTrace, (NULL != cfg));

    if(1U == cfg->advCfg.enableCircAddrMode)
    {
        if(0U != (cfg->advCfg.circBuffSize % 2U))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if((0U == cfg->advCfg.outputBlockHeight) ||
       (0U != (cfg->advCfg.outputBlockHeight % 2U)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(0U == cfg->advCfg.outputBlockWidth)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(VPS_ISS_LDC_MODE_YUV422_LDC == cfg->mode)
    {
        if(0U != (cfg->advCfg.outputBlockWidth % LDC_BLOCK_WTH_ALIGN_8))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }
    else if(VPS_ISS_LDC_MODE_YUV420_LDC == cfg->mode)
    {
        if(0U != (cfg->advCfg.outputBlockWidth % LDC_BLOCK_WTH_ALIGN_16))
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }
    else    /* RAW Mode */
    {
        if(VPS_ISS_LDC_BAYER_DATA_FORMAT_UNPACKED_12BIT ==
           cfg->bayerDataFormat)
        {
            if(0U != (cfg->advCfg.outputBlockWidth % LDC_BLOCK_WTH_ALIGN_8))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
        else if(VPS_ISS_LDC_BAYER_DATA_FORMAT_PACKED_12BIT ==
                cfg->bayerDataFormat)
        {
            if(0U != (cfg->advCfg.outputBlockWidth % LDC_BLOCK_WTH_ALIGN_32))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
        else /* 8Bit packed or ALaw format */
        {
            if(0U != (cfg->advCfg.outputBlockWidth % LDC_BLOCK_WTH_ALIGN_16))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if((0U == cfg->advCfg.outputBlockWidth) ||
       (0U != (cfg->advCfg.outputFrameWidth % cfg->advCfg.outputBlockWidth)))
    {
        status = FVID2_EINVALID_PARAMS;
    }
    if(0U != (cfg->advCfg.outputFrameHeight % cfg->advCfg.outputBlockHeight))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(VPS_ISS_LDC_MODE_BAYER_CHROMA_ABBERATION == cfg->mode)
    {
        if(VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_1 == cfg->lutCfg.downScaleFactor)
        {
            /* For the Bayer data, Down scaling factor 0 is invalid */
            status = FVID2_EINVALID_PARAMS;
        }
    }

    /* For YUV420 and YUV420 mode, block size must be less than 2KB internal
       memory size */
    if((VPS_ISS_LDC_MODE_YUV422_LDC == cfg->mode) ||
       (VPS_ISS_LDC_MODE_YUV420_LDC == cfg->mode))
    {
        if(((cfg->advCfg.outputBlockWidth /
             ((uint32_t)0x1U << (uint32_t)cfg->lutCfg.downScaleFactor)) *
            (cfg->advCfg.outputBlockHeight /
             ((uint32_t)0x1U << (uint32_t)cfg->lutCfg.downScaleFactor)) *
            4U) >
           LDC_MAX_LDC_LUT_BLK_SIZE)
        {
            /* Block size is invalid for this down scaling factor */
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

