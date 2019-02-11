/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

#ifndef HW_VIP_PARSER_H_
#define HW_VIP_PARSER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define VIP_MAIN                                                                                            (0x0U)
#define VIP_PORT_A                                                                                          (0x4U)
#define VIP_XTRA_PORT_A                                                                                     (0x8U)
#define VIP_PORT_B                                                                                          (0xcU)
#define VIP_XTRA_PORT_B                                                                                     (0x10U)
#define VIP_FIQ_MASK                                                                                        (0x14U)
#define VIP_FIQ_CLEAR                                                                                       (0x18U)
#define VIP_FIQ_STATUS                                                                                      (0x1cU)
#define VIP_OUTPUT_PORT_A_SRC_FID                                                                           (0x20U)
#define VIP_OUTPUT_PORT_B_SRC_FID                                                                           (0x28U)
#define VIP_OUTPUT_PORT_A_SRC0_SIZE                                                                         (0x30U)
#define VIP_OUTPUT_PORT_A_SRC1_SIZE                                                                         (0x34U)
#define VIP_OUTPUT_PORT_A_SRC2_SIZE                                                                         (0x38U)
#define VIP_OUTPUT_PORT_A_SRC3_SIZE                                                                         (0x3cU)
#define VIP_OUTPUT_PORT_A_SRC4_SIZE                                                                         (0x40U)
#define VIP_OUTPUT_PORT_A_SRC5_SIZE                                                                         (0x44U)
#define VIP_OUTPUT_PORT_A_SRC6_SIZE                                                                         (0x48U)
#define VIP_OUTPUT_PORT_A_SRC7_SIZE                                                                         (0x4cU)
#define VIP_OUTPUT_PORT_A_SRC8_SIZE                                                                         (0x50U)
#define VIP_OUTPUT_PORT_A_SRC9_SIZE                                                                         (0x54U)
#define VIP_OUTPUT_PORT_A_SRC10_SIZE                                                                        (0x58U)
#define VIP_OUTPUT_PORT_A_SRC11_SIZE                                                                        (0x5cU)
#define VIP_OUTPUT_PORT_A_SRC12_SIZE                                                                        (0x60U)
#define VIP_OUTPUT_PORT_A_SRC13_SIZE                                                                        (0x64U)
#define VIP_OUTPUT_PORT_A_SRC14_SIZE                                                                        (0x68U)
#define VIP_OUTPUT_PORT_A_SRC15_SIZE                                                                        (0x6cU)
#define VIP_OUTPUT_PORT_B_SRC0_SIZE                                                                         (0x70U)
#define VIP_OUTPUT_PORT_B_SRC1_SIZE                                                                         (0x74U)
#define VIP_OUTPUT_PORT_B_SRC2_SIZE                                                                         (0x78U)
#define VIP_OUTPUT_PORT_B_SRC3_SIZE                                                                         (0x7cU)
#define VIP_OUTPUT_PORT_B_SRC4_SIZE                                                                         (0x80U)
#define VIP_OUTPUT_PORT_B_SRC5_SIZE                                                                         (0x84U)
#define VIP_OUTPUT_PORT_B_SRC6_SIZE                                                                         (0x88U)
#define VIP_OUTPUT_PORT_B_SRC7_SIZE                                                                         (0x8cU)
#define VIP_OUTPUT_PORT_B_SRC8_SIZE                                                                         (0x90U)
#define VIP_OUTPUT_PORT_B_SRC9_SIZE                                                                         (0x94U)
#define VIP_OUTPUT_PORT_B_SRC10_SIZE                                                                        (0x98U)
#define VIP_OUTPUT_PORT_B_SRC11_SIZE                                                                        (0x9cU)
#define VIP_OUTPUT_PORT_B_SRC12_SIZE                                                                        (0xa0U)
#define VIP_OUTPUT_PORT_B_SRC13_SIZE                                                                        (0xa4U)
#define VIP_OUTPUT_PORT_B_SRC14_SIZE                                                                        (0xa8U)
#define VIP_OUTPUT_PORT_B_SRC15_SIZE                                                                        (0xacU)
#define VIP_PORT_A_VDET_VEC                                                                                 (0xb0U)
#define VIP_PORT_B_VDET_VEC                                                                                 (0xb4U)
#define VIP_ANC_CROP_HORZ_PORT_A                                                                            (0xb8U)
#define VIP_ANC_CROP_VERT_PORT_A                                                                            (0xbcU)
#define VIP_CROP_HORZ_PORT_A                                                                                (0xc0U)
#define VIP_CROP_VERT_PORT_A                                                                                (0xc4U)
#define VIP_ANC_CROP_HORZ_PORT_B                                                                            (0xc8U)
#define VIP_ANC_CROP_VERT_PORT_B                                                                            (0xccU)
#define VIP_CROP_HORZ_PORT_B                                                                                (0xd0U)
#define VIP_CROP_VERT_PORT_B                                                                                (0xd4U)
#define VIP_STOP_IMMEDIATE_PORT_A                                                                           (0xd8U)
#define VIP_STOP_IMMEDIATE_PORT_B                                                                           (0xdcU)
#define VIP_XTRA8_PORT_A                                                                                    (0xe0U)
#define VIP_XTRA9_PORT_B                                                                                    (0xe4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define VIP_MAIN_DATA_INTERFACE_MODE_SHIFT                                                                  (0U)
#define VIP_MAIN_DATA_INTERFACE_MODE_MASK                                                                   (0x00000003U)

#define VIP_MAIN_CLIP_BLNK_SHIFT                                                                            (4U)
#define VIP_MAIN_CLIP_BLNK_MASK                                                                             (0x00000010U)

#define VIP_MAIN_CLIP_ACTIVE_SHIFT                                                                          (5U)
#define VIP_MAIN_CLIP_ACTIVE_MASK                                                                           (0x00000020U)

#define VIP_PORT_A_SYNC_TYPE_SHIFT                                                                          (0U)
#define VIP_PORT_A_SYNC_TYPE_MASK                                                                           (0x0000000fU)

#define VIP_PORT_A_CTRL_CHAN_SEL_SHIFT                                                                      (4U)
#define VIP_PORT_A_CTRL_CHAN_SEL_MASK                                                                       (0x00000030U)

#define VIP_PORT_A_CLR_ASYNC_WR_FIFO_SHIFT                                                                  (6U)
#define VIP_PORT_A_CLR_ASYNC_WR_FIFO_MASK                                                                   (0x00000040U)

#define VIP_PORT_A_CLR_ASYNC_RD_FIFO_SHIFT                                                                  (7U)
#define VIP_PORT_A_CLR_ASYNC_RD_FIFO_MASK                                                                   (0x00000080U)

#define VIP_PORT_A_ENABLE_SHIFT                                                                             (8U)
#define VIP_PORT_A_ENABLE_MASK                                                                              (0x00000100U)

#define VIP_PORT_A_FID_POLARITY_SHIFT                                                                       (9U)
#define VIP_PORT_A_FID_POLARITY_MASK                                                                        (0x00000200U)

#define VIP_PORT_A_PIXCLK_EDGE_POLARITY_SHIFT                                                               (10U)
#define VIP_PORT_A_PIXCLK_EDGE_POLARITY_MASK                                                                (0x00000400U)

#define VIP_PORT_A_HSYNC_POLARITY_SHIFT                                                                     (11U)
#define VIP_PORT_A_HSYNC_POLARITY_MASK                                                                      (0x00000800U)

#define VIP_PORT_A_VSYNC_POLARITY_SHIFT                                                                     (12U)
#define VIP_PORT_A_VSYNC_POLARITY_MASK                                                                      (0x00001000U)

#define VIP_PORT_A_ACTVID_POLARITY_SHIFT                                                                    (13U)
#define VIP_PORT_A_ACTVID_POLARITY_MASK                                                                     (0x00002000U)

#define VIP_PORT_A_FID_DETECT_MODE_SHIFT                                                                    (14U)
#define VIP_PORT_A_FID_DETECT_MODE_MASK                                                                     (0x00004000U)

#define VIP_PORT_A_USE_ACTVID_HSYNC_N_SHIFT                                                                 (15U)
#define VIP_PORT_A_USE_ACTVID_HSYNC_N_MASK                                                                  (0x00008000U)

#define VIP_PORT_A_FID_SKEW_PRECOUNT_SHIFT                                                                  (16U)
#define VIP_PORT_A_FID_SKEW_PRECOUNT_MASK                                                                   (0x003f0000U)

#define VIP_PORT_A_DISCRETE_BASIC_MODE_SHIFT                                                                (22U)
#define VIP_PORT_A_DISCRETE_BASIC_MODE_MASK                                                                 (0x00400000U)

#define VIP_PORT_A_SW_RESET_SHIFT                                                                           (23U)
#define VIP_PORT_A_SW_RESET_MASK                                                                            (0x00800000U)

#define VIP_PORT_A_FID_SKEW_POSTCOUNT_SHIFT                                                                 (24U)
#define VIP_PORT_A_FID_SKEW_POSTCOUNT_MASK                                                                  (0x3f000000U)

#define VIP_PORT_A_ANALYZER_2X4X_SRCNUM_POS_SHIFT                                                           (30U)
#define VIP_PORT_A_ANALYZER_2X4X_SRCNUM_POS_MASK                                                            (0x40000000U)

#define VIP_PORT_A_ENABLE_ANALYZER_FVH_ERR_CORRECTION_SHIFT                                                 (31U)
#define VIP_PORT_A_ENABLE_ANALYZER_FVH_ERR_CORRECTION_MASK                                                  (0x80000000U)

#define VIP_XTRA_PORT_A_SRC0_NUMLINES_SHIFT                                                                 (0U)
#define VIP_XTRA_PORT_A_SRC0_NUMLINES_MASK                                                                  (0x00000fffU)

#define VIP_XTRA_PORT_A_ANC_CHAN_SEL_8B_SHIFT                                                               (13U)
#define VIP_XTRA_PORT_A_ANC_CHAN_SEL_8B_MASK                                                                (0x00006000U)

#define VIP_XTRA_PORT_A_SRC0_NUMPIX_SHIFT                                                                   (16U)
#define VIP_XTRA_PORT_A_SRC0_NUMPIX_MASK                                                                    (0x0fff0000U)

#define VIP_XTRA_PORT_A_REPACK_SEL_SHIFT                                                                    (28U)
#define VIP_XTRA_PORT_A_REPACK_SEL_MASK                                                                     (0x70000000U)

#define VIP_PORT_B_SYNC_TYPE_SHIFT                                                                          (0U)
#define VIP_PORT_B_SYNC_TYPE_MASK                                                                           (0x0000000fU)

#define VIP_PORT_B_CTRL_CHAN_SEL_SHIFT                                                                      (4U)
#define VIP_PORT_B_CTRL_CHAN_SEL_MASK                                                                       (0x00000030U)

#define VIP_PORT_B_CLR_ASYNC_FIFO_WR_SHIFT                                                                  (6U)
#define VIP_PORT_B_CLR_ASYNC_FIFO_WR_MASK                                                                   (0x00000040U)

#define VIP_PORT_B_CLR_ASYNC_FIFO_RD_SHIFT                                                                  (7U)
#define VIP_PORT_B_CLR_ASYNC_FIFO_RD_MASK                                                                   (0x00000080U)

#define VIP_PORT_B_ENABLE_SHIFT                                                                             (8U)
#define VIP_PORT_B_ENABLE_MASK                                                                              (0x00000100U)

#define VIP_PORT_B_FID_POLARITY_SHIFT                                                                       (9U)
#define VIP_PORT_B_FID_POLARITY_MASK                                                                        (0x00000200U)

#define VIP_PORT_B_PIXCLK_EDGE_POLARITY_SHIFT                                                               (10U)
#define VIP_PORT_B_PIXCLK_EDGE_POLARITY_MASK                                                                (0x00000400U)

#define VIP_PORT_B_HSYNC_POLARITY_SHIFT                                                                     (11U)
#define VIP_PORT_B_HSYNC_POLARITY_MASK                                                                      (0x00000800U)

#define VIP_PORT_B_VSYNC_POLARITY_SHIFT                                                                     (12U)
#define VIP_PORT_B_VSYNC_POLARITY_MASK                                                                      (0x00001000U)

#define VIP_PORT_B_ACTVID_POLARITY_SHIFT                                                                    (13U)
#define VIP_PORT_B_ACTVID_POLARITY_MASK                                                                     (0x00002000U)

#define VIP_PORT_B_FID_DETECT_MODE_SHIFT                                                                    (14U)
#define VIP_PORT_B_FID_DETECT_MODE_MASK                                                                     (0x00004000U)

#define VIP_PORT_B_USE_ACTVID_HSYNC_N_SHIFT                                                                 (15U)
#define VIP_PORT_B_USE_ACTVID_HSYNC_N_MASK                                                                  (0x00008000U)

#define VIP_PORT_B_FID_SKEW_PRECOUNT_SHIFT                                                                  (16U)
#define VIP_PORT_B_FID_SKEW_PRECOUNT_MASK                                                                   (0x003f0000U)

