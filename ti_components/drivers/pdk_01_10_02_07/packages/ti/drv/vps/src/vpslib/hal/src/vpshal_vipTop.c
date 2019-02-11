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
 *  \file vpshal_vipTop.c
 *
 *  \brief HAL implementation for VIP-TOP
 *  This file implements the HAL APIs of the VIP Clock and Reset control
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
#include <ti/csl/cslr_vip.h>
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
#include <ti/csl/cslr_vps.h>
#endif
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vipTop.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSHAL_VIP_TOP_ALL_MODULES  (VPSHAL_VIP_TOP_NUM_MODULES)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_VipTopInfo
 *  \brief Structure containing Instance Information for each VIP Instance.
 *         Primarily baseAddress for the VIP instance.
 */
typedef struct
{
    UInt32 halId;
    /**< Instance ID of VIP */
    UInt32 openCnt;
    /**< Number of handles opened */
    UInt32 baseAddr;
    /**< Base address of VIP TOP for current instance. */
} VpsHal_VipTopInfo;

/**
 *  struct VpsHal_VipTop
 *  \brief Handle structure for all instances of VIP TOP HAL
 */
typedef struct
{
    UInt32            numInst;
    /**< Num instances opened in HALInit */
    VpsHal_VipTopInfo topObj[VPSHAL_VIP_TOP_MAX_INST];
    /**< Instance list for maximum supported instances */
} VpsHal_VipTop;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * vipTopHalObj: VIP TOP HAL object containing all VIP TOP instances
 */
static VpsHal_VipTop vipTopHalObj;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_vipTopInit
 *  \brief VIP HAL init function.
 *  This function should be called before calling any of VIP HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms           Pointer to #VpsHal_VipTopInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_vipTopInit(UInt32                         numInst,
                        const VpsHal_VipTopInstParams *instPrms,
                        Ptr                            arg)
{
    UInt32 i;

    GT_assert(VpsHalTrace, instPrms != NULL);
    vipTopHalObj.numInst = numInst;

    for (i = 0; i < numInst; i++)
    {
        vipTopHalObj.topObj[i].halId    = instPrms[i].halId;
        vipTopHalObj.topObj[i].openCnt  = 0;
        vipTopHalObj.topObj[i].baseAddr = instPrms[i].baseAddr;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_vipTopDeInit
 *  \brief VIP HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         success    0
 *                  failure    error value
 *
 */
Int32 VpsHal_vipTopDeInit(Ptr arg)
{
    UInt32 i;

    for (i = 0; i < vipTopHalObj.numInst; i++)
    {
        GT_assert(VpsHalTrace, vipTopHalObj.topObj[i].openCnt == 0);
        vipTopHalObj.topObj[i].halId    = 0;
        vipTopHalObj.topObj[i].openCnt  = 0;
        vipTopHalObj.topObj[i].baseAddr = 0;
    }
    vipTopHalObj.numInst = 0;

    return (BSP_SOK);
}

/**
 *  VpsHal_vipTopOpen
 *  \brief Returns the handle to the requested Vip instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the VIP HAL
 *  configuration APIs.
 *
 *  VpsHal_vipInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openParams    VpsHal_VipTopOpenParams
 *
 *  \return              success     VIP instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vipTopOpen(const VpsHal_VipTopOpenParams *openParams)
{
    VpsHal_Handle      vipTopHandle = NULL;
    VpsHal_VipTopInfo *vipTopInfo   = NULL;
    UInt32 halId, i;

    halId = openParams->halId;
    for (i = 0U; i < vipTopHalObj.numInst; i++)
    {
        if (vipTopHalObj.topObj[i].halId == halId)
        {
            vipTopInfo = &(vipTopHalObj.topObj[i]);
            vipTopInfo->openCnt++;
            vipTopHandle = (VpsHal_Handle) (vipTopInfo);
            break;
        }
    }

    return (vipTopHandle);
}

/**
 *  VpsHal_vipClose
 *  \brief Closes specified instance of Vip Top HAL
 *  VpsHal_vipInit and Vip_open should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vipTopOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_EFAIL;
    VpsHal_VipTopInfo *topInfo;

    GT_assert(VpsHalTrace, NULL != handle);
    topInfo = (VpsHal_VipTopInfo *) handle;
    if (0 != topInfo->openCnt)
    {
        topInfo->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopEnableAllModules
 *  \brief Enable/Disable all sub modules within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param enable         1: Enable all modules.
 *                        0: Disable all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopEnableAllModules(VpsHal_Handle handle,
                                    UInt32        enable,
                                    Ptr           configOvlyPtr)
{
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    volatile UInt32 value    = 0x01031FFFU;
    UInt32          baseAddr = 0U;

    GT_assert(VpsHalTrace, (NULL != handle));
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    enable = (UInt32) (enable != 0);

    if (TRUE == enable)
    {
        HW_WR_REG32(baseAddr + VIP_CLKC_CLKEN, value);
        HW_WR_REG32(baseAddr + VIP_CLKC_RST, 0);
    }
    else
    {
        /* TODO: Disable */
    }

    return (BSP_SOK);
#else
    Int32           retVal;

    GT_assert(VpsHalTrace, (NULL != handle));
    enable = (UInt32) (enable != 0U);

    retVal = VpsHal_vipTopEnableModule(handle,
                                       VPSHAL_VIP_TOP_S0_DP,
                                       enable,
                                       configOvlyPtr);
    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vipTopEnableModule(handle,
                                           VPSHAL_VIP_TOP_S1_DP,
                                           enable,
                                           configOvlyPtr);
    }

    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vipTopEnableModule(handle,
                                           VPSHAL_VIP_TOP_VPDMA,
                                           enable,
                                           configOvlyPtr);
    }

    return (retVal);
