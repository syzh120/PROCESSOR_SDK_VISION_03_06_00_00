/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*! ============================================================================
 *   \file  cslr_gmacsw_wr.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for GMAC_SW
 *
 *  ============================================================================
 */

#ifndef CSLR_GMACSW_WR_H_
#define CSLR_GMACSW_WR_H_

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* OS/Posix headers */

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct
{
#if defined(DEVICE_CENTAURUS)
   volatile uint8_t  RSVD0[0x900U];             /* offset since union is used for Centaurus */
#endif
   volatile uint32_t WR_IDVER;                  /* 0x000U */
   volatile uint32_t WR_SOFT_RESET;
   volatile uint32_t WR_CONTROL;
   volatile uint32_t WR_INT_CONTROL;
   volatile uint32_t WR_C0_RX_THRESH_EN;        /* 0x010U */
   volatile uint32_t WR_C0_RX_EN;
   volatile uint32_t WR_C0_TX_EN;
   volatile uint32_t WR_C0_MISC_EN;
   volatile uint8_t  RSVD1[0x20U];              /* 0x020U */
   volatile uint32_t WR_C0_RX_THRESH_STAT;      /* 0x040U */
   volatile uint32_t WR_C0_RX_STAT;
   volatile uint32_t WR_C0_TX_STAT;
   volatile uint32_t WR_C0_MISC_STAT;
   volatile uint8_t  RSVD2[0x20U];              /* 0x050U */
   volatile uint32_t WR_C0_RX_IMAX;             /* 0x070U */
   volatile uint32_t WR_C0_TX_IMAX;
   volatile uint8_t  RSVD3[0x10U];              /* 0x078U */
   volatile uint32_t WR_RGMII_CTL;              /* 0x088U */
   volatile uint8_t  RSVD4[0x74U];              /* 0x08CU */
}
CSL_GMACSW_wrRegs;


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* WR_IDVER */

#define CSL_GMACSW_WR_IDVER_REVISION_MASK       (0xFFFFFFFFU)
#define CSL_GMACSW_WR_IDVER_REVISION_SHIFT      (0x00000000U)
#define CSL_GMACSW_WR_IDVER_REVISION_RESETVAL   (0x001A0101U)

#define CSL_GMACSW_WR_IDVER_RESETVAL (0x001A0101U)


/* WR_SOFT_RESET */

#define CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_MASK (0x00000001U)
#define CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_RESETVAL (0x00000000U)
/*----SOFT_RESET Tokens----*/
#define CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_YES (0x00000001U)
#define CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_NO (0x00000000U)

#define CSL_GMACSW_WR_SOFT_RESET_RESETVAL (0x00000000U)


/* WR_INT_CONTROL */

