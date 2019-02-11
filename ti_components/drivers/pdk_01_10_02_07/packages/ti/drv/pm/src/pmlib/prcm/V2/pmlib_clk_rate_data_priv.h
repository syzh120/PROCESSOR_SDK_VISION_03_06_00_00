/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file  pmlib_clk_rate_data_priv.h
 *
 *  \brief This file defines the structures and functions for clock rate.
 */

#ifndef PMLIB_CLK_RATE_DATA_PRIV_H_
#define PMLIB_CLK_RATE_DATA_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_utils.h"
#include "pmhal_prcm_includes.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))
/** \brief Macro to find the number of elements of the array. */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Structure contains MuxId and required Select value for given clockrate
 */
typedef struct pmlibClockRateMuxConfig
{
    pmhalPrcmNodeId_t muxId;
    /**< Mux ID. */
    pmhalPrcmNodeId_t muxSelect;
    /**< Mux Select Value. */
} pmlibClockRateMuxConfig_t;


/**
 * \brief Structure contains divider ID and the division value for a given
 *        frequency.
 */
typedef struct pmlibClockRateDivConfig
{
    pmhalPrcmNodeId_t divId;
    /**< Divider ID. */
    uint8_t divEnum;
    /**< Division enumeration Value. */
} pmlibClockRateDivConfig_t;

/**
 * \brief Structure contains the required programming information for the
 *        clock to reach a certain frequency.
 */
typedef struct pmlibClockRateFreqConfig
{
    pmhalPrcmNodeId_t dpllId;
    /**< Dpll ID to configure */
    pmhalPrcmDpllConfig_t * dpllConfig;
    /**< Dpll configuration structure for the given CPU */
    pmlibClockRateMuxConfig_t * muxSelList;
    /**< Pointer to the mux selection to get to a given frequency */
    uint32_t numMuxSel;
    /**< Number of valid mux selection */
    pmlibClockRateDivConfig_t * divSelList;
    /**< Pointer to the divider selection to get to a given frequency */
    uint32_t numDivSel;
    /**< Number of valid divider selection */
} pmlibClockRateFreqConfig_t;

/**
 * \brief Structure contains the frequency and frequency configuration
 *        structure pointer.
 */
typedef struct pmlibClockRateFreqList
{
    uint32_t suppFreq;
    /**< Supported Frequency */
    pmlibClockRateFreqConfig_t * freqConfig;
    /**< Pointer to configuration structure for the given frequency */
} pmlibClockRateFreqList_t;

typedef struct pmlibClockRateAllFreqList
{
    pmlibClockRateFreqList_t* clkFreqList;
    /**< Pointer to the list of frequencies supported for a given clock */
    uint32_t                  numFreqSupp;
    /**< Number of frequencies supported for the given clock */
} pmlibClockRateAllFreqList_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  \brief Structure defining Clock freq configuration details for a given CLKID
 */
extern pmlibClockRateAllFreqList_t  pmlibClockRateAllClockFreq
                                        [PMHAL_PRCM_CLK_COUNT];

/**
 *  \brief Structure defining generic clocks supported for a MOD ID
 */
extern pmhalPrcmClockId_t gModuleGenericClkList[PMHAL_PRCM_MOD_COUNT];


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif
