/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vps_cfgsimcop.h
 *
 *  \brief  Defines the structures / control operations that could be used to
 *              configure / control LDC module
 */

/**
 *  \addtogroup BSP_DRV_VPS_COMMON_CAPTURE_SIMCOP_LDC_ISS
 *
 *  @{
 */

#ifndef VPS_CFG_SIMCOP_H_
#define VPS_CFG_SIMCOP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Ioctl for Simcop Stream Routing
 */
#define VPS_ISS_SIMCOP_IOCTL_STREAM_ROUTING \
                                        (VPS_ISS_IOCTL_SIMCOP_IOCTL_BASE + 0U)

/** \brief Simcop Open Mode, Used at the time of core Open
 *  Used to open core in either LDC, VTNF or LDC+VTNF mode.
 */
typedef enum vpsissSimcopM2MMode
{
    VPS_ISS_SIMCOP_LDC = 0,
    /**< Open core only for LDC operation */
    VPS_ISS_SIMCOP_VTNF = 1,
    /**< Open core only for VTNF operation */
    VPS_ISS_SIMCOP_LDC_VTNF = 2,
    /**< Open core for LDC and VTNF operation */
    VPS_ISS_SIMCOP_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed,
            will always be contained in int */
} vpsissSimcopM2MMode_t;    /**< vpsissSimcopM2MMode_t */

/**
 *  \brief Enum for selecting burst size for DMA transfers
 */
typedef enum vpsisssimcopDmaMaxBustSize
{
    VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_SINGLE_REQUEST = 0x0,
    /**< Single Request only */
    VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_1 = 0x1,
    /**< Max burst size is less than or equal to 2 */
    VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_2 = 0x2,
    /**< Max burst size is less than or equal to 4 */
    VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_3 = 0x3,
    /**< Max burst size is less than or equal to 8 */
    VPS_ISS_SIMCOP_DMA_MAX_BURST_SIZE_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed,
            will always be contained in int */
} vpsisssimcopDmaMaxBustSize_t; /**< vpsisssimcopDmaMaxBustSize_t */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief SIMCOP DMA Control parameters.
 *         Typically set once and will not be changed
 */
typedef struct vpsisssimcopDmaCtrlParams
{
    uint32_t                     bwLimit;
    /**< Used to set number of functional clock cycles between two OCP
     *   requests. This parameter could be used to reduce traffic generated
     *   by the SIMCOP DMA for non real time critical applications.
     *   0: provides maximum performance. */
    uint32_t                     tagCnt;
    /**< Limits the outstanding transactions count.
     *   Only tags 0 to tagCnt will be used by SIMCOP DMA.
     *   Max value is 0xF */
    uint32_t                     enablePostedWrite;
    /**< Select write type
     *   0: Only nonposted writes are generated
     *   1: Only posted writes are generated */
    vpsisssimcopDmaMaxBustSize_t maxBurstSize;
    /**< Defines the maximum burst length */
} vpsisssimcopDmaCtrlParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* _VPS_CFG_SIMCOP_H_ */

/* @} */
