/*
 * hw_dss_wb.h
 *
 * Register-level header file for DSS_WB
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

#ifndef DSS_WB_HW_H_
#define DSS_WB_HW_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
 * Register Definitions
 ****************************************************************************************************/

#define DSS_WB_ACCUH(n)                                             (0x0U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_ACCUH2(n)                                            (0x8U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_ACCUV(n)                                             (0x10U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_ACCUV2(n)                                            (0x18U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_ATTRIBUTES                                           (0x20U)
#define DSS_WB_ATTRIBUTES2                                          (0x24U)
#define DSS_WB_BA(n)                                                (0x28U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_BA_UV(n)                                             (0x30U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_BUF_SIZE_STATUS                                      (0x38U)
#define DSS_WB_BUF_THRESHOLD                                        (0x3cU)
#define DSS_WB_CONV_COEF0                                           (0x40U)
#define DSS_WB_CONV_COEF1                                           (0x44U)
#define DSS_WB_CONV_COEF2                                           (0x48U)
#define DSS_WB_CONV_COEF3                                           (0x4cU)
#define DSS_WB_CONV_COEF4                                           (0x50U)
#define DSS_WB_CONV_COEF5                                           (0x54U)
#define DSS_WB_CONV_COEF6                                           (0x58U)
#define DSS_WB_FIRH                                                 (0x5cU)
#define DSS_WB_FIRH2                                                (0x60U)
#define DSS_WB_FIRV                                                 (0x64U)
#define DSS_WB_FIRV2                                                (0x68U)
#define DSS_WB_FIR_COEF_H0(n)                                       (0x6cU + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_H0_C(n)                                     (0x90U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_H12(n)                                      (0xb4U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_H12_C(n)                                    (0xf4U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_V0(n)                                       (0x134U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_V0_C(n)                                     (0x158U + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_V12(n)                                      (0x17cU + \
                                                                     ((n) * 0x4U))
#define DSS_WB_FIR_COEF_V12_C(n)                                    (0x1bcU + \
                                                                     ((n) * 0x4U))
#define DSS_WB_IRQENABLE                                            (0x1fcU)
#define DSS_WB_IRQSTATUS                                            (0x200U)
#define DSS_WB_MFLAG_THRESHOLD                                      (0x204U)
#define DSS_WB_PICTURE_SIZE                                         (0x208U)
#define DSS_WB_SIZE                                                 (0x210U)
#define DSS_WB_POSITION                                             (0x214U)
#define DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY                     (0x218U)

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/

#define DSS_WB_ACCUH_HORIZONTALACCU_SHIFT                                               ( \
        0U)
#define DSS_WB_ACCUH_HORIZONTALACCU_MASK                                                ( \
        0x00ffffffU)

#define DSS_WB_ACCUH_RESERVED_SHIFT                                                     ( \
        24U)
#define DSS_WB_ACCUH_RESERVED_MASK                                                      ( \
        0xff000000U)

#define DSS_WB_ACCUH2_HORIZONTALACCU_SHIFT                                              ( \
        0U)
#define DSS_WB_ACCUH2_HORIZONTALACCU_MASK                                               ( \
        0x00ffffffU)

#define DSS_WB_ACCUH2_RESERVED_SHIFT                                                    ( \
        24U)
#define DSS_WB_ACCUH2_RESERVED_MASK                                                     ( \
        0xff000000U)

#define DSS_WB_ACCUV_VERTICALACCU_SHIFT                                                 ( \
        0U)
#define DSS_WB_ACCUV_VERTICALACCU_MASK                                                  ( \
        0x00ffffffU)

#define DSS_WB_ACCUV_RESERVED_SHIFT                                                     ( \
        24U)
#define DSS_WB_ACCUV_RESERVED_MASK                                                      ( \
        0xff000000U)

#define DSS_WB_ACCUV2_VERTICALACCU_SHIFT                                                ( \
        0U)
#define DSS_WB_ACCUV2_VERTICALACCU_MASK                                                 ( \
        0x00ffffffU)

#define DSS_WB_ACCUV2_RESERVED_SHIFT                                                    ( \
        24U)
#define DSS_WB_ACCUV2_RESERVED_MASK                                                     ( \
        0xff000000U)

#define DSS_WB_ATTRIBUTES_ENABLE_SHIFT                                                  ( \
        0U)
#define DSS_WB_ATTRIBUTES_ENABLE_MASK                                                   ( \
        0x00000001U)
#define DSS_WB_ATTRIBUTES_ENABLE_WBDIS                                                   ( \
        0U)
#define DSS_WB_ATTRIBUTES_ENABLE_WBENB                                                   ( \
        1U)

#define DSS_WB_ATTRIBUTES_COLORCONVENABLE_SHIFT                                         ( \
        11U)
