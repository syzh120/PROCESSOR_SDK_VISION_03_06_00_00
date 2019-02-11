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
*  \file   hw_mcasp.h
*
*  \brief  register-level header file for MCASP
*
**/

#ifndef HW_MCASP_H_
#define HW_MCASP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
** McASP Register Offset for MCASP_XRSRCTL(x), MCASP_TXBUF(x), MCASP_RXBUF(x),
   MCASP_DITCSRA(x), MCASP_DITCSRB(x), MCASP_DITUDRA(x), and MCASP_DITUDRB(x) register set.
*/
#define MCASP_REG_OFFSET                                                                                    ((uint32_t)0x4U)

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MCASP_PID                                                                                           ((uint32_t)0x0U)
#define MCASP_PWRIDLESYSCONFIG                                                                              ((uint32_t)0x4U)
#define MCASP_PFUNC                                                                                         ((uint32_t)0x10U)
#define MCASP_PDIR                                                                                          ((uint32_t)0x14U)
#define MCASP_PDOUT                                                                                         ((uint32_t)0x18U)
#define MCASP_PDIN                                                                                          ((uint32_t)0x1cU)
#define MCASP_PDSET                                                                                         ((uint32_t)0x1cU)
#define MCASP_PDCLR                                                                                         ((uint32_t)0x20U)
#define MCASP_GBLCTL                                                                                        ((uint32_t)0x44U)
#define MCASP_AMUTE                                                                                         ((uint32_t)0x48U)
#define MCASP_LBCTL                                                                                         ((uint32_t)0x4cU)
#define MCASP_TXDITCTL                                                                                      ((uint32_t)0x50U)
#define MCASP_GBLCTLR                                                                                       ((uint32_t)0x60U)
#define MCASP_RXMASK                                                                                        ((uint32_t)0x64U)
#define MCASP_RXFMT                                                                                         ((uint32_t)0x68U)
#define MCASP_RXFMCTL                                                                                       ((uint32_t)0x6cU)
#define MCASP_ACLKRCTL                                                                                      ((uint32_t)0x70U)
#define MCASP_AHCLKRCTL                                                                                     ((uint32_t)0x74U)
#define MCASP_RXTDM                                                                                         ((uint32_t)0x78U)
#define MCASP_EVTCTLR                                                                                       ((uint32_t)0x7cU)
#define MCASP_RXSTAT                                                                                        ((uint32_t)0x80U)
#define MCASP_RXTDMSLOT                                                                                     ((uint32_t)0x84U)
#define MCASP_RXCLKCHK                                                                                      ((uint32_t)0x88U)
#define MCASP_REVTCTL                                                                                       ((uint32_t)0x8cU)
#define MCASP_GBLCTLX                                                                                       ((uint32_t)0xa0U)
#define MCASP_TXMASK                                                                                        ((uint32_t)0xa4U)
#define MCASP_TXFMT                                                                                         ((uint32_t)0xa8U)
#define MCASP_TXFMCTL                                                                                       ((uint32_t)0xacU)
#define MCASP_ACLKXCTL                                                                                      ((uint32_t)0xb0U)
#define MCASP_AHCLKXCTL                                                                                     ((uint32_t)0xb4U)
#define MCASP_TXTDM                                                                                         ((uint32_t)0xb8U)
#define MCASP_EVTCTLX                                                                                       ((uint32_t)0xbcU)
#define MCASP_TXSTAT                                                                                        ((uint32_t)0xc0U)
#define MCASP_TXTDMSLOT                                                                                     ((uint32_t)0xc4U)
#define MCASP_TXCLKCHK                                                                                      ((uint32_t)0xc8U)
#define MCASP_XEVTCTL                                                                                       ((uint32_t)0xccU)
#define MCASP_CLKADJEN                                                                                      ((uint32_t)0xd0U)
#define MCASP_DITCSRA0                                                                                      ((uint32_t)0x100U)
#define MCASP_DITCSRA1                                                                                      ((uint32_t)0x104U)
#define MCASP_DITCSRA2                                                                                      ((uint32_t)0x108U)
#define MCASP_DITCSRA3                                                                                      ((uint32_t)0x10cU)
#define MCASP_DITCSRA4                                                                                      ((uint32_t)0x110U)
#define MCASP_DITCSRA5                                                                                      ((uint32_t)0x114U)
#define MCASP_DITCSRB0                                                                                      ((uint32_t)0x118U)
#define MCASP_DITCSRB1                                                                                      ((uint32_t)0x11cU)
#define MCASP_DITCSRB2                                                                                      ((uint32_t)0x120U)
#define MCASP_DITCSRB3                                                                                      ((uint32_t)0x124U)
#define MCASP_DITCSRB4                                                                                      ((uint32_t)0x128U)
#define MCASP_DITCSRB5                                                                                      ((uint32_t)0x12cU)
#define MCASP_DITUDRA0                                                                                      ((uint32_t)0x130U)
#define MCASP_DITUDRA1                                                                                      ((uint32_t)0x134U)
#define MCASP_DITUDRA2                                                                                      ((uint32_t)0x138U)
#define MCASP_DITUDRA3                                                                                      ((uint32_t)0x13cU)
#define MCASP_DITUDRA4                                                                                      ((uint32_t)0x140U)
#define MCASP_DITUDRA5                                                                                      ((uint32_t)0x144U)
#define MCASP_DITUDRB0                                                                                      ((uint32_t)0x148U)
#define MCASP_DITUDRB1                                                                                      ((uint32_t)0x14cU)
#define MCASP_DITUDRB2                                                                                      ((uint32_t)0x150U)
#define MCASP_DITUDRB3                                                                                      ((uint32_t)0x154U)
#define MCASP_DITUDRB4                                                                                      ((uint32_t)0x158U)
#define MCASP_DITUDRB5                                                                                      ((uint32_t)0x15cU)
#define MCASP_XRSRCTL0                                                                                      ((uint32_t)0x180U)
#define MCASP_XRSRCTL1                                                                                      ((uint32_t)0x184U)
#define MCASP_XRSRCTL2                                                                                      ((uint32_t)0x188U)
#define MCASP_XRSRCTL3                                                                                      ((uint32_t)0x18cU)
#define MCASP_XRSRCTL4                                                                                      ((uint32_t)0x190U)
#define MCASP_XRSRCTL5                                                                                      ((uint32_t)0x194U)
#define MCASP_XRSRCTL6                                                                                      ((uint32_t)0x198U)
#define MCASP_XRSRCTL7                                                                                      ((uint32_t)0x19cU)
#define MCASP_XRSRCTL8                                                                                      ((uint32_t)0x1a0U)
#define MCASP_XRSRCTL9                                                                                      ((uint32_t)0x1a4U)
#define MCASP_XRSRCTL10                                                                                     ((uint32_t)0x1a8U)
#define MCASP_XRSRCTL11                                                                                     ((uint32_t)0x1acU)
#define MCASP_XRSRCTL12                                                                                     ((uint32_t)0x1b0U)
#define MCASP_XRSRCTL13                                                                                     ((uint32_t)0x1b4U)
#define MCASP_XRSRCTL14                                                                                     ((uint32_t)0x1b8U)
#define MCASP_XRSRCTL15                                                                                     ((uint32_t)0x1bcU)
#define MCASP_TXBUF0                                                                                        ((uint32_t)0x200U)
#define MCASP_TXBUF1                                                                                        ((uint32_t)0x204U)
#define MCASP_TXBUF2                                                                                        ((uint32_t)0x208U)
#define MCASP_TXBUF3                                                                                        ((uint32_t)0x20cU)
#define MCASP_TXBUF4                                                                                        ((uint32_t)0x210U)
#define MCASP_TXBUF5                                                                                        ((uint32_t)0x214U)
#define MCASP_TXBUF6                                                                                        ((uint32_t)0x218U)
#define MCASP_TXBUF7                                                                                        ((uint32_t)0x21cU)
#define MCASP_TXBUF8                                                                                        ((uint32_t)0x220U)
#define MCASP_TXBUF9                                                                                        ((uint32_t)0x224U)
#define MCASP_TXBUF10                                                                                       ((uint32_t)0x228U)
#define MCASP_TXBUF11                                                                                       ((uint32_t)0x22cU)
#define MCASP_TXBUF12                                                                                       ((uint32_t)0x230U)
#define MCASP_TXBUF13                                                                                       ((uint32_t)0x234U)
#define MCASP_TXBUF14                                                                                       ((uint32_t)0x238U)
#define MCASP_TXBUF15                                                                                       ((uint32_t)0x23cU)
#define MCASP_RXBUF0                                                                                        ((uint32_t)0x280U)
#define MCASP_RXBUF1                                                                                        ((uint32_t)0x284U)
#define MCASP_RXBUF2                                                                                        ((uint32_t)0x288U)
#define MCASP_RXBUF3                                                                                        ((uint32_t)0x28cU)
#define MCASP_RXBUF4                                                                                        ((uint32_t)0x290U)
#define MCASP_RXBUF5                                                                                        ((uint32_t)0x294U)
#define MCASP_RXBUF6                                                                                        ((uint32_t)0x298U)
#define MCASP_RXBUF7                                                                                        ((uint32_t)0x29cU)
#define MCASP_RXBUF8                                                                                        ((uint32_t)0x2a0U)
#define MCASP_RXBUF9                                                                                        ((uint32_t)0x2a4U)
#define MCASP_RXBUF10                                                                                       ((uint32_t)0x2a8U)
#define MCASP_RXBUF11                                                                                       ((uint32_t)0x2acU)
#define MCASP_RXBUF12                                                                                       ((uint32_t)0x2b0U)
#define MCASP_RXBUF13                                                                                       ((uint32_t)0x2b4U)
#define MCASP_RXBUF14                                                                                       ((uint32_t)0x2b8U)
#define MCASP_RXBUF15                                                                                       ((uint32_t)0x2bcU)
#define MCASP_WFIFOCTL                                                                                      ((uint32_t)0x1000U)
#define MCASP_RFIFOCTL                                                                                      ((uint32_t)0x1008U)
#define MCASP_WFIFOSTS                                                                                      ((uint32_t)0x1004U)
#define MCASP_RFIFOSTS                                                                                      ((uint32_t)0x100cU)

/*
** Base address of MCASP_XRSRCTL(x)
*/
#define MCASP_SRCTL(x)                           ((uint32_t) MCASP_XRSRCTL0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_TXBUF(x)
*/
#define MCASP_TXBUF(x)                           ((uint32_t) MCASP_TXBUF0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_RXBUF(x)
*/
#define MCASP_RXBUF(x)                           ((uint32_t) MCASP_RXBUF0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITCSRA(x)
*/
#define MCASP_DITCSRA(x)                         ((uint32_t) MCASP_DITCSRA0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITCSRB(x)
*/
#define MCASP_DITCSRB(x)                         ((uint32_t) MCASP_DITCSRB0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITUDRA(x)
*/
#define MCASP_DITUDRA(x)                         ((uint32_t) MCASP_DITUDRA0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*
** Base address of MCASP_DITUDRB(x)
*/
#define MCASP_DITUDRB(x)                         ((uint32_t) MCASP_DITUDRB0 + \
                                                  (MCASP_REG_OFFSET * (x)))
/*****************************************************************************/

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MCASP_PID_REVISION_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_PID_REVISION_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_PWRIDLESYSCONFIG_IDLE_MODE_SHIFT                                                               ((uint32_t)0U)
#define MCASP_PWRIDLESYSCONFIG_IDLE_MODE_MASK                                                                ((uint32_t)0x00000003U)

#define MCASP_PWRIDLESYSCONFIG_OTHER_SHIFT                                                                   ((uint32_t)2U)
#define MCASP_PWRIDLESYSCONFIG_OTHER_MASK                                                                    ((uint32_t)0x0000003cU)

#define MCASP_PWRIDLESYSCONFIG_RSV_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_PWRIDLESYSCONFIG_RSV_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_PFUNC_AFSR_SHIFT                                                                               ((uint32_t)31U)
#define MCASP_PFUNC_AFSR_MASK                                                                                ((uint32_t)0x80000000U)
#define MCASP_PFUNC_AFSR_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AFSR_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_ACLKR_SHIFT                                                                              ((uint32_t)29U)
#define MCASP_PFUNC_ACLKR_MASK                                                                               ((uint32_t)0x20000000U)
#define MCASP_PFUNC_ACLKR_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_ACLKR_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AFSX_SHIFT                                                                               ((uint32_t)28U)
#define MCASP_PFUNC_AFSX_MASK                                                                                ((uint32_t)0x10000000U)
#define MCASP_PFUNC_AFSX_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AFSX_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AHCLKX_SHIFT                                                                             ((uint32_t)27U)
#define MCASP_PFUNC_AHCLKX_MASK                                                                              ((uint32_t)0x08000000U)
#define MCASP_PFUNC_AHCLKX_MCASP                                                                             ((uint32_t)0U)
#define MCASP_PFUNC_AHCLKX_GPIO                                                                              ((uint32_t)1U)

#define MCASP_PFUNC_ACLKX_SHIFT                                                                              ((uint32_t)26U)
#define MCASP_PFUNC_ACLKX_MASK                                                                               ((uint32_t)0x04000000U)
#define MCASP_PFUNC_ACLKX_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_ACLKX_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AMUTE_SHIFT                                                                              ((uint32_t)25U)
#define MCASP_PFUNC_AMUTE_MASK                                                                               ((uint32_t)0x02000000U)
#define MCASP_PFUNC_AMUTE_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AMUTE_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_RESV1_SHIFT                                                                              ((uint32_t)16U)
#define MCASP_PFUNC_RESV1_MASK                                                                               ((uint32_t)0x01ff0000U)

#define MCASP_PFUNC_AXR15_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_PFUNC_AXR15_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_PFUNC_AXR15_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR15_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR14_SHIFT                                                                              ((uint32_t)14U)
#define MCASP_PFUNC_AXR14_MASK                                                                               ((uint32_t)0x00004000U)
#define MCASP_PFUNC_AXR14_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR14_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR13_SHIFT                                                                              ((uint32_t)13U)
#define MCASP_PFUNC_AXR13_MASK                                                                               ((uint32_t)0x00002000U)
#define MCASP_PFUNC_AXR13_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR13_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR12_SHIFT                                                                              ((uint32_t)12U)
#define MCASP_PFUNC_AXR12_MASK                                                                               ((uint32_t)0x00001000U)
#define MCASP_PFUNC_AXR12_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR12_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR11_SHIFT                                                                              ((uint32_t)11U)
#define MCASP_PFUNC_AXR11_MASK                                                                               ((uint32_t)0x00000800U)
#define MCASP_PFUNC_AXR11_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR11_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR10_SHIFT                                                                              ((uint32_t)10U)
#define MCASP_PFUNC_AXR10_MASK                                                                               ((uint32_t)0x00000400U)
#define MCASP_PFUNC_AXR10_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_AXR10_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PFUNC_AXR9_SHIFT                                                                               ((uint32_t)9U)
#define MCASP_PFUNC_AXR9_MASK                                                                                ((uint32_t)0x00000200U)
#define MCASP_PFUNC_AXR9_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR9_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR8_SHIFT                                                                               ((uint32_t)8U)
#define MCASP_PFUNC_AXR8_MASK                                                                                ((uint32_t)0x00000100U)
#define MCASP_PFUNC_AXR8_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR8_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR7_SHIFT                                                                               ((uint32_t)7U)
#define MCASP_PFUNC_AXR7_MASK                                                                                ((uint32_t)0x00000080U)
#define MCASP_PFUNC_AXR7_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR7_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR6_SHIFT                                                                               ((uint32_t)6U)
#define MCASP_PFUNC_AXR6_MASK                                                                                ((uint32_t)0x00000040U)
#define MCASP_PFUNC_AXR6_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR6_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR5_SHIFT                                                                               ((uint32_t)5U)
#define MCASP_PFUNC_AXR5_MASK                                                                                ((uint32_t)0x00000020U)
#define MCASP_PFUNC_AXR5_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR5_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR4_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_PFUNC_AXR4_MASK                                                                                ((uint32_t)0x00000010U)
#define MCASP_PFUNC_AXR4_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR4_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR3_SHIFT                                                                               ((uint32_t)3U)
#define MCASP_PFUNC_AXR3_MASK                                                                                ((uint32_t)0x00000008U)
#define MCASP_PFUNC_AXR3_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR3_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR2_SHIFT                                                                               ((uint32_t)2U)
#define MCASP_PFUNC_AXR2_MASK                                                                                ((uint32_t)0x00000004U)
#define MCASP_PFUNC_AXR2_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR2_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR1_SHIFT                                                                               ((uint32_t)1U)
#define MCASP_PFUNC_AXR1_MASK                                                                                ((uint32_t)0x00000002U)
#define MCASP_PFUNC_AXR1_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR1_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_AXR0_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR0_MASK                                                                                ((uint32_t)0x00000001U)
#define MCASP_PFUNC_AXR0_MCASP                                                                               ((uint32_t)0U)
#define MCASP_PFUNC_AXR0_GPIO                                                                                ((uint32_t)1U)

#define MCASP_PFUNC_RESV2_SHIFT                                                                              ((uint32_t)30U)
#define MCASP_PFUNC_RESV2_MASK                                                                               ((uint32_t)0x40000000U)
#define MCASP_PFUNC_RESV2_MCASP                                                                              ((uint32_t)0U)
#define MCASP_PFUNC_RESV2_GPIO                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AFSR_SHIFT                                                                                ((uint32_t)31U)
#define MCASP_PDIR_AFSR_MASK                                                                                 ((uint32_t)0x80000000U)
#define MCASP_PDIR_AFSR_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AFSR_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_ACLKR_SHIFT                                                                               ((uint32_t)29U)
#define MCASP_PDIR_ACLKR_MASK                                                                                ((uint32_t)0x20000000U)
#define MCASP_PDIR_ACLKR_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_ACLKR_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AFSX_SHIFT                                                                                ((uint32_t)28U)
#define MCASP_PDIR_AFSX_MASK                                                                                 ((uint32_t)0x10000000U)
#define MCASP_PDIR_AFSX_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AFSX_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AHCLKX_SHIFT                                                                              ((uint32_t)27U)
#define MCASP_PDIR_AHCLKX_MASK                                                                               ((uint32_t)0x08000000U)
#define MCASP_PDIR_AHCLKX_INPUT                                                                              ((uint32_t)0U)
#define MCASP_PDIR_AHCLKX_OUTPUT                                                                             ((uint32_t)1U)

#define MCASP_PDIR_ACLKX_SHIFT                                                                               ((uint32_t)26U)
#define MCASP_PDIR_ACLKX_MASK                                                                                ((uint32_t)0x04000000U)
#define MCASP_PDIR_ACLKX_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_ACLKX_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AMUTE_SHIFT                                                                               ((uint32_t)25U)
#define MCASP_PDIR_AMUTE_MASK                                                                                ((uint32_t)0x02000000U)
#define MCASP_PDIR_AMUTE_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AMUTE_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_RESV_SHIFT                                                                                ((uint32_t)16U)
#define MCASP_PDIR_RESV_MASK                                                                                 ((uint32_t)0x01ff0000U)

