/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_IPUMMU_H_
#define CSLR_IPUMMU_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 REVISION;
    volatile Uint8  RSVD0[12];
    volatile Uint32 SYSCONFIG;
    volatile Uint32 SYSSTS;
    volatile Uint32 IRQSTS;
    volatile Uint32 IRQEN;
    volatile Uint8  RSVD1[32];
    volatile Uint32 WALKING_ST;
    volatile Uint32 CNTL;
    volatile Uint32 FAULT_AD;
    volatile Uint32 TTB;
    volatile Uint32 LOCK;
    volatile Uint32 LD_TLB;
    volatile Uint32 CAM;
    volatile Uint32 RAM;
    volatile Uint32 GFLUSH;
    volatile Uint32 FLUSH_ENTRY;
    volatile Uint32 READ_CAM;
    volatile Uint32 READ_RAM;
    volatile Uint32 EMU_FAULT_AD;
    volatile Uint8  RSVD2[12];
    volatile Uint32 FAULT_PC;
    volatile Uint32 FAULT_STS;
    volatile Uint32 GPR;
} CSL_IpuMmuRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This register contains the IP revision code */
#define CSL_IPUMMU_REVISION                                     (0x0U)

/* This register controls the various parameters of the OCP interface */
#define CSL_IPUMMU_SYSCONFIG                                    (0x10U)

/* This register provides status information about the module, excluding the
 * interrupt status information */
#define CSL_IPUMMU_SYSSTS                                       (0x14U)

/* This interrupt status register regroups all the status of the module
 * internal events that can generate an interrupt. */
#define CSL_IPUMMU_IRQSTS                                       (0x18U)

/* The interrupt enable register allows to mask/unmask the module internal
 * sources of interrupt, on a event-by-event basis. */
#define CSL_IPUMMU_IRQEN                                        (0x1CU)

/* This register provides status information about the table walking logic */
#define CSL_IPUMMU_WALKING_ST                                   (0x40U)

/* This register programs the MMU features */
#define CSL_IPUMMU_CNTL                                         (0x44U)

/* This register contains the virtual address that generated the interrupt */
#define CSL_IPUMMU_FAULT_AD                                     (0x48U)

/* This register contains the Translation Table Base address */
#define CSL_IPUMMU_TTB                                          (0x4CU)

/* This register locks some of the TLB entries */
#define CSL_IPUMMU_LOCK                                         (0x50U)

/* This register loads a TLB entry (CAM+RAM) */
#define CSL_IPUMMU_LD_TLB                                       (0x54U)

/* This register holds a CAM entry */
#define CSL_IPUMMU_CAM                                          (0x58U)

/* This register holds a RAM entry */
#define CSL_IPUMMU_RAM                                          (0x5CU)

/* This register flushes all the non-protected TLB entries */
#define CSL_IPUMMU_GFLUSH                                       (0x60U)

/* This register flushes the entry pointed to by the CAM virtual address */
#define CSL_IPUMMU_FLUSH_ENTRY                                  (0x64U)

/* This register reads CAM data from a CAM entry */
#define CSL_IPUMMU_READ_CAM                                     (0x68U)

/* This register reads RAM data from a RAM entry */
#define CSL_IPUMMU_READ_RAM                                     (0x6CU)

/* This register contains the last virtual address of a fault caused by the
 * debugger */
#define CSL_IPUMMU_EMU_FAULT_AD                                 (0x70U)

/* FAULT_PC */
#define CSL_IPUMMU_FAULT_PC                                     (0x80U)

/* FAULT_STS */
#define CSL_IPUMMU_FAULT_STS                                    (0x84U)

/* controls hwdebug output mux. Force idle req generation */
#define CSL_IPUMMU_GPR                                          (0x88U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_IPUMMU_REVISION_REV_MAJ_MASK                        (0x000000F0U)
#define CSL_IPUMMU_REVISION_REV_MAJ_SHIFT                       (4U)
#define CSL_IPUMMU_REVISION_REV_MAJ_RESETVAL                    (0x00000002U)
#define CSL_IPUMMU_REVISION_REV_MAJ_MAX                         (0x0000000fU)

