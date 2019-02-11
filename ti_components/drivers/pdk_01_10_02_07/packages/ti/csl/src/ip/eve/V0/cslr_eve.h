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
#ifndef CSLR_EVE_H_
#define CSLR_EVE_H_

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
    volatile Uint32 HWINFO;
    volatile Uint32 SYSCONFIG;
    volatile Uint32 STAT;
    volatile Uint32 DISC_CONFIG;
    volatile Uint32 BUS_CONFIG;
    volatile Uint32 VCOP_HALT_CONFIG;
    volatile Uint32 MMU_CONFIG;
    volatile Uint32 MEMMAP;
    volatile Uint32 MSW_CTL;
    volatile Uint32 MSW_ERR;
    volatile Uint32 MSW_ERRADDR;
    volatile Uint8  RSVD0[16];
    volatile Uint32 PC_INV;
    volatile Uint8  RSVD1[12];
    volatile Uint32 PC_IBAR;
    volatile Uint32 PC_IBC;
    volatile Uint32 PC_ISAR;
    volatile Uint32 PC_ISAR_DONE;
    volatile Uint32 PC_PBAR;
    volatile Uint32 PC_PBC;
    volatile Uint8  RSVD2[24];
    volatile Uint32 PMEM_ED_CTL;
    volatile Uint32 PMEM_ED_STAT;
    volatile Uint32 PMEM_EDADDR;
    volatile Uint8  RSVD3[4];
    volatile Uint32 DMEM_ED_CTL;
    volatile Uint32 DMEM_ED_STAT;
    volatile Uint32 DMEM_EDADDR;
    volatile Uint32 DMEM_EDADDR_BO;
    volatile Uint32 WBUF_ED_CTL;
    volatile Uint32 WBUF_ED_STAT;
    volatile Uint32 WBUF_EDADDR;
    volatile Uint32 WBUF_EDADDR_BO;
    volatile Uint32 IBUF_ED_CTL;
    volatile Uint32 IBUF_ED_STAT;
    volatile Uint32 IBUF_EDADDR;
    volatile Uint32 IBUF_EDADDR_BO;
    volatile Uint8  RSVD4[56];
    volatile Uint32 ED_ARP32_DISC_EN;
    volatile Uint32 ED_OCPI_DISC_EN;
    volatile Uint8  RSVD5[16];
    volatile Uint32 MSW_ERR_IRQSTS_RAW;
    volatile Uint32 MSW_ERR_IRQSTS;
    volatile Uint32 MSW_ERR_IRQEN_SET;
    volatile Uint32 MSW_ERR_IRQEN_CLR;
    volatile Uint32 ED_LCL_IRQSTS_RAW;
    volatile Uint32 ED_LCL_IRQSTS;
    volatile Uint32 ED_LCL_IRQEN_SET;
    volatile Uint32 ED_LCL_IRQEN_CLR;
    volatile Uint8  RSVD6[208];
    volatile Uint32 ARP32_NMI_IRQSTS_RAW;
    volatile Uint32 ARP32_NMI_IRQSTS;
    volatile Uint32 ARP32_NMI_IRQEN_SET;
    volatile Uint32 ARP32_NMI_IRQEN_CLR;
    volatile Uint32 ARP32_INT4_IRQSTS_RAW;
    volatile Uint32 ARP32_INT4_IRQSTS;
    volatile Uint32 ARP32_INT4_IRQEN_SET;
    volatile Uint32 ARP32_INT4_IRQEN_CLR;
    volatile Uint32 ARP32_INT5_IRQSTS_RAW;
    volatile Uint32 ARP32_INT5_IRQSTS;
    volatile Uint32 ARP32_INT5_IRQEN_SET;
    volatile Uint32 ARP32_INT5_IRQEN_CLR;
    volatile Uint32 ARP32_INT6_IRQSTS_RAW;
    volatile Uint32 ARP32_INT6_IRQSTS;
    volatile Uint32 ARP32_INT6_IRQEN_SET;
    volatile Uint32 ARP32_INT6_IRQEN_CLR;
    volatile Uint32 ARP32_INT7_IRQSTS_RAW;
    volatile Uint32 ARP32_INT7_IRQSTS;
    volatile Uint32 ARP32_INT7_IRQEN_SET;
    volatile Uint32 ARP32_INT7_IRQEN_CLR;
    volatile Uint8  RSVD7[172];
    volatile Uint32 ARP32_IRQWAKEEN;
    volatile Uint32 MMR_LOCK0;
    volatile Uint32 MMR_LOCK1;
    volatile Uint32 MMR_LOCK2;
    volatile Uint32 MMR_LOCK3;
    volatile Uint32 MMR_LOCK4;
    volatile Uint32 MMR_LOCK5;
    volatile Uint32 MMR_LOCK6;
    volatile Uint32 MMR_LOCK7;
    volatile Uint32 MMR_LOCK8;
    volatile Uint32 MMR_LOCK9;
    volatile Uint8  RSVD8[216];
    volatile Uint32 MISR_CTL;
    volatile Uint32 MISR_CLR;
    volatile Uint8  RSVD9[8];
    volatile Uint32 MISR0_A;
    volatile Uint32 MISR0_D;
    volatile Uint32 MISR1_A;
    volatile Uint32 MISR1_D;
    volatile Uint32 MISR2_D0;
    volatile Uint32 MISR2_D1;
    volatile Uint32 MISR2_D2;
    volatile Uint32 MISR2_D3;
    volatile Uint8  RSVD10[208];
    volatile Uint32 IRQ_EOI;
    volatile Uint8  RSVD11[12];
    volatile Uint32 ED_OUT_IRQSTS_RAW;
    volatile Uint32 ED_OUT_IRQSTS;
    volatile Uint32 ED_OUT_IRQEN_SET;
    volatile Uint32 ED_OUT_IRQEN_CLR;
    volatile Uint32 INT0_OUT_IRQSTS_RAW;
    volatile Uint32 INT0_OUT_IRQSTS;
    volatile Uint32 INT0_OUT_IRQEN_SET;
    volatile Uint32 INT0_OUT_IRQEN_CLR;
    volatile Uint32 INT1_OUT_IRQSTS_RAW;
    volatile Uint32 INT1_OUT_IRQSTS;
    volatile Uint32 INT1_OUT_IRQEN_SET;
    volatile Uint32 INT1_OUT_IRQEN_CLR;
    volatile Uint32 INT2_OUT_IRQSTS_RAW;
    volatile Uint32 INT2_OUT_IRQSTS;
    volatile Uint32 INT2_OUT_IRQEN_SET;
    volatile Uint32 INT2_OUT_IRQEN_CLR;
    volatile Uint32 INT3_OUT_IRQSTS_RAW;
    volatile Uint32 INT3_OUT_IRQSTS;
    volatile Uint32 INT3_OUT_IRQEN_SET;
    volatile Uint32 INT3_OUT_IRQEN_CLR;
    volatile Uint8  RSVD12[160];
    volatile Uint32 ARP32_INT8_IRQSTS_RAW;
    volatile Uint32 ARP32_INT8_IRQSTS;
    volatile Uint32 ARP32_INT8_IRQEN_SET;
    volatile Uint32 ARP32_INT8_IRQEN_CLR;
    volatile Uint32 ARP32_INT9_IRQSTS_RAW;
    volatile Uint32 ARP32_INT9_IRQSTS;
    volatile Uint32 ARP32_INT9_IRQEN_SET;
    volatile Uint32 ARP32_INT9_IRQEN_CLR;
    volatile Uint32 ARP32_INT10_IRQSTS_RAW;
    volatile Uint32 ARP32_INT10_IRQSTS;
    volatile Uint32 ARP32_INT10_IRQEN_SET;
    volatile Uint32 ARP32_INT10_IRQEN_CLR;
    volatile Uint32 ARP32_INT11_IRQSTS_RAW;
    volatile Uint32 ARP32_INT11_IRQSTS;
    volatile Uint32 ARP32_INT11_IRQEN_SET;
    volatile Uint32 ARP32_INT11_IRQEN_CLR;
    volatile Uint32 ARP32_INT12_IRQSTS_RAW;
    volatile Uint32 ARP32_INT12_IRQSTS;
    volatile Uint32 ARP32_INT12_IRQEN_SET;
    volatile Uint32 ARP32_INT12_IRQEN_CLR;
    volatile Uint32 ARP32_INT13_IRQSTS_RAW;
    volatile Uint32 ARP32_INT13_IRQSTS;
    volatile Uint32 ARP32_INT13_IRQEN_SET;
    volatile Uint32 ARP32_INT13_IRQEN_CLR;
    volatile Uint8  RSVD13[32];
    volatile Uint32 ARP32_INT14_IRQSTS_RAW;
    volatile Uint32 ARP32_INT14_IRQSTS;
    volatile Uint32 ARP32_INT14_IRQEN_SET;
    volatile Uint32 ARP32_INT14_IRQEN_CLR;
    volatile Uint32 ARP32_INT15_IRQSTS_RAW;
    volatile Uint32 ARP32_INT15_IRQSTS;
    volatile Uint32 ARP32_INT15_IRQEN_SET;
    volatile Uint32 ARP32_INT15_IRQEN_CLR;
    volatile Uint8  RSVD14[96];
    volatile Uint32 GPOUT0;
    volatile Uint32 GPOUT0_SET;
    volatile Uint32 GPOUT0_CLR;
    volatile Uint32 GPOUT0_PULSE;
    volatile Uint32 GPOUT1;
    volatile Uint32 GPOUT1_SET;
    volatile Uint32 GPOUT1_CLR;
    volatile Uint32 GPOUT1_PULSE;
    volatile Uint8  RSVD15[32];
    volatile Uint32 GPIN0;
    volatile Uint32 GPIN1;
    volatile Uint8  RSVD16[56];
    volatile Uint32 CME_DONE_GPOUT;
    volatile Uint32 CME_DONE_GPOUT_SET;
    volatile Uint32 CME_DONE_GPOUT_CLR;
    volatile Uint32 CME_DONE_GPOUT_PULSE;
    volatile Uint32 CME_DONE_SEL;
    volatile Uint32 CME_DONE_EN;
    volatile Uint8  RSVD17[2120];
    volatile Uint32 PM_STAT0;
    volatile Uint32 PM_STAT1;
    volatile Uint32 DBGOUT;
    volatile Uint8  RSVD18[16];
    volatile Uint32 TEST;
} CSL_EveRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* REVISION */
#define CSL_EVE_REVISION                                        (0x0U)

/* HWINFO */
#define CSL_EVE_HWINFO                                          (0x4U)

/* SYSCONFIG */
#define CSL_EVE_SYSCONFIG                                       (0x8U)

/* STAT */
#define CSL_EVE_STAT                                            (0xCU)

/* DISC_CONFIG */
#define CSL_EVE_DISC_CONFIG                                     (0x10U)

/* BUS_CONFIG */
#define CSL_EVE_BUS_CONFIG                                      (0x14U)

/* VCOP_HALT_CONFIG */
#define CSL_EVE_VCOP_HALT_CONFIG                                (0x18U)

/* MMU_CONFIG */
#define CSL_EVE_MMU_CONFIG                                      (0x1CU)

/* MEMMAP */
#define CSL_EVE_MEMMAP                                          (0x20U)

/* MSW_CTL */
#define CSL_EVE_MSW_CTL                                         (0x24U)

/* MSW_ERR */
#define CSL_EVE_MSW_ERR                                         (0x28U)

/* MSW_ERRADDR */
#define CSL_EVE_MSW_ERRADDR                                     (0x2CU)

/* PC_INV */
#define CSL_EVE_PC_INV                                          (0x40U)

/* PC_IBAR */
#define CSL_EVE_PC_IBAR                                         (0x50U)

/* PC_IBC */
#define CSL_EVE_PC_IBC                                          (0x54U)

/* PC_ISAR */
#define CSL_EVE_PC_ISAR                                         (0x58U)

/* PC_ISAR_DONE */
#define CSL_EVE_PC_ISAR_DONE                                    (0x5CU)

/* PC_PBAR */
#define CSL_EVE_PC_PBAR                                         (0x60U)

/* PC_PBC */
#define CSL_EVE_PC_PBC                                          (0x64U)

/* PMEM_ED_CTL */
#define CSL_EVE_PMEM_ED_CTL                                     (0x80U)

/* PMEM_ED_STAT */
#define CSL_EVE_PMEM_ED_STAT                                    (0x84U)

/* PMEM_EDADDR */
#define CSL_EVE_PMEM_EDADDR                                     (0x88U)

/* DMEM_ED_CTL */
#define CSL_EVE_DMEM_ED_CTL                                     (0x90U)

/* DMEM_ED_STAT */
#define CSL_EVE_DMEM_ED_STAT                                    (0x94U)

/* DMEM_EDADDR */
#define CSL_EVE_DMEM_EDADDR                                     (0x98U)

/* DMEM_EDADDR_BO */
#define CSL_EVE_DMEM_EDADDR_BO                                  (0x9CU)

/* WBUF_ED_CTL */
#define CSL_EVE_WBUF_ED_CTL                                     (0xA0U)

/* WBUF_ED_STAT */
#define CSL_EVE_WBUF_ED_STAT                                    (0xA4U)

/* WBUF_EDADDR */
#define CSL_EVE_WBUF_EDADDR                                     (0xA8U)

/* WBUF_EDADDR_BO */
#define CSL_EVE_WBUF_EDADDR_BO                                  (0xACU)

/* IBUF_ED_CTL */
#define CSL_EVE_IBUF_ED_CTL                                     (0xB0U)

/* IBUF_ED_STAT */
#define CSL_EVE_IBUF_ED_STAT                                    (0xB4U)

/* IBUF_EDADDR */
#define CSL_EVE_IBUF_EDADDR                                     (0xB8U)

/* IBUF_EDADDR_BO */
#define CSL_EVE_IBUF_EDADDR_BO                                  (0xBCU)

/* ED_ARP32_DISC_EN */
#define CSL_EVE_ED_ARP32_DISC_EN                                (0xF8U)

/* ED_OCPI_DISC_EN */
#define CSL_EVE_ED_OCPI_DISC_EN                                 (0xFCU)

/* MSW_ERR_IRQSTS_RAW */
#define CSL_EVE_MSW_ERR_IRQSTS_RAW                              (0x110U)

/* MSW_ERR_IRQSTS */
#define CSL_EVE_MSW_ERR_IRQSTS                                  (0x114U)

/* MSW_ERR_IRQEN_SET */
#define CSL_EVE_MSW_ERR_IRQEN_SET                               (0x118U)

/* MSW_ERR_IRQEN_CLR */
#define CSL_EVE_MSW_ERR_IRQEN_CLR                               (0x11CU)

/* ED_LCL_IRQSTS_RAW */
#define CSL_EVE_ED_LCL_IRQSTS_RAW                               (0x120U)

/* ED_LCL_IRQSTS */
#define CSL_EVE_ED_LCL_IRQSTS                                   (0x124U)

/* ED_LCL_IRQEN_SET */
#define CSL_EVE_ED_LCL_IRQEN_SET                                (0x128U)

/* ED_LCL_IRQEN_CLR */
#define CSL_EVE_ED_LCL_IRQEN_CLR                                (0x12CU)

/* ARP32_NMI_IRQSTS_RAW */
#define CSL_EVE_ARP32_NMI_IRQSTS_RAW                            (0x200U)

/* ARP32_NMI_IRQSTS */
#define CSL_EVE_ARP32_NMI_IRQSTS                                (0x204U)

/* ARP32_NMI_IRQEN_SET */
#define CSL_EVE_ARP32_NMI_IRQEN_SET                             (0x208U)

/* ARP32_NMI_IRQEN_CLR */
#define CSL_EVE_ARP32_NMI_IRQEN_CLR                             (0x20CU)

/* ARP32_INT4_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT4_IRQSTS_RAW                           (0x210U)

/* ARP32_INT4_IRQSTS */
#define CSL_EVE_ARP32_INT4_IRQSTS                               (0x214U)

/* ARP32_INT4_IRQEN_SET */
#define CSL_EVE_ARP32_INT4_IRQEN_SET                            (0x218U)

/* ARP32_INT4_IRQEN_CLR */
#define CSL_EVE_ARP32_INT4_IRQEN_CLR                            (0x21CU)

/* ARP32_INT5_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT5_IRQSTS_RAW                           (0x220U)

/* ARP32_INT5_IRQSTS */
#define CSL_EVE_ARP32_INT5_IRQSTS                               (0x224U)

/* ARP32_INT5_IRQEN_SET */
#define CSL_EVE_ARP32_INT5_IRQEN_SET                            (0x228U)

/* ARP32_INT5_IRQEN_CLR */
#define CSL_EVE_ARP32_INT5_IRQEN_CLR                            (0x22CU)

/* ARP32_INT6_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT6_IRQSTS_RAW                           (0x230U)

/* ARP32_INT6_IRQSTS */
#define CSL_EVE_ARP32_INT6_IRQSTS                               (0x234U)

/* ARP32_INT6_IRQEN_SET */
#define CSL_EVE_ARP32_INT6_IRQEN_SET                            (0x238U)

/* ARP32_INT6_IRQEN_CLR */
#define CSL_EVE_ARP32_INT6_IRQEN_CLR                            (0x23CU)

/* ARP32_INT7_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT7_IRQSTS_RAW                           (0x240U)

/* ARP32_INT7_IRQSTS */
#define CSL_EVE_ARP32_INT7_IRQSTS                               (0x244U)

/* ARP32_INT7_IRQEN_SET */
#define CSL_EVE_ARP32_INT7_IRQEN_SET                            (0x248U)

/* ARP32_INT7_IRQEN_CLR */
#define CSL_EVE_ARP32_INT7_IRQEN_CLR                            (0x24CU)

/* ARP32_IRQWAKEEN */
#define CSL_EVE_ARP32_IRQWAKEEN                                 (0x2FCU)

/* MMR_LOCK0 */
#define CSL_EVE_MMR_LOCK0                                       (0x300U)

/* MMR_LOCK1 */
#define CSL_EVE_MMR_LOCK1                                       (0x304U)

/* MMR_LOCK2 */
#define CSL_EVE_MMR_LOCK2                                       (0x308U)

/* MMR_LOCK3 */
#define CSL_EVE_MMR_LOCK3                                       (0x30CU)

/* MMR_LOCK4 */
#define CSL_EVE_MMR_LOCK4                                       (0x310U)

/* MMR_LOCK5 */
#define CSL_EVE_MMR_LOCK5                                       (0x314U)

/* MMR_LOCK6 */
#define CSL_EVE_MMR_LOCK6                                       (0x318U)

/* MMR_LOCK7 */
#define CSL_EVE_MMR_LOCK7                                       (0x31CU)

/* MMR_LOCK8 */
#define CSL_EVE_MMR_LOCK8                                       (0x320U)

/* MMR_LOCK9 */
#define CSL_EVE_MMR_LOCK9                                       (0x324U)

/* MISR_CTL */
#define CSL_EVE_MISR_CTL                                        (0x400U)

/* MISR_CLR */
#define CSL_EVE_MISR_CLR                                        (0x404U)

/* MISR0_A */
#define CSL_EVE_MISR0_A                                         (0x410U)

/* MISR0_D */
#define CSL_EVE_MISR0_D                                         (0x414U)

/* MISR1_A */
#define CSL_EVE_MISR1_A                                         (0x418U)

/* MISR1_D */
#define CSL_EVE_MISR1_D                                         (0x41CU)

/* MISR2_D0 */
#define CSL_EVE_MISR2_D0                                        (0x420U)

/* MISR2_D1 */
#define CSL_EVE_MISR2_D1                                        (0x424U)

/* MISR2_D2 */
#define CSL_EVE_MISR2_D2                                        (0x428U)

/* MISR2_D3 */
#define CSL_EVE_MISR2_D3                                        (0x42CU)

/* IRQ_EOI */
#define CSL_EVE_IRQ_EOI                                         (0x500U)

/* ED_OUT_IRQSTS_RAW */
#define CSL_EVE_ED_OUT_IRQSTS_RAW                               (0x510U)

/* ED_OUT_IRQSTS */
#define CSL_EVE_ED_OUT_IRQSTS                                   (0x514U)

/* ED_OUT_IRQEN_SET */
#define CSL_EVE_ED_OUT_IRQEN_SET                                (0x518U)

/* ED_OUT_IRQEN_CLR */
#define CSL_EVE_ED_OUT_IRQEN_CLR                                (0x51CU)

/* INT0_OUT_IRQSTS_RAW */
#define CSL_EVE_INT0_OUT_IRQSTS_RAW                             (0x520U)

/* INT0_OUT_IRQSTS */
#define CSL_EVE_INT0_OUT_IRQSTS                                 (0x524U)

/* INT0_OUT_IRQEN_SET */
#define CSL_EVE_INT0_OUT_IRQEN_SET                              (0x528U)

/* INT0_OUT_IRQEN_CLR */
#define CSL_EVE_INT0_OUT_IRQEN_CLR                              (0x52CU)

/* INT1_OUT_IRQSTS_RAW */
#define CSL_EVE_INT1_OUT_IRQSTS_RAW                             (0x530U)

/* INT1_OUT_IRQSTS */
#define CSL_EVE_INT1_OUT_IRQSTS                                 (0x534U)

/* INT1_OUT_IRQEN_SET */
#define CSL_EVE_INT1_OUT_IRQEN_SET                              (0x538U)

/* INT1_OUT_IRQEN_CLR */
#define CSL_EVE_INT1_OUT_IRQEN_CLR                              (0x53CU)

/* INT2_OUT_IRQSTS_RAW */
#define CSL_EVE_INT2_OUT_IRQSTS_RAW                             (0x540U)

/* INT2_OUT_IRQSTS */
#define CSL_EVE_INT2_OUT_IRQSTS                                 (0x544U)

/* INT2_OUT_IRQEN_SET */
#define CSL_EVE_INT2_OUT_IRQEN_SET                              (0x548U)

/* INT2_OUT_IRQEN_CLR */
#define CSL_EVE_INT2_OUT_IRQEN_CLR                              (0x54CU)

/* INT3_OUT_IRQSTS_RAW */
#define CSL_EVE_INT3_OUT_IRQSTS_RAW                             (0x550U)

/* INT3_OUT_IRQSTS */
#define CSL_EVE_INT3_OUT_IRQSTS                                 (0x554U)

/* INT3_OUT_IRQEN_SET */
#define CSL_EVE_INT3_OUT_IRQEN_SET                              (0x558U)

/* INT3_OUT_IRQEN_CLR */
#define CSL_EVE_INT3_OUT_IRQEN_CLR                              (0x55CU)

/* ARP32_INT8_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT8_IRQSTS_RAW                           (0x600U)

/* ARP32_INT8_IRQSTS */
#define CSL_EVE_ARP32_INT8_IRQSTS                               (0x604U)

/* ARP32_INT8_IRQEN_SET */
#define CSL_EVE_ARP32_INT8_IRQEN_SET                            (0x608U)

/* ARP32_INT8_IRQEN_CLR */
#define CSL_EVE_ARP32_INT8_IRQEN_CLR                            (0x60CU)

/* ARP32_INT9_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT9_IRQSTS_RAW                           (0x610U)

/* ARP32_INT9_IRQSTS */
#define CSL_EVE_ARP32_INT9_IRQSTS                               (0x614U)

/* ARP32_INT9_IRQEN_SET */
#define CSL_EVE_ARP32_INT9_IRQEN_SET                            (0x618U)

/* ARP32_INT9_IRQEN_CLR */
#define CSL_EVE_ARP32_INT9_IRQEN_CLR                            (0x61CU)

/* ARP32_INT10_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT10_IRQSTS_RAW                          (0x620U)

/* ARP32_INT10_IRQSTS */
#define CSL_EVE_ARP32_INT10_IRQSTS                              (0x624U)

/* ARP32_INT10_IRQEN_SET */
#define CSL_EVE_ARP32_INT10_IRQEN_SET                           (0x628U)

/* ARP32_INT10_IRQEN_CLR */
#define CSL_EVE_ARP32_INT10_IRQEN_CLR                           (0x62CU)

/* ARP32_INT11_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT11_IRQSTS_RAW                          (0x630U)

/* ARP32_INT11_IRQSTS */
#define CSL_EVE_ARP32_INT11_IRQSTS                              (0x634U)

/* ARP32_INT11_IRQEN_SET */
#define CSL_EVE_ARP32_INT11_IRQEN_SET                           (0x638U)

/* ARP32_INT11_IRQEN_CLR */
#define CSL_EVE_ARP32_INT11_IRQEN_CLR                           (0x63CU)

/* ARP32_INT12_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT12_IRQSTS_RAW                          (0x640U)

/* ARP32_INT12_IRQSTS */
#define CSL_EVE_ARP32_INT12_IRQSTS                              (0x644U)

/* ARP32_INT12_IRQEN_SET */
#define CSL_EVE_ARP32_INT12_IRQEN_SET                           (0x648U)

/* ARP32_INT12_IRQEN_CLR */
#define CSL_EVE_ARP32_INT12_IRQEN_CLR                           (0x64CU)

/* ARP32_INT13_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT13_IRQSTS_RAW                          (0x650U)

/* ARP32_INT13_IRQSTS */
#define CSL_EVE_ARP32_INT13_IRQSTS                              (0x654U)

/* ARP32_INT13_IRQEN_SET */
#define CSL_EVE_ARP32_INT13_IRQEN_SET                           (0x658U)

/* ARP32_INT13_IRQEN_CLR */
#define CSL_EVE_ARP32_INT13_IRQEN_CLR                           (0x65CU)

/* ARP32_INT14_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT14_IRQSTS_RAW                          (0x680U)

/* ARP32_INT14_IRQSTS */
#define CSL_EVE_ARP32_INT14_IRQSTS                              (0x684U)

/* ARP32_INT14_IRQEN_SET */
#define CSL_EVE_ARP32_INT14_IRQEN_SET                           (0x688U)

/* ARP32_INT14_IRQEN_CLR */
#define CSL_EVE_ARP32_INT14_IRQEN_CLR                           (0x68CU)

/* ARP32_INT15_IRQSTS_RAW */
#define CSL_EVE_ARP32_INT15_IRQSTS_RAW                          (0x690U)

/* ARP32_INT15_IRQSTS */
#define CSL_EVE_ARP32_INT15_IRQSTS                              (0x694U)

/* ARP32_INT15_IRQEN_SET */
#define CSL_EVE_ARP32_INT15_IRQEN_SET                           (0x698U)

/* ARP32_INT15_IRQEN_CLR */
#define CSL_EVE_ARP32_INT15_IRQEN_CLR                           (0x69CU)

/* GPOUT0 */
#define CSL_EVE_GPOUT0                                          (0x700U)

/* GPOUT0_SET */
#define CSL_EVE_GPOUT0_SET                                      (0x704U)

/* GPOUT0_CLR */
#define CSL_EVE_GPOUT0_CLR                                      (0x708U)

/* GPOUT0_PULSE */
#define CSL_EVE_GPOUT0_PULSE                                    (0x70CU)

/* GPOUT1 */
#define CSL_EVE_GPOUT1                                          (0x710U)

/* GPOUT1_SET */
#define CSL_EVE_GPOUT1_SET                                      (0x714U)

/* GPOUT1_CLR */
#define CSL_EVE_GPOUT1_CLR                                      (0x718U)

/* GPOUT1_PULSE */
#define CSL_EVE_GPOUT1_PULSE                                    (0x71CU)

/* GPIN0 */
#define CSL_EVE_GPIN0                                           (0x740U)

/* GPIN1 */
#define CSL_EVE_GPIN1                                           (0x744U)

/* CME_DONE_GPOUT */
#define CSL_EVE_CME_DONE_GPOUT                                  (0x780U)

/* CME_DONE_GPOUT_SET */
#define CSL_EVE_CME_DONE_GPOUT_SET                              (0x784U)

/* CME_DONE_GPOUT_CLR */
#define CSL_EVE_CME_DONE_GPOUT_CLR                              (0x788U)

/* CME_DONE_GPOUT_PULSE */
#define CSL_EVE_CME_DONE_GPOUT_PULSE                            (0x78CU)

/* CME_DONE_SEL */
#define CSL_EVE_CME_DONE_SEL                                    (0x790U)

/* CME_DONE_EN */
#define CSL_EVE_CME_DONE_EN                                     (0x794U)

/* PM_STAT0 */
#define CSL_EVE_PM_STAT0                                        (0xFE0U)

/* PM_STAT1 */
#define CSL_EVE_PM_STAT1                                        (0xFE4U)

/* DBGOUT */
#define CSL_EVE_DBGOUT                                          (0xFE8U)

/* TEST */
#define CSL_EVE_TEST                                            (0xFFCU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_EVE_REVISION_MINOR_MASK                             (0x0000003FU)
#define CSL_EVE_REVISION_MINOR_SHIFT                            (0U)
#define CSL_EVE_REVISION_MINOR_RESETVAL                         (0x00000000U)
#define CSL_EVE_REVISION_MINOR_MAX                              (0x0000003fU)

#define CSL_EVE_REVISION_CUSTOM_MASK                            (0x000000C0U)
#define CSL_EVE_REVISION_CUSTOM_SHIFT                           (6U)
#define CSL_EVE_REVISION_CUSTOM_RESETVAL                        (0x00000000U)
#define CSL_EVE_REVISION_CUSTOM_MAX                             (0x00000003U)

#define CSL_EVE_REVISION_MAJOR_MASK                             (0x00000700U)
#define CSL_EVE_REVISION_MAJOR_SHIFT                            (8U)
#define CSL_EVE_REVISION_MAJOR_RESETVAL                         (0x00000000U)
#define CSL_EVE_REVISION_MAJOR_MAX                              (0x00000007U)

#define CSL_EVE_REVISION_RTL_MASK                               (0x0000F800U)
#define CSL_EVE_REVISION_RTL_SHIFT                              (11U)
#define CSL_EVE_REVISION_RTL_RESETVAL                           (0x00000000U)
#define CSL_EVE_REVISION_RTL_MAX                                (0x0000001fU)

#define CSL_EVE_REVISION_FUNC_MASK                              (0x0FFF0000U)
#define CSL_EVE_REVISION_FUNC_SHIFT                             (16U)
#define CSL_EVE_REVISION_FUNC_RESETVAL                          (0x00000000U)
#define CSL_EVE_REVISION_FUNC_MAX                               (0x00000fffU)

#define CSL_EVE_REVISION_SCHEME_MASK                            (0xC0000000U)
#define CSL_EVE_REVISION_SCHEME_SHIFT                           (30U)
#define CSL_EVE_REVISION_SCHEME_RESETVAL                        (0x00000000U)
#define CSL_EVE_REVISION_SCHEME_MAX                             (0x00000003U)

