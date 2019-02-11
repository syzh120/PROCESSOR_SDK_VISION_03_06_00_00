/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

#ifndef HW_EVE_CONTROL_H_
#define HW_EVE_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define EVE_REVISION                                                                                        (0x0U)
#define EVE_HWINFO                                                                                          (0x4U)
#define EVE_SYSCONFIG                                                                                       (0x8U)
#define EVE_STAT                                                                                            (0xcU)
#define EVE_DISC_CONFIG                                                                                     (0x10U)
#define EVE_BUS_CONFIG                                                                                      (0x14U)
#define EVE_VCOP_HALT_CONFIG                                                                                (0x18U)
#define EVE_MMU_CONFIG                                                                                      (0x1cU)
#define EVE_MEMMAP                                                                                          (0x20U)
#define EVE_MSW_CTL                                                                                         (0x24U)
#define EVE_MSW_ERR                                                                                         (0x28U)
#define EVE_MSW_ERRADDR                                                                                     (0x2cU)
#define EVE_PC_INV                                                                                          (0x40U)
#define EVE_PC_IBAR                                                                                         (0x50U)
#define EVE_PC_IBC                                                                                          (0x54U)
#define EVE_PC_ISAR                                                                                         (0x58U)
#define EVE_PC_ISAR_DONE                                                                                    (0x5cU)
#define EVE_PC_PBAR                                                                                         (0x60U)
#define EVE_PC_PBC                                                                                          (0x64U)
#define EVE_PMEM_ED_CTL                                                                                     (0x80U)
#define EVE_PMEM_ED_STAT                                                                                    (0x84U)
#define EVE_PMEM_EDADDR                                                                                     (0x88U)
#define EVE_DMEM_ED_CTL                                                                                     (0x90U)
#define EVE_DMEM_ED_STAT                                                                                    (0x94U)
#define EVE_DMEM_EDADDR                                                                                     (0x98U)
#define EVE_DMEM_EDADDR_BO                                                                                  (0x9cU)
#define EVE_WBUF_ED_CTL                                                                                     (0xa0U)
#define EVE_WBUF_ED_STAT                                                                                    (0xa4U)
#define EVE_WBUF_EDADDR                                                                                     (0xa8U)
#define EVE_WBUF_EDADDR_BO                                                                                  (0xacU)
#define EVE_IBUF_ED_CTL                                                                                     (0xb0U)
#define EVE_IBUF_ED_STAT                                                                                    (0xb4U)
#define EVE_IBUF_EDADDR                                                                                     (0xb8U)
#define EVE_IBUF_EDADDR_BO                                                                                  (0xbcU)
#define EVE_ED_ARP32_DISC_EN                                                                                (0xf8U)
#define EVE_ED_OCPI_DISC_EN                                                                                 (0xfcU)
#define EVE_MSW_ERR_IRQSTATUS_RAW                                                                           (0x110U)
#define EVE_MSW_ERR_IRQSTATUS                                                                               (0x114U)
#define EVE_MSW_ERR_IRQENABLE_SET                                                                           (0x118U)
#define EVE_MSW_ERR_IRQENABLE_CLR                                                                           (0x11cU)
#define EVE_ED_LCL_IRQSTATUS_RAW                                                                            (0x120U)
#define EVE_ED_LCL_IRQSTATUS                                                                                (0x124U)
#define EVE_ED_LCL_IRQENABLE_SET                                                                            (0x128U)
#define EVE_ED_LCL_IRQENABLE_CLR                                                                            (0x12cU)
#define EVE_ARP32_NMI_IRQSTATUS_RAW                                                                         (0x200U)
#define EVE_ARP32_NMI_IRQSTATUS                                                                             (0x204U)
#define EVE_ARP32_NMI_IRQENABLE_SET                                                                         (0x208U)
#define EVE_ARP32_NMI_IRQENABLE_CLR                                                                         (0x20cU)
#define EVE_ARP32_INT4_IRQSTATUS_RAW                                                                        (0x210U)
#define EVE_ARP32_INT4_IRQSTATUS                                                                            (0x214U)
#define EVE_ARP32_INT4_IRQENABLE_SET                                                                        (0x218U)
#define EVE_ARP32_INT4_IRQENABLE_CLR                                                                        (0x21cU)
#define EVE_ARP32_INT5_IRQSTATUS_RAW                                                                        (0x220U)
#define EVE_ARP32_INT5_IRQSTATUS                                                                            (0x224U)
#define EVE_ARP32_INT5_IRQENABLE_SET                                                                        (0x228U)
#define EVE_ARP32_INT5_IRQENABLE_CLR                                                                        (0x22cU)
#define EVE_ARP32_INT6_IRQSTATUS_RAW                                                                        (0x230U)
#define EVE_ARP32_INT6_IRQSTATUS                                                                            (0x234U)
#define EVE_ARP32_INT6_IRQENABLE_SET                                                                        (0x238U)
#define EVE_ARP32_INT6_IRQENABLE_CLR                                                                        (0x23cU)
#define EVE_ARP32_INT7_IRQSTATUS_RAW                                                                        (0x240U)
#define EVE_ARP32_INT7_IRQSTATUS                                                                            (0x244U)
#define EVE_ARP32_INT7_IRQENABLE_SET                                                                        (0x248U)
#define EVE_ARP32_INT7_IRQENABLE_CLR                                                                        (0x24cU)
#define EVE_ARP32_IRQWAKEEN                                                                                 (0x2fcU)
#define MMR_LOCK_0                                                                                          (0x300U)
#define MMR_LOCK_1                                                                                          (0x304U)
#define MMR_LOCK_2                                                                                          (0x308U)
#define MMR_LOCK_3                                                                                          (0x30cU)
#define MMR_LOCK_4                                                                                          (0x310U)
#define MMR_LOCK_5                                                                                          (0x314U)
#define MMR_LOCK_6                                                                                          (0x318U)
#define MMR_LOCK_7                                                                                          (0x31cU)
#define MMR_LOCK_8                                                                                          (0x320U)
#define MMR_LOCK_9                                                                                          (0x324U)
#define EVE_MISR_CTL                                                                                        (0x400U)
#define EVE_MISR_CLEAR                                                                                      (0x404U)
#define EVE_MISR0_A                                                                                         (0x410U)
#define EVE_MISR0_D                                                                                         (0x414U)
#define EVE_MISR1_A                                                                                         (0x418U)
#define EVE_MISR1_D                                                                                         (0x41cU)
#define EVE_MISR2_D0                                                                                        (0x420U)
#define EVE_MISR2_D1                                                                                        (0x424U)
#define EVE_MISR2_D2                                                                                        (0x428U)
#define EVE_MISR2_D3                                                                                        (0x42cU)
#define EVE_IRQ_EOI                                                                                         (0x500U)
#define EVE_ED_OUT_IRQSTATUS_RAW                                                                            (0x510U)
#define EVE_ED_OUT_IRQSTATUS                                                                                (0x514U)
#define EVE_ED_OUT_IRQENABLE_SET                                                                            (0x518U)
#define EVE_ED_OUT_IRQENABLE_CLR                                                                            (0x51cU)
#define EVE_INT0_OUT_IRQSTATUS_RAW                                                                          (0x520U)
#define EVE_INT0_OUT_IRQSTATUS                                                                              (0x524U)
#define EVE_INT0_OUT_IRQENABLE_SET                                                                          (0x528U)
#define EVE_INT0_OUT_IRQENABLE_CLR                                                                          (0x52cU)
#define EVE_INT1_OUT_IRQSTATUS_RAW                                                                          (0x530U)
#define EVE_INT1_OUT_IRQSTATUS                                                                              (0x534U)
#define EVE_INT1_OUT_IRQENABLE_SET                                                                          (0x538U)
#define EVE_INT1_OUT_IRQENABLE_CLR                                                                          (0x53cU)
#define EVE_INT2_OUT_IRQSTATUS_RAW                                                                          (0x540U)
#define EVE_INT2_OUT_IRQSTATUS                                                                              (0x544U)
#define EVE_INT2_OUT_IRQENABLE_SET                                                                          (0x548U)
#define EVE_INT2_OUT_IRQENABLE_CLR                                                                          (0x54cU)
#define EVE_INT3_OUT_IRQSTATUS_RAW                                                                          (0x550U)
#define EVE_INT3_OUT_IRQSTATUS                                                                              (0x554U)
#define EVE_INT3_OUT_IRQENABLE_SET                                                                          (0x558U)
#define EVE_INT3_OUT_IRQENABLE_CLR                                                                          (0x55cU)
#define EVE_GPOUT0                                                                                          (0x700U)
#define EVE_GPOUT0_SET                                                                                      (0x704U)
#define EVE_GPOUT0_CLR                                                                                      (0x708U)
#define EVE_GPOUT0_PULSE                                                                                    (0x70cU)
#define EVE_GPOUT1                                                                                          (0x710U)
#define EVE_GPOUT1_SET                                                                                      (0x714U)
#define EVE_GPOUT1_CLR                                                                                      (0x718U)
#define EVE_GPOUT1_PULSE                                                                                    (0x71cU)
#define EVE_ARP32_INT8_IRQSTATUS_RAW                                                                        (0x600U)
#define EVE_ARP32_INT8_IRQSTATUS                                                                            (0x604U)
#define EVE_ARP32_INT8_IRQENABLE_SET                                                                        (0x608U)
#define EVE_ARP32_INT8_IRQENABLE_CLR                                                                        (0x60cU)
#define EVE_ARP32_INT9_IRQSTATUS_RAW                                                                        (0x610U)
#define EVE_ARP32_INT9_IRQSTATUS                                                                            (0x614U)
#define EVE_ARP32_INT9_IRQENABLE_SET                                                                        (0x618U)
#define EVE_ARP32_INT9_IRQENABLE_CLR                                                                        (0x61cU)
#define EVE_ARP32_INT10_IRQSTATUS_RAW                                                                       (0x620U)
#define EVE_ARP32_INT10_IRQSTATUS                                                                           (0x624U)
#define EVE_ARP32_INT10_IRQENABLE_SET                                                                       (0x628U)
#define EVE_ARP32_INT10_IRQENABLE_CLR                                                                       (0x62cU)
#define EVE_ARP32_INT11_IRQSTATUS_RAW                                                                       (0x630U)
#define EVE_ARP32_INT11_IRQSTATUS                                                                           (0x634U)
#define EVE_ARP32_INT11_IRQENABLE_SET                                                                       (0x638U)
#define EVE_ARP32_INT11_IRQENABLE_CLR                                                                       (0x63cU)
#define EVE_ARP32_INT12_IRQSTATUS_RAW                                                                       (0x640U)
#define EVE_ARP32_INT12_IRQSTATUS                                                                           (0x644U)
#define EVE_ARP32_INT12_IRQENABLE_SET                                                                       (0x648U)
#define EVE_ARP32_INT12_IRQENABLE_CLR                                                                       (0x64cU)
#define EVE_ARP32_INT13_IRQSTATUS_RAW                                                                       (0x650U)
#define EVE_ARP32_INT13_IRQSTATUS                                                                           (0x654U)
#define EVE_ARP32_INT13_IRQENABLE_SET                                                                       (0x658U)
#define EVE_ARP32_INT13_IRQENABLE_CLR                                                                       (0x65cU)
#define EVE_ARP32_INT14_IRQSTATUS_RAW                                                                       (0x680U)
#define EVE_ARP32_INT14_IRQSTATUS                                                                           (0x684U)
#define EVE_ARP32_INT14_IRQENABLE_SET                                                                       (0x688U)
#define EVE_ARP32_INT14_IRQENABLE_CLR                                                                       (0x68cU)
#define EVE_ARP32_INT15_IRQSTATUS_RAW                                                                       (0x690U)
#define EVE_ARP32_INT15_IRQSTATUS                                                                           (0x694U)
#define EVE_ARP32_INT15_IRQENABLE_SET                                                                       (0x698U)
#define EVE_ARP32_INT15_IRQENABLE_CLR                                                                       (0x69cU)
#define EVE_GPIN0                                                                                           (0x740U)
#define EVE_GPIN1                                                                                           (0x744U)
#define EVE_CME_DONE_GPOUT                                                                                  (0x780U)
#define EVE_CME_DONE_GPOUT_SET                                                                              (0x784U)
#define EVE_CME_DONE_GPOUT_CLR                                                                              (0x788U)
#define EVE_CME_DONE_GPOUT_PULSE                                                                            (0x78cU)
#define EVE_CME_DONE_SEL                                                                                    (0x790U)
#define EVE_CME_DONE_EN                                                                                     (0x794U)
#define EVE_PM_STAT0                                                                                        (0xfe0U)
#define EVE_PM_STAT1                                                                                        (0xfe4U)
#define EVE_DBGOUT                                                                                          (0xfe8U)
#define EVE_RSVD0                                                                                           (0xff4U)
#define EVE_RSVD1                                                                                           (0xff8U)
#define EVE_TEST                                                                                            (0xffcU)
#define EVE_MMR_LOCK(n)                                                                                     (0x300U + ((n) * 4))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define EVE_REVISION_REVISION_SHIFT                                                                         (0U)
#define EVE_REVISION_REVISION_MASK                                                                          (0xffffffffU)

