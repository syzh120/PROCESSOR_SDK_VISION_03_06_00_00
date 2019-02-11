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
 *  \file vpshal_vpeTop.c
 *
 *  \brief HAL implementation for VPE-TOP
 *  This file implements the HAL APIs of the VPE Clock and Reset control
 *  modules, Interrupts and Muxes
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_vpe.h>
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
#include <ti/csl/cslr_vps.h>
#endif
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpeTop.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSHAL_VPE_TOP_ALL_MODULES  (VPSHAL_VPE_TOP_NUM_MODULES)

/**
 *  enum VpeTop_ConfigOvlyReg
 *
 *  \brief Enums for the configuration overlay register offsets - used as array
 *  indices to register offset array in VpeTop_Obj object. These enums defines
 *  the registers that will be used to form the configuration register overlay
 *  for VPE Top module. This in turn is used by client drivers to configure
 *  registers using VPDMA during context-switching (software channels with
 *  different configurations).
 *
 *  Note: If in future it is decided to remove or add some register, this enum
 *  should be modified accordingly. And make sure that the values of these
 *  enums are in ascending order and it starts from 0.
 */
typedef enum
{
    VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX = 0U,
    VPE_TOP_CONFIG_OVLY_NUM_IDX      = 1U,
    /**< This should be the last enum */
    VPE_TOP_CONFIG_OVLY_FORCE_INT = 0x7FFFFFFFU
                                    /* *< This will ensure enum is not
                                     *packed,will always be contained in int */
} VpeTop_ConfigOvlyReg;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_VpeTopInfo
 *  \brief Structure containing Instance Information for each VPE Instance.
 *         Primarily baseAddress for the VPE instance.
 */
typedef struct
{
    UInt32  halId;
    /**< Instance ID of VPE */
    UInt32  openCnt;
    /**< Number of handles opened */
    UInt32  baseAddr;
    /**< Base address of VPE TOP for current instance. */
    UInt32  regOvlySize;
    /**< Virtual register overlay size in terms of bytes. Used to allocate
     *   memory for virtual register configured through VPDMA. */
    UInt32 *regOffset[(UInt32)VPE_TOP_CONFIG_OVLY_NUM_IDX];
    /**< Array of physical address of the register configured through VPDMA
     *   register overlay. */
    UInt32  virtRegOffset[(UInt32)VPE_TOP_CONFIG_OVLY_NUM_IDX];
    /**< Array of indexes into the Overlay memory where virtual registers are
     *   to be configured */
} VpsHal_VpeTopInfo;

/**
 *  struct VpsHal_VpeTop
 *  \brief Handle structure for instances VPE TOP HAL
 */
typedef struct
{
    UInt32            numInst;
    /**< Num instances opened in HALInit */

    VpsHal_VpeTopInfo topObj[VPSHAL_VPE_TOP_MAX_INST];
    /**< Instance list for maximum supported instances */
} VpsHal_VpeTop;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 * vpeTopHalObj: VPE TOP HAL object containing all VPE TOP instances
 */