#define DSS_WB_ATTRIBUTES_COLORCONVENABLE_MASK                                          ( \
        0x00000800U)
#define DSS_WB_ATTRIBUTES_COLORCONVENABLE_COLSPCDIS                                      ( \
        0U)
#define DSS_WB_ATTRIBUTES_COLORCONVENABLE_COLSPCENB                                      ( \
        1U)

#define DSS_WB_ATTRIBUTES_VERTICALTAPS_SHIFT                                            ( \
        21U)
#define DSS_WB_ATTRIBUTES_VERTICALTAPS_MASK                                             ( \
        0x00200000U)
#define DSS_WB_ATTRIBUTES_VERTICALTAPS_TAPS5                                             ( \
        1U)
#define DSS_WB_ATTRIBUTES_VERTICALTAPS_TAPS3                                             ( \
        0U)

#define DSS_WB_ATTRIBUTES_FORMAT_SHIFT                                                  ( \
        1U)
#define DSS_WB_ATTRIBUTES_FORMAT_MASK                                                   ( \
        0x0000007eU)
#define DSS_WB_ATTRIBUTES_FORMAT_YUV2                                                    ( \
        62U)
#define DSS_WB_ATTRIBUTES_FORMAT_UYVY                                                    ( \
        63U)
#define DSS_WB_ATTRIBUTES_FORMAT_NV12                                                    ( \
        61U)
#define DSS_WB_ATTRIBUTES_FORMAT_BGRA32_8888                                             ( \
        10U)
#define DSS_WB_ATTRIBUTES_FORMAT_XRGB16_4444                                             ( \
        32U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGB16_565                                               ( \
        3U)
#define DSS_WB_ATTRIBUTES_FORMAT_XRGB32_8888                                             ( \
        39U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGB24P_888                                              ( \
        11U)
#define DSS_WB_ATTRIBUTES_FORMAT_ARGB16_4444                                             ( \
        0U)
#define DSS_WB_ATTRIBUTES_FORMAT_ARGB32_8888                                             ( \
        7U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBA32_8888                                             ( \
        9U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBX32_8888                                             ( \
        41U)
#define DSS_WB_ATTRIBUTES_FORMAT_ARGB16_1555                                             ( \
        5U)
#define DSS_WB_ATTRIBUTES_FORMAT_XRGB16_1555                                             ( \
        37U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBX16_4444                                             ( \
        34U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBA16_4444                                             ( \
        2U)
#define DSS_WB_ATTRIBUTES_FORMAT_BGRX32_8888                                             ( \
        42U)
#define DSS_WB_ATTRIBUTES_FORMAT_ABGR16_4444                                             ( \
        1U)
#define DSS_WB_ATTRIBUTES_FORMAT_XBGR16_4444                                             ( \
        33U)
#define DSS_WB_ATTRIBUTES_FORMAT_BGR16_565                                               ( \
        4U)
#define DSS_WB_ATTRIBUTES_FORMAT_ABGR16_1555                                             ( \
        6U)
#define DSS_WB_ATTRIBUTES_FORMAT_XBGR16_1555                                             ( \
        38U)
#define DSS_WB_ATTRIBUTES_FORMAT_ABGR32_8888                                             ( \
        8U)
#define DSS_WB_ATTRIBUTES_FORMAT_XBGR32_8888                                             ( \
        40U)
#define DSS_WB_ATTRIBUTES_FORMAT_ARGB64_16161616                                         ( \
        16U)
#define DSS_WB_ATTRIBUTES_FORMAT_XRGB64_16161616                                         ( \
        48U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBA64_16161616                                         ( \
        17U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGBX64_16161616                                         ( \
        49U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED                                                ( \
        12U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED1                                               ( \
        24U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED2                                               ( \
        35U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED3                                               ( \
        43U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED4                                               ( \
        50U)
#define DSS_WB_ATTRIBUTES_FORMAT_RGB565A8                                                ( \
        22U)
#define DSS_WB_ATTRIBUTES_FORMAT_RESERVED5                                               ( \
        18U)
#define DSS_WB_ATTRIBUTES_FORMAT_BGR565A8                                                ( \
        23U)

#define DSS_WB_ATTRIBUTES_CHANNELIN_SHIFT                                               ( \
        15U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_MASK                                                ( \
        0x00078000U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_VP1SEL                                               ( \
        0U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_OVR2SEL                                               ( \
        1U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_GFX1SEL                                              ( \
        4U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_VID1SEL                                              ( \
        7U)
#define DSS_WB_ATTRIBUTES_CHANNELIN_VID2SEL                                              ( \
        8U)

#define DSS_WB_ATTRIBUTES_ARBITRATION_SHIFT                                             ( \
        23U)
#define DSS_WB_ATTRIBUTES_ARBITRATION_MASK                                              ( \
        0x00800000U)
#define DSS_WB_ATTRIBUTES_ARBITRATION_HIGHPRIO                                           ( \
        1U)
#define DSS_WB_ATTRIBUTES_ARBITRATION_NORMALPRIO                                         ( \
        0U)

#define DSS_WB_ATTRIBUTES_FULLRANGE_SHIFT                                               ( \
        12U)
#define DSS_WB_ATTRIBUTES_FULLRANGE_MASK                                                ( \
        0x00001000U)
