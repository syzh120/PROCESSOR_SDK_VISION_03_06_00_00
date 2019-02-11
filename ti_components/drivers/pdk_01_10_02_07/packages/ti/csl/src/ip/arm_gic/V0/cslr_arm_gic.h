/********************************************************************
 * Copyright (C) 2011-2016 Texas Instruments Incorporated.
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
#ifndef CSLR_ARM_GIC_H_V0
#define CSLR_ARM_GIC_H_V0

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for Distributor
**************************************************************************/
typedef struct {
    volatile Uint32 GICD_CTLR;
    volatile Uint32 GICD_TYPER;
    volatile Uint32 GICD_IIDR;
    volatile Uint8  RSVD0[116];
    volatile Uint32 GICD_IGROUPR[16];
    volatile Uint8  RSVD1[64];
    volatile Uint32 GICD_ISENABLER[16];
    volatile Uint8  RSVD2[64];
    volatile Uint32 GICD_ICENABLER[16];
    volatile Uint8  RSVD3[64];
    volatile Uint32 GICD_ISPENDR[16];
    volatile Uint8  RSVD4[64];
    volatile Uint32 GICD_ICPENDR[16];
    volatile Uint8  RSVD5[64];
    volatile Uint32 GICD_ISACTIVER[16];
    volatile Uint8  RSVD6[64];
    volatile Uint32 GICD_ICACTIVER[16];
    volatile Uint8  RSVD7[64];
    volatile Uint32 GICD_IPRIORITYR[128];
    volatile Uint8  RSVD8[512];
    volatile Uint32 GICD_ITARGETSR[128];
    volatile Uint8  RSVD9[512];
    volatile Uint32 GICD_ICFGR[32];
    volatile Uint8  RSVD10[128];
    volatile Uint32 GICD_PPISR;
    volatile Uint32 GICD_SPISR[15];
    volatile Uint8  RSVD11[448];
    volatile Uint32 GICD_SGIR;
    volatile Uint8  RSVD12[12];
    volatile Uint32 GICD_CPENDSGIR[4];
    volatile Uint32 GICD_SPENDSGIR[4];
    volatile Uint8  RSVD13[160];
    volatile Uint32 GICD_PIDR4;
    volatile Uint32 GICD_PIDR5;
    volatile Uint32 GICD_PIDR6;
    volatile Uint32 GICD_PIDR7;
    volatile Uint32 GICD_PIDR0;
    volatile Uint32 GICD_PIDR1;
    volatile Uint32 GICD_PIDR2;
    volatile Uint32 GICD_PIDR3;
    volatile Uint32 GICD_CIDR[4];
} CSL_ArmgicDistributorRegs;


/**************************************************************************
* Register Overlay Structure for GICC
**************************************************************************/
typedef struct {
    volatile Uint32 GICC_CTLR;
    volatile Uint32 GICC_PMR;
    volatile Uint32 GICC_BPR;
    volatile Uint32 GICC_IAR;
    volatile Uint32 GICC_EOIR;
    volatile Uint32 GICC_RPR;
    volatile Uint32 GICC_HPPIR;
    volatile Uint32 GICC_ABPR;
    volatile Uint32 GICC_AIAR;
    volatile Uint32 GICC_AEOIR;
    volatile Uint32 GICC_AHPPIR;
    volatile Uint8  RSVD0[164];
    volatile Uint32 GICC_APR0;
    volatile Uint8  RSVD1[12];
    volatile Uint32 GICC_NSAPR0;
    volatile Uint8  RSVD2[24];
    volatile Uint32 GICC_IIDR;
    volatile Uint8  RSVD3[3840];
    volatile Uint32 GICC_DIR;
} CSL_ArmgicGiccRegs;


/**************************************************************************
* Register Overlay Structure for GICH
**************************************************************************/
typedef struct {
    volatile Uint32 GICH_HCR;
    volatile Uint32 GICH_VTR;
    volatile Uint32 GICH_VMCR;
    volatile Uint8  RSVD0[4];
    volatile Uint32 GICH_MISR;
    volatile Uint8  RSVD1[12];
    volatile Uint32 GICH_EISR0;
    volatile Uint8  RSVD2[12];
    volatile Uint32 GICH_ELSR0;
    volatile Uint8  RSVD3[188];
    volatile Uint32 GICH_APR0;
    volatile Uint8  RSVD4[12];
    volatile Uint32 GICH_LR0;
    volatile Uint32 GICH_LR1;
    volatile Uint32 GICH_LR2;
    volatile Uint32 GICH_LR3;
} CSL_ArmgicGichRegs;


/**************************************************************************
* Register Overlay Structure for GICV
**************************************************************************/
typedef struct {
    volatile Uint32 GICV_CTLR;
    volatile Uint32 GICV_PMR;
    volatile Uint32 GICV_BPR;
    volatile Uint32 GICV_IAR;
    volatile Uint32 GICV_EOIR;
    volatile Uint32 GICV_RPR;
    volatile Uint32 GICV_HPPIR;
    volatile Uint32 GICV_ABPR;
    volatile Uint32 GICV_AIAR;
    volatile Uint32 GICV_AEOIR;
    volatile Uint32 GICV_AHPPIR;
    volatile Uint8  RSVD0[164];
    volatile Uint32 GICV_APR0;
    volatile Uint8  RSVD1[40];
    volatile Uint32 GICV_IIDR;
    volatile Uint8  RSVD2[3840];
    volatile Uint32 GICV_DIR;
} CSL_ArmgicGicvRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint8  RSVD3[4096];
    CSL_ArmgicDistributorRegs	DISTRIBUTOR;
    CSL_ArmgicGiccRegs	GICC;
    volatile Uint8  RSVD4[4092];
    CSL_ArmgicGichRegs	GICH;
    volatile Uint8  RSVD5[7920];
    CSL_ArmgicGicvRegs	GICV;
} CSL_ArmGicRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* Distributor Control Register */
#define CSL_ARMGIC_GICD_CTLR                                    (0x1000U)

/* Interrupt Controller Type Register */
#define CSL_ARMGIC_GICD_TYPER                                   (0x1004U)

/* Distributor Implementer Identification Register */
#define CSL_ARMGIC_GICD_IIDR                                    (0x1008U)

/* Interrupt Group Registers */
#define CSL_ARMGIC_GICD_IGROUPR(i)                              (0x1080U + ((i) * (0x4U)))

/* Interrupt Set-Enable Registers */
#define CSL_ARMGIC_GICD_ISENABLER(i)                            (0x1100U + ((i) * (0x4U)))

/* Interrupt Clear-Enable Registers */
#define CSL_ARMGIC_GICD_ICENABLER(i)                            (0x1180U + ((i) * (0x4U)))

/* Interrupt Set-Pending Registers */
#define CSL_ARMGIC_GICD_ISPENDR(i)                              (0x1200U + ((i) * (0x4U)))

/* Interrupt Clear-Pending Registers */
#define CSL_ARMGIC_GICD_ICPENDR(i)                              (0x1280U + ((i) * (0x4U)))

/* Interrupt Set-Active Registers */
#define CSL_ARMGIC_GICD_ISACTIVER(i)                            (0x1300U + ((i) * (0x4U)))

/* Interrupt Priority Registers */
#define CSL_ARMGIC_GICD_IPRIORITYR(i)                           (0x1400U + ((i) * (0x4U)))

/* Interrupt Processor Targets Registers */
#define CSL_ARMGIC_GICD_ITARGETSR(i)                            (0x1800U + ((i) * (0x4U)))

/* Interrupt Configuration Registers */
#define CSL_ARMGIC_GICD_ICFGR(i)                                (0x1C00U + ((i) * (0x4U)))

/* Private Peripheral Interrupt Status Register */
#define CSL_ARMGIC_GICD_PPISR                                   (0x1D00U)

/* Shared Peripheral Interrupt Status Registers */
#define CSL_ARMGIC_GICD_SPISR(i)                                (0x1D04U + ((i) * (0x4U)))

/* Software Generated Interrupt Register */
#define CSL_ARMGIC_GICD_SGIR                                    (0x1F00U)

/* SGI Clear-Pending Registers */
#define CSL_ARMGIC_GICD_CPENDSGIR(i)                            (0x1F10U + ((i) * (0x4U)))

/* SGI Set-Pending Registers */
#define CSL_ARMGIC_GICD_SPENDSGIR(i)                            (0x1F20U + ((i) * (0x4U)))

/* Peripheral ID4 Register */
#define CSL_ARMGIC_GICD_PIDR4                                   (0x1FD0U)

/* Peripheral ID5 Register */
#define CSL_ARMGIC_GICD_PIDR5                                   (0x1FD4U)

/* Peripheral ID6 Register */
#define CSL_ARMGIC_GICD_PIDR6                                   (0x1FD8U)

/* Peripheral ID7 Register */
#define CSL_ARMGIC_GICD_PIDR7                                   (0x1FDCU)

/* Peripheral ID0 Register */
#define CSL_ARMGIC_GICD_PIDR0                                   (0x1FE0U)

/* Peripheral ID1 Register */
#define CSL_ARMGIC_GICD_PIDR1                                   (0x1FE4U)

/* Peripheral ID2 Register */
#define CSL_ARMGIC_GICD_PIDR2                                   (0x1FE8U)

/* Peripheral ID3 Register */
#define CSL_ARMGIC_GICD_PIDR3                                   (0x1FECU)

/* Component ID0 Register */
#define CSL_ARMGIC_GICD_CIDR(i)                                 (0x1FF0U + ((i) * (0x4U)))

/* Interrupt Clear-Active Registers */
#define CSL_ARMGIC_GICD_ICACTIVER(i)                            (0x1380U + ((i) * (0x4U)))

/* CPU Interface Control Register */
#define CSL_ARMGIC_GICC_CTLR                                    (0x2000U)

/* GICC_PMR */
#define CSL_ARMGIC_GICC_PMR                                     (0x2004U)

/* Binary Point Register */
#define CSL_ARMGIC_GICC_BPR                                     (0x2008U)

/* Interrupt Acknowledge Register */
#define CSL_ARMGIC_GICC_IAR                                     (0x200CU)

/* End of Interrupt Register */
#define CSL_ARMGIC_GICC_EOIR                                    (0x2010U)

/* Running Priority Register */
#define CSL_ARMGIC_GICC_RPR                                     (0x2014U)

/* Highest Priority Pending Interrupt Register */
#define CSL_ARMGIC_GICC_HPPIR                                   (0x2018U)

/* Aliased Binary Point Register */
#define CSL_ARMGIC_GICC_ABPR                                    (0x201CU)

/* Aliased Interrupt Acknowledge Register */
#define CSL_ARMGIC_GICC_AIAR                                    (0x2020U)

/* Aliased End of Interrupt Register */
#define CSL_ARMGIC_GICC_AEOIR                                   (0x2024U)

/* Aliased Highest Priority Pending Interrupt Register */
#define CSL_ARMGIC_GICC_AHPPIR                                  (0x2028U)

/* Active Priority Register */
#define CSL_ARMGIC_GICC_APR0                                    (0x20D0U)

/* Non-Secure Active Priority Register */
#define CSL_ARMGIC_GICC_NSAPR0                                  (0x20E0U)

/* CPU Interface Identification Register */
#define CSL_ARMGIC_GICC_IIDR                                    (0x20FCU)

/* Deactivate Interrupt Register */
#define CSL_ARMGIC_GICC_DIR                                     (0x3000U)

/* Hypervisor Control Register */
#define CSL_ARMGIC_GICH_HCR                                     (0x4000U)

/* VGIC Type Register */
#define CSL_ARMGIC_GICH_VTR                                     (0x4004U)

/* Virtual Machine Control Register */
#define CSL_ARMGIC_GICH_VMCR                                    (0x4008U)

/* Maintenance Interrupt Status Register */
#define CSL_ARMGIC_GICH_MISR                                    (0x4010U)

/* End of Interrupt Status Register */
#define CSL_ARMGIC_GICH_EISR0                                   (0x4020U)

/* Empty List register Status Register */
#define CSL_ARMGIC_GICH_ELSR0                                   (0x4030U)

/* Active Priority Register */
#define CSL_ARMGIC_GICH_APR0                                    (0x40F0U)

/* List Register 0 */
#define CSL_ARMGIC_GICH_LR0                                     (0x4100U)

/* List Register 1 */
#define CSL_ARMGIC_GICH_LR1                                     (0x4104U)

/* List Register 2 */
#define CSL_ARMGIC_GICH_LR2                                     (0x4108U)

/* List Register 3 */
#define CSL_ARMGIC_GICH_LR3                                     (0x410CU)

/* Virtual Machine Control Register */
#define CSL_ARMGIC_GICV_CTLR                                    (0x6000U)

