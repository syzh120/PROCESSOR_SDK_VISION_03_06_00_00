/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2016
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
*
*  \file    hw_mpu_intc_phys.h
*
*  \brief   register-level header file for MPU
*
**/

#ifndef HW_MPU_INTC_PHYS_H_
#define HW_MPU_INTC_PHYS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MPU_GICC_ICR                                                                                        ((uint32_t)(0x0U))
#define MPU_GICC_PMR                                                                                        ((uint32_t)(0x4U))
#define MPU_GICC_BPR                                                                                        ((uint32_t)(0x8U))
#define MPU_GICC_IAR                                                                                        ((uint32_t)(0xcU))
#define MPU_GICC_EOIR                                                                                       ((uint32_t)(0x10U))
#define MPU_GICC_RPR                                                                                        ((uint32_t)(0x14U))
#define MPU_GICC_HPIR                                                                                       ((uint32_t)(0x18U))
#define MPU_GICC_ABPR                                                                                       ((uint32_t)(0x1cU))
#define MPU_GICC_AIAR                                                                                       ((uint32_t)(0x20U))
#define MPU_GICC_AEOIR                                                                                      ((uint32_t)(0x24U))
#define MPU_GICC_AHPPIR                                                                                     ((uint32_t)(0x28U))
#define MPU_GICC_APR0                                                                                       ((uint32_t)(0xd0U))
#define MPU_GICC_NSAPR0                                                                                     ((uint32_t)(0xe0U))
#define MPU_GICC_IIDR                                                                                       ((uint32_t)(0xfcU))
#define MPU_GICC_DIR                                                                                        ((uint32_t)(0x1000U))

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MPU_GICC_ICR_RESERVED_SHIFT                                                                         ((uint32_t)(11U))
#define MPU_GICC_ICR_RESERVED_MASK                                                                          ((uint32_t)(0xfffff800U))

#define MPU_GICC_ICR_ENABLES_SHIFT                                                                          ((uint32_t)(0U))
#define MPU_GICC_ICR_ENABLES_MASK                                                                           ((uint32_t)(0x00000001U))

#define MPU_GICC_ICR_ENABLENS_SHIFT                                                                         ((uint32_t)(1U))
#define MPU_GICC_ICR_ENABLENS_MASK                                                                          ((uint32_t)(0x00000002U))

#define MPU_GICC_ICR_ACKCTL_SHIFT                                                                           ((uint32_t)(2U))
#define MPU_GICC_ICR_ACKCTL_MASK                                                                            ((uint32_t)(0x00000004U))

#define MPU_GICC_ICR_FIQEN_SHIFT                                                                            ((uint32_t)(3U))
#define MPU_GICC_ICR_FIQEN_MASK                                                                             ((uint32_t)(0x00000008U))

#define MPU_GICC_ICR_SBPR_SHIFT                                                                             ((uint32_t)(4U))
#define MPU_GICC_ICR_SBPR_MASK                                                                              ((uint32_t)(0x00000010U))

#define MPU_GICC_ICR_FIQBYPDISABLE_SHIFT                                                                    ((uint32_t)(5U))
#define MPU_GICC_ICR_FIQBYPDISABLE_MASK                                                                     ((uint32_t)(0x00000020U))

#define MPU_GICC_ICR_IRQBYPDISABLE_SHIFT                                                                    ((uint32_t)(6U))
#define MPU_GICC_ICR_IRQBYPDISABLE_MASK                                                                     ((uint32_t)(0x00000040U))

#define MPU_GICC_ICR_FIQBYPDISNS_SHIFT                                                                      ((uint32_t)(7U))
#define MPU_GICC_ICR_FIQBYPDISNS_MASK                                                                       ((uint32_t)(0x00000080U))

#define MPU_GICC_ICR_IRQBYPDISNS_SHIFT                                                                      ((uint32_t)(8U))
#define MPU_GICC_ICR_IRQBYPDISNS_MASK                                                                       ((uint32_t)(0x00000100U))

#define MPU_GICC_ICR_EOIMODE_SHIFT                                                                          ((uint32_t)(9U))
#define MPU_GICC_ICR_EOIMODE_MASK                                                                           ((uint32_t)(0x00000200U))

#define MPU_GICC_ICR_EOIMODENS_SHIFT                                                                        ((uint32_t)(10U))
#define MPU_GICC_ICR_EOIMODENS_MASK                                                                         ((uint32_t)(0x00000400U))

