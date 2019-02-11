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
*  \file   hw_mmu.h
*
*  \brief  register-level header file for MMU
*
**/

#ifndef HW_MMU_H_
#define HW_MMU_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MMU_REVISION                                                                                        ((uint32_t)0x0U)
#define MMU_SYSCONFIG                                                                                       ((uint32_t)0x10U)
#define MMU_SYSSTATUS                                                                                       ((uint32_t)0x14U)
#define MMU_IRQSTATUS                                                                                       ((uint32_t)0x18U)
#define MMU_IRQENABLE                                                                                       ((uint32_t)0x1cU)
#define MMU_WALKING_ST                                                                                      ((uint32_t)0x40U)
#define MMU_CNTL                                                                                            ((uint32_t)0x44U)
#define MMU_FAULT_AD                                                                                        ((uint32_t)0x48U)
#define MMU_TTB                                                                                             ((uint32_t)0x4cU)
#define MMU_LOCK                                                                                            ((uint32_t)0x50U)
#define MMU_LD_TLB                                                                                          ((uint32_t)0x54U)
#define MMU_CAM                                                                                             ((uint32_t)0x58U)
#define MMU_RAM                                                                                             ((uint32_t)0x5cU)
#define MMU_GFLUSH                                                                                          ((uint32_t)0x60U)
#define MMU_FLUSH_ENTRY                                                                                     ((uint32_t)0x64U)
#define MMU_READ_CAM                                                                                        ((uint32_t)0x68U)
#define MMU_READ_RAM                                                                                        ((uint32_t)0x6cU)
#define MMU_EMU_FAULT_AD                                                                                    ((uint32_t)0x70U)
#define MMU_FAULT_PC                                                                                        ((uint32_t)0x80U)
#define MMU_FAULT_STATUS                                                                                    ((uint32_t)0x84U)
#define MMU_GP_REG                                                                                          ((uint32_t)0x88U)
#define MMU_DSPSS_GPR                                                                                       ((uint32_t)0x88U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MMU_REVISION_REVISION_SHIFT                                                                          ((uint32_t)0U)
#define MMU_REVISION_REVISION_MASK                                                                           ((uint32_t)0xffffffffU)

#define MMU_SYSCONFIG_AUTOIDLE_SHIFT                                                                         ((uint32_t)0U)
#define MMU_SYSCONFIG_AUTOIDLE_MASK                                                                          ((uint32_t)0x00000001U)
#define MMU_SYSCONFIG_AUTOIDLE_CLKFREE                                                                       ((uint32_t)0U)
#define MMU_SYSCONFIG_AUTOIDLE_AUTOCLKGATE                                                                   ((uint32_t)1U)

#define MMU_SYSCONFIG_SOFTRESET_SHIFT                                                                        ((uint32_t)1U)
#define MMU_SYSCONFIG_SOFTRESET_MASK                                                                         ((uint32_t)0x00000002U)
#define MMU_SYSCONFIG_SOFTRESET_READ0                                                                        ((uint32_t)0U)
#define MMU_SYSCONFIG_SOFTRESET_READ1                                                                        ((uint32_t)1U)
#define MMU_SYSCONFIG_SOFTRESET_WRITE0                                                                       ((uint32_t)0U)
#define MMU_SYSCONFIG_SOFTRESET_WRITE1                                                                       ((uint32_t)1U)

#define MMU_SYSCONFIG_RESERVED_SHIFT                                                                         ((uint32_t)2U)
#define MMU_SYSCONFIG_RESERVED_MASK                                                                          ((uint32_t)0x00000004U)

