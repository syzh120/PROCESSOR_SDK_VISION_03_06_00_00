/*
 * Copyright (C) 2007-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *   \file  mdio.c
 *
 *   \brief
 *          MDIO Polling State Machine API. Functions will enable mii-PHY
 *          negotiation.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Project dependency headers */
#if defined(USE_CSLR)
#include "cslr.h"
#include "cslr_gmacsw.h"
#else
#include "hw_gmacsw_mdio.h"
#endif
#include "gmacsw_al.h"
#include "mac.h"

/* GMACSW Driver private headers */
#include "private/debug_.h"

/* This module's private header */
#include "private/mdio_.h"

/* This module's header */
#include "mdio.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#if (0)
#include <stdio.h>
#define MDIO_DEBUG
/*
 * Map this print to appropriate function. Should be of the form
 * #define mdioPrintf(format, args...)
 */
#define mdioPrintf printf
#endif

/* R A N D O M  N U M B E R  S U P P O R T */
#define COMMON_RANDOM_MAX        0xFFFFU

#define PHY_NOT_FOUND  0xFFFFU    /*  Used in PHY Detection */

/*CHECK:: phyState field breakup  */
#define PHY_DEV_OFFSET      ((uint32_t)0U)
#define PHY_DEV_SIZE        ((uint32_t)5U)
#define PHY_DEV_MASK        ((uint32_t)0x1FU<<PHY_DEV_OFFSET)

#define PHY_STATE_OFFSET    (PHY_DEV_OFFSET+PHY_DEV_SIZE)
#define PHY_STATE_SIZE      ((uint32_t)4U)
#define PHY_STATE_MASK      ((uint32_t)0xFU<<PHY_STATE_OFFSET)
#define FINDING             ((uint32_t)1U<<PHY_STATE_OFFSET)
#define FOUND               ((uint32_t)2U<<PHY_STATE_OFFSET)
#define NWAY_START          ((uint32_t)3U<<PHY_STATE_OFFSET)
#define NWAY_WAIT           ((uint32_t)4U<<PHY_STATE_OFFSET)
#define LINK_WAIT           ((uint32_t)5U<<PHY_STATE_OFFSET)
#define LINKED              ((uint32_t)6U<<PHY_STATE_OFFSET)
#define LOOPBACK            ((uint32_t)7U<<PHY_STATE_OFFSET)

#define PHY_SPEED_OFFSET    (PHY_STATE_OFFSET+PHY_STATE_SIZE)
#define PHY_SPEED_SIZE      ((uint32_t)2U)
#define PHY_SPEED_MASK      ((uint32_t)0x3U<<PHY_SPEED_OFFSET)

#define PHY_DUPLEX_OFFSET   (PHY_SPEED_OFFSET+PHY_SPEED_SIZE)
#define PHY_DUPLEX_SIZE     ((uint32_t)1U)
#define PHY_DUPLEX_MASK     ((uint32_t)1U<<PHY_DUPLEX_OFFSET)

#define PHY_TIM_OFFSET      (PHY_DUPLEX_OFFSET+PHY_DUPLEX_SIZE)
#define PHY_TIM_SIZE        ((uint32_t)10U)
#define PHY_TIM_MASK        ((uint32_t)0x3FFU<<PHY_TIM_OFFSET)

/* we are working with 100ms ticks here */
#define PHY_FIND_TO ((uint32_t)1U<<PHY_TIM_OFFSET)
#define PHY_RECK_TO ((uint32_t)20U<<PHY_TIM_OFFSET)
#define PHY_LINK_TO ((uint32_t)50U<<PHY_TIM_OFFSET)
#define PHY_NWST_TO ((uint32_t)50U<<PHY_TIM_OFFSET)
#define PHY_NWDN_TO ((uint32_t)80U<<PHY_TIM_OFFSET)
#define PHY_MDIX_TO ((uint32_t)27U<<PHY_TIM_OFFSET) /* 2.74 Seconds <--Spec and empirical */

#define PHY_SMODE_OFFSET    (PHY_TIM_OFFSET+PHY_TIM_SIZE)
#define PHY_SMODE_SIZE      ((uint32_t)7U)
#define PHY_SMODE_MASK      ((uint32_t)0x7FU<<PHY_SMODE_OFFSET)
#define SMODE_LPBK   ((uint32_t)0x40U<<PHY_SMODE_OFFSET)
#define SMODE_AUTO   ((uint32_t)0x20U<<PHY_SMODE_OFFSET)
#define SMODE_FD1000 ((uint32_t)0x10U<<PHY_SMODE_OFFSET)
#define SMODE_FD100  ((uint32_t)0x08U<<PHY_SMODE_OFFSET)
#define SMODE_HD100  ((uint32_t)0x04U<<PHY_SMODE_OFFSET)
#define SMODE_FD10   ((uint32_t)0x02U<<PHY_SMODE_OFFSET)
#define SMODE_HD10   ((uint32_t)0x01U<<PHY_SMODE_OFFSET)
#define SMODE_ALL    ((uint32_t)0x1FU<<PHY_SMODE_OFFSET)

#define PHY_CHNG_OFFSET    (PHY_SMODE_OFFSET+PHY_SMODE_SIZE)
#define PHY_CHNG_SIZE      ((uint32_t)1U)
#define PHY_CHNG_MASK      ((uint32_t)1U<<PHY_CHNG_OFFSET)
#define PHY_CHANGE ((uint32_t)1U<<PHY_CHNG_OFFSET)

#define PHY_TIMEDOUT_OFFSET    (PHY_CHNG_OFFSET+PHY_CHNG_SIZE)
#define PHY_TIMEDOUT_SIZE      ((uint32_t)1U)     /*  30 Bits used */
#define PHY_TIMEDOUT_MASK   ((uint32_t)1U<<PHY_TIMEDOUT_OFFSET)
#define PHY_MDIX_SWITCH     ((uint32_t)1U<<PHY_TIMEDOUT_OFFSET)

#define PHY_MDIX_OFFSET    (PHY_TIMEDOUT_OFFSET+PHY_TIMEDOUT_SIZE)
#define PHY_MDIX_SIZE      ((uint32_t)1U)     /*  31 Bits used */
#define PHY_MDIX_MASK      ((uint32_t)1U << PHY_MDIX_OFFSET)
#define PHY_MDIX_EN        ((uint32_t)1U << PHY_MDIX_OFFSET)

/*  Local MDIO Register Macros    */
#if defined(USE_CSLR)
#define myMDIO_VER             (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_VER)
#define myMDIO_CONTROL         (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_CONTROL)
#define myMDIO_ALIVE           (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_ALIVE)
#define myMDIO_LINK            (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_LINK)
#define myMDIO_USERACCESS0     (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_USERACCESS0)
#define myMDIO_USERPHYSEL0     (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_USERPHYSEL0)
#define myMDIO_USERACCESS1     (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_USERACCESS1)
#define myMDIO_USERPHYSEL1     (((CSL_GMACSW_mdioRegs *)(pMdio->miibase))->MDIO_USERPHYSEL1)
#define myMDIO_USERACCESS      (((CSL_GMACSW_mdioRegs *)(pMdio->miibase+(pPhy->macNum*8U)))->MDIO_USERACCESS0)
#define myMDIO_USERPHYSEL      (((CSL_GMACSW_mdioRegs *)(pMdio->miibase+(pPhy->macNum*8U)))->MDIO_USERPHYSEL0)
#else
#define myMDIO_VER             *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_VER))
#define myMDIO_CONTROL         *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_CONTROL))
#define myMDIO_ALIVE           *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_ALIVE))
#define myMDIO_LINK            *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_LINK))
#define myMDIO_USERACCESS0     *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_USERACCESS0))
#define myMDIO_USERPHYSEL0     *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_USERPHYSEL0))
#define myMDIO_USERACCESS1     *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_USERACCESS1))
#define myMDIO_USERPHYSEL1     *((volatile uint32_t *) ((pMdio->miibase)+GMAC_SW_MDIO_USERPHYSEL1))
#define myMDIO_USERACCESS      *((volatile uint32_t *) ((pMdio->miibase)+(pPhy->macNum*8U)+GMAC_SW_MDIO_USERACCESS0))
#define myMDIO_USERPHYSEL      *((volatile uint32_t *) ((pMdio->miibase)+(pPhy->macNum*8U)+GMAC_SW_MDIO_USERPHYSEL0))
#endif

