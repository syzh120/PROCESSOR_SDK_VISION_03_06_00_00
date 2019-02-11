/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file   core_loading.c
 *
 *  \brief  A15 Core loading Example
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef BARE_METAL
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Types.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/utils/Load.h>
#endif

#include <string.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include "dhrystone.h"
#include "app_utils.h"
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/pm/examples/utils/uartStdio.h>

#if defined (BUILD_ARP32)
#include <tlb_config_eve_common.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* populate this to modify CPU load */
#define REQUIRED_CPU_LOAD_IN_PERCENT   (80)

/*******************************************************************************
 * Setup a low frequency clock periodic function
 * to call the CLK32KHZ counter function
 * in order to track overflow condition
 *
 * CLK32KHZ will roughly overflow after 1 day of operation
 * so calling this periodic function once in one hour is enough to
 * guard against overflow condition
 *******************************************************************************
 */
#define  COUNTER_32K_OVERFLOW_CHECK_TIMER_PERIOD_IN_MS          (1000U*60U*60U)

#undef  COUNTER_32K_CR
#define COUNTER_32K_CR          (*(volatile uint32_t*)0x4AE04030U)
#define COUNTER_32K_CR_REF_CLK   (32786U) /* Actual value used on 20M/610
                                            610 is post div in clock tree*/

#if defined (BUILD_A15_0)
#define APP_CORE        "[A15-0  ]"
#elif defined (BUILD_IPU1_0)
#define APP_CORE        "[IPU1-0 ]"
#elif defined (BUILD_IPU1_1)
#define APP_CORE        "[IPU1-1 ]"
#elif defined (BUILD_DSP_1)
#define APP_CORE        "[DSP-1  ]"
#elif defined (BUILD_DSP_2)
#define APP_CORE        "[DSP-2  ]"
#elif defined (BUILD_ARP32_1)
#define APP_CORE        "[EVE-1  ]"
#elif defined (BUILD_ARP32_2)
#define APP_CORE        "[EVE-2  ]"
#elif defined (BUILD_ARP32_3)
#define APP_CORE        "[EVE-3  ]"
#elif defined (BUILD_ARP32_4)
#define APP_CORE        "[EVE-4  ]"
#elif defined (BUILD_IPU2_0)
#define APP_CORE        "[IPU2-0 ]"
#elif defined (BUILD_IPU2_1)
#define APP_CORE        "[IPU2-1 ]"
#else
#define APP_CORE        "[       ]"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *******************************************************************************
 *
 *   \brief Global timer data structure.
 *
 *            This holds the handle to clock started.
 *
 *******************************************************************************
*/
typedef struct
{
    /**<  Periodic Clock object */
    BspOsal_ClockHandle clkHandle;
    /**<  Periodic Clock object handle */
    uint32_t oldClk32KhzValue;
    /**< Last value of CLK 32Khz timer to check overflow */
    uint32_t clk32KhzOverflow;
    /**< CLK 32Khz overflow count */
} Utils_GlobalTimerObj;

/**
 *******************************************************************************
 *  \brief Clock ID to be used with Utils_getClkHz()
 *******************************************************************************
 */
typedef enum {

    UTILS_CLK_ID_EVE,
    /**< EVE CPU ID */

    UTILS_CLK_ID_DSP,
    /**< DSP CPU ID */

    UTILS_CLK_ID_IPU,
    /**< IPU CPU ID */

    UTILS_CLK_ID_A15,
    /**< A15 CPU ID */

    UTILS_CLK_ID_MAX
    /**< Max clock ID */

} Utils_ClkId;

/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
static void Utils_globalTimerPrdFunc(uint32_t arg);

