/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file st_mcanCommon.c
 *
 *  \brief Common code that can be shared across test case files.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_mcan.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/csl_mcan.h>
#include <ti/drv/pm/pmlib.h>
#include <st_mcan.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#if defined (SOC_TDA2PX)
    #define APP_MCAN_INT0_M4                                  (78U)
    #define APP_MCAN_INT1_M4                                  (79U)
    #define APP_MCAN_ECC_INT_M4                               (75U)
    #define APP_MCAN_TS_INT_M4                                (72U)
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    #define APP_MCAN_INT0_M4                                  (34U)
    #define APP_MCAN_INT1_M4                                  (35U)
    #define APP_MCAN_ECC_INT_M4                               (36U)
    /* MCAN TS interrupt only goes to IPU 79 Cross bar */
    #define APP_MCAN_TS_INT_M4                                (79U)
#endif

#ifdef __TI_ARM_V7M4__
    #define APP_MCAN_INT0                     (APP_MCAN_INT0_M4)
    #define APP_MCAN_INT1                     (APP_MCAN_INT1_M4)
    #define APP_MCAN_ECC_INT                  (APP_MCAN_ECC_INT_M4)
    #define APP_MCAN_TS_INT                   (APP_MCAN_TS_INT_M4)
    #define XBAR_CPU                          (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_MCAN_INT0                       (CSL_XBAR_INST_IPU1_IRQ_34)
    #define XBAR_MCAN_INT1                       (CSL_XBAR_INST_IPU1_IRQ_35)
    #define XBAR_MCAN_ECC                        (CSL_XBAR_INST_IPU1_IRQ_36)
    #define XBAR_MCAN_TS                         (CSL_XBAR_INST_IPU1_IRQ_79)
    #define XBAR_INTR0_SOURCE                    (CSL_XBAR_MCAN_IRQ_INT0)
    #define XBAR_INTR1_SOURCE                    (CSL_XBAR_MCAN_IRQ_INT1)
    #define XBAR_INTR_ECC_SOURCE                 (CSL_XBAR_MCAN_IRQ_PARITY)
    #define XBAR_INTR_TS_SOURCE                  (CSL_XBAR_MCAN_IRQ_TS)
#elif defined (_TMS320C6X)
#endif

/** brief 32K Timer frequency */
#define APP_32K_TIMER_FREQ        (32000U)
/** brief Overflow count value for 32bit counter */
#define APP_COUNTER_MAX_COUNT     (0xFFFFFFFFU)
/** \brief Offset of DRM SUSPEND_CTRL31 register */
#define DRM_SUSPEND_CTRL31                 (0x27CU)
/** \brief DRM_SUSPEND_CTRL31 is mapped to COUNTER_32K Suspend Output line */
#define DRM_SUSPEND_CTRL_COUNTER_32K       (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL31)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU_C0             (0x3U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock and PAD config for mcan module.
 *
 * \retval  status          configuration status.
 */
int32_t mcanClockEnableandPADConfig(void);

/**
 * \brief   This API is used to introduce error.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \retvsl  status            Run status
 */
int32_t mcanTestFunc(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This API will MCAN Rx Msg.
 *
 * \param   rxMsg           received message object.
 *
 * \retval  none.
 */
void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg);

/**
 * \brief   This API will MCAN Tx Msg.
 *
 * \param   txMsg           message object to be transmitted.
 *
 * \retval  none.
 */
void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg);

/**
 * \brief   This function will configure X-BAR for MCAN interrupts
 *
 * \param   none.
 *
 * \retval  status      configuration status.
 */
int32_t App_mcanXBarConfig(void);

/**
 * \brief   This is Interrupt Service Routine for MCAN interrupt 0.
 *
 * \param   none.
 *
 * \retval  none.
 */
void App_mcanIntr0ISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN interrupt 1.
 *
 * \param   none.
 *
 * \retval  none.
 */
void App_mcanIntr1ISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN ECC interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
void App_mcanECCIntrISR(void *handle);

/**
 * \brief   This is Interrupt Service Routine for MCAN TimeStamp interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
void App_mcanTSIntrISR(void *handle);

/**
 * \brief   This API will index of the current bit timing configuration within
 *          'canFDBitTimings'.
 *
 * \param   rxMsg           received message object.
 *
 * \retval  index           Array index within 'canFDBitTimings'.
 *                          Return 0xFFFFFFFF if not found.
 */
uint32_t App_getBitConfigParamId(const MCAN_BitTimingParams *bitTimings);

/**
 * \brief   This function used to put 32k Counter into free run mode
 *
 * \param   none.
 *
 * \retval  none.
 */
void App_Config32KCounterSuspendState(void);

/**
 * \brief   This function used to insert delays
 *
 * \param   timeout         Delay value in ms.
 *
 * \retval  none.
 */
void App_delayFunc(uint32_t timeout);

/**
 * \brief   This function used to get current time value in clock ticks
 *
 * \param   value           Read COunter value from register.
 *
 * \retval  none.
 */
void App_Get32KCounterValue(uint32_t *value);

/**
 * \brief   This function used to insert delays
 *
 * \param   value           Initial Value.
 * \param   elapsedValue    Number of clock ticks since 'value'.
 *
 * \retval  none.
 */
void App_GetElapsedValue(uint32_t  value,
                                    uint32_t *elapsedValue);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t          mcanBaseAddr = DEF_MCAN_MODULE;
extern uint32_t                uartBaseAddr;
uint32_t          gMcanAppdataSize[16] =
{0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
volatile uint32_t gMcanIsrIntr0Flag = 1U;
volatile uint32_t gMcanIsrIntr1Flag = 1U;
volatile uint32_t gMcanECCIntrFlag = 1U;
volatile uint32_t gMcanIsrIntr0Status = 1U;
volatile uint32_t gMcanIsrIntr1Status = 1U;
volatile uint32_t gMcanExtTSIntrFlag = 1U;
MCAN_ECCErrStatus gMcaneccErr;
extern MCAN_BitTimingParams canFDBitTimings[];
extern uint32_t bitTimingsListSize;
extern volatile uint32_t isrPrintEnable;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t mcanClockEnableandPADConfig(void)
{
    int32_t status = STW_SOK;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    uint32_t siliconRev;
    /* Configure I/O PAD */
    /* PlatformUnlockMMR();*/
    /*Pad configurations - MCAN */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RXD,
                0x0006000C);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_TXD,
                0x0004000C);

    siliconRev = CSL_getSocSiliconRev();
    if (2U > siliconRev)
    {
        UARTConfigPuts(uartBaseAddr, 
            "\r\nMCAN Evm/B2B Loopback is not supported for Tda3xx PG1.0 Silicon",
            -1);
    }
    /* Configure MCAN io clock */
    if (PM_SUCCESS == PMLIBClkRateSet(PMHAL_PRCM_MOD_MCAN,
                                      PMHAL_PRCM_CLK_MCAN_CLK,
                                      80000000U))
    {
        status = STW_SOK;
        UARTConfigPrintf(uartBaseAddr, "MCAN Clock Configuration Successful.\n");
        status = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCAN,
                                          PMHAL_PRCM_MODULE_MODE_ENABLED,
                                          PM_TIMEOUT_INFINITE);

        if (PM_SUCCESS != status)
        {
            UARTConfigPrintf(uartBaseAddr, "Error in MCAN module enable.\n");
            status = STW_EFAIL;
        }
        else
        {
            status = STW_SOK;
        }
    }
    else
    {
        status = STW_EFAIL;
        UARTConfigPrintf(uartBaseAddr, "Error in MCAN Clock Configuration.\n");
    }

#elif defined (SOC_TDA2PX)
    uint32_t                   postDivider;
    /*Pad configurations- UART  */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /*Pad configurations - MCAN */
    /* Configure mcan_tx, mcan_rx pads on dcan1_tx and dcan1_rx pads */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE+CTRL_CORE_CONTROL_SPARE_RW,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN,
        CTRL_CORE_CONTROL_SPARE_RW_SEL_ALT_MCAN_MCAN_DCAN1_PADS);

    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_TX,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_DCAN1_RX,0x00040000);

    /* Enable MCAN clock. */
    HW_WR_FIELD32(SOC_WKUPAON_CM_BASE+CM_WKUPAON_ADC_CLKCTRL,
        CM_WKUPAON_ADC_CLKCTRL_MODULEMODE,
        CM_WKUPAON_ADC_CLKCTRL_MODULEMODE_ENABLE);
    while (CM_WKUPAON_ADC_CLKCTRL_IDLEST_FUNC !=
                HW_RD_FIELD32(SOC_WKUPAON_CM_BASE+CM_WKUPAON_ADC_CLKCTRL,
                CM_WKUPAON_ADC_CLKCTRL_IDLEST))
    {
        /* wait for module to be enabled */
    }
    postDivider = 24U;
    /* Set the postDividers reg */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV,
                  postDivider);
    /* Select the mux value */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_TENABLEDIV,
                  1U);
    /* Select the Toggle sequence 010 */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  0U);
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  1U);
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_LATCH_EN,
                  0U);
    /* Enable the HSDIV post div clock */
    HW_WR_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE+CTRL_CORE_SMA_SW_0,
                  CTRL_CORE_SMA_SW_0_MCAN_CLK_HSDIV_EN,
                  1U);