#define CSL_EVE_REVISION_RESETVAL                               (0x00000000U)

/* HWINFO */

#define CSL_EVE_HWINFO_EVENUM_MASK                              (0x0000000FU)
#define CSL_EVE_HWINFO_EVENUM_SHIFT                             (0U)
#define CSL_EVE_HWINFO_EVENUM_RESETVAL                          (0x00000000U)
#define CSL_EVE_HWINFO_EVENUM_MAX                               (0x0000000fU)

#define CSL_EVE_HWINFO_INFO_MASK                                (0xFFFFFFF0U)
#define CSL_EVE_HWINFO_INFO_SHIFT                               (4U)
#define CSL_EVE_HWINFO_INFO_RESETVAL                            (0x00000000U)
#define CSL_EVE_HWINFO_INFO_MAX                                 (0x0fffffffU)

#define CSL_EVE_HWINFO_RESETVAL                                 (0x00000000U)

/* SYSCONFIG */

#define CSL_EVE_SYSCONFIG_SOFTRESET_MASK                        (0x00000001U)
#define CSL_EVE_SYSCONFIG_SOFTRESET_SHIFT                       (0U)
#define CSL_EVE_SYSCONFIG_SOFTRESET_RESETVAL                    (0x00000000U)
#define CSL_EVE_SYSCONFIG_SOFTRESET_MAX                         (0x00000001U)

#define CSL_EVE_SYSCONFIG_FREEEMU_MASK                          (0x00000002U)
#define CSL_EVE_SYSCONFIG_FREEEMU_SHIFT                         (1U)
#define CSL_EVE_SYSCONFIG_FREEEMU_RESETVAL                      (0x00000000U)
#define CSL_EVE_SYSCONFIG_FREEEMU_MAX                           (0x00000001U)

#define CSL_EVE_SYSCONFIG_IDLEMODE_MASK                         (0x0000000CU)
#define CSL_EVE_SYSCONFIG_IDLEMODE_SHIFT                        (2U)
#define CSL_EVE_SYSCONFIG_IDLEMODE_RESETVAL                     (0x00000000U)
#define CSL_EVE_SYSCONFIG_IDLEMODE_MAX                          (0x00000003U)

#define CSL_EVE_SYSCONFIG_STANDBYMODE_MASK                      (0x00000030U)
#define CSL_EVE_SYSCONFIG_STANDBYMODE_SHIFT                     (4U)
#define CSL_EVE_SYSCONFIG_STANDBYMODE_RESETVAL                  (0x00000000U)
#define CSL_EVE_SYSCONFIG_STANDBYMODE_MAX                       (0x00000003U)

#define CSL_EVE_SYSCONFIG_RESETVAL                              (0x00000000U)

/* STAT */

#define CSL_EVE_STAT_ARP32_STAT_MASK                            (0x00000001U)
#define CSL_EVE_STAT_ARP32_STAT_SHIFT                           (0U)
#define CSL_EVE_STAT_ARP32_STAT_RESETVAL                        (0x00000000U)
#define CSL_EVE_STAT_ARP32_STAT_MAX                             (0x00000001U)

#define CSL_EVE_STAT_VCOP_STAT_MASK                             (0x00000002U)
#define CSL_EVE_STAT_VCOP_STAT_SHIFT                            (1U)
#define CSL_EVE_STAT_VCOP_STAT_RESETVAL                         (0x00000000U)
#define CSL_EVE_STAT_VCOP_STAT_MAX                              (0x00000001U)

#define CSL_EVE_STAT_PC_STAT_MASK                               (0x00000004U)
#define CSL_EVE_STAT_PC_STAT_SHIFT                              (2U)
#define CSL_EVE_STAT_PC_STAT_RESETVAL                           (0x00000000U)
#define CSL_EVE_STAT_PC_STAT_MAX                                (0x00000001U)

#define CSL_EVE_STAT_TC0_STAT_MASK                              (0x00000010U)
#define CSL_EVE_STAT_TC0_STAT_SHIFT                             (4U)
#define CSL_EVE_STAT_TC0_STAT_RESETVAL                          (0x00000000U)
#define CSL_EVE_STAT_TC0_STAT_MAX                               (0x00000001U)

#define CSL_EVE_STAT_TC1_STAT_MASK                              (0x00000020U)
#define CSL_EVE_STAT_TC1_STAT_SHIFT                             (5U)
#define CSL_EVE_STAT_TC1_STAT_RESETVAL                          (0x00000000U)
#define CSL_EVE_STAT_TC1_STAT_MAX                               (0x00000001U)

#define CSL_EVE_STAT_ARP32_INTC_STAT_MASK                       (0x00000080U)
#define CSL_EVE_STAT_ARP32_INTC_STAT_SHIFT                      (7U)
#define CSL_EVE_STAT_ARP32_INTC_STAT_RESETVAL                   (0x00000000U)
#define CSL_EVE_STAT_ARP32_INTC_STAT_MAX                        (0x00000001U)

#define CSL_EVE_STAT_INT_OUT_STAT_MASK                          (0x00000100U)
#define CSL_EVE_STAT_INT_OUT_STAT_SHIFT                         (8U)
#define CSL_EVE_STAT_INT_OUT_STAT_RESETVAL                      (0x00000000U)
#define CSL_EVE_STAT_INT_OUT_STAT_MAX                           (0x00000001U)

#define CSL_EVE_STAT_ARP32_DISC_STS_MASK                        (0x00030000U)
#define CSL_EVE_STAT_ARP32_DISC_STS_SHIFT                       (16U)
#define CSL_EVE_STAT_ARP32_DISC_STS_RESETVAL                    (0x00000000U)
#define CSL_EVE_STAT_ARP32_DISC_STS_MAX                         (0x00000003U)

#define CSL_EVE_STAT_OCPI_DISC_STAT_MASK                        (0x00300000U)
#define CSL_EVE_STAT_OCPI_DISC_STAT_SHIFT                       (20U)
#define CSL_EVE_STAT_OCPI_DISC_STAT_RESETVAL                    (0x00000000U)
#define CSL_EVE_STAT_OCPI_DISC_STAT_MAX                         (0x00000003U)

#define CSL_EVE_STAT_RESETVAL                                   (0x00000000U)

/* DISC_CONFIG */

#define CSL_EVE_DISC_CONFIG_ARP32_DISC_MASK                     (0x00000001U)
#define CSL_EVE_DISC_CONFIG_ARP32_DISC_SHIFT                    (0U)
#define CSL_EVE_DISC_CONFIG_ARP32_DISC_RESETVAL                 (0x00000000U)
#define CSL_EVE_DISC_CONFIG_ARP32_DISC_MAX                      (0x00000001U)

#define CSL_EVE_DISC_CONFIG_OCPI_DISC_MASK                      (0x00000010U)
#define CSL_EVE_DISC_CONFIG_OCPI_DISC_SHIFT                     (4U)
#define CSL_EVE_DISC_CONFIG_OCPI_DISC_RESETVAL                  (0x00000000U)
#define CSL_EVE_DISC_CONFIG_OCPI_DISC_MAX                       (0x00000001U)

#define CSL_EVE_DISC_CONFIG_RESETVAL                            (0x00000000U)

/* BUS_CONFIG */

#define CSL_EVE_BUS_CONFIG_MAX_IN_FLIGHT_MASK                   (0x0000000FU)
#define CSL_EVE_BUS_CONFIG_MAX_IN_FLIGHT_SHIFT                  (0U)
#define CSL_EVE_BUS_CONFIG_MAX_IN_FLIGHT_RESETVAL               (0x00000000U)
#define CSL_EVE_BUS_CONFIG_MAX_IN_FLIGHT_MAX                    (0x0000000fU)

#define CSL_EVE_BUS_CONFIG_DBP_EN_MASK                          (0x00000010U)
#define CSL_EVE_BUS_CONFIG_DBP_EN_SHIFT                         (4U)
#define CSL_EVE_BUS_CONFIG_DBP_EN_RESETVAL                      (0x00000000U)
#define CSL_EVE_BUS_CONFIG_DBP_EN_MAX                           (0x00000001U)

#define CSL_EVE_BUS_CONFIG_TC0_DBS_MASK                         (0x00000300U)
#define CSL_EVE_BUS_CONFIG_TC0_DBS_SHIFT                        (8U)
#define CSL_EVE_BUS_CONFIG_TC0_DBS_RESETVAL                     (0x00000000U)
#define CSL_EVE_BUS_CONFIG_TC0_DBS_MAX                          (0x00000003U)

#define CSL_EVE_BUS_CONFIG_TC1_DBS_MASK                         (0x00003000U)
#define CSL_EVE_BUS_CONFIG_TC1_DBS_SHIFT                        (12U)
#define CSL_EVE_BUS_CONFIG_TC1_DBS_RESETVAL                     (0x00000000U)
#define CSL_EVE_BUS_CONFIG_TC1_DBS_MAX                          (0x00000003U)

#define CSL_EVE_BUS_CONFIG_RESETVAL                             (0x00000000U)

/* VCOP_HALT_CONFIG */

#define CSL_EVE_VCOP_HALT_CONFIG_ED_EN_MASK                     (0x00000001U)
#define CSL_EVE_VCOP_HALT_CONFIG_ED_EN_SHIFT                    (0U)
#define CSL_EVE_VCOP_HALT_CONFIG_ED_EN_RESETVAL                 (0x00000000U)
#define CSL_EVE_VCOP_HALT_CONFIG_ED_EN_MAX                      (0x00000001U)

#define CSL_EVE_VCOP_HALT_CONFIG_MSW_EN_MASK                    (0x00000002U)
#define CSL_EVE_VCOP_HALT_CONFIG_MSW_EN_SHIFT                   (1U)
#define CSL_EVE_VCOP_HALT_CONFIG_MSW_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_VCOP_HALT_CONFIG_MSW_EN_MAX                     (0x00000001U)

#define CSL_EVE_VCOP_HALT_CONFIG_FORCE_ABORT_MASK               (0x00000004U)
#define CSL_EVE_VCOP_HALT_CONFIG_FORCE_ABORT_SHIFT              (2U)
#define CSL_EVE_VCOP_HALT_CONFIG_FORCE_ABORT_RESETVAL           (0x00000001U)
#define CSL_EVE_VCOP_HALT_CONFIG_FORCE_ABORT_MAX                (0x00000001U)

#define CSL_EVE_VCOP_HALT_CONFIG_RESETVAL                       (0x0000003cU)

/* MMU_CONFIG */

#define CSL_EVE_MMU_CONFIG_MMU0_EN_MASK                         (0x00000001U)
#define CSL_EVE_MMU_CONFIG_MMU0_EN_SHIFT                        (0U)
#define CSL_EVE_MMU_CONFIG_MMU0_EN_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMU_CONFIG_MMU0_EN_MAX                          (0x00000001U)

#define CSL_EVE_MMU_CONFIG_MMU1_EN_MASK                         (0x00000010U)
#define CSL_EVE_MMU_CONFIG_MMU1_EN_SHIFT                        (4U)
#define CSL_EVE_MMU_CONFIG_MMU1_EN_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMU_CONFIG_MMU1_EN_MAX                          (0x00000001U)

#define CSL_EVE_MMU_CONFIG_MMU0_ABORT_MASK                      (0x00000100U)
#define CSL_EVE_MMU_CONFIG_MMU0_ABORT_SHIFT                     (8U)
#define CSL_EVE_MMU_CONFIG_MMU0_ABORT_RESETVAL                  (0x00000000U)
#define CSL_EVE_MMU_CONFIG_MMU0_ABORT_MAX                       (0x00000001U)

#define CSL_EVE_MMU_CONFIG_MMU1_ABORT_MASK                      (0x00001000U)
#define CSL_EVE_MMU_CONFIG_MMU1_ABORT_SHIFT                     (12U)
#define CSL_EVE_MMU_CONFIG_MMU1_ABORT_RESETVAL                  (0x00000000U)
#define CSL_EVE_MMU_CONFIG_MMU1_ABORT_MAX                       (0x00000001U)

#define CSL_EVE_MMU_CONFIG_RESETVAL                             (0x00000000U)

/* MEMMAP */

#define CSL_EVE_MEMMAP_VCOP_ALIAS_MASK                          (0x00000001U)
#define CSL_EVE_MEMMAP_VCOP_ALIAS_SHIFT                         (0U)
#define CSL_EVE_MEMMAP_VCOP_ALIAS_RESETVAL                      (0x00000000U)
#define CSL_EVE_MEMMAP_VCOP_ALIAS_MAX                           (0x00000001U)

#define CSL_EVE_MEMMAP_LCL_EDMA_ALIAS_MASK                      (0x00000010U)
#define CSL_EVE_MEMMAP_LCL_EDMA_ALIAS_SHIFT                     (4U)
#define CSL_EVE_MEMMAP_LCL_EDMA_ALIAS_RESETVAL                  (0x00000000U)
#define CSL_EVE_MEMMAP_LCL_EDMA_ALIAS_MAX                       (0x00000001U)

#define CSL_EVE_MEMMAP_RESETVAL                                 (0x00000000U)

/* MSW_CTL */

#define CSL_EVE_MSW_CTL_IBUFLA_MASK                             (0x00000001U)
#define CSL_EVE_MSW_CTL_IBUFLA_SHIFT                            (0U)
#define CSL_EVE_MSW_CTL_IBUFLA_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_CTL_IBUFLA_MAX                              (0x00000001U)

#define CSL_EVE_MSW_CTL_IBUFHA_MASK                             (0x00000010U)
#define CSL_EVE_MSW_CTL_IBUFHA_SHIFT                            (4U)
#define CSL_EVE_MSW_CTL_IBUFHA_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_CTL_IBUFHA_MAX                              (0x00000001U)

#define CSL_EVE_MSW_CTL_IBUFLB_MASK                             (0x00000100U)
#define CSL_EVE_MSW_CTL_IBUFLB_SHIFT                            (8U)
#define CSL_EVE_MSW_CTL_IBUFLB_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_CTL_IBUFLB_MAX                              (0x00000001U)

#define CSL_EVE_MSW_CTL_IBUFHB_MASK                             (0x00001000U)
#define CSL_EVE_MSW_CTL_IBUFHB_SHIFT                            (12U)
#define CSL_EVE_MSW_CTL_IBUFHB_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_CTL_IBUFHB_MAX                              (0x00000001U)

#define CSL_EVE_MSW_CTL_WBUF_MASK                               (0x00010000U)
#define CSL_EVE_MSW_CTL_WBUF_SHIFT                              (16U)
#define CSL_EVE_MSW_CTL_WBUF_RESETVAL                           (0x00000000U)
#define CSL_EVE_MSW_CTL_WBUF_MAX                                (0x00000001U)

#define CSL_EVE_MSW_CTL_RESETVAL                                (0x00000000U)

/* MSW_ERR */

#define CSL_EVE_MSW_ERR_ARP32ERR_MASK                           (0x00000001U)
#define CSL_EVE_MSW_ERR_ARP32ERR_SHIFT                          (0U)
#define CSL_EVE_MSW_ERR_ARP32ERR_RESETVAL                       (0x00000000U)
#define CSL_EVE_MSW_ERR_ARP32ERR_MAX                            (0x00000001U)

