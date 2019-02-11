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
 *  \file vpshal_vipPort.c
 *
 *  \brief HAL implementation for VIP Parser
 *  This file implements the HAL APIs of the VIP Parsers and Ports.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_vip_parser.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_vipPort.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vipTop.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  enum VpsHal_VipParserIntfMode
 *  \brief Enum for Input Interface Mode
 */
typedef enum
{
    VPSHAL_VIP_PORT_INTF_MODE_24B = 0,
    /**< 24b data interface. Uses Port A settings */

    VPSHAL_VIP_PORT_INTF_MODE_16B,
    /**< 16b data interface. Uses Port A settings */

    VPSHAL_VIP_PORT_INTF_MODE_8B
    /**< Dual independent 8b data interface.Uses independent Port A and Port B
     * settings
     */
} VpsHal_VipParserIntfMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsHal_VipPortInfo
 *  \brief Structure containing Instance Information for each VIP Port
 *         Primarily baseAddress and portId.
 */
typedef struct
{
    UInt32 halId;
    /**< Instance ID of VIP */

    UInt32 instId;
    /**< Vip Instance ID: #Vps_VipInst */

    UInt32 sliceId;
    /**< Slice ID within given instance: #Vps_VipSliceInst */

    UInt32 portId;
    /**< Port ID within given slice: #VpsHal_VipPortInst */

    UInt32 openCnt;
    /**< Number of handles opened */

    UInt32 baseAddr;
    /**< Base address of VIP PORT for current instance. */
} VpsHal_VipPortInfo;

/**
 *  struct VpsHal_VipPort
 *  \brief Handle structure for all instances of VIP Ports
 */
typedef struct
{
    UInt32             numInst;
    /**< Num instances opened in HALInit */

    VpsHal_VipPortInfo portObj[VPSHAL_VIP_PORT_MAX_INST];
    /**< Instance list for maximum supported instances */
} VpsHal_VipPort;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 * vipPortHalObj: VIP PORT HAL object containing all VIP Port instances
 */
static VpsHal_VipPort vipPortHalObj;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */
/**
 *  VpsHal_vipPortSetIntfCfg
 *  \brief Sets the interface config: Primarily PORT_X_MAIN register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen().
 *  \param  intfCfg           Pointer to #Vps_VipPortIntfConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetIntfCfg(VpsHal_Handle                handle,
                               const Vps_VipPortIntfConfig *intfCfg,
                               Ptr                          configOvlyPtr);

/**
 *  VpsHal_vipPortSetSyncType
 *  \brief Sets the sync type in PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen
 *  \param  syncType          Sync type as per #Vps_VipSyncType
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetSyncType(VpsHal_Handle   handle,
                                Vps_VipSyncType syncType,
                                Ptr             configOvlyPtr);

/**
 *  VpsHal_vipPortSetDisCfg
 *  \brief Sets the discrete sync specific fields.
 *         Primarily PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen().
 *  \param  disCfg            Pointer to #Vps_VipPortDisConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetDisCfg(VpsHal_Handle               handle,
                              const Vps_VipPortDisConfig *disCfg,
                              Ptr                         configOvlyPtr);

/**
 *  VpsHal_vipPortSetEmbCfg
 *  \brief Sets the embedded sync specific fields.
 *         Primarily PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen().
 *  \param  disCfg            Pointer to #Vps_VipPortEmbConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetEmbCfg(VpsHal_Handle               handle,
                              const Vps_VipPortEmbConfig *embCfg,
                              Ptr                         configOvlyPtr);

/**
 *  VpsHal_vipPortSetComCfg
 *  \brief Sets the discrete sync specific fields.
 *         Primarily PORT_X and XTRA_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortComConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetComCfg(VpsHal_Handle               handle,
                              const Vps_VipPortComConfig *comCfg,
                              Ptr                         configOvlyPtr);

/**
 *  VpsHal_vipPortSetAncCropCfg
 *  \brief Sets the ancillary cropping parameters.
 *         Primarily XTRA2_PORT_X and XTRA3_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortCropConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetAncCropCfg(VpsHal_Handle                handle,
                                  const Vps_VipPortCropConfig *ancCfg,
                                  Ptr                          configOvlyPtr);

/**
 *  VpsHal_vipPortSetActCropCfg
 *  \brief Sets the active data cropping parameters.
 *         Primarily XTRA4_PORT_X and XTRA5_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortCropConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetActCropCfg(VpsHal_Handle                handle,
                                  const Vps_VipPortCropConfig *actCfg,
                                  Ptr                          configOvlyPtr);

/**
 *  VpsHal_vipPortDisableAncCrop
 *  \brief Disable ancillary cropping.
 *         Primarily use XTRA2_PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortDisableAncCrop(VpsHal_Handle handle,
                                   Ptr           configOvlyPtr);

/**
 *  VpsHal_vipPortDisableActCrop
 *  \brief Disable active data cropping.
 *         Primarily use XTRA4_PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortDisableActCrop(VpsHal_Handle handle,
                                   Ptr           configOvlyPtr);

/**
 *  VpsHal_vipClkEn
 *  \brief Internal function to call VIP Slice clk enable/disable by
 *  selecting the appropriate clock control module.
 */
