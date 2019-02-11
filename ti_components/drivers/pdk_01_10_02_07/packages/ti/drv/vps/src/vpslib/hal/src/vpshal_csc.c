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
 *  \file vpshal_csc.c
 *
 *  \brief HAL implementation for CSC module instances.
 *  This file implements the HAL APIs of the CSC modules.
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
#include <ti/csl/cslr_csc.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_csc.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshal_cscDefaults.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum Csc_ConfigOvlyReg
 *
 *  \brief Enums for the configuration overlay register offsets - used as array
 *  indices to register offset array in Csc_Obj object. These enums defines the
 *  registers that will be used to form the configuration register overlay for
 *  CSC module. This in turn is used by client drivers to configure registers
 *  using VPDMA during context-switching (software channels with different
 *  configurations).
 *
 *  Note: If in future it is decided to remove or add some register, this enum
 *  should be modified accordingly. And make sure that the values of these
 *  enums are in ascending order and it starts from 0.
 */
typedef enum
{
    CSC_CONFIG_OVLY_CSC_00_IDX = 0,
    CSC_CONFIG_OVLY_CSC_01_IDX,
    CSC_CONFIG_OVLY_CSC_02_IDX,
    CSC_CONFIG_OVLY_CSC_03_IDX,
    CSC_CONFIG_OVLY_CSC_04_IDX,
    CSC_CONFIG_OVLY_CSC_05_IDX,
    CSC_CONFIG_OVLY_NUM_IDX
    /**< This should be the last enum */
} Csc_ConfigOvlyReg;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_CscInfo
 *  \brief Structure containing Instance Information for each CSC Instance.
 *         Primarily baseAddress and overlay info for the CSC instance.
 */
typedef struct
{
    UInt32  halId;
    /**< Indicates the path on which CSC is available. */
    UInt32  openCnt;
    /**< Keeps track of number of open for a CSC instance. */
    UInt32  baseAddr;
    /**< Base address of CSC module for current instance. */
    UInt32  regOvlySize;
    /**< Virtual register overlay size in terms of bytes. Used to allocate
     *   memory for virtual register configured through VPDMA. */
    UInt32 *regOffset[(UInt32)CSC_CONFIG_OVLY_NUM_IDX];
    /**< Array of physical address of the register configured through VPDMA
     *   register overlay. */
    UInt32  virtRegOffset[(UInt32)CSC_CONFIG_OVLY_NUM_IDX];
    /**< Array of indexes into the Overlay memory where virtual registers are
     *   to be configured */
} VpsHal_CscInfo;

/**
 *  struct VpsHal_CscObj
 *  \brief Handle structure for all instances of CSC HAL
 */
typedef struct
{
    UInt32         numInst;
    /**< Num instances opened in HAL Init. */
    VpsHal_CscInfo cscInfo[VPSHAL_CSC_MAX_INST];
    /**< Instance list for maximum supported instances. */
} VpsHal_CscObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * VpsHal_cscMakeReg0123
 * \brief Make the register of CSC for the coefficients which has same masks
 * and offsets. (Registers CSC_00 to CSC_03)
 */
static inline UInt32 VpsHal_cscMakeReg0123(UInt16 coeff1,
                                           UInt16 coeff2);

/**
 * VpsHal_cscMakeReg4
 * \brief Make the register CSC_04
 */
static inline UInt32 VpsHal_cscMakeReg4(UInt16 coeff1,
                                        UInt16 coeff2);

/**
 * VpsHal_cscMakeReg5
 * \brief Make the register CSC_05
 */
static inline UInt32 VpsHal_cscMakeReg5(UInt16 coeff1,
                                        UInt16 coeff2);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief CSC HAL object containing all CSC instances. */
static VpsHal_CscObj gCscHalObj;

/** \brief Default Value of Color Space Conversion coefficients. */
static Vps_CscCoeff  gCscDefaultCoeff[VPS_CSC_MODE_MAX] =
    VPSHAL_CSC_DEFAULT_EXPERT_VAL;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_cscInit
 *  \brief CSC HAL init function.
 *
 *  Initializes CSC objects, gets the register overlay offsets for CSC
 *  registers.
 *  This function should be called before calling any of CSC HAL API's.
 *  VPDMA HAL should be initialized prior to calling any of CSC HAL
 *  functions.
 *  All global variables are initialized.
 *
 *  \param numInst       Number of instances to initialize.
 *  \param instPrms      Pointer to #VpsHal_CscInstParams.
 *  \param arg           Not used currently. Meant for future purpose.
 *
 *  \return              Returns 0 on success else returns error value.
 *
 */