#define MDIO_USERACCESS_READ    ((uint32_t)0U)
#define MDIO_USERACCESS_WRITE   ((uint32_t)1U)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static uint32_t LOCAL_random(void);
static uint32_t LOCAL_randomRange(uint32_t min, uint32_t max);

static uint32_t LOCAL_getDuplex(PHY_Device *pPhy);
static uint32_t LOCAL_getSpeed(PHY_Device *pPhy);
static uint32_t LOCAL_getLoopback(PHY_Device *pPhy);
static uint32_t LOCAL_getLinked(PHY_Device *pPhy);

static void LOCAL_MDIO_WaitForAccessComplete(const MDIO_State *pMdio, const PHY_Device *pPhy);
static void LOCAL_MDIO_UserAccess       (const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t method, uint32_t regadr, uint32_t data);
static void LOCAL_MDIO_DisablePHY       (const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t phyNum);
static void LOCAL_MDIO_PHYTimeOut       (MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_ResetPHY         (const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t phyNum);
static void LOCAL_MDIO_DefaultState     (const MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_FindingState     (const MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_FoundState       (MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_LinkedState      (MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_LinkWaitState    (MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_LoopbackState    (MDIO_State *pMdio, const PHY_Device *pPhy);
static void LOCAL_MDIO_NwayStartState   (MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_NwayWaitState    (MDIO_State *pMdio, PHY_Device *pPhy);

static uint32_t LOCAL_MDIO_MdixSupported(MDIO_State *pMdio, PHY_Device *pPhy);
static void LOCAL_MDIO_MdixDelay(MDIO_State *pMdio, PHY_Device *pPhy);

#if defined(MDIO_DEBUG)
static void LOCAL_MDIO_DumpPHY(MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t p);
static void LOCAL_MDIO_DumpState(MDIO_State *pMdio, const PHY_Device *pPhy);
static void LOCAL_MDIO_DumpPHYDetailed(MDIO_State *pMdio, const PHY_Device *pPhy);
#endif


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

uint32_t RandomSeed = 1U;

#if !defined(NSP_DYNAMIC_ALLOCATION)
MDIO_State MDIO_stateObj;
#endif

/* Data to keep track of open references to the MDIO State structure */
static uint32_t     LOCAL_mdioRefCount = 0;
static MDIO_State  *LOCAL_mdioRef     = NULL;

#ifdef MDIO_DEBUG
static char *lstate[]={"NULL","FINDING","FOUND","NWAY_START","NWAY_WAIT","LINK_WAIT","LINKED","LOOPBACK"};
#endif

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

MDIO_Handle MDIO_open(const MDIO_Config *pConfig)
{
    MDIO_State *pMdio = NULL;
    uint32_t    i;
    uint32_t    key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_mdioRefCount++;

    if ((uint32_t)1U == LOCAL_mdioRefCount)
    {
        uint32_t clkdiv;

#if defined(NSP_DYNAMIC_ALLOCATION)
        pMdio = (MDIO_State *) calloc(1U, sizeof(MDIO_State));
#else
        pMdio = &MDIO_stateObj;
#endif

        /* Zero init the MDIO State structure */
        memset(pMdio, 0, sizeof(MDIO_State));

        /* Set the base address */
        pMdio->miibase = pConfig->baseAddress;

        /* Set the callback fxn */
        if (NULL != pConfig->phyFoundCallback)
        {
            pMdio->phyFoundCallback = pConfig->phyFoundCallback;
        }

        /* Check that the channel supplied is within range */
        if ((myMDIO_VER & 0x0FFFFU) > 0x0102U)
        {
            pMdio->highestChannel = myMDIO_CONTROL >> (uint32_t)24U;
        }
        else
        {
            pMdio->highestChannel = myMDIO_CONTROL >> (uint32_t)8U;
        }
        pMdio->highestChannel &= 0x1FU;


        /* Calculate the correct value for the mclkdiv */
        if (0 != pConfig->mdioClockFrequency)
        {
            clkdiv = (uint32_t) (pConfig->mdioClockFrequency / pConfig->mdioBusFrequency) - 1U;
        }
        else
        {
            clkdiv = 0xFFU;
        }

#if defined(USE_CSLR)
        myMDIO_CONTROL =
            CSL_FMK(GMACSW_MDIO_CONTROL_ENABLE,1U) |
            CSL_FMK(GMACSW_MDIO_CONTROL_CLKDIV,clkdiv);
#else

#endif
        /* Set initial state to FINDING for each phy device */
        for (i = 0; i < MAC_NUM_PORTS; i++)
        {
            /* Set to FINDING state to start with */
            pMdio->phy[i].phyState |= PHY_FIND_TO;
            pMdio->phy[i].phyState |= FINDING;
            pMdio->phy[i].phyState |= PHY_CHANGE;
        }

        /* Save a pointer to the state structure to be used to provide a reference for future open calls */
        LOCAL_mdioRef = pMdio;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, Stats was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
         pMdio = LOCAL_mdioRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return (MDIO_Handle) pMdio;
}

uint32_t MDIO_close(MDIO_Handle hMdio)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    uint32_t retVal = MDIO_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_mdioRefCount--;

    if (0U == LOCAL_mdioRefCount)
    {
        /* Reset the local reference holder */
        LOCAL_mdioRef = NULL;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pMdio);
#else
        memset(pMdio, 0 , sizeof(MDIO_State));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

/*Function added to check link status from HW regs*/
uint32_t MDIO_getPhyLink(MDIO_Handle hMdio, uint32_t macNum)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];
    uint32_t phyMask = pPhy->phyMask;
    uint32_t phyNum=0U, phyAcks, i, j;

    phyAcks = myMDIO_ALIVE;
    /* Only interested in 'our' phys */
    phyAcks &= phyMask;

    j = 1U;
    for (i = 0; i < (uint32_t)32U; i++)
    {
        if ((j & phyAcks) != 0)
        {
            break;
        }
        j = j << 1U;
    }

    if ((phyAcks != 0) && (i < (uint32_t)32U))
    {
        phyNum = i;
    }

    uint32_t retVal = 0;

    if ((uint32_t)1U == (uint32_t)((uint32_t)0x00000001U & (myMDIO_LINK >> phyNum)))
    {
        retVal = 1U;
    }
    else
    {
        retVal = 0U;
    }

    return retVal;
}

uint32_t MDIO_ioctl(MDIO_Handle hMdio, uint32_t cmd, void *param, uint32_t size)
{
    uint32_t retVal = MDIO_SUCCESS;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_MDIO_GET_LINKSTATUS:
        {
            /* FIXME */
            retVal = MDIO_SUCCESS;
            break;
        }

        case GMACSW_IOCTL_MDIO_WRITE_PHY_REGISTER:
        {
            if ((sizeof(MDIO_rdWrphyRegIoctlCmd) != size) || (NULL == param))
            {
                retVal = MDIO_MALFORMED_IOCTL;
            }
            else
            {
                MDIO_rdWrphyRegIoctlCmd *cmd = (MDIO_rdWrphyRegIoctlCmd *)param;
                MDIO_userAccessWrite(hMdio,&hMdio->phy[cmd->portNum], cmd->regAddr, *cmd->regVal);
                retVal = MDIO_SUCCESS;
            }
            break;
        }
        case GMACSW_IOCTL_MDIO_READ_PHY_REGISTER:
        {
            if ((sizeof(MDIO_rdWrphyRegIoctlCmd) != size) || (NULL == param))
            {
                retVal = MDIO_MALFORMED_IOCTL;
            }
            else
            {
                MDIO_rdWrphyRegIoctlCmd *cmd = (MDIO_rdWrphyRegIoctlCmd *)param;
                MDIO_userAccessRead(hMdio,&hMdio->phy[cmd->portNum], cmd->regAddr, cmd->regVal);
                retVal = MDIO_SUCCESS;
            }
            break;
        }
        case GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER:
        {
            if ((sizeof(MDIO_rdWrphyRegIoctlCmd) != size) || (NULL == param))
            {
                retVal = MDIO_MALFORMED_IOCTL;
            }
            else
            {
                MDIO_rdWrphyRegIoctlCmd *cmd = (MDIO_rdWrphyRegIoctlCmd *)param;
                MDIO_userAccessWriteIndirect(hMdio,&hMdio->phy[cmd->portNum], cmd->regAddr, *cmd->regVal);
                retVal = MDIO_SUCCESS;
            }
            break;
        }
        case GMACSW_IOCTL_MDIO_READ_DP83867_PHY_INDIRECT_REGISTER:
        {
            if ((sizeof(MDIO_rdWrphyRegIoctlCmd) != size) || (NULL == param))
            {
                retVal = MDIO_MALFORMED_IOCTL;
            }
            else
            {
                MDIO_rdWrphyRegIoctlCmd *cmd = (MDIO_rdWrphyRegIoctlCmd *)param;
                MDIO_userAccessReadIndirect(hMdio,&hMdio->phy[cmd->portNum], cmd->regAddr, cmd->regVal);
                retVal = MDIO_SUCCESS;
            }
            break;
        }
        default:
        {
            retVal = MDIO_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}

/* MDIO_tic is called every 100ms to process PHY state machine */
uint32_t MDIO_tic(MDIO_Handle hMdio, uint32_t macNum, uint32_t* mdioStatus)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    uint32_t    *phyState = &pPhy->phyState;
    uint32_t    currentState;
    uint32_t    retVal = MDIO_SUCCESS;

    *mdioStatus = MDIO_EVENT_NOCHANGE;

    /*Act on current state of the PHY */
    currentState = *phyState;
    switch (currentState&PHY_STATE_MASK)
    {
        case FINDING:
            LOCAL_MDIO_FindingState(pMdio, pPhy);
            break;
        case FOUND:
            /* Call PHY found callback for user-specific PHY configuration */
            if (hMdio->phyFoundCallback != NULL)
            {
                (*hMdio->phyFoundCallback)(macNum, pPhy->phyAddr);
            }

            LOCAL_MDIO_FoundState(pMdio, pPhy);
            break;
        case NWAY_START:
            LOCAL_MDIO_NwayStartState(pMdio, pPhy);
            break;
        case NWAY_WAIT:
            LOCAL_MDIO_NwayWaitState(pMdio, pPhy);
            break;
        case LINK_WAIT:
            LOCAL_MDIO_LinkWaitState(pMdio, pPhy);
            break;
        case LINKED:
            LOCAL_MDIO_LinkedState(pMdio, pPhy);
            break;
        case LOOPBACK:
            LOCAL_MDIO_LoopbackState(pMdio, pPhy);
            break;
        default:
            LOCAL_MDIO_DefaultState(pMdio, pPhy);
            break;
    }

    /* Dump state info if a change has been detected */
#ifdef MDIO_DEBUG
    if ((currentState & (~PHY_TIM_MASK))!=( (*phyState)&(~PHY_TIM_MASK) ))
    {
        LOCAL_MDIO_DumpState(pMdio, pPhy);
    }
#endif

    /* Check if MDI/MDIX mode switch is needed */
    if ((*phyState & PHY_MDIX_SWITCH) != 0)
    {
        /* Clear PHY_MDIX flip indicator */
        *phyState &= ~PHY_MDIX_SWITCH;
        /* Update the PHY status */
        MDIO_updatePhyStatus(hMdio, macNum);
    }
    else
    {
        /* Return state change to user */
        /* CHECK : report MDIO_LINKEVENTS as MDIO_EVENT_NOCHANGE, MDIO_EVENT_LINKDOWN,
         * MDIO_EVENT_PHYERROR,MDIO_EVENT_LINKUP
         * Currently PHY_CHNG_MASK set for any state transition
         */
        if ((*phyState & PHY_CHNG_MASK) != 0)
        {
            if ( ((*phyState & PHY_STATE_MASK) == LINKED) && ((currentState & PHY_STATE_MASK) != LINKED) )
            {
                /* we have just entered Linked state */
                *mdioStatus = MDIO_EVENT_LINKUP;
            }
            if (  ((currentState & PHY_STATE_MASK) == LINKED) && ((*phyState & PHY_STATE_MASK) != LINKED) )
            {
                /* we started in Linked state and we have a state change */
                *mdioStatus = MDIO_EVENT_LINKDOWN;
            }
            /* Clear the PHY_CHNG indicator */
            *phyState &= ~PHY_CHNG_MASK;
            /* Update the PHY status */
            MDIO_updatePhyStatus(hMdio, macNum);
        }
    }

    return retVal;
}

uint32_t MDIO_phyInit(MDIO_Handle hMdio, uint32_t macNum, const PHY_Config *pConfig)
{
    MDIO_State *pMdio   = (MDIO_State *) hMdio;
    PHY_Device *pPhy    = &pMdio->phy[macNum];

    pPhy->macNum        = macNum;
    pPhy->phyMask       = pConfig->phyMask;
    pPhy->MLinkMask     = pConfig->MLinkMask;
    pPhy->MdixMask      = pConfig->MdixMask;
    pPhy->phyState      &= ~PHY_MDIX_MASK;   /* Set initial State to MDI */

    /* Configure the MDIO params, i.e. speed, duplex */
    if ((pConfig->mdioModeFlags & MDIO_MODEFLG_NOPHY) != 0)
    {
        pPhy->phyMode = NWAY_NOPHY;
    }
    else if ((pConfig->mdioModeFlags & MDIO_MODEFLG_AUTONEG) != 0)
    {
        /* If this MAC port is marked for internal PHY loopback,
         * configure the MDIO parameters appropriately.
         */
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_LOOPBACK) != 0)
        {
            pPhy->phyMode = NWAY_LPBK|NWAY_AUTO|NWAY_FD100|NWAY_FD10|NWAY_HD100|NWAY_HD10;
        }
        else
        {
            pPhy->phyMode = NWAY_AUTO|NWAY_FD1000|NWAY_FD100|NWAY_FD10|NWAY_HD100|NWAY_HD10;
        }
    }
    else
    {
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_HD10) != 0)
        {
            pPhy->phyMode = NWAY_HD10;
        }
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_FD10) != 0)
        {
            pPhy->phyMode |= NWAY_FD10;
        }
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_HD100) != 0)
        {
            pPhy->phyMode |= NWAY_HD100;
        }
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_FD100) != 0)
        {
            pPhy->phyMode |= NWAY_FD100;
        }
        if ((pConfig->mdioModeFlags & MDIO_MODEFLG_FD1000) != 0)
        {
            pPhy->phyMode |= NWAY_FD1000;
        }
    }

    MDIO_setPhyMode(hMdio, macNum, pPhy->phyMode);

    return MDIO_SUCCESS;
}

