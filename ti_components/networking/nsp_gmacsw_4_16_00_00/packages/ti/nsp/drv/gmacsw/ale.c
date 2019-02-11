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
 *   \file  ale.c
 *
 *   \brief
 *          ALE module implementation
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
#include "gmacsw_al.h"

/* This module's private header */
#include "private/ale_.h"

/* This module's header */
#include "ale.h"


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

static void LOCAL_setAleConfig(ALE_State *pAle, ALE_Config *pALEConfig);
static void LOCAL_updateAleMode(ALE_State *pAle);
static void LOCAL_setPortConfig(const ALE_PortConfig *pALEPortConfig, uint32_t portNum);

static uint32_t LOCAL_setReceiveFilter(ALE_State *pALE, uint32_t rxFilter);
static uint32_t LOCAL_getReceiveFilter(const ALE_State *pALE, uint32_t *pRxFilter);

static uint32_t LOCAL_setMulticast(ALE_State *pAle, uint32_t addrCount, const uint8_t *pMCastList);
static uint32_t LOCAL_clearMulticast(ALE_State *pAle, uint32_t addrCount, const uint8_t *pMCastList);

static uint32_t LOCAL_getFreeEntry(uint32_t *entry);
static void LOCAL_clearTableEntry(uint32_t entry);


static uint32_t LOCAL_findAddress(const uint8_t *addr, uint32_t vlanId, uint32_t *entry);
static uint32_t LOCAL_findVlan(uint32_t vlanId, uint32_t *vlanMemberList,
                               uint32_t *unregMcastFloodMask, uint32_t *regMcastFloodMask,
                               uint32_t *forceUntaggedEgress);

static uint32_t LOCAL_addUniAddr(uint32_t portNum, const uint8_t *addr, uint32_t vlanId,
                                 uint32_t blocked, uint32_t secure, uint32_t ageable);
static uint32_t LOCAL_addOuiAddr(const uint8_t *ouiAddress);
static uint32_t LOCAL_addMltAddr(const uint8_t *addr, uint32_t vlanId, uint32_t portMask,
                                    uint32_t super, uint32_t fwdState);
static uint32_t LOCAL_addVlan(uint32_t vlanId, uint32_t vlanMemberList,
                              uint32_t unregMcastFloodMask, uint32_t regMcastFloodMask,
                              uint32_t forceUntaggedEgress);

static uint32_t LOCAL_delVlan(uint32_t vlanId);
static uint32_t LOCAL_delAddress(const uint8_t *addr, uint32_t vlanId);

static uint32_t LOCAL_dumpTable(ALE_TableDumpPrintFxn pPrintFxn);



/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
static ALE_State ALE_stateObj;
#endif

/* Data to keep track of open references to the ALE */
static uint32_t     LOCAL_aleRefCount = 0;
static ALE_State    *LOCAL_aleRef     = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

