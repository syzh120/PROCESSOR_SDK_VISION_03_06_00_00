/*
 *  Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_ctrl_core_sec.h
 *
 *  \brief  register-level header file for CTRL_CORE
 *
**/

#ifndef HW_CTRL_CORE_SEC_H_
#define HW_CTRL_CORE_SEC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_0                                                                  (0x100U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_1                                                                  (0x104U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_2                                                                  (0x108U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_3                                                                  (0x10cU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_4                                                                  (0x110U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_5                                                                  (0x114U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_0                                                                  (0x118U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_1                                                                  (0x11cU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_2                                                                  (0x120U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_3                                                                  (0x124U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_4                                                                  (0x128U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_5                                                                  (0x12cU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_6                                                                  (0x130U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_7                                                                  (0x134U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_0                                                            (0x138U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_1                                                            (0x13cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_2                                                            (0x140U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_3                                                            (0x144U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_4                                                            (0x148U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_0                                                               (0x14cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_1                                                               (0x150U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_2                                                               (0x154U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_3                                                               (0x158U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_4                                                               (0x15cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_0                                                              (0x160U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_1                                                              (0x164U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_2                                                              (0x168U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_3                                                              (0x16cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_4                                                              (0x170U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL                                                              (0x174U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL                                                              (0x178U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL                                                            (0x17cU)
#define CTRL_CORE_SMA_SW_2                                                                                 (0x204U)
#define CTRL_CORE_SMA_SW_3                                                                                 (0x208U)
#define CTRL_CORE_SMA_SW_4                                                                                 (0x20cU)
#define CTRL_CORE_SMA_SW_5                                                                                 (0x210U)
#define CTRL_CORE_SMA_SW_6                                                                                 (0x214U)
#define CTRL_CORE_SMA_SW_7                                                                                 (0x218U)
#define CTRL_CORE_SMA_SW_8                                                                                 (0x21cU)
#define CTRL_CORE_SMA_SW_9                                                                                 (0x220U)
#define CTRL_CORE_PCIESS1_PCS1                                                                             (0x224U)
#define CTRL_CORE_PCIESS1_PCS2                                                                             (0x228U)
#define CTRL_CORE_PCIESS2_PCS1                                                                             (0x22cU)
#define CTRL_CORE_PCIESS2_PCS2                                                                             (0x230U)
#define CTRL_CORE_PCIE_PCS                                                                                 (0x234U)
#define CTRL_CORE_PCIE_PCS_REVISION                                                                        (0x238U)
#define CTRL_CORE_PCIE_CONTROL                                                                             (0x23cU)
#define CTRL_CORE_PHY_POWER_PCIESS1                                                                        (0x240U)
#define CTRL_CORE_PHY_POWER_PCIESS2                                                                        (0x244U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_0_STD_FUSE_OPP_VMIN_GPU_0_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_0_STD_FUSE_OPP_VMIN_GPU_0_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_1_STD_FUSE_OPP_VMIN_GPU_1_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_1_STD_FUSE_OPP_VMIN_GPU_1_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_2_STD_FUSE_OPP_VMIN_GPU_2_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_2_STD_FUSE_OPP_VMIN_GPU_2_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_3_STD_FUSE_OPP_VMIN_GPU_3_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_3_STD_FUSE_OPP_VMIN_GPU_3_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_4_STD_FUSE_OPP_VMIN_GPU_4_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_4_STD_FUSE_OPP_VMIN_GPU_4_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_5_STD_FUSE_OPP_VMIN_GPU_5_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_5_STD_FUSE_OPP_VMIN_GPU_5_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_0_STD_FUSE_OPP_VMIN_MPU_0_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_0_STD_FUSE_OPP_VMIN_MPU_0_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_1_STD_FUSE_OPP_VMIN_MPU_1_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_1_STD_FUSE_OPP_VMIN_MPU_1_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_2_STD_FUSE_OPP_VMIN_MPU_2_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_2_STD_FUSE_OPP_VMIN_MPU_2_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_3_STD_FUSE_OPP_VMIN_MPU_3_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_3_STD_FUSE_OPP_VMIN_MPU_3_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_4_STD_FUSE_OPP_VMIN_MPU_4_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_4_STD_FUSE_OPP_VMIN_MPU_4_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_5_STD_FUSE_OPP_VMIN_MPU_5_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_5_STD_FUSE_OPP_VMIN_MPU_5_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_6_STD_FUSE_OPP_VMIN_MPU_6_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_6_STD_FUSE_OPP_VMIN_MPU_6_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_7_STD_FUSE_OPP_VMIN_MPU_7_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_7_STD_FUSE_OPP_VMIN_MPU_7_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_SHIFT                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_STD_FUSE_OPP_VDD_DSPEVE_LVT_0_MASK                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_SHIFT                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_STD_FUSE_OPP_VDD_DSPEVE_LVT_1_MASK                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_SHIFT                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_STD_FUSE_OPP_VDD_DSPEVE_LVT_2_MASK                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_SHIFT                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_STD_FUSE_OPP_VDD_DSPEVE_LVT_3_MASK                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_SHIFT                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_STD_FUSE_OPP_VDD_DSPEVE_LVT_4_MASK                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_0_STD_FUSE_OPP_VDD_IVA_LVT_0_SHIFT                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_0_STD_FUSE_OPP_VDD_IVA_LVT_0_MASK                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_1_STD_FUSE_OPP_VDD_IVA_LVT_1_SHIFT                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_1_STD_FUSE_OPP_VDD_IVA_LVT_1_MASK                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_2_STD_FUSE_OPP_VDD_IVA_LVT_2_SHIFT                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_2_STD_FUSE_OPP_VDD_IVA_LVT_2_MASK                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_3_STD_FUSE_OPP_VDD_IVA_LVT_3_SHIFT                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_3_STD_FUSE_OPP_VDD_IVA_LVT_3_MASK                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_4_STD_FUSE_OPP_VDD_IVA_LVT_4_SHIFT                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_LVT_4_STD_FUSE_OPP_VDD_IVA_LVT_4_MASK                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_0_STD_FUSE_OPP_VDD_CORE_LVT_0_SHIFT                           (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_0_STD_FUSE_OPP_VDD_CORE_LVT_0_MASK                            (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_1_STD_FUSE_OPP_VDD_CORE_LVT_1_SHIFT                           (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_1_STD_FUSE_OPP_VDD_CORE_LVT_1_MASK                            (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_2_STD_FUSE_OPP_VDD_CORE_LVT_2_SHIFT                           (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_2_STD_FUSE_OPP_VDD_CORE_LVT_2_MASK                            (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_3_STD_FUSE_OPP_VDD_CORE_LVT_3_SHIFT                           (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_3_STD_FUSE_OPP_VDD_CORE_LVT_3_MASK                            (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_4_STD_FUSE_OPP_VDD_CORE_LVT_4_SHIFT                           (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_LVT_4_STD_FUSE_OPP_VDD_CORE_LVT_4_MASK                            (0xffffffffU)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_MUX_CTRL_SHIFT                        (26U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_MUX_CTRL_MASK                         (0x04000000U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_MUX_CTRL_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_MUX_CTRL_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_VSET_IN_SHIFT                         (21U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_VSET_IN_MASK                          (0x03e00000U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_VSET_OUT_SHIFT                        (16U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_RETMODE_VSET_OUT_MASK                         (0x001f0000U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_MUX_CTRL_SHIFT                        (10U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_MUX_CTRL_MASK                         (0x00000400U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_MUX_CTRL_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_MUX_CTRL_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_VSET_IN_SHIFT                         (5U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_VSET_IN_MASK                          (0x000003e0U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_VSET_OUT_SHIFT                        (0U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_LDOSRAMCORE_4_ACTMODE_VSET_OUT_MASK                         (0x0000001fU)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_RESERVED_0_SHIFT                                            (11U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_RESERVED_0_MASK                                             (0x0000f800U)

#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_RESERVED_1_SHIFT                                            (27U)
#define CTRL_CORE_LDOSRAM_CORE_4_VOLTAGE_CTRL_RESERVED_1_MASK                                             (0xf8000000U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_MUX_CTRL_SHIFT                        (26U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_MUX_CTRL_MASK                         (0x04000000U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_MUX_CTRL_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_MUX_CTRL_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_VSET_IN_SHIFT                         (21U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_VSET_IN_MASK                          (0x03e00000U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_VSET_OUT_SHIFT                        (16U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_RETMODE_VSET_OUT_MASK                         (0x001f0000U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_MUX_CTRL_SHIFT                        (10U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_MUX_CTRL_MASK                         (0x00000400U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_MUX_CTRL_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_MUX_CTRL_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_VSET_IN_SHIFT                         (5U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_VSET_IN_MASK                          (0x000003e0U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_VSET_OUT_SHIFT                        (0U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_LDOSRAMCORE_5_ACTMODE_VSET_OUT_MASK                         (0x0000001fU)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_RESERVED_0_SHIFT                                            (11U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_RESERVED_0_MASK                                             (0x0000f800U)

#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_RESERVED_1_SHIFT                                            (27U)
#define CTRL_CORE_LDOSRAM_CORE_5_VOLTAGE_CTRL_RESERVED_1_MASK                                             (0xf8000000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_MUX_CTRL_SHIFT                    (26U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_MUX_CTRL_MASK                     (0x04000000U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_MUX_CTRL_OCP                      (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_MUX_CTRL_EFUSE                    (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_VSET_IN_SHIFT                     (21U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_VSET_IN_MASK                      (0x03e00000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_VSET_OUT_SHIFT                    (16U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_RETMODE_VSET_OUT_MASK                     (0x001f0000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_MUX_CTRL_SHIFT                    (10U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_MUX_CTRL_MASK                     (0x00000400U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_MUX_CTRL_OCP                      (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_MUX_CTRL_EFUSE                    (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_VSET_IN_SHIFT                     (5U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_VSET_IN_MASK                      (0x000003e0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_VSET_OUT_SHIFT                    (0U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_LDOSRAMDSPEVE_2_ACTMODE_VSET_OUT_MASK                     (0x0000001fU)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_RESERVED_0_SHIFT                                          (11U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_RESERVED_0_MASK                                           (0x0000f800U)

