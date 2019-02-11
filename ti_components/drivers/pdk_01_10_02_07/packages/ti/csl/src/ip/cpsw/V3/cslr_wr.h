/********************************************************************
 * Copyright (C) 2013-2016 Texas Instruments Incorporated.
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
#ifndef CSLR_WR_H_
#define CSLR_WR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for core_int_en
**************************************************************************/
typedef struct {
    volatile Uint32 RX_THRESH_EN;
    volatile Uint32 RX_EN;
    volatile Uint32 TX_EN;
    volatile Uint32 MISC_EN;
} CSL_WrCore_int_enRegs;


/**************************************************************************
* Register Overlay Structure for core_int_stat
**************************************************************************/
typedef struct {
    volatile Uint32 RX_THRESH_STAT;
    volatile Uint32 RX_STAT;
    volatile Uint32 TX_STAT;
    volatile Uint32 MISC_STAT;
} CSL_WrCore_int_statRegs;


/**************************************************************************
* Register Overlay Structure for core_ints_per_ms
**************************************************************************/
typedef struct {
    volatile Uint32 RX_IMAX;
    volatile Uint32 TX_IMAX;
} CSL_WrCore_ints_per_msRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 IDVER;
    volatile Uint32 SOFT_RESET;
    volatile Uint32 CONTROL;
    volatile Uint32 INT_CONTROL;
    CSL_WrCore_int_enRegs	CORE_INT_EN[3];
    CSL_WrCore_int_statRegs	CORE_INT_STAT[3];
    CSL_WrCore_ints_per_msRegs	CORE_INTS_PER_MS[3];
    volatile Uint32 RGMII_CTL;
    volatile Uint32 STATUS;
} CSL_WRRegs;




/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_WR_RX_THRESH_EN(n)                                  ((uint32_t)0x10u + ((n) * ((uint32_t)10u)))
#define CSL_WR_RX_EN(n)                                         ((uint32_t)0x14u + ((n) * ((uint32_t)10u)))
#define CSL_WR_TX_EN(n)                                         ((uint32_t)0x18u + ((n) * ((uint32_t)10u)))
#define CSL_WR_MISC_EN(n)                                       ((uint32_t)0x1Cu + ((n) * ((uint32_t)10u)))
#define CSL_WR_RX_THRESH_STAT(n)                                ((uint32_t)0x40u + ((n) * ((uint32_t)10u)))
#define CSL_WR_RX_STAT(n)                                       ((uint32_t)0x44u + ((n) * ((uint32_t)10u)))
#define CSL_WR_TX_STAT(n)                                       ((uint32_t)0x48u + ((n) * ((uint32_t)10u)))
#define CSL_WR_MISC_STAT(n)                                     ((uint32_t)0x4Cu + ((n) * ((uint32_t)10u)))
#define CSL_WR_RX_IMAX(n)                                       ((uint32_t)0x70u + ((n) * ((uint32_t)8u)))
#define CSL_WR_TX_IMAX(n)                                       ((uint32_t)0x74u + ((n) * ((uint32_t)8u)))
#define CSL_WR_IDVER                                            ((uint32_t)(0x0u))
#define CSL_WR_SOFT_RESET                                       ((uint32_t)(0x4u))
#define CSL_WR_CONTROL                                          ((uint32_t)(0x8u))
#define CSL_WR_INT_CONTROL                                      ((uint32_t)(0xCu))
#define CSL_WR_RGMII_CTL                                        ((uint32_t)(0x88u))
#define CSL_WR_STATUS                                           ((uint32_t)(0x8Cu))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* RX_THRESH_EN */

#define CSL_WR_RX_THRESH_EN_RX_THRESH_EN_SHIFT                  ((uint32_t)(0u))
#define CSL_WR_RX_THRESH_EN_RX_THRESH_EN_MASK                   ((uint32_t)(0x000000FFu))
#define CSL_WR_RX_THRESH_EN_RX_THRESH_EN_RESETVAL               ((uint32_t)(0x00000000u))
#define CSL_WR_RX_THRESH_EN_RX_THRESH_EN_MAX                    ((uint32_t)(0x000000ffu))

