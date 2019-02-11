/********************************************************************
 * Copyright (C) 2013-2017 Texas Instruments Incorporated.
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
#ifndef CSLR_A15_H_
#define CSLR_A15_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for DBG
**************************************************************************/
typedef struct {
    volatile Uint32 DBGDIDR;
    volatile Uint8  RSVD0[20];
    volatile Uint32 DBGWFAR;
    volatile Uint32 DBGVCR;
    volatile Uint8  RSVD1[4];
    volatile Uint32 DBGECR;
    volatile Uint8  RSVD2[88];
    volatile Uint32 DBGDTRRX;
    volatile Uint32 DBGPCSR_0;
    volatile Uint32 DBGDSCR;
    volatile Uint32 DBGDTRTX;
    volatile Uint32 DBGDRCR;
    volatile Uint32 DBGEACR;
    volatile Uint8  RSVD3[8];
    volatile Uint32 DBGPCSR_1;
    volatile Uint32 DBGCIDSR;
    volatile Uint32 DBGVIDSR;
    volatile Uint8  RSVD4[84];
    volatile Uint32 DBGBVR0;
    volatile Uint32 DBGBVR1;
    volatile Uint32 DBGBVR2;
    volatile Uint32 DBGBVR3;
    volatile Uint32 DBGBVR4;
    volatile Uint32 DBGBVR5;
    volatile Uint8  RSVD5[40];
    volatile Uint32 DBGBCR0;
    volatile Uint32 DBGBCR1;
    volatile Uint32 DBGBCR2;
    volatile Uint32 DBGBCR3;
    volatile Uint32 DBGBCR4;
    volatile Uint32 DBGBCR5;
    volatile Uint8  RSVD6[40];
    volatile Uint32 DBGWVR0;
    volatile Uint32 DBGWVR1;
    volatile Uint32 DBGWVR2;
    volatile Uint32 DBGWVR3;
    volatile Uint8  RSVD7[48];
    volatile Uint32 DBGWCR0;
    volatile Uint32 DBGWCR1;
    volatile Uint32 DBGWCR2;
    volatile Uint32 DBGWCR3;
    volatile Uint8  RSVD8[128];
    volatile Uint32 DBGBXVR0;
    volatile Uint32 DBGBXVR1;
    volatile Uint8  RSVD9[168];
    volatile Uint32 DBGOSLAR;
    volatile Uint32 DBGOSLSR;
    volatile Uint8  RSVD10[8];
    volatile Uint32 DBGPRCR;
    volatile Uint32 DBGPRSR;
    volatile Uint8  RSVD11[2536];
    volatile Uint32 MIDR;
    volatile Uint32 CTR;
    volatile Uint32 TCMTR;
    volatile Uint32 TLBTR;
    volatile Uint32 MPUIR;
    volatile Uint32 MPIDR;
    volatile Uint32 REVIDR;
    volatile Uint8  RSVD12[4];
    volatile Uint32 ID_PFR0;
    volatile Uint32 ID_PFR1;
    volatile Uint32 ID_DFR0;
    volatile Uint32 ID_AFR0;
    volatile Uint32 ID_MMFR0;
    volatile Uint32 ID_MMFR1;
    volatile Uint32 ID_MMFR2;
    volatile Uint32 ID_MMFR3;
    volatile Uint32 ID_ISAR0;
    volatile Uint32 ID_ISAR1;
    volatile Uint32 ID_ISAR2;
    volatile Uint32 ID_ISAR3;
    volatile Uint32 ID_ISAR4;
    volatile Uint32 ID_ISAR5;
    volatile Uint8  RSVD13[416];
    volatile Uint32 DBGITOCTRL;
    volatile Uint32 DBGITISR;
    volatile Uint32 DBGITCTRL;
    volatile Uint8  RSVD14[156];
    volatile Uint32 DBGCLAIMSET;
    volatile Uint32 DBGCLAIMCLR;
    volatile Uint8  RSVD15[8];
    volatile Uint32 DBGLAR;
    volatile Uint32 DBGLSR;
    volatile Uint32 DBGAUTHSTATUS;
    volatile Uint8  RSVD16[4];
    volatile Uint32 DBGDEVID2;
    volatile Uint32 DBGDEVID1;
    volatile Uint32 DBGDEVID0;
    volatile Uint32 DBGDEVTYPE;
    volatile Uint32 DBGPID4;
    volatile Uint8  RSVD17[12];
    volatile Uint32 DBGPID0;
    volatile Uint32 DBGPID1;
    volatile Uint32 DBGPID2;
    volatile Uint32 DBGPID3;
    volatile Uint32 DBGCID0;
    volatile Uint32 DBGCID1;
    volatile Uint32 DBGCID2;
    volatile Uint32 DBGCID3;
} CSL_A15DbgRegs;


/**************************************************************************
* Register Overlay Structure for PMX
**************************************************************************/
typedef struct {
    volatile Uint32 PMXEVCNTR0;
    volatile Uint32 PMXEVCNTR1;
    volatile Uint32 PMXEVCNTR2;
    volatile Uint32 PMXEVCNTR3;
    volatile Uint32 PMXEVCNTR4;
    volatile Uint32 PMXEVCNTR5;
    volatile Uint8  RSVD0[100];
    volatile Uint32 PMCCNTR;
    volatile Uint8  RSVD1[896];
    volatile Uint32 PMXEVTYPER0;
    volatile Uint32 PMXEVTYPER1;
    volatile Uint32 PMXEVTYPER2;
    volatile Uint32 PMXEVTYPER3;
    volatile Uint32 PMXEVTYPER4;
    volatile Uint32 PMXEVTYPER5;
    volatile Uint8  RSVD2[100];
    volatile Uint32 PMCCFILTR;
    volatile Uint8  RSVD3[1920];
    volatile Uint32 PMCNTENSET;
    volatile Uint8  RSVD4[28];
    volatile Uint32 PMCNTENCLR;
    volatile Uint8  RSVD5[28];
    volatile Uint32 PMINTENSET;
    volatile Uint8  RSVD6[28];
    volatile Uint32 PMINTENCLR;
    volatile Uint8  RSVD7[28];
    volatile Uint32 PMOVSR;
    volatile Uint8  RSVD8[28];
    volatile Uint32 PMSWINC;
    volatile Uint8  RSVD9[348];
    volatile Uint32 PMCFGR;
    volatile Uint32 PMCR;
    volatile Uint32 PMUSERENR;
    volatile Uint8  RSVD10[20];
    volatile Uint32 PMCEID0;
    volatile Uint32 PMCEID1;
    volatile Uint8  RSVD11[392];
    volatile Uint32 PMLAR;
    volatile Uint32 PMLSR;
    volatile Uint32 PMAUTHSTATUS;
    volatile Uint8  RSVD12[16];
    volatile Uint32 PMDEVTYPE;
    volatile Uint32 PMPID4;
    volatile Uint32 PMPID5;
    volatile Uint32 PMPID6;
    volatile Uint32 PMPID7;
    volatile Uint32 PMPID0;
    volatile Uint32 PMPID1;
    volatile Uint32 PMPID2;
    volatile Uint32 PMPID3;
    volatile Uint32 PMCID0;
    volatile Uint32 PMCID1;
    volatile Uint32 PMCID2;
    volatile Uint32 PMCID3;
} CSL_A15PmxRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    CSL_A15PmxRegs	PMX;
    volatile Uint8  RSVD13[61440];
    CSL_A15DbgRegs	DBG;
} CSL_A15Regs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* DBGDIDR */
#define CSL_A15_DBGDIDR                                         (0x10000U)

/* DBGWFAR */
#define CSL_A15_DBGWFAR                                         (0x10018U)

/* DBGVCR */
#define CSL_A15_DBGVCR                                          (0x1001CU)

/* DBGECR */
#define CSL_A15_DBGECR                                          (0x10024U)

/* DBGDTRRX */
#define CSL_A15_DBGDTRRX                                        (0x10080U)

/* DBGITR */
#define CSL_A15_DBGITR                                          (0x10084U)

/* DBGPCSR_0 */
#define CSL_A15_DBGPCSR_0                                       (0x10084U)

/* DBGDSCR */
#define CSL_A15_DBGDSCR                                         (0x10088U)

/* DBGDTRTX */
#define CSL_A15_DBGDTRTX                                        (0x1008CU)

/* DBGDRCR */
#define CSL_A15_DBGDRCR                                         (0x10090U)

/* DBGEACR */
#define CSL_A15_DBGEACR                                         (0x10094U)

/* DBGPCSR_1 */
#define CSL_A15_DBGPCSR_1                                       (0x100A0U)

/* DBGCIDSR */
#define CSL_A15_DBGCIDSR                                        (0x100A4U)

/* DBGVIDSR */
#define CSL_A15_DBGVIDSR                                        (0x100A8U)

/* DBGBVR0 */
#define CSL_A15_DBGBVR0                                         (0x10100U)

/* DBGBVR1 */
#define CSL_A15_DBGBVR1                                         (0x10104U)

/* DBGBVR2 */
#define CSL_A15_DBGBVR2                                         (0x10108U)

/* DBGBVR3 */
#define CSL_A15_DBGBVR3                                         (0x1010CU)

/* DBGBVR4 */
#define CSL_A15_DBGBVR4                                         (0x10110U)

/* DBGBVR5 */
#define CSL_A15_DBGBVR5                                         (0x10114U)

/* DBGBCR0 */
#define CSL_A15_DBGBCR0                                         (0x10140U)

/* DBGBCR1 */
#define CSL_A15_DBGBCR1                                         (0x10144U)

/* DBGBCR2 */
#define CSL_A15_DBGBCR2                                         (0x10148U)

/* DBGBCR3 */
#define CSL_A15_DBGBCR3                                         (0x1014CU)

/* DBGBCR4 */
#define CSL_A15_DBGBCR4                                         (0x10150U)

/* DBGBCR5 */
#define CSL_A15_DBGBCR5                                         (0x10154U)

/* DBGWVR0 */
#define CSL_A15_DBGWVR0                                         (0x10180U)

/* DBGWVR1 */
#define CSL_A15_DBGWVR1                                         (0x10184U)

/* DBGWVR2 */
#define CSL_A15_DBGWVR2                                         (0x10188U)

/* DBGWVR3 */
#define CSL_A15_DBGWVR3                                         (0x1018CU)

/* DBGWCR0 */
#define CSL_A15_DBGWCR0                                         (0x101C0U)

/* DBGWCR1 */
#define CSL_A15_DBGWCR1                                         (0x101C4U)

/* DBGWCR2 */
#define CSL_A15_DBGWCR2                                         (0x101C8U)

/* DBGWCR3 */
#define CSL_A15_DBGWCR3                                         (0x101CCU)

/* DBGBXVR0 */
#define CSL_A15_DBGBXVR0                                        (0x10250U)

/* DBGBXVR1 */
#define CSL_A15_DBGBXVR1                                        (0x10254U)

/* DBGOSLAR */
#define CSL_A15_DBGOSLAR                                        (0x10300U)

/* DBGOSLSR */
#define CSL_A15_DBGOSLSR                                        (0x10304U)

/* DBGPRCR */
#define CSL_A15_DBGPRCR                                         (0x10310U)

/* DBGPRSR */
#define CSL_A15_DBGPRSR                                         (0x10314U)

/* MIDR */
#define CSL_A15_MIDR                                            (0x10D00U)

/* CTR */
#define CSL_A15_CTR                                             (0x10D04U)

/* TCMTR */
#define CSL_A15_TCMTR                                           (0x10D08U)

/* TLBTR */
#define CSL_A15_TLBTR                                           (0x10D0CU)

/* MPUIR */
#define CSL_A15_MPUIR                                           (0x10D10U)

/* MPIDR */
#define CSL_A15_MPIDR                                           (0x10D14U)

/* REVIDR */
#define CSL_A15_REVIDR                                          (0x10D18U)

/* ID_PFR0 */
#define CSL_A15_ID_PFR0                                         (0x10D20U)

/* ID_PFR1 */
#define CSL_A15_ID_PFR1                                         (0x10D24U)

/* ID_DFR0 */
#define CSL_A15_ID_DFR0                                         (0x10D28U)

/* ID_AFR0 */
#define CSL_A15_ID_AFR0                                         (0x10D2CU)

/* ID_MMFR0 */
#define CSL_A15_ID_MMFR0                                        (0x10D30U)

/* ID_MMFR1 */
#define CSL_A15_ID_MMFR1                                        (0x10D34U)

/* ID_MMFR2 */
#define CSL_A15_ID_MMFR2                                        (0x10D38U)

/* ID_MMFR3 */
#define CSL_A15_ID_MMFR3                                        (0x10D3CU)

/* ID_ISAR0 */
#define CSL_A15_ID_ISAR0                                        (0x10D40U)

/* ID_ISAR1 */
#define CSL_A15_ID_ISAR1                                        (0x10D44U)

/* ID_ISAR2 */
#define CSL_A15_ID_ISAR2                                        (0x10D48U)

/* ID_ISAR3 */
#define CSL_A15_ID_ISAR3                                        (0x10D4CU)

/* ID_ISAR4 */
#define CSL_A15_ID_ISAR4                                        (0x10D50U)

/* ID_ISAR5 */
#define CSL_A15_ID_ISAR5                                        (0x10D54U)

/* DBGITOCTRL */
#define CSL_A15_DBGITOCTRL                                      (0x10EF8U)

/* DBGITISR */
#define CSL_A15_DBGITISR                                        (0x10EFCU)

/* DBGITCTRL */
#define CSL_A15_DBGITCTRL                                       (0x10F00U)

/* DBGCLAIMSET */
#define CSL_A15_DBGCLAIMSET                                     (0x10FA0U)

/* DBGCLAIMCLR */
#define CSL_A15_DBGCLAIMCLR                                     (0x10FA4U)

/* DBGLAR */
#define CSL_A15_DBGLAR                                          (0x10FB0U)

/* DBGLSR */
#define CSL_A15_DBGLSR                                          (0x10FB4U)

/* DBGAUTHSTATUS */
#define CSL_A15_DBGAUTHSTATUS                                   (0x10FB8U)

/* DBGDEVID2 */
#define CSL_A15_DBGDEVID2                                       (0x10FC0U)

/* DBGDEVID1 */
#define CSL_A15_DBGDEVID1                                       (0x10FC4U)

/* DBGDEVID0 */
#define CSL_A15_DBGDEVID0                                       (0x10FC8U)

/* DBGDEVTYPE */
#define CSL_A15_DBGDEVTYPE                                      (0x10FCCU)

/* DBGPID4 */
#define CSL_A15_DBGPID4                                         (0x10FD0U)

/* DBGPID0 */
#define CSL_A15_DBGPID0                                         (0x10FE0U)

/* DBGPID1 */
#define CSL_A15_DBGPID1                                         (0x10FE4U)

/* DBGPID2 */
#define CSL_A15_DBGPID2                                         (0x10FE8U)

/* DBGPID3 */
#define CSL_A15_DBGPID3                                         (0x10FECU)

/* DBGCID0 */
#define CSL_A15_DBGCID0                                         (0x10FF0U)

/* DBGCID1 */
#define CSL_A15_DBGCID1                                         (0x10FF4U)

/* DBGCID2 */
#define CSL_A15_DBGCID2                                         (0x10FF8U)

/* DBGCID3 */
#define CSL_A15_DBGCID3                                         (0x10FFCU)

/* PMXEVCNTR0 */
#define CSL_A15_PMXEVCNTR0                                      (0x0U)

/* PMXEVCNTR1 */
#define CSL_A15_PMXEVCNTR1                                      (0x4U)

/* PMXEVCNTR2 */
#define CSL_A15_PMXEVCNTR2                                      (0x8U)

/* PMXEVCNTR3 */
#define CSL_A15_PMXEVCNTR3                                      (0xCU)

/* PMXEVCNTR4 */
#define CSL_A15_PMXEVCNTR4                                      (0x10U)

/* PMXEVCNTR5 */
#define CSL_A15_PMXEVCNTR5                                      (0x14U)

/* PMCCNTR */
#define CSL_A15_PMCCNTR                                         (0x7CU)

/* PMXEVTYPER0 */
#define CSL_A15_PMXEVTYPER0                                     (0x400U)

/* PMXEVTYPER1 */
#define CSL_A15_PMXEVTYPER1                                     (0x404U)

/* PMXEVTYPER2 */
#define CSL_A15_PMXEVTYPER2                                     (0x408U)

/* PMXEVTYPER3 */
#define CSL_A15_PMXEVTYPER3                                     (0x40CU)

/* PMXEVTYPER4 */
#define CSL_A15_PMXEVTYPER4                                     (0x410U)

/* PMXEVTYPER5 */
#define CSL_A15_PMXEVTYPER5                                     (0x414U)

/* PMCCFILTR */
#define CSL_A15_PMCCFILTR                                       (0x47CU)

/* PMCNTENSET */
#define CSL_A15_PMCNTENSET                                      (0xC00U)

/* PMCNTENCLR */
#define CSL_A15_PMCNTENCLR                                      (0xC20U)

/* PMINTENSET */
#define CSL_A15_PMINTENSET                                      (0xC40U)

/* PMINTENCLR */
#define CSL_A15_PMINTENCLR                                      (0xC60U)

/* PMOVSR */
#define CSL_A15_PMOVSR                                          (0xC80U)

/* PMSWINC */
#define CSL_A15_PMSWINC                                         (0xCA0U)

/* PMCFGR */
#define CSL_A15_PMCFGR                                          (0xE00U)

/* PMCR */
#define CSL_A15_PMCR                                            (0xE04U)

/* PMUSERENR */
#define CSL_A15_PMUSERENR                                       (0xE08U)

/* PMCEID0 */
#define CSL_A15_PMCEID0                                         (0xE20U)

/* PMCEID1 */
#define CSL_A15_PMCEID1                                         (0xE24U)

/* PMLAR */
#define CSL_A15_PMLAR                                           (0xFB0U)

/* PMLSR */
#define CSL_A15_PMLSR                                           (0xFB4U)

/* PMAUTHSTATUS */
#define CSL_A15_PMAUTHSTATUS                                    (0xFB8U)

/* PMDEVTYPE */
#define CSL_A15_PMDEVTYPE                                       (0xFCCU)

/* PMPID4 */
#define CSL_A15_PMPID4                                          (0xFD0U)

/* PMPID5 */
#define CSL_A15_PMPID5                                          (0xFD4U)

/* PMPID6 */
#define CSL_A15_PMPID6                                          (0xFD8U)

/* PMPID7 */
#define CSL_A15_PMPID7                                          (0xFDCU)

/* PMPID0 */
#define CSL_A15_PMPID0                                          (0xFE0U)

/* PMPID1 */
#define CSL_A15_PMPID1                                          (0xFE4U)

/* PMPID2 */
#define CSL_A15_PMPID2                                          (0xFE8U)

/* PMPID3 */
#define CSL_A15_PMPID3                                          (0xFECU)

/* PMCID0 */
#define CSL_A15_PMCID0                                          (0xFF0U)

/* PMCID1 */
#define CSL_A15_PMCID1                                          (0xFF4U)

/* PMCID2 */
#define CSL_A15_PMCID2                                          (0xFF8U)

/* PMCID3 */
#define CSL_A15_PMCID3                                          (0xFFCU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* DBGDIDR */

#define CSL_A15_DBGDIDR_WRPS_MASK                               (0xF0000000U)
#define CSL_A15_DBGDIDR_WRPS_SHIFT                              (28U)
#define CSL_A15_DBGDIDR_WRPS_RESETVAL                           (0x00000003U)
#define CSL_A15_DBGDIDR_WRPS_MAX                                (0x0000000fU)

#define CSL_A15_DBGDIDR_BRPS_MASK                               (0x0F000000U)
#define CSL_A15_DBGDIDR_BRPS_SHIFT                              (24U)
#define CSL_A15_DBGDIDR_BRPS_RESETVAL                           (0x00000005U)
#define CSL_A15_DBGDIDR_BRPS_MAX                                (0x0000000fU)

#define CSL_A15_DBGDIDR_CTX_CMPS_MASK                           (0x00F00000U)
#define CSL_A15_DBGDIDR_CTX_CMPS_SHIFT                          (20U)
#define CSL_A15_DBGDIDR_CTX_CMPS_RESETVAL                       (0x00000001U)
#define CSL_A15_DBGDIDR_CTX_CMPS_MAX                            (0x0000000fU)

#define CSL_A15_DBGDIDR_VERSION_MASK                            (0x000F0000U)
#define CSL_A15_DBGDIDR_VERSION_SHIFT                           (16U)
#define CSL_A15_DBGDIDR_VERSION_RESETVAL                        (0x00000004U)
#define CSL_A15_DBGDIDR_VERSION_MAX                             (0x0000000fU)

#define CSL_A15_DBGDIDR_DEVID_MASK                              (0x00008000U)
#define CSL_A15_DBGDIDR_DEVID_SHIFT                             (15U)
#define CSL_A15_DBGDIDR_DEVID_RESETVAL                          (0x00000001U)
#define CSL_A15_DBGDIDR_DEVID_MAX                               (0x00000001U)

#define CSL_A15_DBGDIDR_NSUHD_MASK                              (0x00004000U)
#define CSL_A15_DBGDIDR_NSUHD_SHIFT                             (14U)
#define CSL_A15_DBGDIDR_NSUHD_RESETVAL                          (0x00000001U)
#define CSL_A15_DBGDIDR_NSUHD_MAX                               (0x00000001U)

