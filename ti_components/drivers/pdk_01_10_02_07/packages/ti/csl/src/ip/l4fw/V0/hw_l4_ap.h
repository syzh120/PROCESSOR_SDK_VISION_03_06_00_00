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
 *  \file   hw_l4_ap.h
 *
 *  \brief  Register-level header file for L4 AP
 *
**/

#ifndef HW_L4_AP_H_
#define HW_L4_AP_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define L4_AP_COMPONENT                                               (0x0U)
#define L4_AP_SEGMENT_L(n)                                            ((uint32_t)0x100U + ((n) * 8U))
#define L4_AP_SEGMENT_H(n)                                            ((uint32_t)0x104U + ((n) * 8U))
#define L4_AP_PROT_GROUP_MEMBERS_L(n)                                 ((uint32_t)0x200U + ((n) * 8U))
#define L4_AP_PROT_GROUP_MEMBERS_H(n)                                 ((uint32_t)0x204U + ((n) * 8U))
#define L4_AP_PROT_GROUP_ROLES_L(n)                                   ((uint32_t)0x280U + ((n) * 8U))
#define L4_AP_PROT_GROUP_ROLES_H(n)                                   ((uint32_t)0x284U + ((n) * 8U))
#define L4_AP_REGION_L(n)                                             ((uint32_t)0x300U + ((n) * 8U))
#define L4_AP_REGION_H(n)                                             ((uint32_t)0x304U + ((n) * 8U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define L4_AP_COMPONENT_REV_SHIFT                                                      (0U)
#define L4_AP_COMPONENT_REV_MASK                                                       (0x0000ffffU)

#define L4_AP_COMPONENT_CODE_SHIFT                                                     (16U)
#define L4_AP_COMPONENT_CODE_MASK                                                      (0xffff0000U)

#define L4_AP_SEGMENT_L_BASE_SHIFT                                                     (0U)
#define L4_AP_SEGMENT_L_BASE_MASK                                                      (0xffffffffU)

#define L4_AP_SEGMENT_H_SIZE_SHIFT                                                     (0U)
#define L4_AP_SEGMENT_H_SIZE_MASK                                                      (0x0000003fU)

#define L4_AP_PROT_GROUP_MEMBERS_L_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_AP_PROT_GROUP_MEMBERS_L_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_AP_PROT_GROUP_ROLES_L_ENABLE_SHIFT                                          (0U)
#define L4_AP_PROT_GROUP_ROLES_L_ENABLE_MASK                                           (0xffffffffU)

#define L4_AP_PROT_GROUP_ROLES_H_ENABLE_SHIFT                                          (0U)
#define L4_AP_PROT_GROUP_ROLES_H_ENABLE_MASK                                           (0xffffffffU)

#define L4_AP_REGION_L_BASE_SHIFT                                                      (0U)
#define L4_AP_REGION_L_BASE_MASK                                                       (0x001fffffU)

#define L4_AP_REGION_H_ENABLE_SHIFT                                                    (0U)
#define L4_AP_REGION_H_ENABLE_MASK                                                     (0x1U)

#define L4_AP_REGION_H_SIZE_SHIFT                                                      (1U)
#define L4_AP_REGION_H_SIZE_MASK                                                       (0x7eU)

#define L4_AP_REGION_H_PHY_TARGET_ID_SHIFT                                             (8U)
#define L4_AP_REGION_H_PHY_TARGET_ID_MASK                                              (0x7f00U)

#define L4_AP_REGION_H_BYTE_DATA_WIDTH_EXP_SHIFT                                       (17U)
#define L4_AP_REGION_H_BYTE_DATA_WIDTH_EXP_MASK                                        (0x60000U)

#define L4_AP_REGION_H_PROT_GROUP_ID_SHIFT                                             (20U)
#define L4_AP_REGION_H_PROT_GROUP_ID_MASK                                              (0x700000U)

#define L4_AP_REGION_H_SEGMENT_ID_SHIFT                                                (24U)
#define L4_AP_REGION_H_SEGMENT_ID_MASK                                                 (0x7000000U)

#define L4_AP_REGION_H_MADDRSPACE_SHIFT                                                (28U)
#define L4_AP_REGION_H_MADDRSPACE_MASK                                                 (0xf0000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4_AP_H_ */

