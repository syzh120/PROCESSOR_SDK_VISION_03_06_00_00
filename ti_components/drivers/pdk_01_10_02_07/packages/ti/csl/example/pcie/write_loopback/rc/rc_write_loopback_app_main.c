/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     rc_write_loopback_app_main.c
 *
 *  \brief    This file contains PCIe write loopback test code for RC.
 *
 *  \details   RC transmits 1MB of data to EP, waits till EP sends back data
 *             and checks for data integrity.
 *
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/cslr_synctimer.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include <ti/csl/arch/csl_arch.h>

/* Application header files */
#include "pcie_app.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define OUTBOUND_PCIE_ADDRESS ((uint32_t) 0xA0000000U)
#define INBOUND_PCIE_ADDRESS  ((uint32_t) 0xB0000000U)

#define DATA_SIZE                         ((uint32_t) 0x1000000U)
#define DATA_SIZE_IN_WORD                 ((uint32_t) DATA_SIZE / 4U)

#if defined (__TI_ARM_V7M4__)
#define EDMA_TCC_NUM                      ((uint32_t) 1U)
#define EDMA_CH_NUM                       ((uint32_t) 1U)
#else
#define EDMA_TCC_NUM                      ((uint32_t) 0U)
#define EDMA_CH_NUM                       ((uint32_t) 0U)
#endif
#define EDMA_EQ_NUM                       ((uint32_t) 0U)

#define EDMA_CC_REGION_A15                ((uint32_t) 0U)
#define EDMA3_CC_REGION_M4                ((uint32_t) 1U)
#define EDMA3_CC_REGION_DSP               ((uint32_t) 1U)

#define EDMA_A_COUNT                      ((uint32_t) 0x4000U)
#define EDMA_B_COUNT                      ((uint32_t) DATA_SIZE / EDMA_A_COUNT)
#define EDMA_C_COUNT                      ((uint32_t) 1U)

#define PCIE_MAIN_INT_A15                 ((uint32_t) 13U)
#define EDMA_XFER_COMPLETION_INT_A15      ((uint32_t) 12U)

#define PCIE_MAIN_INT_M4                  ((uint32_t) 35U)
#define EDMA_XFER_COMPLETION_INT_M4       ((uint32_t) 34U)

#define PCIE_MAIN_INT_DSP                 ((uint32_t) 39U)
#define EDMA_XFER_COMPLETION_INT_DSP      ((uint32_t) 38U)

#if defined (__ARM_ARCH_7A__)
    #define PCIE_MAIN_INT                 (PCIE_MAIN_INT_A15)
    #define EDMA_XFER_COMPLETION_INT      (EDMA_XFER_COMPLETION_INT_A15)
    #define EDMA_CC_REGION                (EDMA_CC_REGION_A15)
    #define APP_SOC_EDMA_TPCC_BASE        (SOC_EDMA_TPCC_BASE_VIRT)
#elif defined (__TI_ARM_V7M4__)
    #define PCIE_MAIN_INT                 (PCIE_MAIN_INT_M4)
    #define EDMA_XFER_COMPLETION_INT      (EDMA_XFER_COMPLETION_INT_M4)
    #define EDMA_CC_REGION                (EDMA3_CC_REGION_M4)
    #define APP_SOC_EDMA_TPCC_BASE        (SOC_EDMA_TPCC_BASE_VIRT)
#elif defined (_TMS320C6X)
    #define PCIE_MAIN_INT                 (PCIE_MAIN_INT_DSP)
    #define EDMA_XFER_COMPLETION_INT      (EDMA_XFER_COMPLETION_INT_DSP)
    #define EDMA_CC_REGION                (EDMA3_CC_REGION_DSP)
    #define APP_SOC_EDMA_TPCC_BASE        (SOC_EDMA_TPCC_BASE_VIRT)
#endif

#define RX_DATA_BUFFER_ADDR               ((uint32_t) 0x90000000U)