static void VpsHal_vipClkEn(VpsHal_Handle handle, UInt32 enable);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_vipPortInit
 *  \brief VIP PORT HAL init function.
 *  This function should be called before calling any of VIP PORT HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms           Pointer to #VpsHal_VipPortInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_vipPortInit(UInt32                          numInst,
                         const VpsHal_VipPortInstParams *instPrms,
                         Ptr                             arg)
{
    UInt32 i;

    GT_assert(VpsHalTrace, instPrms != NULL);

    vipPortHalObj.numInst = numInst;

    for (i = 0; i < numInst; i++)
    {
        vipPortHalObj.portObj[i].halId  = instPrms[i].halId;
        vipPortHalObj.portObj[i].instId =
            instPrms[i].halId / (VPSHAL_NUM_VIP_SLICES * VPSHAL_NUM_VIP_PORTS);
        vipPortHalObj.portObj[i].sliceId =
            (instPrms[i].halId % (VPSHAL_NUM_VIP_SLICES * VPSHAL_NUM_VIP_PORTS))
            / VPSHAL_NUM_VIP_PORTS;
        vipPortHalObj.portObj[i].portId =
            (instPrms[i].halId % VPSHAL_NUM_VIP_PORTS);
        vipPortHalObj.portObj[i].openCnt  = 0;
        vipPortHalObj.portObj[i].baseAddr = instPrms[i].baseAddr;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_vipPortDeInit
 *  \brief VIP PORT HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         success    0
 *                  failure    error value
 *
 */
Int32 VpsHal_vipPortDeInit(Ptr arg)
{
    UInt32 i;

    for (i = 0; i < vipPortHalObj.numInst; i++)
    {
        GT_assert(VpsHalTrace, vipPortHalObj.portObj[i].openCnt == 0);
        vipPortHalObj.portObj[i].halId    = 0;
        vipPortHalObj.portObj[i].instId   = 0;
        vipPortHalObj.portObj[i].sliceId  = 0;
        vipPortHalObj.portObj[i].portId   = 0;
        vipPortHalObj.portObj[i].openCnt  = 0;
        vipPortHalObj.portObj[i].baseAddr = 0;
    }

    vipPortHalObj.numInst = 0;

    return (BSP_SOK);
}

/**
 *  VpsHal_vipPortOpen
 *  \brief Returns the handle to the requested Vip Port instance.
 *  It is allowed to open only one handle for each vip Instance.
 *
 *  This function should be called prior to calling any of the VIP PORT HAL
 *  configuration APIs.
 *
 *  VpsHal_vipPortInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms     Identify port using #VpsHal_VipPortId
 *
 *  \return              success     VIP PORT handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vipPortOpen(const VpsHal_VipPortOpenParams *openPrms)
{
    VpsHal_Handle       portHandle = NULL;
    VpsHal_VipPortInfo *portInfo   = NULL;
    UInt32 i;

    GT_assert(VpsHalTrace, openPrms != 0);
    GT_assert(VpsHalTrace, vipPortHalObj.numInst != 0);
    GT_assert(VpsHalTrace, openPrms->halId < VPSHAL_VIP_PORT_INST_ID_MAX);

    for (i = 0; i < vipPortHalObj.numInst; i++)
    {
        if (vipPortHalObj.portObj[i].halId == openPrms->halId)
        {
            portInfo = &(vipPortHalObj.portObj[i]);
            VpsHal_vipClkEn((VpsHal_Handle) portInfo, (UInt32) TRUE);
            break;
        }
    }

    if ((portInfo != NULL) && (0 == portInfo->openCnt))
    {
        portInfo->openCnt++;
        portHandle = (VpsHal_Handle) portInfo;
    }

    return (portHandle);
}

/**
 *  VpsHal_vipClose
 *  \brief Closes specified instance of Vip Port HAL
 *  VpsHal_vipPortInit and VpsHal_vipPortOpen should be called prior to this.
 *
 *  \param handle       Valid handle returned by VpsHal_vipPortOpen()
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vipPortClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_SOK;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;
    GT_assert(VpsHalTrace, vipPortHalObj.numInst != 0);

    if (0 == portInfo->openCnt)
    {
        retVal = BSP_EFAIL;
    }
    else
    {
        portInfo->openCnt--;
        if (0 == portInfo->openCnt)
        {
            VpsHal_vipClkEn((VpsHal_Handle) portInfo, (UInt32) FALSE);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetCfg
 *  \brief Sets the entire port configuration
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen
 *                            function
 *  \param  portCfg           Pointer to #Vps_VipPortConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetCfg(VpsHal_Handle            handle,
                           const Vps_VipPortConfig *portCfg,
                           Ptr                      configOvlyPtr)
{
    Int32               retVal = BSP_SOK;
    Vps_VipSyncType     syncType;
    UInt32              baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != portCfg);

    /*Initialize the register to 0 befor configuring*/
    portInfo = (VpsHal_VipPortInfo *) handle;
    baseAddr = portInfo->baseAddr;

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_PORT_A, 0x0U);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_PORT_B, 0x0U);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vipPortSetIntfCfg(handle, &portCfg->intfCfg,
                                          configOvlyPtr);
    }

    if (BSP_SOK == retVal)
    {
        syncType = (Vps_VipSyncType) portCfg->syncType;
        if ((VPS_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_2X_422_YUV == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_4X_422_YUV == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_LINE_YUV == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_SINGLE_RGB_OR_444_YUV == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_2X_RGB == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_4X_RGB == syncType) ||
            (VPS_VIP_SYNC_TYPE_EMB_LINE_RGB == syncType))
        {
            VpsHal_vipPortSetSyncType(handle, syncType, configOvlyPtr);
            retVal = VpsHal_vipPortSetEmbCfg(
                handle,
                &portCfg->embCfg,
                configOvlyPtr);
        }
        else if ((VPS_VIP_SYNC_TYPE_DIS_SINGLE_YUV == syncType) ||
                 (VPS_VIP_SYNC_TYPE_DIS_SINGLE_8B_RGB == syncType) ||
                 (VPS_VIP_SYNC_TYPE_DIS_SINGLE_24B_RGB == syncType))
        {
            VpsHal_vipPortSetSyncType(handle, syncType, configOvlyPtr);
            retVal = VpsHal_vipPortSetDisCfg(
                handle,
                &portCfg->disCfg,
                configOvlyPtr);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_vipPortSetComCfg(
            handle,
            &portCfg->comCfg,
            configOvlyPtr);
    }

    if (BSP_SOK == retVal)
    {
        if (TRUE == portCfg->ancCropEnable)
        {
            retVal = VpsHal_vipPortSetAncCropCfg(
                handle,
                &portCfg->ancCropCfg,
                configOvlyPtr);
        }
        else
        {
            retVal = VpsHal_vipPortDisableAncCrop(handle, configOvlyPtr);
        }
    }

    if (BSP_SOK == retVal)
    {
        if (TRUE == portCfg->actCropEnable)
        {
            retVal = VpsHal_vipPortSetActCropCfg(
                handle,
                &portCfg->actCropCfg,
                configOvlyPtr);
        }
        else
        {
            retVal = VpsHal_vipPortDisableActCrop(handle, configOvlyPtr);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetIntfCfg
 *  \brief Sets the interface config: Primarily PORT_X_MAIN register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  intfCfg           Pointer to #Vps_VipPortIntfConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetIntfCfg(VpsHal_Handle                handle,
                               const Vps_VipPortIntfConfig *intfCfg,
                               Ptr                          configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    UInt32 intfWidth;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != intfCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if ((VPSHAL_VIP_PORT_B == portInfo->portId) &&
        (FVID2_VIFW_8BIT != intfCfg->intfWidth))
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        switch (intfCfg->intfWidth)
        {
            case FVID2_VIFW_8BIT:
                intfWidth = VPSHAL_VIP_PORT_INTF_MODE_8B;
                break;

            case FVID2_VIFW_10BIT:
            case FVID2_VIFW_16BIT:
                intfWidth = VPSHAL_VIP_PORT_INTF_MODE_16B;
                break;

            case FVID2_VIFW_20BIT:
            case FVID2_VIFW_24BIT:
                intfWidth = VPSHAL_VIP_PORT_INTF_MODE_24B;
                break;

            case FVID2_VIFW_30BIT:
                retVal = BSP_EFAIL;
                break;

            default:
                retVal = BSP_EFAIL;
                break;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_FIELD32(
            baseAddr + VIP_MAIN,
            (UInt32) VIP_MAIN_CLIP_ACTIVE,
            intfCfg->clipActive);
        HW_WR_FIELD32(
            baseAddr + VIP_MAIN,
            (UInt32) VIP_MAIN_CLIP_BLNK,
            intfCfg->clipBlank);
        HW_WR_FIELD32(
            baseAddr + VIP_MAIN,
            (UInt32) VIP_MAIN_DATA_INTERFACE_MODE,
            intfWidth);
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetSyncType
 *  \brief Sets the sync type in PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen
 *  \param  syncType          Sync type as per #Vps_VipSyncType
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetSyncType(VpsHal_Handle   handle,
                                Vps_VipSyncType syncType,
                                Ptr             configOvlyPtr)
{
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_A, VIP_PORT_A_SYNC_TYPE, syncType);
    }

    if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_B, VIP_PORT_B_SYNC_TYPE, syncType);
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_vipPortSetDisCfg
 *  \brief Sets the discrete sync specific fields.
 *         Primarily PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  disCfg            Pointer to #Vps_VipPortDisConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetDisCfg(VpsHal_Handle               handle,
                              const Vps_VipPortDisConfig *disCfg,
                              Ptr                         configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != disCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_A);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_B);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_FID_SKEW_POSTCOUNT,
            disCfg->fidSkewPostCnt);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_FID_SKEW_PRECOUNT,
            disCfg->fidSkewPreCnt);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_USE_ACTVID_HSYNC_N,
            disCfg->lineCaptureStyle);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_FID_DETECT_MODE,
            disCfg->fidDetectMode);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_ACTVID_POLARITY,
            disCfg->actvidPol);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_VSYNC_POLARITY,
            disCfg->vsyncPol);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_HSYNC_POLARITY,
            disCfg->hsyncPol);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_DISCRETE_BASIC_MODE,
            disCfg->discreteBasicMode);

        if (VPSHAL_VIP_PORT_A == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_A, regVal);
        }
        else if (VPSHAL_VIP_PORT_B == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_B, regVal);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetEmbCfg
 *  \brief Sets the embedded sync specific fields.
 *         Primarily PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  disCfg            Pointer to #Vps_VipPortEmbConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetEmbCfg(VpsHal_Handle               handle,
                              const Vps_VipPortEmbConfig *embCfg,
                              Ptr                         configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != embCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_A);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_B);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_ENABLE_ANALYZER_FVH_ERR_CORRECTION,
            embCfg->errCorrEnable);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_ANALYZER_2X4X_SRCNUM_POS,
            embCfg->srcNumPos);

        if (VPSHAL_VIP_PORT_A == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_A, regVal);
        }
        else if (VPSHAL_VIP_PORT_B == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_B, regVal);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetComCfg
 *  \brief Sets the discrete sync specific fields.
 *         Primarily PORT_X and XTRA_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortComConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetComCfg(VpsHal_Handle               handle,
                              const Vps_VipPortComConfig *comCfg,
                              Ptr                         configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != comCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_A);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_B);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_CTRL_CHAN_SEL,
            comCfg->ctrlChanSel);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_PIXCLK_EDGE_POLARITY,
            comCfg->pixClkEdgePol);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_FID_POLARITY,
            comCfg->invertFidPol);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_ENABLE,
            comCfg->enablePort);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_CLR_ASYNC_RD_FIFO,
            comCfg->clrAsyncFifoRd);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_PORT_A_CLR_ASYNC_WR_FIFO,
            comCfg->clrAsyncFifoWr);

        if (VPSHAL_VIP_PORT_A == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_A, regVal);
        }
        else if (VPSHAL_VIP_PORT_B == portInfo->portId)
        {
            HW_WR_REG32(baseAddr + VIP_PORT_B, regVal);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        if (VPSHAL_VIP_PORT_A == portInfo->portId)
        {
            regVal = HW_RD_REG32(baseAddr + VIP_XTRA_PORT_A);
        }
        else if (VPSHAL_VIP_PORT_B == portInfo->portId)
        {
            regVal = HW_RD_REG32(baseAddr + VIP_XTRA_PORT_B);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_XTRA_PORT_A_ANC_CHAN_SEL_8B,
            comCfg->ancChSel8b);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_XTRA_PORT_A_SRC0_NUMLINES,
            comCfg->expectedNumLines);
        HW_SET_FIELD32(
            regVal,
            (UInt32) VIP_XTRA_PORT_A_SRC0_NUMPIX,
            comCfg->expectedNumPix);

        if (VPSHAL_VIP_PORT_A == portInfo->portId)
        {
            HW_SET_FIELD32(
                regVal,
                (UInt32) VIP_XTRA_PORT_A_REPACK_SEL,
                comCfg->repackerMode);

            HW_WR_REG32(baseAddr +
                        (UInt32) VIP_XTRA_PORT_A,
                        regVal);
        }
        else if (VPSHAL_VIP_PORT_B == portInfo->portId)
        {
            HW_WR_REG32(baseAddr +
                        (UInt32) VIP_XTRA_PORT_B,
                        regVal);
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetAncCropCfg
 *  \brief Sets the ancillary cropping parameters.
 *         Primarily XTRA2_PORT_X and XTRA3_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortCropConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetAncCropCfg(VpsHal_Handle                handle,
                                  const Vps_VipPortCropConfig *ancCfg,
                                  Ptr                          configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    UInt32 regVal1, regVal2;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != ancCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    regVal1 = 0;
    HW_SET_FIELD32(regVal1, VIP_ANC_CROP_HORZ_PORT_A_ANC_BYPASS_N,
                   (UInt32) TRUE);
    HW_SET_FIELD32(
        regVal1,
        VIP_ANC_CROP_HORZ_PORT_A_ANC_TARGET_SRCNUM,
        (UInt32) ancCfg->srcNum);
    HW_SET_FIELD32(
        regVal1,
        VIP_ANC_CROP_HORZ_PORT_A_ANC_SKIP_NUMPIX,
        (UInt32) ancCfg->cropCfg.cropStartX);
    HW_SET_FIELD32(
        regVal1,
        VIP_ANC_CROP_HORZ_PORT_A_ANC_USE_NUMPIX,
        (UInt32) ancCfg->cropCfg.cropWidth);

    regVal2 = 0;
    HW_SET_FIELD32(
        regVal2,
        VIP_ANC_CROP_VERT_PORT_A_ANC_SKIP_NUMLINES,
        (UInt32) ancCfg->cropCfg.cropStartY);
    HW_SET_FIELD32(
        regVal2,
        VIP_ANC_CROP_VERT_PORT_A_ANC_USE_NUMLINES,
        (UInt32) ancCfg->cropCfg.cropHeight);

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_ANC_CROP_HORZ_PORT_A, regVal1);
        HW_WR_REG32(baseAddr + VIP_ANC_CROP_VERT_PORT_A, regVal2);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_ANC_CROP_HORZ_PORT_B, regVal1);
        HW_WR_REG32(baseAddr + VIP_ANC_CROP_VERT_PORT_A, regVal2);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortSetActCropCfg
 *  \brief Sets the active data cropping parameters.
 *         Primarily XTRA4_PORT_X and XTRA5_PORT_X registers
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  comCfg            Pointer to #Vps_VipPortCropConfig structure.
 *                            This parameter should be non-NULL.
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortSetActCropCfg(VpsHal_Handle                handle,
                                  const Vps_VipPortCropConfig *actCfg,
                                  Ptr                          configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    UInt32 regVal1, regVal2;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != actCfg);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    regVal1 = 0;
    HW_SET_FIELD32(regVal1, (UInt32) VIP_CROP_HORZ_PORT_A_ACT_BYPASS_N, 1U);
    HW_SET_FIELD32(
        regVal1,
        (UInt32) VIP_CROP_HORZ_PORT_A_ACT_TARGET_SRCNUM,
        actCfg->srcNum);
    HW_SET_FIELD32(
        regVal1,
        (UInt32) VIP_CROP_HORZ_PORT_A_ACT_SKIP_NUMPIX,
        actCfg->cropCfg.cropStartX);
    HW_SET_FIELD32(
        regVal1,
        (UInt32) VIP_CROP_HORZ_PORT_A_ACT_USE_NUMPIX,
        actCfg->cropCfg.cropWidth);

    regVal2 = 0;
    HW_SET_FIELD32(
        regVal2,
        (UInt32) VIP_CROP_VERT_PORT_A_ACT_SKIP_NUMLINES,
        actCfg->cropCfg.cropStartY);
    HW_SET_FIELD32(
        regVal2,
        (UInt32) VIP_CROP_VERT_PORT_A_ACT_USE_NUMLINES,
        actCfg->cropCfg.cropHeight);

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_CROP_HORZ_PORT_A, regVal1);
        HW_WR_REG32(baseAddr + VIP_CROP_VERT_PORT_A, regVal2);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_REG32(baseAddr + VIP_CROP_HORZ_PORT_B, regVal1);
        HW_WR_REG32(baseAddr + VIP_CROP_VERT_PORT_B, regVal2);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortEnable
 *  \brief Enable/Disable specified port.
 *         Primarily use PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable            1: Enable Port; 0: Disable Port
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortEnable(VpsHal_Handle handle,
                           UInt32        enable,
                           Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    enable = (UInt32) (enable != 0);

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_A, VIP_PORT_A_ENABLE, enable);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_B, VIP_PORT_B_ENABLE, enable);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortDisableAncCrop
 *  \brief Disable ancillary cropping.
 *         Primarily use XTRA2_PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortDisableAncCrop(VpsHal_Handle handle,
                                   Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_FIELD32(
            baseAddr + VIP_ANC_CROP_HORZ_PORT_A,
            VIP_ANC_CROP_HORZ_PORT_A_ANC_BYPASS_N,
            (UInt32) FALSE);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_FIELD32(
            baseAddr + VIP_ANC_CROP_HORZ_PORT_B,
            VIP_ANC_CROP_HORZ_PORT_B_ANC_BYPASS_N,
            (UInt32) FALSE);
    }
    else
    {
        retVal = BSP_EFAIL;
    }
    return (retVal);
}

