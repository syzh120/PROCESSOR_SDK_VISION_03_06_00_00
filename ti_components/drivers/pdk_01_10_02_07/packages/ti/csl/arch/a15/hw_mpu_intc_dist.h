/*
 *  Copyright (C) 2008-2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_mpu_intc_dist.h
 *
 *  \brief  register-level header file for MPU
 *
**/

#ifndef HW_MPU_INTC_DIST_H_
#define HW_MPU_INTC_DIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_GICD_DCR                                                                                        (uint32_t)(0x0U)
#define MPU_GICD_ICTR                                                                                       (uint32_t)(0x4U)
#define MPU_GICD_IIDR                                                                                       (uint32_t)(0x8U)
#define MPU_GICD_ISR0                                                                                       (uint32_t)(0x80U)
#define MPU_GICD_ISR1                                                                                       (uint32_t)(0x84U)
#define MPU_GICD_ISR2                                                                                       (uint32_t)(0x88U)
#define MPU_GICD_ISR3                                                                                       (uint32_t)(0x8cU)
#define MPU_GICD_ISR4                                                                                       (uint32_t)(0x90U)
#define MPU_GICD_ISR5                                                                                       (uint32_t)(0x94U)
#define MPU_GICD_ISER0                                                                                      (uint32_t)(0x100U)
#define MPU_GICD_ISER1                                                                                      (uint32_t)(0x104U)
#define MPU_GICD_ISER2                                                                                      (uint32_t)(0x108U)
#define MPU_GICD_ISER3                                                                                      (uint32_t)(0x10cU)
#define MPU_GICD_ISER4                                                                                      (uint32_t)(0x110U)
#define MPU_GICD_ISER5                                                                                      (uint32_t)(0x114U)
#define MPU_GICD_ICER0                                                                                      (uint32_t)(0x180U)
#define MPU_GICD_ICER1                                                                                      (uint32_t)(0x184U)
#define MPU_GICD_ICER2                                                                                      (uint32_t)(0x188U)
#define MPU_GICD_ICER3                                                                                      (uint32_t)(0x18cU)
#define MPU_GICD_ICER4                                                                                      (uint32_t)(0x190U)
#define MPU_GICD_ICER5                                                                                      (uint32_t)(0x194U)
#define MPU_GICD_ISPR0                                                                                      (uint32_t)(0x200U)
#define MPU_GICD_ISPR1                                                                                      (uint32_t)(0x204U)
#define MPU_GICD_ISPR2                                                                                      (uint32_t)(0x208U)
#define MPU_GICD_ISPR3                                                                                      (uint32_t)(0x20cU)
#define MPU_GICD_ISPR4                                                                                      (uint32_t)(0x210U)
#define MPU_GICD_ISPR5                                                                                      (uint32_t)(0x214U)
#define MPU_GICD_ICPR0                                                                                      (uint32_t)(0x280U)
#define MPU_GICD_ICPR1                                                                                      (uint32_t)(0x284U)
#define MPU_GICD_ICPR2                                                                                      (uint32_t)(0x288U)
#define MPU_GICD_ICPR3                                                                                      (uint32_t)(0x28cU)
#define MPU_GICD_ICPR4                                                                                      (uint32_t)(0x290U)
#define MPU_GICD_ICPR5                                                                                      (uint32_t)(0x294U)
#define MPU_GICD_ISACTIVER0                                                                                 (uint32_t)(0x300U)
#define MPU_GICD_ISACTIVER1                                                                                 (uint32_t)(0x304U)
#define MPU_GICD_ISACTIVER2                                                                                 (uint32_t)(0x308U)
#define MPU_GICD_ISACTIVER3                                                                                 (uint32_t)(0x30cU)
#define MPU_GICD_ISACTIVER4                                                                                 (uint32_t)(0x310U)
#define MPU_GICD_ISACTIVER5                                                                                 (uint32_t)(0x314U)
#define MPU_GICD_ICACTIVER0                                                                                 (uint32_t)(0x380U)
#define MPU_GICD_ICACTIVER1                                                                                 (uint32_t)(0x384U)
#define MPU_GICD_ICACTIVER2                                                                                 (uint32_t)(0x388U)
#define MPU_GICD_ICACTIVER3                                                                                 (uint32_t)(0x38cU)
#define MPU_GICD_ICACTIVER4                                                                                 (uint32_t)(0x390U)
#define MPU_GICD_ICACTIVER5                                                                                 (uint32_t)(0x394U)
#define MPU_GICD_IPR0                                                                                       (uint32_t)(0x400U)
#define MPU_GICD_IPR1                                                                                       (uint32_t)(0x404U)
#define MPU_GICD_IPR2                                                                                       (uint32_t)(0x408U)
#define MPU_GICD_IPR3                                                                                       (uint32_t)(0x40cU)
#define MPU_GICD_IPR4                                                                                       (uint32_t)(0x410U)
#define MPU_GICD_IPR5                                                                                       (uint32_t)(0x414U)
#define MPU_GICD_IPR6                                                                                       (uint32_t)(0x418U)
#define MPU_GICD_IPR7                                                                                       (uint32_t)(0x41cU)
#define MPU_GICD_IPR8                                                                                       (uint32_t)(0x420U)
#define MPU_GICD_IPR9                                                                                       (uint32_t)(0x424U)
#define MPU_GICD_IPR10                                                                                      (uint32_t)(0x428U)
#define MPU_GICD_IPR11                                                                                      (uint32_t)(0x42cU)
#define MPU_GICD_IPR12                                                                                      (uint32_t)(0x430U)
#define MPU_GICD_IPR13                                                                                      (uint32_t)(0x434U)
#define MPU_GICD_IPR14                                                                                      (uint32_t)(0x438U)
#define MPU_GICD_IPR15                                                                                      (uint32_t)(0x43cU)
#define MPU_GICD_IPR16                                                                                      (uint32_t)(0x440U)
#define MPU_GICD_IPR17                                                                                      (uint32_t)(0x444U)
#define MPU_GICD_IPR18                                                                                      (uint32_t)(0x448U)
#define MPU_GICD_IPR19                                                                                      (uint32_t)(0x44cU)
#define MPU_GICD_IPR20                                                                                      (uint32_t)(0x450U)
#define MPU_GICD_IPR21                                                                                      (uint32_t)(0x454U)
#define MPU_GICD_IPR22                                                                                      (uint32_t)(0x458U)
#define MPU_GICD_IPR23                                                                                      (uint32_t)(0x45cU)
#define MPU_GICD_IPR24                                                                                      (uint32_t)(0x460U)
#define MPU_GICD_IPR25                                                                                      (uint32_t)(0x464U)
#define MPU_GICD_IPR26                                                                                      (uint32_t)(0x468U)
#define MPU_GICD_IPR27                                                                                      (uint32_t)(0x46cU)
#define MPU_GICD_IPR28                                                                                      (uint32_t)(0x470U)
#define MPU_GICD_IPR29                                                                                      (uint32_t)(0x474U)
#define MPU_GICD_IPR30                                                                                      (uint32_t)(0x478U)
#define MPU_GICD_IPR31                                                                                      (uint32_t)(0x47cU)
#define MPU_GICD_IPR32                                                                                      (uint32_t)(0x480U)
#define MPU_GICD_IPR33                                                                                      (uint32_t)(0x484U)
#define MPU_GICD_IPR34                                                                                      (uint32_t)(0x488U)
#define MPU_GICD_IPR35                                                                                      (uint32_t)(0x48cU)
#define MPU_GICD_IPR36                                                                                      (uint32_t)(0x490U)
#define MPU_GICD_IPR37                                                                                      (uint32_t)(0x494U)
#define MPU_GICD_IPR38                                                                                      (uint32_t)(0x498U)
#define MPU_GICD_IPR39                                                                                      (uint32_t)(0x49cU)
#define MPU_GICD_IPR40                                                                                      (uint32_t)(0x4a0U)
#define MPU_GICD_IPR41                                                                                      (uint32_t)(0x4a4U)
#define MPU_GICD_IPR42                                                                                      (uint32_t)(0x4a8U)
#define MPU_GICD_IPR43                                                                                      (uint32_t)(0x4acU)
#define MPU_GICD_IPR44                                                                                      (uint32_t)(0x4b0U)
#define MPU_GICD_IPR45                                                                                      (uint32_t)(0x4b4U)
#define MPU_GICD_IPR46                                                                                      (uint32_t)(0x4b8U)
#define MPU_GICD_IPR47                                                                                      (uint32_t)(0x4bcU)
#define MPU_GICD_IPTR0                                                                                      (uint32_t)(0x800U)
#define MPU_GICD_IPTR1                                                                                      (uint32_t)(0x804U)
#define MPU_GICD_IPTR2                                                                                      (uint32_t)(0x808U)
#define MPU_GICD_IPTR3                                                                                      (uint32_t)(0x80cU)
#define MPU_GICD_IPTR4                                                                                      (uint32_t)(0x810U)
#define MPU_GICD_IPTR5                                                                                      (uint32_t)(0x814U)
#define MPU_GICD_IPTR6                                                                                      (uint32_t)(0x818U)
#define MPU_GICD_IPTR7                                                                                      (uint32_t)(0x81cU)
#define MPU_GICD_IPTR8                                                                                      (uint32_t)(0x820U)
#define MPU_GICD_IPTR9                                                                                      (uint32_t)(0x824U)
#define MPU_GICD_IPTR10                                                                                     (uint32_t)(0x828U)
#define MPU_GICD_IPTR11                                                                                     (uint32_t)(0x82cU)
#define MPU_GICD_IPTR12                                                                                     (uint32_t)(0x830U)
#define MPU_GICD_IPTR13                                                                                     (uint32_t)(0x834U)
#define MPU_GICD_IPTR14                                                                                     (uint32_t)(0x838U)
#define MPU_GICD_IPTR15                                                                                     (uint32_t)(0x83cU)
#define MPU_GICD_IPTR16                                                                                     (uint32_t)(0x840U)
#define MPU_GICD_IPTR17                                                                                     (uint32_t)(0x844U)
#define MPU_GICD_IPTR18                                                                                     (uint32_t)(0x848U)
#define MPU_GICD_IPTR19                                                                                     (uint32_t)(0x84cU)
#define MPU_GICD_IPTR20                                                                                     (uint32_t)(0x850U)
#define MPU_GICD_IPTR21                                                                                     (uint32_t)(0x854U)
#define MPU_GICD_IPTR22                                                                                     (uint32_t)(0x858U)
#define MPU_GICD_IPTR23                                                                                     (uint32_t)(0x85cU)
#define MPU_GICD_IPTR24                                                                                     (uint32_t)(0x860U)
#define MPU_GICD_IPTR25                                                                                     (uint32_t)(0x864U)
#define MPU_GICD_IPTR26                                                                                     (uint32_t)(0x868U)
#define MPU_GICD_IPTR27                                                                                     (uint32_t)(0x86cU)
#define MPU_GICD_IPTR28                                                                                     (uint32_t)(0x870U)
#define MPU_GICD_IPTR29                                                                                     (uint32_t)(0x874U)
#define MPU_GICD_IPTR30                                                                                     (uint32_t)(0x878U)
#define MPU_GICD_IPTR31                                                                                     (uint32_t)(0x87cU)
#define MPU_GICD_IPTR32                                                                                     (uint32_t)(0x880U)
#define MPU_GICD_IPTR33                                                                                     (uint32_t)(0x884U)
#define MPU_GICD_IPTR34                                                                                     (uint32_t)(0x888U)
#define MPU_GICD_IPTR35                                                                                     (uint32_t)(0x88cU)
#define MPU_GICD_IPTR36                                                                                     (uint32_t)(0x890U)
#define MPU_GICD_IPTR37                                                                                     (uint32_t)(0x894U)
#define MPU_GICD_IPTR38                                                                                     (uint32_t)(0x898U)
#define MPU_GICD_IPTR39                                                                                     (uint32_t)(0x89cU)
#define MPU_GICD_IPTR40                                                                                     (uint32_t)(0x8a0U)
#define MPU_GICD_IPTR41                                                                                     (uint32_t)(0x8a4U)
#define MPU_GICD_IPTR42                                                                                     (uint32_t)(0x8a8U)
#define MPU_GICD_IPTR43                                                                                     (uint32_t)(0x8acU)
#define MPU_GICD_IPTR44                                                                                     (uint32_t)(0x8b0U)
#define MPU_GICD_IPTR45                                                                                     (uint32_t)(0x8b4U)
#define MPU_GICD_IPTR46                                                                                     (uint32_t)(0x8b8U)
#define MPU_GICD_IPTR47                                                                                     (uint32_t)(0x8bcU)
#define MPU_GICD_ICFR0                                                                                      (uint32_t)(0xc00U)
#define MPU_GICD_ICFR1                                                                                      (uint32_t)(0xc04U)
#define MPU_GICD_ICFR2                                                                                      (uint32_t)(0xc08U)
#define MPU_GICD_ICFR3                                                                                      (uint32_t)(0xc0cU)
#define MPU_GICD_ICFR4                                                                                      (uint32_t)(0xc10U)
#define MPU_GICD_ICFR5                                                                                      (uint32_t)(0xc14U)
#define MPU_GICD_ICFR6                                                                                      (uint32_t)(0xc18U)
#define MPU_GICD_ICFR7                                                                                      (uint32_t)(0xc1cU)
#define MPU_GICD_ICFR8                                                                                      (uint32_t)(0xc20U)
#define MPU_GICD_ICFR9                                                                                      (uint32_t)(0xc24U)
#define MPU_GICD_ICFR10                                                                                     (uint32_t)(0xc28U)
#define MPU_GICD_ICFR11                                                                                     (uint32_t)(0xc2cU)
#define MPU_GICD_PPISR                                                                                      (uint32_t)(0xd00U)
#define MPU_GICD_SPISR0                                                                                     (uint32_t)(0xd04U)
#define MPU_GICD_SPISR1                                                                                     (uint32_t)(0xd08U)
#define MPU_GICD_SPISR2                                                                                     (uint32_t)(0xd0cU)
#define MPU_GICD_SPISR3                                                                                     (uint32_t)(0xd10U)
#define MPU_GICD_SPISR4                                                                                     (uint32_t)(0xd14U)
#define MPU_GICD_SGIR                                                                                       (uint32_t)(0xf00U)
#define MPU_GICD_CPENDSGIR0                                                                                 (uint32_t)(0xf10U)
#define MPU_GICD_CPENDSGIR1                                                                                 (uint32_t)(0xf14U)
#define MPU_GICD_CPENDSGIR2                                                                                 (uint32_t)(0xf18U)
#define MPU_GICD_CPENDSGIR3                                                                                 (uint32_t)(0xf1cU)
#define MPU_GICD_SPENDSGIR0                                                                                 (uint32_t)(0xf20U)
#define MPU_GICD_SPENDSGIR1                                                                                 (uint32_t)(0xf24U)
#define MPU_GICD_SPENDSGIR2                                                                                 (uint32_t)(0xf28U)
#define MPU_GICD_SPENDSGIR3                                                                                 (uint32_t)(0xf2cU)
#define MPU_GICD_PIDR4                                                                                      (uint32_t)(0xfd0U)
#define MPU_GICD_PIDR5                                                                                      (uint32_t)(0xfd4U)
#define MPU_GICD_PIDR6                                                                                      (uint32_t)(0xfd8U)
#define MPU_GICD_PIDR7                                                                                      (uint32_t)(0xfdcU)
#define MPU_GICD_PIDR0                                                                                      (uint32_t)(0xfe0U)
#define MPU_GICD_PIDR1                                                                                      (uint32_t)(0xfe4U)
#define MPU_GICD_PIDR2                                                                                      (uint32_t)(0xfe8U)
#define MPU_GICD_PIDR3                                                                                      (uint32_t)(0xfecU)
#define MPU_GICD_CIDR0                                                                                      (uint32_t)(0xff0U)
#define MPU_GICD_CIDR1                                                                                      (uint32_t)(0xff4U)
#define MPU_GICD_CIDR2                                                                                      (uint32_t)(0xff8U)
#define MPU_GICD_CIDR3                                                                                      (uint32_t)(0xffcU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_GICD_DCR_ENABLES_SHIFT                                                                          ((uint32_t)0U)
#define MPU_GICD_DCR_ENABLES_MASK                                                                           ((uint32_t)0x00000001U)

