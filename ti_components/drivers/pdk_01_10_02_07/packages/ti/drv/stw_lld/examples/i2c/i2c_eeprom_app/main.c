/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/soc.h>

#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/i2clld/src/lld_hsi2c_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/stw_lld/platform/platform.h>

#include <ti/csl/csl_edma.h>

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX)) || \
    (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
#define SLAVE_ADDR                  (0x50)
#endif

#if (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
#define SLAVE_ADDR_1                  (0x51)
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || (defined (SOC_TDA2EX))
#define I2C_INT_NUM                   (56U)
#define I2C_XBAR_CFG_REQUIRED         (0U)

#define EDMA_COMP_INT                 (26U)
#define EDMA_XBAR_CFG_REQUIRED        (1U)

#define EDMA_INT_IRQ_XBAR_CPU_ID       CPU_MPUSS
#define EDMA_INT_IRQ_XBAR_INST_NO      XBAR_INST_MPU_IRQ_26
#define EDMA_INT_IRQ_XBAR_INDEX        EDMA_TPCC_IRQ_REGION0

#elif defined (SOC_TDA3XX)
#define I2C_INT_NUM                   (41U)
#define I2C_XBAR_CFG_REQUIRED         (0U)

#define EDMA_COMP_INT                 (34U)
#define EDMA_XBAR_CFG_REQUIRED        (1U)

#define EDMA_INT_IRQ_XBAR_CPU_ID       CPU_IPU1
#define EDMA_INT_IRQ_XBAR_INST_NO      XBAR_INST_IPU1_IRQ_34
#define EDMA_INT_IRQ_XBAR_INDEX        EDMA_TPCC_IRQ_REGION0

#elif defined (SOC_TI814X)
#define I2C_INT_NUM                   (70U)
#define I2C_XBAR_CFG_REQUIRED         (0U)
#define EDMA_COMP_INT                 (12U)
#define EDMA_XBAR_CFG_REQUIRED        (0U)
#endif

#define EDMA3_EVENT_QUEUE             (0U)
#define EDMA_U_BASE                   (SOC_EDMA_TPCC_BASE_VIRT)

#define DATA_SIZE                     (64)

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1, txRxStatus = 0;
lld_hsi2c_opMode  currentOpMode;
int32_t           gTestStatus = STW_SOK;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
int32_t I2CEepromReadWriteTest(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                               uint32_t blockNum);
void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);
void sampleDelay(int32_t delay);
void configurI2cTestInterrupts(hsI2cHandle           i2cHandle,
                               lld_hsi2c_initParam_t initPar);

void configurI2cTestInterrupts(hsI2cHandle           i2cHandle,
                               lld_hsi2c_initParam_t initPar)
{
#ifndef BUILD_A8
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();
#endif

#if I2C_XBAR_CFG_REQUIRED
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   I2C_INT_IRQ_XBAR_CPU_ID,
                   I2C_INT_IRQ_XBAR_INST_NO,
                   I2C_INT_IRQ_XBAR_INDEX);
#endif
#if EDMA_XBAR_CFG_REQUIRED
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   EDMA_INT_IRQ_XBAR_CPU_ID,
                   EDMA_INT_IRQ_XBAR_INST_NO,
                   EDMA_INT_IRQ_XBAR_INDEX);
#endif

    Intc_Init();
    Intc_IntEnable(0);
    /* Enable I2C interrupt */
    Intc_IntRegister(I2C_INT_NUM, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(I2C_INT_NUM, 1, 0);
    Intc_SystemEnable(I2C_INT_NUM);
    /* Enable EDMA Interrupt */
    Intc_IntRegister(EDMA_COMP_INT, (IntrFuncPtr) EDMA_callbackFn, i2cHandle);
    Intc_IntPrioritySet(EDMA_COMP_INT, 1, 0);
    Intc_SystemEnable(EDMA_COMP_INT);
}

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    volatile uint32_t     Done = 1;
    hsI2cObjHandle        i2cObjHandle;
    int32_t retVal = LLD_HSI2C_SUCCESS;
    LLD_hsi2cEdmaParam    edmaParam;
    uint32_t userInput, fifoEnable, probeStatus = 0;
    uint8_t  slaveAddr;
#ifndef TAKE_USER_INPUT
    uint32_t busfreq, opMode, fifoStatus;
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\r\nI2C EEPROM Test Application ", -1);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || (defined (SOC_TDA2EX))
    UARTPuts("\r\nWe write to EEPROM on EVM, Makesure USERCONFIG switch is on", -1);
    UARTPuts("\r\nRefer to EVM schematics to check USERCONFIG switch number", -1);
#elif defined (SOC_TDA3XX)
    UARTPuts("\r\nWe write to EEPROM on EVM, Makesure SW8001 - 2 is on", -1);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || (defined (SOC_TDA2EX))
    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();
