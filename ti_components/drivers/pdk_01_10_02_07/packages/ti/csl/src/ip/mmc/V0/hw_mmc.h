/*
 *  Copyright (C) 2013-2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file hw_mmc.h
 *
 *  \brief Register-level header file for MMC
 *
**/

#ifndef HW_MMC_H_
#define HW_MMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MMC_HL_REV                                                                                          ((uint32_t)0x0U)
#define MMC_HL_HWINFO                                                                                       ((uint32_t)0x4U)
#define MMC_HL_SYSCONFIG                                                                                    ((uint32_t)0x10U)
#define MMC_SYSCONFIG                                                                                       ((uint32_t)0x110U)
#define MMC_SYSSTATUS                                                                                       ((uint32_t)0x114U)
#define MMC_CSRE                                                                                            ((uint32_t)0x124U)
#define MMC_SYSTEST                                                                                         ((uint32_t)0x128U)
#define MMC_CON                                                                                             ((uint32_t)0x12cU)
#define MMC_PWCNT                                                                                           ((uint32_t)0x130U)
#define MMC_DLL                                                                                             ((uint32_t)0x134U)
#define MMC_SDMASA                                                                                          ((uint32_t)0x200U)
#define MMC_BLK                                                                                             ((uint32_t)0x204U)
#define MMC_ARG                                                                                             ((uint32_t)0x208U)
#define MMC_CMD                                                                                             ((uint32_t)0x20cU)
#define MMC_RSP10                                                                                           ((uint32_t)0x210U)
#define MMC_RSP32                                                                                           ((uint32_t)0x214U)
#define MMC_RSP54                                                                                           ((uint32_t)0x218U)
#define MMC_RSP76                                                                                           ((uint32_t)0x21cU)
#define MMC_DATA                                                                                            ((uint32_t)0x220U)
#define MMC_PSTATE                                                                                          ((uint32_t)0x224U)
#define MMC_HCTL                                                                                            ((uint32_t)0x228U)
#define MMC_SYSCTL                                                                                          ((uint32_t)0x22cU)
#define MMC_STAT                                                                                            ((uint32_t)0x230U)
#define MMC_IE                                                                                              ((uint32_t)0x234U)
#define MMC_ISE                                                                                             ((uint32_t)0x238U)
#define MMC_AC12                                                                                            ((uint32_t)0x23cU)
#define MMC_CAPA                                                                                            ((uint32_t)0x240U)
#define MMC_CAPA2                                                                                           ((uint32_t)0x244U)
#define MMC_CUR_CAPA                                                                                        ((uint32_t)0x248U)
#define MMC_FE                                                                                              ((uint32_t)0x250U)
#define MMC_ADMAES                                                                                          ((uint32_t)0x254U)
#define MMC_ADMASAL                                                                                         ((uint32_t)0x258U)
#define MMC_PVINITSD                                                                                        ((uint32_t)0x260U)
#define MMC_PVHSSDR12                                                                                       ((uint32_t)0x264U)
#define MMC_PVSDR25SDR50                                                                                    ((uint32_t)0x268U)
#define MMC_PVSDR104DDR50                                                                                   ((uint32_t)0x26cU)
#define MMC_REV                                                                                             ((uint32_t)0x2fcU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MMC_HL_REV_REVISION_SHIFT                                                                            ((uint32_t)0U)
#define MMC_HL_REV_REVISION_MASK                                                                             ((uint32_t)0xffffffffU)
#define MMC_HL_REV_REVISION_LEGACY                                                                           ((uint32_t)0U)
#define MMC_HL_REV_REVISION_HIGHLANDER                                                                       ((uint32_t)1U)

#define MMC_HL_HWINFO_MADMA_EN_SHIFT                                                                         ((uint32_t)0U)
#define MMC_HL_HWINFO_MADMA_EN_MASK                                                                          ((uint32_t)0x00000001U)
#define MMC_HL_HWINFO_MADMA_EN_NOMASTERDMA                                                                   ((uint32_t)0U)
#define MMC_HL_HWINFO_MADMA_EN_SUPPORTADMA                                                                   ((uint32_t)1U)

#define MMC_HL_HWINFO_MERGE_MEM_SHIFT                                                                        ((uint32_t)1U)
#define MMC_HL_HWINFO_MERGE_MEM_MASK                                                                         ((uint32_t)0x00000002U)
#define MMC_HL_HWINFO_MERGE_MEM_TWOMEMBUFFER                                                                 ((uint32_t)0U)
#define MMC_HL_HWINFO_MERGE_MEM_SINGLEMEMBUFFER                                                              ((uint32_t)1U)

#define MMC_HL_HWINFO_MEM_SIZE_SHIFT                                                                         ((uint32_t)2U)
#define MMC_HL_HWINFO_MEM_SIZE_MASK                                                                          ((uint32_t)0x0000003cU)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_512                                                                       ((uint32_t)1U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_1024                                                                      ((uint32_t)2U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_2048                                                                      ((uint32_t)4U)
#define MMC_HL_HWINFO_MEM_SIZE_MEM_4096                                                                      ((uint32_t)8U)

#define MMC_HL_HWINFO_RETMODE_SHIFT                                                                          ((uint32_t)6U)
#define MMC_HL_HWINFO_RETMODE_MASK                                                                           ((uint32_t)0x00000040U)
#define MMC_HL_HWINFO_RETMODE_RETDISABLED                                                                    ((uint32_t)0U)
#define MMC_HL_HWINFO_RETMODE_RETENABLED                                                                     ((uint32_t)1U)

#define MMC_HL_HWINFO_RESERVED_SHIFT                                                                         ((uint32_t)7U)
#define MMC_HL_HWINFO_RESERVED_MASK                                                                          ((uint32_t)0xffffff80U)

#define MMC_HL_SYSCONFIG_SOFTRESET_SHIFT                                                                     ((uint32_t)0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_MASK                                                                      ((uint32_t)0x00000001U)
#define MMC_HL_SYSCONFIG_SOFTRESET_RESETDONE                                                                 ((uint32_t)0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_NOACTION                                                                  ((uint32_t)0U)
#define MMC_HL_SYSCONFIG_SOFTRESET_SOFTRESET                                                                 ((uint32_t)1U)
#define MMC_HL_SYSCONFIG_SOFTRESET_RESETONGOING                                                              ((uint32_t)1U)

#define MMC_HL_SYSCONFIG_FREEEMU_SHIFT                                                                       ((uint32_t)1U)
#define MMC_HL_SYSCONFIG_FREEEMU_MASK                                                                        ((uint32_t)0x00000002U)
#define MMC_HL_SYSCONFIG_FREEEMU_EMUEN                                                                       ((uint32_t)0U)
#define MMC_HL_SYSCONFIG_FREEEMU_EMUDIS                                                                      ((uint32_t)1U)

#define MMC_HL_SYSCONFIG_IDLEMODE_SHIFT                                                                      ((uint32_t)2U)
#define MMC_HL_SYSCONFIG_IDLEMODE_MASK                                                                       ((uint32_t)0x0000000cU)
#define MMC_HL_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                  ((uint32_t)0U)
#define MMC_HL_SYSCONFIG_IDLEMODE_NOIDLE                                                                     ((uint32_t)1U)
#define MMC_HL_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                  ((uint32_t)2U)
#define MMC_HL_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP                                                            ((uint32_t)3U)

#define MMC_HL_SYSCONFIG_STANDBYMODE_SHIFT                                                                   ((uint32_t)4U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_MASK                                                                    ((uint32_t)0x00000030U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_SMARTSTANDBYWAKEUP                                                      ((uint32_t)3U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_SMARTSTANDBY                                                            ((uint32_t)2U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_NOSTANDBY                                                               ((uint32_t)1U)
#define MMC_HL_SYSCONFIG_STANDBYMODE_FORCESTANDBY                                                            ((uint32_t)0U)

#define MMC_HL_SYSCONFIG_RESERVED_SHIFT                                                                      ((uint32_t)6U)
#define MMC_HL_SYSCONFIG_RESERVED_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                    ((uint32_t)8U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_MASK                                                                     ((uint32_t)0x00000300U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_NONE                                                                     ((uint32_t)0U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_FUNC                                                                     ((uint32_t)2U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_OCP                                                                      ((uint32_t)1U)
#define MMC_SYSCONFIG_CLOCKACTIVITY_BOTH                                                                     ((uint32_t)3U)

#define MMC_SYSCONFIG_SIDLEMODE_SHIFT                                                                        ((uint32_t)3U)
#define MMC_SYSCONFIG_SIDLEMODE_MASK                                                                         ((uint32_t)0x00000018U)
#define MMC_SYSCONFIG_SIDLEMODE_SMART                                                                        ((uint32_t)2U)
#define MMC_SYSCONFIG_SIDLEMODE_FORCE                                                                        ((uint32_t)0U)
#define MMC_SYSCONFIG_SIDLEMODE_NOIDLE                                                                       ((uint32_t)1U)
#define MMC_SYSCONFIG_SIDLEMODE_SMARTWAKE                                                                    ((uint32_t)3U)

#define MMC_SYSCONFIG_SOFTRESET_SHIFT                                                                        ((uint32_t)1U)
#define MMC_SYSCONFIG_SOFTRESET_MASK                                                                         ((uint32_t)0x00000002U)
#define MMC_SYSCONFIG_SOFTRESET_NORESET_R                                                                    ((uint32_t)0U)
#define MMC_SYSCONFIG_SOFTRESET_ONRESET_R                                                                    ((uint32_t)1U)
#define MMC_SYSCONFIG_SOFTRESET_ST_UN_W                                                                      ((uint32_t)0U)
#define MMC_SYSCONFIG_SOFTRESET_ST_RST_W                                                                     ((uint32_t)1U)

#define MMC_SYSCONFIG_AUTOIDLE_SHIFT                                                                         ((uint32_t)0U)
#define MMC_SYSCONFIG_AUTOIDLE_MASK                                                                          ((uint32_t)0x00000001U)
#define MMC_SYSCONFIG_AUTOIDLE_OFF                                                                           ((uint32_t)0U)
#define MMC_SYSCONFIG_AUTOIDLE_ON                                                                            ((uint32_t)1U)

#define MMC_SYSCONFIG_ENAWAKEUP_SHIFT                                                                        ((uint32_t)2U)
#define MMC_SYSCONFIG_ENAWAKEUP_MASK                                                                         ((uint32_t)0x00000004U)
#define MMC_SYSCONFIG_ENAWAKEUP_DISABLED                                                                     ((uint32_t)0U)
#define MMC_SYSCONFIG_ENAWAKEUP_ENABLE                                                                       ((uint32_t)1U)

#define MMC_SYSCONFIG_STANDBYMODE_SHIFT                                                                      ((uint32_t)12U)
#define MMC_SYSCONFIG_STANDBYMODE_MASK                                                                       ((uint32_t)0x00003000U)
#define MMC_SYSCONFIG_STANDBYMODE_NOIDLE                                                                     ((uint32_t)1U)
#define MMC_SYSCONFIG_STANDBYMODE_SMART                                                                      ((uint32_t)2U)
#define MMC_SYSCONFIG_STANDBYMODE_SMARTWAKE                                                                  ((uint32_t)3U)
#define MMC_SYSCONFIG_STANDBYMODE_FORCE                                                                      ((uint32_t)0U)

#define MMC_SYSCONFIG_RESERVED_SHIFT                                                                         ((uint32_t)5U)
#define MMC_SYSCONFIG_RESERVED_MASK                                                                          ((uint32_t)0x000000e0U)

#define MMC_SYSCONFIG_RESERVED1_SHIFT                                                                        ((uint32_t)10U)
#define MMC_SYSCONFIG_RESERVED1_MASK                                                                         ((uint32_t)0x00000c00U)

#define MMC_SYSCONFIG_RESERVED2_SHIFT                                                                        ((uint32_t)14U)
#define MMC_SYSCONFIG_RESERVED2_MASK                                                                         ((uint32_t)0xffffc000U)

#define MMC_SYSSTATUS_RESETDONE_SHIFT                                                                        ((uint32_t)0U)
#define MMC_SYSSTATUS_RESETDONE_MASK                                                                         ((uint32_t)0x00000001U)
#define MMC_SYSSTATUS_RESETDONE_DONE                                                                         ((uint32_t)1U)
#define MMC_SYSSTATUS_RESETDONE_ONGOING                                                                      ((uint32_t)0U)

#define MMC_SYSSTATUS_RESERVED_SHIFT                                                                         ((uint32_t)1U)
#define MMC_SYSSTATUS_RESERVED_MASK                                                                          ((uint32_t)0xfffffffeU)

#define MMC_CSRE_CSRE_SHIFT                                                                                  ((uint32_t)0U)
#define MMC_CSRE_CSRE_MASK                                                                                   ((uint32_t)0xffffffffU)

#define MMC_SYSTEST_WAKD_SHIFT                                                                               ((uint32_t)13U)
#define MMC_SYSTEST_WAKD_MASK                                                                                ((uint32_t)0x00002000U)
#define MMC_SYSTEST_WAKD_DRIVENHIGH_W                                                                        ((uint32_t)1U)
#define MMC_SYSTEST_WAKD_ZERO_R                                                                              ((uint32_t)0U)
#define MMC_SYSTEST_WAKD_ONE_R                                                                               ((uint32_t)1U)
#define MMC_SYSTEST_WAKD_DRIVENLOW_W                                                                         ((uint32_t)0U)

#define MMC_SYSTEST_D4D_SHIFT                                                                                ((uint32_t)8U)
#define MMC_SYSTEST_D4D_MASK                                                                                 ((uint32_t)0x00000100U)
#define MMC_SYSTEST_D4D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D4D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D4D_ONE_R                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_D4D_DRIVELOW_W                                                                           ((uint32_t)0U)

#define MMC_SYSTEST_CDIR_SHIFT                                                                               ((uint32_t)1U)
#define MMC_SYSTEST_CDIR_MASK                                                                                ((uint32_t)0x00000002U)
#define MMC_SYSTEST_CDIR_IN_W                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_CDIR_ZERO_R                                                                              ((uint32_t)0U)
#define MMC_SYSTEST_CDIR_OUT_W                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_CDIR_ONE_R                                                                               ((uint32_t)1U)

#define MMC_SYSTEST_D1D_SHIFT                                                                                ((uint32_t)5U)
#define MMC_SYSTEST_D1D_MASK                                                                                 ((uint32_t)0x00000020U)
#define MMC_SYSTEST_D1D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D1D_ONE_R                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_D1D_DRIVELOW_W                                                                           ((uint32_t)0U)
#define MMC_SYSTEST_D1D_ZERO_R                                                                               ((uint32_t)0U)

#define MMC_SYSTEST_SDWP_SHIFT                                                                               ((uint32_t)14U)
#define MMC_SYSTEST_SDWP_MASK                                                                                ((uint32_t)0x00004000U)
#define MMC_SYSTEST_SDWP_DRIVENHIGH                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_SDWP_DRIVENLOW                                                                           ((uint32_t)0U)

#define MMC_SYSTEST_D2D_SHIFT                                                                                ((uint32_t)6U)
#define MMC_SYSTEST_D2D_MASK                                                                                 ((uint32_t)0x00000040U)
#define MMC_SYSTEST_D2D_DRIVELOW_W                                                                           ((uint32_t)0U)
#define MMC_SYSTEST_D2D_ONE_R                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_D2D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D2D_DRIVEHIGH_W                                                                          ((uint32_t)1U)

#define MMC_SYSTEST_DDIR_SHIFT                                                                               ((uint32_t)3U)
#define MMC_SYSTEST_DDIR_MASK                                                                                ((uint32_t)0x00000008U)
#define MMC_SYSTEST_DDIR_IN_W                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_DDIR_ONE_R                                                                               ((uint32_t)1U)
#define MMC_SYSTEST_DDIR_ZERO_R                                                                              ((uint32_t)0U)
#define MMC_SYSTEST_DDIR_OUT_W                                                                               ((uint32_t)0U)

#define MMC_SYSTEST_CDAT_SHIFT                                                                               ((uint32_t)2U)
#define MMC_SYSTEST_CDAT_MASK                                                                                ((uint32_t)0x00000004U)
#define MMC_SYSTEST_CDAT_ONE_R                                                                               ((uint32_t)1U)
#define MMC_SYSTEST_CDAT_DRIVELOW_W                                                                          ((uint32_t)0U)
#define MMC_SYSTEST_CDAT_ZERO_R                                                                              ((uint32_t)0U)
#define MMC_SYSTEST_CDAT_DRIVEHIGH_W                                                                         ((uint32_t)1U)

#define MMC_SYSTEST_D5D_SHIFT                                                                                ((uint32_t)9U)
#define MMC_SYSTEST_D5D_MASK                                                                                 ((uint32_t)0x00000200U)
#define MMC_SYSTEST_D5D_DRIVELOW_W                                                                           ((uint32_t)0U)
#define MMC_SYSTEST_D5D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D5D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D5D_ONE_R                                                                                ((uint32_t)1U)

