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
 *  \ingroup PM_LIB PM LIB API
 *  \defgroup CLK_RATE Clock Rate Configuration
 *
 * Initialization of the device involves setting the right frequency
 * for the clocks for the CPUs and peripherals and right voltage for
 * the voltage rails.
 *
 * The initialization of the system is carried in 3 stages:
 *  - Setting the AVS class-0 voltage and ABB voltage at boot from the SBL
 *    (\ref PM_HAL_VM)
 *  - Configuring the DPLL, multiplexer and dividers at boot time from the SBL
 *    (\ref PM_HAL_CM)
 *  - Configuring peripheral, Video Pll and CPU frequency at run time with
 *    necessaryvoltage changes. This is taken care by the
 *    PMLIB Clock Rate Configuration APIs.
 *
 * The Clock Rate Configuration provides 2 APIs to set and get the frequency
 * of any clock of any given module.
 * - PMLIBClkRateGet()
 * - PMLIBClkRateSet()
 * @{
 */

/**
 *  \file  pmlib_clkrate.h
 *
 *  \brief  PMLIB Clock Rate Manager API interface file.
 */

#ifndef PMLIB_CLKRATE_H_
#define PMLIB_CLKRATE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/pmlib_boardconfig.h>
#include <ti/drv/pm/include/prcm/pmhal_clocktree.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/pm_types.h>

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

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Function to set-up power related platform information for the
 *         given device which are the as follows :
 *
 *         1. Root Clock Frequencies which are on customer boards
 *
 *         2. Information which explains whether more than one Voltage domains
 *         share same rails or not(Ganging of voltage rails)
 *
 * \param  rootClkFreqList Array having root clock frequencies (in Hertz)
 *
 * \param  vdRailShareList Array having voltage rail sharing information between
 *                         Voltage domains
 *
 * \retval errorStatus     Status of API call. Can be any of the following,
 *          - #PM_SUCCESS      Indicates the operation is success
 *          - #PM_FAIL         Can Indicate the following:
 *                            - Array is not provided.
 *                            - Array provided is NULL
 */
pmErrCode_t PMLIBClkRateInit(uint32_t                *rootClkFreqList,
                             pmlibBoardVdRailShare_t *vdRailShareList);

/**
 * \brief  Set the clock rate of the given module.
 *
 * The API configures the necessary DPLL, Mux and
 * divider registers for a given input frequency. The API uses an internal
 * database to find the necessary device configuration for a given frequency.
 * The list of supported frequencies for a given clock of a given module can
 * be seen in the files
 * pm\pmlib\tda2xx\pmlib_clk_rate_supported_freq_tda2xx.txt.
 * The API makes sure when the frequency of a CPU is changed such that the
 * OPP shifts, the PMIC is also programmed to change the voltage to
 * correspond to this OPP shift.
 *
 * \param  modId           Module ID
 *                         Refer Enum #pmhalPrcmModuleId_t for values.
 * \param  clkId           Clock Id present in the module
 *                         Refer Enum #pmhalPrcmClockId_t for values.
 * \param  clkRate         New clock rate in Hz to be provided for the clockID
 *
 * \retval errorStatus     Status of API call. Can be any of the following,
 *         - #PM_SUCCESS      Indicates the operation is success
 *         - #PM_FAIL         Can Indicate the following:
 *                          - ModId is not valid.
 *                          - ClockRate provided is not supported
 *                          - Structure provided is not properly initialized
 *                          - Refer Enum #pmErrCode_t for detailed values.
 */
pmErrCode_t PMLIBClkRateSet(pmhalPrcmModuleId_t modId,
                            pmhalPrcmClockId_t  clkId,
                            uint32_t            clkRate);

/**
 * \brief Get the current clock rate of the given module.
 *
 * The API traverses through
 * the clock tree data structure to determine the clock frequency of a given
 * module clock at run time for debug or application feedback to know the clock
 * frequency of timers and other peripherals to convert ticks to seconds.
 *
 * \param modId            Module ID
 *                         Refer Enum #pmhalPrcmModuleId_t for values.
 * \param  clkId           Clock Id present in the module
 *                         Refer Enum #pmhalPrcmClockId_t for values.
 * \param  clkRate         New clock rate in Hz returned for the clockID
 *
 * \retval errorStatus     Status of API call. Can be any of the following,
 *         - #PM_SUCCESS      Indicates the operation is success
 *         - #PM_FAIL         Can Indicate the following:
 *                          - ModId is not valid.
 *                          - ClockId provided is not valid
 *                          - Structure provided is not properly initialized
 *                          - Refer Enum #pmErrCode_t for detailed values.
 */
pmErrCode_t PMLIBClkRateGet(pmhalPrcmModuleId_t modId,
                            pmhalPrcmClockId_t  clkId,
                            uint32_t           *clkRate);

#ifdef __cplusplus
}
#endif

#endif /* PMLIB_CLKRATE_H_ */

/* @} */


