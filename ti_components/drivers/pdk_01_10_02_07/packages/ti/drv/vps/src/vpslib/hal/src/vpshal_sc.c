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
 *  \file vpshal_sc.c
 *
 *  \brief HAL implementation for SC module instances
 *  This file implements the HAL APIs of the Scaler modules
 *
 */

/* TODO: Add error check for RAV upscaling */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#ifdef VPS_DV_BUILD
#include <cgt_pragmas.h>
#endif
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_sc.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_sc.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshal_scPriv.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshal_scDefaults.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * scHalObj: SC HAL object containing all SC instances
 */
static VpsHal_Sc    scHalObj;

/**
 *  \brief Scaling Coefficient Memory Pointers
 *  Separate allocation is required to allow for dynamic allocation of
 *  non-cached memory for VPDMA usage
 */
static UInt8       *gScVertBilinearCoeffMemPtr      = NULL;
static UInt8       *gScVertUpScaleCoeffMemPtr       = NULL;
static UInt8       *gScVertOneToOneScaleCoeffMemPtr = NULL;
static UInt8       *gScVertDownScaleCoeffMemPtr     = NULL;
static UInt8       *gScHorzUpScaleCoeffMemPtr       = NULL;
static UInt8       *gScHorzOneToOneScaleCoeffMemPtr = NULL;
static UInt8       *gScHorzDownScaleCoeffMemPtr     = NULL;
static Vps_ScCoeff *gUserScCoeff = NULL;

#ifdef VPS_DV_BUILD

DO_PRAGMA_SECTION_INIT(gVpsScVertBilinearCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScVertUpScaleCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScVertOneToOneScaleCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScVertDownScaleCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScHorzUpScaleCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScHorzOneToOneScaleCoeff, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpsScHorzDownScaleCoeff, user_ocmc_ram)

__align(32) const UInt16 gVpsScVertBilinearCoeff[
    VPSHAL_SC_BILINEAR_NUM_COEFF_SETS]
[VPS_SC_NUM_PHASES][8] =
    SC_VERTICAL_BILINEAR_COEFF;
__align(32) const UInt16 gVpsScVertUpScaleCoeff[
    VPSHAL_SC_BILINEAR_NUM_COEFF_SETS][
    VPS_SC_NUM_PHASES][8] =
    SC_VERTICAL_POLYPHASE_UP_SCALE_COEFF;
__align(32) const UInt16 gVpsScVertOneToOneScaleCoeff[
    VPSHAL_SC_VERT_NUM_COEFF_SETS
][VPS_SC_NUM_PHASES][8] =
    SC_VERTICAL_POLYPHASE_1_1_SCALE_COEFF;
__align(32) const UInt16 gVpsScVertDownScaleCoeff[13][
    VPSHAL_SC_VERT_NUM_COEFF_SETS
][VPS_SC_NUM_PHASES][8] =
    SC_VERTICAL_POLYPHASE_DOWN_SCALE_COEFF;
__align(32) const UInt16 gVpsScHorzUpScaleCoeff[VPSHAL_SC_HORZ_NUM_COEFF_SETS][
    VPS_SC_NUM_PHASES][8] =
    SC_HORIZONTAL_POLYPHASE_UP_SCALE_COEFF;
__align(32) const UInt16 gVpsScHorzOneToOneScaleCoeff[
    VPSHAL_SC_HORZ_NUM_COEFF_SETS
][
    VPS_SC_NUM_PHASES][8] =
    SC_HORIZONTAL_POLYPHASE_1_1_SCALE_COEFF;
__align(32) const UInt16 gVpsScHorzDownScaleCoeff[12][
    VPSHAL_SC_HORZ_NUM_COEFF_SETS
][VPS_SC_NUM_PHASES][8] =
    SC_HORIZONTAL_POLYPHASE_DOWN_SCALE_COEFF;

#else /* VPS_DV_BUILD */

