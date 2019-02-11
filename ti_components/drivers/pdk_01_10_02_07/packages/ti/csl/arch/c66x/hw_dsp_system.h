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
*  \file    hw_dsp_system.h
*
*  \brief   register-level header file for DSP
*
**/

#ifndef HW_DSP_SYSTEM_H_
#define HW_DSP_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define DSP_REVISION                                                                                        ((uint32_t)(0x0U))
#define DSP_HWINFO                                                                                          ((uint32_t)(0x4U))
#define DSP_SYSCONFIG                                                                                       ((uint32_t)(0x8U))
#define DSP_STAT                                                                                            ((uint32_t)(0xcU))
#define DSP_DISC_CONFIG                                                                                     ((uint32_t)(0x10U))
#define DSP_BUS_CONFIG                                                                                      ((uint32_t)(0x14U))
#define DSP_MMU_CONFIG                                                                                      ((uint32_t)(0x18U))
#define DSP_IRQWAKEEN0                                                                                      ((uint32_t)(0x20U))
#define DSP_IRQWAKEEN1                                                                                      ((uint32_t)(0x24U))
#define DSP_DMAWAKEEN0                                                                                      ((uint32_t)(0x30U))
#define DSP_DMAWAKEEN1                                                                                      ((uint32_t)(0x34U))
#define DSP_EVTOUT_SET                                                                                      ((uint32_t)(0x40U))
#define DSP_EVTOUT_CLR                                                                                      ((uint32_t)(0x44U))
#define DSP_ERRINT_IRQSTATUS_RAW                                                                            ((uint32_t)(0x50U))
#define DSP_ERRINT_IRQSTATUS                                                                                ((uint32_t)(0x54U))
#define DSP_ERRINT_IRQENABLE_SET                                                                            ((uint32_t)(0x58U))
#define DSP_ERRINT_IRQENABLE_CLR                                                                            ((uint32_t)(0x5cU))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW                                                                         ((uint32_t)(0x60U))
#define DSP_EDMAWAKE0_IRQSTATUS                                                                             ((uint32_t)(0x64U))
#define DSP_EDMAWAKE0_IRQENABLE_SET                                                                         ((uint32_t)(0x68U))
#define DSP_EDMAWAKE0_IRQENABLE_CLR                                                                         ((uint32_t)(0x6cU))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW                                                                         ((uint32_t)(0x70U))
#define DSP_EDMAWAKE1_IRQSTATUS                                                                             ((uint32_t)(0x74U))
#define DSP_EDMAWAKE1_IRQENABLE_SET                                                                         ((uint32_t)(0x78U))
#define DSP_EDMAWAKE1_IRQENABLE_CLR                                                                         ((uint32_t)(0x7cU))
#define DSP_HW_DBGOUT_SEL                                                                                   ((uint32_t)(0xf8U))
#define DSP_HW_DBGOUT_VAL                                                                                   ((uint32_t)(0xfcU))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSP_REVISION_REVISION_SHIFT                                                                          ((uint32_t)(0U))
#define DSP_REVISION_REVISION_MASK                                                                           ((uint32_t)(0xffffffffU))

#define DSP_HWINFO_NUM_SHIFT                                                                                 ((uint32_t)(0U))
#define DSP_HWINFO_NUM_MASK                                                                                  ((uint32_t)(0x0000000fU))

#define DSP_HWINFO_INFO_SHIFT                                                                                ((uint32_t)(4U))
#define DSP_HWINFO_INFO_MASK                                                                                 ((uint32_t)(0xfffffff0U))

#define DSP_SYSCONFIG_SOFTRESET_SHIFT                                                                        ((uint32_t)(0U))
#define DSP_SYSCONFIG_SOFTRESET_MASK                                                                         ((uint32_t)(0x00000001U))

#define DSP_SYSCONFIG_FREE_EMU_SHIFT                                                                         ((uint32_t)(1U))
#define DSP_SYSCONFIG_FREE_EMU_MASK                                                                          ((uint32_t)(0x00000002U))

#define DSP_SYSCONFIG_IDLEMODE_SHIFT                                                                         ((uint32_t)(2U))
#define DSP_SYSCONFIG_IDLEMODE_MASK                                                                          ((uint32_t)(0x0000000cU))
#define DSP_SYSCONFIG_IDLEMODE_SMARTIDLEWKUP                                                                 ((uint32_t)(3U))
#define DSP_SYSCONFIG_IDLEMODE_FORCE_IDLE                                                                    ((uint32_t)(0U))
#define DSP_SYSCONFIG_IDLEMODE_NO_IDLE                                                                       ((uint32_t)(1U))
#define DSP_SYSCONFIG_IDLEMODE_SMART_IDLE                                                                    ((uint32_t)(2U))

#define DSP_SYSCONFIG_STANDBYMODE_SHIFT                                                                      ((uint32_t)(4U))
#define DSP_SYSCONFIG_STANDBYMODE_MASK                                                                       ((uint32_t)(0x00000030U))
#define DSP_SYSCONFIG_STANDBYMODE_SMART_STANDBY_WKUP                                                         ((uint32_t)(3U))
#define DSP_SYSCONFIG_STANDBYMODE_SMART_STAND_BY                                                             ((uint32_t)(2U))
#define DSP_SYSCONFIG_STANDBYMODE_FORCE_STANDBY                                                              ((uint32_t)(0U))
#define DSP_SYSCONFIG_STANDBYMODE_NO_STANDBY                                                                 ((uint32_t)(1U))

#define DSP_SYSCONFIG_RESERVED_SHIFT                                                                         ((uint32_t)(9U))
#define DSP_SYSCONFIG_RESERVED_MASK                                                                          ((uint32_t)(0xfffffe00U))

#define DSP_SYSCONFIG_DSP_IDLEREQ_SHIFT                                                                      ((uint32_t)(8U))
#define DSP_SYSCONFIG_DSP_IDLEREQ_MASK                                                                       ((uint32_t)(0x00000100U))
#define DSP_SYSCONFIG_DSP_IDLEREQ_NOREQ                                                                      ((uint32_t)(0U))
#define DSP_SYSCONFIG_DSP_IDLEREQ_IDLEREQ                                                                    ((uint32_t)(1U))

#define DSP_SYSCONFIG_RESERVED_2_SHIFT                                                                       ((uint32_t)(6U))
#define DSP_SYSCONFIG_RESERVED_2_MASK                                                                        ((uint32_t)(0x000000c0U))

#define DSP_STAT_C66X_STAT_SHIFT                                                                             ((uint32_t)(0U))
#define DSP_STAT_C66X_STAT_MASK                                                                              ((uint32_t)(0x00000001U))
#define DSP_STAT_C66X_STAT_IDLE                                                                              ((uint32_t)(0U))
#define DSP_STAT_C66X_STAT_ACTIVE                                                                            ((uint32_t)(1U))

#define DSP_STAT_TC0_STAT_SHIFT                                                                              ((uint32_t)(1U))
#define DSP_STAT_TC0_STAT_MASK                                                                               ((uint32_t)(0x00000002U))
#define DSP_STAT_TC0_STAT_IDLE                                                                               ((uint32_t)(0U))
#define DSP_STAT_TC0_STAT_ACTIVE                                                                             ((uint32_t)(1U))

#define DSP_STAT_TC1_STAT_SHIFT                                                                              ((uint32_t)(2U))
#define DSP_STAT_TC1_STAT_MASK                                                                               ((uint32_t)(0x00000004U))
#define DSP_STAT_TC1_STAT_IDLE                                                                               ((uint32_t)(0U))
#define DSP_STAT_TC1_STAT_ACTIVE                                                                             ((uint32_t)(1U))

#define DSP_STAT_RESERVED_SHIFT                                                                              ((uint32_t)(3U))
#define DSP_STAT_RESERVED_MASK                                                                               ((uint32_t)(0x00000008U))

#define DSP_STAT_OCPI_DISC_STAT_SHIFT                                                                        ((uint32_t)(4U))
#define DSP_STAT_OCPI_DISC_STAT_MASK                                                                         ((uint32_t)(0x00000030U))
#define DSP_STAT_OCPI_DISC_STAT_OCP_INITIATOR_DISCONNECT                                                     ((uint32_t)(0U))
#define DSP_STAT_OCPI_DISC_STAT_OCP_TRYING_TO_DISCONNECT                                                     ((uint32_t)(1U))
#define DSP_STAT_OCPI_DISC_STAT_OCP_INITIATOR_ACTIVE                                                         ((uint32_t)(2U))

#define DSP_STAT_RESERVED_2_SHIFT                                                                            ((uint32_t)(6U))
#define DSP_STAT_RESERVED_2_MASK                                                                             ((uint32_t)(0xffffffc0U))

