/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
#include <stdarg.h>

#include <ti/csl/tistdtypes.h>
#include <ti/osal/osal.h>
#include <ti/drv/vps/include/common/trace.h>

#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/hw_types.h>

#if defined(_TMS320C6X)
#include <ti/csl/csl_cacheAux.h>
#endif


/**
 *  \file osal.c
 *
 *  \brief Implement the OSAL layer required for starterware.
 *
 */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Check macros values. */

#if defined (__TI_ARM_V7M4__)
#define SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE  (CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS)

#if (BSP_OSAL_WAIT_FOREVER != UNICACHE_WAIT_INFINITE)
    #error "OSAL and UNICACHE wait forever macros are not same!!"
#endif
#if (BSP_OSAL_NO_WAIT != UNICACHE_WAIT_NOWAIT)
    #error "OSAL and UNICACHE no-wait macros are not same!!"
#endif
#endif

#define BSPOSAL_PRINT_BUF_LEN                       (UInt32) (1024U * 2U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Char gBspOsalPrintBuf[BSPOSAL_PRINT_BUF_LEN] = {0};
static BspOsal_InitParams_t gBspOsalInitPrms = {0};
static  uint32_t            gBspOsalClockTickCount = 0U;
static  TimerP_Handle       gBspOsalTimerHandle;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

UInt32 BspOsal_disableInterrupt(void)
{
    return (UInt32) HwiP_disable();
}

void BspOsal_restoreInterrupt(UInt32 cookie)
{
    HwiP_restore(cookie);
}

void BspOsal_clearIntr(UInt32 intNum)
{
    HwiP_clearInterrupt(intNum);
}

#define BSPOSAL_MAX_HWI_HANDLES (20U)
volatile void*   hwi[BSPOSAL_MAX_HWI_HANDLES];      /* Hwi handle */
volatile int32_t bsposal_hwi_index = -1;

BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0)
{

    OsalRegisterIntrParams_t interruptRegParams;
    bsposal_hwi_index++;
    if (bsposal_hwi_index >= BSPOSAL_MAX_HWI_HANDLES) {
       return ((BspOsal_IntrHandle) NULL);
    }

    /* Initialize with defaults */
    Osal_RegisterInterrupt_initParams(&interruptRegParams);

    /* Populate the interrupt parameters */
    interruptRegParams.corepacConfig.arg=(uintptr_t) arg0;
    interruptRegParams.corepacConfig.name=NULL;
    interruptRegParams.corepacConfig.isrRoutine=(void (*)(uintptr_t))fxn;
#if defined (__ARM_ARCH_7A__)
    interruptRegParams.corepacConfig.triggerSensitivity =  OSAL_ARM_GIC_TRIG_TYPE_EDGE;
#endif

#if defined(_TMS320C6X)
    interruptRegParams.corepacConfig.corepacEventNum=intNum; /* Event going in to CPU */
    interruptRegParams.corepacConfig.intVecNum      = OSAL_REGINT_INTVEC_EVENT_COMBINER; /* Host Interrupt vector */
#else
    interruptRegParams.corepacConfig.priority = 0x1U;
    interruptRegParams.corepacConfig.intVecNum=intNum; /* Host Interrupt vector */
    interruptRegParams.corepacConfig.corepacEventNum = intNum;
#endif
    /* Register interrupts */
    Osal_RegisterInterrupt(&interruptRegParams, (HwiP_Handle) &hwi[bsposal_hwi_index]);

    Osal_EnableInterrupt(interruptRegParams.corepacConfig.corepacEventNum, interruptRegParams.corepacConfig.intVecNum);

#if defined (__ARM_ARCH_7A__)
    Intc_SystemEnable(intNum-32);
#endif

    return ( (BspOsal_IntrHandle) hwi[bsposal_hwi_index]);
}

void BspOsal_unRegisterIntr(BspOsal_IntrHandle *pIntrHandle)
{
    bsposal_hwi_index--;
    Osal_DeleteInterrupt(*pIntrHandle, (int32_t) NULL);
}

void BspOsal_irqXbarConnect(UInt32 xbarInstance,
                            UInt32 intSource)
{
    CSL_XbarIrqCpuId cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    Int32   retVal = STW_EFAIL;

#if defined (__TI_ARM_V7M4__)
#if defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU1;
    retVal = STW_SOK;
#endif
#if defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    /* Overrides core id if its ipu2, __TI_ARM_V7M4__ is defiend for both IPUs */
    cpuId = CSL_XBAR_IRQ_CPU_ID_IPU2;
    retVal = STW_SOK;
#endif
#endif
#if defined (_TMS320C6X) || defined (BUILD_DSP_1)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP1;
    retVal = STW_SOK;
#endif
#if defined (_TMS320C6X) || defined (BUILD_DSP_2)
    cpuId = CSL_XBAR_IRQ_CPU_ID_DSP1;
    retVal = STW_SOK;
#endif
#if defined (__ARM_ARCH_7A__)
    cpuId = CSL_XBAR_IRQ_CPU_ID_MPU;
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
    Osal_delay(delayMsec);
}

UInt32 BspOsal_getClockTicks(void)
{
    return (gBspOsalClockTickCount);
}

static void BspOsaltimer_Isr(void)
{
  gBspOsalClockTickCount++;
}

