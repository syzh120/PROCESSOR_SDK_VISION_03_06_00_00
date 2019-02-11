/*
 *   Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file     crc_app_semicpu.c
 *
 *  \brief    This file contains CRC test code for Semi-CPU mode.
 *
 *  \details  CRC operational mode is set to Semi-CPU for channel number 1.
 *            CRC signature is calculated on frame(1280*720*2) stored in DDR RAM
 *            and compared against pre-calculated good CRC signature value.
 *            Program uses SYNTIMER32k for performance calculation.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_crc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_crc.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Pre-calculated crc signature value for gievn data pattern */
#define APP_CRC_REFERENCE_SIGN_VAL_L      (0x10598F29U)
#define APP_CRC_REFERENCE_SIGN_VAL_H      (0x8BACD4FEU)

/* Timer frequency */
#define TIMER_FREQUENCY                 (32786U)

/* Frame deatils - used as refeneance data */
#define APP_FRAME_HEIGHT                     ((uint32_t) 1280U)
#define APP_FRAME_WIDTH                      ((uint32_t) 720U)
#define APP_FRAME_PIXEL_SIZE                  ((uint32_t) 2U)

/* CRC configuration parameters */
#define APP_CRC_CHANNEL                      (CRC_CHANNEL_1)
#define APP_CRC_PATTERN_SIZE                  ((uint32_t) 8U)
#define APP_CRC_PATTERN_CNT                                        \
    ((APP_FRAME_HEIGHT * APP_FRAME_WIDTH * APP_FRAME_PIXEL_SIZE) / \
     APP_CRC_PATTERN_SIZE)
#define APP_CRC_SECT_CNT                  ((uint32_t) 1U)
#define APP_CRC_WATCHDOG_PRELOAD_VAL              ((uint32_t) 0U)
#define APP_CRC_BLOCK_PRELOAD_VAL                 ((uint32_t) 0U)
#define APP_CRC_CH_CCITENR_MASK              (CRC_INTR_CH1_CCITENR_MASK)

/* Interation count for checking data integrity */
#define APP_ITERATION_CNT                  (20U)

/* Parameters for registering EDMA interrupt */
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (32U)
#define EDMA3_CC_REGION_M4                              (1U)
#define EDMA3_CC_REGION_DSP                             (1U)
#ifdef __TI_ARM_V7M4__
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_INST                       (CSL_XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)
#elif defined (_TMS320C6X)
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_DSP)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_DSP)
    #define SOC_EMIF1_BASE                  (0x80000000U)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_DSP1)
    #define XBAR_INST                       (CSL_XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_EDMA_TPCC_IRQ_REGION1)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

volatile uint32_t edmaTransferComplete;
uint32_t          edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber,
                  edmaInterruptNumber;
int32_t           gTestStatus = STW_SOK;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for CRC module.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void CRCAppClockEnable(void);
/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void CRCAppEdmaCompletionISR(void *handle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
#endif
}

