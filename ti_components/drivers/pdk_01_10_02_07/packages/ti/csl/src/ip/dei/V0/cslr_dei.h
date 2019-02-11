/********************************************************************
 * Copyright (C) 2013-2015 Texas Instruments Incorporated.
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
#ifndef CSLR_DEI_H_
#define CSLR_DEI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>

/**************************************************************************
* Register Overlay Structure for mmr_generated_address_block
**************************************************************************/
typedef struct {
    volatile Uint32 REG0;
    volatile Uint32 REG1;
    volatile Uint32 REG2;
    volatile Uint32 REG3;
    volatile Uint32 REG4;
    volatile Uint32 REG5;
    volatile Uint32 REG6;
    volatile Uint32 REG7;
    volatile Uint32 REG8;
    volatile Uint32 REG9;
    volatile Uint32 REG10;
    volatile Uint32 REG11;
    volatile Uint32 REG12;
    volatile Uint32 REG13;
    volatile Uint32 REG14;
} CSL_DeiRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_DEI_REG0                                            (0x0U)
#define CSL_DEI_REG1                                            (0x4U)
#define CSL_DEI_REG2                                            (0x8U)
#define CSL_DEI_REG3                                            (0xCU)
#define CSL_DEI_REG4                                            (0x10U)
#define CSL_DEI_REG5                                            (0x14U)
#define CSL_DEI_REG6                                            (0x18U)
#define CSL_DEI_REG7                                            (0x1CU)
#define CSL_DEI_REG8                                            (0x20U)
#define CSL_DEI_REG9                                            (0x24U)
#define CSL_DEI_REG10                                           (0x28U)
#define CSL_DEI_REG11                                           (0x2CU)
#define CSL_DEI_REG12                                           (0x30U)
#define CSL_DEI_REG13                                           (0x34U)
#define CSL_DEI_REG14                                           (0x38U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REG0 */

#define CSL_DEI_REG0_INTERLACE_BYPASS_MASK                      (0x20000000U)
#define CSL_DEI_REG0_INTERLACE_BYPASS_SHIFT                     (29U)
#define CSL_DEI_REG0_INTERLACE_BYPASS_RESETVAL                  (0x00000000U)
#define CSL_DEI_REG0_INTERLACE_BYPASS_MAX                       (0x00000001U)

#define CSL_DEI_REG0_HEIGHT_MASK                                (0x07FF0000U)
#define CSL_DEI_REG0_HEIGHT_SHIFT                               (16U)
#define CSL_DEI_REG0_HEIGHT_RESETVAL                            (0x000001e0U)
#define CSL_DEI_REG0_HEIGHT_MAX                                 (0x000007ffU)

#define CSL_DEI_REG0_WIDTH_MASK                                 (0x000007FFU)
#define CSL_DEI_REG0_WIDTH_SHIFT                                (0U)
#define CSL_DEI_REG0_WIDTH_RESETVAL                             (0x000002d0U)
#define CSL_DEI_REG0_WIDTH_MAX                                  (0x000007ffU)

#define CSL_DEI_REG0_FIELD_FLUSH_MASK                           (0x40000000U)
#define CSL_DEI_REG0_FIELD_FLUSH_SHIFT                          (30U)
#define CSL_DEI_REG0_FIELD_FLUSH_RESETVAL                       (0x00000000U)
#define CSL_DEI_REG0_FIELD_FLUSH_MAX                            (0x00000001U)

#define CSL_DEI_REG0_RESETVAL                                   (0x01e002d0U)

/* REG1 */

#define CSL_DEI_REG1_MDT_SPATMAX_BYPASS_MASK                    (0x00000002U)
#define CSL_DEI_REG1_MDT_SPATMAX_BYPASS_SHIFT                   (1U)
#define CSL_DEI_REG1_MDT_SPATMAX_BYPASS_RESETVAL                (0x00000000U)
#define CSL_DEI_REG1_MDT_SPATMAX_BYPASS_MAX                     (0x00000001U)

#define CSL_DEI_REG1_MDT_TEMPMAX_BYPASS_MASK                    (0x00000001U)
#define CSL_DEI_REG1_MDT_TEMPMAX_BYPASS_SHIFT                   (0U)
#define CSL_DEI_REG1_MDT_TEMPMAX_BYPASS_RESETVAL                (0x00000000U)
#define CSL_DEI_REG1_MDT_TEMPMAX_BYPASS_MAX                     (0x00000001U)

#define CSL_DEI_REG1_RESETVAL                                   (0x00000000U)

/* REG2 */

