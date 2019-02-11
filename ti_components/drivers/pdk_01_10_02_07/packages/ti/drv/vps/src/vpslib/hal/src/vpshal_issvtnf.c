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
 *  \file isshal_vtnf.c
 *
 *  \brief File containing the ISS VTNF HAL init, deinit and other common
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
#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issvtnf.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief YUV40 NV12/21 width alignment
 */
#define VTNF_BLK_WTH_ALIGN_NV               (16U)

/**
 *  \brief YUV40 Planar width alignment
 */
#define VTNF_BLK_WTH_ALIGN_YV21             (32U)

/**
 *  \brief YUV40 Planar width alignment
 */
#define VTNF_BLK_HGT_ALIGN                  (4U)

/**
 *  \brief Max block height supported
 */
#define VTNF_BLK_MAX_HEIGHT                 (128U)

/**
 *  \brief Max block width supported
 */
#define VTNF_BLK_MAX_WIDTH                  (512U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalvtnfInstObj
{
    uint32_t               instId;
    /**< Id of the instance */
    uint32_t               baseAddress;
    /**< Register base address */
    uint32_t               openCnt;
    /**< Open count */
    vpsissvtnfTriggerSrc_t triggerSource;
    /**< Trigger source */
} isshalvtnfInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Demonstrates how to define an internal function without Doxygen
 *          tags.
 *
 * \param   obj           Pointer to the local structure object.
 *
 * \return  S_PASS on success else error code.
 *
 **/
static uint32_t VtnfMakeLutReg(uint32_t l0, uint32_t l1, uint32_t l2,
                               uint32_t l3);

static inline uint32_t VtnfLut1GetMask(uint32_t n);
static inline uint32_t VtnfLut1GetShift(uint32_t n);
static inline uint32_t VtnfLut2GetMask(uint32_t n);
static inline uint32_t VtnfLut2GetShift(uint32_t n);

static inline uint32_t VtnfLut1GetMask(uint32_t n)
{
    return ((uint32_t)0x000000FFU << ((n) * (uint32_t)0x00000008U));
}

static inline uint32_t VtnfLut1GetShift(uint32_t n)
{
    return ((n) * 0x00000008U);
}

static inline uint32_t VtnfLut2GetMask(uint32_t n)
{
    return ((uint32_t)0x000000FFU << ((n) * (uint32_t)0x00000008U));
}

static inline uint32_t VtnfLut2GetShift(uint32_t n)
{
    return ((n) * 0x00000008U);
}

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalvtnfInstObj_t gIssHalVtnfInstObjs[ISSHAL_VTNF_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_issvtnfInit
 *  \brief VTNF init function.
 *
 *  Initializes VTNF objects.
 *  This function should be called before calling any of VTNF HAL API's.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #isshalvtnfInstParams_t.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
int32_t VpsHal_issvtnfInit(UInt32                        numInst,
                           const isshalvtnfInstParams_t *instPrms,
                           Ptr                           arg)
{
    uint32_t instCnt;
    isshalvtnfInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_VTNF_MAX_INST));
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
         * vtnf number of instances. The size of this number of instances
         * is never more than ISSHAL_VTNF_INST_MAX_ID.
         */
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].instId < ISSHAL_VTNF_INST_MAX_ID));

        pInstObj = &gIssHalVtnfInstObjs[instCnt];

        pInstObj->openCnt     = 0U;
        pInstObj->instId      = instPrms[instCnt].instId;
        pInstObj->baseAddress = instPrms[instCnt].baseAddress;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_issvtnfDeInit
 *  \brief VTNF HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
int32_t VpsHal_issvtnfDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalvtnfInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_VTNF_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIssHalVtnfInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == pInstObj->openCnt));

        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
    }

    return (FVID2_SOK);
}

/**
 *  VpsHal_issvtnfOpen
 *  \brief This function should be called prior to calling any of the VTNF HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param openPrms       Open Parameters
 */
VpsHal_Handle VpsHal_issvtnfOpen(const isshalvtnfOpenParams_t *openPrms)
{
    uint32_t             instCnt;
    uint32_t             regVal;
    VpsHal_Handle        handle   = NULL;
    isshalvtnfInstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_VTNF_MAX_INST; instCnt++)
    {
        pInstObj = &(gIssHalVtnfInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) (pInstObj);

            /* Check whether some one has already opened this instance */
            if(0 == pInstObj->openCnt)
            {
                /* Set the clock to be free running
                 * TODO: Change it according to power requirement */
                regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_CTRL);
                regVal = regVal & ~((UInt32) VTNF_CTRL_AUTOGATING_MASK);
                HW_WR_REG32(pInstObj->baseAddress + VTNF_CTRL, regVal);
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_issvtnfClose
 *  \brief This functions closes the vtnf handle and after call to this
 *  function, vtnf handle is not valid.
 *
 *  \param handle         Requested VTNF instance
 */
int32_t VpsHal_issvtnfClose(VpsHal_Handle handle)
{
    int32_t status = FVID2_EFAIL;
    isshalvtnfInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalvtnfInstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;
        status = FVID2_SOK;
    }

    return (status);
}