#define DSP_DISC_CONFIG_OCPI_DISC_SHIFT                                                                      ((uint32_t)(0U))
#define DSP_DISC_CONFIG_OCPI_DISC_MASK                                                                       ((uint32_t)(0x00000001U))
#define DSP_DISC_CONFIG_OCPI_DISC_WRITE0                                                                     ((uint32_t)(0U))
#define DSP_DISC_CONFIG_OCPI_DISC_WRITE1                                                                     ((uint32_t)(1U))
#define DSP_DISC_CONFIG_OCPI_DISC_READ0                                                                      ((uint32_t)(0U))
#define DSP_DISC_CONFIG_OCPI_DISC_READ1                                                                      ((uint32_t)(1U))

#define DSP_DISC_CONFIG_RESERVED_SHIFT                                                                       ((uint32_t)(1U))
#define DSP_DISC_CONFIG_RESERVED_MASK                                                                        ((uint32_t)(0xfffffffeU))

#define DSP_BUS_CONFIG_TC0_DBS_SHIFT                                                                         ((uint32_t)(0U))
#define DSP_BUS_CONFIG_TC0_DBS_MASK                                                                          ((uint32_t)(0x00000003U))
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_16                                                                       ((uint32_t)(0U))
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_32                                                                       ((uint32_t)(1U))
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_64                                                                       ((uint32_t)(2U))
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_128                                                                      ((uint32_t)(3U))

#define DSP_BUS_CONFIG_RESERVED_SHIFT                                                                        ((uint32_t)(2U))
#define DSP_BUS_CONFIG_RESERVED_MASK                                                                         ((uint32_t)(0x0000000cU))

#define DSP_BUS_CONFIG_TC1_DBS_SHIFT                                                                         ((uint32_t)(4U))
#define DSP_BUS_CONFIG_TC1_DBS_MASK                                                                          ((uint32_t)(0x00000030U))
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_16                                                                       ((uint32_t)(0U))
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_32                                                                       ((uint32_t)(1U))
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_64                                                                       ((uint32_t)(2U))
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_128                                                                      ((uint32_t)(3U))

#define DSP_BUS_CONFIG_RESERVED_2_SHIFT                                                                      ((uint32_t)(6U))
#define DSP_BUS_CONFIG_RESERVED_2_MASK                                                                       ((uint32_t)(0x000000c0U))

#define DSP_BUS_CONFIG_TC0_L2PRES_SHIFT                                                                      ((uint32_t)(8U))
#define DSP_BUS_CONFIG_TC0_L2PRES_MASK                                                                       ((uint32_t)(0x00000300U))
#define DSP_BUS_CONFIG_TC0_L2PRES_LOW                                                                        ((uint32_t)(0U))
#define DSP_BUS_CONFIG_TC0_L2PRES_MED                                                                        ((uint32_t)(1U))
#define DSP_BUS_CONFIG_TC0_L2PRES_HIGH                                                                       ((uint32_t)(3U))

#define DSP_BUS_CONFIG_TC1_L2PRES_SHIFT                                                                      ((uint32_t)(12U))
#define DSP_BUS_CONFIG_TC1_L2PRES_MASK                                                                       ((uint32_t)(0x00003000U))
#define DSP_BUS_CONFIG_TC1_L2PRES_LOW                                                                        ((uint32_t)(0U))
#define DSP_BUS_CONFIG_TC1_L2PRES_MED                                                                        ((uint32_t)(1U))
#define DSP_BUS_CONFIG_TC1_L2PRES_HIGH                                                                       ((uint32_t)(3U))

#define DSP_BUS_CONFIG_CFG_L2PRES_SHIFT                                                                      ((uint32_t)(16U))
#define DSP_BUS_CONFIG_CFG_L2PRES_MASK                                                                       ((uint32_t)(0x00030000U))
#define DSP_BUS_CONFIG_CFG_L2PRES_LOW                                                                        ((uint32_t)(0U))
#define DSP_BUS_CONFIG_CFG_L2PRES_MED                                                                        ((uint32_t)(1U))
#define DSP_BUS_CONFIG_CFG_L2PRES_HIGH                                                                       ((uint32_t)(3U))

#define DSP_BUS_CONFIG_SDMA_L2PRES_SHIFT                                                                     ((uint32_t)(20U))
#define DSP_BUS_CONFIG_SDMA_L2PRES_MASK                                                                      ((uint32_t)(0x00300000U))
#define DSP_BUS_CONFIG_SDMA_L2PRES_LOW                                                                       ((uint32_t)(0U))
#define DSP_BUS_CONFIG_SDMA_L2PRES_MED                                                                       ((uint32_t)(1U))
#define DSP_BUS_CONFIG_SDMA_L2PRES_HIGH                                                                      ((uint32_t)(3U))

#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_SHIFT                                                                  ((uint32_t)(24U))
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_MASK                                                                   ((uint32_t)(0x01000000U))
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_MIX                                                                    ((uint32_t)(0U))
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_NOPOST                                                                 ((uint32_t)(1U))

#define DSP_BUS_CONFIG_SDMA_PRI_SHIFT                                                                        ((uint32_t)(28U))
#define DSP_BUS_CONFIG_SDMA_PRI_MASK                                                                         ((uint32_t)(0x70000000U))

#define DSP_BUS_CONFIG_RESERVED_3_SHIFT                                                                      ((uint32_t)(31U))
#define DSP_BUS_CONFIG_RESERVED_3_MASK                                                                       ((uint32_t)(0x80000000U))

#define DSP_BUS_CONFIG_RESERVED_4_SHIFT                                                                      ((uint32_t)(10U))
#define DSP_BUS_CONFIG_RESERVED_4_MASK                                                                       ((uint32_t)(0x00000c00U))

#define DSP_BUS_CONFIG_RESERVED_5_SHIFT                                                                      ((uint32_t)(14U))
#define DSP_BUS_CONFIG_RESERVED_5_MASK                                                                       ((uint32_t)(0x0000c000U))

#define DSP_BUS_CONFIG_RESERVED_6_SHIFT                                                                      ((uint32_t)(18U))
#define DSP_BUS_CONFIG_RESERVED_6_MASK                                                                       ((uint32_t)(0x000c0000U))

#define DSP_BUS_CONFIG_RESERVED_7_SHIFT                                                                      ((uint32_t)(22U))
#define DSP_BUS_CONFIG_RESERVED_7_MASK                                                                       ((uint32_t)(0x00c00000U))

#define DSP_BUS_CONFIG_RESERVED_8_SHIFT                                                                      ((uint32_t)(25U))
#define DSP_BUS_CONFIG_RESERVED_8_MASK                                                                       ((uint32_t)(0x0e000000U))

#define DSP_MMU_CONFIG_MMU0_EN_SHIFT                                                                         ((uint32_t)(0U))
#define DSP_MMU_CONFIG_MMU0_EN_MASK                                                                          ((uint32_t)(0x00000001U))
#define DSP_MMU_CONFIG_MMU0_EN_DISABLED                                                                      ((uint32_t)(0U))
#define DSP_MMU_CONFIG_MMU0_EN_ENABLED                                                                       ((uint32_t)(1U))

#define DSP_MMU_CONFIG_RESERVED_SHIFT                                                                        ((uint32_t)(1U))
#define DSP_MMU_CONFIG_RESERVED_MASK                                                                         ((uint32_t)(0x0000000eU))

#define DSP_MMU_CONFIG_MMU1_EN_SHIFT                                                                         ((uint32_t)(4U))
#define DSP_MMU_CONFIG_MMU1_EN_MASK                                                                          ((uint32_t)(0x00000010U))
#define DSP_MMU_CONFIG_MMU1_EN_DISABLED                                                                      ((uint32_t)(0U))
#define DSP_MMU_CONFIG_MMU1_EN_ENABLED                                                                       ((uint32_t)(1U))

#define DSP_MMU_CONFIG_RESERVED_2_SHIFT                                                                      ((uint32_t)(5U))
#define DSP_MMU_CONFIG_RESERVED_2_MASK                                                                       ((uint32_t)(0x000000e0U))

#define DSP_MMU_CONFIG_MMU0_ABORT_SHIFT                                                                      ((uint32_t)(8U))
#define DSP_MMU_CONFIG_MMU0_ABORT_MASK                                                                       ((uint32_t)(0x00000100U))
#define DSP_MMU_CONFIG_MMU0_ABORT_NOABORT                                                                    ((uint32_t)(0U))
#define DSP_MMU_CONFIG_MMU0_ABORT_ABORT                                                                      ((uint32_t)(1U))

#define DSP_MMU_CONFIG_RESERVED_3_SHIFT                                                                      ((uint32_t)(9U))
#define DSP_MMU_CONFIG_RESERVED_3_MASK                                                                       ((uint32_t)(0x00000e00U))