#define MPU_GICD_DCR_RESERVED_SHIFT                                                                         ((uint32_t)2U)
#define MPU_GICD_DCR_RESERVED_MASK                                                                          ((uint32_t)0xfffffffcU)

#define MPU_GICD_DCR_ENABLENS_SHIFT                                                                         ((uint32_t)1U)
#define MPU_GICD_DCR_ENABLENS_MASK                                                                          ((uint32_t)0x00000002U)

#define MPU_GICD_ICTR_ITLINESNUMBER_SHIFT                                                                   ((uint32_t)0U)
#define MPU_GICD_ICTR_ITLINESNUMBER_MASK                                                                    ((uint32_t)0x0000001fU)

#define MPU_GICD_ICTR_CPUNUMBER_SHIFT                                                                       ((uint32_t)5U)
#define MPU_GICD_ICTR_CPUNUMBER_MASK                                                                        ((uint32_t)0x000000e0U)

#define MPU_GICD_ICTR_SECURITYEXTN_SHIFT                                                                    ((uint32_t)10U)
#define MPU_GICD_ICTR_SECURITYEXTN_MASK                                                                     ((uint32_t)0x00000400U)

#define MPU_GICD_ICTR_LSPI_SHIFT                                                                            ((uint32_t)11U)
#define MPU_GICD_ICTR_LSPI_MASK                                                                             ((uint32_t)0x0000f800U)

#define MPU_GICD_ICTR_RESERVED_SHIFT                                                                        ((uint32_t)8U)
#define MPU_GICD_ICTR_RESERVED_MASK                                                                         ((uint32_t)0x00000300U)

#define MPU_GICD_ICTR_RESERVED1_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_ICTR_RESERVED1_MASK                                                                        ((uint32_t)0xffff0000U)

#define MPU_GICD_IIDR_IMPLEMENTER_SHIFT                                                                     ((uint32_t)0U)
#define MPU_GICD_IIDR_IMPLEMENTER_MASK                                                                      ((uint32_t)0x00000fffU)

#define MPU_GICD_IIDR_REVISION_SHIFT                                                                        ((uint32_t)12U)
#define MPU_GICD_IIDR_REVISION_MASK                                                                         ((uint32_t)0x0000f000U)

#define MPU_GICD_IIDR_VARIANT_SHIFT                                                                         ((uint32_t)16U)
#define MPU_GICD_IIDR_VARIANT_MASK                                                                          ((uint32_t)0x000f0000U)

#define MPU_GICD_IIDR_PRODUCTID_SHIFT                                                                       ((uint32_t)24U)
#define MPU_GICD_IIDR_PRODUCTID_MASK                                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IIDR_RESERVED_SHIFT                                                                        ((uint32_t)20U)
#define MPU_GICD_IIDR_RESERVED_MASK                                                                         ((uint32_t)0x00f00000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_0_MASK                                                            ((uint32_t)0x00000001U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_1_SHIFT                                                           ((uint32_t)1U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_1_MASK                                                            ((uint32_t)0x00000002U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_2_SHIFT                                                           ((uint32_t)2U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_2_MASK                                                            ((uint32_t)0x00000004U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_3_SHIFT                                                           ((uint32_t)3U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_3_MASK                                                            ((uint32_t)0x00000008U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_4_SHIFT                                                           ((uint32_t)4U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_4_MASK                                                            ((uint32_t)0x00000010U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_5_SHIFT                                                           ((uint32_t)5U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_5_MASK                                                            ((uint32_t)0x00000020U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_6_SHIFT                                                           ((uint32_t)6U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_6_MASK                                                            ((uint32_t)0x00000040U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_7_SHIFT                                                           ((uint32_t)7U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_7_MASK                                                            ((uint32_t)0x00000080U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_8_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_8_MASK                                                            ((uint32_t)0x00000100U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_9_SHIFT                                                           ((uint32_t)9U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_9_MASK                                                            ((uint32_t)0x00000200U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_10_SHIFT                                                          ((uint32_t)10U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_10_MASK                                                           ((uint32_t)0x00000400U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_11_SHIFT                                                          ((uint32_t)11U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_11_MASK                                                           ((uint32_t)0x00000800U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_12_SHIFT                                                          ((uint32_t)12U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_12_MASK                                                           ((uint32_t)0x00001000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_13_SHIFT                                                          ((uint32_t)13U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_13_MASK                                                           ((uint32_t)0x00002000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_14_SHIFT                                                          ((uint32_t)14U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_14_MASK                                                           ((uint32_t)0x00004000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_15_SHIFT                                                          ((uint32_t)15U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_15_MASK                                                           ((uint32_t)0x00008000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_27_SHIFT                                                          ((uint32_t)27U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_27_MASK                                                           ((uint32_t)0x08000000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_28_SHIFT                                                          ((uint32_t)28U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_28_MASK                                                           ((uint32_t)0x10000000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_29_SHIFT                                                          ((uint32_t)29U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_29_MASK                                                           ((uint32_t)0x20000000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_30_SHIFT                                                          ((uint32_t)30U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_30_MASK                                                           ((uint32_t)0x40000000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_31_SHIFT                                                          ((uint32_t)31U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_31_MASK                                                           ((uint32_t)0x80000000U)

#define MPU_GICD_ISR0_RESERVED_SHIFT                                                                        ((uint32_t)16U)
#define MPU_GICD_ISR0_RESERVED_MASK                                                                         ((uint32_t)0x01ff0000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_25_SHIFT                                                          ((uint32_t)25U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_25_MASK                                                           ((uint32_t)0x02000000U)

#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_26_SHIFT                                                          ((uint32_t)26U)
#define MPU_GICD_ISR0_SECURITY_STATUS_FOR_26_MASK                                                           ((uint32_t)0x04000000U)

#define MPU_GICD_ISR1_SECURITY_STATUS_FOR_32_63_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ISR1_SECURITY_STATUS_FOR_32_63_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ISR2_SECURITY_STATUS_FOR_64_95_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ISR2_SECURITY_STATUS_FOR_64_95_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ISR3_SECURITY_STATUS_FOR_96_127_SHIFT                                                      ((uint32_t)0U)
#define MPU_GICD_ISR3_SECURITY_STATUS_FOR_96_127_MASK                                                       ((uint32_t)0xffffffffU)

#define MPU_GICD_ISR4_SECURITY_STATUS_FOR_127_159_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ISR4_SECURITY_STATUS_FOR_127_159_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ISR5_SECURITY_STATUS_FOR_160_191_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ISR5_SECURITY_STATUS_FOR_160_191_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_0_SHIFT                                                               ((uint32_t)0U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_0_MASK                                                                ((uint32_t)0x00000001U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_1_SHIFT                                                               ((uint32_t)1U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_1_MASK                                                                ((uint32_t)0x00000002U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_2_SHIFT                                                               ((uint32_t)2U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_2_MASK                                                                ((uint32_t)0x00000004U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_3_SHIFT                                                               ((uint32_t)3U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_3_MASK                                                                ((uint32_t)0x00000008U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_4_SHIFT                                                               ((uint32_t)4U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_4_MASK                                                                ((uint32_t)0x00000010U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_5_SHIFT                                                               ((uint32_t)5U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_5_MASK                                                                ((uint32_t)0x00000020U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_6_SHIFT                                                               ((uint32_t)6U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_6_MASK                                                                ((uint32_t)0x00000040U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_7_SHIFT                                                               ((uint32_t)7U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_7_MASK                                                                ((uint32_t)0x00000080U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_8_SHIFT                                                               ((uint32_t)8U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_8_MASK                                                                ((uint32_t)0x00000100U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_9_SHIFT                                                               ((uint32_t)9U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_9_MASK                                                                ((uint32_t)0x00000200U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_10_SHIFT                                                              ((uint32_t)10U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_10_MASK                                                               ((uint32_t)0x00000400U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_11_SHIFT                                                              ((uint32_t)11U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_11_MASK                                                               ((uint32_t)0x00000800U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_12_SHIFT                                                              ((uint32_t)12U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_12_MASK                                                               ((uint32_t)0x00001000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_13_SHIFT                                                              ((uint32_t)13U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_13_MASK                                                               ((uint32_t)0x00002000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_14_SHIFT                                                              ((uint32_t)14U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_14_MASK                                                               ((uint32_t)0x00004000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_15_SHIFT                                                              ((uint32_t)15U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_15_MASK                                                               ((uint32_t)0x00008000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_27_SHIFT                                                              ((uint32_t)27U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_27_MASK                                                               ((uint32_t)0x08000000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_28_SHIFT                                                              ((uint32_t)28U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_28_MASK                                                               ((uint32_t)0x10000000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_29_SHIFT                                                              ((uint32_t)29U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_29_MASK                                                               ((uint32_t)0x20000000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_30_SHIFT                                                              ((uint32_t)30U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_30_MASK                                                               ((uint32_t)0x40000000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_31_SHIFT                                                              ((uint32_t)31U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_31_MASK                                                               ((uint32_t)0x80000000U)