#define MPU_GICC_PMR_PRIORITY_SHIFT                                                                         ((uint32_t)(3U))
#define MPU_GICC_PMR_PRIORITY_MASK                                                                          ((uint32_t)(0x000000f8U))

#define MPU_GICC_PMR_RESERVED_SHIFT                                                                         ((uint32_t)(8U))
#define MPU_GICC_PMR_RESERVED_MASK                                                                          ((uint32_t)(0xffffff00U))

#define MPU_GICC_PMR_RESERVED1_SHIFT                                                                        ((uint32_t)(0U))
#define MPU_GICC_PMR_RESERVED1_MASK                                                                         ((uint32_t)(0x00000007U))

#define MPU_GICC_BPR_BINARYPOINT_SHIFT                                                                      ((uint32_t)(0U))
#define MPU_GICC_BPR_BINARYPOINT_MASK                                                                       ((uint32_t)(0x00000007U))

#define MPU_GICC_BPR_RESERVED_SHIFT                                                                         ((uint32_t)(3U))
#define MPU_GICC_BPR_RESERVED_MASK                                                                          ((uint32_t)(0xfffffff8U))

#define MPU_GICC_IAR_ACKINTID_SHIFT                                                                         ((uint32_t)(0U))
#define MPU_GICC_IAR_ACKINTID_MASK                                                                          ((uint32_t)(0x000003ffU))

#define MPU_GICC_IAR_RESERVED_SHIFT                                                                         ((uint32_t)(13U))
#define MPU_GICC_IAR_RESERVED_MASK                                                                          ((uint32_t)(0xffffe000U))

#define MPU_GICC_IAR_CPUID_SHIFT                                                                            ((uint32_t)(10U))
#define MPU_GICC_IAR_CPUID_MASK                                                                             ((uint32_t)(0x00001c00U))

#define MPU_GICC_EOIR_EOIINTID_SHIFT                                                                        ((uint32_t)(0U))
#define MPU_GICC_EOIR_EOIINTID_MASK                                                                         ((uint32_t)(0x000003ffU))

#define MPU_GICC_EOIR_CPUID_SHIFT                                                                           ((uint32_t)(10U))
#define MPU_GICC_EOIR_CPUID_MASK                                                                            ((uint32_t)(0x00001c00U))

#define MPU_GICC_EOIR_RESERVED_SHIFT                                                                        ((uint32_t)(13U))
#define MPU_GICC_EOIR_RESERVED_MASK                                                                         ((uint32_t)(0xffffe000U))

#define MPU_GICC_RPR_RESERVED_SHIFT                                                                         ((uint32_t)(8U))
#define MPU_GICC_RPR_RESERVED_MASK                                                                          ((uint32_t)(0xffffff00U))

#define MPU_GICC_RPR_PRIORITY_SHIFT                                                                         ((uint32_t)(0U))
#define MPU_GICC_RPR_PRIORITY_MASK                                                                          ((uint32_t)(0x000000ffU))

#define MPU_GICC_HPIR_RESERVED_SHIFT                                                                        ((uint32_t)(13U))
#define MPU_GICC_HPIR_RESERVED_MASK                                                                         ((uint32_t)(0xffffe000U))

#define MPU_GICC_HPIR_CPUID_SHIFT                                                                           ((uint32_t)(10U))
#define MPU_GICC_HPIR_CPUID_MASK                                                                            ((uint32_t)(0x00001c00U))

#define MPU_GICC_HPIR_PENDINTID_SHIFT                                                                       ((uint32_t)(0U))
#define MPU_GICC_HPIR_PENDINTID_MASK                                                                        ((uint32_t)(0x000003ffU))

#define MPU_GICC_ABPR_RESERVED_SHIFT                                                                        ((uint32_t)(3U))
#define MPU_GICC_ABPR_RESERVED_MASK                                                                         ((uint32_t)(0xfffffff8U))

#define MPU_GICC_ABPR_BINARYPOINT_SHIFT                                                                     ((uint32_t)(0U))
#define MPU_GICC_ABPR_BINARYPOINT_MASK                                                                      ((uint32_t)(0x00000007U))

#define MPU_GICC_AIAR_ACKINTID_SHIFT                                                                        ((uint32_t)(0U))
#define MPU_GICC_AIAR_ACKINTID_MASK                                                                         ((uint32_t)(0x000003ffU))