/**
 *******************************************************************************
 *
 *   \brief Global timer object
 *
 *          This holds the timer handle. This is for local processor.
 *
 *******************************************************************************
*/
Utils_GlobalTimerObj gUtils_GlobalTimerObj = { 0 };

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void mainTimerTick(UArg arg);
void loadCoreTask(UArg arg0, UArg arg1);
void Utils_idlePrepare(void);
int32_t Utils_globalTimerInit(void);
uint64_t Utils_getCurGlobalTimeInUsec(void);
uint64_t Utils_getCurGlobalTimeInMsec(void);
uint32_t Utils_getClkHz(Utils_ClkId clkId);
int32_t Utils_setCpuFrequency (uint32_t freq);
void printToUart(const char *pStr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32_t numRun = 0U;
static BspOsal_SemHandle gSem;
static volatile uint32_t semaphoreInit = 0U;
volatile uint32_t numIterationsToRun = 0U;
volatile uint32_t cpuLoadReq = 0U;
volatile uint32_t stopRun = 0U;

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined (__ti__)
#pragma DATA_ALIGN(gLoadAppTskStackMain, 32)
#pragma DATA_SECTION(gLoadAppTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static UInt8           gLoadAppTskStackMain[10U * 1024U]
#if defined(__GNUC__) && !defined(__ti__)
__attribute__ ((aligned (32)))
__attribute__ ((section (".bss:taskStackSection")))
#endif
;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    Task_Handle task;
    Task_Params tskPrms;
    Error_Block eb;
    int32_t retVal = 0;
    Error_init(&eb);
    uint32_t clkHz;
    UInt32                  tempFuncPtr;
    BspOsal_InitParams_t    bspOsalInitPrms = {0};
    AppUtils_defaultInit();
    BspUtils_prfInit();
    tempFuncPtr = (UInt32) &printToUart;
    bspOsalInitPrms.printFxn = (BspOsal_PrintFxn) (tempFuncPtr);
    BspOsal_Init(&bspOsalInitPrms);
#if defined (BUILD_A15_0)
    clkHz = Utils_getClkHz(UTILS_CLK_ID_A15);
#elif defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1) || \
      defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    clkHz = Utils_getClkHz(UTILS_CLK_ID_IPU);
#elif defined (_TMS320C6600)
    clkHz = Utils_getClkHz(UTILS_CLK_ID_DSP);
#else
    clkHz = Utils_getClkHz(UTILS_CLK_ID_EVE);
    IntXbar_connectIRQ(5, 32);
    IntXbar_connectIRQ(6, 33);
    IntXbar_connectIRQ(7, 34);
#endif
    AppUtils_printf(APP_CORE "--------------Core Loading Software------------\n");
    Utils_idlePrepare();
    Utils_globalTimerInit();
    Utils_setCpuFrequency(clkHz);
    numRun = 0U;
    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = 10U;
    tskPrms.stack         = gLoadAppTskStackMain;
    tskPrms.stackSize     = sizeof (gLoadAppTskStackMain);
    tskPrms.arg0          = (UArg) NULL;
    task = Task_create(loadCoreTask, &tskPrms, &eb);
    /* Register the task to the load module for calculating the load */
    BspUtils_prfLoadRegister(task, "CORE LOADING");
    
    if (task == NULL)
    {
        AppUtils_printf(APP_CORE "Task_create() CpuIdleTest failed!\n");
        BIOS_exit(0);
    }
    gSem = BspOsal_semCreate(0, TRUE);
    semaphoreInit = 1U;
    /* Start BIOS */
    BIOS_start();

    return retVal;
}

void loadCoreTask(UArg arg0, UArg arg1)
{
    volatile uint32_t loopForever = 1U;
    uint32_t i = 0U;
    volatile uint64_t startTime = 0, endTime = 0,
                      timeTaken = (uint64_t)330 * (uint64_t)REQUIRED_CPU_LOAD_IN_PERCENT;
    /* Start the load calculation */
    BspUtils_prfLoadCalcStart();
    cpuLoadReq = REQUIRED_CPU_LOAD_IN_PERCENT;
#if defined (BUILD_ARP32_1) || defined (BUILD_ARP32_2) ||\
    defined (BUILD_ARP32_3) || defined (BUILD_ARP32_4)
    {
        void fft_init();
        fft_init();
    }
#endif
    while (loopForever)
    {
        numIterationsToRun = (uint32_t)(((uint64_t)33000 * (uint64_t)cpuLoadReq)/
                         ((uint64_t)timeTaken * (uint64_t)100));
        if ((numIterationsToRun == 0) || (numIterationsToRun > 100000))
        {
            numIterationsToRun = 1;
        }
        BspOsal_semWait(gSem, BSP_OSAL_WAIT_FOREVER);
        startTime = Utils_getCurGlobalTimeInUsec();
        for (i = 0U; i < numIterationsToRun; i++)
        {
#if defined (_TMS320C6600) ||\
    defined (BUILD_ARP32_1) || defined (BUILD_ARP32_2) ||\
    defined (BUILD_ARP32_3) || defined (BUILD_ARP32_4)
            void runLoad(void);
            runLoad();
            numRun++;
#else
            runDhrystone();
            numRun++;
#endif
        }
        endTime = Utils_getCurGlobalTimeInUsec();
        timeTaken = (endTime - startTime)/numIterationsToRun;
        if (numRun > 3000000/timeTaken)
        {
            uint32_t key;
            AppUtils_printf(APP_CORE "Load Kernel Time Taken = %d\n", (uint32_t)timeTaken);
            /* Print the load */
            BspUtils_prfLoadPrintAll(TRUE);
            key = Hwi_disable();
            BspUtils_prfLoadCalcStop();
            BspUtils_prfLoadCalcReset();
            BspUtils_prfLoadCalcStart();
            Hwi_restore(key);
            numRun = 0U;
        }
    }
}