#define MPU_GICD_ISER0_RESERVED_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_ISER0_RESERVED_MASK                                                                        ((uint32_t)0x01ff0000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_25_SHIFT                                                              ((uint32_t)25U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_25_MASK                                                               ((uint32_t)0x02000000U)

#define MPU_GICD_ISER0_SET_ENABLE_FOR_26_SHIFT                                                              ((uint32_t)26U)
#define MPU_GICD_ISER0_SET_ENABLE_FOR_26_MASK                                                               ((uint32_t)0x04000000U)

#define MPU_GICD_ISER1_SET_ENABLE_FOR_63_32_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_ISER1_SET_ENABLE_FOR_63_32_MASK                                                            ((uint32_t)0xffffffffU)

#define MPU_GICD_ISER2_SET_ENABLE_FOR_95_64_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_ISER2_SET_ENABLE_FOR_95_64_MASK                                                            ((uint32_t)0xffffffffU)

#define MPU_GICD_ISER3_SET_ENABLE_FOR_127_96_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_ISER3_SET_ENABLE_FOR_127_96_MASK                                                           ((uint32_t)0xffffffffU)

#define MPU_GICD_ISER4_SET_ENABLE_FOR_159_128_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ISER4_SET_ENABLE_FOR_159_128_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ISER5_SET_ENABLE_FOR_191_160_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ISER5_SET_ENABLE_FOR_191_160_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_0_MASK                                                              ((uint32_t)0x00000001U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_1_SHIFT                                                             ((uint32_t)1U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_1_MASK                                                              ((uint32_t)0x00000002U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_2_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_2_MASK                                                              ((uint32_t)0x00000004U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_3_SHIFT                                                             ((uint32_t)3U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_3_MASK                                                              ((uint32_t)0x00000008U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_4_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_4_MASK                                                              ((uint32_t)0x00000010U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_5_SHIFT                                                             ((uint32_t)5U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_5_MASK                                                              ((uint32_t)0x00000020U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_6_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_6_MASK                                                              ((uint32_t)0x00000040U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_7_SHIFT                                                             ((uint32_t)7U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_7_MASK                                                              ((uint32_t)0x00000080U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_8_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_8_MASK                                                              ((uint32_t)0x00000100U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_9_SHIFT                                                             ((uint32_t)9U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_9_MASK                                                              ((uint32_t)0x00000200U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_10_SHIFT                                                            ((uint32_t)10U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_10_MASK                                                             ((uint32_t)0x00000400U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_11_SHIFT                                                            ((uint32_t)11U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_11_MASK                                                             ((uint32_t)0x00000800U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_12_SHIFT                                                            ((uint32_t)12U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_12_MASK                                                             ((uint32_t)0x00001000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_13_SHIFT                                                            ((uint32_t)13U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_13_MASK                                                             ((uint32_t)0x00002000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_14_SHIFT                                                            ((uint32_t)14U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_14_MASK                                                             ((uint32_t)0x00004000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_15_SHIFT                                                            ((uint32_t)15U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_15_MASK                                                             ((uint32_t)0x00008000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_27_SHIFT                                                            ((uint32_t)27U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_27_MASK                                                             ((uint32_t)0x08000000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_28_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_28_MASK                                                             ((uint32_t)0x10000000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_29_SHIFT                                                            ((uint32_t)29U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_29_MASK                                                             ((uint32_t)0x20000000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_30_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_30_MASK                                                             ((uint32_t)0x40000000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_31_SHIFT                                                            ((uint32_t)31U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_31_MASK                                                             ((uint32_t)0x80000000U)

#define MPU_GICD_ICER0_RESERVED_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_ICER0_RESERVED_MASK                                                                        ((uint32_t)0x01ff0000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_25_SHIFT                                                            ((uint32_t)25U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_25_MASK                                                             ((uint32_t)0x02000000U)

#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_26_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICER0_CLEAR_ENABLE_FOR_26_MASK                                                             ((uint32_t)0x04000000U)

#define MPU_GICD_ICER1_CLEAR_ENABLE_FOR_63_32_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ICER1_CLEAR_ENABLE_FOR_63_32_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ICER2_CLEAR_ENABLE_FOR_95_64_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ICER2_CLEAR_ENABLE_FOR_95_64_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ICER3_CLEAR_ENABLE_FOR_127_96_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_ICER3_CLEAR_ENABLE_FOR_127_96_MASK                                                         ((uint32_t)0xffffffffU)

#define MPU_GICD_ICER4_CLEAR_ENABLE_FOR_159_128_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ICER4_CLEAR_ENABLE_FOR_159_128_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ICER5_CLEAR_ENABLE_FOR_191_160_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ICER5_CLEAR_ENABLE_FOR_191_160_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_0_SHIFT                                                              ((uint32_t)0U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_0_MASK                                                               ((uint32_t)0x00000001U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_1_SHIFT                                                              ((uint32_t)1U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_1_MASK                                                               ((uint32_t)0x00000002U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_2_SHIFT                                                              ((uint32_t)2U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_2_MASK                                                               ((uint32_t)0x00000004U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_3_SHIFT                                                              ((uint32_t)3U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_3_MASK                                                               ((uint32_t)0x00000008U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_4_SHIFT                                                              ((uint32_t)4U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_4_MASK                                                               ((uint32_t)0x00000010U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_5_SHIFT                                                              ((uint32_t)5U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_5_MASK                                                               ((uint32_t)0x00000020U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_6_SHIFT                                                              ((uint32_t)6U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_6_MASK                                                               ((uint32_t)0x00000040U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_7_SHIFT                                                              ((uint32_t)7U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_7_MASK                                                               ((uint32_t)0x00000080U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_8_SHIFT                                                              ((uint32_t)8U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_8_MASK                                                               ((uint32_t)0x00000100U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_9_SHIFT                                                              ((uint32_t)9U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_9_MASK                                                               ((uint32_t)0x00000200U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_10_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_10_MASK                                                              ((uint32_t)0x00000400U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_11_SHIFT                                                             ((uint32_t)11U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_11_MASK                                                              ((uint32_t)0x00000800U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_12_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_12_MASK                                                              ((uint32_t)0x00001000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_13_SHIFT                                                             ((uint32_t)13U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_13_MASK                                                              ((uint32_t)0x00002000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_14_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_14_MASK                                                              ((uint32_t)0x00004000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_15_SHIFT                                                             ((uint32_t)15U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_15_MASK                                                              ((uint32_t)0x00008000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_27_SHIFT                                                             ((uint32_t)27U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_27_MASK                                                              ((uint32_t)0x08000000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_28_SHIFT                                                             ((uint32_t)28U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_28_MASK                                                              ((uint32_t)0x10000000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_29_SHIFT                                                             ((uint32_t)29U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_29_MASK                                                              ((uint32_t)0x20000000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_30_SHIFT                                                             ((uint32_t)30U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_30_MASK                                                              ((uint32_t)0x40000000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_31_SHIFT                                                             ((uint32_t)31U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_31_MASK                                                              ((uint32_t)0x80000000U)

#define MPU_GICD_ISPR0_RESERVED_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_ISPR0_RESERVED_MASK                                                                        ((uint32_t)0x01ff0000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_25_SHIFT                                                             ((uint32_t)25U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_25_MASK                                                              ((uint32_t)0x02000000U)

#define MPU_GICD_ISPR0_SET_PENDING_FOR_26_SHIFT                                                             ((uint32_t)26U)
#define MPU_GICD_ISPR0_SET_PENDING_FOR_26_MASK                                                              ((uint32_t)0x04000000U)

#define MPU_GICD_ISPR1_SET_PENDING_FOR_63_32_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_ISPR1_SET_PENDING_FOR_63_32_MASK                                                           ((uint32_t)0xffffffffU)

#define MPU_GICD_ISPR2_SET_PENDING_FOR_95_64_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_ISPR2_SET_PENDING_FOR_95_64_MASK                                                           ((uint32_t)0xffffffffU)

#define MPU_GICD_ISPR3_SET_PENDING_FOR_127_96_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ISPR3_SET_PENDING_FOR_127_96_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ISPR4_SET_PENDING_FOR_159_128_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_ISPR4_SET_PENDING_FOR_159_128_MASK                                                         ((uint32_t)0xffffffffU)

#define MPU_GICD_ISPR5_SET_PENDING_FOR_191_160_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_ISPR5_SET_PENDING_FOR_191_160_MASK                                                         ((uint32_t)0xffffffffU)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_0_MASK                                                              ((uint32_t)0x00000001U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_1_SHIFT                                                             ((uint32_t)1U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_1_MASK                                                              ((uint32_t)0x00000002U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_2_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_2_MASK                                                              ((uint32_t)0x00000004U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_3_SHIFT                                                             ((uint32_t)3U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_3_MASK                                                              ((uint32_t)0x00000008U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_4_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_4_MASK                                                              ((uint32_t)0x00000010U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_5_SHIFT                                                             ((uint32_t)5U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_5_MASK                                                              ((uint32_t)0x00000020U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_6_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_6_MASK                                                              ((uint32_t)0x00000040U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_7_SHIFT                                                             ((uint32_t)7U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_7_MASK                                                              ((uint32_t)0x00000080U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_8_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_8_MASK                                                              ((uint32_t)0x00000100U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_9_SHIFT                                                             ((uint32_t)9U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_9_MASK                                                              ((uint32_t)0x00000200U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_10_SHIFT                                                            ((uint32_t)10U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_10_MASK                                                             ((uint32_t)0x00000400U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_11_SHIFT                                                            ((uint32_t)11U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_11_MASK                                                             ((uint32_t)0x00000800U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_12_SHIFT                                                            ((uint32_t)12U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_12_MASK                                                             ((uint32_t)0x00001000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_13_SHIFT                                                            ((uint32_t)13U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_13_MASK                                                             ((uint32_t)0x00002000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_14_SHIFT                                                            ((uint32_t)14U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_14_MASK                                                             ((uint32_t)0x00004000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_15_SHIFT                                                            ((uint32_t)15U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_15_MASK                                                             ((uint32_t)0x00008000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_27_SHIFT                                                            ((uint32_t)27U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_27_MASK                                                             ((uint32_t)0x08000000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_28_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_28_MASK                                                             ((uint32_t)0x10000000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_29_SHIFT                                                            ((uint32_t)29U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_29_MASK                                                             ((uint32_t)0x20000000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_30_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_30_MASK                                                             ((uint32_t)0x40000000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_31_SHIFT                                                            ((uint32_t)31U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_31_MASK                                                             ((uint32_t)0x80000000U)

#define MPU_GICD_ICPR0_RESERVED_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_ICPR0_RESERVED_MASK                                                                        ((uint32_t)0x01ff0000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_25_SHIFT                                                            ((uint32_t)25U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_25_MASK                                                             ((uint32_t)0x02000000U)

#define MPU_GICD_ICPR0_CLEARPENDING_FOR_26_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICPR0_CLEARPENDING_FOR_26_MASK                                                             ((uint32_t)0x04000000U)

#define MPU_GICD_ICPR1_CLEARPENDING_FOR_63_32_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ICPR1_CLEARPENDING_FOR_63_32_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ICPR2_CLEARPENDING_FOR_95_64_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ICPR2_CLEARPENDING_FOR_95_64_MASK                                                          ((uint32_t)0xffffffffU)

#define MPU_GICD_ICPR3_CLEARPENDING_FOR_127_96_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_ICPR3_CLEARPENDING_FOR_127_96_MASK                                                         ((uint32_t)0xffffffffU)

