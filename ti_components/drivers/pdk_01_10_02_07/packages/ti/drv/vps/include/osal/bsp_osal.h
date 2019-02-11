/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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

/**
 *  \file bsp_osal.h
 *
 *  \brief BSP OS abstraction layer header file.
 *
 */
#ifndef BSP_OSAL_H_
#define BSP_OSAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Wait forever */
#define BSP_OSAL_WAIT_FOREVER           (0xFFFFFFFFU)
/** \brief No wait */
#define BSP_OSAL_NO_WAIT                (0x00000000U)

/* Lists of bitmask cache types */
/**
 * \name Lists of bitmask cache types
 *  @{
 */
/** \brief Cache Type is L1I (or L1P) */
#define BSP_OSAL_CT_L1P                 (0x1U)
/** \brief Cache Type is L1D */
#define BSP_OSAL_CT_L1D                 (0x2U)
/** \brief Cache Type is L1 */
#define BSP_OSAL_CT_L1                  (BSP_OSAL_CT_L1P | BSP_OSAL_CT_L1D)
/** \brief Cache Type is L2I (or L2P) */
#define BSP_OSAL_CT_L2P                 (0x4U)
/** \brief Cache Type is L2D */
#define BSP_OSAL_CT_L2D                 (0x8U)
/** \brief Cache Type is L2 */
#define BSP_OSAL_CT_L2                  (BSP_OSAL_CT_L2P | BSP_OSAL_CT_L2D)
/** \brief Cache Type is ALLI (or ALLP) */
#define BSP_OSAL_CT_ALLP                (BSP_OSAL_CT_L1P | BSP_OSAL_CT_L2P)
/** \brief Cache Type is ALLD */
#define BSP_OSAL_CT_ALLD                (BSP_OSAL_CT_L1D | BSP_OSAL_CT_L2D)
/** \brief Cache Type is ALL */
#define BSP_OSAL_CT_ALL                 (0x7FFFU)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/** \brief Semaphore handler datatye */
typedef void *BspOsal_SemHandle;
/** \brief Task handler datatye */
typedef void *BspOsal_TaskHandle;
/** \brief Clock handler datatye */
typedef void *BspOsal_ClockHandle;
/** \brief Interrupt handler datatye */
typedef void *BspOsal_IntrHandle;

/** \brief Pointer to the function of newly created task */
typedef void (*BspOsal_TaskFuncPtr)(UInt32 arg0, UInt32 arg1);
/** \brief Pointer to the timer function used for system tic */
typedef void (*BspOsal_ClockFuncPtr)(UInt32 arg0);
/** \brief Pointer to the interrupt hnadler */
typedef void (*BspOsal_IntrFuncPtr)(UInt32 arg0);
/** \brief Pointer to the print function used for logs */
typedef void (*BspOsal_PrintFxn)(const char *pBuffer);

/**
 *  \brief This structure holds static memory status parameters of BSP OSAL
 *         library
 */
typedef struct BspOsal_StaticMemoryStatus
{
    UInt32 peakSemObjs;
    /**< Peak Sem Objects */
    UInt32 numMaxSemObjs;
    /**< Max  Sem Objects */
    UInt32 numFreeSemObjs;
    /**< Free Sem Objects */

    UInt32 peakTaskObjs;
    /**< Peak Task Objects */
    UInt32 numMaxTaskObjs;
    /**< Max  Task Objects */
    UInt32 numFreeTaskObjs;
    /**< Free Task Objects */

    UInt32 peakClockObjs;
    /**< Peak clock Objects */
    UInt32 numMaxClockObjs;
    /**< Max  clock Objects */
    UInt32 numFreeClockObjs;
    /**< Free clock Objects */

    UInt32 peakHwiObjs;
    /**< Peak Hwi Objects */
    UInt32 numMaxHwiObjs;
    /**< Max  Hwi Objects */
    UInt32 numFreeHwiObjs;
    /**< Free Hwi Objects */
} BspOsal_StaticMemStatus;

/**
 *  \brief This structure holds initilization parameters passed to
 *         #BspOsal_Init function.
 */