#define DSP_MMU_CONFIG_MMU1_ABORT_SHIFT                                                                      ((uint32_t)(12U))
#define DSP_MMU_CONFIG_MMU1_ABORT_MASK                                                                       ((uint32_t)(0x00001000U))
#define DSP_MMU_CONFIG_MMU1_ABORT_NOABORT                                                                    ((uint32_t)(0U))
#define DSP_MMU_CONFIG_MMU1_ABORT_ABORT                                                                      ((uint32_t)(1U))

#define DSP_MMU_CONFIG_RESERVED_4_SHIFT                                                                      ((uint32_t)(13U))
#define DSP_MMU_CONFIG_RESERVED_4_MASK                                                                       ((uint32_t)(0xffffe000U))

#define DSP_IRQWAKEEN0_ENABLE_SHIFT                                                                          ((uint32_t)(0U))
#define DSP_IRQWAKEEN0_ENABLE_MASK                                                                           ((uint32_t)(0xffffffffU))
#define DSP_IRQWAKEEN0_ENABLE_DISABLE                                                                        ((uint32_t)(0U))
#define DSP_IRQWAKEEN0_ENABLE_ENABLE                                                                         ((uint32_t)(1U))

#define DSP_IRQWAKEEN1_ENABLE_SHIFT                                                                          ((uint32_t)(0U))
#define DSP_IRQWAKEEN1_ENABLE_MASK                                                                           ((uint32_t)(0xffffffffU))
#define DSP_IRQWAKEEN1_ENABLE_DISABLE                                                                        ((uint32_t)(0U))
#define DSP_IRQWAKEEN1_ENABLE_ENABLE                                                                         ((uint32_t)(1U))

#define DSP_DMAWAKEEN0_ENABLE_SHIFT                                                                          ((uint32_t)(0U))
#define DSP_DMAWAKEEN0_ENABLE_MASK                                                                           ((uint32_t)(0xffffffffU))
#define DSP_DMAWAKEEN0_ENABLE_DISABLE                                                                        ((uint32_t)(0U))
#define DSP_DMAWAKEEN0_ENABLE_ENABLE                                                                         ((uint32_t)(1U))

#define DSP_DMAWAKEEN1_ENABLE_SHIFT                                                                          ((uint32_t)(0U))
#define DSP_DMAWAKEEN1_ENABLE_MASK                                                                           ((uint32_t)(0xffffffffU))
#define DSP_DMAWAKEEN1_ENABLE_DISABLE                                                                        ((uint32_t)(0U))
#define DSP_DMAWAKEEN1_ENABLE_ENABLE                                                                         ((uint32_t)(1U))

#define DSP_EVTOUT_SET_EVENT_SHIFT                                                                           ((uint32_t)(0U))
#define DSP_EVTOUT_SET_EVENT_MASK                                                                            ((uint32_t)(0xffffffffU))
#define DSP_EVTOUT_SET_EVENT_WRITE0                                                                          ((uint32_t)(0U))
#define DSP_EVTOUT_SET_EVENT_READ0                                                                           ((uint32_t)(0U))
#define DSP_EVTOUT_SET_EVENT_WRITE1                                                                          ((uint32_t)(1U))
#define DSP_EVTOUT_SET_EVENT_READ1                                                                           ((uint32_t)(1U))

#define DSP_EVTOUT_CLR_EVENT_SHIFT                                                                           ((uint32_t)(0U))
#define DSP_EVTOUT_CLR_EVENT_MASK                                                                            ((uint32_t)(0xffffffffU))
#define DSP_EVTOUT_CLR_EVENT_WRITE0                                                                          ((uint32_t)(0U))
#define DSP_EVTOUT_CLR_EVENT_WRITE1                                                                          ((uint32_t)(1U))
#define DSP_EVTOUT_CLR_EVENT_READ0                                                                           ((uint32_t)(0U))
#define DSP_EVTOUT_CLR_EVENT_READ1                                                                           ((uint32_t)(1U))

#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_SHIFT                                                                 ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_MASK                                                                  ((uint32_t)(0x007fffffU))
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_W0                                                                    ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_W1                                                                    ((uint32_t)(1U))
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_R0                                                                    ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_R1                                                                    ((uint32_t)(1U))

#define DSP_ERRINT_IRQSTATUS_RAW_RESERVED_SHIFT                                                              ((uint32_t)(23U))
#define DSP_ERRINT_IRQSTATUS_RAW_RESERVED_MASK                                                               ((uint32_t)(0xff800000U))