void Utils_idlePrepare(void)
{
    int32_t status = (int32_t) PM_SUCCESS;
    pmhalPrcmModuleId_t moduleId;
#if defined (BUILD_A15_0)
    pmhalMpuPowerStatusParams_t mpuPowerState;
    moduleId = PMHAL_PRCM_MOD_MPU;
#elif defined (BUILD_IPU1)
    moduleId = PMHAL_PRCM_MOD_IPU1;
#elif defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    moduleId = PMHAL_PRCM_MOD_IPU2;
#elif defined (BUILD_DSP_1)
    moduleId = PMHAL_PRCM_MOD_DSP1;
#elif defined (BUILD_DSP_2)
    moduleId = PMHAL_PRCM_MOD_DSP2;
#elif defined (BUILD_ARP32_1)
    moduleId = PMHAL_PRCM_MOD_EVE1;
#elif defined (BUILD_ARP32_2)
    moduleId = PMHAL_PRCM_MOD_EVE2;
#elif defined (BUILD_ARP32_3)
    moduleId = PMHAL_PRCM_MOD_EVE3;
#elif defined (BUILD_ARP32_4)
    moduleId = PMHAL_PRCM_MOD_EVE4;
#else
    /* Default */
    moduleId = PMHAL_PRCM_MOD_COUNT;
#endif

    status = PMLIBCpuModePrepare(moduleId,PMLIB_IDLE_CPU_MODE_AUTOCG);
    if (status == PM_SUCCESS)
    {
#if defined (BUILD_A15_0)
        MPU_WUGEN_Init();

        PMHALMpuLprmGetPowerStatus((uint32_t)1u, &mpuPowerState);
        if (PMHAL_PRCM_PD_STATE_ON_ACTIVE == mpuPowerState.currPowerStatus)
        {
            PMLIBCpu1ForcedOff();
        }
#elif defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1) || \
      defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
        IPU_WUGEN_Init();
#elif defined (_TMS320C6600)
        DSP_WUGEN_IRQ_Init();
#else
        ARP32_WUGEN_IRQ_Init();
#endif
    }
}

void Utils_idleFxn(void)
{
    uint32_t key;

    key = Hwi_disable();
#if defined (BUILD_A15_0)
    MPU_WUGEN_0_Interrupt_Lookup();
#elif defined (BUILD_IPU1_0) || defined (BUILD_IPU1_1) || \
      defined (BUILD_IPU2_0) || defined (BUILD_IPU2_1)
    IPU_WUGEN_Interrupt_Lookup();
#elif defined (_TMS320C6600)
    DSP_WUGEN_IRQ_Interrupt_Lookup();
#else
    ARP32_WUGEN_IRQ_Interrupt_Lookup();
#endif
    Hwi_restore(key);

    /* Enter low power */
    PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
}

void mainTimerTick(UArg arg)
{
    Clock_tick();
}

void triggerRun (UArg arg)
{
    if ((semaphoreInit == 1U) && (stopRun == 0U))
    {
        BspOsal_semPost(gSem);
    }
}

/**
 *******************************************************************************
 *
 * \brief Initializes the global timer for 1ms period.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
int32_t Utils_globalTimerInit(void)
{
    Utils_GlobalTimerObj *pClkObj;
    int32_t retVal;
    
    pClkObj = &gUtils_GlobalTimerObj;
    
    pClkObj->clkHandle = BspOsal_clockCreate(
                            &Utils_globalTimerPrdFunc,
                            COUNTER_32K_OVERFLOW_CHECK_TIMER_PERIOD_IN_MS,
                            (Bool)FALSE,
                            pClkObj
                            );
    if (pClkObj->clkHandle == NULL)
    {
        AppUtils_printf(APP_CORE "clock create failed\n");
        retVal = PM_FAIL;
    }
    else
    {
        BspOsal_clockStart(pClkObj->clkHandle);
        retVal = PM_SUCCESS;
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief Get current Global time across all cores
 *        Its important to have a global time across all cores to identify
 *        certain things like latency/delay etc. All link should use this
 *        function to insert timestamp or calculate latency/delay etc.
 *
 * \return current Global time in units of micro sec's
 *
 *******************************************************************************
 */
