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
 *  \file vpshal_dei.c
 *
 *  \brief VPS Deinterlacer HAL file.
 *  This file implements the HAL APIs of the VPS Deinterlacer.
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
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dei.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dei.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshalDeiDefaults.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  enum VpsHal_DeiConfigOvlyIdx
 *  \brief Enums for the configuration overlay register offsets - used as array
 *  indices to register offset array. These enums defines the registers
 *  that will be used to form the configuration register overlay.
 *  This in turn is used by client drivers to configure registers using
 *  VPDMA during context-switching (software channels with different
 *  configurations).
 *
 *  Note: If in future it is decided to remove or add some register, this
 *  enum should be modified accordingly.
 *  And make sure that the values of these enums are in ascending order
 *  and it starts from 0.
 */
typedef enum
{
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG0 = 0,
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG1,
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG3,
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG8,
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG9,
    VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG10,
    VPSHAL_DEI_NUM_REG_IDX              /* This should be the last enum */
} VpsHal_DeiConfigOvlyIdx;

/**
 *  Macros for maximum value possible for some of the bit fields used.
 */
#define VPSHAL_DEI_MAX_DEI_WIDTH \
    (DEI_REG0_WIDTH_MASK >> DEI_REG0_WIDTH_SHIFT)
#define VPSHAL_DEI_MAX_DEI_HEIGHT \
    (DEI_REG0_HEIGHT_MASK >> DEI_REG0_HEIGHT_SHIFT)
#define VPSHAL_DEI_MAX_FMD_WINDOW_MINX \
    (DEI_REG8_FMD_WINDOW_MINX_MASK >> DEI_REG8_FMD_WINDOW_MINX_SHIFT)
#define VPSHAL_DEI_MAX_FMD_WINDOW_MINY \
    (DEI_REG9_FMD_WINDOW_MINY_MASK >> DEI_REG9_FMD_WINDOW_MINY_SHIFT)
#define VPSHAL_DEI_MAX_FMD_WINDOW_MAXX \
    (DEI_REG8_FMD_WINDOW_MAXX_MASK >> DEI_REG8_FMD_WINDOW_MAXX_SHIFT)
#define VPSHAL_DEI_MAX_FMD_WINDOW_MAXY \
    (DEI_REG9_FMD_WINDOW_MAXY_MASK >> DEI_REG9_FMD_WINDOW_MAXY_SHIFT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DeiObj
 *  \brief Per instance information about each DEI module.
 */
typedef struct
{
    UInt32  halId;
    /**< Instance number/ID */
    UInt32  baseAddr;
    /**< Base address for the current instance */
    UInt32  openCnt;
    /**< Counter to keep track of number of open calls for an instance */
    UInt32  configOvlySize;
    /**< Size (in bytes) of VPDMA register configuration overlay memory
     *   required */
    UInt32 *regOffset[VPSHAL_DEI_NUM_REG_IDX];
    /**< Array of register offsets for all the registers that needs to be
     *   programmed through VPDMA */
    UInt32  virRegOffset[VPSHAL_DEI_NUM_REG_IDX];
    /**< Array of virtual register offsets in the VPDMA register configuration
     *   overlay memory corresponding to regOffset member */
} VpsHal_DeiObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 halDeiInitInstance(VpsHal_DeiObj *deiObj);

static Int32 halDeiSetExpertConfig(const VpsHal_DeiObj          *deiObj,
                                   const VpsHal_DeiExpertConfig *config);

static inline UInt32 halDeiMakeDeiReg0Reg(UInt32 initRegVal,
                                          UInt16 width,
                                          UInt16 height,
                                          UInt32 interlaceBypass,
                                          UInt32 fieldFlush,
                                          UInt32 progressiveBypass);
static inline UInt32 halDeiMakeDeiReg1Reg(UInt32 initRegVal,
                                          UInt32 spatMaxBypass,
                                          UInt32 tempMaxBypass);
static inline UInt32 halDeiMakeDeiReg3Reg(UInt32 initRegVal,
                                          UInt32 inpMode,
                                          UInt32 tempInpEnable,
                                          UInt32 tempInpChromaEnable);
static inline UInt32 halDeiMakeDeiReg8Reg(UInt32 initRegVal,
                                          UInt16 windowMinx,
                                          UInt16 windowMaxx,
                                          UInt32 window);
static inline UInt32 halDeiMakeDeiReg9Reg(UInt32 initRegVal,
                                          UInt16 windowMiny,
                                          UInt16 windowMaxy);
static inline UInt32 halDeiMakeDeiReg10Reg(UInt32 initRegVal,
                                           UInt32 filmMode,
                                           UInt32 bed,
                                           UInt32 lock,
                                           UInt32 jamDir);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  DEI objects - Module variable to store information about each DEI instance.
 *  Note: If the number of DEI instance increase, then VPSHAL_DEI_MAX_INST
 *  macro should be changed accordingly.
 */
static VpsHal_DeiObj gDeiHalObj[VPSHAL_DEI_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_deiInit
 *  \brief DEI HAL init function.
 *
 *  Initializes DEI objects, gets the register overlay offsets for DEI
 *  registers.
 *  This function should be called before calling any of DEI HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiInit(UInt32                      numInst,
                     const VpsHal_DeiInstParams *instPrms,
                     Ptr                         arg)
{
    Int32          retVal = BSP_SOK;
    UInt32         instCnt;
    VpsHal_DeiObj *deiObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, numInst <= VPSHAL_DEI_MAX_INST);
    GT_assert(VpsHalTrace, instPrms != NULL);

    /* Initialize DEI Objects to zero */
    BspUtils_memset(gDeiHalObj, 0, sizeof (gDeiHalObj));

    for (instCnt = 0; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  instPrms[instCnt].halId < VPSHAL_DEI_INST_ID_MAX);

        deiObj           = &gDeiHalObj[instCnt];
        deiObj->halId    = instPrms[instCnt].halId;
        deiObj->baseAddr = instPrms[instCnt].baseAddr;

        /* Initialize the instance */
        retVal += halDeiInitInstance(deiObj);
    }

    return (retVal);
}

/**
 *  VpsHal_deiDeInit
 *  \brief DEI HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiDeInit(Ptr arg)
{
    UInt32 instCnt;

    for (instCnt = 0; instCnt < VPSHAL_DEI_MAX_INST; instCnt++)
    {
        gDeiHalObj[instCnt].halId    = 0;
        gDeiHalObj[instCnt].baseAddr = 0;
        gDeiHalObj[instCnt].openCnt  = 0;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiOpen
 *  \brief Returns the handle to the requested DEI instance.
 *
 *  This function should be called prior to calling any of the DEI HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DEI instance.
 *
 *  \return                 Returns DEI instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_deiOpen(const VpsHal_DeiOpenParams *openPrms)
{
    UInt32        cnt;
    VpsHal_Handle handle = NULL;

    /* Check if instance number is valid */
    GT_assert(VpsHalTrace, NULL != openPrms);
    GT_assert(VpsHalTrace, openPrms->halId < VPSHAL_DEI_INST_ID_MAX);

    for (cnt = 0; cnt < VPSHAL_DEI_MAX_INST; cnt++)
    {
        /* Return the matching instance handle */
        if (openPrms->halId == gDeiHalObj[cnt].halId)
        {
            /* Check whether some one has already opened this instance */
            if (0U == gDeiHalObj[cnt].openCnt)
            {
                handle = (VpsHal_Handle) & gDeiHalObj[cnt];
                gDeiHalObj[cnt].openCnt++;
            }
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_deiClose
 *  \brief Closes the DEI HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_deiOpen function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiClose(VpsHal_Handle handle)
{
    Int32          retVal = BSP_EFAIL;
    VpsHal_DeiObj *deiObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    deiObj = (VpsHal_DeiObj *) handle;

    /* Decrement the open count */
    if (deiObj->openCnt > 0U)
    {
        deiObj->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsHal_deiGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA register configuration
 *  overlay required to program the DEI registers using VPDMA config
 *  descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the DEI registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context
 *  (multiple instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay
 *  one-time and submit this to VPDMA everytime when context changes.
 *  Thus saving valuable CPU in programming the VPS registers.
 *
 *  \param handle           Instance handle
 *  \return                 Returns the size of config overlay memory
 */
UInt32 VpsHal_deiGetConfigOvlySize(VpsHal_Handle handle)
{
    UInt32 configOvlySize = 0;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    /* Return the value already got in init function */
    configOvlySize = ((VpsHal_DeiObj *) handle)->configOvlySize;

    return (configOvlySize);
}

/**
 *  VpsHal_deiCreateConfigOvly
 *  \brief Creates the DEI register configuration overlay using VPDMA
 *  helper function.
 *
 *  This function does not initialize the overlay with DEI configuration.
 *  It is the responsibility of the client driver to configure the overlay
 *  by calling VpsHal_deiSetConfig function before submitting the same
 *  to VPDMA for register configuration at runtime.
 *
 *  \param handle           Instance handle
 *  \param configOvlyPtr    Pointer to the overlay memory where the
 *                          overlay is formed. The memory for the overlay
 *                          should be allocated by client driver.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    Int32 retVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != configOvlyPtr);

    /* Create the register overlay */
    retVal = VpsHal_vpdmaCreateRegOverlay(
        ((VpsHal_DeiObj *) handle)->regOffset,
        VPSHAL_DEI_NUM_REG_IDX,
        configOvlyPtr);

    return (retVal);
}

/**
 *  VpsHal_deiSetConfig
 *  \brief Sets the entire DEI configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiSetConfig(VpsHal_Handle           handle,
                          const VpsHal_DeiConfig *config,
                          Ptr                     configOvlyPtr)
{
    Int32          retVal;
    UInt32         height;
    UInt32         tempReg;
    UInt32        *virRegOffset;
    UInt32         interlaceBypass;
    UInt32         progressiveBypass;
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    /* Check whether parameters are valid */
    GT_assert(VpsHalTrace, config->width <= VPSHAL_DEI_MAX_DEI_WIDTH);
    GT_assert(VpsHalTrace, config->height <= VPSHAL_DEI_MAX_DEI_HEIGHT);

    /* Depending on mode and bypass parameters, decide the bypass values */
    if (FVID2_SF_INTERLACED == config->scanFormat)
    {
        if (TRUE == config->bypass)
        {
            /* For the interlaced bypass mode, output height is field height */
            height            = config->height;
            interlaceBypass   = (UInt32) TRUE;
            progressiveBypass = (UInt32) FALSE;
        }
        else /* Bypass disabled - Normal operation */
        {
            /* For the de-interlacing mode, output height is frame height */
            height            = (UInt32) config->height * 2U;
            interlaceBypass   = (UInt32) FALSE;
            progressiveBypass = (UInt32) FALSE;
        }
    }
    else /* Progressive mode */
    {
        /* For interlaced, config parameters has frame height. For
         * progressive bypass mode, DEI should
         * be configured with the half of the frame size */
        height = config->height;
        /* For progressive inputs, irrespective of the bypass flag DEI should
         * be set in bypass mode only
         * Progressive bypass mode is not supported in DEI, so make it
         * interlaced bypass */
        interlaceBypass   = (UInt32) TRUE;
        progressiveBypass = (UInt32) FALSE;
    }

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    /* Make register */
    tempReg = halDeiMakeDeiReg0Reg(
        HW_RD_REG32(baseAddr + DEI_REG0),
        config->width,
        (UInt16) height,
        interlaceBypass,
        config->fieldFlush,
        progressiveBypass);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG0, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG0];
        *virRegOffset = tempReg;
    }

    /* Call individual functions to set the configuration */
    retVal  = VpsHal_deiSetMdtConfig(handle, &config->mdt, configOvlyPtr);
    retVal += VpsHal_deiSetEdiConfig(handle, &config->edi, configOvlyPtr);
    retVal += VpsHal_deiSetFmdConfig(
        handle,
        &config->fmd,
        configOvlyPtr,
        config->width,
        config->height);

    return (retVal);
}

/**
 *  VpsHal_deiSetMdtConfig
 *  \brief Sets the entire DEI MDT configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI MDT registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiMdtConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiSetMdtConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiMdtConfig *config,
                             Ptr                        configOvlyPtr)
{
    UInt32         tempReg;
    UInt32        *virRegOffset;
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    /* Make register */
    tempReg = halDeiMakeDeiReg1Reg(
        HW_RD_REG32(baseAddr + DEI_REG1),
        config->spatMaxBypass,
        config->tempMaxBypass);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG1, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG1];
        *virRegOffset = tempReg;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiSetEdiConfig
 *  \brief Sets the entire DEI EDI configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI EDI registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiEdiConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiSetEdiConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiEdiConfig *config,
                             Ptr                        configOvlyPtr)
{
    UInt32         tempReg;
    UInt32        *virRegOffset;
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);
    /* If temporal Interpolation for luma is disabled, then temporal
     * interpolation for chroma should also be disabled */
    GT_assert(VpsHalTrace, (!((FALSE == config->tempInpEnable) &&
                              (TRUE == config->tempInpChromaEnable))));

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    /* Make register */
    tempReg = halDeiMakeDeiReg3Reg(
        HW_RD_REG32(baseAddr + DEI_REG3),
        config->inpMode,
        config->tempInpEnable,
        config->tempInpChromaEnable);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG3, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG3];
        *virRegOffset = tempReg;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiSetFmdConfig
 *  \brief Sets the entire DEI FMD configuration to either the actual DEI
 *  registers or to the configuration overlay memory.
 *
 *  This function configures the entire DEI FMD registers. Depending
 *  on the value of configOvlyPtr parameter, the updating will happen
 *  to actual DEI MMR or to configuration overlay memory.
 *  This function configures all the sub-modules in DEI using other
 *  config function call.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *  \param width            Picture width at output.
 *  \param height           Picture height at output.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiSetFmdConfig(VpsHal_Handle              handle,
                             const VpsHal_DeiFmdConfig *config,
                             Ptr                        configOvlyPtr,
                             UInt32                     width,
                             UInt32                     height)
{
    UInt32         tempReg;
    UInt32        *virRegOffset;
    UInt32         windowWidth, windowHeight;
    UInt16         windowDimenValue;
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    /* Check whether parameters are valid */
    GT_assert(VpsHalTrace,
              config->windowMinx <= VPSHAL_DEI_MAX_FMD_WINDOW_MINX);
    GT_assert(VpsHalTrace,
              config->windowMiny <= VPSHAL_DEI_MAX_FMD_WINDOW_MINY);
    GT_assert(VpsHalTrace,
              config->windowMaxx <= VPSHAL_DEI_MAX_FMD_WINDOW_MAXX);
    GT_assert(VpsHalTrace,
              config->windowMaxy <= VPSHAL_DEI_MAX_FMD_WINDOW_MAXY);

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    /*
     * Check whether the window size is less than the already set values
     */
    windowDimenValue = (config->windowMaxx - config->windowMinx) + (UInt16) 1U;
    windowWidth      = (UInt32) windowDimenValue;
    windowDimenValue = (config->windowMaxy - config->windowMiny) + (UInt16) 1U;
    windowHeight     = (UInt32) windowDimenValue;
    GT_assert(VpsHalTrace, windowWidth <= width);
    GT_assert(VpsHalTrace, windowHeight <= height);

    /* Make register */
    tempReg = halDeiMakeDeiReg8Reg(
        HW_RD_REG32(baseAddr + DEI_REG8),
        config->windowMinx,
        config->windowMaxx,
        config->window);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG8, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG8];
        *virRegOffset = tempReg;
    }

    /* Make register */
    tempReg = halDeiMakeDeiReg9Reg(
        HW_RD_REG32(baseAddr + DEI_REG9),
        config->windowMiny,
        config->windowMaxy);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG9, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG9];
        *virRegOffset = tempReg;
    }

    /* Make register */
    tempReg = halDeiMakeDeiReg10Reg(
        HW_RD_REG32(baseAddr + DEI_REG10),
        config->filmMode,
        config->bed,
        config->lock,
        config->jamDir);
    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG10, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG10];
        *virRegOffset = tempReg;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiGetConfig
 *  \brief Gets the entire DEI configuration from the actual DEI registers.
 *
 *  This function gets the entire DEI configuration. This function
 *  gets the configuration of all the sub-modules in DEI using other
 *  get configuration function calls.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiGetConfig(VpsHal_Handle handle, VpsHal_DeiConfig *config)
{
    Int32          retVal = BSP_EFAIL;
    UInt32         interlaceBypass;
    UInt32         progressiveBypass;
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    baseAddr = deiObj->baseAddr;

    /* Get DEI configurations */
    config->width      = HW_RD_FIELD32(baseAddr + DEI_REG0, DEI_REG0_WIDTH);
    config->height     = HW_RD_FIELD32(baseAddr + DEI_REG0, DEI_REG0_HEIGHT);
    config->fieldFlush =
        HW_RD_FIELD32(baseAddr + DEI_REG0, DEI_REG0_FIELD_FLUSH);
    progressiveBypass =
        HW_RD_FIELD32(baseAddr + DEI_REG0, DEI_REG0_PROGRESSIVE_BYPASS);
    interlaceBypass =
        HW_RD_FIELD32(baseAddr + DEI_REG0, DEI_REG0_INTERLACE_BYPASS);

    if (TRUE == interlaceBypass)
    {
        if (TRUE == progressiveBypass)
        {
            /* Invalid state - This can never happen */
            GT_0trace(VpsHalTrace, GT_ERR,
                      "VpsHal_deiGetConfig: Invalid bypass settings!!\r\n");
            config->scanFormat = FVID2_SF_PROGRESSIVE;
            config->bypass     = (UInt32) TRUE;
        }
        else        /* Progressive Bypass Disabled */
        {
            /* Deinterlace bypass operation */
            config->scanFormat = FVID2_SF_INTERLACED;
            config->bypass     = (UInt32) TRUE;
        }
    }
    else            /* Interlace Bypass Disabled */
    {
        if (TRUE == progressiveBypass)
        {
            /* Progressive bypass operation */
            config->scanFormat = FVID2_SF_PROGRESSIVE;
            config->bypass     = (UInt32) TRUE;
        }
        else        /* Progressive Bypass Disabled */
        {
            /* Normal deinterlace operation */
            config->scanFormat = FVID2_SF_INTERLACED;
            config->bypass     = (UInt32) FALSE;
        }
    }

    /* Call individual functions to get the configuration */
    retVal  = VpsHal_deiGetMdtConfig(handle, &config->mdt);
    retVal += VpsHal_deiGetEdiConfig(handle, &config->edi);
    retVal += VpsHal_deiGetFmdConfig(handle, &config->fmd);

    return (retVal);
}

/**
 *  VpsHal_deiGetMdtConfig
 *  \brief Gets DEI MDT configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to MDT module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiMdtConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiGetMdtConfig(VpsHal_Handle handle, VpsHal_DeiMdtConfig *config)
{
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    baseAddr = deiObj->baseAddr;

    /* Get MDT configurations */
    config->spatMaxBypass =
        HW_RD_FIELD32(baseAddr + DEI_REG1, DEI_REG1_MDT_SPATMAX_BYPASS);
    config->tempMaxBypass =
        HW_RD_FIELD32(baseAddr + DEI_REG1, DEI_REG1_MDT_TEMPMAX_BYPASS);

    return (BSP_SOK);
}

/**
 *  VpsHal_deiGetEdiConfig
 *  \brief Gets DEI EDI configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to EDI module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiEdiConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiGetEdiConfig(VpsHal_Handle handle, VpsHal_DeiEdiConfig *config)
{
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    baseAddr = deiObj->baseAddr;

    /* Get EDI configurations */
    config->inpMode = HW_RD_FIELD32(baseAddr + DEI_REG3,
                                    DEI_REG3_EDI_INP_MODE);
    config->tempInpEnable =
        HW_RD_FIELD32(baseAddr + DEI_REG3, DEI_REG3_EDI_ENABLE_3D);
    config->tempInpChromaEnable =
        HW_RD_FIELD32(baseAddr + DEI_REG3, DEI_REG3_EDI_CHROMA_3D_ENABLE);

    return (BSP_SOK);
}