#define CSL_DEI_REG2_MDT_MVSTMAX_COR_THR_MASK                   (0xF0000000U)
#define CSL_DEI_REG2_MDT_MVSTMAX_COR_THR_SHIFT                  (28U)
#define CSL_DEI_REG2_MDT_MVSTMAX_COR_THR_RESETVAL               (0x00000000U)
#define CSL_DEI_REG2_MDT_MVSTMAX_COR_THR_MAX                    (0x0000000fU)

#define CSL_DEI_REG2_MDT_MV_COR_THR_MASK                        (0x0F000000U)
#define CSL_DEI_REG2_MDT_MV_COR_THR_SHIFT                       (24U)
#define CSL_DEI_REG2_MDT_MV_COR_THR_RESETVAL                    (0x0000000cU)
#define CSL_DEI_REG2_MDT_MV_COR_THR_MAX                         (0x0000000fU)

#define CSL_DEI_REG2_MDT_SF_SC_THR3_MASK                        (0x00FF0000U)
#define CSL_DEI_REG2_MDT_SF_SC_THR3_SHIFT                       (16U)
#define CSL_DEI_REG2_MDT_SF_SC_THR3_RESETVAL                    (0x0000000cU)
#define CSL_DEI_REG2_MDT_SF_SC_THR3_MAX                         (0x000000ffU)

#define CSL_DEI_REG2_MDT_SF_SC_THR2_MASK                        (0x0000FF00U)
#define CSL_DEI_REG2_MDT_SF_SC_THR2_SHIFT                       (8U)
#define CSL_DEI_REG2_MDT_SF_SC_THR2_RESETVAL                    (0x00000008U)
#define CSL_DEI_REG2_MDT_SF_SC_THR2_MAX                         (0x000000ffU)

#define CSL_DEI_REG2_MDT_SF_SC_THR1_MASK                        (0x000000FFU)
#define CSL_DEI_REG2_MDT_SF_SC_THR1_SHIFT                       (0U)
#define CSL_DEI_REG2_MDT_SF_SC_THR1_RESETVAL                    (0x00000004U)
#define CSL_DEI_REG2_MDT_SF_SC_THR1_MAX                         (0x000000ffU)

#define CSL_DEI_REG2_RESETVAL                                   (0x0c0c0804U)

/* REG3 */

#define CSL_DEI_REG3_EDI_COR_SCALE_FACTOR_MASK                  (0xFF000000U)
#define CSL_DEI_REG3_EDI_COR_SCALE_FACTOR_SHIFT                 (24U)
#define CSL_DEI_REG3_EDI_COR_SCALE_FACTOR_RESETVAL              (0x00000001U)
#define CSL_DEI_REG3_EDI_COR_SCALE_FACTOR_MAX                   (0x000000ffU)

#define CSL_DEI_REG3_EDI_DIR_COR_LOWER_THR_MASK                 (0x00FF0000U)
#define CSL_DEI_REG3_EDI_DIR_COR_LOWER_THR_SHIFT                (16U)
#define CSL_DEI_REG3_EDI_DIR_COR_LOWER_THR_RESETVAL             (0x00000018U)
#define CSL_DEI_REG3_EDI_DIR_COR_LOWER_THR_MAX                  (0x000000ffU)

#define CSL_DEI_REG3_EDI_CHROMA3D_COR_THR_MASK                  (0x0000FF00U)
#define CSL_DEI_REG3_EDI_CHROMA3D_COR_THR_SHIFT                 (8U)
#define CSL_DEI_REG3_EDI_CHROMA3D_COR_THR_RESETVAL              (0x00000010U)
#define CSL_DEI_REG3_EDI_CHROMA3D_COR_THR_MAX                   (0x000000ffU)

#define CSL_DEI_REG3_EDI_CHROMA_3D_EN_MASK                      (0x00000008U)
#define CSL_DEI_REG3_EDI_CHROMA_3D_EN_SHIFT                     (3U)
#define CSL_DEI_REG3_EDI_CHROMA_3D_EN_RESETVAL                  (0x00000001U)
#define CSL_DEI_REG3_EDI_CHROMA_3D_EN_MAX                       (0x00000001U)

#define CSL_DEI_REG3_EDI_EN_3D_MASK                             (0x00000004U)
#define CSL_DEI_REG3_EDI_EN_3D_SHIFT                            (2U)
#define CSL_DEI_REG3_EDI_EN_3D_RESETVAL                         (0x00000001U)
#define CSL_DEI_REG3_EDI_EN_3D_MAX                              (0x00000001U)

