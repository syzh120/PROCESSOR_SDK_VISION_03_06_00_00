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
 *  \file       hw_dei.h
 *
 *  \brief      register-level header file for DEI
 *
**/

#ifndef HW_DEI_H_
#define HW_DEI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DEI_REG0                                                                                            (0x0U)
#define DEI_REG1                                                                                            (0x4U)
#define DEI_REG2                                                                                            (0x8U)
#define DEI_REG3                                                                                            (0xcU)
#define DEI_REG4                                                                                            (0x10U)
#define DEI_REG5                                                                                            (0x14U)
#define DEI_REG6                                                                                            (0x18U)
#define DEI_REG7                                                                                            (0x1cU)
#define DEI_REG8                                                                                            (0x20U)
#define DEI_REG9                                                                                            (0x24U)
#define DEI_REG10                                                                                           (0x28U)
#define DEI_REG11                                                                                           (0x2cU)
#define DEI_REG12                                                                                           (0x30U)
#define DEI_REG13                                                                                           (0x34U)
#define DEI_REG14                                                                                           (0x38U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DEI_REG0_INTERLACE_BYPASS_SHIFT                                                                     (29U)
#define DEI_REG0_INTERLACE_BYPASS_MASK                                                                      (0x20000000U)

#define DEI_REG0_HEIGHT_SHIFT                                                                               (16U)
#define DEI_REG0_HEIGHT_MASK                                                                                (0x07ff0000U)

#define DEI_REG0_WIDTH_SHIFT                                                                                (0U)
#define DEI_REG0_WIDTH_MASK                                                                                 (0x000007ffU)

#define DEI_REG0_FIELD_FLUSH_SHIFT                                                                          (30U)
#define DEI_REG0_FIELD_FLUSH_MASK                                                                           (0x40000000U)

#define DEI_REG0_PROGRESSIVE_BYPASS_SHIFT                                                                   (31U)
#define DEI_REG0_PROGRESSIVE_BYPASS_MASK                                                                    (0x80000000U)

#define DEI_REG1_MDT_SPATMAX_BYPASS_SHIFT                                                                   (1U)
#define DEI_REG1_MDT_SPATMAX_BYPASS_MASK                                                                    (0x00000002U)

#define DEI_REG1_MDT_TEMPMAX_BYPASS_SHIFT                                                                   (0U)
#define DEI_REG1_MDT_TEMPMAX_BYPASS_MASK                                                                    (0x00000001U)

#define DEI_REG2_MDT_MVSTMAX_COR_THR_SHIFT                                                                  (28U)
#define DEI_REG2_MDT_MVSTMAX_COR_THR_MASK                                                                   (0xf0000000U)

#define DEI_REG2_MDT_MV_COR_THR_SHIFT                                                                       (24U)
#define DEI_REG2_MDT_MV_COR_THR_MASK                                                                        (0x0f000000U)

#define DEI_REG2_MDT_SF_SC_THR3_SHIFT                                                                       (16U)
#define DEI_REG2_MDT_SF_SC_THR3_MASK                                                                        (0x00ff0000U)

#define DEI_REG2_MDT_SF_SC_THR2_SHIFT                                                                       (8U)
#define DEI_REG2_MDT_SF_SC_THR2_MASK                                                                        (0x0000ff00U)

#define DEI_REG2_MDT_SF_SC_THR1_SHIFT                                                                       (0U)
#define DEI_REG2_MDT_SF_SC_THR1_MASK                                                                        (0x000000ffU)

#define DEI_REG3_EDI_COR_SCALE_FACTOR_SHIFT                                                                 (24U)
#define DEI_REG3_EDI_COR_SCALE_FACTOR_MASK                                                                  (0xff000000U)

#define DEI_REG3_EDI_DIR_COR_LOWER_THR_SHIFT                                                                (16U)
#define DEI_REG3_EDI_DIR_COR_LOWER_THR_MASK                                                                 (0x00ff0000U)

#define DEI_REG3_EDI_CHROMA3D_COR_THR_SHIFT                                                                 (8U)
#define DEI_REG3_EDI_CHROMA3D_COR_THR_MASK                                                                  (0x0000ff00U)

#define DEI_REG3_EDI_CHROMA_3D_ENABLE_SHIFT                                                                 (3U)
#define DEI_REG3_EDI_CHROMA_3D_ENABLE_MASK                                                                  (0x00000008U)

#define DEI_REG3_EDI_ENABLE_3D_SHIFT                                                                        (2U)
#define DEI_REG3_EDI_ENABLE_3D_MASK                                                                         (0x00000004U)

#define DEI_REG3_EDI_INP_MODE_SHIFT                                                                         (0U)
#define DEI_REG3_EDI_INP_MODE_MASK                                                                          (0x00000003U)

#define DEI_REG4_EDI_LUT3_SHIFT                                                                             (24U)
#define DEI_REG4_EDI_LUT3_MASK                                                                              (0x1f000000U)

#define DEI_REG4_EDI_LUT2_SHIFT                                                                             (16U)
#define DEI_REG4_EDI_LUT2_MASK                                                                              (0x001f0000U)

#define DEI_REG4_EDI_LUT1_SHIFT                                                                             (8U)
#define DEI_REG4_EDI_LUT1_MASK                                                                              (0x00001f00U)

#define DEI_REG4_EDI_LUT0_SHIFT                                                                             (0U)
#define DEI_REG4_EDI_LUT0_MASK                                                                              (0x0000001fU)

