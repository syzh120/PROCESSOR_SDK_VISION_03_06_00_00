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
 *  \file   hw_l4_cfg_ap.h
 *
 *  \brief  Register-level header file for L4_CFG
 *
**/

#ifndef HW_L4_CFG_AP_H_
#define HW_L4_CFG_AP_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define L4_CFG_COMPONENT                                            (0x0U)
#define L4_CFG_SEGMENT_0                                            (0x100U)
#define L4_CFG_SEGMENT_1                                            (0x108U)
#define L4_CFG_SEGMENT_2                                            (0x110U)
#define L4_CFG_PROT_GROUP_MEMBERS_0                                 (0x200U)
#define L4_CFG_PROT_GROUP_MEMBERS_1                                 (0x208U)
#define L4_CFG_PROT_GROUP_MEMBERS_2                                 (0x210U)
#define L4_CFG_PROT_GROUP_MEMBERS_3                                 (0x218U)
#define L4_CFG_PROT_GROUP_MEMBERS_4                                 (0x220U)
#define L4_CFG_PROT_GROUP_MEMBERS_5                                 (0x228U)
#define L4_CFG_PROT_GROUP_MEMBERS_6                                 (0x230U)
#define L4_CFG_PROT_GROUP_MEMBERS_7                                 (0x238U)
#define L4_CFG_PROT_GROUP_ROLES_0                                   (0x280U)
#define L4_CFG_PROT_GROUP_ROLES_1                                   (0x288U)
#define L4_CFG_PROT_GROUP_ROLES_2                                   (0x290U)
#define L4_CFG_PROT_GROUP_ROLES_3                                   (0x298U)
#define L4_CFG_PROT_GROUP_ROLES_4                                   (0x2a0U)
#define L4_CFG_PROT_GROUP_ROLES_5                                   (0x2a8U)
#define L4_CFG_PROT_GROUP_ROLES_6                                   (0x2b0U)
#define L4_CFG_PROT_GROUP_ROLES_7                                   (0x2b8U)
#define L4_CFG_REGION_0                                             (0x300U)
#define L4_CFG_REGION_1                                             (0x308U)
#define L4_CFG_REGION_2                                             (0x310U)
#define L4_CFG_REGION_3                                             (0x318U)
#define L4_CFG_REGION_4                                             (0x320U)
#define L4_CFG_REGION_5                                             (0x328U)
#define L4_CFG_REGION_6                                             (0x330U)
#define L4_CFG_REGION_7                                             (0x338U)
#define L4_CFG_REGION_8                                             (0x340U)
#define L4_CFG_REGION_9                                             (0x348U)
#define L4_CFG_REGION_10                                            (0x350U)
#define L4_CFG_REGION_11                                            (0x358U)
#define L4_CFG_REGION_12                                            (0x360U)
#define L4_CFG_REGION_13                                            (0x368U)
#define L4_CFG_REGION_14                                            (0x370U)
#define L4_CFG_REGION_15                                            (0x378U)
#define L4_CFG_REGION_16                                            (0x380U)
#define L4_CFG_REGION_17                                            (0x388U)
#define L4_CFG_REGION_18                                            (0x390U)
#define L4_CFG_REGION_19                                            (0x398U)
#define L4_CFG_REGION_20                                            (0x3a0U)
#define L4_CFG_REGION_21                                            (0x3a8U)
#define L4_CFG_REGION_22                                            (0x3b0U)
#define L4_CFG_REGION_23                                            (0x3b8U)
#define L4_CFG_REGION_24                                            (0x3c0U)
#define L4_CFG_REGION_25                                            (0x3c8U)
#define L4_CFG_REGION_26                                            (0x3d0U)
#define L4_CFG_REGION_27                                            (0x3d8U)
#define L4_CFG_REGION_28                                            (0x3e0U)
#define L4_CFG_REGION_29                                            (0x3e8U)
#define L4_CFG_REGION_30                                            (0x3f0U)
#define L4_CFG_REGION_31                                            (0x3f8U)
#define L4_CFG_REGION_32                                            (0x400U)
#define L4_CFG_REGION_33                                            (0x408U)
#define L4_CFG_REGION_34                                            (0x410U)
#define L4_CFG_REGION_35                                            (0x418U)
#define L4_CFG_REGION_36                                            (0x420U)
#define L4_CFG_REGION_37                                            (0x428U)
#define L4_CFG_REGION_38                                            (0x430U)
#define L4_CFG_REGION_39                                            (0x438U)
#define L4_CFG_REGION_40                                            (0x440U)
#define L4_CFG_REGION_41                                            (0x448U)
#define L4_CFG_REGION_42                                            (0x450U)
#define L4_CFG_REGION_43                                            (0x458U)
#define L4_CFG_REGION_44                                            (0x460U)
#define L4_CFG_REGION_45                                            (0x468U)
#define L4_CFG_REGION_46                                            (0x470U)
#define L4_CFG_REGION_47                                            (0x478U)
#define L4_CFG_REGION_48                                            (0x480U)
#define L4_CFG_REGION_49                                            (0x488U)
#define L4_CFG_REGION_50                                            (0x490U)
#define L4_CFG_REGION_51                                            (0x498U)
#define L4_CFG_REGION_52                                            (0x4a0U)
#define L4_CFG_REGION_53                                            (0x4a8U)
#define L4_CFG_REGION_54                                            (0x4b0U)
#define L4_CFG_REGION_55                                            (0x4b8U)
#define L4_CFG_REGION_56                                            (0x4c0U)
#define L4_CFG_REGION_57                                            (0x4c8U)
#define L4_CFG_REGION_58                                            (0x4d0U)
#define L4_CFG_REGION_59                                            (0x4d8U)
#define L4_CFG_REGION_60                                            (0x4e0U)
#define L4_CFG_REGION_61                                            (0x4e8U)
#define L4_CFG_REGION_62                                            (0x4f0U)
#define L4_CFG_REGION_63                                            (0x4f8U)
#define L4_CFG_REGION_64                                            (0x500U)
#define L4_CFG_REGION_65                                            (0x508U)
#define L4_CFG_REGION_66                                            (0x510U)
#define L4_CFG_REGION_67                                            (0x518U)
#define L4_CFG_REGION_68                                            (0x520U)
#define L4_CFG_REGION_69                                            (0x528U)
#define L4_CFG_REGION_70                                            (0x530U)
#define L4_CFG_REGION_71                                            (0x538U)
#define L4_CFG_REGION_72                                            (0x540U)
#define L4_CFG_REGION_73                                            (0x548U)
#define L4_CFG_REGION_74                                            (0x550U)
#define L4_CFG_REGION_75                                            (0x558U)
#define L4_CFG_REGION_76                                            (0x560U)
#define L4_CFG_REGION_77                                            (0x568U)
#define L4_CFG_REGION_78                                            (0x570U)
#define L4_CFG_REGION_79                                            (0x578U)
#define L4_CFG_REGION_80                                            (0x580U)
#define L4_CFG_REGION_81                                            (0x588U)
#define L4_CFG_REGION_82                                            (0x590U)
#define L4_CFG_REGION_83                                            (0x598U)
#define L4_CFG_REGION_84                                            (0x5a0U)
#define L4_CFG_REGION_85                                            (0x5a8U)
#define L4_CFG_REGION_86                                            (0x5b0U)
#define L4_CFG_REGION_87                                            (0x5b8U)
#define L4_CFG_REGION_88                                            (0x5c0U)
#define L4_CFG_REGION_89                                            (0x5c8U)
#define L4_CFG_REGION_90                                            (0x5d0U)
#define L4_CFG_REGION_91                                            (0x5d8U)
#define L4_CFG_REGION_92                                            (0x5e0U)
#define L4_CFG_REGION_93                                            (0x5e8U)
#define L4_CFG_REGION_94                                            (0x5f0U)
#define L4_CFG_REGION_95                                            (0x5f8U)
#define L4_CFG_REGION_96                                            (0x600U)
#define L4_CFG_REGION_97                                            (0x608U)
#define L4_CFG_REGION_98                                            (0x610U)
#define L4_CFG_REGION_99                                            (0x618U)
#define L4_CFG_REGION_100                                           (0x620U)
#define L4_CFG_REGION_101                                           (0x628U)
#define L4_CFG_REGION_102                                           (0x630U)
#define L4_CFG_REGION_103                                           (0x638U)
#define L4_CFG_REGION_104                                           (0x640U)
#define L4_CFG_REGION_105                                           (0x648U)
#define L4_CFG_REGION_106                                           (0x650U)
#define L4_CFG_REGION_107                                           (0x658U)
#define L4_CFG_REGION_108                                           (0x660U)
#define L4_CFG_REGION_109                                           (0x668U)
#define L4_CFG_REGION_110                                           (0x670U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define L4_CFG_COMPONENT_REV_SHIFT                                                      (0U)
#define L4_CFG_COMPONENT_REV_MASK                                                       (0x0000ffffU)

