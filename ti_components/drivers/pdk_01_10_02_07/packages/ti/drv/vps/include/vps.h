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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_COMMON_API VPS - Common API
 *
 *  @{
 */

/**
 *  \file vps.h
 *
 *  \brief VPS - Common API
 */

#ifndef VPS_H_
#define VPS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/soc.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver ID base for the display driver class. */
#define VPS_DISP_DRV_BASE               (0x00000100U)

/** \brief Driver ID base for the capture driver class. */
#define VPS_CAPT_DRV_BASE               (0x00000200U)

/** \brief Driver ID base for the M2M driver class. */
#define VPS_M2M_DRV_BASE                (0x00000300U)

/** \brief Driver ID base for the other driver class. */
#define VPS_MISC_DRV_BASE               (0x00000400U)

/** \brief Driver ID base for the custom/user driver class. */
#define VPS_USER_DRV_BASE               (0x00000500U)

/** \brief Display driver ID used at the time of FVID2 create. */
#define FVID2_VPS_DISP_DRV              (VPS_DISP_DRV_BASE + 0x00000000U)

/** \brief Display controller driver ID used at the time of FVID2 create. */
#define FVID2_VPS_DCTRL_DRV             (VPS_DISP_DRV_BASE + 0x00000001U)

/** \brief Video capture driver ID used at the time of FVID2 create. */
#define FVID2_VPS_CAPT_VID_DRV          (VPS_CAPT_DRV_BASE + 0x00000000U)

/** \brief M2M driver ID used at the time of FVID2 create. */
#define FVID2_VPS_M2M_DRV               (VPS_M2M_DRV_BASE + 0x00000000U)

/** \brief FVID2 Driver ID for the common M2M interface */
#define FVID2_VPS_COMMON_M2M_INTF_DRV   (VPS_M2M_DRV_BASE + 1U)

/** \brief FVID2 Driver ID for the DSS M2M driver */
#define FVID2_VPS_DSS_M2M_DRV           (VPS_M2M_DRV_BASE + 2U)

/** \brief VPS control driver ID used at the time of FVID2 create. */
#define FVID2_VPS_CTRL_DRV              (VPS_MISC_DRV_BASE + 0x00000000U)

/*
 *  IOCTLs Base address.
 */
/** \brief IOCTL base address for the IOCTLs common to display, capture and
 *  mem to mem drivers. */
#define VPS_COMMON_IOCTL_BASE           (FVID2_USER_BASE + 0x00000000U)
/** \brief IOCTL base address for the display driver IOCTLs. */
#define VPS_DISP_IOCTL_BASE             (FVID2_USER_BASE + 0x00010000U)
/** \brief IOCTL base address for the display controller driver IOCTLs. */
#define VPS_DCTRL_IOCTL_BASE            (FVID2_USER_BASE + 0x00020000U)
/** \brief IOCTL base address for the capture driver IOCTLs. */
#define VPS_CAPT_IOCTL_BASE             (FVID2_USER_BASE + 0x00030000U)
/** \brief IOCTL base address for the M2M driver IOCTLs. */
#define VPS_M2M_IOCTL_BASE              (FVID2_USER_BASE + 0x00040000U)
/** \brief IOCTL base address for the VPS control driver IOCTLs. */
#define VPS_CTRL_IOCTL_BASE             (FVID2_USER_BASE + 0x00050000U)
/** \brief IOCTL base address for the advanced debug capabilities.
 *  Caution: To be used with care. */
#define VPS_ADV_IOCTL_BASE              (FVID2_USER_BASE + 0x00060000U)

/** \brief Multi window layout ID base for the user created layouts. */
#define VPS_USER_LAYOUT_ID_BASE         (100U)

/*
 * Capture Driver Instances
 */
/** \brief VIP driver instance ID base. */
#define VPS_CAPT_INST_VIP_BASE          (0U)
/** \brief Number of VIP driver instances. */
#define VPS_CAPT_INST_VIP_COUNT         (32U)
/** \brief VIP driver instance ID end. */
#define VPS_CAPT_INST_VIP_END           (VPS_CAPT_INST_VIP_BASE + \
                                         VPS_CAPT_INST_VIP_COUNT)

