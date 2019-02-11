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
 * \file hw_pmhal_prmdata.h
 *
 * \brief   This file contains the APIs to access the PRM Interrupt device
 *          specific functions.
 */

#ifndef HW_PMHAL_PRMDATA_
#define HW_PMHAL_PRMDATA_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pm_types.h"
#include "pmhal_prcm.h"

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
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This function helps read the IRQ Enable register address and the
 *          shift for a given interrupt ID.
 *
 *  \param  cpuId   Unique ID of the CPU. Refer #pmhalPrcmSocCpuId_t for details
 *  \param  intId   Unique ID of the Interrupt. Refer #pmhalPrcmPrmIntId_t for
 *                  details.
 *  \param  addr    Address of the IRQ Enable Register.
 *  \param  shift   Shift of the interrupt ID in the register.
 *
 *  \return status  Status of the APIs
 *                  PM_SUCCESS - If the address and shift are correct.
 *                  PM_BADARGS - If the CPU ID is not valid.
 */
pmErrCode_t PmhalPrmIntGetIrqEnAddrShift(pmhalPrcmSocCpuId_t cpuId,
                                         pmhalPrcmPrmIntId_t intId,
                                         uint32_t           *addr,
                                         uint32_t           *shift);

/**
 *  \brief  This function helps read the IRQ Status register address and the
 *          shift for a given interrupt ID.
 *
 *  \param  cpuId   Unique ID of the CPU. Refer #pmhalPrcmSocCpuId_t for details
 *  \param  intId   Unique ID of the Interrupt. Refer #pmhalPrcmPrmIntId_t for
 *                  details.
 *  \param  addr    Address of the IRQ Status Register.
 *  \param  shift   Shift of the interrupt ID in the register.
 *
 *  \return status  Status of the APIs
 *                  PM_SUCCESS - If the address and shift are correct.
 *                  PM_BADARGS - If the CPU ID is not valid.
 */
pmErrCode_t PmhalPrmIntGetIrqStAddrShift(pmhalPrcmSocCpuId_t cpuId,
                                         pmhalPrcmPrmIntId_t intId,
                                         uint32_t           *addr,
                                         uint32_t           *shift);

/**
 *  \brief  This function helps read the IRQ Enable register address for a given
 *          CPU ID.
 *
 *  \param  cpuId   Unique ID of the CPU. Refer #pmhalPrcmSocCpuId_t for details
 *  \param  addr    Address of the IRQ Enable Register.
 *
 *  \return status  Status of the APIs
 *                  PM_SUCCESS - If the address is correct.
 *                  PM_BADARGS - If the CPU ID is not valid.
 */
pmErrCode_t PmhalPrmIntGetIrqEnAddr(pmhalPrcmSocCpuId_t cpuId,
                                    uint32_t           *addr);

/**
 *  \brief  This function helps read the IRQ Status register address for a given
 *          CPU ID.
 *
 *  \param  cpuId   Unique ID of the CPU. Refer #pmhalPrcmSocCpuId_t for details
 *  \param  addr    Address of the IRQ Status Register.
 *
 *  \return status  Status of the APIs
 *                  PM_SUCCESS - If the address is correct.
 *                  PM_BADARGS - If the CPU ID is not valid.
 */
pmErrCode_t PmhalPrmIntGetIrqStAddr(pmhalPrcmSocCpuId_t cpuId,
                                    uint32_t           *addr);

/**
 *  \brief  This function helps read the Interrupts which are enabled.
 *
 *  \param  cpuId       CPU ID of the CPU to configure the register.
 *  \param  addr        Address of the IRQ Enable Register.
 *  \param  interrupts  The enabled interrupts are stored in this parameter
 *
 *  \return None
 */
void PmhalPrmIntGetEnabledInts(uint32_t  cpuId,
                               uint32_t  addr,
                               uint64_t *interrupts);

/**
 *  \brief  This function helps configure all PRM interrupts with the value in
 *          regVal.
 *
 *  \param  cpuId       CPU ID of the CPU to configure the register.
 *  \param  addr        Address of the IRQ Enable Register.
 *  \param  regVal      Address of the IRQ Enable Register.
 *
 *  \return None
 */
void PmhalPrmIntConfigRegister(uint32_t cpuId, uint32_t addr, uint32_t regVal);

#ifdef __cplusplus
}
#endif

#endif