#define MPU_GICC_AIAR_RESERVED_SHIFT                                                                        ((uint32_t)(13U))
#define MPU_GICC_AIAR_RESERVED_MASK                                                                         ((uint32_t)(0xffffe000U))

#define MPU_GICC_AIAR_CPUID_SHIFT                                                                           ((uint32_t)(10U))
#define MPU_GICC_AIAR_CPUID_MASK                                                                            ((uint32_t)(0x00001c00U))

#define MPU_GICC_AEOIR_EOIINTID_SHIFT                                                                       ((uint32_t)(0U))
#define MPU_GICC_AEOIR_EOIINTID_MASK                                                                        ((uint32_t)(0x000003ffU))

#define MPU_GICC_AEOIR_CPUID_SHIFT                                                                          ((uint32_t)(10U))
#define MPU_GICC_AEOIR_CPUID_MASK                                                                           ((uint32_t)(0x00001c00U))

#define MPU_GICC_AEOIR_RESERVED_SHIFT                                                                       ((uint32_t)(13U))
#define MPU_GICC_AEOIR_RESERVED_MASK                                                                        ((uint32_t)(0xffffe000U))

#define MPU_GICC_AHPPIR_RESERVED_SHIFT                                                                      ((uint32_t)(13U))
#define MPU_GICC_AHPPIR_RESERVED_MASK                                                                       ((uint32_t)(0xffffe000U))

#define MPU_GICC_AHPPIR_CPUID_SHIFT                                                                         ((uint32_t)(10U))
#define MPU_GICC_AHPPIR_CPUID_MASK                                                                          ((uint32_t)(0x00001c00U))

#define MPU_GICC_AHPPIR_PENDINTID_SHIFT                                                                     ((uint32_t)(0U))
#define MPU_GICC_AHPPIR_PENDINTID_MASK                                                                      ((uint32_t)(0x000003ffU))

#define MPU_GICC_APR0_AP0_SHIFT                                                                             ((uint32_t)(0U))
#define MPU_GICC_APR0_AP0_MASK                                                                              ((uint32_t)(0x00000001U))

#define MPU_GICC_APR0_AP1_SHIFT                                                                             ((uint32_t)(1U))
#define MPU_GICC_APR0_AP1_MASK                                                                              ((uint32_t)(0x00000002U))

#define MPU_GICC_APR0_AP2_SHIFT                                                                             ((uint32_t)(2U))
#define MPU_GICC_APR0_AP2_MASK                                                                              ((uint32_t)(0x00000004U))

#define MPU_GICC_APR0_AP3_SHIFT                                                                             ((uint32_t)(3U))
#define MPU_GICC_APR0_AP3_MASK                                                                              ((uint32_t)(0x00000008U))

#define MPU_GICC_APR0_AP4_SHIFT                                                                             ((uint32_t)(4U))
#define MPU_GICC_APR0_AP4_MASK                                                                              ((uint32_t)(0x00000010U))

#define MPU_GICC_APR0_AP5_SHIFT                                                                             ((uint32_t)(5U))
#define MPU_GICC_APR0_AP5_MASK                                                                              ((uint32_t)(0x00000020U))

#define MPU_GICC_APR0_AP6_SHIFT                                                                             ((uint32_t)(6U))
#define MPU_GICC_APR0_AP6_MASK                                                                              ((uint32_t)(0x00000040U))

#define MPU_GICC_APR0_AP7_SHIFT                                                                             ((uint32_t)(7U))
#define MPU_GICC_APR0_AP7_MASK                                                                              ((uint32_t)(0x00000080U))

#define MPU_GICC_APR0_AP8_SHIFT                                                                             ((uint32_t)(8U))
#define MPU_GICC_APR0_AP8_MASK                                                                              ((uint32_t)(0x00000100U))

#define MPU_GICC_APR0_AP9_SHIFT                                                                             ((uint32_t)(9U))
#define MPU_GICC_APR0_AP9_MASK                                                                              ((uint32_t)(0x00000200U))

#define MPU_GICC_APR0_AP10_SHIFT                                                                            ((uint32_t)(10U))
#define MPU_GICC_APR0_AP10_MASK                                                                             ((uint32_t)(0x00000400U))

#define MPU_GICC_APR0_AP11_SHIFT                                                                            ((uint32_t)(11U))
#define MPU_GICC_APR0_AP11_MASK                                                                             ((uint32_t)(0x00000800U))