#define EVE_HWINFO_EVENUM_SHIFT                                                                             (0U)
#define EVE_HWINFO_EVENUM_MASK                                                                              (0x0000000fU)

#define EVE_HWINFO_INFO_SHIFT                                                                               (4U)
#define EVE_HWINFO_INFO_MASK                                                                                (0xfffffff0U)

#define EVE_SYSCONFIG_SOFTRESET_SHIFT                                                                       (0U)
#define EVE_SYSCONFIG_SOFTRESET_MASK                                                                        (0x00000001U)

#define EVE_SYSCONFIG_FREEEMU_SHIFT                                                                         (1U)
#define EVE_SYSCONFIG_FREEEMU_MASK                                                                          (0x00000002U)

#define EVE_SYSCONFIG_IDLEMODE_SHIFT                                                                        (2U)
#define EVE_SYSCONFIG_IDLEMODE_MASK                                                                         (0x0000000cU)

#define EVE_SYSCONFIG_STANDBYMODE_SHIFT                                                                     (4U)
#define EVE_SYSCONFIG_STANDBYMODE_MASK                                                                      (0x00000030U)

#define EVE_SYSCONFIG_RESERVED_SHIFT                                                                        (6U)
#define EVE_SYSCONFIG_RESERVED_MASK                                                                         (0xffffffc0U)

#define EVE_STAT_ARP32_STAT_SHIFT                                                                           (0U)
#define EVE_STAT_ARP32_STAT_MASK                                                                            (0x00000001U)

#define EVE_STAT_VCOP_STAT_SHIFT                                                                            (1U)
#define EVE_STAT_VCOP_STAT_MASK                                                                             (0x00000002U)

#define EVE_STAT_PC_STAT_SHIFT                                                                              (2U)
#define EVE_STAT_PC_STAT_MASK                                                                               (0x00000004U)

#define EVE_STAT_TC0_STAT_SHIFT                                                                             (4U)
#define EVE_STAT_TC0_STAT_MASK                                                                              (0x00000010U)

#define EVE_STAT_TC1_STAT_SHIFT                                                                             (5U)
#define EVE_STAT_TC1_STAT_MASK                                                                              (0x00000020U)

#define EVE_STAT_INT_OUT_STAT_SHIFT                                                                         (8U)
#define EVE_STAT_INT_OUT_STAT_MASK                                                                          (0x00000100U)

#define EVE_STAT_ARP32_DISC_STATUS_SHIFT                                                                    (16U)
#define EVE_STAT_ARP32_DISC_STATUS_MASK                                                                     (0x00030000U)

#define EVE_STAT_OCPI_DISC_STAT_SHIFT                                                                       (20U)
#define EVE_STAT_OCPI_DISC_STAT_MASK                                                                        (0x00300000U)

#define EVE_STAT_RESERVED_SHIFT                                                                             (3U)
#define EVE_STAT_RESERVED_MASK                                                                              (0x00000008U)

#define EVE_STAT_RESERVED1_SHIFT                                                                            (6U)
#define EVE_STAT_RESERVED1_MASK                                                                             (0x00000040U)

#define EVE_STAT_RESERVED2_SHIFT                                                                            (9U)
#define EVE_STAT_RESERVED2_MASK                                                                             (0x0000fe00U)