/* VM Priority Mask Register */
#define CSL_ARMGIC_GICV_PMR                                     (0x6004U)

/* VM Binary Point Register */
#define CSL_ARMGIC_GICV_BPR                                     (0x6008U)

/* VM Interrupt Acknowledge Register */
#define CSL_ARMGIC_GICV_IAR                                     (0x600CU)

/* VM End of Interrupt Register */
#define CSL_ARMGIC_GICV_EOIR                                    (0x6010U)

/* VM Running Priority Register */
#define CSL_ARMGIC_GICV_RPR                                     (0x6014U)

/* VM Highest Priority Pending Interrupt Register */
#define CSL_ARMGIC_GICV_HPPIR                                   (0x6018U)

/* VM Aliased Binary Point Register */
#define CSL_ARMGIC_GICV_ABPR                                    (0x601CU)

/* VM Aliased Interrupt Acknowledge Register */
#define CSL_ARMGIC_GICV_AIAR                                    (0x6020U)

/* VM Aliased End of Interrupt Register */
#define CSL_ARMGIC_GICV_AEOIR                                   (0x6024U)

/* VM Aliased Highest Priority Pending Interrupt Register */
#define CSL_ARMGIC_GICV_AHPPIR                                  (0x6028U)

/* VM Active Priority Register */
#define CSL_ARMGIC_GICV_APR0                                    (0x60D0U)

/* VM CPU Interface Identification Register */
#define CSL_ARMGIC_GICV_IIDR                                    (0x60FCU)

/* VM Deactivate Interrupt Register */
#define CSL_ARMGIC_GICV_DIR                                     (0x7000U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* GICD_CTLR */

#define CSL_ARMGIC_GICD_CTLR_GICD_CTLR_MASK                     (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_CTLR_GICD_CTLR_SHIFT                    (0U)
#define CSL_ARMGIC_GICD_CTLR_GICD_CTLR_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICD_CTLR_GICD_CTLR_MAX                      (0xffffffffU)
#define CSL_ARMGIC_GICD_CTLR_RESETVAL                           (0x00000000U)

#if !defined(CSL_MODIFICATION)
#define CSL_ARMGIC_GICD_CTLR_INTERRUPT_IN_EN_MASK               (0x00000001U)
#endif

/* GICD_TYPER */

#define CSL_ARMGIC_GICD_TYPER_GICD_TYPER_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_TYPER_GICD_TYPER_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_TYPER_GICD_TYPER_RESETVAL               (0x00000000U)
#define CSL_ARMGIC_GICD_TYPER_GICD_TYPER_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_TYPER_RESETVAL                          (0x00000000U)

/* GICD_IIDR */

#define CSL_ARMGIC_GICD_IIDR_IMPLEMENTER_MASK                   (0x00000FFFU)
#define CSL_ARMGIC_GICD_IIDR_IMPLEMENTER_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_IIDR_IMPLEMENTER_RESETVAL               (0x0000043bU)
#define CSL_ARMGIC_GICD_IIDR_IMPLEMENTER_MAX                    (0x00000fffU)

#define CSL_ARMGIC_GICD_IIDR_REVISION_MASK                      (0x0000F000U)
#define CSL_ARMGIC_GICD_IIDR_REVISION_SHIFT                     (12U)
#define CSL_ARMGIC_GICD_IIDR_REVISION_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICD_IIDR_REVISION_MAX                       (0x0000000fU)

#define CSL_ARMGIC_GICD_IIDR_VARIANT_MASK                       (0x000F0000U)
#define CSL_ARMGIC_GICD_IIDR_VARIANT_SHIFT                      (16U)
#define CSL_ARMGIC_GICD_IIDR_VARIANT_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_IIDR_VARIANT_MAX                        (0x0000000fU)

#define CSL_ARMGIC_GICD_IIDR_PRODUCDID_MASK                     (0xFF000000U)
#define CSL_ARMGIC_GICD_IIDR_PRODUCDID_SHIFT                    (24U)
#define CSL_ARMGIC_GICD_IIDR_PRODUCDID_RESETVAL                 (0x00000002U)
#define CSL_ARMGIC_GICD_IIDR_PRODUCDID_MAX                      (0x000000ffU)

#define CSL_ARMGIC_GICD_IIDR_RESETVAL                           (0x0200043bU)

/* GICD_IGROUPR */

#define CSL_ARMGIC_GICD_IGROUPR_GICD_IGROUPR_MASK               (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_IGROUPR_GICD_IGROUPR_SHIFT              (0U)
#define CSL_ARMGIC_GICD_IGROUPR_GICD_IGROUPR_RESETVAL           (0x00000000U)
#define CSL_ARMGIC_GICD_IGROUPR_GICD_IGROUPR_MAX                (0xffffffffU)

#define CSL_ARMGIC_GICD_IGROUPR_RESETVAL                        (0x00000000U)

/* GICD_ISENABLER */

#define CSL_ARMGIC_GICD_ISENABLER_GICD_ISENABLER_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ISENABLER_GICD_ISENABLER_SHIFT          (0U)
#define CSL_ARMGIC_GICD_ISENABLER_GICD_ISENABLER_RESETVAL       (0x0000ffffU)
#define CSL_ARMGIC_GICD_ISENABLER_GICD_ISENABLER_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_ISENABLER_RESETVAL                      (0x0000ffffU)

#if !defined(CSL_MODIFICATION)
/* Macro to get mask for set-enable and clear-enable register bits */
#define CSL_ARMGIC_GICD_SET_CLR_MASK(intrNum)                  ((uint32_t) 0x1 << ((intrNum) % 32U))
#endif

/* GICD_ICENABLER */

#define CSL_ARMGIC_GICD_ICENABLER_GICD_ICENABLER_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ICENABLER_GICD_ICENABLER_SHIFT          (0U)
#define CSL_ARMGIC_GICD_ICENABLER_GICD_ICENABLER_RESETVAL       (0x0000ffffU)
#define CSL_ARMGIC_GICD_ICENABLER_GICD_ICENABLER_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_ICENABLER_RESETVAL                      (0x0000ffffU)

/* GICD_ISPENDR */

#define CSL_ARMGIC_GICD_ISPENDR_GICD_ISPENDR_MASK               (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ISPENDR_GICD_ISPENDR_SHIFT              (0U)
#define CSL_ARMGIC_GICD_ISPENDR_GICD_ISPENDR_RESETVAL           (0x00000000U)
#define CSL_ARMGIC_GICD_ISPENDR_GICD_ISPENDR_MAX                (0xffffffffU)

#define CSL_ARMGIC_GICD_ISPENDR_RESETVAL                        (0x00000000U)

/* GICD_ICPENDR */

#define CSL_ARMGIC_GICD_ICPENDR_GICD_ICPENDR_MASK               (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ICPENDR_GICD_ICPENDR_SHIFT              (0U)
#define CSL_ARMGIC_GICD_ICPENDR_GICD_ICPENDR_RESETVAL           (0x00000000U)
#define CSL_ARMGIC_GICD_ICPENDR_GICD_ICPENDR_MAX                (0xffffffffU)

#define CSL_ARMGIC_GICD_ICPENDR_RESETVAL                        (0x00000000U)

/* GICD_ISACTIVER */

#define CSL_ARMGIC_GICD_ISACTIVER_GICD_ISACTIVER_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ISACTIVER_GICD_ISACTIVER_SHIFT          (0U)
#define CSL_ARMGIC_GICD_ISACTIVER_GICD_ISACTIVER_RESETVAL       (0x00000000U)
#define CSL_ARMGIC_GICD_ISACTIVER_GICD_ISACTIVER_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_ISACTIVER_RESETVAL                      (0x00000000U)

/* GICD_IPRIORITYR */

#define CSL_ARMGIC_GICD_IPRIORITYR_GICD_IPRIORITYR_MASK         (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_IPRIORITYR_GICD_IPRIORITYR_SHIFT        (0U)
#define CSL_ARMGIC_GICD_IPRIORITYR_GICD_IPRIORITYR_RESETVAL     (0x00000000U)
#define CSL_ARMGIC_GICD_IPRIORITYR_GICD_IPRIORITYR_MAX          (0xffffffffU)

#define CSL_ARMGIC_GICD_IPRIORITYR_RESETVAL                     (0x00000000U)

/* GICD_ITARGETSR */

#define CSL_ARMGIC_GICD_ITARGETSR_GICD_ITARGETSR_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ITARGETSR_GICD_ITARGETSR_SHIFT          (0U)
#define CSL_ARMGIC_GICD_ITARGETSR_GICD_ITARGETSR_RESETVAL       (0x00000000U)
#define CSL_ARMGIC_GICD_ITARGETSR_GICD_ITARGETSR_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_ITARGETSR_RESETVAL                      (0x00000000U)

/* GICD_ICFGR */

#define CSL_ARMGIC_GICD_ICFGR_GICD_ICFGR_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ICFGR_GICD_ICFGR_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_ICFGR_GICD_ICFGR_RESETVAL               (0xaaaaaaaaU)
#define CSL_ARMGIC_GICD_ICFGR_GICD_ICFGR_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_ICFGR_RESETVAL                          (0xaaaaaaaaU)

/* GICD_PPISR */

#define CSL_ARMGIC_GICD_PPISR_GICD_PPISR_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PPISR_GICD_PPISR_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PPISR_GICD_PPISR_RESETVAL               (0x00000000U)
#define CSL_ARMGIC_GICD_PPISR_GICD_PPISR_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PPISR_RESETVAL                          (0x00000000U)

/* GICD_SPISR */

#define CSL_ARMGIC_GICD_SPISR_IRQS0_MASK                        (0x00000001U)
#define CSL_ARMGIC_GICD_SPISR_IRQS0_SHIFT                       (0U)
#define CSL_ARMGIC_GICD_SPISR_IRQS0_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS0_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS1_MASK                        (0x00000002U)
#define CSL_ARMGIC_GICD_SPISR_IRQS1_SHIFT                       (1U)
#define CSL_ARMGIC_GICD_SPISR_IRQS1_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS1_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS2_MASK                        (0x00000004U)
#define CSL_ARMGIC_GICD_SPISR_IRQS2_SHIFT                       (2U)
#define CSL_ARMGIC_GICD_SPISR_IRQS2_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS2_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS3_MASK                        (0x00000008U)
#define CSL_ARMGIC_GICD_SPISR_IRQS3_SHIFT                       (3U)
#define CSL_ARMGIC_GICD_SPISR_IRQS3_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS3_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS4_MASK                        (0x00000010U)
#define CSL_ARMGIC_GICD_SPISR_IRQS4_SHIFT                       (4U)
#define CSL_ARMGIC_GICD_SPISR_IRQS4_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS4_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS5_MASK                        (0x00000020U)
#define CSL_ARMGIC_GICD_SPISR_IRQS5_SHIFT                       (5U)
#define CSL_ARMGIC_GICD_SPISR_IRQS5_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS5_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS6_MASK                        (0x00000040U)
#define CSL_ARMGIC_GICD_SPISR_IRQS6_SHIFT                       (6U)
#define CSL_ARMGIC_GICD_SPISR_IRQS6_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS6_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS7_MASK                        (0x00000080U)
#define CSL_ARMGIC_GICD_SPISR_IRQS7_SHIFT                       (7U)
#define CSL_ARMGIC_GICD_SPISR_IRQS7_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS7_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS8_MASK                        (0x00000100U)
#define CSL_ARMGIC_GICD_SPISR_IRQS8_SHIFT                       (8U)
#define CSL_ARMGIC_GICD_SPISR_IRQS8_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS8_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS9_MASK                        (0x00000200U)
#define CSL_ARMGIC_GICD_SPISR_IRQS9_SHIFT                       (9U)
#define CSL_ARMGIC_GICD_SPISR_IRQS9_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS9_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS10_MASK                       (0x00000400U)
#define CSL_ARMGIC_GICD_SPISR_IRQS10_SHIFT                      (10U)
#define CSL_ARMGIC_GICD_SPISR_IRQS10_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS10_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS11_MASK                       (0x00000800U)
#define CSL_ARMGIC_GICD_SPISR_IRQS11_SHIFT                      (11U)
#define CSL_ARMGIC_GICD_SPISR_IRQS11_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS11_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS12_MASK                       (0x00001000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS12_SHIFT                      (12U)
#define CSL_ARMGIC_GICD_SPISR_IRQS12_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS12_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS13_MASK                       (0x00002000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS13_SHIFT                      (13U)
#define CSL_ARMGIC_GICD_SPISR_IRQS13_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS13_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS14_MASK                       (0x00004000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS14_SHIFT                      (14U)
#define CSL_ARMGIC_GICD_SPISR_IRQS14_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS14_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS15_MASK                       (0x00008000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS15_SHIFT                      (15U)
#define CSL_ARMGIC_GICD_SPISR_IRQS15_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS15_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS16_MASK                       (0x00010000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS16_SHIFT                      (16U)
#define CSL_ARMGIC_GICD_SPISR_IRQS16_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS16_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS17_MASK                       (0x00020000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS17_SHIFT                      (17U)
#define CSL_ARMGIC_GICD_SPISR_IRQS17_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS17_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS18_MASK                       (0x00040000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS18_SHIFT                      (18U)
#define CSL_ARMGIC_GICD_SPISR_IRQS18_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS18_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS19_MASK                       (0x00080000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS19_SHIFT                      (19U)
#define CSL_ARMGIC_GICD_SPISR_IRQS19_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS19_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS20_MASK                       (0x00100000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS20_SHIFT                      (20U)
#define CSL_ARMGIC_GICD_SPISR_IRQS20_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS20_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS21_MASK                       (0x00200000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS21_SHIFT                      (21U)
#define CSL_ARMGIC_GICD_SPISR_IRQS21_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS21_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS22_MASK                       (0x00400000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS22_SHIFT                      (22U)
#define CSL_ARMGIC_GICD_SPISR_IRQS22_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS22_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS23_MASK                       (0x00800000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS23_SHIFT                      (23U)
#define CSL_ARMGIC_GICD_SPISR_IRQS23_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS23_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS24_MASK                       (0x01000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS24_SHIFT                      (24U)
#define CSL_ARMGIC_GICD_SPISR_IRQS24_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS24_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS25_MASK                       (0x02000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS25_SHIFT                      (25U)
#define CSL_ARMGIC_GICD_SPISR_IRQS25_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS25_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS26_MASK                       (0x04000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS26_SHIFT                      (26U)
#define CSL_ARMGIC_GICD_SPISR_IRQS26_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS26_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS27_MASK                       (0x08000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS27_SHIFT                      (27U)
#define CSL_ARMGIC_GICD_SPISR_IRQS27_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS27_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS28_MASK                       (0x10000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS28_SHIFT                      (28U)
#define CSL_ARMGIC_GICD_SPISR_IRQS28_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS28_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS29_MASK                       (0x20000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS29_SHIFT                      (29U)
#define CSL_ARMGIC_GICD_SPISR_IRQS29_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS29_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS30_MASK                       (0x40000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS30_SHIFT                      (30U)
#define CSL_ARMGIC_GICD_SPISR_IRQS30_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS30_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_IRQS31_MASK                       (0x80000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS31_SHIFT                      (31U)
#define CSL_ARMGIC_GICD_SPISR_IRQS31_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICD_SPISR_IRQS31_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICD_SPISR_RESETVAL                          (0x00000000U)

