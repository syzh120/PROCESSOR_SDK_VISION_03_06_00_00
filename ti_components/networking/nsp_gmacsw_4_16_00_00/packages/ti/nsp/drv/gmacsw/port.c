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
 *   \file  port.c
 *
 *   \brief
 *          PORT module implementation
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
#include "gmacsw_al.h"
#include "private/cpdma_.h"

/* This module's private header */
#include "private/port_.h"

/* This module's header */
#include "port.h"


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

static uint32_t LOCAL_addRxPriorityMapping(PORT_Handle hPort, const PORT_RxPriorityConfig *pPriConfig, PORT_RxPriorityMapHandle *pRxPriorityMapHandle);
static uint32_t LOCAL_removeRxPriorityMapping(PORT_Handle hPort, PORT_RxPriorityMapHandle hMap);
static uint32_t LOCAL_addTxPriorityMapping(PORT_Handle hPort, const PORT_TxPriorityConfig *pPriConfig, PORT_TxPriorityMapHandle *pTxPriorityMapHandle);
static uint32_t LOCAL_removeTxPriorityMapping(PORT_Handle hPort, PORT_TxPriorityMapHandle hMap);

static uint32_t LOCAL_isBitSet(uint32_t bitNum, uint32_t bitVector);
static uint32_t LOCAL_getPacketPriorityNum(const PORT_RxPriorityConfig *pPriConfig);
static int32_t  LOCAL_getSwitchPriorityNum(PORT_SwitchPriority switchPriority, PORT_SwitchPriority switchPriorityMap[]);
static void     LOCAL_updateRxPriorityMapping(const PORT_State *pPORTState);
static void     LOCAL_updateTxPriorityMapping(const PORT_State *pPORTState);
static uint32_t LOCAL_updateRxPortSettingsForUntagged(PORT_State *pPORTState, const PORT_RxPriorityConfig *pPriConfig);
#if !defined(DEVICE_CENTAURUS)
static uint32_t LOCAL_updateRxPortSettingsForDSCP(PORT_State *pPORTState, const PORT_RxPriorityConfig *pPriConfig);
#endif


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
PORT_State PORT_stateObj;
#endif

/* Data to keep track of open references to the PORT state */
static uint32_t     LOCAL_portRefCount  = 0;
static PORT_State   *LOCAL_portRef      = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

PORT_Handle PORT_open(void)
{
    PORT_State *pPORTState;
    uint32_t i;
    uint32_t j;

    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_portRefCount++;

    if ((uint32_t)1U == LOCAL_portRefCount)
    {

#if defined(NSP_DYNAMIC_ALLOCATION)
        pPORTState = (PORT_State *) calloc(1U, sizeof(PORT_State));
#else
        pPORTState = &PORT_stateObj;
#endif

        /* Zero init the PORT_State structure */
        memset(pPORTState, 0, sizeof(PORT_State));

        for (i = 0; i < MAC_NUM_PORTS; i++)
        {
            uint32_t regValue;

            for (j = 0; j < PORT_PACKET_PRIORITY_COUNT; j++)
            {
                pPORTState->rxPacketToSwitchPriorityMap[i][j] = PORT_SWITCH_PRIORITY_UNUSED;
                pPORTState->txPacketToSwitchPriorityMap[i][j] = PORT_SWITCH_PRIORITY_UNUSED;
            }

            for (j = 0; j < PORT_SWITCH_PRIORITY_COUNT; j++)
            {
                pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][j] = PORT_CPDMA_CHANNEL_UNUSED;
            }

            pPORTState->rxUntaggedMappingActive[i] = 0U;
            pPORTState->rxDiffservMappingCount[i] = 0U;

            /* Map packet priority to best effort header packet priority */
            regValue = 0;
            for (j=0; j<PORT_PACKET_PRIORITY_COUNT; j++)
            {
                regValue = (regValue << (j*4U)) | (i*PORT_SWITCH_PRIORITY_COUNT);
            }
            GMACSW_REGS->SL.MAC[i].SL_RX_PRI_MAP = regValue;
        }

        /*
         * Map the Rx switch priorities to highest CPDMA channel which will be
         * the last used. This should ensure that no stray packets go to the
         * wrong CPDMA channel as they are allocated.
         */
        GMACSW_REGS->PORT.CPDMA_PORT.P0_CPDMA_RX_CH_MAP = (uint32_t) 0x77777777U;

        /*
         * Map the Rx packet priorities to lowest switch priority number (0)
         * which will be the last used. This should help ensure that no stray packets
         * go to the wrong switch priority as they are allocated.
         */
        GMACSW_REGS->PORT.CPDMA_PORT.P0_TX_PRI_MAP      = (uint32_t) 0x00000000U;

        /* Save a pointer to the state structure to be used to provide a reference for future open calls */
        LOCAL_portRef = pPORTState;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, CPDMA was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
        pPORTState = LOCAL_portRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return (PORT_Handle) pPORTState;
}