ALE_Handle ALE_open(ALE_Config *pALEConfig, const uint8_t *macAddr)
{
    ALE_State *pAle = NULL;

    uint32_t  key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_aleRefCount++;

    if ((uint32_t)1U == LOCAL_aleRefCount)
    {

#if defined(NSP_DYNAMIC_ALLOCATION)
        pAle = (ALE_State *) calloc(1U, sizeof(ALE_State));
#else
        pAle = &ALE_stateObj;
#endif

        /* Zero init the MAC_State structure */
        memset(pAle, 0, sizeof(ALE_State));

        LOCAL_setAleConfig(pAle, pALEConfig);

        /* Add ALE entry for CPU port */
        LOCAL_addUniAddr((uint32_t)0U, macAddr, (uint32_t)0, (uint32_t)0, (uint32_t)1U, (uint32_t)0);

        /* Save a pointer to the state structure to be used to provide a reference for future open calls */
        LOCAL_aleRef = pAle;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, Stats was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
         pAle = LOCAL_aleRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return (ALE_Handle) pAle;
}

uint32_t ALE_close(ALE_Handle hAle)
{
    ALE_State * pAle = (ALE_State *) hAle;

    uint32_t retVal = ALE_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_aleRefCount--;

    if (0U == LOCAL_aleRefCount)
    {

        /* De-activate the ALE ageout timer here */
        pAle->aleTimerActive = 0;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pAle);
#else
        memset(pAle, 0, sizeof(ALE_State));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;

}

uint32_t ALE_ioctl(ALE_Handle hAle, uint32_t cmd, void *param, uint32_t size)
{
    ALE_State *pAle = (ALE_State *) hAle;
    uint32_t retVal = ALE_FAILURE;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_ALE_ADD_MULTICAST:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_ADD_UNICAST:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_ADD_OUI:
        {
            if ((size != (uint32_t)(sizeof(uint8_t) * 3U)) || (param == NULL))
            {

            }
            else
            {
                uint8_t *addr = (uint8_t *)param;
                retVal = LOCAL_addOuiAddr(addr);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_ADD_VLAN:
        {
            if ((size != sizeof(ALE_AddVlanIoctlCmd)) || (param == NULL))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                ALE_AddVlanIoctlCmd *pCmd = (ALE_AddVlanIoctlCmd *) param;

                retVal = LOCAL_addVlan(pCmd->vlanId, pCmd->vlanMemberList,
                            pCmd->unregMcastFloodMask, pCmd->regMcastFloodMask,
                            pCmd->forceUntaggedEgress);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_REMOVE_ADDR:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_REMOVE_VLAN:
        {
            if ((size != sizeof(uint32_t)) || (param == NULL))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                uint32_t vlanId = *((uint32_t *) param);

                retVal = LOCAL_delVlan(vlanId);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_TIMEOUT:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_DUMP_TABLE:
        {
            if ((size != sizeof(ALE_TableDumpPrintFxn)) || (param == NULL))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                ALE_TableDumpPrintFxn pPrintFxn = *((ALE_TableDumpPrintFxn *) param);

                retVal = LOCAL_dumpTable(pPrintFxn);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_LOOKUP_ADDR:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_LOOKUP_VLAN:
        {
            break;
        }
        case GMACSW_IOCTL_ALE_SET_RX_FILTER:
        {
            if (size != sizeof(uint32_t))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                uint32_t rxFilter = *((uint32_t *)param);

                retVal = LOCAL_setReceiveFilter(pAle, rxFilter);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_GET_RX_FILTER:
        {
            if (size != sizeof(uint32_t *))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                uint32_t *pRxFilter = *((uint32_t **)param);

                retVal = LOCAL_getReceiveFilter(pAle, pRxFilter);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_SET_MULTICAST:
        {
            if (size != sizeof(ALE_MulticastIoctlCmd))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                ALE_MulticastIoctlCmd *pCmd = (ALE_MulticastIoctlCmd *) param;

                retVal = LOCAL_setMulticast(pAle, pCmd->addrCount, pCmd->pMCastList);
            }
            break;
        }
        case GMACSW_IOCTL_ALE_CLEAR_MULTICAST:
        {
            if (size != sizeof(ALE_MulticastIoctlCmd))
            {
                retVal = ALE_MALFORMED_IOCTL;
            }
            else
            {
                ALE_MulticastIoctlCmd *pCmd = (ALE_MulticastIoctlCmd *) param;

                retVal = LOCAL_clearMulticast(pAle, pCmd->addrCount, pCmd->pMCastList);
            }
            break;
        }
        default:
        {
            retVal = ALE_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}

void ALE_ageOut(ALE_Handle hAle)
{
    ALE_State *pAle = (ALE_State *) hAle;

    if (((uint32_t)0U != pAle->aleTimerActive) && ((uint32_t)0U != pAle->aleTickTimeOutCount))
    {
        /* aleTickCount can become greater if timeout period is changed in between */
        pAle->aleTickCount++;
        if (pAle->aleTickCount >= pAle->aleTickTimeOutCount)
        {
            /* age out now */
#if defined(USE_CSLR)
            GMACSW_REGS->ALE.ALE_CONTROL |= CSL_GMACSW_ALE_CONTROL_AGE_OUT_NOW_MASK;
#else
            GMAC_SW_ALEAgeOut(SOC_GMAC_SW_ALE_BASE);
#endif
            pAle->aleTickCount = 0;
        }
    }
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_setAleConfig(ALE_State *pAle, ALE_Config *pALEConfig)
{
    uint32_t i = 0;

    /* Save some config info in the state structure*/
    pAle->aleTickTimeOutCount           = pALEConfig->aleTimeOutTicks;
    pAle->aleModeFlags                  = pALEConfig->defaultAleModeFlags;
    pAle->unknownVlanMemberList         = pALEConfig->unknownVlanMemberList;
    pAle->unknownMcastFloodMask         = pALEConfig->unknownMcastFloodMask;
    pAle->unknownRegMcastFloodMask      = pALEConfig->unknownRegMcastFloodMask;
    pAle->unknownForceUntaggedEgress    = pALEConfig->unknownForceUntaggedEgress;
    pAle->defaultPortVID                = pALEConfig->defaultPortVID;

    /* Activate the ALE ageout timer here */
    pAle->aleTimerActive = 1U;

    /* Reset the ALE tick count */
    pAle->aleTickCount = 0;

    /* Configure ALE Prescale register */
    GMACSW_REGS->ALE.ALE_PRESCALE = pALEConfig->alePrescale;

    /* Program the ALE Control register */
    LOCAL_updateAleMode(pAle);

    /* Configure ALE Port Control Register */
    for(i = 0; i < ALE_NUM_PORTS; i++)
    {
        LOCAL_setPortConfig(&(pALEConfig->alePortCfg[i]), i);
    }

    /* Add vlan entry into Ale for default PORT VID*/
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENVLANAWARE))
    {
        /* Modified Unreg_multicast_mask from 0x7U to 0x6 to exclude port 0 (host port) */
        LOCAL_addVlan(pAle->defaultPortVID, pAle->unknownVlanMemberList,
                    (uint32_t)6U, (uint32_t)7U, pAle->unknownForceUntaggedEgress);
    }
}

static void LOCAL_updateAleMode(ALE_State *pAle)
{
    uint32_t aleCtlVal = 0;

    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENABLE))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ENABLE_ALE, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_CLRTABLE))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_CLEAR_TABLE, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_AGEOUTNOW))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_AGE_OUT_NOW, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_LEARNNOVID))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_LEARN_NO_VID, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENVID0MODE))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_EN_VID0_MODE, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENOUIDENY))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ENABLE_OUI_DENY, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ALEBYPASS))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ALE_BYPASS, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_RATELIMITTX))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_RATE_LIMIT_TX, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENVLANAWARE))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ALE_VLAN_AWARE, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENAUTHMODE))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ENABLE_AUTH_MODE, 1U);
    }
    if (NOT_ZERO(pAle->aleModeFlags & ALE_CONFIG_ENRATELIMIT))
    {
        aleCtlVal |= CSL_FMK(GMACSW_ALE_CONTROL_ENABLE_RATE_LIMIT, 1U);
    }

    /* Update ALE control register */
    GMACSW_REGS->ALE.ALE_CONTROL = aleCtlVal;

    /* Clear out toggle bits */
    pAle->aleModeFlags &= (uint32_t)~(ALE_CONFIG_CLRTABLE | ALE_CONFIG_AGEOUTNOW);

    /* Configure Unknown VLAN items */
    GMACSW_REGS->ALE.ALE_UNKNOWN_VLAN =
        CSL_FMK(GMACSW_ALE_UNKNOWN_VLAN_UNKNOWN_FORCE_UNTAGGED_EGRESS, pAle->unknownForceUntaggedEgress)
        | CSL_FMK(GMACSW_ALE_UNKNOWN_VLAN_UNKNOWN_REG_MCAST_FLOOD_MASK, pAle->unknownRegMcastFloodMask)
        | CSL_FMK(GMACSW_ALE_UNKNOWN_VLAN_UNKNOWN_MCAST_FLOOD_MASK, pAle->unknownMcastFloodMask)
        | CSL_FMK(GMACSW_ALE_UNKNOWN_VLAN_UNKNOWN_VLAN_MEMBER_LIST, pAle->unknownVlanMemberList);
}

