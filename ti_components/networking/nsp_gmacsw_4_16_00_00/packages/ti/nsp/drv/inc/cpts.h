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
 *   \file  cpts.h
 *
 *   \brief
 *      Header file for CPTS module of GMAC SW subsystem.
 *
 */


#ifndef CPTS_H_
#define CPTS_H_

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
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Max number of events we can buffer in software */
#define CPTS_EVENT_COUNT_MAX                (16U)

/* Define success and error status values */
#define CPTS_SUCCESS                        (0x00000000U)
#define CPTS_FAILURE                        (0xFFFFFFFFU)
#define CPTS_UNKNOWN_IOCTL                  (0x00000001U)
#define CPTS_MALFORMED_IOCTL                (0x00000002U)
#define CPTS_TSPUSH_ALREADY_IN_FLIGHT       (0x00000003U)
#define CPTS_STACK_ALREADY_REGISTERED       (0x00000004U)
#define CPTS_STACK_NONE_REGISTERED          (0x00000005U)
#define CPTS_STACK_INVALID_CONFIG           (0x00000006U)
#define CPTS_NO_ACTIVE_EVENTS               (0x00000007U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 * \brief  CPTS Event Type Enumeration
 */
typedef enum CPTS_EVENT_TYPE_
{
    CPTS_EVENT_TIME_STAMP_PUSH          = 0x00U,
    CPTS_EVENT_TIME_STAMP_ROLLOVER      = 0x01U,
    CPTS_EVENT_TIME_STAMP_HALF_ROLLOVER = 0x02U,
    CPTS_EVENT_HARDWARE_TIME_STAMP_PUSH = 0X03U,
    CPTS_EVENT_ETHERNET_RECEIVE         = 0X04U,
    CPTS_EVENT_ETHERNET_TRANSMIT        = 0X05U,
    CPTS_EVENT_INVALID                  = -1L * INT32_MAX
}
CPTS_EventType;

/*!
 * \brief  CPTS Ethernet Message Type Enumeration
 */
typedef enum CPTS_MESSAGE_TYPE_
{
    CPTS_MESSAGE_SYNC                   = 0x00U,
    CPTS_MESSAGE_DELAY_REQ              = 0x01U,
    CPTS_MESSAGE_PDELAY_REQ             = 0x02U,
    CPTS_MESSAGE_PDELAY_RESP            = 0x03U,
    CPTS_MESSAGE_FOLLOW_UP              = 0x08U,
    CPTS_MESSAGE_DELAY_RESP             = 0x09U,
    CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP  = 0x0AU,
    CPTS_MESSAGE_ANNOUNCE               = 0x0BU,
    CPTS_MESSAGE_SIGNALING              = 0x0CU,
    CPTS_MESSAGE_MANAGEMENT             = 0x0DU,
    CPTS_MESSAGE_INVALID                = -1L * INT32_MAX
}
CPTS_MessageType;

/*!
 *  \brief Enum of mac ports to use for CPTS packets
 */
typedef enum CPTS_PORT_SELECTION_
{
    CPTS_PORT_SELECTION_MAC_NONE        = 0x00U,
    CPTS_PORT_SELECTION_MAC_1           = 0x01U,
    CPTS_PORT_SELECTION_MAC_2           = 0x02U,
    CPTS_PORT_SELECTION_MAC_BOTH        = 0x03U,
    CPTS_PORT_SELECTION_INVALID         = -1L * INT32_MAX
}
CPTS_PortSelection;

/*!
 *  \brief Enum of VLAN usage type for CPTS packets
 */
typedef enum CPTS_VLAN_TYPE_
{
    CPTS_VLAN_TYPE_NONE                 = 0x00U,
    CPTS_VLAN_TYPE_SINGLE_TAG           = 0x01U,
    CPTS_VLAN_TYPE_STACKED_TAGS         = 0x02U,
    CPTS_VLAN_TYPE_INVALID              = -1L * INT32_MAX
}
CPTS_VlanType;

/*!
 * \brief CPTS Event notify callback type
 */
typedef void (*CPTS_EventNotifyCallback)(void *hEventNotifyCallbackArg);

/*!
 *  \brief CPTS Stack Configuration Structure
 *
 *  Configuration information for registering a stack with the CPTS module
 */