#define EVE_STAT_RESERVED3_SHIFT                                                                            (18U)
#define EVE_STAT_RESERVED3_MASK                                                                             (0x000c0000U)

#define EVE_STAT_RESERVED4_SHIFT                                                                            (22U)
#define EVE_STAT_RESERVED4_MASK                                                                             (0xffc00000U)

#define EVE_STAT_ARP_INTC_STAT_SHIFT                                                                        (7U)
#define EVE_STAT_ARP_INTC_STAT_MASK                                                                         (0x00000080U)

#define EVE_DISC_CONFIG_ARP32_DISC_SHIFT                                                                    (0U)
#define EVE_DISC_CONFIG_ARP32_DISC_MASK                                                                     (0x00000001U)

#define EVE_DISC_CONFIG_OCPI_DISC_SHIFT                                                                     (4U)
#define EVE_DISC_CONFIG_OCPI_DISC_MASK                                                                      (0x00000010U)

#define EVE_DISC_CONFIG_RESERVED_SHIFT                                                                      (1U)
#define EVE_DISC_CONFIG_RESERVED_MASK                                                                       (0x0000000eU)

#define EVE_DISC_CONFIG_RESERVED1_SHIFT                                                                     (5U)
#define EVE_DISC_CONFIG_RESERVED1_MASK                                                                      (0xffffffe0U)

#define EVE_BUS_CONFIG_MAX_IN_FLIGHT_SHIFT                                                                  (0U)
#define EVE_BUS_CONFIG_MAX_IN_FLIGHT_MASK                                                                   (0x0000000fU)

#define EVE_BUS_CONFIG_DBP_ENABLE_SHIFT                                                                     (4U)
#define EVE_BUS_CONFIG_DBP_ENABLE_MASK                                                                      (0x00000010U)

#define EVE_BUS_CONFIG_TC0_DBS_SHIFT                                                                        (8U)
#define EVE_BUS_CONFIG_TC0_DBS_MASK                                                                         (0x00000300U)

#define EVE_BUS_CONFIG_TC1_DBS_SHIFT                                                                        (12U)
#define EVE_BUS_CONFIG_TC1_DBS_MASK                                                                         (0x00003000U)

#define EVE_BUS_CONFIG_RESERVED_SHIFT                                                                       (5U)
#define EVE_BUS_CONFIG_RESERVED_MASK                                                                        (0x000000e0U)

#define EVE_BUS_CONFIG_RESERVED1_SHIFT                                                                      (10U)
#define EVE_BUS_CONFIG_RESERVED1_MASK                                                                       (0x00000c00U)

#define EVE_BUS_CONFIG_RESERVED2_SHIFT                                                                      (14U)
#define EVE_BUS_CONFIG_RESERVED2_MASK                                                                       (0xffffc000U)

#define EVE_VCOP_HALT_CONFIG_ED_EN_SHIFT                                                                    (0U)
#define EVE_VCOP_HALT_CONFIG_ED_EN_MASK                                                                     (0x00000001U)

#define EVE_VCOP_HALT_CONFIG_MSW_EN_SHIFT                                                                   (1U)
#define EVE_VCOP_HALT_CONFIG_MSW_EN_MASK                                                                    (0x00000002U)

#define EVE_VCOP_HALT_CONFIG_FORCE_ABORT_SHIFT                                                              (2U)
#define EVE_VCOP_HALT_CONFIG_FORCE_ABORT_MASK                                                               (0x00000004U)

#define EVE_VCOP_HALT_CONFIG_RESERVED_SHIFT                                                                 (3U)
#define EVE_VCOP_HALT_CONFIG_RESERVED_MASK                                                                  (0xfffffff8U)

#define EVE_MMU_CONFIG_MMU0_EN_SHIFT                                                                        (0U)
#define EVE_MMU_CONFIG_MMU0_EN_MASK                                                                         (0x00000001U)

#define EVE_MMU_CONFIG_MMU1_EN_SHIFT                                                                        (4U)
#define EVE_MMU_CONFIG_MMU1_EN_MASK                                                                         (0x00000010U)

#define EVE_MMU_CONFIG_MMU0_ABORT_SHIFT                                                                     (8U)
#define EVE_MMU_CONFIG_MMU0_ABORT_MASK                                                                      (0x00000100U)

#define EVE_MMU_CONFIG_MMU1_ABORT_SHIFT                                                                     (12U)
#define EVE_MMU_CONFIG_MMU1_ABORT_MASK                                                                      (0x00001000U)

#define EVE_MMU_CONFIG_RESERVED_SHIFT                                                                       (1U)
#define EVE_MMU_CONFIG_RESERVED_MASK                                                                        (0x0000000eU)

#define EVE_MMU_CONFIG_RESERVED1_SHIFT                                                                      (5U)
#define EVE_MMU_CONFIG_RESERVED1_MASK                                                                       (0x000000e0U)

#define EVE_MMU_CONFIG_RESERVED2_SHIFT                                                                      (9U)
#define EVE_MMU_CONFIG_RESERVED2_MASK                                                                       (0x00000e00U)

#define EVE_MMU_CONFIG_RESERVED3_SHIFT                                                                      (13U)
#define EVE_MMU_CONFIG_RESERVED3_MASK                                                                       (0xffffe000U)

#define EVE_MEMMAP_VCOP_ALIAS_SHIFT                                                                         (0U)
#define EVE_MEMMAP_VCOP_ALIAS_MASK                                                                          (0x00000001U)

#define EVE_MEMMAP_LCL_EDMA_ALIAS_SHIFT                                                                     (4U)
#define EVE_MEMMAP_LCL_EDMA_ALIAS_MASK                                                                      (0x00000010U)

#define EVE_MEMMAP_RESERVED_SHIFT                                                                           (1U)
#define EVE_MEMMAP_RESERVED_MASK                                                                            (0x0000000eU)

#define EVE_MEMMAP_RESERVED1_SHIFT                                                                          (5U)
#define EVE_MEMMAP_RESERVED1_MASK                                                                           (0xffffffe0U)

#define EVE_MSW_CTL_IBUFLA_SHIFT                                                                            (0U)
#define EVE_MSW_CTL_IBUFLA_MASK                                                                             (0x00000001U)

#define EVE_MSW_CTL_IBUFHA_SHIFT                                                                            (4U)
#define EVE_MSW_CTL_IBUFHA_MASK                                                                             (0x00000010U)

#define EVE_MSW_CTL_IBUFLB_SHIFT                                                                            (8U)
#define EVE_MSW_CTL_IBUFLB_MASK                                                                             (0x00000100U)

#define EVE_MSW_CTL_IBUFHB_SHIFT                                                                            (12U)
#define EVE_MSW_CTL_IBUFHB_MASK                                                                             (0x00001000U)

#define EVE_MSW_CTL_WBUF_SHIFT                                                                              (16U)
#define EVE_MSW_CTL_WBUF_MASK                                                                               (0x00010000U)

#define EVE_MSW_CTL_RESERVED_SHIFT                                                                          (1U)
#define EVE_MSW_CTL_RESERVED_MASK                                                                           (0x0000000eU)

#define EVE_MSW_CTL_RESERVED1_SHIFT                                                                         (5U)
#define EVE_MSW_CTL_RESERVED1_MASK                                                                          (0x000000e0U)

#define EVE_MSW_CTL_RESERVED2_SHIFT                                                                         (9U)
#define EVE_MSW_CTL_RESERVED2_MASK                                                                          (0x00000e00U)

#define EVE_MSW_CTL_RESERVED3_SHIFT                                                                         (13U)
#define EVE_MSW_CTL_RESERVED3_MASK                                                                          (0x0000e000U)

#define EVE_MSW_CTL_RESERVED4_SHIFT                                                                         (17U)
#define EVE_MSW_CTL_RESERVED4_MASK                                                                          (0xfffe0000U)

#define EVE_MSW_ERR_ARP32ERR_SHIFT                                                                          (0U)
#define EVE_MSW_ERR_ARP32ERR_MASK                                                                           (0x00000001U)

#define EVE_MSW_ERR_VERR_SHIFT                                                                              (1U)
#define EVE_MSW_ERR_VERR_MASK                                                                               (0x00000002U)

#define EVE_MSW_ERR_DMAERR_SHIFT                                                                            (2U)
#define EVE_MSW_ERR_DMAERR_MASK                                                                             (0x00000004U)

