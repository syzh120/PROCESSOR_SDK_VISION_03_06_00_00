/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vpshal_vpdma.c
 *
 *  \brief HAL implementation for VPDMA
 *  This file implements the HAL APIs of the VPS VPDMA module
 *
 */

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
#include <ti/csl/cslr_vpdma.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/src/vpslib/hal/vpshal_vipTop.h>
#endif
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpeTop.h>
#endif
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>

#include <ti/drv/vps/src/vpslib/hal/src/vpshal_vpdmaPriv.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshal_vpdmaFirmwareTda2xx_v288.h>
#include <ti/drv/vps/src/vpslib/hal/src/vpshal_vpdmaFirmwareTda2xx_v1B8.h>
#if defined (SOC_TDA3XX)
#include <ti/drv/vps/src/vpslib/hal/src/vpshalVpdmaDefaultsTda3xx.h>
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_AM574x)
#include <ti/drv/vps/src/vpslib/hal/src/vpshalVpdmaDefaultsTda2xx.h>
#endif
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
#include <ti/drv/vps/src/vpslib/hal/src/vpshalVpdmaDefaultsTI814x.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Macros required if descriptors are in virtual memory. */
#define VPSHAL_VPDMA_ENABLE_ADDR_TRANS

/** \brief Descriptor memory Size for the vpdma firmware in bytes */
#define VPSHAL_VPDMA_MAX_FIRMWARE_SIZE (4U * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsHal_VpdmaInfo
 *  \brief Structure containing Instance Information for each VPDMA Instance.
 *         Primarily baseAddress for the VPDMA instance.
 */
typedef struct
{
    UInt32                      halId;
    /**< Instance ID of VPDMA */

    UInt32                      openCnt;
    /**< Number of handles opened */

    UInt32                      baseAddr;
    /**< Base address for the current instance */

    Vpdma_TraceObj              listTraceObj;
    /**< store trace information for all the lists */

    VpsHal_Handle               vipTopHandle;
    /**< VPE HAL ID if this is VIP_VPDMA, else set to 0 */

    VpsHal_Handle               vpeTopHandle;
    /**< VPE HAL ID if this is VPE_VPDMA, else set to 0 */

    VpsHal_VpdmaFirmwareVersion ver;
    /**< VPDMA Firware version to used #VpsHal_VpdmaFirmwareVersion */
} VpsHal_VpdmaInfo;

/**
 *  struct VpsHal_Vpdma
 *  \brief Handle structure for all instances of VPDMA HAL
 */
typedef struct
{
    UInt32 numInst;
    /**< Num instances opened in HAL Init */
    Bool   isAddrTransReq;
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
     *   address to be programmed to the hardware. */
    UInt32           virtBaseAddr;
    /**< Virtual memory base address. */
    UInt32           physBaseAddr;
    /**< Physical memory base address. */
    Bool             isCacheOpsReq;
    /**< This will enable cache flush and invalidate operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    Bool             isCacheFlushReq;
    /**< This will enable cache flush operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *   In case of write-through cache mode, this flag could be set to FALSE
     *   to save cycles as flush operation is not required in write-through
     *   mode.
     *   This parameter is valid/used only if isCacheOpsReq is TRUE.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    VpsHal_VpdmaInfo topObj[VPSHAL_VPDMA_MAX_INST];
    /**< Instance list for maximum supported instances */
} VpsHal_Vpdma;

/**
 *  struct Vpdma_ChannelInfo
 *  \brief This structure keeps track of the channel information like channel
 *  number, direction of the channel, data type supported on the channel etc.
 *  When client of the VPDMA asks to create data descriptor in the memory, VPDMA
 *  HAL will fill up the memory with these default information
 *
 */
typedef struct
{
    VpsHal_VpdmaChannel    chNum;
    /**< VPDMA Channel Number */
    UInt32                 clientCtrlReg;
    /**< Register into which frame start event for channel can be set */
    VpsHal_VpdmaMemoryType memType;
    /**< Type of the memory from which data can be taken for this channel
     *   ---- Can we assume all 422p paths will uPossible value for this fields
     *   are 0 for 1D and 1 for 2D memory se non-tiled memory ---- */
    UInt8                  assigned;
    /**< Flag to indicate whether channel is free or not. This flag will
     *   be used for free channel only */
} Vpdma_ChannelInfo;

/**
 *  struct Vpdma_PathInfo
 *  \brief This structure keeps track of the channel information like channel
 *  number, direction of the channel, data type supported on the channel etc.
 *  When client of the VPDMA asks to create data descriptor in the memory, VPDMA
 *  HAL will fill up the memory with these default information
 *
 */
typedef struct
{
    VpsHal_VpdmaPath vpdmaPath;
    /**< VPDMA Path */
    UInt32           isTiledDataSupported;
    /**< Flag to indicate whether tiled data can be supported on this channel */
    UInt32           tiledLineSize;
    /**< Line size in terms of bytes for tiled data */
    UInt32           lineSize;
    /**< Line size in terms of bytes for non-tiled data or pixels for grpx
     *data*/
    UInt32           enhancedLineSize;
    /**< Line size in terms of bytes for non-tiled data or pixels for grpx data
     *   Valid only for PG's version greater than 2.0 (Both Ce and Ne)*/
} Vpdma_PathInfo;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * vpdmaHalObj: VPDMA TOP HAL object containing all VPDMA instances
 */
#ifdef VPS_DV_BUILD
DO_PRAGMA_SECTION_INIT(vpdmaHalObj, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpdmaChInfo, user_ocmc_ram)
DO_PRAGMA_SECTION_INIT(gVpdmaPathInfo, user_ocmc_ram)
#endif
VpsHal_Vpdma             vpdmaHalObj;

static Vpdma_ChannelInfo gVpdmaChInfo[VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS] =
    VPSHAL_VPDMA_DEFAULT_CHANNEL_INFO;
static Vpdma_PathInfo    gVpdmaPathInfo[VPSHAL_VPDMA_MAX_PATH] =
    VPSHAL_VPDMA_DEFAULT_PATH_INFO;
static inline UInt32 VpsHal_vpdmaVirtToPhy(Ptr virt);
/* static inline UInt32 VpsHal_vpdmaPhyToVirt(Ptr phys); */

static Vpdma_Fvid2DTmapping
    gDataTypeMapping[VPSHAL_VPDMA_FVID2_DT_MAPPING_SIZE] =
    VPSHAL_VPDMA_FVID2_DT_MAPPING;

/* TODO: Make this similar to Scaler HAL constant section */
#ifdef VPS_DV_BUILD
DO_PRAGMA_SECTION_INIT(gVpsHal_VpdmaFirmware_1B8, user_ocmc_ram)
__align(32) const UInt16 gVpsHal_VpdmaFirmware_1B8[] = VPSHAL_VPDMAFIRMWARE_1B8;
#else
/* Align firmware with that of VPDMA requirement. */
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32)
#else
#pragma DATA_ALIGN(gVpsHal_VpdmaFirmware_1B8, 32)
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16      gVpsHal_VpdmaFirmware_1B8[] = VPSHAL_VPDMAFIRMWARE_1B8;
#endif

#ifdef VPS_DV_BUILD
DO_PRAGMA_SECTION_INIT(gVpsHal_VpdmaFirmware_288, user_ocmc_ram)
__align(32) const UInt16 gVpsHal_VpdmaFirmware_288[] = VPSHAL_VPDMAFIRMWARE_288;
#else
/* Align firmware with that of VPDMA requirement. */
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32)
#else
#pragma DATA_ALIGN(gVpsHal_VpdmaFirmware_288, 32)
#endif
#endif  /* #ifdef __cplusplus */
static const UInt16      gVpsHal_VpdmaFirmware_288[] = VPSHAL_VPDMAFIRMWARE_288;
#endif

/* Align descriptor memory with that of VPDMA requirement. */
/* Place the descriptor in non-cached section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(".bss:extMemNonCache:vpdma");
#else
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(VPSHAL_VPDMA_DESC_BYTE_ALIGN) DATA_SECTION(".bss:extMemNonCache:vpdma")
#else
#pragma DATA_ALIGN(gVpsHalVpdmaFirmware, VPSHAL_VPDMA_DESC_BYTE_ALIGN);
#pragma DATA_SECTION(gVpsHalVpdmaFirmware,".bss:extMemNonCache:vpdma");
#endif
#endif  /* #ifdef __cplusplus */
static UInt8             gVpsHalVpdmaFirmware[VPSHAL_VPDMA_MAX_FIRMWARE_SIZE];
/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  VpsHal_vpdmaInit
 *  \brief VPDMA HAL init function.
 *  This function should be called before calling any of VPDMA HAL API's.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param instPrms         Pointer to #VpsHal_VpdmaInstParams.
 *  \param arg                Not used currently. Meant for future purpose.
 *
 *  \return                   TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpdmaInit(UInt32                        numInst,
                       const VpsHal_VpdmaInstParams *instPrms,
                       Ptr                           arg)
{
    UInt32 i;

    /* TODO: GT_assert( VpsHalTrace, instPrms != NULL); */

    /*MISRA.PTR.ARITH */
    vpdmaHalObj.numInst         = numInst;
    vpdmaHalObj.isAddrTransReq  = instPrms[0U].isAddrTransReq;
    vpdmaHalObj.virtBaseAddr    = instPrms[0U].virtBaseAddr;
    vpdmaHalObj.physBaseAddr    = instPrms[0U].physBaseAddr;
    vpdmaHalObj.isCacheOpsReq   = (Bool) instPrms[0U].isCacheOpsReq;
    vpdmaHalObj.isCacheFlushReq = (Bool) instPrms[0U].isCacheFlushReq;
    for (i = 0; i < numInst; i++)
    {
        /*MISRA.PTR.ARITH */
        vpdmaHalObj.topObj[i].halId   = instPrms[i].halId;
        vpdmaHalObj.topObj[i].openCnt = 0;
        /*MISRA.PTR.ARITH */
        vpdmaHalObj.topObj[i].baseAddr     = instPrms[i].baseAddr;
        vpdmaHalObj.topObj[i].vipTopHandle = NULL;
        vpdmaHalObj.topObj[i].vpeTopHandle = NULL;
        vpdmaHalObj.topObj[i].ver          = VPSHAL_VPDMA_NO_FIRMWARE_LOADED;

        VpsHal_vpdmaSetTopHandle(&vpdmaHalObj.topObj[i]);
        BspUtils_memset(
            &vpdmaHalObj.topObj[i].listTraceObj,
            0U,
            sizeof (vpdmaHalObj.topObj[i].listTraceObj));
    }

    return BSP_SOK;
}

/**
 *  VpsHal_vpdmaDeInit
 *  \brief VPDMA HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpdmaDeInit(Ptr arg)
{
    UInt32 i;
    for (i = 0; i < VPSHAL_VPDMA_MAX_INST; i++)
    {
        /* TODO: GT_assert( VpsHalTrace, vpdmaHalObj.topObj[i].openCnt == 0); */
        vpdmaHalObj.topObj[i].halId        = 0;
        vpdmaHalObj.topObj[i].openCnt      = 0;
        vpdmaHalObj.topObj[i].baseAddr     = 0;
        vpdmaHalObj.topObj[i].vipTopHandle = NULL;
        vpdmaHalObj.topObj[i].vpeTopHandle = NULL;
    }
    vpdmaHalObj.numInst = 0;

    return BSP_SOK;
}