#define MMC_SYSTEST_D6D_SHIFT                                                                                ((uint32_t)10U)
#define MMC_SYSTEST_D6D_MASK                                                                                 ((uint32_t)0x00000400U)
#define MMC_SYSTEST_D6D_DRIVELOW_W                                                                           ((uint32_t)0U)
#define MMC_SYSTEST_D6D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D6D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D6D_ONE_R                                                                                ((uint32_t)1U)

#define MMC_SYSTEST_SSB_SHIFT                                                                                ((uint32_t)12U)
#define MMC_SYSTEST_SSB_MASK                                                                                 ((uint32_t)0x00001000U)
#define MMC_SYSTEST_SSB_SETTHEMALL_W                                                                         ((uint32_t)1U)
#define MMC_SYSTEST_SSB_CLEAR_W                                                                              ((uint32_t)0U)
#define MMC_SYSTEST_SSB_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_SSB_ONE_R                                                                                ((uint32_t)1U)

#define MMC_SYSTEST_D3D_SHIFT                                                                                ((uint32_t)7U)
#define MMC_SYSTEST_D3D_MASK                                                                                 ((uint32_t)0x00000080U)
#define MMC_SYSTEST_D3D_ONE_R                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_D3D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D3D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D3D_DRIVELOW_W                                                                           ((uint32_t)0U)

#define MMC_SYSTEST_MCKD_SHIFT                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_MCKD_MASK                                                                                ((uint32_t)0x00000001U)
#define MMC_SYSTEST_MCKD_DRIVENLOW_W                                                                         ((uint32_t)0U)
#define MMC_SYSTEST_MCKD_DRIVENHIGH_W                                                                        ((uint32_t)1U)
#define MMC_SYSTEST_MCKD_ONE_R                                                                               ((uint32_t)1U)
#define MMC_SYSTEST_MCKD_ZERO_R                                                                              ((uint32_t)0U)

#define MMC_SYSTEST_D0D_SHIFT                                                                                ((uint32_t)4U)
#define MMC_SYSTEST_D0D_MASK                                                                                 ((uint32_t)0x00000010U)
#define MMC_SYSTEST_D0D_ONE_R                                                                                ((uint32_t)1U)
#define MMC_SYSTEST_D0D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D0D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D0D_ZERO_W                                                                               ((uint32_t)0U)

#define MMC_SYSTEST_D7D_SHIFT                                                                                ((uint32_t)11U)
#define MMC_SYSTEST_D7D_MASK                                                                                 ((uint32_t)0x00000800U)
#define MMC_SYSTEST_D7D_ZERO_R                                                                               ((uint32_t)0U)
#define MMC_SYSTEST_D7D_DRIVEHIGH_W                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_D7D_DRIVELOW_W                                                                           ((uint32_t)0U)
#define MMC_SYSTEST_D7D_ONE_R                                                                                ((uint32_t)1U)

#define MMC_SYSTEST_SDCD_SHIFT                                                                               ((uint32_t)15U)
#define MMC_SYSTEST_SDCD_MASK                                                                                ((uint32_t)0x00008000U)
#define MMC_SYSTEST_SDCD_DRIVENHIGH                                                                          ((uint32_t)1U)
#define MMC_SYSTEST_SDCD_DRIVENLOW                                                                           ((uint32_t)0U)

#define MMC_SYSTEST_OBI_SHIFT                                                                                ((uint32_t)16U)
#define MMC_SYSTEST_OBI_MASK                                                                                 ((uint32_t)0x00010000U)
#define MMC_SYSTEST_OBI_HIGHLEVEL                                                                            ((uint32_t)1U)
#define MMC_SYSTEST_OBI_LOWLEVEL                                                                             ((uint32_t)0U)

#define MMC_SYSTEST_RESERVED_SHIFT                                                                           ((uint32_t)17U)
#define MMC_SYSTEST_RESERVED_MASK                                                                            ((uint32_t)0xfffe0000U)

#define MMC_CON_HR_SHIFT                                                                                     ((uint32_t)2U)
#define MMC_CON_HR_MASK                                                                                      ((uint32_t)0x00000004U)
#define MMC_CON_HR_HOSTRESP                                                                                  ((uint32_t)1U)
#define MMC_CON_HR_NOHOSTRESP                                                                                ((uint32_t)0U)

#define MMC_CON_WPP_SHIFT                                                                                    ((uint32_t)8U)
#define MMC_CON_WPP_MASK                                                                                     ((uint32_t)0x00000100U)
#define MMC_CON_WPP_ACTIVEHIGH                                                                               ((uint32_t)0U)
#define MMC_CON_WPP_ACTIVELOW                                                                                ((uint32_t)1U)

#define MMC_CON_STR_SHIFT                                                                                    ((uint32_t)3U)
#define MMC_CON_STR_MASK                                                                                     ((uint32_t)0x00000008U)
#define MMC_CON_STR_STREAM                                                                                   ((uint32_t)1U)
#define MMC_CON_STR_BLOCK                                                                                    ((uint32_t)0U)

#define MMC_CON_OD_SHIFT                                                                                     ((uint32_t)0U)
#define MMC_CON_OD_MASK                                                                                      ((uint32_t)0x00000001U)
#define MMC_CON_OD_OPENDRAIN                                                                                 ((uint32_t)1U)
#define MMC_CON_OD_NOOPENDRAIN                                                                               ((uint32_t)0U)

#define MMC_CON_DVAL_SHIFT                                                                                   ((uint32_t)9U)
#define MMC_CON_DVAL_MASK                                                                                    ((uint32_t)0x00000600U)
#define MMC_CON_DVAL_FILTERLEVEL1                                                                            ((uint32_t)1U)
#define MMC_CON_DVAL_FILTERLEVEL2                                                                            ((uint32_t)2U)
#define MMC_CON_DVAL_FILTERLEVEL0                                                                            ((uint32_t)0U)
#define MMC_CON_DVAL_FILTERLEVEL3                                                                            ((uint32_t)3U)

#define MMC_CON_INIT_SHIFT                                                                                   ((uint32_t)1U)
#define MMC_CON_INIT_MASK                                                                                    ((uint32_t)0x00000002U)
#define MMC_CON_INIT_NOINIT                                                                                  ((uint32_t)0U)
#define MMC_CON_INIT_INITSTREAM                                                                              ((uint32_t)1U)

#define MMC_CON_MIT_SHIFT                                                                                    ((uint32_t)6U)
#define MMC_CON_MIT_MASK                                                                                     ((uint32_t)0x00000040U)
#define MMC_CON_MIT_CTO                                                                                      ((uint32_t)0U)
#define MMC_CON_MIT_NO_CTO                                                                                   ((uint32_t)1U)

#define MMC_CON_CDP_SHIFT                                                                                    ((uint32_t)7U)
#define MMC_CON_CDP_MASK                                                                                     ((uint32_t)0x00000080U)
#define MMC_CON_CDP_ACTIVEHIGH                                                                               ((uint32_t)1U)
#define MMC_CON_CDP_ACTIVELOW                                                                                ((uint32_t)0U)

#define MMC_CON_DW8_SHIFT                                                                                    ((uint32_t)5U)
#define MMC_CON_DW8_MASK                                                                                     ((uint32_t)0x00000020U)
#define MMC_CON_DW8_8BITMODE                                                                                 ((uint32_t)1U)
#define MMC_CON_DW8_1_4BITMODE                                                                               ((uint32_t)0U)

#define MMC_CON_MODE_SHIFT                                                                                   ((uint32_t)4U)
#define MMC_CON_MODE_MASK                                                                                    ((uint32_t)0x00000010U)
#define MMC_CON_MODE_SYSTEST                                                                                 ((uint32_t)1U)
#define MMC_CON_MODE_FUNC                                                                                    ((uint32_t)0U)

#define MMC_CON_CTPL_SHIFT                                                                                   ((uint32_t)11U)
#define MMC_CON_CTPL_MASK                                                                                    ((uint32_t)0x00000800U)
#define MMC_CON_CTPL_MMC_SD                                                                                  ((uint32_t)0U)
#define MMC_CON_CTPL_SDIO                                                                                    ((uint32_t)1U)

#define MMC_CON_CEATA_SHIFT                                                                                  ((uint32_t)12U)
#define MMC_CON_CEATA_MASK                                                                                   ((uint32_t)0x00001000U)
#define MMC_CON_CEATA_NORMALMODE                                                                             ((uint32_t)0U)
#define MMC_CON_CEATA_CEATAMODE                                                                              ((uint32_t)1U)

#define MMC_CON_OBIP_SHIFT                                                                                   ((uint32_t)13U)
#define MMC_CON_OBIP_MASK                                                                                    ((uint32_t)0x00002000U)
#define MMC_CON_OBIP_ACTIVEHIGH                                                                              ((uint32_t)0U)
#define MMC_CON_OBIP_ACTIVELOW                                                                               ((uint32_t)1U)

#define MMC_CON_OBIE_SHIFT                                                                                   ((uint32_t)14U)
#define MMC_CON_OBIE_MASK                                                                                    ((uint32_t)0x00004000U)
#define MMC_CON_OBIE_OBINTMODE                                                                               ((uint32_t)1U)
#define MMC_CON_OBIE_NORMALMODE                                                                              ((uint32_t)0U)

#define MMC_CON_PADEN_SHIFT                                                                                  ((uint32_t)15U)
#define MMC_CON_PADEN_MASK                                                                                   ((uint32_t)0x00008000U)
#define MMC_CON_PADEN_DISABLE                                                                                ((uint32_t)0U)
#define MMC_CON_PADEN_ENABLE                                                                                 ((uint32_t)1U)

#define MMC_CON_CLKEXTFREE_SHIFT                                                                             ((uint32_t)16U)
#define MMC_CON_CLKEXTFREE_MASK                                                                              ((uint32_t)0x00010000U)
#define MMC_CON_CLKEXTFREE_AUTOGATING                                                                        ((uint32_t)0U)
#define MMC_CON_CLKEXTFREE_FREERUNNING                                                                       ((uint32_t)1U)

#define MMC_CON_BOOT_ACK_SHIFT                                                                               ((uint32_t)17U)
#define MMC_CON_BOOT_ACK_MASK                                                                                ((uint32_t)0x00020000U)
#define MMC_CON_BOOT_ACK_BOOTNOACK                                                                           ((uint32_t)0U)
#define MMC_CON_BOOT_ACK_BOOTACK                                                                             ((uint32_t)1U)

#define MMC_CON_BOOT_CF0_SHIFT                                                                               ((uint32_t)18U)
#define MMC_CON_BOOT_CF0_MASK                                                                                ((uint32_t)0x00040000U)
#define MMC_CON_BOOT_CF0_NOCMDFORCE                                                                          ((uint32_t)0U)
#define MMC_CON_BOOT_CF0_CMDFORCED                                                                           ((uint32_t)1U)
#define MMC_CON_BOOT_CF0_CMDFORCEREQ                                                                         ((uint32_t)1U)
#define MMC_CON_BOOT_CF0_CMDRELEASED                                                                         ((uint32_t)0U)

#define MMC_CON_DDR_SHIFT                                                                                    ((uint32_t)19U)
#define MMC_CON_DDR_MASK                                                                                     ((uint32_t)0x00080000U)
#define MMC_CON_DDR_NORMALMODE                                                                               ((uint32_t)0U)
#define MMC_CON_DDR_DDRMODE                                                                                  ((uint32_t)1U)

#define MMC_CON_DMA_MNS_SHIFT                                                                                ((uint32_t)20U)
#define MMC_CON_DMA_MNS_MASK                                                                                 ((uint32_t)0x00100000U)
#define MMC_CON_DMA_MNS_MASTERDMADIS                                                                         ((uint32_t)0U)
#define MMC_CON_DMA_MNS_MASTERDMAEN                                                                          ((uint32_t)1U)

#define MMC_CON_SDMA_LNE_SHIFT                                                                               ((uint32_t)21U)
#define MMC_CON_SDMA_LNE_MASK                                                                                ((uint32_t)0x00200000U)
#define MMC_CON_SDMA_LNE_LATEDEASSERT                                                                        ((uint32_t)1U)
#define MMC_CON_SDMA_LNE_EARLYDEASSERT                                                                       ((uint32_t)0U)

#define MMC_CON_RESERVED_SHIFT                                                                               ((uint32_t)22U)
#define MMC_CON_RESERVED_MASK                                                                                ((uint32_t)0xffc00000U)

#define MMC_PWCNT_PWRCNT_SHIFT                                                                               ((uint32_t)0U)
#define MMC_PWCNT_PWRCNT_MASK                                                                                ((uint32_t)0x0000ffffU)
#define MMC_PWCNT_PWRCNT_65535CYCLES                                                                         ((uint32_t)65535U)
#define MMC_PWCNT_PWRCNT_65534CYCLES                                                                         ((uint32_t)65534U)
#define MMC_PWCNT_PWRCNT_2CYCLES                                                                             ((uint32_t)2U)
#define MMC_PWCNT_PWRCNT_1CYCLES                                                                             ((uint32_t)1U)
#define MMC_PWCNT_PWRCNT_NODELAY                                                                             ((uint32_t)0U)

#define MMC_PWCNT_RESERVED_SHIFT                                                                             ((uint32_t)16U)
#define MMC_PWCNT_RESERVED_MASK                                                                              ((uint32_t)0xffff0000U)

#define MMC_DLL_DLL_LOCK_SHIFT                                                                               ((uint32_t)0U)
#define MMC_DLL_DLL_LOCK_MASK                                                                                ((uint32_t)0x00000001U)
#define MMC_DLL_DLL_LOCK_NOTLOCKED                                                                           ((uint32_t)0U)
#define MMC_DLL_DLL_LOCK_LOCKED                                                                              ((uint32_t)1U)

#define MMC_DLL_DLL_CALIB_SHIFT                                                                              ((uint32_t)1U)
#define MMC_DLL_DLL_CALIB_MASK                                                                               ((uint32_t)0x00000002U)
#define MMC_DLL_DLL_CALIB_ENABLED                                                                            ((uint32_t)1U)
#define MMC_DLL_DLL_CALIB_DISABLED                                                                           ((uint32_t)0U)

#define MMC_DLL_SLAVE_RATIO_SHIFT                                                                            ((uint32_t)6U)
#define MMC_DLL_SLAVE_RATIO_MASK                                                                             ((uint32_t)0x00000fc0U)
#define MMC_DLL_SLAVE_RATIO_PLUS0                                                                            ((uint32_t)0U)
#define MMC_DLL_SLAVE_RATIO_PLUS45                                                                           ((uint32_t)2U)
#define MMC_DLL_SLAVE_RATIO_PLUS90                                                                           ((uint32_t)4U)
#define MMC_DLL_SLAVE_RATIO_PLUS135                                                                          ((uint32_t)6U)
#define MMC_DLL_SLAVE_RATIO_PLUS180                                                                          ((uint32_t)8U)
#define MMC_DLL_SLAVE_RATIO_PLUS225                                                                          ((uint32_t)10U)
#define MMC_DLL_SLAVE_RATIO_PLUS270                                                                          ((uint32_t)12U)
#define MMC_DLL_SLAVE_RATIO_PLUS315                                                                          ((uint32_t)14U)
#define MMC_DLL_SLAVE_RATIO_PLUS380                                                                          ((uint32_t)16U)
#define MMC_DLL_SLAVE_RATIO_FOURCYCLES                                                                       ((uint32_t)63U)

#define MMC_DLL_MAX_LOCK_DIFF_SHIFT                                                                          ((uint32_t)22U)
#define MMC_DLL_MAX_LOCK_DIFF_MASK                                                                           ((uint32_t)0x3fc00000U)

#define MMC_DLL_LOCK_TIMER_SHIFT                                                                             ((uint32_t)30U)
#define MMC_DLL_LOCK_TIMER_MASK                                                                              ((uint32_t)0x40000000U)
#define MMC_DLL_LOCK_TIMER_DLL_FAST_MODE                                                                     ((uint32_t)0U)
#define MMC_DLL_LOCK_TIMER_OTHER                                                                             ((uint32_t)1U)

#define MMC_DLL_FORCE_VALUE_SHIFT                                                                            ((uint32_t)12U)
#define MMC_DLL_FORCE_VALUE_MASK                                                                             ((uint32_t)0x00001000U)
#define MMC_DLL_FORCE_VALUE_NO_FORCE                                                                         ((uint32_t)0U)
#define MMC_DLL_FORCE_VALUE_FORCE                                                                            ((uint32_t)1U)

#define MMC_DLL_FORCE_SR_C_SHIFT                                                                             ((uint32_t)13U)
#define MMC_DLL_FORCE_SR_C_MASK                                                                              ((uint32_t)0x000fe000U)

#define MMC_DLL_FORCE_SR_F_SHIFT                                                                             ((uint32_t)20U)
#define MMC_DLL_FORCE_SR_F_MASK                                                                              ((uint32_t)0x00300000U)