#define MCASP_PDIR_AXR15_SHIFT                                                                               ((uint32_t)15U)
#define MCASP_PDIR_AXR15_MASK                                                                                ((uint32_t)0x00008000U)
#define MCASP_PDIR_AXR15_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR15_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR14_SHIFT                                                                               ((uint32_t)14U)
#define MCASP_PDIR_AXR14_MASK                                                                                ((uint32_t)0x00004000U)
#define MCASP_PDIR_AXR14_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR14_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR13_SHIFT                                                                               ((uint32_t)13U)
#define MCASP_PDIR_AXR13_MASK                                                                                ((uint32_t)0x00002000U)
#define MCASP_PDIR_AXR13_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR13_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR12_SHIFT                                                                               ((uint32_t)12U)
#define MCASP_PDIR_AXR12_MASK                                                                                ((uint32_t)0x00001000U)
#define MCASP_PDIR_AXR12_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR12_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR11_SHIFT                                                                               ((uint32_t)11U)
#define MCASP_PDIR_AXR11_MASK                                                                                ((uint32_t)0x00000800U)
#define MCASP_PDIR_AXR11_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR11_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR10_SHIFT                                                                               ((uint32_t)10U)
#define MCASP_PDIR_AXR10_MASK                                                                                ((uint32_t)0x00000400U)
#define MCASP_PDIR_AXR10_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_AXR10_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDIR_AXR9_SHIFT                                                                                ((uint32_t)9U)
#define MCASP_PDIR_AXR9_MASK                                                                                 ((uint32_t)0x00000200U)
#define MCASP_PDIR_AXR9_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR9_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR8_SHIFT                                                                                ((uint32_t)8U)
#define MCASP_PDIR_AXR8_MASK                                                                                 ((uint32_t)0x00000100U)
#define MCASP_PDIR_AXR8_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR8_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR7_SHIFT                                                                                ((uint32_t)7U)
#define MCASP_PDIR_AXR7_MASK                                                                                 ((uint32_t)0x00000080U)
#define MCASP_PDIR_AXR7_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR7_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR6_SHIFT                                                                                ((uint32_t)6U)
#define MCASP_PDIR_AXR6_MASK                                                                                 ((uint32_t)0x00000040U)
#define MCASP_PDIR_AXR6_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR6_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR5_SHIFT                                                                                ((uint32_t)5U)
#define MCASP_PDIR_AXR5_MASK                                                                                 ((uint32_t)0x00000020U)
#define MCASP_PDIR_AXR5_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR5_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR4_SHIFT                                                                                ((uint32_t)4U)
#define MCASP_PDIR_AXR4_MASK                                                                                 ((uint32_t)0x00000010U)
#define MCASP_PDIR_AXR4_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR4_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR3_SHIFT                                                                                ((uint32_t)3U)
#define MCASP_PDIR_AXR3_MASK                                                                                 ((uint32_t)0x00000008U)
#define MCASP_PDIR_AXR3_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR3_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR2_SHIFT                                                                                ((uint32_t)2U)
#define MCASP_PDIR_AXR2_MASK                                                                                 ((uint32_t)0x00000004U)
#define MCASP_PDIR_AXR2_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR2_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR1_SHIFT                                                                                ((uint32_t)1U)
#define MCASP_PDIR_AXR1_MASK                                                                                 ((uint32_t)0x00000002U)
#define MCASP_PDIR_AXR1_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR1_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_AXR0_SHIFT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR0_MASK                                                                                 ((uint32_t)0x00000001U)
#define MCASP_PDIR_AXR0_INPUT                                                                                ((uint32_t)0U)
#define MCASP_PDIR_AXR0_OUTPUT                                                                               ((uint32_t)1U)

#define MCASP_PDIR_RESV1_SHIFT                                                                               ((uint32_t)30U)
#define MCASP_PDIR_RESV1_MASK                                                                                ((uint32_t)0x40000000U)
#define MCASP_PDIR_RESV1_INPUT                                                                               ((uint32_t)0U)
#define MCASP_PDIR_RESV1_OUTPUT                                                                              ((uint32_t)1U)

#define MCASP_PDOUT_AFSR_SHIFT                                                                               ((uint32_t)31U)
#define MCASP_PDOUT_AFSR_MASK                                                                                ((uint32_t)0x80000000U)
#define MCASP_PDOUT_AFSR_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AFSR_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AHCLKR_SHIFT                                                                             ((uint32_t)30U)
#define MCASP_PDOUT_AHCLKR_MASK                                                                              ((uint32_t)0x40000000U)
#define MCASP_PDOUT_AHCLKR_DRV0                                                                              ((uint32_t)0U)
#define MCASP_PDOUT_AHCLKR_DRV1                                                                              ((uint32_t)1U)

#define MCASP_PDOUT_ACLKR_SHIFT                                                                              ((uint32_t)29U)
#define MCASP_PDOUT_ACLKR_MASK                                                                               ((uint32_t)0x20000000U)
#define MCASP_PDOUT_ACLKR_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_ACLKR_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AFSX_SHIFT                                                                               ((uint32_t)28U)
#define MCASP_PDOUT_AFSX_MASK                                                                                ((uint32_t)0x10000000U)
#define MCASP_PDOUT_AFSX_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AFSX_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AHCLKX_SHIFT                                                                             ((uint32_t)27U)
#define MCASP_PDOUT_AHCLKX_MASK                                                                              ((uint32_t)0x08000000U)
#define MCASP_PDOUT_AHCLKX_DRV0                                                                              ((uint32_t)0U)
#define MCASP_PDOUT_AHCLKX_DRV1                                                                              ((uint32_t)1U)

#define MCASP_PDOUT_ACLKX_SHIFT                                                                              ((uint32_t)26U)
#define MCASP_PDOUT_ACLKX_MASK                                                                               ((uint32_t)0x04000000U)
#define MCASP_PDOUT_ACLKX_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_ACLKX_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AMUTE_SHIFT                                                                              ((uint32_t)25U)
#define MCASP_PDOUT_AMUTE_MASK                                                                               ((uint32_t)0x02000000U)
#define MCASP_PDOUT_AMUTE_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AMUTE_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_RESV_SHIFT                                                                               ((uint32_t)16U)
#define MCASP_PDOUT_RESV_MASK                                                                                ((uint32_t)0x01ff0000U)

#define MCASP_PDOUT_AXR15_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_PDOUT_AXR15_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_PDOUT_AXR15_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR15_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR14_SHIFT                                                                              ((uint32_t)14U)
#define MCASP_PDOUT_AXR14_MASK                                                                               ((uint32_t)0x00004000U)
#define MCASP_PDOUT_AXR14_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR14_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR13_SHIFT                                                                              ((uint32_t)13U)
#define MCASP_PDOUT_AXR13_MASK                                                                               ((uint32_t)0x00002000U)
#define MCASP_PDOUT_AXR13_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR13_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR12_SHIFT                                                                              ((uint32_t)12U)
#define MCASP_PDOUT_AXR12_MASK                                                                               ((uint32_t)0x00001000U)
#define MCASP_PDOUT_AXR12_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR12_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR11_SHIFT                                                                              ((uint32_t)11U)
#define MCASP_PDOUT_AXR11_MASK                                                                               ((uint32_t)0x00000800U)
#define MCASP_PDOUT_AXR11_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR11_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR10_SHIFT                                                                              ((uint32_t)10U)
#define MCASP_PDOUT_AXR10_MASK                                                                               ((uint32_t)0x00000400U)
#define MCASP_PDOUT_AXR10_DRV0                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR10_DRV1                                                                               ((uint32_t)1U)

#define MCASP_PDOUT_AXR9_SHIFT                                                                               ((uint32_t)9U)
#define MCASP_PDOUT_AXR9_MASK                                                                                ((uint32_t)0x00000200U)
#define MCASP_PDOUT_AXR9_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR9_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR8_SHIFT                                                                               ((uint32_t)8U)
#define MCASP_PDOUT_AXR8_MASK                                                                                ((uint32_t)0x00000100U)
#define MCASP_PDOUT_AXR8_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR8_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR7_SHIFT                                                                               ((uint32_t)7U)
#define MCASP_PDOUT_AXR7_MASK                                                                                ((uint32_t)0x00000080U)
#define MCASP_PDOUT_AXR7_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR7_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR6_SHIFT                                                                               ((uint32_t)6U)
#define MCASP_PDOUT_AXR6_MASK                                                                                ((uint32_t)0x00000040U)
#define MCASP_PDOUT_AXR6_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR6_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR5_SHIFT                                                                               ((uint32_t)5U)
#define MCASP_PDOUT_AXR5_MASK                                                                                ((uint32_t)0x00000020U)
#define MCASP_PDOUT_AXR5_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR5_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR4_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_PDOUT_AXR4_MASK                                                                                ((uint32_t)0x00000010U)
#define MCASP_PDOUT_AXR4_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR4_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR3_SHIFT                                                                               ((uint32_t)3U)
#define MCASP_PDOUT_AXR3_MASK                                                                                ((uint32_t)0x00000008U)
#define MCASP_PDOUT_AXR3_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR3_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR2_SHIFT                                                                               ((uint32_t)2U)
#define MCASP_PDOUT_AXR2_MASK                                                                                ((uint32_t)0x00000004U)
#define MCASP_PDOUT_AXR2_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR2_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR1_SHIFT                                                                               ((uint32_t)1U)
#define MCASP_PDOUT_AXR1_MASK                                                                                ((uint32_t)0x00000002U)
#define MCASP_PDOUT_AXR1_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR1_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDOUT_AXR0_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_PDOUT_AXR0_MASK                                                                                ((uint32_t)0x00000001U)
#define MCASP_PDOUT_AXR0_DRV0                                                                                ((uint32_t)0U)
#define MCASP_PDOUT_AXR0_DRV1                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AFSR_SHIFT                                                                                ((uint32_t)31U)
#define MCASP_PDIN_AFSR_MASK                                                                                 ((uint32_t)0x80000000U)
#define MCASP_PDIN_AFSR_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AFSR_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_ACLKR_SHIFT                                                                               ((uint32_t)29U)
#define MCASP_PDIN_ACLKR_MASK                                                                                ((uint32_t)0x20000000U)
#define MCASP_PDIN_ACLKR_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_ACLKR_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AFSX_SHIFT                                                                                ((uint32_t)28U)
#define MCASP_PDIN_AFSX_MASK                                                                                 ((uint32_t)0x10000000U)
#define MCASP_PDIN_AFSX_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AFSX_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AHCLKX_SHIFT                                                                              ((uint32_t)27U)
#define MCASP_PDIN_AHCLKX_MASK                                                                               ((uint32_t)0x08000000U)
#define MCASP_PDIN_AHCLKX_LOW                                                                                ((uint32_t)0U)
#define MCASP_PDIN_AHCLKX_HIGH                                                                               ((uint32_t)1U)

#define MCASP_PDIN_ACLKX_SHIFT                                                                               ((uint32_t)26U)
#define MCASP_PDIN_ACLKX_MASK                                                                                ((uint32_t)0x04000000U)
#define MCASP_PDIN_ACLKX_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_ACLKX_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AMUTE_SHIFT                                                                               ((uint32_t)25U)
#define MCASP_PDIN_AMUTE_MASK                                                                                ((uint32_t)0x02000000U)
#define MCASP_PDIN_AMUTE_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AMUTE_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_RESV_SHIFT                                                                                ((uint32_t)16U)
#define MCASP_PDIN_RESV_MASK                                                                                 ((uint32_t)0x01ff0000U)

#define MCASP_PDIN_AXR15_SHIFT                                                                               ((uint32_t)15U)
#define MCASP_PDIN_AXR15_MASK                                                                                ((uint32_t)0x00008000U)
#define MCASP_PDIN_AXR15_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR15_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR14_SHIFT                                                                               ((uint32_t)14U)
#define MCASP_PDIN_AXR14_MASK                                                                                ((uint32_t)0x00004000U)
#define MCASP_PDIN_AXR14_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR14_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR13_SHIFT                                                                               ((uint32_t)13U)
#define MCASP_PDIN_AXR13_MASK                                                                                ((uint32_t)0x00002000U)
#define MCASP_PDIN_AXR13_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR13_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR12_SHIFT                                                                               ((uint32_t)12U)
#define MCASP_PDIN_AXR12_MASK                                                                                ((uint32_t)0x00001000U)
#define MCASP_PDIN_AXR12_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR12_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR11_SHIFT                                                                               ((uint32_t)11U)
#define MCASP_PDIN_AXR11_MASK                                                                                ((uint32_t)0x00000800U)
#define MCASP_PDIN_AXR11_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR11_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR10_SHIFT                                                                               ((uint32_t)10U)
#define MCASP_PDIN_AXR10_MASK                                                                                ((uint32_t)0x00000400U)
#define MCASP_PDIN_AXR10_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_AXR10_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDIN_AXR9_SHIFT                                                                                ((uint32_t)9U)
#define MCASP_PDIN_AXR9_MASK                                                                                 ((uint32_t)0x00000200U)
#define MCASP_PDIN_AXR9_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR9_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR8_SHIFT                                                                                ((uint32_t)8U)
#define MCASP_PDIN_AXR8_MASK                                                                                 ((uint32_t)0x00000100U)
#define MCASP_PDIN_AXR8_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR8_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR7_SHIFT                                                                                ((uint32_t)7U)
#define MCASP_PDIN_AXR7_MASK                                                                                 ((uint32_t)0x00000080U)
#define MCASP_PDIN_AXR7_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR7_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR6_SHIFT                                                                                ((uint32_t)6U)
#define MCASP_PDIN_AXR6_MASK                                                                                 ((uint32_t)0x00000040U)
#define MCASP_PDIN_AXR6_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR6_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR5_SHIFT                                                                                ((uint32_t)5U)
#define MCASP_PDIN_AXR5_MASK                                                                                 ((uint32_t)0x00000020U)
#define MCASP_PDIN_AXR5_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR5_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR4_SHIFT                                                                                ((uint32_t)4U)
#define MCASP_PDIN_AXR4_MASK                                                                                 ((uint32_t)0x00000010U)
#define MCASP_PDIN_AXR4_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR4_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR3_SHIFT                                                                                ((uint32_t)3U)
#define MCASP_PDIN_AXR3_MASK                                                                                 ((uint32_t)0x00000008U)
#define MCASP_PDIN_AXR3_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR3_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR2_SHIFT                                                                                ((uint32_t)2U)
#define MCASP_PDIN_AXR2_MASK                                                                                 ((uint32_t)0x00000004U)
#define MCASP_PDIN_AXR2_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR2_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR1_SHIFT                                                                                ((uint32_t)1U)
#define MCASP_PDIN_AXR1_MASK                                                                                 ((uint32_t)0x00000002U)
#define MCASP_PDIN_AXR1_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR1_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_AXR0_SHIFT                                                                                ((uint32_t)0U)
#define MCASP_PDIN_AXR0_MASK                                                                                 ((uint32_t)0x00000001U)
#define MCASP_PDIN_AXR0_LOW                                                                                  ((uint32_t)0U)
#define MCASP_PDIN_AXR0_HIGH                                                                                 ((uint32_t)1U)

#define MCASP_PDIN_RESV1_SHIFT                                                                               ((uint32_t)30U)
#define MCASP_PDIN_RESV1_MASK                                                                                ((uint32_t)0x40000000U)
#define MCASP_PDIN_RESV1_LOW                                                                                 ((uint32_t)0U)
#define MCASP_PDIN_RESV1_HIGH                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AFSR_SHIFT                                                                               ((uint32_t)31U)
#define MCASP_PDSET_AFSR_MASK                                                                                ((uint32_t)0x80000000U)
#define MCASP_PDSET_AFSR_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AFSR_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_ACLKR_SHIFT                                                                              ((uint32_t)29U)
#define MCASP_PDSET_ACLKR_MASK                                                                               ((uint32_t)0x20000000U)
#define MCASP_PDSET_ACLKR_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_ACLKR_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AFSX_SHIFT                                                                               ((uint32_t)28U)
#define MCASP_PDSET_AFSX_MASK                                                                                ((uint32_t)0x10000000U)
#define MCASP_PDSET_AFSX_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AFSX_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AHCLKX_SHIFT                                                                             ((uint32_t)27U)
#define MCASP_PDSET_AHCLKX_MASK                                                                              ((uint32_t)0x08000000U)
#define MCASP_PDSET_AHCLKX_NOEFFECT                                                                          ((uint32_t)0U)
#define MCASP_PDSET_AHCLKX_SET                                                                               ((uint32_t)1U)

#define MCASP_PDSET_ACLKX_SHIFT                                                                              ((uint32_t)26U)
#define MCASP_PDSET_ACLKX_MASK                                                                               ((uint32_t)0x04000000U)
#define MCASP_PDSET_ACLKX_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_ACLKX_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AMUTE_SHIFT                                                                              ((uint32_t)25U)
#define MCASP_PDSET_AMUTE_MASK                                                                               ((uint32_t)0x02000000U)
#define MCASP_PDSET_AMUTE_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AMUTE_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_RESV_SHIFT                                                                               ((uint32_t)16U)
#define MCASP_PDSET_RESV_MASK                                                                                ((uint32_t)0x01ff0000U)

#define MCASP_PDSET_AXR15_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_PDSET_AXR15_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_PDSET_AXR15_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR15_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR14_SHIFT                                                                              ((uint32_t)14U)
#define MCASP_PDSET_AXR14_MASK                                                                               ((uint32_t)0x00004000U)
#define MCASP_PDSET_AXR14_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR14_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR13_SHIFT                                                                              ((uint32_t)13U)
#define MCASP_PDSET_AXR13_MASK                                                                               ((uint32_t)0x00002000U)
#define MCASP_PDSET_AXR13_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR13_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR12_SHIFT                                                                              ((uint32_t)12U)
#define MCASP_PDSET_AXR12_MASK                                                                               ((uint32_t)0x00001000U)
#define MCASP_PDSET_AXR12_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR12_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR11_SHIFT                                                                              ((uint32_t)11U)
#define MCASP_PDSET_AXR11_MASK                                                                               ((uint32_t)0x00000800U)
#define MCASP_PDSET_AXR11_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR11_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR10_SHIFT                                                                              ((uint32_t)10U)
#define MCASP_PDSET_AXR10_MASK                                                                               ((uint32_t)0x00000400U)
#define MCASP_PDSET_AXR10_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_AXR10_SET                                                                                ((uint32_t)1U)

