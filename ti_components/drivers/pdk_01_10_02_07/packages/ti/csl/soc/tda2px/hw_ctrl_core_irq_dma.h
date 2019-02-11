/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2013
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
*  \file   hw_ctrl_core_irq_dma.h
*
*  \brief  register-level header file for CTRL_CORE
*
**/

#ifndef HW_CTRL_CORE_IRQ_DMA_H_
#define HW_CTRL_CORE_IRQ_DMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CTRL_CORE_EVE1_IRQ_0_1                                                                              (0x0U)
#define CTRL_CORE_EVE1_IRQ_2_3                                                                              (0x4U)
#define CTRL_CORE_EVE1_IRQ_4_5                                                                              (0x8U)
#define CTRL_CORE_EVE1_IRQ_6_7                                                                              (0xcU)
#define CTRL_CORE_EVE2_IRQ_0_1                                                                              (0x10U)
#define CTRL_CORE_EVE2_IRQ_2_3                                                                              (0x14U)
#define CTRL_CORE_EVE2_IRQ_4_5                                                                              (0x18U)
#define CTRL_CORE_EVE2_IRQ_6_7                                                                              (0x1cU)
#define CTRL_CORE_EVE3_IRQ_0_1                                                                              (0x20U)
#define CTRL_CORE_EVE3_IRQ_2_3                                                                              (0x24U)
#define CTRL_CORE_EVE3_IRQ_4_5                                                                              (0x28U)
#define CTRL_CORE_EVE3_IRQ_6_7                                                                              (0x2cU)
#define CTRL_CORE_EVE4_IRQ_0_1                                                                              (0x30U)
#define CTRL_CORE_EVE4_IRQ_2_3                                                                              (0x34U)
#define CTRL_CORE_EVE4_IRQ_4_5                                                                              (0x38U)
#define CTRL_CORE_EVE4_IRQ_6_7                                                                              (0x3cU)
#define CTRL_CORE_IPU1_IRQ_23_24                                                                            (0x40U)
#define CTRL_CORE_IPU1_IRQ_25_26                                                                            (0x44U)
#define CTRL_CORE_IPU1_IRQ_27_28                                                                            (0x48U)
#define CTRL_CORE_IPU1_IRQ_29_30                                                                            (0x4cU)
#define CTRL_CORE_IPU1_IRQ_31_32                                                                            (0x50U)
#define CTRL_CORE_IPU1_IRQ_33_34                                                                            (0x54U)
#define CTRL_CORE_IPU1_IRQ_35_36                                                                            (0x58U)
#define CTRL_CORE_IPU1_IRQ_37_38                                                                            (0x5cU)
#define CTRL_CORE_IPU1_IRQ_39_40                                                                            (0x60U)
#define CTRL_CORE_IPU1_IRQ_41_42                                                                            (0x64U)
#define CTRL_CORE_IPU1_IRQ_43_44                                                                            (0x68U)
#define CTRL_CORE_IPU1_IRQ_45_46                                                                            (0x6cU)
#define CTRL_CORE_IPU1_IRQ_47_48                                                                            (0x70U)
#define CTRL_CORE_IPU1_IRQ_49_50                                                                            (0x74U)
#define CTRL_CORE_IPU1_IRQ_51_52                                                                            (0x78U)
#define CTRL_CORE_IPU1_IRQ_53_54                                                                            (0x7cU)
#define CTRL_CORE_IPU1_IRQ_55_56                                                                            (0x80U)
#define CTRL_CORE_IPU1_IRQ_57_58                                                                            (0x84U)
#define CTRL_CORE_IPU1_IRQ_59_60                                                                            (0x88U)
#define CTRL_CORE_IPU1_IRQ_61_62                                                                            (0x8cU)
#define CTRL_CORE_IPU1_IRQ_63_64                                                                            (0x90U)
#define CTRL_CORE_IPU1_IRQ_65_66                                                                            (0x94U)
#define CTRL_CORE_IPU1_IRQ_67_68                                                                            (0x98U)
#define CTRL_CORE_IPU1_IRQ_69_70                                                                            (0x9cU)
#define CTRL_CORE_IPU1_IRQ_71_72                                                                            (0xa0U)
#define CTRL_CORE_IPU1_IRQ_73_74                                                                            (0xa4U)
#define CTRL_CORE_IPU1_IRQ_75_76                                                                            (0xa8U)
#define CTRL_CORE_IPU1_IRQ_77_78                                                                            (0xacU)
#define CTRL_CORE_IPU1_IRQ_79_80                                                                            (0xb0U)
#define CTRL_CORE_IPU2_IRQ_23_24                                                                            (0xb4U)
#define CTRL_CORE_IPU2_IRQ_25_26                                                                            (0xb8U)
#define CTRL_CORE_IPU2_IRQ_27_28                                                                            (0xbcU)
#define CTRL_CORE_IPU2_IRQ_29_30                                                                            (0xc0U)
#define CTRL_CORE_IPU2_IRQ_31_32                                                                            (0xc4U)
#define CTRL_CORE_IPU2_IRQ_33_34                                                                            (0xc8U)
#define CTRL_CORE_IPU2_IRQ_35_36                                                                            (0xccU)
#define CTRL_CORE_IPU2_IRQ_37_38                                                                            (0xd0U)
#define CTRL_CORE_IPU2_IRQ_39_40                                                                            (0xd4U)
#define CTRL_CORE_IPU2_IRQ_41_42                                                                            (0xd8U)
#define CTRL_CORE_IPU2_IRQ_43_44                                                                            (0xdcU)
#define CTRL_CORE_IPU2_IRQ_45_46                                                                            (0xe0U)
#define CTRL_CORE_IPU2_IRQ_47_48                                                                            (0xe4U)
#define CTRL_CORE_IPU2_IRQ_49_50                                                                            (0xe8U)
#define CTRL_CORE_IPU2_IRQ_51_52                                                                            (0xecU)
#define CTRL_CORE_IPU2_IRQ_53_54                                                                            (0xf0U)
#define CTRL_CORE_IPU2_IRQ_55_56                                                                            (0xf4U)
#define CTRL_CORE_IPU2_IRQ_57_58                                                                            (0xf8U)
#define CTRL_CORE_IPU2_IRQ_59_60                                                                            (0xfcU)
#define CTRL_CORE_IPU2_IRQ_61_62                                                                            (0x100U)
#define CTRL_CORE_IPU2_IRQ_63_64                                                                            (0x104U)
#define CTRL_CORE_IPU2_IRQ_65_66                                                                            (0x108U)
#define CTRL_CORE_IPU2_IRQ_67_68                                                                            (0x10cU)
#define CTRL_CORE_IPU2_IRQ_69_70                                                                            (0x110U)
#define CTRL_CORE_IPU2_IRQ_71_72                                                                            (0x114U)
#define CTRL_CORE_IPU2_IRQ_73_74                                                                            (0x118U)
#define CTRL_CORE_IPU2_IRQ_75_76                                                                            (0x11cU)
#define CTRL_CORE_IPU2_IRQ_77_78                                                                            (0x120U)
#define CTRL_CORE_IPU2_IRQ_79_80                                                                            (0x124U)
#define CTRL_CORE_PRUSS1_IRQ_32_33                                                                          (0x128U)
#define CTRL_CORE_PRUSS1_IRQ_34_35                                                                          (0x12cU)
#define CTRL_CORE_PRUSS1_IRQ_36_37                                                                          (0x130U)
#define CTRL_CORE_PRUSS1_IRQ_38_39                                                                          (0x134U)
#define CTRL_CORE_PRUSS1_IRQ_40_41                                                                          (0x138U)
#define CTRL_CORE_PRUSS1_IRQ_42_43                                                                          (0x13cU)
#define CTRL_CORE_PRUSS1_IRQ_44_45                                                                          (0x140U)
#define CTRL_CORE_PRUSS1_IRQ_46_47                                                                          (0x144U)
#define CTRL_CORE_PRUSS1_IRQ_48_49                                                                          (0x148U)
#define CTRL_CORE_PRUSS1_IRQ_50_51                                                                          (0x14cU)
#define CTRL_CORE_PRUSS1_IRQ_52_53                                                                          (0x150U)
#define CTRL_CORE_PRUSS1_IRQ_54_55                                                                          (0x154U)
#define CTRL_CORE_PRUSS1_IRQ_56_57                                                                          (0x158U)
#define CTRL_CORE_PRUSS1_IRQ_58_59                                                                          (0x15cU)
#define CTRL_CORE_PRUSS1_IRQ_60_61                                                                          (0x160U)
#define CTRL_CORE_PRUSS1_IRQ_62_63                                                                          (0x164U)
#define CTRL_CORE_DSP1_IRQ_32_33                                                                            (0x1a8U)
#define CTRL_CORE_DSP1_IRQ_34_35                                                                            (0x1acU)
#define CTRL_CORE_DSP1_IRQ_36_37                                                                            (0x1b0U)
#define CTRL_CORE_DSP1_IRQ_38_39                                                                            (0x1b4U)
#define CTRL_CORE_DSP1_IRQ_40_41                                                                            (0x1b8U)
#define CTRL_CORE_DSP1_IRQ_42_43                                                                            (0x1bcU)
#define CTRL_CORE_DSP1_IRQ_44_45                                                                            (0x1c0U)
#define CTRL_CORE_DSP1_IRQ_46_47                                                                            (0x1c4U)
#define CTRL_CORE_DSP1_IRQ_48_49                                                                            (0x1c8U)
#define CTRL_CORE_DSP1_IRQ_50_51                                                                            (0x1ccU)
#define CTRL_CORE_DSP1_IRQ_52_53                                                                            (0x1d0U)
#define CTRL_CORE_DSP1_IRQ_54_55                                                                            (0x1d4U)
#define CTRL_CORE_DSP1_IRQ_56_57                                                                            (0x1d8U)
#define CTRL_CORE_DSP1_IRQ_58_59                                                                            (0x1dcU)
#define CTRL_CORE_DSP1_IRQ_60_61                                                                            (0x1e0U)
#define CTRL_CORE_DSP1_IRQ_62_63                                                                            (0x1e4U)
#define CTRL_CORE_DSP1_IRQ_64_65                                                                            (0x1e8U)
#define CTRL_CORE_DSP1_IRQ_66_67                                                                            (0x1ecU)
#define CTRL_CORE_DSP1_IRQ_68_69                                                                            (0x1f0U)
#define CTRL_CORE_DSP1_IRQ_70_71                                                                            (0x1f4U)
#define CTRL_CORE_DSP1_IRQ_72_73                                                                            (0x1f8U)
#define CTRL_CORE_DSP1_IRQ_74_75                                                                            (0x1fcU)
#define CTRL_CORE_DSP1_IRQ_76_77                                                                            (0x200U)
#define CTRL_CORE_DSP1_IRQ_78_79                                                                            (0x204U)
#define CTRL_CORE_DSP1_IRQ_80_81                                                                            (0x208U)
#define CTRL_CORE_DSP1_IRQ_82_83                                                                            (0x20cU)
#define CTRL_CORE_DSP1_IRQ_84_85                                                                            (0x210U)
#define CTRL_CORE_DSP1_IRQ_86_87                                                                            (0x214U)
#define CTRL_CORE_DSP1_IRQ_88_89                                                                            (0x218U)
#define CTRL_CORE_DSP1_IRQ_90_91                                                                            (0x21cU)
#define CTRL_CORE_DSP1_IRQ_92_93                                                                            (0x220U)
#define CTRL_CORE_DSP1_IRQ_94_95                                                                            (0x224U)
#define CTRL_CORE_DSP2_IRQ_32_33                                                                            (0x228U)
#define CTRL_CORE_DSP2_IRQ_34_35                                                                            (0x22cU)
#define CTRL_CORE_DSP2_IRQ_36_37                                                                            (0x230U)
#define CTRL_CORE_DSP2_IRQ_38_39                                                                            (0x234U)
#define CTRL_CORE_DSP2_IRQ_40_41                                                                            (0x238U)
#define CTRL_CORE_DSP2_IRQ_42_43                                                                            (0x23cU)
#define CTRL_CORE_DSP2_IRQ_44_45                                                                            (0x240U)
#define CTRL_CORE_DSP2_IRQ_46_47                                                                            (0x244U)
#define CTRL_CORE_DSP2_IRQ_48_49                                                                            (0x248U)
#define CTRL_CORE_DSP2_IRQ_50_51                                                                            (0x24cU)
#define CTRL_CORE_DSP2_IRQ_52_53                                                                            (0x250U)
#define CTRL_CORE_DSP2_IRQ_54_55                                                                            (0x254U)
#define CTRL_CORE_DSP2_IRQ_56_57                                                                            (0x258U)
#define CTRL_CORE_DSP2_IRQ_58_59                                                                            (0x25cU)
#define CTRL_CORE_DSP2_IRQ_60_61                                                                            (0x260U)
#define CTRL_CORE_DSP2_IRQ_62_63                                                                            (0x264U)
#define CTRL_CORE_DSP2_IRQ_64_65                                                                            (0x268U)
#define CTRL_CORE_DSP2_IRQ_66_67                                                                            (0x26cU)
#define CTRL_CORE_DSP2_IRQ_68_69                                                                            (0x270U)
#define CTRL_CORE_DSP2_IRQ_70_71                                                                            (0x274U)
#define CTRL_CORE_DSP2_IRQ_72_73                                                                            (0x278U)
#define CTRL_CORE_DSP2_IRQ_74_75                                                                            (0x27cU)
#define CTRL_CORE_DSP2_IRQ_76_77                                                                            (0x280U)
#define CTRL_CORE_DSP2_IRQ_78_79                                                                            (0x284U)
#define CTRL_CORE_DSP2_IRQ_80_81                                                                            (0x288U)
#define CTRL_CORE_DSP2_IRQ_82_83                                                                            (0x28cU)
#define CTRL_CORE_DSP2_IRQ_84_85                                                                            (0x290U)
#define CTRL_CORE_DSP2_IRQ_86_87                                                                            (0x294U)
#define CTRL_CORE_DSP2_IRQ_88_89                                                                            (0x298U)
#define CTRL_CORE_DSP2_IRQ_90_91                                                                            (0x29cU)
#define CTRL_CORE_DSP2_IRQ_92_93                                                                            (0x2a0U)
#define CTRL_CORE_DSP2_IRQ_94_95                                                                            (0x2a4U)
#define CTRL_CORE_MPU_IRQ_4_5                                                                               (0x2a8U)
#define CTRL_CORE_MPU_IRQ_8_9                                                                               (0x2acU)
#define CTRL_CORE_MPU_IRQ_10_11                                                                             (0x2b0U)
#define CTRL_CORE_MPU_IRQ_12_13                                                                             (0x2b4U)
#define CTRL_CORE_MPU_IRQ_14_15                                                                             (0x2b8U)
#define CTRL_CORE_MPU_IRQ_16_17                                                                             (0x2bcU)
#define CTRL_CORE_MPU_IRQ_18_19                                                                             (0x2c0U)
#define CTRL_CORE_MPU_IRQ_20_21                                                                             (0x2c4U)
#define CTRL_CORE_MPU_IRQ_22_23                                                                             (0x2c8U)
#define CTRL_CORE_MPU_IRQ_24_25                                                                             (0x2ccU)
#define CTRL_CORE_MPU_IRQ_26_27                                                                             (0x2d0U)
#define CTRL_CORE_MPU_IRQ_28_29                                                                             (0x2d4U)
#define CTRL_CORE_MPU_IRQ_30_31                                                                             (0x2d8U)
#define CTRL_CORE_MPU_IRQ_32_33                                                                             (0x2dcU)
#define CTRL_CORE_MPU_IRQ_34_35                                                                             (0x2e0U)
#define CTRL_CORE_MPU_IRQ_36_37                                                                             (0x2e4U)
#define CTRL_CORE_MPU_IRQ_38_39                                                                             (0x2e8U)
#define CTRL_CORE_MPU_IRQ_40_41                                                                             (0x2ecU)
#define CTRL_CORE_MPU_IRQ_42_43                                                                             (0x2f0U)
#define CTRL_CORE_MPU_IRQ_44_45                                                                             (0x2f4U)
#define CTRL_CORE_MPU_IRQ_46_47                                                                             (0x2f8U)
#define CTRL_CORE_MPU_IRQ_48_49                                                                             (0x2fcU)
#define CTRL_CORE_MPU_IRQ_50_51                                                                             (0x300U)
#define CTRL_CORE_MPU_IRQ_52_53                                                                             (0x304U)
#define CTRL_CORE_MPU_IRQ_54_55                                                                             (0x308U)
#define CTRL_CORE_MPU_IRQ_56_57                                                                             (0x30cU)
#define CTRL_CORE_MPU_IRQ_58_59                                                                             (0x310U)
#define CTRL_CORE_MPU_IRQ_60_61                                                                             (0x314U)
#define CTRL_CORE_MPU_IRQ_62_63                                                                             (0x318U)
#define CTRL_CORE_MPU_IRQ_64_65                                                                             (0x31cU)
#define CTRL_CORE_MPU_IRQ_66_67                                                                             (0x320U)
#define CTRL_CORE_MPU_IRQ_68_69                                                                             (0x324U)
#define CTRL_CORE_MPU_IRQ_70_71                                                                             (0x328U)
#define CTRL_CORE_MPU_IRQ_72_73                                                                             (0x32cU)
#define CTRL_CORE_MPU_IRQ_74_75                                                                             (0x330U)
#define CTRL_CORE_MPU_IRQ_76_77                                                                             (0x334U)
#define CTRL_CORE_MPU_IRQ_78_79                                                                             (0x338U)
#define CTRL_CORE_MPU_IRQ_80_81                                                                             (0x33cU)
#define CTRL_CORE_MPU_IRQ_82_83                                                                             (0x340U)
#define CTRL_CORE_MPU_IRQ_84_85                                                                             (0x344U)
#define CTRL_CORE_MPU_IRQ_86_87                                                                             (0x348U)
#define CTRL_CORE_MPU_IRQ_88_89                                                                             (0x34cU)
#define CTRL_CORE_MPU_IRQ_90_91                                                                             (0x350U)
#define CTRL_CORE_MPU_IRQ_92_93                                                                             (0x354U)
#define CTRL_CORE_MPU_IRQ_94_95                                                                             (0x358U)
#define CTRL_CORE_MPU_IRQ_96_97                                                                             (0x35cU)
#define CTRL_CORE_MPU_IRQ_98_99                                                                             (0x360U)
#define CTRL_CORE_MPU_IRQ_100_101                                                                           (0x364U)
#define CTRL_CORE_MPU_IRQ_102_103                                                                           (0x368U)
#define CTRL_CORE_MPU_IRQ_104_105                                                                           (0x36cU)
#define CTRL_CORE_MPU_IRQ_106_107                                                                           (0x370U)
#define CTRL_CORE_MPU_IRQ_108_109                                                                           (0x374U)
#define CTRL_CORE_MPU_IRQ_110_111                                                                           (0x378U)
#define CTRL_CORE_MPU_IRQ_112_113                                                                           (0x37cU)
#define CTRL_CORE_MPU_IRQ_114_115                                                                           (0x380U)
#define CTRL_CORE_MPU_IRQ_116_117                                                                           (0x384U)
#define CTRL_CORE_MPU_IRQ_118_119                                                                           (0x388U)
#define CTRL_CORE_MPU_IRQ_120_121                                                                           (0x38cU)
#define CTRL_CORE_MPU_IRQ_122_123                                                                           (0x390U)
#define CTRL_CORE_MPU_IRQ_124_125                                                                           (0x394U)
#define CTRL_CORE_MPU_IRQ_126_127                                                                           (0x398U)
#define CTRL_CORE_MPU_IRQ_128_129                                                                           (0x39cU)
#define CTRL_CORE_MPU_IRQ_130_131                                                                           (0x3a0U)
#define CTRL_CORE_MPU_IRQ_134_135                                                                           (0x3a4U)
#define CTRL_CORE_MPU_IRQ_136_137                                                                           (0x3a8U)
#define CTRL_CORE_MPU_IRQ_138_139                                                                           (0x3acU)
#define CTRL_CORE_MPU_IRQ_140_141                                                                           (0x3b0U)
#define CTRL_CORE_MPU_IRQ_142_143                                                                           (0x3b4U)
#define CTRL_CORE_MPU_IRQ_144_145                                                                           (0x3b8U)
#define CTRL_CORE_MPU_IRQ_146_147                                                                           (0x3bcU)
#define CTRL_CORE_MPU_IRQ_148_149                                                                           (0x3c0U)
#define CTRL_CORE_MPU_IRQ_150_151                                                                           (0x3c4U)
#define CTRL_CORE_MPU_IRQ_152_153                                                                           (0x3c8U)
#define CTRL_CORE_MPU_IRQ_154_155                                                                           (0x3ccU)
#define CTRL_CORE_MPU_IRQ_156_157                                                                           (0x3d0U)
#define CTRL_CORE_MPU_IRQ_158_159                                                                           (0x3d4U)
#define CTRL_CORE_DMA_EDMA_DREQ_0_1                                                                         (0x4d8U)
#define CTRL_CORE_DMA_EDMA_DREQ_2_3                                                                         (0x4dcU)
#define CTRL_CORE_DMA_EDMA_DREQ_4_5                                                                         (0x4e0U)
#define CTRL_CORE_DMA_EDMA_DREQ_6_7                                                                         (0x4e4U)
#define CTRL_CORE_DMA_EDMA_DREQ_8_9                                                                         (0x4e8U)
#define CTRL_CORE_DMA_EDMA_DREQ_10_11                                                                       (0x4ecU)
#define CTRL_CORE_DMA_EDMA_DREQ_12_13                                                                       (0x4f0U)
#define CTRL_CORE_DMA_EDMA_DREQ_14_15                                                                       (0x4f4U)
#define CTRL_CORE_DMA_EDMA_DREQ_16_17                                                                       (0x4f8U)
#define CTRL_CORE_DMA_EDMA_DREQ_18_19                                                                       (0x4fcU)
#define CTRL_CORE_DMA_EDMA_DREQ_20_21                                                                       (0x500U)
#define CTRL_CORE_DMA_EDMA_DREQ_22_23                                                                       (0x504U)
#define CTRL_CORE_DMA_EDMA_DREQ_24_25                                                                       (0x508U)
#define CTRL_CORE_DMA_EDMA_DREQ_26_27                                                                       (0x50cU)
#define CTRL_CORE_DMA_EDMA_DREQ_28_29                                                                       (0x510U)
#define CTRL_CORE_DMA_EDMA_DREQ_30_31                                                                       (0x514U)
#define CTRL_CORE_DMA_EDMA_DREQ_32_33                                                                       (0x518U)
#define CTRL_CORE_DMA_EDMA_DREQ_34_35                                                                       (0x51cU)
#define CTRL_CORE_DMA_EDMA_DREQ_36_37                                                                       (0x520U)
#define CTRL_CORE_DMA_EDMA_DREQ_38_39                                                                       (0x524U)
#define CTRL_CORE_DMA_EDMA_DREQ_40_41                                                                       (0x528U)
#define CTRL_CORE_DMA_EDMA_DREQ_42_43                                                                       (0x52cU)
#define CTRL_CORE_DMA_EDMA_DREQ_44_45                                                                       (0x530U)
#define CTRL_CORE_DMA_EDMA_DREQ_46_47                                                                       (0x534U)
#define CTRL_CORE_DMA_EDMA_DREQ_48_49                                                                       (0x538U)
#define CTRL_CORE_DMA_EDMA_DREQ_50_51                                                                       (0x53cU)
#define CTRL_CORE_DMA_EDMA_DREQ_52_53                                                                       (0x540U)
#define CTRL_CORE_DMA_EDMA_DREQ_54_55                                                                       (0x544U)
#define CTRL_CORE_DMA_EDMA_DREQ_56_57                                                                       (0x548U)
#define CTRL_CORE_DMA_EDMA_DREQ_58_59                                                                       (0x54cU)
#define CTRL_CORE_DMA_EDMA_DREQ_60_61                                                                       (0x550U)
#define CTRL_CORE_DMA_EDMA_DREQ_62_63                                                                       (0x554U)
#define CTRL_CORE_DMA_DSP1_DREQ_0_1                                                                         (0x558U)
#define CTRL_CORE_DMA_DSP1_DREQ_2_3                                                                         (0x55cU)
#define CTRL_CORE_DMA_DSP1_DREQ_4_5                                                                         (0x560U)
#define CTRL_CORE_DMA_DSP1_DREQ_6_7                                                                         (0x564U)
#define CTRL_CORE_DMA_DSP1_DREQ_8_9                                                                         (0x568U)
#define CTRL_CORE_DMA_DSP1_DREQ_10_11                                                                       (0x56cU)
#define CTRL_CORE_DMA_DSP1_DREQ_12_13                                                                       (0x570U)
#define CTRL_CORE_DMA_DSP1_DREQ_14_15                                                                       (0x574U)
#define CTRL_CORE_DMA_DSP1_DREQ_16_17                                                                       (0x578U)
#define CTRL_CORE_DMA_DSP1_DREQ_18_19                                                                       (0x57cU)
#define CTRL_CORE_DMA_DSP2_DREQ_0_1                                                                         (0x580U)
#define CTRL_CORE_DMA_DSP2_DREQ_2_3                                                                         (0x584U)
#define CTRL_CORE_DMA_DSP2_DREQ_4_5                                                                         (0x588U)
#define CTRL_CORE_DMA_DSP2_DREQ_6_7                                                                         (0x58cU)
#define CTRL_CORE_DMA_DSP2_DREQ_8_9                                                                         (0x590U)
#define CTRL_CORE_DMA_DSP2_DREQ_10_11                                                                       (0x594U)
#define CTRL_CORE_DMA_DSP2_DREQ_12_13                                                                       (0x598U)
#define CTRL_CORE_DMA_DSP2_DREQ_14_15                                                                       (0x59cU)
#define CTRL_CORE_DMA_DSP2_DREQ_16_17                                                                       (0x5a0U)
#define CTRL_CORE_DMA_DSP2_DREQ_18_19                                                                       (0x5a4U)
#define CTRL_CORE_OVS_DMARQ_IO_MUX                                                                          (0x5acU)
#define CTRL_CORE_OVS_IRQ_IO_MUX                                                                            (0x5b0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_EVE1_IRQ_0_1_EVE1_IRQ_0_SHIFT                                                            (0U)
#define CTRL_CORE_EVE1_IRQ_0_1_EVE1_IRQ_0_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE1_IRQ_0_1_EVE1_IRQ_1_SHIFT                                                            (16U)
#define CTRL_CORE_EVE1_IRQ_0_1_EVE1_IRQ_1_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE1_IRQ_0_1_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE1_IRQ_0_1_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE1_IRQ_0_1_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE1_IRQ_0_1_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE1_IRQ_2_3_EVE1_IRQ_2_SHIFT                                                            (0U)
#define CTRL_CORE_EVE1_IRQ_2_3_EVE1_IRQ_2_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE1_IRQ_2_3_EVE1_IRQ_3_SHIFT                                                            (16U)
#define CTRL_CORE_EVE1_IRQ_2_3_EVE1_IRQ_3_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE1_IRQ_2_3_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE1_IRQ_2_3_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE1_IRQ_2_3_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE1_IRQ_2_3_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE1_IRQ_4_5_EVE1_IRQ_4_SHIFT                                                            (0U)
#define CTRL_CORE_EVE1_IRQ_4_5_EVE1_IRQ_4_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE1_IRQ_4_5_EVE1_IRQ_5_SHIFT                                                            (16U)
#define CTRL_CORE_EVE1_IRQ_4_5_EVE1_IRQ_5_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE1_IRQ_4_5_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE1_IRQ_4_5_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE1_IRQ_4_5_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE1_IRQ_4_5_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE1_IRQ_6_7_EVE1_IRQ_6_SHIFT                                                            (0U)
#define CTRL_CORE_EVE1_IRQ_6_7_EVE1_IRQ_6_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE1_IRQ_6_7_EVE1_IRQ_7_SHIFT                                                            (16U)
#define CTRL_CORE_EVE1_IRQ_6_7_EVE1_IRQ_7_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE1_IRQ_6_7_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE1_IRQ_6_7_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE1_IRQ_6_7_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE1_IRQ_6_7_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE2_IRQ_0_1_EVE2_IRQ_0_SHIFT                                                            (0U)
#define CTRL_CORE_EVE2_IRQ_0_1_EVE2_IRQ_0_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE2_IRQ_0_1_EVE2_IRQ_1_SHIFT                                                            (16U)
#define CTRL_CORE_EVE2_IRQ_0_1_EVE2_IRQ_1_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE2_IRQ_0_1_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE2_IRQ_0_1_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE2_IRQ_0_1_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE2_IRQ_0_1_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE2_IRQ_2_3_EVE2_IRQ_2_SHIFT                                                            (0U)
#define CTRL_CORE_EVE2_IRQ_2_3_EVE2_IRQ_2_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE2_IRQ_2_3_EVE2_IRQ_3_SHIFT                                                            (16U)
#define CTRL_CORE_EVE2_IRQ_2_3_EVE2_IRQ_3_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE2_IRQ_2_3_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE2_IRQ_2_3_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE2_IRQ_2_3_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE2_IRQ_2_3_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE2_IRQ_4_5_EVE2_IRQ_4_SHIFT                                                            (0U)
#define CTRL_CORE_EVE2_IRQ_4_5_EVE2_IRQ_4_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE2_IRQ_4_5_EVE2_IRQ_5_SHIFT                                                            (16U)
#define CTRL_CORE_EVE2_IRQ_4_5_EVE2_IRQ_5_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE2_IRQ_4_5_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE2_IRQ_4_5_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE2_IRQ_4_5_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE2_IRQ_4_5_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE2_IRQ_6_7_EVE2_IRQ_6_SHIFT                                                            (0U)
#define CTRL_CORE_EVE2_IRQ_6_7_EVE2_IRQ_6_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE2_IRQ_6_7_EVE2_IRQ_7_SHIFT                                                            (16U)
#define CTRL_CORE_EVE2_IRQ_6_7_EVE2_IRQ_7_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE2_IRQ_6_7_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE2_IRQ_6_7_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE2_IRQ_6_7_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE2_IRQ_6_7_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE3_IRQ_0_1_EVE3_IRQ_0_SHIFT                                                            (0U)
#define CTRL_CORE_EVE3_IRQ_0_1_EVE3_IRQ_0_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE3_IRQ_0_1_EVE3_IRQ_1_SHIFT                                                            (16U)
#define CTRL_CORE_EVE3_IRQ_0_1_EVE3_IRQ_1_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE3_IRQ_0_1_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE3_IRQ_0_1_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE3_IRQ_0_1_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE3_IRQ_0_1_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE3_IRQ_2_3_EVE3_IRQ_2_SHIFT                                                            (0U)
#define CTRL_CORE_EVE3_IRQ_2_3_EVE3_IRQ_2_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE3_IRQ_2_3_EVE3_IRQ_3_SHIFT                                                            (16U)
#define CTRL_CORE_EVE3_IRQ_2_3_EVE3_IRQ_3_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE3_IRQ_2_3_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE3_IRQ_2_3_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE3_IRQ_2_3_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE3_IRQ_2_3_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE3_IRQ_4_5_EVE3_IRQ_4_SHIFT                                                            (0U)
#define CTRL_CORE_EVE3_IRQ_4_5_EVE3_IRQ_4_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE3_IRQ_4_5_EVE3_IRQ_5_SHIFT                                                            (16U)
#define CTRL_CORE_EVE3_IRQ_4_5_EVE3_IRQ_5_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE3_IRQ_4_5_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE3_IRQ_4_5_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE3_IRQ_4_5_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE3_IRQ_4_5_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE3_IRQ_6_7_EVE3_IRQ_6_SHIFT                                                            (0U)
#define CTRL_CORE_EVE3_IRQ_6_7_EVE3_IRQ_6_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE3_IRQ_6_7_EVE3_IRQ_7_SHIFT                                                            (16U)
#define CTRL_CORE_EVE3_IRQ_6_7_EVE3_IRQ_7_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE3_IRQ_6_7_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE3_IRQ_6_7_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE3_IRQ_6_7_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE3_IRQ_6_7_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE4_IRQ_0_1_EVE4_IRQ_0_SHIFT                                                            (0U)
#define CTRL_CORE_EVE4_IRQ_0_1_EVE4_IRQ_0_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE4_IRQ_0_1_EVE4_IRQ_1_SHIFT                                                            (16U)
#define CTRL_CORE_EVE4_IRQ_0_1_EVE4_IRQ_1_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE4_IRQ_0_1_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE4_IRQ_0_1_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE4_IRQ_0_1_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE4_IRQ_0_1_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE4_IRQ_2_3_EVE4_IRQ_2_SHIFT                                                            (0U)
#define CTRL_CORE_EVE4_IRQ_2_3_EVE4_IRQ_2_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE4_IRQ_2_3_EVE4_IRQ_3_SHIFT                                                            (16U)
#define CTRL_CORE_EVE4_IRQ_2_3_EVE4_IRQ_3_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE4_IRQ_2_3_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE4_IRQ_2_3_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE4_IRQ_2_3_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE4_IRQ_2_3_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE4_IRQ_4_5_EVE4_IRQ_4_SHIFT                                                            (0U)
#define CTRL_CORE_EVE4_IRQ_4_5_EVE4_IRQ_4_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE4_IRQ_4_5_EVE4_IRQ_5_SHIFT                                                            (16U)
#define CTRL_CORE_EVE4_IRQ_4_5_EVE4_IRQ_5_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE4_IRQ_4_5_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE4_IRQ_4_5_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE4_IRQ_4_5_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE4_IRQ_4_5_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_EVE4_IRQ_6_7_EVE4_IRQ_6_SHIFT                                                            (0U)
#define CTRL_CORE_EVE4_IRQ_6_7_EVE4_IRQ_6_MASK                                                             (0x000001ffU)