#define COUNTER_MAX_VALUE                 ((uint32_t) 0xFFFFFFFFU)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static volatile uint32_t dataTxBuffer[DATA_SIZE_IN_WORD];

static volatile uint32_t transfer_complete = 0U;
static volatile uint32_t memSpaceEnable    = 0U;
static volatile uint32_t linkEnable        = 0U;
static volatile uint32_t timerStartVal, timerEndVal, timerDiffVal;

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API configures the PCIe outbound window.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigOutBoundWindow(void);

/**
 * \brief   This API configures the PCIe inbound window.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigInBoundWindow(void);

/**
 * \brief   This API configures the PCIe local traffic.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigTrafficLocal(void);

/**
 * \brief   This API configures the PCIe remote traffic.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppConfigTrafficRemote(void);

/**
 * \brief   This API initializes the RX and Tx data buffer.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppInitRxTxBuf(void);

/**
 * \brief   This API initializes the EDMA for data transfer.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppEdmaInit(void);

/**
 * \brief   This API configures the INTC for PCIe and EDMA interrupts.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void PcieAppIntrInit(void);

/**
 * \brief   ISR which gets called on EDMA completion interrupt.
 *
 * \param   handle      Interrupt handle.
 *
 * \retval  none.
 */
static void PcieAppEdmaCompletionIsr(void *handle);

/**
 * \brief   ISR that gets called when main interrupt is raised.
 *
 * \param   handle      Interrupt handle.
 *
 * \retval  none.
 */
static void PcieAppMainIsr(void *handle);

/**
 * \brief   This API checks the data sent by EP for integrity.
 *
 * \param   none.
 *
 * \retval  PASS      Test case ran successfully and receive data matches
 *                    transmitted data.
 * \retval  FALSE      Test case ran successfully and receive data does not
 *                    match transmitted data.
 */
static uint32_t PcieAppCheckDataIntegrity(void);

/**
 * \brief   This API Reads current 32KHz counter value.
 *
 * \param   none.
 *
 * \retval  none.
 */
static uint32_t PcieRead32kCounter(void);

/**
 * \brief   This API Calculates the count difference between old and new timer.
 *          count value. Takes care when the counter value is wrapped back to 0.
 *
 * \param   none.
 *
 * \retval  none.
 */
static uint32_t PcieCounterDiff(uint32_t oldVal, uint32_t newVal);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
/*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO | 
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

void PlatformEDMAWkupDepEnable(void)
{
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC1_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC1_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC2_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC2_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPCC_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPCC_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }
}

int main()
{
    uint32_t timeInUSec, txSpeed;
    uint32_t linkSpeed, linkSpeedUsrInput;

#if    defined (__TI_ARM_V7M4__)
    /* Enable AMMU for M4 */
    AppUtilsConfigIPU1DefaultAMMU();
    /* Enable UniCache */
    UNICACHEEnable(CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS);
