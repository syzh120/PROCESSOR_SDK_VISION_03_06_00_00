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
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup PRCM_STAT PRCM Statistics
 *   PRCM Statistics - API to gather PRCM Statistics.
 *
 * @{
 */

/**
 *  \file     pmhal_prcm_stats.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of PRCM status.
 */

#ifndef PMHAL_PRCM_STATS_H
#define PMHAL_PRCM_STATS_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Power Domain register details
 */
typedef struct pmhalPDStats
{
    uint32_t         pwrStateCtrlRegAddr;
    /**< Power domain state control register address - ON/OFF/Retention */
    uint32_t         pwrStateCtrlRegVal;
    /**< Power domain state control register Value */
    uint32_t         pwrStateStatusRegAddr;
    /**< Power domain state status register address - ON/OFF/Retention */
    uint32_t         pwrStateStatusRegVal;
    /**< Power domain state status register Value */
    uint8_t          numClockDomain;
    /**< Number of Clock domain elements present in the power domain. */
    pmhalPrcmCdId_t *prcmCdList;
    /**< Clock Domains present in the PD */
} pmhalPDStats_t;

/**
 * \brief Clock Domain register details
 */
typedef struct pmhalCDStats
{
    uint32_t             clkStCtrlAddr;
    /**< Clock state(gated/ungated) status control register address */
    uint32_t             clkStCtrlRegVal;
    /**< Clock domain state control register Value */
    uint32_t             staticDepAddr;
    /**< Static Dependency register base address */
    uint32_t             staticDepRegVal;
    /**< Static Dependency register base Value */
    uint8_t              numModulesInCd;
    /**< Number of Clock domain elements present in the power domain. */
    pmhalPrcmModuleId_t *prcmModList;
    /**< Modules present in the CD */
} pmhalCDStats_t;

/**
 * \brief Module register details
 */
typedef struct pmhalModuleStats
{
    uint32_t clkCtrlRegAddr;
    /**< Clock mode register address. */
    uint32_t clkCtrlRegVal;
    /**< Clock domain state control register Value */
} pmhalModuleStats_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  The API gets the Power Domain Register details
 *
 *  \param  pdIdx       Unique Power domain ID.
 *                      Refer enum #pmhalPrcmPdId_t for valid values.
 *  \param  pdStatus    Structure to return the Power domain status and
 *                      list of Clockdomain in the Power Domain.
 *
 *  \return status      Status of the API. This can be the following values:
 *                      PM_SUCCESS   Indicates the operation is success
 *                      PM_FAIL      Indicates the API failed to complete the
 *                                   desired functionality. No valid Reg addr
 */
int32_t PMHALPrcmStatsGetPdRegData(pmhalPrcmPdId_t pdIdx,
                                   pmhalPDStats_t *pdStatus);

/**
 *  \brief  The API gets the Clock Domain Register details
 *
 *  \param  cdIdx       Unique Clock domain ID.
 *                      Refer enum #pmhalPrcmCdId_t for valid values.
 *  \param  cdStatus    Structure to return the Clock domain status and
 *                      list of Module elements in the Clock Domain.
 *
 *  \return status      Status of the API. This can be the following values:
 *                      PM_SUCCESS   Indicates the operation is success
 *                      PM_FAIL      Indicates the API failed to complete the
 *                                   desired functionality. No valid Reg addr
 */
int32_t PMHALPrcmStatsGetCdRegData(pmhalPrcmCdId_t cdIdx,
                                   pmhalCDStats_t *cdStatus);

/**
 *  \brief  The API gets the Module Register details
 *
 *  \param  modIdx       Unique Module ID.
 *                       Refer enum #pmhalPrcmModuleId_t for valid values.
 *  \param  modStatus    Structure to return the module status.
 *
 *  \return status      Status of the API. This can be the following values:
 *                      PM_SUCCESS   Indicates the operation is success
 *                      PM_FAIL      Indicates the API failed to complete the
 *                                   desired functionality. No valid Reg addr
 */
int32_t PMHALPrcmStatsGetModRegData(pmhalPrcmModuleId_t modIdx,
                                    pmhalModuleStats_t *modStatus);
#ifdef __cplusplus
}
#endif

#endif

/* @} */