#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_RESERVED_1_SHIFT                                          (27U)
#define CTRL_CORE_LDOSRAM_DSPEVE_2_VOLTAGE_CTRL_RESERVED_1_MASK                                           (0xf8000000U)

#define CTRL_CORE_SMA_SW_2_SMA_SW_2_SHIFT                                                                 (0U)
#define CTRL_CORE_SMA_SW_2_SMA_SW_2_MASK                                                                  (0xffffffffU)

#define CTRL_CORE_SMA_SW_3_SMA_SW_3_SHIFT                                                                 (2U)
#define CTRL_CORE_SMA_SW_3_SMA_SW_3_MASK                                                                  (0xfffffffcU)

#define CTRL_CORE_SMA_SW_3_DSP2_LRST_DONE_RESERVED_SHIFT                                                  (1U)
#define CTRL_CORE_SMA_SW_3_DSP2_LRST_DONE_RESERVED_MASK                                                   (0x00000002U)

#define CTRL_CORE_SMA_SW_3_DSP1_LRST_DONE_RESERVED_SHIFT                                                  (0U)
#define CTRL_CORE_SMA_SW_3_DSP1_LRST_DONE_RESERVED_MASK                                                   (0x00000001U)

#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_EXP7_LOCK_SHIFT                                                     (31U)
#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_EXP7_LOCK_MASK                                                      (0x80000000U)

#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_CSI2_2_SHIFT                                                        (9U)
#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_CSI2_2_MASK                                                         (0x00000e00U)

#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_CSI2_1_SHIFT                                                        (6U)
#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_CSI2_1_MASK                                                         (0x000001c0U)

#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_DSP2_EDMA_SHIFT                                                     (3U)
#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_DSP2_EDMA_MASK                                                      (0x00000038U)

#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_DSP1_EDMA_SHIFT                                                     (0U)
#define CTRL_CORE_SMA_SW_4_MREQDOMAIN_DSP1_EDMA_MASK                                                      (0x00000007U)

#define CTRL_CORE_SMA_SW_4_RESERVED_0_SHIFT                                                               (12U)
#define CTRL_CORE_SMA_SW_4_RESERVED_0_MASK                                                                (0x7ffff000U)

