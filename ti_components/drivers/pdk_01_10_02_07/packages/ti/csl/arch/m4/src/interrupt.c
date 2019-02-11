/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <interrupt.h>
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
/* not required */
#else
#include <ipu_wugen.h>
#endif

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

#define M4_IRQ_PEND_CLR_START  (0xE000E280U)
#define M4_IRQ_PEND_CLR_END    (M4_IRQ_PEND_CLR_START + \
                                (M4_NUM_NVIC_EXTERNAL >> 5) * 4U)

#define M4_INT_CTL_STATE    (0xE000ED04U)

#define M4_PID0_ADDR           (0xE00FFFE0U)
#define M4_IPU1_0_PID          (0x0U)
#define M4_IPU1_1_PID          (0x1U)

/* The vector table offset should be aligend with 32 words
 * so the size allocated to ipu1_0 and ipu1_1 should be aligned with 32 words
 * (256 * 4) = 0x400
 */
#define IPU_VECTOR_TABLE_SIZE   (256U)


void       *argArray[M4_NUM_NVIC_EXTERNAL] = {0};
IntrFuncPtr fxnArray[M4_NUM_NVIC_EXTERNAL] = {0};
uint32_t    ieCookie[M4_NUM_NVIC_EXTERNAL >> 5] = {0};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#ifdef __cplusplus
#pragma CODE_SECTION(".intc_text");
#else
#pragma CODE_SECTION(HF, ".intc_text");
#endif  /* #ifdef __cplusplus */
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
void clearIntr(uint32_t intNum);
void Intc_IntClrPend(uint16_t intrNum);

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */

extern "C"
{
#endif
extern const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE];
extern int32_t _c_int00(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

void HF(void)
{
    volatile uint32_t loop = 1U;
    while (1U == loop)
    {
        ;
    }
}

#ifdef __cplusplus
#pragma NOINIT /* Prevent initialization of ipu_0VectorTable */
#else
#pragma NOINIT(ipu_0VectorTable)
#endif  /* #ifdef __cplusplus */
volatile uint32_t ipu_0VectorTable[IPU_VECTOR_TABLE_SIZE];

#ifdef __cplusplus
#pragma NOINIT /* Prevent initialization of ipu_1VectorTable */
#else
#pragma NOINIT(ipu_1VectorTable)
#endif  /* #ifdef __cplusplus */
volatile uint32_t ipu_1VectorTable[IPU_VECTOR_TABLE_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".intvecs");
#else
#pragma DATA_SECTION(vector_table, ".intvecs");
#endif  /* #ifdef __cplusplus */

const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE] =
{
    0,                    /* Stack_base + STACK_SIZE*4 */
    (uint32_t) &_c_int00, /* ResetHandler               */
    (uint32_t) &HF,
    (uint32_t) &HF,       /* Hard Fault Handler */
    (uint32_t) &HF,       /* Populate if using MemManage(MPU)  */
    (uint32_t) &HF,       /* Populate if using Bus fault       */
    (uint32_t) &HF,       /* Populate if using Usage Fault     */
    (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF, /*   Reserved slots                          */
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF,(uint32_t) &HF,  (uint32_t) &HF, (uint32_t) &HF,
    (uint32_t) &HF
};

static void IntDefaultHandler(void *dummy)
{
    /* Go into an infinite loop.*/
    volatile uint32_t loop = 1U;
    while (1U == loop)
    {
        ;
    }
}

static void masterIsr(void)
{
    IntrFuncPtr        fxnPtr;
    uint32_t           regVal;
    volatile uint32_t  intNum;
    volatile uint32_t *intCtlStateAddr = (uint32_t *) M4_INT_CTL_STATE;
    regVal = *(volatile uint32_t *) intCtlStateAddr;
    /* 9 LSBits of Interrupt control state register contain
     * the actual interrupt number*/
    intNum = regVal & 0x1FFU;
    if (fxnArray[intNum] != NULL)
    {
        fxnPtr = fxnArray[intNum];
        fxnPtr(argArray[intNum]);
    }
}

void clearIntr(uint32_t intNum) {}

void Intc_IntClrPend(uint16_t intrNum)
{
    if (intrNum >= M4_NUM_NVIC_INTERNAL)
    {
        volatile uint32_t *irqPendClrAddr = (uint32_t *) M4_IRQ_PEND_CLR_START;

        intrNum -= M4_NUM_NVIC_INTERNAL;

        while ((intrNum >= 32U) &&
               (irqPendClrAddr < (uint32_t *) M4_IRQ_PEND_CLR_END))
        {
            intrNum -= 32U;
            irqPendClrAddr++;
        }
        HW_WR_REG32((irqPendClrAddr), ((uint32_t) 1 << intrNum));
    }
}

void Intc_Init(void)
{
    volatile int32_t a;
    uint32_t vTableOffset;
    a = 0;
    if (0 != a)
    {
        volatile uint32_t b = vector_table[0];
    }

    if(HW_RD_REG32(M4_PID0_ADDR) == M4_IPU1_1_PID)
    {
        /* IPU1_1 core detected */

        /* Get offset locaton for new vector table location
         * ipu_1VectorTable and vector_table are pointer to uint and hence
         * multiplied with 4
         */
        vTableOffset = (ipu_1VectorTable - vector_table) * 4U;

        /* Set vector table offset and copy the vector table to offset location */
        memcpy((void *)ipu_1VectorTable, (void *)vector_table,
               (NUM_ELEMENTS_VECTOR_TABLE * 4U));
        HW_WR_REG32(SOC_IPU1_C0_INTC_BASE+IPU_M4_NVIC_VECTOR_TABLE_OFFSET,
                    vTableOffset);
    }
    else
    {
        /* IPU1_0 core detected */

        /* Get offset locaton for new vector table location
         * ipu_1VectorTable and vector_table are pointer to uint and hence
         * multiplied with 4
         */
        vTableOffset = (ipu_0VectorTable - vector_table) * 4U;

        /* Set vector table offset and copy the vector table to offset location */
        memcpy((void *)ipu_0VectorTable, (void *)vector_table,
               (NUM_ELEMENTS_VECTOR_TABLE * 4U));
        HW_WR_REG32(SOC_IPU1_C0_INTC_BASE+IPU_M4_NVIC_VECTOR_TABLE_OFFSET,
                    vTableOffset);
    }

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* not required */
#else
    IPU_WUGEN_Init();
#endif

    /* TODO - Check for Cortex-M3 Interrupt controller( Reset & Init) */
}

void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg)
{
    uint32_t tempIntr = (uint32_t) intrNum * 4U;

    /* Correcting the Vector table location with offset */
    if(HW_RD_REG32(M4_PID0_ADDR) == M4_IPU1_1_PID)
    {
        /* IPU1_1 core detected
         * ipu_1VectorTable and vector_table are pointer to uint and hence
         * multiplied with 4
        */
        tempIntr += ((ipu_1VectorTable - vector_table) * 4U);
    }
    else
    {
        /* IPU1_0 core detected
         * ipu_1VectorTable and vector_table are pointer to uint and hence
         * multiplied with 4
         */
        tempIntr += ((ipu_0VectorTable - vector_table) * 4U);
    }

    *(volatile uint32_t *) (tempIntr) = (uint32_t) &masterIsr;
    fxnArray[intrNum] = fptr;
    argArray[intrNum] = fun_arg;
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* not required */
#else
    if (intrNum > IPU_WUGEN_NUM_INTR_INTERNAL)
    {
        IPU_WUGEN_Enable(intrNum);
    }
#endif
}