#define MPU_GICC_APR0_AP12_SHIFT                                                                            ((uint32_t)(12U))
#define MPU_GICC_APR0_AP12_MASK                                                                             ((uint32_t)(0x00001000U))

#define MPU_GICC_APR0_AP13_SHIFT                                                                            ((uint32_t)(13U))
#define MPU_GICC_APR0_AP13_MASK                                                                             ((uint32_t)(0x00002000U))

#define MPU_GICC_APR0_AP14_SHIFT                                                                            ((uint32_t)(14U))
#define MPU_GICC_APR0_AP14_MASK                                                                             ((uint32_t)(0x00004000U))

#define MPU_GICC_APR0_AP15_SHIFT                                                                            ((uint32_t)(15U))
#define MPU_GICC_APR0_AP15_MASK                                                                             ((uint32_t)(0x00008000U))

#define MPU_GICC_APR0_AP16_SHIFT                                                                            ((uint32_t)(16U))
#define MPU_GICC_APR0_AP16_MASK                                                                             ((uint32_t)(0x00010000U))

#define MPU_GICC_APR0_AP17_SHIFT                                                                            ((uint32_t)(17U))
#define MPU_GICC_APR0_AP17_MASK                                                                             ((uint32_t)(0x00020000U))

#define MPU_GICC_APR0_AP18_SHIFT                                                                            ((uint32_t)(18U))
#define MPU_GICC_APR0_AP18_MASK                                                                             ((uint32_t)(0x00040000U))

#define MPU_GICC_APR0_AP19_SHIFT                                                                            ((uint32_t)(19U))
#define MPU_GICC_APR0_AP19_MASK                                                                             ((uint32_t)(0x00080000U))

#define MPU_GICC_APR0_AP20_SHIFT                                                                            ((uint32_t)(20U))
#define MPU_GICC_APR0_AP20_MASK                                                                             ((uint32_t)(0x00100000U))

#define MPU_GICC_APR0_AP21_SHIFT                                                                            ((uint32_t)(21U))
#define MPU_GICC_APR0_AP21_MASK                                                                             ((uint32_t)(0x00200000U))

#define MPU_GICC_APR0_AP22_SHIFT                                                                            ((uint32_t)(22U))
#define MPU_GICC_APR0_AP22_MASK                                                                             ((uint32_t)(0x00400000U))

#define MPU_GICC_APR0_AP23_SHIFT                                                                            ((uint32_t)(23U))
#define MPU_GICC_APR0_AP23_MASK                                                                             ((uint32_t)(0x00800000U))

#define MPU_GICC_APR0_AP24_SHIFT                                                                            ((uint32_t)(24U))
#define MPU_GICC_APR0_AP24_MASK                                                                             ((uint32_t)(0x01000000U))

#define MPU_GICC_APR0_AP25_SHIFT                                                                            ((uint32_t)(25U))
#define MPU_GICC_APR0_AP25_MASK                                                                             ((uint32_t)(0x02000000U))

#define MPU_GICC_APR0_AP26_SHIFT                                                                            ((uint32_t)(26U))
#define MPU_GICC_APR0_AP26_MASK                                                                             ((uint32_t)(0x04000000U))

#define MPU_GICC_APR0_AP27_SHIFT                                                                            ((uint32_t)(27U))
#define MPU_GICC_APR0_AP27_MASK                                                                             ((uint32_t)(0x08000000U))

#define MPU_GICC_APR0_AP28_SHIFT                                                                            ((uint32_t)(28U))
#define MPU_GICC_APR0_AP28_MASK                                                                             ((uint32_t)(0x10000000U))

#define MPU_GICC_APR0_AP29_SHIFT                                                                            ((uint32_t)(29U))
#define MPU_GICC_APR0_AP29_MASK                                                                             ((uint32_t)(0x20000000U))

#define MPU_GICC_APR0_AP30_SHIFT                                                                            ((uint32_t)(30U))
#define MPU_GICC_APR0_AP30_MASK                                                                             ((uint32_t)(0x40000000U))

#define MPU_GICC_APR0_AP31_SHIFT                                                                            ((uint32_t)(31U))
#define MPU_GICC_APR0_AP31_MASK                                                                             ((uint32_t)(0x80000000U))

#define MPU_GICC_NSAPR0_AP0_SHIFT                                                                           ((uint32_t)(0U))
#define MPU_GICC_NSAPR0_AP0_MASK                                                                            ((uint32_t)(0x00000001U))