static void LOCAL_setPortConfig(const ALE_PortConfig *pALEPortConfig, uint32_t portNum)
{
    uint32_t  alePortControlVal = 0;

    alePortControlVal =
        CSL_FMK(GMACSW_ALE_PORTCTL_BCAST_LIMIT, pALEPortConfig->bcastLimit) |
        CSL_FMK(GMACSW_ALE_PORTCTL_MCAST_LIMIT, pALEPortConfig->mcastLimit) |
        CSL_FMK(GMACSW_ALE_PORTCTL_NO_LEARN, pALEPortConfig->noLearn) |
        CSL_FMK(GMACSW_ALE_PORTCTL_VID_INGRESS_CHECK, pALEPortConfig->vidIngressCheck) |
        CSL_FMK(GMACSW_ALE_PORTCTL_DROP_UNTAGGED, pALEPortConfig->dropUntagged) |
        CSL_FMK(GMACSW_ALE_PORTCTL_PORT_STATE, pALEPortConfig->portState);

    GMACSW_REGS->ALE.ALE_PORTCTL[portNum] = alePortControlVal;
}

/*
 *  Finds index to the next free entry in ALE table.
 */
static uint32_t LOCAL_getFreeEntry(uint32_t *entry)
{
    uint32_t i, ret = ALE_SUCCESS;

    for (i = 0; i < ALE_TABLE_DEPTH; i++)
    {
        uint32_t reg1;
        GMACSW_REGS->ALE.ALE_TBLCTL = i ;
        reg1 = GMACSW_REGS->ALE.ALE_TBLW1;

        if ((reg1 & 0x30000000U) == 0U)
        {
            break;
        }
    }

    if (ALE_TABLE_DEPTH == i)
    {
        ret = ALE_TABLE_FULL;
    }
    else
    {
        *entry = i;
    }

    return ret;
}

/*
 * This function clears the given entry from the ALE table.
 */
static void LOCAL_clearTableEntry(uint32_t entry)
{

    GMACSW_REGS->ALE.ALE_TBLW2 = 0;
    GMACSW_REGS->ALE.ALE_TBLW1 = 0;
    GMACSW_REGS->ALE.ALE_TBLW0 = 0;
    GMACSW_REGS->ALE.ALE_TBLCTL = entry | CSL_FMK(GMACSW_ALE_TBLCTL_WRITE_RDZ, 1U);

    return;
}

static uint32_t LOCAL_setReceiveFilter(ALE_State *pAle, uint32_t rxFilter)
{
    /* Validate the input */
    if (rxFilter > ALE_RXFILTER_ALL)
    {
        return ALE_INVALID_PARAM;
    }

    pAle->rxFilter = rxFilter;

    return ALE_SUCCESS;
}

