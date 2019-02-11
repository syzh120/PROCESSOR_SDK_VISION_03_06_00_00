/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2016
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
 *
 *  \file   hw_qspi.h
 *  \brief  register-level header file for QSPI
 *
**/

#ifndef HW_QSPI_H_
#define HW_QSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define QSPI_PID                                                                                            ((uint32_t)0x0U)
#define QSPI_SYSCONFIG                                                                                      ((uint32_t)0x10U)
#define QSPI_INTR_STATUS_RAW_SET                                                                            ((uint32_t)0x20U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR                                                                      ((uint32_t)0x24U)
#define QSPI_INTR_ENABLE_SET_REG                                                                            ((uint32_t)0x28U)
#define QSPI_INTR_ENABLE_CLEAR_REG                                                                          ((uint32_t)0x2cU)
#define QSPI_SPI_CLOCK_CNTRL_REG                                                                            ((uint32_t)0x40U)
#define QSPI_SPI_DC_REG                                                                                     ((uint32_t)0x44U)
#define QSPI_SPI_CMD_REG                                                                                    ((uint32_t)0x48U)
#define QSPI_SPI_STATUS_REG                                                                                 ((uint32_t)0x4cU)
#define QSPI_SPI_DATA_REG                                                                                   ((uint32_t)0x50U)
#define QSPI_SPI_SETUP0_REG                                                                                 ((uint32_t)0x54U)
#define QSPI_SPI_SWITCH_REG                                                                                 ((uint32_t)0x64U)
#define QSPI_SPI_SETUP1_REG                                                                                 ((uint32_t)0x58U)
#define QSPI_SPI_SETUP2_REG                                                                                 ((uint32_t)0x5cU)
#define QSPI_SPI_SETUP3_REG                                                                                 ((uint32_t)0x60U)
#define QSPI_SPI_DATA_REG_1                                                                                 ((uint32_t)0x68U)
#define QSPI_SPI_DATA_REG_2                                                                                 ((uint32_t)0x6cU)
#define QSPI_SPI_DATA_REG_3                                                                                 ((uint32_t)0x70U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define QSPI_PID_REVISION_SHIFT                                                                             ((uint32_t)0U)
#define QSPI_PID_REVISION_MASK                                                                              ((uint32_t)0xffffffffU)

#define QSPI_SYSCONFIG_RSVD_1_SHIFT                                                                         ((uint32_t)0U)
#define QSPI_SYSCONFIG_RSVD_1_MASK                                                                          ((uint32_t)0x00000003U)

#define QSPI_SYSCONFIG_IDLE_MODE_SHIFT                                                                      ((uint32_t)2U)
#define QSPI_SYSCONFIG_IDLE_MODE_MASK                                                                       ((uint32_t)0x0000000cU)
#define QSPI_SYSCONFIG_IDLE_MODE_FORCE_IDLE                                                                  ((uint32_t)0U)
#define QSPI_SYSCONFIG_IDLE_MODE_NO_IDLE                                                                     ((uint32_t)1U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE                                                                  ((uint32_t)2U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE_WAKEUP_CAPABLE                                                   ((uint32_t)3U)

#define QSPI_SYSCONFIG_RSVD_3_SHIFT                                                                         ((uint32_t)4U)
#define QSPI_SYSCONFIG_RSVD_3_MASK                                                                          ((uint32_t)0x00000030U)

#define QSPI_SYSCONFIG_RSVD_2_SHIFT                                                                         ((uint32_t)6U)
#define QSPI_SYSCONFIG_RSVD_2_MASK                                                                          ((uint32_t)0xffffffc0U)

#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_SHIFT                                                             ((uint32_t)0U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_MASK                                                              ((uint32_t)0x00000001U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_INACTIVE                                                      ((uint32_t)0U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_ACTIVE                                                        ((uint32_t)1U)

#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_SHIFT                                                             ((uint32_t)1U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_MASK                                                              ((uint32_t)0x00000002U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_INACTIVE                                                      ((uint32_t)0U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_ACTIVE                                                        ((uint32_t)1U)