#define L4_CFG_COMPONENT_CODE_SHIFT                                                     (16U)
#define L4_CFG_COMPONENT_CODE_MASK                                                      (0xffff0000U)

#define L4_CFG_SEGMENT_0_BASE_SHIFT                                                     (0U)
#define L4_CFG_SEGMENT_0_BASE_MASK                                                      (0xffffffffU)

#define L4_CFG_SEGMENT_0_SIZE_SHIFT                                                     (32U)
#define L4_CFG_SEGMENT_0_SIZE_MASK                                                      (0x3f00000000U)

#define L4_CFG_SEGMENT_1_BASE_SHIFT                                                     (0U)
#define L4_CFG_SEGMENT_1_BASE_MASK                                                      (0xffffffffU)

#define L4_CFG_SEGMENT_1_SIZE_SHIFT                                                     (32U)
#define L4_CFG_SEGMENT_1_SIZE_MASK                                                      (0x3f00000000U)

#define L4_CFG_SEGMENT_2_BASE_SHIFT                                                     (0U)
#define L4_CFG_SEGMENT_2_BASE_MASK                                                      (0xffffffffU)

#define L4_CFG_SEGMENT_2_SIZE_SHIFT                                                     (32U)
#define L4_CFG_SEGMENT_2_SIZE_MASK                                                      (0x3f00000000U)