#define CSL_A15_DBGDIDR_PCSR_MASK                               (0x00002000U)
#define CSL_A15_DBGDIDR_PCSR_SHIFT                              (13U)
#define CSL_A15_DBGDIDR_PCSR_RESETVAL                           (0x00000001U)
#define CSL_A15_DBGDIDR_PCSR_MAX                                (0x00000001U)

#define CSL_A15_DBGDIDR_SE_MASK                                 (0x00001000U)
#define CSL_A15_DBGDIDR_SE_SHIFT                                (12U)
#define CSL_A15_DBGDIDR_SE_RESETVAL                             (0x00000001U)
#define CSL_A15_DBGDIDR_SE_MAX                                  (0x00000001U)

#define CSL_A15_DBGDIDR_VARIANT_MASK                            (0x000000F0U)
#define CSL_A15_DBGDIDR_VARIANT_SHIFT                           (4U)
#define CSL_A15_DBGDIDR_VARIANT_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDIDR_VARIANT_MAX                             (0x0000000fU)

#define CSL_A15_DBGDIDR_REVISION_MASK                           (0x0000000FU)
#define CSL_A15_DBGDIDR_REVISION_SHIFT                          (0U)
#define CSL_A15_DBGDIDR_REVISION_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGDIDR_REVISION_MAX                            (0x0000000fU)

#define CSL_A15_DBGDIDR_RESETVAL                                (0x3514f000U)

/* DBGWFAR */

#define CSL_A15_DBGWFAR_IAPLUSOFFSET_MASK                       (0xFFFFFFFFU)
#define CSL_A15_DBGWFAR_IAPLUSOFFSET_SHIFT                      (0U)
#define CSL_A15_DBGWFAR_IAPLUSOFFSET_RESETVAL                   (0x00000000U)
#define CSL_A15_DBGWFAR_IAPLUSOFFSET_MAX                        (0xffffffffU)

#define CSL_A15_DBGWFAR_RESETVAL                                (0x00000000U)

/* DBGVCR */

#define CSL_A15_DBGVCR_NSF_MASK                                 (0x80000000U)
#define CSL_A15_DBGVCR_NSF_SHIFT                                (31U)
#define CSL_A15_DBGVCR_NSF_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSF_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSI_MASK                                 (0x40000000U)
#define CSL_A15_DBGVCR_NSI_SHIFT                                (30U)
#define CSL_A15_DBGVCR_NSI_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSI_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSD_MASK                                 (0x10000000U)
#define CSL_A15_DBGVCR_NSD_SHIFT                                (28U)
#define CSL_A15_DBGVCR_NSD_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSD_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSP_MASK                                 (0x08000000U)
#define CSL_A15_DBGVCR_NSP_SHIFT                                (27U)
#define CSL_A15_DBGVCR_NSP_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSP_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSS_MASK                                 (0x04000000U)
#define CSL_A15_DBGVCR_NSS_SHIFT                                (26U)
#define CSL_A15_DBGVCR_NSS_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSS_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSU_MASK                                 (0x02000000U)
#define CSL_A15_DBGVCR_NSU_SHIFT                                (25U)
#define CSL_A15_DBGVCR_NSU_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVCR_NSU_MAX                                  (0x00000001U)

#define CSL_A15_DBGVCR_NSHF_MASK                                (0x00800000U)
#define CSL_A15_DBGVCR_NSHF_SHIFT                               (23U)
#define CSL_A15_DBGVCR_NSHF_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHF_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHI_MASK                                (0x00400000U)
#define CSL_A15_DBGVCR_NSHI_SHIFT                               (22U)
#define CSL_A15_DBGVCR_NSHI_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHI_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHE_MASK                                (0x00200000U)
#define CSL_A15_DBGVCR_NSHE_SHIFT                               (21U)
#define CSL_A15_DBGVCR_NSHE_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHE_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHD_MASK                                (0x00100000U)
#define CSL_A15_DBGVCR_NSHD_SHIFT                               (20U)
#define CSL_A15_DBGVCR_NSHD_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHD_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHP_MASK                                (0x00080000U)
#define CSL_A15_DBGVCR_NSHP_SHIFT                               (19U)
#define CSL_A15_DBGVCR_NSHP_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHP_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHC_MASK                                (0x00040000U)
#define CSL_A15_DBGVCR_NSHC_SHIFT                               (18U)
#define CSL_A15_DBGVCR_NSHC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHC_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_NSHU_MASK                                (0x00020000U)
#define CSL_A15_DBGVCR_NSHU_SHIFT                               (17U)
#define CSL_A15_DBGVCR_NSHU_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVCR_NSHU_MAX                                 (0x00000001U)

#define CSL_A15_DBGVCR_MF_MASK                                  (0x00008000U)
#define CSL_A15_DBGVCR_MF_SHIFT                                 (15U)
#define CSL_A15_DBGVCR_MF_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_MF_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_MI_MASK                                  (0x00004000U)
#define CSL_A15_DBGVCR_MI_SHIFT                                 (14U)
#define CSL_A15_DBGVCR_MI_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_MI_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_MD_MASK                                  (0x00001000U)
#define CSL_A15_DBGVCR_MD_SHIFT                                 (12U)
#define CSL_A15_DBGVCR_MD_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_MD_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_MP_MASK                                  (0x00000800U)
#define CSL_A15_DBGVCR_MP_SHIFT                                 (11U)
#define CSL_A15_DBGVCR_MP_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_MP_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_MS_MASK                                  (0x00000400U)
#define CSL_A15_DBGVCR_MS_SHIFT                                 (10U)
#define CSL_A15_DBGVCR_MS_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_MS_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SF_MASK                                  (0x00000080U)
#define CSL_A15_DBGVCR_SF_SHIFT                                 (7U)
#define CSL_A15_DBGVCR_SF_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SF_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SI_MASK                                  (0x00000040U)
#define CSL_A15_DBGVCR_SI_SHIFT                                 (6U)
#define CSL_A15_DBGVCR_SI_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SI_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SD_MASK                                  (0x00000010U)
#define CSL_A15_DBGVCR_SD_SHIFT                                 (4U)
#define CSL_A15_DBGVCR_SD_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SD_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SP_MASK                                  (0x00000008U)
#define CSL_A15_DBGVCR_SP_SHIFT                                 (3U)
#define CSL_A15_DBGVCR_SP_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SP_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SS_MASK                                  (0x00000004U)
#define CSL_A15_DBGVCR_SS_SHIFT                                 (2U)
#define CSL_A15_DBGVCR_SS_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SS_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_SU_MASK                                  (0x00000002U)
#define CSL_A15_DBGVCR_SU_SHIFT                                 (1U)
#define CSL_A15_DBGVCR_SU_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGVCR_SU_MAX                                   (0x00000001U)

#define CSL_A15_DBGVCR_R_MASK                                   (0x00000001U)
#define CSL_A15_DBGVCR_R_SHIFT                                  (0U)
#define CSL_A15_DBGVCR_R_RESETVAL                               (0x00000000U)
#define CSL_A15_DBGVCR_R_MAX                                    (0x00000001U)

#define CSL_A15_DBGVCR_RESETVAL                                 (0x00000000U)

/* DBGECR */

#define CSL_A15_DBGECR_OSUCE_MASK                               (0x00000001U)
#define CSL_A15_DBGECR_OSUCE_SHIFT                              (0U)
#define CSL_A15_DBGECR_OSUCE_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGECR_OSUCE_MAX                                (0x00000001U)

#define CSL_A15_DBGECR_RESETVAL                                 (0x00000000U)

/* DBGDTRRX */

#define CSL_A15_DBGDTRRX_HOSTTOTARGETDATA_MASK                  (0xFFFFFFFFU)
#define CSL_A15_DBGDTRRX_HOSTTOTARGETDATA_SHIFT                 (0U)
#define CSL_A15_DBGDTRRX_HOSTTOTARGETDATA_RESETVAL              (0x00000000U)
#define CSL_A15_DBGDTRRX_HOSTTOTARGETDATA_MAX                   (0xffffffffU)

#define CSL_A15_DBGDTRRX_RESETVAL                               (0x00000000U)

/* DBGITR */

#define CSL_A15_DBGITR_ARMINSTR_MASK                            (0xFFFFFFFFU)
#define CSL_A15_DBGITR_ARMINSTR_SHIFT                           (0U)
#define CSL_A15_DBGITR_ARMINSTR_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGITR_ARMINSTR_MAX                             (0xffffffffU)

#define CSL_A15_DBGITR_RESETVAL                                 (0x00000000U)

/* DBGPCSR_0 */

#define CSL_A15_DBGPCSR_0_PCS_MASK                              (0xFFFFFFFCU)
#define CSL_A15_DBGPCSR_0_PCS_SHIFT                             (2U)
#define CSL_A15_DBGPCSR_0_PCS_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGPCSR_0_PCS_MAX                               (0x3fffffffU)

#define CSL_A15_DBGPCSR_0_IS_MASK                               (0x00000003U)
#define CSL_A15_DBGPCSR_0_IS_SHIFT                              (0U)
#define CSL_A15_DBGPCSR_0_IS_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGPCSR_0_IS_MAX                                (0x00000003U)

#define CSL_A15_DBGPCSR_0_RESETVAL                              (0x00000000U)

/* DBGDSCR */

#define CSL_A15_DBGDSCR_RXFULL_MASK                             (0x40000000U)
#define CSL_A15_DBGDSCR_RXFULL_SHIFT                            (30U)
#define CSL_A15_DBGDSCR_RXFULL_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_RXFULL_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_TXFULL_MASK                             (0x20000000U)
#define CSL_A15_DBGDSCR_TXFULL_SHIFT                            (29U)
#define CSL_A15_DBGDSCR_TXFULL_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_TXFULL_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_RXFULLL_MASK                            (0x08000000U)
#define CSL_A15_DBGDSCR_RXFULLL_SHIFT                           (27U)
#define CSL_A15_DBGDSCR_RXFULLL_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDSCR_RXFULLL_MAX                             (0x00000001U)

#define CSL_A15_DBGDSCR_TXFULLL_MASK                            (0x04000000U)
#define CSL_A15_DBGDSCR_TXFULLL_SHIFT                           (26U)
#define CSL_A15_DBGDSCR_TXFULLL_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDSCR_TXFULLL_MAX                             (0x00000001U)

#define CSL_A15_DBGDSCR_PIPEADV_MASK                            (0x02000000U)
#define CSL_A15_DBGDSCR_PIPEADV_SHIFT                           (25U)
#define CSL_A15_DBGDSCR_PIPEADV_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDSCR_PIPEADV_MAX                             (0x00000001U)

#define CSL_A15_DBGDSCR_INSTRCOMPLL_MASK                        (0x01000000U)
#define CSL_A15_DBGDSCR_INSTRCOMPLL_SHIFT                       (24U)
#define CSL_A15_DBGDSCR_INSTRCOMPLL_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGDSCR_INSTRCOMPLL_MAX                         (0x00000001U)

#define CSL_A15_DBGDSCR_EXTDCCMODE_MASK                         (0x00300000U)
#define CSL_A15_DBGDSCR_EXTDCCMODE_SHIFT                        (20U)
#define CSL_A15_DBGDSCR_EXTDCCMODE_RESETVAL                     (0x00000000U)
#define CSL_A15_DBGDSCR_EXTDCCMODE_MAX                          (0x00000003U)

#define CSL_A15_DBGDSCR_ADADISCARD_MASK                         (0x00080000U)
#define CSL_A15_DBGDSCR_ADADISCARD_SHIFT                        (19U)
#define CSL_A15_DBGDSCR_ADADISCARD_RESETVAL                     (0x00000000U)
#define CSL_A15_DBGDSCR_ADADISCARD_MAX                          (0x00000001U)

#define CSL_A15_DBGDSCR_NS_MASK                                 (0x00040000U)
#define CSL_A15_DBGDSCR_NS_SHIFT                                (18U)
#define CSL_A15_DBGDSCR_NS_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGDSCR_NS_MAX                                  (0x00000001U)

#define CSL_A15_DBGDSCR_SPNIDDIS_MASK                           (0x00020000U)
#define CSL_A15_DBGDSCR_SPNIDDIS_SHIFT                          (17U)
#define CSL_A15_DBGDSCR_SPNIDDIS_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGDSCR_SPNIDDIS_MAX                            (0x00000001U)

#define CSL_A15_DBGDSCR_SPIDDIS_MASK                            (0x00010000U)
#define CSL_A15_DBGDSCR_SPIDDIS_SHIFT                           (16U)
#define CSL_A15_DBGDSCR_SPIDDIS_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDSCR_SPIDDIS_MAX                             (0x00000001U)

#define CSL_A15_DBGDSCR_MDBGEN_MASK                             (0x00008000U)
#define CSL_A15_DBGDSCR_MDBGEN_SHIFT                            (15U)
#define CSL_A15_DBGDSCR_MDBGEN_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_MDBGEN_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_HDBGEN_MASK                             (0x00004000U)
#define CSL_A15_DBGDSCR_HDBGEN_SHIFT                            (14U)
#define CSL_A15_DBGDSCR_HDBGEN_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_HDBGEN_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_ITREN_MASK                              (0x00002000U)
#define CSL_A15_DBGDSCR_ITREN_SHIFT                             (13U)
#define CSL_A15_DBGDSCR_ITREN_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGDSCR_ITREN_MAX                               (0x00000001U)

#define CSL_A15_DBGDSCR_UDCCDIS_MASK                            (0x00001000U)
#define CSL_A15_DBGDSCR_UDCCDIS_SHIFT                           (12U)
#define CSL_A15_DBGDSCR_UDCCDIS_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGDSCR_UDCCDIS_MAX                             (0x00000001U)

#define CSL_A15_DBGDSCR_INTDIS_MASK                             (0x00000800U)
#define CSL_A15_DBGDSCR_INTDIS_SHIFT                            (11U)
#define CSL_A15_DBGDSCR_INTDIS_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_INTDIS_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_DBGACK_MASK                             (0x00000400U)
#define CSL_A15_DBGDSCR_DBGACK_SHIFT                            (10U)
#define CSL_A15_DBGDSCR_DBGACK_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_DBGACK_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_FS_MASK                                 (0x00000200U)
#define CSL_A15_DBGDSCR_FS_SHIFT                                (9U)
#define CSL_A15_DBGDSCR_FS_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGDSCR_FS_MAX                                  (0x00000001U)

#define CSL_A15_DBGDSCR_UNDL_MASK                               (0x00000100U)
#define CSL_A15_DBGDSCR_UNDL_SHIFT                              (8U)
#define CSL_A15_DBGDSCR_UNDL_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGDSCR_UNDL_MAX                                (0x00000001U)

#define CSL_A15_DBGDSCR_ADABORTL_MASK                           (0x00000080U)
#define CSL_A15_DBGDSCR_ADABORTL_SHIFT                          (7U)
#define CSL_A15_DBGDSCR_ADABORTL_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGDSCR_ADABORTL_MAX                            (0x00000001U)

#define CSL_A15_DBGDSCR_SDABORTL_MASK                           (0x00000040U)
#define CSL_A15_DBGDSCR_SDABORTL_SHIFT                          (6U)
#define CSL_A15_DBGDSCR_SDABORTL_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGDSCR_SDABORTL_MAX                            (0x00000001U)

#define CSL_A15_DBGDSCR_MOE_MASK                                (0x0000003CU)
#define CSL_A15_DBGDSCR_MOE_SHIFT                               (2U)
#define CSL_A15_DBGDSCR_MOE_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGDSCR_MOE_MAX                                 (0x0000000fU)

#define CSL_A15_DBGDSCR_RESTARTED_MASK                          (0x00000002U)
#define CSL_A15_DBGDSCR_RESTARTED_SHIFT                         (1U)
#define CSL_A15_DBGDSCR_RESTARTED_RESETVAL                      (0x00000000U)
#define CSL_A15_DBGDSCR_RESTARTED_MAX                           (0x00000001U)

#define CSL_A15_DBGDSCR_HALTED_MASK                             (0x00000001U)
#define CSL_A15_DBGDSCR_HALTED_SHIFT                            (0U)
#define CSL_A15_DBGDSCR_HALTED_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGDSCR_HALTED_MAX                              (0x00000001U)

#define CSL_A15_DBGDSCR_RESETVAL                                (0x00000000U)

/* DBGDTRTX */

#define CSL_A15_DBGDTRTX_TARGETTOHOSTDATA_MASK                  (0xFFFFFFFFU)
#define CSL_A15_DBGDTRTX_TARGETTOHOSTDATA_SHIFT                 (0U)
#define CSL_A15_DBGDTRTX_TARGETTOHOSTDATA_RESETVAL              (0x00000000U)
#define CSL_A15_DBGDTRTX_TARGETTOHOSTDATA_MAX                   (0xffffffffU)

#define CSL_A15_DBGDTRTX_RESETVAL                               (0x00000000U)

/* DBGDRCR */

#define CSL_A15_DBGDRCR_CBRRQ_MASK                              (0x00000010U)
#define CSL_A15_DBGDRCR_CBRRQ_SHIFT                             (4U)
#define CSL_A15_DBGDRCR_CBRRQ_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGDRCR_CBRRQ_MAX                               (0x00000001U)

#define CSL_A15_DBGDRCR_CSPA_MASK                               (0x00000008U)
#define CSL_A15_DBGDRCR_CSPA_SHIFT                              (3U)
#define CSL_A15_DBGDRCR_CSPA_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGDRCR_CSPA_MAX                                (0x00000001U)

#define CSL_A15_DBGDRCR_CSE_MASK                                (0x00000004U)
#define CSL_A15_DBGDRCR_CSE_SHIFT                               (2U)
#define CSL_A15_DBGDRCR_CSE_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGDRCR_CSE_MAX                                 (0x00000001U)

#define CSL_A15_DBGDRCR_RRQ_MASK                                (0x00000002U)
#define CSL_A15_DBGDRCR_RRQ_SHIFT                               (1U)
#define CSL_A15_DBGDRCR_RRQ_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGDRCR_RRQ_MAX                                 (0x00000001U)

#define CSL_A15_DBGDRCR_HRQ_MASK                                (0x00000001U)
#define CSL_A15_DBGDRCR_HRQ_SHIFT                               (0U)
#define CSL_A15_DBGDRCR_HRQ_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGDRCR_HRQ_MAX                                 (0x00000001U)

#define CSL_A15_DBGDRCR_RESETVAL                                (0x00000000U)

/* DBGEACR */

#define CSL_A15_DBGEACR_CDRS_MASK                               (0x00000008U)
#define CSL_A15_DBGEACR_CDRS_SHIFT                              (3U)
#define CSL_A15_DBGEACR_CDRS_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGEACR_CDRS_MAX                                (0x00000001U)

#define CSL_A15_DBGEACR_DECRRQ_MASK                             (0x00000004U)
#define CSL_A15_DBGEACR_DECRRQ_SHIFT                            (2U)
#define CSL_A15_DBGEACR_DECRRQ_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGEACR_DECRRQ_MAX                              (0x00000001U)

#define CSL_A15_DBGEACR_DPDO_MASK                               (0x00000002U)
#define CSL_A15_DBGEACR_DPDO_SHIFT                              (1U)
#define CSL_A15_DBGEACR_DPDO_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGEACR_DPDO_MAX                                (0x00000001U)

#define CSL_A15_DBGEACR_DCSC_MASK                               (0x00000001U)
#define CSL_A15_DBGEACR_DCSC_SHIFT                              (0U)
#define CSL_A15_DBGEACR_DCSC_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGEACR_DCSC_MAX                                (0x00000001U)

#define CSL_A15_DBGEACR_RESETVAL                                (0x00000000U)

/* DBGPCSR_1 */

#define CSL_A15_DBGPCSR_1_PCS_MASK                              (0xFFFFFFFCU)
#define CSL_A15_DBGPCSR_1_PCS_SHIFT                             (2U)
#define CSL_A15_DBGPCSR_1_PCS_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGPCSR_1_PCS_MAX                               (0x3fffffffU)

#define CSL_A15_DBGPCSR_1_IS_MASK                               (0x00000003U)
#define CSL_A15_DBGPCSR_1_IS_SHIFT                              (0U)
#define CSL_A15_DBGPCSR_1_IS_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGPCSR_1_IS_MAX                                (0x00000003U)

#define CSL_A15_DBGPCSR_1_RESETVAL                              (0x00000000U)

/* DBGCIDSR */

#define CSL_A15_DBGCIDSR_CONTEXTIDRSAMPVAL_MASK                 (0xFFFFFFFFU)
#define CSL_A15_DBGCIDSR_CONTEXTIDRSAMPVAL_SHIFT                (0U)
#define CSL_A15_DBGCIDSR_CONTEXTIDRSAMPVAL_RESETVAL             (0x00000000U)
#define CSL_A15_DBGCIDSR_CONTEXTIDRSAMPVAL_MAX                  (0xffffffffU)

#define CSL_A15_DBGCIDSR_RESETVAL                               (0x00000000U)

/* DBGVIDSR */

#define CSL_A15_DBGVIDSR_NS_MASK                                (0x80000000U)
#define CSL_A15_DBGVIDSR_NS_SHIFT                               (31U)
#define CSL_A15_DBGVIDSR_NS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGVIDSR_NS_MAX                                 (0x00000001U)