#define CSL_DEI_REG3_EDI_INP_MODE_MASK                          (0x00000003U)
#define CSL_DEI_REG3_EDI_INP_MODE_SHIFT                         (0U)
#define CSL_DEI_REG3_EDI_INP_MODE_RESETVAL                      (0x00000003U)
#define CSL_DEI_REG3_EDI_INP_MODE_MAX                           (0x00000003U)

#define CSL_DEI_REG3_RESETVAL                                   (0x0118100fU)

/* REG4 */

#define CSL_DEI_REG4_EDI_LUT3_MASK                              (0x1F000000U)
#define CSL_DEI_REG4_EDI_LUT3_SHIFT                             (24U)
#define CSL_DEI_REG4_EDI_LUT3_RESETVAL                          (0x00000008U)
#define CSL_DEI_REG4_EDI_LUT3_MAX                               (0x0000001fU)

#define CSL_DEI_REG4_EDI_LUT2_MASK                              (0x001F0000U)
#define CSL_DEI_REG4_EDI_LUT2_SHIFT                             (16U)
#define CSL_DEI_REG4_EDI_LUT2_RESETVAL                          (0x00000004U)
#define CSL_DEI_REG4_EDI_LUT2_MAX                               (0x0000001fU)

#define CSL_DEI_REG4_EDI_LUT1_MASK                              (0x00001F00U)
#define CSL_DEI_REG4_EDI_LUT1_SHIFT                             (8U)
#define CSL_DEI_REG4_EDI_LUT1_RESETVAL                          (0x00000002U)
#define CSL_DEI_REG4_EDI_LUT1_MAX                               (0x0000001fU)

#define CSL_DEI_REG4_EDI_LUT0_MASK                              (0x0000001FU)
#define CSL_DEI_REG4_EDI_LUT0_SHIFT                             (0U)
#define CSL_DEI_REG4_EDI_LUT0_RESETVAL                          (0x00000000U)
#define CSL_DEI_REG4_EDI_LUT0_MAX                               (0x0000001fU)

#define CSL_DEI_REG4_RESETVAL                                   (0x08040200U)

/* REG5 */

#define CSL_DEI_REG5_EDI_LUT7_MASK                              (0x1F000000U)
#define CSL_DEI_REG5_EDI_LUT7_SHIFT                             (24U)
#define CSL_DEI_REG5_EDI_LUT7_RESETVAL                          (0x00000010U)
#define CSL_DEI_REG5_EDI_LUT7_MAX                               (0x0000001fU)

#define CSL_DEI_REG5_EDI_LUT6_MASK                              (0x001F0000U)
#define CSL_DEI_REG5_EDI_LUT6_SHIFT                             (16U)
#define CSL_DEI_REG5_EDI_LUT6_RESETVAL                          (0x00000010U)
#define CSL_DEI_REG5_EDI_LUT6_MAX                               (0x0000001fU)

#define CSL_DEI_REG5_EDI_LUT5_MASK                              (0x00001F00U)
#define CSL_DEI_REG5_EDI_LUT5_SHIFT                             (8U)
#define CSL_DEI_REG5_EDI_LUT5_RESETVAL                          (0x00000010U)
#define CSL_DEI_REG5_EDI_LUT5_MAX                               (0x0000001fU)

#define CSL_DEI_REG5_EDI_LUT4_MASK                              (0x0000001FU)
#define CSL_DEI_REG5_EDI_LUT4_SHIFT                             (0U)
#define CSL_DEI_REG5_EDI_LUT4_RESETVAL                          (0x0000000cU)
#define CSL_DEI_REG5_EDI_LUT4_MAX                               (0x0000001fU)

#define CSL_DEI_REG5_RESETVAL                                   (0x1010100cU)

/* REG6 */

#define CSL_DEI_REG6_EDI_LUT11_MASK                             (0x1F000000U)
#define CSL_DEI_REG6_EDI_LUT11_SHIFT                            (24U)
#define CSL_DEI_REG6_EDI_LUT11_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG6_EDI_LUT11_MAX                              (0x0000001fU)

#define CSL_DEI_REG6_EDI_LUT10_MASK                             (0x001F0000U)
#define CSL_DEI_REG6_EDI_LUT10_SHIFT                            (16U)
#define CSL_DEI_REG6_EDI_LUT10_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG6_EDI_LUT10_MAX                              (0x0000001fU)

#define CSL_DEI_REG6_EDI_LUT9_MASK                              (0x00001F00U)
#define CSL_DEI_REG6_EDI_LUT9_SHIFT                             (8U)
#define CSL_DEI_REG6_EDI_LUT9_RESETVAL                          (0x00000010U)
#define CSL_DEI_REG6_EDI_LUT9_MAX                               (0x0000001fU)

