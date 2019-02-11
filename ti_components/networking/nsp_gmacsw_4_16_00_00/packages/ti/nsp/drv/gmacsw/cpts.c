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
 *   \file  cpts.c
 *
 *   \brief
 *          CPTS module implementation
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Project dependency headers */
#if defined(USE_CSLR)
#include "cslr.h"
#include "cslr_gmacsw.h"
#else
#include "soc.h"
#include "gmac_sw.h"
#endif
#include "gmacsw_al.h"

/* This module's private header */
#include "private/cpts_.h"

/* This module's public header */
#include "cpts.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/


static uint32_t LOCAL_timestampPush(CPTS_State *pCpts);
static uint32_t LOCAL_timestampLoad(CPTS_State *pCpts, uint64_t timeStamp);
static uint32_t LOCAL_registerStack(CPTS_State *pCpts, const CPTS_StackConfig *pCptsStackConfig);
static uint32_t LOCAL_unregisterStack(CPTS_State *pCpts);
static uint32_t LOCAL_getEvent(CPTS_State *pCpts, CPTS_Event **ppEvent);
static uint32_t LOCAL_lookupEvent(CPTS_State *pCpts, const CPTS_Event *pEventTemplate, CPTS_Event **ppEvent);
static uint32_t LOCAL_releaseEvent(CPTS_State *pCpts, CPTS_Event *pEvent);
static uint32_t LOCAL_clearAllCPTSEvents(CPTS_State *pCpts);
static uint32_t LOCAL_getFrequency(const CPTS_State *pCpts, uint32_t *pFrequency);
static uint32_t LOCAL_setFrequency(CPTS_State *pCpts, uint32_t frequency);

static CPTS_Event *LOCAL_cptsEventExtract(CPTS_EventQueue *pCPTSEventQueue, const CPTS_Event *pEventTemplate);
static CPTS_Event *LOCAL_cptsEventDequeue(CPTS_EventQueue *pCPTSEventQueue);
static void LOCAL_cptsEventEnqueue(CPTS_EventQueue *pCPTSEventQueue, CPTS_Event *pCPTSEvent);
static uint64_t LOCAL_calcTimestamp(const CPTS_State *pCpts, uint32_t lowerTimeStamp);

static void LOCAL_clearSWQueueEvents(CPTS_State *pCpts);
static void LOCAL_clearHWFifoEvents(CPTS_State *pCpts);
static void LOCAL_disableCPTSInterrupt(CPTS_State *pCpts);
static void LOCAL_enableCPTSInterrupt(CPTS_State *pCpts);



/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
static CPTS_State CPTS_stateObj;
#endif

/* Data to keep track of open references to the PORT state */
static uint32_t     LOCAL_cptsRefCount  = 0;
static CPTS_State   *LOCAL_cptsRef      = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(NSP_INSTRUMENTATION_ENABLED)
CPTS_Stats cptsStats;
#endif


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