#define VIP_PORT_B_DISCRETE_BASIC_MODE_SHIFT                                                                (22U)
#define VIP_PORT_B_DISCRETE_BASIC_MODE_MASK                                                                 (0x00400000U)

#define VIP_PORT_B_SW_RESET_SHIFT                                                                           (23U)
#define VIP_PORT_B_SW_RESET_MASK                                                                            (0x00800000U)

#define VIP_PORT_B_FID_SKEW_POSTCOUNT_SHIFT                                                                 (24U)
#define VIP_PORT_B_FID_SKEW_POSTCOUNT_MASK                                                                  (0x3f000000U)

#define VIP_PORT_B_ANALYZER_2X4X_SRCNUM_POS_SHIFT                                                           (30U)
#define VIP_PORT_B_ANALYZER_2X4X_SRCNUM_POS_MASK                                                            (0x40000000U)

#define VIP_PORT_B_ENABLE_ANALYZER_FVH_ERR_CORRECTION_SHIFT                                                 (31U)
#define VIP_PORT_B_ENABLE_ANALYZER_FVH_ERR_CORRECTION_MASK                                                  (0x80000000U)

#define VIP_XTRA_PORT_B_SRC0_NUMLINES_SHIFT                                                                 (0U)
#define VIP_XTRA_PORT_B_SRC0_NUMLINES_MASK                                                                  (0x00000fffU)

#define VIP_XTRA_PORT_B_ANC_CHAN_SEL_8B_SHIFT                                                               (13U)
#define VIP_XTRA_PORT_B_ANC_CHAN_SEL_8B_MASK                                                                (0x00006000U)

#define VIP_XTRA_PORT_B_SRC0_NUMPIX_SHIFT                                                                   (16U)
#define VIP_XTRA_PORT_B_SRC0_NUMPIX_MASK                                                                    (0x0fff0000U)

#define VIP_FIQ_MASK_PORT_A_VDET_SHIFT                                                                      (0U)
#define VIP_FIQ_MASK_PORT_A_VDET_MASK                                                                       (0x00000001U)

#define VIP_FIQ_MASK_PORT_B_VDET_SHIFT                                                                      (1U)
#define VIP_FIQ_MASK_PORT_B_VDET_MASK                                                                       (0x00000002U)

#define VIP_FIQ_MASK_ASYNC_FIFO_PORT_A_OF_SHIFT                                                             (2U)
#define VIP_FIQ_MASK_ASYNC_FIFO_PORT_A_OF_MASK                                                              (0x00000004U)

#define VIP_FIQ_MASK_ASYNC_FIFO_PORT_B_OF_SHIFT                                                             (3U)
#define VIP_FIQ_MASK_ASYNC_FIFO_PORT_B_OF_MASK                                                              (0x00000008U)

#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_A_YUV_OF_SHIFT                                                        (4U)
#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_A_YUV_OF_MASK                                                         (0x00000010U)

#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_A_ANC_OF_SHIFT                                                        (6U)
#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_A_ANC_OF_MASK                                                         (0x00000040U)

#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_B_YUV_OF_SHIFT                                                        (7U)
#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_B_YUV_OF_MASK                                                         (0x00000080U)

#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_B_ANC_OF_SHIFT                                                        (9U)
#define VIP_FIQ_MASK_OUTPUT_FIFO_PORT_B_ANC_OF_MASK                                                         (0x00000200U)

#define VIP_FIQ_MASK_PORT_A_CONN_SHIFT                                                                      (10U)
#define VIP_FIQ_MASK_PORT_A_CONN_MASK                                                                       (0x00000400U)

#define VIP_FIQ_MASK_PORT_A_DISCONN_SHIFT                                                                   (11U)
#define VIP_FIQ_MASK_PORT_A_DISCONN_MASK                                                                    (0x00000800U)

#define VIP_FIQ_MASK_PORT_B_CONN_SHIFT                                                                      (12U)
#define VIP_FIQ_MASK_PORT_B_CONN_MASK                                                                       (0x00001000U)

#define VIP_FIQ_MASK_PORT_B_DISCONN_SHIFT                                                                   (13U)
#define VIP_FIQ_MASK_PORT_B_DISCONN_MASK                                                                    (0x00002000U)

#define VIP_FIQ_MASK_PORT_A_SRC0_UNEXPECTED_SIZE_SHIFT                                                      (14U)
#define VIP_FIQ_MASK_PORT_A_SRC0_UNEXPECTED_SIZE_MASK                                                       (0x00004000U)

#define VIP_FIQ_MASK_PORT_B_SRC0_UNEXPECTED_SIZE_SHIFT                                                      (15U)
#define VIP_FIQ_MASK_PORT_B_SRC0_UNEXPECTED_SIZE_MASK                                                       (0x00008000U)

#define VIP_FIQ_MASK_PORT_B_DISABLE_COMPLETE_SHIFT                                                          (21U)
#define VIP_FIQ_MASK_PORT_B_DISABLE_COMPLETE_MASK                                                           (0x00200000U)

#define VIP_FIQ_MASK_PORT_A_DISABLE_COMPLETE_SHIFT                                                          (20U)
#define VIP_FIQ_MASK_PORT_A_DISABLE_COMPLETE_MASK                                                           (0x00100000U)

#define VIP_FIQ_MASK_PORT_B_ANC_PROTOCOL_VIOLATION_SHIFT                                                    (19U)
#define VIP_FIQ_MASK_PORT_B_ANC_PROTOCOL_VIOLATION_MASK                                                     (0x00080000U)

#define VIP_FIQ_MASK_PORT_B_YUV_PROTOCOL_VIOLATION_SHIFT                                                    (18U)
#define VIP_FIQ_MASK_PORT_B_YUV_PROTOCOL_VIOLATION_MASK                                                     (0x00040000U)

#define VIP_FIQ_MASK_PORT_A_ANC_PROTOCOL_VIOLATION_SHIFT                                                    (17U)
#define VIP_FIQ_MASK_PORT_A_ANC_PROTOCOL_VIOLATION_MASK                                                     (0x00020000U)

#define VIP_FIQ_MASK_PORT_A_YUV_PROTOCOL_VIOLATION_SHIFT                                                    (16U)
#define VIP_FIQ_MASK_PORT_A_YUV_PROTOCOL_VIOLATION_MASK                                                     (0x00010000U)

#define VIP_FIQ_CLEAR_PORT_A_VDET_SHIFT                                                                     (0U)
#define VIP_FIQ_CLEAR_PORT_A_VDET_MASK                                                                      (0x00000001U)

