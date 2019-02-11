/*
 *  Copyright (C) 2013-2016 Texas Instruments Incorporated
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
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related APIs.
 *
 *   This file contains the APIs for configuring AINTC
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/arch/csl_arch.h>
#include <interrupt.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_a15.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                                 Macros & typedefs                          */
/* ========================================================================== */
#define REG_IDX_SHIFT                  (0x05U)
#define REG_BIT_MASK                   (0x1FU)

#define NUM_GICD_ENABLE_REGS    6U
#define NUM_BYTES_REG           4U
#define BINARY_POINT_REG_VAL    0x03
#define PRIORITY_MASK_REG_VAL   0xF0

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
IntrFuncPtr    fnRAMVectors[NUM_INTERRUPTS];
void          *argArray[NUM_INTERRUPTS] = {0};
/* This change is done as ADDR_IAR & ADDR_EOI macro from hw_intc.h
 * has an address appended with U(unsigned) which is not
 * allowed in asm file. */
const uint32_t addrIar = ADDR_IAR;
const uint32_t addrEoi = ADDR_EOI;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void IntDefaultHandler(void *dummy);
extern void CSL_A15_INIT_copyVectorTable(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

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

void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    /* Assign ISR */
    fnRAMVectors[intrNum] = fptr;
    argArray[intrNum]     = fun_arg;
}

void Intc_IntUnregister(uint16_t intrNum)
{
    uint32_t IntDefaultHandler_t = (uint32_t) (&IntDefaultHandler);
    /* Assign default ISR */
    fnRAMVectors[intrNum] = (IntrFuncPtr) IntDefaultHandler_t;
    argArray[intrNum]     = NULL;
}

void Intc_Init(void)
{
    uint32_t intActiveReg = 0;
    uint32_t i, j;

    /*Initialize vector table*/
    CSL_A15_INIT_copyVectorTable();

    /*
     * Disable forwarding of interrupts in GIC Distributor and CPU interface
     * Controller.
     */
    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE + MPU_GICD_DCR, 0);
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, 0);

    /*
     * Disable all interrupts at startup
     */
    for (i = 0U; i < NUM_GICD_ENABLE_REGS; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICER0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Disable all wakeup events at startup
     */
    MPU_WUGEN_Init();

    /*
     * Enable forwarding of both secure and non secure interrupts in GIC
     * Distributor and CPU interface
     * Controller.
     */
/*    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE + MPU_GICD_DCR,
 *          (MPU_GICD_DCR__ENABLENS | MPU_GICD_DCR_ENABLES_MASK));
 *  HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR,
 *          (MPU_GICC_ICR_ENABLES_MASK | MPU_GICC_ICR__ENABLENS |
 *                  MPU_GICC_ICR__ACKCTL | MPU_GICC_ICR__SBPR));
 */
    HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                MPU_GICD_DCR, MPU_GICD_DCR_ENABLES_MASK);
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                MPU_GICC_ICR, MPU_GICC_ICR_ENABLES_MASK);

    /* Search for any previously active interrupts and acknowledge them */
    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++)
    {
        intActiveReg =
            HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                        (MPU_GICD_ISACTIVER0 + (NUM_BYTES_REG * i)));

        if (intActiveReg)
        {
            for (j = 0U; j < 32U; j++)
            {
                if (intActiveReg & 0x1U)
                {
                    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                                MPU_GICC_EOIR, (i * 32U) + j);
                }
                intActiveReg = intActiveReg >> 1;
            }
        }
    }

    /*
     * Clear any currently pending enabled interrupts
     *
     * Note: SGIs are always enabled
     */
    for (i = 0U; i < 4U; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_CPENDSGIR0 + (NUM_BYTES_REG * i)), 0x01010101);
    }

    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICPR0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Clear all interrupt active status registers
     */
    for (i = 0; i < NUM_GICD_ENABLE_REGS; i++) {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICACTIVER0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }

    /*
     * Set MPU0 as the target processor for all interrupts.
     *
     */
    for (i = 0U; i < 48U; i++) {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPTR0 + (NUM_BYTES_REG * i)), 0x01010101);
    }

    /*
     * Initialize Binary Point Register
     */
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_BPR,
                BINARY_POINT_REG_VAL);

    /*
     * Initialize Priority mast register
     */
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_PMR,
                PRIORITY_MASK_REG_VAL);

    /*configure interrupts to level-sensitive interrupt type and 1-N model */
    for (i = 0U; i < 12U; i++)
    {
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICFR0 + (NUM_BYTES_REG * i)), 0xFFFFFFFFU);
    }
}