#endif

    EDMAsetRegion(0);
    EDMA3Init(EDMA_U_BASE, EDMA3_EVENT_QUEUE);

#ifndef TAKE_USER_INPUT
    for (busfreq = 1; busfreq < 3; busfreq++)
    {
        for (opMode = 1; opMode < 4; opMode++)
        {
            for (fifoStatus = 1; fifoStatus < 3; fifoStatus++)
            {
#else
    do {
#endif
#ifdef TAKE_USER_INPUT
                UARTPuts(
                    "\r\nEnter Operating Mode\r\n1 For Polled Mode\
                          \r\n2 For Interrupt Mode\r\n3 For DMA Mode\r\n",
                    -1);
                userInput = UARTGetNum();
#else
                userInput = opMode;
#endif
                if (userInput == 1)
                {
                    currentOpMode = HSI2C_OPMODE_POLLED;
                    UARTPuts("\r\nconfigured in - POLLED Mode", -1);
                }
                else if (userInput == 2)
                {
                    currentOpMode = HSI2C_OPMODE_INTERRUPT;
                    UARTPuts("\r\nconfigured in - INTERRUPT Mode", -1);
                }
                else if (userInput == 3)
                {
                    currentOpMode = HSI2C_OPMODE_DMA;
                    UARTPuts("\r\nconfigured in - DMA Mode", -1);
                }
                else
                {
                    UARTPuts("\r\nInvalid Input: Defaulting to Interrupt mode",
                             -1);
                    currentOpMode = HSI2C_OPMODE_INTERRUPT;
                }
                initPar.opMode = currentOpMode;

#ifdef TAKE_USER_INPUT
                UARTPuts(
                    "\r\nEnter I2c Bus Speed\r\n1 For 100 Kbps\
                          \r\n2 For 400 Kbps\r\n",
                    -1);
                userInput = UARTGetNum();
                UARTPuts("\r\n", -1);
#else
                userInput = busfreq;
#endif
                if (userInput == 1)
                {
                    initPar.i2cBusFreq = I2C_NORMAL;
                    UARTPuts(" Frequency - 100 Kbps", -1);
                }
                else if (userInput == 2)
                {
                    initPar.i2cBusFreq = I2C_FAST;
                    UARTPuts(" Frequency - 400 Kbps", -1);
                }
                else
                {
                    UARTPuts("\r\nInvalid Input: Defaulting to 100 Kbps", -1);
                    initPar.i2cBusFreq = I2C_NORMAL;
                }

#ifdef TAKE_USER_INPUT
                UARTPuts(
                    "\r\nEnter FIFO Status\r\n1 For Enabled\r\n2 For Disabled\r\n",
                    -1);
                userInput = UARTGetNum();
                UARTPuts("\r\n", -1);
#else
                userInput = fifoStatus;
#endif
                if (userInput == 1)
                {
                    fifoEnable = 0U;
                    UARTPuts(" FIFO status - Disabled", -1);
                }
                else if (userInput == 2)
                {
                    fifoEnable = 1U;
                    UARTPuts(" FIFO status - Enabled", -1);
                }
                else
                {
                    UARTPuts("\r\nInvalid Input: Defaulting Fifo Disabled", -1);
                    fifoEnable = 0U;
                }

                edmaParam.baseAddr   = EDMA_U_BASE;
                edmaParam.eventQueue = EDMA3_EVENT_QUEUE;
                initPar.edmaParam    = (void *) &edmaParam;
                initPar.i2cOwnAddr   = 0xFE;
                initPar.is10BitAddr  = 0;
                initPar.isMasterMode = 1;
                initPar.i2cIntNum    = I2C_INT_NUM;

                lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);

                if (fifoEnable == 1U)
                {
                    /*Set FIFO threshold of 16bytes*/
                    lld_i2c_SetFifoThreshold(HSI2C_INST_0, 15, 15);
                }

                i2cHandle =
                    lld_i2c_open(HSI2C_INST_0,
                                 (lldHsi2cAppCallback) i2c_callback,
                                 NULL);
                configurI2cTestInterrupts(i2cHandle, initPar);

                if (probeStatus == 0)
                {
                    slaveAddr = SLAVE_ADDR;
                    retVal    = lld_i2c_probe(i2cHandle, slaveAddr);
#if (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
                    if (retVal != LLD_HSI2C_SUCCESS)
                    {
                        slaveAddr = SLAVE_ADDR_1;
                        retVal    = lld_i2c_probe(i2cHandle, slaveAddr);
                    }
#endif
                    if (retVal != LLD_HSI2C_SUCCESS)
                    {
                        UARTPuts("\r\nI2c Probe failed ", -1);
                        return 0;
                    }
                    probeStatus = 1;
                }

                /* Write to Block 1 of EEPROM */
                retVal = I2CEepromReadWriteTest(i2cHandle, slaveAddr, 1U);

                if (retVal == LLD_HSI2C_SUCCESS)
                {
                    UARTPuts("\r\nI2c Test successfull ", -1);
                }
                else
                {
                    UARTPuts("\r\nI2c Test Failed ", -1);
                    UARTPuts("\r\nI2C EEPROM Test Fail ", -1);

#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX)) || \
    (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
                    StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
#endif
                    while (Done) ;
                }

                lld_i2c_close(&i2cHandle);

                lld_i2c_deinit(HSI2C_INST_0);

#ifndef TAKE_USER_INPUT
            }
        }
    }
#else
                UARTPuts(
                    "\r\nPress 1 to run again with different configuration",
                    -1);
                UARTPuts("\r\nPress Any other Key to exit\r\n", -1);
                userInput = UARTGetNum();
                if (userInput != 1)
                {
                    UARTPuts("\r\n", -1);
                    break;
                }
            }
            while (Done) ;