#define VIP_FIQ_CLEAR_PORT_B_VDET_SHIFT                                                                     (1U)
#define VIP_FIQ_CLEAR_PORT_B_VDET_MASK                                                                      (0x00000002U)

#define VIP_FIQ_CLEAR_ASYNC_FIFO_PORT_A_SHIFT                                                               (2U)
#define VIP_FIQ_CLEAR_ASYNC_FIFO_PORT_A_MASK                                                                (0x00000004U)

#define VIP_FIQ_CLEAR_ASYNC_FIFO_PORT_B_SHIFT                                                               (3U)
#define VIP_FIQ_CLEAR_ASYNC_FIFO_PORT_B_MASK                                                                (0x00000008U)

#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_A_YUV_SHIFT                                                          (4U)
#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_A_YUV_MASK                                                           (0x00000010U)

#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_A_ANC_SHIFT                                                          (6U)
#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_A_ANC_MASK                                                           (0x00000040U)

#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_B_YUV_SHIFT                                                          (7U)
#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_B_YUV_MASK                                                           (0x00000080U)

#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_B_ANC_SHIFT                                                          (9U)
#define VIP_FIQ_CLEAR_OUTPUT_FIFO_PORT_B_ANC_MASK                                                           (0x00000200U)

#define VIP_FIQ_CLEAR_PORT_A_CONN_SHIFT                                                                     (10U)
#define VIP_FIQ_CLEAR_PORT_A_CONN_MASK                                                                      (0x00000400U)

#define VIP_FIQ_CLEAR_PORT_A_DISCONN_SHIFT                                                                  (11U)
#define VIP_FIQ_CLEAR_PORT_A_DISCONN_MASK                                                                   (0x00000800U)

#define VIP_FIQ_CLEAR_PORT_B_CONN_SHIFT                                                                     (12U)
#define VIP_FIQ_CLEAR_PORT_B_CONN_MASK                                                                      (0x00001000U)

#define VIP_FIQ_CLEAR_PORT_B_DISCONN_SHIFT                                                                  (13U)
#define VIP_FIQ_CLEAR_PORT_B_DISCONN_MASK                                                                   (0x00002000U)

#define VIP_FIQ_CLEAR_PORT_A_SRC0_SIZE_SHIFT                                                                (14U)
#define VIP_FIQ_CLEAR_PORT_A_SRC0_SIZE_MASK                                                                 (0x00004000U)

#define VIP_FIQ_CLEAR_PORT_B_SRC0_SIZE_SHIFT                                                                (15U)
#define VIP_FIQ_CLEAR_PORT_B_SRC0_SIZE_MASK                                                                 (0x00008000U)

#define VIP_FIQ_CLEAR_PORT_B_DISABLE_COMPLETE_SHIFT                                                         (16U)
#define VIP_FIQ_CLEAR_PORT_B_DISABLE_COMPLETE_MASK                                                          (0x00010000U)

#define VIP_FIQ_CLEAR_PORT_A_DISABLE_COMPLETE_SHIFT                                                         (17U)
#define VIP_FIQ_CLEAR_PORT_A_DISABLE_COMPLETE_MASK                                                          (0x00020000U)

#define VIP_FIQ_CLEAR_PORT_B_ANC_PROTOCOL_VIOLATION_SHIFT                                                   (18U)
#define VIP_FIQ_CLEAR_PORT_B_ANC_PROTOCOL_VIOLATION_MASK                                                    (0x00040000U)

#define VIP_FIQ_CLEAR_PORT_B_YUV_PROTOCOL_VIOLATION_SHIFT                                                   (19U)
#define VIP_FIQ_CLEAR_PORT_B_YUV_PROTOCOL_VIOLATION_MASK                                                    (0x00080000U)

#define VIP_FIQ_CLEAR_PORT_A_ANC_PROTOCOL_VIOLATION_SHIFT                                                   (20U)
#define VIP_FIQ_CLEAR_PORT_A_ANC_PROTOCOL_VIOLATION_MASK                                                    (0x00100000U)

#define VIP_FIQ_CLEAR_PORT_A_YUV_PROTOCOL_VIOLATION_SHIFT                                                   (21U)
#define VIP_FIQ_CLEAR_PORT_A_YUV_PROTOCOL_VIOLATION_MASK                                                    (0x00200000U)

#define VIP_FIQ_STATUS_PORT_A_VDET_SHIFT                                                                    (0U)
#define VIP_FIQ_STATUS_PORT_A_VDET_MASK                                                                     (0x00000001U)

#define VIP_FIQ_STATUS_PORT_B_VDET_SHIFT                                                                    (1U)
#define VIP_FIQ_STATUS_PORT_B_VDET_MASK                                                                     (0x00000002U)

#define VIP_FIQ_STATUS_ASYNC_FIFO_PORT_A_SHIFT                                                              (2U)
#define VIP_FIQ_STATUS_ASYNC_FIFO_PORT_A_MASK                                                               (0x00000004U)

#define VIP_FIQ_STATUS_ASYNC_FIFO_PORT_B_SHIFT                                                              (3U)
#define VIP_FIQ_STATUS_ASYNC_FIFO_PORT_B_MASK                                                               (0x00000008U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_LUMA_SHIFT                                                        (4U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_LUMA_MASK                                                         (0x00000010U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_CHROMA_SHIFT                                                      (5U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_CHROMA_MASK                                                       (0x00000020U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_ANC_SHIFT                                                         (6U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_A_ANC_MASK                                                          (0x00000040U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_LUMA_SHIFT                                                        (7U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_LUMA_MASK                                                         (0x00000080U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_CHROMA_SHIFT                                                      (8U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_CHROMA_MASK                                                       (0x00000100U)

#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_ANC_SHIFT                                                         (9U)
#define VIP_FIQ_STATUS_OUTPUT_FIFO_PORT_B_ANC_MASK                                                          (0x00000200U)

#define VIP_FIQ_STATUS_PORT_A_CONN_SHIFT                                                                    (10U)
#define VIP_FIQ_STATUS_PORT_A_CONN_MASK                                                                     (0x00000400U)

#define VIP_FIQ_STATUS_PORT_A_DISCONN_SHIFT                                                                 (11U)
#define VIP_FIQ_STATUS_PORT_A_DISCONN_MASK                                                                  (0x00000800U)

#define VIP_FIQ_STATUS_PORT_B_CONN_SHIFT                                                                    (12U)
#define VIP_FIQ_STATUS_PORT_B_CONN_MASK                                                                     (0x00001000U)

#define VIP_FIQ_STATUS_PORT_B_DISCONN_SHIFT                                                                 (13U)
#define VIP_FIQ_STATUS_PORT_B_DISCONN_MASK                                                                  (0x00002000U)

#define VIP_FIQ_STATUS_PORT_A_SRC0_SIZE_SHIFT                                                               (14U)
#define VIP_FIQ_STATUS_PORT_A_SRC0_SIZE_MASK                                                                (0x00004000U)

#define VIP_FIQ_STATUS_PORT_B_SRC0_SIZE_SHIFT                                                               (15U)
#define VIP_FIQ_STATUS_PORT_B_SRC0_SIZE_MASK                                                                (0x00008000U)

#define VIP_FIQ_STATUS_PORT_B_DISABLE_COMPLETE_SHIFT                                                        (21U)
#define VIP_FIQ_STATUS_PORT_B_DISABLE_COMPLETE_MASK                                                         (0x00200000U)

#define VIP_FIQ_STATUS_PORT_A_DISABLE_COMPLETE_SHIFT                                                        (20U)
#define VIP_FIQ_STATUS_PORT_A_DISABLE_COMPLETE_MASK                                                         (0x00100000U)

#define VIP_FIQ_STATUS_PORT_B_ANC_PROTOCOL_VIOLATION_SHIFT                                                  (19U)
#define VIP_FIQ_STATUS_PORT_B_ANC_PROTOCOL_VIOLATION_MASK                                                   (0x00080000U)

#define VIP_FIQ_STATUS_PORT_B_YUV_PROTOCOL_VIOLATION_SHIFT                                                  (18U)
#define VIP_FIQ_STATUS_PORT_B_YUV_PROTOCOL_VIOLATION_MASK                                                   (0x00040000U)

#define VIP_FIQ_STATUS_PORT_A_ANC_PROTOCOL_VIOLATION_SHIFT                                                  (17U)
#define VIP_FIQ_STATUS_PORT_A_ANC_PROTOCOL_VIOLATION_MASK                                                   (0x00020000U)

#define VIP_FIQ_STATUS_PORT_A_YUV_PROTOCOL_VIOLATION_SHIFT                                                  (16U)
#define VIP_FIQ_STATUS_PORT_A_YUV_PROTOCOL_VIOLATION_MASK                                                   (0x00010000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC0_PREV_SRC_FID_SHIFT                                            (0U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC0_PREV_SRC_FID_MASK                                             (0x00000001U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC0_CURR_SRC_FID_SHIFT                                            (1U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC0_CURR_SRC_FID_MASK                                             (0x00000002U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC1_PREV_SRC_FID_SHIFT                                            (2U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC1_PREV_SRC_FID_MASK                                             (0x00000004U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC1_CURR_SRC_FID_SHIFT                                            (3U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC1_CURR_SRC_FID_MASK                                             (0x00000008U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC2_PREV_SRC_FID_SHIFT                                            (4U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC2_PREV_SRC_FID_MASK                                             (0x00000010U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC2_CURR_SRC_FID_SHIFT                                            (5U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC2_CURR_SRC_FID_MASK                                             (0x00000020U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC3_PREV_SRC_FID_SHIFT                                            (6U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC3_PREV_SRC_FID_MASK                                             (0x00000040U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC3_CURR_SRC_FID_SHIFT                                            (7U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC3_CURR_SRC_FID_MASK                                             (0x00000080U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC4_PREV_SRC_FID_SHIFT                                            (8U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC4_PREV_SRC_FID_MASK                                             (0x00000100U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC4_CURR_SRC_FID_SHIFT                                            (9U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC4_CURR_SRC_FID_MASK                                             (0x00000200U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC5_PREV_SRC_FID_SHIFT                                            (10U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC5_PREV_SRC_FID_MASK                                             (0x00000400U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC5_CURR_SRC_FID_SHIFT                                            (11U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC5_CURR_SRC_FID_MASK                                             (0x00000800U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC6_PREV_SRC_FID_SHIFT                                            (12U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC6_PREV_SRC_FID_MASK                                             (0x00001000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC6_CURR_SRC_FID_SHIFT                                            (13U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC6_CURR_SRC_FID_MASK                                             (0x00002000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC7_PREV_SRC_FID_SHIFT                                            (14U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC7_PREV_SRC_FID_MASK                                             (0x00004000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC7_CURR_SRC_FID_SHIFT                                            (15U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC7_CURR_SRC_FID_MASK                                             (0x00008000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC8_PREV_SRC_FID_SHIFT                                            (16U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC8_PREV_SRC_FID_MASK                                             (0x00010000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC8_CURR_SRC_FID_SHIFT                                            (17U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC8_CURR_SRC_FID_MASK                                             (0x00020000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC9_PREV_SRC_FID_SHIFT                                            (18U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC9_PREV_SRC_FID_MASK                                             (0x00040000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC9_CURR_SRC_FID_SHIFT                                            (19U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC9_CURR_SRC_FID_MASK                                             (0x00080000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC10_PREV_SRC_FID_SHIFT                                           (20U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC10_PREV_SRC_FID_MASK                                            (0x00100000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC10_CURR_SRC_FID_SHIFT                                           (21U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC10_CURR_SRC_FID_MASK                                            (0x00200000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC11_PREV_SRC_FID_SHIFT                                           (22U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC11_PREV_SRC_FID_MASK                                            (0x00400000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC11_CURR_SRC_FID_SHIFT                                           (23U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC11_CURR_SRC_FID_MASK                                            (0x00800000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC12_PREV_SRC_FID_SHIFT                                           (24U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC12_PREV_SRC_FID_MASK                                            (0x01000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC12_CURR_SRC_FID_SHIFT                                           (25U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC12_CURR_SRC_FID_MASK                                            (0x02000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC13_PREV_SRC_FID_SHIFT                                           (26U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC13_PREV_SRC_FID_MASK                                            (0x04000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC13_CURR_SRC_FID_SHIFT                                           (27U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC13_CURR_SRC_FID_MASK                                            (0x08000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC14_PREV_SRC_FID_SHIFT                                           (28U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC14_PREV_SRC_FID_MASK                                            (0x10000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC14_CURR_SRC_FID_SHIFT                                           (29U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC14_CURR_SRC_FID_MASK                                            (0x20000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC15_PREV_SRC_FID_SHIFT                                           (30U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC15_PREV_SRC_FID_MASK                                            (0x40000000U)

