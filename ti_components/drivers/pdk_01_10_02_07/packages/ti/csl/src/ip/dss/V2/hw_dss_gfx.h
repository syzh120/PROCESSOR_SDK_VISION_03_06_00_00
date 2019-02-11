/*
 * DSS_GFX_HW.h
 *
 * Register-level header file for DSS_GFX
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

#ifndef DSS_GFX_HW_H_
#define DSS_GFX_HW_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
 * Register Definitions
 ****************************************************************************************************/

#define DSS_GFX_ATTRIBUTES                                          (0x0U)
#define DSS_GFX_ATTRIBUTES2                                         (0x4U)
#define DSS_GFX_BA(n)                                               (0x8U + \
                                                                     ((n) * 0x4U))
#define DSS_GFX_BUF_SIZE_STATUS                                     (0x10U)
#define DSS_GFX_BUF_THRESHOLD                                       (0x14U)
#define DSS_GFX_GLOBAL_ALPHA                                        (0x18U)
#define DSS_GFX_IRQENABLE                                           (0x1cU)
#define DSS_GFX_IRQSTATUS                                           (0x20U)
#define DSS_GFX_MFLAG_THRESHOLD                                     (0x24U)
#define DSS_GFX_PIXEL_INC                                           (0x28U)
#define DSS_GFX_POSITION                                            (0x2cU)
#define DSS_GFX_PRELOAD                                             (0x30U)
#define DSS_GFX_ROW_INC                                             (0x34U)
#define DSS_GFX_SIZE                                                (0x38U)
#define DSS_GFX_CLUT                                                (0x3cU)

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/

#define DSS_GFX_ATTRIBUTES_CHANNELOUT_SHIFT                                             ( \
        8U)
#define DSS_GFX_ATTRIBUTES_CHANNELOUT_MASK                                              ( \
        0x00000700U)
#define DSS_GFX_ATTRIBUTES_CHANNELOUT_VP1SEL                                             ( \
        0U)
#define DSS_GFX_ATTRIBUTES_CHANNELOUT_WBSEL                                              ( \
        4U)

#define DSS_GFX_ATTRIBUTES_ENABLE_SHIFT                                                 ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ENABLE_MASK                                                  ( \
        0x00000001U)
#define DSS_GFX_ATTRIBUTES_ENABLE_GRAPHICSDIS                                            ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ENABLE_GRAPHICSENB                                            ( \
        1U)

#define DSS_GFX_ATTRIBUTES_FORMAT_SHIFT                                                 ( \
        1U)
#define DSS_GFX_ATTRIBUTES_FORMAT_MASK                                                  ( \
        0x0000007eU)