static VpsHal_VpeTop vpeTopHalObj;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  VpsHal_vpeTopInit
 *  \brief VPE HAL init function.
 *  This function should be called before calling any of VPE HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initParams         Pointer to #VpsHal_VpeTopInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_vpeTopInit(UInt32                         numInst,
                        const VpsHal_VpeTopInstParams *instPrms,
                        Ptr                            arg)
{
    UInt32 i;
    VpsHal_VpeTopInfo *instObj;
    UInt32 tempAddr;

    GT_assert(VpsHalTrace, instPrms != NULL);

    vpeTopHalObj.numInst = numInst;
    for (i = 0; i < numInst; i++)
    {
        instObj = &vpeTopHalObj.topObj[i];
        /* MISRA.PTR.ARIT */
        instObj->halId   = instPrms[i].halId;
        instObj->openCnt = 0;
        /* MISRA.PTR.ARIT */
        instObj->baseAddr = instPrms[i].baseAddr;

        /* Calculate VPDMA register overlay size and register offset in
         * the VPDMA register overlay. Since register organization for all
         * VPE TOP are same, only one array of register offset is sufficient. */
        tempAddr = (instObj->baseAddr + (UInt32) VPE_CLKC_DPS);
        instObj->regOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX] =
            (UInt32 *) tempAddr;

        instObj->regOvlySize =
            VpsHal_vpdmaCalcRegOvlyMemSize(
                instObj->regOffset,
                VPE_TOP_CONFIG_OVLY_NUM_IDX,
                instObj->virtRegOffset);
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_vpeTopDeInit
 *  \brief VPE HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         success    0
 *                  failure    error value
 *
 */
Int32 VpsHal_vpeTopDeInit(Ptr arg)
{
    UInt32 i;

    for (i = 0; i < vpeTopHalObj.numInst; i++)
    {
        GT_assert(VpsHalTrace, vpeTopHalObj.topObj[i].openCnt == 0);
        vpeTopHalObj.topObj[i].halId    = 0;
        vpeTopHalObj.topObj[i].openCnt  = 0;
        vpeTopHalObj.topObj[i].baseAddr = 0;
    }
    vpeTopHalObj.numInst = 0;

    return (BSP_SOK);
}

/**
 *  VpsHal_vpeTopOpen
 *  \brief Returns the handle to the requested Vpe instance.
 *  Multiple handles are supported.
 *
 *  This function should be called prior to calling any of the VPE HAL
 *  configuration APIs.
 *
 *  VpsHal_vpeInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openParams    VpsHal_VpeTopOpenParams
 *
 *  \return              success     VPE instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vpeTopOpen(const VpsHal_VpeTopOpenParams *openParams)
{
    VpsHal_Handle      vpeTopHandle = NULL;
    VpsHal_VpeTopInfo *vpeTopInfo   = NULL;
    UInt32 halId;

    halId = openParams->halId;
    if (halId < VPSHAL_VPE_TOP_MAX_INST)
    {
        vpeTopInfo = &(vpeTopHalObj.topObj[halId]);
        vpeTopInfo->openCnt++;
        vpeTopHandle = (VpsHal_Handle) (vpeTopInfo);

        VpsHal_vpeTopEnableAllModules(vpeTopHandle, (UInt32) TRUE, 0);
    }

    return (vpeTopHandle);
}

/**
 *  VpsHal_vpeClose
 *  \brief Closes specified instance of Vpe Top HAL
 *  VpsHal_vpeInit and Vpe_open should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_EFAIL;
    VpsHal_VpeTopInfo *topInfo;

    GT_assert(VpsHalTrace, NULL != handle);
    topInfo = (VpsHal_VpeTopInfo *) handle;
    if (0 != topInfo->openCnt)
    {
        topInfo->openCnt--;
        if (0 == topInfo->openCnt)
        {
            VpsHal_vpeTopEnableAllModules(handle, (UInt32) FALSE, 0);
        }
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopGetConfigOvlySize
 *  \brief Returns the size (in bytes) of the VPDMA
 *  register configuration overlay required to program the VPE TOP mux
 *  register using VPDMA config descriptors.
 *
 *  The client drivers can use this value to allocate memory for register
 *  overlay used to program the vpeTop registers using VPDMA.
 *  This feature will be useful for memory to memory operation of clients in
 *  which the client drivers have to switch between different context (multiple
 *  instance of mem-mem drivers).
 *  With this feature, the clients can form the configuration overlay one-time
 *  and submit this to VPDMA everytime when context changes. Thus saving
 *  valuable CPU in programming the VPS registers.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *
 *  \param handle Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \return       Returns 0 on success else returns error value.
 */
UInt32 VpsHal_vpeTopGetConfigOvlySize(VpsHal_Handle handle)
{
    UInt32 regOvlySize = 0;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    /* Return the value already got in init function */
    regOvlySize = ((VpsHal_VpeTopInfo *) handle)->regOvlySize;

    return (regOvlySize);
}

/**
 *  VpsHal_vpeTopCreateConfigOvly
 *  \brief Creates the VPE top register configuration
 *  overlay using VPDMA helper function.
 *
 *  This function does not initialize the overlay with VPE Top mux
 *  configuration. It is the responsibility of the client driver to configure
 *  the overlay by calling VpsHal_vpeTopSetConfig function before submitting
 *  the same to VPDMA for register configuration at runtime.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \param configOvlyPtr  Pointer to the overlay memory where the overlay is
 *                        formed. The memory for the overlay should be allocated
 *                        by client driver. This parameter should be non-NULL.
 *
 *  \return               Returns 0 on success else returns error value.
 */
Int32 VpsHal_vpeTopCreateConfigOvly(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    Int32 retVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != configOvlyPtr));

    /* Create the register overlay */
    retVal = VpsHal_vpdmaCreateRegOverlay(
        ((VpsHal_VpeTopInfo *) handle)->regOffset,
        VPE_TOP_CONFIG_OVLY_NUM_IDX,
        configOvlyPtr);

    return (retVal);
}