#define MPU_GICD_ICPR4_CLEARPENDING_FOR_159_128_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ICPR4_CLEARPENDING_FOR_159_128_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ICPR5_CLEARPENDING_FOR_191_160_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_ICPR5_CLEARPENDING_FOR_191_160_MASK                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_0_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_0_MASK                                                          ((uint32_t)0x00000001U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_1_SHIFT                                                         ((uint32_t)1U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_1_MASK                                                          ((uint32_t)0x00000002U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_2_SHIFT                                                         ((uint32_t)2U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_2_MASK                                                          ((uint32_t)0x00000004U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_3_SHIFT                                                         ((uint32_t)3U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_3_MASK                                                          ((uint32_t)0x00000008U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_4_SHIFT                                                         ((uint32_t)4U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_4_MASK                                                          ((uint32_t)0x00000010U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_5_SHIFT                                                         ((uint32_t)5U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_5_MASK                                                          ((uint32_t)0x00000020U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_6_SHIFT                                                         ((uint32_t)6U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_6_MASK                                                          ((uint32_t)0x00000040U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_7_SHIFT                                                         ((uint32_t)7U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_7_MASK                                                          ((uint32_t)0x00000080U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_8_SHIFT                                                         ((uint32_t)8U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_8_MASK                                                          ((uint32_t)0x00000100U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_9_SHIFT                                                         ((uint32_t)9U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_9_MASK                                                          ((uint32_t)0x00000200U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_10_SHIFT                                                        ((uint32_t)10U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_10_MASK                                                         ((uint32_t)0x00000400U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_11_SHIFT                                                        ((uint32_t)11U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_11_MASK                                                         ((uint32_t)0x00000800U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_12_SHIFT                                                        ((uint32_t)12U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_12_MASK                                                         ((uint32_t)0x00001000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_13_SHIFT                                                        ((uint32_t)13U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_13_MASK                                                         ((uint32_t)0x00002000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_14_SHIFT                                                        ((uint32_t)14U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_14_MASK                                                         ((uint32_t)0x00004000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_15_SHIFT                                                        ((uint32_t)15U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_15_MASK                                                         ((uint32_t)0x00008000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_27_SHIFT                                                        ((uint32_t)27U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_27_MASK                                                         ((uint32_t)0x08000000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_28_SHIFT                                                        ((uint32_t)28U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_28_MASK                                                         ((uint32_t)0x10000000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_29_SHIFT                                                        ((uint32_t)29U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_29_MASK                                                         ((uint32_t)0x20000000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_30_SHIFT                                                        ((uint32_t)30U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_30_MASK                                                         ((uint32_t)0x40000000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_31_SHIFT                                                        ((uint32_t)31U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_31_MASK                                                         ((uint32_t)0x80000000U)

#define MPU_GICD_ISACTIVER0_RESERVED_SHIFT                                                                  ((uint32_t)16U)
#define MPU_GICD_ISACTIVER0_RESERVED_MASK                                                                   ((uint32_t)0x01ff0000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_25_SHIFT                                                        ((uint32_t)25U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_25_MASK                                                         ((uint32_t)0x02000000U)

#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_26_SHIFT                                                        ((uint32_t)26U)
#define MPU_GICD_ISACTIVER0_ACTIVE_BITS_FOR_26_MASK                                                         ((uint32_t)0x04000000U)

#define MPU_GICD_ISACTIVER1_ACTIVE_BITS_FOR_63_32_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ISACTIVER1_ACTIVE_BITS_FOR_63_32_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ISACTIVER2_ACTIVE_BITS_FOR_95_64_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ISACTIVER2_ACTIVE_BITS_FOR_95_64_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ISACTIVER3_ACTIVE_BITS_FOR_127_96_SHIFT                                                    ((uint32_t)0U)
#define MPU_GICD_ISACTIVER3_ACTIVE_BITS_FOR_127_96_MASK                                                     ((uint32_t)0xffffffffU)

#define MPU_GICD_ISACTIVER4_ACTIVE_BITS_FOR_159_128_SHIFT                                                   ((uint32_t)0U)
#define MPU_GICD_ISACTIVER4_ACTIVE_BITS_FOR_159_128_MASK                                                    ((uint32_t)0xffffffffU)

#define MPU_GICD_ISACTIVER5_ACTIVE_BITS_FOR_191_160_SHIFT                                                   ((uint32_t)0U)
#define MPU_GICD_ISACTIVER5_ACTIVE_BITS_FOR_191_160_MASK                                                    ((uint32_t)0xffffffffU)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_0_SHIFT                                                         ((uint32_t)0U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_0_MASK                                                          ((uint32_t)0x00000001U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_1_SHIFT                                                         ((uint32_t)1U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_1_MASK                                                          ((uint32_t)0x00000002U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_2_SHIFT                                                         ((uint32_t)2U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_2_MASK                                                          ((uint32_t)0x00000004U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_3_SHIFT                                                         ((uint32_t)3U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_3_MASK                                                          ((uint32_t)0x00000008U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_4_SHIFT                                                         ((uint32_t)4U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_4_MASK                                                          ((uint32_t)0x00000010U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_5_SHIFT                                                         ((uint32_t)5U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_5_MASK                                                          ((uint32_t)0x00000020U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_6_SHIFT                                                         ((uint32_t)6U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_6_MASK                                                          ((uint32_t)0x00000040U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_7_SHIFT                                                         ((uint32_t)7U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_7_MASK                                                          ((uint32_t)0x00000080U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_8_SHIFT                                                         ((uint32_t)8U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_8_MASK                                                          ((uint32_t)0x00000100U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_9_SHIFT                                                         ((uint32_t)9U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_9_MASK                                                          ((uint32_t)0x00000200U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_10_SHIFT                                                        ((uint32_t)10U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_10_MASK                                                         ((uint32_t)0x00000400U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_11_SHIFT                                                        ((uint32_t)11U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_11_MASK                                                         ((uint32_t)0x00000800U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_12_SHIFT                                                        ((uint32_t)12U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_12_MASK                                                         ((uint32_t)0x00001000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_13_SHIFT                                                        ((uint32_t)13U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_13_MASK                                                         ((uint32_t)0x00002000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_14_SHIFT                                                        ((uint32_t)14U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_14_MASK                                                         ((uint32_t)0x00004000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_15_SHIFT                                                        ((uint32_t)15U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_15_MASK                                                         ((uint32_t)0x00008000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_27_SHIFT                                                        ((uint32_t)27U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_27_MASK                                                         ((uint32_t)0x08000000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_28_SHIFT                                                        ((uint32_t)28U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_28_MASK                                                         ((uint32_t)0x10000000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_29_SHIFT                                                        ((uint32_t)29U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_29_MASK                                                         ((uint32_t)0x20000000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_30_SHIFT                                                        ((uint32_t)30U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_30_MASK                                                         ((uint32_t)0x40000000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_31_SHIFT                                                        ((uint32_t)31U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_31_MASK                                                         ((uint32_t)0x80000000U)

#define MPU_GICD_ICACTIVER0_RESERVED_SHIFT                                                                  ((uint32_t)16U)
#define MPU_GICD_ICACTIVER0_RESERVED_MASK                                                                   ((uint32_t)0x01ff0000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_25_SHIFT                                                        ((uint32_t)25U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_25_MASK                                                         ((uint32_t)0x02000000U)

#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_26_SHIFT                                                        ((uint32_t)26U)
#define MPU_GICD_ICACTIVER0_ACTIVE_BITS_FOR_26_MASK                                                         ((uint32_t)0x04000000U)

#define MPU_GICD_ICACTIVER1_ACTIVE_BITS_FOR_63_32_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ICACTIVER1_ACTIVE_BITS_FOR_63_32_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ICACTIVER2_ACTIVE_BITS_FOR_95_64_SHIFT                                                     ((uint32_t)0U)
#define MPU_GICD_ICACTIVER2_ACTIVE_BITS_FOR_95_64_MASK                                                      ((uint32_t)0xffffffffU)

#define MPU_GICD_ICACTIVER3_ACTIVE_BITS_FOR_127_96_SHIFT                                                    ((uint32_t)0U)
#define MPU_GICD_ICACTIVER3_ACTIVE_BITS_FOR_127_96_MASK                                                     ((uint32_t)0xffffffffU)

#define MPU_GICD_ICACTIVER4_ACTIVE_BITS_FOR_159_128_SHIFT                                                   ((uint32_t)0U)
#define MPU_GICD_ICACTIVER4_ACTIVE_BITS_FOR_159_128_MASK                                                    ((uint32_t)0xffffffffU)

#define MPU_GICD_ICACTIVER5_ACTIVE_BITS_FOR_191_160_SHIFT                                                   ((uint32_t)0U)
#define MPU_GICD_ICACTIVER5_ACTIVE_BITS_FOR_191_160_MASK                                                    ((uint32_t)0xffffffffU)

#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR0_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR1_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR2_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR3_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR4_RESERVED_SHIFT                                                                        ((uint32_t)0U)
#define MPU_GICD_IPR4_RESERVED_MASK                                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR4_RESERVED1_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_IPR4_RESERVED1_MASK                                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR4_RESERVED2_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_IPR4_RESERVED2_MASK                                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR4_RESERVED3_SHIFT                                                                       ((uint32_t)24U)
#define MPU_GICD_IPR4_RESERVED3_MASK                                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPR5_RESERVED_SHIFT                                                                        ((uint32_t)0U)
#define MPU_GICD_IPR5_RESERVED_MASK                                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR5_RESERVED1_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_IPR5_RESERVED1_MASK                                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR5_RESERVED2_SHIFT                                                                       ((uint32_t)16U)
#define MPU_GICD_IPR5_RESERVED2_MASK                                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR5_RESERVED3_SHIFT                                                                       ((uint32_t)24U)
#define MPU_GICD_IPR5_RESERVED3_MASK                                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR6_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR6_RESERVED1_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_IPR6_RESERVED1_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR7_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR8_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_2_SHIFT                                                           ((uint32_t)16U)
#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_2_MASK                                                            ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_1_SHIFT                                                           ((uint32_t)8U)
#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_1_MASK                                                            ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_3_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_3_MASK                                                            ((uint32_t)0xff000000U)

#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_0_SHIFT                                                           ((uint32_t)0U)
#define MPU_GICD_IPR9_PRIORITY_BYTEOFFSET_0_MASK                                                            ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR10_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR11_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR12_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR13_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR14_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR15_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR16_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR17_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR18_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR19_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR20_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR21_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR22_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR23_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR24_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR25_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR26_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR27_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR28_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR29_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR30_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR31_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR32_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR33_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR34_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR35_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR36_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR37_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR38_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR39_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR40_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR41_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR42_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR43_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR44_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR45_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR46_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_2_SHIFT                                                          ((uint32_t)16U)
#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_2_MASK                                                           ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_1_SHIFT                                                          ((uint32_t)8U)
#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_1_MASK                                                           ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_3_SHIFT                                                          ((uint32_t)24U)
#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_3_MASK                                                           ((uint32_t)0xff000000U)

#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_0_SHIFT                                                          ((uint32_t)0U)
#define MPU_GICD_IPR47_PRIORITY_BYTEOFFSET_0_MASK                                                           ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR0_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR1_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR2_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR3_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR4_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR4_RESERVED_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR4_RESERVED1_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_IPTR4_RESERVED1_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR4_RESERVED2_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_IPTR4_RESERVED2_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR4_RESERVED3_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_IPTR4_RESERVED3_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR5_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR5_RESERVED_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR5_RESERVED1_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_IPTR5_RESERVED1_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR5_RESERVED2_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_IPTR5_RESERVED2_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR5_RESERVED3_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_IPTR5_RESERVED3_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR6_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR6_RESERVED_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR6_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR7_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR8_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                        ((uint32_t)0U)
#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_0_MASK                                                         ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                        ((uint32_t)8U)
#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_1_MASK                                                         ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                        ((uint32_t)16U)
#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_2_MASK                                                         ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                        ((uint32_t)24U)
#define MPU_GICD_IPTR9_CPUTARGETS_BYTEOFFSET_3_MASK                                                         ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR10_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR11_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR12_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR13_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR14_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR15_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR16_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR17_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR18_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR19_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR20_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR21_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR22_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR23_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR24_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR25_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR26_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR27_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR28_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR29_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR30_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR31_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR32_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR33_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR34_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR35_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR36_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR37_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR38_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR39_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR40_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR41_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR42_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR43_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR44_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR45_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR46_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_0_SHIFT                                                       ((uint32_t)0U)
#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_0_MASK                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_1_SHIFT                                                       ((uint32_t)8U)
#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_1_MASK                                                        ((uint32_t)0x0000ff00U)

#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_2_SHIFT                                                       ((uint32_t)16U)
#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_2_MASK                                                        ((uint32_t)0x00ff0000U)