#define DSS_WB_ATTRIBUTES_FULLRANGE                                                      ( \
        1U)
#define DSS_WB_ATTRIBUTES_FULLRANGE_LIMRANGE                                             ( \
        0U)

#define DSS_WB_ATTRIBUTES_RESIZEENABLE_SHIFT                                            ( \
        7U)
#define DSS_WB_ATTRIBUTES_RESIZEENABLE_MASK                                             ( \
        0x00000180U)
#define DSS_WB_ATTRIBUTES_RESIZEENABLE_HVRESIZE                                          ( \
        3U)
#define DSS_WB_ATTRIBUTES_RESIZEENABLE_VRESIZE                                           ( \
        2U)
#define DSS_WB_ATTRIBUTES_RESIZEENABLE_HRESIZE                                           ( \
        1U)
#define DSS_WB_ATTRIBUTES_RESIZEENABLE_RESIZEPROC                                        ( \
        0U)

#define DSS_WB_ATTRIBUTES_ALPHAENABLE_SHIFT                                             ( \
        9U)
#define DSS_WB_ATTRIBUTES_ALPHAENABLE_MASK                                              ( \
        0x00000200U)
#define DSS_WB_ATTRIBUTES_ALPHAENABLE_DISABLE                                            ( \
        0U)
#define DSS_WB_ATTRIBUTES_ALPHAENABLE_ENABLE                                             ( \
        1U)

#define DSS_WB_ATTRIBUTES_CAPTUREMODE_SHIFT                                             ( \
        24U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_MASK                                              ( \
        0x07000000U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ALL                                                ( \
        0U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1                                              ( \
        1U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_2                                            ( \
        2U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_3                                            ( \
        3U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_4                                            ( \
        4U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_5                                            ( \
        5U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_6                                            ( \
        6U)
#define DSS_WB_ATTRIBUTES_CAPTUREMODE_ONLY1_7                                            ( \
        7U)

#define DSS_WB_ATTRIBUTES_IDLESIZE_SHIFT                                                ( \
        27U)
#define DSS_WB_ATTRIBUTES_IDLESIZE_MASK                                                 ( \
        0x08000000U)
#define DSS_WB_ATTRIBUTES_IDLESIZE_IDLEBURST                                             ( \
        1U)
#define DSS_WB_ATTRIBUTES_IDLESIZE_IDLESINGLE                                            ( \
        0U)

#define DSS_WB_ATTRIBUTES_IDLENUMBER_SHIFT                                              ( \
        28U)
#define DSS_WB_ATTRIBUTES_IDLENUMBER_MASK                                               ( \
        0xf0000000U)

#define DSS_WB_ATTRIBUTES_DOUBLESTRIDE_SHIFT                                            ( \
        22U)
#define DSS_WB_ATTRIBUTES_DOUBLESTRIDE_MASK                                             ( \
        0x00400000U)
#define DSS_WB_ATTRIBUTES_DOUBLESTRIDE_INITIAL                                           ( \
        0U)
#define DSS_WB_ATTRIBUTES_DOUBLESTRIDE_DOUBLE                                            ( \
        1U)

#define DSS_WB_ATTRIBUTES_WRITEBACKMODE_SHIFT                                           ( \
        19U)
#define DSS_WB_ATTRIBUTES_WRITEBACKMODE_MASK                                            ( \
        0x00080000U)
#define DSS_WB_ATTRIBUTES_WRITEBACKMODE_CAPTURE                                          ( \
        0U)
#define DSS_WB_ATTRIBUTES_WRITEBACKMODE_MEM2MEM                                          ( \
        1U)

#define DSS_WB_ATTRIBUTES_RESERVED_SHIFT                                                ( \
        13U)
#define DSS_WB_ATTRIBUTES_RESERVED_MASK                                                 ( \
        0x00006000U)

#define DSS_WB_ATTRIBUTES_RESERVED_BT_SHIFT                                             ( \
        10U)
#define DSS_WB_ATTRIBUTES_RESERVED_BT_MASK                                              ( \
        0x00000400U)

#define DSS_WB_ATTRIBUTES_RESERVED_FTD_SHIFT                                            ( \
        20U)