#define CSL_WR_RX_THRESH_EN_RESETVAL                            ((uint32_t)(0x00000000u))

/* RX_EN */

#define CSL_WR_RX_EN_RX_EN_SHIFT                                ((uint32_t)(0u))
#define CSL_WR_RX_EN_RX_EN_MASK                                 ((uint32_t)(0x000000FFu))
#define CSL_WR_RX_EN_RX_EN_RESETVAL                             ((uint32_t)(0x00000000u))
#define CSL_WR_RX_EN_RX_EN_MAX                                  ((uint32_t)(0x000000ffu))

#define CSL_WR_RX_EN_RESETVAL                                   ((uint32_t)(0x00000000u))

/* TX_EN */

#define CSL_WR_TX_EN_TX_EN_SHIFT                                ((uint32_t)(0u))
#define CSL_WR_TX_EN_TX_EN_MASK                                 ((uint32_t)(0x000000FFu))
#define CSL_WR_TX_EN_TX_EN_RESETVAL                             ((uint32_t)(0x00000000u))
#define CSL_WR_TX_EN_TX_EN_MAX                                  ((uint32_t)(0x000000ffu))

#define CSL_WR_TX_EN_RESETVAL                                   ((uint32_t)(0x00000000u))

/* MISC_EN */

#define CSL_WR_MISC_EN_MISC_EN_SHIFT                            ((uint32_t)(0u))
#define CSL_WR_MISC_EN_MISC_EN_MASK                             ((uint32_t)(0x0000001Fu))
#define CSL_WR_MISC_EN_MISC_EN_RESETVAL                         ((uint32_t)(0x00000000u))
#define CSL_WR_MISC_EN_MISC_EN_MAX                              ((uint32_t)(0x0000001fu))

#define CSL_WR_MISC_EN_RESETVAL                                 ((uint32_t)(0x00000000u))

/* RX_THRESH_STAT */

#define CSL_WR_RX_THRESH_STAT_RX_THRESH_STAT_SHIFT              ((uint32_t)(0u))
#define CSL_WR_RX_THRESH_STAT_RX_THRESH_STAT_MASK               ((uint32_t)(0x000000FFu))
#define CSL_WR_RX_THRESH_STAT_RX_THRESH_STAT_RESETVAL           ((uint32_t)(0x00000000u))
#define CSL_WR_RX_THRESH_STAT_RX_THRESH_STAT_MAX                ((uint32_t)(0x000000ffu))

#define CSL_WR_RX_THRESH_STAT_RESETVAL                          ((uint32_t)(0x00000000u))

/* RX_STAT */

#define CSL_WR_RX_STAT_RX_STAT_SHIFT                            ((uint32_t)(0u))
#define CSL_WR_RX_STAT_RX_STAT_MASK                             ((uint32_t)(0x000000FFu))
#define CSL_WR_RX_STAT_RX_STAT_RESETVAL                         ((uint32_t)(0x00000000u))
#define CSL_WR_RX_STAT_RX_STAT_MAX                              ((uint32_t)(0x000000ffu))

#define CSL_WR_RX_STAT_RESETVAL                                 ((uint32_t)(0x00000000u))

/* TX_STAT */

#define CSL_WR_TX_STAT_TX_STAT_SHIFT                            ((uint32_t)(0u))
#define CSL_WR_TX_STAT_TX_STAT_MASK                             ((uint32_t)(0x000000FFu))
#define CSL_WR_TX_STAT_TX_STAT_RESETVAL                         ((uint32_t)(0x00000000u))
#define CSL_WR_TX_STAT_TX_STAT_MAX                              ((uint32_t)(0x000000ffu))

#define CSL_WR_TX_STAT_RESETVAL                                 ((uint32_t)(0x00000000u))

/* MISC_STAT */

#define CSL_WR_MISC_STAT_MISC_STAT_SHIFT                        ((uint32_t)(0u))
#define CSL_WR_MISC_STAT_MISC_STAT_MASK                         ((uint32_t)(0x0000001Fu))
#define CSL_WR_MISC_STAT_MISC_STAT_RESETVAL                     ((uint32_t)(0x00000000u))
#define CSL_WR_MISC_STAT_MISC_STAT_MAX                          ((uint32_t)(0x0000001fu))