uint32_t PORT_close(PORT_Handle hPort)
{
    PORT_State *pPORTState = (PORT_State *) hPort;
    uint32_t retVal = PORT_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_portRefCount--;

    if (0U == LOCAL_portRefCount)
    {
        /* Reset the local reference holder */
        LOCAL_portRef = NULL;

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pPORTState);
#else
        memset(pPORTState, 0 , sizeof(PORT_State));
#endif
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

uint32_t PORT_ioctl(PORT_Handle hPort, uint32_t cmd, void *param, uint32_t size)
{
    uint32_t retVal = PORT_FAILURE;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING:
        {
            if ((sizeof(PORT_AddRxPriorityMappingIoctlCmd) != size) || (NULL == param))
            {
                retVal = PORT_MALFORMED_IOCTL;
            }
            else
            {
                PORT_AddRxPriorityMappingIoctlCmd *priCmd = (PORT_AddRxPriorityMappingIoctlCmd *) param;

                retVal = LOCAL_addRxPriorityMapping(hPort, priCmd->pPriConfig, priCmd->pRxPriorityMapHandle);
            }
            break;
        }
        case GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING:
        {
            if ((sizeof(PORT_RxPriorityMapHandle) != size) || (NULL == param))
            {
                retVal = PORT_MALFORMED_IOCTL;
            }
            else
            {
                PORT_RxPriorityMapHandle hRxPriorityMap = *((PORT_RxPriorityMapHandle *) param);

                retVal = LOCAL_removeRxPriorityMapping(hPort,hRxPriorityMap);
            }
            break;
        }
        case GMACSW_IOCTL_PORT_ADD_TX_PRIORITY_MAPPING:
        {
            if ((sizeof(PORT_AddTxPriorityMappingIoctlCmd) != size) || (NULL == param))
            {
                retVal = PORT_MALFORMED_IOCTL;
            }
            else
            {
                PORT_AddTxPriorityMappingIoctlCmd *priCmd = (PORT_AddTxPriorityMappingIoctlCmd *) param;

                retVal = LOCAL_addTxPriorityMapping(hPort, priCmd->pPriConfig, priCmd->pTxPriorityMapHandle);
            }
            break;
        }
        case GMACSW_IOCTL_PORT_REMOVE_TX_PRIORITY_MAPPING:
        {
            if ((sizeof(PORT_TxPriorityMapHandle) != size) || (NULL == param))
            {
                retVal = PORT_MALFORMED_IOCTL;
            }
            else
            {
                PORT_TxPriorityMapHandle hTxPriorityMap = *((PORT_TxPriorityMapHandle *) param);

                retVal = LOCAL_removeTxPriorityMapping(hPort, hTxPriorityMap);
            }
            break;
        }
        case GMACSW_IOCTL_PORT_ADD_TX_RATE_LIMIT_MAP:
        {
            break;
        }
        case GMACSW_IOCTL_PORT_REMOVE_TX_RATE_LIMIT_MAP:
        {
            break;
        }
        default:
        {
            retVal = PORT_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* LOCAL IOCTL implementations */
static uint32_t LOCAL_addRxPriorityMapping(PORT_Handle hPort, const PORT_RxPriorityConfig *pPriConfig, PORT_RxPriorityMapHandle *pRxPriorityMapHandle)
{
    PORT_State *pPORTState = (PORT_State *) hPort;
    uint32_t retVal = PORT_SUCCESS;

    if ((NULL != pPORTState) &&
        (NULL != pPriConfig) &&
        (NULL != pRxPriorityMapHandle))
    {
        uint32_t mapNum = 0;

        /* Find the first open mapping */
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            while ( (LOCAL_isBitSet(mapNum, pPORTState->rxPriorityMapBitVector) != 0U) &&
                    (mapNum < PORT_MAX_RX_PRIORITY_MAP))
            {
                mapNum++;
            }

            if (PORT_MAX_RX_PRIORITY_MAP <= mapNum)
            {
                retVal = PORT_NO_RX_PRIORITY_MAPPINGS_AVAILABLE;
            }
            else
            {
                pPORTState->rxPriorityMapBitVector |= ((uint32_t)0x1U << mapNum);
            }
            GMACSW_AL_globalInterruptEnable(key);
        }

        /* If an open mapping was available, process the priority mapping */
        if (retVal == PORT_SUCCESS)
        {
            PORT_RxPriorityMap *pMap = &pPORTState->rxPriorityMap[mapNum];
            uint32_t i;

            /* Save mapping number */
            pMap->mapNumber = mapNum;

            /* Init with numbers that will result in no activity */
            uint32_t startPortNum;
            uint32_t stopPortNum;

            if (PORT_RX_SOURCE_MAC_1 == pPriConfig->rxSource)
            {
                startPortNum = 0U;   stopPortNum = 0U;
            }
            else if (PORT_RX_SOURCE_MAC_2 == pPriConfig->rxSource)
            {
                startPortNum = 1U;   stopPortNum = 1U;
            }
            else if (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource)
            {
                startPortNum = 0U;   stopPortNum = 1U;
            }
            else
            {
                /* Init with numbers that will result in no looping */
                startPortNum = 1U;   stopPortNum = 0U;
            }

            /* Update the state structure */
            for (i = startPortNum; i <= stopPortNum; i++)
            {
                uint32_t packetPriorityNum = 0U;
                uint32_t cpdmaChannelNum = 0U;
                
                packetPriorityNum = LOCAL_getPacketPriorityNum(pPriConfig);
                cpdmaChannelNum = ((CPDMA_Channel *) pPriConfig->hCpdmaRxChannel)->channelNum;

                /* Step 1 - Check to make sure packet priority to switch priority mapping does not exist */
                if ((packetPriorityNum < PORT_PACKET_PRIORITY_COUNT) && (pPORTState->rxPacketToSwitchPriorityMap[i][packetPriorityNum] != PORT_SWITCH_PRIORITY_UNUSED))
                {
                    retVal = PORT_PRIORITY_ALREADY_MAPPED;
                    break;
                }

                /* Step 2 - Add the packet to switch priority mapping */
                if(packetPriorityNum < PORT_PACKET_PRIORITY_COUNT)
                {
                    pPORTState->rxPacketToSwitchPriorityMap[i][packetPriorityNum] = pPriConfig->switchPriority;
                }

                /* Step 3 - Add the switch priority to CPDMA channel mapping */
                if ( pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][(int32_t) pPriConfig->switchPriority] ==
                     PORT_CPDMA_CHANNEL_UNUSED )
                {
                    pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][(int32_t) pPriConfig->switchPriority] =
                        cpdmaChannelNum;
                }

                /*
                 * Step 4- Check to make sure the switch priority to cpdma map is correct. It was either
                 * added above or it existed from a previous mapping.
                 */
                if (pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][(int32_t) pPriConfig->switchPriority] !=
                     cpdmaChannelNum)
                {
                    retVal = PORT_PRIORITY_ALREADY_MAPPED;
                }
            }

            /* Save the config info in the Rx priority map structure */
            memcpy(&pMap->config, pPriConfig, sizeof(PORT_RxPriorityConfig));

            if (PORT_SUCCESS == retVal)
            {
                /* Update the PORT hardware registers with the current state */
                LOCAL_updateRxPriorityMapping(pPORTState);

                if (PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED == pPriConfig->rxPriorityType)
                {
                    LOCAL_updateRxPortSettingsForUntagged(pPORTState, pPriConfig);
                }
#if !defined(DEVICE_CENTAURUS)
                if (PORT_RX_PRIORITY_TYPE_IPV4_DIFFSERV == pPriConfig->rxPriorityType)
                {
                    LOCAL_updateRxPortSettingsForDSCP(pPORTState, pPriConfig);
                }
#endif
                /* Give the pointer to the Rx priority map structure as a return */
                *pRxPriorityMapHandle = (PORT_RxPriorityMapHandle) pMap;
            }
            else
            {
                /* There was an issue with the supplied config, so remove it */
                LOCAL_removeRxPriorityMapping(hPort, pMap);
            }
        }
    }
    else
    {
        retVal = PORT_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_removeRxPriorityMapping(PORT_Handle hPort, PORT_RxPriorityMapHandle hMap)
{
    PORT_State          *pPORTState = (PORT_State *) hPort;
    PORT_RxPriorityMap  *pMap       = (PORT_RxPriorityMap *) hMap;
    uint32_t retVal                 = PORT_SUCCESS;

    uint32_t i;
    uint32_t j;

    if ((NULL != pPORTState) &&
        (NULL != pMap))
    {
        uint32_t mapNum = pMap->mapNumber;

        if ( (LOCAL_isBitSet(mapNum, pPORTState->rxPriorityMapBitVector) != 0U) &&
                    (mapNum < PORT_MAX_RX_PRIORITY_MAP))
        {
            PORT_RxPriorityConfig *pPriConfig = &pMap->config;

            uint32_t startPortNum;
            uint32_t stopPortNum;

            if (PORT_RX_SOURCE_MAC_1 == pPriConfig->rxSource)
            {
                startPortNum = 0U;   stopPortNum = 0U;
            }
            else if (PORT_RX_SOURCE_MAC_2 == pPriConfig->rxSource)
            {
                startPortNum = 1U;   stopPortNum = 1U;
            }
            else if (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource)
            {
                startPortNum = 0U;   stopPortNum = 1U;
            }
            else
            {
                /* Dummy init with numbers that will result in no looping */
                startPortNum = 1U;   stopPortNum = 0U;
            }

            /* Update the state structure */
            for (i = startPortNum; i <= stopPortNum; i++)
            {
                uint32_t packetPriorityNum = 0U;
                uint32_t cpdmaChannelNum = 0U;
                uint32_t switchPriorityInUseCount = 0U;
                
                packetPriorityNum = LOCAL_getPacketPriorityNum(pPriConfig);
                cpdmaChannelNum = ((CPDMA_Channel *) pPriConfig->hCpdmaRxChannel)->channelNum;

                /* Step 1 - Check to make sure the correct mapping exists in the PORT state */
                if(packetPriorityNum < PORT_PACKET_PRIORITY_COUNT)
                {
                    if( (pPORTState->rxPacketToSwitchPriorityMap[i][packetPriorityNum] != pPriConfig->switchPriority) ||
                        (pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][(int32_t) pPriConfig->switchPriority] != cpdmaChannelNum))
                    {
                        retVal = PORT_RX_PRIORITY_MAPPING_INVALID;
                        break;
                    }
                }

                /* Step 2 - Always remove the Packet to Switch Mapping */
                if(packetPriorityNum < PORT_PACKET_PRIORITY_COUNT)
                {
                    pPORTState->rxPacketToSwitchPriorityMap[i][packetPriorityNum] = PORT_SWITCH_PRIORITY_UNUSED;
                }

                /*
                 * Step 3 - Remove the switch to CPDMA channel map if this switch priority
                 * is not being used by this port anymore.
                 */
                for (j = 0; j<PORT_PACKET_PRIORITY_COUNT; j++)
                {
                    if (pPORTState->rxPacketToSwitchPriorityMap[i][j] == pPriConfig->switchPriority)
                    {
                        switchPriorityInUseCount++;
                    }
                }
                if (switchPriorityInUseCount == 0)
                {
                    /* Remove the switch priority to CPDMA channel mapping */
                    pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][(int32_t) pPriConfig->switchPriority] =
                        PORT_CPDMA_CHANNEL_UNUSED;
                }
            }

            /* Step 4 - Update the PORT module registers as needed */
            if (PORT_SUCCESS == retVal)
            {
                /* Update the PORT hardware registers with the current state */
                LOCAL_updateRxPriorityMapping(pPORTState);

                if (PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED == pPriConfig->rxPriorityType)
                {
                    LOCAL_updateRxPortSettingsForUntagged(pPORTState, pPriConfig);
                }
#if !defined(DEVICE_CENTAURUS)
                if (PORT_RX_PRIORITY_TYPE_IPV4_DIFFSERV == pPriConfig->rxPriorityType)
                {
                    LOCAL_updateRxPortSettingsForDSCP(pPORTState, pPriConfig);
                }
#endif
            }
        }
        else
        {
            retVal = PORT_RX_PRIORITY_MAPPING_INVALID;
        }

        if (PORT_SUCCESS == retVal)
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            /* Clear map bit for this map number */
            pPORTState->rxPriorityMapBitVector &= ~((uint32_t)0x1U << mapNum);

            GMACSW_AL_globalInterruptEnable(key);
        }
    }
    else
    {
        retVal = PORT_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_addTxPriorityMapping(PORT_Handle hPort,
                                           const PORT_TxPriorityConfig *pPriConfig,
                                           PORT_TxPriorityMapHandle *pTxPriorityMapHandle)
{
    PORT_State *pPORTState = (PORT_State *) hPort;
    uint32_t retVal = PORT_SUCCESS;

    if ((NULL != pPORTState) &&
        (NULL != pPriConfig) &&
        (NULL != pTxPriorityMapHandle))
    {
        uint32_t mapNum = 0;

        /* Find the first open mapping */
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            while ( (LOCAL_isBitSet(mapNum, pPORTState->txPriorityMapBitVector) != 0U) &&
                    (mapNum < PORT_MAX_TX_PRIORITY_MAP))
            {
                mapNum++;
            }

            if (PORT_MAX_TX_PRIORITY_MAP <= mapNum)
            {
                retVal = PORT_NO_TX_PRIORITY_MAPPINGS_AVAILABLE;
            }
            else
            {
                pPORTState->txPriorityMapBitVector |= ((uint32_t)0x1U << mapNum);
            }
            GMACSW_AL_globalInterruptEnable(key);
        }

        /* If an open mapping was available, process the priority mapping */
        if (retVal == PORT_SUCCESS)
        {
            PORT_TxPriorityMap *pMap = &pPORTState->txPriorityMap[mapNum];
            uint32_t i;

            /* Save mapping number */
            pMap->mapNumber = mapNum;

            /* Init with numbers that will result in no activity */
            uint32_t startPortNum;
            uint32_t stopPortNum;

            if (PORT_TX_DEST_MAC_1 == pPriConfig->txDest)
            {
                startPortNum = 0U;   stopPortNum = 0U;
            }
            else if (PORT_TX_DEST_MAC_2 == pPriConfig->txDest)
            {
                startPortNum = 1U;   stopPortNum = 1U;
            }
            else if (PORT_TX_DEST_MAC_BOTH == pPriConfig->txDest)
            {
                startPortNum = 0U;   stopPortNum = 1U;
            }
            else
            {
                /* Init with numbers that will result in no looping */
                startPortNum = 1U;   stopPortNum = 0U;
            }

            /* Update the state structure */
            for (i = startPortNum; i <= stopPortNum; i++)
            {
                uint32_t packetPriorityNum = pPriConfig->priority;

                /* Step 1 - Check to make sure packet priority to switch priority mapping does not exist */
                if (pPORTState->txPacketToSwitchPriorityMap[i][packetPriorityNum] != PORT_SWITCH_PRIORITY_UNUSED)
                {
                    retVal = PORT_PRIORITY_ALREADY_MAPPED;
                    break;
                }

                /* Step 2 - Add the packet to switch priority mapping */
                pPORTState->txPacketToSwitchPriorityMap[i][packetPriorityNum] = pPriConfig->switchPriority;
            }

            /* Save the config info in the Tx priority map structure */
            memcpy(&pMap->config, pPriConfig, sizeof(PORT_TxPriorityConfig));

            if (PORT_SUCCESS == retVal)
            {
                /* Update the PORT hardware registers with the current state */
                LOCAL_updateTxPriorityMapping(pPORTState);

                /* Give the pointer to the Tx priority map structure as a return */
                *pTxPriorityMapHandle = (PORT_TxPriorityMapHandle) pMap;
            }
            else
            {
                /* There was an issue with the supplied config, so remove it */
                LOCAL_removeTxPriorityMapping(hPort, pMap);
            }
        }
    }
    else
    {
        retVal = PORT_INVALID_PARAM;
    }

    return retVal;
}