#define CSL_IPUMMU_REVISION_REV_MIN_MASK                        (0x0000000FU)
#define CSL_IPUMMU_REVISION_REV_MIN_SHIFT                       (0U)
#define CSL_IPUMMU_REVISION_REV_MIN_RESETVAL                    (0x00000000U)
#define CSL_IPUMMU_REVISION_REV_MIN_MAX                         (0x0000000fU)

#define CSL_IPUMMU_REVISION_RESETVAL                            (0x00000020U)

/* SYSCONFIG */

#define CSL_IPUMMU_SYSCONFIG_AUTOIDLE_MASK                      (0x00000001U)
#define CSL_IPUMMU_SYSCONFIG_AUTOIDLE_SHIFT                     (0U)
#define CSL_IPUMMU_SYSCONFIG_AUTOIDLE_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_AUTOIDLE_CLKFREE                   (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_AUTOIDLE_AUTOCLKGATE               (0x00000001U)

#define CSL_IPUMMU_SYSCONFIG_CLOCKACTIVITY_MASK                 (0x00000300U)
#define CSL_IPUMMU_SYSCONFIG_CLOCKACTIVITY_SHIFT                (8U)
#define CSL_IPUMMU_SYSCONFIG_CLOCKACTIVITY_RESETVAL             (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_CLOCKACTIVITY_MAX                  (0x00000003U)

#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_MASK                     (0x00000002U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_SHIFT                    (1U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_RESETVAL                 (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_ALWAYS_R                 (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_NEVER_R                  (0x00000001U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_NOFUN_W                  (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_SOFTRESET_RSTMODE_W                (0x00000001U)

#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_MASK                      (0x00000018U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_SHIFT                     (3U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_SFIDLE                    (0x00000000U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_SNIDLE                    (0x00000001U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_SSIDLE                    (0x00000002U)
#define CSL_IPUMMU_SYSCONFIG_IDLEMODE_RES                       (0x00000003U)

#define CSL_IPUMMU_SYSCONFIG_RESETVAL                           (0x00000000U)

/* SYSSTS */

#define CSL_IPUMMU_SYSSTS_RESETDONE_MASK                        (0x00000001U)
#define CSL_IPUMMU_SYSSTS_RESETDONE_SHIFT                       (0U)
#define CSL_IPUMMU_SYSSTS_RESETDONE_RESETVAL                    (0x00000000U)
#define CSL_IPUMMU_SYSSTS_RESETDONE_RSTONGOING                  (0x00000000U)
#define CSL_IPUMMU_SYSSTS_RESETDONE_RSTCOMP                     (0x00000001U)

#define CSL_IPUMMU_SYSSTS_RESETVAL                              (0x00000000U)

/* IRQSTS */

#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_MASK                     (0x00000008U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_SHIFT                    (3U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_RESETVAL                 (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_NTWF_R                   (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_TWF_R                    (0x00000001U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_TWFSTAT_W                (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TBLWALKFAULT_RTWFSTAT_W               (0x00000001U)

#define CSL_IPUMMU_IRQSTS_TLBMISS_MASK                          (0x00000001U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_SHIFT                         (0U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_RESETVAL                      (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_NTLBM_R                       (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_TLBM_R                        (0x00000001U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_MSTAT_W                       (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TLBMISS_RMSTAT_W                      (0x00000001U)

#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_MASK                    (0x00000010U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_SHIFT                   (4U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_RESETVAL                (0x00000000U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_NMHF_R                  (0x00000000U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_MHF_R                   (0x00000001U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_MHFSTAT_W               (0x00000000U)
#define CSL_IPUMMU_IRQSTS_MULTIHITFAULT_RMHFSTAT_W              (0x00000001U)

#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_MASK                 (0x00000002U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_SHIFT                (1U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_RESETVAL             (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_NFAULT_R             (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_FAULT_R              (0x00000001U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_FSTAT_W              (0x00000000U)
#define CSL_IPUMMU_IRQSTS_TRANSLATIONFAULT_RFSTAT_W             (0x00000001U)

