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
 *  \file null_stack_private.h
 *
 *  \brief NULL Stack private header file.
 */

#ifndef NULL_STACK_PRIV_H_
#define NULL_STACK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>
#include <stdbool.h>

/* OS/Posix headers */
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Project dependency headers */
#include "null_stack.h"
#include "null2nsp.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define MAX_ETH_PAYLOAD_LEN         (1500U)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Ethernet frame definitions                        |
\*---------------------------------------------------------------------------*/

/*! \brief 802.1Q tag field in an ethernet frame
 * \ingroup group_nullstack_priv
 */
struct vlan_af
{
    uint16_t tpid;
    uint16_t tci;
};

/*! \brief The main Ethernet frame header
 * \ingroup group_nullstack_priv
 */
typedef struct ether_frame_header
{
    /*! Destination MAC address */
    uint8_t dstMac[6];
    /*! Source MAC address */
    uint8_t srcMac[6];
    /*! VLAN tag */
    struct vlan_af vlanaf;
    /*! The frame type */
    uint16_t etherType;
} ether_frame_header_t;

/*! \brief An ethernet frame
 * \ingroup group_nullstack_priv
 */
typedef struct ether_frame
{
    /*! Header */
    ether_frame_header_t header;
    /*! The generic data payload */
    uint8_t payload[MAX_ETH_PAYLOAD_LEN];
} ether_frame_t;

typedef struct null_frame_payload
{
    uint16_t length;
    uint32_t seq_num;
}
null_frame_payload_t;

/*! \brief Structure for holding the state information of an instance of the NULL stack
 * \ingroup group_nullstack_priv
 */
typedef struct NULL_STACK_STATE_
{
    /*! boolean to indicate that packets/frames should be examined */
    bool checkPackets;
    /*! saved sequence number from previous Rx packet */
    uint32_t prevSeqNum;
    /*! A semaphore to synchronize shutdown */
    Semaphore_Handle exitSem;
    /*! The handle to the translation layer between the Null Stack and the NSP driver */
    NULL2NSP_Handle hNULL2NSP;

    NULL_Stats stats;
}
NULL_State;


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

#endif  /* NULL_STACK_PRIV_H_ */
