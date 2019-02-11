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
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *
 *  @{
 */

/**
 *  \file vps_cfgMem.h
 *
 *  \brief VPS - Configuration for size of static object array
 */

#ifndef VPS_CFG_MEM_H_
#define VPS_CFG_MEM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief DSS number of instances for Vid + Gfx (Forward) pipe objects to
 *  allocate.
 *  If user uses only fewer than these pipes, this can be reduced!!
 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
/* Tda2xx has 3 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS   (4U)
#elif defined (SOC_TDA3XX)
/* Tda3xx has 2 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS   (3U)
#endif

/**
 *  \brief DSS number of instances of WB pipe objects to allocate
 *  Tda2xx and Tda3xx supports 1 WB pipeline
 */
#define VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS    (1U)

/**
 *  \brief Number of VIP instances objects to allocate.
 *
 *  Note: This macro is used for storing platform data at init time. Hence
 *  this should be changed only when a particular VIP instance is removed
 *  from the build using make macros like VPS_VIP1_BUILD etc...
 */
/* Add each VIP count based on build flag */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x)
  #if defined (VPS_VIP1_BUILD)
    #define VPS_VIP1_INCLUDE_CNT    (1U)
  #else
    #define VPS_VIP1_INCLUDE_CNT    (0U)
  #endif
  #if defined (VPS_VIP2_BUILD)
    #define VPS_VIP2_INCLUDE_CNT    (1U)
  #else
    #define VPS_VIP2_INCLUDE_CNT    (0U)
  #endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
  #if defined (VPS_VIP3_BUILD)
    #define VPS_VIP3_INCLUDE_CNT    (1U)
  #else
    #define VPS_VIP3_INCLUDE_CNT    (0U)
  #endif
#else
    #define VPS_VIP3_INCLUDE_CNT    (0U)
#endif
#define VPS_CFG_MEM_VIP_MAX_INST_OBJS       (VPS_VIP1_INCLUDE_CNT + \
                                             VPS_VIP2_INCLUDE_CNT + \
                                             VPS_VIP3_INCLUDE_CNT)
#else
#define VPS_CFG_MEM_VIP_MAX_INST_OBJS       (VPS_VIP_MAX)
#endif

/**
 *  \brief Number of VIP port objects to allocate.
 *  If user uses only fewer than these ports, this can be reduced!!
 *  Note: Each VIP instance has 4 ports. That's why it is (x * 2 * 2) below.
 */
#define VPS_CFG_MEM_VIP_MAX_PORT_OBJS                \
            (VPS_CFG_MEM_VIP_MAX_INST_OBJS * VPS_VIP_SLICE_MAX * \
             VPS_VIP_PORT_MAX)

/*
 * Note: Below macros cannot be changed. These macros are used for storing
 * platform data. Hence depends on a platform build and not as a configurable
 * parameters!!
 */
/**
 *  \brief DSS number of instances for Vid + Gfx (forward) pipes for a platform
 */
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
/* Tda2xx has 3 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_NUM_FWD_PIPE        (4U)
#elif defined (SOC_TDA3XX)
/* Tda3xx has 2 video + 1 Grpx pipelines */
#define VPS_CFG_MEM_DSS_NUM_FWD_PIPE        (3U)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_MEM_H_ */

/* @} */