/**
 *  VpsHal_deiGetFmdConfig
 *  \brief Gets DEI FMD configuration from the actual DEI registers.
 *
 *  This function gets the DEI configuration specific to FMD module.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdConfig structure to be
 *                          filled with register configurations.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiGetFmdConfig(VpsHal_Handle handle, VpsHal_DeiFmdConfig *config)
{
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    baseAddr = deiObj->baseAddr;

    /* Get FMD configurations from DEI_REG8 */
    config->window =
        HW_RD_FIELD32(baseAddr + DEI_REG8, DEI_REG8_FMD_WINDOW_ENABLE);
    config->windowMinx =
        HW_RD_FIELD32(baseAddr + DEI_REG8, DEI_REG8_FMD_WINDOW_MINX);
    config->windowMaxx =
        HW_RD_FIELD32(baseAddr + DEI_REG8, DEI_REG8_FMD_WINDOW_MAXX);

    /* Get FMD configurations from DEI_REG9 */
    config->windowMiny =
        HW_RD_FIELD32(baseAddr + DEI_REG9, DEI_REG9_FMD_WINDOW_MINY);
    config->windowMaxy =
        HW_RD_FIELD32(baseAddr + DEI_REG9, DEI_REG9_FMD_WINDOW_MAXY);

    /* Get FMD configurations from DEI_REG10 */
    config->filmMode =
        HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_ENABLE);
    config->bed  = HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_BED_ENABLE);
    config->lock = HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_LOCK);
    if (0U != HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_JAM_DIR))
    {
        config->jamDir = VPS_DEI_FMDJAMDIR_NEXT_FLD;
    }
    else            /* Jam direction - Previous field */
    {
        config->jamDir = VPS_DEI_FMDJAMDIR_PREV_FLD;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiGetFmdStatus
 *  \brief Returns DEI FMD status information that is needed by the FMD
 *  software (ISR context) at each frame ready interrupt.
 *
 *  \param handle           Instance handle
 *  \param status           Pointer to VpsHal_DeiFmdStatus structure
 *                          containing the register status.
 *                          This parameter should be non-NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiGetFmdStatus(VpsHal_Handle handle, VpsHal_DeiFmdStatus *status)
{
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != status);

    baseAddr = deiObj->baseAddr;

    /* Get FMD CAF and Reset status */
    status->caf   = HW_RD_FIELD32(baseAddr + DEI_REG12, DEI_REG12_FMD_CAF);
    status->reset = HW_RD_FIELD32(baseAddr + DEI_REG12, DEI_REG12_FMD_RESET);

    /* Get FMD Field Difference status */
    status->fldDiff =
        HW_RD_FIELD32(baseAddr + DEI_REG13, DEI_REG13_FMD_FIELD_DIFF);

    /* Get FMD Frame Difference status */
    status->frameDiff =
        HW_RD_FIELD32(baseAddr + DEI_REG14, DEI_REG14_FMD_FRAME_DIFF);

    return (BSP_SOK);
}