#define QSPI_INTR_STATUS_RAW_SET_RSVD_SHIFT                                                                 ((uint32_t)2U)
#define QSPI_INTR_STATUS_RAW_SET_RSVD_MASK                                                                  ((uint32_t)0xfffffffcU)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_SHIFT                                                       ((uint32_t)0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_MASK                                                        ((uint32_t)0x00000001U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_INACTIVE                                                     ((uint32_t)0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_ACTIVE                                                       ((uint32_t)1U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_SHIFT                                                       ((uint32_t)1U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_MASK                                                        ((uint32_t)0x00000002U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_INACTIVE                                                     ((uint32_t)0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_ACTIVE                                                       ((uint32_t)1U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_SHIFT                                                           ((uint32_t)2U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_MASK                                                            ((uint32_t)0xfffffffcU)

#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_SHIFT                                                         ((uint32_t)0U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK                                                          ((uint32_t)0x00000001U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_INACTIVE                                                       ((uint32_t)0U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_ACTIVE                                                         ((uint32_t)1U)

#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_SHIFT                                                         ((uint32_t)1U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK                                                          ((uint32_t)0x00000002U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_INACTIVE                                                       ((uint32_t)0U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_ACTIVE                                                         ((uint32_t)1U)

#define QSPI_INTR_ENABLE_SET_REG_RSVD_SHIFT                                                                 ((uint32_t)2U)
#define QSPI_INTR_ENABLE_SET_REG_RSVD_MASK                                                                  ((uint32_t)0xfffffffcU)

#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_SHIFT                                                       ((uint32_t)0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_MASK                                                        ((uint32_t)0x00000001U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_INACTIVE                                                     ((uint32_t)0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE                                                       ((uint32_t)1U)

#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_SHIFT                                                       ((uint32_t)1U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_MASK                                                        ((uint32_t)0x00000002U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_INACTIVE                                                     ((uint32_t)0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE                                                       ((uint32_t)1U)

#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_SHIFT                                                               ((uint32_t)2U)
#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_MASK                                                                ((uint32_t)0xfffffffcU)

#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_SHIFT                                                             ((uint32_t)0U)
#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_MASK                                                              ((uint32_t)0x0000ffffU)

#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_SHIFT                                                                 ((uint32_t)16U)
#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_MASK                                                                  ((uint32_t)0x7fff0000U)

#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_SHIFT                                                                ((uint32_t)31U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_MASK                                                                 ((uint32_t)0x80000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON                                                             ((uint32_t)1U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF                                                            ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CKP_DATA_ACTIVE                                                                      ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKP_DATA_INACTIVE                                                                    ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CKP0_SHIFT                                                                          ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKP0_MASK                                                                           ((uint32_t)0x00000001U)
#define QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE                                                                     ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE                                                                   ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CSP_ACTIVE_LOW                                                                       ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CSP_ACTIVE_HIGH                                                                      ((uint32_t)1U)

#define QSPI_SPI_DC_REG_CSP0_SHIFT                                                                          ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CSP0_MASK                                                                           ((uint32_t)0x00000002U)
#define QSPI_SPI_DC_REG_CSP0_ACTIVE_LOW                                                                      ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CSP0_ACTIVE_HIGH                                                                     ((uint32_t)1U)

#define QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE                                                    ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_RISING_EDGE                                                     ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE                                                    ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_RISING_EDGE                                                     ((uint32_t)0U)


#define QSPI_SPI_DC_REG_CKPH0_SHIFT                                                                         ((uint32_t)2U)
#define QSPI_SPI_DC_REG_CKPH0_MASK                                                                          ((uint32_t)0x00000004U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)0U)

#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_0                                                                ((uint32_t)0U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_1                                                                ((uint32_t)1U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_2                                                                ((uint32_t)2U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_3                                                                ((uint32_t)3U)

#define QSPI_SPI_DC_REG_DD0_SHIFT                                                                           ((uint32_t)3U)
#define QSPI_SPI_DC_REG_DD0_MASK                                                                            ((uint32_t)0x00000018U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_0                                                               ((uint32_t)0U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_1                                                               ((uint32_t)1U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_2                                                               ((uint32_t)2U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_3                                                               ((uint32_t)3U)