#define MMU_SYSCONFIG_IDLEMODE_SHIFT                                                                         ((uint32_t)3U)
#define MMU_SYSCONFIG_IDLEMODE_MASK                                                                          ((uint32_t)0x00000018U)
#define MMU_SYSCONFIG_IDLEMODE_SFIDLE                                                                        ((uint32_t)0U)
#define MMU_SYSCONFIG_IDLEMODE_SNIDLE                                                                        ((uint32_t)1U)
#define MMU_SYSCONFIG_IDLEMODE_SSIDLE                                                                        ((uint32_t)2U)
#define MMU_SYSCONFIG_IDLEMODE_RES                                                                           ((uint32_t)3U)

#define MMU_SYSCONFIG_RESERVED2_SHIFT                                                                        ((uint32_t)5U)
#define MMU_SYSCONFIG_RESERVED2_MASK                                                                         ((uint32_t)0x000000e0U)

#define MMU_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                    ((uint32_t)8U)
#define MMU_SYSCONFIG_CLOCKACTIVITY_MASK                                                                     ((uint32_t)0x00000300U)

#define MMU_SYSCONFIG_RESERVED3_SHIFT                                                                        ((uint32_t)10U)
#define MMU_SYSCONFIG_RESERVED3_MASK                                                                         ((uint32_t)0xfffffc00U)

#define MMU_SYSSTATUS_RESETDONE_SHIFT                                                                        ((uint32_t)0U)
#define MMU_SYSSTATUS_RESETDONE_MASK                                                                         ((uint32_t)0x00000001U)
#define MMU_SYSSTATUS_RESETDONE_RSTONGOING                                                                   ((uint32_t)0U)
#define MMU_SYSSTATUS_RESETDONE_RSTCOMP                                                                      ((uint32_t)1U)

#define MMU_SYSSTATUS_RESERVED_SHIFT                                                                         ((uint32_t)1U)
#define MMU_SYSSTATUS_RESERVED_MASK                                                                          ((uint32_t)0x000000feU)

#define MMU_SYSSTATUS_RESERVED2_SHIFT                                                                        ((uint32_t)8U)
#define MMU_SYSSTATUS_RESERVED2_MASK                                                                         ((uint32_t)0xffffff00U)

#define MMU_IRQSTATUS_TLBMISS_SHIFT                                                                          ((uint32_t)0U)
#define MMU_IRQSTATUS_TLBMISS_MASK                                                                           ((uint32_t)0x00000001U)
#define MMU_IRQSTATUS_TLBMISS_READ0                                                                          ((uint32_t)0U)
#define MMU_IRQSTATUS_TLBMISS_READ1                                                                          ((uint32_t)1U)
#define MMU_IRQSTATUS_TLBMISS_WRITE0                                                                         ((uint32_t)0U)
#define MMU_IRQSTATUS_TLBMISS_WRITE1                                                                         ((uint32_t)1U)

#define MMU_IRQSTATUS_TRANSLATIONFAULT_SHIFT                                                                 ((uint32_t)1U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_MASK                                                                  ((uint32_t)0x00000002U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_READ0                                                                 ((uint32_t)0U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_READ1                                                                 ((uint32_t)1U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_WRITE0                                                                ((uint32_t)0U)
#define MMU_IRQSTATUS_TRANSLATIONFAULT_WRITE1                                                                ((uint32_t)1U)

#define MMU_IRQSTATUS_EMUMISS_SHIFT                                                                          ((uint32_t)2U)
#define MMU_IRQSTATUS_EMUMISS_MASK                                                                           ((uint32_t)0x00000004U)
#define MMU_IRQSTATUS_EMUMISS_READ0                                                                          ((uint32_t)0U)
#define MMU_IRQSTATUS_EMUMISS_READ1                                                                          ((uint32_t)1U)
#define MMU_IRQSTATUS_EMUMISS_WRITE0                                                                         ((uint32_t)0U)
#define MMU_IRQSTATUS_EMUMISS_WRITE1                                                                         ((uint32_t)1U)

