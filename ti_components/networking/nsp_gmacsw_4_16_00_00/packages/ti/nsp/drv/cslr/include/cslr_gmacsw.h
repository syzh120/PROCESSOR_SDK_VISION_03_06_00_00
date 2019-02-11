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
 *   \file  cslr_gmacsw.h
 *
 *   \desc  This file contains the Register Descriptions for GMACSW
 *
 *  ============================================================================
 */

#ifndef CSLR_GMACSW_H_
#define CSLR_GMACSW_H_

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
#include "cslr_gmacsw_ss.h"
#include "cslr_gmacsw_port.h"
#include "cslr_gmacsw_cpdma.h"
#include "cslr_gmacsw_stats.h"
#include "cslr_gmacsw_stateram.h"
#include "cslr_gmacsw_cpts.h"
#include "cslr_gmacsw_ale.h"
#include "cslr_gmacsw_sl.h"
#include "cslr_gmacsw_mdio.h"
#include "cslr_gmacsw_wr.h"


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/* Register Overlay Structure */
#if defined(DEVICE_CENTAURUS)
typedef struct
{
    volatile uint8_t        RSVD1[0x2000U];
    uint8_t                 RAM[8192];              /* 0x2000U */
}
CSL_GMACSW_cppiRam;

typedef union
{
    CSL_GMACSW_ssRegs       SS;                     /* 0x0000U */
    CSL_GMACSW_portRegs     PORT;                   /* 0x0028U */
    CSL_GMACSW_cpdmaRegs    CPDMA;                  /* 0x0100U */
    CSL_GMACSW_stateramRegs STATERAM;               /* 0x0200U */
    CSL_GMACSW_statsRegs    STATS;                  /* 0x0400U */
    CSL_GMACSW_cptsRegs     CPTS;                   /* 0x0500U */
    CSL_GMACSW_aleRegs      ALE;                    /* 0x0600U */
    CSL_GMACSW_slRegs       SL;                     /* 0x0700U */
    CSL_GMACSW_mdioRegs     MDIO;                   /* 0x0800U */
    CSL_GMACSW_wrRegs       WR;                     /* 0x0900U */
    CSL_GMACSW_cppiRam      CPPI_RAM;               /* 0x2000U */
}
CSL_GmacSWRegs;
#else
typedef struct
{
    uint8_t                 RAM[8192];              /* 0x2000U */
}
CSL_GMACSW_cppiRam;

typedef struct
{
    CSL_GMACSW_ssRegs       SS;                     /* 0x0000U */
    CSL_GMACSW_portRegs     PORT;                   /* 0x0100U */
    volatile uint8_t        RSVD1[0x400U];          /* 0x0400U */
    CSL_GMACSW_cpdmaRegs    CPDMA;                  /* 0x0800U */
    CSL_GMACSW_statsRegs    STATS;                  /* 0x0900U */
    CSL_GMACSW_stateramRegs STATERAM;               /* 0x0A00U */
    CSL_GMACSW_cptsRegs     CPTS;                   /* 0x0C00U */
    CSL_GMACSW_aleRegs      ALE;                    /* 0x0D00U */
    CSL_GMACSW_slRegs       SL;                     /* 0x0D80U */
    volatile uint8_t        RSVD2[0x200U];          /* 0x0E00U */
    CSL_GMACSW_mdioRegs     MDIO;                   /* 0x1000U */
    CSL_GMACSW_wrRegs       WR;                     /* 0x1200U */
    volatile uint8_t        RSVD3[0xD00U];          /* 0x1300U */
    CSL_GMACSW_cppiRam      CPPI_RAM;               /* 0x2000U */
}
CSL_GmacSWRegs;
#endif


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Peripheral Base Address */
#if (defined(DEVICE_J5ECO) || defined(DEVICE_CENTAURUS))
#define GMACSW_REGS                         ((CSL_GmacSWRegs *)0x4A100000U)
#else
/* #if defined(DEVICE_VAYU)*/
#define GMACSW_REGS                         ((CSL_GmacSWRegs *)0x48484000U)
#endif


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _CSLR_GMACSW_H_ */