#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC15_CURR_SRC_FID_SHIFT                                           (31U)
#define VIP_OUTPUT_PORT_A_SRC_FID_PORT_A_SRC15_CURR_SRC_FID_MASK                                            (0x80000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC0_PREV_SRC_FID_SHIFT                                            (0U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC0_PREV_SRC_FID_MASK                                             (0x00000001U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC0_CURR_SRC_FID_SHIFT                                            (1U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC0_CURR_SRC_FID_MASK                                             (0x00000002U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC1_PREV_SRC_FID_SHIFT                                            (2U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC1_PREV_SRC_FID_MASK                                             (0x00000004U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC1_CURR_SRC_FID_SHIFT                                            (3U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC1_CURR_SRC_FID_MASK                                             (0x00000008U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC2_PREV_SRC_FID_SHIFT                                            (4U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC2_PREV_SRC_FID_MASK                                             (0x00000010U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC2_CURR_SRC_FID_SHIFT                                            (5U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC2_CURR_SRC_FID_MASK                                             (0x00000020U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC3_PREV_SRC_FID_SHIFT                                            (6U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC3_PREV_SRC_FID_MASK                                             (0x00000040U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC3_CURR_SRC_FID_SHIFT                                            (7U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC3_CURR_SRC_FID_MASK                                             (0x00000080U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC4_PREV_SRC_FID_SHIFT                                            (8U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC4_PREV_SRC_FID_MASK                                             (0x00000100U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC4_CURR_SRC_FID_SHIFT                                            (9U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC4_CURR_SRC_FID_MASK                                             (0x00000200U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC5_PREV_SRC_FID_SHIFT                                            (10U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC5_PREV_SRC_FID_MASK                                             (0x00000400U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC5_CURR_SRC_FID_SHIFT                                            (11U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC5_CURR_SRC_FID_MASK                                             (0x00000800U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC6_PREV_SRC_FID_SHIFT                                            (12U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC6_PREV_SRC_FID_MASK                                             (0x00001000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC6_CURR_SRC_FID_SHIFT                                            (13U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC6_CURR_SRC_FID_MASK                                             (0x00002000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC7_PREV_SRC_FID_SHIFT                                            (14U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC7_PREV_SRC_FID_MASK                                             (0x00004000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC7_CURR_SRC_FID_SHIFT                                            (15U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC7_CURR_SRC_FID_MASK                                             (0x00008000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC8_PREV_SRC_FID_SHIFT                                            (16U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC8_PREV_SRC_FID_MASK                                             (0x00010000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC8_CURR_SRC_FID_SHIFT                                            (17U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC8_CURR_SRC_FID_MASK                                             (0x00020000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC9_PREV_SRC_FID_SHIFT                                            (18U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC9_PREV_SRC_FID_MASK                                             (0x00040000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC9_CURR_SRC_FID_SHIFT                                            (19U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC9_CURR_SRC_FID_MASK                                             (0x00080000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC10_PREV_SRC_FID_SHIFT                                           (20U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC10_PREV_SRC_FID_MASK                                            (0x00100000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC10_CURR_SRC_FID_SHIFT                                           (21U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC10_CURR_SRC_FID_MASK                                            (0x00200000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC11_PREV_SRC_FID_SHIFT                                           (22U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC11_PREV_SRC_FID_MASK                                            (0x00400000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC11_CURR_SRC_FID_SHIFT                                           (23U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC11_CURR_SRC_FID_MASK                                            (0x00800000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC12_PREV_SRC_FID_SHIFT                                           (24U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC12_PREV_SRC_FID_MASK                                            (0x01000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC12_CURR_SRC_FID_SHIFT                                           (25U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC12_CURR_SRC_FID_MASK                                            (0x02000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC13_PREV_SRC_FID_SHIFT                                           (26U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC13_PREV_SRC_FID_MASK                                            (0x04000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC13_CURR_SRC_FID_SHIFT                                           (27U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC13_CURR_SRC_FID_MASK                                            (0x08000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC14_PREV_SRC_FID_SHIFT                                           (28U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC14_PREV_SRC_FID_MASK                                            (0x10000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC14_CURR_SRC_FID_SHIFT                                           (29U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC14_CURR_SRC_FID_MASK                                            (0x20000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC15_PREV_SRC_FID_SHIFT                                           (30U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC15_PREV_SRC_FID_MASK                                            (0x40000000U)

#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC15_CURR_SRC_FID_SHIFT                                           (31U)
#define VIP_OUTPUT_PORT_B_SRC_FID_PORT_B_SRC15_CURR_SRC_FID_MASK                                            (0x80000000U)

