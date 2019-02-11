/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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

#ifndef HW_ISS_SYS2_H_
#define HW_ISS_SYS2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ISP5_KEY_EN1                                                (0x0U)
#define ISP5_KEY_EN2                                                (0x4U)
#define ISP5_KEY_EN3                                                (0x8U)
#define ISP5_KEY_EN4                                                (0xcU)
#define ISP5_KEY_EN5                                                (0x10U)
#define ISP5_KEY_EN6                                                (0x14U)

#define ISP5_IRQSTATUS_RAW2(m)                                      (0x18U + \
                                                                     ((m) * (uint32_t)0x10))
#define ISP5_IRQSTATUS2(m)                                          (0x1cU + \
                                                                     ((m) * (uint32_t)0x10))
#define ISP5_IRQENABLE_SET2(m)                                      (0x20U + \
                                                                     ((m) * (uint32_t)0x10))
#define ISP5_IRQSTATUS_CLR2(m)                                      (0x24U + \
                                                                     ((m) * (uint32_t)0x10))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISP5_KEY_EN1_KEY1_EN_SHIFT                                                      ( \
        0U)
#define ISP5_KEY_EN1_KEY1_EN_MASK                                                       ( \
        0x00000001U)
#define ISP5_KEY_EN1_KEY1_EN_NEWENUM1                                                    ( \
        0U)
#define ISP5_KEY_EN1_KEY1_EN_NEWENUM2                                                    ( \
        1U)

#define ISP5_KEY_EN1_RESERVED_SHIFT                                                     ( \
        1U)
#define ISP5_KEY_EN1_RESERVED_MASK                                                      ( \
        0xfffffffeU)

#define ISP5_KEY_EN2_KEY1_EN_SHIFT                                                      ( \
        0U)
#define ISP5_KEY_EN2_KEY1_EN_MASK                                                       ( \
        0x00000001U)
#define ISP5_KEY_EN2_KEY1_EN_NEWENUM1                                                    ( \
        0U)
#define ISP5_KEY_EN2_KEY1_EN_NEWENUM2                                                    ( \
        1U)

#define ISP5_KEY_EN2_RESERVED_SHIFT                                                     ( \
        1U)
#define ISP5_KEY_EN2_RESERVED_MASK                                                      ( \
        0xfffffffeU)

#define ISP5_KEY_EN3_EN_SHIFT                                                           ( \
        0U)
#define ISP5_KEY_EN3_EN_MASK                                                            ( \
        0x00000001U)
#define ISP5_KEY_EN3_EN_NEWENUM1                                                         ( \
        0U)
#define ISP5_KEY_EN3_EN_NEWENUM2                                                         ( \
        1U)

#define ISP5_KEY_EN3_RESERVED_SHIFT                                                     ( \
        1U)
#define ISP5_KEY_EN3_RESERVED_MASK                                                      ( \
        0xfffffffeU)

#define ISP5_KEY_EN4_KEY1_EN_SHIFT                                                      ( \
        0U)
#define ISP5_KEY_EN4_KEY1_EN_MASK                                                       ( \
        0x00000001U)
#define ISP5_KEY_EN4_KEY1_EN_NEWENUM1                                                    ( \
        0U)
#define ISP5_KEY_EN4_KEY1_EN_NEWENUM2                                                    ( \
        1U)

#define ISP5_KEY_EN4_KEY2_EN_SHIFT                                                      ( \
        1U)
#define ISP5_KEY_EN4_KEY2_EN_MASK                                                       ( \
        0x00000002U)
#define ISP5_KEY_EN4_KEY2_EN_NEWENUM1                                                    ( \
        0U)
#define ISP5_KEY_EN4_KEY2_EN_NEWENUM2                                                    ( \
        1U)

#define ISP5_KEY_EN4_RESERVED_SHIFT                                                     ( \
        2U)
#define ISP5_KEY_EN4_RESERVED_MASK                                                      ( \
        0xfffffffcU)

#define ISP5_KEY_EN5_EN_SHIFT                                                           ( \
        0U)
#define ISP5_KEY_EN5_EN_MASK                                                            ( \
        0x00000001U)
#define ISP5_KEY_EN5_EN_NEWENUM1                                                         ( \
        0U)
#define ISP5_KEY_EN5_EN_NEWENUM2                                                         ( \
        1U)

#define ISP5_KEY_EN5_RESERVED_SHIFT                                                     ( \
        1U)
#define ISP5_KEY_EN5_RESERVED_MASK                                                      ( \
        0xfffffffeU)

