/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file   irq_xbar.h
 *
 *  \brief  This module contains the IRQ XBAR hardware abstraction layer
 *
 *   This file contains the IRQ XBAR HAL API prototypes and macro definitions.
 */

#ifndef IRQ_XBAR_HAL_H
#define IRQ_XBAR_HAL_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/drv/stw_lld/platform/chip_config.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                         Structures & enums                                 */
/* ========================================================================== */
/**
 * \enum   irq_xbar_ret_type_t
 * \brief  Enumeration that specifies all possible return values from the IRQ
 *         XBAR
 *
 */
typedef enum
{
    irq_xbar_success,
    invalid_mpu_id,
    invalid_ipu_id,
    invalid_dsp_id,
#if defined (SOC_TDA2EX)
    /* No Eve in TDA2EX */
#else
    invalid_eve_id,
#endif
    invalid_pru_id,
    invalid_irq_xbar_inst_id,
    invalid_intr_source_id
} irq_xbar_ret_type_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
extern irq_xbar_ret_type_t IRQXBARValidateArgs(cpu_id_t   cpu,
                                               uint32_t   xbarInst,
                                               xbar_irq_t intrSource);

extern uint32_t IRQXBARGetOffset(cpu_id_t cpu, uint32_t xbarInst);

extern irq_xbar_ret_type_t IRQXBARConnect(uint32_t baseAddr, cpu_id_t cpu,
                                          uint32_t xbarInst,
                                          xbar_irq_t intrSource);

extern irq_xbar_ret_type_t IRQXBARDisconnect(uint32_t baseAddr,
                                             cpu_id_t cpu,
                                             uint32_t xbarInst);

extern irq_xbar_ret_type_t IRQXBARIsConnected(uint32_t   baseAddr,
                                              cpu_id_t   cpu,
                                              uint32_t   xbarInst,
                                              xbar_irq_t intrSource,
                                              uint8_t   *status);

extern irq_xbar_ret_type_t IRQXBARGetConnection(uint32_t    baseAddr,
                                                cpu_id_t    cpu,
                                                uint32_t    xbarInst,
                                                xbar_irq_t *intrSource);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