#define MMU_IRQSTATUS_TABLEWALKFAULT_SHIFT                                                                   ((uint32_t)3U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_MASK                                                                    ((uint32_t)0x00000008U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_READ0                                                                   ((uint32_t)0U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_READ1                                                                   ((uint32_t)1U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_WRITE0                                                                  ((uint32_t)0U)
#define MMU_IRQSTATUS_TABLEWALKFAULT_WRITE1                                                                  ((uint32_t)1U)

#define MMU_IRQSTATUS_MULTIHITFAULT_SHIFT                                                                    ((uint32_t)4U)
#define MMU_IRQSTATUS_MULTIHITFAULT_MASK                                                                     ((uint32_t)0x00000010U)
#define MMU_IRQSTATUS_MULTIHITFAULT_READ0                                                                    ((uint32_t)0U)
#define MMU_IRQSTATUS_MULTIHITFAULT_READ1                                                                    ((uint32_t)1U)
#define MMU_IRQSTATUS_MULTIHITFAULT_WRITE0                                                                   ((uint32_t)0U)
#define MMU_IRQSTATUS_MULTIHITFAULT_WRITE1                                                                   ((uint32_t)1U)

#define MMU_IRQSTATUS_RESERVED_SHIFT                                                                         ((uint32_t)5U)
#define MMU_IRQSTATUS_RESERVED_MASK                                                                          ((uint32_t)0xffffffe0U)

#define MMU_IRQENABLE_TLBMISS_SHIFT                                                                          ((uint32_t)0U)
#define MMU_IRQENABLE_TLBMISS_MASK                                                                           ((uint32_t)0x00000001U)
#define MMU_IRQENABLE_TLBMISS_TRMISSINTM                                                                     ((uint32_t)0U)
#define MMU_IRQENABLE_TLBMISS_TRMISSGINT                                                                     ((uint32_t)1U)

#define MMU_IRQENABLE_TRANSLATIONFAULT_SHIFT                                                                 ((uint32_t)1U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_MASK                                                                  ((uint32_t)0x00000002U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTMASK                                                           ((uint32_t)0U)
#define MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTGINT                                                           ((uint32_t)1U)

#define MMU_IRQENABLE_EMUMISS_SHIFT                                                                          ((uint32_t)2U)
#define MMU_IRQENABLE_EMUMISS_MASK                                                                           ((uint32_t)0x00000004U)
#define MMU_IRQENABLE_EMUMISS_EMUMFLTMASK                                                                    ((uint32_t)0U)
#define MMU_IRQENABLE_EMUMISS_EMUMFLTGINT                                                                    ((uint32_t)1U)

#define MMU_IRQENABLE_TABLEWALKFAULT_SHIFT                                                                   ((uint32_t)3U)
#define MMU_IRQENABLE_TABLEWALKFAULT_MASK                                                                    ((uint32_t)0x00000008U)
#define MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTMASK                                                              ((uint32_t)0U)
#define MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTGINT                                                              ((uint32_t)1U)

#define MMU_IRQENABLE_MULTIHITFAULT_SHIFT                                                                    ((uint32_t)4U)
#define MMU_IRQENABLE_MULTIHITFAULT_MASK                                                                     ((uint32_t)0x00000010U)
#define MMU_IRQENABLE_MULTIHITFAULT_MHFLTMASK                                                                ((uint32_t)0U)
#define MMU_IRQENABLE_MULTIHITFAULT_MHFLTGINT                                                                ((uint32_t)1U)

#define MMU_IRQENABLE_RESERVED_SHIFT                                                                         ((uint32_t)5U)
#define MMU_IRQENABLE_RESERVED_MASK                                                                          ((uint32_t)0xffffffe0U)

#define MMU_WALKING_ST_TWLRUNNING_SHIFT                                                                      ((uint32_t)0U)
#define MMU_WALKING_ST_TWLRUNNING_MASK                                                                       ((uint32_t)0x00000001U)
#define MMU_WALKING_ST_TWLRUNNING_READ0                                                                      ((uint32_t)0U)
#define MMU_WALKING_ST_TWLRUNNING_READ1                                                                      ((uint32_t)1U)