#define CSL_A15_DBGVIDSR_H_MASK                                 (0x40000000U)
#define CSL_A15_DBGVIDSR_H_SHIFT                                (30U)
#define CSL_A15_DBGVIDSR_H_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGVIDSR_H_MAX                                  (0x00000001U)

#define CSL_A15_DBGVIDSR_VMID_MASK                              (0x000000FFU)
#define CSL_A15_DBGVIDSR_VMID_SHIFT                             (0U)
#define CSL_A15_DBGVIDSR_VMID_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGVIDSR_VMID_MAX                               (0x000000ffU)

#define CSL_A15_DBGVIDSR_RESETVAL                               (0x00000000U)

/* DBGBVR0 */

#define CSL_A15_DBGBVR0_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR0_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR0_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR0_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR0_RESETVAL                                (0x00000000U)

/* DBGBVR1 */

#define CSL_A15_DBGBVR1_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR1_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR1_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR1_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR1_RESETVAL                                (0x00000000U)

/* DBGBVR2 */

#define CSL_A15_DBGBVR2_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR2_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR2_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR2_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR2_RESETVAL                                (0x00000000U)

/* DBGBVR3 */

#define CSL_A15_DBGBVR3_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR3_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR3_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR3_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR3_RESETVAL                                (0x00000000U)

/* DBGBVR4 */

#define CSL_A15_DBGBVR4_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR4_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR4_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR4_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR4_RESETVAL                                (0x00000000U)

/* DBGBVR5 */

#define CSL_A15_DBGBVR5_IA_MASK                                 (0xFFFFFFFCU)
#define CSL_A15_DBGBVR5_IA_SHIFT                                (2U)
#define CSL_A15_DBGBVR5_IA_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBVR5_IA_MAX                                  (0x3fffffffU)

#define CSL_A15_DBGBVR5_RESETVAL                                (0x00000000U)

/* DBGBCR0 */

#define CSL_A15_DBGBCR0_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR0_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR0_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR0_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR0_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR0_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR0_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR0_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR0_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR0_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR0_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR0_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR0_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR0_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR0_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR0_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR0_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR0_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR0_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR0_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR0_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR0_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR0_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR0_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR0_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR0_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR0_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR0_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR0_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR0_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR0_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR0_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR0_RESETVAL                                (0x00000000U)

/* DBGBCR1 */

#define CSL_A15_DBGBCR1_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR1_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR1_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR1_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR1_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR1_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR1_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR1_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR1_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR1_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR1_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR1_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR1_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR1_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR1_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR1_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR1_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR1_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR1_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR1_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR1_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR1_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR1_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR1_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR1_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR1_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR1_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR1_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR1_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR1_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR1_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR1_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR1_RESETVAL                                (0x00000000U)

/* DBGBCR2 */

#define CSL_A15_DBGBCR2_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR2_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR2_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR2_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR2_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR2_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR2_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR2_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR2_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR2_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR2_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR2_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR2_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR2_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR2_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR2_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR2_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR2_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR2_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR2_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR2_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR2_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR2_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR2_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR2_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR2_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR2_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR2_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR2_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR2_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR2_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR2_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR2_RESETVAL                                (0x00000000U)

/* DBGBCR3 */

#define CSL_A15_DBGBCR3_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR3_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR3_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR3_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR3_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR3_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR3_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR3_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR3_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR3_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR3_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR3_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR3_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR3_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR3_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR3_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR3_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR3_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR3_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR3_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR3_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR3_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR3_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR3_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR3_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR3_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR3_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR3_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR3_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR3_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR3_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR3_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR3_RESETVAL                                (0x00000000U)

/* DBGBCR4 */

#define CSL_A15_DBGBCR4_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR4_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR4_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR4_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR4_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR4_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR4_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR4_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR4_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR4_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR4_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR4_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR4_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR4_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR4_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR4_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR4_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR4_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR4_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR4_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR4_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR4_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR4_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR4_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR4_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR4_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR4_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR4_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR4_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR4_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR4_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR4_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR4_RESETVAL                                (0x00000000U)

/* DBGBCR5 */

#define CSL_A15_DBGBCR5_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGBCR5_MASK_SHIFT                              (24U)
#define CSL_A15_DBGBCR5_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGBCR5_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGBCR5_BT_MASK                                 (0x00F00000U)
#define CSL_A15_DBGBCR5_BT_SHIFT                                (20U)
#define CSL_A15_DBGBCR5_BT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGBCR5_BT_MAX                                  (0x0000000fU)

#define CSL_A15_DBGBCR5_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGBCR5_LBN_SHIFT                               (16U)
#define CSL_A15_DBGBCR5_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR5_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR5_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGBCR5_SSC_SHIFT                               (14U)
#define CSL_A15_DBGBCR5_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR5_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR5_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGBCR5_HMC_SHIFT                               (13U)
#define CSL_A15_DBGBCR5_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR5_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGBCR5_BAS_MASK                                (0x000001E0U)
#define CSL_A15_DBGBCR5_BAS_SHIFT                               (5U)
#define CSL_A15_DBGBCR5_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR5_BAS_MAX                                 (0x0000000fU)

#define CSL_A15_DBGBCR5_PMC_MASK                                (0x00000006U)
#define CSL_A15_DBGBCR5_PMC_SHIFT                               (1U)
#define CSL_A15_DBGBCR5_PMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGBCR5_PMC_MAX                                 (0x00000003U)

#define CSL_A15_DBGBCR5_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGBCR5_E_SHIFT                                 (0U)
#define CSL_A15_DBGBCR5_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGBCR5_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGBCR5_RESETVAL                                (0x00000000U)

/* DBGWVR0 */

#define CSL_A15_DBGWVR0_DATAADDRESS_MASK                        (0xFFFFFFFCU)
#define CSL_A15_DBGWVR0_DATAADDRESS_SHIFT                       (2U)
#define CSL_A15_DBGWVR0_DATAADDRESS_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGWVR0_DATAADDRESS_MAX                         (0x3fffffffU)

#define CSL_A15_DBGWVR0_RESETVAL                                (0x00000000U)

/* DBGWVR1 */

#define CSL_A15_DBGWVR1_DATAADDRESS_MASK                        (0xFFFFFFFCU)
#define CSL_A15_DBGWVR1_DATAADDRESS_SHIFT                       (2U)
#define CSL_A15_DBGWVR1_DATAADDRESS_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGWVR1_DATAADDRESS_MAX                         (0x3fffffffU)

#define CSL_A15_DBGWVR1_RESETVAL                                (0x00000000U)

/* DBGWVR2 */

#define CSL_A15_DBGWVR2_DATAADDRESS_MASK                        (0xFFFFFFFCU)
#define CSL_A15_DBGWVR2_DATAADDRESS_SHIFT                       (2U)
#define CSL_A15_DBGWVR2_DATAADDRESS_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGWVR2_DATAADDRESS_MAX                         (0x3fffffffU)

#define CSL_A15_DBGWVR2_RESETVAL                                (0x00000000U)

/* DBGWVR3 */

#define CSL_A15_DBGWVR3_DATAADDRESS_MASK                        (0xFFFFFFFCU)
#define CSL_A15_DBGWVR3_DATAADDRESS_SHIFT                       (2U)
#define CSL_A15_DBGWVR3_DATAADDRESS_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGWVR3_DATAADDRESS_MAX                         (0x3fffffffU)

#define CSL_A15_DBGWVR3_RESETVAL                                (0x00000000U)

/* DBGWCR0 */

#define CSL_A15_DBGWCR0_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGWCR0_MASK_SHIFT                              (24U)
#define CSL_A15_DBGWCR0_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGWCR0_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGWCR0_WT_MASK                                 (0x00100000U)
#define CSL_A15_DBGWCR0_WT_SHIFT                                (20U)
#define CSL_A15_DBGWCR0_WT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGWCR0_WT_MAX                                  (0x00000001U)

#define CSL_A15_DBGWCR0_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGWCR0_LBN_SHIFT                               (16U)
#define CSL_A15_DBGWCR0_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGWCR0_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGWCR0_SSC_SHIFT                               (14U)
#define CSL_A15_DBGWCR0_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR0_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGWCR0_HMC_SHIFT                               (13U)
#define CSL_A15_DBGWCR0_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGWCR0_BAS_MASK                                (0x00001FE0U)
#define CSL_A15_DBGWCR0_BAS_SHIFT                               (5U)
#define CSL_A15_DBGWCR0_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_BAS_MAX                                 (0x000000ffU)

#define CSL_A15_DBGWCR0_LSC_MASK                                (0x00000018U)
#define CSL_A15_DBGWCR0_LSC_SHIFT                               (3U)
#define CSL_A15_DBGWCR0_LSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_LSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR0_PAC_MASK                                (0x00000006U)
#define CSL_A15_DBGWCR0_PAC_SHIFT                               (1U)
#define CSL_A15_DBGWCR0_PAC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR0_PAC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR0_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGWCR0_E_SHIFT                                 (0U)
#define CSL_A15_DBGWCR0_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGWCR0_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGWCR0_RESETVAL                                (0x00000000U)

/* DBGWCR1 */

#define CSL_A15_DBGWCR1_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGWCR1_MASK_SHIFT                              (24U)
#define CSL_A15_DBGWCR1_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGWCR1_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGWCR1_WT_MASK                                 (0x00100000U)
#define CSL_A15_DBGWCR1_WT_SHIFT                                (20U)
#define CSL_A15_DBGWCR1_WT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGWCR1_WT_MAX                                  (0x00000001U)

#define CSL_A15_DBGWCR1_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGWCR1_LBN_SHIFT                               (16U)
#define CSL_A15_DBGWCR1_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGWCR1_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGWCR1_SSC_SHIFT                               (14U)
#define CSL_A15_DBGWCR1_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR1_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGWCR1_HMC_SHIFT                               (13U)
#define CSL_A15_DBGWCR1_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGWCR1_BAS_MASK                                (0x00001FE0U)
#define CSL_A15_DBGWCR1_BAS_SHIFT                               (5U)
#define CSL_A15_DBGWCR1_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_BAS_MAX                                 (0x000000ffU)

#define CSL_A15_DBGWCR1_LSC_MASK                                (0x00000018U)
#define CSL_A15_DBGWCR1_LSC_SHIFT                               (3U)
#define CSL_A15_DBGWCR1_LSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_LSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR1_PAC_MASK                                (0x00000006U)
#define CSL_A15_DBGWCR1_PAC_SHIFT                               (1U)
#define CSL_A15_DBGWCR1_PAC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR1_PAC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR1_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGWCR1_E_SHIFT                                 (0U)
#define CSL_A15_DBGWCR1_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGWCR1_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGWCR1_RESETVAL                                (0x00000000U)

/* DBGWCR2 */

#define CSL_A15_DBGWCR2_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGWCR2_MASK_SHIFT                              (24U)
#define CSL_A15_DBGWCR2_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGWCR2_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGWCR2_WT_MASK                                 (0x00100000U)
#define CSL_A15_DBGWCR2_WT_SHIFT                                (20U)
#define CSL_A15_DBGWCR2_WT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGWCR2_WT_MAX                                  (0x00000001U)

#define CSL_A15_DBGWCR2_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGWCR2_LBN_SHIFT                               (16U)
#define CSL_A15_DBGWCR2_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGWCR2_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGWCR2_SSC_SHIFT                               (14U)
#define CSL_A15_DBGWCR2_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR2_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGWCR2_HMC_SHIFT                               (13U)
#define CSL_A15_DBGWCR2_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGWCR2_BAS_MASK                                (0x00001FE0U)
#define CSL_A15_DBGWCR2_BAS_SHIFT                               (5U)
#define CSL_A15_DBGWCR2_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_BAS_MAX                                 (0x000000ffU)

#define CSL_A15_DBGWCR2_LSC_MASK                                (0x00000018U)
#define CSL_A15_DBGWCR2_LSC_SHIFT                               (3U)
#define CSL_A15_DBGWCR2_LSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_LSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR2_PAC_MASK                                (0x00000006U)
#define CSL_A15_DBGWCR2_PAC_SHIFT                               (1U)
#define CSL_A15_DBGWCR2_PAC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR2_PAC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR2_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGWCR2_E_SHIFT                                 (0U)
#define CSL_A15_DBGWCR2_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGWCR2_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGWCR2_RESETVAL                                (0x00000000U)

/* DBGWCR3 */

#define CSL_A15_DBGWCR3_MASK_MASK                               (0x1F000000U)
#define CSL_A15_DBGWCR3_MASK_SHIFT                              (24U)
#define CSL_A15_DBGWCR3_MASK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGWCR3_MASK_MAX                                (0x0000001fU)

#define CSL_A15_DBGWCR3_WT_MASK                                 (0x00100000U)
#define CSL_A15_DBGWCR3_WT_SHIFT                                (20U)
#define CSL_A15_DBGWCR3_WT_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGWCR3_WT_MAX                                  (0x00000001U)

#define CSL_A15_DBGWCR3_LBN_MASK                                (0x000F0000U)
#define CSL_A15_DBGWCR3_LBN_SHIFT                               (16U)
#define CSL_A15_DBGWCR3_LBN_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_LBN_MAX                                 (0x0000000fU)

#define CSL_A15_DBGWCR3_SSC_MASK                                (0x0000C000U)
#define CSL_A15_DBGWCR3_SSC_SHIFT                               (14U)
#define CSL_A15_DBGWCR3_SSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_SSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR3_HMC_MASK                                (0x00002000U)
#define CSL_A15_DBGWCR3_HMC_SHIFT                               (13U)
#define CSL_A15_DBGWCR3_HMC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_HMC_MAX                                 (0x00000001U)

#define CSL_A15_DBGWCR3_BAS_MASK                                (0x00001FE0U)
#define CSL_A15_DBGWCR3_BAS_SHIFT                               (5U)
#define CSL_A15_DBGWCR3_BAS_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_BAS_MAX                                 (0x000000ffU)

#define CSL_A15_DBGWCR3_LSC_MASK                                (0x00000018U)
#define CSL_A15_DBGWCR3_LSC_SHIFT                               (3U)
#define CSL_A15_DBGWCR3_LSC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_LSC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR3_PAC_MASK                                (0x00000006U)
#define CSL_A15_DBGWCR3_PAC_SHIFT                               (1U)
#define CSL_A15_DBGWCR3_PAC_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGWCR3_PAC_MAX                                 (0x00000003U)

#define CSL_A15_DBGWCR3_E_MASK                                  (0x00000001U)
#define CSL_A15_DBGWCR3_E_SHIFT                                 (0U)
#define CSL_A15_DBGWCR3_E_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGWCR3_E_MAX                                   (0x00000001U)

#define CSL_A15_DBGWCR3_RESETVAL                                (0x00000000U)

/* DBGBXVR0 */

#define CSL_A15_DBGBXVR0_VMID_MASK                              (0x000000FFU)
#define CSL_A15_DBGBXVR0_VMID_SHIFT                             (0U)
#define CSL_A15_DBGBXVR0_VMID_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGBXVR0_VMID_MAX                               (0x000000ffU)

#define CSL_A15_DBGBXVR0_RESETVAL                               (0x00000000U)

/* DBGBXVR1 */

#define CSL_A15_DBGBXVR1_VMID_MASK                              (0x000000FFU)
#define CSL_A15_DBGBXVR1_VMID_SHIFT                             (0U)
#define CSL_A15_DBGBXVR1_VMID_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGBXVR1_VMID_MAX                               (0x000000ffU)

#define CSL_A15_DBGBXVR1_RESETVAL                               (0x00000000U)

/* DBGOSLAR */

#define CSL_A15_DBGOSLAR_OSLOCKACCESS_MASK                      (0xFFFFFFFFU)
#define CSL_A15_DBGOSLAR_OSLOCKACCESS_SHIFT                     (0U)
#define CSL_A15_DBGOSLAR_OSLOCKACCESS_RESETVAL                  (0x00000000U)
#define CSL_A15_DBGOSLAR_OSLOCKACCESS_MAX                       (0xffffffffU)

#define CSL_A15_DBGOSLAR_RESETVAL                               (0x00000000U)

/* DBGOSLSR */

#define CSL_A15_DBGOSLSR_LM1_MASK                               (0x00000008U)
#define CSL_A15_DBGOSLSR_LM1_SHIFT                              (3U)
#define CSL_A15_DBGOSLSR_LM1_RESETVAL                           (0x00000001U)
#define CSL_A15_DBGOSLSR_LM1_MAX                                (0x00000001U)

#define CSL_A15_DBGOSLSR_NTT_MASK                               (0x00000004U)
#define CSL_A15_DBGOSLSR_NTT_SHIFT                              (2U)
#define CSL_A15_DBGOSLSR_NTT_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGOSLSR_NTT_MAX                                (0x00000001U)

#define CSL_A15_DBGOSLSR_LK_MASK                                (0x00000002U)
#define CSL_A15_DBGOSLSR_LK_SHIFT                               (1U)
#define CSL_A15_DBGOSLSR_LK_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGOSLSR_LK_MAX                                 (0x00000001U)

#define CSL_A15_DBGOSLSR_LM0_MASK                               (0x00000001U)
#define CSL_A15_DBGOSLSR_LM0_SHIFT                              (0U)
#define CSL_A15_DBGOSLSR_LM0_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGOSLSR_LM0_MAX                                (0x00000001U)

#define CSL_A15_DBGOSLSR_RESETVAL                               (0x00000008U)

/* DBGPRCR */

#define CSL_A15_DBGPRCR_COREPURQ_MASK                           (0x00000008U)
#define CSL_A15_DBGPRCR_COREPURQ_SHIFT                          (3U)
#define CSL_A15_DBGPRCR_COREPURQ_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGPRCR_COREPURQ_MAX                            (0x00000001U)

#define CSL_A15_DBGPRCR_HCWR_MASK                               (0x00000004U)
#define CSL_A15_DBGPRCR_HCWR_SHIFT                              (2U)
#define CSL_A15_DBGPRCR_HCWR_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGPRCR_HCWR_MAX                                (0x00000001U)

#define CSL_A15_DBGPRCR_CWRR_MASK                               (0x00000002U)
#define CSL_A15_DBGPRCR_CWRR_SHIFT                              (1U)
#define CSL_A15_DBGPRCR_CWRR_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGPRCR_CWRR_MAX                                (0x00000001U)

#define CSL_A15_DBGPRCR_CORENPDRQ_MASK                          (0x00000001U)
#define CSL_A15_DBGPRCR_CORENPDRQ_SHIFT                         (0U)
#define CSL_A15_DBGPRCR_CORENPDRQ_RESETVAL                      (0x00000000U)
#define CSL_A15_DBGPRCR_CORENPDRQ_MAX                           (0x00000001U)

#define CSL_A15_DBGPRCR_RESETVAL                                (0x00000000U)

/* DBGPRSR */

#define CSL_A15_DBGPRSR_DLK_MASK                                (0x00000040U)
#define CSL_A15_DBGPRSR_DLK_SHIFT                               (6U)
#define CSL_A15_DBGPRSR_DLK_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGPRSR_DLK_MAX                                 (0x00000001U)

#define CSL_A15_DBGPRSR_OSLK_MASK                               (0x00000020U)
#define CSL_A15_DBGPRSR_OSLK_SHIFT                              (5U)
#define CSL_A15_DBGPRSR_OSLK_RESETVAL                           (0x00000000U)
#define CSL_A15_DBGPRSR_OSLK_MAX                                (0x00000001U)

#define CSL_A15_DBGPRSR_HALTED_MASK                             (0x00000010U)
#define CSL_A15_DBGPRSR_HALTED_SHIFT                            (4U)
#define CSL_A15_DBGPRSR_HALTED_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGPRSR_HALTED_MAX                              (0x00000001U)

#define CSL_A15_DBGPRSR_SR_MASK                                 (0x00000008U)
#define CSL_A15_DBGPRSR_SR_SHIFT                                (3U)
#define CSL_A15_DBGPRSR_SR_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGPRSR_SR_MAX                                  (0x00000001U)

#define CSL_A15_DBGPRSR_R_MASK                                  (0x00000004U)
#define CSL_A15_DBGPRSR_R_SHIFT                                 (2U)
#define CSL_A15_DBGPRSR_R_RESETVAL                              (0x00000000U)
#define CSL_A15_DBGPRSR_R_MAX                                   (0x00000001U)

#define CSL_A15_DBGPRSR_SPD_MASK                                (0x00000002U)
#define CSL_A15_DBGPRSR_SPD_SHIFT                               (1U)
#define CSL_A15_DBGPRSR_SPD_RESETVAL                            (0x00000000U)
#define CSL_A15_DBGPRSR_SPD_MAX                                 (0x00000001U)

#define CSL_A15_DBGPRSR_PU_MASK                                 (0x00000001U)
#define CSL_A15_DBGPRSR_PU_SHIFT                                (0U)
#define CSL_A15_DBGPRSR_PU_RESETVAL                             (0x00000000U)
#define CSL_A15_DBGPRSR_PU_MAX                                  (0x00000001U)

#define CSL_A15_DBGPRSR_RESETVAL                                (0x00000000U)

/* MIDR */

#define CSL_A15_MIDR_IMPLEMENTER_MASK                           (0xFF000000U)
#define CSL_A15_MIDR_IMPLEMENTER_SHIFT                          (24U)
#define CSL_A15_MIDR_IMPLEMENTER_RESETVAL                       (0x00000041U)
#define CSL_A15_MIDR_IMPLEMENTER_MAX                            (0x000000ffU)