static uint32_t LOCAL_getReceiveFilter(const ALE_State *pAle, uint32_t *pRxFilter)
{
    /* Validate our handle */
    if (IS_NULL(pRxFilter))
    {
        return ALE_INVALID_PARAM;
    }

    *pRxFilter = pAle->rxFilter;

    return ALE_SUCCESS;
}

static uint32_t LOCAL_setMulticast(ALE_State *pAle, uint32_t addrCount, const uint8_t *pMCastList)
{
    /* Validate our handle */
    if ((addrCount != 0) && IS_NULL(pMCastList))
    {
        return ALE_INVALID_PARAM;
    }

    if ( pAle->rxFilter < ALE_RXFILTER_ALL )
    {
        /* ENSURE ALE BYPASS IS TURNED OFF */
        if ((pAle->aleModeFlags & ALE_CONFIG_ALEBYPASS) != 0)
        {
            pAle->aleModeFlags &= (uint32_t)~ALE_CONFIG_ALEBYPASS;
            pAle->aleModeFlags |= ALE_CONFIG_CLRTABLE;
            LOCAL_updateAleMode(pAle);
        }
    }

    if ( pAle->rxFilter < ALE_RXFILTER_ALLMULTICAST )
    {
        /* Ensure that unreg_multicast_mask has CPU port(port 0) cleared */
        pAle->unknownMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U);

        pAle->aleModeFlags &= (uint32_t)~ALE_CONFIG_ALEBYPASS;
        pAle->aleModeFlags |= ALE_CONFIG_CLRTABLE;

        LOCAL_updateAleMode(pAle);

        /* Also Program VLAN entry settings for Default VID */
        LOCAL_addVlan( pAle->defaultPortVID, pAle->unknownVlanMemberList,
                (uint32_t)3U, (uint32_t)7U, pAle->unknownForceUntaggedEgress);
    }

    if ( pAle->rxFilter < ALE_RXFILTER_MULTICAST )
    {
        /* Ensure that reg/unreg_multicast_mask has CPU port(port 0) cleared */
        pAle->unknownMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U);

        pAle->unknownRegMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U);

        pAle->aleModeFlags &= (uint32_t)~ALE_CONFIG_ALEBYPASS;
        pAle->aleModeFlags |= ALE_CONFIG_CLRTABLE;

        LOCAL_updateAleMode(pAle);

        /* Also Program VLAN entry settings for Default VID */
        LOCAL_addVlan(pAle->defaultPortVID,pAle->unknownVlanMemberList,
                (uint32_t)3U, (uint32_t)3U, pAle->unknownForceUntaggedEgress);
    }

    if ( pAle->rxFilter < ALE_RXFILTER_BROADCAST )
    {
        /* Broadcast cannot be turned off */
    }

    if ( pAle->rxFilter < ALE_RXFILTER_DIRECT )
    {
        /* Remove the unicast address here*/
    }

    /*!
     * Enable Section
     */
    if ( pAle->rxFilter >= ALE_RXFILTER_DIRECT )
    {
       /* Add the unicast address here*/
    }

    if ( pAle->rxFilter >= ALE_RXFILTER_BROADCAST )
    {

    }

    if ( pAle->rxFilter == ALE_RXFILTER_MULTICAST )
    {
        uint32_t i;

        /* Ensure that reg_multicast_mask has CPU port(port 0) enabled */
        pAle->unknownMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U);
        pAle->unknownRegMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U) | (uint32_t)1U;
        LOCAL_updateAleMode(pAle);

        /* Also Program VLAN entry settings for Default VID */
        LOCAL_addVlan(pAle->defaultPortVID,pAle->unknownVlanMemberList,
                (uint32_t)3U, (uint32_t)7U, pAle->unknownForceUntaggedEgress);

        /* run through the list of multicast entries and add them to ALE */

        /* CHECK: Do we delete all existing multicast entries from ALE before
         * adding new entries from the list
         */
        for(i = 0; i < addrCount; i++)
        {
            /* adding with Portmask=0x7U so that pkt is forwarded to remaining 2 ports */
            LOCAL_addMltAddr(pMCastList + (i * (uint32_t)6U), pAle->defaultPortVID , (uint32_t)0x7U,
                    (uint32_t)0, (uint32_t)3U);
        }

    }

    if ( pAle->rxFilter == ALE_RXFILTER_ALLMULTICAST )
    {
        /* Ensure that reg/unreg_multicast_mask have CPU port enabled */
        pAle->unknownMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U) | (uint32_t)1U;
        pAle->unknownRegMcastFloodMask = ((uint32_t)1U << (uint32_t)2U) | ((uint32_t)1U << (uint32_t)1U) | (uint32_t)1U;
        LOCAL_updateAleMode(pAle);

        /* Also Program VLAN entry settings for Default VID */
        LOCAL_addVlan(pAle->defaultPortVID, pAle->unknownVlanMemberList,
                (uint32_t)7U, (uint32_t)7U, pAle->unknownForceUntaggedEgress);
    }

    if ( pAle->rxFilter == ALE_RXFILTER_ALL )
    {
        if ((uint32_t)0U == (pAle->aleModeFlags & ALE_CONFIG_ALEBYPASS))
        {
            pAle->aleModeFlags |= ALE_CONFIG_ALEBYPASS | ALE_CONFIG_CLRTABLE;
            LOCAL_updateAleMode(pAle);
        }
    }

    return 0U;
}