#define EVE_MSW_ERR_SYSERR_SHIFT                                                                            (3U)
#define EVE_MSW_ERR_SYSERR_MASK                                                                             (0x00000008U)

#define EVE_MSW_ERR_CONNID_SHIFT                                                                            (16U)
#define EVE_MSW_ERR_CONNID_MASK                                                                             (0x01ff0000U)

#define EVE_MSW_ERR_RESERVED_SHIFT                                                                          (4U)
#define EVE_MSW_ERR_RESERVED_MASK                                                                           (0x0000fff0U)

#define EVE_MSW_ERR_RESERVED1_SHIFT                                                                         (25U)
#define EVE_MSW_ERR_RESERVED1_MASK                                                                          (0xfe000000U)

#define EVE_MSW_ERRADDR_ADDR_SHIFT                                                                          (0U)
#define EVE_MSW_ERRADDR_ADDR_MASK                                                                           (0xffffffffU)

#define EVE_PC_INV_I_SHIFT                                                                                  (0U)
#define EVE_PC_INV_I_MASK                                                                                   (0x00000001U)

#define EVE_PC_INV_RESERVED_SHIFT                                                                           (1U)
#define EVE_PC_INV_RESERVED_MASK                                                                            (0xfffffffeU)

#define EVE_PC_IBAR_ADDR_SHIFT                                                                              (0U)
#define EVE_PC_IBAR_ADDR_MASK                                                                               (0xffffffffU)

#define EVE_PC_IBC_BC_SHIFT                                                                                 (0U)
#define EVE_PC_IBC_BC_MASK                                                                                  (0x0000ffffU)

#define EVE_PC_IBC_RESERVED_SHIFT                                                                           (16U)
#define EVE_PC_IBC_RESERVED_MASK                                                                            (0xffff0000U)

#define EVE_PC_ISAR_ADDR_SHIFT                                                                              (0U)
#define EVE_PC_ISAR_ADDR_MASK                                                                               (0xffffffffU)

#define EVE_PC_ISAR_DONE_DONE_SHIFT                                                                         (0U)
#define EVE_PC_ISAR_DONE_DONE_MASK                                                                          (0x00000001U)

#define EVE_PC_ISAR_DONE_RESERVED_SHIFT                                                                     (1U)
#define EVE_PC_ISAR_DONE_RESERVED_MASK                                                                      (0xfffffffeU)

#define EVE_PC_PBAR_ADDR_SHIFT                                                                              (0U)
#define EVE_PC_PBAR_ADDR_MASK                                                                               (0xffffffffU)

#define EVE_PC_PBC_BC_SHIFT                                                                                 (0U)
#define EVE_PC_PBC_BC_MASK                                                                                  (0x0000ffffU)

#define EVE_PC_PBC_RESERVED_SHIFT                                                                           (16U)
#define EVE_PC_PBC_RESERVED_MASK                                                                            (0xffff0000U)

#define EVE_PMEM_ED_CTL_EN_SHIFT                                                                            (0U)
#define EVE_PMEM_ED_CTL_EN_MASK                                                                             (0x00000001U)

#define EVE_PMEM_ED_CTL_INV_SHIFT                                                                           (1U)
#define EVE_PMEM_ED_CTL_INV_MASK                                                                            (0x00000002U)

#define EVE_PMEM_ED_CTL_RESERVED_SHIFT                                                                      (2U)
#define EVE_PMEM_ED_CTL_RESERVED_MASK                                                                       (0xfffffffcU)

#define EVE_PMEM_ED_STAT_ARP32ERR_SHIFT                                                                     (0U)
#define EVE_PMEM_ED_STAT_ARP32ERR_MASK                                                                      (0x00000001U)

#define EVE_PMEM_ED_STAT_VERR_SHIFT                                                                         (1U)
#define EVE_PMEM_ED_STAT_VERR_MASK                                                                          (0x00000002U)

#define EVE_PMEM_ED_STAT_DMAERR_SHIFT                                                                       (2U)
#define EVE_PMEM_ED_STAT_DMAERR_MASK                                                                        (0x00000004U)

#define EVE_PMEM_ED_STAT_SYSERR_SHIFT                                                                       (3U)
#define EVE_PMEM_ED_STAT_SYSERR_MASK                                                                        (0x00000008U)

#define EVE_PMEM_ED_STAT_SYSCONNID_SHIFT                                                                    (16U)
#define EVE_PMEM_ED_STAT_SYSCONNID_MASK                                                                     (0x01ff0000U)

#define EVE_PMEM_ED_STAT_RESERVED_SHIFT                                                                     (4U)
#define EVE_PMEM_ED_STAT_RESERVED_MASK                                                                      (0x0000fff0U)

#define EVE_PMEM_ED_STAT_RESERVED1_SHIFT                                                                    (25U)
#define EVE_PMEM_ED_STAT_RESERVED1_MASK                                                                     (0xfe000000U)

#define EVE_PMEM_EDADDR_ADDR_SHIFT                                                                          (0U)
#define EVE_PMEM_EDADDR_ADDR_MASK                                                                           (0xffffffffU)

#define EVE_DMEM_ED_CTL_EN_SHIFT                                                                            (0U)
#define EVE_DMEM_ED_CTL_EN_MASK                                                                             (0x00000001U)

#define EVE_DMEM_ED_CTL_INV_SHIFT                                                                           (1U)
#define EVE_DMEM_ED_CTL_INV_MASK                                                                            (0x00000002U)

#define EVE_DMEM_ED_CTL_RESERVED_SHIFT                                                                      (2U)
#define EVE_DMEM_ED_CTL_RESERVED_MASK                                                                       (0xfffffffcU)

#define EVE_DMEM_ED_STAT_ARP32ERR_SHIFT                                                                     (0U)
#define EVE_DMEM_ED_STAT_ARP32ERR_MASK                                                                      (0x00000001U)

#define EVE_DMEM_ED_STAT_VERR_SHIFT                                                                         (1U)
#define EVE_DMEM_ED_STAT_VERR_MASK                                                                          (0x00000002U)

#define EVE_DMEM_ED_STAT_DMAERR_SHIFT                                                                       (2U)
#define EVE_DMEM_ED_STAT_DMAERR_MASK                                                                        (0x00000004U)

#define EVE_DMEM_ED_STAT_SYSERR_SHIFT                                                                       (3U)
#define EVE_DMEM_ED_STAT_SYSERR_MASK                                                                        (0x00000008U)

#define EVE_DMEM_ED_STAT_SYSCONNID_SHIFT                                                                    (16U)
#define EVE_DMEM_ED_STAT_SYSCONNID_MASK                                                                     (0x01ff0000U)

#define EVE_DMEM_ED_STAT_RESERVED_SHIFT                                                                     (4U)
#define EVE_DMEM_ED_STAT_RESERVED_MASK                                                                      (0x0000fff0U)

#define EVE_DMEM_ED_STAT_RESERVED1_SHIFT                                                                    (25U)
#define EVE_DMEM_ED_STAT_RESERVED1_MASK                                                                     (0xfe000000U)

#define EVE_DMEM_EDADDR_ADDR_SHIFT                                                                          (0U)
#define EVE_DMEM_EDADDR_ADDR_MASK                                                                           (0xffffffffU)

#define EVE_DMEM_EDADDR_BO_BO_SHIFT                                                                         (0U)
#define EVE_DMEM_EDADDR_BO_BO_MASK                                                                          (0xffffffffU)

#define EVE_WBUF_ED_CTL_EN_SHIFT                                                                            (0U)
#define EVE_WBUF_ED_CTL_EN_MASK                                                                             (0x00000001U)

#define EVE_WBUF_ED_CTL_INV_SHIFT                                                                           (1U)
#define EVE_WBUF_ED_CTL_INV_MASK                                                                            (0x00000002U)

#define EVE_WBUF_ED_CTL_RESERVED_SHIFT                                                                      (2U)
#define EVE_WBUF_ED_CTL_RESERVED_MASK                                                                       (0xfffffffcU)

#define EVE_WBUF_ED_STAT_ARP32ERR_SHIFT                                                                     (0U)
#define EVE_WBUF_ED_STAT_ARP32ERR_MASK                                                                      (0x00000001U)

#define EVE_WBUF_ED_STAT_VERR_SHIFT                                                                         (1U)
#define EVE_WBUF_ED_STAT_VERR_MASK                                                                          (0x00000002U)