#endif

    /* Do Pad Config for UART */
    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"RC: PCIe write loopBack App\n\n", -1);
    UARTConfigPuts(uartBaseAddr,"RC: Please enter link speed\n 1 - for Gen 1\n 2 - For Gen 2\n",
            -1);
    linkSpeedUsrInput = UARTConfigGetNum(uartBaseAddr);
    if (linkSpeedUsrInput == 1)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTConfigPuts(uartBaseAddr,"RC: Configured for Gen1 Mode\n", -1);
    }
    else if (linkSpeedUsrInput == 2)
    {
        linkSpeed = PCIE_LINK_SPEED_GEN2;
        UARTConfigPuts(uartBaseAddr,"RC: Configured for Gen2 Mode\n", -1);
    }
    else
    {
        linkSpeed = PCIE_LINK_SPEED_GEN1;
        UARTConfigPuts(uartBaseAddr,"RC: Invalid Input. Using Gen1 by default\n", -1);
    }

    /*Configure INTC*/
    PcieAppIntrInit();
    /*Configure PCIe Pll, PRCM, PHY */
    PCIEAppPrcmConfig();

    /*Set device type*/
    PCIESetDeviceType(SOC_PCIE_SS1_CONF_BASE, PCIE_DEVICE_TYPE_RC);

    PCIEMainIntrEnable(
        SOC_PCIE_SS1_CONF_BASE,
        PCIE_MAIN_INTR_FLAG_CFG_MSG_SPACE_EN_EVT |
        PCIE_MAIN_INTR_FLAG_LINK_UP_EVT);

    /*Set max link width and speed*/
    PCIEConfigLink(
        SOC_PCIE_SS1_CONF_BASE,
        (pcieLinkSpeed_t)linkSpeed,
        PCIE_NUMBER_OF_LANES);

    /*Configure outbound cfg and mem space*/
    PcieAppConfigOutBoundWindow();
    /*Configure inbound mem space*/
    PcieAppConfigInBoundWindow();
    /*Init transmit and receive buffer*/
    PcieAppInitRxTxBuf();

    PcieAppConfigTrafficLocal();

    /*Enable link*/
    PCIELtssmEnable(SOC_PCIE_SS1_CONF_BASE, PCIE_CONFIG_ENABLE);
    UARTConfigPuts(uartBaseAddr,"RC: Waiting for link to be UP\n", -1);

    /*Wait till link is up link*/
    while (linkEnable != 1U);
    UARTConfigPuts(uartBaseAddr,"RC: Link is UP\n\n", -1);

    /*Configure PCIe traffic*/
    PcieAppConfigTrafficRemote();
    /*Wait till mem space is enabled*/
    while (memSpaceEnable != 1U) ;
    UARTConfigPuts(uartBaseAddr,"RC: Mem space is enabled\n", -1);
    UARTConfigPuts(uartBaseAddr,"RC: Sending data to EP\n", -1);

    /*Init EDMA and enable transfer*/
    PcieAppEdmaInit();

    /* Wait till EP receives the data. */
    while (HW_RD_REG32(PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
                        OUTBOUND_MEM_SPACE + DATA_SIZE - 4U) != 0x12344321U)
    {
#if defined (__ARM_ARCH_7A__)
    CSL_a15InvDataCache((void *)(PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
                        OUTBOUND_MEM_SPACE + DATA_SIZE - 4U), 4U);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEInvalidate( CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS,
                        (uint32_t) (PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
                        OUTBOUND_MEM_SPACE + DATA_SIZE - 4U),
                        4U,
                        UNICACHE_WAIT_INFINITE);
#endif
    }

    timerEndVal  = PcieRead32kCounter();
    timerDiffVal = PcieCounterDiff(timerStartVal, timerEndVal);

    /* Time in Micro Sec = (Counter Difference * 1000 * 1000) / 32K) */
    timeInUSec = (timerDiffVal * 1000) / 32;
    /* Transfer Speed = Data transferred / Time taken for transfer */
    txSpeed = DATA_SIZE / timeInUSec;

    UARTConfigPuts(uartBaseAddr,"RC: Data sent to EP\n", -1);
    UARTConfigPuts(uartBaseAddr,"RC: Data size is : ", -1);
    UARTConfigPutHexNum(uartBaseAddr,DATA_SIZE);
    UARTConfigPuts(uartBaseAddr,"\nRC: Time taken to transmit data is : ", -1);
    UARTConfigPutNum(uartBaseAddr,(int32_t)timeInUSec);
    UARTConfigPuts(uartBaseAddr," micro Sec\n", -1);
    UARTConfigPuts(uartBaseAddr,"RC: Transfer Speed is : ", -1);
    UARTConfigPutNum(uartBaseAddr,(int32_t)txSpeed);
    UARTConfigPuts(uartBaseAddr," MBps\n", -1);

    /* Deinit EDMA*/
    EDMA3Deinit(APP_SOC_EDMA_TPCC_BASE, EDMA_EQ_NUM);
    UARTConfigPuts(uartBaseAddr,"RC: Waiting for EP to transmit data\n", -1);
    /*Wait till EP writes back data to RC*/
    while (HW_RD_REG32(RX_DATA_BUFFER_ADDR + DATA_SIZE - 4U) !=
            0x12344321U)
    {
#if defined (__ARM_ARCH_7A__)
    CSL_a15InvDataCache((void *)(RX_DATA_BUFFER_ADDR + DATA_SIZE - 4U), 4U);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEInvalidate( CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS,
                            (uint32_t) (RX_DATA_BUFFER_ADDR + DATA_SIZE - 4U),
                            4U,
                            UNICACHE_WAIT_INFINITE);
#endif
    }

    UARTConfigPuts(uartBaseAddr,"RC: Data received from EP\n", -1);

    if (TRUE == PcieAppCheckDataIntegrity())
    {
        UARTConfigPuts(uartBaseAddr,"RC: Sent data matches received data\n", -1);
        UARTConfigPuts(uartBaseAddr,"RC: PCIe write loopBack test passed\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"RC: Sent data doesn't match received data\n", -1);
        UARTConfigPuts(uartBaseAddr,"RC: PCIe write loopBack test failed\n", -1);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static uint32_t PcieRead32kCounter(void)
{
    uint32_t val;
    val = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    return val;
}

static uint32_t PcieCounterDiff(uint32_t oldVal, uint32_t newVal)
{
    uint32_t diff;
    if (oldVal > newVal)
    {
        /* Counter has Wrapped back to 0 */
        diff  = COUNTER_MAX_VALUE - oldVal;
        diff += newVal;
    }
    else
    {
        diff = newVal - oldVal;
    }
    return diff;
}

static uint32_t PcieAppCheckDataIntegrity(void)
{
    uint32_t wordCount;
    uint32_t status = TRUE;

#if defined (__ARM_ARCH_7A__)
    CSL_a15InvDataCache((void *)(RX_DATA_BUFFER_ADDR), DATA_SIZE);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEInvalidate( CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS,
                        (uint32_t) (RX_DATA_BUFFER_ADDR),
                        DATA_SIZE,
                        UNICACHE_WAIT_INFINITE);
#endif

    for (wordCount = 0U; wordCount < DATA_SIZE_IN_WORD - 1U;
        wordCount++)
    {
        if (dataTxBuffer[wordCount] !=
            HW_RD_REG32(RX_DATA_BUFFER_ADDR + (wordCount * 4U)))
        {
            UARTConfigPuts(uartBaseAddr,
                "\nRC: Received data did not match transmitted data",
                -1);
            status = FALSE;
            break;
        }
        wordCount++;
    }

    return status;
}

static void PcieAppConfigOutBoundWindow(void)
{
    pcieLocationParams_t  locationParams;
    pcieAtuRegionParams_t regionParams;

    /*Configure OB region for remote configuration access space*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_OUTBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_CFG;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;

    regionParams.lowerBaseAddr    = OUTBOUND_CFG_OFFSET;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = OUTBOUND_CFG_OFFSET_LIMIT;

    regionParams.lowerTargetAddr = 0U;
    regionParams.upperTargetAddr = 0U;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 0U,
        &regionParams);

    /*Configure OB region for memory transfer*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_OUTBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_MEM;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;

    regionParams.lowerBaseAddr    = OUTBOUND_MEM_SPACE;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = OUTBOUND_MEM_SPACE_LIMIT;

    regionParams.lowerTargetAddr = OUTBOUND_PCIE_ADDRESS;
    regionParams.upperTargetAddr = PCIE_UPPER_ADDRESS;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 1U,
        &regionParams);
}

static void PcieAppConfigInBoundWindow(void)
{
    pcieLocationParams_t  locationParams;
    pcieAtuRegionParams_t regionParams;

    /*Configure IB region for memory transfer*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    regionParams.regionDir    = PCIE_ATU_REGION_DIR_INBOUND;
    regionParams.tlpType      = PCIE_TLP_TYPE_MEM;
    regionParams.enableRegion = PCIE_CONFIG_ENABLE;
    regionParams.matchMode    = PCIE_ATU_REGION_MATCH_MODE_ADDR;

    regionParams.lowerBaseAddr    = INBOUND_PCIE_ADDRESS;
    regionParams.upperBaseAddr    = PCIE_UPPER_ADDRESS;
    regionParams.regionWindowSize = INBOUND_PCIE_LIMIT;

    regionParams.lowerTargetAddr = RX_DATA_BUFFER_ADDR;
    regionParams.upperTargetAddr = PCIE_UPPER_ADDRESS;

    PCIEAtuRegionConfig(
        SOC_PCIE_SS1_CONF_BASE,
        &locationParams,
        (uint32_t) 0U,
        &regionParams);
}

static void PcieAppConfigTrafficLocal(void)
{
    pcieLocationParams_t    locationParams;
    pcieTrafficCtrlParams_t trafficCtrlParams;

    /*Enable local traffic*/
    locationParams.location = PCIE_LOCATION_LOCAL;

    trafficCtrlParams.enableMemSpace   = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIntxAssert = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIoSpace    = PCIE_CONFIG_DISABLE;
    trafficCtrlParams.enableSerr       = PCIE_CONFIG_DISABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams,
                    &trafficCtrlParams);
}

static void PcieAppConfigTrafficRemote(void)
{
    pcieLocationParams_t    locationParams;
    pcieTrafficCtrlParams_t trafficCtrlParams;

    /*Enable remote traffic*/
    locationParams.location          = PCIE_LOCATION_REMOTE;
    locationParams.outboundCfgOffset = OUTBOUND_CFG_OFFSET;

    trafficCtrlParams.enableMemSpace  = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableBusMaster = PCIE_CONFIG_ENABLE;
    trafficCtrlParams.enableIntxAssert = PCIE_CONFIG_DISABLE;
    trafficCtrlParams.enableIoSpace    = PCIE_CONFIG_DISABLE;
    PCIETrafficCtrl(SOC_PCIE_SS1_CONF_BASE, &locationParams,
                    &trafficCtrlParams);
}

static void PcieAppInitRxTxBuf(void)
{
    uint32_t wordCount;

    for (wordCount = 0U; wordCount < DATA_SIZE_IN_WORD; wordCount++)
    {
        dataTxBuffer[wordCount] = wordCount;
    }
    dataTxBuffer[--wordCount] = 0xE0DU;

    memset((void *) RX_DATA_BUFFER_ADDR, 0U, DATA_SIZE);
#if defined (__ARM_ARCH_7A__)
    CSL_a15WbDataCache((void *)dataTxBuffer, DATA_SIZE);
    CSL_a15WbDataCache((void *)RX_DATA_BUFFER_ADDR, DATA_SIZE);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBack ( CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS,
                        (uint32_t) (dataTxBuffer),
                        DATA_SIZE,
                        UNICACHE_WAIT_INFINITE);

    UNICACHEWriteBack ( CSL_IPU_IPU1_UNICACHE_MMU_CONF_REGS_REGS,
                        (uint32_t) (RX_DATA_BUFFER_ADDR),
                        DATA_SIZE,
                        UNICACHE_WAIT_INFINITE);
#endif
}

static void PcieAppEdmaInit(void)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          triggerCount;

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    EDMAsetRegion(EDMA_CC_REGION);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(APP_SOC_EDMA_TPCC_BASE, 0U);

    EDMA3RequestChannel(
        APP_SOC_EDMA_TPCC_BASE,
        EDMA3_CHANNEL_TYPE_DMA,
        EDMA_CH_NUM,
        EDMA_TCC_NUM,
        EDMA_EQ_NUM);

    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) dataTxBuffer;
    edmaParam.destAddr =
        (PCIEGetOutboundAddr(SOC_PCIE_SS1_CONF_BASE) +
        OUTBOUND_MEM_SPACE);
    edmaParam.aCnt     = EDMA_A_COUNT;
    edmaParam.bCnt     = EDMA_B_COUNT;
    edmaParam.cCnt     = EDMA_C_COUNT;
    edmaParam.srcBIdx  = EDMA_A_COUNT;
    edmaParam.destBIdx = EDMA_A_COUNT;
    edmaParam.srcCIdx  = EDMA_C_COUNT;
    edmaParam.destCIdx = EDMA_C_COUNT;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
        ((EDMA_TCC_NUM <<
        EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK) |
        (EDMA3_SYNC_AB << 2U));

    EDMA3SetPaRAM(APP_SOC_EDMA_TPCC_BASE, EDMA_CH_NUM, &edmaParam);
    timerStartVal = PcieRead32kCounter();
    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are C COUNT
     */
    for (triggerCount = 0U; triggerCount < (EDMA_C_COUNT);
         triggerCount++)
    {
        transfer_complete = 0U;
        EDMA3EnableTransfer(
            APP_SOC_EDMA_TPCC_BASE,
            EDMA_CH_NUM,
            EDMA3_TRIG_MODE_MANUAL);
        while (transfer_complete != 1U) ;
    }
}