#define CSL_WR_MISC_STAT_RESETVAL                               ((uint32_t)(0x00000000u))

/* RX_IMAX */

#define CSL_WR_RX_IMAX_RX_IMAX_SHIFT                            ((uint32_t)(0u))
#define CSL_WR_RX_IMAX_RX_IMAX_MASK                             ((uint32_t)(0x0000003Fu))
#define CSL_WR_RX_IMAX_RX_IMAX_RESETVAL                         ((uint32_t)(0x00000000u))
#define CSL_WR_RX_IMAX_RX_IMAX_MAX                              ((uint32_t)(0x0000003fu))

#define CSL_WR_RX_IMAX_RESETVAL                                 ((uint32_t)(0x00000000u))

/* TX_IMAX */

#define CSL_WR_TX_IMAX_TX_IMAX_SHIFT                            ((uint32_t)(0u))
#define CSL_WR_TX_IMAX_TX_IMAX_MASK                             ((uint32_t)(0x0000003Fu))
#define CSL_WR_TX_IMAX_TX_IMAX_RESETVAL                         ((uint32_t)(0x00000000u))
#define CSL_WR_TX_IMAX_TX_IMAX_MAX                              ((uint32_t)(0x0000003fu))

#define CSL_WR_TX_IMAX_RESETVAL                                 ((uint32_t)(0x00000000u))

/* IDVER */

#define CSL_WR_IDVER_MINOR_SHIFT                                ((uint32_t)(0u))
#define CSL_WR_IDVER_MINOR_MASK                                 ((uint32_t)(0x0000003Fu))
#define CSL_WR_IDVER_MINOR_RESETVAL                             ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_MINOR_MAX                                  ((uint32_t)(0x0000003fu))

#define CSL_WR_IDVER_CUSTOM_SHIFT                               ((uint32_t)(6u))
#define CSL_WR_IDVER_CUSTOM_MASK                                ((uint32_t)(0x000000C0u))
#define CSL_WR_IDVER_CUSTOM_RESETVAL                            ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_CUSTOM_MAX                                 ((uint32_t)(0x00000003u))

#define CSL_WR_IDVER_MAJOR_SHIFT                                ((uint32_t)(8u))
#define CSL_WR_IDVER_MAJOR_MASK                                 ((uint32_t)(0x00000700u))
#define CSL_WR_IDVER_MAJOR_RESETVAL                             ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_MAJOR_MAX                                  ((uint32_t)(0x00000007u))

#define CSL_WR_IDVER_RTL_SHIFT                                  ((uint32_t)(11u))
#define CSL_WR_IDVER_RTL_MASK                                   ((uint32_t)(0x0000F800u))
#define CSL_WR_IDVER_RTL_RESETVAL                               ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_RTL_MAX                                    ((uint32_t)(0x0000001fu))

#define CSL_WR_IDVER_FUNCTION_SHIFT                             ((uint32_t)(16u))
#define CSL_WR_IDVER_FUNCTION_MASK                              ((uint32_t)(0x0FFF0000u))
#define CSL_WR_IDVER_FUNCTION_RESETVAL                          ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_FUNCTION_MAX                               ((uint32_t)(0x00000fffu))

#define CSL_WR_IDVER_SCHEME_SHIFT                               ((uint32_t)(30u))
#define CSL_WR_IDVER_SCHEME_MASK                                ((uint32_t)(0xC0000000u))
#define CSL_WR_IDVER_SCHEME_RESETVAL                            ((uint32_t)(0x00000000u))
#define CSL_WR_IDVER_SCHEME_MAX                                 ((uint32_t)(0x00000003u))

#define CSL_WR_IDVER_RESETVAL                                   ((uint32_t)(0x00000000u))

/* SOFT_RESET */