#define DSS_GFX_ATTRIBUTES_FORMAT_BGRA32_8888                                            ( \
        10U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XRGB16_4444                                            ( \
        32U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGB16_565                                              ( \
        3U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XRGB32_8888                                            ( \
        39U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGB24P_888                                             ( \
        11U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ARGB16_4444                                            ( \
        0U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ARGB32_8888                                            ( \
        7U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBA32_8888                                            ( \
        9U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBX32_8888                                            ( \
        41U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ARGB16_1555                                            ( \
        5U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XRGB16_1555                                            ( \
        37U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBX16_4444                                            ( \
        34U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBA16_4444                                            ( \
        2U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BGRX32_8888                                            ( \
        42U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ABGR16_4444                                            ( \
        1U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XBGR16_4444                                            ( \
        33U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BGR16_565                                              ( \
        4U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ABGR16_1555                                            ( \
        6U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XBGR16_1555                                            ( \
        38U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ABGR32_8888                                            ( \
        8U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XBGR32_8888                                            ( \
        40U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ARGB32_2101010                                         ( \
        14U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XRGB32_2101010                                         ( \
        46U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ABGR32_2101010                                         ( \
        15U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XBGR32_2101010                                         ( \
        47U)
#define DSS_GFX_ATTRIBUTES_FORMAT_ARGB64_16161616                                        ( \
        16U)
#define DSS_GFX_ATTRIBUTES_FORMAT_XRGB64_16161616                                        ( \
        48U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBA64_16161616                                        ( \
        17U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RGBX64_16161616                                        ( \
        49U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RESERVED                                               ( \
        22U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RESERVED1                                              ( \
        35U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RESERVED2                                              ( \
        43U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RESERVED3                                              ( \
        50U)
#define DSS_GFX_ATTRIBUTES_FORMAT_RESERVED4                                              ( \
        12U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BITMAP1                                                ( \
        18U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BITMAP2                                                ( \
        19U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BITMAP4                                                ( \
        20U)
#define DSS_GFX_ATTRIBUTES_FORMAT_BITMAP8                                                ( \
        21U)

#define DSS_GFX_ATTRIBUTES_BUFPRELOAD_SHIFT                                             ( \
        11U)
#define DSS_GFX_ATTRIBUTES_BUFPRELOAD_MASK                                              ( \
        0x00000800U)
#define DSS_GFX_ATTRIBUTES_BUFPRELOAD_HIGHTHRES                                          ( \
        1U)
#define DSS_GFX_ATTRIBUTES_BUFPRELOAD_DEFVAL                                             ( \
        0U)

#define DSS_GFX_ATTRIBUTES_ARBITRATION_SHIFT                                            ( \
        14U)
#define DSS_GFX_ATTRIBUTES_ARBITRATION_MASK                                             ( \
        0x00004000U)
#define DSS_GFX_ATTRIBUTES_ARBITRATION_NORMALPRIO                                        ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ARBITRATION_HIGHPRIO                                          ( \
        1U)

#define DSS_GFX_ATTRIBUTES_SELFREFRESH_SHIFT                                            ( \
        15U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESH_MASK                                             ( \
        0x00008000U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESH_SELFREFRESHDIS                                    ( \
        0U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESH_SELFREFRESHENB                                    ( \
        1U)

#define DSS_GFX_ATTRIBUTES_ZORDER_SHIFT                                                 ( \
        25U)
#define DSS_GFX_ATTRIBUTES_ZORDER_MASK                                                  ( \
        0x0e000000U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER0                                                ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER1                                                ( \
        1U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER2                                                ( \
        2U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER3                                                ( \
        3U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER4                                                ( \
        4U)
#define DSS_GFX_ATTRIBUTES_ZORDER_ZORDER5                                                ( \
        5U)

#define DSS_GFX_ATTRIBUTES_PREMULTIPLYALPHA_SHIFT                                       ( \
        28U)
#define DSS_GFX_ATTRIBUTES_PREMULTIPLYALPHA_MASK                                        ( \
        0x10000000U)
#define DSS_GFX_ATTRIBUTES_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA                        ( \
        0U)
#define DSS_GFX_ATTRIBUTES_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA                           ( \
        1U)

#define DSS_GFX_ATTRIBUTES_ANTIFLICKER_SHIFT                                            ( \
        24U)
#define DSS_GFX_ATTRIBUTES_ANTIFLICKER_MASK                                             ( \
        0x01000000U)
#define DSS_GFX_ATTRIBUTES_ANTIFLICKER_AFDIS                                             ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ANTIFLICKER_AFENB                                             ( \
        1U)

#define DSS_GFX_ATTRIBUTES_SELFREFRESHAUTO_SHIFT                                        ( \
        17U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESHAUTO_MASK                                         ( \
        0x00020000U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTODIS                            ( \
        0U)
#define DSS_GFX_ATTRIBUTES_SELFREFRESHAUTO_SELFREFRESHAUTOEN                             ( \
        1U)

#define DSS_GFX_ATTRIBUTES_RESERVED2_SHIFT                                              ( \
        30U)
#define DSS_GFX_ATTRIBUTES_RESERVED2_MASK                                               ( \
        0x40000000U)

#define DSS_GFX_ATTRIBUTES_RESERVED_SHIFT                                               ( \
        19U)
#define DSS_GFX_ATTRIBUTES_RESERVED_MASK                                                ( \
        0x00f80000U)

#define DSS_GFX_ATTRIBUTES_RESERVED3_SHIFT                                              ( \
        18U)
#define DSS_GFX_ATTRIBUTES_RESERVED3_MASK                                               ( \
        0x00040000U)

#define DSS_GFX_ATTRIBUTES_RESERVED4_SHIFT                                              ( \
        31U)
#define DSS_GFX_ATTRIBUTES_RESERVED4_MASK                                               ( \
        0x80000000U)

#define DSS_GFX_ATTRIBUTES_RESERVED_ROT_SHIFT                                           ( \
        12U)
#define DSS_GFX_ATTRIBUTES_RESERVED_ROT_MASK                                            ( \
        0x00001000U)

#define DSS_GFX_ATTRIBUTES_RESERVED_FTD_SHIFT                                           ( \
        16U)
#define DSS_GFX_ATTRIBUTES_RESERVED_FTD_MASK                                            ( \
        0x00010000U)

#define DSS_GFX_ATTRIBUTES_RESERVED_BT_SHIFT                                            ( \
        29U)
#define DSS_GFX_ATTRIBUTES_RESERVED_BT_MASK                                             ( \
        0x20000000U)

#define DSS_GFX_ATTRIBUTES_BURSTTYPE_SHIFT                                              ( \
        29U)
#define DSS_GFX_ATTRIBUTES_BURSTTYPE_MASK                                               ( \
        0x20000000U)
#define DSS_GFX_ATTRIBUTES_BURSTTYPE_INC                                                 ( \
        0U)