/**
 *  \brief Scaling Coefficient Arrays used for initialization
 */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScVertBilinearCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScVertBilinearCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScVertBilinearCoeffMem
            [VPSHAL_SC_BILINEAR_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScVertBilinearCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScVertBilinearCoeff[VPSHAL_SC_BILINEAR_NUM_COEFF_SETS]
                [VPS_SC_NUM_PHASES][8] = SC_VERTICAL_BILINEAR_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScVertUpScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScVertUpScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScVertUpScaleCoeffMem
                [VPSHAL_SC_BILINEAR_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScVertUpScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScVertUpScaleCoeff[VPSHAL_SC_BILINEAR_NUM_COEFF_SETS][
    VPS_SC_NUM_PHASES][8] = SC_VERTICAL_POLYPHASE_UP_SCALE_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScVertOneToOneScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScVertOneToOneScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScVertOneToOneScaleCoeffMem
                [VPSHAL_SC_VERT_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScVertOneToOneScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScVertOneToOneScaleCoeff[VPSHAL_SC_VERT_NUM_COEFF_SETS]
                [VPS_SC_NUM_PHASES][8] = SC_VERTICAL_POLYPHASE_1_1_SCALE_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScVertDownScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScVertDownScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScVertDownScaleCoeffMem[13]
        [VPSHAL_SC_VERT_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScVertDownScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScVertDownScaleCoeff[13][VPSHAL_SC_VERT_NUM_COEFF_SETS]
                [VPS_SC_NUM_PHASES][8] = SC_VERTICAL_POLYPHASE_DOWN_SCALE_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScHorzUpScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScHorzUpScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScHorzUpScaleCoeffMem
                [VPSHAL_SC_HORZ_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScHorzUpScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScHorzUpScaleCoeff[VPSHAL_SC_HORZ_NUM_COEFF_SETS]
    [VPS_SC_NUM_PHASES][8] = SC_HORIZONTAL_POLYPHASE_UP_SCALE_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScHorzOneToOneScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScHorzOneToOneScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScHorzOneToOneScaleCoeffMem
            [VPSHAL_SC_HORZ_NUM_COEFF_SETS][VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScHorzOneToOneScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScHorzOneToOneScaleCoeff[VPSHAL_SC_HORZ_NUM_COEFF_SETS]
               [VPS_SC_NUM_PHASES][8] = SC_HORIZONTAL_POLYPHASE_1_1_SCALE_COEFF;

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsScHorzDownScaleCoeffMem, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsScHorzDownScaleCoeffMem,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt16 gVpsScHorzDownScaleCoeffMem[12][VPSHAL_SC_HORZ_NUM_COEFF_SETS]
                [VPS_SC_NUM_PHASES][8];

#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN)
#else
#pragma DATA_ALIGN(gVpsScHorzDownScaleCoeff, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16 gVpsScHorzDownScaleCoeff[12][VPSHAL_SC_HORZ_NUM_COEFF_SETS]
                [VPS_SC_NUM_PHASES][8] = SC_HORIZONTAL_POLYPHASE_DOWN_SCALE_COEFF;
#endif  /* VPS_DV_BUILD */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static inline void VpsHal_scCalVertPolyphaseParams(
    const Vps_ScConfig *config,
    UInt32             *rowAccInc,
    UInt32             *offsetA,
    UInt32             *offsetB);
static inline UInt32 VpsHal_scCalHorzLinearAccInc(const Vps_ScConfig *config,
                                                  UInt32             *shift);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_scInit
 *  \brief SC HAL init function.
 *
 *  Initializes SC objects, gets the register overlay offsets for SC
 *  registers.
 *  This function should be called before calling any of SC HAL API's.
 *  VPDMA HAL should be initialized prior to calling any of SC HAL
 *  functions.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #VpsHal_ScInstParams.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
Int32 VpsHal_scInit(UInt32                     numInst,
                    const VpsHal_ScInstParams *instPrms,
                    Ptr                        arg)
{
    Int32  retval = BSP_SOK;
    UInt32 i;
    UInt32 baseAddr, regAddr;
    Vps_ScPeakingConfig peak = SC_EXPERT_VAL_PEAKING;

    GT_assert(VpsHalTrace, instPrms != NULL);

    scHalObj.numInst = numInst;

    for (i = 0; i < numInst; i++)
    {
        VpsHal_ScInfo *scInfo = &scHalObj.scInfo[i];
        scInfo->halId           = instPrms[i].halId;
        scInfo->openCnt         = 0;
        scInfo->baseAddr        = instPrms[i].baseAddr;
        scInfo->coeffConfigDest = instPrms[i].coeffConfigDest;
        scInfo->isHqScaler      = instPrms[i].isHqScaler;
        scInfo->userScCoeff     = NULL; /* NULL till provided by user */

        VpsHal_scSetPeakingParams(scInfo, &peak);

        /* Calculate VPDMA register overlay size and register offset in the
         * VPDMA
         * register overlay. Since register organization for all scaler are
         * same,
         * only one array of register offset is sufficient.
         * Since the register offset are same for all scaler instances,
         * using HQ
         * scaler to get physical offset. */
        baseAddr = scInfo->baseAddr;
        regAddr  = baseAddr + SC_CFG_0;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC0_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_1;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC1_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_2;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC2_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_3;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC3_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_4;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC4_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_5;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC5_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_6;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC6_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_8;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC8_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_9;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC9_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_10;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC10_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_11;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC11_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_12;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC12_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_13;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC13_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_18;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC18_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_24;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC24_IDX] = (UInt32 *) regAddr;
        regAddr = baseAddr + SC_CFG_25;
        scInfo->regOffset[SC_CONFIG_OVLY_CFG_SC25_IDX] = (UInt32 *) regAddr;

        scInfo->regOvlySize =
            VpsHal_vpdmaCalcRegOvlyMemSize(scInfo->regOffset,
                                           SC_CONFIG_OVLY_NUM_IDX,
                                           scInfo->virtRegOffset);
    }

    gScVertBilinearCoeffMemPtr      = (UInt8 *) gVpsScVertBilinearCoeffMem;
    gScVertUpScaleCoeffMemPtr       = (UInt8 *) gVpsScVertUpScaleCoeffMem;
    gScVertOneToOneScaleCoeffMemPtr = (UInt8 *) gVpsScVertOneToOneScaleCoeffMem;
    gScVertDownScaleCoeffMemPtr     = (UInt8 *) gVpsScVertDownScaleCoeffMem;
    gScHorzUpScaleCoeffMemPtr       = (UInt8 *) gVpsScHorzUpScaleCoeffMem;
    gScHorzOneToOneScaleCoeffMemPtr = (UInt8 *) gVpsScHorzOneToOneScaleCoeffMem;
    gScHorzDownScaleCoeffMemPtr     = (UInt8 *) gVpsScHorzDownScaleCoeffMem;

    /* Init the coeff memories */
    BspUtils_memcpy(
        gScVertBilinearCoeffMemPtr,
        gVpsScVertBilinearCoeff,
        sizeof (gVpsScVertBilinearCoeff));
    BspUtils_memcpy(
        gScVertUpScaleCoeffMemPtr,
        gVpsScVertUpScaleCoeff,
        sizeof (gVpsScVertUpScaleCoeff));
    BspUtils_memcpy(
        gScVertOneToOneScaleCoeffMemPtr,
        gVpsScVertOneToOneScaleCoeff,
        sizeof (gVpsScVertOneToOneScaleCoeff));
    BspUtils_memcpy(
        gScVertDownScaleCoeffMemPtr,
        gVpsScVertDownScaleCoeff,
        sizeof (gVpsScVertDownScaleCoeff));
    BspUtils_memcpy(
        gScHorzUpScaleCoeffMemPtr,
        gVpsScHorzUpScaleCoeff,
        sizeof (gVpsScHorzUpScaleCoeff));
    BspUtils_memcpy(
        gScHorzOneToOneScaleCoeffMemPtr,
        gVpsScHorzOneToOneScaleCoeff,
        sizeof (gVpsScHorzOneToOneScaleCoeff));
    BspUtils_memcpy(
        gScHorzDownScaleCoeffMemPtr,
        gVpsScHorzDownScaleCoeff,
        sizeof (gVpsScHorzDownScaleCoeff));

    return retval;
}

/**
 *  VpsHal_scDeInit
 *  \brief SC HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_scDeInit(Ptr arg)
{
    UInt32 i;
    for (i = 0; i < scHalObj.numInst; i++)
    {
        /* TODO: GT_assert( VpsHalTrace, scHalObj.scInfo[i].openCnt == 0); */
        scHalObj.scInfo[i].halId    = 0;
        scHalObj.scInfo[i].openCnt  = 0;
        scHalObj.scInfo[i].baseAddr = 0;
    }
    scHalObj.numInst = 0;

    gScVertBilinearCoeffMemPtr      = NULL;
    gScVertUpScaleCoeffMemPtr       = NULL;
    gScVertOneToOneScaleCoeffMemPtr = NULL;
    gScVertDownScaleCoeffMemPtr     = NULL;
    gScHorzUpScaleCoeffMemPtr       = NULL;
    gScHorzOneToOneScaleCoeffMemPtr = NULL;
    gScHorzDownScaleCoeffMemPtr     = NULL;
    return BSP_SOK;
}

/**
 *  VpsHal_scOpen
 *  \brief Returns the handle to the requested SC instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the SC HAL
 *  configuration APIs.
 *
 *  VpsHal_scInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param instId        VpsHal_ScOpenParams
 *
 *  \return              success     SC instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_scOpen(const VpsHal_ScOpenParams *instId)
{
    VpsHal_Handle  returnHandle = NULL; /* Contains the value to be returned */

    /* Since there was no positive initial value for returnHandle, we use a
     * variable to check if returnHandle was initially NULL or NULL because
     * of an error condition
     */
    Bool           isErrorCondition = FALSE;
    UInt32         i;
    VpsHal_Handle  scHandle = NULL;
    VpsHal_ScInfo *scInfo   = NULL;

    GT_assert(VpsHalTrace, NULL != instId);
    if (instId->halId >= VPSHAL_SC_INST_ID_MAX)
    {
        isErrorCondition = TRUE;
    }
    if (FALSE == isErrorCondition)
    {
        for (i = 0U; i < VPSHAL_SC_MAX_INST; i++)
        {
            scInfo = &(scHalObj.scInfo[i]);
            if (instId->halId == scInfo->halId)
            {
                /* TODO: Fix incorrect check after VPSHAL_SC_INST_ID_MAX
                 *addition */
                if ((VPSHAL_VPE1_SC <= instId->halId) ||
                    (0 == scInfo->openCnt))
                {
                    scInfo->openCnt++;
                    scHandle = (VpsHal_Handle) scInfo;
                    break;
                }
            }
        }
    }

    if (!isErrorCondition)
    {
        returnHandle = scHandle;
    }

    return returnHandle;
}

/**
 *  VpsHal_scClose
 *  \brief Closes specified instance of SC HAL
 *  VpsHal_scInit and scOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_scOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_scClose(VpsHal_Handle handle)
{
    Int32          retval = BSP_SOK;
    VpsHal_ScInfo *scInfo = (VpsHal_ScInfo *) handle;

    GT_assert(VpsHalTrace, NULL != handle);

    if (0 == scInfo->openCnt)
    {
        retval = BSP_EFAIL;
    }
    else
    {
        scInfo->openCnt--;
    }
    return retval;
}

/**
 *  VpsHal_scSetConfig
 *  \brief This function is used to set the scaler parameters in appropriate
 *  scaler register or in the virtual registers created in the register
 *  overlay whose address is passed as the last argument. If last
 *  argument is null, it will set the parameters in registers otherwise
 *  it will set the parameters in the VPDMA register overlay.
 *
 *  \param handle           Scaler Handle
 *  \param config           pointers to structure containing scaler parameters
 *                          While calling this function ensure
 *                          config->advCfg->vsType != VPS_SC_VST_AUTO
 *                          config->advCfg->hsDcmType != VPS_SC_HST_DCM_AUTO
 *                          Use #VpsHal_scGetScFactorConfig to set this
 *                          variables appropriately
 *  \param ovlyPtr          Pointer to memory containing VPDMA register
 *                          overlay for scaler. It can be set to memory
 *                          pointer to program register in overlay or set
 *                          to null to program directly in hardware register
 *
 *  \return                 0 on success, -1 on error
 */
Int32 VpsHal_scSetConfig(VpsHal_Handle       handle,
                         const Vps_ScConfig *config,
                         Ptr                 ovlyPtr)
{
    Int32 ret = 0;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, config->advCfg->vsType != VPS_SC_VST_AUTO);
    GT_assert(VpsHalTrace, config->advCfg->vsType < VPS_SC_VST_MAX);
    GT_assert(VpsHalTrace, config->advCfg->hsDcmType != VPS_SC_HST_DCM_AUTO);
    GT_assert(VpsHalTrace, config->advCfg->hsDcmType < VPS_SC_HST_DCM_MAX);

    /* Set SC0 register configurations */
    VpsHal_scSetNonRTParams(handle, config, ovlyPtr);

    /* Set scaler ratio specific parameters */
    VpsHal_scSetRTParams(handle, config, ovlyPtr);

    return ret;
}

/**
 *  VpsHal_scGetScFactorConfig
 *
 *  \param handle           Scaler Handle
 *  \param config           Pointer to structure containing scaler parameters.
 *  \param scFactorCfg      Pointer to structure scaling factors and scaling
 *                          types. This is the output of this function.
 *
 *  \brief This function is used to get the information that
 *  identifies the scaling factor for the provided configuration.
 *  It also sets the register related to vsType changes.
 */
