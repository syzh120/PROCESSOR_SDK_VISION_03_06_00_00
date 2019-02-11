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
 *   \file  cslr_gmacsw_stateram.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for GMAC_SW
 *
 *  ============================================================================
 */

#ifndef CSLR_GMACSW_STATERAM_H_
#define CSLR_GMACSW_STATERAM_H_

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
    volatile uint8_t  RSVD0[0x200U];           /* offset since union is used for Centaurus*/
#endif
    volatile uint32_t TX_HDP[8];
    volatile uint32_t RX_HDP[8];
    volatile uint32_t TX_CP[8];
    volatile uint32_t RX_CP[8];
    volatile uint8_t  RSVD1[384];
}
CSL_GMACSW_stateramRegs;


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Field Definition Macros */

/* Field Definition Macros */

/* TX_HDP */

#define CSL_GMACSW_TX_HDP_TX_HDP_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_TX_HDP_TX_HDP_SHIFT (0x00000000U)
#define CSL_GMACSW_TX_HDP_TX_HDP_RESETVAL (0x00000000U)

#define CSL_GMACSW_TX_HDP_RESETVAL (0x00000000U)

/* RX_HDP */

#define CSL_GMACSW_RX_HDP_RX_HDP_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_RX_HDP_RX_HDP_SHIFT (0x00000000U)
#define CSL_GMACSW_RX_HDP_RX_HDP_RESETVAL (0x00000000U)

#define CSL_GMACSW_RX_HDP_RESETVAL (0x00000000U)

/* TX_CP */

#define CSL_GMACSW_TX_CP_TX_CP_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_TX_CP_TX_CP_SHIFT (0x00000000U)
#define CSL_GMACSW_TX_CP_TX_CP_RESETVAL (0x00000000U)

#define CSL_GMACSW_TX_CP_RESETVAL (0x00000000U)

/* RX_CP */

#define CSL_GMACSW_RX_CP_RX_CP_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_RX_CP_RX_CP_SHIFT (0x00000000U)
#define CSL_GMACSW_RX_CP_RX_CP_RESETVAL (0x00000000U)

#define CSL_GMACSW_RX_CP_RESETVAL (0x00000000U)



/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CSLR_GMACSW_STATERAM_H_ */