#define DSS_WB_ATTRIBUTES_RESERVED_FTD_MASK                                             ( \
        0x00100000U)

#define DSS_WB_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                        ( \
        20U)
#define DSS_WB_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                         ( \
        0x00100000U)
#define DSS_WB_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                          ( \
        0U)
#define DSS_WB_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                          ( \
        1U)

#define DSS_WB_ATTRIBUTES_BURSTTYPE_SHIFT                                               ( \
        10U)
#define DSS_WB_ATTRIBUTES_BURSTTYPE_MASK                                                ( \
        0x00000400U)
#define DSS_WB_ATTRIBUTES_BURSTTYPE_INC                                                  ( \
        0U)
#define DSS_WB_ATTRIBUTES_BURSTTYPE_BLCK                                                 ( \
        1U)

#define DSS_WB_ATTRIBUTES2_TAGS_SHIFT                                                   ( \
        26U)
#define DSS_WB_ATTRIBUTES2_TAGS_MASK                                                    ( \
        0x7c000000U)

#define DSS_WB_ATTRIBUTES2_SECURE_SHIFT                                                 ( \
        16U)
#define DSS_WB_ATTRIBUTES2_SECURE_MASK                                                  ( \
        0x00010000U)

#define DSS_WB_ATTRIBUTES2_RESERVED_SHIFT                                               ( \
        1U)
#define DSS_WB_ATTRIBUTES2_RESERVED_MASK                                                ( \
        0x0000fffeU)

#define DSS_WB_ATTRIBUTES2_FSC_SHIFT                                                    ( \
        0U)
#define DSS_WB_ATTRIBUTES2_FSC_MASK                                                     ( \
        0x00000001U)
#define DSS_WB_ATTRIBUTES2_FSC_ENABLE                                                    ( \
        1U)
#define DSS_WB_ATTRIBUTES2_FSC_DISABLE                                                   ( \
        0U)

#define DSS_WB_ATTRIBUTES2_RESERVED2_SHIFT                                              ( \
        18U)
#define DSS_WB_ATTRIBUTES2_RESERVED2_MASK                                               ( \
        0x00fc0000U)

#define DSS_WB_ATTRIBUTES2_RESERVED_COMP_SHIFT                                          ( \
        31U)
#define DSS_WB_ATTRIBUTES2_RESERVED_COMP_MASK                                           ( \
        0x80000000U)

#define DSS_WB_ATTRIBUTES2_RESERVED_COR_SHIFT                                           ( \
        17U)
#define DSS_WB_ATTRIBUTES2_RESERVED_COR_MASK                                            ( \
        0x00020000U)

#define DSS_WB_ATTRIBUTES2_COMPRESSION_SHIFT                                            ( \
        31U)
#define DSS_WB_ATTRIBUTES2_COMPRESSION_MASK                                             ( \
        0x80000000U)
#define DSS_WB_ATTRIBUTES2_COMPRESSION_NOTCOMPRESSED                                     ( \
        0U)
#define DSS_WB_ATTRIBUTES2_COMPRESSION_COMPRESSED                                        ( \
        1U)

#define DSS_WB_ATTRIBUTES2_CORRELATION_SHIFT                                            ( \
        17U)
#define DSS_WB_ATTRIBUTES2_CORRELATION_MASK                                             ( \
        0x00020000U)

#define DSS_WB_ATTRIBUTES2_REGION_BASED_SHIFT                                           ( \
        24U)
#define DSS_WB_ATTRIBUTES2_REGION_BASED_MASK                                            ( \
        0x01000000U)
#define DSS_WB_ATTRIBUTES2_REGION_BASED_DISABLE                                          ( \
        0U)
#define DSS_WB_ATTRIBUTES2_REGION_BASED_ENABLE                                           ( \
        1U)

#define DSS_WB_ATTRIBUTES2_RESERVED3_SHIFT                                              ( \
        25U)
#define DSS_WB_ATTRIBUTES2_RESERVED3_MASK                                               ( \
        0x02000000U)

#define DSS_WB_BA_SHIFT                                                                 ( \
        0U)
#define DSS_WB_BA_MASK                                                                  ( \
        0xffffffffU)

#define DSS_WB_BA_UV_SHIFT                                                              ( \
        0U)
#define DSS_WB_BA_UV_MASK                                                               ( \
        0xffffffffU)

#define DSS_WB_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                            ( \
        0U)
#define DSS_WB_BUF_SIZE_STATUS_BUFSIZE_MASK                                             ( \
        0x0000ffffU)

#define DSS_WB_BUF_SIZE_STATUS_RESERVED_85_SHIFT                                        ( \
        16U)
#define DSS_WB_BUF_SIZE_STATUS_RESERVED_85_MASK                                         ( \
        0xffff0000U)

