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
 * \file vpshal_chrus.c
 *
 * \brief VPS Chroma Up Sampler HAL Source file.
 * This file implements the HAL APIs of the VPS Chroma Up Sampler (420 -> 422).
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

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_chr_us.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_chrus.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshalChrusDefaults.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*!
 *  \brief Enums for the configuration overlay register offsets - used as array
 *  indices to register offset array. These enums defines the registers
 *  that will be used to form the configuration register overlay.
 *  This in turn is used by client drivers to configure registers using
 *  VPDMA during context-switching (software channels with different
 *  configurations).
 *
 *  Note: If in future it is decided to remove or add some register, this
 *  enum and the initial value of NUM_REG_IDX macro should be modified
 *  accordingly. And make sure that the values of these enums are in
 *  ascending order and it starts from 0.
 */
typedef enum
{
    CHRUS_CONFIGOVLYIDX_REG0 = 0,
    CHRUS_CONFIGOVLYIDX_REG1,
    CHRUS_CONFIGOVLYIDX_REG2,
    CHRUS_CONFIGOVLYIDX_REG3,
    CHRUS_CONFIGOVLYIDX_REG4,
    CHRUS_CONFIGOVLYIDX_REG5,
    CHRUS_CONFIGOVLYIDX_REG6,
    CHRUS_CONFIGOVLYIDX_REG7,
    CHRUS_CONFIGOVLYIDX_MAX
} Chrus_ConfigOvlyIdx;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing Instance Information for each CHRUS module
 *  parent -            Pointer to the main CHRUS info structure
 */
typedef struct
{
    UInt32  halId;
    /**< Indicates the path on which CHRUS is available */
    UInt32  openCnt;
    /**< Keeps track of number of open for a Chrus instance */
    UInt32  baseAddr;
    /**< Base address for the current instance */
    UInt32  configOvlySize;
    /**< Virtual register overlay size in terms of bytes. Used to allocate
     *   memory for virtual register configured through VPDMA */
    UInt32 *regOffset[CHRUS_CONFIGOVLYIDX_MAX];
    /**< Array of physical address of the register configured through
     *   VPDMA register overlay. */
    UInt32  virRegOffset[CHRUS_CONFIGOVLYIDX_MAX];
    /**< Array of indexes into the Overlay memory where virtual registers
     *   are to be configured */
} ChrusInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to make CHR_US register */
static inline UInt32 chrusMakeReg(UInt16 coeff1, UInt16 coeff2);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * VpsHal_ChrusCoeff
 */
static VpsHal_ChrusCoeff ChrusDefaultCoeff[2] = VPSHAL_CHRUS_DEFAULT_EXPERT_VAL;

/**
 * \brief CHRUS objects - Module variable to store information about each CHRUS
 * instance.
 */
static ChrusInfo         ChrusObj[VPSHAL_CHRUS_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_chrusInit
 *  \brief Initializes CHRUS objects, gets the register overlay offsets for
 *  CHRUS registers.
 *  This function should be called before calling any of CHRUS HAL API's.
 *
 *  \param numInst          Number of Noise Filter Instances and number of
 *                          array elements in the second argument
 *  \param instPrms         Instance Specific Parameters
 *  \param arg              Not used currently. Meant for future purpose.
 */
Int32 VpsHal_chrusInit(UInt32                        numInst,
                       const VpsHal_ChrusInstParams *instPrms,
                       Ptr                           arg)
{
    UInt32     instCnt;
    UInt32     baseAddr;
    Int32      ret      = 0;
    ChrusInfo *instInfo = NULL;
    UInt32     regCnt;
    UInt32     regOffsetValue;

    /* Check for errors */
    GT_assert(VpsHalTrace, numInst <= VPSHAL_CHRUS_MAX_INST);
    GT_assert(VpsHalTrace, NULL != instPrms);

    /* Set the default Values for non-changing parameters */
    for (instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  instPrms[instCnt].halId < VPSHAL_CHRUS_INST_ID_MAX);

        /* Initialize Instance Specific Parameters */
        instInfo           = &(ChrusObj[instCnt]);
        instInfo->openCnt  = 0U;
        instInfo->baseAddr = instPrms[instCnt].baseAddr;
        instInfo->halId    = instPrms[instCnt].halId;

        /* Calculate VPDMA register overlay size and register offset in
         * the VPDMA register overlay. Since register organization for all
         * CHRUS are same, only one array of register offset is sufficient. */
        /* Since the register offset are same for all CHRUS instances,
         * using one CHRUS to get physical offset. */
        baseAddr = instInfo->baseAddr;
        for (regCnt = 0U; regCnt < CHRUS_CONFIGOVLYIDX_MAX; regCnt++)
        {
            regOffsetValue = baseAddr + CHR_US_REG0 + (regCnt * 4U);
            instInfo->regOffset[regCnt] = (UInt32 *) regOffsetValue;
        }

        instInfo->configOvlySize = VpsHal_vpdmaCalcRegOvlyMemSize(
            instInfo->regOffset,
            CHRUS_CONFIGOVLYIDX_MAX,
            instInfo->virRegOffset);
    }

    return (ret);
}