#define CSL_DEI_REG6_EDI_LUT8_MASK                              (0x0000001FU)
#define CSL_DEI_REG6_EDI_LUT8_SHIFT                             (0U)
#define CSL_DEI_REG6_EDI_LUT8_RESETVAL                          (0x00000010U)
#define CSL_DEI_REG6_EDI_LUT8_MAX                               (0x0000001fU)

#define CSL_DEI_REG6_RESETVAL                                   (0x10101010U)

/* REG7 */

#define CSL_DEI_REG7_EDI_LUT15_MASK                             (0x1F000000U)
#define CSL_DEI_REG7_EDI_LUT15_SHIFT                            (24U)
#define CSL_DEI_REG7_EDI_LUT15_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG7_EDI_LUT15_MAX                              (0x0000001fU)

#define CSL_DEI_REG7_EDI_LUT14_MASK                             (0x001F0000U)
#define CSL_DEI_REG7_EDI_LUT14_SHIFT                            (16U)
#define CSL_DEI_REG7_EDI_LUT14_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG7_EDI_LUT14_MAX                              (0x0000001fU)

#define CSL_DEI_REG7_EDI_LUT13_MASK                             (0x00001F00U)
#define CSL_DEI_REG7_EDI_LUT13_SHIFT                            (8U)
#define CSL_DEI_REG7_EDI_LUT13_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG7_EDI_LUT13_MAX                              (0x0000001fU)

#define CSL_DEI_REG7_EDI_LUT12_MASK                             (0x0000001FU)
#define CSL_DEI_REG7_EDI_LUT12_SHIFT                            (0U)
#define CSL_DEI_REG7_EDI_LUT12_RESETVAL                         (0x00000010U)
#define CSL_DEI_REG7_EDI_LUT12_MAX                              (0x0000001fU)

#define CSL_DEI_REG7_RESETVAL                                   (0x10101010U)

/* REG8 */

#define CSL_DEI_REG8_FMD_WINDOW_EN_MASK                         (0x80000000U)
#define CSL_DEI_REG8_FMD_WINDOW_EN_SHIFT                        (31U)
#define CSL_DEI_REG8_FMD_WINDOW_EN_RESETVAL                     (0x00000001U)
#define CSL_DEI_REG8_FMD_WINDOW_EN_MAX                          (0x00000001U)

#define CSL_DEI_REG8_FMD_WINDOW_MAXX_MASK                       (0x07FF0000U)
#define CSL_DEI_REG8_FMD_WINDOW_MAXX_SHIFT                      (16U)
#define CSL_DEI_REG8_FMD_WINDOW_MAXX_RESETVAL                   (0x000002cfU)
#define CSL_DEI_REG8_FMD_WINDOW_MAXX_MAX                        (0x000007ffU)

#define CSL_DEI_REG8_FMD_WINDOW_MINX_MASK                       (0x000007FFU)
#define CSL_DEI_REG8_FMD_WINDOW_MINX_SHIFT                      (0U)
#define CSL_DEI_REG8_FMD_WINDOW_MINX_RESETVAL                   (0x00000000U)
#define CSL_DEI_REG8_FMD_WINDOW_MINX_MAX                        (0x000007ffU)

#define CSL_DEI_REG8_RESETVAL                                   (0x82cf0000U)

/* REG9 */

#define CSL_DEI_REG9_FMD_WINDOW_MAXY_MASK                       (0x07FF0000U)
#define CSL_DEI_REG9_FMD_WINDOW_MAXY_SHIFT                      (16U)
#define CSL_DEI_REG9_FMD_WINDOW_MAXY_RESETVAL                   (0x000000efU)
#define CSL_DEI_REG9_FMD_WINDOW_MAXY_MAX                        (0x000007ffU)

#define CSL_DEI_REG9_FMD_WINDOW_MINY_MASK                       (0x000007FFU)
#define CSL_DEI_REG9_FMD_WINDOW_MINY_SHIFT                      (0U)
#define CSL_DEI_REG9_FMD_WINDOW_MINY_RESETVAL                   (0x00000000U)
#define CSL_DEI_REG9_FMD_WINDOW_MINY_MAX                        (0x000007ffU)

#define CSL_DEI_REG9_RESETVAL                                   (0x00ef0000U)

/* REG10 */

#define CSL_DEI_REG10_FMD_CAF_LINE_THR_MASK                     (0xFF000000U)
#define CSL_DEI_REG10_FMD_CAF_LINE_THR_SHIFT                    (24U)
#define CSL_DEI_REG10_FMD_CAF_LINE_THR_RESETVAL                 (0x00000008U)
#define CSL_DEI_REG10_FMD_CAF_LINE_THR_MAX                      (0x000000ffU)