#define DSS_WB_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                     ( \
        16U)
#define DSS_WB_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                      ( \
        0xffff0000U)

#define DSS_WB_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                      ( \
        0U)
#define DSS_WB_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                       ( \
        0x0000ffffU)

#define DSS_WB_CONV_COEF0_RESERVED_77_SHIFT                                             ( \
        11U)
#define DSS_WB_CONV_COEF0_RESERVED_77_MASK                                              ( \
        0x0000f800U)

#define DSS_WB_CONV_COEF0_YR_SHIFT                                                      ( \
        0U)
#define DSS_WB_CONV_COEF0_YR_MASK                                                       ( \
        0x000007ffU)

#define DSS_WB_CONV_COEF0_YG_SHIFT                                                      ( \
        16U)
#define DSS_WB_CONV_COEF0_YG_MASK                                                       ( \
        0x07ff0000U)

#define DSS_WB_CONV_COEF0_RESERVED_76_SHIFT                                             ( \
        27U)
#define DSS_WB_CONV_COEF0_RESERVED_76_MASK                                              ( \
        0xf8000000U)

#define DSS_WB_CONV_COEF1_RESERVED_79_SHIFT                                             ( \
        11U)
#define DSS_WB_CONV_COEF1_RESERVED_79_MASK                                              ( \
        0x0000f800U)

#define DSS_WB_CONV_COEF1_YB_SHIFT                                                      ( \
        0U)
#define DSS_WB_CONV_COEF1_YB_MASK                                                       ( \
        0x000007ffU)

#define DSS_WB_CONV_COEF1_RESERVED_78_SHIFT                                             ( \
        27U)
#define DSS_WB_CONV_COEF1_RESERVED_78_MASK                                              ( \
        0xf8000000U)

#define DSS_WB_CONV_COEF1_CRR_SHIFT                                                     ( \
        16U)
#define DSS_WB_CONV_COEF1_CRR_MASK                                                      ( \
        0x07ff0000U)

#define DSS_WB_CONV_COEF2_RESERVED_81_SHIFT                                             ( \
        11U)
#define DSS_WB_CONV_COEF2_RESERVED_81_MASK                                              ( \
        0x0000f800U)

#define DSS_WB_CONV_COEF2_RESERVED_80_SHIFT                                             ( \
        27U)
#define DSS_WB_CONV_COEF2_RESERVED_80_MASK                                              ( \
        0xf8000000U)

#define DSS_WB_CONV_COEF2_CRG_SHIFT                                                     ( \
        0U)
#define DSS_WB_CONV_COEF2_CRG_MASK                                                      ( \
        0x000007ffU)

#define DSS_WB_CONV_COEF2_CRB_SHIFT                                                     ( \
        16U)
#define DSS_WB_CONV_COEF2_CRB_MASK                                                      ( \
        0x07ff0000U)

#define DSS_WB_CONV_COEF3_CBR_SHIFT                                                     ( \
        0U)
#define DSS_WB_CONV_COEF3_CBR_MASK                                                      ( \
        0x000007ffU)

#define DSS_WB_CONV_COEF3_RESERVED_82_SHIFT                                             ( \
        27U)
#define DSS_WB_CONV_COEF3_RESERVED_82_MASK                                              ( \
        0xf8000000U)

#define DSS_WB_CONV_COEF3_RESERVED_83_SHIFT                                             ( \
        11U)
#define DSS_WB_CONV_COEF3_RESERVED_83_MASK                                              ( \
        0x0000f800U)

#define DSS_WB_CONV_COEF3_CBG_SHIFT                                                     ( \
        16U)
#define DSS_WB_CONV_COEF3_CBG_MASK                                                      ( \
        0x07ff0000U)

#define DSS_WB_CONV_COEF4_CBB_SHIFT                                                     ( \
        0U)
#define DSS_WB_CONV_COEF4_CBB_MASK                                                      ( \
        0x000007ffU)

#define DSS_WB_CONV_COEF4_RESERVED_SHIFT                                                ( \
        11U)
#define DSS_WB_CONV_COEF4_RESERVED_MASK                                                 ( \
        0xfffff800U)

#define DSS_WB_CONV_COEF5_ROFFSET_SHIFT                                                 ( \
        3U)
#define DSS_WB_CONV_COEF5_ROFFSET_MASK                                                  ( \
        0x0000fff8U)

#define DSS_WB_CONV_COEF5_GOFFSET_SHIFT                                                 ( \
        19U)
#define DSS_WB_CONV_COEF5_GOFFSET_MASK                                                  ( \
        0xfff80000U)

#define DSS_WB_CONV_COEF5_RESERVED_SHIFT                                                ( \
        0U)
#define DSS_WB_CONV_COEF5_RESERVED_MASK                                                 ( \
        0x00000007U)