#define CSL_A15_MIDR_VARIANT_MASK                               (0x00F00000U)
#define CSL_A15_MIDR_VARIANT_SHIFT                              (20U)
#define CSL_A15_MIDR_VARIANT_RESETVAL                           (0x00000000U)
#define CSL_A15_MIDR_VARIANT_MAX                                (0x0000000fU)

#define CSL_A15_MIDR_ARCHITECTURE_MASK                          (0x000F0000U)
#define CSL_A15_MIDR_ARCHITECTURE_SHIFT                         (16U)
#define CSL_A15_MIDR_ARCHITECTURE_RESETVAL                      (0x0000000fU)
#define CSL_A15_MIDR_ARCHITECTURE_MAX                           (0x0000000fU)

#define CSL_A15_MIDR_PRIMARYPARTNUMBER_MASK                     (0x0000FFF0U)
#define CSL_A15_MIDR_PRIMARYPARTNUMBER_SHIFT                    (4U)
#define CSL_A15_MIDR_PRIMARYPARTNUMBER_RESETVAL                 (0x00000c0fU)
#define CSL_A15_MIDR_PRIMARYPARTNUMBER_MAX                      (0x00000fffU)

#define CSL_A15_MIDR_REVISION_MASK                              (0x0000000FU)
#define CSL_A15_MIDR_REVISION_SHIFT                             (0U)
#define CSL_A15_MIDR_REVISION_RESETVAL                          (0x00000000U)
#define CSL_A15_MIDR_REVISION_MAX                               (0x0000000fU)

#define CSL_A15_MIDR_RESETVAL                                   (0x410fc0f0U)

/* CTR */

#define CSL_A15_CTR_FORMAT_MASK                                 (0xE0000000U)
#define CSL_A15_CTR_FORMAT_SHIFT                                (29U)
#define CSL_A15_CTR_FORMAT_RESETVAL                             (0x00000000U)
#define CSL_A15_CTR_FORMAT_MAX                                  (0x00000007U)

#define CSL_A15_CTR_CWG_MASK                                    (0x0F000000U)
#define CSL_A15_CTR_CWG_SHIFT                                   (24U)
#define CSL_A15_CTR_CWG_RESETVAL                                (0x00000000U)
#define CSL_A15_CTR_CWG_MAX                                     (0x0000000fU)

#define CSL_A15_CTR_ERG_MASK                                    (0x00F00000U)
#define CSL_A15_CTR_ERG_SHIFT                                   (20U)
#define CSL_A15_CTR_ERG_RESETVAL                                (0x00000000U)
#define CSL_A15_CTR_ERG_MAX                                     (0x0000000fU)

#define CSL_A15_CTR_DMINLINE_MASK                               (0x000F0000U)
#define CSL_A15_CTR_DMINLINE_SHIFT                              (16U)
#define CSL_A15_CTR_DMINLINE_RESETVAL                           (0x00000000U)
#define CSL_A15_CTR_DMINLINE_MAX                                (0x0000000fU)

#define CSL_A15_CTR_L1IP_MASK                                   (0x0000C000U)
#define CSL_A15_CTR_L1IP_SHIFT                                  (14U)
#define CSL_A15_CTR_L1IP_RESETVAL                               (0x00000000U)
#define CSL_A15_CTR_L1IP_MAX                                    (0x00000003U)

#define CSL_A15_CTR_IMINLINE_MASK                               (0x0000000FU)
#define CSL_A15_CTR_IMINLINE_SHIFT                              (0U)
#define CSL_A15_CTR_IMINLINE_RESETVAL                           (0x00000000U)
#define CSL_A15_CTR_IMINLINE_MAX                                (0x0000000fU)

#define CSL_A15_CTR_RESETVAL                                    (0x00000000U)

/* TCMTR */

#define CSL_A15_TCMTR_ITCM_MASK                                 (0x00000007U)
#define CSL_A15_TCMTR_ITCM_SHIFT                                (0U)
#define CSL_A15_TCMTR_ITCM_RESETVAL                             (0x00000000U)
#define CSL_A15_TCMTR_ITCM_MAX                                  (0x00000007U)

#define CSL_A15_TCMTR_DTCM_MASK                                 (0x00070000U)
#define CSL_A15_TCMTR_DTCM_SHIFT                                (16U)
#define CSL_A15_TCMTR_DTCM_RESETVAL                             (0x00000000U)
#define CSL_A15_TCMTR_DTCM_MAX                                  (0x00000007U)

#define CSL_A15_TCMTR_TCM_MASK                                  (0xE0000000U)
#define CSL_A15_TCMTR_TCM_SHIFT                                 (29U)
#define CSL_A15_TCMTR_TCM_RESETVAL                              (0x00000000U)
#define CSL_A15_TCMTR_TCM_MAX                                   (0x00000007U)

#define CSL_A15_TCMTR_RESETVAL                                  (0x00000000U)

/* TLBTR */

#define CSL_A15_TLBTR_NU_MASK                                   (0x00000001U)
#define CSL_A15_TLBTR_NU_SHIFT                                  (0U)
#define CSL_A15_TLBTR_NU_RESETVAL                               (0x00000000U)
#define CSL_A15_TLBTR_NU_MAX                                    (0x00000001U)

#define CSL_A15_TLBTR_RESETVAL                                  (0x00000000U)

/* MPUIR */

#define CSL_A15_MPUIR_NU_MASK                                   (0x00000001U)
#define CSL_A15_MPUIR_NU_SHIFT                                  (0U)
#define CSL_A15_MPUIR_NU_RESETVAL                               (0x00000000U)
#define CSL_A15_MPUIR_NU_MAX                                    (0x00000001U)

#define CSL_A15_MPUIR_DREGION_MASK                              (0x0000FF00U)
#define CSL_A15_MPUIR_DREGION_SHIFT                             (8U)
#define CSL_A15_MPUIR_DREGION_RESETVAL                          (0x00000000U)
#define CSL_A15_MPUIR_DREGION_MAX                               (0x000000ffU)

#define CSL_A15_MPUIR_IREGION_MASK                              (0x00FF0000U)
#define CSL_A15_MPUIR_IREGION_SHIFT                             (16U)
#define CSL_A15_MPUIR_IREGION_RESETVAL                          (0x00000000U)
#define CSL_A15_MPUIR_IREGION_MAX                               (0x000000ffU)

#define CSL_A15_MPUIR_RESETVAL                                  (0x00000000U)

/* MPIDR */

#define CSL_A15_MPIDR_U_MASK                                    (0x40000000U)
#define CSL_A15_MPIDR_U_SHIFT                                   (30U)
#define CSL_A15_MPIDR_U_RESETVAL                                (0x00000000U)
#define CSL_A15_MPIDR_U_MAX                                     (0x00000001U)

#define CSL_A15_MPIDR_MT_MASK                                   (0x01000000U)
#define CSL_A15_MPIDR_MT_SHIFT                                  (24U)
#define CSL_A15_MPIDR_MT_RESETVAL                               (0x00000000U)
#define CSL_A15_MPIDR_MT_MAX                                    (0x00000001U)

#define CSL_A15_MPIDR_CLUSTERID_MASK                            (0x00000F00U)
#define CSL_A15_MPIDR_CLUSTERID_SHIFT                           (8U)
#define CSL_A15_MPIDR_CLUSTERID_RESETVAL                        (0x00000000U)
#define CSL_A15_MPIDR_CLUSTERID_MAX                             (0x0000000fU)

#define CSL_A15_MPIDR_CPUID_MASK                                (0x00000003U)
#define CSL_A15_MPIDR_CPUID_SHIFT                               (0U)
#define CSL_A15_MPIDR_CPUID_RESETVAL                            (0x00000003U)
#define CSL_A15_MPIDR_CPUID_MAX                                 (0x00000003U)

#define CSL_A15_MPIDR_RESETVAL                                  (0x80000003U)

/* REVIDR */

#define CSL_A15_REVIDR_IMPLEMENTER_MASK                         (0xFF000000U)
#define CSL_A15_REVIDR_IMPLEMENTER_SHIFT                        (24U)
#define CSL_A15_REVIDR_IMPLEMENTER_RESETVAL                     (0x00000041U)
#define CSL_A15_REVIDR_IMPLEMENTER_MAX                          (0x000000ffU)

#define CSL_A15_REVIDR_VARIANT_MASK                             (0x00F00000U)
#define CSL_A15_REVIDR_VARIANT_SHIFT                            (20U)
#define CSL_A15_REVIDR_VARIANT_RESETVAL                         (0x00000000U)
#define CSL_A15_REVIDR_VARIANT_MAX                              (0x0000000fU)

#define CSL_A15_REVIDR_ARCHITECTURE_MASK                        (0x000F0000U)
#define CSL_A15_REVIDR_ARCHITECTURE_SHIFT                       (16U)
#define CSL_A15_REVIDR_ARCHITECTURE_RESETVAL                    (0x0000000fU)
#define CSL_A15_REVIDR_ARCHITECTURE_MAX                         (0x0000000fU)

#define CSL_A15_REVIDR_PRIMARYPARTNUMBER_MASK                   (0x0000FFF0U)
#define CSL_A15_REVIDR_PRIMARYPARTNUMBER_SHIFT                  (4U)
#define CSL_A15_REVIDR_PRIMARYPARTNUMBER_RESETVAL               (0x00000c0fU)
#define CSL_A15_REVIDR_PRIMARYPARTNUMBER_MAX                    (0x00000fffU)

#define CSL_A15_REVIDR_REVISION_MASK                            (0x0000000FU)
#define CSL_A15_REVIDR_REVISION_SHIFT                           (0U)
#define CSL_A15_REVIDR_REVISION_RESETVAL                        (0x00000000U)
#define CSL_A15_REVIDR_REVISION_MAX                             (0x0000000fU)

#define CSL_A15_REVIDR_RESETVAL                                 (0x410fc0f0U)

/* ID_PFR0 */

#define CSL_A15_ID_PFR0_STATE3_MASK                             (0x0000F000U)
#define CSL_A15_ID_PFR0_STATE3_SHIFT                            (12U)
#define CSL_A15_ID_PFR0_STATE3_RESETVAL                         (0x00000001U)
#define CSL_A15_ID_PFR0_STATE3_MAX                              (0x0000000fU)

#define CSL_A15_ID_PFR0_STATE2_MASK                             (0x00000F00U)
#define CSL_A15_ID_PFR0_STATE2_SHIFT                            (8U)
#define CSL_A15_ID_PFR0_STATE2_RESETVAL                         (0x00000000U)
#define CSL_A15_ID_PFR0_STATE2_MAX                              (0x0000000fU)

#define CSL_A15_ID_PFR0_STATE1_MASK                             (0x000000F0U)
#define CSL_A15_ID_PFR0_STATE1_SHIFT                            (4U)
#define CSL_A15_ID_PFR0_STATE1_RESETVAL                         (0x00000003U)
#define CSL_A15_ID_PFR0_STATE1_MAX                              (0x0000000fU)

#define CSL_A15_ID_PFR0_STATE0_MASK                             (0x0000000FU)
#define CSL_A15_ID_PFR0_STATE0_SHIFT                            (0U)
#define CSL_A15_ID_PFR0_STATE0_RESETVAL                         (0x00000001U)
#define CSL_A15_ID_PFR0_STATE0_MAX                              (0x0000000fU)

#define CSL_A15_ID_PFR0_RESETVAL                                (0x00001031U)

/* ID_PFR1 */

#define CSL_A15_ID_PFR1_GENERICTIMER_MASK                       (0x000F0000U)
#define CSL_A15_ID_PFR1_GENERICTIMER_SHIFT                      (16U)
#define CSL_A15_ID_PFR1_GENERICTIMER_RESETVAL                   (0x00000001U)
#define CSL_A15_ID_PFR1_GENERICTIMER_MAX                        (0x0000000fU)

#define CSL_A15_ID_PFR1_VIRTEXT_MASK                            (0x0000F000U)
#define CSL_A15_ID_PFR1_VIRTEXT_SHIFT                           (12U)
#define CSL_A15_ID_PFR1_VIRTEXT_RESETVAL                        (0x00000001U)
#define CSL_A15_ID_PFR1_VIRTEXT_MAX                             (0x0000000fU)

#define CSL_A15_ID_PFR1_MPROFPROGMODEL_MASK                     (0x00000F00U)
#define CSL_A15_ID_PFR1_MPROFPROGMODEL_SHIFT                    (8U)
#define CSL_A15_ID_PFR1_MPROFPROGMODEL_RESETVAL                 (0x00000000U)
#define CSL_A15_ID_PFR1_MPROFPROGMODEL_MAX                      (0x0000000fU)

#define CSL_A15_ID_PFR1_SECURITYEXT_MASK                        (0x000000F0U)
#define CSL_A15_ID_PFR1_SECURITYEXT_SHIFT                       (4U)
#define CSL_A15_ID_PFR1_SECURITYEXT_RESETVAL                    (0x00000001U)
#define CSL_A15_ID_PFR1_SECURITYEXT_MAX                         (0x0000000fU)

#define CSL_A15_ID_PFR1_PROGMODEL_MASK                          (0x0000000FU)
#define CSL_A15_ID_PFR1_PROGMODEL_SHIFT                         (0U)
#define CSL_A15_ID_PFR1_PROGMODEL_RESETVAL                      (0x00000001U)
#define CSL_A15_ID_PFR1_PROGMODEL_MAX                           (0x0000000fU)

#define CSL_A15_ID_PFR1_RESETVAL                                (0x00011011U)

/* ID_DFR0 */

#define CSL_A15_ID_DFR0_PERFMONMOD_MASK                         (0x0F000000U)
#define CSL_A15_ID_DFR0_PERFMONMOD_SHIFT                        (24U)
#define CSL_A15_ID_DFR0_PERFMONMOD_RESETVAL                     (0x00000002U)
#define CSL_A15_ID_DFR0_PERFMONMOD_MAX                          (0x0000000fU)

#define CSL_A15_ID_DFR0_MDEBUGMOD_MASK                          (0x00F00000U)
#define CSL_A15_ID_DFR0_MDEBUGMOD_SHIFT                         (20U)
#define CSL_A15_ID_DFR0_MDEBUGMOD_RESETVAL                      (0x00000000U)
#define CSL_A15_ID_DFR0_MDEBUGMOD_MAX                           (0x0000000fU)

#define CSL_A15_ID_DFR0_MEMMAPPEDTRACEMOD_MASK                  (0x000F0000U)
#define CSL_A15_ID_DFR0_MEMMAPPEDTRACEMOD_SHIFT                 (16U)
#define CSL_A15_ID_DFR0_MEMMAPPEDTRACEMOD_RESETVAL              (0x00000001U)
#define CSL_A15_ID_DFR0_MEMMAPPEDTRACEMOD_MAX                   (0x0000000fU)

#define CSL_A15_ID_DFR0_COPROCTRACEMOD_MASK                     (0x0000F000U)
#define CSL_A15_ID_DFR0_COPROCTRACEMOD_SHIFT                    (12U)
#define CSL_A15_ID_DFR0_COPROCTRACEMOD_RESETVAL                 (0x00000000U)
#define CSL_A15_ID_DFR0_COPROCTRACEMOD_MAX                      (0x0000000fU)

#define CSL_A15_ID_DFR0_MEMMAPPEDDEBUGMOD_MASK                  (0x00000F00U)
#define CSL_A15_ID_DFR0_MEMMAPPEDDEBUGMOD_SHIFT                 (8U)
#define CSL_A15_ID_DFR0_MEMMAPPEDDEBUGMOD_RESETVAL              (0x00000005U)
#define CSL_A15_ID_DFR0_MEMMAPPEDDEBUGMOD_MAX                   (0x0000000fU)

#define CSL_A15_ID_DFR0_COPROCSECDEBUGMOD_MASK                  (0x000000F0U)
#define CSL_A15_ID_DFR0_COPROCSECDEBUGMOD_SHIFT                 (4U)
#define CSL_A15_ID_DFR0_COPROCSECDEBUGMOD_RESETVAL              (0x00000005U)
#define CSL_A15_ID_DFR0_COPROCSECDEBUGMOD_MAX                   (0x0000000fU)

#define CSL_A15_ID_DFR0_COPROCDEBUGMOD_MASK                     (0x0000000FU)
#define CSL_A15_ID_DFR0_COPROCDEBUGMOD_SHIFT                    (0U)
#define CSL_A15_ID_DFR0_COPROCDEBUGMOD_RESETVAL                 (0x00000005U)
#define CSL_A15_ID_DFR0_COPROCDEBUGMOD_MAX                      (0x0000000fU)

#define CSL_A15_ID_DFR0_RESETVAL                                (0x02010555U)

/* ID_AFR0 */

#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED0_MASK            (0x0000000FU)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED0_SHIFT           (0U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED0_RESETVAL        (0x00000000U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED0_MAX             (0x0000000fU)

#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED1_MASK            (0x000000F0U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED1_SHIFT           (4U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED1_RESETVAL        (0x00000000U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED1_MAX             (0x0000000fU)

#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED2_MASK            (0x00000F00U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED2_SHIFT           (8U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED2_RESETVAL        (0x00000000U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED2_MAX             (0x0000000fU)

#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED3_MASK            (0x0000F000U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED3_SHIFT           (12U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED3_RESETVAL        (0x00000000U)
#define CSL_A15_ID_AFR0_IMPLEMENTATION_DEFINED3_MAX             (0x0000000fU)

#define CSL_A15_ID_AFR0_RESETVAL                                (0x00000000U)

/* ID_MMFR0 */

#define CSL_A15_ID_MMFR0_INNERSHAREABILITY_MASK                 (0xF0000000U)
#define CSL_A15_ID_MMFR0_INNERSHAREABILITY_SHIFT                (28U)
#define CSL_A15_ID_MMFR0_INNERSHAREABILITY_RESETVAL             (0x00000001U)
#define CSL_A15_ID_MMFR0_INNERSHAREABILITY_MAX                  (0x0000000fU)

#define CSL_A15_ID_MMFR0_FCSESUPPORT_MASK                       (0x0F000000U)
#define CSL_A15_ID_MMFR0_FCSESUPPORT_SHIFT                      (24U)
#define CSL_A15_ID_MMFR0_FCSESUPPORT_RESETVAL                   (0x00000000U)
#define CSL_A15_ID_MMFR0_FCSESUPPORT_MAX                        (0x0000000fU)

#define CSL_A15_ID_MMFR0_AUXILIARYREGS_MASK                     (0x00F00000U)
#define CSL_A15_ID_MMFR0_AUXILIARYREGS_SHIFT                    (20U)
#define CSL_A15_ID_MMFR0_AUXILIARYREGS_RESETVAL                 (0x00000002U)
#define CSL_A15_ID_MMFR0_AUXILIARYREGS_MAX                      (0x0000000fU)

#define CSL_A15_ID_MMFR0_TCMSUPPORT_MASK                        (0x000F0000U)
#define CSL_A15_ID_MMFR0_TCMSUPPORT_SHIFT                       (16U)
#define CSL_A15_ID_MMFR0_TCMSUPPORT_RESETVAL                    (0x00000000U)
#define CSL_A15_ID_MMFR0_TCMSUPPORT_MAX                         (0x0000000fU)

#define CSL_A15_ID_MMFR0_SHAREABILITYLEVELS_MASK                (0x0000F000U)
#define CSL_A15_ID_MMFR0_SHAREABILITYLEVELS_SHIFT               (12U)
#define CSL_A15_ID_MMFR0_SHAREABILITYLEVELS_RESETVAL            (0x00000001U)
#define CSL_A15_ID_MMFR0_SHAREABILITYLEVELS_MAX                 (0x0000000fU)

#define CSL_A15_ID_MMFR0_OUTERSHAREABILITY_MASK                 (0x00000F00U)
#define CSL_A15_ID_MMFR0_OUTERSHAREABILITY_SHIFT                (8U)
#define CSL_A15_ID_MMFR0_OUTERSHAREABILITY_RESETVAL             (0x00000001U)
#define CSL_A15_ID_MMFR0_OUTERSHAREABILITY_MAX                  (0x0000000fU)

#define CSL_A15_ID_MMFR0_PMSASUPPORT_MASK                       (0x000000F0U)
#define CSL_A15_ID_MMFR0_PMSASUPPORT_SHIFT                      (4U)
#define CSL_A15_ID_MMFR0_PMSASUPPORT_RESETVAL                   (0x00000000U)
#define CSL_A15_ID_MMFR0_PMSASUPPORT_MAX                        (0x0000000fU)

#define CSL_A15_ID_MMFR0_VMSASUPPORT_MASK                       (0x0000000FU)
#define CSL_A15_ID_MMFR0_VMSASUPPORT_SHIFT                      (0U)
#define CSL_A15_ID_MMFR0_VMSASUPPORT_RESETVAL                   (0x00000005U)
#define CSL_A15_ID_MMFR0_VMSASUPPORT_MAX                        (0x0000000fU)

#define CSL_A15_ID_MMFR0_RESETVAL                               (0x10201105U)

/* ID_MMFR1 */