#define QSPI_SPI_DC_REG_RSVD_0_SHIFT                                                                        ((uint32_t)5U)
#define QSPI_SPI_DC_REG_RSVD_0_MASK                                                                         ((uint32_t)0x000000e0U)

#define QSPI_SPI_DC_REG_CKP1_SHIFT                                                                          ((uint32_t)8U)
#define QSPI_SPI_DC_REG_CKP1_MASK                                                                           ((uint32_t)0x00000100U)
#define QSPI_SPI_DC_REG_CKP1_DATA_ACTIVE                                                                     ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKP1_DATA_INACTIVE                                                                   ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CSP1_SHIFT                                                                          ((uint32_t)9U)
#define QSPI_SPI_DC_REG_CSP1_MASK                                                                           ((uint32_t)0x00000200U)
#define QSPI_SPI_DC_REG_CSP1_ACTIVE_LOW                                                                      ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CSP1_ACTIVE_HIGH                                                                     ((uint32_t)1U)

#define QSPI_SPI_DC_REG_CKPH1_SHIFT                                                                         ((uint32_t)10U)
#define QSPI_SPI_DC_REG_CKPH1_MASK                                                                          ((uint32_t)0x00000400U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_0_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_0_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_1_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_1_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)0U)

#define QSPI_SPI_DC_REG_DD1_SHIFT                                                                           ((uint32_t)11U)
#define QSPI_SPI_DC_REG_DD1_MASK                                                                            ((uint32_t)0x00001800U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_0                                                               ((uint32_t)0U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_1                                                               ((uint32_t)1U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_2                                                               ((uint32_t)2U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_3                                                               ((uint32_t)3U)

#define QSPI_SPI_DC_REG_RSVD_1_SHIFT                                                                        ((uint32_t)13U)
#define QSPI_SPI_DC_REG_RSVD_1_MASK                                                                         ((uint32_t)0x0000e000U)

#define QSPI_SPI_DC_REG_CKP2_SHIFT                                                                          ((uint32_t)16U)
#define QSPI_SPI_DC_REG_CKP2_MASK                                                                           ((uint32_t)0x00010000U)
#define QSPI_SPI_DC_REG_CKP2_DATA_ACTIVE                                                                     ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKP2_DATA_INACTIVE                                                                   ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CSP2_SHIFT                                                                          ((uint32_t)17U)
#define QSPI_SPI_DC_REG_CSP2_MASK                                                                           ((uint32_t)0x00020000U)
#define QSPI_SPI_DC_REG_CSP2_ACTIVE_LOW                                                                      ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CSP2_ACTIVE_HIGH                                                                     ((uint32_t)1U)

#define QSPI_SPI_DC_REG_CKPH2_SHIFT                                                                         ((uint32_t)18U)
#define QSPI_SPI_DC_REG_CKPH2_MASK                                                                          ((uint32_t)0x00040000U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_0_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_0_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_1_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_1_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)0U)

#define QSPI_SPI_DC_REG_DD2_SHIFT                                                                           ((uint32_t)19U)
#define QSPI_SPI_DC_REG_DD2_MASK                                                                            ((uint32_t)0x00180000U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_0                                                               ((uint32_t)0U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_1                                                               ((uint32_t)1U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_2                                                               ((uint32_t)2U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_3                                                               ((uint32_t)3U)

#define QSPI_SPI_DC_REG_RSVD_2_SHIFT                                                                        ((uint32_t)21U)
#define QSPI_SPI_DC_REG_RSVD_2_MASK                                                                         ((uint32_t)0x00e00000U)

#define QSPI_SPI_DC_REG_CKP3_SHIFT                                                                          ((uint32_t)24U)
#define QSPI_SPI_DC_REG_CKP3_MASK                                                                           ((uint32_t)0x01000000U)
#define QSPI_SPI_DC_REG_CKP3_DATA_ACTIVE                                                                     ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKP3_DATA_INACTIVE                                                                   ((uint32_t)0U)