#define DSS_WB_CONV_COEF5_RESERVED1_SHIFT                                               ( \
        16U)
#define DSS_WB_CONV_COEF5_RESERVED1_MASK                                                ( \
        0x00070000U)

#define DSS_WB_CONV_COEF6_BOFFSET_SHIFT                                                 ( \
        3U)
#define DSS_WB_CONV_COEF6_BOFFSET_MASK                                                  ( \
        0x0000fff8U)

#define DSS_WB_CONV_COEF6_RESERVED1_SHIFT                                               ( \
        16U)
#define DSS_WB_CONV_COEF6_RESERVED1_MASK                                                ( \
        0xffff0000U)

#define DSS_WB_CONV_COEF6_RESERVED_SHIFT                                                ( \
        0U)
#define DSS_WB_CONV_COEF6_RESERVED_MASK                                                 ( \
        0x00000007U)

#define DSS_WB_FIRH_FIRHINC_SHIFT                                                       ( \
        0U)
#define DSS_WB_FIRH_FIRHINC_MASK                                                        ( \
        0x00ffffffU)

#define DSS_WB_FIRH_RESERVED_SHIFT                                                      ( \
        24U)
#define DSS_WB_FIRH_RESERVED_MASK                                                       ( \
        0xff000000U)

#define DSS_WB_FIRH2_FIRHINC_SHIFT                                                      ( \
        0U)
#define DSS_WB_FIRH2_FIRHINC_MASK                                                       ( \
        0x00ffffffU)

#define DSS_WB_FIRH2_RESERVED_SHIFT                                                     ( \
        24U)
#define DSS_WB_FIRH2_RESERVED_MASK                                                      ( \
        0xff000000U)

#define DSS_WB_FIRV_FIRVINC_SHIFT                                                       ( \
        0U)
#define DSS_WB_FIRV_FIRVINC_MASK                                                        ( \
        0x00ffffffU)

#define DSS_WB_FIRV_RESERVED_SHIFT                                                      ( \
        24U)
#define DSS_WB_FIRV_RESERVED_MASK                                                       ( \
        0xff000000U)

#define DSS_WB_FIRV2_FIRVINC_SHIFT                                                      ( \
        0U)
#define DSS_WB_FIRV2_FIRVINC_MASK                                                       ( \
        0x00ffffffU)

#define DSS_WB_FIRV2_RESERVED_SHIFT                                                     ( \
        24U)
#define DSS_WB_FIRV2_RESERVED_MASK                                                      ( \
        0xff000000U)

#define DSS_WB_FIR_COEF_H0_FIRHC0_SHIFT                                                 ( \
        0U)
#define DSS_WB_FIR_COEF_H0_FIRHC0_MASK                                                  ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_H0_RESERVED_SHIFT                                               ( \
        30U)
#define DSS_WB_FIR_COEF_H0_RESERVED_MASK                                                ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_H0_RESERVED1_SHIFT                                              ( \
        10U)
#define DSS_WB_FIR_COEF_H0_RESERVED1_MASK                                               ( \
        0x3ffffc00U)

#define DSS_WB_FIR_COEF_H0_C_FIRHC0_SHIFT                                               ( \
        0U)
#define DSS_WB_FIR_COEF_H0_C_FIRHC0_MASK                                                ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_H0_C_RESERVED_SHIFT                                             ( \
        30U)
#define DSS_WB_FIR_COEF_H0_C_RESERVED_MASK                                              ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_H0_C_RESERVED1_SHIFT                                            ( \
        10U)
#define DSS_WB_FIR_COEF_H0_C_RESERVED1_MASK                                             ( \
        0x3ffffc00U)

#define DSS_WB_FIR_COEF_H12_FIRHC2_SHIFT                                                ( \
        20U)
#define DSS_WB_FIR_COEF_H12_FIRHC2_MASK                                                 ( \
        0x3ff00000U)

#define DSS_WB_FIR_COEF_H12_FIRHC1_SHIFT                                                ( \
        10U)
#define DSS_WB_FIR_COEF_H12_FIRHC1_MASK                                                 ( \
        0x000ffc00U)

#define DSS_WB_FIR_COEF_H12_RESERVED_SHIFT                                              ( \
        30U)
#define DSS_WB_FIR_COEF_H12_RESERVED_MASK                                               ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_H12_RESERVED1_SHIFT                                             ( \
        0U)
#define DSS_WB_FIR_COEF_H12_RESERVED1_MASK                                              ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_H12_C_FIRHC2_SHIFT                                              ( \
        20U)
#define DSS_WB_FIR_COEF_H12_C_FIRHC2_MASK                                               ( \
        0x3ff00000U)