static uint32_t LOCAL_removeTxPriorityMapping(PORT_Handle hPort, PORT_TxPriorityMapHandle hMap)
{
    PORT_State          *pPORTState = (PORT_State *) hPort;
    PORT_TxPriorityMap  *pMap       = (PORT_TxPriorityMap *) hMap;
    uint32_t retVal                 = PORT_SUCCESS;
    uint32_t i;

    if ((NULL != pPORTState) &&
        (NULL != pMap))
    {
        uint32_t mapNum = pMap->mapNumber;

        if ( (LOCAL_isBitSet(mapNum, pPORTState->txPriorityMapBitVector) != 0U) &&
                    (mapNum < PORT_MAX_TX_PRIORITY_MAP))
        {
            PORT_TxPriorityConfig *pPriConfig = &pMap->config;

            uint32_t startPortNum;
            uint32_t stopPortNum;

            if (PORT_TX_DEST_MAC_1 == pPriConfig->txDest)
            {
                startPortNum = 0U;   stopPortNum = 0U;
            }
            else if (PORT_TX_DEST_MAC_2 == pPriConfig->txDest)
            {
                startPortNum = 1U;   stopPortNum = 1U;
            }
            else if (PORT_TX_DEST_MAC_BOTH == pPriConfig->txDest)
            {
                startPortNum = 0U;   stopPortNum = 1U;
            }
            else
            {
                /* Dummy init with numbers that will result in no looping */
                startPortNum = 1U;   stopPortNum = 0U;
            }

            /* Update the state structure */
            for (i = startPortNum; i <= stopPortNum; i++)
            {
                uint32_t packetPriorityNum = pPriConfig->priority;

                /* Step 1 - Check to make sure the correct mapping exists in the PORT state */
                if (pPORTState->txPacketToSwitchPriorityMap[i][packetPriorityNum] != pPriConfig->switchPriority)
                {
                    retVal = PORT_TX_PRIORITY_MAPPING_INVALID;
                    break;
                }

                /* Step 2 - Always remove the Packet to Switch Mapping */
                pPORTState->txPacketToSwitchPriorityMap[i][packetPriorityNum] = PORT_SWITCH_PRIORITY_UNUSED;
            }

            /* Step 3 - Update the PORT module registers as needed */
            if (PORT_SUCCESS == retVal)
            {
                /* Update the PORT hardware registers with the current state */
                LOCAL_updateTxPriorityMapping(pPORTState);
            }
        }
        else
        {
            retVal = PORT_TX_PRIORITY_MAPPING_INVALID;
        }

        if (PORT_SUCCESS == retVal)
        {
            uint32_t key = GMACSW_AL_globalInterruptDisable();

            /* Clear map bit for this map number */
            pPORTState->txPriorityMapBitVector &= ~((uint32_t)0x1U << mapNum);

            GMACSW_AL_globalInterruptEnable(key);
        }
    }
    else
    {
        retVal = PORT_INVALID_PARAM;
    }

    return retVal;
}


