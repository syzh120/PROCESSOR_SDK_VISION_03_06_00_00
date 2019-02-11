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
 *   \file  gmacsw_config.c
 *
 *   \brief
 *          Configuration generation for the GMAC_SW driver.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* OS/Posix headers */

/* Project dependency headers */
#if defined(USE_CSLR)
#include "cslr.h"
#include "cslr_gmacsw.h"
#else
#include "soc.h"
#include "gmac_sw.h"
#endif
#include "cpts.h"

/* */
#include "private/gmacsw_.h"

/* This module's header */
#include "gmacsw_config.h"


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


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

/* Switch Configuration structure  */
GMACSW_Config LOCAL_configObj = {0};


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

GMACSW_Config *GMACSW_CONFIG_getDefaultConfig(void)
{
    GMACSW_Config   *pGMACSWConfig;
    CPDMA_Config    *pCPDMAConfig;
    uint32_t         i, j;

    pGMACSWConfig   = &LOCAL_configObj;

    /* Clear the GMACSW configuration structure */
    memset(pGMACSWConfig,0,sizeof(GMACSW_Config));

    /******************* Top-level config **********************/

    /* CPSW3G default config  */
    pGMACSWConfig->cpswPtypeModeFlags       = 0;
    pGMACSWConfig->escPriLdVal              = (uint8_t)GMACSW_DEFAULT_ESCPRI_LD_VAL;

    /* Set default MTU for Ethernet packets */
#if defined(ENABLE_JUMBO_FRAMES)
    /*
     * For TDA hardware maximum packet length for CPDMA can't be more that 2048
     * due to packet length being 11 bits in descriptors. Hence Jumbo packet of
     * max. 2K can be used
     */
    pGMACSWConfig->PktMTU                   = (uint32_t)2000U;
#else
    pGMACSWConfig->PktMTU                   = (uint32_t)1518U;
#endif

    pGMACSWConfig->linkStatusCallback       = NULL;

    /* Set count of active MAC ports */
    pGMACSWConfig->activeMACPortMask       = PORT_MASK_MAC_BOTH;


    /******************** CPDMA Config ************************/

    /* Program Default Dma Config */
    pCPDMAConfig = &pGMACSWConfig->cpdmaInitCfg;

    pCPDMAConfig->portPri = GMACSW_DEFAULT_DMA_PORTPRI;
    pCPDMAConfig->portCfi = GMACSW_DEFAULT_DMA_PORTCFI;
    pCPDMAConfig->portVID = GMACSW_DEFAULT_DMA_PORTVID;
    pCPDMAConfig->rxBufferOffset = GMACSW_DEFAULT_RXBUFOFF;
    pCPDMAConfig->rxInterruptPacingEnabled = 1U;
    pCPDMAConfig->rxInterruptsPerMsec = 2;
    pCPDMAConfig->txInterruptPacingEnabled = 1U;
    pCPDMAConfig->txInterruptsPerMsec = 2;
    pCPDMAConfig->pacingClkFreq = GMACSW_DEFAULT_MAINCLKFREQ;
    pCPDMAConfig->PktMTU = pGMACSWConfig->PktMTU;


    /********************* MAC Port Config **********************/

    /* Program default MAC SL config */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        /* use auto-neg */
        pGMACSWConfig->macInitCfg[i].mdioModeFlags = MDIO_MODEFLG_AUTONEG;

        if(0U == i)
        {
            /* program phy_mask for mac 0/port 1 */
            pGMACSWConfig->macInitCfg[i].phyMask = 0x1U;   /* corresponding to PHY address 0 */
            pGMACSWConfig->macInitCfg[i].MLinkMask = 0x0U; /* Do not use MLINK pin for link status */
        }
        else
        {
            /* program phy_mask for mac 1/port 2 */
            pGMACSWConfig->macInitCfg[i].phyMask = 0x2U;   /* corresponding to PHY address 1 */
            pGMACSWConfig->macInitCfg[i].MLinkMask = 0x0U; /* Do not use MLINK pin for link status */
        }

        pGMACSWConfig->macInitCfg[i].portPri = GMACSW_DEFAULT_MAC_PORTPRI;
        pGMACSWConfig->macInitCfg[i].portCfi = GMACSW_DEFAULT_MAC_PORTCFI;
        pGMACSWConfig->macInitCfg[i].portVID = GMACSW_DEFAULT_MAC_PORTVID;


        pGMACSWConfig->macInitCfg[i].macModeFlags =
            MAC_CONFIG_MODEFLG_TXFLOWCNTL  |
            MAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL;

        /* Driver default connection is RGMII speed/duplex auto detect */
        pGMACSWConfig->macInitCfg[i].macConnectionType =
#if defined(DEVICE_VAYU)
            /*
             * National PHY on Vayu EVM does not work with the default INBAND detection mode.
             * It would seem the Rx clock from the PHY is not generated unless the Tx clock
             * from the Vayu device is present. So set the mode to force 1Gbps to start.
             */
            MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
#else
            MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND;
#endif
        pGMACSWConfig->macInitCfg[i].PktMTU = pGMACSWConfig->PktMTU;

        /* Generate default MAC addresses to use */
        for (j = 0; j < 6U; j++)
        {
            pGMACSWConfig->macInitCfg[i].macAddr[j] = (uint8_t)((i * 0x10U) + j);
        }
    }/* end of for loop over MAC_NUM_PORTS */


    /*------------------------- MDIO Config -------------------------*/

    pGMACSWConfig->mdioCfg.baseAddress          = (uint32_t) &GMACSW_REGS->MDIO;
    pGMACSWConfig->mdioCfg.mdioBusFrequency     = GMACSW_DEFAULT_MDIOBUSFREQ;
    pGMACSWConfig->mdioCfg.mdioClockFrequency   = GMACSW_DEFAULT_MDIOCLOCKFREQ;


    /*--------------------------- ALE Config ------------------------*/

    /* We count in 100ms Ticks */
    pGMACSWConfig->aleCfg.aleTimeOutTicks       = ALE_AGE_OUT_TIME_IN_MS / 100U;
    pGMACSWConfig->aleCfg.defaultPortVID        = GMACSW_DEFAULT_MAC_PORTVID;

    /* Set default receive filter */
    pGMACSWConfig->aleCfg.defaultRxFilter       = ALE_RXFILTER_NOTHING;

    pGMACSWConfig->aleCfg.defaultAleModeFlags   = ALE_CONFIG_ENABLE |
                                                  ALE_CONFIG_CLRTABLE;

    pGMACSWConfig->aleCfg.unknownForceUntaggedEgress    = GMACSW_DEFAULT_UNK_FORCE_UNTAG_EGR;
    pGMACSWConfig->aleCfg.unknownRegMcastFloodMask      = GMACSW_DEFAULT_UNK_REGMCAST_FLOODMASK;
    pGMACSWConfig->aleCfg.unknownMcastFloodMask         = GMACSW_DEFAULT_UNK_MCAST_FLOODMASK;
    pGMACSWConfig->aleCfg.unknownVlanMemberList         = GMACSW_DEFAULT_UNK_VLANMEMLIST;

    /* CHECK: Set this to correct value.Set Ratelimit counter for 1msec*/
    pGMACSWConfig->aleCfg.alePrescale =  GMACSW_DEFAULT_ALEPRESCALE;

    /* Ale Port Config */
    for (i = 0; i < ALE_NUM_PORTS; i++)
    {
        pGMACSWConfig->aleCfg.alePortCfg[i].bcastLimit      = GMACSW_DEFAULT_BCASTLIMIT;
        pGMACSWConfig->aleCfg.alePortCfg[i].mcastLimit      = GMACSW_DEFAULT_MCASTLIMIT;
        pGMACSWConfig->aleCfg.alePortCfg[i].noLearn         = GMACSW_DEFAULT_LEARN;
        if (0U == i)
        {
            /* Enable host port on default */
            pGMACSWConfig->aleCfg.alePortCfg[i].portState       = ALE_PORT_STATE_FWD;
        }
        else
        {
            /*
             * Enable MAC ports when link is detected
             * NOTE: For MAC-to-MAC (PHY less) connection, application should enabled
             *      the port explicitly.
             */
            pGMACSWConfig->aleCfg.alePortCfg[i].portState       = ALE_PORT_STATE_DISABLED;
        }

        pGMACSWConfig->aleCfg.alePortCfg[i].vidIngressCheck = GMACSW_DEFAULT_VIDINGRESSCHECK;
        pGMACSWConfig->aleCfg.alePortCfg[i].dropUntagged    = GMACSW_DEFAULT_DROPUNTAGGED;
    }

    /************************* STATS Config ****************************/
    pGMACSWConfig->statsCfg.enableStatistics = 1U;

    /************************* CPTS Config ****************************/
    pGMACSWConfig->cptsCfg.enableCPTSEvents = 1U;