#define DSP_ERRINT_IRQSTATUS_EVENT_SHIFT                                                                     ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_EVENT_MASK                                                                      ((uint32_t)(0x007fffffU))
#define DSP_ERRINT_IRQSTATUS_EVENT_W0                                                                        ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_EVENT_W1                                                                        ((uint32_t)(1U))
#define DSP_ERRINT_IRQSTATUS_EVENT_R0                                                                        ((uint32_t)(0U))
#define DSP_ERRINT_IRQSTATUS_EVENT_R1                                                                        ((uint32_t)(1U))

#define DSP_ERRINT_IRQSTATUS_RESERVED_SHIFT                                                                  ((uint32_t)(23U))
#define DSP_ERRINT_IRQSTATUS_RESERVED_MASK                                                                   ((uint32_t)(0x07800000U))

#define DSP_ERRINT_IRQENABLE_SET_ENABLE_SHIFT                                                                ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_MASK                                                                 ((uint32_t)(0x007fffffU))
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_W0                                                                   ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_W1                                                                   ((uint32_t)(1U))
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_R0                                                                   ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_R1                                                                   ((uint32_t)(1U))

#define DSP_ERRINT_IRQENABLE_SET_RESERVED_SHIFT                                                              ((uint32_t)(23U))
#define DSP_ERRINT_IRQENABLE_SET_RESERVED_MASK                                                               ((uint32_t)(0x07800000U))

#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_SHIFT                                                                ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_MASK                                                                 ((uint32_t)(0x007fffffU))
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_W0                                                                   ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_W1                                                                   ((uint32_t)(1U))
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_R0                                                                   ((uint32_t)(0U))
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_R1                                                                   ((uint32_t)(1U))

#define DSP_ERRINT_IRQENABLE_CLR_RESERVED_SHIFT                                                              ((uint32_t)(23U))
#define DSP_ERRINT_IRQENABLE_CLR_RESERVED_MASK                                                               ((uint32_t)(0x07800000U))

#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_SHIFT                                                              ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_MASK                                                               ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_W0                                                                 ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_W1                                                                 ((uint32_t)(1U))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_R0                                                                 ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_R1                                                                 ((uint32_t)(1U))

#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_SHIFT                                                                  ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_MASK                                                                   ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_W0                                                                     ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_W1                                                                     ((uint32_t)(1U))
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_R0                                                                     ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_R1                                                                     ((uint32_t)(1U))

#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_SHIFT                                                             ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_MASK                                                              ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_W0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_W1                                                                ((uint32_t)(1U))
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_R0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_R1                                                                ((uint32_t)(1U))

#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_SHIFT                                                             ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_MASK                                                              ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_W0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_W1                                                                ((uint32_t)(1U))
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_R0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_R1                                                                ((uint32_t)(1U))

#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_SHIFT                                                              ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_MASK                                                               ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_W0                                                                 ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_W1                                                                 ((uint32_t)(1U))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_R0                                                                 ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_R1                                                                 ((uint32_t)(1U))

#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_SHIFT                                                                  ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_MASK                                                                   ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_W0                                                                     ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_W1                                                                     ((uint32_t)(1U))
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_R0                                                                     ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_R1                                                                     ((uint32_t)(1U))

#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_SHIFT                                                             ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_MASK                                                              ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_W0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_W1                                                                ((uint32_t)(1U))
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_R0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_R1                                                                ((uint32_t)(1U))

#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_SHIFT                                                             ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_MASK                                                              ((uint32_t)(0xffffffffU))
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_W0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_W1                                                                ((uint32_t)(1U))
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_R0                                                                ((uint32_t)(0U))
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_R1                                                                ((uint32_t)(1U))

#define DSP_HW_DBGOUT_SEL_GROUP_SHIFT                                                                        ((uint32_t)(0U))
#define DSP_HW_DBGOUT_SEL_GROUP_MASK                                                                         ((uint32_t)(0x0000000fU))
#define DSP_HW_DBGOUT_SEL_GROUP_DISABLED                                                                     ((uint32_t)(0U))
#define DSP_HW_DBGOUT_SEL_GROUP_G1                                                                           ((uint32_t)(1U))
#define DSP_HW_DBGOUT_SEL_GROUP_G2                                                                           ((uint32_t)(2U))
#define DSP_HW_DBGOUT_SEL_GROUP_GN                                                                           ((uint32_t)(2U))

#define DSP_HW_DBGOUT_VAL_VALUE_SHIFT                                                                        ((uint32_t)(0U))
#define DSP_HW_DBGOUT_VAL_VALUE_MASK                                                                         ((uint32_t)(0xffffffffU))

#ifdef __cplusplus
}
#endif
#endif  /* _HW_DSP_SYSTEM_H_ */
