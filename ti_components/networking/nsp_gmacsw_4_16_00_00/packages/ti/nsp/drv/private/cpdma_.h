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
 *   \file  cpdma.h
 *
 *   \brief
 *      Private header file for CPDMA port of GMACSW subsystem.
 *
 */


#ifndef CPDMA__H_
#define CPDMA__H_

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
#if defined(NSP_INSTRUMENTATION_ENABLED)
#include "timer_.h"
#endif
#include "gmacsw_al.h"
#include "cpdma.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Maximum num of channels of one type (Rx or Tx) supported by the DMA */
#define CPDMA_MAX_RX_CHANNELS                       ((uint32_t)0x8U)
#define CPDMA_MAX_TX_CHANNELS                       ((uint32_t)0x8U)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief CPDMA Direction Enum
 *
 *  \details
 */
typedef enum CPDMA_DIRECTION_
{
    CPDMA_DIRECTION_RX = 0,
    CPDMA_DIRECTION_TX = 1
}
CPDMA_Direction;

#if defined(NSP_INSTRUMENTATION_ENABLED)

#define INTERRUPT_HISTORY_CNT (256U)

typedef struct CPDMA_INTERRUPT_STATS_
{
    uint32_t totalInterruptCnt;
    uint32_t totalPacketCnt;
    uint32_t totalCycleCnt;
    uint32_t completionType[INTERRUPT_HISTORY_CNT];
    uint32_t packetsPerInterruptMax;
    uint32_t packetsPerInterruptMaxEventNumber;
    uint32_t packetsPerInterrupt[INTERRUPT_HISTORY_CNT];
    uint32_t cycleCountPerInterruptMax;
    uint32_t cycleCountPerInterruptMaxEventNumber;
    uint32_t cycleCountPerInterrupt[INTERRUPT_HISTORY_CNT];
    uint32_t cycleCountPerPacketMax;
    uint32_t cycleCountPerPacketMaxEventNumber;
    uint32_t cycleCountPerPacket[INTERRUPT_HISTORY_CNT];
}
CPDMA_InterruptStats;

typedef struct CPDMA_STATS_
{
    CPDMA_InterruptStats rxThreshChannelStats[CPDMA_MAX_RX_CHANNELS];

    CPDMA_InterruptStats rxChannelStats[CPDMA_MAX_RX_CHANNELS];

    CPDMA_InterruptStats txChannelStats[CPDMA_MAX_TX_CHANNELS];

    uint32_t hwIntMiscCnt[5];               /* Measures how many times the Misc ISR was called for each type of misc interrupt */
}
CPDMA_Stats;

#endif

/*!
 * \brief Transmit/Receive Channel Structure
 *
 * \details
 *      The following is a book keeping structure for the channels that can
 *      be used in the CPDMA.
 *
 */
typedef struct CPDMA_CHANNEL_
{
    /*!
     * \brief  Channel number (from 0 to CPDMA_MAX_CHANNELS - 1)
     */
    uint32_t            channelNum;
    /*!
     * \brief  Channel direction (from CPDMA_DIRECTION_RX or CPDMA_DIRECTION_TX)
     */
    uint32_t            channelDir;
    /*!
     * \brief  Channel open flag
     */
    uint32_t            isOpened;
    /*!
     * \brief  Channel started flag
     */
    uint32_t            isStarted;
    /*!
     * \brief  Channel packet count
     */
    uint32_t            packetCount;
    /*!
     * \brief  Channel packet memory pointer
     */
    CPDMA_Packet        *packetMem;
    /*!
     * \brief  Callback information to get to translation layer
     */
    CPDMA_Callbacks     callbacks;
    /*!
     * \brief  Packet queue to track active packets given to the CPDMA hardware for this channel
     */
    CPDMA_PacketQueue   inUsePacketQueue;
    /*!
     * \brief  Packet queue to hold packets that have been used by the CPDMA hardware (full on Rx, empty on Tx)
     */
    CPDMA_PacketQueue   fromHardwarePacketQueue;
    /*!
     * \brief  Packet queue to hold packets that are ready to be returned to the channel's inUse queue (SW is finished)
     */
    CPDMA_PacketQueue   toHardwarePacketQueue;
}
CPDMA_Channel;

/*!
 * \brief Transmit/Receive Channel Structure
 *
 * \details
 *      The following is a book keeping structure for the channels that can
 *      be used in the CPDMA.
 *
 */
typedef struct CPDMA_RX_CHANNEL_
{
    /*!
     * \brief  Underlying shared channel structure.
     */
    CPDMA_Channel           channel;
    /*!
     * \brief  Free buffer descriptors count threshold to trigger an RX_THRESH interrupt.
     *         Set to zero for no threshold interrupt enablement. This is a don't care for Tx
     *         channels.
     */
    uint32_t                rxThreshCount;
}
CPDMA_RxChannel;

/*!
 * \brief Transmit/Receive Channel Structure
 *
 * \details
 *      The following is a book keeping structure for the channels that can
 *      be used in the CPDMA.
 *
 */
typedef struct CPDMA_TX_CHANNEL_
{
    CPDMA_Channel       channel;
}
CPDMA_TxChannel;

/*!
 * \brief CPDMA State Structure
 *
 * \details
 *      Structure to hold software state for the CPDMA hardware.
 *
 */
typedef struct CPDMA_STATE_
{
    /*!
     * \brief  Pointer to original config used to initialize the CPDMA
     */
    CPDMA_Config        *pCPDMAConfig;

    /*!
     * \brief  A global buffer descriptor queue from which open operations
     *         can get descriptor and to which close operations can return
     *         descriptors.  If this queue is empty, open channel operations
     *         will fail.
     */
    CPDMA_BuffDescQueue freeDescriptorQueue;

    /*!
     * \brief  Bit vector of allocated Rx channels.
     */
    uint32_t rxChannelBitVector;

    /*!
     * \brief  Bit vector of allocated Tx channels.
     */
    uint32_t txChannelBitVector;

    /*!
     * \brief  Array of receive channels that can be managed by this module.
     */
    CPDMA_RxChannel     rxChannel[CPDMA_MAX_RX_CHANNELS];

    /*!
     * \brief  Array of transmit channels that can be managed by this module.
     */
    CPDMA_TxChannel     txChannel[CPDMA_MAX_TX_CHANNELS];
}
CPDMA_State;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(NSP_INSTRUMENTATION_ENABLED)
extern CPDMA_Stats cpdmaStats;
#endif


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern uint32_t CPDMA_openRxChannel(CPDMA_Handle hCpdma, const CPDMA_RxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle);
extern uint32_t CPDMA_closeRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);

extern uint32_t CPDMA_startRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
extern uint32_t CPDMA_stopRxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);

extern uint32_t CPDMA_openTxChannel(CPDMA_Handle hCpdma, const CPDMA_TxChannelConfig *pCPDMAChannelConfig, CPDMA_ChannelHandle *pChannelHandle);
extern uint32_t CPDMA_closeTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);

extern uint32_t CPDMA_startTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);
extern uint32_t CPDMA_stopTxChannel(CPDMA_Handle hCpdma, CPDMA_ChannelHandle hChannel);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CPDMA__H_ */


