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
 *  \file  pm_utils.h
 *
 *  \brief This file contains PM Module utility functions.
 */

#ifndef PM_UTILS_H_
#define PM_UTILS_H_

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

/** \brief Macro to find the size of the vector */
#define PM_UTIL_VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None  */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Provide a delay of at least the given time in micro seconds. In
 *         most cases this function provides more delay than the specified
 *         time; the goal is to guarantee delay of at least the given amount
 *         of time.
 *
 *
 *  \note  1. This is a blocking call.
 *         2. This function makes an assumption about the highest frequency
 *            the processor executing this code can run at.
 *
 * \param  timeUS  Time in micro seconds
 *
 * \return none
 */
void PMUtilsMinDelayUS(uint32_t timeUS);

/**
 * \brief  Provide a delay of at least the given time in ms. In
 *         most cases this function provides more delay than the specified
 *         time; the goal is to guarantee delay of at least the given amount
 *         of time.
 *
 *
 * \note   1. This is a blocking call.
 *
 * \param  timeMS  Time in ms
 *
 * \return none
 */
void PMUtilsMinDelayMS(uint32_t timeMS);

/** \brief  Utils function to get the clock domain ID in which the module is.
 *
 *  \param  modId   Module ID of the module to be checked.
 *                  Refer #pmhalPrcmModuleId_t for details.
 *
 *  \return cdId    Clock domain ID to which the module belongs.
 *                  Refer #pmhalPrcmCdId_t for details.
 */
pmhalPrcmCdId_t PMUtilsGetCdId(pmhalPrcmModuleId_t modId);

/** \brief  Utils function to get the power domain ID in which the clock domain
 *          is.
 *
 *  \param  cdId   Clock Domain ID of the CD to be checked.
 *                 Refer #pmhalPrcmCdId_t for details.
 *
 *  \return pdId    Power domain ID to which the CD belongs.
 *                  Refer #pmhalPrcmPdId_t for details.
 */
pmhalPrcmPdId_t PMUtilsGetPdId(pmhalPrcmCdId_t cdId);

/** \brief  Utils function to get the number of modules in a clock domain.
 *
 *  \param  cdId    Clock Domain ID of the CD to be checked.
 *                  Refer #pmhalPrcmCdId_t for details.
 *
 *  \return num     Number of modules in the clock domain. 0U if the clock
 *                  domain ID is invalid.
 */
uint32_t PMUtilsGetNumModsInCd(pmhalPrcmCdId_t cdId);

/** \brief  Utils function to get the module ID saved in index.
 *
 *  \param  cdId    Clock Domain ID of the CD to be checked.
 *                  Refer #pmhalPrcmCdId_t for details.
 *  \param  iter    Iteration index which is to be returned.
 *
 *  \return modId   Module ID of the module in index iter of the clock domain.
 *                  Refer #pmhalPrcmModuleId_t for details.
 *                  PMHAL_PRCM_MOD_UNDEF is returned if the iter is larger than
 *                  number of modules in the clock domain or the cdId is invalid
 */
pmhalPrcmModuleId_t PMUtilsGetModuleIdinCd(pmhalPrcmCdId_t cdId,
                                           uint32_t        iter);

/** \brief  Utils function to get the number of clock domains in a power domain.
 *
 *  \param  pdId    Power Domain ID of the PD to be checked.
 *                  Refer #pmhalPrcmPdId_t for details.
 *
 *  \return num     Number of clock domains in the power domain. 0U if the power
 *                  domain ID is invalid.
 */
uint32_t PMUtilsGetNumCdsInPd(pmhalPrcmPdId_t pdId);

/** \brief  Utils function to get the clock domain ID saved in index.
 *
 *  \param  pdId    Power Domain ID of the PD to be checked.
 *                  Refer #pmhalPrcmPdId_t for details.
 *  \param  iter    Iteration index which is to be returned.
 *
 *  \return modId   Clock Domain ID of the module in index iter of the power
 *                  domain. Refer #pmhalPrcmCdId_t for details.
 *                  PMHAL_PRCM_CD_COUNT is returned if the iter is larger than
 *                  number of CDs in the power domain or the pdId is invalid
 */
pmhalPrcmCdId_t PMUtilsGetClockDomInPd(pmhalPrcmPdId_t pdId,
                                       uint32_t        iter);