uint32_t MDIO_getLinkStatus(MDIO_Handle hMdio, uint32_t macNum, uint32_t *linkStatus)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    *linkStatus = ((LOCAL_getSpeed(pPhy) + (uint32_t)1U) << (uint32_t)1U) + LOCAL_getDuplex(pPhy);

    return MDIO_SUCCESS;
}

uint32_t MDIO_getPhyAddr(MDIO_Handle hMdio, uint32_t macNum, uint32_t *pPhyAddr)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    *pPhyAddr = pPhy->phyAddr;

    return MDIO_SUCCESS;
}

uint32_t MDIO_updatePhyStatus(MDIO_Handle hMdio, uint32_t macNum)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    PHY_Status *phyStatus = &pPhy->phyStatus;

    uint32_t        phyMode     = pPhy->phyMode;
    uint32_t        macControl  = GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL;

    /* No PHY Condition */
    if ((phyMode & NWAY_NOPHY) != 0)
    {
        /* Write mac control register from stored value */
        macControl |= ((uint32_t)1U << CSL_GMACSW_SL_MACCONTROL_FULLDUPLEX_SHIFT);
        GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL = macControl;
        macControl= GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL;
    }
    else
    {
        /* If loopback set in hardware, set link to ON */
        if (NOT_ZERO(macControl & CSL_GMACSW_SL_MACCONTROL_LOOPBACK_MASK))
        {
            phyStatus->phyLinked = 1U;
        }
        else
        {
            if ((phyMode & NWAY_LPBK) != 0)
            {
                phyStatus->phyLinked = LOCAL_getLoopback(pPhy);
            }
            else
            {
                phyStatus->phyLinked = LOCAL_getLinked(pPhy);
            }

            if (phyStatus->phyLinked != 0)
            {
                /*  Retreive Duplex and Speed and the PHY Number  */
                if ((phyMode & NWAY_LPBK) != 0)
                {
                    phyStatus->phyDuplex = 1U;
                }
                else
                {
                    phyStatus->phyDuplex = LOCAL_getDuplex(pPhy);
                }
                phyStatus->phySpeed = LOCAL_getSpeed(pPhy);
                MDIO_getPhyAddr(hMdio, macNum, &phyStatus->phyNum);

                /* Adjust MAC control settings for speed and duplex */
                if (phyStatus->phySpeed != 2U)
                {
                    /* Not a gigabit link, so clear the GIG bit*/
                    macControl &= ~CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U);
                    /*
                     * The IFCTL_A bit really only applies for RMII mode, but we will
                     * just set it (100Mbps) or clear it (10Mbps) for all modes
                     */
                    if (phyStatus->phySpeed == 1U)
                    {
                        macControl |= CSL_FMK(GMACSW_SL_MACCONTROL_IFCTL_A, 1U);
                    }
                    else
                    {
                        if (phyStatus->phySpeed == 0U)
                        {
                            macControl &= ~CSL_FMK(GMACSW_SL_MACCONTROL_IFCTL_A, 1U);
                        }
                    }
                }
                else
                {
                    macControl |= CSL_FMK(GMACSW_SL_MACCONTROL_GIG, 1U);
                }

                if (phyStatus->phyDuplex != 0)
                {
                    macControl |= CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U);
                }
                else
                {
                    macControl &= ~CSL_FMK(GMACSW_SL_MACCONTROL_FULLDUPLEX, 1U);
                }
            }

            /* Write mac control register from stored value */
            GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL = macControl;
            macControl = GMACSW_REGS->SL.MAC[macNum].SL_MACCONTROL;
        }
    }

    return MDIO_SUCCESS;
}

uint32_t MDIO_setPhyMode(MDIO_Handle hMdio, uint32_t macNum, uint32_t phyMode)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    uint32_t *phyState = &pPhy->phyState;
    uint32_t currentState;

    pPhy->phyMode = phyMode;
    *phyState &= ~PHY_SMODE_MASK;

    if ((phyMode & NWAY_LPBK) != 0)
    {
        *phyState |= SMODE_LPBK;
    }
    if ((phyMode & NWAY_AUTO) != 0)
    {
        *phyState |= SMODE_AUTO;
    }
    if ((phyMode & NWAY_FD1000) != 0)
    {
        *phyState |= SMODE_FD1000;
    }
    if ((phyMode & NWAY_FD100) != 0)
    {
        *phyState |= SMODE_FD100;
    }
    if ((phyMode & NWAY_HD100) != 0)
    {
        *phyState |= SMODE_HD100;
    }
    if ((phyMode & NWAY_FD10) != 0)
    {
        *phyState |= SMODE_FD10;
    }
    if ((phyMode & NWAY_HD10) != 0)
    {
        *phyState |= SMODE_HD10;
    }

    /* Return state machine back to found state to renegotiate link */
    currentState = *phyState & PHY_STATE_MASK;
    if ( (currentState == NWAY_START) || (currentState == NWAY_WAIT) ||
         (currentState == LINK_WAIT)  || (currentState == LINKED)    || (currentState == LOOPBACK) )
    {
        *phyState = ( *phyState & ~PHY_STATE_MASK) | FOUND | PHY_CHANGE;
    }

#if defined(MDIO_DEBUG)
     mdioPrintf("SetPHYMode:%08X Auto:%d, FD10:%d, HD10:%d, FD100:%d, HD100:%d, FD1000:%d LPBK:%d\n", phyMode,
        (phyMode & NWAY_AUTO), (phyMode & MII_NWAY_FD10),(phyMode & MII_NWAY_HD10),(phyMode & MII_NWAY_FD100),
        (phyMode & MII_NWAY_HD100), (phyMode & NWAY_FD1000),
        (phyMode & NWAY_LPBK)  );

    LOCAL_MDIO_DumpState(pMdio, pPhy);
#endif
    return MDIO_SUCCESS;
}

uint32_t MDIO_getPhyMode(MDIO_Handle hMdio, uint32_t macNum, uint32_t *pPhyMode)
{
    MDIO_State *pMdio = (MDIO_State *) hMdio;
    PHY_Device *pPhy = (PHY_Device *) &pMdio->phy[macNum];

    uint32_t  phyMode = pPhy->phyMode;
    uint32_t  status_reg = 0, control_reg = 0, advertize_reg;

    /* If not NOPHY mode and PHY is found, then talk to it to get the mode info */
    if (((phyMode & NWAY_NOPHY) == 0) && (pPhy->isFound != 0U))
    {
        /* Not NOPHY mode */
        phyMode = 0;

        if (1U == pPhy->isGigabitPHY)
        {
            /* Read gig control register */
            MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTCR, &control_reg);
            /* Read gig status register */
            MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTSR, &status_reg);

            /* figure out if gig connected at FD 1000 or not first */
            if (((control_reg & MII_NWAY_MY_FD1000) != 0U) && ((status_reg & MII_NWAY_REM_FD1000) != 0U) )
            {
                phyMode |= NWAY_FD1000;
            }
        }

        MDIO_userAccessRead(pMdio, pPhy, PHY_BMCR, &control_reg);
        if ((control_reg & MII_AUTO_NEGOTIATE_EN) != 0 )
        {
            phyMode |= NWAY_AUTO;
        }
        MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, &status_reg);
        MDIO_userAccessRead(pMdio, pPhy, PHY_ANAR, &advertize_reg);

        /* Check for 10/100 capabilities of PHYs */
        if (((control_reg & MII_PHY_100) != 0) || ((phyMode & NWAY_AUTO) != 0) )
        {
            if ((advertize_reg & MII_NWAY_FD100) != 0)
            {
                phyMode |= NWAY_FD100;
            }
            if ((advertize_reg & MII_NWAY_HD100) != 0)
            {
                phyMode |= NWAY_HD100;
            }
        }

        if (((control_reg & MII_PHY_100) == 0) || ((phyMode & NWAY_AUTO) != 0) )
        {
            if ((advertize_reg & MII_NWAY_FD10) != 0)
            {
                phyMode |= NWAY_FD10;
            }
            if ((advertize_reg & MII_NWAY_HD10) != 0)
            {
                phyMode |= NWAY_HD10;
            }
        }
    #if defined(MDIO_DEBUG)
        LOCAL_MDIO_DumpState(pMdio, pPhy);
    #endif
    }

    *pPhyMode = phyMode;

    return MDIO_SUCCESS;
}

