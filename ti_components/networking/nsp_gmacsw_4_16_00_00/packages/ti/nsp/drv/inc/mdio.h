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
 *   \file  mdio.h
 *
 *   \brief
 *      This include file contains structure definitions
 *      prototypes,macros for MDIO module.
 *
 */


#ifndef MDIO_H_
#define MDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! MDIO module return codes */
#define MDIO_SUCCESS           (0x00000000U)
#define MDIO_FAILURE           (0xFFFFFFFFU)
#define MDIO_UNKNOWN_IOCTL     (0x00000001U)
#define MDIO_MALFORMED_IOCTL   (0x00000002U)


/*!
 *  \brief  MDIO Configuration Mode Flags
 *
 *  These flags determine how the MDIO module behaves
 *
 */
#define MDIO_MODEFLG_AUTONEG                (0x0001U)
/*!< Use Autonegotiation                                                    */

/* The following bits are used for manual and fallback configuration        */
#define MDIO_MODEFLG_HD10                   (0x0002U)
/*!< Use 10Mb/s Half Duplex                                                 */
#define MDIO_MODEFLG_FD10                   (0x0004U)
/*!< Use 10Mb/s Full Duplex                                                 */
#define MDIO_MODEFLG_HD100                  (0x0008U)
/*!< Use 100Mb/s Half Duplex                                                */
#define MDIO_MODEFLG_FD100                  (0x0010U)
/*!< Use 100Mb/s Full Duplex                                                */
#define MDIO_MODEFLG_FD1000                 (0x0020U)
/*!< Use 1000Mb/s Full Duplex                                               */
#define MDIO_MODEFLG_LOOPBACK               (0x0040U)
/*!< Use internal PHY Loopback                                              */
#define MDIO_MODEFLG_NOPHY                  (0x0080U)
/*!< Use external SMA connectors instead of PHY                             */


/*------------------- Software Mode Values ---------------------*/

/* PHY Mode Values  */
#define NWAY_AUTOMDIX       ((uint32_t)1U<<16U)
#define NWAY_FD1000         ((uint32_t)1U<<13U)
#define NWAY_HD1000         ((uint32_t)1U<<12U)
#define NWAY_NOPHY          ((uint32_t)1U<<10U)
#define NWAY_LPBK           ((uint32_t)1U<<9U)
#define NWAY_FD100          ((uint32_t)1U<<8U)
#define NWAY_HD100          ((uint32_t)1U<<7U)
#define NWAY_FD10           ((uint32_t)1U<<6U)
#define NWAY_HD10           ((uint32_t)1U<<5U)
#define NWAY_AUTO           ((uint32_t)1U<<0U)

/* Tic() return values */
#define MIIMDIO_MDIXFLIP    ((uint32_t)1U<<28U)
#define AUTOMDIX_DELAY_MIN  ((uint32_t)80U)   /* milli-seconds*/
#define AUTOMDIX_DELAY_MAX  ((uint32_t)200U)  /* milli-seconds*/

/*-----------------------------------------------------------------------
 * MDIO Events
 *
 * These events are returned as result param by MDIO_Tic() to allow the application
 * (or GMACSW) to track MDIO status.
 *-----------------------------------------------------------------------*/
#define MDIO_EVENT_NOCHANGE     ((uint32_t)0U)   /* No change from previous status */
#define MDIO_EVENT_LINKDOWN     ((uint32_t)1U)   /* Link down event                */
#define MDIO_EVENT_LINKUP       ((uint32_t)2U)   /* Link (or re-link) event        */
#define MDIO_EVENT_PHYERROR     ((uint32_t)3U)   /* No PHY connected                */

/*-----------------------------------------------------------------------
 * MDIO Link Status Values
 *

 *
 *-----------------------------------------------------------------------*/
#define MDIO_LINKSTATUS_NOLINK      ((uint32_t)0U)
#define MDIO_LINKSTATUS_INVALID     ((uint32_t)1U)
#define MDIO_LINKSTATUS_HD10        ((uint32_t)2U)
#define MDIO_LINKSTATUS_FD10        ((uint32_t)3U)
#define MDIO_LINKSTATUS_HD100       ((uint32_t)4U)
#define MDIO_LINKSTATUS_FD100       ((uint32_t)5U)
#define MDIO_LINKSTATUS_FD1000      ((uint32_t)7U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*! Callback function type that application can supply as part of MDIO configuration structure */
typedef void (*MDIO_phyFoundCallback)(uint32_t portNum, uint32_t phyNum);

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief  The MDIO module IOCTL enums
 */