#define QSPI_SPI_DC_REG_CSP3_SHIFT                                                                          ((uint32_t)25U)
#define QSPI_SPI_DC_REG_CSP3_MASK                                                                           ((uint32_t)0x02000000U)
#define QSPI_SPI_DC_REG_CSP3_ACTIVE_LOW                                                                      ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CSP3_ACTIVE_HIGH                                                                     ((uint32_t)1U)

#define QSPI_SPI_DC_REG_CKPH3_SHIFT                                                                         ((uint32_t)26U)
#define QSPI_SPI_DC_REG_CKPH3_MASK                                                                          ((uint32_t)0x04000000U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_0_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)0U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_0_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_1_SHIFT_OUT_FALLING_EDGE                                                   ((uint32_t)1U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_1_SHIFT_OUT_RISING_EDGE                                                    ((uint32_t)0U)

#define QSPI_SPI_DC_REG_DD3_SHIFT                                                                           ((uint32_t)27U)
#define QSPI_SPI_DC_REG_DD3_MASK                                                                            ((uint32_t)0x18000000U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_0                                                               ((uint32_t)0U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_1                                                               ((uint32_t)1U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_2                                                               ((uint32_t)2U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_3                                                               ((uint32_t)3U)

#define QSPI_SPI_DC_REG_RSVD_3_SHIFT                                                                        ((uint32_t)29U)
#define QSPI_SPI_DC_REG_RSVD_3_MASK                                                                         ((uint32_t)0xe0000000U)

#define QSPI_SPI_CMD_REG_FLEN_SHIFT                                                                         ((uint32_t)0U)
#define QSPI_SPI_CMD_REG_FLEN_MASK                                                                          ((uint32_t)0x00000fffU)

#define QSPI_SPI_CMD_REG_RSVD_SHIFT                                                                         ((uint32_t)12U)
#define QSPI_SPI_CMD_REG_RSVD_MASK                                                                          ((uint32_t)0x00003000U)

#define QSPI_SPI_CMD_REG_WIRQ_SHIFT                                                                         ((uint32_t)14U)
#define QSPI_SPI_CMD_REG_WIRQ_MASK                                                                          ((uint32_t)0x00004000U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE                                                          ((uint32_t)1U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE                                                         ((uint32_t)0U)

#define QSPI_SPI_CMD_REG_FIRQ_SHIFT                                                                         ((uint32_t)15U)
#define QSPI_SPI_CMD_REG_FIRQ_MASK                                                                          ((uint32_t)0x00008000U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE                                                         ((uint32_t)1U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE                                                        ((uint32_t)0U)

#define QSPI_SPI_CMD_REG_CMD_SHIFT                                                                          ((uint32_t)16U)
#define QSPI_SPI_CMD_REG_CMD_MASK                                                                           ((uint32_t)0x00070000U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE                                                            ((uint32_t)1U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE                                                           ((uint32_t)2U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL                                                              ((uint32_t)3U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_READ_SINGLE                                                           ((uint32_t)5U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_WRITE_SINGLE                                                          ((uint32_t)6U)
#define QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD                                                               ((uint32_t)7U)

#define QSPI_SPI_CMD_REG_WLEN_SHIFT                                                                         ((uint32_t)19U)
#define QSPI_SPI_CMD_REG_WLEN_MASK                                                                          ((uint32_t)0x03f80000U)

#define QSPI_SPI_CMD_REG_RSVD_2_SHIFT                                                                       ((uint32_t)24U)
#define QSPI_SPI_CMD_REG_RSVD_2_MASK                                                                        ((uint32_t)0x0f000000U)

#define QSPI_SPI_CMD_REG_CSNUM_SHIFT                                                                        ((uint32_t)28U)
#define QSPI_SPI_CMD_REG_CSNUM_MASK                                                                         ((uint32_t)0x30000000U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_0                                                                          ((uint32_t)0U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_1                                                                          ((uint32_t)1U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_2                                                                          ((uint32_t)2U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_3                                                                          ((uint32_t)3U)

