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
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/stw_lld/platform/platform.h>

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define I2C_INT_NUM                   (56U)
#elif defined (SOC_TDA3XX)
#define I2C_INT_NUM                   (41U)
#endif
#define I2C_APP_SLAVE_OWN_ADDR        (0x68)
typedef enum
{
    TransferTypeFreshTransfer = 0,
    TransferTypeResponse1     = 1,
    TransferTypeResponse2     = 2
}I2C_AppTransferType_e;

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1, txRxStatus = 0;
lld_hsi2c_opMode  currentOpMode;
uint8_t           txData[15];
uint8_t           rxData[15];
uint8_t           resp1Data[15];
uint8_t           resp2Data[15];

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
int32_t I2CSlaveTransReceiveTest(hsI2cHandle i2cHandle);
void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);

static void configurI2cInterrupts(hsI2cHandle           i2cHandle,
                                  lld_hsi2c_initParam_t initPar);
static void printUsage(void);
static hsI2cHandle initializeI2cSlave(void);
static void printTxRxStatus(lld_hsi2c_transreceive_params_t *i2cXferParams);

/*******************************************************************************
**                            FUNCTION DEFINITION
*******************************************************************************/
int main()
{
    volatile uint32_t Done      = 1;
    hsI2cHandle       i2cHandle = NULL;
    int32_t           status    = STW_SOK;

    printUsage();

    i2cHandle = initializeI2cSlave();
    if (i2cHandle == NULL)
    {
        UARTprintf("\r\nError Initializing I2C Slave mode");
        status = STW_EFAIL;
    }

    if (status == STW_SOK)
    {
        I2CSlaveTransReceiveTest(i2cHandle);

        lld_i2c_close(&i2cHandle);

        lld_i2c_deinit(HSI2C_INST_0);
    }

    while (Done) ;

    return 0;
}

static hsI2cHandle initializeI2cSlave(void)
{
    hsI2cObjHandle        i2cObjHandle;
    hsI2cHandle           i2cHandle = NULL;
    lld_hsi2c_initParam_t initPar;

    initPar.opMode       = HSI2C_OPMODE_INTERRUPT;
    initPar.i2cBusFreq   = I2C_NORMAL;
    initPar.i2cOwnAddr   = I2C_APP_SLAVE_OWN_ADDR;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = LLD_HSI2C_MODE_SLAVE_TRANSRECEIVE;
    initPar.i2cIntNum    = I2C_INT_NUM;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST_0, (lldHsi2cAppCallback) i2c_callback,
                             NULL);

    configurI2cInterrupts(i2cHandle, initPar);

    return i2cHandle;
}

static void configurI2cInterrupts(hsI2cHandle           i2cHandle,
                                  lld_hsi2c_initParam_t initPar)
{
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    Intc_Init();
    Intc_IntEnable(0);
    /* Enable I2C interrupt */
    Intc_IntRegister(I2C_INT_NUM, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(I2C_INT_NUM, 1, 0);
    Intc_SystemEnable(I2C_INT_NUM);
}

/* Callback function for the restart condition */
void i2c_restartCallback(hsI2cHandle                      appHandle,
                         lld_hsi2c_transreceive_params_t *i2cXferParams)
{
    if (i2cXferParams->transferStatus == LLD_HSI2C_SLAVE_TX_PENDING)
    {
        if ((rxData[0] == 0x12) && (rxData[1] == 0x34))
        {
            /* transaction complete with restart condition from master */
            /* Send response 1 in restart Callback */
            i2cXferParams->txBuffer = &resp1Data[0];
            i2cXferParams->flags    = LLD_HSI2C_SLAVE |
                                      LLD_HSI2C_REPEAT_TX_BUF;
            i2cXferParams->txBufLen       = 15;
            i2cXferParams->transferStatus = LLD_HSI2C_SLAVE_BUFFER_UPDATED;
        }
    }
}

/* Callback function for transfer completion */
void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData)
{
    /* Unblock the thread waiting for transfer completion */
    intStatus = 0;
    /* Copy the transfer completion status to global variable to use it in
     * thread waiting for transfer completion */
    txRxStatus = status;
}

int32_t I2CInitiateSlaveTransfer(hsI2cHandle                      i2cHandle,
                                 lld_hsi2c_transreceive_params_t *i2cXferParams,
                                 I2C_AppTransferType_e            transferType)
{
    int32_t retVal = LLD_HSI2C_SUCCESS;

    if (transferType == TransferTypeFreshTransfer)
    {
        i2cXferParams->txBufLen          = 10;
        i2cXferParams->txBuffer          = &txData[0];
        i2cXferParams->rxBufLen          = 10;
        i2cXferParams->rxBuffer          = &rxData[0];
        i2cXferParams->processedTxBufLen = i2cXferParams->processedRxBufLen = 0;
        i2cXferParams->timeout           = 4000;
        i2cXferParams->flags         = LLD_HSI2C_SLAVE;
        i2cXferParams->txRxRestartCb =
            (lldHsi2cTransreceiveRestartCallback) i2c_restartCallback;
    }
    else if (transferType == TransferTypeResponse2)
    {
        /* Send Resp2 Buffer, repeate same buffer if more data is requested */
        i2cXferParams->txBuffer = &resp2Data[0];
        i2cXferParams->flags    = LLD_HSI2C_SLAVE |
                                  LLD_HSI2C_REPEAT_TX_BUF;
        i2cXferParams->txBufLen       = 15;
        i2cXferParams->transferStatus = LLD_HSI2C_SLAVE_BUFFER_UPDATED;
    }

    retVal = lld_i2c_transReceive(i2cHandle, i2cXferParams);

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        /* transfer initiated. Wait for completion callback. */
        while (intStatus) ;
        intStatus = 1;
        retVal    = txRxStatus;
    }
    else
    {
        UARTprintf("\r\nError initiating I2C slave transfer.");
    }

    return retVal;
}