#define MMU_WALKING_ST_RESERVED_SHIFT                                                                        ((uint32_t)1U)
#define MMU_WALKING_ST_RESERVED_MASK                                                                         ((uint32_t)0xfffffffeU)

#define MMU_CNTL_RESERVED_SHIFT                                                                              ((uint32_t)0U)
#define MMU_CNTL_RESERVED_MASK                                                                               ((uint32_t)0x00000001U)

#define MMU_CNTL_MMUENABLE_SHIFT                                                                             ((uint32_t)1U)
#define MMU_CNTL_MMUENABLE_MASK                                                                              ((uint32_t)0x00000002U)
#define MMU_CNTL_MMUENABLE_MMUDIS                                                                            ((uint32_t)0U)
#define MMU_CNTL_MMUENABLE_MMUEN                                                                             ((uint32_t)1U)

#define MMU_CNTL_TWLENABLE_SHIFT                                                                             ((uint32_t)2U)
#define MMU_CNTL_TWLENABLE_MASK                                                                              ((uint32_t)0x00000004U)
#define MMU_CNTL_TWLENABLE_TWLEN                                                                             ((uint32_t)1U)
#define MMU_CNTL_TWLENABLE_TWLDIS                                                                            ((uint32_t)0U)

#define MMU_CNTL_EMUTLBUPDATE_SHIFT                                                                          ((uint32_t)3U)
#define MMU_CNTL_EMUTLBUPDATE_MASK                                                                           ((uint32_t)0x00000008U)
#define MMU_CNTL_EMUTLBUPDATE_EMUDIS                                                                         ((uint32_t)0U)
#define MMU_CNTL_EMUTLBUPDATE_EMUEN                                                                          ((uint32_t)1U)

#define MMU_CNTL_RESERVED2_SHIFT                                                                             ((uint32_t)4U)
#define MMU_CNTL_RESERVED2_MASK                                                                              ((uint32_t)0xfffffff0U)

#define MMU_FAULT_AD_FAULTADDRESS_SHIFT                                                                      ((uint32_t)0U)
#define MMU_FAULT_AD_FAULTADDRESS_MASK                                                                       ((uint32_t)0xffffffffU)

#define MMU_TTB_RESERVED_SHIFT                                                                               ((uint32_t)0U)
#define MMU_TTB_RESERVED_MASK                                                                                ((uint32_t)0x0000007fU)

#define MMU_TTB_TTBADDRESS_SHIFT                                                                             ((uint32_t)7U)
#define MMU_TTB_TTBADDRESS_MASK                                                                              ((uint32_t)0xffffff80U)

#define MMU_LOCK_RESERVED_SHIFT                                                                              ((uint32_t)0U)
#define MMU_LOCK_RESERVED_MASK                                                                               ((uint32_t)0x0000000fU)

#define MMU_LOCK_CURRENTVICTIM_SHIFT                                                                         ((uint32_t)4U)
#define MMU_LOCK_CURRENTVICTIM_MASK                                                                          ((uint32_t)0x000001f0U)

#define MMU_LOCK_RESERVED2_SHIFT                                                                             ((uint32_t)9U)
#define MMU_LOCK_RESERVED2_MASK                                                                              ((uint32_t)0x00000200U)

#define MMU_LOCK_BASEVALUE_SHIFT                                                                             ((uint32_t)10U)
#define MMU_LOCK_BASEVALUE_MASK                                                                              ((uint32_t)0x00007c00U)

#define MMU_LOCK_RESERVED3_SHIFT                                                                             ((uint32_t)15U)
#define MMU_LOCK_RESERVED3_MASK                                                                              ((uint32_t)0xffff8000U)