/* GICD_SGIR */

#define CSL_ARMGIC_GICD_SGIR_SGIINTID_MASK                      (0x0000000FU)
#define CSL_ARMGIC_GICD_SGIR_SGIINTID_SHIFT                     (0U)
#define CSL_ARMGIC_GICD_SGIR_SGIINTID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICD_SGIR_SGIINTID_MAX                       (0x0000000fU)

#define CSL_ARMGIC_GICD_SGIR_SATT_MASK                          (0x00008000U)
#define CSL_ARMGIC_GICD_SGIR_SATT_SHIFT                         (15U)
#define CSL_ARMGIC_GICD_SGIR_SATT_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICD_SGIR_SATT_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICD_SGIR_CPUTARGETLIST_MASK                 (0x00FF0000U)
#define CSL_ARMGIC_GICD_SGIR_CPUTARGETLIST_SHIFT                (16U)
#define CSL_ARMGIC_GICD_SGIR_CPUTARGETLIST_RESETVAL             (0x00000000U)
#define CSL_ARMGIC_GICD_SGIR_CPUTARGETLIST_MAX                  (0x000000ffU)

#define CSL_ARMGIC_GICD_SGIR_TARGETLISTFILTER_MASK              (0x03000000U)
#define CSL_ARMGIC_GICD_SGIR_TARGETLISTFILTER_SHIFT             (24U)
#define CSL_ARMGIC_GICD_SGIR_TARGETLISTFILTER_RESETVAL          (0x00000000U)
#define CSL_ARMGIC_GICD_SGIR_TARGETLISTFILTER_MAX               (0x00000003U)

#define CSL_ARMGIC_GICD_SGIR_RESETVAL                           (0x00000000U)

/* GICD_CPENDSGIR */

#define CSL_ARMGIC_GICD_CPENDSGIR_GICD_CPENDSGIR_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_CPENDSGIR_GICD_CPENDSGIR_SHIFT          (0U)
#define CSL_ARMGIC_GICD_CPENDSGIR_GICD_CPENDSGIR_RESETVAL       (0x00000000U)
#define CSL_ARMGIC_GICD_CPENDSGIR_GICD_CPENDSGIR_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_CPENDSGIR_RESETVAL                      (0x00000000U)

/* GICD_SPENDSGIR */

#define CSL_ARMGIC_GICD_SPENDSGIR_GICD_SPENDSGIR_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_SPENDSGIR_GICD_SPENDSGIR_SHIFT          (0U)
#define CSL_ARMGIC_GICD_SPENDSGIR_GICD_SPENDSGIR_RESETVAL       (0x00000000U)
#define CSL_ARMGIC_GICD_SPENDSGIR_GICD_SPENDSGIR_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_SPENDSGIR_RESETVAL                      (0x00000000U)

/* GICD_PIDR4 */

#define CSL_ARMGIC_GICD_PIDR4_GICD_PIDR4_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PIDR4_GICD_PIDR4_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PIDR4_GICD_PIDR4_RESETVAL               (0x00000004U)
#define CSL_ARMGIC_GICD_PIDR4_GICD_PIDR4_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PIDR4_RESETVAL                          (0x00000004U)

/* GICD_PIDR5 */

#define CSL_ARMGIC_GICD_PIDR5_GICD_PIDR5_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PIDR5_GICD_PIDR5_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PIDR5_GICD_PIDR5_RESETVAL               (0x00000000U)
#define CSL_ARMGIC_GICD_PIDR5_GICD_PIDR5_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PIDR5_RESETVAL                          (0x00000000U)

/* GICD_PIDR6 */

#define CSL_ARMGIC_GICD_PIDR6_GICD_PIDR6_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PIDR6_GICD_PIDR6_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PIDR6_GICD_PIDR6_RESETVAL               (0x00000000U)
#define CSL_ARMGIC_GICD_PIDR6_GICD_PIDR6_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PIDR6_RESETVAL                          (0x00000000U)

/* GICD_PIDR7 */

#define CSL_ARMGIC_GICD_PIDR7_GICD_PIDR7_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PIDR7_GICD_PIDR7_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PIDR7_GICD_PIDR7_RESETVAL               (0x00000000U)
#define CSL_ARMGIC_GICD_PIDR7_GICD_PIDR7_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PIDR7_RESETVAL                          (0x00000000U)

/* GICD_PIDR0 */

#define CSL_ARMGIC_GICD_PIDR0_GICD_PIDR0_MASK                   (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_PIDR0_GICD_PIDR0_SHIFT                  (0U)
#define CSL_ARMGIC_GICD_PIDR0_GICD_PIDR0_RESETVAL               (0x00000090U)
#define CSL_ARMGIC_GICD_PIDR0_GICD_PIDR0_MAX                    (0xffffffffU)

#define CSL_ARMGIC_GICD_PIDR0_RESETVAL                          (0x00000090U)

/* GICD_PIDR1 */

#define CSL_ARMGIC_GICD_PIDR1_ARCHID_MASK                       (0x000000F0U)
#define CSL_ARMGIC_GICD_PIDR1_ARCHID_SHIFT                      (4U)
#define CSL_ARMGIC_GICD_PIDR1_ARCHID_RESETVAL                   (0x0000000bU)
#define CSL_ARMGIC_GICD_PIDR1_ARCHID_MAX                        (0x0000000fU)

#define CSL_ARMGIC_GICD_PIDR1_DEVID_MASK                        (0x0000000FU)
#define CSL_ARMGIC_GICD_PIDR1_DEVID_SHIFT                       (0U)
#define CSL_ARMGIC_GICD_PIDR1_DEVID_RESETVAL                    (0x00000004U)
#define CSL_ARMGIC_GICD_PIDR1_DEVID_MAX                         (0x0000000fU)

#define CSL_ARMGIC_GICD_PIDR1_RESETVAL                          (0x000000b4U)

/* GICD_PIDR2 */

#define CSL_ARMGIC_GICD_PIDR2_ARCHREV_MASK                      (0x000000F0U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHREV_SHIFT                     (4U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHREV_RESETVAL                  (0x00000002U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHREV_MAX                       (0x0000000fU)

#define CSL_ARMGIC_GICD_PIDR2_USESJEPCODE_MASK                  (0x00000008U)
#define CSL_ARMGIC_GICD_PIDR2_USESJEPCODE_SHIFT                 (3U)
#define CSL_ARMGIC_GICD_PIDR2_USESJEPCODE_RESETVAL              (0x00000001U)
#define CSL_ARMGIC_GICD_PIDR2_USESJEPCODE_MAX                   (0x00000001U)

#define CSL_ARMGIC_GICD_PIDR2_ARCHID_MASK                       (0x00000007U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHID_SHIFT                      (0U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHID_RESETVAL                   (0x00000003U)
#define CSL_ARMGIC_GICD_PIDR2_ARCHID_MAX                        (0x00000007U)

#define CSL_ARMGIC_GICD_PIDR2_RESETVAL                          (0x0000002bU)

/* GICD_PIDR3 */

#define CSL_ARMGIC_GICD_PIDR3_REVISION_MASK                     (0x000000F0U)
#define CSL_ARMGIC_GICD_PIDR3_REVISION_SHIFT                    (4U)
#define CSL_ARMGIC_GICD_PIDR3_REVISION_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICD_PIDR3_REVISION_MAX                      (0x0000000fU)

#define CSL_ARMGIC_GICD_PIDR3_RESETVAL                          (0x00000000U)

/* GICD_CIDR */

#define CSL_ARMGIC_GICD_CIDR_REVISION_MASK                      (0x000000FFU)
#define CSL_ARMGIC_GICD_CIDR_REVISION_SHIFT                     (0U)
#define CSL_ARMGIC_GICD_CIDR_REVISION_RESETVAL                  (0x0000000dU)
#define CSL_ARMGIC_GICD_CIDR_REVISION_MAX                       (0x000000ffU)

#define CSL_ARMGIC_GICD_CIDR_RESETVAL                           (0x0000000dU)

/* GICD_ICACTIVER */

#define CSL_ARMGIC_GICD_ICACTIVER_GICD_ICACTIVER_MASK           (0xFFFFFFFFU)
#define CSL_ARMGIC_GICD_ICACTIVER_GICD_ICACTIVER_SHIFT          (0U)
#define CSL_ARMGIC_GICD_ICACTIVER_GICD_ICACTIVER_RESETVAL       (0x00000000U)
#define CSL_ARMGIC_GICD_ICACTIVER_GICD_ICACTIVER_MAX            (0xffffffffU)

#define CSL_ARMGIC_GICD_ICACTIVER_RESETVAL                      (0x00000000U)

/* GICC_CTLR */

#define CSL_ARMGIC_GICC_CTLR_GICC_CTLR_MASK                     (0xFFFFFFFFU)
#define CSL_ARMGIC_GICC_CTLR_GICC_CTLR_SHIFT                    (0U)
#define CSL_ARMGIC_GICC_CTLR_GICC_CTLR_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICC_CTLR_GICC_CTLR_MAX                      (0xffffffffU)

#define CSL_ARMGIC_GICC_CTLR_RESETVAL                           (0x00000000U)

/* GICC_PMR */

#define CSL_ARMGIC_GICC_PMR_PRIORITY_MASK                       (0x000000FFU)
#define CSL_ARMGIC_GICC_PMR_PRIORITY_SHIFT                      (0U)
#define CSL_ARMGIC_GICC_PMR_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICC_PMR_PRIORITY_MAX                        (0x000000ffU)

#define CSL_ARMGIC_GICC_PMR_RESETVAL                            (0x00000000U)

/* GICC_BPR */

#define CSL_ARMGIC_GICC_BPR_BINARYPOINT_MASK                    (0x00000007U)
#define CSL_ARMGIC_GICC_BPR_BINARYPOINT_SHIFT                   (0U)
#define CSL_ARMGIC_GICC_BPR_BINARYPOINT_RESETVAL                (0x00000002U)
#define CSL_ARMGIC_GICC_BPR_BINARYPOINT_MAX                     (0x00000007U)

#define CSL_ARMGIC_GICC_BPR_RESETVAL                            (0x00000002U)