#define L4_CFG_PROT_GROUP_MEMBERS_0_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_0_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_1_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_1_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_2_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_2_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_3_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_3_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_4_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_4_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_5_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_5_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_6_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_6_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_MEMBERS_7_CONNID_BIT_VECTOR_SHIFT                             (0U)
#define L4_CFG_PROT_GROUP_MEMBERS_7_CONNID_BIT_VECTOR_MASK                              (0x0000ffffU)

#define L4_CFG_PROT_GROUP_ROLES_0_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_0_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_1_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_1_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_2_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_2_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_3_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_3_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_4_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_4_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_5_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_5_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_6_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_6_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_PROT_GROUP_ROLES_7_ENABLE_SHIFT                                          (0U)
#define L4_CFG_PROT_GROUP_ROLES_7_ENABLE_MASK                                           (0xffffffffffffffffU)

#define L4_CFG_REGION_0_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_0_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_0_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_0_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_0_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_0_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_0_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_0_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_0_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_0_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_0_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_0_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_0_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_0_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_0_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_0_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_1_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_1_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_1_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_1_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_1_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_1_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_1_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_1_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_1_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_1_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_1_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_1_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_1_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_1_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_1_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_1_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_2_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_2_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_2_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_2_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_2_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_2_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_2_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_2_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_2_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_2_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_2_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_2_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_2_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_2_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_2_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_2_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_3_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_3_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_3_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_3_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_3_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_3_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_3_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_3_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_3_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_3_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_3_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_3_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_3_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_3_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_3_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_3_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_4_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_4_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_4_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_4_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_4_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_4_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_4_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_4_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_4_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_4_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_4_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_4_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_4_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_4_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_4_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_4_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_5_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_5_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_5_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_5_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_5_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_5_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_5_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_5_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_5_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_5_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_5_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_5_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_5_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_5_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_5_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_5_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_6_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_6_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_6_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_6_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_6_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_6_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_6_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_6_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_6_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_6_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_6_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_6_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_6_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_6_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_6_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_6_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_7_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_7_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_7_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_7_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_7_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_7_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_7_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_7_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_7_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_7_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_7_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_7_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_7_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_7_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_7_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_7_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_8_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_8_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_8_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_8_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_8_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_8_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_8_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_8_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_8_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_8_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_8_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_8_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_8_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_8_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_8_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_8_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_9_BASE_SHIFT                                                      (0U)
#define L4_CFG_REGION_9_BASE_MASK                                                       (0x000fffffU)