#define ISP5_KEY_EN6_EN_SHIFT                                                           ( \
        0U)
#define ISP5_KEY_EN6_EN_MASK                                                            ( \
        0x00000001U)
#define ISP5_KEY_EN6_EN_NEWENUM1                                                         ( \
        0U)
#define ISP5_KEY_EN6_EN_NEWENUM2                                                         ( \
        1U)

#define ISP5_KEY_EN6_RESERVED_SHIFT                                                     ( \
        1U)
#define ISP5_KEY_EN6_RESERVED_MASK                                                      ( \
        0xfffffffeU)

#define ISP5_IRQSTATUS_RAW2_H3A_OVF_SHIFT                                               ( \
        0U)
#define ISP5_IRQSTATUS_RAW2_H3A_OVF_MASK                                                ( \
        0x00000001U)

#define ISP5_IRQSTATUS_RAW2_IPIPEIF_UDF_SHIFT                                           ( \
        1U)
#define ISP5_IRQSTATUS_RAW2_IPIPEIF_UDF_MASK                                            ( \
        0x00000002U)

#define ISP5_IRQSTATUS_RAW2_IPIPE_BOXCAR_OVF_SHIFT                                      ( \
        2U)
#define ISP5_IRQSTATUS_RAW2_IPIPE_BOXCAR_OVF_MASK                                       ( \
        0x00000004U)

#define ISP5_IRQSTATUS_RAW2_ISIF_OVF_SHIFT                                              ( \
        3U)
#define ISP5_IRQSTATUS_RAW2_ISIF_OVF_MASK                                               ( \
        0x00000008U)

#define ISP5_IRQSTATUS_RAW2_IPIPE_HST_ERR_SHIFT                                      ( \
        4U)
#define ISP5_IRQSTATUS_RAW2_IPIPE_HST_ERR_MASK                                       ( \
        0x00000010U)

#define ISP5_IRQSTATUS_RAW2_IPIPE_BSC_ERR_SHIFT                                      ( \
        5U)
#define ISP5_IRQSTATUS_RAW2_IPIPE_BSC_ERR_MASK                                       ( \
        0x00000020U)

#define ISP5_IRQSTATUS_RAW2_IPIPEIF_CB_SHIFT                                      ( \
        6U)
#define ISP5_IRQSTATUS_RAW2_IPIPEIF_CB_MASK                                       ( \
        0x00000040U)

#define ISP5_IRQSTATUS_RAW2_ISIF_CB_SHIFT                                      ( \
        7U)
#define ISP5_IRQSTATUS_RAW2_ISIF_CB_MASK                                       ( \
        0x00000080U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_REPRGM_SHIFT                                      ( \
        8U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_REPRGM_MASK                                       ( \
        0x00000100U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_INCMPL_SHIFT                                      ( \
        9U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_INCMPL_MASK                                       ( \
        0x00000200U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_OUTCMPL_SHIFT                                      ( \
        10U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_OUTCMPL_MASK                                       ( \
        0x00000400U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_OVERFLOW_SHIFT                                      ( \
        11U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_OVERFLOW_MASK                                       ( \
        0x00000800U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_VERT_BLANK_SHIFT                                      ( \
        12U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_VERT_BLANK_MASK                                       ( \
        0x00001000U)

#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_HORZ_BLANK_SHIFT                                      ( \
        13U)
#define ISP5_IRQSTATUS_RAW2_NSF3V_INT_HORZ_BLANK_MASK                                       ( \
        0x00002000U)

#define ISP5_IRQSTATUS_RAW2_GLBCE_INT_REG_SHIFT                                      ( \
        14U)
#define ISP5_IRQSTATUS_RAW2_GLBCE_INT_REG_MASK                                       ( \
        0x00004000U)

#define ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_START_SHIFT                                      ( \
        15U)
#define ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_START_MASK                                       ( \
        0x00008000U)

#define ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_DONE_SHIFT                                      ( \
        16U)
#define ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_DONE_MASK                                       ( \
        0x00010000U)

#define ISP5_IRQSTATUS_RAW2_GLBCE_ERROR_SHIFT                                      ( \
        17U)
#define ISP5_IRQSTATUS_RAW2_GLBCE_ERROR_MASK                                       ( \
        0x00020000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_INT_REPRGM_SHIFT                                      ( \
        18U)
#define ISP5_IRQSTATUS_RAW2_CNFA_INT_REPRGM_MASK                                       ( \
        0x00040000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_INT_INCMPL_SHIFT                                      ( \
        19U)
