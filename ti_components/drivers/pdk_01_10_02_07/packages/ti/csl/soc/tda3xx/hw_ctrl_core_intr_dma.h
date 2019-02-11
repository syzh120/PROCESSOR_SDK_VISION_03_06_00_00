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
 *  \file   hw_ctrl_core_intr_dma.h
 *
 *  \brief  Register-level header file for CTRL_CORE_INTR_DMA
 *
**/

#ifndef HW_CTRL_CORE_INTR_DMA_H_
#define HW_CTRL_CORE_INTR_DMA_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CTRL_CORE_INTR_DMA_EVE_IRQ_0_1                              (0x0U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_2_3                              (0x4U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_4_5                              (0x8U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_6_7                              (0xcU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_23_24                            (0x40U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_25_26                            (0x44U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_27_28                            (0x48U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_29_30                            (0x4cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_31_32                            (0x50U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_33_34                            (0x54U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_35_36                            (0x58U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_37_38                            (0x5cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_39_40                            (0x60U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_41_42                            (0x64U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_43_44                            (0x68U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_45_46                            (0x6cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_47_48                            (0x70U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_49_50                            (0x74U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_51_52                            (0x78U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_53_54                            (0x7cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_55_56                            (0x80U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_57_58                            (0x84U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_59_60                            (0x88U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_61_62                            (0x8cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_63_64                            (0x90U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_65_66                            (0x94U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_67_68                            (0x98U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_69_70                            (0x9cU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_71_72                            (0xa0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_73_74                            (0xa4U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_75_76                            (0xa8U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_77_78                            (0xacU)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_79_80                            (0xb0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_32_33                           (0x1a8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_34_35                           (0x1acU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_36_37                           (0x1b0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_38_39                           (0x1b4U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_40_41                           (0x1b8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_42_43                           (0x1bcU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_44_45                           (0x1c0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_46_47                           (0x1c4U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_48_49                           (0x1c8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_50_51                           (0x1ccU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_52_53                           (0x1d0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_54_55                           (0x1d4U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_56_57                           (0x1d8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_58_59                           (0x1dcU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_60_61                           (0x1e0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_62_63                           (0x1e4U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_64_65                           (0x1e8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_66_67                           (0x1ecU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_68_69                           (0x1f0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_70_71                           (0x1f4U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_72_73                           (0x1f8U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_74_75                           (0x1fcU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_76_77                           (0x200U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_78_79                           (0x204U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_80_81                           (0x208U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_82_83                           (0x20cU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_84_85                           (0x210U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_86_87                           (0x214U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_88_89                           (0x218U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_90_91                           (0x21cU)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_92_93                           (0x220U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_94_95                           (0x224U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_32_33                           (0x228U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_34_35                           (0x22cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_36_37                           (0x230U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_38_39                           (0x234U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_40_41                           (0x238U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_42_43                           (0x23cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_44_45                           (0x240U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_46_47                           (0x244U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_48_49                           (0x248U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_50_51                           (0x24cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_52_53                           (0x250U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_54_55                           (0x254U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_56_57                           (0x258U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_58_59                           (0x25cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_60_61                           (0x260U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_62_63                           (0x264U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_64_65                           (0x268U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_66_67                           (0x26cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_68_69                           (0x270U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_70_71                           (0x274U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_72_73                           (0x278U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_74_75                           (0x27cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_76_77                           (0x280U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_78_79                           (0x284U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_80_81                           (0x288U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_82_83                           (0x28cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_84_85                           (0x290U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_86_87                           (0x294U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_88_89                           (0x298U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_90_91                           (0x29cU)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_92_93                           (0x2a0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_94_95                           (0x2a4U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_0_1                            (0x4d8U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_2_3                            (0x4dcU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_4_5                            (0x4e0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_6_7                            (0x4e4U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_8_9                            (0x4e8U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_10_11                          (0x4ecU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_12_13                          (0x4f0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_14_15                          (0x4f4U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_16_17                          (0x4f8U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_18_19                          (0x4fcU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_20_21                          (0x500U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_22_23                          (0x504U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_24_25                          (0x508U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_26_27                          (0x50cU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_28_29                          (0x510U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_30_31                          (0x514U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_32_33                          (0x518U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_34_35                          (0x51cU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_36_37                          (0x520U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_38_39                          (0x524U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_40_41                          (0x528U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_42_43                          (0x52cU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_44_45                          (0x530U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_46_47                          (0x534U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_48_49                          (0x538U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_50_51                          (0x53cU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_52_53                          (0x540U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_54_55                          (0x544U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_56_57                          (0x548U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_58_59                          (0x54cU)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_60_61                          (0x550U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_62_63                          (0x554U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_0_1                            (0x558U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_2_3                            (0x55cU)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_4_5                            (0x560U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_6_7                            (0x564U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_8_9                            (0x568U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_10_11                          (0x56cU)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_12_13                          (0x570U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_14_15                          (0x574U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_16_17                          (0x578U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_18_19                          (0x57cU)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_0_1                            (0x580U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_2_3                            (0x584U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_4_5                            (0x588U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_6_7                            (0x58cU)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_8_9                            (0x590U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_10_11                          (0x594U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_12_13                          (0x598U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_14_15                          (0x59cU)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_16_17                          (0x5a0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_18_19                          (0x5a4U)
#define CTRL_CORE_INTR_DMA_OVS_DMARQ_IO_MUX                         (0x5acU)
#define CTRL_CORE_INTR_DMA_OVS_IRQ_IO_MUX                           (0x5b0U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_0                             (0x5b4U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_1                             (0x5b8U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_2                             (0x5bcU)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_3                             (0x5c0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_INTR_DMA_EVE_IRQ_0_1_SHIFT                                            (0U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_0_1_MASK                                             (0x000001ffU)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_0_1_SHIFT                                            (16U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_0_1_MASK                                             (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_2_3_SHIFT                                            (0U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_2_3_MASK                                             (0x000001ffU)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_2_3_SHIFT                                            (16U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_2_3_MASK                                             (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_4_5_SHIFT                                            (0U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_4_5_MASK                                             (0x000001ffU)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_4_5_SHIFT                                            (16U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_4_5_MASK                                             (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_6_7_SHIFT                                            (0U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_6_7_MASK                                             (0x000001ffU)