#define L4_CFG_REGION_9_ENABLE_SHIFT                                                    (32U)
#define L4_CFG_REGION_9_ENABLE_MASK                                                     (0x100000000U)

#define L4_CFG_REGION_9_SIZE_SHIFT                                                      (33U)
#define L4_CFG_REGION_9_SIZE_MASK                                                       (0x7e00000000U)

#define L4_CFG_REGION_9_PHY_TARGET_ID_SHIFT                                             (40U)
#define L4_CFG_REGION_9_PHY_TARGET_ID_MASK                                              (0x7f0000000000U)

#define L4_CFG_REGION_9_BYTE_DATA_WIDTH_EXP_SHIFT                                       (49U)
#define L4_CFG_REGION_9_BYTE_DATA_WIDTH_EXP_MASK                                        (0x6000000000000U)

#define L4_CFG_REGION_9_PROT_GROUP_ID_SHIFT                                             (52U)
#define L4_CFG_REGION_9_PROT_GROUP_ID_MASK                                              (0x70000000000000U)

#define L4_CFG_REGION_9_SEGMENT_ID_SHIFT                                                (56U)
#define L4_CFG_REGION_9_SEGMENT_ID_MASK                                                 (0x700000000000000U)

#define L4_CFG_REGION_9_MADDRSPACE_SHIFT                                                (60U)
#define L4_CFG_REGION_9_MADDRSPACE_MASK                                                 (0xf000000000000000U)

