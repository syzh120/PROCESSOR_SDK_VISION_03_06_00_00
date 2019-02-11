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
 *   \file  mac.c
 *
 *   \brief
 *          Sliver/GMAC module implementation
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
#include "private/mdio_.h"

/* This module's private header */
#include "private/mac_.h"

/* This module's header */
#include "mac.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#if defined(DEVICE_VAYU)
/* CONTROL MODULE Lock register defines for Vayu */
#define CTRL_CORE_MMR_LOCK_1        (*(volatile uint32_t*)0x4A002540)
#define CTRL_CORE_MMR_LOCK_1_LOCK   (uint32_t)(0x1A1C8144)
#define CTRL_CORE_MMR_LOCK_1_UNLOCK (uint32_t)(0x2FF1AC2B)
#endif

/* GMII_SEL defines */
#if (defined(DEVICE_J5ECO) || defined(DEVICE_CENTAURUS))
#define GMII_SEL                    (*(volatile uint32_t*)0x48140650U)
#define GMII_SEL_SHIFT              (2U)
#elif defined(DEVICE_VAYU)
#define GMII_SEL                    (*(volatile uint32_t*)0x4A002554U)
#define GMII_SEL_SHIFT              (4U)
#elif defined(DEVICE_AEGIS)
#define GMII_SEL                    (*(volatile uint32_t*)0x44E10000U)

#endif

#define GMII_SEL_GMII_MODE          (0x0U)
#define GMII_SEL_RMII_MODE          (0x1U)
#define GMII_SEL_RGMII_MODE         (0x2U)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_setConfig(MAC_State *pMACState);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
MAC_State MAC_stateObj[MAC_NUM_PORTS];
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

MAC_Handle MAC_open(MAC_Config *pMACConfig, uint32_t macNum)
{
    MAC_State   *pMACState;
    uint8_t     *macAddr;
#if defined(USE_CSLR)
    CSL_GMACSW_macRegs      *macRegs    = &(GMACSW_REGS->SL.MAC[macNum]);
    CSL_GMACSW_macPortRegs  *portRegs   = &(GMACSW_REGS->PORT.MAC_PORT[macNum]);
#endif

#if defined(NSP_DYNAMIC_ALLOCATION)
    pMACState = (MAC_State *) calloc(1U, sizeof(MAC_State));
#else
    pMACState = &MAC_stateObj[macNum];
#endif

    /* Zero init the MAC_State structure */
    memset(pMACState, 0, sizeof(MAC_State));

    /*
     * Populate the MAC State Object based on the configuration input
     */

    /* Save a pointer to the initial config structure used to open the MAC */
    pMACState->pMACConfig = pMACConfig;

    /* Save MAC number */
    pMACState->macNum = macNum;

    /*
     *  Initialize the MAC Hardware Registers
     */
#if defined(USE_CSLR)
    /* Do a soft reset of the module */
    CSL_FINS(macRegs->SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET, CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_RESET);
    while(CSL_FEXT(macRegs->SL_SOFT_RESET,GMACSW_SL_SOFT_RESET_SOFT_RESET) !=
            CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_NORESET)
    {
    }
#else
    if (0 == macNum)
    {
        GMAC_SW_SlReset(SOC_GMAC_SW_SL1_BASE);
    }
    else if (1 == macNum)
    {
        GMAC_SW_SlReset(SOC_GMAC_SW_SL2_BASE);
    }
#endif

    /* Set MacControl Register */
    LOCAL_setConfig(pMACState);

    /* Configure Mac Address */
    macAddr = &(pMACConfig->macAddr[0]);
    portRegs->P_SA_LO = ((uint32_t)macAddr[5] <<  8U) | ((uint32_t)macAddr[4] <<  0U);
    portRegs->P_SA_HI = ((uint32_t)macAddr[3] << 24U) | ((uint32_t)macAddr[2] << 16U) |
                        ((uint32_t)macAddr[1] <<  8U) | ((uint32_t)macAddr[0] <<  0U);

#if !defined(DEVICE_CENTAURUS)
    /* Disable the DSCP priority mapping by default */
    CSL_FINS(portRegs->P_CONTROL, GMACSW_P_CONTROL_DSCP_PRI_EN, 0);
#endif

    /* Configure port VLAN information */
    portRegs->P_PORT_VLAN = CSL_FMK(GMACSW_P_PORT_VLAN_PORT_PRI, pMACConfig->portPri) |
                            CSL_FMK(GMACSW_P_PORT_VLAN_PORT_CFI, pMACConfig->portCfi) |
                            CSL_FMK(GMACSW_P_PORT_VLAN_PORT_VID, pMACConfig->portVID);

    /* write rx maxlen register */
    macRegs->SL_RX_MAXLEN = pMACState->PktMTU + 4U;

    /* Finally Set the Mac Control register. Enable MII */
    macRegs->SL_MACCONTROL |= ((uint32_t)1U << CSL_GMACSW_SL_MACCONTROL_GMII_EN_SHIFT);

    return pMACState;
}