#define MCASP_PDSET_AXR9_SHIFT                                                                               ((uint32_t)9U)
#define MCASP_PDSET_AXR9_MASK                                                                                ((uint32_t)0x00000200U)
#define MCASP_PDSET_AXR9_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR9_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR8_SHIFT                                                                               ((uint32_t)8U)
#define MCASP_PDSET_AXR8_MASK                                                                                ((uint32_t)0x00000100U)
#define MCASP_PDSET_AXR8_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR8_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR7_SHIFT                                                                               ((uint32_t)7U)
#define MCASP_PDSET_AXR7_MASK                                                                                ((uint32_t)0x00000080U)
#define MCASP_PDSET_AXR7_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR7_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR6_SHIFT                                                                               ((uint32_t)6U)
#define MCASP_PDSET_AXR6_MASK                                                                                ((uint32_t)0x00000040U)
#define MCASP_PDSET_AXR6_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR6_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR5_SHIFT                                                                               ((uint32_t)5U)
#define MCASP_PDSET_AXR5_MASK                                                                                ((uint32_t)0x00000020U)
#define MCASP_PDSET_AXR5_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR5_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR4_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_PDSET_AXR4_MASK                                                                                ((uint32_t)0x00000010U)
#define MCASP_PDSET_AXR4_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR4_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR3_SHIFT                                                                               ((uint32_t)3U)
#define MCASP_PDSET_AXR3_MASK                                                                                ((uint32_t)0x00000008U)
#define MCASP_PDSET_AXR3_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR3_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR2_SHIFT                                                                               ((uint32_t)2U)
#define MCASP_PDSET_AXR2_MASK                                                                                ((uint32_t)0x00000004U)
#define MCASP_PDSET_AXR2_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR2_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR1_SHIFT                                                                               ((uint32_t)1U)
#define MCASP_PDSET_AXR1_MASK                                                                                ((uint32_t)0x00000002U)
#define MCASP_PDSET_AXR1_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR1_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_AXR0_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_PDSET_AXR0_MASK                                                                                ((uint32_t)0x00000001U)
#define MCASP_PDSET_AXR0_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDSET_AXR0_SET                                                                                 ((uint32_t)1U)

#define MCASP_PDSET_RESV1_SHIFT                                                                              ((uint32_t)30U)
#define MCASP_PDSET_RESV1_MASK                                                                               ((uint32_t)0x40000000U)
#define MCASP_PDSET_RESV1_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDSET_RESV1_SET                                                                                ((uint32_t)1U)

#define MCASP_PDCLR_AFSR_SHIFT                                                                               ((uint32_t)31U)
#define MCASP_PDCLR_AFSR_MASK                                                                                ((uint32_t)0x80000000U)
#define MCASP_PDCLR_AFSR_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AFSR_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_ACLKR_SHIFT                                                                              ((uint32_t)29U)
#define MCASP_PDCLR_ACLKR_MASK                                                                               ((uint32_t)0x20000000U)
#define MCASP_PDCLR_ACLKR_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_ACLKR_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AFSX_SHIFT                                                                               ((uint32_t)28U)
#define MCASP_PDCLR_AFSX_MASK                                                                                ((uint32_t)0x10000000U)
#define MCASP_PDCLR_AFSX_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AFSX_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AHCLKX_SHIFT                                                                             ((uint32_t)27U)
#define MCASP_PDCLR_AHCLKX_MASK                                                                              ((uint32_t)0x08000000U)
#define MCASP_PDCLR_AHCLKX_NOEFFECT                                                                          ((uint32_t)0U)
#define MCASP_PDCLR_AHCLKX_CLEAR                                                                             ((uint32_t)1U)

#define MCASP_PDCLR_ACLKX_SHIFT                                                                              ((uint32_t)26U)
#define MCASP_PDCLR_ACLKX_MASK                                                                               ((uint32_t)0x04000000U)
#define MCASP_PDCLR_ACLKX_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_ACLKX_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AMUTE_SHIFT                                                                              ((uint32_t)25U)
#define MCASP_PDCLR_AMUTE_MASK                                                                               ((uint32_t)0x02000000U)
#define MCASP_PDCLR_AMUTE_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AMUTE_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_RESV_SHIFT                                                                               ((uint32_t)16U)
#define MCASP_PDCLR_RESV_MASK                                                                                ((uint32_t)0x01ff0000U)

#define MCASP_PDCLR_AXR15_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_PDCLR_AXR15_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_PDCLR_AXR15_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR15_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR14_SHIFT                                                                              ((uint32_t)14U)
#define MCASP_PDCLR_AXR14_MASK                                                                               ((uint32_t)0x00004000U)
#define MCASP_PDCLR_AXR14_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR14_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR13_SHIFT                                                                              ((uint32_t)13U)
#define MCASP_PDCLR_AXR13_MASK                                                                               ((uint32_t)0x00002000U)
#define MCASP_PDCLR_AXR13_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR13_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR12_SHIFT                                                                              ((uint32_t)12U)
#define MCASP_PDCLR_AXR12_MASK                                                                               ((uint32_t)0x00001000U)
#define MCASP_PDCLR_AXR12_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR12_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR11_SHIFT                                                                              ((uint32_t)11U)
#define MCASP_PDCLR_AXR11_MASK                                                                               ((uint32_t)0x00000800U)
#define MCASP_PDCLR_AXR11_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR11_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR10_SHIFT                                                                              ((uint32_t)10U)
#define MCASP_PDCLR_AXR10_MASK                                                                               ((uint32_t)0x00000400U)
#define MCASP_PDCLR_AXR10_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_AXR10_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_PDCLR_AXR9_SHIFT                                                                               ((uint32_t)9U)
#define MCASP_PDCLR_AXR9_MASK                                                                                ((uint32_t)0x00000200U)
#define MCASP_PDCLR_AXR9_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR9_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR8_SHIFT                                                                               ((uint32_t)8U)
#define MCASP_PDCLR_AXR8_MASK                                                                                ((uint32_t)0x00000100U)
#define MCASP_PDCLR_AXR8_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR8_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR7_SHIFT                                                                               ((uint32_t)7U)
#define MCASP_PDCLR_AXR7_MASK                                                                                ((uint32_t)0x00000080U)
#define MCASP_PDCLR_AXR7_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR7_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR6_SHIFT                                                                               ((uint32_t)6U)
#define MCASP_PDCLR_AXR6_MASK                                                                                ((uint32_t)0x00000040U)
#define MCASP_PDCLR_AXR6_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR6_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR5_SHIFT                                                                               ((uint32_t)5U)
#define MCASP_PDCLR_AXR5_MASK                                                                                ((uint32_t)0x00000020U)
#define MCASP_PDCLR_AXR5_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR5_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR4_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_PDCLR_AXR4_MASK                                                                                ((uint32_t)0x00000010U)
#define MCASP_PDCLR_AXR4_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR4_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR3_SHIFT                                                                               ((uint32_t)3U)
#define MCASP_PDCLR_AXR3_MASK                                                                                ((uint32_t)0x00000008U)
#define MCASP_PDCLR_AXR3_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR3_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR2_SHIFT                                                                               ((uint32_t)2U)
#define MCASP_PDCLR_AXR2_MASK                                                                                ((uint32_t)0x00000004U)
#define MCASP_PDCLR_AXR2_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR2_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR1_SHIFT                                                                               ((uint32_t)1U)
#define MCASP_PDCLR_AXR1_MASK                                                                                ((uint32_t)0x00000002U)
#define MCASP_PDCLR_AXR1_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR1_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_AXR0_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_PDCLR_AXR0_MASK                                                                                ((uint32_t)0x00000001U)
#define MCASP_PDCLR_AXR0_NOEFFECT                                                                            ((uint32_t)0U)
#define MCASP_PDCLR_AXR0_CLEAR                                                                               ((uint32_t)1U)

#define MCASP_PDCLR_RESV1_SHIFT                                                                              ((uint32_t)30U)
#define MCASP_PDCLR_RESV1_MASK                                                                               ((uint32_t)0x40000000U)
#define MCASP_PDCLR_RESV1_NOEFFECT                                                                           ((uint32_t)0U)
#define MCASP_PDCLR_RESV1_CLEAR                                                                              ((uint32_t)1U)

#define MCASP_GBLCTL_RESERVED_SHIFT                                                                          ((uint32_t)13U)
#define MCASP_GBLCTL_RESERVED_MASK                                                                           ((uint32_t)0xffffe000U)

#define MCASP_GBLCTL_XFRST_SHIFT                                                                             ((uint32_t)12U)
#define MCASP_GBLCTL_XFRST_MASK                                                                              ((uint32_t)0x00001000U)
#define MCASP_GBLCTL_XFRST_RESET                                                                             ((uint32_t)0U)
#define MCASP_GBLCTL_XFRST_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_GBLCTL_XSMRST_SHIFT                                                                            ((uint32_t)11U)
#define MCASP_GBLCTL_XSMRST_MASK                                                                             ((uint32_t)0x00000800U)
#define MCASP_GBLCTL_XSMRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTL_XSMRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTL_XSRCLR_SHIFT                                                                            ((uint32_t)10U)
#define MCASP_GBLCTL_XSRCLR_MASK                                                                             ((uint32_t)0x00000400U)
#define MCASP_GBLCTL_XSRCLR_CLEAR                                                                            ((uint32_t)0U)
#define MCASP_GBLCTL_XSRCLR_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTL_XHCLKRST_SHIFT                                                                          ((uint32_t)9U)
#define MCASP_GBLCTL_XHCLKRST_MASK                                                                           ((uint32_t)0x00000200U)
#define MCASP_GBLCTL_XHCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTL_XHCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_GBLCTL_XCLKRST_SHIFT                                                                           ((uint32_t)8U)
#define MCASP_GBLCTL_XCLKRST_MASK                                                                            ((uint32_t)0x00000100U)
#define MCASP_GBLCTL_XCLKRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTL_XCLKRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTL_RESERVED1_SHIFT                                                                         ((uint32_t)5U)
#define MCASP_GBLCTL_RESERVED1_MASK                                                                          ((uint32_t)0x000000e0U)

#define MCASP_GBLCTL_RFRST_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_GBLCTL_RFRST_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_GBLCTL_RFRST_RESET                                                                             ((uint32_t)0U)
#define MCASP_GBLCTL_RFRST_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_GBLCTL_RSMRST_SHIFT                                                                            ((uint32_t)3U)
#define MCASP_GBLCTL_RSMRST_MASK                                                                             ((uint32_t)0x00000008U)
#define MCASP_GBLCTL_RSMRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTL_RSMRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTL_RSRCLR_SHIFT                                                                            ((uint32_t)2U)
#define MCASP_GBLCTL_RSRCLR_MASK                                                                             ((uint32_t)0x00000004U)
#define MCASP_GBLCTL_RSRCLR_CLEAR                                                                            ((uint32_t)0U)
#define MCASP_GBLCTL_RSRCLR_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTL_RHCLKRST_SHIFT                                                                          ((uint32_t)1U)
#define MCASP_GBLCTL_RHCLKRST_MASK                                                                           ((uint32_t)0x00000002U)
#define MCASP_GBLCTL_RHCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTL_RHCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_GBLCTL_RCLKRST_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_GBLCTL_RCLKRST_MASK                                                                            ((uint32_t)0x00000001U)
#define MCASP_GBLCTL_RCLKRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTL_RCLKRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_AMUTE_RESERVED_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_AMUTE_RESERVED_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_AMUTE_XDMAERR_SHIFT                                                                            ((uint32_t)12U)
#define MCASP_AMUTE_XDMAERR_MASK                                                                             ((uint32_t)0x00001000U)
#define MCASP_AMUTE_XDMAERR_ENABLE                                                                           ((uint32_t)1U)
#define MCASP_AMUTE_XDMAERR_DISABLE                                                                          ((uint32_t)0U)

#define MCASP_AMUTE_RDMAERR_SHIFT                                                                            ((uint32_t)11U)
#define MCASP_AMUTE_RDMAERR_MASK                                                                             ((uint32_t)0x00000800U)
#define MCASP_AMUTE_RDMAERR_ENABLE                                                                           ((uint32_t)1U)
#define MCASP_AMUTE_RDMAERR_DISABLE                                                                          ((uint32_t)0U)

#define MCASP_AMUTE_XCKFAIL_SHIFT                                                                            ((uint32_t)10U)
#define MCASP_AMUTE_XCKFAIL_MASK                                                                             ((uint32_t)0x00000400U)
#define MCASP_AMUTE_XCKFAIL_ENABLE                                                                           ((uint32_t)1U)
#define MCASP_AMUTE_XCKFAIL_DISABLE                                                                          ((uint32_t)0U)

#define MCASP_AMUTE_RCKFAIL_SHIFT                                                                            ((uint32_t)9U)
#define MCASP_AMUTE_RCKFAIL_MASK                                                                             ((uint32_t)0x00000200U)
#define MCASP_AMUTE_RCKFAIL_ENABLE                                                                           ((uint32_t)1U)
#define MCASP_AMUTE_RCKFAIL_DISABLE                                                                          ((uint32_t)0U)

#define MCASP_AMUTE_XSYNCERR_SHIFT                                                                           ((uint32_t)8U)
#define MCASP_AMUTE_XSYNCERR_MASK                                                                            ((uint32_t)0x00000100U)
#define MCASP_AMUTE_XSYNCERR_ENABLE                                                                          ((uint32_t)1U)
#define MCASP_AMUTE_XSYNCERR_DISABLE                                                                         ((uint32_t)0U)

#define MCASP_AMUTE_RSYNCERR_SHIFT                                                                           ((uint32_t)7U)
#define MCASP_AMUTE_RSYNCERR_MASK                                                                            ((uint32_t)0x00000080U)
#define MCASP_AMUTE_RSYNCERR_ENABLE                                                                          ((uint32_t)1U)
#define MCASP_AMUTE_RSYNCERR_DISABLE                                                                         ((uint32_t)0U)

#define MCASP_AMUTE_XUNDRN_SHIFT                                                                             ((uint32_t)6U)
#define MCASP_AMUTE_XUNDRN_MASK                                                                              ((uint32_t)0x00000040U)
#define MCASP_AMUTE_XUNDRN_ENABLE                                                                            ((uint32_t)1U)
#define MCASP_AMUTE_XUNDRN_DISABLE                                                                           ((uint32_t)0U)

#define MCASP_AMUTE_ROVRN_SHIFT                                                                              ((uint32_t)5U)
#define MCASP_AMUTE_ROVRN_MASK                                                                               ((uint32_t)0x00000020U)
#define MCASP_AMUTE_ROVRN_ENABLE                                                                             ((uint32_t)1U)
#define MCASP_AMUTE_ROVRN_DISABLE                                                                            ((uint32_t)0U)

#define MCASP_AMUTE_INSTAT_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_AMUTE_INSTAT_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_AMUTE_INSTAT_ENABLE                                                                            ((uint32_t)1U)
#define MCASP_AMUTE_INSTAT_DISABLE                                                                           ((uint32_t)0U)

#define MCASP_AMUTE_INEN_SHIFT                                                                               ((uint32_t)3U)
#define MCASP_AMUTE_INEN_MASK                                                                                ((uint32_t)0x0000008U)
#define MCASP_AMUTE_INEN_ENABLE                                                                              ((uint32_t)1U)
#define MCASP_AMUTE_INEN_DISABLE                                                                             ((uint32_t)0U)

#define MCASP_AMUTE_INPOL_SHIFT                                                                              ((uint32_t)2U)
#define MCASP_AMUTE_INPOL_MASK                                                                               ((uint32_t)0x000004U)
#define MCASP_AMUTE_INPOL_HIGH                                                                               ((uint32_t)1U)
#define MCASP_AMUTE_INPOL_LOW                                                                                ((uint32_t)0U)

#define MCASP_AMUTE_MUTEN_SHIFT                                                                              ((uint32_t)0U)
#define MCASP_AMUTE_MUTEN_MASK                                                                               ((uint32_t)0x000003U)
#define MCASP_AMUTE_MUTEN_PIN_DISABLED                                                                       ((uint32_t)0U)
#define MCASP_AMUTE_MUTEN_PIN_HIGH                                                                           ((uint32_t)1U)
#define MCASP_AMUTE_MUTEN_PIN_LOW                                                                            ((uint32_t)2U)

#define MCASP_LBCTL_RESERVED3_SHIFT                                                                          ((uint32_t)5U)
#define MCASP_LBCTL_RESERVED3_MASK                                                                           ((uint32_t)0xffffffe0U)

#define MCASP_LBCTL_IOLBEN_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_LBCTL_IOLBEN_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_LBCTL_IOLBEN_DISABLE                                                                           ((uint32_t)0U)
#define MCASP_LBCTL_IOLBEN_ENABLE                                                                            ((uint32_t)1U)

#define MCASP_LBCTL_MODE_SHIFT                                                                               ((uint32_t)2U)
#define MCASP_LBCTL_MODE_MASK                                                                                ((uint32_t)0x0000000cU)
#define MCASP_LBCTL_MODE_RESERVED                                                                            ((uint32_t)0U)
#define MCASP_LBCTL_MODE_XMTCLK                                                                              ((uint32_t)1U)
#define MCASP_LBCTL_MODE_RESERVED1                                                                           ((uint32_t)2U)
#define MCASP_LBCTL_MODE_RESERVED2                                                                           ((uint32_t)3U)

#define MCASP_LBCTL_ORD_SHIFT                                                                                ((uint32_t)1U)
#define MCASP_LBCTL_ORD_MASK                                                                                 ((uint32_t)0x00000002U)
#define MCASP_LBCTL_ORD_ODD                                                                                  ((uint32_t)0U)
#define MCASP_LBCTL_ORD_EVEN                                                                                 ((uint32_t)1U)

#define MCASP_LBCTL_DLBEN_SHIFT                                                                              ((uint32_t)0U)
#define MCASP_LBCTL_DLBEN_MASK                                                                               ((uint32_t)0x00000001U)
#define MCASP_LBCTL_DLBEN_DISABLE                                                                            ((uint32_t)0U)
#define MCASP_LBCTL_DLBEN_ENABLE                                                                             ((uint32_t)1U)

#define MCASP_TXDITCTL_RESERVED3_SHIFT                                                                       ((uint32_t)4U)
#define MCASP_TXDITCTL_RESERVED3_MASK                                                                        ((uint32_t)0xfffffff0U)

#define MCASP_TXDITCTL_VB_SHIFT                                                                              ((uint32_t)3U)
#define MCASP_TXDITCTL_VB_MASK                                                                               ((uint32_t)0x00000008U)
#define MCASP_TXDITCTL_VB_ZEROSTUFF                                                                          ((uint32_t)0U)
#define MCASP_TXDITCTL_VB_ONESTUFF                                                                           ((uint32_t)1U)

#define MCASP_TXDITCTL_VA_SHIFT                                                                              ((uint32_t)2U)
#define MCASP_TXDITCTL_VA_MASK                                                                               ((uint32_t)0x00000004U)
#define MCASP_TXDITCTL_VA_ZEROSTUFF                                                                          ((uint32_t)0U)
#define MCASP_TXDITCTL_VA_ONESTUFF                                                                           ((uint32_t)1U)

#define MCASP_TXDITCTL_RESERVED4_SHIFT                                                                       ((uint32_t)1U)
#define MCASP_TXDITCTL_RESERVED4_MASK                                                                        ((uint32_t)0x00000002U)

#define MCASP_TXDITCTL_DITEN_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXDITCTL_DITEN_MASK                                                                            ((uint32_t)0x00000001U)
#define MCASP_TXDITCTL_DITEN_DISABLE                                                                         ((uint32_t)0U)
#define MCASP_TXDITCTL_DITEN_ENABLE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLR_RESERVED5_SHIFT                                                                        ((uint32_t)13U)
#define MCASP_GBLCTLR_RESERVED5_MASK                                                                         ((uint32_t)0xffffe000U)

