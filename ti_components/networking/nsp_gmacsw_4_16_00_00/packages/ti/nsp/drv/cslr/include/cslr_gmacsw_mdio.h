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
 *   \file  cslr_gmacsw_mdio.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for GMAC_SW
 *
 *  ============================================================================
 */

#ifndef CSLR_GMACSW_MDIO_H_
#define CSLR_GMACSW_MDIO_H_

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
    volatile uint32_t MDIO_USERACCESS;
    volatile uint32_t MDIO_USERPHYSEL;
}
CSL_GMACSW_mdioUserRegs;

typedef struct
{
#if defined(DEVICE_CENTAURUS)
   volatile uint8_t  RSVD0[0x800U];             /* 0x000U - offset since union is used for Centaurus*/
#endif
    volatile uint32_t MDIO_VER;                 /* 0x000U */
    volatile uint32_t MDIO_CONTROL;
    volatile uint32_t MDIO_ALIVE;
    volatile uint32_t MDIO_LINK;
    volatile uint32_t MDIO_LINKINTRAW;          /* 0x010U */
    volatile uint32_t MDIO_LINKINTMASKED;
    volatile uint8_t  RSVD1[0x08U];
    volatile uint32_t MDIO_USERINTRAW;          /* 0x020U */
    volatile uint32_t MDIO_USERINTMASKED;
    volatile uint32_t MDIO_USERINTMASKSET;
    volatile uint32_t MDIO_USERINTMASKCLR;
    volatile uint8_t  RSVD2[0x50U];             /* 0x030U */
#if (0)
    CSL_GMACSW_mdioUserRegs MDIO_USER[2];       /* 0x080U */
#else
    volatile uint32_t MDIO_USERACCESS0;         /* 0x080U */
    volatile uint32_t MDIO_USERPHYSEL0;
    volatile uint32_t MDIO_USERACCESS1;
    volatile uint32_t MDIO_USERPHYSEL1;
#endif
    volatile uint8_t  RSVD3[0x170U];            /* 0x090U */
}
CSL_GMACSW_mdioRegs;


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Field Definition Macros */

/* MDIO_VER */

#define CSL_GMACSW_MDIO_VER_REVMIN_SHIFT                                                                        (0x00000000U)
#define CSL_GMACSW_MDIO_VER_REVMIN_MASK                                                                         (0x000000FFU)

#define CSL_GMACSW_MDIO_VER_REVMAJ_SHIFT                                                                        (0x00000008U)
#define CSL_GMACSW_MDIO_VER_REVMAJ_MASK                                                                         (0x0000FF00U)

#define CSL_GMACSW_MDIO_VER_MODID_SHIFT                                                                         (0x00000010U)
#define CSL_GMACSW_MDIO_VER_MODID_MASK                                                                          (0xFFFF0000U)


/* MDIO_CONTROL */

#define CSL_GMACSW_MDIO_CONTROL_CLKDIV_SHIFT                                                                    (0x00000000U)
#define CSL_GMACSW_MDIO_CONTROL_CLKDIV_MASK                                                                     (0x0000FFFFU)

#define CSL_GMACSW_MDIO_CONTROL_RESERVED3_SHIFT                                                                 (0x00000010U)
#define CSL_GMACSW_MDIO_CONTROL_RESERVED3_MASK                                                                  (0x00010000U)

#define CSL_GMACSW_MDIO_CONTROL_INTTESTENB_SHIFT                                                                (0x00000011U)
#define CSL_GMACSW_MDIO_CONTROL_INTTESTENB_MASK                                                                 (0x00020000U)

#define CSL_GMACSW_MDIO_CONTROL_FAULTENB_SHIFT                                                                  (0x00000012U)
#define CSL_GMACSW_MDIO_CONTROL_FAULTENB_MASK                                                                   (0x00040000U)

#define CSL_GMACSW_MDIO_CONTROL_FAULT_SHIFT                                                                     (0x00000013U)
#define CSL_GMACSW_MDIO_CONTROL_FAULT_MASK                                                                      (0x00080000U)

#define CSL_GMACSW_MDIO_CONTROL_PREAMBLE_SHIFT                                                                  (0x00000014U)
#define CSL_GMACSW_MDIO_CONTROL_PREAMBLE_MASK                                                                   (0x00100000U)