/**
 *  VpsHal_vpdmaOpen
 *  \brief Returns the handle to the requested VPDMA instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the VPDMA HAL
 *  configuration APIs.
 *
 *  VpsHal_vpdmaInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms      VpsHal_VpdmaOpenParams
 *
 *  \return              success     VPDMA instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vpdmaOpen(const VpsHal_VpdmaOpenParams *openPrms)
{
    VpsHal_Handle     returnHandle = NULL;
    /* Contains the value to be returned */
    UInt32            i;
    Int32             retVal = BSP_SOK;
    UInt32            vpdmaFirmwareSize;
    VpsHal_VpdmaInfo *vpdmaInfo = NULL;
    UInt16           *vpdmaFirmwareSrc;
    UInt8            *vpdmaFirmware;

    /* TODO: GT_assert( VpsHalTrace, openPrms.numInst == 0); */
    /* TODO: GT_assert( VpsHalTrace, vpdmaHalObj.numInst != 0); */
    /* TODO: GT_assert( VpsHalTrace, halId < VPSHAL_VPDMA_INST_ID_MAX); */
    if (openPrms->halId >= VPSHAL_VPDMA_INST_ID_MAX)
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        for (i = 0U; i < vpdmaHalObj.numInst; i++)
        {
            vpdmaInfo = &(vpdmaHalObj.topObj[i]);
            if (openPrms->halId == vpdmaInfo->halId)
            {
                vpdmaInfo->openCnt++;
                break;
            }
        }
    }

    /* TODO: Check if init to zero works */
    if ((vpdmaInfo != NULL) && (1 == vpdmaInfo->openCnt) && (BSP_SOK == retVal))
    {
        VpsHal_vpdmaClkEn((VpsHal_Handle) vpdmaInfo, (UInt32) TRUE);
        if (VPSHAL_VPDMA_NO_FIRMWARE_LOADED == vpdmaInfo->ver)
        {
            /* load VPDMA firmware */
            vpdmaFirmwareSize = 0U;
            vpdmaFirmwareSrc  = VpsHal_vpdmaGetFirmwareAddr(
                openPrms->ver,
                &vpdmaFirmwareSize);

            /* TODO: GT_assert (VpsHalTrace, vpdmaFirmwareSize <=
             *                      VPSHAL_VPDMA_MAX_FIRMWARE_SIZE); */
            if (vpdmaFirmwareSize <= VPSHAL_VPDMA_MAX_FIRMWARE_SIZE)
            {
                vpdmaFirmware = gVpsHalVpdmaFirmware;
            }
            else
            {
                vpdmaFirmware = NULL;
                retVal        = BSP_EFAIL;
            }

            if (BSP_SOK == retVal)
            {
                BspUtils_memcpy(vpdmaFirmware, vpdmaFirmwareSrc,
                                vpdmaFirmwareSize);

                retVal = VpsHal_vpdmaLoadFirmware(vpdmaInfo, vpdmaFirmware, 0);

                vpdmaFirmware = NULL;
            }
            if (BSP_SOK == retVal)
            {
                vpdmaInfo->ver = openPrms->ver;
                /* set the background color for RGB */
                VpsHal_vpdmaSetRgbBackgroundColor(
                    (VpsHal_Handle) (vpdmaInfo),
                    (UInt32)
                    VPS_CFG_VPDMA_ARGB_BKCOLOR);
            }
        }
    }
    if ((vpdmaInfo != NULL) && (openPrms->ver != vpdmaInfo->ver) &&
        (BSP_SOK == retVal))
    {
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        returnHandle = ((VpsHal_Handle) (vpdmaInfo));
    }

    return returnHandle;
}

/**
 *  VpsHal_vpdmaClose
 *  \brief Closes specified instance of VPDMA HAL
 *  VpsHal_vpdmaInit and VpsHal_vpdmaOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vpdmaOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpdmaClose(VpsHal_Handle handle)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* TODO: GT_assert( VpsHalTrace, NULL != handle); */
    /* TODO: GT_assert( VpsHalTrace, vpdmaHalObj.numInst != 0); */
    /* TODO: GT_assert( VpsHalTrace, halId < VPSHAL_NUM_VPDMA_HAL_INST); */

    if (0 == vpdmaInfo->openCnt)
    {
        retval = BSP_EFAIL;
    }
    else
    {
        vpdmaInfo->openCnt--;
        if (0 == vpdmaInfo->openCnt)
        {
            VpsHal_vpdmaClkEn(handle, (UInt32) FALSE);
            vpdmaInfo->ver = VPSHAL_VPDMA_NO_FIRMWARE_LOADED;
        }
    }
    return retval;
}

/**
 *  VpsHal_vpdmaGetClient
 *  \brief Function to map the channel number to client number.
 *
 *  \param channel          #VpsHal_VpdmaChannel
 *
 *  \return                 #VpsHal_VpdmaClient
 */
VpsHal_VpdmaClient VpsHal_vpdmaGetClient(VpsHal_VpdmaChannel channel)
{
    VpsHal_VpdmaClient client = VPSHAL_VPDMA_CLIENT_INVALID;

    if ((channel > VPSHAL_VPDMA_CHANNEL_INVALID) &&
        (channel < VPSHAL_VPDMA_CHANNEL_NUM_CHANNELS))
    {
        if (((channel >= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC0) &&
             (channel <= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTA_SRC15)) ||
            ((channel == VPSHAL_VPDMA_CHANNEL_S0_PORTB_LUMA) ||
             (channel == VPSHAL_VPDMA_CHANNEL_S0_PORTB_RGB)))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_LO_Y;
        }
        else if (((channel >= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC0) &&
                  (channel <= VPSHAL_VPDMA_CHANNEL_S0_MULT_PORTB_SRC15)) ||
                 (channel == VPSHAL_VPDMA_CHANNEL_S0_PORTB_CHROMA))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_LO_UV;
        }
        else if ((channel == VPSHAL_VPDMA_CHANNEL_S0_PORTA_LUMA) ||
                 (channel == VPSHAL_VPDMA_CHANNEL_S0_PORTA_RGB))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_UP_Y;
        }
        else if (channel == VPSHAL_VPDMA_CHANNEL_S0_PORTA_CHROMA)
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_UP_UV;
        }
        else if (((channel >= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC0) &&
                  (channel <= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTA_SRC15)) ||
                 ((channel == VPSHAL_VPDMA_CHANNEL_S1_PORTB_LUMA) ||
                  (channel == VPSHAL_VPDMA_CHANNEL_S1_PORTB_RGB)))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_LO_Y;
        }
        else if (((channel >= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC0) &&
                  (channel <= VPSHAL_VPDMA_CHANNEL_S1_MULT_PORTB_SRC15)) ||
                 (channel == VPSHAL_VPDMA_CHANNEL_S1_PORTB_CHROMA))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_LO_UV;
        }
        else if ((channel == VPSHAL_VPDMA_CHANNEL_S1_PORTA_LUMA) ||
                 (channel == VPSHAL_VPDMA_CHANNEL_S1_PORTA_RGB))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_UP_Y;
        }
        else if (channel == VPSHAL_VPDMA_CHANNEL_S1_PORTA_CHROMA)
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_UP_UV;
        }
        else if ((channel >= VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC0) &&
                 (channel <= VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCA_SRC15))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_ANC_A;
        }
        else if ((channel >= VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC0) &&
                 (channel <= VPSHAL_VPDMA_CHANNEL_S0_MULT_ANCB_SRC15))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S0_ANC_B;
        }
        else if ((channel >= VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC0) &&
                 (channel <= VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCA_SRC15))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_ANC_A;
        }
        else if ((channel >= VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC0) &&
                 (channel <= VPSHAL_VPDMA_CHANNEL_S1_MULT_ANCB_SRC15))
        {
            client = VPSHAL_VPDMA_CLIENT_VIP_S1_ANC_B;
        }
        else
        {
            /* TODO: GT_assert(VpsHalTrace, FALSE); */
        }
    }

    return (client);
}

/**
 *  VpsHal_vpdmaCreateOutBoundDataDesc
 *  \brief Function to create Out Bound Data descriptor from the given
 *  parameters and in the given contiguous memory. Memory pointer given must
 *  contain physically contiguous memory because VPDMA works with that only.
 *
 *  \param memPtr           Pointer to physically contiguous memory into
 *                          which descriptor will be created
 *  \param descInfo         Pointer to structure containing out bound data
 *                          descriptor parameters
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaCreateOutBoundDataDesc(
    Ptr memPtr,
    const VpsHal_VpdmaOutDescParams *
    descInfo)
{
    volatile VpsHal_VpdmaOutDataDesc *dataDesc;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != descInfo)); */
    /* TODO: GT_assert(VpsHalTrace, (0U == ((UInt32)(descInfo->lineStride) & */
    /* TODO:               (VPSHAL_VPDMA_LINE_STRIDE_ALIGN - 1U)))); */

    dataDesc = (volatile VpsHal_VpdmaOutDataDesc *) memPtr;

    dataDesc->descType    = VPSHAL_VPDMA_PT_DATA;
    dataDesc->dataType    = (UInt32) descInfo->dataType;
    dataDesc->memType     = descInfo->memType;
    dataDesc->direction   = VPSHAL_VPDMA_OUTBOUND_DATA_DESC;
    dataDesc->channel     = (UInt32) descInfo->channel;
    dataDesc->nextChannel = (UInt32) descInfo->nextChannel;
    dataDesc->lineStride  = descInfo->lineStride;
    dataDesc->evenSkip    = dataDesc->oddSkip = (UInt32) descInfo->lineSkip;
    dataDesc->notify      = descInfo->notify;
    dataDesc->priority    = descInfo->priority;
    dataDesc->maxWidth    = descInfo->maxWidth;
    dataDesc->maxHeight   = descInfo->maxHeight;
    if (TRUE == descInfo->is1DData)
    {
        dataDesc->oneD = 1;
    }
    else
    {
        dataDesc->oneD = 0;
    }

    /* Reset unused fields to 0 */
    dataDesc->useDescReg      = 0U;
    dataDesc->dropData        = 0U;
    dataDesc->writeDesc       = 0U;
    dataDesc->outDescAddress  = 0U;
    dataDesc->clientSpecific1 = 0U;
    dataDesc->clientSpecific2 = 0U;
    dataDesc->descSkip        = 0U;
    dataDesc->reserved1       = dataDesc->reserved2 = 0U;
    dataDesc->reserved3       = dataDesc->reserved4 = 0U;
    dataDesc->reserved5       = dataDesc->reserved6 = 0U;
    dataDesc->reserved7       = 0U;
    return (0);
}