/* GICC_IAR */

#define CSL_ARMGIC_GICC_IAR_CPUID_MASK                          (0x00001C00U)
#define CSL_ARMGIC_GICC_IAR_CPUID_SHIFT                         (10U)
#define CSL_ARMGIC_GICC_IAR_CPUID_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_IAR_CPUID_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICC_IAR_ACKINTID_MASK                       (0x000003FFU)
#define CSL_ARMGIC_GICC_IAR_ACKINTID_SHIFT                      (0U)
#define CSL_ARMGIC_GICC_IAR_ACKINTID_RESETVAL                   (0x000003ffU)
#define CSL_ARMGIC_GICC_IAR_ACKINTID_MAX                        (0x000003ffU)

#define CSL_ARMGIC_GICC_IAR_RESETVAL                            (0x000003ffU)

/* GICC_EOIR */

#define CSL_ARMGIC_GICC_EOIR_CPUID_MASK                         (0x00001C00U)
#define CSL_ARMGIC_GICC_EOIR_CPUID_SHIFT                        (10U)
#define CSL_ARMGIC_GICC_EOIR_CPUID_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_EOIR_CPUID_MAX                          (0x00000007U)

#define CSL_ARMGIC_GICC_EOIR_EOINTID_MASK                       (0x000003FFU)
#define CSL_ARMGIC_GICC_EOIR_EOINTID_SHIFT                      (0U)
#define CSL_ARMGIC_GICC_EOIR_EOINTID_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICC_EOIR_EOINTID_MAX                        (0x000003ffU)

#define CSL_ARMGIC_GICC_EOIR_RESETVAL                           (0x00000000U)

/* GICC_RPR */

#define CSL_ARMGIC_GICC_RPR_PRIORITY_MASK                       (0x000000FFU)
#define CSL_ARMGIC_GICC_RPR_PRIORITY_SHIFT                      (0U)
#define CSL_ARMGIC_GICC_RPR_PRIORITY_RESETVAL                   (0x000000ffU)
#define CSL_ARMGIC_GICC_RPR_PRIORITY_MAX                        (0x000000ffU)

#define CSL_ARMGIC_GICC_RPR_RESETVAL                            (0x000000ffU)

/* GICC_HPPIR */

#define CSL_ARMGIC_GICC_HPPIR_CPUID_MASK                        (0x00001C00U)
#define CSL_ARMGIC_GICC_HPPIR_CPUID_SHIFT                       (10U)
#define CSL_ARMGIC_GICC_HPPIR_CPUID_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_HPPIR_CPUID_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICC_HPPIR_HPINTID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICC_HPPIR_HPINTID_SHIFT                     (0U)
#define CSL_ARMGIC_GICC_HPPIR_HPINTID_RESETVAL                  (0x000003ffU)
#define CSL_ARMGIC_GICC_HPPIR_HPINTID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICC_HPPIR_RESETVAL                          (0x000003ffU)

/* GICC_ABPR */

#define CSL_ARMGIC_GICC_ABPR_BINARYPOINT_MASK                   (0x00000007U)
#define CSL_ARMGIC_GICC_ABPR_BINARYPOINT_SHIFT                  (0U)
#define CSL_ARMGIC_GICC_ABPR_BINARYPOINT_RESETVAL               (0x00000003U)
#define CSL_ARMGIC_GICC_ABPR_BINARYPOINT_MAX                    (0x00000007U)

#define CSL_ARMGIC_GICC_ABPR_RESETVAL                           (0x00000003U)

/* GICC_AIAR */

#define CSL_ARMGIC_GICC_AIAR_CPUID_MASK                         (0x00001C00U)
#define CSL_ARMGIC_GICC_AIAR_CPUID_SHIFT                        (10U)
#define CSL_ARMGIC_GICC_AIAR_CPUID_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_AIAR_CPUID_MAX                          (0x00000007U)

#define CSL_ARMGIC_GICC_AIAR_AACKINTID_MASK                     (0x000003FFU)
#define CSL_ARMGIC_GICC_AIAR_AACKINTID_SHIFT                    (0U)
#define CSL_ARMGIC_GICC_AIAR_AACKINTID_RESETVAL                 (0x000003ffU)
#define CSL_ARMGIC_GICC_AIAR_AACKINTID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICC_AIAR_RESETVAL                           (0x000003ffU)

/* GICC_AEOIR */

#define CSL_ARMGIC_GICC_AEOIR_CPUID_MASK                        (0x00001C00U)
#define CSL_ARMGIC_GICC_AEOIR_CPUID_SHIFT                       (10U)
#define CSL_ARMGIC_GICC_AEOIR_CPUID_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_AEOIR_CPUID_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICC_AEOIR_AEOINTID_MASK                     (0x000003FFU)
#define CSL_ARMGIC_GICC_AEOIR_AEOINTID_SHIFT                    (0U)
#define CSL_ARMGIC_GICC_AEOIR_AEOINTID_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICC_AEOIR_AEOINTID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICC_AEOIR_RESETVAL                          (0x00000000U)

/* GICC_AHPPIR */

#define CSL_ARMGIC_GICC_AHPPIR_CPUID_MASK                       (0x00001C00U)
#define CSL_ARMGIC_GICC_AHPPIR_CPUID_SHIFT                      (10U)
#define CSL_ARMGIC_GICC_AHPPIR_CPUID_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICC_AHPPIR_CPUID_MAX                        (0x00000007U)

#define CSL_ARMGIC_GICC_AHPPIR_AHPINTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICC_AHPPIR_AHPINTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICC_AHPPIR_AHPINTID_RESETVAL                (0x000003ffU)
#define CSL_ARMGIC_GICC_AHPPIR_AHPINTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICC_AHPPIR_RESETVAL                         (0x000003ffU)

/* GICC_APR0 */

#define CSL_ARMGIC_GICC_APR0_AP31_MASK                          (0x80000000U)
#define CSL_ARMGIC_GICC_APR0_AP31_SHIFT                         (31U)
#define CSL_ARMGIC_GICC_APR0_AP31_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP31_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP30_MASK                          (0x40000000U)
#define CSL_ARMGIC_GICC_APR0_AP30_SHIFT                         (30U)
#define CSL_ARMGIC_GICC_APR0_AP30_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP30_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP29_MASK                          (0x20000000U)
#define CSL_ARMGIC_GICC_APR0_AP29_SHIFT                         (29U)
#define CSL_ARMGIC_GICC_APR0_AP29_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP29_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP28_MASK                          (0x10000000U)
#define CSL_ARMGIC_GICC_APR0_AP28_SHIFT                         (28U)
#define CSL_ARMGIC_GICC_APR0_AP28_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP28_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP27_MASK                          (0x08000000U)
#define CSL_ARMGIC_GICC_APR0_AP27_SHIFT                         (27U)
#define CSL_ARMGIC_GICC_APR0_AP27_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP27_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP26_MASK                          (0x04000000U)
#define CSL_ARMGIC_GICC_APR0_AP26_SHIFT                         (26U)
#define CSL_ARMGIC_GICC_APR0_AP26_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP26_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP25_MASK                          (0x02000000U)
#define CSL_ARMGIC_GICC_APR0_AP25_SHIFT                         (25U)
#define CSL_ARMGIC_GICC_APR0_AP25_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP25_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP24_MASK                          (0x01000000U)
#define CSL_ARMGIC_GICC_APR0_AP24_SHIFT                         (24U)
#define CSL_ARMGIC_GICC_APR0_AP24_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP24_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP23_MASK                          (0x00800000U)
#define CSL_ARMGIC_GICC_APR0_AP23_SHIFT                         (23U)
#define CSL_ARMGIC_GICC_APR0_AP23_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP23_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP22_MASK                          (0x00400000U)
#define CSL_ARMGIC_GICC_APR0_AP22_SHIFT                         (22U)
#define CSL_ARMGIC_GICC_APR0_AP22_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP22_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP21_MASK                          (0x00200000U)
#define CSL_ARMGIC_GICC_APR0_AP21_SHIFT                         (21U)
#define CSL_ARMGIC_GICC_APR0_AP21_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP21_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP20_MASK                          (0x00100000U)
#define CSL_ARMGIC_GICC_APR0_AP20_SHIFT                         (20U)
#define CSL_ARMGIC_GICC_APR0_AP20_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP20_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP19_MASK                          (0x00080000U)
#define CSL_ARMGIC_GICC_APR0_AP19_SHIFT                         (19U)
#define CSL_ARMGIC_GICC_APR0_AP19_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP19_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP18_MASK                          (0x00040000U)
#define CSL_ARMGIC_GICC_APR0_AP18_SHIFT                         (18U)
#define CSL_ARMGIC_GICC_APR0_AP18_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP18_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP17_MASK                          (0x00020000U)
#define CSL_ARMGIC_GICC_APR0_AP17_SHIFT                         (17U)
#define CSL_ARMGIC_GICC_APR0_AP17_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP17_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP16_MASK                          (0x00010000U)
#define CSL_ARMGIC_GICC_APR0_AP16_SHIFT                         (16U)
#define CSL_ARMGIC_GICC_APR0_AP16_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP16_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP15_MASK                          (0x00008000U)
#define CSL_ARMGIC_GICC_APR0_AP15_SHIFT                         (15U)
#define CSL_ARMGIC_GICC_APR0_AP15_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP15_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP14_MASK                          (0x00004000U)
#define CSL_ARMGIC_GICC_APR0_AP14_SHIFT                         (14U)
#define CSL_ARMGIC_GICC_APR0_AP14_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP14_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP13_MASK                          (0x00002000U)
#define CSL_ARMGIC_GICC_APR0_AP13_SHIFT                         (13U)
#define CSL_ARMGIC_GICC_APR0_AP13_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP13_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP12_MASK                          (0x00001000U)
#define CSL_ARMGIC_GICC_APR0_AP12_SHIFT                         (12U)
#define CSL_ARMGIC_GICC_APR0_AP12_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP12_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP11_MASK                          (0x00000800U)
#define CSL_ARMGIC_GICC_APR0_AP11_SHIFT                         (11U)
#define CSL_ARMGIC_GICC_APR0_AP11_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP11_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP10_MASK                          (0x00000400U)
#define CSL_ARMGIC_GICC_APR0_AP10_SHIFT                         (10U)
#define CSL_ARMGIC_GICC_APR0_AP10_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP10_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP9_MASK                           (0x00000200U)
#define CSL_ARMGIC_GICC_APR0_AP9_SHIFT                          (9U)
#define CSL_ARMGIC_GICC_APR0_AP9_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP9_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP8_MASK                           (0x00000100U)
#define CSL_ARMGIC_GICC_APR0_AP8_SHIFT                          (8U)
#define CSL_ARMGIC_GICC_APR0_AP8_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP8_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP7_MASK                           (0x00000080U)
#define CSL_ARMGIC_GICC_APR0_AP7_SHIFT                          (7U)
#define CSL_ARMGIC_GICC_APR0_AP7_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP7_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP6_MASK                           (0x00000040U)
#define CSL_ARMGIC_GICC_APR0_AP6_SHIFT                          (6U)
#define CSL_ARMGIC_GICC_APR0_AP6_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP6_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP5_MASK                           (0x00000020U)
#define CSL_ARMGIC_GICC_APR0_AP5_SHIFT                          (5U)
#define CSL_ARMGIC_GICC_APR0_AP5_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP5_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP4_MASK                           (0x00000010U)
#define CSL_ARMGIC_GICC_APR0_AP4_SHIFT                          (4U)
#define CSL_ARMGIC_GICC_APR0_AP4_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP4_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP3_MASK                           (0x00000008U)
#define CSL_ARMGIC_GICC_APR0_AP3_SHIFT                          (3U)
#define CSL_ARMGIC_GICC_APR0_AP3_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP3_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP2_MASK                           (0x00000004U)
#define CSL_ARMGIC_GICC_APR0_AP2_SHIFT                          (2U)
#define CSL_ARMGIC_GICC_APR0_AP2_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP2_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP1_MASK                           (0x00000002U)
#define CSL_ARMGIC_GICC_APR0_AP1_SHIFT                          (1U)
#define CSL_ARMGIC_GICC_APR0_AP1_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP1_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_AP0_MASK                           (0x00000001U)
#define CSL_ARMGIC_GICC_APR0_AP0_SHIFT                          (0U)
#define CSL_ARMGIC_GICC_APR0_AP0_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICC_APR0_AP0_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICC_APR0_RESETVAL                           (0x00000000U)

/* GICC_NSAPR0 */