#define CTRL_CORE_INTR_DMA_EVE_IRQ_6_7_SHIFT                                            (16U)
#define CTRL_CORE_INTR_DMA_EVE_IRQ_6_7_MASK                                             (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_23_24_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_23_24_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_23_24_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_23_24_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_25_26_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_25_26_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_25_26_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_25_26_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_27_28_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_27_28_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_27_28_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_27_28_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_29_30_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_29_30_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_29_30_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_29_30_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_31_32_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_31_32_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_31_32_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_31_32_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_33_34_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_33_34_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_33_34_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_33_34_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_35_36_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_35_36_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_35_36_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_35_36_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_37_38_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_37_38_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_37_38_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_37_38_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_39_40_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_39_40_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_39_40_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_39_40_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_41_42_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_41_42_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_41_42_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_41_42_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_43_44_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_43_44_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_43_44_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_43_44_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_45_46_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_45_46_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_45_46_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_45_46_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_47_48_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_47_48_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_47_48_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_47_48_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_49_50_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_49_50_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_49_50_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_49_50_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_51_52_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_51_52_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_51_52_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_51_52_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_53_54_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_53_54_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_53_54_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_53_54_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_55_56_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_55_56_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_55_56_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_55_56_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_57_58_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_57_58_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_57_58_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_57_58_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_59_60_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_59_60_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_59_60_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_59_60_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_61_62_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_61_62_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_61_62_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_61_62_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_63_64_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_63_64_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_63_64_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_63_64_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_65_66_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_65_66_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_65_66_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_65_66_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_67_68_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_67_68_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_67_68_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_67_68_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_69_70_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_69_70_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_69_70_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_69_70_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_71_72_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_71_72_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_71_72_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_71_72_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_73_74_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_73_74_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_73_74_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_73_74_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_75_76_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_75_76_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_75_76_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_75_76_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_77_78_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_77_78_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_77_78_SHIFT                                          (16U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_77_78_MASK                                           (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_IPU_IRQ_79_80_SHIFT                                          (0U)
#define CTRL_CORE_INTR_DMA_IPU_IRQ_79_80_MASK                                           (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_32_33_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_32_33_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_32_33_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_32_33_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_34_35_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_34_35_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_34_35_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_34_35_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_36_37_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_36_37_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_36_37_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_36_37_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_38_39_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_38_39_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_38_39_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_38_39_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_40_41_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_40_41_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_40_41_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_40_41_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_42_43_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_42_43_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_42_43_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_42_43_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_44_45_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_44_45_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_44_45_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_44_45_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_46_47_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_46_47_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_46_47_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_46_47_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_48_49_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_48_49_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_48_49_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_48_49_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_50_51_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_50_51_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_50_51_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_50_51_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_52_53_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_52_53_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_52_53_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_52_53_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_54_55_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_54_55_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_54_55_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_54_55_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_56_57_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_56_57_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_56_57_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_56_57_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_58_59_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_58_59_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_58_59_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_58_59_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_60_61_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_60_61_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_60_61_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_60_61_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_62_63_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_62_63_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_62_63_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_62_63_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_64_65_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_64_65_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_64_65_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_64_65_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_66_67_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_66_67_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_66_67_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_66_67_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_68_69_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_68_69_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_68_69_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_68_69_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_70_71_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_70_71_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_70_71_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_70_71_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_72_73_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_72_73_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_72_73_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_72_73_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_74_75_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_74_75_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_74_75_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_74_75_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_76_77_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_76_77_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_76_77_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_76_77_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_78_79_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_78_79_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_78_79_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_78_79_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_80_81_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_80_81_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_80_81_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_80_81_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_82_83_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_82_83_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_82_83_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_82_83_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_84_85_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_84_85_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_84_85_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_84_85_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_86_87_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_86_87_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_86_87_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_86_87_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_88_89_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_88_89_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_88_89_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_88_89_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_90_91_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_90_91_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_90_91_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_90_91_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_92_93_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_92_93_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_92_93_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_92_93_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_94_95_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_94_95_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP1_IRQ_94_95_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP1_IRQ_94_95_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_32_33_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_32_33_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_32_33_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_32_33_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_34_35_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_34_35_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_34_35_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_34_35_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_36_37_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_36_37_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_36_37_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_36_37_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_38_39_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_38_39_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_38_39_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_38_39_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_40_41_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_40_41_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_40_41_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_40_41_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_42_43_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_42_43_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_42_43_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_42_43_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_44_45_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_44_45_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_44_45_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_44_45_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_46_47_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_46_47_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_46_47_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_46_47_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_48_49_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_48_49_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_48_49_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_48_49_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_50_51_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_50_51_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_50_51_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_50_51_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_52_53_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_52_53_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_52_53_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_52_53_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_54_55_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_54_55_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_54_55_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_54_55_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_56_57_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_56_57_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_56_57_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_56_57_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_58_59_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_58_59_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_58_59_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_58_59_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_60_61_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_60_61_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_60_61_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_60_61_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_62_63_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_62_63_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_62_63_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_62_63_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_64_65_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_64_65_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_64_65_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_64_65_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_66_67_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_66_67_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_66_67_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_66_67_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_68_69_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_68_69_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_68_69_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_68_69_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_70_71_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_70_71_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_70_71_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_70_71_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_72_73_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_72_73_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_72_73_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_72_73_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_74_75_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_74_75_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_74_75_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_74_75_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_76_77_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_76_77_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_76_77_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_76_77_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_78_79_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_78_79_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_78_79_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_78_79_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_80_81_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_80_81_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_80_81_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_80_81_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_82_83_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_82_83_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_82_83_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_82_83_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_84_85_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_84_85_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_84_85_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_84_85_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_86_87_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_86_87_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_86_87_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_86_87_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_88_89_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_88_89_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_88_89_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_88_89_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_90_91_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_90_91_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_90_91_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_90_91_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_92_93_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_92_93_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_92_93_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_92_93_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_94_95_SHIFT                                         (0U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_94_95_MASK                                          (0x000001ffU)