#define CSL_IPUMMU_IRQSTS_EMUMISS_MASK                          (0x00000004U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_SHIFT                         (2U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_RESETVAL                      (0x00000000U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_NEMUM_R                       (0x00000000U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_EMUM_R                        (0x00000001U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_ESTAT_W                       (0x00000000U)
#define CSL_IPUMMU_IRQSTS_EMUMISS_RESTAT_W                      (0x00000001U)

#define CSL_IPUMMU_IRQSTS_RESETVAL                              (0x00000000U)

/* IRQEN */

#define CSL_IPUMMU_IRQEN_TRANSLATIONFAULT_MASK                  (0x00000002U)
#define CSL_IPUMMU_IRQEN_TRANSLATIONFAULT_SHIFT                 (1U)
#define CSL_IPUMMU_IRQEN_TRANSLATIONFAULT_RESETVAL              (0x00000000U)
#define CSL_IPUMMU_IRQEN_TRANSLATIONFAULT_TRANFLTMASK           (0x00000000U)
#define CSL_IPUMMU_IRQEN_TRANSLATIONFAULT_TRANFLTGINT           (0x00000001U)

#define CSL_IPUMMU_IRQEN_TBLWALKFAULT_MASK                      (0x00000008U)
#define CSL_IPUMMU_IRQEN_TBLWALKFAULT_SHIFT                     (3U)
#define CSL_IPUMMU_IRQEN_TBLWALKFAULT_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_IRQEN_TBLWALKFAULT_TWLFLTMASK                (0x00000000U)
#define CSL_IPUMMU_IRQEN_TBLWALKFAULT_TWLFLTGINT                (0x00000001U)

#define CSL_IPUMMU_IRQEN_TLBMISS_MASK                           (0x00000001U)
#define CSL_IPUMMU_IRQEN_TLBMISS_SHIFT                          (0U)
#define CSL_IPUMMU_IRQEN_TLBMISS_RESETVAL                       (0x00000000U)
#define CSL_IPUMMU_IRQEN_TLBMISS_TRMISSINTM                     (0x00000000U)
#define CSL_IPUMMU_IRQEN_TLBMISS_TRMISSGINT                     (0x00000001U)

#define CSL_IPUMMU_IRQEN_EMUMISS_MASK                           (0x00000004U)
#define CSL_IPUMMU_IRQEN_EMUMISS_SHIFT                          (2U)
#define CSL_IPUMMU_IRQEN_EMUMISS_RESETVAL                       (0x00000000U)
#define CSL_IPUMMU_IRQEN_EMUMISS_EMUMFLTMASK                    (0x00000000U)
#define CSL_IPUMMU_IRQEN_EMUMISS_EMUMFLTGINT                    (0x00000001U)

#define CSL_IPUMMU_IRQEN_MULTIHITFAULT_MASK                     (0x00000010U)
#define CSL_IPUMMU_IRQEN_MULTIHITFAULT_SHIFT                    (4U)
#define CSL_IPUMMU_IRQEN_MULTIHITFAULT_RESETVAL                 (0x00000000U)
#define CSL_IPUMMU_IRQEN_MULTIHITFAULT_MHFLTMASK                (0x00000000U)
#define CSL_IPUMMU_IRQEN_MULTIHITFAULT_MHFLTGINT                (0x00000001U)

#define CSL_IPUMMU_IRQEN_RESETVAL                               (0x00000000U)

/* WALKING_ST */

#define CSL_IPUMMU_WALKING_ST_TWLRUNNING_MASK                   (0x00000001U)
#define CSL_IPUMMU_WALKING_ST_TWLRUNNING_SHIFT                  (0U)
#define CSL_IPUMMU_WALKING_ST_TWLRUNNING_RESETVAL               (0x00000000U)
#define CSL_IPUMMU_WALKING_ST_TWLRUNNING_TWLCOMP                (0x00000000U)
#define CSL_IPUMMU_WALKING_ST_TWLRUNNING_TWLRUN                 (0x00000001U)

#define CSL_IPUMMU_WALKING_ST_RESETVAL                          (0x00000000U)

/* CNTL */