#define EVE_WBUF_ED_STAT_DMAERR_SHIFT                                                                       (2U)
#define EVE_WBUF_ED_STAT_DMAERR_MASK                                                                        (0x00000004U)

#define EVE_WBUF_ED_STAT_SYSERR_SHIFT                                                                       (3U)
#define EVE_WBUF_ED_STAT_SYSERR_MASK                                                                        (0x00000008U)

#define EVE_WBUF_ED_STAT_SYSCONNID_SHIFT                                                                    (16U)
#define EVE_WBUF_ED_STAT_SYSCONNID_MASK                                                                     (0x01ff0000U)

#define EVE_WBUF_ED_STAT_RESERVED_SHIFT                                                                     (4U)
#define EVE_WBUF_ED_STAT_RESERVED_MASK                                                                      (0x0000fff0U)

#define EVE_WBUF_ED_STAT_RESERVED1_SHIFT                                                                    (25U)
#define EVE_WBUF_ED_STAT_RESERVED1_MASK                                                                     (0xfe000000U)

#define EVE_WBUF_EDADDR_ADDR_SHIFT                                                                          (0U)
#define EVE_WBUF_EDADDR_ADDR_MASK                                                                           (0xffffffffU)

#define EVE_WBUF_EDADDR_BO_BO_SHIFT                                                                         (0U)
#define EVE_WBUF_EDADDR_BO_BO_MASK                                                                          (0xffffffffU)

#define EVE_IBUF_ED_CTL_EN_SHIFT                                                                            (0U)
#define EVE_IBUF_ED_CTL_EN_MASK                                                                             (0x00000001U)

#define EVE_IBUF_ED_CTL_INV_SHIFT                                                                           (1U)
#define EVE_IBUF_ED_CTL_INV_MASK                                                                            (0x00000002U)

#define EVE_IBUF_ED_CTL_RESERVED_SHIFT                                                                      (2U)
#define EVE_IBUF_ED_CTL_RESERVED_MASK                                                                       (0xfffffffcU)

#define EVE_IBUF_ED_STAT_ARP32ERR_SHIFT                                                                     (0U)
#define EVE_IBUF_ED_STAT_ARP32ERR_MASK                                                                      (0x00000001U)

#define EVE_IBUF_ED_STAT_VERR_SHIFT                                                                         (1U)
#define EVE_IBUF_ED_STAT_VERR_MASK                                                                          (0x00000002U)

#define EVE_IBUF_ED_STAT_DMAERR_SHIFT                                                                       (2U)
#define EVE_IBUF_ED_STAT_DMAERR_MASK                                                                        (0x00000004U)

#define EVE_IBUF_ED_STAT_SYSERR_SHIFT                                                                       (3U)
#define EVE_IBUF_ED_STAT_SYSERR_MASK                                                                        (0x00000008U)

#define EVE_IBUF_ED_STAT_SYSCONNID_SHIFT                                                                    (16U)
#define EVE_IBUF_ED_STAT_SYSCONNID_MASK                                                                     (0x01ff0000U)

#define EVE_IBUF_ED_STAT_RESERVED_SHIFT                                                                     (4U)
#define EVE_IBUF_ED_STAT_RESERVED_MASK                                                                      (0x0000fff0U)

#define EVE_IBUF_ED_STAT_RESERVED1_SHIFT                                                                    (25U)
#define EVE_IBUF_ED_STAT_RESERVED1_MASK                                                                     (0xfe000000U)

#define EVE_IBUF_EDADDR_ADDR_SHIFT                                                                          (0U)
#define EVE_IBUF_EDADDR_ADDR_MASK                                                                           (0xffffffffU)

#define EVE_IBUF_EDADDR_BO_BO_SHIFT                                                                         (0U)
#define EVE_IBUF_EDADDR_BO_BO_MASK                                                                          (0xffffffffU)

#define EVE_ED_ARP32_DISC_EN_ENABLE_SHIFT                                                                   (0U)
#define EVE_ED_ARP32_DISC_EN_ENABLE_MASK                                                                    (0x0000ffffU)

#define EVE_ED_ARP32_DISC_EN_RESERVED_SHIFT                                                                 (16U)
#define EVE_ED_ARP32_DISC_EN_RESERVED_MASK                                                                  (0xffff0000U)

#define EVE_ED_OCPI_DISC_EN_ENABLE_SHIFT                                                                    (0U)
#define EVE_ED_OCPI_DISC_EN_ENABLE_MASK                                                                     (0x0000ffffU)

#define EVE_ED_OCPI_DISC_EN_RESERVED_SHIFT                                                                  (16U)
#define EVE_ED_OCPI_DISC_EN_RESERVED_MASK                                                                   (0xffff0000U)

#define EVE_MSW_ERR_IRQSTATUS_RAW_EVENT_SHIFT                                                               (0U)
#define EVE_MSW_ERR_IRQSTATUS_RAW_EVENT_MASK                                                                (0x0000000fU)

#define EVE_MSW_ERR_IRQSTATUS_RAW_RESERVED_SHIFT                                                            (4U)
#define EVE_MSW_ERR_IRQSTATUS_RAW_RESERVED_MASK                                                             (0xfffffff0U)

#define EVE_MSW_ERR_IRQSTATUS_EVENT_SHIFT                                                                   (0U)
#define EVE_MSW_ERR_IRQSTATUS_EVENT_MASK                                                                    (0x0000000fU)

#define EVE_MSW_ERR_IRQSTATUS_RESERVED_SHIFT                                                                (4U)
#define EVE_MSW_ERR_IRQSTATUS_RESERVED_MASK                                                                 (0xfffffff0U)

#define EVE_MSW_ERR_IRQENABLE_SET_ENABLE_SHIFT                                                              (0U)
#define EVE_MSW_ERR_IRQENABLE_SET_ENABLE_MASK                                                               (0x0000000fU)

#define EVE_MSW_ERR_IRQENABLE_SET_RESERVED_SHIFT                                                            (4U)
#define EVE_MSW_ERR_IRQENABLE_SET_RESERVED_MASK                                                             (0xfffffff0U)

#define EVE_MSW_ERR_IRQENABLE_CLR_ENABLE_SHIFT                                                              (0U)
#define EVE_MSW_ERR_IRQENABLE_CLR_ENABLE_MASK                                                               (0x0000000fU)

#define EVE_MSW_ERR_IRQENABLE_CLR_RESERVED_SHIFT                                                            (4U)
#define EVE_MSW_ERR_IRQENABLE_CLR_RESERVED_MASK                                                             (0xfffffff0U)

#define EVE_ED_LCL_IRQSTATUS_RAW_EVENT_SHIFT                                                                (0U)
#define EVE_ED_LCL_IRQSTATUS_RAW_EVENT_MASK                                                                 (0x0000ffffU)

#define EVE_ED_LCL_IRQSTATUS_RAW_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_LCL_IRQSTATUS_RAW_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_ED_LCL_IRQSTATUS_EVENT_SHIFT                                                                    (0U)
#define EVE_ED_LCL_IRQSTATUS_EVENT_MASK                                                                     (0x0000ffffU)

#define EVE_ED_LCL_IRQSTATUS_RESERVED_SHIFT                                                                 (16U)
#define EVE_ED_LCL_IRQSTATUS_RESERVED_MASK                                                                  (0xffff0000U)

#define EVE_ED_LCL_IRQENABLE_SET_ENABLE_SHIFT                                                               (0U)
#define EVE_ED_LCL_IRQENABLE_SET_ENABLE_MASK                                                                (0x0000ffffU)

#define EVE_ED_LCL_IRQENABLE_SET_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_LCL_IRQENABLE_SET_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_ED_LCL_IRQENABLE_CLR_ENABLE_SHIFT                                                               (0U)
#define EVE_ED_LCL_IRQENABLE_CLR_ENABLE_MASK                                                                (0x0000ffffU)

#define EVE_ED_LCL_IRQENABLE_CLR_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_LCL_IRQENABLE_CLR_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_ARP32_NMI_IRQSTATUS_RAW_EVENT_SHIFT                                                             (0U)
#define EVE_ARP32_NMI_IRQSTATUS_RAW_EVENT_MASK                                                              (0xffffffffU)