#define CSL_A15_ID_MMFR1_BRANCHPREDICTOR_MASK                   (0xF0000000U)
#define CSL_A15_ID_MMFR1_BRANCHPREDICTOR_SHIFT                  (28U)
#define CSL_A15_ID_MMFR1_BRANCHPREDICTOR_RESETVAL               (0x00000002U)
#define CSL_A15_ID_MMFR1_BRANCHPREDICTOR_MAX                    (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1TESTANDCLEAN_MASK                    (0x0F000000U)
#define CSL_A15_ID_MMFR1_L1TESTANDCLEAN_SHIFT                   (24U)
#define CSL_A15_ID_MMFR1_L1TESTANDCLEAN_RESETVAL                (0x00000000U)
#define CSL_A15_ID_MMFR1_L1TESTANDCLEAN_MAX                     (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1UNIFIED_MASK                         (0x00F00000U)
#define CSL_A15_ID_MMFR1_L1UNIFIED_SHIFT                        (20U)
#define CSL_A15_ID_MMFR1_L1UNIFIED_RESETVAL                     (0x00000000U)
#define CSL_A15_ID_MMFR1_L1UNIFIED_MAX                          (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1HARVARD_MASK                         (0x000F0000U)
#define CSL_A15_ID_MMFR1_L1HARVARD_SHIFT                        (16U)
#define CSL_A15_ID_MMFR1_L1HARVARD_RESETVAL                     (0x00000000U)
#define CSL_A15_ID_MMFR1_L1HARVARD_MAX                          (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1UNIFIEDSETWAY_MASK                   (0x0000F000U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDSETWAY_SHIFT                  (12U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDSETWAY_RESETVAL               (0x00000000U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDSETWAY_MAX                    (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1HARVARDSETWAY_MASK                   (0x00000F00U)
#define CSL_A15_ID_MMFR1_L1HARVARDSETWAY_SHIFT                  (8U)
#define CSL_A15_ID_MMFR1_L1HARVARDSETWAY_RESETVAL               (0x00000000U)
#define CSL_A15_ID_MMFR1_L1HARVARDSETWAY_MAX                    (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1UNIFIEDVA_MASK                       (0x000000F0U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDVA_SHIFT                      (4U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDVA_RESETVAL                   (0x00000000U)
#define CSL_A15_ID_MMFR1_L1UNIFIEDVA_MAX                        (0x0000000fU)

#define CSL_A15_ID_MMFR1_L1HARVARDVA_MASK                       (0x0000000FU)
#define CSL_A15_ID_MMFR1_L1HARVARDVA_SHIFT                      (0U)
#define CSL_A15_ID_MMFR1_L1HARVARDVA_RESETVAL                   (0x00000000U)
#define CSL_A15_ID_MMFR1_L1HARVARDVA_MAX                        (0x0000000fU)

#define CSL_A15_ID_MMFR1_RESETVAL                               (0x20000000U)

/* ID_MMFR2 */

#define CSL_A15_ID_MMFR2_HWACCESSFLAG_MASK                      (0xF0000000U)
#define CSL_A15_ID_MMFR2_HWACCESSFLAG_SHIFT                     (28U)
#define CSL_A15_ID_MMFR2_HWACCESSFLAG_RESETVAL                  (0x00000000U)
#define CSL_A15_ID_MMFR2_HWACCESSFLAG_MAX                       (0x0000000fU)

#define CSL_A15_ID_MMFR2_WFISTALL_MASK                          (0x0F000000U)
#define CSL_A15_ID_MMFR2_WFISTALL_SHIFT                         (24U)
#define CSL_A15_ID_MMFR2_WFISTALL_RESETVAL                      (0x00000001U)
#define CSL_A15_ID_MMFR2_WFISTALL_MAX                           (0x0000000fU)

#define CSL_A15_ID_MMFR2_MEMORYBARRIER_MASK                     (0x00F00000U)
#define CSL_A15_ID_MMFR2_MEMORYBARRIER_SHIFT                    (20U)
#define CSL_A15_ID_MMFR2_MEMORYBARRIER_RESETVAL                 (0x00000002U)
#define CSL_A15_ID_MMFR2_MEMORYBARRIER_MAX                      (0x0000000fU)

#define CSL_A15_ID_MMFR2_UNIFIEDTLB_MASK                        (0x000F0000U)
#define CSL_A15_ID_MMFR2_UNIFIEDTLB_SHIFT                       (16U)
#define CSL_A15_ID_MMFR2_UNIFIEDTLB_RESETVAL                    (0x00000004U)
#define CSL_A15_ID_MMFR2_UNIFIEDTLB_MAX                         (0x0000000fU)

#define CSL_A15_ID_MMFR2_HARVARDTLB_MASK                        (0x0000F000U)
#define CSL_A15_ID_MMFR2_HARVARDTLB_SHIFT                       (12U)
#define CSL_A15_ID_MMFR2_HARVARDTLB_RESETVAL                    (0x00000000U)
#define CSL_A15_ID_MMFR2_HARVARDTLB_MAX                         (0x0000000fU)

#define CSL_A15_ID_MMFR2_L1HARVARDRANGE_MASK                    (0x00000F00U)
#define CSL_A15_ID_MMFR2_L1HARVARDRANGE_SHIFT                   (8U)
#define CSL_A15_ID_MMFR2_L1HARVARDRANGE_RESETVAL                (0x00000000U)
#define CSL_A15_ID_MMFR2_L1HARVARDRANGE_MAX                     (0x0000000fU)

#define CSL_A15_ID_MMFR2_L1HARVARDBGPREFETCH_MASK               (0x000000F0U)
#define CSL_A15_ID_MMFR2_L1HARVARDBGPREFETCH_SHIFT              (4U)
#define CSL_A15_ID_MMFR2_L1HARVARDBGPREFETCH_RESETVAL           (0x00000000U)
#define CSL_A15_ID_MMFR2_L1HARVARDBGPREFETCH_MAX                (0x0000000fU)

#define CSL_A15_ID_MMFR2_L1HARVARDFGPREFETCH_MASK               (0x0000000FU)
#define CSL_A15_ID_MMFR2_L1HARVARDFGPREFETCH_SHIFT              (0U)
#define CSL_A15_ID_MMFR2_L1HARVARDFGPREFETCH_RESETVAL           (0x00000000U)
#define CSL_A15_ID_MMFR2_L1HARVARDFGPREFETCH_MAX                (0x0000000fU)

#define CSL_A15_ID_MMFR2_RESETVAL                               (0x01240000U)

/* ID_MMFR3 */

#define CSL_A15_ID_MMFR3_SUPERSECTIONSUPPORT_MASK               (0xF0000000U)
#define CSL_A15_ID_MMFR3_SUPERSECTIONSUPPORT_SHIFT              (28U)
#define CSL_A15_ID_MMFR3_SUPERSECTIONSUPPORT_RESETVAL           (0x00000000U)
#define CSL_A15_ID_MMFR3_SUPERSECTIONSUPPORT_MAX                (0x0000000fU)

#define CSL_A15_ID_MMFR3_PHYSICALMEMSIZE_MASK                   (0x0F000000U)
#define CSL_A15_ID_MMFR3_PHYSICALMEMSIZE_SHIFT                  (24U)
#define CSL_A15_ID_MMFR3_PHYSICALMEMSIZE_RESETVAL               (0x00000002U)
#define CSL_A15_ID_MMFR3_PHYSICALMEMSIZE_MAX                    (0x0000000fU)

#define CSL_A15_ID_MMFR3_COHERENTWALK_MASK                      (0x00F00000U)
#define CSL_A15_ID_MMFR3_COHERENTWALK_SHIFT                     (20U)
#define CSL_A15_ID_MMFR3_COHERENTWALK_RESETVAL                  (0x00000001U)
#define CSL_A15_ID_MMFR3_COHERENTWALK_MAX                       (0x0000000fU)

#define CSL_A15_ID_MMFR3_MAINTENANCEBROADCAST_MASK              (0x0000F000U)
#define CSL_A15_ID_MMFR3_MAINTENANCEBROADCAST_SHIFT             (12U)
#define CSL_A15_ID_MMFR3_MAINTENANCEBROADCAST_RESETVAL          (0x00000002U)
#define CSL_A15_ID_MMFR3_MAINTENANCEBROADCAST_MAX               (0x0000000fU)

#define CSL_A15_ID_MMFR3_BRANCHPREDMAINTENANCE_MASK             (0x00000F00U)
#define CSL_A15_ID_MMFR3_BRANCHPREDMAINTENANCE_SHIFT            (8U)
#define CSL_A15_ID_MMFR3_BRANCHPREDMAINTENANCE_RESETVAL         (0x00000002U)
#define CSL_A15_ID_MMFR3_BRANCHPREDMAINTENANCE_MAX              (0x0000000fU)

#define CSL_A15_ID_MMFR3_CACHEMAINTBYSETWAY_MASK                (0x000000F0U)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYSETWAY_SHIFT               (4U)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYSETWAY_RESETVAL            (0x00000001U)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYSETWAY_MAX                 (0x0000000fU)

#define CSL_A15_ID_MMFR3_CACHEMAINTBYMVA_MASK                   (0x0000000FU)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYMVA_SHIFT                  (0U)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYMVA_RESETVAL               (0x00000001U)
#define CSL_A15_ID_MMFR3_CACHEMAINTBYMVA_MAX                    (0x0000000fU)

#define CSL_A15_ID_MMFR3_RESETVAL                               (0x02102211U)

/* ID_ISAR0 */

#define CSL_A15_ID_ISAR0_DIVIDEINSTRS_MASK                      (0x0F000000U)
#define CSL_A15_ID_ISAR0_DIVIDEINSTRS_SHIFT                     (24U)
#define CSL_A15_ID_ISAR0_DIVIDEINSTRS_RESETVAL                  (0x00000002U)
#define CSL_A15_ID_ISAR0_DIVIDEINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR0_DEBUGINSTRS_MASK                       (0x00F00000U)
#define CSL_A15_ID_ISAR0_DEBUGINSTRS_SHIFT                      (20U)
#define CSL_A15_ID_ISAR0_DEBUGINSTRS_RESETVAL                   (0x00000001U)
#define CSL_A15_ID_ISAR0_DEBUGINSTRS_MAX                        (0x0000000fU)

#define CSL_A15_ID_ISAR0_COPROCINSTRS_MASK                      (0x000F0000U)
#define CSL_A15_ID_ISAR0_COPROCINSTRS_SHIFT                     (16U)
#define CSL_A15_ID_ISAR0_COPROCINSTRS_RESETVAL                  (0x00000000U)
#define CSL_A15_ID_ISAR0_COPROCINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR0_CMPBRANCHINSTRS_MASK                   (0x0000F000U)
#define CSL_A15_ID_ISAR0_CMPBRANCHINSTRS_SHIFT                  (12U)
#define CSL_A15_ID_ISAR0_CMPBRANCHINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR0_CMPBRANCHINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR0_BITFIELDINSTRS_MASK                    (0x00000F00U)
#define CSL_A15_ID_ISAR0_BITFIELDINSTRS_SHIFT                   (8U)
#define CSL_A15_ID_ISAR0_BITFIELDINSTRS_RESETVAL                (0x00000001U)
#define CSL_A15_ID_ISAR0_BITFIELDINSTRS_MAX                     (0x0000000fU)

#define CSL_A15_ID_ISAR0_BITCOUNTINSTRS_MASK                    (0x000000F0U)
#define CSL_A15_ID_ISAR0_BITCOUNTINSTRS_SHIFT                   (4U)
#define CSL_A15_ID_ISAR0_BITCOUNTINSTRS_RESETVAL                (0x00000001U)
#define CSL_A15_ID_ISAR0_BITCOUNTINSTRS_MAX                     (0x0000000fU)

#define CSL_A15_ID_ISAR0_SWAPINSTRS_MASK                        (0x0000000FU)
#define CSL_A15_ID_ISAR0_SWAPINSTRS_SHIFT                       (0U)
#define CSL_A15_ID_ISAR0_SWAPINSTRS_RESETVAL                    (0x00000000U)
#define CSL_A15_ID_ISAR0_SWAPINSTRS_MAX                         (0x0000000fU)

#define CSL_A15_ID_ISAR0_RESETVAL                               (0x02101110U)

/* ID_ISAR1 */

#define CSL_A15_ID_ISAR1_JAZELLEINSTRS_MASK                     (0xF0000000U)
#define CSL_A15_ID_ISAR1_JAZELLEINSTRS_SHIFT                    (28U)
#define CSL_A15_ID_ISAR1_JAZELLEINSTRS_RESETVAL                 (0x00000001U)
#define CSL_A15_ID_ISAR1_JAZELLEINSTRS_MAX                      (0x0000000fU)

#define CSL_A15_ID_ISAR1_INTERWORKINSTRS_MASK                   (0x0F000000U)
#define CSL_A15_ID_ISAR1_INTERWORKINSTRS_SHIFT                  (24U)
#define CSL_A15_ID_ISAR1_INTERWORKINSTRS_RESETVAL               (0x00000003U)
#define CSL_A15_ID_ISAR1_INTERWORKINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR1_IMMEDIATEINSTRS_MASK                   (0x00F00000U)
#define CSL_A15_ID_ISAR1_IMMEDIATEINSTRS_SHIFT                  (20U)
#define CSL_A15_ID_ISAR1_IMMEDIATEINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR1_IMMEDIATEINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR1_IFTHENINSTRS_MASK                      (0x000F0000U)
#define CSL_A15_ID_ISAR1_IFTHENINSTRS_SHIFT                     (16U)
#define CSL_A15_ID_ISAR1_IFTHENINSTRS_RESETVAL                  (0x00000001U)
#define CSL_A15_ID_ISAR1_IFTHENINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR1_EXTENDINSTRS_MASK                      (0x0000F000U)
#define CSL_A15_ID_ISAR1_EXTENDINSTRS_SHIFT                     (12U)
#define CSL_A15_ID_ISAR1_EXTENDINSTRS_RESETVAL                  (0x00000002U)
#define CSL_A15_ID_ISAR1_EXTENDINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR1_EXCEPTARINSTRS_MASK                    (0x00000F00U)
#define CSL_A15_ID_ISAR1_EXCEPTARINSTRS_SHIFT                   (8U)
#define CSL_A15_ID_ISAR1_EXCEPTARINSTRS_RESETVAL                (0x00000001U)
#define CSL_A15_ID_ISAR1_EXCEPTARINSTRS_MAX                     (0x0000000fU)

#define CSL_A15_ID_ISAR1_EXCEPTINSTRS_MASK                      (0x000000F0U)
#define CSL_A15_ID_ISAR1_EXCEPTINSTRS_SHIFT                     (4U)
#define CSL_A15_ID_ISAR1_EXCEPTINSTRS_RESETVAL                  (0x00000001U)
#define CSL_A15_ID_ISAR1_EXCEPTINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR1_ENDIANINSTRS_MASK                      (0x0000000FU)
#define CSL_A15_ID_ISAR1_ENDIANINSTRS_SHIFT                     (0U)
#define CSL_A15_ID_ISAR1_ENDIANINSTRS_RESETVAL                  (0x00000001U)
#define CSL_A15_ID_ISAR1_ENDIANINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR1_RESETVAL                               (0x13112111U)

/* ID_ISAR2 */

#define CSL_A15_ID_ISAR2_REVERSALINSTRS_MASK                    (0xF0000000U)
#define CSL_A15_ID_ISAR2_REVERSALINSTRS_SHIFT                   (28U)
#define CSL_A15_ID_ISAR2_REVERSALINSTRS_RESETVAL                (0x00000002U)
#define CSL_A15_ID_ISAR2_REVERSALINSTRS_MAX                     (0x0000000fU)

#define CSL_A15_ID_ISAR2_PSRINSTRS_MASK                         (0x0F000000U)
#define CSL_A15_ID_ISAR2_PSRINSTRS_SHIFT                        (24U)
#define CSL_A15_ID_ISAR2_PSRINSTRS_RESETVAL                     (0x00000001U)
#define CSL_A15_ID_ISAR2_PSRINSTRS_MAX                          (0x0000000fU)

#define CSL_A15_ID_ISAR2_MULTUINSTRS_MASK                       (0x00F00000U)
#define CSL_A15_ID_ISAR2_MULTUINSTRS_SHIFT                      (20U)
#define CSL_A15_ID_ISAR2_MULTUINSTRS_RESETVAL                   (0x00000002U)
#define CSL_A15_ID_ISAR2_MULTUINSTRS_MAX                        (0x0000000fU)

#define CSL_A15_ID_ISAR2_MULTSINSTRS_MASK                       (0x000F0000U)
#define CSL_A15_ID_ISAR2_MULTSINSTRS_SHIFT                      (16U)
#define CSL_A15_ID_ISAR2_MULTSINSTRS_RESETVAL                   (0x00000003U)
#define CSL_A15_ID_ISAR2_MULTSINSTRS_MAX                        (0x0000000fU)

#define CSL_A15_ID_ISAR2_MULTINSTRS_MASK                        (0x0000F000U)
#define CSL_A15_ID_ISAR2_MULTINSTRS_SHIFT                       (12U)
#define CSL_A15_ID_ISAR2_MULTINSTRS_RESETVAL                    (0x00000002U)
#define CSL_A15_ID_ISAR2_MULTINSTRS_MAX                         (0x0000000fU)

#define CSL_A15_ID_ISAR2_MULTIACCESSINTINSTRS_MASK              (0x00000F00U)
#define CSL_A15_ID_ISAR2_MULTIACCESSINTINSTRS_SHIFT             (8U)
#define CSL_A15_ID_ISAR2_MULTIACCESSINTINSTRS_RESETVAL          (0x00000000U)
#define CSL_A15_ID_ISAR2_MULTIACCESSINTINSTRS_MAX               (0x0000000fU)

#define CSL_A15_ID_ISAR2_MEMHINTINSTRS_MASK                     (0x000000F0U)
#define CSL_A15_ID_ISAR2_MEMHINTINSTRS_SHIFT                    (4U)
#define CSL_A15_ID_ISAR2_MEMHINTINSTRS_RESETVAL                 (0x00000004U)
#define CSL_A15_ID_ISAR2_MEMHINTINSTRS_MAX                      (0x0000000fU)

#define CSL_A15_ID_ISAR2_LOADSTOREINSTRS_MASK                   (0x0000000FU)
#define CSL_A15_ID_ISAR2_LOADSTOREINSTRS_SHIFT                  (0U)
#define CSL_A15_ID_ISAR2_LOADSTOREINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR2_LOADSTOREINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR2_RESETVAL                               (0x21232041U)

/* ID_ISAR3 */

#define CSL_A15_ID_ISAR3_THUMBEEEXTNINSTRS_MASK                 (0xF0000000U)
#define CSL_A15_ID_ISAR3_THUMBEEEXTNINSTRS_SHIFT                (28U)
#define CSL_A15_ID_ISAR3_THUMBEEEXTNINSTRS_RESETVAL             (0x00000001U)
#define CSL_A15_ID_ISAR3_THUMBEEEXTNINSTRS_MAX                  (0x0000000fU)

#define CSL_A15_ID_ISAR3_TRUENOPINSTRS_MASK                     (0x0F000000U)
#define CSL_A15_ID_ISAR3_TRUENOPINSTRS_SHIFT                    (24U)
#define CSL_A15_ID_ISAR3_TRUENOPINSTRS_RESETVAL                 (0x00000001U)
#define CSL_A15_ID_ISAR3_TRUENOPINSTRS_MAX                      (0x0000000fU)

#define CSL_A15_ID_ISAR3_THUMBCOPYINSTRS_MASK                   (0x00F00000U)
#define CSL_A15_ID_ISAR3_THUMBCOPYINSTRS_SHIFT                  (20U)
#define CSL_A15_ID_ISAR3_THUMBCOPYINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR3_THUMBCOPYINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR3_TABBRANCHINSTRS_MASK                   (0x000F0000U)
#define CSL_A15_ID_ISAR3_TABBRANCHINSTRS_SHIFT                  (16U)
#define CSL_A15_ID_ISAR3_TABBRANCHINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR3_TABBRANCHINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR3_SYNCHPRIMINSTRS_MASK                   (0x0000F000U)
#define CSL_A15_ID_ISAR3_SYNCHPRIMINSTRS_SHIFT                  (12U)
#define CSL_A15_ID_ISAR3_SYNCHPRIMINSTRS_RESETVAL               (0x00000002U)
#define CSL_A15_ID_ISAR3_SYNCHPRIMINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR3_SVCINSTRS_MASK                         (0x00000F00U)
#define CSL_A15_ID_ISAR3_SVCINSTRS_SHIFT                        (8U)
#define CSL_A15_ID_ISAR3_SVCINSTRS_RESETVAL                     (0x00000001U)
#define CSL_A15_ID_ISAR3_SVCINSTRS_MAX                          (0x0000000fU)

#define CSL_A15_ID_ISAR3_SIMDINSTRS_MASK                        (0x000000F0U)
#define CSL_A15_ID_ISAR3_SIMDINSTRS_SHIFT                       (4U)
#define CSL_A15_ID_ISAR3_SIMDINSTRS_RESETVAL                    (0x00000003U)
#define CSL_A15_ID_ISAR3_SIMDINSTRS_MAX                         (0x0000000fU)

#define CSL_A15_ID_ISAR3_SATURATEINSTRS_MASK                    (0x0000000FU)
#define CSL_A15_ID_ISAR3_SATURATEINSTRS_SHIFT                   (0U)
#define CSL_A15_ID_ISAR3_SATURATEINSTRS_RESETVAL                (0x00000001U)
#define CSL_A15_ID_ISAR3_SATURATEINSTRS_MAX                     (0x0000000fU)

