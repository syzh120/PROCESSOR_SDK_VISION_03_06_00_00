/*
 *  Copyright (c) Texas Instruments Incorporated 2014
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
 *  \ingroup CSL_ARCH_A15
 *  \defgroup CSL_ARCH_A15_WUGEN MPU WUGEN
 *
 *  @{
 */
/**
 *  \file  mpu_wugen.h
 *
 *  \brief This file contains the API prototypes for configuring MPU_WUGEN for
 *         ARM Cortex-A15 on AM57x and TDA2xx SOC's.
 *
 */

#ifndef MPU_WUGEN_H_
#define MPU_WUGEN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

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
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to initialize MPU_WUGEN. All wakeup events will be
 *          disabled after initialization.
 *
 * \return  None.
 *
 **/
void MPU_WUGEN_Init(void);

/**
 * \brief  Disables all wakeup events for CPU0.
 *
 * \return   None
 *
 **/
void MPU_WUGEN_0_DisableAll(void);

/**
 * \brief  Disables all wakeup events for CPU1.
 *
 * \return   None
 *
 **/
void MPU_WUGEN_1_DisableAll(void);

/**
 * \brief  Configure wakeup events by looking up the CPU0 interrupt settings.
 *
 * \return   None
 *
 **/
void MPU_WUGEN_0_Interrupt_Lookup(void);

/**
 * \brief  Configure wakeup events by looking up the CPU1 interrupt settings.
 *
 * \return   None
 *
 **/
void MPU_WUGEN_1_Interrupt_Lookup(void);

/**
 * \brief   This API enables the CPU0 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void MPU_WUGEN_0_Enable(uint16_t intrNum);

/**
 * \brief   This API enables the CPU1 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void MPU_WUGEN_1_Enable(uint16_t intrNum);

/**
 * \brief   This API disables the CPU0 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void MPU_WUGEN_0_Disable(uint16_t intrNum);

/**
 * \brief   This API disables the CPU1 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void MPU_WUGEN_1_Disable(uint16_t intrNum);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef MPU_WUGEN_H_ */
 /** @} */