#define CSL_ARMGIC_GICC_NSAPR0_AP31_MASK                        (0x80000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP31_SHIFT                       (31U)
#define CSL_ARMGIC_GICC_NSAPR0_AP31_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP31_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP30_MASK                        (0x40000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP30_SHIFT                       (30U)
#define CSL_ARMGIC_GICC_NSAPR0_AP30_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP30_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP29_MASK                        (0x20000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP29_SHIFT                       (29U)
#define CSL_ARMGIC_GICC_NSAPR0_AP29_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP29_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP28_MASK                        (0x10000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP28_SHIFT                       (28U)
#define CSL_ARMGIC_GICC_NSAPR0_AP28_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP28_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP27_MASK                        (0x08000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP27_SHIFT                       (27U)
#define CSL_ARMGIC_GICC_NSAPR0_AP27_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP27_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP26_MASK                        (0x04000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP26_SHIFT                       (26U)
#define CSL_ARMGIC_GICC_NSAPR0_AP26_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP26_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP25_MASK                        (0x02000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP25_SHIFT                       (25U)
#define CSL_ARMGIC_GICC_NSAPR0_AP25_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP25_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP24_MASK                        (0x01000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP24_SHIFT                       (24U)
#define CSL_ARMGIC_GICC_NSAPR0_AP24_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP24_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP23_MASK                        (0x00800000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP23_SHIFT                       (23U)
#define CSL_ARMGIC_GICC_NSAPR0_AP23_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP23_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP22_MASK                        (0x00400000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP22_SHIFT                       (22U)
#define CSL_ARMGIC_GICC_NSAPR0_AP22_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP22_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP21_MASK                        (0x00200000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP21_SHIFT                       (21U)
#define CSL_ARMGIC_GICC_NSAPR0_AP21_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP21_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP20_MASK                        (0x00100000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP20_SHIFT                       (20U)
#define CSL_ARMGIC_GICC_NSAPR0_AP20_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP20_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP19_MASK                        (0x00080000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP19_SHIFT                       (19U)
#define CSL_ARMGIC_GICC_NSAPR0_AP19_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP19_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP18_MASK                        (0x00040000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP18_SHIFT                       (18U)
#define CSL_ARMGIC_GICC_NSAPR0_AP18_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP18_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP17_MASK                        (0x00020000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP17_SHIFT                       (17U)
#define CSL_ARMGIC_GICC_NSAPR0_AP17_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP17_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP16_MASK                        (0x00010000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP16_SHIFT                       (16U)
#define CSL_ARMGIC_GICC_NSAPR0_AP16_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP16_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP15_MASK                        (0x00008000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP15_SHIFT                       (15U)
#define CSL_ARMGIC_GICC_NSAPR0_AP15_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP15_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP14_MASK                        (0x00004000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP14_SHIFT                       (14U)
#define CSL_ARMGIC_GICC_NSAPR0_AP14_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP14_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP13_MASK                        (0x00002000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP13_SHIFT                       (13U)
#define CSL_ARMGIC_GICC_NSAPR0_AP13_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP13_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP12_MASK                        (0x00001000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP12_SHIFT                       (12U)
#define CSL_ARMGIC_GICC_NSAPR0_AP12_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP12_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP11_MASK                        (0x00000800U)
#define CSL_ARMGIC_GICC_NSAPR0_AP11_SHIFT                       (11U)
#define CSL_ARMGIC_GICC_NSAPR0_AP11_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP11_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP10_MASK                        (0x00000400U)
#define CSL_ARMGIC_GICC_NSAPR0_AP10_SHIFT                       (10U)
#define CSL_ARMGIC_GICC_NSAPR0_AP10_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP10_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP9_MASK                         (0x00000200U)
#define CSL_ARMGIC_GICC_NSAPR0_AP9_SHIFT                        (9U)
#define CSL_ARMGIC_GICC_NSAPR0_AP9_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP9_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP8_MASK                         (0x00000100U)
#define CSL_ARMGIC_GICC_NSAPR0_AP8_SHIFT                        (8U)
#define CSL_ARMGIC_GICC_NSAPR0_AP8_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP8_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP7_MASK                         (0x00000080U)
#define CSL_ARMGIC_GICC_NSAPR0_AP7_SHIFT                        (7U)
#define CSL_ARMGIC_GICC_NSAPR0_AP7_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP7_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP6_MASK                         (0x00000040U)
#define CSL_ARMGIC_GICC_NSAPR0_AP6_SHIFT                        (6U)
#define CSL_ARMGIC_GICC_NSAPR0_AP6_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP6_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP5_MASK                         (0x00000020U)
#define CSL_ARMGIC_GICC_NSAPR0_AP5_SHIFT                        (5U)
#define CSL_ARMGIC_GICC_NSAPR0_AP5_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP5_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP4_MASK                         (0x00000010U)
#define CSL_ARMGIC_GICC_NSAPR0_AP4_SHIFT                        (4U)
#define CSL_ARMGIC_GICC_NSAPR0_AP4_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP4_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP3_MASK                         (0x00000008U)
#define CSL_ARMGIC_GICC_NSAPR0_AP3_SHIFT                        (3U)
#define CSL_ARMGIC_GICC_NSAPR0_AP3_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP3_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP2_MASK                         (0x00000004U)
#define CSL_ARMGIC_GICC_NSAPR0_AP2_SHIFT                        (2U)
#define CSL_ARMGIC_GICC_NSAPR0_AP2_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP2_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP1_MASK                         (0x00000002U)
#define CSL_ARMGIC_GICC_NSAPR0_AP1_SHIFT                        (1U)
#define CSL_ARMGIC_GICC_NSAPR0_AP1_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP1_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_AP0_MASK                         (0x00000001U)
#define CSL_ARMGIC_GICC_NSAPR0_AP0_SHIFT                        (0U)
#define CSL_ARMGIC_GICC_NSAPR0_AP0_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICC_NSAPR0_AP0_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICC_NSAPR0_RESETVAL                         (0x00000000U)

/* GICC_IIDR */

#define CSL_ARMGIC_GICC_IIDR_PRODUCTID_MASK                     (0xFFF00000U)
#define CSL_ARMGIC_GICC_IIDR_PRODUCTID_SHIFT                    (20U)
#define CSL_ARMGIC_GICC_IIDR_PRODUCTID_RESETVAL                 (0x00000020U)
#define CSL_ARMGIC_GICC_IIDR_PRODUCTID_MAX                      (0x00000fffU)

#define CSL_ARMGIC_GICC_IIDR_ARCHITECTUREVERSION_MASK           (0x000F0000U)
#define CSL_ARMGIC_GICC_IIDR_ARCHITECTUREVERSION_SHIFT          (16U)
#define CSL_ARMGIC_GICC_IIDR_ARCHITECTUREVERSION_RESETVAL       (0x00000002U)
#define CSL_ARMGIC_GICC_IIDR_ARCHITECTUREVERSION_MAX            (0x0000000fU)

#define CSL_ARMGIC_GICC_IIDR_REVISION_MASK                      (0x0000F000U)
#define CSL_ARMGIC_GICC_IIDR_REVISION_SHIFT                     (12U)
#define CSL_ARMGIC_GICC_IIDR_REVISION_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICC_IIDR_REVISION_MAX                       (0x0000000fU)

#define CSL_ARMGIC_GICC_IIDR_IMPLEMENTER_MASK                   (0x00000FFFU)
#define CSL_ARMGIC_GICC_IIDR_IMPLEMENTER_SHIFT                  (0U)
#define CSL_ARMGIC_GICC_IIDR_IMPLEMENTER_RESETVAL               (0x0000043bU)
#define CSL_ARMGIC_GICC_IIDR_IMPLEMENTER_MAX                    (0x00000fffU)

#define CSL_ARMGIC_GICC_IIDR_RESETVAL                           (0x0202043bU)

/* GICC_DIR */

#define CSL_ARMGIC_GICC_DIR_CPUID_MASK                          (0x00001C00U)
#define CSL_ARMGIC_GICC_DIR_CPUID_SHIFT                         (10U)
#define CSL_ARMGIC_GICC_DIR_CPUID_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICC_DIR_CPUID_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICC_DIR_INTERRUPTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICC_DIR_INTERRUPTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICC_DIR_INTERRUPTID_RESETVAL                (0x00000000U)
#define CSL_ARMGIC_GICC_DIR_INTERRUPTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICC_DIR_RESETVAL                            (0x00000000U)

/* GICH_HCR */

#define CSL_ARMGIC_GICH_HCR_EOICOUNT_MASK                       (0xF8000000U)
#define CSL_ARMGIC_GICH_HCR_EOICOUNT_SHIFT                      (27U)
#define CSL_ARMGIC_GICH_HCR_EOICOUNT_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_EOICOUNT_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICH_HCR_VDNSIE_MASK                         (0x00000080U)
#define CSL_ARMGIC_GICH_HCR_VDNSIE_SHIFT                        (7U)
#define CSL_ARMGIC_GICH_HCR_VDNSIE_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_VDNSIE_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_VENSIE_MASK                         (0x00000040U)
#define CSL_ARMGIC_GICH_HCR_VENSIE_SHIFT                        (6U)
#define CSL_ARMGIC_GICH_HCR_VENSIE_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_VENSIE_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_VDSIE_MASK                          (0x00000020U)
#define CSL_ARMGIC_GICH_HCR_VDSIE_SHIFT                         (5U)
#define CSL_ARMGIC_GICH_HCR_VDSIE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_VDSIE_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_VESIE_MASK                          (0x00000010U)
#define CSL_ARMGIC_GICH_HCR_VESIE_SHIFT                         (4U)
#define CSL_ARMGIC_GICH_HCR_VESIE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_VESIE_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_NPIE_MASK                           (0x00000008U)
#define CSL_ARMGIC_GICH_HCR_NPIE_SHIFT                          (3U)
#define CSL_ARMGIC_GICH_HCR_NPIE_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_NPIE_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_SKIDIE_MASK                         (0x00000004U)
#define CSL_ARMGIC_GICH_HCR_SKIDIE_SHIFT                        (2U)
#define CSL_ARMGIC_GICH_HCR_SKIDIE_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_SKIDIE_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_UIE_MASK                            (0x00000002U)
#define CSL_ARMGIC_GICH_HCR_UIE_SHIFT                           (1U)
#define CSL_ARMGIC_GICH_HCR_UIE_RESETVAL                        (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_UIE_MAX                             (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_EN_MASK                             (0x00000001U)
#define CSL_ARMGIC_GICH_HCR_EN_SHIFT                            (0U)
#define CSL_ARMGIC_GICH_HCR_EN_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_HCR_EN_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_HCR_RESETVAL                            (0x00000000U)

/* GICH_VTR */

#define CSL_ARMGIC_GICH_VTR_PRIBITS_MASK                        (0xE0000000U)
#define CSL_ARMGIC_GICH_VTR_PRIBITS_SHIFT                       (29U)
#define CSL_ARMGIC_GICH_VTR_PRIBITS_RESETVAL                    (0x00000004U)
#define CSL_ARMGIC_GICH_VTR_PRIBITS_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICH_VTR_PREBITS_MASK                        (0x1C000000U)
#define CSL_ARMGIC_GICH_VTR_PREBITS_SHIFT                       (26U)
#define CSL_ARMGIC_GICH_VTR_PREBITS_RESETVAL                    (0x00000004U)
#define CSL_ARMGIC_GICH_VTR_PREBITS_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICH_VTR_LISTREGS_MASK                       (0x0000003FU)
#define CSL_ARMGIC_GICH_VTR_LISTREGS_SHIFT                      (0U)
#define CSL_ARMGIC_GICH_VTR_LISTREGS_RESETVAL                   (0x00000003U)
#define CSL_ARMGIC_GICH_VTR_LISTREGS_MAX                        (0x0000003fU)

#define CSL_ARMGIC_GICH_VTR_RESETVAL                            (0x90000003U)

/* GICH_VMCR */

#define CSL_ARMGIC_GICH_VMCR_VMPRIMASK_MASK                     (0xF8000000U)
#define CSL_ARMGIC_GICH_VMCR_VMPRIMASK_SHIFT                    (27U)
#define CSL_ARMGIC_GICH_VMCR_VMPRIMASK_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMPRIMASK_MAX                      (0x0000001fU)