Int32 VpsHal_cscInit(UInt32                      numInst,
                     const VpsHal_CscInstParams *instPrms,
                     Ptr                         arg)
{
    UInt32          instCnt;
    VpsHal_CscInfo *instObj;
    UInt32          baseAddr;
    UInt32          regOffsetValue;

    /* Check for errors */
    GT_assert(VpsHalTrace, numInst <= VPSHAL_CSC_MAX_INST);
    GT_assert(VpsHalTrace, NULL != instPrms);

    gCscHalObj.numInst = numInst;

    for (instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  instPrms[instCnt].halId < VPSHAL_CSC_INST_ID_MAX);

        /* Initialize Instance Specific Parameters */
        instObj           = &gCscHalObj.cscInfo[instCnt];
        instObj->openCnt  = 0;
        instObj->halId    = instPrms[instCnt].halId;
        instObj->baseAddr = instPrms[instCnt].baseAddr;

        /* Calculate VPDMA register overlay size and register offset in
         * the VPDMA register overlay. Since register organization for all
         * CSC are same, only one array of register offset is sufficient. */
        /* Since the register offset are same for all CSC instances, using HQ
         * CSC to get physical offset. */
        baseAddr       = instObj->baseAddr;
        regOffsetValue = baseAddr + CSC_00;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_00_IDX] =
            (UInt32 *) regOffsetValue;
        regOffsetValue = baseAddr + CSC_01;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_01_IDX] =
            (UInt32 *) regOffsetValue;
        regOffsetValue = baseAddr + CSC_02;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_02_IDX] =
            (UInt32 *) regOffsetValue;
        regOffsetValue = baseAddr + CSC_03;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_03_IDX] =
            (UInt32 *) regOffsetValue;
        regOffsetValue = baseAddr + CSC_04;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_04_IDX] =
            (UInt32 *) regOffsetValue;
        regOffsetValue = baseAddr + CSC_05;
        instObj->regOffset[CSC_CONFIG_OVLY_CSC_05_IDX] =
            (UInt32 *) regOffsetValue;

        instObj->regOvlySize =
            VpsHal_vpdmaCalcRegOvlyMemSize(
                instObj->regOffset,
                CSC_CONFIG_OVLY_NUM_IDX,
                instObj->virtRegOffset);
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_cscDeInit
 *  \brief CSC HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_cscDeInit(Ptr arg)
{
    UInt32 instCnt;

    for (instCnt = 0; instCnt < VPSHAL_CSC_MAX_INST; instCnt++)
    {
        gCscHalObj.cscInfo[instCnt].halId    = 0;
        gCscHalObj.cscInfo[instCnt].openCnt  = 0;
        gCscHalObj.cscInfo[instCnt].baseAddr = 0;
    }
    gCscHalObj.numInst = 0;

    return (BSP_SOK);
}

/**
 *  VpsHal_cscOpen
 *  \brief Returns the handle to the requested CSC instance.
 *
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the CSC HAL
 *  configuration APIs.
 *
 *  VpsHal_cscInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms     VpsHal_CscOpenParams
 *
 *  \return             success     CSC instance's HAL handle
 *                      failure     NULL
 */
VpsHal_Handle VpsHal_cscOpen(const VpsHal_CscOpenParams *openPrms)
{
    UInt32          instCnt;
    VpsHal_Handle   cscHandle = NULL;
    VpsHal_CscInfo *instObj   = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, NULL != openPrms);

    for (instCnt = 0U; instCnt < gCscHalObj.numInst; instCnt++)
    {
        instObj = &gCscHalObj.cscInfo[instCnt];
        /* Return the matching instance handle */
        if (openPrms->halId == instObj->halId)
        {
            if (0 == instObj->openCnt)
            {
                instObj->openCnt++;
                cscHandle = (VpsHal_Handle) instObj;
                break;
            }
        }
    }

    return (cscHandle);
}