#define MMC_DLL_DLL_SOFT_RESET_SHIFT                                                                         ((uint32_t)31U)
#define MMC_DLL_DLL_SOFT_RESET_MASK                                                                          ((uint32_t)0x80000000U)
#define MMC_DLL_DLL_SOFT_RESET_WRITE_1                                                                       ((uint32_t)1U)
#define MMC_DLL_DLL_SOFT_RESET_WRITE_0                                                                       ((uint32_t)0U)
#define MMC_DLL_DLL_SOFT_RESET_READ_1                                                                        ((uint32_t)1U)
#define MMC_DLL_DLL_SOFT_RESET_READ_0                                                                        ((uint32_t)0U)

#define MMC_DLL_DLL_UNLOCK_STICKY_SHIFT                                                                      ((uint32_t)2U)
#define MMC_DLL_DLL_UNLOCK_STICKY_MASK                                                                       ((uint32_t)0x00000004U)

#define MMC_DLL_DLL_UNLOCK_CLEAR_SHIFT                                                                       ((uint32_t)3U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_MASK                                                                        ((uint32_t)0x00000008U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_1                                                                           ((uint32_t)1U)
#define MMC_DLL_DLL_UNLOCK_CLEAR_0                                                                           ((uint32_t)0U)

#define MMC_DLL_RESERVED_SHIFT                                                                               ((uint32_t)4U)
#define MMC_DLL_RESERVED_MASK                                                                                ((uint32_t)0x00000030U)

#define MMC_SDMASA_SDMA_ARG2_SHIFT                                                                           ((uint32_t)0U)
#define MMC_SDMASA_SDMA_ARG2_MASK                                                                            ((uint32_t)0xffffffffU)

#define MMC_BLK_NBLK_SHIFT                                                                                   ((uint32_t)16U)
#define MMC_BLK_NBLK_MASK                                                                                    ((uint32_t)0xffff0000U)
#define MMC_BLK_NBLK_1BLK                                                                                    ((uint32_t)1U)
#define MMC_BLK_NBLK_2BLKS                                                                                   ((uint32_t)2U)
#define MMC_BLK_NBLK_65535BLKS                                                                               ((uint32_t)65535U)
#define MMC_BLK_NBLK_STPCNT                                                                                  ((uint32_t)0U)

#define MMC_BLK_BLEN_SHIFT                                                                                   ((uint32_t)0U)
#define MMC_BLK_BLEN_MASK                                                                                    ((uint32_t)0x00000fffU)
#define MMC_BLK_BLEN_1BYTELEN                                                                                ((uint32_t)1U)
#define MMC_BLK_BLEN_2048BYTESLEN                                                                            ((uint32_t)2048U)
#define MMC_BLK_BLEN_3BYTESLEN                                                                               ((uint32_t)3U)
#define MMC_BLK_BLEN_2047BYTESLEN                                                                            ((uint32_t)2047U)
#define MMC_BLK_BLEN_2BYTESLEN                                                                               ((uint32_t)2U)
#define MMC_BLK_BLEN_511BYTESLEN                                                                             ((uint32_t)511U)
#define MMC_BLK_BLEN_512BYTESLEN                                                                             ((uint32_t)512U)
#define MMC_BLK_BLEN_NOTRANSFER                                                                              ((uint32_t)0U)

#define MMC_BLK_RESERVED_SHIFT                                                                               ((uint32_t)12U)
#define MMC_BLK_RESERVED_MASK                                                                                ((uint32_t)0x0000f000U)

#define MMC_ARG_ARG_SHIFT                                                                                    ((uint32_t)0U)
#define MMC_ARG_ARG_MASK                                                                                     ((uint32_t)0xffffffffU)

#define MMC_CMD_RSP_TYPE_SHIFT                                                                               ((uint32_t)16U)
#define MMC_CMD_RSP_TYPE_MASK                                                                                ((uint32_t)0x00030000U)
#define MMC_CMD_RSP_TYPE_LGHT48B                                                                             ((uint32_t)3U)
#define MMC_CMD_RSP_TYPE_NORSP                                                                               ((uint32_t)0U)
#define MMC_CMD_RSP_TYPE_LGHT36                                                                              ((uint32_t)1U)
#define MMC_CMD_RSP_TYPE_LGHT48                                                                              ((uint32_t)2U)

#define MMC_CMD_CCCE_SHIFT                                                                                   ((uint32_t)19U)
#define MMC_CMD_CCCE_MASK                                                                                    ((uint32_t)0x00080000U)
#define MMC_CMD_CCCE_NOCHECK                                                                                 ((uint32_t)0U)
#define MMC_CMD_CCCE_CHECK                                                                                   ((uint32_t)1U)

#define MMC_CMD_ACEN_SHIFT                                                                                   ((uint32_t)2U)
#define MMC_CMD_ACEN_MASK                                                                                    ((uint32_t)0x0000000cU)
#define MMC_CMD_ACEN_DISABLE                                                                                 ((uint32_t)0U)
#define MMC_CMD_ACEN_ENABLECMD12                                                                             ((uint32_t)1U)
#define MMC_CMD_ACEN_ENABLECMD23                                                                             ((uint32_t)2U)
#define MMC_CMD_ACEN_RESERVED                                                                                ((uint32_t)3U)

#define MMC_CMD_INDX_SHIFT                                                                                   ((uint32_t)24U)
#define MMC_CMD_INDX_MASK                                                                                    ((uint32_t)0x3f000000U)
#define MMC_CMD_INDX_CMD0                                                                                    ((uint32_t)0U)
#define MMC_CMD_INDX_CMD1                                                                                    ((uint32_t)1U)
#define MMC_CMD_INDX_CMD2                                                                                    ((uint32_t)2U)
#define MMC_CMD_INDX_CMD3                                                                                    ((uint32_t)3U)
#define MMC_CMD_INDX_CMD4                                                                                    ((uint32_t)4U)
#define MMC_CMD_INDX_CMD5                                                                                    ((uint32_t)5U)
#define MMC_CMD_INDX_CMD6                                                                                    ((uint32_t)6U)
#define MMC_CMD_INDX_CMD7                                                                                    ((uint32_t)7U)
#define MMC_CMD_INDX_CMD8                                                                                    ((uint32_t)8U)
#define MMC_CMD_INDX_CMD9                                                                                    ((uint32_t)9U)
#define MMC_CMD_INDX_CMD10                                                                                   ((uint32_t)10U)
#define MMC_CMD_INDX_CMD11                                                                                   ((uint32_t)11U)
#define MMC_CMD_INDX_CMD12                                                                                   ((uint32_t)12U)
#define MMC_CMD_INDX_CMD13                                                                                   ((uint32_t)13U)
#define MMC_CMD_INDX_CMD14                                                                                   ((uint32_t)14U)
#define MMC_CMD_INDX_CMD15                                                                                   ((uint32_t)15U)
#define MMC_CMD_INDX_CMD16                                                                                   ((uint32_t)16U)
#define MMC_CMD_INDX_CMD17                                                                                   ((uint32_t)17U)
#define MMC_CMD_INDX_CMD18                                                                                   ((uint32_t)18U)
#define MMC_CMD_INDX_CMD19                                                                                   ((uint32_t)19U)
#define MMC_CMD_INDX_CMD20                                                                                   ((uint32_t)20U)
#define MMC_CMD_INDX_CMD21                                                                                   ((uint32_t)21U)
#define MMC_CMD_INDX_CMD22                                                                                   ((uint32_t)22U)
#define MMC_CMD_INDX_CMD23                                                                                   ((uint32_t)23U)
#define MMC_CMD_INDX_CMD24                                                                                   ((uint32_t)24U)
#define MMC_CMD_INDX_CMD25                                                                                   ((uint32_t)25U)
#define MMC_CMD_INDX_CMD26                                                                                   ((uint32_t)26U)
#define MMC_CMD_INDX_CMD27                                                                                   ((uint32_t)27U)
#define MMC_CMD_INDX_CMD28                                                                                   ((uint32_t)28U)
#define MMC_CMD_INDX_CMD29                                                                                   ((uint32_t)29U)
#define MMC_CMD_INDX_CMD30                                                                                   ((uint32_t)30U)
#define MMC_CMD_INDX_CMD31                                                                                   ((uint32_t)31U)
#define MMC_CMD_INDX_CMD32                                                                                   ((uint32_t)32U)
#define MMC_CMD_INDX_CMD33                                                                                   ((uint32_t)33U)
#define MMC_CMD_INDX_CMD34                                                                                   ((uint32_t)34U)
#define MMC_CMD_INDX_CMD35                                                                                   ((uint32_t)35U)
#define MMC_CMD_INDX_CMD36                                                                                   ((uint32_t)36U)
#define MMC_CMD_INDX_CMD37                                                                                   ((uint32_t)37U)
#define MMC_CMD_INDX_CMD38                                                                                   ((uint32_t)38U)
#define MMC_CMD_INDX_CMD39                                                                                   ((uint32_t)39U)
#define MMC_CMD_INDX_CMD40                                                                                   ((uint32_t)40U)
#define MMC_CMD_INDX_CMD41                                                                                   ((uint32_t)41U)
#define MMC_CMD_INDX_CMD42                                                                                   ((uint32_t)42U)
#define MMC_CMD_INDX_CMD43                                                                                   ((uint32_t)43U)
#define MMC_CMD_INDX_CMD44                                                                                   ((uint32_t)44U)
#define MMC_CMD_INDX_CMD45                                                                                   ((uint32_t)45U)
#define MMC_CMD_INDX_CMD46                                                                                   ((uint32_t)46U)
#define MMC_CMD_INDX_CMD47                                                                                   ((uint32_t)47U)
#define MMC_CMD_INDX_CMD48                                                                                   ((uint32_t)48U)
#define MMC_CMD_INDX_CMD49                                                                                   ((uint32_t)49U)
#define MMC_CMD_INDX_CMD50                                                                                   ((uint32_t)50U)
#define MMC_CMD_INDX_CMD51                                                                                   ((uint32_t)51U)
#define MMC_CMD_INDX_CMD52                                                                                   ((uint32_t)52U)
#define MMC_CMD_INDX_CMD53                                                                                   ((uint32_t)53U)
#define MMC_CMD_INDX_CMD54                                                                                   ((uint32_t)54U)
#define MMC_CMD_INDX_CMD55                                                                                   ((uint32_t)55U)
#define MMC_CMD_INDX_CMD56                                                                                   ((uint32_t)56U)
#define MMC_CMD_INDX_CMD57                                                                                   ((uint32_t)57U)
#define MMC_CMD_INDX_CMD58                                                                                   ((uint32_t)58U)
#define MMC_CMD_INDX_CMD59                                                                                   ((uint32_t)59U)
#define MMC_CMD_INDX_CMD60                                                                                   ((uint32_t)60U)
#define MMC_CMD_INDX_CMD61                                                                                   ((uint32_t)61U)
#define MMC_CMD_INDX_CMD62                                                                                   ((uint32_t)62U)
#define MMC_CMD_INDX_CMD63                                                                                   ((uint32_t)63U)

#define MMC_CMD_DE_SHIFT                                                                                     ((uint32_t)0U)
#define MMC_CMD_DE_MASK                                                                                      ((uint32_t)0x00000001U)
#define MMC_CMD_DE_DISABLE                                                                                   ((uint32_t)0U)
#define MMC_CMD_DE_ENABLE                                                                                    ((uint32_t)1U)

#define MMC_CMD_BCE_SHIFT                                                                                    ((uint32_t)1U)
#define MMC_CMD_BCE_MASK                                                                                     ((uint32_t)0x00000002U)
#define MMC_CMD_BCE_DISABLE                                                                                  ((uint32_t)0U)
#define MMC_CMD_BCE_ENABLE                                                                                   ((uint32_t)1U)

#define MMC_CMD_CICE_SHIFT                                                                                   ((uint32_t)20U)
#define MMC_CMD_CICE_MASK                                                                                    ((uint32_t)0x00100000U)
#define MMC_CMD_CICE_CHECK                                                                                   ((uint32_t)1U)
#define MMC_CMD_CICE_NOCHECK                                                                                 ((uint32_t)0U)

#define MMC_CMD_MSBS_SHIFT                                                                                   ((uint32_t)5U)
#define MMC_CMD_MSBS_MASK                                                                                    ((uint32_t)0x00000020U)
#define MMC_CMD_MSBS_MULTIBLK                                                                                ((uint32_t)1U)
#define MMC_CMD_MSBS_SGLEBLK                                                                                 ((uint32_t)0U)

#define MMC_CMD_CMD_TYPE_SHIFT                                                                               ((uint32_t)22U)
#define MMC_CMD_CMD_TYPE_MASK                                                                                ((uint32_t)0x00c00000U)
#define MMC_CMD_CMD_TYPE_RESUME                                                                              ((uint32_t)2U)
#define MMC_CMD_CMD_TYPE_SUSPEND                                                                             ((uint32_t)1U)
#define MMC_CMD_CMD_TYPE_NORMAL                                                                              ((uint32_t)0U)
#define MMC_CMD_CMD_TYPE_ABORT                                                                               ((uint32_t)3U)

#define MMC_CMD_DP_SHIFT                                                                                     ((uint32_t)21U)
#define MMC_CMD_DP_MASK                                                                                      ((uint32_t)0x00200000U)
#define MMC_CMD_DP_NODATA                                                                                    ((uint32_t)0U)
#define MMC_CMD_DP_DATA                                                                                      ((uint32_t)1U)

#define MMC_CMD_DDIR_SHIFT                                                                                   ((uint32_t)4U)
#define MMC_CMD_DDIR_MASK                                                                                    ((uint32_t)0x00000010U)
#define MMC_CMD_DDIR_READ                                                                                    ((uint32_t)1U)
#define MMC_CMD_DDIR_WRITE                                                                                   ((uint32_t)0U)

#define MMC_CMD_RESERVED_SHIFT                                                                               ((uint32_t)6U)
#define MMC_CMD_RESERVED_MASK                                                                                ((uint32_t)0x0000ffc0U)

#define MMC_CMD_RESERVED1_SHIFT                                                                              ((uint32_t)18U)
#define MMC_CMD_RESERVED1_MASK                                                                               ((uint32_t)0x00040000U)

#define MMC_CMD_RESERVED2_SHIFT                                                                              ((uint32_t)30U)
#define MMC_CMD_RESERVED2_MASK                                                                               ((uint32_t)0xc0000000U)

#define MMC_RSP10_RSP1_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_RSP10_RSP1_MASK                                                                                  ((uint32_t)0xffff0000U)

#define MMC_RSP10_RSP0_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_RSP10_RSP0_MASK                                                                                  ((uint32_t)0x0000ffffU)

#define MMC_RSP32_RSP3_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_RSP32_RSP3_MASK                                                                                  ((uint32_t)0xffff0000U)

#define MMC_RSP32_RSP2_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_RSP32_RSP2_MASK                                                                                  ((uint32_t)0x0000ffffU)

#define MMC_RSP54_RSP5_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_RSP54_RSP5_MASK                                                                                  ((uint32_t)0xffff0000U)

#define MMC_RSP54_RSP4_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_RSP54_RSP4_MASK                                                                                  ((uint32_t)0x0000ffffU)

#define MMC_RSP76_RSP6_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_RSP76_RSP6_MASK                                                                                  ((uint32_t)0x0000ffffU)

#define MMC_RSP76_RSP7_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_RSP76_RSP7_MASK                                                                                  ((uint32_t)0xffff0000U)

#define MMC_DATA_DATA_SHIFT                                                                                  ((uint32_t)0U)
#define MMC_DATA_DATA_MASK                                                                                   ((uint32_t)0xffffffffU)

#define MMC_PSTATE_RTA_SHIFT                                                                                 ((uint32_t)9U)
#define MMC_PSTATE_RTA_MASK                                                                                  ((uint32_t)0x00000200U)
#define MMC_PSTATE_RTA_TRANSFER                                                                              ((uint32_t)1U)
#define MMC_PSTATE_RTA_NOTRANSFER                                                                            ((uint32_t)0U)

#define MMC_PSTATE_WTA_SHIFT                                                                                 ((uint32_t)8U)
#define MMC_PSTATE_WTA_MASK                                                                                  ((uint32_t)0x00000100U)
#define MMC_PSTATE_WTA_NOTRANSFER                                                                            ((uint32_t)0U)
#define MMC_PSTATE_WTA_TRANSFER                                                                              ((uint32_t)1U)

#define MMC_PSTATE_BRE_SHIFT                                                                                 ((uint32_t)11U)
#define MMC_PSTATE_BRE_MASK                                                                                  ((uint32_t)0x00000800U)
#define MMC_PSTATE_BRE_RDDISABLE                                                                             ((uint32_t)0U)
#define MMC_PSTATE_BRE_RDENABLE                                                                              ((uint32_t)1U)

