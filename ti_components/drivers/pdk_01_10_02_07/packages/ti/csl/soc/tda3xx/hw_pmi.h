/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  hw_pmi.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_PMI_H_
#define HW_PMI_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PMI_IDENTICATION                                       (0x0U)
#define PMI_SYS_CONFIG                                         (0x10U)
#define PMI_STATUS                                             (0x14U)
#define PMI_CONFIGURATION                                      (0x24U)
#define PMI_CLASS_FILTERING                                    (0x28U)
#define PMI_TRIGGERING                                         (0x2cU)
#define PMI_SAMPLING                                           (0x30U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PMI_IDENTICATION_MINOR_SHIFT                                               (0U)
#define PMI_IDENTICATION_MINOR_MASK                                                (0x0000003fU)

#define PMI_IDENTICATION_CUSTOM_SHIFT                                              (6U)
#define PMI_IDENTICATION_CUSTOM_MASK                                               (0x000000c0U)

#define PMI_IDENTICATION_MAJOR_SHIFT                                               (8U)
#define PMI_IDENTICATION_MAJOR_MASK                                                (0x00000700U)

#define PMI_IDENTICATION_RTL_SHIFT                                                 (11U)
#define PMI_IDENTICATION_RTL_MASK                                                  (0x0000f800U)

#define PMI_IDENTICATION_FUNC_SHIFT                                                (16U)
#define PMI_IDENTICATION_FUNC_MASK                                                 (0x0fff0000U)

#define PMI_IDENTICATION_SCHEME_SHIFT                                              (30U)
#define PMI_IDENTICATION_SCHEME_MASK                                               (0xc0000000U)

#define PMI_SYS_CONFIG_SOFTRESET_SHIFT                                             (0U)
#define PMI_SYS_CONFIG_SOFTRESET_MASK                                              (0x00000001U)

#define PMI_SYS_CONFIG_IDLEMODE_SHIFT                                              (2U)
#define PMI_SYS_CONFIG_IDLEMODE_MASK                                               (0x0000000cU)

#define PMI_STATUS_FIFOEMPTY_SHIFT                                                 (8U)
#define PMI_STATUS_FIFOEMPTY_MASK                                                  (0x00000100U)

#define PMI_CONFIGURATION_EVT_CAPT_EN_SHIFT                                        (7U)
#define PMI_CONFIGURATION_EVT_CAPT_EN_MASK                                         (0x00000080U)

#define PMI_CONFIGURATION_CLAIM_1_SHIFT                                            (28U)
#define PMI_CONFIGURATION_CLAIM_1_MASK                                             (0x10000000U)

#define PMI_CONFIGURATION_CLAIM_2_SHIFT                                            (29U)
#define PMI_CONFIGURATION_CLAIM_2_MASK                                             (0x20000000U)

#define PMI_CONFIGURATION_CLAIM_3_SHIFT                                            (30U)
#define PMI_CONFIGURATION_CLAIM_3_MASK                                             (0xc0000000U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_00_SHIFT                                  (0U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_00_MASK                                   (0x00000001U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_01_SHIFT                                  (1U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_01_MASK                                   (0x00000002U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_02_SHIFT                                  (2U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_02_MASK                                   (0x00000004U)

#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_03_SHIFT                                  (3U)
#define PMI_CLASS_FILTERING_SNAP_CAPT_EN_03_MASK                                   (0x00000008U)

#define PMI_TRIGGERING_TRIG_START_EN_SHIFT                                         (0U)
#define PMI_TRIGGERING_TRIG_START_EN_MASK                                          (0x00000001U)

#define PMI_TRIGGERING_TRIG_STOP_EN_SHIFT                                          (1U)
#define PMI_TRIGGERING_TRIG_STOP_EN_MASK                                           (0x00000002U)

#define PMI_SAMPLING_SAMP_WIND_SIZE_SHIFT                                          (0U)
#define PMI_SAMPLING_SAMP_WIND_SIZE_MASK                                           (0x000000ffU)

#define PMI_SAMPLING_FCLK_DIV_FACOR_SHIFT                                          (16U)
#define PMI_SAMPLING_FCLK_DIV_FACOR_MASK                                           (0x000f0000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_PMI_H_ */