#define L4_CFG_REGION_10_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_10_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_10_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_10_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_10_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_10_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_10_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_10_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_10_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_10_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_10_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_10_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_10_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_10_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_10_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_10_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_11_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_11_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_11_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_11_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_11_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_11_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_11_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_11_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_11_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_11_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_11_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_11_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_11_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_11_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_11_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_11_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_12_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_12_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_12_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_12_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_12_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_12_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_12_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_12_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_12_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_12_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_12_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_12_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_12_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_12_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_12_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_12_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_13_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_13_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_13_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_13_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_13_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_13_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_13_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_13_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_13_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_13_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_13_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_13_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_13_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_13_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_13_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_13_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_14_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_14_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_14_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_14_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_14_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_14_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_14_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_14_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_14_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_14_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_14_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_14_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_14_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_14_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_14_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_14_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_15_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_15_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_15_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_15_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_15_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_15_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_15_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_15_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_15_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_15_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_15_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_15_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_15_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_15_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_15_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_15_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_16_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_16_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_16_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_16_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_16_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_16_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_16_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_16_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_16_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_16_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_16_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_16_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_16_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_16_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_16_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_16_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_17_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_17_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_17_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_17_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_17_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_17_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_17_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_17_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_17_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_17_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_17_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_17_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_17_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_17_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_17_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_17_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_18_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_18_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_18_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_18_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_18_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_18_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_18_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_18_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_18_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_18_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_18_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_18_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_18_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_18_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_18_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_18_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_19_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_19_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_19_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_19_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_19_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_19_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_19_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_19_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_19_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_19_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_19_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_19_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_19_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_19_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_19_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_19_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_20_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_20_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_20_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_20_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_20_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_20_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_20_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_20_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_20_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_20_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_20_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_20_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_20_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_20_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_20_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_20_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_21_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_21_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_21_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_21_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_21_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_21_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_21_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_21_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_21_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_21_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_21_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_21_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_21_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_21_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_21_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_21_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_22_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_22_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_22_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_22_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_22_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_22_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_22_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_22_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_22_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_22_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_22_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_22_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_22_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_22_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_22_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_22_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_23_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_23_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_23_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_23_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_23_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_23_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_23_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_23_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_23_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_23_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_23_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_23_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_23_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_23_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_23_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_23_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_24_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_24_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_24_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_24_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_24_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_24_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_24_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_24_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_24_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_24_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_24_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_24_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_24_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_24_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_24_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_24_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_25_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_25_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_25_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_25_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_25_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_25_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_25_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_25_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_25_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_25_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_25_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_25_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_25_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_25_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_25_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_25_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_26_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_26_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_26_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_26_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_26_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_26_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_26_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_26_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_26_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_26_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_26_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_26_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_26_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_26_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_26_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_26_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_27_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_27_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_27_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_27_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_27_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_27_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_27_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_27_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_27_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_27_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_27_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_27_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_27_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_27_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_27_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_27_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_28_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_28_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_28_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_28_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_28_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_28_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_28_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_28_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_28_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_28_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_28_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_28_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_28_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_28_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_28_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_28_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_29_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_29_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_29_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_29_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_29_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_29_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_29_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_29_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_29_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_29_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_29_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_29_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_29_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_29_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_29_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_29_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_30_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_30_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_30_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_30_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_30_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_30_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_30_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_30_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_30_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_30_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_30_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_30_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_30_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_30_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_30_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_30_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_31_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_31_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_31_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_31_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_31_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_31_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_31_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_31_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_31_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_31_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_31_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_31_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_31_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_31_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_31_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_31_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_32_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_32_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_32_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_32_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_32_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_32_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_32_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_32_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_32_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_32_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_32_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_32_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_32_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_32_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_32_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_32_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_33_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_33_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_33_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_33_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_33_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_33_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_33_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_33_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_33_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_33_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_33_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_33_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_33_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_33_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_33_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_33_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_34_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_34_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_34_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_34_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_34_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_34_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_34_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_34_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_34_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_34_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_34_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_34_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_34_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_34_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_34_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_34_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_35_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_35_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_35_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_35_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_35_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_35_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_35_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_35_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_35_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_35_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_35_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_35_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_35_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_35_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_35_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_35_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_36_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_36_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_36_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_36_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_36_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_36_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_36_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_36_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_36_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_36_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_36_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_36_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_36_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_36_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_36_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_36_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_37_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_37_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_37_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_37_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_37_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_37_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_37_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_37_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_37_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_37_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_37_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_37_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_37_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_37_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_37_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_37_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_38_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_38_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_38_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_38_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_38_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_38_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_38_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_38_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_38_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_38_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_38_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_38_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_38_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_38_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_38_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_38_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_39_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_39_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_39_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_39_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_39_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_39_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_39_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_39_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_39_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_39_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_39_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_39_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_39_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_39_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_39_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_39_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_40_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_40_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_40_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_40_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_40_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_40_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_40_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_40_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_40_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_40_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_40_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_40_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_40_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_40_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_40_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_40_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_41_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_41_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_41_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_41_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_41_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_41_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_41_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_41_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_41_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_41_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_41_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_41_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_41_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_41_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_41_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_41_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_42_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_42_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_42_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_42_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_42_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_42_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_42_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_42_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_42_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_42_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_42_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_42_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_42_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_42_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_42_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_42_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_43_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_43_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_43_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_43_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_43_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_43_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_43_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_43_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_43_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_43_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_43_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_43_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_43_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_43_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_43_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_43_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_44_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_44_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_44_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_44_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_44_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_44_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_44_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_44_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_44_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_44_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_44_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_44_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_44_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_44_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_44_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_44_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_45_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_45_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_45_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_45_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_45_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_45_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_45_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_45_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_45_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_45_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_45_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_45_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_45_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_45_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_45_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_45_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_46_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_46_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_46_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_46_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_46_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_46_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_46_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_46_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_46_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_46_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_46_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_46_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_46_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_46_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_46_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_46_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_47_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_47_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_47_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_47_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_47_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_47_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_47_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_47_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_47_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_47_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_47_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_47_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_47_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_47_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_47_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_47_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_48_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_48_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_48_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_48_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_48_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_48_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_48_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_48_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_48_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_48_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_48_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_48_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_48_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_48_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_48_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_48_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_49_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_49_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_49_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_49_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_49_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_49_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_49_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_49_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_49_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_49_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_49_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_49_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_49_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_49_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_49_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_49_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_50_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_50_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_50_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_50_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_50_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_50_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_50_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_50_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_50_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_50_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_50_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_50_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_50_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_50_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_50_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_50_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_51_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_51_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_51_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_51_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_51_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_51_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_51_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_51_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_51_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_51_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_51_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_51_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_51_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_51_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_51_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_51_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_52_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_52_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_52_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_52_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_52_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_52_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_52_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_52_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_52_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_52_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_52_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_52_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_52_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_52_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_52_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_52_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_53_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_53_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_53_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_53_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_53_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_53_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_53_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_53_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_53_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_53_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_53_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_53_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_53_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_53_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_53_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_53_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_54_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_54_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_54_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_54_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_54_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_54_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_54_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_54_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_54_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_54_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_54_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_54_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_54_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_54_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_54_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_54_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_55_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_55_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_55_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_55_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_55_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_55_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_55_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_55_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_55_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_55_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_55_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_55_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_55_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_55_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_55_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_55_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_56_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_56_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_56_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_56_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_56_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_56_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_56_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_56_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_56_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_56_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_56_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_56_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_56_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_56_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_56_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_56_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_57_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_57_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_57_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_57_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_57_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_57_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_57_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_57_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_57_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_57_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_57_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_57_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_57_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_57_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_57_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_57_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_58_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_58_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_58_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_58_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_58_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_58_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_58_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_58_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_58_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_58_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_58_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_58_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_58_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_58_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_58_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_58_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_59_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_59_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_59_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_59_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_59_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_59_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_59_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_59_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_59_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_59_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_59_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_59_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_59_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_59_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_59_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_59_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_60_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_60_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_60_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_60_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_60_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_60_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_60_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_60_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_60_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_60_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_60_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_60_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_60_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_60_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_60_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_60_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_61_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_61_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_61_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_61_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_61_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_61_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_61_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_61_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_61_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_61_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_61_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_61_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_61_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_61_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_61_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_61_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_62_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_62_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_62_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_62_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_62_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_62_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_62_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_62_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_62_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_62_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_62_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_62_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_62_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_62_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_62_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_62_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_63_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_63_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_63_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_63_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_63_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_63_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_63_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_63_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_63_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_63_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_63_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_63_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_63_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_63_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_63_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_63_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_64_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_64_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_64_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_64_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_64_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_64_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_64_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_64_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_64_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_64_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_64_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_64_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_64_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_64_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_64_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_64_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_65_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_65_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_65_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_65_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_65_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_65_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_65_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_65_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_65_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_65_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_65_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_65_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_65_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_65_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_65_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_65_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_66_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_66_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_66_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_66_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_66_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_66_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_66_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_66_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_66_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_66_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_66_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_66_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_66_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_66_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_66_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_66_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_67_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_67_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_67_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_67_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_67_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_67_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_67_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_67_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_67_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_67_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_67_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_67_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_67_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_67_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_67_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_67_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_68_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_68_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_68_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_68_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_68_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_68_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_68_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_68_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_68_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_68_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_68_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_68_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_68_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_68_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_68_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_68_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_69_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_69_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_69_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_69_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_69_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_69_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_69_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_69_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_69_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_69_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_69_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_69_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_69_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_69_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_69_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_69_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_70_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_70_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_70_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_70_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_70_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_70_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_70_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_70_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_70_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_70_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_70_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_70_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_70_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_70_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_70_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_70_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_71_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_71_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_71_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_71_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_71_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_71_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_71_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_71_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_71_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_71_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_71_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_71_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_71_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_71_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_71_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_71_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_72_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_72_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_72_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_72_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_72_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_72_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_72_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_72_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_72_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_72_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_72_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_72_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_72_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_72_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_72_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_72_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_73_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_73_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_73_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_73_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_73_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_73_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_73_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_73_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_73_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_73_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_73_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_73_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_73_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_73_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_73_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_73_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_74_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_74_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_74_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_74_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_74_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_74_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_74_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_74_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_74_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_74_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_74_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_74_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_74_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_74_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_74_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_74_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_75_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_75_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_75_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_75_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_75_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_75_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_75_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_75_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_75_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_75_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_75_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_75_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_75_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_75_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_75_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_75_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_76_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_76_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_76_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_76_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_76_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_76_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_76_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_76_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_76_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_76_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_76_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_76_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_76_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_76_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_76_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_76_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_77_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_77_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_77_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_77_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_77_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_77_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_77_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_77_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_77_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_77_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_77_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_77_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_77_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_77_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_77_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_77_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_78_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_78_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_78_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_78_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_78_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_78_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_78_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_78_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_78_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_78_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_78_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_78_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_78_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_78_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_78_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_78_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_79_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_79_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_79_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_79_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_79_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_79_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_79_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_79_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_79_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_79_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_79_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_79_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_79_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_79_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_79_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_79_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_80_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_80_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_80_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_80_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_80_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_80_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_80_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_80_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_80_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_80_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_80_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_80_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_80_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_80_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_80_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_80_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_81_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_81_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_81_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_81_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_81_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_81_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_81_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_81_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_81_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_81_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_81_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_81_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_81_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_81_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_81_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_81_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_82_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_82_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_82_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_82_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_82_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_82_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_82_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_82_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_82_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_82_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_82_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_82_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_82_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_82_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_82_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_82_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_83_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_83_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_83_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_83_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_83_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_83_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_83_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_83_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_83_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_83_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_83_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_83_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_83_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_83_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_83_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_83_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_84_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_84_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_84_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_84_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_84_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_84_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_84_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_84_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_84_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_84_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_84_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_84_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_84_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_84_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_84_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_84_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_85_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_85_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_85_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_85_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_85_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_85_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_85_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_85_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_85_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_85_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_85_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_85_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_85_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_85_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_85_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_85_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_86_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_86_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_86_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_86_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_86_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_86_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_86_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_86_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_86_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_86_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_86_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_86_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_86_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_86_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_86_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_86_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_87_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_87_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_87_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_87_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_87_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_87_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_87_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_87_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_87_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_87_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_87_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_87_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_87_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_87_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_87_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_87_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_88_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_88_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_88_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_88_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_88_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_88_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_88_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_88_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_88_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_88_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_88_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_88_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_88_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_88_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_88_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_88_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_89_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_89_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_89_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_89_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_89_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_89_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_89_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_89_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_89_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_89_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_89_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_89_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_89_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_89_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_89_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_89_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_90_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_90_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_90_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_90_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_90_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_90_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_90_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_90_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_90_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_90_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_90_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_90_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_90_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_90_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_90_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_90_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_91_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_91_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_91_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_91_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_91_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_91_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_91_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_91_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_91_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_91_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_91_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_91_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_91_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_91_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_91_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_91_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_92_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_92_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_92_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_92_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_92_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_92_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_92_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_92_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_92_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_92_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_92_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_92_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_92_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_92_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_92_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_92_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_93_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_93_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_93_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_93_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_93_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_93_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_93_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_93_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_93_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_93_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_93_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_93_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_93_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_93_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_93_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_93_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_94_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_94_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_94_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_94_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_94_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_94_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_94_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_94_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_94_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_94_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_94_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_94_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_94_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_94_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_94_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_94_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_95_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_95_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_95_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_95_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_95_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_95_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_95_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_95_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_95_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_95_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_95_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_95_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_95_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_95_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_95_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_95_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_96_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_96_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_96_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_96_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_96_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_96_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_96_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_96_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_96_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_96_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_96_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_96_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_96_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_96_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_96_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_96_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_97_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_97_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_97_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_97_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_97_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_97_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_97_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_97_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_97_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_97_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_97_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_97_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_97_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_97_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_97_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_97_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_98_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_98_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_98_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_98_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_98_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_98_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_98_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_98_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_98_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_98_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_98_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_98_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_98_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_98_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_98_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_98_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_99_BASE_SHIFT                                                     (0U)
#define L4_CFG_REGION_99_BASE_MASK                                                      (0x000fffffU)

#define L4_CFG_REGION_99_ENABLE_SHIFT                                                   (32U)
#define L4_CFG_REGION_99_ENABLE_MASK                                                    (0x100000000U)

#define L4_CFG_REGION_99_SIZE_SHIFT                                                     (33U)
#define L4_CFG_REGION_99_SIZE_MASK                                                      (0x7e00000000U)

#define L4_CFG_REGION_99_PHY_TARGET_ID_SHIFT                                            (40U)
#define L4_CFG_REGION_99_PHY_TARGET_ID_MASK                                             (0x7f0000000000U)

#define L4_CFG_REGION_99_BYTE_DATA_WIDTH_EXP_SHIFT                                      (49U)
#define L4_CFG_REGION_99_BYTE_DATA_WIDTH_EXP_MASK                                       (0x6000000000000U)

#define L4_CFG_REGION_99_PROT_GROUP_ID_SHIFT                                            (52U)
#define L4_CFG_REGION_99_PROT_GROUP_ID_MASK                                             (0x70000000000000U)

#define L4_CFG_REGION_99_SEGMENT_ID_SHIFT                                               (56U)
#define L4_CFG_REGION_99_SEGMENT_ID_MASK                                                (0x700000000000000U)

#define L4_CFG_REGION_99_MADDRSPACE_SHIFT                                               (60U)
#define L4_CFG_REGION_99_MADDRSPACE_MASK                                                (0xf000000000000000U)

