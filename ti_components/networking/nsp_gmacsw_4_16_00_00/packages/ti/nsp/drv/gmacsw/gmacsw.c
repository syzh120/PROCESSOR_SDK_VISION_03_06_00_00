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
 *   \file  gmacsw.c
 *
 *   \brief
 *          Top-level of hardware driver for GMACSW IP block
 *
 *  \par
 *  NOTE:
 *  When used in an multitasking environment, no GMACSW function may be
 *  called while another GMACSW function is operating on the same device
 *  handle in another thread. It is the responsibility of the application
 *  to assure adherence to this restriction.
 *
 *  \par
 *  Although the GMACSW API is defined to support multiple device instances,
 *  this version supports a single device instance
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
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
#include "gmacsw_al.h"

/* GMACSW Driver private headers */
#include "private/cpdma_.h"
#include "private/debug_.h"
#include "private/cpts_.h"
#include "private/mac_.h"
#include "private/mdio_.h"
#include "private/port_.h"
#include "private/ale_.h"

/* This module's private header */
#include "private/gmacsw_.h"

/* This module's public header */
#include "gmacsw.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define GMACSW_IOCTL_MAJOR_MASK                     (0xFFFF0000U)
#define GMACSW_IOCTL_MINOR_MASK                     (0x0000FFFFU)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_setGmacSwConfig(const GMACSW_Config *pGMACSWConfig);

static uint32_t LOCAL_registerTickFxn(GMACSW_Device *pGMACSW,
    GMACSW_TickFxnCallback tickFxn,
    void *tickFxnArg,
    GMACSW_RegisteredTickFxnHandle *pTickFxnHandle);
static uint32_t LOCAL_unregisterTickFxn(GMACSW_Device *pGMACSW,
    GMACSW_RegisteredTickFxnHandle hTickFxn);
static uint32_t LOCAL_registerPrintFxn(GMACSW_Device *pGMACSW,
    GMACSW_PrintFxnCallback printFxn);
static void inline LOCAL_printFxn(char *prnStr,...);

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

/* Data to keep track of open references to the GMACSW Hardware Driver */
static uint32_t         LOCAL_gmacswRefCount    = 0;
static GMACSW_Device    *LOCAL_gmacswRef        = NULL;

#if !defined(NSP_DYNAMIC_ALLOCATION)
/*! Local copy of the GMACSW device instance */
GMACSW_Device GMACSW_deviceObj;
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