#define CSL_IPUMMU_CNTL_MMUEN_MASK                              (0x00000002U)
#define CSL_IPUMMU_CNTL_MMUEN_SHIFT                             (1U)
#define CSL_IPUMMU_CNTL_MMUEN_RESETVAL                          (0x00000000U)
#define CSL_IPUMMU_CNTL_MMUEN_MMUDIS                            (0x00000000U)
#define CSL_IPUMMU_CNTL_MMUEN_MMUEN                             (0x00000001U)

#define CSL_IPUMMU_CNTL_EMUTLBUPDATE_MASK                       (0x00000008U)
#define CSL_IPUMMU_CNTL_EMUTLBUPDATE_SHIFT                      (3U)
#define CSL_IPUMMU_CNTL_EMUTLBUPDATE_RESETVAL                   (0x00000000U)
#define CSL_IPUMMU_CNTL_EMUTLBUPDATE_EMUDIS                     (0x00000000U)
#define CSL_IPUMMU_CNTL_EMUTLBUPDATE_EMUEN                      (0x00000001U)

#define CSL_IPUMMU_CNTL_TWLEN_MASK                              (0x00000004U)
#define CSL_IPUMMU_CNTL_TWLEN_SHIFT                             (2U)
#define CSL_IPUMMU_CNTL_TWLEN_RESETVAL                          (0x00000000U)
#define CSL_IPUMMU_CNTL_TWLEN_TWLDIS                            (0x00000000U)
#define CSL_IPUMMU_CNTL_TWLEN_TWLEN                             (0x00000001U)

#define CSL_IPUMMU_CNTL_RESETVAL                                (0x00000000U)

/* FAULT_AD */

#define CSL_IPUMMU_FAULT_AD_FAULTADDR_MASK                      (0xFFFFFFFFU)
#define CSL_IPUMMU_FAULT_AD_FAULTADDR_SHIFT                     (0U)
#define CSL_IPUMMU_FAULT_AD_FAULTADDR_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_FAULT_AD_FAULTADDR_MAX                       (0xffffffffU)

#define CSL_IPUMMU_FAULT_AD_RESETVAL                            (0x00000000U)

/* TTB */

#define CSL_IPUMMU_TTB_TTBADDR_MASK                             (0xFFFFFF80U)
#define CSL_IPUMMU_TTB_TTBADDR_SHIFT                            (7U)
#define CSL_IPUMMU_TTB_TTBADDR_RESETVAL                         (0x00000000U)
#define CSL_IPUMMU_TTB_TTBADDR_MAX                              (0x01ffffffU)

#define CSL_IPUMMU_TTB_RESETVAL                                 (0x00000000U)

/* LOCK */

#define CSL_IPUMMU_LOCK_BASEVALUE_MASK                          (0x00007C00U)
#define CSL_IPUMMU_LOCK_BASEVALUE_SHIFT                         (10U)
#define CSL_IPUMMU_LOCK_BASEVALUE_RESETVAL                      (0x00000000U)
#define CSL_IPUMMU_LOCK_BASEVALUE_MAX                           (0x0000001fU)

#define CSL_IPUMMU_LOCK_CURRENTVICTIM_MASK                      (0x000001F0U)
#define CSL_IPUMMU_LOCK_CURRENTVICTIM_SHIFT                     (4U)
#define CSL_IPUMMU_LOCK_CURRENTVICTIM_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_LOCK_CURRENTVICTIM_MAX                       (0x0000001fU)

#define CSL_IPUMMU_LOCK_RESETVAL                                (0x00000000U)

/* LD_TLB */

#define CSL_IPUMMU_LD_TLB_LDTLBITEM_MASK                        (0x00000001U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_SHIFT                       (0U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_RESETVAL                    (0x00000000U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_ALWAYS_R                    (0x00000000U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_NEVER_R                     (0x00000001U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_NOEFFECT_W                  (0x00000000U)
#define CSL_IPUMMU_LD_TLB_LDTLBITEM_LDTLB_W                     (0x00000001U)

#define CSL_IPUMMU_LD_TLB_RESETVAL                              (0x00000000U)

/* CAM */

