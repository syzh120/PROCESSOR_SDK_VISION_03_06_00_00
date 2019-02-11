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

/*!
 *   \file  port.h
 *
 *   \brief
 *      Private header file for PORT module of GMAC SW subsystem.
 *
 */


#ifndef PORT__H_
#define PORT__H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */
#include "mac_.h"
#include "cpdma_.h"
#include "port.h"

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Maximum num of channels of one type (Rx or Tx) supported by the DMA */
#define PORT_MAX_RX_PRIORITY_MAP                        ((uint32_t)0x8U)
#define PORT_MAX_TX_PRIORITY_MAP                        ((uint32_t)0x8U)
#define PORT_MAX_TX_RATE_LIMIT_MAP                      ((uint32_t)0x8U)

/* Number of priority levels attributable to packets */
#define PORT_PACKET_PRIORITY_COUNT ((uint32_t)8U)

/* Number of priority levels in the switch FIFOs */
#define PORT_SWITCH_PRIORITY_COUNT ((uint32_t)4U)

#define PORT_CPDMA_CHANNEL_UNUSED  ((uint32_t)0xFFFFFFFFU)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 * \brief  PORT Receive Priority Map Instance Structure
 */
typedef struct PORT_RX_PRIORITY_MAP_
{
    uint32_t                mapNumber;
    PORT_RxPriorityConfig   config;
}
PORT_RxPriorityMap;

/*!
 * \brief  PORT Transmit Priority Map Instance Structure
 */
typedef struct PORT_TX_PRIORITY_MAP_
{
    uint32_t                mapNumber;
    PORT_TxPriorityConfig   config;
}
PORT_TxPriorityMap;

/*!
 * \brief  PORT Transmit Rate Limit Map Instance Structure
 */
typedef struct PORT_TX_RATE_LIMIT_MAP_
{
    uint32_t    mapNumber;
    uint32_t    limitPercentage;
}
PORT_TxRateLimitMap;

/*!
 * \brief  PORT Instance Structure
 */
typedef struct PORT_STATE_
{
    /*!
     * \brief  Bit vector of allocated Rx priority mappings.
     */
    uint32_t rxPriorityMapBitVector;

    /*!
     * \brief  Bit vector of allocated Tx priority mappings.
     */
    uint32_t txPriorityMapBitVector;

    /*!
     * \brief  Bit vector of allocated Tx rate limiting mappings.
     */
    uint32_t txRateLimitBitVector;

    /*!
     * \brief  Array of Rx priority mappings.
     */
    PORT_RxPriorityMap      rxPriorityMap[PORT_MAX_RX_PRIORITY_MAP];

    /*!
     * \brief  Array of Tx priority mappings.
     */
    PORT_TxPriorityMap      txPriorityMap[PORT_MAX_TX_PRIORITY_MAP];

    /*!
     * \brief  Mappings of packet priority to switch priority for each port
     */
    PORT_SwitchPriority     rxPacketToSwitchPriorityMap[MAC_NUM_PORTS][PORT_PACKET_PRIORITY_COUNT];

    /*!
     * \brief  Mappings of packet priority to switch priority for each port
     */
    PORT_SwitchPriority     txPacketToSwitchPriorityMap[MAC_NUM_PORTS][PORT_PACKET_PRIORITY_COUNT];

    /*!
     * \brief  Mappings of switch priority to cpdma channel for each port
     */
    uint32_t                rxSwitchPriorityToCPDMAChannelMap[MAC_NUM_PORTS][PORT_SWITCH_PRIORITY_COUNT];

    uint32_t                rxUntaggedMappingActive[MAC_NUM_PORTS];
    uint32_t                rxDiffservMappingCount[MAC_NUM_PORTS];

#if (0)
    /*!
     * \brief  Array of Tx rate limiting mappings.
     */
    PORT_TxRateLimitMap     txRateLimitMap[PORT_MAX_TX_RATE_LIMIT_MAP];

    PORT_SwitchPriority     txSwitchPriority[PORT_SWITCH_PRIORITY_COUNT];
#endif
}
PORT_State;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* PORT__H_ */