#define L4_CFG_REGION_100_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_100_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_100_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_100_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_100_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_100_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_100_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_100_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_100_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_100_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_100_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_100_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_100_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_100_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_100_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_100_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_101_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_101_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_101_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_101_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_101_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_101_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_101_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_101_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_101_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_101_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_101_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_101_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_101_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_101_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_101_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_101_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_102_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_102_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_102_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_102_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_102_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_102_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_102_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_102_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_102_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_102_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_102_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_102_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_102_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_102_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_102_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_102_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_103_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_103_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_103_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_103_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_103_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_103_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_103_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_103_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_103_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_103_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_103_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_103_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_103_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_103_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_103_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_103_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_104_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_104_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_104_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_104_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_104_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_104_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_104_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_104_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_104_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_104_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_104_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_104_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_104_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_104_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_104_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_104_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_105_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_105_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_105_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_105_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_105_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_105_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_105_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_105_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_105_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_105_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_105_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_105_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_105_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_105_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_105_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_105_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_106_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_106_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_106_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_106_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_106_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_106_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_106_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_106_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_106_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_106_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_106_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_106_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_106_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_106_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_106_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_106_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_107_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_107_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_107_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_107_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_107_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_107_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_107_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_107_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_107_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_107_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_107_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_107_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_107_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_107_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_107_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_107_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_108_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_108_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_108_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_108_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_108_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_108_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_108_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_108_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_108_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_108_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_108_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_108_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_108_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_108_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_108_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_108_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_109_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_109_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_109_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_109_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_109_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_109_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_109_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_109_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_109_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_109_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_109_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_109_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_109_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_109_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_109_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_109_MADDRSPACE_MASK                                               (0xf000000000000000U)

#define L4_CFG_REGION_110_BASE_SHIFT                                                    (0U)
#define L4_CFG_REGION_110_BASE_MASK                                                     (0x000fffffU)

#define L4_CFG_REGION_110_ENABLE_SHIFT                                                  (32U)
#define L4_CFG_REGION_110_ENABLE_MASK                                                   (0x100000000U)

#define L4_CFG_REGION_110_SIZE_SHIFT                                                    (33U)
#define L4_CFG_REGION_110_SIZE_MASK                                                     (0x7e00000000U)

#define L4_CFG_REGION_110_PHY_TARGET_ID_SHIFT                                           (40U)
#define L4_CFG_REGION_110_PHY_TARGET_ID_MASK                                            (0x7f0000000000U)

#define L4_CFG_REGION_110_BYTE_DATA_WIDTH_EXP_SHIFT                                     (49U)
#define L4_CFG_REGION_110_BYTE_DATA_WIDTH_EXP_MASK                                      (0x6000000000000U)

#define L4_CFG_REGION_110_PROT_GROUP_ID_SHIFT                                           (52U)
#define L4_CFG_REGION_110_PROT_GROUP_ID_MASK                                            (0x70000000000000U)

#define L4_CFG_REGION_110_SEGMENT_ID_SHIFT                                              (56U)
#define L4_CFG_REGION_110_SEGMENT_ID_MASK                                               (0x700000000000000U)

#define L4_CFG_REGION_110_MADDRSPACE_SHIFT                                              (60U)
#define L4_CFG_REGION_110_MADDRSPACE_MASK                                               (0xf000000000000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L4_CFG_AP_H_ */