/**
 *  \brief Sets the entire VTNF configuration to the VTNF registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issvtnfConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param arg              Not used, should be NULL
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfSetConfig(VpsHal_Handle             handle,
                                const vpsissvtnfConfig_t *config,
                                Ptr                       arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    uint32_t lutCnt;
    isshalvtnfInstObj_t         *pInstObj = NULL;
    const vpsissvtnfAdvConfig_t *advCfg;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != config));
    advCfg = &(config->advCfg);

    pInstObj = (isshalvtnfInstObj_t *) handle;

    if((config->outDataFormat != FVID2_DF_YUV420SP_UV) &&
       (config->outDataFormat != FVID2_DF_YUV420SP_VU) &&
       (config->outDataFormat != FVID2_DF_YUV420P))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(config->outDataFormat != FVID2_DF_YUV420P)
    {
        if((advCfg->blockWidth % VTNF_BLK_WTH_ALIGN_YV21) != 0U)
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }
    else /* YUV420 Format */
    {
        if((advCfg->blockWidth % VTNF_BLK_WTH_ALIGN_NV) != 0U)
        {
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if((advCfg->blockWidth % VTNF_BLK_HGT_ALIGN) != 0U)
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if((VTNF_BLK_MAX_WIDTH < advCfg->blockWidth) ||
       (VTNF_BLK_MAX_HEIGHT < advCfg->blockHeight))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        /* Set the configuration of trigger source and interrupt enable
         * in ctrl register */
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_CTRL);

        regVal = regVal & ~((UInt32) VTNF_CTRL_TRIG_SRC_MASK);
        regVal =
            (advCfg->triggerSource <<
             VTNF_CTRL_TRIG_SRC_SHIFT) & VTNF_CTRL_TRIG_SRC_MASK;

        regVal  = regVal & ~((UInt32) VTNF_CTRL_INTEN_MASK);
        regVal |=
            (advCfg->intrEnable <<
             VTNF_CTRL_INTEN_SHIFT) & VTNF_CTRL_INTEN_MASK;

        HW_WR_REG32(pInstObj->baseAddress + VTNF_CTRL, regVal);

        /* Set outDataFormat and round down bit size in the fmg register */
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_CFG);

        regVal = regVal & ~((UInt32) VTNF_CFG_FMT_MASK);
        if(config->outDataFormat == FVID2_DF_YUV420P)
        {
            regVal = regVal | VTNF_CFG_FMT_MASK;
        }

        regVal  = regVal & ~((UInt32) VTNF_CFG_T_MASK);
        regVal |= (advCfg->roundBitCount << VTNF_CFG_T_SHIFT) & VTNF_CFG_T_MASK;

        HW_WR_REG32(pInstObj->baseAddress + VTNF_CFG, regVal);

        /* Set the block size */
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_SZ);

        regVal  = regVal & ~((UInt32) VTNF_SZ_BLKW_MASK);
        regVal |=
            (advCfg->blockWidth << VTNF_SZ_BLKW_SHIFT) & VTNF_SZ_BLKW_MASK;

        regVal  = regVal & ~VTNF_SZ_BLKH_MASK;
        regVal |=
            (advCfg->blockHeight << VTNF_SZ_BLKH_SHIFT) & VTNF_SZ_BLKH_MASK;

        HW_WR_REG32(pInstObj->baseAddress + VTNF_SZ, regVal);

        /* Set the Weights */
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_WEIGHTS);

        regVal  = regVal & ~((UInt32) VTNF_WEIGHTS_W1_MASK);
        regVal |=
            (advCfg->colorWeight1 <<
             VTNF_WEIGHTS_W1_SHIFT) & VTNF_WEIGHTS_W1_MASK;

        regVal  = regVal & ~VTNF_WEIGHTS_W2_MASK;
        regVal |=
            (advCfg->colorWeight2 <<
             VTNF_WEIGHTS_W2_SHIFT) & VTNF_WEIGHTS_W2_MASK;

        HW_WR_REG32(pInstObj->baseAddress + VTNF_WEIGHTS, regVal);

        /* Configure the LUT0 in the registers */
        for(lutCnt = 0U; lutCnt < VPS_ISS_VTNF_LUT_SIZE; lutCnt += 4U)
        {
            regVal = VtnfMakeLutReg(advCfg->lut1[lutCnt],
                                    advCfg->lut1[lutCnt + 1U],
                                    advCfg->lut1[lutCnt + 2U],
                                    advCfg->lut1[lutCnt + 3U]);

            HW_WR_REG32(pInstObj->baseAddress + VTNF_LUT1_0 + lutCnt, regVal);
        }

        /* Configure the LUT0 in the registers */
        for(lutCnt = 0U; lutCnt < VPS_ISS_VTNF_LUT_SIZE; lutCnt += 4U)
        {
            regVal = VtnfMakeLutReg(advCfg->lut2[lutCnt],
                                    advCfg->lut2[lutCnt + 1U],
                                    advCfg->lut2[lutCnt + 2U],
                                    advCfg->lut2[lutCnt + 3U]);

            HW_WR_REG32(pInstObj->baseAddress + VTNF_LUT2_0 + lutCnt, regVal);
        }
        pInstObj->triggerSource = advCfg->triggerSource;
    }

    return (status);
}