#define CTRL_CORE_EVE4_IRQ_6_7_EVE4_IRQ_7_SHIFT                                                            (16U)
#define CTRL_CORE_EVE4_IRQ_6_7_EVE4_IRQ_7_MASK                                                             (0x01ff0000U)

#define CTRL_CORE_EVE4_IRQ_6_7_RESERVED_0_SHIFT                                                            (9U)
#define CTRL_CORE_EVE4_IRQ_6_7_RESERVED_0_MASK                                                             (0x0000fe00U)

#define CTRL_CORE_EVE4_IRQ_6_7_RESERVED_1_SHIFT                                                            (25U)
#define CTRL_CORE_EVE4_IRQ_6_7_RESERVED_1_MASK                                                             (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_23_24_IPU1_IRQ_23_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_23_24_IPU1_IRQ_23_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_23_24_IPU1_IRQ_24_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_23_24_IPU1_IRQ_24_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_23_24_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_23_24_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_23_24_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_23_24_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_25_26_IPU1_IRQ_25_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_25_26_IPU1_IRQ_25_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_25_26_IPU1_IRQ_26_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_25_26_IPU1_IRQ_26_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_25_26_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_25_26_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_25_26_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_25_26_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_27_28_IPU1_IRQ_27_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_27_28_IPU1_IRQ_27_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_27_28_IPU1_IRQ_28_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_27_28_IPU1_IRQ_28_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_27_28_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_27_28_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_27_28_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_27_28_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_29_30_IPU1_IRQ_29_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_29_30_IPU1_IRQ_29_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_29_30_IPU1_IRQ_30_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_29_30_IPU1_IRQ_30_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_29_30_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_29_30_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_29_30_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_29_30_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_31_32_IPU1_IRQ_31_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_31_32_IPU1_IRQ_31_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_31_32_IPU1_IRQ_32_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_31_32_IPU1_IRQ_32_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_31_32_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_31_32_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_31_32_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_31_32_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_33_34_IPU1_IRQ_33_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_33_34_IPU1_IRQ_33_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_33_34_IPU1_IRQ_34_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_33_34_IPU1_IRQ_34_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_33_34_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_33_34_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_33_34_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_33_34_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_35_36_IPU1_IRQ_35_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_35_36_IPU1_IRQ_35_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_35_36_IPU1_IRQ_36_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_35_36_IPU1_IRQ_36_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_35_36_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_35_36_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_35_36_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_35_36_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_37_38_IPU1_IRQ_37_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_37_38_IPU1_IRQ_37_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_37_38_IPU1_IRQ_38_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_37_38_IPU1_IRQ_38_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_37_38_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_37_38_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_37_38_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_37_38_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_39_40_IPU1_IRQ_39_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_39_40_IPU1_IRQ_39_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_39_40_IPU1_IRQ_40_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_39_40_IPU1_IRQ_40_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_39_40_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_39_40_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_39_40_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_39_40_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_41_42_IPU1_IRQ_41_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_41_42_IPU1_IRQ_41_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_41_42_IPU1_IRQ_42_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_41_42_IPU1_IRQ_42_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_41_42_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_41_42_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_41_42_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_41_42_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_43_44_IPU1_IRQ_43_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_43_44_IPU1_IRQ_43_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_43_44_IPU1_IRQ_44_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_43_44_IPU1_IRQ_44_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_43_44_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_43_44_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_43_44_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_43_44_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_45_46_IPU1_IRQ_45_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_45_46_IPU1_IRQ_45_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_45_46_IPU1_IRQ_46_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_45_46_IPU1_IRQ_46_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_45_46_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_45_46_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_45_46_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_45_46_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_47_48_IPU1_IRQ_47_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_47_48_IPU1_IRQ_47_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_47_48_IPU1_IRQ_48_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_47_48_IPU1_IRQ_48_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_47_48_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_47_48_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_47_48_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_47_48_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_49_50_IPU1_IRQ_49_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_49_50_IPU1_IRQ_49_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_49_50_IPU1_IRQ_50_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_49_50_IPU1_IRQ_50_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_49_50_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_49_50_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_49_50_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_49_50_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_51_52_IPU1_IRQ_51_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_51_52_IPU1_IRQ_51_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_51_52_IPU1_IRQ_52_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_51_52_IPU1_IRQ_52_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_51_52_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_51_52_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_51_52_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_51_52_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_53_54_IPU1_IRQ_53_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_53_54_IPU1_IRQ_53_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_53_54_IPU1_IRQ_54_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_53_54_IPU1_IRQ_54_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_53_54_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_53_54_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_53_54_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_53_54_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_55_56_IPU1_IRQ_55_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_55_56_IPU1_IRQ_55_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_55_56_IPU1_IRQ_56_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_55_56_IPU1_IRQ_56_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_55_56_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_55_56_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_55_56_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_55_56_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_57_58_IPU1_IRQ_57_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_57_58_IPU1_IRQ_57_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_57_58_IPU1_IRQ_58_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_57_58_IPU1_IRQ_58_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_57_58_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_57_58_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_57_58_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_57_58_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_59_60_IPU1_IRQ_59_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_59_60_IPU1_IRQ_59_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_59_60_IPU1_IRQ_60_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_59_60_IPU1_IRQ_60_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_59_60_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_59_60_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_59_60_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_59_60_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_61_62_IPU1_IRQ_61_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_61_62_IPU1_IRQ_61_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_61_62_IPU1_IRQ_62_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_61_62_IPU1_IRQ_62_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_61_62_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_61_62_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_61_62_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_61_62_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_63_64_IPU1_IRQ_63_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_63_64_IPU1_IRQ_63_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_63_64_IPU1_IRQ_64_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_63_64_IPU1_IRQ_64_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_63_64_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_63_64_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_63_64_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_63_64_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_65_66_IPU1_IRQ_65_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_65_66_IPU1_IRQ_65_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_65_66_IPU1_IRQ_66_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_65_66_IPU1_IRQ_66_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_65_66_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_65_66_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_65_66_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_65_66_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_67_68_IPU1_IRQ_67_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_67_68_IPU1_IRQ_67_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_67_68_IPU1_IRQ_68_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_67_68_IPU1_IRQ_68_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_67_68_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_67_68_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_67_68_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_67_68_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_69_70_IPU1_IRQ_69_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_69_70_IPU1_IRQ_69_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_69_70_IPU1_IRQ_70_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_69_70_IPU1_IRQ_70_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_69_70_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_69_70_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_69_70_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_69_70_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_71_72_IPU1_IRQ_71_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_71_72_IPU1_IRQ_71_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_71_72_IPU1_IRQ_72_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_71_72_IPU1_IRQ_72_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_71_72_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_71_72_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_71_72_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_71_72_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_73_74_IPU1_IRQ_73_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_73_74_IPU1_IRQ_73_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_73_74_IPU1_IRQ_74_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_73_74_IPU1_IRQ_74_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_73_74_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_73_74_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_73_74_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_73_74_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_75_76_IPU1_IRQ_75_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_75_76_IPU1_IRQ_75_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_75_76_IPU1_IRQ_76_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_75_76_IPU1_IRQ_76_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_75_76_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_75_76_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_75_76_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_75_76_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_77_78_IPU1_IRQ_77_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_77_78_IPU1_IRQ_77_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_77_78_IPU1_IRQ_78_SHIFT                                                         (16U)
#define CTRL_CORE_IPU1_IRQ_77_78_IPU1_IRQ_78_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU1_IRQ_77_78_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_77_78_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU1_IRQ_77_78_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU1_IRQ_77_78_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU1_IRQ_79_80_IPU1_IRQ_79_SHIFT                                                         (0U)
#define CTRL_CORE_IPU1_IRQ_79_80_IPU1_IRQ_79_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU1_IRQ_79_80_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU1_IRQ_79_80_RESERVED_0_MASK                                                           (0xfffffe00U)