#define CSL_WR_SOFT_RESET_SOFT_RESET_SHIFT                      ((uint32_t)(0u))
#define CSL_WR_SOFT_RESET_SOFT_RESET_MASK                       ((uint32_t)(0x00000001u))
#define CSL_WR_SOFT_RESET_SOFT_RESET_RESETVAL                   ((uint32_t)(0x00000000u))
#define CSL_WR_SOFT_RESET_SOFT_RESET_MAX                        ((uint32_t)(0x00000001u))

#define CSL_WR_SOFT_RESET_RESETVAL                              ((uint32_t)(0x00000000u))

/* CONTROL */

#define CSL_WR_CONTROL_MMR_IDLEMODE_SHIFT                       ((uint32_t)(0u))
#define CSL_WR_CONTROL_MMR_IDLEMODE_MASK                        ((uint32_t)(0x00000003u))
#define CSL_WR_CONTROL_MMR_IDLEMODE_RESETVAL                    ((uint32_t)(0x00000000u))
#define CSL_WR_CONTROL_MMR_IDLEMODE_MAX                         ((uint32_t)(0x00000003u))

#define CSL_WR_CONTROL_MMR_STDBYMODE_SHIFT                      ((uint32_t)(2u))
#define CSL_WR_CONTROL_MMR_STDBYMODE_MASK                       ((uint32_t)(0x0000000Cu))
#define CSL_WR_CONTROL_MMR_STDBYMODE_RESETVAL                   ((uint32_t)(0x00000000u))
#define CSL_WR_CONTROL_MMR_STDBYMODE_MAX                        ((uint32_t)(0x00000003u))

#define CSL_WR_CONTROL_SS_EEE_EN_SHIFT                          ((uint32_t)(8u))
#define CSL_WR_CONTROL_SS_EEE_EN_MASK                           ((uint32_t)(0x00000100u))
#define CSL_WR_CONTROL_SS_EEE_EN_RESETVAL                       ((uint32_t)(0x00000000u))
#define CSL_WR_CONTROL_SS_EEE_EN_MAX                            ((uint32_t)(0x00000001u))

#define CSL_WR_CONTROL_RESETVAL                                 ((uint32_t)(0x00000000u))

/* INT_CONTROL */

#define CSL_WR_INT_CONTROL_INT_PRESCALE_SHIFT                   ((uint32_t)(0u))
#define CSL_WR_INT_CONTROL_INT_PRESCALE_MASK                    ((uint32_t)(0x00000FFFu))
#define CSL_WR_INT_CONTROL_INT_PRESCALE_RESETVAL                ((uint32_t)(0x00000000u))
#define CSL_WR_INT_CONTROL_INT_PRESCALE_MAX                     ((uint32_t)(0x00000fffu))

#define CSL_WR_INT_CONTROL_INT_PACE_EN_SHIFT                    ((uint32_t)(16u))
#define CSL_WR_INT_CONTROL_INT_PACE_EN_MASK                     ((uint32_t)(0x003F0000u))
#define CSL_WR_INT_CONTROL_INT_PACE_EN_RESETVAL                 ((uint32_t)(0x00000000u))
#define CSL_WR_INT_CONTROL_INT_PACE_EN_MAX                      ((uint32_t)(0x0000003fu))

#define CSL_WR_INT_CONTROL_INT_TEST_SHIFT                       ((uint32_t)(31u))
#define CSL_WR_INT_CONTROL_INT_TEST_MASK                        ((uint32_t)(0x80000000u))
#define CSL_WR_INT_CONTROL_INT_TEST_RESETVAL                    ((uint32_t)(0x00000000u))
#define CSL_WR_INT_CONTROL_INT_TEST_MAX                         ((uint32_t)(0x00000001u))

#define CSL_WR_INT_CONTROL_RESETVAL                             ((uint32_t)(0x00000000u))

/* RGMII_CTL */

#define CSL_WR_RGMII_CTL_RGMII1_LINK_SHIFT                      ((uint32_t)(0u))
#define CSL_WR_RGMII_CTL_RGMII1_LINK_MASK                       ((uint32_t)(0x00000001u))
#define CSL_WR_RGMII_CTL_RGMII1_LINK_RESETVAL                   ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII1_LINK_MAX                        ((uint32_t)(0x00000001u))