#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_3_SHIFT                                                       ((uint32_t)24U)
#define MPU_GICD_IPTR47_CPUTARGETS_BYTEOFFSET_3_MASK                                                        ((uint32_t)0xff000000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR0_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR1_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR2_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR3_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR4_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR5_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR6_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR7_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR8_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_0_SHIFT                                                             ((uint32_t)0U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_0_MASK                                                              ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_1_SHIFT                                                             ((uint32_t)2U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_1_MASK                                                              ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_2_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_2_MASK                                                              ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_3_SHIFT                                                             ((uint32_t)6U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_3_MASK                                                              ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_4_SHIFT                                                             ((uint32_t)8U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_4_MASK                                                              ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_5_SHIFT                                                             ((uint32_t)10U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_5_MASK                                                              ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_6_SHIFT                                                             ((uint32_t)12U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_6_MASK                                                              ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_7_SHIFT                                                             ((uint32_t)14U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_7_MASK                                                              ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_8_SHIFT                                                             ((uint32_t)16U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_8_MASK                                                              ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_9_SHIFT                                                             ((uint32_t)18U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_9_MASK                                                              ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_10_SHIFT                                                            ((uint32_t)20U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_10_MASK                                                             ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_11_SHIFT                                                            ((uint32_t)22U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_11_MASK                                                             ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_12_SHIFT                                                            ((uint32_t)24U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_12_MASK                                                             ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_13_SHIFT                                                            ((uint32_t)26U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_13_MASK                                                             ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_14_SHIFT                                                            ((uint32_t)28U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_14_MASK                                                             ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_15_SHIFT                                                            ((uint32_t)30U)
#define MPU_GICD_ICFR9_INT_CONFIG_FIELD_15_MASK                                                             ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_0_SHIFT                                                            ((uint32_t)0U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_0_MASK                                                             ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_1_SHIFT                                                            ((uint32_t)2U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_1_MASK                                                             ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_2_SHIFT                                                            ((uint32_t)4U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_2_MASK                                                             ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_3_SHIFT                                                            ((uint32_t)6U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_3_MASK                                                             ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_4_SHIFT                                                            ((uint32_t)8U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_4_MASK                                                             ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_5_SHIFT                                                            ((uint32_t)10U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_5_MASK                                                             ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_6_SHIFT                                                            ((uint32_t)12U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_6_MASK                                                             ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_7_SHIFT                                                            ((uint32_t)14U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_7_MASK                                                             ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_8_SHIFT                                                            ((uint32_t)16U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_8_MASK                                                             ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_9_SHIFT                                                            ((uint32_t)18U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_9_MASK                                                             ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_10_SHIFT                                                           ((uint32_t)20U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_10_MASK                                                            ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_11_SHIFT                                                           ((uint32_t)22U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_11_MASK                                                            ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_12_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_12_MASK                                                            ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_13_SHIFT                                                           ((uint32_t)26U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_13_MASK                                                            ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_14_SHIFT                                                           ((uint32_t)28U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_14_MASK                                                            ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_15_SHIFT                                                           ((uint32_t)30U)
#define MPU_GICD_ICFR10_INT_CONFIG_FIELD_15_MASK                                                            ((uint32_t)0xc0000000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_0_SHIFT                                                            ((uint32_t)0U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_0_MASK                                                             ((uint32_t)0x00000003U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_1_SHIFT                                                            ((uint32_t)2U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_1_MASK                                                             ((uint32_t)0x0000000cU)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_2_SHIFT                                                            ((uint32_t)4U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_2_MASK                                                             ((uint32_t)0x00000030U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_3_SHIFT                                                            ((uint32_t)6U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_3_MASK                                                             ((uint32_t)0x000000c0U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_4_SHIFT                                                            ((uint32_t)8U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_4_MASK                                                             ((uint32_t)0x00000300U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_5_SHIFT                                                            ((uint32_t)10U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_5_MASK                                                             ((uint32_t)0x00000c00U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_6_SHIFT                                                            ((uint32_t)12U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_6_MASK                                                             ((uint32_t)0x00003000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_7_SHIFT                                                            ((uint32_t)14U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_7_MASK                                                             ((uint32_t)0x0000c000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_8_SHIFT                                                            ((uint32_t)16U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_8_MASK                                                             ((uint32_t)0x00030000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_9_SHIFT                                                            ((uint32_t)18U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_9_MASK                                                             ((uint32_t)0x000c0000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_10_SHIFT                                                           ((uint32_t)20U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_10_MASK                                                            ((uint32_t)0x00300000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_11_SHIFT                                                           ((uint32_t)22U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_11_MASK                                                            ((uint32_t)0x00c00000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_12_SHIFT                                                           ((uint32_t)24U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_12_MASK                                                            ((uint32_t)0x03000000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_13_SHIFT                                                           ((uint32_t)26U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_13_MASK                                                            ((uint32_t)0x0c000000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_14_SHIFT                                                           ((uint32_t)28U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_14_MASK                                                            ((uint32_t)0x30000000U)

#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_15_SHIFT                                                           ((uint32_t)30U)
#define MPU_GICD_ICFR11_INT_CONFIG_FIELD_15_MASK                                                            ((uint32_t)0xc0000000U)

#define MPU_GICD_PPISR_PPI_STATUS_0_SHIFT                                                                   ((uint32_t)12U)
#define MPU_GICD_PPISR_PPI_STATUS_0_MASK                                                                    ((uint32_t)0x00001000U)

#define MPU_GICD_PPISR_PPI_STATUS_1_SHIFT                                                                   ((uint32_t)13U)
#define MPU_GICD_PPISR_PPI_STATUS_1_MASK                                                                    ((uint32_t)0x00002000U)

#define MPU_GICD_PPISR_PPI_STATUS_2_SHIFT                                                                   ((uint32_t)14U)
#define MPU_GICD_PPISR_PPI_STATUS_2_MASK                                                                    ((uint32_t)0x00004000U)

#define MPU_GICD_PPISR_PPI_STATUS_3_SHIFT                                                                   ((uint32_t)15U)
#define MPU_GICD_PPISR_PPI_STATUS_3_MASK                                                                    ((uint32_t)0x00008000U)

#define MPU_GICD_PPISR_PPI_STATUS_4_SHIFT                                                                   ((uint32_t)11U)
#define MPU_GICD_PPISR_PPI_STATUS_4_MASK                                                                    ((uint32_t)0x00000800U)

#define MPU_GICD_PPISR_PPI_STATUS_5_SHIFT                                                                   ((uint32_t)10U)
#define MPU_GICD_PPISR_PPI_STATUS_5_MASK                                                                    ((uint32_t)0x00000400U)

#define MPU_GICD_PPISR_PPI_STATUS_6_SHIFT                                                                   ((uint32_t)9U)
#define MPU_GICD_PPISR_PPI_STATUS_6_MASK                                                                    ((uint32_t)0x00000200U)

#define MPU_GICD_PPISR_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_PPISR_RESERVED_MASK                                                                        ((uint32_t)0x000001ffU)

#define MPU_GICD_PPISR_RESERVED1_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_PPISR_RESERVED1_MASK                                                                       ((uint32_t)0xffff0000U)

#define MPU_GICD_SPISR0_SPI_0_SHIFT                                                                         ((uint32_t)0U)
#define MPU_GICD_SPISR0_SPI_0_MASK                                                                          ((uint32_t)0x00000001U)

#define MPU_GICD_SPISR0_SPI_1_SHIFT                                                                         ((uint32_t)1U)
#define MPU_GICD_SPISR0_SPI_1_MASK                                                                          ((uint32_t)0x00000002U)

#define MPU_GICD_SPISR0_SPI_2_SHIFT                                                                         ((uint32_t)2U)
#define MPU_GICD_SPISR0_SPI_2_MASK                                                                          ((uint32_t)0x00000004U)

#define MPU_GICD_SPISR0_SPI_3_SHIFT                                                                         ((uint32_t)3U)
#define MPU_GICD_SPISR0_SPI_3_MASK                                                                          ((uint32_t)0x00000008U)

#define MPU_GICD_SPISR0_SPI_4_SHIFT                                                                         ((uint32_t)4U)
#define MPU_GICD_SPISR0_SPI_4_MASK                                                                          ((uint32_t)0x00000010U)

#define MPU_GICD_SPISR0_SPI_5_SHIFT                                                                         ((uint32_t)5U)
#define MPU_GICD_SPISR0_SPI_5_MASK                                                                          ((uint32_t)0x00000020U)

#define MPU_GICD_SPISR0_SPI_6_SHIFT                                                                         ((uint32_t)6U)
#define MPU_GICD_SPISR0_SPI_6_MASK                                                                          ((uint32_t)0x00000040U)

#define MPU_GICD_SPISR0_SPI_7_SHIFT                                                                         ((uint32_t)7U)
#define MPU_GICD_SPISR0_SPI_7_MASK                                                                          ((uint32_t)0x00000080U)

#define MPU_GICD_SPISR0_SPI_8_SHIFT                                                                         ((uint32_t)8U)
#define MPU_GICD_SPISR0_SPI_8_MASK                                                                          ((uint32_t)0x00000100U)

#define MPU_GICD_SPISR0_SPI_9_SHIFT                                                                         ((uint32_t)9U)
#define MPU_GICD_SPISR0_SPI_9_MASK                                                                          ((uint32_t)0x00000200U)

#define MPU_GICD_SPISR0_SPI_10_SHIFT                                                                        ((uint32_t)10U)
#define MPU_GICD_SPISR0_SPI_10_MASK                                                                         ((uint32_t)0x00000400U)

#define MPU_GICD_SPISR0_SPI_11_SHIFT                                                                        ((uint32_t)11U)
#define MPU_GICD_SPISR0_SPI_11_MASK                                                                         ((uint32_t)0x00000800U)

#define MPU_GICD_SPISR0_SPI_12_SHIFT                                                                        ((uint32_t)12U)
#define MPU_GICD_SPISR0_SPI_12_MASK                                                                         ((uint32_t)0x00001000U)

#define MPU_GICD_SPISR0_SPI_13_SHIFT                                                                        ((uint32_t)13U)
#define MPU_GICD_SPISR0_SPI_13_MASK                                                                         ((uint32_t)0x00002000U)

#define MPU_GICD_SPISR0_SPI_14_SHIFT                                                                        ((uint32_t)14U)
#define MPU_GICD_SPISR0_SPI_14_MASK                                                                         ((uint32_t)0x00004000U)

#define MPU_GICD_SPISR0_SPI_15_SHIFT                                                                        ((uint32_t)15U)
#define MPU_GICD_SPISR0_SPI_15_MASK                                                                         ((uint32_t)0x00008000U)

#define MPU_GICD_SPISR0_SPI_16_SHIFT                                                                        ((uint32_t)16U)
#define MPU_GICD_SPISR0_SPI_16_MASK                                                                         ((uint32_t)0x00010000U)

#define MPU_GICD_SPISR0_SPI_17_SHIFT                                                                        ((uint32_t)17U)
#define MPU_GICD_SPISR0_SPI_17_MASK                                                                         ((uint32_t)0x00020000U)

#define MPU_GICD_SPISR0_SPI_18_SHIFT                                                                        ((uint32_t)18U)
#define MPU_GICD_SPISR0_SPI_18_MASK                                                                         ((uint32_t)0x00040000U)

#define MPU_GICD_SPISR0_SPI_19_SHIFT                                                                        ((uint32_t)19U)
#define MPU_GICD_SPISR0_SPI_19_MASK                                                                         ((uint32_t)0x00080000U)

#define MPU_GICD_SPISR0_SPI_20_SHIFT                                                                        ((uint32_t)20U)
#define MPU_GICD_SPISR0_SPI_20_MASK                                                                         ((uint32_t)0x00100000U)

#define MPU_GICD_SPISR0_SPI_21_SHIFT                                                                        ((uint32_t)21U)
#define MPU_GICD_SPISR0_SPI_21_MASK                                                                         ((uint32_t)0x00200000U)

#define MPU_GICD_SPISR0_SPI_22_SHIFT                                                                        ((uint32_t)22U)
#define MPU_GICD_SPISR0_SPI_22_MASK                                                                         ((uint32_t)0x00400000U)

#define MPU_GICD_SPISR0_SPI_23_SHIFT                                                                        ((uint32_t)23U)
#define MPU_GICD_SPISR0_SPI_23_MASK                                                                         ((uint32_t)0x00800000U)

#define MPU_GICD_SPISR0_SPI_24_SHIFT                                                                        ((uint32_t)24U)
#define MPU_GICD_SPISR0_SPI_24_MASK                                                                         ((uint32_t)0x01000000U)

#define MPU_GICD_SPISR0_SPI_25_SHIFT                                                                        ((uint32_t)25U)
#define MPU_GICD_SPISR0_SPI_25_MASK                                                                         ((uint32_t)0x02000000U)

#define MPU_GICD_SPISR0_SPI_26_SHIFT                                                                        ((uint32_t)26U)
#define MPU_GICD_SPISR0_SPI_26_MASK                                                                         ((uint32_t)0x04000000U)

#define MPU_GICD_SPISR0_SPI_27_SHIFT                                                                        ((uint32_t)27U)
#define MPU_GICD_SPISR0_SPI_27_MASK                                                                         ((uint32_t)0x08000000U)

#define MPU_GICD_SPISR0_SPI_28_SHIFT                                                                        ((uint32_t)28U)
#define MPU_GICD_SPISR0_SPI_28_MASK                                                                         ((uint32_t)0x10000000U)

#define MPU_GICD_SPISR0_SPI_29_SHIFT                                                                        ((uint32_t)29U)
#define MPU_GICD_SPISR0_SPI_29_MASK                                                                         ((uint32_t)0x20000000U)