#define CSL_EVE_MSW_ERR_VERR_MASK                               (0x00000002U)
#define CSL_EVE_MSW_ERR_VERR_SHIFT                              (1U)
#define CSL_EVE_MSW_ERR_VERR_RESETVAL                           (0x00000000U)
#define CSL_EVE_MSW_ERR_VERR_MAX                                (0x00000001U)

#define CSL_EVE_MSW_ERR_DMAERR_MASK                             (0x00000004U)
#define CSL_EVE_MSW_ERR_DMAERR_SHIFT                            (2U)
#define CSL_EVE_MSW_ERR_DMAERR_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_ERR_DMAERR_MAX                              (0x00000001U)

#define CSL_EVE_MSW_ERR_SYSERR_MASK                             (0x00000008U)
#define CSL_EVE_MSW_ERR_SYSERR_SHIFT                            (3U)
#define CSL_EVE_MSW_ERR_SYSERR_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_ERR_SYSERR_MAX                              (0x00000001U)

#define CSL_EVE_MSW_ERR_CONNID_MASK                             (0x01FF0000U)
#define CSL_EVE_MSW_ERR_CONNID_SHIFT                            (16U)
#define CSL_EVE_MSW_ERR_CONNID_RESETVAL                         (0x00000000U)
#define CSL_EVE_MSW_ERR_CONNID_MAX                              (0x000001ffU)

#define CSL_EVE_MSW_ERR_RESETVAL                                (0x00000000U)

/* MSW_ERRADDR */

#define CSL_EVE_MSW_ERRADDR_ADDR_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_MSW_ERRADDR_ADDR_SHIFT                          (0U)
#define CSL_EVE_MSW_ERRADDR_ADDR_RESETVAL                       (0x00000000U)
#define CSL_EVE_MSW_ERRADDR_ADDR_MAX                            (0xffffffffU)

#define CSL_EVE_MSW_ERRADDR_RESETVAL                            (0x00000000U)

/* PC_INV */

#define CSL_EVE_PC_INV_I_MASK                                   (0x00000001U)
#define CSL_EVE_PC_INV_I_SHIFT                                  (0U)
#define CSL_EVE_PC_INV_I_RESETVAL                               (0x00000000U)
#define CSL_EVE_PC_INV_I_MAX                                    (0x00000001U)

#define CSL_EVE_PC_INV_RESETVAL                                 (0x00000000U)

/* PC_IBAR */

#define CSL_EVE_PC_IBAR_ADDR_MASK                               (0xFFFFFFFFU)
#define CSL_EVE_PC_IBAR_ADDR_SHIFT                              (0U)
#define CSL_EVE_PC_IBAR_ADDR_RESETVAL                           (0x00000000U)
#define CSL_EVE_PC_IBAR_ADDR_MAX                                (0xffffffffU)

#define CSL_EVE_PC_IBAR_RESETVAL                                (0x00000000U)

/* PC_IBC */

#define CSL_EVE_PC_IBC_BC_MASK                                  (0x0000FFFFU)
#define CSL_EVE_PC_IBC_BC_SHIFT                                 (0U)
#define CSL_EVE_PC_IBC_BC_RESETVAL                              (0x00000000U)
#define CSL_EVE_PC_IBC_BC_MAX                                   (0x0000ffffU)

#define CSL_EVE_PC_IBC_RESETVAL                                 (0x00000000U)

/* PC_ISAR */

#define CSL_EVE_PC_ISAR_ADDR_MASK                               (0xFFFFFFFFU)
#define CSL_EVE_PC_ISAR_ADDR_SHIFT                              (0U)
#define CSL_EVE_PC_ISAR_ADDR_RESETVAL                           (0x00000000U)
#define CSL_EVE_PC_ISAR_ADDR_MAX                                (0xffffffffU)

#define CSL_EVE_PC_ISAR_RESETVAL                                (0x00000000U)

/* PC_ISAR_DONE */

#define CSL_EVE_PC_ISAR_DONE_DONE_MASK                          (0x00000001U)
#define CSL_EVE_PC_ISAR_DONE_DONE_SHIFT                         (0U)
#define CSL_EVE_PC_ISAR_DONE_DONE_RESETVAL                      (0x00000000U)
#define CSL_EVE_PC_ISAR_DONE_DONE_MAX                           (0x00000001U)

#define CSL_EVE_PC_ISAR_DONE_RESETVAL                           (0x00000050U)

/* PC_PBAR */

#define CSL_EVE_PC_PBAR_ADDR_MASK                               (0xFFFFFFFFU)
#define CSL_EVE_PC_PBAR_ADDR_SHIFT                              (0U)
#define CSL_EVE_PC_PBAR_ADDR_RESETVAL                           (0x00000000U)
#define CSL_EVE_PC_PBAR_ADDR_MAX                                (0xffffffffU)

#define CSL_EVE_PC_PBAR_RESETVAL                                (0x00000000U)

/* PC_PBC */

#define CSL_EVE_PC_PBC_BC_MASK                                  (0x0000FFFFU)
#define CSL_EVE_PC_PBC_BC_SHIFT                                 (0U)
#define CSL_EVE_PC_PBC_BC_RESETVAL                              (0x00000000U)
#define CSL_EVE_PC_PBC_BC_MAX                                   (0x0000ffffU)

#define CSL_EVE_PC_PBC_RESETVAL                                 (0x00000000U)

/* PMEM_ED_CTL */

#define CSL_EVE_PMEM_ED_CTL_EN_MASK                             (0x00000001U)
#define CSL_EVE_PMEM_ED_CTL_EN_SHIFT                            (0U)
#define CSL_EVE_PMEM_ED_CTL_EN_RESETVAL                         (0x00000000U)
#define CSL_EVE_PMEM_ED_CTL_EN_MAX                              (0x00000001U)

#define CSL_EVE_PMEM_ED_CTL_INV_MASK                            (0x00000002U)
#define CSL_EVE_PMEM_ED_CTL_INV_SHIFT                           (1U)
#define CSL_EVE_PMEM_ED_CTL_INV_RESETVAL                        (0x00000000U)
#define CSL_EVE_PMEM_ED_CTL_INV_MAX                             (0x00000001U)

#define CSL_EVE_PMEM_ED_CTL_RESETVAL                            (0x00000000U)

/* PMEM_ED_STAT */

#define CSL_EVE_PMEM_ED_STAT_ARP32ERR_MASK                      (0x00000001U)
#define CSL_EVE_PMEM_ED_STAT_ARP32ERR_SHIFT                     (0U)
#define CSL_EVE_PMEM_ED_STAT_ARP32ERR_RESETVAL                  (0x00000000U)
#define CSL_EVE_PMEM_ED_STAT_ARP32ERR_MAX                       (0x00000001U)

#define CSL_EVE_PMEM_ED_STAT_VERR_MASK                          (0x00000002U)
#define CSL_EVE_PMEM_ED_STAT_VERR_SHIFT                         (1U)
#define CSL_EVE_PMEM_ED_STAT_VERR_RESETVAL                      (0x00000000U)
#define CSL_EVE_PMEM_ED_STAT_VERR_MAX                           (0x00000001U)

#define CSL_EVE_PMEM_ED_STAT_DMAERR_MASK                        (0x00000004U)
#define CSL_EVE_PMEM_ED_STAT_DMAERR_SHIFT                       (2U)
#define CSL_EVE_PMEM_ED_STAT_DMAERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_PMEM_ED_STAT_DMAERR_MAX                         (0x00000001U)

#define CSL_EVE_PMEM_ED_STAT_SYSERR_MASK                        (0x00000008U)
#define CSL_EVE_PMEM_ED_STAT_SYSERR_SHIFT                       (3U)
#define CSL_EVE_PMEM_ED_STAT_SYSERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_PMEM_ED_STAT_SYSERR_MAX                         (0x00000001U)

#define CSL_EVE_PMEM_ED_STAT_SYSCONNID_MASK                     (0x01FF0000U)
#define CSL_EVE_PMEM_ED_STAT_SYSCONNID_SHIFT                    (16U)
#define CSL_EVE_PMEM_ED_STAT_SYSCONNID_RESETVAL                 (0x00000000U)
#define CSL_EVE_PMEM_ED_STAT_SYSCONNID_MAX                      (0x000001ffU)

#define CSL_EVE_PMEM_ED_STAT_RESETVAL                           (0x00000000U)

/* PMEM_EDADDR */

#define CSL_EVE_PMEM_EDADDR_ADDR_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_PMEM_EDADDR_ADDR_SHIFT                          (0U)
#define CSL_EVE_PMEM_EDADDR_ADDR_RESETVAL                       (0x00000000U)
#define CSL_EVE_PMEM_EDADDR_ADDR_MAX                            (0xffffffffU)

#define CSL_EVE_PMEM_EDADDR_RESETVAL                            (0x00000000U)

/* DMEM_ED_CTL */

#define CSL_EVE_DMEM_ED_CTL_EN_MASK                             (0x00000001U)
#define CSL_EVE_DMEM_ED_CTL_EN_SHIFT                            (0U)
#define CSL_EVE_DMEM_ED_CTL_EN_RESETVAL                         (0x00000000U)
#define CSL_EVE_DMEM_ED_CTL_EN_MAX                              (0x00000001U)

#define CSL_EVE_DMEM_ED_CTL_INV_MASK                            (0x00000002U)
#define CSL_EVE_DMEM_ED_CTL_INV_SHIFT                           (1U)
#define CSL_EVE_DMEM_ED_CTL_INV_RESETVAL                        (0x00000000U)
#define CSL_EVE_DMEM_ED_CTL_INV_MAX                             (0x00000001U)

#define CSL_EVE_DMEM_ED_CTL_RESETVAL                            (0x00000000U)

/* DMEM_ED_STAT */

#define CSL_EVE_DMEM_ED_STAT_ARP32ERR_MASK                      (0x00000001U)
#define CSL_EVE_DMEM_ED_STAT_ARP32ERR_SHIFT                     (0U)
#define CSL_EVE_DMEM_ED_STAT_ARP32ERR_RESETVAL                  (0x00000000U)
#define CSL_EVE_DMEM_ED_STAT_ARP32ERR_MAX                       (0x00000001U)

#define CSL_EVE_DMEM_ED_STAT_VERR_MASK                          (0x00000002U)
#define CSL_EVE_DMEM_ED_STAT_VERR_SHIFT                         (1U)
#define CSL_EVE_DMEM_ED_STAT_VERR_RESETVAL                      (0x00000000U)
#define CSL_EVE_DMEM_ED_STAT_VERR_MAX                           (0x00000001U)

#define CSL_EVE_DMEM_ED_STAT_DMAERR_MASK                        (0x00000004U)
#define CSL_EVE_DMEM_ED_STAT_DMAERR_SHIFT                       (2U)
#define CSL_EVE_DMEM_ED_STAT_DMAERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_DMEM_ED_STAT_DMAERR_MAX                         (0x00000001U)

#define CSL_EVE_DMEM_ED_STAT_SYSERR_MASK                        (0x00000008U)
#define CSL_EVE_DMEM_ED_STAT_SYSERR_SHIFT                       (3U)
#define CSL_EVE_DMEM_ED_STAT_SYSERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_DMEM_ED_STAT_SYSERR_MAX                         (0x00000001U)

#define CSL_EVE_DMEM_ED_STAT_SYSCONNID_MASK                     (0x01FF0000U)
#define CSL_EVE_DMEM_ED_STAT_SYSCONNID_SHIFT                    (16U)
#define CSL_EVE_DMEM_ED_STAT_SYSCONNID_RESETVAL                 (0x00000000U)
#define CSL_EVE_DMEM_ED_STAT_SYSCONNID_MAX                      (0x000001ffU)

#define CSL_EVE_DMEM_ED_STAT_RESETVAL                           (0x00000000U)

/* DMEM_EDADDR */

#define CSL_EVE_DMEM_EDADDR_ADDR_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_DMEM_EDADDR_ADDR_SHIFT                          (0U)
#define CSL_EVE_DMEM_EDADDR_ADDR_RESETVAL                       (0x00000000U)
#define CSL_EVE_DMEM_EDADDR_ADDR_MAX                            (0xffffffffU)

#define CSL_EVE_DMEM_EDADDR_RESETVAL                            (0x00000000U)

/* DMEM_EDADDR_BO */

#define CSL_EVE_DMEM_EDADDR_BO_BO_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_DMEM_EDADDR_BO_BO_SHIFT                         (0U)
#define CSL_EVE_DMEM_EDADDR_BO_BO_RESETVAL                      (0x00000000U)
#define CSL_EVE_DMEM_EDADDR_BO_BO_MAX                           (0xffffffffU)

#define CSL_EVE_DMEM_EDADDR_BO_RESETVAL                         (0x00000000U)

/* WBUF_ED_CTL */

#define CSL_EVE_WBUF_ED_CTL_EN_MASK                             (0x00000001U)
#define CSL_EVE_WBUF_ED_CTL_EN_SHIFT                            (0U)
#define CSL_EVE_WBUF_ED_CTL_EN_RESETVAL                         (0x00000000U)
#define CSL_EVE_WBUF_ED_CTL_EN_MAX                              (0x00000001U)

#define CSL_EVE_WBUF_ED_CTL_INV_MASK                            (0x00000002U)
#define CSL_EVE_WBUF_ED_CTL_INV_SHIFT                           (1U)
#define CSL_EVE_WBUF_ED_CTL_INV_RESETVAL                        (0x00000000U)
#define CSL_EVE_WBUF_ED_CTL_INV_MAX                             (0x00000001U)

#define CSL_EVE_WBUF_ED_CTL_RESETVAL                            (0x00000000U)

/* WBUF_ED_STAT */

#define CSL_EVE_WBUF_ED_STAT_ARP32ERR_MASK                      (0x00000001U)
#define CSL_EVE_WBUF_ED_STAT_ARP32ERR_SHIFT                     (0U)
#define CSL_EVE_WBUF_ED_STAT_ARP32ERR_RESETVAL                  (0x00000000U)
#define CSL_EVE_WBUF_ED_STAT_ARP32ERR_MAX                       (0x00000001U)

#define CSL_EVE_WBUF_ED_STAT_VERR_MASK                          (0x00000002U)
#define CSL_EVE_WBUF_ED_STAT_VERR_SHIFT                         (1U)
#define CSL_EVE_WBUF_ED_STAT_VERR_RESETVAL                      (0x00000000U)
#define CSL_EVE_WBUF_ED_STAT_VERR_MAX                           (0x00000001U)

#define CSL_EVE_WBUF_ED_STAT_DMAERR_MASK                        (0x00000004U)
#define CSL_EVE_WBUF_ED_STAT_DMAERR_SHIFT                       (2U)
#define CSL_EVE_WBUF_ED_STAT_DMAERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_WBUF_ED_STAT_DMAERR_MAX                         (0x00000001U)

#define CSL_EVE_WBUF_ED_STAT_SYSERR_MASK                        (0x00000008U)
#define CSL_EVE_WBUF_ED_STAT_SYSERR_SHIFT                       (3U)
#define CSL_EVE_WBUF_ED_STAT_SYSERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_WBUF_ED_STAT_SYSERR_MAX                         (0x00000001U)

#define CSL_EVE_WBUF_ED_STAT_SYSCONNID_MASK                     (0x01FF0000U)
#define CSL_EVE_WBUF_ED_STAT_SYSCONNID_SHIFT                    (16U)
#define CSL_EVE_WBUF_ED_STAT_SYSCONNID_RESETVAL                 (0x00000000U)
#define CSL_EVE_WBUF_ED_STAT_SYSCONNID_MAX                      (0x000001ffU)