#define MCASP_GBLCTLR_XFRST_SHIFT                                                                            ((uint32_t)12U)
#define MCASP_GBLCTLR_XFRST_MASK                                                                             ((uint32_t)0x00001000U)
#define MCASP_GBLCTLR_XFRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTLR_XFRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTLR_XSMRST_SHIFT                                                                           ((uint32_t)11U)
#define MCASP_GBLCTLR_XSMRST_MASK                                                                            ((uint32_t)0x00000800U)
#define MCASP_GBLCTLR_XSMRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLR_XSMRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLR_XSRCLR_SHIFT                                                                           ((uint32_t)10U)
#define MCASP_GBLCTLR_XSRCLR_MASK                                                                            ((uint32_t)0x00000400U)
#define MCASP_GBLCTLR_XSRCLR_CLEAR                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLR_XSRCLR_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLR_XHCLKRST_SHIFT                                                                         ((uint32_t)9U)
#define MCASP_GBLCTLR_XHCLKRST_MASK                                                                          ((uint32_t)0x00000200U)
#define MCASP_GBLCTLR_XHCLKRST_RESET                                                                         ((uint32_t)0U)
#define MCASP_GBLCTLR_XHCLKRST_ACTIVE                                                                        ((uint32_t)1U)

#define MCASP_GBLCTLR_XCLKRST_SHIFT                                                                          ((uint32_t)8U)
#define MCASP_GBLCTLR_XCLKRST_MASK                                                                           ((uint32_t)0x00000100U)
#define MCASP_GBLCTLR_XCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLR_XCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_GBLCTLR_RESERVED6_SHIFT                                                                        ((uint32_t)5U)
#define MCASP_GBLCTLR_RESERVED6_MASK                                                                         ((uint32_t)0x000000e0U)

#define MCASP_GBLCTLR_RFRST_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_GBLCTLR_RFRST_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_GBLCTLR_RFRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTLR_RFRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTLR_RSMRST_SHIFT                                                                           ((uint32_t)3U)
#define MCASP_GBLCTLR_RSMRST_MASK                                                                            ((uint32_t)0x00000008U)
#define MCASP_GBLCTLR_RSMRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLR_RSMRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLR_RSRCLR_SHIFT                                                                           ((uint32_t)2U)
#define MCASP_GBLCTLR_RSRCLR_MASK                                                                            ((uint32_t)0x00000004U)
#define MCASP_GBLCTLR_RSRCLR_CLEAR                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLR_RSRCLR_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLR_RHCLKRST_SHIFT                                                                         ((uint32_t)1U)
#define MCASP_GBLCTLR_RHCLKRST_MASK                                                                          ((uint32_t)0x00000002U)
#define MCASP_GBLCTLR_RHCLKRST_RESET                                                                         ((uint32_t)0U)
#define MCASP_GBLCTLR_RHCLKRST_ACTIVE                                                                        ((uint32_t)1U)

#define MCASP_GBLCTLR_RCLKRST_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLR_RCLKRST_MASK                                                                           ((uint32_t)0x00000001U)
#define MCASP_GBLCTLR_RCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLR_RCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_RXMASK_RMASK31_SHIFT                                                                           ((uint32_t)31U)
#define MCASP_RXMASK_RMASK31_MASK                                                                            ((uint32_t)0x80000000U)
#define MCASP_RXMASK_RMASK31_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK31_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK30_SHIFT                                                                           ((uint32_t)30U)
#define MCASP_RXMASK_RMASK30_MASK                                                                            ((uint32_t)0x40000000U)
#define MCASP_RXMASK_RMASK30_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK30_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK29_SHIFT                                                                           ((uint32_t)29U)
#define MCASP_RXMASK_RMASK29_MASK                                                                            ((uint32_t)0x20000000U)
#define MCASP_RXMASK_RMASK29_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK29_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK28_SHIFT                                                                           ((uint32_t)28U)
#define MCASP_RXMASK_RMASK28_MASK                                                                            ((uint32_t)0x10000000U)
#define MCASP_RXMASK_RMASK28_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK28_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK27_SHIFT                                                                           ((uint32_t)27U)
#define MCASP_RXMASK_RMASK27_MASK                                                                            ((uint32_t)0x08000000U)
#define MCASP_RXMASK_RMASK27_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK27_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK26_SHIFT                                                                           ((uint32_t)26U)
#define MCASP_RXMASK_RMASK26_MASK                                                                            ((uint32_t)0x04000000U)
#define MCASP_RXMASK_RMASK26_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK26_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK25_SHIFT                                                                           ((uint32_t)25U)
#define MCASP_RXMASK_RMASK25_MASK                                                                            ((uint32_t)0x02000000U)
#define MCASP_RXMASK_RMASK25_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK25_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK24_SHIFT                                                                           ((uint32_t)24U)
#define MCASP_RXMASK_RMASK24_MASK                                                                            ((uint32_t)0x01000000U)
#define MCASP_RXMASK_RMASK24_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK24_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK23_SHIFT                                                                           ((uint32_t)23U)
#define MCASP_RXMASK_RMASK23_MASK                                                                            ((uint32_t)0x00800000U)
#define MCASP_RXMASK_RMASK23_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK23_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK22_SHIFT                                                                           ((uint32_t)22U)
#define MCASP_RXMASK_RMASK22_MASK                                                                            ((uint32_t)0x00400000U)
#define MCASP_RXMASK_RMASK22_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK22_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK21_SHIFT                                                                           ((uint32_t)21U)
#define MCASP_RXMASK_RMASK21_MASK                                                                            ((uint32_t)0x00200000U)
#define MCASP_RXMASK_RMASK21_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK21_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK20_SHIFT                                                                           ((uint32_t)20U)
#define MCASP_RXMASK_RMASK20_MASK                                                                            ((uint32_t)0x00100000U)
#define MCASP_RXMASK_RMASK20_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK20_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK19_SHIFT                                                                           ((uint32_t)19U)
#define MCASP_RXMASK_RMASK19_MASK                                                                            ((uint32_t)0x00080000U)
#define MCASP_RXMASK_RMASK19_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK19_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK18_SHIFT                                                                           ((uint32_t)18U)
#define MCASP_RXMASK_RMASK18_MASK                                                                            ((uint32_t)0x00040000U)
#define MCASP_RXMASK_RMASK18_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK18_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK17_SHIFT                                                                           ((uint32_t)17U)
#define MCASP_RXMASK_RMASK17_MASK                                                                            ((uint32_t)0x00020000U)
#define MCASP_RXMASK_RMASK17_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK17_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK16_SHIFT                                                                           ((uint32_t)16U)
#define MCASP_RXMASK_RMASK16_MASK                                                                            ((uint32_t)0x00010000U)
#define MCASP_RXMASK_RMASK16_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK16_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK15_SHIFT                                                                           ((uint32_t)15U)
#define MCASP_RXMASK_RMASK15_MASK                                                                            ((uint32_t)0x00008000U)
#define MCASP_RXMASK_RMASK15_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK15_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK14_SHIFT                                                                           ((uint32_t)14U)
#define MCASP_RXMASK_RMASK14_MASK                                                                            ((uint32_t)0x00004000U)
#define MCASP_RXMASK_RMASK14_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK14_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK13_SHIFT                                                                           ((uint32_t)13U)
#define MCASP_RXMASK_RMASK13_MASK                                                                            ((uint32_t)0x00002000U)
#define MCASP_RXMASK_RMASK13_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK13_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK12_SHIFT                                                                           ((uint32_t)12U)
#define MCASP_RXMASK_RMASK12_MASK                                                                            ((uint32_t)0x00001000U)
#define MCASP_RXMASK_RMASK12_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK12_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK11_SHIFT                                                                           ((uint32_t)11U)
#define MCASP_RXMASK_RMASK11_MASK                                                                            ((uint32_t)0x00000800U)
#define MCASP_RXMASK_RMASK11_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK11_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK10_SHIFT                                                                           ((uint32_t)10U)
#define MCASP_RXMASK_RMASK10_MASK                                                                            ((uint32_t)0x00000400U)
#define MCASP_RXMASK_RMASK10_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_RXMASK_RMASK10_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_RXMASK_RMASK9_SHIFT                                                                            ((uint32_t)9U)
#define MCASP_RXMASK_RMASK9_MASK                                                                             ((uint32_t)0x00000200U)
#define MCASP_RXMASK_RMASK9_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK9_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK8_SHIFT                                                                            ((uint32_t)8U)
#define MCASP_RXMASK_RMASK8_MASK                                                                             ((uint32_t)0x00000100U)
#define MCASP_RXMASK_RMASK8_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK8_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK7_SHIFT                                                                            ((uint32_t)7U)
#define MCASP_RXMASK_RMASK7_MASK                                                                             ((uint32_t)0x00000080U)
#define MCASP_RXMASK_RMASK7_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK7_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK6_SHIFT                                                                            ((uint32_t)6U)
#define MCASP_RXMASK_RMASK6_MASK                                                                             ((uint32_t)0x00000040U)
#define MCASP_RXMASK_RMASK6_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK6_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK5_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_RXMASK_RMASK5_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_RXMASK_RMASK5_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK5_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK4_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_RXMASK_RMASK4_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_RXMASK_RMASK4_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK4_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK3_SHIFT                                                                            ((uint32_t)3U)
#define MCASP_RXMASK_RMASK3_MASK                                                                             ((uint32_t)0x00000008U)
#define MCASP_RXMASK_RMASK3_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK3_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK2_SHIFT                                                                            ((uint32_t)2U)
#define MCASP_RXMASK_RMASK2_MASK                                                                             ((uint32_t)0x00000004U)
#define MCASP_RXMASK_RMASK2_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK2_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK1_SHIFT                                                                            ((uint32_t)1U)
#define MCASP_RXMASK_RMASK1_MASK                                                                             ((uint32_t)0x00000002U)
#define MCASP_RXMASK_RMASK1_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK1_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXMASK_RMASK0_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_RXMASK_RMASK0_MASK                                                                             ((uint32_t)0x00000001U)
#define MCASP_RXMASK_RMASK0_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_RXMASK_RMASK0_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_RXFMT_RESERVED7_SHIFT                                                                          ((uint32_t)18U)
#define MCASP_RXFMT_RESERVED7_MASK                                                                           ((uint32_t)0xfffc0000U)

#define MCASP_RXFMT_RDATDLY_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_RXFMT_RDATDLY_MASK                                                                             ((uint32_t)0x00030000U)
#define MCASP_RXFMT_RDATDLY_0BIT                                                                             ((uint32_t)0U)
#define MCASP_RXFMT_RDATDLY_1BIT                                                                             ((uint32_t)1U)
#define MCASP_RXFMT_RDATDLY_2BIT                                                                             ((uint32_t)2U)

#define MCASP_RXFMT_RRVRS_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_RXFMT_RRVRS_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_RXFMT_RRVRS_LSBFIRST                                                                           ((uint32_t)0U)
#define MCASP_RXFMT_RRVRS_MSBFIRST                                                                           ((uint32_t)1U)

#define MCASP_RXFMT_RPAD_SHIFT                                                                               ((uint32_t)13U)
#define MCASP_RXFMT_RPAD_MASK                                                                                ((uint32_t)0x00006000U)
#define MCASP_RXFMT_RPAD_ZERO                                                                                ((uint32_t)0U)
#define MCASP_RXFMT_RPAD_ONE                                                                                 ((uint32_t)1U)
#define MCASP_RXFMT_RPAD_RPBIT                                                                               ((uint32_t)2U)

#define MCASP_RXFMT_RPBIT_SHIFT                                                                              ((uint32_t)8U)
#define MCASP_RXFMT_RPBIT_MASK                                                                               ((uint32_t)0x00001f00U)

#define MCASP_RXFMT_RSSZ_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_RXFMT_RSSZ_MASK                                                                                ((uint32_t)0x000000f0U)
#define MCASP_RXFMT_RSSZ_RSV                                                                                 ((uint32_t)0U)
#define MCASP_RXFMT_RSSZ_RSV1                                                                                ((uint32_t)1U)
#define MCASP_RXFMT_RSSZ_RSV2                                                                                ((uint32_t)2U)
#define MCASP_RXFMT_RSSZ_8BITS                                                                               ((uint32_t)3U)
#define MCASP_RXFMT_RSSZ_RSV3                                                                                ((uint32_t)4U)
#define MCASP_RXFMT_RSSZ_12BITS                                                                              ((uint32_t)5U)
#define MCASP_RXFMT_RSSZ_RSV4                                                                                ((uint32_t)6U)
#define MCASP_RXFMT_RSSZ_16BITS                                                                              ((uint32_t)7U)
#define MCASP_RXFMT_RSSZ_RSV5                                                                                ((uint32_t)8U)
#define MCASP_RXFMT_RSSZ_20BITS                                                                              ((uint32_t)9U)
#define MCASP_RXFMT_RSSZ_RSV6                                                                                ((uint32_t)10U)
#define MCASP_RXFMT_RSSZ_24BITS                                                                              ((uint32_t)11U)
#define MCASP_RXFMT_RSSZ_RSV7                                                                                ((uint32_t)12U)
#define MCASP_RXFMT_RSSZ_28BITS                                                                              ((uint32_t)13U)
#define MCASP_RXFMT_RSSZ_RSV8                                                                                ((uint32_t)14U)
#define MCASP_RXFMT_RSSZ_32BITS                                                                              ((uint32_t)15U)

#define MCASP_RXFMT_RBUSEL_SHIFT                                                                             ((uint32_t)3U)
#define MCASP_RXFMT_RBUSEL_MASK                                                                              ((uint32_t)0x00000008U)
#define MCASP_RXFMT_RBUSEL_VBUSP                                                                             ((uint32_t)0U)
#define MCASP_RXFMT_RBUSEL_VBUS                                                                              ((uint32_t)1U)

#define MCASP_RXFMT_RROT_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_RXFMT_RROT_MASK                                                                                ((uint32_t)0x00000007U)
#define MCASP_RXFMT_RROT_NONE                                                                                ((uint32_t)0U)
#define MCASP_RXFMT_RROT_4BITS                                                                               ((uint32_t)1U)
#define MCASP_RXFMT_RROT_8BITS                                                                               ((uint32_t)2U)
#define MCASP_RXFMT_RROT_12BITS                                                                              ((uint32_t)3U)
#define MCASP_RXFMT_RROT_16BITS                                                                              ((uint32_t)4U)
#define MCASP_RXFMT_RROT_20BITS                                                                              ((uint32_t)5U)
#define MCASP_RXFMT_RROT_24BITS                                                                              ((uint32_t)6U)
#define MCASP_RXFMT_RROT_28BITS                                                                              ((uint32_t)7U)

#define MCASP_RXFMCTL_RESERVED8_SHIFT                                                                        ((uint32_t)16U)
#define MCASP_RXFMCTL_RESERVED8_MASK                                                                         ((uint32_t)0xffff0000U)

#define MCASP_RXFMCTL_RMOD_SHIFT                                                                             ((uint32_t)7U)
#define MCASP_RXFMCTL_RMOD_MASK                                                                              ((uint32_t)0x0000ff80U)

#define MCASP_RXFMCTL_RESERVED9_SHIFT                                                                        ((uint32_t)5U)
#define MCASP_RXFMCTL_RESERVED9_MASK                                                                         ((uint32_t)0x00000060U)

#define MCASP_RXFMCTL_FRWID_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_RXFMCTL_FRWID_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_RXFMCTL_FRWID_BIT                                                                              ((uint32_t)0U)
#define MCASP_RXFMCTL_FRWID_WORD                                                                             ((uint32_t)1U)

#define MCASP_RXFMCTL_RESERVED10_SHIFT                                                                       ((uint32_t)2U)
#define MCASP_RXFMCTL_RESERVED10_MASK                                                                        ((uint32_t)0x0000000cU)

#define MCASP_RXFMCTL_FSRM_SHIFT                                                                             ((uint32_t)1U)
#define MCASP_RXFMCTL_FSRM_MASK                                                                              ((uint32_t)0x00000002U)
#define MCASP_RXFMCTL_FSRM_EXTERNAL                                                                          ((uint32_t)0U)
#define MCASP_RXFMCTL_FSRM_INTERNAL                                                                          ((uint32_t)1U)

#define MCASP_RXFMCTL_FSRP_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXFMCTL_FSRP_MASK                                                                              ((uint32_t)0x00000001U)
#define MCASP_RXFMCTL_FSRP_RISINGEDGE                                                                        ((uint32_t)0U)
#define MCASP_RXFMCTL_FSRP_FALLINGEDGE                                                                       ((uint32_t)1U)

#define MCASP_ACLKRCTL_RESERVED11_SHIFT                                                                      ((uint32_t)21U)
#define MCASP_ACLKRCTL_RESERVED11_MASK                                                                       ((uint32_t)0xffe00000U)

#define MCASP_ACLKRCTL_BUSY_SHIFT                                                                            ((uint32_t)20U)
#define MCASP_ACLKRCTL_BUSY_MASK                                                                             ((uint32_t)0x00100000U)
#define MCASP_ACLKRCTL_BUSY_NOTBUSY                                                                          ((uint32_t)0U)
#define MCASP_ACLKRCTL_BUSY_BUSY                                                                             ((uint32_t)1U)

#define MCASP_ACLKRCTL_DIVBUSY_SHIFT                                                                         ((uint32_t)19U)
#define MCASP_ACLKRCTL_DIVBUSY_MASK                                                                          ((uint32_t)0x00080000U)
#define MCASP_ACLKRCTL_DIVBUSY_NOTBUSY                                                                       ((uint32_t)0U)
#define MCASP_ACLKRCTL_DIVBUSY_BUSY                                                                          ((uint32_t)1U)

#define MCASP_ACLKRCTL_ADJBUSY_SHIFT                                                                         ((uint32_t)18U)
#define MCASP_ACLKRCTL_ADJBUSY_MASK                                                                          ((uint32_t)0x00040000U)
#define MCASP_ACLKRCTL_ADJBUSY_NOTBUSY                                                                       ((uint32_t)0U)
#define MCASP_ACLKRCTL_ADJBUSY_BUSY                                                                          ((uint32_t)1U)

#define MCASP_ACLKRCTL_CLKRADJ_SHIFT                                                                         ((uint32_t)16U)
#define MCASP_ACLKRCTL_CLKRADJ_MASK                                                                          ((uint32_t)0x00030000U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSZERO                                                                      ((uint32_t)0U)
#define MCASP_ACLKRCTL_CLKRADJ_MINUSONE                                                                      ((uint32_t)1U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSONE                                                                       ((uint32_t)2U)
#define MCASP_ACLKRCTL_CLKRADJ_PLUSZER0                                                                      ((uint32_t)3U)

#define MCASP_ACLKRCTL_RESERVED12_SHIFT                                                                      ((uint32_t)8U)
#define MCASP_ACLKRCTL_RESERVED12_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MCASP_ACLKRCTL_CLKRP_SHIFT                                                                           ((uint32_t)7U)
#define MCASP_ACLKRCTL_CLKRP_MASK                                                                            ((uint32_t)0x00000080U)
#define MCASP_ACLKRCTL_CLKRP_FALLINGEDGE                                                                     ((uint32_t)0U)
#define MCASP_ACLKRCTL_CLKRP_RISINGEDGE                                                                      ((uint32_t)1U)

