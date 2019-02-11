/*
 * Copyright (C) 2013, Texas Instruments Incorporated  - http://www.ti.com/
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

/**
 *   @file  platform_init.c
 *
 *   @brief
 *       Do all necessary board level initialization for AVBTP test app.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw_config.h>

/* Project dependency headers */
#include "../../common/platform_init.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Ethernet MAC ID registers(Device configuration) from EFuse */
#define MAC_ID0_LO  (*(volatile uint32_t*)0x48140630u)
#define MAC_ID0_HI  (*(volatile uint32_t*)0x48140634u)
#define MAC_ID1_LO  (*(volatile uint32_t*)0x48140638u)
#define MAC_ID1_HI  (*(volatile uint32_t*)0x4814063Cu)

/* I/O Control */
#define GMII_SEL    (*(volatile uint32_t*)0x48140650u)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

void platform_init( void )
{
    /* Select RGMII mode */
    /* FIXME: This should properly move into the driver */
    GMII_SEL      = 0x0000030A;
}

void platform_getMACAddress(uint32_t portNum, uint8_t *macAddr)
{
    bool useDummyMAC = false;
    if (0 == portNum)
    {
        useDummyMAC = (MAC_ID0_HI == 0) && (MAC_ID0_LO == 0);

        macAddr[0] = (uint8_t)((MAC_ID0_HI & 0x000000FFu) >> 0u );
        macAddr[1] = (uint8_t)((MAC_ID0_HI & 0x0000FF00u) >> 8u );
        macAddr[2] = (uint8_t)((MAC_ID0_HI & 0x00FF0000u) >> 16u);
        macAddr[3] = (uint8_t)((MAC_ID0_HI & 0xFF000000u) >> 24u);
        macAddr[4] = (uint8_t)((MAC_ID0_LO & 0x000000FFu) >> 0u );
        macAddr[5] = (uint8_t)((MAC_ID0_LO & 0x0000FF00u) >> 8u );
    }
    else
    {
        useDummyMAC = (MAC_ID1_HI == 0) && (MAC_ID1_LO == 0);

        macAddr[0] = (uint8_t)((MAC_ID1_HI & 0x000000FFu) >> 0u );
        macAddr[1] = (uint8_t)((MAC_ID1_HI & 0x0000FF00u) >> 8u );
        macAddr[2] = (uint8_t)((MAC_ID1_HI & 0x00FF0000u) >> 16u);
        macAddr[3] = (uint8_t)((MAC_ID1_HI & 0xFF000000u) >> 24u);
        macAddr[4] = (uint8_t)((MAC_ID1_LO & 0x000000FFu) >> 0u );
        macAddr[5] = (uint8_t)((MAC_ID1_LO & 0x0000FF00u) >> 8u );
    }

    if (useDummyMAC) {
        macAddr[0] = 0x00U;
        macAddr[1] = 0x01U;
        macAddr[2] = 0x02U;
        macAddr[3] = 0x03U;
        macAddr[4] = 0x04U;
        macAddr[5] = 0x06U;
    }
}

void platform_fillConfig(GMACSW_Config *config)
{
    /* Nothing platform specific to configure */
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