typedef struct BspOsal_InitParams
{
    BspOsal_PrintFxn printFxn;
    /**< SBL Lib Print Function */
}BspOsal_InitParams_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief     Dummy print function
 *
 * \param     buff Pointer to buffer for printing
 *
 * \return    None
 *
 */
static inline void Empty_printf(void *buff);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
/**
 * \brief     This API is used to initilize BSP OSAL parameters
 *
 * \param     bspOsalInitPrms Pointer ti strucure #BspOsal_InitParams_t
 *                            containing initilization parameters.
 *
 * \return    None
 *
 */
extern void BspOsal_Init(const BspOsal_InitParams_t *bspOsalInitPrms);
/**
 * \brief     This API is used to De-initilize BSP OSAL parameters
 *
 * \return    None
 *
 */
extern void BspOsal_Deinit(void);
/**
 * \brief     BSP OSAL API to print the logs and data
 *
 * \param     format  Format string to be printed
 *
 * \return    BSP_SOK in case of success -ve otherwise
 *
 */
extern Int32 BspOsal_printf(const Char *format, ...);
/**
 * \brief     BSP OSAL API to read the user input data
 *
 * \param     format  Format string to be read
 *
 * \return    BSP_SOK in case of success -ve otherwise
 *
 */
extern Int32 BspOsal_scanf(const Char *format, ...);

/**
 * \brief     BSP OSAL API to create a new task
 *
 * \param     fxn          new task function handler
 * \param     tskName      task function name
 * \param     priority     priority of new task
 * \param     stack        pointer ti memory used for stack
 * \param     stackSize    stack size to be allocated to the function
 * \param     arg0         pointer to the argument passed to the function
 * \param     tskAffinity  task affinity
 *
 * \return    task handler #BspOsal_TaskHandle, NULL otherwise
 *
 */
extern BspOsal_TaskHandle BspOsal_taskCreate(
    BspOsal_TaskFuncPtr fxn,
    char               *tskName,
    Int32               priority,
    void               *stack,
    UInt32              stackSize,
    const void         *arg0,
    UInt32              tskAffinity
    );

/**
 * \brief  BSP OSAL API to delete a task
 *
 * \param  pTskHandle  Pointer to the task handler to be deleted
 *
 */
extern void BspOsal_taskDelete(BspOsal_TaskHandle *pTskHandle);

/**
 *  \brief Returns the stack used in bytes by the task represented by the
 *         handle passed. If the handle is NULL, it uses the current task
 *         context from which this function is called.
 *
 * \param  tskHandle  Pointer to the task handler
 *
 * \return Task stack usage
 *
 * \note This can't be called from HWI/SWI context.
 */
extern UInt32 BspOsal_getTaskStackUsage(BspOsal_TaskHandle tskHandle);

/**
 *  \brief Returns the system stack used in bytes by interrupts.
 *
 * \return System stack usage
 *
 *  Note: This can't be called from HWI/SWI context.
 */
extern UInt32 BspOsal_getSystemStackUsage(void);

/**
 *  \brief API to get task self handler
 *
 * \return Self task handler #BspOsal_TaskHandle
 *
 *  Note: This can't be called from HWI/SWI context.
 */
extern BspOsal_TaskHandle BspOsal_taskGetSelfHandle(void);

/**
 *  \brief API to get task priority.
 *
 * \param  taskHandle  Pointer to the task handler
 */
extern Int32 BspOsal_taskGetPri(BspOsal_TaskHandle taskHandle);

/**
 *  \brief API to set task priority.
 *
 * \param  taskHandle  Pointer to the task handler
 * \param  newPri     Task's newe priority
 */
extern void BspOsal_taskSetPri(BspOsal_TaskHandle taskHandle, Int32 newPri);

/**
 *  \brief API to create new semaphore
 *
 * \param  initValue  Semaphore init value
 * \param  isBinary   TRUE for binary semaphore, FASLE otherwise
 *
 * \return Semaphore handler
 */
extern BspOsal_SemHandle BspOsal_semCreate(Int32 initValue, Bool isBinary);

/**
 *  \brief API to create a semaphore
 *
 * \param  pSemHandle  Semaphore handler to be deleted
 */
extern void BspOsal_semDelete(BspOsal_SemHandle *pSemHandle);