#define CTRL_CORE_SMA_SW_5_SMA_SW_5_RESERVED_SHIFT                                                        (1U)
#define CTRL_CORE_SMA_SW_5_SMA_SW_5_RESERVED_MASK                                                         (0xfffffffeU)

#define CTRL_CORE_SMA_SW_5_TSHUT_OVERRIDE_SHIFT                                                           (0U)
#define CTRL_CORE_SMA_SW_5_TSHUT_OVERRIDE_MASK                                                            (0x00000001U)

#define CTRL_CORE_SMA_SW_6_SMA_SW_6_RESERVED_SHIFT                                                        (29U)
#define CTRL_CORE_SMA_SW_6_SMA_SW_6_RESERVED_MASK                                                         (0xe0000000U)

#define CTRL_CORE_SMA_SW_6_PLLEN_CONTROL_SHIFT                                                            (24U)
#define CTRL_CORE_SMA_SW_6_PLLEN_CONTROL_MASK                                                             (0x1f000000U)

#define CTRL_CORE_SMA_SW_6_PCIE_TX_RX_CONTROL_SHIFT                                                       (16U)
#define CTRL_CORE_SMA_SW_6_PCIE_TX_RX_CONTROL_MASK                                                        (0x00030000U)

#define CTRL_CORE_SMA_SW_6_RMII_CLK_SETTING_SHIFT                                                         (8U)
#define CTRL_CORE_SMA_SW_6_RMII_CLK_SETTING_MASK                                                          (0x00000100U)

#define CTRL_CORE_SMA_SW_6_MUXSEL_32K_CLKIN_SHIFT                                                         (0U)
#define CTRL_CORE_SMA_SW_6_MUXSEL_32K_CLKIN_MASK                                                          (0x00000001U)

#define CTRL_CORE_SMA_SW_6_RESERVED_0_SHIFT                                                               (1U)
#define CTRL_CORE_SMA_SW_6_RESERVED_0_MASK                                                                (0x000000feU)

#define CTRL_CORE_SMA_SW_6_RESERVED_1_SHIFT                                                               (9U)
#define CTRL_CORE_SMA_SW_6_RESERVED_1_MASK                                                                (0x0000fe00U)

#define CTRL_CORE_SMA_SW_6_RESERVED_2_SHIFT                                                               (18U)
#define CTRL_CORE_SMA_SW_6_RESERVED_2_MASK                                                                (0x00fc0000U)

#define CTRL_CORE_SMA_SW_7_SMA_SW_7_RESERVED_SHIFT                                                        (18U)
#define CTRL_CORE_SMA_SW_7_SMA_SW_7_RESERVED_MASK                                                         (0xfffc0000U)

#define CTRL_CORE_SMA_SW_7_MMU1_ABORT_ENABLE_SHIFT                                                        (17U)
#define CTRL_CORE_SMA_SW_7_MMU1_ABORT_ENABLE_MASK                                                         (0x00020000U)

#define CTRL_CORE_SMA_SW_7_MMU2_ABORT_ENABLE_SHIFT                                                        (16U)
#define CTRL_CORE_SMA_SW_7_MMU2_ABORT_ENABLE_MASK                                                         (0x00010000U)

#define CTRL_CORE_SMA_SW_7_EDMA_TC1_WR_MMU_ROUTE_ENABLE_SHIFT                                             (13U)
#define CTRL_CORE_SMA_SW_7_EDMA_TC1_WR_MMU_ROUTE_ENABLE_MASK                                              (0x00002000U)

#define CTRL_CORE_SMA_SW_7_EDMA_TC1_RD_MMU_ROUTE_ENABLE_SHIFT                                             (12U)
#define CTRL_CORE_SMA_SW_7_EDMA_TC1_RD_MMU_ROUTE_ENABLE_MASK                                              (0x00001000U)

#define CTRL_CORE_SMA_SW_7_EDMA_TC0_WR_MMU_ROUTE_ENABLE_SHIFT                                             (11U)
#define CTRL_CORE_SMA_SW_7_EDMA_TC0_WR_MMU_ROUTE_ENABLE_MASK                                              (0x00000800U)