/**
 *  VpsHal_vpeTopSetConfig
 *  \brief Sets the VPE top configuration to either the
 *  actual mux registers or to the configuration overlay memory.
 *
 *  This function configures the VPE top registers. Depending on the value
 *  of configOvlyPtr parameter, the updating will happen to actual MMR or
 *  to configuration overlay memory.
 *  VpsHal_vpeTopInit and VpsHal_vpeTopOpen should be called prior to this.
 *  VPE top mux registers or configuration overlay memory are programmed
 *  according to the parameters passed.
 *
 *  \param handle          Valid handle returned by VpsHal_vpeTopOpen function.
 *
 *  \param config          Pointer to Vps_vpeTopConfig structure containing the
 *                         register configurations. This parameter should be
 *                         non-NULL.
 *
 *  \param configOvlyPtr   Pointer to the configuration overlay memory.
 *                         If this parameter is NULL, then the configuration is
 *                         written to the actual registers. Otherwise the
 *                         configuration is updated in the memory pointed
 *                         by the same at proper virtual offsets. This parameter
 *                         can be NULL depending on the intended usage.
 *
 *  \return                Returns 0 on success else returns error value.
 */
Int32 VpsHal_vpeTopSetConfig(VpsHal_Handle              handle,
                             const VpsHal_VpeTopConfig *config,
                             Ptr                        configOvlyPtr)
{
    Int32 retVal = BSP_SOK;
    VpsHal_VpeTopInfo *instObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != config));

    /* Get the register Overlay pointer */
    instObj = (VpsHal_VpeTopInfo *) handle;

    /* Set the mux values */
    VpsHal_vpeTopDisableAllMux(instObj, configOvlyPtr);
    VpsHal_vpeTopSetMux(
        instObj,
        VPSHAL_VPE_TOP_CSC_SRC,
        VPSHAL_VPE_TOP_CSC_MUX_SRC_DEI_SC,
        configOvlyPtr);
    VpsHal_vpeTopSetMux(
        instObj,
        VPSHAL_VPE_TOP_CHRDS0_SRC,
        VPSHAL_VPE_TOP_CHRDS0_MUX_SRC_DEI_SC,
        configOvlyPtr);

    /* Set RGB mux - Even YUV444 we should enable this as this is 24-bit
     * mode */
    if ((FVID2_DF_YUV444I == config->dataFmt) ||
        (FVID2_DF_RGB24_888 == config->dataFmt))
    {
        VpsHal_vpeTopSetMux(
            (VpsHal_Handle) instObj,
            VPSHAL_VPE_TOP_RGB_OUT,
            VPSHAL_VPE_TOP_RGB_OUT_RGB,
            configOvlyPtr);
    }
    else
    {
        VpsHal_vpeTopSetMux(
            instObj,
            VPSHAL_VPE_TOP_RGB_OUT,
            VPSHAL_VPE_TOP_RGB_OUT_YUV,
            configOvlyPtr);
    }

    /* Set CHRDS enable/disable mux */
    if ((Int32) TRUE == Fvid2_isDataFmtYuv420Sp(config->dataFmt))
    {
        VpsHal_vpeTopSetMux(
            instObj,
            VPSHAL_VPE_TOP_CHRDS0_BYPASS,
            (UInt32) FALSE,
            configOvlyPtr);
    }
    else
    {
        VpsHal_vpeTopSetMux(
            instObj,
            VPSHAL_VPE_TOP_CHRDS0_BYPASS,
            (UInt32) TRUE,
            configOvlyPtr);
    }

    /* Set 422SP enable/disable mux */
    if ((Int32) TRUE == Fvid2_isDataFmtYuv422Sp(config->dataFmt))
    {
        VpsHal_vpeTopSetMux(
            instObj,
            VPSHAL_VPE_TOP_422SP_EN,
            (UInt32) TRUE,
            configOvlyPtr);
    }
    else
    {
        VpsHal_vpeTopSetMux(
            instObj,
            VPSHAL_VPE_TOP_422SP_EN,
            (UInt32) FALSE,
            configOvlyPtr);
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopEnableAllModules
 *  \brief Enable/Disable all sub modules within VPE
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param enable       1: Enable all modules.
 *                      0: Disable all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopEnableAllModules(VpsHal_Handle handle,
                                    UInt32        enable,
                                    Ptr           configOvlyPtr)
{
    volatile UInt32 value    = 0x01031FFFU;
    UInt32          baseAddr = 0U;
    Int32           retVal   = BSP_SOK;

    GT_assert(VpsHalTrace, (NULL != handle));
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VpeTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VpsLib_platformIsTI814xFamilyBuild())
    {
        enable = (UInt32) (enable != 0);

        if (TRUE == enable)
        {
            HW_WR_REG32(baseAddr + VPE_CLKC_CLKEN, value);
        }
        else
        {
            /* TODO: Disable */
        }
    }
    else
    {
        retVal = VpsHal_vpeTopEnableModule(handle,
                                           VPSHAL_VPE_PRIM_DP,
                                           enable,
                                           configOvlyPtr);
        if (BSP_SOK == retVal)
        {
            retVal = VpsHal_vpeTopEnableModule(handle,
                                               VPSHAL_VPE_TOP_VPDMA,
                                               enable,
                                               configOvlyPtr);
        }

#if defined (PLATFORM_VIRTIO) || defined (PLATFORM_SIM)
        if (BSP_SOK == retVal)
        {
            /* Enable CLKC and reset path for sim */
            value = 0xFFFFFFFEU;
            HW_WR_REG32(baseAddr + VPE_CLKC_RST, value);
            /* BspOsal_sleep(1); */
            value = 0U;
            HW_WR_REG32(baseAddr + VPE_CLKC_RST, value);
            /* BspOsal_sleep(1); */
        }
#endif
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopResetAllModules
 *  \brief Reset/Unreset all sub modules within VPE
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param enable       1: Reset all modules.
 *                      0: Release reset for all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopResetAllModules(VpsHal_Handle handle,
                                   UInt32 enable, Ptr configOvlyPtr)
{
    Int32 retVal = BSP_SOK;

    enable = (UInt32) (enable != 0);
    retVal = VpsHal_vpeTopResetModule(handle,
                                      VPSHAL_VPE_PRIM_DP,
                                      enable,
                                      configOvlyPtr);
    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vpeTopResetModule(handle,
                                          VPSHAL_VPE_TOP_VPDMA,
                                          enable,
                                          configOvlyPtr);
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopEnableModule
 *  \brief Enable/Disable specified module within VPE
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param module       Module to reset/unreset.  #VpsHal_VpeTopModule
 *  \param enable       1: Enable module
 *                      0: Disable module
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopEnableModule(VpsHal_Handle handle,
                                UInt32        module,
                                UInt32        enable,
                                Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0U;

    GT_assert(VpsHalTrace, NULL != handle);

    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    enable = (UInt32) (enable != 0);

    switch (module)
    {
        case VPSHAL_VPE_PRIM_DP:
            HW_WR_FIELD32(
                baseAddr + VPE_CLKC_CLKEN,
                VPE_CLKC_CLKEN_PRIM_DP_EN,
                enable);
            break;

        case VPSHAL_VPE_TOP_VPDMA:
            HW_WR_FIELD32(
                baseAddr + VPE_CLKC_CLKEN,
                VPE_CLKC_CLKEN_VPDMA_EN,
                enable);
            break;

        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopResetModule
 *  \brief Reset/Unreset specified module within VPE
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param module       Module to reset/unreset. #VpsHal_VpeTopModule
 *  \param enable       1: Reset module
 *                      0: Release module reset
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopResetModule(VpsHal_Handle handle,
                               UInt32        module,
                               UInt32        enable,
                               Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0U;

    GT_assert(VpsHalTrace, NULL != handle);
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    switch (module)
    {
        case VPSHAL_VPE_PRIM_DP:
            HW_WR_FIELD32(
                baseAddr + VPE_CLKC_RST,
                VPE_CLKC_RST_PRIM_DP_RST,
                enable);
            break;

        case VPSHAL_VPE_TOP_VPDMA:
            HW_WR_FIELD32(
                baseAddr + VPE_CLKC_RST,
                VPE_CLKC_RST_VPDMA_RST,
                enable);
            break;

        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopDisableAllMux
 *  \brief Disable all muxes within VPE
 *
 *  \param handle       Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopDisableAllMux(VpsHal_Handle handle, Ptr configOvlyPtr)
{
    VpsHal_VpeTopInfo *instObj;
    UInt32 tempAddr;

    GT_assert(VpsHalTrace, NULL != handle);

    instObj = (VpsHal_VpeTopInfo *) handle;
    if (NULL == configOvlyPtr)
    {
        tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
        HW_WR_REG32(tempAddr, 0);
    }
    else
    {
        /* MISRA.PTR.ARITH */
        *((UInt32 *) configOvlyPtr +
          instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX]) = 0U;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_vpeTopSetMux
 *  \brief Set specified mux within VPE
 *
 *  \param handle         Valid handle returned by VpsHal_vpeTopOpen function.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *  \param mux            VPE Mux to control #VpsHal_VpeTopMux
 *  \param muxVal         Mux value to set #VpsHal_VpeTopMuxVal
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpeTopSetMux(VpsHal_Handle handle,
                          UInt32        mux,
                          UInt32        muxVal,
                          Ptr           configOvlyPtr)
{
    Int32  retVal = BSP_SOK;
    VpsHal_VpeTopInfo *instObj;
    UInt32 tempReg  = 0U;
    UInt32 tempAddr = 0U;

    GT_assert(VpsHalTrace, NULL != handle);

    instObj = (VpsHal_VpeTopInfo *) handle;

    if (NULL != configOvlyPtr)
    {
        /* MISRA.PTR.ARITH */
        tempReg = *((UInt32 *) configOvlyPtr +
                    instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX]);
    }

    switch (mux)
    {
        case VPSHAL_VPE_TOP_CSC_SRC:
            if (NULL == configOvlyPtr)
            {
                tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
                HW_WR_FIELD32(
                    tempAddr,
                    VPE_CLKC_DPS_CSC_SRC_SELECT,
                    muxVal);
            }
            else
            {
                HW_SET_FIELD32(tempReg, VPE_CLKC_DPS_CSC_SRC_SELECT, muxVal);

                /* MISRA.PTR.ARITH */
                *((UInt32 *) configOvlyPtr +
                  instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX])
                    = tempReg;
            }
            break;

        case VPSHAL_VPE_TOP_RGB_OUT:
            if (NULL == configOvlyPtr)
            {
                tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
                HW_WR_FIELD32(
                    tempAddr,
                    VPE_CLKC_DPS_RGB_OUT_SELECT,
                    muxVal);
            }
            else
            {
                HW_SET_FIELD32(tempReg, VPE_CLKC_DPS_RGB_OUT_SELECT, muxVal);

                /* MISRA.PTR.ARITH */
                *((UInt32 *) configOvlyPtr +
                  instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX])
                    = tempReg;
            }
            break;

        case VPSHAL_VPE_TOP_CHRDS0_SRC:
            if (NULL == configOvlyPtr)
            {
                tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
                HW_WR_FIELD32(
                    tempAddr,
                    VPE_CLKC_DPS_CHR_DS_SRC_SELECT,
                    muxVal);
            }
            else
            {
                HW_SET_FIELD32(tempReg, VPE_CLKC_DPS_CHR_DS_SRC_SELECT, muxVal);

                /* MISRA.PTR.ARITH */
                *((UInt32 *) configOvlyPtr +
                  instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX])
                    = tempReg;
            }
            break;

        case VPSHAL_VPE_TOP_CHRDS0_BYPASS:
            if (NULL == configOvlyPtr)
            {
                tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
                HW_WR_FIELD32(
                    tempAddr,
                    VPE_CLKC_DPS_CHR_DS_BYPASS,
                    muxVal);
            }
            else
            {
                HW_SET_FIELD32(tempReg, VPE_CLKC_DPS_CHR_DS_BYPASS, muxVal);

                /* MISRA.PTR.ARITH */
                *((UInt32 *) configOvlyPtr +
                  instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX])
                    = tempReg;
            }
            break;

        case VPSHAL_VPE_TOP_422SP_EN:
            if (NULL == configOvlyPtr)
            {
                tempAddr = instObj->baseAddr + (UInt32) VPE_CLKC_DPS;
                HW_WR_FIELD32(
                    tempAddr,
                    VPE_CLKC_DPS_COLOR_SEPARATE_422,
                    muxVal);
            }
            else
            {
                HW_SET_FIELD32(tempReg, VPE_CLKC_DPS_COLOR_SEPARATE_422, muxVal);

                /* MISRA.PTR.ARITH */
                *((UInt32 *) configOvlyPtr +
                  instObj->virtRegOffset[VPE_TOP_CONFIG_OVLY_CLKC_DPS_IDX])
                    = tempReg;
            }
            break;

        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;

    enable = (UInt32) (enable != 0);
    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPE_INTC_INTR0_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPE_INTC_INTR0_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR1_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR1_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
    else if (VPSHAL_VPDMA_INT2 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR2_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR2_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
    else if (VPSHAL_VPDMA_INT3 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR3_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR3_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
#endif
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;

    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPE_INTC_INTR0_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR1_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
    else if (VPSHAL_VPDMA_INT2 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR2_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
    else if (VPSHAL_VPDMA_INT3 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR3_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
#endif

    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    HW_WR_FIELD32(baseAddr + VPE_INTC_EOI,
                  VPE_INTC_EOI_EOI_VECTOR,
                  intrLine
                  );

    return (retVal);
}

/**
 *  VpsHal_vpeTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;

    enable = (UInt32) (enable != 0);
    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPE_INTC_INTR0_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPE_INTC_INTR0_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR1_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR1_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
    else if (VPSHAL_VPDMA_INT2 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR2_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR2_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
    else if (VPSHAL_VPDMA_INT3 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR3_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VPS_INTC_INTR3_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
#endif
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 *  VpsHal_vpeTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpeTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;

    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPE_INTC_INTR0_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR1_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
    else if (VPSHAL_VPDMA_INT2 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR2_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
    else if (VPSHAL_VPDMA_INT3 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VPS_INTC_INTR3_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
#endif
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    HW_WR_FIELD32(baseAddr + VPE_INTC_EOI, VPE_INTC_EOI_EOI_VECTOR, intrLine);

    return (retVal);
}

/**
 *  VpsHal_vpeTopGetInstInfo
 *  \brief Get VPE Handle from VPE Instance ID.
 *  Caller should ensure VPE TOP HAL init is complete.
 *
 *  \param vpeTopId         Valid vpeTopId of type #Vps_VpeInst
 *
 *  \return                 Valid VPE TOP Instance handle.
 *
 */
VpsHal_Handle VpsHal_vpeTopGetInstInfo(UInt32 vpeTopId)
{
    VpsHal_Handle retHandle = NULL;

    if (vpeTopId < VPSHAL_VPE_TOP_MAX_INST)
    {
        retHandle = (VpsHal_Handle) (&(vpeTopHalObj.topObj[vpeTopId]));
    }

    return (retHandle);
}

/**
 *  VpsHal_vpeTopGetInstInfo
 *  \brief Get VPE Handle from VPE Instance ID.
 *  Caller should ensure VPE TOP HAL init is complete.
 *
 *  \param vpeTopId         Valid vpeTopId of type #Vps_VpeInst
 *
 *  \return                 Valid VPE TOP Instance handle.
 *
 */
UInt32 VpsHal_vpeTopGetBaseAddress(VpsHal_Handle handle)
{
    UInt32 retVal;

    if (NULL == handle)
    {
        retVal = (UInt32) NULL;
    }
    else
    {
        retVal = ((VpsHal_VpeTopInfo *) (handle))->baseAddr;
    }

    return (retVal);
}

