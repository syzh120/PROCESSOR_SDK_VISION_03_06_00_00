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
 *   \file  cpts_.h
 *
 *   \brief
 *      Private header file for CPTS module of GMACSW subsystem.
 *
 */


#ifndef CPTS__H_
#define CPTS__H_

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
#include "cpts.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 * \brief  CPTS Event Queue Structure
 */
typedef struct CPTS_EVENT_QUEUE_
{
    /*!
     * \brief        Count of elements in the buffer descriptor queue
     */
    uint32_t        count;
    /*!
     * \brief        Pointer to the front of the buffer descriptor queue
     */
    CPTS_Event      *pHead;
    /*!
     * \brief        Pointer to the back of the buffer descriptor queue
     */
    CPTS_Event      *pTail;
}
CPTS_EventQueue;

#if defined(NSP_INSTRUMENTATION_ENABLED)
typedef struct CPTS_STATS_
{
    uint32_t            tsSwPushEventCount;
    uint32_t            tsRolloverEventCount;
    uint32_t            tsHalfRolloverEventCount;
    uint32_t            tsHwPushEventCount[4];
    uint32_t            tsEthernetRxEventCount;
    uint32_t            tsEthernetTxEventCount;
    uint32_t            unhandledEventCount;
}
CPTS_Stats;
#endif

/*!
 * \brief  CPTS Instance Structure
 */
typedef struct CPTS_STATE_
{
    /*!
     * \brief        Field to hold the value of the CPTS timestamp counter frequency
     */
    uint32_t                    cptsInputFrequency;

    /*!
     * \brief        Field to hold the upper 32-bits of the HW timestamp
     */
    uint32_t                    upperTimeStamp;

    /*!
     * \brief        Notify callback function for registered stack
     */
    CPTS_EventNotifyCallback    pEventNotifyCallback;

    /*!
     * \brief        Notify callback function for registered stack
     */
    void                        *hEventNotifyCallbackArg;

    /*!
     * \brief        Queue of events that are not in use
     */
    CPTS_EventQueue             freeQueue;

    /*!
     * \brief        Queue of events that are in use
     */
    CPTS_EventQueue             activeQueue;

    /*!
     * \brief        Flag to indicate that a SW push event is already active
     */
    uint32_t                    tsPushInFIFO;

    /*!
     * \brief        Flag to indicate an alignment check is required
     */
    uint32_t                    checkForMisalignment;
}
CPTS_State;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Declarations                        |
\*---------------------------------------------------------------------------*/

static inline void CPTS_eventQueueInit(CPTS_EventQueue *pCPTSEventQueue);

/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* Init the buffer descriptor queue */
static inline void CPTS_eventQueueInit(CPTS_EventQueue *pCPTSEventQueue)
{
    pCPTSEventQueue->pHead = NULL;
    pCPTSEventQueue->pTail = NULL;
    pCPTSEventQueue->count = 0;
}

/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/* NSP internal module function only */

/*!
 * \brief   CPTS_handleEvents is intended to be called in an ISR context
 *          This is an internal driver function and should not be called
 *          by an application or user.
 */
extern void CPTS_handleEvents(CPTS_Handle hCptsState);




/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CPTS__H_ */
