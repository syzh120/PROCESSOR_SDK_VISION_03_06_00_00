/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2015
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
 *  \file       hw_vpdma.h
 *
 *  \brief      register-level header file for VPDMA
 *
**/

#ifndef HW_VPDMA_H_
#define HW_VPDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define VPDMA_PID                                                                                           (0x0U)
#define VPDMA_LIST_ADDR                                                                                     (0x4U)
#define VPDMA_LIST_ATTR                                                                                     (0x8U)
#define VPDMA_LIST_STAT_SYNC                                                                                (0xcU)
#define VPDMA_BG_RGB                                                                                        (0x18U)
#define VPDMA_BG_YUV                                                                                        (0x1cU)
#define VPDMA_SETUP                                                                                         (0x30U)
#define VPDMA_MAX_SIZE1                                                                                     (0x34U)
#define VPDMA_MAX_SIZE2                                                                                     (0x38U)
#define VPDMA_MAX_SIZE3                                                                                     (0x3cU)
#define VPDMA_INT0_CHANNEL0_INT_STAT                                                                        (0x40U)
#define VPDMA_INT0_CHANNEL0_INT_MASK                                                                        (0x44U)
#define VPDMA_INT0_CHANNEL1_INT_STAT                                                                        (0x48U)
#define VPDMA_INT0_CHANNEL1_INT_MASK                                                                        (0x4cU)
#define VPDMA_INT0_CHANNEL2_INT_STAT                                                                        (0x50U)
#define VPDMA_INT0_CHANNEL2_INT_MASK                                                                        (0x54U)
#define VPDMA_INT0_CHANNEL3_INT_STAT                                                                        (0x58U)
#define VPDMA_INT0_CHANNEL3_INT_MASK                                                                        (0x5cU)
#define VPDMA_INT0_CHANNEL4_INT_STAT                                                                        (0x60U)
#define VPDMA_INT0_CHANNEL4_INT_MASK                                                                        (0x64U)
#define VPDMA_INT0_CHANNEL5_INT_STAT                                                                        (0x68U)
#define VPDMA_INT0_CHANNEL5_INT_MASK                                                                        (0x6cU)
#define VPDMA_INT0_CLIENT0_INT_STAT                                                                         (0x78U)
#define VPDMA_INT0_CLIENT0_INT_MASK                                                                         (0x7cU)
#define VPDMA_INT0_LIST0_INT_STAT                                                                           (0x88U)
#define VPDMA_INT0_LIST0_INT_MASK                                                                           (0x8cU)
#define VPDMA_INT1_CHANNEL0_INT_STAT                                                                        (0x90U)
#define VPDMA_INT1_CHANNEL0_INT_MASK                                                                        (0x94U)
#define VPDMA_INT1_CHANNEL1_INT_STAT                                                                        (0x98U)
#define VPDMA_INT1_CHANNEL1_INT_MASK                                                                        (0x9cU)
#define VPDMA_INT1_CHANNEL2_INT_STAT                                                                        (0xa0U)
#define VPDMA_INT1_CHANNEL2_INT_MASK                                                                        (0xa4U)
#define VPDMA_INT1_CHANNEL3_INT_STAT                                                                        (0xa8U)
#define VPDMA_INT1_CHANNEL3_INT_MASK                                                                        (0xacU)
#define VPDMA_INT1_CHANNEL4_INT_STAT                                                                        (0xb0U)
#define VPDMA_INT1_CHANNEL4_INT_MASK                                                                        (0xb4U)
#define VPDMA_INT1_CHANNEL5_INT_STAT                                                                        (0xb8U)
#define VPDMA_INT1_CHANNEL5_INT_MASK                                                                        (0xbcU)
#define VPDMA_INT1_CLIENT0_INT_STAT                                                                         (0xc8U)
#define VPDMA_INT1_CLIENT0_INT_MASK                                                                         (0xccU)
#define VPDMA_INT1_LIST0_INT_STAT                                                                           (0xd8U)
#define VPDMA_INT1_LIST0_INT_MASK                                                                           (0xdcU)
#define VPDMA_INT2_CHANNEL0_INT_STAT                                                                        (0xe0U)
#define VPDMA_INT2_CHANNEL0_INT_MASK                                                                        (0xe4U)
#define VPDMA_INT2_CHANNEL1_INT_STAT                                                                        (0xe8U)
#define VPDMA_INT2_CHANNEL1_INT_MASK                                                                        (0xecU)
#define VPDMA_INT2_CHANNEL2_INT_STAT                                                                        (0xf0U)
#define VPDMA_INT2_CHANNEL2_INT_MASK                                                                        (0xf4U)
#define VPDMA_INT2_CHANNEL3_INT_STAT                                                                        (0xf8U)
#define VPDMA_INT2_CHANNEL3_INT_MASK                                                                        (0xfcU)
#define VPDMA_INT2_CHANNEL4_INT_STAT                                                                        (0x100U)
#define VPDMA_INT2_CHANNEL4_INT_MASK                                                                        (0x104U)
#define VPDMA_INT2_CHANNEL5_INT_STAT                                                                        (0x108U)
#define VPDMA_INT2_CHANNEL5_INT_MASK                                                                        (0x10cU)
#define VPDMA_INT2_CLIENT0_INT_STAT                                                                         (0x118U)
#define VPDMA_INT2_CLIENT0_INT_MASK                                                                         (0x11cU)
#define VPDMA_INT2_LIST0_INT_STAT                                                                           (0x128U)
#define VPDMA_INT2_LIST0_INT_MASK                                                                           (0x12cU)
#define VPDMA_INT3_CHANNEL0_INT_STAT                                                                        (0x130U)
#define VPDMA_INT3_CHANNEL0_INT_MASK                                                                        (0x134U)
#define VPDMA_INT3_CHANNEL1_INT_STAT                                                                        (0x138U)
#define VPDMA_INT3_CHANNEL1_INT_MASK                                                                        (0x13cU)
#define VPDMA_INT3_CHANNEL2_INT_STAT                                                                        (0x140U)
#define VPDMA_INT3_CHANNEL2_INT_MASK                                                                        (0x144U)
#define VPDMA_INT3_CHANNEL3_INT_STAT                                                                        (0x148U)
#define VPDMA_INT3_CHANNEL3_INT_MASK                                                                        (0x14cU)
#define VPDMA_INT3_CHANNEL4_INT_STAT                                                                        (0x150U)
#define VPDMA_INT3_CHANNEL4_INT_MASK                                                                        (0x154U)
#define VPDMA_INT3_CHANNEL5_INT_STAT                                                                        (0x158U)
#define VPDMA_INT3_CHANNEL5_INT_MASK                                                                        (0x15cU)
#define VPDMA_INT3_CLIENT0_INT_STAT                                                                         (0x168U)
#define VPDMA_INT3_CLIENT0_INT_MASK                                                                         (0x16cU)
#define VPDMA_INT3_LIST0_INT_STAT                                                                           (0x178U)
#define VPDMA_INT3_LIST0_INT_MASK                                                                           (0x17cU)
#define VPDMA_PERF_MON0                                                                                     (0x200U)
#define VPDMA_PERF_MON1                                                                                     (0x204U)
#define VPDMA_PERF_MON2                                                                                     (0x208U)
#define VPDMA_PERF_MON3                                                                                     (0x20cU)
#define VPDMA_PERF_MON4                                                                                     (0x210U)
#define VPDMA_PERF_MON5                                                                                     (0x214U)
#define VPDMA_PERF_MON6                                                                                     (0x218U)
#define VPDMA_PERF_MON7                                                                                     (0x21cU)
#define VPDMA_PERF_MON8                                                                                     (0x220U)
#define VPDMA_PERF_MON9                                                                                     (0x224U)
#define VPDMA_PERF_MON10                                                                                    (0x228U)
#define VPDMA_PERF_MON11                                                                                    (0x22cU)
#define VPDMA_PERF_MON12                                                                                    (0x230U)
#define VPDMA_PERF_MON13                                                                                    (0x234U)
#define VPDMA_PERF_MON14                                                                                    (0x238U)
#define VPDMA_PERF_MON15                                                                                    (0x23cU)
#define VPDMA_PERF_MON16                                                                                    (0x240U)
#define VPDMA_PERF_MON17                                                                                    (0x244U)
#define VPDMA_PERF_MON18                                                                                    (0x248U)
#define VPDMA_PERF_MON19                                                                                    (0x24cU)
#define VPDMA_PERF_MON20                                                                                    (0x250U)
#define VPDMA_PERF_MON21                                                                                    (0x254U)
#define VPDMA_PERF_MON22                                                                                    (0x258U)
#define VPDMA_PERF_MON23                                                                                    (0x25cU)
#define VPDMA_PERF_MON24                                                                                    (0x260U)
#define VPDMA_PERF_MON25                                                                                    (0x264U)
#define VPDMA_PERF_MON26                                                                                    (0x268U)
#define VPDMA_PERF_MON27                                                                                    (0x26cU)
#define VPDMA_PERF_MON28                                                                                    (0x270U)
#define VPDMA_PERF_MON29                                                                                    (0x274U)
#define VPDMA_PERF_MON30                                                                                    (0x278U)
#define VPDMA_PERF_MON31                                                                                    (0x27cU)
#define VPDMA_PERF_MON32                                                                                    (0x280U)
#define VPDMA_PERF_MON33                                                                                    (0x284U)
#define VPDMA_PERF_MON34                                                                                    (0x288U)
#define VPDMA_PERF_MON35                                                                                    (0x28cU)
#define VPDMA_PERF_MON36                                                                                    (0x290U)
#define VPDMA_PERF_MON37                                                                                    (0x294U)
#define VPDMA_PERF_MON38                                                                                    (0x298U)
#define VPDMA_PERF_MON39                                                                                    (0x29cU)
#define VPDMA_PERF_MON40                                                                                    (0x2a0U)
#define VPDMA_PERF_MON41                                                                                    (0x2a4U)
#define VPDMA_PERF_MON42                                                                                    (0x2a8U)
#define VPDMA_PERF_MON43                                                                                    (0x2acU)
#define VPDMA_PERF_MON44                                                                                    (0x2b0U)
#define VPDMA_PERF_MON45                                                                                    (0x2b4U)
#define VPDMA_PERF_MON46                                                                                    (0x2b8U)
#define VPDMA_PERF_MON47                                                                                    (0x2bcU)
#define VPDMA_PERF_MON48                                                                                    (0x2c0U)
#define VPDMA_PERF_MON49                                                                                    (0x2c4U)
#define VPDMA_PERF_MON50                                                                                    (0x2c8U)
#define VPDMA_PERF_MON51                                                                                    (0x2ccU)
#define VPDMA_PERF_MON52                                                                                    (0x2d0U)
#define VPDMA_PERF_MON53                                                                                    (0x2d4U)
#define VPDMA_PERF_MON54                                                                                    (0x2d8U)
#define VPDMA_PERF_MON55                                                                                    (0x2dcU)
#define VPDMA_PERF_MON56                                                                                    (0x2e0U)
#define VPDMA_PERF_MON57                                                                                    (0x2e4U)
#define VPDMA_PERF_MON58                                                                                    (0x2e8U)
#define VPDMA_PERF_MON59                                                                                    (0x2ecU)
#define VPDMA_PERF_MON60                                                                                    (0x2f0U)
#define VPDMA_PERF_MON61                                                                                    (0x2f4U)
#define VPDMA_PRI_CHROMA_CSTAT                                                                              (0x300U)
#define VPDMA_PRI_LUMA_CSTAT                                                                                (0x304U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT                                                                           (0x308U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT                                                                         (0x30cU)
#define VPDMA_PRI_FLD2_LUMA_CSTAT                                                                           (0x310U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT                                                                         (0x314U)
#define VPDMA_PRI_MV0_CSTAT                                                                                 (0x330U)
#define VPDMA_PRI_MV_OUT_CSTAT                                                                              (0x33cU)
#define VPDMA_WB0_CSTAT                                                                                     (0x344U)
#define VPDMA_BP0_CSTAT                                                                                     (0x348U)
#define VPDMA_AUX_CHROMA_CSTAT                                                                              (0x34cU)
#define VPDMA_AUX_LUMA_CSTAT                                                                                (0x350U)
#define VPDMA_WB1_CSTAT                                                                                     (0x374U)
#define VPDMA_BP1_CSTAT                                                                                     (0x378U)
#define VPDMA_GRPX0_DATA_CSTAT                                                                              (0x37cU)
#define VPDMA_GRPX1_DATA_CSTAT                                                                              (0x380U)
#define VPDMA_GRPX2_DATA_CSTAT                                                                              (0x384U)
#define VPDMA_S0_LO_Y_CSTAT                                                                                 (0x388U)
#define VPDMA_S0_LO_UV_CSTAT                                                                                (0x38cU)
#define VPDMA_S0_UP_Y_CSTAT                                                                                 (0x390U)
#define VPDMA_S0_UP_UV_CSTAT                                                                                (0x394U)
#define VPDMA_S1_LO_Y_CSTAT                                                                                 (0x398U)
#define VPDMA_S1_LO_UV_CSTAT                                                                                (0x39cU)
#define VPDMA_S1_UP_Y_CSTAT                                                                                 (0x3a0U)
#define VPDMA_S1_UP_UV_CSTAT                                                                                (0x3a4U)
#define VPDMA_STENCIL0_CSTAT                                                                                (0x3a8U)
#define VPDMA_STENCIL1_CSTAT                                                                                (0x3acU)
#define VPDMA_STENCIL2_CSTAT                                                                                (0x3b0U)
#define VPDMA_NF_RD_CSTAT                                                                                   (0x3b4U)
#define VPDMA_NF_PREV_LUMA_CSTAT                                                                            (0x3b8U)
#define VPDMA_NF_PREV_CHROMA_CSTAT                                                                          (0x3bcU)
#define VPDMA_NF_WR_LUMA_CSTAT                                                                              (0x3c0U)
#define VPDMA_NF_WR_CHROMA_CSTAT                                                                            (0x3c4U)
#define VPDMA_VBI_SDVENC_CSTAT                                                                              (0x3ccU)
#define VPDMA_VPI_CTL_CSTAT                                                                                 (0x3d0U)
#define VPDMA_WB2_CSTAT                                                                                     (0x3d4U)
#define VPDMA_SEC0_CHROMA_CSTAT                                                                             (0x3d8U)
#define VPDMA_SEC0_LUMA_CSTAT                                                                               (0x3dcU)
#define VPDMA_SEC1_CHROMA_CSTAT                                                                             (0x3e0U)
#define VPDMA_SEC1_LUMA_CSTAT                                                                               (0x3e4U)
#define VPDMA_S0_ANC_A_CSTAT                                                                                (0x3e8U)
#define VPDMA_S0_ANC_B_CSTAT                                                                                (0x3ecU)
#define VPDMA_S1_ANC_A_CSTAT                                                                                (0x3f0U)
#define VPDMA_S1_ANC_B_CSTAT                                                                                (0x3f4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define VPDMA_PID_FUNC_SHIFT                                                                                (16U)
#define VPDMA_PID_FUNC_MASK                                                                                 (0x3fff0000U)