/**
 *  VpsHal_vpdmaCreateInBoundDataDesc
 *  \brief Function to create In Bound Data descriptor from the given parameters
 *  and in the given contiguous memory. Memory pointer given must contain
 *  physically contiguous memory because VPDMA works with that only.
 *
 *  \param memPtr           Pointer to physically contiguous memory into
 *                          which descriptor will be created
 *  \param descInfo         Pointer to structure containing in bound data
 *                          descriptor parameters
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaCreateInBoundDataDesc(
    Ptr memPtr,
    const VpsHal_VpdmaInDescParams *
    descInfo)
{
    volatile VpsHal_VpdmaInDataDesc *dataDesc = NULL;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != descInfo)); */
    /* TODO: GT_assert(VpsHalTrace, (0U == ((UInt32)(descInfo->lineStride) & */
    /* TODO:               (VPSHAL_VPDMA_LINE_STRIDE_ALIGN - 1U)))); */

    dataDesc = (volatile VpsHal_VpdmaInDataDesc *) memPtr;

    dataDesc->descType        = VPSHAL_VPDMA_PT_DATA;
    dataDesc->channel         = descInfo->channel;
    dataDesc->dataType        = descInfo->dataType;
    dataDesc->transferHeight  = descInfo->transHeight;
    dataDesc->transferWidth   = descInfo->transWidth;
    dataDesc->frameHeight     = descInfo->frameHeight;
    dataDesc->frameWidth      = descInfo->frameWidth;
    dataDesc->horizontalStart = descInfo->startX;
    dataDesc->verticalStart   = descInfo->startY;
    dataDesc->lineStride      = descInfo->lineStride;
    dataDesc->evenSkip        = dataDesc->oddSkip = descInfo->lineSkip;
    dataDesc->nextChannel     = descInfo->nextChannel;
    dataDesc->memType         = descInfo->memType;
    dataDesc->direction       = VPSHAL_VPDMA_INBOUND_DATA_DESC;
    dataDesc->priority        = descInfo->priority;
    dataDesc->notify          = descInfo->notify;
    dataDesc->priority        = descInfo->priority;
    if (TRUE == descInfo->is1DData)
    {
        dataDesc->oneD = 1;
    }
    else
    {
        dataDesc->oneD = 0;
    }

    /* Reset unused fields to 0 */
    dataDesc->mosaicMode      = 0U;
    dataDesc->clientSpecific1 = 0U;
    dataDesc->clientSpecific2 = 0U;
    dataDesc->reserved1       = dataDesc->reserved2 = dataDesc->reserved3 = 0;
    return (0);
}

Int32 VpsHal_vpdmaParseWriteDesc(const void                  *memPtr,
                                 VpsHal_VpdmaWriteDescParams *descInfo)
{
    const VpsHal_VpdmaInDataDesc *dataDesc = NULL;
    UInt32 wrDescAddr = (UInt32) memPtr;
    UInt32 tempAddr   = 0U;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != descInfo)); */
    /* TODO: GT_assert(VpsHalTrace, (0U == ((UInt32)(descInfo->lineStride) & */
    /* TODO:               (VPSHAL_VPDMA_LINE_STRIDE_ALIGN - 1U)))); */

    descInfo->isValid = TRUE;
    tempAddr          = wrDescAddr + 16U;
    if ((VPSHAL_VPDMA_ERR_PATTERN == *(volatile UInt32 *) wrDescAddr) ||
        (VPSHAL_VPDMA_ERR_PATTERN == *(volatile UInt32 *) (tempAddr)))
    {
        descInfo->isValid = FALSE;
    }

    dataDesc = (const VpsHal_VpdmaInDataDesc *) memPtr;

    descInfo->channel     = (VpsHal_VpdmaChannel) dataDesc->channel;
    descInfo->dataType    = (VpsHal_VpdmaChanDT) dataDesc->dataType;
    descInfo->transHeight = dataDesc->transferHeight;
    descInfo->transWidth  = dataDesc->transferWidth;
    descInfo->frameHeight = dataDesc->frameHeight;
    descInfo->frameWidth  = dataDesc->frameWidth;
    descInfo->startX      = dataDesc->horizontalStart;
    descInfo->startY      = dataDesc->verticalStart;
    descInfo->lineStride  = dataDesc->lineStride;
    descInfo->lineSkip    = (VpsHal_VpdmaLineSkip) dataDesc->evenSkip;
    descInfo->nextChannel = (VpsHal_VpdmaChannel) dataDesc->nextChannel;
    descInfo->memType     = (VpsHal_VpdmaMemoryType) dataDesc->memType;
    descInfo->priority    = (VpsHal_VpdmaDataDescPrio) dataDesc->priority;
    descInfo->notify      = dataDesc->notify;
    if (dataDesc->oneD == 1)
    {
        descInfo->is1DData = TRUE;
    }
    else
    {
        descInfo->is1DData = FALSE;
    }
    descInfo->fid        = dataDesc->fieldId;
    descInfo->bufferAddr = (Ptr) dataDesc->address;

    return (0);
}

/**
 *  VpsHal_vpdmaCreateSOCHCtrlDesc
 *  \brief Function to create Sync On Channel Control Descriptor in the
 *  given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param chNum            Channel Number to sync on
 *  \return                 None
 */
void VpsHal_vpdmaCreateSOCHCtrlDesc(Ptr                 memPtr,
                                    VpsHal_VpdmaChannel chNum)
{
    volatile VpsHal_VpdmaSyncOnChannelDesc *socDesc = NULL;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    socDesc            = (volatile VpsHal_VpdmaSyncOnChannelDesc *) memPtr;
    socDesc->descType  = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    socDesc->ctrl      = (UInt32) VPSHAL_VPDMA_CDT_SOCH;
    socDesc->channel   = (UInt32) chNum;
    socDesc->reserved1 = socDesc->reserved2 = 0U;
    socDesc->reserved3 = socDesc->reserved4 = 0U;
    socDesc->reserved5 = 0U;
}

/**
 *  VpsHal_vpdmaCreateCCISCtrlDesc
 *  Function to create a Change client interrupt source control descriptor
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param channelNum       Channel whose interrupt is to be changed
 *  \param event            event to which interrupt is to be changed
 *  \param lineCount        Line Count
 *  \param pixCount         Pixel Count
 *  \return                 None
 */
void VpsHal_vpdmaCreateCCISCtrlDesc(Ptr                  memPtr,
                                    VpsHal_VpdmaChannel  channelNum,
                                    VpsHal_VpdmaSocEvent event,
                                    UInt16               lineCount,
                                    UInt16               pixCount)
{
    volatile VpsHal_VpdmaChangeClientIntSrc *ccisDesc = NULL;

    GT_assert(VpsHalTrace, NULL != memPtr);
    ccisDesc = (volatile VpsHal_VpdmaChangeClientIntSrc *) memPtr;

    ccisDesc->lineCount  = lineCount;
    ccisDesc->pixelCount = pixCount;
    ccisDesc->event      = (UInt32) event;
    ccisDesc->ctrl       = (UInt32) VPSHAL_VPDMA_CDT_INTR_CHANGE;
    ccisDesc->source     = (UInt32) channelNum;
    ccisDesc->descType   = (UInt32) VPSHAL_VPDMA_PT_CONTROL;

    ccisDesc->reserved1 = ccisDesc->reserved2 = 0U;
    ccisDesc->reserved3 = ccisDesc->reserved4 = 0U;
}

/**
 *  VpsHal_vpdmaCreateSOCCtrlDesc
 *  \brief Function to create a Sync on Client control Descriptor
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param chNum            Channel whose interrupt is to be changed
 *  \param event            event to which interrupt is to be changed
 *  \param lineCount        Line Count
 *  \param pixCount         Pixel Count
 *  \return                 None
 */
void VpsHal_vpdmaCreateSOCCtrlDesc(Ptr                  memPtr,
                                   VpsHal_VpdmaChannel  chNum,
                                   VpsHal_VpdmaSocEvent event,
                                   UInt16               lineCount,
                                   UInt16               pixCount)
{
    volatile VpsHal_VpdmaSyncOnClientDesc *socDesc = NULL;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    socDesc             = (volatile VpsHal_VpdmaSyncOnClientDesc *) memPtr;
    socDesc->descType   = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    socDesc->ctrl       = (UInt32) VPSHAL_VPDMA_CDT_SOC;
    socDesc->event      = (UInt32) event;
    socDesc->channel    = (UInt32) chNum;
    socDesc->lineCount  = lineCount;
    socDesc->pixelCount = pixCount;
    socDesc->reserved1  = socDesc->reserved2 = 0U;
    socDesc->reserved3  = socDesc->reserved4 = 0U;
}

/**
 *  VpsHal_vpdmaCreateDummyDesc
 *  \brief Function to create Dummy descriptor of 4 words in the given memory
 *
 *  \param memPtr           Pointer to the memory in which dummy
 *                          descriptor is to be created
 *  \return                 None
 */
void VpsHal_vpdmaCreateDummyDesc(Ptr memPtr)
{
    GT_assert(VpsHalTrace, NULL != memPtr);

    VpsHal_vpdmaCreateConfigDesc(memPtr,
                                 VPSHAL_VPDMA_CONFIG_DEST_MMR,
                                 VPSHAL_VPDMA_CPT_BLOCK_SET,
                                 VPSHAL_VPDMA_CCT_DIRECT,
                                 (UInt32) 0,
                                 NULL,
                                 NULL,
                                 (UInt16) 0);
}

/**
 *  VpsHal_vpdmaSetSyncList
 *  \brief Function to register bit for the Sync on Register event.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List Number
 *  \return                 None
 */
void VpsHal_vpdmaSetSyncList(VpsHal_Handle handle, UInt8 listNum)
{
    VpsHal_VpdmaInfo *vpdmaInfo;
    UInt32 tempAddr = 0U;

    vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* This is W1TS register, write 1 to set and writing 0 will
     * have no effect. */

    tempAddr = vpdmaInfo->baseAddr + (UInt32) VPDMA_LIST_STAT_SYNC;
    HW_WR_REG32(tempAddr, ((UInt32) 0x1U << listNum));
}

/**
 *  VpsHal_vpdmaCreateConfigDesc
 *  \brief Function to create the configuration descriptor in the given memory.
 *
 *  \param memPtr           Pointer memory in which config descriptor is
 *                          to be created
 *  \param dest             Config descriptor destination
 *  \param clss             This indicates whether payload is blocks of
 *                          data or single contiguous block.
 *  \param direct           This indicates whether payload is stored in
 *                          contiguous with the descriptor or stored in some
 *                          other memory location
 *  \param payloadSize      Payload size in bytes
 *  \param payloadAddr      Pointer to payload memory for indirect
 *                          configuration
 *  \param destAddr         Destination address offset used for block type
 *                          configuration class. Not used for address set.
 *  \param dataSize         NONE
 *
 *  \return                 None
 */