#define DSS_GFX_ATTRIBUTES_BURSTTYPE_BLCK                                                ( \
        1U)

#define DSS_GFX_ATTRIBUTES_FORCE1DTILEDMODE_SHIFT                                       ( \
        16U)
#define DSS_GFX_ATTRIBUTES_FORCE1DTILEDMODE_MASK                                        ( \
        0x00010000U)
#define DSS_GFX_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS                         ( \
        0U)
#define DSS_GFX_ATTRIBUTES_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS                         ( \
        1U)

#define DSS_GFX_ATTRIBUTES_ROTATION_SHIFT                                               ( \
        12U)
#define DSS_GFX_ATTRIBUTES_ROTATION_MASK                                                ( \
        0x00001000U)
#define DSS_GFX_ATTRIBUTES_ROTATION_NOROT                                                ( \
        0U)
#define DSS_GFX_ATTRIBUTES_ROTATION_ROT90                                                ( \
        1U)
#define DSS_GFX_ATTRIBUTES_ROTATION_ROT180                                               ( \
        2U)
#define DSS_GFX_ATTRIBUTES_ROTATION_ROT270                                               ( \
        3U)

#define DSS_GFX_ATTRIBUTES_NIBBLEMODE_SHIFT                                             ( \
        7U)
#define DSS_GFX_ATTRIBUTES_NIBBLEMODE_MASK                                              ( \
        0x00000080U)
#define DSS_GFX_ATTRIBUTES_NIBBLEMODE_NIBBLEMODEDIS                                      ( \
        0U)
#define DSS_GFX_ATTRIBUTES_NIBBLEMODE_NIBBLEMODEEN                                       ( \
        1U)

#define DSS_GFX_ATTRIBUTES2_SECURE_SHIFT                                                ( \
        16U)
#define DSS_GFX_ATTRIBUTES2_SECURE_MASK                                                 ( \
        0x00010000U)

#define DSS_GFX_ATTRIBUTES2_RESERVED2_SHIFT                                             ( \
        17U)
#define DSS_GFX_ATTRIBUTES2_RESERVED2_MASK                                              ( \
        0x00fe0000U)

#define DSS_GFX_ATTRIBUTES2_TAGS_SHIFT                                                  ( \
        26U)
#define DSS_GFX_ATTRIBUTES2_TAGS_MASK                                                   ( \
        0x7c000000U)

#define DSS_GFX_ATTRIBUTES2_RESERVED_SHIFT                                              ( \
        0U)
#define DSS_GFX_ATTRIBUTES2_RESERVED_MASK                                               ( \
        0x0000ffffU)

#define DSS_GFX_ATTRIBUTES2_REGION_BASED_SHIFT                                          ( \
        24U)
#define DSS_GFX_ATTRIBUTES2_REGION_BASED_MASK                                           ( \
        0x01000000U)
#define DSS_GFX_ATTRIBUTES2_REGION_BASED_DISABLE                                         ( \
        0U)
#define DSS_GFX_ATTRIBUTES2_REGION_BASED_ENABLE                                          ( \
        1U)

#define DSS_GFX_ATTRIBUTES2_RESERVED1_SHIFT                                             ( \
        25U)
#define DSS_GFX_ATTRIBUTES2_RESERVED1_MASK                                              ( \
        0x02000000U)

#define DSS_GFX_ATTRIBUTES2_RESERVED3_SHIFT                                             ( \
        31U)
#define DSS_GFX_ATTRIBUTES2_RESERVED3_MASK                                              ( \
        0x80000000U)

#define DSS_GFX_BA_SHIFT                                                                ( \
        0U)