Int32 VpsHal_scGetScFactorConfig(VpsHal_Handle          handle,
                                 const Vps_ScConfig    *config,
                                 VpsHal_ScFactorConfig *scFactorCfg)
{
    Int32            ret = BSP_SOK;
    UInt32           srcInnerWidth, tarInnerWidth;

    Vps_ScAdvConfig *advCfg = NULL;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != scFactorCfg);

    advCfg = config->advCfg;

    /* -------------------------------------------------------------------------
     * Calculate horizontal scaling configurations.
     * -------------------------------------------------------------------------
     */
    if (TRUE == config->bypass)
    {
        /* Set everything to invalid in case scaler is in bypass, so that the
         * driver knows to not do any scaler coeff configuration for this
         * channel. hScalingSet and vScalingSet don't matter in this case.
         */
        scFactorCfg->hsDcmType   = VPS_SC_HST_DCM_NONE;
        scFactorCfg->hScalingSet = VPS_SC_SET_MAX;
        scFactorCfg->vsType      = VPS_SC_VST_POLYPHASE;
        scFactorCfg->vScalingSet = VPS_SC_SET_MAX;
        scFactorCfg->hPolyBypass = (UInt32) FALSE;
    }
    else
    {
        /* All scaling ratio are calculated based on the inner size of the
         * source and the targer image */
        if (TRUE == config->nonLinear)
        {
            /* For nonlinear scaling, source inner width is height and target
             * inner is calculated based on strip size */
            srcInnerWidth = advCfg->cropHeight;
            tarInnerWidth =
                (UInt32) (advCfg->tarWidth - (config->stripSize << 1U));
        }
        else /* Linear horizontal Scaling */
        {
            /* For linear scaling, inner size is same width */
            srcInnerWidth = advCfg->cropWidth;
            tarInnerWidth = advCfg->tarWidth;
        }

        /* Use upscaling coefficients when target width is more than source
         * width.
         * For downscaling where the downscaling factor is exactly 1/2 or 1/4,
         * polyphase filter does not get used at all, and only decimators are
         * used. For scaling factor 1, neither polyphase filter nor decimators
         * are used.
         */
        scFactorCfg->hsDcmType   = VPS_SC_HST_DCM_NONE;
        scFactorCfg->hPolyBypass = (UInt32) FALSE;
        if (tarInnerWidth > srcInnerWidth)
        {
            scFactorCfg->hsDcmType   = VPS_SC_HST_DCM_NONE;
            scFactorCfg->hScalingSet = VPS_SC_US_SET;
            scFactorCfg->hPolyBypass = (UInt32) FALSE;
        }
        else if (tarInnerWidth == srcInnerWidth)
        {
            scFactorCfg->hPolyBypass = (UInt32) TRUE;
            scFactorCfg->hScalingSet = VPS_SC_SET_1_1;
        }
        else
        {
            UInt32 polyphaseInW, i;
            if (tarInnerWidth > (srcInnerWidth >> 2U))
            {
                /* No decimation for SR [1/4, 1) */
                scFactorCfg->hsDcmType = VPS_SC_HST_DCM_NONE;
            }
            else if (tarInnerWidth > (srcInnerWidth >> 3U))
            {
                /* 2X decimation for SR [1/8, 1/4) */
                scFactorCfg->hsDcmType = VPS_SC_HST_DCM_2X;
            }
            else if (tarInnerWidth > (srcInnerWidth >> 4U))
            {
                /* 2X decimation for SR [1/8, 1/4) */
                scFactorCfg->hsDcmType = VPS_SC_HST_DCM_4X;
            }
            else
            {
                scFactorCfg->hsDcmType = VPS_SC_HST_DCM_NONE;
                ret = BSP_WNON_RECOMMENDED_PARAMS;
            }

            /* Reset as per user-config */
            if (VPS_SC_HST_DCM_AUTO != advCfg->hsDcmType)
            {
                if (scFactorCfg->hsDcmType != advCfg->hsDcmType)
                {
                    ret = BSP_WNON_RECOMMENDED_PARAMS;
                    scFactorCfg->hsDcmType = advCfg->hsDcmType;
                }
            }

            polyphaseInW = srcInnerWidth;
            if (VPS_SC_HST_DCM_2X == scFactorCfg->hsDcmType)
            {
                polyphaseInW = srcInnerWidth >> 1;
            }
            if (VPS_SC_HST_DCM_4X == scFactorCfg->hsDcmType)
            {
                polyphaseInW = (srcInnerWidth >> 2);
            }

            scFactorCfg->hScalingSet = VPS_SC_DS_SET_15_16;
            for (i = VPS_SC_DS_SET_4_16; i < VPS_SC_DS_SET_15_16; i++)
            {
                if ((tarInnerWidth << VPSHAL_SC_COEFF_SCALE_SHIFT) <=
                    (polyphaseInW * ((i - VPS_SC_DS_SET_4_16) + 5U)))
                {
                    scFactorCfg->hScalingSet = i;
                    break;
                }
            }

            if (polyphaseInW == tarInnerWidth)
            {
                scFactorCfg->hPolyBypass = (UInt32) TRUE;
            }
            else
            {
                scFactorCfg->hPolyBypass = (UInt32) FALSE;
            }

            if (VPS_SC_HST_DCM_AUTO != advCfg->hsDcmType)
            {
                GT_assert(VpsHalTrace,
                          scFactorCfg->hPolyBypass == advCfg->hPolyBypass);
            }
        }

        /* -----------------------------------------------------------------
         * Calculate vertical scaling configurations.
         * -----------------------------------------------------------------
         */
        /* Check if upscaling */
        if (advCfg->tarHeight > advCfg->cropHeight)
        {
            /* Always use polyphase for upscaling. */
            scFactorCfg->vsType      = VPS_SC_VST_POLYPHASE;
            scFactorCfg->vScalingSet = VPS_SC_US_SET;
        }
        else if (advCfg->tarHeight == advCfg->cropHeight)
        {
            /* 1-1 Scaling */
            scFactorCfg->vsType      = VPS_SC_VST_POLYPHASE;
            scFactorCfg->vScalingSet = VPS_SC_SET_1_1;
        }
        else /* Down Scaling */
        {
            /* Determine the type of vertical scaling filter to be used. Use
             * RAV filter for downscaling more than (1/4)x and polyphase for
             * scaling factor lower than that.
             */
            UInt32 tmp, i;
            UInt32 polyphaseInH = advCfg->cropHeight;
            scFactorCfg->vsType = VPS_SC_VST_POLYPHASE;
            tmp = (UInt32) (advCfg->tarHeight << VPSHAL_SC_COEFF_SCALE_SHIFT);

            scFactorCfg->vScalingSet = VPS_SC_DS_SET_15_16;
            for (i = VPS_SC_DS_SET_3_16; i < VPS_SC_DS_SET_15_16; i++)
            {
                if (tmp <= (polyphaseInH * ((i - VPS_SC_DS_SET_3_16) + 4U)))
                {
                    scFactorCfg->vScalingSet = i;
                    break;
                }
            }

            if (advCfg->tarHeight < (advCfg->cropHeight >> 2U))
            {
                /* Should use RAV for factor < (1/4)x. */
                scFactorCfg->vsType = VPS_SC_VST_RAV;
                /* Coeff need not be loaded for RAV!! */
                scFactorCfg->vScalingSet = VPS_SC_SET_MAX;
            }
        }
        /* Reset as per user-config */
        if (VPS_SC_VST_AUTO != advCfg->vsType)
        {
            if (scFactorCfg->vsType != advCfg->vsType)
            {
                scFactorCfg->vsType = advCfg->vsType;
                ret = BSP_WNON_RECOMMENDED_PARAMS;
            }
        }
    }

    GT_5trace(VpsHalTrace, GT_DEBUG,
              "Width %d->%d: hsDcmType: %d, hScalingSet: %d, hPolyBypass: %d\r\n",
              advCfg->cropWidth, advCfg->tarWidth,
              scFactorCfg->hsDcmType, scFactorCfg->hScalingSet,
              scFactorCfg->hPolyBypass);
    GT_4trace(VpsHalTrace, GT_DEBUG,
              "Height %d->%d: vsType: %d, vScalingSet: %d\r\n",
              advCfg->cropHeight, advCfg->tarHeight, scFactorCfg->vsType,
              scFactorCfg->vScalingSet);

    GT_5trace(VpsHalTrace, GT_DEBUG,
              "%d,%d,%d,%d,%d,",
              advCfg->cropWidth, advCfg->tarWidth,
              scFactorCfg->hsDcmType, scFactorCfg->hScalingSet,
              scFactorCfg->hPolyBypass);
    GT_4trace(VpsHalTrace, GT_DEBUG,
              "%d,%d,%d,%d\r\n",
              advCfg->cropHeight, advCfg->tarHeight, scFactorCfg->vsType,
              scFactorCfg->vScalingSet);

    return (ret);
}

/**
 *  void VpsHal_scSetNonRTParams
 *  \brief Function is used to set registers which are NOT allowed to be changed
 *  at run-time. These include peaking/ED config, some thresholds, lin/non-lin
 *  scaling type, etc.
 *
 *  \param handle           Scaler Handle
 *  \param config           Pointer to structure containing scaler parameters.
 *                          While calling this function ensure
 *                          config->vsType != VPS_SC_VST_AUTO
 *                          config->hsDcmType != VPS_SC_HST_DCM_AUTO
 *  \param ovlyPtr          VPDMA register overlay pointer
 *
 *  \return                 None
 */