/**
 *  VpsHal_vipPortDisableActCrop
 *  \brief Disable active data cropping.
 *         Primarily use XTRA4_PORT_X register
 *
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr     Register Overlay address. Ignored if 0.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vipPortDisableActCrop(VpsHal_Handle handle,
                                   Ptr           configOvlyPtr)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        HW_WR_FIELD32(
            baseAddr + VIP_CROP_HORZ_PORT_A,
            VIP_CROP_HORZ_PORT_A_ACT_BYPASS_N,
            0U);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        HW_WR_FIELD32(
            baseAddr + VIP_CROP_HORZ_PORT_B,
            VIP_CROP_HORZ_PORT_B_ACT_BYPASS_N,
            0U);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipGetSrcStatus
 *  \brief Get the status of Video Source.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  configOvlyPtr  Register Overlay address. Ignored if 0.
 *  \param  vpdmaCh        VPDMA channel used
 *  \param  vipStatus      Pointer to #VpsHal_VipStatus structure.
 *                         This parameter should be non-NULL
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipGetSrcStatus(VpsHal_Handle handle,
                             UInt32 vpdmaCh, VpsHal_VipStatus *vipStatus,
                             Ptr configOvlyPtr)
{
    UInt32 baseAddr = 0;
    Int32  retVal   = BSP_SOK;
    UInt32 sid;
    UInt32 regAddr, regVal;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    if (NULL == configOvlyPtr)
    {
        baseAddr = portInfo->baseAddr;
    }
    else
    {
        GT_assert(VpsHalTrace, FALSE);
    }

    if ((vpdmaCh >= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0) &&
        (vpdmaCh <= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC15))
    {
        sid = vpdmaCh - VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0;
    }
    else
    if ((vpdmaCh >= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0) &&
        (vpdmaCh <= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC15))
    {
        sid = vpdmaCh - VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0;
    }
    else
    if ((vpdmaCh >= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0) &&
        (vpdmaCh <= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC15))
    {
        sid = vpdmaCh - VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0;
    }
    else
    if ((vpdmaCh >= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0) &&
        (vpdmaCh <= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC15))
    {
        sid = vpdmaCh - VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0;
    }
    else
    {
        /* For PORTA/B_LUMA/CHROMA/RGB channels */
        sid = 0;
    }

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != vipStatus);
    /*Check for source id*/
    GT_assert(VpsHalTrace, sid < 0x16U);

    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_A_VDET_VEC);
        vipStatus->isVideoDetect = ((regVal >> sid) & 0x00000001U);

        regVal = HW_RD_REG32(baseAddr + VIP_OUTPUT_PORT_A_SRC_FID);
        vipStatus->prevFid = ((regVal >> (0x2U * sid)) & 0x00000001U);

        regVal = HW_RD_REG32(baseAddr + VIP_OUTPUT_PORT_A_SRC_FID);
        vipStatus->curFid = ((regVal >> ((0x2U * sid) + 0x1U)) & 0x00000001U);

        regAddr = baseAddr + VIP_OUTPUT_PORT_A_SRC0_SIZE + (sid * 0x4U);
        regVal  = HW_RD_REG32(regAddr);

        vipStatus->height = (UInt16) ((regVal & 0x000007FFU) >> 0x00000000U);
        vipStatus->width  = (UInt16) ((regVal & 0x07FF0000U) >> 0x00000010U);
    }
    else if (VPSHAL_VIP_PORT_B == portInfo->portId)
    {
        regVal = HW_RD_REG32(baseAddr + VIP_PORT_B_VDET_VEC);
        vipStatus->isVideoDetect = ((regVal >> sid) & 0x00000001U);

        regVal = HW_RD_REG32(baseAddr + VIP_OUTPUT_PORT_B_SRC_FID);
        vipStatus->prevFid = ((regVal >> (0x2U * sid)) & 0x00000001U);

        regVal = HW_RD_REG32(baseAddr + VIP_OUTPUT_PORT_B_SRC_FID);
        vipStatus->curFid = ((regVal >> ((0x2U * sid) + 0x1U)) & 0x00000001U);

        regAddr = baseAddr + VIP_OUTPUT_PORT_B_SRC0_SIZE + (sid * 0x4U);
        regVal  = HW_RD_REG32(regAddr);

        vipStatus->height = (UInt16) ((regVal & 0x000007FFU) >> 0x00000000U);
        vipStatus->width  = (UInt16) ((regVal & 0x07FF0000U) >> 0x00000010U);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortReset
 *  \brief SW reset for VIP Ports.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable         1 to RESET, 0 to UN-RESET
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipPortReset(VpsHal_Handle handle, UInt32 enable)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;
    baseAddr = portInfo->baseAddr;

    if (portInfo->portId == VPSHAL_VIP_PORT_A)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_A, VIP_PORT_A_SW_RESET, enable);
    }
    else if (portInfo->portId == VPSHAL_VIP_PORT_B)
    {
        HW_WR_FIELD32(baseAddr + VIP_PORT_B, VIP_PORT_B_SW_RESET, enable);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipPortReset
 *  \brief FIFO reset for VIP Ports.
 *
 *  \param  handle         Valid handle returned by VpsHal_vipPortOpen()
 *  \param  enable         1 to RESET, 0 to UN-RESET
 *
 *  \return                success     0
 *                         failure     error value.
 */
Int32 VpsHal_vipPortResetFIFO(VpsHal_Handle handle, UInt32 enable)
{
    Int32  retVal   = BSP_SOK;
    UInt32 baseAddr = 0;
    UInt32 regVal;
    VpsHal_VipPortInfo *portInfo;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;

    baseAddr = portInfo->baseAddr;
    enable   = (UInt32) (enable != 0);

    regVal = (VIP_PORT_A_CLR_ASYNC_WR_FIFO_MASK |
              VIP_PORT_A_CLR_ASYNC_RD_FIFO_MASK);
    if (portInfo->portId == VPSHAL_VIP_PORT_A)
    {
        if (enable)
        {
            regVal |= HW_RD_REG32(baseAddr + VIP_PORT_A);
        }
        else
        {
            regVal = (~regVal) & HW_RD_REG32(baseAddr + VIP_PORT_A);
        }
        HW_WR_REG32(baseAddr + VIP_PORT_A, regVal);
    }
    else if (portInfo->portId == VPSHAL_VIP_PORT_B)
    {
        if (enable)
        {
            regVal |= HW_RD_REG32(baseAddr + VIP_PORT_B);
        }
        else
        {
            regVal = (~regVal) & HW_RD_REG32(baseAddr + VIP_PORT_B);
        }
        HW_WR_REG32(baseAddr + VIP_PORT_B, regVal);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

/**
 *  VpsHal_vipClkEn
 *  \brief Internal function to call VIP Slice clk enable/disable by
 *  selecting the appropriate clock control module.
 */
static void VpsHal_vipClkEn(VpsHal_Handle handle, UInt32 enable)
{
    VpsHal_VipPortInfo *portInfo;
    VpsHal_Handle       vipTopHandle = NULL;
    UInt32 halId, i;
    Bool   alreadyOn = FALSE;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    portInfo = (VpsHal_VipPortInfo *) handle;
    halId    = portInfo->halId;

    if (enable == 0U)
    {
        switch (portInfo->portId)
        {
            /* Assumes PORTA is followed PORTB of same slice in the HAL obj */
            case VPSHAL_VIP_PORT_A:
                for (i = 0; i < vipPortHalObj.numInst; i++)
                {
                    if (vipPortHalObj.portObj[i].halId == (halId + 1U))
                    {
                        if (0x0U != vipPortHalObj.portObj[i].openCnt)
                        {
                            alreadyOn = TRUE;
                        }
                        break;
                    }
                }
                break;

            case VPSHAL_VIP_PORT_B:
                for (i = 0; i < vipPortHalObj.numInst; i++)
                {
                    if (vipPortHalObj.portObj[i].halId == (halId - 1U))
                    {
                        if (0x0U != vipPortHalObj.portObj[i].openCnt)
                        {
                            alreadyOn = TRUE;
                        }
                        break;
                    }
                }
                break;

            default:
                /* TODO: Error check */
                break;
        }
    }

    if (FALSE == alreadyOn)
    {
        switch (portInfo->instId)
        {
            case VPSHAL_VIP1:
                vipTopHandle = VpsHal_vipTopGetInstInfo(VPSHAL_VIP1);
                break;

            case VPSHAL_VIP2:
                vipTopHandle = VpsHal_vipTopGetInstInfo(VPSHAL_VIP2);
                break;

            case VPSHAL_VIP3:
                vipTopHandle = VpsHal_vipTopGetInstInfo(VPSHAL_VIP3);
                break;

            default:
                /* TODO: Error check */
                break;
        }
    }

    if ((NULL != vipTopHandle) && (FALSE == alreadyOn))
    {
        switch (portInfo->sliceId)
        {
            case VPSHAL_VIP_S0:
                VpsHal_vipTopEnableModule(
                    vipTopHandle,
                    VPSHAL_VIP_TOP_S0_DP,
                    enable,
                    0);
                break;

            case VPSHAL_VIP_S1:
                VpsHal_vipTopEnableModule(
                    vipTopHandle,
                    VPSHAL_VIP_TOP_S1_DP,
                    enable,
                    0);
                break;

            default:
                /* TODO: Error check */
                break;
        }
    }

    return;
}

/**
 *  VpsHal_vipPortGetPortParams
 *  \brief when passed with the handle of VIP,it returns the port and slice ID
 *  to the calling functions.
 *  839
 *  \param  handle            Valid handle returned by VpsHal_vipPortOpen()
 *  \param  port            Pointer to return the value of the VIP port.
 *  \param  slice           pointer to return the value of the VIP slice.
 *
 *  \return                   success    0
 *                            failure    error value
 */

Int32 VpsHal_vipPortGetPortParams(VpsHal_Handle handle, UInt32 *port,
                                  UInt32 *slice)
{
    Int32 retVal = BSP_SOK;
    VpsHal_VipPortInfo *portInfo = (VpsHal_VipPortInfo *) handle;

    *port  = (portInfo->portId);
    *slice = (portInfo->sliceId);
    return retVal;
}

/**
 *  VpsHal_vipPortGetOverflowStatus
 *  \brief Check whether the specified port/slice combo has overflowed or not.
 *
 *  \param handle           Valid handle returned by VpsHal_vipPortOpen function
 *  \param vipErrStatus     Pointer to #VpsHal_VipErrStatus which will contains
 *                          error status for the specified port
 *
 *  \return                 BSP_SOK: Success
 *                          BSP_EFAIL: Failure
 */
Int32 VpsHal_vipPortGetOverflowStatus(VpsHal_Handle handle,
                                      UInt32       *vipErrStatus)
{
    VpsHal_VipPortInfo *portInfo;
    UInt32 baseAddr, regVal;
    UInt32 opOverflowVal, asyncOverflowVal, ancOverflowVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != vipErrStatus);
    portInfo = (VpsHal_VipPortInfo *) handle;
    baseAddr = portInfo->baseAddr;

    regVal = HW_RD_REG32(baseAddr + VIP_FIQ_STATUS);
    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        opOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_LUMA_MASK);
        asyncOverflowVal =
            (regVal & VIP_FIQ_STATUS_ASYNC_FIFO_PORT_A_MASK);
        ancOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_ANC_MASK);
    }
    else
    {
        opOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_LUMA_MASK);
        asyncOverflowVal =
            (regVal & VIP_FIQ_STATUS_ASYNC_FIFO_PORT_B_MASK);
        ancOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_ANC_MASK);
    }

    *vipErrStatus = (opOverflowVal | asyncOverflowVal | ancOverflowVal);

    return BSP_SOK;
}