#endif

    return status;
}

int32_t mcanTestFunc(st_mcanTestcaseParams_t *testParams)
{
    int32_t           status = STW_SOK;

    return status;
}

void App_mcanPrintTxMsg(const MCAN_TxBufElement *txMsg)
{
    uint32_t loopCnt;

    UARTConfigPrintf(uartBaseAddr, "\nMessage ID: 0x%x", txMsg->id);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Remote Transmission Request: 0x%x", txMsg->rtr);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Extended Frame ID(0:11Bit ID/1:29bit ID): 0x%x",
               txMsg->xtd);
    UARTConfigPrintf(uartBaseAddr, 
        "\nMessage Error State Indicator(0:Error Active/1:Error Passive): 0x%x",
        txMsg->esi);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Data Length Code: 0x%x", txMsg->dlc);
    UARTConfigPrintf(uartBaseAddr, "\nMessage BRS: 0x%x", txMsg->brs);
    UARTConfigPrintf(uartBaseAddr, "\nMessage CAN FD format: 0x%x", txMsg->fdf);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Store Tx Events: 0x%x", txMsg->efc);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Marker: 0x%x", txMsg->mm);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Data(byte no:byte data):\n");
    UARTConfigPuts(uartBaseAddr, "{", -1);
    for (loopCnt = 0U; loopCnt < gMcanAppdataSize[txMsg->dlc]; loopCnt++)
    {
        if((loopCnt % 8) == 0U)
        {
            UARTConfigPuts(uartBaseAddr, "\n", -1);
        }
        UARTConfigPrintf(uartBaseAddr, " (%d:0x%x) ", loopCnt, txMsg->data[loopCnt]);
    }
    UARTConfigPuts(uartBaseAddr, "\n}\n", -1);
}

void App_mcanPrintRxMsg(const MCAN_RxBufElement *rxMsg)
{
    uint32_t loopCnt;

    UARTConfigPrintf(uartBaseAddr, "\nMessage ID: 0x%x", rxMsg->id);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Remote Transmission Request: 0x%x", rxMsg->rtr);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Extended Frame ID(0:11Bit ID/1:29bit ID): 0x%x",
               rxMsg->xtd);
    UARTConfigPrintf(uartBaseAddr, 
        "\nMessage Error State Indicator(0:Error Active/1:Error Passive): 0x%x",
        rxMsg->esi);
    UARTConfigPrintf(uartBaseAddr, "\nMessage TimeStamp: 0x%x", rxMsg->rxts);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Data Length Code: 0x%x", rxMsg->dlc);
    UARTConfigPrintf(uartBaseAddr, "\nMessage BRS: 0x%x", rxMsg->brs);
    UARTConfigPrintf(uartBaseAddr, "\nMessage CAN FD format: 0x%x", rxMsg->fdf);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Filter Index: 0x%x", rxMsg->fidx);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Accept Non-matching Frame: 0x%x", rxMsg->anmf);
    UARTConfigPrintf(uartBaseAddr, "\nMessage Data(byte no:byte data):\n");
    UARTConfigPuts(uartBaseAddr, "{", -1);
    for (loopCnt = 0U; loopCnt < gMcanAppdataSize[rxMsg->dlc]; loopCnt++)
    {
        if((loopCnt % 8) == 0U)
        {
            UARTConfigPuts(uartBaseAddr, "\n", -1);
        }
        UARTConfigPrintf(uartBaseAddr, " (%d:0x%x) ", loopCnt, rxMsg->data[loopCnt]);
    }
    UARTConfigPuts(uartBaseAddr, "\n}\n", -1);
}