/** \brief  Utils function to report if the reset domain is a part of the power
 *          domain.
 *
 *  \param  rstId   Reset Domain ID to be checked.
 *  \param  pdId    Power Domain ID to be checked.
 *
 *  \return status  PM_SUCCESS if the reset domain ID is valid for the PD.
 *                  PM_INPUT_PARAM_BAD_RESET_ID if the reset domain ID is
 *                  invalid.
 */
pmErrCode_t PMUtilsIsResetIdValid(pmhalPrcmResetGroupId_t rstId,
                                  pmhalPrcmPdId_t         pdId);

/**
 *  \brief   PMUtilsGetModuleId returns the module id idx.
 *
 *  \param   x      Module ID of the MOD ID to be transformed. Refer
 *                  #pmhalPrcmModuleId_t for details.
 *
 *  \return  y      Modified MODID for element indexing into the module elements
 *                  structure.
 */
pmhalPrcmModuleId_t PMUtilsGetModuleId(pmhalPrcmModuleId_t x);

/**
 * \brief PMUtilsGetDpllId returns the dpll id idx.
 *
 *  \param   x      DPLL ID to be extracted
 *
 *  \return  y      Modified DPLL ID for element indexing into the dpll
 *                  elements structure.
 */
pmhalPrcmNodeId_t PMUtilsGetDpllId(pmhalPrcmNodeId_t x);

/**
 * \brief PMUtilsGetMuxId returns the Mux id idx.
 *
 *  \param   x      MUX ID to be extracted
 *
 *  \return  y      Modified MUX ID for element indexing into the mux
 *                  elements structure.
 */
pmhalPrcmNodeId_t PMUtilsGetMuxId(pmhalPrcmNodeId_t x);

/**
 * \brief PMUtilsGetDivId returns the Divider id idx.
 *
 *  \param   x      DIV ID to be extracted
 *
 *  \return  y      Modified DIV ID for element indexing into the divider
 *                  elements structure.
 */
pmhalPrcmNodeId_t PMUtilsGetDivId(pmhalPrcmNodeId_t x);

/**
 * \brief PMUtilsGetVidpllId returns the videopll id idx.
 *
 *  \param   x      Video ID to be extracted
 *
 *  \return  y      Modified Video ID for element indexing into the Video
 *                  elements structure.
 */
pmhalPrcmNodeId_t PMUtilsGetVidpllId(pmhalPrcmNodeId_t x);

/** \brief  Utils function to get the voltage domain ID in which the power
 *          domain is.
 *
 *  \param  pdId   Power Domain ID of the PD to be checked.
 *                 Refer #pmhalPrcmPdId_t for details.
 *
 *  \return vdId    Voltage domain ID to which the PD belongs.
 *                  Refer #pmhalPrcmVdId_t for details.
 */
pmhalPrcmVdId_t PMUtilsGetVdId(pmhalPrcmPdId_t pdId);

/**
 * \brief Get the CPUID if the module passed is a CPU
 *
 * \param   modId       The MODULE ID
 *          Refer       Enum #pmhalPrcmModuleId_t for values.
 *
 * \retval              CPUID of the module.
 *
 */
pmhalPrcmCpuId_t PMUtilsGetCpuId(pmhalPrcmModuleId_t modId);

/**
 * \brief  Return the OPP that can support the given rate.
 *         1. Get the current clock rate.
 *         2. Look up the pmlibOppModuleMaxRate[] table to find the right OPP
 *            and return.
 *
 * \param  cpuId   The CPU ID
 *
 * \param  rate    The Clock rate in Hz
 *
 * \return OPP     OPP that can support the given rate. If OPP not found
 *                 return PMHAL_VM_OPP_UNDEF
 */
pmhalVmOppId_t PMUtilsGetOppFromClkRate(pmhalPrcmCpuId_t cpuId,
                                        uint32_t         rate);

/**
 * \brief  Get the Voltage domain for the given CPUID
 *
 * \param  modId   The mod ID
 *
 * \return              Voltage domain of the module.
 */
pmhalPrcmVdId_t PMUtilsGetCpuVdId(pmhalPrcmModuleId_t modId);

/**
 * \brief  Get the Module ID for the given CPUID
 *
 * \param  cpuId   The cpu ID
 *
 * \return         ModuleId for the given CPU.
 *                 Refer #pmhalPrcmModuleId_t enum for details
 */
pmhalPrcmModuleId_t PMUtilsGetModIdForCpuId(pmhalPrcmCpuId_t cpuId);

#ifdef __cplusplus
}
#endif

#endif

