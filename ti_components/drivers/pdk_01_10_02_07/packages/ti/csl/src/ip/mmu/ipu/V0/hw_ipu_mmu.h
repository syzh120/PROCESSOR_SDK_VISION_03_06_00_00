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

#ifndef HW_IPU_MMU_H_
#define HW_IPU_MMU_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define IPU_MMU_REVISION                                                                                    (0x0U)
#define IPU_MMU_SYSCONFIG                                                                                   (0x10U)
#define IPU_MMU_SYSSTATUS                                                                                   (0x14U)
#define IPU_MMU_IRQSTATUS                                                                                   (0x18U)
#define IPU_MMU_IRQENABLE                                                                                   (0x1cU)
#define IPU_MMU_WALKING_ST                                                                                  (0x40U)
#define IPU_MMU_CNTL                                                                                        (0x44U)
#define IPU_MMU_FAULT_AD                                                                                    (0x48U)
#define IPU_MMU_TTB                                                                                         (0x4cU)
#define IPU_MMU_LOCK                                                                                        (0x50U)
#define IPU_MMU_LD_TLB                                                                                      (0x54U)
#define IPU_MMU_CAM                                                                                         (0x58U)
#define IPU_MMU_RAM                                                                                         (0x5cU)
#define IPU_MMU_GFLUSH                                                                                      (0x60U)
#define IPU_MMU_FLUSH_ENTRY                                                                                 (0x64U)
#define IPU_MMU_READ_CAM                                                                                    (0x68U)
#define IPU_MMU_READ_RAM                                                                                    (0x6cU)
#define IPU_MMU_EMU_FAULT_AD                                                                                (0x70U)
#define IPU_MMU_FAULT_PC                                                                                    (0x80U)
#define IPU_MMU_FAULT_STATUS                                                                                (0x84U)
#define IPU_MMU_GP_REG                                                                                      (0x88U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define IPU_MMU_REVISION_REVISION_SHIFT                                                                     (0U)
#define IPU_MMU_REVISION_REVISION_MASK                                                                      (0xffffffffU)

#define IPU_MMU_SYSCONFIG_AUTOIDLE_SHIFT                                                                    (0U)
#define IPU_MMU_SYSCONFIG_AUTOIDLE_MASK                                                                     (0x00000001U)
#define IPU_MMU_SYSCONFIG_AUTOIDLE_CLKFREE                                                                   (0U)
#define IPU_MMU_SYSCONFIG_AUTOIDLE_AUTOCLKGATE                                                               (1U)

#define IPU_MMU_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                               (8U)
#define IPU_MMU_SYSCONFIG_CLOCKACTIVITY_MASK                                                                (0x00000300U)

#define IPU_MMU_SYSCONFIG_SOFTRESET_SHIFT                                                                   (1U)
#define IPU_MMU_SYSCONFIG_SOFTRESET_MASK                                                                    (0x00000002U)
#define IPU_MMU_SYSCONFIG_SOFTRESET_ALWAYS_R                                                                 (0U)
#define IPU_MMU_SYSCONFIG_SOFTRESET_NEVER_R                                                                  (1U)
#define IPU_MMU_SYSCONFIG_SOFTRESET_NOFUN_W                                                                  (0U)
#define IPU_MMU_SYSCONFIG_SOFTRESET_RSTMODE_W                                                                (1U)

#define IPU_MMU_SYSCONFIG_RESERVED1_SHIFT                                                                   (5U)
#define IPU_MMU_SYSCONFIG_RESERVED1_MASK                                                                    (0x000000e0U)

#define IPU_MMU_SYSCONFIG_RESERVED0_SHIFT                                                                   (2U)
#define IPU_MMU_SYSCONFIG_RESERVED0_MASK                                                                    (0x00000004U)

#define IPU_MMU_SYSCONFIG_RESERVED3_SHIFT                                                                   (10U)
#define IPU_MMU_SYSCONFIG_RESERVED3_MASK                                                                    (0xfffffc00U)

#define IPU_MMU_SYSCONFIG_IDLEMODE_SHIFT                                                                    (3U)
#define IPU_MMU_SYSCONFIG_IDLEMODE_MASK                                                                     (0x00000018U)
#define IPU_MMU_SYSCONFIG_IDLEMODE_SFIDLE                                                                    (0U)
#define IPU_MMU_SYSCONFIG_IDLEMODE_SNIDLE                                                                    (1U)
#define IPU_MMU_SYSCONFIG_IDLEMODE_SSIDLE                                                                    (2U)
#define IPU_MMU_SYSCONFIG_IDLEMODE_RES                                                                       (3U)