#define CSL_IPUMMU_CAM_V_MASK                                   (0x00000004U)
#define CSL_IPUMMU_CAM_V_SHIFT                                  (2U)
#define CSL_IPUMMU_CAM_V_RESETVAL                               (0x00000000U)
#define CSL_IPUMMU_CAM_V_INVALID                                (0x00000000U)
#define CSL_IPUMMU_CAM_V_VALID                                  (0x00000001U)

#define CSL_IPUMMU_CAM_VATAG_MASK                               (0xFFFFF000U)
#define CSL_IPUMMU_CAM_VATAG_SHIFT                              (12U)
#define CSL_IPUMMU_CAM_VATAG_RESETVAL                           (0x00000000U)
#define CSL_IPUMMU_CAM_VATAG_MAX                                (0x000fffffU)

#define CSL_IPUMMU_CAM_PAGESIZE_MASK                            (0x00000003U)
#define CSL_IPUMMU_CAM_PAGESIZE_SHIFT                           (0U)
#define CSL_IPUMMU_CAM_PAGESIZE_RESETVAL                        (0x00000000U)
#define CSL_IPUMMU_CAM_PAGESIZE_SECTION                         (0x00000000U)
#define CSL_IPUMMU_CAM_PAGESIZE_LARGE                           (0x00000001U)
#define CSL_IPUMMU_CAM_PAGESIZE_SMALL                           (0x00000002U)
#define CSL_IPUMMU_CAM_PAGESIZE_SUPER                           (0x00000003U)

#define CSL_IPUMMU_CAM_P_MASK                                   (0x00000008U)
#define CSL_IPUMMU_CAM_P_SHIFT                                  (3U)
#define CSL_IPUMMU_CAM_P_RESETVAL                               (0x00000000U)
#define CSL_IPUMMU_CAM_P_CANFLUSH                               (0x00000000U)
#define CSL_IPUMMU_CAM_P_NOFLUSH                                (0x00000001U)

#define CSL_IPUMMU_CAM_RESETVAL                                 (0x00000000U)

/* RAM */

#define CSL_IPUMMU_RAM_PHYSICALADDR_MASK                        (0xFFFFF000U)
#define CSL_IPUMMU_RAM_PHYSICALADDR_SHIFT                       (12U)
#define CSL_IPUMMU_RAM_PHYSICALADDR_RESETVAL                    (0x00000000U)
#define CSL_IPUMMU_RAM_PHYSICALADDR_MAX                         (0x000fffffU)

#define CSL_IPUMMU_RAM_ENDIAN_MASK                              (0x00000200U)
#define CSL_IPUMMU_RAM_ENDIAN_SHIFT                             (9U)
#define CSL_IPUMMU_RAM_ENDIAN_RESETVAL                          (0x00000000U)
#define CSL_IPUMMU_RAM_ENDIAN_LITTLE                            (0x00000000U)
#define CSL_IPUMMU_RAM_ENDIAN_BIG                               (0x00000001U)

#define CSL_IPUMMU_RAM_MIXED_MASK                               (0x00000040U)
#define CSL_IPUMMU_RAM_MIXED_SHIFT                              (6U)
#define CSL_IPUMMU_RAM_MIXED_RESETVAL                           (0x00000000U)
#define CSL_IPUMMU_RAM_MIXED_TLBES                              (0x00000000U)
#define CSL_IPUMMU_RAM_MIXED_CPUES                              (0x00000001U)

#define CSL_IPUMMU_RAM_ELEMENTSIZE_MASK                         (0x00000180U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_SHIFT                        (7U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_RESETVAL                     (0x00000000U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_BYTE                         (0x00000000U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_SHORT                        (0x00000001U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_LONG                         (0x00000002U)
#define CSL_IPUMMU_RAM_ELEMENTSIZE_NONE                         (0x00000003U)

#define CSL_IPUMMU_RAM_RESETVAL                                 (0x00000000U)

/* GFLUSH */

#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_MASK                      (0x00000001U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_SHIFT                     (0U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_RTN0_R                    (0x00000000U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_NEVER_R                   (0x00000001U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_NFT_W                     (0x00000000U)
#define CSL_IPUMMU_GFLUSH_GLOBALFLUSH_FLUSH_W                   (0x00000001U)