/*!**********************************
***
*** Waits for MDIO_USERACCESS to be ready and reads data
*** If 'WaitForData' set, waits for read to complete and returns Data,
*** otherwise returns 0
*** Note: 'data' is 16 bits but we use 32 bits
***        to be consistent with rest of the code.
***
**************************************/
uint32_t MDIO_userAccessRead(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t *data)
{
    uint32_t localData;

    LOCAL_MDIO_WaitForAccessComplete(pMdio, pPhy);  /* Wait until UserAccess ready */
    LOCAL_MDIO_UserAccess(pMdio, pPhy, MDIO_USERACCESS_READ, regadr, (uint32_t)0U);
    LOCAL_MDIO_WaitForAccessComplete(pMdio, pPhy);  /* Wait for Read to complete */

#if defined(USE_CSLR)
    localData = CSL_FEXT(myMDIO_USERACCESS,GMACSW_MDIO_USERACCESS0_DATA);
    if (NULL != data)
    {
        *data = localData;
    }
#else

#endif

    return MDIO_SUCCESS;
}

/*!**********************************
***
*** Waits for MDIO_USERACCESS to be ready and writes data
***
**************************************/
uint32_t MDIO_userAccessWrite(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t data)
{
    /* Wait until UserAccess ready */
    LOCAL_MDIO_WaitForAccessComplete(pMdio, pPhy);
    LOCAL_MDIO_UserAccess(pMdio, pPhy, MDIO_USERACCESS_WRITE, regadr, data);

    return MDIO_SUCCESS;
}

/*!**********************************
***
*** Waits for MDIO_USERACCESS to be ready and writes data to DP83867 PHY extended set
*** of registers using indirect method.
***
**************************************/
uint32_t MDIO_userAccessWriteIndirect(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t data)
{
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_REGCR, DP83867_DEVADDR);
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_ADDAR, regadr);
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_REGCR,
                                    DP83867_WRITE_INDIRECT_NOPOSTINCREMENT);
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_ADDAR, data);

    return MDIO_SUCCESS;
}

/*!**********************************
***
*** Waits for MDIO_USERACCESS to be ready and reads data to DP83867 PHY extended set
*** of registers using indirect method.
***
**************************************/
uint32_t MDIO_userAccessReadIndirect(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t regadr, uint32_t *data)
{
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_REGCR, DP83867_DEVADDR);
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_ADDAR, regadr);
    MDIO_userAccessWrite(pMdio, pPhy, DP83867_REGCR,
                                    DP83867_WRITE_INDIRECT_NOPOSTINCREMENT);
    MDIO_userAccessRead(pMdio, pPhy, DP83867_ADDAR, data);

    return MDIO_SUCCESS;
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* LOCAL_getLoopback is called to Determine if the LOOPBACK state has been reached*/
static uint32_t LOCAL_getLoopback(PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    return (uint32_t)((*phyState & PHY_STATE_MASK) == LOOPBACK);
}

/* MDIO_GetLinked is called to Determine if the LINKED state has been reached*/
static uint32_t LOCAL_getLinked(PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    return (uint32_t)((*phyState & PHY_STATE_MASK) == LINKED);
}

/* Simple Query Functions for reporting speed,duplex */
/* MDIO_GetDuplex is called to retrieve the Duplex info */
static uint32_t LOCAL_getDuplex(PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;

    return (*phyState & PHY_DUPLEX_MASK) >> PHY_DUPLEX_OFFSET;
}

/* LOCAL_getSpeed is called to retreive the Speed info */
static uint32_t LOCAL_getSpeed(PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;

    return (*phyState & PHY_SPEED_MASK) >> PHY_SPEED_OFFSET;
}

static uint32_t LOCAL_random(void)
{
    RandomSeed = (RandomSeed * (uint32_t)1103515245U) + (uint32_t)12345U;
    return (RandomSeed/(uint32_t)65536U) % ((uint32_t)COMMON_RANDOM_MAX + (uint32_t)1U);
}

static uint32_t LOCAL_randomRange(uint32_t min, uint32_t max)
{
    uint32_t iTmp;

    iTmp =  LOCAL_random();
    iTmp %= (max - min) + 1U;
    iTmp += min;
    return iTmp;
}

/* returns 0 if current PHY has AutoMdix support, otherwise 0 */
static uint32_t LOCAL_MDIO_MdixSupported(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    uint32_t phyNum;
    uint32_t ret;

    if ((uint32_t)0 == (pPhy->phyMode & NWAY_AUTOMDIX))
    {
        ret = 0;  /* AutoMdix not turned on */
    }
    else
    {
        phyNum = (*phyState & PHY_DEV_MASK) >> PHY_DEV_OFFSET;
        if ((uint32_t)0 == (((uint32_t)1U << phyNum) & pPhy->MdixMask))
        {
            ret = 0;  /*  PHY does not support AutoMdix*/
        }
        else
        {
            ret = 1U;
        }
    }
    return ret;
}

/* If current PHY has AutoMdix support add Mdix Delay to the Timer State Value */
static void LOCAL_MDIO_MdixDelay(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t Delay;
    uint32_t *phyState = &pPhy->phyState;

    if (LOCAL_MDIO_MdixSupported(pMdio, pPhy) != 0)
    {
        /* Get the Delay value in milli-seconds and convert to ten-milli second value */
        Delay = LOCAL_randomRange(AUTOMDIX_DELAY_MIN, AUTOMDIX_DELAY_MAX);
        Delay /= 10U;

        /*  Add AutoMidx Random Switch Delay to AutoMdix Link Delay */
        Delay += (PHY_MDIX_TO >> PHY_TIM_OFFSET);

        /* Change Timeout value to AutoMdix standard */
        *phyState &= ~PHY_TIM_MASK;  /* Clear current Time out value */
        *phyState |=  Delay << PHY_TIM_OFFSET;     /* Set new value */
    }
}

static void LOCAL_MDIO_DisablePHY(const MDIO_State *pMdio, const PHY_Device *pPhy,uint32_t phyNum)
{
    MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, MII_PHY_ISOLATE | MII_PHY_PDOWN);
}

static void LOCAL_MDIO_FindingState(const MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    uint32_t  phyMask  = pPhy->phyMask;
    uint32_t  phyNum, i, j, phyAcks;

    phyNum = PHY_NOT_FOUND;

    if ((*phyState & PHY_TIM_MASK) != 0)
    {
        *phyState = (*phyState & ~PHY_TIM_MASK) | ((*phyState & PHY_TIM_MASK) - ((uint32_t)1U << PHY_TIM_OFFSET));
    }
    else
    {
        phyAcks = myMDIO_ALIVE;
        phyAcks &= phyMask;   /* Only interested in 'our' phys */

        j = 1U;
        for (i = 0; i < (uint32_t)32U; i++)
        {
            if ((j & phyAcks) != 0)
            {
                break;
            }
            j = j << 1U;
        }

        if ((phyAcks != 0) && (i < (uint32_t)32U))
        {
            phyNum = i;
        }

        if (phyNum != PHY_NOT_FOUND)
        {
            /*  PHY Found! */
            pPhy->phyAddr = phyNum;
            pPhy->isFound = 1;
            *phyState = (*phyState & ~PHY_DEV_MASK) | ((phyNum & PHY_DEV_MASK) << PHY_DEV_OFFSET);
            *phyState = (*phyState & ~PHY_STATE_MASK) | FOUND;
            *phyState |= PHY_CHANGE;
#if defined(MDIO_DEBUG)
            mdioPrintf("MDIO_FindingState: phyNum: %d\n",phyNum);
#endif
        }
        else
        {
#if defined(MDIO_DEBUG)
            mdioPrintf("MDIO_FindingState: Timed Out looking for a PHY!\n");
#endif
            *phyState |= PHY_RECK_TO;  /* Set Timer */
        }
    }
}

static void LOCAL_MDIO_FoundState(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState  = &pPhy->phyState;
    uint32_t  phyMask   = pPhy->phyMask;
    uint32_t  MLinkMask = pPhy->MLinkMask;

    uint32_t  phyNum;
    uint32_t  phyStatus;
    uint32_t  NWAYadvertise;
    uint32_t  NWAY1000advertise=0;
    uint32_t  m;
    uint32_t  num;
    uint32_t  i, j;
    uint32_t  phyAcks;
    uint32_t  phySel;

    static uint32_t auto_neg1 = 0xFFFFFFFFU, auto_neg2 = 0xFFFFFFFFU;

    if ((uint32_t)0 == (*phyState & PHY_SMODE_MASK))
    {
        return;
    }

    phyNum = (*phyState & PHY_DEV_MASK) >> PHY_DEV_OFFSET;
    phyAcks = myMDIO_ALIVE;
    phyAcks &= phyMask;   /* Only interested in 'our' PHYs */

    /* Will now isolate all our PHYs, except the one we have decided to use */
    j = 1U;
    for (num = 0; num < (uint32_t)32U; num++)
    {
        if ((phyAcks & j) != 0)
        {
            if (num != phyNum)
            {
                /* Do not disabled Found PHY */
                LOCAL_MDIO_DisablePHY(pMdio, pPhy, num);
            }
        }
        j = j << 1U;
    }
    /* If Aries SWR2 reset then don't reset phy*/
    /*  Reset the PHY and proceed with auto-negotiation */
    if ((auto_neg1 & ((uint32_t)1U << phyNum)) == 0)
    {
        LOCAL_MDIO_ResetPHY(pMdio, pPhy, phyNum);
    }

    /* Now setup the MDIOUserPHYSel register */
#if defined(USE_CSLR)
    phySel = CSL_FMK(GMACSW_MDIO_USERPHYSEL0_PHYADDRMON, phyNum);

    /* Set the way Link will be Monitored */
    /* Check the Link Selection Method */
    if ((((uint32_t)1U << phyNum) & MLinkMask) != 0 )
    {
        phySel |= CSL_FMK(GMACSW_MDIO_USERPHYSEL0_LINKSEL, 1U);
    }
#else
#endif

    myMDIO_USERPHYSEL = (uint32_t)phySel;  /* update PHYSEL */

    /* Get the PHY Status */
    MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, &phyStatus);

    /*
     * For PHY Internal loopback test, need to wait until PHY
     *  found, then set Loopback
     */
    if ((*phyState & SMODE_LPBK) != 0)
    {
        /* Set PHY in Loopback */
        MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, MII_PHY_LOOP|MII_PHY_FD);
        /* Do a read to ensure PHY_LOOP has completed */
        MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, NULL);
        *phyState = (*phyState & ~PHY_STATE_MASK) | LOOPBACK;
        *phyState |= PHY_CHANGE;
        return;
    }

#if defined(MDIO_DEBUG)
    mdioPrintf("Enable PHY to negotiate external connection\n");
#endif
    NWAYadvertise=MII_NWAY_SEL;
    if ((*phyState & SMODE_FD100) != 0)
    {
        NWAYadvertise |= MII_NWAY_FD100;
    }
    if ((*phyState & SMODE_HD100) != 0)
    {
        NWAYadvertise |= MII_NWAY_HD100;
    }
    if ((*phyState & SMODE_FD10) != 0)
    {
        NWAYadvertise |= MII_NWAY_FD10;
    }
    if ((*phyState & SMODE_HD10) != 0)
    {
        NWAYadvertise |= MII_NWAY_HD10;
    }

    if ((phyStatus & MII_EXTENDED_STATUS) != 0)
    {
        uint32_t extendedStatus;

        /* Read extended status register to get gigabit support info */
        MDIO_userAccessRead(pMdio, pPhy, PHY_EXSR, &extendedStatus);
        if ((extendedStatus & MII_EXSR_FD1000T) != 0U)
        {
            pPhy->isGigabitPHY = 1U;
            if ((*phyState & SMODE_FD1000) != 0)
            {
                NWAY1000advertise |= MII_NWAY_MY_FD1000;
            }
        }
        else
        {
            /* Not a full-duplex gigabit capable PHY */
            pPhy->isGigabitPHY = 0U;
            *phyState &= ~SMODE_FD1000;
        }
    }

    *phyState &= ~(PHY_TIM_MASK | PHY_STATE_MASK);
    if (((phyStatus & MII_NWAY_CAPABLE) != 0) && ((*phyState & SMODE_AUTO) != 0) )
    {
        /* The PHY is capable of auto negotiation! */
        if ((auto_neg1 & ((uint32_t)1U << phyNum)) == 0)
        {
            /*For NWAY compliant PHYs                                                */
            MDIO_userAccessWrite(pMdio, pPhy, PHY_ANAR, NWAYadvertise);
            /* for gig negotiation */
            if(pPhy->isGigabitPHY != 0U)
            {
                MDIO_userAccessWrite(pMdio, pPhy, PHY_1000BTCR, NWAY1000advertise);
            }

            dprint("NWAY Advertising: ");
            if ((*phyState & SMODE_FD1000) != 0)
            {
                dprint("FullDuplex-1000");
            }
            if ((NWAYadvertise & MII_NWAY_FD100) != 0)
            {
                dprint("FullDuplex-100");
            }
            if ((NWAYadvertise & MII_NWAY_HD100) != 0)
            {
                dprint("HalfDuplex-100");
            }
            if ((NWAYadvertise & MII_NWAY_FD10) != 0)
            {
                dprint("FullDuplex-10");
            }
            if ((NWAYadvertise & MII_NWAY_HD10) != 0)
            {
                dprint("HalfDuplex-10");
            }

            dprint("\n");
            MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, MII_AUTO_NEGOTIATE_EN);
            MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, MII_AUTO_NEGOTIATE_EN | MII_RENEGOTIATE);
            *phyState |= PHY_CHANGE | PHY_NWST_TO | NWAY_START;
        }
        else
        {
            *phyState |= PHY_CHANGE | PHY_NWST_TO | NWAY_START;
            auto_neg1 = auto_neg1 & ~((uint32_t)1U << phyNum);
        }
    }
    else
    {
        /* The PHY is not capable of auto negotiation! */
        *phyState &= ~SMODE_AUTO;
        m = NWAYadvertise;
        j = 0x8000U;

        for (i = 0; i < (uint32_t)16U; i++)
        {
            if ((j & m) != 0)
            {
                break;
            }
            j = j >> 1U ;
        }
        m = j;
        j = 0;

        /* Figure out if gig connected at FD 1000 or not first */
        if ((NWAY1000advertise & MII_NWAY_MY_FD1000) == MII_NWAY_MY_FD1000)
        {
            j = MII_PHY_1000 | MII_PHY_FD;
        }
        else
        {
            if ((m & (MII_NWAY_FD100 | MII_NWAY_HD100)) != 0)
            {
                j = MII_PHY_100;
                m &= MII_NWAY_FD100|MII_NWAY_HD100;
            }
            if ((m & (MII_NWAY_FD100 | MII_NWAY_FD10)) != 0)
            {
                j |= MII_PHY_FD;
            }
        }
#if defined(MDIO_DEBUG)
        mdioPrintf("Requested PHY mode %s Duplex %s Mbps\n",(j & MII_PHY_FD) ? "Full":"Half",
                (j & MII_PHY_1000) ? "1000":((j & MII_PHY_100) ? "100":"10"));
#endif
        if ((auto_neg2 & ((uint32_t)1U << phyNum)) == 0)
        {
            if ((j & MII_PHY_1000) != 0)
            {
                MDIO_userAccessWrite(pMdio, pPhy,PHY_1000BTCR, j);
            }
            else
            {
                MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, j);
                MDIO_userAccessWrite(pMdio, pPhy, PHY_ANAR, NWAYadvertise);
            }
        }
        else
        {
            auto_neg2 = auto_neg2 & ~((uint32_t)1U << phyNum);
        }

        /* Set speed field */
        *phyState &= ~PHY_SPEED_MASK;
        if ((j & MII_PHY_1000) != 0)
        {
            *phyState |= (uint32_t)2U << PHY_SPEED_OFFSET;
        }
        if ((j & MII_PHY_100) != 0)
        {
            *phyState |= (uint32_t)1U << PHY_SPEED_OFFSET;
        }

        /* Set duplex field */
        *phyState &= ~PHY_DUPLEX_MASK;
        if ((j & MII_PHY_FD) != 0)
        {
            *phyState |= (uint32_t)1U << PHY_DUPLEX_OFFSET;
        }

        /* Update state, mark state as changed */
        *phyState |= PHY_CHANGE | PHY_LINK_TO | LINK_WAIT;
    }

    /* If AutoMdix add delay */
    LOCAL_MDIO_MdixDelay(pMdio, pPhy);
}

