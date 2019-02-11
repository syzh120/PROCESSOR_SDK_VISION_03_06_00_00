/*
* hw_dispc.h
*
* Register-level header file for DSS
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

#ifndef HW_DISPC_H_
#define HW_DISPC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DSS_DISPC_REVISION                                                                                  (0x0U)
#define DSS_DISPC_SYSCONFIG                                                                                 (0x10U)
#define DSS_DISPC_SYSSTATUS                                                                                 (0x14U)
#define DSS_DISPC_IRQSTATUS                                                                                 (0x18U)
#define DSS_DISPC_IRQENABLE                                                                                 (0x1cU)
#define DSS_DISPC_CONTROL1                                                                                  (0x40U)
#define DSS_DISPC_CONFIG1                                                                                   (0x44U)
#define DSS_DISPC_DEFAULT_COLOR0                                                                            (0x4cU)
#define DSS_DISPC_DEFAULT_COLOR1                                                                            (0x50U)
#define DSS_DISPC_TRANS_COLOR0                                                                              (0x54U)
#define DSS_DISPC_TRANS_COLOR1                                                                              (0x58U)
#define DSS_DISPC_LINE_STATUS                                                                               (0x5cU)
#define DSS_DISPC_LINE_NUMBER                                                                               (0x60U)
#define DSS_DISPC_TIMING_H1                                                                                 (0x64U)
#define DSS_DISPC_TIMING_V1                                                                                 (0x68U)
#define DSS_DISPC_POL_FREQ1                                                                                 (0x6cU)
#define DSS_DISPC_DIVISOR1                                                                                  (0x70U)
#define DSS_DISPC_GLOBAL_ALPHA                                                                              (0x74U)
#define DSS_DISPC_SIZE_TV                                                                                   (0x78U)
#define DSS_DISPC_SIZE_LCD1                                                                                 (0x7cU)
#define DSS_DISPC_GFX_BA(n)                                                                                 ((uint32_t) 0x80U + ((n) * 4U))
#define DSS_DISPC_GFX_POSITION                                                                              (0x88U)
#define DSS_DISPC_GFX_SIZE                                                                                  (0x8cU)
#define DSS_DISPC_GFX_ATTRIBUTES                                                                            (0xa0U)
#define DSS_DISPC_GFX_BUF_THRESHOLD                                                                         (0xa4U)
#define DSS_DISPC_GFX_BUF_SIZE_STATUS                                                                       (0xa8U)
#define DSS_DISPC_GFX_ROW_INC                                                                               (0xacU)
#define DSS_DISPC_GFX_PIXEL_INC                                                                             (0xb0U)
#define DSS_DISPC_GFX_TABLE_BA                                                                              (0xb8U)
#define DSS_DISPC_VID1_BA(n)                                                                                ((uint32_t) 0xbcU + ((n) * 4U))
#define DSS_DISPC_VID1_POSITION                                                                             (0xc4U)
#define DSS_DISPC_VID1_SIZE                                                                                 (0xc8U)
#define DSS_DISPC_VID1_ATTRIBUTES                                                                           (0xccU)
#define DSS_DISPC_VID1_BUF_THRESHOLD                                                                        (0xd0U)
#define DSS_DISPC_VID1_BUF_SIZE_STATUS                                                                      (0xd4U)
#define DSS_DISPC_VID1_ROW_INC                                                                              (0xd8U)
#define DSS_DISPC_VID1_PIXEL_INC                                                                            (0xdcU)
#define DSS_DISPC_VID1_FIR                                                                                  (0xe0U)
#define DSS_DISPC_VID1_PICTURE_SIZE                                                                         (0xe4U)
#define DSS_DISPC_VID1_ACCU(n)                                                                              ((uint32_t) 0xe8U + ((n) * 4U))
#define DSS_DISPC_VID1_FIR_COEF_H(n)                                                                        ((uint32_t) 0xf0U + ((n) * 8U))
#define DSS_DISPC_VID1_FIR_COEF_HV(n)                                                                       ((uint32_t) 0xf4U + ((n) * 8U))
#define DSS_DISPC_VID1_CONV_COEF0                                                                           (0x130U)
#define DSS_DISPC_VID1_CONV_COEF1                                                                           (0x134U)
#define DSS_DISPC_VID1_CONV_COEF2                                                                           (0x138U)
#define DSS_DISPC_VID1_CONV_COEF3                                                                           (0x13cU)
#define DSS_DISPC_VID1_CONV_COEF4                                                                           (0x140U)
#define DSS_DISPC_VID2_BA(n)                                                                                ((uint32_t) 0x14cU + ((n) * 4U))
#define DSS_DISPC_VID2_POSITION                                                                             (0x154U)
#define DSS_DISPC_VID2_SIZE                                                                                 (0x158U)
#define DSS_DISPC_VID2_ATTRIBUTES                                                                           (0x15cU)
#define DSS_DISPC_VID2_BUF_THRESHOLD                                                                        (0x160U)
#define DSS_DISPC_VID2_BUF_SIZE_STATUS                                                                      (0x164U)
#define DSS_DISPC_VID2_ROW_INC                                                                              (0x168U)
#define DSS_DISPC_VID2_PIXEL_INC                                                                            (0x16cU)
#define DSS_DISPC_VID2_FIR                                                                                  (0x170U)
#define DSS_DISPC_VID2_PICTURE_SIZE                                                                         (0x174U)
#define DSS_DISPC_VID2_ACCU(n)                                                                              ((uint32_t) 0x178U + ((n) * 4U))
#define DSS_DISPC_VID2_FIR_COEF_H(n)                                                                        ((uint32_t) 0x180U + ((n) * 8U))
#define DSS_DISPC_VID2_FIR_COEF_HV(n)                                                                       ((uint32_t) 0x184U + ((n) * 8U))
#define DSS_DISPC_VID2_CONV_COEF0                                                                           (0x1c0U)
#define DSS_DISPC_VID2_CONV_COEF1                                                                           (0x1c4U)
#define DSS_DISPC_VID2_CONV_COEF2                                                                           (0x1c8U)
#define DSS_DISPC_VID2_CONV_COEF3                                                                           (0x1ccU)
#define DSS_DISPC_VID2_CONV_COEF4                                                                           (0x1d0U)
#define DSS_DISPC_DATA1_CYCLE1                                                                              (0x1d4U)
#define DSS_DISPC_DATA1_CYCLE2                                                                              (0x1d8U)
#define DSS_DISPC_DATA1_CYCLE3                                                                              (0x1dcU)
#define DSS_DISPC_VID1_FIR_COEF_V(n)                                                                        ((uint32_t) 0x1e0U + ((n) * 4U))
#define DSS_DISPC_VID2_FIR_COEF_V(n)                                                                        ((uint32_t) 0x200U + ((n) * 4U))
#define DSS_DISPC_CPR1_COEF_R                                                                               (0x220U)
#define DSS_DISPC_CPR1_COEF_G                                                                               (0x224U)
#define DSS_DISPC_CPR1_COEF_B                                                                               (0x228U)
#define DSS_DISPC_GFX_PRELOAD                                                                               (0x22cU)
#define DSS_DISPC_VID1_PRELOAD                                                                              (0x230U)
#define DSS_DISPC_VID2_PRELOAD                                                                              (0x234U)
#define DSS_DISPC_CONTROL2                                                                                  (0x238U)
#define DSS_DISPC_GFX_POSITION2                                                                             (0x240U)
#define DSS_DISPC_VID1_POSITION2                                                                            (0x244U)
#define DSS_DISPC_VID2_POSITION2                                                                            (0x248U)
#define DSS_DISPC_VID3_POSITION2                                                                            (0x24cU)
#define DSS_DISPC_VID3_ACCU(n)                                                                              ((uint32_t) 0x300U + ((n) * 4U))
#define DSS_DISPC_VID3_BA(n)                                                                                ((uint32_t) 0x308U + ((n) * 4U))
#define DSS_DISPC_VID3_FIR_COEF_H(n)                                                                        ((uint32_t) 0x310U + ((n) * 8U))
#define DSS_DISPC_VID3_FIR_COEF_HV(n)                                                                       ((uint32_t) 0x314U + ((n) * 8U))
#define DSS_DISPC_VID3_FIR_COEF_V(n)                                                                        ((uint32_t) 0x350U + ((n) * 4U))
#define DSS_DISPC_VID3_ATTRIBUTES                                                                           (0x370U)
#define DSS_DISPC_VID3_CONV_COEF0                                                                           (0x374U)
#define DSS_DISPC_VID3_CONV_COEF1                                                                           (0x378U)
#define DSS_DISPC_VID3_CONV_COEF2                                                                           (0x37cU)
#define DSS_DISPC_VID3_CONV_COEF3                                                                           (0x380U)
#define DSS_DISPC_VID3_CONV_COEF4                                                                           (0x384U)
#define DSS_DISPC_VID3_BUF_SIZE_STATUS                                                                      (0x388U)
#define DSS_DISPC_VID3_BUF_THRESHOLD                                                                        (0x38cU)
#define DSS_DISPC_VID3_FIR                                                                                  (0x390U)
#define DSS_DISPC_VID3_PICTURE_SIZE                                                                         (0x394U)
#define DSS_DISPC_VID3_PIXEL_INC                                                                            (0x398U)
#define DSS_DISPC_VID3_POSITION                                                                             (0x39cU)
#define DSS_DISPC_VID3_PRELOAD                                                                              (0x3a0U)
#define DSS_DISPC_VID3_ROW_INC                                                                              (0x3a4U)
#define DSS_DISPC_VID3_SIZE                                                                                 (0x3a8U)
#define DSS_DISPC_DEFAULT_COLOR2                                                                            (0x3acU)
#define DSS_DISPC_TRANS_COLOR2                                                                              (0x3b0U)
#define DSS_DISPC_CPR2_COEF_B                                                                               (0x3b4U)
#define DSS_DISPC_CPR2_COEF_G                                                                               (0x3b8U)
#define DSS_DISPC_CPR2_COEF_R                                                                               (0x3bcU)
#define DSS_DISPC_DATA2_CYCLE1                                                                              (0x3c0U)
#define DSS_DISPC_DATA2_CYCLE2                                                                              (0x3c4U)
#define DSS_DISPC_DATA2_CYCLE3                                                                              (0x3c8U)
#define DSS_DISPC_SIZE_LCD2                                                                                 (0x3ccU)
#define DSS_DISPC_TIMING_H2                                                                                 (0x400U)
#define DSS_DISPC_TIMING_V2                                                                                 (0x404U)
#define DSS_DISPC_POL_FREQ2                                                                                 (0x408U)
#define DSS_DISPC_DIVISOR2                                                                                  (0x40cU)
#define DSS_DISPC_WB_ACCU(n)                                                                                ((uint32_t) 0x500U + ((n) * 4U))
#define DSS_DISPC_WB_BA(n)                                                                                  ((uint32_t) 0x508U + ((n) * 4U))
#define DSS_DISPC_WB_FIR_COEF_H(n)                                                                          ((uint32_t) 0x510U + ((n) * 8U))
#define DSS_DISPC_WB_FIR_COEF_HV(n)                                                                         ((uint32_t) 0x514U + ((n) * 8U))
#define DSS_DISPC_WB_FIR_COEF_V(n)                                                                          ((uint32_t) 0x550U + ((n) * 4U))
#define DSS_DISPC_WB_ATTRIBUTES                                                                             (0x570U)
#define DSS_DISPC_WB_CONV_COEF0                                                                             (0x574U)
#define DSS_DISPC_WB_CONV_COEF1                                                                             (0x578U)
#define DSS_DISPC_WB_CONV_COEF2                                                                             (0x57cU)
#define DSS_DISPC_WB_CONV_COEF3                                                                             (0x580U)
#define DSS_DISPC_WB_CONV_COEF4                                                                             (0x584U)
#define DSS_DISPC_WB_BUF_SIZE_STATUS                                                                        (0x588U)
#define DSS_DISPC_WB_BUF_THRESHOLD                                                                          (0x58cU)
#define DSS_DISPC_WB_FIR                                                                                    (0x590U)
#define DSS_DISPC_WB_PICTURE_SIZE                                                                           (0x594U)
#define DSS_DISPC_WB_PIXEL_INC                                                                              (0x598U)
#define DSS_DISPC_WB_ROW_INC                                                                                (0x5a4U)
#define DSS_DISPC_WB_SIZE                                                                                   (0x5a8U)
#define DSS_DISPC_VID1_BA_UV(n)                                                                             ((uint32_t) 0x600U + ((n) * 4U))
#define DSS_DISPC_VID2_BA_UV(n)                                                                             ((uint32_t) 0x608U + ((n) * 4U))
#define DSS_DISPC_VID3_BA_UV(n)                                                                             ((uint32_t) 0x610U + ((n) * 4U))
#define DSS_DISPC_WB_BA_UV(n)                                                                               ((uint32_t) 0x618U + ((n) * 4U))
#define DSS_DISPC_CONFIG2                                                                                   (0x620U)
#define DSS_DISPC_VID1_ATTRIBUTES2                                                                          (0x624U)
#define DSS_DISPC_VID2_ATTRIBUTES2                                                                          (0x628U)
#define DSS_DISPC_VID3_ATTRIBUTES2                                                                          (0x62cU)
#define DSS_DISPC_GAMMA_TABLE0                                                                              (0x630U)
#define DSS_DISPC_GAMMA_TABLE2                                                                              (0x638U)
#define DSS_DISPC_VID1_FIR2                                                                                 (0x63cU)
#define DSS_DISPC_VID1_ACCU2(n)                                                                             ((uint32_t) 0x640U + ((n) * 4U))
#define DSS_DISPC_VID1_FIR_COEF_H2(n)                                                                       ((uint32_t) 0x648U + ((n) * 8U))
#define DSS_DISPC_VID1_FIR_COEF_HV2(n)                                                                      ((uint32_t) 0x64cU + ((n) * 8U))
#define DSS_DISPC_VID1_FIR_COEF_V2(n)                                                                       ((uint32_t) 0x688U + ((n) * 4U))
#define DSS_DISPC_VID2_FIR2                                                                                 (0x6a8U)
#define DSS_DISPC_VID2_ACCU2(n)                                                                             ((uint32_t) 0x6acU + ((n) * 4U))
#define DSS_DISPC_VID2_FIR_COEF_H2(n)                                                                       ((uint32_t) 0x6b4U + ((n) * 8U))
#define DSS_DISPC_VID2_FIR_COEF_HV2(n)                                                                      ((uint32_t) 0x6b8U + ((n) * 8U))
#define DSS_DISPC_VID2_FIR_COEF_V2(n)                                                                       ((uint32_t) 0x6f4U + ((n) * 4U))
#define DSS_DISPC_VID3_FIR2                                                                                 (0x724U)
#define DSS_DISPC_VID3_ACCU2(n)                                                                             ((uint32_t) 0x728U + ((n) * 4U))
#define DSS_DISPC_VID3_FIR_COEF_H2(n)                                                                       ((uint32_t) 0x730U + ((n) * 8U))
#define DSS_DISPC_VID3_FIR_COEF_HV2(n)                                                                      ((uint32_t) 0x734U + ((n) * 8U))
#define DSS_DISPC_VID3_FIR_COEF_V2(n)                                                                       ((uint32_t) 0x770U + ((n) * 4U))
#define DSS_DISPC_WB_FIR2                                                                                   (0x790U)
#define DSS_DISPC_WB_ACCU2(n)                                                                               ((uint32_t) 0x794U + ((n) * 4U))
#define DSS_DISPC_WB_FIR_COEF_H2(n)                                                                         ((uint32_t) 0x7a0U + ((n) * 8U))
#define DSS_DISPC_WB_FIR_COEF_HV2(n)                                                                        ((uint32_t) 0x7a4U + ((n) * 8U))
#define DSS_DISPC_WB_FIR_COEF_V2(n)                                                                         ((uint32_t) 0x7e0U + ((n) * 4U))
#define DSS_DISPC_GLOBAL_BUFFER                                                                             (0x800U)
#define DSS_DISPC_DIVISOR                                                                                   (0x804U)
#define DSS_DISPC_WB_ATTRIBUTES2                                                                            (0x810U)
#define DSS_DISPC_DEFAULT_COLOR3                                                                            (0x814U)
#define DSS_DISPC_TRANS_COLOR3                                                                              (0x818U)
#define DSS_DISPC_CPR3_COEF_B                                                                               (0x81cU)
#define DSS_DISPC_CPR3_COEF_G                                                                               (0x820U)
#define DSS_DISPC_CPR3_COEF_R                                                                               (0x824U)
#define DSS_DISPC_DATA3_CYCLE1                                                                              (0x828U)
#define DSS_DISPC_DATA3_CYCLE2                                                                              (0x82cU)
#define DSS_DISPC_DATA3_CYCLE3                                                                              (0x830U)
#define DSS_DISPC_SIZE_LCD3                                                                                 (0x834U)
#define DSS_DISPC_DIVISOR3                                                                                  (0x838U)
#define DSS_DISPC_POL_FREQ3                                                                                 (0x83cU)
#define DSS_DISPC_TIMING_H3                                                                                 (0x840U)
#define DSS_DISPC_TIMING_V3                                                                                 (0x844U)
#define DSS_DISPC_CONTROL3                                                                                  (0x848U)
#define DSS_DISPC_CONFIG3                                                                                   (0x84cU)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN                                                                      (0x854U)
#define DSS_DISPC_DISABLE_MSTANDBY_ENHANCEMENT                                                              (0x858U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE                                                                    (0x85cU)
#define DSS_DISPC_GFX_MFLAG_THRESHOLD                                                                       (0x860U)
#define DSS_DISPC_VID1_MFLAG_THRESHOLD                                                                      (0x864U)
#define DSS_DISPC_VID2_MFLAG_THRESHOLD                                                                      (0x868U)
#define DSS_DISPC_VID3_MFLAG_THRESHOLD                                                                      (0x86cU)
#define DSS_DISPC_WB_MFLAG_THRESHOLD                                                                        (0x870U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_DISPC_REVISION_RESERVED_32_SHIFT                                                                (8U)
#define DSS_DISPC_REVISION_RESERVED_32_MASK                                                                 (0xffffff00U)

#define DSS_DISPC_REVISION_REV_SHIFT                                                                        (0U)
#define DSS_DISPC_REVISION_REV_MASK                                                                         (0x000000ffU)

#define DSS_DISPC_SYSCONFIG_SOFTRESET_SHIFT                                                                 (1U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_MASK                                                                  (0x00000002U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_NMODE                                                                  (0U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_RST                                                                    (1U)

#define DSS_DISPC_SYSCONFIG_RESERVED_37_SHIFT                                                               (6U)
#define DSS_DISPC_SYSCONFIG_RESERVED_37_MASK                                                                (0x000000c0U)

#define DSS_DISPC_SYSCONFIG_SIDLEMODE_SHIFT                                                                 (3U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_MASK                                                                  (0x00000018U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_FIDLE                                                                  (0U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_NIDLE                                                                  (1U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_SIDLE                                                                  (2U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_RES                                                                    (3U)

#define DSS_DISPC_SYSCONFIG_RESERVED_38_SHIFT                                                               (14U)
#define DSS_DISPC_SYSCONFIG_RESERVED_38_MASK                                                                (0xffffc000U)

#define DSS_DISPC_SYSCONFIG_MIDLEMODE_SHIFT                                                                 (12U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_MASK                                                                  (0x00003000U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_FSTANDBY                                                               (0U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_NSTANDBY                                                               (1U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_SSTANDBY                                                               (2U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_RES                                                                    (3U)

#define DSS_DISPC_SYSCONFIG_AUTOIDLE_SHIFT                                                                  (0U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_MASK                                                                   (0x00000001U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKFREE                                                                 (0U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKGATED                                                                (1U)

#define DSS_DISPC_SYSCONFIG_ENWAKEUP_SHIFT                                                                  (2U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_MASK                                                                   (0x00000004U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPENB                                                               (1U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPDIS                                                               (0U)

#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                             (8U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_MASK                                                              (0x00000300U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCOFF                                                         (0U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCON                                                          (3U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPOFF                                                             (2U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_FUNCOFF                                                            (1U)

#define DSS_DISPC_SYSCONFIG_RESERVED_100_SHIFT                                                              (10U)
#define DSS_DISPC_SYSCONFIG_RESERVED_100_MASK                                                               (0x00000c00U)

#define DSS_DISPC_SYSCONFIG_WARMRESET_SHIFT                                                                 (5U)
#define DSS_DISPC_SYSCONFIG_WARMRESET_MASK                                                                  (0x00000020U)
#define DSS_DISPC_SYSCONFIG_WARMRESET_NORMAL                                                                 (0U)
#define DSS_DISPC_SYSCONFIG_WARMRESET_WARMRESET                                                              (1U)

#define DSS_DISPC_SYSSTATUS_RESERVED_40_SHIFT                                                               (1U)
#define DSS_DISPC_SYSSTATUS_RESERVED_40_MASK                                                                (0x000000feU)

#define DSS_DISPC_SYSSTATUS_RESETDONE_SHIFT                                                                 (0U)
#define DSS_DISPC_SYSSTATUS_RESETDONE_MASK                                                                  (0x00000001U)
#define DSS_DISPC_SYSSTATUS_RESETDONE_RSTONGOING                                                             (0U)
#define DSS_DISPC_SYSSTATUS_RESETDONE_RSTCOMP                                                                (1U)

#define DSS_DISPC_SYSSTATUS_RESERVED_41_SHIFT                                                               (8U)
#define DSS_DISPC_SYSSTATUS_RESERVED_41_MASK                                                                (0xffffff00U)

#define DSS_DISPC_IRQSTATUS_VID2ENDWINDOW_IRQ_SHIFT                                                         (13U)
#define DSS_DISPC_IRQSTATUS_VID2ENDWINDOW_IRQ_MASK                                                          (0x00002000U)
#define DSS_DISPC_IRQSTATUS_VID2ENDWINDOW_IRQ_FALSE                                                          (0U)
#define DSS_DISPC_IRQSTATUS_VID2ENDWINDOW_IRQ_TRUE                                                           (1U)

#define DSS_DISPC_IRQSTATUS_VID1BUFFERUNDERFLOW_IRQ_SHIFT                                                   (10U)
#define DSS_DISPC_IRQSTATUS_VID1BUFFERUNDERFLOW_IRQ_MASK                                                    (0x00000400U)
#define DSS_DISPC_IRQSTATUS_VID1BUFFERUNDERFLOW_IRQ_FALSE                                                    (0U)
#define DSS_DISPC_IRQSTATUS_VID1BUFFERUNDERFLOW_IRQ_TRUE                                                     (1U)

#define DSS_DISPC_IRQSTATUS_SYNCLOST1_IRQ_SHIFT                                                             (14U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST1_IRQ_MASK                                                              (0x00004000U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST1_IRQ_FALSE                                                              (0U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST1_IRQ_TRUE                                                               (1U)

#define DSS_DISPC_IRQSTATUS_GFXENDWINDOW_IRQ_SHIFT                                                          (7U)
#define DSS_DISPC_IRQSTATUS_GFXENDWINDOW_IRQ_MASK                                                           (0x00000080U)
#define DSS_DISPC_IRQSTATUS_GFXENDWINDOW_IRQ_FALSE                                                           (0U)
#define DSS_DISPC_IRQSTATUS_GFXENDWINDOW_IRQ_TRUE                                                            (1U)

#define DSS_DISPC_IRQSTATUS_VID1ENDWINDOW_IRQ_SHIFT                                                         (11U)
#define DSS_DISPC_IRQSTATUS_VID1ENDWINDOW_IRQ_MASK                                                          (0x00000800U)
#define DSS_DISPC_IRQSTATUS_VID1ENDWINDOW_IRQ_FALSE                                                          (0U)
#define DSS_DISPC_IRQSTATUS_VID1ENDWINDOW_IRQ_TRUE                                                           (1U)

#define DSS_DISPC_IRQSTATUS_PALETTEGAMMALOADING_IRQ_SHIFT                                                   (8U)
#define DSS_DISPC_IRQSTATUS_PALETTEGAMMALOADING_IRQ_MASK                                                    (0x00000100U)
#define DSS_DISPC_IRQSTATUS_PALETTEGAMMALOADING_IRQ_FALSE                                                    (0U)
#define DSS_DISPC_IRQSTATUS_PALETTEGAMMALOADING_IRQ_TRUE                                                     (1U)

#define DSS_DISPC_IRQSTATUS_PROGRAMMEDLINENUMBER_IRQ_SHIFT                                                  (5U)
#define DSS_DISPC_IRQSTATUS_PROGRAMMEDLINENUMBER_IRQ_MASK                                                   (0x00000020U)
#define DSS_DISPC_IRQSTATUS_PROGRAMMEDLINENUMBER_IRQ_FALSE                                                   (0U)
#define DSS_DISPC_IRQSTATUS_PROGRAMMEDLINENUMBER_IRQ_TRUE                                                    (1U)

#define DSS_DISPC_IRQSTATUS_OCPERROR_IRQ_SHIFT                                                              (9U)
#define DSS_DISPC_IRQSTATUS_OCPERROR_IRQ_MASK                                                               (0x00000200U)
#define DSS_DISPC_IRQSTATUS_OCPERROR_IRQ_FALSE                                                               (0U)
#define DSS_DISPC_IRQSTATUS_OCPERROR_IRQ_TRUE                                                                (1U)

#define DSS_DISPC_IRQSTATUS_EVSYNC_EVEN_IRQ_SHIFT                                                           (2U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_EVEN_IRQ_MASK                                                            (0x00000004U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_EVEN_IRQ_FALSE                                                            (0U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_EVEN_IRQ_TRUE                                                             (1U)

#define DSS_DISPC_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_SHIFT                                                    (6U)
#define DSS_DISPC_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_MASK                                                     (0x00000040U)
#define DSS_DISPC_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_FALSE                                                     (0U)
#define DSS_DISPC_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_TRUE                                                      (1U)

#define DSS_DISPC_IRQSTATUS_EVSYNC_ODD_IRQ_SHIFT                                                            (3U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_ODD_IRQ_MASK                                                             (0x00000008U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_ODD_IRQ_FALSE                                                             (0U)
#define DSS_DISPC_IRQSTATUS_EVSYNC_ODD_IRQ_TRUE                                                              (1U)

#define DSS_DISPC_IRQSTATUS_FRAMEDONE1_IRQ_SHIFT                                                            (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE1_IRQ_MASK                                                             (0x00000001U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE1_IRQ_FALSE                                                             (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE1_IRQ_TRUE                                                              (1U)

#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS1_IRQ_SHIFT                                                    (4U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS1_IRQ_MASK                                                     (0x00000010U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS1_IRQ_FALSE                                                     (0U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS1_IRQ_TRUE                                                      (1U)

#define DSS_DISPC_IRQSTATUS_VSYNC1_IRQ_SHIFT                                                                (1U)
#define DSS_DISPC_IRQSTATUS_VSYNC1_IRQ_MASK                                                                 (0x00000002U)
#define DSS_DISPC_IRQSTATUS_VSYNC1_IRQ_FALSE                                                                 (0U)
#define DSS_DISPC_IRQSTATUS_VSYNC1_IRQ_TRUE                                                                  (1U)

#define DSS_DISPC_IRQSTATUS_SYNCLOSTTV_IRQ_SHIFT                                                            (15U)
#define DSS_DISPC_IRQSTATUS_SYNCLOSTTV_IRQ_MASK                                                             (0x00008000U)
#define DSS_DISPC_IRQSTATUS_SYNCLOSTTV_IRQ_FALSE                                                             (0U)
#define DSS_DISPC_IRQSTATUS_SYNCLOSTTV_IRQ_TRUE                                                              (1U)

#define DSS_DISPC_IRQSTATUS_VID2BUFFERUNDERFLOW_IRQ_SHIFT                                                   (12U)
#define DSS_DISPC_IRQSTATUS_VID2BUFFERUNDERFLOW_IRQ_MASK                                                    (0x00001000U)
#define DSS_DISPC_IRQSTATUS_VID2BUFFERUNDERFLOW_IRQ_FALSE                                                    (0U)
#define DSS_DISPC_IRQSTATUS_VID2BUFFERUNDERFLOW_IRQ_TRUE                                                     (1U)

#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_SHIFT                                                                (16U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_MASK                                                                 (0x00010000U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_FALSE                                                                 (0U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_TRUE                                                                  (1U)

#define DSS_DISPC_IRQSTATUS_VSYNC2_IRQ_SHIFT                                                                (18U)
#define DSS_DISPC_IRQSTATUS_VSYNC2_IRQ_MASK                                                                 (0x00040000U)
#define DSS_DISPC_IRQSTATUS_VSYNC2_IRQ_FALSE                                                                 (0U)
#define DSS_DISPC_IRQSTATUS_VSYNC2_IRQ_TRUE                                                                  (1U)

#define DSS_DISPC_IRQSTATUS_VID3ENDWINDOW_IRQ_SHIFT                                                         (19U)
#define DSS_DISPC_IRQSTATUS_VID3ENDWINDOW_IRQ_MASK                                                          (0x00080000U)
#define DSS_DISPC_IRQSTATUS_VID3ENDWINDOW_IRQ_FALSE                                                          (0U)
#define DSS_DISPC_IRQSTATUS_VID3ENDWINDOW_IRQ_TRUE                                                           (1U)

#define DSS_DISPC_IRQSTATUS_VID3BUFFERUNDERFLOW_IRQ_SHIFT                                                   (20U)
#define DSS_DISPC_IRQSTATUS_VID3BUFFERUNDERFLOW_IRQ_MASK                                                    (0x00100000U)
#define DSS_DISPC_IRQSTATUS_VID3BUFFERUNDERFLOW_IRQ_FALSE                                                    (0U)
#define DSS_DISPC_IRQSTATUS_VID3BUFFERUNDERFLOW_IRQ_TRUE                                                     (1U)

#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS2_IRQ_SHIFT                                                    (21U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS2_IRQ_MASK                                                     (0x00200000U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS2_IRQ_FALSE                                                     (0U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS2_IRQ_TRUE                                                      (1U)

#define DSS_DISPC_IRQSTATUS_SYNCLOST2_IRQ_SHIFT                                                             (17U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST2_IRQ_MASK                                                              (0x00020000U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST2_IRQ_FALSE                                                              (0U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST2_IRQ_TRUE                                                               (1U)

#define DSS_DISPC_IRQSTATUS_FRAMEDONE2_IRQ_SHIFT                                                            (22U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE2_IRQ_MASK                                                             (0x00400000U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE2_IRQ_FALSE                                                             (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE2_IRQ_TRUE                                                              (1U)

#define DSS_DISPC_IRQSTATUS_FRAMEDONEWB_IRQ_SHIFT                                                           (23U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONEWB_IRQ_MASK                                                            (0x00800000U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONEWB_IRQ_FALSE                                                            (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONEWB_IRQ_TRUE                                                             (1U)

#define DSS_DISPC_IRQSTATUS_FRAMEDONETV_IRQ_SHIFT                                                           (24U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONETV_IRQ_MASK                                                            (0x01000000U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONETV_IRQ_FALSE                                                            (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONETV_IRQ_TRUE                                                             (1U)

#define DSS_DISPC_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_SHIFT                                                      (25U)
#define DSS_DISPC_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_MASK                                                       (0x02000000U)
#define DSS_DISPC_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_FALSE                                                       (0U)
#define DSS_DISPC_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_TRUE                                                        (1U)

#define DSS_DISPC_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_SHIFT                                                     (26U)
#define DSS_DISPC_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_MASK                                                      (0x04000000U)
#define DSS_DISPC_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_FALSE                                                      (0U)
#define DSS_DISPC_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_TRUE                                                       (1U)

#define DSS_DISPC_IRQSTATUS_SYNCLOST3_IRQ_SHIFT                                                             (27U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST3_IRQ_MASK                                                              (0x08000000U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST3_IRQ_FALSE                                                              (0U)
#define DSS_DISPC_IRQSTATUS_SYNCLOST3_IRQ_TRUE                                                               (1U)

#define DSS_DISPC_IRQSTATUS_VSYNC3_IRQ_SHIFT                                                                (28U)
#define DSS_DISPC_IRQSTATUS_VSYNC3_IRQ_MASK                                                                 (0x10000000U)
#define DSS_DISPC_IRQSTATUS_VSYNC3_IRQ_FALSE                                                                 (0U)
#define DSS_DISPC_IRQSTATUS_VSYNC3_IRQ_TRUE                                                                  (1U)

#define DSS_DISPC_IRQSTATUS_FRAMEDONE3_IRQ_SHIFT                                                            (30U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE3_IRQ_MASK                                                             (0x40000000U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE3_IRQ_FALSE                                                             (0U)
#define DSS_DISPC_IRQSTATUS_FRAMEDONE3_IRQ_TRUE                                                              (1U)

#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS3_IRQ_SHIFT                                                    (29U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS3_IRQ_MASK                                                     (0x20000000U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS3_IRQ_FALSE                                                     (0U)
#define DSS_DISPC_IRQSTATUS_ACBIASCOUNTSTATUS3_IRQ_TRUE                                                      (1U)

#define DSS_DISPC_IRQSTATUS_FLIPIMMEDIATEDONE_IRQ_SHIFT                                                     (31U)
#define DSS_DISPC_IRQSTATUS_FLIPIMMEDIATEDONE_IRQ_MASK                                                      (0x80000000U)
#define DSS_DISPC_IRQSTATUS_FLIPIMMEDIATEDONE_IRQ_FALSE                                                      (0U)
#define DSS_DISPC_IRQSTATUS_FLIPIMMEDIATEDONE_IRQ_TRUE                                                       (1U)

#define DSS_DISPC_IRQENABLE_EVSYNC_ODD_EN_SHIFT                                                             (3U)
#define DSS_DISPC_IRQENABLE_EVSYNC_ODD_EN_MASK                                                              (0x00000008U)
#define DSS_DISPC_IRQENABLE_EVSYNC_ODD_EN_MASKED                                                             (0U)
#define DSS_DISPC_IRQENABLE_EVSYNC_ODD_EN_GENINT                                                             (1U)

#define DSS_DISPC_IRQENABLE_FRAMEDONE_EN_SHIFT                                                              (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE_EN_MASK                                                               (0x00000001U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE_EN_MASKED                                                              (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE_EN_GENINT                                                              (1U)

#define DSS_DISPC_IRQENABLE_EVSYNC_EVEN_EN_SHIFT                                                            (2U)
#define DSS_DISPC_IRQENABLE_EVSYNC_EVEN_EN_MASK                                                             (0x00000004U)
#define DSS_DISPC_IRQENABLE_EVSYNC_EVEN_EN_MASKED                                                            (0U)
#define DSS_DISPC_IRQENABLE_EVSYNC_EVEN_EN_GENINT                                                            (1U)

#define DSS_DISPC_IRQENABLE_VSYNC1_EN_SHIFT                                                                 (1U)
#define DSS_DISPC_IRQENABLE_VSYNC1_EN_MASK                                                                  (0x00000002U)
#define DSS_DISPC_IRQENABLE_VSYNC1_EN_MASKED                                                                 (0U)
#define DSS_DISPC_IRQENABLE_VSYNC1_EN_GENINT                                                                 (1U)

#define DSS_DISPC_IRQENABLE_SYNCLOSTTV_EN_SHIFT                                                             (15U)
#define DSS_DISPC_IRQENABLE_SYNCLOSTTV_EN_MASK                                                              (0x00008000U)
#define DSS_DISPC_IRQENABLE_SYNCLOSTTV_EN_MASKED                                                             (0U)
#define DSS_DISPC_IRQENABLE_SYNCLOSTTV_EN_GENINT                                                             (1U)

#define DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN_SHIFT                                                    (10U)
#define DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN_MASK                                                     (0x00000400U)
#define DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN_MASKED                                                    (0U)
#define DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN_GENINT                                                    (1U)

#define DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN_SHIFT                                                    (12U)
#define DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN_MASK                                                     (0x00001000U)
#define DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN_MASKED                                                    (0U)
#define DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN_GENINT                                                    (1U)

#define DSS_DISPC_IRQENABLE_SYNCLOST1_EN_SHIFT                                                              (14U)
#define DSS_DISPC_IRQENABLE_SYNCLOST1_EN_MASK                                                               (0x00004000U)
#define DSS_DISPC_IRQENABLE_SYNCLOST1_EN_MASKED                                                              (0U)
#define DSS_DISPC_IRQENABLE_SYNCLOST1_EN_GENINT                                                              (1U)

#define DSS_DISPC_IRQENABLE_PROGRAMMEDLINENUMBER_EN_SHIFT                                                   (5U)
#define DSS_DISPC_IRQENABLE_PROGRAMMEDLINENUMBER_EN_MASK                                                    (0x00000020U)
#define DSS_DISPC_IRQENABLE_PROGRAMMEDLINENUMBER_EN_MASKED                                                   (0U)
#define DSS_DISPC_IRQENABLE_PROGRAMMEDLINENUMBER_EN_GENINT                                                   (1U)

#define DSS_DISPC_IRQENABLE_GFXENDWINDOW_EN_SHIFT                                                           (7U)
#define DSS_DISPC_IRQENABLE_GFXENDWINDOW_EN_MASK                                                            (0x00000080U)
#define DSS_DISPC_IRQENABLE_GFXENDWINDOW_EN_MASKED                                                           (0U)
#define DSS_DISPC_IRQENABLE_GFXENDWINDOW_EN_GENINT                                                           (1U)

#define DSS_DISPC_IRQENABLE_OCPERROR_EN_SHIFT                                                               (9U)
#define DSS_DISPC_IRQENABLE_OCPERROR_EN_MASK                                                                (0x00000200U)
#define DSS_DISPC_IRQENABLE_OCPERROR_EN_MASKED                                                               (0U)
#define DSS_DISPC_IRQENABLE_OCPERROR_EN_GENINT                                                               (1U)

#define DSS_DISPC_IRQENABLE_ENDVID1WINDOW_EN_SHIFT                                                          (11U)
#define DSS_DISPC_IRQENABLE_ENDVID1WINDOW_EN_MASK                                                           (0x00000800U)
#define DSS_DISPC_IRQENABLE_ENDVID1WINDOW_EN_MASKED                                                          (0U)
#define DSS_DISPC_IRQENABLE_ENDVID1WINDOW_EN_GENINT                                                          (1U)

#define DSS_DISPC_IRQENABLE_VID2ENDWINDOW_EN_SHIFT                                                          (13U)
#define DSS_DISPC_IRQENABLE_VID2ENDWINDOW_EN_MASK                                                           (0x00002000U)
#define DSS_DISPC_IRQENABLE_VID2ENDWINDOW_EN_MASKED                                                          (0U)
#define DSS_DISPC_IRQENABLE_VID2ENDWINDOW_EN_GENINT                                                          (1U)

#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS1_EN_SHIFT                                                     (4U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS1_EN_MASK                                                      (0x00000010U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS1_EN_MASKED                                                     (0U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS1_EN_GENINT                                                     (1U)

#define DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN_SHIFT                                                     (6U)
#define DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN_MASK                                                      (0x00000040U)
#define DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN_MASKED                                                     (0U)
#define DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN_GENINT                                                     (1U)

#define DSS_DISPC_IRQENABLE_PALETTEGAMMA_EN_SHIFT                                                           (8U)
#define DSS_DISPC_IRQENABLE_PALETTEGAMMA_EN_MASK                                                            (0x00000100U)
#define DSS_DISPC_IRQENABLE_PALETTEGAMMA_EN_MASKED                                                           (0U)
#define DSS_DISPC_IRQENABLE_PALETTEGAMMA_EN_GENINT                                                           (1U)

#define DSS_DISPC_IRQENABLE_WAKEUP_EN_SHIFT                                                                 (16U)
#define DSS_DISPC_IRQENABLE_WAKEUP_EN_MASK                                                                  (0x00010000U)
#define DSS_DISPC_IRQENABLE_WAKEUP_EN_GENINT                                                                 (1U)
#define DSS_DISPC_IRQENABLE_WAKEUP_EN_MASKED                                                                 (0U)

#define DSS_DISPC_IRQENABLE_RESERVED_SHIFT                                                                  (2U)
#define DSS_DISPC_IRQENABLE_RESERVED_MASK                                                                   (0x00000004U)

#define DSS_DISPC_IRQENABLE_RESERVED1_SHIFT                                                                 (3U)
#define DSS_DISPC_IRQENABLE_RESERVED1_MASK                                                                  (0x00000008U)

#define DSS_DISPC_IRQENABLE_RESERVED_31_SHIFT                                                               (5U)
#define DSS_DISPC_IRQENABLE_RESERVED_31_MASK                                                                (0x00000020U)

#define DSS_DISPC_IRQENABLE_RESERVED_3_SHIFT                                                                (6U)
#define DSS_DISPC_IRQENABLE_RESERVED_3_MASK                                                                 (0x00000040U)

#define DSS_DISPC_IRQENABLE_RESERVED_10_SHIFT                                                               (7U)
#define DSS_DISPC_IRQENABLE_RESERVED_10_MASK                                                                (0x00000080U)

#define DSS_DISPC_IRQENABLE_RESERVED_1_SHIFT                                                                (1U)
#define DSS_DISPC_IRQENABLE_RESERVED_1_MASK                                                                 (0x00000002U)

#define DSS_DISPC_IRQENABLE_RESERVED_32_SHIFT                                                               (10U)
#define DSS_DISPC_IRQENABLE_RESERVED_32_MASK                                                                (0x00000400U)

#define DSS_DISPC_IRQENABLE_RESERVED_40_SHIFT                                                               (11U)
#define DSS_DISPC_IRQENABLE_RESERVED_40_MASK                                                                (0x00000800U)

#define DSS_DISPC_IRQENABLE_RESERVED_100_SHIFT                                                              (12U)
#define DSS_DISPC_IRQENABLE_RESERVED_100_MASK                                                               (0x00001000U)

#define DSS_DISPC_IRQENABLE_RESERVED_200_SHIFT                                                              (13U)
#define DSS_DISPC_IRQENABLE_RESERVED_200_MASK                                                               (0x00002000U)

#define DSS_DISPC_IRQENABLE_RESERVED_150_SHIFT                                                              (14U)
#define DSS_DISPC_IRQENABLE_RESERVED_150_MASK                                                               (0x00004000U)

#define DSS_DISPC_IRQENABLE_RESERVED_110_SHIFT                                                              (15U)
#define DSS_DISPC_IRQENABLE_RESERVED_110_MASK                                                               (0x00008000U)

#define DSS_DISPC_IRQENABLE_FRAMEDONE2_EN_SHIFT                                                             (22U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE2_EN_MASK                                                              (0x00400000U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE2_EN_MASKED                                                             (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE2_EN_GENINT                                                             (1U)

#define DSS_DISPC_IRQENABLE_VSYNC2_EN_SHIFT                                                                 (18U)
#define DSS_DISPC_IRQENABLE_VSYNC2_EN_MASK                                                                  (0x00040000U)
#define DSS_DISPC_IRQENABLE_VSYNC2_EN_MASKED                                                                 (0U)
#define DSS_DISPC_IRQENABLE_VSYNC2_EN_GENINT                                                                 (1U)

#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS2_EN_SHIFT                                                     (21U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS2_EN_MASK                                                      (0x00200000U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS2_EN_MASKED                                                     (0U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS2_EN_GENINT                                                     (1U)

#define DSS_DISPC_IRQENABLE_SYNCLOST2_EN_SHIFT                                                              (17U)
#define DSS_DISPC_IRQENABLE_SYNCLOST2_EN_MASK                                                               (0x00020000U)
#define DSS_DISPC_IRQENABLE_SYNCLOST2_EN_MASKED                                                              (0U)
#define DSS_DISPC_IRQENABLE_SYNCLOST2_EN_GENINT                                                              (1U)

#define DSS_DISPC_IRQENABLE_VID3ENDWINDOW_EN_SHIFT                                                          (19U)
#define DSS_DISPC_IRQENABLE_VID3ENDWINDOW_EN_MASK                                                           (0x00080000U)
#define DSS_DISPC_IRQENABLE_VID3ENDWINDOW_EN_MASKED                                                          (0U)
#define DSS_DISPC_IRQENABLE_VID3ENDWINDOW_EN_GENINT                                                          (1U)

#define DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN_SHIFT                                                    (20U)
#define DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN_MASK                                                     (0x00100000U)
#define DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN_MASKED                                                    (0U)
#define DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN_GENINT                                                    (1U)

#define DSS_DISPC_IRQENABLE_FRAMEDONEWB_EN_SHIFT                                                            (23U)
#define DSS_DISPC_IRQENABLE_FRAMEDONEWB_EN_MASK                                                             (0x00800000U)
#define DSS_DISPC_IRQENABLE_FRAMEDONEWB_EN_MASKED                                                            (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONEWB_EN_GENINT                                                            (1U)

#define DSS_DISPC_IRQENABLE_FRAMEDONETV_EN_SHIFT                                                            (24U)
#define DSS_DISPC_IRQENABLE_FRAMEDONETV_EN_MASK                                                             (0x01000000U)
#define DSS_DISPC_IRQENABLE_FRAMEDONETV_EN_MASKED                                                            (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONETV_EN_GENINT                                                            (1U)

#define DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN_SHIFT                                                       (25U)
#define DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN_MASK                                                        (0x02000000U)
#define DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN_MASKED                                                       (0U)
#define DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN_GENINT                                                       (1U)

#define DSS_DISPC_IRQENABLE_WBUNCOMPLETEERROR_EN_SHIFT                                                      (26U)
#define DSS_DISPC_IRQENABLE_WBUNCOMPLETEERROR_EN_MASK                                                       (0x04000000U)
#define DSS_DISPC_IRQENABLE_WBUNCOMPLETEERROR_EN_MASKED                                                      (0U)
#define DSS_DISPC_IRQENABLE_WBUNCOMPLETEERROR_EN_GENINT                                                      (1U)

#define DSS_DISPC_IRQENABLE_SYNCLOST3_EN_SHIFT                                                              (27U)
#define DSS_DISPC_IRQENABLE_SYNCLOST3_EN_MASK                                                               (0x08000000U)
#define DSS_DISPC_IRQENABLE_SYNCLOST3_EN_MASKED                                                              (0U)
#define DSS_DISPC_IRQENABLE_SYNCLOST3_EN_GENINT                                                              (1U)

#define DSS_DISPC_IRQENABLE_VSYNC3_EN_SHIFT                                                                 (28U)
#define DSS_DISPC_IRQENABLE_VSYNC3_EN_MASK                                                                  (0x10000000U)
#define DSS_DISPC_IRQENABLE_VSYNC3_EN_MASKED                                                                 (0U)
#define DSS_DISPC_IRQENABLE_VSYNC3_EN_GENINT                                                                 (1U)

#define DSS_DISPC_IRQENABLE_FRAMEDONE3_EN_SHIFT                                                             (30U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE3_EN_MASK                                                              (0x40000000U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE3_EN_MASKED                                                             (0U)
#define DSS_DISPC_IRQENABLE_FRAMEDONE3_EN_GENINT                                                             (1U)

#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS3_EN_SHIFT                                                     (29U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS3_EN_MASK                                                      (0x20000000U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS3_EN_MASKED                                                     (0U)
#define DSS_DISPC_IRQENABLE_ACBIASCOUNTSTATUS3_EN_GENINT                                                     (1U)

#define DSS_DISPC_IRQENABLE_FLIPIMMEDIATEDONE_EN_SHIFT                                                      (31U)
#define DSS_DISPC_IRQENABLE_FLIPIMMEDIATEDONE_EN_MASK                                                       (0x80000000U)
#define DSS_DISPC_IRQENABLE_FLIPIMMEDIATEDONE_EN_MASKED                                                      (0U)
#define DSS_DISPC_IRQENABLE_FLIPIMMEDIATEDONE_EN_GENINT                                                      (1U)

#define DSS_DISPC_CONTROL1_STDITHERENABLE_SHIFT                                                             (7U)
#define DSS_DISPC_CONTROL1_STDITHERENABLE_MASK                                                              (0x00000080U)
#define DSS_DISPC_CONTROL1_STDITHERENABLE_STDITHDIS                                                          (0U)
#define DSS_DISPC_CONTROL1_STDITHERENABLE_STDITHENB                                                          (1U)

#define DSS_DISPC_CONTROL1_TFTDATALINES_SHIFT                                                               (8U)
#define DSS_DISPC_CONTROL1_TFTDATALINES_MASK                                                                (0x00000300U)
#define DSS_DISPC_CONTROL1_TFTDATALINES_OALSB12B                                                             (0U)
#define DSS_DISPC_CONTROL1_TFTDATALINES_OALSB16B                                                             (1U)
#define DSS_DISPC_CONTROL1_TFTDATALINES_OALSB18B                                                             (2U)
#define DSS_DISPC_CONTROL1_TFTDATALINES_OALSB24B                                                             (3U)

#define DSS_DISPC_CONTROL1_STALLMODE_SHIFT                                                                  (11U)
#define DSS_DISPC_CONTROL1_STALLMODE_MASK                                                                   (0x00000800U)
#define DSS_DISPC_CONTROL1_STALLMODE_NMODE                                                                   (0U)
#define DSS_DISPC_CONTROL1_STALLMODE_RFBIMODE                                                                (1U)

#define DSS_DISPC_CONTROL1_GPIN0_SHIFT                                                                      (13U)
#define DSS_DISPC_CONTROL1_GPIN0_MASK                                                                       (0x00002000U)
#define DSS_DISPC_CONTROL1_GPIN0_GPIN0RST                                                                    (0U)
#define DSS_DISPC_CONTROL1_GPIN0_GPIN0SET                                                                    (1U)

#define DSS_DISPC_CONTROL1_MONOCOLOR_SHIFT                                                                  (2U)
#define DSS_DISPC_CONTROL1_MONOCOLOR_MASK                                                                   (0x00000004U)
#define DSS_DISPC_CONTROL1_MONOCOLOR_COLOPENB                                                                (0U)
#define DSS_DISPC_CONTROL1_MONOCOLOR_MONOPENB                                                                (1U)

#define DSS_DISPC_CONTROL1_M8B_SHIFT                                                                        (4U)
#define DSS_DISPC_CONTROL1_M8B_MASK                                                                         (0x00000010U)
#define DSS_DISPC_CONTROL1_M8B_4PIXTOPANEL                                                                   (0U)
#define DSS_DISPC_CONTROL1_M8B_8PIXTOPANEL                                                                   (1U)

#define DSS_DISPC_CONTROL1_GOTV_SHIFT                                                                       (6U)
#define DSS_DISPC_CONTROL1_GOTV_MASK                                                                        (0x00000040U)
#define DSS_DISPC_CONTROL1_GOTV_HFUISR                                                                       (0U)
#define DSS_DISPC_CONTROL1_GOTV_UFPSR                                                                        (1U)

#define DSS_DISPC_CONTROL1_TVENABLE_SHIFT                                                                   (1U)
#define DSS_DISPC_CONTROL1_TVENABLE_MASK                                                                    (0x00000002U)
#define DSS_DISPC_CONTROL1_TVENABLE_DIGOPDIS                                                                 (0U)
#define DSS_DISPC_CONTROL1_TVENABLE_DIGOPENB                                                                 (1U)

#define DSS_DISPC_CONTROL1_STNTFT_SHIFT                                                                     (3U)
#define DSS_DISPC_CONTROL1_STNTFT_MASK                                                                      (0x00000008U)
#define DSS_DISPC_CONTROL1_STNTFT_STNDISPENB                                                                 (0U)
#define DSS_DISPC_CONTROL1_STNTFT_ATFTDISENB                                                                 (1U)

#define DSS_DISPC_CONTROL1_GOLCD_SHIFT                                                                      (5U)
#define DSS_DISPC_CONTROL1_GOLCD_MASK                                                                       (0x00000020U)
#define DSS_DISPC_CONTROL1_GOLCD_HFUISR                                                                      (0U)
#define DSS_DISPC_CONTROL1_GOLCD_UFPSR                                                                       (1U)

#define DSS_DISPC_CONTROL1_LCDENABLE_SHIFT                                                                  (0U)
#define DSS_DISPC_CONTROL1_LCDENABLE_MASK                                                                   (0x00000001U)
#define DSS_DISPC_CONTROL1_LCDENABLE_LCDOPDIS                                                                (0U)
#define DSS_DISPC_CONTROL1_LCDENABLE_LCDOPENB                                                                (1U)

#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_SHIFT                                             (30U)
#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_MASK                                              (0xc0000000U)
#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_ONEFRAME                                           (0U)
#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_TWOFRAMES                                          (1U)
#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_FOURFRAMES                                         (2U)
#define DSS_DISPC_CONTROL1_SPATIALTEMPORALDITHERINGFRAMES_RESERVED                                           (3U)

#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_SHIFT                                                              (25U)
#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_MASK                                                               (0x06000000U)
#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_LOWLEVEL                                                            (0U)
#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_HIGHLEVEL                                                           (1U)
#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_UNCHANGED                                                           (2U)
#define DSS_DISPC_CONTROL1_TDMUNUSEDBITS_RES                                                                 (3U)

#define DSS_DISPC_CONTROL1_TDMENABLE_SHIFT                                                                  (20U)
#define DSS_DISPC_CONTROL1_TDMENABLE_MASK                                                                   (0x00100000U)
#define DSS_DISPC_CONTROL1_TDMENABLE_TDMDIS                                                                  (0U)
#define DSS_DISPC_CONTROL1_TDMENABLE_TDMENB                                                                  (1U)

#define DSS_DISPC_CONTROL1_GPOUT0_SHIFT                                                                     (15U)
#define DSS_DISPC_CONTROL1_GPOUT0_MASK                                                                      (0x00008000U)
#define DSS_DISPC_CONTROL1_GPOUT0_RESET                                                                      (0U)
#define DSS_DISPC_CONTROL1_GPOUT0_SET                                                                        (1U)

#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_SHIFT                                                            (21U)
#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_MASK                                                             (0x00600000U)
#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_8BPARAINT                                                         (0U)
#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_9BPARAINT                                                         (1U)
#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_12BPARAINT                                                        (2U)
#define DSS_DISPC_CONTROL1_TDMPARALLELMODE_16BPARAINT                                                        (3U)

#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_SHIFT                                                             (23U)
#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_MASK                                                              (0x01800000U)
#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_1CYCPERPIX                                                         (0U)
#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_2CYCPERPIX                                                         (1U)
#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_3CYCPERPIX                                                         (2U)
#define DSS_DISPC_CONTROL1_TDMCYCLEFORMAT_3CYCPER2PIX                                                        (3U)

#define DSS_DISPC_CONTROL1_HT_SHIFT                                                                         (17U)
#define DSS_DISPC_CONTROL1_HT_MASK                                                                          (0x000e0000U)

#define DSS_DISPC_CONTROL1_GPOUT1_SHIFT                                                                     (16U)
#define DSS_DISPC_CONTROL1_GPOUT1_MASK                                                                      (0x00010000U)
#define DSS_DISPC_CONTROL1_GPOUT1_RESET                                                                      (0U)
#define DSS_DISPC_CONTROL1_GPOUT1_SET                                                                        (1U)

#define DSS_DISPC_CONTROL1_GPIN1_SHIFT                                                                      (14U)
#define DSS_DISPC_CONTROL1_GPIN1_MASK                                                                       (0x00004000U)
#define DSS_DISPC_CONTROL1_GPIN1_RESET                                                                       (0U)
#define DSS_DISPC_CONTROL1_GPIN1_SET                                                                         (1U)

#define DSS_DISPC_CONTROL1_OVERLAYOPTIMIZATION_SHIFT                                                        (12U)
#define DSS_DISPC_CONTROL1_OVERLAYOPTIMIZATION_MASK                                                         (0x00001000U)
#define DSS_DISPC_CONTROL1_OVERLAYOPTIMIZATION_GDBVWFM                                                       (0U)
#define DSS_DISPC_CONTROL1_OVERLAYOPTIMIZATION_GDBVWNFM                                                      (1U)

#define DSS_DISPC_CONTROL1_SECURE_SHIFT                                                                     (10U)
#define DSS_DISPC_CONTROL1_SECURE_MASK                                                                      (0x00000400U)
#define DSS_DISPC_CONTROL1_SECURE_NSECMODE                                                                   (0U)
#define DSS_DISPC_CONTROL1_SECURE_SECMODE                                                                    (1U)

#define DSS_DISPC_CONTROL1_PCKFREEENABLE_SHIFT                                                              (27U)
#define DSS_DISPC_CONTROL1_PCKFREEENABLE_MASK                                                               (0x08000000U)

#define DSS_DISPC_CONTROL1_LCDENABLESIGNAL_SHIFT                                                            (28U)
#define DSS_DISPC_CONTROL1_LCDENABLESIGNAL_MASK                                                             (0x10000000U)

#define DSS_DISPC_CONTROL1_LCDENABLEPOL_SHIFT                                                               (29U)
#define DSS_DISPC_CONTROL1_LCDENABLEPOL_MASK                                                                (0x20000000U)

#define DSS_DISPC_CONFIG1_PIXELDATAGATED_SHIFT                                                              (4U)
#define DSS_DISPC_CONFIG1_PIXELDATAGATED_MASK                                                               (0x00000010U)
#define DSS_DISPC_CONFIG1_PIXELDATAGATED_PDGDIS                                                              (0U)
#define DSS_DISPC_CONFIG1_PIXELDATAGATED_PDGENB                                                              (1U)

#define DSS_DISPC_CONFIG1_HSYNCGATED_SHIFT                                                                  (6U)
#define DSS_DISPC_CONFIG1_HSYNCGATED_MASK                                                                   (0x00000040U)
#define DSS_DISPC_CONFIG1_HSYNCGATED_HGDIS                                                                   (0U)
#define DSS_DISPC_CONFIG1_HSYNCGATED_HGENB                                                                   (1U)

#define DSS_DISPC_CONFIG1_ACBIASGATED_SHIFT                                                                 (8U)
#define DSS_DISPC_CONFIG1_ACBIASGATED_MASK                                                                  (0x00000100U)
#define DSS_DISPC_CONFIG1_ACBIASGATED_ACBGDIS                                                                (0U)
#define DSS_DISPC_CONFIG1_ACBIASGATED_ACBGENB                                                                (1U)

#define DSS_DISPC_CONFIG1_TCKLCDENABLE_SHIFT                                                                (10U)
#define DSS_DISPC_CONFIG1_TCKLCDENABLE_MASK                                                                 (0x00000400U)
#define DSS_DISPC_CONFIG1_TCKLCDENABLE_DISTCK                                                                (0U)
#define DSS_DISPC_CONFIG1_TCKLCDENABLE_ENBTCK                                                                (1U)

#define DSS_DISPC_CONFIG1_TCKTVENABLE_SHIFT                                                                 (12U)
#define DSS_DISPC_CONFIG1_TCKTVENABLE_MASK                                                                  (0x00001000U)
#define DSS_DISPC_CONFIG1_TCKTVENABLE_DISTCK                                                                 (0U)
#define DSS_DISPC_CONFIG1_TCKTVENABLE_ENBTCK                                                                 (1U)

#define DSS_DISPC_CONFIG1_PALETTEGAMMATABLE_SHIFT                                                           (3U)
#define DSS_DISPC_CONFIG1_PALETTEGAMMATABLE_MASK                                                            (0x00000008U)
#define DSS_DISPC_CONFIG1_PALETTEGAMMATABLE_LUTPALLETTE                                                      (0U)
#define DSS_DISPC_CONFIG1_PALETTEGAMMATABLE_LUTGTABLE                                                        (1U)

#define DSS_DISPC_CONFIG1_PIXELCLOCKGATED_SHIFT                                                             (5U)
#define DSS_DISPC_CONFIG1_PIXELCLOCKGATED_MASK                                                              (0x00000020U)
#define DSS_DISPC_CONFIG1_PIXELCLOCKGATED_PCGDIS                                                             (0U)
#define DSS_DISPC_CONFIG1_PIXELCLOCKGATED_PCGENB                                                             (1U)

#define DSS_DISPC_CONFIG1_VSYNCGATED_SHIFT                                                                  (7U)
#define DSS_DISPC_CONFIG1_VSYNCGATED_MASK                                                                   (0x00000080U)
#define DSS_DISPC_CONFIG1_VSYNCGATED_VGDIS                                                                   (0U)
#define DSS_DISPC_CONFIG1_VSYNCGATED_VGENB                                                                   (1U)

#define DSS_DISPC_CONFIG1_PIXELGATED_SHIFT                                                                  (0U)
#define DSS_DISPC_CONFIG1_PIXELGATED_MASK                                                                   (0x00000001U)
#define DSS_DISPC_CONFIG1_PIXELGATED_PCLKTOGA                                                                (0U)
#define DSS_DISPC_CONFIG1_PIXELGATED_PCLKTOGV                                                                (1U)

#define DSS_DISPC_CONFIG1_LOADMODE_SHIFT                                                                    (1U)
#define DSS_DISPC_CONFIG1_LOADMODE_MASK                                                                     (0x00000006U)
#define DSS_DISPC_CONFIG1_LOADMODE_PGTABLEFR                                                                 (0U)
#define DSS_DISPC_CONFIG1_LOADMODE_PGTABUSETB                                                                (1U)
#define DSS_DISPC_CONFIG1_LOADMODE_FRDATLEFR                                                                 (2U)
#define DSS_DISPC_CONFIG1_LOADMODE_DLOFRSW                                                                   (3U)

#define DSS_DISPC_CONFIG1_GAMATABLEENABLE_SHIFT                                                             (9U)
#define DSS_DISPC_CONFIG1_GAMATABLEENABLE_MASK                                                              (0x00000200U)
#define DSS_DISPC_CONFIG1_GAMATABLEENABLE_GAMMATABLEEN                                                       (0U)
#define DSS_DISPC_CONFIG1_GAMATABLEENABLE_GAMMATABLEDIS                                                      (1U)

#define DSS_DISPC_CONFIG1_TCKLCDSELECTION_SHIFT                                                             (11U)
#define DSS_DISPC_CONFIG1_TCKLCDSELECTION_MASK                                                              (0x00000800U)
#define DSS_DISPC_CONFIG1_TCKLCDSELECTION_GDTK                                                               (0U)
#define DSS_DISPC_CONFIG1_TCKLCDSELECTION_VSTK                                                               (1U)

#define DSS_DISPC_CONFIG1_TCKTVSELECTION_SHIFT                                                              (13U)
#define DSS_DISPC_CONFIG1_TCKTVSELECTION_MASK                                                               (0x00002000U)
#define DSS_DISPC_CONFIG1_TCKTVSELECTION_GDTCK                                                               (0U)
#define DSS_DISPC_CONFIG1_TCKTVSELECTION_VSTCK                                                               (1U)

#define DSS_DISPC_CONFIG1_BUFFERMERGE_SHIFT                                                                 (14U)
#define DSS_DISPC_CONFIG1_BUFFERMERGE_MASK                                                                  (0x00004000U)
#define DSS_DISPC_CONFIG1_BUFFERMERGE_MERGEDIS                                                               (0U)
#define DSS_DISPC_CONFIG1_BUFFERMERGE_MERGEENB                                                               (1U)

#define DSS_DISPC_CONFIG1_CPR_SHIFT                                                                         (15U)
#define DSS_DISPC_CONFIG1_CPR_MASK                                                                          (0x00008000U)
#define DSS_DISPC_CONFIG1_CPR_CPRDIS                                                                         (0U)
#define DSS_DISPC_CONFIG1_CPR_CPRENB                                                                         (1U)

#define DSS_DISPC_CONFIG1_BUFFERHANDCHECK_SHIFT                                                             (16U)
#define DSS_DISPC_CONFIG1_BUFFERHANDCHECK_MASK                                                              (0x00010000U)
#define DSS_DISPC_CONFIG1_BUFFERHANDCHECK_HANDCHECKDIS                                                       (0U)
#define DSS_DISPC_CONFIG1_BUFFERHANDCHECK_HANDCHECKENB                                                       (1U)

#define DSS_DISPC_CONFIG1_BUFFERFILLING_SHIFT                                                               (17U)
#define DSS_DISPC_CONFIG1_BUFFERFILLING_MASK                                                                (0x00020000U)
#define DSS_DISPC_CONFIG1_BUFFERFILLING_FIFOFILLINGDIS                                                       (0U)
#define DSS_DISPC_CONFIG1_BUFFERFILLING_FIFOFILLINGENB                                                       (1U)

#define DSS_DISPC_CONFIG1_LCDALPHABLENDERENABLE_SHIFT                                                       (18U)
#define DSS_DISPC_CONFIG1_LCDALPHABLENDERENABLE_MASK                                                        (0x00040000U)
#define DSS_DISPC_CONFIG1_LCDALPHABLENDERENABLE_DISABLE                                                      (0U)
#define DSS_DISPC_CONFIG1_LCDALPHABLENDERENABLE_ENABLE                                                       (1U)

#define DSS_DISPC_CONFIG1_TVALPHABLENDERENABLE_SHIFT                                                        (19U)
#define DSS_DISPC_CONFIG1_TVALPHABLENDERENABLE_MASK                                                         (0x00080000U)
#define DSS_DISPC_CONFIG1_TVALPHABLENDERENABLE_DISABLE                                                       (0U)
#define DSS_DISPC_CONFIG1_TVALPHABLENDERENABLE_ENABLE                                                        (1U)

#define DSS_DISPC_CONFIG1_BT656ENABLE_SHIFT                                                                 (20U)
#define DSS_DISPC_CONFIG1_BT656ENABLE_MASK                                                                  (0x00100000U)
#define DSS_DISPC_CONFIG1_BT656ENABLE_DISABLE                                                                (0U)
#define DSS_DISPC_CONFIG1_BT656ENABLE_ENABLE                                                                 (1U)

#define DSS_DISPC_CONFIG1_BT1120ENABLE_SHIFT                                                                (21U)
#define DSS_DISPC_CONFIG1_BT1120ENABLE_MASK                                                                 (0x00200000U)
#define DSS_DISPC_CONFIG1_BT1120ENABLE_DISABLE                                                               (0U)
#define DSS_DISPC_CONFIG1_BT1120ENABLE_ENABLE                                                                (1U)

#define DSS_DISPC_CONFIG1_OUTPUTMODEENABLE_SHIFT                                                            (22U)
#define DSS_DISPC_CONFIG1_OUTPUTMODEENABLE_MASK                                                             (0x00400000U)
#define DSS_DISPC_CONFIG1_OUTPUTMODEENABLE_DISABLE                                                           (0U)
#define DSS_DISPC_CONFIG1_OUTPUTMODEENABLE_ENABLE                                                            (1U)

#define DSS_DISPC_CONFIG1_COLORCONVENABLE_SHIFT                                                             (24U)
#define DSS_DISPC_CONFIG1_COLORCONVENABLE_MASK                                                              (0x01000000U)
#define DSS_DISPC_CONFIG1_COLORCONVENABLE_COLSPCDIS                                                          (0U)
#define DSS_DISPC_CONFIG1_COLORCONVENABLE_COLSPCENB                                                          (1U)

#define DSS_DISPC_CONFIG1_FULLRANGE_SHIFT                                                                   (25U)
#define DSS_DISPC_CONFIG1_FULLRANGE_MASK                                                                    (0x02000000U)
#define DSS_DISPC_CONFIG1_FULLRANGE_LIMRANGE                                                                 (0U)
#define DSS_DISPC_CONFIG1_FULLRANGE_FULLRANGE                                                                (1U)

#define DSS_DISPC_CONFIG1_FIDFIRST_SHIFT                                                                    (23U)
#define DSS_DISPC_CONFIG1_FIDFIRST_MASK                                                                     (0x00800000U)
#define DSS_DISPC_CONFIG1_FIDFIRST_EVEN                                                                      (0U)
#define DSS_DISPC_CONFIG1_FIDFIRST_ODD                                                                       (1U)

#define DSS_DISPC_CONFIG1_TVINTERLEAVE_SHIFT                                                                (28U)
#define DSS_DISPC_CONFIG1_TVINTERLEAVE_MASK                                                                 (0x30000000U)

#define DSS_DISPC_CONFIG1_PLCDINTERLEAVE_SHIFT                                                              (26U)
#define DSS_DISPC_CONFIG1_PLCDINTERLEAVE_MASK                                                               (0x0c000000U)

#define DSS_DISPC_CONFIG1_RESERVED_SHIFT                                                                    (30U)
#define DSS_DISPC_CONFIG1_RESERVED_MASK                                                                     (0xc0000000U)

#define DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_SHIFT                                                         (0U)
#define DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_MASK                                                          (0x00ffffffU)

#define DSS_DISPC_DEFAULT_COLOR0_RESERVED_15_SHIFT                                                          (24U)
#define DSS_DISPC_DEFAULT_COLOR0_RESERVED_15_MASK                                                           (0xff000000U)

#define DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_SHIFT                                                         (0U)
#define DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_MASK                                                          (0x00ffffffU)

#define DSS_DISPC_DEFAULT_COLOR1_RESERVED_15_SHIFT                                                          (24U)
#define DSS_DISPC_DEFAULT_COLOR1_RESERVED_15_MASK                                                           (0xff000000U)

#define DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_SHIFT                                                          (0U)
#define DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_MASK                                                           (0x00ffffffU)

#define DSS_DISPC_TRANS_COLOR0_RESERVED_48_SHIFT                                                            (24U)
#define DSS_DISPC_TRANS_COLOR0_RESERVED_48_MASK                                                             (0xff000000U)

#define DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_SHIFT                                                          (0U)
#define DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_MASK                                                           (0x00ffffffU)

#define DSS_DISPC_TRANS_COLOR1_RESERVED_48_SHIFT                                                            (24U)
#define DSS_DISPC_TRANS_COLOR1_RESERVED_48_MASK                                                             (0xff000000U)

#define DSS_DISPC_LINE_STATUS_LINENUMBER_SHIFT                                                              (0U)
#define DSS_DISPC_LINE_STATUS_LINENUMBER_MASK                                                               (0x00000fffU)

#define DSS_DISPC_LINE_STATUS_RESERVED_SHIFT                                                                (12U)
#define DSS_DISPC_LINE_STATUS_RESERVED_MASK                                                                 (0xfffff000U)

#define DSS_DISPC_LINE_NUMBER_LINENUMBER_SHIFT                                                              (0U)
#define DSS_DISPC_LINE_NUMBER_LINENUMBER_MASK                                                               (0x00000fffU)

#define DSS_DISPC_LINE_NUMBER_RESERVED_SHIFT                                                                (12U)
#define DSS_DISPC_LINE_NUMBER_RESERVED_MASK                                                                 (0xfffff000U)

#define DSS_DISPC_TIMING_H1_HBP_SHIFT                                                                       (20U)
#define DSS_DISPC_TIMING_H1_HBP_MASK                                                                        (0xfff00000U)

#define DSS_DISPC_TIMING_H1_HFP_SHIFT                                                                       (8U)
#define DSS_DISPC_TIMING_H1_HFP_MASK                                                                        (0x000fff00U)

#define DSS_DISPC_TIMING_H1_HSW_SHIFT                                                                       (0U)
#define DSS_DISPC_TIMING_H1_HSW_MASK                                                                        (0x000000ffU)

#define DSS_DISPC_TIMING_V1_VBP_SHIFT                                                                       (20U)
#define DSS_DISPC_TIMING_V1_VBP_MASK                                                                        (0xfff00000U)

#define DSS_DISPC_TIMING_V1_VFP_SHIFT                                                                       (8U)
#define DSS_DISPC_TIMING_V1_VFP_MASK                                                                        (0x000fff00U)

#define DSS_DISPC_TIMING_V1_VSW_SHIFT                                                                       (0U)
#define DSS_DISPC_TIMING_V1_VSW_MASK                                                                        (0x000000ffU)

#define DSS_DISPC_POL_FREQ1_ACBI_SHIFT                                                                      (8U)
#define DSS_DISPC_POL_FREQ1_ACBI_MASK                                                                       (0x00000f00U)

#define DSS_DISPC_POL_FREQ1_IHS_SHIFT                                                                       (13U)
#define DSS_DISPC_POL_FREQ1_IHS_MASK                                                                        (0x00002000U)
#define DSS_DISPC_POL_FREQ1_IHS_LCKPINAH                                                                     (0U)
#define DSS_DISPC_POL_FREQ1_IHS_LCKPINAL                                                                     (1U)

#define DSS_DISPC_POL_FREQ1_IEO_SHIFT                                                                       (15U)
#define DSS_DISPC_POL_FREQ1_IEO_MASK                                                                        (0x00008000U)
#define DSS_DISPC_POL_FREQ1_IEO_ACBAHIGH                                                                     (0U)
#define DSS_DISPC_POL_FREQ1_IEO_ACBALOW                                                                      (1U)

#define DSS_DISPC_POL_FREQ1_ONOFF_SHIFT                                                                     (17U)
#define DSS_DISPC_POL_FREQ1_ONOFF_MASK                                                                      (0x00020000U)
#define DSS_DISPC_POL_FREQ1_ONOFF_DOPEDPCK                                                                   (0U)
#define DSS_DISPC_POL_FREQ1_ONOFF_DBIT16                                                                     (1U)

#define DSS_DISPC_POL_FREQ1_ACB_SHIFT                                                                       (0U)
#define DSS_DISPC_POL_FREQ1_ACB_MASK                                                                        (0x000000ffU)

#define DSS_DISPC_POL_FREQ1_IVS_SHIFT                                                                       (12U)
#define DSS_DISPC_POL_FREQ1_IVS_MASK                                                                        (0x00001000U)
#define DSS_DISPC_POL_FREQ1_IVS_FCKPINAH                                                                     (0U)
#define DSS_DISPC_POL_FREQ1_IVS_FCKPINAL                                                                     (1U)

#define DSS_DISPC_POL_FREQ1_IPC_SHIFT                                                                       (14U)
#define DSS_DISPC_POL_FREQ1_IPC_MASK                                                                        (0x00004000U)
#define DSS_DISPC_POL_FREQ1_IPC_DRPCK                                                                        (0U)
#define DSS_DISPC_POL_FREQ1_IPC_DFPCK                                                                        (1U)

#define DSS_DISPC_POL_FREQ1_RF_SHIFT                                                                        (16U)
#define DSS_DISPC_POL_FREQ1_RF_MASK                                                                         (0x00010000U)
#define DSS_DISPC_POL_FREQ1_RF_DFEDPCK                                                                       (0U)
#define DSS_DISPC_POL_FREQ1_RF_DRIEDPCK                                                                      (1U)

#define DSS_DISPC_POL_FREQ1_ALIGN_SHIFT                                                                     (18U)
#define DSS_DISPC_POL_FREQ1_ALIGN_MASK                                                                      (0x00040000U)
#define DSS_DISPC_POL_FREQ1_ALIGN_NOTALIGNED                                                                 (0U)
#define DSS_DISPC_POL_FREQ1_ALIGN_ALIGNED                                                                    (1U)

#define DSS_DISPC_POL_FREQ1_RESERVED_SHIFT                                                                  (19U)
#define DSS_DISPC_POL_FREQ1_RESERVED_MASK                                                                   (0xfff80000U)

#define DSS_DISPC_DIVISOR1_RESERVED_16_SHIFT                                                                (24U)
#define DSS_DISPC_DIVISOR1_RESERVED_16_MASK                                                                 (0xff000000U)

#define DSS_DISPC_DIVISOR1_RESERVED_17_SHIFT                                                                (8U)
#define DSS_DISPC_DIVISOR1_RESERVED_17_MASK                                                                 (0x0000ff00U)

#define DSS_DISPC_DIVISOR1_PCD_SHIFT                                                                        (0U)
#define DSS_DISPC_DIVISOR1_PCD_MASK                                                                         (0x000000ffU)

#define DSS_DISPC_DIVISOR1_LCD_SHIFT                                                                        (16U)
#define DSS_DISPC_DIVISOR1_LCD_MASK                                                                         (0x00ff0000U)

#define DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_SHIFT                                                         (0U)
#define DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_MASK                                                          (0x000000ffU)

#define DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_SHIFT                                                        (16U)
#define DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_MASK                                                         (0x00ff0000U)

#define DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_SHIFT                                                        (24U)
#define DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_MASK                                                         (0xff000000U)

#define DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_SHIFT                                                        (8U)
#define DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_MASK                                                         (0x0000ff00U)

#define DSS_DISPC_SIZE_TV_LPP_SHIFT                                                                         (16U)
#define DSS_DISPC_SIZE_TV_LPP_MASK                                                                          (0x0fff0000U)

#define DSS_DISPC_SIZE_TV_PPL_SHIFT                                                                         (0U)
#define DSS_DISPC_SIZE_TV_PPL_MASK                                                                          (0x00000fffU)

#define DSS_DISPC_SIZE_TV_DELTA_LPP_SHIFT                                                                   (14U)
#define DSS_DISPC_SIZE_TV_DELTA_LPP_MASK                                                                    (0x0000c000U)
#define DSS_DISPC_SIZE_TV_DELTA_LPP_SAME                                                                     (0U)
#define DSS_DISPC_SIZE_TV_DELTA_LPP_PLUSONE                                                                  (1U)
#define DSS_DISPC_SIZE_TV_DELTA_LPP_MINUSONE                                                                 (2U)

#define DSS_DISPC_SIZE_TV_RESERVED_SHIFT                                                                    (12U)
#define DSS_DISPC_SIZE_TV_RESERVED_MASK                                                                     (0x00003000U)

#define DSS_DISPC_SIZE_TV_RESERVED1_SHIFT                                                                   (28U)
#define DSS_DISPC_SIZE_TV_RESERVED1_MASK                                                                    (0xf0000000U)

#define DSS_DISPC_SIZE_LCD1_LPP_SHIFT                                                                       (16U)
#define DSS_DISPC_SIZE_LCD1_LPP_MASK                                                                        (0x0fff0000U)

#define DSS_DISPC_SIZE_LCD1_PPL_SHIFT                                                                       (0U)
#define DSS_DISPC_SIZE_LCD1_PPL_MASK                                                                        (0x00000fffU)

#define DSS_DISPC_SIZE_LCD1_DELTA_LPP_SHIFT                                                                 (14U)
#define DSS_DISPC_SIZE_LCD1_DELTA_LPP_MASK                                                                  (0x0000c000U)
#define DSS_DISPC_SIZE_LCD1_DELTA_LPP_SAME                                                                   (0U)
#define DSS_DISPC_SIZE_LCD1_DELTA_LPP_PLUSONE                                                                (1U)
#define DSS_DISPC_SIZE_LCD1_DELTA_LPP_MINUSONE                                                               (2U)

#define DSS_DISPC_SIZE_LCD1_RESERVED_SHIFT                                                                  (12U)
#define DSS_DISPC_SIZE_LCD1_RESERVED_MASK                                                                   (0x00003000U)

#define DSS_DISPC_SIZE_LCD1_RESERVED1_SHIFT                                                                 (28U)
#define DSS_DISPC_SIZE_LCD1_RESERVED1_MASK                                                                  (0xf0000000U)

#define DSS_DISPC_GFX_BA_BA_SHIFT                                                                           (0U)
#define DSS_DISPC_GFX_BA_BA_MASK                                                                            (0xffffffffU)

#define DSS_DISPC_GFX_POSITION_POSX_SHIFT                                                                   (0U)
#define DSS_DISPC_GFX_POSITION_POSX_MASK                                                                    (0x000007ffU)

#define DSS_DISPC_GFX_POSITION_RESERVED_23_SHIFT                                                            (27U)
#define DSS_DISPC_GFX_POSITION_RESERVED_23_MASK                                                             (0xf8000000U)

#define DSS_DISPC_GFX_POSITION_POSY_SHIFT                                                                   (16U)
#define DSS_DISPC_GFX_POSITION_POSY_MASK                                                                    (0x07ff0000U)

#define DSS_DISPC_GFX_POSITION_RESERVED_24_SHIFT                                                            (11U)
#define DSS_DISPC_GFX_POSITION_RESERVED_24_MASK                                                             (0x0000f800U)

#define DSS_DISPC_GFX_SIZE_SIZEY_SHIFT                                                                      (16U)
#define DSS_DISPC_GFX_SIZE_SIZEY_MASK                                                                       (0x0fff0000U)

#define DSS_DISPC_GFX_SIZE_RESERVED_26_SHIFT                                                                (11U)
#define DSS_DISPC_GFX_SIZE_RESERVED_26_MASK                                                                 (0x0000f800U)

#define DSS_DISPC_GFX_SIZE_SIZEX_SHIFT                                                                      (0U)
#define DSS_DISPC_GFX_SIZE_SIZEX_MASK                                                                       (0x000007ffU)

#define DSS_DISPC_GFX_SIZE_RESERVED_SHIFT                                                                   (28U)
#define DSS_DISPC_GFX_SIZE_RESERVED_MASK                                                                    (0xf0000000U)

#define DSS_DISPC_GFX_ATTRIBUTES_NIBBLEMODE_SHIFT                                                           (9U)
#define DSS_DISPC_GFX_ATTRIBUTES_NIBBLEMODE_MASK                                                            (0x00000200U)
#define DSS_DISPC_GFX_ATTRIBUTES_NIBBLEMODE_NIBMDIS                                                          (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_NIBBLEMODE_NIBMENB                                                          (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT_SHIFT                                                           (8U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT_MASK                                                            (0x00000100U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT_LCDOPSEL                                                         (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT_TVOPSEL                                                          (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_REPLICATIONENABLE_SHIFT                                                    (5U)
#define DSS_DISPC_GFX_ATTRIBUTES_REPLICATIONENABLE_MASK                                                     (0x00000020U)
#define DSS_DISPC_GFX_ATTRIBUTES_REPLICATIONENABLE_GRLOGENB                                                  (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_REPLICATIONENABLE_GRLOGDIS                                                  (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_ENABLE_SHIFT                                                               (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ENABLE_MASK                                                                (0x00000001U)
#define DSS_DISPC_GFX_ATTRIBUTES_ENABLE_GRAPHICSDIS                                                          (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ENABLE_GRAPHICSENB                                                          (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_SHIFT                                                            (6U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_MASK                                                             (0x000000c0U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_BURST2X128                                                        (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_BURST4X128                                                        (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_BURST8X128                                                        (2U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE_RES                                                               (3U)

#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_SHIFT                                                               (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_MASK                                                                (0x0000001eU)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_BGRA32                                                               (3U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_XRGB12                                                               (4U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGB16                                                                (6U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_XRGB24                                                               (8U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGB24P                                                               (9U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_ARGB16                                                               (5U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_ARGB32                                                               (12U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGBA32                                                               (13U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGBX24                                                               (14U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_ARGB16_1                                                             (7U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_XRGB15                                                               (15U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGBX12                                                               (10U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORMAT_RGBA12                                                               (11U)

#define DSS_DISPC_GFX_ATTRIBUTES_BUFPRELOAD_SHIFT                                                           (11U)
#define DSS_DISPC_GFX_ATTRIBUTES_BUFPRELOAD_MASK                                                            (0x00000800U)
#define DSS_DISPC_GFX_ATTRIBUTES_BUFPRELOAD_HIGHTHRES                                                        (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_BUFPRELOAD_DEFVAL                                                           (0U)

#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_SHIFT                                                             (12U)
#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_MASK                                                              (0x00003000U)
#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_NOROT                                                              (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_ROT90                                                              (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_ROT180                                                             (2U)
#define DSS_DISPC_GFX_ATTRIBUTES_ROTATION_ROT270                                                             (3U)

#define DSS_DISPC_GFX_ATTRIBUTES_ARBITRATION_SHIFT                                                          (14U)
#define DSS_DISPC_GFX_ATTRIBUTES_ARBITRATION_MASK                                                           (0x00004000U)
#define DSS_DISPC_GFX_ATTRIBUTES_ARBITRATION_NORMALPRIO                                                      (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ARBITRATION_HIGHPRIO                                                        (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESH_SHIFT                                                          (15U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESH_MASK                                                           (0x00008000U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESH_SELFREFRESHDIS                                                  (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESH_SELFREFRESHENB                                                  (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_SHIFT                                                          (30U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_MASK                                                           (0xc0000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_PRIMARYLCDSEL                                                   (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_SECONDARYLCDSEL                                                 (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_WRITEBACKSEL                                                    (3U)
#define DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2_THIRDLCDSEL                                                     (2U)

#define DSS_DISPC_GFX_ATTRIBUTES_BURSTTYPE_SHIFT                                                            (29U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTTYPE_MASK                                                             (0x20000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTTYPE_INC                                                               (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_BURSTTYPE_BLCK                                                              (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_SHIFT                                                               (26U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_MASK                                                                (0x0c000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_ZORDER0                                                              (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_ZORDER1                                                              (1U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_ZORDER2                                                              (2U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDER_ZORDER3                                                              (3U)

#define DSS_DISPC_GFX_ATTRIBUTES_ZORDERENABLE_SHIFT                                                         (25U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDERENABLE_MASK                                                          (0x02000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDERENABLE_ZORDERDIS                                                      (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ZORDERENABLE_ZORDERENB                                                      (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_PREMULTIPLYALPHA_SHIFT                                                     (28U)
#define DSS_DISPC_GFX_ATTRIBUTES_PREMULTIPLYALPHA_MASK                                                      (0x10000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA                                      (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA                                         (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_ANTIFLICKER_SHIFT                                                          (24U)
#define DSS_DISPC_GFX_ATTRIBUTES_ANTIFLICKER_MASK                                                           (0x01000000U)
#define DSS_DISPC_GFX_ATTRIBUTES_ANTIFLICKER_AFDIS                                                           (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_ANTIFLICKER_AFENB                                                           (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESHAUTO_SHIFT                                                      (17U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESHAUTO_MASK                                                       (0x00020000U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTODIS                                          (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTOEN                                           (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                                     (16U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                                      (0x00010000U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                                       (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                                       (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_FRAMEPACKINGMODE_SHIFT                                                     (10U)
#define DSS_DISPC_GFX_ATTRIBUTES_FRAMEPACKINGMODE_MASK                                                      (0x00000400U)
#define DSS_DISPC_GFX_ATTRIBUTES_FRAMEPACKINGMODE_FPMDIS                                                     (0U)
#define DSS_DISPC_GFX_ATTRIBUTES_FRAMEPACKINGMODE_FPMENB                                                     (1U)

#define DSS_DISPC_GFX_ATTRIBUTES_SUBSAMPLINGPATTERN_SHIFT                                                   (18U)
#define DSS_DISPC_GFX_ATTRIBUTES_SUBSAMPLINGPATTERN_MASK                                                    (0x001c0000U)

#define DSS_DISPC_GFX_ATTRIBUTES_RESERVED_SHIFT                                                             (21U)
#define DSS_DISPC_GFX_ATTRIBUTES_RESERVED_MASK                                                              (0x00e00000U)

#define DSS_DISPC_GFX_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                                   (0U)
#define DSS_DISPC_GFX_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                                    (0x0000ffffU)

#define DSS_DISPC_GFX_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                                  (16U)
#define DSS_DISPC_GFX_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                                   (0xffff0000U)

#define DSS_DISPC_GFX_BUF_SIZE_STATUS_RESERVED_19_SHIFT                                                     (16U)
#define DSS_DISPC_GFX_BUF_SIZE_STATUS_RESERVED_19_MASK                                                      (0xffff0000U)

#define DSS_DISPC_GFX_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                                         (0U)
#define DSS_DISPC_GFX_BUF_SIZE_STATUS_BUFSIZE_MASK                                                          (0x0000ffffU)

#define DSS_DISPC_GFX_ROW_INC_ROWINC_SHIFT                                                                  (0U)
#define DSS_DISPC_GFX_ROW_INC_ROWINC_MASK                                                                   (0xffffffffU)

#define DSS_DISPC_GFX_PIXEL_INC_RESERVED_22_SHIFT                                                           (8U)
#define DSS_DISPC_GFX_PIXEL_INC_RESERVED_22_MASK                                                            (0xffffff00U)

#define DSS_DISPC_GFX_PIXEL_INC_PIXELINC_SHIFT                                                              (0U)
#define DSS_DISPC_GFX_PIXEL_INC_PIXELINC_MASK                                                               (0x000000ffU)

#define DSS_DISPC_GFX_TABLE_BA_TABLEBA_SHIFT                                                                (0U)
#define DSS_DISPC_GFX_TABLE_BA_TABLEBA_MASK                                                                 (0xffffffffU)

#define DSS_DISPC_VID1_BA_BA_SHIFT                                                                          (0U)
#define DSS_DISPC_VID1_BA_BA_MASK                                                                           (0xffffffffU)

#define DSS_DISPC_VID1_POSITION_RESERVED_69_SHIFT                                                           (27U)
#define DSS_DISPC_VID1_POSITION_RESERVED_69_MASK                                                            (0xf8000000U)

#define DSS_DISPC_VID1_POSITION_POSY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID1_POSITION_POSY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID1_POSITION_RESERVED_70_SHIFT                                                           (11U)
#define DSS_DISPC_VID1_POSITION_RESERVED_70_MASK                                                            (0x0000f800U)

#define DSS_DISPC_VID1_POSITION_POSX_SHIFT                                                                  (0U)
#define DSS_DISPC_VID1_POSITION_POSX_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID1_SIZE_SIZEY_SHIFT                                                                     (16U)
#define DSS_DISPC_VID1_SIZE_SIZEY_MASK                                                                      (0x0fff0000U)

#define DSS_DISPC_VID1_SIZE_SIZEX_SHIFT                                                                     (0U)
#define DSS_DISPC_VID1_SIZE_SIZEX_MASK                                                                      (0x00000fffU)

#define DSS_DISPC_VID1_SIZE_RESERVED_SHIFT                                                                  (12U)
#define DSS_DISPC_VID1_SIZE_RESERVED_MASK                                                                   (0x0000f000U)

#define DSS_DISPC_VID1_SIZE_RESERVED1_SHIFT                                                                 (28U)
#define DSS_DISPC_VID1_SIZE_RESERVED1_MASK                                                                  (0xf0000000U)

#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESHAUTO_SHIFT                                                     (17U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESHAUTO_MASK                                                      (0x00020000U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTODIS                                         (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTOEN                                          (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_FULLRANGE_SHIFT                                                           (11U)
#define DSS_DISPC_VID1_ATTRIBUTES_FULLRANGE_MASK                                                            (0x00000800U)
#define DSS_DISPC_VID1_ATTRIBUTES_FULLRANGE_LIMRANGE                                                         (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_FULLRANGE_FULLRANGE                                                        (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT_SHIFT                                                          (16U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT_MASK                                                           (0x00010000U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT_LCDOP                                                           (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT_TVOP                                                            (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_100_SHIFT                                                        (18U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_100_MASK                                                         (0x00040000U)

#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_SHIFT                                                            (12U)
#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_MASK                                                             (0x00003000U)
#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_NOROT                                                             (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_ROT90                                                             (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_ROT180                                                            (2U)
#define DSS_DISPC_VID1_ATTRIBUTES_ROTATION_ROT270                                                            (3U)

#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_SHIFT                                                        (5U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_MASK                                                         (0x00000060U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_RESIZEPROC                                                    (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE                                                       (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE                                                       (2U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HVRESIZE                                                      (3U)

#define DSS_DISPC_VID1_ATTRIBUTES_REPLICATIONENABLE_SHIFT                                                   (10U)
#define DSS_DISPC_VID1_ATTRIBUTES_REPLICATIONENABLE_MASK                                                    (0x00000400U)
#define DSS_DISPC_VID1_ATTRIBUTES_REPLICATIONENABLE_VREPLDIS                                                 (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_REPLICATIONENABLE_VREPLENB                                                 (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_SHIFT                                                           (14U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_MASK                                                            (0x0000c000U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_BURST2X128B                                                      (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_BURST4X128B                                                      (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_BURST8X128B                                                      (2U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE_RES                                                              (3U)

#define DSS_DISPC_VID1_ATTRIBUTES_HRESIZECONF_SHIFT                                                         (7U)
#define DSS_DISPC_VID1_ATTRIBUTES_HRESIZECONF_MASK                                                          (0x00000080U)

#define DSS_DISPC_VID1_ATTRIBUTES_COLORCONVENABLE_SHIFT                                                     (9U)
#define DSS_DISPC_VID1_ATTRIBUTES_COLORCONVENABLE_MASK                                                      (0x00000200U)
#define DSS_DISPC_VID1_ATTRIBUTES_COLORCONVENABLE_COLSPCDIS                                                  (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_COLORCONVENABLE_COLSPCENB                                                  (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_ENABLE_SHIFT                                                              (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ENABLE_MASK                                                               (0x00000001U)
#define DSS_DISPC_VID1_ATTRIBUTES_ENABLE_VIDEODIS                                                            (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ENABLE_VIDEOENB                                                            (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_SHIFT                                                              (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_MASK                                                               (0x0000001eU)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_YUV2                                                                (10U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_UYVY                                                                (11U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_NV12                                                                (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_XRGB12                                                              (4U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGB16                                                               (6U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_XRGB24                                                              (8U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGB24P                                                              (9U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_ARGB16                                                              (5U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_ARGB32                                                              (12U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGBA32                                                              (13U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGBX24                                                              (14U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_ARGB16_1                                                            (7U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_XRGB15                                                              (15U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGBX12                                                              (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_RGBA12                                                              (2U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORMAT_BGRA32                                                              (3U)

#define DSS_DISPC_VID1_ATTRIBUTES_BUFPRELOAD_SHIFT                                                          (19U)
#define DSS_DISPC_VID1_ATTRIBUTES_BUFPRELOAD_MASK                                                           (0x00080000U)
#define DSS_DISPC_VID1_ATTRIBUTES_BUFPRELOAD_DEFVAL                                                          (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_BUFPRELOAD_HIGHTHRES                                                       (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_SHIFT                                                        (21U)
#define DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_MASK                                                         (0x00200000U)
#define DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS3                                                         (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS5                                                         (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESH_SHIFT                                                         (24U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESH_MASK                                                          (0x01000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESH_SELFREFRESHDIS                                                 (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESH_SELFREFRESHENB                                                 (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_ARBITRATION_SHIFT                                                         (23U)
#define DSS_DISPC_VID1_ATTRIBUTES_ARBITRATION_MASK                                                          (0x00800000U)
#define DSS_DISPC_VID1_ATTRIBUTES_ARBITRATION_NORMALPRIO                                                     (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ARBITRATION_HIGHPRIO                                                       (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_SHIFT                                                            (5U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_MASK                                                             (0x00000020U)

#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_1_SHIFT                                                          (7U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_1_MASK                                                           (0x00000080U)

#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_3_SHIFT                                                          (8U)
#define DSS_DISPC_VID1_ATTRIBUTES_RESERVED_3_MASK                                                           (0x00000100U)

#define DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE_SHIFT                                                        (25U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE_MASK                                                         (0x02000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE_ZORDERDIS                                                     (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE_ZORDERENB                                                     (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_SHIFT                                                              (26U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_MASK                                                               (0x0c000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_ZORDER0                                                             (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_ZORDER1                                                             (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_ZORDER2                                                             (2U)
#define DSS_DISPC_VID1_ATTRIBUTES_ZORDER_ZORDER3                                                             (3U)

#define DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA_SHIFT                                                    (28U)
#define DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA_MASK                                                     (0x10000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA_NONPREMULTIPLIEDALPHA                                     (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA_PREMULTIPLIEDALPHA                                        (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_BURSTTYPE_SHIFT                                                           (29U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTTYPE_MASK                                                            (0x20000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTTYPE_INC                                                              (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_BURSTTYPE_BLCK                                                             (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_SHIFT                                                         (30U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_MASK                                                          (0xc0000000U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_PRIMARYLCDSEL                                                  (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_SECONDARYLCDSEL                                                (1U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_WRITEBACKSEL                                                   (3U)
#define DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2_THIRDLCDSEL                                                    (2U)

#define DSS_DISPC_VID1_ATTRIBUTES_DOUBLESTRIDE_SHIFT                                                        (22U)
#define DSS_DISPC_VID1_ATTRIBUTES_DOUBLESTRIDE_MASK                                                         (0x00400000U)
#define DSS_DISPC_VID1_ATTRIBUTES_DOUBLESTRIDE_INITIAL                                                       (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_DOUBLESTRIDE_DOUBLE                                                        (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                                    (20U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                                     (0x00100000U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                                      (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                                      (1U)

#define DSS_DISPC_VID1_ATTRIBUTES_FRAMEPACKINGMODE_SHIFT                                                    (8U)
#define DSS_DISPC_VID1_ATTRIBUTES_FRAMEPACKINGMODE_MASK                                                     (0x00000100U)
#define DSS_DISPC_VID1_ATTRIBUTES_FRAMEPACKINGMODE_FPMDIS                                                    (0U)
#define DSS_DISPC_VID1_ATTRIBUTES_FRAMEPACKINGMODE_FPMENB                                                    (1U)

#define DSS_DISPC_VID1_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                                  (0U)
#define DSS_DISPC_VID1_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                                   (0x0000ffffU)

#define DSS_DISPC_VID1_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                                 (16U)
#define DSS_DISPC_VID1_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                                  (0xffff0000U)

#define DSS_DISPC_VID1_BUF_SIZE_STATUS_RESERVED_61_SHIFT                                                    (16U)
#define DSS_DISPC_VID1_BUF_SIZE_STATUS_RESERVED_61_MASK                                                     (0xffff0000U)

#define DSS_DISPC_VID1_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                                        (0U)
#define DSS_DISPC_VID1_BUF_SIZE_STATUS_BUFSIZE_MASK                                                         (0x0000ffffU)

#define DSS_DISPC_VID1_ROW_INC_ROWINC_SHIFT                                                                 (0U)
#define DSS_DISPC_VID1_ROW_INC_ROWINC_MASK                                                                  (0xffffffffU)

#define DSS_DISPC_VID1_PIXEL_INC_RESERVED_68_SHIFT                                                          (8U)
#define DSS_DISPC_VID1_PIXEL_INC_RESERVED_68_MASK                                                           (0xffffff00U)

#define DSS_DISPC_VID1_PIXEL_INC_PIXELINC_SHIFT                                                             (0U)
#define DSS_DISPC_VID1_PIXEL_INC_PIXELINC_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID1_FIR_RESERVED_64_SHIFT                                                                (29U)
#define DSS_DISPC_VID1_FIR_RESERVED_64_MASK                                                                 (0xe0000000U)

#define DSS_DISPC_VID1_FIR_FIRVINC_SHIFT                                                                    (16U)
#define DSS_DISPC_VID1_FIR_FIRVINC_MASK                                                                     (0x1fff0000U)

#define DSS_DISPC_VID1_FIR_RESERVED_65_SHIFT                                                                (13U)
#define DSS_DISPC_VID1_FIR_RESERVED_65_MASK                                                                 (0x0000e000U)

#define DSS_DISPC_VID1_FIR_FIRHINC_SHIFT                                                                    (0U)
#define DSS_DISPC_VID1_FIR_FIRHINC_MASK                                                                     (0x00001fffU)

#define DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_SHIFT                                                          (16U)
#define DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_MASK                                                           (0x0fff0000U)

#define DSS_DISPC_VID1_PICTURE_SIZE_RESERVED_67_SHIFT                                                       (11U)
#define DSS_DISPC_VID1_PICTURE_SIZE_RESERVED_67_MASK                                                        (0x0000f800U)

#define DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_SHIFT                                                          (0U)
#define DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_MASK                                                           (0x000007ffU)

#define DSS_DISPC_VID1_PICTURE_SIZE_RESERVED_SHIFT                                                          (28U)
#define DSS_DISPC_VID1_PICTURE_SIZE_RESERVED_MASK                                                           (0xf0000000U)

#define DSS_DISPC_VID1_ACCU_HORIZONTALACCU_SHIFT                                                            (0U)
#define DSS_DISPC_VID1_ACCU_HORIZONTALACCU_MASK                                                             (0x000007ffU)

#define DSS_DISPC_VID1_ACCU_VERTICALACCU_SHIFT                                                              (16U)
#define DSS_DISPC_VID1_ACCU_VERTICALACCU_MASK                                                               (0x07ff0000U)

#define DSS_DISPC_VID1_ACCU_RESERVED_SHIFT                                                                  (11U)
#define DSS_DISPC_VID1_ACCU_RESERVED_MASK                                                                   (0x0000f800U)

#define DSS_DISPC_VID1_ACCU_RESERVED1_SHIFT                                                                 (27U)
#define DSS_DISPC_VID1_ACCU_RESERVED1_MASK                                                                  (0xf8000000U)

#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_SHIFT                                                              (16U)
#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_MASK                                                               (0x00ff0000U)

#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_SHIFT                                                              (8U)
#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_MASK                                                               (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_SHIFT                                                              (0U)
#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_MASK                                                               (0x000000ffU)

#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_SHIFT                                                              (24U)
#define DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_MASK                                                               (0xff000000U)

#define DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_SHIFT                                                             (0U)
#define DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_SHIFT                                                             (8U)
#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_SHIFT                                                             (16U)
#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_SHIFT                                                             (24U)
#define DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID1_CONV_COEF0_RESERVED_52_SHIFT                                                         (27U)
#define DSS_DISPC_VID1_CONV_COEF0_RESERVED_52_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID1_CONV_COEF0_RCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID1_CONV_COEF0_RCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID1_CONV_COEF0_RESERVED_53_SHIFT                                                         (11U)
#define DSS_DISPC_VID1_CONV_COEF0_RESERVED_53_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID1_CONV_COEF0_RY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID1_CONV_COEF0_RY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID1_CONV_COEF1_RESERVED_54_SHIFT                                                         (27U)
#define DSS_DISPC_VID1_CONV_COEF1_RESERVED_54_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID1_CONV_COEF1_GY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID1_CONV_COEF1_GY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID1_CONV_COEF1_RESERVED_55_SHIFT                                                         (11U)
#define DSS_DISPC_VID1_CONV_COEF1_RESERVED_55_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID1_CONV_COEF1_RCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID1_CONV_COEF1_RCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID1_CONV_COEF2_RESERVED_56_SHIFT                                                         (27U)
#define DSS_DISPC_VID1_CONV_COEF2_RESERVED_56_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID1_CONV_COEF2_GCB_SHIFT                                                                 (16U)
#define DSS_DISPC_VID1_CONV_COEF2_GCB_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID1_CONV_COEF2_RESERVED_57_SHIFT                                                         (11U)
#define DSS_DISPC_VID1_CONV_COEF2_RESERVED_57_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID1_CONV_COEF2_GCR_SHIFT                                                                 (0U)
#define DSS_DISPC_VID1_CONV_COEF2_GCR_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID1_CONV_COEF3_RESERVED_58_SHIFT                                                         (27U)
#define DSS_DISPC_VID1_CONV_COEF3_RESERVED_58_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID1_CONV_COEF3_BCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID1_CONV_COEF3_BCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID1_CONV_COEF3_RESERVED_59_SHIFT                                                         (11U)
#define DSS_DISPC_VID1_CONV_COEF3_RESERVED_59_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID1_CONV_COEF3_BY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID1_CONV_COEF3_BY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID1_CONV_COEF4_RESERVED_60_SHIFT                                                         (11U)
#define DSS_DISPC_VID1_CONV_COEF4_RESERVED_60_MASK                                                          (0xfffff800U)

#define DSS_DISPC_VID1_CONV_COEF4_BCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID1_CONV_COEF4_BCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID2_BA_BA_SHIFT                                                                          (0U)
#define DSS_DISPC_VID2_BA_BA_MASK                                                                           (0xffffffffU)

#define DSS_DISPC_VID2_POSITION_RESERVED_93_SHIFT                                                           (27U)
#define DSS_DISPC_VID2_POSITION_RESERVED_93_MASK                                                            (0xf8000000U)

#define DSS_DISPC_VID2_POSITION_POSY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID2_POSITION_POSY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID2_POSITION_RESERVED_94_SHIFT                                                           (11U)
#define DSS_DISPC_VID2_POSITION_RESERVED_94_MASK                                                            (0x0000f800U)

#define DSS_DISPC_VID2_POSITION_POSX_SHIFT                                                                  (0U)
#define DSS_DISPC_VID2_POSITION_POSX_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID2_SIZE_SIZEY_SHIFT                                                                     (16U)
#define DSS_DISPC_VID2_SIZE_SIZEY_MASK                                                                      (0x0fff0000U)

#define DSS_DISPC_VID2_SIZE_SIZEX_SHIFT                                                                     (0U)
#define DSS_DISPC_VID2_SIZE_SIZEX_MASK                                                                      (0x00000fffU)

#define DSS_DISPC_VID2_SIZE_RESERVED_SHIFT                                                                  (12U)
#define DSS_DISPC_VID2_SIZE_RESERVED_MASK                                                                   (0x0000f000U)

#define DSS_DISPC_VID2_SIZE_RESERVED1_SHIFT                                                                 (28U)
#define DSS_DISPC_VID2_SIZE_RESERVED1_MASK                                                                  (0xf0000000U)

#define DSS_DISPC_VID2_ATTRIBUTES_FULLRANGE_SHIFT                                                           (11U)
#define DSS_DISPC_VID2_ATTRIBUTES_FULLRANGE_MASK                                                            (0x00000800U)
#define DSS_DISPC_VID2_ATTRIBUTES_FULLRANGE_LIMRANGE                                                         (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_FULLRANGE_FULLRANGE                                                        (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_SHIFT                                                            (12U)
#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_MASK                                                             (0x00003000U)
#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_NOROT                                                             (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_ROT90                                                             (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_ROT180                                                            (2U)
#define DSS_DISPC_VID2_ATTRIBUTES_ROTATION_ROT270                                                            (3U)

#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_SHIFT                                                        (5U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_MASK                                                         (0x00000020U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_RESIZEPROC                                                    (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_HRESIZE                                                       (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_VRESIZE                                                       (2U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESIZEENABLE_HVRESIZE                                                      (3U)

#define DSS_DISPC_VID2_ATTRIBUTES_REPLICATIONENABLE_SHIFT                                                   (10U)
#define DSS_DISPC_VID2_ATTRIBUTES_REPLICATIONENABLE_MASK                                                    (0x00000400U)
#define DSS_DISPC_VID2_ATTRIBUTES_REPLICATIONENABLE_VREPLDIS                                                 (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_REPLICATIONENABLE_VREPLENB                                                 (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_SHIFT                                                           (14U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_MASK                                                            (0x0000c000U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_BURST2X128B                                                      (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_BURST4X128B                                                      (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_BURST8X128B                                                      (2U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTSIZE_RES                                                              (3U)

#define DSS_DISPC_VID2_ATTRIBUTES_HRESIZECONF_SHIFT                                                         (7U)
#define DSS_DISPC_VID2_ATTRIBUTES_HRESIZECONF_MASK                                                          (0x00000080U)

#define DSS_DISPC_VID2_ATTRIBUTES_COLORCONVENABLE_SHIFT                                                     (9U)
#define DSS_DISPC_VID2_ATTRIBUTES_COLORCONVENABLE_MASK                                                      (0x00000200U)
#define DSS_DISPC_VID2_ATTRIBUTES_COLORCONVENABLE_COLSPCDIS                                                  (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_COLORCONVENABLE_COLSPCENB                                                  (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_ENABLE_SHIFT                                                              (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ENABLE_MASK                                                               (0x00000001U)
#define DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEODIS                                                            (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEOENB                                                            (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_BUFPRELOAD_SHIFT                                                          (19U)
#define DSS_DISPC_VID2_ATTRIBUTES_BUFPRELOAD_MASK                                                           (0x00080000U)
#define DSS_DISPC_VID2_ATTRIBUTES_BUFPRELOAD_DEFVAL                                                          (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_BUFPRELOAD_HIGHTHRES                                                       (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_VERTICALTAPS_SHIFT                                                        (21U)
#define DSS_DISPC_VID2_ATTRIBUTES_VERTICALTAPS_MASK                                                         (0x00200000U)
#define DSS_DISPC_VID2_ATTRIBUTES_VERTICALTAPS_TAPS5                                                         (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_VERTICALTAPS_TAPS3                                                         (0U)

#define DSS_DISPC_VID2_ATTRIBUTES_ARBITRATION_SHIFT                                                         (23U)
#define DSS_DISPC_VID2_ATTRIBUTES_ARBITRATION_MASK                                                          (0x00800000U)
#define DSS_DISPC_VID2_ATTRIBUTES_ARBITRATION_NORMALPRIO                                                     (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ARBITRATION_HIGHPRIO                                                       (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESH_SHIFT                                                         (24U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESH_MASK                                                          (0x01000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESH_SELFREFRESHDIS                                                 (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESH_SELFREFRESHENB                                                 (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_SHIFT                                                              (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_MASK                                                               (0x0000001eU)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_YUV2                                                                (10U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_UYVY                                                                (11U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_NV12                                                                (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_XRGB12                                                              (4U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGB16                                                               (6U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_XRGB24                                                              (8U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGB24                                                               (9U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_ARGB16                                                              (5U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_ARGB32                                                              (12U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGBA32                                                              (13U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGBX24                                                              (14U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_ARGB16_1                                                            (7U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_XRGB15                                                              (15U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGBX12                                                              (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_RGBA12                                                              (2U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORMAT_BGRA32                                                              (3U)

#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_SHIFT                                                            (5U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_MASK                                                             (0x00000020U)

#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_1_SHIFT                                                          (7U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_1_MASK                                                           (0x00000080U)

#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_2_SHIFT                                                          (8U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_2_MASK                                                           (0x00000100U)

#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_100_SHIFT                                                        (18U)
#define DSS_DISPC_VID2_ATTRIBUTES_RESERVED_100_MASK                                                         (0x00040000U)

#define DSS_DISPC_VID2_ATTRIBUTES_ZORDERENABLE_SHIFT                                                        (25U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDERENABLE_MASK                                                         (0x02000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDERENABLE_ZORDERDIS                                                     (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDERENABLE_ZORDERENB                                                     (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_SHIFT                                                              (26U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_MASK                                                               (0x0c000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_ZORDER0                                                             (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_ZORDER1                                                             (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_ZORDER2                                                             (2U)
#define DSS_DISPC_VID2_ATTRIBUTES_ZORDER_ZORDER3                                                             (3U)

#define DSS_DISPC_VID2_ATTRIBUTES_PREMULTIPLYALPHA_SHIFT                                                    (28U)
#define DSS_DISPC_VID2_ATTRIBUTES_PREMULTIPLYALPHA_MASK                                                     (0x10000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA                                     (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA                                        (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_BURSTTYPE_SHIFT                                                           (29U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTTYPE_MASK                                                            (0x20000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTTYPE_INC                                                              (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_BURSTTYPE_BLCK                                                             (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_SHIFT                                                         (30U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_MASK                                                          (0xc0000000U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_PRIMARYLCDSEL                                                  (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_SECONDARYLCDSEL                                                (1U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_WRITEBACKSEL                                                   (3U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT2_THIRDLCDSEL                                                    (2U)

#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT_SHIFT                                                          (16U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT_MASK                                                           (0x00010000U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT_LCDOP                                                           (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_CHANNELOUT_TVOP                                                            (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESHAUTO_SHIFT                                                     (17U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESHAUTO_MASK                                                      (0x00020000U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTODIS                                         (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTOEN                                          (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_DOUBLESTRIDE_SHIFT                                                        (22U)
#define DSS_DISPC_VID2_ATTRIBUTES_DOUBLESTRIDE_MASK                                                         (0x00400000U)
#define DSS_DISPC_VID2_ATTRIBUTES_DOUBLESTRIDE_INITIAL                                                       (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_DOUBLESTRIDE_DOUBLE                                                        (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                                    (20U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                                     (0x00100000U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                                      (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                                      (1U)

#define DSS_DISPC_VID2_ATTRIBUTES_FRAMEPACKINGMODE_SHIFT                                                    (8U)
#define DSS_DISPC_VID2_ATTRIBUTES_FRAMEPACKINGMODE_MASK                                                     (0x00000100U)
#define DSS_DISPC_VID2_ATTRIBUTES_FRAMEPACKINGMODE_FPMDIS                                                    (0U)
#define DSS_DISPC_VID2_ATTRIBUTES_FRAMEPACKINGMODE_FPMENB                                                    (1U)

#define DSS_DISPC_VID2_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                                  (0U)
#define DSS_DISPC_VID2_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                                   (0x0000ffffU)

#define DSS_DISPC_VID2_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                                 (16U)
#define DSS_DISPC_VID2_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                                  (0xffff0000U)

#define DSS_DISPC_VID2_BUF_SIZE_STATUS_RESERVED_85_SHIFT                                                    (16U)
#define DSS_DISPC_VID2_BUF_SIZE_STATUS_RESERVED_85_MASK                                                     (0xffff0000U)

#define DSS_DISPC_VID2_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                                        (0U)
#define DSS_DISPC_VID2_BUF_SIZE_STATUS_BUFSIZE_MASK                                                         (0x0000ffffU)

#define DSS_DISPC_VID2_ROW_INC_ROWINC_SHIFT                                                                 (0U)
#define DSS_DISPC_VID2_ROW_INC_ROWINC_MASK                                                                  (0xffffffffU)

#define DSS_DISPC_VID2_PIXEL_INC_RESERVED_92_SHIFT                                                          (8U)
#define DSS_DISPC_VID2_PIXEL_INC_RESERVED_92_MASK                                                           (0xffffff00U)

#define DSS_DISPC_VID2_PIXEL_INC_PIXELINC_SHIFT                                                             (0U)
#define DSS_DISPC_VID2_PIXEL_INC_PIXELINC_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID2_FIR_RESERVED_88_SHIFT                                                                (29U)
#define DSS_DISPC_VID2_FIR_RESERVED_88_MASK                                                                 (0xe0000000U)

#define DSS_DISPC_VID2_FIR_FIRVINC_SHIFT                                                                    (16U)
#define DSS_DISPC_VID2_FIR_FIRVINC_MASK                                                                     (0x1fff0000U)

#define DSS_DISPC_VID2_FIR_RESERVED_89_SHIFT                                                                (13U)
#define DSS_DISPC_VID2_FIR_RESERVED_89_MASK                                                                 (0x0000e000U)

#define DSS_DISPC_VID2_FIR_FIRHINC_SHIFT                                                                    (0U)
#define DSS_DISPC_VID2_FIR_FIRHINC_MASK                                                                     (0x00001fffU)

#define DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_SHIFT                                                          (16U)
#define DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_MASK                                                           (0x0fff0000U)

#define DSS_DISPC_VID2_PICTURE_SIZE_RESERVED_91_SHIFT                                                       (11U)
#define DSS_DISPC_VID2_PICTURE_SIZE_RESERVED_91_MASK                                                        (0x0000f800U)

#define DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_SHIFT                                                          (0U)
#define DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_MASK                                                           (0x000007ffU)

#define DSS_DISPC_VID2_PICTURE_SIZE_RESERVED_SHIFT                                                          (28U)
#define DSS_DISPC_VID2_PICTURE_SIZE_RESERVED_MASK                                                           (0xf0000000U)

#define DSS_DISPC_VID2_ACCU_HORIZONTALACCU_SHIFT                                                            (0U)
#define DSS_DISPC_VID2_ACCU_HORIZONTALACCU_MASK                                                             (0x000007ffU)

#define DSS_DISPC_VID2_ACCU_VERTICALACCU_SHIFT                                                              (16U)
#define DSS_DISPC_VID2_ACCU_VERTICALACCU_MASK                                                               (0x07ff0000U)

#define DSS_DISPC_VID2_ACCU_RESERVED_SHIFT                                                                  (11U)
#define DSS_DISPC_VID2_ACCU_RESERVED_MASK                                                                   (0x0000f800U)

#define DSS_DISPC_VID2_ACCU_RESERVED1_SHIFT                                                                 (27U)
#define DSS_DISPC_VID2_ACCU_RESERVED1_MASK                                                                  (0xf8000000U)

#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_SHIFT                                                              (16U)
#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_MASK                                                               (0x00ff0000U)

#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_SHIFT                                                              (8U)
#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_MASK                                                               (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_SHIFT                                                              (0U)
#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_MASK                                                               (0x000000ffU)

#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_SHIFT                                                              (24U)
#define DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_MASK                                                               (0xff000000U)

#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_SHIFT                                                             (16U)
#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_SHIFT                                                             (8U)
#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_SHIFT                                                             (0U)
#define DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_SHIFT                                                             (24U)
#define DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID2_CONV_COEF0_RESERVED_76_SHIFT                                                         (27U)
#define DSS_DISPC_VID2_CONV_COEF0_RESERVED_76_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID2_CONV_COEF0_RCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID2_CONV_COEF0_RCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID2_CONV_COEF0_RESERVED_77_SHIFT                                                         (11U)
#define DSS_DISPC_VID2_CONV_COEF0_RESERVED_77_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID2_CONV_COEF0_RY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID2_CONV_COEF0_RY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID2_CONV_COEF1_RESERVED_78_SHIFT                                                         (27U)
#define DSS_DISPC_VID2_CONV_COEF1_RESERVED_78_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID2_CONV_COEF1_GY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID2_CONV_COEF1_GY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID2_CONV_COEF1_RESERVED_79_SHIFT                                                         (11U)
#define DSS_DISPC_VID2_CONV_COEF1_RESERVED_79_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID2_CONV_COEF1_RCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID2_CONV_COEF1_RCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID2_CONV_COEF2_RESERVED_80_SHIFT                                                         (27U)
#define DSS_DISPC_VID2_CONV_COEF2_RESERVED_80_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID2_CONV_COEF2_GCB_SHIFT                                                                 (16U)
#define DSS_DISPC_VID2_CONV_COEF2_GCB_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID2_CONV_COEF2_RESERVED_81_SHIFT                                                         (11U)
#define DSS_DISPC_VID2_CONV_COEF2_RESERVED_81_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID2_CONV_COEF2_GCR_SHIFT                                                                 (0U)
#define DSS_DISPC_VID2_CONV_COEF2_GCR_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID2_CONV_COEF3_RESERVED_82_SHIFT                                                         (27U)
#define DSS_DISPC_VID2_CONV_COEF3_RESERVED_82_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID2_CONV_COEF3_BCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID2_CONV_COEF3_BCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID2_CONV_COEF3_RESERVED_83_SHIFT                                                         (11U)
#define DSS_DISPC_VID2_CONV_COEF3_RESERVED_83_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID2_CONV_COEF3_BY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID2_CONV_COEF3_BY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID2_CONV_COEF4_RESERVED_84_SHIFT                                                         (11U)
#define DSS_DISPC_VID2_CONV_COEF4_RESERVED_84_MASK                                                          (0xfffff800U)

#define DSS_DISPC_VID2_CONV_COEF4_BCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID2_CONV_COEF4_BCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_SHIFT                                                           (16U)
#define DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_MASK                                                            (0x001f0000U)

#define DSS_DISPC_DATA1_CYCLE1_RESERVED_3_SHIFT                                                             (12U)
#define DSS_DISPC_DATA1_CYCLE1_RESERVED_3_MASK                                                              (0x0000f000U)

#define DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_SHIFT                                                     (8U)
#define DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_MASK                                                      (0x00000f00U)

#define DSS_DISPC_DATA1_CYCLE1_RESERVED_4_SHIFT                                                             (5U)
#define DSS_DISPC_DATA1_CYCLE1_RESERVED_4_MASK                                                              (0x000000e0U)

#define DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_SHIFT                                                           (0U)
#define DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_MASK                                                            (0x0000001fU)

#define DSS_DISPC_DATA1_CYCLE1_RESERVED_5_SHIFT                                                             (28U)
#define DSS_DISPC_DATA1_CYCLE1_RESERVED_5_MASK                                                              (0xf0000000U)

#define DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_SHIFT                                                     (24U)
#define DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_MASK                                                      (0x0f000000U)

#define DSS_DISPC_DATA1_CYCLE1_RESERVED_6_SHIFT                                                             (21U)
#define DSS_DISPC_DATA1_CYCLE1_RESERVED_6_MASK                                                              (0x00e00000U)

#define DSS_DISPC_DATA1_CYCLE2_RESERVED_7_SHIFT                                                             (28U)
#define DSS_DISPC_DATA1_CYCLE2_RESERVED_7_MASK                                                              (0xf0000000U)

#define DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_SHIFT                                                     (8U)
#define DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_MASK                                                      (0x00000f00U)

#define DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_SHIFT                                                     (24U)
#define DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_MASK                                                      (0x0f000000U)

#define DSS_DISPC_DATA1_CYCLE2_RESERVED_8_SHIFT                                                             (5U)
#define DSS_DISPC_DATA1_CYCLE2_RESERVED_8_MASK                                                              (0x000000e0U)

#define DSS_DISPC_DATA1_CYCLE2_RESERVED_9_SHIFT                                                             (21U)
#define DSS_DISPC_DATA1_CYCLE2_RESERVED_9_MASK                                                              (0x00e00000U)

#define DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_SHIFT                                                           (0U)
#define DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_MASK                                                            (0x0000001fU)

#define DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_SHIFT                                                           (16U)
#define DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_MASK                                                            (0x001f0000U)

#define DSS_DISPC_DATA1_CYCLE2_RESERVED_10_SHIFT                                                            (12U)
#define DSS_DISPC_DATA1_CYCLE2_RESERVED_10_MASK                                                             (0x0000f000U)

#define DSS_DISPC_DATA1_CYCLE3_RESERVED_11_SHIFT                                                            (21U)
#define DSS_DISPC_DATA1_CYCLE3_RESERVED_11_MASK                                                             (0x00e00000U)

#define DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_SHIFT                                                           (0U)
#define DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_MASK                                                            (0x0000001fU)

#define DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_SHIFT                                                           (16U)
#define DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_MASK                                                            (0x001f0000U)

#define DSS_DISPC_DATA1_CYCLE3_RESERVED_12_SHIFT                                                            (12U)
#define DSS_DISPC_DATA1_CYCLE3_RESERVED_12_MASK                                                             (0x0000f000U)

#define DSS_DISPC_DATA1_CYCLE3_RESERVED_13_SHIFT                                                            (28U)
#define DSS_DISPC_DATA1_CYCLE3_RESERVED_13_MASK                                                             (0xf0000000U)

#define DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_SHIFT                                                     (8U)
#define DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_MASK                                                      (0x00000f00U)

#define DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_SHIFT                                                     (24U)
#define DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_MASK                                                      (0x0f000000U)

#define DSS_DISPC_DATA1_CYCLE3_RESERVED_14_SHIFT                                                            (5U)
#define DSS_DISPC_DATA1_CYCLE3_RESERVED_14_MASK                                                             (0x000000e0U)

#define DSS_DISPC_VID1_FIR_COEF_V_RESERVED_110_SHIFT                                                        (16U)
#define DSS_DISPC_VID1_FIR_COEF_V_RESERVED_110_MASK                                                         (0xffff0000U)

#define DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_SHIFT                                                             (8U)
#define DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_SHIFT                                                             (0U)
#define DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID2_FIR_COEF_V_RESERVED_111_SHIFT                                                        (16U)
#define DSS_DISPC_VID2_FIR_COEF_V_RESERVED_111_MASK                                                         (0xffff0000U)

#define DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_SHIFT                                                             (8U)
#define DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_SHIFT                                                             (0U)
#define DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_MASK                                                              (0x000000ffU)

#define DSS_DISPC_CPR1_COEF_R_RB_SHIFT                                                                      (0U)
#define DSS_DISPC_CPR1_COEF_R_RB_MASK                                                                       (0x000003ffU)

#define DSS_DISPC_CPR1_COEF_R_RESERVED_152_SHIFT                                                            (10U)
#define DSS_DISPC_CPR1_COEF_R_RESERVED_152_MASK                                                             (0x00000400U)

#define DSS_DISPC_CPR1_COEF_R_RESERVED_153_SHIFT                                                            (21U)
#define DSS_DISPC_CPR1_COEF_R_RESERVED_153_MASK                                                             (0x00200000U)

#define DSS_DISPC_CPR1_COEF_R_RR_SHIFT                                                                      (22U)
#define DSS_DISPC_CPR1_COEF_R_RR_MASK                                                                       (0xffc00000U)

#define DSS_DISPC_CPR1_COEF_R_RG_SHIFT                                                                      (11U)
#define DSS_DISPC_CPR1_COEF_R_RG_MASK                                                                       (0x001ff800U)

#define DSS_DISPC_CPR1_COEF_G_GB_SHIFT                                                                      (0U)
#define DSS_DISPC_CPR1_COEF_G_GB_MASK                                                                       (0x000003ffU)

#define DSS_DISPC_CPR1_COEF_G_RESERVED_154_SHIFT                                                            (10U)
#define DSS_DISPC_CPR1_COEF_G_RESERVED_154_MASK                                                             (0x00000400U)

#define DSS_DISPC_CPR1_COEF_G_RESERVED_155_SHIFT                                                            (21U)
#define DSS_DISPC_CPR1_COEF_G_RESERVED_155_MASK                                                             (0x00200000U)

#define DSS_DISPC_CPR1_COEF_G_GR_SHIFT                                                                      (22U)
#define DSS_DISPC_CPR1_COEF_G_GR_MASK                                                                       (0xffc00000U)

#define DSS_DISPC_CPR1_COEF_G_GG_SHIFT                                                                      (11U)
#define DSS_DISPC_CPR1_COEF_G_GG_MASK                                                                       (0x001ff800U)

#define DSS_DISPC_CPR1_COEF_B_BB_SHIFT                                                                      (0U)
#define DSS_DISPC_CPR1_COEF_B_BB_MASK                                                                       (0x000003ffU)

#define DSS_DISPC_CPR1_COEF_B_RESERVED_156_SHIFT                                                            (10U)
#define DSS_DISPC_CPR1_COEF_B_RESERVED_156_MASK                                                             (0x00000400U)

#define DSS_DISPC_CPR1_COEF_B_RESERVED_157_SHIFT                                                            (21U)
#define DSS_DISPC_CPR1_COEF_B_RESERVED_157_MASK                                                             (0x00200000U)

#define DSS_DISPC_CPR1_COEF_B_BR_SHIFT                                                                      (22U)
#define DSS_DISPC_CPR1_COEF_B_BR_MASK                                                                       (0xffc00000U)

#define DSS_DISPC_CPR1_COEF_B_BG_SHIFT                                                                      (11U)
#define DSS_DISPC_CPR1_COEF_B_BG_MASK                                                                       (0x001ff800U)

#define DSS_DISPC_GFX_PRELOAD_RESERVED_211_SHIFT                                                            (12U)
#define DSS_DISPC_GFX_PRELOAD_RESERVED_211_MASK                                                             (0xfffff000U)

#define DSS_DISPC_GFX_PRELOAD_PRELOAD_SHIFT                                                                 (0U)
#define DSS_DISPC_GFX_PRELOAD_PRELOAD_MASK                                                                  (0x00000fffU)

#define DSS_DISPC_VID1_PRELOAD_RESERVED_212_SHIFT                                                           (12U)
#define DSS_DISPC_VID1_PRELOAD_RESERVED_212_MASK                                                            (0xfffff000U)

#define DSS_DISPC_VID1_PRELOAD_PRELOAD_SHIFT                                                                (0U)
#define DSS_DISPC_VID1_PRELOAD_PRELOAD_MASK                                                                 (0x00000fffU)

#define DSS_DISPC_VID2_PRELOAD_RESERVED_211_SHIFT                                                           (12U)
#define DSS_DISPC_VID2_PRELOAD_RESERVED_211_MASK                                                            (0xfffff000U)

#define DSS_DISPC_VID2_PRELOAD_PRELOAD_SHIFT                                                                (0U)
#define DSS_DISPC_VID2_PRELOAD_PRELOAD_MASK                                                                 (0x00000fffU)

#define DSS_DISPC_CONTROL2_STDITHERENABLE_SHIFT                                                             (7U)
#define DSS_DISPC_CONTROL2_STDITHERENABLE_MASK                                                              (0x00000080U)
#define DSS_DISPC_CONTROL2_STDITHERENABLE_STDITHDIS                                                          (0U)
#define DSS_DISPC_CONTROL2_STDITHERENABLE_STDITHENB                                                          (1U)

#define DSS_DISPC_CONTROL2_TFTDATALINES_SHIFT                                                               (8U)
#define DSS_DISPC_CONTROL2_TFTDATALINES_MASK                                                                (0x00000300U)
#define DSS_DISPC_CONTROL2_TFTDATALINES_OALSB12B                                                             (0U)
#define DSS_DISPC_CONTROL2_TFTDATALINES_OALSB16B                                                             (1U)
#define DSS_DISPC_CONTROL2_TFTDATALINES_OALSB18B                                                             (2U)
#define DSS_DISPC_CONTROL2_TFTDATALINES_OALSB24B                                                             (3U)

#define DSS_DISPC_CONTROL2_STALLMODE_SHIFT                                                                  (11U)
#define DSS_DISPC_CONTROL2_STALLMODE_MASK                                                                   (0x00000800U)
#define DSS_DISPC_CONTROL2_STALLMODE_NMODE                                                                   (0U)
#define DSS_DISPC_CONTROL2_STALLMODE_RFBIMODE                                                                (1U)

#define DSS_DISPC_CONTROL2_MONOCOLOR_SHIFT                                                                  (2U)
#define DSS_DISPC_CONTROL2_MONOCOLOR_MASK                                                                   (0x00000004U)
#define DSS_DISPC_CONTROL2_MONOCOLOR_COLOPENB                                                                (0U)
#define DSS_DISPC_CONTROL2_MONOCOLOR_MONOPENB                                                                (1U)

#define DSS_DISPC_CONTROL2_M8B_SHIFT                                                                        (4U)
#define DSS_DISPC_CONTROL2_M8B_MASK                                                                         (0x00000010U)
#define DSS_DISPC_CONTROL2_M8B_4PIXTOPANEL                                                                   (0U)
#define DSS_DISPC_CONTROL2_M8B_8PIXTOPANEL                                                                   (1U)

#define DSS_DISPC_CONTROL2_STNTFT_SHIFT                                                                     (3U)
#define DSS_DISPC_CONTROL2_STNTFT_MASK                                                                      (0x00000008U)
#define DSS_DISPC_CONTROL2_STNTFT_STNDISPENB                                                                 (0U)
#define DSS_DISPC_CONTROL2_STNTFT_ATFTDISENB                                                                 (1U)

#define DSS_DISPC_CONTROL2_GOLCD_SHIFT                                                                      (5U)
#define DSS_DISPC_CONTROL2_GOLCD_MASK                                                                       (0x00000020U)
#define DSS_DISPC_CONTROL2_GOLCD_HFUISR                                                                      (0U)
#define DSS_DISPC_CONTROL2_GOLCD_UFPSR                                                                       (1U)

#define DSS_DISPC_CONTROL2_LCDENABLE_SHIFT                                                                  (0U)
#define DSS_DISPC_CONTROL2_LCDENABLE_MASK                                                                   (0x00000001U)
#define DSS_DISPC_CONTROL2_LCDENABLE_LCDOPDIS                                                                (0U)
#define DSS_DISPC_CONTROL2_LCDENABLE_LCDOPENB                                                                (1U)

#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_SHIFT                                             (30U)
#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_MASK                                              (0xc0000000U)
#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_ONEFRAME                                           (0U)
#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_TWOFRAMES                                          (1U)
#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_FOURFRAMES                                         (2U)
#define DSS_DISPC_CONTROL2_SPATIALTEMPORALDITHERINGFRAMES_RESERVED                                           (3U)

#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_SHIFT                                                              (25U)
#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_MASK                                                               (0x06000000U)
#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_LOWLEVEL                                                            (0U)
#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_HIGHLEVEL                                                           (1U)
#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_UNCHANGED                                                           (2U)
#define DSS_DISPC_CONTROL2_TDMUNUSEDBITS_RES                                                                 (3U)

#define DSS_DISPC_CONTROL2_TDMENABLE_SHIFT                                                                  (20U)
#define DSS_DISPC_CONTROL2_TDMENABLE_MASK                                                                   (0x00100000U)
#define DSS_DISPC_CONTROL2_TDMENABLE_TDMDIS                                                                  (0U)
#define DSS_DISPC_CONTROL2_TDMENABLE_TDMENB                                                                  (1U)

#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_SHIFT                                                            (21U)
#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_MASK                                                             (0x00600000U)
#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_8BPARAINT                                                         (0U)
#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_9BPARAINT                                                         (1U)
#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_12BPARAINT                                                        (2U)
#define DSS_DISPC_CONTROL2_TDMPARALLELMODE_16BPARAINT                                                        (3U)

#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_SHIFT                                                             (23U)
#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_MASK                                                              (0x01800000U)
#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_1CYCPERPIX                                                         (0U)
#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_2CYCPERPIX                                                         (1U)
#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_3CYCPERPIX                                                         (2U)
#define DSS_DISPC_CONTROL2_TDMCYCLEFORMAT_3CYCPER2PIX                                                        (3U)

#define DSS_DISPC_CONTROL2_OVERLAYOPTIMIZATION_SHIFT                                                        (12U)
#define DSS_DISPC_CONTROL2_OVERLAYOPTIMIZATION_MASK                                                         (0x00001000U)
#define DSS_DISPC_CONTROL2_OVERLAYOPTIMIZATION_GDBVWFM                                                       (0U)
#define DSS_DISPC_CONTROL2_OVERLAYOPTIMIZATION_GDBVWNFM                                                      (1U)

#define DSS_DISPC_CONTROL2_RESERVED_3_SHIFT                                                                 (10U)
#define DSS_DISPC_CONTROL2_RESERVED_3_MASK                                                                  (0x00000400U)

#define DSS_DISPC_CONTROL2_GOWB_SHIFT                                                                       (6U)
#define DSS_DISPC_CONTROL2_GOWB_MASK                                                                        (0x00000040U)
#define DSS_DISPC_CONTROL2_GOWB_HFUISR                                                                       (0U)
#define DSS_DISPC_CONTROL2_GOWB_UFPSR                                                                        (1U)

#define DSS_DISPC_CONTROL2_RESERVED_4_SHIFT                                                                 (1U)
#define DSS_DISPC_CONTROL2_RESERVED_4_MASK                                                                  (0x00000002U)

#define DSS_DISPC_CONTROL2_RESERVED_SHIFT                                                                   (27U)
#define DSS_DISPC_CONTROL2_RESERVED_MASK                                                                    (0x38000000U)

#define DSS_DISPC_CONTROL2_TVOVERLAYOPTIMIZATION_SHIFT                                                      (13U)
#define DSS_DISPC_CONTROL2_TVOVERLAYOPTIMIZATION_MASK                                                       (0x00002000U)
#define DSS_DISPC_CONTROL2_TVOVERLAYOPTIMIZATION_GDBVWFM                                                     (0U)
#define DSS_DISPC_CONTROL2_TVOVERLAYOPTIMIZATION_GDBVWNFM                                                    (1U)

#define DSS_DISPC_CONTROL2_RESERVED1_SHIFT                                                                  (14U)
#define DSS_DISPC_CONTROL2_RESERVED1_MASK                                                                   (0x000fc000U)

#define DSS_DISPC_GFX_POSITION2_POSX_SHIFT                                                                  (0U)
#define DSS_DISPC_GFX_POSITION2_POSX_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_GFX_POSITION2_RESERVED_23_SHIFT                                                           (27U)
#define DSS_DISPC_GFX_POSITION2_RESERVED_23_MASK                                                            (0xf8000000U)

#define DSS_DISPC_GFX_POSITION2_POSY_SHIFT                                                                  (16U)
#define DSS_DISPC_GFX_POSITION2_POSY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_GFX_POSITION2_RESERVED_24_SHIFT                                                           (11U)
#define DSS_DISPC_GFX_POSITION2_RESERVED_24_MASK                                                            (0x0000f800U)

#define DSS_DISPC_VID1_POSITION2_RESERVED_69_SHIFT                                                          (27U)
#define DSS_DISPC_VID1_POSITION2_RESERVED_69_MASK                                                           (0xf8000000U)

#define DSS_DISPC_VID1_POSITION2_POSY_SHIFT                                                                 (16U)
#define DSS_DISPC_VID1_POSITION2_POSY_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID1_POSITION2_RESERVED_70_SHIFT                                                          (11U)
#define DSS_DISPC_VID1_POSITION2_RESERVED_70_MASK                                                           (0x0000f800U)

#define DSS_DISPC_VID1_POSITION2_POSX_SHIFT                                                                 (0U)
#define DSS_DISPC_VID1_POSITION2_POSX_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID2_POSITION2_RESERVED_93_SHIFT                                                          (27U)
#define DSS_DISPC_VID2_POSITION2_RESERVED_93_MASK                                                           (0xf8000000U)

#define DSS_DISPC_VID2_POSITION2_POSY_SHIFT                                                                 (16U)
#define DSS_DISPC_VID2_POSITION2_POSY_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID2_POSITION2_RESERVED_94_SHIFT                                                          (11U)
#define DSS_DISPC_VID2_POSITION2_RESERVED_94_MASK                                                           (0x0000f800U)

#define DSS_DISPC_VID2_POSITION2_POSX_SHIFT                                                                 (0U)
#define DSS_DISPC_VID2_POSITION2_POSX_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID3_POSITION2_POSY_SHIFT                                                                 (16U)
#define DSS_DISPC_VID3_POSITION2_POSY_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID3_POSITION2_RESERVED_94_SHIFT                                                          (11U)
#define DSS_DISPC_VID3_POSITION2_RESERVED_94_MASK                                                           (0x0000f800U)

#define DSS_DISPC_VID3_POSITION2_POSX_SHIFT                                                                 (0U)
#define DSS_DISPC_VID3_POSITION2_POSX_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID3_POSITION2_RESERVED_93_SHIFT                                                          (27U)
#define DSS_DISPC_VID3_POSITION2_RESERVED_93_MASK                                                           (0xf8000000U)

#define DSS_DISPC_VID3_ACCU_HORIZONTALACCU_SHIFT                                                            (0U)
#define DSS_DISPC_VID3_ACCU_HORIZONTALACCU_MASK                                                             (0x000007ffU)

#define DSS_DISPC_VID3_ACCU_VERTICALACCU_SHIFT                                                              (16U)
#define DSS_DISPC_VID3_ACCU_VERTICALACCU_MASK                                                               (0x07ff0000U)

#define DSS_DISPC_VID3_ACCU_RESERVED_SHIFT                                                                  (11U)
#define DSS_DISPC_VID3_ACCU_RESERVED_MASK                                                                   (0x0000f800U)

#define DSS_DISPC_VID3_ACCU_RESERVED1_SHIFT                                                                 (27U)
#define DSS_DISPC_VID3_ACCU_RESERVED1_MASK                                                                  (0xf8000000U)

#define DSS_DISPC_VID3_BA_BA_SHIFT                                                                          (0U)
#define DSS_DISPC_VID3_BA_BA_MASK                                                                           (0xffffffffU)

#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_SHIFT                                                              (16U)
#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_MASK                                                               (0x00ff0000U)

#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_SHIFT                                                              (8U)
#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_MASK                                                               (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_SHIFT                                                              (0U)
#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_MASK                                                               (0x000000ffU)

#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_SHIFT                                                              (24U)
#define DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_MASK                                                               (0xff000000U)

#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_SHIFT                                                             (8U)
#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_SHIFT                                                             (0U)
#define DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_SHIFT                                                             (24U)
#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_SHIFT                                                             (16U)
#define DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_SHIFT                                                             (8U)
#define DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_V_RESERVED_111_SHIFT                                                        (16U)
#define DSS_DISPC_VID3_FIR_COEF_V_RESERVED_111_MASK                                                         (0xffff0000U)

#define DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_SHIFT                                                             (0U)
#define DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID3_ATTRIBUTES_ENABLE_SHIFT                                                              (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_ENABLE_MASK                                                               (0x00000001U)
#define DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEODIS                                                            (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEOENB                                                            (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_SHIFT                                                           (14U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_MASK                                                            (0x0000c000U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_BURST2X128B                                                      (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_BURST4X128B                                                      (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_BURST8X128B                                                      (2U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTSIZE_RES                                                              (3U)

#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESH_SHIFT                                                         (24U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESH_MASK                                                          (0x01000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESH_SELFREFRESHDIS                                                 (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESH_SELFREFRESHENB                                                 (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_COLORCONVENABLE_SHIFT                                                     (9U)
#define DSS_DISPC_VID3_ATTRIBUTES_COLORCONVENABLE_MASK                                                      (0x00000200U)
#define DSS_DISPC_VID3_ATTRIBUTES_COLORCONVENABLE_COLSPCDIS                                                  (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_COLORCONVENABLE_COLSPCENB                                                  (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_REPLICATIONENABLE_SHIFT                                                   (10U)
#define DSS_DISPC_VID3_ATTRIBUTES_REPLICATIONENABLE_MASK                                                    (0x00000400U)
#define DSS_DISPC_VID3_ATTRIBUTES_REPLICATIONENABLE_VREPLENB                                                 (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_REPLICATIONENABLE_VREPLDIS                                                 (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_VERTICALTAPS_SHIFT                                                        (21U)
#define DSS_DISPC_VID3_ATTRIBUTES_VERTICALTAPS_MASK                                                         (0x00200000U)
#define DSS_DISPC_VID3_ATTRIBUTES_VERTICALTAPS_TAPS5                                                         (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_VERTICALTAPS_TAPS3                                                         (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_SHIFT                                                              (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_MASK                                                               (0x0000001eU)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_YUV2                                                                (10U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_UYVY                                                                (11U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_NV12                                                                (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_XRGB12                                                              (4U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGB16                                                               (6U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_XRGB24                                                              (8U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGB24                                                               (9U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_ARGB16                                                              (5U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_ARGB32                                                              (12U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGBA32                                                              (13U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGBX24                                                              (14U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_ARGB16_1                                                            (7U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_XRGB15                                                              (15U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGBX12                                                              (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_RGBA12                                                              (2U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORMAT_BGRA32                                                              (3U)

#define DSS_DISPC_VID3_ATTRIBUTES_ARBITRATION_SHIFT                                                         (23U)
#define DSS_DISPC_VID3_ATTRIBUTES_ARBITRATION_MASK                                                          (0x00800000U)
#define DSS_DISPC_VID3_ATTRIBUTES_ARBITRATION_HIGHPRIO                                                       (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_ARBITRATION_NORMALPRIO                                                     (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_FULLRANGE_SHIFT                                                           (11U)
#define DSS_DISPC_VID3_ATTRIBUTES_FULLRANGE_MASK                                                            (0x00000800U)
#define DSS_DISPC_VID3_ATTRIBUTES_FULLRANGE_FULLRANGE                                                        (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_FULLRANGE_LIMRANGE                                                         (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_SHIFT                                                        (5U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_MASK                                                         (0x00000020U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_HVRESIZE                                                      (3U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_VRESIZE                                                       (2U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_HRESIZE                                                       (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESIZEENABLE_RESIZEPROC                                                    (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_HRESIZECONF_SHIFT                                                         (7U)
#define DSS_DISPC_VID3_ATTRIBUTES_HRESIZECONF_MASK                                                          (0x00000080U)

#define DSS_DISPC_VID3_ATTRIBUTES_BUFPRELOAD_SHIFT                                                          (19U)
#define DSS_DISPC_VID3_ATTRIBUTES_BUFPRELOAD_MASK                                                           (0x00080000U)
#define DSS_DISPC_VID3_ATTRIBUTES_BUFPRELOAD_DEFVAL                                                          (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_BUFPRELOAD_HIGHTHRES                                                       (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_SHIFT                                                            (12U)
#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_MASK                                                             (0x00003000U)
#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_ROT270                                                            (3U)
#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_ROT180                                                            (2U)
#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_ROT90                                                             (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_ROTATION_NOROT                                                             (0U)

#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_SHIFT                                                            (5U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_MASK                                                             (0x00000020U)

#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_1_SHIFT                                                          (7U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_1_MASK                                                           (0x00000080U)

#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_2_SHIFT                                                          (8U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_2_MASK                                                           (0x00000100U)

#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_100_SHIFT                                                        (18U)
#define DSS_DISPC_VID3_ATTRIBUTES_RESERVED_100_MASK                                                         (0x00040000U)

#define DSS_DISPC_VID3_ATTRIBUTES_ZORDERENABLE_SHIFT                                                        (25U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDERENABLE_MASK                                                         (0x02000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDERENABLE_ZORDERDIS                                                     (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDERENABLE_ZORDERENB                                                     (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_SHIFT                                                              (26U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_MASK                                                               (0x0c000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_ZORDER0                                                             (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_ZORDER1                                                             (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_ZORDER2                                                             (2U)
#define DSS_DISPC_VID3_ATTRIBUTES_ZORDER_ZORDER3                                                             (3U)

#define DSS_DISPC_VID3_ATTRIBUTES_PREMULTIPLYALPHA_SHIFT                                                    (28U)
#define DSS_DISPC_VID3_ATTRIBUTES_PREMULTIPLYALPHA_MASK                                                     (0x10000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA                                     (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA                                        (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_BURSTTYPE_SHIFT                                                           (29U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTTYPE_MASK                                                            (0x20000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTTYPE_INC                                                              (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_BURSTTYPE_BLCK                                                             (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_SHIFT                                                         (30U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_MASK                                                          (0xc0000000U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_PRIMARYLCDSEL                                                  (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_SECONDARYLCDSEL                                                (1U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_WRITEBACKSEL                                                   (3U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT2_THIRDLCDSEL                                                    (2U)

#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT_SHIFT                                                          (16U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT_MASK                                                           (0x00010000U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT_LCDOP                                                           (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_CHANNELOUT_TVOP                                                            (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESHAUTO_SHIFT                                                     (17U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESHAUTO_MASK                                                      (0x00020000U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTODIS                                         (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTOEN                                          (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_DOUBLESTRIDE_SHIFT                                                        (22U)
#define DSS_DISPC_VID3_ATTRIBUTES_DOUBLESTRIDE_MASK                                                         (0x00400000U)
#define DSS_DISPC_VID3_ATTRIBUTES_DOUBLESTRIDE_INITIAL                                                       (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_DOUBLESTRIDE_DOUBLE                                                        (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                                    (20U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                                     (0x00100000U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                                      (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                                      (1U)

#define DSS_DISPC_VID3_ATTRIBUTES_FRAMEPACKINGMODE_SHIFT                                                    (8U)
#define DSS_DISPC_VID3_ATTRIBUTES_FRAMEPACKINGMODE_MASK                                                     (0x00000100U)
#define DSS_DISPC_VID3_ATTRIBUTES_FRAMEPACKINGMODE_FPMDIS                                                    (0U)
#define DSS_DISPC_VID3_ATTRIBUTES_FRAMEPACKINGMODE_FPMENB                                                    (1U)

#define DSS_DISPC_VID3_CONV_COEF0_RESERVED_77_SHIFT                                                         (11U)
#define DSS_DISPC_VID3_CONV_COEF0_RESERVED_77_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID3_CONV_COEF0_RY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID3_CONV_COEF0_RY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID3_CONV_COEF0_RCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID3_CONV_COEF0_RCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID3_CONV_COEF0_RESERVED_76_SHIFT                                                         (27U)
#define DSS_DISPC_VID3_CONV_COEF0_RESERVED_76_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID3_CONV_COEF1_RESERVED_79_SHIFT                                                         (11U)
#define DSS_DISPC_VID3_CONV_COEF1_RESERVED_79_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID3_CONV_COEF1_RCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID3_CONV_COEF1_RCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID3_CONV_COEF1_RESERVED_78_SHIFT                                                         (27U)
#define DSS_DISPC_VID3_CONV_COEF1_RESERVED_78_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID3_CONV_COEF1_GY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID3_CONV_COEF1_GY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID3_CONV_COEF2_RESERVED_81_SHIFT                                                         (11U)
#define DSS_DISPC_VID3_CONV_COEF2_RESERVED_81_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID3_CONV_COEF2_RESERVED_80_SHIFT                                                         (27U)
#define DSS_DISPC_VID3_CONV_COEF2_RESERVED_80_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID3_CONV_COEF2_GCR_SHIFT                                                                 (0U)
#define DSS_DISPC_VID3_CONV_COEF2_GCR_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID3_CONV_COEF2_GCB_SHIFT                                                                 (16U)
#define DSS_DISPC_VID3_CONV_COEF2_GCB_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID3_CONV_COEF3_BY_SHIFT                                                                  (0U)
#define DSS_DISPC_VID3_CONV_COEF3_BY_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID3_CONV_COEF3_RESERVED_82_SHIFT                                                         (27U)
#define DSS_DISPC_VID3_CONV_COEF3_RESERVED_82_MASK                                                          (0xf8000000U)

#define DSS_DISPC_VID3_CONV_COEF3_RESERVED_83_SHIFT                                                         (11U)
#define DSS_DISPC_VID3_CONV_COEF3_RESERVED_83_MASK                                                          (0x0000f800U)

#define DSS_DISPC_VID3_CONV_COEF3_BCR_SHIFT                                                                 (16U)
#define DSS_DISPC_VID3_CONV_COEF3_BCR_MASK                                                                  (0x07ff0000U)

#define DSS_DISPC_VID3_CONV_COEF4_BCB_SHIFT                                                                 (0U)
#define DSS_DISPC_VID3_CONV_COEF4_BCB_MASK                                                                  (0x000007ffU)

#define DSS_DISPC_VID3_CONV_COEF4_RESERVED_84_SHIFT                                                         (11U)
#define DSS_DISPC_VID3_CONV_COEF4_RESERVED_84_MASK                                                          (0xfffff800U)

#define DSS_DISPC_VID3_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                                        (0U)
#define DSS_DISPC_VID3_BUF_SIZE_STATUS_BUFSIZE_MASK                                                         (0x0000ffffU)

#define DSS_DISPC_VID3_BUF_SIZE_STATUS_RESERVED_85_SHIFT                                                    (16U)
#define DSS_DISPC_VID3_BUF_SIZE_STATUS_RESERVED_85_MASK                                                     (0xffff0000U)

#define DSS_DISPC_VID3_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                                 (16U)
#define DSS_DISPC_VID3_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                                  (0xffff0000U)

#define DSS_DISPC_VID3_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                                  (0U)
#define DSS_DISPC_VID3_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                                   (0x0000ffffU)

#define DSS_DISPC_VID3_FIR_RESERVED_88_SHIFT                                                                (29U)
#define DSS_DISPC_VID3_FIR_RESERVED_88_MASK                                                                 (0xe0000000U)

#define DSS_DISPC_VID3_FIR_FIRVINC_SHIFT                                                                    (16U)
#define DSS_DISPC_VID3_FIR_FIRVINC_MASK                                                                     (0x1fff0000U)

#define DSS_DISPC_VID3_FIR_RESERVED_89_SHIFT                                                                (13U)
#define DSS_DISPC_VID3_FIR_RESERVED_89_MASK                                                                 (0x0000e000U)

#define DSS_DISPC_VID3_FIR_FIRHINC_SHIFT                                                                    (0U)
#define DSS_DISPC_VID3_FIR_FIRHINC_MASK                                                                     (0x00001fffU)

#define DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_SHIFT                                                          (16U)
#define DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_MASK                                                           (0x0fff0000U)

#define DSS_DISPC_VID3_PICTURE_SIZE_RESERVED_91_SHIFT                                                       (11U)
#define DSS_DISPC_VID3_PICTURE_SIZE_RESERVED_91_MASK                                                        (0x0000f800U)

#define DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_SHIFT                                                          (0U)
#define DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_MASK                                                           (0x000007ffU)

#define DSS_DISPC_VID3_PICTURE_SIZE_RESERVED_SHIFT                                                          (28U)
#define DSS_DISPC_VID3_PICTURE_SIZE_RESERVED_MASK                                                           (0xf0000000U)

#define DSS_DISPC_VID3_PIXEL_INC_RESERVED_92_SHIFT                                                          (8U)
#define DSS_DISPC_VID3_PIXEL_INC_RESERVED_92_MASK                                                           (0xffffff00U)

#define DSS_DISPC_VID3_PIXEL_INC_PIXELINC_SHIFT                                                             (0U)
#define DSS_DISPC_VID3_PIXEL_INC_PIXELINC_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID3_POSITION_POSY_SHIFT                                                                  (16U)
#define DSS_DISPC_VID3_POSITION_POSY_MASK                                                                   (0x07ff0000U)

#define DSS_DISPC_VID3_POSITION_RESERVED_94_SHIFT                                                           (11U)
#define DSS_DISPC_VID3_POSITION_RESERVED_94_MASK                                                            (0x0000f800U)

#define DSS_DISPC_VID3_POSITION_POSX_SHIFT                                                                  (0U)
#define DSS_DISPC_VID3_POSITION_POSX_MASK                                                                   (0x000007ffU)

#define DSS_DISPC_VID3_POSITION_RESERVED_93_SHIFT                                                           (27U)
#define DSS_DISPC_VID3_POSITION_RESERVED_93_MASK                                                            (0xf8000000U)

#define DSS_DISPC_VID3_PRELOAD_PRELOAD_SHIFT                                                                (0U)
#define DSS_DISPC_VID3_PRELOAD_PRELOAD_MASK                                                                 (0x00000fffU)

#define DSS_DISPC_VID3_PRELOAD_RESERVED_211_SHIFT                                                           (12U)
#define DSS_DISPC_VID3_PRELOAD_RESERVED_211_MASK                                                            (0xfffff000U)

#define DSS_DISPC_VID3_ROW_INC_ROWINC_SHIFT                                                                 (0U)
#define DSS_DISPC_VID3_ROW_INC_ROWINC_MASK                                                                  (0xffffffffU)

#define DSS_DISPC_VID3_SIZE_SIZEY_SHIFT                                                                     (16U)
#define DSS_DISPC_VID3_SIZE_SIZEY_MASK                                                                      (0x0fff0000U)

#define DSS_DISPC_VID3_SIZE_SIZEX_SHIFT                                                                     (0U)
#define DSS_DISPC_VID3_SIZE_SIZEX_MASK                                                                      (0x00000fffU)

#define DSS_DISPC_VID3_SIZE_RESERVED_SHIFT                                                                  (12U)
#define DSS_DISPC_VID3_SIZE_RESERVED_MASK                                                                   (0x0000f000U)

#define DSS_DISPC_VID3_SIZE_RESERVED1_SHIFT                                                                 (28U)
#define DSS_DISPC_VID3_SIZE_RESERVED1_MASK                                                                  (0xf0000000U)

#define DSS_DISPC_CONTROL3_GOLCD_SHIFT                                                                      (5U)
#define DSS_DISPC_CONTROL3_GOLCD_MASK                                                                       (0x00000020U)
#define DSS_DISPC_CONTROL3_GOLCD_HFUISR                                                                      (0U)
#define DSS_DISPC_CONTROL3_GOLCD_UFPSR                                                                       (1U)

#define DSS_DISPC_CONTROL3_TFTDATALINES_SHIFT                                                               (8U)
#define DSS_DISPC_CONTROL3_TFTDATALINES_MASK                                                                (0x00000300U)
#define DSS_DISPC_CONTROL3_TFTDATALINES_OALSB12B                                                             (0U)
#define DSS_DISPC_CONTROL3_TFTDATALINES_OALSB16B                                                             (1U)
#define DSS_DISPC_CONTROL3_TFTDATALINES_OALSB18B                                                             (2U)
#define DSS_DISPC_CONTROL3_TFTDATALINES_OALSB24B                                                             (3U)

#define DSS_DISPC_WB_ACCU_HORIZONTALACCU_SHIFT                                                              (0U)
#define DSS_DISPC_WB_ACCU_HORIZONTALACCU_MASK                                                               (0x000007ffU)

#define DSS_DISPC_WB_ACCU_VERTICALACCU_SHIFT                                                                (16U)
#define DSS_DISPC_WB_ACCU_VERTICALACCU_MASK                                                                 (0x07ff0000U)

#define DSS_DISPC_WB_ACCU_RESERVED_SHIFT                                                                    (11U)
#define DSS_DISPC_WB_ACCU_RESERVED_MASK                                                                     (0x0000f800U)

#define DSS_DISPC_WB_ACCU_RESERVED1_SHIFT                                                                   (27U)
#define DSS_DISPC_WB_ACCU_RESERVED1_MASK                                                                    (0xf8000000U)

#define DSS_DISPC_WB_BA_BA_SHIFT                                                                            (0U)
#define DSS_DISPC_WB_BA_BA_MASK                                                                             (0xffffffffU)

#define DSS_DISPC_WB_FIR_COEF_H_FIRHC2_SHIFT                                                                (16U)
#define DSS_DISPC_WB_FIR_COEF_H_FIRHC2_MASK                                                                 (0x00ff0000U)

#define DSS_DISPC_WB_FIR_COEF_H_FIRHC1_SHIFT                                                                (8U)
#define DSS_DISPC_WB_FIR_COEF_H_FIRHC1_MASK                                                                 (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_H_FIRHC0_SHIFT                                                                (0U)
#define DSS_DISPC_WB_FIR_COEF_H_FIRHC0_MASK                                                                 (0x000000ffU)

#define DSS_DISPC_WB_FIR_COEF_H_FIRHC3_SHIFT                                                                (24U)
#define DSS_DISPC_WB_FIR_COEF_H_FIRHC3_MASK                                                                 (0xff000000U)

#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_SHIFT                                                               (8U)
#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_MASK                                                                (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_SHIFT                                                               (0U)
#define DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_MASK                                                                (0x000000ffU)

#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_SHIFT                                                               (24U)
#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_MASK                                                                (0xff000000U)

#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_SHIFT                                                               (16U)
#define DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_MASK                                                                (0x00ff0000U)

#define DSS_DISPC_WB_FIR_COEF_V_FIRVC22_SHIFT                                                               (8U)
#define DSS_DISPC_WB_FIR_COEF_V_FIRVC22_MASK                                                                (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_V_RESERVED_111_SHIFT                                                          (16U)
#define DSS_DISPC_WB_FIR_COEF_V_RESERVED_111_MASK                                                           (0xffff0000U)

#define DSS_DISPC_WB_FIR_COEF_V_FIRVC00_SHIFT                                                               (0U)
#define DSS_DISPC_WB_FIR_COEF_V_FIRVC00_MASK                                                                (0x000000ffU)

#define DSS_DISPC_WB_ATTRIBUTES_ENABLE_SHIFT                                                                (0U)
#define DSS_DISPC_WB_ATTRIBUTES_ENABLE_MASK                                                                 (0x00000001U)
#define DSS_DISPC_WB_ATTRIBUTES_ENABLE_WBDIS                                                                 (0U)
#define DSS_DISPC_WB_ATTRIBUTES_ENABLE_WBENB                                                                 (1U)

#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_SHIFT                                                             (14U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_MASK                                                              (0x0000c000U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_BURST2X128B                                                        (0U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_BURST4X128B                                                        (1U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_BURST8X128B                                                        (2U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE_RES                                                                (3U)

#define DSS_DISPC_WB_ATTRIBUTES_COLORCONVENABLE_SHIFT                                                       (9U)
#define DSS_DISPC_WB_ATTRIBUTES_COLORCONVENABLE_MASK                                                        (0x00000200U)
#define DSS_DISPC_WB_ATTRIBUTES_COLORCONVENABLE_COLSPCDIS                                                    (0U)
#define DSS_DISPC_WB_ATTRIBUTES_COLORCONVENABLE_COLSPCENB                                                    (1U)

#define DSS_DISPC_WB_ATTRIBUTES_TRUNCATIONENABLE_SHIFT                                                      (10U)
#define DSS_DISPC_WB_ATTRIBUTES_TRUNCATIONENABLE_MASK                                                       (0x00000400U)
#define DSS_DISPC_WB_ATTRIBUTES_TRUNCATIONENABLE_WBTRUNCENB                                                  (1U)
#define DSS_DISPC_WB_ATTRIBUTES_TRUNCATIONENABLE_WBTRUNCDIS                                                  (0U)

#define DSS_DISPC_WB_ATTRIBUTES_VERTICALTAPS_SHIFT                                                          (21U)
#define DSS_DISPC_WB_ATTRIBUTES_VERTICALTAPS_MASK                                                           (0x00200000U)
#define DSS_DISPC_WB_ATTRIBUTES_VERTICALTAPS_TAPS5                                                           (1U)
#define DSS_DISPC_WB_ATTRIBUTES_VERTICALTAPS_TAPS3                                                           (0U)

#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_SHIFT                                                                (1U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_MASK                                                                 (0x0000001eU)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_YUV2                                                                  (10U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_UYVY                                                                  (11U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_NV12                                                                  (0U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_XRGB12                                                                (4U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGB16                                                                 (6U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_XRGB24                                                                (8U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGB24                                                                 (9U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_ARGB16                                                                (5U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_ARGB32                                                                (12U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGBA32                                                                (13U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGBX24                                                                (14U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_ARGB16_1                                                              (7U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_XRGB15                                                                (15U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGBX12                                                                (1U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_RGBA12                                                                (2U)
#define DSS_DISPC_WB_ATTRIBUTES_FORMAT_BGRA32                                                                (3U)

#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_SHIFT                                                             (16U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_MASK                                                              (0x00070000U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD2                                                               (1U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD1                                                               (0U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_TV                                                                 (2U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_GFX                                                                (3U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID1                                                               (4U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID2                                                               (5U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID3                                                               (6U)
#define DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD3                                                               (7U)

#define DSS_DISPC_WB_ATTRIBUTES_ARBITRATION_SHIFT                                                           (23U)
#define DSS_DISPC_WB_ATTRIBUTES_ARBITRATION_MASK                                                            (0x00800000U)
#define DSS_DISPC_WB_ATTRIBUTES_ARBITRATION_HIGHPRIO                                                         (1U)
#define DSS_DISPC_WB_ATTRIBUTES_ARBITRATION_NORMALPRIO                                                       (0U)

#define DSS_DISPC_WB_ATTRIBUTES_BURSTTYPE_SHIFT                                                             (8U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTTYPE_MASK                                                              (0x00000100U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTTYPE_1D_BURST                                                           (0U)
#define DSS_DISPC_WB_ATTRIBUTES_BURSTTYPE_2D_BURST                                                           (1U)

#define DSS_DISPC_WB_ATTRIBUTES_FULLRANGE_SHIFT                                                             (11U)
#define DSS_DISPC_WB_ATTRIBUTES_FULLRANGE_MASK                                                              (0x00000800U)
#define DSS_DISPC_WB_ATTRIBUTES_FULLRANGE_FULLRANGE                                                          (1U)
#define DSS_DISPC_WB_ATTRIBUTES_FULLRANGE_LIMRANGE                                                           (0U)

#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_SHIFT                                                          (5U)
#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_MASK                                                           (0x00000020U)
#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_HVRESIZE                                                        (3U)
#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_VRESIZE                                                         (2U)
#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_HRESIZE                                                         (1U)
#define DSS_DISPC_WB_ATTRIBUTES_RESIZEENABLE_RESIZEPROC                                                      (0U)

#define DSS_DISPC_WB_ATTRIBUTES_HRESIZECONF_SHIFT                                                           (7U)
#define DSS_DISPC_WB_ATTRIBUTES_HRESIZECONF_MASK                                                            (0x00000080U)

#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_SHIFT                                                              (12U)
#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_MASK                                                               (0x00003000U)
#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_ROT270                                                              (3U)
#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_ROT180                                                              (2U)
#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_ROT90                                                               (1U)
#define DSS_DISPC_WB_ATTRIBUTES_ROTATION_NOROT                                                               (0U)

#define DSS_DISPC_WB_ATTRIBUTES_RESERVED_SHIFT                                                              (5U)
#define DSS_DISPC_WB_ATTRIBUTES_RESERVED_MASK                                                               (0x00000020U)

#define DSS_DISPC_WB_ATTRIBUTES_ALPHAENABLE_SHIFT                                                           (7U)
#define DSS_DISPC_WB_ATTRIBUTES_ALPHAENABLE_MASK                                                            (0x00000080U)
#define DSS_DISPC_WB_ATTRIBUTES_ALPHAENABLE_DISABLE                                                          (0U)
#define DSS_DISPC_WB_ATTRIBUTES_ALPHAENABLE_ENABLE                                                           (1U)

#define DSS_DISPC_WB_ATTRIBUTES_RESERVED_2_SHIFT                                                            (8U)
#define DSS_DISPC_WB_ATTRIBUTES_RESERVED_2_MASK                                                             (0x00000100U)

#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_SHIFT                                                           (24U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_MASK                                                            (0x07000000U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ALL                                                              (0U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1                                                            (1U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_2                                                          (2U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_3                                                          (3U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_4                                                          (4U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_5                                                          (5U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_6                                                          (6U)
#define DSS_DISPC_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_7                                                          (7U)

#define DSS_DISPC_WB_ATTRIBUTES_IDLESIZE_SHIFT                                                              (27U)
#define DSS_DISPC_WB_ATTRIBUTES_IDLESIZE_MASK                                                               (0x08000000U)
#define DSS_DISPC_WB_ATTRIBUTES_IDLESIZE_IDLEBURST                                                           (1U)
#define DSS_DISPC_WB_ATTRIBUTES_IDLESIZE_IDLESINGLE                                                          (0U)

#define DSS_DISPC_WB_ATTRIBUTES_IDLENUMBER_SHIFT                                                            (28U)
#define DSS_DISPC_WB_ATTRIBUTES_IDLENUMBER_MASK                                                             (0xf0000000U)

#define DSS_DISPC_WB_ATTRIBUTES_DOUBLESTRIDE_SHIFT                                                          (22U)
#define DSS_DISPC_WB_ATTRIBUTES_DOUBLESTRIDE_MASK                                                           (0x00400000U)
#define DSS_DISPC_WB_ATTRIBUTES_DOUBLESTRIDE_INITIAL                                                         (0U)
#define DSS_DISPC_WB_ATTRIBUTES_DOUBLESTRIDE_DOUBLE                                                          (1U)

#define DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_SHIFT                                                         (19U)
#define DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_MASK                                                          (0x00080000U)
#define DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_CAPTURE                                                        (0U)
#define DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_MEM2MEM                                                        (1U)

#define DSS_DISPC_WB_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                                      (20U)
#define DSS_DISPC_WB_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                                       (0x00100000U)
#define DSS_DISPC_WB_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                                        (0U)
#define DSS_DISPC_WB_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                                        (1U)

#define DSS_DISPC_WB_CONV_COEF0_RESERVED_77_SHIFT                                                           (11U)
#define DSS_DISPC_WB_CONV_COEF0_RESERVED_77_MASK                                                            (0x0000f800U)

#define DSS_DISPC_WB_CONV_COEF0_YR_SHIFT                                                                    (0U)
#define DSS_DISPC_WB_CONV_COEF0_YR_MASK                                                                     (0x000007ffU)

#define DSS_DISPC_WB_CONV_COEF0_YG_SHIFT                                                                    (16U)
#define DSS_DISPC_WB_CONV_COEF0_YG_MASK                                                                     (0x07ff0000U)

#define DSS_DISPC_WB_CONV_COEF0_RESERVED_76_SHIFT                                                           (27U)
#define DSS_DISPC_WB_CONV_COEF0_RESERVED_76_MASK                                                            (0xf8000000U)

#define DSS_DISPC_WB_CONV_COEF1_RESERVED_79_SHIFT                                                           (11U)
#define DSS_DISPC_WB_CONV_COEF1_RESERVED_79_MASK                                                            (0x0000f800U)

#define DSS_DISPC_WB_CONV_COEF1_YB_SHIFT                                                                    (0U)
#define DSS_DISPC_WB_CONV_COEF1_YB_MASK                                                                     (0x000007ffU)

#define DSS_DISPC_WB_CONV_COEF1_RESERVED_78_SHIFT                                                           (27U)
#define DSS_DISPC_WB_CONV_COEF1_RESERVED_78_MASK                                                            (0xf8000000U)

#define DSS_DISPC_WB_CONV_COEF1_CRR_SHIFT                                                                   (16U)
#define DSS_DISPC_WB_CONV_COEF1_CRR_MASK                                                                    (0x07ff0000U)

#define DSS_DISPC_WB_CONV_COEF2_RESERVED_81_SHIFT                                                           (11U)
#define DSS_DISPC_WB_CONV_COEF2_RESERVED_81_MASK                                                            (0x0000f800U)

#define DSS_DISPC_WB_CONV_COEF2_RESERVED_80_SHIFT                                                           (27U)
#define DSS_DISPC_WB_CONV_COEF2_RESERVED_80_MASK                                                            (0xf8000000U)

#define DSS_DISPC_WB_CONV_COEF2_CRG_SHIFT                                                                   (0U)
#define DSS_DISPC_WB_CONV_COEF2_CRG_MASK                                                                    (0x000007ffU)

#define DSS_DISPC_WB_CONV_COEF2_CRB_SHIFT                                                                   (16U)
#define DSS_DISPC_WB_CONV_COEF2_CRB_MASK                                                                    (0x07ff0000U)

#define DSS_DISPC_WB_CONV_COEF3_CBR_SHIFT                                                                   (0U)
#define DSS_DISPC_WB_CONV_COEF3_CBR_MASK                                                                    (0x000007ffU)

#define DSS_DISPC_WB_CONV_COEF3_RESERVED_82_SHIFT                                                           (27U)
#define DSS_DISPC_WB_CONV_COEF3_RESERVED_82_MASK                                                            (0xf8000000U)

#define DSS_DISPC_WB_CONV_COEF3_RESERVED_83_SHIFT                                                           (11U)
#define DSS_DISPC_WB_CONV_COEF3_RESERVED_83_MASK                                                            (0x0000f800U)

#define DSS_DISPC_WB_CONV_COEF3_CBG_SHIFT                                                                   (16U)
#define DSS_DISPC_WB_CONV_COEF3_CBG_MASK                                                                    (0x07ff0000U)

#define DSS_DISPC_WB_CONV_COEF4_CBB_SHIFT                                                                   (0U)
#define DSS_DISPC_WB_CONV_COEF4_CBB_MASK                                                                    (0x000007ffU)

#define DSS_DISPC_WB_CONV_COEF4_RESERVED_84_SHIFT                                                           (11U)
#define DSS_DISPC_WB_CONV_COEF4_RESERVED_84_MASK                                                            (0xfffff800U)

#define DSS_DISPC_WB_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                                          (0U)
#define DSS_DISPC_WB_BUF_SIZE_STATUS_BUFSIZE_MASK                                                           (0x0000ffffU)

#define DSS_DISPC_WB_BUF_SIZE_STATUS_RESERVED_85_SHIFT                                                      (16U)
#define DSS_DISPC_WB_BUF_SIZE_STATUS_RESERVED_85_MASK                                                       (0xffff0000U)

#define DSS_DISPC_WB_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                                   (16U)
#define DSS_DISPC_WB_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                                    (0xffff0000U)

#define DSS_DISPC_WB_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                                    (0U)
#define DSS_DISPC_WB_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                                     (0x0000ffffU)

#define DSS_DISPC_WB_FIR_RESERVED_88_SHIFT                                                                  (29U)
#define DSS_DISPC_WB_FIR_RESERVED_88_MASK                                                                   (0xe0000000U)

#define DSS_DISPC_WB_FIR_FIRVINC_SHIFT                                                                      (16U)
#define DSS_DISPC_WB_FIR_FIRVINC_MASK                                                                       (0x1fff0000U)

#define DSS_DISPC_WB_FIR_RESERVED_89_SHIFT                                                                  (13U)
#define DSS_DISPC_WB_FIR_RESERVED_89_MASK                                                                   (0x0000e000U)

#define DSS_DISPC_WB_FIR_FIRHINC_SHIFT                                                                      (0U)
#define DSS_DISPC_WB_FIR_FIRHINC_MASK                                                                       (0x00001fffU)

#define DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_SHIFT                                                            (16U)
#define DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_MASK                                                             (0x0fff0000U)

#define DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_SHIFT                                                            (0U)
#define DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_MASK                                                             (0x000007ffU)

#define DSS_DISPC_WB_PICTURE_SIZE_RESERVED1_SHIFT                                                           (28U)
#define DSS_DISPC_WB_PICTURE_SIZE_RESERVED1_MASK                                                            (0xf0000000U)

#define DSS_DISPC_WB_PICTURE_SIZE_RESERVED_SHIFT                                                            (11U)
#define DSS_DISPC_WB_PICTURE_SIZE_RESERVED_MASK                                                             (0x0000f800U)

#define DSS_DISPC_WB_PIXEL_INC_RESERVED_92_SHIFT                                                            (8U)
#define DSS_DISPC_WB_PIXEL_INC_RESERVED_92_MASK                                                             (0xffffff00U)

#define DSS_DISPC_WB_PIXEL_INC_PIXELINC_SHIFT                                                               (0U)
#define DSS_DISPC_WB_PIXEL_INC_PIXELINC_MASK                                                                (0x000000ffU)

#define DSS_DISPC_WB_ROW_INC_ROWINC_SHIFT                                                                   (0U)
#define DSS_DISPC_WB_ROW_INC_ROWINC_MASK                                                                    (0xffffffffU)

#define DSS_DISPC_WB_SIZE_SIZEY_SHIFT                                                                       (16U)
#define DSS_DISPC_WB_SIZE_SIZEY_MASK                                                                        (0x0fff0000U)

#define DSS_DISPC_WB_SIZE_SIZEX_SHIFT                                                                       (0U)
#define DSS_DISPC_WB_SIZE_SIZEX_MASK                                                                        (0x000007ffU)

#define DSS_DISPC_WB_SIZE_RESERVED_96_SHIFT                                                                 (11U)
#define DSS_DISPC_WB_SIZE_RESERVED_96_MASK                                                                  (0x0000f800U)

#define DSS_DISPC_WB_SIZE_RESERVED_SHIFT                                                                    (28U)
#define DSS_DISPC_WB_SIZE_RESERVED_MASK                                                                     (0xf0000000U)

#define DSS_DISPC_VID1_BA_UV_BA_SHIFT                                                                       (0U)
#define DSS_DISPC_VID1_BA_UV_BA_MASK                                                                        (0xffffffffU)

#define DSS_DISPC_VID2_BA_UV_BA_SHIFT                                                                       (0U)
#define DSS_DISPC_VID2_BA_UV_BA_MASK                                                                        (0xffffffffU)

#define DSS_DISPC_VID3_BA_UV_BA_SHIFT                                                                       (0U)
#define DSS_DISPC_VID3_BA_UV_BA_MASK                                                                        (0xffffffffU)

#define DSS_DISPC_WB_BA_UV_BA_SHIFT                                                                         (0U)
#define DSS_DISPC_WB_BA_UV_BA_MASK                                                                          (0xffffffffU)

#define DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_Y_SHIFT                                                        (1U)
#define DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_Y_MASK                                                         (0x0000000eU)

#define DSS_DISPC_VID1_ATTRIBUTES2_VC1ENABLE_SHIFT                                                          (0U)
#define DSS_DISPC_VID1_ATTRIBUTES2_VC1ENABLE_MASK                                                           (0x00000001U)
#define DSS_DISPC_VID1_ATTRIBUTES2_VC1ENABLE_VC1DIS                                                          (0U)
#define DSS_DISPC_VID1_ATTRIBUTES2_VC1ENABLE_VC1ENB                                                          (1U)

#define DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_CBCR_SHIFT                                                     (4U)
#define DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_CBCR_MASK                                                      (0x00000070U)

#define DSS_DISPC_VID1_ATTRIBUTES2_RESERVED_11_SHIFT                                                        (7U)
#define DSS_DISPC_VID1_ATTRIBUTES2_RESERVED_11_MASK                                                         (0x00000080U)

#define DSS_DISPC_VID1_ATTRIBUTES2_YUVCHROMARESAMPLING_SHIFT                                                (8U)
#define DSS_DISPC_VID1_ATTRIBUTES2_YUVCHROMARESAMPLING_MASK                                                 (0x00000100U)
#define DSS_DISPC_VID1_ATTRIBUTES2_YUVCHROMARESAMPLING_AVERAGE                                               (0U)
#define DSS_DISPC_VID1_ATTRIBUTES2_YUVCHROMARESAMPLING_FILTER                                                (1U)

#define DSS_DISPC_VID1_ATTRIBUTES2_SUBSAMPLINGPATTERN_SHIFT                                                 (9U)
#define DSS_DISPC_VID1_ATTRIBUTES2_SUBSAMPLINGPATTERN_MASK                                                  (0x00000e00U)

#define DSS_DISPC_VID1_ATTRIBUTES2_RESERVED_SHIFT                                                           (12U)
#define DSS_DISPC_VID1_ATTRIBUTES2_RESERVED_MASK                                                            (0xfffff000U)

#define DSS_DISPC_VID2_ATTRIBUTES2_VC1_RANGE_Y_SHIFT                                                        (1U)
#define DSS_DISPC_VID2_ATTRIBUTES2_VC1_RANGE_Y_MASK                                                         (0x0000000eU)

#define DSS_DISPC_VID2_ATTRIBUTES2_VC1ENABLE_SHIFT                                                          (0U)
#define DSS_DISPC_VID2_ATTRIBUTES2_VC1ENABLE_MASK                                                           (0x00000001U)
#define DSS_DISPC_VID2_ATTRIBUTES2_VC1ENABLE_VC1DIS                                                          (0U)
#define DSS_DISPC_VID2_ATTRIBUTES2_VC1ENABLE_VC1ENB                                                          (1U)

#define DSS_DISPC_VID2_ATTRIBUTES2_VC1_RANGE_CBCR_SHIFT                                                     (4U)
#define DSS_DISPC_VID2_ATTRIBUTES2_VC1_RANGE_CBCR_MASK                                                      (0x00000070U)

#define DSS_DISPC_VID2_ATTRIBUTES2_RESERVED_11_SHIFT                                                        (7U)
#define DSS_DISPC_VID2_ATTRIBUTES2_RESERVED_11_MASK                                                         (0x00000080U)

#define DSS_DISPC_VID2_ATTRIBUTES2_YUVCHROMARESAMPLING_SHIFT                                                (8U)
#define DSS_DISPC_VID2_ATTRIBUTES2_YUVCHROMARESAMPLING_MASK                                                 (0x00000100U)
#define DSS_DISPC_VID2_ATTRIBUTES2_YUVCHROMARESAMPLING_AVERAGE                                               (0U)
#define DSS_DISPC_VID2_ATTRIBUTES2_YUVCHROMARESAMPLING_FILTER                                                (1U)

#define DSS_DISPC_VID2_ATTRIBUTES2_SUBSAMPLINGPATTERN_SHIFT                                                 (9U)
#define DSS_DISPC_VID2_ATTRIBUTES2_SUBSAMPLINGPATTERN_MASK                                                  (0x00000e00U)

#define DSS_DISPC_VID2_ATTRIBUTES2_RESERVED_SHIFT                                                           (12U)
#define DSS_DISPC_VID2_ATTRIBUTES2_RESERVED_MASK                                                            (0xfffff000U)

#define DSS_DISPC_VID3_ATTRIBUTES2_VC1_RANGE_Y_SHIFT                                                        (1U)
#define DSS_DISPC_VID3_ATTRIBUTES2_VC1_RANGE_Y_MASK                                                         (0x0000000eU)

#define DSS_DISPC_VID3_ATTRIBUTES2_VC1ENABLE_SHIFT                                                          (0U)
#define DSS_DISPC_VID3_ATTRIBUTES2_VC1ENABLE_MASK                                                           (0x00000001U)
#define DSS_DISPC_VID3_ATTRIBUTES2_VC1ENABLE_VC1DIS                                                          (0U)
#define DSS_DISPC_VID3_ATTRIBUTES2_VC1ENABLE_VC1ENB                                                          (1U)

#define DSS_DISPC_VID3_ATTRIBUTES2_VC1_RANGE_CBCR_SHIFT                                                     (4U)
#define DSS_DISPC_VID3_ATTRIBUTES2_VC1_RANGE_CBCR_MASK                                                      (0x00000070U)

#define DSS_DISPC_VID3_ATTRIBUTES2_RESERVED_11_SHIFT                                                        (7U)
#define DSS_DISPC_VID3_ATTRIBUTES2_RESERVED_11_MASK                                                         (0x00000080U)

#define DSS_DISPC_VID3_ATTRIBUTES2_YUVCHROMARESAMPLING_SHIFT                                                (8U)
#define DSS_DISPC_VID3_ATTRIBUTES2_YUVCHROMARESAMPLING_MASK                                                 (0x00000100U)
#define DSS_DISPC_VID3_ATTRIBUTES2_YUVCHROMARESAMPLING_AVERAGE                                               (0U)
#define DSS_DISPC_VID3_ATTRIBUTES2_YUVCHROMARESAMPLING_FILTER                                                (1U)

#define DSS_DISPC_VID3_ATTRIBUTES2_SUBSAMPLINGPATTERN_SHIFT                                                 (9U)
#define DSS_DISPC_VID3_ATTRIBUTES2_SUBSAMPLINGPATTERN_MASK                                                  (0x00000e00U)

#define DSS_DISPC_VID3_ATTRIBUTES2_RESERVED_SHIFT                                                           (12U)
#define DSS_DISPC_VID3_ATTRIBUTES2_RESERVED_MASK                                                            (0xfffff000U)

#define DSS_DISPC_GAMMA_TABLE0_VALUE_R_SHIFT                                                                (16U)
#define DSS_DISPC_GAMMA_TABLE0_VALUE_R_MASK                                                                 (0x00ff0000U)

#define DSS_DISPC_GAMMA_TABLE0_INDEX_SHIFT                                                                  (24U)
#define DSS_DISPC_GAMMA_TABLE0_INDEX_MASK                                                                   (0xff000000U)

#define DSS_DISPC_GAMMA_TABLE0_VALUE_G_SHIFT                                                                (8U)
#define DSS_DISPC_GAMMA_TABLE0_VALUE_G_MASK                                                                 (0x0000ff00U)

#define DSS_DISPC_GAMMA_TABLE0_VALUE_B_SHIFT                                                                (0U)
#define DSS_DISPC_GAMMA_TABLE0_VALUE_B_MASK                                                                 (0x000000ffU)

#define DSS_DISPC_GAMMA_TABLE2_VALUE_R_SHIFT                                                                (20U)
#define DSS_DISPC_GAMMA_TABLE2_VALUE_R_MASK                                                                 (0x3ff00000U)

#define DSS_DISPC_GAMMA_TABLE2_INDEX_SHIFT                                                                  (31U)
#define DSS_DISPC_GAMMA_TABLE2_INDEX_MASK                                                                   (0x80000000U)

#define DSS_DISPC_GAMMA_TABLE2_VALUE_G_SHIFT                                                                (10U)
#define DSS_DISPC_GAMMA_TABLE2_VALUE_G_MASK                                                                 (0x000ffc00U)

#define DSS_DISPC_GAMMA_TABLE2_VALUE_B_SHIFT                                                                (0U)
#define DSS_DISPC_GAMMA_TABLE2_VALUE_B_MASK                                                                 (0x000003ffU)

#define DSS_DISPC_GAMMA_TABLE2_RESERVED_SHIFT                                                               (30U)
#define DSS_DISPC_GAMMA_TABLE2_RESERVED_MASK                                                                (0x40000000U)

#define DSS_DISPC_VID1_FIR2_RESERVED_64_SHIFT                                                               (29U)
#define DSS_DISPC_VID1_FIR2_RESERVED_64_MASK                                                                (0xe0000000U)

#define DSS_DISPC_VID1_FIR2_FIRVINC_SHIFT                                                                   (16U)
#define DSS_DISPC_VID1_FIR2_FIRVINC_MASK                                                                    (0x1fff0000U)

#define DSS_DISPC_VID1_FIR2_RESERVED_65_SHIFT                                                               (13U)
#define DSS_DISPC_VID1_FIR2_RESERVED_65_MASK                                                                (0x0000e000U)

#define DSS_DISPC_VID1_FIR2_FIRHINC_SHIFT                                                                   (0U)
#define DSS_DISPC_VID1_FIR2_FIRHINC_MASK                                                                    (0x00001fffU)

#define DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_SHIFT                                                           (0U)
#define DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_MASK                                                            (0x000007ffU)

#define DSS_DISPC_VID1_ACCU2_VERTICALACCU_SHIFT                                                             (16U)
#define DSS_DISPC_VID1_ACCU2_VERTICALACCU_MASK                                                              (0x07ff0000U)

#define DSS_DISPC_VID1_ACCU2_RESERVED_SHIFT                                                                 (11U)
#define DSS_DISPC_VID1_ACCU2_RESERVED_MASK                                                                  (0x0000f800U)

#define DSS_DISPC_VID1_ACCU2_RESERVED1_SHIFT                                                                (27U)
#define DSS_DISPC_VID1_ACCU2_RESERVED1_MASK                                                                 (0xf8000000U)

#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_SHIFT                                                             (16U)
#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_SHIFT                                                             (8U)
#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_SHIFT                                                             (0U)
#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_SHIFT                                                             (24U)
#define DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_SHIFT                                                            (0U)
#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_MASK                                                             (0x000000ffU)

#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_SHIFT                                                            (8U)
#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_SHIFT                                                            (16U)
#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_MASK                                                             (0x00ff0000U)

#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_SHIFT                                                            (24U)
#define DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_MASK                                                             (0xff000000U)

#define DSS_DISPC_VID1_FIR_COEF_V2_RESERVED_110_SHIFT                                                       (16U)
#define DSS_DISPC_VID1_FIR_COEF_V2_RESERVED_110_MASK                                                        (0xffff0000U)

#define DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_SHIFT                                                            (8U)
#define DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_SHIFT                                                            (0U)
#define DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_MASK                                                             (0x000000ffU)

#define DSS_DISPC_VID2_FIR2_RESERVED_64_SHIFT                                                               (29U)
#define DSS_DISPC_VID2_FIR2_RESERVED_64_MASK                                                                (0xe0000000U)

#define DSS_DISPC_VID2_FIR2_FIRVINC_SHIFT                                                                   (16U)
#define DSS_DISPC_VID2_FIR2_FIRVINC_MASK                                                                    (0x1fff0000U)

#define DSS_DISPC_VID2_FIR2_RESERVED_65_SHIFT                                                               (13U)
#define DSS_DISPC_VID2_FIR2_RESERVED_65_MASK                                                                (0x0000e000U)

#define DSS_DISPC_VID2_FIR2_FIRHINC_SHIFT                                                                   (0U)
#define DSS_DISPC_VID2_FIR2_FIRHINC_MASK                                                                    (0x00001fffU)

#define DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_SHIFT                                                           (0U)
#define DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_MASK                                                            (0x000007ffU)

#define DSS_DISPC_VID2_ACCU2_VERTICALACCU_SHIFT                                                             (16U)
#define DSS_DISPC_VID2_ACCU2_VERTICALACCU_MASK                                                              (0x07ff0000U)

#define DSS_DISPC_VID2_ACCU2_RESERVED_SHIFT                                                                 (11U)
#define DSS_DISPC_VID2_ACCU2_RESERVED_MASK                                                                  (0x0000f800U)

#define DSS_DISPC_VID2_ACCU2_RESERVED1_SHIFT                                                                (27U)
#define DSS_DISPC_VID2_ACCU2_RESERVED1_MASK                                                                 (0xf8000000U)

#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_SHIFT                                                             (16U)
#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_SHIFT                                                             (8U)
#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_SHIFT                                                             (0U)
#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_SHIFT                                                             (24U)
#define DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_SHIFT                                                            (16U)
#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_MASK                                                             (0x00ff0000U)

#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_SHIFT                                                            (8U)
#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_SHIFT                                                            (0U)
#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_MASK                                                             (0x000000ffU)

#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_SHIFT                                                            (24U)
#define DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_MASK                                                             (0xff000000U)

#define DSS_DISPC_VID2_FIR_COEF_V2_RESERVED_111_SHIFT                                                       (16U)
#define DSS_DISPC_VID2_FIR_COEF_V2_RESERVED_111_MASK                                                        (0xffff0000U)

#define DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_SHIFT                                                            (8U)
#define DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_SHIFT                                                            (0U)
#define DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_MASK                                                             (0x000000ffU)

#define DSS_DISPC_VID3_FIR2_RESERVED_64_SHIFT                                                               (29U)
#define DSS_DISPC_VID3_FIR2_RESERVED_64_MASK                                                                (0xe0000000U)

#define DSS_DISPC_VID3_FIR2_FIRVINC_SHIFT                                                                   (16U)
#define DSS_DISPC_VID3_FIR2_FIRVINC_MASK                                                                    (0x1fff0000U)

#define DSS_DISPC_VID3_FIR2_RESERVED_65_SHIFT                                                               (13U)
#define DSS_DISPC_VID3_FIR2_RESERVED_65_MASK                                                                (0x0000e000U)

#define DSS_DISPC_VID3_FIR2_FIRHINC_SHIFT                                                                   (0U)
#define DSS_DISPC_VID3_FIR2_FIRHINC_MASK                                                                    (0x00001fffU)

#define DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_SHIFT                                                           (0U)
#define DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_MASK                                                            (0x000007ffU)

#define DSS_DISPC_VID3_ACCU2_VERTICALACCU_SHIFT                                                             (16U)
#define DSS_DISPC_VID3_ACCU2_VERTICALACCU_MASK                                                              (0x07ff0000U)

#define DSS_DISPC_VID3_ACCU2_RESERVED_SHIFT                                                                 (11U)
#define DSS_DISPC_VID3_ACCU2_RESERVED_MASK                                                                  (0x0000f800U)

#define DSS_DISPC_VID3_ACCU2_RESERVED1_SHIFT                                                                (27U)
#define DSS_DISPC_VID3_ACCU2_RESERVED1_MASK                                                                 (0xf8000000U)

#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_SHIFT                                                             (16U)
#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_MASK                                                              (0x00ff0000U)

#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_SHIFT                                                             (8U)
#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_MASK                                                              (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_SHIFT                                                             (0U)
#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_MASK                                                              (0x000000ffU)

#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_SHIFT                                                             (24U)
#define DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_MASK                                                              (0xff000000U)

#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_SHIFT                                                            (8U)
#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_SHIFT                                                            (0U)
#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_MASK                                                             (0x000000ffU)

#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_SHIFT                                                            (24U)
#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_MASK                                                             (0xff000000U)

#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_SHIFT                                                            (16U)
#define DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_MASK                                                             (0x00ff0000U)

#define DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_SHIFT                                                            (8U)
#define DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_MASK                                                             (0x0000ff00U)

#define DSS_DISPC_VID3_FIR_COEF_V2_RESERVED_111_SHIFT                                                       (16U)
#define DSS_DISPC_VID3_FIR_COEF_V2_RESERVED_111_MASK                                                        (0xffff0000U)

#define DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_SHIFT                                                            (0U)
#define DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_MASK                                                             (0x000000ffU)

#define DSS_DISPC_WB_FIR2_RESERVED_64_SHIFT                                                                 (29U)
#define DSS_DISPC_WB_FIR2_RESERVED_64_MASK                                                                  (0xe0000000U)

#define DSS_DISPC_WB_FIR2_FIRVINC_SHIFT                                                                     (16U)
#define DSS_DISPC_WB_FIR2_FIRVINC_MASK                                                                      (0x1fff0000U)

#define DSS_DISPC_WB_FIR2_RESERVED_65_SHIFT                                                                 (13U)
#define DSS_DISPC_WB_FIR2_RESERVED_65_MASK                                                                  (0x0000e000U)

#define DSS_DISPC_WB_FIR2_FIRHINC_SHIFT                                                                     (0U)
#define DSS_DISPC_WB_FIR2_FIRHINC_MASK                                                                      (0x00001fffU)

#define DSS_DISPC_WB_ACCU2_HORIZONTALACCU_SHIFT                                                             (0U)
#define DSS_DISPC_WB_ACCU2_HORIZONTALACCU_MASK                                                              (0x000007ffU)

#define DSS_DISPC_WB_ACCU2_VERTICALACCU_SHIFT                                                               (16U)
#define DSS_DISPC_WB_ACCU2_VERTICALACCU_MASK                                                                (0x07ff0000U)

#define DSS_DISPC_WB_ACCU2_RESERVED_SHIFT                                                                   (11U)
#define DSS_DISPC_WB_ACCU2_RESERVED_MASK                                                                    (0x0000f800U)

#define DSS_DISPC_WB_ACCU2_RESERVED1_SHIFT                                                                  (27U)
#define DSS_DISPC_WB_ACCU2_RESERVED1_MASK                                                                   (0xf8000000U)

#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_SHIFT                                                               (16U)
#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_MASK                                                                (0x00ff0000U)

#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_SHIFT                                                               (8U)
#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_MASK                                                                (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_SHIFT                                                               (0U)
#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_MASK                                                                (0x000000ffU)

#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_SHIFT                                                               (24U)
#define DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_MASK                                                                (0xff000000U)

#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_SHIFT                                                              (8U)
#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_MASK                                                               (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_SHIFT                                                              (0U)
#define DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_MASK                                                               (0x000000ffU)

#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_SHIFT                                                              (24U)
#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_MASK                                                               (0xff000000U)

#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_SHIFT                                                              (16U)
#define DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_MASK                                                               (0x00ff0000U)

#define DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_SHIFT                                                              (8U)
#define DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_MASK                                                               (0x0000ff00U)

#define DSS_DISPC_WB_FIR_COEF_V2_RESERVED_111_SHIFT                                                         (16U)
#define DSS_DISPC_WB_FIR_COEF_V2_RESERVED_111_MASK                                                          (0xffff0000U)

#define DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_SHIFT                                                              (0U)
#define DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_MASK                                                               (0x000000ffU)

#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_SHIFT                                                            (0U)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_MASK                                                             (0x0000003fU)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_GFX                                                               (0U)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_VID1                                                              (9U)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_VID2                                                              (18U)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_VID3                                                              (27U)
#define DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_WB                                                                (36U)

#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_SHIFT                                                           (6U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_MASK                                                            (0x00000fc0U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_GFX                                                              (0U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_VID1                                                             (9U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_VID2                                                             (18U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_VID3                                                             (27U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_WB                                                               (36U)

#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_SHIFT                                                           (12U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_MASK                                                            (0x0003f000U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_GFX                                                              (0U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_VID1                                                             (9U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_VID2                                                             (18U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_VID3                                                             (27U)
#define DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_WB                                                               (36U)

#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_SHIFT                                                           (18U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_MASK                                                            (0x00fc0000U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_GFX                                                              (0U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_VID1                                                             (9U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_VID2                                                             (18U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_VID3                                                             (27U)
#define DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_WB                                                               (36U)

#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_SHIFT                                                             (24U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_MASK                                                              (0x3f000000U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_GFX                                                                (0U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_VID1                                                               (9U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_VID2                                                               (18U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_VID3                                                               (27U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_WB                                                                 (36U)

#define DSS_DISPC_GLOBAL_BUFFER_RESERVED_SHIFT                                                              (30U)
#define DSS_DISPC_GLOBAL_BUFFER_RESERVED_MASK                                                               (0xc0000000U)

#define DSS_DISPC_DIVISOR_RESERVED_16_SHIFT                                                                 (24U)
#define DSS_DISPC_DIVISOR_RESERVED_16_MASK                                                                  (0xff000000U)

#define DSS_DISPC_DIVISOR_LCD_SHIFT                                                                         (16U)
#define DSS_DISPC_DIVISOR_LCD_MASK                                                                          (0x00ff0000U)

#define DSS_DISPC_DIVISOR_RESERVED_17_SHIFT                                                                 (1U)
#define DSS_DISPC_DIVISOR_RESERVED_17_MASK                                                                  (0x0000fffeU)

#define DSS_DISPC_DIVISOR_ENABLE_SHIFT                                                                      (0U)
#define DSS_DISPC_DIVISOR_ENABLE_MASK                                                                       (0x00000001U)
#define DSS_DISPC_DIVISOR_ENABLE_ENABLE                                                                      (1U)
#define DSS_DISPC_DIVISOR_ENABLE_DISABLE                                                                     (0U)

#define DSS_DISPC_WB_ATTRIBUTES2_WBDELAYCOUNT_SHIFT                                                         (0U)
#define DSS_DISPC_WB_ATTRIBUTES2_WBDELAYCOUNT_MASK                                                          (0x000000ffU)

#define DSS_DISPC_WB_ATTRIBUTES2_RESERVED_SHIFT                                                             (8U)
#define DSS_DISPC_WB_ATTRIBUTES2_RESERVED_MASK                                                              (0xffffff00U)

#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_SHIFT                                                            (0U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_MASK                                                             (0x00000001U)

#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_SHIFT                                                           (1U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_MASK                                                            (0x00000002U)

#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_SHIFT                                                           (2U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_MASK                                                            (0x00000004U)

#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_SHIFT                                                           (3U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_MASK                                                            (0x00000008U)

#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_RESERVED_SHIFT                                                       (4U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN_RESERVED_MASK                                                        (0xfffffff0U)

#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL_SHIFT                                                   (0U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_CTRL_MASK                                                    (0x00000003U)

#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_START_SHIFT                                                  (2U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_MFLAG_START_MASK                                                   (0x00000004U)

#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_RESERVED_SHIFT                                                     (3U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_RESERVED_MASK                                                      (0xfffffff8U)

#define DSS_DISPC_GFX_MFLAG_THRESHOLD_LT_MFLAG_SHIFT                                                        (0U)
#define DSS_DISPC_GFX_MFLAG_THRESHOLD_LT_MFLAG_MASK                                                         (0x0000ffffU)

#define DSS_DISPC_GFX_MFLAG_THRESHOLD_HT_MFLAG_SHIFT                                                        (16U)
#define DSS_DISPC_GFX_MFLAG_THRESHOLD_HT_MFLAG_MASK                                                         (0xffff0000U)

#define DSS_DISPC_VID1_MFLAG_THRESHOLD_LT_MFLAG_SHIFT                                                       (0U)
#define DSS_DISPC_VID1_MFLAG_THRESHOLD_LT_MFLAG_MASK                                                        (0x0000ffffU)

#define DSS_DISPC_VID1_MFLAG_THRESHOLD_HT_MFLAG_SHIFT                                                       (16U)
#define DSS_DISPC_VID1_MFLAG_THRESHOLD_HT_MFLAG_MASK                                                        (0xffff0000U)

#define DSS_DISPC_VID2_MFLAG_THRESHOLD_LT_MFLAG_SHIFT                                                       (0U)
#define DSS_DISPC_VID2_MFLAG_THRESHOLD_LT_MFLAG_MASK                                                        (0x0000ffffU)

#define DSS_DISPC_VID2_MFLAG_THRESHOLD_HT_MFLAG_SHIFT                                                       (16U)
#define DSS_DISPC_VID2_MFLAG_THRESHOLD_HT_MFLAG_MASK                                                        (0xffff0000U)

#define DSS_DISPC_VID3_MFLAG_THRESHOLD_LT_MFLAG_SHIFT                                                       (0U)
#define DSS_DISPC_VID3_MFLAG_THRESHOLD_LT_MFLAG_MASK                                                        (0x0000ffffU)

#define DSS_DISPC_VID3_MFLAG_THRESHOLD_HT_MFLAG_SHIFT                                                       (16U)
#define DSS_DISPC_VID3_MFLAG_THRESHOLD_HT_MFLAG_MASK                                                        (0xffff0000U)

#define DSS_DISPC_WB_MFLAG_THRESHOLD_LT_MFLAG_SHIFT                                                         (0U)
#define DSS_DISPC_WB_MFLAG_THRESHOLD_LT_MFLAG_MASK                                                          (0x0000ffffU)

#define DSS_DISPC_WB_MFLAG_THRESHOLD_HT_MFLAG_SHIFT                                                         (16U)
#define DSS_DISPC_WB_MFLAG_THRESHOLD_HT_MFLAG_MASK                                                          (0xffff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DISPC_H_ */