void VpsHal_scSetNonRTParams(VpsHal_Handle       handle,
                             const Vps_ScConfig *config,
                             Ptr                 ovlyPtr)
{
    UInt32           value   = 0;
    VpsHal_ScInfo   *scInfo  = NULL;
    Vps_ScAdvConfig *advCfg  = NULL;
    UInt32          *wordPtr = (UInt32 *) ovlyPtr;
    UInt32          *tempPtr;

    scInfo = (VpsHal_ScInfo *) handle;
    advCfg = config->advCfg;

    /* Non-RT params will always be called before RT params, it will assumed
     * SC0 initial value to be zero.
     */
    if (FALSE == config->bypass)
    {
        /* Check for the valid value of parameters */
        /* TODO: GT_assert( VpsHalTrace, (0 == scCheckParams(handle, config)));
        **/

        value &= ~((UInt32) SC_CFG_0_SC_BYPASS_MASK);

        /* Set the input and output frame format in the scaler config0
         * register */
        if (FVID2_SF_INTERLACED == advCfg->inFrameMode)
        {
            value |= SC_CFG_0_INTERLACE_I_MASK;
        }
        else /* Progressive input frame */
        {
            value &= ~((UInt32) SC_CFG_0_INTERLACE_I_MASK);
        }

        if (FVID2_SF_INTERLACED == advCfg->outFrameMode)
        {
            value |= SC_CFG_0_INTERLACE_O_MASK;
        }
        else /* Progressive output frame */
        {
            value &= ~((UInt32) SC_CFG_0_INTERLACE_O_MASK);
        }

        /* If cropping size is not same as the source frame size, enable
         * trimming */
        if ((advCfg->srcWidth != advCfg->cropWidth) ||
            (advCfg->srcHeight != advCfg->cropHeight))
        {
            value |= SC_CFG_0_ENABLE_TRIM_MASK;
        }
        else /* Since crop and source size are same, disable trimming */
        {
            value &= ~((UInt32) SC_CFG_0_ENABLE_TRIM_MASK);
        }

        /* Invert FID if it is set */
        if (FVID2_FIDPOL_INVERT == advCfg->fidPol)
        {
            value |= SC_CFG_0_INVT_FID_MASK;
        }
        else /* Field ID will be used without inversion */
        {
            value &= ~((UInt32) SC_CFG_0_INVT_FID_MASK);
        }

        /* Enable Self Generate FID feature if it is enabled */
        if (VPS_SC_SELF_GEN_FID_ENABLE == advCfg->selfGenFid)
        {
            value |= SC_CFG_0_ENABLE_FID_SELFGEN_MASK;
        }
        else /* Disable Self Generate FID */
        {
            value &= ~((UInt32) SC_CFG_0_ENABLE_FID_SELFGEN_MASK);
        }

        /* Enable nonlinear Algorighm */
        if (TRUE == config->nonLinear)
        {
            value &= ~((UInt32) SC_CFG_0_LINEAR_MASK);
        }
        else
        {
            value |= SC_CFG_0_LINEAR_MASK;
        }

        /* Enable Peaking filter */
        value &= ~((UInt32) SC_CFG_0_ENABLE_Y_PK_MASK);
        if (TRUE == config->enablePeaking)
        {
            value |= SC_CFG_0_ENABLE_Y_PK_MASK;
        }

        /* Enable Edge Detection */
        value &= ~((UInt32) SC_CFG_0_ENABLE_EV_MASK);
        if (TRUE == config->enableEdgeDetect)
        {
            value |= SC_CFG_0_ENABLE_EV_MASK;
        }
    }
    else
    {
        value |= SC_CFG_0_SC_BYPASS_MASK;
    }

    /* Set the Configuration in SC_CFG0 register */
    if (NULL == ovlyPtr)
    {
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_0, value);
    }
    else /* Set the configuration in the VPDMA overlay virtual registers */
    {
        /* Set the configuration in the VPDMA register overlay */
        tempPtr = wordPtr + scInfo->virtRegOffset[SC_CONFIG_OVLY_CFG_SC0_IDX];
        HW_WR_REG32(tempPtr, value);
    }

    if ((NULL != advCfg->peakingCfg) && (TRUE == config->enablePeaking))
    {
        VpsHal_scSetPeakingParams(scInfo, advCfg->peakingCfg);
    }

    return;
}

/**
 *  void VpsHal_scSetRTParams
 *  \brief Function is used to set registers which are allowed to be changed at
 *  run-time. These are the scaling ratio, dimensions and position specific
 *  parameters in the VPDMA register overlay. This function will only change
 *  scaling ratio specific parameters. It will not change scaling algorithm
 *  or parameters configurable in CFG_SC0 register.
 *
 *  \param handle           Scaler Handle
 *  \param config           Pointer to structure containing scaler parameters.
 *                          While calling this function ensure
 *                          config->vsType != VPS_SC_VST_AUTO
 *                          config->hsDcmType != VPS_SC_HST_DCM_AUTO
 *  \param ovlyPtr          VPDMA register overlay pointer
 *
 *  \return                 None
 */