#define MCASP_ACLKRCTL_RESERVED13_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_ACLKRCTL_RESERVED13_MASK                                                                       ((uint32_t)0x00000040U)

#define MCASP_ACLKRCTL_CLKRM_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_ACLKRCTL_CLKRM_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_ACLKRCTL_CLKRM_EXTERNAL                                                                        ((uint32_t)0U)
#define MCASP_ACLKRCTL_CLKRM_INTERNAL                                                                        ((uint32_t)1U)

#define MCASP_ACLKRCTL_CLKRDIV_SHIFT                                                                         ((uint32_t)0U)
#define MCASP_ACLKRCTL_CLKRDIV_MASK                                                                          ((uint32_t)0x0000001fU)

#define MCASP_AHCLKRCTL_RESERVED14_SHIFT                                                                     ((uint32_t)21U)
#define MCASP_AHCLKRCTL_RESERVED14_MASK                                                                      ((uint32_t)0xffe00000U)

#define MCASP_AHCLKRCTL_BUSY_SHIFT                                                                           ((uint32_t)20U)
#define MCASP_AHCLKRCTL_BUSY_MASK                                                                            ((uint32_t)0x00100000U)
#define MCASP_AHCLKRCTL_BUSY_NOTBUSY                                                                         ((uint32_t)0U)
#define MCASP_AHCLKRCTL_BUSY_BUSY                                                                            ((uint32_t)1U)

#define MCASP_AHCLKRCTL_DIVBUSY_SHIFT                                                                        ((uint32_t)19U)
#define MCASP_AHCLKRCTL_DIVBUSY_MASK                                                                         ((uint32_t)0x00080000U)
#define MCASP_AHCLKRCTL_DIVBUSY_NOTBUSY                                                                      ((uint32_t)0U)
#define MCASP_AHCLKRCTL_DIVBUSY_BUSY                                                                         ((uint32_t)1U)

#define MCASP_AHCLKRCTL_ADJBUSY_SHIFT                                                                        ((uint32_t)18U)
#define MCASP_AHCLKRCTL_ADJBUSY_MASK                                                                         ((uint32_t)0x00040000U)
#define MCASP_AHCLKRCTL_ADJBUSY_NOTBUSY                                                                      ((uint32_t)0U)
#define MCASP_AHCLKRCTL_ADJBUSY_BUSY                                                                         ((uint32_t)1U)

#define MCASP_AHCLKRCTL_HCLKRADJ_SHIFT                                                                       ((uint32_t)16U)
#define MCASP_AHCLKRCTL_HCLKRADJ_MASK                                                                        ((uint32_t)0x00030000U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSZERO                                                                    ((uint32_t)0U)
#define MCASP_AHCLKRCTL_HCLKRADJ_MINUSONE                                                                    ((uint32_t)1U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSONE                                                                     ((uint32_t)2U)
#define MCASP_AHCLKRCTL_HCLKRADJ_PLUSZER0                                                                    ((uint32_t)3U)

#define MCASP_AHCLKRCTL_HCLKRM_SHIFT                                                                         ((uint32_t)15U)
#define MCASP_AHCLKRCTL_HCLKRM_MASK                                                                          ((uint32_t)0x00008000U)
#define MCASP_AHCLKRCTL_HCLKRM_EXTERNAL                                                                      ((uint32_t)0U)
#define MCASP_AHCLKRCTL_HCLKRM_INTERNAL                                                                      ((uint32_t)1U)

#define MCASP_AHCLKRCTL_HCLKRP_SHIFT                                                                         ((uint32_t)14U)
#define MCASP_AHCLKRCTL_HCLKRP_MASK                                                                          ((uint32_t)0x00004000U)
#define MCASP_AHCLKRCTL_HCLKRP_NOTINVERTED                                                                   ((uint32_t)0U)
#define MCASP_AHCLKRCTL_HCLKRP_INVERTED                                                                      ((uint32_t)1U)

#define MCASP_AHCLKRCTL_RESERVED15_SHIFT                                                                     ((uint32_t)12U)
#define MCASP_AHCLKRCTL_RESERVED15_MASK                                                                      ((uint32_t)0x00003000U)

#define MCASP_AHCLKRCTL_HCLKRDIV_SHIFT                                                                       ((uint32_t)0U)
#define MCASP_AHCLKRCTL_HCLKRDIV_MASK                                                                        ((uint32_t)0x00000fffU)

#define MCASP_RXTDM_RTDMS31_SHIFT                                                                            ((uint32_t)31U)
#define MCASP_RXTDM_RTDMS31_MASK                                                                             ((uint32_t)0x80000000U)
#define MCASP_RXTDM_RTDMS31_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS31_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS30_SHIFT                                                                            ((uint32_t)30U)
#define MCASP_RXTDM_RTDMS30_MASK                                                                             ((uint32_t)0x40000000U)
#define MCASP_RXTDM_RTDMS30_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS30_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS29_SHIFT                                                                            ((uint32_t)29U)
#define MCASP_RXTDM_RTDMS29_MASK                                                                             ((uint32_t)0x20000000U)
#define MCASP_RXTDM_RTDMS29_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS29_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS28_SHIFT                                                                            ((uint32_t)28U)
#define MCASP_RXTDM_RTDMS28_MASK                                                                             ((uint32_t)0x10000000U)
#define MCASP_RXTDM_RTDMS28_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS28_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS27_SHIFT                                                                            ((uint32_t)27U)
#define MCASP_RXTDM_RTDMS27_MASK                                                                             ((uint32_t)0x08000000U)
#define MCASP_RXTDM_RTDMS27_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS27_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS26_SHIFT                                                                            ((uint32_t)26U)
#define MCASP_RXTDM_RTDMS26_MASK                                                                             ((uint32_t)0x04000000U)
#define MCASP_RXTDM_RTDMS26_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS26_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS25_SHIFT                                                                            ((uint32_t)25U)
#define MCASP_RXTDM_RTDMS25_MASK                                                                             ((uint32_t)0x02000000U)
#define MCASP_RXTDM_RTDMS25_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS25_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS24_SHIFT                                                                            ((uint32_t)24U)
#define MCASP_RXTDM_RTDMS24_MASK                                                                             ((uint32_t)0x01000000U)
#define MCASP_RXTDM_RTDMS24_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS24_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS23_SHIFT                                                                            ((uint32_t)23U)
#define MCASP_RXTDM_RTDMS23_MASK                                                                             ((uint32_t)0x00800000U)
#define MCASP_RXTDM_RTDMS23_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS23_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS22_SHIFT                                                                            ((uint32_t)22U)
#define MCASP_RXTDM_RTDMS22_MASK                                                                             ((uint32_t)0x00400000U)
#define MCASP_RXTDM_RTDMS22_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS22_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS21_SHIFT                                                                            ((uint32_t)21U)
#define MCASP_RXTDM_RTDMS21_MASK                                                                             ((uint32_t)0x00200000U)
#define MCASP_RXTDM_RTDMS21_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS21_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS20_SHIFT                                                                            ((uint32_t)20U)
#define MCASP_RXTDM_RTDMS20_MASK                                                                             ((uint32_t)0x00100000U)
#define MCASP_RXTDM_RTDMS20_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS20_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS19_SHIFT                                                                            ((uint32_t)19U)
#define MCASP_RXTDM_RTDMS19_MASK                                                                             ((uint32_t)0x00080000U)
#define MCASP_RXTDM_RTDMS19_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS19_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS18_SHIFT                                                                            ((uint32_t)18U)
#define MCASP_RXTDM_RTDMS18_MASK                                                                             ((uint32_t)0x00040000U)
#define MCASP_RXTDM_RTDMS18_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS18_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS17_SHIFT                                                                            ((uint32_t)17U)
#define MCASP_RXTDM_RTDMS17_MASK                                                                             ((uint32_t)0x00020000U)
#define MCASP_RXTDM_RTDMS17_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS17_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS16_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_RXTDM_RTDMS16_MASK                                                                             ((uint32_t)0x00010000U)
#define MCASP_RXTDM_RTDMS16_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS16_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS15_SHIFT                                                                            ((uint32_t)15U)
#define MCASP_RXTDM_RTDMS15_MASK                                                                             ((uint32_t)0x00008000U)
#define MCASP_RXTDM_RTDMS15_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS15_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS14_SHIFT                                                                            ((uint32_t)14U)
#define MCASP_RXTDM_RTDMS14_MASK                                                                             ((uint32_t)0x00004000U)
#define MCASP_RXTDM_RTDMS14_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS14_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS13_SHIFT                                                                            ((uint32_t)13U)
#define MCASP_RXTDM_RTDMS13_MASK                                                                             ((uint32_t)0x00002000U)
#define MCASP_RXTDM_RTDMS13_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS13_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS12_SHIFT                                                                            ((uint32_t)12U)
#define MCASP_RXTDM_RTDMS12_MASK                                                                             ((uint32_t)0x00001000U)
#define MCASP_RXTDM_RTDMS12_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS12_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS11_SHIFT                                                                            ((uint32_t)11U)
#define MCASP_RXTDM_RTDMS11_MASK                                                                             ((uint32_t)0x00000800U)
#define MCASP_RXTDM_RTDMS11_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS11_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS10_SHIFT                                                                            ((uint32_t)10U)
#define MCASP_RXTDM_RTDMS10_MASK                                                                             ((uint32_t)0x00000400U)
#define MCASP_RXTDM_RTDMS10_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS10_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS9_SHIFT                                                                             ((uint32_t)9U)
#define MCASP_RXTDM_RTDMS9_MASK                                                                              ((uint32_t)0x00000200U)
#define MCASP_RXTDM_RTDMS9_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS9_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS8_SHIFT                                                                             ((uint32_t)8U)
#define MCASP_RXTDM_RTDMS8_MASK                                                                              ((uint32_t)0x00000100U)
#define MCASP_RXTDM_RTDMS8_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS8_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS7_SHIFT                                                                             ((uint32_t)7U)
#define MCASP_RXTDM_RTDMS7_MASK                                                                              ((uint32_t)0x00000080U)
#define MCASP_RXTDM_RTDMS7_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS7_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS6_SHIFT                                                                             ((uint32_t)6U)
#define MCASP_RXTDM_RTDMS6_MASK                                                                              ((uint32_t)0x00000040U)
#define MCASP_RXTDM_RTDMS6_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS6_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS5_SHIFT                                                                             ((uint32_t)5U)
#define MCASP_RXTDM_RTDMS5_MASK                                                                              ((uint32_t)0x00000020U)
#define MCASP_RXTDM_RTDMS5_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS5_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS4_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_RXTDM_RTDMS4_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_RXTDM_RTDMS4_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS4_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS3_SHIFT                                                                             ((uint32_t)3U)
#define MCASP_RXTDM_RTDMS3_MASK                                                                              ((uint32_t)0x00000008U)
#define MCASP_RXTDM_RTDMS3_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS3_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS2_SHIFT                                                                             ((uint32_t)2U)
#define MCASP_RXTDM_RTDMS2_MASK                                                                              ((uint32_t)0x00000004U)
#define MCASP_RXTDM_RTDMS2_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS2_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS1_SHIFT                                                                             ((uint32_t)1U)
#define MCASP_RXTDM_RTDMS1_MASK                                                                              ((uint32_t)0x00000002U)
#define MCASP_RXTDM_RTDMS1_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS1_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_RXTDM_RTDMS0_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS0_MASK                                                                              ((uint32_t)0x00000001U)
#define MCASP_RXTDM_RTDMS0_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_RXTDM_RTDMS0_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_EVTCTLR_RESERVED16_SHIFT                                                                       ((uint32_t)8U)
#define MCASP_EVTCTLR_RESERVED16_MASK                                                                        ((uint32_t)0xffffff00U)

#define MCASP_EVTCTLR_RSTAFRM_SHIFT                                                                          ((uint32_t)7U)
#define MCASP_EVTCTLR_RSTAFRM_MASK                                                                           ((uint32_t)0x00000080U)
#define MCASP_EVTCTLR_RSTAFRM_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLR_RSTAFRM_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLR_RESERVED17_SHIFT                                                                       ((uint32_t)6U)
#define MCASP_EVTCTLR_RESERVED17_MASK                                                                        ((uint32_t)0x00000040U)

#define MCASP_EVTCTLR_RDATA_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_EVTCTLR_RDATA_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_EVTCTLR_RDATA_DISABLE                                                                          ((uint32_t)0U)
#define MCASP_EVTCTLR_RDATA_ENABLE                                                                           ((uint32_t)1U)

#define MCASP_EVTCTLR_RLAST_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_EVTCTLR_RLAST_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_EVTCTLR_RLAST_DISABLE                                                                          ((uint32_t)0U)
#define MCASP_EVTCTLR_RLAST_ENABLE                                                                           ((uint32_t)1U)

#define MCASP_EVTCTLR_RDMAERR_SHIFT                                                                          ((uint32_t)3U)
#define MCASP_EVTCTLR_RDMAERR_MASK                                                                           ((uint32_t)0x00000008U)
#define MCASP_EVTCTLR_RDMAERR_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLR_RDMAERR_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLR_RCKFAIL_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_EVTCTLR_RCKFAIL_MASK                                                                           ((uint32_t)0x00000004U)
#define MCASP_EVTCTLR_RCKFAIL_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLR_RCKFAIL_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLR_RSYNCERR_SHIFT                                                                         ((uint32_t)1U)
#define MCASP_EVTCTLR_RSYNCERR_MASK                                                                          ((uint32_t)0x00000002U)
#define MCASP_EVTCTLR_RSYNCERR_DISABLE                                                                       ((uint32_t)0U)
#define MCASP_EVTCTLR_RSYNCERR_ENABLE                                                                        ((uint32_t)1U)

#define MCASP_EVTCTLR_ROVRN_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_EVTCTLR_ROVRN_MASK                                                                             ((uint32_t)0x00000001U)
#define MCASP_EVTCTLR_ROVRN_DISABLE                                                                          ((uint32_t)0U)
#define MCASP_EVTCTLR_ROVRN_ENABLE                                                                           ((uint32_t)1U)

#define MCASP_RXSTAT_RESERVED18_SHIFT                                                                        ((uint32_t)9U)
#define MCASP_RXSTAT_RESERVED18_MASK                                                                         ((uint32_t)0xfffffe00U)

#define MCASP_RXSTAT_RERR_SHIFT                                                                              ((uint32_t)8U)
#define MCASP_RXSTAT_RERR_MASK                                                                               ((uint32_t)0x00000100U)
#define MCASP_RXSTAT_RERR_NOERROR                                                                            ((uint32_t)0U)
#define MCASP_RXSTAT_RERR_ERROR                                                                              ((uint32_t)1U)

#define MCASP_RXSTAT_RDMAERR_SHIFT                                                                           ((uint32_t)7U)
#define MCASP_RXSTAT_RDMAERR_MASK                                                                            ((uint32_t)0x00000080U)
#define MCASP_RXSTAT_RDMAERR_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_RXSTAT_RDMAERR_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_RXSTAT_RSTAFRM_SHIFT                                                                           ((uint32_t)6U)
#define MCASP_RXSTAT_RSTAFRM_MASK                                                                            ((uint32_t)0x00000040U)
#define MCASP_RXSTAT_RSTAFRM_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_RXSTAT_RSTAFRM_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_RXSTAT_RDATA_SHIFT                                                                             ((uint32_t)5U)
#define MCASP_RXSTAT_RDATA_MASK                                                                              ((uint32_t)0x00000020U)
#define MCASP_RXSTAT_RDATA_NOTOCCUR                                                                          ((uint32_t)0U)
#define MCASP_RXSTAT_RDATA_OCCUR                                                                             ((uint32_t)1U)

#define MCASP_RXSTAT_RLAST_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_RXSTAT_RLAST_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_RXSTAT_RLAST_NOTOCCUR                                                                          ((uint32_t)0U)
#define MCASP_RXSTAT_RLAST_OCCUR                                                                             ((uint32_t)1U)

#define MCASP_RXSTAT_RTDMSLOT_SHIFT                                                                          ((uint32_t)3U)
#define MCASP_RXSTAT_RTDMSLOT_MASK                                                                           ((uint32_t)0x00000008U)
#define MCASP_RXSTAT_RTDMSLOT_ODDSLOT                                                                        ((uint32_t)0U)
#define MCASP_RXSTAT_RTDMSLOT_EVENSLOT                                                                       ((uint32_t)1U)

#define MCASP_RXSTAT_RCKFAIL_SHIFT                                                                           ((uint32_t)2U)
#define MCASP_RXSTAT_RCKFAIL_MASK                                                                            ((uint32_t)0x00000004U)
#define MCASP_RXSTAT_RCKFAIL_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_RXSTAT_RCKFAIL_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_RXSTAT_RSYNCERR_SHIFT                                                                          ((uint32_t)1U)
#define MCASP_RXSTAT_RSYNCERR_MASK                                                                           ((uint32_t)0x00000002U)
#define MCASP_RXSTAT_RSYNCERR_NOTOCCUR                                                                       ((uint32_t)0U)
#define MCASP_RXSTAT_RSYNCERR_OCCUR                                                                          ((uint32_t)1U)

#define MCASP_RXSTAT_ROVRN_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXSTAT_ROVRN_MASK                                                                              ((uint32_t)0x00000001U)
#define MCASP_RXSTAT_ROVRN_NOTOCCUR                                                                          ((uint32_t)0U)
#define MCASP_RXSTAT_ROVRN_OCCUR                                                                             ((uint32_t)1U)

#define MCASP_RXTDMSLOT_RESERVED19_SHIFT                                                                     ((uint32_t)10U)
#define MCASP_RXTDMSLOT_RESERVED19_MASK                                                                      ((uint32_t)0xfffffc00U)

#define MCASP_RXTDMSLOT_RSLOTCNT_SHIFT                                                                       ((uint32_t)0U)
#define MCASP_RXTDMSLOT_RSLOTCNT_MASK                                                                        ((uint32_t)0x000003ffU)

#define MCASP_RXCLKCHK_RCNT_SHIFT                                                                            ((uint32_t)24U)
#define MCASP_RXCLKCHK_RCNT_MASK                                                                             ((uint32_t)0xff000000U)

#define MCASP_RXCLKCHK_RMAX_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_RXCLKCHK_RMAX_MASK                                                                             ((uint32_t)0x00ff0000U)

#define MCASP_RXCLKCHK_RMIN_SHIFT                                                                            ((uint32_t)8U)
#define MCASP_RXCLKCHK_RMIN_MASK                                                                             ((uint32_t)0x0000ff00U)

#define MCASP_RXCLKCHK_RESERVED20_SHIFT                                                                      ((uint32_t)4U)
#define MCASP_RXCLKCHK_RESERVED20_MASK                                                                       ((uint32_t)0x000000f0U)