#define MPU_GICD_SPISR0_SPI_30_SHIFT                                                                        ((uint32_t)30U)
#define MPU_GICD_SPISR0_SPI_30_MASK                                                                         ((uint32_t)0x40000000U)

#define MPU_GICD_SPISR0_SPI_31_SHIFT                                                                        ((uint32_t)31U)
#define MPU_GICD_SPISR0_SPI_31_MASK                                                                         ((uint32_t)0x80000000U)

#define MPU_GICD_SPISR1_SPI_32_SHIFT                                                                        ((uint32_t)0U)
#define MPU_GICD_SPISR1_SPI_32_MASK                                                                         ((uint32_t)0x00000001U)

#define MPU_GICD_SPISR1_SPI_33_SHIFT                                                                        ((uint32_t)1U)
#define MPU_GICD_SPISR1_SPI_33_MASK                                                                         ((uint32_t)0x00000002U)

#define MPU_GICD_SPISR1_SPI_34_SHIFT                                                                        ((uint32_t)2U)
#define MPU_GICD_SPISR1_SPI_34_MASK                                                                         ((uint32_t)0x00000004U)

#define MPU_GICD_SPISR1_SPI_35_SHIFT                                                                        ((uint32_t)3U)
#define MPU_GICD_SPISR1_SPI_35_MASK                                                                         ((uint32_t)0x00000008U)

#define MPU_GICD_SPISR1_SPI_36_SHIFT                                                                        ((uint32_t)4U)
#define MPU_GICD_SPISR1_SPI_36_MASK                                                                         ((uint32_t)0x00000010U)

#define MPU_GICD_SPISR1_SPI_37_SHIFT                                                                        ((uint32_t)5U)
#define MPU_GICD_SPISR1_SPI_37_MASK                                                                         ((uint32_t)0x00000020U)

#define MPU_GICD_SPISR1_SPI_38_SHIFT                                                                        ((uint32_t)6U)
#define MPU_GICD_SPISR1_SPI_38_MASK                                                                         ((uint32_t)0x00000040U)

#define MPU_GICD_SPISR1_SPI_39_SHIFT                                                                        ((uint32_t)7U)
#define MPU_GICD_SPISR1_SPI_39_MASK                                                                         ((uint32_t)0x00000080U)

#define MPU_GICD_SPISR1_SPI_40_SHIFT                                                                        ((uint32_t)8U)
#define MPU_GICD_SPISR1_SPI_40_MASK                                                                         ((uint32_t)0x00000100U)

#define MPU_GICD_SPISR1_SPI_41_SHIFT                                                                        ((uint32_t)9U)
#define MPU_GICD_SPISR1_SPI_41_MASK                                                                         ((uint32_t)0x00000200U)

#define MPU_GICD_SPISR1_SPI_42_SHIFT                                                                        ((uint32_t)10U)
#define MPU_GICD_SPISR1_SPI_42_MASK                                                                         ((uint32_t)0x00000400U)

#define MPU_GICD_SPISR1_SPI_43_SHIFT                                                                        ((uint32_t)11U)
#define MPU_GICD_SPISR1_SPI_43_MASK                                                                         ((uint32_t)0x00000800U)

#define MPU_GICD_SPISR1_SPI_44_SHIFT                                                                        ((uint32_t)12U)
#define MPU_GICD_SPISR1_SPI_44_MASK                                                                         ((uint32_t)0x00001000U)

#define MPU_GICD_SPISR1_SPI_45_SHIFT                                                                        ((uint32_t)13U)
#define MPU_GICD_SPISR1_SPI_45_MASK                                                                         ((uint32_t)0x00002000U)

#define MPU_GICD_SPISR1_SPI_46_SHIFT                                                                        ((uint32_t)14U)
#define MPU_GICD_SPISR1_SPI_46_MASK                                                                         ((uint32_t)0x00004000U)

#define MPU_GICD_SPISR1_SPI_47_SHIFT                                                                        ((uint32_t)15U)
#define MPU_GICD_SPISR1_SPI_47_MASK                                                                         ((uint32_t)0x00008000U)

#define MPU_GICD_SPISR1_SPI_48_SHIFT                                                                        ((uint32_t)16U)
#define MPU_GICD_SPISR1_SPI_48_MASK                                                                         ((uint32_t)0x00010000U)

#define MPU_GICD_SPISR1_SPI_49_SHIFT                                                                        ((uint32_t)17U)
#define MPU_GICD_SPISR1_SPI_49_MASK                                                                         ((uint32_t)0x00020000U)

#define MPU_GICD_SPISR1_SPI_50_SHIFT                                                                        ((uint32_t)18U)
#define MPU_GICD_SPISR1_SPI_50_MASK                                                                         ((uint32_t)0x00040000U)

#define MPU_GICD_SPISR1_SPI_51_SHIFT                                                                        ((uint32_t)19U)
#define MPU_GICD_SPISR1_SPI_51_MASK                                                                         ((uint32_t)0x00080000U)

#define MPU_GICD_SPISR1_SPI_52_SHIFT                                                                        ((uint32_t)20U)
#define MPU_GICD_SPISR1_SPI_52_MASK                                                                         ((uint32_t)0x00100000U)

#define MPU_GICD_SPISR1_SPI_53_SHIFT                                                                        ((uint32_t)21U)
#define MPU_GICD_SPISR1_SPI_53_MASK                                                                         ((uint32_t)0x00200000U)

#define MPU_GICD_SPISR1_SPI_54_SHIFT                                                                        ((uint32_t)22U)
#define MPU_GICD_SPISR1_SPI_54_MASK                                                                         ((uint32_t)0x00400000U)

#define MPU_GICD_SPISR1_SPI_55_SHIFT                                                                        ((uint32_t)23U)
#define MPU_GICD_SPISR1_SPI_55_MASK                                                                         ((uint32_t)0x00800000U)

#define MPU_GICD_SPISR1_SPI_56_SHIFT                                                                        ((uint32_t)24U)
#define MPU_GICD_SPISR1_SPI_56_MASK                                                                         ((uint32_t)0x01000000U)

#define MPU_GICD_SPISR1_SPI_57_SHIFT                                                                        ((uint32_t)25U)
#define MPU_GICD_SPISR1_SPI_57_MASK                                                                         ((uint32_t)0x02000000U)

#define MPU_GICD_SPISR1_SPI_58_SHIFT                                                                        ((uint32_t)26U)
#define MPU_GICD_SPISR1_SPI_58_MASK                                                                         ((uint32_t)0x04000000U)

#define MPU_GICD_SPISR1_SPI_59_SHIFT                                                                        ((uint32_t)27U)
#define MPU_GICD_SPISR1_SPI_59_MASK                                                                         ((uint32_t)0x08000000U)

#define MPU_GICD_SPISR1_SPI_60_SHIFT                                                                        ((uint32_t)28U)
#define MPU_GICD_SPISR1_SPI_60_MASK                                                                         ((uint32_t)0x10000000U)

#define MPU_GICD_SPISR1_SPI_61_SHIFT                                                                        ((uint32_t)29U)
#define MPU_GICD_SPISR1_SPI_61_MASK                                                                         ((uint32_t)0x20000000U)

#define MPU_GICD_SPISR1_SPI_62_SHIFT                                                                        ((uint32_t)30U)
#define MPU_GICD_SPISR1_SPI_62_MASK                                                                         ((uint32_t)0x40000000U)

#define MPU_GICD_SPISR1_SPI_63_SHIFT                                                                        ((uint32_t)31U)
#define MPU_GICD_SPISR1_SPI_63_MASK                                                                         ((uint32_t)0x80000000U)

#define MPU_GICD_SPISR2_ID64_SHIFT                                                                          ((uint32_t)0U)
#define MPU_GICD_SPISR2_ID64_MASK                                                                           ((uint32_t)0x00000001U)

#define MPU_GICD_SPISR2_ID65_SHIFT                                                                          ((uint32_t)1U)
#define MPU_GICD_SPISR2_ID65_MASK                                                                           ((uint32_t)0x00000002U)

#define MPU_GICD_SPISR2_ID66_SHIFT                                                                          ((uint32_t)2U)
#define MPU_GICD_SPISR2_ID66_MASK                                                                           ((uint32_t)0x00000004U)

#define MPU_GICD_SPISR2_ID67_SHIFT                                                                          ((uint32_t)3U)
#define MPU_GICD_SPISR2_ID67_MASK                                                                           ((uint32_t)0x00000008U)

#define MPU_GICD_SPISR2_ID68_SHIFT                                                                          ((uint32_t)4U)
#define MPU_GICD_SPISR2_ID68_MASK                                                                           ((uint32_t)0x00000010U)

#define MPU_GICD_SPISR2_ID69_SHIFT                                                                          ((uint32_t)5U)
#define MPU_GICD_SPISR2_ID69_MASK                                                                           ((uint32_t)0x00000020U)

#define MPU_GICD_SPISR2_ID70_SHIFT                                                                          ((uint32_t)6U)
#define MPU_GICD_SPISR2_ID70_MASK                                                                           ((uint32_t)0x00000040U)

#define MPU_GICD_SPISR2_ID71_SHIFT                                                                          ((uint32_t)7U)
#define MPU_GICD_SPISR2_ID71_MASK                                                                           ((uint32_t)0x00000080U)

#define MPU_GICD_SPISR2_ID72_SHIFT                                                                          ((uint32_t)8U)
#define MPU_GICD_SPISR2_ID72_MASK                                                                           ((uint32_t)0x00000100U)

#define MPU_GICD_SPISR2_ID73_SHIFT                                                                          ((uint32_t)9U)
#define MPU_GICD_SPISR2_ID73_MASK                                                                           ((uint32_t)0x00000200U)

#define MPU_GICD_SPISR2_ID74_SHIFT                                                                          ((uint32_t)10U)
#define MPU_GICD_SPISR2_ID74_MASK                                                                           ((uint32_t)0x00000400U)

#define MPU_GICD_SPISR2_ID75_SHIFT                                                                          ((uint32_t)11U)
#define MPU_GICD_SPISR2_ID75_MASK                                                                           ((uint32_t)0x00000800U)

#define MPU_GICD_SPISR2_ID76_SHIFT                                                                          ((uint32_t)12U)
#define MPU_GICD_SPISR2_ID76_MASK                                                                           ((uint32_t)0x00001000U)

#define MPU_GICD_SPISR2_ID77_SHIFT                                                                          ((uint32_t)13U)
#define MPU_GICD_SPISR2_ID77_MASK                                                                           ((uint32_t)0x00002000U)

#define MPU_GICD_SPISR2_ID78_SHIFT                                                                          ((uint32_t)14U)
#define MPU_GICD_SPISR2_ID78_MASK                                                                           ((uint32_t)0x00004000U)

#define MPU_GICD_SPISR2_ID79_SHIFT                                                                          ((uint32_t)15U)
#define MPU_GICD_SPISR2_ID79_MASK                                                                           ((uint32_t)0x00008000U)

#define MPU_GICD_SPISR2_ID80_SHIFT                                                                          ((uint32_t)16U)
#define MPU_GICD_SPISR2_ID80_MASK                                                                           ((uint32_t)0x00010000U)

#define MPU_GICD_SPISR2_ID81_SHIFT                                                                          ((uint32_t)17U)
#define MPU_GICD_SPISR2_ID81_MASK                                                                           ((uint32_t)0x00020000U)

#define MPU_GICD_SPISR2_ID82_SHIFT                                                                          ((uint32_t)18U)
#define MPU_GICD_SPISR2_ID82_MASK                                                                           ((uint32_t)0x00040000U)

#define MPU_GICD_SPISR2_ID83_SHIFT                                                                          ((uint32_t)19U)
#define MPU_GICD_SPISR2_ID83_MASK                                                                           ((uint32_t)0x00080000U)

#define MPU_GICD_SPISR2_ID84_SHIFT                                                                          ((uint32_t)20U)
#define MPU_GICD_SPISR2_ID84_MASK                                                                           ((uint32_t)0x00100000U)

#define MPU_GICD_SPISR2_ID85_SHIFT                                                                          ((uint32_t)21U)
#define MPU_GICD_SPISR2_ID85_MASK                                                                           ((uint32_t)0x00200000U)

#define MPU_GICD_SPISR2_ID86_SHIFT                                                                          ((uint32_t)22U)
#define MPU_GICD_SPISR2_ID86_MASK                                                                           ((uint32_t)0x00400000U)

#define MPU_GICD_SPISR2_ID87_SHIFT                                                                          ((uint32_t)23U)
#define MPU_GICD_SPISR2_ID87_MASK                                                                           ((uint32_t)0x00800000U)

#define MPU_GICD_SPISR2_ID88_SHIFT                                                                          ((uint32_t)24U)
#define MPU_GICD_SPISR2_ID88_MASK                                                                           ((uint32_t)0x01000000U)