#define IPU_MMU_SYSSTATUS_RESETDONE_SHIFT                                                                   (0U)
#define IPU_MMU_SYSSTATUS_RESETDONE_MASK                                                                    (0x00000001U)
#define IPU_MMU_SYSSTATUS_RESETDONE_RSTONGOING                                                               (0U)
#define IPU_MMU_SYSSTATUS_RESETDONE_RSTCOMP                                                                  (1U)

#define IPU_MMU_SYSSTATUS_RESERVED_SHIFT                                                                    (1U)
#define IPU_MMU_SYSSTATUS_RESERVED_MASK                                                                     (0xfffffffeU)

#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_SHIFT                                                              (3U)
#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_MASK                                                               (0x00000008U)
#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_NTWF_R                                                              (0U)
#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_TWF_R                                                               (1U)
#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_TWFSTAT_W                                                           (0U)
#define IPU_MMU_IRQSTATUS_TABLEWALKFAULT_RTWFSTAT_W                                                          (1U)

#define IPU_MMU_IRQSTATUS_RESERVED_SHIFT                                                                    (5U)
#define IPU_MMU_IRQSTATUS_RESERVED_MASK                                                                     (0xffffffe0U)

#define IPU_MMU_IRQSTATUS_TLBMISS_SHIFT                                                                     (0U)
#define IPU_MMU_IRQSTATUS_TLBMISS_MASK                                                                      (0x00000001U)
#define IPU_MMU_IRQSTATUS_TLBMISS_NTLBM_R                                                                    (0U)
#define IPU_MMU_IRQSTATUS_TLBMISS_TLBM_R                                                                     (1U)
#define IPU_MMU_IRQSTATUS_TLBMISS_MSTAT_W                                                                    (0U)
#define IPU_MMU_IRQSTATUS_TLBMISS_RMSTAT_W                                                                   (1U)

#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_SHIFT                                                               (4U)
#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_MASK                                                                (0x00000010U)
#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_NMHF_R                                                               (0U)
#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_MHF_R                                                                (1U)
#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_MHFSTAT_W                                                            (0U)
#define IPU_MMU_IRQSTATUS_MULTIHITFAULT_RMHFSTAT_W                                                           (1U)

#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_SHIFT                                                            (1U)
#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_MASK                                                             (0x00000002U)
#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_NFAULT_R                                                          (0U)
#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_FAULT_R                                                           (1U)
#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_FSTAT_W                                                           (0U)
#define IPU_MMU_IRQSTATUS_TRANSLATIONFAULT_RFSTAT_W                                                          (1U)

#define IPU_MMU_IRQSTATUS_EMUMISS_SHIFT                                                                     (2U)
#define IPU_MMU_IRQSTATUS_EMUMISS_MASK                                                                      (0x00000004U)
#define IPU_MMU_IRQSTATUS_EMUMISS_NEMUM_R                                                                    (0U)
#define IPU_MMU_IRQSTATUS_EMUMISS_EMUM_R                                                                     (1U)
#define IPU_MMU_IRQSTATUS_EMUMISS_ESTAT_W                                                                    (0U)
#define IPU_MMU_IRQSTATUS_EMUMISS_RESTAT_W                                                                   (1U)

#define IPU_MMU_IRQENABLE_TRANSLATIONFAULT_SHIFT                                                            (1U)
#define IPU_MMU_IRQENABLE_TRANSLATIONFAULT_MASK                                                             (0x00000002U)
#define IPU_MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTMASK                                                       (0U)
#define IPU_MMU_IRQENABLE_TRANSLATIONFAULT_TRANFLTGINT                                                       (1U)

#define IPU_MMU_IRQENABLE_TABLEWALKFAULT_SHIFT                                                              (3U)
#define IPU_MMU_IRQENABLE_TABLEWALKFAULT_MASK                                                               (0x00000008U)
#define IPU_MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTMASK                                                          (0U)
#define IPU_MMU_IRQENABLE_TABLEWALKFAULT_TWLFLTGINT                                                          (1U)