#define MPU_GICC_NSAPR0_AP1_SHIFT                                                                           ((uint32_t)(1U))
#define MPU_GICC_NSAPR0_AP1_MASK                                                                            ((uint32_t)(0x00000002U))

#define MPU_GICC_NSAPR0_AP2_SHIFT                                                                           ((uint32_t)(2U))
#define MPU_GICC_NSAPR0_AP2_MASK                                                                            ((uint32_t)(0x00000004U))

#define MPU_GICC_NSAPR0_AP3_SHIFT                                                                           ((uint32_t)(3U))
#define MPU_GICC_NSAPR0_AP3_MASK                                                                            ((uint32_t)(0x00000008U))

#define MPU_GICC_NSAPR0_AP4_SHIFT                                                                           ((uint32_t)(4U))
#define MPU_GICC_NSAPR0_AP4_MASK                                                                            ((uint32_t)(0x00000010U))

#define MPU_GICC_NSAPR0_AP5_SHIFT                                                                           ((uint32_t)(5U))
#define MPU_GICC_NSAPR0_AP5_MASK                                                                            ((uint32_t)(0x00000020U))

#define MPU_GICC_NSAPR0_AP6_SHIFT                                                                           ((uint32_t)(6U))
#define MPU_GICC_NSAPR0_AP6_MASK                                                                            ((uint32_t)(0x00000040U))

#define MPU_GICC_NSAPR0_AP7_SHIFT                                                                           ((uint32_t)(7U))
#define MPU_GICC_NSAPR0_AP7_MASK                                                                            ((uint32_t)(0x00000080U))

#define MPU_GICC_NSAPR0_AP8_SHIFT                                                                           ((uint32_t)(8U))
#define MPU_GICC_NSAPR0_AP8_MASK                                                                            ((uint32_t)(0x00000100U))

#define MPU_GICC_NSAPR0_AP9_SHIFT                                                                           ((uint32_t)(9U))
#define MPU_GICC_NSAPR0_AP9_MASK                                                                            ((uint32_t)(0x00000200U))

#define MPU_GICC_NSAPR0_AP10_SHIFT                                                                          ((uint32_t)(10U))
#define MPU_GICC_NSAPR0_AP10_MASK                                                                           ((uint32_t)(0x00000400U))

#define MPU_GICC_NSAPR0_AP11_SHIFT                                                                          ((uint32_t)(11U))
#define MPU_GICC_NSAPR0_AP11_MASK                                                                           ((uint32_t)(0x00000800U))

#define MPU_GICC_NSAPR0_AP12_SHIFT                                                                          ((uint32_t)(12U))
#define MPU_GICC_NSAPR0_AP12_MASK                                                                           ((uint32_t)(0x00001000U))

#define MPU_GICC_NSAPR0_AP13_SHIFT                                                                          ((uint32_t)(13U))
#define MPU_GICC_NSAPR0_AP13_MASK                                                                           ((uint32_t)(0x00002000U))

#define MPU_GICC_NSAPR0_AP14_SHIFT                                                                          ((uint32_t)(14U))
#define MPU_GICC_NSAPR0_AP14_MASK                                                                           ((uint32_t)(0x00004000U))

#define MPU_GICC_NSAPR0_AP15_SHIFT                                                                          ((uint32_t)(15U))
#define MPU_GICC_NSAPR0_AP15_MASK                                                                           ((uint32_t)(0x00008000U))

#define MPU_GICC_NSAPR0_AP16_SHIFT                                                                          ((uint32_t)(16U))
#define MPU_GICC_NSAPR0_AP16_MASK                                                                           ((uint32_t)(0x00010000U))

#define MPU_GICC_NSAPR0_AP17_SHIFT                                                                          ((uint32_t)(17U))
#define MPU_GICC_NSAPR0_AP17_MASK                                                                           ((uint32_t)(0x00020000U))

#define MPU_GICC_NSAPR0_AP18_SHIFT                                                                          ((uint32_t)(18U))
#define MPU_GICC_NSAPR0_AP18_MASK                                                                           ((uint32_t)(0x00040000U))

#define MPU_GICC_NSAPR0_AP19_SHIFT                                                                          ((uint32_t)(19U))
#define MPU_GICC_NSAPR0_AP19_MASK                                                                           ((uint32_t)(0x00080000U))