#define MMU_LD_TLB_LDTLBITEM_SHIFT                                                                           ((uint32_t)0U)
#define MMU_LD_TLB_LDTLBITEM_MASK                                                                            ((uint32_t)0x00000001U)
#define MMU_LD_TLB_LDTLBITEM_READ0                                                                           ((uint32_t)0U)
#define MMU_LD_TLB_LDTLBITEM_READ1                                                                           ((uint32_t)1U)
#define MMU_LD_TLB_LDTLBITEM_WRITE0                                                                          ((uint32_t)0U)
#define MMU_LD_TLB_LDTLBITEM_WRITE1                                                                          ((uint32_t)1U)

#define MMU_LD_TLB_RESERVED_SHIFT                                                                            ((uint32_t)1U)
#define MMU_LD_TLB_RESERVED_MASK                                                                             ((uint32_t)0xfffffffeU)

#define MMU_CAM_PAGESIZE_SHIFT                                                                               ((uint32_t)0U)
#define MMU_CAM_PAGESIZE_MASK                                                                                ((uint32_t)0x00000003U)
#define MMU_CAM_PAGESIZE_SECTION                                                                             ((uint32_t)0U)
#define MMU_CAM_PAGESIZE_LARGE                                                                               ((uint32_t)1U)
#define MMU_CAM_PAGESIZE_SMALL                                                                               ((uint32_t)2U)
#define MMU_CAM_PAGESIZE_SUPER                                                                               ((uint32_t)3U)

#define MMU_CAM_V_SHIFT                                                                                      ((uint32_t)2U)
#define MMU_CAM_V_MASK                                                                                       ((uint32_t)0x00000004U)
#define MMU_CAM_V_INVALID                                                                                    ((uint32_t)0U)
#define MMU_CAM_V_VALID                                                                                      ((uint32_t)1U)

#define MMU_CAM_P_SHIFT                                                                                      ((uint32_t)3U)
#define MMU_CAM_P_MASK                                                                                       ((uint32_t)0x00000008U)
#define MMU_CAM_P_CANFLUSH                                                                                   ((uint32_t)0U)
#define MMU_CAM_P_NOFLUSH                                                                                    ((uint32_t)1U)

#define MMU_CAM_RESERVED_SHIFT                                                                               ((uint32_t)4U)
#define MMU_CAM_RESERVED_MASK                                                                                ((uint32_t)0x00000ff0U)

#define MMU_CAM_VATAG_SHIFT                                                                                  ((uint32_t)12U)
#define MMU_CAM_VATAG_MASK                                                                                   ((uint32_t)0xfffff000U)

#define MMU_RAM_RESERVED_SHIFT                                                                               ((uint32_t)0U)
#define MMU_RAM_RESERVED_MASK                                                                                ((uint32_t)0x0000003fU)

#define MMU_RAM_PHYSICALADDRESS_SHIFT                                                                        ((uint32_t)12U)
#define MMU_RAM_PHYSICALADDRESS_MASK                                                                         ((uint32_t)0xfffff000U)

#define MMU_RAM_MIXED_SHIFT                                                                                  ((uint32_t)6U)
#define MMU_RAM_MIXED_MASK                                                                                   ((uint32_t)0x00000040U)

#define MMU_RAM_ELEMENTSIZE_SHIFT                                                                            ((uint32_t)7U)
#define MMU_RAM_ELEMENTSIZE_MASK                                                                             ((uint32_t)0x00000180U)

#define MMU_RAM_ENDIANNESS_SHIFT                                                                             ((uint32_t)9U)
#define MMU_RAM_ENDIANNESS_MASK                                                                              ((uint32_t)0x00000200U)

#define MMU_RAM_RESERVED1_SHIFT                                                                              ((uint32_t)10U)
#define MMU_RAM_RESERVED1_MASK                                                                               ((uint32_t)0x00000c00U)