void VpsHal_scSetRTParams(VpsHal_Handle       handle,
                          const Vps_ScConfig *config,
                          Ptr                 ovlyPtr)
{
    /* If the overlay pointer is null, config need to be set in
     * the register otherwise config need to be set in the register overlay.
     * Register overlay is used for both memory to memory transfer and
     * runtime configuration. Since number of registers are same for
     * mem-to-mem driver as well runtime configuration, there is no need
     * to keep two separate sets of register overlay offsets. */

    UInt32          *scRegsOffset;
    UInt32           shift;
    UInt32           ravFactor;
    UInt32           accInit, accIncr, offsetA, offsetB;
    Int32            nonLinearInit, nonLinearAcc;
    VpsHal_ScInfo   *scInfo = NULL;
    Vps_ScAdvConfig *advCfg = NULL;
    UInt32           value;
    UInt32          *wordPtr = (UInt32 *) ovlyPtr;
    UInt32          *tempPtr;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != config->advCfg);

    /* Get the pointer to register offsets array */
    scInfo       = (VpsHal_ScInfo *) handle;
    scRegsOffset = scInfo->virtRegOffset;
    advCfg       = config->advCfg;
    /* TODO: GT_assert( VpsHalTrace, (NULL != scRegsOffset)); */

    /* First update Scaler mode in SC0 register */
    if (NULL == ovlyPtr)
    {
        /* Get the Value from SC0 Register */
        value = HW_RD_REG32(scInfo->baseAddr + SC_CFG_0);
    }
    else
    {
        tempPtr = wordPtr + scInfo->virtRegOffset[SC_CONFIG_OVLY_CFG_SC0_IDX];
        value   =
            HW_RD_REG32(tempPtr);
    }

    /* Set the decimator setting algorithm */
    value &= ~((UInt32) (SC_CFG_0_AUTO_HS_MASK |
                         SC_CFG_0_DCM_2X_MASK  |
                         SC_CFG_0_DCM_4X_MASK));
    switch (advCfg->hsDcmType)
    {
        case VPS_SC_HST_DCM_2X:
            value |= SC_CFG_0_DCM_2X_MASK;
            break;
        case VPS_SC_HST_DCM_4X:
            value |= SC_CFG_0_DCM_4X_MASK;
            break;
        default:
            break;
    }

    /* Set the Horizontal Polyphase Bypass mode */
    value &= ~((UInt32) SC_CFG_0_HP_BYPASS_MASK);
    if (TRUE == advCfg->hPolyBypass)
    {
        value |= SC_CFG_0_HP_BYPASS_MASK;
    }

    /* Set the Vertical Scaling Algorithm */
    if (VPS_SC_VST_RAV == advCfg->vsType)
    {
        /* Enable Running Average Filter in CFG0 */
        value |= SC_CFG_0_USE_RAV_MASK;
    }
    else
    {
        value &= ~((UInt32) SC_CFG_0_USE_RAV_MASK);
    }
    /* Set the Configuration in SC_CFG0 register */
    if (NULL == ovlyPtr)
    {
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_0, value);
    }
    else /* Set the configuration in the VPDMA overlay virtual registers */
    {
        /* Set the configuration in the VPDMA register overlay */
        tempPtr = wordPtr + scInfo->virtRegOffset[SC_CONFIG_OVLY_CFG_SC0_IDX];
        HW_WR_REG32(tempPtr, value);
    }

    /* Set the Size Parameters */
    if (NULL == ovlyPtr)
    {
        /* Set the Size Parameters */
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_24,
                    VpsHal_scMakeScCfg24Reg(advCfg));
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_25,
                    VpsHal_scMakeScCfg25Reg(advCfg));

        HW_WR_REG32(scInfo->baseAddr + SC_CFG_4,
                    VpsHal_scMakeScCfg4Reg(advCfg));
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_5,
                    VpsHal_scMakeScCfg5Reg(advCfg));
    }
    else
    {
        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC24_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scMakeScCfg24Reg(advCfg));

        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC25_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scMakeScCfg25Reg(advCfg));

        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC4_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scMakeScCfg4Reg(advCfg));

        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC5_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scMakeScCfg5Reg(advCfg));
    }

    /* TODO: How to calculate value of Col Acc Offset - copied from Ne/Ce*/
    if (NULL == ovlyPtr)
    {
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_12, 0);
    }
    else
    {
        HW_WR_REG32((wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC12_IDX]), 0U);
    }

    if (VPS_SC_VST_POLYPHASE == advCfg->vsType)
    {
        /* Set the polyphase filter parameters for vertical scaler from
         * input/output heights or copy from config as per phInfoMode */
        VpsHal_scCalVertPolyphaseParams(config, &accIncr, &offsetA, &offsetB);
        if (NULL == ovlyPtr)
        {
            HW_WR_REG32(scInfo->baseAddr + SC_CFG_1, accIncr);
            HW_WR_REG32(scInfo->baseAddr + SC_CFG_2, offsetA);
            HW_WR_REG32(scInfo->baseAddr + SC_CFG_3, offsetB);
        }
        else
        {
            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC1_IDX];
            HW_WR_REG32(tempPtr, accIncr);

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC2_IDX];
            HW_WR_REG32(tempPtr, offsetA);

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC3_IDX];
            HW_WR_REG32(tempPtr, offsetB);
        }
    }
    if (VPS_SC_VST_RAV == advCfg->vsType)
    {
        /* Set the running average filter parameters for vertical scaler
         * from input/output heights or copy from config as per phInfoMode
         */
        VpsHal_scCalVertRavParams(advCfg, &ravFactor, &accInit);
        if (NULL == ovlyPtr)
        {
            HW_WR_FIELD32(scInfo->baseAddr + SC_CFG_13,
                          SC_CFG_13_SC_FACTOR_RAV,
                          ravFactor);
            HW_WR_REG32(scInfo->baseAddr + SC_CFG_6, accInit);
        }
        else
        {
            UInt32 tmp;

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC13_IDX];
            tmp     = HW_RD_REG32(tempPtr);
            HW_SET_FIELD32(tmp, SC_CFG_13_SC_FACTOR_RAV, ravFactor);

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC13_IDX];
            HW_WR_REG32(tempPtr, tmp);

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC6_IDX];
            HW_WR_REG32(tempPtr, accInit);
        }
    }

    /* Set the linear horizontal scaling parameters */
    if (NULL == ovlyPtr)
    {
        /* Linear parameters must be calculated first to get
         * the value of shift */
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_9,
                    VpsHal_scCalHorzLinearAccInc(config, &shift));
        /* Set the size of left and right strip for nonlinear scaling*/
        HW_WR_REG32(scInfo->baseAddr + SC_CFG_8,
                    VpsHal_scMakeScCfg8Reg(config));
        /* TODO: Fix this Ne/Ce assumes this
         * SC_CFG_4_LIN_ACC_INC_U to be always zero -
         * this may not be always true */
        HW_WR_FIELD32(scInfo->baseAddr + SC_CFG_4,
                      SC_CFG_4_LIN_ACC_INC_U,
                      0U);
    }
    else
    {
        UInt32 tmp;

        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC9_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scCalHorzLinearAccInc(config, &shift));
        /* Set the size of left and right strip for nonlinear scaling*/
        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC8_IDX];
        HW_WR_REG32(tempPtr, VpsHal_scMakeScCfg8Reg(config));

        /* TODO: Fix this Ne/Ce assumes this
         * SC_CFG_4_LIN_ACC_INC_U to be always zero -
         * this may not be always true */

        tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC4_IDX];
        tmp     = HW_RD_REG32(tempPtr);
        tmp    |= VpsHal_scMakeScCfg4Reg(advCfg);
        HW_WR_REG32(tempPtr, tmp);
    }

    if (NULL == ovlyPtr)
    {
        if (TRUE == config->nonLinear)
        {
            VpsHal_scCalHorzNonLinearParams(
                config,
                shift,
                &nonLinearInit,
                &nonLinearAcc);

            HW_WR_REG32(scInfo->baseAddr + SC_CFG_10, nonLinearInit);
            HW_WR_REG32(scInfo->baseAddr + SC_CFG_11, nonLinearAcc);

            HW_WR_FIELD32(scInfo->baseAddr + SC_CFG_4,
                          SC_CFG_4_NLIN_ACC_INIT_U,
                          0U);
            /* TODO: Fix this Ne/Ce assumes this
             * SC_CFG_5_NLIN_ACC_INC_U to be always zero
             * -
             * this may not be always true */
            HW_WR_FIELD32(scInfo->baseAddr + SC_CFG_5,
                          SC_CFG_5_NLIN_ACC_INC_U,
                          0U);
        }
    }
    else
    {
        if (TRUE == config->nonLinear)
        {
            UInt32 tmp;

            /* Set the nonlinear horizontal scaling parameters */
            VpsHal_scCalHorzNonLinearParams(
                config,
                shift,
                &nonLinearInit,
                &nonLinearAcc);

            tempPtr = (wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC10_IDX]);
            HW_WR_REG32(tempPtr, nonLinearInit);

            tempPtr = (wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC11_IDX]);
            HW_WR_REG32(tempPtr, nonLinearAcc);

            /* Adding for completeness - following two lines were not present
             * in original code */

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC4_IDX];
            tmp     = HW_RD_REG32(tempPtr);
            HW_SET_FIELD32(tmp, SC_CFG_4_NLIN_ACC_INIT_U, 0U);
            HW_WR_REG32(tempPtr, tmp);

            /* TODO: Fix this Ne/Ce assumes this
             * SC_CFG_5_NLIN_ACC_INC_U to be always zero
             * -
             * this may not be always true */

            tempPtr = wordPtr + scRegsOffset[SC_CONFIG_OVLY_CFG_SC5_IDX];
            tmp     = HW_RD_REG32(tempPtr);
            HW_SET_FIELD32(tmp, SC_CFG_5_NLIN_ACC_INC_U, 0U);
            HW_WR_REG32(tempPtr, tmp);
        }
    }

    return;
}

/**
 *  VpsHal_scGetVpdmaConfigDest
 *  \brief Returns the VPDMA configuration destination to program coefficients
 *  for this scaler instance.
 *
 *  \param handle           Scaler Handle
 *
 *  \return                 VPDMA configuration destination
 */
VpsHal_VpdmaConfigDest VpsHal_scGetVpdmaConfigDest(VpsHal_Handle handle)
{
    GT_assert(VpsHalTrace, NULL != handle);
    return (((VpsHal_ScInfo *) handle)->coeffConfigDest);
}

/**
 *  void VpsHal_scGetRegOvlySize
 *  \brief Function to get the VPDMA register overlay size required to
 *  store scaler registers. This overlay is mainly used for stoing
 *  register for the runtime configuration as well as for the memory
 *  to memory driver where configuration changes for each channel.
 *
 *  \param handle           Scaler Handle
 *
 *  \return                 Register Overlay size
 */
UInt32 VpsHal_scGetConfigOvlySize(VpsHal_Handle handle)
{
    return (((VpsHal_ScInfo *) handle)->regOvlySize);
}

/**
 *  void VpsHal_scCreateConfigOvly
 *  \brief This function is used to create the complete VPDMA register overlay
 *  for scaler registers. It just create the overlay but does not
 *  initialize the virtual registers with the configuration.
 *  Configuration can be done by calling Sc_setParams function.
 *
 *  \param handle           Scaler Handle
 *  \param configOvlyPtr    Pointer to memory where VPDMA overlay will be
 *                          stored
 *
 *  \return                 0 on success, -1 on error
 */
Int32 VpsHal_scCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    Int32 retVal = BSP_EFAIL;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != configOvlyPtr);

    /* Create the register overlay */
    retVal = VpsHal_vpdmaCreateRegOverlay(
        ((VpsHal_ScInfo *) handle)->regOffset,
        SC_CONFIG_OVLY_NUM_IDX,
        configOvlyPtr);

    return (retVal);
}

/**
 *  void VpsHal_scGetCoeffOvlySize
 *  \brief This function is used to get the memory size required to
 *  store coefficients. It returns size in terms of bytes. Upper
 *  layer can allocate the memory and pass this memory with the
 *  coefficients to fill the the memory with coefficients.
 *
 *  \param handle            Scaler Handle
 *  \param horzCoeffOvlySize Location to return size of horizontal scaling
 *                           coefficients
 *  \param vertCoeffOvlySize Location to return size of vertical scaling
 *                           coefficients
 *  \param vertBilinearCoeffOvlySize Location to return size of vertical
 *                                   bilinear scaling coefficients. If not HQ
 *                                   scaler, value returned shall be 0.
 *
 *  \return                 None
 */
void VpsHal_scGetCoeffOvlySize(VpsHal_Handle handle,
                               UInt32       *horzCoeffOvlySize,
                               UInt32       *vertCoeffOvlySize,
                               UInt32       *vertBilinearCoeffOvlySize)
{
    VpsHal_ScInfo *scInfo = (VpsHal_ScInfo *) handle;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != horzCoeffOvlySize);
    GT_assert(VpsHalTrace, NULL != vertCoeffOvlySize);
    GT_assert(VpsHalTrace, NULL != vertBilinearCoeffOvlySize);

    *horzCoeffOvlySize = VPSHAL_SC_HORZ_COEFF_OVLY_SIZE;
    *vertCoeffOvlySize = VPSHAL_SC_VERT_COEFF_OVLY_SIZE;
    if (TRUE == scInfo->isHqScaler)
    {
        *vertBilinearCoeffOvlySize = VPSHAL_SC_BILINEAR_COEFF_OVLY_SIZE;
    }
    else
    {
        *vertBilinearCoeffOvlySize = 0U;
    }

    return;
}

/**
 *  VpsHal_scSetUserCoeff
 *
 *  \brief  If the application has its own set of coefficients and does not
 *          want to use driver provided coefficient, this function is used. It
 *          copies the user provided coefficients locally so that they can be
 *          used instead of the defaults during scaling.
 *          Coefficient Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  coeff           Structure containing all user-provided scaler
 *                          coefficients.
 *
 *  \return 0               on Success
 *          -1              on Error
 */