void VpsHal_vpdmaCreateConfigDesc(Ptr                           memPtr,
                                  VpsHal_VpdmaConfigDest        dest,
                                  VpsHal_VpdmaConfigPayloadType classVal,
                                  VpsHal_VpdmaConfigCmdType     direct,
                                  UInt32                        payloadSize,
                                  Ptr                           payloadAddr,
                                  Ptr                           destAddr,
                                  UInt16                        dataSize)
{
    volatile VpsHal_VpdmaConfigDesc *configDesc = NULL;
    UInt32 alignment = 0U;

    GT_assert(VpsHalTrace, NULL != memPtr);
    GT_assert(VpsHalTrace, (VPSHAL_VPDMA_CCT_INDIRECT == direct) ||
              (VPSHAL_VPDMA_CCT_DIRECT == direct));
    GT_assert(VpsHalTrace, (VPSHAL_VPDMA_CPT_ADDR_DATA_SET == classVal) ||
              (VPSHAL_VPDMA_CPT_BLOCK_SET == classVal));

    /* For dummy descriptor, NULL is passed, so don't translate!! */
    if (payloadAddr != NULL)
    {
        payloadAddr = (Ptr) VpsHal_vpdmaVirtToPhy(payloadAddr);
    }
    configDesc              = (volatile VpsHal_VpdmaConfigDesc *) memPtr;
    configDesc->descType    = (UInt32) VPSHAL_VPDMA_PT_CONFIG;
    configDesc->destination = (UInt32) dest;
    configDesc->classVal    = classVal;
    configDesc->direct      = direct;
    configDesc->reserved1   = 0U;
    /* Payload size is in terms of 128 bit word. memSize is in terms of
     * words so divide it by word size to get 128 bit aligned size. */
    configDesc->payloadLength = (payloadSize >>
                                 VPSHAL_VPDMA_CONFIG_PAYLOAD_SIZE_SHIFT);

    /* Data Size need not be 128 bit aligned */
    configDesc->dataLength = (dataSize & VPSHAL_VPDMA_CONFIG_DATA_SIZE_MASK);

    if (VPSHAL_VPDMA_CCT_INDIRECT == direct)
    {
        alignment = ((UInt32) payloadAddr) &
                    (VPSHAL_VPDMA_CONFIG_PAYLOAD_SIZE_ALIGN - 1U);
        GT_assert(VpsHalTrace, (0U == alignment));
        configDesc->payloadAddress = (UInt32) payloadAddr;
    }

    if (VPSHAL_VPDMA_CPT_BLOCK_SET == classVal)
    {
        /* When creating dummy config descriptor, destAddr will be null,
         * so there is no assert for this error */
        if ((VPSHAL_VPDMA_CONFIG_DEST_MMR == dest) &&
            (NULL != destAddr))
        {
            configDesc->destAddr = (UInt32) destAddr;
            /* Offset should be from VPS/VIP_TOP/VPE_TOP Base address.
             * Implicit subtraction of baseAdress is done using 16b mask */
            configDesc->destAddr &= 0xFFFFU;
        }
        /*configuration descriptor is different for GRPX*/
        else if (((VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX0 == dest) ||
                  (VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX1 == dest) ||
                  (VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX2 == dest)) &&
                 (NULL != destAddr))
        {
            configDesc->destAddr = (UInt32) destAddr;
        }
        else
        {
            /* The address offset in destination needs to be in units of 128-bit
             * words. The provided destAddr offset is in bytes. Hence it needs
             * to be divided by 16 to get the correct value.
             */
            configDesc->destAddr = (((UInt32) destAddr) >>
                                    VPSHAL_VPDMA_CONFIG_PAYLOAD_SIZE_SHIFT);
        }
    }
}

/**
 *  VpsHal_vpdmaCreateSORCtrlDesc
 *  \brief Function to create Sync On Register Control Descriptor in the
 *  given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param listNum          List Number for which SOR is to be created
 *  \return                 None
 */
void VpsHal_vpdmaCreateSORCtrlDesc(Ptr memPtr, UInt8 listNum)
{
    volatile VpsHal_VpdmaSyncOnRegDesc *sorDesc = NULL;
    GT_assert(VpsHalTrace, NULL != memPtr);
    sorDesc            = (volatile VpsHal_VpdmaSyncOnRegDesc *) memPtr;
    sorDesc->descType  = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    sorDesc->ctrl      = (UInt32) VPSHAL_VPDMA_CDT_SOR;
    sorDesc->listNum   = listNum;
    sorDesc->reserved1 = sorDesc->reserved2 = 0U;
    sorDesc->reserved3 = sorDesc->reserved4 = 0U;
    sorDesc->reserved5 = 0U;
}

/**
 *  VpsHal_vpdmaCreateSICtrlDesc
 *  \brief Function to create a Send Interrupt Control Descriptor
 *  in the given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param source           Send Interrupt source possible values are 0-15
 *  \return                 None
 */
void VpsHal_vpdmaCreateSICtrlDesc(Ptr memPtr, UInt16 source)
{
    volatile VpsHal_VpdmaSendIntrDesc *siDesc = NULL;

    GT_assert(VpsHalTrace, NULL != memPtr);
    GT_assert(VpsHalTrace, source < VPSHAL_VPDMA_MAX_SI_SOURCE);

    siDesc            = (volatile VpsHal_VpdmaSendIntrDesc *) memPtr;
    siDesc->descType  = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    siDesc->ctrl      = (UInt32) VPSHAL_VPDMA_CDT_SI;
    siDesc->source    = source;
    siDesc->reserved1 = siDesc->reserved2 = 0U;
    siDesc->reserved3 = siDesc->reserved4 = 0U;
    siDesc->reserved5 = 0U;
}

/**
 *  VpsHal_vpdmaCreateRLCtrlDesc
 *  \brief Function to create Reload Control Descriptor in the given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param listNum          NONE
 *  \param rlListAddr       Address of the memory from where list is to be
 *                          reloaded
 *  \param size             Size of the reloaded list in bytes
 *  \return                 None
 */
void VpsHal_vpdmaCreateRLCtrlDesc(Ptr    memPtr,
                                  Ptr    rlListAddr,
                                  UInt32 size)
{
    volatile VpsHal_VpdmaReloadDesc *rlDesc = NULL;
    GT_assert(VpsHalTrace, NULL != memPtr);
    rlListAddr       = (Ptr) VpsHal_vpdmaVirtToPhy(rlListAddr);
    rlDesc           = (volatile VpsHal_VpdmaReloadDesc *) memPtr;
    rlDesc->descType = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    rlDesc->ctrl     = (UInt32) VPSHAL_VPDMA_CDT_RL;
    rlDesc->listSize = (size & ~(VPSHAL_VPDMA_LIST_SIZE_ALIGN - 1U)) >>
                       VPSHAL_VPDMA_LIST_SIZE_SHIFT;
    rlDesc->reloadAddr = (UInt32) rlListAddr;
    rlDesc->reserved1  = rlDesc->reserved2 = rlDesc->reserved3 = 0U;
}

/**
 *  VpsHal_vpdmaCreateAbortCtrlDesc
 *  \brief Function to create a control descriptor to Invert List Manager
 *  FID
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param channelNum       Channel whose data transfer is to be aborted
 *  \return                 None
 */
void VpsHal_vpdmaCreateAbortCtrlDesc(Ptr                 memPtr,
                                     VpsHal_VpdmaChannel channelNum)
{
    volatile VpsHal_VpdmaAbortDesc *aDesc = NULL;
    GT_assert(VpsHalTrace, NULL != memPtr);
    aDesc            = (volatile VpsHal_VpdmaAbortDesc *) memPtr;
    aDesc->descType  = (UInt32) VPSHAL_VPDMA_PT_CONTROL;
    aDesc->ctrl      = (UInt32) VPSHAL_VPDMA_CDT_ABT_CHANNEL;
    aDesc->channel   = (UInt32) channelNum;
    aDesc->reserved1 = aDesc->reserved2 = 0U;
    aDesc->reserved3 = aDesc->reserved4 = 0U;
    aDesc->reserved5 = 0U;
}

/**
 *  VpsHal_vpdmaIsValidSize
 *  \brief Function to check whether the size is valid or not for
 *         the given input path and for the given format
 *
 *  \param vpdmaPath        VPDMA Path
 *  \param isYuv422iFormat  Is the format YUV 422 interleaved?
 *                          descriptor is to be created
 *  \return                 None
 */
Int32 VpsHal_vpdmaIsValidSize(VpsHal_VpdmaPath       vpdmaPath,
                              Bool                   isYuv422iFormat,
                              VpsHal_VpdmaMemoryType memType,
                              UInt32                 width,
                              UInt32                 height)
{
    Int32  retVal = BSP_SOK;
    UInt32 lineSize;

    GT_assert(VpsHalTrace, vpdmaPath == gVpdmaPathInfo[vpdmaPath].vpdmaPath);
    if ((VPSHAL_VPDMA_MT_TILEDMEM == memType) &&
        (TRUE != gVpdmaPathInfo[vpdmaPath].isTiledDataSupported))
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    if (BSP_SOK == retVal)
    {
        /* Width and Height should not be zero */
        if ((0U == width) || (0U == height))
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Check against the minimum and maximum width and height
         * supported by VPDMA path */
        if ((width > VPSHAL_VPDMA_MAX_FRAME_WIDTH) ||
            (height > VPSHAL_VPDMA_MAX_FRAME_HEIGHT) ||
            (width < VPSHAL_VPDMA_MIN_FRAME_WIDTH) ||
            (height < VPSHAL_VPDMA_MIN_FRAME_HEIGHT))
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    if (BSP_SOK == retVal)
    {
        if (VPSHAL_VPDMA_MT_TILEDMEM == memType)
        {
            lineSize = gVpdmaPathInfo[vpdmaPath].tiledLineSize;
        }
        else
        {
            /* TODO: Assuming all versions have enhanced line size */
            lineSize = gVpdmaPathInfo[vpdmaPath].enhancedLineSize;
        }
        if (TRUE == isYuv422iFormat)
        {
            lineSize = lineSize / 2U;
        }
        if (width > lineSize)
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_vpdmaPostList
 *  \brief Function for posting the list to the VPDMA. Once posted, VPDMA will
 *  start reading and processing the list. It is interrupt protected so
 *  can be called from the interrupt context also.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List Number
 *  \param listType         List Type i.e. Normal or Self Modifying
 *  \param listAddr         Physical address of the contiguous memory
 *                          containing list
 *  \param listSize         List size in bytes
 *  \param enableCheck      Flag to indicate whether parameter check needs to
 *                          be done or not. TODO: Not used currently.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaPostList(VpsHal_Handle        handle,
                           UInt8                listNum,
                           VpsHal_VpdmaListType listType,
                           Ptr                  listAddr,
                           UInt32               listSize,
                           UInt32               enableCheck)
{
    UInt32 timeout  = 0U;
    UInt32 listAttr = 0U;
    UInt32 ltype    = (UInt32) listType;
    Int32  ret      = 0;
    UInt32 cookie;
    Vpdma_ListPostTrace *listPost;
    Vpdma_TraceObj      *listTraceObj;
    VpsHal_VpdmaInfo    *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    UInt32 listStatus = 0U;

    if (TRUE == enableCheck)
    {
        /* TODO: GT_assert( VpsHalTrace, (NULL != listAddr) ); */
        /* TODO: GT_assert( VpsHalTrace, ( 0U == ( (UInt32)listAddr & */
        /* TODO:                                  (VPSHAL_VPDMA_LIST_ADDR_ALIGN
        **/
        /* - */
        /* 1U) ) ) ); */
        /* TODO: GT_assert( VpsHalTrace, ( 0U == ( (UInt32)listSize & */
        /* TODO:                                  (VPSHAL_VPDMA_LIST_SIZE_ALIGN
        **/
        /* - */
        /* 1U) ) ) ); */
        /* TODO: GT_assert( VpsHalTrace, (listNum < VPSHAL_VPDMA_MAX_LIST) ); */
    }

    listTraceObj = &vpdmaInfo->listTraceObj;
    listAddr     = (Ptr) VpsHal_vpdmaVirtToPhy(listAddr);

    /* Number of 16 byte word in the new list of descriptors */
    listSize = (listSize & ~(VPSHAL_VPDMA_LIST_SIZE_ALIGN - 1U)) >>
               VPSHAL_VPDMA_LIST_SIZE_SHIFT;

    while ((0U == VPSHAL_VPDMA_ISREADY(vpdmaInfo->baseAddr)) &&
           (timeout < VPSHAL_VPDMA_BUSY_TIMEOUT))
    {
        timeout++;
    }

    if (0U == VPSHAL_VPDMA_ISREADY(vpdmaInfo->baseAddr))
    {
        ret = (-((int32_t) 1));
    }

    if (0 == ret)
    {
        timeout    = 0U;
        listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr,
                                             (UInt32) listNum);
        while ((0U != listStatus) &&
               (timeout < (UInt32) VPSHAL_VPDMA_BUSY_TIMEOUT))
        {
            timeout   += 1U;
            listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr,
                                                 (UInt32) listNum);
        }

        /* Disable global interrupts
         * Note: Since List is always going to be
         * Submitted from the single processor, hardware interrupts are
         * disabled. If multiple processor will submit the list, it is
         * required to take the hardware spinlock here. */
        cookie = BspOsal_disableInterrupt();

        listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr,
                                             (UInt32) listNum);
        if (0U != listStatus)
        {
            ret = (-((int32_t) 1));
        }

        if (0 == ret)
        {
            HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_LIST_NUM, (UInt32) listNum);
            HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_LIST_TYPE, ltype);
            HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_LIST_SIZE, listSize);

            /* Set the List Address */
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_LIST_ADDR,
                (UInt32) listAddr);