void Intc_IntUnregister(uint16_t intrNum)
{
    fxnArray[intrNum] = &IntDefaultHandler;
    argArray[intrNum] = NULL;
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* not required */
#else
    if (intrNum > IPU_WUGEN_NUM_INTR_INTERNAL)
    {
        IPU_WUGEN_Disable(intrNum);
    }
#endif
}

void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute)
{
    /* Dummy function in Cortex - M3 */
}

void Intc_SystemEnable(uint16_t intrNum)
{
    if (intrNum >= M4_NUM_NVIC_INTERNAL)
    {
        volatile uint32_t *irqEnSetAddr = (uint32_t *) M4_IRQ_EN_SET_START;

        intrNum -= M4_NUM_NVIC_INTERNAL;

        while ((intrNum >= 32U) &&
               (irqEnSetAddr < (uint32_t *) M4_IRQ_ACTIVE_END))
        {
            intrNum -= 32U;
            irqEnSetAddr++;
        }
        HW_WR_REG32((irqEnSetAddr), ((uint32_t) 1 << intrNum));
    }
}

void Intc_SystemDisable(uint16_t intrNum)
{
    if (intrNum >= M4_NUM_NVIC_INTERNAL)
    {
        volatile uint32_t *irqEnClrAddr = (uint32_t *) M4_IRQ_EN_CLR_START;

        intrNum -= M4_NUM_NVIC_INTERNAL;

        while ((intrNum >= (uint16_t) 32U) &&
               (irqEnClrAddr < (uint32_t *) M4_IRQ_EN_CLR_END))
        {
            intrNum -= 32U;
            irqEnClrAddr++;
        }

        HW_WR_REG32((irqEnClrAddr), ((uint32_t) 1 << intrNum));
    }
}

uint8_t Intc_IntDisable(void)
{
    /* Clear GIE */
    asm (" CPSID I");

    return 0U;
}

void Intc_IntEnable(uint32_t status)
{
    asm (" CPSIE I");
}

/********************************* End of file ******************************/
