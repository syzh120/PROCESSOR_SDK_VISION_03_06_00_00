/*
 *   Copyright (c) Texas Instruments Incorporated 2016-2017
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

/*
 * main.c
 */

 #include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/ipc_lite/ipclib_interrupt.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/csl_spinlock.h>
#include <ti/csl/csl_wd_timer.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/******************************************************************************
 *                  Macros
 *****************************************************************************/
#define  COMMON_LOCAL_EVENT_ID  (5U)
#define  NUM_ITERATIONS         (10000U)

#if defined (SOC_TDA2XX)
#define  NUM_VALID_PROCS        (10U)
#elif defined (SOC_TDA2PX)
#define  NUM_VALID_PROCS        (8U)
#elif defined (SOC_TDA3XX)
#define  NUM_VALID_PROCS        (5U)
#elif defined (SOC_TDA2EX)
#define  NUM_VALID_PROCS        (5U)
#endif

#define  SPINLOCK_ID            (40U)

/******************************************************************************
 *                  Globals
 *****************************************************************************/

static char     gSelfProcName[10];
static char     gRemoteProcName[10];
static volatile uint32_t gSem = 0;
static uint32_t gRecvedPayload[IPCLIB_MAX_PROC][NUM_ITERATIONS];

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void UARTmulticorePrintf(const char *pcString, ...);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t interruptCallback(uint32_t remoteProcId, uint32_t eventId,
                          uint32_t payload,
                          void *arg,
                          int32_t status)
{
    uint32_t iteration = 0U;
    if (status == IPCLIB_SOK)
    {
        gSem++;

        iteration = payload & 0x0000FFFF;
        gRecvedPayload[remoteProcId][iteration] = payload;
    }

    return 0;
}

char *getSelfProcName()
{
    char *name = gSelfProcName;
    IpcLib_interruptGetProcName(name,
                                sizeof (gSelfProcName),
                                IpcLib_interruptGetSelfProcId());
    return name;
}

char *getRemoteProcName(uint32_t id)
{
    char *name = gRemoteProcName;
    IpcLib_interruptGetProcName(name, sizeof (gRemoteProcName), id);
    return name;
}

void multicoreLockAcquire()
{
    uint32_t status     = 1U;
    uint32_t baseAddr   = SOC_SPINLOCK_BASE;
    uint32_t spinLockId = SPINLOCK_ID;

    while (0U != status)
    {
        status = SPINLOCKLockStatusSet(baseAddr, spinLockId);
    }
}

void multicoreLockRelease()
{
    uint32_t baseAddr   = SOC_SPINLOCK_BASE;
    uint32_t spinLockId = SPINLOCK_ID;

    SPINLOCKLockStatusFree(baseAddr, spinLockId);
}

void UARTmulticorePrintf(const char *pcString, ...)
{
#if defined (ENABLE_MULTICORE_PRINTS)
    va_list args;
    multicoreLockAcquire();

    va_start(args, pcString);
    UARTConfigvPrintf(uartBaseAddr,pcString, args);
    va_end(args);

    multicoreLockRelease();
#endif
}

void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

#if defined (BUILD_IPU1_0) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX))
void validateErrorReturn()
{
    int32_t  status;

    status =
        IpcLib_interruptRegisterEvent(
            IPCLIB_MAX_PROC,
            IPCLIB_MAX_EVENTS,
            (IpcLib_InterruptCallback) (&interruptCallback),
            NULL);
    if (status != IPCLIB_SOK)
    {
        multicoreLockAcquire();
        UARTConfigPrintf(uartBaseAddr,
            "\r\nIPC app - Error retucn check for Resister event Sucessfull!!\r\n");
        multicoreLockRelease();
    }

    status = IpcLib_interruptSendEvent(
                    IPCLIB_MAX_PROC,
                    IPCLIB_MAX_EVENTS,
                    (16U),
                    TRUE);
    if (status != IPCLIB_SOK)
    {
        multicoreLockAcquire();
        UARTConfigPrintf(uartBaseAddr,
            "IPC app - Error retucn check for Send event Sucessfull!!\r\n");
        multicoreLockRelease();
    }


    status = IpcLib_interruptUnregisterEvent(
            IPCLIB_MAX_PROC,
            IPCLIB_MAX_EVENTS);
    if (status != IPCLIB_SOK)
    {
        multicoreLockAcquire();
        UARTConfigPrintf(uartBaseAddr,
            "IPC app - Error retucn check for Unresister event Sucessfull!!\r\n");
        multicoreLockRelease();
    }

}
#endif