/**
 *  VpsHal_issvtnfGetConfig
 *  \brief Gets the entire VTNF configuration from the registers.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_issvtnfConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfGetConfig(VpsHal_Handle       handle,
                                vpsissvtnfConfig_t *config)
{
    uint32_t regVal;
    uint32_t lutCnt;
    isshalvtnfInstObj_t   *pInstObj = NULL;
    vpsissvtnfAdvConfig_t *advCfg;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != config));
    advCfg = &(config->advCfg);

    pInstObj = (isshalvtnfInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_CTRL);

    if(((regVal & VTNF_CTRL_TRIG_SRC_MASK) >> VTNF_CTRL_TRIG_SRC_SHIFT) == 1u)
    {
        advCfg->triggerSource = ISSHAL_VTNF_TRG_SRC_HWSEQ;
    }
    else
    {
        advCfg->triggerSource = ISSHAL_VTNF_TRG_SRC_REG;
    }
    advCfg->intrEnable =
        (regVal & VTNF_CTRL_INTEN_MASK) >> VTNF_CTRL_TRIG_SRC_SHIFT;

    regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_CFG);

    if((VTNF_CFG_FMT_MASK & regVal) == 1U)
    {
        config->outDataFormat = FVID2_DF_YUV420P;
    }
    else
    {
        config->outDataFormat = FVID2_DF_YUV420SP_UV;
    }

    advCfg->roundBitCount = (regVal & VTNF_CFG_T_MASK) >> VTNF_CFG_T_SHIFT;

    regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_SZ);
    advCfg->blockWidth  = (regVal & VTNF_SZ_BLKW_MASK) >> VTNF_SZ_BLKW_SHIFT;
    advCfg->blockHeight = (regVal & VTNF_SZ_BLKH_MASK) >> VTNF_SZ_BLKH_SHIFT;

    regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_WEIGHTS);
    advCfg->colorWeight1 =
        (regVal & VTNF_WEIGHTS_W1_MASK) >> VTNF_WEIGHTS_W1_SHIFT;
    advCfg->colorWeight2 =
        (regVal & VTNF_WEIGHTS_W2_MASK) >> VTNF_WEIGHTS_W2_SHIFT;

    for(lutCnt = 0U; lutCnt < VPS_ISS_VTNF_LUT_SIZE; lutCnt += 4U)
    {
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_LUT1_0 + lutCnt);

        advCfg->lut1[lutCnt] =
            (regVal & VtnfLut1GetMask(0x00000000U)) >>
            VtnfLut1GetShift(0x00000000U);
        advCfg->lut1[lutCnt + 1U] =
            (regVal & VtnfLut1GetMask(1U)) >> VtnfLut1GetShift(1U);
        advCfg->lut1[lutCnt + 2U] =
            (regVal & VtnfLut1GetMask(2U)) >> VtnfLut1GetShift(2U);
        advCfg->lut1[lutCnt + 3U] =
            (regVal & VtnfLut1GetMask(3U)) >> VtnfLut1GetShift(3U);
    }
    for(lutCnt = 0U; lutCnt < VPS_ISS_VTNF_LUT_SIZE; lutCnt += 4U)
    {
        regVal = HW_RD_REG32(pInstObj->baseAddress + VTNF_LUT2_0 + lutCnt);

        advCfg->lut2[lutCnt] =
            (regVal & VtnfLut2GetMask(0U)) >> VtnfLut2GetShift(0U);
        advCfg->lut2[lutCnt + 1U] =
            (regVal & VtnfLut2GetMask(1U)) >> VtnfLut2GetShift(1U);
        advCfg->lut2[lutCnt + 2U] =
            (regVal & VtnfLut2GetMask(2U)) >> VtnfLut2GetShift(2U);
        advCfg->lut2[lutCnt + 3U] =
            (regVal & VtnfLut2GetMask(3U)) >> VtnfLut2GetShift(3U);
    }

    return (FVID2_SOK);
}

/**
 *  VpsHal_issvtnfControl
 *  \brief VTNF specific control commands.
 *
 *  \param handle           Instance handle
 *  \param cmd              Control Command
 *  \param cmdArgs          Arguments for the control command, could be null
 *                          depends on the control command
 *  \param arg              not used. should be null
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfControl(VpsHal_Handle handle,
                              UInt32        cmd,
                              Ptr           cmdArgs,
                              Ptr           arg)
{
    return (FVID2_SOK);
}

/**
 *  VpsHal_issvtnfSetAddress
 *  \brief VTNF Api for setting input and output address.
 *
 *  \param handle           Instance handle
 *  \param inAddr           Current Input Frame address, must be 16byte aligned
 *  \param prevInAddr       Previous Input Frame address, must be 16byte aligned
 *  \param outAddr          Current Output Frame address, must be 16byte aligned
 *  \param lineOffset       Line Offset/pitch for input and output buffers
 *                          must be even
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfSetAddress(VpsHal_Handle handle,
                                 Ptr           inAddr,
                                 Ptr           prevInAddr,
                                 Ptr           outAddr,
                                 uint32_t      lineOffset)
{
    isshalvtnfInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    /* TBD Fix check below                              */
    /* GT_assert(VpsHalTrace, (NULL != inAddr));        */
    /* GT_assert(VpsHalTrace, (NULL != prevInAddr));    */
    /* GT_assert(VpsHalTrace, (NULL != outAddr));       */

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address type casted for error checking
     */
    /* Check for alignment requirement */
    GT_assert(VpsHalTrace,
              (0U == ((uint32_t) inAddr & ~((UInt32) VTNF_CADR_ADDR_MASK))));
    GT_assert(VpsHalTrace,
              (0U == ((uint32_t) prevInAddr & ~((UInt32) VTNF_PADR_ADDR_MASK))));
    GT_assert(VpsHalTrace,
              (0U == ((uint32_t) outAddr & ~((UInt32) VTNF_OADR_ADDR_MASK))));
    GT_assert(VpsHalTrace,
              (0U == (lineOffset & ~((UInt32) VTNF_LOFST_MASK))));

    pInstObj = (isshalvtnfInstObj_t *) handle;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Pointer containing frame buffer address used for setting memory
     * mapped register
     */
    /* TODO check for the address alignment requirement */
    HW_WR_REG32(pInstObj->baseAddress + VTNF_LOFST,
                (lineOffset & VTNF_LOFST_MASK));
    HW_WR_REG32(pInstObj->baseAddress + VTNF_OADR,
                ((uint32_t) outAddr & VTNF_OADR_ADDR_MASK));
    HW_WR_REG32(pInstObj->baseAddress + VTNF_PADR,
                ((uint32_t) prevInAddr & VTNF_PADR_ADDR_MASK));
    HW_WR_REG32(pInstObj->baseAddress + VTNF_CADR,
                ((uint32_t) inAddr & VTNF_CADR_ADDR_MASK));

    return (FVID2_SOK);
}