void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    uint32_t index, mask;
    uint32_t gicIntrId = (uint32_t)intrNum + (uint32_t)32U;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) gicIntrId >> 2) + 1U;
        mask  = (uint32_t) gicIntrId % 4U;

        /*Sets the priority of shared peripheral interrupt*/
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPR0 + (NUM_BYTES_REG * index)),
                    ((priority & (uint32_t) 0xFF) << (mask * 8U)));
    }
}

void Intc_SystemEnable(uint16_t intrNum)
{
    uint32_t index, mask, shift;
    uint32_t addr, target_cpus;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << ((uint32_t) intrNum & REG_BIT_MASK);

        /* Enable the system interrupt for interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISER0 + (NUM_BYTES_REG * index)), mask);

        index = (uint32_t) intrNum >> 2;
        shift = ((uint32_t) ((uint32_t) intrNum & 3U) << 3);
        mask  = ((uint32_t) 0xffU) << shift;
        addr  = SOC_INTC_MPU_DISTRIBUTOR_BASE +
                (MPU_GICD_IPTR8 + (NUM_BYTES_REG * index));
        target_cpus = HW_RD_FIELD32_RAW(addr,
                                        mask,
                                        shift);
        switch (target_cpus)
        {
            case 1U:
                MPU_WUGEN_0_Enable(intrNum);
                break;
            case 2U:
                MPU_WUGEN_1_Enable(intrNum);
                break;
            case 3U:
                MPU_WUGEN_0_Enable(intrNum);
                MPU_WUGEN_1_Enable(intrNum);
                break;
            default:
                MPU_WUGEN_0_Enable(intrNum);
                break;
        }
    }
}

void Intc_SystemDisable(uint16_t intrNum)
{
    uint32_t index, mask, shift;
    uint32_t addr, target_cpus;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = ((uint32_t) intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << ((uint32_t) intrNum & REG_BIT_MASK);

        /* Disable the system interrupt for interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICER0 + (NUM_BYTES_REG * index)), mask);

        index = (uint32_t) intrNum >> 2;
        shift = ((uint32_t) ((uint32_t) intrNum & 3U) << 3);
        mask  = ((uint32_t) 0xffU) << shift;
        addr  = SOC_INTC_MPU_DISTRIBUTOR_BASE +
                (MPU_GICD_IPTR8 + (NUM_BYTES_REG * index));
        target_cpus = HW_RD_FIELD32_RAW(addr,
                                        mask,
                                        shift);
        switch (target_cpus)
        {
            case 1U:
                MPU_WUGEN_0_Disable(intrNum);
                break;
            case 2U:
                MPU_WUGEN_1_Disable(intrNum);
                break;
            case 3U:
                MPU_WUGEN_0_Disable(intrNum);
                MPU_WUGEN_1_Disable(intrNum);
                break;
            default:
                MPU_WUGEN_0_Disable(intrNum);
                break;
        }
    }
}

void IntEnableSecureMode(uint32_t intrNum)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;

        mask = ~((uint32_t) 1U << (intrNum & (uint32_t) 0x1fU));

        /* Enable secure mode for interrupt number passed */
        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)));
        tmpVar &= mask;
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

void IntDisableSecureMode(uint32_t intrNum)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;

        mask = (uint32_t) 1 << (intrNum & (uint32_t) 0x1f);

        /* Disable secure mode for interrupt number passed */
        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)));
        tmpVar |= mask;
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

void IntSetPendingState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Set the interrupt status to pending for the interrupt number passed*/
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ISPR0 + (NUM_BYTES_REG * index)), mask);
    }
}

void IntClearPendingState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICPR0 + (NUM_BYTES_REG * index)), mask);
    }
}

uint32_t IntGetPendingState(uint32_t intrNum)
{
    uint32_t state = 0U;
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        state = (HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISPR0 + (NUM_BYTES_REG * index))) & mask);
    }

    return (state);
}

uint32_t IntGetActiveState(uint32_t intrNum)
{
    uint32_t state = 0U;
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        state = (HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISACTIVER0 +
                              (NUM_BYTES_REG * index))) & mask);
    }

    return (state);
}

void IntClearActiveState(uint32_t intrNum)
{
    uint32_t index, mask;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (intrNum >> REG_IDX_SHIFT) + 1U;
        mask  = ((uint32_t) 1) << (intrNum & REG_BIT_MASK);

        /* Clear the interrupt pending status for the interrupt number passed */
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICACTIVER0 + (NUM_BYTES_REG * index)), mask);
    }
}