#define CSL_DEI_REG10_FMD_CAF_FIELD_THR_MASK                    (0x00FF0000U)
#define CSL_DEI_REG10_FMD_CAF_FIELD_THR_SHIFT                   (16U)
#define CSL_DEI_REG10_FMD_CAF_FIELD_THR_RESETVAL                (0x0000000aU)
#define CSL_DEI_REG10_FMD_CAF_FIELD_THR_MAX                     (0x000000ffU)

#define CSL_DEI_REG10_FMD_BED_EN_MASK                           (0x00000008U)
#define CSL_DEI_REG10_FMD_BED_EN_SHIFT                          (3U)
#define CSL_DEI_REG10_FMD_BED_EN_RESETVAL                       (0x00000000U)
#define CSL_DEI_REG10_FMD_BED_EN_MAX                            (0x00000001U)

#define CSL_DEI_REG10_FMD_JAM_DIR_MASK                          (0x00000004U)
#define CSL_DEI_REG10_FMD_JAM_DIR_SHIFT                         (2U)
#define CSL_DEI_REG10_FMD_JAM_DIR_RESETVAL                      (0x00000000U)
#define CSL_DEI_REG10_FMD_JAM_DIR_MAX                           (0x00000001U)

#define CSL_DEI_REG10_FMD_LOCK_MASK                             (0x00000002U)
#define CSL_DEI_REG10_FMD_LOCK_SHIFT                            (1U)
#define CSL_DEI_REG10_FMD_LOCK_RESETVAL                         (0x00000000U)
#define CSL_DEI_REG10_FMD_LOCK_MAX                              (0x00000001U)

#define CSL_DEI_REG10_FMD_EN_MASK                               (0x00000001U)
#define CSL_DEI_REG10_FMD_EN_SHIFT                              (0U)
#define CSL_DEI_REG10_FMD_EN_RESETVAL                           (0x00000000U)
#define CSL_DEI_REG10_FMD_EN_MAX                                (0x00000001U)

#define CSL_DEI_REG10_RESETVAL                                  (0x080a0000U)

/* REG11 */

#define CSL_DEI_REG11_FMD_CAF_THR_MASK                          (0x000FFFFFU)
#define CSL_DEI_REG11_FMD_CAF_THR_SHIFT                         (0U)
#define CSL_DEI_REG11_FMD_CAF_THR_RESETVAL                      (0x00002004U)
#define CSL_DEI_REG11_FMD_CAF_THR_MAX                           (0x000fffffU)

#define CSL_DEI_REG11_RESETVAL                                  (0x00002004U)

/* REG12 */

#define CSL_DEI_REG12_FMD_RESET_MASK                            (0x01000000U)
#define CSL_DEI_REG12_FMD_RESET_SHIFT                           (24U)
#define CSL_DEI_REG12_FMD_RESET_RESETVAL                        (0x00000000U)
#define CSL_DEI_REG12_FMD_RESET_MAX                             (0x00000001U)

#define CSL_DEI_REG12_FMD_CAF_MASK                              (0x001FFFFFU)
#define CSL_DEI_REG12_FMD_CAF_SHIFT                             (0U)
#define CSL_DEI_REG12_FMD_CAF_RESETVAL                          (0x00000000U)
#define CSL_DEI_REG12_FMD_CAF_MAX                               (0x001fffffU)

#define CSL_DEI_REG12_RESETVAL                                  (0x00000000U)

/* REG13 */

#define CSL_DEI_REG13_FMD_FIELD_DIFF_MASK                       (0x0FFFFFFFU)
#define CSL_DEI_REG13_FMD_FIELD_DIFF_SHIFT                      (0U)
#define CSL_DEI_REG13_FMD_FIELD_DIFF_RESETVAL                   (0x00000000U)
#define CSL_DEI_REG13_FMD_FIELD_DIFF_MAX                        (0x0fffffffU)

#define CSL_DEI_REG13_RESETVAL                                  (0x00000000U)

/* REG14 */

#define CSL_DEI_REG14_FMD_FRM_DIFF_MASK                         (0x000FFFFFU)
#define CSL_DEI_REG14_FMD_FRM_DIFF_SHIFT                        (0U)
#define CSL_DEI_REG14_FMD_FRM_DIFF_RESETVAL                     (0x00000000U)
#define CSL_DEI_REG14_FMD_FRM_DIFF_MAX                          (0x000fffffU)

#define CSL_DEI_REG14_RESETVAL                                  (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