/**
 *  VpsHal_issvtnfSetAddress
 *  \brief VTNF Api for enabling the module. Used only when Trigger Source
 *         is set to 0, otherwise HwSeq takes care of starting the module.
 *         It will get reset when it finishes processing for a block.
 *
 *  \param handle           Instance handle
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issvtnfStart(VpsHal_Handle handle)
{
    isshalvtnfInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalvtnfInstObj_t *) handle;

    if(ISSHAL_VTNF_TRG_SRC_HWSEQ != pInstObj->triggerSource)
    {
        HW_WR_REG32(pInstObj->baseAddress + VTNF_CTRL,
                    HW_RD_REG32(pInstObj->baseAddress + VTNF_CTRL) |
                    VTNF_CTRL_EN_MASK);
    }

    return (FVID2_SOK);
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
static uint32_t VtnfMakeLutReg(uint32_t l0, uint32_t l1, uint32_t l2,
                               uint32_t l3)
{
    uint32_t regVal = 0U;

    regVal |= (l0 << VtnfLut1GetShift(0U)) & VtnfLut1GetMask(0U);
    regVal |= (l1 << VtnfLut1GetShift(1U)) & VtnfLut1GetMask(1U);
    regVal |= (l2 << VtnfLut1GetShift(2U)) & VtnfLut1GetMask(2U);
    regVal |= (l3 << VtnfLut1GetShift(3U)) & VtnfLut1GetMask(3U);

    return (regVal);
}

