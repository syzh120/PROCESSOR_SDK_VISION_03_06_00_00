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
 *   \file  stats.c
 *
 *   \brief
 *          GMACSW Statistics gathering and processing functionality
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
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
#include "gmacsw_al.h"

/* This module's private header */
#include "private/stats_.h"

/* This module's header */
#include "stats.h"


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

static uint32_t LOCAL_clearStats(STATS_Handle hStats);
static uint32_t LOCAL_getStats(STATS_Handle hStats, STATS_Statistics *pStatistics);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
STATS_State STATS_stateObj;
#endif

/* Data to keep track of open references to the Stats structure */
static uint32_t     LOCAL_statsRefCount = 0;
static STATS_State  *LOCAL_statsRef     = NULL;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

STATS_Handle STATS_open(STATS_Config *pStatsConfig, uint32_t activeMACPortMask)
{
    STATS_State *pStats = NULL;

    uint32_t    key = GMACSW_AL_globalInterruptDisable();

    /* Increment the reference count */
    LOCAL_statsRefCount++;

    if ((uint32_t)1U == LOCAL_statsRefCount)
    {
#if defined(NSP_DYNAMIC_ALLOCATION)
        pStats = (STATS_State *) calloc(1U, sizeof(STATS_State));
#else
        pStats = &STATS_stateObj;
#endif

        /* Zero init the STATS_State structure */
        memset(pStats, 0, sizeof(STATS_State));

        pStats->pStatsConfig = pStatsConfig;

        if (1U == pStatsConfig->enableStatistics)
        {
            /* Enable statistics gathering for each port */
            GMACSW_REGS->SS.CPSW_STAT_PORT_EN =
                CSL_FMK(GMACSW_CPSW_STAT_PORT_EN_P0_STAT_EN, 1U) |
                CSL_FMK(GMACSW_CPSW_STAT_PORT_EN_P1_STAT_EN,
                                        ((activeMACPortMask >> 0U) & 1U) ) |
                CSL_FMK(GMACSW_CPSW_STAT_PORT_EN_P2_STAT_EN,
                                        ((activeMACPortMask >> 1U) & 1U));

            /* Enable the STATS interrupt by setting the mask bit */
            CSL_FINS( GMACSW_REGS->CPDMA.CPDMA_DMA_INTMASK_SET,
                      GMACSW_CPDMA_DMA_INTMASK_SET_STAT_INT_MASK,
                      1);

            /* Enable the STATS interrupt in the wrapper module */
            CSL_FINS( GMACSW_REGS->WR.WR_C0_MISC_EN,
                      GMACSW_WR_C0_MISC_EN_STAT_PEND,
                      1);
        }

        /* Save a pointer to the state structure to be used to provide a reference for future open calls */
        LOCAL_statsRef = pStats;
    }
    else
    {
        /*
         * If reference count at entry was non-zero, Stats was already opened, so
         * we just return a pointer to the state structure and increment the reference count
         */
         pStats = LOCAL_statsRef;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return (STATS_Handle) pStats;
}

uint32_t STATS_close(STATS_Handle hStats)
{
    STATS_State *pStats = (STATS_State *) hStats;
    uint32_t retVal = STATS_SUCCESS;
    uint32_t key = GMACSW_AL_globalInterruptDisable();

    /* Decrement reference counter and return if still non-zero */
    LOCAL_statsRefCount--;

    if (0U == LOCAL_statsRefCount)
    {

#if defined(NSP_DYNAMIC_ALLOCATION)
        free(pStats);
#else
        memset(pStats, 0 , sizeof(STATS_State));
#endif
        /* Reset the local reference holder */
        LOCAL_statsRef = NULL;
    }

    GMACSW_AL_globalInterruptEnable(key);

    return retVal;
}

uint32_t STATS_ioctl(STATS_Handle hStats, uint32_t cmd, void *param, uint32_t size)
{
    uint32_t retVal = STATS_SUCCESS;

    /* Decode the command and act on it */
    switch (cmd)
    {
        case GMACSW_IOCTL_STATS_CLEAR_STATS:
        {
            if ((0U != size) || (NULL != param))
            {
                retVal = STATS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_clearStats(hStats);
            }
            break;
        }
        case GMACSW_IOCTL_STATS_GET_STATS:
        {
            if ((sizeof(STATS_Statistics) != size) || (NULL == param))
            {
                retVal = STATS_MALFORMED_IOCTL;
            }
            else
            {
                retVal = LOCAL_getStats(hStats, (STATS_Statistics *) param);
            }
            break;
        }
        default:
        {
            retVal = STATS_UNKNOWN_IOCTL;
            break;
        }
    }

    return retVal;
}

void STATS_update(STATS_Handle hStats)
{
    volatile uint32_t *statRegs;
    uint64_t          *pStatAddr;
    uint32_t          statval;

    statRegs    = &GMACSW_REGS->STATS.RXGOODFRAMES;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    pStatAddr   = (uint64_t *)((void *)(&hStats->stats));

    while((uint32_t)statRegs <= (uint32_t) &GMACSW_REGS->STATS.RXDMAOVERRUNS)
    {
        statval     = *statRegs;
        *statRegs   = statval;
        *pStatAddr  += statval;

        statRegs++;
        pStatAddr++;
    }
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/* LOCAL IOCTL implementations */
static uint32_t LOCAL_clearStats(STATS_Handle hStats)
{
    volatile uint32_t *statRegs;
    uint64_t          *pStatAddr;

    statRegs    = &GMACSW_REGS->STATS.RXGOODFRAMES;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    pStatAddr   = (uint64_t *)((void *)(&hStats->stats));

    while(statRegs <= &GMACSW_REGS->STATS.RXDMAOVERRUNS)
    {
        /* Write to decrement to zero */
        *statRegs = 0xFFFFFFFFU;
        /* Clear the software accumulation structure */
        *pStatAddr = (uint64_t)0U;

        statRegs++;
        pStatAddr++;
    }

    return STATS_SUCCESS;
}

static uint32_t LOCAL_getStats(STATS_Handle hStats, STATS_Statistics *pStatistics)
{
    /* Update the stats */
    STATS_update(hStats);

    /* Copy the updated stats to the application */
    memcpy(pStatistics, &hStats->stats, sizeof(STATS_Statistics));

    return STATS_SUCCESS;
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