void IntSetTargetProcessor(uint32_t intrNum, uint32_t processorSelect)
{
    uint32_t index, mask;
    uint32_t tmpVar;
    uint32_t gicIntrId = intrNum + 32U;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = (gicIntrId >> 2) + 1U;
        mask  = gicIntrId % 4U;

        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_IPTR0 + (NUM_BYTES_REG * index)));
        tmpVar |= ((processorSelect & (uint32_t) 0x03) << (mask * 8U));
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_IPTR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

void IntConfigTypenModel(uint32_t intrNum, uint32_t intType,
                         uint32_t intHandleModel)
{
    uint32_t index, mask;
    uint32_t tmpVar;

    if (intrNum < NUM_INTERRUPTS_EXTERNAL)
    {
        index = intrNum / 16U;
        mask  = intrNum % 16U;

        tmpVar = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ICFR0 + (NUM_BYTES_REG * index)));
        tmpVar &= ~(((uint32_t) MPU_GICD_ICFR0_INT_CONFIG_FIELD_0_MASK <<
                     (mask * 2U)));
        tmpVar |= ((((intType & 0x01U) << 1) |
                    (intHandleModel & 0x01U)) << (mask * 2U));
        HW_WR_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                    (MPU_GICD_ICFR0 + (NUM_BYTES_REG * index)), tmpVar);
    }
}

void IntEnableSecureFIQ(uint32_t intRoute)
{
    uint32_t tmpVar;
    if (AINTC_HOSTINT_ROUTE_FIQ == intRoute)
    {
        tmpVar  = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR);
        tmpVar |= MPU_GICC_ICR_FIQEN_MASK;
        HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, tmpVar);
    }
    else
    {
        tmpVar  = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR);
        tmpVar &= ~((uint32_t) MPU_GICC_ICR_FIQEN_MASK);
        HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_ICR, tmpVar);
    }
}

void IntSetProirityMask(uint32_t priorityMask)
{
    HW_WR_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                MPU_GICC_PMR, (priorityMask & MPU_GICC_PMR_PRIORITY_MASK));
}

uint32_t IntGetProirityMask(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                        MPU_GICC_PMR) & MPU_GICC_PMR_PRIORITY_MASK);
}

uint32_t IntGetActivePriority(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_RPR));
}

uint32_t IntGetPendingIntNum(void)
{
    return (HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE +
                        MPU_GICC_HPIR) & MPU_GICC_HPIR_PENDINTID_MASK);
}

uint32_t IntGetPendingCPUID(void)
{
    uint32_t tmpVar;
    tmpVar = HW_RD_REG32(SOC_INTC_MPU_PHYS_CPU_IF_BASE + MPU_GICC_HPIR);
    tmpVar = (tmpVar & MPU_GICC_HPIR_CPUID_MASK) >> MPU_GICC_HPIR_CPUID_SHIFT;
    return (tmpVar);
}

void IntMasterIRQEnable(void)
{
    /* Enable IRQ in CPSR.*/
    CSL_a15EnableIrq();
}

void IntMasterIRQDisable(void)
{
    /* Disable IRQ in CPSR.*/
    CSL_a15DisableIrq();
}

void IntMasterFIQEnable(void)
{
    /* Enable FIQ in CPSR.*/
    CSL_a15EnableFiq();
}

void IntMasterFIQDisable(void)
{
    /* Disable FIQ in CPSR.*/
    CSL_a15DisableFiq();
}

uint32_t IntMasterStatusGet(void)
{
    return CSL_a15IntrStatus();
}

uint8_t Intc_IntDisable(void)
{
    uint8_t status;

    /* Reads the current status.*/
    status = (uint8_t) (IntMasterStatusGet() & 0xFFU);

    /* Disable the Interrupts.*/
    IntMasterIRQDisable();

    return status;
}

void Intc_IntEnable(uint32_t status)
{
    if ((status & 0x80U) == 0)
    {
        IntMasterIRQEnable();
    }
}

void Intc_AbortHandler(void)
{
    if (0U != fnRAMVectors[INTERNAL_INTERRUPT_ABORT_ID])
    {
        fnRAMVectors[INTERNAL_INTERRUPT_ABORT_ID]
            (argArray[INTERNAL_INTERRUPT_ABORT_ID]);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

/********************************** End Of File ******************************/