#define VPDMA_PID_MAJOR_SHIFT                                                                               (8U)
#define VPDMA_PID_MAJOR_MASK                                                                                (0x00000700U)

#define VPDMA_PID_MINOR_SHIFT                                                                               (0U)
#define VPDMA_PID_MINOR_MASK                                                                                (0x0000003fU)

#define VPDMA_PID_RTL_SHIFT                                                                                 (11U)
#define VPDMA_PID_RTL_MASK                                                                                  (0x0000f800U)

#define VPDMA_PID_SCHEME_SHIFT                                                                              (30U)
#define VPDMA_PID_SCHEME_MASK                                                                               (0xc0000000U)

#define VPDMA_PID_VPDMA_ACCESS_TYPE_SHIFT                                                                   (6U)
#define VPDMA_PID_VPDMA_ACCESS_TYPE_MASK                                                                    (0x00000040U)

#define VPDMA_PID_VPDMA_LOAD_COMPLETE_SHIFT                                                                 (7U)
#define VPDMA_PID_VPDMA_LOAD_COMPLETE_MASK                                                                  (0x00000080U)

#define VPDMA_LIST_ADDR_LIST_ADDR_SHIFT                                                                     (0U)
#define VPDMA_LIST_ADDR_LIST_ADDR_MASK                                                                      (0xffffffffU)