/**
 *  VpsHal_deiUpdateFmdConfig
 *  \brief Updates DEI FMD configuration that needs to be updated by the
 *  FMD software (ISR context) at each frame ready interrupt.
 *
 *  \param handle           Instance handle
 *  \param config           Pointer to VpsHal_DeiFmdUpdateConfig structure
 *                          containing the register configurations.
 *                          This parameter should be non-NULL.
 *  \param configOvlyPtr    Pointer to the configuration overlay memory.
 *                          If this parameter is NULL, then the
 *                          configuration is written to the actual
 *                          DEI registers. Otherwise the configuration
 *                          is updated in the memory pointed
 *                          by the same at proper virtual offsets.
 *                          This parameter can be NULL depending
 *                          on the intended usage.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_deiUpdateFmdConfig(VpsHal_Handle                    handle,
                                const VpsHal_DeiFmdUpdateConfig *config,
                                Ptr                              configOvlyPtr)
{
    UInt32         tempReg;
    UInt32        *virRegOffset;
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != config);

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    tempReg = HW_RD_REG32(baseAddr + DEI_REG10);
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_LOCK, config->lock);
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_JAM_DIR, config->jamDir);

    if (NULL == configOvlyPtr)
    {
        /* Write to the actual register */
        HW_WR_REG32(baseAddr + DEI_REG10, tempReg);
    }
    else            /* Update in config overlay memory */
    {
        /* Write to config register overlay at the correct offset. Since the
         * offset is in words, it can be directly added to the pointer so that
         * (UInt32 *) addition will result in proper offset value */
        virRegOffset =
            (UInt32 *) configOvlyPtr +
            deiObj->virRegOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG10];
        *virRegOffset = tempReg;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_deiSetAdvConfig
 */