#define MMU_GFLUSH_GLOBALFLUSH_SHIFT                                                                         ((uint32_t)0U)
#define MMU_GFLUSH_GLOBALFLUSH_MASK                                                                          ((uint32_t)0x00000001U)
#define MMU_GFLUSH_GLOBALFLUSH_READ0                                                                         ((uint32_t)0U)
#define MMU_GFLUSH_GLOBALFLUSH_READ1                                                                         ((uint32_t)1U)
#define MMU_GFLUSH_GLOBALFLUSH_WRITE0                                                                        ((uint32_t)0U)
#define MMU_GFLUSH_GLOBALFLUSH_WRITE1                                                                        ((uint32_t)1U)

#define MMU_GFLUSH_RESERVED_SHIFT                                                                            ((uint32_t)1U)
#define MMU_GFLUSH_RESERVED_MASK                                                                             ((uint32_t)0xfffffffeU)

#define MMU_FLUSH_ENTRY_FLUSHENTRY_SHIFT                                                                     ((uint32_t)0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_MASK                                                                      ((uint32_t)0x00000001U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_READ0                                                                     ((uint32_t)0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_READ1                                                                     ((uint32_t)1U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_WRITE0                                                                    ((uint32_t)0U)
#define MMU_FLUSH_ENTRY_FLUSHENTRY_WRITE1                                                                    ((uint32_t)1U)

#define MMU_FLUSH_ENTRY_RESERVED_SHIFT                                                                       ((uint32_t)1U)
#define MMU_FLUSH_ENTRY_RESERVED_MASK                                                                        ((uint32_t)0xfffffffeU)

#define MMU_READ_CAM_PAGESIZE_SHIFT                                                                          ((uint32_t)0U)
#define MMU_READ_CAM_PAGESIZE_MASK                                                                           ((uint32_t)0x00000003U)
#define MMU_READ_CAM_PAGESIZE_SECTION                                                                        ((uint32_t)0U)
#define MMU_READ_CAM_PAGESIZE_LARGE                                                                          ((uint32_t)1U)
#define MMU_READ_CAM_PAGESIZE_SMALL                                                                          ((uint32_t)2U)
#define MMU_READ_CAM_PAGESIZE_SUPER                                                                          ((uint32_t)3U)

#define MMU_READ_CAM_V_SHIFT                                                                                 ((uint32_t)2U)
#define MMU_READ_CAM_V_MASK                                                                                  ((uint32_t)0x00000004U)
#define MMU_READ_CAM_V_INVALID                                                                               ((uint32_t)0U)
#define MMU_READ_CAM_V_VALID                                                                                 ((uint32_t)1U)

#define MMU_READ_CAM_P_SHIFT                                                                                 ((uint32_t)3U)
#define MMU_READ_CAM_P_MASK                                                                                  ((uint32_t)0x00000008U)
#define MMU_READ_CAM_P_CANFLUSH                                                                              ((uint32_t)0U)
#define MMU_READ_CAM_P_NOFLUSH                                                                               ((uint32_t)1U)

#define MMU_READ_CAM_RESERVED_SHIFT                                                                          ((uint32_t)4U)
#define MMU_READ_CAM_RESERVED_MASK                                                                           ((uint32_t)0x00000ff0U)

#define MMU_READ_CAM_VATAG_SHIFT                                                                             ((uint32_t)12U)
#define MMU_READ_CAM_VATAG_MASK                                                                              ((uint32_t)0xfffff000U)

#define MMU_READ_RAM_RESERVED_SHIFT                                                                          ((uint32_t)0U)
#define MMU_READ_RAM_RESERVED_MASK                                                                           ((uint32_t)0x0000003fU)

#define MMU_READ_RAM_PHYSICALADDRESS_SHIFT                                                                   ((uint32_t)12U)
#define MMU_READ_RAM_PHYSICALADDRESS_MASK                                                                    ((uint32_t)0xfffff000U)

#define MMU_READ_RAM_MIXED_SHIFT                                                                             ((uint32_t)6U)
#define MMU_READ_RAM_MIXED_MASK                                                                              ((uint32_t)0x00000040U)

