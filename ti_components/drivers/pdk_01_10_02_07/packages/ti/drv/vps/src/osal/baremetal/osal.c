/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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
 */

#include <stdint.h>
#include <stdio.h>  /* Required to handle variable argument list */
#include <ti/csl/csl_types.h>

#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/src/ip/synctimer/V0/hw_counter_32k.h>

/**
 *  \file osal.c
 *
 *  \brief Implement the OSAL layer required for starterware.
 *
 */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPOSAL_PRINT_BUF_LEN                       (UInt32) (1024U * 2U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if !((defined (__ARM_ARCH_7A__)) || (defined (BUILD_A8)))
static Char gBspOsalPrintBuf[BSPOSAL_PRINT_BUF_LEN] = {0};
static BspOsal_InitParams_t gBspOsalInitPrms = {0};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

UInt32 BspOsal_disableInterrupt(void)
{
    return (UInt32) Intc_IntDisable();
}

void BspOsal_restoreInterrupt(UInt32 cookie)
{
    Intc_IntEnable(cookie);
}

void BspOsal_clearIntr(UInt32 intNum)
{
}

BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0)
{
    Intc_IntRegister((UInt16) intNum, (IntrFuncPtr) fxn, (void *) arg0);
#if defined (BUILD_ARP32)
    if (intNum < 32U)
    {
        Intc_IntPrioritySet((UInt16) intNum, (UInt16) INTH_INT4, 0);
    }
    else if (intNum < 64U)
    {
        Intc_IntPrioritySet((UInt16) intNum, (UInt16) INTH_INT8, 0);
    }
    else if (intNum < 96U)
    {
        Intc_IntPrioritySet((UInt16) intNum, (UInt16) INTH_INT12, 0);
    }
    else
    {
        Intc_IntPrioritySet((UInt16) intNum, (UInt16) INTH_INT14, 0);
    }
#else
    Intc_IntPrioritySet((UInt16) intNum, (UInt16) 1, 0);
#endif
    Intc_SystemEnable((UInt16) intNum);
    return (BspOsal_IntrHandle) intNum;
}

void BspOsal_unRegisterIntr(BspOsal_IntrHandle *pIntrHandle)
{
    UInt32 intNum = (UInt32) * pIntrHandle;
    Intc_SystemDisable((UInt16) intNum);
    Intc_IntUnregister((UInt16) intNum);
}

void BspOsal_irqXbarConnect(UInt32 xbarInstance,
                            UInt32 intSource)
{
    CSL_XbarIrqCpuId cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    Int32   retVal = STW_EFAIL;

#if defined (__TI_ARM_V7M4__) || defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    /* Overrides core id if its ipu2, __TI_ARM_V7M4__ is defiend for both IPUs */
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU2;
    retVal = STW_SOK;
#endif
#if defined (BUILD_DSP_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_DSP_2)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP2;
    retVal = STW_SOK;
#endif
#if defined (__ARM_ARCH_7A__)
    cpuId = CSL_XBAR_IRQ_CPU_ID_MPU;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_2)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE2;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_3)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE3;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_4)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE4;
    retVal = STW_SOK;
#endif

    if (STW_SOK == retVal)
    {
        CSL_xbarIrqConfigure(cpuId, xbarInstance, (CSL_XbarIrq) intSource);
    }

    return;
}

void BspOsal_irqXbarDisconnect(UInt32 xbarInstance)
{
    CSL_XbarIrqCpuId cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    Int32   retVal = STW_EFAIL;

#if defined (__TI_ARM_V7M4__) || defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    /* Overrides core id if its ipu2, __TI_ARM_V7M4__ is defiend for both IPUs */
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU2;
    retVal = STW_SOK;
#endif
#if defined (BUILD_DSP_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_DSP_2)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP1;
    retVal = STW_SOK;
#endif
#if defined (__ARM_ARCH_7A__)
    cpuId = CSL_XBAR_IRQ_CPU_ID_MPU;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_2)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE2;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_3)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE3;
    retVal = STW_SOK;
#endif
#if defined (BUILD_ARP32_4)
    cpuId = CSL_XBAR_IRQ_CPU_ID_EVE4;
    retVal = STW_SOK;
#endif

    if (STW_SOK == retVal)
    {
        CSL_xbarIrqConfigure(cpuId, xbarInstance, CSL_XBAR_IRQ_MIN);
    }

    return;
}

BspOsal_SemHandle BspOsal_semCreate(Int32 initValue, Bool isBinary)
{
    /* Semaphores not supported in these mode */
    return (BspOsal_SemHandle) 1;
}

void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle)
{
    /* Semaphores not supported in these mode */
}

Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut)
{
    /* Semaphores not supported in these mode */
    return TRUE;
}

void BspOsal_semPost(BspOsal_SemHandle semHandle)
{
    /* Semaphores not supported in these mode */
}

void BspOsal_sleep(UInt32 delayMsec)
{
    volatile UInt32 a = delayMsec * 100U;
    while (a--)
    {
        /* delay */
    }
}

UInt32 BspOsal_getClockTicks(void)
{
    /* Using the 32 KHz free running counter
        20 MHz Crystal inputs with divider of 610
        = (20 * 1000 000)/610 = 32786.88
        (1 / 32786.88) * 1000000 = 30.5 us

       30.5 micro seconds / tick */

    return (HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR));
}

void BspOsal_Init(const BspOsal_InitParams_t *bspOsalInitPrms)
{
    if (NULL != bspOsalInitPrms)
    {
#if !((defined (__ARM_ARCH_7A__)) || (defined (BUILD_A8)))
        gBspOsalInitPrms.printFxn = bspOsalInitPrms->printFxn;
#endif
    }
}

void BspOsal_Deinit(void)
{
#if !((defined (__ARM_ARCH_7A__)) || (defined (BUILD_A8)))
    gBspOsalInitPrms.printFxn = NULL;
#endif
}

Int32 BspOsal_printf(const Char *format, ...)
{
#if (defined (__ARM_ARCH_7A__)) || (defined (BUILD_A8))
    Int32   retVal = 0;
#else
    va_list vaArgPtr;
    Int32   retVal = 0;
    Char   *buf    = NULL;

    buf = &gBspOsalPrintBuf[0];
    va_start(vaArgPtr, format);
    vsnprintf(buf, BSPOSAL_PRINT_BUF_LEN,
              (const Char *) format, vaArgPtr);
    va_end(vaArgPtr);

    if (NULL != gBspOsalInitPrms.printFxn)
    {
        gBspOsalInitPrms.printFxn(buf);
    }
    else
    {
        printf("%s",buf);
    }

#endif
    return (retVal);
}

UInt64 BspOsal_getTimestamp64(void)
{
    return (0U);
}

UInt64 BspOsal_getTimestampFreq(void)
{
    return (1U);
}

UInt32 BspOsal_getCurTimeInMsec(void)
{
    return (0U);
}

UInt64 BspOsal_getCurTimeInUsec(void)
{
    return (0U);
}
