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
 * \file  hw_pciectrl_ti_conf.h
 *
 * \brief Register-level header file for PCIECTRL_TI_CONF [default]
 *
**/

#ifndef HW_PCIECTRL_TI_CONF_H_
#define HW_PCIECTRL_TI_CONF_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Component offset
****************************************************************************************************/
#define PCIECTRL_TI_CONF_OFFSET                                     ((uint32_t)0x2000U)


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PCIECTRL_TI_CONF_REVISION                                   ((uint32_t)0x0U)
#define PCIECTRL_TI_CONF_SYSCONFIG                                  ((uint32_t)0x10U)
#define PCIECTRL_TI_CONF_IRQ_EOI                                    ((uint32_t)0x18U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN                         ((uint32_t)0x20U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN                             ((uint32_t)0x24U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN                         ((uint32_t)0x28U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN                         ((uint32_t)0x2cU)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI                          ((uint32_t)0x30U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI                              ((uint32_t)0x34U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI                          ((uint32_t)0x38U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI                          ((uint32_t)0x3cU)
#define PCIECTRL_TI_CONF_DEVICE_TYPE                                ((uint32_t)0x100U)
#define PCIECTRL_TI_CONF_DEVICE_CMD                                 ((uint32_t)0x104U)
#define PCIECTRL_TI_CONF_PM_CTRL                                    ((uint32_t)0x108U)
#define PCIECTRL_TI_CONF_PHY_CS                                     ((uint32_t)0x10cU)
#define PCIECTRL_TI_CONF_INTX_ASSERT                                ((uint32_t)0x124U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT                              ((uint32_t)0x128U)
#define PCIECTRL_TI_CONF_MSI_XMT                                    ((uint32_t)0x12cU)
#define PCIECTRL_TI_CONF_DEBUG_CFG                                  ((uint32_t)0x140U)
#define PCIECTRL_TI_CONF_DEBUG_DATA                                 ((uint32_t)0x144U)
#define PCIECTRL_TI_CONF_DIAG_CTRL                                  ((uint32_t)0x148U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PCIECTRL_TI_CONF_REVISION_Y_MINOR_SHIFT                                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_REVISION_Y_MINOR_MASK                                           ((uint32_t)0x0000003fU)

#define PCIECTRL_TI_CONF_REVISION_CUSTOM_SHIFT                                           ((uint32_t)6U)
#define PCIECTRL_TI_CONF_REVISION_CUSTOM_MASK                                            ((uint32_t)0x000000c0U)
#define PCIECTRL_TI_CONF_REVISION_CUSTOM_STANDARD                                        ((uint32_t)0U)

#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_SHIFT                                          ((uint32_t)8U)
#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_MASK                                           ((uint32_t)0x00000700U)
#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_C1                                             ((uint32_t)2U)

#define PCIECTRL_TI_CONF_REVISION_R_RTL_SHIFT                                            ((uint32_t)11U)
#define PCIECTRL_TI_CONF_REVISION_R_RTL_MASK                                             ((uint32_t)0x0000f800U)

#define PCIECTRL_TI_CONF_REVISION_FUNC_SHIFT                                             ((uint32_t)16U)
#define PCIECTRL_TI_CONF_REVISION_FUNC_MASK                                              ((uint32_t)0x0fff0000U)

#define PCIECTRL_TI_CONF_REVISION_SCHEME_SHIFT                                           ((uint32_t)30U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_MASK                                            ((uint32_t)0xc0000000U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_H08                                             ((uint32_t)1U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_LEGACY                                          ((uint32_t)0U)

#define PCIECTRL_TI_CONF_REVISION_BU_SHIFT                                               ((uint32_t)28U)
#define PCIECTRL_TI_CONF_REVISION_BU_MASK                                                ((uint32_t)0x30000000U)
#define PCIECTRL_TI_CONF_REVISION_BU_WBU                                                 ((uint32_t)1U)
#define PCIECTRL_TI_CONF_REVISION_BU_DSPS                                                ((uint32_t)0U)