int main(void)
{
    /* Declaration of variables */
    uint32_t              loopCnt, srcBuffer, edmaRegion,
                          errorFlag;
    uint32_t              frameSize, edmaCCnt;
    uint32_t             *srcMemory;
    uint32_t              timeStampBeforeDMAConfig,
                          timeStampAfterCompleteCompression;
    Float32               completionTime;
    EDMA3CCPaRAMEntry     edmaParam;
    uint32_t              patternCnt, sectCnt, baseAddr;
    uint32_t              watchdogPreloadVal, blockPreloadVal, patternSize;
    crcChannel_t          chNumber;
    crcOperationMode_t    mode;
    crcSignature_t        sectSignVal;
    crcSignatureRegAddr_t psaSignRegAddr;
    Float32               semiCPUPerformance;
    uint32_t          chain_param = (EDMA3_OPT_ITCCHEN_MASK |
                                     EDMA3_OPT_TCINTEN_MASK |
                                     EDMA3_OPT_ITCINTEN_MASK);

    /* Do Pad Config for UART */
    padConfig_prcmEnable();
    /* Initialize the UART Instance */
   /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr, " CRC Test Application\r\n", -1);
    /* Initialize variables */
    errorFlag        = 0U;
    srcMemory        = (uint32_t *) SOC_EMIF1_BASE;
    srcBuffer        = SOC_EMIF1_BASE;
    sectSignVal.regL = 0U;
    sectSignVal.regH = 0U;

    /* Configure CRC parameters */
    baseAddr           = SOC_CRC_BASE;
    patternSize        = APP_CRC_PATTERN_SIZE;
    patternCnt         = APP_CRC_PATTERN_CNT;
    sectCnt            = APP_CRC_SECT_CNT;
    watchdogPreloadVal = APP_CRC_WATCHDOG_PRELOAD_VAL;
    blockPreloadVal    = APP_CRC_BLOCK_PRELOAD_VAL;
    chNumber           = APP_CRC_CHANNEL;
    mode = CRC_OPERATION_MODE_SEMICPU;
    /* Enable CRC clock */
    CRCAppClockEnable();
    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(baseAddr,
                        chNumber,
                        &psaSignRegAddr);

    frameSize = (APP_FRAME_WIDTH * APP_FRAME_HEIGHT * APP_FRAME_PIXEL_SIZE);

    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    /* Enable EDAM completion interrupt */
    edmaInterruptNumber = EDMA3_CC_XFER_COMPLETION_INT;

    CSL_xbarIrqConfigure(XBAR_CPU,XBAR_INST,XBAR_INTR_SOURCE);

    Intc_Init();
    Intc_IntEnable(edmaInterruptNumber);
    Intc_IntRegister(edmaInterruptNumber, (IntrFuncPtr) CRCAppEdmaCompletionISR,
                     NULL);
    Intc_IntPrioritySet(edmaInterruptNumber, 1, 0);
    Intc_SystemEnable(edmaInterruptNumber);

    /* Calculate EDMA cCnt */
    edmaCCnt = 1;
    while ((frameSize / edmaCCnt) > 0x7FFF)
    {
        edmaCCnt = edmaCCnt * 2;
    }
    /* Configure EDMA parameters */
    edmaChannelNumber  = 0x1U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 0x1U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) srcBuffer;
    edmaParam.destAddr = psaSignRegAddr.regL;
    edmaParam.aCnt     = patternSize;
    edmaParam.bCnt     = patternCnt / edmaCCnt;
    edmaParam.cCnt     = edmaCCnt;
    edmaParam.srcBIdx  = edmaParam.aCnt;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = (edmaParam.aCnt * edmaParam.bCnt);
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    /* Initialize source memory with reference data */
    for (loopCnt = 0;
         loopCnt < (frameSize / 4);
         loopCnt++)
    {
        srcMemory[loopCnt] = loopCnt;
    }
    UARTConfigPuts(uartBaseAddr,"Copied reference data into DDR memory.\r\n", -1);
    UARTConfigPuts(uartBaseAddr,"Configuring EDMA and CRC for transfer.\r\n", -1);
    /* Configure CRC channel */
    CRCInitialize(baseAddr,
                  chNumber,
                  watchdogPreloadVal,
                  blockPreloadVal);
    /* Configure EDMA */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);