CPTS_Handle CPTS_open(const CPTS_Config *pCptsConfig)
{
    CPTS_State      *pCpts;
    uint32_t        key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_cptsRefCount++;

    if ((uint32_t)1U == LOCAL_cptsRefCount)
    {
        if (IS_NULL(pCptsConfig))
        {
            return NULL;
        }

        /*
         * Init the instance structure
         */
#if defined(NSP_DYNAMIC_ALLOCATION)
        pCpts  = (CPTS_State *) calloc(1U, sizeof(CPTS_State));
#else
        pCpts = &CPTS_stateObj;

        /* Zero init the CPTS_State structure */
        memset((void *)pCpts, 0, (size_t) sizeof(CPTS_State));
#endif

#if defined(NSP_INSTRUMENTATION_ENABLED)
        memset(&cptsStats, 0, sizeof(CPTS_Stats));
#endif

        /* Initialize the free event queue */
        CPTS_eventQueueInit(&pCpts->freeQueue);

        /* Initialize the active event queue */
        CPTS_eventQueueInit(&pCpts->activeQueue);

        /* Set initial values for state fields */
        pCpts->pEventNotifyCallback        = NULL;
        pCpts->upperTimeStamp              = 0U;
        pCpts->checkForMisalignment        = 0U;
        pCpts->tsPushInFIFO                = 0U;

        /* Save the input frequency value */
        pCpts->cptsInputFrequency          = pCptsConfig->cptsInputFrequency;

        if (0U != pCptsConfig->enableCPTSEvents)
        {
            /* Enable the CPTS Module */
            CSL_FINS( GMACSW_REGS->CPTS.CPTS_CONTROL,
                      GMACSW_CPTS_CONTROL_CPTS_EN,
                      1U );

            /* Enable the CPTS interrupt by setting the enable bit */
            LOCAL_enableCPTSInterrupt(pCpts);

            /* Enable the EVNT misc interrupt in the wrapper module */
            CSL_FINS( GMACSW_REGS->WR.WR_C0_MISC_EN,
                      GMACSW_WR_C0_MISC_EN_EVNT_PEND,
                      1U );
        }

        /* Save a pointer to the state structure to be used to provide a reference for future open calls */
        LOCAL_cptsRef = pCpts;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, CPDMA was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
        pCpts = LOCAL_cptsRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return (CPTS_Handle) pCpts;
}

uint32_t CPTS_close(CPTS_Handle hCptsState)
{
    CPTS_State *pCpts = (CPTS_State *) hCptsState;

    uint32_t retVal = CPTS_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_cptsRefCount--;

    if (0U == LOCAL_cptsRefCount)
    {
        /* Disable the CPTS interrupt by setting the enable bit */
        LOCAL_disableCPTSInterrupt(pCpts);

        /* Disable the CPTS Module */
        CSL_FINS( GMACSW_REGS->CPTS.CPTS_CONTROL,
                  GMACSW_CPTS_CONTROL_CPTS_EN,
                  0U );

        /* Reset the local reference holder */
        LOCAL_cptsRef = NULL;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pCpts);
#else
        memset(pCpts, 0 , sizeof(CPTS_State));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

uint32_t CPTS_ioctl(CPTS_Handle hCpts, uint32_t cmd, void *param, uint32_t size)
{
    CPTS_State *pCpts = (CPTS_State *) hCpts;
    uint32_t retVal = CPTS_FAILURE;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_CPTS_TIMESTAMP_PUSH:
        {
            if ((0U != size) || (NULL != param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_timestampPush(pCpts);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_TIMESTAMP_LOAD:
        {
            if ((sizeof(uint64_t) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_timestampLoad(pCpts,*((uint64_t *)param));
            }

            break;
        }
        case GMACSW_IOCTL_CPTS_REGISTER_STACK:
        {
            if ((sizeof(CPTS_StackConfig) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_registerStack(pCpts, (CPTS_StackConfig *) param);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_UNREGISTER_STACK:
        {
            if ((0U != size) || (NULL != param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_unregisterStack(pCpts);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_GET_EVENT:
        {
            if ((sizeof(CPTS_Event **) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                CPTS_Event **ppEvent = (CPTS_Event **) param;
                retVal = LOCAL_getEvent(pCpts, ppEvent);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_LOOKUP_EVENT:
        {
            if ((sizeof(CPTS_LookupEventIoctlCmd) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                CPTS_LookupEventIoctlCmd *pCmd = (CPTS_LookupEventIoctlCmd *) param;
                retVal = LOCAL_lookupEvent(pCpts, pCmd->pEventTemplate, pCmd->pReturnEvent);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_RELEASE_EVENT:
        {
            if ((sizeof(CPTS_Event *) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                CPTS_Event *pEvent = (CPTS_Event *) param;
                retVal = LOCAL_releaseEvent(pCpts, pEvent);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_CLEAR_ALL_EVENTS:
        {
            if ((0U != size) || (NULL != param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_clearAllCPTSEvents(pCpts);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_GET_FREQUENCY:
        {
            if ((sizeof(uint32_t) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                uint32_t *pFrequency = (uint32_t *) param;
                retVal = LOCAL_getFrequency(pCpts, pFrequency);
            }
            break;
        }
        case GMACSW_IOCTL_CPTS_SET_FREQUENCY:
        {
            if ((sizeof(uint32_t) != size) || (NULL == param))
            {
                retVal = CPTS_MALFORMED_IOCTL;
            }
            else
            {
                uint32_t frequency = *((uint32_t *)param);
                retVal = LOCAL_setFrequency(pCpts, frequency);
            }
            break;
        }
        default:
        {
            retVal = CPTS_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}

void CPTS_handleEvents(CPTS_Handle hCptsState)
{
    CPTS_State *pCpts = (CPTS_State *) hCptsState;
    CPTS_Event event;

    uint32_t lowerTimeStamp;
    uint32_t eventFields;

    /* Upon interrupt, read the CPTS_EVENT_LOW and CPTS_EVENT_HIGH registers values. */
    eventFields     = GMACSW_REGS->CPTS.CPTS_EVENT_HIGH;
    lowerTimeStamp  = GMACSW_REGS->CPTS.CPTS_EVENT_LOW;

    /*
     * Set the EVENT_POP field (bit 0) of the CPTS_EVENT_POP register to pop the
     * previously read value off of the event FIFO.
     */
    CSL_FINS( GMACSW_REGS->CPTS.CPTS_EVENT_POP,
              GMACSW_CPTS_EVENT_POP_EVENT_POP,
              1 );

    event.eventType     = (CPTS_EventType) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_EVENT_TYPE);
    event.messageType   = (CPTS_MessageType) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE);
    event.sequenceId    = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID);
    event.portNumber    = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER);

    if (event.eventType == CPTS_EVENT_TIME_STAMP_ROLLOVER)
    {
        /* Lower 32-bits in hardware rolled over, increment upper 32-bits by 1 */
        pCpts->upperTimeStamp += 1;

        /* Mark that misalignement checking is now required */
        pCpts->checkForMisalignment = 1U;

    #if defined(NSP_INSTRUMENTATION_ENABLED)
        cptsStats.tsRolloverEventCount++;
    #endif
    }
    else if (event.eventType == CPTS_EVENT_TIME_STAMP_HALF_ROLLOVER)
    {
        /* Mark that misalignment checking is not required */
        pCpts->checkForMisalignment = 0U;

    #if defined(NSP_INSTRUMENTATION_ENABLED)
        cptsStats.tsHalfRolloverEventCount++;
    #endif
    }
    else
    {
        if ( NULL != pCpts->pEventNotifyCallback )
        {
            /* Get a free Event from the freeEvent queue */
            CPTS_Event *pEvent = LOCAL_cptsEventDequeue(&pCpts->freeQueue);

            /* Check to make sure an event was available - if not, this current event gets dropped */
            if (NULL != pEvent)
            {
                /* Get the event information */
                pEvent->eventType   = event.eventType;
                pEvent->messageType = event.messageType;
                pEvent->sequenceId  = event.sequenceId;
                pEvent->portNumber  = event.portNumber;

                switch(pEvent->eventType)
                {
                    case CPTS_EVENT_TIME_STAMP_PUSH:
                    {
                        /* Clear the flag that indicates a TS_PUSH event is in the FIFO */
                        pCpts->tsPushInFIFO = 0U;

                        /* These fields are meaningless for this event type */
                        pEvent->portNumber  = 0;
                        pEvent->sequenceId  = 0;
                        pEvent->messageType = CPTS_MESSAGE_INVALID;
        #if defined(NSP_INSTRUMENTATION_ENABLED)
                        cptsStats.tsSwPushEventCount++;
        #endif
                        break;
                    }

                    case CPTS_EVENT_HARDWARE_TIME_STAMP_PUSH:
                    {
                        /* Get the port number which for HW PUSH events gives the HW_PUSH number (1-4) */
                        pEvent->portNumber  = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER);

                        /* These fields are meaningless for this event type */
                        pEvent->sequenceId  = 0;
                        pEvent->messageType = CPTS_MESSAGE_INVALID;
        #if defined(NSP_INSTRUMENTATION_ENABLED)
                        cptsStats.tsHwPushEventCount[pEvent->portNumber]++;
        #endif
                        break;
                    }

                    case CPTS_EVENT_ETHERNET_RECEIVE:
                    {
                        /* For Ethernet events, get the messageType, sequence ID, and port number */
                        pEvent->messageType = (CPTS_MessageType) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE);
                        pEvent->sequenceId = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID);
                        pEvent->portNumber = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER);
        #if defined(NSP_INSTRUMENTATION_ENABLED)
                        cptsStats.tsEthernetRxEventCount++;
        #endif
                        break;
                    }

                    case CPTS_EVENT_ETHERNET_TRANSMIT:
                    {
                        /* For Ethernet events, get the messageType, sequence ID, and port number */
                        pEvent->messageType = (CPTS_MessageType) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE);
                        pEvent->sequenceId = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID);
                        pEvent->portNumber = (uint16_t) CSL_FEXT(eventFields, GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER);
        #if defined(NSP_INSTRUMENTATION_ENABLED)
                        cptsStats.tsEthernetTxEventCount++;
        #endif
                        break;
                    }

                    default:
                    {
                        /* Release the event since it isn't needed by anyone */
                        LOCAL_releaseEvent(pCpts, pEvent);
                        pEvent = NULL;

                        break;
                    }
                }

                if (NULL != pEvent)
                {
                    /* Calculate the full 64-bit timestamp */
                    pEvent->timeStamp = LOCAL_calcTimestamp(pCpts, lowerTimeStamp);

                    /*
                     * The event should be handled by the registered stack, so
                     * put it into the active event queue
                     */
                    LOCAL_cptsEventEnqueue(&pCpts->activeQueue, pEvent);

                    /* Notify the registered stack that a CPTS event has been detected */
                    (*pCpts->pEventNotifyCallback)(pCpts->hEventNotifyCallbackArg);
                }
            }
#if defined(NSP_INSTRUMENTATION_ENABLED)
            else
            {
                cptsStats.unhandledEventCount++;
            }
#endif
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        else
        {
            cptsStats.unhandledEventCount++;
        }
#endif
    }
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* LOCAL IOCTL implementations */

static uint32_t LOCAL_timestampPush(CPTS_State *pCpts)
{
    uint32_t retVal = CPTS_SUCCESS;

    /* Do SW timestamp push */
    if (0U == pCpts->tsPushInFIFO)
    {
        pCpts->tsPushInFIFO = 1U;
        CSL_FINS( GMACSW_REGS->CPTS.CPTS_TS_PUSH,
                  GMACSW_CPTS_TS_PUSH_TS_PUSH,
                  1);
    }
    else
    {
        retVal = CPTS_TSPUSH_ALREADY_IN_FLIGHT;
    }
    return retVal;
}

static uint32_t LOCAL_timestampLoad(CPTS_State *pCpts, uint64_t timeStamp)
{
    uint32_t upperTimeStamp = (uint32_t) (timeStamp >> 32U);
    uint32_t lowerTimeStamp = (uint32_t) (timeStamp & 0xFFFFFFFFU);

    LOCAL_disableCPTSInterrupt(pCpts);

    /* Get rid of all old events since the timestamp base will change */
    LOCAL_clearSWQueueEvents(pCpts);
    LOCAL_clearHWFifoEvents(pCpts);

    /* Now set the timestamp value (lower 32-bit in HW and upper 32-bit in module state) */
    GMACSW_REGS->CPTS.CPTS_TS_LOAD_VAL = lowerTimeStamp;
    GMACSW_REGS->CPTS.CPTS_TS_LOAD_EN = 0x1;
    
    pCpts->upperTimeStamp = upperTimeStamp;

    LOCAL_enableCPTSInterrupt(pCpts);

    return CPTS_SUCCESS;
}

static uint32_t LOCAL_registerStack(CPTS_State *pCpts, const CPTS_StackConfig *pCptsStackConfig)
{
    uint32_t retVal = CPTS_FAILURE;

    if (NULL != pCpts->pEventNotifyCallback)
    {
        retVal = CPTS_STACK_ALREADY_REGISTERED;
    }
    else if (NULL == pCptsStackConfig->pEventNotifyCallback)
    {
        retVal = CPTS_STACK_INVALID_CONFIG;
    }
    else
    {
        uint32_t startMacNum = 0;
        uint32_t endMacNum = 0;
        uint32_t i;

        pCpts->pEventNotifyCallback = pCptsStackConfig->pEventNotifyCallback;

        pCpts->hEventNotifyCallbackArg = pCptsStackConfig->hEventNotifyCallbackArg;

#if !defined(DEVICE_CENTAURUS)
        /*
         * Set the TS LTYPE to the IEEE 1588 Annex F value. This LTYPE will
         * be used by both ports (if both are used for PTP events)
         */
        CSL_FINS( GMACSW_REGS->SS.CPSW_TS_LTYPE,
                  GMACSW_CPSW_TS_LTYPE_TS_LTYPE1,
                  0x88F7U );
        /*
         * Set the VLAN LTYPE to the standard 802.1Q VLAN Ethertype. This LTYPE will
         * be used by both ports (if both are used for PTP events)
         */
        if (CPTS_VLAN_TYPE_NONE != pCptsStackConfig->vlanType)
        {
            CSL_FINS( GMACSW_REGS->SS.CPSW_VLAN_LTYPE,
                      GMACSW_CPSW_VLAN_LTYPE_VLAN_LTYPE1,
                      CSL_GMACSW_CPSW_VLAN_LTYPE_VLAN_LTYPE1_RESETVAL );
            if (CPTS_VLAN_TYPE_STACKED_TAGS == pCptsStackConfig->vlanType)
            {
                CSL_FINS( GMACSW_REGS->SS.CPSW_VLAN_LTYPE,
                          GMACSW_CPSW_VLAN_LTYPE_VLAN_LTYPE2,
                          CSL_GMACSW_CPSW_VLAN_LTYPE_VLAN_LTYPE2_RESETVAL );

            }
        }
#endif

        if (CPTS_PORT_SELECTION_MAC_1 == (CPTS_PortSelection)pCptsStackConfig->portSelection)
        {
            startMacNum = 0U; endMacNum = 0U;
        }
        else if (CPTS_PORT_SELECTION_MAC_2 == (CPTS_PortSelection)pCptsStackConfig->portSelection)
        {
            startMacNum = 1U; endMacNum = 1U;
        }
        else if (CPTS_PORT_SELECTION_MAC_BOTH == (CPTS_PortSelection)pCptsStackConfig->portSelection)
        {
            startMacNum = 0U; endMacNum = 1U;
        }
        else
        {
            /* Dummy settings to do no looping */
            startMacNum = 1U; endMacNum = 0;
        }

        for (i = startMacNum; i <= endMacNum; i++)
        {
#if !defined(DEVICE_CENTAURUS)
            /* Enable all message types */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_SEQ_MTYPE,
                      GMACSW_P_TS_MSG_TYPE_EN,
                      0xFFFFU);

            /* Make sure Sequence ID offset is correct */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_SEQ_MTYPE,
                      GMACSW_P_TS_SEQ_ID_OFFSET,
                      CSL_GMACSW_P_TS_SEQ_ID_OFFSET_RESETVAL);

            /* Enable Rx of TS packets */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                      GMACSW_P_CONTROL_TS_RX_EN,
                      1U );

            /* Enable Tx of TS packets */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                      GMACSW_P_CONTROL_TS_TX_EN,
                      1U );

            /* Enable Annex F of 1588v2 */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                      GMACSW_P_CONTROL_TS_ANNEX_F_EN,
                      1U );

            /* ToDo: Add support for Annex E (IPv6) & Annex D (IPv4)? */

            /* Enable the use of TS LYPTE1 only */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                      GMACSW_P_CONTROL_TS_LTYPE1_EN,
                      1U);
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                      GMACSW_P_CONTROL_TS_LTYPE2_EN,
                      0U);
#else
            /* Enable all message types */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                      GMACSW_P_TS_CTL_TS_MSG_TYPE_EN,
                      0xFFFFU);

            /* Enable Rx of TS packets */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                      GMACSW_P_TS_CTL_TS_RX_EN,
                      1U );

            /* Enable Tx of TS packets */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                      GMACSW_P_TS_CTL_TS_TX_EN,
                      1U );

            /* Make sure Sequence ID offset is correct */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_SEQ_LTYPE,
                      GMACSW_P_TS_SEQ_LTYPE_P_TS_SEQ_ID_OFFSET,
                      CSL_GMACSW_P_TS_SEQ_LTYPE_P_TS_SEQ_ID_OFFSET_RESETVAL);
            /*
             * Set the TS LTYPE to the IEEE 1588 Annex F value. This LTYPE will
             * be used by both ports (if both are used for PTP events)
             */
            CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_SEQ_LTYPE,
                      GMACSW_P_TS_SEQ_LTYPE_P_TS_LTYPE,
                      0x88F7U);
#endif

            if (CPTS_VLAN_TYPE_NONE != pCptsStackConfig->vlanType)
            {

#if !defined(DEVICE_CENTAURUS)
                /* Configure VLAN LTYPE1 */
                CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                          GMACSW_P_CONTROL_VLAN_LTYPE1_EN,
                          1U);
#else
                CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                          GMACSW_P_TS_CTL_TS_TX_VLAN_LTYPE1_EN,
                          1U);
                CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                          GMACSW_P_TS_CTL_TS_RX_VLAN_LTYPE1_EN,
                          1U);

                CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_VLAN,
                          GMACSW_P_TS_VLAN_TS_VLAN_LTYPE1,
                          CSL_GMACSW_P_TS_VLAN_TS_VLAN_LTYPE1_RESETVAL );
#endif
                if (CPTS_VLAN_TYPE_STACKED_TAGS == pCptsStackConfig->vlanType)
                {
#if !defined(DEVICE_CENTAURUS)
                    /* Configure VLAN LTYPE2 */
                    CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_CONTROL,
                              GMACSW_P_CONTROL_VLAN_LTYPE2_EN,
                              1U);
#else
                    CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                              GMACSW_P_TS_CTL_TS_TX_VLAN_LTYPE2_EN,
                              1U);
                    CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_CTL,
                              GMACSW_P_TS_CTL_TS_RX_VLAN_LTYPE2_EN,
                              1U);
                    CSL_FINS( GMACSW_REGS->PORT.MAC_PORT[i].P_TS_VLAN,
                              GMACSW_P_TS_VLAN_TS_VLAN_LTYPE2,
                              CSL_GMACSW_P_TS_VLAN_TS_VLAN_LTYPE2_RESETVAL );
#endif
                }
            }
        }

        /* Init the event queue using memory provided by the stack/app */
        {
            CPTS_Event *pCPTSEvents = (CPTS_Event *)pCptsStackConfig->eventMem;

            /* Clear the entire events array, add to free queue */
            for (i = 0U; i < pCptsStackConfig->eventCount; i++)
            {
                LOCAL_releaseEvent(pCpts, &pCPTSEvents[i]);
            }
        }

        retVal = CPTS_SUCCESS;
    }

    return retVal;
}