#define CSL_A15_ID_ISAR3_RESETVAL                               (0x11112131U)

/* ID_ISAR4 */

#define CSL_A15_ID_ISAR4_SWPFRAC_MASK                           (0xF0000000U)
#define CSL_A15_ID_ISAR4_SWPFRAC_SHIFT                          (28U)
#define CSL_A15_ID_ISAR4_SWPFRAC_RESETVAL                       (0x00000001U)
#define CSL_A15_ID_ISAR4_SWPFRAC_MAX                            (0x0000000fU)

#define CSL_A15_ID_ISAR4_PSRMINSTRS_MASK                        (0x0F000000U)
#define CSL_A15_ID_ISAR4_PSRMINSTRS_SHIFT                       (24U)
#define CSL_A15_ID_ISAR4_PSRMINSTRS_RESETVAL                    (0x00000000U)
#define CSL_A15_ID_ISAR4_PSRMINSTRS_MAX                         (0x0000000fU)

#define CSL_A15_ID_ISAR4_SYNCHPRIMINSTRSFRAC_MASK               (0x00F00000U)
#define CSL_A15_ID_ISAR4_SYNCHPRIMINSTRSFRAC_SHIFT              (20U)
#define CSL_A15_ID_ISAR4_SYNCHPRIMINSTRSFRAC_RESETVAL           (0x00000000U)
#define CSL_A15_ID_ISAR4_SYNCHPRIMINSTRSFRAC_MAX                (0x0000000fU)

#define CSL_A15_ID_ISAR4_BARRIERINSTRS_MASK                     (0x000F0000U)
#define CSL_A15_ID_ISAR4_BARRIERINSTRS_SHIFT                    (16U)
#define CSL_A15_ID_ISAR4_BARRIERINSTRS_RESETVAL                 (0x00000001U)
#define CSL_A15_ID_ISAR4_BARRIERINSTRS_MAX                      (0x0000000fU)

#define CSL_A15_ID_ISAR4_SMCINSTRS_MASK                         (0x0000F000U)
#define CSL_A15_ID_ISAR4_SMCINSTRS_SHIFT                        (12U)
#define CSL_A15_ID_ISAR4_SMCINSTRS_RESETVAL                     (0x00000001U)
#define CSL_A15_ID_ISAR4_SMCINSTRS_MAX                          (0x0000000fU)

#define CSL_A15_ID_ISAR4_WRITEBACKINSTRS_MASK                   (0x00000F00U)
#define CSL_A15_ID_ISAR4_WRITEBACKINSTRS_SHIFT                  (8U)
#define CSL_A15_ID_ISAR4_WRITEBACKINSTRS_RESETVAL               (0x00000001U)
#define CSL_A15_ID_ISAR4_WRITEBACKINSTRS_MAX                    (0x0000000fU)

#define CSL_A15_ID_ISAR4_WITHSHIFTSINSTRS_MASK                  (0x000000F0U)
#define CSL_A15_ID_ISAR4_WITHSHIFTSINSTRS_SHIFT                 (4U)
#define CSL_A15_ID_ISAR4_WITHSHIFTSINSTRS_RESETVAL              (0x00000004U)
#define CSL_A15_ID_ISAR4_WITHSHIFTSINSTRS_MAX                   (0x0000000fU)

#define CSL_A15_ID_ISAR4_UNPRIVINSTRS_MASK                      (0x0000000FU)
#define CSL_A15_ID_ISAR4_UNPRIVINSTRS_SHIFT                     (0U)
#define CSL_A15_ID_ISAR4_UNPRIVINSTRS_RESETVAL                  (0x00000002U)
#define CSL_A15_ID_ISAR4_UNPRIVINSTRS_MAX                       (0x0000000fU)

#define CSL_A15_ID_ISAR4_RESETVAL                               (0x10011142U)

/* ID_ISAR5 */

#define CSL_A15_ID_ISAR5_RESETVAL                               (0x00000000U)

/* DBGITOCTRL */

#define CSL_A15_DBGITOCTRL_NPMUIRQ_MASK                         (0x00000008U)
#define CSL_A15_DBGITOCTRL_NPMUIRQ_SHIFT                        (3U)
#define CSL_A15_DBGITOCTRL_NPMUIRQ_RESETVAL                     (0x00000000U)
#define CSL_A15_DBGITOCTRL_NPMUIRQ_MAX                          (0x00000001U)

#define CSL_A15_DBGITOCTRL_CTIPMUIRQ_MASK                       (0x00000004U)
#define CSL_A15_DBGITOCTRL_CTIPMUIRQ_SHIFT                      (2U)
#define CSL_A15_DBGITOCTRL_CTIPMUIRQ_RESETVAL                   (0x00000000U)
#define CSL_A15_DBGITOCTRL_CTIPMUIRQ_MAX                        (0x00000001U)

#define CSL_A15_DBGITOCTRL_CTIDBGRESTARTED_MASK                 (0x00000002U)
#define CSL_A15_DBGITOCTRL_CTIDBGRESTARTED_SHIFT                (1U)
#define CSL_A15_DBGITOCTRL_CTIDBGRESTARTED_RESETVAL             (0x00000000U)
#define CSL_A15_DBGITOCTRL_CTIDBGRESTARTED_MAX                  (0x00000001U)

#define CSL_A15_DBGITOCTRL_CTIDBGTRIGGER_MASK                   (0x00000001U)
#define CSL_A15_DBGITOCTRL_CTIDBGTRIGGER_SHIFT                  (0U)
#define CSL_A15_DBGITOCTRL_CTIDBGTRIGGER_RESETVAL               (0x00000000U)
#define CSL_A15_DBGITOCTRL_CTIDBGTRIGGER_MAX                    (0x00000001U)

#define CSL_A15_DBGITOCTRL_RESETVAL                             (0x00000000U)

/* DBGITISR */

#define CSL_A15_DBGITISR_DBGSWENABLE_MASK                       (0x00000008U)
#define CSL_A15_DBGITISR_DBGSWENABLE_SHIFT                      (3U)
#define CSL_A15_DBGITISR_DBGSWENABLE_RESETVAL                   (0x00000000U)
#define CSL_A15_DBGITISR_DBGSWENABLE_MAX                        (0x00000001U)

#define CSL_A15_DBGITISR_CTIDBGRESTART_MASK                     (0x00000004U)
#define CSL_A15_DBGITISR_CTIDBGRESTART_SHIFT                    (2U)
#define CSL_A15_DBGITISR_CTIDBGRESTART_RESETVAL                 (0x00000000U)
#define CSL_A15_DBGITISR_CTIDBGRESTART_MAX                      (0x00000001U)

#define CSL_A15_DBGITISR_CTIEDBGRQ_MASK                         (0x00000002U)
#define CSL_A15_DBGITISR_CTIEDBGRQ_SHIFT                        (1U)
#define CSL_A15_DBGITISR_CTIEDBGRQ_RESETVAL                     (0x00000000U)
#define CSL_A15_DBGITISR_CTIEDBGRQ_MAX                          (0x00000001U)

#define CSL_A15_DBGITISR_EDBGRQ_MASK                            (0x00000001U)
#define CSL_A15_DBGITISR_EDBGRQ_SHIFT                           (0U)
#define CSL_A15_DBGITISR_EDBGRQ_RESETVAL                        (0x00000000U)
#define CSL_A15_DBGITISR_EDBGRQ_MAX                             (0x00000001U)

#define CSL_A15_DBGITISR_RESETVAL                               (0x00000000U)

/* DBGITCTRL */

#define CSL_A15_DBGITCTRL_IME_MASK                              (0x00000001U)
#define CSL_A15_DBGITCTRL_IME_SHIFT                             (0U)
#define CSL_A15_DBGITCTRL_IME_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGITCTRL_IME_MAX                               (0x00000001U)

#define CSL_A15_DBGITCTRL_RESETVAL                              (0x00000000U)

/* DBGCLAIMSET */

#define CSL_A15_DBGCLAIMSET_CLAIM_MASK                          (0x000000FFU)
#define CSL_A15_DBGCLAIMSET_CLAIM_SHIFT                         (0U)
#define CSL_A15_DBGCLAIMSET_CLAIM_RESETVAL                      (0x00000000U)
#define CSL_A15_DBGCLAIMSET_CLAIM_MAX                           (0x000000ffU)

#define CSL_A15_DBGCLAIMSET_RESETVAL                            (0x00000000U)

/* DBGCLAIMCLR */

#define CSL_A15_DBGCLAIMCLR_CLAIM_MASK                          (0x000000FFU)
#define CSL_A15_DBGCLAIMCLR_CLAIM_SHIFT                         (0U)
#define CSL_A15_DBGCLAIMCLR_CLAIM_RESETVAL                      (0x00000000U)
#define CSL_A15_DBGCLAIMCLR_CLAIM_MAX                           (0x000000ffU)

#define CSL_A15_DBGCLAIMCLR_RESETVAL                            (0x00000000U)

/* DBGLAR */

#define CSL_A15_DBGLAR_LOCKACCESSCONTROL_MASK                   (0xFFFFFFFFU)
#define CSL_A15_DBGLAR_LOCKACCESSCONTROL_SHIFT                  (0U)
#define CSL_A15_DBGLAR_LOCKACCESSCONTROL_RESETVAL               (0x00000000U)
#define CSL_A15_DBGLAR_LOCKACCESSCONTROL_MAX                    (0xffffffffU)

#define CSL_A15_DBGLAR_RESETVAL                                 (0x00000000U)

/* DBGLSR */

#define CSL_A15_DBGLSR_X32BITACCESS_MASK                        (0x00000004U)
#define CSL_A15_DBGLSR_X32BITACCESS_SHIFT                       (2U)
#define CSL_A15_DBGLSR_X32BITACCESS_RESETVAL                    (0x00000000U)
#define CSL_A15_DBGLSR_X32BITACCESS_MAX                         (0x00000001U)

#define CSL_A15_DBGLSR_LOCKED_MASK                              (0x00000002U)
#define CSL_A15_DBGLSR_LOCKED_SHIFT                             (1U)
#define CSL_A15_DBGLSR_LOCKED_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGLSR_LOCKED_MAX                               (0x00000001U)

#define CSL_A15_DBGLSR_LOCKIMPLEMENTED_MASK                     (0x00000001U)
#define CSL_A15_DBGLSR_LOCKIMPLEMENTED_SHIFT                    (0U)
#define CSL_A15_DBGLSR_LOCKIMPLEMENTED_RESETVAL                 (0x00000000U)
#define CSL_A15_DBGLSR_LOCKIMPLEMENTED_MAX                      (0x00000001U)

#define CSL_A15_DBGLSR_RESETVAL                                 (0x00000000U)

/* DBGAUTHSTATUS */

#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGFEATURESIMPL_MASK     (0x00000080U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGFEATURESIMPL_SHIFT    (7U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGFEATURESIMPL_RESETVAL  (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGFEATURESIMPL_MAX      (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGEN_MASK               (0x00000040U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGEN_SHIFT              (6U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGEN_RESETVAL           (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_SECNONINVDBGEN_MAX                (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_SECINVDBGFEATURESIMPL_MASK        (0x00000020U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGFEATURESIMPL_SHIFT       (5U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGFEATURESIMPL_RESETVAL    (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGFEATURESIMPL_MAX         (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_SECINVDBGEN_MASK                  (0x00000010U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGEN_SHIFT                 (4U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGEN_RESETVAL              (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_SECINVDBGEN_MAX                   (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGFEATURSIMPL_MASK   (0x00000008U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGFEATURSIMPL_SHIFT  (3U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGFEATURSIMPL_RESETVAL  (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGFEATURSIMPL_MAX    (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGEN_MASK            (0x00000004U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGEN_SHIFT           (2U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGEN_RESETVAL        (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_NONSECNONINVDBGEN_MAX             (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGFEATURESIMPL_MASK     (0x00000002U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGFEATURESIMPL_SHIFT    (1U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGFEATURESIMPL_RESETVAL  (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGFEATURESIMPL_MAX      (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGEN_MASK               (0x00000001U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGEN_SHIFT              (0U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGEN_RESETVAL           (0x00000000U)
#define CSL_A15_DBGAUTHSTATUS_NONSECINVDBGEN_MAX                (0x00000001U)

#define CSL_A15_DBGAUTHSTATUS_RESETVAL                          (0x00000000U)

/* DBGDEVID2 */

#define CSL_A15_DBGDEVID2_UNK_MASK                              (0xFFFFFFFFU)
#define CSL_A15_DBGDEVID2_UNK_SHIFT                             (0U)
#define CSL_A15_DBGDEVID2_UNK_RESETVAL                          (0x00000000U)
#define CSL_A15_DBGDEVID2_UNK_MAX                               (0xffffffffU)

#define CSL_A15_DBGDEVID2_RESETVAL                              (0x00000000U)

/* DBGDEVID1 */

#define CSL_A15_DBGDEVID1_PCSROFFSET_MASK                       (0x0000000FU)
#define CSL_A15_DBGDEVID1_PCSROFFSET_SHIFT                      (0U)
#define CSL_A15_DBGDEVID1_PCSROFFSET_RESETVAL                   (0x00000000U)
#define CSL_A15_DBGDEVID1_PCSROFFSET_MAX                        (0x0000000fU)

#define CSL_A15_DBGDEVID1_RESETVAL                              (0x00000000U)

/* DBGDEVID0 */

#define CSL_A15_DBGDEVID0_AUXREGS_MASK                          (0x0F000000U)
#define CSL_A15_DBGDEVID0_AUXREGS_SHIFT                         (24U)
#define CSL_A15_DBGDEVID0_AUXREGS_RESETVAL                      (0x00000001U)
#define CSL_A15_DBGDEVID0_AUXREGS_MAX                           (0x0000000fU)

#define CSL_A15_DBGDEVID0_DOUBLELOCK_MASK                       (0x00F00000U)
#define CSL_A15_DBGDEVID0_DOUBLELOCK_SHIFT                      (20U)
#define CSL_A15_DBGDEVID0_DOUBLELOCK_RESETVAL                   (0x00000001U)
#define CSL_A15_DBGDEVID0_DOUBLELOCK_MAX                        (0x0000000fU)

#define CSL_A15_DBGDEVID0_VIRTEXTNS_MASK                        (0x000F0000U)
#define CSL_A15_DBGDEVID0_VIRTEXTNS_SHIFT                       (16U)
#define CSL_A15_DBGDEVID0_VIRTEXTNS_RESETVAL                    (0x00000001U)
#define CSL_A15_DBGDEVID0_VIRTEXTNS_MAX                         (0x0000000fU)

#define CSL_A15_DBGDEVID0_VECTORCATCH_MASK                      (0x0000F000U)
#define CSL_A15_DBGDEVID0_VECTORCATCH_SHIFT                     (12U)
#define CSL_A15_DBGDEVID0_VECTORCATCH_RESETVAL                  (0x00000000U)
#define CSL_A15_DBGDEVID0_VECTORCATCH_MAX                       (0x0000000fU)

#define CSL_A15_DBGDEVID0_BPADDRMASK_MASK                       (0x00000F00U)
#define CSL_A15_DBGDEVID0_BPADDRMASK_SHIFT                      (8U)
#define CSL_A15_DBGDEVID0_BPADDRMASK_RESETVAL                   (0x0000000fU)
#define CSL_A15_DBGDEVID0_BPADDRMASK_MAX                        (0x0000000fU)

#define CSL_A15_DBGDEVID0_WPADDRMASK_MASK                       (0x000000F0U)
#define CSL_A15_DBGDEVID0_WPADDRMASK_SHIFT                      (4U)
#define CSL_A15_DBGDEVID0_WPADDRMASK_RESETVAL                   (0x00000001U)
#define CSL_A15_DBGDEVID0_WPADDRMASK_MAX                        (0x0000000fU)

#define CSL_A15_DBGDEVID0_PCSAMPLE_MASK                         (0x0000000FU)
#define CSL_A15_DBGDEVID0_PCSAMPLE_SHIFT                        (0U)
#define CSL_A15_DBGDEVID0_PCSAMPLE_RESETVAL                     (0x00000003U)
#define CSL_A15_DBGDEVID0_PCSAMPLE_MAX                          (0x0000000fU)

#define CSL_A15_DBGDEVID0_RESETVAL                              (0x01110f13U)

/* DBGDEVTYPE */

#define CSL_A15_DBGDEVTYPE_SUBTYPE_MASK                         (0x000000F0U)
#define CSL_A15_DBGDEVTYPE_SUBTYPE_SHIFT                        (4U)
#define CSL_A15_DBGDEVTYPE_SUBTYPE_RESETVAL                     (0x00000001U)
#define CSL_A15_DBGDEVTYPE_SUBTYPE_MAX                          (0x0000000fU)

#define CSL_A15_DBGDEVTYPE_MAINCLASS_MASK                       (0x0000000FU)
#define CSL_A15_DBGDEVTYPE_MAINCLASS_SHIFT                      (0U)
#define CSL_A15_DBGDEVTYPE_MAINCLASS_RESETVAL                   (0x00000005U)
#define CSL_A15_DBGDEVTYPE_MAINCLASS_MAX                        (0x0000000fU)

#define CSL_A15_DBGDEVTYPE_RESETVAL                             (0x00000015U)

/* DBGPID4 */

#define CSL_A15_DBGPID4_COUNT4KB_MASK                           (0x000000F0U)
#define CSL_A15_DBGPID4_COUNT4KB_SHIFT                          (4U)
#define CSL_A15_DBGPID4_COUNT4KB_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGPID4_COUNT4KB_MAX                            (0x0000000fU)

#define CSL_A15_DBGPID4_JEP106CONTCODE_MASK                     (0x0000000FU)
#define CSL_A15_DBGPID4_JEP106CONTCODE_SHIFT                    (0U)
#define CSL_A15_DBGPID4_JEP106CONTCODE_RESETVAL                 (0x00000004U)
#define CSL_A15_DBGPID4_JEP106CONTCODE_MAX                      (0x0000000fU)

#define CSL_A15_DBGPID4_RESETVAL                                (0x00000004U)

/* DBGPID0 */

#define CSL_A15_DBGPID0_PARTNUMBER_MASK                         (0x000000FFU)
#define CSL_A15_DBGPID0_PARTNUMBER_SHIFT                        (0U)
#define CSL_A15_DBGPID0_PARTNUMBER_RESETVAL                     (0x0000000fU)
#define CSL_A15_DBGPID0_PARTNUMBER_MAX                          (0x000000ffU)

#define CSL_A15_DBGPID0_RESETVAL                                (0x0000000fU)

/* DBGPID1 */

#define CSL_A15_DBGPID1_JEP106IDCODE_MASK                       (0x000000F0U)
#define CSL_A15_DBGPID1_JEP106IDCODE_SHIFT                      (4U)
#define CSL_A15_DBGPID1_JEP106IDCODE_RESETVAL                   (0x0000000bU)
#define CSL_A15_DBGPID1_JEP106IDCODE_MAX                        (0x0000000fU)

#define CSL_A15_DBGPID1_PARTNUMBER_MASK                         (0x0000000FU)
#define CSL_A15_DBGPID1_PARTNUMBER_SHIFT                        (0U)
#define CSL_A15_DBGPID1_PARTNUMBER_RESETVAL                     (0x0000000cU)
#define CSL_A15_DBGPID1_PARTNUMBER_MAX                          (0x0000000fU)

#define CSL_A15_DBGPID1_RESETVAL                                (0x000000bcU)

/* DBGPID2 */

#define CSL_A15_DBGPID2_REVISION_MASK                           (0x000000F0U)
#define CSL_A15_DBGPID2_REVISION_SHIFT                          (4U)
#define CSL_A15_DBGPID2_REVISION_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGPID2_REVISION_MAX                            (0x0000000fU)

#define CSL_A15_DBGPID2_USESJEP106IDCODE_MASK                   (0x00000008U)
#define CSL_A15_DBGPID2_USESJEP106IDCODE_SHIFT                  (3U)
#define CSL_A15_DBGPID2_USESJEP106IDCODE_RESETVAL               (0x00000001U)
#define CSL_A15_DBGPID2_USESJEP106IDCODE_MAX                    (0x00000001U)

#define CSL_A15_DBGPID2_JEP106IDCODE_MASK                       (0x00000007U)
#define CSL_A15_DBGPID2_JEP106IDCODE_SHIFT                      (0U)
#define CSL_A15_DBGPID2_JEP106IDCODE_RESETVAL                   (0x00000003U)
#define CSL_A15_DBGPID2_JEP106IDCODE_MAX                        (0x00000007U)

#define CSL_A15_DBGPID2_RESETVAL                                (0x0000000bU)

/* DBGPID3 */

#define CSL_A15_DBGPID3_REVAND_MASK                             (0x000000F0U)
#define CSL_A15_DBGPID3_REVAND_SHIFT                            (4U)
#define CSL_A15_DBGPID3_REVAND_RESETVAL                         (0x00000000U)
#define CSL_A15_DBGPID3_REVAND_MAX                              (0x0000000fU)

#define CSL_A15_DBGPID3_CUSTOMERMODIFIED_MASK                   (0x0000000FU)
#define CSL_A15_DBGPID3_CUSTOMERMODIFIED_SHIFT                  (0U)
#define CSL_A15_DBGPID3_CUSTOMERMODIFIED_RESETVAL               (0x00000000U)
#define CSL_A15_DBGPID3_CUSTOMERMODIFIED_MAX                    (0x0000000fU)