Int32 VpsHal_deiSetAdvConfig(VpsHal_Handle            handle,
                             const Vps_DeiRdWrAdvCfg *advCfg,
                             Ptr                      configOvlyPtr)
{
    VpsHal_DeiObj *deiObj;
    UInt32         baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != advCfg);

    deiObj   = (VpsHal_DeiObj *) handle;
    baseAddr = deiObj->baseAddr;

    /* Write MDT configurations to DEI_REG2 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG2,
        DEI_REG2_MDT_MVSTMAX_COR_THR,
        advCfg->mdtCfg.mvstmMaxCorThr);
    HW_WR_FIELD32(
        baseAddr + DEI_REG2,
        DEI_REG2_MDT_MV_COR_THR,
        advCfg->mdtCfg.mvCorThr);
    HW_WR_FIELD32(
        baseAddr + DEI_REG2,
        DEI_REG2_MDT_SF_SC_THR1,
        advCfg->mdtCfg.sfScThr[0U]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG2,
        DEI_REG2_MDT_SF_SC_THR2,
        advCfg->mdtCfg.sfScThr[1U]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG2,
        DEI_REG2_MDT_SF_SC_THR3,
        advCfg->mdtCfg.sfScThr[2U]);

    /* Write MDT configurations to DEI_REG3 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG3,
        DEI_REG3_EDI_COR_SCALE_FACTOR,
        advCfg->ediCfg.corScaleFactor);
    HW_WR_FIELD32(
        baseAddr + DEI_REG3,
        DEI_REG3_EDI_DIR_COR_LOWER_THR,
        advCfg->ediCfg.detCorLowerThr);
    HW_WR_FIELD32(
        baseAddr + DEI_REG3,
        DEI_REG3_EDI_CHROMA3D_COR_THR,
        advCfg->ediCfg.chroma3DCorThr);

    /* Write EDI LUT configurations to DEI_REG4 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG4,
        DEI_REG4_EDI_LUT0,
        advCfg->ediCfg.lut[0]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG4,
        DEI_REG4_EDI_LUT1,
        advCfg->ediCfg.lut[1]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG4,
        DEI_REG4_EDI_LUT2,
        advCfg->ediCfg.lut[2]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG4,
        DEI_REG4_EDI_LUT3,
        advCfg->ediCfg.lut[3]);

    /* Write EDI LUT configurations to DEI_REG5 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG5,
        DEI_REG5_EDI_LUT4,
        advCfg->ediCfg.lut[4]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG5,
        DEI_REG5_EDI_LUT5,
        advCfg->ediCfg.lut[5]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG5,
        DEI_REG5_EDI_LUT6,
        advCfg->ediCfg.lut[6]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG5,
        DEI_REG5_EDI_LUT7,
        advCfg->ediCfg.lut[7]);

    /* Write EDI LUT configurations to DEI_REG6 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG6,
        DEI_REG6_EDI_LUT8,
        advCfg->ediCfg.lut[8]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG6,
        DEI_REG6_EDI_LUT9,
        advCfg->ediCfg.lut[9]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG6,
        DEI_REG6_EDI_LUT10,
        advCfg->ediCfg.lut[10]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG6,
        DEI_REG6_EDI_LUT11,
        advCfg->ediCfg.lut[11]);

    /* Write EDI LUT configurations to DEI_REG7 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG7,
        DEI_REG7_EDI_LUT12,
        advCfg->ediCfg.lut[12]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG7,
        DEI_REG7_EDI_LUT13,
        advCfg->ediCfg.lut[13]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG7,
        DEI_REG7_EDI_LUT14,
        advCfg->ediCfg.lut[14]);
    HW_WR_FIELD32(
        baseAddr + DEI_REG7,
        DEI_REG7_EDI_LUT15,
        advCfg->ediCfg.lut[15]);

    /* Write FMD configurations to DEI_REG10 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG10,
        DEI_REG10_FMD_CAF_LINE_THR,
        advCfg->fmdCfg.cafLineThr);
    HW_WR_FIELD32(
        baseAddr + DEI_REG10,
        DEI_REG10_FMD_CAF_FIELD_THR,
        advCfg->fmdCfg.cafFieldThr);

    /* Write FMD configurations to DEI_REG11 */
    HW_WR_FIELD32(
        baseAddr + DEI_REG11,
        DEI_REG11_FMD_CAF_THR,
        advCfg->fmdCfg.cafThr);

    return (BSP_SOK);
}

/**
 *  VpsHal_deiGetAdvConfig
 */
