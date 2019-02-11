/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     pcie_app.h
 *
 *  \brief    This file contains the function declarations and macros
 *            corresponding to the pcie.
 *
**/

#ifndef PCIE_APP_H_
#define PCIE_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_pcie.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define PCIE_CONFIG_ENABLE                  ((uint32_t) 1U)
#define PCIE_CONFIG_DISABLE                 ((uint32_t) 0U)

#define PCIE_NUMBER_OF_LANES                ((uint32_t) 1U)
#define PCIE_UPPER_ADDRESS                  ((uint32_t) 0U)

#if    defined (__TI_ARM_V7M4__)
#define OUTBOUND_CFG_OFFSET                 ((uint32_t) 0x04001000U)
#else
#define OUTBOUND_CFG_OFFSET                 ((uint32_t) 0x00001000U)
#endif
#define OUTBOUND_CFG_OFFSET_LIMIT           ((uint32_t) 0x00000FFFU)
#define OUTBOUND_MEM_SPACE                  ((uint32_t) 0x05000000U)
#define OUTBOUND_MEM_SPACE_LIMIT            ((uint32_t) 0x00FFFFFFU)

#define INBOUND_PCIE_LIMIT                  ((uint32_t) 0x0FFFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
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
 * \brief   This API configures the PCIeSS1 PLL and clocks, resets the PCIeSS1
 *          and configures PHY.
 *
 * \param   none.
 *
 * \return  none.
 */
void PCIEAppPrcmConfig(void);

void AppUtilsConfigIPU1DefaultAMMU(void);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef PCIE_APP_H_ */