#define CSL_EVE_WBUF_ED_STAT_RESETVAL                           (0x00000000U)

/* WBUF_EDADDR */

#define CSL_EVE_WBUF_EDADDR_ADDR_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_WBUF_EDADDR_ADDR_SHIFT                          (0U)
#define CSL_EVE_WBUF_EDADDR_ADDR_RESETVAL                       (0x00000000U)
#define CSL_EVE_WBUF_EDADDR_ADDR_MAX                            (0xffffffffU)

#define CSL_EVE_WBUF_EDADDR_RESETVAL                            (0x00000000U)

/* WBUF_EDADDR_BO */

#define CSL_EVE_WBUF_EDADDR_BO_BO_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_WBUF_EDADDR_BO_BO_SHIFT                         (0U)
#define CSL_EVE_WBUF_EDADDR_BO_BO_RESETVAL                      (0x00000000U)
#define CSL_EVE_WBUF_EDADDR_BO_BO_MAX                           (0xffffffffU)

#define CSL_EVE_WBUF_EDADDR_BO_RESETVAL                         (0x00000000U)

/* IBUF_ED_CTL */

#define CSL_EVE_IBUF_ED_CTL_EN_MASK                             (0x00000001U)
#define CSL_EVE_IBUF_ED_CTL_EN_SHIFT                            (0U)
#define CSL_EVE_IBUF_ED_CTL_EN_RESETVAL                         (0x00000000U)
#define CSL_EVE_IBUF_ED_CTL_EN_MAX                              (0x00000001U)

#define CSL_EVE_IBUF_ED_CTL_INV_MASK                            (0x00000002U)
#define CSL_EVE_IBUF_ED_CTL_INV_SHIFT                           (1U)
#define CSL_EVE_IBUF_ED_CTL_INV_RESETVAL                        (0x00000000U)
#define CSL_EVE_IBUF_ED_CTL_INV_MAX                             (0x00000001U)

#define CSL_EVE_IBUF_ED_CTL_RESETVAL                            (0x00000000U)

/* IBUF_ED_STAT */

#define CSL_EVE_IBUF_ED_STAT_ARP32ERR_MASK                      (0x00000001U)
#define CSL_EVE_IBUF_ED_STAT_ARP32ERR_SHIFT                     (0U)
#define CSL_EVE_IBUF_ED_STAT_ARP32ERR_RESETVAL                  (0x00000000U)
#define CSL_EVE_IBUF_ED_STAT_ARP32ERR_MAX                       (0x00000001U)

#define CSL_EVE_IBUF_ED_STAT_VERR_MASK                          (0x00000002U)
#define CSL_EVE_IBUF_ED_STAT_VERR_SHIFT                         (1U)
#define CSL_EVE_IBUF_ED_STAT_VERR_RESETVAL                      (0x00000000U)
#define CSL_EVE_IBUF_ED_STAT_VERR_MAX                           (0x00000001U)

#define CSL_EVE_IBUF_ED_STAT_DMAERR_MASK                        (0x00000004U)
#define CSL_EVE_IBUF_ED_STAT_DMAERR_SHIFT                       (2U)
#define CSL_EVE_IBUF_ED_STAT_DMAERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_IBUF_ED_STAT_DMAERR_MAX                         (0x00000001U)

#define CSL_EVE_IBUF_ED_STAT_SYSERR_MASK                        (0x00000008U)
#define CSL_EVE_IBUF_ED_STAT_SYSERR_SHIFT                       (3U)
#define CSL_EVE_IBUF_ED_STAT_SYSERR_RESETVAL                    (0x00000000U)
#define CSL_EVE_IBUF_ED_STAT_SYSERR_MAX                         (0x00000001U)

#define CSL_EVE_IBUF_ED_STAT_SYSCONNID_MASK                     (0x01FF0000U)
#define CSL_EVE_IBUF_ED_STAT_SYSCONNID_SHIFT                    (16U)
#define CSL_EVE_IBUF_ED_STAT_SYSCONNID_RESETVAL                 (0x00000000U)
#define CSL_EVE_IBUF_ED_STAT_SYSCONNID_MAX                      (0x000001ffU)

#define CSL_EVE_IBUF_ED_STAT_RESETVAL                           (0x00000000U)

/* IBUF_EDADDR */

#define CSL_EVE_IBUF_EDADDR_ADDR_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_IBUF_EDADDR_ADDR_SHIFT                          (0U)
#define CSL_EVE_IBUF_EDADDR_ADDR_RESETVAL                       (0x00000000U)
#define CSL_EVE_IBUF_EDADDR_ADDR_MAX                            (0xffffffffU)

#define CSL_EVE_IBUF_EDADDR_RESETVAL                            (0x00000000U)

/* IBUF_EDADDR_BO */

#define CSL_EVE_IBUF_EDADDR_BO_BO_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_IBUF_EDADDR_BO_BO_SHIFT                         (0U)
#define CSL_EVE_IBUF_EDADDR_BO_BO_RESETVAL                      (0x00000000U)
#define CSL_EVE_IBUF_EDADDR_BO_BO_MAX                           (0xffffffffU)

#define CSL_EVE_IBUF_EDADDR_BO_RESETVAL                         (0x00000000U)

/* ED_ARP32_DISC_EN */

#define CSL_EVE_ED_ARP32_DISC_EN_EN_MASK                        (0x0000FFFFU)
#define CSL_EVE_ED_ARP32_DISC_EN_EN_SHIFT                       (0U)
#define CSL_EVE_ED_ARP32_DISC_EN_EN_RESETVAL                    (0x00000000U)
#define CSL_EVE_ED_ARP32_DISC_EN_EN_MAX                         (0x0000ffffU)

#define CSL_EVE_ED_ARP32_DISC_EN_RESETVAL                       (0x00000000U)

/* ED_OCPI_DISC_EN */

#define CSL_EVE_ED_OCPI_DISC_EN_EN_MASK                         (0x0000FFFFU)
#define CSL_EVE_ED_OCPI_DISC_EN_EN_SHIFT                        (0U)
#define CSL_EVE_ED_OCPI_DISC_EN_EN_RESETVAL                     (0x00000000U)
#define CSL_EVE_ED_OCPI_DISC_EN_EN_MAX                          (0x0000ffffU)

#define CSL_EVE_ED_OCPI_DISC_EN_RESETVAL                        (0x00000000U)

/* MSW_ERR_IRQSTS_RAW */

#define CSL_EVE_MSW_ERR_IRQSTS_RAW_EVT_MASK                     (0x0000000FU)
#define CSL_EVE_MSW_ERR_IRQSTS_RAW_EVT_SHIFT                    (0U)
#define CSL_EVE_MSW_ERR_IRQSTS_RAW_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_MSW_ERR_IRQSTS_RAW_EVT_MAX                      (0x0000000fU)

#define CSL_EVE_MSW_ERR_IRQSTS_RAW_RESETVAL                     (0x00000000U)

/* MSW_ERR_IRQSTS */

#define CSL_EVE_MSW_ERR_IRQSTS_EVT_MASK                         (0x0000000FU)
#define CSL_EVE_MSW_ERR_IRQSTS_EVT_SHIFT                        (0U)
#define CSL_EVE_MSW_ERR_IRQSTS_EVT_RESETVAL                     (0x00000000U)
#define CSL_EVE_MSW_ERR_IRQSTS_EVT_MAX                          (0x0000000fU)

#define CSL_EVE_MSW_ERR_IRQSTS_RESETVAL                         (0x00000000U)

/* MSW_ERR_IRQEN_SET */

#define CSL_EVE_MSW_ERR_IRQEN_SET_EN_MASK                       (0x0000000FU)
#define CSL_EVE_MSW_ERR_IRQEN_SET_EN_SHIFT                      (0U)
#define CSL_EVE_MSW_ERR_IRQEN_SET_EN_RESETVAL                   (0x00000000U)
#define CSL_EVE_MSW_ERR_IRQEN_SET_EN_MAX                        (0x0000000fU)

#define CSL_EVE_MSW_ERR_IRQEN_SET_RESETVAL                      (0x00000000U)

/* MSW_ERR_IRQEN_CLR */

#define CSL_EVE_MSW_ERR_IRQEN_CLR_EN_MASK                       (0x0000000FU)
#define CSL_EVE_MSW_ERR_IRQEN_CLR_EN_SHIFT                      (0U)
#define CSL_EVE_MSW_ERR_IRQEN_CLR_EN_RESETVAL                   (0x00000000U)
#define CSL_EVE_MSW_ERR_IRQEN_CLR_EN_MAX                        (0x0000000fU)

#define CSL_EVE_MSW_ERR_IRQEN_CLR_RESETVAL                      (0x00000000U)

/* ED_LCL_IRQSTS_RAW */

#define CSL_EVE_ED_LCL_IRQSTS_RAW_EVT_MASK                      (0x0000FFFFU)
#define CSL_EVE_ED_LCL_IRQSTS_RAW_EVT_SHIFT                     (0U)
#define CSL_EVE_ED_LCL_IRQSTS_RAW_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ED_LCL_IRQSTS_RAW_EVT_MAX                       (0x0000ffffU)

#define CSL_EVE_ED_LCL_IRQSTS_RAW_RESETVAL                      (0x00000000U)

/* ED_LCL_IRQSTS */

#define CSL_EVE_ED_LCL_IRQSTS_EVT_MASK                          (0x0000FFFFU)
#define CSL_EVE_ED_LCL_IRQSTS_EVT_SHIFT                         (0U)
#define CSL_EVE_ED_LCL_IRQSTS_EVT_RESETVAL                      (0x00000000U)
#define CSL_EVE_ED_LCL_IRQSTS_EVT_MAX                           (0x0000ffffU)

#define CSL_EVE_ED_LCL_IRQSTS_RESETVAL                          (0x00000000U)

/* ED_LCL_IRQEN_SET */

#define CSL_EVE_ED_LCL_IRQEN_SET_EN_MASK                        (0x0000FFFFU)
#define CSL_EVE_ED_LCL_IRQEN_SET_EN_SHIFT                       (0U)
#define CSL_EVE_ED_LCL_IRQEN_SET_EN_RESETVAL                    (0x00000000U)
#define CSL_EVE_ED_LCL_IRQEN_SET_EN_MAX                         (0x0000ffffU)

#define CSL_EVE_ED_LCL_IRQEN_SET_RESETVAL                       (0x00000000U)

/* ED_LCL_IRQEN_CLR */

#define CSL_EVE_ED_LCL_IRQEN_CLR_EN_MASK                        (0x0000FFFFU)
#define CSL_EVE_ED_LCL_IRQEN_CLR_EN_SHIFT                       (0U)
#define CSL_EVE_ED_LCL_IRQEN_CLR_EN_RESETVAL                    (0x00000000U)
#define CSL_EVE_ED_LCL_IRQEN_CLR_EN_MAX                         (0x0000ffffU)

#define CSL_EVE_ED_LCL_IRQEN_CLR_RESETVAL                       (0x00000000U)

/* ARP32_NMI_IRQSTS_RAW */

#define CSL_EVE_ARP32_NMI_IRQSTS_RAW_EVT_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_NMI_IRQSTS_RAW_EVT_SHIFT                  (0U)
#define CSL_EVE_ARP32_NMI_IRQSTS_RAW_EVT_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_NMI_IRQSTS_RAW_EVT_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_NMI_IRQSTS_RAW_RESETVAL                   (0x00000000U)

/* ARP32_NMI_IRQSTS */

#define CSL_EVE_ARP32_NMI_IRQSTS_EVT_MASK                       (0xFFFFFFFFU)
#define CSL_EVE_ARP32_NMI_IRQSTS_EVT_SHIFT                      (0U)
#define CSL_EVE_ARP32_NMI_IRQSTS_EVT_RESETVAL                   (0x00000000U)
#define CSL_EVE_ARP32_NMI_IRQSTS_EVT_MAX                        (0xffffffffU)

#define CSL_EVE_ARP32_NMI_IRQSTS_RESETVAL                       (0x00000000U)

/* ARP32_NMI_IRQEN_SET */

#define CSL_EVE_ARP32_NMI_IRQEN_SET_EN_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_NMI_IRQEN_SET_EN_SHIFT                    (0U)
#define CSL_EVE_ARP32_NMI_IRQEN_SET_EN_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_NMI_IRQEN_SET_EN_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_NMI_IRQEN_SET_RESETVAL                    (0x00000000U)

/* ARP32_NMI_IRQEN_CLR */

#define CSL_EVE_ARP32_NMI_IRQEN_CLR_EN_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_NMI_IRQEN_CLR_EN_SHIFT                    (0U)
#define CSL_EVE_ARP32_NMI_IRQEN_CLR_EN_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_NMI_IRQEN_CLR_EN_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_NMI_IRQEN_CLR_RESETVAL                    (0x00000000U)

/* ARP32_INT4_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT4_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT4_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT4_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT4_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT4_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT4_IRQSTS */

#define CSL_EVE_ARP32_INT4_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT4_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT4_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT4_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT4_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT4_IRQEN_SET */

#define CSL_EVE_ARP32_INT4_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT4_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT4_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT4_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT4_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT4_IRQEN_CLR */

#define CSL_EVE_ARP32_INT4_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT4_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT4_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT4_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT4_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_INT5_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT5_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT5_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT5_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT5_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT5_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT5_IRQSTS */

#define CSL_EVE_ARP32_INT5_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT5_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT5_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT5_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT5_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT5_IRQEN_SET */

#define CSL_EVE_ARP32_INT5_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT5_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT5_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT5_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT5_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT5_IRQEN_CLR */

#define CSL_EVE_ARP32_INT5_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT5_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT5_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT5_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT5_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_INT6_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT6_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT6_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT6_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT6_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT6_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT6_IRQSTS */

#define CSL_EVE_ARP32_INT6_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT6_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT6_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT6_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT6_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT6_IRQEN_SET */

#define CSL_EVE_ARP32_INT6_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT6_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT6_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT6_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT6_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT6_IRQEN_CLR */

#define CSL_EVE_ARP32_INT6_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT6_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT6_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT6_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT6_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_INT7_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT7_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT7_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT7_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT7_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT7_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT7_IRQSTS */

#define CSL_EVE_ARP32_INT7_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT7_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT7_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT7_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT7_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT7_IRQEN_SET */

#define CSL_EVE_ARP32_INT7_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT7_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT7_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT7_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT7_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT7_IRQEN_CLR */

#define CSL_EVE_ARP32_INT7_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT7_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT7_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT7_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT7_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_IRQWAKEEN */

#define CSL_EVE_ARP32_IRQWAKEEN_EN_MASK                         (0x00FFFFFFU)
#define CSL_EVE_ARP32_IRQWAKEEN_EN_SHIFT                        (0U)
#define CSL_EVE_ARP32_IRQWAKEEN_EN_RESETVAL                     (0x00000000U)
#define CSL_EVE_ARP32_IRQWAKEEN_EN_MAX                          (0x00ffffffU)

#define CSL_EVE_ARP32_IRQWAKEEN_RESETVAL                        (0x00000000U)

/* MMR_LOCK0 */

#define CSL_EVE_MMR_LOCK0_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK0_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK0_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK0_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK0_RESETVAL                              (0x00000000U)

/* MMR_LOCK1 */

#define CSL_EVE_MMR_LOCK1_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK1_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK1_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK1_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK1_RESETVAL                              (0x00000000U)