/**
 *  VpsHal_cscClose
 *  \brief Closes specified instance of CSC HAL
 *  VpsHal_cscInit and cscOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_cscOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_cscClose(VpsHal_Handle handle)
{
    Int32           retVal = BSP_EFAIL;
    VpsHal_CscInfo *instObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    instObj = (VpsHal_CscInfo *) handle;

    /* Decrement the open count */
    if (instObj->openCnt > 0)
    {
        instObj->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsHal_cscGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA
 *  register configuration overlay required to program the CSC registers using
 *  VPDMA config descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the CSC registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context (multiple
 *  instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay one-time
 *  and submit this to VPDMA everytime when context changes. Thus saving
 *  valuable CPU in programming the VPS registers.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *
 *  \param handle Valid handle returned by VpsHal_cscOpen function.
 *
 *  \return       Returns 0 on success else returns error value.
 */
UInt32 VpsHal_cscGetConfigOvlySize(VpsHal_Handle handle)
{
    UInt32 regOvlySize = 0;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    /* Return the value already got in init function */
    regOvlySize = ((VpsHal_CscInfo *) handle)->regOvlySize;

    return (regOvlySize);
}

/**
 *  VpsHal_cscCreateConfigOvly
 *  \brief Creates the CSC register configuration
 *  overlay using VPDMA helper function.
 *
 *  This function does not initialize the overlay with CSC configuration. It is
 *  the responsibility of the client driver to configure the overlay by calling
 *  VpsHal_cscSetConfig function before submitting the same to VPDMA for
 *  register configuration at runtime.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *
 *  \param handle         Valid handle returned by VpsHal_cscOpen function.
 *
 *  \param configOvlyPtr  Pointer to the overlay memory where the overlay is
 *                        formed. The memory for the overlay should be allocated
 *                        by client driver. This parameter should be non-NULL.
 *
 *  \return               Returns 0 on success else returns error value.
 */
Int32 VpsHal_cscCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    Int32 retVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != configOvlyPtr);

    /* Create the register overlay */
    retVal = VpsHal_vpdmaCreateRegOverlay(
        ((VpsHal_CscInfo *) handle)->regOffset,
        CSC_CONFIG_OVLY_NUM_IDX,
        configOvlyPtr);

    return (retVal);
}

/**
 *  VpsHal_cscSetConfig
 *  \brief Sets the CSC configuration to either the
 *  actual CSC registers or to the configuration overlay memory.
 *
 *  This function configures the CSC registers. Depending on the value
 *  of ovlyPtr parameter, the updating will happen to actual CSC MMR or
 *  to configuration overlay memory.
 *  This function configures all the sub-modules in CSC using other config
 *  function call.
 *  VpsHal_cscInit and VpsHal_cscOpen should be called prior to this.
 *  CSC registers or configuration overlay memory are programmed
 *  according to the parameters passed.
 *
 *  \param handle          Valid handle returned by VpsHal_cscOpen function.
 *
 *  \param config          Pointer to Vps_CscConfig structure containing the
 *                         register configurations. This parameter should be
 *                         non-NULL.
 *
 *  \param configOvlyPtr   Pointer to the configuration overlay memory.
 *                         If this parameter is NULL, then the configuration is
 *                         written to the actual CSC registers. Otherwise the
 *                         configuration is updated in the memory pointed
 *                         by the same at proper virtual offsets. This parameter
 *                         can be NULL depending on the intended usage.
 *
 *  \return                Returns 0 on success else returns error value.
 */