static uint32_t LOCAL_unregisterStack(CPTS_State *pCpts)
{
    uint32_t retVal = CPTS_FAILURE;

    if (pCpts->pEventNotifyCallback == NULL)
    {
        retVal = CPTS_STACK_NONE_REGISTERED;
    }
    else
    {
        CPTS_Event *pEvent;

        LOCAL_disableCPTSInterrupt(pCpts);

        pCpts->pEventNotifyCallback = NULL;

        /* Clear out any active SW queue events */
        LOCAL_clearSWQueueEvents(pCpts);

        /* Clear out all the inactive SW queue events */
        pEvent = LOCAL_cptsEventDequeue(&pCpts->freeQueue);
        while (pEvent != NULL)
        {
            memset(pEvent, 0, sizeof(CPTS_Event));
            pEvent = LOCAL_cptsEventDequeue(&pCpts->freeQueue);
        }

        LOCAL_enableCPTSInterrupt(pCpts);

        retVal = CPTS_SUCCESS;
    }

    return retVal;
}

static uint32_t LOCAL_getEvent(CPTS_State *pCpts, CPTS_Event **ppEvent)
{
    uint32_t retVal = CPTS_SUCCESS;

    *ppEvent = LOCAL_cptsEventDequeue(&pCpts->activeQueue);

    if (*ppEvent == NULL)
    {
        retVal = CPTS_NO_ACTIVE_EVENTS;
    }

    return retVal;
}