#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SHIFT                                        ((uint32_t)2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_MASK                                         ((uint32_t)0x0000000cU)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_FORCE                                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_NO                                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SMART                                        ((uint32_t)2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SMART_WAKEUP                                 ((uint32_t)3U)

#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SHIFT                                     ((uint32_t)4U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_MASK                                      ((uint32_t)0x00000030U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_FORCE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_NO                                        ((uint32_t)1U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SMART                                     ((uint32_t)2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SMART_WAKEUP                              ((uint32_t)3U)

#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_SHIFT                                    ((uint32_t)16U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_MASK                                     ((uint32_t)0x00010000U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_DIS                                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN                                          ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_SHIFT                                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MASK                                        ((uint32_t)0x0000000fU)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_READ0                                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MAIN                                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MSI                                         ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_SHIFT                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_MASK                                 ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_SET                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_SHIFT                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_MASK                               ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_NONE                               ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_PENDING                            ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_NOACTION                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_SET                                ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_SHIFT                           ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_MASK                            ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_NONE                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_PENDING                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_NOACTION                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_SET                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_SHIFT                                ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_MASK                                 ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_SET                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_SHIFT                                ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_MASK                                 ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_SET                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_SHIFT                               ((uint32_t)5U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_MASK                                ((uint32_t)0x00000020U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_NONE                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_PENDING                             ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_NOACTION                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_SET                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_SHIFT                           ((uint32_t)8U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_MASK                            ((uint32_t)0x00000100U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_NONE                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_PENDING                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_NOACTION                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_SET                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_SHIFT                             ((uint32_t)9U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_MASK                              ((uint32_t)0x00000200U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_NONE                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_PENDING                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_SET                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_SHIFT                                 ((uint32_t)10U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_MASK                                  ((uint32_t)0x00000400U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_NONE                                  ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_PENDING                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_SET                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_SHIFT                           ((uint32_t)11U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_MASK                            ((uint32_t)0x00000800U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_NONE                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_PENDING                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_NOACTION                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_SET                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_SHIFT                            ((uint32_t)12U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_MASK                             ((uint32_t)0x00001000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_NONE                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_PENDING                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_NOACTION                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_SET                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_SHIFT                            ((uint32_t)13U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_MASK                             ((uint32_t)0x00002000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_NONE                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_PENDING                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_NOACTION                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_SET                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_SHIFT                            ((uint32_t)14U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_MASK                             ((uint32_t)0x00004000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_NONE                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_PENDING                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_NOACTION                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_SET                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_SHIFT                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_MASK                                     ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_CLEAR                                    ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_SHIFT                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_MASK                                   ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_NONE                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_PENDING                                ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_NOACTION                               ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_CLEAR                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_SHIFT                               ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_MASK                                ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_NONE                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_PENDING                             ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_NOACTION                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_CLEAR                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_SHIFT                                    ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_MASK                                     ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_CLEAR                                    ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_SHIFT                                    ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_MASK                                     ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_CLEAR                                    ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_SHIFT                                   ((uint32_t)5U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_MASK                                    ((uint32_t)0x00000020U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_NONE                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_PENDING                                 ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_NOACTION                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_CLEAR                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_SHIFT                               ((uint32_t)8U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_MASK                                ((uint32_t)0x00000100U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_NONE                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_PENDING                             ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_NOACTION                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_CLEAR                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_SHIFT                                 ((uint32_t)9U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_MASK                                  ((uint32_t)0x00000200U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_NONE                                  ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_PENDING                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_CLEAR                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_SHIFT                                     ((uint32_t)10U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_MASK                                      ((uint32_t)0x00000400U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_NONE                                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_PENDING                                   ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_NOACTION                                  ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_CLEAR                                     ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_SHIFT                               ((uint32_t)11U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_MASK                                ((uint32_t)0x00000800U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_NONE                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_PENDING                             ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_NOACTION                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_CLEAR                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_SHIFT                                ((uint32_t)12U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_MASK                                 ((uint32_t)0x00001000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_CLEAR                                ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_SHIFT                                ((uint32_t)13U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_MASK                                 ((uint32_t)0x00002000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_CLEAR                                ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_SHIFT                                ((uint32_t)14U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_MASK                                 ((uint32_t)0x00004000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_NONE                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_PENDING                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_NOACTION                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_CLEAR                                ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_SHIFT                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_MASK                              ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_SHIFT                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_MASK                            ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_DISABLED                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_ENABLED                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_NOACTION                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_SHIFT                        ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_MASK                         ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_SHIFT                             ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_MASK                              ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_SHIFT                             ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_MASK                              ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_SHIFT                            ((uint32_t)5U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_MASK                             ((uint32_t)0x00000020U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_DISABLED                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_ENABLED                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_NOACTION                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_SHIFT                        ((uint32_t)8U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_MASK                         ((uint32_t)0x00000100U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_SHIFT                          ((uint32_t)9U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_MASK                           ((uint32_t)0x00000200U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_DISABLED                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_ENABLED                        ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_NOACTION                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN                                ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_SHIFT                              ((uint32_t)10U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_MASK                               ((uint32_t)0x00000400U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_DISABLED                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_ENABLED                            ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_NOACTION                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN                                    ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_SHIFT                        ((uint32_t)11U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_MASK                         ((uint32_t)0x00000800U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_SHIFT                         ((uint32_t)12U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_MASK                          ((uint32_t)0x00001000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_SHIFT                         ((uint32_t)13U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_MASK                          ((uint32_t)0x00002000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_SHIFT                         ((uint32_t)14U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_MASK                          ((uint32_t)0x00004000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_SHIFT                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_MASK                              ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_CLEAR                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_SHIFT                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_MASK                            ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_DISABLED                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_ENABLED                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_NOACTION                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_CLEAR                           ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_SHIFT                        ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_MASK                         ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_CLEAR                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_SHIFT                             ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_MASK                              ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_CLEAR                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_SHIFT                             ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_MASK                              ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_DISABLED                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_ENABLED                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_NOACTION                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_CLEAR                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_SHIFT                            ((uint32_t)5U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_MASK                             ((uint32_t)0x00000020U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_DISABLED                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_ENABLED                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_NOACTION                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_CLEAR                            ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_SHIFT                        ((uint32_t)8U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_MASK                         ((uint32_t)0x00000100U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_CLEAR                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_SHIFT                          ((uint32_t)9U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_MASK                           ((uint32_t)0x00000200U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_DISABLED                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_ENABLED                        ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_NOACTION                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_CLEAR                          ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_SHIFT                              ((uint32_t)10U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_MASK                               ((uint32_t)0x00000400U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_DISABLED                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_ENABLED                            ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_NOACTION                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_CLEAR                              ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_SHIFT                        ((uint32_t)11U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_MASK                         ((uint32_t)0x00000800U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_DISABLED                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_ENABLED                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_NOACTION                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_CLEAR                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_SHIFT                         ((uint32_t)12U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_MASK                          ((uint32_t)0x00001000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_CLEAR                         ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_SHIFT                         ((uint32_t)13U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_MASK                          ((uint32_t)0x00002000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_CLEAR                         ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_SHIFT                         ((uint32_t)14U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_MASK                          ((uint32_t)0x00004000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_DISABLED                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_ENABLED                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_NOACTION                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_CLEAR                         ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_SHIFT                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_MASK                                     ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_SET                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_SHIFT                                    ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_MASK                                     ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_SET                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_SHIFT                                    ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_MASK                                     ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_SET                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_SHIFT                                    ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_MASK                                     ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_NONE                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_PENDING                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_NOACTION                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_SET                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_SHIFT                                         ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_MASK                                          ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_NONE                                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_PENDING                                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_NOACTION                                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_SET                                           ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_SHIFT                                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_MASK                                         ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_NONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_PENDING                                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_NOACTION                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_CLEAR                                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_SHIFT                                        ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_MASK                                         ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_NONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_PENDING                                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_NOACTION                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_CLEAR                                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_SHIFT                                        ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_MASK                                         ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_NONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_PENDING                                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_NOACTION                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_CLEAR                                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_SHIFT                                        ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_MASK                                         ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_NONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_PENDING                                      ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_NOACTION                                     ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_CLEAR                                        ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_SHIFT                                             ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_MASK                                              ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_NONE                                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_PENDING                                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_NOACTION                                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_CLEAR                                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_SHIFT                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_MASK                                  ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN                                       ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_SHIFT                                 ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_MASK                                  ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN                                       ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_SHIFT                                 ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_MASK                                  ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN                                       ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_SHIFT                                 ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_MASK                                  ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN                                       ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_SHIFT                                      ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_MASK                                       ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_NONE                                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_PENDING                                    ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_NOACTION                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_CLEAR                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_SHIFT                                 ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_MASK                                  ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_CLEAR                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_SHIFT                                 ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_MASK                                  ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_CLEAR                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_SHIFT                                 ((uint32_t)2U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_MASK                                  ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_CLEAR                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_SHIFT                                 ((uint32_t)3U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_MASK                                  ((uint32_t)0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_DISABLED                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_ENABLED                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_NOACTION                              ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_CLEAR                                 ((uint32_t)1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_SHIFT                                      ((uint32_t)4U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_MASK                                       ((uint32_t)0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_DISABLED                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_ENABLED                                    ((uint32_t)1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_NOACTION                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_CLEAR                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_DEVICE_TYPE_SHIFT                                               ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_MASK                                                ((uint32_t)0x0000000fU)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_EP                                                  ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_LEG_EP                                              ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_RC                                                  ((uint32_t)4U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_SHIFT                                    ((uint32_t)2U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_MASK                                     ((uint32_t)0x000000fcU)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_QUIET                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_ACT                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_ACTIVE                              ((uint32_t)2U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_COMPLIANCE                          ((uint32_t)3U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_CONFIG                              ((uint32_t)4U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_PRE_DETECT_QUIET                         ((uint32_t)5U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_WAIT                              ((uint32_t)6U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LINKWD_START                         ((uint32_t)7U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LINKWD_ACEPT                         ((uint32_t)8U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LANENUM_WAIT                         ((uint32_t)9U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LANENUM_ACEPT                        ((uint32_t)10U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_COMPLETE                             ((uint32_t)11U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_IDLE                                 ((uint32_t)12U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_LOCK                               ((uint32_t)13U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_SPEED                              ((uint32_t)14U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_RCVRCFG                            ((uint32_t)15U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_IDLE                               ((uint32_t)16U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L0                                       ((uint32_t)17U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L0S                                      ((uint32_t)18U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L123_SEND_EIDLE                          ((uint32_t)19U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L1_IDLE                                  ((uint32_t)20U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L2_IDLE                                  ((uint32_t)21U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L2_WAKE                                  ((uint32_t)22U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED_ENTRY                           ((uint32_t)23U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED_IDLE                            ((uint32_t)24U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED                                 ((uint32_t)25U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_ENTRY                               ((uint32_t)26U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_ACTIVE                              ((uint32_t)27U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_EXIT                                ((uint32_t)28U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_EXIT_TIMEOUT                        ((uint32_t)29U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_HOT_RESET_ENTRY                          ((uint32_t)30U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_HOT_RESET                                ((uint32_t)31U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ0                                ((uint32_t)32U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ1                                ((uint32_t)33U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ2                                ((uint32_t)34U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ3                                ((uint32_t)35U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_SHIFT                                       ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_MASK                                        ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_DISABLED                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_ENABLED                                     ((uint32_t)1U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_SHIFT                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_MASK                                ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_DISABLED                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_ENABLED                             ((uint32_t)1U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_DEV_NUM_SHIFT                                        ((uint32_t)16U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_DEV_NUM_MASK                                         ((uint32_t)0x001f0000U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_BUS_NUM_SHIFT                                        ((uint32_t)21U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_BUS_NUM_MASK                                         ((uint32_t)0x1fe00000U)