#define MCASP_RXCLKCHK_RPS_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXCLKCHK_RPS_MASK                                                                              ((uint32_t)0x0000000fU)
#define MCASP_RXCLKCHK_RPS_DIVBY1                                                                            ((uint32_t)0U)
#define MCASP_RXCLKCHK_RPS_DIVBY2                                                                            ((uint32_t)1U)
#define MCASP_RXCLKCHK_RPS_DIVBY4                                                                            ((uint32_t)2U)
#define MCASP_RXCLKCHK_RPS_DIVBY8                                                                            ((uint32_t)3U)
#define MCASP_RXCLKCHK_RPS_DIVBY16                                                                           ((uint32_t)4U)
#define MCASP_RXCLKCHK_RPS_DIVBY32                                                                           ((uint32_t)5U)
#define MCASP_RXCLKCHK_RPS_DIVBY64                                                                           ((uint32_t)6U)
#define MCASP_RXCLKCHK_RPS_DIVBY128                                                                          ((uint32_t)7U)
#define MCASP_RXCLKCHK_RPS_DIVBY256                                                                          ((uint32_t)8U)

#define MCASP_REVTCTL_RESERVED21_SHIFT                                                                       ((uint32_t)1U)
#define MCASP_REVTCTL_RESERVED21_MASK                                                                        ((uint32_t)0xfffffffeU)

#define MCASP_REVTCTL_RDATDMA_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_REVTCTL_RDATDMA_MASK                                                                           ((uint32_t)0x00000001U)
#define MCASP_REVTCTL_RDATDMA_ENABLE                                                                         ((uint32_t)0U)
#define MCASP_REVTCTL_RDATDMA_DISABLE                                                                        ((uint32_t)1U)

#define MCASP_GBLCTLX_RESERVED22_SHIFT                                                                       ((uint32_t)13U)
#define MCASP_GBLCTLX_RESERVED22_MASK                                                                        ((uint32_t)0xffffe000U)

#define MCASP_GBLCTLX_XFRST_SHIFT                                                                            ((uint32_t)12U)
#define MCASP_GBLCTLX_XFRST_MASK                                                                             ((uint32_t)0x00001000U)
#define MCASP_GBLCTLX_XFRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTLX_XFRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTLX_XSMRST_SHIFT                                                                           ((uint32_t)11U)
#define MCASP_GBLCTLX_XSMRST_MASK                                                                            ((uint32_t)0x00000800U)
#define MCASP_GBLCTLX_XSMRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLX_XSMRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLX_XSRCLR_SHIFT                                                                           ((uint32_t)10U)
#define MCASP_GBLCTLX_XSRCLR_MASK                                                                            ((uint32_t)0x00000400U)
#define MCASP_GBLCTLX_XSRCLR_CLEAR                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLX_XSRCLR_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLX_XHCLKRST_SHIFT                                                                         ((uint32_t)9U)
#define MCASP_GBLCTLX_XHCLKRST_MASK                                                                          ((uint32_t)0x00000200U)
#define MCASP_GBLCTLX_XHCLKRST_RESET                                                                         ((uint32_t)0U)
#define MCASP_GBLCTLX_XHCLKRST_ACTIVE                                                                        ((uint32_t)1U)

#define MCASP_GBLCTLX_XCLKRST_SHIFT                                                                          ((uint32_t)8U)
#define MCASP_GBLCTLX_XCLKRST_MASK                                                                           ((uint32_t)0x00000100U)
#define MCASP_GBLCTLX_XCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLX_XCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_GBLCTLX_RESERVED23_SHIFT                                                                       ((uint32_t)5U)
#define MCASP_GBLCTLX_RESERVED23_MASK                                                                        ((uint32_t)0x000000e0U)

#define MCASP_GBLCTLX_RFRST_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_GBLCTLX_RFRST_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_GBLCTLX_RFRST_RESET                                                                            ((uint32_t)0U)
#define MCASP_GBLCTLX_RFRST_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_GBLCTLX_RSMRST_SHIFT                                                                           ((uint32_t)3U)
#define MCASP_GBLCTLX_RSMRST_MASK                                                                            ((uint32_t)0x00000008U)
#define MCASP_GBLCTLX_RSMRST_RESET                                                                           ((uint32_t)0U)
#define MCASP_GBLCTLX_RSMRST_ACTIVE                                                                          ((uint32_t)1U)

#define MCASP_GBLCTLX_RSRCLKR_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_GBLCTLX_RSRCLKR_MASK                                                                           ((uint32_t)0x00000004U)
#define MCASP_GBLCTLX_RSRCLKR_CLEAR                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLX_RSRCLKR_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_GBLCTLX_RHCLKRST_SHIFT                                                                         ((uint32_t)1U)
#define MCASP_GBLCTLX_RHCLKRST_MASK                                                                          ((uint32_t)0x00000002U)
#define MCASP_GBLCTLX_RHCLKRST_RESET                                                                         ((uint32_t)0U)
#define MCASP_GBLCTLX_RHCLKRST_ACTIVE                                                                        ((uint32_t)1U)

#define MCASP_GBLCTLX_RCLKRST_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLX_RCLKRST_MASK                                                                           ((uint32_t)0x00000001U)
#define MCASP_GBLCTLX_RCLKRST_RESET                                                                          ((uint32_t)0U)
#define MCASP_GBLCTLX_RCLKRST_ACTIVE                                                                         ((uint32_t)1U)

#define MCASP_TXMASK_XMASK31_SHIFT                                                                           ((uint32_t)31U)
#define MCASP_TXMASK_XMASK31_MASK                                                                            ((uint32_t)0x80000000U)
#define MCASP_TXMASK_XMASK31_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK31_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK30_SHIFT                                                                           ((uint32_t)30U)
#define MCASP_TXMASK_XMASK30_MASK                                                                            ((uint32_t)0x40000000U)
#define MCASP_TXMASK_XMASK30_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK30_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK29_SHIFT                                                                           ((uint32_t)29U)
#define MCASP_TXMASK_XMASK29_MASK                                                                            ((uint32_t)0x20000000U)
#define MCASP_TXMASK_XMASK29_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK29_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK28_SHIFT                                                                           ((uint32_t)28U)
#define MCASP_TXMASK_XMASK28_MASK                                                                            ((uint32_t)0x10000000U)
#define MCASP_TXMASK_XMASK28_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK28_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK27_SHIFT                                                                           ((uint32_t)27U)
#define MCASP_TXMASK_XMASK27_MASK                                                                            ((uint32_t)0x08000000U)
#define MCASP_TXMASK_XMASK27_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK27_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK26_SHIFT                                                                           ((uint32_t)26U)
#define MCASP_TXMASK_XMASK26_MASK                                                                            ((uint32_t)0x04000000U)
#define MCASP_TXMASK_XMASK26_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK26_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK25_SHIFT                                                                           ((uint32_t)25U)
#define MCASP_TXMASK_XMASK25_MASK                                                                            ((uint32_t)0x02000000U)
#define MCASP_TXMASK_XMASK25_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK25_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK24_SHIFT                                                                           ((uint32_t)24U)
#define MCASP_TXMASK_XMASK24_MASK                                                                            ((uint32_t)0x01000000U)
#define MCASP_TXMASK_XMASK24_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK24_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK23_SHIFT                                                                           ((uint32_t)23U)
#define MCASP_TXMASK_XMASK23_MASK                                                                            ((uint32_t)0x00800000U)
#define MCASP_TXMASK_XMASK23_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK23_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK22_SHIFT                                                                           ((uint32_t)22U)
#define MCASP_TXMASK_XMASK22_MASK                                                                            ((uint32_t)0x00400000U)
#define MCASP_TXMASK_XMASK22_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK22_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK21_SHIFT                                                                           ((uint32_t)21U)
#define MCASP_TXMASK_XMASK21_MASK                                                                            ((uint32_t)0x00200000U)
#define MCASP_TXMASK_XMASK21_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK21_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK20_SHIFT                                                                           ((uint32_t)20U)
#define MCASP_TXMASK_XMASK20_MASK                                                                            ((uint32_t)0x00100000U)
#define MCASP_TXMASK_XMASK20_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK20_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK19_SHIFT                                                                           ((uint32_t)19U)
#define MCASP_TXMASK_XMASK19_MASK                                                                            ((uint32_t)0x00080000U)
#define MCASP_TXMASK_XMASK19_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK19_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK18_SHIFT                                                                           ((uint32_t)18U)
#define MCASP_TXMASK_XMASK18_MASK                                                                            ((uint32_t)0x00040000U)
#define MCASP_TXMASK_XMASK18_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK18_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK17_SHIFT                                                                           ((uint32_t)17U)
#define MCASP_TXMASK_XMASK17_MASK                                                                            ((uint32_t)0x00020000U)
#define MCASP_TXMASK_XMASK17_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK17_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK16_SHIFT                                                                           ((uint32_t)16U)
#define MCASP_TXMASK_XMASK16_MASK                                                                            ((uint32_t)0x00010000U)
#define MCASP_TXMASK_XMASK16_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK16_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK15_SHIFT                                                                           ((uint32_t)15U)
#define MCASP_TXMASK_XMASK15_MASK                                                                            ((uint32_t)0x00008000U)
#define MCASP_TXMASK_XMASK15_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK15_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK14_SHIFT                                                                           ((uint32_t)14U)
#define MCASP_TXMASK_XMASK14_MASK                                                                            ((uint32_t)0x00004000U)
#define MCASP_TXMASK_XMASK14_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK14_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK13_SHIFT                                                                           ((uint32_t)13U)
#define MCASP_TXMASK_XMASK13_MASK                                                                            ((uint32_t)0x00002000U)
#define MCASP_TXMASK_XMASK13_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK13_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK12_SHIFT                                                                           ((uint32_t)12U)
#define MCASP_TXMASK_XMASK12_MASK                                                                            ((uint32_t)0x00001000U)
#define MCASP_TXMASK_XMASK12_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK12_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK11_SHIFT                                                                           ((uint32_t)11U)
#define MCASP_TXMASK_XMASK11_MASK                                                                            ((uint32_t)0x00000800U)
#define MCASP_TXMASK_XMASK11_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK11_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK10_SHIFT                                                                           ((uint32_t)10U)
#define MCASP_TXMASK_XMASK10_MASK                                                                            ((uint32_t)0x00000400U)
#define MCASP_TXMASK_XMASK10_USEMASK                                                                         ((uint32_t)0U)
#define MCASP_TXMASK_XMASK10_NOMASK                                                                          ((uint32_t)1U)

#define MCASP_TXMASK_XMASK9_SHIFT                                                                            ((uint32_t)9U)
#define MCASP_TXMASK_XMASK9_MASK                                                                             ((uint32_t)0x00000200U)
#define MCASP_TXMASK_XMASK9_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK9_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK8_SHIFT                                                                            ((uint32_t)8U)
#define MCASP_TXMASK_XMASK8_MASK                                                                             ((uint32_t)0x00000100U)
#define MCASP_TXMASK_XMASK8_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK8_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK7_SHIFT                                                                            ((uint32_t)7U)
#define MCASP_TXMASK_XMASK7_MASK                                                                             ((uint32_t)0x00000080U)
#define MCASP_TXMASK_XMASK7_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK7_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK6_SHIFT                                                                            ((uint32_t)6U)
#define MCASP_TXMASK_XMASK6_MASK                                                                             ((uint32_t)0x00000040U)
#define MCASP_TXMASK_XMASK6_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK6_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK5_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_TXMASK_XMASK5_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_TXMASK_XMASK5_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK5_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK4_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_TXMASK_XMASK4_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_TXMASK_XMASK4_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK4_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK3_SHIFT                                                                            ((uint32_t)3U)
#define MCASP_TXMASK_XMASK3_MASK                                                                             ((uint32_t)0x00000008U)
#define MCASP_TXMASK_XMASK3_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK3_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK2_SHIFT                                                                            ((uint32_t)2U)
#define MCASP_TXMASK_XMASK2_MASK                                                                             ((uint32_t)0x00000004U)
#define MCASP_TXMASK_XMASK2_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK2_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK1_SHIFT                                                                            ((uint32_t)1U)
#define MCASP_TXMASK_XMASK1_MASK                                                                             ((uint32_t)0x00000002U)
#define MCASP_TXMASK_XMASK1_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK1_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXMASK_XMASK0_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_TXMASK_XMASK0_MASK                                                                             ((uint32_t)0x00000001U)
#define MCASP_TXMASK_XMASK0_USEMASK                                                                          ((uint32_t)0U)
#define MCASP_TXMASK_XMASK0_NOMASK                                                                           ((uint32_t)1U)

#define MCASP_TXFMT_RESERVED24_SHIFT                                                                         ((uint32_t)18U)
#define MCASP_TXFMT_RESERVED24_MASK                                                                          ((uint32_t)0xfffc0000U)

#define MCASP_TXFMT_XDATDLY_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_TXFMT_XDATDLY_MASK                                                                             ((uint32_t)0x00030000U)
#define MCASP_TXFMT_XDATDLY_0BIT                                                                             ((uint32_t)0U)
#define MCASP_TXFMT_XDATDLY_1BIT                                                                             ((uint32_t)1U)
#define MCASP_TXFMT_XDATDLY_2BIT                                                                             ((uint32_t)2U)

#define MCASP_TXFMT_XRVRS_SHIFT                                                                              ((uint32_t)15U)
#define MCASP_TXFMT_XRVRS_MASK                                                                               ((uint32_t)0x00008000U)
#define MCASP_TXFMT_XRVRS_LSBFIRST                                                                           ((uint32_t)0U)
#define MCASP_TXFMT_XRVRS_MSBFIRST                                                                           ((uint32_t)1U)

#define MCASP_TXFMT_XPAD_SHIFT                                                                               ((uint32_t)13U)
#define MCASP_TXFMT_XPAD_MASK                                                                                ((uint32_t)0x00006000U)
#define MCASP_TXFMT_XPAD_ZERO                                                                                ((uint32_t)0U)
#define MCASP_TXFMT_XPAD_ONE                                                                                 ((uint32_t)1U)
#define MCASP_TXFMT_XPAD_XPBIT                                                                               ((uint32_t)2U)

#define MCASP_TXFMT_XPBIT_SHIFT                                                                              ((uint32_t)8U)
#define MCASP_TXFMT_XPBIT_MASK                                                                               ((uint32_t)0x00001f00U)

#define MCASP_TXFMT_XSSZ_SHIFT                                                                               ((uint32_t)4U)
#define MCASP_TXFMT_XSSZ_MASK                                                                                ((uint32_t)0x000000f0U)
#define MCASP_TXFMT_XSSZ_RSV                                                                                 ((uint32_t)0U)
#define MCASP_TXFMT_XSSZ_RSV1                                                                                ((uint32_t)1U)
#define MCASP_TXFMT_XSSZ_RSV2                                                                                ((uint32_t)2U)
#define MCASP_TXFMT_XSSZ_8BITS                                                                               ((uint32_t)3U)
#define MCASP_TXFMT_XSSZ_RSV3                                                                                ((uint32_t)4U)
#define MCASP_TXFMT_XSSZ_12BITS                                                                              ((uint32_t)5U)
#define MCASP_TXFMT_XSSZ_RSV4                                                                                ((uint32_t)6U)
#define MCASP_TXFMT_XSSZ_16BITS                                                                              ((uint32_t)7U)
#define MCASP_TXFMT_XSSZ_RSV5                                                                                ((uint32_t)8U)
#define MCASP_TXFMT_XSSZ_20BITS                                                                              ((uint32_t)9U)
#define MCASP_TXFMT_XSSZ_RSV6                                                                                ((uint32_t)10U)
#define MCASP_TXFMT_XSSZ_24BITS                                                                              ((uint32_t)11U)
#define MCASP_TXFMT_XSSZ_RSV7                                                                                ((uint32_t)12U)
#define MCASP_TXFMT_XSSZ_28BITS                                                                              ((uint32_t)13U)
#define MCASP_TXFMT_XSSZ_RSV8                                                                                ((uint32_t)14U)
#define MCASP_TXFMT_XSSZ_32BITS                                                                              ((uint32_t)15U)

#define MCASP_TXFMT_XBUSEL_SHIFT                                                                             ((uint32_t)3U)
#define MCASP_TXFMT_XBUSEL_MASK                                                                              ((uint32_t)0x00000008U)
#define MCASP_TXFMT_XBUSEL_VBUSP                                                                             ((uint32_t)0U)
#define MCASP_TXFMT_XBUSEL_VBUS                                                                              ((uint32_t)1U)

#define MCASP_TXFMT_XROT_SHIFT                                                                               ((uint32_t)0U)
#define MCASP_TXFMT_XROT_MASK                                                                                ((uint32_t)0x00000007U)
#define MCASP_TXFMT_XROT_NONE                                                                                ((uint32_t)0U)
#define MCASP_TXFMT_XROT_4BITS                                                                               ((uint32_t)1U)
#define MCASP_TXFMT_XROT_8BITS                                                                               ((uint32_t)2U)
#define MCASP_TXFMT_XROT_12BITS                                                                              ((uint32_t)3U)
#define MCASP_TXFMT_XROT_16BITS                                                                              ((uint32_t)4U)
#define MCASP_TXFMT_XROT_20BITS                                                                              ((uint32_t)5U)
#define MCASP_TXFMT_XROT_24BITS                                                                              ((uint32_t)6U)
#define MCASP_TXFMT_XROT_28BITS                                                                              ((uint32_t)7U)

#define MCASP_TXFMCTL_RESERVED25_SHIFT                                                                       ((uint32_t)16U)
#define MCASP_TXFMCTL_RESERVED25_MASK                                                                        ((uint32_t)0xffff0000U)

#define MCASP_TXFMCTL_XMOD_SHIFT                                                                             ((uint32_t)7U)
#define MCASP_TXFMCTL_XMOD_MASK                                                                              ((uint32_t)0x0000ff80U)

#define MCASP_TXFMCTL_RESERVED26_SHIFT                                                                       ((uint32_t)5U)
#define MCASP_TXFMCTL_RESERVED26_MASK                                                                        ((uint32_t)0x00000060U)

#define MCASP_TXFMCTL_FXWID_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_TXFMCTL_FXWID_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_TXFMCTL_FXWID_BIT                                                                              ((uint32_t)0U)
#define MCASP_TXFMCTL_FXWID_WORD                                                                             ((uint32_t)1U)

#define MCASP_TXFMCTL_RESERVED27_SHIFT                                                                       ((uint32_t)2U)
#define MCASP_TXFMCTL_RESERVED27_MASK                                                                        ((uint32_t)0x0000000cU)

#define MCASP_TXFMCTL_FSXM_SHIFT                                                                             ((uint32_t)1U)
#define MCASP_TXFMCTL_FSXM_MASK                                                                              ((uint32_t)0x00000002U)
#define MCASP_TXFMCTL_FSXM_EXTERNAL                                                                          ((uint32_t)0U)
#define MCASP_TXFMCTL_FSXM_INTERNAL                                                                          ((uint32_t)1U)

#define MCASP_TXFMCTL_FSXP_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXFMCTL_FSXP_MASK                                                                              ((uint32_t)0x00000001U)
#define MCASP_TXFMCTL_FSXP_RISINGEDGE                                                                        ((uint32_t)0U)
#define MCASP_TXFMCTL_FSXP_FALLINGEDGE                                                                       ((uint32_t)1U)