static uint32_t LOCAL_clearMulticast(ALE_State *pAle, uint32_t addrCount, const uint8_t *pMCastList)
{
    uint32_t        i = 0;

    /* Validate our handle */
    if ((addrCount != 0) && IS_NULL(pMCastList))
    {
        return ALE_INVALID_PARAM;
    }

    /* Remove multicast entries that was added from previous
     * setMulticast if there are any
     */
    if (addrCount != 0)
    {
        for(i = 0U; i < addrCount; i++)
        {
            LOCAL_delAddress(pMCastList + (i * 6U), pAle->defaultPortVID);
        }
    }

    return 0U;
}

static uint32_t LOCAL_findAddress(const uint8_t *addr, uint32_t vlanId, uint32_t *entry)
{
    uint32_t i;
    uint32_t info1, info0;
    uint32_t ret = ALE_ADDRESS_NOT_FOUND;

    /* figure out the expected values to match with */
    info1 = ((uint32_t)addr[0] << 8U) | (uint32_t)addr[1];
    info0 = ((uint32_t)addr[2] << 24U) | ((uint32_t)addr[3] << 16U) |
            ((uint32_t)addr[4] << 8U)  | (uint32_t)addr[5];

    for (i = 0; i < ALE_TABLE_DEPTH; i++)
    {
        uint32_t value;
        uint32_t masked_reg1;
        uint32_t reg0, reg1;

        /* read from the ALE table */
        GMACSW_REGS->ALE.ALE_TBLCTL = i;
        reg0 = GMACSW_REGS->ALE.ALE_TBLW0;
        reg1 = GMACSW_REGS->ALE.ALE_TBLW1;

        value = (reg1 >> 28U) & 3U;
        /* We only need to check the entry type and address fields */
        masked_reg1 = reg1 & 0x0000FFFFU;

        if ((value == 1U) || (value == 3U))
        {
            if ((masked_reg1 == info1) && (reg0 == info0))
            {
                uint32_t vid = (reg1 >> 16U) & 0x0FFFU;
                if ((vlanId >= 4096U) || (vid == vlanId))
                {
                    break;
                }
            }
        }
    }

    if (i != ALE_TABLE_DEPTH)
    {
        *entry = i;
        ret = ALE_SUCCESS;
    }

    return ret;
}

static uint32_t LOCAL_findVlan(uint32_t vlanId, uint32_t *vlanMemberList,
            uint32_t *unregMcastFloodMask, uint32_t *regMcastFloodMask,
            uint32_t *forceUntaggedEgress)
{
    uint32_t i;
    uint32_t ret = ALE_VLAN_NOT_FOUND;

    for (i = 0; i < ALE_TABLE_DEPTH; i++)
    {
        uint32_t vid;
        uint32_t value;
        uint32_t info0, info1;
        GMACSW_REGS->ALE.ALE_TBLCTL = i;
        info0 = GMACSW_REGS->ALE.ALE_TBLW0;
        info1 = GMACSW_REGS->ALE.ALE_TBLW1;
        value = (info1 >> 28U) & 3U;
        vid = (info1 >> 16U) & 0x0FFFU;
        if (value == 2U)
        {
            if (vid == vlanId)
            {
                if (i < ALE_TABLE_DEPTH)
                {
                    if (0U != vlanMemberList)
                    {
                        *vlanMemberList = info0 & 0x00000007U;
                    }
                    if (0U != unregMcastFloodMask)
                    {
                        *unregMcastFloodMask = (info0 & 0x00000700U) >> 8U;
                    }
                    if (0U != regMcastFloodMask)
                    {
                        *regMcastFloodMask   = (info0 & 0x00070000U) >> 16U;
                    }
                    if (0U != forceUntaggedEgress)
                    {
                        *forceUntaggedEgress = (info0 & 0x07000000U) >> 24U;
                    }

                    ret = i;
                    break;
                }
            }/* end of id VID == vlanId block */
        }
    }/* end of for i loop */

    return ret;
}

