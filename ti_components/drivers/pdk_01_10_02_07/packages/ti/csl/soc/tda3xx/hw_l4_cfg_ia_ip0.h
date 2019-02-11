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
 *  \file   hw_l4_cfg_ia_ip0.h
 *
 *  \brief  Register-level header file for L4_CFG
 *
**/

#ifndef HW_L4_CFG_IA_IP0_H_
#define HW_L4_CFG_IA_IP0_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define L4_CFG_COMPONENT                                            (0x0U)
#define L4_CFG_CORE                                                 (0x18U)
#define L4_CFG_AGENT_CONTROL                                        (0x20U)
#define L4_CFG_AGENT_STATUS                                         (0x28U)
#define L4_CFG_ERROR_LOG                                            (0x58U)
#define L4_CFG_ERROR_LOG_ADDR                                       (0x60U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define L4_CFG_COMPONENT_REV_SHIFT                                                      (0U)
#define L4_CFG_COMPONENT_REV_MASK                                                       (0x0000ffffU)

#define L4_CFG_COMPONENT_CODE_SHIFT                                                     (16U)
#define L4_CFG_COMPONENT_CODE_MASK                                                      (0xffff0000U)

#define L4_CFG_CORE_REV_CODE_SHIFT                                                      (0U)
#define L4_CFG_CORE_REV_CODE_MASK                                                       (0x0000ffffU)

#define L4_CFG_CORE_CODE_SHIFT                                                          (16U)
#define L4_CFG_CORE_CODE_MASK                                                           (0xffff0000U)

#define L4_CFG_CORE_VENDOR_CODE_SHIFT                                                   (32U)
#define L4_CFG_CORE_VENDOR_CODE_MASK                                                    (0xffff00000000U)

#define L4_CFG_AGENT_CONTROL_MERROR_REP_SHIFT                                           (24U)
#define L4_CFG_AGENT_CONTROL_MERROR_REP_MASK                                            (0x01000000U)

#define L4_CFG_AGENT_CONTROL_INBAND_ERROR_REP_SHIFT                                     (27U)
#define L4_CFG_AGENT_CONTROL_INBAND_ERROR_REP_MASK                                      (0x08000000U)

#define L4_CFG_AGENT_CONTROL_PROT_ERROR_PRIMARY_REP_SHIFT                               (30U)
#define L4_CFG_AGENT_CONTROL_PROT_ERROR_PRIMARY_REP_MASK                                (0x40000000U)

#define L4_CFG_AGENT_CONTROL_PROT_ERROR_SECONDARY_REP_SHIFT                             (31U)
#define L4_CFG_AGENT_CONTROL_PROT_ERROR_SECONDARY_REP_MASK                              (0x80000000U)

#define L4_CFG_AGENT_STATUS_MERROR_SHIFT                                                (24U)
#define L4_CFG_AGENT_STATUS_MERROR_MASK                                                 (0x01000000U)

#define L4_CFG_AGENT_STATUS_INBAND_ERROR_SHIFT                                          (27U)
#define L4_CFG_AGENT_STATUS_INBAND_ERROR_MASK                                           (0x08000000U)

#define L4_CFG_AGENT_STATUS_PROT_ERROR_PRIMARY_SHIFT                                    (30U)
#define L4_CFG_AGENT_STATUS_PROT_ERROR_PRIMARY_MASK                                     (0x40000000U)

#define L4_CFG_AGENT_STATUS_PROT_ERROR_SECONDARY_SHIFT                                  (31U)
#define L4_CFG_AGENT_STATUS_PROT_ERROR_SECONDARY_MASK                                   (0x80000000U)

#define L4_CFG_ERROR_LOG_CMD_SHIFT                                                      (0U)
#define L4_CFG_ERROR_LOG_CMD_MASK                                                       (0x00000007U)

#define L4_CFG_ERROR_LOG_CONNID_SHIFT                                                   (8U)
#define L4_CFG_ERROR_LOG_CONNID_MASK                                                    (0x00003f00U)

#define L4_CFG_ERROR_LOG_CODE_SHIFT                                                     (24U)
#define L4_CFG_ERROR_LOG_CODE_MASK                                                      (0x03000000U)
#define L4_CFG_ERROR_LOG_CODE_IA_IP0_0                                                   (0U)
#define L4_CFG_ERROR_LOG_CODE_IA_IP0_1                                                   (1U)
#define L4_CFG_ERROR_LOG_CODE_IA_IP0_2                                                   (2U)
#define L4_CFG_ERROR_LOG_CODE_IA_IP0_3                                                   (3U)

#define L4_CFG_ERROR_LOG_SECONDARY_SHIFT                                                (30U)
#define L4_CFG_ERROR_LOG_SECONDARY_MASK                                                 (0x40000000U)

#define L4_CFG_ERROR_LOG_MULTI_SHIFT                                                    (31U)
#define L4_CFG_ERROR_LOG_MULTI_MASK                                                     (0x80000000U)

#define L4_CFG_ERROR_LOG_REQ_INFO_SHIFT                                                 (32U)
#define L4_CFG_ERROR_LOG_REQ_INFO_MASK                                                  (0xffff00000000U)

#define L4_CFG_ERROR_LOG_ADDR_SHIFT                                                     (0U)
#define L4_CFG_ERROR_LOG_ADDR_MASK                                                      (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4_CFG_IA_IP0_H_ */

