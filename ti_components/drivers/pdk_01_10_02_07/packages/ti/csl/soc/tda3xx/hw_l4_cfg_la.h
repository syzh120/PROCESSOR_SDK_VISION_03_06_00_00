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
 *  \file   hw_l4_cfg_la.h
 *
 *  \brief  Register-level header file for L4_CFG
 *
**/

#ifndef HW_L4_CFG_LA_H_
#define HW_L4_CFG_LA_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define L4_CFG_COMPONENT                                            (0x0U)
#define L4_CFG_NETWORK                                              (0x10U)
#define L4_CFG_INITIATOR_INFO                                       (0x18U)
#define L4_CFG_NETWORK_CONTROL                                      (0x20U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define L4_CFG_COMPONENT_REV_SHIFT                                                      (0U)
#define L4_CFG_COMPONENT_REV_MASK                                                       (0x0000ffffU)

#define L4_CFG_COMPONENT_CODE_SHIFT                                                     (16U)
#define L4_CFG_COMPONENT_CODE_MASK                                                      (0xffff0000U)

#define L4_CFG_NETWORK_ID_SHIFT                                                         (32U)
#define L4_CFG_NETWORK_ID_MASK                                                          (0xffffffff00000000U)

#define L4_CFG_INITIATOR_INFO_SEGMENTS_SHIFT                                            (0U)
#define L4_CFG_INITIATOR_INFO_SEGMENTS_MASK                                             (0x0000000fU)

#define L4_CFG_INITIATOR_INFO_NUMBER_REGIONS_SHIFT                                      (16U)
#define L4_CFG_INITIATOR_INFO_NUMBER_REGIONS_MASK                                       (0x00ff0000U)

#define L4_CFG_INITIATOR_INFO_PROT_GROUPS_SHIFT                                         (24U)
#define L4_CFG_INITIATOR_INFO_PROT_GROUPS_MASK                                          (0x0f000000U)

#define L4_CFG_INITIATOR_INFO_ADDR_WIDTH_SHIFT                                          (32U)
#define L4_CFG_INITIATOR_INFO_ADDR_WIDTH_MASK                                           (0x3f00000000U)

#define L4_CFG_INITIATOR_INFO_BYTE_DATA_WIDTH_EXP_SHIFT                                 (40U)
#define L4_CFG_INITIATOR_INFO_BYTE_DATA_WIDTH_EXP_MASK                                  (0x70000000000U)

#define L4_CFG_INITIATOR_INFO_CONNID_WIDTH_SHIFT                                        (44U)
#define L4_CFG_INITIATOR_INFO_CONNID_WIDTH_MASK                                         (0x700000000000U)

#define L4_CFG_INITIATOR_INFO_THREADS_SHIFT                                             (48U)
#define L4_CFG_INITIATOR_INFO_THREADS_MASK                                              (0x7000000000000U)

#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_SHIFT                                       (8U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_MASK                                        (0x00000700U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_TA_0                                         (0U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_TA_1                                         (1U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_TA_2                                         (2U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_TA_3                                         (3U)
#define L4_CFG_NETWORK_CONTROL_TIMEOUT_BASE_TA_4                                         (4U)

#define L4_CFG_NETWORK_CONTROL_EXT_CLOCK_SHIFT                                          (40U)
#define L4_CFG_NETWORK_CONTROL_EXT_CLOCK_MASK                                           (0x10000000000U)

#define L4_CFG_NETWORK_CONTROL_THREAD0_PRI_SHIFT                                        (52U)
#define L4_CFG_NETWORK_CONTROL_THREAD0_PRI_MASK                                         (0x10000000000000U)

#define L4_CFG_NETWORK_CONTROL_CLOCK_GATE_DISABLE_SHIFT                                 (56U)
#define L4_CFG_NETWORK_CONTROL_CLOCK_GATE_DISABLE_MASK                                  (0x100000000000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4_CFG_LA_H_ */