#define VPDMA_LIST_ATTR_LIST_NUM_SHIFT                                                                      (24U)
#define VPDMA_LIST_ATTR_LIST_NUM_MASK                                                                       (0x07000000U)

#define VPDMA_LIST_ATTR_LIST_SIZE_SHIFT                                                                     (0U)
#define VPDMA_LIST_ATTR_LIST_SIZE_MASK                                                                      (0x0000ffffU)

#define VPDMA_LIST_ATTR_LIST_TYPE_SHIFT                                                                     (16U)
#define VPDMA_LIST_ATTR_LIST_TYPE_MASK                                                                      (0x00070000U)

#define VPDMA_LIST_ATTR_RDY_SHIFT                                                                           (19U)
#define VPDMA_LIST_ATTR_RDY_MASK                                                                            (0x00080000U)

#define VPDMA_LIST_ATTR_STOP_SHIFT                                                                          (20U)
#define VPDMA_LIST_ATTR_STOP_MASK                                                                           (0x00100000U)

#define VPDMA_LIST_STAT_SYNC_LIST0_BUSY_SHIFT                                                               (16U)
#define VPDMA_LIST_STAT_SYNC_LIST0_BUSY_MASK                                                                (0x00010000U)

#define VPDMA_LIST_STAT_SYNC_LIST1_BUSY_SHIFT                                                               (17U)
#define VPDMA_LIST_STAT_SYNC_LIST1_BUSY_MASK                                                                (0x00020000U)

#define VPDMA_LIST_STAT_SYNC_LIST2_BUSY_SHIFT                                                               (18U)
#define VPDMA_LIST_STAT_SYNC_LIST2_BUSY_MASK                                                                (0x00040000U)

#define VPDMA_LIST_STAT_SYNC_LIST3_BUSY_SHIFT                                                               (19U)
#define VPDMA_LIST_STAT_SYNC_LIST3_BUSY_MASK                                                                (0x00080000U)

#define VPDMA_LIST_STAT_SYNC_LIST4_BUSY_SHIFT                                                               (20U)
#define VPDMA_LIST_STAT_SYNC_LIST4_BUSY_MASK                                                                (0x00100000U)

#define VPDMA_LIST_STAT_SYNC_LIST5_BUSY_SHIFT                                                               (21U)
#define VPDMA_LIST_STAT_SYNC_LIST5_BUSY_MASK                                                                (0x00200000U)

#define VPDMA_LIST_STAT_SYNC_LIST6_BUSY_SHIFT                                                               (22U)
#define VPDMA_LIST_STAT_SYNC_LIST6_BUSY_MASK                                                                (0x00400000U)

#define VPDMA_LIST_STAT_SYNC_LIST7_BUSY_SHIFT                                                               (23U)
#define VPDMA_LIST_STAT_SYNC_LIST7_BUSY_MASK                                                                (0x00800000U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_SHIFT                                                              (0U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_MASK                                                               (0x00000001U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_SHIFT                                                              (1U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_MASK                                                               (0x00000002U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_SHIFT                                                              (2U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_MASK                                                               (0x00000004U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_SHIFT                                                              (3U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_MASK                                                               (0x00000008U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_SHIFT                                                              (4U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_MASK                                                               (0x00000010U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_SHIFT                                                              (5U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_MASK                                                               (0x00000020U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_SHIFT                                                              (6U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_MASK                                                               (0x00000040U)

#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_SHIFT                                                              (7U)
#define VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_MASK                                                               (0x00000080U)

#define VPDMA_BG_RGB_BLEND_SHIFT                                                                            (0U)
#define VPDMA_BG_RGB_BLEND_MASK                                                                             (0x000000ffU)

#define VPDMA_BG_RGB_BLUE_SHIFT                                                                             (8U)
#define VPDMA_BG_RGB_BLUE_MASK                                                                              (0x0000ff00U)

#define VPDMA_BG_RGB_GREEN_SHIFT                                                                            (16U)
#define VPDMA_BG_RGB_GREEN_MASK                                                                             (0x00ff0000U)

#define VPDMA_BG_RGB_RED_SHIFT                                                                              (24U)
#define VPDMA_BG_RGB_RED_MASK                                                                               (0xff000000U)

#define VPDMA_BG_YUV_CB_SHIFT                                                                               (0U)
#define VPDMA_BG_YUV_CB_MASK                                                                                (0x000000ffU)

#define VPDMA_BG_YUV_CR_SHIFT                                                                               (8U)
#define VPDMA_BG_YUV_CR_MASK                                                                                (0x0000ff00U)

#define VPDMA_BG_YUV_Y_SHIFT                                                                                (16U)
#define VPDMA_BG_YUV_Y_MASK                                                                                 (0x00ff0000U)

#define VPDMA_SETUP_SEC_BASE_CH_SHIFT                                                                       (0U)
#define VPDMA_SETUP_SEC_BASE_CH_MASK                                                                        (0x00000001U)

#define VPDMA_MAX_SIZE1_MAX_HEIGHT_SHIFT                                                                    (0U)
#define VPDMA_MAX_SIZE1_MAX_HEIGHT_MASK                                                                     (0x0000ffffU)

#define VPDMA_MAX_SIZE1_MAX_WIDTH_SHIFT                                                                     (16U)
#define VPDMA_MAX_SIZE1_MAX_WIDTH_MASK                                                                      (0xffff0000U)

#define VPDMA_MAX_SIZE2_MAX_HEIGHT_SHIFT                                                                    (0U)
#define VPDMA_MAX_SIZE2_MAX_HEIGHT_MASK                                                                     (0x0000ffffU)

#define VPDMA_MAX_SIZE2_MAX_WIDTH_SHIFT                                                                     (16U)
#define VPDMA_MAX_SIZE2_MAX_WIDTH_MASK                                                                      (0xffff0000U)

#define VPDMA_MAX_SIZE3_MAX_HEIGHT_SHIFT                                                                    (0U)
#define VPDMA_MAX_SIZE3_MAX_HEIGHT_MASK                                                                     (0x0000ffffU)

#define VPDMA_MAX_SIZE3_MAX_WIDTH_SHIFT                                                                     (16U)
#define VPDMA_MAX_SIZE3_MAX_WIDTH_MASK                                                                      (0xffff0000U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT0_CHANNEL0_INT_STAT_PRI_FLD2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT0_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT0_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT0_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT0_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT0_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT0_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT0_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT0_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT0_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT0_CHANNEL5_INT_STAT_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT0_CHANNEL5_INT_MASK_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT0_CLIENT0_INT_STAT_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT0_CLIENT0_INT_MASK_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT0_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT0_LIST0_INT_STAT_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT0_LIST0_INT_STAT_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT0_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT0_LIST0_INT_MASK_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT0_LIST0_INT_MASK_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT1_CHANNEL0_INT_STAT_PRI_VID2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT1_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT1_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT1_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT1_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT1_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT1_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT1_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT1_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT1_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT1_CHANNEL5_INT_STAT_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT1_CHANNEL5_INT_MASK_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT1_CLIENT0_INT_STAT_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT1_CLIENT0_INT_MASK_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT1_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT1_LIST0_INT_STAT_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT1_LIST0_INT_STAT_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT1_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT1_LIST0_INT_MASK_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT1_LIST0_INT_MASK_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT2_CHANNEL0_INT_STAT_PRI_VID2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT2_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT2_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT2_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT2_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT2_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT2_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT2_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT2_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT2_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT2_CHANNEL5_INT_STAT_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT2_CHANNEL5_INT_MASK_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT2_CLIENT0_INT_STAT_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT2_CLIENT0_INT_MASK_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT2_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT2_LIST0_INT_STAT_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT2_LIST0_INT_STAT_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT2_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT2_LIST0_INT_MASK_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT2_LIST0_INT_MASK_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT3_CHANNEL0_INT_STAT_PRI_VID2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_MV0_SHIFT                                                          (12U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_MV0_MASK                                                           (0x00001000U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_MV_OUT_SHIFT                                                       (15U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_MV_OUT_MASK                                                        (0x00008000U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_CHROMA_SHIFT                                                       (1U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_CHROMA_MASK                                                        (0x00000002U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_LUMA_SHIFT                                                         (0U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_LUMA_MASK                                                          (0x00000001U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                  (3U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                   (0x00000008U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                    (2U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD1_LUMA_MASK                                                     (0x00000004U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                  (5U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                   (0x00000020U)