#define QSPI_SPI_CMD_REG_RSVD_3_SHIFT                                                                       ((uint32_t)30U)
#define QSPI_SPI_CMD_REG_RSVD_3_MASK                                                                        ((uint32_t)0xc0000000U)

#define QSPI_SPI_STATUS_REG_BUSY_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_STATUS_REG_BUSY_MASK                                                                       ((uint32_t)0x00000001U)
#define QSPI_SPI_STATUS_REG_BUSY_IDLE                                                                        ((uint32_t)0U)
#define QSPI_SPI_STATUS_REG_BUSY_BUSY                                                                        ((uint32_t)1U)

#define QSPI_SPI_STATUS_REG_WC_SHIFT                                                                        ((uint32_t)1U)
#define QSPI_SPI_STATUS_REG_WC_MASK                                                                         ((uint32_t)0x00000002U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_NOT_COMPLETE                                                    ((uint32_t)0U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_COMPLETE                                                        ((uint32_t)1U)

#define QSPI_SPI_STATUS_REG_FC_SHIFT                                                                        ((uint32_t)2U)
#define QSPI_SPI_STATUS_REG_FC_MASK                                                                         ((uint32_t)0x00000004U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_NOT_COMPLETE                                                   ((uint32_t)0U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_COMPLETE                                                       ((uint32_t)1U)

#define QSPI_SPI_STATUS_REG_RSVD_SHIFT                                                                      ((uint32_t)3U)
#define QSPI_SPI_STATUS_REG_RSVD_MASK                                                                       ((uint32_t)0x0000fff8U)

#define QSPI_SPI_STATUS_REG_WDCNT_SHIFT                                                                     ((uint32_t)16U)
#define QSPI_SPI_STATUS_REG_WDCNT_MASK                                                                      ((uint32_t)0x0fff0000U)

#define QSPI_SPI_STATUS_REG_RSVD_2_SHIFT                                                                    ((uint32_t)28U)
#define QSPI_SPI_STATUS_REG_RSVD_2_MASK                                                                     ((uint32_t)0xf0000000U)

#define QSPI_SPI_DATA_REG_DATA_SHIFT                                                                        ((uint32_t)0U)
#define QSPI_SPI_DATA_REG_DATA_MASK                                                                         ((uint32_t)0xffffffffU)

#define QSPI_SPI_SETUP0_REG_RCMD_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_SETUP0_REG_RCMD_MASK                                                                       ((uint32_t)0x000000ffU)

#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_SHIFT                                                               ((uint32_t)8U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_MASK                                                                ((uint32_t)0x00000300U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_ONE_BYTE                                                             ((uint32_t)0U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_TWO_BYTES                                                            ((uint32_t)1U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_THREE_BYTES                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES                                                           ((uint32_t)3U)

#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_SHIFT                                                               ((uint32_t)10U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_MASK                                                                ((uint32_t)0x00000c00U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS                                                       ((uint32_t)0U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS                                                           ((uint32_t)1U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS                                                          ((uint32_t)3U)

#define QSPI_SPI_SETUP0_REG_READ_TYPE_SHIFT                                                                 ((uint32_t)12U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_MASK                                                                  ((uint32_t)0x00003000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ                                                            ((uint32_t)0U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ                                                              ((uint32_t)1U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE                                                       ((uint32_t)2U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ                                                              ((uint32_t)3U)

#define QSPI_SPI_SETUP0_REG_RSVD_1_SHIFT                                                                    ((uint32_t)14U)
#define QSPI_SPI_SETUP0_REG_RSVD_1_MASK                                                                     ((uint32_t)0x0000c000U)

#define QSPI_SPI_SETUP0_REG_WCMD_SHIFT                                                                      ((uint32_t)16U)
#define QSPI_SPI_SETUP0_REG_WCMD_MASK                                                                       ((uint32_t)0x00ff0000U)

#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_SHIFT                                                                ((uint32_t)24U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_MASK                                                                 ((uint32_t)0x1f000000U)