enum MDIO_IOCTL_
{
    GMACSW_IOCTL_MDIO_BASE           = 0x00070000U,
    /*! MDIO get link status IOCTL value. Not yet implemented. */
    GMACSW_IOCTL_MDIO_GET_LINKSTATUS = 0x00070000U,
    /*! Write to PHY register IOCTL . */
    GMACSW_IOCTL_MDIO_WRITE_PHY_REGISTER = 0x00070001U,
    /*! Read from PHY register IOCTL . */
    GMACSW_IOCTL_MDIO_READ_PHY_REGISTER = 0x00070002U,
    /*! Write to DP83867 PHY extended set of register IOCTL . */
    GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER = 0x00070003U,
    /*! Read from DP83867 PHY extended set of register IOCTL . */
    GMACSW_IOCTL_MDIO_READ_DP83867_PHY_INDIRECT_REGISTER = 0x00070004U
};

/*!
 * \brief Param struct for the mdio read/write PHY register IOCTL
 *
 * \details
 *      The param struct for mdio read/write PHY register IOCTL, portNum (0 for port1 and 1 for port2), regAddr and
 *      a pointer to a read/write data which will contain value to be written
 *      to register or value read from register.
 *
 */
typedef struct MDIO_READWRITE_PHY_IOCTL_CMD_
{
    uint32_t                portNum;
    uint32_t                regAddr;
    uint32_t                *regVal;
}
MDIO_rdWrphyRegIoctlCmd;

/*!
 * @}
 */

/*!
 *  \brief  PHY Link Status values
 *
 *  Provides PHY status of the device.
 *  The status value is constructed as follows
 *     Bit0: 0  for HalfDuplex, 1 for FullDuplex
 *     Bit[2:1]: 10Mbps- 1, 100Mbps - 2, 1000Mbps - 3
 *
 */
typedef enum MDIO_LINK_STATUS_
{
    LINKSTATUS_NOLINK       = 0x00U,
    LINKSTATUS_NOTVALID     = 0x01U,
    LINKSTATUS_HD10         = 0x02U,
    LINKSTATUS_FD10         = 0x03U,
    LINKSTATUS_HD100        = 0x04U,
    LINKSTATUS_FD100        = 0x05U,
    LINKSTATUS_HD1000       = 0x06U,
    LINKSTATUS_FD1000       = 0x07U,
    LINKSTATUS_MAX          = 0x08U,
    LINKSTATUS_INVALID      = -1L * INT32_MAX
}
MDIO_LinkStatus;

/*!
 *  \brief PHY Status values
 *
 *  Provides PHY status of the device.
 *
 */
typedef struct PHY_STATUS_
{
    uint32_t      phyLinked;
    /*!< Link status: 1=Linked, 0=No link                                     */
    uint32_t      phyDuplex;
    /*!< Duplex status: 1=Full Duplex, 0=Half Duplex                          */
    uint32_t      phySpeed;
    /*!< Link Speed = 2= 1000 mbps, 1= 100 mbps, 0= 10 mbps                   */
    uint32_t      phyNum;
    /*!< PHY number - useful if phy number is discovered                      */
}
PHY_Status;

/*!
 *  \brief PHY Init Configuration
 *
 *  Configuration information for the PHYs provided during initialization.
 */
typedef struct PHY_CONFIG_
{
    uint32_t      phyMask;
    uint32_t      macNum;
    uint32_t      MLinkMask;
    uint32_t      MdixMask;
    uint32_t      mdioModeFlags;
}
PHY_Config;

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup MDIO_CONFIG_DEFINITIONS MDIO Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the MDIO
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*!
 *  \brief MDIO Module Init Configuration
 *
 *  Configuration information for the MDIO modules provided during initialization.
 */
typedef struct MDIO_CONFIG_
{
    /*! Base address of the MDIO register block */
    uint32_t        baseAddress;

    /*! Bus frequency for the MII module */
    uint32_t        mdioBusFrequency;

    /*! Clock frequency for MDIO link */
    uint32_t        mdioClockFrequency;
    
    /*! Function pointer to application's PHY found callback for phy specific cfg */
    MDIO_phyFoundCallback   phyFoundCallback;
}
MDIO_Config;

/*!
 * @}
 * @}
 */

/*!
 * \brief  Opaque handle for MDIO State structure
 */
typedef struct MDIO_STATE_ *MDIO_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern MDIO_Handle MDIO_open(const MDIO_Config *pConfig);
extern uint32_t MDIO_close(MDIO_Handle hMdio);

extern uint32_t MDIO_ioctl(MDIO_Handle hMdio, uint32_t cmd, void *param, uint32_t size);

extern uint32_t MDIO_getPhyLink(MDIO_Handle hMdio, uint32_t macNum);

extern uint32_t MDIO_tic(MDIO_Handle hMdio, uint32_t macNum, uint32_t* mdioStatus);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif


#endif /* _MDIO_H_ */