#define CTRL_CORE_IPU2_IRQ_23_24_IPU2_IRQ_23_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_23_24_IPU2_IRQ_23_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_23_24_IPU2_IRQ_24_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_23_24_IPU2_IRQ_24_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_23_24_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_23_24_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_23_24_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_23_24_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_25_26_IPU2_IRQ_25_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_25_26_IPU2_IRQ_25_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_25_26_IPU2_IRQ_26_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_25_26_IPU2_IRQ_26_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_25_26_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_25_26_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_25_26_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_25_26_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_27_28_IPU2_IRQ_27_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_27_28_IPU2_IRQ_27_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_27_28_IPU2_IRQ_28_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_27_28_IPU2_IRQ_28_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_27_28_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_27_28_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_27_28_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_27_28_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_29_30_IPU2_IRQ_29_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_29_30_IPU2_IRQ_29_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_29_30_IPU2_IRQ_30_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_29_30_IPU2_IRQ_30_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_29_30_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_29_30_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_29_30_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_29_30_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_31_32_IPU2_IRQ_31_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_31_32_IPU2_IRQ_31_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_31_32_IPU2_IRQ_32_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_31_32_IPU2_IRQ_32_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_31_32_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_31_32_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_31_32_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_31_32_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_33_34_IPU2_IRQ_33_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_33_34_IPU2_IRQ_33_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_33_34_IPU2_IRQ_34_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_33_34_IPU2_IRQ_34_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_33_34_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_33_34_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_33_34_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_33_34_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_35_36_IPU2_IRQ_35_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_35_36_IPU2_IRQ_35_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_35_36_IPU2_IRQ_36_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_35_36_IPU2_IRQ_36_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_35_36_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_35_36_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_35_36_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_35_36_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_37_38_IPU2_IRQ_37_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_37_38_IPU2_IRQ_37_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_37_38_IPU2_IRQ_38_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_37_38_IPU2_IRQ_38_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_37_38_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_37_38_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_37_38_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_37_38_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_39_40_IPU2_IRQ_39_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_39_40_IPU2_IRQ_39_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_39_40_IPU2_IRQ_40_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_39_40_IPU2_IRQ_40_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_39_40_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_39_40_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_39_40_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_39_40_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_41_42_IPU2_IRQ_41_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_41_42_IPU2_IRQ_41_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_41_42_IPU2_IRQ_42_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_41_42_IPU2_IRQ_42_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_41_42_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_41_42_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_41_42_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_41_42_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_43_44_IPU2_IRQ_43_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_43_44_IPU2_IRQ_43_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_43_44_IPU2_IRQ_44_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_43_44_IPU2_IRQ_44_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_43_44_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_43_44_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_43_44_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_43_44_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_45_46_IPU2_IRQ_45_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_45_46_IPU2_IRQ_45_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_45_46_IPU2_IRQ_46_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_45_46_IPU2_IRQ_46_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_45_46_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_45_46_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_45_46_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_45_46_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_47_48_IPU2_IRQ_47_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_47_48_IPU2_IRQ_47_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_47_48_IPU2_IRQ_48_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_47_48_IPU2_IRQ_48_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_47_48_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_47_48_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_47_48_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_47_48_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_50_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_50_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_49_50_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_49_50_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_49_50_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_49_50_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_51_52_IPU2_IRQ_51_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_51_52_IPU2_IRQ_51_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_51_52_IPU2_IRQ_52_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_51_52_IPU2_IRQ_52_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_51_52_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_51_52_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_51_52_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_51_52_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_53_54_IPU2_IRQ_53_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_53_54_IPU2_IRQ_53_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_53_54_IPU2_IRQ_54_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_53_54_IPU2_IRQ_54_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_53_54_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_53_54_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_53_54_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_53_54_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_55_56_IPU2_IRQ_55_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_55_56_IPU2_IRQ_55_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_55_56_IPU2_IRQ_56_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_55_56_IPU2_IRQ_56_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_55_56_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_55_56_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_55_56_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_55_56_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_57_58_IPU2_IRQ_57_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_57_58_IPU2_IRQ_57_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_57_58_IPU2_IRQ_58_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_57_58_IPU2_IRQ_58_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_57_58_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_57_58_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_57_58_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_57_58_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_59_60_IPU2_IRQ_59_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_59_60_IPU2_IRQ_59_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_59_60_IPU2_IRQ_60_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_59_60_IPU2_IRQ_60_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_59_60_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_59_60_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_59_60_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_59_60_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_61_62_IPU2_IRQ_61_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_61_62_IPU2_IRQ_61_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_61_62_IPU2_IRQ_62_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_61_62_IPU2_IRQ_62_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_61_62_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_61_62_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_61_62_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_61_62_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_63_64_IPU2_IRQ_63_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_63_64_IPU2_IRQ_63_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_63_64_IPU2_IRQ_64_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_63_64_IPU2_IRQ_64_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_63_64_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_63_64_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_63_64_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_63_64_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_65_66_IPU2_IRQ_65_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_65_66_IPU2_IRQ_65_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_65_66_IPU2_IRQ_66_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_65_66_IPU2_IRQ_66_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_65_66_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_65_66_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_65_66_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_65_66_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_67_68_IPU2_IRQ_67_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_67_68_IPU2_IRQ_67_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_67_68_IPU2_IRQ_68_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_67_68_IPU2_IRQ_68_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_67_68_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_67_68_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_67_68_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_67_68_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_69_70_IPU2_IRQ_69_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_69_70_IPU2_IRQ_69_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_69_70_IPU2_IRQ_70_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_69_70_IPU2_IRQ_70_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_69_70_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_69_70_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_69_70_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_69_70_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_71_72_IPU2_IRQ_71_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_71_72_IPU2_IRQ_71_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_71_72_IPU2_IRQ_72_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_71_72_IPU2_IRQ_72_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_71_72_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_71_72_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_71_72_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_71_72_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_73_74_IPU2_IRQ_73_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_73_74_IPU2_IRQ_73_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_73_74_IPU2_IRQ_74_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_73_74_IPU2_IRQ_74_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_73_74_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_73_74_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_73_74_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_73_74_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_75_76_IPU2_IRQ_75_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_75_76_IPU2_IRQ_75_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_75_76_IPU2_IRQ_76_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_75_76_IPU2_IRQ_76_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_75_76_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_75_76_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_75_76_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_75_76_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_77_78_IPU2_IRQ_77_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_77_78_IPU2_IRQ_77_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_77_78_IPU2_IRQ_78_SHIFT                                                         (16U)
#define CTRL_CORE_IPU2_IRQ_77_78_IPU2_IRQ_78_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_IPU2_IRQ_77_78_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_77_78_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_IPU2_IRQ_77_78_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_IPU2_IRQ_77_78_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_IPU2_IRQ_79_80_IPU2_IRQ_79_SHIFT                                                         (0U)
#define CTRL_CORE_IPU2_IRQ_79_80_IPU2_IRQ_79_MASK                                                          (0x000001ffU)