#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                    (4U)
#define VPDMA_INT3_CHANNEL0_INT_MASK_PRI_FLD2_LUMA_MASK                                                     (0x00000010U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT3_CHANNEL1_INT_STAT_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_SHIFT                                               (6U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC0_MASK                                                (0x00000040U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_SHIFT                                               (7U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC1_MASK                                                (0x00000080U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_SHIFT                                              (16U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC10_MASK                                               (0x00010000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_SHIFT                                              (17U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC11_MASK                                               (0x00020000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_SHIFT                                              (18U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC12_MASK                                               (0x00040000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_SHIFT                                              (19U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC13_MASK                                               (0x00080000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_SHIFT                                              (20U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC14_MASK                                               (0x00100000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_SHIFT                                              (21U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC15_MASK                                               (0x00200000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_SHIFT                                               (8U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC2_MASK                                                (0x00000100U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_SHIFT                                               (9U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC3_MASK                                                (0x00000200U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_SHIFT                                               (10U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC4_MASK                                                (0x00000400U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_SHIFT                                               (11U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC5_MASK                                                (0x00000800U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_SHIFT                                               (12U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC6_MASK                                                (0x00001000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_SHIFT                                               (13U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC7_MASK                                                (0x00002000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_SHIFT                                               (14U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC8_MASK                                                (0x00004000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_SHIFT                                               (15U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTA_SRC9_MASK                                                (0x00008000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_SHIFT                                               (22U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC0_MASK                                                (0x00400000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_SHIFT                                               (23U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC1_MASK                                                (0x00800000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_SHIFT                                               (24U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC2_MASK                                                (0x01000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_SHIFT                                               (25U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC3_MASK                                                (0x02000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_SHIFT                                               (26U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC4_MASK                                                (0x04000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_SHIFT                                               (27U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC5_MASK                                                (0x08000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_SHIFT                                               (28U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC6_MASK                                                (0x10000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_SHIFT                                               (29U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC7_MASK                                                (0x20000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_SHIFT                                               (30U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC8_MASK                                                (0x40000000U)

#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_SHIFT                                               (31U)
#define VPDMA_INT3_CHANNEL1_INT_MASK_S0_MULT_PORTB_SRC9_MASK                                                (0x80000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT3_CHANNEL2_INT_STAT_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_SHIFT                                                (6U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC0_MASK                                                 (0x00000040U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_SHIFT                                                (7U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC1_MASK                                                 (0x00000080U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_SHIFT                                               (16U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC10_MASK                                                (0x00010000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_SHIFT                                               (17U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC11_MASK                                                (0x00020000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_SHIFT                                               (18U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC12_MASK                                                (0x00040000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_SHIFT                                               (19U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC13_MASK                                                (0x00080000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_SHIFT                                               (20U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC14_MASK                                                (0x00100000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_SHIFT                                               (21U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC15_MASK                                                (0x00200000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_SHIFT                                                (8U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC2_MASK                                                 (0x00000100U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_SHIFT                                                (9U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC3_MASK                                                 (0x00000200U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_SHIFT                                                (10U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC4_MASK                                                 (0x00000400U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_SHIFT                                                (11U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC5_MASK                                                 (0x00000800U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_SHIFT                                                (12U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC6_MASK                                                 (0x00001000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_SHIFT                                                (13U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC7_MASK                                                 (0x00002000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_SHIFT                                                (14U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC8_MASK                                                 (0x00004000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_SHIFT                                                (15U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCA_SRC9_MASK                                                 (0x00008000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_SHIFT                                                (22U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC0_MASK                                                 (0x00400000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_SHIFT                                                (23U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC1_MASK                                                 (0x00800000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_SHIFT                                                (24U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC2_MASK                                                 (0x01000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_SHIFT                                                (25U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC3_MASK                                                 (0x02000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_SHIFT                                                (26U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC4_MASK                                                 (0x04000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_SHIFT                                                (27U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC5_MASK                                                 (0x08000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_SHIFT                                                (28U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC6_MASK                                                 (0x10000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_SHIFT                                                (29U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC7_MASK                                                 (0x20000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_SHIFT                                                (30U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC8_MASK                                                 (0x40000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_SHIFT                                                (31U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_ANCB_SRC9_MASK                                                 (0x80000000U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_SHIFT                                              (0U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC10_MASK                                               (0x00000001U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_SHIFT                                              (1U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC11_MASK                                               (0x00000002U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_SHIFT                                              (2U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC12_MASK                                               (0x00000004U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_SHIFT                                              (3U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC13_MASK                                               (0x00000008U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_SHIFT                                              (4U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC14_MASK                                               (0x00000010U)

#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_SHIFT                                              (5U)
#define VPDMA_INT3_CHANNEL2_INT_MASK_S0_MULT_PORTB_SRC15_MASK                                               (0x00000020U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT3_CHANNEL3_INT_STAT_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_SHIFT                                               (0U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC10_MASK                                                (0x00000001U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_SHIFT                                               (1U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC11_MASK                                                (0x00000002U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_SHIFT                                               (2U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC12_MASK                                                (0x00000004U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_SHIFT                                               (3U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC13_MASK                                                (0x00000008U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_SHIFT                                               (4U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC14_MASK                                                (0x00000010U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_SHIFT                                               (5U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_MULT_ANCB_SRC15_MASK                                                (0x00000020U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_SHIFT                                                  (7U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_CHROMA_MASK                                                   (0x00000080U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_LUMA_SHIFT                                                    (6U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_LUMA_MASK                                                     (0x00000040U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_RGB_SHIFT                                                     (10U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTA_RGB_MASK                                                      (0x00000400U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_SHIFT                                                  (9U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_CHROMA_MASK                                                   (0x00000200U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_LUMA_SHIFT                                                    (8U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_LUMA_MASK                                                     (0x00000100U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_RGB_SHIFT                                                     (11U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S0_PORTB_RGB_MASK                                                      (0x00000800U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_SHIFT                                               (12U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC0_MASK                                                (0x00001000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_SHIFT                                               (13U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC1_MASK                                                (0x00002000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_SHIFT                                              (22U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC10_MASK                                               (0x00400000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_SHIFT                                              (23U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC11_MASK                                               (0x00800000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_SHIFT                                              (24U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC12_MASK                                               (0x01000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_SHIFT                                              (25U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC13_MASK                                               (0x02000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_SHIFT                                              (26U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC14_MASK                                               (0x04000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_SHIFT                                              (27U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC15_MASK                                               (0x08000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_SHIFT                                               (14U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC2_MASK                                                (0x00004000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_SHIFT                                               (15U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC3_MASK                                                (0x00008000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_SHIFT                                               (16U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC4_MASK                                                (0x00010000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_SHIFT                                               (17U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC5_MASK                                                (0x00020000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_SHIFT                                               (18U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC6_MASK                                                (0x00040000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_SHIFT                                               (19U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC7_MASK                                                (0x00080000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_SHIFT                                               (20U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC8_MASK                                                (0x00100000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_SHIFT                                               (21U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTA_SRC9_MASK                                                (0x00200000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_SHIFT                                               (28U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC0_MASK                                                (0x10000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_SHIFT                                               (29U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC1_MASK                                                (0x20000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_SHIFT                                               (30U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC2_MASK                                                (0x40000000U)