/* TODO: This is always defined since all header files for all firmwares are */
/* always included. */
#ifdef VPSHAL_VPDMA_DO_PID_REG_CHECK /* defined in vpshalVpdmaFirmware_vNNN.h */

            /* Post the list only when other list is not getting cleared */
            timeout = 0U;
            do
            {
                UInt32 pidRegVal, cnt;
                pidRegVal = HW_RD_REG32(
                    vpdmaInfo->baseAddr + (UInt32) VPDMA_PID);
                /* Wait for some time if other list is getting
                 * cleared by checking bit 15th of the PID register */
                if ((pidRegVal & ((UInt32) 1U << 15)) == 0)
                {
                    break;
                }

                for (cnt = 0U; cnt < VPSHAL_VPDMA_BUSY_WAIT; cnt++)
                {
                    /* wait */
                }

                timeout++;
            } while (timeout < VPSHAL_VPDMA_BUSY_TIMEOUT);

            if (timeout != 0U)
            {
                listTraceObj->listPost[listNum].listWaitCnt++;

                if (listTraceObj->listPost[listNum].maxListWait < timeout)
                {
                    listTraceObj->listPost[listNum].maxListWait = timeout;
                }
            }
#endif

            /* Set the List Attributes */
            HW_WR_REG32(vpdmaInfo->baseAddr + VPDMA_LIST_ATTR,
                        listAttr);
        }
        /* ----- Release the Hardware spinlock ----- */
        /* Enable global interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    /* Update trace */
    listPost = &(listTraceObj->listPost[listNum]);

    if (listPost->curIdx >= VPSHAL_VPDMA_MAX_TRACE_COUNT)
    {
        listPost->curIdx = 0U;
    }

    listPost->totalPosts++;
    listPost->listAddr[listPost->curIdx]  = listAddr;
    listPost->listSize[listPost->curIdx]  = listSize;
    listPost->retVal[listPost->curIdx]    = ret;
    listPost->listType[listPost->curIdx]  = listType;
    listPost->timeStamp[listPost->curIdx] = BspOsal_getCurTimeInMsec();
    listPost->curIdx++;
    if (listPost->curIdx >= VPSHAL_VPDMA_MAX_TRACE_COUNT)
    {
        listPost->curIdx = 0U;
    }

    return (ret);
}

void VpsHal_vpdmaStopList(VpsHal_Handle        handle,
                          UInt8                listNum,
                          VpsHal_VpdmaListType listType)
{
    UInt32 listAttr = 0U;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_LIST_NUM, (UInt32) listNum);
    HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_LIST_TYPE, (UInt32) listType);
    HW_SET_FIELD32(listAttr, VPDMA_LIST_ATTR_STOP, 1U);

    HW_WR_REG32(vpdmaInfo->baseAddr + VPDMA_LIST_ATTR, listAttr);

    return;
}

/**
 *  VpsHal_vpdmaPostList
 *  \brief Function for posting the list to the VPDMA. Once posted, VPDMA will
 *  start reading and processing the list. It is interrupt protected so
 *  can be called from the interrupt context also.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List Number to wait for
 *  \param timeout          Control loop-count while waiting for list to
 *                          complete. ~multiple of 1ms
 *
 *  \return                 BSP_SOK if list complete is detected,
 *                          BSP_EFAIL otherwise.
 */
Int32 VpsHal_vpdmaListWaitComplete(VpsHal_Handle handle,
                                   UInt8         listNum,
                                   UInt32        timeout)
{
    Int32  ret        = 0;
    UInt32 timeoutCnt = 0U;
    Bool   getListStatus;
    UInt32 cookie;
    VpsHal_VpdmaInfo    *vpdmaInfo;
    Vpdma_ListPostTrace *listPost;
    Vpdma_TraceObj      *listTraceObj;
    UInt32 listStatus = 0U;

    vpdmaInfo     = (VpsHal_VpdmaInfo *) handle;
    listTraceObj  = &vpdmaInfo->listTraceObj;
    getListStatus = TRUE;

    listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr,
                                         (UInt32) listNum);

    while ((0U != listStatus) &&
           (timeoutCnt < timeout))
    {
        listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr,
                                             (UInt32) listNum);
        /* ----- Delay for some time ----- */
        timeoutCnt += 1U;
        /* TODO: BspOsal_sleep(1); */

        if ((timeoutCnt > 8U) && ((Bool) TRUE == getListStatus))
        {
            getListStatus = FALSE;

            cookie = BspOsal_disableInterrupt();

            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_PID,
                (0xDEAD0000U | (listNum & (UInt32) 0xFU)));

            listStatus  = HW_RD_REG32(vpdmaInfo->baseAddr + VPDMA_PID);
            listStatus &= 0xFFFU;

            BspOsal_restoreInterrupt(cookie);

            /* Update trace */
            listPost = &(listTraceObj->listPost[listNum]);
            if (0 != listPost->curIdx)
            {
                listPost->listStatus[listPost->curIdx - 1] = listStatus;
            }
            else
            {
                listPost->listStatus[VPSHAL_VPDMA_MAX_TRACE_COUNT - 1U] =
                    listStatus;
            }
        }
    }

    listStatus = VPSHAL_VPDMA_ISLISTBUSY(vpdmaInfo->baseAddr, (UInt32) listNum);
    if (0U != listStatus)
    {
        ret = (-((int32_t) 1));
    }

    return ret;
}

/**
 *  VpsHal_vpdmaLoadFirmware
 *  \brief Load VPDMA firmware
 *
 *  This function will be called as part of VpsHal_vpdmaOpen()
 *
 *  If firmware is loaded, it will exit immediately
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param firmwareAddr     Pointer to firmware buffer. TODO: Alignment ???
 *  \param timeout          Loop-count to wait while loading. Set 0 for default.
 *
 *  \return              success     VPDMA instance's HAL handle
 *                       failure     NULL
 */
Int32 VpsHal_vpdmaLoadFirmware(VpsHal_Handle handle,
                               Ptr firmwareAddr, UInt32 timeout)
{
    Int32  ret                  = 0;
    UInt32 timeoutCnt           = 0U;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    UInt32 alignment            = 0U;
    UInt32 fwLoaded             = 0U;

    GT_assert(VpsHalTrace, handle != NULL);
    GT_assert(VpsHalTrace, NULL != firmwareAddr);
    alignment = ((UInt32) firmwareAddr & (VPSHAL_VPDMA_LIST_ADDR_ALIGN - 1U));
    GT_assert(VpsHalTrace, (0U == alignment));

    firmwareAddr = (Ptr) VpsHal_vpdmaVirtToPhy(firmwareAddr);
    if (0U == timeout)
    {
        timeout = 0xFFFFFFFFU;
    }

    GT_0trace(VpsHalTrace, GT_INFO, "*** VPDMA Firmware Loading... ***\r\n");

    fwLoaded = VPSHAL_VPDMA_FW_IS_LOADED(vpdmaInfo->baseAddr);
    if (0U != fwLoaded)
    {
        /* firmware is already loaded, no need to load again */
        GT_0trace(VpsHalTrace, GT_INFO, "VPDMA Firmware already loaded !!!\r\n");
    }
    else
    {
        GT_1trace(VpsHalTrace, GT_INFO,
                  "VPDMA Firmware Address = 0x%08x\r\n", firmwareAddr);
        GT_1trace(VpsHalTrace, GT_INFO,
                  "VPDMA Load Address     = 0x%08x\r\n",
                  vpdmaInfo->baseAddr + VPDMA_LIST_ADDR);

        /* ----- Reset VPDMA ----- */

        /* toggle VPDMA reset to load the firmware */
        VpsHal_vpdmaReset(handle, (UInt32) TRUE);
        /* TODO: BspOsal_sleep(1); */
        VpsHal_vpdmaReset(handle, (UInt32) FALSE);

        /* Load firmware in the VPDMA */
        HW_WR_REG32(
            vpdmaInfo->baseAddr + VPDMA_LIST_ADDR,
            (UInt32) firmwareAddr);

        /* Wait till firmware gets loaded */
        while ((0U == VPSHAL_VPDMA_ISREADY(vpdmaInfo->baseAddr)) &&
               (timeoutCnt < timeout))
        {
            timeoutCnt += 1U;
        }
        if (0U == VPSHAL_VPDMA_ISREADY(vpdmaInfo->baseAddr))
        {
            ret = (-((int32_t) 1));
        }
        else
        {
            ret = 0;
        }
    }

    GT_1trace(VpsHalTrace, GT_INFO,
              "VPDMA Firmware Version = 0x%08x\r\n",
              HW_RD_REG32(vpdmaInfo->baseAddr + VPDMA_PID));
    GT_1trace(VpsHalTrace, GT_INFO,
              "VPDMA List Busy Status = 0x%08x\r\n",
              HW_RD_REG32(vpdmaInfo->baseAddr + VPDMA_LIST_STAT_SYNC));
    if (0 == ret)
    {
        GT_0trace(VpsHalTrace, GT_INFO,
                  "*** VPDMA Firmware Load Success ***\r\n\r\n");
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_INFO,
                  "*** VPDMA Firmware Load ERROR!!! ***\r\n\r\n");
    }

    return (ret);
}

/**
 *  VpsHal_vpdmaSetFrameStartEvent
 *  \brief Function is used to set the frame start event for the channel/client.
 *  This function tells VPDMA to use a given source of NF to transfer data
 *  to the down stream module. VPDMA starts transfer of data at the NF
 *  signal only. If there is no NF signal, it will transfer data to the
 *  internal FIFO. When FIFO becomes full, that channel will be blocked.
 *  Upper layer should pass the channel number to set the frame
 *  start event and VPDMA HAL sets it in the client register. This VPDMA
 *  client is the one associated with the channel number. If event is to
 *  be set for multiplexed client, upper layer can pass any channel
 *  associated with that client to set frame start event
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param chanNum          Channel Number for which frame start event is
 *                          to be set
 *  \param fsEvent          Source of NF signal
 *  \param lineMode         NONE
 *  \param reqDelay         NONE
 *  \param ovlyPtr          NONE
 *  \param index            NONE
 *  \return                 None
 */