int main(void) {
    int32_t  status = IPCLIB_SOK;
    IpcLib_InterruptInitPrms initPrm;
    int32_t  i, k;
    uint32_t waitCount = 0U;
    uint32_t selfProcId;


#if defined (BUILD_IPU1_0) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX))
    /* Disable the watchdog timer. The policy for handling WD Timer
     * needs to be defined and implemented appropriately */
    WDTIMERDisable(SOC_WD_TIMER2_BASE);
#endif

    multicoreLockAcquire();

    padConfig_prcmEnable();

    multicoreLockRelease();

    Intc_Init();
    Intc_IntDisable();

    IpcLib_interruptSetDefaultInitPrm(&initPrm);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    initPrm.numValidProcs   = NUM_VALID_PROCS;
    initPrm.validProcIds[0] = IPCLIB_A15_0_ID;
    initPrm.validProcIds[1] = IPCLIB_DSP1_ID;
    initPrm.validProcIds[2] = IPCLIB_IPU1_0_ID;
    initPrm.validProcIds[3] = IPCLIB_IPU2_0_ID;
    initPrm.validProcIds[4] = IPCLIB_DSP2_ID;
    initPrm.validProcIds[5] = IPCLIB_IPU1_1_ID;
    initPrm.validProcIds[6] = IPCLIB_EVE1_ID;
    initPrm.validProcIds[7] = IPCLIB_EVE2_ID;
#if defined (SOC_TDA2XX)
    initPrm.validProcIds[8] = IPCLIB_EVE3_ID;
    initPrm.validProcIds[9] = IPCLIB_EVE4_ID;
#endif
#elif defined (SOC_TDA3XX)
    initPrm.numValidProcs   = NUM_VALID_PROCS;
    initPrm.validProcIds[0] = IPCLIB_DSP1_ID;
    initPrm.validProcIds[1] = IPCLIB_IPU1_0_ID;
    initPrm.validProcIds[2] = IPCLIB_DSP2_ID;
    initPrm.validProcIds[3] = IPCLIB_IPU1_1_ID;
    initPrm.validProcIds[4] = IPCLIB_EVE1_ID;
#elif defined (SOC_TDA2EX)
    initPrm.numValidProcs   = NUM_VALID_PROCS;
    initPrm.validProcIds[0] = IPCLIB_DSP1_ID;
    initPrm.validProcIds[1] = IPCLIB_IPU1_0_ID;
    initPrm.validProcIds[2] = IPCLIB_A15_0_ID;
    initPrm.validProcIds[3] = IPCLIB_IPU1_1_ID;
    initPrm.validProcIds[4] = IPCLIB_IPU2_0_ID;
#endif
    initPrm.msgTimeOut      = 0xFFFF;

    IpcLib_interruptInit(&initPrm);

    selfProcId = IpcLib_interruptGetSelfProcId();

    multicoreLockAcquire();
    UARTConfigPrintf(uartBaseAddr,"\r\n[%s] IPC app - Start \r\n ", getSelfProcName());
    multicoreLockRelease();

#if defined (BUILD_IPU1_0) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX))
    validateErrorReturn();
#endif

    for (i = 0; i < initPrm.numValidProcs; i++)
    {
        if (initPrm.validProcIds[i] != selfProcId)
        {
            status =
                IpcLib_interruptRegisterEvent(
                    initPrm.validProcIds[i],
                    COMMON_LOCAL_EVENT_ID,
                    (IpcLib_InterruptCallback) (&interruptCallback),
                    NULL);
            if (status != IPCLIB_SOK)
            {
                UARTmulticorePrintf(
                    "\r\n[%s] IPC app - Register event failed!! \r\n ",
                    getSelfProcName());
            }
            else
            {
                UARTmulticorePrintf(
                    "\r\n[%s] IPC app - Register event successful \r\n ",
                    getSelfProcName());
            }
        }
    }

    Intc_IntEnable(0);

    if (status == IPCLIB_SOK)
    {
        UARTmulticorePrintf("\r\n[%s] IPC app - Sending interrupt \r\n ",
                            getSelfProcName());

        for(k = 0; k < NUM_ITERATIONS; k++)
        {
            for (i = 0; i < initPrm.numValidProcs; i++)
            {
                if (initPrm.validProcIds[i] != selfProcId)
                {
                    status =
                    IpcLib_interruptSendEvent(
                                        initPrm.validProcIds[i],
                                        COMMON_LOCAL_EVENT_ID,
                                        ((selfProcId) << 16U | 0x80000000U | k),
                                        TRUE);

                    if (status != IPCLIB_SOK)
                    {
                        UARTmulticorePrintf(
                            "\r\n[%s] IPC app - Send event failed!! \r\n ",
                            getSelfProcName());
                    }
                    else
                    {
                        UARTmulticorePrintf(
                         "\r\n[%s] IPC app - Send event to %s successful \r\n ",
                         getSelfProcName(),
                         getRemoteProcName(initPrm.validProcIds[i]));
                    }
                }
            }
        }

        while (gSem < ((NUM_VALID_PROCS - 1U) * NUM_ITERATIONS)) ;

        multicoreLockAcquire();
        UARTConfigPrintf(uartBaseAddr,"\r\n[%s] IPC app - Received payloads ", getSelfProcName());

        for(k = 0; k < NUM_ITERATIONS; k++)
        {
            if((!(k%1000) || k == (NUM_ITERATIONS-1)) && (k !=0))
            {
                for (i = 0; i < initPrm.numValidProcs; i++)
                {
                    if (initPrm.validProcIds[i] != selfProcId)
                    {
                        UARTConfigPrintf(uartBaseAddr,
                            "\r\n[%s] IPC app - last payload in the iteration ="
                            " [0x%x], received %d interrupts from %s ",
                            getSelfProcName(),
                            gRecvedPayload[initPrm.validProcIds[i]][k],
                            k,
                            getRemoteProcName(initPrm.validProcIds[i])
                            );
                    }
                }
            }
        }
        UARTConfigPrintf(uartBaseAddr,"\r\n");
        multicoreLockRelease();

        for (i = 0; i < initPrm.numValidProcs; i++)
        {
            if (initPrm.validProcIds[i] != selfProcId)
            {
                status = IpcLib_interruptUnregisterEvent(
                    initPrm.validProcIds[i],
                    COMMON_LOCAL_EVENT_ID);

                if (status != IPCLIB_SOK)
                {
                    UARTmulticorePrintf(
                        "\r\n[%s] IPC app - Event unregister failed !! \r\n ",
                        getSelfProcName());
                }
                else
                {
                    UARTmulticorePrintf(
                        "\r\n[%s] IPC app - Event unregister successful \r\n ",
                        getSelfProcName());
                }
            }
        }
    }

    IpcLib_interruptDeInit();


    multicoreLockAcquire();
    UARTConfigPrintf(uartBaseAddr,"\r\n[%s] IPC app - End \r\n ", getSelfProcName());
    if (status == IPCLIB_SOK)
    {
        UARTConfigPrintf(uartBaseAddr,"Test Passed\r\n");
    }
    multicoreLockRelease();

    waitCount = 1U;
    while (waitCount) ;

    return 0;
}