int32_t App_mcanXBarConfig(void)
{
    int32_t configStatus = STW_SOK;

    Intc_Init();

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /* XBar configuration */
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_INT0, XBAR_INTR0_SOURCE);
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_INT1, XBAR_INTR1_SOURCE);
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_ECC, XBAR_INTR_ECC_SOURCE);
    CSL_xbarIrqConfigure(XBAR_CPU, XBAR_MCAN_TS, XBAR_INTR_TS_SOURCE);
#endif

    /* Enable CPU Interrupts and register ISR */
    Intc_IntEnable(APP_MCAN_INT0_M4);
    Intc_IntRegister(APP_MCAN_INT0_M4,
                     (IntrFuncPtr) App_mcanIntr0ISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_INT0_M4, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_INT0_M4);
    Intc_IntEnable(APP_MCAN_INT1_M4);
    Intc_IntRegister(APP_MCAN_INT1_M4,
                     (IntrFuncPtr) App_mcanIntr1ISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_INT1_M4, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_INT1_M4);
    Intc_IntEnable(APP_MCAN_ECC_INT);
    Intc_IntRegister(APP_MCAN_ECC_INT,
                     (IntrFuncPtr) App_mcanECCIntrISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_ECC_INT, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_ECC_INT);
    Intc_IntEnable(APP_MCAN_TS_INT);
    Intc_IntRegister(APP_MCAN_TS_INT,
                     (IntrFuncPtr) App_mcanTSIntrISR, 0U);
    Intc_IntPrioritySet(APP_MCAN_TS_INT, 1U, 0U);
    Intc_SystemEnable(APP_MCAN_TS_INT);
    if (STW_SOK == configStatus)
    {
        UARTConfigPrintf(uartBaseAddr, "CrossBar Configuration done.\n");
    }
    else
    {
        UARTConfigPrintf(uartBaseAddr, "Error in configuring CrossBar.\n");
    }
    return configStatus;
}

void App_mcanIntr0ISR(void *handle)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(mcanBaseAddr);
    MCAN_clearIntrStatus(mcanBaseAddr, intrStatus);
    gMcanIsrIntr0Status = (intrStatus &
                          (~MCAN_getIntrLineSelectStatus(mcanBaseAddr)));
    if(isrPrintEnable == (uint32_t)TRUE)
    {
        UARTConfigPrintf(uartBaseAddr, "\nInterrupt Status: 0x%x.\n", intrStatus);
    }
    gMcanIsrIntr0Flag = 0U;
}

void App_mcanIntr1ISR(void *handle)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(mcanBaseAddr);
    MCAN_clearIntrStatus(mcanBaseAddr, intrStatus);
    gMcanIsrIntr1Status = (intrStatus &
                          (MCAN_getIntrLineSelectStatus(mcanBaseAddr)));
    if(isrPrintEnable == (uint32_t)TRUE)
    {
        UARTConfigPrintf(uartBaseAddr, "\nInterrupt Status: 0x%x.\n", intrStatus);
    }
    gMcanIsrIntr1Flag = 0U;
}