#define MPU_GICC_NSAPR0_AP20_SHIFT                                                                          ((uint32_t)(20U))
#define MPU_GICC_NSAPR0_AP20_MASK                                                                           ((uint32_t)(0x00100000U))

#define MPU_GICC_NSAPR0_AP21_SHIFT                                                                          ((uint32_t)(21U))
#define MPU_GICC_NSAPR0_AP21_MASK                                                                           ((uint32_t)(0x00200000U))

#define MPU_GICC_NSAPR0_AP22_SHIFT                                                                          ((uint32_t)(22U))
#define MPU_GICC_NSAPR0_AP22_MASK                                                                           ((uint32_t)(0x00400000U))

#define MPU_GICC_NSAPR0_AP23_SHIFT                                                                          ((uint32_t)(23U))
#define MPU_GICC_NSAPR0_AP23_MASK                                                                           ((uint32_t)(0x00800000U))

#define MPU_GICC_NSAPR0_AP24_SHIFT                                                                          ((uint32_t)(24U))
#define MPU_GICC_NSAPR0_AP24_MASK                                                                           ((uint32_t)(0x01000000U))

#define MPU_GICC_NSAPR0_AP25_SHIFT                                                                          ((uint32_t)(25U))
#define MPU_GICC_NSAPR0_AP25_MASK                                                                           ((uint32_t)(0x02000000U))

#define MPU_GICC_NSAPR0_AP26_SHIFT                                                                          ((uint32_t)(26U))
#define MPU_GICC_NSAPR0_AP26_MASK                                                                           ((uint32_t)(0x04000000U))

#define MPU_GICC_NSAPR0_AP27_SHIFT                                                                          ((uint32_t)(27U))
#define MPU_GICC_NSAPR0_AP27_MASK                                                                           ((uint32_t)(0x08000000U))

#define MPU_GICC_NSAPR0_AP28_SHIFT                                                                          ((uint32_t)(28U))
#define MPU_GICC_NSAPR0_AP28_MASK                                                                           ((uint32_t)(0x10000000U))

#define MPU_GICC_NSAPR0_AP29_SHIFT                                                                          ((uint32_t)(29U))
#define MPU_GICC_NSAPR0_AP29_MASK                                                                           ((uint32_t)(0x20000000U))

#define MPU_GICC_NSAPR0_AP30_SHIFT                                                                          ((uint32_t)(30U))
#define MPU_GICC_NSAPR0_AP30_MASK                                                                           ((uint32_t)(0x40000000U))

#define MPU_GICC_NSAPR0_AP31_SHIFT                                                                          ((uint32_t)(31U))
#define MPU_GICC_NSAPR0_AP31_MASK                                                                           ((uint32_t)(0x80000000U))

#define MPU_GICC_IIDR_PRODUCTID_SHIFT                                                                       ((uint32_t)(20U))
#define MPU_GICC_IIDR_PRODUCTID_MASK                                                                        ((uint32_t)(0xfff00000U))

#define MPU_GICC_IIDR_ARCHITECTUREVERSION_SHIFT                                                             ((uint32_t)(16U))
#define MPU_GICC_IIDR_ARCHITECTUREVERSION_MASK                                                              ((uint32_t)(0x000f0000U))

#define MPU_GICC_IIDR_REVISION_SHIFT                                                                        ((uint32_t)(12U))
#define MPU_GICC_IIDR_REVISION_MASK                                                                         ((uint32_t)(0x0000f000U))

#define MPU_GICC_IIDR_IMPLEMENTER_SHIFT                                                                     ((uint32_t)(0U))
#define MPU_GICC_IIDR_IMPLEMENTER_MASK                                                                      ((uint32_t)(0x00000fffU))

#define MPU_GICC_DIR_INTERRUPTID_SHIFT                                                                      ((uint32_t)(0U))
#define MPU_GICC_DIR_INTERRUPTID_MASK                                                                       ((uint32_t)(0x000003ffU))

#define MPU_GICC_DIR_CPUID_SHIFT                                                                            ((uint32_t)(10U))
#define MPU_GICC_DIR_CPUID_MASK                                                                             ((uint32_t)(0x00001c00U))

#define MPU_GICC_DIR_RESERVED_SHIFT                                                                         ((uint32_t)(13U))
#define MPU_GICC_DIR_RESERVED_MASK                                                                          ((uint32_t)(0xffffe000U))

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_INTC_PHYS_H_ */