Int32 VpsHal_scSetUserCoeff(VpsHal_Handle      handle,
                            const Vps_ScCoeff *coeff)
{
    Int32          ret    = 0;
    VpsHal_ScInfo *scInfo = (VpsHal_ScInfo *) handle;

    GT_assert(VpsHalTrace, (NULL != handle));

    /* If coeff is not NULL, then new coeffs are to be set. */
    if (NULL != coeff)
    {
        /* It is assumed that user has provided all the coefficients. */
        BspUtils_memcpy(gUserScCoeff, coeff, sizeof (Vps_ScCoeff));
        scInfo->userScCoeff = gUserScCoeff;
    }

    return (ret);
}

/**
 *  VpsHal_scGetCoeffOvlyMemPtr
 *  \brief Function is used to get the coefficient overlay memory pointers
 *  with the standard coefficients provided by the IP team or if with the
 *  user provided memeory pointer in case user has given the coeff.
 *  The coefficients are selected based on the scaling ratio.
 */
Int32 VpsHal_scGetCoeffOvlyMemPtr(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *horzCoeffMemPtr,
    Ptr                         *vertCoeffMemPtr,
    Ptr                         *vertBilinearCoeffMemPtr)
{
    Int32          ret    = 0;
    VpsHal_ScInfo *scInfo = (VpsHal_ScInfo *) handle;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != horzCoeffMemPtr);
    GT_assert(VpsHalTrace, NULL != vertCoeffMemPtr);
    GT_assert(VpsHalTrace, NULL != vertBilinearCoeffMemPtr);

    /* Check if user has provided coeffs */
    if (NULL == scInfo->userScCoeff)
    {
        /* Get a pointer to coefficient memory for Horizontal scaler */
        VpsHal_scGetStdHorzCoeffOvly(handle, config, horzCoeffMemPtr);

        /* Get pointers to coefficient memories for Vertical scaler */
        VpsHal_scGetStdVertCoeffOvly(handle,
                                     config,
                                     vertCoeffMemPtr,
                                     vertBilinearCoeffMemPtr);
    }
    else
    {
        /*
         * Use the user-provided coeffs instead.
         */
        /* Return pointers to the horizontal, vertical and bilinear coeffs. The
         * pointer to horizontal luma coeffs has the chroma coeffs after it
         * for each set of coefficients.
         */
        *horzCoeffMemPtr = &(scInfo->userScCoeff->hsLuma);
        *vertCoeffMemPtr = &(scInfo->userScCoeff->vsLuma);

        if (TRUE == (((VpsHal_ScInfo *) handle)->isHqScaler))
        {
            *vertBilinearCoeffMemPtr = &(scInfo->userScCoeff->vsBilinearLuma);
        }
        else
        {
            /* Return NULL for non-HQ Scaler */
            *vertBilinearCoeffMemPtr = NULL;
        }
    }

    GT_5trace(VpsHalTrace, GT_DEBUG,
              "hScalingSet: %d, vScalingSet: %d, "
              "horzCoeffMemPtr: 0x%0.8x, vertCoeffMemPtr: 0x%0.8x, "
              "vertBilinearCoeffMemPtr: 0x%0.8x, \r\n",
              config->hScalingSet, config->vScalingSet,
              *horzCoeffMemPtr, *vertCoeffMemPtr, *vertBilinearCoeffMemPtr);

    return (ret);
}

/**
 *  static Int32 VpsHal_scSetPeakingParams(VpsHal_ScInfo *scInfo,
 *                                          Vps_ScPeakingConfig *pParams)
 *
 *  \brief  Function to the peaking block parameters in the scaler register.
 *          Expert values for this block is set at the time of init. If
 *          required, expert user can change parameters for this block by
 *          modifying macros given for the peaking block.
 *          scInfo      must be correct pointer
 *          pParams     must be correct pointer
 *
 *  \param  scInfo      Pointer to scaler information structure
 *  \param  pParams     Pointer to structure containing peaking parameters
 *
 *  \return  0          on Success
 *          -1          on Error
 */
static Int32 VpsHal_scSetPeakingParams(const VpsHal_ScInfo       *scInfo,
                                       const Vps_ScPeakingConfig *pParams)
{
    UInt32 regVal;

    GT_assert(VpsHalTrace, NULL != scInfo);
    GT_assert(VpsHalTrace, NULL != pParams);
    GT_assert(VpsHalTrace,
              pParams->nlLowThreshold < pParams->nlHighThreshold);

    /* Set the High Pass Filter Coefficients in the register */
    regVal = 0;
    HW_SET_FIELD32(regVal, SC_CFG_19_HPF_COEFF0, (UInt32) pParams->hpfCoeff[0]);
    HW_SET_FIELD32(regVal, SC_CFG_19_HPF_COEFF1, (UInt32) pParams->hpfCoeff[1]);
    HW_SET_FIELD32(regVal, SC_CFG_19_HPF_COEFF2, (UInt32) pParams->hpfCoeff[2]);
    HW_SET_FIELD32(regVal, SC_CFG_19_HPF_COEFF3, (UInt32) pParams->hpfCoeff[3]);
    HW_WR_REG32(scInfo->baseAddr + SC_CFG_19, regVal);

    /* Set the Clipping limit and decimal point for coefficient in
     * register */
    regVal = 0;
    HW_SET_FIELD32(regVal, SC_CFG_20_HPF_COEFF4, (UInt32) pParams->hpfCoeff[4]);
    HW_SET_FIELD32(regVal, SC_CFG_20_HPF_COEFF5, (UInt32) pParams->hpfCoeff[5]);
    HW_SET_FIELD32(
        regVal, SC_CFG_20_HPF_NORM_SHIFT, (UInt32) pParams->hpfNormShift);
    HW_SET_FIELD32(regVal, SC_CFG_20_NL_LIMIT, (UInt32) pParams->nlClipLimit);
    HW_WR_REG32(scInfo->baseAddr + SC_CFG_20, regVal);

    /* Set the Low threshold and low slope gain in the register */
    regVal = 0;
    HW_SET_FIELD32(
        regVal, SC_CFG_21_NL_LO_THRLD, (UInt32) pParams->nlLowThreshold);
    HW_SET_FIELD32(
        regVal, SC_CFG_21_NL_LO_SLOPE, (UInt32) pParams->nlLowSlopeGain);
    HW_WR_REG32(scInfo->baseAddr + SC_CFG_21, regVal);

    /* Set the High Threshold and slope shift in the register */
    regVal = 0;
    HW_SET_FIELD32(
        regVal, SC_CFG_22_NL_HI_THRLD, (UInt32) pParams->nlHighThreshold);
    HW_SET_FIELD32(
        regVal, SC_CFG_22_NL_HI_SLOPE_SHIFT, (UInt32) pParams->nlHighThreshold);
    HW_WR_REG32(scInfo->baseAddr + SC_CFG_22, regVal);

    /* Enable Peaking block in the register */
    HW_WR_FIELD32(scInfo->baseAddr + SC_CFG_0,
                  SC_CFG_0_ENABLE_Y_PK,
                  (UInt32) TRUE);

    return BSP_SOK;
}

/**
 *  static inline void VpsHal_scCalVertPolyphaseParams(
 *                          const Vps_ScConfig *config,
 *                          UInt32 *rowAccInc,
 *                          UInt32 *offsetA,
 *                          UInt32 *offsetB)
 *
 *  \brief  Function to calculate parameters for polyphase vertical scaler. It
 *          calculates Row accumulator increment and offset value and returns
 *          them to the caller. The value returned from this function can be
 *          directly set into register
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  rowAccInc   Row Accumulator Increment Value
 *  \param  offsetA     Vertical Offset for top field or frame
 *  \param  offsetB     Vertical Offset for bottom field
 *
 *  \return None
 */
static inline void VpsHal_scCalVertPolyphaseParams(
    const Vps_ScConfig *config,
    UInt32             *rowAccInc,
    UInt32             *offsetA,
    UInt32             *offsetB)
{
    Vps_ScAdvConfig *advCfg = NULL;

    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != config->advCfg);
    GT_assert(VpsHalTrace, NULL != rowAccInc);
    GT_assert(VpsHalTrace, NULL != offsetA);
    GT_assert(VpsHalTrace, NULL != offsetB);

    advCfg = config->advCfg;

    if (advCfg->phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP)
    {
        *rowAccInc = advCfg->polyphasePhInfo.rowAccInc;
        *offsetA   = advCfg->polyphasePhInfo.rowAccOffset;
        *offsetB   = advCfg->polyphasePhInfo.rowAccOffsetB;
    }
    else
    {
        *offsetA = 0U; /* TODO: How to calculate offsetA */
        if (FVID2_SF_INTERLACED == advCfg->inFrameMode)
        {
            if (FVID2_SF_INTERLACED == advCfg->outFrameMode)
            {
                *rowAccInc = (((UInt32) ((advCfg->cropHeight << 2U) - 1U)) <<
                              SC_ROW_ACC_INC_SHIFT) /
                             ((advCfg->tarHeight << 2U) - 1U);
                *offsetB = (((UInt32) ((advCfg->cropHeight - 1U)) <<
                             (SC_ROW_ACC_INC_SHIFT - 1U)) /
                            (advCfg->tarHeight - 1U)) - 1U;
            }
            else /* Progressive output frame */
            {
                *rowAccInc = (((UInt32) ((advCfg->cropHeight << 2U) - 1U)) <<
                              SC_ROW_ACC_INC_SHIFT) /
                             (((UInt32) (advCfg->tarHeight - 1U)) << 2U);
                *offsetB =
                    (UInt32) ((Int32) ((UInt32) 1U <<
                                       (SC_ROW_ACC_INC_SHIFT - 1U)) * (-((int32_t) 1)));
            }
        }
        else /* Progressive input frame */
        {
            if (FVID2_SF_INTERLACED == advCfg->outFrameMode)
            {
                *rowAccInc = (((UInt32) (advCfg->cropHeight - 1U)) <<
                              (SC_ROW_ACC_INC_SHIFT + 1U)) /
                             ((advCfg->tarHeight << 2U) - 1U);
                *offsetB = (((UInt32) (advCfg->cropHeight - 1U)) <<
                            SC_ROW_ACC_INC_SHIFT) /
                           (advCfg->tarHeight - 1U);
            }
            else /* Progressive output frame */
            {
                *rowAccInc = (((UInt32) (advCfg->cropHeight - 1U)) <<
                              SC_ROW_ACC_INC_SHIFT) /
                             (advCfg->tarHeight - 1U);
                *offsetB = 0U;
            }
        }
        *offsetB += *offsetA;
    }

    return;
}