void VpsHal_vpdmaSetFrameStartEvent(VpsHal_Handle        handle,
                                    VpsHal_VpdmaChannel  chanNum,
                                    VpsHal_VpdmaFSEvent  fsEvent,
                                    VpsHal_VpdmaLineMode lineMode,
                                    UInt32               reqDelay,
                                    Ptr                  ovlyPtr,
                                    UInt32               index)
{
    UInt32           value;
    UInt32           fs  = (UInt32) fsEvent;
    volatile UInt32 *ptr = NULL;

    ptr = (volatile UInt32 *) VpsHal_vpdmaGetClientRegAdd(handle, chanNum);

    value = 0x0;
    HW_SET_FIELD32(value, VPDMA_PRI_CHROMA_CSTAT_FRAME_START, fs);
    HW_SET_FIELD32(value, VPDMA_PRI_CHROMA_CSTAT_LINE_MODE, (UInt32) lineMode);
    HW_SET_FIELD32(value, VPDMA_PRI_CHROMA_CSTAT_REQ_DELAY, reqDelay);

    if (NULL == ovlyPtr)
    {
        (*ptr) = value;
    }
    else
    {
        /* MISRA.PTR.ARITH */
        *(((UInt32 *) ovlyPtr) + index) = value;
    }
    /* TODO: LineMode should be set only to the client where chrus
     * is available */

    return;
}

/**
 *  VpsHal_vpdmaGetClientRegAdd
 *  \brief This function is used to get the base address for the client
 * registers. This address needs to pass to VPDMA to create the register
 * overlay for that client register
 *
 *  \param chanNum          Channel number for which the base address of client
 *                          reg is address.
 *  \return                 Returns the base address of the client register.
 */
Ptr VpsHal_vpdmaGetClientRegAdd(VpsHal_Handle       handle,
                                VpsHal_VpdmaChannel chanNum)
{
    VpsHal_VpdmaInfo *vpdmaInfo;
    UInt32 tempAddr = 0U;

    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, VPSHAL_VPDMA_CHANNEL_INVALID != chanNum);

    vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    tempAddr  = vpdmaInfo->baseAddr +
                (UInt32) gVpdmaChInfo[chanNum].clientCtrlReg;
    return (Ptr) (tempAddr);
}

/**
 *  VpsHal_vpdmaSetAddress
 *  \brief Function to set the buffer address and fid in the data descriptor.
 *  This function can be called from the ISR to update the buffer
 *  address and fid
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param fid              Value of FID. It must be either 0 or 1.
 *  \param bufferAddr       Buffer Address to be set in the data desc.
 *  \return                 None
 */
void VpsHal_vpdmaSetAddress(Ptr memPtr, UInt8 fid, Ptr bufferAddr)
{
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    /* TODO: GT_assert(VpsHalTrace, (0U == (((UInt32)bufferAddr & */
    /* TODO:         (VPSHAL_VPDMA_BUF_ADDR_ALIGN - 1U))))); */
    ((volatile VpsHal_VpdmaInDataDesc *) memPtr)->address =
        (UInt32) bufferAddr & VPSHAL_VPDMA_DATADESC_INBUFFERMASK;
    ((volatile VpsHal_VpdmaInDataDesc *) memPtr)->fieldId = fid;
}

/**
 *  VpsHal_vpdmaGetAddress
 *  \brief TODO:
 */
Ptr VpsHal_vpdmaGetAddress(Ptr memPtr)
{
    UInt32 bufferAddr;
    /* TODO: GT_assert(VpsHalTrace, (NULL != memPtr)); */
    /* TODO: GT_assert(VpsHalTrace, (0U == (((UInt32)bufferAddr & */
    /* TODO:         (VPSHAL_VPDMA_BUF_ADDR_ALIGN - 1U))))); */
    bufferAddr = ((volatile VpsHal_VpdmaInDataDesc *) memPtr)->address;
    /* TODO: ( (volatile VpsHal_VpdmaInDataDesc *)memPtr)->fieldId = fid; */
    return (Ptr) bufferAddr;
}

/**
 *  VpsHal_vpdmaSetDescWriteAddr
 *  \brief Function to set the descriptor write address into
 *  data descriptor. This is the address where VPDMA prepares the
 *  data descriptor. This function is used only for the outbound
 *  data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param wrDescAddr       Address of the memory where descriptors will
 *                          be written by VPDMA
 *  \return                 None
 */
void VpsHal_vpdmaSetDescWriteAddr(Ptr memPtr, Ptr wrDescAddr)
{
    /* Write err pattern using virtual addr before converting to physical */
    *(volatile UInt32 *) wrDescAddr          = VPSHAL_VPDMA_ERR_PATTERN;
    *((volatile UInt32 *) (wrDescAddr) + 4U) = VPSHAL_VPDMA_ERR_PATTERN;
    wrDescAddr = (Ptr) VpsHal_vpdmaVirtToPhy(wrDescAddr);
    ((volatile VpsHal_VpdmaOutDataDesc *) memPtr)->outDescAddress =
        (UInt32) wrDescAddr >> 5U;
}

/**
 *  VpsHal_vpdmaSetWriteDesc
 *  Function to set the write descriptor flag in out bound data
 *  descriptor. Setting this flag tells VPDMA to write data descriptor
 *  in the memory
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable           Flag to indicate whether to enable/disable
 *                          Write Descriptor
 *                          be written by VPDMA
 *  \return                 None
 */
void VpsHal_vpdmaSetWriteDesc(Ptr memPtr, UInt8 enable)
{
    GT_assert(VpsHalTrace, NULL != memPtr);
    ((volatile VpsHal_VpdmaOutDataDesc *) memPtr)->writeDesc = enable;
}

/**
 *  VpsHal_vpdmaEnableDescSkip
 *  \brief Function to enable/disable skip desc bit.
 *
 *  \param memPtr           Pointer to memory containing in bound
 *                          descriptor
 *  \param enableSkip       Flag to indicate whether to enable/disable
 *
 *  \return                 None
 */
void VpsHal_vpdmaEnableDescSkip(Ptr memPtr, UInt32 enableSkip)
{
    GT_assert(VpsHalTrace, NULL != memPtr);
    ((volatile VpsHal_VpdmaOutDataDesc *) memPtr)->descSkip = enableSkip;
}

/**
 *  VpsHal_vpdmaSetLineStride
 *  Function to set the line stride for both in/out bound data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param lineStride       Line stride in bytes between two lines
 *
 *  \return                 None
 */
void VpsHal_vpdmaSetLineStride(Ptr memPtr, UInt16 lineStride)
{
    GT_assert(VpsHalTrace, NULL != memPtr);

    /* Caution: Assuming memType bit position is same for both in and out
     * bound descriptors */
    ((volatile VpsHal_VpdmaInDataDesc *) memPtr)->lineStride = lineStride;
}

/**
 *  VpsHal_vpdmaSetMemType
 *  Function to set the memory type for both in/out bound data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param memType          Type of memory i.e. Tiled or Non-Tiled
 *
 *  \return                 None
 */
void VpsHal_vpdmaSetMemType(Ptr memPtr, VpsHal_VpdmaMemoryType memType)
{
    GT_assert(VpsHalTrace, NULL != memPtr);

    /* Caution: Assuming memType bit position is same for both in and out
     * bound descriptors */
    ((volatile VpsHal_VpdmaInDataDesc *) memPtr)->memType = memType;
}

/**
 *  VpsHal_vpdmaSetDropData
 *  Function to set the drop data flag in out bound data descriptor.
 *  When this flag is set, VPDMA will drop the captured data without
 *  storing it the memory.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable           Flag to indicate whether to enable/disable
 *                          drop data be written by VPDMA
 *  \return                 None
 */
void VpsHal_vpdmaSetDropData(Ptr memPtr, UInt8 enable)
{
    GT_assert(VpsHalTrace, NULL != memPtr);
    ((volatile VpsHal_VpdmaOutDataDesc *) memPtr)->dropData = enable;
}

/**
 *  VpsHal_vpdmaSetDescHeight
 *  Function to set the height in out bound data
 *  descriptor. This API is used to set the height in
 *  case of slice based operations.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable
 *                          Pointer to Data descriptor whose height
 *                          field needs to be modified
 *  \return                 None
 */
void VpsHal_vpdmaSetDescHeight(Ptr                             memPtr,
                               const VpsHal_VpdmaInDescParams *descInfo)
{
    volatile VpsHal_VpdmaInDataDesc *dataDesc = NULL;
    GT_assert(VpsHalTrace, NULL != memPtr);
    GT_assert(VpsHalTrace, NULL != descInfo);

    dataDesc = (volatile VpsHal_VpdmaInDataDesc *) memPtr;

    dataDesc->frameHeight    = descInfo->frameHeight;
    dataDesc->transferHeight = descInfo->transHeight;
}

/**
 *  VpsHal_vpdmaGetFirmwareAddr
 *  \brief Internal function to select the appropriate firmware version
 */
static UInt16 *VpsHal_vpdmaGetFirmwareAddr(
    VpsHal_VpdmaFirmwareVersion ver,
    UInt32                     *
    vpdmaFirmwareSize)
{
    UInt16     *vpdmaFirmware = NULL;
    switch (ver)
    {
        case VPSHAL_VPDMA_VER_288:
            vpdmaFirmware      = (UInt16 *) gVpsHal_VpdmaFirmware_288;
            *vpdmaFirmwareSize = sizeof (gVpsHal_VpdmaFirmware_288);
            break;
        case VPSHAL_VPDMA_VER_1B8:
        case VPSHAL_VPDMA_VER_DEFAULT:
        default:
            vpdmaFirmware      = (UInt16 *) gVpsHal_VpdmaFirmware_1B8;
            *vpdmaFirmwareSize = sizeof (gVpsHal_VpdmaFirmware_1B8);
            break;
    }
#ifdef VPSHAL_CFG_ENABLE_CUSTOM_FW_LOAD
    UInt16     *tempPtr;
    FILE       *hFile;
    static Char filePath[256U];
    UInt32      bytesRead, totalRead;

    while (1)
    {
        GT_0trace(VpsHalTrace, GT_INFO,
                  "Enter VPDMA firmware hex file path: ");
        BspOsal_scanf("%s", filePath);
        GT_0trace(VpsHalTrace, GT_INFO, " \r\n");

        /* Open file */
        hFile = fopen(filePath, "rt");
        if (NULL == hFile)
        {
            GT_1trace(VpsHalTrace, GT_INFO,
                      "Can't open file %s. Try again!!\r\n", filePath);
            continue;
        }
        else
        {
            totalRead = 0U;
            tempPtr   = &gVpsVpdmaHalCustomFw[0U];
            while (1)
            {
                bytesRead = fscanf(hFile, "%x", tempPtr);
                if (bytesRead <= 0)
                {
                    break;
                }
                totalRead += 2U;
                tempPtr++;
            }
            /* GT_assert( VpsHalTrace, ( totalRead <= */
            /* sizeof(gVpsVpdmaHalCustomFw) ) ); */
            fclose(hFile);

            vpdmaFirmware = gVpsVpdmaHalCustomFw;
            break;
        }
    }
#endif

    return (vpdmaFirmware);
}

/**
 *  VpsHal_vpdmaEnableListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaEnableListCompleteInterrupt(VpsHal_Handle handle,
                                              UInt32        intrLine,
                                              UInt32        listNum,
                                              UInt32        enable)
{
    Int32  retval = BSP_SOK;
    UInt32 regVal;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* TODO: Null check */
    /* TODO: Do we need support for multiple interrupt lines? */

    if (listNum > VPSHAL_VPDMA_MAX_LIST)
    {
        retval = BSP_EFAIL;
    }
    if (BSP_SOK == retval)
    {
        if (VPSHAL_VPDMA_INT0 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << (listNum * 2U))));
        }
        else if (VPSHAL_VPDMA_INT1 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << (listNum * 2U))));
        }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        else if (VPSHAL_VPDMA_INT2 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << (listNum * 2U))));
        }
        else if (VPSHAL_VPDMA_INT3 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << (listNum * 2U))));
        }
