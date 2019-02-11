/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2017
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
 *  \defgroup CSL_ARCH_A15_INTERRUPT Interrupt
 *
 *  @{
 */
/**
 *  \file  a15/interrupt.h
 *
 *  \brief This file contains the API prototypes for configuring INTC for
 *         ARM Cortex-A15
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros & typedefs                          */
/* ========================================================================== */
/*
 * \brief Macros which can be passed to IntPrioritySet API as hostIntRoute.
  *  @{
*/

/* \brief To route an interrupt to IRQ */
#define AINTC_HOSTINT_ROUTE_IRQ                (0U)

/* \brief To route an interrupt to FIQ */
#define AINTC_HOSTINT_ROUTE_FIQ                (1U)

/* External interrupt from the system */
#define NUM_INTERRUPTS_EXTERNAL     (160U)

/*\brief Internal interrupts in ARMV7A core Currently only supporting ABORT*/
#define NUM_INTERRUPTS_INTERNAL     (1U)

#define INTERNAL_INTERRUPT_ABORT_ID (NUM_INTERRUPTS_EXTERNAL)

#define NUM_INTERRUPTS    (1024U)
/* @} */

/* ========================================================================== */
/*                          Internal typedef Declarations                     */
/* ========================================================================== */
typedef void (*IntrFuncPtr)(void *handle);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *
 * \param    intrNum - Interrupt Number
 * \param    fptr    - Function pointer to the ISR
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
 * \brief   This API is used to initialize the interrupt controller. This API
 *          shall be called before using the interrupt controller.
 *
 * \return  None.
 *
 **/
void Intc_Init(void);

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - Unused currently
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
 * \brief   This API configures the interrupt passed to secure.
 *          In secure mode interrupts can be routed to either IRQ or FIQ.
 *
 * \param   intrNum  - Interrupt number
 *
 *
 * \return  None.
 *
 **/
void IntEnableSecureMode(uint32_t intrNum);

/**
 * \brief   This API configures the interrupt passed to non-secure.
 *          In non-secure mode interrupts can only be routed to IRQ
 *
 * \param   intrNum  - Interrupt number
 *
 *
 * \return  None.
 *
 **/
void IntDisableSecureMode(uint32_t intrNum);

/**
 * \brief   This API sets the status of the interrupt passed to pending.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntSetPendingState(uint32_t intrNum);

/**
 * \brief   This API clears the pending status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntClearPendingState(uint32_t intrNum);

/**
 * \brief   This API gets the pending status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  non zero value if pending.
 *          0              if not pending
 *
 **/
uint32_t IntGetPendingState(uint32_t intrNum);

/**
 * \brief   This API gets the active status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  non zero value if active.
 *          0              if not active
 *
 **/
uint32_t IntGetActiveState(uint32_t intrNum);

/**
 * \brief   This API clears the Active status of interrupt passed.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntClearActiveState(uint32_t intrNum);

/**
 * \brief   This API configures the target processor for the interrupt passed
 *
 * \param   intrNum  - Interrupt number
 *
 * \param   processorSelect - Possible values are:
 *                            0x1 - Pending interrupt is sent to processors 0
 *                            0x2 - Pending interrupt is sent to processors 1
 *                            0x3 - Pending interrupt is sent to processors 0
 *                                  and 1
 * \return  None.
 *
 **/
void IntSetTargetProcessor(uint32_t intrNum, uint32_t processorSelect);

/**
 * \brief   This API configures the type of interrupt and Mode of interupt
 *          handling
 *
 * \param   intrNum  - Interrupt number
 *
 * \param   intType  - Possible values are:
 *                     0x0 - interrupt set to level sensitive type
 *                     0x1 - interrupt set to edge triggered type
 *
 * \param   intHandleModel  -
 *          1-N Model : Only one processor handles this interrupt. The system
 *          must implement a mechanism to determine which processor handles an
 *          interrupt that is programmed to target more than one processor.
 *
 *          1-N Model :All processors receive the interrupt independently. When
 *          a processor acknowledges the interrupt, the interrupt pending state
 *          is cleared only for that processor. The interrupt remains pending
 *          for the other processors
 *
 *          Possible values are:
 *             0x0 - interrupt set to 1-N interrupt handling Model
 *             0x1 - interrupt set to N-N interrupt handling Model
 *
 * \return  None.
 *
 **/
void IntConfigTypenModel(uint32_t intrNum, uint32_t intType,
                         uint32_t intHandleModel);

/**
 * \brief   This API configures whether the interrupt in secure mode to be
 *          routed to IRQ or FIQ
 *
 * \param   intRoute  - Possible values
 *                      AINTC_HOSTINT_ROUTE_IRQ - Interrupt routed to IRQ
 *                      AINTC_HOSTINT_ROUTE_FIQ - Interrupt routed to FIQ
 *
 * \return  None.
 *
 **/
void IntEnableSecureFIQ(uint32_t intRoute);

/**
 * \brief        The priority mask level for the CPU interface. If the
 *               priority of an interrupt is higher than the
 *               value indicated by this field, the interface signals the
 *               interrupt to the processor.
 *               If the GIC supports fewer than 256 priority levels then some
 *               bits are RAZ/WI, as follows:
 *               128 supported levels Bit [0] = 0.
 *               64 supported levels Bit [1:0] = 0b00.
 *               32 supported levels Bit [2:0] = 0b000.
 *               16 supported levels Bit [3:0] = 0b0000. - (RW)
 *
 * \param        priorityMask - Priority mask
 *
 * \return  None.
 *
 **/
void IntSetProirityMask(uint32_t priorityMask);

/**
 * \brief   returns the priority mask level for the CPU interface.
 *
 * \return  prirityMask.
 *
 **/
uint32_t IntGetProirityMask(void);

/**
 * \brief   This API returns the priority value of the highest priority
 *          interrupt that is active on the CPU interface
 *
 * \return  priority value of the highest priority interrupt
 *          that is active on the CPU interface
 *
 **/
uint32_t IntGetActivePriority(void);

/**
 * \brief  returns the interrupt ID of the highest priority pending interrupt
 *
 * \return interrupt ID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingIntNum(void);

/**
 * \brief  On a multiprocessor implementation, if the PENDINTID field returns
 *         the ID of an SGI, this field contains the CPUID value for that
 *         interrupt. This identifies the processor that generated the
 *         interrupt.
 *
 * \return CPUID of the highest priority pending interrupt
 *
 */
uint32_t IntGetPendingCPUID(void);

/**
 * \brief  Enables the processor IRQ only in CPSR. Makes the processor to
 *         respond to IRQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQEnable(void);

/**
 * \brief  Disables the processor IRQ only in CPSR.Prevents the processor to
 *         respond to IRQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQDisable(void);

/**
 * \brief  Enables the processor FIQ only in CPSR. Makes the processor to
 *         respond to FIQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQEnable(void);

/**
 * \brief  Disables the processor FIQ only in CPSR.Prevents the processor to
 *         respond to FIQs.  This does not affect the set of interrupts
 *         enabled/disabled in the AINTC.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQDisable(void);

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint32_t IntMasterStatusGet(void);

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.
 *
 * \return   Current status of IRQ
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint8_t Intc_IntDisable(void);

/**
 * \brief  Restore the processor IRQ only status. This does not affect
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    status Status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void Intc_IntEnable(uint32_t status);

/**
 * \brief     This API is called when the CPU is aborted When the abort
 *            interrupt occurs , the control goes to the ISR which is registered
 *            using Intc_IntRegister else will result in infinite loop.
 *
 * \return    None.
 *
 **/
void Intc_AbortHandler(void);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
/**
 *  \ingroup CSL_ARCH
 *  \defgroup CSL_ARCH_A15 A15
 */
/********************************* End of file ******************************/