#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_SHIFT                                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_MASK                                       ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_TRANSMIT                                   ((uint32_t)1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_NOACTION                                   ((uint32_t)0U)

#define PCIECTRL_TI_CONF_PM_CTRL_PME_SHIFT                                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_MASK                                                ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TRANSMIT                                            ((uint32_t)1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_NOACTION                                            ((uint32_t)0U)

#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_SHIFT                                         ((uint32_t)8U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_MASK                                          ((uint32_t)0x00000100U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_NOT                                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY                                               ((uint32_t)1U)

#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_SHIFT                                       ((uint32_t)9U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_MASK                                        ((uint32_t)0x00000200U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_INACTIVE                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_ACTIVE                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_SHIFT                                       ((uint32_t)10U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_MASK                                        ((uint32_t)0x00000400U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_INACTIVE                                    ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_ACTIVE                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_SHIFT                                       ((uint32_t)11U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_MASK                                        ((uint32_t)0x00000800U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_UNPOWERED                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_POWERED                                     ((uint32_t)1U)

#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_SHIFT                                            ((uint32_t)16U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_MASK                                             ((uint32_t)0x00010000U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_DOWN                                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP                                                  ((uint32_t)1U)

#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_SHIFT                                      ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_MASK                                       ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_STRAIGHT                                   ((uint32_t)0U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_REVERSED                                   ((uint32_t)1U)