#define IPU_MMU_IRQENABLE_RESERVED_SHIFT                                                                    (5U)
#define IPU_MMU_IRQENABLE_RESERVED_MASK                                                                     (0xffffffe0U)

#define IPU_MMU_IRQENABLE_TLBMISS_SHIFT                                                                     (0U)
#define IPU_MMU_IRQENABLE_TLBMISS_MASK                                                                      (0x00000001U)
#define IPU_MMU_IRQENABLE_TLBMISS_TRMISSINTM                                                                 (0U)
#define IPU_MMU_IRQENABLE_TLBMISS_TRMISSGINT                                                                 (1U)

#define IPU_MMU_IRQENABLE_EMUMISS_SHIFT                                                                     (2U)
#define IPU_MMU_IRQENABLE_EMUMISS_MASK                                                                      (0x00000004U)
#define IPU_MMU_IRQENABLE_EMUMISS_EMUMFLTMASK                                                                (0U)
#define IPU_MMU_IRQENABLE_EMUMISS_EMUMFLTGINT                                                                (1U)

#define IPU_MMU_IRQENABLE_MULTIHITFAULT_SHIFT                                                               (4U)
#define IPU_MMU_IRQENABLE_MULTIHITFAULT_MASK                                                                (0x00000010U)
#define IPU_MMU_IRQENABLE_MULTIHITFAULT_MHFLTMASK                                                            (0U)
#define IPU_MMU_IRQENABLE_MULTIHITFAULT_MHFLTGINT                                                            (1U)

#define IPU_MMU_WALKING_ST_TWLRUNNING_SHIFT                                                                 (0U)
#define IPU_MMU_WALKING_ST_TWLRUNNING_MASK                                                                  (0x00000001U)
#define IPU_MMU_WALKING_ST_TWLRUNNING_TWLCOMP                                                                (0U)
#define IPU_MMU_WALKING_ST_TWLRUNNING_TWLRUN                                                                 (1U)

#define IPU_MMU_WALKING_ST_RESERVED_SHIFT                                                                   (1U)
#define IPU_MMU_WALKING_ST_RESERVED_MASK                                                                    (0xfffffffeU)

#define IPU_MMU_CNTL_MMUENABLE_SHIFT                                                                        (1U)
#define IPU_MMU_CNTL_MMUENABLE_MASK                                                                         (0x00000002U)
#define IPU_MMU_CNTL_MMUENABLE_MMUDIS                                                                        (0U)
#define IPU_MMU_CNTL_MMUENABLE_MMUEN                                                                         (1U)

#define IPU_MMU_CNTL_EMUTLBUPDATE_SHIFT                                                                     (3U)
#define IPU_MMU_CNTL_EMUTLBUPDATE_MASK                                                                      (0x00000008U)
#define IPU_MMU_CNTL_EMUTLBUPDATE_EMUDIS                                                                     (0U)
#define IPU_MMU_CNTL_EMUTLBUPDATE_EMUEN                                                                      (1U)

#define IPU_MMU_CNTL_TWLENABLE_SHIFT                                                                        (2U)
#define IPU_MMU_CNTL_TWLENABLE_MASK                                                                         (0x00000004U)
#define IPU_MMU_CNTL_TWLENABLE_TWLDIS                                                                        (0U)
#define IPU_MMU_CNTL_TWLENABLE_TWLEN                                                                         (1U)

#define IPU_MMU_CNTL_RESERVED0_SHIFT                                                                        (0U)
#define IPU_MMU_CNTL_RESERVED0_MASK                                                                         (0x00000001U)

#define IPU_MMU_CNTL_RESERVED1_SHIFT                                                                        (4U)
#define IPU_MMU_CNTL_RESERVED1_MASK                                                                         (0xfffffff0U)

#define IPU_MMU_FAULT_AD_FAULTADDRESS_SHIFT                                                                 (0U)
#define IPU_MMU_FAULT_AD_FAULTADDRESS_MASK                                                                  (0xffffffffU)

#define IPU_MMU_TTB_TTBADDRESS_SHIFT                                                                        (7U)
#define IPU_MMU_TTB_TTBADDRESS_MASK                                                                         (0xffffff80U)

#define IPU_MMU_TTB_RESERVED_SHIFT                                                                          (0U)
#define IPU_MMU_TTB_RESERVED_MASK                                                                           (0x0000007fU)