/* LOCAL helper functions */
static uint32_t LOCAL_isBitSet(uint32_t bitNum, uint32_t bitVector)
{
    return (uint32_t)(((((uint32_t)1U << bitNum) & bitVector) == 0) ? 0U : 1U);
}

static uint32_t LOCAL_getPacketPriorityNum(const PORT_RxPriorityConfig *pPriConfig)
{
    uint32_t packetPriorityNum = 0xFFFFFFFFU;

    switch (pPriConfig->rxPriorityType)
    {
        case PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED:
        {
            /* Mask the priority to an allowed value */
            packetPriorityNum = pPriConfig->rxPriorityOption.untagged.priority & (uint32_t)0x7U;
            break;
        }

#if !defined(DEVICE_CENTAURUS)
        case PORT_RX_PRIORITY_TYPE_IPV4_DIFFSERV:
        {
            /* Mask the priority to an allowed value */
            packetPriorityNum = pPriConfig->rxPriorityOption.diffserv.priority & (uint32_t)0x7U;
            break;
        }
#endif

        case PORT_RX_PRIORITY_TYPE_PRI_TAGGED:
        {
            packetPriorityNum = pPriConfig->rxPriorityOption.priTagged.priority & (uint32_t)0x7U;
            break;
        }

        case PORT_RX_PRIORITY_TYPE_VLAN_TAGGED:
        {
            packetPriorityNum = pPriConfig->rxPriorityOption.vlanTagged.priority & (uint32_t)0x7U;
            break;
        }

        default:
        {
            break;
        }
    }

    return packetPriorityNum;
}