/* MMR_LOCK2 */

#define CSL_EVE_MMR_LOCK2_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK2_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK2_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK2_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK2_RESETVAL                              (0x00000000U)

/* MMR_LOCK3 */

#define CSL_EVE_MMR_LOCK3_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK3_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK3_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK3_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK3_RESETVAL                              (0x00000000U)

/* MMR_LOCK4 */

#define CSL_EVE_MMR_LOCK4_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK4_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK4_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK4_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK4_RESETVAL                              (0x00000000U)

/* MMR_LOCK5 */

#define CSL_EVE_MMR_LOCK5_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK5_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK5_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK5_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK5_RESETVAL                              (0x00000000U)

/* MMR_LOCK6 */

#define CSL_EVE_MMR_LOCK6_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK6_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK6_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK6_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK6_RESETVAL                              (0x00000000U)

/* MMR_LOCK7 */

#define CSL_EVE_MMR_LOCK7_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK7_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK7_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK7_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK7_RESETVAL                              (0x00000000U)

/* MMR_LOCK8 */

#define CSL_EVE_MMR_LOCK8_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK8_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK8_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK8_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK8_RESETVAL                              (0x00000000U)

/* MMR_LOCK9 */

#define CSL_EVE_MMR_LOCK9_MMR_LOCK_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MMR_LOCK9_MMR_LOCK_SHIFT                        (0U)
#define CSL_EVE_MMR_LOCK9_MMR_LOCK_RESETVAL                     (0x00000000U)
#define CSL_EVE_MMR_LOCK9_MMR_LOCK_MAX                          (0xffffffffU)

#define CSL_EVE_MMR_LOCK9_RESETVAL                              (0x00000000U)

/* MISR_CTL */

#define CSL_EVE_MISR_CTL_EN_MASK                                (0x00000007U)
#define CSL_EVE_MISR_CTL_EN_SHIFT                               (0U)
#define CSL_EVE_MISR_CTL_EN_RESETVAL                            (0x00000000U)
#define CSL_EVE_MISR_CTL_EN_MAX                                 (0x00000007U)

#define CSL_EVE_MISR_CTL_RESETVAL                               (0x00000000U)

/* MISR_CLR */

#define CSL_EVE_MISR_CLR_CLR_MASK                               (0x00000007U)
#define CSL_EVE_MISR_CLR_CLR_SHIFT                              (0U)
#define CSL_EVE_MISR_CLR_CLR_RESETVAL                           (0x00000000U)
#define CSL_EVE_MISR_CLR_CLR_MAX                                (0x00000007U)

#define CSL_EVE_MISR_CLR_RESETVAL                               (0x00000000U)

/* MISR0_A */

#define CSL_EVE_MISR0_A_SIGNATURE_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_MISR0_A_SIGNATURE_SHIFT                         (0U)
#define CSL_EVE_MISR0_A_SIGNATURE_RESETVAL                      (0x00000000U)
#define CSL_EVE_MISR0_A_SIGNATURE_MAX                           (0xffffffffU)

#define CSL_EVE_MISR0_A_RESETVAL                                (0x00000000U)

/* MISR0_D */

#define CSL_EVE_MISR0_D_SIGNATURE_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_MISR0_D_SIGNATURE_SHIFT                         (0U)
#define CSL_EVE_MISR0_D_SIGNATURE_RESETVAL                      (0x00000000U)
#define CSL_EVE_MISR0_D_SIGNATURE_MAX                           (0xffffffffU)

#define CSL_EVE_MISR0_D_RESETVAL                                (0x00000000U)

/* MISR1_A */

#define CSL_EVE_MISR1_A_SIGNATURE_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_MISR1_A_SIGNATURE_SHIFT                         (0U)
#define CSL_EVE_MISR1_A_SIGNATURE_RESETVAL                      (0x00000000U)
#define CSL_EVE_MISR1_A_SIGNATURE_MAX                           (0xffffffffU)

#define CSL_EVE_MISR1_A_RESETVAL                                (0x00000000U)

/* MISR1_D */

#define CSL_EVE_MISR1_D_SIGNATURE_MASK                          (0xFFFFFFFFU)
#define CSL_EVE_MISR1_D_SIGNATURE_SHIFT                         (0U)
#define CSL_EVE_MISR1_D_SIGNATURE_RESETVAL                      (0x00000000U)
#define CSL_EVE_MISR1_D_SIGNATURE_MAX                           (0xffffffffU)

#define CSL_EVE_MISR1_D_RESETVAL                                (0x00000000U)

/* MISR2_D0 */

#define CSL_EVE_MISR2_D0_SIGNATURE_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MISR2_D0_SIGNATURE_SHIFT                        (0U)
#define CSL_EVE_MISR2_D0_SIGNATURE_RESETVAL                     (0x00000000U)
#define CSL_EVE_MISR2_D0_SIGNATURE_MAX                          (0xffffffffU)

#define CSL_EVE_MISR2_D0_RESETVAL                               (0x00000000U)

/* MISR2_D1 */

#define CSL_EVE_MISR2_D1_SIGNATURE_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MISR2_D1_SIGNATURE_SHIFT                        (0U)
#define CSL_EVE_MISR2_D1_SIGNATURE_RESETVAL                     (0x00000000U)
#define CSL_EVE_MISR2_D1_SIGNATURE_MAX                          (0xffffffffU)

#define CSL_EVE_MISR2_D1_RESETVAL                               (0x00000000U)

/* MISR2_D2 */

#define CSL_EVE_MISR2_D2_SIGNATURE_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MISR2_D2_SIGNATURE_SHIFT                        (0U)
#define CSL_EVE_MISR2_D2_SIGNATURE_RESETVAL                     (0x00000000U)
#define CSL_EVE_MISR2_D2_SIGNATURE_MAX                          (0xffffffffU)

#define CSL_EVE_MISR2_D2_RESETVAL                               (0x00000000U)

/* MISR2_D3 */

#define CSL_EVE_MISR2_D3_SIGNATURE_MASK                         (0xFFFFFFFFU)
#define CSL_EVE_MISR2_D3_SIGNATURE_SHIFT                        (0U)
#define CSL_EVE_MISR2_D3_SIGNATURE_RESETVAL                     (0x00000000U)
#define CSL_EVE_MISR2_D3_SIGNATURE_MAX                          (0xffffffffU)

#define CSL_EVE_MISR2_D3_RESETVAL                               (0x00000000U)

/* IRQ_EOI */

#define CSL_EVE_IRQ_EOI_LINE_NUMBER_MASK                        (0x00000007U)
#define CSL_EVE_IRQ_EOI_LINE_NUMBER_SHIFT                       (0U)
#define CSL_EVE_IRQ_EOI_LINE_NUMBER_RESETVAL                    (0x00000000U)
#define CSL_EVE_IRQ_EOI_LINE_NUMBER_MAX                         (0x00000007U)

#define CSL_EVE_IRQ_EOI_RESETVAL                                (0x00000000U)

/* ED_OUT_IRQSTS_RAW */

#define CSL_EVE_ED_OUT_IRQSTS_RAW_EVT_MASK                      (0x0000FFFFU)
#define CSL_EVE_ED_OUT_IRQSTS_RAW_EVT_SHIFT                     (0U)
#define CSL_EVE_ED_OUT_IRQSTS_RAW_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ED_OUT_IRQSTS_RAW_EVT_MAX                       (0x0000ffffU)

#define CSL_EVE_ED_OUT_IRQSTS_RAW_RESETVAL                      (0x00000000U)

/* ED_OUT_IRQSTS */

#define CSL_EVE_ED_OUT_IRQSTS_EVT_MASK                          (0x0000FFFFU)
#define CSL_EVE_ED_OUT_IRQSTS_EVT_SHIFT                         (0U)
#define CSL_EVE_ED_OUT_IRQSTS_EVT_RESETVAL                      (0x00000000U)
#define CSL_EVE_ED_OUT_IRQSTS_EVT_MAX                           (0x0000ffffU)

#define CSL_EVE_ED_OUT_IRQSTS_RESETVAL                          (0x00000000U)

/* ED_OUT_IRQEN_SET */

#define CSL_EVE_ED_OUT_IRQEN_SET_EN_MASK                        (0x0000FFFFU)
#define CSL_EVE_ED_OUT_IRQEN_SET_EN_SHIFT                       (0U)
#define CSL_EVE_ED_OUT_IRQEN_SET_EN_RESETVAL                    (0x00000000U)
#define CSL_EVE_ED_OUT_IRQEN_SET_EN_MAX                         (0x0000ffffU)

#define CSL_EVE_ED_OUT_IRQEN_SET_RESETVAL                       (0x00000000U)

/* ED_OUT_IRQEN_CLR */

#define CSL_EVE_ED_OUT_IRQEN_CLR_EN_MASK                        (0x0000FFFFU)
#define CSL_EVE_ED_OUT_IRQEN_CLR_EN_SHIFT                       (0U)
#define CSL_EVE_ED_OUT_IRQEN_CLR_EN_RESETVAL                    (0x00000000U)
#define CSL_EVE_ED_OUT_IRQEN_CLR_EN_MAX                         (0x0000ffffU)

#define CSL_EVE_ED_OUT_IRQEN_CLR_RESETVAL                       (0x00000000U)

/* INT0_OUT_IRQSTS_RAW */

#define CSL_EVE_INT0_OUT_IRQSTS_RAW_EVT_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_INT0_OUT_IRQSTS_RAW_EVT_SHIFT                   (0U)
#define CSL_EVE_INT0_OUT_IRQSTS_RAW_EVT_RESETVAL                (0x00000000U)
#define CSL_EVE_INT0_OUT_IRQSTS_RAW_EVT_MAX                     (0xffffffffU)

#define CSL_EVE_INT0_OUT_IRQSTS_RAW_RESETVAL                    (0x00000000U)

/* INT0_OUT_IRQSTS */

#define CSL_EVE_INT0_OUT_IRQSTS_EVT_MASK                        (0xFFFFFFFFU)
#define CSL_EVE_INT0_OUT_IRQSTS_EVT_SHIFT                       (0U)
#define CSL_EVE_INT0_OUT_IRQSTS_EVT_RESETVAL                    (0x00000000U)
#define CSL_EVE_INT0_OUT_IRQSTS_EVT_MAX                         (0xffffffffU)

#define CSL_EVE_INT0_OUT_IRQSTS_RESETVAL                        (0x00000000U)

/* INT0_OUT_IRQEN_SET */

#define CSL_EVE_INT0_OUT_IRQEN_SET_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT0_OUT_IRQEN_SET_EN_SHIFT                     (0U)
#define CSL_EVE_INT0_OUT_IRQEN_SET_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT0_OUT_IRQEN_SET_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT0_OUT_IRQEN_SET_RESETVAL                     (0x00000000U)

/* INT0_OUT_IRQEN_CLR */

#define CSL_EVE_INT0_OUT_IRQEN_CLR_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT0_OUT_IRQEN_CLR_EN_SHIFT                     (0U)
#define CSL_EVE_INT0_OUT_IRQEN_CLR_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT0_OUT_IRQEN_CLR_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT0_OUT_IRQEN_CLR_RESETVAL                     (0x00000000U)

/* INT1_OUT_IRQSTS_RAW */

#define CSL_EVE_INT1_OUT_IRQSTS_RAW_EVT_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_INT1_OUT_IRQSTS_RAW_EVT_SHIFT                   (0U)
#define CSL_EVE_INT1_OUT_IRQSTS_RAW_EVT_RESETVAL                (0x00000000U)
#define CSL_EVE_INT1_OUT_IRQSTS_RAW_EVT_MAX                     (0xffffffffU)

#define CSL_EVE_INT1_OUT_IRQSTS_RAW_RESETVAL                    (0x00000000U)

/* INT1_OUT_IRQSTS */

#define CSL_EVE_INT1_OUT_IRQSTS_EVT_MASK                        (0xFFFFFFFFU)
#define CSL_EVE_INT1_OUT_IRQSTS_EVT_SHIFT                       (0U)
#define CSL_EVE_INT1_OUT_IRQSTS_EVT_RESETVAL                    (0x00000000U)
#define CSL_EVE_INT1_OUT_IRQSTS_EVT_MAX                         (0xffffffffU)

#define CSL_EVE_INT1_OUT_IRQSTS_RESETVAL                        (0x00000000U)

/* INT1_OUT_IRQEN_SET */

#define CSL_EVE_INT1_OUT_IRQEN_SET_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT1_OUT_IRQEN_SET_EN_SHIFT                     (0U)
#define CSL_EVE_INT1_OUT_IRQEN_SET_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT1_OUT_IRQEN_SET_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT1_OUT_IRQEN_SET_RESETVAL                     (0x00000000U)

/* INT1_OUT_IRQEN_CLR */

#define CSL_EVE_INT1_OUT_IRQEN_CLR_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT1_OUT_IRQEN_CLR_EN_SHIFT                     (0U)
#define CSL_EVE_INT1_OUT_IRQEN_CLR_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT1_OUT_IRQEN_CLR_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT1_OUT_IRQEN_CLR_RESETVAL                     (0x00000000U)

/* INT2_OUT_IRQSTS_RAW */

#define CSL_EVE_INT2_OUT_IRQSTS_RAW_EVT_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_INT2_OUT_IRQSTS_RAW_EVT_SHIFT                   (0U)
#define CSL_EVE_INT2_OUT_IRQSTS_RAW_EVT_RESETVAL                (0x00000000U)
#define CSL_EVE_INT2_OUT_IRQSTS_RAW_EVT_MAX                     (0xffffffffU)

#define CSL_EVE_INT2_OUT_IRQSTS_RAW_RESETVAL                    (0x00000000U)

/* INT2_OUT_IRQSTS */

#define CSL_EVE_INT2_OUT_IRQSTS_EVT_MASK                        (0xFFFFFFFFU)
#define CSL_EVE_INT2_OUT_IRQSTS_EVT_SHIFT                       (0U)
#define CSL_EVE_INT2_OUT_IRQSTS_EVT_RESETVAL                    (0x00000000U)
#define CSL_EVE_INT2_OUT_IRQSTS_EVT_MAX                         (0xffffffffU)

#define CSL_EVE_INT2_OUT_IRQSTS_RESETVAL                        (0x00000000U)

/* INT2_OUT_IRQEN_SET */

#define CSL_EVE_INT2_OUT_IRQEN_SET_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT2_OUT_IRQEN_SET_EN_SHIFT                     (0U)
#define CSL_EVE_INT2_OUT_IRQEN_SET_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT2_OUT_IRQEN_SET_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT2_OUT_IRQEN_SET_RESETVAL                     (0x00000000U)

/* INT2_OUT_IRQEN_CLR */

#define CSL_EVE_INT2_OUT_IRQEN_CLR_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT2_OUT_IRQEN_CLR_EN_SHIFT                     (0U)
#define CSL_EVE_INT2_OUT_IRQEN_CLR_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT2_OUT_IRQEN_CLR_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT2_OUT_IRQEN_CLR_RESETVAL                     (0x00000000U)

/* INT3_OUT_IRQSTS_RAW */

#define CSL_EVE_INT3_OUT_IRQSTS_RAW_EVT_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_INT3_OUT_IRQSTS_RAW_EVT_SHIFT                   (0U)
#define CSL_EVE_INT3_OUT_IRQSTS_RAW_EVT_RESETVAL                (0x00000000U)
#define CSL_EVE_INT3_OUT_IRQSTS_RAW_EVT_MAX                     (0xffffffffU)

