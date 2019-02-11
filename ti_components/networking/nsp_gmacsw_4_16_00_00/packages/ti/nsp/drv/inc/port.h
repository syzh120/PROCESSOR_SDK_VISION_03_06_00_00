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
 *      Header file for PORT module of GMAC SW subsystem.
 *
 */


#ifndef PORT_H_
#define PORT_H_

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


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! Define success and error status values */
#define PORT_SUCCESS                            (0x00000000U)
#define PORT_FAILURE                            (0xFFFFFFFFU)
#define PORT_UNKNOWN_IOCTL                      (0x00000001U)
#define PORT_MALFORMED_IOCTL                    (0x00000002U)
#define PORT_PRIORITY_ALREADY_MAPPED            (0x00000003U)
#define PORT_UNTAGGED_PRIORITY_UNMAPPED         (0x00000004U)
#define PORT_PRIORITY_TYPE_UNKNOWN              (0x00000005U)
#define PORT_NO_RX_PRIORITY_MAPPINGS_AVAILABLE  (0x00000006U)
#define PORT_RX_PRIORITY_MAPPING_INVALID        (0x00000007U)
#define PORT_INVALID_PARAM                      (0x00000008U)
#define PORT_NO_TX_PRIORITY_MAPPINGS_AVAILABLE  (0x00000009U)
#define PORT_TX_PRIORITY_MAPPING_INVALID        (0x0000000AU)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief Enum of possible switch priorities
 */
typedef enum PORT_SWITCH_PRIORITY_
{
    PORT_SWITCH_PRIORITY_UNUSED     = -1,
    PORT_SWITCH_PRIORITY_NONE       = 0x00U,
    PORT_SWITCH_PRIORITY_LOW        = 0x01U,
    PORT_SWITCH_PRIORITY_MEDIUM     = 0x02U,
    PORT_SWITCH_PRIORITY_HIGH       = 0x03U,
    PORT_SWITCH_PRIORITY_INVALID    = -1L * INT32_MAX
}
PORT_SwitchPriority;

/*!
 *  \brief Enum of source mac ports for priortity map
 */
typedef enum PORT_RX_SOURCE_
{
    PORT_RX_SOURCE_NONE             = 0x00U,
    PORT_RX_SOURCE_MAC_1            = 0x01U,
    PORT_RX_SOURCE_MAC_2            = 0x02U,
    PORT_RX_SOURCE_MAC_BOTH         = 0x03U,
    PORT_RX_SOURCE_INVALID          = -1L * INT32_MAX
}
PORT_RxSource;

/*!
 *  \brief Enum of destination mac ports for priortity map
 */
typedef enum PORT_TX_DEST_
{
    PORT_TX_DEST_NONE               = 0x00U,
    PORT_TX_DEST_MAC_1              = 0x01U,
    PORT_TX_DEST_MAC_2              = 0x02U,
    PORT_TX_DEST_MAC_BOTH           = 0x03U,
    PORT_TX_DEST_INVALID            = -1L * INT32_MAX
}
PORT_TxDest;

/*!
 *  \brief Enum of possible priority settings
 */
typedef enum PORT_RX_PRIORITY_TYPE_
{
    /*! Priority mapping type for all data with no VLAN tagging */
    PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED  = 0x00U,
    /*! Priority mapping type IPv4 diffserv packets */
    PORT_RX_PRIORITY_TYPE_IPV4_DIFFSERV = 0x01U,
    /*! Priority mapping type for VLAN tagged packets with VLAN ID of zero (known as priority tagging)*/
    PORT_RX_PRIORITY_TYPE_PRI_TAGGED    = 0x02U,
    /*! Priority mapping type for VLAN tagged packets with full VLAN tag */
    PORT_RX_PRIORITY_TYPE_VLAN_TAGGED   = 0x03U,
    PORT_RX_PRIORITY_TYPE_INVALID       = -1L * INT32_MAX
}
PORT_RxPriorityType;

typedef struct
{
    uint32_t priority;
}
PORT_RxPriorityAllUntagged;

typedef struct
{
    uint32_t priority;
    uint32_t dscp;
}
PORT_RxPriorityIPv4DiffServ;

typedef struct
{
    uint32_t priority;
}
PORT_RxPriorityPriTagged;

typedef struct
{
    uint32_t priority;
    uint32_t vlanID;
}
PORT_RxPriorityVlanTagged;

/* NOTE: MISRA-C:2004 Deviation from Rule 18.4 - union is used */
/*! Type definition of a union, used to hold the priority mapping options. */
typedef union PORT_RX_PRIORITY_OPTION_
{
    PORT_RxPriorityAllUntagged      untagged;
    PORT_RxPriorityIPv4DiffServ     diffserv;
    PORT_RxPriorityPriTagged        priTagged;
    PORT_RxPriorityVlanTagged       vlanTagged;
}
PORT_RxPriorityOption;

/*!
 * \brief PORT Rx priority configuration structure
 */