#define IPU_MMU_LOCK_CURRENTVICTIM_SHIFT                                                                    (4U)
#define IPU_MMU_LOCK_CURRENTVICTIM_MASK                                                                     (0x000001f0U)

#define IPU_MMU_LOCK_BASEVALUE_SHIFT                                                                        (10U)
#define IPU_MMU_LOCK_BASEVALUE_MASK                                                                         (0x00007c00U)

#define IPU_MMU_LOCK_RESERVED0_SHIFT                                                                        (0U)
#define IPU_MMU_LOCK_RESERVED0_MASK                                                                         (0x0000000fU)

#define IPU_MMU_LOCK_RESERVED1_SHIFT                                                                        (9U)
#define IPU_MMU_LOCK_RESERVED1_MASK                                                                         (0x00000200U)

#define IPU_MMU_LOCK_RESERVED2_SHIFT                                                                        (15U)
#define IPU_MMU_LOCK_RESERVED2_MASK                                                                         (0xffff8000U)

#define IPU_MMU_LD_TLB_LDTLBITEM_SHIFT                                                                      (0U)
#define IPU_MMU_LD_TLB_LDTLBITEM_MASK                                                                       (0x00000001U)
#define IPU_MMU_LD_TLB_LDTLBITEM_ALWAYS_R                                                                    (0U)
#define IPU_MMU_LD_TLB_LDTLBITEM_NEVER_R                                                                     (1U)
#define IPU_MMU_LD_TLB_LDTLBITEM_NOEFFECT_W                                                                  (0U)
#define IPU_MMU_LD_TLB_LDTLBITEM_LDTLB_W                                                                     (1U)

#define IPU_MMU_LD_TLB_RESERVED_SHIFT                                                                       (1U)
#define IPU_MMU_LD_TLB_RESERVED_MASK                                                                        (0xfffffffeU)

#define IPU_MMU_CAM_V_SHIFT                                                                                 (2U)
#define IPU_MMU_CAM_V_MASK                                                                                  (0x00000004U)
#define IPU_MMU_CAM_V_INVALID                                                                                (0U)
#define IPU_MMU_CAM_V_VALID                                                                                  (1U)

#define IPU_MMU_CAM_P_SHIFT                                                                                 (3U)
#define IPU_MMU_CAM_P_MASK                                                                                  (0x00000008U)
#define IPU_MMU_CAM_P_CANFLUSH                                                                               (0U)
#define IPU_MMU_CAM_P_NOFLUSH                                                                                (1U)

#define IPU_MMU_CAM_VATAG_SHIFT                                                                             (12U)
#define IPU_MMU_CAM_VATAG_MASK                                                                              (0xfffff000U)

#define IPU_MMU_CAM_RESERVED_SHIFT                                                                          (4U)
#define IPU_MMU_CAM_RESERVED_MASK                                                                           (0x00000ff0U)

#define IPU_MMU_CAM_PAGESIZE_SHIFT                                                                          (0U)
#define IPU_MMU_CAM_PAGESIZE_MASK                                                                           (0x00000003U)
#define IPU_MMU_CAM_PAGESIZE_SECTION                                                                         (0U)
#define IPU_MMU_CAM_PAGESIZE_LARGE                                                                           (1U)
#define IPU_MMU_CAM_PAGESIZE_SMALL                                                                           (2U)
#define IPU_MMU_CAM_PAGESIZE_SUPER                                                                           (3U)

#define IPU_MMU_RAM_RESERVED_SHIFT                                                                          (0U)
#define IPU_MMU_RAM_RESERVED_MASK                                                                           (0x0000003fU)

#define IPU_MMU_RAM_PHYSICALADDRESS_SHIFT                                                                   (12U)
#define IPU_MMU_RAM_PHYSICALADDRESS_MASK                                                                    (0xfffff000U)

#define IPU_MMU_RAM_RESERVED1_SHIFT                                                                         (10U)
#define IPU_MMU_RAM_RESERVED1_MASK                                                                          (0x00000c00U)

#define IPU_MMU_RAM_ENDIANNESS_SHIFT                                                                        (9U)
#define IPU_MMU_RAM_ENDIANNESS_MASK                                                                         (0x00000200U)
#define IPU_MMU_RAM_ENDIANNESS_LITTLE                                                                        (0U)
#define IPU_MMU_RAM_ENDIANNESS_BIG                                                                           (1U)

#define IPU_MMU_RAM_MIXED_SHIFT                                                                             (6U)
#define IPU_MMU_RAM_MIXED_MASK                                                                              (0x00000040U)
#define IPU_MMU_RAM_MIXED_TLBES                                                                              (0U)
#define IPU_MMU_RAM_MIXED_CPUES                                                                              (1U)

#define IPU_MMU_RAM_ELEMENTSIZE_SHIFT                                                                       (7U)
#define IPU_MMU_RAM_ELEMENTSIZE_MASK                                                                        (0x00000180U)
#define IPU_MMU_RAM_ELEMENTSIZE_BYTE                                                                         (0U)
#define IPU_MMU_RAM_ELEMENTSIZE_SHORT                                                                        (1U)
#define IPU_MMU_RAM_ELEMENTSIZE_LONG                                                                         (2U)
#define IPU_MMU_RAM_ELEMENTSIZE_NONE                                                                         (3U)

#define IPU_MMU_GFLUSH_GLOBALFLUSH_SHIFT                                                                    (0U)
#define IPU_MMU_GFLUSH_GLOBALFLUSH_MASK                                                                     (0x00000001U)
#define IPU_MMU_GFLUSH_GLOBALFLUSH_RTN0_R                                                                    (0U)
#define IPU_MMU_GFLUSH_GLOBALFLUSH_NEVER_R                                                                   (1U)
#define IPU_MMU_GFLUSH_GLOBALFLUSH_NFT_W                                                                     (0U)
#define IPU_MMU_GFLUSH_GLOBALFLUSH_FLUSH_W                                                                   (1U)

#define IPU_MMU_GFLUSH_RESERVED_SHIFT                                                                       (1U)
#define IPU_MMU_GFLUSH_RESERVED_MASK                                                                        (0xfffffffeU)

#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_SHIFT                                                                (0U)
#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_MASK                                                                 (0x00000001U)
#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_ALWAYS_R                                                              (0U)
#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_NEVER_R                                                               (1U)
#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_NOFUN_W                                                               (0U)
#define IPU_MMU_FLUSH_ENTRY_FLUSHENTRY_FLUSHTLB_W                                                            (1U)

#define IPU_MMU_FLUSH_ENTRY_RESERVED_SHIFT                                                                  (1U)
#define IPU_MMU_FLUSH_ENTRY_RESERVED_MASK                                                                   (0xfffffffeU)

#define IPU_MMU_READ_CAM_P_SHIFT                                                                            (3U)
#define IPU_MMU_READ_CAM_P_MASK                                                                             (0x00000008U)
#define IPU_MMU_READ_CAM_P_CANFLUSH                                                                          (0U)
#define IPU_MMU_READ_CAM_P_NOFLUSH                                                                           (1U)

#define IPU_MMU_READ_CAM_V_SHIFT                                                                            (2U)
#define IPU_MMU_READ_CAM_V_MASK                                                                             (0x00000004U)
#define IPU_MMU_READ_CAM_V_INVALID                                                                           (0U)
#define IPU_MMU_READ_CAM_V_VALID                                                                             (1U)

#define IPU_MMU_READ_CAM_RESERVED_SHIFT                                                                     (4U)
#define IPU_MMU_READ_CAM_RESERVED_MASK                                                                      (0x00000ff0U)

#define IPU_MMU_READ_CAM_PAGESIZE_SHIFT                                                                     (0U)
#define IPU_MMU_READ_CAM_PAGESIZE_MASK                                                                      (0x00000003U)
#define IPU_MMU_READ_CAM_PAGESIZE_SECTION                                                                    (0U)
#define IPU_MMU_READ_CAM_PAGESIZE_LARGE                                                                      (1U)
#define IPU_MMU_READ_CAM_PAGESIZE_SMALL                                                                      (2U)
#define IPU_MMU_READ_CAM_PAGESIZE_SUPER                                                                      (3U)

#define IPU_MMU_READ_CAM_VATAG_SHIFT                                                                        (12U)
#define IPU_MMU_READ_CAM_VATAG_MASK                                                                         (0xfffff000U)

#define IPU_MMU_READ_RAM_ELEMENTSIZE_SHIFT                                                                  (7U)
#define IPU_MMU_READ_RAM_ELEMENTSIZE_MASK                                                                   (0x00000180U)
#define IPU_MMU_READ_RAM_ELEMENTSIZE_BYTE                                                                    (0U)
#define IPU_MMU_READ_RAM_ELEMENTSIZE_SHORT                                                                   (1U)
#define IPU_MMU_READ_RAM_ELEMENTSIZE_LONG                                                                    (2U)
#define IPU_MMU_READ_RAM_ELEMENTSIZE_NONE                                                                    (3U)

#define IPU_MMU_READ_RAM_RESERVED_SHIFT                                                                     (0U)
#define IPU_MMU_READ_RAM_RESERVED_MASK                                                                      (0x0000003fU)

#define IPU_MMU_READ_RAM_PHYSICALADDRESS_SHIFT                                                              (12U)
#define IPU_MMU_READ_RAM_PHYSICALADDRESS_MASK                                                               (0xfffff000U)

#define IPU_MMU_READ_RAM_RESERVED1_SHIFT                                                                    (10U)
#define IPU_MMU_READ_RAM_RESERVED1_MASK                                                                     (0x00000c00U)

#define IPU_MMU_READ_RAM_ENDIANNESS_SHIFT                                                                   (9U)
#define IPU_MMU_READ_RAM_ENDIANNESS_MASK                                                                    (0x00000200U)
#define IPU_MMU_READ_RAM_ENDIANNESS_LITTLE                                                                   (0U)
#define IPU_MMU_READ_RAM_ENDIANNESS_BIG                                                                      (1U)

#define IPU_MMU_READ_RAM_MIXED_SHIFT                                                                        (6U)
#define IPU_MMU_READ_RAM_MIXED_MASK                                                                         (0x00000040U)
#define IPU_MMU_READ_RAM_MIXED_TLBES                                                                         (0U)
#define IPU_MMU_READ_RAM_MIXED_CPUES                                                                         (1U)

#define IPU_MMU_EMU_FAULT_AD_EMUFAULTADDRESS_SHIFT                                                          (0U)
#define IPU_MMU_EMU_FAULT_AD_EMUFAULTADDRESS_MASK                                                           (0xffffffffU)

#define IPU_MMU_FAULT_PC_PC_SHIFT                                                                           (0U)
#define IPU_MMU_FAULT_PC_PC_MASK                                                                            (0xffffffffU)

#define IPU_MMU_FAULT_STATUS_FAULTINDICATION_SHIFT                                                          (0U)
#define IPU_MMU_FAULT_STATUS_FAULTINDICATION_MASK                                                           (0x00000001U)

#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TYPE_SHIFT                                                           (1U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TYPE_MASK                                                            (0x00000006U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TYPE_LD_ST                                                            (0U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TYPE_FETCH                                                            (1U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TYPE_DMA                                                              (2U)

#define IPU_MMU_FAULT_STATUS_RD_WR_SHIFT                                                                    (3U)
#define IPU_MMU_FAULT_STATUS_RD_WR_MASK                                                                     (0x00000008U)

#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_SHIFT                                                       (4U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_MASK                                                        (0x000000f0U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_DMA_RD1                                                      (0U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_DMA_RD2                                                      (1U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_DMA_WR1                                                      (2U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_DMA_WR2                                                      (3U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_CACHE_MISC                                                   (4U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_CACHE_CPU                                                    (5U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_CACHE_DMA                                                    (6U)
#define IPU_MMU_FAULT_STATUS_MMU_FAULT_TRANS_ID_MMU_HW_TBL_WALK                                              (8U)

#define IPU_MMU_FAULT_STATUS_RESERVED_SHIFT                                                                 (8U)
#define IPU_MMU_FAULT_STATUS_RESERVED_MASK                                                                  (0xffffff00U)

#define IPU_MMU_GP_REG_BUS_ERR_BACK_EN_SHIFT                                                                (0U)
#define IPU_MMU_GP_REG_BUS_ERR_BACK_EN_MASK                                                                 (0x00000001U)

#define IPU_MMU_GP_REG_RESERVED_SHIFT                                                                       (1U)
#define IPU_MMU_GP_REG_RESERVED_MASK                                                                        (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_MMU_H_ */