#define CSL_EVE_INT3_OUT_IRQSTS_RAW_RESETVAL                    (0x00000000U)

/* INT3_OUT_IRQSTS */

#define CSL_EVE_INT3_OUT_IRQSTS_EVT_MASK                        (0xFFFFFFFFU)
#define CSL_EVE_INT3_OUT_IRQSTS_EVT_SHIFT                       (0U)
#define CSL_EVE_INT3_OUT_IRQSTS_EVT_RESETVAL                    (0x00000000U)
#define CSL_EVE_INT3_OUT_IRQSTS_EVT_MAX                         (0xffffffffU)

#define CSL_EVE_INT3_OUT_IRQSTS_RESETVAL                        (0x00000000U)

/* INT3_OUT_IRQEN_SET */

#define CSL_EVE_INT3_OUT_IRQEN_SET_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT3_OUT_IRQEN_SET_EN_SHIFT                     (0U)
#define CSL_EVE_INT3_OUT_IRQEN_SET_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT3_OUT_IRQEN_SET_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT3_OUT_IRQEN_SET_RESETVAL                     (0x00000000U)

/* INT3_OUT_IRQEN_CLR */

#define CSL_EVE_INT3_OUT_IRQEN_CLR_EN_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_INT3_OUT_IRQEN_CLR_EN_SHIFT                     (0U)
#define CSL_EVE_INT3_OUT_IRQEN_CLR_EN_RESETVAL                  (0x00000000U)
#define CSL_EVE_INT3_OUT_IRQEN_CLR_EN_MAX                       (0xffffffffU)

#define CSL_EVE_INT3_OUT_IRQEN_CLR_RESETVAL                     (0x00000000U)

/* ARP32_INT8_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT8_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT8_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT8_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT8_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT8_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT8_IRQSTS */

#define CSL_EVE_ARP32_INT8_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT8_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT8_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT8_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT8_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT8_IRQEN_SET */

#define CSL_EVE_ARP32_INT8_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT8_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT8_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT8_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT8_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT8_IRQEN_CLR */

#define CSL_EVE_ARP32_INT8_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT8_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT8_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT8_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT8_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_INT9_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT9_IRQSTS_RAW_EVT_MASK                  (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT9_IRQSTS_RAW_EVT_SHIFT                 (0U)
#define CSL_EVE_ARP32_INT9_IRQSTS_RAW_EVT_RESETVAL              (0x00000000U)
#define CSL_EVE_ARP32_INT9_IRQSTS_RAW_EVT_MAX                   (0xffffffffU)

#define CSL_EVE_ARP32_INT9_IRQSTS_RAW_RESETVAL                  (0x00000000U)

/* ARP32_INT9_IRQSTS */

#define CSL_EVE_ARP32_INT9_IRQSTS_EVT_MASK                      (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT9_IRQSTS_EVT_SHIFT                     (0U)
#define CSL_EVE_ARP32_INT9_IRQSTS_EVT_RESETVAL                  (0x00000000U)
#define CSL_EVE_ARP32_INT9_IRQSTS_EVT_MAX                       (0xffffffffU)

#define CSL_EVE_ARP32_INT9_IRQSTS_RESETVAL                      (0x00000000U)

/* ARP32_INT9_IRQEN_SET */

#define CSL_EVE_ARP32_INT9_IRQEN_SET_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT9_IRQEN_SET_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT9_IRQEN_SET_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT9_IRQEN_SET_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT9_IRQEN_SET_RESETVAL                   (0x00000000U)

/* ARP32_INT9_IRQEN_CLR */

#define CSL_EVE_ARP32_INT9_IRQEN_CLR_EN_MASK                    (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT9_IRQEN_CLR_EN_SHIFT                   (0U)
#define CSL_EVE_ARP32_INT9_IRQEN_CLR_EN_RESETVAL                (0x00000000U)
#define CSL_EVE_ARP32_INT9_IRQEN_CLR_EN_MAX                     (0xffffffffU)

#define CSL_EVE_ARP32_INT9_IRQEN_CLR_RESETVAL                   (0x00000000U)

/* ARP32_INT10_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT10_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT10_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT10_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT10_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT10_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT10_IRQSTS */

#define CSL_EVE_ARP32_INT10_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT10_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT10_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT10_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT10_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT10_IRQEN_SET */

#define CSL_EVE_ARP32_INT10_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT10_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT10_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT10_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT10_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT10_IRQEN_CLR */

#define CSL_EVE_ARP32_INT10_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT10_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT10_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT10_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT10_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* ARP32_INT11_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT11_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT11_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT11_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT11_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT11_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT11_IRQSTS */

#define CSL_EVE_ARP32_INT11_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT11_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT11_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT11_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT11_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT11_IRQEN_SET */

#define CSL_EVE_ARP32_INT11_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT11_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT11_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT11_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT11_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT11_IRQEN_CLR */

#define CSL_EVE_ARP32_INT11_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT11_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT11_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT11_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT11_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* ARP32_INT12_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT12_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT12_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT12_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT12_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT12_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT12_IRQSTS */

#define CSL_EVE_ARP32_INT12_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT12_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT12_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT12_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT12_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT12_IRQEN_SET */

#define CSL_EVE_ARP32_INT12_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT12_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT12_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT12_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT12_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT12_IRQEN_CLR */

#define CSL_EVE_ARP32_INT12_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT12_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT12_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT12_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT12_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* ARP32_INT13_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT13_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT13_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT13_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT13_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT13_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT13_IRQSTS */

#define CSL_EVE_ARP32_INT13_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT13_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT13_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT13_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT13_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT13_IRQEN_SET */

#define CSL_EVE_ARP32_INT13_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT13_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT13_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT13_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT13_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT13_IRQEN_CLR */

#define CSL_EVE_ARP32_INT13_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT13_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT13_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT13_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT13_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* ARP32_INT14_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT14_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT14_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT14_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT14_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT14_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT14_IRQSTS */

#define CSL_EVE_ARP32_INT14_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT14_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT14_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT14_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT14_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT14_IRQEN_SET */

#define CSL_EVE_ARP32_INT14_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT14_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT14_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT14_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT14_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT14_IRQEN_CLR */

#define CSL_EVE_ARP32_INT14_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT14_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT14_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT14_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT14_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* ARP32_INT15_IRQSTS_RAW */

#define CSL_EVE_ARP32_INT15_IRQSTS_RAW_EVT_MASK                 (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT15_IRQSTS_RAW_EVT_SHIFT                (0U)
#define CSL_EVE_ARP32_INT15_IRQSTS_RAW_EVT_RESETVAL             (0x00000000U)
#define CSL_EVE_ARP32_INT15_IRQSTS_RAW_EVT_MAX                  (0xffffffffU)

#define CSL_EVE_ARP32_INT15_IRQSTS_RAW_RESETVAL                 (0x00000000U)

/* ARP32_INT15_IRQSTS */

#define CSL_EVE_ARP32_INT15_IRQSTS_EVT_MASK                     (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT15_IRQSTS_EVT_SHIFT                    (0U)
#define CSL_EVE_ARP32_INT15_IRQSTS_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_ARP32_INT15_IRQSTS_EVT_MAX                      (0xffffffffU)

#define CSL_EVE_ARP32_INT15_IRQSTS_RESETVAL                     (0x00000000U)

/* ARP32_INT15_IRQEN_SET */

#define CSL_EVE_ARP32_INT15_IRQEN_SET_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT15_IRQEN_SET_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT15_IRQEN_SET_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT15_IRQEN_SET_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT15_IRQEN_SET_RESETVAL                  (0x00000000U)

/* ARP32_INT15_IRQEN_CLR */

#define CSL_EVE_ARP32_INT15_IRQEN_CLR_EN_MASK                   (0xFFFFFFFFU)
#define CSL_EVE_ARP32_INT15_IRQEN_CLR_EN_SHIFT                  (0U)
#define CSL_EVE_ARP32_INT15_IRQEN_CLR_EN_RESETVAL               (0x00000000U)
#define CSL_EVE_ARP32_INT15_IRQEN_CLR_EN_MAX                    (0xffffffffU)

#define CSL_EVE_ARP32_INT15_IRQEN_CLR_RESETVAL                  (0x00000000U)

/* GPOUT0 */

#define CSL_EVE_GPOUT0_EVT_MASK                                 (0xFFFFFFFFU)
#define CSL_EVE_GPOUT0_EVT_SHIFT                                (0U)
#define CSL_EVE_GPOUT0_EVT_RESETVAL                             (0x00000000U)
#define CSL_EVE_GPOUT0_EVT_MAX                                  (0xffffffffU)

#define CSL_EVE_GPOUT0_RESETVAL                                 (0x00000000U)

/* GPOUT0_SET */

#define CSL_EVE_GPOUT0_SET_EVT_MASK                             (0xFFFFFFFFU)
#define CSL_EVE_GPOUT0_SET_EVT_SHIFT                            (0U)
#define CSL_EVE_GPOUT0_SET_EVT_RESETVAL                         (0x00000000U)
#define CSL_EVE_GPOUT0_SET_EVT_MAX                              (0xffffffffU)

#define CSL_EVE_GPOUT0_SET_RESETVAL                             (0x00000000U)

/* GPOUT0_CLR */

#define CSL_EVE_GPOUT0_CLR_EVT_MASK                             (0xFFFFFFFFU)
#define CSL_EVE_GPOUT0_CLR_EVT_SHIFT                            (0U)
#define CSL_EVE_GPOUT0_CLR_EVT_RESETVAL                         (0x00000000U)
#define CSL_EVE_GPOUT0_CLR_EVT_MAX                              (0xffffffffU)

#define CSL_EVE_GPOUT0_CLR_RESETVAL                             (0x00000000U)

/* GPOUT0_PULSE */

#define CSL_EVE_GPOUT0_PULSE_EVT_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_GPOUT0_PULSE_EVT_SHIFT                          (0U)
#define CSL_EVE_GPOUT0_PULSE_EVT_RESETVAL                       (0x00000000U)
#define CSL_EVE_GPOUT0_PULSE_EVT_MAX                            (0xffffffffU)

#define CSL_EVE_GPOUT0_PULSE_RESETVAL                           (0x00000000U)

/* GPOUT1 */

#define CSL_EVE_GPOUT1_EVT_MASK                                 (0xFFFFFFFFU)
#define CSL_EVE_GPOUT1_EVT_SHIFT                                (0U)
#define CSL_EVE_GPOUT1_EVT_RESETVAL                             (0x00000000U)
#define CSL_EVE_GPOUT1_EVT_MAX                                  (0xffffffffU)

#define CSL_EVE_GPOUT1_RESETVAL                                 (0x00000000U)

/* GPOUT1_SET */

#define CSL_EVE_GPOUT1_SET_EVT_MASK                             (0xFFFFFFFFU)
#define CSL_EVE_GPOUT1_SET_EVT_SHIFT                            (0U)
#define CSL_EVE_GPOUT1_SET_EVT_RESETVAL                         (0x00000000U)
#define CSL_EVE_GPOUT1_SET_EVT_MAX                              (0xffffffffU)

#define CSL_EVE_GPOUT1_SET_RESETVAL                             (0x00000000U)

/* GPOUT1_CLR */

#define CSL_EVE_GPOUT1_CLR_EVT_MASK                             (0xFFFFFFFFU)
#define CSL_EVE_GPOUT1_CLR_EVT_SHIFT                            (0U)
#define CSL_EVE_GPOUT1_CLR_EVT_RESETVAL                         (0x00000000U)
#define CSL_EVE_GPOUT1_CLR_EVT_MAX                              (0xffffffffU)

#define CSL_EVE_GPOUT1_CLR_RESETVAL                             (0x00000000U)

/* GPOUT1_PULSE */

#define CSL_EVE_GPOUT1_PULSE_EVT_MASK                           (0xFFFFFFFFU)
#define CSL_EVE_GPOUT1_PULSE_EVT_SHIFT                          (0U)
#define CSL_EVE_GPOUT1_PULSE_EVT_RESETVAL                       (0x00000000U)
#define CSL_EVE_GPOUT1_PULSE_EVT_MAX                            (0xffffffffU)

#define CSL_EVE_GPOUT1_PULSE_RESETVAL                           (0x00000000U)

/* GPIN0 */

#define CSL_EVE_GPIN0_EVT_MASK                                  (0xFFFFFFFFU)
#define CSL_EVE_GPIN0_EVT_SHIFT                                 (0U)
#define CSL_EVE_GPIN0_EVT_RESETVAL                              (0x00000000U)
#define CSL_EVE_GPIN0_EVT_MAX                                   (0xffffffffU)

#define CSL_EVE_GPIN0_RESETVAL                                  (0x00000000U)

/* GPIN1 */

#define CSL_EVE_GPIN1_EVT_MASK                                  (0xFFFFFFFFU)
#define CSL_EVE_GPIN1_EVT_SHIFT                                 (0U)
#define CSL_EVE_GPIN1_EVT_RESETVAL                              (0x00000000U)
#define CSL_EVE_GPIN1_EVT_MAX                                   (0xffffffffU)

#define CSL_EVE_GPIN1_RESETVAL                                  (0x00000000U)

/* CME_DONE_GPOUT */

#define CSL_EVE_CME_DONE_GPOUT_EVT_MASK                         (0x000000FFU)
#define CSL_EVE_CME_DONE_GPOUT_EVT_SHIFT                        (0U)
#define CSL_EVE_CME_DONE_GPOUT_EVT_RESETVAL                     (0x00000000U)
#define CSL_EVE_CME_DONE_GPOUT_EVT_MAX                          (0x000000ffU)

#define CSL_EVE_CME_DONE_GPOUT_RESETVAL                         (0x00000000U)

/* CME_DONE_GPOUT_SET */

#define CSL_EVE_CME_DONE_GPOUT_SET_EVT_MASK                     (0x000000FFU)
#define CSL_EVE_CME_DONE_GPOUT_SET_EVT_SHIFT                    (0U)
#define CSL_EVE_CME_DONE_GPOUT_SET_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_CME_DONE_GPOUT_SET_EVT_MAX                      (0x000000ffU)

#define CSL_EVE_CME_DONE_GPOUT_SET_RESETVAL                     (0x00000000U)

/* CME_DONE_GPOUT_CLR */

#define CSL_EVE_CME_DONE_GPOUT_CLR_EVT_MASK                     (0x000000FFU)
#define CSL_EVE_CME_DONE_GPOUT_CLR_EVT_SHIFT                    (0U)
#define CSL_EVE_CME_DONE_GPOUT_CLR_EVT_RESETVAL                 (0x00000000U)
#define CSL_EVE_CME_DONE_GPOUT_CLR_EVT_MAX                      (0x000000ffU)

#define CSL_EVE_CME_DONE_GPOUT_CLR_RESETVAL                     (0x00000000U)

/* CME_DONE_GPOUT_PULSE */

#define CSL_EVE_CME_DONE_GPOUT_PULSE_EVT_MASK                   (0x000000FFU)
#define CSL_EVE_CME_DONE_GPOUT_PULSE_EVT_SHIFT                  (0U)
#define CSL_EVE_CME_DONE_GPOUT_PULSE_EVT_RESETVAL               (0x00000000U)
#define CSL_EVE_CME_DONE_GPOUT_PULSE_EVT_MAX                    (0x000000ffU)