#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_SHIFT                                               (31U)
#define VPDMA_INT3_CHANNEL3_INT_MASK_S1_MULT_PORTB_SRC3_MASK                                                (0x80000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT3_CHANNEL4_INT_STAT_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_SHIFT                                                (12U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC0_MASK                                                 (0x00001000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_SHIFT                                                (13U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC1_MASK                                                 (0x00002000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_SHIFT                                               (22U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC10_MASK                                                (0x00400000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_SHIFT                                               (23U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC11_MASK                                                (0x00800000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_SHIFT                                               (24U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC12_MASK                                                (0x01000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_SHIFT                                               (25U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC13_MASK                                                (0x02000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_SHIFT                                               (26U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC14_MASK                                                (0x04000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_SHIFT                                               (27U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC15_MASK                                                (0x08000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_SHIFT                                                (14U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC2_MASK                                                 (0x00004000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_SHIFT                                                (15U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC3_MASK                                                 (0x00008000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_SHIFT                                                (16U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC4_MASK                                                 (0x00010000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_SHIFT                                                (17U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC5_MASK                                                 (0x00020000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_SHIFT                                                (18U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC6_MASK                                                 (0x00040000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_SHIFT                                                (19U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC7_MASK                                                 (0x00080000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_SHIFT                                                (20U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC8_MASK                                                 (0x00100000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_SHIFT                                                (21U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCA_SRC9_MASK                                                 (0x00200000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_SHIFT                                                (28U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC0_MASK                                                 (0x10000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_SHIFT                                                (29U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC1_MASK                                                 (0x20000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_SHIFT                                                (30U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC2_MASK                                                 (0x40000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_SHIFT                                                (31U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_ANCB_SRC3_MASK                                                 (0x80000000U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_SHIFT                                              (6U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC10_MASK                                               (0x00000040U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_SHIFT                                              (7U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC11_MASK                                               (0x00000080U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_SHIFT                                              (8U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC12_MASK                                               (0x00000100U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_SHIFT                                              (9U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC13_MASK                                               (0x00000200U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_SHIFT                                              (10U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC14_MASK                                               (0x00000400U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_SHIFT                                              (11U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC15_MASK                                               (0x00000800U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_SHIFT                                               (0U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC4_MASK                                                (0x00000001U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_SHIFT                                               (1U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC5_MASK                                                (0x00000002U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_SHIFT                                               (2U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC6_MASK                                                (0x00000004U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_SHIFT                                               (3U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC7_MASK                                                (0x00000008U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_SHIFT                                               (4U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC8_MASK                                                (0x00000010U)

#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_SHIFT                                               (5U)
#define VPDMA_INT3_CHANNEL4_INT_MASK_S1_MULT_PORTB_SRC9_MASK                                                (0x00000020U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT3_CHANNEL5_INT_STAT_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_SHIFT                                               (6U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC10_MASK                                                (0x00000040U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_SHIFT                                               (7U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC11_MASK                                                (0x00000080U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_SHIFT                                               (8U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC12_MASK                                                (0x00000100U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_SHIFT                                               (9U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC13_MASK                                                (0x00000200U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_SHIFT                                               (10U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC14_MASK                                                (0x00000400U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_SHIFT                                               (11U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC15_MASK                                                (0x00000800U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_SHIFT                                                (0U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC4_MASK                                                 (0x00000001U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_SHIFT                                                (1U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC5_MASK                                                 (0x00000002U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_SHIFT                                                (2U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC6_MASK                                                 (0x00000004U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_SHIFT                                                (3U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC7_MASK                                                 (0x00000008U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_SHIFT                                                (4U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC8_MASK                                                 (0x00000010U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_SHIFT                                                (5U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_MULT_ANCB_SRC9_MASK                                                 (0x00000020U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_SHIFT                                                  (13U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_CHROMA_MASK                                                   (0x00002000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_LUMA_SHIFT                                                    (12U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_LUMA_MASK                                                     (0x00001000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_RGB_SHIFT                                                     (16U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTA_RGB_MASK                                                      (0x00010000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_SHIFT                                                  (15U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_CHROMA_MASK                                                   (0x00008000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_LUMA_SHIFT                                                    (14U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_LUMA_MASK                                                     (0x00004000U)

#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_RGB_SHIFT                                                     (17U)
#define VPDMA_INT3_CHANNEL5_INT_MASK_S1_PORTB_RGB_MASK                                                      (0x00020000U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT3_CLIENT0_INT_STAT_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_CHROMA_SHIFT                                                        (0U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_CHROMA_MASK                                                         (0x00000001U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_LUMA_SHIFT                                                          (1U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_LUMA_MASK                                                           (0x00000002U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_SHIFT                                                   (3U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD1_CHROMA_MASK                                                    (0x00000008U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD1_LUMA_SHIFT                                                     (2U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD1_LUMA_MASK                                                      (0x00000004U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_SHIFT                                                   (5U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD2_CHROMA_MASK                                                    (0x00000020U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD2_LUMA_SHIFT                                                     (4U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_FLD2_LUMA_MASK                                                      (0x00000010U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_MV0_SHIFT                                                           (12U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_MV0_MASK                                                            (0x00001000U)

#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_MV_OUT_SHIFT                                                        (15U)
#define VPDMA_INT3_CLIENT0_INT_MASK_PRI_MV_OUT_MASK                                                         (0x00008000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT3_LIST0_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT3_LIST0_INT_STAT_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT3_LIST0_INT_STAT_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT                                             (16U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK                                              (0x00010000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT                                             (17U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK                                              (0x00020000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT                                            (26U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK                                             (0x04000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT                                            (27U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK                                             (0x08000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT                                            (28U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK                                             (0x10000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT                                            (29U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK                                             (0x20000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT                                            (30U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK                                             (0x40000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT                                            (31U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK                                             (0x80000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT                                             (18U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK                                              (0x00040000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT                                             (19U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK                                              (0x00080000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT                                             (20U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK                                              (0x00100000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT                                             (21U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK                                              (0x00200000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT                                             (22U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK                                              (0x00400000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT                                             (23U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK                                              (0x00800000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT                                             (24U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK                                              (0x01000000U)

#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT                                             (25U)
#define VPDMA_INT3_LIST0_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK                                              (0x02000000U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST0_COMPLETE_SHIFT                                                      (0U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST0_COMPLETE_MASK                                                       (0x00000001U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST0_NOTIFY_SHIFT                                                        (1U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST0_NOTIFY_MASK                                                         (0x00000002U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST1_COMPLETE_SHIFT                                                      (2U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST1_COMPLETE_MASK                                                       (0x00000004U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST1_NOTIFY_SHIFT                                                        (3U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST1_NOTIFY_MASK                                                         (0x00000008U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST2_COMPLETE_SHIFT                                                      (4U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST2_COMPLETE_MASK                                                       (0x00000010U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST2_NOTIFY_SHIFT                                                        (5U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST2_NOTIFY_MASK                                                         (0x00000020U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST3_COMPLETE_SHIFT                                                      (6U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST3_COMPLETE_MASK                                                       (0x00000040U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST3_NOTIFY_SHIFT                                                        (7U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST3_NOTIFY_MASK                                                         (0x00000080U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST4_COMPLETE_SHIFT                                                      (8U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST4_COMPLETE_MASK                                                       (0x00000100U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST4_NOTIFY_SHIFT                                                        (9U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST4_NOTIFY_MASK                                                         (0x00000200U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST5_COMPLETE_SHIFT                                                      (10U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST5_COMPLETE_MASK                                                       (0x00000400U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST5_NOTIFY_SHIFT                                                        (11U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST5_NOTIFY_MASK                                                         (0x00000800U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST6_COMPLETE_SHIFT                                                      (12U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST6_COMPLETE_MASK                                                       (0x00001000U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST6_NOTIFY_SHIFT                                                        (13U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST6_NOTIFY_MASK                                                         (0x00002000U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST7_COMPLETE_SHIFT                                                      (14U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST7_COMPLETE_MASK                                                       (0x00004000U)