#define CTRL_CORE_IPU2_IRQ_79_80_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_IPU2_IRQ_79_80_RESERVED_0_MASK                                                           (0xfffffe00U)


#define CTRL_CORE_PRUSS1_IRQ_32_33_PRUSS1_IRQ_32_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_32_33_PRUSS1_IRQ_32_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_32_33_PRUSS1_IRQ_33_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_32_33_PRUSS1_IRQ_33_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_32_33_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_32_33_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_32_33_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_32_33_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_34_35_PRUSS1_IRQ_34_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_34_35_PRUSS1_IRQ_34_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_34_35_PRUSS1_IRQ_35_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_34_35_PRUSS1_IRQ_35_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_34_35_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_34_35_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_34_35_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_34_35_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_36_37_PRUSS1_IRQ_36_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_36_37_PRUSS1_IRQ_36_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_36_37_PRUSS1_IRQ_37_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_36_37_PRUSS1_IRQ_37_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_36_37_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_36_37_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_36_37_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_36_37_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_38_39_PRUSS1_IRQ_38_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_38_39_PRUSS1_IRQ_38_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_38_39_PRUSS1_IRQ_39_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_38_39_PRUSS1_IRQ_39_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_38_39_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_38_39_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_38_39_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_38_39_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_40_41_PRUSS1_IRQ_40_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_40_41_PRUSS1_IRQ_40_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_40_41_PRUSS1_IRQ_41_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_40_41_PRUSS1_IRQ_41_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_40_41_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_40_41_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_40_41_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_40_41_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_42_43_PRUSS1_IRQ_42_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_42_43_PRUSS1_IRQ_42_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_42_43_PRUSS1_IRQ_43_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_42_43_PRUSS1_IRQ_43_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_42_43_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_42_43_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_42_43_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_42_43_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_44_45_PRUSS1_IRQ_44_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_44_45_PRUSS1_IRQ_44_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_44_45_PRUSS1_IRQ_45_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_44_45_PRUSS1_IRQ_45_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_44_45_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_44_45_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_44_45_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_44_45_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_46_47_PRUSS1_IRQ_46_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_46_47_PRUSS1_IRQ_46_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_46_47_PRUSS1_IRQ_47_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_46_47_PRUSS1_IRQ_47_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_46_47_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_46_47_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_46_47_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_46_47_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_48_49_PRUSS1_IRQ_48_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_48_49_PRUSS1_IRQ_48_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_48_49_PRUSS1_IRQ_49_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_48_49_PRUSS1_IRQ_49_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_48_49_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_48_49_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_48_49_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_48_49_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_50_51_PRUSS1_IRQ_50_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_50_51_PRUSS1_IRQ_50_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_50_51_PRUSS1_IRQ_51_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_50_51_PRUSS1_IRQ_51_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_50_51_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_50_51_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_50_51_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_50_51_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_52_53_PRUSS1_IRQ_52_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_52_53_PRUSS1_IRQ_52_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_52_53_PRUSS1_IRQ_53_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_52_53_PRUSS1_IRQ_53_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_52_53_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_52_53_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_52_53_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_52_53_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_54_55_PRUSS1_IRQ_54_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_54_55_PRUSS1_IRQ_54_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_54_55_PRUSS1_IRQ_55_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_54_55_PRUSS1_IRQ_55_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_54_55_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_54_55_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_54_55_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_54_55_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_56_57_PRUSS1_IRQ_56_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_56_57_PRUSS1_IRQ_56_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_56_57_PRUSS1_IRQ_57_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_56_57_PRUSS1_IRQ_57_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_56_57_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_56_57_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_56_57_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_56_57_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_58_59_PRUSS1_IRQ_58_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_58_59_PRUSS1_IRQ_58_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_58_59_PRUSS1_IRQ_59_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_58_59_PRUSS1_IRQ_59_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_58_59_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_58_59_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_58_59_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_58_59_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_60_61_PRUSS1_IRQ_60_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_60_61_PRUSS1_IRQ_60_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_60_61_PRUSS1_IRQ_61_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_60_61_PRUSS1_IRQ_61_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_60_61_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_60_61_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_60_61_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_60_61_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_PRUSS1_IRQ_62_63_PRUSS1_IRQ_62_SHIFT                                                     (0U)
#define CTRL_CORE_PRUSS1_IRQ_62_63_PRUSS1_IRQ_62_MASK                                                      (0x000001ffU)

#define CTRL_CORE_PRUSS1_IRQ_62_63_PRUSS1_IRQ_63_SHIFT                                                     (16U)
#define CTRL_CORE_PRUSS1_IRQ_62_63_PRUSS1_IRQ_63_MASK                                                      (0x01ff0000U)

#define CTRL_CORE_PRUSS1_IRQ_62_63_RESERVED_0_SHIFT                                                        (9U)
#define CTRL_CORE_PRUSS1_IRQ_62_63_RESERVED_0_MASK                                                         (0x0000fe00U)