int32_t I2CSlaveTransReceiveTest(hsI2cHandle i2cHandle)
{
    uint8_t                         i;
    volatile uint32_t               Done   = 1;
    volatile int32_t                retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_transreceive_params_t i2cXferParams;
    I2C_AppTransferType_e           transferType = TransferTypeFreshTransfer;

    /* Initialize Buffers */
    for (i = 0; i < 15; i++)
    {
        txData[i]    = i;
        rxData[i]    = 0;
        resp1Data[i] = 0x80 + i;
        resp2Data[i] = 0xA0 + i;
    }

    while (Done)
    {
        retVal = I2CInitiateSlaveTransfer(i2cHandle, &i2cXferParams,
                                          transferType);
        /* By default set transfer type for next transfer to fresh transfer.
         * This will be updated in specific cases */
        transferType = TransferTypeFreshTransfer;

        if (retVal < LLD_HSI2C_SUCCESS)
        {
            UARTprintf("\r\nI2c transaction failed ");
            /* Abort Current Transfer */
            lld_i2c_abort_transfer(i2cHandle);
        }
        else
        {
            /* Current transaction is complete */
            if ((i2cXferParams.transferStatus == LLD_HSI2C_SLAVE_RX_PENDING) ||
                (i2cXferParams.transferStatus == LLD_HSI2C_SLAVE_TX_PENDING))
            {
                /* transfer complete with restart condition from master */
                UARTprintf("\r\nRestart Received and buffer was not updated in"
                           " restart callback.");
                if (i2cXferParams.transferStatus == LLD_HSI2C_SLAVE_TX_PENDING)
                {
                    if ((rxData[0] == 0x12) && (rxData[1] == 0x35))
                    {
                        UARTprintf("Initiating new transaction with "
                                   "response type 2.");
                        /* Initiate transfer with response 2 */
                        transferType = TransferTypeResponse2;
                    }
                }
            }
            else if (i2cXferParams.transferStatus == LLD_HSI2C_SUCCESS)
            {
                /* transfer complete with stop condition from master */
                /* Print status Transmitted/received Bytes and count etc */
                printTxRxStatus(&i2cXferParams);

                /* Check if the exit condition is sent from external master */
                if ((i2cXferParams.processedRxBufLen != 0) &&
                    ((rxData[0] == 0x11) && (rxData[1] == 0x22)))
                {
                    UARTprintf("\r\nExiting the App\r\n");
                    /* Exit the App */
                    break;
                }
            }
        }
    }
    return retVal;
}

static void printTxRxStatus(lld_hsi2c_transreceive_params_t *i2cXferParams)
{
    uint32_t i;
    if (i2cXferParams->processedTxBufLen != 0)
    {
        UARTprintf("\r\nI2C Slave transmit successful. Transmitted %d bytes",
                   i2cXferParams->processedTxBufLen);
    }
    else if (i2cXferParams->processedRxBufLen != 0)
    {
        UARTprintf("\r\nI2C Slave read successful read %d bytes",
                   i2cXferParams->processedRxBufLen);
        for (i = 0; i < i2cXferParams->processedRxBufLen; i++)
        {
            UARTprintf("  %x", rxData[i]);
        }
    }
}

static void printUsage(void)
{
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTprintf("\r\nI2C Slave Test Started ");

    /* Slave mode supported only in interrupt mode and FIFO disabled */
    UARTprintf("\r\nconfigured in - INTERRUPT Mode, FIFO disabled.");
    UARTprintf("\r\nOwn Address of I2C slave is 0x%x.", I2C_APP_SLAVE_OWN_ADDR);
    UARTprintf("\r\nConnect the external I2C master like Aardvark to I2C1 SDA"
               " and SCL lines.");
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    UARTprintf("\r\npin 28 and 30 of EXP_P2 connector on base board connects to"
               " SCL and SDA lines of I2C1");
#endif
    UARTprintf("\r\nReceive and Transmit buffers are of 10 Bytes. Reading More"
               " or writing more than that will result in error.");
    UARTprintf("\r\nRegister read with different reg Address have "
               "following behaviour");
    UARTprintf("\r\n  reg Addr as 0x1234 Send resp1Data buffer "
               "in restart callback.");
    UARTprintf("\r\n  reg Addr as 0x1235 Send resp2Data buffer "
               "by initiating seperate transaction");
    UARTprintf("\r\n  reg Addr other than above Send txData buffer "
               "by initiating seperate transaction");
    UARTprintf("\r\nSending 2 byte data of 0x1122 will exit the application.");
}