static uint32_t LOCAL_lookupEvent(CPTS_State *pCpts, const CPTS_Event *pEventTemplate, CPTS_Event **ppEvent)
{
    uint32_t retVal = CPTS_SUCCESS;

    /* Double cast to avoid MISRA-C:2004 11.4 */
    *ppEvent = (CPTS_Event *) ((void *)LOCAL_cptsEventExtract(&pCpts->activeQueue, pEventTemplate));

    if (*ppEvent == NULL)
    {
        retVal = CPTS_NO_ACTIVE_EVENTS;
    }

    return retVal;
}

static uint32_t LOCAL_releaseEvent(CPTS_State *pCpts, CPTS_Event *pEvent)
{
    /* Clear the event contents */
    memset(pEvent, 0, sizeof(CPTS_Event));

    LOCAL_cptsEventEnqueue(&pCpts->freeQueue, pEvent);

    return CPTS_SUCCESS;
}

static uint32_t LOCAL_clearAllCPTSEvents(CPTS_State *pCpts)
{
    LOCAL_disableCPTSInterrupt(pCpts);

    /* Clear out any active events in the SW queue */
    LOCAL_clearSWQueueEvents(pCpts);

    /* Clear out any active events in the HW FIFO */
    LOCAL_clearHWFifoEvents(pCpts);

    LOCAL_enableCPTSInterrupt(pCpts);

    return CPTS_SUCCESS;
}

static uint32_t LOCAL_getFrequency(const CPTS_State *pCpts, uint32_t *pFrequency)
{
    *pFrequency = pCpts->cptsInputFrequency;

    return CPTS_SUCCESS;
}

static uint32_t LOCAL_setFrequency(CPTS_State *pCpts, uint32_t frequency)
{
    pCpts->cptsInputFrequency = frequency;

    return CPTS_SUCCESS;
}


/* Local helper functions */

/* Remove a buffer descriptor from the head of the descriptor queue */
static CPTS_Event *LOCAL_cptsEventDequeue(CPTS_EventQueue *pCPTSEventQueue)
{
    CPTS_Event *pCPTSEvent = NULL;

    if (NULL != pCPTSEventQueue)
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        pCPTSEvent = pCPTSEventQueue->pHead;

        if (NULL != pCPTSEvent)
        {
            pCPTSEventQueue->count--;

            if (pCPTSEventQueue->count)
            {
                pCPTSEventQueue->pHead = pCPTSEvent->pNextEvent;
            }
            else
            {
                pCPTSEventQueue->pHead = NULL;
            }
            pCPTSEvent->pNextEvent = NULL;
            /* Check if queue is now empty */
            if (NULL == pCPTSEventQueue->pHead)
            {
                pCPTSEventQueue->pTail = NULL;
            }
        }

        GMACSW_AL_globalInterruptEnable(key);
    }

    return (pCPTSEvent);
}