Int32 VpsHal_deiGetAdvConfig(VpsHal_Handle      handle,
                             Vps_DeiRdWrAdvCfg *advCfg)
{
    UInt32         baseAddr;
    VpsHal_DeiObj *deiObj = (VpsHal_DeiObj *) handle;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != advCfg);

    baseAddr = deiObj->baseAddr;

    /* Get MDT configurations from DEI_REG2 */
    advCfg->mdtCfg.mvstmMaxCorThr =
        HW_RD_FIELD32(baseAddr + DEI_REG2, DEI_REG2_MDT_MVSTMAX_COR_THR);
    advCfg->mdtCfg.mvCorThr =
        HW_RD_FIELD32(baseAddr + DEI_REG2, DEI_REG2_MDT_MV_COR_THR);
    advCfg->mdtCfg.sfScThr[0U] =
        HW_RD_FIELD32(baseAddr + DEI_REG2, DEI_REG2_MDT_SF_SC_THR1);
    advCfg->mdtCfg.sfScThr[1U] =
        HW_RD_FIELD32(baseAddr + DEI_REG2, DEI_REG2_MDT_SF_SC_THR2);
    advCfg->mdtCfg.sfScThr[2U] =
        HW_RD_FIELD32(baseAddr + DEI_REG2, DEI_REG2_MDT_SF_SC_THR3);

    /* Get EDI configurations from DEI_REG3 */
    advCfg->ediCfg.corScaleFactor =
        HW_RD_FIELD32(baseAddr + DEI_REG3, DEI_REG3_EDI_COR_SCALE_FACTOR);
    advCfg->ediCfg.detCorLowerThr =
        HW_RD_FIELD32(baseAddr + DEI_REG3, DEI_REG3_EDI_DIR_COR_LOWER_THR);
    advCfg->ediCfg.chroma3DCorThr =
        HW_RD_FIELD32(baseAddr + DEI_REG3, DEI_REG3_EDI_CHROMA3D_COR_THR);

    /* Get EDI LUT configurations from DEI_REG4 */
    advCfg->ediCfg.lut[0] =
        HW_RD_FIELD32(baseAddr + DEI_REG4, DEI_REG4_EDI_LUT0);
    advCfg->ediCfg.lut[1] =
        HW_RD_FIELD32(baseAddr + DEI_REG4, DEI_REG4_EDI_LUT1);
    advCfg->ediCfg.lut[2] =
        HW_RD_FIELD32(baseAddr + DEI_REG4, DEI_REG4_EDI_LUT2);
    advCfg->ediCfg.lut[3] =
        HW_RD_FIELD32(baseAddr + DEI_REG4, DEI_REG4_EDI_LUT3);

    /* Get EDI LUT configurations from DEI_REG5 */
    advCfg->ediCfg.lut[4] =
        HW_RD_FIELD32(baseAddr + DEI_REG5, DEI_REG5_EDI_LUT4);
    advCfg->ediCfg.lut[5] =
        HW_RD_FIELD32(baseAddr + DEI_REG5, DEI_REG5_EDI_LUT5);
    advCfg->ediCfg.lut[6] =
        HW_RD_FIELD32(baseAddr + DEI_REG5, DEI_REG5_EDI_LUT6);
    advCfg->ediCfg.lut[7] =
        HW_RD_FIELD32(baseAddr + DEI_REG5, DEI_REG5_EDI_LUT7);

    /* Get EDI LUT configurations from DEI_REG6 */
    advCfg->ediCfg.lut[8] =
        HW_RD_FIELD32(baseAddr + DEI_REG6, DEI_REG6_EDI_LUT8);
    advCfg->ediCfg.lut[9] =
        HW_RD_FIELD32(baseAddr + DEI_REG6, DEI_REG6_EDI_LUT9);
    advCfg->ediCfg.lut[10] =
        HW_RD_FIELD32(baseAddr + DEI_REG6, DEI_REG6_EDI_LUT10);
    advCfg->ediCfg.lut[11] =
        HW_RD_FIELD32(baseAddr + DEI_REG6, DEI_REG6_EDI_LUT11);

    /* Get EDI LUT configurations from DEI_REG7 */
    advCfg->ediCfg.lut[12] =
        HW_RD_FIELD32(baseAddr + DEI_REG7, DEI_REG7_EDI_LUT12);
    advCfg->ediCfg.lut[13] =
        HW_RD_FIELD32(baseAddr + DEI_REG7, DEI_REG7_EDI_LUT13);
    advCfg->ediCfg.lut[14] =
        HW_RD_FIELD32(baseAddr + DEI_REG7, DEI_REG7_EDI_LUT14);
    advCfg->ediCfg.lut[15] =
        HW_RD_FIELD32(baseAddr + DEI_REG7, DEI_REG7_EDI_LUT15);

    /* Get FMD configurations from DEI_REG10 */
    advCfg->fmdCfg.cafLineThr =
        HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_CAF_LINE_THR);
    advCfg->fmdCfg.cafFieldThr =
        HW_RD_FIELD32(baseAddr + DEI_REG10, DEI_REG10_FMD_CAF_FIELD_THR);

    /* Get FMD configurations from DEI_REG11 */
    advCfg->fmdCfg.cafThr =
        HW_RD_FIELD32(baseAddr + DEI_REG11, DEI_REG11_FMD_CAF_THR);

    return (BSP_SOK);
}

/**
 *  halDeiInitInstance
 *  Initialize the DEI instance by writing to expert registers and figuring
 *  out the virtual offsets of registers for config overlay memory.
 */
static Int32 halDeiInitInstance(VpsHal_DeiObj *deiObj)
{
    Int32  retVal;
    UInt32 baseAddr;
    VpsHal_DeiExpertConfig deiExpertConfig = VPSHAL_DEI_DEFAULT_EXPERT_VAL;
    UInt32 deiRegValue;

    baseAddr = deiObj->baseAddr;

    /* Set the expert registers with recommended value */
    retVal = halDeiSetExpertConfig(deiObj, &deiExpertConfig);

    /* Initialize the register offsets for the registers which are used
     * to form the VPDMA configuration overlay */
    deiRegValue = baseAddr + DEI_REG0;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG0] =
        (UInt32 *) deiRegValue;
    deiRegValue = baseAddr + DEI_REG1;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG1] =
        (UInt32 *) deiRegValue;
    deiRegValue = baseAddr + DEI_REG3;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG3] =
        (UInt32 *) deiRegValue;
    deiRegValue = baseAddr + DEI_REG8;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG8] =
        (UInt32 *) deiRegValue;
    deiRegValue = baseAddr + DEI_REG9;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG9] =
        (UInt32 *) deiRegValue;
    deiRegValue = baseAddr + DEI_REG10;
    deiObj->regOffset[VPSHAL_DEI_CONFIGOVLYIDX_DEI_REG10] =
        (UInt32 *) deiRegValue;

    /* Get the size of the overlay for DEI registers and the relative
     * virtual offset for the above registers when VPDMA config register
     * overlay is formed */
    deiObj->configOvlySize = VpsHal_vpdmaCalcRegOvlyMemSize(
        deiObj->regOffset,
        VPSHAL_DEI_NUM_REG_IDX,
        deiObj->virRegOffset);

    return (retVal);
}

/**
 *  halDeiSetExpertConfig
 *  Set the expert registers with expert values.
 */