#define CTRL_CORE_SMA_SW_7_EDMA_TC0_RD_MMU_ROUTE_ENABLE_SHIFT                                             (10U)
#define CTRL_CORE_SMA_SW_7_EDMA_TC0_RD_MMU_ROUTE_ENABLE_MASK                                              (0x00000400U)

#define CTRL_CORE_SMA_SW_7_PCIE_SS2_MMU_ROUTE_ENABLE_SHIFT                                                (9U)
#define CTRL_CORE_SMA_SW_7_PCIE_SS2_MMU_ROUTE_ENABLE_MASK                                                 (0x00000200U)

#define CTRL_CORE_SMA_SW_7_PCIE_SS1_MMU_ROUTE_ENABLE_SHIFT                                                (8U)
#define CTRL_CORE_SMA_SW_7_PCIE_SS1_MMU_ROUTE_ENABLE_MASK                                                 (0x00000100U)

#define CTRL_CORE_SMA_SW_7_PCIE_SS1_AXI2OCP_LEGACY_MODE_ENABLE_SHIFT                                      (1U)
#define CTRL_CORE_SMA_SW_7_PCIE_SS1_AXI2OCP_LEGACY_MODE_ENABLE_MASK                                       (0x00000002U)

#define CTRL_CORE_SMA_SW_7_PCIE_SS2_AXI2OCP_LEGACY_MODE_ENABLE_SHIFT                                      (0U)
#define CTRL_CORE_SMA_SW_7_PCIE_SS2_AXI2OCP_LEGACY_MODE_ENABLE_MASK                                       (0x00000001U)

#define CTRL_CORE_SMA_SW_7_RESERVED_0_SHIFT                                                               (2U)
#define CTRL_CORE_SMA_SW_7_RESERVED_0_MASK                                                                (0x000000fcU)

#define CTRL_CORE_SMA_SW_7_RESERVED_1_SHIFT                                                               (14U)
#define CTRL_CORE_SMA_SW_7_RESERVED_1_MASK                                                                (0x0000c000U)

#define CTRL_CORE_SMA_SW_8_PCIE_PLL_TEST_INPUT_1_SHIFT                                                    (0U)
#define CTRL_CORE_SMA_SW_8_PCIE_PLL_TEST_INPUT_1_MASK                                                     (0xffffffffU)

#define CTRL_CORE_SMA_SW_9_PCIE_PLL_TEST_INPUT_2_SHIFT                                                    (0U)
#define CTRL_CORE_SMA_SW_9_PCIE_PLL_TEST_INPUT_2_MASK                                                     (0xffffffffU)

#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_TEST_TXDATA_SHIFT                                              (22U)
#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_TEST_TXDATA_MASK                                               (0xffc00000U)

#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_ERR_BIT_EN_SHIFT                                               (12U)
#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_ERR_BIT_EN_MASK                                                (0x003ff000U)

#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_CFG_HOLDOFF_SHIFT                                              (4U)
#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_CFG_HOLDOFF_MASK                                               (0x00000ff0U)

#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_DET_DELAY_SHIFT                                                (0U)
#define CTRL_CORE_PCIESS1_PCS1_PCIESS1_PCS_DET_DELAY_MASK                                                 (0x0000000fU)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_SYNC_SHIFT                                                 (27U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_SYNC_MASK                                                  (0xf8000000U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_FUNC_SHIFT                                              (23U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_FUNC_MASK                                               (0x07800000U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_HOLD_SHIFT                                              (19U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_HOLD_MASK                                               (0x00780000U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_INIT_SHIFT                                              (15U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_CFG_EQ_INIT_MASK                                               (0x00078000U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_OSEL_SHIFT                                                (12U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_OSEL_MASK                                                 (0x00007000U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_LSEL_SHIFT                                                (9U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_LSEL_MASK                                                 (0x00000200U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_ERR_MODE_SHIFT                                                 (6U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_ERR_MODE_MASK                                                  (0x000000c0U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_L1_SLEEP_SHIFT                                                 (5U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_L1_SLEEP_MASK                                                  (0x00000020U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_MODE_SHIFT                                                (4U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_TEST_MODE_MASK                                                 (0x00000010U)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_ERR_LN_EN_SHIFT                                                (2U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_ERR_LN_EN_MASK                                                 (0x0000000cU)