#endif
}

/**
 *  VpsHal_vipTopResetAllModules
 *  \brief Reset/Unreset all sub modules within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param enable         1: Reset all modules.
 *                        0: Release reset for all modules.
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopResetAllModules(VpsHal_Handle handle,
                                   UInt32        enable,
                                   Ptr           configOvlyPtr)
{
    Int32 retVal;

    enable = (UInt32) (enable != 0);
    retVal = VpsHal_vipTopResetModule(
        handle,
        VPSHAL_VIP_TOP_ALL_MODULES,
        enable,
        configOvlyPtr);

    return (retVal);
}

/**
 *  VpsHal_vipTopEnableModule
 *  \brief Enable/Disable specified module within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param module         Module to reset/unreset.  #VpsHal_VipTopModule
 *  \param enable         1: Enable module
 *                        0: Disable module
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopEnableModule(VpsHal_Handle handle,
                                UInt32        module,
                                UInt32        enable,
                                Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;

    GT_assert(VpsHalTrace, NULL != handle);
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    enable = (UInt32) (enable != 0);

    switch (module)
    {
        case VPSHAL_VIP_TOP_S0_DP:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_CLKEN,
                VIP_CLKC_CLKEN_S0_DP_EN,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_DP:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_CLKEN,
                VIP_CLKC_CLKEN_S1_DP_EN,
                enable);
            break;

        case VPSHAL_VIP_TOP_VPDMA:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_CLKEN,
                VIP_CLKC_CLKEN_VPDMA_EN,
                enable);
            break;

        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopResetModule
 *  \brief Reset/Unreset specified module within VIP
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param module         Module to reset/unreset. #VpsHal_VipTopModule
 *  \param enable         1: Reset module
 *                        0: Release module reset
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopResetModule(VpsHal_Handle handle,
                               UInt32        module,
                               UInt32        enable,
                               Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;

    GT_assert(VpsHalTrace, NULL != handle);
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    switch (module)
    {
        case VPSHAL_VIP_TOP_S0_DP:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_DP_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_DP:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_DP_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_VPDMA:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_VPDMA_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S0_PARSER:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_PARSER_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_PARSER:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_PARSER_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S0_CSC:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_CSC_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_CSC:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_CSC_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S0_SC:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_SC_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_SC:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_SC_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S0_CHRDS0:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_CHR_DS_0_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_CHRDS0:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_CHR_DS_0_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S0_CHRDS1:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S0_CHR_DS_1_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_S1_CHRDS1:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_S1_CHR_DS_1_RST,
                enable);
            break;

        case VPSHAL_VIP_TOP_ALL_MODULES:
            HW_WR_FIELD32(
                baseAddr + VIP_CLKC_RST,
                VIP_CLKC_RST_MAIN_RST,
                enable);
            break;

        default:
            retVal = BSP_EFAIL;
            break;
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopDisableAllMux
 *  \brief Disable all muxes within given VIP slice
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param slice          VIP Slice to control #Vps_VipSliceInst
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopDisableAllMux(VpsHal_Handle handle,
                                 UInt32        slice,
                                 Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    UInt32 regAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_S0 == slice)
    {
        regAddr = baseAddr + VIP_CLKC_S0_DPS;
    }
    else if (VPSHAL_VIP_S1 == slice)
    {
        regAddr = baseAddr + VIP_CLKC_S1_DPS;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_REG32(regAddr, 0);
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopSetMux
 *  \brief Set specified mux within given VIP slice
 *
 *  \param handle         Valid handle returned by VpsHal_vipTopOpen function.
 *  \param slice          VIP Slice to control #Vps_VipSliceInst
 *  \param mux            VIP Mux to control #VpsHal_VipTopMux
 *  \param muxVal         Mux value to set #VpsHal_VipTopMuxVal
 *  \param configOvlyPtr  Register Overlay address. Ignored if 0.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipTopSetMux(VpsHal_Handle handle,
                          UInt32        slice,
                          UInt32        mux,
                          UInt32        muxVal,
                          Ptr           configOvlyPtr)
{
    Int32  retVal            = BSP_SOK;
    UInt32 baseAddr          = 0;
    UInt32 multipleSelectReq = 0U;
    UInt32 regAddr, regVal;

    GT_assert(VpsHalTrace, NULL != handle);
    if (NULL == configOvlyPtr)
    {
        baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_S0 == slice)
    {
        regAddr = baseAddr + VIP_CLKC_S0_DPS;
    }
    else if (VPSHAL_VIP_S1 == slice)
    {
        regAddr = baseAddr + VIP_CLKC_S1_DPS;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        regVal = 0;
        switch (mux)
        {
            case VPSHAL_VIP_TOP_CSC_SRC:
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_CSC_SRC_SELECT,
                               muxVal);
                break;

            case VPSHAL_VIP_TOP_SC_SRC:
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_SC_SRC_SELECT, muxVal);
                break;

            case VPSHAL_VIP_TOP_RGB_SRC:
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_RGB_SRC_SELECT,
                               muxVal);
                break;

            case VPSHAL_VIP_TOP_RGB_OUT_LO:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_RGB_OUT_LO_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_RGB_OUT_HI:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_RGB_OUT_HI_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_CHRDS0_SRC:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_0_SRC_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_CHRDS1_SRC:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_1_SRC_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_MULTI_CH:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_MULTI_CHANNEL_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_CHRDS0_BYPASS:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_0_BYPASS,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_CHRDS1_BYPASS:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_1_BYPASS,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_TESTPORT_A:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_TESTPORT_A_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_TESTPORT_B:
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_TESTPORT_B_SELECT,
                    muxVal);
                break;

            case VPSHAL_VIP_TOP_RGB_OUT:
                multipleSelectReq = 1U;

                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_RGB_OUT_HI_SELECT,
                    ((muxVal >> 1) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_RGB_OUT_HI);
                HW_WR_REG32(regAddr, regVal);

                regVal = 0;
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_RGB_SRC_SELECT,
                               ((muxVal >> 0) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_RGB_SRC);
                HW_WR_REG32(regAddr, regVal);
                break;

            case VPSHAL_VIP_TOP_UV_UP:
                multipleSelectReq = 1U;
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_RGB_OUT_HI_SELECT,
                    ((muxVal >> 2) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_RGB_OUT_HI);
                HW_WR_REG32(regAddr, regVal);

                regVal = 0;
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_0_BYPASS,
                    ((muxVal >> 1) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_CHRDS0_BYPASS);
                HW_WR_REG32(regAddr, regVal);

                regVal = 0;
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_CHR_DS_1_BYPASS,
                    ((muxVal >> 0) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_CHRDS1_BYPASS);
                HW_WR_REG32(regAddr, regVal);
                break;

            case VPSHAL_VIP_TOP_UV_LO:
                multipleSelectReq = 1U;
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_RGB_OUT_LO_SELECT,
                    ((muxVal >> 1) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_RGB_OUT_LO);
                HW_WR_REG32(regAddr, regVal);

                regVal = 0;
                HW_SET_FIELD32(
                    regVal,
                    VIP_CLKC_S0_DPS_S0_MULTI_CHANNEL_SELECT,
                    ((muxVal >> 0) & 0x1U));
                HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT,
                               VPSHAL_VIP_TOP_MULTI_CH);
                HW_WR_REG32(regAddr, regVal);
                break;

            default:
                multipleSelectReq = 1U;
                retVal = BSP_EFAIL;
                break;
        }

        if (0U == multipleSelectReq)
        {
            HW_SET_FIELD32(regVal, VIP_CLKC_S0_DPS_S0_DATAPATH_SELECT, mux);
            HW_WR_REG32(regAddr, regVal);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;

    enable = (UInt32) (enable != 0);
    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VIP_INTC_INTR0_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VIP_INTC_INTR0_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VIP_INTC_INTR1_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VIP_INTC_INTR1_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    else if (VPSHAL_VPDMA_INT2 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VPS_INTC_INTR2_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VPS_INTC_INTR2_ENA_CLR0,
                ((UInt32) 1U << (listNum * 2U)));
        }
    }
    else if (VPSHAL_VPDMA_INT3 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VPS_INTC_INTR3_ENA_SET0,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + (UInt32) VPS_INTC_INTR3_ENA_CLR0,
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
 *  VpsHal_vipTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;

    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VIP_INTC_INTR0_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VIP_INTC_INTR1_STATUS0,
            ((UInt32) 1U << (listNum * 2U)));
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
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

    HW_WR_FIELD32(baseAddr + VIP_INTC_EOI, VIP_INTC_EOI_EOI_VECTOR, intrLine);

    return (retVal);
}

/**
 *  VpsHal_vipTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;

    enable = (UInt32) (enable != 0);
    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VIP_INTC_INTR0_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VIP_INTC_INTR0_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        if (0U != enable)
        {
            HW_WR_REG32(
                baseAddr + VIP_INTC_INTR1_ENA_SET0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else
        {
            HW_WR_REG32(
                baseAddr + VIP_INTC_INTR1_ENA_CLR0,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
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
 *  VpsHal_vipTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vipTopOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, NULL != handle);
    baseAddr = ((VpsHal_VipTopInfo *) handle)->baseAddr;

    if (VPSHAL_VPDMA_INT0 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VIP_INTC_INTR0_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
    else if (VPSHAL_VPDMA_INT1 == intrLine)
    {
        HW_WR_REG32(
            baseAddr + VIP_INTC_INTR1_STATUS0,
            ((UInt32) 1U << ((listNum * 2U) + 1U)));
    }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
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

    HW_WR_FIELD32(baseAddr + VIP_INTC_EOI, VIP_INTC_EOI_EOI_VECTOR, intrLine);

    return (retVal);
}

/**
 *  VpsHal_vipTopGetInstInfo
 *  \brief Get VIP Handle from VIP Instance ID.
 *  Caller should ensure VIP TOP HAL init is complete.
 *
 *  \param vipTopId         Valid vipTopId of type #Vps_VipInst
 *
 *  \return                 Valid VIP TOP Instance handle.
 *
 */
VpsHal_Handle VpsHal_vipTopGetInstInfo(UInt32 vipTopId)
{
    VpsHal_Handle retVal = NULL;
    UInt32        i;

    if (vipTopId >= VPSHAL_VIP_TOP_MAX_INST)
    {
        retVal = NULL;
    }
    else
    {
        for (i = 0U; i < vipTopHalObj.numInst; i++)
        {
            if (vipTopHalObj.topObj[i].halId == vipTopId)
            {
                retVal = (VpsHal_Handle) (&(vipTopHalObj.topObj[i]));
                break;
            }
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipTopGetBaseAddress
 *  \brief Get VIP Base Address from VIP Instance ID.
 *  Caller should ensure VIP TOP HAL init is complete.
 *
 *  \param vipTopId         Valid vipTopId of type #Vps_VipInst
 *
 *  \return                 Valid VIP TOP Instance handle.
 *
 */
UInt32 VpsHal_vipTopGetBaseAddress(VpsHal_Handle handle)
{
    UInt32 retVal = 0;

    if (NULL != handle)
    {
        retVal = ((VpsHal_VipTopInfo *) handle)->baseAddr;
    }

    return (retVal);
}

