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
 *   \file  ale.h
 *
 *   \brief
 *      Header file for ALE of GMAC SW subsystem.
 *
 */


#ifndef ALE_H_
#define ALE_H_

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

/* Number of switch ports in the subsystem */
#define ALE_NUM_PORTS                ((uint32_t)3U)

/* Success and error return codes */
#define ALE_SUCCESS                                 ((uint32_t)0x00000000U)
#define ALE_FAILURE                                 ((uint32_t)0xFFFFFFFFU)
#define ALE_UNKNOWN_IOCTL                           ((uint32_t)0x00000001U)
#define ALE_MALFORMED_IOCTL                         ((uint32_t)0x00000002U)
#define ALE_TABLE_FULL                              ((uint32_t)0x00000003U)
#define ALE_VLAN_UNAWARE_MODE                       ((uint32_t)0x80000004U)
#define ALE_ADDRESS_NOT_FOUND                       ((uint32_t)0x80000005U)
#define ALE_VLAN_NOT_FOUND                          ((uint32_t)0x80000006U)
#define ALE_INVALID_PARAM                           ((uint32_t)0x00000007U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup ALE_CONFIG_DEFINITIONS MAC Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the ALE
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*!
 *  \brief  Enumerates port state configuration values in address lookup engine.
 *
 *  port state Config Options
 *
 */
typedef enum ALE_PORTSTATE_TYPE_
{
    ALE_PORT_STATE_DISABLED = 0x00U,
    /*! Port is disabled in address lookup engine. */
    ALE_PORT_STATE_BLOCKED = 0x01U,
    /*! Port is blocked in address lookup engine. */
    ALE_PORT_STATE_LEARN = 0x02U,
    /*! Port is configured for learning in address lookup engine. */
    ALE_PORT_STATE_FWD = 0x03U
    /*! Port is configured to forward in address lookup engine. */
}ALE_portStateType;

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief The ALE module IOCTL enums
 */
enum ALE_IOCTL_
{
    GMACSW_IOCTL_ALE_BASE               = 0x00010000,
    /*! ALE add multicast IOCTL value */
    GMACSW_IOCTL_ALE_ADD_MULTICAST      = 0x00010000,
    /*! ALE add unicast IOCTL value */
    GMACSW_IOCTL_ALE_ADD_UNICAST        = 0x00010001,
    /*! ALE add OUI IOCTL value */
    GMACSW_IOCTL_ALE_ADD_OUI            = 0x00010002,
    /*! ALE add VLAN IOCTL value */
    GMACSW_IOCTL_ALE_ADD_VLAN           = 0x00010003,
    /*! ALE remove address IOCTL value */
    GMACSW_IOCTL_ALE_REMOVE_ADDR        = 0x00010004,
    /*! ALE remove VLAN IOCTL value */
    GMACSW_IOCTL_ALE_REMOVE_VLAN        = 0x00010005,
    /*! ALE immediate timeout IOCTL value */
    GMACSW_IOCTL_ALE_TIMEOUT            = 0x00010006,
    /*! ALE table dump IOCTL value */
    GMACSW_IOCTL_ALE_DUMP_TABLE         = 0x00010007,
    /*! ALE lookup address IOCTL value */
    GMACSW_IOCTL_ALE_LOOKUP_ADDR        = 0x00010008,
    /*! ALE lookup VLAN IOCTL value */
    GMACSW_IOCTL_ALE_LOOKUP_VLAN        = 0x00010009,
    /*! ALE set multicast IOCTL value. IOCTL param should be a structure of type ALE_MulticastIoctlCmd. */
    GMACSW_IOCTL_ALE_SET_MULTICAST      = 0x0001000A,
    /*! ALE clear multicast OCTL value. IOCTL param should be a structure of type ALE_MulticastIoctlCmd. */
    GMACSW_IOCTL_ALE_CLEAR_MULTICAST    = 0x0001000B,
    /*! ALE set receive filter field IOCTL value. IOCTL param should be a uint32_t value. */
    GMACSW_IOCTL_ALE_SET_RX_FILTER      = 0x0001000C,
    /*! ALE get receive filter field IOCTL value. IOCTL param should be a pointer to a uint32_t value. */
    GMACSW_IOCTL_ALE_GET_RX_FILTER      = 0x0001000D
};

/*! Param structure for ALE Get/Set Multicast IOCTLs */
typedef struct ALE_MULTICAST_IOCTL_CMD_
{
    /*!
     * \brief  Count of addresses to add
     */
    uint32_t    addrCount;
    /*!
     * \brief  Pointer to multicast address list (contains 'addrCount' * 6 bytes)
     */
    uint8_t     *pMCastList;
}
ALE_MulticastIoctlCmd;

/*! Param structure for ALE Add VLAN IOCTL */
typedef struct ALE_ADD_VLAN_IOCTL_CMD_
{
    /*! Vlan ID to add */
    uint32_t    vlanId;
    /*! Port member mask for the VLAN entry being added */
    uint32_t    vlanMemberList;
    /*! Unregistered multicast flood mask - Mask used for multicast when the multicast address is not found*/
    uint32_t    unregMcastFloodMask;
    /*! Registered multicast flood mask - Mask used for multicast when the multicast address is found */
    uint32_t    regMcastFloodMask;
    /*! Force untagged egress bit flags - Causes the packet VLAN tag to be removed on egress.*/
    uint32_t    forceUntaggedEgress;
}
ALE_AddVlanIoctlCmd;