Int32 VpsHal_cscSetConfig(VpsHal_Handle        handle,
                          const Vps_CscConfig *config,
                          Ptr                  configOvlyPtr)
{
    Int32           retVal = BSP_SOK;
    UInt32          tempReg;
    Vps_CscCoeff   *coeff   = NULL;
    VpsHal_CscInfo *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    /* Get the register Overlay pointer */
    instObj = (VpsHal_CscInfo *) handle;

    /* Get the coefficient pointer either from config or from default coeff */
    if (VPS_CSC_MODE_NONE != config->mode)
    {
        coeff = &gCscDefaultCoeff[(UInt32) config->mode];
    }
    else
    {
        coeff = config->coeff;
    }

    /* Configure CSC if it is not in bypass mode */
    if (FALSE == config->bypass)
    {
        /* Check whether parameters are valid */
        GT_assert(VpsHalTrace,
                  (((NULL != config->coeff) &&
                    (VPS_CSC_MODE_NONE == config->mode)) ||
                   ((NULL == config->coeff) &&
                    (VPS_CSC_MODE_NONE != config->mode))));

        if (NULL == configOvlyPtr)
        {
            /* Set the coefficients in the actual register */
            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[0][0],
                (UInt16) coeff->mulCoeff[0][1]);
            HW_WR_REG32((instObj->baseAddr + CSC_00), tempReg);

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[0][2],
                (UInt16) coeff->mulCoeff[1][0]);
            HW_WR_REG32((instObj->baseAddr + CSC_01), tempReg);

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[1][1],
                (UInt16) coeff->mulCoeff[1][2]);
            HW_WR_REG32((instObj->baseAddr + CSC_02), tempReg);

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[2][0],
                (UInt16) coeff->mulCoeff[2][1]);
            HW_WR_REG32((instObj->baseAddr + CSC_03), tempReg);

            tempReg = VpsHal_cscMakeReg4(
                (UInt16) coeff->mulCoeff[2][2],
                (UInt16) coeff->addCoeff[0]);
            HW_WR_REG32((instObj->baseAddr + CSC_04), tempReg);

            tempReg = VpsHal_cscMakeReg5(
                (UInt16) coeff->addCoeff[1],
                (UInt16) coeff->addCoeff[2]);
            HW_WR_REG32((instObj->baseAddr + CSC_05), tempReg);
        }
        else
        {
            /* Set the coefficients in Virtual Register Overlay */
            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[0][0],
                (UInt16) coeff->mulCoeff[0][1]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_00_IDX]) = tempReg;

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[0][2],
                (UInt16) coeff->mulCoeff[1][0]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_01_IDX]) = tempReg;

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[1][1],
                (UInt16) coeff->mulCoeff[1][2]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_02_IDX]) = tempReg;

            tempReg = VpsHal_cscMakeReg0123(
                (UInt16) coeff->mulCoeff[2][0],
                (UInt16) coeff->mulCoeff[2][1]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_03_IDX]) = tempReg;

            tempReg = VpsHal_cscMakeReg4(
                (UInt16) coeff->mulCoeff[2][2],
                (UInt16) coeff->addCoeff[0]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_04_IDX]) = tempReg;

            tempReg = VpsHal_cscMakeReg5(
                (UInt16) coeff->addCoeff[1],
                (UInt16) coeff->addCoeff[2]);
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_05_IDX]) = tempReg;
        }
    }
    else
    {
        /* CSC is in bypass mode so enable bypass in CSC */
        if (NULL == configOvlyPtr)
        {
            HW_WR_REG32((instObj->baseAddr + CSC_05), CSC_05_BYPASS_MASK);
        }
        else
        {
            *((UInt32 *) configOvlyPtr +
              instObj->virtRegOffset[CSC_CONFIG_OVLY_CSC_05_IDX]) =
                CSC_05_BYPASS_MASK;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_cscMakeReg0123
 *  \brief Make the register of CSC for the coefficients which has same masks
 *  and offsets. (Registers CSC_00 to CSC_03).
 */
static inline UInt32 VpsHal_cscMakeReg0123(UInt16 coeff1,
                                           UInt16 coeff2)
{
    UInt32 tempReg = 0;

    /* Since all coefficients masks are same, onle masks for A0 and
     * B0 are used */
    HW_SET_FIELD32(tempReg, CSC_00_A0, (UInt32) coeff1);
    HW_SET_FIELD32(tempReg, CSC_00_B0, (UInt32) coeff2);

    return (tempReg);
}

/**
 *  VpsHal_cscMakeReg4
 *  \brief Make the register CSC_04.
 */
static inline UInt32 VpsHal_cscMakeReg4(UInt16 coeff1,
                                        UInt16 coeff2)
{
    UInt32 tempReg = 0;

    HW_SET_FIELD32(tempReg, CSC_04_C2, (UInt32) coeff1);
    HW_SET_FIELD32(tempReg, CSC_04_D0, (UInt32) coeff2);

    return (tempReg);
}

/**
 *  VpsHal_cscMakeReg5
 *  \brief Make the register CSC_05.
 */
static inline UInt32 VpsHal_cscMakeReg5(UInt16 coeff1,
                                        UInt16 coeff2)
{
    UInt32 tempReg = 0;

    HW_SET_FIELD32(tempReg, CSC_05_D1, (UInt32) coeff1);
    HW_SET_FIELD32(tempReg, CSC_05_D2, (UInt32) coeff2);

    return (tempReg);
}