static void LOCAL_MDIO_ResetPHY(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t phyNum)
{
    uint32_t phyControlReg;

    /* Issue Reset command to the PHY */
    MDIO_userAccessWrite(pMdio, pPhy, PHY_BMCR, MII_PHY_RESET);

    /* Read control register until PHY Reset is complete */
    do
    {
        MDIO_userAccessRead(pMdio, pPhy, PHY_BMCR, &phyControlReg);
    }
    while ((uint32_t)(phyControlReg & (uint16_t)MII_PHY_RESET) != 0); /* Wait for Reset to clear */
}

static void LOCAL_MDIO_NwayStartState(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    uint32_t phyMode;

    /*Wait for Negotiation to start */
    MDIO_userAccessRead(pMdio, pPhy, PHY_BMCR, &phyMode);

    if((uint32_t)0 == (phyMode & MII_RENEGOTIATE))
    {
        MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, NULL); /*Flush pending latch bits*/
        *phyState &= ~(PHY_STATE_MASK | PHY_TIM_MASK);
        *phyState |= PHY_CHANGE | NWAY_WAIT | PHY_NWDN_TO;
        LOCAL_MDIO_MdixDelay(pMdio, pPhy);  /* If AutoMdix add delay */
    }
    else
    {
        if ((*phyState & PHY_TIM_MASK) != 0)
        {
            *phyState = (*phyState & ~PHY_TIM_MASK) | ((*phyState & PHY_TIM_MASK) - ((uint32_t)1U << PHY_TIM_OFFSET));
        }
        else
        {
            LOCAL_MDIO_PHYTimeOut(pMdio, pPhy);
        }
    }
}

static void LOCAL_MDIO_NwayWaitState(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t    *phyState = &pPhy->phyState;
    uint32_t    phyStatus;
    uint32_t    NWAYadvertise = 0, NWAYREadvertise = 0;
    uint32_t    NegMode = 0;
    uint32_t    i, j;

    MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, &phyStatus);

    if ((phyStatus & MII_NWAY_COMPLETE) != 0)
    {
        *phyState |= PHY_CHANGE;
        *phyState &= ~PHY_SPEED_MASK;
        *phyState &= ~PHY_DUPLEX_MASK;

        /* read gig status */
        if(pPhy->isGigabitPHY != 0U)
        {
            MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTCR, &NWAYadvertise);
            MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTSR, &NWAYREadvertise);
            /* figure out if gig connected at FD 1000 or not first */
            if (((NWAYadvertise & MII_NWAY_MY_FD1000) != 0) && ((NWAYREadvertise & MII_NWAY_REM_FD1000) != 0) )
            {
                NegMode = MII_NWAY_MY_FD1000;

                /* found 1000 negotiated connection! */
                dprint("Negotiated connection: ");
                dprint("FullDuplex 1000 Mbs\n");
            }
        }

        if (NegMode == 0U)
        {
            MDIO_userAccessRead(pMdio, pPhy, PHY_ANAR, &NWAYadvertise);
            MDIO_userAccessRead(pMdio, pPhy, PHY_ANLPAR, &NWAYREadvertise);

            /* continue checking for 100 and 10 connection */

            /* Negotiated mode is we and the remote have in common */
            NegMode = NWAYadvertise & NWAYREadvertise;

            dprint1("PHY: %d, ",(*phyState & PHY_DEV_MASK) >> PHY_DEV_OFFSET);
            dprint3("NegMode %04X, NWAYadvertise %04X, NWAYREadvertise %04X\n",
                NegMode,  NWAYadvertise, NWAYREadvertise);

            /* Limit negotiation to fields below */
            NegMode &= MII_NWAY_FD100 | MII_NWAY_HD100 | MII_NWAY_FD10 | MII_NWAY_HD10;

            if (0U == NegMode)
            {
                NegMode=(MII_NWAY_HD100|MII_NWAY_HD10)&NWAYadvertise; /*or 10 ?? who knows, PHY is not MII compliant*/

                dprint("Mdio:WARNING: Negotiation complete but NO agreement, default is HD\n");
#ifdef MDIO_DEBUG
                LOCAL_MDIO_DumpPHYDetailed(pMdio, pPhy);
#endif
            }

            j = 0x8000U;
            for (i = 0; i < (uint32_t)16U ; i++)
            {
                if ((j & NegMode) != 0)
                {
                    break;
                }
                j = j >> (uint32_t)1U;
            }

            NegMode = j;

            dprint("Negotiated connection: ");
            if ((NegMode & MII_NWAY_FD100) != 0)
            {
                dprint("FullDuplex 100 Mbs\n");
            }
            if ((NegMode & MII_NWAY_HD100) != 0)
            {
                dprint("HalfDuplex 100 Mbs\n");
            }
            if ((NegMode & MII_NWAY_FD10) != 0)
            {
                dprint("FullDuplex 10 Mbs\n");
            }
            if ((NegMode & MII_NWAY_HD10) != 0)
            {
                dprint("HalfDuplex 10 Mbs\n");
            }
        }

        if (NegMode != 0U)
        {
            if ((phyStatus & MII_PHY_LINKED) != 0)
            {
                *phyState = (*phyState & ~PHY_STATE_MASK) | LINKED;
            }
            else
            {
                *phyState = (*phyState & ~PHY_STATE_MASK) | LINK_WAIT;
            }

            /* Set speed field */
            *phyState &= ~PHY_SPEED_MASK;
            if ((NegMode & MII_NWAY_MY_FD1000) != 0)
            {
                *phyState |= (uint32_t)2U << PHY_SPEED_OFFSET;
            }
            if ((NegMode & (MII_NWAY_FD100 | MII_NWAY_HD100)) != 0)
            {
                *phyState |= (uint32_t)1U << PHY_SPEED_OFFSET;
            }

            /* Set the duplex field */
            *phyState &= ~PHY_DUPLEX_MASK;
            if ((NegMode & (MII_NWAY_MY_FD1000 | MII_NWAY_FD100 | MII_NWAY_FD10)) != 0)
            {
                *phyState |= (uint32_t)1U << PHY_DUPLEX_OFFSET;
            }
        }
    }
    else
    {
        if ((*phyState & PHY_TIM_MASK) != 0)
        {
            *phyState = (*phyState & ~PHY_TIM_MASK) | ((*phyState & PHY_TIM_MASK) - ((uint32_t)1U << PHY_TIM_OFFSET));
        }
        else
        {
            LOCAL_MDIO_PHYTimeOut(pMdio, pPhy);
        }
    }
}

static void LOCAL_MDIO_LinkWaitState(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    uint32_t  phyStatus;

    MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, &phyStatus);

    if ((phyStatus & MII_PHY_LINKED) != 0)
    {
        *phyState = (*phyState & ~PHY_STATE_MASK) | LINKED;
        *phyState |= PHY_CHANGE;
    }
    else
    {
        if ((*phyState & PHY_TIM_MASK) != 0)
        {
            *phyState = (*phyState & ~PHY_TIM_MASK) | ((*phyState & PHY_TIM_MASK) - ((uint32_t)1U << PHY_TIM_OFFSET));
        }
         else
        {
            LOCAL_MDIO_PHYTimeOut(pMdio, pPhy);
        }
    }
}

static void LOCAL_MDIO_PHYTimeOut(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;

    if(LOCAL_MDIO_MdixSupported(pMdio, pPhy) != 0)
    {
        /* AutoMdix is supported */
        /*  Indicate MDI/MDIX mode switch is needed */
        *phyState |= PHY_MDIX_SWITCH;

        /* Toggle the MDIX mode indicator */
        if ((*phyState & PHY_MDIX_MASK) == PHY_MDIX_EN)
        {
            /* Current State is MDIX, set to MDI by clearing PHY_MDIX field*/
            *phyState &= ~PHY_MDIX_MASK;
        }
        else
        {
            /* Current State is MDI, set to MDIX by setting PHY_MDIX_EN in the PHY_MDIX field*/
            *phyState = (*phyState & ~PHY_MDIX_MASK) | PHY_MDIX_EN;
        }

        /* Reset state machine to FOUND */
        *phyState = (*phyState & ~PHY_STATE_MASK) | FOUND;
    }
}