/* Add a buffer descriptor to the tail of the descriptor queue */
static void LOCAL_cptsEventEnqueue(CPTS_EventQueue *pCPTSEventQueue, CPTS_Event *pCPTSEvent)
{
    if ( (NULL != pCPTSEvent) && (NULL != pCPTSEventQueue))
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        pCPTSEvent->pNextEvent = NULL;

        if (NULL == pCPTSEventQueue->pHead)
        {
            /* Queue is empty, make head point to new event */
            pCPTSEventQueue->pHead = pCPTSEvent;
        }
        else
        {
            /* Queue is not empty, make previous tail point to new event */
            pCPTSEventQueue->pTail->pNextEvent = pCPTSEvent;
        }

        /* Make tail of queue point to new event */
        pCPTSEventQueue->pTail = pCPTSEvent;
        pCPTSEventQueue->count++;

        GMACSW_AL_globalInterruptEnable(key);
    }
}

/* Lookup and extract an event from the queue */
static CPTS_Event *LOCAL_cptsEventExtract(CPTS_EventQueue *pCPTSEventQueue, const CPTS_Event *pEventTemplate)
{
    CPTS_Event *pCPTSEvent = NULL;

    if (NULL != pCPTSEventQueue)
    {
        uint32_t matchFound         = 0U;
        uint32_t key                = 0U;
        CPTS_Event *currentEvent    = NULL;
        CPTS_Event *prevEvent       = NULL;

        key = GMACSW_AL_globalInterruptDisable();
        currentEvent = pCPTSEventQueue->pHead;

        while (currentEvent)
        {
            /* Double cast to avoid MISRA-C:2004 11.4 */
            CPTS_Event *pEvent = (CPTS_Event *) ((void *)currentEvent);
            /* Check if current event type matches template event type */
            if ( (pEventTemplate->eventType == CPTS_EVENT_ETHERNET_RECEIVE) ||
                 (pEventTemplate->eventType == CPTS_EVENT_ETHERNET_TRANSMIT) )
            {
                /* Ethernet events match by event type, message type, and seq ID */
                if ((pEventTemplate->eventType == pEvent->eventType) &&
                    (pEventTemplate->messageType == pEvent->messageType) &&
                    (pEventTemplate->sequenceId == pEvent->sequenceId))
                {
                    matchFound = 1U;
                }
            }
            else
            {
                /* All other events match by event type only */
                if (pEventTemplate->eventType == pEvent->eventType)
                {
                    matchFound = 1U;
                }
            }

            if (1U == matchFound)
            {
                break;
            }

            prevEvent = currentEvent;
            currentEvent = currentEvent->pNextEvent;
        }

        if (matchFound != 0U)
        {
            /* The currentEvent should be removed from the queue */
            if (currentEvent == pCPTSEventQueue->pHead)
            {
                /* Removing head (and also tail if only one element in queue) */
                pCPTSEventQueue->pHead = currentEvent->pNextEvent;
            }
            else if (currentEvent == pCPTSEventQueue->pTail)
            {
                /* Removing tail (from queue with two or more elements) */
                prevEvent->pNextEvent = NULL;
                pCPTSEventQueue->pTail = prevEvent;
            }
            else
            {
                /* Removing from middle of queue (from queue with 3 or more entries) */
                prevEvent->pNextEvent = currentEvent->pNextEvent;
            }
            /* Decrement the event queue count */
            pCPTSEventQueue->count--;

            /* Disconnect event to be returned from others */
            currentEvent->pNextEvent = NULL;
            pCPTSEvent = currentEvent;
        }

        GMACSW_AL_globalInterruptEnable(key);
    }

    return (pCPTSEvent);
}