#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_SHIFT                                            ((uint32_t)0U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_MASK                                             ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_ACTIVE                                           ((uint32_t)0U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_INACTIVE                                         ((uint32_t)1U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0                                                  ((uint32_t)1U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_NOACTION                                         ((uint32_t)0U)

#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_SHIFT                                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_MASK                                           ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_ACTIVE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_INACTIVE                                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0                                                ((uint32_t)1U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_NOACTION                                       ((uint32_t)0U)

#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_SHIFT                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_MASK                                          ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT                                               ((uint32_t)1U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_PENDING                                       ((uint32_t)1U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_DONE                                          ((uint32_t)0U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_NO_ACTION                                     ((uint32_t)0U)

#define PCIECTRL_TI_CONF_MSI_XMT_FUNC_NUM_SHIFT                                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_MSI_XMT_FUNC_NUM_MASK                                           ((uint32_t)0x0000000eU)

#define PCIECTRL_TI_CONF_MSI_XMT_VECTOR_SHIFT                                            ((uint32_t)7U)
#define PCIECTRL_TI_CONF_MSI_XMT_VECTOR_MASK                                             ((uint32_t)0x00000f80U)

#define PCIECTRL_TI_CONF_MSI_XMT_TC_SHIFT                                                ((uint32_t)4U)
#define PCIECTRL_TI_CONF_MSI_XMT_TC_MASK                                                 ((uint32_t)0x00000070U)

#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_SHIFT                                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_MASK                                              ((uint32_t)0x0000003fU)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_TIELO                                             ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PIPE_L0                                           ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PIPE_L1                                           ((uint32_t)2U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_INFO_LO                                           ((uint32_t)4U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_INFO_HI                                           ((uint32_t)5U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PM                                                ((uint32_t)3U)

#define PCIECTRL_TI_CONF_DEBUG_DATA_SHIFT                                                ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DEBUG_DATA_MASK                                                 ((uint32_t)0xffffffffU)

#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_SHIFT                                        ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_MASK                                         ((uint32_t)0x00000001U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_REQ                                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_DONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_PENDING                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_SHIFT                                        ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_MASK                                         ((uint32_t)0x00000002U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_REQ                                          ((uint32_t)1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_DONE                                         ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_PENDING                                      ((uint32_t)1U)

#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_SHIFT                                  ((uint32_t)2U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_MASK                                   ((uint32_t)0x00000004U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_STANDARD                               ((uint32_t)0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE                                        ((uint32_t)1U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_PCIECTRL_TI_CONF_H_ */