static void LOCAL_MDIO_LoopbackState(MDIO_State *pMdio, const PHY_Device *pPhy)
{
    return;
}

static void LOCAL_MDIO_LinkedState(MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    uint32_t  phyNum   = (*phyState & PHY_DEV_MASK) >> PHY_DEV_OFFSET;

    if ((myMDIO_LINK & ((uint32_t)1U << phyNum)) != 0)
    {
        return;  /* if still Linked, exit*/
    }

    /* Not Linked */
    *phyState &= ~(PHY_STATE_MASK | PHY_TIM_MASK);
    if ((*phyState & SMODE_AUTO) != 0)
    {
        *phyState |= PHY_CHANGE | NWAY_WAIT | PHY_NWDN_TO;
    }
    else
    {
        *phyState |= PHY_CHANGE | PHY_LINK_TO | LINK_WAIT;
    }

    LOCAL_MDIO_MdixDelay(pMdio, pPhy);  /* If AutoMdix add delay */
}

static void LOCAL_MDIO_DefaultState(const MDIO_State *pMdio, PHY_Device *pPhy)
{
    uint32_t *phyState = &pPhy->phyState;
    /* Awaiting a MDIO_Init call */
    *phyState |= PHY_CHANGE;
}

static void LOCAL_MDIO_WaitForAccessComplete(const MDIO_State *pMdio, const PHY_Device *pPhy)
{
#if defined(USE_CSLR)
    while(CSL_FEXT(myMDIO_USERACCESS,GMACSW_MDIO_USERACCESS0_GO) != 0U)
    {
    }
#endif
}

static void LOCAL_MDIO_UserAccess(const MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t method, uint32_t regadr, uint32_t data)
{
    uint32_t  control;

#if defined(USE_CSLR)
    control =  CSL_FMK(GMACSW_MDIO_USERACCESS0_GO,0x1U) |
               CSL_FMK(GMACSW_MDIO_USERACCESS0_WRITE, method) |
               CSL_FMK(GMACSW_MDIO_USERACCESS0_REGADR, regadr) |
               CSL_FMK(GMACSW_MDIO_USERACCESS0_PHYADR, pPhy->phyAddr) |
               CSL_FMK(GMACSW_MDIO_USERACCESS0_DATA, (data & 0xFFFFU));
#else

#endif

    myMDIO_USERACCESS = control;
}

#ifdef MDIO_DEBUG
/*! Debug print functions , exported for Apps */
static void LOCAL_MDIO_DumpState(MDIO_State *pMdio, const PHY_Device *pPhy)
{
    uint32_t state = pPhy->phyState;

    mdioPrintf("PHY: %d, ",(state&PHY_DEV_MASK)>>PHY_DEV_OFFSET);
    mdioPrintf("State: %d/%s, ",(state & PHY_STATE_MASK) >> PHY_STATE_OFFSET,
          lstate[(state & PHY_STATE_MASK) >> PHY_STATE_OFFSET]);
    mdioPrintf("Speed: %d, ",(state&PHY_SPEED_MASK)>>PHY_SPEED_OFFSET);
    mdioPrintf("Dup: %d, ",(state&PHY_DUPLEX_MASK)>>PHY_DUPLEX_OFFSET);
    mdioPrintf("Tim: %d, ",(state&PHY_TIM_MASK)>>PHY_TIM_OFFSET);
    mdioPrintf("SMode: %d, ",(state&PHY_SMODE_MASK)>>PHY_SMODE_OFFSET);
    mdioPrintf("Chng: %d",(state&PHY_CHNG_MASK)>>PHY_CHNG_OFFSET);
    mdioPrintf("\n");

    if ((state & PHY_STATE_MASK) != FINDING)
    {
        LOCAL_MDIO_DumpPHY(pMdio, pPhy, (state&PHY_DEV_MASK)>>PHY_DEV_OFFSET);
    }
}

static void LOCAL_MDIO_DumpPHY(MDIO_State *pMdio, const PHY_Device *pPhy, uint32_t p)
{
    uint32_t j, n, phyAcks;
    uint32_t phyRegAddr;
    uint32_t num;
    uint32_t phyMask  = pPhy->phyMask;

    phyAcks=myMDIO_ALIVE;
    phyAcks&=phyMask;   /* Only interested in 'our' PHYs */

    num = 0;
    for(j = 1; num < 32; num++)
    {
        if (0U != (phyAcks & j))
        {
            mdioPrintf("%2d%s:",num,(num==p)?">":" ");
            for(phyRegAddr=0; phyRegAddr<0x20 ; phyRegAddr++)
            {
                MDIO_userAccessRead(pMdio, pPhy, phyRegAddr, &n);
                mdioPrintf(" @0x%02x = 0x%04x\n", phyRegAddr, (n & 0x0FFFFU));
            }/* end of for loop */
            mdioPrintf("\n");
        }/* end of if conditional loop */
        j <<= 1;
    }/* end of for num loop */

    LOCAL_MDIO_DumpPHYDetailed(pMdio, pPhy);
}

static void LOCAL_MDIO_DumpPHYDetailed(MDIO_State *pMdio, const PHY_Device *pPhy)
{
    uint32_t    RegData, RegData2;
    uint32_t    phyNum = ( pPhy->phyState & PHY_DEV_MASK) >> PHY_DEV_OFFSET;

    phyNum = phyNum;
    MDIO_userAccessRead(pMdio, pPhy, PHY_BMCR, &RegData);
    mdioPrintf("phyControl: %04X, Lookback=%s, Speed=%s, Duplex=%s\n",
        RegData,
        (RegData & MII_PHY_LOOP) ? "On":"Off",
        (RegData & MII_PHY_1000) ? "1000" : (RegData & MII_PHY_100 ? "100":"10"),
        (RegData & MII_PHY_FD ) ? "Full":"Half");

    MDIO_userAccessRead(pMdio, pPhy, PHY_BMSR, &RegData);
    mdioPrintf("phyStatus: %04X, AutoNeg=%s, Link=%s\n",
        RegData,
        (RegData & MII_NWAY_COMPLETE) ? "Complete":"NotComplete",
        (RegData & MII_PHY_LINKED) ? "Up":"Down");

    MDIO_userAccessRead(pMdio, pPhy, PHY_ANAR, &RegData);
    MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTCR, &RegData2);
    mdioPrintf("phyMyCapability: %04X, 1000FD=%s, 100FD=%s, 100HD=%s, 10FD=%s, 10HD=%s\n",
        RegData,
        (RegData2 & MII_NWAY_MY_FD1000) ? "Yes":"No",
        (RegData & MII_NWAY_FD100) ? "Yes":"No",
        (RegData & MII_NWAY_HD100) ? "Yes":"No",
        (RegData & MII_NWAY_FD10) ? "Yes":"No",
        (RegData & MII_NWAY_HD10) ? "Yes":"No");

    MDIO_userAccessRead(pMdio, pPhy, PHY_ANLPAR, &RegData);
    MDIO_userAccessRead(pMdio, pPhy, PHY_1000BTSR, &RegData2);
    mdioPrintf("phyPartnerCapability: %04X, 1000FD=%s, 100FD=%s, 100HD=%s, 10FD=%s, 10HD=%s\n",
        RegData,
        (RegData2 & MII_NWAY_REM_FD1000 ) ? "Yes":"No",
        (RegData & MII_NWAY_FD100) ? "Yes":"No",
        (RegData & MII_NWAY_HD100) ? "Yes":"No",
        (RegData & MII_NWAY_FD10) ? "Yes":"No",
        (RegData & MII_NWAY_HD10) ? "Yes":"No");
}

#endif


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