#define CSL_GMACSW_WR_INT_CONTROL_INT_TEST_MASK (0x80000000U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_TEST_SHIFT (0x0000001FU)
#define CSL_GMACSW_WR_INT_CONTROL_INT_TEST_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_MASK (0x003F0000U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT (0x00000010U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_RESETVAL (0x00000000U)
/*----INT_PACE_EN Tokens----*/
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C0_RX ((uint32_t)0x00000001U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C0_TX ((uint32_t)0x00000002U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C1_RX ((uint32_t)0x00000004U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C1_TX ((uint32_t)0x00000008U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C2_RX ((uint32_t)0x00000010U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PACE_EN_C2_TX ((uint32_t)0x00000020U)


#define CSL_GMACSW_WR_INT_CONTROL_INT_PRESCALE_MASK (0x00000FFFU)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PRESCALE_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_INT_CONTROL_INT_PRESCALE_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_INT_CONTROL_RESETVAL (0x00000000U)


/* WR_C0_RX_THRESH_EN */

#define CSL_GMACSW_WR_C0_RX_THRESH_EN_RX_THRESH_EN_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_RX_THRESH_EN_RX_THRESH_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_RX_THRESH_EN_RX_THRESH_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_RX_THRESH_EN_RESETVAL (0x00000000U)


/* WR_C0_RX_EN */

#define CSL_GMACSW_WR_C0_RX_EN_RX_EN_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_RX_EN_RX_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_RX_EN_RX_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_RX_EN_RESETVAL (0x00000000U)


/* WR_C0_TX_EN */

#define CSL_GMACSW_WR_C0_TX_EN_TX_EN_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_TX_EN_TX_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_TX_EN_TX_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_TX_EN_RESETVAL (0x00000000U)


/* WR_C0_MISC_EN */

#define CSL_GMACSW_WR_C0_MISC_EN_SPF2_PEND_MASK (0x00000040U)
#define CSL_GMACSW_WR_C0_MISC_EN_SPF2_PEND_SHIFT (0x00000006U)
#define CSL_GMACSW_WR_C0_MISC_EN_SPF2_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_SPF1_PEND_MASK (0x00000020U)
#define CSL_GMACSW_WR_C0_MISC_EN_SPF1_PEND_SHIFT (0x00000005U)
#define CSL_GMACSW_WR_C0_MISC_EN_SPF1_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_EVNT_PEND_MASK (0x00000010U)
#define CSL_GMACSW_WR_C0_MISC_EN_EVNT_PEND_SHIFT (0x00000004U)
#define CSL_GMACSW_WR_C0_MISC_EN_EVNT_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_STAT_PEND_MASK (0x00000008U)
#define CSL_GMACSW_WR_C0_MISC_EN_STAT_PEND_SHIFT (0x00000003U)
#define CSL_GMACSW_WR_C0_MISC_EN_STAT_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_HOST_PEND_MASK (0x00000004U)
#define CSL_GMACSW_WR_C0_MISC_EN_HOST_PEND_SHIFT (0x00000002U)
#define CSL_GMACSW_WR_C0_MISC_EN_HOST_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_LINKINT_MASK (0x00000002U)
#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_LINKINT_SHIFT (0x00000001U)
#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_LINKINT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_USERINT_MASK (0x00000001U)
#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_USERINT_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_MISC_EN_MDIO_USERINT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_EN_RESETVAL (0x00000000U)



/* WR_C0_RX_THRESH_STAT */

#define CSL_GMACSW_WR_C0_RX_THRESH_STAT_RX_THRESH_STAT_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_RX_THRESH_STAT_RX_THRESH_STAT_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_RX_THRESH_STAT_RX_THRESH_STAT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_RX_THRESH_STAT_RESETVAL (0x00000000U)


/* WR_C0_RX_STAT */

#define CSL_GMACSW_WR_C0_RX_STAT_RX_STAT_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_RX_STAT_RX_STAT_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_RX_STAT_RX_STAT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_RX_STAT_RESETVAL (0x00000000U)


/* WR_C0_TX_STAT */

#define CSL_GMACSW_WR_C0_TX_STAT_TX_STAT_MASK (0x000000FFU)
#define CSL_GMACSW_WR_C0_TX_STAT_TX_STAT_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_TX_STAT_TX_STAT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_TX_STAT_RESETVAL (0x00000000U)


/* WR_C0_MISC_STAT */

#define CSL_GMACSW_WR_C0_MISC_STAT_SPF2_PEND_MASK (0x00000040U)
#define CSL_GMACSW_WR_C0_MISC_STAT_SPF2_PEND_SHIFT (0x00000006U)
#define CSL_GMACSW_WR_C0_MISC_STAT_SPF2_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_SPF1_PEND_MASK (0x00000020U)
#define CSL_GMACSW_WR_C0_MISC_STAT_SPF1_PEND_SHIFT (0x00000005U)
#define CSL_GMACSW_WR_C0_MISC_STAT_SPF1_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_EVNT_PEND_MASK (0x00000010U)
#define CSL_GMACSW_WR_C0_MISC_STAT_EVNT_PEND_SHIFT (0x00000004U)
#define CSL_GMACSW_WR_C0_MISC_STAT_EVNT_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_STAT_PEND_MASK (0x00000008U)
#define CSL_GMACSW_WR_C0_MISC_STAT_STAT_PEND_SHIFT (0x00000003U)
#define CSL_GMACSW_WR_C0_MISC_STAT_STAT_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_HOST_PEND_MASK (0x00000004U)
#define CSL_GMACSW_WR_C0_MISC_STAT_HOST_PEND_SHIFT (0x00000002U)
#define CSL_GMACSW_WR_C0_MISC_STAT_HOST_PEND_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_LINKINT_MASK (0x00000002U)
#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_LINKINT_SHIFT (0x00000001U)
#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_LINKINT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_USERINT_MASK (0x00000001U)
#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_USERINT_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_MISC_STAT_MDIO_USERINT_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_MISC_STAT_RESETVAL (0x00000000U)


/* WR_C0_RX_IMAX */

#define CSL_GMACSW_WR_C0_RX_IMAX_RX_IMAX_MASK (0x0000003FU)
#define CSL_GMACSW_WR_C0_RX_IMAX_RX_IMAX_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_RX_IMAX_RX_IMAX_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_RX_IMAX_RESETVAL (0x00000000U)


/* WR_C0_TX_IMAX */

#define CSL_GMACSW_WR_C0_TX_IMAX_TX_IMAX_MASK (0x0000003FU)
#define CSL_GMACSW_WR_C0_TX_IMAX_TX_IMAX_SHIFT (0x00000000U)
#define CSL_GMACSW_WR_C0_TX_IMAX_TX_IMAX_RESETVAL (0x00000000U)

#define CSL_GMACSW_WR_C0_TX_IMAX_RESETVAL (0x00000000U)


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CSLR_GMACSW_WR_H_ */