#endif
        else
        {
            retval = BSP_EINVALID_PARAMS;
        }
    }
    if (BSP_SOK == retval)
    {
        retval = VpsHal_vpdmaTopEnableVpdmaListCompleteInterrupt(
            handle, intrLine, listNum, enable);
    }

    return retval;
}

/**
 *  VpsHal_vpdmaClearListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaClearListCompleteInterrupt(VpsHal_Handle handle,
                                             UInt32        intrLine,
                                             UInt32        listNum)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* TODO: Null check */

    if (listNum > VPSHAL_VPDMA_MAX_LIST)
    {
        retval = BSP_EFAIL;
    }
    if (BSP_SOK == retval)
    {
        if (VPSHAL_VPDMA_INT0 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_STAT,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else if (VPSHAL_VPDMA_INT1 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_STAT,
                ((UInt32) 1U << (listNum * 2U)));
        }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        else if (VPSHAL_VPDMA_INT2 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_STAT,
                ((UInt32) 1U << (listNum * 2U)));
        }
        else if (VPSHAL_VPDMA_INT3 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_STAT,
                ((UInt32) 1U << (listNum * 2U)));
        }
#endif
        else
        {
            retval = BSP_EINVALID_PARAMS;
        }
    }

    if (BSP_SOK == retval)
    {
        retval =
            VpsHal_vpdmaTopClearVpdmaListCompleteInterrupt(handle, intrLine,
                                                           listNum);
    }

    return retval;
}

/**
 *  VpsHal_vpdmaEnableListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaEnableListNotifyInterrupt(VpsHal_Handle handle,
                                            UInt32        intrLine,
                                            UInt32        listNum,
                                            UInt32        enable)
{
    Int32  retval = BSP_SOK;
    UInt32 regVal;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* TODO: Null check */
    /* TODO: Do we need support for multiple interrupt lines? */

    if (listNum > VPSHAL_VPDMA_MAX_LIST)
    {
        retval = BSP_EFAIL;
    }
    if (retval == BSP_SOK)
    {
        if (VPSHAL_VPDMA_INT0 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << ((listNum * 2U) + 1U))));
        }
        else if (VPSHAL_VPDMA_INT1 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << ((listNum * 2U) + 1U))));
        }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        else if (VPSHAL_VPDMA_INT2 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << ((listNum * 2U) + 1U))));
        }
        else if (VPSHAL_VPDMA_INT3 == intrLine)
        {
            regVal =
                HW_RD_REG32(
                    vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_MASK);
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_MASK,
                (regVal | ((UInt32) 1U << ((listNum * 2U) + 1U))));
        }
#endif
        else
        {
            retval = BSP_EINVALID_PARAMS;
        }
    }
    if (retval == BSP_SOK)
    {
        retval = VpsHal_vpdmaTopEnableVpdmaListNotifyInterrupt(
            handle, intrLine, listNum, enable);
    }

    return retval;
}

/**
 *  VpsHal_vpdmaClearListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaClearListNotifyInterrupt(VpsHal_Handle handle,
                                           UInt32        intrLine,
                                           UInt32        listNum)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    /* TODO: Null check */

    if (listNum > VPSHAL_VPDMA_MAX_LIST)
    {
        retval = BSP_EFAIL;
    }
    if (BSP_SOK == retval)
    {
        if (VPSHAL_VPDMA_INT0 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT0_LIST0_INT_STAT,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else if (VPSHAL_VPDMA_INT1 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT1_LIST0_INT_STAT,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        else if (VPSHAL_VPDMA_INT2 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT2_LIST0_INT_STAT,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
        else if (VPSHAL_VPDMA_INT3 == intrLine)
        {
            HW_WR_REG32(
                vpdmaInfo->baseAddr + VPDMA_INT3_LIST0_INT_STAT,
                ((UInt32) 1U << ((listNum * 2U) + 1U)));
        }
#endif
        else
        {
            retval = BSP_EFAIL;
        }
    }
    if (BSP_SOK == retval)
    {
        retval = VpsHal_vpdmaTopClearVpdmaListNotifyInterrupt(handle, intrLine,
                                                              listNum);
    }

    return retval;
}

/**
 *  VpsHal_vpdmaCalcRegOvlyMemSize
 *  \brief Function to calculate the size of memory required for creating
 *  VPDMA configuration address set for the given register offsets. It
 *  also returns the offsets of the virtual register in the register
 *  overlay from the starting location of the overlay in terms of
 *  words. This function will be used for the other HALs to calculate
 *  the size required to store configured through VPDMA and to get
 *  the virtual register offset so that they can modify virtual
 *  registers.
 *
 *  \param regOffset        List of Register Offsets
 *  \param numReg           Number of register offsets in first parameter
 *  \param virtRegOffset    Pointer to array in which virtual register
 *                          offsets will be returned. This offsets are
 *                          in terms of words.
 *  \return                 Size of memory in terms of bytes
 */
UInt32 VpsHal_vpdmaCalcRegOvlyMemSize(UInt32 *const *regOffset,
                                      UInt32         numReg,
                                      UInt32        *virtRegOffset)
{
    UInt32 memSize = 0U, cnt, offsetCnt;
    UInt32 blockSize, numBlockReg;

    /* TODO: GT_assert(VpsHalTrace, (NULL != regOffset)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != virtRegOffset)); */

    cnt = 0U;
    while (cnt < numReg)
    {
        /* Get the number of register in the block and block size */
        /* MISRA.PTR.ARITH */
        VpsHal_vpdmaCalcBlockInfo(
            &regOffset[cnt],
            numReg - cnt,
            &blockSize,
            &numBlockReg);
        /* Store the virtual register offset in the block */
        for (offsetCnt = 0; offsetCnt < numBlockReg; offsetCnt++)
        {
            /* MISRA.PTR.ARITH */
            virtRegOffset[cnt + offsetCnt] = memSize +
                                             VPSHAL_VPDMA_ADDR_SET_SIZE +
                                             offsetCnt;
        }
        /* Update the number of register counter and total memory size */
        cnt     += numBlockReg;
        memSize += blockSize;
    }

    return (memSize * VPSHAL_VPDMA_WORD_SIZE);
}

/**
 *  VpsHal_vpdmaCreateRegOverlay
 *  Function is used to create complete configuration descriptor
 *  with the address set for the given registers offsets. It takes
 *  list of register offsets and pointer to memory, creates
 *  configuration descriptor and address set for the register set and
 *  returns the virtual addresses of the registers.
 *
 *  \param configRegList    List of Register Offsets
 *  \param numConfigReg     List of Register Offsets
 *  \param regOverlay       Pointer to array in which virtual register
 *                          offsets will be returned. This offsets are
 *                          in terms of words.
 *  \return                 Size of memory in terms of bytes
 */
Int32 VpsHal_vpdmaCreateRegOverlay(UInt32 *const *configRegList,
                                   UInt32         numConfigReg,
                                   void          *regOverlay)
{
    UInt32  blockSize, numBlockReg, cnt;
    UInt32 *regOvlyPtr = (UInt32 *) regOverlay;

    GT_assert(VpsHalTrace, NULL != configRegList);
    GT_assert(VpsHalTrace, NULL != regOverlay);

    cnt = 0U;
    while (cnt < numConfigReg)
    {
        /* Get the number of register in the block and block size */
        /* MISRA.PTR.ARITH */
        VpsHal_vpdmaCalcBlockInfo(
            &configRegList[cnt],
            numConfigReg - cnt,
            &blockSize,
            &numBlockReg);
        /* Set the start address and number of registers in the overlay
         * header */
        ((VpsHal_VpdmaSubBlockHeader *) regOvlyPtr)->nextClientAddr =
            (UInt32) configRegList[cnt] & 0xFFFFU;
        ((VpsHal_VpdmaSubBlockHeader *) regOvlyPtr)->subBlockLength =
            numBlockReg;
        ((VpsHal_VpdmaSubBlockHeader *) regOvlyPtr)->reserved1 = 0U;
        ((VpsHal_VpdmaSubBlockHeader *) regOvlyPtr)->reserved2 = 0U;
        ((VpsHal_VpdmaSubBlockHeader *) regOvlyPtr)->reserved3 = 0U;
        /* Move to the next register block */
        regOvlyPtr = regOvlyPtr + blockSize;
        /* Update the register counter */
        cnt += numBlockReg;
    }
    return (0);
}

/**
 *  VpsHal_vpdmaCalcBlockInfo
 *  \brief Function to calculate block information for the VPDMA Register
 *  Overlay
 */
void VpsHal_vpdmaCalcBlockInfo(UInt32 *const *regOffset,
                               UInt32         numReg,
                               UInt32        *blockSize,
                               UInt32        *numBlockReg)
{
    UInt32 prevOffset = 0U, count;
    Int32  diff;

    /* TODO: GT_assert(VpsHalTrace, (NULL != regOffset)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != blockSize)); */
    /* TODO: GT_assert(VpsHalTrace, (NULL != numBlockReg)); */

    if (numReg > 0)
    {
        /* At least one address set is needed for the first register */
        *blockSize = VPSHAL_VPDMA_ADDR_SET_SIZE +
                     VPSHAL_VPDMA_MIN_REG_SET_SIZE;
        *numBlockReg = 1U;
        prevOffset   = (UInt32) regOffset[0];
    }
    for (count = 1U; count < numReg; count++)
    {
        /*
         * Workaround: Data payload cannot be more than 128 bytes (including
         * header of 4 words). Hence creating new block when number of
         * registers in a block cross VPSHAL_VPDMA_CONFIG_MMR_MAX_BLOCK_REG.
         */
        /* If the offset difference between current and previous register is
         * greater than 4, create a new address set */
        diff = (Int32) regOffset[count] - (Int32) prevOffset;
        if (((diff > (Int32) VPSHAL_VPDMA_REG_OFFSET_DIFF) || (diff < 0)) ||
            (*numBlockReg >= VPSHAL_VPDMA_CONFIG_MMR_MAX_BLOCK_REG))
        {
            break;
        }
        /* Address set is always 4 word aligned so for the 5th register,
         * new memory is required */
        if (0U == (*numBlockReg & (VPSHAL_VPDMA_REG_OFFSET_DIFF - 1U)))
        {
            *blockSize += VPSHAL_VPDMA_ADDR_SET_SIZE;
        }
        *numBlockReg += 1U;
        prevOffset    = (UInt32) regOffset[count];
    }
}

/**
 *  VpsHal_vpdmaSetTopHandle
 *  \brief Internal function to identify the clock control module which will
 *  be required for the current use-case
 */
static void VpsHal_vpdmaSetTopHandle(VpsHal_Handle handle)
{
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    switch (vpdmaInfo->halId)
    {
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        case VPSHAL_VIP1_VPDMA:
            vpdmaInfo->vipTopHandle =
                VpsHal_vipTopGetInstInfo(VPSHAL_VIP1);
            break;
  #endif  /* #if defined (VPS_VIP1_BUILD) */
  #if defined (VPS_VIP2_BUILD)
        case VPSHAL_VIP2_VPDMA:
            vpdmaInfo->vipTopHandle =
                VpsHal_vipTopGetInstInfo(VPSHAL_VIP2);
            break;
  #endif  /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        case VPSHAL_VIP3_VPDMA:
            vpdmaInfo->vipTopHandle =
                VpsHal_vipTopGetInstInfo(VPSHAL_VIP3);
            break;
  #endif  /* #if defined (VPS_VIP3_BUILD) */
#endif

#ifdef VPS_VPE_BUILD
        case VPSHAL_VPE1_VPDMA:
            vpdmaInfo->vpeTopHandle =
                VpsHal_vpeTopGetInstInfo(VPSHAL_VPE1);
            break;
#endif
        case VPSHAL_VPDMA_GENERIC:
            /* In case of TI814x, there is only one VPS top, hence use
             * VIP top in case VIP is defined. Else use VPE top. */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
            vpdmaInfo->vipTopHandle =
                VpsHal_vipTopGetInstInfo(VPSHAL_VIP1);
  #endif  /* #if defined (VPS_VIP1_BUILD) */
#else
 #ifdef VPS_VPE_BUILD
            vpdmaInfo->vpeTopHandle =
                VpsHal_vpeTopGetInstInfo(VPSHAL_VPE1);
 #endif
#endif
            break;
        default:
            /* TODO: GT_assert(VpsHalTrace, (NULL != regOffset)); */
            break;
    }
}

/**
 *  VpsHal_vpdmaReset
 *  \brief Internal function to call VPDMA reset/un-reset by selecting the
 *  appropriate clock control module
 */
static void VpsHal_vpdmaReset(VpsHal_Handle handle, UInt32 enable)
{
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        VpsHal_vipTopResetModule(vpdmaInfo->vipTopHandle,
                                 VPSHAL_VIP_TOP_VPDMA,
                                 enable, 0);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        VpsHal_vpeTopResetModule(vpdmaInfo->vpeTopHandle,
                                 VPSHAL_VPE_TOP_VPDMA,
                                 enable, 0);
#endif
    }
    else
    {
        /*
         * Do nothing.
         */
    }
}

/**
 *  VpsHal_vpdmaClkEn
 *  \brief Internal function to call VPDMA clk enable/disable by selecting the
 *  appropriate clock control module
 */
static void VpsHal_vpdmaClkEn(VpsHal_Handle handle, UInt32 enable)
{
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        VpsHal_vipTopEnableModule(vpdmaInfo->vipTopHandle,
                                  VPSHAL_VIP_TOP_VPDMA,
                                  enable, 0);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        VpsHal_vpeTopEnableModule(vpdmaInfo->vpeTopHandle,
                                  VPSHAL_VPE_TOP_VPDMA,
                                  enable, 0);
#endif
    }
    else
    {
        /*
         * Do nothing.
         */
    }
}