#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_SHORT_TIMES_SHIFT                                              (0U)
#define CTRL_CORE_PCIESS1_PCS2_PCIESS1_PCS_SHORT_TIMES_MASK                                               (0x00000001U)

#define CTRL_CORE_PCIESS1_PCS2_RESERVED_0_SHIFT                                                           (1U)
#define CTRL_CORE_PCIESS1_PCS2_RESERVED_0_MASK                                                            (0x00000002U)

#define CTRL_CORE_PCIESS1_PCS2_RESERVED_1_SHIFT                                                           (8U)
#define CTRL_CORE_PCIESS1_PCS2_RESERVED_1_MASK                                                            (0x00000100U)

#define CTRL_CORE_PCIESS1_PCS2_RESERVED_2_SHIFT                                                           (10U)
#define CTRL_CORE_PCIESS1_PCS2_RESERVED_2_MASK                                                            (0x00000c00U)

#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_TEST_TXDATA_SHIFT                                              (22U)
#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_TEST_TXDATA_MASK                                               (0xffc00000U)

#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_ERR_BIT_EN_SHIFT                                               (12U)
#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_ERR_BIT_EN_MASK                                                (0x003ff000U)

#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_CFG_HOLDOFF_SHIFT                                              (4U)
#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_CFG_HOLDOFF_MASK                                               (0x00000ff0U)

#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_DET_DELAY_SHIFT                                                (0U)
#define CTRL_CORE_PCIESS2_PCS1_PCIESS2_PCS_DET_DELAY_MASK                                                 (0x0000000fU)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_SYNC_SHIFT                                                 (27U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_SYNC_MASK                                                  (0xf8000000U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_FUNC_SHIFT                                              (23U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_FUNC_MASK                                               (0x07800000U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_HOLD_SHIFT                                              (19U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_HOLD_MASK                                               (0x00780000U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_INIT_SHIFT                                              (15U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_CFG_EQ_INIT_MASK                                               (0x00078000U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_OSEL_SHIFT                                                (12U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_OSEL_MASK                                                 (0x00007000U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_LSEL_SHIFT                                                (9U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_LSEL_MASK                                                 (0x00000200U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_ERR_MODE_SHIFT                                                 (6U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_ERR_MODE_MASK                                                  (0x000000c0U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_L1_SLEEP_SHIFT                                                 (5U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_L1_SLEEP_MASK                                                  (0x00000020U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_MODE_SHIFT                                                (4U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_TEST_MODE_MASK                                                 (0x00000010U)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_ERR_LN_EN_SHIFT                                                (2U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_ERR_LN_EN_MASK                                                 (0x0000000cU)

#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_SHORT_TIMES_SHIFT                                              (0U)
#define CTRL_CORE_PCIESS2_PCS2_PCIESS2_PCS_SHORT_TIMES_MASK                                               (0x00000001U)

#define CTRL_CORE_PCIESS2_PCS2_RESERVED_0_SHIFT                                                           (1U)
#define CTRL_CORE_PCIESS2_PCS2_RESERVED_0_MASK                                                            (0x00000002U)

#define CTRL_CORE_PCIESS2_PCS2_RESERVED_1_SHIFT                                                           (8U)
#define CTRL_CORE_PCIESS2_PCS2_RESERVED_1_MASK                                                            (0x00000100U)

#define CTRL_CORE_PCIESS2_PCS2_RESERVED_2_SHIFT                                                           (10U)
#define CTRL_CORE_PCIESS2_PCS2_RESERVED_2_MASK                                                            (0x00000c00U)

#define CTRL_CORE_PCIE_PCS_PCIESS2_PCS_RC_DELAY_COUNT_SHIFT                                               (16U)
#define CTRL_CORE_PCIE_PCS_PCIESS2_PCS_RC_DELAY_COUNT_MASK                                                (0x00ff0000U)