#endif

    if (gTestStatus == STW_SOK)
    {
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX)) || \
    (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
#endif
        UARTPuts("\r\nI2C EEPROM Test Pass ", -1);
    }
    else
    {
#if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX)) || \
    (defined (SOC_TDA2EX)) || (defined (SOC_TDA3XX))
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
#endif
        UARTPuts("\r\nI2C EEPROM Test Fail ", -1);
    }

    while (Done) ;

    return 0;
}

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData)
{
    intStatus = 0;

    if (LLD_HSI2C_SUCCESS == status)
    {
        /*UARTPuts("\r\nISR Called. I2C TX/RX Successfull", -1);*/
    }
    else
    {
        txRxStatus = 1;
        /*UARTPuts("\r\nISR Called. I2C TX/RX Failed", -1);*/
    }
}

int32_t I2CEepromReadWriteTest(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                               uint32_t blockNum)
{
    volatile int32_t retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t count;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t data[DATA_SIZE + 2];
    uint32_t processedBufLength;
    uint32_t blockAddr = 0;

#if defined BUILD_A8 && !defined BUILD_GCC
    volatile uint32_t start, stop;
#endif
    do
    {
        i2cXferParams.bufLen    = (DATA_SIZE + 2);
        i2cXferParams.buffer    = &data[0];
        i2cXferParams.slaveAddr = (uint8_t) slaveAddr;
        i2cXferParams.timeout   = 4000;

        /*Calculate block addr*/
        blockAddr = 64 * (blockNum);
        data[0]   = (uint8_t) (((uint32_t) 0xFF00 & blockAddr) >> 8);
        data[1]   = (uint8_t) ((uint32_t) 0xFF & blockAddr);
        for (count = 2; count < (DATA_SIZE + 2); count++)
        {
            data[count] = count;
        }

        /*Write data to eeprom*/
        i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        /*Wait for EEPROM to complete write*/
        sampleDelay(1000);

        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt is called
            **/
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }

        if(currentOpMode == HSI2C_OPMODE_INTERRUPT)
        {
            lld_i2c_getProcessedBufLength(i2cHandle, &processedBufLength);
            if(processedBufLength != i2cXferParams.bufLen)
            {
                UARTprintf("\r\ni2cXferParams.bufLen = %d is not same as "
                    "processed bytes = %d",
                    i2cXferParams.bufLen, processedBufLength);
            }
        }

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2c write Data failed ", -1);
            gTestStatus = STW_EFAIL;
            break;
        }

        /*Clear data*/
        for (count = 2; count < (DATA_SIZE + 2); count++)
        {
            data[count] = 0;
        }

        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];

        /*Write base address to eeprom*/
        i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        /*Wait for EEPROM to complete write*/
        sampleDelay(1000);

        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt call */
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2c write Address failed ", -1);
            gTestStatus = STW_EFAIL;
            break;
        }

        i2cXferParams.bufLen = DATA_SIZE;
        i2cXferParams.buffer = &data[2];

        i2cXferParams.flags = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

#if defined BUILD_A8 && !defined BUILD_GCC
        /*Read data in 100kbps*/
        enableticks;
        start = getticks;
#endif
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt call */
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\r\nI2c write Address failed ", -1);
            gTestStatus = STW_EFAIL;
            break;
        }

#if defined BUILD_A8 && !defined BUILD_GCC
        stop = getticks;
        printticks(ticks(start, stop), "\r\nTime taken for 100kbps");
#endif
        for (count = 2; count < DATA_SIZE + 2; count++)
        {
            if (data[count] != count)
            {
                UARTPuts("\r\nI2c write and read data did not match ", -1);
                UARTPutNum(count);
                retVal = LLD_HSI2C_FAIL;
            }
        }
    } while (0);
    txRxStatus = 0;
    return retVal;
}

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}