#define DEI_REG5_EDI_LUT7_SHIFT                                                                             (24U)
#define DEI_REG5_EDI_LUT7_MASK                                                                              (0x1f000000U)

#define DEI_REG5_EDI_LUT6_SHIFT                                                                             (16U)
#define DEI_REG5_EDI_LUT6_MASK                                                                              (0x001f0000U)

#define DEI_REG5_EDI_LUT5_SHIFT                                                                             (8U)
#define DEI_REG5_EDI_LUT5_MASK                                                                              (0x00001f00U)

#define DEI_REG5_EDI_LUT4_SHIFT                                                                             (0U)
#define DEI_REG5_EDI_LUT4_MASK                                                                              (0x0000001fU)

#define DEI_REG6_EDI_LUT11_SHIFT                                                                            (24U)
#define DEI_REG6_EDI_LUT11_MASK                                                                             (0x1f000000U)

#define DEI_REG6_EDI_LUT10_SHIFT                                                                            (16U)
#define DEI_REG6_EDI_LUT10_MASK                                                                             (0x001f0000U)

#define DEI_REG6_EDI_LUT9_SHIFT                                                                             (8U)
#define DEI_REG6_EDI_LUT9_MASK                                                                              (0x00001f00U)

#define DEI_REG6_EDI_LUT8_SHIFT                                                                             (0U)
#define DEI_REG6_EDI_LUT8_MASK                                                                              (0x0000001fU)

#define DEI_REG7_EDI_LUT15_SHIFT                                                                            (24U)
#define DEI_REG7_EDI_LUT15_MASK                                                                             (0x1f000000U)

#define DEI_REG7_EDI_LUT14_SHIFT                                                                            (16U)
#define DEI_REG7_EDI_LUT14_MASK                                                                             (0x001f0000U)

#define DEI_REG7_EDI_LUT13_SHIFT                                                                            (8U)
#define DEI_REG7_EDI_LUT13_MASK                                                                             (0x00001f00U)

#define DEI_REG7_EDI_LUT12_SHIFT                                                                            (0U)
#define DEI_REG7_EDI_LUT12_MASK                                                                             (0x0000001fU)

#define DEI_REG8_FMD_WINDOW_ENABLE_SHIFT                                                                    (31U)
#define DEI_REG8_FMD_WINDOW_ENABLE_MASK                                                                     (0x80000000U)

#define DEI_REG8_FMD_WINDOW_MAXX_SHIFT                                                                      (16U)
#define DEI_REG8_FMD_WINDOW_MAXX_MASK                                                                       (0x07ff0000U)

#define DEI_REG8_FMD_WINDOW_MINX_SHIFT                                                                      (0U)
#define DEI_REG8_FMD_WINDOW_MINX_MASK                                                                       (0x000007ffU)

#define DEI_REG9_FMD_WINDOW_MAXY_SHIFT                                                                      (16U)
#define DEI_REG9_FMD_WINDOW_MAXY_MASK                                                                       (0x07ff0000U)

#define DEI_REG9_FMD_WINDOW_MINY_SHIFT                                                                      (0U)
#define DEI_REG9_FMD_WINDOW_MINY_MASK                                                                       (0x000007ffU)

#define DEI_REG10_FMD_CAF_LINE_THR_SHIFT                                                                    (24U)
#define DEI_REG10_FMD_CAF_LINE_THR_MASK                                                                     (0xff000000U)

#define DEI_REG10_FMD_CAF_FIELD_THR_SHIFT                                                                   (16U)
#define DEI_REG10_FMD_CAF_FIELD_THR_MASK                                                                    (0x00ff0000U)

#define DEI_REG10_FMD_BED_ENABLE_SHIFT                                                                      (3U)
#define DEI_REG10_FMD_BED_ENABLE_MASK                                                                       (0x00000008U)

#define DEI_REG10_FMD_JAM_DIR_SHIFT                                                                         (2U)
#define DEI_REG10_FMD_JAM_DIR_MASK                                                                          (0x00000004U)

#define DEI_REG10_FMD_LOCK_SHIFT                                                                            (1U)
#define DEI_REG10_FMD_LOCK_MASK                                                                             (0x00000002U)

#define DEI_REG10_FMD_ENABLE_SHIFT                                                                          (0U)
#define DEI_REG10_FMD_ENABLE_MASK                                                                           (0x00000001U)

#define DEI_REG11_FMD_CAF_THR_SHIFT                                                                         (0U)
#define DEI_REG11_FMD_CAF_THR_MASK                                                                          (0x000fffffU)

#define DEI_REG12_FMD_RESET_SHIFT                                                                           (24U)
#define DEI_REG12_FMD_RESET_MASK                                                                            (0x01000000U)

#define DEI_REG12_FMD_CAF_SHIFT                                                                             (0U)
#define DEI_REG12_FMD_CAF_MASK                                                                              (0x001fffffU)

#define DEI_REG13_FMD_FIELD_DIFF_SHIFT                                                                      (0U)
#define DEI_REG13_FMD_FIELD_DIFF_MASK                                                                       (0x0fffffffU)

#define DEI_REG14_FMD_FRAME_DIFF_SHIFT                                                                      (0U)
#define DEI_REG14_FMD_FRAME_DIFF_MASK                                                                       (0x000fffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DEI_H_ */