#define MMU_READ_RAM_ELEMENTSIZE_SHIFT                                                                       ((uint32_t)7U)
#define MMU_READ_RAM_ELEMENTSIZE_MASK                                                                        ((uint32_t)0x00000180U)

#define MMU_READ_RAM_ENDIANESS_SHIFT                                                                         ((uint32_t)9U)
#define MMU_READ_RAM_ENDIANESS_MASK                                                                          ((uint32_t)0x00000200U)

#define MMU_READ_RAM_RESERVED1_SHIFT                                                                         ((uint32_t)10U)
#define MMU_READ_RAM_RESERVED1_MASK                                                                          ((uint32_t)0x00000c00U)

#define MMU_EMU_FAULT_AD_EMUFAULTADDRESS_SHIFT                                                               ((uint32_t)0U)
#define MMU_EMU_FAULT_AD_EMUFAULTADDRESS_MASK                                                                ((uint32_t)0xffffffffU)

#define MMU_FAULT_PC_PC_SHIFT                                                                                ((uint32_t)0U)
#define MMU_FAULT_PC_PC_MASK                                                                                 ((uint32_t)0xffffffffU)

#define MMU_FAULT_STATUS_FAULTINDICATION_SHIFT                                                               ((uint32_t)0U)
#define MMU_FAULT_STATUS_FAULTINDICATION_MASK                                                                ((uint32_t)0x00000001U)

#define MMU_FAULT_STATUS_MMU_FAULT_TYPE_SHIFT                                                                ((uint32_t)1U)
#define MMU_FAULT_STATUS_MMU_FAULT_TYPE_MASK                                                                 ((uint32_t)0x00000006U)

#define MMU_FAULT_STATUS_RD_WR_SHIFT                                                                         ((uint32_t)3U)
#define MMU_FAULT_STATUS_RD_WR_MASK                                                                          ((uint32_t)0x00000008U)

#define MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_SHIFT                                                            ((uint32_t)4U)
#define MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_MASK                                                             ((uint32_t)0x000000f0U)

#define MMU_FAULT_STATUS_RESERVED_SHIFT                                                                      ((uint32_t)8U)
#define MMU_FAULT_STATUS_RESERVED_MASK                                                                       ((uint32_t)0x7fffff00U)

#define MMU_GP_REG_BUS_ERR_BACK_EN_SHIFT                                                                     ((uint32_t)0U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_MASK                                                                      ((uint32_t)0x00000001U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_DEFAULT                                                                   ((uint32_t)0U)
#define MMU_GP_REG_BUS_ERR_BACK_EN_ALL                                                                       ((uint32_t)1U)

#define MMU_GP_REG_RESERVED_SHIFT                                                                            ((uint32_t)1U)
#define MMU_GP_REG_RESERVED_MASK                                                                             ((uint32_t)0xfffffffeU)

#define MMU_DSPSS_GPR_HWDEBUG_MUX_SHIFT                                                                      ((uint32_t)0U)
#define MMU_DSPSS_GPR_HWDEBUG_MUX_MASK                                                                       ((uint32_t)0x0000000fU)

#define MMU_DSPSS_GPR_RESERVED_SHIFT                                                                         ((uint32_t)4U)
#define MMU_DSPSS_GPR_RESERVED_MASK                                                                          ((uint32_t)0x00007ff0U)

#define MMU_DSPSS_GPR_FORCE_IDLE_REQ_SHIFT                                                                   ((uint32_t)15U)
#define MMU_DSPSS_GPR_FORCE_IDLE_REQ_MASK                                                                    ((uint32_t)0x00008000U)

#define MMU_DSPSS_GPR_RESERVED1_SHIFT                                                                        ((uint32_t)16U)
#define MMU_DSPSS_GPR_RESERVED1_MASK                                                                         ((uint32_t)0xffff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MMU_H_ */
