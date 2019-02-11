/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *  \file  interrupt.h
 *
 *  \brief This file contains the API prototypes for configuring INTC for
 *         ARM Cortex-M3
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stdint.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

typedef void *IntrHandle;
typedef void  (*IntrFuncPtr)(void * ptr);

/*
** Interrupt number list
*/

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/
uint32_t disableInterrupt(void);
void restoreInterrupt(uint32_t dummyArg);

/**
 * \brief   This API is used to initialize the interrupt controller. This API
 *          shall be called before using the interrupt controller.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void Intc_Init(void);

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *
 * \param    intrNum - Interrupt Number
 * \param    fnHandler - Function pointer to the ISR
 * \param    fun_arg - Argument to the ISR
 *
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 *
 * \return      None.
 **/
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg);

/**
 * \brief   Unregisters an interrupt
 *
 * \param   intrNum - Interrupt Number
 *
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 *
 * \return      None.
 **/
void Intc_IntUnregister(uint16_t intrNum);

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.
 *
 *     'hostIntRoute' can take one of the following values \n
 *             ROUTE_IRQ - To route the interrupt to IRQ \n
 *             ROUTE_FIQ - To route the interrupt to FIQ
 *
 * \return  None.
 *
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute);

/**
 * \brief   This API enables the system interrupt in INTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemEnable(uint16_t intrNum);

/**
 * \brief   This API disables the system interrupt in INTC.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemDisable(uint16_t intrNum);

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.
 *
 * \param    None
 *
 * \return   Current status of IRQ
 *
 *
 **/
uint8_t Intc_IntDisable(void);

/**
 * \brief  Restore the processor IRQ only status. This does not affect
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    The status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 **/
void Intc_IntEnable(uint8_t status);

#ifdef __cplusplus
}
#endif
#endif