typedef struct PORT_RX_PRIORITY_CONFIG_
{
    /*! Handle to the receive channel for which the priority mapping is being applied */
    CPDMA_ChannelHandle     hCpdmaRxChannel;
    /*! The switch priority value for the mapping (HIGH, MEDIUM, LOW, NONE) */
    PORT_SwitchPriority     switchPriority;
    /*! The port/mac source for which this mapping applies */
    PORT_RxSource           rxSource;
    /*! The priority mapping type */
    PORT_RxPriorityType     rxPriorityType;
    /*! The priority options for the mapping of this type */
    PORT_RxPriorityOption   rxPriorityOption;
}
PORT_RxPriorityConfig;

/*!
 * \brief PORT Tx priority configuration structure
 */
typedef struct PORT_TX_PRIORITY_CONFIG_
{
    /*! The switch priority value for the mapping (HIGH, MEDIUM, LOW, NONE) */
    PORT_SwitchPriority     switchPriority;
    /*! The port/mac destination for which this mapping applies */
    PORT_TxDest             txDest;
    /*! The packet priority value for the mapping */
    uint32_t                priority;
}
PORT_TxPriorityConfig;

/*!
 * \brief  Opaque handle for PORT_RxPriorityMap structure
 */
typedef struct PORT_RX_PRIORITY_MAP_ *PORT_RxPriorityMapHandle;

/*!
 * \brief  Opaque handle for PORT_TxPriorityMap structure
 */
typedef struct PORT_TX_PRIORITY_MAP_ *PORT_TxPriorityMapHandle;

/*!
 * \brief  Opaque handle for PORT_TxRateLimit structure
 */
typedef struct PORT_TX_RATE_LIMIT_ *PORT_TxRateLimitHandle;

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief  The PORT module IOCTL enums
 */
enum PORT_IOCTL_
{
    GMACSW_IOCTL_PORT_BASE                          = 0x00050000,
    /*! Port add receive priority mapping IOCTL value. IOCTL param should be a structure of type PORT_AddRxPriorityMappingIoctlCmd. */
    GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING       = 0x00050000,
    /*! Port add receive priority mapping IOCTL value. IOCTL param should be a handle of type PORT_RxPriorityMapHandle,
     *  which was returned by the add receive priority mapping IOCTL call.
     */
    GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING    = 0x00050001,
    /*! Port add transmit rate limit IOCTL value. Not yet implmented. */
    GMACSW_IOCTL_PORT_ADD_TX_RATE_LIMIT_MAP         = 0x00050002,
    /*! Port remove transmit rate limit IOCTL value. Not yet implmented. */
    GMACSW_IOCTL_PORT_REMOVE_TX_RATE_LIMIT_MAP      = 0x00050003,
    /*! Port add transmit priority mapping IOCTL value. IOCTL param should be a structure of type PORT_AddTxPriorityMappingIoctlCmd. */
    GMACSW_IOCTL_PORT_ADD_TX_PRIORITY_MAPPING       = 0x00050004,
    /*! Port add transmit priority mapping IOCTL value. IOCTL param should be a handle of type PORT_TxPriorityMapHandle,
     *  which was returned by the add receive priority mapping IOCTL call.
     */
    GMACSW_IOCTL_PORT_REMOVE_TX_PRIORITY_MAPPING    = 0x00050005
};

/*!
 *  \brief  IOCTL param structure for the add receive priority mapping IOCTL.
 */
typedef struct PORT_ADD_RX_PRIORTIY_MAPPING_IOCTL_CMD_
{
    /*! Pointer to a config structure of type PORT_RxPriorityConfig. */
    PORT_RxPriorityConfig       *pPriConfig;
    /*! Pointer to a handle of type PORT_RxPriorityMapHandle, which receives the return
     *  value of the add receive priority mapping IOCTL.
     */
    PORT_RxPriorityMapHandle    *pRxPriorityMapHandle;
}
PORT_AddRxPriorityMappingIoctlCmd;

/*!
 *  \brief  IOCTL param structure for the add transmit priority mapping IOCTL.
 */
typedef struct PORT_ADD_TX_PRIORTIY_MAPPING_IOCTL_CMD_
{
    /*! Pointer to a config structure of type PORT_TxPriorityConfig. */
    PORT_TxPriorityConfig       *pPriConfig;
    /*! Pointer to a handle of type PORT_TxPriorityMapHandle, which receives the return
     *  value of the add transmit priority mapping IOCTL.
     */
    PORT_TxPriorityMapHandle    *pTxPriorityMapHandle;
}
PORT_AddTxPriorityMappingIoctlCmd;

/*!
 *  @}
 */

/*!
 * \brief  Opaque handle for PORT_State structure
 */
typedef struct PORT_STATE_ *PORT_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern PORT_Handle PORT_open(void);
extern uint32_t PORT_close(PORT_Handle hPort);

extern uint32_t PORT_ioctl(PORT_Handle hPort, uint32_t cmd, void *param, uint32_t size);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */

