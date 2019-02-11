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

#include "stdint.h"
#include "stddef.h"
#include <stw_dataTypes.h>
#include <stw_types.h>
#include "hw_types.h"
#include "interrupt.h"

#define M4_NUM_NVIC_INTERNAL   (16U)
#define M4_NUM_NVIC_EXTERNAL   (128U)
#define M4_IRQ_EN_SET_START    (0xE000E100U)
#define M4_IRQ_EN_SET_END      (M4_IRQ_EN_SET_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)
#define M4_IRQ_EN_CLR_START    (0xE000E180U)
#define M4_IRQ_EN_CLR_END      (M4_IRQ_EN_CLR_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)
#define M4_IRQ_ACTIVE_START    (0xE000E300U)
#define M4_IRQ_ACTIVE_END      (M4_IRQ_ACTIVE_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)

void       *argArray[M4_NUM_NVIC_EXTERNAL] = {0};
IntrFuncPtr fxnArray[M4_NUM_NVIC_EXTERNAL] = {0};
uint32_t    ieCookie[M4_NUM_NVIC_EXTERNAL >> 5] = {0};

/******************************************************************************
**                FUNCTION DECLARATIONS
******************************************************************************/
#pragma CODE_SECTION(HF, ".intc_text");
void HF(void);
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void IntDefaultHandler(void *dummy);
#ifdef __cplusplus
}
#endif

static void masterIsr(void);
static void masterIsr_nmi(void);
void clearIntr(uint32_t intNum);

/******************************************************************************
**
******************************************************************************/

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */

extern "C"
{
#endif

extern int32_t _c_int00(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

void HF(void)
{
    volatile int32_t a;
    a = 0;
}

#pragma DATA_SECTION(vector_table, ".intvecs");
const volatile uint32_t vector_table[] =
{
    0,                    /* Stack_base + STACK_SIZE*4 */
    (uint32_t) &_c_int00, /* ResetHandler               */
    (uint32_t) &masterIsr_nmi,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr, /* Populate if using MemManage(MPU)  */
    (uint32_t) &masterIsr, /* Populate if using Bus fault       */
    (uint32_t) &masterIsr, /* Populate if using Usage Fault     */
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr, /*   Reserved slots                          */
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr,(uint32_t) &masterIsr,  (uint32_t) &masterIsr, (uint32_t) &masterIsr,
    (uint32_t) &masterIsr
};

/**
 *
 * The Default Interrupt Handler.
 *
 * This is the default interrupt handler for all interrupts.  It simply loops
 * forever so that the system state is preserved for observation by a
 * debugger.  Since interrupts should be disabled before unregistering the
 * corresponding handler, this should never be called.
 *
 *
 **/
static void IntDefaultHandler(void *dummy)
{
    /* Go into an infinite loop.*/
    volatile uint32_t loop = 1U;
    while (1U == loop)
    {
        ;
    }
}

/**
 *
 * Master ISR handler.
 *
 * Reads the active interrupt number & check for status.
 * Call the registered ISR function with arguments
 *
 *
 **/

static void masterIsr_nmi(void)
{
    /* Go into an infinite loop.*/
    volatile uint32_t loop = 1U;
    while(loop==1);
}
static void masterIsr(void)
{
    IntrFuncPtr        fxnPtr;
   int internalIntr=1;
    volatile uint32_t *irqActiveAddr = (uint32_t *) M4_IRQ_ACTIVE_START;
    volatile uint32_t  intNum        = M4_NUM_NVIC_INTERNAL;
    while (irqActiveAddr < (uint32_t *) M4_IRQ_ACTIVE_END)
    {
        uint32_t i = 0;
        if (*(volatile uint32_t *) irqActiveAddr != 0)
        {
            while (i < 32U)
            {
                if ((*(volatile uint32_t *) irqActiveAddr &
                     ((uint32_t) 1 << i)) != 0U)
                {
                    if (fxnArray[intNum] != NULL)
                    {
                        fxnPtr = fxnArray[intNum];
                        fxnPtr(argArray[intNum]);
                        internalIntr=0;
                    }
                }
                i++;
                intNum++;
            }
        }
        else
        {
            intNum += 32U;
        }
        irqActiveAddr++;
    }
    if(internalIntr)
    {
       HF();
    }
}

void clearIntr(uint32_t intNum) {}

void Intc_Init(void)
{
    volatile int32_t a;
    a = 0;
    if (0 != a)
    {
        volatile int32_t b = vector_table[0];
    }
    /* TODO - Check for Cortex-M3 Interrupt controller( Reset & Init) */
}

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *
 **/
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    uint32_t tempIntr = (uint32_t) intrNum * 4U;
    //*(volatile uint32_t *) (intrNum * 4) = (uint32_t) &masterIsr;
    fxnArray[intrNum] = fptr;
    argArray[intrNum] = fun_arg;
}

/**
 * \brief   Unregisters an interrupt
 *
 **/
void Intc_IntUnregister(uint16_t intrNum)
{
    fxnArray[intrNum] = &IntDefaultHandler;
    argArray[intrNum] = NULL;
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    /* Dummy function in Cortex - M3 */
}

/**
 * \brief   This API enables the system interrupt in INTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 **/
void Intc_SystemEnable(uint16_t intrNum)
{
    volatile uint32_t *irqEnSetAddr = (uint32_t *) M4_IRQ_EN_SET_START;

    intrNum -= M4_NUM_NVIC_INTERNAL;

    while ((intrNum >= 32U) && (irqEnSetAddr < (uint32_t *) M4_IRQ_ACTIVE_END))
    {
        intrNum -= 32U;
        irqEnSetAddr++;
    }
    *(volatile uint32_t *) (irqEnSetAddr) = ((uint32_t) 1 << intrNum);
}

/**
 * \brief   This API disables the system interrupt in INTC.
 **/
void Intc_SystemDisable(uint16_t intrNum)
{
    volatile uint32_t *irqEnClrAddr = (uint32_t *) M4_IRQ_EN_CLR_START;

    intrNum -= M4_NUM_NVIC_INTERNAL;

    while ((intrNum > 32U) && (irqEnClrAddr < (uint32_t *) M4_IRQ_EN_CLR_END))
    {
        intrNum -= 32U;
        irqEnClrAddr++;
    }

    *(volatile uint32_t *) (irqEnClrAddr) = ((uint32_t) 1 << intrNum);
}

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.
 **/
uint8_t Intc_IntDisable(void)
{
    uint32_t           dummyRetVal  = 0;
    uint32_t           i            = 0;
    volatile uint32_t *irqEnSetAddr = (uint32_t *) M4_IRQ_EN_SET_START;
    volatile uint32_t *irqEnClrAddr = (uint32_t *) M4_IRQ_EN_CLR_START;
    while ((irqEnSetAddr < (uint32_t *) M4_IRQ_EN_SET_END) &&
           (irqEnClrAddr < (uint32_t *) M4_IRQ_EN_CLR_END))
    {
        ieCookie[i] = *(volatile uint32_t *) (irqEnSetAddr);
        *(volatile uint32_t *) (irqEnClrAddr) = ieCookie[i];
        i++;
        irqEnSetAddr++;
        irqEnClrAddr++;
        dummyRetVal++;
    }
    return (uint8_t) dummyRetVal;
}

/**
 * \brief  Restore the processor IRQ only status. This does not affect
 *          the set of interrupts enabled/disabled in the AINTC.
 **/
void Intc_IntEnable(uint8_t status)
{
    uint32_t           i = 0;
    volatile uint32_t *irqEnSetAddr = (uint32_t *) M4_IRQ_EN_SET_START;
    while (irqEnSetAddr < (uint32_t *) M4_IRQ_EN_SET_END)
    {
        *(volatile uint32_t *) (irqEnSetAddr) = ieCookie[i];
        i++;
        irqEnSetAddr++;
    }
}