#define ISP5_IRQSTATUS_RAW2_CNFA_INT_INCMPL_MASK                                       ( \
        0x00080000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_INT_OUTCMPL_SHIFT                                      ( \
        20U)
#define ISP5_IRQSTATUS_RAW2_CNFA_INT_OUTCMPL_MASK                                       ( \
        0x00100000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_INT_OVERFLOW_SHIFT                                      ( \
        21U)
#define ISP5_IRQSTATUS_RAW2_CNFA_INT_OVERFLOW_MASK                                       ( \
        0x00200000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_VERT_BLANK_SHIFT                                      ( \
        22U)
#define ISP5_IRQSTATUS_RAW2_CNFA_VERT_BLANK_MASK                                       ( \
        0x00400000U)

#define ISP5_IRQSTATUS_RAW2_CNFA_INT_HORZ_BLANK_SHIFT                                      ( \
        23U)
#define ISP5_IRQSTATUS_RAW2_CNFA_INT_HORZ_BLANK_MASK                                       ( \
        0x00800000U)

#define ISP5_IRQSTATUS_RAW2_SWT_NSF3V_OVERFLOW_SHIFT                                      ( \
        31U)
#define ISP5_IRQSTATUS_RAW2_SWT_NSF3V_OVERFLOW_MASK                                       ( \
        0x80000000U)

#define ISP5_IRQSTATUS2_H3A_OVF_SHIFT                                               ( \
        0U)
#define ISP5_IRQSTATUS2_H3A_OVF_MASK                                                ( \
        0x00000001U)
#define ISP5_IRQSTATUS2_IPIPEIF_UDF_SHIFT                                           ( \
        1U)
#define ISP5_IRQSTATUS2_IPIPEIF_UDF_MASK                                            ( \
        0x00000002U)
#define ISP5_IRQSTATUS2_IPIPE_BOXCAR_OVF_SHIFT                                      ( \
        2U)
#define ISP5_IRQSTATUS2_IPIPE_BOXCAR_OVF_MASK                                       ( \
        0x00000004U)
#define ISP5_IRQSTATUS2_ISIF_OVF_SHIFT                                              ( \
        3U)
#define ISP5_IRQSTATUS2_ISIF_OVF_MASK                                               ( \
        0x00000008U)
#define ISP5_IRQSTATUS2_IPIPE_HST_ERR_SHIFT                                      ( \
        4U)
#define ISP5_IRQSTATUS2_IPIPE_HST_ERR_MASK                                       ( \
        0x00000010U)
#define ISP5_IRQSTATUS2_IPIPE_BSC_ERR_SHIFT                                      ( \
        5U)
#define ISP5_IRQSTATUS2_IPIPE_BSC_ERR_MASK                                       ( \
        0x00000020U)
#define ISP5_IRQSTATUS2_IPIPEIF_CB_SHIFT                                      ( \
        6U)
#define ISP5_IRQSTATUS2_IPIPEIF_CB_MASK                                       ( \
        0x00000040U)
#define ISP5_IRQSTATUS2_ISIF_CB_SHIFT                                      (7U)
#define ISP5_IRQSTATUS2_ISIF_CB_MASK                                       ( \
        0x00000080U)
#define ISP5_IRQSTATUS2_NSF3V_INT_REPRGM_SHIFT                                      ( \
        8U)
#define ISP5_IRQSTATUS2_NSF3V_INT_REPRGM_MASK                                       ( \
        0x00000100U)
#define ISP5_IRQSTATUS2_NSF3V_INT_INCMPL_SHIFT                                      ( \
        9U)
#define ISP5_IRQSTATUS2_NSF3V_INT_INCMPL_MASK                                       ( \
        0x00000200U)
#define ISP5_IRQSTATUS2_NSF3V_INT_OUTCMPL_SHIFT                                      ( \
        10U)
#define ISP5_IRQSTATUS2_NSF3V_INT_OUTCMPL_MASK                                       ( \
        0x00000400U)
#define ISP5_IRQSTATUS2_NSF3V_INT_OVERFLOW_SHIFT                                      ( \
        11U)
#define ISP5_IRQSTATUS2_NSF3V_INT_OVERFLOW_MASK                                       ( \
        0x00000800U)
#define ISP5_IRQSTATUS2_NSF3V_VERT_BLANK_SHIFT                                      ( \
        12U)
#define ISP5_IRQSTATUS2_NSF3V_VERT_BLANK_MASK                                       ( \
        0x00001000U)