#define VPDMA_INT3_LIST0_INT_MASK_LIST7_NOTIFY_SHIFT                                                        (15U)
#define VPDMA_INT3_LIST0_INT_MASK_LIST7_NOTIFY_MASK                                                         (0x00008000U)

#define VPDMA_PERF_MON0_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON0_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON0_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON0_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON0_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON0_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON0_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON0_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON0_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON0_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON0_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON0_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON1_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON1_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON1_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON1_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON1_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON1_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON1_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON1_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON1_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON1_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON1_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON1_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON2_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON2_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON2_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON2_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON2_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON2_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON2_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON2_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON2_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON2_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON2_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON2_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON3_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON3_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON3_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON3_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON3_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON3_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON3_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON3_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON3_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON3_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON3_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON3_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON4_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON4_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON4_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON4_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON4_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON4_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON4_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON4_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON4_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON4_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON4_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON4_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON5_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON5_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON5_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON5_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON5_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON5_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON5_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON5_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON5_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON5_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON5_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON5_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON6_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON6_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON6_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON6_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON6_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON6_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON6_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON6_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON6_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON6_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON6_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON6_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON7_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON7_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON7_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON7_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON7_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON7_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON7_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON7_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON7_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON7_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON7_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON7_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON8_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON8_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON8_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON8_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON8_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON8_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON8_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON8_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON8_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON8_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON8_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON8_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON9_CAPTURE_MODE_SHIFT                                                                  (30U)
#define VPDMA_PERF_MON9_CAPTURE_MODE_MASK                                                                   (0xc0000000U)

#define VPDMA_PERF_MON9_CURR_COUNT_SHIFT                                                                    (0U)
#define VPDMA_PERF_MON9_CURR_COUNT_MASK                                                                     (0x0000ffffU)

#define VPDMA_PERF_MON9_START_CLIENT_SHIFT                                                                  (20U)
#define VPDMA_PERF_MON9_START_CLIENT_MASK                                                                   (0x00300000U)

#define VPDMA_PERF_MON9_START_COUNT_SHIFT                                                                   (16U)
#define VPDMA_PERF_MON9_START_COUNT_MASK                                                                    (0x00070000U)

#define VPDMA_PERF_MON9_STOP_CLIENT_SHIFT                                                                   (28U)
#define VPDMA_PERF_MON9_STOP_CLIENT_MASK                                                                    (0x30000000U)

#define VPDMA_PERF_MON9_STOP_COUNT_SHIFT                                                                    (24U)
#define VPDMA_PERF_MON9_STOP_COUNT_MASK                                                                     (0x07000000U)

#define VPDMA_PERF_MON10_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON10_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON10_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON10_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON10_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON10_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON10_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON10_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON10_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON10_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON10_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON10_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON11_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON11_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON11_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON11_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON11_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON11_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON11_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON11_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON11_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON11_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON11_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON11_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON12_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON12_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON12_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON12_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON12_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON12_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON12_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON12_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON12_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON12_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON12_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON12_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON13_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON13_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON13_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON13_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON13_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON13_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON13_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON13_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON13_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON13_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON13_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON13_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON14_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON14_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON14_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON14_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON14_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON14_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON14_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON14_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON14_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON14_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON14_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON14_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON15_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON15_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON15_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON15_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON15_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON15_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON15_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON15_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON15_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON15_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON15_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON15_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON16_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON16_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON16_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON16_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON16_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON16_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON16_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON16_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON16_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON16_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON16_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON16_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON17_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON17_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON17_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON17_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON17_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON17_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON17_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON17_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON17_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON17_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON17_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON17_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON18_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON18_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON18_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON18_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON18_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON18_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON18_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON18_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON18_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON18_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON18_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON18_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON19_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON19_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON19_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON19_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON19_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON19_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON19_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON19_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON19_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON19_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON19_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON19_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON20_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON20_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON20_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON20_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON20_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON20_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON20_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON20_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON20_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON20_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON20_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON20_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON21_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON21_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON21_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON21_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON21_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON21_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON21_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON21_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON21_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON21_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON21_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON21_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON22_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON22_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON22_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON22_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON22_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON22_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON22_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON22_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON22_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON22_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON22_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON22_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON23_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON23_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON23_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON23_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON23_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON23_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON23_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON23_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON23_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON23_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON23_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON23_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON24_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON24_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON24_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON24_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON24_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON24_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON24_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON24_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON24_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON24_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON24_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON24_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON25_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON25_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON25_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON25_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON25_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON25_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON25_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON25_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON25_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON25_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON25_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON25_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON26_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON26_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON26_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON26_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON26_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON26_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON26_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON26_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON26_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON26_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON26_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON26_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON27_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON27_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON27_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON27_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON27_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON27_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON27_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON27_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON27_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON27_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON27_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON27_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON28_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON28_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON28_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON28_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON28_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON28_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON28_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON28_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON28_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON28_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON28_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON28_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON29_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON29_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON29_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON29_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON29_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON29_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON29_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON29_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON29_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON29_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON29_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON29_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON30_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON30_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON30_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON30_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON30_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON30_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON30_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON30_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON30_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON30_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON30_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON30_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON31_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON31_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON31_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON31_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON31_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON31_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON31_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON31_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON31_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON31_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON31_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON31_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON32_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON32_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON32_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON32_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON32_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON32_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON32_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON32_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON32_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON32_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON32_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON32_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON33_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON33_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON33_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON33_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON33_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON33_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON33_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON33_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON33_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON33_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON33_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON33_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON34_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON34_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON34_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON34_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON34_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON34_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON34_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON34_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON34_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON34_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON34_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON34_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON35_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON35_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON35_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON35_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON35_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON35_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON35_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON35_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON35_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON35_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON35_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON35_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON36_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON36_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON36_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON36_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON36_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON36_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON36_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON36_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON36_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON36_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON36_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON36_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON37_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON37_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON37_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON37_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON37_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON37_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON37_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON37_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON37_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON37_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON37_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON37_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON38_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON38_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON38_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON38_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON38_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON38_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON38_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON38_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON38_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON38_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON38_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON38_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON39_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON39_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON39_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON39_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON39_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON39_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON39_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON39_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON39_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON39_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON39_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON39_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON40_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON40_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON40_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON40_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON40_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON40_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON40_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON40_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON40_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON40_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON40_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON40_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON41_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON41_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON41_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON41_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON41_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON41_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON41_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON41_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON41_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON41_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON41_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON41_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON42_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON42_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON42_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON42_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON42_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON42_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON42_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON42_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON42_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON42_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON42_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON42_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON43_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON43_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON43_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON43_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON43_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON43_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON43_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON43_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON43_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON43_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON43_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON43_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON44_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON44_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON44_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON44_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON44_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON44_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON44_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON44_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON44_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON44_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON44_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON44_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON45_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON45_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON45_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON45_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON45_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON45_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON45_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON45_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON45_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON45_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON45_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON45_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON46_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON46_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON46_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON46_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON46_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON46_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON46_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON46_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON46_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON46_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON46_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON46_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON47_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON47_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON47_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON47_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON47_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON47_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON47_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON47_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON47_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON47_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON47_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON47_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON48_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON48_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON48_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON48_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON48_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON48_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON48_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON48_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON48_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON48_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON48_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON48_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON49_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON49_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON49_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON49_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON49_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON49_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON49_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON49_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON49_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON49_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON49_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON49_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON50_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON50_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON50_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON50_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON50_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON50_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON50_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON50_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON50_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON50_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON50_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON50_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON51_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON51_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON51_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON51_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON51_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON51_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON51_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON51_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON51_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON51_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON51_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON51_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON52_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON52_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON52_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON52_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON52_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON52_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON52_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON52_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON52_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON52_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON52_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON52_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON53_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON53_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON53_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON53_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON53_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON53_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON53_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON53_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON53_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON53_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON53_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON53_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON54_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON54_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON54_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON54_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON54_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON54_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON54_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON54_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON54_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON54_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON54_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON54_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON55_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON55_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON55_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON55_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON55_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON55_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON55_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON55_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON55_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON55_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON55_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON55_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON56_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON56_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON56_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON56_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON56_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON56_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON56_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON56_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON56_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON56_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON56_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON56_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON57_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON57_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON57_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON57_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON57_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON57_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON57_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON57_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON57_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON57_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON57_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON57_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON58_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON58_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON58_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON58_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON58_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON58_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON58_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON58_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON58_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON58_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON58_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON58_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON59_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON59_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON59_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON59_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON59_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON59_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON59_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON59_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON59_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON59_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON59_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON59_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON60_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON60_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON60_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON60_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON60_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON60_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON60_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON60_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON60_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON60_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON60_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON60_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PERF_MON61_CAPTURE_MODE_SHIFT                                                                 (30U)
#define VPDMA_PERF_MON61_CAPTURE_MODE_MASK                                                                  (0xc0000000U)