/**
 *  \brief API to wait for a semaphore
 *
 * \param  semHandle  Semaphore halder
 * \param  timeOut    Timeout value
 *
 * \return TRUE in case of success, FALSE for timeOut
 */
extern Bool BspOsal_semWait(BspOsal_SemHandle semHandle, UInt32 timeOut);

/**
 *  \brief API to post a semaphore
 *
 * \param  semHandle  Semaphore handler
 */
extern void BspOsal_semPost(BspOsal_SemHandle semHandle);

/**
 *  \brief API to create OS clock
 *
 * \param  fxn       Function handler for OS clock tick
 * \param  period    OS clock period
 * \param  startFlag OS clock start flag
 * \param  arg0      OS clock function argument
 *
 * \return Created OS clock handler #BspOsal_ClockHandle
 */
extern BspOsal_ClockHandle BspOsal_clockCreate(
    BspOsal_ClockFuncPtr fxn,
    UInt32               period,
    Bool                 startFlag,
    const void          *arg0);

/**
 *  \brief API to delete the OS clock
 *
 * \param  pClkHandle  Pointer to clock handler #BspOsal_ClockHandle
 */
extern void BspOsal_clockDelete(BspOsal_ClockHandle *pClkHandle);

/**
 *  \brief API to start the OS clock
 *
 * \param  clkHandle  Clock handler #BspOsal_ClockHandle
 */
extern void BspOsal_clockStart(BspOsal_ClockHandle clkHandle);

/**
 *  \brief API to stop the OS clock
 *
 * \param  clkHandle  Clock handler #BspOsal_ClockHandle
 */
extern void BspOsal_clockStop(BspOsal_ClockHandle clkHandle);

/**
 *  \brief API to get the OS clock ticks
 *
 * \return Number of clock ticks
 */
extern UInt32 BspOsal_getClockTicks(void);

/**
 *  \brief API to register interrupt handler
 *
 * \param  intNum  Registered interrupt number
 * \param  fxn     Function handler to be registered for the interrupt
 * \param  arg0    Handler function argument
 *
 * \return Registered interrupt handler #BspOsal_IntrHandle
 */
extern BspOsal_IntrHandle BspOsal_registerIntr(
    UInt32              intNum,
    BspOsal_IntrFuncPtr fxn,
    void               *arg0);

/**
 *  \brief API to unregister the interrupt
 *
 * \param  pIntrHandle  Interrupt hnadler to be unregistered #BspOsal_IntrHandle
 */
extern void BspOsal_unRegisterIntr(BspOsal_IntrHandle *pIntrHandle);
/**
 *  \brief API to clear the interrupt
 *
 * \param  intNum  Interrupt to be cleared
 */
extern void BspOsal_clearIntr(UInt32 intNum);
/**
 *  \brief API to diable the interrupt
 *
 * \return Disable interrupt status
 */
extern UInt32 BspOsal_disableInterrupt(void);
/**
 *  \brief API to restore the interrupt
 *
 * \param  cookie
 */
extern void BspOsal_restoreInterrupt(UInt32 cookie);

/**
 *  \brief      Connect the XBAR instance associated with an interrupt.
 *  \details    Dynamically connects the XBAR instance associated with an
 *              interrupt on the current core to the selected interrupt source.
 *
 *  \param  xbarInstance    XBAR instance number
 *                          (1-8)   For EVE Cores
 *                          (1-64)  For DSP Cores
 *                          (1-57)  For M4 Cores
 *                          (1-152) For A15 Cores
 *  \param  intSource       IRQ crossbar input index
 *
 *  \return None
 */
extern void BspOsal_irqXbarConnect(UInt32 xbarInstance,
                                   UInt32 intSource);
/**
 *  \brief      Disconnect the XBAR instance associated with an interrupt.
 *  \details    Dynamically disconnects the XBAR instance associated with
 *              an interrupt on the current core by clearing the interrupt
 *              source index.
 *
 *  \param  xbarInstance    XBAR instance number
 *                          (1-8)   For EVE Cores
 *                          (1-64)  For DSP Cores
 *                          (1-57)  For M4 Cores
 *                          (1-152) For A15 Cores
 *
 *  \return None
 */
