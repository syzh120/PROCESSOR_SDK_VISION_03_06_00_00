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
 *  \file   hw_sysconfig.h
 *
 *  \brief  register-level header file for IPs missing Sysconfig register
 *
**/

#ifndef HW_SYSCONFIG_H_
#define HW_SYSCONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define ELM_SYSCONFIG                   (0x10U)
#define DMA4_OCP_SYSCONFIG              (0x2CU)
#define PWMSS_SYSCONFIG                 (0x4U)
#define CPSW_WR_CTRL                    (0x8U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ELM_SYSCONFIG_SIDLEMODE_SHIFT                                                                       (3U)
#define ELM_SYSCONFIG_SIDLEMODE_MASK                                                                        (0x00000018U)
#define ELM_SYSCONFIG_SIDLEMODE_FORCE_IDLE                                                                   (0U)
#define ELM_SYSCONFIG_SIDLEMODE_NOIDLE                                                                       (1U)
#define ELM_SYSCONFIG_SIDLEMODE_SMARTIDLE                                                                    (2U)
#define ELM_SYSCONFIG_SIDLEMODE_RESERVED3                                                                    (3U)

#define ELM_SYSCONFIG_SOFTRESET_SHIFT                                                                    (1U)
#define ELM_SYSCONFIG_SOFTRESET_MASK                                                                     (0x00000002U)

#define ELM_SYSCONFIG_AUTOIDLE_SHIFT                                                                  (0U)
#define ELM_SYSCONFIG_AUTOIDLE_MASK                                                                   (0x00000001U)
#define ELM_SYSCONFIG_AUTOIDLE_CLKFREE                                                                 (0U)
#define ELM_SYSCONFIG_AUTOIDLE_CLKGATED                                                                (1U)

#define ELM_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                   (8U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_MASK                                                                    (0x00000100U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_NONE                                                                     (0U)
#define ELM_SYSCONFIG_CLOCKACTIVITY_OCP                                                                      (1U)

#define PWMSS_SYSCONFIG_IDLEMODE_SHIFT                                                                       (2U)
#define PWMSS_SYSCONFIG_IDLEMODE_MASK                                                                        (0x000000cU)
#define PWMSS_SYSCONFIG_IDLEMODE_FORCE_IDLE                                                                    (0U)
#define PWMSS_SYSCONFIG_IDLEMODE_NOIDLE                                                                       (1U)
#define PWMSS_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                    (2U)
#define PWMSS_SYSCONFIG_IDLEMODE_RESERVED3                                                                    (3U)

#define PWMSS_SYSCONFIG_SOFTRESET_SHIFT                                                                    (0U)
#define PWMSS_SYSCONFIG_SOFTRESET_MASK                                                                     (0x00000001U)

#define CPSW_WR_CTRL_MMR_IDLEMODE_SHIFT                                                 (0U)
#define CPSW_WR_CTRL_MMR_IDLEMODE_MASK                                                  (0x00000003U)
#define CPSW_WR_CTRL_MMR_IDLEMODE_EN_0X1                                                 (1U)
#define CPSW_WR_CTRL_MMR_IDLEMODE_EN_0X2                                                 (2U)
#define CPSW_WR_CTRL_MMR_IDLEMODE_EN_0X3                                                 (3U)
#define CPSW_WR_CTRL_MMR_IDLEMODE_EN_0X0                                                 (0U)

#define CPSW_WR_CTRL_MMR_STDBYMODE_SHIFT                                                (2U)
#define CPSW_WR_CTRL_MMR_STDBYMODE_MASK                                                 (0x0000000cU)
#define CPSW_WR_CTRL_MMR_STDBYMODE_EN_0X0                                                (0U)
#define CPSW_WR_CTRL_MMR_STDBYMODE_EN_0X2                                                (2U)
#define CPSW_WR_CTRL_MMR_STDBYMODE_EN_0X3                                                (3U)
#define CPSW_WR_CTRL_MMR_STDBYMODE_EN_0X1                                                (1U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_SYSCONFIG_H_ */