#define DSS_WB_FIR_COEF_H12_C_FIRHC1_SHIFT                                              ( \
        10U)
#define DSS_WB_FIR_COEF_H12_C_FIRHC1_MASK                                               ( \
        0x000ffc00U)

#define DSS_WB_FIR_COEF_H12_C_RESERVED_SHIFT                                            ( \
        30U)
#define DSS_WB_FIR_COEF_H12_C_RESERVED_MASK                                             ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_H12_C_RESERVED1_SHIFT                                           ( \
        0U)
#define DSS_WB_FIR_COEF_H12_C_RESERVED1_MASK                                            ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_V0_FIRVC0_SHIFT                                                 ( \
        0U)
#define DSS_WB_FIR_COEF_V0_FIRVC0_MASK                                                  ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_V0_RESERVED_SHIFT                                               ( \
        30U)
#define DSS_WB_FIR_COEF_V0_RESERVED_MASK                                                ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_V0_RESERVED1_SHIFT                                              ( \
        10U)
#define DSS_WB_FIR_COEF_V0_RESERVED1_MASK                                               ( \
        0x3ffffc00U)

#define DSS_WB_FIR_COEF_V0_C_FIRVC0_SHIFT                                               ( \
        0U)
#define DSS_WB_FIR_COEF_V0_C_FIRVC0_MASK                                                ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_V0_C_RESERVED_SHIFT                                             ( \
        30U)
#define DSS_WB_FIR_COEF_V0_C_RESERVED_MASK                                              ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_V0_C_RESERVED1_SHIFT                                            ( \
        10U)
#define DSS_WB_FIR_COEF_V0_C_RESERVED1_MASK                                             ( \
        0x3ffffc00U)

#define DSS_WB_FIR_COEF_V12_FIRVC2_SHIFT                                                ( \
        20U)
#define DSS_WB_FIR_COEF_V12_FIRVC2_MASK                                                 ( \
        0x3ff00000U)

#define DSS_WB_FIR_COEF_V12_FIRVC1_SHIFT                                                ( \
        10U)
#define DSS_WB_FIR_COEF_V12_FIRVC1_MASK                                                 ( \
        0x000ffc00U)

#define DSS_WB_FIR_COEF_V12_RESERVED_SHIFT                                              ( \
        30U)
#define DSS_WB_FIR_COEF_V12_RESERVED_MASK                                               ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_V12_RESERVED1_SHIFT                                             ( \
        0U)
#define DSS_WB_FIR_COEF_V12_RESERVED1_MASK                                              ( \
        0x000003ffU)

#define DSS_WB_FIR_COEF_V12_C_FIRVC2_SHIFT                                              ( \
        20U)
#define DSS_WB_FIR_COEF_V12_C_FIRVC2_MASK                                               ( \
        0x3ff00000U)

#define DSS_WB_FIR_COEF_V12_C_FIRVC1_SHIFT                                              ( \
        10U)
#define DSS_WB_FIR_COEF_V12_C_FIRVC1_MASK                                               ( \
        0x000ffc00U)

#define DSS_WB_FIR_COEF_V12_C_RESERVED_SHIFT                                            ( \
        30U)
#define DSS_WB_FIR_COEF_V12_C_RESERVED_MASK                                             ( \
        0xc0000000U)

#define DSS_WB_FIR_COEF_V12_C_RESERVED1_SHIFT                                           ( \
        0U)
#define DSS_WB_FIR_COEF_V12_C_RESERVED1_MASK                                            ( \
        0x000003ffU)

#define DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN_SHIFT                                      ( \
        0U)
#define DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN_MASK                                       ( \
        0x00000001U)
#define DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN_MASKED                                      ( \
        0U)
#define DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN_GENINT                                      ( \
        1U)

#define DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN_SHIFT                                     ( \
        1U)
#define DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN_MASK                                      ( \
        0x00000002U)
#define DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN_MASKED                                     ( \
        0U)
#define DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN_GENINT                                     ( \
        1U)

#define DSS_WB_IRQENABLE_WBFRAMEDONE_EN_SHIFT                                           ( \
        2U)
#define DSS_WB_IRQENABLE_WBFRAMEDONE_EN_MASK                                            ( \
        0x00000004U)
#define DSS_WB_IRQENABLE_WBFRAMEDONE_EN_MASKED                                           ( \
        0U)
#define DSS_WB_IRQENABLE_WBFRAMEDONE_EN_GENINT                                           ( \
        1U)

#define DSS_WB_IRQENABLE_RESERVED_SHIFT                                                 ( \
        4U)
#define DSS_WB_IRQENABLE_RESERVED_MASK                                                  ( \
        0xfffffff0U)

#define DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_SHIFT                                    ( \
        3U)
#define DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_MASK                                     ( \
        0x00000008U)
#define DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_MASKED                                    ( \
        0U)