#define MCASP_ACLKXCTL_RESERVED28_SHIFT                                                                      ((uint32_t)21U)
#define MCASP_ACLKXCTL_RESERVED28_MASK                                                                       ((uint32_t)0xffe00000U)

#define MCASP_ACLKXCTL_BUSY_SHIFT                                                                            ((uint32_t)20U)
#define MCASP_ACLKXCTL_BUSY_MASK                                                                             ((uint32_t)0x00100000U)
#define MCASP_ACLKXCTL_BUSY_NOTBUSY                                                                          ((uint32_t)0U)
#define MCASP_ACLKXCTL_BUSY_BUSY                                                                             ((uint32_t)1U)

#define MCASP_ACLKXCTL_DIVBUSY_SHIFT                                                                         ((uint32_t)19U)
#define MCASP_ACLKXCTL_DIVBUSY_MASK                                                                          ((uint32_t)0x00080000U)
#define MCASP_ACLKXCTL_DIVBUSY_NOTBUSY                                                                       ((uint32_t)0U)
#define MCASP_ACLKXCTL_DIVBUSY_BUSY                                                                          ((uint32_t)1U)

#define MCASP_ACLKXCTL_ADJBUSY_SHIFT                                                                         ((uint32_t)18U)
#define MCASP_ACLKXCTL_ADJBUSY_MASK                                                                          ((uint32_t)0x00040000U)
#define MCASP_ACLKXCTL_ADJBUSY_NOTBUSY                                                                       ((uint32_t)0U)
#define MCASP_ACLKXCTL_ADJBUSY_BUSY                                                                          ((uint32_t)1U)

#define MCASP_ACLKXCTL_CLKXADJ_SHIFT                                                                         ((uint32_t)16U)
#define MCASP_ACLKXCTL_CLKXADJ_MASK                                                                          ((uint32_t)0x00030000U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSZERO                                                                      ((uint32_t)0U)
#define MCASP_ACLKXCTL_CLKXADJ_MINUSONE                                                                      ((uint32_t)1U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSONE                                                                       ((uint32_t)2U)
#define MCASP_ACLKXCTL_CLKXADJ_PLUSZER0                                                                      ((uint32_t)3U)

#define MCASP_ACLKXCTL_RESERVED29_SHIFT                                                                      ((uint32_t)8U)
#define MCASP_ACLKXCTL_RESERVED29_MASK                                                                       ((uint32_t)0x0000ff00U)

#define MCASP_ACLKXCTL_CLKXP_SHIFT                                                                           ((uint32_t)7U)
#define MCASP_ACLKXCTL_CLKXP_MASK                                                                            ((uint32_t)0x00000080U)
#define MCASP_ACLKXCTL_CLKXP_RISINGEDGE                                                                      ((uint32_t)0U)
#define MCASP_ACLKXCTL_CLKXP_FALLINGEDGE                                                                     ((uint32_t)1U)

#define MCASP_ACLKXCTL_ASYNC_SHIFT                                                                           ((uint32_t)6U)
#define MCASP_ACLKXCTL_ASYNC_MASK                                                                            ((uint32_t)0x00000040U)
#define MCASP_ACLKXCTL_ASYNC_SYNC                                                                            ((uint32_t)0U)
#define MCASP_ACLKXCTL_ASYNC_ASYNC                                                                           ((uint32_t)1U)

#define MCASP_ACLKXCTL_CLKXM_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_ACLKXCTL_CLKXM_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_ACLKXCTL_CLKXM_EXTERNAL                                                                        ((uint32_t)0U)
#define MCASP_ACLKXCTL_CLKXM_INTERNAL                                                                        ((uint32_t)1U)

#define MCASP_ACLKXCTL_CLKXDIV_SHIFT                                                                         ((uint32_t)0U)
#define MCASP_ACLKXCTL_CLKXDIV_MASK                                                                          ((uint32_t)0x0000001fU)

#define MCASP_AHCLKXCTL_RESERVED30_SHIFT                                                                     ((uint32_t)21U)
#define MCASP_AHCLKXCTL_RESERVED30_MASK                                                                      ((uint32_t)0xffe00000U)

#define MCASP_AHCLKXCTL_BUSY_SHIFT                                                                           ((uint32_t)20U)
#define MCASP_AHCLKXCTL_BUSY_MASK                                                                            ((uint32_t)0x00100000U)
#define MCASP_AHCLKXCTL_BUSY_NOTBUSY                                                                         ((uint32_t)0U)
#define MCASP_AHCLKXCTL_BUSY_BUSY                                                                            ((uint32_t)1U)

#define MCASP_AHCLKXCTL_DIVBUSY_SHIFT                                                                        ((uint32_t)19U)
#define MCASP_AHCLKXCTL_DIVBUSY_MASK                                                                         ((uint32_t)0x00080000U)
#define MCASP_AHCLKXCTL_DIVBUSY_NOTBUSY                                                                      ((uint32_t)0U)
#define MCASP_AHCLKXCTL_DIVBUSY_BUSY                                                                         ((uint32_t)1U)

#define MCASP_AHCLKXCTL_ADJBUSY_SHIFT                                                                        ((uint32_t)18U)
#define MCASP_AHCLKXCTL_ADJBUSY_MASK                                                                         ((uint32_t)0x00040000U)
#define MCASP_AHCLKXCTL_ADJBUSY_NOTBUSY                                                                      ((uint32_t)0U)
#define MCASP_AHCLKXCTL_ADJBUSY_BUSY                                                                         ((uint32_t)1U)

#define MCASP_AHCLKXCTL_HCLKXADJ_SHIFT                                                                       ((uint32_t)16U)
#define MCASP_AHCLKXCTL_HCLKXADJ_MASK                                                                        ((uint32_t)0x00030000U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSZERO                                                                    ((uint32_t)0U)
#define MCASP_AHCLKXCTL_HCLKXADJ_MINUSONE                                                                    ((uint32_t)1U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSONE                                                                     ((uint32_t)2U)
#define MCASP_AHCLKXCTL_HCLKXADJ_PLUSZER0                                                                    ((uint32_t)3U)

#define MCASP_AHCLKXCTL_HCLKXM_SHIFT                                                                         ((uint32_t)15U)
#define MCASP_AHCLKXCTL_HCLKXM_MASK                                                                          ((uint32_t)0x00008000U)
#define MCASP_AHCLKXCTL_HCLKXM_EXTERNAL                                                                      ((uint32_t)0U)
#define MCASP_AHCLKXCTL_HCLKXM_INTERNAL                                                                      ((uint32_t)1U)

#define MCASP_AHCLKXCTL_HCLKXP_SHIFT                                                                         ((uint32_t)14U)
#define MCASP_AHCLKXCTL_HCLKXP_MASK                                                                          ((uint32_t)0x00004000U)
#define MCASP_AHCLKXCTL_HCLKXP_NOTINVERTED                                                                   ((uint32_t)0U)
#define MCASP_AHCLKXCTL_HCLKXP_INVERTED                                                                      ((uint32_t)1U)

#define MCASP_AHCLKXCTL_RESERVED31_SHIFT                                                                     ((uint32_t)12U)
#define MCASP_AHCLKXCTL_RESERVED31_MASK                                                                      ((uint32_t)0x00003000U)

#define MCASP_AHCLKXCTL_HCLKXDIV_SHIFT                                                                       ((uint32_t)0U)
#define MCASP_AHCLKXCTL_HCLKXDIV_MASK                                                                        ((uint32_t)0x00000fffU)

#define MCASP_TXTDM_XTDMS31_SHIFT                                                                            ((uint32_t)31U)
#define MCASP_TXTDM_XTDMS31_MASK                                                                             ((uint32_t)0x80000000U)
#define MCASP_TXTDM_XTDMS31_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS31_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS30_SHIFT                                                                            ((uint32_t)30U)
#define MCASP_TXTDM_XTDMS30_MASK                                                                             ((uint32_t)0x40000000U)
#define MCASP_TXTDM_XTDMS30_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS30_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS29_SHIFT                                                                            ((uint32_t)29U)
#define MCASP_TXTDM_XTDMS29_MASK                                                                             ((uint32_t)0x20000000U)
#define MCASP_TXTDM_XTDMS29_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS29_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS28_SHIFT                                                                            ((uint32_t)28U)
#define MCASP_TXTDM_XTDMS28_MASK                                                                             ((uint32_t)0x10000000U)
#define MCASP_TXTDM_XTDMS28_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS28_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS27_SHIFT                                                                            ((uint32_t)27U)
#define MCASP_TXTDM_XTDMS27_MASK                                                                             ((uint32_t)0x08000000U)
#define MCASP_TXTDM_XTDMS27_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS27_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS26_SHIFT                                                                            ((uint32_t)26U)
#define MCASP_TXTDM_XTDMS26_MASK                                                                             ((uint32_t)0x04000000U)
#define MCASP_TXTDM_XTDMS26_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS26_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS25_SHIFT                                                                            ((uint32_t)25U)
#define MCASP_TXTDM_XTDMS25_MASK                                                                             ((uint32_t)0x02000000U)
#define MCASP_TXTDM_XTDMS25_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS25_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS24_SHIFT                                                                            ((uint32_t)24U)
#define MCASP_TXTDM_XTDMS24_MASK                                                                             ((uint32_t)0x01000000U)
#define MCASP_TXTDM_XTDMS24_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS24_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS23_SHIFT                                                                            ((uint32_t)23U)
#define MCASP_TXTDM_XTDMS23_MASK                                                                             ((uint32_t)0x00800000U)
#define MCASP_TXTDM_XTDMS23_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS23_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS22_SHIFT                                                                            ((uint32_t)22U)
#define MCASP_TXTDM_XTDMS22_MASK                                                                             ((uint32_t)0x00400000U)
#define MCASP_TXTDM_XTDMS22_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS22_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS21_SHIFT                                                                            ((uint32_t)21U)
#define MCASP_TXTDM_XTDMS21_MASK                                                                             ((uint32_t)0x00200000U)
#define MCASP_TXTDM_XTDMS21_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS21_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS20_SHIFT                                                                            ((uint32_t)20U)
#define MCASP_TXTDM_XTDMS20_MASK                                                                             ((uint32_t)0x00100000U)
#define MCASP_TXTDM_XTDMS20_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS20_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS19_SHIFT                                                                            ((uint32_t)19U)
#define MCASP_TXTDM_XTDMS19_MASK                                                                             ((uint32_t)0x00080000U)
#define MCASP_TXTDM_XTDMS19_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS19_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS18_SHIFT                                                                            ((uint32_t)18U)
#define MCASP_TXTDM_XTDMS18_MASK                                                                             ((uint32_t)0x00040000U)
#define MCASP_TXTDM_XTDMS18_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS18_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS17_SHIFT                                                                            ((uint32_t)17U)
#define MCASP_TXTDM_XTDMS17_MASK                                                                             ((uint32_t)0x00020000U)
#define MCASP_TXTDM_XTDMS17_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS17_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS16_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_TXTDM_XTDMS16_MASK                                                                             ((uint32_t)0x00010000U)
#define MCASP_TXTDM_XTDMS16_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS16_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS15_SHIFT                                                                            ((uint32_t)15U)
#define MCASP_TXTDM_XTDMS15_MASK                                                                             ((uint32_t)0x00008000U)
#define MCASP_TXTDM_XTDMS15_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS15_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS14_SHIFT                                                                            ((uint32_t)14U)
#define MCASP_TXTDM_XTDMS14_MASK                                                                             ((uint32_t)0x00004000U)
#define MCASP_TXTDM_XTDMS14_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS14_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS13_SHIFT                                                                            ((uint32_t)13U)
#define MCASP_TXTDM_XTDMS13_MASK                                                                             ((uint32_t)0x00002000U)
#define MCASP_TXTDM_XTDMS13_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS13_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS12_SHIFT                                                                            ((uint32_t)12U)
#define MCASP_TXTDM_XTDMS12_MASK                                                                             ((uint32_t)0x00001000U)
#define MCASP_TXTDM_XTDMS12_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS12_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS11_SHIFT                                                                            ((uint32_t)11U)
#define MCASP_TXTDM_XTDMS11_MASK                                                                             ((uint32_t)0x00000800U)
#define MCASP_TXTDM_XTDMS11_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS11_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS10_SHIFT                                                                            ((uint32_t)10U)
#define MCASP_TXTDM_XTDMS10_MASK                                                                             ((uint32_t)0x00000400U)
#define MCASP_TXTDM_XTDMS10_INACTIVE                                                                         ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS10_ACTIVE                                                                           ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS9_SHIFT                                                                             ((uint32_t)9U)
#define MCASP_TXTDM_XTDMS9_MASK                                                                              ((uint32_t)0x00000200U)
#define MCASP_TXTDM_XTDMS9_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS9_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS8_SHIFT                                                                             ((uint32_t)8U)
#define MCASP_TXTDM_XTDMS8_MASK                                                                              ((uint32_t)0x00000100U)
#define MCASP_TXTDM_XTDMS8_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS8_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS7_SHIFT                                                                             ((uint32_t)7U)
#define MCASP_TXTDM_XTDMS7_MASK                                                                              ((uint32_t)0x00000080U)
#define MCASP_TXTDM_XTDMS7_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS7_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS6_SHIFT                                                                             ((uint32_t)6U)
#define MCASP_TXTDM_XTDMS6_MASK                                                                              ((uint32_t)0x00000040U)
#define MCASP_TXTDM_XTDMS6_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS6_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS5_SHIFT                                                                             ((uint32_t)5U)
#define MCASP_TXTDM_XTDMS5_MASK                                                                              ((uint32_t)0x00000020U)
#define MCASP_TXTDM_XTDMS5_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS5_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS4_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_TXTDM_XTDMS4_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_TXTDM_XTDMS4_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS4_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS3_SHIFT                                                                             ((uint32_t)3U)
#define MCASP_TXTDM_XTDMS3_MASK                                                                              ((uint32_t)0x00000008U)
#define MCASP_TXTDM_XTDMS3_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS3_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS2_SHIFT                                                                             ((uint32_t)2U)
#define MCASP_TXTDM_XTDMS2_MASK                                                                              ((uint32_t)0x00000004U)
#define MCASP_TXTDM_XTDMS2_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS2_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS1_SHIFT                                                                             ((uint32_t)1U)
#define MCASP_TXTDM_XTDMS1_MASK                                                                              ((uint32_t)0x00000002U)
#define MCASP_TXTDM_XTDMS1_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS1_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_TXTDM_XTDMS0_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS0_MASK                                                                              ((uint32_t)0x00000001U)
#define MCASP_TXTDM_XTDMS0_INACTIVE                                                                          ((uint32_t)0U)
#define MCASP_TXTDM_XTDMS0_ACTIVE                                                                            ((uint32_t)1U)

#define MCASP_EVTCTLX_RESERVED32_SHIFT                                                                       ((uint32_t)8U)
#define MCASP_EVTCTLX_RESERVED32_MASK                                                                        ((uint32_t)0xffffff00U)

#define MCASP_EVTCTLX_XSTAFRM_SHIFT                                                                          ((uint32_t)7U)
#define MCASP_EVTCTLX_XSTAFRM_MASK                                                                           ((uint32_t)0x00000080U)
#define MCASP_EVTCTLX_XSTAFRM_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLX_XSTAFRM_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLX_RESERVED33_SHIFT                                                                       ((uint32_t)6U)
#define MCASP_EVTCTLX_RESERVED33_MASK                                                                        ((uint32_t)0x00000040U)

#define MCASP_EVTCTLX_XDATA_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_EVTCTLX_XDATA_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_EVTCTLX_XDATA_DISABLE                                                                          ((uint32_t)0U)
#define MCASP_EVTCTLX_XDATA_ENABLE                                                                           ((uint32_t)1U)

#define MCASP_EVTCTLX_XLAST_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_EVTCTLX_XLAST_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_EVTCTLX_XLAST_DISABLE                                                                          ((uint32_t)0U)
#define MCASP_EVTCTLX_XLAST_ENABLE                                                                           ((uint32_t)1U)

#define MCASP_EVTCTLX_XDMAERR_SHIFT                                                                          ((uint32_t)3U)
#define MCASP_EVTCTLX_XDMAERR_MASK                                                                           ((uint32_t)0x00000008U)
#define MCASP_EVTCTLX_XDMAERR_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLX_XDMAERR_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLX_XCKFAIL_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_EVTCTLX_XCKFAIL_MASK                                                                           ((uint32_t)0x00000004U)
#define MCASP_EVTCTLX_XCKFAIL_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_EVTCTLX_XCKFAIL_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_EVTCTLX_XSYNCERR_SHIFT                                                                         ((uint32_t)1U)
#define MCASP_EVTCTLX_XSYNCERR_MASK                                                                          ((uint32_t)0x00000002U)
#define MCASP_EVTCTLX_XSYNCERR_DISABLE                                                                       ((uint32_t)0U)
#define MCASP_EVTCTLX_XSYNCERR_ENABLE                                                                        ((uint32_t)1U)

#define MCASP_EVTCTLX_XUNDRN_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_EVTCTLX_XUNDRN_MASK                                                                            ((uint32_t)0x00000001U)
#define MCASP_EVTCTLX_XUNDRN_DISABLE                                                                         ((uint32_t)0U)
#define MCASP_EVTCTLX_XUNDRN_ENABLE                                                                          ((uint32_t)1U)

#define MCASP_TXSTAT_RESERVED34_SHIFT                                                                        ((uint32_t)9U)
#define MCASP_TXSTAT_RESERVED34_MASK                                                                         ((uint32_t)0xfffffe00U)

#define MCASP_TXSTAT_XERR_SHIFT                                                                              ((uint32_t)8U)
#define MCASP_TXSTAT_XERR_MASK                                                                               ((uint32_t)0x00000100U)
#define MCASP_TXSTAT_XERR_NOERROR                                                                            ((uint32_t)0U)
#define MCASP_TXSTAT_XERR_ERROR                                                                              ((uint32_t)1U)

#define MCASP_TXSTAT_XDMAERR_SHIFT                                                                           ((uint32_t)7U)
#define MCASP_TXSTAT_XDMAERR_MASK                                                                            ((uint32_t)0x00000080U)
#define MCASP_TXSTAT_XDMAERR_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_TXSTAT_XDMAERR_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_TXSTAT_XSTAFRM_SHIFT                                                                           ((uint32_t)6U)
#define MCASP_TXSTAT_XSTAFRM_MASK                                                                            ((uint32_t)0x00000040U)
#define MCASP_TXSTAT_XSTAFRM_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_TXSTAT_XSTAFRM_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_TXSTAT_XDATA_SHIFT                                                                             ((uint32_t)5U)
#define MCASP_TXSTAT_XDATA_MASK                                                                              ((uint32_t)0x00000020U)
#define MCASP_TXSTAT_XDATA_NOTOCCUR                                                                          ((uint32_t)0U)
#define MCASP_TXSTAT_XDATA_OCCUR                                                                             ((uint32_t)1U)