uint32_t MAC_close(MAC_Handle hMac)
{
    uint32_t retVal = MAC_SUCCESS;

    MAC_State *pMACState = (MAC_State *) hMac;
    uint32_t macNum = pMACState->macNum;

#if defined(USE_CSLR)
    CSL_GMACSW_macRegs *macRegs = &(GMACSW_REGS->SL.MAC[macNum]);

    /* Do a soft reset of the module */
    CSL_FINS(macRegs->SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET, CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_RESET);
    while(CSL_FEXT(macRegs->SL_SOFT_RESET,GMACSW_SL_SOFT_RESET_SOFT_RESET) !=
            CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_NORESET)
    {
    }
#else
    if (0 == macNum)
    {
        GMAC_SW_SlReset(SOC_GMAC_SW_SL1_BASE);
    }
    else if (1 == macNum)
    {
        GMAC_SW_SlReset(SOC_GMAC_SW_SL2_BASE);
    }
#endif

#if defined(NSP_DYNAMIC_ALLOCATION)
    free(pMACState);
#else
    memset(pMACState, 0, sizeof(MAC_State));
#endif

    return retVal;
}

uint32_t MAC_ioctl(MAC_Handle hMac, uint32_t cmd, void *param, uint32_t size)
{
    /* Get MAC address for a MAC port */
    /* Get configured MAC speed */
    /* Get configured duplex */
    return MAC_SUCCESS;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_setConfig(MAC_State *pMACState)
{
    MAC_Config *pMACConfig = pMACState->pMACConfig;
    uint32_t macNum = pMACState->macNum;
    uint32_t macControlVal = 0;

    /* Update GMII_SEL in Control Module */
#if defined(DEVICE_VAYU)
    /* Unlock the pertinent Control Module locks */
    uint32_t controlLockTemp = CTRL_CORE_MMR_LOCK_1;
    CTRL_CORE_MMR_LOCK_1 = CTRL_CORE_MMR_LOCK_1_UNLOCK;
#endif
    switch (pMACConfig->macConnectionType)
    {
        case MAC_CONNECTION_TYPE_MII_10:
        case MAC_CONNECTION_TYPE_MII_100:
            /* MII modes */
            GMII_SEL =  (GMII_SEL & ~((uint32_t)0x3U << (macNum*GMII_SEL_SHIFT))) |
                        (GMII_SEL_GMII_MODE << (macNum*GMII_SEL_SHIFT));
#if (defined(DEVICE_J5ECO) || defined(DEVICE_CENTAURUS))
            GMII_SEL =  GMII_SEL & ~(0x1U << (8 + macNum));
#endif
            break;
        case MAC_CONNECTION_TYPE_RMII_10:
        case MAC_CONNECTION_TYPE_RMII_100:
            /* RMII modes */
            GMII_SEL =  (GMII_SEL & ~((uint32_t)0x3U << (macNum*GMII_SEL_SHIFT))) |
                        (GMII_SEL_RMII_MODE << (macNum*GMII_SEL_SHIFT));
#if (defined(DEVICE_J5ECO) || defined(DEVICE_CENTAURUS))
            GMII_SEL =  GMII_SEL & ~(0x1U << (8 + macNum));
#endif
            break;
        case MAC_CONNECTION_TYPE_RGMII_FORCE_100_HALF:
        case MAC_CONNECTION_TYPE_RGMII_FORCE_100_FULL:
        case MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL:
        case MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND:
            /* RGMII modes */
            GMII_SEL =  (GMII_SEL & ~((uint32_t)0x3U << (macNum*GMII_SEL_SHIFT))) |
                        (GMII_SEL_RGMII_MODE << (macNum*GMII_SEL_SHIFT));
#if (defined(DEVICE_J5ECO) || defined(DEVICE_CENTAURUS))
            GMII_SEL =  GMII_SEL | (0x1U << (8 + macNum));
#endif
            break;
        default:
            break;
    }
#if defined(DEVICE_VAYU)
    /* Lock the pertinent Control Module locks */
    CTRL_CORE_MMR_LOCK_1 = controlLockTemp;
#endif

    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_RXCRC) != 0)
    {
        pMACState->PktMTU = (pMACConfig->PktMTU) + 4U;
    }
    else
    {
        pMACState->PktMTU = (pMACConfig->PktMTU);
    }

    /* If PASSCONTROL is set, enable control frames */
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_PASSCONTROL) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_RX_CMF_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_PASSERROR) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_RX_CEF_EN, 1U);
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_RX_CSF_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_CMDIDLE) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_CMD_IDLE, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_TXSHORTGAPEN) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_TX_SHORT_GAP_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_TXSHORTGAPEN) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_TX_SHORT_GAP_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_TXPACE) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_TX_PACE, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_TXPACE) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_TX_PACE, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_TXFLOWCNTL) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_TX_FLOW_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_RX_FLOW_EN, 1U);
    }
    if ((pMACConfig->macModeFlags & MAC_CONFIG_MODEFLG_MACLOOPBACK) != 0)
    {
        macControlVal |= CSL_FMK(GMACSW_SL_MACCONTROL_LOOPBACK, 1U);
    }

    GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL = macControlVal;

    /*
     * We put this down here on its own since in DLB mode we have to
     * enable GMII_EN bit after enabling loop back mode. When not in
     * DLB mode, we can still do it here.
     */
    switch (pMACConfig->macConnectionType)
    {
        case MAC_CONNECTION_TYPE_MII_10:
        case MAC_CONNECTION_TYPE_MII_100:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U)       &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U)          &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U)    |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U);
            break;
        case MAC_CONNECTION_TYPE_RMII_10:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U)       &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U)          &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U)    &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_IFCTL_A, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U)    |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U);
            break;
        case MAC_CONNECTION_TYPE_RMII_100:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U)       &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U)          &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U)    |
                CSL_FMK(GMACSW_SL_MACCONTROL_IFCTL_A, 1U)       |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U);
            break;
        case MAC_CONNECTION_TYPE_RGMII_FORCE_100_HALF:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U)   &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U)      &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U);
            break;
        case MAC_CONNECTION_TYPE_RGMII_FORCE_100_FULL:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U)   &
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U)   |
                CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U);
            break;
        case MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U);
            break;
        case MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND:
            macControlVal &=
                ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG_FORCE, 1U);
            macControlVal |=
                CSL_FMK(GMACSW_SL_MACCONTROL_EXT_EN, 1U) |
                CSL_FMK(GMACSW_SL_MACCONTROL_GMII_EN, 1U);
            break;
        default:
            break;
    }

    /* Update MACCONTROL with speed/duplex/type settings */
    GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL = macControlVal;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