static void PcieAppEdmaCompletionIsr(void *handle)
{
    transfer_complete = 1;
    EDMA3ClrIntr(APP_SOC_EDMA_TPCC_BASE, EDMA_TCC_NUM);
}

static void PcieAppMainIsr(void *handle)
{
    uint32_t status;

    status = PCIEMainIntrStatus(SOC_PCIE_SS1_CONF_BASE);
    if (status & PCIE_MAIN_INTR_FLAG_CFG_MSG_SPACE_EN_EVT)
    {
        memSpaceEnable = 1;
    }

    if (status & PCIE_MAIN_INTR_FLAG_LINK_UP_EVT)
    {
        linkEnable = 1;
    }

    PCIEMainIntrClear(SOC_PCIE_SS1_CONF_BASE, status);
}

static void PcieAppIntrInit(void)
{
#if defined (__ARM_ARCH_7A__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,CSL_XBAR_INST_MPU_IRQ_12,CSL_XBAR_EDMA_TPCC_IRQ_REGION0);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU,CSL_XBAR_INST_MPU_IRQ_13,CSL_XBAR_PCIe_SS1_IRQ_INT0);
#elif defined (__TI_ARM_V7M4__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,CSL_XBAR_INST_IPU1_IRQ_34,CSL_XBAR_EDMA_TPCC_IRQ_REGION1);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,CSL_XBAR_INST_IPU1_IRQ_35,CSL_XBAR_PCIe_SS1_IRQ_INT0);
#elif defined (_TMS320C6X)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,CSL_XBAR_INST_DSP1_IRQ_38,CSL_XBAR_EDMA_TPCC_IRQ_REGION1);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,CSL_XBAR_INST_DSP1_IRQ_39,CSL_XBAR_PCIe_SS1_IRQ_INT0);
#endif

    /* Enable The EDMA interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(
        EDMA_XFER_COMPLETION_INT,
        (IntrFuncPtr) PcieAppEdmaCompletionIsr,
        NULL);
    Intc_IntPrioritySet(EDMA_XFER_COMPLETION_INT, 1, 0);

    Intc_IntRegister(
        PCIE_MAIN_INT,
        (IntrFuncPtr) PcieAppMainIsr,
        NULL);
    Intc_IntPrioritySet(PCIE_MAIN_INT, 1, 0);

    Intc_SystemEnable(EDMA_XFER_COMPLETION_INT);
    Intc_SystemEnable(PCIE_MAIN_INT);
}
/********************************* End of file ******************************/