/**
 *  VpsHal_vipPortIsOverflow
 *  \brief Check whether the specified port/slice combo has overflowed or not.
 *         Interrupt will also be cleared.
 *
 *  \param handle           Valid handle returned by VpsHal_vipPortOpen function
 *  \param vipErrStatus     Pointer to #VpsHal_VipErrStatus which will contains
 *                          error status for the specified port
 *
 *  \return                 BSP_SOK: Success
 *                          BSP_EFAIL: Failure
 */
Int32 VpsHal_vipPortGetErrorStatus(VpsHal_Handle            handle,
                                   VpsHal_VipPortErrStatus *vipErrStatus)
{
    VpsHal_VipPortInfo *portInfo;
    UInt32 baseAddr, regVal;
    UInt32 opOverflowVal, asyncOverflowVal, actProtVal, ancProtVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != vipErrStatus);
    portInfo = (VpsHal_VipPortInfo *) handle;
    baseAddr = portInfo->baseAddr;

    vipErrStatus->isOutputOverflow   = 0;
    vipErrStatus->isAsyncOverflow    = 0;
    vipErrStatus->isActProtViolation = 0;
    vipErrStatus->isAncProtViolation = 0;

    regVal = HW_RD_REG32(baseAddr + VIP_FIQ_STATUS);
    if (VPSHAL_VIP_PORT_A == portInfo->portId)
    {
        opOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_LUMA_MASK);
        asyncOverflowVal =
            (regVal & VIP_FIQ_STATUS_ASYNC_FIFO_PORT_A_MASK);
        actProtVal =
            (regVal & VIP_FIQ_STATUS_PORT_A_YUV_PROTOCOL_VIOLATION_MASK);
        ancProtVal =
            (regVal & VIP_FIQ_STATUS_PORT_A_ANC_PROTOCOL_VIOLATION_MASK);
    }
    else
    {
        opOverflowVal =
            (regVal & VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_LUMA_MASK);
        asyncOverflowVal =
            (regVal & VIP_FIQ_STATUS_ASYNC_FIFO_PORT_B_MASK);
        actProtVal =
            (regVal & VIP_FIQ_STATUS_PORT_B_YUV_PROTOCOL_VIOLATION_MASK);
        ancProtVal =
            (regVal & VIP_FIQ_STATUS_PORT_B_ANC_PROTOCOL_VIOLATION_MASK);
    }

    vipErrStatus->isOutputOverflow   = (UInt32) (opOverflowVal != 0U);
    vipErrStatus->isAsyncOverflow    = (UInt32) (asyncOverflowVal != 0U);
    vipErrStatus->isActProtViolation = (UInt32) (actProtVal != 0U);
    vipErrStatus->isAncProtViolation = (UInt32) (ancProtVal != 0U);

    regVal = (opOverflowVal | asyncOverflowVal | actProtVal | ancProtVal);

    HW_WR_REG32(baseAddr + VIP_FIQ_CLEAR, 0);
    HW_WR_REG32(baseAddr + VIP_FIQ_CLEAR, regVal);

    return BSP_SOK;
}