#define CSL_EVE_CME_DONE_GPOUT_PULSE_RESETVAL                   (0x00000000U)

/* CME_DONE_SEL */

#define CSL_EVE_CME_DONE_SEL_SEL0_MASK                          (0x0000000FU)
#define CSL_EVE_CME_DONE_SEL_SEL0_SHIFT                         (0U)
#define CSL_EVE_CME_DONE_SEL_SEL0_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL0_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL1_MASK                          (0x000000F0U)
#define CSL_EVE_CME_DONE_SEL_SEL1_SHIFT                         (4U)
#define CSL_EVE_CME_DONE_SEL_SEL1_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL1_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL2_MASK                          (0x00000F00U)
#define CSL_EVE_CME_DONE_SEL_SEL2_SHIFT                         (8U)
#define CSL_EVE_CME_DONE_SEL_SEL2_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL2_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL3_MASK                          (0x0000F000U)
#define CSL_EVE_CME_DONE_SEL_SEL3_SHIFT                         (12U)
#define CSL_EVE_CME_DONE_SEL_SEL3_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL3_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL4_MASK                          (0x000F0000U)
#define CSL_EVE_CME_DONE_SEL_SEL4_SHIFT                         (16U)
#define CSL_EVE_CME_DONE_SEL_SEL4_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL4_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL5_MASK                          (0x00F00000U)
#define CSL_EVE_CME_DONE_SEL_SEL5_SHIFT                         (20U)
#define CSL_EVE_CME_DONE_SEL_SEL5_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL5_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL6_MASK                          (0x0F000000U)
#define CSL_EVE_CME_DONE_SEL_SEL6_SHIFT                         (24U)
#define CSL_EVE_CME_DONE_SEL_SEL6_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL6_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_SEL7_MASK                          (0xF0000000U)
#define CSL_EVE_CME_DONE_SEL_SEL7_SHIFT                         (28U)
#define CSL_EVE_CME_DONE_SEL_SEL7_RESETVAL                      (0x00000000U)
#define CSL_EVE_CME_DONE_SEL_SEL7_MAX                           (0x0000000fU)

#define CSL_EVE_CME_DONE_SEL_RESETVAL                           (0x00000000U)

/* CME_DONE_EN */

#define CSL_EVE_CME_DONE_EN_EN_MASK                             (0x000000FFU)
#define CSL_EVE_CME_DONE_EN_EN_SHIFT                            (0U)
#define CSL_EVE_CME_DONE_EN_EN_RESETVAL                         (0x00000000U)
#define CSL_EVE_CME_DONE_EN_EN_MAX                              (0x000000ffU)

#define CSL_EVE_CME_DONE_EN_RESETVAL                            (0x00000000U)

/* PM_STAT0 */

#define CSL_EVE_PM_STAT0_SIDLEREQ_MASK                          (0x00000001U)
#define CSL_EVE_PM_STAT0_SIDLEREQ_SHIFT                         (0U)
#define CSL_EVE_PM_STAT0_SIDLEREQ_RESETVAL                      (0x00000000U)
#define CSL_EVE_PM_STAT0_SIDLEREQ_MAX                           (0x00000001U)

#define CSL_EVE_PM_STAT0_SIDLEACK_MASK                          (0x00000006U)
#define CSL_EVE_PM_STAT0_SIDLEACK_SHIFT                         (1U)
#define CSL_EVE_PM_STAT0_SIDLEACK_RESETVAL                      (0x00000000U)
#define CSL_EVE_PM_STAT0_SIDLEACK_MAX                           (0x00000003U)

#define CSL_EVE_PM_STAT0_SWAKEUP_MASK                           (0x00000008U)
#define CSL_EVE_PM_STAT0_SWAKEUP_SHIFT                          (3U)
#define CSL_EVE_PM_STAT0_SWAKEUP_RESETVAL                       (0x00000000U)
#define CSL_EVE_PM_STAT0_SWAKEUP_MAX                            (0x00000001U)

#define CSL_EVE_PM_STAT0_MSTANDBY_MASK                          (0x00000010U)
#define CSL_EVE_PM_STAT0_MSTANDBY_SHIFT                         (4U)
#define CSL_EVE_PM_STAT0_MSTANDBY_RESETVAL                      (0x00000000U)
#define CSL_EVE_PM_STAT0_MSTANDBY_MAX                           (0x00000001U)

#define CSL_EVE_PM_STAT0_MWAIT_MASK                             (0x00000020U)
#define CSL_EVE_PM_STAT0_MWAIT_SHIFT                            (5U)
#define CSL_EVE_PM_STAT0_MWAIT_RESETVAL                         (0x00000000U)
#define CSL_EVE_PM_STAT0_MWAIT_MAX                              (0x00000001U)

#define CSL_EVE_PM_STAT0_OCPS_MCONNECT_MASK                     (0x00000300U)
#define CSL_EVE_PM_STAT0_OCPS_MCONNECT_SHIFT                    (8U)
#define CSL_EVE_PM_STAT0_OCPS_MCONNECT_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPS_MCONNECT_MAX                      (0x00000003U)

#define CSL_EVE_PM_STAT0_OCPS_SCONNECT_MASK                     (0x00007000U)
#define CSL_EVE_PM_STAT0_OCPS_SCONNECT_SHIFT                    (12U)
#define CSL_EVE_PM_STAT0_OCPS_SCONNECT_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPS_SCONNECT_MAX                      (0x00000007U)

#define CSL_EVE_PM_STAT0_OCPM0_MCONNECT_MASK                    (0x00030000U)
#define CSL_EVE_PM_STAT0_OCPM0_MCONNECT_SHIFT                   (16U)
#define CSL_EVE_PM_STAT0_OCPM0_MCONNECT_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPM0_MCONNECT_MAX                     (0x00000003U)

#define CSL_EVE_PM_STAT0_OCPM0_SCONNECT_MASK                    (0x00700000U)
#define CSL_EVE_PM_STAT0_OCPM0_SCONNECT_SHIFT                   (20U)
#define CSL_EVE_PM_STAT0_OCPM0_SCONNECT_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPM0_SCONNECT_MAX                     (0x00000007U)

#define CSL_EVE_PM_STAT0_OCPM1_MCONNECT_MASK                    (0x03000000U)
#define CSL_EVE_PM_STAT0_OCPM1_MCONNECT_SHIFT                   (24U)
#define CSL_EVE_PM_STAT0_OCPM1_MCONNECT_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPM1_MCONNECT_MAX                     (0x00000003U)

#define CSL_EVE_PM_STAT0_OCPM1_SCONNECT_MASK                    (0x70000000U)
#define CSL_EVE_PM_STAT0_OCPM1_SCONNECT_SHIFT                   (28U)
#define CSL_EVE_PM_STAT0_OCPM1_SCONNECT_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT0_OCPM1_SCONNECT_MAX                     (0x00000007U)

#define CSL_EVE_PM_STAT0_RESETVAL                               (0x00000000U)

/* PM_STAT1 */

#define CSL_EVE_PM_STAT1_SUBMODULE_IDLE_REQ_MASK                (0x00000001U)
#define CSL_EVE_PM_STAT1_SUBMODULE_IDLE_REQ_SHIFT               (0U)
#define CSL_EVE_PM_STAT1_SUBMODULE_IDLE_REQ_RESETVAL            (0x00000000U)
#define CSL_EVE_PM_STAT1_SUBMODULE_IDLE_REQ_MAX                 (0x00000001U)

#define CSL_EVE_PM_STAT1_TPTC0_SIDLEACK_MASK                    (0x00000002U)
#define CSL_EVE_PM_STAT1_TPTC0_SIDLEACK_SHIFT                   (1U)
#define CSL_EVE_PM_STAT1_TPTC0_SIDLEACK_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT1_TPTC0_SIDLEACK_MAX                     (0x00000001U)

#define CSL_EVE_PM_STAT1_TPTC1_SIDLEACK_MASK                    (0x00000004U)
#define CSL_EVE_PM_STAT1_TPTC1_SIDLEACK_SHIFT                   (2U)
#define CSL_EVE_PM_STAT1_TPTC1_SIDLEACK_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT1_TPTC1_SIDLEACK_MAX                     (0x00000001U)

#define CSL_EVE_PM_STAT1_TPCC_SIDLEACK_MASK                     (0x00000008U)
#define CSL_EVE_PM_STAT1_TPCC_SIDLEACK_SHIFT                    (3U)
#define CSL_EVE_PM_STAT1_TPCC_SIDLEACK_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT1_TPCC_SIDLEACK_MAX                      (0x00000001U)

#define CSL_EVE_PM_STAT1_SCTM_SIDLEACK_MASK                     (0x00000010U)
#define CSL_EVE_PM_STAT1_SCTM_SIDLEACK_SHIFT                    (4U)
#define CSL_EVE_PM_STAT1_SCTM_SIDLEACK_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT1_SCTM_SIDLEACK_MAX                      (0x00000001U)

#define CSL_EVE_PM_STAT1_MMU0_SIDLEACK_MASK                     (0x00000020U)
#define CSL_EVE_PM_STAT1_MMU0_SIDLEACK_SHIFT                    (5U)
#define CSL_EVE_PM_STAT1_MMU0_SIDLEACK_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT1_MMU0_SIDLEACK_MAX                      (0x00000001U)

#define CSL_EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_MASK              (0x00000040U)
#define CSL_EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_SHIFT             (6U)
#define CSL_EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_RESETVAL          (0x00000000U)
#define CSL_EVE_PM_STAT1_MMU0_CONFIG_SIDLEACK_MAX               (0x00000001U)

#define CSL_EVE_PM_STAT1_MMU1_SIDLEACK_MASK                     (0x00000080U)
#define CSL_EVE_PM_STAT1_MMU1_SIDLEACK_SHIFT                    (7U)
#define CSL_EVE_PM_STAT1_MMU1_SIDLEACK_RESETVAL                 (0x00000000U)
#define CSL_EVE_PM_STAT1_MMU1_SIDLEACK_MAX                      (0x00000001U)

#define CSL_EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_MASK              (0x00000100U)
#define CSL_EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_SHIFT             (8U)
#define CSL_EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_RESETVAL          (0x00000000U)
#define CSL_EVE_PM_STAT1_MMU1_CONFIG_SIDLEACK_MAX               (0x00000001U)

#define CSL_EVE_PM_STAT1_L2_EVE_SIDLEACK_MASK                   (0x00000200U)
#define CSL_EVE_PM_STAT1_L2_EVE_SIDLEACK_SHIFT                  (9U)
#define CSL_EVE_PM_STAT1_L2_EVE_SIDLEACK_RESETVAL               (0x00000000U)
#define CSL_EVE_PM_STAT1_L2_EVE_SIDLEACK_MAX                    (0x00000001U)

#define CSL_EVE_PM_STAT1_SMSET_SIDLEACK_MASK                    (0x00000400U)
#define CSL_EVE_PM_STAT1_SMSET_SIDLEACK_SHIFT                   (10U)
#define CSL_EVE_PM_STAT1_SMSET_SIDLEACK_RESETVAL                (0x00000000U)
#define CSL_EVE_PM_STAT1_SMSET_SIDLEACK_MAX                     (0x00000001U)

#define CSL_EVE_PM_STAT1_EVE_CTRL_SIDLEACK_MASK                 (0x00000800U)
#define CSL_EVE_PM_STAT1_EVE_CTRL_SIDLEACK_SHIFT                (11U)
#define CSL_EVE_PM_STAT1_EVE_CTRL_SIDLEACK_RESETVAL             (0x00000000U)
#define CSL_EVE_PM_STAT1_EVE_CTRL_SIDLEACK_MAX                  (0x00000001U)

#define CSL_EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_MASK               (0x00001000U)
#define CSL_EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_SHIFT              (12U)
#define CSL_EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_RESETVAL           (0x00000000U)
#define CSL_EVE_PM_STAT1_EVE_PCACHE_OCP_BUSY_MAX                (0x00000001U)

#define CSL_EVE_PM_STAT1_TPTC0_MWAIT_MASK                       (0x00002000U)
#define CSL_EVE_PM_STAT1_TPTC0_MWAIT_SHIFT                      (13U)
#define CSL_EVE_PM_STAT1_TPTC0_MWAIT_RESETVAL                   (0x00000000U)
#define CSL_EVE_PM_STAT1_TPTC0_MWAIT_MAX                        (0x00000001U)

#define CSL_EVE_PM_STAT1_TPTC1_MWAIT_MASK                       (0x00004000U)
#define CSL_EVE_PM_STAT1_TPTC1_MWAIT_SHIFT                      (14U)
#define CSL_EVE_PM_STAT1_TPTC1_MWAIT_RESETVAL                   (0x00000000U)
#define CSL_EVE_PM_STAT1_TPTC1_MWAIT_MAX                        (0x00000001U)

#define CSL_EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_MASK             (0x00008000U)
#define CSL_EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_SHIFT            (15U)
#define CSL_EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_RESETVAL         (0x00000000U)
#define CSL_EVE_PM_STAT1_EVE_IDLE_INTR_DISABLE_MAX              (0x00000001U)

#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_MASK              (0x00010000U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_SHIFT             (16U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_RESETVAL          (0x00000000U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_REQ_MAX               (0x00000001U)

#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_MASK              (0x00020000U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_SHIFT             (17U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_RESETVAL          (0x00000000U)
#define CSL_EVE_PM_STAT1_IDLE_SDISCONNECT_ACK_MAX               (0x00000001U)

#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_MASK               (0x00040000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_SHIFT              (18U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_RESETVAL           (0x00000000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM0_MAX                (0x00000001U)

#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_MASK               (0x00080000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_SHIFT              (19U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_RESETVAL           (0x00000000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCREQ_OCPM1_MAX                (0x00000001U)

#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM0_MASK               (0x00300000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM0_SHIFT              (20U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM0_RESETVAL           (0x00000000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM0_MAX                (0x00000003U)

#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM1_MASK               (0x00C00000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM1_SHIFT              (22U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM1_RESETVAL           (0x00000000U)
#define CSL_EVE_PM_STAT1_STBY_MDISCACK_OCPM1_MAX                (0x00000003U)

#define CSL_EVE_PM_STAT1_RESETVAL                               (0x00000000U)

/* DBGOUT */

#define CSL_EVE_DBGOUT_GROUP_MASK                               (0x0000000FU)
#define CSL_EVE_DBGOUT_GROUP_SHIFT                              (0U)
#define CSL_EVE_DBGOUT_GROUP_RESETVAL                           (0x00000000U)
#define CSL_EVE_DBGOUT_GROUP_MAX                                (0x0000000fU)

#define CSL_EVE_DBGOUT_VALUE_MASK                               (0xFFFFFF00U)
#define CSL_EVE_DBGOUT_VALUE_SHIFT                              (8U)
#define CSL_EVE_DBGOUT_VALUE_RESETVAL                           (0x00000000U)
#define CSL_EVE_DBGOUT_VALUE_MAX                                (0x00ffffffU)

#define CSL_EVE_DBGOUT_RESETVAL                                 (0x00000000U)

/* TEST */

#define CSL_EVE_TEST_VAL_MASK                                   (0xFFFFFFFFU)
#define CSL_EVE_TEST_VAL_SHIFT                                  (0U)
#define CSL_EVE_TEST_VAL_RESETVAL                               (0x00000000U)
#define CSL_EVE_TEST_VAL_MAX                                    (0xffffffffU)

#define CSL_EVE_TEST_RESETVAL                                   (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
