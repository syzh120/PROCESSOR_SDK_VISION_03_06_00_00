/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *
*/

/**
 *  \file   hw_ocp_socket_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_OCP_SOCKET_CM_CORE_H_
#define HW_OCP_SOCKET_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define REVISION_CM_CORE                                        (0x0U)
#define CM_CM_CORE_PROFILING_CLKCTRL                            (0x40U)
#define CM_CORE_DEBUG_CFG                                       (0xf0U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define REVISION_CM_CORE_CUSTOM_SHIFT                           (6U)
#define REVISION_CM_CORE_CUSTOM_MASK                            (0x000000c0U)
#define REVISION_CM_CORE_CUSTOM_STANDARD                         (0U)

#define REVISION_CM_CORE_R_RTL_SHIFT                            (11U)
#define REVISION_CM_CORE_R_RTL_MASK                             (0x0000f800U)

#define REVISION_CM_CORE_FUNC_SHIFT                             (16U)
#define REVISION_CM_CORE_FUNC_MASK                              (0x0fff0000U)

#define REVISION_CM_CORE_SCHEME_SHIFT                           (30U)
#define REVISION_CM_CORE_SCHEME_MASK                            (0xc0000000U)
#define REVISION_CM_CORE_SCHEME_H08                              (1U)
#define REVISION_CM_CORE_SCHEME_LEGACY                           (0U)

#define REVISION_CM_CORE_Y_MINOR_SHIFT                          (0U)
#define REVISION_CM_CORE_Y_MINOR_MASK                           (0x0000003fU)
#define REVISION_CM_CORE_Y_MINOR_ES1                             (0U)
#define REVISION_CM_CORE_Y_MINOR_ES2                             (1U)

#define REVISION_CM_CORE_X_MAJOR_SHIFT                          (8U)
#define REVISION_CM_CORE_X_MAJOR_MASK                           (0x00000700U)
#define REVISION_CM_CORE_X_MAJOR_OMAP4430_ES1_X                  (0U)
#define REVISION_CM_CORE_X_MAJOR_OMAP4430_ES2_X                  (1U)
#define REVISION_CM_CORE_X_MAJOR_OMAP4460                        (2U)
#define REVISION_CM_CORE_X_MAJOR_OMAP5430                        (3U)
#define REVISION_CM_CORE_X_MAJOR_OMAP470                         (4U)

#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_SHIFT           (0U)
#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_MASK            (0x00000003U)
#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_DISABLED         (0U)
#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_AUTO             (1U)
#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_RESERVED_2       (2U)
#define CM_CM_CORE_PROFILING_CLKCTRL_MODULEMODE_RESERVED         (3U)

#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_SHIFT               (16U)
#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_MASK                (0x00030000U)
#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_DISABLE              (3U)
#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_IDLE                 (2U)
#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_FUNC                 (0U)
#define CM_CM_CORE_PROFILING_CLKCTRL_IDLEST_TRANS                (1U)

#define CM_CORE_DEBUG_CFG_SEL0_SHIFT                            (0U)
#define CM_CORE_DEBUG_CFG_SEL0_MASK                             (0x000000ffU)

#define CM_CORE_DEBUG_CFG_SEL1_SHIFT                            (8U)
#define CM_CORE_DEBUG_CFG_SEL1_MASK                             (0x0000ff00U)

#define CM_CORE_DEBUG_CFG_SEL2_SHIFT                            (16U)
#define CM_CORE_DEBUG_CFG_SEL2_MASK                             (0x00ff0000U)

#define CM_CORE_DEBUG_CFG_SEL3_SHIFT                            (24U)
#define CM_CORE_DEBUG_CFG_SEL3_MASK                             (0xff000000U)

#ifdef __cplusplus
}
#endif

#endif /* HW_OCP_SOCKET_CM_CORE_H_ */

