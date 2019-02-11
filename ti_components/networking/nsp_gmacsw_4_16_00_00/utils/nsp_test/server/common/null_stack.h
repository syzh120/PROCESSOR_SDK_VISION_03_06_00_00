/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *  \file null_stack.h
 *
 *  \brief Null Stack main header file.
 */

#ifndef NULL_STACK_H_
#define NULL_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <inttypes.h>
#include <stdbool.h>


#include "null_packet.h"

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief  Structure to report successfully processed packet counts and parser error counts.
 */
typedef struct NULL_STACK_STATS_
{
    /*! Number of data packets successfully processed by the NULL stack */
    uint32_t packetCnt;
    /*! Number of parser errors encountered by the stack */
    uint32_t errorCnt;
    /*! Number of packets with an unexpected ether type field */
    uint32_t unexpectedEtherType;
    /*! Number of packets with zero size or bigger than the maximum allowed payload */
    uint32_t invalidPacketSizeError;
    /*! Number of times the parser encountered an out-of-sequence packet (either from packet loss or truly out of sequence) */
    uint32_t outOfSequenceError;
}
NULL_Stats;

/*!
 *  \brief  Opaque handle type for Null Stack Functions
 */
typedef struct NULL_STACK_STATE_ *NULL_Handle;

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief  Creates and returns an Null Stack handle.
 */
extern NULL_Handle  NULL_open(void);

/*!
 *  \brief  Closes the given Null Stack handle
 */
extern void         NULL_close(NULL_Handle hNullStack);

/*! \brief Obtains statistics gathered by NULL stack
 * \param [in] hNullStack Handle obtained from NULL_open
 * \param [out] stats Structure containing the stack statistics
 */
extern void         NULL_getStatistics(NULL_Handle hNullStack, NULL_Stats *pStats);

/*! \brief Obtains statistics gathered by NULL stack
 * \param [in] hNullStack Handle obtained from NULL_open
 */
extern void         NULL_clearStatistics(NULL_Handle hNullStack);

/*! \brief Obtains the load of the internal listener task
 * \param [in] NULL Handle obtained from NULL_open
 * \returns the task load in percent (0-100)
 */
extern uint32_t     NULL_getRxLoad(NULL_Handle hNullStack);

/*! \brief Obtains the load of the internal talker task
 * \param [in] NULL Handle obtained from NULL_open
 * \returns the task load in percent (0-100)
 */
extern uint32_t     NULL_getTxLoad(NULL_Handle hNullStack);

/*! \brief Asynchronous call to parse and process packets from the ready queue.
 */
extern void         NULL_processRxPackets(NULL_Handle hNullStack);

/*! \brief Blocking call that waits until all received packets are processed
 */
extern void         NULL_waitForPendingRxPackets(NULL_Handle hNullStack);

/*! \brief Sends an NULL Packet to the NSP translation layer
 */
extern void         NULL_sendPacket(NULL_Handle hNullStack, NULL_Packet *pNULLPacket);

/*! \brief Set Packet check for Null packets
 */
extern void         NULL_setPacketChecks(NULL_Handle hNullStack, bool enabled);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* NULL_STACK_H_ */