#define DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_GENINT                                    ( \
        1U)

#define DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_SHIFT                                     ( \
        0U)
#define DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_MASK                                      ( \
        0x00000001U)
#define DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_FALSE                                      ( \
        0U)
#define DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_TRUE                                       ( \
        1U)

#define DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_SHIFT                                    ( \
        1U)
#define DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_MASK                                     ( \
        0x00000002U)
#define DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_FALSE                                     ( \
        0U)
#define DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_TRUE                                      ( \
        1U)

#define DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_SHIFT                                          ( \
        2U)
#define DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_MASK                                           ( \
        0x00000004U)
#define DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_FALSE                                           ( \
        0U)
#define DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_TRUE                                            ( \
        1U)

#define DSS_WB_IRQSTATUS_RESERVED_SHIFT                                                 ( \
        4U)
#define DSS_WB_IRQSTATUS_RESERVED_MASK                                                  ( \
        0xfffffff0U)

#define DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ_SHIFT                                   ( \
        3U)
#define DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ_MASK                                    ( \
        0x00000008U)
#define DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ_FALSE                                    ( \
        0U)
#define DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ_TRUE                                     ( \
        1U)

#define DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_SHIFT                                          ( \
        4U)
#define DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_MASK                                           ( \
        0x00000010U)
#define DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_FALSE                                           ( \
        0U)
#define DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_TRUE                                            ( \
        1U)

#define DSS_WB_MFLAG_THRESHOLD_LT_SHIFT                                                 ( \
        0U)
#define DSS_WB_MFLAG_THRESHOLD_LT_MASK                                                  ( \
        0x0000ffffU)

#define DSS_WB_MFLAG_THRESHOLD_HT_SHIFT                                                 ( \
        16U)
#define DSS_WB_MFLAG_THRESHOLD_HT_MASK                                                  ( \
        0xffff0000U)

#define DSS_WB_PICTURE_SIZE_MEMSIZEY_SHIFT                                              ( \
        16U)
#define DSS_WB_PICTURE_SIZE_MEMSIZEY_MASK                                               ( \
        0x0fff0000U)

#define DSS_WB_PICTURE_SIZE_MEMSIZEX_SHIFT                                              ( \
        0U)
#define DSS_WB_PICTURE_SIZE_MEMSIZEX_MASK                                               ( \
        0x00000fffU)

#define DSS_WB_PICTURE_SIZE_RESERVED1_SHIFT                                             ( \
        28U)
#define DSS_WB_PICTURE_SIZE_RESERVED1_MASK                                              ( \
        0xf0000000U)

#define DSS_WB_PICTURE_SIZE_RESERVED_SHIFT                                              ( \
        12U)
#define DSS_WB_PICTURE_SIZE_RESERVED_MASK                                               ( \
        0x0000f000U)

#define DSS_WB_SIZE_SIZEY_SHIFT                                                         ( \
        16U)
#define DSS_WB_SIZE_SIZEY_MASK                                                          ( \
        0x0fff0000U)

#define DSS_WB_SIZE_SIZEX_SHIFT                                                         ( \
        0U)
#define DSS_WB_SIZE_SIZEX_MASK                                                          ( \
        0x00000fffU)

#define DSS_WB_SIZE_RESERVED_SHIFT                                                      ( \
        28U)
#define DSS_WB_SIZE_RESERVED_MASK                                                       ( \
        0xf0000000U)

#define DSS_WB_SIZE_RESERVED1_SHIFT                                                     ( \
        12U)
#define DSS_WB_SIZE_RESERVED1_MASK                                                      ( \
        0x0000f000U)

#define DSS_WB_POSITION_POSY_SHIFT                                                      ( \
        16U)
#define DSS_WB_POSITION_POSY_MASK                                                       ( \
        0x0fff0000U)

#define DSS_WB_POSITION_POSX_SHIFT                                                      ( \
        0U)
#define DSS_WB_POSITION_POSX_MASK                                                       ( \
        0x00000fffU)

#define DSS_WB_POSITION_RESERVED_SHIFT                                                  ( \
        12U)
#define DSS_WB_POSITION_RESERVED_MASK                                                   ( \
        0x0000f000U)

#define DSS_WB_POSITION_RESERVED1_SHIFT                                                 ( \
        28U)
#define DSS_WB_POSITION_RESERVED1_MASK                                                  ( \
        0xf0000000U)

#define DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_SHIFT                                   ( \
        0U)
#define DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_MASK                                    ( \
        0x00000fffU)

#define DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_RESERVED_SHIFT                          ( \
        12U)
#define DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_RESERVED_MASK                           ( \
        0xfffff000U)

#ifdef __cplusplus
}
#endif
#endif  /* DSS_WB_HW_H_ */