#define ISP5_IRQSTATUS2_NSF3V_INT_HORZ_BLANK_SHIFT                                      ( \
        13U)
#define ISP5_IRQSTATUS2_NSF3V_INT_HORZ_BLANK_MASK                                       ( \
        0x00002000U)
#define ISP5_IRQSTATUS2_GLBCE_INT_REG_SHIFT                                      ( \
        14U)
#define ISP5_IRQSTATUS2_GLBCE_INT_REG_MASK                                       ( \
        0x00004000U)
#define ISP5_IRQSTATUS2_GLBCE_FILTERING_START_SHIFT                                      ( \
        15U)
#define ISP5_IRQSTATUS2_GLBCE_FILTERING_START_MASK                                       ( \
        0x00008000U)
#define ISP5_IRQSTATUS2_GLBCE_FILTERING_DONE_SHIFT                                      ( \
        16U)
#define ISP5_IRQSTATUS2_GLBCE_FILTERING_DONE_MASK                                       ( \
        0x00010000U)
#define ISP5_IRQSTATUS2_GLBCE_ERROR_SHIFT                                      ( \
        17U)
#define ISP5_IRQSTATUS2_GLBCE_ERROR_MASK                                       ( \
        0x00020000U)
#define ISP5_IRQSTATUS2_CNFA_INT_REPRGM_SHIFT                                      ( \
        18U)
#define ISP5_IRQSTATUS2_CNFA_INT_REPRGM_MASK                                       ( \
        0x00040000U)
#define ISP5_IRQSTATUS2_CNFA_INT_INCMPL_SHIFT                                      ( \
        19U)
#define ISP5_IRQSTATUS2_CNFA_INT_INCMPL_MASK                                       ( \
        0x00080000U)
#define ISP5_IRQSTATUS2_CNFA_INT_OUTCMPL_SHIFT                                      ( \
        20U)
#define ISP5_IRQSTATUS2_CNFA_INT_OUTCMPL_MASK                                       ( \
        0x00100000U)
#define ISP5_IRQSTATUS2_CNFA_INT_OVERFLOW_SHIFT                                      ( \
        21U)
#define ISP5_IRQSTATUS2_CNFA_INT_OVERFLOW_MASK                                       ( \
        0x00200000U)
#define ISP5_IRQSTATUS2_CNFA_VERT_BLANK_SHIFT                                      ( \
        22U)
#define ISP5_IRQSTATUS2_CNFA_VERT_BLANK_MASK                                       ( \
        0x00400000U)
#define ISP5_IRQSTATUS2_CNFA_INT_HORZ_BLANK_SHIFT                                      ( \
        23U)
#define ISP5_IRQSTATUS2_CNFA_INT_HORZ_BLANK_MASK                                       ( \
        0x00800000U)
#define ISP5_IRQSTATUS2_SWT_NSF3V_OVERFLOW_SHIFT                                      ( \
        31U)
#define ISP5_IRQSTATUS2_SWT_NSF3V_OVERFLOW_MASK                                       ( \
        0x80000000U)

#define ISP5_IRQENABLE_SET2_H3A_OVF_SHIFT                                               ( \
        0U)
#define ISP5_IRQENABLE_SET2_H3A_OVF_MASK                                                ( \
        0x00000001U)
#define ISP5_IRQENABLE_SET2_IPIPEIF_UDF_SHIFT                                           ( \
        1U)
#define ISP5_IRQENABLE_SET2_IPIPEIF_UDF_MASK                                            ( \
        0x00000002U)
#define ISP5_IRQENABLE_SET2_IPIPE_BOXCAR_OVF_SHIFT                                      ( \
        2U)
#define ISP5_IRQENABLE_SET2_IPIPE_BOXCAR_OVF_MASK                                       ( \
        0x00000004U)
#define ISP5_IRQENABLE_SET2_ISIF_OVF_SHIFT                                              ( \
        3U)
#define ISP5_IRQENABLE_SET2_ISIF_OVF_MASK                                               ( \
        0x00000008U)
#define ISP5_IRQENABLE_SET2_IPIPE_HST_ERR_SHIFT                                      ( \
        4U)
#define ISP5_IRQENABLE_SET2_IPIPE_HST_ERR_MASK                                       ( \
        0x00000010U)
#define ISP5_IRQENABLE_SET2_IPIPE_BSC_ERR_SHIFT                                      ( \
        5U)
#define ISP5_IRQENABLE_SET2_IPIPE_BSC_ERR_MASK                                       ( \
        0x00000020U)