#if defined (_TMS320C6X) && defined (SOC_TDA3XX)
    for (loopCnt = 0; loopCnt < 32; loopCnt++)
    {
        DSPICFGSetMAR(SOC_DSP_ICFG_BASE, 0x80000000U + 16 * 1024 * 1024 *
                      loopCnt,
                      DSPICFG_MAR_PC);
    }
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif
    /* Get time-stamp */
    timeStampBeforeDMAConfig = HW_RD_REG32(SOC_COUNTER_32K_BASE +
                                           COUNTER_32K_CR);
    edmaTransferComplete = 0;
    for (loopCnt = 0U; loopCnt < APP_ITERATION_CNT; loopCnt++)
    {
        /* CRC channel RESET before initialization/configuration */
        CRCChannelReset(baseAddr, chNumber);
        /* Initialize CRC channel */
        CRCConfigure(baseAddr, chNumber, patternCnt, sectCnt, mode);
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
        /*Set params for chain transfer. Chain two channels*/
        EDMA3ChainChannel(SOC_EDMA_TPCC_BASE_VIRT,
                          edmaChannelNumber,
                          edmaChannelNumber,
                          chain_param);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                            edmaChannelNumber,
                            EDMA3_TRIG_MODE_MANUAL);

        /* Wait for transfer to complete */
        while (edmaTransferComplete != 1)
        {
        }
        edmaTransferComplete = 0;

        while ((CRCGetIntrStatus(baseAddr, chNumber) & APP_CRC_CH_CCITENR_MASK)
               != 0x1U)
        {
            /* Wait here till CRC compression complete is set. */
        }

        /* Fetch CRC signature value */
        CRCGetPSASectorSig(baseAddr, chNumber, &sectSignVal);
        /* Compare CRC signature value against reference CRC signature */
        if ((sectSignVal.regH ==
             APP_CRC_REFERENCE_SIGN_VAL_H)
            && (sectSignVal.regL ==
                APP_CRC_REFERENCE_SIGN_VAL_L))
        {
            /* Sector signature matches */
        }
        else
        {
            errorFlag = 1U;
            UARTConfigPuts(uartBaseAddr,
                "Sector signature does not match with pre-calculated value.\n",
                -1);
            gTestStatus = STW_EFAIL;
            break;
        }
        CRCClearIntr(baseAddr,
                     chNumber,
                     CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
    }

    if (errorFlag == 0U)
    {
        /* Get the time-stamp */
        timeStampAfterCompleteCompression = HW_RD_REG32(
            SOC_COUNTER_32K_BASE +
            COUNTER_32K_CR);
        UARTConfigPuts(uartBaseAddr,"CRC signature verification done successfully.\n", -1);
        completionTime = ((Float32)
                          (timeStampAfterCompleteCompression -
                           timeStampBeforeDMAConfig))
                         / (Float32) TIMER_FREQUENCY;
        semiCPUPerformance =
            (Float32) (((Float32) frameSize) / completionTime);
        semiCPUPerformance = ((Float32) semiCPUPerformance) *
                             ((Float32) APP_ITERATION_CNT);
        semiCPUPerformance = (Float32) semiCPUPerformance /
                             (1024U * 1024U);
        UARTConfigPuts(uartBaseAddr,"Processed frames ",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)APP_ITERATION_CNT);
        UARTConfigPuts(uartBaseAddr,"\n",-1);
        UARTConfigPuts(uartBaseAddr,"frames of size",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)APP_FRAME_HEIGHT);
        UARTConfigPuts(uartBaseAddr,"*",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)APP_FRAME_WIDTH);
        UARTConfigPuts(uartBaseAddr,"*",-1);
        UARTConfigPutNum(uartBaseAddr,(uint32_t)APP_FRAME_PIXEL_SIZE);
        UARTConfigPuts(uartBaseAddr,"\n",-1);
        UARTConfigPuts(uartBaseAddr,"CRC performance:",-1 );
        UARTConfigPutNum(uartBaseAddr,(uint32_t) semiCPUPerformance);
        UARTConfigPuts(uartBaseAddr,"MB/s\n",-1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"CRC signature verification failed.\n", -1);
    }

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAndInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif
    /* Disable the EDMA interrupt */
    Intc_SystemDisable(edmaInterruptNumber);
    Intc_IntUnregister(edmaInterruptNumber);
    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n CRC Test Pass", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\n CRC Test Fail", -1);
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void CRCAppClockEnable(void)
{
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CLKSTCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL,
                  CM_CRC_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
    HW_WR_FIELD32(SOC_CORE_CM_CORE_BASE + CM_CRC_CRC_CLKCTRL,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE,
                  CM_CRC_CRC_CLKCTRL_MODULEMODE_ENABLE);
}

static void CRCAppEdmaCompletionISR(void *handle)
{
    edmaTransferComplete = 1U;
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTCCNumber);
}
/********************************* End of file ******************************/