#define MCASP_TXSTAT_XLAST_SHIFT                                                                             ((uint32_t)4U)
#define MCASP_TXSTAT_XLAST_MASK                                                                              ((uint32_t)0x00000010U)
#define MCASP_TXSTAT_XLAST_NOTOCCUR                                                                          ((uint32_t)0U)
#define MCASP_TXSTAT_XLAST_OCCUR                                                                             ((uint32_t)1U)

#define MCASP_TXSTAT_XTDMSLOT_SHIFT                                                                          ((uint32_t)3U)
#define MCASP_TXSTAT_XTDMSLOT_MASK                                                                           ((uint32_t)0x00000008U)
#define MCASP_TXSTAT_XTDMSLOT_ODDSLOT                                                                        ((uint32_t)0U)
#define MCASP_TXSTAT_XTDMSLOT_EVENSLOT                                                                       ((uint32_t)1U)

#define MCASP_TXSTAT_XCKFAIL_SHIFT                                                                           ((uint32_t)2U)
#define MCASP_TXSTAT_XCKFAIL_MASK                                                                            ((uint32_t)0x00000004U)
#define MCASP_TXSTAT_XCKFAIL_NOTOCCUR                                                                        ((uint32_t)0U)
#define MCASP_TXSTAT_XCKFAIL_OCCUR                                                                           ((uint32_t)1U)

#define MCASP_TXSTAT_XSYNCERR_SHIFT                                                                          ((uint32_t)1U)
#define MCASP_TXSTAT_XSYNCERR_MASK                                                                           ((uint32_t)0x00000002U)
#define MCASP_TXSTAT_XSYNCERR_NOTOCCUR                                                                       ((uint32_t)0U)
#define MCASP_TXSTAT_XSYNCERR_OCCUR                                                                          ((uint32_t)1U)

#define MCASP_TXSTAT_XUNDRN_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_TXSTAT_XUNDRN_MASK                                                                             ((uint32_t)0x00000001U)
#define MCASP_TXSTAT_XUNDRN_NOTOCCUR                                                                         ((uint32_t)0U)
#define MCASP_TXSTAT_XUNDRN_OCCUR                                                                            ((uint32_t)1U)

#define MCASP_TXTDMSLOT_RESERVED35_SHIFT                                                                     ((uint32_t)10U)
#define MCASP_TXTDMSLOT_RESERVED35_MASK                                                                      ((uint32_t)0xfffffc00U)

#define MCASP_TXTDMSLOT_XSLOTCNT_SHIFT                                                                       ((uint32_t)0U)
#define MCASP_TXTDMSLOT_XSLOTCNT_MASK                                                                        ((uint32_t)0x000003ffU)

#define MCASP_TXCLKCHK_XCNT_SHIFT                                                                            ((uint32_t)24U)
#define MCASP_TXCLKCHK_XCNT_MASK                                                                             ((uint32_t)0xff000000U)

#define MCASP_TXCLKCHK_XMAX_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_TXCLKCHK_XMAX_MASK                                                                             ((uint32_t)0x00ff0000U)

#define MCASP_TXCLKCHK_XMIN_SHIFT                                                                            ((uint32_t)8U)
#define MCASP_TXCLKCHK_XMIN_MASK                                                                             ((uint32_t)0x0000ff00U)

#define MCASP_TXCLKCHK_RESV_SHIFT                                                                            ((uint32_t)7U)
#define MCASP_TXCLKCHK_RESV_MASK                                                                             ((uint32_t)0x00000080U)

#define MCASP_TXCLKCHK_RESERVED36_SHIFT                                                                      ((uint32_t)4U)
#define MCASP_TXCLKCHK_RESERVED36_MASK                                                                       ((uint32_t)0x00000070U)

#define MCASP_TXCLKCHK_XPS_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXCLKCHK_XPS_MASK                                                                              ((uint32_t)0x0000000fU)
#define MCASP_TXCLKCHK_XPS_DIVBY1                                                                            ((uint32_t)0U)
#define MCASP_TXCLKCHK_XPS_DIVBY2                                                                            ((uint32_t)1U)
#define MCASP_TXCLKCHK_XPS_DIVBY4                                                                            ((uint32_t)2U)
#define MCASP_TXCLKCHK_XPS_DIVBY8                                                                            ((uint32_t)3U)
#define MCASP_TXCLKCHK_XPS_DIVBY16                                                                           ((uint32_t)4U)
#define MCASP_TXCLKCHK_XPS_DIVBY32                                                                           ((uint32_t)5U)
#define MCASP_TXCLKCHK_XPS_DIVBY64                                                                           ((uint32_t)6U)
#define MCASP_TXCLKCHK_XPS_DIVBY128                                                                          ((uint32_t)7U)
#define MCASP_TXCLKCHK_XPS_DIVBY256                                                                          ((uint32_t)8U)

#define MCASP_XEVTCTL_RESERVED37_SHIFT                                                                       ((uint32_t)1U)
#define MCASP_XEVTCTL_RESERVED37_MASK                                                                        ((uint32_t)0xfffffffeU)

#define MCASP_XEVTCTL_XDATDMA_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XEVTCTL_XDATDMA_MASK                                                                           ((uint32_t)0x00000001U)
#define MCASP_XEVTCTL_XDATDMA_ENABLE                                                                         ((uint32_t)0U)
#define MCASP_XEVTCTL_XDATDMA_DISABLE                                                                        ((uint32_t)1U)

#define MCASP_CLKADJEN_RESERVED38_SHIFT                                                                      ((uint32_t)1U)
#define MCASP_CLKADJEN_RESERVED38_MASK                                                                       ((uint32_t)0xfffffffeU)

#define MCASP_CLKADJEN_ENABLE_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_CLKADJEN_ENABLE_MASK                                                                           ((uint32_t)0x00000001U)
#define MCASP_CLKADJEN_ENABLE_DISABLE                                                                        ((uint32_t)0U)
#define MCASP_CLKADJEN_ENABLE_ENABLE                                                                         ((uint32_t)1U)

#define MCASP_DITCSRA0_DITCSRA0_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA0_DITCSRA0_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRA1_DITCSRA1_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA1_DITCSRA1_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRA2_DITCSRA2_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA2_DITCSRA2_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRA3_DITCSRA3_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA3_DITCSRA3_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRA4_DITCSRA4_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA4_DITCSRA4_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRA5_DITCSRA5_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRA5_DITCSRA5_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB0_DITCSRB0_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB0_DITCSRB0_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB1_DITCSRB1_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB1_DITCSRB1_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB2_DITCSRB2_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB2_DITCSRB2_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB3_DITCSRB3_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB3_DITCSRB3_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB4_DITCSRB4_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB4_DITCSRB4_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITCSRB5_DITCSRB5_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITCSRB5_DITCSRB5_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA0_DITUDRA0_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA0_DITUDRA0_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA1_DITUDRA1_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA1_DITUDRA1_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA2_DITUDRA2_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA2_DITUDRA2_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA3_DITUDRA3_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA3_DITUDRA3_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA4_DITUDRA4_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA4_DITUDRA4_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRA5_DITUDRA5_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRA5_DITUDRA5_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB0_DITUDRB0_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB0_DITUDRB0_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB1_DITUDRB1_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB1_DITUDRB1_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB2_DITUDRB2_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB2_DITUDRB2_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB3_DITUDRB3_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB3_DITUDRB3_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB4_DITUDRB4_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB4_DITUDRB4_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_DITUDRB5_DITUDRB5_SHIFT                                                                        ((uint32_t)0U)
#define MCASP_DITUDRB5_DITUDRB5_MASK                                                                         ((uint32_t)0xffffffffU)

#define MCASP_XRSRCTL0_RESERVED39_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL0_RESERVED39_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL0_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL0_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL0_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL0_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL0_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL0_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL0_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL0_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL0_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL0_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL0_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL0_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL0_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL0_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL0_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL0_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL0_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL0_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL0_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL1_RESERVED40_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL1_RESERVED40_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL1_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL1_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL1_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL1_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL1_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL1_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL1_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL1_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL1_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL1_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL1_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL1_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL1_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL1_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL1_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL1_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL1_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL1_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL1_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL2_RESERVED41_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL2_RESERVED41_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL2_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL2_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL2_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL2_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL2_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL2_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL2_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL2_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL2_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL2_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL2_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL2_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL2_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL2_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL2_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL2_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL2_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL2_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL2_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL3_RESERVED42_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL3_RESERVED42_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL3_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL3_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL3_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL3_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL3_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL3_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL3_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL3_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL3_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL3_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL3_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL3_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL3_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL3_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL3_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL3_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL3_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL3_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL3_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL4_RESERVED43_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL4_RESERVED43_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL4_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL4_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL4_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL4_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL4_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL4_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL4_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL4_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL4_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL4_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL4_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL4_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL4_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL4_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL4_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL4_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL4_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL4_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL4_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL5_RESERVED44_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL5_RESERVED44_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL5_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL5_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL5_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL5_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL5_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL5_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL5_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL5_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL5_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL5_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL5_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL5_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL5_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL5_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL5_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL5_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL5_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL5_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL5_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL6_RESERVED45_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL6_RESERVED45_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL6_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL6_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL6_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL6_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL6_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL6_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL6_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL6_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL6_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL6_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL6_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL6_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL6_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL6_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL6_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL6_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL6_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL6_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL6_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL7_RESERVED46_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL7_RESERVED46_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL7_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL7_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL7_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL7_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL7_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL7_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL7_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL7_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL7_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL7_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL7_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL7_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL7_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL7_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL7_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL7_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL7_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL7_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL7_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL8_RESERVED47_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL8_RESERVED47_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL8_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL8_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL8_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL8_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL8_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL8_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL8_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL8_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL8_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL8_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL8_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL8_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL8_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL8_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL8_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL8_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL8_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL8_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL8_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL9_RESERVED48_SHIFT                                                                      ((uint32_t)6U)
#define MCASP_XRSRCTL9_RESERVED48_MASK                                                                       ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL9_RRDY_SHIFT                                                                            ((uint32_t)5U)
#define MCASP_XRSRCTL9_RRDY_MASK                                                                             ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL9_RRDY_EMPTY                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL9_RRDY_DATA                                                                             ((uint32_t)1U)

#define MCASP_XRSRCTL9_XRDY_SHIFT                                                                            ((uint32_t)4U)
#define MCASP_XRSRCTL9_XRDY_MASK                                                                             ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL9_XRDY_DATA                                                                             ((uint32_t)0U)
#define MCASP_XRSRCTL9_XRDY_EMPTY                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL9_DISMOD_SHIFT                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL9_DISMOD_MASK                                                                           ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL9_DISMOD_TRI                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL9_DISMOD_RSV                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL9_DISMOD_DRV0                                                                           ((uint32_t)2U)
#define MCASP_XRSRCTL9_DISMOD_DRV1                                                                           ((uint32_t)3U)

#define MCASP_XRSRCTL9_SRMOD_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL9_SRMOD_MASK                                                                            ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL9_SRMOD_INACTIVE                                                                        ((uint32_t)0U)
#define MCASP_XRSRCTL9_SRMOD_XMT                                                                             ((uint32_t)1U)
#define MCASP_XRSRCTL9_SRMOD_RCV                                                                             ((uint32_t)2U)

#define MCASP_XRSRCTL10_RESERVED49_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL10_RESERVED49_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL10_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL10_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL10_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL10_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL10_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL10_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL10_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL10_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL10_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL10_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL10_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL10_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL10_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL10_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL10_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL10_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL10_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL10_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL10_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_XRSRCTL11_RESERVED50_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL11_RESERVED50_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL11_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL11_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL11_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL11_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL11_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL11_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL11_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL11_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL11_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL11_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL11_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL11_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL11_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL11_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL11_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL11_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL11_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL11_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL11_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_XRSRCTL12_RESERVED51_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL12_RESERVED51_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL12_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL12_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL12_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL12_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL12_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL12_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL12_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL12_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL12_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL12_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL12_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL12_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL12_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL12_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL12_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL12_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL12_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL12_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL12_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_XRSRCTL13_RESERVED52_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL13_RESERVED52_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL13_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL13_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL13_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL13_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL13_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL13_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL13_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL13_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL13_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL13_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL13_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL13_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL13_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL13_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL13_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL13_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL13_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL13_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL13_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_XRSRCTL14_RESERVED53_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL14_RESERVED53_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL14_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL14_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL14_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL14_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL14_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL14_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL14_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL14_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL14_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL14_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL14_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL14_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL14_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL14_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL14_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL14_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL14_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL14_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL14_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_XRSRCTL15_RESERVED54_SHIFT                                                                     ((uint32_t)6U)
#define MCASP_XRSRCTL15_RESERVED54_MASK                                                                      ((uint32_t)0xffffffc0U)

#define MCASP_XRSRCTL15_RRDY_SHIFT                                                                           ((uint32_t)5U)
#define MCASP_XRSRCTL15_RRDY_MASK                                                                            ((uint32_t)0x00000020U)
#define MCASP_XRSRCTL15_RRDY_EMPTY                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL15_RRDY_DATA                                                                            ((uint32_t)1U)

#define MCASP_XRSRCTL15_XRDY_SHIFT                                                                           ((uint32_t)4U)
#define MCASP_XRSRCTL15_XRDY_MASK                                                                            ((uint32_t)0x00000010U)
#define MCASP_XRSRCTL15_XRDY_DATA                                                                            ((uint32_t)0U)
#define MCASP_XRSRCTL15_XRDY_EMPTY                                                                           ((uint32_t)1U)

#define MCASP_XRSRCTL15_DISMOD_SHIFT                                                                         ((uint32_t)2U)
#define MCASP_XRSRCTL15_DISMOD_MASK                                                                          ((uint32_t)0x0000000cU)
#define MCASP_XRSRCTL15_DISMOD_TRI                                                                           ((uint32_t)0U)
#define MCASP_XRSRCTL15_DISMOD_RSV                                                                           ((uint32_t)1U)
#define MCASP_XRSRCTL15_DISMOD_DRV0                                                                          ((uint32_t)2U)
#define MCASP_XRSRCTL15_DISMOD_DRV1                                                                          ((uint32_t)3U)

#define MCASP_XRSRCTL15_SRMOD_SHIFT                                                                          ((uint32_t)0U)
#define MCASP_XRSRCTL15_SRMOD_MASK                                                                           ((uint32_t)0x00000003U)
#define MCASP_XRSRCTL15_SRMOD_INACTIVE                                                                       ((uint32_t)0U)
#define MCASP_XRSRCTL15_SRMOD_XMT                                                                            ((uint32_t)1U)
#define MCASP_XRSRCTL15_SRMOD_RCV                                                                            ((uint32_t)2U)

#define MCASP_TXBUF0_XBUF0_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF0_XBUF0_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF1_XBUF1_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF1_XBUF1_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF2_XBUF2_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF2_XBUF2_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF3_XBUF3_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF3_XBUF3_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF4_XBUF4_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF4_XBUF4_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF5_XBUF5_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF5_XBUF5_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF6_XBUF6_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF6_XBUF6_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF7_XBUF7_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF7_XBUF7_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF8_XBUF8_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF8_XBUF8_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF9_XBUF9_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_TXBUF9_XBUF9_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_TXBUF10_XBUF10_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF10_XBUF10_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_TXBUF11_XBUF11_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF11_XBUF11_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_TXBUF12_XBUF12_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF12_XBUF12_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_TXBUF13_XBUF13_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF13_XBUF13_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_TXBUF14_XBUF14_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF14_XBUF14_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_TXBUF15_XBUF15_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_TXBUF15_XBUF15_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF0_RBUF0_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF0_RBUF0_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF1_RBUF1_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF1_RBUF1_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF2_RBUF2_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF2_RBUF2_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF3_RBUF3_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF3_RBUF3_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF4_RBUF4_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF4_RBUF4_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF5_RBUF5_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF5_RBUF5_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF6_RBUF6_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF6_RBUF6_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF7_RBUF7_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF7_RBUF7_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF8_RBUF8_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF8_RBUF8_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF9_RBUF9_SHIFT                                                                             ((uint32_t)0U)
#define MCASP_RXBUF9_RBUF9_MASK                                                                              ((uint32_t)0xffffffffU)

#define MCASP_RXBUF10_RBUF10_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF10_RBUF10_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF11_RBUF11_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF11_RBUF11_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF12_RBUF12_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF12_RBUF12_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF13_RBUF13_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF13_RBUF13_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF14_RBUF14_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF14_RBUF14_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_RXBUF15_RBUF15_SHIFT                                                                           ((uint32_t)0U)
#define MCASP_RXBUF15_RBUF15_MASK                                                                            ((uint32_t)0xffffffffU)

#define MCASP_WFIFOCTL_WNUMDMA_SHIFT                                                                         ((uint32_t)0U)
#define MCASP_WFIFOCTL_WNUMDMA_MASK                                                                          ((uint32_t)0x000000ffU)

#define MCASP_WFIFOCTL_WNUMEVT_SHIFT                                                                         ((uint32_t)8U)
#define MCASP_WFIFOCTL_WNUMEVT_MASK                                                                          ((uint32_t)0x0000ff00U)

#define MCASP_WFIFOCTL_WENA_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_WFIFOCTL_WENA_MASK                                                                             ((uint32_t)0x00010000U)

#define MCASP_WFIFOCTL_RESERVED_SHIFT                                                                        ((uint32_t)17U)
#define MCASP_WFIFOCTL_RESERVED_MASK                                                                         ((uint32_t)0xfffe0000U)

#define MCASP_RFIFOCTL_RNUMDMA_SHIFT                                                                         ((uint32_t)0U)
#define MCASP_RFIFOCTL_RNUMDMA_MASK                                                                          ((uint32_t)0x000000ffU)

#define MCASP_RFIFOCTL_RNUMEVT_SHIFT                                                                         ((uint32_t)8U)
#define MCASP_RFIFOCTL_RNUMEVT_MASK                                                                          ((uint32_t)0x0000ff00U)

#define MCASP_RFIFOCTL_RENA_SHIFT                                                                            ((uint32_t)16U)
#define MCASP_RFIFOCTL_RENA_MASK                                                                             ((uint32_t)0x00010000U)

#define MCASP_RFIFOCTL_RESERVED_SHIFT                                                                        ((uint32_t)17U)
#define MCASP_RFIFOCTL_RESERVED_MASK                                                                         ((uint32_t)0xfffe0000U)

#define MCASP_WFIFOSTS_WLVL_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_WFIFOSTS_WLVL_MASK                                                                             ((uint32_t)0x000000ffU)

#define MCASP_WFIFOSTS_RESERVED_SHIFT                                                                        ((uint32_t)8U)
#define MCASP_WFIFOSTS_RESERVED_MASK                                                                         ((uint32_t)0xffffff00U)

#define MCASP_RFIFOSTS_RLVL_SHIFT                                                                            ((uint32_t)0U)
#define MCASP_RFIFOSTS_RLVL_MASK                                                                             ((uint32_t)0x000000ffU)

#define MCASP_RFIFOSTS_RESERVED_SHIFT                                                                        ((uint32_t)8U)
#define MCASP_RFIFOSTS_RESERVED_MASK                                                                         ((uint32_t)0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MCASP_H_ */