/**
 *  static inline UInt32 VpsHal_scCalHorzLinearAccInc(
 *                                     const Vps_ScConfig *config,
 *                                     UInt32 *shift)
 *
 *  \brief  Function to calculate linear accumulator increment value and also
 *          shift required to calculate linear as well non-linear parameters.
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  shift       Returns the shift by which width and internal
 *                      width should be right shifted
 *
 *  \return             Linear Accumulator increment value
 */
static inline UInt32 VpsHal_scCalHorzLinearAccInc(const Vps_ScConfig *config,
                                                  UInt32             *shift)
{
    Vps_ScAdvConfig *advCfg       = NULL;
    UInt32           linearAccInc = 0, hiValue, loValue, srcInnerWidth,
                     tarInnerWidth;

    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != config->advCfg);
    GT_assert(VpsHalTrace, NULL != shift);
    GT_assert(VpsHalTrace, config->advCfg->hsDcmType != VPS_SC_HST_DCM_AUTO);

    advCfg = config->advCfg;

    *shift = 0;
    if (VPS_SC_HST_DCM_2X == advCfg->hsDcmType)
    {
        *shift = 1U;
    }
    if (VPS_SC_HST_DCM_4X == advCfg->hsDcmType)
    {
        *shift = 2U;
    }

    if (TRUE == config->nonLinear)
    {
        srcInnerWidth = advCfg->cropHeight;
        tarInnerWidth = (UInt32) (advCfg->tarWidth - (config->stripSize << 0x1U));
    }
    else /* Linear Horizontal Scaling */
    {
        srcInnerWidth = advCfg->cropWidth;
        tarInnerWidth = advCfg->tarWidth;
    }
    /* Note: Minimum target inner width is 8 such that upper 3 bits required to
     * be programmed is always 0. */
    hiValue = (((srcInnerWidth >> *shift) - 1U) &
               SC_HORZ_HIGH_VALUE_MASK) >> SC_HORZ_HIGH_VALUE_SHIFT;
    loValue = ((UInt32) (((srcInnerWidth >> *shift) - 1U) &
               (~((UInt32) SC_HORZ_HIGH_VALUE_MASK)))) << SC_LINEAR_ACC_INC_SHIFT;
    linearAccInc = VpsHal_scLongDivide(hiValue, loValue, (tarInnerWidth - 1U));

    return (linearAccInc);
}

/**
 *  static inline void VpsHal_scCalHorzNonLinearParams(
 *                          const Vps_ScConfig *config,
 *                          UInt32 shift,
 *                          Int32 *initValue,
 *                          Int32 *incValue)
 *
 *  \brief  Function to calculate non-linear accumulator initial and
 *          increment value. It uses shift returned from scCalHorzLinearAccInc
 *          function and calculates parameters.
 *          scCalHorzLinearAccInc function must be called before calling
 *          this function in order to get value of shift                *
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  shift       As per the equation, width and inner width are
 *                      right shifted by this value
 *  \param  initValue   Row Accumulator initial value
 *  \param  incValue    Row Accumulator increment value
 *
 *  \return None
 */
static inline void VpsHal_scCalHorzNonLinearParams(
    const Vps_ScConfig *config,
    UInt32              shift,
    Int32              *initValue,
    Int32              *incValue)
{
    Vps_ScAdvConfig *advCfg = NULL;
    UInt32           srcLeftStrip;
    UInt32           d, value1, valueK;
    UInt32           hiValue, loValue;
    UInt32           initUvalue, incUvalue;

    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != config->advCfg);
    GT_assert(VpsHalTrace, NULL != initValue);
    GT_assert(VpsHalTrace, NULL != incValue);

    advCfg = config->advCfg;
    /* Only nonlinear configuration will call this function so source inner
     * width will always be source height and there is no need to check wether
     * it is linear or not. */
    srcLeftStrip = ((advCfg->cropWidth >> shift) -
                    (advCfg->cropHeight >> shift)) >> 1U;
    if (advCfg->tarWidth >= advCfg->cropWidth)
    {
        d = 0;
    }
    else /* Down Scaling */
    {
        d = (UInt32) (advCfg->tarWidth - 1U) >> 1U;
    }
    if (0 != config->stripSize)
    {
        /* if Minimum value for stripSize is 3 pixels, then accumulator
         * initial and increment upper value in 35 bit can be assumed to
         * zero */
        value1 = ((config->stripSize) *
                  (config->stripSize - (d << 1U)));
        hiValue = (srcLeftStrip & SC_HORZ_HIGH_VALUE_MASK) >>
                  SC_HORZ_HIGH_VALUE_SHIFT;
        loValue = (srcLeftStrip & (~((UInt32)SC_HORZ_HIGH_VALUE_MASK))) <<
                  SC_NONLINEAR_ACC_INC_SHIFT;
        valueK = VpsHal_scLongDivide(hiValue, loValue, value1);
    }
    else /* Non Zero Strip Size */
    {
        valueK = 0;
    }
    incUvalue  = valueK << 1U;
    *incValue  = (Int32) incUvalue;
    initUvalue = valueK - (2U * valueK * d);
    *initValue = (Int32) initUvalue;

    return;
}

/**
 *  static inline void VpsHal_scCalVertRavParams(const Vps_ScAdvConfig *config,
 *                                                UInt32 *factor,
 *                                                UInt32 *ravInit)
 *
 *  \brief  Function to calculate parameters for running average scaler. It
 *          calculates scaling factor and row accumulator initial value and
 *          returns them to the caller. The value returned from this function
 *          can be directly set into register.
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  factor      Vertical Scaling factor
 *  \param  ravInit     Row Accumulator initial value
 *
 *  \return None
 */
static inline void VpsHal_scCalVertRavParams(const Vps_ScAdvConfig *advCfg,
                                             UInt32                *factor,
                                             UInt32                *ravInit)
{
    Int32  initA, initB;
    UInt32 initAValue;

    GT_assert(VpsHalTrace, (NULL != advCfg));
    GT_assert(VpsHalTrace, (NULL != factor));
    GT_assert(VpsHalTrace, (NULL != ravInit));

    if (advCfg->phInfoMode == VPS_SC_SET_PHASE_INFO_FROM_APP)
    {
        *factor = advCfg->ravPhInfo.ravScFactor;
        initA   = advCfg->ravPhInfo.ravRowAccInit;
        initB   = advCfg->ravPhInfo.ravRowAccInitB;
    }
    else
    {
        *factor = (UInt32) ((advCfg->tarHeight << SC_HORZ_SCALE_SHIFT) /
                            advCfg->cropHeight);

        /* TODO: CSG - removing this seems incorrect. */
        /* TODO: *factor = (*factor & */
        /* CSL_VPS_SC_H_CFG_SC13_CFG_SC_FACTOR_RAV_MASK) << */
        /* TODO:              CSL_VPS_SC_H_CFG_SC13_CFG_SC_FACTOR_RAV_SHIFT; */

        /* Calculate row_acc_init a and b value and set them */
        /* Currently Rajitha's method is used to calculate these values. But
         * this might be changed to Peter's method */
#ifdef SC_USE_RAJITHA_METHOD
        initAValue = *factor + (UInt32) ((1U + *factor) >> 1U);
        initA      = (Int32) initAValue;
        if (initA >= (Int32) SC_VERT_RAV_INIT_MAX)
        {
            initA -= (Int32) SC_VERT_RAV_INIT_MAX;
        }
        initAValue = ((UInt32) 1U + ((UInt32) initA >> 1U)) -
                     ((UInt32) SC_VERT_RAV_INIT_MAX >> 1U);
        initB = (initA + (Int32) initAValue);
        if (initB < 0)
        {
            initB += initA;
            initA += initA;
        }
#else   /* Use Peter's method */
        float scale, delta, int_part, fract_part;
        delta     = (1.0 / scale - 1.0) / 2.0;
        int_part  = floor(delta);
        frac_part = delta - int_part;

        initA = Int32(1024 * (scale + (1.0 - scale) / 2.0) + 0.5);
        initB = Int32(
            1024 * (scale + (1.0 - 2.0 * frac_part) *
                    (1.0 -
                     (1.0 + 2.0 * int_part) * scale) / 2.0) + 0.5);
#endif
    }
    *ravInit = 0;
    HW_SET_FIELD32(*ravInit, SC_CFG_6_ROW_ACC_INIT_RAV, (UInt32) initA);
    HW_SET_FIELD32(*ravInit, SC_CFG_6_ROW_ACC_INIT_RAV_B, (UInt32) initB);
}