#define EVE_ARP32_NMI_IRQSTATUS_EVENT_SHIFT                                                                 (0U)
#define EVE_ARP32_NMI_IRQSTATUS_EVENT_MASK                                                                  (0xffffffffU)

#define EVE_ARP32_NMI_IRQENABLE_SET_ENABLE_SHIFT                                                            (0U)
#define EVE_ARP32_NMI_IRQENABLE_SET_ENABLE_MASK                                                             (0xffffffffU)

#define EVE_ARP32_NMI_IRQENABLE_CLR_ENABLE_SHIFT                                                            (0U)
#define EVE_ARP32_NMI_IRQENABLE_CLR_ENABLE_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT4_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT4_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT4_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT4_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT4_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT4_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT4_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT4_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT5_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT5_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT5_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT5_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT5_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT5_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT5_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT5_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT6_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT6_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT6_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT6_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT6_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT6_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT6_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT6_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT7_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT7_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT7_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT7_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT7_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT7_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT7_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT7_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_IRQWAKEEN_ENABLE_SHIFT                                                                    (0U)
#define EVE_ARP32_IRQWAKEEN_ENABLE_MASK                                                                     (0x00ffffffU)

#define EVE_ARP32_IRQWAKEEN_RESERVED_SHIFT                                                                  (24U)
#define EVE_ARP32_IRQWAKEEN_RESERVED_MASK                                                                   (0xff000000U)

#define EVE_MISR_CTL_ENABLE_SHIFT                                                                           (0U)
#define EVE_MISR_CTL_ENABLE_MASK                                                                            (0x00000007U)

#define EVE_MISR_CTL_RESERVED_SHIFT                                                                         (3U)
#define EVE_MISR_CTL_RESERVED_MASK                                                                          (0xfffffff8U)

#define EVE_MISR_CLEAR_CLEAR_SHIFT                                                                          (0U)
#define EVE_MISR_CLEAR_CLEAR_MASK                                                                           (0x00000007U)

#define EVE_MISR_CLEAR_RESERVED_SHIFT                                                                       (3U)
#define EVE_MISR_CLEAR_RESERVED_MASK                                                                        (0xfffffff8U)

#define EVE_MISR0_A_SIGNATURE_SHIFT                                                                         (0U)
#define EVE_MISR0_A_SIGNATURE_MASK                                                                          (0xffffffffU)

#define EVE_MISR0_D_SIGNATURE_SHIFT                                                                         (0U)
#define EVE_MISR0_D_SIGNATURE_MASK                                                                          (0xffffffffU)

#define EVE_MISR1_A_SIGNATURE_SHIFT                                                                         (0U)
#define EVE_MISR1_A_SIGNATURE_MASK                                                                          (0xffffffffU)

#define EVE_MISR1_D_SIGNATURE_SHIFT                                                                         (0U)
#define EVE_MISR1_D_SIGNATURE_MASK                                                                          (0xffffffffU)

#define EVE_MISR2_D0_SIGNATURE_SHIFT                                                                        (0U)
#define EVE_MISR2_D0_SIGNATURE_MASK                                                                         (0xffffffffU)

#define EVE_MISR2_D1_SIGNATURE_SHIFT                                                                        (0U)
#define EVE_MISR2_D1_SIGNATURE_MASK                                                                         (0xffffffffU)

#define EVE_MISR2_D2_SIGNATURE_SHIFT                                                                        (0U)
#define EVE_MISR2_D2_SIGNATURE_MASK                                                                         (0xffffffffU)

#define EVE_MISR2_D3_SIGNATURE_SHIFT                                                                        (0U)
#define EVE_MISR2_D3_SIGNATURE_MASK                                                                         (0xffffffffU)

#define EVE_IRQ_EOI_LINE_NUMBER_SHIFT                                                                       (0U)
#define EVE_IRQ_EOI_LINE_NUMBER_MASK                                                                        (0x00000007U)

#define EVE_IRQ_EOI_RESERVED_SHIFT                                                                          (3U)
#define EVE_IRQ_EOI_RESERVED_MASK                                                                           (0xfffffff8U)

#define EVE_ED_OUT_IRQSTATUS_RAW_EVENT_SHIFT                                                                (0U)
#define EVE_ED_OUT_IRQSTATUS_RAW_EVENT_MASK                                                                 (0x0000ffffU)

#define EVE_ED_OUT_IRQSTATUS_RAW_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_OUT_IRQSTATUS_RAW_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_ED_OUT_IRQSTATUS_EVENT_SHIFT                                                                    (0U)
#define EVE_ED_OUT_IRQSTATUS_EVENT_MASK                                                                     (0x0000ffffU)

#define EVE_ED_OUT_IRQSTATUS_RESERVED_SHIFT                                                                 (16U)
#define EVE_ED_OUT_IRQSTATUS_RESERVED_MASK                                                                  (0xffff0000U)

#define EVE_ED_OUT_IRQENABLE_SET_ENABLE_SHIFT                                                               (0U)
#define EVE_ED_OUT_IRQENABLE_SET_ENABLE_MASK                                                                (0x0000ffffU)

#define EVE_ED_OUT_IRQENABLE_SET_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_OUT_IRQENABLE_SET_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_ED_OUT_IRQENABLE_CLR_ENABLE_SHIFT                                                               (0U)
#define EVE_ED_OUT_IRQENABLE_CLR_ENABLE_MASK                                                                (0x0000ffffU)

#define EVE_ED_OUT_IRQENABLE_CLR_RESERVED_SHIFT                                                             (16U)
#define EVE_ED_OUT_IRQENABLE_CLR_RESERVED_MASK                                                              (0xffff0000U)

#define EVE_INT0_OUT_IRQSTATUS_RAW_EVENT_SHIFT                                                              (0U)
#define EVE_INT0_OUT_IRQSTATUS_RAW_EVENT_MASK                                                               (0xffffffffU)

#define EVE_INT0_OUT_IRQSTATUS_EVENT_SHIFT                                                                  (0U)
#define EVE_INT0_OUT_IRQSTATUS_EVENT_MASK                                                                   (0xffffffffU)

#define EVE_INT0_OUT_IRQENABLE_SET_ENABLE_SHIFT                                                             (0U)
#define EVE_INT0_OUT_IRQENABLE_SET_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT0_OUT_IRQENABLE_CLR_ENABLE_SHIFT                                                             (0U)
#define EVE_INT0_OUT_IRQENABLE_CLR_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT1_OUT_IRQSTATUS_RAW_EVENT_SHIFT                                                              (0U)
#define EVE_INT1_OUT_IRQSTATUS_RAW_EVENT_MASK                                                               (0xffffffffU)

#define EVE_INT1_OUT_IRQSTATUS_EVENT_SHIFT                                                                  (0U)
#define EVE_INT1_OUT_IRQSTATUS_EVENT_MASK                                                                   (0xffffffffU)

#define EVE_INT1_OUT_IRQENABLE_SET_ENABLE_SHIFT                                                             (0U)
#define EVE_INT1_OUT_IRQENABLE_SET_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT1_OUT_IRQENABLE_CLR_ENABLE_SHIFT                                                             (0U)
#define EVE_INT1_OUT_IRQENABLE_CLR_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT2_OUT_IRQSTATUS_RAW_EVENT_SHIFT                                                              (0U)
#define EVE_INT2_OUT_IRQSTATUS_RAW_EVENT_MASK                                                               (0xffffffffU)

#define EVE_INT2_OUT_IRQSTATUS_EVENT_SHIFT                                                                  (0U)
#define EVE_INT2_OUT_IRQSTATUS_EVENT_MASK                                                                   (0xffffffffU)

#define EVE_INT2_OUT_IRQENABLE_SET_ENABLE_SHIFT                                                             (0U)
#define EVE_INT2_OUT_IRQENABLE_SET_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT2_OUT_IRQENABLE_CLR_ENABLE_SHIFT                                                             (0U)
#define EVE_INT2_OUT_IRQENABLE_CLR_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT3_OUT_IRQSTATUS_RAW_EVENT_SHIFT                                                              (0U)
#define EVE_INT3_OUT_IRQSTATUS_RAW_EVENT_MASK                                                               (0xffffffffU)

#define EVE_INT3_OUT_IRQSTATUS_EVENT_SHIFT                                                                  (0U)
#define EVE_INT3_OUT_IRQSTATUS_EVENT_MASK                                                                   (0xffffffffU)

