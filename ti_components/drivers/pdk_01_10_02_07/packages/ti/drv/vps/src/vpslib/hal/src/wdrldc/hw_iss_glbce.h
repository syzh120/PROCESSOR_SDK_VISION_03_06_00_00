/*
* hw_iss_glbce.h
*
* Register-level header file for ISS_GLBCE
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
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

#ifndef HW_ISS_GLBCE_H_
#define HW_ISS_GLBCE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define ISS_GLBCE_CFG                                               (0x0U)
#define ISS_GLBCE_MODE                                              (0x4U)
#define ISS_GLBCE_CONTROL0                                          (0x8U)
#define ISS_GLBCE_CONTROL1                                          (0xcU)
#define ISS_GLBCE_BLACK_LEVEL                                       (0x10U)
#define ISS_GLBCE_WHITE_LEVEL                                       (0x14U)
#define ISS_GLBCE_VARIANCE                                          (0x18U)
#define ISS_GLBCE_LIMIT_AMPL                                        (0x1cU)
#define ISS_GLBCE_DITHER                                            (0x20U)
#define ISS_GLBCE_SLOPE_MAX                                         (0x24U)
#define ISS_GLBCE_SLOPE_MIN                                         (0x28U)
#define ISS_GLBCE_LUT_FI_00                                         (0x2cU)
#define ISS_GLBCE_LUT_FI_01                                         (0x30U)
#define ISS_GLBCE_LUT_FI_02                                         (0x34U)
#define ISS_GLBCE_LUT_FI_03                                         (0x38U)
#define ISS_GLBCE_LUT_FI_04                                         (0x3cU)
#define ISS_GLBCE_LUT_FI_05                                         (0x40U)
#define ISS_GLBCE_LUT_FI_06                                         (0x44U)
#define ISS_GLBCE_LUT_FI_07                                         (0x48U)
#define ISS_GLBCE_LUT_FI_08                                         (0x4cU)
#define ISS_GLBCE_LUT_FI_09                                         (0x50U)
#define ISS_GLBCE_LUT_FI_10                                         (0x54U)
#define ISS_GLBCE_LUT_FI_11                                         (0x58U)
#define ISS_GLBCE_LUT_FI_12                                         (0x5cU)
#define ISS_GLBCE_LUT_FI_13                                         (0x60U)
#define ISS_GLBCE_LUT_FI_14                                         (0x64U)
#define ISS_GLBCE_LUT_FI_15                                         (0x68U)
#define ISS_GLBCE_LUT_FI_16                                         (0x6cU)
#define ISS_GLBCE_LUT_FI_17                                         (0x70U)
#define ISS_GLBCE_LUT_FI_18                                         (0x74U)
#define ISS_GLBCE_LUT_FI_19                                         (0x78U)
#define ISS_GLBCE_LUT_FI_20                                         (0x7cU)
#define ISS_GLBCE_LUT_FI_21                                         (0x80U)
#define ISS_GLBCE_LUT_FI_22                                         (0x84U)
#define ISS_GLBCE_LUT_FI_23                                         (0x88U)
#define ISS_GLBCE_LUT_FI_24                                         (0x8cU)
#define ISS_GLBCE_LUT_FI_25                                         (0x90U)
#define ISS_GLBCE_LUT_FI_26                                         (0x94U)
#define ISS_GLBCE_LUT_FI_27                                         (0x98U)
#define ISS_GLBCE_LUT_FI_28                                         (0x9cU)
#define ISS_GLBCE_LUT_FI_29                                         (0xa0U)
#define ISS_GLBCE_LUT_FI_30                                         (0xa4U)
#define ISS_GLBCE_LUT_FI_31                                         (0xa8U)
#define ISS_GLBCE_LUT_FI_32                                         (0xacU)
#define ISS_GLBCE_FORMAT_CONTROL_REG0                               (0xb0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1                               (0xb4U)
#define ISS_GLBCE_FRAME_WIDTH                                       (0xb8U)
#define ISS_GLBCE_FRAME_HEIGHT                                      (0xbcU)
#define ISS_GLBCE_STRENGTH_IR                                       (0xc0U)
#define ISS_GLBCE_PERCEPT_EN                                        (0xc4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_00                                (0xc8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_01                                (0xccU)
#define ISS_GLBCE_REV_PERCEPT_LUT_02                                (0xd0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_03                                (0xd4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_04                                (0xd8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_05                                (0xdcU)
#define ISS_GLBCE_REV_PERCEPT_LUT_06                                (0xe0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_07                                (0xe4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_08                                (0xe8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_09                                (0xecU)
#define ISS_GLBCE_REV_PERCEPT_LUT_10                                (0xf0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_11                                (0xf4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_12                                (0xf8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_13                                (0xfcU)
#define ISS_GLBCE_REV_PERCEPT_LUT_14                                (0x100U)
#define ISS_GLBCE_REV_PERCEPT_LUT_15                                (0x104U)
#define ISS_GLBCE_REV_PERCEPT_LUT_16                                (0x108U)
#define ISS_GLBCE_REV_PERCEPT_LUT_17                                (0x10cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_18                                (0x110U)
#define ISS_GLBCE_REV_PERCEPT_LUT_19                                (0x114U)
#define ISS_GLBCE_REV_PERCEPT_LUT_20                                (0x118U)
#define ISS_GLBCE_REV_PERCEPT_LUT_21                                (0x11cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_22                                (0x120U)
#define ISS_GLBCE_REV_PERCEPT_LUT_23                                (0x124U)
#define ISS_GLBCE_REV_PERCEPT_LUT_24                                (0x128U)
#define ISS_GLBCE_REV_PERCEPT_LUT_25                                (0x12cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_26                                (0x130U)
#define ISS_GLBCE_REV_PERCEPT_LUT_27                                (0x134U)
#define ISS_GLBCE_REV_PERCEPT_LUT_28                                (0x138U)
#define ISS_GLBCE_REV_PERCEPT_LUT_29                                (0x13cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_30                                (0x140U)
#define ISS_GLBCE_REV_PERCEPT_LUT_31                                (0x144U)
#define ISS_GLBCE_REV_PERCEPT_LUT_32                                (0x148U)
#define ISS_GLBCE_REV_PERCEPT_LUT_33                                (0x14cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_34                                (0x150U)
#define ISS_GLBCE_REV_PERCEPT_LUT_35                                (0x154U)
#define ISS_GLBCE_REV_PERCEPT_LUT_36                                (0x158U)
#define ISS_GLBCE_REV_PERCEPT_LUT_37                                (0x15cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_38                                (0x160U)
#define ISS_GLBCE_REV_PERCEPT_LUT_39                                (0x164U)
#define ISS_GLBCE_REV_PERCEPT_LUT_40                                (0x168U)
#define ISS_GLBCE_REV_PERCEPT_LUT_41                                (0x16cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_42                                (0x170U)
#define ISS_GLBCE_REV_PERCEPT_LUT_43                                (0x174U)
#define ISS_GLBCE_REV_PERCEPT_LUT_44                                (0x178U)
#define ISS_GLBCE_REV_PERCEPT_LUT_45                                (0x17cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_46                                (0x180U)
#define ISS_GLBCE_REV_PERCEPT_LUT_47                                (0x184U)
#define ISS_GLBCE_REV_PERCEPT_LUT_48                                (0x188U)
#define ISS_GLBCE_REV_PERCEPT_LUT_49                                (0x18cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_50                                (0x190U)
#define ISS_GLBCE_REV_PERCEPT_LUT_51                                (0x194U)
#define ISS_GLBCE_REV_PERCEPT_LUT_52                                (0x198U)
#define ISS_GLBCE_REV_PERCEPT_LUT_53                                (0x19cU)
#define ISS_GLBCE_REV_PERCEPT_LUT_54                                (0x1a0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_55                                (0x1a4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_56                                (0x1a8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_57                                (0x1acU)
#define ISS_GLBCE_REV_PERCEPT_LUT_58                                (0x1b0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_59                                (0x1b4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_60                                (0x1b8U)
#define ISS_GLBCE_REV_PERCEPT_LUT_61                                (0x1bcU)
#define ISS_GLBCE_REV_PERCEPT_LUT_62                                (0x1c0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_63                                (0x1c4U)
#define ISS_GLBCE_REV_PERCEPT_LUT_64                                (0x1c8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_00                                (0x1ccU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_01                                (0x1d0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_02                                (0x1d4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_03                                (0x1d8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_04                                (0x1dcU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_05                                (0x1e0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_06                                (0x1e4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_07                                (0x1e8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_08                                (0x1ecU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_09                                (0x1f0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_10                                (0x1f4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_11                                (0x1f8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_12                                (0x1fcU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_13                                (0x200U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_14                                (0x204U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_15                                (0x208U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_16                                (0x20cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_17                                (0x210U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_18                                (0x214U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_19                                (0x218U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_20                                (0x21cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_21                                (0x220U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_22                                (0x224U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_23                                (0x228U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_24                                (0x22cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_25                                (0x230U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_26                                (0x234U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_27                                (0x238U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_28                                (0x23cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_29                                (0x240U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_30                                (0x244U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_31                                (0x248U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_32                                (0x24cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_33                                (0x250U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_34                                (0x254U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_35                                (0x258U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_36                                (0x25cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_37                                (0x260U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_38                                (0x264U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_39                                (0x268U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_40                                (0x26cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_41                                (0x270U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_42                                (0x274U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_43                                (0x278U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_44                                (0x27cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_45                                (0x280U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_46                                (0x284U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_47                                (0x288U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_48                                (0x28cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_49                                (0x290U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_50                                (0x294U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_51                                (0x298U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_52                                (0x29cU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_53                                (0x2a0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_54                                (0x2a4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_55                                (0x2a8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_56                                (0x2acU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_57                                (0x2b0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_58                                (0x2b4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_59                                (0x2b8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_60                                (0x2bcU)
#define ISS_GLBCE_FWD_PERCEPT_LUT_61                                (0x2c0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_62                                (0x2c4U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_63                                (0x2c8U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_64                                (0x2ccU)
#define ISS_GLBCE_WDR_GAMMA_EN                                      (0x2d0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_00                                  (0x2d4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_01                                  (0x2d8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_02                                  (0x2dcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_03                                  (0x2e0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_04                                  (0x2e4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_05                                  (0x2e8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_06                                  (0x2ecU)
#define ISS_GLBCE_WDR_GAMMA_LUT_07                                  (0x2f0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_08                                  (0x2f4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_09                                  (0x2f8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_10                                  (0x2fcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_11                                  (0x300U)
#define ISS_GLBCE_WDR_GAMMA_LUT_12                                  (0x304U)
#define ISS_GLBCE_WDR_GAMMA_LUT_13                                  (0x308U)
#define ISS_GLBCE_WDR_GAMMA_LUT_14                                  (0x30cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_15                                  (0x310U)
#define ISS_GLBCE_WDR_GAMMA_LUT_16                                  (0x314U)
#define ISS_GLBCE_WDR_GAMMA_LUT_17                                  (0x318U)
#define ISS_GLBCE_WDR_GAMMA_LUT_18                                  (0x31cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_19                                  (0x320U)
#define ISS_GLBCE_WDR_GAMMA_LUT_20                                  (0x324U)
#define ISS_GLBCE_WDR_GAMMA_LUT_21                                  (0x328U)
#define ISS_GLBCE_WDR_GAMMA_LUT_22                                  (0x32cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_23                                  (0x330U)
#define ISS_GLBCE_WDR_GAMMA_LUT_24                                  (0x334U)
#define ISS_GLBCE_WDR_GAMMA_LUT_25                                  (0x338U)
#define ISS_GLBCE_WDR_GAMMA_LUT_26                                  (0x33cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_27                                  (0x340U)
#define ISS_GLBCE_WDR_GAMMA_LUT_28                                  (0x344U)
#define ISS_GLBCE_WDR_GAMMA_LUT_29                                  (0x348U)
#define ISS_GLBCE_WDR_GAMMA_LUT_30                                  (0x34cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_31                                  (0x350U)
#define ISS_GLBCE_WDR_GAMMA_LUT_32                                  (0x354U)
#define ISS_GLBCE_WDR_GAMMA_LUT_33                                  (0x358U)
#define ISS_GLBCE_WDR_GAMMA_LUT_34                                  (0x35cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_35                                  (0x360U)
#define ISS_GLBCE_WDR_GAMMA_LUT_36                                  (0x364U)
#define ISS_GLBCE_WDR_GAMMA_LUT_37                                  (0x368U)
#define ISS_GLBCE_WDR_GAMMA_LUT_38                                  (0x36cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_39                                  (0x370U)
#define ISS_GLBCE_WDR_GAMMA_LUT_40                                  (0x374U)
#define ISS_GLBCE_WDR_GAMMA_LUT_41                                  (0x378U)
#define ISS_GLBCE_WDR_GAMMA_LUT_42                                  (0x37cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_43                                  (0x380U)
#define ISS_GLBCE_WDR_GAMMA_LUT_44                                  (0x384U)
#define ISS_GLBCE_WDR_GAMMA_LUT_45                                  (0x388U)
#define ISS_GLBCE_WDR_GAMMA_LUT_46                                  (0x38cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_47                                  (0x390U)
#define ISS_GLBCE_WDR_GAMMA_LUT_48                                  (0x394U)
#define ISS_GLBCE_WDR_GAMMA_LUT_49                                  (0x398U)
#define ISS_GLBCE_WDR_GAMMA_LUT_50                                  (0x39cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_51                                  (0x3a0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_52                                  (0x3a4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_53                                  (0x3a8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_54                                  (0x3acU)
#define ISS_GLBCE_WDR_GAMMA_LUT_55                                  (0x3b0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_56                                  (0x3b4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_57                                  (0x3b8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_58                                  (0x3bcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_59                                  (0x3c0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_60                                  (0x3c4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_61                                  (0x3c8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_62                                  (0x3ccU)
#define ISS_GLBCE_WDR_GAMMA_LUT_63                                  (0x3d0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_64                                  (0x3d4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_65                                  (0x3d8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_66                                  (0x3dcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_67                                  (0x3e0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_68                                  (0x3e4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_69                                  (0x3e8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_70                                  (0x3ecU)
#define ISS_GLBCE_WDR_GAMMA_LUT_71                                  (0x3f0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_72                                  (0x3f4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_73                                  (0x3f8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_74                                  (0x3fcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_75                                  (0x400U)
#define ISS_GLBCE_WDR_GAMMA_LUT_76                                  (0x404U)
#define ISS_GLBCE_WDR_GAMMA_LUT_77                                  (0x408U)
#define ISS_GLBCE_WDR_GAMMA_LUT_78                                  (0x40cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_79                                  (0x410U)
#define ISS_GLBCE_WDR_GAMMA_LUT_80                                  (0x414U)
#define ISS_GLBCE_WDR_GAMMA_LUT_81                                  (0x418U)
#define ISS_GLBCE_WDR_GAMMA_LUT_82                                  (0x41cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_83                                  (0x420U)
#define ISS_GLBCE_WDR_GAMMA_LUT_84                                  (0x424U)
#define ISS_GLBCE_WDR_GAMMA_LUT_85                                  (0x428U)
#define ISS_GLBCE_WDR_GAMMA_LUT_86                                  (0x42cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_87                                  (0x430U)
#define ISS_GLBCE_WDR_GAMMA_LUT_88                                  (0x434U)
#define ISS_GLBCE_WDR_GAMMA_LUT_89                                  (0x438U)
#define ISS_GLBCE_WDR_GAMMA_LUT_90                                  (0x43cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_91                                  (0x440U)
#define ISS_GLBCE_WDR_GAMMA_LUT_92                                  (0x444U)
#define ISS_GLBCE_WDR_GAMMA_LUT_93                                  (0x448U)
#define ISS_GLBCE_WDR_GAMMA_LUT_94                                  (0x44cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_95                                  (0x450U)
#define ISS_GLBCE_WDR_GAMMA_LUT_96                                  (0x454U)
#define ISS_GLBCE_WDR_GAMMA_LUT_97                                  (0x458U)
#define ISS_GLBCE_WDR_GAMMA_LUT_98                                  (0x45cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_99                                  (0x460U)
#define ISS_GLBCE_WDR_GAMMA_LUT_100                                 (0x464U)
#define ISS_GLBCE_WDR_GAMMA_LUT_101                                 (0x468U)
#define ISS_GLBCE_WDR_GAMMA_LUT_102                                 (0x46cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_103                                 (0x470U)
#define ISS_GLBCE_WDR_GAMMA_LUT_104                                 (0x474U)
#define ISS_GLBCE_WDR_GAMMA_LUT_105                                 (0x478U)
#define ISS_GLBCE_WDR_GAMMA_LUT_106                                 (0x47cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_107                                 (0x480U)
#define ISS_GLBCE_WDR_GAMMA_LUT_108                                 (0x484U)
#define ISS_GLBCE_WDR_GAMMA_LUT_109                                 (0x488U)
#define ISS_GLBCE_WDR_GAMMA_LUT_110                                 (0x48cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_111                                 (0x490U)
#define ISS_GLBCE_WDR_GAMMA_LUT_112                                 (0x494U)
#define ISS_GLBCE_WDR_GAMMA_LUT_113                                 (0x498U)
#define ISS_GLBCE_WDR_GAMMA_LUT_114                                 (0x49cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_115                                 (0x4a0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_116                                 (0x4a4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_117                                 (0x4a8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_118                                 (0x4acU)
#define ISS_GLBCE_WDR_GAMMA_LUT_119                                 (0x4b0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_120                                 (0x4b4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_121                                 (0x4b8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_122                                 (0x4bcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_123                                 (0x4c0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_124                                 (0x4c4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_125                                 (0x4c8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_126                                 (0x4ccU)
#define ISS_GLBCE_WDR_GAMMA_LUT_127                                 (0x4d0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_128                                 (0x4d4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_129                                 (0x4d8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_130                                 (0x4dcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_131                                 (0x4e0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_132                                 (0x4e4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_133                                 (0x4e8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_134                                 (0x4ecU)
#define ISS_GLBCE_WDR_GAMMA_LUT_135                                 (0x4f0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_136                                 (0x4f4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_137                                 (0x4f8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_138                                 (0x4fcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_139                                 (0x500U)
#define ISS_GLBCE_WDR_GAMMA_LUT_140                                 (0x504U)
#define ISS_GLBCE_WDR_GAMMA_LUT_141                                 (0x508U)
#define ISS_GLBCE_WDR_GAMMA_LUT_142                                 (0x50cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_143                                 (0x510U)
#define ISS_GLBCE_WDR_GAMMA_LUT_144                                 (0x514U)
#define ISS_GLBCE_WDR_GAMMA_LUT_145                                 (0x518U)
#define ISS_GLBCE_WDR_GAMMA_LUT_146                                 (0x51cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_147                                 (0x520U)
#define ISS_GLBCE_WDR_GAMMA_LUT_148                                 (0x524U)
#define ISS_GLBCE_WDR_GAMMA_LUT_149                                 (0x528U)
#define ISS_GLBCE_WDR_GAMMA_LUT_150                                 (0x52cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_151                                 (0x530U)
#define ISS_GLBCE_WDR_GAMMA_LUT_152                                 (0x534U)
#define ISS_GLBCE_WDR_GAMMA_LUT_153                                 (0x538U)
#define ISS_GLBCE_WDR_GAMMA_LUT_154                                 (0x53cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_155                                 (0x540U)
#define ISS_GLBCE_WDR_GAMMA_LUT_156                                 (0x544U)
#define ISS_GLBCE_WDR_GAMMA_LUT_157                                 (0x548U)
#define ISS_GLBCE_WDR_GAMMA_LUT_158                                 (0x54cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_159                                 (0x550U)
#define ISS_GLBCE_WDR_GAMMA_LUT_160                                 (0x554U)
#define ISS_GLBCE_WDR_GAMMA_LUT_161                                 (0x558U)
#define ISS_GLBCE_WDR_GAMMA_LUT_162                                 (0x55cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_163                                 (0x560U)
#define ISS_GLBCE_WDR_GAMMA_LUT_164                                 (0x564U)
#define ISS_GLBCE_WDR_GAMMA_LUT_165                                 (0x568U)
#define ISS_GLBCE_WDR_GAMMA_LUT_166                                 (0x56cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_167                                 (0x570U)
#define ISS_GLBCE_WDR_GAMMA_LUT_168                                 (0x574U)
#define ISS_GLBCE_WDR_GAMMA_LUT_169                                 (0x578U)
#define ISS_GLBCE_WDR_GAMMA_LUT_170                                 (0x57cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_171                                 (0x580U)
#define ISS_GLBCE_WDR_GAMMA_LUT_172                                 (0x584U)
#define ISS_GLBCE_WDR_GAMMA_LUT_173                                 (0x588U)
#define ISS_GLBCE_WDR_GAMMA_LUT_174                                 (0x58cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_175                                 (0x590U)
#define ISS_GLBCE_WDR_GAMMA_LUT_176                                 (0x594U)
#define ISS_GLBCE_WDR_GAMMA_LUT_177                                 (0x598U)
#define ISS_GLBCE_WDR_GAMMA_LUT_178                                 (0x59cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_179                                 (0x5a0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_180                                 (0x5a4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_181                                 (0x5a8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_182                                 (0x5acU)
#define ISS_GLBCE_WDR_GAMMA_LUT_183                                 (0x5b0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_184                                 (0x5b4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_185                                 (0x5b8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_186                                 (0x5bcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_187                                 (0x5c0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_188                                 (0x5c4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_189                                 (0x5c8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_190                                 (0x5ccU)
#define ISS_GLBCE_WDR_GAMMA_LUT_191                                 (0x5d0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_192                                 (0x5d4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_193                                 (0x5d8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_194                                 (0x5dcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_195                                 (0x5e0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_196                                 (0x5e4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_197                                 (0x5e8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_198                                 (0x5ecU)
#define ISS_GLBCE_WDR_GAMMA_LUT_199                                 (0x5f0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_200                                 (0x5f4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_201                                 (0x5f8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_202                                 (0x5fcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_203                                 (0x600U)
#define ISS_GLBCE_WDR_GAMMA_LUT_204                                 (0x604U)
#define ISS_GLBCE_WDR_GAMMA_LUT_205                                 (0x608U)
#define ISS_GLBCE_WDR_GAMMA_LUT_206                                 (0x60cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_207                                 (0x610U)
#define ISS_GLBCE_WDR_GAMMA_LUT_208                                 (0x614U)
#define ISS_GLBCE_WDR_GAMMA_LUT_209                                 (0x618U)
#define ISS_GLBCE_WDR_GAMMA_LUT_210                                 (0x61cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_211                                 (0x620U)
#define ISS_GLBCE_WDR_GAMMA_LUT_212                                 (0x624U)
#define ISS_GLBCE_WDR_GAMMA_LUT_213                                 (0x628U)
#define ISS_GLBCE_WDR_GAMMA_LUT_214                                 (0x62cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_215                                 (0x630U)
#define ISS_GLBCE_WDR_GAMMA_LUT_216                                 (0x634U)
#define ISS_GLBCE_WDR_GAMMA_LUT_217                                 (0x638U)
#define ISS_GLBCE_WDR_GAMMA_LUT_218                                 (0x63cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_219                                 (0x640U)
#define ISS_GLBCE_WDR_GAMMA_LUT_220                                 (0x644U)
#define ISS_GLBCE_WDR_GAMMA_LUT_221                                 (0x648U)
#define ISS_GLBCE_WDR_GAMMA_LUT_222                                 (0x64cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_223                                 (0x650U)
#define ISS_GLBCE_WDR_GAMMA_LUT_224                                 (0x654U)
#define ISS_GLBCE_WDR_GAMMA_LUT_225                                 (0x658U)
#define ISS_GLBCE_WDR_GAMMA_LUT_226                                 (0x65cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_227                                 (0x660U)
#define ISS_GLBCE_WDR_GAMMA_LUT_228                                 (0x664U)
#define ISS_GLBCE_WDR_GAMMA_LUT_229                                 (0x668U)
#define ISS_GLBCE_WDR_GAMMA_LUT_230                                 (0x66cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_231                                 (0x670U)
#define ISS_GLBCE_WDR_GAMMA_LUT_232                                 (0x674U)
#define ISS_GLBCE_WDR_GAMMA_LUT_233                                 (0x678U)
#define ISS_GLBCE_WDR_GAMMA_LUT_234                                 (0x67cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_235                                 (0x680U)
#define ISS_GLBCE_WDR_GAMMA_LUT_236                                 (0x684U)
#define ISS_GLBCE_WDR_GAMMA_LUT_237                                 (0x688U)
#define ISS_GLBCE_WDR_GAMMA_LUT_238                                 (0x68cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_239                                 (0x690U)
#define ISS_GLBCE_WDR_GAMMA_LUT_240                                 (0x694U)
#define ISS_GLBCE_WDR_GAMMA_LUT_241                                 (0x698U)
#define ISS_GLBCE_WDR_GAMMA_LUT_242                                 (0x69cU)
#define ISS_GLBCE_WDR_GAMMA_LUT_243                                 (0x6a0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_244                                 (0x6a4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_245                                 (0x6a8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_246                                 (0x6acU)
#define ISS_GLBCE_WDR_GAMMA_LUT_247                                 (0x6b0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_248                                 (0x6b4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_249                                 (0x6b8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_250                                 (0x6bcU)
#define ISS_GLBCE_WDR_GAMMA_LUT_251                                 (0x6c0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_252                                 (0x6c4U)
#define ISS_GLBCE_WDR_GAMMA_LUT_253                                 (0x6c8U)
#define ISS_GLBCE_WDR_GAMMA_LUT_254                                 (0x6ccU)
#define ISS_GLBCE_WDR_GAMMA_LUT_255                                 (0x6d0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_256                                 (0x6d4U)
#define ISS_GLBCE_TILE_OUT_POS                                      (0x6d8U)
#define ISS_GLBCE_TILE_OUT_SIZE                                     (0x6e0U)
#define ISS_GLBCE_TILE_CONTROL                                      (0x6e8U)
#define ISS_GLBCE_OUTPUT_FLAGS                                      (0x6ecU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISS_GLBCE_CFG_SWRST_SHIFT                                                       (0U)
#define ISS_GLBCE_CFG_SWRST_MASK                                                        (0x00000001U)
#define ISS_GLBCE_CFG_SWRST_ON                                                           (1U)
#define ISS_GLBCE_CFG_SWRST_OFF                                                          (0U)

#define ISS_GLBCE_MODE_OST_SHIFT                                                        (0U)
#define ISS_GLBCE_MODE_OST_MASK                                                         (0x00000001U)
#define ISS_GLBCE_MODE_OST_CONTINUOUT                                                    (0U)
#define ISS_GLBCE_MODE_OST_ONE_SHOT                                                      (1U)

#define ISS_GLBCE_CONTROL0_ONOFF_SHIFT                                                  (0U)
#define ISS_GLBCE_CONTROL0_ONOFF_MASK                                                   (0x00000001U)
#define ISS_GLBCE_CONTROL0_ONOFF_OFF                                                     (0U)
#define ISS_GLBCE_CONTROL0_ONOFF_ON                                                      (1U)

#define ISS_GLBCE_CONTROL0_MB_SHIFT                                                     (3U)
#define ISS_GLBCE_CONTROL0_MB_MASK                                                      (0x00000008U)
#define ISS_GLBCE_CONTROL0_MB_ALGORITHM2                                                 (1U)
#define ISS_GLBCE_CONTROL0_MB_ALGORITHM1                                                 (0U)

#define ISS_GLBCE_CONTROL0_CCTL_SHIFT                                                   (4U)
#define ISS_GLBCE_CONTROL0_CCTL_MASK                                                    (0x00000010U)

#define ISS_GLBCE_BLACK_LEVEL_VAL_SHIFT                                                 (0U)
#define ISS_GLBCE_BLACK_LEVEL_VAL_MASK                                                  (0x0000ffffU)

#define ISS_GLBCE_WHITE_LEVEL_VAL_SHIFT                                                 (0U)
#define ISS_GLBCE_WHITE_LEVEL_VAL_MASK                                                  (0x0000ffffU)

#define ISS_GLBCE_VARIANCE_VARIANCESPACE_SHIFT                                          (0U)
#define ISS_GLBCE_VARIANCE_VARIANCESPACE_MASK                                           (0x0000000fU)

#define ISS_GLBCE_VARIANCE_VARIANCEINTENSITY_SHIFT                                      (4U)
#define ISS_GLBCE_VARIANCE_VARIANCEINTENSITY_MASK                                       (0x000000f0U)

#define ISS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_SHIFT                               (0U)
#define ISS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MASK                                (0x0000000fU)

#define ISS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_SHIFT                             (4U)
#define ISS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MASK                              (0x000000f0U)

#define ISS_GLBCE_DITHER_SHIFT                                                          (0U)
#define ISS_GLBCE_DITHER_MASK                                                           (0x00000007U)
#define ISS_GLBCE_DITHER_NO                                                              (0U)
#define ISS_GLBCE_DITHER_ONE_LSB                                                         (1U)
#define ISS_GLBCE_DITHER_TWO_LSBS                                                        (2U)
#define ISS_GLBCE_DITHER_THREE_LSBS                                                      (3U)
#define ISS_GLBCE_DITHER_FOUR_LSBS                                                       (4U)

#define ISS_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_SHIFT                                         (0U)
#define ISS_GLBCE_SLOPE_MAX_SLOPEMAXLIMIT_MASK                                          (0x000000ffU)

#define ISS_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_SHIFT                                         (0U)
#define ISS_GLBCE_SLOPE_MIN_SLOPEMINLIMIT_MASK                                          (0x000000ffU)

#define ISS_GLBCE_LUT_FI_00_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_00_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_01_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_01_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_02_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_02_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_03_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_03_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_04_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_04_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_05_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_05_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_06_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_06_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_07_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_07_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_08_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_08_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_09_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_09_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_10_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_10_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_11_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_11_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_12_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_12_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_13_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_13_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_14_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_14_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_15_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_15_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_16_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_16_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_17_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_17_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_18_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_18_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_19_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_19_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_20_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_20_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_21_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_21_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_22_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_22_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_23_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_23_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_24_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_24_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_25_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_25_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_26_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_26_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_27_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_27_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_28_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_28_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_29_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_29_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_30_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_30_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_31_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_31_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_LUT_FI_32_VAL_SHIFT                                                   (0U)
#define ISS_GLBCE_LUT_FI_32_VAL_MASK                                                    (0x0000ffffU)

#define ISS_GLBCE_FORMAT_CONTROL_REG0_DATAFORMAT_SHIFT                                  (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG0_DATAFORMAT_MASK                                   (0x00000003U)

#define ISS_GLBCE_FORMAT_CONTROL_REG1_HSPOL_SHIFT                                       (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_HSPOL_MASK                                        (0x00000001U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_HSPOL_RISING                                       (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_HSPOL_FALLING                                      (1U)

#define ISS_GLBCE_FORMAT_CONTROL_REG1_VSPOL_SHIFT                                       (1U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_VSPOL_MASK                                        (0x00000002U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_VSPOL_RISING                                       (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_VSPOL_FALLING                                      (1U)

#define ISS_GLBCE_FORMAT_CONTROL_REG1_FCMODE_SHIFT                                      (4U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_FCMODE_MASK                                       (0x00000030U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_FCMODE_INTERNAL                                    (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_FCMODE_VSYNC                                       (1U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_FCMODE_ACTIVELINE                                  (2U)

#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_SHIFT                                     (6U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_MASK                                      (0x00000040U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_OFF                                        (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOPOS_ON                                         (1U)

#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_SHIFT                                    (7U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_MASK                                     (0x00000080U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_OFF                                       (0U)
#define ISS_GLBCE_FORMAT_CONTROL_REG1_AUTOSIZE_ON                                        (1U)

#define ISS_GLBCE_FRAME_WIDTH_VAL_SHIFT                                                 (0U)
#define ISS_GLBCE_FRAME_WIDTH_VAL_MASK                                                  (0x0000ffffU)

#define ISS_GLBCE_FRAME_HEIGHT_VAL_SHIFT                                                (0U)
#define ISS_GLBCE_FRAME_HEIGHT_VAL_MASK                                                 (0x0000ffffU)

#define ISS_GLBCE_STRENGTH_IR_VAL_SHIFT                                                 (0U)
#define ISS_GLBCE_STRENGTH_IR_VAL_MASK                                                  (0x000000ffU)

#define ISS_GLBCE_PERCEPT_EN_REV_SHIFT                                                  (0U)
#define ISS_GLBCE_PERCEPT_EN_REV_MASK                                                   (0x00000001U)
#define ISS_GLBCE_PERCEPT_EN_REV_DISABLE                                                 (0U)
#define ISS_GLBCE_PERCEPT_EN_REV_ENABLE                                                  (1U)

#define ISS_GLBCE_PERCEPT_EN_FWD_SHIFT                                                  (1U)
#define ISS_GLBCE_PERCEPT_EN_FWD_MASK                                                   (0x00000002U)
#define ISS_GLBCE_PERCEPT_EN_FWD_DISABLE                                                 (0U)
#define ISS_GLBCE_PERCEPT_EN_FWD_ENABLE                                                  (1U)

#define ISS_GLBCE_REV_PERCEPT_LUT_00_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_00_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_01_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_01_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_02_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_02_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_03_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_03_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_04_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_04_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_05_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_05_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_06_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_06_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_07_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_07_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_08_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_08_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_09_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_09_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_10_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_10_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_11_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_11_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_12_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_12_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_13_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_13_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_14_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_14_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_15_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_15_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_16_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_16_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_17_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_17_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_18_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_18_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_19_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_19_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_20_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_20_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_21_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_21_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_22_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_22_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_23_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_23_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_24_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_24_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_25_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_25_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_26_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_26_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_27_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_27_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_28_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_28_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_29_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_29_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_30_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_30_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_31_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_31_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_32_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_32_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_33_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_33_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_34_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_34_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_35_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_35_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_36_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_36_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_37_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_37_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_38_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_38_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_39_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_39_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_40_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_40_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_41_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_41_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_42_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_42_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_43_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_43_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_44_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_44_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_45_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_45_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_46_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_46_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_47_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_47_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_48_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_48_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_49_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_49_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_50_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_50_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_51_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_51_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_52_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_52_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_53_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_53_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_54_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_54_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_55_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_55_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_56_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_56_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_57_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_57_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_58_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_58_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_59_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_59_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_60_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_60_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_61_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_61_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_62_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_62_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_63_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_63_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_REV_PERCEPT_LUT_64_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_REV_PERCEPT_LUT_64_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_00_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_00_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_01_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_01_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_02_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_02_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_03_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_03_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_04_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_04_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_05_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_05_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_06_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_06_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_07_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_07_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_08_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_08_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_09_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_09_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_10_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_10_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_11_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_11_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_12_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_12_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_13_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_13_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_14_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_14_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_15_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_15_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_16_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_16_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_17_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_17_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_18_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_18_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_19_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_19_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_20_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_20_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_21_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_21_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_22_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_22_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_23_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_23_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_24_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_24_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_25_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_25_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_26_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_26_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_27_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_27_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_28_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_28_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_29_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_29_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_30_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_30_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_31_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_31_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_32_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_32_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_33_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_33_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_34_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_34_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_35_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_35_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_36_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_36_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_37_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_37_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_38_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_38_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_39_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_39_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_40_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_40_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_41_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_41_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_42_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_42_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_43_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_43_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_44_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_44_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_45_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_45_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_46_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_46_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_47_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_47_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_48_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_48_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_49_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_49_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_50_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_50_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_51_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_51_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_52_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_52_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_53_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_53_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_54_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_54_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_55_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_55_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_56_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_56_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_57_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_57_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_58_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_58_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_59_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_59_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_60_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_60_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_61_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_61_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_62_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_62_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_63_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_63_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_FWD_PERCEPT_LUT_64_VAL_SHIFT                                          (0U)
#define ISS_GLBCE_FWD_PERCEPT_LUT_64_VAL_MASK                                           (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_EN_SHIFT                                                    (0U)
#define ISS_GLBCE_WDR_GAMMA_EN_MASK                                                     (0x00000001U)
#define ISS_GLBCE_WDR_GAMMA_EN_DISABLE                                                   (0U)
#define ISS_GLBCE_WDR_GAMMA_EN_ENABLE                                                    (1U)

#define ISS_GLBCE_WDR_GAMMA_LUT_00_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_00_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_01_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_01_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_02_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_02_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_03_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_03_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_04_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_04_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_05_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_05_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_06_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_06_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_07_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_07_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_08_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_08_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_09_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_09_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_10_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_10_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_11_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_11_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_12_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_12_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_13_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_13_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_14_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_14_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_15_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_15_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_16_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_16_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_17_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_17_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_18_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_18_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_19_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_19_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_20_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_20_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_21_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_21_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_22_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_22_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_23_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_23_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_24_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_24_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_25_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_25_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_26_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_26_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_27_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_27_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_28_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_28_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_29_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_29_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_30_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_30_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_31_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_31_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_32_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_32_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_33_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_33_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_34_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_34_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_35_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_35_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_36_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_36_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_37_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_37_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_38_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_38_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_39_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_39_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_40_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_40_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_41_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_41_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_42_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_42_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_43_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_43_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_44_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_44_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_45_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_45_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_46_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_46_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_47_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_47_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_48_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_48_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_49_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_49_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_50_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_50_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_51_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_51_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_52_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_52_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_53_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_53_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_54_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_54_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_55_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_55_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_56_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_56_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_57_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_57_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_58_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_58_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_59_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_59_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_60_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_60_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_61_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_61_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_62_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_62_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_63_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_63_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_64_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_64_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_65_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_65_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_66_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_66_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_67_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_67_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_68_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_68_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_69_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_69_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_70_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_70_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_71_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_71_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_72_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_72_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_73_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_73_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_74_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_74_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_75_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_75_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_76_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_76_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_77_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_77_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_78_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_78_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_79_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_79_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_80_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_80_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_81_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_81_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_82_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_82_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_83_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_83_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_84_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_84_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_85_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_85_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_86_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_86_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_87_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_87_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_88_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_88_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_89_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_89_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_90_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_90_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_91_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_91_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_92_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_92_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_93_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_93_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_94_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_94_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_95_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_95_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_96_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_96_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_97_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_97_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_98_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_98_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_99_VAL_SHIFT                                            (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_99_VAL_MASK                                             (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_100_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_100_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_101_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_101_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_102_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_102_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_103_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_103_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_104_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_104_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_105_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_105_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_106_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_106_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_107_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_107_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_108_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_108_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_109_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_109_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_110_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_110_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_111_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_111_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_112_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_112_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_113_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_113_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_114_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_114_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_115_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_115_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_116_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_116_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_117_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_117_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_118_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_118_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_119_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_119_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_120_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_120_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_121_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_121_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_122_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_122_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_123_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_123_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_124_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_124_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_125_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_125_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_126_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_126_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_127_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_127_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_128_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_128_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_129_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_129_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_130_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_130_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_131_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_131_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_132_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_132_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_133_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_133_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_134_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_134_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_135_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_135_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_136_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_136_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_137_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_137_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_138_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_138_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_139_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_139_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_140_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_140_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_141_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_141_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_142_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_142_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_143_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_143_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_144_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_144_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_145_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_145_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_146_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_146_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_147_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_147_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_148_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_148_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_149_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_149_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_150_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_150_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_151_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_151_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_152_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_152_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_153_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_153_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_154_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_154_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_155_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_155_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_156_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_156_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_157_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_157_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_158_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_158_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_159_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_159_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_160_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_160_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_161_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_161_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_162_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_162_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_163_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_163_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_164_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_164_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_165_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_165_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_166_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_166_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_167_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_167_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_168_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_168_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_169_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_169_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_170_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_170_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_171_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_171_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_172_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_172_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_173_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_173_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_174_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_174_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_175_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_175_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_176_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_176_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_177_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_177_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_178_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_178_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_179_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_179_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_180_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_180_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_181_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_181_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_182_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_182_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_183_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_183_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_184_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_184_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_185_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_185_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_186_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_186_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_187_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_187_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_188_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_188_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_189_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_189_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_190_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_190_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_191_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_191_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_192_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_192_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_193_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_193_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_194_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_194_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_195_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_195_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_196_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_196_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_197_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_197_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_198_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_198_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_199_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_199_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_200_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_200_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_201_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_201_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_202_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_202_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_203_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_203_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_204_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_204_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_205_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_205_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_206_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_206_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_207_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_207_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_208_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_208_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_209_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_209_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_210_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_210_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_211_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_211_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_212_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_212_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_213_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_213_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_214_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_214_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_215_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_215_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_216_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_216_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_217_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_217_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_218_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_218_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_219_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_219_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_220_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_220_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_221_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_221_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_222_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_222_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_223_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_223_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_224_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_224_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_225_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_225_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_226_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_226_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_227_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_227_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_228_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_228_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_229_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_229_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_230_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_230_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_231_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_231_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_232_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_232_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_233_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_233_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_234_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_234_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_235_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_235_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_236_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_236_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_237_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_237_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_238_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_238_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_239_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_239_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_240_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_240_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_241_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_241_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_242_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_242_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_243_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_243_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_244_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_244_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_245_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_245_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_246_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_246_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_247_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_247_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_248_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_248_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_249_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_249_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_250_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_250_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_251_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_251_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_252_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_252_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_253_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_253_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_254_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_254_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_255_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_255_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_WDR_GAMMA_LUT_256_VAL_SHIFT                                           (0U)
#define ISS_GLBCE_WDR_GAMMA_LUT_256_VAL_MASK                                            (0x0000ffffU)

#define ISS_GLBCE_TILE_OUT_POS_LEFT_SHIFT                                               (0U)
#define ISS_GLBCE_TILE_OUT_POS_LEFT_MASK                                                (0x0000ffffU)

#define ISS_GLBCE_TILE_OUT_POS_TOP_SHIFT                                                (16U)
#define ISS_GLBCE_TILE_OUT_POS_TOP_MASK                                                 (0xffff0000U)

#define ISS_GLBCE_TILE_OUT_SIZE_WIDTH_SHIFT                                             (0U)
#define ISS_GLBCE_TILE_OUT_SIZE_WIDTH_MASK                                              (0x0000ffffU)

#define ISS_GLBCE_TILE_OUT_SIZE_HEIGHT_SHIFT                                            (16U)
#define ISS_GLBCE_TILE_OUT_SIZE_HEIGHT_MASK                                             (0xffff0000U)

#define ISS_GLBCE_TILE_CONTROL_ENABLE_SHIFT                                             (0U)
#define ISS_GLBCE_TILE_CONTROL_ENABLE_MASK                                              (0x00000001U)

#define ISS_GLBCE_TILE_CONTROL_UPDATE_DSABLE_SHIFT                                      (2U)
#define ISS_GLBCE_TILE_CONTROL_UPDATE_DSABLE_MASK                                       (0x00000004U)

#define ISS_GLBCE_TILE_CONTROL_COLLECTION_DISABLE_SHIFT                                 (3U)
#define ISS_GLBCE_TILE_CONTROL_COLLECTION_DISABLE_MASK                                  (0x00000008U)

#define ISS_GLBCE_TILE_CONTROL_LAST_SHIFT                                               (4U)
#define ISS_GLBCE_TILE_CONTROL_LAST_MASK                                                (0x00000010U)

#define ISS_GLBCE_OUTPUT_FLAGS_TILE_STATUS_SHIFT                                        (0U)
#define ISS_GLBCE_OUTPUT_FLAGS_TILE_STATUS_MASK                                         (0x0000ffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_GLBCE_H_ */

