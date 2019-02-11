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
#ifndef HW_XMC_H_
#define HW_XMC_H_

#ifdef __cplusplus
extern "C"
{
#endif


/**************************************************************************
* Register Macros
**************************************************************************/
#define XMPFAR                                          (0x200U)
#define XMPFSR                                          (0x204U)
#define XMPFCR                                          (0x208U)
#define MDMAARBX                                        (0x280U)
#define XPFCMD                                          (0x300U)
#define XPFACS                                          (0x304U)
#define XPFAC0                                          (0x310U)
#define XPFAC1                                          (0x314U)
#define XPFAC2                                          (0x318U)
#define XPFAC3                                          (0x31CU)
#define XPFADDR(i)                                      (0x400U + ((i) * (0x4U)))
#define XEDIAX                                          (0xFFFCU)
#define XMPAXL(n)                                       ((uint32_t)0x0U + ((n) * (uint32_t)(0x8U)))
#define XMPAXH(n)                                       ((uint32_t)0x4U + ((n) * (uint32_t)(0x8U)))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* XMPFAR */
#define XMPFAR_FADDR_MASK                             (0xFFFFFFFFU)
#define XMPFAR_FADDR_SHIFT                            (0U)

/* XMPFSR */
#define XMPFSR_ACCTYPE_MASK                           (0x0000003FU)
#define XMPFSR_ACCTYPE_SHIFT                          (0U)
#define XMPFSR_RESVD1_MASK                            (0x00000040U)
#define XMPFSR_RESVD1_SHIFT                           (6U)
#define XMPFSR_NS_MASK                                (0x00000080U)
#define XMPFSR_NS_SHIFT                               (7U)
#define XMPFSR_LOCAL_MASK                             (0x00000100U)
#define XMPFSR_LOCAL_SHIFT                            (8U)
#define XMPFSR_RESVD2_MASK                            (0xFFFFFE00U)
#define XMPFSR_RESVD2_SHIFT                           (9U)

/* XMPFCR */
#define XMPFCR_MPFCLR_MASK                            (0x00000001U)
#define XMPFCR_MPFCLR_SHIFT                           (0U)
#define XMPFCR_RESVD_MASK                             (0xFFFFFFFEU)
#define XMPFCR_RESVD_SHIFT                            (1U)

/* MDMAARBX */
#define MDMAARBX_RESVD1_MASK                          (0x0000FFFFU)
#define MDMAARBX_RESVD1_SHIFT                         (0U)
#define MDMAARBX_PRI_MASK                             (0x00070000U)
#define MDMAARBX_PRI_SHIFT                            (16U)
#define MDMAARBX_RESVD2_MASK                          (0xFFF80000U)
#define MDMAARBX_RESVD2_SHIFT                         (19U)

/* XPFCMD */
#define XPFCMD_INV_MASK                               (0x00000001U)
#define XPFCMD_INV_SHIFT                              (0U)
#define XPFCMD_ACENL_MASK                             (0x00000002U)
#define XPFCMD_ACENL_SHIFT                            (1U)
#define XPFCMD_ACEN_MASK                              (0x0000000CU)
#define XPFCMD_ACEN_SHIFT                             (2U)
#define XPFCMD_ACRST_MASK                             (0x00000010U)
#define XPFCMD_ACRST_SHIFT                            (4U)
#define XPFCMD_RESVD_MASK                             (0x7FFFFFE0U)
#define XPFCMD_RESVD_SHIFT                            (5U)
#define XPFCMD_ACWE_MASK                              (0x80000000U)
#define XPFCMD_ACWE_SHIFT                             (31U)

/* XPFACS */
#define XPFACS_RESVD1_MASK                            (0x00000003U)
#define XPFACS_RESVD1_SHIFT                           (0U)
#define XPFACS_ACEN_MASK                              (0x0000000CU)
#define XPFACS_ACEN_SHIFT                             (2U)
#define XPFACS_RESVD2_MASK                            (0x7FFFFFF0U)
#define XPFACS_RESVD2_SHIFT                           (4U)
#define XPFACS_ACWE_MASK                              (0x80000000U)
#define XPFACS_ACWE_SHIFT                             (31U)

/* XPFAC0 */
#define XPFAC0_SENT_MASK                              (0x000FFFFFU)
#define XPFAC0_SENT_SHIFT                             (0U)
#define XPFAC0_RESVD_MASK                             (0xFFF00000U)
#define XPFAC0_RESVD_SHIFT                            (20U)

/* XPFAC1 */
#define XPFAC1_CANCELED_MASK                          (0x000FFFFFU)
#define XPFAC1_CANCELED_SHIFT                         (0U)
#define XPFAC1_RESVD_MASK                             (0xFFF00000U)
#define XPFAC1_RESVD_SHIFT                            (20U)

/* XPFAC2 */
#define XPFAC2_HIT_MASK                               (0x000FFFFFU)
#define XPFAC2_HIT_SHIFT                              (0U)
#define XPFAC2_RESVD_MASK                             (0xFFF00000U)
#define XPFAC2_RESVD_SHIFT                            (20U)

/* XPFAC3 */
#define XPFAC3_MISS_MASK                              (0x000FFFFFU)
#define XPFAC3_MISS_SHIFT                             (0U)
#define XPFAC3_RESVD_MASK                             (0xFFF00000U)
#define XPFAC3_RESVD_SHIFT                            (20U)

/* XPFADDR */
#define XPFADDR_AVL_MASK                              (0x00000001U)
#define XPFADDR_AVL_SHIFT                             (0U)
#define XPFADDR_DVL_MASK                              (0x00000002U)
#define XPFADDR_DVL_SHIFT                             (1U)
#define XPFADDR_DPL_MASK                              (0x00000004U)
#define XPFADDR_DPL_SHIFT                             (2U)
#define XPFADDR_AVH_MASK                              (0x00000008U)
#define XPFADDR_AVH_SHIFT                             (3U)
#define XPFADDR_DVH_MASK                              (0x00000010U)
#define XPFADDR_DVH_SHIFT                             (4U)
#define XPFADDR_DPH_MASK                              (0x00000020U)
#define XPFADDR_DPH_SHIFT                             (5U)
#define XPFADDR_DIR_MASK                              (0x00000040U)
#define XPFADDR_DIR_SHIFT                             (6U)
#define XPFADDR_ADDR_MASK                             (0xFFFFFF80U)
#define XPFADDR_ADDR_SHIFT                            (7U)

/* XEDIAX */
#define XEDIAX_RESVD_MASK                             (0x00000FFFU)
#define XEDIAX_RESVD_SHIFT                            (0U)
#define XEDIAX_RADDR_MASK                             (0xFFFFF000U)
#define XEDIAX_RADDR_SHIFT                            (12U)

/* XMPAXL */
#define XMPAXL_UX_MASK                                (0x00000001U)
#define XMPAXL_UX_SHIFT                               (0U)
#define XMPAXL_UW_MASK                                (0x00000002U)
#define XMPAXL_UW_SHIFT                               (1U)
#define XMPAXL_UR_MASK                                (0x00000004U)
#define XMPAXL_UR_SHIFT                               (2U)
#define XMPAXL_SX_MASK                                (0x00000008U)
#define XMPAXL_SX_SHIFT                               (3U)
#define XMPAXL_SW_MASK                                (0x00000010U)
#define XMPAXL_SW_SHIFT                               (4U)
#define XMPAXL_SR_MASK                                (0x00000020U)
#define XMPAXL_SR_SHIFT                               (5U)
#define XMPAXL_NS_MASK                                (0x00000040U)
#define XMPAXL_NS_SHIFT                               (6U)
#define XMPAXL_EMU_MASK                               (0x00000080U)
#define XMPAXL_EMU_SHIFT                              (7U)
#define XMPAXL_RADDR_MASK                             (0xFFFFFF00U)
#define XMPAXL_RADDR_SHIFT                            (8U)


/* XMPAXH */
#define XMPAXH_SEGSZ_MASK                             (0x0000001FU)
#define XMPAXH_SEGSZ_SHIFT                            (0U)
#define XMPAXH_BADDR_MASK                             (0xFFFFF000U)
#define XMPAXH_BADDR_SHIFT                            (12U)

#ifdef __cplusplus
}
#endif
#endif