#define VIP_OUTPUT_PORT_A_SRC0_SIZE_PORT_A_SRC0_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC0_SIZE_PORT_A_SRC0_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC0_SIZE_PORT_A_SRC0_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC0_SIZE_PORT_A_SRC0_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC1_SIZE_PORT_A_SRC1_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC1_SIZE_PORT_A_SRC1_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC1_SIZE_PORT_A_SRC1_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC1_SIZE_PORT_A_SRC1_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC2_SIZE_PORT_A_SRC2_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC2_SIZE_PORT_A_SRC2_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC2_SIZE_PORT_A_SRC2_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC2_SIZE_PORT_A_SRC2_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC3_SIZE_PORT_A_SRC3_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC3_SIZE_PORT_A_SRC3_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC3_SIZE_PORT_A_SRC3_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC3_SIZE_PORT_A_SRC3_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC4_SIZE_PORT_A_SRC4_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC4_SIZE_PORT_A_SRC4_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC4_SIZE_PORT_A_SRC4_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC4_SIZE_PORT_A_SRC4_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC5_SIZE_PORT_A_SRC5_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC5_SIZE_PORT_A_SRC5_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC5_SIZE_PORT_A_SRC5_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC5_SIZE_PORT_A_SRC5_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC6_SIZE_PORT_A_SRC6_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC6_SIZE_PORT_A_SRC6_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC6_SIZE_PORT_A_SRC6_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC6_SIZE_PORT_A_SRC6_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC7_SIZE_PORT_A_SRC7_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC7_SIZE_PORT_A_SRC7_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC7_SIZE_PORT_A_SRC7_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC7_SIZE_PORT_A_SRC7_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC8_SIZE_PORT_A_SRC8_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC8_SIZE_PORT_A_SRC8_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC8_SIZE_PORT_A_SRC8_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC8_SIZE_PORT_A_SRC8_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC9_SIZE_PORT_A_SRC9_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_A_SRC9_SIZE_PORT_A_SRC9_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC9_SIZE_PORT_A_SRC9_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_A_SRC9_SIZE_PORT_A_SRC9_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC10_SIZE_PORT_A_SRC10_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC10_SIZE_PORT_A_SRC10_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC10_SIZE_PORT_A_SRC10_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC10_SIZE_PORT_A_SRC10_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC11_SIZE_PORT_A_SRC11_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC11_SIZE_PORT_A_SRC11_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC11_SIZE_PORT_A_SRC11_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC11_SIZE_PORT_A_SRC11_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC12_SIZE_PORT_A_SRC12_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC12_SIZE_PORT_A_SRC12_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC12_SIZE_PORT_A_SRC12_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC12_SIZE_PORT_A_SRC12_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC13_SIZE_PORT_A_SRC13_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC13_SIZE_PORT_A_SRC13_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC13_SIZE_PORT_A_SRC13_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC13_SIZE_PORT_A_SRC13_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC14_SIZE_PORT_A_SRC14_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC14_SIZE_PORT_A_SRC14_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC14_SIZE_PORT_A_SRC14_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC14_SIZE_PORT_A_SRC14_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_A_SRC15_SIZE_PORT_A_SRC15_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_A_SRC15_SIZE_PORT_A_SRC15_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_A_SRC15_SIZE_PORT_A_SRC15_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_A_SRC15_SIZE_PORT_A_SRC15_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC0_SIZE_PORT_B_SRC0_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC0_SIZE_PORT_B_SRC0_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC0_SIZE_PORT_B_SRC0_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC0_SIZE_PORT_B_SRC0_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC1_SIZE_PORT_B_SRC1_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC1_SIZE_PORT_B_SRC1_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC1_SIZE_PORT_B_SRC1_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC1_SIZE_PORT_B_SRC1_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC2_SIZE_PORT_B_SRC2_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC2_SIZE_PORT_B_SRC2_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC2_SIZE_PORT_B_SRC2_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC2_SIZE_PORT_B_SRC2_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC3_SIZE_PORT_B_SRC3_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC3_SIZE_PORT_B_SRC3_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC3_SIZE_PORT_B_SRC3_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC3_SIZE_PORT_B_SRC3_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC4_SIZE_PORT_B_SRC4_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC4_SIZE_PORT_B_SRC4_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC4_SIZE_PORT_B_SRC4_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC4_SIZE_PORT_B_SRC4_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC5_SIZE_PORT_B_SRC5_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC5_SIZE_PORT_B_SRC5_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC5_SIZE_PORT_B_SRC5_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC5_SIZE_PORT_B_SRC5_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC6_SIZE_PORT_B_SRC6_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC6_SIZE_PORT_B_SRC6_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC6_SIZE_PORT_B_SRC6_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC6_SIZE_PORT_B_SRC6_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC7_SIZE_PORT_B_SRC7_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC7_SIZE_PORT_B_SRC7_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC7_SIZE_PORT_B_SRC7_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC7_SIZE_PORT_B_SRC7_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC8_SIZE_PORT_B_SRC8_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC8_SIZE_PORT_B_SRC8_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC8_SIZE_PORT_B_SRC8_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC8_SIZE_PORT_B_SRC8_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC9_SIZE_PORT_B_SRC9_WIDTH_SHIFT                                                 (16U)
#define VIP_OUTPUT_PORT_B_SRC9_SIZE_PORT_B_SRC9_WIDTH_MASK                                                  (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC9_SIZE_PORT_B_SRC9_HEIGHT_SHIFT                                                (0U)
#define VIP_OUTPUT_PORT_B_SRC9_SIZE_PORT_B_SRC9_HEIGHT_MASK                                                 (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC10_SIZE_PORT_B_SRC10_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC10_SIZE_PORT_B_SRC10_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC10_SIZE_PORT_B_SRC10_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC10_SIZE_PORT_B_SRC10_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC11_SIZE_PORT_B_SRC11_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC11_SIZE_PORT_B_SRC11_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC11_SIZE_PORT_B_SRC11_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC11_SIZE_PORT_B_SRC11_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC12_SIZE_PORT_B_SRC12_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC12_SIZE_PORT_B_SRC12_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC12_SIZE_PORT_B_SRC12_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC12_SIZE_PORT_B_SRC12_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC13_SIZE_PORT_B_SRC13_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC13_SIZE_PORT_B_SRC13_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC13_SIZE_PORT_B_SRC13_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC13_SIZE_PORT_B_SRC13_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC14_SIZE_PORT_B_SRC14_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC14_SIZE_PORT_B_SRC14_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC14_SIZE_PORT_B_SRC14_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC14_SIZE_PORT_B_SRC14_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_OUTPUT_PORT_B_SRC15_SIZE_PORT_B_SRC15_WIDTH_SHIFT                                               (16U)
#define VIP_OUTPUT_PORT_B_SRC15_SIZE_PORT_B_SRC15_WIDTH_MASK                                                (0x07ff0000U)

#define VIP_OUTPUT_PORT_B_SRC15_SIZE_PORT_B_SRC15_HEIGHT_SHIFT                                              (0U)
#define VIP_OUTPUT_PORT_B_SRC15_SIZE_PORT_B_SRC15_HEIGHT_MASK                                               (0x000007ffU)

#define VIP_PORT_A_VDET_VEC_PORT_A_VDET_VEC_SHIFT                                                           (0U)
#define VIP_PORT_A_VDET_VEC_PORT_A_VDET_VEC_MASK                                                            (0xffffffffU)

#define VIP_PORT_B_VDET_VEC_PORT_B_VDET_VEC_SHIFT                                                           (0U)
#define VIP_PORT_B_VDET_VEC_PORT_B_VDET_VEC_MASK                                                            (0xffffffffU)

#define VIP_ANC_CROP_HORZ_PORT_A_ANC_SKIP_NUMPIX_SHIFT                                                      (0U)
#define VIP_ANC_CROP_HORZ_PORT_A_ANC_SKIP_NUMPIX_MASK                                                       (0x00000fffU)

#define VIP_ANC_CROP_HORZ_PORT_A_ANC_BYPASS_N_SHIFT                                                         (15U)
#define VIP_ANC_CROP_HORZ_PORT_A_ANC_BYPASS_N_MASK                                                          (0x00008000U)

#define VIP_ANC_CROP_HORZ_PORT_A_ANC_USE_NUMPIX_SHIFT                                                       (16U)
#define VIP_ANC_CROP_HORZ_PORT_A_ANC_USE_NUMPIX_MASK                                                        (0x0fff0000U)

#define VIP_ANC_CROP_HORZ_PORT_A_ANC_TARGET_SRCNUM_SHIFT                                                    (28U)
#define VIP_ANC_CROP_HORZ_PORT_A_ANC_TARGET_SRCNUM_MASK                                                     (0xf0000000U)

#define VIP_ANC_CROP_VERT_PORT_A_ANC_SKIP_NUMLINES_SHIFT                                                    (0U)
#define VIP_ANC_CROP_VERT_PORT_A_ANC_SKIP_NUMLINES_MASK                                                     (0x00000fffU)