#if defined(DEVICE_VAYU)
    /* 266 MHz by default (L3 Frequency) */
    pGMACSWConfig->cptsCfg.cptsInputFrequency = 266000000UL;
#else
    /* 250 MHz by default (Shared with 250MHz input for CPSW SS, needed in RGMII mode ) */
    pGMACSWConfig->cptsCfg.cptsInputFrequency = 250000000UL;
#endif
    return pGMACSWConfig;
}

GMACSW_Config *GMACSW_CONFIG_getDLBConfig(void)
{
    uint32_t i = 0;
    /* Start with the default config and then modify */
    GMACSW_Config *pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();

    /* Set DLB mode flag */
    pGMACSWConfig->dlbMode = 1U;

    /********************* MAC Port Config **********************/
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        /* Specify NOPHY mode when for digital loopback operation */
        pGMACSWConfig->macInitCfg[i].mdioModeFlags = MDIO_MODEFLG_NOPHY;

        pGMACSWConfig->macInitCfg[i].macModeFlags |=
            MAC_CONFIG_MODEFLG_MACLOOPBACK |   /* enable DLB */
            MAC_CONFIG_MODEFLG_PASSERROR   |   /* enable RX_CMF*/
            MAC_CONFIG_MODEFLG_PASSCONTROL;    /* enable RX_CSF,RX_CEF*/
    }

    /************************* ALE Config ****************************/

    /* Bypass ALE in for digital loopback operation */
    pGMACSWConfig->aleCfg.defaultAleModeFlags |= ALE_CONFIG_ALEBYPASS;

    /* Ale Port Config */
    for(i = 0; i < ALE_NUM_PORTS; i++)
    {
        /* No learn for digital loopback operation */
        pGMACSWConfig->aleCfg.alePortCfg[i].noLearn = GMACSW_DEFAULT_NOLEARN;
    }

    return pGMACSWConfig;
}

GMACSW_Config *GMACSW_CONFIG_getVLANConfig(void)
{
    /* Start with the default config and then modify */
    GMACSW_Config *pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();

    /* Add space for VLAN tag */
    pGMACSWConfig->PktMTU += 4;

    /* Enable this to turn on VLAN Tx support in the CPMAC_SL modules of the GMACSW */
    pGMACSWConfig->cpswCtlModeFlags |= GMACSW_CONFIG_CPSW_ENVLANAWARE;

    /************************* ALE Config ****************************/

    /* Enable this to turn on VLAN support in the ALE */
    pGMACSWConfig->aleCfg.defaultAleModeFlags |= ALE_CONFIG_ENVLANAWARE;

    return pGMACSWConfig;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

