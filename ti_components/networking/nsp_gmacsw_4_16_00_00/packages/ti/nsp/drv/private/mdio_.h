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


#ifndef MDIO__H_
#define MDIO__H_

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
#include "mdio.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* PHY Register Addresses */
#define PHY_BMCR            ((uint32_t)0x00U)
#define PHY_BMSR            ((uint32_t)0x01U)
#define PHY_PHYIDR1         ((uint32_t)0x02U)
#define PHY_PHYIDR2         ((uint32_t)0x03U)
#define PHY_ANAR            ((uint32_t)0x04U)
#define PHY_ANLPAR          ((uint32_t)0x05U)
#define PHY_ANER            ((uint32_t)0x06U)
#define PHY_ANNPTR          ((uint32_t)0x07U)
#define PHY_ANLPNP          ((uint32_t)0x08U)
#define PHY_1000BTCR        ((uint32_t)0x09U)
#define PHY_1000BTSR        ((uint32_t)0x0AU)
#define PHY_EXSR            ((uint32_t)0x0FU)
#define PHY_PHYSTS          ((uint32_t)0x10U)
#define PHY_MIPSCR          ((uint32_t)0x11U)
#define PHY_MIPGSR          ((uint32_t)0x12U)
#define PHY_DCR             ((uint32_t)0x13U)
#define PHY_FCSCR           ((uint32_t)0x14U)
#define PHY_RECR            ((uint32_t)0x15U)
#define PHY_PCSR            ((uint32_t)0x16U)
#define PHY_LBR             ((uint32_t)0x17U)
#define PHY_10BTSCR         ((uint32_t)0x18U)
#define PHY_PHYCTRL         ((uint32_t)0x19U)

/* National DP83865 */
#define PHY_STRAP_REG       (0x10U)
#define PHY_LINK_AN         (0x11U)
#define PHY_AUX_CTRL        (0x12U)
#define PHY_LED_CTRL        (0x13U)
#define PHY_BIST_CNT        (0x18U)
#define PHY_BIST_CFG1       (0x19U)
#define PHY_BIST_CFG2       (0x1AU)

/*National DP83867IR */
#define DP83867_DEVADDR        (0x1FU)
#define MII_DP83867_PHYCTRL    (0x10U)
#define MII_DP83867_MICR    (0x12U)
#define MII_DP83867_ISR        (0x13U)
#define DP83867_REGCR        (0xDU)
#define DP83867_ADDAR        (0xEU)
#define DP83867_CTRL        (0x1FU)

#define    DP83867_WRITE_INDIRECT_NOPOSTINCREMENT 0x401F

/* Atheros/Qualcomm AR803x */


/*------------------- Hardware Register Fields ---------------------*/

/* PBCR fields */
#define MII_PHY_RESET           ((uint32_t)1U<<15U)
#define MII_PHY_LOOP            ((uint32_t)1U<<14U)
#define MII_PHY_100             ((uint32_t)1U<<13U)
#define MII_AUTO_NEGOTIATE_EN   ((uint32_t)1U<<12U)
#define MII_PHY_PDOWN           ((uint32_t)1U<<11U)
#define MII_PHY_ISOLATE         ((uint32_t)1U<<10U)
#define MII_RENEGOTIATE         ((uint32_t)1U<<9U)
#define MII_PHY_FD              ((uint32_t)1U<<8U)
#define MII_PHY_1000            ((uint32_t)1U<<6U)

/* PBSR fields */
#define MII_EXTENDED_STATUS     ((uint32_t)1U<<8U)
#define MII_NWAY_COMPLETE       ((uint32_t)1U<<5U)
#define MII_NWAY_CAPABLE        ((uint32_t)1U<<3U)
#define MII_PHY_LINKED          ((uint32_t)1U<<2U)

/* PHY_ANAR fields */
#define MII_NWAY_FD100          ((uint32_t)1U<<8U)
#define MII_NWAY_HD100          ((uint32_t)1U<<7U)
#define MII_NWAY_FD10           ((uint32_t)1U<<6U)
#define MII_NWAY_HD10           ((uint32_t)1U<<5U)
#define MII_NWAY_SEL            ((uint32_t)1U<<0U)

/* PHY_1000BTCR fields */
#define MII_NWAY_MY_FD1000      ((uint32_t)1U<<9U)
#define MII_NWAY_MY_HD1000      ((uint32_t)1U<<8U)

/* PHY_1000BTSR fields */
#define MII_NWAY_REM_FD1000     ((uint32_t)1U<<11U)
#define MII_NWAY_REM_HD1000     ((uint32_t)1U<<10U)

/* PHY_EXSR fields */
#define MII_EXSR_FD1000X        ((uint32_t)1U<<15U)
#define MII_EXSR_HD1000X        ((uint32_t)1U<<14U)
#define MII_EXSR_FD1000T        ((uint32_t)1U<<13U)
#define MII_EXSR_HD1000T        ((uint32_t)1U<<12U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct PHY_DEVICE_
{
    uint32_t    isFound;
    uint32_t    macNum;
    uint32_t    phyAddr;
    uint32_t    phyMode;
    uint32_t    phyState;
    uint32_t    MdixMask;
    uint32_t    phyMask;
    uint32_t    MLinkMask;
    uint32_t    isGigabitPHY;
    PHY_Status  phyStatus;
}
PHY_Device;

typedef struct MDIO_STATE_
{
    uint32_t highestChannel;

    uint32_t miibase;

    PHY_Device phy[2];

    MDIO_phyFoundCallback   phyFoundCallback;
}
MDIO_State;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern uint32_t MDIO_phyInit(MDIO_Handle hMdio, uint32_t macNum, const PHY_Config *pConfig);

extern uint32_t MDIO_getLinkStatus(MDIO_Handle hMdio, uint32_t macNum, uint32_t *linkStatus);

extern uint32_t MDIO_getPhyAddr(MDIO_Handle hMdio, uint32_t macNum, uint32_t *pPhyAddr);

extern uint32_t MDIO_updatePhyStatus(MDIO_Handle hMdio, uint32_t macNum);

extern uint32_t MDIO_setPhyMode(MDIO_Handle hMdio, uint32_t macNum, uint32_t phyMode);

extern uint32_t MDIO_getPhyMode(MDIO_Handle hMdio, uint32_t macNum, uint32_t *pPhyMode);

extern uint32_t MDIO_userAccessRead(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t *data);
extern uint32_t MDIO_userAccessWrite(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t data);
extern uint32_t MDIO_userAccessWriteIndirect(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t data);
extern uint32_t MDIO_userAccessReadIndirect(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t *data);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif


#endif /* _MDIO__H_ */