#define ISP5_IRQENABLE_SET2_IPIPEIF_CB_SHIFT                                      ( \
        6U)
#define ISP5_IRQENABLE_SET2_IPIPEIF_CB_MASK                                       ( \
        0x00000040U)
#define ISP5_IRQENABLE_SET2_ISIF_CB_SHIFT                                      ( \
        7U)
#define ISP5_IRQENABLE_SET2_ISIF_CB_MASK                                       ( \
        0x00000080U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_REPRGM_SHIFT                                      ( \
        8U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_REPRGM_MASK                                       ( \
        0x00000100U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_INCMPL_SHIFT                                      ( \
        9U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_INCMPL_MASK                                       ( \
        0x00000200U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_OUTCMPL_SHIFT                                      ( \
        10U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_OUTCMPL_MASK                                       ( \
        0x00000400U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_OVERFLOW_SHIFT                                      ( \
        11U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_OVERFLOW_MASK                                       ( \
        0x00000800U)
#define ISP5_IRQENABLE_SET2_NSF3V_VERT_BLANK_SHIFT                                      ( \
        12U)
#define ISP5_IRQENABLE_SET2_NSF3V_VERT_BLANK_MASK                                       ( \
        0x00001000U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_HORZ_BLANK_SHIFT                                      ( \
        13U)
#define ISP5_IRQENABLE_SET2_NSF3V_INT_HORZ_BLANK_MASK                                       ( \
        0x00002000U)
#define ISP5_IRQENABLE_SET2_GLBCE_INT_REG_SHIFT                                      ( \
        14U)
#define ISP5_IRQENABLE_SET2_GLBCE_INT_REG_MASK                                       ( \
        0x00004000U)
#define ISP5_IRQENABLE_SET2_GLBCE_FILTERING_START_SHIFT                                      ( \
        15U)
#define ISP5_IRQENABLE_SET2_GLBCE_FILTERING_START_MASK                                       ( \
        0x00008000U)
#define ISP5_IRQENABLE_SET2_GLBCE_FILTERING_DONE_SHIFT                                      ( \
        16U)
#define ISP5_IRQENABLE_SET2_GLBCE_FILTERING_DONE_MASK                                       ( \
        0x00010000U)
#define ISP5_IRQENABLE_SET2_GLBCE_ERROR_SHIFT                                      ( \
        17U)
#define ISP5_IRQENABLE_SET2_GLBCE_ERROR_MASK                                       ( \
        0x00020000U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_REPRGM_SHIFT                                      ( \
        18U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_REPRGM_MASK                                       ( \
        0x00040000U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_INCMPL_SHIFT                                      ( \
        19U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_INCMPL_MASK                                       ( \
        0x00080000U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_OUTCMPL_SHIFT                                      ( \
        20U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_OUTCMPL_MASK                                       ( \
        0x00100000U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_OVERFLOW_SHIFT                                      ( \
        21U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_OVERFLOW_MASK                                       ( \
        0x00200000U)
#define ISP5_IRQENABLE_SET2_CNFA_VERT_BLANK_SHIFT                                      ( \
        22U)
#define ISP5_IRQENABLE_SET2_CNFA_VERT_BLANK_MASK                                       ( \
        0x00400000U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_HORZ_BLANK_SHIFT                                      ( \
        23U)
#define ISP5_IRQENABLE_SET2_CNFA_INT_HORZ_BLANK_MASK                                       ( \
        0x00800000U)
#define ISP5_IRQENABLE_SET2_SWT_NSF3V_OVERFLOW_SHIFT                                      ( \
        31U)
#define ISP5_IRQENABLE_SET2_SWT_NSF3V_OVERFLOW_MASK                                       ( \
        0x80000000U)

#define ISP5_IRQENABLE_CLR2_H3A_OVF_SHIFT                                               ( \
        0U)
#define ISP5_IRQENABLE_CLR2_H3A_OVF_MASK                                                ( \
        0x00000001U)
#define ISP5_IRQENABLE_CLR2_IPIPEIF_UDF_SHIFT                                           ( \
        1U)
#define ISP5_IRQENABLE_CLR2_IPIPEIF_UDF_MASK                                            ( \
        0x00000002U)
#define ISP5_IRQENABLE_CLR2_IPIPE_BOXCAR_OVF_SHIFT                                      ( \
        2U)
#define ISP5_IRQENABLE_CLR2_IPIPE_BOXCAR_OVF_MASK                                       ( \
        0x00000004U)