/**
 *  VpsHal_chrusDeInit
 *  \brief Currently this function does not do anything.
 *
 *  \param arg       Not used currently. Meant for future purpose.
 */
Int32 VpsHal_chrusDeInit(Ptr arg)
{
    return (0);
}

/**
 *  VpsHal_chrusOpen
 *  \brief This function should be called prior to calling any of the CHRUS HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param chrusInst       Requested CHRUS instance
 */
VpsHal_Handle VpsHal_chrusOpen(const VpsHal_ChrusOpenParams *openPrms)
{
    UInt32        cnt;
    VpsHal_Handle handle   = NULL;
    ChrusInfo    *instInfo = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, NULL != openPrms);

    for (cnt = 0; cnt < VPSHAL_CHRUS_MAX_INST; cnt++)
    {
        instInfo = &(ChrusObj[cnt]);
        /* Return the matching instance handle */
        if (openPrms->halId == instInfo->halId)
        {
            /* Check whether some one has already opened this instance */
            if (0 == instInfo->openCnt)
            {
                handle = (VpsHal_Handle) instInfo;
                instInfo->openCnt++;
            }
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_chrusClose
 *  \brief This functions closes the chrus handle and after call to this
 *  function, chrus handle is not valid. It also decrements the reference
 *  counter.
 *
 *  \param handle       Requested CHRUS instance
 */
Int32 VpsHal_chrusClose(VpsHal_Handle handle)
{
    Int32      ret      = (-(int32_t)1);
    ChrusInfo *instInfo = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    instInfo = (ChrusInfo *) handle;

    /* Decrement the open count */
    if (instInfo->openCnt > 0)
    {
        instInfo->openCnt--;
        ret = 0;
    }

    return (ret);
}

/**
 *  VpsHal_chrusGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA register configuration
 *  overlay required to program the CHRUS registers using VPDMA config
 *  descriptors.
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the CHRUS registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context
 *  (multiple instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay
 *  one-time and submit this to VPDMA everytime when context changes.
 *  Thus saving valuable CPU in programming the VPS registers.
 *
 *  \param  handle       Instance handle
 *  \return              Returns the size of config overlay memory
 */
UInt32 VpsHal_chrusGetConfigOvlySize(VpsHal_Handle handle)
{
    UInt32 configOvlySize = 0;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    /* Return the value already got in init function */
    configOvlySize = ((ChrusInfo *) handle)->configOvlySize;

    return configOvlySize;
}

/**
 *  VpsHal_chrusCreateConfigOvly
 *  \brief Creates the CHRUS register configuration overlay using VPDMA
 *  helper function.
 *
 *  This function does not initialize the overlay with CHRUS configuration.
 *  It is the responsibility of the client driver to configure the overlay
 *  by calling HalChrus_setConfig function before submitting the same
 *  to VPDMA for register configuration at runtime.
 *
 *  \param handle           Instance handle
 *  \param configOvlyPtr    Pointer to the overlay memory where the
 *                          overlay is formed. The memory for the overlay
 *                          should be allocated by client driver.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    Int32 retVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != configOvlyPtr);

    /* Create the register overlay */
    retVal = VpsHal_vpdmaCreateRegOverlay(
        ((ChrusInfo *) handle)->regOffset,
        CHRUS_CONFIGOVLYIDX_MAX,
        configOvlyPtr);

    return (retVal);
}

/**
 *  \brief Sets the entire CHRUS configuration to either the actual CHRUS
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire CHRUS registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual CHRUS MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in CHRUS using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_chrusConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          CHRUS registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusSetConfig(VpsHal_Handle             handle,
                            const VpsHal_ChrusConfig *config,
                            Ptr                       configOvlyPtr)
{
    Int32  ret = 0;
    ChrusInfo         *chrusObj = NULL;
    UInt32 baseAddr;
    VpsHal_ChrusCoeff *coeff = NULL;
    UInt32 mode, tempReg, regCnt, index, coeffCnt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    chrusObj = (ChrusInfo *) handle;
    baseAddr = chrusObj->baseAddr;

    mode = 0U;
    if (FVID2_SF_INTERLACED == config->mode)
    {
        mode = 1U;
    }
    if (NULL == config->coeff)
    {
        coeff = &(ChrusDefaultCoeff[mode]);
    }
    else
    {
        coeff = config->coeff;
    }

    tempReg = 0U;
    HW_SET_FIELD32(tempReg, CHR_US_REG0_CFG_MODE, (UInt32) config->cfgMode);
    index = 0U;
    for (regCnt = 0; regCnt < CHRUS_CONFIGOVLYIDX_MAX; regCnt++)
    {
        /* Increment the coefficient counter if 4 coefficients
         * are stored */
        coeffCnt = regCnt >> 1U;

        if (index >= (VPSHAL_CHRUS_NUM_COEFFS - 1U))
        {
            index = 0U;
        }
        /* All register format are same so using same function to
         * make the register */
        tempReg |= chrusMakeReg(
            coeff->coeff[coeffCnt][index],
            coeff->coeff[coeffCnt][index + 1U]);
        if (NULL != configOvlyPtr)
        {
            *((UInt32 *) configOvlyPtr +
              chrusObj->virRegOffset[regCnt]) = tempReg;
        }
        else
        {
            HW_WR_REG32(baseAddr + CHR_US_REG0 + (regCnt * 4U), tempReg);
        }

        tempReg = 0U;
        /* One register stores 2 coefficients, so increment index
         * by 2 */
        index += 2U;
    }

    return (ret);
}

