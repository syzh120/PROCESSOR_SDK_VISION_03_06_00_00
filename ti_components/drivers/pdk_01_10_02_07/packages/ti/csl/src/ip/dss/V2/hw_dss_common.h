/*
* hw_dss_common.h
*
* Register-level header file for DSS
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

#ifndef HW_DSS_COMMON_H_
#define HW_DSS_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_DISPC_REVISION                                          (0x0U)
#define DSS_DISPC_SYSCONFIG                                         (0x4U)
#define DSS_DISPC_SYSSTATUS                                         (0x8U)
#define DSS_DISPC_IRQ_EOI                                           (0x20U)
#define DSS_DISPC_IRQSTATUS_RAW                                     (0x24U)
#define DSS_DISPC_IRQSTATUS                                         (0x28U)
#define DSS_DISPC_IRQENABLE_SET                                     (0x2cU)
#define DSS_DISPC_IRQENABLE_CLR                                     (0x30U)
#define DSS_DISPC_IRQWAKEEN                                         (0x34U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE                            (0x40U)
#define DSS_DISPC_GLOBAL_BUFFER                                     (0x44U)
#define DSS_DISPC_BA0_FLIPIMMEDIATE_EN                              (0x48U)
#define DSS_DISPC_DBG_CONTROL                                       (0x4cU)
#define DSS_DISPC_DBG_STATUS                                        (0x50U)
#define DSS_DISPC_CLKGATING_DISABLE                                 (0x54U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_DISPC_REVISION_REV_SHIFT                                                    (0U)
#define DSS_DISPC_REVISION_REV_MASK                                                     (0x000000ffU)

#define DSS_DISPC_SYSCONFIG_SOFTRESET_SHIFT                                             (1U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_MASK                                              (0x00000002U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_NMODE                                              (0U)
#define DSS_DISPC_SYSCONFIG_SOFTRESET_RST                                                (1U)

#define DSS_DISPC_SYSCONFIG_SIDLEMODE_SHIFT                                             (3U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_MASK                                              (0x00000018U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_FIDLE                                              (0U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_NIDLE                                              (1U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_SIDLE                                              (2U)
#define DSS_DISPC_SYSCONFIG_SIDLEMODE_RES                                                (3U)

#define DSS_DISPC_SYSCONFIG_MIDLEMODE_SHIFT                                             (12U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_MASK                                              (0x00003000U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_FSTANDBY                                           (0U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_NSTANDBY                                           (1U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_SSTANDBY                                           (2U)
#define DSS_DISPC_SYSCONFIG_MIDLEMODE_RES                                                (3U)

#define DSS_DISPC_SYSCONFIG_AUTOIDLE_SHIFT                                              (0U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_MASK                                               (0x00000001U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKFREE                                             (0U)
#define DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKGATED                                            (1U)

#define DSS_DISPC_SYSCONFIG_ENWAKEUP_SHIFT                                              (2U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_MASK                                               (0x00000004U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPENB                                           (1U)
#define DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPDIS                                           (0U)

#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_SHIFT                                         (8U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_MASK                                          (0x00000300U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCOFF                                     (0U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCON                                      (3U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPOFF                                         (2U)
#define DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_FUNCOFF                                        (1U)

#define DSS_DISPC_SYSCONFIG_WARMRESET_SHIFT                                             (5U)
#define DSS_DISPC_SYSCONFIG_WARMRESET_MASK                                              (0x00000020U)
#define DSS_DISPC_SYSCONFIG_WARMRESET_NORMAL                                             (0U)
#define DSS_DISPC_SYSCONFIG_WARMRESET                                                    (1U)

#define DSS_DISPC_SYSSTATUS_FUNC_RESETDONE_SHIFT                                        (0U)
#define DSS_DISPC_SYSSTATUS_FUNC_RESETDONE_MASK                                         (0x00000001U)
#define DSS_DISPC_SYSSTATUS_FUNC_RESETDONE_RSTONGOING                                    (0U)
#define DSS_DISPC_SYSSTATUS_FUNC_RESETDONE_RSTCOMP                                       (1U)

#define DSS_DISPC_SYSSTATUS_VP1_RESETDONE_SHIFT                                         (1U)
#define DSS_DISPC_SYSSTATUS_VP1_RESETDONE_MASK                                          (0x00000002U)
#define DSS_DISPC_SYSSTATUS_VP1_RESETDONE_RSTONGOING                                     (0U)
#define DSS_DISPC_SYSSTATUS_VP1_RESETDONE_RSTCOMP                                        (1U)

#define DSS_DISPC_IRQ_EOI_LINE_NUMBER_SHIFT                                             (0U)
#define DSS_DISPC_IRQ_EOI_LINE_NUMBER_MASK                                              (0x00000001U)
#define DSS_DISPC_IRQ_EOI_LINE_NUMBER_READ0                                              (0U)
#define DSS_DISPC_IRQ_EOI_LINE_NUMBER_EOI0                                               (0U)

#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_SHIFT                                           (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_MASK                                            (0x00000001U)
#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_NONE                                             (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_PENDING                                          (1U)
#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_NOACTION                                         (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VP1_IRQ_SET_EVENT                                        (1U)

#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_SHIFT                                          (4U)
#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_MASK                                           (0x00000010U)
#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_NONE                                            (0U)
#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_PENDING                                         (1U)
#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQSTATUS_RAW_GFX1_IRQ_SET_EVENT                                       (1U)

#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_SHIFT                                          (7U)
#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_MASK                                           (0x00000080U)
#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_NONE                                            (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_PENDING                                         (1U)
#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VID1_IRQ_SET_EVENT                                       (1U)

#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_SHIFT                                          (8U)
#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_MASK                                           (0x00000100U)
#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_NONE                                            (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_PENDING                                         (1U)
#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQSTATUS_RAW_VID2_IRQ_SET_EVENT                                       (1U)

#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_SHIFT                                            (11U)
#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_MASK                                             (0x00000800U)
#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_NONE                                              (0U)
#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_PENDING                                           (1U)
#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_NOACTION                                          (0U)
#define DSS_DISPC_IRQSTATUS_RAW_WB_IRQ_SET_EVENT                                         (1U)

#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_SHIFT                                        (13U)
#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_MASK                                         (0x00002000U)
#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_NONE                                          (0U)
#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_PENDING                                       (1U)
#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_NOACTION                                      (0U)
#define DSS_DISPC_IRQSTATUS_RAW_WAKEUP_IRQ_SET_EVENT                                     (1U)

#define DSS_DISPC_IRQSTATUS_VP1_IRQ_SHIFT                                               (0U)
#define DSS_DISPC_IRQSTATUS_VP1_IRQ_MASK                                                (0x00000001U)
#define DSS_DISPC_IRQSTATUS_VP1_IRQ_NONE                                                 (0U)
#define DSS_DISPC_IRQSTATUS_VP1_IRQ_PENDING                                              (1U)
#define DSS_DISPC_IRQSTATUS_VP1_IRQ_NOACTION                                             (0U)
#define DSS_DISPC_IRQSTATUS_VP1_IRQ_CLEAR                                                (1U)

#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_SHIFT                                              (4U)
#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_MASK                                               (0x00000010U)
#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_NONE                                                (0U)
#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_PENDING                                             (1U)
#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_NOACTION                                            (0U)
#define DSS_DISPC_IRQSTATUS_GFX1_IRQ_CLEAR                                               (1U)

#define DSS_DISPC_IRQSTATUS_VID1_IRQ_SHIFT                                              (7U)
#define DSS_DISPC_IRQSTATUS_VID1_IRQ_MASK                                               (0x00000080U)
#define DSS_DISPC_IRQSTATUS_VID1_IRQ_NONE                                                (0U)
#define DSS_DISPC_IRQSTATUS_VID1_IRQ_PENDING                                             (1U)
#define DSS_DISPC_IRQSTATUS_VID1_IRQ_NOACTION                                            (0U)
#define DSS_DISPC_IRQSTATUS_VID1_IRQ_CLEAR                                               (1U)

#define DSS_DISPC_IRQSTATUS_VID2_IRQ_SHIFT                                              (8U)
#define DSS_DISPC_IRQSTATUS_VID2_IRQ_MASK                                               (0x00000100U)
#define DSS_DISPC_IRQSTATUS_VID2_IRQ_NONE                                                (0U)
#define DSS_DISPC_IRQSTATUS_VID2_IRQ_PENDING                                             (1U)
#define DSS_DISPC_IRQSTATUS_VID2_IRQ_NOACTION                                            (0U)
#define DSS_DISPC_IRQSTATUS_VID2_IRQ_CLEAR                                               (1U)

#define DSS_DISPC_IRQSTATUS_WB_IRQ_SHIFT                                                (11U)
#define DSS_DISPC_IRQSTATUS_WB_IRQ_MASK                                                 (0x00000800U)
#define DSS_DISPC_IRQSTATUS_WB_IRQ_NONE                                                  (0U)
#define DSS_DISPC_IRQSTATUS_WB_IRQ_PENDING                                               (1U)
#define DSS_DISPC_IRQSTATUS_WB_IRQ_NOACTION                                              (0U)
#define DSS_DISPC_IRQSTATUS_WB_IRQ_CLEAR                                                 (1U)

#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_SHIFT                                            (13U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_MASK                                             (0x00002000U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_NONE                                              (0U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_PENDING                                           (1U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_NOACTION                                          (0U)
#define DSS_DISPC_IRQSTATUS_WAKEUP_IRQ_CLEAR                                             (1U)

#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_SHIFT                                        (13U)
#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_MASK                                         (0x00002000U)
#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_DISABLED                                      (0U)
#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_ENABLED                                       (1U)
#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_NOACTION                                      (0U)
#define DSS_DISPC_IRQENABLE_SET_WAKEUP_IRQ_ENABLE                                        (1U)

#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_SHIFT                                           (0U)
#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_MASK                                            (0x00000001U)
#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_DISABLED                                         (0U)
#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_ENABLED                                          (1U)
#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_NOACTION                                         (0U)
#define DSS_DISPC_IRQENABLE_SET_VP1_IRQ_ENABLE                                           (1U)

#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_SHIFT                                          (4U)
#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_MASK                                           (0x00000010U)
#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_ENABLE                                          (1U)

#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_SHIFT                                          (7U)
#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_MASK                                           (0x00000080U)
#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_VID1_IRQ_ENABLE                                          (1U)

#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_SHIFT                                          (8U)
#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_MASK                                           (0x00000100U)
#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_SET_VID2_IRQ_ENABLE                                          (1U)

#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_SHIFT                                            (11U)
#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_MASK                                             (0x00000800U)
#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_DISABLED                                          (0U)
#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_ENABLED                                           (1U)
#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_NOACTION                                          (0U)
#define DSS_DISPC_IRQENABLE_SET_WB_IRQ_ENABLE                                            (1U)

#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_SHIFT                                        (13U)
#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_MASK                                         (0x00002000U)
#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_DISABLED                                      (0U)
#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_ENABLED                                       (1U)
#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_NOACTION                                      (0U)
#define DSS_DISPC_IRQENABLE_CLR_WAKEUP_IRQ_DISABLE                                       (1U)

#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_SHIFT                                           (0U)
#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_MASK                                            (0x00000001U)
#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_DISABLED                                         (0U)
#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_ENABLED                                          (1U)
#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_NOACTION                                         (0U)
#define DSS_DISPC_IRQENABLE_CLR_VP1_IRQ_DISABLE                                          (1U)

#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_SHIFT                                          (4U)
#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_MASK                                           (0x00000010U)
#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_GFX1_IRQ_DISABLE                                         (1U)

#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_SHIFT                                          (7U)
#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_MASK                                           (0x00000080U)
#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_VID1_IRQ_DISABLE                                         (1U)

#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_SHIFT                                          (8U)
#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_MASK                                           (0x00000100U)
#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_DISABLED                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_ENABLED                                         (1U)
#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_NOACTION                                        (0U)
#define DSS_DISPC_IRQENABLE_CLR_VID2_IRQ_DISABLE                                         (1U)

#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_SHIFT                                            (11U)
#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_MASK                                             (0x00000800U)
#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_DISABLED                                          (0U)
#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_ENABLED                                           (1U)
#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_NOACTION                                          (0U)
#define DSS_DISPC_IRQENABLE_CLR_WB_IRQ_DISABLE                                           (1U)

#define DSS_DISPC_IRQWAKEEN_VP1_SHIFT                                                   (0U)
#define DSS_DISPC_IRQWAKEEN_VP1_MASK                                                    (0x00000001U)
#define DSS_DISPC_IRQWAKEEN_VP1_SWAKEUPDIS                                               (0U)
#define DSS_DISPC_IRQWAKEEN_VP1_SWAKEUPEN                                                (1U)

#define DSS_DISPC_IRQWAKEEN_GFX1_SHIFT                                                  (4U)
#define DSS_DISPC_IRQWAKEEN_GFX1_MASK                                                   (0x00000010U)
#define DSS_DISPC_IRQWAKEEN_GFX1_SWAKEUPDIS                                              (0U)
#define DSS_DISPC_IRQWAKEEN_GFX1_SWAKEUPEN                                               (1U)

#define DSS_DISPC_IRQWAKEEN_VID1_SHIFT                                                  (7U)
#define DSS_DISPC_IRQWAKEEN_VID1_MASK                                                   (0x00000080U)
#define DSS_DISPC_IRQWAKEEN_VID1_SWAKEUPDIS                                              (0U)
#define DSS_DISPC_IRQWAKEEN_VID1_SWAKEUPEN                                               (1U)

#define DSS_DISPC_IRQWAKEEN_VID2_SHIFT                                                  (8U)
#define DSS_DISPC_IRQWAKEEN_VID2_MASK                                                   (0x00000100U)
#define DSS_DISPC_IRQWAKEEN_VID2_SWAKEUPDIS                                              (0U)
#define DSS_DISPC_IRQWAKEEN_VID2_SWAKEUPEN                                               (1U)

#define DSS_DISPC_IRQWAKEEN_WB_SHIFT                                                    (11U)
#define DSS_DISPC_IRQWAKEEN_WB_MASK                                                     (0x00000800U)
#define DSS_DISPC_IRQWAKEEN_WB_SWAKEUPDIS                                                (0U)
#define DSS_DISPC_IRQWAKEEN_WB_SWAKEUPEN                                                 (1U)

#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL_SHIFT                                     (0U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL_MASK                                      (0x00000003U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL_MFLAGDIS                                   (0U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL_MFLAGFORCE                                 (1U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL_MFLAGEN                                    (2U)

#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START_SHIFT                                    (2U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START_MASK                                     (0x00000004U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START_MFLAGNORMALSTARTMODE                      (0U)
#define DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START_MFLAGFORCESTARTMODE                       (1U)

#define DSS_DISPC_GLOBAL_BUFFER_VID1_SHIFT                                              (9U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_MASK                                               (0x00000e00U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1                                                     (4U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_VID2                                                (5U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_VID3                                                (6U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_WB                                                  (7U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_GFX1                                                (1U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_GFX2                                                (2U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_GFX3                                                (3U)
#define DSS_DISPC_GLOBAL_BUFFER_VID1_UNUSED                                              (0U)

#define DSS_DISPC_GLOBAL_BUFFER_WB_SHIFT                                                (18U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_MASK                                                 (0x001c0000U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_VID1                                                  (4U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_VID2                                                  (5U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_VID3                                                  (6U)
#define DSS_DISPC_GLOBAL_BUFFER_WB                                                       (7U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_GFX1                                                  (1U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_GFX2                                                  (2U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_GFX3                                                  (3U)
#define DSS_DISPC_GLOBAL_BUFFER_WB_UNUSED                                                (0U)

#define DSS_DISPC_GLOBAL_BUFFER_BUFFERFILLING_SHIFT                                     (31U)
#define DSS_DISPC_GLOBAL_BUFFER_BUFFERFILLING_MASK                                      (0x80000000U)
#define DSS_DISPC_GLOBAL_BUFFER_BUFFERFILLING_INDIVIDUALPIPE                             (0U)
#define DSS_DISPC_GLOBAL_BUFFER_BUFFERFILLING_ALLPIPES                                   (1U)

#define DSS_DISPC_DBG_CONTROL_DBGEN_SHIFT                                               (0U)
#define DSS_DISPC_DBG_CONTROL_DBGEN_MASK                                                (0x00000001U)
#define DSS_DISPC_DBG_CONTROL_DBGEN                                                      (1U)
#define DSS_DISPC_DBG_CONTROL_DBGEN_DBGDIS                                               (0U)

#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_SHIFT                                           (1U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_MASK                                            (0x000001feU)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL0                                         (0U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL1                                         (1U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL2                                         (2U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL3                                         (3U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL4                                         (4U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL5                                         (5U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL6                                         (6U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID1SEL7                                         (7U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL0                                         (8U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL1                                         (9U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL2                                         (10U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL3                                         (11U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL4                                         (12U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL5                                         (13U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL6                                         (14U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID2SEL7                                         (15U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL0                                         (16U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL1                                         (17U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL2                                         (18U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL3                                         (19U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL4                                         (20U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL5                                         (21U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL6                                         (22U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VID3SEL7                                         (23U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_WBSEL                                            (24U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_OVR1SEL                                          (25U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_OVR2SEL                                          (26U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_OVR3SEL                                          (27U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_OVR4SEL                                          (28U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_GFX1SEL                                          (29U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_GFX2SEL                                          (30U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_GFX3SEL                                          (31U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VP1SEL                                           (32U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VP2SEL                                           (33U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VP3SEL                                           (34U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_VP4SEL                                           (35U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_GLBCE1SEL                                        (36U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_GLBCE2SEL                                        (37U)
#define DSS_DISPC_DBG_CONTROL_DBGMUXSEL_RESERVED                                         (38U)

#define DSS_DISPC_DBG_STATUS_DBGOUT_SHIFT                                               (0U)
#define DSS_DISPC_DBG_STATUS_DBGOUT_MASK                                                (0xffffffffU)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_COMMON_SHIFT                                    (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_COMMON_MASK                                     (0x00000001U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_COMMON_CLKGATINGEN                               (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_COMMON_CLKGATINGDIS                              (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH1_SHIFT                                       (1U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH1_MASK                                        (0x00000002U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH1_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH1_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH2_SHIFT                                       (2U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH2_MASK                                        (0x00000004U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH2_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH2_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH3_SHIFT                                       (3U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH3_MASK                                        (0x00000008U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH3_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH3_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH4_SHIFT                                       (4U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH4_MASK                                        (0x00000010U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH4_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH4_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH5_SHIFT                                       (5U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH5_MASK                                        (0x00000020U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH5_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH5_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH6_SHIFT                                       (6U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH6_MASK                                        (0x00000040U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH6_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH6_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH7_SHIFT                                       (7U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH7_MASK                                        (0x00000080U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH7_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH7_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH8_SHIFT                                       (8U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH8_MASK                                        (0x00000100U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH8_CLKGATINGEN                                  (0U)
#define DSS_DISPC_CLKGATING_DISABLE_DMA_CH8_CLKGATINGDIS                                 (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VID1_SHIFT                                          (9U)
#define DSS_DISPC_CLKGATING_DISABLE_VID1_MASK                                           (0x00000200U)
#define DSS_DISPC_CLKGATING_DISABLE_VID1_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VID1_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VID2_SHIFT                                          (10U)
#define DSS_DISPC_CLKGATING_DISABLE_VID2_MASK                                           (0x00000400U)
#define DSS_DISPC_CLKGATING_DISABLE_VID2_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VID2_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VID3_SHIFT                                          (11U)
#define DSS_DISPC_CLKGATING_DISABLE_VID3_MASK                                           (0x00000800U)
#define DSS_DISPC_CLKGATING_DISABLE_VID3_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VID3_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_GFX1_SHIFT                                          (12U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX1_MASK                                           (0x00001000U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX1_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX1_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_GFX2_SHIFT                                          (13U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX2_MASK                                           (0x00002000U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX2_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX2_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_GFX3_SHIFT                                          (14U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX3_MASK                                           (0x00004000U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX3_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_GFX3_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_GLBCE1_SHIFT                                        (15U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE1_MASK                                         (0x00008000U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE1_CLKGATINGEN                                   (0U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE1_CLKGATINGDIS                                  (1U)

#define DSS_DISPC_CLKGATING_DISABLE_GLBCE2_SHIFT                                        (16U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE2_MASK                                         (0x00010000U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE2_CLKGATINGEN                                   (0U)
#define DSS_DISPC_CLKGATING_DISABLE_GLBCE2_CLKGATINGDIS                                  (1U)

#define DSS_DISPC_CLKGATING_DISABLE_WB_SHIFT                                            (17U)
#define DSS_DISPC_CLKGATING_DISABLE_WB_MASK                                             (0x00020000U)
#define DSS_DISPC_CLKGATING_DISABLE_WB_CLKGATINGEN                                       (0U)
#define DSS_DISPC_CLKGATING_DISABLE_WB_CLKGATINGDIS                                      (1U)

#define DSS_DISPC_CLKGATING_DISABLE_CUR_SHIFT                                           (18U)
#define DSS_DISPC_CLKGATING_DISABLE_CUR_MASK                                            (0x00040000U)
#define DSS_DISPC_CLKGATING_DISABLE_CUR_CLKGATINGEN                                      (0U)
#define DSS_DISPC_CLKGATING_DISABLE_CUR_CLKGATINGDIS                                     (1U)

#define DSS_DISPC_CLKGATING_DISABLE_OVR1_SHIFT                                          (19U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR1_MASK                                           (0x00080000U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR1_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR1_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_OVR2_SHIFT                                          (20U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR2_MASK                                           (0x00100000U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR2_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR2_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_OVR3_SHIFT                                          (21U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR3_MASK                                           (0x00200000U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR3_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR3_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_OVR4_SHIFT                                          (22U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR4_MASK                                           (0x00400000U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR4_CLKGATINGEN                                     (0U)
#define DSS_DISPC_CLKGATING_DISABLE_OVR4_CLKGATINGDIS                                    (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VP1_SHIFT                                           (23U)
#define DSS_DISPC_CLKGATING_DISABLE_VP1_MASK                                            (0x00800000U)
#define DSS_DISPC_CLKGATING_DISABLE_VP1_CLKGATINGEN                                      (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VP1_CLKGATINGDIS                                     (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VP2_SHIFT                                           (24U)
#define DSS_DISPC_CLKGATING_DISABLE_VP2_MASK                                            (0x01000000U)
#define DSS_DISPC_CLKGATING_DISABLE_VP2_CLKGATINGEN                                      (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VP2_CLKGATINGDIS                                     (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VP3_SHIFT                                           (25U)
#define DSS_DISPC_CLKGATING_DISABLE_VP3_MASK                                            (0x02000000U)
#define DSS_DISPC_CLKGATING_DISABLE_VP3_CLKGATINGEN                                      (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VP3_CLKGATINGDIS                                     (1U)

#define DSS_DISPC_CLKGATING_DISABLE_VP4_SHIFT                                           (26U)
#define DSS_DISPC_CLKGATING_DISABLE_VP4_MASK                                            (0x04000000U)
#define DSS_DISPC_CLKGATING_DISABLE_VP4_CLKGATINGEN                                      (0U)
#define DSS_DISPC_CLKGATING_DISABLE_VP4_CLKGATINGDIS                                     (1U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_COMMON_H_ */