void BspOsal_Init(const BspOsal_InitParams_t *bspOsalInitPrms)
{
    /* Configure the timer for 1ms ticks, to get the timer ticks */
    TimerP_Params timerParams;
    TimerP_Status status;
#if defined (__ARM_ARCH_7A__)
    uint32_t      id = 1; /* timer ID */
#elif  defined (_TMS320C6X)
    uint32_t      id = 4; /* timer ID */
#else
    uint32_t      id = 8; /* timer ID */
#endif

    if (NULL != bspOsalInitPrms)
    {
        gBspOsalInitPrms.printFxn = bspOsalInitPrms->printFxn;
    }

    TimerP_Params_init(&timerParams);
    timerParams.runMode       = TimerP_RunMode_CONTINUOUS;
    timerParams.startMode     = TimerP_StartMode_USER;
    timerParams.periodType    = TimerP_PeriodType_MICROSECS;

    gBspOsalTimerHandle = TimerP_create(id, (TimerP_Fxn)&BspOsaltimer_Isr, &timerParams);
    if (gBspOsalTimerHandle != NULL)
    {
      status = TimerP_start(gBspOsalTimerHandle);
      if (status != TimerP_OK)
      {
           GT_1trace(BspAppTrace, GT_ERR,
              "Err: Coult not start the timer %d \n", id);
      }
    }
    else
    {
      GT_1trace(BspAppTrace, GT_ERR,
                  "Err: Coult not create the timer %d \n", id);
    }
}

void BspOsal_Deinit(void)
{
      TimerP_Status status;
      status = TimerP_stop(gBspOsalTimerHandle);
      if (status != TimerP_OK)
      {
           GT_0trace(BspAppTrace, GT_ERR,
              "Err: Coult not stop the timer \n");
      }

      status = TimerP_delete(gBspOsalTimerHandle);

      if (status != TimerP_OK)
      {
           GT_0trace(BspAppTrace, GT_ERR,
              "Err: Coult not delete the timer \n");
      }

    gBspOsalInitPrms.printFxn = NULL;
}

Int32 BspOsal_printf(const Char *format, ...)
{
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
        /* Disable printf for A15 due to CCS bug
         * re-enable it after CCS fixes it JIRA: CCBT-2110 */
#if !defined (__ARM_ARCH_7A__)
        printf("%s",buf);
#endif
    }

    return (retVal);
}

UInt64 BspOsal_getTimestamp64(void)
{
    uintptr_t timerBase = (uintptr_t) SOC_COUNTER_32K_BASE;
    UInt64 baseTime;
    baseTime = (UInt64) HW_RD_REG32((uint32_t)timerBase + (uint32_t)CSL_SYNCTIMER_CR);
    return(baseTime);
}

UInt64 BspOsal_getTimestampFreq(void)
{
    UInt64       freq = (UInt64) 32U;
    /* Using the counter32K sync timer for time calculations 
     * returns, the frequency in KHz */
    return (freq);
}

UInt32 BspOsal_getCurTimeInMsec(void)
{
    UInt64 curTimeMsec, curTimeUsec;

    curTimeUsec = BspOsal_getCurTimeInUsec();
    curTimeMsec = (curTimeUsec / 1000U);

    return ((UInt32) curTimeMsec);
}

UInt64 BspOsal_getCurTimeInUsec(void)
{
    UInt64        curTs, curTimeUsec;

    curTs       = BspOsal_getTimestamp64();
    curTimeUsec = (curTs * 1000U) >> 5U;

    return (curTimeUsec);
}


UInt32 BspOsal_getTaskStackUsage(BspOsal_TaskHandle tskHandle)
{
  return (0U);
}

UInt32 BspOsal_getSystemStackUsage(void)
{
  return (0U);
}

Int32 BspOsal_getStaticMemStatus(BspOsal_StaticMemStatus *pMemStat)
{
  return (0U);
}

void BspOsal_cacheDisable(UInt32 type)
{

#if defined (__TI_ARM_V7M4__)
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheEnable(UInt32 type)
{
#if defined (__TI_ARM_V7M4__)
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheInv(void *blockPtr,
                      UInt32 byteCnt,
                      UInt32 type,
                      UInt32 timeOut)
{

     /* Built on top of Processor SDK osal callouts */
     CacheP_Inv(blockPtr, byteCnt);
     return;
}

void BspOsal_cacheWb(void *blockPtr,
                     UInt32 byteCnt,
                     UInt32 type,
                     UInt32 timeOut)
{
     /* Built on top of Processor SDK osal callouts */
     CacheP_wb(blockPtr, byteCnt);
     return;
}

void BspOsal_cacheWbAll(void)
{

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

#if defined(_TMS320C6X)
     CACHE_wbAllL1d(CACHE_FENCE_WAIT);
     CACHE_wbAllL2(CACHE_FENCE_WAIT);
#endif

    return;
}

void BspOsal_cacheWbInv(void *blockPtr,
                        UInt32 byteCnt,
                        UInt32 type,
                        UInt32 timeOut)
{

   /* Built on top of Processor SDK osal callouts */
   CacheP_wbInv(blockPtr, byteCnt);
   return;
}

void BspOsal_cacheWbInvAll(void)
{

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAndInvalidateAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

#if defined(_TMS320C6X)
     CACHE_wbInvAllL1d(CACHE_FENCE_WAIT);
     CACHE_wbInvAllL2(CACHE_FENCE_WAIT);
#endif
    return;
}

/* Nothing past this point */