GMACSW_DeviceHandle GMACSW_open(GMACSW_Config *pGMACSWConfig)
{
    GMACSW_Device           *pGMACSW = NULL;
    uint32_t                i, j;
    uint8_t                 *pMacAddr;
    uint32_t                key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_gmacswRefCount++;

    if ((uint32_t)1U == LOCAL_gmacswRefCount)
    {
        if (IS_NULL(pGMACSWConfig))
        {
            return NULL;
        }
        /* check port mask is valid */
        if ( 0U != ((uint8_t)(~PORT_MASK_MAC_BOTH) & pGMACSWConfig->activeMACPortMask) )
        {
            pGMACSWConfig->activeMACPortMask = (uint8_t)PORT_MASK_MAC_BOTH;
        }

        /* MAC address must be supplied and not a multicast address */
        for( i=0; i < MAC_NUM_PORTS; i++ )
        {
            if ((1U << i) & (uint32_t)pGMACSWConfig->activeMACPortMask )
            {
                pMacAddr = &(pGMACSWConfig->macInitCfg[i].macAddr[0]);

                if( ((uint32_t)pMacAddr[0] & 0x1U) != 0U)
                {
                    return NULL;
                }
                for (j = 0; j < (uint32_t)6U; j++)
                {
                    /* If we see any non-zero byte in the mac address then break */
                    if (pMacAddr[j] != 0U)
                    {
                        break;
                    }
                }
                if (j == 6U)
                {
                    return NULL;
                }
            }
        }
        /*
         * Init the instance structure
         */
#if defined(NSP_DYNAMIC_ALLOCATION)
        pGMACSW = (GMACSW_Device *) calloc(1U, sizeof(GMACSW_Device));
        if (IS_NULL(pGMACSW))
        {
            LOCAL_printFxn("ERROR: Unable to allocate GMACSW device object!\n");
            return NULL;
        }
#else
        pGMACSW = &GMACSW_deviceObj;
#endif

        /* Default everything in our instance structure to zero */
        memset(pGMACSW, 0, sizeof(GMACSW_Device));

        /* Save the supplied configuration */
        memcpy(&pGMACSW->config, pGMACSWConfig, sizeof(GMACSW_Config));

        /* Soft reset CPDMA */
#if defined(USE_CSLR)
        CSL_FINS(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET, CSL_GMACSW_CPDMA_SOFT_RESET_SOFT_RESET_RESET);
        while(CSL_FEXT(GMACSW_REGS->CPDMA.CPDMA_SOFT_RESET, GMACSW_CPDMA_SOFT_RESET_SOFT_RESET) !=
                CSL_GMACSW_CPDMA_SOFT_RESET_SOFT_RESET_NORESET)
        {
        }
#else
        GMAC_SW_CPDMAReset(SOC_GMAC_SW_CPDMA_BASE);
#endif

        /* Soft reset CPGMAC_SL1 */
#if defined(USE_CSLR)
        CSL_FINS(GMACSW_REGS->SL.MAC[0].SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET, CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_RESET);
        while (CSL_FEXT(GMACSW_REGS->SL.MAC[0].SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET) !=
                CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_NORESET)
        {
        }
#else
        GMAC_SW_SlReset(SOC_GMAC_SW_SL1_BASE);
#endif

        /* Soft reset CPGMAC_SL2 */
#if defined(USE_CSLR)
        CSL_FINS(GMACSW_REGS->SL.MAC[1].SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET, CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_RESET);
        while(CSL_FEXT(GMACSW_REGS->SL.MAC[1].SL_SOFT_RESET, GMACSW_SL_SOFT_RESET_SOFT_RESET) !=
                CSL_GMACSW_SL_SOFT_RESET_SOFT_RESET_NORESET)
        {
        }
#else
        GMAC_SW_SlReset(SOC_GMAC_SW_SL2_BASE);
#endif

        /* Soft reset CPSW_3G */
#if defined(USE_CSLR)
        CSL_FINS(GMACSW_REGS->SS.CPSW_SOFT_RESET, GMACSW_CPSW_SOFT_RESET_SOFT_RESET, CSL_GMACSW_CPSW_SOFT_RESET_SOFT_RESET_RESET);
        while (CSL_FEXT(GMACSW_REGS->SS.CPSW_SOFT_RESET, GMACSW_CPSW_SOFT_RESET_SOFT_RESET) !=
                CSL_GMACSW_CPSW_SOFT_RESET_SOFT_RESET_NORESET)
        {
        }
#else
        GMAC_SW_SSReset(SOC_GMAC_SW_SS_BASE);
#endif

        /* Soft reset CPSW_3G_SS */
#if defined(USE_CSLR)
        CSL_FINS(GMACSW_REGS->WR.WR_SOFT_RESET,
                GMACSW_WR_SOFT_RESET_SOFT_RESET,CSL_GMACSW_WR_SOFT_RESET_SOFT_RESET_YES);

#else
        GMAC_SW_WrReset(SOC_GMAC_SW_WR_BASE);
#endif

        /* Open the CPDMA host port */
        pGMACSW->cpdma = CPDMA_open(&(pGMACSWConfig->cpdmaInitCfg));   /* port 0 */
        if (IS_NULL(pGMACSW->cpdma))
        {
            LOCAL_printFxn("ERROR: CPDMA_open() failed!\n");
            return NULL;
        }

        /* Open the MAC external ports */
        for( i=0; i < MAC_NUM_PORTS; i++ )
        {
            if ( (1U << i) & (uint32_t)pGMACSWConfig->activeMACPortMask )
            {
                pGMACSW->mac[i] = MAC_open(&(pGMACSWConfig->macInitCfg[i]), i); /* ports 1 through n */

                if (NULL == pGMACSW->mac[i])
                {
                    LOCAL_printFxn("ERROR: MAC_open() failed for MAC number %d!\n",i);
                    return NULL;
                }
            }
        }

        /* Open the MDIO module */
        pGMACSW->mdio = MDIO_open(&pGMACSWConfig->mdioCfg);

        /* Configure the PHY devices */
        for( i=0; i < MAC_NUM_PORTS; i++ )
        {
            if ( (1U << i) & (uint32_t)pGMACSWConfig->activeMACPortMask )
            {
                PHY_Config phyConfig;

                /* Set up the config structure */
                phyConfig.phyMask = pGMACSWConfig->macInitCfg[i].phyMask;
                phyConfig.MLinkMask = pGMACSWConfig->macInitCfg[i].MLinkMask;
                phyConfig.MdixMask = 0;
                phyConfig.mdioModeFlags = pGMACSWConfig->macInitCfg[i].mdioModeFlags;

                /* Configure the PHY */
                MDIO_phyInit(pGMACSW->mdio, i, &phyConfig);
            }
        }

        /* Open the PORT module */
        pGMACSW->port = PORT_open();
        if (IS_NULL(pGMACSW->port))
        {
            LOCAL_printFxn("ERROR: PORT_open() failed!\n");
            return NULL;
        }

        /* Open the CPTS module */
        pGMACSW->cpts = CPTS_open(&(pGMACSWConfig->cptsCfg));
        if (IS_NULL(pGMACSW->cpts))
        {
            LOCAL_printFxn("ERROR: PORT_open() failed!\n");
            return NULL;
        }

        /* Program the CPSW_Control register */
        LOCAL_setGmacSwConfig(pGMACSWConfig);

        /* Open the ALE module */
        pGMACSW->ale = ALE_open(&(pGMACSWConfig->aleCfg), pGMACSW->config.macInitCfg[0].macAddr);
        if (IS_NULL(pGMACSW->ale))
        {
            LOCAL_printFxn("ERROR: ALE_open() failed!\n");
            return NULL;
        }

        /* Open the STATS module */
        pGMACSW->stats = STATS_open(&(pGMACSWConfig->statsCfg), pGMACSWConfig->activeMACPortMask);
        if (IS_NULL(pGMACSW->stats))
        {
            LOCAL_printFxn("ERROR: STATS_open() failed!\n");
            return NULL;
        }

        /* Assume linked interface is the first one */
        pGMACSW->currLinkedInterface = 0;

        /* Figure out default link status */
        if ( (pGMACSWConfig->dlbMode != 0U) ||
             ((pGMACSWConfig->macInitCfg[0].mdioModeFlags & MDIO_MODEFLG_NOPHY) != 0) )
        {
            /* No need to wait for link up in digital loopback mode */
            pGMACSW->linkIsUp[0U] = 1U;
            pGMACSW->linkIsUp[1U] = 1U;
        }
        else
        {
            /* Wait for link to come up */
            pGMACSW->linkIsUp[0U] = 0U;
            pGMACSW->linkIsUp[1U] = 0U;
        }

        /* Use specified MTU value */
        pGMACSW->PktMTU = pGMACSWConfig->PktMTU;

        /* Set magic number used to validate the device handle */
        pGMACSW->devMagic = GMACSW_DEVMAGIC;

        LOCAL_gmacswRef = pGMACSW;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, CPDMA was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
        pGMACSW = LOCAL_gmacswRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    /* Give a handle back to the caller */
    return (GMACSW_DeviceHandle) pGMACSW;
}

uint32_t GMACSW_close(GMACSW_DeviceHandle hGMACSW)
{
    uint32_t        retVal = GMACSW_SUCCESS;
    uint32_t        key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_gmacswRefCount--;

    if ((uint32_t)0U == LOCAL_gmacswRefCount)
    {
        GMACSW_Device   *pGMACSW = (GMACSW_Device *)hGMACSW;
        uint32_t         i;

        /* Validate our handle */
        if (IS_NULL(pGMACSW) || (pGMACSW->devMagic != GMACSW_DEVMAGIC))
        {
            return GMACSW_INVALID_PARAM;
        }

        /* Close all ports */
        CPDMA_close(pGMACSW->cpdma);  /* port 0 */

        for( i=0; i < MAC_NUM_PORTS; i++ )
        {
            if ((1U << i) & (uint32_t)pGMACSW->config.activeMACPortMask )
            {
                MAC_close(pGMACSW->mac[i]); /* ports 1 through n */
            }
        }

        /* Cleanup the PORT module */
        PORT_close(pGMACSW->port);

        /* Cleanup the MDIO module */
        MDIO_close(pGMACSW->mdio);

        /* Cleanup the PORT module */
        CPTS_close(pGMACSW->cpts);

        /* Cleanup the ALE module */
        ALE_close(pGMACSW->ale);

        /* Cleanup the STATS module */
        STATS_close(pGMACSW->stats);

        /* Invalidate the GMACSW handle */
        pGMACSW->devMagic = 0;

        /* Reset the local reference holder */
        LOCAL_gmacswRef = NULL;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pGMACSW);
#else
        memset(pGMACSW, 0, sizeof(GMACSW_Device));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

uint32_t GMACSW_ioctl(GMACSW_DeviceHandle hGMACSW, uint32_t cmd, void *param, uint32_t size)
{
    GMACSW_Device *pGMACSW = (GMACSW_Device *)hGMACSW;

    uint32_t majorCmd = (cmd & GMACSW_IOCTL_MAJOR_MASK);

    uint32_t retVal = GMACSW_FAILURE;

    if (IS_NULL(pGMACSW) || (pGMACSW->devMagic != GMACSW_DEVMAGIC))
    {
        retVal = GMACSW_INVALID_PARAM;
    }
    else if (GMACSW_IOCTL_BASE == majorCmd)
    {
        switch (cmd)
        {
            case GMACSW_IOCTL_REGISTER_TICK_FXN:
            {
                if (size != sizeof(GMACSW_TickFxnIoctlCmd))
                {
                    retVal = GMACSW_MALFORMED_IOCTL;
                }
                else
                {
                    GMACSW_TickFxnIoctlCmd *pCmd = (GMACSW_TickFxnIoctlCmd *) param;

                    retVal = LOCAL_registerTickFxn(
                        pGMACSW,
                        pCmd->pTickFxnCallback,
                        pCmd->hTickFxnCallbackArg,
                        pCmd->hRegisteredTickFxn );
                }
                break;
            }
            case GMACSW_IOCTL_UNREGISTER_TICK_FXN:
            {
                if (size != sizeof(GMACSW_RegisteredTickFxnHandle))
                {
                    retVal = GMACSW_MALFORMED_IOCTL;
                }
                else
                {
                    GMACSW_RegisteredTickFxnHandle hTickFxn = *((GMACSW_RegisteredTickFxnHandle *) param);
                    retVal = LOCAL_unregisterTickFxn(pGMACSW, hTickFxn);
                }
                break;
            }
            case GMACSW_IOCTL_REGISTER_PRINT_FXN:
            {
                if (size != sizeof(GMACSW_PrintFxnIoctlCmd))
                {
                    retVal = GMACSW_MALFORMED_IOCTL;
                }
                else
                {
                    GMACSW_PrintFxnIoctlCmd *pCmd = (GMACSW_PrintFxnIoctlCmd *) param;

                    retVal = LOCAL_registerPrintFxn(
                        pGMACSW,
                        pCmd->pPrintFxnCallback);
                }
                break;
            }
            default:
            {
                /* driver doesnt recognize this command. */
                retVal = GMACSW_UNKNOWN_IOCTL;
                break;
            }
        }
    }
    else
    {
        switch (majorCmd)
        {
            case (uint32_t)GMACSW_IOCTL_ALE_BASE:
                retVal = ALE_ioctl(pGMACSW->ale, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_STATS_BASE:
                retVal = STATS_ioctl(pGMACSW->stats, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_CPTS_BASE:
                retVal = CPTS_ioctl(pGMACSW->cpts, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_CPDMA_BASE:
                retVal = CPDMA_ioctl(pGMACSW->cpdma, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_PORT_BASE:
                retVal = PORT_ioctl(pGMACSW->port, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_MDIO_BASE:
                retVal = MDIO_ioctl(pGMACSW->mdio, cmd, param, size);
                break;
            case (uint32_t)GMACSW_IOCTL_MAC_BASE:
                break;
            default:
            {
                /* driver doesnt recognize this command. */
                retVal = GMACSW_UNKNOWN_IOCTL;
                break;
            }
        }
    }

    return retVal;
}

void GMACSW_periodicTick( GMACSW_DeviceHandle hGMACSW )
{
    GMACSW_Device*  pGMACSW = (GMACSW_Device *) hGMACSW;
    uint32_t        macNum;
    uint32_t        i = 0;

    /* Do ALE table age out if enabled and needed */
    ALE_ageOut(pGMACSW->ale);

    /* Check with PHYs via MDIO interface for status updates */
    for( macNum=0; macNum< MAC_NUM_PORTS; macNum++ )
    {
        if ((1U << macNum) & (uint32_t)pGMACSW->config.activeMACPortMask )
        {
            uint32_t phyMode;
            uint32_t portNum = macNum + 1U;
            uint32_t mdioStatus, linkStatus;
            uint32_t portLink = 0U;

            /* Check that MAC/PHY is not in NO_PHY mode */
            MDIO_getPhyMode(pGMACSW->mdio, macNum, &phyMode);

            if (0U == (phyMode & NWAY_NOPHY))
            {
                /* run the state machine */
                MDIO_tic(pGMACSW->mdio, macNum, &mdioStatus);
                portLink = MDIO_getPhyLink(pGMACSW->mdio, macNum);
            }

            /* Check for port in forward state */
#if defined(USE_CSLR)
            if ( ( 0U != portLink) ||
                 (CSL_FEXT(GMACSW_REGS->ALE.ALE_PORTCTL[portNum],
                           GMACSW_ALE_PORTCTL_PORT_STATE) !=
                           ALE_PORT_STATE_DISABLED) )
#else
            if (( 0U != portLink) ||
                  GMAC_SW_ALE_PORT_STATE_DISABLED !=
                        GMAC_SW_ALEPortStateGet(SOC_GMAC_SW_ALE_BASE, portNum))
#endif
            {

                if (0U == (phyMode & NWAY_NOPHY))
                {
                    if (mdioStatus != MDIO_EVENT_NOCHANGE)
                    {
                        if (MDIO_EVENT_LINKDOWN == mdioStatus)
                        {
                            linkStatus = LINKSTATUS_NOLINK;

                            uint32_t prevLink = pGMACSW->linkIsUp[macNum];
                            if (1U == prevLink)
                            {
                                /*Disable ALE by a direct register write*/
#if defined(USE_CSLR)
                                CSL_FINS( GMACSW_REGS->ALE.ALE_PORTCTL[portNum],
                                        GMACSW_ALE_PORTCTL_PORT_STATE,
                                        ALE_PORT_STATE_DISABLED);
#else
                                GMAC_SW_ALEPortStateSet(SOC_GMAC_SW_ALE_BASE,
                                                        portNum,
                                                        GMAC_SW_ALE_PORT_STATE_DISABLED);
#endif
                            }

                            /* Mark that link is down */
                            pGMACSW->linkIsUp[macNum] = 0U;
                        }
                        else if (MDIO_EVENT_LINKUP == mdioStatus)
                        {
                            MDIO_getLinkStatus(pGMACSW->mdio, macNum, &linkStatus);

                            uint32_t prevLink = pGMACSW->linkIsUp[macNum];
                            if (0U == prevLink)
                            {
                                /*Enable ALE*/
#if defined(USE_CSLR)
                            CSL_FINS( GMACSW_REGS->ALE.ALE_PORTCTL[portNum],
                                      GMACSW_ALE_PORTCTL_PORT_STATE,
                                      ALE_PORT_STATE_FWD);

#else
                            GMAC_SW_ALEPortStateSet(SOC_GMAC_SW_ALE_BASE,
                                                    portNum,
                                                    GMAC_SW_ALE_PORT_STATE_FWD);
#endif
                            }

                            /* Mark that link is up */
                            pGMACSW->linkIsUp[macNum] = 1U;
                            pGMACSW->currLinkedInterface = macNum;
                        }
                        else
                        {
                            linkStatus = LINKSTATUS_NOTVALID;
                        }

                        if ((linkStatus != LINKSTATUS_NOTVALID) && (pGMACSW->config.linkStatusCallback != NULL))
                        {
                            uint32_t phyAddr;

                            MDIO_getPhyAddr(pGMACSW->mdio, macNum, &phyAddr);

                            (*pGMACSW->config.linkStatusCallback)(phyAddr, linkStatus);
                        }
                    }
                }
            }
        }
    }
    /* Do stack-registered periodic callbacks */
    for (i = 0; i < GMACSW_MAX_TICK_FXN_CNT; i++)
    {
        GMACSW_RegisteredTickFxn *pTickFxn = &pGMACSW->registeredTickFxns[i];
        if (((pGMACSW->tickFxnBitVector >> i) & 0x1U) != 0x0U)
        {
            if (NULL != pTickFxn->pTickFxnCallback)
            {
                (*pTickFxn->pTickFxnCallback)(pTickFxn->hTickFxnCallbackArg);
            }
        }
    }
}

void GMACSW_getLinkStatus( GMACSW_DeviceHandle hGMACSW, uint32_t *linkState, uint32_t devIdx)
{
    GMACSW_Device* pGMACSW = (GMACSW_Device *) hGMACSW;

    *linkState          = pGMACSW->linkIsUp[devIdx];
}

void GMACSW_printFxn(GMACSW_DeviceHandle hGMACSW, char *prnStr,...)
{
    char str[100];

    if ((NULL != hGMACSW) && (NULL != hGMACSW->printFxnCb))
    {
        /* Function is non- reentrant */
        snprintf (str, 100U, prnStr);
       (*hGMACSW->printFxnCb)(str);
    }
    else
    {
#if defined (DEBUG)
        printf(prnStr);
#endif
    }
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_setGmacSwConfig(const GMACSW_Config *pGMACSWConfig)
{
    uint32_t            regVal = 0;

    /* CPSW_CONTROL register config */
    if ((pGMACSWConfig->cpswCtlModeFlags & GMACSW_CONFIG_CPSW_EEE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_CONTROL_EEE_EN, CSL_GMACSW_CPSW_CONTROL_EEE_EN_ENABLE);
    }
    if ((pGMACSWConfig->cpswCtlModeFlags & GMACSW_CONFIG_CPSW_DLR_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_CONTROL_DLR_EN, CSL_GMACSW_CPSW_CONTROL_DLR_EN_ENABLE);
    }
    if ((pGMACSWConfig->cpswCtlModeFlags & GMACSW_CONFIG_CPSW_RXVLANENCAP) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_CONTROL_RX_VLAN_ENCAP, CSL_GMACSW_CPSW_CONTROL_RX_VLAN_ENCAP_ENABLE);
    }
    /*
     * VLAN Aware mode only impacts Tx packet handling in the CPGMAC_SL modules.
     * This has no impact for Rx packets.
     */
    if ((pGMACSWConfig->cpswCtlModeFlags & GMACSW_CONFIG_CPSW_ENVLANAWARE) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_CONTROL_VLAN_AWARE, CSL_GMACSW_CPSW_CONTROL_VLAN_AWARE_ENABLE);
    }
    if ((pGMACSWConfig->cpswCtlModeFlags & GMACSW_CONFIG_CPSW_FIFOLOOPBACK) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_CONTROL_FIFO_LOOPBACK, CSL_GMACSW_CPSW_CONTROL_FIFO_LOOPBACK_ENABLE);
    }
    GMACSW_REGS->SS.CPSW_CONTROL = regVal;

    /* CPSW_PTYPE register config */
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P2_PRI3_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P2_PRI3_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P2_PRI2_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P2_PRI2_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P2_PRI1_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P2_PRI1_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P1_PRI3_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P1_PRI3_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P1_PRI2_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P1_PRI2_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P1_PRI1_SHAPE_EN) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P1_PRI1_SHAPE_EN, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P2PTYPEESC) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P2_PTYPE_ESC, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P1PTYPEESC) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P1_PTYPE_ESC, 1);
    }
    if ((pGMACSWConfig->cpswPtypeModeFlags & GMACSW_CONFIG_PTYPE_P0PTYPEESC) != 0)
    {
        regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_P0_PTYPE_ESC, 1);
    }
    regVal |= CSL_FMK(GMACSW_CPSW_PTYPE_ESC_PRI_LD_VAL, pGMACSWConfig->escPriLdVal);

    GMACSW_REGS->SS.CPSW_PTYPE = regVal;
}