#define CSL_IPUMMU_GFLUSH_RESETVAL                              (0x00000000U)

/* FLUSH_ENTRY */

#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_MASK                  (0x00000001U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_SHIFT                 (0U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_RESETVAL              (0x00000000U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_ALWAYS_R              (0x00000000U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_NEVER_R               (0x00000001U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_NOFUN_W               (0x00000000U)
#define CSL_IPUMMU_FLUSH_ENTRY_FLUSHENTRY_FLUSHTLB_W            (0x00000001U)

#define CSL_IPUMMU_FLUSH_ENTRY_RESETVAL                         (0x00000000U)

/* READ_CAM */

#define CSL_IPUMMU_READ_CAM_PAGESIZE_MASK                       (0x00000003U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_SHIFT                      (0U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_RESETVAL                   (0x00000000U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_SECTION                    (0x00000000U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_LARGE                      (0x00000001U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_SMALL                      (0x00000002U)
#define CSL_IPUMMU_READ_CAM_PAGESIZE_SUPER                      (0x00000003U)

#define CSL_IPUMMU_READ_CAM_P_MASK                              (0x00000008U)
#define CSL_IPUMMU_READ_CAM_P_SHIFT                             (3U)
#define CSL_IPUMMU_READ_CAM_P_RESETVAL                          (0x00000000U)
#define CSL_IPUMMU_READ_CAM_P_CANFLUSH                          (0x00000000U)
#define CSL_IPUMMU_READ_CAM_P_NOFLUSH                           (0x00000001U)

#define CSL_IPUMMU_READ_CAM_V_MASK                              (0x00000004U)
#define CSL_IPUMMU_READ_CAM_V_SHIFT                             (2U)
#define CSL_IPUMMU_READ_CAM_V_RESETVAL                          (0x00000000U)
#define CSL_IPUMMU_READ_CAM_V_INVALID                           (0x00000000U)
#define CSL_IPUMMU_READ_CAM_V_VALID                             (0x00000001U)

#define CSL_IPUMMU_READ_CAM_VATAG_MASK                          (0xFFFFF000U)
#define CSL_IPUMMU_READ_CAM_VATAG_SHIFT                         (12U)
#define CSL_IPUMMU_READ_CAM_VATAG_RESETVAL                      (0x00000000U)
#define CSL_IPUMMU_READ_CAM_VATAG_MAX                           (0x000fffffU)

#define CSL_IPUMMU_READ_CAM_RESETVAL                            (0x00000000U)

/* READ_RAM */

#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_MASK                    (0x00000180U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_SHIFT                   (7U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_RESETVAL                (0x00000000U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_BYTE                    (0x00000000U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_SHORT                   (0x00000001U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_LONG                    (0x00000002U)
#define CSL_IPUMMU_READ_RAM_ELEMENTSIZE_NONE                    (0x00000003U)

#define CSL_IPUMMU_READ_RAM_PHYSICALADDR_MASK                   (0xFFFFF000U)
#define CSL_IPUMMU_READ_RAM_PHYSICALADDR_SHIFT                  (12U)
#define CSL_IPUMMU_READ_RAM_PHYSICALADDR_RESETVAL               (0x00000000U)
#define CSL_IPUMMU_READ_RAM_PHYSICALADDR_MAX                    (0x000fffffU)

#define CSL_IPUMMU_READ_RAM_ENDIAN_MASK                         (0x00000200U)
#define CSL_IPUMMU_READ_RAM_ENDIAN_SHIFT                        (9U)
#define CSL_IPUMMU_READ_RAM_ENDIAN_RESETVAL                     (0x00000000U)
#define CSL_IPUMMU_READ_RAM_ENDIAN_LITTLE                       (0x00000000U)
#define CSL_IPUMMU_READ_RAM_ENDIAN_BIG                          (0x00000001U)