#define MPU_GICD_SPISR2_ID89_SHIFT                                                                          ((uint32_t)25U)
#define MPU_GICD_SPISR2_ID89_MASK                                                                           ((uint32_t)0x02000000U)

#define MPU_GICD_SPISR2_ID90_SHIFT                                                                          ((uint32_t)26U)
#define MPU_GICD_SPISR2_ID90_MASK                                                                           ((uint32_t)0x04000000U)

#define MPU_GICD_SPISR2_ID91_SHIFT                                                                          ((uint32_t)27U)
#define MPU_GICD_SPISR2_ID91_MASK                                                                           ((uint32_t)0x08000000U)

#define MPU_GICD_SPISR2_ID92_SHIFT                                                                          ((uint32_t)28U)
#define MPU_GICD_SPISR2_ID92_MASK                                                                           ((uint32_t)0x10000000U)

#define MPU_GICD_SPISR2_ID93_SHIFT                                                                          ((uint32_t)29U)
#define MPU_GICD_SPISR2_ID93_MASK                                                                           ((uint32_t)0x20000000U)

#define MPU_GICD_SPISR2_ID94_SHIFT                                                                          ((uint32_t)30U)
#define MPU_GICD_SPISR2_ID94_MASK                                                                           ((uint32_t)0x40000000U)

#define MPU_GICD_SPISR2_ID95_SHIFT                                                                          ((uint32_t)31U)
#define MPU_GICD_SPISR2_ID95_MASK                                                                           ((uint32_t)0x80000000U)

#define MPU_GICD_SPISR3_ID96_SHIFT                                                                          ((uint32_t)0U)
#define MPU_GICD_SPISR3_ID96_MASK                                                                           ((uint32_t)0x00000001U)

#define MPU_GICD_SPISR3_ID97_SHIFT                                                                          ((uint32_t)1U)
#define MPU_GICD_SPISR3_ID97_MASK                                                                           ((uint32_t)0x00000002U)

#define MPU_GICD_SPISR3_ID98_SHIFT                                                                          ((uint32_t)2U)
#define MPU_GICD_SPISR3_ID98_MASK                                                                           ((uint32_t)0x00000004U)

#define MPU_GICD_SPISR3_ID99_SHIFT                                                                          ((uint32_t)3U)
#define MPU_GICD_SPISR3_ID99_MASK                                                                           ((uint32_t)0x00000008U)

#define MPU_GICD_SPISR3_ID100_SHIFT                                                                         ((uint32_t)4U)
#define MPU_GICD_SPISR3_ID100_MASK                                                                          ((uint32_t)0x00000010U)

#define MPU_GICD_SPISR3_ID101_SHIFT                                                                         ((uint32_t)5U)
#define MPU_GICD_SPISR3_ID101_MASK                                                                          ((uint32_t)0x00000020U)

#define MPU_GICD_SPISR3_ID102_SHIFT                                                                         ((uint32_t)6U)
#define MPU_GICD_SPISR3_ID102_MASK                                                                          ((uint32_t)0x00000040U)

#define MPU_GICD_SPISR3_ID103_SHIFT                                                                         ((uint32_t)7U)
#define MPU_GICD_SPISR3_ID103_MASK                                                                          ((uint32_t)0x00000080U)

#define MPU_GICD_SPISR3_ID104_SHIFT                                                                         ((uint32_t)8U)
#define MPU_GICD_SPISR3_ID104_MASK                                                                          ((uint32_t)0x00000100U)

#define MPU_GICD_SPISR3_ID105_SHIFT                                                                         ((uint32_t)9U)
#define MPU_GICD_SPISR3_ID105_MASK                                                                          ((uint32_t)0x00000200U)

#define MPU_GICD_SPISR3_ID106_SHIFT                                                                         ((uint32_t)10U)
#define MPU_GICD_SPISR3_ID106_MASK                                                                          ((uint32_t)0x00000400U)

#define MPU_GICD_SPISR3_ID107_SHIFT                                                                         ((uint32_t)11U)
#define MPU_GICD_SPISR3_ID107_MASK                                                                          ((uint32_t)0x00000800U)

#define MPU_GICD_SPISR3_ID108_SHIFT                                                                         ((uint32_t)12U)
#define MPU_GICD_SPISR3_ID108_MASK                                                                          ((uint32_t)0x00001000U)

#define MPU_GICD_SPISR3_ID109_SHIFT                                                                         ((uint32_t)13U)
#define MPU_GICD_SPISR3_ID109_MASK                                                                          ((uint32_t)0x00002000U)

#define MPU_GICD_SPISR3_ID110_SHIFT                                                                         ((uint32_t)14U)
#define MPU_GICD_SPISR3_ID110_MASK                                                                          ((uint32_t)0x00004000U)

#define MPU_GICD_SPISR3_ID111_SHIFT                                                                         ((uint32_t)15U)
#define MPU_GICD_SPISR3_ID111_MASK                                                                          ((uint32_t)0x00008000U)

#define MPU_GICD_SPISR3_ID112_SHIFT                                                                         ((uint32_t)16U)
#define MPU_GICD_SPISR3_ID112_MASK                                                                          ((uint32_t)0x00010000U)

#define MPU_GICD_SPISR3_ID113_SHIFT                                                                         ((uint32_t)17U)
#define MPU_GICD_SPISR3_ID113_MASK                                                                          ((uint32_t)0x00020000U)

#define MPU_GICD_SPISR3_ID114_SHIFT                                                                         ((uint32_t)18U)
#define MPU_GICD_SPISR3_ID114_MASK                                                                          ((uint32_t)0x00040000U)

#define MPU_GICD_SPISR3_ID115_SHIFT                                                                         ((uint32_t)19U)
#define MPU_GICD_SPISR3_ID115_MASK                                                                          ((uint32_t)0x00080000U)

#define MPU_GICD_SPISR3_ID116_SHIFT                                                                         ((uint32_t)20U)
#define MPU_GICD_SPISR3_ID116_MASK                                                                          ((uint32_t)0x00100000U)

#define MPU_GICD_SPISR3_ID117_SHIFT                                                                         ((uint32_t)21U)
#define MPU_GICD_SPISR3_ID117_MASK                                                                          ((uint32_t)0x00200000U)

#define MPU_GICD_SPISR3_ID118_SHIFT                                                                         ((uint32_t)22U)
#define MPU_GICD_SPISR3_ID118_MASK                                                                          ((uint32_t)0x00400000U)

#define MPU_GICD_SPISR3_ID119_SHIFT                                                                         ((uint32_t)23U)
#define MPU_GICD_SPISR3_ID119_MASK                                                                          ((uint32_t)0x00800000U)

#define MPU_GICD_SPISR3_ID120_SHIFT                                                                         ((uint32_t)24U)
#define MPU_GICD_SPISR3_ID120_MASK                                                                          ((uint32_t)0x01000000U)

#define MPU_GICD_SPISR3_ID121_SHIFT                                                                         ((uint32_t)25U)
#define MPU_GICD_SPISR3_ID121_MASK                                                                          ((uint32_t)0x02000000U)

#define MPU_GICD_SPISR3_ID122_SHIFT                                                                         ((uint32_t)26U)
#define MPU_GICD_SPISR3_ID122_MASK                                                                          ((uint32_t)0x04000000U)

#define MPU_GICD_SPISR3_ID123_SHIFT                                                                         ((uint32_t)27U)
#define MPU_GICD_SPISR3_ID123_MASK                                                                          ((uint32_t)0x08000000U)

#define MPU_GICD_SPISR3_ID124_SHIFT                                                                         ((uint32_t)28U)
#define MPU_GICD_SPISR3_ID124_MASK                                                                          ((uint32_t)0x10000000U)

#define MPU_GICD_SPISR3_ID125_SHIFT                                                                         ((uint32_t)29U)
#define MPU_GICD_SPISR3_ID125_MASK                                                                          ((uint32_t)0x20000000U)

#define MPU_GICD_SPISR3_ID126_SHIFT                                                                         ((uint32_t)30U)
#define MPU_GICD_SPISR3_ID126_MASK                                                                          ((uint32_t)0x40000000U)

#define MPU_GICD_SPISR3_ID127_SHIFT                                                                         ((uint32_t)31U)
#define MPU_GICD_SPISR3_ID127_MASK                                                                          ((uint32_t)0x80000000U)

#define MPU_GICD_SPISR4_ID128_SHIFT                                                                         ((uint32_t)0U)
#define MPU_GICD_SPISR4_ID128_MASK                                                                          ((uint32_t)0x00000001U)

#define MPU_GICD_SPISR4_ID129_SHIFT                                                                         ((uint32_t)1U)
#define MPU_GICD_SPISR4_ID129_MASK                                                                          ((uint32_t)0x00000002U)

#define MPU_GICD_SPISR4_ID130_SHIFT                                                                         ((uint32_t)2U)
#define MPU_GICD_SPISR4_ID130_MASK                                                                          ((uint32_t)0x00000004U)

#define MPU_GICD_SPISR4_ID131_SHIFT                                                                         ((uint32_t)3U)
#define MPU_GICD_SPISR4_ID131_MASK                                                                          ((uint32_t)0x00000008U)

#define MPU_GICD_SPISR4_ID132_SHIFT                                                                         ((uint32_t)4U)
#define MPU_GICD_SPISR4_ID132_MASK                                                                          ((uint32_t)0x00000010U)

#define MPU_GICD_SPISR4_ID133_SHIFT                                                                         ((uint32_t)5U)
#define MPU_GICD_SPISR4_ID133_MASK                                                                          ((uint32_t)0x00000020U)

#define MPU_GICD_SPISR4_ID134_SHIFT                                                                         ((uint32_t)6U)
#define MPU_GICD_SPISR4_ID134_MASK                                                                          ((uint32_t)0x00000040U)

#define MPU_GICD_SPISR4_ID135_SHIFT                                                                         ((uint32_t)7U)
#define MPU_GICD_SPISR4_ID135_MASK                                                                          ((uint32_t)0x00000080U)

#define MPU_GICD_SPISR4_ID136_SHIFT                                                                         ((uint32_t)8U)
#define MPU_GICD_SPISR4_ID136_MASK                                                                          ((uint32_t)0x00000100U)

#define MPU_GICD_SPISR4_ID137_SHIFT                                                                         ((uint32_t)9U)
#define MPU_GICD_SPISR4_ID137_MASK                                                                          ((uint32_t)0x00000200U)

#define MPU_GICD_SPISR4_ID138_SHIFT                                                                         ((uint32_t)10U)
#define MPU_GICD_SPISR4_ID138_MASK                                                                          ((uint32_t)0x00000400U)

#define MPU_GICD_SPISR4_ID139_SHIFT                                                                         ((uint32_t)11U)
#define MPU_GICD_SPISR4_ID139_MASK                                                                          ((uint32_t)0x00000800U)

#define MPU_GICD_SPISR4_ID140_SHIFT                                                                         ((uint32_t)12U)
#define MPU_GICD_SPISR4_ID140_MASK                                                                          ((uint32_t)0x00001000U)

#define MPU_GICD_SPISR4_ID141_SHIFT                                                                         ((uint32_t)13U)
#define MPU_GICD_SPISR4_ID141_MASK                                                                          ((uint32_t)0x00002000U)

#define MPU_GICD_SPISR4_ID142_SHIFT                                                                         ((uint32_t)14U)
#define MPU_GICD_SPISR4_ID142_MASK                                                                          ((uint32_t)0x00004000U)

#define MPU_GICD_SPISR4_ID143_SHIFT                                                                         ((uint32_t)15U)
#define MPU_GICD_SPISR4_ID143_MASK                                                                          ((uint32_t)0x00008000U)

#define MPU_GICD_SPISR4_ID144_SHIFT                                                                         ((uint32_t)16U)
#define MPU_GICD_SPISR4_ID144_MASK                                                                          ((uint32_t)0x00010000U)

#define MPU_GICD_SPISR4_ID145_SHIFT                                                                         ((uint32_t)17U)
#define MPU_GICD_SPISR4_ID145_MASK                                                                          ((uint32_t)0x00020000U)

#define MPU_GICD_SPISR4_ID146_SHIFT                                                                         ((uint32_t)18U)
#define MPU_GICD_SPISR4_ID146_MASK                                                                          ((uint32_t)0x00040000U)

#define MPU_GICD_SPISR4_ID147_SHIFT                                                                         ((uint32_t)19U)
#define MPU_GICD_SPISR4_ID147_MASK                                                                          ((uint32_t)0x00080000U)

#define MPU_GICD_SPISR4_ID148_SHIFT                                                                         ((uint32_t)20U)
#define MPU_GICD_SPISR4_ID148_MASK                                                                          ((uint32_t)0x00100000U)