void App_mcanECCIntrISR(void *handle)
{
    MCAN_ECCErrStatus mcanECCErr;

    MCAN_eccGetErrorStatus(mcanBaseAddr, &gMcaneccErr);
    if (MCAN_eccGetIntrStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC))
    {
        MCAN_eccClearIntrStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
        if(isrPrintEnable == (uint32_t)TRUE)
        {
            UARTConfigPrintf(uartBaseAddr, "ECC SEC interrupt happened.\n");
        }
    }
    if (MCAN_eccGetIntrStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED))
    {
        MCAN_eccClearIntrStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
        if(isrPrintEnable == (uint32_t)TRUE)
        {
            UARTConfigPrintf(uartBaseAddr, "ECC DED interrupt happened.\n");
        }
    }
    if (1U == gMcaneccErr.secErr)
    {
        MCAN_eccClearErrorStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
        MCAN_eccGetErrorStatus(mcanBaseAddr, &mcanECCErr);
        while (mcanECCErr.secErr == 1U)
        {
            MCAN_eccGetErrorStatus(mcanBaseAddr, &mcanECCErr);
        }
        MCAN_eccWriteEOI(mcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    }
    if (1U == gMcaneccErr.dedErr)
    {
        MCAN_eccClearErrorStatus(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
        MCAN_eccGetErrorStatus(mcanBaseAddr, &mcanECCErr);
        while (mcanECCErr.dedErr == 1U)
        {
            MCAN_eccGetErrorStatus(mcanBaseAddr, &mcanECCErr);
        }
        MCAN_eccWriteEOI(mcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    }
    gMcanECCIntrFlag = 0U;
}

void App_mcanTSIntrISR(void *handle)
{
    if(isrPrintEnable == (uint32_t)TRUE)
    {
        if (MCAN_extTSIsIntrEnable(mcanBaseAddr) == (uint32_t)TRUE)
        {
            UARTConfigPrintf(uartBaseAddr, "Time Stamp overflow happened.\n");
            UARTConfigPrintf(uartBaseAddr, "Unserviced Interrupt Count: %d\n", MCAN_extTSGetUnservicedIntrCount(mcanBaseAddr));
        }
    }
    MCAN_extTSClearRawStatus(mcanBaseAddr);
    gMcanExtTSIntrFlag = 0U;
    MCAN_extTSWriteEOI(mcanBaseAddr);
}

uint32_t App_getBitConfigParamId(const MCAN_BitTimingParams *bitTimings)
{
    uint32_t loopCnt;

    for(loopCnt = 0U ; loopCnt < bitTimingsListSize ; loopCnt++)
    {
        if ((canFDBitTimings[loopCnt].nomRatePrescalar == bitTimings->nomRatePrescalar) &&
            (canFDBitTimings[loopCnt].nomTimeSeg1 == bitTimings->nomTimeSeg1) &&
            (canFDBitTimings[loopCnt].nomTimeSeg2 == bitTimings->nomTimeSeg2) &&
            (canFDBitTimings[loopCnt].nomSynchJumpWidth == bitTimings->nomSynchJumpWidth) &&
            (canFDBitTimings[loopCnt].dataRatePrescalar == bitTimings->dataRatePrescalar) &&
            (canFDBitTimings[loopCnt].dataTimeSeg1 == bitTimings->dataTimeSeg1) &&
            (canFDBitTimings[loopCnt].dataTimeSeg2 == bitTimings->dataTimeSeg2) &&
            (canFDBitTimings[loopCnt].dataSynchJumpWidth == bitTimings->dataSynchJumpWidth))
        {
            break;
        }
    }
    if(loopCnt == bitTimingsListSize)
    {
        loopCnt = 0xFFFFFFFFU;
    }

    return loopCnt;
}

void App_Config32KCounterSuspendState(void)
{
#if defined (SOC_TDA3XX) && !(defined (__TI_ARM_V7M4__))
    /* Suspend Input Line : IPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when M4 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_IPU_C0 << 4U) | 0x0U));

#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /* As L3_INSTR is not connected to EVE1_P1 , so we cant able to configure
     * DRM_SUSPEND_CTRL_COUNTER_32K for EVE
     */
#if defined (__TI_ARM_V7M4__) || defined (_TMS320C6X)
    /* Suspend Input Line : MPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when A15 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_IPU_C0 << 4U) | 0x0U));
#endif
#endif
}

void App_Get32KCounterValue(uint32_t *value)
{
    *value = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
}

void App_GetElapsedValue(uint32_t  value,
                                    uint32_t *elapsedValue)
{
    uint32_t currVal;

    currVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (currVal < value)
    {
        /* Counter overflow occured */
        currVal       = (APP_COUNTER_MAX_COUNT - value) + currVal + 1U;
        *elapsedValue = currVal;
    }
    else
    {
        *elapsedValue = currVal - value;
    }
}

void App_delayFunc(uint32_t timeout)
{
    uint32_t startCount, elapsedCount, cycleDelay;

    /* To config 32K Counter in run state when A15(Tda2xx)/M4(Tda3xx) is
     * halted */
    App_Config32KCounterSuspendState();

    App_Get32KCounterValue(&startCount);
    cycleDelay = (timeout * APP_32K_TIMER_FREQ) / 1000U;
    do
    {
        App_GetElapsedValue(startCount, &elapsedCount);
    } while (elapsedCount <= cycleDelay);
    UARTConfigPrintf(uartBaseAddr, "Delayed for %dms!!\n", timeout);
}