#define ISP5_IRQENABLE_CLR2_ISIF_OVF_SHIFT                                              ( \
        3U)
#define ISP5_IRQENABLE_CLR2_ISIF_OVF_MASK                                               ( \
        0x00000008U)
#define ISP5_IRQENABLE_CLR2_IPIPE_HST_ERR_SHIFT                                      ( \
        4U)
#define ISP5_IRQENABLE_CLR2_IPIPE_HST_ERR_MASK                                       ( \
        0x00000010U)
#define ISP5_IRQENABLE_CLR2_IPIPE_BSC_ERR_SHIFT                                      ( \
        5U)
#define ISP5_IRQENABLE_CLR2_IPIPE_BSC_ERR_MASK                                       ( \
        0x00000020U)
#define ISP5_IRQENABLE_CLR2_IPIPEIF_CB_SHIFT                                      ( \
        6U)
#define ISP5_IRQENABLE_CLR2_IPIPEIF_CB_MASK                                       ( \
        0x00000040U)
#define ISP5_IRQENABLE_CLR2_ISIF_CB_SHIFT                                      ( \
        7U)
#define ISP5_IRQENABLE_CLR2_ISIF_CB_MASK                                       ( \
        0x00000080U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_REPRGM_SHIFT                                      ( \
        8U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_REPRGM_MASK                                       ( \
        0x00000100U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_INCMPL_SHIFT                                      ( \
        9U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_INCMPL_MASK                                       ( \
        0x00000200U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_OUTCMPL_SHIFT                                      ( \
        10U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_OUTCMPL_MASK                                       ( \
        0x00000400U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_OVERFLOW_SHIFT                                      ( \
        11U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_OVERFLOW_MASK                                       ( \
        0x00000800U)
#define ISP5_IRQENABLE_CLR2_NSF3V_VERT_BLANK_SHIFT                                      ( \
        12U)
#define ISP5_IRQENABLE_CLR2_NSF3V_VERT_BLANK_MASK                                       ( \
        0x00001000U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_HORZ_BLANK_SHIFT                                      ( \
        13U)
#define ISP5_IRQENABLE_CLR2_NSF3V_INT_HORZ_BLANK_MASK                                       ( \
        0x00002000U)
#define ISP5_IRQENABLE_CLR2_GLBCE_INT_REG_SHIFT                                      ( \
        14U)
#define ISP5_IRQENABLE_CLR2_GLBCE_INT_REG_MASK                                       ( \
        0x00004000U)
#define ISP5_IRQENABLE_CLR2_GLBCE_FILTERING_START_SHIFT                                      ( \
        15U)
#define ISP5_IRQENABLE_CLR2_GLBCE_FILTERING_START_MASK                                       ( \
        0x00008000U)
#define ISP5_IRQENABLE_CLR2_GLBCE_FILTERING_DONE_SHIFT                                      ( \
        16U)
#define ISP5_IRQENABLE_CLR2_GLBCE_FILTERING_DONE_MASK                                       ( \
        0x00010000U)
#define ISP5_IRQENABLE_CLR2_GLBCE_ERROR_SHIFT                                      ( \
        17U)
#define ISP5_IRQENABLE_CLR2_GLBCE_ERROR_MASK                                       ( \
        0x00020000U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_REPRGM_SHIFT                                      ( \
        18U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_REPRGM_MASK                                       ( \
        0x00040000U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_INCMPL_SHIFT                                      ( \
        19U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_INCMPL_MASK                                       ( \
        0x00080000U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_OUTCMPL_SHIFT                                      ( \
        20U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_OUTCMPL_MASK                                       ( \
        0x00100000U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_OVERFLOW_SHIFT                                      ( \
        21U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_OVERFLOW_MASK                                       ( \
        0x00200000U)
#define ISP5_IRQENABLE_CLR2_CNFA_VERT_BLANK_SHIFT                                      ( \
        22U)
#define ISP5_IRQENABLE_CLR2_CNFA_VERT_BLANK_MASK                                       ( \
        0x00400000U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_HORZ_BLANK_SHIFT                                      ( \
        23U)
#define ISP5_IRQENABLE_CLR2_CNFA_INT_HORZ_BLANK_MASK                                       ( \
        0x00800000U)
#define ISP5_IRQENABLE_CLR2_SWT_NSF3V_OVERFLOW_SHIFT                                      ( \
        31U)
#define ISP5_IRQENABLE_CLR2_SWT_NSF3V_OVERFLOW_MASK                                       ( \
        0x80000000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_SYS2_H_ */