#define CTRL_CORE_PRUSS1_IRQ_62_63_RESERVED_1_SHIFT                                                        (25U)
#define CTRL_CORE_PRUSS1_IRQ_62_63_RESERVED_1_MASK                                                         (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_32_33_DSP1_IRQ_32_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_32_33_DSP1_IRQ_32_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_32_33_DSP1_IRQ_33_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_32_33_DSP1_IRQ_33_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_32_33_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_32_33_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_32_33_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_32_33_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_34_35_DSP1_IRQ_34_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_34_35_DSP1_IRQ_34_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_34_35_DSP1_IRQ_35_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_34_35_DSP1_IRQ_35_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_34_35_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_34_35_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_34_35_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_34_35_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_36_37_DSP1_IRQ_36_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_36_37_DSP1_IRQ_36_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_36_37_DSP1_IRQ_37_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_36_37_DSP1_IRQ_37_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_36_37_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_36_37_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_36_37_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_36_37_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_38_39_DSP1_IRQ_38_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_38_39_DSP1_IRQ_38_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_38_39_DSP1_IRQ_39_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_38_39_DSP1_IRQ_39_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_38_39_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_38_39_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_38_39_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_38_39_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_40_41_DSP1_IRQ_40_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_40_41_DSP1_IRQ_40_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_40_41_DSP1_IRQ_41_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_40_41_DSP1_IRQ_41_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_40_41_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_40_41_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_40_41_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_40_41_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_42_43_DSP1_IRQ_42_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_42_43_DSP1_IRQ_42_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_42_43_DSP1_IRQ_43_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_42_43_DSP1_IRQ_43_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_42_43_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_42_43_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_42_43_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_42_43_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_44_45_DSP1_IRQ_44_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_44_45_DSP1_IRQ_44_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_44_45_DSP1_IRQ_45_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_44_45_DSP1_IRQ_45_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_44_45_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_44_45_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_44_45_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_44_45_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_46_47_DSP1_IRQ_46_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_46_47_DSP1_IRQ_46_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_46_47_DSP1_IRQ_47_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_46_47_DSP1_IRQ_47_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_46_47_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_46_47_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_46_47_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_46_47_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_48_49_DSP1_IRQ_48_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_48_49_DSP1_IRQ_48_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_48_49_DSP1_IRQ_49_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_48_49_DSP1_IRQ_49_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_48_49_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_48_49_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_48_49_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_48_49_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_50_51_DSP1_IRQ_50_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_50_51_DSP1_IRQ_50_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_50_51_DSP1_IRQ_51_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_50_51_DSP1_IRQ_51_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_50_51_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_50_51_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_50_51_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_50_51_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_52_53_DSP1_IRQ_52_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_52_53_DSP1_IRQ_52_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_52_53_DSP1_IRQ_53_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_52_53_DSP1_IRQ_53_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_52_53_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_52_53_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_52_53_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_52_53_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_54_55_DSP1_IRQ_54_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_54_55_DSP1_IRQ_54_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_54_55_DSP1_IRQ_55_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_54_55_DSP1_IRQ_55_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_54_55_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_54_55_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_54_55_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_54_55_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_56_57_DSP1_IRQ_56_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_56_57_DSP1_IRQ_56_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_56_57_DSP1_IRQ_57_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_56_57_DSP1_IRQ_57_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_56_57_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_56_57_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_56_57_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_56_57_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_58_59_DSP1_IRQ_58_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_58_59_DSP1_IRQ_58_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_58_59_DSP1_IRQ_59_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_58_59_DSP1_IRQ_59_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_58_59_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_58_59_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_58_59_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_58_59_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_60_61_DSP1_IRQ_60_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_60_61_DSP1_IRQ_60_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_60_61_DSP1_IRQ_61_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_60_61_DSP1_IRQ_61_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_60_61_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_60_61_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_60_61_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_60_61_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_62_63_DSP1_IRQ_62_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_62_63_DSP1_IRQ_62_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_62_63_DSP1_IRQ_63_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_62_63_DSP1_IRQ_63_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_62_63_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_62_63_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_62_63_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_62_63_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_64_65_DSP1_IRQ_64_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_64_65_DSP1_IRQ_64_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_64_65_DSP1_IRQ_65_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_64_65_DSP1_IRQ_65_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_64_65_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_64_65_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_64_65_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_64_65_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_66_67_DSP1_IRQ_66_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_66_67_DSP1_IRQ_66_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_66_67_DSP1_IRQ_67_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_66_67_DSP1_IRQ_67_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_66_67_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_66_67_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_66_67_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_66_67_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_68_69_DSP1_IRQ_68_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_68_69_DSP1_IRQ_68_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_68_69_DSP1_IRQ_69_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_68_69_DSP1_IRQ_69_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_68_69_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_68_69_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_68_69_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_68_69_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_70_71_DSP1_IRQ_70_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_70_71_DSP1_IRQ_70_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_70_71_DSP1_IRQ_71_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_70_71_DSP1_IRQ_71_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_70_71_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_70_71_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_70_71_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_70_71_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_72_73_DSP1_IRQ_72_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_72_73_DSP1_IRQ_72_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_72_73_DSP1_IRQ_73_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_72_73_DSP1_IRQ_73_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_72_73_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_72_73_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_72_73_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_72_73_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_74_75_DSP1_IRQ_74_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_74_75_DSP1_IRQ_74_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_74_75_DSP1_IRQ_75_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_74_75_DSP1_IRQ_75_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_74_75_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_74_75_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_74_75_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_74_75_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_76_77_DSP1_IRQ_76_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_76_77_DSP1_IRQ_76_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_76_77_DSP1_IRQ_77_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_76_77_DSP1_IRQ_77_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_76_77_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_76_77_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_76_77_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_76_77_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_78_79_DSP1_IRQ_78_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_78_79_DSP1_IRQ_78_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_78_79_DSP1_IRQ_79_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_78_79_DSP1_IRQ_79_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_78_79_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_78_79_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_78_79_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_78_79_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_80_81_DSP1_IRQ_80_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_80_81_DSP1_IRQ_80_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_80_81_DSP1_IRQ_81_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_80_81_DSP1_IRQ_81_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_80_81_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_80_81_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_80_81_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_80_81_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_82_83_DSP1_IRQ_82_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_82_83_DSP1_IRQ_82_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_82_83_DSP1_IRQ_83_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_82_83_DSP1_IRQ_83_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_82_83_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_82_83_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_82_83_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_82_83_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_84_85_DSP1_IRQ_84_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_84_85_DSP1_IRQ_84_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_84_85_DSP1_IRQ_85_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_84_85_DSP1_IRQ_85_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_84_85_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_84_85_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_84_85_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_84_85_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_86_87_DSP1_IRQ_86_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_86_87_DSP1_IRQ_86_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_86_87_DSP1_IRQ_87_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_86_87_DSP1_IRQ_87_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_86_87_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_86_87_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_86_87_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_86_87_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_88_89_DSP1_IRQ_88_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_88_89_DSP1_IRQ_88_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_88_89_DSP1_IRQ_89_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_88_89_DSP1_IRQ_89_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_88_89_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_88_89_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_88_89_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_88_89_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_90_91_DSP1_IRQ_90_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_90_91_DSP1_IRQ_90_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_90_91_DSP1_IRQ_91_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_90_91_DSP1_IRQ_91_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_90_91_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_90_91_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_90_91_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_90_91_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_92_93_DSP1_IRQ_92_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_92_93_DSP1_IRQ_92_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_92_93_DSP1_IRQ_93_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_92_93_DSP1_IRQ_93_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_92_93_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_92_93_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_92_93_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_92_93_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP1_IRQ_94_95_DSP1_IRQ_94_SHIFT                                                         (0U)
#define CTRL_CORE_DSP1_IRQ_94_95_DSP1_IRQ_94_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP1_IRQ_94_95_DSP1_IRQ_95_SHIFT                                                         (16U)
#define CTRL_CORE_DSP1_IRQ_94_95_DSP1_IRQ_95_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP1_IRQ_94_95_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP1_IRQ_94_95_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP1_IRQ_94_95_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP1_IRQ_94_95_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_32_33_DSP2_IRQ_32_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_32_33_DSP2_IRQ_32_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_32_33_DSP2_IRQ_33_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_32_33_DSP2_IRQ_33_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_32_33_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_32_33_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_32_33_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_32_33_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_34_35_DSP2_IRQ_34_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_34_35_DSP2_IRQ_34_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_34_35_DSP2_IRQ_35_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_34_35_DSP2_IRQ_35_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_34_35_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_34_35_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_34_35_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_34_35_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_36_37_DSP2_IRQ_36_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_36_37_DSP2_IRQ_36_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_36_37_DSP2_IRQ_37_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_36_37_DSP2_IRQ_37_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_36_37_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_36_37_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_36_37_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_36_37_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_38_39_DSP2_IRQ_38_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_38_39_DSP2_IRQ_38_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_38_39_DSP2_IRQ_39_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_38_39_DSP2_IRQ_39_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_38_39_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_38_39_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_38_39_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_38_39_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_40_41_DSP2_IRQ_40_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_40_41_DSP2_IRQ_40_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_40_41_DSP2_IRQ_41_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_40_41_DSP2_IRQ_41_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_40_41_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_40_41_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_40_41_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_40_41_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_42_43_DSP2_IRQ_42_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_42_43_DSP2_IRQ_42_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_42_43_DSP2_IRQ_43_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_42_43_DSP2_IRQ_43_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_42_43_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_42_43_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_42_43_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_42_43_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_44_45_DSP2_IRQ_44_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_44_45_DSP2_IRQ_44_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_44_45_DSP2_IRQ_45_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_44_45_DSP2_IRQ_45_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_44_45_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_44_45_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_44_45_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_44_45_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_46_47_DSP2_IRQ_46_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_46_47_DSP2_IRQ_46_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_46_47_DSP2_IRQ_47_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_46_47_DSP2_IRQ_47_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_46_47_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_46_47_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_46_47_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_46_47_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_48_49_DSP2_IRQ_48_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_48_49_DSP2_IRQ_48_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_48_49_DSP2_IRQ_49_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_48_49_DSP2_IRQ_49_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_48_49_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_48_49_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_48_49_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_48_49_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_50_51_DSP2_IRQ_50_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_50_51_DSP2_IRQ_50_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_50_51_DSP2_IRQ_51_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_50_51_DSP2_IRQ_51_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_50_51_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_50_51_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_50_51_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_50_51_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_52_53_DSP2_IRQ_52_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_52_53_DSP2_IRQ_52_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_52_53_DSP2_IRQ_53_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_52_53_DSP2_IRQ_53_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_52_53_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_52_53_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_52_53_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_52_53_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_54_55_DSP2_IRQ_54_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_54_55_DSP2_IRQ_54_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_54_55_DSP2_IRQ_55_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_54_55_DSP2_IRQ_55_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_54_55_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_54_55_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_54_55_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_54_55_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_56_57_DSP2_IRQ_56_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_56_57_DSP2_IRQ_56_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_56_57_DSP2_IRQ_57_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_56_57_DSP2_IRQ_57_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_56_57_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_56_57_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_56_57_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_56_57_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_58_59_DSP2_IRQ_58_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_58_59_DSP2_IRQ_58_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_58_59_DSP2_IRQ_59_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_58_59_DSP2_IRQ_59_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_58_59_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_58_59_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_58_59_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_58_59_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_60_61_DSP2_IRQ_60_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_60_61_DSP2_IRQ_60_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_60_61_DSP2_IRQ_61_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_60_61_DSP2_IRQ_61_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_60_61_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_60_61_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_60_61_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_60_61_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_62_63_DSP2_IRQ_62_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_62_63_DSP2_IRQ_62_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_62_63_DSP2_IRQ_63_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_62_63_DSP2_IRQ_63_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_62_63_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_62_63_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_62_63_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_62_63_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_64_65_DSP2_IRQ_64_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_64_65_DSP2_IRQ_64_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_64_65_DSP2_IRQ_65_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_64_65_DSP2_IRQ_65_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_64_65_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_64_65_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_64_65_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_64_65_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_66_67_DSP2_IRQ_66_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_66_67_DSP2_IRQ_66_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_66_67_DSP2_IRQ_67_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_66_67_DSP2_IRQ_67_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_66_67_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_66_67_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_66_67_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_66_67_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_68_69_DSP2_IRQ_68_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_68_69_DSP2_IRQ_68_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_68_69_DSP2_IRQ_69_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_68_69_DSP2_IRQ_69_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_68_69_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_68_69_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_68_69_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_68_69_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_70_71_DSP2_IRQ_70_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_70_71_DSP2_IRQ_70_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_70_71_DSP2_IRQ_71_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_70_71_DSP2_IRQ_71_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_70_71_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_70_71_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_70_71_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_70_71_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_72_73_DSP2_IRQ_72_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_72_73_DSP2_IRQ_72_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_72_73_DSP2_IRQ_73_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_72_73_DSP2_IRQ_73_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_72_73_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_72_73_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_72_73_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_72_73_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_74_75_DSP2_IRQ_74_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_74_75_DSP2_IRQ_74_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_74_75_DSP2_IRQ_75_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_74_75_DSP2_IRQ_75_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_74_75_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_74_75_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_74_75_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_74_75_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_76_77_DSP2_IRQ_76_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_76_77_DSP2_IRQ_76_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_76_77_DSP2_IRQ_77_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_76_77_DSP2_IRQ_77_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_76_77_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_76_77_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_76_77_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_76_77_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_78_79_DSP2_IRQ_78_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_78_79_DSP2_IRQ_78_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_78_79_DSP2_IRQ_79_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_78_79_DSP2_IRQ_79_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_78_79_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_78_79_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_78_79_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_78_79_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_80_81_DSP2_IRQ_80_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_80_81_DSP2_IRQ_80_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_80_81_DSP2_IRQ_81_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_80_81_DSP2_IRQ_81_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_80_81_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_80_81_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_80_81_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_80_81_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_82_83_DSP2_IRQ_82_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_82_83_DSP2_IRQ_82_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_82_83_DSP2_IRQ_83_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_82_83_DSP2_IRQ_83_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_82_83_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_82_83_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_82_83_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_82_83_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_84_85_DSP2_IRQ_84_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_84_85_DSP2_IRQ_84_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_84_85_DSP2_IRQ_85_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_84_85_DSP2_IRQ_85_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_84_85_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_84_85_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_84_85_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_84_85_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_86_87_DSP2_IRQ_86_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_86_87_DSP2_IRQ_86_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_86_87_DSP2_IRQ_87_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_86_87_DSP2_IRQ_87_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_86_87_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_86_87_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_86_87_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_86_87_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_88_89_DSP2_IRQ_88_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_88_89_DSP2_IRQ_88_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_88_89_DSP2_IRQ_89_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_88_89_DSP2_IRQ_89_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_88_89_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_88_89_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_88_89_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_88_89_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_90_91_DSP2_IRQ_90_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_90_91_DSP2_IRQ_90_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_90_91_DSP2_IRQ_91_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_90_91_DSP2_IRQ_91_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_90_91_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_90_91_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_90_91_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_90_91_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_92_93_DSP2_IRQ_92_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_92_93_DSP2_IRQ_92_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_92_93_DSP2_IRQ_93_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_92_93_DSP2_IRQ_93_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_92_93_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_92_93_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_92_93_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_92_93_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_DSP2_IRQ_94_95_DSP2_IRQ_94_SHIFT                                                         (0U)
#define CTRL_CORE_DSP2_IRQ_94_95_DSP2_IRQ_94_MASK                                                          (0x000001ffU)