#define CSL_A15_DBGPID3_RESETVAL                                (0x00000000U)

/* DBGCID0 */

#define CSL_A15_DBGCID0_PREAMBLE_MASK                           (0x000000FFU)
#define CSL_A15_DBGCID0_PREAMBLE_SHIFT                          (0U)
#define CSL_A15_DBGCID0_PREAMBLE_RESETVAL                       (0x0000000dU)
#define CSL_A15_DBGCID0_PREAMBLE_MAX                            (0x000000ffU)

#define CSL_A15_DBGCID0_RESETVAL                                (0x0000000dU)

/* DBGCID1 */

#define CSL_A15_DBGCID1_COMPONENTCLASS_MASK                     (0x000000F0U)
#define CSL_A15_DBGCID1_COMPONENTCLASS_SHIFT                    (4U)
#define CSL_A15_DBGCID1_COMPONENTCLASS_RESETVAL                 (0x00000009U)
#define CSL_A15_DBGCID1_COMPONENTCLASS_MAX                      (0x0000000fU)

#define CSL_A15_DBGCID1_PREAMBLE_MASK                           (0x0000000FU)
#define CSL_A15_DBGCID1_PREAMBLE_SHIFT                          (0U)
#define CSL_A15_DBGCID1_PREAMBLE_RESETVAL                       (0x00000000U)
#define CSL_A15_DBGCID1_PREAMBLE_MAX                            (0x0000000fU)

#define CSL_A15_DBGCID1_RESETVAL                                (0x00000090U)

/* DBGCID2 */

#define CSL_A15_DBGCID2_PREAMBLE_MASK                           (0x000000FFU)
#define CSL_A15_DBGCID2_PREAMBLE_SHIFT                          (0U)
#define CSL_A15_DBGCID2_PREAMBLE_RESETVAL                       (0x00000005U)
#define CSL_A15_DBGCID2_PREAMBLE_MAX                            (0x000000ffU)

#define CSL_A15_DBGCID2_RESETVAL                                (0x00000005U)

/* DBGCID3 */

#define CSL_A15_DBGCID3_PREAMBLE_MASK                           (0x000000FFU)
#define CSL_A15_DBGCID3_PREAMBLE_SHIFT                          (0U)
#define CSL_A15_DBGCID3_PREAMBLE_RESETVAL                       (0x000000b1U)
#define CSL_A15_DBGCID3_PREAMBLE_MAX                            (0x000000ffU)

#define CSL_A15_DBGCID3_RESETVAL                                (0x000000b1U)

/* PMXEVCNTR0 */

#define CSL_A15_PMXEVCNTR0_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR0_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR0_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR0_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR0_RESETVAL                             (0x00000000U)

/* PMXEVCNTR1 */

#define CSL_A15_PMXEVCNTR1_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR1_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR1_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR1_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR1_RESETVAL                             (0x00000000U)

/* PMXEVCNTR2 */

#define CSL_A15_PMXEVCNTR2_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR2_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR2_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR2_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR2_RESETVAL                             (0x00000000U)

/* PMXEVCNTR3 */

#define CSL_A15_PMXEVCNTR3_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR3_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR3_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR3_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR3_RESETVAL                             (0x00000000U)

/* PMXEVCNTR4 */

#define CSL_A15_PMXEVCNTR4_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR4_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR4_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR4_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR4_RESETVAL                             (0x00000000U)

/* PMXEVCNTR5 */

#define CSL_A15_PMXEVCNTR5_PMNX_MASK                            (0xFFFFFFFFU)
#define CSL_A15_PMXEVCNTR5_PMNX_SHIFT                           (0U)
#define CSL_A15_PMXEVCNTR5_PMNX_RESETVAL                        (0x00000000U)
#define CSL_A15_PMXEVCNTR5_PMNX_MAX                             (0xffffffffU)

#define CSL_A15_PMXEVCNTR5_RESETVAL                             (0x00000000U)

/* PMCCNTR */

#define CSL_A15_PMCCNTR_CCNT_MASK                               (0xFFFFFFFFU)
#define CSL_A15_PMCCNTR_CCNT_SHIFT                              (0U)
#define CSL_A15_PMCCNTR_CCNT_RESETVAL                           (0x00000000U)
#define CSL_A15_PMCCNTR_CCNT_MAX                                (0xffffffffU)

#define CSL_A15_PMCCNTR_RESETVAL                                (0x00000000U)

/* PMXEVTYPER0 */

#define CSL_A15_PMXEVTYPER0_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER0_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER0_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER0_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER0_RESETVAL                            (0x00000000U)

/* PMXEVTYPER1 */

#define CSL_A15_PMXEVTYPER1_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER1_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER1_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER1_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER1_RESETVAL                            (0x00000000U)

/* PMXEVTYPER2 */

#define CSL_A15_PMXEVTYPER2_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER2_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER2_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER2_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER2_RESETVAL                            (0x00000000U)

/* PMXEVTYPER3 */

#define CSL_A15_PMXEVTYPER3_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER3_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER3_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER3_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER3_RESETVAL                            (0x00000000U)

/* PMXEVTYPER4 */

#define CSL_A15_PMXEVTYPER4_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER4_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER4_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER4_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER4_RESETVAL                            (0x00000000U)

/* PMXEVTYPER5 */

#define CSL_A15_PMXEVTYPER5_EVTCOUNT_MASK                       (0x000000FFU)
#define CSL_A15_PMXEVTYPER5_EVTCOUNT_SHIFT                      (0U)
#define CSL_A15_PMXEVTYPER5_EVTCOUNT_RESETVAL                   (0x00000000U)
#define CSL_A15_PMXEVTYPER5_EVTCOUNT_MAX                        (0x000000ffU)

#define CSL_A15_PMXEVTYPER5_RESETVAL                            (0x00000000U)

/* PMCCFILTR */

#define CSL_A15_PMCCFILTR_PL1_MASK                              (0x80000000U)
#define CSL_A15_PMCCFILTR_PL1_SHIFT                             (31U)
#define CSL_A15_PMCCFILTR_PL1_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCCFILTR_PL1_MAX                               (0x00000001U)

#define CSL_A15_PMCCFILTR_U_MASK                                (0x40000000U)
#define CSL_A15_PMCCFILTR_U_SHIFT                               (30U)
#define CSL_A15_PMCCFILTR_U_RESETVAL                            (0x00000000U)
#define CSL_A15_PMCCFILTR_U_MAX                                 (0x00000001U)

#define CSL_A15_PMCCFILTR_NSPL1_MASK                            (0x20000000U)
#define CSL_A15_PMCCFILTR_NSPL1_SHIFT                           (29U)
#define CSL_A15_PMCCFILTR_NSPL1_RESETVAL                        (0x00000000U)
#define CSL_A15_PMCCFILTR_NSPL1_MAX                             (0x00000001U)

#define CSL_A15_PMCCFILTR_NSU_MASK                              (0x10000000U)
#define CSL_A15_PMCCFILTR_NSU_SHIFT                             (28U)
#define CSL_A15_PMCCFILTR_NSU_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCCFILTR_NSU_MAX                               (0x00000001U)

#define CSL_A15_PMCCFILTR_NSH_MASK                              (0x08000000U)
#define CSL_A15_PMCCFILTR_NSH_SHIFT                             (27U)
#define CSL_A15_PMCCFILTR_NSH_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCCFILTR_NSH_MAX                               (0x00000001U)

#define CSL_A15_PMCCFILTR_RESETVAL                              (0x00000000U)

/* PMCNTENSET */

#define CSL_A15_PMCNTENSET_C_MASK                               (0x80000000U)
#define CSL_A15_PMCNTENSET_C_SHIFT                              (31U)
#define CSL_A15_PMCNTENSET_C_RESETVAL                           (0x00000000U)
#define CSL_A15_PMCNTENSET_C_MAX                                (0x00000001U)

#define CSL_A15_PMCNTENSET_P5_MASK                              (0x00000020U)
#define CSL_A15_PMCNTENSET_P5_SHIFT                             (5U)
#define CSL_A15_PMCNTENSET_P5_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P5_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_P4_MASK                              (0x00000010U)
#define CSL_A15_PMCNTENSET_P4_SHIFT                             (4U)
#define CSL_A15_PMCNTENSET_P4_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P4_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_P3_MASK                              (0x00000008U)
#define CSL_A15_PMCNTENSET_P3_SHIFT                             (3U)
#define CSL_A15_PMCNTENSET_P3_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P3_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_P2_MASK                              (0x00000004U)
#define CSL_A15_PMCNTENSET_P2_SHIFT                             (2U)
#define CSL_A15_PMCNTENSET_P2_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P2_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_P1_MASK                              (0x00000002U)
#define CSL_A15_PMCNTENSET_P1_SHIFT                             (1U)
#define CSL_A15_PMCNTENSET_P1_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P1_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_P0_MASK                              (0x00000001U)
#define CSL_A15_PMCNTENSET_P0_SHIFT                             (0U)
#define CSL_A15_PMCNTENSET_P0_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENSET_P0_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENSET_RESETVAL                             (0x00000000U)

/* PMCNTENCLR */

#define CSL_A15_PMCNTENCLR_C_MASK                               (0x80000000U)
#define CSL_A15_PMCNTENCLR_C_SHIFT                              (31U)
#define CSL_A15_PMCNTENCLR_C_RESETVAL                           (0x00000000U)
#define CSL_A15_PMCNTENCLR_C_MAX                                (0x00000001U)

#define CSL_A15_PMCNTENCLR_P5_MASK                              (0x00000020U)
#define CSL_A15_PMCNTENCLR_P5_SHIFT                             (5U)
#define CSL_A15_PMCNTENCLR_P5_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P5_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_P4_MASK                              (0x00000010U)
#define CSL_A15_PMCNTENCLR_P4_SHIFT                             (4U)
#define CSL_A15_PMCNTENCLR_P4_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P4_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_P3_MASK                              (0x00000008U)
#define CSL_A15_PMCNTENCLR_P3_SHIFT                             (3U)
#define CSL_A15_PMCNTENCLR_P3_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P3_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_P2_MASK                              (0x00000004U)
#define CSL_A15_PMCNTENCLR_P2_SHIFT                             (2U)
#define CSL_A15_PMCNTENCLR_P2_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P2_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_P1_MASK                              (0x00000002U)
#define CSL_A15_PMCNTENCLR_P1_SHIFT                             (1U)
#define CSL_A15_PMCNTENCLR_P1_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P1_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_P0_MASK                              (0x00000001U)
#define CSL_A15_PMCNTENCLR_P0_SHIFT                             (0U)
#define CSL_A15_PMCNTENCLR_P0_RESETVAL                          (0x00000000U)
#define CSL_A15_PMCNTENCLR_P0_MAX                               (0x00000001U)

#define CSL_A15_PMCNTENCLR_RESETVAL                             (0x00000000U)

/* PMINTENSET */

#define CSL_A15_PMINTENSET_C_MASK                               (0x80000000U)
#define CSL_A15_PMINTENSET_C_SHIFT                              (31U)
#define CSL_A15_PMINTENSET_C_RESETVAL                           (0x00000000U)
#define CSL_A15_PMINTENSET_C_MAX                                (0x00000001U)

#define CSL_A15_PMINTENSET_P5_MASK                              (0x00000020U)
#define CSL_A15_PMINTENSET_P5_SHIFT                             (5U)
#define CSL_A15_PMINTENSET_P5_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P5_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_P4_MASK                              (0x00000010U)
#define CSL_A15_PMINTENSET_P4_SHIFT                             (4U)
#define CSL_A15_PMINTENSET_P4_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P4_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_P3_MASK                              (0x00000008U)
#define CSL_A15_PMINTENSET_P3_SHIFT                             (3U)
#define CSL_A15_PMINTENSET_P3_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P3_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_P2_MASK                              (0x00000004U)
#define CSL_A15_PMINTENSET_P2_SHIFT                             (2U)
#define CSL_A15_PMINTENSET_P2_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P2_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_P1_MASK                              (0x00000002U)
#define CSL_A15_PMINTENSET_P1_SHIFT                             (1U)
#define CSL_A15_PMINTENSET_P1_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P1_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_P0_MASK                              (0x00000001U)
#define CSL_A15_PMINTENSET_P0_SHIFT                             (0U)
#define CSL_A15_PMINTENSET_P0_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENSET_P0_MAX                               (0x00000001U)

#define CSL_A15_PMINTENSET_RESETVAL                             (0x00000000U)

/* PMINTENCLR */

#define CSL_A15_PMINTENCLR_C_MASK                               (0x80000000U)
#define CSL_A15_PMINTENCLR_C_SHIFT                              (31U)
#define CSL_A15_PMINTENCLR_C_RESETVAL                           (0x00000000U)
#define CSL_A15_PMINTENCLR_C_MAX                                (0x00000001U)

#define CSL_A15_PMINTENCLR_P5_MASK                              (0x00000020U)
#define CSL_A15_PMINTENCLR_P5_SHIFT                             (5U)
#define CSL_A15_PMINTENCLR_P5_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P5_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_P4_MASK                              (0x00000010U)
#define CSL_A15_PMINTENCLR_P4_SHIFT                             (4U)
#define CSL_A15_PMINTENCLR_P4_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P4_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_P3_MASK                              (0x00000008U)
#define CSL_A15_PMINTENCLR_P3_SHIFT                             (3U)
#define CSL_A15_PMINTENCLR_P3_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P3_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_P2_MASK                              (0x00000004U)
#define CSL_A15_PMINTENCLR_P2_SHIFT                             (2U)
#define CSL_A15_PMINTENCLR_P2_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P2_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_P1_MASK                              (0x00000002U)
#define CSL_A15_PMINTENCLR_P1_SHIFT                             (1U)
#define CSL_A15_PMINTENCLR_P1_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P1_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_P0_MASK                              (0x00000001U)
#define CSL_A15_PMINTENCLR_P0_SHIFT                             (0U)
#define CSL_A15_PMINTENCLR_P0_RESETVAL                          (0x00000000U)
#define CSL_A15_PMINTENCLR_P0_MAX                               (0x00000001U)

#define CSL_A15_PMINTENCLR_RESETVAL                             (0x00000000U)

/* PMOVSR */

#define CSL_A15_PMOVSR_C_MASK                                   (0x80000000U)
#define CSL_A15_PMOVSR_C_SHIFT                                  (31U)
#define CSL_A15_PMOVSR_C_RESETVAL                               (0x00000000U)
#define CSL_A15_PMOVSR_C_MAX                                    (0x00000001U)

#define CSL_A15_PMOVSR_P5_MASK                                  (0x00000020U)
#define CSL_A15_PMOVSR_P5_SHIFT                                 (5U)
#define CSL_A15_PMOVSR_P5_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P5_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_P4_MASK                                  (0x00000010U)
#define CSL_A15_PMOVSR_P4_SHIFT                                 (4U)
#define CSL_A15_PMOVSR_P4_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P4_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_P3_MASK                                  (0x00000008U)
#define CSL_A15_PMOVSR_P3_SHIFT                                 (3U)
#define CSL_A15_PMOVSR_P3_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P3_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_P2_MASK                                  (0x00000004U)
#define CSL_A15_PMOVSR_P2_SHIFT                                 (2U)
#define CSL_A15_PMOVSR_P2_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P2_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_P1_MASK                                  (0x00000002U)
#define CSL_A15_PMOVSR_P1_SHIFT                                 (1U)
#define CSL_A15_PMOVSR_P1_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P1_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_P0_MASK                                  (0x00000001U)
#define CSL_A15_PMOVSR_P0_SHIFT                                 (0U)
#define CSL_A15_PMOVSR_P0_RESETVAL                              (0x00000000U)
#define CSL_A15_PMOVSR_P0_MAX                                   (0x00000001U)

#define CSL_A15_PMOVSR_RESETVAL                                 (0x00000000U)

/* PMSWINC */

#define CSL_A15_PMSWINC_P5_MASK                                 (0x00000020U)
#define CSL_A15_PMSWINC_P5_SHIFT                                (5U)
#define CSL_A15_PMSWINC_P5_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P5_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_P4_MASK                                 (0x00000010U)
#define CSL_A15_PMSWINC_P4_SHIFT                                (4U)
#define CSL_A15_PMSWINC_P4_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P4_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_P3_MASK                                 (0x00000008U)
#define CSL_A15_PMSWINC_P3_SHIFT                                (3U)
#define CSL_A15_PMSWINC_P3_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P3_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_P2_MASK                                 (0x00000004U)
#define CSL_A15_PMSWINC_P2_SHIFT                                (2U)
#define CSL_A15_PMSWINC_P2_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P2_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_P1_MASK                                 (0x00000002U)
#define CSL_A15_PMSWINC_P1_SHIFT                                (1U)
#define CSL_A15_PMSWINC_P1_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P1_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_P0_MASK                                 (0x00000001U)
#define CSL_A15_PMSWINC_P0_SHIFT                                (0U)
#define CSL_A15_PMSWINC_P0_RESETVAL                             (0x00000000U)
#define CSL_A15_PMSWINC_P0_MAX                                  (0x00000001U)

#define CSL_A15_PMSWINC_RESETVAL                                (0x00000000U)

/* PMCFGR */

#define CSL_A15_PMCFGR_UEN_MASK                                 (0x00080000U)
#define CSL_A15_PMCFGR_UEN_SHIFT                                (19U)
#define CSL_A15_PMCFGR_UEN_RESETVAL                             (0x00000001U)
#define CSL_A15_PMCFGR_UEN_MAX                                  (0x00000001U)

#define CSL_A15_PMCFGR_WT_MASK                                  (0x00040000U)
#define CSL_A15_PMCFGR_WT_SHIFT                                 (18U)
#define CSL_A15_PMCFGR_WT_RESETVAL                              (0x00000000U)
#define CSL_A15_PMCFGR_WT_MAX                                   (0x00000001U)

#define CSL_A15_PMCFGR_NA_MASK                                  (0x00020000U)
#define CSL_A15_PMCFGR_NA_SHIFT                                 (17U)
#define CSL_A15_PMCFGR_NA_RESETVAL                              (0x00000000U)
#define CSL_A15_PMCFGR_NA_MAX                                   (0x00000001U)

#define CSL_A15_PMCFGR_EX_MASK                                  (0x00010000U)
#define CSL_A15_PMCFGR_EX_SHIFT                                 (16U)
#define CSL_A15_PMCFGR_EX_RESETVAL                              (0x00000001U)
#define CSL_A15_PMCFGR_EX_MAX                                   (0x00000001U)

#define CSL_A15_PMCFGR_CCD_MASK                                 (0x00008000U)
#define CSL_A15_PMCFGR_CCD_SHIFT                                (15U)
#define CSL_A15_PMCFGR_CCD_RESETVAL                             (0x00000001U)
#define CSL_A15_PMCFGR_CCD_MAX                                  (0x00000001U)

#define CSL_A15_PMCFGR_CC_MASK                                  (0x00004000U)
#define CSL_A15_PMCFGR_CC_SHIFT                                 (14U)
#define CSL_A15_PMCFGR_CC_RESETVAL                              (0x00000001U)
#define CSL_A15_PMCFGR_CC_MAX                                   (0x00000001U)

#define CSL_A15_PMCFGR_SIZE_MASK                                (0x00001800U)
#define CSL_A15_PMCFGR_SIZE_SHIFT                               (11U)
#define CSL_A15_PMCFGR_SIZE_RESETVAL                            (0x00000003U)
#define CSL_A15_PMCFGR_SIZE_MAX                                 (0x00000003U)

#define CSL_A15_PMCFGR_N_MASK                                   (0x000000FFU)
#define CSL_A15_PMCFGR_N_SHIFT                                  (0U)
#define CSL_A15_PMCFGR_N_RESETVAL                               (0x00000006U)
#define CSL_A15_PMCFGR_N_MAX                                    (0x000000ffU)

#define CSL_A15_PMCFGR_RESETVAL                                 (0x0009df06U)

/* PMCR */

#define CSL_A15_PMCR_IMP_MASK                                   (0xFF000000U)
#define CSL_A15_PMCR_IMP_SHIFT                                  (24U)
#define CSL_A15_PMCR_IMP_RESETVAL                               (0x00000041U)
#define CSL_A15_PMCR_IMP_MAX                                    (0x000000ffU)

#define CSL_A15_PMCR_IDCODE_MASK                                (0x00FF0000U)
#define CSL_A15_PMCR_IDCODE_SHIFT                               (16U)
#define CSL_A15_PMCR_IDCODE_RESETVAL                            (0x0000000fU)
#define CSL_A15_PMCR_IDCODE_MAX                                 (0x000000ffU)

#define CSL_A15_PMCR_N_MASK                                     (0x0000F800U)
#define CSL_A15_PMCR_N_SHIFT                                    (11U)
#define CSL_A15_PMCR_N_RESETVAL                                 (0x00000006U)
#define CSL_A15_PMCR_N_MAX                                      (0x0000001fU)

#define CSL_A15_PMCR_DP_MASK                                    (0x00000020U)
#define CSL_A15_PMCR_DP_SHIFT                                   (5U)
#define CSL_A15_PMCR_DP_RESETVAL                                (0x00000000U)
#define CSL_A15_PMCR_DP_MAX                                     (0x00000001U)