/** \brief DSS WB driver instance ID base. */
#define VPS_CAPT_INST_DSS_WB_BASE       (VPS_CAPT_INST_VIP_END + 1U)
/** \brief Number of DSS WB driver instances. */
#define VPS_CAPT_INST_DSS_WB_COUNT      (8U)
/** \brief DSS WB driver instance ID end. */
#define VPS_CAPT_INST_DSS_WB_END        (VPS_CAPT_INST_DSS_WB_BASE + \
                                         VPS_CAPT_INST_DSS_WB_COUNT)

/** \brief ISS based capture driver instance ID base. */
#define VPS_CAPT_INST_ISS_BASE          (VPS_CAPT_INST_DSS_WB_END + 1U)
/** \brief Number of ISS based capture driver instances. */
#define VPS_CAPT_INST_ISS_COUNT         (16U)
/** \brief ISS based capture driver instance ID end. */
#define VPS_CAPT_INST_ISS_END           (VPS_CAPT_INST_ISS_BASE + \
                                         VPS_CAPT_INST_ISS_COUNT)

/** \brief Cumulative number of capture instances supported */
#define VPS_CAPT_INST_ID_MAX            (VPS_CAPT_INST_ISS_END)

/**
 *  \brief Maximum number of streams supported by the VPS driver,
 *         Used in allocating array size.
 */
#define VPS_MAX_STREAMS                 (16U)

/**
 *  \brief Maximum nember of VIP instances across all platforms.
 *         This is defined here to make the interface not dependant on the
 *         specific build and platform.
 */