static uint32_t LOCAL_registerTickFxn(GMACSW_Device *pGMACSW,
    GMACSW_TickFxnCallback tickFxn,
    void *tickFxnArg,
    GMACSW_RegisteredTickFxnHandle *pTickFxnHandle)
{
    /* Set default return value */
    uint32_t retVal = GMACSW_SUCCESS;

    if ((NULL == tickFxn) || (NULL == pTickFxnHandle))
    {
        retVal =  GMACSW_INVALID_PARAM;
    }
    else
    {
        uint32_t tickFxnNum = 0;
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        *pTickFxnHandle = NULL;

        /* Find next available stack number */
        while ( ( (((uint32_t)0x1U<<tickFxnNum) & pGMACSW->tickFxnBitVector) != 0U)
                && (tickFxnNum < GMACSW_MAX_TICK_FXN_CNT) )
        {
            tickFxnNum++;
        }
        if (GMACSW_MAX_TICK_FXN_CNT <= tickFxnNum)
        {
            retVal = GMACSW_TOO_MANY_TICK_FXNS;
        }
        else
        {
            pGMACSW->tickFxnBitVector |= ((uint32_t)0x1U << tickFxnNum);
        }
        GMACSW_AL_globalInterruptEnable(key);

        if ( GMACSW_SUCCESS == retVal)
        {
            GMACSW_RegisteredTickFxn *pTickFxn;

            pTickFxn = &(pGMACSW->registeredTickFxns[tickFxnNum]);

            /* Set the number of this registered tick function */
            pTickFxn->tickFxnNum            = tickFxnNum;
            pTickFxn->pTickFxnCallback      = tickFxn;
            pTickFxn->hTickFxnCallbackArg   = tickFxnArg;

            *pTickFxnHandle = (GMACSW_RegisteredTickFxnHandle) pTickFxn;
        }
    }
    return retVal;
}