#define MMC_PSTATE_CSS_SHIFT                                                                                 ((uint32_t)17U)
#define MMC_PSTATE_CSS_MASK                                                                                  ((uint32_t)0x00020000U)
#define MMC_PSTATE_CSS_STABLE                                                                                ((uint32_t)1U)
#define MMC_PSTATE_CSS_DEBOUNCING                                                                            ((uint32_t)0U)

#define MMC_PSTATE_DLEV_SHIFT                                                                                ((uint32_t)20U)
#define MMC_PSTATE_DLEV_MASK                                                                                 ((uint32_t)0x00f00000U)

#define MMC_PSTATE_CDPL_SHIFT                                                                                ((uint32_t)18U)
#define MMC_PSTATE_CDPL_MASK                                                                                 ((uint32_t)0x00040000U)
#define MMC_PSTATE_CDPL_ZERO                                                                                 ((uint32_t)0U)
#define MMC_PSTATE_CDPL_ONE                                                                                  ((uint32_t)1U)

#define MMC_PSTATE_CLEV_SHIFT                                                                                ((uint32_t)24U)
#define MMC_PSTATE_CLEV_MASK                                                                                 ((uint32_t)0x01000000U)
#define MMC_PSTATE_CLEV_ZERO                                                                                 ((uint32_t)0U)
#define MMC_PSTATE_CLEV_ONE                                                                                  ((uint32_t)1U)

#define MMC_PSTATE_CINS_SHIFT                                                                                ((uint32_t)16U)
#define MMC_PSTATE_CINS_MASK                                                                                 ((uint32_t)0x00010000U)
#define MMC_PSTATE_CINS_ZERO                                                                                 ((uint32_t)0U)
#define MMC_PSTATE_CINS_ONE                                                                                  ((uint32_t)1U)

#define MMC_PSTATE_DATI_SHIFT                                                                                ((uint32_t)1U)
#define MMC_PSTATE_DATI_MASK                                                                                 ((uint32_t)0x00000002U)
#define MMC_PSTATE_DATI_CMDDIS                                                                               ((uint32_t)1U)
#define MMC_PSTATE_DATI_CMDEN                                                                                ((uint32_t)0U)

#define MMC_PSTATE_WP_SHIFT                                                                                  ((uint32_t)19U)
#define MMC_PSTATE_WP_MASK                                                                                   ((uint32_t)0x00080000U)
#define MMC_PSTATE_WP_ONE                                                                                    ((uint32_t)1U)
#define MMC_PSTATE_WP_ZERO                                                                                   ((uint32_t)0U)

#define MMC_PSTATE_CMDI_SHIFT                                                                                ((uint32_t)0U)
#define MMC_PSTATE_CMDI_MASK                                                                                 ((uint32_t)0x00000001U)
#define MMC_PSTATE_CMDI_CMDDIS                                                                               ((uint32_t)1U)
#define MMC_PSTATE_CMDI_CMDEN                                                                                ((uint32_t)0U)

#define MMC_PSTATE_DLA_SHIFT                                                                                 ((uint32_t)2U)
#define MMC_PSTATE_DLA_MASK                                                                                  ((uint32_t)0x00000004U)
#define MMC_PSTATE_DLA_ZERO                                                                                  ((uint32_t)0U)
#define MMC_PSTATE_DLA_ONE                                                                                   ((uint32_t)1U)

#define MMC_PSTATE_BWE_SHIFT                                                                                 ((uint32_t)10U)
#define MMC_PSTATE_BWE_MASK                                                                                  ((uint32_t)0x00000400U)
#define MMC_PSTATE_BWE_WRENABLE                                                                              ((uint32_t)1U)
#define MMC_PSTATE_BWE_WRDISABLE                                                                             ((uint32_t)0U)

#define MMC_PSTATE_RTR_SHIFT                                                                                 ((uint32_t)3U)
#define MMC_PSTATE_RTR_MASK                                                                                  ((uint32_t)0x00000008U)
#define MMC_PSTATE_RTR_NOTUNING                                                                              ((uint32_t)0U)
#define MMC_PSTATE_RTR_TUNING                                                                                ((uint32_t)1U)

#define MMC_PSTATE_RESERVED_SHIFT                                                                            ((uint32_t)4U)
#define MMC_PSTATE_RESERVED_MASK                                                                             ((uint32_t)0x000000f0U)

#define MMC_PSTATE_RESERVED1_SHIFT                                                                           ((uint32_t)12U)
#define MMC_PSTATE_RESERVED1_MASK                                                                            ((uint32_t)0x0000f000U)

#define MMC_PSTATE_RESERVED2_SHIFT                                                                           ((uint32_t)25U)
#define MMC_PSTATE_RESERVED2_MASK                                                                            ((uint32_t)0xfe000000U)

#define MMC_HCTL_SDVS_SHIFT                                                                                  ((uint32_t)9U)
#define MMC_HCTL_SDVS_MASK                                                                                   ((uint32_t)0x00000e00U)
#define MMC_HCTL_SDVS_1V8                                                                                    ((uint32_t)5U)
#define MMC_HCTL_SDVS_3V0                                                                                    ((uint32_t)6U)
#define MMC_HCTL_SDVS_3V3                                                                                    ((uint32_t)7U)

#define MMC_HCTL_LED_SHIFT                                                                                   ((uint32_t)0U)
#define MMC_HCTL_LED_MASK                                                                                    ((uint32_t)0x00000001U)

#define MMC_HCTL_DTW_SHIFT                                                                                   ((uint32_t)1U)
#define MMC_HCTL_DTW_MASK                                                                                    ((uint32_t)0x00000002U)
#define MMC_HCTL_DTW_1_BITMODE                                                                               ((uint32_t)0U)
#define MMC_HCTL_DTW_4_BITMODE                                                                               ((uint32_t)1U)

#define MMC_HCTL_SBGR_SHIFT                                                                                  ((uint32_t)16U)
#define MMC_HCTL_SBGR_MASK                                                                                   ((uint32_t)0x00010000U)
#define MMC_HCTL_SBGR_TRANSFER                                                                               ((uint32_t)0U)
#define MMC_HCTL_SBGR_STPBLK                                                                                 ((uint32_t)1U)

#define MMC_HCTL_REM_SHIFT                                                                                   ((uint32_t)26U)
#define MMC_HCTL_REM_MASK                                                                                    ((uint32_t)0x04000000U)
#define MMC_HCTL_REM_ENABLE                                                                                  ((uint32_t)1U)
#define MMC_HCTL_REM_DISABLE                                                                                 ((uint32_t)0U)

#define MMC_HCTL_IBG_SHIFT                                                                                   ((uint32_t)19U)
#define MMC_HCTL_IBG_MASK                                                                                    ((uint32_t)0x00080000U)
#define MMC_HCTL_IBG_ITDIABLE                                                                                ((uint32_t)0U)
#define MMC_HCTL_IBG_ITENABLE                                                                                ((uint32_t)1U)

#define MMC_HCTL_SDBP_SHIFT                                                                                  ((uint32_t)8U)
#define MMC_HCTL_SDBP_MASK                                                                                   ((uint32_t)0x00000100U)
#define MMC_HCTL_SDBP_PWROFF                                                                                 ((uint32_t)0U)
#define MMC_HCTL_SDBP_PWRON                                                                                  ((uint32_t)1U)

#define MMC_HCTL_INS_SHIFT                                                                                   ((uint32_t)25U)
#define MMC_HCTL_INS_MASK                                                                                    ((uint32_t)0x02000000U)
#define MMC_HCTL_INS_ENABLE                                                                                  ((uint32_t)1U)
#define MMC_HCTL_INS_DISABLE                                                                                 ((uint32_t)0U)

#define MMC_HCTL_IWE_SHIFT                                                                                   ((uint32_t)24U)
#define MMC_HCTL_IWE_MASK                                                                                    ((uint32_t)0x01000000U)
#define MMC_HCTL_IWE_ENABLE                                                                                  ((uint32_t)1U)
#define MMC_HCTL_IWE_DISABLE                                                                                 ((uint32_t)0U)

#define MMC_HCTL_HSPE_SHIFT                                                                                  ((uint32_t)2U)
#define MMC_HCTL_HSPE_MASK                                                                                   ((uint32_t)0x00000004U)
#define MMC_HCTL_HSPE_NORMALSPEED                                                                            ((uint32_t)0U)
#define MMC_HCTL_HSPE_HIGHSPEED                                                                              ((uint32_t)1U)

#define MMC_HCTL_CR_SHIFT                                                                                    ((uint32_t)17U)
#define MMC_HCTL_CR_MASK                                                                                     ((uint32_t)0x00020000U)
#define MMC_HCTL_CR_NONE                                                                                     ((uint32_t)0U)
#define MMC_HCTL_CR_RESTART                                                                                  ((uint32_t)1U)

#define MMC_HCTL_RWC_SHIFT                                                                                   ((uint32_t)18U)
#define MMC_HCTL_RWC_MASK                                                                                    ((uint32_t)0x00040000U)
#define MMC_HCTL_RWC_RW                                                                                      ((uint32_t)1U)
#define MMC_HCTL_RWC_NORW                                                                                    ((uint32_t)0U)

#define MMC_HCTL_OBWE_SHIFT                                                                                  ((uint32_t)27U)
#define MMC_HCTL_OBWE_MASK                                                                                   ((uint32_t)0x08000000U)
#define MMC_HCTL_OBWE_DISABLE                                                                                ((uint32_t)0U)
#define MMC_HCTL_OBWE_ENABLE                                                                                 ((uint32_t)1U)

#define MMC_HCTL_DMAS_SHIFT                                                                                  ((uint32_t)3U)
#define MMC_HCTL_DMAS_MASK                                                                                   ((uint32_t)0x00000018U)
#define MMC_HCTL_DMAS_RESERVED                                                                               ((uint32_t)0U)
#define MMC_HCTL_DMAS_RESERVED1                                                                              ((uint32_t)1U)
#define MMC_HCTL_DMAS_ADMA2                                                                                  ((uint32_t)2U)
#define MMC_HCTL_DMAS_RESERVED2                                                                              ((uint32_t)3U)

#define MMC_HCTL_CDTL_SHIFT                                                                                  ((uint32_t)6U)
#define MMC_HCTL_CDTL_MASK                                                                                   ((uint32_t)0x00000040U)
#define MMC_HCTL_CDTL_NOCARD                                                                                 ((uint32_t)0U)
#define MMC_HCTL_CDTL_CARDINS                                                                                ((uint32_t)1U)

#define MMC_HCTL_CDSS_SHIFT                                                                                  ((uint32_t)7U)
#define MMC_HCTL_CDSS_MASK                                                                                   ((uint32_t)0x00000080U)
#define MMC_HCTL_CDSS_SDCDSEL                                                                                ((uint32_t)0U)
#define MMC_HCTL_CDSS_CDTLSEL                                                                                ((uint32_t)1U)

#define MMC_HCTL_RESERVED_SHIFT                                                                              ((uint32_t)5U)
#define MMC_HCTL_RESERVED_MASK                                                                               ((uint32_t)0x00000020U)

#define MMC_HCTL_RESERVED1_SHIFT                                                                             ((uint32_t)12U)
#define MMC_HCTL_RESERVED1_MASK                                                                              ((uint32_t)0x0000f000U)

#define MMC_HCTL_RESERVED2_SHIFT                                                                             ((uint32_t)20U)
#define MMC_HCTL_RESERVED2_MASK                                                                              ((uint32_t)0x00f00000U)

#define MMC_HCTL_RESERVED3_SHIFT                                                                             ((uint32_t)28U)
#define MMC_HCTL_RESERVED3_MASK                                                                              ((uint32_t)0xf0000000U)

#define MMC_SYSCTL_ICS_SHIFT                                                                                 ((uint32_t)1U)
#define MMC_SYSCTL_ICS_MASK                                                                                  ((uint32_t)0x00000002U)
#define MMC_SYSCTL_ICS_NOTREADY                                                                              ((uint32_t)0U)
#define MMC_SYSCTL_ICS_READY                                                                                 ((uint32_t)1U)

#define MMC_SYSCTL_SRA_SHIFT                                                                                 ((uint32_t)24U)
#define MMC_SYSCTL_SRA_MASK                                                                                  ((uint32_t)0x01000000U)
#define MMC_SYSCTL_SRA_WORK                                                                                  ((uint32_t)0U)
#define MMC_SYSCTL_SRA_RESET                                                                                 ((uint32_t)1U)

#define MMC_SYSCTL_ICE_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_SYSCTL_ICE_MASK                                                                                  ((uint32_t)0x00000001U)
#define MMC_SYSCTL_ICE_OSCILLATE                                                                             ((uint32_t)1U)
#define MMC_SYSCTL_ICE_STOP                                                                                  ((uint32_t)0U)

#define MMC_SYSCTL_CEN_SHIFT                                                                                 ((uint32_t)2U)
#define MMC_SYSCTL_CEN_MASK                                                                                  ((uint32_t)0x00000004U)
#define MMC_SYSCTL_CEN_ENABLE                                                                                ((uint32_t)1U)
#define MMC_SYSCTL_CEN_DISABLE                                                                               ((uint32_t)0U)

#define MMC_SYSCTL_CLKD_SHIFT                                                                                ((uint32_t)6U)
#define MMC_SYSCTL_CLKD_MASK                                                                                 ((uint32_t)0x0000ffc0U)
#define MMC_SYSCTL_CLKD_BYPASS1                                                                              ((uint32_t)1U)
#define MMC_SYSCTL_CLKD_DIV2                                                                                 ((uint32_t)2U)
#define MMC_SYSCTL_CLKD_DIV3                                                                                 ((uint32_t)3U)
#define MMC_SYSCTL_CLKD_BYPASS0                                                                              ((uint32_t)0U)
#define MMC_SYSCTL_CLKD_DIV1023                                                                              ((uint32_t)1023U)

#define MMC_SYSCTL_SRD_SHIFT                                                                                 ((uint32_t)26U)
#define MMC_SYSCTL_SRD_MASK                                                                                  ((uint32_t)0x04000000U)
#define MMC_SYSCTL_SRD_WORK                                                                                  ((uint32_t)0U)
#define MMC_SYSCTL_SRD_RESET                                                                                 ((uint32_t)1U)

#define MMC_SYSCTL_DTO_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_SYSCTL_DTO_MASK                                                                                  ((uint32_t)0x000f0000U)
#define MMC_SYSCTL_DTO_15THDTO                                                                               ((uint32_t)14U)
#define MMC_SYSCTL_DTO_RSVD                                                                                  ((uint32_t)15U)
#define MMC_SYSCTL_DTO_1STDTO                                                                                ((uint32_t)0U)
#define MMC_SYSCTL_DTO_2NDDTO                                                                                ((uint32_t)1U)

#define MMC_SYSCTL_SRC_SHIFT                                                                                 ((uint32_t)25U)
#define MMC_SYSCTL_SRC_MASK                                                                                  ((uint32_t)0x02000000U)
#define MMC_SYSCTL_SRC_WORK                                                                                  ((uint32_t)0U)
#define MMC_SYSCTL_SRC_RESET                                                                                 ((uint32_t)1U)

#define MMC_SYSCTL_CGS_SHIFT                                                                                 ((uint32_t)5U)
#define MMC_SYSCTL_CGS_MASK                                                                                  ((uint32_t)0x00000020U)

#define MMC_SYSCTL_RESERVED_SHIFT                                                                            ((uint32_t)3U)
#define MMC_SYSCTL_RESERVED_MASK                                                                             ((uint32_t)0x00000018U)

#define MMC_SYSCTL_RESERVED1_SHIFT                                                                           ((uint32_t)20U)
#define MMC_SYSCTL_RESERVED1_MASK                                                                            ((uint32_t)0x00f00000U)

#define MMC_SYSCTL_RESERVED2_SHIFT                                                                           ((uint32_t)27U)
#define MMC_SYSCTL_RESERVED2_MASK                                                                            ((uint32_t)0xf8000000U)

#define MMC_STAT_ERRI_SHIFT                                                                                  ((uint32_t)15U)
#define MMC_STAT_ERRI_MASK                                                                                   ((uint32_t)0x00008000U)
#define MMC_STAT_ERRI_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_ERRI_IRQ_TRU_R                                                                              ((uint32_t)1U)

#define MMC_STAT_BGE_SHIFT                                                                                   ((uint32_t)2U)
#define MMC_STAT_BGE_MASK                                                                                    ((uint32_t)0x00000004U)
#define MMC_STAT_BGE_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_BGE_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_BGE_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_BGE_ST_RST_W                                                                                ((uint32_t)1U)

#define MMC_STAT_CERR_SHIFT                                                                                  ((uint32_t)28U)
#define MMC_STAT_CERR_MASK                                                                                   ((uint32_t)0x10000000U)
#define MMC_STAT_CERR_ST_RST_W                                                                               ((uint32_t)1U)
#define MMC_STAT_CERR_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_CERR_IRQ_TRU_R                                                                              ((uint32_t)1U)
#define MMC_STAT_CERR_ST_UN_W                                                                                ((uint32_t)0U)