#define DSS_GFX_BA_MASK                                                                 ( \
        0xffffffffU)

#define DSS_GFX_BUF_SIZE_STATUS_RESERVED_19_SHIFT                                       ( \
        16U)
#define DSS_GFX_BUF_SIZE_STATUS_RESERVED_19_MASK                                        ( \
        0xffff0000U)

#define DSS_GFX_BUF_SIZE_STATUS_BUFSIZE_SHIFT                                           ( \
        0U)
#define DSS_GFX_BUF_SIZE_STATUS_BUFSIZE_MASK                                            ( \
        0x0000ffffU)

#define DSS_GFX_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT                                     ( \
        0U)
#define DSS_GFX_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK                                      ( \
        0x0000ffffU)

#define DSS_GFX_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT                                    ( \
        16U)
#define DSS_GFX_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK                                     ( \
        0xffff0000U)

#define DSS_GFX_GLOBAL_ALPHA_GLOBALALPHA_SHIFT                                          ( \
        0U)
#define DSS_GFX_GLOBAL_ALPHA_GLOBALALPHA_MASK                                           ( \
        0x000000ffU)

#define DSS_GFX_GLOBAL_ALPHA_RESERVED_SHIFT                                             ( \
        8U)
#define DSS_GFX_GLOBAL_ALPHA_RESERVED_MASK                                              ( \
        0xffffff00U)

#define DSS_GFX_IRQENABLE_GFXENDWINDOW_EN_SHIFT                                         ( \
        1U)
#define DSS_GFX_IRQENABLE_GFXENDWINDOW_EN_MASK                                          ( \
        0x00000002U)
#define DSS_GFX_IRQENABLE_GFXENDWINDOW_EN_MASKED                                         ( \
        0U)
#define DSS_GFX_IRQENABLE_GFXENDWINDOW_EN_GENINT                                         ( \
        1U)

#define DSS_GFX_IRQENABLE_GFXBUFFERUNDERFLOW_EN_SHIFT                                   ( \
        0U)
#define DSS_GFX_IRQENABLE_GFXBUFFERUNDERFLOW_EN_MASK                                    ( \
        0x00000001U)
#define DSS_GFX_IRQENABLE_GFXBUFFERUNDERFLOW_EN_MASKED                                   ( \
        0U)
#define DSS_GFX_IRQENABLE_GFXBUFFERUNDERFLOW_EN_GENINT                                   ( \
        1U)

#define DSS_GFX_IRQENABLE_RESERVED_SHIFT                                                ( \
        4U)
#define DSS_GFX_IRQENABLE_RESERVED_MASK                                                 ( \
        0xfffffff0U)

#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPESTART_EN_SHIFT                              ( \
        2U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPESTART_EN_MASK                               ( \
        0x00000004U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPESTART_EN_MASKED                              ( \
        0U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPESTART_EN_GENINT                              ( \
        1U)

#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPEEND_EN_SHIFT                                ( \
        3U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPEEND_EN_MASK                                 ( \
        0x00000008U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPEEND_EN_MASKED                                ( \
        0U)
#define DSS_GFX_IRQENABLE_GFXREGIONBASEDPIPEEND_EN_GENINT                                ( \
        1U)

#define DSS_GFX_IRQSTATUS_GFXENDWINDOW_IRQ_SHIFT                                        ( \
        1U)
#define DSS_GFX_IRQSTATUS_GFXENDWINDOW_IRQ_MASK                                         ( \
        0x00000002U)
#define DSS_GFX_IRQSTATUS_GFXENDWINDOW_IRQ_FALSE                                         ( \
        0U)
#define DSS_GFX_IRQSTATUS_GFXENDWINDOW_IRQ_TRUE                                          ( \
        1U)

#define DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_SHIFT                                  ( \
        0U)
#define DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_MASK                                   ( \
        0x00000001U)
#define DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_FALSE                                   ( \
        0U)
#define DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_TRUE                                    ( \
        1U)

#define DSS_GFX_IRQSTATUS_RESERVED_SHIFT                                                ( \
        4U)
#define DSS_GFX_IRQSTATUS_RESERVED_MASK                                                 ( \
        0xfffffff0U)