#define EVE_INT3_OUT_IRQENABLE_SET_ENABLE_SHIFT                                                             (0U)
#define EVE_INT3_OUT_IRQENABLE_SET_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_INT3_OUT_IRQENABLE_CLR_ENABLE_SHIFT                                                             (0U)
#define EVE_INT3_OUT_IRQENABLE_CLR_ENABLE_MASK                                                              (0xffffffffU)

#define EVE_GPOUT0_EVENT_SHIFT                                                                              (0U)
#define EVE_GPOUT0_EVENT_MASK                                                                               (0xffffffffU)

#define EVE_GPOUT0_SET_EVENT_SHIFT                                                                          (0U)
#define EVE_GPOUT0_SET_EVENT_MASK                                                                           (0xffffffffU)

#define EVE_GPOUT0_CLR_EVENT_SHIFT                                                                          (0U)
#define EVE_GPOUT0_CLR_EVENT_MASK                                                                           (0xffffffffU)

#define EVE_GPOUT0_PULSE_EVENT_SHIFT                                                                        (0U)
#define EVE_GPOUT0_PULSE_EVENT_MASK                                                                         (0xffffffffU)

#define EVE_GPOUT1_EVENT_SHIFT                                                                              (0U)
#define EVE_GPOUT1_EVENT_MASK                                                                               (0xffffffffU)

#define EVE_GPOUT1_SET_EVENT_SHIFT                                                                          (0U)
#define EVE_GPOUT1_SET_EVENT_MASK                                                                           (0xffffffffU)

#define EVE_GPOUT1_CLR_EVENT_SHIFT                                                                          (0U)
#define EVE_GPOUT1_CLR_EVENT_MASK                                                                           (0xffffffffU)

#define EVE_GPOUT1_PULSE_EVENT_SHIFT                                                                        (0U)
#define EVE_GPOUT1_PULSE_EVENT_MASK                                                                         (0xffffffffU)

#define EVE_ARP32_INT8_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT8_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT8_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT8_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT8_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT8_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT8_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT8_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT9_IRQSTATUS_RAW_EVENT_SHIFT                                                            (0U)
#define EVE_ARP32_INT9_IRQSTATUS_RAW_EVENT_MASK                                                             (0xffffffffU)

#define EVE_ARP32_INT9_IRQSTATUS_EVENT_SHIFT                                                                (0U)
#define EVE_ARP32_INT9_IRQSTATUS_EVENT_MASK                                                                 (0xffffffffU)

#define EVE_ARP32_INT9_IRQENABLE_SET_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT9_IRQENABLE_SET_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT9_IRQENABLE_CLR_ENABLE_SHIFT                                                           (0U)
#define EVE_ARP32_INT9_IRQENABLE_CLR_ENABLE_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT10_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT10_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT10_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT10_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT10_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT10_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT10_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT10_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT11_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT11_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT11_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT11_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT11_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT11_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT11_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT11_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT12_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT12_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT12_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT12_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT12_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT12_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT12_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT12_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT13_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT13_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT13_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT13_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT13_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT13_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT13_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT13_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT14_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT14_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT14_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT14_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT14_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT14_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT14_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT14_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT15_IRQSTATUS_RAW_EVENT_SHIFT                                                           (0U)
#define EVE_ARP32_INT15_IRQSTATUS_RAW_EVENT_MASK                                                            (0xffffffffU)

#define EVE_ARP32_INT15_IRQSTATUS_EVENT_SHIFT                                                               (0U)
#define EVE_ARP32_INT15_IRQSTATUS_EVENT_MASK                                                                (0xffffffffU)

#define EVE_ARP32_INT15_IRQENABLE_SET_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT15_IRQENABLE_SET_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_ARP32_INT15_IRQENABLE_CLR_ENABLE_SHIFT                                                          (0U)
#define EVE_ARP32_INT15_IRQENABLE_CLR_ENABLE_MASK                                                           (0xffffffffU)

#define EVE_GPIN0_EVENT_SHIFT                                                                               (0U)
#define EVE_GPIN0_EVENT_MASK                                                                                (0xffffffffU)

#define EVE_GPIN1_EVENT_SHIFT                                                                               (0U)
#define EVE_GPIN1_EVENT_MASK                                                                                (0xffffffffU)

#define EVE_CME_DONE_GPOUT_EVENT_SHIFT                                                                      (0U)
#define EVE_CME_DONE_GPOUT_EVENT_MASK                                                                       (0x000000ffU)

#define EVE_CME_DONE_GPOUT_RESERVED_SHIFT                                                                   (8U)
#define EVE_CME_DONE_GPOUT_RESERVED_MASK                                                                    (0xffffff00U)

#define EVE_CME_DONE_GPOUT_SET_EVENT_SHIFT                                                                  (0U)
#define EVE_CME_DONE_GPOUT_SET_EVENT_MASK                                                                   (0x000000ffU)

#define EVE_CME_DONE_GPOUT_SET_RESERVED_SHIFT                                                               (8U)
#define EVE_CME_DONE_GPOUT_SET_RESERVED_MASK                                                                (0xffffff00U)

#define EVE_CME_DONE_GPOUT_CLR_EVENT_SHIFT                                                                  (0U)
#define EVE_CME_DONE_GPOUT_CLR_EVENT_MASK                                                                   (0x000000ffU)

#define EVE_CME_DONE_GPOUT_CLR_RESERVED_SHIFT                                                               (8U)
#define EVE_CME_DONE_GPOUT_CLR_RESERVED_MASK                                                                (0xffffff00U)

#define EVE_CME_DONE_GPOUT_PULSE_EVENT_SHIFT                                                                (0U)
#define EVE_CME_DONE_GPOUT_PULSE_EVENT_MASK                                                                 (0x000000ffU)

#define EVE_CME_DONE_GPOUT_PULSE_RESERVED_SHIFT                                                             (8U)
#define EVE_CME_DONE_GPOUT_PULSE_RESERVED_MASK                                                              (0xffffff00U)

#define EVE_CME_DONE_SEL_SEL0_SHIFT                                                                         (0U)
#define EVE_CME_DONE_SEL_SEL0_MASK                                                                          (0x0000000fU)

#define EVE_CME_DONE_SEL_SEL1_SHIFT                                                                         (4U)
#define EVE_CME_DONE_SEL_SEL1_MASK                                                                          (0x000000f0U)

#define EVE_CME_DONE_SEL_SEL2_SHIFT                                                                         (8U)
#define EVE_CME_DONE_SEL_SEL2_MASK                                                                          (0x00000f00U)

#define EVE_CME_DONE_SEL_SEL3_SHIFT                                                                         (12U)
#define EVE_CME_DONE_SEL_SEL3_MASK                                                                          (0x0000f000U)

#define EVE_CME_DONE_SEL_SEL4_SHIFT                                                                         (16U)
#define EVE_CME_DONE_SEL_SEL4_MASK                                                                          (0x000f0000U)

#define EVE_CME_DONE_SEL_SEL5_SHIFT                                                                         (20U)
#define EVE_CME_DONE_SEL_SEL5_MASK                                                                          (0x00f00000U)

#define EVE_CME_DONE_SEL_SEL6_SHIFT                                                                         (24U)
#define EVE_CME_DONE_SEL_SEL6_MASK                                                                          (0x0f000000U)

#define EVE_CME_DONE_SEL_SEL7_SHIFT                                                                         (28U)
#define EVE_CME_DONE_SEL_SEL7_MASK                                                                          (0xf0000000U)

#define EVE_CME_DONE_EN_EN_SHIFT                                                                            (0U)
#define EVE_CME_DONE_EN_EN_MASK                                                                             (0x000000ffU)

#define EVE_CME_DONE_EN_RESERVED_SHIFT                                                                      (8U)
#define EVE_CME_DONE_EN_RESERVED_MASK                                                                       (0xffffff00U)

#define EVE_PM_STAT0_SIDLEREQ_SHIFT                                                                         (0U)
#define EVE_PM_STAT0_SIDLEREQ_MASK                                                                          (0x00000001U)

#define EVE_PM_STAT0_SIDLEACK_SHIFT                                                                         (1U)
#define EVE_PM_STAT0_SIDLEACK_MASK                                                                          (0x00000006U)