#define VPDMA_PERF_MON61_CURR_COUNT_SHIFT                                                                   (0U)
#define VPDMA_PERF_MON61_CURR_COUNT_MASK                                                                    (0x0000ffffU)

#define VPDMA_PERF_MON61_START_CLIENT_SHIFT                                                                 (20U)
#define VPDMA_PERF_MON61_START_CLIENT_MASK                                                                  (0x00300000U)

#define VPDMA_PERF_MON61_START_COUNT_SHIFT                                                                  (16U)
#define VPDMA_PERF_MON61_START_COUNT_MASK                                                                   (0x00070000U)

#define VPDMA_PERF_MON61_STOP_CLIENT_SHIFT                                                                  (28U)
#define VPDMA_PERF_MON61_STOP_CLIENT_MASK                                                                   (0x30000000U)

#define VPDMA_PERF_MON61_STOP_COUNT_SHIFT                                                                   (24U)
#define VPDMA_PERF_MON61_STOP_COUNT_MASK                                                                    (0x07000000U)

#define VPDMA_PRI_CHROMA_CSTAT_BUSY_SHIFT                                                                   (15U)
#define VPDMA_PRI_CHROMA_CSTAT_BUSY_MASK                                                                    (0x00008000U)

#define VPDMA_PRI_CHROMA_CSTAT_DMA_ACTIVE_SHIFT                                                             (14U)
#define VPDMA_PRI_CHROMA_CSTAT_DMA_ACTIVE_MASK                                                              (0x00004000U)

#define VPDMA_PRI_CHROMA_CSTAT_FRAME_START_SHIFT                                                            (10U)
#define VPDMA_PRI_CHROMA_CSTAT_FRAME_START_MASK                                                             (0x00003c00U)

#define VPDMA_PRI_CHROMA_CSTAT_LINE_MODE_SHIFT                                                              (8U)
#define VPDMA_PRI_CHROMA_CSTAT_LINE_MODE_MASK                                                               (0x00000300U)

#define VPDMA_PRI_CHROMA_CSTAT_REQ_DELAY_SHIFT                                                              (24U)
#define VPDMA_PRI_CHROMA_CSTAT_REQ_DELAY_MASK                                                               (0xff000000U)

#define VPDMA_PRI_CHROMA_CSTAT_REQ_RATE_SHIFT                                                               (16U)
#define VPDMA_PRI_CHROMA_CSTAT_REQ_RATE_MASK                                                                (0x00ff0000U)

#define VPDMA_PRI_LUMA_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_PRI_LUMA_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_PRI_LUMA_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_PRI_LUMA_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_PRI_LUMA_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_PRI_LUMA_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_PRI_LUMA_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_PRI_LUMA_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_PRI_LUMA_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_PRI_LUMA_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_PRI_FLD1_LUMA_CSTAT_BUSY_SHIFT                                                                (15U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT_BUSY_MASK                                                                 (0x00008000U)

#define VPDMA_PRI_FLD1_LUMA_CSTAT_DMA_ACTIVE_SHIFT                                                          (14U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT_DMA_ACTIVE_MASK                                                           (0x00004000U)

#define VPDMA_PRI_FLD1_LUMA_CSTAT_FRAME_START_SHIFT                                                         (10U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT_FRAME_START_MASK                                                          (0x00003c00U)

#define VPDMA_PRI_FLD1_LUMA_CSTAT_REQ_DELAY_SHIFT                                                           (24U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT_REQ_DELAY_MASK                                                            (0xff000000U)

#define VPDMA_PRI_FLD1_LUMA_CSTAT_REQ_RATE_SHIFT                                                            (16U)
#define VPDMA_PRI_FLD1_LUMA_CSTAT_REQ_RATE_MASK                                                             (0x00ff0000U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_BUSY_SHIFT                                                              (15U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_BUSY_MASK                                                               (0x00008000U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_DMA_ACTIVE_SHIFT                                                        (14U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_DMA_ACTIVE_MASK                                                         (0x00004000U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_FRAME_START_SHIFT                                                       (10U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_FRAME_START_MASK                                                        (0x00003c00U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_LINE_MODE_SHIFT                                                         (8U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_LINE_MODE_MASK                                                          (0x00000300U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_REQ_DELAY_SHIFT                                                         (24U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_REQ_DELAY_MASK                                                          (0xff000000U)

#define VPDMA_PRI_FLD1_CHROMA_CSTAT_REQ_RATE_SHIFT                                                          (16U)
#define VPDMA_PRI_FLD1_CHROMA_CSTAT_REQ_RATE_MASK                                                           (0x00ff0000U)

#define VPDMA_PRI_FLD2_LUMA_CSTAT_BUSY_SHIFT                                                                (15U)
#define VPDMA_PRI_FLD2_LUMA_CSTAT_BUSY_MASK                                                                 (0x00008000U)

#define VPDMA_PRI_FLD2_LUMA_CSTAT_DMA_ACTIVE_SHIFT                                                          (14U)
#define VPDMA_PRI_FLD2_LUMA_CSTAT_DMA_ACTIVE_MASK                                                           (0x00004000U)