#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPESTART_IRQ_SHIFT                             ( \
        2U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPESTART_IRQ_MASK                              ( \
        0x00000004U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPESTART_IRQ_FALSE                              ( \
        0U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPESTART_IRQ_TRUE                               ( \
        1U)

#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPEEND_IRQ_SHIFT                               ( \
        3U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPEEND_IRQ_MASK                                ( \
        0x00000008U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPEEND_IRQ_FALSE                                ( \
        0U)
#define DSS_GFX_IRQSTATUS_GFXREGIONBASEDPIPEEND_IRQ_TRUE                                 ( \
        1U)

#define DSS_GFX_MFLAG_THRESHOLD_LT_SHIFT                                                ( \
        0U)
#define DSS_GFX_MFLAG_THRESHOLD_LT_MASK                                                 ( \
        0x0000ffffU)

#define DSS_GFX_MFLAG_THRESHOLD_HT_SHIFT                                                ( \
        16U)
#define DSS_GFX_MFLAG_THRESHOLD_HT_MASK                                                 ( \
        0xffff0000U)

#define DSS_GFX_PIXEL_INC_RESERVED_22_SHIFT                                             ( \
        8U)
#define DSS_GFX_PIXEL_INC_RESERVED_22_MASK                                              ( \
        0xffffff00U)

#define DSS_GFX_PIXEL_INC_PIXELINC_SHIFT                                                ( \
        0U)
#define DSS_GFX_PIXEL_INC_PIXELINC_MASK                                                 ( \
        0x000000ffU)

#define DSS_GFX_POSITION_POSX_SHIFT                                                     ( \
        0U)
#define DSS_GFX_POSITION_POSX_MASK                                                      ( \
        0x00000fffU)

#define DSS_GFX_POSITION_POSY_SHIFT                                                     ( \
        16U)
#define DSS_GFX_POSITION_POSY_MASK                                                      ( \
        0x0fff0000U)

#define DSS_GFX_POSITION_RESERVED_SHIFT                                                 ( \
        12U)
#define DSS_GFX_POSITION_RESERVED_MASK                                                  ( \
        0x0000f000U)

#define DSS_GFX_POSITION_RESERVED1_SHIFT                                                ( \
        28U)
#define DSS_GFX_POSITION_RESERVED1_MASK                                                 ( \
        0xf0000000U)

#define DSS_GFX_PRELOAD_RESERVED_211_SHIFT                                              ( \
        12U)
#define DSS_GFX_PRELOAD_RESERVED_211_MASK                                               ( \
        0xfffff000U)

#define DSS_GFX_PRELOAD_SHIFT                                                           ( \
        0U)
#define DSS_GFX_PRELOAD_MASK                                                            ( \
        0x00000fffU)

#define DSS_GFX_ROW_INC_ROWINC_SHIFT                                                    ( \
        0U)
#define DSS_GFX_ROW_INC_ROWINC_MASK                                                     ( \
        0xffffffffU)

#define DSS_GFX_SIZE_SIZEY_SHIFT                                                        ( \
        16U)
#define DSS_GFX_SIZE_SIZEY_MASK                                                         ( \
        0x0fff0000U)

#define DSS_GFX_SIZE_SIZEX_SHIFT                                                        ( \
        0U)
#define DSS_GFX_SIZE_SIZEX_MASK                                                         ( \
        0x00000fffU)

#define DSS_GFX_SIZE_RESERVED_SHIFT                                                     ( \
        28U)
#define DSS_GFX_SIZE_RESERVED_MASK                                                      ( \
        0xf0000000U)

#define DSS_GFX_SIZE_RESERVED1_SHIFT                                                    ( \
        12U)
#define DSS_GFX_SIZE_RESERVED1_MASK                                                     ( \
        0x0000f000U)

#define DSS_GFX_CLUT_VALUE_R_SHIFT                                                      ( \
        16U)
#define DSS_GFX_CLUT_VALUE_R_MASK                                                       ( \
        0x00ff0000U)

#define DSS_GFX_CLUT_INDEX_SHIFT                                                        ( \
        24U)
#define DSS_GFX_CLUT_INDEX_MASK                                                         ( \
        0xff000000U)

#define DSS_GFX_CLUT_VALUE_G_SHIFT                                                      ( \
        8U)
#define DSS_GFX_CLUT_VALUE_G_MASK                                                       ( \
        0x0000ff00U)

#define DSS_GFX_CLUT_VALUE_B_SHIFT                                                      ( \
        0U)
#define DSS_GFX_CLUT_VALUE_B_MASK                                                       ( \
        0x000000ffU)

#ifdef __cplusplus
}
#endif
#endif  /* DSS_GFX_HW_H_ */