/**
 *  VpsHal_chrusGetConfig
 *  \brief Gets the entire CHRUS configuration from the actual CHRUS registers.
 *
 *  This function gets the entire CHRUS configuration. This function
 *  gets the configuration of all the sub-modules in CHRUS using other
 *  get configuration function calls.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_chrusConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_chrusGetConfig(VpsHal_Handle handle, VpsHal_ChrusConfig *config)
{
    UInt32     baseAddr;
    UInt32     regVal;
    UInt32     regCnt, coeffCnt, index;
    ChrusInfo *chrusObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    GT_assert(VpsHalTrace, NULL != config->coeff);

    /* Get the Register Overlay Pointer from the handle */
    chrusObj = (ChrusInfo *) handle;
    baseAddr = chrusObj->baseAddr;

    /* Get the Configuration Mode from the Register 0 */
    config->cfgMode = (VpsHal_ChrusCfgMode)
                      HW_RD_FIELD32(baseAddr + CHR_US_REG0,
                                    CHR_US_REG0_CFG_MODE);

    coeffCnt = index = 0;
    for (regCnt = 0; regCnt < CHRUS_CONFIGOVLYIDX_MAX; regCnt++)
    {
        /* Increment the coefficient counter if 4 coefficients
         * are stored */
        coeffCnt = regCnt >> 1U;

        if (index >= (VPSHAL_CHRUS_NUM_COEFFS - 1U))
        {
            index = 0U;
        }
        /* All register format are same so using same function to
         * make the register */
        regVal = HW_RD_REG32(baseAddr + CHR_US_REG0 + (regCnt * 4U));
        config->coeff->coeff[coeffCnt][index] =
            (UInt16) (regVal & CHR_US_REG0_ANCHOR_FID0_C0_MASK) >>
                      CHR_US_REG0_ANCHOR_FID0_C0_SHIFT;
        config->coeff->coeff[coeffCnt][index + 1U] =
            (UInt16) (regVal & CHR_US_REG0_ANCHOR_FID0_C1_MASK) >>
                      CHR_US_REG0_ANCHOR_FID0_C1_SHIFT;
        /* One register stores 2 coefficients, so increment index
         * by 2 */
        index += 2U;
    }

    return (0);
}

/**
 * chrusMakeReg
 * \brief Makes the CHRUS register given two coefficient to be stored in the
 * register and returns the register value.
 */
static inline UInt32 chrusMakeReg(UInt16 coeff1, UInt16 coeff2)
{
    UInt32 tempReg;

    /* All coefficients width and position are same so this function uses
     * macros from reg0 */
    tempReg =
        ((UInt32) coeff1 << CHR_US_REG0_ANCHOR_FID0_C0_SHIFT)
        & CHR_US_REG0_ANCHOR_FID0_C0_MASK;
    tempReg |=
        ((UInt32) coeff2 << CHR_US_REG0_ANCHOR_FID0_C1_SHIFT)
        & CHR_US_REG0_ANCHOR_FID0_C1_MASK;

    return (tempReg);
}