/* Calculate the full timestamp from the lower 32-bits and the upper 32-bits in the state */
static uint64_t LOCAL_calcTimestamp(const CPTS_State *pCpts, uint32_t lowerTimeStamp)
{
    uint64_t retTimeStamp = (uint64_t) pCpts->upperTimeStamp;

    /* If misalignment check is required, check it and adjust the upper 32-bits */
    if (1U == pCpts->checkForMisalignment)
    {
        if (0U != (uint32_t)(lowerTimeStamp & (uint32_t) 0x80000000U) )
        {
            retTimeStamp -= 1U;
        }
    }

    /* Shift upper 32-bit to top of timestamp return value and add in lower 32-bits */
    retTimeStamp = (retTimeStamp << 32) + (uint64_t) lowerTimeStamp;

    return retTimeStamp;
}

/* Clear all the active events*/
static void LOCAL_clearSWQueueEvents(CPTS_State *pCpts)
{
    CPTS_Event *pEvent = NULL;

    /* Clear out any active events in the SW queue */
    LOCAL_getEvent(pCpts, &pEvent);
    while (pEvent != NULL)
    {
        LOCAL_releaseEvent(pCpts,pEvent);
        LOCAL_getEvent(pCpts, &pEvent);
    }
}

static void LOCAL_clearHWFifoEvents(CPTS_State *pCpts)
{
    /* Clear out any active events in the HW FIFO */
    while (0U != (GMACSW_REGS->CPTS.CPTS_INTSTAT_RAW & 0x1U))
    {
        /*
         * Set the EVENT_POP field (bit 0) of the CPTS_EVENT_POP register to pop the
         * previously read value off of the event FIFO.
         */
        CSL_FINS( GMACSW_REGS->CPTS.CPTS_EVENT_POP,
                  GMACSW_CPTS_EVENT_POP_EVENT_POP,
                  1U );
    }
}

static void LOCAL_disableCPTSInterrupt(CPTS_State *pCpts)
{
    /* Mask the interrupts */
    CSL_FINS( GMACSW_REGS->CPTS.CPTS_INT_ENABLE,
              GMACSW_CPTS_INT_ENABLE_TS_PEND_EN,
              0U );
}

static void LOCAL_enableCPTSInterrupt(CPTS_State *pCpts)
{
    /* Unmask the interrupts */
    CSL_FINS( GMACSW_REGS->CPTS.CPTS_INT_ENABLE,
              GMACSW_CPTS_INT_ENABLE_TS_PEND_EN,
              1U );
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