#define VPDMA_PRI_FLD2_LUMA_CSTAT_FRAME_START_SHIFT                                                         (10U)
#define VPDMA_PRI_FLD2_LUMA_CSTAT_FRAME_START_MASK                                                          (0x00003c00U)

#define VPDMA_PRI_FLD2_LUMA_CSTAT_REQ_DELAY_SHIFT                                                           (24U)
#define VPDMA_PRI_FLD2_LUMA_CSTAT_REQ_DELAY_MASK                                                            (0xff000000U)

#define VPDMA_PRI_FLD2_LUMA_CSTAT_REQ_RATE_SHIFT                                                            (16U)
#define VPDMA_PRI_FLD2_LUMA_CSTAT_REQ_RATE_MASK                                                             (0x00ff0000U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_BUSY_SHIFT                                                              (15U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_BUSY_MASK                                                               (0x00008000U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_DMA_ACTIVE_SHIFT                                                        (14U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_DMA_ACTIVE_MASK                                                         (0x00004000U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_FRAME_START_SHIFT                                                       (10U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_FRAME_START_MASK                                                        (0x00003c00U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_LINE_MODE_SHIFT                                                         (8U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_LINE_MODE_MASK                                                          (0x00000300U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_REQ_DELAY_SHIFT                                                         (24U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_REQ_DELAY_MASK                                                          (0xff000000U)

#define VPDMA_PRI_FLD2_CHROMA_CSTAT_REQ_RATE_SHIFT                                                          (16U)
#define VPDMA_PRI_FLD2_CHROMA_CSTAT_REQ_RATE_MASK                                                           (0x00ff0000U)

#define VPDMA_PRI_MV0_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_PRI_MV0_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_PRI_MV0_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_PRI_MV0_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_PRI_MV0_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_PRI_MV0_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_PRI_MV0_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_PRI_MV0_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_PRI_MV0_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_PRI_MV0_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_PRI_MV_OUT_CSTAT_BUSY_SHIFT                                                                   (15U)
#define VPDMA_PRI_MV_OUT_CSTAT_BUSY_MASK                                                                    (0x00008000U)

#define VPDMA_PRI_MV_OUT_CSTAT_DMA_ACTIVE_SHIFT                                                             (14U)
#define VPDMA_PRI_MV_OUT_CSTAT_DMA_ACTIVE_MASK                                                              (0x00004000U)

#define VPDMA_PRI_MV_OUT_CSTAT_FRAME_START_SHIFT                                                            (10U)
#define VPDMA_PRI_MV_OUT_CSTAT_FRAME_START_MASK                                                             (0x00003c00U)

#define VPDMA_PRI_MV_OUT_CSTAT_REQ_DELAY_SHIFT                                                              (24U)
#define VPDMA_PRI_MV_OUT_CSTAT_REQ_DELAY_MASK                                                               (0xff000000U)

#define VPDMA_PRI_MV_OUT_CSTAT_REQ_RATE_SHIFT                                                               (16U)
#define VPDMA_PRI_MV_OUT_CSTAT_REQ_RATE_MASK                                                                (0x00ff0000U)

#define VPDMA_S0_LO_Y_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_S0_LO_Y_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_S0_LO_Y_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_S0_LO_Y_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_S0_LO_Y_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_S0_LO_Y_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_S0_LO_Y_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_S0_LO_Y_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_S0_LO_Y_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_S0_LO_Y_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_S0_LO_UV_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S0_LO_UV_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S0_LO_UV_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S0_LO_UV_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S0_LO_UV_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S0_LO_UV_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S0_LO_UV_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S0_LO_UV_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S0_LO_UV_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S0_LO_UV_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S0_UP_Y_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_S0_UP_Y_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_S0_UP_Y_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_S0_UP_Y_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_S0_UP_Y_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_S0_UP_Y_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_S0_UP_Y_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_S0_UP_Y_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_S0_UP_Y_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_S0_UP_Y_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_S0_UP_UV_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S0_UP_UV_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S0_UP_UV_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S0_UP_UV_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S0_UP_UV_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S0_UP_UV_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S0_UP_UV_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S0_UP_UV_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S0_UP_UV_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S0_UP_UV_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S1_LO_Y_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_S1_LO_Y_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_S1_LO_Y_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_S1_LO_Y_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_S1_LO_Y_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_S1_LO_Y_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_S1_LO_Y_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_S1_LO_Y_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_S1_LO_Y_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_S1_LO_Y_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_S1_LO_UV_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S1_LO_UV_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S1_LO_UV_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S1_LO_UV_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S1_LO_UV_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S1_LO_UV_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S1_LO_UV_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S1_LO_UV_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S1_LO_UV_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S1_LO_UV_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S1_UP_Y_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_S1_UP_Y_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_S1_UP_Y_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_S1_UP_Y_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_S1_UP_Y_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_S1_UP_Y_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_S1_UP_Y_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_S1_UP_Y_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_S1_UP_Y_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_S1_UP_Y_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_S1_UP_UV_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S1_UP_UV_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S1_UP_UV_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S1_UP_UV_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S1_UP_UV_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S1_UP_UV_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S1_UP_UV_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S1_UP_UV_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S1_UP_UV_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S1_UP_UV_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_VPI_CTL_CSTAT_BUSY_SHIFT                                                                      (15U)
#define VPDMA_VPI_CTL_CSTAT_BUSY_MASK                                                                       (0x00008000U)

#define VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_SHIFT                                                                (14U)
#define VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_MASK                                                                 (0x00004000U)

#define VPDMA_VPI_CTL_CSTAT_FRAME_START_SHIFT                                                               (10U)
#define VPDMA_VPI_CTL_CSTAT_FRAME_START_MASK                                                                (0x00003c00U)

#define VPDMA_VPI_CTL_CSTAT_REQ_DELAY_SHIFT                                                                 (24U)
#define VPDMA_VPI_CTL_CSTAT_REQ_DELAY_MASK                                                                  (0xff000000U)

#define VPDMA_VPI_CTL_CSTAT_REQ_RATE_SHIFT                                                                  (16U)
#define VPDMA_VPI_CTL_CSTAT_REQ_RATE_MASK                                                                   (0x00ff0000U)

#define VPDMA_S0_ANC_A_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S0_ANC_A_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S0_ANC_A_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S0_ANC_A_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S0_ANC_A_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S0_ANC_A_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S0_ANC_A_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S0_ANC_A_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S0_ANC_A_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S0_ANC_A_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S0_ANC_B_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S0_ANC_B_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S0_ANC_B_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S0_ANC_B_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S0_ANC_B_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S0_ANC_B_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S0_ANC_B_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S0_ANC_B_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S0_ANC_B_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S0_ANC_B_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S1_ANC_A_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S1_ANC_A_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S1_ANC_A_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S1_ANC_A_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S1_ANC_A_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S1_ANC_A_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S1_ANC_A_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S1_ANC_A_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S1_ANC_A_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S1_ANC_A_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#define VPDMA_S1_ANC_B_CSTAT_BUSY_SHIFT                                                                     (15U)
#define VPDMA_S1_ANC_B_CSTAT_BUSY_MASK                                                                      (0x00008000U)

#define VPDMA_S1_ANC_B_CSTAT_DMA_ACTIVE_SHIFT                                                               (14U)
#define VPDMA_S1_ANC_B_CSTAT_DMA_ACTIVE_MASK                                                                (0x00004000U)

#define VPDMA_S1_ANC_B_CSTAT_FRAME_START_SHIFT                                                              (10U)
#define VPDMA_S1_ANC_B_CSTAT_FRAME_START_MASK                                                               (0x00003c00U)

#define VPDMA_S1_ANC_B_CSTAT_REQ_DELAY_SHIFT                                                                (24U)
#define VPDMA_S1_ANC_B_CSTAT_REQ_DELAY_MASK                                                                 (0xff000000U)

#define VPDMA_S1_ANC_B_CSTAT_REQ_RATE_SHIFT                                                                 (16U)
#define VPDMA_S1_ANC_B_CSTAT_REQ_RATE_MASK                                                                  (0x00ff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_VPDMA_H_ */