#define CTRL_CORE_PCIE_PCS_PCIESS1_PCS_RC_DELAY_COUNT_SHIFT                                               (8U)
#define CTRL_CORE_PCIE_PCS_PCIESS1_PCS_RC_DELAY_COUNT_MASK                                                (0x0000ff00U)

#define CTRL_CORE_PCIE_PCS_RESERVED_0_SHIFT                                                               (0U)
#define CTRL_CORE_PCIE_PCS_RESERVED_0_MASK                                                                (0x000000ffU)

#define CTRL_CORE_PCIE_PCS_RESERVED_1_SHIFT                                                               (24U)
#define CTRL_CORE_PCIE_PCS_RESERVED_1_MASK                                                                (0xff000000U)

#define CTRL_CORE_PCIE_PCS_REVISION_PCIESS2_PCS_REVISION_SHIFT                                            (23U)
#define CTRL_CORE_PCIE_PCS_REVISION_PCIESS2_PCS_REVISION_MASK                                             (0x03800000U)

#define CTRL_CORE_PCIE_PCS_REVISION_PCIESS1_PCS_REVISION_SHIFT                                            (20U)
#define CTRL_CORE_PCIE_PCS_REVISION_PCIESS1_PCS_REVISION_MASK                                             (0x00700000U)

#define CTRL_CORE_PCIE_PCS_REVISION_RESERVED_0_SHIFT                                                      (0U)
#define CTRL_CORE_PCIE_PCS_REVISION_RESERVED_0_MASK                                                       (0x000fffffU)

#define CTRL_CORE_PCIE_PCS_REVISION_RESERVED_1_SHIFT                                                      (26U)
#define CTRL_CORE_PCIE_PCS_REVISION_RESERVED_1_MASK                                                       (0xfc000000U)

#define CTRL_CORE_PCIE_CONTROL_PCIE_B1C0_MODE_SEL_SHIFT                                                   (2U)
#define CTRL_CORE_PCIE_CONTROL_PCIE_B1C0_MODE_SEL_MASK                                                    (0x00000004U)

#define CTRL_CORE_PCIE_CONTROL_PCIE_B0_B1_TSYNCEN_SHIFT                                                   (0U)
#define CTRL_CORE_PCIE_CONTROL_PCIE_B0_B1_TSYNCEN_MASK                                                    (0x00000001U)

#define CTRL_CORE_PCIE_CONTROL_RESERVED_0_SHIFT                                                           (1U)
#define CTRL_CORE_PCIE_CONTROL_RESERVED_0_MASK                                                            (0x00000002U)

#define CTRL_CORE_PCIE_CONTROL_RESERVED_1_SHIFT                                                           (3U)
#define CTRL_CORE_PCIE_CONTROL_RESERVED_1_MASK                                                            (0xfffffff8U)

#define CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CLKFREQ_SHIFT                                          (22U)
#define CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CLKFREQ_MASK                                           (0xffc00000U)

#define CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CMD_SHIFT                                              (14U)
#define CTRL_CORE_PHY_POWER_PCIESS1_PCIESS1_PWRCTL_CMD_MASK                                               (0x003fc000U)

#define CTRL_CORE_PHY_POWER_PCIESS1_RESERVED_0_SHIFT                                                      (0U)
#define CTRL_CORE_PHY_POWER_PCIESS1_RESERVED_0_MASK                                                       (0x00003fffU)

#define CTRL_CORE_PHY_POWER_PCIESS2_PCIESS2_PWRCTL_CLKFREQ_SHIFT                                          (22U)
#define CTRL_CORE_PHY_POWER_PCIESS2_PCIESS2_PWRCTL_CLKFREQ_MASK                                           (0xffc00000U)

#define CTRL_CORE_PHY_POWER_PCIESS2_PCIESS2_PWRCTL_CMD_SHIFT                                              (14U)
#define CTRL_CORE_PHY_POWER_PCIESS2_PCIESS2_PWRCTL_CMD_MASK                                               (0x003fc000U)

#define CTRL_CORE_PHY_POWER_PCIESS2_RESERVED_0_SHIFT                                                      (0U)
#define CTRL_CORE_PHY_POWER_PCIESS2_RESERVED_0_MASK                                                       (0x00003fffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_CORE_SEC_H_ */