static uint32_t LOCAL_addUniAddr(uint32_t portNum, const uint8_t *addr, uint32_t vlanId,
                                    uint32_t blocked, uint32_t secure, uint32_t ageable)
{
    uint32_t freeEntry, vlanAware, info0, info1, info2, ret;
    uint32_t addrEntry = 0;

    /* Check the current setting for vlanAware */
    vlanAware = CSL_FEXT(GMACSW_REGS->SS.CPSW_CONTROL, GMACSW_CPSW_CONTROL_VLAN_AWARE);

    /* ignore input vlanId if not in VLAN aware mode */
    if (vlanAware == 0)
    {
        vlanId = 0;
    }
    /* Check for space in the ALE table */
    ret = LOCAL_findAddress(addr, vlanId, &addrEntry);
    if (ALE_ADDRESS_NOT_FOUND == ret)
    {
        ret = LOCAL_getFreeEntry(&freeEntry);
    }
    else
    {
        /* update the existing entry itself */
        freeEntry = (uint32_t) addrEntry;
    }

    if (ret != ALE_TABLE_FULL)
    {
        /* Add new entry to ALE table */
        info2 = (ageable << 2U) | (portNum & 3U);
        info1 = (blocked << 31U) | (secure << 30U) | ((uint32_t)1U << 28U) |
            ((vlanId & 0x0FFFU) << 16U) | ((uint32_t)addr[0] << 8U) | (uint32_t)addr[1];

        if (vlanId != 0)
        {
            info1 |= (uint32_t)1U << 29U;
        }

        info0 = ((uint32_t)addr[2] << 24U) | ((uint32_t)addr[3] << 16U) |
                ((uint32_t)addr[4] << 8U)  | (uint32_t)addr[5];

        GMACSW_REGS->ALE.ALE_TBLW2 = info2;
        GMACSW_REGS->ALE.ALE_TBLW1 = info1;
        GMACSW_REGS->ALE.ALE_TBLW0 = info0;
        GMACSW_REGS->ALE.ALE_TBLCTL = freeEntry | CSL_FMK(GMACSW_ALE_TBLCTL_WRITE_RDZ, 1U);
        ret = ALE_SUCCESS;
    }

    return ret;
}

static uint32_t LOCAL_addOuiAddr(const uint8_t *ouiAddress)
{
    uint32_t freeEntry, ret = ALE_SUCCESS;
    uint32_t addrEntry;

    /* Check for space in the ALE table */
    ret = LOCAL_findAddress(ouiAddress, (uint32_t)4096U, &addrEntry);
    if(ALE_ADDRESS_NOT_FOUND == ret)
    {
        ret = LOCAL_getFreeEntry(&freeEntry);
    }
    else
    {
        freeEntry = addrEntry;
    }

    if (ret != ALE_TABLE_FULL)
    {
        GMACSW_REGS->ALE.ALE_TBLW2 =
            0U;
        GMACSW_REGS->ALE.ALE_TBLW1 =
            ((uint32_t)9U << 28U) | ((uint32_t)ouiAddress[0] << 8U) | (uint32_t)ouiAddress[1];
        GMACSW_REGS->ALE.ALE_TBLW0 =
            (uint32_t)ouiAddress[2] << 24U;
        GMACSW_REGS->ALE.ALE_TBLCTL = freeEntry | CSL_FMK(GMACSW_ALE_TBLCTL_WRITE_RDZ, 1U);

        ret = ALE_SUCCESS;
    }

    return ret;
}

static uint32_t LOCAL_addMltAddr(const uint8_t *addr, uint32_t vlanId, uint32_t portMask,
                                    uint32_t super, uint32_t fwdState)
{
    uint32_t freeEntry, vlanAware, info0, info1, info2, ret = ALE_SUCCESS;
    uint32_t addrEntry = 0;

    /* Check the current setting for vlanAware */
    vlanAware = CSL_FEXT(GMACSW_REGS->SS.CPSW_CONTROL, GMACSW_CPSW_CONTROL_VLAN_AWARE);

    /* ignore input vlanId if not in VLAN aware mode */
    if (vlanAware == 0)
    {
        vlanId = 0;
    }

    /* Check for space in the ALE table */
    ret = LOCAL_findAddress(addr, vlanId, &addrEntry);
    if(ALE_ADDRESS_NOT_FOUND == ret)
    {
        ret = LOCAL_getFreeEntry(&freeEntry);
    }
    else
    {
        /* update the existing entry */
        freeEntry = addrEntry;
    }

    if (ret == ALE_TABLE_FULL)
    {
        ret = ALE_TABLE_FULL;
    }
    else
    {
        /* Add new entry to the ALE table */
        fwdState &= 3U;
        info2 = (super << 3U) | (portMask & 7U);
        if((uint32_t)0U != vlanId)
        {
            info1 = (fwdState << 30U) | (vlanAware << 29U) | ((uint32_t)1U << 28U) |
                    ((vlanId & 0x0FFFU) << 16U) | ((uint32_t)addr[0] << 8U) | (uint32_t)addr[1];
        }
        else
        {
            info1 = (fwdState << 30U) | ((uint32_t)1U << 28U) | ((uint32_t)(vlanId & 0x0FFFU) << 16U) |
                         ((uint32_t)addr[0] << 8U) | (uint32_t)addr[1];
        }
        info0 = ((uint32_t)addr[2] << 24U) | ((uint32_t)addr[3] << 16U) |
                ((uint32_t)addr[4] << 8U)  | (uint32_t)addr[5];
        GMACSW_REGS->ALE.ALE_TBLW2 = info2;
        GMACSW_REGS->ALE.ALE_TBLW1 = info1;
        GMACSW_REGS->ALE.ALE_TBLW0 = info0;
        GMACSW_REGS->ALE.ALE_TBLCTL = freeEntry | CSL_FMK(GMACSW_ALE_TBLCTL_WRITE_RDZ, 1U);

        ret = ALE_SUCCESS;
    }

    return ret;
}