#define MMC_STAT_CIRQ_SHIFT                                                                                  ((uint32_t)8U)
#define MMC_STAT_CIRQ_MASK                                                                                   ((uint32_t)0x00000100U)
#define MMC_STAT_CIRQ_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_CIRQ_IRQ_TRU_R                                                                              ((uint32_t)1U)

#define MMC_STAT_CREM_SHIFT                                                                                  ((uint32_t)7U)
#define MMC_STAT_CREM_MASK                                                                                   ((uint32_t)0x00000080U)
#define MMC_STAT_CREM_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_CREM_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_STAT_CREM_ST_RST_W                                                                               ((uint32_t)1U)
#define MMC_STAT_CREM_IRQ_TRU_R                                                                              ((uint32_t)1U)

#define MMC_STAT_DEB_SHIFT                                                                                   ((uint32_t)22U)
#define MMC_STAT_DEB_MASK                                                                                    ((uint32_t)0x00400000U)
#define MMC_STAT_DEB_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_DEB_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_DEB_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_DEB_ST_RST_W                                                                                ((uint32_t)1U)

#define MMC_STAT_CC_SHIFT                                                                                    ((uint32_t)0U)
#define MMC_STAT_CC_MASK                                                                                     ((uint32_t)0x00000001U)
#define MMC_STAT_CC_IRQ_TRU_R                                                                                ((uint32_t)1U)
#define MMC_STAT_CC_ST_RST_W                                                                                 ((uint32_t)1U)
#define MMC_STAT_CC_IRQ_FAL_R                                                                                ((uint32_t)0U)
#define MMC_STAT_CC_ST_UN_W                                                                                  ((uint32_t)0U)

#define MMC_STAT_BWR_SHIFT                                                                                   ((uint32_t)4U)
#define MMC_STAT_BWR_MASK                                                                                    ((uint32_t)0x00000010U)
#define MMC_STAT_BWR_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_BWR_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_BWR_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_BWR_ST_UN_W                                                                                 ((uint32_t)0U)

#define MMC_STAT_ACE_SHIFT                                                                                   ((uint32_t)24U)
#define MMC_STAT_ACE_MASK                                                                                    ((uint32_t)0x01000000U)
#define MMC_STAT_ACE_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_ACE_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_ACE_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_ACE_IRQ_TRU_R                                                                               ((uint32_t)1U)

#define MMC_STAT_DMA_SHIFT                                                                                   ((uint32_t)3U)
#define MMC_STAT_DMA_MASK                                                                                    ((uint32_t)0x00000008U)
#define MMC_STAT_DMA_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_DMA_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_DMA_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_DMA_ST_RST_W                                                                                ((uint32_t)1U)

#define MMC_STAT_CTO_SHIFT                                                                                   ((uint32_t)16U)
#define MMC_STAT_CTO_MASK                                                                                    ((uint32_t)0x00010000U)
#define MMC_STAT_CTO_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_CTO_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_CTO_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_CTO_ST_UN_W                                                                                 ((uint32_t)0U)

#define MMC_STAT_DCRC_SHIFT                                                                                  ((uint32_t)21U)
#define MMC_STAT_DCRC_MASK                                                                                   ((uint32_t)0x00200000U)
#define MMC_STAT_DCRC_ST_RST_W                                                                               ((uint32_t)1U)
#define MMC_STAT_DCRC_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_DCRC_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_STAT_DCRC_IRQ_TRU_R                                                                              ((uint32_t)1U)

#define MMC_STAT_CCRC_SHIFT                                                                                  ((uint32_t)17U)
#define MMC_STAT_CCRC_MASK                                                                                   ((uint32_t)0x00020000U)
#define MMC_STAT_CCRC_IRQ_TRU_R                                                                              ((uint32_t)1U)
#define MMC_STAT_CCRC_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_CCRC_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_STAT_CCRC_ST_RST_W                                                                               ((uint32_t)1U)

#define MMC_STAT_TC_SHIFT                                                                                    ((uint32_t)1U)
#define MMC_STAT_TC_MASK                                                                                     ((uint32_t)0x00000002U)
#define MMC_STAT_TC_IRQ_TRU_R                                                                                ((uint32_t)1U)
#define MMC_STAT_TC_ST_RST_W                                                                                 ((uint32_t)1U)
#define MMC_STAT_TC_IRQ_FAL_R                                                                                ((uint32_t)0U)
#define MMC_STAT_TC_ST_UN_W                                                                                  ((uint32_t)0U)

#define MMC_STAT_BRR_SHIFT                                                                                   ((uint32_t)5U)
#define MMC_STAT_BRR_MASK                                                                                    ((uint32_t)0x00000020U)
#define MMC_STAT_BRR_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_BRR_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_BRR_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_BRR_IRQ_TRU_R                                                                               ((uint32_t)1U)

#define MMC_STAT_CIE_SHIFT                                                                                   ((uint32_t)19U)
#define MMC_STAT_CIE_MASK                                                                                    ((uint32_t)0x00080000U)
#define MMC_STAT_CIE_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_CIE_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_CIE_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_CIE_IRQ_FAL_R                                                                               ((uint32_t)0U)

#define MMC_STAT_DTO_SHIFT                                                                                   ((uint32_t)20U)
#define MMC_STAT_DTO_MASK                                                                                    ((uint32_t)0x00100000U)
#define MMC_STAT_DTO_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_DTO_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_DTO_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_DTO_ST_RST_W                                                                                ((uint32_t)1U)

#define MMC_STAT_CINS_SHIFT                                                                                  ((uint32_t)6U)
#define MMC_STAT_CINS_MASK                                                                                   ((uint32_t)0x00000040U)
#define MMC_STAT_CINS_IRQ_TRU_R                                                                              ((uint32_t)1U)
#define MMC_STAT_CINS_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_CINS_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_STAT_CINS_ST_RST_W                                                                               ((uint32_t)1U)

#define MMC_STAT_BADA_SHIFT                                                                                  ((uint32_t)29U)
#define MMC_STAT_BADA_MASK                                                                                   ((uint32_t)0x20000000U)
#define MMC_STAT_BADA_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_STAT_BADA_ST_RST_W                                                                               ((uint32_t)1U)
#define MMC_STAT_BADA_IRQ_FAL_R                                                                              ((uint32_t)0U)
#define MMC_STAT_BADA_IRQ_TRU_R                                                                              ((uint32_t)1U)

#define MMC_STAT_CEB_SHIFT                                                                                   ((uint32_t)18U)
#define MMC_STAT_CEB_MASK                                                                                    ((uint32_t)0x00040000U)
#define MMC_STAT_CEB_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_CEB_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_CEB_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_CEB_ST_UN_W                                                                                 ((uint32_t)0U)

#define MMC_STAT_OBI_SHIFT                                                                                   ((uint32_t)9U)
#define MMC_STAT_OBI_MASK                                                                                    ((uint32_t)0x00000200U)
#define MMC_STAT_OBI_ST_UN_W                                                                                 ((uint32_t)0U)
#define MMC_STAT_OBI_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_OBI_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_OBI_IRQ_TRU_R                                                                               ((uint32_t)1U)

#define MMC_STAT_BSR_SHIFT                                                                                   ((uint32_t)10U)
#define MMC_STAT_BSR_MASK                                                                                    ((uint32_t)0x00000400U)
#define MMC_STAT_BSR_IRQ_TRU_R                                                                               ((uint32_t)1U)
#define MMC_STAT_BSR_ST_RST_W                                                                                ((uint32_t)1U)
#define MMC_STAT_BSR_IRQ_FAL_R                                                                               ((uint32_t)0U)
#define MMC_STAT_BSR_ST_UN_W                                                                                 ((uint32_t)0U)

#define MMC_STAT_ADMAE_SHIFT                                                                                 ((uint32_t)25U)
#define MMC_STAT_ADMAE_MASK                                                                                  ((uint32_t)0x02000000U)
#define MMC_STAT_ADMAE_IRQ_TRU_R                                                                             ((uint32_t)1U)
#define MMC_STAT_ADMAE_ST_RST_W                                                                              ((uint32_t)1U)
#define MMC_STAT_ADMAE_IRQ_FAL_R                                                                             ((uint32_t)0U)
#define MMC_STAT_ADMAE_ST_UN_W                                                                               ((uint32_t)0U)

#define MMC_STAT_TE_SHIFT                                                                                    ((uint32_t)26U)
#define MMC_STAT_TE_MASK                                                                                     ((uint32_t)0x04000000U)
#define MMC_STAT_TE_ERROR                                                                                    ((uint32_t)1U)
#define MMC_STAT_TE_NOERROR                                                                                  ((uint32_t)0U)

#define MMC_STAT_RESERVED_SHIFT                                                                              ((uint32_t)11U)
#define MMC_STAT_RESERVED_MASK                                                                               ((uint32_t)0x00007800U)

#define MMC_STAT_RESERVED2_SHIFT                                                                             ((uint32_t)27U)
#define MMC_STAT_RESERVED2_MASK                                                                              ((uint32_t)0x08000000U)

#define MMC_STAT_RESERVED3_SHIFT                                                                             ((uint32_t)30U)
#define MMC_STAT_RESERVED3_MASK                                                                              ((uint32_t)0xc0000000U)

#define MMC_STAT_RESERVED4_SHIFT                                                                             ((uint32_t)23U)
#define MMC_STAT_RESERVED4_MASK                                                                              ((uint32_t)0x00800000U)

#define MMC_IE_DCRC_ENABLE_SHIFT                                                                             ((uint32_t)21U)
#define MMC_IE_DCRC_ENABLE_MASK                                                                              ((uint32_t)0x00200000U)
#define MMC_IE_DCRC_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_IE_DCRC_ENABLE_MASKED                                                                            ((uint32_t)0U)

#define MMC_IE_BWR_ENABLE_SHIFT                                                                              ((uint32_t)4U)
#define MMC_IE_BWR_ENABLE_MASK                                                                               ((uint32_t)0x00000010U)
#define MMC_IE_BWR_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_BWR_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_DMA_ENABLE_SHIFT                                                                              ((uint32_t)3U)
#define MMC_IE_DMA_ENABLE_MASK                                                                               ((uint32_t)0x00000008U)
#define MMC_IE_DMA_ENABLE_MASKED                                                                             ((uint32_t)0U)
#define MMC_IE_DMA_ENABLE_ENABLED                                                                            ((uint32_t)1U)

#define MMC_IE_TC_ENABLE_SHIFT                                                                               ((uint32_t)1U)
#define MMC_IE_TC_ENABLE_MASK                                                                                ((uint32_t)0x00000002U)
#define MMC_IE_TC_ENABLE_ENABLED                                                                             ((uint32_t)1U)
#define MMC_IE_TC_ENABLE_MASKED                                                                              ((uint32_t)0U)

#define MMC_IE_CEB_ENABLE_SHIFT                                                                              ((uint32_t)18U)
#define MMC_IE_CEB_ENABLE_MASK                                                                               ((uint32_t)0x00040000U)
#define MMC_IE_CEB_ENABLE_MASKED                                                                             ((uint32_t)0U)
#define MMC_IE_CEB_ENABLE_ENABLED                                                                            ((uint32_t)1U)

#define MMC_IE_BRR_ENABLE_SHIFT                                                                              ((uint32_t)5U)
#define MMC_IE_BRR_ENABLE_MASK                                                                               ((uint32_t)0x00000020U)
#define MMC_IE_BRR_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_BRR_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_CERR_ENABLE_SHIFT                                                                             ((uint32_t)28U)
#define MMC_IE_CERR_ENABLE_MASK                                                                              ((uint32_t)0x10000000U)
#define MMC_IE_CERR_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_IE_CERR_ENABLE_MASKED                                                                            ((uint32_t)0U)

#define MMC_IE_CIRQ_ENABLE_SHIFT                                                                             ((uint32_t)8U)
#define MMC_IE_CIRQ_ENABLE_MASK                                                                              ((uint32_t)0x00000100U)
#define MMC_IE_CIRQ_ENABLE_MASKED                                                                            ((uint32_t)0U)
#define MMC_IE_CIRQ_ENABLE_ENABLED                                                                           ((uint32_t)1U)

#define MMC_IE_CC_ENABLE_SHIFT                                                                               ((uint32_t)0U)
#define MMC_IE_CC_ENABLE_MASK                                                                                ((uint32_t)0x00000001U)
#define MMC_IE_CC_ENABLE_MASKED                                                                              ((uint32_t)0U)
#define MMC_IE_CC_ENABLE_ENABLED                                                                             ((uint32_t)1U)

#define MMC_IE_CIE_ENABLE_SHIFT                                                                              ((uint32_t)19U)
#define MMC_IE_CIE_ENABLE_MASK                                                                               ((uint32_t)0x00080000U)
#define MMC_IE_CIE_ENABLE_MASKED                                                                             ((uint32_t)0U)
#define MMC_IE_CIE_ENABLE_ENABLED                                                                            ((uint32_t)1U)

#define MMC_IE_BADA_ENABLE_SHIFT                                                                             ((uint32_t)29U)
#define MMC_IE_BADA_ENABLE_MASK                                                                              ((uint32_t)0x20000000U)
#define MMC_IE_BADA_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_IE_BADA_ENABLE_MASKED                                                                            ((uint32_t)0U)

#define MMC_IE_DTO_ENABLE_SHIFT                                                                              ((uint32_t)20U)
#define MMC_IE_DTO_ENABLE_MASK                                                                               ((uint32_t)0x00100000U)
#define MMC_IE_DTO_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_DTO_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_CINS_ENABLE_SHIFT                                                                             ((uint32_t)6U)
#define MMC_IE_CINS_ENABLE_MASK                                                                              ((uint32_t)0x00000040U)
#define MMC_IE_CINS_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_IE_CINS_ENABLE_MASKED                                                                            ((uint32_t)0U)

#define MMC_IE_DEB_ENABLE_SHIFT                                                                              ((uint32_t)22U)
#define MMC_IE_DEB_ENABLE_MASK                                                                               ((uint32_t)0x00400000U)
#define MMC_IE_DEB_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_DEB_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_ACE_ENABLE_SHIFT                                                                              ((uint32_t)24U)
#define MMC_IE_ACE_ENABLE_MASK                                                                               ((uint32_t)0x01000000U)
#define MMC_IE_ACE_ENABLE_MASKED                                                                             ((uint32_t)0U)
#define MMC_IE_ACE_ENABLE_ENABLED                                                                            ((uint32_t)1U)

#define MMC_IE_BGE_ENABLE_SHIFT                                                                              ((uint32_t)2U)
#define MMC_IE_BGE_ENABLE_MASK                                                                               ((uint32_t)0x00000004U)
#define MMC_IE_BGE_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_BGE_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_CCRC_ENABLE_SHIFT                                                                             ((uint32_t)17U)
#define MMC_IE_CCRC_ENABLE_MASK                                                                              ((uint32_t)0x00020000U)
#define MMC_IE_CCRC_ENABLE_MASKED                                                                            ((uint32_t)0U)
#define MMC_IE_CCRC_ENABLE_ENABLED                                                                           ((uint32_t)1U)

#define MMC_IE_NULL_SHIFT                                                                                    ((uint32_t)15U)
#define MMC_IE_NULL_MASK                                                                                     ((uint32_t)0x00008000U)

#define MMC_IE_CREM_ENABLE_SHIFT                                                                             ((uint32_t)7U)
#define MMC_IE_CREM_ENABLE_MASK                                                                              ((uint32_t)0x00000080U)
#define MMC_IE_CREM_ENABLE_MASKED                                                                            ((uint32_t)0U)
#define MMC_IE_CREM_ENABLE_ENABLED                                                                           ((uint32_t)1U)

#define MMC_IE_CTO_ENABLE_SHIFT                                                                              ((uint32_t)16U)
#define MMC_IE_CTO_ENABLE_MASK                                                                               ((uint32_t)0x00010000U)
#define MMC_IE_CTO_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_CTO_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_OBI_ENABLE_SHIFT                                                                              ((uint32_t)9U)
#define MMC_IE_OBI_ENABLE_MASK                                                                               ((uint32_t)0x00000200U)
#define MMC_IE_OBI_ENABLE_MASKED                                                                             ((uint32_t)0U)
#define MMC_IE_OBI_ENABLE_ENABLED                                                                            ((uint32_t)1U)

#define MMC_IE_ADMAE_ENABLE_SHIFT                                                                            ((uint32_t)25U)
#define MMC_IE_ADMAE_ENABLE_MASK                                                                             ((uint32_t)0x02000000U)
#define MMC_IE_ADMAE_ENABLE_ENABLED                                                                          ((uint32_t)1U)
#define MMC_IE_ADMAE_ENABLE_MASKED                                                                           ((uint32_t)0U)

#define MMC_IE_BSR_ENABLE_SHIFT                                                                              ((uint32_t)10U)
#define MMC_IE_BSR_ENABLE_MASK                                                                               ((uint32_t)0x00000400U)
#define MMC_IE_BSR_ENABLE_ENABLED                                                                            ((uint32_t)1U)
#define MMC_IE_BSR_ENABLE_MASKED                                                                             ((uint32_t)0U)

