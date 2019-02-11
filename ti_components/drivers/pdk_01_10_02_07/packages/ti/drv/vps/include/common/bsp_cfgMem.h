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
 *  \file bsp_cfgMem.h
 *
 *  \brief BSP header file containing configuration details,
 *         for the size of static object array.
 *
 */

#ifndef BSP_CFG_MEM_H_
#define BSP_CFG_MEM_H_

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

/** \brief Number of queue length per capture channel in capture driver */
#define BSP_CFG_CAPT_QUEUE_LEN_PER_CH       (16U)

/** \brief Number of queue length per display instance in display driver */
#define BSP_CFG_DISP_QUEUE_LEN_PER_INST     (16U)

/** \brief Number of queue length per M2M channel in M2M driver */
#define BSP_CFG_M2M_INTF_QUEUE_LEN_PER_CH   (10U)

/** \brief Number of queue length per VPE channel in VPE driver */
#define BSP_CFG_M2M_VPE_QUEUE_LEN_PER_CH    (10U)

/** \brief Number of queue length per handle in DSS M2M driver */
#define BSP_CFG_M2M_DSS_QUEUE_LEN_HANDLE    (10U)

/** \brief Number of driver object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_DRV_OBJS          (40U)

/** \brief Number of channel object to allocate in FVID2 library. */
#define FVID2_CFG_FDM_NUM_CH_OBJS           (80U)

/**
 *  \brief Number of capture objects to allocate
 *
 *  Note: This macro is used for storing platform data at init time. Hence
 *  this should be changed only when a particular capture instance is removed
 *  from the build using make macros like VPS_VIP1_BUILD, VPS_ISS_BUILD etc...
 */
#define VPS_CFG_CAPT_NUM_INST_OBJS          (CSL_VPS_VIP_PORT_PER_CNT +    \
                                             CSL_VPS_DSS_WB_PIPE_PER_CNT + \
                                             CSL_VPS_ISS_CAPT_PIPE_PER_CNT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_CFG_MEM_H_ */