#define VIP_ANC_CROP_VERT_PORT_A_ANC_USE_NUMLINES_SHIFT                                                     (16U)
#define VIP_ANC_CROP_VERT_PORT_A_ANC_USE_NUMLINES_MASK                                                      (0x0fff0000U)

#define VIP_CROP_HORZ_PORT_A_ACT_SKIP_NUMPIX_SHIFT                                                          (0U)
#define VIP_CROP_HORZ_PORT_A_ACT_SKIP_NUMPIX_MASK                                                           (0x00000fffU)

#define VIP_CROP_HORZ_PORT_A_ACT_BYPASS_N_SHIFT                                                             (15U)
#define VIP_CROP_HORZ_PORT_A_ACT_BYPASS_N_MASK                                                              (0x00008000U)

#define VIP_CROP_HORZ_PORT_A_ACT_USE_NUMPIX_SHIFT                                                           (16U)
#define VIP_CROP_HORZ_PORT_A_ACT_USE_NUMPIX_MASK                                                            (0x0fff0000U)

#define VIP_CROP_HORZ_PORT_A_ACT_TARGET_SRCNUM_SHIFT                                                        (28U)
#define VIP_CROP_HORZ_PORT_A_ACT_TARGET_SRCNUM_MASK                                                         (0xf0000000U)

#define VIP_CROP_VERT_PORT_A_ACT_SKIP_NUMLINES_SHIFT                                                        (0U)
#define VIP_CROP_VERT_PORT_A_ACT_SKIP_NUMLINES_MASK                                                         (0x00000fffU)

#define VIP_CROP_VERT_PORT_A_ACT_USE_NUMLINES_SHIFT                                                         (16U)
#define VIP_CROP_VERT_PORT_A_ACT_USE_NUMLINES_MASK                                                          (0x0fff0000U)

#define VIP_ANC_CROP_HORZ_PORT_B_ANC_SKIP_NUMPIX_SHIFT                                                      (0U)
#define VIP_ANC_CROP_HORZ_PORT_B_ANC_SKIP_NUMPIX_MASK                                                       (0x00000fffU)

#define VIP_ANC_CROP_HORZ_PORT_B_ANC_BYPASS_N_SHIFT                                                         (15U)
#define VIP_ANC_CROP_HORZ_PORT_B_ANC_BYPASS_N_MASK                                                          (0x00008000U)

#define VIP_ANC_CROP_HORZ_PORT_B_ANC_USE_NUMPIX_SHIFT                                                       (16U)
#define VIP_ANC_CROP_HORZ_PORT_B_ANC_USE_NUMPIX_MASK                                                        (0x0fff0000U)

#define VIP_ANC_CROP_HORZ_PORT_B_ANC_TARGET_SRCNUM_SHIFT                                                    (28U)
#define VIP_ANC_CROP_HORZ_PORT_B_ANC_TARGET_SRCNUM_MASK                                                     (0xf0000000U)

#define VIP_ANC_CROP_VERT_PORT_B_ANC_SKIP_NUMLINES_SHIFT                                                    (0U)
#define VIP_ANC_CROP_VERT_PORT_B_ANC_SKIP_NUMLINES_MASK                                                     (0x00000fffU)

#define VIP_ANC_CROP_VERT_PORT_B_ANC_USE_NUMLINES_SHIFT                                                     (16U)
#define VIP_ANC_CROP_VERT_PORT_B_ANC_USE_NUMLINES_MASK                                                      (0x0fff0000U)

#define VIP_CROP_HORZ_PORT_B_ACT_SKIP_NUMPIX_SHIFT                                                          (0U)
#define VIP_CROP_HORZ_PORT_B_ACT_SKIP_NUMPIX_MASK                                                           (0x00000fffU)

#define VIP_CROP_HORZ_PORT_B_ACT_BYPASS_N_SHIFT                                                             (15U)
#define VIP_CROP_HORZ_PORT_B_ACT_BYPASS_N_MASK                                                              (0x00008000U)

#define VIP_CROP_HORZ_PORT_B_ACT_USE_NUMPIX_SHIFT                                                           (16U)
#define VIP_CROP_HORZ_PORT_B_ACT_USE_NUMPIX_MASK                                                            (0x0fff0000U)

#define VIP_CROP_HORZ_PORT_B_ACT_TARGET_SRCNUM_SHIFT                                                        (28U)
#define VIP_CROP_HORZ_PORT_B_ACT_TARGET_SRCNUM_MASK                                                         (0xf0000000U)

#define VIP_CROP_VERT_PORT_B_ACT_SKIP_NUMLINES_SHIFT                                                        (0U)
#define VIP_CROP_VERT_PORT_B_ACT_SKIP_NUMLINES_MASK                                                         (0x00000fffU)

#define VIP_CROP_VERT_PORT_B_ACT_USE_NUMLINES_SHIFT                                                         (16U)
#define VIP_CROP_VERT_PORT_B_ACT_USE_NUMLINES_MASK                                                          (0x0fff0000U)

#define VIP_STOP_IMMEDIATE_PORT_A_ANC_SRCNUM_STOP_IMMEDIATELY_SHIFT                                         (0U)
#define VIP_STOP_IMMEDIATE_PORT_A_ANC_SRCNUM_STOP_IMMEDIATELY_MASK                                          (0x0000ffffU)

#define VIP_STOP_IMMEDIATE_PORT_A_YUV_SRCNUM_STOP_IMMEDIATELY_SHIFT                                         (16U)
#define VIP_STOP_IMMEDIATE_PORT_A_YUV_SRCNUM_STOP_IMMEDIATELY_MASK                                          (0xffff0000U)

#define VIP_STOP_IMMEDIATE_PORT_B_ANC_SRCNUM_STOP_IMMEDIATELY_SHIFT                                         (0U)
#define VIP_STOP_IMMEDIATE_PORT_B_ANC_SRCNUM_STOP_IMMEDIATELY_MASK                                          (0x0000ffffU)

#define VIP_STOP_IMMEDIATE_PORT_B_YUV_SRCNUM_STOP_IMMEDIATELY_SHIFT                                         (16U)
#define VIP_STOP_IMMEDIATE_PORT_B_YUV_SRCNUM_STOP_IMMEDIATELY_MASK                                          (0xffff0000U)

#define VIP_XTRA8_PORT_A_RESERVED_SHIFT                                                                     (0U)
#define VIP_XTRA8_PORT_A_RESERVED_MASK                                                                      (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_VIP_PARSER_H_ */