#define CTRL_CORE_DSP2_IRQ_94_95_DSP2_IRQ_95_SHIFT                                                         (16U)
#define CTRL_CORE_DSP2_IRQ_94_95_DSP2_IRQ_95_MASK                                                          (0x01ff0000U)

#define CTRL_CORE_DSP2_IRQ_94_95_RESERVED_0_SHIFT                                                          (9U)
#define CTRL_CORE_DSP2_IRQ_94_95_RESERVED_0_MASK                                                           (0x0000fe00U)

#define CTRL_CORE_DSP2_IRQ_94_95_RESERVED_1_SHIFT                                                          (25U)
#define CTRL_CORE_DSP2_IRQ_94_95_RESERVED_1_MASK                                                           (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_4_5_MPU_IRQ_4_SHIFT                                                              (0U)
#define CTRL_CORE_MPU_IRQ_4_5_MPU_IRQ_4_MASK                                                               (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_4_5_MPU_IRQ_7_SHIFT                                                              (16U)
#define CTRL_CORE_MPU_IRQ_4_5_MPU_IRQ_7_MASK                                                               (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_4_5_RESERVED_0_SHIFT                                                             (9U)
#define CTRL_CORE_MPU_IRQ_4_5_RESERVED_0_MASK                                                              (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_4_5_RESERVED_1_SHIFT                                                             (25U)
#define CTRL_CORE_MPU_IRQ_4_5_RESERVED_1_MASK                                                              (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_8_9_MPU_IRQ_8_SHIFT                                                              (0U)
#define CTRL_CORE_MPU_IRQ_8_9_MPU_IRQ_8_MASK                                                               (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_8_9_MPU_IRQ_9_SHIFT                                                              (16U)
#define CTRL_CORE_MPU_IRQ_8_9_MPU_IRQ_9_MASK                                                               (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_8_9_RESERVED_0_SHIFT                                                             (9U)
#define CTRL_CORE_MPU_IRQ_8_9_RESERVED_0_MASK                                                              (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_8_9_RESERVED_1_SHIFT                                                             (25U)
#define CTRL_CORE_MPU_IRQ_8_9_RESERVED_1_MASK                                                              (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_10_11_MPU_IRQ_10_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_10_11_MPU_IRQ_10_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_10_11_MPU_IRQ_11_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_10_11_MPU_IRQ_11_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_10_11_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_10_11_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_10_11_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_10_11_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_12_13_MPU_IRQ_12_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_12_13_MPU_IRQ_12_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_12_13_MPU_IRQ_13_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_12_13_MPU_IRQ_13_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_12_13_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_12_13_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_12_13_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_12_13_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_14_15_MPU_IRQ_14_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_14_15_MPU_IRQ_14_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_14_15_MPU_IRQ_15_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_14_15_MPU_IRQ_15_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_14_15_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_14_15_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_14_15_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_14_15_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_16_17_MPU_IRQ_16_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_16_17_MPU_IRQ_16_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_16_17_MPU_IRQ_17_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_16_17_MPU_IRQ_17_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_16_17_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_16_17_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_16_17_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_16_17_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_18_19_MPU_IRQ_18_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_18_19_MPU_IRQ_18_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_18_19_MPU_IRQ_19_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_18_19_MPU_IRQ_19_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_18_19_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_18_19_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_18_19_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_18_19_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_20_21_MPU_IRQ_20_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_20_21_MPU_IRQ_20_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_20_21_MPU_IRQ_21_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_20_21_MPU_IRQ_21_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_20_21_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_20_21_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_20_21_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_20_21_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_22_23_MPU_IRQ_22_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_22_23_MPU_IRQ_22_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_22_23_MPU_IRQ_23_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_22_23_MPU_IRQ_23_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_22_23_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_22_23_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_22_23_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_22_23_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_24_25_MPU_IRQ_24_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_24_25_MPU_IRQ_24_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_24_25_MPU_IRQ_25_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_24_25_MPU_IRQ_25_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_24_25_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_24_25_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_24_25_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_24_25_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_26_27_MPU_IRQ_26_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_26_27_MPU_IRQ_26_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_26_27_MPU_IRQ_27_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_26_27_MPU_IRQ_27_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_26_27_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_26_27_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_26_27_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_26_27_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_28_29_MPU_IRQ_28_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_28_29_MPU_IRQ_28_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_28_29_MPU_IRQ_29_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_28_29_MPU_IRQ_29_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_28_29_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_28_29_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_28_29_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_28_29_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_30_31_MPU_IRQ_30_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_30_31_MPU_IRQ_30_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_30_31_MPU_IRQ_31_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_30_31_MPU_IRQ_31_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_30_31_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_30_31_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_30_31_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_30_31_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_32_33_MPU_IRQ_32_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_32_33_MPU_IRQ_32_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_32_33_MPU_IRQ_33_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_32_33_MPU_IRQ_33_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_32_33_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_32_33_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_32_33_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_32_33_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_34_35_MPU_IRQ_34_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_34_35_MPU_IRQ_34_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_34_35_MPU_IRQ_35_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_34_35_MPU_IRQ_35_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_34_35_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_34_35_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_34_35_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_34_35_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_36_37_MPU_IRQ_36_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_36_37_MPU_IRQ_36_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_36_37_MPU_IRQ_37_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_36_37_MPU_IRQ_37_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_36_37_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_36_37_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_36_37_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_36_37_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_38_39_MPU_IRQ_38_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_38_39_MPU_IRQ_38_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_38_39_MPU_IRQ_39_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_38_39_MPU_IRQ_39_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_38_39_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_38_39_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_38_39_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_38_39_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_40_41_MPU_IRQ_40_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_40_41_MPU_IRQ_40_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_40_41_MPU_IRQ_41_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_40_41_MPU_IRQ_41_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_40_41_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_40_41_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_40_41_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_40_41_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_42_43_MPU_IRQ_42_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_42_43_MPU_IRQ_42_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_42_43_MPU_IRQ_43_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_42_43_MPU_IRQ_43_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_42_43_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_42_43_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_42_43_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_42_43_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_44_45_MPU_IRQ_44_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_44_45_MPU_IRQ_44_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_44_45_MPU_IRQ_45_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_44_45_MPU_IRQ_45_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_44_45_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_44_45_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_44_45_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_44_45_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_46_47_MPU_IRQ_46_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_46_47_MPU_IRQ_46_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_46_47_MPU_IRQ_47_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_46_47_MPU_IRQ_47_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_46_47_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_46_47_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_46_47_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_46_47_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_48_49_MPU_IRQ_48_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_48_49_MPU_IRQ_48_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_48_49_MPU_IRQ_49_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_48_49_MPU_IRQ_49_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_48_49_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_48_49_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_48_49_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_48_49_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_50_51_MPU_IRQ_50_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_50_51_MPU_IRQ_50_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_50_51_MPU_IRQ_51_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_50_51_MPU_IRQ_51_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_50_51_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_50_51_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_50_51_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_50_51_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_52_53_MPU_IRQ_52_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_52_53_MPU_IRQ_52_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_52_53_MPU_IRQ_53_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_52_53_MPU_IRQ_53_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_52_53_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_52_53_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_52_53_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_52_53_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_54_55_MPU_IRQ_54_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_54_55_MPU_IRQ_54_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_54_55_MPU_IRQ_55_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_54_55_MPU_IRQ_55_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_54_55_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_54_55_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_54_55_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_54_55_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_56_57_MPU_IRQ_56_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_56_57_MPU_IRQ_56_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_56_57_MPU_IRQ_57_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_56_57_MPU_IRQ_57_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_56_57_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_56_57_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_56_57_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_56_57_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_58_59_MPU_IRQ_58_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_58_59_MPU_IRQ_58_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_58_59_MPU_IRQ_59_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_58_59_MPU_IRQ_59_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_58_59_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_58_59_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_58_59_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_58_59_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_60_61_MPU_IRQ_60_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_60_61_MPU_IRQ_60_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_60_61_MPU_IRQ_61_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_60_61_MPU_IRQ_61_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_60_61_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_60_61_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_60_61_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_60_61_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_62_63_MPU_IRQ_62_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_62_63_MPU_IRQ_62_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_62_63_MPU_IRQ_63_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_62_63_MPU_IRQ_63_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_62_63_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_62_63_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_62_63_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_62_63_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_64_65_MPU_IRQ_64_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_64_65_MPU_IRQ_64_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_64_65_MPU_IRQ_65_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_64_65_MPU_IRQ_65_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_64_65_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_64_65_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_64_65_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_64_65_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_66_67_MPU_IRQ_66_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_66_67_MPU_IRQ_66_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_66_67_MPU_IRQ_67_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_66_67_MPU_IRQ_67_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_66_67_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_66_67_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_66_67_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_66_67_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_68_69_MPU_IRQ_68_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_68_69_MPU_IRQ_68_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_68_69_MPU_IRQ_69_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_68_69_MPU_IRQ_69_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_68_69_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_68_69_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_68_69_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_68_69_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_70_71_MPU_IRQ_70_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_70_71_MPU_IRQ_70_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_70_71_MPU_IRQ_71_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_70_71_MPU_IRQ_71_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_70_71_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_70_71_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_70_71_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_70_71_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_72_73_MPU_IRQ_72_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_72_73_MPU_IRQ_72_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_72_73_MPU_IRQ_73_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_72_73_MPU_IRQ_73_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_72_73_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_72_73_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_72_73_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_72_73_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_74_75_MPU_IRQ_74_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_74_75_MPU_IRQ_74_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_74_75_MPU_IRQ_75_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_74_75_MPU_IRQ_75_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_74_75_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_74_75_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_74_75_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_74_75_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_76_77_MPU_IRQ_76_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_76_77_MPU_IRQ_76_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_76_77_MPU_IRQ_77_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_76_77_MPU_IRQ_77_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_76_77_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_76_77_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_76_77_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_76_77_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_78_79_MPU_IRQ_78_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_78_79_MPU_IRQ_78_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_78_79_MPU_IRQ_79_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_78_79_MPU_IRQ_79_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_78_79_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_78_79_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_78_79_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_78_79_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_80_81_MPU_IRQ_80_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_80_81_MPU_IRQ_80_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_80_81_MPU_IRQ_81_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_80_81_MPU_IRQ_81_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_80_81_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_80_81_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_80_81_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_80_81_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_82_83_MPU_IRQ_82_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_82_83_MPU_IRQ_82_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_82_83_MPU_IRQ_83_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_82_83_MPU_IRQ_83_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_82_83_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_82_83_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_82_83_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_82_83_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_84_85_MPU_IRQ_84_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_84_85_MPU_IRQ_84_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_84_85_MPU_IRQ_85_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_84_85_MPU_IRQ_85_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_84_85_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_84_85_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_84_85_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_84_85_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_86_87_MPU_IRQ_86_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_86_87_MPU_IRQ_86_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_86_87_MPU_IRQ_87_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_86_87_MPU_IRQ_87_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_86_87_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_86_87_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_86_87_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_86_87_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_88_89_MPU_IRQ_88_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_88_89_MPU_IRQ_88_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_88_89_MPU_IRQ_89_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_88_89_MPU_IRQ_89_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_88_89_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_88_89_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_88_89_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_88_89_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_90_91_MPU_IRQ_90_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_90_91_MPU_IRQ_90_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_90_91_MPU_IRQ_91_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_90_91_MPU_IRQ_91_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_90_91_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_90_91_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_90_91_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_90_91_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_92_93_MPU_IRQ_92_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_92_93_MPU_IRQ_92_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_92_93_MPU_IRQ_93_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_92_93_MPU_IRQ_93_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_92_93_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_92_93_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_92_93_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_92_93_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_94_95_MPU_IRQ_94_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_94_95_MPU_IRQ_94_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_94_95_MPU_IRQ_95_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_94_95_MPU_IRQ_95_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_94_95_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_94_95_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_94_95_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_94_95_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_96_97_MPU_IRQ_96_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_96_97_MPU_IRQ_96_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_96_97_MPU_IRQ_97_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_96_97_MPU_IRQ_97_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_96_97_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_96_97_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_96_97_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_96_97_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_98_99_MPU_IRQ_98_SHIFT                                                           (0U)
#define CTRL_CORE_MPU_IRQ_98_99_MPU_IRQ_98_MASK                                                            (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_98_99_MPU_IRQ_99_SHIFT                                                           (16U)
#define CTRL_CORE_MPU_IRQ_98_99_MPU_IRQ_99_MASK                                                            (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_98_99_RESERVED_0_SHIFT                                                           (9U)
#define CTRL_CORE_MPU_IRQ_98_99_RESERVED_0_MASK                                                            (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_98_99_RESERVED_1_SHIFT                                                           (25U)
#define CTRL_CORE_MPU_IRQ_98_99_RESERVED_1_MASK                                                            (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_100_101_MPU_IRQ_100_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_100_101_MPU_IRQ_100_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_100_101_MPU_IRQ_101_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_100_101_MPU_IRQ_101_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_100_101_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_100_101_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_100_101_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_100_101_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_102_103_MPU_IRQ_102_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_102_103_MPU_IRQ_102_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_102_103_MPU_IRQ_103_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_102_103_MPU_IRQ_103_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_102_103_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_102_103_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_102_103_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_102_103_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_104_105_MPU_IRQ_104_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_104_105_MPU_IRQ_104_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_104_105_MPU_IRQ_105_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_104_105_MPU_IRQ_105_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_104_105_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_104_105_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_104_105_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_104_105_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_106_107_MPU_IRQ_106_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_106_107_MPU_IRQ_106_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_106_107_MPU_IRQ_107_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_106_107_MPU_IRQ_107_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_106_107_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_106_107_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_106_107_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_106_107_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_108_109_MPU_IRQ_108_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_108_109_MPU_IRQ_108_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_108_109_MPU_IRQ_109_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_108_109_MPU_IRQ_109_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_108_109_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_108_109_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_108_109_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_108_109_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_110_111_MPU_IRQ_110_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_110_111_MPU_IRQ_110_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_110_111_MPU_IRQ_111_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_110_111_MPU_IRQ_111_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_110_111_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_110_111_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_110_111_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_110_111_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_112_113_MPU_IRQ_112_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_112_113_MPU_IRQ_112_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_112_113_MPU_IRQ_113_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_112_113_MPU_IRQ_113_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_112_113_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_112_113_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_112_113_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_112_113_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_114_115_MPU_IRQ_114_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_114_115_MPU_IRQ_114_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_114_115_MPU_IRQ_115_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_114_115_MPU_IRQ_115_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_114_115_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_114_115_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_114_115_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_114_115_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_116_117_MPU_IRQ_116_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_116_117_MPU_IRQ_116_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_116_117_MPU_IRQ_117_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_116_117_MPU_IRQ_117_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_116_117_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_116_117_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_116_117_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_116_117_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_118_119_MPU_IRQ_118_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_118_119_MPU_IRQ_118_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_118_119_MPU_IRQ_119_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_118_119_MPU_IRQ_119_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_118_119_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_118_119_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_118_119_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_118_119_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_120_121_MPU_IRQ_120_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_120_121_MPU_IRQ_120_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_120_121_MPU_IRQ_121_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_120_121_MPU_IRQ_121_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_120_121_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_120_121_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_120_121_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_120_121_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_122_123_MPU_IRQ_122_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_122_123_MPU_IRQ_122_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_122_123_MPU_IRQ_123_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_122_123_MPU_IRQ_123_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_122_123_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_122_123_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_122_123_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_122_123_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_124_125_MPU_IRQ_124_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_124_125_MPU_IRQ_124_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_124_125_MPU_IRQ_125_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_124_125_MPU_IRQ_125_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_124_125_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_124_125_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_124_125_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_124_125_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_126_127_MPU_IRQ_126_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_126_127_MPU_IRQ_126_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_126_127_MPU_IRQ_127_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_126_127_MPU_IRQ_127_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_126_127_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_126_127_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_126_127_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_126_127_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_128_129_MPU_IRQ_128_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_128_129_MPU_IRQ_128_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_128_129_MPU_IRQ_129_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_128_129_MPU_IRQ_129_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_128_129_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_128_129_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_128_129_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_128_129_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_130_131_MPU_IRQ_130_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_130_131_MPU_IRQ_130_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_130_131_MPU_IRQ_133_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_130_131_MPU_IRQ_133_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_130_131_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_130_131_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_130_131_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_130_131_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_134_135_MPU_IRQ_134_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_134_135_MPU_IRQ_134_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_134_135_MPU_IRQ_135_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_134_135_MPU_IRQ_135_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_134_135_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_134_135_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_134_135_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_134_135_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_136_137_MPU_IRQ_136_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_136_137_MPU_IRQ_136_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_136_137_MPU_IRQ_137_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_136_137_MPU_IRQ_137_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_136_137_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_136_137_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_136_137_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_136_137_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_138_139_MPU_IRQ_138_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_138_139_MPU_IRQ_138_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_138_139_MPU_IRQ_139_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_138_139_MPU_IRQ_139_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_138_139_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_138_139_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_138_139_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_138_139_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_140_141_MPU_IRQ_140_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_140_141_MPU_IRQ_140_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_140_141_MPU_IRQ_141_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_140_141_MPU_IRQ_141_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_140_141_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_140_141_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_140_141_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_140_141_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_142_143_MPU_IRQ_142_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_142_143_MPU_IRQ_142_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_142_143_MPU_IRQ_143_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_142_143_MPU_IRQ_143_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_142_143_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_142_143_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_142_143_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_142_143_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_144_145_MPU_IRQ_144_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_144_145_MPU_IRQ_144_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_144_145_MPU_IRQ_145_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_144_145_MPU_IRQ_145_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_144_145_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_144_145_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_144_145_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_144_145_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_146_147_MPU_IRQ_146_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_146_147_MPU_IRQ_146_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_146_147_MPU_IRQ_147_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_146_147_MPU_IRQ_147_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_146_147_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_146_147_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_146_147_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_146_147_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_148_149_MPU_IRQ_148_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_148_149_MPU_IRQ_148_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_148_149_MPU_IRQ_149_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_148_149_MPU_IRQ_149_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_148_149_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_148_149_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_148_149_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_148_149_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_150_151_MPU_IRQ_150_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_150_151_MPU_IRQ_150_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_150_151_MPU_IRQ_151_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_150_151_MPU_IRQ_151_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_150_151_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_150_151_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_150_151_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_150_151_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_152_153_MPU_IRQ_152_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_152_153_MPU_IRQ_152_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_152_153_MPU_IRQ_153_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_152_153_MPU_IRQ_153_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_152_153_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_152_153_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_152_153_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_152_153_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_154_155_MPU_IRQ_154_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_154_155_MPU_IRQ_154_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_154_155_MPU_IRQ_155_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_154_155_MPU_IRQ_155_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_154_155_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_154_155_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_154_155_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_154_155_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_156_157_MPU_IRQ_156_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_156_157_MPU_IRQ_156_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_156_157_MPU_IRQ_157_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_156_157_MPU_IRQ_157_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_156_157_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_156_157_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_156_157_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_156_157_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_MPU_IRQ_158_159_MPU_IRQ_158_SHIFT                                                        (0U)
#define CTRL_CORE_MPU_IRQ_158_159_MPU_IRQ_158_MASK                                                         (0x000001ffU)

