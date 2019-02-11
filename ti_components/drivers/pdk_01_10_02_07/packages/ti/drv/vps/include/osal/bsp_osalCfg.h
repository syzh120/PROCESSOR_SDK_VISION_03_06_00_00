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
 *  \file bsp_osalCfg.h
 *
 *  \brief BSP OS abstraction layer configuration header file.
 *
 */

#ifndef BSP_OSAL_CFG_H_
#define BSP_OSAL_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Set this to TRUE to use [Module]_Construct API of BIOS */
#define BSP_OSAL_CFG_USE_STATIC          (TRUE)

#if defined (BUILD_ARP32) || defined (_TMS320C6X) || defined (__ARM_ARCH_7A__)

/** \brief Max number of sem objects */
#define BSP_OSAL_CFG_MAX_SEM_OBJECTS     (1050U)
/** \brief Max number of task objects */
#define BSP_OSAL_CFG_MAX_TASK_OBJECTS    (100U)
/** \brief Max number of clock objects */
#define BSP_OSAL_CFG_MAX_CLOCK_OBJECTS   (100U)
/** \brief Max number of hwi objects */
#define BSP_OSAL_CFG_MAX_HWI_OBJECTS     (100U)

#else

/** \brief Max number of sem objects */
#define BSP_OSAL_CFG_MAX_SEM_OBJECTS     (1050U)
/** \brief Max number of task objects */
#define BSP_OSAL_CFG_MAX_TASK_OBJECTS    (100U)
/** \brief Max number of clock objects */
#define BSP_OSAL_CFG_MAX_CLOCK_OBJECTS   (100U)
/** \brief Max number of hwi objects */
#define BSP_OSAL_CFG_MAX_HWI_OBJECTS     (100U)

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_OSAL_CFG_H_ */