#define QSPI_SPI_SETUP0_REG_RSVD_2_SHIFT                                                                    ((uint32_t)29U)
#define QSPI_SPI_SETUP0_REG_RSVD_2_MASK                                                                     ((uint32_t)0xe0000000U)

#define QSPI_SPI_SWITCH_REG_MMPT_S_SHIFT                                                                    ((uint32_t)0U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_MASK                                                                     ((uint32_t)0x00000001U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT                                                              ((uint32_t)0U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT                                                               ((uint32_t)1U)

#define QSPI_SPI_SWITCH_REG_MM_INT_EN_SHIFT                                                                 ((uint32_t)1U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MASK                                                                  ((uint32_t)0x00000002U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_DISABLED                                                  ((uint32_t)0U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_ENABLED                                                   ((uint32_t)1U)

#define QSPI_SPI_SWITCH_REG_RSVD_SHIFT                                                                      ((uint32_t)2U)
#define QSPI_SPI_SWITCH_REG_RSVD_MASK                                                                       ((uint32_t)0xfffffffcU)

#define QSPI_SPI_SETUP1_REG_RCMD_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_SETUP1_REG_RCMD_MASK                                                                       ((uint32_t)0x000000ffU)

#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_SHIFT                                                               ((uint32_t)8U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_MASK                                                                ((uint32_t)0x00000300U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_ONE_BYTE                                                             ((uint32_t)0U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_TWO_BYTES                                                            ((uint32_t)1U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_THREE_BYTES                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_FOUR_BYTES                                                           ((uint32_t)3U)

#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_SHIFT                                                               ((uint32_t)10U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_MASK                                                                ((uint32_t)0x00000c00U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_NUM_D_BITS                                                       ((uint32_t)0U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_8_BITS                                                           ((uint32_t)1U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_16_BITS                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_24_BITS                                                          ((uint32_t)3U)

#define QSPI_SPI_SETUP1_REG_READ_TYPE_SHIFT                                                                 ((uint32_t)12U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_MASK                                                                  ((uint32_t)0x00003000U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_NORMAL_READ                                                            ((uint32_t)0U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_DUAL_READ                                                              ((uint32_t)1U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_NORMAL_READ_TYPE                                                       ((uint32_t)2U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_QUAD_READ                                                              ((uint32_t)3U)

#define QSPI_SPI_SETUP1_REG_RSVD_1_SHIFT                                                                    ((uint32_t)14U)
#define QSPI_SPI_SETUP1_REG_RSVD_1_MASK                                                                     ((uint32_t)0x0000c000U)

#define QSPI_SPI_SETUP1_REG_WCMD_SHIFT                                                                      ((uint32_t)16U)
#define QSPI_SPI_SETUP1_REG_WCMD_MASK                                                                       ((uint32_t)0x00ff0000U)

#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_SHIFT                                                                ((uint32_t)24U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_MASK                                                                 ((uint32_t)0x1f000000U)

#define QSPI_SPI_SETUP1_REG_RSVD_2_SHIFT                                                                    ((uint32_t)29U)
#define QSPI_SPI_SETUP1_REG_RSVD_2_MASK                                                                     ((uint32_t)0xe0000000U)

#define QSPI_SPI_SETUP2_REG_RCMD_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_SETUP2_REG_RCMD_MASK                                                                       ((uint32_t)0x000000ffU)

#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_SHIFT                                                               ((uint32_t)8U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_MASK                                                                ((uint32_t)0x00000300U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_ONE_BYTE                                                             ((uint32_t)0U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_TWO_BYTES                                                            ((uint32_t)1U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_THREE_BYTES                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_FOUR_BYTES                                                           ((uint32_t)3U)

#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_SHIFT                                                               ((uint32_t)10U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_MASK                                                                ((uint32_t)0x00000c00U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_NUM_D_BITS                                                       ((uint32_t)0U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_8_BITS                                                           ((uint32_t)1U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_16_BITS                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_24_BITS                                                          ((uint32_t)3U)