static uint32_t LOCAL_addVlan(uint32_t vlanId, uint32_t vlanMemberList,
                              uint32_t unregMcastFloodMask, uint32_t regMcastFloodMask,
                              uint32_t forceUntaggedEgress)
{
    uint32_t vlanAware = 0, freeEntry = 0;
    uint32_t ret = ALE_SUCCESS;
    uint32_t vlanEntry = 0;

    /* Check the current setting for vlanAware */
    vlanAware = CSL_FEXT(GMACSW_REGS->SS.CPSW_CONTROL, GMACSW_CPSW_CONTROL_VLAN_AWARE);

    if (vlanAware == 0)
    {
        ret = ALE_VLAN_UNAWARE_MODE;
    }
    else
    {
        vlanId              &= (uint32_t) 0xFFFU;
        vlanMemberList      &= (uint32_t) 7U;
        unregMcastFloodMask &= (uint32_t) 7U;
        regMcastFloodMask   &= (uint32_t) 7U;
        forceUntaggedEgress &= (uint32_t) 7U;

        vlanEntry = LOCAL_findVlan(vlanId, (void *)0, (void *)0, (void *)0, (void *)0);
        if ((ALE_VLAN_NOT_FOUND != vlanEntry) && (vlanEntry < ALE_TABLE_DEPTH))
        {
            /* update existing entry */
            freeEntry = vlanEntry ;
        }
        else
        {
            /* Update VLAN Info */
            ret = LOCAL_getFreeEntry(&freeEntry);
        }

        if (ret != ALE_TABLE_FULL)
        {
            GMACSW_REGS->ALE.ALE_TBLW2 = 0;
            GMACSW_REGS->ALE.ALE_TBLW1 = ((uint32_t)2U << 28U) | (vlanId << 16U);
            GMACSW_REGS->ALE.ALE_TBLW0 = (forceUntaggedEgress << 24U)|
                                     (regMcastFloodMask << 16U) | (unregMcastFloodMask << 8U) |
                                     (vlanMemberList << 0);
            GMACSW_REGS->ALE.ALE_TBLCTL = freeEntry | CSL_FMK(GMACSW_ALE_TBLCTL_WRITE_RDZ, 0x1U);
            ret = ALE_SUCCESS;
        }
    }

    return ret;
}

static uint32_t LOCAL_delVlan(uint32_t vlanId)
{
    uint32_t delCount;
    uint32_t vlanMemberList, unregMcastFloodMask, regMcastFloodMask, forceUntaggedEgress;
    uint32_t ret = ALE_VLAN_NOT_FOUND;

    delCount = LOCAL_findVlan(vlanId,
                        &vlanMemberList,
                        &unregMcastFloodMask,
                        &regMcastFloodMask,
                        &forceUntaggedEgress);
    if((ALE_VLAN_NOT_FOUND != delCount) && (delCount < ALE_TABLE_DEPTH))
    {
        LOCAL_clearTableEntry(delCount);
        ret = ALE_SUCCESS;
    }

    return ret;
}

static uint32_t LOCAL_delAddress(const uint8_t *addr, uint32_t vlanId)
{
    uint32_t i;
    uint32_t info1, info0;
    uint32_t ret = ALE_ADDRESS_NOT_FOUND;

    /* figure out the expected values to match with */
    info1 = ((uint32_t)addr[0] << 8U)  | (uint32_t)addr[1];
    info0 = ((uint32_t)addr[2] << 24U) | ((uint32_t)addr[3] << 16U) |
            ((uint32_t)addr[4] << 8U)  | (uint32_t)addr[5];

    for (i = 0; i < ALE_TABLE_DEPTH; i++)
    {
        uint32_t value;
        uint32_t masked_reg1;
        uint32_t reg0, reg1;

        /* read from the ALE table */
        GMACSW_REGS->ALE.ALE_TBLCTL = i;
        reg0 = GMACSW_REGS->ALE.ALE_TBLW0;
        reg1 = GMACSW_REGS->ALE.ALE_TBLW1;

        value = (reg1 >> 28U) & 3U;
        /* We only need to check the entry type and address fields */
        masked_reg1 = reg1 & 0x0000FFFFU;

        if ((value == 1U) || (value == 3U))
        {
            if ((masked_reg1 == info1) && (reg0 == info0))
            {
                uint32_t vid = (reg1 >> 16U) & 0x0FFFU;
                if ((vlanId >= 4096U) || (vid == vlanId))
                {
                    LOCAL_clearTableEntry(i);
                    break;
                }
            }/* end of if address match block*/
       }
    }/* end of for i loop over ALE entries */

    if (i != ALE_TABLE_DEPTH)
    {
        ret = i;
    }

    return ret;
}