#define CTRL_CORE_MPU_IRQ_158_159_MPU_IRQ_159_SHIFT                                                        (16U)
#define CTRL_CORE_MPU_IRQ_158_159_MPU_IRQ_159_MASK                                                         (0x01ff0000U)

#define CTRL_CORE_MPU_IRQ_158_159_RESERVED_0_SHIFT                                                         (9U)
#define CTRL_CORE_MPU_IRQ_158_159_RESERVED_0_MASK                                                          (0x0000fe00U)

#define CTRL_CORE_MPU_IRQ_158_159_RESERVED_1_SHIFT                                                         (25U)
#define CTRL_CORE_MPU_IRQ_158_159_RESERVED_1_MASK                                                          (0xfe000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_0_1_DMA_EDMA_DREQ_0_IRQ_0_SHIFT                                            (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_0_1_DMA_EDMA_DREQ_0_IRQ_0_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_0_1_DMA_EDMA_DREQ_1_IRQ_1_SHIFT                                            (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_0_1_DMA_EDMA_DREQ_1_IRQ_1_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_0_1_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_0_1_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_0_1_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_0_1_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_2_3_DMA_EDMA_DREQ_2_IRQ_2_SHIFT                                            (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_2_3_DMA_EDMA_DREQ_2_IRQ_2_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_2_3_DMA_EDMA_DREQ_3_IRQ_3_SHIFT                                            (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_2_3_DMA_EDMA_DREQ_3_IRQ_3_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_2_3_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_2_3_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_2_3_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_2_3_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_4_5_DMA_EDMA_DREQ_4_IRQ_4_SHIFT                                            (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_4_5_DMA_EDMA_DREQ_4_IRQ_4_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_4_5_DMA_EDMA_DREQ_5_IRQ_5_SHIFT                                            (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_4_5_DMA_EDMA_DREQ_5_IRQ_5_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_4_5_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_4_5_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_4_5_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_4_5_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_6_7_DMA_EDMA_DREQ_6_IRQ_6_SHIFT                                            (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_6_7_DMA_EDMA_DREQ_6_IRQ_6_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_6_7_DMA_EDMA_DREQ_7_IRQ_7_SHIFT                                            (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_6_7_DMA_EDMA_DREQ_7_IRQ_7_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_6_7_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_6_7_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_6_7_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_6_7_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_8_9_DMA_EDMA_DREQ_8_IRQ_8_SHIFT                                            (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_8_9_DMA_EDMA_DREQ_8_IRQ_8_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_8_9_DMA_EDMA_DREQ_9_IRQ_9_SHIFT                                            (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_8_9_DMA_EDMA_DREQ_9_IRQ_9_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_8_9_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_8_9_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_8_9_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_8_9_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_10_11_DMA_EDMA_DREQ_10_IRQ_10_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_10_11_DMA_EDMA_DREQ_10_IRQ_10_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_10_11_DMA_EDMA_DREQ_11_IRQ_11_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_10_11_DMA_EDMA_DREQ_11_IRQ_11_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_10_11_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_10_11_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_10_11_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_10_11_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_12_13_DMA_EDMA_DREQ_12_IRQ_12_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_12_13_DMA_EDMA_DREQ_12_IRQ_12_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_12_13_DMA_EDMA_DREQ_13_IRQ_13_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_12_13_DMA_EDMA_DREQ_13_IRQ_13_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_12_13_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_12_13_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_12_13_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_12_13_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_14_15_DMA_EDMA_DREQ_14_IRQ_14_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_14_15_DMA_EDMA_DREQ_14_IRQ_14_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_14_15_DMA_EDMA_DREQ_15_IRQ_15_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_14_15_DMA_EDMA_DREQ_15_IRQ_15_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_14_15_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_14_15_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_14_15_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_14_15_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_16_17_DMA_EDMA_DREQ_16_IRQ_16_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_16_17_DMA_EDMA_DREQ_16_IRQ_16_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_16_17_DMA_EDMA_DREQ_17_IRQ_17_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_16_17_DMA_EDMA_DREQ_17_IRQ_17_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_16_17_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_16_17_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_16_17_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_16_17_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_18_19_DMA_EDMA_DREQ_18_IRQ_18_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_18_19_DMA_EDMA_DREQ_18_IRQ_18_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_18_19_DMA_EDMA_DREQ_19_IRQ_19_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_18_19_DMA_EDMA_DREQ_19_IRQ_19_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_18_19_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_18_19_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_18_19_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_18_19_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_20_21_DMA_EDMA_DREQ_20_IRQ_20_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_20_21_DMA_EDMA_DREQ_20_IRQ_20_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_20_21_DMA_EDMA_DREQ_21_IRQ_21_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_20_21_DMA_EDMA_DREQ_21_IRQ_21_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_20_21_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_20_21_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_20_21_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_20_21_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_22_23_DMA_EDMA_DREQ_22_IRQ_22_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_22_23_DMA_EDMA_DREQ_22_IRQ_22_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_22_23_DMA_EDMA_DREQ_23_IRQ_23_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_22_23_DMA_EDMA_DREQ_23_IRQ_23_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_22_23_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_22_23_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_22_23_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_22_23_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_24_25_DMA_EDMA_DREQ_24_IRQ_24_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_24_25_DMA_EDMA_DREQ_24_IRQ_24_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_24_25_DMA_EDMA_DREQ_25_IRQ_25_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_24_25_DMA_EDMA_DREQ_25_IRQ_25_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_24_25_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_24_25_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_24_25_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_24_25_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_26_27_DMA_EDMA_DREQ_26_IRQ_26_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_26_27_DMA_EDMA_DREQ_26_IRQ_26_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_26_27_DMA_EDMA_DREQ_27_IRQ_27_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_26_27_DMA_EDMA_DREQ_27_IRQ_27_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_26_27_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_26_27_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_26_27_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_26_27_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_28_29_DMA_EDMA_DREQ_28_IRQ_28_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_28_29_DMA_EDMA_DREQ_28_IRQ_28_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_28_29_DMA_EDMA_DREQ_29_IRQ_29_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_28_29_DMA_EDMA_DREQ_29_IRQ_29_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_28_29_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_28_29_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_28_29_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_28_29_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_30_31_DMA_EDMA_DREQ_30_IRQ_30_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_30_31_DMA_EDMA_DREQ_30_IRQ_30_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_30_31_DMA_EDMA_DREQ_31_IRQ_31_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_30_31_DMA_EDMA_DREQ_31_IRQ_31_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_30_31_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_30_31_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_30_31_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_30_31_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_32_33_DMA_EDMA_DREQ_32_IRQ_32_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_32_33_DMA_EDMA_DREQ_32_IRQ_32_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_32_33_DMA_EDMA_DREQ_33_IRQ_33_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_32_33_DMA_EDMA_DREQ_33_IRQ_33_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_32_33_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_32_33_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_32_33_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_32_33_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_34_35_DMA_EDMA_DREQ_34_IRQ_34_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_34_35_DMA_EDMA_DREQ_34_IRQ_34_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_34_35_DMA_EDMA_DREQ_35_IRQ_35_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_34_35_DMA_EDMA_DREQ_35_IRQ_35_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_34_35_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_34_35_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_34_35_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_34_35_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_36_37_DMA_EDMA_DREQ_36_IRQ_36_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_36_37_DMA_EDMA_DREQ_36_IRQ_36_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_36_37_DMA_EDMA_DREQ_37_IRQ_37_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_36_37_DMA_EDMA_DREQ_37_IRQ_37_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_36_37_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_36_37_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_36_37_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_36_37_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_38_39_DMA_EDMA_DREQ_38_IRQ_38_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_38_39_DMA_EDMA_DREQ_38_IRQ_38_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_38_39_DMA_EDMA_DREQ_39_IRQ_39_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_38_39_DMA_EDMA_DREQ_39_IRQ_39_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_38_39_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_38_39_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_38_39_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_38_39_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_40_41_DMA_EDMA_DREQ_40_IRQ_40_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_40_41_DMA_EDMA_DREQ_40_IRQ_40_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_40_41_DMA_EDMA_DREQ_41_IRQ_41_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_40_41_DMA_EDMA_DREQ_41_IRQ_41_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_40_41_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_40_41_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_40_41_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_40_41_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_42_43_DMA_EDMA_DREQ_42_IRQ_42_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_42_43_DMA_EDMA_DREQ_42_IRQ_42_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_42_43_DMA_EDMA_DREQ_43_IRQ_43_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_42_43_DMA_EDMA_DREQ_43_IRQ_43_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_42_43_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_42_43_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_42_43_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_42_43_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_44_45_DMA_EDMA_DREQ_44_IRQ_44_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_44_45_DMA_EDMA_DREQ_44_IRQ_44_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_44_45_DMA_EDMA_DREQ_45_IRQ_45_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_44_45_DMA_EDMA_DREQ_45_IRQ_45_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_44_45_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_44_45_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_44_45_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_44_45_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_46_47_DMA_EDMA_DREQ_46_IRQ_46_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_46_47_DMA_EDMA_DREQ_46_IRQ_46_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_46_47_DMA_EDMA_DREQ_47_IRQ_47_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_46_47_DMA_EDMA_DREQ_47_IRQ_47_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_46_47_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_46_47_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_46_47_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_46_47_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_48_49_DMA_EDMA_DREQ_48_IRQ_48_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_48_49_DMA_EDMA_DREQ_48_IRQ_48_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_48_49_DMA_EDMA_DREQ_49_IRQ_49_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_48_49_DMA_EDMA_DREQ_49_IRQ_49_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_48_49_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_48_49_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_48_49_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_48_49_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_50_51_DMA_EDMA_DREQ_50_IRQ_50_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_50_51_DMA_EDMA_DREQ_50_IRQ_50_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_50_51_DMA_EDMA_DREQ_51_IRQ_51_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_50_51_DMA_EDMA_DREQ_51_IRQ_51_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_50_51_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_50_51_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_50_51_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_50_51_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_52_53_DMA_EDMA_DREQ_52_IRQ_52_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_52_53_DMA_EDMA_DREQ_52_IRQ_52_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_52_53_DMA_EDMA_DREQ_53_IRQ_53_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_52_53_DMA_EDMA_DREQ_53_IRQ_53_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_52_53_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_52_53_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_52_53_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_52_53_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_54_55_DMA_EDMA_DREQ_54_IRQ_54_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_54_55_DMA_EDMA_DREQ_54_IRQ_54_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_54_55_DMA_EDMA_DREQ_55_IRQ_55_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_54_55_DMA_EDMA_DREQ_55_IRQ_55_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_54_55_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_54_55_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_54_55_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_54_55_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_56_57_DMA_EDMA_DREQ_56_IRQ_56_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_56_57_DMA_EDMA_DREQ_56_IRQ_56_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_56_57_DMA_EDMA_DREQ_57_IRQ_57_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_56_57_DMA_EDMA_DREQ_57_IRQ_57_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_56_57_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_56_57_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_56_57_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_56_57_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_58_59_DMA_EDMA_DREQ_58_IRQ_58_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_58_59_DMA_EDMA_DREQ_58_IRQ_58_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_58_59_DMA_EDMA_DREQ_59_IRQ_59_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_58_59_DMA_EDMA_DREQ_59_IRQ_59_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_58_59_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_58_59_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_58_59_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_58_59_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_60_61_DMA_EDMA_DREQ_60_IRQ_60_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_60_61_DMA_EDMA_DREQ_60_IRQ_60_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_60_61_DMA_EDMA_DREQ_61_IRQ_61_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_60_61_DMA_EDMA_DREQ_61_IRQ_61_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_60_61_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_60_61_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_60_61_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_60_61_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_EDMA_DREQ_62_63_DMA_EDMA_DREQ_62_IRQ_62_SHIFT                                        (0U)
#define CTRL_CORE_DMA_EDMA_DREQ_62_63_DMA_EDMA_DREQ_62_IRQ_62_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_EDMA_DREQ_62_63_DMA_EDMA_DREQ_63_IRQ_63_SHIFT                                        (16U)
#define CTRL_CORE_DMA_EDMA_DREQ_62_63_DMA_EDMA_DREQ_63_IRQ_63_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_EDMA_DREQ_62_63_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_EDMA_DREQ_62_63_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_EDMA_DREQ_62_63_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_EDMA_DREQ_62_63_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_0_1_DMA_DSP1_DREQ_0_IRQ_0_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_0_1_DMA_DSP1_DREQ_0_IRQ_0_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_0_1_DMA_DSP1_DREQ_1_IRQ_1_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_0_1_DMA_DSP1_DREQ_1_IRQ_1_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_0_1_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_0_1_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_0_1_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_0_1_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_2_3_DMA_DSP1_DREQ_2_IRQ_2_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_2_3_DMA_DSP1_DREQ_2_IRQ_2_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_2_3_DMA_DSP1_DREQ_3_IRQ_3_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_2_3_DMA_DSP1_DREQ_3_IRQ_3_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_2_3_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_2_3_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_2_3_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_2_3_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_4_5_DMA_DSP1_DREQ_4_IRQ_4_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_4_5_DMA_DSP1_DREQ_4_IRQ_4_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_4_5_DMA_DSP1_DREQ_5_IRQ_5_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_4_5_DMA_DSP1_DREQ_5_IRQ_5_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_4_5_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_4_5_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_4_5_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_4_5_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_6_7_DMA_DSP1_DREQ_6_IRQ_6_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_6_7_DMA_DSP1_DREQ_6_IRQ_6_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_6_7_DMA_DSP1_DREQ_7_IRQ_7_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_6_7_DMA_DSP1_DREQ_7_IRQ_7_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_6_7_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_6_7_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_6_7_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_6_7_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_8_9_DMA_DSP1_DREQ_8_IRQ_8_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_8_9_DMA_DSP1_DREQ_8_IRQ_8_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_8_9_DMA_DSP1_DREQ_9_IRQ_9_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_8_9_DMA_DSP1_DREQ_9_IRQ_9_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_8_9_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_8_9_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_8_9_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_8_9_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_10_11_DMA_DSP1_DREQ_10_IRQ_10_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_10_11_DMA_DSP1_DREQ_10_IRQ_10_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_10_11_DMA_DSP1_DREQ_11_IRQ_11_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_10_11_DMA_DSP1_DREQ_11_IRQ_11_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_10_11_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_10_11_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_10_11_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_10_11_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_12_13_DMA_DSP1_DREQ_12_IRQ_12_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_12_13_DMA_DSP1_DREQ_12_IRQ_12_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_12_13_DMA_DSP1_DREQ_13_IRQ_13_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_12_13_DMA_DSP1_DREQ_13_IRQ_13_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_12_13_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_12_13_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_12_13_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_12_13_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_14_15_DMA_DSP1_DREQ_14_IRQ_14_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_14_15_DMA_DSP1_DREQ_14_IRQ_14_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_14_15_DMA_DSP1_DREQ_15_IRQ_15_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_14_15_DMA_DSP1_DREQ_15_IRQ_15_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_14_15_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_14_15_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_14_15_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_14_15_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_16_17_DMA_DSP1_DREQ_16_IRQ_16_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_16_17_DMA_DSP1_DREQ_16_IRQ_16_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_16_17_DMA_DSP1_DREQ_17_IRQ_17_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_16_17_DMA_DSP1_DREQ_17_IRQ_17_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_16_17_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_16_17_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_16_17_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_16_17_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP1_DREQ_18_19_DMA_DSP1_DREQ_18_IRQ_18_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP1_DREQ_18_19_DMA_DSP1_DREQ_18_IRQ_18_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP1_DREQ_18_19_DMA_DSP1_DREQ_19_IRQ_19_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP1_DREQ_18_19_DMA_DSP1_DREQ_19_IRQ_19_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP1_DREQ_18_19_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP1_DREQ_18_19_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP1_DREQ_18_19_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP1_DREQ_18_19_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_0_1_DMA_DSP2_DREQ_0_IRQ_0_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_0_1_DMA_DSP2_DREQ_0_IRQ_0_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_0_1_DMA_DSP2_DREQ_1_IRQ_1_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_0_1_DMA_DSP2_DREQ_1_IRQ_1_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_0_1_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_0_1_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_0_1_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_0_1_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_2_3_DMA_DSP2_DREQ_2_IRQ_2_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_2_3_DMA_DSP2_DREQ_2_IRQ_2_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_2_3_DMA_DSP2_DREQ_3_IRQ_3_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_2_3_DMA_DSP2_DREQ_3_IRQ_3_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_2_3_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_2_3_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_2_3_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_2_3_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_4_5_DMA_DSP2_DREQ_4_IRQ_4_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_4_5_DMA_DSP2_DREQ_4_IRQ_4_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_4_5_DMA_DSP2_DREQ_5_IRQ_5_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_4_5_DMA_DSP2_DREQ_5_IRQ_5_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_4_5_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_4_5_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_4_5_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_4_5_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_6_7_DMA_DSP2_DREQ_6_IRQ_6_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_6_7_DMA_DSP2_DREQ_6_IRQ_6_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_6_7_DMA_DSP2_DREQ_7_IRQ_7_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_6_7_DMA_DSP2_DREQ_7_IRQ_7_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_6_7_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_6_7_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_6_7_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_6_7_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_8_9_DMA_DSP2_DREQ_8_IRQ_8_SHIFT                                            (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_8_9_DMA_DSP2_DREQ_8_IRQ_8_MASK                                             (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_8_9_DMA_DSP2_DREQ_9_IRQ_9_SHIFT                                            (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_8_9_DMA_DSP2_DREQ_9_IRQ_9_MASK                                             (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_8_9_RESERVED_0_SHIFT                                                       (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_8_9_RESERVED_0_MASK                                                        (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_8_9_RESERVED_1_SHIFT                                                       (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_8_9_RESERVED_1_MASK                                                        (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_10_11_DMA_DSP2_DREQ_10_IRQ_10_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_10_11_DMA_DSP2_DREQ_10_IRQ_10_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_10_11_DMA_DSP2_DREQ_11_IRQ_11_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_10_11_DMA_DSP2_DREQ_11_IRQ_11_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_10_11_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_10_11_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_10_11_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_10_11_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_12_13_DMA_DSP2_DREQ_12_IRQ_12_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_12_13_DMA_DSP2_DREQ_12_IRQ_12_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_12_13_DMA_DSP2_DREQ_13_IRQ_13_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_12_13_DMA_DSP2_DREQ_13_IRQ_13_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_12_13_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_12_13_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_12_13_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_12_13_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_14_15_DMA_DSP2_DREQ_14_IRQ_14_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_14_15_DMA_DSP2_DREQ_14_IRQ_14_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_14_15_DMA_DSP2_DREQ_15_IRQ_15_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_14_15_DMA_DSP2_DREQ_15_IRQ_15_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_14_15_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_14_15_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_14_15_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_14_15_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_16_17_DMA_DSP2_DREQ_16_IRQ_16_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_16_17_DMA_DSP2_DREQ_16_IRQ_16_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_16_17_DMA_DSP2_DREQ_17_IRQ_17_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_16_17_DMA_DSP2_DREQ_17_IRQ_17_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_16_17_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_16_17_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_16_17_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_16_17_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_DMA_DSP2_DREQ_18_19_DMA_DSP2_DREQ_18_IRQ_18_SHIFT                                        (0U)
#define CTRL_CORE_DMA_DSP2_DREQ_18_19_DMA_DSP2_DREQ_18_IRQ_18_MASK                                         (0x000000ffU)

#define CTRL_CORE_DMA_DSP2_DREQ_18_19_DMA_DSP2_DREQ_19_IRQ_19_SHIFT                                        (16U)
#define CTRL_CORE_DMA_DSP2_DREQ_18_19_DMA_DSP2_DREQ_19_IRQ_19_MASK                                         (0x00ff0000U)

#define CTRL_CORE_DMA_DSP2_DREQ_18_19_RESERVED_0_SHIFT                                                     (8U)
#define CTRL_CORE_DMA_DSP2_DREQ_18_19_RESERVED_0_MASK                                                      (0x0000ff00U)

#define CTRL_CORE_DMA_DSP2_DREQ_18_19_RESERVED_1_SHIFT                                                     (24U)
#define CTRL_CORE_DMA_DSP2_DREQ_18_19_RESERVED_1_MASK                                                      (0xff000000U)

#define CTRL_CORE_OVS_DMARQ_IO_MUX_OVS_DMARQ_IO_MUX_1_SHIFT                                                (0U)
#define CTRL_CORE_OVS_DMARQ_IO_MUX_OVS_DMARQ_IO_MUX_1_MASK                                                 (0x000000ffU)

#define CTRL_CORE_OVS_DMARQ_IO_MUX_OVS_DMARQ_IO_MUX_2_SHIFT                                                (8U)
#define CTRL_CORE_OVS_DMARQ_IO_MUX_OVS_DMARQ_IO_MUX_2_MASK                                                 (0x0000ff00U)

#define CTRL_CORE_OVS_DMARQ_IO_MUX_RESERVED_0_SHIFT                                                        (16U)
#define CTRL_CORE_OVS_DMARQ_IO_MUX_RESERVED_0_MASK                                                         (0xffff0000U)

#define CTRL_CORE_OVS_IRQ_IO_MUX_OVS_IRQ_IO_MUX_1_SHIFT                                                    (0U)
#define CTRL_CORE_OVS_IRQ_IO_MUX_OVS_IRQ_IO_MUX_1_MASK                                                     (0x000001ffU)

#define CTRL_CORE_OVS_IRQ_IO_MUX_OVS_IRQ_IO_MUX_2_SHIFT                                                    (9U)
#define CTRL_CORE_OVS_IRQ_IO_MUX_OVS_IRQ_IO_MUX_2_MASK                                                     (0x0003fe00U)

#define CTRL_CORE_OVS_IRQ_IO_MUX_RESERVED_0_SHIFT                                                          (18U)
#define CTRL_CORE_OVS_IRQ_IO_MUX_RESERVED_0_MASK                                                           (0xfffc0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_CORE_IRQ_DMA_H_ */