static uint32_t LOCAL_unregisterTickFxn(GMACSW_Device *pGMACSW,
    GMACSW_RegisteredTickFxnHandle hTickFxn)
{
    uint32_t retVal = GMACSW_SUCCESS;
    GMACSW_RegisteredTickFxn *pTickFxn = (GMACSW_RegisteredTickFxn *) hTickFxn;
    uint32_t tickFxnNum = pTickFxn->tickFxnNum;

    if (((uint32_t)(pGMACSW->tickFxnBitVector & (uint32_t)(((uint32_t)0x1U) << tickFxnNum))) == 0U)
    {
        retVal = GMACSW_INVALID_PARAM;
    }
    else
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();
        pGMACSW->tickFxnBitVector &= ~((uint32_t)0x1U << tickFxnNum);
        GMACSW_AL_globalInterruptEnable(key);

        pTickFxn->tickFxnNum            = 0;
        pTickFxn->pTickFxnCallback      = NULL;
        pTickFxn->hTickFxnCallbackArg   = NULL;
    }

    return retVal;
}

static uint32_t LOCAL_registerPrintFxn(GMACSW_Device *pGMACSW,
    GMACSW_PrintFxnCallback printFxn)
{
    /* Set default return value */
    uint32_t retVal = GMACSW_SUCCESS;

    pGMACSW->printFxnCb = printFxn;
    LOCAL_printFxn(" NSP GMAC: Registered debug callback function\n");

    return retVal;
}

static void inline LOCAL_printFxn(char *prnStr,...)
{
    GMACSW_printFxn((GMACSW_DeviceHandle)LOCAL_gmacswRef, prnStr);
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