#define MPU_GICD_SPISR4_ID149_SHIFT                                                                         ((uint32_t)21U)
#define MPU_GICD_SPISR4_ID149_MASK                                                                          ((uint32_t)0x00200000U)

#define MPU_GICD_SPISR4_ID150_SHIFT                                                                         ((uint32_t)22U)
#define MPU_GICD_SPISR4_ID150_MASK                                                                          ((uint32_t)0x00400000U)

#define MPU_GICD_SPISR4_ID151_SHIFT                                                                         ((uint32_t)23U)
#define MPU_GICD_SPISR4_ID151_MASK                                                                          ((uint32_t)0x00800000U)

#define MPU_GICD_SPISR4_ID152_SHIFT                                                                         ((uint32_t)24U)
#define MPU_GICD_SPISR4_ID152_MASK                                                                          ((uint32_t)0x01000000U)

#define MPU_GICD_SPISR4_ID153_SHIFT                                                                         ((uint32_t)25U)
#define MPU_GICD_SPISR4_ID153_MASK                                                                          ((uint32_t)0x02000000U)

#define MPU_GICD_SPISR4_ID154_SHIFT                                                                         ((uint32_t)26U)
#define MPU_GICD_SPISR4_ID154_MASK                                                                          ((uint32_t)0x04000000U)

#define MPU_GICD_SPISR4_ID155_SHIFT                                                                         ((uint32_t)27U)
#define MPU_GICD_SPISR4_ID155_MASK                                                                          ((uint32_t)0x08000000U)

#define MPU_GICD_SPISR4_ID156_SHIFT                                                                         ((uint32_t)28U)
#define MPU_GICD_SPISR4_ID156_MASK                                                                          ((uint32_t)0x10000000U)

#define MPU_GICD_SPISR4_ID157_SHIFT                                                                         ((uint32_t)29U)
#define MPU_GICD_SPISR4_ID157_MASK                                                                          ((uint32_t)0x20000000U)

#define MPU_GICD_SPISR4_ID158_SHIFT                                                                         ((uint32_t)30U)
#define MPU_GICD_SPISR4_ID158_MASK                                                                          ((uint32_t)0x40000000U)

#define MPU_GICD_SPISR4_ID159_SHIFT                                                                         ((uint32_t)31U)
#define MPU_GICD_SPISR4_ID159_MASK                                                                          ((uint32_t)0x80000000U)

#define MPU_GICD_SGIR_SATT_SHIFT                                                                            ((uint32_t)15U)
#define MPU_GICD_SGIR_SATT_MASK                                                                             ((uint32_t)0x00008000U)

#define MPU_GICD_SGIR_SGIINTID_SHIFT                                                                        ((uint32_t)0U)
#define MPU_GICD_SGIR_SGIINTID_MASK                                                                         ((uint32_t)0x0000000fU)

#define MPU_GICD_SGIR_CPUTARGETLIST_SHIFT                                                                   ((uint32_t)16U)
#define MPU_GICD_SGIR_CPUTARGETLIST_MASK                                                                    ((uint32_t)0x00ff0000U)

#define MPU_GICD_SGIR_TARGETLISTFILTER_SHIFT                                                                ((uint32_t)24U)
#define MPU_GICD_SGIR_TARGETLISTFILTER_MASK                                                                 ((uint32_t)0x03000000U)

#define MPU_GICD_SGIR_RESERVED_SHIFT                                                                        ((uint32_t)4U)
#define MPU_GICD_SGIR_RESERVED_MASK                                                                         ((uint32_t)0x00007ff0U)

#define MPU_GICD_SGIR_RESERVED2_SHIFT                                                                       ((uint32_t)26U)
#define MPU_GICD_SGIR_RESERVED2_MASK                                                                        ((uint32_t)0xfc000000U)

#define MPU_GICD_CPENDSGIR0_SGI0_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_CPENDSGIR0_SGI0_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_CPENDSGIR0_SGI1_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_CPENDSGIR0_SGI1_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_CPENDSGIR0_SGI2_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_CPENDSGIR0_SGI2_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_CPENDSGIR0_SGI3_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_CPENDSGIR0_SGI3_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_CPENDSGIR1_SGI4_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_CPENDSGIR1_SGI4_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_CPENDSGIR1_SGI5_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_CPENDSGIR1_SGI5_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_CPENDSGIR1_SGI6_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_CPENDSGIR1_SGI6_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_CPENDSGIR1_SGI7_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_CPENDSGIR1_SGI7_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_CPENDSGIR2_SGI8_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_CPENDSGIR2_SGI8_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_CPENDSGIR2_SGI9_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_CPENDSGIR2_SGI9_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_CPENDSGIR2_SGI10_SHIFT                                                                     ((uint32_t)16U)
#define MPU_GICD_CPENDSGIR2_SGI10_MASK                                                                      ((uint32_t)0x00ff0000U)

#define MPU_GICD_CPENDSGIR2_SGI11_SHIFT                                                                     ((uint32_t)24U)
#define MPU_GICD_CPENDSGIR2_SGI11_MASK                                                                      ((uint32_t)0xff000000U)

#define MPU_GICD_CPENDSGIR3_SGI12_SHIFT                                                                     ((uint32_t)0U)
#define MPU_GICD_CPENDSGIR3_SGI12_MASK                                                                      ((uint32_t)0x000000ffU)

#define MPU_GICD_CPENDSGIR3_SGI13_SHIFT                                                                     ((uint32_t)8U)
#define MPU_GICD_CPENDSGIR3_SGI13_MASK                                                                      ((uint32_t)0x0000ff00U)

#define MPU_GICD_CPENDSGIR3_SGI14_SHIFT                                                                     ((uint32_t)16U)
#define MPU_GICD_CPENDSGIR3_SGI14_MASK                                                                      ((uint32_t)0x00ff0000U)

#define MPU_GICD_CPENDSGIR3_SGI15_SHIFT                                                                     ((uint32_t)24U)
#define MPU_GICD_CPENDSGIR3_SGI15_MASK                                                                      ((uint32_t)0xff000000U)

#define MPU_GICD_SPENDSGIR0_SGI0_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_SPENDSGIR0_SGI0_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_SPENDSGIR0_SGI1_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_SPENDSGIR0_SGI1_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_SPENDSGIR0_SGI2_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_SPENDSGIR0_SGI2_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_SPENDSGIR0_SGI3_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_SPENDSGIR0_SGI3_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_SPENDSGIR1_SGI4_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_SPENDSGIR1_SGI4_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_SPENDSGIR1_SGI5_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_SPENDSGIR1_SGI5_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_SPENDSGIR1_SGI6_SHIFT                                                                      ((uint32_t)16U)
#define MPU_GICD_SPENDSGIR1_SGI6_MASK                                                                       ((uint32_t)0x00ff0000U)

#define MPU_GICD_SPENDSGIR1_SGI7_SHIFT                                                                      ((uint32_t)24U)
#define MPU_GICD_SPENDSGIR1_SGI7_MASK                                                                       ((uint32_t)0xff000000U)

#define MPU_GICD_SPENDSGIR2_SGI8_SHIFT                                                                      ((uint32_t)0U)
#define MPU_GICD_SPENDSGIR2_SGI8_MASK                                                                       ((uint32_t)0x000000ffU)

#define MPU_GICD_SPENDSGIR2_SGI9_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_SPENDSGIR2_SGI9_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MPU_GICD_SPENDSGIR2_SGI10_SHIFT                                                                     ((uint32_t)16U)
#define MPU_GICD_SPENDSGIR2_SGI10_MASK                                                                      ((uint32_t)0x00ff0000U)

#define MPU_GICD_SPENDSGIR2_SGI11_SHIFT                                                                     ((uint32_t)24U)
#define MPU_GICD_SPENDSGIR2_SGI11_MASK                                                                      ((uint32_t)0xff000000U)

#define MPU_GICD_SPENDSGIR3_SGI12_SHIFT                                                                     ((uint32_t)0U)
#define MPU_GICD_SPENDSGIR3_SGI12_MASK                                                                      ((uint32_t)0x000000ffU)

#define MPU_GICD_SPENDSGIR3_SGI13_SHIFT                                                                     ((uint32_t)8U)
#define MPU_GICD_SPENDSGIR3_SGI13_MASK                                                                      ((uint32_t)0x0000ff00U)

#define MPU_GICD_SPENDSGIR3_SGI14_SHIFT                                                                     ((uint32_t)16U)
#define MPU_GICD_SPENDSGIR3_SGI14_MASK                                                                      ((uint32_t)0x00ff0000U)

#define MPU_GICD_SPENDSGIR3_SGI15_SHIFT                                                                     ((uint32_t)24U)
#define MPU_GICD_SPENDSGIR3_SGI15_MASK                                                                      ((uint32_t)0xff000000U)

#define MPU_GICD_PIDR4_CONTINUATION_CODE_SHIFT                                                              ((uint32_t)0U)
#define MPU_GICD_PIDR4_CONTINUATION_CODE_MASK                                                               ((uint32_t)0x0000000fU)

#define MPU_GICD_PIDR4_RESERVED_SHIFT                                                                       ((uint32_t)4U)
#define MPU_GICD_PIDR4_RESERVED_MASK                                                                        ((uint32_t)0xfffffff0U)

#define MPU_GICD_PIDR5_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_PIDR5_RESERVED_MASK                                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_PIDR6_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_PIDR6_RESERVED_MASK                                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_PIDR7_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_PIDR7_RESERVED_MASK                                                                        ((uint32_t)0xffffffffU)

#define MPU_GICD_PIDR0_DEVID_FIELD_SHIFT                                                                    ((uint32_t)0U)
#define MPU_GICD_PIDR0_DEVID_FIELD_MASK                                                                     ((uint32_t)0x000000ffU)

#define MPU_GICD_PIDR0_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_PIDR0_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_PIDR1_DEVID_SHIFT                                                                          ((uint32_t)0U)
#define MPU_GICD_PIDR1_DEVID_MASK                                                                           ((uint32_t)0x0000000fU)

#define MPU_GICD_PIDR1_ARCHID_LOWER_FIELD_SHIFT                                                             ((uint32_t)4U)
#define MPU_GICD_PIDR1_ARCHID_LOWER_FIELD_MASK                                                              ((uint32_t)0x000000f0U)

#define MPU_GICD_PIDR1_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_PIDR1_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_PIDR2_ARCHID_HIGHER_FIELD_SHIFT                                                            ((uint32_t)0U)
#define MPU_GICD_PIDR2_ARCHID_HIGHER_FIELD_MASK                                                             ((uint32_t)0x00000007U)

#define MPU_GICD_PIDR2_USESJEP_CODE_FIELD_SHIFT                                                             ((uint32_t)3U)
#define MPU_GICD_PIDR2_USESJEP_CODE_FIELD_MASK                                                              ((uint32_t)0x00000008U)

#define MPU_GICD_PIDR2_ARCHREV_FIELD_SHIFT                                                                  ((uint32_t)4U)
#define MPU_GICD_PIDR2_ARCHREV_FIELD_MASK                                                                   ((uint32_t)0x000000f0U)

#define MPU_GICD_PIDR2_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_PIDR2_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_PIDR3_REVISION_FIELD_SHIFT                                                                 ((uint32_t)4U)
#define MPU_GICD_PIDR3_REVISION_FIELD_MASK                                                                  ((uint32_t)0x000000f0U)

#define MPU_GICD_PIDR3_RESERVED_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_PIDR3_RESERVED_MASK                                                                        ((uint32_t)0x0000000fU)

#define MPU_GICD_PIDR3_RESERVED1_SHIFT                                                                      ((uint32_t)8U)
#define MPU_GICD_PIDR3_RESERVED1_MASK                                                                       ((uint32_t)0xffffff00U)

#define MPU_GICD_CIDR0_PREAMBLE_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_CIDR0_PREAMBLE_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_CIDR0_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_CIDR0_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_CIDR1_PREAMBLE_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_CIDR1_PREAMBLE_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_CIDR1_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_CIDR1_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_CIDR2_PREAMBLE_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_CIDR2_PREAMBLE_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_CIDR2_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_CIDR2_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#define MPU_GICD_CIDR3_PREAMBLE_SHIFT                                                                       ((uint32_t)0U)
#define MPU_GICD_CIDR3_PREAMBLE_MASK                                                                        ((uint32_t)0x000000ffU)

#define MPU_GICD_CIDR3_RESERVED_SHIFT                                                                       ((uint32_t)8U)
#define MPU_GICD_CIDR3_RESERVED_MASK                                                                        ((uint32_t)0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_INTC_DIST_H_ */