static void LOCAL_updateRxPriorityMapping(const PORT_State *pPORTState)
{
    PORT_SwitchPriority switchNum2PriorityMap[MAC_NUM_PORTS][PORT_SWITCH_PRIORITY_COUNT];
    uint32_t regValue;
    uint32_t i;
    uint32_t j;
    int32_t  k;
    int32_t  l;

    /*
     * Create the switch priority to switch number mapping based on what
     *  priorities are active for both ports
     */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        for (j = 0; j < PORT_SWITCH_PRIORITY_COUNT; j++)
        {
            switchNum2PriorityMap[i][j] = PORT_SWITCH_PRIORITY_UNUSED;
        }
        for (j = 0; j < PORT_PACKET_PRIORITY_COUNT; j++)
        {
            if (pPORTState->rxPacketToSwitchPriorityMap[i][j] != PORT_SWITCH_PRIORITY_UNUSED)
            {
                for (k = (int32_t)((int32_t)PORT_SWITCH_PRIORITY_COUNT - 1); k >= 0; k--)
                {
                    if (pPORTState->rxPacketToSwitchPriorityMap[i][j] > switchNum2PriorityMap[i][k])
                    {
                        for (l = 1; l <= k; l++)
                        {
                            switchNum2PriorityMap[i][l-1] = switchNum2PriorityMap[i][l];
                        }
                        switchNum2PriorityMap[i][k] = pPORTState->rxPacketToSwitchPriorityMap[i][j];
                    }
                    if (pPORTState->rxPacketToSwitchPriorityMap[i][j] == switchNum2PriorityMap[i][k])
                    {
                        /* This mapping is accounted for */
                        break;
                    }
                }
            }
        }
    }

    /*
     * Set the MAC packet priority to header packet priority registers
     * MAC Port 1 gets priorites 0-3. MAC Port 2 gets priorities 4-7.
     * Each of these set of four can then be mapped to the four switch
     * Tx priorities (NONE, LOW, MED, HIGH).
     */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        regValue = GMACSW_REGS->SL.MAC[i].SL_RX_PRI_MAP;
        for (j = 0; j < PORT_PACKET_PRIORITY_COUNT; j++)
        {
            uint32_t priorityMapValue;

            if (pPORTState->rxPacketToSwitchPriorityMap[i][j] != PORT_SWITCH_PRIORITY_UNUSED)
            {
                priorityMapValue = (((uint32_t) pPORTState->rxPacketToSwitchPriorityMap[i][j]) + i*4U) & 0x7U;
            }
            else
            {
                /* If packet priority is unused, map to best effort switch priority (NONE) */
                priorityMapValue = (i*4U) & 0x7U;
            }
            regValue = (uint32_t) ((regValue & ~(0x7U << (4U * j))) | (priorityMapValue << (4U * j)));
        }
        GMACSW_REGS->SL.MAC[i].SL_RX_PRI_MAP = regValue;
    }

    /* Set the header packet priority to switch number mapping */
    regValue = 0x00000000U;
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        for (j = 0; j < PORT_SWITCH_PRIORITY_COUNT; j++)
        {
            if (switchNum2PriorityMap[i][j] != PORT_SWITCH_PRIORITY_UNUSED)
            {
                int32_t headerPacketPriorityValue =
                    (int32_t) switchNum2PriorityMap[i][j] + (int32_t)(i*4U);
                regValue = (uint32_t)((regValue & (uint32_t)~(0x3U << (headerPacketPriorityValue*4U))) |
                           (j << ((uint32_t)headerPacketPriorityValue*4U)));
            }
        }
    }
    GMACSW_REGS->PORT.CPDMA_PORT.P0_TX_PRI_MAP = regValue;

    /* Set the Port/Switch Priority to CPDMA channel mapping */
    regValue = 0x77777777U;
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        for (j = 0; j < PORT_SWITCH_PRIORITY_COUNT; j++)
        {
            uint32_t cpdmaChannelNum = pPORTState->rxSwitchPriorityToCPDMAChannelMap[i][j];

            if (cpdmaChannelNum != PORT_CPDMA_CHANNEL_UNUSED)
            {
                uint32_t switchNum = (uint32_t)LOCAL_getSwitchPriorityNum((PORT_SwitchPriority)j, switchNum2PriorityMap[i]);
                regValue &= ~(0x7U << (switchNum*4U + i*16U));
                regValue |= cpdmaChannelNum << (switchNum*4U + i*16U);
            }
            else
            {
                /* If CPDMA channel is unused, map to highest channel number (last used) */
                cpdmaChannelNum = 7U;
            }
        }
    }
    GMACSW_REGS->PORT.CPDMA_PORT.P0_CPDMA_RX_CH_MAP = regValue;
}

static void LOCAL_updateTxPriorityMapping(const PORT_State *pPORTState)
{
    PORT_SwitchPriority switchNum2PriorityMap[MAC_NUM_PORTS][PORT_SWITCH_PRIORITY_COUNT];
    uint32_t regValue;
    uint32_t i;
    uint32_t j;
    int32_t  k;
    int32_t  l;

    /*
     * Create the switch priority to switch number mapping based on what
     *  priorities are active for both ports
     */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        for (j = 0; j < PORT_SWITCH_PRIORITY_COUNT; j++)
        {
            switchNum2PriorityMap[i][j] = PORT_SWITCH_PRIORITY_UNUSED;
        }
        for (j = 0; j < PORT_PACKET_PRIORITY_COUNT; j++)
        {
            if (pPORTState->txPacketToSwitchPriorityMap[i][j] != PORT_SWITCH_PRIORITY_UNUSED)
            {
                for (k = (int32_t)((int32_t)PORT_SWITCH_PRIORITY_COUNT - 1); k >= 0; k--)
                {
                    if (pPORTState->txPacketToSwitchPriorityMap[i][j] > switchNum2PriorityMap[i][k])
                    {
                        for (l = 1; l <= k; l++)
                        {
                            switchNum2PriorityMap[i][l-1] = switchNum2PriorityMap[i][l];
                        }
                        switchNum2PriorityMap[i][k] = pPORTState->txPacketToSwitchPriorityMap[i][j];
                    }
                    if (pPORTState->txPacketToSwitchPriorityMap[i][j] == switchNum2PriorityMap[i][k])
                    {
                        /* This mapping is accounted for */
                        break;
                    }
                }
            }
        }
    }

    /*
     * Set the packet priority to packet header priority mapping.
     * Use the default one-to-one mapping.
     */
    GMACSW_REGS->PORT.CPDMA_PORT.P0_CPDMA_TX_PRI_MAP = 0x76543210U;

    /*
     * Set the MAC packet header priority to switch priority registers.
     * Each of these set of four can then be mapped to the four switch
     * Tx priorities (NONE, LOW, MED, HIGH).
     */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        regValue = 0x00000000U;

        for (j = 0; j < PORT_PACKET_PRIORITY_COUNT; j++)
        {
            PORT_SwitchPriority switchPriority = pPORTState->txPacketToSwitchPriorityMap[i][j];
            if (switchPriority != PORT_SWITCH_PRIORITY_UNUSED)
            {
                uint32_t switchNum = (uint32_t)LOCAL_getSwitchPriorityNum(switchPriority, switchNum2PriorityMap[i]);
                regValue = (uint32_t)((regValue & (uint32_t)~(0x3U << (j*4U))) | (switchNum << (j*4U)));
            }
        }

        GMACSW_REGS->PORT.MAC_PORT[i].P_TX_PRI_MAP = regValue;
    }
}

static int32_t LOCAL_getSwitchPriorityNum(PORT_SwitchPriority switchPriority, PORT_SwitchPriority switchPriorityMap[])
{
    int32_t retVal = -1;
    int32_t i;

    for (i = 0; i < (int32_t)PORT_SWITCH_PRIORITY_COUNT; i++)
    {
        if (switchPriorityMap[i] == switchPriority)
        {
            retVal = (int32_t)i;
        }
    }

    return retVal;
}

static uint32_t LOCAL_updateRxPortSettingsForUntagged(PORT_State *pPORTState, const PORT_RxPriorityConfig *pPriConfig)
{
    uint32_t retVal = PORT_SUCCESS;
    uint32_t regValue = 0;
    uint32_t packetPriorityNum = LOCAL_getPacketPriorityNum(pPriConfig);

    uint32_t i;

    /*
     * For untagged priority handling we will do three things:
     *  1. Set the PORT_VLAN register PORT_PRI field to the provided priority value.
     *     This is the value used for all untagged packets and for IPv4 diffserv
     *     packets when RX_DSCP_PRI_EN is not asserted.
     *  2. Set the port's RX_DSCP_PRI_MAP registers to map all IPv4 diffserv to the
     *     provided priority value.  This ensures that when any diffserv mappings
     *     are enabled, all the non-mapped DSCPs will go to the original unmapped priority.
     *  3. Disable DiffServ mapping by asserting RX_DSCP_PRI_EN as it should only be
     *     enabled after this untagged mapping is in place
     */

    if (packetPriorityNum >= PORT_PACKET_PRIORITY_COUNT)
    {
        retVal = PORT_PRIORITY_TYPE_UNKNOWN;
    }
    else
    {
        /* Create the RX_DSCP_PRI_MAP register value */
        for (i = 0; i < 8U; i++)
        {
            regValue |= packetPriorityNum << ((uint32_t)i*4U);
        }
        if ((PORT_RX_SOURCE_MAC_1 == pPriConfig->rxSource) ||
            (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource))
        {
            if (0U == pPORTState->rxUntaggedMappingActive[0])
            {
                /* 1. Set the PORT_PRI field of the PORT_VLAN register  */
                CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[0].P_PORT_VLAN,
                         GMACSW_P_PORT_VLAN_PORT_PRI,
                         packetPriorityNum);
#if !defined(DEVICE_CENTAURUS)
                /* 2. Set the DSCP_PRI_MAP registers with defaults */
                for (i = 0; i < 8U; i++)
                {
                    GMACSW_REGS->PORT.MAC_PORT[0].P_RX_DSCP_PRI_MAP[i] = regValue;
                }
                /* 3. Clear the DSCP_PRI_EN bit to disable DiffServ mapping */
                CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[0].P_CONTROL,
                         GMACSW_P_CONTROL_DSCP_PRI_EN,
                         0U);
#endif
                pPORTState->rxUntaggedMappingActive[0] = 1U;
            }
            else
            {
                retVal = PORT_PRIORITY_ALREADY_MAPPED;
            }
        }
        if ((PORT_RX_SOURCE_MAC_2 == pPriConfig->rxSource) ||
            (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource))
        {
            if (0U == pPORTState->rxUntaggedMappingActive[1])
            {
                /* 1. Set the PORT_PRI field of the PORT_VLAN register */
                CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[1].P_PORT_VLAN,
                         GMACSW_P_PORT_VLAN_PORT_PRI,
                         packetPriorityNum);
#if !defined(DEVICE_CENTAURUS)
                /* 2. Set the DSCP_PRI_MAP registers with defaults */
                for (i = 0; i < 8U; i++)
                {
                    GMACSW_REGS->PORT.MAC_PORT[1].P_RX_DSCP_PRI_MAP[i] = regValue;
                }
                /* 3. Clear the DSCP_PRI_EN bit to disable DiffServ mapping */
                CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[1].P_CONTROL,
                         GMACSW_P_CONTROL_DSCP_PRI_EN,
                         0U);
#endif
                pPORTState->rxUntaggedMappingActive[1] = 1U;
            }
            else
            {
                retVal = PORT_PRIORITY_ALREADY_MAPPED;
            }
        }
    }

    return retVal;
}

#if !defined(DEVICE_CENTAURUS)
static uint32_t LOCAL_updateRxPortSettingsForDSCP(PORT_State *pPORTState, const PORT_RxPriorityConfig *pPriConfig)
{
    uint32_t retVal         = PORT_SUCCESS;

    uint32_t packetPriorityNum = LOCAL_getPacketPriorityNum(pPriConfig);

    uint32_t dscp           = pPriConfig->rxPriorityOption.diffserv.dscp & (uint32_t)0x3FU;
    uint32_t regOffset      = dscp >> 3U;
    uint32_t fieldOffset    = dscp - (regOffset << 3U);

    /*
     * For IPv4 DiffServ priority handling we will do three things:
     *  1. Verify that an untagged mapping already exists for the incoming
     *     source port.
     *  2. Set the port's RX_DSCP_PRI_MAP register to map the particular
     *     DiffServ DSCP provided
     *  3. Enable DiffServ mapping by asserting RX_DSCP_PRI_EN
     */

    /* Handle PORT 1 */
    if ((PORT_RX_SOURCE_MAC_1 == pPriConfig->rxSource) ||
        (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource))
    {
        /* 1. Ensure that an untagged mapping is already in place */
        if (0U == pPORTState->rxUntaggedMappingActive[0])
        {
            retVal = PORT_UNTAGGED_PRIORITY_UNMAPPED;
        }
        else
        {
            /* 2. Set the appropriate DSCP_PRI_MAP register and field */
            GMACSW_REGS->PORT.MAC_PORT[0].P_RX_DSCP_PRI_MAP[regOffset] =
                (GMACSW_REGS->PORT.MAC_PORT[0].P_RX_DSCP_PRI_MAP[regOffset] & ~((uint32_t)0x7U << (fieldOffset*4U))) |
                (packetPriorityNum << (fieldOffset*4U));

            /* 3. Set the DSCP_PRI_EN bit to enable DiffServ mapping */
            CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[0].P_CONTROL,
                     GMACSW_P_CONTROL_DSCP_PRI_EN,
                     1U);

            /* Keep track of how many diffserv mappings in place for this port */
            pPORTState->rxDiffservMappingCount[0]++;
        }
    }

    /* Handle PORT 2 */
    if ((PORT_RX_SOURCE_MAC_2 == pPriConfig->rxSource) ||
        (PORT_RX_SOURCE_MAC_BOTH == pPriConfig->rxSource))
    {
        /* 1. Ensure that an untagged mapping is already in place */
        if (0U == pPORTState->rxUntaggedMappingActive[0])
        {
            retVal = PORT_UNTAGGED_PRIORITY_UNMAPPED;
        }
        else
        {
            /* 2. Set the appropriate DSCP_PRI_MAP register */
            GMACSW_REGS->PORT.MAC_PORT[1].P_RX_DSCP_PRI_MAP[regOffset] =
                (GMACSW_REGS->PORT.MAC_PORT[1].P_RX_DSCP_PRI_MAP[regOffset] & ~((uint32_t)0x7U << (fieldOffset*4U))) |
                (packetPriorityNum << (fieldOffset*4U));

            /* 3. Set the DSCP_PRI_EN bit to enable DiffServ mapping */
            CSL_FINS(GMACSW_REGS->PORT.MAC_PORT[1].P_CONTROL,
                     GMACSW_P_CONTROL_DSCP_PRI_EN,
                     1U);

            /* Keep track of how many diffserv mappings in place for this port */
            pPORTState->rxDiffservMappingCount[1]++;
        }
    }

    return retVal;
}
#endif


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