/**
 *  static inline UInt32 VpsHal_scMakeScCfg4Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get Target image size in 32 bit
 *          value. Value returned from this function can be directly set into
 *          the register.
 *
 *  \param  config      pointers to structure containing source
 *
 *  \return             target image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg4Reg(const Vps_ScAdvConfig *advCfg)
{
    UInt32 size = 0;

    GT_assert(VpsHalTrace, (NULL != advCfg));

    HW_SET_FIELD32(size, (UInt32) SC_CFG_4_TAR_W, advCfg->tarWidth);
    HW_SET_FIELD32(size, (UInt32) SC_CFG_4_TAR_H, advCfg->tarHeight);

    return (size);
}

/**
 *  static inline UInt32 VpsHal_scMakeScCfg5Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get cropped image size in 32 bit
 *          value. Value returned from this function can be directly set into
 *          the register.
 *
 *  \param  config     pointers to structure containing source
 *
 *  \return            cropped image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg5Reg(const Vps_ScAdvConfig *advCfg)
{
    UInt32 size = 0;

    GT_assert(VpsHalTrace, (NULL != advCfg));

    HW_SET_FIELD32(size, (UInt32) SC_CFG_5_SRC_W, advCfg->cropWidth);
    HW_SET_FIELD32(size, (UInt32) SC_CFG_5_SRC_H, advCfg->cropHeight);

    return (size);
}

/**
 *  static inline UInt32 VpsHal_scMakeScCfg8Reg(const Vps_ScConfig *config)
 *
 *  \brief  Inline Function to calculate and get left and right strip size in
 *          32 bit value. Value returned from this function can be directly
 *          set into the register.
 *
 *  \param  config   pointers to structure containing source
 *
 *  \return          strip size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg8Reg(const Vps_ScConfig *config)
{
    Vps_ScAdvConfig *advCfg;
    UInt32           size = 0, innerWidth;

    GT_assert(VpsHalTrace, (NULL != config));
    GT_assert(VpsHalTrace, (NULL != config->advCfg));

    advCfg = config->advCfg;
    /* Typically strip should be calculated using following equation.
     * left = (advCfg->tarWidth - advCfg->tarHeight) >> 2;
     * right = left + advCfg->tarHeight - 1;
     * But scaler supports non-linear scaling which has inner width different
     * from height, strip size must be specified by the user. */

    HW_SET_FIELD32(size, SC_CFG_8_NLIN_LEFT, config->stripSize);
    innerWidth = advCfg->tarWidth - (UInt32) (config->stripSize << 1U);
    HW_SET_FIELD32(
        size,
        SC_CFG_8_NLIN_RIGHT,
        ((config->stripSize + innerWidth) - 1U));

    return (size);
}

/**
 *  static inline UInt32 VpsHal_scMakeScCfg24Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get the Source image size in
 *          32 bit value. Value returned from this function can be directly
 *          set into the register.
 *
 *  \param  config      pointers to structure containing source
 *
 *  \return             source image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg24Reg(const Vps_ScAdvConfig *advCfg)
{
    UInt32 size = 0;

    GT_assert(VpsHalTrace, (NULL != advCfg));

    HW_SET_FIELD32(size, (UInt32) SC_CFG_24_ORG_W, advCfg->srcWidth);
    HW_SET_FIELD32(size, (UInt32) SC_CFG_24_ORG_H, advCfg->srcHeight);

    return (size);
}

/**
 *  static inline UInt32 VpsHal_scMakeScCfg25Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get offset from where to crop
 *          image in 32 bit value. Value returned from this function can be
 *          directly set into the register.
 *
 *  \param  config     pointers to structure containing source
 *
 *  \return            offset in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg25Reg(const Vps_ScAdvConfig *advCfg)
{
    UInt32 size = 0;

    GT_assert(VpsHalTrace, (NULL != advCfg));

    HW_SET_FIELD32(size, (UInt32) SC_CFG_25_OFF_W, advCfg->cropStartX);
    HW_SET_FIELD32(size, (UInt32) SC_CFG_25_OFF_H, advCfg->cropStartY);

    return (size);
}

/**
 *  VpsHal_scLongDivide UInt32 hiValue, UInt32 loValue, UInt32 divider)
 *
 *  \brief Function is used to divide 64 bit value by 32 bit value. It is used
 *  in calculating linear as well as non-linear horizontal scaling parameters
 */
static UInt32 VpsHal_scLongDivide(UInt32 hiValue,
                                  UInt32 loValue,
                                  UInt32 divider)
{
    Int32  cnt;
    UInt32 temp;

    /* Optimization is required */
    for (cnt = 1; cnt <= 32; cnt++)
    {
        temp    = (UInt32) hiValue >> 31;
        hiValue = (hiValue << 1) | (loValue >> 31);
        loValue = loValue << 1;
        if ((hiValue | temp) >= divider)
        {
            hiValue = hiValue - divider;
            loValue = loValue + 0x1U;
        }
    }

    return loValue;
}

/**
 *  VpsHal_scGetStdHorzCoeffOvly
 *
 *  \brief  Function to return the horizontal scaling standard coefficients
 *          as per the scaling ratio.
 *          Register Overlay Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  horzCoeffMemPtr Location to return a pointer to horizontal scaling
 *                          coefficients
 *  \param  config          Scaler Parameters using which it calculates the
 *                          scaling ratio
 *
 *  \return 0               on Success
 *          -1              on Error
 */
static void VpsHal_scGetStdHorzCoeffOvly(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *
    horzCoeffMemPtr)
{
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != config));
    GT_assert(VpsHalTrace, (NULL != horzCoeffMemPtr));

    if (config->hScalingSet == VPS_SC_US_SET)
    {
        *horzCoeffMemPtr = gScHorzUpScaleCoeffMemPtr;
    }
    else if (config->hScalingSet == VPS_SC_SET_1_1)
    {
        *horzCoeffMemPtr = gScHorzOneToOneScaleCoeffMemPtr;
    }
    else if (config->hScalingSet == VPS_SC_SET_MAX)
    {
        /* No coeff mem is needed, set NULL */
        *horzCoeffMemPtr = NULL;
    }
    else
    {
        GT_assert(VpsHalTrace,
                  ((config->hScalingSet - VPS_SC_DS_SET_4_16) < 12));
        *horzCoeffMemPtr = gScHorzDownScaleCoeffMemPtr +
                           ((config->hScalingSet - VPS_SC_DS_SET_4_16) *
                            VPSHAL_SC_HORZ_COEFF_OVLY_SIZE);
    }

    return;
}

/**
 *  VpsHal_scGetStdVertCoeffOvly
 *
 *  \brief  Function to return the vertical scaling standard coefficients as per
 *          the scaling ratio.
 *          Register Overlay Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  vertCoeffMemPtr Location to return a pointer to vertical scaling
 *                          coefficients
 *  \param  vertBilinearCoeffMemPtr Location to return a pointer to vertical
 *                          bilinear scaling coefficients (only if applicable,
 *                          i.e. for HQ scaler. Can be NULL otherwise).
 *  \param  config          Scaler Parameters using which it calculates the
 *                          scaling ratio
 *
 *  \return 0               on Success
 *          -1              on Error
 */
static void VpsHal_scGetStdVertCoeffOvly(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *vertCoeffMemPtr,
    Ptr                         *vertBilinearCoeffMemPtr)
{
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != config));
    GT_assert(VpsHalTrace, (NULL != vertCoeffMemPtr));
    GT_assert(VpsHalTrace, (NULL != vertBilinearCoeffMemPtr));

    if (config->vScalingSet == VPS_SC_US_SET)
    {
        *vertCoeffMemPtr = gScVertUpScaleCoeffMemPtr;
    }
    else if (config->vScalingSet == VPS_SC_SET_1_1)
    {
        *vertCoeffMemPtr = gScVertOneToOneScaleCoeffMemPtr;
    }
    else if (config->vScalingSet == VPS_SC_SET_MAX)
    {
        /* No coeff mem is needed, set NULL */
        *vertCoeffMemPtr = NULL;
    }
    else
    {
        GT_assert(VpsHalTrace,
                  ((config->vScalingSet - VPS_SC_DS_SET_3_16) < 13));
        *vertCoeffMemPtr = gScVertDownScaleCoeffMemPtr +
                           ((config->vScalingSet - VPS_SC_DS_SET_3_16) *
                            VPSHAL_SC_VERT_COEFF_OVLY_SIZE);
    }

    if (TRUE == (((VpsHal_ScInfo *) handle)->isHqScaler))
    {
        *vertBilinearCoeffMemPtr = gScVertBilinearCoeffMemPtr;
    }
    else
    {
        /* Return NULL for non-HQ Scaler */
        *vertBilinearCoeffMemPtr = NULL;
    }

    return;
}