/**
 *  VpsHal_vpdmaTopEnableVpdmaListCompleteInterrupt
 *  \brief Enable/Disable List loading completion interrupt
 *  in the appropriate Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopEnableVpdmaListCompleteInterrupt(
    VpsHal_Handle handle, UInt32 intrLine, UInt32 listNum, UInt32 enable)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        retval = VpsHal_vipTopEnableVpdmaListCompleteInterrupt(
            vpdmaInfo->vipTopHandle, intrLine, listNum, enable);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        retval = VpsHal_vpeTopEnableVpdmaListCompleteInterrupt(
            vpdmaInfo->vpeTopHandle, intrLine, listNum, enable);
#endif
    }
    else
    {
        retval = BSP_EFAIL;
    }

    return retval;
}

/**
 *  VpsHal_vpdmaTopClearVpdmaListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *  in the appropriate Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopClearVpdmaListCompleteInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        retval = VpsHal_vipTopClearVpdmaListCompleteInterrupt(
            vpdmaInfo->vipTopHandle, intrLine, listNum);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        retval = VpsHal_vpeTopClearVpdmaListCompleteInterrupt(
            vpdmaInfo->vpeTopHandle, intrLine, listNum);
#endif
    }
    else
    {
        retval = BSP_EFAIL;
    }

    return retval;
}

/**
 *  VpsHal_vpdmaTopEnableVpdmaListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor) in the appropriate
 *  Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopEnableVpdmaListNotifyInterrupt(
    VpsHal_Handle handle, UInt32 intrLine, UInt32 listNum, UInt32 enable)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        retval = VpsHal_vipTopEnableVpdmaListNotifyInterrupt(
            vpdmaInfo->vipTopHandle, intrLine, listNum, enable);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        retval = VpsHal_vpeTopEnableVpdmaListNotifyInterrupt(
            vpdmaInfo->vpeTopHandle, intrLine, listNum, enable);
#endif
    }
    else
    {
        retval = BSP_EFAIL;
    }

    return retval;
}

/**
 *  VpsHal_vpdmaTopClearVpdmaListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor) in the appropriate
 *  Top INTC module
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *                          Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
static Int32 VpsHal_vpdmaTopClearVpdmaListNotifyInterrupt(
    VpsHal_Handle handle,
    UInt32        intrLine,
    UInt32        listNum)
{
    Int32 retval = BSP_SOK;
    VpsHal_VpdmaInfo *vpdmaInfo = (VpsHal_VpdmaInfo *) handle;

    if (NULL != vpdmaInfo->vipTopHandle)
    {
#ifdef VPS_VIP_BUILD
        retval = VpsHal_vipTopClearVpdmaListNotifyInterrupt(
            vpdmaInfo->vipTopHandle, intrLine, listNum);
#endif
    }
    else if (NULL != vpdmaInfo->vpeTopHandle)
    {
#ifdef VPS_VPE_BUILD
        retval = VpsHal_vpeTopClearVpdmaListNotifyInterrupt(
            vpdmaInfo->vpeTopHandle, intrLine, listNum);
#endif
    }
    else
    {
        retval = BSP_EFAIL;
    }
    return retval;
}

/**
 *  VpsHal_vpdmaVirtToPhy
 *  \brief Internal function for virtual-physical translation of addresses.
 *
 *  \param virt            Input virtual address
 *
 *  \return                Output physical address
 *
 */
static inline UInt32 VpsHal_vpdmaVirtToPhy(Ptr virt)
{
    UInt32 retval = 0;
#ifdef VPSHAL_VPDMA_ENABLE_ADDR_TRANS
    if (vpdmaHalObj.isAddrTransReq)
    {
        retval = ((UInt32) virt - vpdmaHalObj.virtBaseAddr) +
                 vpdmaHalObj.physBaseAddr;
    }
#endif
    if (retval == 0)
    {
        retval = (UInt32) virt;
    }

    return retval;
}

#if 0
/**
 *  VpsHal_vpdmaPhyToVirt
 *  \brief Internal function for physical-virtual translation of OCMC addresses.
 *
 *  \param phys            Input physical address
 *
 *  \return                Output virtual address
 *
 */
static inline UInt32 VpsHal_vpdmaPhyToVirt(Ptr phys)
{
#ifdef VPSHAL_VPDMA_ENABLE_ADDR_TRANS
    if (vpdmaHalObj.isAddrTransReq)
    {
        return (((UInt32) phys - vpdmaHalObj.physBaseAddr)
                + vpdmaHalObj.virtBaseAddr);
    }
#endif

    return (UInt32) (phys);
}

#endif

/**
 *  VpsHal_vpdmaSetFrameSizeReg
 *  \brief Function to configure the MAX_SIZE1, MAX_SIZE2 and MAX_SIZE3
 *  registers with the user provided values.
 *  User is expected to provide maxHeight, maxWidth information for
 *  all the 3 MAX_SIZE registers for a VPDMA.
 *
 *  \param handle          Handle to Vpdma instance. This handle shall
 *                         contain the halId information of the VPDMA
 *                         being used.
 *  \param args            Instance of the max size parameters.
 *
 *  \return                No return value.
 *
 */
void VpsHal_vpdmaSetFrameSizeReg(VpsHal_Handle handle,
                                 Ptr           args)
{
    UInt32 size;
    VpsHal_VpdmaInfo          *vpdmaInfo  = (VpsHal_VpdmaInfo *) handle;
    Vps_VpdmaMaxSizeParams *maxSizeParams =
        (Vps_VpdmaMaxSizeParams *) args;
    UInt16 width, height;

    width  = (UInt16) maxSizeParams->maxOutWidth[0] - 1U;
    height = (UInt16) maxSizeParams->maxOutHeight[0] - 1U;
    size   = ((UInt32) width << 16) | height;
    HW_WR_REG32(vpdmaInfo->baseAddr + VPDMA_MAX_SIZE1, size);

    width  = (UInt16) maxSizeParams->maxOutWidth[1] - 1U;
    height = (UInt16) maxSizeParams->maxOutHeight[1] - 1U;
    size   = ((UInt32) width << 16) | height;
    HW_WR_REG32(vpdmaInfo->baseAddr + VPDMA_MAX_SIZE2, size);

    width  = (UInt16) maxSizeParams->maxOutWidth[2] - 1U;
    height = (UInt16) maxSizeParams->maxOutHeight[2] - 1U;
    size   = ((UInt32) width << 16) | height;
    HW_WR_REG32(vpdmaInfo->baseAddr + VPDMA_MAX_SIZE3, size);

    return;
}

/**
 *  VpsHal_vpdmaFvid2ToVpdma
 *  \brief Returns VPDMA data-types corresponding to input FVID2 datatypes
 *
 *  \param fvid2DT         Input FVID2 data-type
 *
 *  \return                Corresponding VPDMA data-type.
 *                         Returns VPSHAL_VPDMA_CHANDT_INVALID for invalid
 *                         input.
 *
 */
VpsHal_VpdmaChanDT VpsHal_vpdmaFvid2ToVpdma(Fvid2_DataFormat fvid2DT)
{
    VpsHal_VpdmaChanDT retVpdmaChanDT = VPSHAL_VPDMA_CHANDT_INVALID;
    UInt32 i;
    for (i = 0U; i < VPSHAL_VPDMA_FVID2_DT_MAPPING_SIZE; i++)
    {
        if (fvid2DT == gDataTypeMapping[i].fvid2DT)
        {
            retVpdmaChanDT = gDataTypeMapping[i].vpdmaDT;
        }
    }
    return retVpdmaChanDT;
}

/**
 *  VpsHal_vpdmaSetRgbBackgroundColor
 *  \brief Function used to set the background color for RGB.
 *                  Bits  7:0  -  Configures Blend
 *                  Bits 15:8  -  Configures Blue
 *                  Bits 23:16 -  Configures Green
 *                  Bits 31:24 -  Configures Red
 *
 *  \param handle       VpsHal_Handle handle returned by VpsHal_vpdmaOpen
 ************function.
 *  \param value        Value used to set the background color register.
 *
 *  \return                None
 *
 */
void VpsHal_vpdmaSetRgbBackgroundColor(VpsHal_Handle handle, UInt32 value)
{
    VpsHal_VpdmaInfo *vpdmaInfo = NULL;
    UInt32 baseAddr;

    GT_assert(VpsHalTrace, (NULL != handle));
    vpdmaInfo = (VpsHal_VpdmaInfo *) handle;
    baseAddr  = vpdmaInfo->baseAddr;

    /* Set Background color register value*/
    HW_WR_REG32(baseAddr + VPDMA_BG_RGB, value);
}