/*! Function pointer type for ALE Dump IOCTL */
typedef int (*ALE_TableDumpPrintFxn)(const char* arg,...);

/*!
 * @}
 */

typedef enum _ALE_DATA_TYPE_
{
    BROADCAST               = 0x00U,
    MULTICAST               = 0x01U,
    UNICAST                 = 0x02U,
    ALE_DATA_TYPE_INVALID   = -1L*INT32_MAX
}
ALE_DataType;

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup ALE_CONFIG_DEFINITIONS ALE Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the ALE
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*! ALE mode config options */
enum ALE_MODE_CONFIG_
{
    /*! Enable ALE                                                             */
    ALE_CONFIG_ENABLE       = 0x00001U,
    /*! Clear ALE Address table.                                               */
    ALE_CONFIG_CLRTABLE     = 0x00002U,
    /*! Age out address table now                                              */
    ALE_CONFIG_AGEOUTNOW    = 0x00004U,
    /*! Learn no VID                                                           */
    ALE_CONFIG_LEARNNOVID   = 0x00008U,
    /*! Enable VLAN ID = 0 Mode                                                */
    ALE_CONFIG_ENVID0MODE   = 0x00010U,
    /*! Enable OUI Deny Mode                                                   */
    ALE_CONFIG_ENOUIDENY    = 0x00020U,
    /*! ALE bypass mode                                                        */
    ALE_CONFIG_ALEBYPASS    = 0x00040U,
    /*! Rate limit transmit mode                                               */
    ALE_CONFIG_RATELIMITTX  = 0x00080U,
    /*! ALE Vlan Aware                                                         */
    ALE_CONFIG_ENVLANAWARE  = 0x00100U,
    /*! Enable MAC Authorization mode                                          */
    ALE_CONFIG_ENAUTHMODE   = 0x00200U,
    /*! Enable broadcast and multicast rate limit                              */
    ALE_CONFIG_ENRATELIMIT  = 0x00400U
};


/*!
 *  Packet Filtering Settings (cumulative)
 */
enum ALE_RXFILTER_
{
    /*! Receive filter set to Nothing */
    ALE_RXFILTER_NOTHING        = 0x0000U,
    /*! Receive filter set to Direct */
    ALE_RXFILTER_DIRECT         = 0x0001U,
    /*! Receive filter set to Broadcast */
    ALE_RXFILTER_BROADCAST      = 0x0002U,
    /*! Receive filter set to Multicast */
    ALE_RXFILTER_MULTICAST      = 0x0003U,
    /*! Receive filter set to All Mcast */
    ALE_RXFILTER_ALLMULTICAST   = 0x0004U,
    /*! Receive filter set to All */
    ALE_RXFILTER_ALL            = 0x0005U
};

/*!
 *  \brief ALE Port configuration
 *
 *  This data structure contains configuration items related to the
 *  ALE_Port_Control register fields.
 */
typedef struct ALE_PORT_CONFIG_
{
    uint32_t        bcastLimit;
    /*!< Broadcast Packet Rate Limit                                          */
    uint32_t        mcastLimit;
    /*!< Multicast Packet Rate Limit                                          */
    uint32_t        noLearn;
    /*!< No Learn mode                                                        */
    uint32_t        vidIngressCheck;
    /*!< VLAN ID Ingress Check                                                */
    uint32_t        dropUntagged;
    /*!< Drop untagged packets                                                */
    uint32_t        portState;
    /*!< Port State: 0-disabled, 1-blocked, 2-learn, 3-forward                */
}
ALE_PortConfig;

/*!
 *  \brief ALE configuration
 *
 *  This data structure contains configuration items related to the
 *  ALE_CONTROL register fields.
 */
typedef struct ALE_MODULE_CONFIG_
{
    /*! ALE Control fields                                                      */
    uint32_t        defaultAleModeFlags;
    /*! ALE Prescale value                                                      */
    uint32_t        alePrescale;
    /*! ALE Ticks for this timer                                                */
    uint32_t        aleTimeOutTicks;
    /*! ALE Default receive filter settings                                     */
    uint32_t        defaultRxFilter;
    /*! Unknown VLAN Force Untagged Egress (except on port 2)                   */
    uint8_t         unknownForceUntaggedEgress;
    /*! Unknown VLAN Registered Multicast Flood Mask                            */
    uint8_t         unknownRegMcastFloodMask;
    /*! Unknown VLAN Multicast Flood Mask                                       */
    uint8_t         unknownMcastFloodMask;
    /*! Unknown VLAN Member List                                                */
    uint8_t         unknownVlanMemberList;
    /*! Default Port VLAN ID                                                    */
    uint32_t        defaultPortVID;
    /*! ALE Port Configs                                                        */
    ALE_PortConfig  alePortCfg[ALE_NUM_PORTS];
}
ALE_Config;

/*!
 *  @}
 *  @}
 */

/*!
 * \brief  Opaque handle for ALE State structure
 */
typedef struct ALE_STATE_ *ALE_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern ALE_Handle   ALE_open(ALE_Config *pALEConfig, const uint8_t *macAddr);
extern uint32_t     ALE_close(ALE_Handle hAle);
extern uint32_t     ALE_ioctl(ALE_Handle hAle, uint32_t cmd, void *param, uint32_t size);

extern void ALE_dumpTable(int(*printFunctionPtr)(const char* str,...));


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* ALE_H_ */