#define CTRL_CORE_INTR_DMA_DSP2_IRQ_94_95_SHIFT                                         (16U)
#define CTRL_CORE_INTR_DMA_DSP2_IRQ_94_95_MASK                                          (0x01ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_0_1_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_0_1_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_0_1_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_0_1_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_2_3_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_2_3_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_2_3_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_2_3_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_4_5_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_4_5_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_4_5_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_4_5_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_6_7_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_6_7_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_6_7_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_6_7_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_8_9_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_8_9_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_8_9_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_8_9_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_10_11_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_10_11_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_10_11_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_10_11_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_12_13_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_12_13_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_12_13_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_12_13_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_14_15_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_14_15_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_14_15_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_14_15_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_16_17_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_16_17_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_16_17_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_16_17_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_18_19_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_18_19_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_18_19_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_18_19_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_20_21_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_20_21_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_20_21_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_20_21_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_22_23_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_22_23_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_22_23_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_22_23_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_24_25_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_24_25_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_24_25_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_24_25_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_26_27_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_26_27_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_26_27_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_26_27_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_28_29_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_28_29_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_28_29_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_28_29_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_30_31_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_30_31_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_30_31_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_30_31_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_32_33_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_32_33_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_32_33_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_32_33_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_34_35_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_34_35_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_34_35_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_34_35_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_36_37_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_36_37_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_36_37_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_36_37_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_38_39_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_38_39_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_38_39_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_38_39_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_40_41_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_40_41_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_40_41_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_40_41_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_42_43_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_42_43_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_42_43_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_42_43_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_44_45_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_44_45_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_44_45_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_44_45_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_46_47_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_46_47_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_46_47_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_46_47_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_48_49_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_48_49_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_48_49_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_48_49_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_50_51_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_50_51_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_50_51_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_50_51_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_52_53_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_52_53_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_52_53_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_52_53_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_54_55_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_54_55_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_54_55_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_54_55_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_56_57_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_56_57_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_56_57_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_56_57_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_58_59_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_58_59_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_58_59_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_58_59_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_60_61_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_60_61_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_60_61_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_60_61_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_62_63_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_62_63_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_EDMA_DREQ_62_63_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_EDMA_DREQ_62_63_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_0_1_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_0_1_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_0_1_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_0_1_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_2_3_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_2_3_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_2_3_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_2_3_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_4_5_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_4_5_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_4_5_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_4_5_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_6_7_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_6_7_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_6_7_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_6_7_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_8_9_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_8_9_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_8_9_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_8_9_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_10_11_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_10_11_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_10_11_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_10_11_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_12_13_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_12_13_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_12_13_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_12_13_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_14_15_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_14_15_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_14_15_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_14_15_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_16_17_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_16_17_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_16_17_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_16_17_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_18_19_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_18_19_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP1_DREQ_18_19_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP1_DREQ_18_19_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_0_1_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_0_1_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_0_1_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_0_1_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_2_3_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_2_3_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_2_3_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_2_3_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_4_5_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_4_5_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_4_5_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_4_5_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_6_7_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_6_7_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_6_7_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_6_7_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_8_9_IRQ_SHIFT                                      (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_8_9_IRQ_MASK                                       (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_8_9_IRQ_SHIFT                                      (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_8_9_IRQ_MASK                                       (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_10_11_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_10_11_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_10_11_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_10_11_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_12_13_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_12_13_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_12_13_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_12_13_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_14_15_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_14_15_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_14_15_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_14_15_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_16_17_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_16_17_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_16_17_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_16_17_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_18_19_IRQ_SHIFT                                    (0U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_18_19_IRQ_MASK                                     (0x000000ffU)

#define CTRL_CORE_INTR_DMA_DSP2_DREQ_18_19_IRQ_SHIFT                                    (16U)
#define CTRL_CORE_INTR_DMA_DSP2_DREQ_18_19_IRQ_MASK                                     (0x00ff0000U)

#define CTRL_CORE_INTR_DMA_OVS_DMARQ_IO_MUX_1_SHIFT                                     (0U)
#define CTRL_CORE_INTR_DMA_OVS_DMARQ_IO_MUX_1_MASK                                      (0x000000ffU)

#define CTRL_CORE_INTR_DMA_OVS_DMARQ_IO_MUX_2_SHIFT                                     (8U)
#define CTRL_CORE_INTR_DMA_OVS_DMARQ_IO_MUX_2_MASK                                      (0x0000ff00U)

#define CTRL_CORE_INTR_DMA_OVS_IRQ_IO_MUX_1_SHIFT                                       (0U)
#define CTRL_CORE_INTR_DMA_OVS_IRQ_IO_MUX_1_MASK                                        (0x000001ffU)

#define CTRL_CORE_INTR_DMA_OVS_IRQ_IO_MUX_2_SHIFT                                       (9U)
#define CTRL_CORE_INTR_DMA_OVS_IRQ_IO_MUX_2_MASK                                        (0x0003fe00U)

#define CTRL_CORE_INTR_DMA_ESM_GROUP1_0_IRQ_SHIFT                                       (0U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_0_IRQ_MASK                                        (0x000001ffU)

#define CTRL_CORE_INTR_DMA_ESM_GROUP1_1_IRQ_SHIFT                                       (0U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_1_IRQ_MASK                                        (0x000001ffU)

#define CTRL_CORE_INTR_DMA_ESM_GROUP1_2_IRQ_SHIFT                                       (0U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_2_IRQ_MASK                                        (0x000001ffU)

#define CTRL_CORE_INTR_DMA_ESM_GROUP1_3_SHIFT                                           (0U)
#define CTRL_CORE_INTR_DMA_ESM_GROUP1_3_MASK                                            (0x000000ffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_INTR_DMA_H_ */