#define CSL_GMACSW_MDIO_CONTROL_RESERVED2_SHIFT                                                                 (0x00000015U)
#define CSL_GMACSW_MDIO_CONTROL_RESERVED2_MASK                                                                  (0x00E00000U)

#define CSL_GMACSW_MDIO_CONTROL_HIGHEST_USER_CHANNEL_SHIFT                                                      (0x00000018U)
#define CSL_GMACSW_MDIO_CONTROL_HIGHEST_USER_CHANNEL_MASK                                                       (0x1F000000U)

#define CSL_GMACSW_MDIO_CONTROL_RESERVED1_SHIFT                                                                 (0x0000001DU)
#define CSL_GMACSW_MDIO_CONTROL_RESERVED1_MASK                                                                  (0x20000000U)

#define CSL_GMACSW_MDIO_CONTROL_ENABLE_SHIFT                                                                    (0x0000001EU)
#define CSL_GMACSW_MDIO_CONTROL_ENABLE_MASK                                                                     (0x40000000U)

#define CSL_GMACSW_MDIO_CONTROL_IDLE_SHIFT                                                                      (0x0000001FU)
#define CSL_GMACSW_MDIO_CONTROL_IDLE_MASK                                                                       (0x80000000U)


/* MDIO_USERACCESS0 */

#define CSL_GMACSW_MDIO_USERACCESS0_DATA_SHIFT                                                                  (0x00000000U)
#define CSL_GMACSW_MDIO_USERACCESS0_DATA_MASK                                                                   (0x0000FFFFU)

#define CSL_GMACSW_MDIO_USERACCESS0_PHYADR_SHIFT                                                                (0x00000010U)
#define CSL_GMACSW_MDIO_USERACCESS0_PHYADR_MASK                                                                 (0x001F0000U)

#define CSL_GMACSW_MDIO_USERACCESS0_REGADR_SHIFT                                                                (0x00000015U)
#define CSL_GMACSW_MDIO_USERACCESS0_REGADR_MASK                                                                 (0x03E00000U)

#define CSL_GMACSW_MDIO_USERACCESS0_RESERVED1_SHIFT                                                             (0x0000001AU)
#define CSL_GMACSW_MDIO_USERACCESS0_RESERVED1_MASK                                                              (0x1C000000U)

#define CSL_GMACSW_MDIO_USERACCESS0_ACK_SHIFT                                                                   (0x0000001DU)
#define CSL_GMACSW_MDIO_USERACCESS0_ACK_MASK                                                                    (0x20000000U)

#define CSL_GMACSW_MDIO_USERACCESS0_WRITE_SHIFT                                                                 (0x0000001EU)
#define CSL_GMACSW_MDIO_USERACCESS0_WRITE_MASK                                                                  (0x40000000U)

#define CSL_GMACSW_MDIO_USERACCESS0_GO_SHIFT                                                                    (0x0000001FU)
#define CSL_GMACSW_MDIO_USERACCESS0_GO_MASK                                                                     (0x80000000U)


/* MDIO_USERPHYSEL0 */

#define CSL_GMACSW_MDIO_USERPHYSEL0_PHYADDRMON_SHIFT                                                            (0x00000000U)
#define CSL_GMACSW_MDIO_USERPHYSEL0_PHYADDRMON_MASK                                                             (0x0000001FU)

#define CSL_GMACSW_MDIO_USERPHYSEL0_RESERVED2_SHIFT                                                             (0x00000005U)
#define CSL_GMACSW_MDIO_USERPHYSEL0_RESERVED2_MASK                                                              (0x00000020U)

#define CSL_GMACSW_MDIO_USERPHYSEL0_LINKINTENB_SHIFT                                                            (0x00000006U)
#define CSL_GMACSW_MDIO_USERPHYSEL0_LINKINTENB_MASK                                                             (0x00000040U)

#define CSL_GMACSW_MDIO_USERPHYSEL0_LINKSEL_SHIFT                                                               (0x00000007U)
#define CSL_GMACSW_MDIO_USERPHYSEL0_LINKSEL_MASK                                                                (0x00000080U)

#define CSL_GMACSW_MDIO_USERPHYSEL0_RESERVED1_SHIFT                                                             (0x00000008U)
#define CSL_GMACSW_MDIO_USERPHYSEL0_RESERVED1_MASK                                                              (0xFFFFFF00U)


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CSLR_GMACSW_MDIO_H_ */