#define EVE_PM_STAT0_SWAKEUP_SHIFT                                                                          (3U)
#define EVE_PM_STAT0_SWAKEUP_MASK                                                                           (0x00000008U)

#define EVE_PM_STAT0_MSTANDBY_SHIFT                                                                         (4U)
#define EVE_PM_STAT0_MSTANDBY_MASK                                                                          (0x00000010U)

#define EVE_PM_STAT0_MWAIT_SHIFT                                                                            (5U)
#define EVE_PM_STAT0_MWAIT_MASK                                                                             (0x00000020U)

#define EVE_PM_STAT0_OCPS_MCONNECT_SHIFT                                                                    (8U)
#define EVE_PM_STAT0_OCPS_MCONNECT_MASK                                                                     (0x00000300U)

#define EVE_PM_STAT0_OCPS_SCONNECT_SHIFT                                                                    (12U)
#define EVE_PM_STAT0_OCPS_SCONNECT_MASK                                                                     (0x00007000U)

#define EVE_PM_STAT0_OCPM0_MCONNECT_SHIFT                                                                   (16U)
#define EVE_PM_STAT0_OCPM0_MCONNECT_MASK                                                                    (0x00030000U)

#define EVE_PM_STAT0_OCPM0_SCONNECT_SHIFT                                                                   (20U)
#define EVE_PM_STAT0_OCPM0_SCONNECT_MASK                                                                    (0x00700000U)

#define EVE_PM_STAT0_OCPM1_MCONNECT_SHIFT                                                                   (24U)
#define EVE_PM_STAT0_OCPM1_MCONNECT_MASK                                                                    (0x03000000U)

#define EVE_PM_STAT0_OCPM1_SCONNECT_SHIFT                                                                   (28U)
#define EVE_PM_STAT0_OCPM1_SCONNECT_MASK                                                                    (0x70000000U)

#define EVE_PM_STAT0_RESERVED_SHIFT                                                                         (6U)
#define EVE_PM_STAT0_RESERVED_MASK                                                                          (0x000000c0U)

#define EVE_PM_STAT0_RESERVED1_SHIFT                                                                        (10U)
#define EVE_PM_STAT0_RESERVED1_MASK                                                                         (0x00000c00U)

#define EVE_PM_STAT0_RESERVED2_SHIFT                                                                        (15U)
#define EVE_PM_STAT0_RESERVED2_MASK                                                                         (0x00008000U)

#define EVE_PM_STAT0_RESERVED3_SHIFT                                                                        (18U)
#define EVE_PM_STAT0_RESERVED3_MASK                                                                         (0x000c0000U)

#define EVE_PM_STAT0_RESERVED4_SHIFT                                                                        (23U)
#define EVE_PM_STAT0_RESERVED4_MASK                                                                         (0x00800000U)

#define EVE_PM_STAT0_RESERVED5_SHIFT                                                                        (26U)
#define EVE_PM_STAT0_RESERVED5_MASK                                                                         (0x0c000000U)

#define EVE_PM_STAT0_RESERVED6_SHIFT                                                                        (31U)
#define EVE_PM_STAT0_RESERVED6_MASK                                                                         (0x80000000U)

#define EVE_PM_STAT1_SUBMODULE_IDLE_REQ_SHIFT                                                               (0U)
#define EVE_PM_STAT1_SUBMODULE_IDLE_REQ_MASK                                                                (0x00000001U)

#define EVE_PM_STAT1_TPTC0_SIDLEACK_SHIFT                                                                   (1U)
#define EVE_PM_STAT1_TPTC0_SIDLEACK_MASK                                                                    (0x00000002U)

#define EVE_PM_STAT1_TPTC1_SIDLEACK_SHIFT                                                                   (2U)
#define EVE_PM_STAT1_TPTC1_SIDLEACK_MASK                                                                    (0x00000004U)

#define EVE_PM_STAT1_TPCC_SIDLEACK_SHIFT                                                                    (3U)
#define EVE_PM_STAT1_TPCC_SIDLEACK_MASK                                                                     (0x00000008U)

#define EVE_PM_STAT1_SCTM_SIDLEACK_SHIFT                                                                    (4U)
#define EVE_PM_STAT1_SCTM_SIDLEACK_MASK                                                                     (0x00000010U)

#define EVE_PM_STAT1_MMU0_SIDLEACK_SHIFT                                                                    (5U)
#define EVE_PM_STAT1_MMU0_SIDLEACK_MASK                                                                     (0x00000020U)

#define EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_SHIFT                                                             (6U)
#define EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_MASK                                                              (0x00000040U)

#define EVE_PM_STAT1_MMU1_SIDLEACK_SHIFT                                                                    (7U)
#define EVE_PM_STAT1_MMU1_SIDLEACK_MASK                                                                     (0x00000080U)

#define EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_SHIFT                                                             (8U)
#define EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_MASK                                                              (0x00000100U)

#define EVE_PM_STAT1_L2_EVE_SIDLEACK_SHIFT                                                                  (9U)
#define EVE_PM_STAT1_L2_EVE_SIDLEACK_MASK                                                                   (0x00000200U)

#define EVE_PM_STAT1_SMSET_SIDLEACK_SHIFT                                                                   (10U)
#define EVE_PM_STAT1_SMSET_SIDLEACK_MASK                                                                    (0x00000400U)

#define EVE_PM_STAT1_EVE_CONTROL_SIDLEACK_SHIFT                                                             (11U)
#define EVE_PM_STAT1_EVE_CONTROL_SIDLEACK_MASK                                                              (0x00000800U)

#define EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_SHIFT                                                              (12U)
#define EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_MASK                                                               (0x00001000U)

#define EVE_PM_STAT1_TPTC0_MWAIT_SHIFT                                                                      (13U)
#define EVE_PM_STAT1_TPTC0_MWAIT_MASK                                                                       (0x00002000U)

#define EVE_PM_STAT1_TPTC1_MWAIT_SHIFT                                                                      (14U)
#define EVE_PM_STAT1_TPTC1_MWAIT_MASK                                                                       (0x00004000U)

#define EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_SHIFT                                                            (15U)
#define EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_MASK                                                             (0x00008000U)

#define EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_SHIFT                                                             (16U)
#define EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_MASK                                                              (0x00010000U)

#define EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_SHIFT                                                             (17U)
#define EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_MASK                                                              (0x00020000U)

#define EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_SHIFT                                                              (18U)
#define EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_MASK                                                               (0x00040000U)

#define EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_SHIFT                                                              (19U)
#define EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_MASK                                                               (0x00080000U)

#define EVE_PM_STAT1_STBY_MDISCACK_OCPM0_SHIFT                                                              (20U)
#define EVE_PM_STAT1_STBY_MDISCACK_OCPM0_MASK                                                               (0x00300000U)

#define EVE_PM_STAT1_STBY_MDISCACK_OCPM1_SHIFT                                                              (22U)
#define EVE_PM_STAT1_STBY_MDISCACK_OCPM1_MASK                                                               (0x00c00000U)

#define EVE_PM_STAT1_RESERVED_SHIFT                                                                         (24U)
#define EVE_PM_STAT1_RESERVED_MASK                                                                          (0xff000000U)

#define EVE_DBGOUT_GROUP_SHIFT                                                                              (0U)
#define EVE_DBGOUT_GROUP_MASK                                                                               (0x0000000fU)

#define EVE_DBGOUT_VALUE_SHIFT                                                                              (8U)
#define EVE_DBGOUT_VALUE_MASK                                                                               (0xffffff00U)

#define EVE_DBGOUT_RESERVED_SHIFT                                                                           (4U)
#define EVE_DBGOUT_RESERVED_MASK                                                                            (0x000000f0U)

#define EVE_RSVD0_VAL_SHIFT                                                                                 (0U)
#define EVE_RSVD0_VAL_MASK                                                                                  (0xffffffffU)

#define EVE_RSVD1_VAL_SHIFT                                                                                 (0U)
#define EVE_RSVD1_VAL_MASK                                                                                  (0xffffffffU)

#define EVE_TEST_VAL_SHIFT                                                                                  (0U)
#define EVE_TEST_VAL_MASK                                                                                   (0xffffffffU)

#define EVE_MMR_LOCK_MMR_LOCK_SHIFT                                                                         (0U)
#define EVE_MMR_LOCK_MMR_LOCK_MASK                                                                          (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_EVE_CONTROL_H_ */