static Int32 halDeiSetExpertConfig(const VpsHal_DeiObj          *deiObj,
                                   const VpsHal_DeiExpertConfig *config)
{
    UInt32 baseAddr;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != deiObj);
    GT_assert(VpsHalTrace, NULL != config);

    baseAddr = deiObj->baseAddr;

    /* Write to DEI expert registers */
    HW_WR_REG32(baseAddr + DEI_REG2, config->deiReg2);
    HW_WR_REG32(baseAddr + DEI_REG3, config->deiReg3);
    HW_WR_REG32(baseAddr + DEI_REG4, config->deiReg4);
    HW_WR_REG32(baseAddr + DEI_REG5, config->deiReg5);
    HW_WR_REG32(baseAddr + DEI_REG6, config->deiReg6);
    HW_WR_REG32(baseAddr + DEI_REG7, config->deiReg7);
    HW_WR_REG32(baseAddr + DEI_REG10, config->deiReg10);
    HW_WR_REG32(baseAddr + DEI_REG11, config->deiReg11);

    return (BSP_SOK);
}

/**
 *  halDeiMakeDeiReg0Reg
 *  Make DEI REG0 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg0Reg(UInt32 initRegVal,
                                          UInt16 width,
                                          UInt16 height,
                                          UInt32 interlaceBypass,
                                          UInt32 fieldFlush,
                                          UInt32 progressiveBypass)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set Height and Width */
    HW_SET_FIELD32(tempReg, DEI_REG0_WIDTH, width);
    HW_SET_FIELD32(tempReg, DEI_REG0_HEIGHT, height);

    /* Set interlace bypass field */
    HW_SET_FIELD32(tempReg, DEI_REG0_INTERLACE_BYPASS, interlaceBypass);

    /* Set field flush field */
    HW_SET_FIELD32(tempReg, DEI_REG0_FIELD_FLUSH, fieldFlush);

    /* Set progressive bypass field */
    HW_SET_FIELD32(tempReg, DEI_REG0_PROGRESSIVE_BYPASS, progressiveBypass);

    return (tempReg);
}

/**
 *  halDeiMakeDeiReg1Reg
 *  Make DEI REG1 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg1Reg(UInt32 initRegVal,
                                          UInt32 spatMaxBypass,
                                          UInt32 tempMaxBypass)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set temporal max bypass field */
    HW_SET_FIELD32(tempReg, DEI_REG1_MDT_TEMPMAX_BYPASS, tempMaxBypass);

    /* Set spatial max bypass field */
    HW_SET_FIELD32(tempReg, DEI_REG1_MDT_SPATMAX_BYPASS, spatMaxBypass);

    return (tempReg);
}

/**
 *  halDeiMakeDeiReg3Reg
 *  Make DEI REG3 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg3Reg(UInt32 initRegVal,
                                          UInt32 inpMode,
                                          UInt32 tempInpEnable,
                                          UInt32 tempInpChromaEnable)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set EDI interpolation Mode */
    HW_SET_FIELD32(tempReg, DEI_REG3_EDI_INP_MODE, inpMode);

    /* Set temporal interpolation for luma field */
    HW_SET_FIELD32(tempReg, DEI_REG3_EDI_ENABLE_3D, tempInpEnable);

    /* Set temporal interpolation for chroma field */
    HW_SET_FIELD32(
        tempReg, DEI_REG3_EDI_CHROMA_3D_ENABLE, tempInpChromaEnable);

    return (tempReg);
}

/**
 *  halDeiMakeDeiReg8Reg
 *  Make DEI REG8 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg8Reg(UInt32 initRegVal,
                                          UInt16 windowMinx,
                                          UInt16 windowMaxx,
                                          UInt32 window)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set FMD window fields - horizontal limits */
    HW_SET_FIELD32(tempReg, DEI_REG8_FMD_WINDOW_MINX, windowMinx);
    HW_SET_FIELD32(tempReg, DEI_REG8_FMD_WINDOW_MAXX, windowMaxx);

    /* Set enable FMD window fields */
    HW_SET_FIELD32(tempReg, DEI_REG8_FMD_WINDOW_ENABLE, window);

    return (tempReg);
}

/**
 *  halDeiMakeDeiReg9Reg
 *  Make DEI REG9 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg9Reg(UInt32 initRegVal,
                                          UInt16 windowMiny,
                                          UInt16 windowMaxy)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set FMD window fields - vertical limits */
    HW_SET_FIELD32(tempReg, DEI_REG9_FMD_WINDOW_MINY, windowMiny);
    HW_SET_FIELD32(tempReg, DEI_REG9_FMD_WINDOW_MAXY, windowMaxy);

    return (tempReg);
}

/**
 *  halDeiMakeDeiReg10Reg
 *  Make DEI REG10 register with given parameters.
 */
static inline UInt32 halDeiMakeDeiReg10Reg(UInt32 initRegVal,
                                           UInt32 filmMode,
                                           UInt32 bed,
                                           UInt32 lock,
                                           UInt32 jamDir)
{
    UInt32 tempReg;

    tempReg = initRegVal;

    /* Set enable film mode field */
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_ENABLE, filmMode);

    /* Set lock to film mode field */
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_LOCK, lock);

    /* Set jamming direction field */
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_JAM_DIR, jamDir);

    /* Set enable bad edit detection field */
    HW_SET_FIELD32(tempReg, DEI_REG10_FMD_BED_ENABLE, bed);

    return (tempReg);
}