#define CSL_IPUMMU_READ_RAM_MIXED_MASK                          (0x00000040U)
#define CSL_IPUMMU_READ_RAM_MIXED_SHIFT                         (6U)
#define CSL_IPUMMU_READ_RAM_MIXED_RESETVAL                      (0x00000000U)
#define CSL_IPUMMU_READ_RAM_MIXED_TLBES                         (0x00000000U)
#define CSL_IPUMMU_READ_RAM_MIXED_CPUES                         (0x00000001U)

#define CSL_IPUMMU_READ_RAM_RESETVAL                            (0x00000000U)

/* EMU_FAULT_AD */

#define CSL_IPUMMU_EMU_FAULT_AD_EMUFAULTADDR_MASK               (0xFFFFFFFFU)
#define CSL_IPUMMU_EMU_FAULT_AD_EMUFAULTADDR_SHIFT              (0U)
#define CSL_IPUMMU_EMU_FAULT_AD_EMUFAULTADDR_RESETVAL           (0x00000000U)
#define CSL_IPUMMU_EMU_FAULT_AD_EMUFAULTADDR_MAX                (0xffffffffU)

#define CSL_IPUMMU_EMU_FAULT_AD_RESETVAL                        (0x00000000U)

/* FAULT_PC */

#define CSL_IPUMMU_FAULT_PC_PC_MASK                             (0xFFFFFFFFU)
#define CSL_IPUMMU_FAULT_PC_PC_SHIFT                            (0U)
#define CSL_IPUMMU_FAULT_PC_PC_RESETVAL                         (0x00000000U)
#define CSL_IPUMMU_FAULT_PC_PC_MAX                              (0xffffffffU)

#define CSL_IPUMMU_FAULT_PC_RESETVAL                            (0x00000000U)

/* FAULT_STS */

#define CSL_IPUMMU_FAULT_STS_FAULTINDICATION_MASK               (0x00000001U)
#define CSL_IPUMMU_FAULT_STS_FAULTINDICATION_SHIFT              (0U)
#define CSL_IPUMMU_FAULT_STS_FAULTINDICATION_RESETVAL           (0x00000000U)
#define CSL_IPUMMU_FAULT_STS_FAULTINDICATION_MAX                (0x00000001U)

#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_MASK                (0x00000006U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_SHIFT               (1U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_RESETVAL            (0x00000000U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_LD_ST               (0x00000000U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_FETCH               (0x00000001U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TYPE_DMA                 (0x00000002U)

#define CSL_IPUMMU_FAULT_STS_RD_WR_MASK                         (0x00000008U)
#define CSL_IPUMMU_FAULT_STS_RD_WR_SHIFT                        (3U)
#define CSL_IPUMMU_FAULT_STS_RD_WR_RESETVAL                     (0x00000000U)
#define CSL_IPUMMU_FAULT_STS_RD_WR_MAX                          (0x00000001U)

#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TRANS_ID_MASK            (0x000000F0U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TRANS_ID_SHIFT           (4U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TRANS_ID_RESETVAL        (0x00000000U)
#define CSL_IPUMMU_FAULT_STS_MMU_FAULT_TRANS_ID_MAX             (0x0000000fU)

#define CSL_IPUMMU_FAULT_STS_RESETVAL                           (0x00000000U)

/* GPR */

#define CSL_IPUMMU_GPR_HWDBG_MUX_MASK                           (0x0000000FU)
#define CSL_IPUMMU_GPR_HWDBG_MUX_SHIFT                          (0U)
#define CSL_IPUMMU_GPR_HWDBG_MUX_RESETVAL                       (0x00000000U)
#define CSL_IPUMMU_GPR_HWDBG_MUX_MAX                            (0x0000000fU)

#define CSL_IPUMMU_GPR_FORCE_IDLE_REQ_MASK                      (0x00008000U)
#define CSL_IPUMMU_GPR_FORCE_IDLE_REQ_SHIFT                     (15U)
#define CSL_IPUMMU_GPR_FORCE_IDLE_REQ_RESETVAL                  (0x00000000U)
#define CSL_IPUMMU_GPR_FORCE_IDLE_REQ_MAX                       (0x00000001U)

#define CSL_IPUMMU_GPR_RESETVAL                                 (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
