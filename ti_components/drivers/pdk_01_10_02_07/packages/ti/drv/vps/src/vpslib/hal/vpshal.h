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
 *  \file vpshal.h
 *
 *  \brief Common Header file for all VPS HALs
 *  This file defines common data-structures, enums, etc for all VPS HALs
 *
 */

#ifndef VPSHAL_H_
#define VPSHAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Typedef for HAL handle. */
typedef void *VpsHal_Handle;

/** \brief Typedef for the VPS HAL get config overlay size function pointer. */
typedef UInt32 (*VpsHal_GetCfgOvlySize)(VpsHal_Handle handle);
/** \brief Typedef for the VPS HAL create config overlay function pointer. */
typedef Int32 (*VpsHal_CreateCfgOvly)(VpsHal_Handle handle, Ptr configOvlyPtr);

/**
 *  enum Vps_VipInst
 *  This is a top-level module at SOC level and hence numbering starts from 1.
 */
typedef enum
{
    VPSHAL_VIP1 = 0,
    /**< Vip Instance 1 */
    VPSHAL_VIP2,
    /**< Vip Instance 2 */
    VPSHAL_VIP3,
    /**< Vip Instance 3 */
    VPSHAL_NUM_VIP_INST
    /**< Vip Instance MAX */
} Vps_VipInst;

/**
 *  enum Vps_VipSliceInst
 */
typedef enum
{
    VPSHAL_VIP_S0 = 0,
    /**< Slice 0 */
    VPSHAL_VIP_S1,
    /**< Slice 1 */
    VPSHAL_NUM_VIP_SLICES
    /**< MAX slice */
} Vps_VipSliceInst;

/**
 *  enum VpsHal_VipPortInst
 */
typedef enum
{
    VPSHAL_VIP_PORT_A = 0,
    /**< PORTA */

    VPSHAL_VIP_PORT_B,
    /**< PORTB */

    VPSHAL_NUM_VIP_PORTS
    /**< MAX slice */
} VpsHal_VipPortInst;

/**
 *  enum Vps_VpeInst
 *  This is a top-level module at SOC level and hence numbering starts from 1.
 */
typedef enum
{
    VPSHAL_VPE1 = 0,
    /**< Vpe Instance 1 */
    VPSHAL_NUM_VPE_INST
    /**< Vpe Instance MAX */
} Vps_VpeInst;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS HAL initialization parameters.
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
} VpsHal_InitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS HAL init function.
 */
Int32 VpsHal_init(const VpsHal_InitParams *initPrms);

/**
 *  \brief VPS HAL deinit function.
 */
Int32 VpsHal_deInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_H_ */
