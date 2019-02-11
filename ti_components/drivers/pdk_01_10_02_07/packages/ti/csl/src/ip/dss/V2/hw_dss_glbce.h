/*
* hw_dss_glbce.h
*
* Register-level header file for DSS_GLBCE
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

#ifndef HW_DSS_GLBCE_H_
#define HW_DSS_GLBCE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_GLBCE_DATA_FORMAT                                       (0x0U)
#define DSS_GLBCE_SYNC_FORMAT                                       (0x4U)
#define DSS_GLBCE_FRAME_WIDTH                                       (0x8U)
#define DSS_GLBCE_FRAME_HEIGHT                                      (0xcU)
#define DSS_GLBCE_CONTROL_0                                         (0x10U)
#define DSS_GLBCE_CONTROL_1                                         (0x14U)
#define DSS_GLBCE_STRENGTH_IR                                       (0x18U)
#define DSS_GLBCE_VARIANCE                                          (0x1cU)
#define DSS_GLBCE_DITHER                                            (0x20U)
#define DSS_GLBCE_LIMIT_AMPL                                        (0x24U)
#define DSS_GLBCE_SLOPE_MIN                                         (0x28U)
#define DSS_GLBCE_SLOPE_MAX                                         (0x2cU)
#define DSS_GLBCE_BLACK_LEVEL                                       (0x30U)
#define DSS_GLBCE_WHITE_LEVEL                                       (0x34U)
#define DSS_GLBCE_LUT_FI(n)                                         (0x38U + ((n) * 0x4U))
#define DSS_GLBCE_LUT_CC(n)                                         (0xbcU + ((n) * 0x4U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_GLBCE_DATA_FORMAT_SHIFT                                                     (0U)
#define DSS_GLBCE_DATA_FORMAT_MASK                                                      (0x00000003U)
#define DSS_GLBCE_DATA_FORMAT_YCBCR0                                                     (0U)
#define DSS_GLBCE_DATA_FORMAT_YCBCR1                                                     (1U)
#define DSS_GLBCE_DATA_FORMAT_YCBCR2                                                     (2U)
#define DSS_GLBCE_DATA_FORMAT_RGB                                                        (3U)

#define DSS_GLBCE_DATA_FORMAT_CM_SHIFT                                                  (4U)
#define DSS_GLBCE_DATA_FORMAT_CM_MASK                                                   (0x00000010U)
#define DSS_GLBCE_DATA_FORMAT_CM_SAMECLK                                                 (0U)
#define DSS_GLBCE_DATA_FORMAT_CM_RESERVED                                                (1U)

#define DSS_GLBCE_SYNC_FORMAT_AUTOSIZE_SHIFT                                            (7U)
#define DSS_GLBCE_SYNC_FORMAT_AUTOSIZE_MASK                                             (0x00000080U)
#define DSS_GLBCE_SYNC_FORMAT_AUTOSIZE_AUTOSIZEOFF                                       (0U)
#define DSS_GLBCE_SYNC_FORMAT_AUTOSIZE_RESERVED                                          (1U)

#define DSS_GLBCE_FRAME_WIDTH_LINELENGTH_SHIFT                                          (0U)
#define DSS_GLBCE_FRAME_WIDTH_LINELENGTH_MASK                                           (0x00007fffU)

#define DSS_GLBCE_FRAME_HEIGHT_LINENUMBER_SHIFT                                         (0U)
#define DSS_GLBCE_FRAME_HEIGHT_LINENUMBER_MASK                                          (0x00007fffU)

#define DSS_GLBCE_CONTROL_0_ON_OFF_SHIFT                                                (0U)
#define DSS_GLBCE_CONTROL_0_ON_OFF_MASK                                                 (0x00000001U)
#define DSS_GLBCE_CONTROL_0_ON_OFF_DISABLE                                               (0U)
#define DSS_GLBCE_CONTROL_0_ON_OFF_ENABLE                                                (1U)

#define DSS_GLBCE_CONTROL_0_LC_SHIFT                                                    (1U)
#define DSS_GLBCE_CONTROL_0_LC_MASK                                                     (0x00000006U)
#define DSS_GLBCE_CONTROL_0_LC_DISABLE                                                   (0U)
#define DSS_GLBCE_CONTROL_0_LC_LCENABLE                                                  (1U)
#define DSS_GLBCE_CONTROL_0_LC_LCENABLE1                                                 (2U)
#define DSS_GLBCE_CONTROL_0_LC_LCENABLE2                                                 (3U)

#define DSS_GLBCE_CONTROL_0_LC2_SHIFT                                                   (3U)
#define DSS_GLBCE_CONTROL_0_LC2_MASK                                                    (0x00000008U)
#define DSS_GLBCE_CONTROL_0_LC2_MEMUSED                                                  (0U)
#define DSS_GLBCE_CONTROL_0_LC2_MEMBYPASS                                                (1U)

#define DSS_GLBCE_CONTROL_0_CCTL_SHIFT                                                  (4U)
#define DSS_GLBCE_CONTROL_0_CCTL_MASK                                                   (0x00000010U)
#define DSS_GLBCE_CONTROL_0_CCTL_DISABLE                                                 (0U)
#define DSS_GLBCE_CONTROL_0_CCTL_ENABLE                                                  (1U)

#define DSS_GLBCE_CONTROL_1_CONTROLPORT1_SHIFT                                          (0U)
#define DSS_GLBCE_CONTROL_1_CONTROLPORT1_MASK                                           (0x000000ffU)

#define DSS_GLBCE_STRENGTH_IR_SHIFT                                                     (0U)
#define DSS_GLBCE_STRENGTH_IR_MASK                                                      (0x000000ffU)

#define DSS_GLBCE_VARIANCE_VARIANCESPACE_SHIFT                                          (0U)
#define DSS_GLBCE_VARIANCE_VARIANCESPACE_MASK                                           (0x0000000fU)

#define DSS_GLBCE_VARIANCE_VARIANCEINTENSITY_SHIFT                                      (4U)
#define DSS_GLBCE_VARIANCE_VARIANCEINTENSITY_MASK                                       (0x000000f0U)

#define DSS_GLBCE_DITHER_MODE_SHIFT                                                     (0U)
#define DSS_GLBCE_DITHER_MODE_MASK                                                      (0x00000007U)

#define DSS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_SHIFT                               (0U)
#define DSS_GLBCE_LIMIT_AMPL_DARKAMPLIFICATIONLIMIT_MASK                                (0x00000001U)

#define DSS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_SHIFT                             (1U)
#define DSS_GLBCE_LIMIT_AMPL_BRIGHTAMPLIFICATIONLIMIT_MASK                              (0x0000001eU)

#define DSS_GLBCE_SLOPE_MIN_LIMIT_SHIFT                                                 (0U)
#define DSS_GLBCE_SLOPE_MIN_LIMIT_MASK                                                  (0x000000ffU)

#define DSS_GLBCE_SLOPE_MAX_LIMIT_SHIFT                                                 (0U)
#define DSS_GLBCE_SLOPE_MAX_LIMIT_MASK                                                  (0x000000ffU)

#define DSS_GLBCE_BLACK_LEVEL_SHIFT                                                     (0U)
#define DSS_GLBCE_BLACK_LEVEL_MASK                                                      (0x000000ffU)

#define DSS_GLBCE_WHITE_LEVEL_SHIFT                                                     (0U)
#define DSS_GLBCE_WHITE_LEVEL_MASK                                                      (0x00000001U)

#define DSS_GLBCE_LUT_FI_LUTFI_SHIFT                                                    (0U)
#define DSS_GLBCE_LUT_FI_LUTFI_MASK                                                     (0x0000ffffU)

#define DSS_GLBCE_LUT_CC_LUTCC_SHIFT                                                    (0U)
#define DSS_GLBCE_LUT_CC_LUTCC_MASK                                                     (0x00000fffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_GLBCE_H_ */