#define MMC_IE_RESERVED_SHIFT                                                                                ((uint32_t)11U)
#define MMC_IE_RESERVED_MASK                                                                                 ((uint32_t)0x00007800U)

#define MMC_IE_RESERVED2_SHIFT                                                                               ((uint32_t)27U)
#define MMC_IE_RESERVED2_MASK                                                                                ((uint32_t)0x08000000U)

#define MMC_IE_RESERVED3_SHIFT                                                                               ((uint32_t)30U)
#define MMC_IE_RESERVED3_MASK                                                                                ((uint32_t)0xc0000000U)

#define MMC_IE_TE_ENABLE_SHIFT                                                                               ((uint32_t)26U)
#define MMC_IE_TE_ENABLE_MASK                                                                                ((uint32_t)0x04000000U)
#define MMC_IE_TE_ENABLE_MASKED                                                                              ((uint32_t)0U)
#define MMC_IE_TE_ENABLE_ENABLED                                                                             ((uint32_t)1U)

#define MMC_IE_RESERVED4_SHIFT                                                                               ((uint32_t)23U)
#define MMC_IE_RESERVED4_MASK                                                                                ((uint32_t)0x00800000U)

#define MMC_ISE_BWR_SIGEN_SHIFT                                                                              ((uint32_t)4U)
#define MMC_ISE_BWR_SIGEN_MASK                                                                               ((uint32_t)0x00000010U)
#define MMC_ISE_BWR_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_BWR_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_DEB_SIGEN_SHIFT                                                                              ((uint32_t)22U)
#define MMC_ISE_DEB_SIGEN_MASK                                                                               ((uint32_t)0x00400000U)
#define MMC_ISE_DEB_SIGEN_ENABLED                                                                            ((uint32_t)1U)
#define MMC_ISE_DEB_SIGEN_MASKED                                                                             ((uint32_t)0U)

#define MMC_ISE_CREM_SIGEN_SHIFT                                                                             ((uint32_t)7U)
#define MMC_ISE_CREM_SIGEN_MASK                                                                              ((uint32_t)0x00000080U)
#define MMC_ISE_CREM_SIGEN_MASKED                                                                            ((uint32_t)0U)
#define MMC_ISE_CREM_SIGEN_ENABLED                                                                           ((uint32_t)1U)

#define MMC_ISE_NULL_SHIFT                                                                                   ((uint32_t)15U)
#define MMC_ISE_NULL_MASK                                                                                    ((uint32_t)0x00008000U)

#define MMC_ISE_CIRQ_SIGEN_SHIFT                                                                             ((uint32_t)8U)
#define MMC_ISE_CIRQ_SIGEN_MASK                                                                              ((uint32_t)0x00000100U)
#define MMC_ISE_CIRQ_SIGEN_ENABLED                                                                           ((uint32_t)1U)
#define MMC_ISE_CIRQ_SIGEN_MASKED                                                                            ((uint32_t)0U)

#define MMC_ISE_CCRC_SIGEN_SHIFT                                                                             ((uint32_t)17U)
#define MMC_ISE_CCRC_SIGEN_MASK                                                                              ((uint32_t)0x00020000U)
#define MMC_ISE_CCRC_SIGEN_MASKED                                                                            ((uint32_t)0U)
#define MMC_ISE_CCRC_SIGEN_ENABLED                                                                           ((uint32_t)1U)

#define MMC_ISE_ACE_SIGEN_SHIFT                                                                              ((uint32_t)24U)
#define MMC_ISE_ACE_SIGEN_MASK                                                                               ((uint32_t)0x01000000U)
#define MMC_ISE_ACE_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_ACE_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_BGE_SIGEN_SHIFT                                                                              ((uint32_t)2U)
#define MMC_ISE_BGE_SIGEN_MASK                                                                               ((uint32_t)0x00000004U)
#define MMC_ISE_BGE_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_BGE_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_CERR_SIGEN_SHIFT                                                                             ((uint32_t)28U)
#define MMC_ISE_CERR_SIGEN_MASK                                                                              ((uint32_t)0x10000000U)
#define MMC_ISE_CERR_SIGEN_MASKED                                                                            ((uint32_t)0U)
#define MMC_ISE_CERR_SIGEN_ENABLED                                                                           ((uint32_t)1U)

#define MMC_ISE_CINS_SIGEN_SHIFT                                                                             ((uint32_t)6U)
#define MMC_ISE_CINS_SIGEN_MASK                                                                              ((uint32_t)0x00000040U)
#define MMC_ISE_CINS_SIGEN_ENABLED                                                                           ((uint32_t)1U)
#define MMC_ISE_CINS_SIGEN_MASKED                                                                            ((uint32_t)0U)

#define MMC_ISE_RESERVED4_SHIFT                                                                              ((uint32_t)23U)
#define MMC_ISE_RESERVED4_MASK                                                                               ((uint32_t)0x00800000U)

#define MMC_ISE_CC_SIGEN_SHIFT                                                                               ((uint32_t)0U)
#define MMC_ISE_CC_SIGEN_MASK                                                                                ((uint32_t)0x00000001U)
#define MMC_ISE_CC_SIGEN_MASKED                                                                              ((uint32_t)0U)
#define MMC_ISE_CC_SIGEN_ENABLED                                                                             ((uint32_t)1U)

#define MMC_ISE_CTO_SIGEN_SHIFT                                                                              ((uint32_t)16U)
#define MMC_ISE_CTO_SIGEN_MASK                                                                               ((uint32_t)0x00010000U)
#define MMC_ISE_CTO_SIGEN_ENABLED                                                                            ((uint32_t)1U)
#define MMC_ISE_CTO_SIGEN_MASKED                                                                             ((uint32_t)0U)

#define MMC_ISE_TC_SIGEN_SHIFT                                                                               ((uint32_t)1U)
#define MMC_ISE_TC_SIGEN_MASK                                                                                ((uint32_t)0x00000002U)
#define MMC_ISE_TC_SIGEN_MASKED                                                                              ((uint32_t)0U)
#define MMC_ISE_TC_SIGEN_ENABLED                                                                             ((uint32_t)1U)

#define MMC_ISE_BADA_SIGEN_SHIFT                                                                             ((uint32_t)29U)
#define MMC_ISE_BADA_SIGEN_MASK                                                                              ((uint32_t)0x20000000U)
#define MMC_ISE_BADA_SIGEN_ENABLED                                                                           ((uint32_t)1U)
#define MMC_ISE_BADA_SIGEN_MASKED                                                                            ((uint32_t)0U)

#define MMC_ISE_DCRC_SIGEN_SHIFT                                                                             ((uint32_t)21U)
#define MMC_ISE_DCRC_SIGEN_MASK                                                                              ((uint32_t)0x00200000U)
#define MMC_ISE_DCRC_SIGEN_MASKED                                                                            ((uint32_t)0U)
#define MMC_ISE_DCRC_SIGEN_ENABLED                                                                           ((uint32_t)1U)

#define MMC_ISE_DTO_SIGEN_SHIFT                                                                              ((uint32_t)20U)
#define MMC_ISE_DTO_SIGEN_MASK                                                                               ((uint32_t)0x00100000U)
#define MMC_ISE_DTO_SIGEN_ENABLED                                                                            ((uint32_t)1U)
#define MMC_ISE_DTO_SIGEN_MASKED                                                                             ((uint32_t)0U)

#define MMC_ISE_CIE_SIGEN_SHIFT                                                                              ((uint32_t)19U)
#define MMC_ISE_CIE_SIGEN_MASK                                                                               ((uint32_t)0x00080000U)
#define MMC_ISE_CIE_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_CIE_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_CEB_SIGEN_SHIFT                                                                              ((uint32_t)18U)
#define MMC_ISE_CEB_SIGEN_MASK                                                                               ((uint32_t)0x00040000U)
#define MMC_ISE_CEB_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_CEB_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_DMA_SIGEN_SHIFT                                                                              ((uint32_t)3U)
#define MMC_ISE_DMA_SIGEN_MASK                                                                               ((uint32_t)0x00000008U)
#define MMC_ISE_DMA_SIGEN_ENABLED                                                                            ((uint32_t)1U)
#define MMC_ISE_DMA_SIGEN_MASKED                                                                             ((uint32_t)0U)

#define MMC_ISE_BRR_SIGEN_SHIFT                                                                              ((uint32_t)5U)
#define MMC_ISE_BRR_SIGEN_MASK                                                                               ((uint32_t)0x00000020U)
#define MMC_ISE_BRR_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_BRR_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_OBI_SIGEN_SHIFT                                                                              ((uint32_t)9U)
#define MMC_ISE_OBI_SIGEN_MASK                                                                               ((uint32_t)0x00000200U)
#define MMC_ISE_OBI_SIGEN_MASKED                                                                             ((uint32_t)0U)
#define MMC_ISE_OBI_SIGEN_ENABLED                                                                            ((uint32_t)1U)

#define MMC_ISE_ADMAE_SIGEN_SHIFT                                                                            ((uint32_t)25U)
#define MMC_ISE_ADMAE_SIGEN_MASK                                                                             ((uint32_t)0x02000000U)
#define MMC_ISE_ADMAE_SIGEN_ENABLED                                                                          ((uint32_t)1U)
#define MMC_ISE_ADMAE_SIGEN_MASKED                                                                           ((uint32_t)0U)

#define MMC_ISE_BSR_SIGEN_SHIFT                                                                              ((uint32_t)10U)
#define MMC_ISE_BSR_SIGEN_MASK                                                                               ((uint32_t)0x00000400U)
#define MMC_ISE_BSR_SIGEN_ENABLED                                                                            ((uint32_t)1U)
#define MMC_ISE_BSR_SIGEN_MASKED                                                                             ((uint32_t)0U)

#define MMC_ISE_TE_SIGEN_SHIFT                                                                               ((uint32_t)26U)
#define MMC_ISE_TE_SIGEN_MASK                                                                                ((uint32_t)0x04000000U)
#define MMC_ISE_TE_SIGEN_MASKED                                                                              ((uint32_t)0U)
#define MMC_ISE_TE_SIGEN_ENABLED                                                                             ((uint32_t)1U)

#define MMC_ISE_RESERVED_SHIFT                                                                               ((uint32_t)11U)
#define MMC_ISE_RESERVED_MASK                                                                                ((uint32_t)0x00007800U)

#define MMC_ISE_RESERVED2_SHIFT                                                                              ((uint32_t)27U)
#define MMC_ISE_RESERVED2_MASK                                                                               ((uint32_t)0x08000000U)

#define MMC_ISE_RESERVED3_SHIFT                                                                              ((uint32_t)30U)
#define MMC_ISE_RESERVED3_MASK                                                                               ((uint32_t)0xc0000000U)

#define MMC_AC12_CNI_SHIFT                                                                                   ((uint32_t)7U)
#define MMC_AC12_CNI_MASK                                                                                    ((uint32_t)0x00000080U)
#define MMC_AC12_CNI_CMDNI                                                                                   ((uint32_t)1U)
#define MMC_AC12_CNI_NOERR                                                                                   ((uint32_t)0U)

#define MMC_AC12_ACTO_SHIFT                                                                                  ((uint32_t)1U)
#define MMC_AC12_ACTO_MASK                                                                                   ((uint32_t)0x00000002U)
#define MMC_AC12_ACTO_TIMEOUT                                                                                ((uint32_t)1U)
#define MMC_AC12_ACTO_NOERR                                                                                  ((uint32_t)0U)

#define MMC_AC12_ACEB_SHIFT                                                                                  ((uint32_t)3U)
#define MMC_AC12_ACEB_MASK                                                                                   ((uint32_t)0x00000008U)
#define MMC_AC12_ACEB_ERR                                                                                    ((uint32_t)1U)
#define MMC_AC12_ACEB_NOERR                                                                                  ((uint32_t)0U)

#define MMC_AC12_ACIE_SHIFT                                                                                  ((uint32_t)4U)
#define MMC_AC12_ACIE_MASK                                                                                   ((uint32_t)0x00000010U)
#define MMC_AC12_ACIE_NOERR                                                                                  ((uint32_t)0U)
#define MMC_AC12_ACIE_ERR                                                                                    ((uint32_t)1U)

#define MMC_AC12_ACCE_SHIFT                                                                                  ((uint32_t)2U)
#define MMC_AC12_ACCE_MASK                                                                                   ((uint32_t)0x00000004U)
#define MMC_AC12_ACCE_NOERR                                                                                  ((uint32_t)0U)
#define MMC_AC12_ACCE_ERR                                                                                    ((uint32_t)1U)

#define MMC_AC12_ACNE_SHIFT                                                                                  ((uint32_t)0U)
#define MMC_AC12_ACNE_MASK                                                                                   ((uint32_t)0x00000001U)
#define MMC_AC12_ACNE_EXE                                                                                    ((uint32_t)0U)
#define MMC_AC12_ACNE_NOTEXE                                                                                 ((uint32_t)1U)

#define MMC_AC12_UHSMS_SHIFT                                                                                 ((uint32_t)16U)
#define MMC_AC12_UHSMS_MASK                                                                                  ((uint32_t)0x00070000U)
#define MMC_AC12_UHSMS_SDR12                                                                                 ((uint32_t)0U)
#define MMC_AC12_UHSMS_SDR25                                                                                 ((uint32_t)1U)
#define MMC_AC12_UHSMS_SDR50                                                                                 ((uint32_t)2U)
#define MMC_AC12_UHSMS_SDR104                                                                                ((uint32_t)3U)
#define MMC_AC12_UHSMS_DDR50                                                                                 ((uint32_t)4U)
#define MMC_AC12_UHSMS_RESERVED1                                                                             ((uint32_t)5U)
#define MMC_AC12_UHSMS_RESERVED2                                                                             ((uint32_t)6U)
#define MMC_AC12_UHSMS_RESERVED3                                                                             ((uint32_t)7U)

#define MMC_AC12_V1V8_SIGEN_SHIFT                                                                            ((uint32_t)19U)
#define MMC_AC12_V1V8_SIGEN_MASK                                                                             ((uint32_t)0x00080000U)
#define MMC_AC12_V1V8_SIGEN_1V8                                                                              ((uint32_t)1U)
#define MMC_AC12_V1V8_SIGEN_3V3                                                                              ((uint32_t)0U)

#define MMC_AC12_DS_SEL_SHIFT                                                                                ((uint32_t)20U)
#define MMC_AC12_DS_SEL_MASK                                                                                 ((uint32_t)0x00300000U)
#define MMC_AC12_DS_SEL_DTB                                                                                  ((uint32_t)0U)
#define MMC_AC12_DS_SEL_DTA                                                                                  ((uint32_t)1U)
#define MMC_AC12_DS_SEL_DTC                                                                                  ((uint32_t)2U)
#define MMC_AC12_DS_SEL_DTD                                                                                  ((uint32_t)3U)

#define MMC_AC12_ET_SHIFT                                                                                    ((uint32_t)22U)
#define MMC_AC12_ET_MASK                                                                                     ((uint32_t)0x00400000U)
#define MMC_AC12_ET_EXECUTE                                                                                  ((uint32_t)1U)
#define MMC_AC12_ET_COMPLETED                                                                                ((uint32_t)0U)

#define MMC_AC12_SCLK_SEL_SHIFT                                                                              ((uint32_t)23U)
#define MMC_AC12_SCLK_SEL_MASK                                                                               ((uint32_t)0x00800000U)
#define MMC_AC12_SCLK_SEL_TUNED                                                                              ((uint32_t)1U)
#define MMC_AC12_SCLK_SEL_FIXED                                                                              ((uint32_t)0U)

#define MMC_AC12_AI_ENABLE_SHIFT                                                                             ((uint32_t)30U)
#define MMC_AC12_AI_ENABLE_MASK                                                                              ((uint32_t)0x40000000U)
#define MMC_AC12_AI_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_AC12_AI_ENABLE_DISABLED                                                                          ((uint32_t)0U)

#define MMC_AC12_PV_ENABLE_SHIFT                                                                             ((uint32_t)31U)
#define MMC_AC12_PV_ENABLE_MASK                                                                              ((uint32_t)0x80000000U)
#define MMC_AC12_PV_ENABLE_ENABLED                                                                           ((uint32_t)1U)
#define MMC_AC12_PV_ENABLE_DISABLED                                                                          ((uint32_t)0U)

#define MMC_AC12_RESERVED_SHIFT                                                                              ((uint32_t)5U)
#define MMC_AC12_RESERVED_MASK                                                                               ((uint32_t)0x00000060U)

#define MMC_AC12_RESERVED1_SHIFT                                                                             ((uint32_t)8U)
#define MMC_AC12_RESERVED1_MASK                                                                              ((uint32_t)0x0000ff00U)

#define MMC_AC12_RESERVED2_SHIFT                                                                             ((uint32_t)24U)
#define MMC_AC12_RESERVED2_MASK                                                                              ((uint32_t)0x3f000000U)