uint64_t Utils_getCurGlobalTimeInMsec(void)
{
    return Utils_getCurGlobalTimeInUsec()/1000U;
}

/**
 *******************************************************************************
 *
 * \brief Get current Global time across all cores
 *        Its important to have a global time across all cores to identify
 *        certain things like latency/delay etc. All link should use this
 *        function to insert timestamp or calculate latency/delay etc.
 *
 * \return current Global time in units of micro sec's
 *
 *******************************************************************************
 */
uint64_t Utils_getCurGlobalTimeInUsec(void)
{
    uint64_t curGblTime;
    uint32_t oldIntState;
    uint64_t clk32KhzValue;
    uint64_t clk32KhzValue64;
    uint64_t temp; /* Using uint64_t datatype as uint64_t datatype causes
                      MisraC issue while performing shift operation*/

    oldIntState = Hwi_disable();

    clk32KhzValue = COUNTER_32K_CR;

    if(clk32KhzValue < gUtils_GlobalTimerObj.oldClk32KhzValue)
    {
        gUtils_GlobalTimerObj.clk32KhzOverflow++;
    }

    temp = (uint64_t)gUtils_GlobalTimerObj.clk32KhzOverflow &
        0xFFFFFFFFU;
    temp  = temp << 32U;
    clk32KhzValue64  = (uint64_t)clk32KhzValue | temp;

    curGblTime = (1000000U*clk32KhzValue64)/COUNTER_32K_CR_REF_CLK;

    gUtils_GlobalTimerObj.oldClk32KhzValue = clk32KhzValue;

    Hwi_restore(oldIntState);

    return (curGblTime);
}

Void Utils_getGlobalTimeCounterValue(uint32_t *valueH, uint32_t *valueL)
{
    uint32_t oldIntState;

    oldIntState = Hwi_disable();

    Utils_getCurGlobalTimeInUsec();

    *valueL = gUtils_GlobalTimerObj.oldClk32KhzValue;
    *valueH = gUtils_GlobalTimerObj.clk32KhzOverflow;

    Hwi_restore(oldIntState);
}

static void Utils_globalTimerPrdFunc(uint32_t arg)
{
    Utils_getCurGlobalTimeInUsec();
}

uint32_t Utils_getClkHz(Utils_ClkId clkId)
{
    uint32_t clkHz = 0;
    pmErrCode_t status = PM_FAIL;

    /**
     * \brief Holds the root clock frequencies specific for a given platform
     */
    uint32_t *rootClkFreqList;

    /**
     * \brief Holds the voltage domains information whose rails are shared
     */
    pmlibBoardVdRailShare_t *vdRailShareList;

    rootClkFreqList = PMLIBBoardConfigGetRootClks();
    vdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    status = PMLIBClkRateInit(rootClkFreqList,vdRailShareList);

    if (PM_SUCCESS == status)
    {
        switch(clkId)
        {
#if defined (TDA2XX_BUILD) || defined (TDA2PX_BUILD) || defined (TDA3XX_BUILD)
            case UTILS_CLK_ID_EVE:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_EVE1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
#endif
            case UTILS_CLK_ID_DSP:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_DSP1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
            case UTILS_CLK_ID_IPU:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_IPU1, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
#if defined (TDA2XX_BUILD) || defined (TDA2PX_BUILD) || defined (TDA2EX_BUILD)
            case UTILS_CLK_ID_A15:
                status = PMLIBClkRateGet(PMHAL_PRCM_MOD_MPU, PMHAL_PRCM_CLK_GENERIC, &clkHz);
                break;
#endif
            default:
                status = PM_FAIL;
                break;
        }
    }
    if (PM_SUCCESS != status)
    {
        clkHz = 0U;
    }
    return clkHz;
}

int32_t Utils_setCpuFrequency (uint32_t freq)
{
    UInt cookie;
    Types_FreqHz cpuHz;
    Types_FreqHz oldCpuHz;

    BIOS_getCpuFreq(&oldCpuHz);

    cookie = Hwi_disable();
    cpuHz.lo = freq;
    cpuHz.hi = 0;
    ti_sysbios_BIOS_setCpuFreq(&cpuHz);
    Clock_tickStop();
    Clock_tickReconfig();
    Clock_tickStart();
    Hwi_restore(cookie);

    BIOS_getCpuFreq(&cpuHz);

    return PM_SUCCESS;
}

void printToUart(const char *pStr)
{
    UARTPuts(pStr, strlen(pStr));
}