#define CSL_WR_RGMII_CTL_RGMII1_SPEED_SHIFT                     ((uint32_t)(1u))
#define CSL_WR_RGMII_CTL_RGMII1_SPEED_MASK                      ((uint32_t)(0x00000006u))
#define CSL_WR_RGMII_CTL_RGMII1_SPEED_RESETVAL                  ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII1_SPEED_MAX                       ((uint32_t)(0x00000003u))

#define CSL_WR_RGMII_CTL_RGMII1_FULLDUPLEX_SHIFT                ((uint32_t)(3u))
#define CSL_WR_RGMII_CTL_RGMII1_FULLDUPLEX_MASK                 ((uint32_t)(0x00000008u))
#define CSL_WR_RGMII_CTL_RGMII1_FULLDUPLEX_RESETVAL             ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII1_FULLDUPLEX_MAX                  ((uint32_t)(0x00000001u))

#define CSL_WR_RGMII_CTL_RGMII2_LINK_SHIFT                      ((uint32_t)(4u))
#define CSL_WR_RGMII_CTL_RGMII2_LINK_MASK                       ((uint32_t)(0x00000010u))
#define CSL_WR_RGMII_CTL_RGMII2_LINK_RESETVAL                   ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII2_LINK_MAX                        ((uint32_t)(0x00000001u))

#define CSL_WR_RGMII_CTL_RGMII2_SPEED_SHIFT                     ((uint32_t)(5u))
#define CSL_WR_RGMII_CTL_RGMII2_SPEED_MASK                      ((uint32_t)(0x00000060u))
#define CSL_WR_RGMII_CTL_RGMII2_SPEED_RESETVAL                  ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII2_SPEED_MAX                       ((uint32_t)(0x00000003u))

#define CSL_WR_RGMII_CTL_RGMII2_FULLDUPLEX_SHIFT                ((uint32_t)(7u))
#define CSL_WR_RGMII_CTL_RGMII2_FULLDUPLEX_MASK                 ((uint32_t)(0x00000080u))
#define CSL_WR_RGMII_CTL_RGMII2_FULLDUPLEX_RESETVAL             ((uint32_t)(0x00000000u))
#define CSL_WR_RGMII_CTL_RGMII2_FULLDUPLEX_MAX                  ((uint32_t)(0x00000001u))

#define CSL_WR_RGMII_CTL_RESETVAL                               ((uint32_t)(0x00000000u))

/* STATUS */

#define CSL_WR_STATUS_EEE_CLKSTOP_ACK_SHIFT                     ((uint32_t)(0u))
#define CSL_WR_STATUS_EEE_CLKSTOP_ACK_MASK                      ((uint32_t)(0x00000001u))
#define CSL_WR_STATUS_EEE_CLKSTOP_ACK_RESETVAL                  ((uint32_t)(0x00000000u))
#define CSL_WR_STATUS_EEE_CLKSTOP_ACK_MAX                       ((uint32_t)(0x00000001u))

#define CSL_WR_STATUS_SPF1_CLKSTOP_ACK_SHIFT                    ((uint32_t)(1u))
#define CSL_WR_STATUS_SPF1_CLKSTOP_ACK_MASK                     ((uint32_t)(0x00000002u))
#define CSL_WR_STATUS_SPF1_CLKSTOP_ACK_RESETVAL                 ((uint32_t)(0x00000000u))
#define CSL_WR_STATUS_SPF1_CLKSTOP_ACK_MAX                      ((uint32_t)(0x00000001u))

#define CSL_WR_STATUS_SPF2_CLKSTOP_ACK_SHIFT                    ((uint32_t)(2u))
#define CSL_WR_STATUS_SPF2_CLKSTOP_ACK_MASK                     ((uint32_t)(0x00000004u))
#define CSL_WR_STATUS_SPF2_CLKSTOP_ACK_RESETVAL                 ((uint32_t)(0x00000000u))
#define CSL_WR_STATUS_SPF2_CLKSTOP_ACK_MAX                      ((uint32_t)(0x00000001u))

#define CSL_WR_STATUS_RESETVAL                                  ((uint32_t)(0x00000000u))

#ifdef __cplusplus
}
#endif
#endif