#define MMC_CAPA_HSS_SHIFT                                                                                   ((uint32_t)21U)
#define MMC_CAPA_HSS_MASK                                                                                    ((uint32_t)0x00200000U)
#define MMC_CAPA_HSS_NOTSUPPORTED                                                                            ((uint32_t)0U)
#define MMC_CAPA_HSS_SUPPORTED                                                                               ((uint32_t)1U)

#define MMC_CAPA_SRS_SHIFT                                                                                   ((uint32_t)23U)
#define MMC_CAPA_SRS_MASK                                                                                    ((uint32_t)0x00800000U)
#define MMC_CAPA_SRS_NOTSUPPORTED                                                                            ((uint32_t)0U)
#define MMC_CAPA_SRS_SUPPORTED                                                                               ((uint32_t)1U)

#define MMC_CAPA_DS_SHIFT                                                                                    ((uint32_t)22U)
#define MMC_CAPA_DS_MASK                                                                                     ((uint32_t)0x00400000U)
#define MMC_CAPA_DS_NOTSUPPORTED                                                                             ((uint32_t)0U)
#define MMC_CAPA_DS_SUPPORTED                                                                                ((uint32_t)1U)

#define MMC_CAPA_BCF_SHIFT                                                                                   ((uint32_t)8U)
#define MMC_CAPA_BCF_MASK                                                                                    ((uint32_t)0x0000ff00U)
#define MMC_CAPA_BCF_OMETH                                                                                   ((uint32_t)0U)

#define MMC_CAPA_MBL_SHIFT                                                                                   ((uint32_t)16U)
#define MMC_CAPA_MBL_MASK                                                                                    ((uint32_t)0x00030000U)
#define MMC_CAPA_MBL_512                                                                                     ((uint32_t)0U)
#define MMC_CAPA_MBL_1024                                                                                    ((uint32_t)1U)
#define MMC_CAPA_MBL_2048                                                                                    ((uint32_t)2U)

#define MMC_CAPA_VS18_SHIFT                                                                                  ((uint32_t)26U)
#define MMC_CAPA_VS18_MASK                                                                                   ((uint32_t)0x04000000U)
#define MMC_CAPA_VS18_ST_1V8SUP_W                                                                            ((uint32_t)1U)
#define MMC_CAPA_VS18_1V8_SUP_R                                                                              ((uint32_t)1U)
#define MMC_CAPA_VS18_1V8_NOTSUP_R                                                                           ((uint32_t)0U)
#define MMC_CAPA_VS18_ST_1V8NOTSUP_W                                                                         ((uint32_t)0U)

#define MMC_CAPA_TCU_SHIFT                                                                                   ((uint32_t)7U)
#define MMC_CAPA_TCU_MASK                                                                                    ((uint32_t)0x00000080U)
#define MMC_CAPA_TCU_MHZ                                                                                     ((uint32_t)0U)
#define MMC_CAPA_TCU_KHZ                                                                                     ((uint32_t)1U)

#define MMC_CAPA_VS33_SHIFT                                                                                  ((uint32_t)24U)
#define MMC_CAPA_VS33_MASK                                                                                   ((uint32_t)0x01000000U)
#define MMC_CAPA_VS33_ST_3V3SUP_W                                                                            ((uint32_t)1U)
#define MMC_CAPA_VS33_ST_3V3NOTSUP_W                                                                         ((uint32_t)0U)
#define MMC_CAPA_VS33_3V3_SUP_R                                                                              ((uint32_t)1U)
#define MMC_CAPA_VS33_3V3_NOTSUP_R                                                                           ((uint32_t)0U)

#define MMC_CAPA_VS30_SHIFT                                                                                  ((uint32_t)25U)
#define MMC_CAPA_VS30_MASK                                                                                   ((uint32_t)0x02000000U)
#define MMC_CAPA_VS30_ST_3V0NOTSUP_W                                                                         ((uint32_t)0U)
#define MMC_CAPA_VS30_3V0_NOTSUP_R                                                                           ((uint32_t)0U)
#define MMC_CAPA_VS30_3V0_SUP_R                                                                              ((uint32_t)1U)
#define MMC_CAPA_VS30_ST_3V0SUP_W                                                                            ((uint32_t)1U)

#define MMC_CAPA_TCF_SHIFT                                                                                   ((uint32_t)0U)
#define MMC_CAPA_TCF_MASK                                                                                    ((uint32_t)0x0000003fU)
#define MMC_CAPA_TCF_OMETH                                                                                   ((uint32_t)0U)

#define MMC_CAPA_BIT64_SHIFT                                                                                 ((uint32_t)28U)
#define MMC_CAPA_BIT64_MASK                                                                                  ((uint32_t)0x10000000U)
#define MMC_CAPA_BIT64_SYSADDR32B                                                                            ((uint32_t)0U)
#define MMC_CAPA_BIT64_SYSADDR64B                                                                            ((uint32_t)1U)

#define MMC_CAPA_AD2S_SHIFT                                                                                  ((uint32_t)19U)
#define MMC_CAPA_AD2S_MASK                                                                                   ((uint32_t)0x00080000U)
#define MMC_CAPA_AD2S_ADMA2NOTSUPPORTED                                                                      ((uint32_t)0U)
#define MMC_CAPA_AD2S_ADMA2SUPPORTED                                                                         ((uint32_t)1U)

#define MMC_CAPA_RESERVED_SHIFT                                                                              ((uint32_t)6U)
#define MMC_CAPA_RESERVED_MASK                                                                               ((uint32_t)0x00000040U)

#define MMC_CAPA_RESERVED1_SHIFT                                                                             ((uint32_t)18U)
#define MMC_CAPA_RESERVED1_MASK                                                                              ((uint32_t)0x00040000U)

#define MMC_CAPA_RESERVED2_SHIFT                                                                             ((uint32_t)20U)
#define MMC_CAPA_RESERVED2_MASK                                                                              ((uint32_t)0x00100000U)

#define MMC_CAPA_RESERVED3_SHIFT                                                                             ((uint32_t)27U)
#define MMC_CAPA_RESERVED3_MASK                                                                              ((uint32_t)0x08000000U)

#define MMC_CAPA_RESERVED4_SHIFT                                                                             ((uint32_t)30U)
#define MMC_CAPA_RESERVED4_MASK                                                                              ((uint32_t)0xc0000000U)

#define MMC_CAPA_AIS_SHIFT                                                                                   ((uint32_t)29U)
#define MMC_CAPA_AIS_MASK                                                                                    ((uint32_t)0x20000000U)
#define MMC_CAPA_AIS_AIS_SUP                                                                                 ((uint32_t)1U)
#define MMC_CAPA_AIS_AIS_NOTSUP                                                                              ((uint32_t)0U)

#define MMC_CAPA2_SDR50_SHIFT                                                                                ((uint32_t)0U)
#define MMC_CAPA2_SDR50_MASK                                                                                 ((uint32_t)0x00000001U)
#define MMC_CAPA2_SDR50_SUPPORTED                                                                            ((uint32_t)1U)
#define MMC_CAPA2_SDR50_NOTSUPPORTED                                                                         ((uint32_t)0U)

#define MMC_CAPA2_SDR104_SHIFT                                                                               ((uint32_t)1U)
#define MMC_CAPA2_SDR104_MASK                                                                                ((uint32_t)0x00000002U)
#define MMC_CAPA2_SDR104_SUPPORTED                                                                           ((uint32_t)1U)
#define MMC_CAPA2_SDR104_NOTSUPPORTED                                                                        ((uint32_t)0U)

#define MMC_CAPA2_DDR50_SHIFT                                                                                ((uint32_t)2U)
#define MMC_CAPA2_DDR50_MASK                                                                                 ((uint32_t)0x00000004U)
#define MMC_CAPA2_DDR50_SUPPORTED                                                                            ((uint32_t)1U)
#define MMC_CAPA2_DDR50_NOTSUPPORTED                                                                         ((uint32_t)0U)

#define MMC_CAPA2_DTA_SHIFT                                                                                  ((uint32_t)4U)
#define MMC_CAPA2_DTA_MASK                                                                                   ((uint32_t)0x00000010U)
#define MMC_CAPA2_DTA_SUPPORTED                                                                              ((uint32_t)1U)
#define MMC_CAPA2_DTA_NOTSUPPORTED                                                                           ((uint32_t)0U)

#define MMC_CAPA2_DTC_SHIFT                                                                                  ((uint32_t)5U)
#define MMC_CAPA2_DTC_MASK                                                                                   ((uint32_t)0x00000020U)
#define MMC_CAPA2_DTC_SUPPORTED                                                                              ((uint32_t)1U)
#define MMC_CAPA2_DTC_NOTSUPPORTED                                                                           ((uint32_t)0U)

#define MMC_CAPA2_DTD_SHIFT                                                                                  ((uint32_t)6U)
#define MMC_CAPA2_DTD_MASK                                                                                   ((uint32_t)0x00000040U)
#define MMC_CAPA2_DTD_SUPPORTED                                                                              ((uint32_t)1U)
#define MMC_CAPA2_DTD_NOTSUPPORTED                                                                           ((uint32_t)0U)

#define MMC_CAPA2_TCRT_SHIFT                                                                                 ((uint32_t)8U)
#define MMC_CAPA2_TCRT_MASK                                                                                  ((uint32_t)0x00000f00U)
#define MMC_CAPA2_TCRT_DISABLED                                                                              ((uint32_t)0U)
#define MMC_CAPA2_TCRT_1                                                                                     ((uint32_t)1U)
#define MMC_CAPA2_TCRT_2                                                                                     ((uint32_t)2U)
#define MMC_CAPA2_TCRT_3                                                                                     ((uint32_t)3U)
#define MMC_CAPA2_TCRT_4                                                                                     ((uint32_t)4U)
#define MMC_CAPA2_TCRT_5                                                                                     ((uint32_t)5U)
#define MMC_CAPA2_TCRT_6                                                                                     ((uint32_t)6U)
#define MMC_CAPA2_TCRT_7                                                                                     ((uint32_t)7U)
#define MMC_CAPA2_TCRT_8                                                                                     ((uint32_t)8U)
#define MMC_CAPA2_TCRT_9                                                                                     ((uint32_t)9U)
#define MMC_CAPA2_TCRT_10                                                                                    ((uint32_t)10U)
#define MMC_CAPA2_TCRT_11                                                                                    ((uint32_t)11U)
#define MMC_CAPA2_TCRT_RESERVED1                                                                             ((uint32_t)12U)
#define MMC_CAPA2_TCRT_RESERVED2                                                                             ((uint32_t)13U)
#define MMC_CAPA2_TCRT_RESERVED3                                                                             ((uint32_t)14U)
#define MMC_CAPA2_TCRT_OTHERSOURCE                                                                           ((uint32_t)15U)

#define MMC_CAPA2_TSDR50_SHIFT                                                                               ((uint32_t)13U)
#define MMC_CAPA2_TSDR50_MASK                                                                                ((uint32_t)0x00002000U)
#define MMC_CAPA2_TSDR50_REQUIRED                                                                            ((uint32_t)1U)
#define MMC_CAPA2_TSDR50_NOTREQUIRED                                                                         ((uint32_t)0U)

#define MMC_CAPA2_RTM_SHIFT                                                                                  ((uint32_t)14U)
#define MMC_CAPA2_RTM_MASK                                                                                   ((uint32_t)0x0000c000U)
#define MMC_CAPA2_RTM_MODE1                                                                                  ((uint32_t)0U)
#define MMC_CAPA2_RTM_MODE2                                                                                  ((uint32_t)1U)
#define MMC_CAPA2_RTM_MODE3                                                                                  ((uint32_t)2U)
#define MMC_CAPA2_RTM_RESERVED                                                                               ((uint32_t)3U)

#define MMC_CAPA2_CM_SHIFT                                                                                   ((uint32_t)16U)
#define MMC_CAPA2_CM_MASK                                                                                    ((uint32_t)0x00ff0000U)

#define MMC_CAPA2_RESERVED_SHIFT                                                                             ((uint32_t)3U)
#define MMC_CAPA2_RESERVED_MASK                                                                              ((uint32_t)0x00000008U)

#define MMC_CAPA2_RESERVED1_SHIFT                                                                            ((uint32_t)7U)
#define MMC_CAPA2_RESERVED1_MASK                                                                             ((uint32_t)0x00000080U)

#define MMC_CAPA2_RESERVED2_SHIFT                                                                            ((uint32_t)12U)
#define MMC_CAPA2_RESERVED2_MASK                                                                             ((uint32_t)0x00001000U)

#define MMC_CAPA2_RESERVED3_SHIFT                                                                            ((uint32_t)24U)
#define MMC_CAPA2_RESERVED3_MASK                                                                             ((uint32_t)0xff000000U)

#define MMC_CUR_CAPA_CUR_3V3_SHIFT                                                                           ((uint32_t)0U)
#define MMC_CUR_CAPA_CUR_3V3_MASK                                                                            ((uint32_t)0x000000ffU)
#define MMC_CUR_CAPA_CUR_3V3_OMETH                                                                           ((uint32_t)0U)

#define MMC_CUR_CAPA_CUR_1V8_SHIFT                                                                           ((uint32_t)16U)
#define MMC_CUR_CAPA_CUR_1V8_MASK                                                                            ((uint32_t)0x00ff0000U)
#define MMC_CUR_CAPA_CUR_1V8_OMETH                                                                           ((uint32_t)0U)

#define MMC_CUR_CAPA_CUR_3V0_SHIFT                                                                           ((uint32_t)8U)
#define MMC_CUR_CAPA_CUR_3V0_MASK                                                                            ((uint32_t)0x0000ff00U)
#define MMC_CUR_CAPA_CUR_3V0_OMETH                                                                           ((uint32_t)0U)

#define MMC_CUR_CAPA_RESERVED_SHIFT                                                                          ((uint32_t)24U)
#define MMC_CUR_CAPA_RESERVED_MASK                                                                           ((uint32_t)0xff000000U)

#define MMC_FE_FE_CEB_SHIFT                                                                                  ((uint32_t)18U)
#define MMC_FE_FE_CEB_MASK                                                                                   ((uint32_t)0x00040000U)
#define MMC_FE_FE_CEB_NOACTION                                                                               ((uint32_t)0U)
#define MMC_FE_FE_CEB_INTFORCED                                                                              ((uint32_t)1U)

#define MMC_FE_FE_CTO_SHIFT                                                                                  ((uint32_t)16U)
#define MMC_FE_FE_CTO_MASK                                                                                   ((uint32_t)0x00010000U)
#define MMC_FE_FE_CTO_ST_UN_W                                                                                ((uint32_t)0U)
#define MMC_FE_FE_CTO_ST_RST_W                                                                               ((uint32_t)1U)

#define MMC_FE_FE_DCRC_SHIFT                                                                                 ((uint32_t)21U)
#define MMC_FE_FE_DCRC_MASK                                                                                  ((uint32_t)0x00200000U)
#define MMC_FE_FE_DCRC_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_DCRC_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_FE_BADA_SHIFT                                                                                 ((uint32_t)29U)
#define MMC_FE_FE_BADA_MASK                                                                                  ((uint32_t)0x20000000U)
#define MMC_FE_FE_BADA_NOACTION                                                                              ((uint32_t)0U)
#define MMC_FE_FE_BADA_INTFORCED                                                                             ((uint32_t)1U)

#define MMC_FE_FE_CCRC_SHIFT                                                                                 ((uint32_t)17U)
#define MMC_FE_FE_CCRC_MASK                                                                                  ((uint32_t)0x00020000U)
#define MMC_FE_FE_CCRC_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_CCRC_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_FE_ACE_SHIFT                                                                                  ((uint32_t)24U)
#define MMC_FE_FE_ACE_MASK                                                                                   ((uint32_t)0x01000000U)
#define MMC_FE_FE_ACE_INTFORCED                                                                              ((uint32_t)1U)
#define MMC_FE_FE_ACE_NOACTION                                                                               ((uint32_t)0U)

#define MMC_FE_FE_DEB_SHIFT                                                                                  ((uint32_t)22U)
#define MMC_FE_FE_DEB_MASK                                                                                   ((uint32_t)0x00400000U)
#define MMC_FE_FE_DEB_NOACTION                                                                               ((uint32_t)0U)
#define MMC_FE_FE_DEB_INTFORCED                                                                              ((uint32_t)1U)

#define MMC_FE_FE_CIE_SHIFT                                                                                  ((uint32_t)19U)
#define MMC_FE_FE_CIE_MASK                                                                                   ((uint32_t)0x00080000U)
#define MMC_FE_FE_CIE_INTFORCED                                                                              ((uint32_t)1U)
#define MMC_FE_FE_CIE_NOACTION                                                                               ((uint32_t)0U)

