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
 *   \file  mac.h
 *
 *   \brief
 *      Header file for MAC/Sliver modules of GMAC SW subsystem.
 *
 */


#ifndef MAC_H_
#define MAC_H_

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
#include "mdio.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Number of mac ports in the subsystem */
#define MAC_NUM_PORTS                ((uint32_t)2U)

/*! MAC module return codes */
#define MAC_SUCCESS                 (0x00000000U)
#define MAC_FAILURE                 (0xFFFFFFFFU)
#define MAC_UNKNOWN_IOCTL           (0x00000001U)
#define MAC_MALFORMED_IOCTL         (0x00000002U)

#define MAC_CONFIG_MODEFLG_CHPRIORITY           0x00001U
/*!< Use Tx channel priority                                                */
#define MAC_CONFIG_MODEFLG_MACLOOPBACK          0x00002U
/*!< MAC internal loopback                                                  */
#define MAC_CONFIG_MODEFLG_RXCRC                0x00004U
/*!< Include CRC in RX frames                                               */
#define MAC_CONFIG_MODEFLG_TXCRC                0x00008U
/*!< Tx frames include CRC                                                  */
#define MAC_CONFIG_MODEFLG_PASSERROR            0x00010U
/*!< Pass error frames                                                      */
#define MAC_CONFIG_MODEFLG_PASSCONTROL          0x00020U
/*!< Pass control frames                                                    */
#define MAC_CONFIG_MODEFLG_PASSALL              0x00040U
/*!< pass all frames                                                        */
#define MAC_CONFIG_MODEFLG_RXQOS                0x00080U
/*!< Enable QOS at receive side                                             */
#define MAC_CONFIG_MODEFLG_RXNOCHAIN            0x00100U
/*!< Select no buffer chaining                                              */
#define MAC_CONFIG_MODEFLG_RXOFFLENBLOCK        0x00200U
/*!< Enable offset/length blocking                                          */
#define MAC_CONFIG_MODEFLG_RXOWNERSHIP          0x00400U
/*!< Use ownership bit as 1                                                 */
#define MAC_CONFIG_MODEFLG_RXFIFOFLOWCNTL       0x00800U
/*!< Enable rx fifo flow control                                            */
#define MAC_CONFIG_MODEFLG_CMDIDLE              0x01000U
/*!< Enable IDLE command                                                    */
#define MAC_CONFIG_MODEFLG_TXSHORTGAPEN         0x02000U
/*!< Enable tx short gap                                                    */
#define MAC_CONFIG_MODEFLG_TXPACE               0x04000U
/*!< Enable tx pacing                                                       */
#define MAC_CONFIG_MODEFLG_TXFLOWCNTL           0x08000U
/*!< Enable tx flow control                                                 */
#define MAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL     0x10000U
/*!< Enable rx buffer flow control                                          */


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief  The MAC module IOCTL enums. Currently there are none.
 */
enum MAC_IOCTL_
{
    GMACSW_IOCTL_MAC_BASE   = 0x00060000
};

/*!
 * @}
 */


/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup MAC_CONFIG_DEFINITIONS MAC Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the MAC
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*!
 *  \brief  Type/Speed/Duplex Connection Config Options
 *
 *  Connection Config Options
 *
 */
typedef enum MAC_CONNECTION_TYPE_
{
    /*! MAC connection type for 10Mbps MII mode */
    MAC_CONNECTION_TYPE_MII_10                  = 0x00U,
    /*! MAC connection type for 100Mbps MII mode */
    MAC_CONNECTION_TYPE_MII_100                 = 0x01U,
    /*! MAC connection type for 10Mbps RMII mode */
    MAC_CONNECTION_TYPE_RMII_10                 = 0x02U,
    /*! MAC connection type for 100Mbps RMII mode */
    MAC_CONNECTION_TYPE_RMII_100                = 0x03U,
    /*! MAC connection type for forced half-duplex 100Mbps RGMII mode */
    MAC_CONNECTION_TYPE_RGMII_FORCE_100_HALF    = 0x04U,
    /*! MAC connection type for forced full-duplex 100Mbps RGMII mode */
    MAC_CONNECTION_TYPE_RGMII_FORCE_100_FULL    = 0x05U,
    /*! MAC connection type for forced full-duplex 1000Mbps RGMII mode */
    MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL   = 0x06U,
    /*! MAC connection type for RGMII inband detection mode (speed determined based on received RGMII Rx clock) */
    MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND     = 0x07U,
    MAC_CONNECTION_TYPE_INVALID                 = -1L * INT32_MAX
}
MAC_ConnectionType;

/*!
 *  \brief Enum of mac ports for enable mask
 */
typedef enum MAC_PORTMASK_
{
    PORT_MASK_MAC_1            = 0x01U,
    PORT_MASK_MAC_2            = 0x02U,
    PORT_MASK_MAC_BOTH         = 0x03U
}
MAC_portMask;


/*!
 *  \brief CPGMAC SL Init Configuration
 *
 *  Configuration information for MAC modules provided during initialization.
 */
typedef struct MAC_CONFIG_
{
    /*! MAC address                                                            */
    uint8_t             macAddr[6];
    /*! Packet MTU for this MAC                                                */
    uint32_t            PktMTU;
    /*! Phy Mask for this MAC Phy                                              */
    uint32_t            phyMask;
    /*! MLink Mask for this MAC Phy                                            */
    uint32_t            MLinkMask;
    /*! Port VLAN priority (7 is highest)                                      */
    uint32_t            portPri;
    /*! Port CFI bit                                                           */
    uint32_t            portCfi;
    /*! Port VLAN ID                                                           */
    uint32_t            portVID;
    /*! MAC Connection Type                                                    */
    MAC_ConnectionType  macConnectionType;
    /*! Configuation Mode Flags                                                */
    uint32_t            macModeFlags;
    /*! MDIO configuration flags for this MAC port                             */
    uint32_t            mdioModeFlags;
}
MAC_Config;

/*!
 * @}
 * @}
 */

/*!
 * \brief  Opaque handle for MAC State structure
 */
typedef struct MAC_STATE_ *MAC_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern MAC_Handle   MAC_open(MAC_Config *pMACConfig, uint32_t macNum);
extern uint32_t     MAC_close(MAC_Handle hMac);

extern uint32_t     MAC_ioctl(MAC_Handle hMac, uint32_t cmd, void *param, uint32_t size);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* MAC_H_ */