#define CSL_ARMGIC_GICH_VMCR_VMBP_MASK                          (0x00E00000U)
#define CSL_ARMGIC_GICH_VMCR_VMBP_SHIFT                         (21U)
#define CSL_ARMGIC_GICH_VMCR_VMBP_RESETVAL                      (0x00000002U)
#define CSL_ARMGIC_GICH_VMCR_VMBP_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICH_VMCR_VMNSBP_MASK                        (0x001C0000U)
#define CSL_ARMGIC_GICH_VMCR_VMNSBP_SHIFT                       (18U)
#define CSL_ARMGIC_GICH_VMCR_VMNSBP_RESETVAL                    (0x00000003U)
#define CSL_ARMGIC_GICH_VMCR_VMNSBP_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICH_VMCR_VEM_MASK                           (0x00000200U)
#define CSL_ARMGIC_GICH_VMCR_VEM_SHIFT                          (9U)
#define CSL_ARMGIC_GICH_VMCR_VEM_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VEM_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_VMSBPR_MASK                        (0x00000010U)
#define CSL_ARMGIC_GICH_VMCR_VMSBPR_SHIFT                       (4U)
#define CSL_ARMGIC_GICH_VMCR_VMSBPR_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMSBPR_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_VMFIQEN_MASK                       (0x00000008U)
#define CSL_ARMGIC_GICH_VMCR_VMFIQEN_SHIFT                      (3U)
#define CSL_ARMGIC_GICH_VMCR_VMFIQEN_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMFIQEN_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_VMACKCTL_MASK                      (0x00000004U)
#define CSL_ARMGIC_GICH_VMCR_VMACKCTL_SHIFT                     (2U)
#define CSL_ARMGIC_GICH_VMCR_VMACKCTL_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMACKCTL_MAX                       (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_VMNSEN_MASK                        (0x00000002U)
#define CSL_ARMGIC_GICH_VMCR_VMNSEN_SHIFT                       (1U)
#define CSL_ARMGIC_GICH_VMCR_VMNSEN_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMNSEN_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_VMSEN_MASK                         (0x00000001U)
#define CSL_ARMGIC_GICH_VMCR_VMSEN_SHIFT                        (0U)
#define CSL_ARMGIC_GICH_VMCR_VMSEN_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_VMCR_VMSEN_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_VMCR_RESETVAL                           (0x004c0000U)

/* GICH_MISR */

#define CSL_ARMGIC_GICH_MISR_VDNSI_MASK                         (0x00000080U)
#define CSL_ARMGIC_GICH_MISR_VDNSI_SHIFT                        (7U)
#define CSL_ARMGIC_GICH_MISR_VDNSI_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_VDNSI_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_VENSI_MASK                         (0x00000040U)
#define CSL_ARMGIC_GICH_MISR_VENSI_SHIFT                        (6U)
#define CSL_ARMGIC_GICH_MISR_VENSI_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_VENSI_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_VDSI_MASK                          (0x00000020U)
#define CSL_ARMGIC_GICH_MISR_VDSI_SHIFT                         (5U)
#define CSL_ARMGIC_GICH_MISR_VDSI_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_VDSI_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_VESI_MASK                          (0x00000010U)
#define CSL_ARMGIC_GICH_MISR_VESI_SHIFT                         (4U)
#define CSL_ARMGIC_GICH_MISR_VESI_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_VESI_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_NPI_MASK                           (0x00000008U)
#define CSL_ARMGIC_GICH_MISR_NPI_SHIFT                          (3U)
#define CSL_ARMGIC_GICH_MISR_NPI_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_NPI_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_SKIDI_MASK                         (0x00000004U)
#define CSL_ARMGIC_GICH_MISR_SKIDI_SHIFT                        (2U)
#define CSL_ARMGIC_GICH_MISR_SKIDI_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_SKIDI_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_UI_MASK                            (0x00000002U)
#define CSL_ARMGIC_GICH_MISR_UI_SHIFT                           (1U)
#define CSL_ARMGIC_GICH_MISR_UI_RESETVAL                        (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_UI_MAX                             (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_EI_MASK                            (0x00000001U)
#define CSL_ARMGIC_GICH_MISR_EI_SHIFT                           (0U)
#define CSL_ARMGIC_GICH_MISR_EI_RESETVAL                        (0x00000000U)
#define CSL_ARMGIC_GICH_MISR_EI_MAX                             (0x00000001U)

#define CSL_ARMGIC_GICH_MISR_RESETVAL                           (0x00000000U)

/* GICH_EISR0 */

#define CSL_ARMGIC_GICH_EISR0_LR3_MASK                          (0x00000008U)
#define CSL_ARMGIC_GICH_EISR0_LR3_SHIFT                         (3U)
#define CSL_ARMGIC_GICH_EISR0_LR3_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_EISR0_LR3_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_EISR0_LR2_MASK                          (0x00000004U)
#define CSL_ARMGIC_GICH_EISR0_LR2_SHIFT                         (2U)
#define CSL_ARMGIC_GICH_EISR0_LR2_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_EISR0_LR2_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_EISR0_LR1_MASK                          (0x00000002U)
#define CSL_ARMGIC_GICH_EISR0_LR1_SHIFT                         (1U)
#define CSL_ARMGIC_GICH_EISR0_LR1_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_EISR0_LR1_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_EISR0_LR0_MASK                          (0x00000001U)
#define CSL_ARMGIC_GICH_EISR0_LR0_SHIFT                         (0U)
#define CSL_ARMGIC_GICH_EISR0_LR0_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_EISR0_LR0_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_EISR0_RESETVAL                          (0x00000000U)

/* GICH_ELSR0 */

#define CSL_ARMGIC_GICH_ELSR0_LR3_MASK                          (0x00000008U)
#define CSL_ARMGIC_GICH_ELSR0_LR3_SHIFT                         (3U)
#define CSL_ARMGIC_GICH_ELSR0_LR3_RESETVAL                      (0x00000001U)
#define CSL_ARMGIC_GICH_ELSR0_LR3_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_ELSR0_LR2_MASK                          (0x00000004U)
#define CSL_ARMGIC_GICH_ELSR0_LR2_SHIFT                         (2U)
#define CSL_ARMGIC_GICH_ELSR0_LR2_RESETVAL                      (0x00000001U)
#define CSL_ARMGIC_GICH_ELSR0_LR2_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_ELSR0_LR1_MASK                          (0x00000002U)
#define CSL_ARMGIC_GICH_ELSR0_LR1_SHIFT                         (1U)
#define CSL_ARMGIC_GICH_ELSR0_LR1_RESETVAL                      (0x00000001U)
#define CSL_ARMGIC_GICH_ELSR0_LR1_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_ELSR0_LR0_MASK                          (0x00000001U)
#define CSL_ARMGIC_GICH_ELSR0_LR0_SHIFT                         (0U)
#define CSL_ARMGIC_GICH_ELSR0_LR0_RESETVAL                      (0x00000001U)
#define CSL_ARMGIC_GICH_ELSR0_LR0_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_ELSR0_RESETVAL                          (0x0000000fU)

/* GICH_APR0 */

#define CSL_ARMGIC_GICH_APR0_AP31_MASK                          (0x80000000U)
#define CSL_ARMGIC_GICH_APR0_AP31_SHIFT                         (31U)
#define CSL_ARMGIC_GICH_APR0_AP31_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP31_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP30_MASK                          (0x40000000U)
#define CSL_ARMGIC_GICH_APR0_AP30_SHIFT                         (30U)
#define CSL_ARMGIC_GICH_APR0_AP30_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP30_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP29_MASK                          (0x20000000U)
#define CSL_ARMGIC_GICH_APR0_AP29_SHIFT                         (29U)
#define CSL_ARMGIC_GICH_APR0_AP29_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP29_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP28_MASK                          (0x10000000U)
#define CSL_ARMGIC_GICH_APR0_AP28_SHIFT                         (28U)
#define CSL_ARMGIC_GICH_APR0_AP28_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP28_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP27_MASK                          (0x08000000U)
#define CSL_ARMGIC_GICH_APR0_AP27_SHIFT                         (27U)
#define CSL_ARMGIC_GICH_APR0_AP27_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP27_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP26_MASK                          (0x04000000U)
#define CSL_ARMGIC_GICH_APR0_AP26_SHIFT                         (26U)
#define CSL_ARMGIC_GICH_APR0_AP26_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP26_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP25_MASK                          (0x02000000U)
#define CSL_ARMGIC_GICH_APR0_AP25_SHIFT                         (25U)
#define CSL_ARMGIC_GICH_APR0_AP25_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP25_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP24_MASK                          (0x01000000U)
#define CSL_ARMGIC_GICH_APR0_AP24_SHIFT                         (24U)
#define CSL_ARMGIC_GICH_APR0_AP24_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP24_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP23_MASK                          (0x00800000U)
#define CSL_ARMGIC_GICH_APR0_AP23_SHIFT                         (23U)
#define CSL_ARMGIC_GICH_APR0_AP23_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP23_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP22_MASK                          (0x00400000U)
#define CSL_ARMGIC_GICH_APR0_AP22_SHIFT                         (22U)
#define CSL_ARMGIC_GICH_APR0_AP22_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP22_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP21_MASK                          (0x00200000U)
#define CSL_ARMGIC_GICH_APR0_AP21_SHIFT                         (21U)
#define CSL_ARMGIC_GICH_APR0_AP21_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP21_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP20_MASK                          (0x00100000U)
#define CSL_ARMGIC_GICH_APR0_AP20_SHIFT                         (20U)
#define CSL_ARMGIC_GICH_APR0_AP20_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP20_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP19_MASK                          (0x00080000U)
#define CSL_ARMGIC_GICH_APR0_AP19_SHIFT                         (19U)
#define CSL_ARMGIC_GICH_APR0_AP19_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP19_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP18_MASK                          (0x00040000U)
#define CSL_ARMGIC_GICH_APR0_AP18_SHIFT                         (18U)
#define CSL_ARMGIC_GICH_APR0_AP18_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP18_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP17_MASK                          (0x00020000U)
#define CSL_ARMGIC_GICH_APR0_AP17_SHIFT                         (17U)
#define CSL_ARMGIC_GICH_APR0_AP17_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP17_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP16_MASK                          (0x00010000U)
#define CSL_ARMGIC_GICH_APR0_AP16_SHIFT                         (16U)
#define CSL_ARMGIC_GICH_APR0_AP16_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP16_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP15_MASK                          (0x00008000U)
#define CSL_ARMGIC_GICH_APR0_AP15_SHIFT                         (15U)
#define CSL_ARMGIC_GICH_APR0_AP15_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP15_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP14_MASK                          (0x00004000U)
#define CSL_ARMGIC_GICH_APR0_AP14_SHIFT                         (14U)
#define CSL_ARMGIC_GICH_APR0_AP14_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP14_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP13_MASK                          (0x00002000U)
#define CSL_ARMGIC_GICH_APR0_AP13_SHIFT                         (13U)
#define CSL_ARMGIC_GICH_APR0_AP13_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP13_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP12_MASK                          (0x00001000U)
#define CSL_ARMGIC_GICH_APR0_AP12_SHIFT                         (12U)
#define CSL_ARMGIC_GICH_APR0_AP12_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP12_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP11_MASK                          (0x00000800U)
#define CSL_ARMGIC_GICH_APR0_AP11_SHIFT                         (11U)
#define CSL_ARMGIC_GICH_APR0_AP11_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP11_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP10_MASK                          (0x00000400U)
#define CSL_ARMGIC_GICH_APR0_AP10_SHIFT                         (10U)
#define CSL_ARMGIC_GICH_APR0_AP10_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP10_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP9_MASK                           (0x00000200U)
#define CSL_ARMGIC_GICH_APR0_AP9_SHIFT                          (9U)
#define CSL_ARMGIC_GICH_APR0_AP9_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP9_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP8_MASK                           (0x00000100U)
#define CSL_ARMGIC_GICH_APR0_AP8_SHIFT                          (8U)
#define CSL_ARMGIC_GICH_APR0_AP8_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP8_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP7_MASK                           (0x00000080U)
#define CSL_ARMGIC_GICH_APR0_AP7_SHIFT                          (7U)
#define CSL_ARMGIC_GICH_APR0_AP7_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP7_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP6_MASK                           (0x00000040U)
#define CSL_ARMGIC_GICH_APR0_AP6_SHIFT                          (6U)
#define CSL_ARMGIC_GICH_APR0_AP6_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP6_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP5_MASK                           (0x00000020U)
#define CSL_ARMGIC_GICH_APR0_AP5_SHIFT                          (5U)
#define CSL_ARMGIC_GICH_APR0_AP5_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP5_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP4_MASK                           (0x00000010U)
#define CSL_ARMGIC_GICH_APR0_AP4_SHIFT                          (4U)
#define CSL_ARMGIC_GICH_APR0_AP4_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP4_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP3_MASK                           (0x00000008U)
#define CSL_ARMGIC_GICH_APR0_AP3_SHIFT                          (3U)
#define CSL_ARMGIC_GICH_APR0_AP3_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP3_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP2_MASK                           (0x00000004U)
#define CSL_ARMGIC_GICH_APR0_AP2_SHIFT                          (2U)
#define CSL_ARMGIC_GICH_APR0_AP2_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP2_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP1_MASK                           (0x00000002U)
#define CSL_ARMGIC_GICH_APR0_AP1_SHIFT                          (1U)
#define CSL_ARMGIC_GICH_APR0_AP1_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP1_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_AP0_MASK                           (0x00000001U)
#define CSL_ARMGIC_GICH_APR0_AP0_SHIFT                          (0U)
#define CSL_ARMGIC_GICH_APR0_AP0_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICH_APR0_AP0_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICH_APR0_RESETVAL                           (0x00000000U)

/* GICH_LR0 */

#define CSL_ARMGIC_GICH_LR0_HW_MASK                             (0x80000000U)
#define CSL_ARMGIC_GICH_LR0_HW_SHIFT                            (31U)
#define CSL_ARMGIC_GICH_LR0_HW_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_HW_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR0_NS_MASK                             (0x40000000U)
#define CSL_ARMGIC_GICH_LR0_NS_SHIFT                            (30U)
#define CSL_ARMGIC_GICH_LR0_NS_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_NS_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR0_STATE_MASK                          (0x30000000U)
#define CSL_ARMGIC_GICH_LR0_STATE_SHIFT                         (28U)
#define CSL_ARMGIC_GICH_LR0_STATE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_STATE_MAX                           (0x00000003U)

#define CSL_ARMGIC_GICH_LR0_PRIORITY_MASK                       (0x0F800000U)
#define CSL_ARMGIC_GICH_LR0_PRIORITY_SHIFT                      (23U)
#define CSL_ARMGIC_GICH_LR0_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_PRIORITY_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICH_LR0_PHYSICALID_MASK                     (0x000FFC00U)
#define CSL_ARMGIC_GICH_LR0_PHYSICALID_SHIFT                    (10U)
#define CSL_ARMGIC_GICH_LR0_PHYSICALID_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_PHYSICALID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICH_LR0_VIRTUALID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICH_LR0_VIRTUALID_SHIFT                     (0U)
#define CSL_ARMGIC_GICH_LR0_VIRTUALID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICH_LR0_VIRTUALID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICH_LR0_RESETVAL                            (0x00000000U)

/* GICH_LR1 */

#define CSL_ARMGIC_GICH_LR1_HW_MASK                             (0x80000000U)
#define CSL_ARMGIC_GICH_LR1_HW_SHIFT                            (31U)
#define CSL_ARMGIC_GICH_LR1_HW_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_HW_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR1_NS_MASK                             (0x40000000U)
#define CSL_ARMGIC_GICH_LR1_NS_SHIFT                            (30U)
#define CSL_ARMGIC_GICH_LR1_NS_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_NS_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR1_STATE_MASK                          (0x30000000U)
#define CSL_ARMGIC_GICH_LR1_STATE_SHIFT                         (28U)
#define CSL_ARMGIC_GICH_LR1_STATE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_STATE_MAX                           (0x00000003U)

#define CSL_ARMGIC_GICH_LR1_PRIORITY_MASK                       (0x0F800000U)
#define CSL_ARMGIC_GICH_LR1_PRIORITY_SHIFT                      (23U)
#define CSL_ARMGIC_GICH_LR1_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_PRIORITY_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICH_LR1_PHYSICALID_MASK                     (0x000FFC00U)
#define CSL_ARMGIC_GICH_LR1_PHYSICALID_SHIFT                    (10U)
#define CSL_ARMGIC_GICH_LR1_PHYSICALID_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_PHYSICALID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICH_LR1_VIRTUALID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICH_LR1_VIRTUALID_SHIFT                     (0U)
#define CSL_ARMGIC_GICH_LR1_VIRTUALID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICH_LR1_VIRTUALID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICH_LR1_RESETVAL                            (0x00000000U)

/* GICH_LR2 */

#define CSL_ARMGIC_GICH_LR2_HW_MASK                             (0x80000000U)
#define CSL_ARMGIC_GICH_LR2_HW_SHIFT                            (31U)
#define CSL_ARMGIC_GICH_LR2_HW_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_HW_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR2_NS_MASK                             (0x40000000U)
#define CSL_ARMGIC_GICH_LR2_NS_SHIFT                            (30U)
#define CSL_ARMGIC_GICH_LR2_NS_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_NS_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR2_STATE_MASK                          (0x30000000U)
#define CSL_ARMGIC_GICH_LR2_STATE_SHIFT                         (28U)
#define CSL_ARMGIC_GICH_LR2_STATE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_STATE_MAX                           (0x00000003U)

#define CSL_ARMGIC_GICH_LR2_PRIORITY_MASK                       (0x0F800000U)
#define CSL_ARMGIC_GICH_LR2_PRIORITY_SHIFT                      (23U)
#define CSL_ARMGIC_GICH_LR2_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_PRIORITY_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICH_LR2_PHYSICALID_MASK                     (0x000FFC00U)
#define CSL_ARMGIC_GICH_LR2_PHYSICALID_SHIFT                    (10U)
#define CSL_ARMGIC_GICH_LR2_PHYSICALID_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_PHYSICALID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICH_LR2_VIRTUALID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICH_LR2_VIRTUALID_SHIFT                     (0U)
#define CSL_ARMGIC_GICH_LR2_VIRTUALID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICH_LR2_VIRTUALID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICH_LR2_RESETVAL                            (0x00000000U)

/* GICH_LR3 */

#define CSL_ARMGIC_GICH_LR3_HW_MASK                             (0x80000000U)
#define CSL_ARMGIC_GICH_LR3_HW_SHIFT                            (31U)
#define CSL_ARMGIC_GICH_LR3_HW_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_HW_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR3_NS_MASK                             (0x40000000U)
#define CSL_ARMGIC_GICH_LR3_NS_SHIFT                            (30U)
#define CSL_ARMGIC_GICH_LR3_NS_RESETVAL                         (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_NS_MAX                              (0x00000001U)

#define CSL_ARMGIC_GICH_LR3_STATE_MASK                          (0x30000000U)
#define CSL_ARMGIC_GICH_LR3_STATE_SHIFT                         (28U)
#define CSL_ARMGIC_GICH_LR3_STATE_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_STATE_MAX                           (0x00000003U)

#define CSL_ARMGIC_GICH_LR3_PRIORITY_MASK                       (0x0F800000U)
#define CSL_ARMGIC_GICH_LR3_PRIORITY_SHIFT                      (23U)
#define CSL_ARMGIC_GICH_LR3_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_PRIORITY_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICH_LR3_PHYSICALID_MASK                     (0x000FFC00U)
#define CSL_ARMGIC_GICH_LR3_PHYSICALID_SHIFT                    (10U)
#define CSL_ARMGIC_GICH_LR3_PHYSICALID_RESETVAL                 (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_PHYSICALID_MAX                      (0x000003ffU)

#define CSL_ARMGIC_GICH_LR3_VIRTUALID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICH_LR3_VIRTUALID_SHIFT                     (0U)
#define CSL_ARMGIC_GICH_LR3_VIRTUALID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICH_LR3_VIRTUALID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICH_LR3_RESETVAL                            (0x00000000U)

/* GICV_CTLR */

#define CSL_ARMGIC_GICV_CTLR_EOIMODE_MASK                       (0x00000200U)
#define CSL_ARMGIC_GICV_CTLR_EOIMODE_SHIFT                      (9U)
#define CSL_ARMGIC_GICV_CTLR_EOIMODE_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_EOIMODE_MAX                        (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_CBPR_MASK                          (0x00000010U)
#define CSL_ARMGIC_GICV_CTLR_CBPR_SHIFT                         (4U)
#define CSL_ARMGIC_GICV_CTLR_CBPR_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_CBPR_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_FIQEN_MASK                         (0x00000008U)
#define CSL_ARMGIC_GICV_CTLR_FIQEN_SHIFT                        (3U)
#define CSL_ARMGIC_GICV_CTLR_FIQEN_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_FIQEN_MAX                          (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_ACKCTL_MASK                        (0x00000004U)
#define CSL_ARMGIC_GICV_CTLR_ACKCTL_SHIFT                       (2U)
#define CSL_ARMGIC_GICV_CTLR_ACKCTL_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_ACKCTL_MAX                         (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP1_MASK                    (0x00000002U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP1_SHIFT                   (1U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP1_RESETVAL                (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP1_MAX                     (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP0_MASK                    (0x00000001U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP0_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP0_RESETVAL                (0x00000000U)
#define CSL_ARMGIC_GICV_CTLR_ENABLEGRP0_MAX                     (0x00000001U)

#define CSL_ARMGIC_GICV_CTLR_RESETVAL                           (0x00000000U)

/* GICV_PMR */

#define CSL_ARMGIC_GICV_PMR_PRIORITY_MASK                       (0x000000F8U)
#define CSL_ARMGIC_GICV_PMR_PRIORITY_SHIFT                      (3U)
#define CSL_ARMGIC_GICV_PMR_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICV_PMR_PRIORITY_MAX                        (0x0000001fU)

#define CSL_ARMGIC_GICV_PMR_RESETVAL                            (0x00000000U)

/* GICV_BPR */

#define CSL_ARMGIC_GICV_BPR_BINARYPOINT_MASK                    (0x00000007U)
#define CSL_ARMGIC_GICV_BPR_BINARYPOINT_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_BPR_BINARYPOINT_RESETVAL                (0x00000002U)
#define CSL_ARMGIC_GICV_BPR_BINARYPOINT_MAX                     (0x00000007U)

#define CSL_ARMGIC_GICV_BPR_RESETVAL                            (0x00000002U)

/* GICV_IAR */

#define CSL_ARMGIC_GICV_IAR_CPUID_MASK                          (0x00001C00U)
#define CSL_ARMGIC_GICV_IAR_CPUID_SHIFT                         (10U)
#define CSL_ARMGIC_GICV_IAR_CPUID_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_IAR_CPUID_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICV_IAR_INTERRUPTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICV_IAR_INTERRUPTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_IAR_INTERRUPTID_RESETVAL                (0x000003ffU)
#define CSL_ARMGIC_GICV_IAR_INTERRUPTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICV_IAR_RESETVAL                            (0x000003ffU)

/* GICV_EOIR */

#define CSL_ARMGIC_GICV_EOIR_CPUID_MASK                         (0x00001C00U)
#define CSL_ARMGIC_GICV_EOIR_CPUID_SHIFT                        (10U)
#define CSL_ARMGIC_GICV_EOIR_CPUID_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICV_EOIR_CPUID_MAX                          (0x00000007U)

#define CSL_ARMGIC_GICV_EOIR_EOIINTID_MASK                      (0x000003FFU)
#define CSL_ARMGIC_GICV_EOIR_EOIINTID_SHIFT                     (0U)
#define CSL_ARMGIC_GICV_EOIR_EOIINTID_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICV_EOIR_EOIINTID_MAX                       (0x000003ffU)

#define CSL_ARMGIC_GICV_EOIR_RESETVAL                           (0x00000000U)

/* GICV_RPR */

#define CSL_ARMGIC_GICV_RPR_CPUID_MASK                          (0x00001C00U)
#define CSL_ARMGIC_GICV_RPR_CPUID_SHIFT                         (10U)
#define CSL_ARMGIC_GICV_RPR_CPUID_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_RPR_CPUID_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICV_RPR_INTERRUPTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICV_RPR_INTERRUPTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_RPR_INTERRUPTID_RESETVAL                (0x000000ffU)
#define CSL_ARMGIC_GICV_RPR_INTERRUPTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICV_RPR_RESETVAL                            (0x000000ffU)

/* GICV_HPPIR */

#define CSL_ARMGIC_GICV_HPPIR_CPUID_MASK                        (0x00001C00U)
#define CSL_ARMGIC_GICV_HPPIR_CPUID_SHIFT                       (10U)
#define CSL_ARMGIC_GICV_HPPIR_CPUID_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICV_HPPIR_CPUID_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICV_HPPIR_PENDINTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICV_HPPIR_PENDINTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_HPPIR_PENDINTID_RESETVAL                (0x000003ffU)
#define CSL_ARMGIC_GICV_HPPIR_PENDINTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICV_HPPIR_RESETVAL                          (0x000003ffU)

/* GICV_ABPR */

#define CSL_ARMGIC_GICV_ABPR_BINARYPOINT_MASK                   (0x00000007U)
#define CSL_ARMGIC_GICV_ABPR_BINARYPOINT_SHIFT                  (0U)
#define CSL_ARMGIC_GICV_ABPR_BINARYPOINT_RESETVAL               (0x00000003U)
#define CSL_ARMGIC_GICV_ABPR_BINARYPOINT_MAX                    (0x00000007U)

#define CSL_ARMGIC_GICV_ABPR_RESETVAL                           (0x00000003U)

/* GICV_AIAR */

#define CSL_ARMGIC_GICV_AIAR_CPUID_MASK                         (0x00001C00U)
#define CSL_ARMGIC_GICV_AIAR_CPUID_SHIFT                        (10U)
#define CSL_ARMGIC_GICV_AIAR_CPUID_RESETVAL                     (0x00000000U)
#define CSL_ARMGIC_GICV_AIAR_CPUID_MAX                          (0x00000007U)

#define CSL_ARMGIC_GICV_AIAR_INTERRUPTID_MASK                   (0x000003FFU)
#define CSL_ARMGIC_GICV_AIAR_INTERRUPTID_SHIFT                  (0U)
#define CSL_ARMGIC_GICV_AIAR_INTERRUPTID_RESETVAL               (0x000003ffU)
#define CSL_ARMGIC_GICV_AIAR_INTERRUPTID_MAX                    (0x000003ffU)

#define CSL_ARMGIC_GICV_AIAR_RESETVAL                           (0x000003ffU)

/* GICV_AEOIR */

#define CSL_ARMGIC_GICV_AEOIR_CPUID_MASK                        (0x00001C00U)
#define CSL_ARMGIC_GICV_AEOIR_CPUID_SHIFT                       (10U)
#define CSL_ARMGIC_GICV_AEOIR_CPUID_RESETVAL                    (0x00000000U)
#define CSL_ARMGIC_GICV_AEOIR_CPUID_MAX                         (0x00000007U)

#define CSL_ARMGIC_GICV_AEOIR_INTERRUPTID_MASK                  (0x000003FFU)
#define CSL_ARMGIC_GICV_AEOIR_INTERRUPTID_SHIFT                 (0U)
#define CSL_ARMGIC_GICV_AEOIR_INTERRUPTID_RESETVAL              (0x00000000U)
#define CSL_ARMGIC_GICV_AEOIR_INTERRUPTID_MAX                   (0x000003ffU)

#define CSL_ARMGIC_GICV_AEOIR_RESETVAL                          (0x00000000U)

/* GICV_AHPPIR */

#define CSL_ARMGIC_GICV_AHPPIR_CPUID_MASK                       (0x00001C00U)
#define CSL_ARMGIC_GICV_AHPPIR_CPUID_SHIFT                      (10U)
#define CSL_ARMGIC_GICV_AHPPIR_CPUID_RESETVAL                   (0x00000000U)
#define CSL_ARMGIC_GICV_AHPPIR_CPUID_MAX                        (0x00000007U)

#define CSL_ARMGIC_GICV_AHPPIR_PENDINTID_MASK                   (0x000003FFU)
#define CSL_ARMGIC_GICV_AHPPIR_PENDINTID_SHIFT                  (0U)
#define CSL_ARMGIC_GICV_AHPPIR_PENDINTID_RESETVAL               (0x000003ffU)
#define CSL_ARMGIC_GICV_AHPPIR_PENDINTID_MAX                    (0x000003ffU)

#define CSL_ARMGIC_GICV_AHPPIR_RESETVAL                         (0x000003ffU)

/* GICV_APR0 */

#define CSL_ARMGIC_GICV_APR0_AP31_MASK                          (0x80000000U)
#define CSL_ARMGIC_GICV_APR0_AP31_SHIFT                         (31U)
#define CSL_ARMGIC_GICV_APR0_AP31_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP31_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP30_MASK                          (0x40000000U)
#define CSL_ARMGIC_GICV_APR0_AP30_SHIFT                         (30U)
#define CSL_ARMGIC_GICV_APR0_AP30_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP30_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP29_MASK                          (0x20000000U)
#define CSL_ARMGIC_GICV_APR0_AP29_SHIFT                         (29U)
#define CSL_ARMGIC_GICV_APR0_AP29_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP29_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP28_MASK                          (0x10000000U)
#define CSL_ARMGIC_GICV_APR0_AP28_SHIFT                         (28U)
#define CSL_ARMGIC_GICV_APR0_AP28_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP28_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP27_MASK                          (0x08000000U)
#define CSL_ARMGIC_GICV_APR0_AP27_SHIFT                         (27U)
#define CSL_ARMGIC_GICV_APR0_AP27_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP27_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP26_MASK                          (0x04000000U)
#define CSL_ARMGIC_GICV_APR0_AP26_SHIFT                         (26U)
#define CSL_ARMGIC_GICV_APR0_AP26_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP26_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP25_MASK                          (0x02000000U)
#define CSL_ARMGIC_GICV_APR0_AP25_SHIFT                         (25U)
#define CSL_ARMGIC_GICV_APR0_AP25_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP25_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP24_MASK                          (0x01000000U)
#define CSL_ARMGIC_GICV_APR0_AP24_SHIFT                         (24U)
#define CSL_ARMGIC_GICV_APR0_AP24_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP24_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP23_MASK                          (0x00800000U)
#define CSL_ARMGIC_GICV_APR0_AP23_SHIFT                         (23U)
#define CSL_ARMGIC_GICV_APR0_AP23_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP23_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP22_MASK                          (0x00400000U)
#define CSL_ARMGIC_GICV_APR0_AP22_SHIFT                         (22U)
#define CSL_ARMGIC_GICV_APR0_AP22_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP22_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP21_MASK                          (0x00200000U)
#define CSL_ARMGIC_GICV_APR0_AP21_SHIFT                         (21U)
#define CSL_ARMGIC_GICV_APR0_AP21_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP21_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP20_MASK                          (0x00100000U)
#define CSL_ARMGIC_GICV_APR0_AP20_SHIFT                         (20U)
#define CSL_ARMGIC_GICV_APR0_AP20_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP20_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP19_MASK                          (0x00080000U)
#define CSL_ARMGIC_GICV_APR0_AP19_SHIFT                         (19U)
#define CSL_ARMGIC_GICV_APR0_AP19_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP19_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP18_MASK                          (0x00040000U)
#define CSL_ARMGIC_GICV_APR0_AP18_SHIFT                         (18U)
#define CSL_ARMGIC_GICV_APR0_AP18_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP18_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP17_MASK                          (0x00020000U)
#define CSL_ARMGIC_GICV_APR0_AP17_SHIFT                         (17U)
#define CSL_ARMGIC_GICV_APR0_AP17_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP17_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP16_MASK                          (0x00010000U)
#define CSL_ARMGIC_GICV_APR0_AP16_SHIFT                         (16U)
#define CSL_ARMGIC_GICV_APR0_AP16_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP16_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP15_MASK                          (0x00008000U)
#define CSL_ARMGIC_GICV_APR0_AP15_SHIFT                         (15U)
#define CSL_ARMGIC_GICV_APR0_AP15_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP15_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP14_MASK                          (0x00004000U)
#define CSL_ARMGIC_GICV_APR0_AP14_SHIFT                         (14U)
#define CSL_ARMGIC_GICV_APR0_AP14_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP14_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP13_MASK                          (0x00002000U)
#define CSL_ARMGIC_GICV_APR0_AP13_SHIFT                         (13U)
#define CSL_ARMGIC_GICV_APR0_AP13_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP13_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP12_MASK                          (0x00001000U)
#define CSL_ARMGIC_GICV_APR0_AP12_SHIFT                         (12U)
#define CSL_ARMGIC_GICV_APR0_AP12_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP12_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP11_MASK                          (0x00000800U)
#define CSL_ARMGIC_GICV_APR0_AP11_SHIFT                         (11U)
#define CSL_ARMGIC_GICV_APR0_AP11_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP11_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP10_MASK                          (0x00000400U)
#define CSL_ARMGIC_GICV_APR0_AP10_SHIFT                         (10U)
#define CSL_ARMGIC_GICV_APR0_AP10_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP10_MAX                           (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP9_MASK                           (0x00000200U)
#define CSL_ARMGIC_GICV_APR0_AP9_SHIFT                          (9U)
#define CSL_ARMGIC_GICV_APR0_AP9_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP9_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP8_MASK                           (0x00000100U)
#define CSL_ARMGIC_GICV_APR0_AP8_SHIFT                          (8U)
#define CSL_ARMGIC_GICV_APR0_AP8_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP8_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP7_MASK                           (0x00000080U)
#define CSL_ARMGIC_GICV_APR0_AP7_SHIFT                          (7U)
#define CSL_ARMGIC_GICV_APR0_AP7_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP7_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP6_MASK                           (0x00000040U)
#define CSL_ARMGIC_GICV_APR0_AP6_SHIFT                          (6U)
#define CSL_ARMGIC_GICV_APR0_AP6_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP6_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP5_MASK                           (0x00000020U)
#define CSL_ARMGIC_GICV_APR0_AP5_SHIFT                          (5U)
#define CSL_ARMGIC_GICV_APR0_AP5_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP5_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP4_MASK                           (0x00000010U)
#define CSL_ARMGIC_GICV_APR0_AP4_SHIFT                          (4U)
#define CSL_ARMGIC_GICV_APR0_AP4_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP4_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP3_MASK                           (0x00000008U)
#define CSL_ARMGIC_GICV_APR0_AP3_SHIFT                          (3U)
#define CSL_ARMGIC_GICV_APR0_AP3_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP3_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP2_MASK                           (0x00000004U)
#define CSL_ARMGIC_GICV_APR0_AP2_SHIFT                          (2U)
#define CSL_ARMGIC_GICV_APR0_AP2_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP2_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP1_MASK                           (0x00000002U)
#define CSL_ARMGIC_GICV_APR0_AP1_SHIFT                          (1U)
#define CSL_ARMGIC_GICV_APR0_AP1_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP1_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_AP0_MASK                           (0x00000001U)
#define CSL_ARMGIC_GICV_APR0_AP0_SHIFT                          (0U)
#define CSL_ARMGIC_GICV_APR0_AP0_RESETVAL                       (0x00000000U)
#define CSL_ARMGIC_GICV_APR0_AP0_MAX                            (0x00000001U)

#define CSL_ARMGIC_GICV_APR0_RESETVAL                           (0x00000000U)

/* GICV_IIDR */

#define CSL_ARMGIC_GICV_IIDR_PRODUCTID_MASK                     (0xFFF00000U)
#define CSL_ARMGIC_GICV_IIDR_PRODUCTID_SHIFT                    (20U)
#define CSL_ARMGIC_GICV_IIDR_PRODUCTID_RESETVAL                 (0x00000020U)
#define CSL_ARMGIC_GICV_IIDR_PRODUCTID_MAX                      (0x00000fffU)

#define CSL_ARMGIC_GICV_IIDR_ARCHITECTUREVERSION_MASK           (0x000F0000U)
#define CSL_ARMGIC_GICV_IIDR_ARCHITECTUREVERSION_SHIFT          (16U)
#define CSL_ARMGIC_GICV_IIDR_ARCHITECTUREVERSION_RESETVAL       (0x00000002U)
#define CSL_ARMGIC_GICV_IIDR_ARCHITECTUREVERSION_MAX            (0x0000000fU)

#define CSL_ARMGIC_GICV_IIDR_REVISION_MASK                      (0x0000F000U)
#define CSL_ARMGIC_GICV_IIDR_REVISION_SHIFT                     (12U)
#define CSL_ARMGIC_GICV_IIDR_REVISION_RESETVAL                  (0x00000000U)
#define CSL_ARMGIC_GICV_IIDR_REVISION_MAX                       (0x0000000fU)

#define CSL_ARMGIC_GICV_IIDR_IMPLEMENTER_MASK                   (0x00000FFFU)
#define CSL_ARMGIC_GICV_IIDR_IMPLEMENTER_SHIFT                  (0U)
#define CSL_ARMGIC_GICV_IIDR_IMPLEMENTER_RESETVAL               (0x0000043bU)
#define CSL_ARMGIC_GICV_IIDR_IMPLEMENTER_MAX                    (0x00000fffU)

#define CSL_ARMGIC_GICV_IIDR_RESETVAL                           (0x0202043bU)

/* GICV_DIR */

#define CSL_ARMGIC_GICV_DIR_CPUID_MASK                          (0x00001C00U)
#define CSL_ARMGIC_GICV_DIR_CPUID_SHIFT                         (10U)
#define CSL_ARMGIC_GICV_DIR_CPUID_RESETVAL                      (0x00000000U)
#define CSL_ARMGIC_GICV_DIR_CPUID_MAX                           (0x00000007U)

#define CSL_ARMGIC_GICV_DIR_INTERRUPTID_MASK                    (0x000003FFU)
#define CSL_ARMGIC_GICV_DIR_INTERRUPTID_SHIFT                   (0U)
#define CSL_ARMGIC_GICV_DIR_INTERRUPTID_RESETVAL                (0x00000000U)
#define CSL_ARMGIC_GICV_DIR_INTERRUPTID_MAX                     (0x000003ffU)

#define CSL_ARMGIC_GICV_DIR_RESETVAL                            (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