#define MMC_FE_FE_DTO_SHIFT                                                                                  ((uint32_t)20U)
#define MMC_FE_FE_DTO_MASK                                                                                   ((uint32_t)0x00100000U)
#define MMC_FE_FE_DTO_NOACTION                                                                               ((uint32_t)0U)
#define MMC_FE_FE_DTO_INTFORCED                                                                              ((uint32_t)1U)

#define MMC_FE_FE_CERR_SHIFT                                                                                 ((uint32_t)28U)
#define MMC_FE_FE_CERR_MASK                                                                                  ((uint32_t)0x10000000U)
#define MMC_FE_FE_CERR_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_CERR_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_RESERVED4_SHIFT                                                                               ((uint32_t)23U)
#define MMC_FE_RESERVED4_MASK                                                                                ((uint32_t)0x00800000U)

#define MMC_FE_FE_ADMAE_SHIFT                                                                                ((uint32_t)25U)
#define MMC_FE_FE_ADMAE_MASK                                                                                 ((uint32_t)0x02000000U)
#define MMC_FE_FE_ADMAE_NOACTION                                                                             ((uint32_t)0U)
#define MMC_FE_FE_ADMAE_INTFORCED                                                                            ((uint32_t)1U)

#define MMC_FE_FE_ACNE_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_FE_FE_ACNE_MASK                                                                                  ((uint32_t)0x00000001U)
#define MMC_FE_FE_ACNE_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_ACNE_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_FE_ACCE_SHIFT                                                                                 ((uint32_t)2U)
#define MMC_FE_FE_ACCE_MASK                                                                                  ((uint32_t)0x00000004U)
#define MMC_FE_FE_ACCE_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_ACCE_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_FE_ACIE_SHIFT                                                                                 ((uint32_t)4U)
#define MMC_FE_FE_ACIE_MASK                                                                                  ((uint32_t)0x00000010U)
#define MMC_FE_FE_ACIE_INTFORCED                                                                             ((uint32_t)1U)
#define MMC_FE_FE_ACIE_NOACTION                                                                              ((uint32_t)0U)

#define MMC_FE_FE_ACEB_SHIFT                                                                                 ((uint32_t)3U)
#define MMC_FE_FE_ACEB_MASK                                                                                  ((uint32_t)0x00000008U)
#define MMC_FE_FE_ACEB_NOACTION                                                                              ((uint32_t)0U)
#define MMC_FE_FE_ACEB_INTFORCED                                                                             ((uint32_t)1U)

#define MMC_FE_FE_ACTO_SHIFT                                                                                 ((uint32_t)1U)
#define MMC_FE_FE_ACTO_MASK                                                                                  ((uint32_t)0x00000002U)
#define MMC_FE_FE_ACTO_NOACTION                                                                              ((uint32_t)0U)
#define MMC_FE_FE_ACTO_INTFORCED                                                                             ((uint32_t)1U)

#define MMC_FE_FE_CNI_SHIFT                                                                                  ((uint32_t)7U)
#define MMC_FE_FE_CNI_MASK                                                                                   ((uint32_t)0x00000080U)
#define MMC_FE_FE_CNI_NOACTION                                                                               ((uint32_t)0U)
#define MMC_FE_FE_CNI_INTFORCED                                                                              ((uint32_t)1U)

#define MMC_FE_RESERVED_SHIFT                                                                                ((uint32_t)5U)
#define MMC_FE_RESERVED_MASK                                                                                 ((uint32_t)0x00000060U)

#define MMC_FE_RESERVED1_SHIFT                                                                               ((uint32_t)8U)
#define MMC_FE_RESERVED1_MASK                                                                                ((uint32_t)0x0000ff00U)

#define MMC_FE_RESERVED2_SHIFT                                                                               ((uint32_t)26U)
#define MMC_FE_RESERVED2_MASK                                                                                ((uint32_t)0x0c000000U)

#define MMC_FE_RESERVED3_SHIFT                                                                               ((uint32_t)30U)
#define MMC_FE_RESERVED3_MASK                                                                                ((uint32_t)0xc0000000U)

#define MMC_ADMAES_LME_SHIFT                                                                                 ((uint32_t)2U)
#define MMC_ADMAES_LME_MASK                                                                                  ((uint32_t)0x00000004U)
#define MMC_ADMAES_LME_NOERROR                                                                               ((uint32_t)0U)
#define MMC_ADMAES_LME_ERROR                                                                                 ((uint32_t)1U)

#define MMC_ADMAES_AES_SHIFT                                                                                 ((uint32_t)0U)
#define MMC_ADMAES_AES_MASK                                                                                  ((uint32_t)0x00000003U)
#define MMC_ADMAES_AES_SYSSDR                                                                                ((uint32_t)0U)
#define MMC_ADMAES_AES_LINKDESC                                                                              ((uint32_t)1U)
#define MMC_ADMAES_AES_RESERVED                                                                              ((uint32_t)2U)
#define MMC_ADMAES_AES_TRANSDATA                                                                             ((uint32_t)3U)

#define MMC_ADMAES_RESERVED_SHIFT                                                                            ((uint32_t)3U)
#define MMC_ADMAES_RESERVED_MASK                                                                             ((uint32_t)0xfffffff8U)

#define MMC_ADMASAL_ADMA_A32B_SHIFT                                                                          ((uint32_t)0U)
#define MMC_ADMASAL_ADMA_A32B_MASK                                                                           ((uint32_t)0xffffffffU)

#define MMC_PVINITSD_INITSDCLK_SEL_SHIFT                                                                     ((uint32_t)0U)
#define MMC_PVINITSD_INITSDCLK_SEL_MASK                                                                      ((uint32_t)0x000003ffU)

#define MMC_PVINITSD_INITCLKGEN_SEL_SHIFT                                                                    ((uint32_t)10U)
#define MMC_PVINITSD_INITCLKGEN_SEL_MASK                                                                     ((uint32_t)0x00000400U)
#define MMC_PVINITSD_INITCLKGEN_SEL_PROG                                                                     ((uint32_t)1U)
#define MMC_PVINITSD_INITCLKGEN_SEL_HOST                                                                     ((uint32_t)0U)

#define MMC_PVINITSD_INITDS_SEL_SHIFT                                                                        ((uint32_t)14U)
#define MMC_PVINITSD_INITDS_SEL_MASK                                                                         ((uint32_t)0x0000c000U)
#define MMC_PVINITSD_INITDS_SEL_DTD                                                                          ((uint32_t)3U)
#define MMC_PVINITSD_INITDS_SEL_DTC                                                                          ((uint32_t)2U)
#define MMC_PVINITSD_INITDS_SEL_DTA                                                                          ((uint32_t)1U)
#define MMC_PVINITSD_INITDS_SEL_DTB                                                                          ((uint32_t)0U)

#define MMC_PVINITSD_DSSDCLK_SEL_SHIFT                                                                       ((uint32_t)16U)
#define MMC_PVINITSD_DSSDCLK_SEL_MASK                                                                        ((uint32_t)0x03ff0000U)

#define MMC_PVINITSD_DSCLKGEN_SEL_SHIFT                                                                      ((uint32_t)26U)
#define MMC_PVINITSD_DSCLKGEN_SEL_MASK                                                                       ((uint32_t)0x04000000U)
#define MMC_PVINITSD_DSCLKGEN_SEL_PROG                                                                       ((uint32_t)1U)
#define MMC_PVINITSD_DSCLKGEN_SEL_HOST                                                                       ((uint32_t)0U)

#define MMC_PVINITSD_DSDS_SEL_SHIFT                                                                          ((uint32_t)30U)
#define MMC_PVINITSD_DSDS_SEL_MASK                                                                           ((uint32_t)0xc0000000U)
#define MMC_PVINITSD_DSDS_SEL_DTD                                                                            ((uint32_t)3U)
#define MMC_PVINITSD_DSDS_SEL_DTC                                                                            ((uint32_t)2U)
#define MMC_PVINITSD_DSDS_SEL_DTA                                                                            ((uint32_t)1U)
#define MMC_PVINITSD_DSDS_SEL_DTB                                                                            ((uint32_t)0U)

#define MMC_PVINITSD_RESERVED_SHIFT                                                                          ((uint32_t)11U)
#define MMC_PVINITSD_RESERVED_MASK                                                                           ((uint32_t)0x00003800U)

#define MMC_PVINITSD_RESERVED1_SHIFT                                                                         ((uint32_t)27U)
#define MMC_PVINITSD_RESERVED1_MASK                                                                          ((uint32_t)0x38000000U)

#define MMC_PVHSSDR12_HSSDCLK_SEL_SHIFT                                                                      ((uint32_t)0U)
#define MMC_PVHSSDR12_HSSDCLK_SEL_MASK                                                                       ((uint32_t)0x000003ffU)

#define MMC_PVHSSDR12_HSCLKGEN_SEL_SHIFT                                                                     ((uint32_t)10U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_MASK                                                                      ((uint32_t)0x00000400U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_PROG                                                                      ((uint32_t)1U)
#define MMC_PVHSSDR12_HSCLKGEN_SEL_HOST                                                                      ((uint32_t)0U)

#define MMC_PVHSSDR12_HSDS_SEL_SHIFT                                                                         ((uint32_t)14U)
#define MMC_PVHSSDR12_HSDS_SEL_MASK                                                                          ((uint32_t)0x0000c000U)
#define MMC_PVHSSDR12_HSDS_SEL_DTB                                                                           ((uint32_t)0U)
#define MMC_PVHSSDR12_HSDS_SEL_DTA                                                                           ((uint32_t)1U)
#define MMC_PVHSSDR12_HSDS_SEL_DTC                                                                           ((uint32_t)2U)
#define MMC_PVHSSDR12_HSDS_SEL_DTD                                                                           ((uint32_t)3U)

#define MMC_PVHSSDR12_SDR12SDCLK_SEL_SHIFT                                                                   ((uint32_t)16U)
#define MMC_PVHSSDR12_SDR12SDCLK_SEL_MASK                                                                    ((uint32_t)0x03ff0000U)

#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_SHIFT                                                                  ((uint32_t)26U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_MASK                                                                   ((uint32_t)0x04000000U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_PROG                                                                   ((uint32_t)1U)
#define MMC_PVHSSDR12_SDR12CLKGEN_SEL_HOST                                                                   ((uint32_t)0U)

#define MMC_PVHSSDR12_SDR12DS_SEL_SHIFT                                                                      ((uint32_t)30U)
#define MMC_PVHSSDR12_SDR12DS_SEL_MASK                                                                       ((uint32_t)0xc0000000U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTD                                                                        ((uint32_t)3U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTC                                                                        ((uint32_t)2U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTA                                                                        ((uint32_t)1U)
#define MMC_PVHSSDR12_SDR12DS_SEL_DTB                                                                        ((uint32_t)0U)

#define MMC_PVHSSDR12_RESERVED_SHIFT                                                                         ((uint32_t)11U)
#define MMC_PVHSSDR12_RESERVED_MASK                                                                          ((uint32_t)0x00003800U)

#define MMC_PVHSSDR12_RESERVED1_SHIFT                                                                        ((uint32_t)27U)
#define MMC_PVHSSDR12_RESERVED1_MASK                                                                         ((uint32_t)0x38000000U)

#define MMC_PVSDR25SDR50_SDR25SDCLK_SEL_SHIFT                                                                ((uint32_t)0U)
#define MMC_PVSDR25SDR50_SDR25SDCLK_SEL_MASK                                                                 ((uint32_t)0x000003ffU)

#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_SHIFT                                                               ((uint32_t)10U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_MASK                                                                ((uint32_t)0x00000400U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_PROG                                                                ((uint32_t)1U)
#define MMC_PVSDR25SDR50_SDR25CLKGEN_SEL_HOST                                                                ((uint32_t)0U)

#define MMC_PVSDR25SDR50_SDR25DS_SEL_SHIFT                                                                   ((uint32_t)14U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_MASK                                                                    ((uint32_t)0x0000c000U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTD                                                                     ((uint32_t)3U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTC                                                                     ((uint32_t)2U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTA                                                                     ((uint32_t)1U)
#define MMC_PVSDR25SDR50_SDR25DS_SEL_DTB                                                                     ((uint32_t)0U)

#define MMC_PVSDR25SDR50_SDR50SDCLK_SEL_SHIFT                                                                ((uint32_t)16U)
#define MMC_PVSDR25SDR50_SDR50SDCLK_SEL_MASK                                                                 ((uint32_t)0x03ff0000U)

#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_SHIFT                                                               ((uint32_t)26U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_MASK                                                                ((uint32_t)0x04000000U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_PROG                                                                ((uint32_t)1U)
#define MMC_PVSDR25SDR50_SDR50CLKGEN_SEL_HOST                                                                ((uint32_t)0U)

#define MMC_PVSDR25SDR50_SDR50DS_SEL_SHIFT                                                                   ((uint32_t)30U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_MASK                                                                    ((uint32_t)0xc0000000U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTD                                                                     ((uint32_t)3U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTC                                                                     ((uint32_t)2U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTA                                                                     ((uint32_t)1U)
#define MMC_PVSDR25SDR50_SDR50DS_SEL_DTB                                                                     ((uint32_t)0U)

#define MMC_PVSDR25SDR50_RESERVED_SHIFT                                                                      ((uint32_t)11U)
#define MMC_PVSDR25SDR50_RESERVED_MASK                                                                       ((uint32_t)0x00003800U)

#define MMC_PVSDR25SDR50_RESERVED1_SHIFT                                                                     ((uint32_t)27U)
#define MMC_PVSDR25SDR50_RESERVED1_MASK                                                                      ((uint32_t)0x38000000U)

#define MMC_PVSDR104DDR50_SDR104SDCLK_SEL_SHIFT                                                              ((uint32_t)0U)
#define MMC_PVSDR104DDR50_SDR104SDCLK_SEL_MASK                                                               ((uint32_t)0x000003ffU)

#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_SHIFT                                                             ((uint32_t)10U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_MASK                                                              ((uint32_t)0x00000400U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_PROG                                                              ((uint32_t)1U)
#define MMC_PVSDR104DDR50_SDR104CLKGEN_SEL_HOST                                                              ((uint32_t)0U)

#define MMC_PVSDR104DDR50_SDR104DS_SEL_SHIFT                                                                 ((uint32_t)14U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_MASK                                                                  ((uint32_t)0x0000c000U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTD                                                                   ((uint32_t)3U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTC                                                                   ((uint32_t)2U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTA                                                                   ((uint32_t)1U)
#define MMC_PVSDR104DDR50_SDR104DS_SEL_DTB                                                                   ((uint32_t)0U)

#define MMC_PVSDR104DDR50_DDR50SDCLK_SEL_SHIFT                                                               ((uint32_t)16U)
#define MMC_PVSDR104DDR50_DDR50SDCLK_SEL_MASK                                                                ((uint32_t)0x03ff0000U)

#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_SHIFT                                                              ((uint32_t)26U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_MASK                                                               ((uint32_t)0x04000000U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_PROG                                                               ((uint32_t)1U)
#define MMC_PVSDR104DDR50_DDR50CLKGEN_SEL_HOST                                                               ((uint32_t)0U)

#define MMC_PVSDR104DDR50_DDR50DS_SEL_SHIFT                                                                  ((uint32_t)30U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_MASK                                                                   ((uint32_t)0xc0000000U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTD                                                                    ((uint32_t)3U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTC                                                                    ((uint32_t)2U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTA                                                                    ((uint32_t)1U)
#define MMC_PVSDR104DDR50_DDR50DS_SEL_DTB                                                                    ((uint32_t)0U)

#define MMC_PVSDR104DDR50_RESERVED_SHIFT                                                                     ((uint32_t)11U)
#define MMC_PVSDR104DDR50_RESERVED_MASK                                                                      ((uint32_t)0x00003800U)

#define MMC_PVSDR104DDR50_RESERVED1_SHIFT                                                                    ((uint32_t)27U)
#define MMC_PVSDR104DDR50_RESERVED1_MASK                                                                     ((uint32_t)0x38000000U)

#define MMC_REV_VREV_SHIFT                                                                                   ((uint32_t)24U)
#define MMC_REV_VREV_MASK                                                                                    ((uint32_t)0xff000000U)

#define MMC_REV_SIS_SHIFT                                                                                    ((uint32_t)0U)
#define MMC_REV_SIS_MASK                                                                                     ((uint32_t)0x00000001U)

#define MMC_REV_SREV_SHIFT                                                                                   ((uint32_t)16U)
#define MMC_REV_SREV_MASK                                                                                    ((uint32_t)0x00ff0000U)
#define MMC_REV_SREV_VER1                                                                                    ((uint32_t)0U)
#define MMC_REV_SREV_VER2                                                                                    ((uint32_t)1U)
#define MMC_REV_SREV_VER3                                                                                    ((uint32_t)2U)
#define MMC_REV_SREV_OTHER                                                                                   ((uint32_t)3U)

#define MMC_REV_RESERVED_SHIFT                                                                               ((uint32_t)1U)
#define MMC_REV_RESERVED_MASK                                                                                ((uint32_t)0x0000fffeU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_MMC_H_ */