typedef struct CPTS_STACK_CONFIG_
{
    void                        *eventMem;
    uint32_t                    eventCount;
    CPTS_VlanType               vlanType;
    CPTS_PortSelection          portSelection;
    CPTS_EventNotifyCallback    pEventNotifyCallback;
    void                        *hEventNotifyCallbackArg;
}
CPTS_StackConfig;

/*!
 * \brief  CPTS Event Structure
 */
typedef struct CPTS_EVENT_
{
    uint64_t            timeStamp;
    CPTS_EventType      eventType;
    CPTS_MessageType    messageType;
    uint16_t            sequenceId;
    uint16_t            portNumber;
    struct CPTS_EVENT_  *pNextEvent;
}
CPTS_Event;

/*!
 *  \brief  The CPTS module IOCTL enums
 */
enum CPTS_IOCTL_
{
    GMACSW_IOCTL_CPTS_BASE              = 0x00030000,
    /*! CPTS timestamp push IOCTL value. IOCTL param should be NULL. */
    GMACSW_IOCTL_CPTS_TIMESTAMP_PUSH    = 0x00030000,
    /*! CPTS timestamp load IOCTL value. IOCTL param should be uint64_t timestamp value. */
    GMACSW_IOCTL_CPTS_TIMESTAMP_LOAD    = 0x00030001,
    /*! CPTS stack registration IOCTL value. IOCTL param should be structure of type CPTS_StackConfig. */
    GMACSW_IOCTL_CPTS_REGISTER_STACK    = 0x00030002,
    /*! CPTS stack unregistration IOCTL value. IOCTL param should be NULL. */
    GMACSW_IOCTL_CPTS_UNREGISTER_STACK  = 0x00030003,
    /*! CPTS get event IOCTL value. IOCTL param should be a pointer to a CPTS_Event. */
    GMACSW_IOCTL_CPTS_GET_EVENT         = 0x00030004,
    /*! CPTS lookup event IOCTL value. IOCTL param should be a structure of type CPTS_LookupEventIoctlCmd. */
    GMACSW_IOCTL_CPTS_LOOKUP_EVENT      = 0x00030005,
    /*! CPTS release event IOCTL value. IOCTL param should be a CPTS_Event (previously returned by get or lookup). */
    GMACSW_IOCTL_CPTS_RELEASE_EVENT     = 0x00030006,
    /*! CPTS clear the event queue IOCTL value. IOCTL param should be NULL. */
    GMACSW_IOCTL_CPTS_CLEAR_ALL_EVENTS  = 0x00030007,
    /*!CPTS get frequency IOCTL value. IOCTL param should be uint32_t pointer. */
    GMACSW_IOCTL_CPTS_GET_FREQUENCY     = 0x00030008,
    /*! CPTS get frequency IOCTL value. IOCTL param should be uint32_t pointer. */
    GMACSW_IOCTL_CPTS_SET_FREQUENCY     = 0x00030009
};

/*!
 * \brief CPTS Event Lookup IOCTL command structure.
 */
typedef struct CPTS_LOOKUP_EVENT_IOCTL_CMD_
{
    /*! Pointer to event template */
    CPTS_Event       *pEventTemplate;
    /*! Pointer to pointer to return event */
    CPTS_Event       **pReturnEvent;
}
CPTS_LookupEventIoctlCmd;

/*!
 *  @}
 */

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup CPTS_CONFIG_DEFINITIONS CPTS Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the CPTS
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*!
 *  \brief CPTS Module Init Configuration Structure
 *
 *  Configuration information for CPTS modules provided during initialization.
 */
typedef struct CPTS_MODULE_CONFIG_
{
    uint32_t    enableCPTSEvents;
    uint32_t    cptsInputFrequency;
}
CPTS_Config;

/*!
 * @}
 * @}
 */

/*!
 * \brief  Opaque handle for CPTS State structure
 */
typedef struct CPTS_STATE_ *CPTS_Handle;


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
 * \brief CPTS module open function
 */
extern CPTS_Handle  CPTS_open(const CPTS_Config *pCptsConfig);

/*!
 * \brief CPTS module close function
 */
extern uint32_t     CPTS_close(CPTS_Handle hCptsState);

/*!
 * \brief API for CPTS IOCTL handling
 */
extern uint32_t     CPTS_ioctl(CPTS_Handle hCpts, uint32_t cmd, void *param, uint32_t size);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CPTS_H_ */