static uint32_t LOCAL_dumpTable(ALE_TableDumpPrintFxn pPrintFxn)
{
    uint32_t retVal = ALE_FAILURE;
    uint32_t i, freeEntries = 0;

    if (!IS_NULL(pPrintFxn))
    {
        (*pPrintFxn)("\n");

        for (i = 0; i < ALE_TABLE_DEPTH; i++)
        {
            uint32_t info0, info1, info2;

            GMACSW_REGS->ALE.ALE_TBLCTL = i;
            info0 = GMACSW_REGS->ALE.ALE_TBLW0;
            info1 = GMACSW_REGS->ALE.ALE_TBLW1;
            info2 = GMACSW_REGS->ALE.ALE_TBLW2;

            if ((info0 == 0xFFFFFFFEU) && ((info1 & 0x0FFFFU) == 0x0FFFFU))
            {
            }
            else
            {
                switch ((info1 >> 28U) & 3U)
                {
                    case 0U:
                    {
                        freeEntries++;
                        break;
                    }
                case 1U: /*MacAddress*/
                {
                    if ((uint32_t)0U != (info1 & ((uint32_t)1U << 8U)))
                    {
                            (*pPrintFxn)("  %4d: Multicast Address: %02x%02x%02x%02x%02x%02x, [Super]: %01x Multi_frd_state=%2d Port Mask =%d",
                                            i,
                                            (info1 >> 8U) & 0xFFU, info1 & 0xFFU, (info0 >> 24U) & 0xFFU,
                                            (info0 >> 16U) & 0xFFU, (info0 >> 8U) & 0xFFU, info0 & 0xFFU,
                                            info2 & 2U, (info1 >> 30U) & 3U, (info2 >> 2U) & 3U);
                    }
                    else
                    {
                            (*pPrintFxn)("  %4d: Unicast Address: %02x%02x%02x%02x%02x%02x, [Block:Secure]: %03x Ageable=%x Touch=%d Port=%d",
                                            i,
                                            (info1 >> 8U) & 0xFFU, info1 & 0xFFU, (info0 >> 24U) & 0xFFU,
                                            (info0 >> 16U) & 0xFFU, (info0 >> 8U) & 0xFFU, info0 & 0xFFU,
                                            info2 & 3U, (info1 >> 30U) & 1U, (info1 >> 31U) & 1U, (info2 >> 2U) & 3U);
                    }
                    break;
                }
                case 2U: /*VLAN*/
                {
                    (*pPrintFxn)("  %4d: Vlanid: %04d, UTagged: %x, Reg Mult flood mask : %x, UReg Mult flood mask: %x, Member: %x",
                                        i,
                                        (info1 >> 16U) & 0x0FFFU,
                                        (info0 >> 24U) & 7U, (info0 >> 16U) & 7U, (info0 >> 8U) & 7U, (info0 >> 0) & 7U);
                    break;
                }
                case 3U: /*VLAN-MacAddress*/
                {
                    if ((uint32_t)0U != (info1 & ((uint32_t)1U << 8U)))
                    {
                            (*pPrintFxn)("  %4d: VLAN Multicast Address: %02x%02x%02x%02x%02x%02x, VlanId: %04d, [Super]: %01x Multi_frd_state=%2d Port Mask =%d",
                                            i,
                                            (info1 >> 8U) & 0xFFU, info1 & 0xFFU, (info0 >> 24U) & 0xFFU,
                                            (info0 >> 16U) & 0xFFU, (info0 >> 8U) & 0xFFU, info0 & 0xFFU,
                                            (info1 >> 16U) & 0x0FFFU, info2 & 2U, (info1 >> 30U) & 3U, (info2 >> 2U) & 3U);
                    }
                    else
                    {
                            (*pPrintFxn)("  %4d: VLAN Unicast Address: %02x%02x%02x%02x%02x%02x, VlanId: %04d, [Block:Secure]: %03x Ageable=%x Touch=%d Port=%d",
                                            i,
                                            (info1 >> 8U) & 0xFFU, info1 & 0xFFU, (info0 >> 24U) & 0xFFU,
                                            (info0 >> 16U) & 0xFFU, (info0 >> 8U) & 0xFFU, info0 & 0xFFU,
                                            (info1 >> 16U) & 0x0FFFU, info2 & 3U, (info1 >> 30U) & 1U, (info1 >> 31U) & 1U, (info2 >> 2U) & 3U);
                    }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }/* end of switch construct */

                /*Raw Dump,followed by parsed output*/
                if ((uint32_t)0U != ((info1 >> 28U) & 3U))
                {
                    /* print Info for entried that are not free */
                    (*pPrintFxn)(" RAW:[%01x %02x%02x%02x", info2 & 0xFU,
                                        (info1 >> 24U) & 0xFFU, (info1 >> 16U) & 0xFFU, (info1 >> 8U) & 0xFFU);
                    (*pPrintFxn)("%02x %02x%02x%02x%02x] \n", info1 & 0xFU,
                                        (info0 >> 24U) & 0xFFU, (info0 >> 16U) & 0xFFU,
                                        (info0 >> 8U)  & 0xFFU, info0 & 0xFFU);
                }
            }/* end of else conditional block */
        }/* end of for loop over ALE entries */

        (*pPrintFxn)("\n\r");
        (*pPrintFxn)("%d Free Entries \r\n",freeEntries);

        retVal = ALE_SUCCESS;
    }

    return retVal;
}



/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