extern void BspOsal_irqXbarDisconnect(UInt32 xbarInstance);

/**
 *  \brief      Make a XBAR connection for the given IRQ number
 *  \details    Dynamically connects the XBAR instance associated with the
 *              given IRQ number on the current core to the selected interrupt
 *              source. Please note that IRQ number is same as Event Id
 *              on C66 DSP.
 *
 *  \param  cpuIrqNum       CPU's IRQ number
 *  \param  intSource       IRQ crossbar input index
 *
 *  \return None
 */
extern void BspOsal_irqXbarConnectIrq(UInt32 cpuIrqNum, UInt32 intSource);

/**
 *  \brief      Disconnect the XBAR connection associated with the given
 *              IRQ number
 *  \details    Dynamically disconnects the XBAR instance associated with the
 *              given IRQ number on the current core by clearing the interrupt
 *              source index. Please note that IRQ number is same as Event Id
 *              on C66 DSP.
 *
 *  \param  cpuIrqNum       CPU's IRQ number
 *
 *  \return None
 */
extern void BspOsal_irqXbarDisconnectIrq(UInt32 cpuIrqNum);

/**
 *  \brief API to put task to sleep for passed milli seconds
 *
 * \param  delayMsec  Sleep delay in milli seconds
 */
extern void BspOsal_sleep(UInt32 delayMsec);

/**
 *  \brief API to get the OS timestamp
 *
 * \return timestamp value
 */
extern UInt64 BspOsal_getTimestamp64(void);

/**
 *  \brief API to Time stamp frequency
 *
 * \return Timestamp frequency
 */
extern UInt64 BspOsal_getTimestampFreq(void);

/**
 *  \brief API to get current OS time in milli seconds
 *
 * \return OS time in milli seconds
 */
extern UInt32 BspOsal_getCurTimeInMsec(void);

/**
 *  \brief API to get current OS time in micro seconds
 *
 * \return OS time in micro seconds
 */
extern UInt64 BspOsal_getCurTimeInUsec(void);

/**
 *  \brief API to get static memory status
 *
 * \param  pMemStat  Pointer to structure to store static memory status
 *                   #BspOsal_StaticMemStatus
 *
 * \return BSP_SOK in case of success, -ve otherwise
 */
Int32 BspOsal_getStaticMemStatus(BspOsal_StaticMemStatus *pMemStat);

static inline void Empty_printf(void *buff)
{
    return;
}

/**
 *  \brief API to diable the cache
 *
 * \param  type  cache type
 */
void BspOsal_cacheDisable(UInt32 type);

/**
 *  \brief API to enable the cache
 *
 * \param  type  cache type
 */
void BspOsal_cacheEnable(UInt32 type);

/**
 *  \brief API to invalidate a block of cache
 *
 * \param  blockPtr  Block pointer to be invalidated
 * \param  byteCnt   byte count to be invalidated
 * \param  type      cahe type
 * \param  timeOut   timeout value
 */
void BspOsal_cacheInv(void *blockPtr, UInt32 byteCnt, UInt32 type,
                      UInt32 timeOut);

/**
 *  \brief API to writeback the cache module
 *
 * \param  blockPtr  Block pointer to be invalidated
 * \param  byteCnt   byte count to be invalidated
 * \param  type      cahe type
 * \param  timeOut   timeout value
 */
void BspOsal_cacheWb(void *blockPtr, UInt32 byteCnt, UInt32 type,
                     UInt32 timeOut);

/**
 *  \brief API to writeback the complete cache
 */
void BspOsal_cacheWbAll(void);

/**
 *  \brief API to Invalidate the complete cache
 */
void BspOsal_cacheInvAll(void);

/**
 *  \brief API to invalidate the write back for cache module
 *
 * \param  blockPtr  Block pointer to be invalidated
 * \param  byteCnt   byte count to be invalidated
 * \param  type      cahe type
 * \param  timeOut   timeout value
 */
void BspOsal_cacheWbInv(void *blockPtr, UInt32 byteCnt, UInt32 type,
                        UInt32 timeOut);

/**
 *  \brief API to invalidate the write back for complete cache
 */
void BspOsal_cacheWbInvAll(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_OSAL_H_ */
