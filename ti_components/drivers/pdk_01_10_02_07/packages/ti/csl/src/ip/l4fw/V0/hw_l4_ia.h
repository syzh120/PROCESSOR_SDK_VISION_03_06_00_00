/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file   hw_l4_ia.h
 *
 *  \brief  Register-level header file for L4 IA
 *
**/

#ifndef HW_L4_IA_H_
#define HW_L4_IA_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define L4_IA_COMPONENT_L(n)                                                            ((uint32_t)0x1000U + ((n) * 0x400U))
#define L4_IA_COMPONENT_H(n)                                                            ((uint32_t)0x1004U + ((n) * 0x400U))
#define L4_IA_CORE_L(n)                                                                 ((uint32_t)0x1018U + ((n) * 0x400U))
#define L4_IA_CORE_H(n)                                                                 ((uint32_t)0x101CU + ((n) * 0x400U))
#define L4_IA_AGENT_CONTROL_L(n)                                                        ((uint32_t)0x1020U + ((n) * 0x400U))
#define L4_IA_AGENT_CONTROL_H(n)                                                        ((uint32_t)0x1024U + ((n) * 0x400U))
#define L4_IA_AGENT_STATUS_L(n)                                                         ((uint32_t)0x1028U + ((n) * 0x400U))
#define L4_IA_AGENT_STATUS_H(n)                                                         ((uint32_t)0x102CU + ((n) * 0x400U))
#define L4_IA_ERROR_LOG_L(n)                                                            ((uint32_t)0x1058U + ((n) * 0x400U))
#define L4_IA_ERROR_LOG_H(n)                                                            ((uint32_t)0x105CU + ((n) * 0x400U))
#define L4_IA_ERROR_LOG_ADDR_L(n)                                                       ((uint32_t)0x1060U + ((n) * 0x400U))
#define L4_IA_ERROR_LOG_ADDR_H(n)                                                       ((uint32_t)0x1064U + ((n) * 0x400U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define L4_IA_AGENT_CONTROL_L_MERROR_REP_SHIFT                                          (24U)
#define L4_IA_AGENT_CONTROL_L_MERROR_REP_MASK                                           (0x01000000U)

#define L4_IA_AGENT_CONTROL_L_INBAND_ERROR_REP_SHIFT                                    (27U)
#define L4_IA_AGENT_CONTROL_L_INBAND_ERROR_REP_MASK                                     (0x08000000U)

#define L4_IA_AGENT_CONTROL_L_PROT_ERROR_PRIMARY_REP_SHIFT                              (30U)
#define L4_IA_AGENT_CONTROL_L_PROT_ERROR_PRIMARY_REP_MASK                               (0x40000000U)

#define L4_IA_AGENT_CONTROL_L_PROT_ERROR_SECONDARY_REP_SHIFT                            (31U)
#define L4_IA_AGENT_CONTROL_L_PROT_ERROR_SECONDARY_REP_MASK                             (0x80000000U)

#define L4_IA_AGENT_STATUS_L_MERROR_SHIFT                                               (24U)
#define L4_IA_AGENT_STATUS_L_MERROR_MASK                                                (0x01000000U)

#define L4_IA_AGENT_STATUS_L_INBAND_ERROR_SHIFT                                         (27U)
#define L4_IA_AGENT_STATUS_L_INBAND_ERROR_MASK                                          (0x08000000U)

#define L4_IA_AGENT_STATUS_L_PROT_ERROR_PRIMARY_SHIFT                                   (30U)
#define L4_IA_AGENT_STATUS_L_PROT_ERROR_PRIMARY_MASK                                    (0x40000000U)

#define L4_IA_AGENT_STATUS_L_PROT_ERROR_SECONDARY_SHIFT                                 (31U)
#define L4_IA_AGENT_STATUS_L_PROT_ERROR_SECONDARY_MASK                                  (0x80000000U)

#define L4_IA_AGENT_ERROR_LOG_L_CMD_SHIFT                                               (0U)
#define L4_IA_AGENT_ERROR_LOG_L_CMD_MASK                                                (0x00000007U)

#define L4_IA_AGENT_ERROR_LOG_L_CONNID_SHIFT                                            (8U)
#define L4_IA_AGENT_ERROR_LOG_L_CONNID_MASK                                             (0x00003F00U)

#define L4_IA_AGENT_ERROR_LOG_L_CODE_SHIFT                                              (24U)
#define L4_IA_AGENT_ERROR_LOG_L_CODE_MASK                                               (0x03000000U)
#define L4_IA_AGENT_ERROR_LOG_L_CODE_NO_ERROR                                           (0x0U)
#define L4_IA_AGENT_ERROR_LOG_L_CODE_ADDRESS_HOLE                                       (0x2U)
#define L4_IA_AGENT_ERROR_LOG_L_CODE_PROTECTION_VIOLATION                               (0x3U)

#define L4_IA_AGENT_ERROR_LOG_L_SECONDARY_SHIFT                                         (30U)
#define L4_IA_AGENT_ERROR_LOG_L_SECONDARY_MASK                                          (0x40000000U)

#define L4_IA_AGENT_ERROR_LOG_L_MULTI_SHIFT                                             (31U)
#define L4_IA_AGENT_ERROR_LOG_L_MULTI_MASK                                              (0x80000000U)

#define L4_IA_AGENT_ERROR_LOG_H_REQ_INFO_SHIFT                                          (0U)
#define L4_IA_AGENT_ERROR_LOG_H_REQ_INFO_MASK                                           (0x0000FFFFU)

#define L4_IA_AGENT_ERROR_LOG_ADDR_L_REQ_INFO_SHIFT                                     (0U)
#define L4_IA_AGENT_ERROR_LOG_ADDR_L_REQ_INFO_MASK                                      (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4_IA_H_ */