#define CSL_A15_PMCR_X_MASK                                     (0x00000010U)
#define CSL_A15_PMCR_X_SHIFT                                    (4U)
#define CSL_A15_PMCR_X_RESETVAL                                 (0x00000000U)
#define CSL_A15_PMCR_X_MAX                                      (0x00000001U)

#define CSL_A15_PMCR_D_MASK                                     (0x00000008U)
#define CSL_A15_PMCR_D_SHIFT                                    (3U)
#define CSL_A15_PMCR_D_RESETVAL                                 (0x00000000U)
#define CSL_A15_PMCR_D_MAX                                      (0x00000001U)

#define CSL_A15_PMCR_C_MASK                                     (0x00000004U)
#define CSL_A15_PMCR_C_SHIFT                                    (2U)
#define CSL_A15_PMCR_C_RESETVAL                                 (0x00000000U)
#define CSL_A15_PMCR_C_MAX                                      (0x00000001U)

#define CSL_A15_PMCR_P_MASK                                     (0x00000002U)
#define CSL_A15_PMCR_P_SHIFT                                    (1U)
#define CSL_A15_PMCR_P_RESETVAL                                 (0x00000000U)
#define CSL_A15_PMCR_P_MAX                                      (0x00000001U)

#define CSL_A15_PMCR_E_MASK                                     (0x00000001U)
#define CSL_A15_PMCR_E_SHIFT                                    (0U)
#define CSL_A15_PMCR_E_RESETVAL                                 (0x00000000U)
#define CSL_A15_PMCR_E_MAX                                      (0x00000001U)

#define CSL_A15_PMCR_RESETVAL                                   (0x410f3000U)

/* PMUSERENR */

#define CSL_A15_PMUSERENR_EN_MASK                               (0x00000001U)
#define CSL_A15_PMUSERENR_EN_SHIFT                              (0U)
#define CSL_A15_PMUSERENR_EN_RESETVAL                           (0x00000000U)
#define CSL_A15_PMUSERENR_EN_MAX                                (0x00000001U)

#define CSL_A15_PMUSERENR_RESETVAL                              (0x00000000U)

/* PMCEID0 */

#define CSL_A15_PMCEID0_BUSCYCLE_MASK                           (0x20000000U)
#define CSL_A15_PMCEID0_BUSCYCLE_SHIFT                          (29U)
#define CSL_A15_PMCEID0_BUSCYCLE_RESETVAL                       (0x00000001U)
#define CSL_A15_PMCEID0_BUSCYCLE_MAX                            (0x00000001U)

#define CSL_A15_PMCEID0_PASSWRITETOTTB_MASK                     (0x10000000U)
#define CSL_A15_PMCEID0_PASSWRITETOTTB_SHIFT                    (28U)
#define CSL_A15_PMCEID0_PASSWRITETOTTB_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_PASSWRITETOTTB_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_SPECEXC_MASK                            (0x08000000U)
#define CSL_A15_PMCEID0_SPECEXC_SHIFT                           (27U)
#define CSL_A15_PMCEID0_SPECEXC_RESETVAL                        (0x00000001U)
#define CSL_A15_PMCEID0_SPECEXC_MAX                             (0x00000001U)

#define CSL_A15_PMCEID0_LOCALMEMERR_MASK                        (0x04000000U)
#define CSL_A15_PMCEID0_LOCALMEMERR_SHIFT                       (26U)
#define CSL_A15_PMCEID0_LOCALMEMERR_RESETVAL                    (0x00000001U)
#define CSL_A15_PMCEID0_LOCALMEMERR_MAX                         (0x00000001U)

#define CSL_A15_PMCEID0_BUSACCESS_MASK                          (0x02000000U)
#define CSL_A15_PMCEID0_BUSACCESS_SHIFT                         (25U)
#define CSL_A15_PMCEID0_BUSACCESS_RESETVAL                      (0x00000001U)
#define CSL_A15_PMCEID0_BUSACCESS_MAX                           (0x00000001U)

#define CSL_A15_PMCEID0_L2DCACHEWB_MASK                         (0x01000000U)
#define CSL_A15_PMCEID0_L2DCACHEWB_SHIFT                        (24U)
#define CSL_A15_PMCEID0_L2DCACHEWB_RESETVAL                     (0x00000001U)
#define CSL_A15_PMCEID0_L2DCACHEWB_MAX                          (0x00000001U)

#define CSL_A15_PMCEID0_L2DCACHEREFILL_MASK                     (0x00800000U)
#define CSL_A15_PMCEID0_L2DCACHEREFILL_SHIFT                    (23U)
#define CSL_A15_PMCEID0_L2DCACHEREFILL_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L2DCACHEREFILL_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_L2DCACHEACCESS_MASK                     (0x00400000U)
#define CSL_A15_PMCEID0_L2DCACHEACCESS_SHIFT                    (22U)
#define CSL_A15_PMCEID0_L2DCACHEACCESS_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L2DCACHEACCESS_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_L1DCACHEWB_MASK                         (0x00200000U)
#define CSL_A15_PMCEID0_L1DCACHEWB_SHIFT                        (21U)
#define CSL_A15_PMCEID0_L1DCACHEWB_RESETVAL                     (0x00000001U)
#define CSL_A15_PMCEID0_L1DCACHEWB_MAX                          (0x00000001U)

#define CSL_A15_PMCEID0_L1ICACHEACCESS_MASK                     (0x00100000U)
#define CSL_A15_PMCEID0_L1ICACHEACCESS_SHIFT                    (20U)
#define CSL_A15_PMCEID0_L1ICACHEACCESS_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L1ICACHEACCESS_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_DATAMEMACCESS_MASK                      (0x00080000U)
#define CSL_A15_PMCEID0_DATAMEMACCESS_SHIFT                     (19U)
#define CSL_A15_PMCEID0_DATAMEMACCESS_RESETVAL                  (0x00000001U)
#define CSL_A15_PMCEID0_DATAMEMACCESS_MAX                       (0x00000001U)

#define CSL_A15_PMCEID0_PREDBRNSPECEXC_MASK                     (0x00040000U)
#define CSL_A15_PMCEID0_PREDBRNSPECEXC_SHIFT                    (18U)
#define CSL_A15_PMCEID0_PREDBRNSPECEXC_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_PREDBRNSPECEXC_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_CYCLE_MASK                              (0x00020000U)
#define CSL_A15_PMCEID0_CYCLE_SHIFT                             (17U)
#define CSL_A15_PMCEID0_CYCLE_RESETVAL                          (0x00000001U)
#define CSL_A15_PMCEID0_CYCLE_MAX                               (0x00000001U)

#define CSL_A15_PMCEID0_MISPREDBRNSPECEXC_MASK                  (0x00010000U)
#define CSL_A15_PMCEID0_MISPREDBRNSPECEXC_SHIFT                 (16U)
#define CSL_A15_PMCEID0_MISPREDBRNSPECEXC_RESETVAL              (0x00000001U)
#define CSL_A15_PMCEID0_MISPREDBRNSPECEXC_MAX                   (0x00000001U)

#define CSL_A15_PMCEID0_PASSUNALGNLS_MASK                       (0x00008000U)
#define CSL_A15_PMCEID0_PASSUNALGNLS_SHIFT                      (15U)
#define CSL_A15_PMCEID0_PASSUNALGNLS_RESETVAL                   (0x00000000U)
#define CSL_A15_PMCEID0_PASSUNALGNLS_MAX                        (0x00000001U)

#define CSL_A15_PMCEID0_PASSPRCRETURN_MASK                      (0x00004000U)
#define CSL_A15_PMCEID0_PASSPRCRETURN_SHIFT                     (14U)
#define CSL_A15_PMCEID0_PASSPRCRETURN_RESETVAL                  (0x00000000U)
#define CSL_A15_PMCEID0_PASSPRCRETURN_MAX                       (0x00000001U)

#define CSL_A15_PMCEID0_IMMBRN_MASK                             (0x00002000U)
#define CSL_A15_PMCEID0_IMMBRN_SHIFT                            (13U)
#define CSL_A15_PMCEID0_IMMBRN_RESETVAL                         (0x00000000U)
#define CSL_A15_PMCEID0_IMMBRN_MAX                              (0x00000001U)

#define CSL_A15_PMCEID0_PASSSWCHANGEPC_MASK                     (0x00001000U)
#define CSL_A15_PMCEID0_PASSSWCHANGEPC_SHIFT                    (12U)
#define CSL_A15_PMCEID0_PASSSWCHANGEPC_RESETVAL                 (0x00000000U)
#define CSL_A15_PMCEID0_PASSSWCHANGEPC_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_PASSWRITETOCONTEXTIDR_MASK              (0x00000800U)
#define CSL_A15_PMCEID0_PASSWRITETOCONTEXTIDR_SHIFT             (11U)
#define CSL_A15_PMCEID0_PASSWRITETOCONTEXTIDR_RESETVAL          (0x00000001U)
#define CSL_A15_PMCEID0_PASSWRITETOCONTEXTIDR_MAX               (0x00000001U)

#define CSL_A15_PMCEID0_PASSEXCRETURN_MASK                      (0x00000400U)
#define CSL_A15_PMCEID0_PASSEXCRETURN_SHIFT                     (10U)
#define CSL_A15_PMCEID0_PASSEXCRETURN_RESETVAL                  (0x00000001U)
#define CSL_A15_PMCEID0_PASSEXCRETURN_MAX                       (0x00000001U)

#define CSL_A15_PMCEID0_EXCTAKEN_MASK                           (0x00000200U)
#define CSL_A15_PMCEID0_EXCTAKEN_SHIFT                          (9U)
#define CSL_A15_PMCEID0_EXCTAKEN_RESETVAL                       (0x00000001U)
#define CSL_A15_PMCEID0_EXCTAKEN_MAX                            (0x00000001U)

#define CSL_A15_PMCEID0_INSTARCHEXC_MASK                        (0x00000100U)
#define CSL_A15_PMCEID0_INSTARCHEXC_SHIFT                       (8U)
#define CSL_A15_PMCEID0_INSTARCHEXC_RESETVAL                    (0x00000001U)
#define CSL_A15_PMCEID0_INSTARCHEXC_MAX                         (0x00000001U)

#define CSL_A15_PMCEID0_PASSSTORE_MASK                          (0x00000080U)
#define CSL_A15_PMCEID0_PASSSTORE_SHIFT                         (7U)
#define CSL_A15_PMCEID0_PASSSTORE_RESETVAL                      (0x00000000U)
#define CSL_A15_PMCEID0_PASSSTORE_MAX                           (0x00000001U)

#define CSL_A15_PMCEID0_PASSLOAD_MASK                           (0x00000040U)
#define CSL_A15_PMCEID0_PASSLOAD_SHIFT                          (6U)
#define CSL_A15_PMCEID0_PASSLOAD_RESETVAL                       (0x00000000U)
#define CSL_A15_PMCEID0_PASSLOAD_MAX                            (0x00000001U)

#define CSL_A15_PMCEID0_L1DATATLBREFILL_MASK                    (0x00000020U)
#define CSL_A15_PMCEID0_L1DATATLBREFILL_SHIFT                   (5U)
#define CSL_A15_PMCEID0_L1DATATLBREFILL_RESETVAL                (0x00000001U)
#define CSL_A15_PMCEID0_L1DATATLBREFILL_MAX                     (0x00000001U)

#define CSL_A15_PMCEID0_L1DCACHEACCESS_MASK                     (0x00000010U)
#define CSL_A15_PMCEID0_L1DCACHEACCESS_SHIFT                    (4U)
#define CSL_A15_PMCEID0_L1DCACHEACCESS_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L1DCACHEACCESS_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_L1DCACHEREFILL_MASK                     (0x00000008U)
#define CSL_A15_PMCEID0_L1DCACHEREFILL_SHIFT                    (3U)
#define CSL_A15_PMCEID0_L1DCACHEREFILL_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L1DCACHEREFILL_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_L1INSTTLBREFILL_MASK                    (0x00000004U)
#define CSL_A15_PMCEID0_L1INSTTLBREFILL_SHIFT                   (2U)
#define CSL_A15_PMCEID0_L1INSTTLBREFILL_RESETVAL                (0x00000001U)
#define CSL_A15_PMCEID0_L1INSTTLBREFILL_MAX                     (0x00000001U)

#define CSL_A15_PMCEID0_L1ICACHEREFILL_MASK                     (0x00000002U)
#define CSL_A15_PMCEID0_L1ICACHEREFILL_SHIFT                    (1U)
#define CSL_A15_PMCEID0_L1ICACHEREFILL_RESETVAL                 (0x00000001U)
#define CSL_A15_PMCEID0_L1ICACHEREFILL_MAX                      (0x00000001U)

#define CSL_A15_PMCEID0_PASSSWINC_MASK                          (0x00000001U)
#define CSL_A15_PMCEID0_PASSSWINC_SHIFT                         (0U)
#define CSL_A15_PMCEID0_PASSSWINC_RESETVAL                      (0x00000001U)
#define CSL_A15_PMCEID0_PASSSWINC_MAX                           (0x00000001U)

#define CSL_A15_PMCEID0_RESETVAL                                (0x3fff0f3fU)

/* PMCEID1 */

#define CSL_A15_PMCEID1_RESETVAL                                (0x00000000U)

/* PMLAR */

#define CSL_A15_PMLAR_LOCKACCESSCONTROL_MASK                    (0xFFFFFFFFU)
#define CSL_A15_PMLAR_LOCKACCESSCONTROL_SHIFT                   (0U)
#define CSL_A15_PMLAR_LOCKACCESSCONTROL_RESETVAL                (0x00000000U)
#define CSL_A15_PMLAR_LOCKACCESSCONTROL_MAX                     (0xffffffffU)

#define CSL_A15_PMLAR_RESETVAL                                  (0x00000000U)

/* PMLSR */

#define CSL_A15_PMLSR_NTT_MASK                                  (0x00000004U)
#define CSL_A15_PMLSR_NTT_SHIFT                                 (2U)
#define CSL_A15_PMLSR_NTT_RESETVAL                              (0x00000000U)
#define CSL_A15_PMLSR_NTT_MAX                                   (0x00000001U)

#define CSL_A15_PMLSR_SLK_MASK                                  (0x00000002U)
#define CSL_A15_PMLSR_SLK_SHIFT                                 (1U)
#define CSL_A15_PMLSR_SLK_RESETVAL                              (0x00000000U)
#define CSL_A15_PMLSR_SLK_MAX                                   (0x00000001U)

#define CSL_A15_PMLSR_SLI_MASK                                  (0x00000001U)
#define CSL_A15_PMLSR_SLI_SHIFT                                 (0U)
#define CSL_A15_PMLSR_SLI_RESETVAL                              (0x00000000U)
#define CSL_A15_PMLSR_SLI_MAX                                   (0x00000001U)

#define CSL_A15_PMLSR_RESETVAL                                  (0x00000000U)

/* PMAUTHSTATUS */

#define CSL_A15_PMAUTHSTATUS_SECNINVDBGFTIMP_MASK               (0x00000080U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGFTIMP_SHIFT              (7U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGFTIMP_RESETVAL           (0x00000001U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGFTIMP_MAX                (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_SECNINVDBGEN_MASK                  (0x00000040U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGEN_SHIFT                 (6U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGEN_RESETVAL              (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_SECNINVDBGEN_MAX                   (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_SECINVDBGFTIMP_MASK                (0x00000020U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGFTIMP_SHIFT               (5U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGFTIMP_RESETVAL            (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGFTIMP_MAX                 (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_SECINVDBGEN_MASK                   (0x00000010U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGEN_SHIFT                  (4U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGEN_RESETVAL               (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_SECINVDBGEN_MAX                    (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGFTIMP_MASK              (0x00000008U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGFTIMP_SHIFT             (3U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGFTIMP_RESETVAL          (0x00000001U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGFTIMP_MAX               (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGEN_MASK                 (0x00000004U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGEN_SHIFT                (2U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGEN_RESETVAL             (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_NSECNINVDBGEN_MAX                  (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_NSECINVDBGFTIMP_MASK               (0x00000002U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGFTIMP_SHIFT              (1U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGFTIMP_RESETVAL           (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGFTIMP_MAX                (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_NSECINVDBGEN_MASK                  (0x00000001U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGEN_SHIFT                 (0U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGEN_RESETVAL              (0x00000000U)
#define CSL_A15_PMAUTHSTATUS_NSECINVDBGEN_MAX                   (0x00000001U)

#define CSL_A15_PMAUTHSTATUS_RESETVAL                           (0x00000088U)

/* PMDEVTYPE */

#define CSL_A15_PMDEVTYPE_T_MASK                                (0x000000F0U)
#define CSL_A15_PMDEVTYPE_T_SHIFT                               (4U)
#define CSL_A15_PMDEVTYPE_T_RESETVAL                            (0x00000001U)
#define CSL_A15_PMDEVTYPE_T_MAX                                 (0x0000000fU)

#define CSL_A15_PMDEVTYPE_C_MASK                                (0x0000000FU)
#define CSL_A15_PMDEVTYPE_C_SHIFT                               (0U)
#define CSL_A15_PMDEVTYPE_C_RESETVAL                            (0x00000006U)
#define CSL_A15_PMDEVTYPE_C_MAX                                 (0x0000000fU)

#define CSL_A15_PMDEVTYPE_RESETVAL                              (0x00000016U)

/* PMPID4 */

#define CSL_A15_PMPID4_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID4_PID_SHIFT                                (0U)
#define CSL_A15_PMPID4_PID_RESETVAL                             (0x00000004U)
#define CSL_A15_PMPID4_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID4_RESETVAL                                 (0x00000004U)

/* PMPID5 */

#define CSL_A15_PMPID5_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID5_PID_SHIFT                                (0U)
#define CSL_A15_PMPID5_PID_RESETVAL                             (0x00000000U)
#define CSL_A15_PMPID5_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID5_RESETVAL                                 (0x00000000U)

/* PMPID6 */

#define CSL_A15_PMPID6_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID6_PID_SHIFT                                (0U)
#define CSL_A15_PMPID6_PID_RESETVAL                             (0x00000000U)
#define CSL_A15_PMPID6_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID6_RESETVAL                                 (0x00000000U)

/* PMPID7 */

#define CSL_A15_PMPID7_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID7_PID_SHIFT                                (0U)
#define CSL_A15_PMPID7_PID_RESETVAL                             (0x00000000U)
#define CSL_A15_PMPID7_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID7_RESETVAL                                 (0x00000000U)

/* PMPID0 */

#define CSL_A15_PMPID0_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID0_PID_SHIFT                                (0U)
#define CSL_A15_PMPID0_PID_RESETVAL                             (0x000000afU)
#define CSL_A15_PMPID0_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID0_RESETVAL                                 (0x000000afU)

/* PMPID1 */

#define CSL_A15_PMPID1_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID1_PID_SHIFT                                (0U)
#define CSL_A15_PMPID1_PID_RESETVAL                             (0x000000b9U)
#define CSL_A15_PMPID1_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID1_RESETVAL                                 (0x000000b9U)

/* PMPID2 */

#define CSL_A15_PMPID2_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID2_PID_SHIFT                                (0U)
#define CSL_A15_PMPID2_PID_RESETVAL                             (0x0000000bU)
#define CSL_A15_PMPID2_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID2_RESETVAL                                 (0x0000000bU)

/* PMPID3 */

#define CSL_A15_PMPID3_PID_MASK                                 (0x000000FFU)
#define CSL_A15_PMPID3_PID_SHIFT                                (0U)
#define CSL_A15_PMPID3_PID_RESETVAL                             (0x00000000U)
#define CSL_A15_PMPID3_PID_MAX                                  (0x000000ffU)

#define CSL_A15_PMPID3_RESETVAL                                 (0x00000000U)

/* PMCID0 */

#define CSL_A15_PMCID0_CID_MASK                                 (0x000000FFU)
#define CSL_A15_PMCID0_CID_SHIFT                                (0U)
#define CSL_A15_PMCID0_CID_RESETVAL                             (0x0000000dU)
#define CSL_A15_PMCID0_CID_MAX                                  (0x000000ffU)

#define CSL_A15_PMCID0_RESETVAL                                 (0x0000000dU)

/* PMCID1 */

#define CSL_A15_PMCID1_CID_MASK                                 (0x000000FFU)
#define CSL_A15_PMCID1_CID_SHIFT                                (0U)
#define CSL_A15_PMCID1_CID_RESETVAL                             (0x00000090U)
#define CSL_A15_PMCID1_CID_MAX                                  (0x000000ffU)

#define CSL_A15_PMCID1_RESETVAL                                 (0x00000090U)

/* PMCID2 */

#define CSL_A15_PMCID2_CID_MASK                                 (0x000000FFU)
#define CSL_A15_PMCID2_CID_SHIFT                                (0U)
#define CSL_A15_PMCID2_CID_RESETVAL                             (0x00000005U)
#define CSL_A15_PMCID2_CID_MAX                                  (0x000000ffU)

#define CSL_A15_PMCID2_RESETVAL                                 (0x00000005U)

/* PMCID3 */

#define CSL_A15_PMCID3_CID_MASK                                 (0x000000FFU)
#define CSL_A15_PMCID3_CID_SHIFT                                (0U)
#define CSL_A15_PMCID3_CID_RESETVAL                             (0x000000b1U)
#define CSL_A15_PMCID3_CID_MAX                                  (0x000000ffU)

#define CSL_A15_PMCID3_RESETVAL                                 (0x000000b1U)

#ifdef __cplusplus
}
#endif
#endif