#define QSPI_SPI_SETUP2_REG_READ_TYPE_SHIFT                                                                 ((uint32_t)12U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_MASK                                                                  ((uint32_t)0x00003000U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_NORMAL_READ                                                            ((uint32_t)0U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_DUAL_READ                                                              ((uint32_t)1U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_NORMAL_READ_TYPE                                                       ((uint32_t)2U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_QUAD_READ                                                              ((uint32_t)3U)

#define QSPI_SPI_SETUP2_REG_RSVD_1_SHIFT                                                                    ((uint32_t)14U)
#define QSPI_SPI_SETUP2_REG_RSVD_1_MASK                                                                     ((uint32_t)0x0000c000U)

#define QSPI_SPI_SETUP2_REG_WCMD_SHIFT                                                                      ((uint32_t)16U)
#define QSPI_SPI_SETUP2_REG_WCMD_MASK                                                                       ((uint32_t)0x00ff0000U)

#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_SHIFT                                                                ((uint32_t)24U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_MASK                                                                 ((uint32_t)0x1f000000U)

#define QSPI_SPI_SETUP2_REG_RSVD_2_SHIFT                                                                    ((uint32_t)29U)
#define QSPI_SPI_SETUP2_REG_RSVD_2_MASK                                                                     ((uint32_t)0xe0000000U)

#define QSPI_SPI_SETUP3_REG_RCMD_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_SETUP3_REG_RCMD_MASK                                                                       ((uint32_t)0x000000ffU)

#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_SHIFT                                                               ((uint32_t)8U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_MASK                                                                ((uint32_t)0x00000300U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_ONE_BYTE                                                             ((uint32_t)0U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_TWO_BYTES                                                            ((uint32_t)1U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_THREE_BYTES                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_FOUR_BYTES                                                           ((uint32_t)3U)

#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_SHIFT                                                               ((uint32_t)10U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_MASK                                                                ((uint32_t)0x00000c00U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_NUM_D_BITS                                                       ((uint32_t)0U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_8_BITS                                                           ((uint32_t)1U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_16_BITS                                                          ((uint32_t)2U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_24_BITS                                                          ((uint32_t)3U)

#define QSPI_SPI_SETUP3_REG_READ_TYPE_SHIFT                                                                 ((uint32_t)12U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_MASK                                                                  ((uint32_t)0x00003000U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_NORMAL_READ                                                            ((uint32_t)0U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_DUAL_READ                                                              ((uint32_t)1U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_NORMAL_READ_TYPE                                                       ((uint32_t)2U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_QUAD_READ                                                              ((uint32_t)3U)

#define QSPI_SPI_SETUP3_REG_RSVD_1_SHIFT                                                                    ((uint32_t)14U)
#define QSPI_SPI_SETUP3_REG_RSVD_1_MASK                                                                     ((uint32_t)0x0000c000U)

#define QSPI_SPI_SETUP3_REG_WCMD_SHIFT                                                                      ((uint32_t)16U)
#define QSPI_SPI_SETUP3_REG_WCMD_MASK                                                                       ((uint32_t)0x00ff0000U)

#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_SHIFT                                                                ((uint32_t)24U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_MASK                                                                 ((uint32_t)0x1f000000U)

#define QSPI_SPI_SETUP3_REG_RSVD_2_SHIFT                                                                    ((uint32_t)29U)
#define QSPI_SPI_SETUP3_REG_RSVD_2_MASK                                                                     ((uint32_t)0xe0000000U)

#define QSPI_SPI_DATA_REG_1_DATA_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_DATA_REG_1_DATA_MASK                                                                       ((uint32_t)0xffffffffU)

#define QSPI_SPI_DATA_REG_2_DATA_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_DATA_REG_2_DATA_MASK                                                                       ((uint32_t)0xffffffffU)

#define QSPI_SPI_DATA_REG_3_DATA_SHIFT                                                                      ((uint32_t)0U)
#define QSPI_SPI_DATA_REG_3_DATA_MASK                                                                       ((uint32_t)0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_QSPI_H_ */