#define VPS_VIP_IRQ_MAX                 (3U)
/*
 *  Common IOCTLS for display, M2M and capture drivers
 */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_COMMON
 *  @{
 */

/**
 *  \brief Set the scaler coefficients.
 *
 *  \param cmdArgs       [IN]  const Vps_ScCoeffParams *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_SET_COEFFS            (VPS_COMMON_IOCTL_BASE + 0x0000U)

/**
 *  \brief Get DEI context information.
 *
 *  \param cmdArgs       [IN]     Vps_DeiCtxInfo *
 *  \param cmdStatusArgs [OUT]    NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_GET_DEI_CTX_INFO      (VPS_COMMON_IOCTL_BASE + 0x0004U)

/**
 *  \brief Set DEI context buffers to driver.
 *
 *  \param cmdArgs       [IN]     const Vps_DeiCtxBuf *
 *  \param cmdStatusArgs [OUT]    NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_SET_DEI_CTX_BUF       (VPS_COMMON_IOCTL_BASE + 0x0005U)

/**
 *  \brief Get DEI context buffers from driver.
 *
 *  \param cmdArgs       [IN]     Vps_DeiCtxBuf *
 *  \param cmdStatusArgs [OUT]    NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_GET_DEI_CTX_BUF       (VPS_COMMON_IOCTL_BASE + 0x0006U)

/**
 *  \brief Enable/disable FMD operation of DEIH/DEI.
 *
 *  \param cmdArgs       [IN]  const Vps_DeiFmdConfig *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_SET_DEI_FMD_CFG       (VPS_COMMON_IOCTL_BASE + 0x000CU)

/**
 *  \brief Returns the FMD status, to be used only for debugging purpose.
 *
 *  \param cmdArgs       [IN]  Vps_DeiFmdStatusReg *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_RD_DEI_FMD_STAT       (VPS_COMMON_IOCTL_BASE + 0x000DU)

/**
 *  \brief Updates the FMD settings, to be used only for debugging purpose.
 *
 *  \param cmdArgs       [IN]  const Vps_DeiFmdUpdateConfig *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_WR_DEI_FMD_UPDATE     (VPS_COMMON_IOCTL_BASE + 0x000EU)

/**
 *  \brief Used to enable or disable VC-1 Range Mapping and Range Reduction
 *         Feature
 *
 *  This IOCTL could be used by the application to enable or disable
 *  Range Mapping and Range Reduction for M2M drivers for the following paths
 *  a) Primary Input Path
 *  b) Auxiliary Input Path
 *  c) Both Secondary Input Paths.
 *
 *  This IOCTL will be used to enable or disable this feature for future frames
 *  of all channels
 *
 *  Range Mapping is supported for the range of values: 0 to 7 for Y and UV
 *  Component.
 *
 *  When using this IOCTL the application should ensure that there is no
 *  input request pending with the driver. Otherwise the driver will return
 *  error.
 *
 *  By Default Range Mapping and Range Reduction feature is disabled in the
 *  M2M drivers
 *
 *  Range Mapping is performed based on the following equations:
 *  Y[n] = (rngMapEnable) ? CLIP ((((Y[n] - 128) * (rngMapValY + 9) + 4) >> 3)
 *                                 + 128) : Y[n] ;
 *  Cb[n] = (rngMapEnable) ? CLIP ((((Cb[n] - 128) * (rngMapValUV + 9) + 4)
 *                                   >> 3) + 128) : Cb[n] ;
 *  Cr[n] = (rngMapEnable) ? CLIP ((((Cr[n] - 128) * (rngMapValUV + 9) + 4)
 *                                   >> 3) + 128) : Cr[n] ;
 *
 *  Range Reduction is performed based on the following equations:
 *  Y[n] = (rngRdtEnable) ? CLIP ((Y[n] - 128) * 2 + 128) : Y[n];
 *  Cb[n] = (rngRdtEnable) ? CLIP ((Cb[n] - 128) * 2 + 128) : Cb[n]
 *  Cr[n] = (rngRdtEnable) ? CLIP ((Cr[n] - 128) * 2 + 128) : Cr[n];
 *
 *  The implementation performs Range Mapping first, and the output of
 *  Range Mapping drives Range Reduction.
 *
 *  \param cmdArgs       [IN]       const Vps_RngMapRdtCfg *
 *  \param cmdStatusArgs [OUT]      NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_SET_RANGE_MAP_REDUCT_CFG  (VPS_COMMON_IOCTL_BASE + 0x000FU)

/**
 *  \brief Get Range Mapping and Range Reduction configuration
 *
 *  When using this IOCTL the application should ensure that there is no
 *  input request pending with the driver. Otherwise the driver will return
 *  error.
 *
 *  \param cmdArgs       [IN]     Vps_RngMapRdtCfg *
 *  \param cmdStatusArgs [OUT]    NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_GET_RANGE_MAP_REDUCT_CFG  (VPS_COMMON_IOCTL_BASE + 0x0010U)

/**
 *  \brief Register an application function (pointer) for getting the
 *  time stamp value used at the frame completion time.
 *
 *  The same IOCTL could be used to un-register the existing time stamp
 *  function by passing NULL to the function pointer.
 *
 *  \param cmdArgs       [IN]  const Vps_TimeStampParams *
 *  \param cmdArgsStatus       NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_REGISTER_TIMESTAMP_FXN    (VPS_COMMON_IOCTL_BASE + 0x0011U)

/* @} */

/*
 *  Advanced IOCTLS for display, M2M and capture drivers.
 */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_ADVANCED
 *  @{
 */

/**
 *  \brief Read the scaler hardware configuration.
 *
 *  This ioctl can be used to read the actual hardware registers of the
 *  scaler.
 *  This is for the advanced user for the hardware debug capability.
 *  For the multiple channel mode of the driver data is returned from the
 *  overlay memory instead of actual hardware registers.
 *
 *  \param cmdArgs       [OUT] Vps_ScRdWrAdvCfg *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_READ_ADV_SC_CFG       (VPS_ADV_IOCTL_BASE + 0x0000U)

/**
 *  \brief Write the scaler hardware configuration.
 *
 *  This ioctl can be used to write the actual hardware registers of the
 *  scaler.
 *  This is for the advanced user for the hardware debug capability.
 *  For the multiple channel mode of the driver data is written to the
 *  overlay memory instead of actual hardware registers.
 *
 *  \param cmdArgs       [IN]  const Vps_ScRdWrAdvCfg *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_WRITE_ADV_SC_CFG      (VPS_ADV_IOCTL_BASE + 0x0001U)

/**
 *  \brief Read the De-Interlacer hardware configuration.
 *
 *  This ioctl can be used to read the actual hardware registers of the
 *  De-interlacer.
 *  This is for the advanced user for the hardware debug capability.
 *
 *  \param cmdArgs       [OUT] Vps_DeiRdWrAdvCfg *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_READ_ADV_DEI_CFG       (VPS_ADV_IOCTL_BASE + 0x0012U)

/**
 *  \brief Write the De-Interlacer hardware configuration.
 *
 *  This ioctl can be used to write the actual hardware registers of the
 *  De-interlacer.
 *  This is for the advanced user for the hardware debug capability.
 *
 *  \param cmdArgs       [IN]  const Vps_DeiRdWrAdvCfg *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure
 *
 */
#define IOCTL_VPS_WRITE_ADV_DEI_CFG      (VPS_ADV_IOCTL_BASE + 0x0013U)

/* @} */

/**
 *  \brief Function prototype, to determine the time stamp.
 *
 *  \param args  [IN]  Not used as of now.
 *
 *  \return An unsigned int 64 value, that represents the current time in usec.
 */
typedef UInt64 (*Vps_TimeStampFxn)(void *args);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS interrupt initialization parameters.
 */
typedef struct
{
    UInt32 vipIrqNum[VPS_VIP_IRQ_MAX];
    /**< Array of VIP interrupt number for each of the VIP instance.
     *   Array is defined for max VIP instances across all platforms.
     *   But only the number elements equal to VIPs available for any platform
     *   are valid. */
    UInt32 vpeIrqNum;
    /**< VPE interrupt number. */
    UInt32 dssIrqNum;
    /**< DSS interrupt number. */
    UInt32 calIrqNum;
    /**< CAL interrupt number. */
    UInt32 issIrqNum;
    /**< ISS interrupt number. */
} Vps_IrqParams;

/**
 *  \brief VPS initialization parameters.
 */
typedef struct
{
    UInt32 isAddrTransReq;
    /**< Set this flag to TRUE if the driver has to perform address translation
     *   of the descriptor memory before submitting the descriptor to the
     *   hardware. This is used when the physical memory of the descriptor
     *   is mapped to a different virtual memory.
     *
     *   When address translation is enabled, the dirver performs the following
     *   operations to convert the virtual address to physical address and
     *   vice versa.
     *
     *   physAddr = (virtAddr - virtBaseAddr) + physBaseAddr;
     *   virtAddr = (physAddr - physBaseAddr) + virtBaseAddr;
     *
     *   Important: The descriptor memory should in a physically continuous
     *   memory.
     *
     *   Note: The buffer address will not be translated using the above
     *   translation and hence the application should provide the physical
     *   address to be programmed to the hardware.
     *
     *   Note: VPSHAL_VPDMA_ENABLE_ADDR_TRANS macro should be defined in
     *   vpshal_vpdma.c file to enable address translation at compile time.
     *   By default this is defined. But alternatively application could disable
     *   this conversion at compile time by removing this macro definition
     *   to improve performance. */
    UInt32 virtBaseAddr;
    /**< Virtual memory base address. */
    UInt32 physBaseAddr;
    /**< Physical memory base address. */
    UInt32 isCacheOpsReq;
    /**< This will enable cache flush and invalidate operations on the
     *   descriptor memory in case the descriptor memory is in cache region.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    UInt32 isCacheFlushReq;
    /**< This will enable cache flush operations on the
     *   descriptor memory in case the descriptor memory is in cache region.
     *   In case of write-through cache mode, this flag could be set to FALSE
     *   to save cycles as flush operation is not required in write-through
     *   mode.
     *   This parameter is valid/used only if isCacheOpsReq is TRUE.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    Vps_IrqParams irqParams;
    /**< This will enable to configure different interrupt numnbers for
     *   different VPS modules. This will be initialized to default values as
     *   specified in the VpsInitParams_init function. User may override these
     *   values.
     *
     *   Note: Driver will only register for the specified interrupt numbers.
     *   The corresponding crossbar mapping for the device interrupt should be
     *   done by the application. In the Vps examples the crossar mapping is
     *   done from function Bsp_platformTda2xxInit/Bsp_platformTda3xxInit.
     *   Application may pass the Bsp_PlatformInitParams->isIrqXBarSettingReq as
     *   false to Bsp_platformInit function and do all the crossbar mapping
     *   required or update the crossbar configuration done in
     *   Bsp_platformTda2xxInit/Bsp_platformTda3xxInit.
     */
} Vps_InitParams;

/**
 *  struct Vps_SubFrameParams
 *  \brief Configuration for sub-frame level processing at create time.
 */
typedef struct
{
    UInt32 subFrameEnable;
    /**< TRUE : SubFrame level capture/processing is enabled.
     *   FALSE: SubFrame level capture/processing is disabled.
     *   Must be FALSE for multi-channel capture mode. */
    UInt32 numLinesPerSubFrame;
    /**< Number of lines per subframes.
     *
     *   MUST be multiple of the output size.
     *   Not valid, ignored for ancillary data capture.
     *
     *   In case of capture,
     *   SubFrame callback gets called after every numLinesPerSubFrame
     *   for every output stream, except ancillary data stream.
     *
     *   Ignored when subFrameEnable = FALSE */
    UInt32              interruptMode;
    /**< Client Interrupt mode as per #Vps_VpdmaClientIntrMode
     *   Ignored when subFrameEnable = FALSE */
    Fvid2_SubFrameCbFxn subFrameCb;
    /**< SubFrame callback, is called for every subframe of output stream.
     *
     *   This is valid only in case of capture as for M2M operation each
     *   slice is considered as a separate request to the driver.
     *
     *   When sub frame is enabled and this parameter is NULL, then the driver
     *   will not generate any callback to the application. Internally
     *   the driver will not register for this interrupt as well. This could
     *   be used in use cases when the slice interrupt is handled by a remote
     *   core.
     *   Ignored when subFrameEnable = FALSE. */
} Vps_SubFrameParams;

/**
 *  \brief Structure used to configure time stamping of frames.
 */
typedef struct
{
    Vps_TimeStampFxn timeStampFxn;
    /**< By default, OSAL (BIOS) API is used to time stamp frames.
     *
     *   Applications could over-ride the same, by providing a
     *   function that would return an unsigned int 64 value representing the
     *   timestamp in usec.
     *   The driver would call this function and update the 'timeStamp'
     *   and 'timeStamp64' member of #Fvid2_Frame with the return
     *   value of this function.
     *
     *   Note: The 64-bit value / 1000 is used to update the 'timeStamp'
     *   member.
     *
     *   Passing a value of NULL un-registers the time stamp function. */
    UInt32 reserved;
    /**< Not used now. Set to zero. */
} Vps_TimeStampParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS init function.
 *
 *  Initializes the VPS drivers and the hardware.
 *  This function should be called before calling any of driver API's and
 *  should be called only once.
 *
 *  \param initPrms     [IN] VPS Initialization parameters.
 *                           If NULL is passed, the default parameters will be
 *                           assumed - address translation disabled.
 *
 *  \return BSP_SOK on success else appropiate FVID2 error code on failure.
 */
Int32 Vps_init(const Vps_InitParams *initPrms);

/**
 *  \brief VPS deinit function.
 *
 *  Uninitializes the drivers and the hardware and should be called during
 *  system shutdown. Should not be called if Vps_init() is not called.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 Vps_deInit(Ptr args);

/**
 *  \brief Vps_InitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #Vps_InitParams structure.
 *
 */
void VpsInitParams_init(Vps_InitParams *initPrms);

/**
 *  \brief Vps_SubFrameParams structure init function.
 *
 *  \param sfPrms       [IN] Pointer to #Vps_SubFrameParams structure.
 *
 */
static inline void VpsSubFrameParams_init(Vps_SubFrameParams *sfPrms);

/**
 *  \brief Vps_SubFrameParams structure init function.
 *
 *  \param tsPrms       [IN] Pointer to #Vps_TimeStampParams structure.
 *
 */
static inline void VpsTimeStampParams_init(Vps_TimeStampParams *tsPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsSubFrameParams_init(Vps_SubFrameParams *sfPrms)
{
    if(NULL != sfPrms)
    {
        sfPrms->subFrameEnable      = (UInt32) FALSE;
        sfPrms->numLinesPerSubFrame = 0U;
        sfPrms->interruptMode       = VPS_INTR_END_OF_EVERY_NTH_LINE;
        sfPrms->subFrameCb          = NULL;
    }

    return;
}

static inline void VpsTimeStampParams_init(Vps_TimeStampParams *tsPrms)
{
    if(NULL != tsPrms)
    {
        tsPrms->timeStampFxn = NULL;
        tsPrms->reserved     = 0U;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_H_ */

/* @} */

/**
 * \mainpage  VPS Drivers
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 * VPS video Drivers allow users to make use of all video hardware features like
 * 1080P capture, HDMI/LCD/SDTV display, deinterlacing, scaling.
 * A user can use the drivers in many different ways like multi-channel capture,
 * memory to memory processing, display and so on.
 * This document has detailed API description that user's can use to make use
 * of the VPS drivers.
 *
 * <b>
 * Also refer to VPS driver user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 * The VPS driver API can be broadly divided into the following categories
 *
 * - <b> FVID2 API </b> (See \ref BSP_DRV_FVID2_API) <br>
 *  API used to create, control and use the different VPS drivers
 *
 * - <b> VPS (Video Processing Sub-system) API </b> <br>
 *  API for all video drivers
 *    - <b> VPS Common API </b> (See \ref BSP_DRV_VPS_COMMON_API) <br>
 *    - <b> VPS Control Driver API </b> (See \ref BSP_DRV_VPS_CTRL_API) <br>
 *    - <b> VPS Capture API </b> (See \ref BSP_DRV_VPS_CAPTURE_API)
 *      API for video capture drivers <br>
 *          - \ref BSP_DRV_VPS_CAPTURE_VIP_API API specific to VIP capture driver
 *          - \ref BSP_DRV_VPS_CAPTURE_ISS_API API specific to ISS capture driver
 *          - \ref BSP_DRV_VPS_CAPTURE_DSSWB_API API specific to DSS WB capture driver
 *    - <b> VPS Display API </b> (See \ref BSP_DRV_VPS_DISPLAY_API)
 *      API for video display drivers
 *    - <b> VPS Display Controller API </b> (See \ref BSP_DRV_VPS_DCTRL_API)
 *      API for controlling and configuring VENCs in the display subsystem
 *    - <b> VPS Memory to Memory (M2M) API </b>
 *      (See \ref BSP_DRV_VPS_M2M_API and \ref BSP_DRV_VPS_M2M_INTF_API) API for memory to memory drivers
 *          - \ref BSP_DRV_VPS_M2M_VPE_API API specific to VPE M2M driver
 *          - \ref BSP_DRV_VPS_M2M_ISS_API API specific to ISS M2M driver
 *          - \ref BSP_DRV_VPS_M2M_DSS_API API specific to DSS M2M writeback driver
 *
 * - <b> External Device API </b> (See \ref BSP_DRV_DEVICE_API) <br>
 *  API for controlling external video devices like video decoders, video
 * encoders, video filters, IO expanders, Ultra-sonic sensors
 *  - See \ref BSP_DRV_DEVICE_VID_DEC_API
 *  - See \ref BSP_DRV_DEVICE_VID_SENSOR_API
 *  - See \ref BSP_DRV_DEVICE_VID_ENC_API
 *  - See \ref BSP_DRV_DEVICE_IOEXP_API
 *  - See \ref BSP_DRV_DEVICE_ULTRASONIC_SENSOR_API_PGA450
 *  - See \ref BSP_DRV_DEVICE_ULTRASONIC_SENSOR_API_PGA460
 *
 * - <b> Platform Specific API </b> (See \ref BSP_DRV_PLATFORM_API) <br>
 *  API for platform/board specific control, like setting pin muxes, clocks etc
 *
 * - <b> Board Specific API </b> (See \ref BSP_DRV_BOARD_API) <br>
 *  API for board specific features.
 *
 *
 * In addition to above drivers the VPS package also includes many sample
 * examples
 * which show how to use the drivers in different ways.
 * Many of these sample examples use a common set of APIs which a user may find
 * useful to
 * refer to for use in their final application.
 * - <b> Utility library API </b> (See \ref BSPUTILS_API) <br>
 *  APIs used by sample application for allocating memory, exchanging buffers,
 *  measuring performamce and so on
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */

/**
 *  \defgroup BSP_DRV_VPS_API VPS Driver API
 */

/**
 *  \defgroup BSP_DRV_IOCTL                 VPS - All IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL
 *  \defgroup BSP_DRV_IOCTL_FVID2           FVID2 - Common IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL
 *  \defgroup BSP_DRV_IOCTL_VPS             VPS IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_COMMON      VPS - Common IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_ADVANCED    VPS - Advanced IOCTL's
 */

/*
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_CTRL        VPS Control Driver IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_CAPTURE     VPS Capture IOCTL's
 *
 *  VIP capture specific IOCTLs are as below
 *
 *  - \ref BSP_DRV_IOCTL_VPS_CAPTURE_VIP
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver
 *
 *  - \ref FVID2_START
 *  - \ref FVID2_STOP
 *  - \ref IOCTL_VPS_REGISTER_TIMESTAMP_FXN
 */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_M2M_VPE     VPS M2M VPE IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver
 *
 *  - \ref FVID2_STOP
 *  - \ref IOCTL_VPS_SET_COEFFS
 *  - \ref IOCTL_VPS_GET_DEI_CTX_INFO
 *  - \ref IOCTL_VPS_SET_DEI_CTX_BUF
 *  - \ref IOCTL_VPS_GET_DEI_CTX_BUF
 *  - \ref IOCTL_VPS_SET_DEI_FMD_CFG
 *  - \ref IOCTL_VPS_RD_DEI_FMD_STAT
 *  - \ref IOCTL_VPS_WR_DEI_FMD_UPDATE
 *  - \ref IOCTL_VPS_SET_RANGE_MAP_REDUCT_CFG
 *  - \ref IOCTL_VPS_GET_RANGE_MAP_REDUCT_CFG
 *  - \ref IOCTL_VPS_READ_ADV_DEI_CFG
 *  - \ref IOCTL_VPS_WRITE_ADV_DEI_CFG
 *  - \ref IOCTL_VPS_READ_ADV_SC_CFG
 *  - \ref IOCTL_VPS_WRITE_ADV_SC_CFG
 */

/*
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_DCTRL       VPS Display Controller IOCTL's
 */

/*
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_DISPLAY     VPS Display IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver
 *
 *  - \ref FVID2_START
 *  - \ref FVID2_STOP
 */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS
 *  \defgroup BSP_DRV_IOCTL_VPS_DSS_M2M     VPS DSS M2M writeback driver IOCTL's
 */

/**
 *  \ingroup BSP_DRV_IOCTL
 *  \defgroup BSP_DRV_IOCTL_DEVICE_VID_DEC  External Video Decoder IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver.
 *
 *  - \ref FVID2_START
 *  - \ref FVID2_STOP
 */

/**
 *  \ingroup BSP_DRV_IOCTL
 *  \defgroup BSP_DRV_IOCTL_DEVICE_VID_SENSOR  External Video Sensor IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver.
 *
 *  - \ref FVID2_START
 *  - \ref FVID2_STOP
 */

/*
 *  \ingroup BSP_DRV_IOCTL
 *  \defgroup BSP_DRV_IOCTL_DEVICE_VID_ENC  External Video Encoder IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver.
 *
 *  - \ref FVID2_START
 *  - \ref FVID2_STOP
 */

/**
 *  \ingroup BSP_DRV_IOCTL_DEVICE_VID_DEC
 *  \defgroup BSP_DRV_IOCTL_TVP5158         TVP5158 IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver.
 *
 *  - \ref BSP_DRV_IOCTL_DEVICE_VID_DEC
 */

/**
 *  \ingroup BSP_DRV_IOCTL_DEVICE_VID_ENC
 *  \defgroup BSP_DRV_IOCTL_SII9022A        SII9022A IOCTL's
 *
 *  In addition to the IOCTLs listed above the following common IOCTLs
 *  are applicable to this driver.
 *
 *  - \ref BSP_DRV_IOCTL_DEVICE_VID_ENC
 */
