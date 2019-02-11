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
 *  \file vps_common.h
 *
 *  \brief BSP header file containing commonly used functions.
 *
 */

#ifndef VPS_COMMON_H_
#define VPS_COMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/soc.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/src/vpslib/common/vps_evtMgr.h>
#include <ti/drv/vps/src/vpslib/common/vps_resrcMgr.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_platform.h>
#if defined (SOC_TDA3XX)
#if defined VPS_ISS_ISP_DEF
#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Maximum nember of VIP instances across all platforms.
 *         This is defined here to make the interface not dependant on the
 *         specific build and platform.
 */
#define VPSLIB_VIP_IRQ_MAX                 (3U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS Lib interrupt initialization parameters.
 */
typedef struct
{
    UInt32 vipIrqNum[VPSLIB_VIP_IRQ_MAX];
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
} VpsLib_IrqParams;
/**
 *  \brief VPS Lib initialization parameters.
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
     *   descriptor memory in case the descriptor memory is cache region.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    UInt32 isCacheFlushReq;
    /**< This will enable cache flush operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *   In case of write-through cache mode, this flag could be set to FALSE
     *   to save cycles as flush operation is not required in write-through
     *   mode.
     *   This parameter is valid/used only if isCacheOpsReq is TRUE.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    VpsLib_IrqParams irqParams;
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
} VpsLib_InitParams;

/**
 *  \brief Platform specific data containing base address information of
 *  various modules.
 */
typedef struct
{
    const VpsHal_PlatformData *hal;
    /**< HAL related platform data. */

    const Ptr                 *ispHal;
    /**< ISP Hal Information */
    const Ptr                 *simcopHal;
    /**< Simcop Hal Information */

    const Ptr                 *issCommonPrms;
    /**< Common Parameters */

    /*
     * Misc platform data.
     */
    UInt32                     numEvtMgr;
    /**< Number of event manager present for a platform. */
    Vem_InstParams             evtMgrInstPrms[VEM_MAX_INST];
    /**< Corresponding VEM instance params. */

    UInt32                     numResrcMgr;
    /**< Number of resource manager present for a platform. */
    Vrm_InstParams             resrcMgrInstPrms[VRM_MAX_INST];
    /**< Corresponding VRM instance params. */

    const Ptr                 *calHal;
    /**< CAL Hal information */
    UInt32                     numCalEmInst;
    /**< Number CAL Event Manager instances */
    void                      *calEmInitPrms;
    /**< Cal Event Manager Init Params */
} VpsLib_PlatformData;

/**
 *  struct VpsCore_SubFrameParams
 *  \brief Configuration for sub-frame level processing at create time used
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
    UInt32 interruptMode;
    /**< Client Interrupt mode as per #Vps_VpdmaClientIntrMode
     *   Ignored when subFrameEnable = FALSE */
} VpsCore_SubFrameParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS Lib init function.
 *
 *  Initializes the VPS library.
 *  This function should be called before calling any of driver API's and
 *  should be called only once.
 *
 *  \param initPrms     [IN] VPS Initialization parameters.
 *                           If NULL is passed, the default parameters will be
 *                           assumed - address translation disabled.
 *
 *  \return BSP_SOK on success else appropiate FVID2 error code on failure.
 */
Int32 VpsLib_init(const VpsLib_InitParams *initPrms);

/**
 *  \brief VPS Lib deinit function.
 *
 *  Uninitializes the VPS library and should be called during
 *  system shutdown. Should not be called if Vps_init() is not called.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 VpsLib_deInit(Ptr args);

/**
 *  \brief Returns VPS Lib platform data.
 */
VpsLib_PlatformData *VpsLib_getPlatformData(void);

#ifdef VPS_VIP_BUILD
/**
 *  \brief Returns VPS Lib VIP core instance object pointer.
 *
 *  \param vipInstId    [IN]  VIP Instance number
 */
VpsCore_Inst VpsLib_getVipCoreInstObj(UInt32 vipInstId);
#endif

#ifdef VPS_DSS_BUILD
/**
 *  \brief Returns VPS Lib DSS core instance object pointer.
 */
VpsCore_Inst VpsLib_getDssCoreInstObj(void);

/**
 *  \brief Returns VPS Lib DSS WB core instance object pointer.
 */
VpsCore_Inst VpsLib_getDssWbCoreInstObj(void);

/**
 *  \brief Returns VPS Lib Dctrl core instance object pointer.
 */
VpsCore_Inst VpsLib_getDctrlCoreInstObj(void);

/**
 *  \brief Returns VPS Lib DSS overlay Hal handle.
 *
 *  \param vpdmaInstId  [IN]  DSS overlay instance number
 */
VpsHal_Handle VpsLib_getDssOvlyHalHandle(UInt32 ovlyInstId);
#endif

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
/**
 *  \brief Returns VPS Lib VPDMA Hal handle.
 *
 *  \param vpdmaInstId  [IN]  VPDMA instance number
 */
VpsHal_Handle VpsLib_getVpdmaHalHandle(UInt32 vpdmaInstId);
#endif

/**
 *  \brief VpsLib_InitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #VpsLib_InitParams structure.
 *
 */
static inline void VpsLibInitParams_init(VpsLib_InitParams *initPrms);

Bool VpsLib_platformIsTda2xxFamilyBuild(void);
Bool VpsLib_platformIsOmap5FamilyBuild(void);
Bool VpsLib_platformIsTI814xFamilyBuild(void);
Bool VpsLib_platformIsTda3xxFamilyBuild(void);

int32_t VpsLib_issCommonInit(const VpsLib_PlatformData *platData);

int32_t VpsLib_issCommonDeInit(Ptr arg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsLibInitParams_init(VpsLib_InitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isAddrTransReq  = (UInt32) FALSE;
        initPrms->virtBaseAddr    = 0U;
        initPrms->physBaseAddr    = 0U;
        initPrms->isCacheOpsReq   = (UInt32) FALSE;
        initPrms->isCacheFlushReq = (UInt32) FALSE;
        BspUtils_memset(&initPrms->irqParams, 0, sizeof (VpsLib_IrqParams));
    #if defined (VPS_VIP1_BUILD)
        initPrms->irqParams.vipIrqNum[0U] = CSL_INTC_EVENTID_VIP1INT0;
    #endif
    #if defined (VPS_VIP2_BUILD)
        initPrms->irqParams.vipIrqNum[1U] = CSL_INTC_EVENTID_VIP2INT0;
    #endif
    #if defined (VPS_VIP3_BUILD)
        initPrms->irqParams.vipIrqNum[2U] = CSL_INTC_EVENTID_VIP3INT0;
    #endif
    #if defined (VPS_VPE_BUILD)
        initPrms->irqParams.vpeIrqNum    = CSL_INTC_EVENTID_VPEINT0;
    #endif
    #if defined (VPS_DSS_BUILD)
        initPrms->irqParams.dssIrqNum    = CSL_INTC_EVENTID_DSS_DISPC;
    #endif
    #if defined (VPS_CAL_BUILD)
        initPrms->irqParams.calIrqNum    = CSL_CAL_IRQ_NUM;
    #endif
    #if defined (VPS_ISS_BUILD)
        initPrms->irqParams.issIrqNum    = CSL_ISS_IRQ0_NUM;
    #endif

    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_COMMON_H_ */
