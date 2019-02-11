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

/**
 * @file  lld_hsi2c.c
 *
 * @brief This file contains the device LLD APIs for High Speed I2c
 *
 */

/******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************/
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <lld_hsi2c_edma.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>

/* ========================================================================== */

/* Maximum number of interrupts to handle in same ISR - to avoid locking up
 * CPU in I2C ISRs
 * Keep atleast 3 to support optimal RX followed by TX scenario
 * Keep atleast 2 to support optimal RX scenario
 */
#define MAX_CONSECUTIVE_ISRS (5U)

/** LLD_Hsi2cInstState_t are the states the LLD is operating.
 *
 *  @param    LLD_HSI2C_INST_CREATED    Instance is in created state . Set after
 *                                      calling lld_i2c_init() fn
 *  @param    LLD_HSI2C_INST_OPENED     Instance is open open state. Set after
 *                                      calling lld_i2c_open()
 *  @param    LLD_HSI2C_INST_BUSY       Instance is in BUSY state. Set by
 *                                      transfer function is case status is busy
 *  @param    LLD_HSI2C_INST_ERROR      ERROR occurred. Set by transfer function
 *                                      in case error occurred during transfer
 *  @param    LLD_HSI2C_INST_CLOSED     State of instance is closed. Set by
 *                                      lld_i2c_close() fn
 *
 */
/* ========================================================================== */
typedef enum
{
    LLD_HSI2C_INST_CREATED = (uint8_t) 0,
    LLD_HSI2C_INST_OPENED,
    LLD_HSI2C_INST_BUSY,
    LLD_HSI2C_INST_BUSY_SLAVE_TFR_NOT_STARTED,
    LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED,
    LLD_HSI2C_INST_BUSY_SLAVE_TFR_HOLD,
    LLD_HSI2C_INST_ERROR,
    LLD_HSI2C_INST_CLOSED
}LLD_Hsi2cInstState_t;

/* ========================================================================== */
/**
 *   lld_hsi2c_obj_s defines the I2C Object parameters.
 *
 *   @see lld_hsi2c.h
 */
/* ========================================================================== */
typedef struct lld_hsi2c_obj_s {
    lld_hsi2c_initParam_t            initParam;
    lld_hsi2c_datatfr_params_t       dataTfrParam;
    uint32_t                         maxBufLength;

    LLD_Hsi2cInstId_t                instNum;
    uint32_t                         baseAddr;
    uint8_t                          numOpens;
    LLD_Hsi2cInstState_t             state;

    uint16_t                         dmaChaAllocated;
    uint32_t                         rxDmaEventNumber;
    uint32_t                         txDmaEventNumber;

    uint8_t                          rxThreshold;
    uint8_t                          txThreshold;

    uint32_t                         i2cFclk;
    uint32_t                         i2cIclk;
    lld_i2c_busspeed                 busFreq;

    lld_hsi2c_transreceive_params_t *i2cXferParams;
}lld_hsi2c_obj_t;

/* ========================================================================== */
/**
 *   lld_hsi2c_obj_s defines the I2C handle parameters.
 *
 *   @see lld_hsi2c.h
 */
/* ========================================================================== */
typedef struct lld_hsi2c_handle_s {
    lld_hsi2c_obj_t    *i2cObj;

    lldHsi2cAppCallback callbackFunPtr;

    void               *appCbData;
}lld_hsi2c_handle_t;

/* ========================================================================== */
/**
 *   lld_hsi2c_handle_arr holds the I2C handle parameters.
 */
/* ========================================================================== */
lld_hsi2c_handle_t lld_hsi2c_handle_arr[HSI2C_INST_MAX][HSI2C_NUM_OPENS];

/* ========================================================================== */
/**
 *   lld_hsi2c_obj_arr holds the I2C oject parameters.
 */
/* ========================================================================== */
lld_hsi2c_obj_t    lld_hsi2c_obj_arr[HSI2C_INST_MAX];

/******************************************************************************
 *                        PRIVATE FUNCTION DECLARATIONS
 ******************************************************************************/
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================= */
/**
 * @fn      lld_i2c_isr() Master ISR for all I2C instance
 *
 * @param   handle handle of the I2C
 *
 * @return  None
 *
 * @see
 */
/* ========================================================================= */
void lld_i2c_isr(void *arg);

/* ========================================================================= */
/**
 * @fn      lld_i2c_edmaCallback() Call back function to be registered with EDMA
 *          in DMA mode of operation.
 *
 * @return  None
 *
 * @see
 */
/* ========================================================================= */

void lld_i2c_edmaCallback(uint32_t tcc, LLD_hsi2cEdmaStatus i2cEdmaErrStatus,
                          void *arg);
#ifdef __cplusplus
}
#endif
/* ========================================================================= */
/**
 * @fn      lld_i2c_localEdmaChanRequest() requests edma channels.
 *          This function will be called from the lld_i2c_open function. This
 *          function requests the required edma channels.
 *
 * @param   handle    Pointer to the i2c driver instance handle
 *
 * @return  None
 *
 * @see
 */
/* ========================================================================= */
void lld_i2c_localEdmaChanRequest(hsI2cHandle handle);

/* ========================================================================= */
/**
 * @fn      lld_i2c_localEdmaTransfer() initiates Edma mode of operation
 *
 * @param   handle    Pointer to the i2c driver instance handle
 *
 * @return  LLD_hsi2cErrorCode_t status of the operation
 *
 * @see
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_localEdmaTransfer(hsI2cHandle handle);

void lld_hsi2c_udelay(uint32_t delay);

static LLD_hsi2cErrorCode_t lld_i2c_ctrlProbe(const lld_hsi2c_obj_t *instObj,
                                              uint8_t                slaveAddr);

static uint32_t lld_hsi2c_waitForPin(const lld_hsi2c_obj_t *instObj,
                                     uint32_t               flag,
                                     uint32_t               timeout,
                                     uint8_t               *timeOutStatus);

static LLD_hsi2cErrorCode_t lld_i2c_ctrlInit(const lld_hsi2c_obj_t *instObj);

static uint32_t lld_i2c_ctrledmaCallback(const lld_hsi2c_obj_t *instObj);

static LLD_hsi2cErrorCode_t lld_hsi2c_waitForBb(const lld_hsi2c_obj_t *instObj,
                                                uint32_t               timeout);

static LLD_hsi2cErrorCode_t lld_i2c_tranceiver(
    const lld_hsi2c_obj_t            *instObj,
    const lld_hsi2c_datatfr_params_t *i2cXferParams);

static void lld_i2c_isr_slave_transreceive(hsI2cHandle handle);

static void lld_i2c_isr_master(hsI2cHandle handle);

static LLD_hsi2cErrorCode_t lld_i2c_slavetranceiver(
    lld_hsi2c_handle_t              *i2cDrvObj,
    lld_hsi2c_obj_t                 *instObj,
    lld_hsi2c_transreceive_params_t *i2cXferParams);

static LLD_hsi2cErrorCode_t lld_i2c_validateArgsTransReceive(
    hsI2cHandle                      handle,
    lld_hsi2c_transreceive_params_t *i2cXferParams);

/******************************************************************************
 *                        API FUNCTION DEFINITIONS
 ******************************************************************************/

/* ========================================================================= */
/**
 * @fn      lld_i2c_init() Initializes i2c instance object properties.
 *          Read the application initialization parameters & initialize
 *          the data structure. Changes the state to created after successful
 *          initialization.
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_init(hsI2cObjHandle        *i2cObjHandle,
                                  LLD_Hsi2cInstId_t      numInstance,
                                  lld_hsi2c_initParam_t *initParams)
{
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj = NULL;

    static uint32_t      resetFlag = 0;

    /* Init all global variables to zero */
    if (resetFlag == 0)
    {
        memset(lld_hsi2c_obj_arr, 0, sizeof (lld_hsi2c_obj_arr));
        memset(lld_hsi2c_handle_arr, 0, sizeof (lld_hsi2c_handle_arr));

        resetFlag = 1U;
    }

    /* Validate arguments */
    if ((numInstance >= HSI2C_INST_MAX) || (NULL == initParams))
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    else
    {
        /* Validate initParams, leave bool ones */
        if ((initParams->i2cBusFreq < HSI2C_MIN_BUS_FREQ)
            || (initParams->i2cBusFreq > HSI2C_MAX_BUS_FREQ))
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        instObj = &lld_hsi2c_obj_arr[numInstance];

        instObj->initParam.isMasterMode = initParams->isMasterMode;
        instObj->initParam.opMode       = initParams->opMode;
        instObj->initParam.i2cBusFreq   = initParams->i2cBusFreq;
        instObj->initParam.is10BitAddr  = initParams->is10BitAddr;
        instObj->initParam.i2cOwnAddr   = initParams->i2cOwnAddr;
        instObj->initParam.i2cIntNum    = initParams->i2cIntNum;
        instObj->initParam.edmaParam    = initParams->edmaParam;
        if (initParams->i2cBusFreq > I2C_NORMAL)
        {
            instObj->i2cIclk = 12000000; /* 12 MHz */
        }
        else
        {
            instObj->i2cIclk = 4000000;  /* 4 MHz */
        }
        instObj->busFreq = instObj->initParam.i2cBusFreq;
        *i2cObjHandle    = (hsI2cObjHandle *) instObj;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Everything went fine, change state and instanceId */
        instObj->state    = LLD_HSI2C_INST_CREATED;
        instObj->instNum  = numInstance;
        instObj->numOpens = 0;

        switch (instObj->instNum)
        {
            case HSI2C_INST_0:
                instObj->baseAddr = SOC_I2C1_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_0_MODULE_FREQ;
                break;
            case HSI2C_INST_1:
                instObj->baseAddr = SOC_I2C2_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_1_MODULE_FREQ;
                break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
            case HSI2C_INST_2:
                instObj->baseAddr = SOC_I2C3_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_2_MODULE_FREQ;
                break;
            case HSI2C_INST_3:
                instObj->baseAddr = SOC_I2C4_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_3_MODULE_FREQ;
                break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            case HSI2C_INST_4:
                instObj->baseAddr = SOC_I2C5_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_4_MODULE_FREQ;
                break;
#if defined (SOC_TDA2EX)
            case HSI2C_INST_5:
                instObj->baseAddr = SOC_I2C6_BASE;
                instObj->i2cFclk  = (uint32_t) CSL_I2C_5_MODULE_FREQ;
                break;
#endif
#endif
            default:
                retVal = LLD_HSI2C_BADARGS;
                break;
        }
        instObj->initParam.i2cIsr = &lld_i2c_isr;
        initParams->i2cIsr        = &lld_i2c_isr;
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_deinit() closes all the handles and clears the instance
 *          for the instance number passed
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_deinit(LLD_Hsi2cInstId_t numInstance)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t cnt;

    if (numInstance < HSI2C_INST_MAX)
    {
        /* clear all the handles of I2C instance*/
        for (cnt = 0; cnt < HSI2C_NUM_OPENS; cnt++)
        {
            if (NULL != lld_hsi2c_handle_arr[numInstance][cnt].i2cObj)
            {
                lld_hsi2c_handle_arr[numInstance][cnt].i2cObj = NULL;
            }
        }

        /* clear the I2C instance*/
        memset(&lld_hsi2c_obj_arr[numInstance], 0,
               sizeof (lld_hsi2c_obj_arr[numInstance]));
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_ctrlInit() API initializes I2C module
 *
 * @see     struct       hal_hsi2c.h
 *
 */
/* ========================================================================= */
static LLD_hsi2cErrorCode_t lld_i2c_ctrlInit(const lld_hsi2c_obj_t *instObj)
{
    uint32_t             delay = 50U;
    uint32_t             busFrequency;
    lld_i2c_busspeed     busFreq = I2C_NORMAL;
    uint32_t             regVal;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    /* Do a software reset */
    I2CSoftReset(instObj->baseAddr);

    /* Enable i2c module */
    I2CMasterEnable(instObj->baseAddr);

    /* Wait for the reset to get complete  -- constant delay - 50ms */
    while ((I2CSystemStatusGet(instObj->baseAddr) == 0) && (delay != 0))
    {
        delay--;
        lld_hsi2c_udelay(HSI2C_DELAY_SMALL);
    }

    if (delay == 0)
    {
        /* reset has failed, return!!! */
        retVal = LLD_HSI2C_ETIMEOUT;
    }
    else
    {
        /* Put i2c in reset/disabled state */
        I2CMasterDisable(instObj->baseAddr);

        /* Configure i2c bus speed*/
        lld_i2c_getBusFreq(instObj->instNum, &busFreq);
        busFrequency = (uint32_t) busFreq * 1000U;

        I2CMasterInitExpClk(instObj->baseAddr, lld_i2c_getFclk(instObj->instNum),
                            lld_i2c_getIclk(instObj->instNum), busFrequency);

        /*Set Own address*/
        I2COwnAddressSet(instObj->baseAddr, instObj->initParam.i2cOwnAddr,
                         I2C_OWN_ADDR_0);

        /**
         * Configure I2C_SYSC params
         * Disable auto idle mode
         * Both OCP and systen clock cut off
         * Wake up mechanism disabled
         * No idle mode selected
         */
        regVal = I2C_AUTOIDLE_DISABLE | I2C_CUT_OFF_BOTH_CLK |
                 I2C_ENAWAKEUP_DISABLE | I2C_NO_IDLE_MODE;
        I2CSyscInit(instObj->baseAddr, regVal);

        /**
         * Configure I2C_CON params
         * Select Fast/standard mode
         * Select normal mode
         * Select 7 bit slave address mode
         * Select 7 bit own address mode
         * Enable I2C module
         */
        regVal = I2C_OPMODE_FAST_STAND_MODE | I2C_NORMAL_MODE;
        if (instObj->initParam.is10BitAddr)
        {
            regVal |= I2C_XSA_10BIT;
        }

        I2CConfig(instObj->baseAddr, regVal);

        /*Set Rx and Tx FIFO threshold value and reset the fifo*/
        I2CFIFOThresholdConfig(instObj->baseAddr, instObj->txThreshold,
                               I2C_TX_MODE);

        I2CFIFOThresholdConfig(instObj->baseAddr, instObj->rxThreshold,
                               I2C_RX_MODE);

        /* High speed configuration */
        if (instObj->initParam.i2cBusFreq > 400)
        {
            I2CMasterControl(instObj->baseAddr, (uint32_t) I2C_CON_OPMODE_HSI2C);
        }

        if (instObj->initParam.is10BitAddr)
        {
            I2CMasterControl(instObj->baseAddr, (uint32_t) I2C_CON_XSA_B10);
        }

        /* Take the I2C module out of reset: */
        I2CMasterEnable(instObj->baseAddr);

        /* Enable free run mode */
        I2CMasterEnableFreeRun(instObj->baseAddr);
    }

    /*Clear status register */
    I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_resetCtrl() resets the i2c controller
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_resetCtrl(hsI2cHandle handle)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS; /* default = fail */
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    if (NULL == handle)
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;
        instObj   = i2cDrvObj->i2cObj;
        if (NULL == instObj)
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        retVal = lld_i2c_ctrlInit(instObj);
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_open() creates the handle for I2C port for a open.
 *          There can be maximum of HSI2C_NUM_OPENS opens
 *          Initialize the hardware port & change the state to open
 *          Funtion is not Re-entrant. Please use semaphore in the application
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
hsI2cHandle lld_i2c_open(LLD_Hsi2cInstId_t   instanceId,
                         lldHsi2cAppCallback appCallback,
                         void               *appData)
{
    uint32_t cnt;
    LLD_hsi2cErrorCode_t retVal      = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj     = NULL;
    lld_hsi2c_handle_t  *hsi2cHandle = NULL;
    lld_hsi2c_obj_t     *tempInstObj   = NULL;
    lld_hsi2c_handle_t  *tempI2cDrvObj = NULL;

    if (instanceId < HSI2C_INST_MAX)
    {
        instObj = &lld_hsi2c_obj_arr[instanceId];
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        /* Verify the state first.
         * If no driver object is opened and this is the first one,
         * then state should be created/closed.
         */
        if ((((uint8_t) 0 == instObj->numOpens) &&
             (instObj->state != LLD_HSI2C_INST_CREATED))
            && (instObj->state != LLD_HSI2C_INST_CLOSED))
        {
            retVal = LLD_HSI2C_BADARGS;
        }
        else
        {
            if (((instObj->numOpens != 0) &&
                 (instObj->numOpens < HSI2C_NUM_OPENS))
                && (instObj->state != LLD_HSI2C_INST_OPENED))
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        for (cnt = 0; cnt < HSI2C_NUM_OPENS; cnt++)
        {
            if (NULL == lld_hsi2c_handle_arr[instanceId][cnt].i2cObj)
            {
                /* Free handle found, allocate it */
                lld_hsi2c_handle_arr[instanceId][cnt].i2cObj = instObj;

                /* Callback/appData not used currently */
                lld_hsi2c_handle_arr[instanceId][cnt].callbackFunPtr =
                    appCallback;
                lld_hsi2c_handle_arr[instanceId][cnt].appCbData =
                    appData;
                /* Read the handle*/
                hsi2cHandle = &lld_hsi2c_handle_arr[instanceId][cnt];

                break;
            }
        }
        if (HSI2C_NUM_OPENS == cnt)
        {
            retVal = LLD_HSI2C_HANDLE_UNAVAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        if (NULL != hsi2cHandle)
        {
            /* Initialize hardware for the first open */
            if (0 == instObj->numOpens)
            {
                retVal = lld_i2c_ctrlInit(instObj);

                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    if (HSI2C_OPMODE_DMA == instObj->initParam.opMode)
                    {
                        switch (instObj->instNum)
                        {
                            case HSI2C_INST_0:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT0;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT0;
                                break;

                            case HSI2C_INST_1:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT1;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT1;
                                break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
                            case HSI2C_INST_2:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT2;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT2;
                                break;

                            case HSI2C_INST_3:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT3;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT3;
                                break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
                            case HSI2C_INST_4:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT4;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT4;
                                break;
#if defined (SOC_TDA2EX)
                            case HSI2C_INST_5:
                                instObj->txDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CTXEVT5;
                                instObj->rxDmaEventNumber =
                                    LLD_I2C_EDMA_CHA_I2CRXEVT5;
                                break;
#endif
#endif

                            default:
                                retVal = LLD_HSI2C_BADARGS;
                                break;
                        }

                        tempI2cDrvObj = (lld_hsi2c_handle_t *) hsi2cHandle;
                        tempInstObj = tempI2cDrvObj->i2cObj;
                        if (tempInstObj->initParam.edmaParam == NULL)
                        {
                            retVal = LLD_HSI2C_FAIL;
                        }
                        else
                        {
                            if (instObj->dmaChaAllocated == FALSE)
                            {
                                /* CPUSwitchToPrivilegedMode();*/
                                lld_i2c_localEdmaChanRequest(hsi2cHandle);
                                /* CPUSwitchToUserMode(); */
                            }
                            if (FALSE == instObj->dmaChaAllocated)
                            {
                                retVal = LLD_HSI2C_FAIL;
                            }
                        }
                    }
                }
                else
                {
                    retVal = LLD_HSI2C_FAIL;
                }
            }
        }
    }

    if ((NULL != hsi2cHandle) && (LLD_HSI2C_SUCCESS == retVal))
    {
        /* Increment open count */
        instObj->numOpens++;
        /* Update the instance object state */
        if (LLD_HSI2C_INST_OPENED != instObj->state)
        {
            instObj->state = LLD_HSI2C_INST_OPENED;
        }
    }
    else
    {
        hsi2cHandle = NULL;
    }

    return (hsI2cHandle) hsi2cHandle;
}

/* ========================================================================= */
/**
 * @fn         lld_i2c_localEdmaChanRequest() requests edma channels.
 *             This function will be called from the lld_i2c_open function. This
 *             function requests the required edma channels.
 *
 * @see        lld_hsi2c.c
 */
/* ========================================================================= */
void lld_i2c_localEdmaChanRequest(hsI2cHandle handle)
{
    LLD_hsi2cErrorCode_t status     = LLD_HSI2C_SUCCESS;
    LLD_hsi2cEdmaStatus  edmaStatus = EDMA_TRANSFER_SUCCESS;

    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    if (NULL == handle)
    {
        status = LLD_HSI2C_BADARGS;
        /*printf("\r\nInvalid Handle");*/
    }

    if (LLD_HSI2C_SUCCESS == status)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                status = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            status = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == status)
    {
        /* request for RX DMA channels
         *                                           */
        edmaStatus =
            EDMA_requestChannel(handle, &(instObj->rxDmaEventNumber),
                                lld_i2c_edmaCallback,
                                instObj->initParam.edmaParam);

        if (EDMA_TRANSFER_SUCCESS == edmaStatus)
        {
            /* request for TX DMA channels
             *                                       */
            edmaStatus =
                EDMA_requestChannel(handle, &(instObj->txDmaEventNumber),
                                    lld_i2c_edmaCallback,
                                    instObj->initParam.edmaParam);
        }
        else
        {
            /* Failed to allocated the channel hence free the already allocated
             *   *
             * channel
             *                                                           */
            EDMA_freeChannel(instObj->rxDmaEventNumber,
                             instObj->initParam.edmaParam);
            status = LLD_HSI2C_FAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == status)
    {
        /* set the status of DMA channels as allocated                        */
        instObj->dmaChaAllocated = (uint16_t) TRUE;
    }
    else
    {
        /* printf("\r\n Edma channel request failed"); */
    }
}

static uint32_t lld_i2c_ctrledmaCallback(const lld_hsi2c_obj_t *instObj)
{
    volatile uint32_t delay  = 0;
    uint32_t          retVal = 0;
    uint32_t          stat, w;

    /* Read the status*/
    delay = instObj->dataTfrParam.timeout;

    stat = I2CMasterIntRawStatus(instObj->baseAddr);

    do
    {
        if (((stat & I2C_INT_BUS_BUSY) != 0) ||
            ((stat & I2C_INT_ADRR_READY_ACESS) == 0))
        {
            stat = I2CMasterIntRawStatus(instObj->baseAddr);
        }
        else
        {
            break;
        }
        delay--;
    } while (delay > 0);

    if (delay == 0)
    {
        retVal |= I2C_INT_BUS_BUSY;
    }

    if (instObj->dataTfrParam.flags & LLD_HSI2C_WRITE)
    {
        I2CDMATxEventDisable(instObj->baseAddr);
    }
    else
    {
        I2CDMARxEventDisable(instObj->baseAddr);
    }

    /* Check for NACK*/
    if (stat & I2C_INT_NO_ACK)
    {
        retVal |= I2C_INT_NO_ACK;
        if (instObj->dataTfrParam.flags & LLD_HSI2C_STOP)
        {
            I2CMasterStop(instObj->baseAddr);
        }
    }

    /* Check for Arbitration Loss*/
    if (stat & I2C_INT_ARBITRATION_LOST)
    {
        /*printf (" I2C: Arbitration lost !!!\r\n");*/
        retVal |= I2C_INT_ARBITRATION_LOST;
    }

    /**/
    if (stat & (I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                I2C_INT_ARBITRATION_LOST))
    {
        retVal |= I2C_INT_ADRR_READY_ACESS;

        if (instObj->dataTfrParam.flags & LLD_HSI2C_STOP)
        {
            I2CFlushFifo(instObj->baseAddr);

            /*Clear data buffer length*/
            I2CSetDataCount(instObj->baseAddr, 0);

            /*Set the default threshold value after doing transfer with transfer
             *length less than threshold value */
            if ((instObj->dataTfrParam.bufLen <= instObj->rxThreshold) ||
                (instObj->dataTfrParam.bufLen <= instObj->txThreshold))
            {
                if (instObj->dataTfrParam.flags & LLD_HSI2C_WRITE)
                {
                    /*Set Tx FIFO threshold value and reset the fifo*/
                    I2CFIFOThresholdConfig(instObj->baseAddr,
                                           instObj->txThreshold,
                                           I2C_TX_MODE);
                }
                else
                {
                    /*Set Rx FIFO threshold value and reset the fifo*/
                    I2CFIFOThresholdConfig(instObj->baseAddr,
                                           instObj->rxThreshold,
                                           I2C_RX_MODE);
                }
            }
        }

        w = stat & (I2C_INT_RECV_READY | I2C_INT_RECV_DRAIN |
                    I2C_INT_TRANSMIT_READY | I2C_INT_TRANSMIT_DRAIN);
        I2CMasterIntClearEx(instObj->baseAddr, w);
    }

    return retVal;
}

void lld_i2c_edmaCallback(uint32_t tcc, LLD_hsi2cEdmaStatus i2cEdmaErrStatus,
                          void *arg)
{
    uint32_t             tfrStatus = 0;
    LLD_hsi2cErrorCode_t errStatus = LLD_HSI2C_FAIL;
    hsI2cHandle          hsi2cHandle;
    lld_hsi2c_obj_t     *instObj        = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj      = NULL;
    uint32_t             stat           = 0;
    uint32_t             remainingBytes = 0;
    uint8_t w = 0;
    uint8_t             *remBuffer = NULL;
    uint8_t timeOutStatus          = 0;

    hsi2cHandle = (hsI2cHandle) arg;
    i2cDrvObj   = (lld_hsi2c_handle_t *) hsi2cHandle;
    if (NULL != i2cDrvObj)
    {
        instObj = (lld_hsi2c_obj_t *) i2cDrvObj->i2cObj;
    }

    if ((NULL != i2cDrvObj) && (NULL != instObj))
    {
        if (instObj->dataTfrParam.flags & LLD_HSI2C_WRITE)
        {
            if ((instObj->dataTfrParam.bufLen > (instObj->txThreshold + 1)))
            {
                if ((instObj->dataTfrParam.bufLen %
                     (instObj->txThreshold + 1)) !=
                    0)
                {
                    stat = lld_hsi2c_waitForPin(instObj, I2C_INT_TRANSMIT_DRAIN,
                                                instObj->dataTfrParam.timeout,
                                                &timeOutStatus);
                }
            }
        }
        else
        {
            if ((instObj->dataTfrParam.bufLen > (instObj->rxThreshold + 1)))
            {
                if ((instObj->dataTfrParam.bufLen %
                     (instObj->rxThreshold + 1)) !=
                    0)
                {
                    stat = lld_hsi2c_waitForPin(instObj, I2C_INT_RECV_DRAIN,
                                                instObj->dataTfrParam.timeout,
                                                &timeOutStatus);
                }
            }
        }

        if (0 == timeOutStatus)
        {
            if (stat & I2C_INT_RECV_DRAIN)
            {
                remainingBytes = I2CBufferStatus(instObj->baseAddr,
                                                 I2C_RX_BUFFER_STATUS);

                remBuffer = instObj->dataTfrParam.buffer +
                            (instObj->dataTfrParam.bufLen - remainingBytes);
                for (; remainingBytes > 0; remainingBytes--)
                {
                    w = I2CMasterDataGet(instObj->baseAddr);

                    if (instObj->dataTfrParam.bufLen)
                    {
                        *remBuffer = (uint8_t) w;
                        remBuffer++;
                    }
                    else
                    {
                        /*printf("Rx IRQ while no data requested")*/
                    }
                }

                I2CMasterIntClearEx(instObj->baseAddr,
                                    (stat & I2C_INT_RECV_DRAIN));
            }

            if (stat & I2C_INT_TRANSMIT_DRAIN)
            {
                remainingBytes = I2CBufferStatus(instObj->baseAddr,
                                                 I2C_TX_BUFFER_STATUS);

                remBuffer = instObj->dataTfrParam.buffer +
                            (instObj->dataTfrParam.bufLen - remainingBytes);
                for (; remainingBytes > 0; remainingBytes--)
                {
                    w = 0;
                    if (instObj->dataTfrParam.bufLen)
                    {
                        w = *remBuffer;
                        remBuffer++;
                    }
                    else
                    {
                        /*printf("Tx IRQ while no data to send")*/
                    }

                    I2CMasterDataPut(instObj->baseAddr, w);
                }

                I2CMasterIntClearEx(instObj->baseAddr,
                                    (stat & I2C_INT_TRANSMIT_DRAIN));
            }
        }
        else
        {
            instObj->state = LLD_HSI2C_INST_ERROR;
            errStatus      = LLD_HSI2C_FAIL;
        }

        tfrStatus = lld_i2c_ctrledmaCallback(instObj);

        EDMA_disableLogicalChannel(tcc, instObj->initParam.edmaParam);

        if (EDMA_TRANSFER_SUCCESS == i2cEdmaErrStatus)
        {
            instObj->state = LLD_HSI2C_INST_OPENED;
        }
        else
        {
            instObj->state = LLD_HSI2C_INST_ERROR;

            /* Ensure to clear the error bits of EDMA channel             */
            EDMA_clearErrorBits(tcc, instObj->initParam.edmaParam);
        }

        if (tfrStatus & I2C_INT_BUS_BUSY)
        {
            instObj->state = LLD_HSI2C_INST_ERROR;
            errStatus      = LLD_HSI2C_BUS_BUSY_ERR;
        }
        else if (tfrStatus & I2C_INT_NO_ACK)
        {
            instObj->state = LLD_HSI2C_INST_ERROR;
            errStatus      = LLD_HSI2C_NACK_ERR;
        }
        else if (tfrStatus & I2C_INT_ARBITRATION_LOST)
        {
            instObj->state = LLD_HSI2C_INST_ERROR;
            errStatus      = LLD_HSI2C_ARBITRATION_LOSS_ERR;
        }
        else if (tfrStatus & I2C_INT_ADRR_READY_ACESS)
        {
            instObj->state = LLD_HSI2C_INST_OPENED;
            errStatus      = LLD_HSI2C_SUCCESS;
        }
        else
        {
            /*
             * tfrStatus cannot have any other state except the above four
             * Hence this else condition is never hit
             */
        }
        if (tfrStatus & (I2C_INT_NO_ACK |
                         I2C_INT_ARBITRATION_LOST |
                         I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_BUSY))
        {
            i2cDrvObj->callbackFunPtr((hsI2cHandle) hsi2cHandle, errStatus,
                                      i2cDrvObj->appCbData);
        }
    }
    else
    {
        if (NULL != instObj)
        {
            instObj->state = LLD_HSI2C_INST_ERROR;
        }
        errStatus = LLD_HSI2C_BUS_BUSY_ERR;
    }
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_close() closes the handle for I2C port for a open.
 *          Decreaments number of open handles. Changes the state of object
 *          to CLOSED. Clears the handle
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_close(hsI2cHandle *handle)
{
    LLD_hsi2cErrorCode_t retVal      = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj     = NULL;
    lld_hsi2c_handle_t  *hsi2cHandle = NULL;

    hsi2cHandle = (lld_hsi2c_handle_t *) (*handle);

    /* check the status*/
    if ((NULL != hsi2cHandle) && (NULL != hsi2cHandle->i2cObj))
    {
        instObj = &lld_hsi2c_obj_arr[hsi2cHandle->i2cObj->instNum];

        if (0 == instObj->numOpens)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }
    else
    {
        retVal = LLD_HSI2C_FAIL;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* reduce the numerOpens*/
        instObj->numOpens--;
        if (0 == instObj->numOpens)
        {
            instObj->dmaChaAllocated = (uint16_t) FALSE;

            /* Set the state of the object to closed*/
            instObj->state = LLD_HSI2C_INST_CLOSED;

            /* Clear the handle*/
            hsi2cHandle->i2cObj = NULL;
        }
        *handle = NULL;
    }

    return retVal;
}

void lld_i2c_isr(void *arg)
{
    hsI2cHandle         handle;
    lld_hsi2c_obj_t    *instObj   = NULL;
    lld_hsi2c_handle_t *i2cDrvObj = NULL;

    handle    = (hsI2cHandle) arg;
    i2cDrvObj = (lld_hsi2c_handle_t *) handle;
    instObj   = (lld_hsi2c_obj_t *) i2cDrvObj->i2cObj;

    if (instObj->initParam.isMasterMode == LLD_HSI2C_MODE_SLAVE_TRANSRECEIVE)
    {
        lld_i2c_isr_slave_transreceive(handle);
    }
    else
    {
        lld_i2c_isr_master(handle);
    }
}

static void lld_i2c_isr_slave_transreceive(hsI2cHandle handle)
{
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;
    uint32_t intStat, rawStat, i, bytesToProcess;
    lld_hsi2c_transreceive_params_t *i2cXferParams;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t regVal;

    i2cDrvObj     = (lld_hsi2c_handle_t *) handle;
    instObj       = (lld_hsi2c_obj_t *) i2cDrvObj->i2cObj;
    i2cXferParams = instObj->i2cXferParams;

    /*
     *  ISR Handling of different events is as below in same order:
     *  1.  RRDY: Handle receive ready interrupt before AAS or ARDY interrupt,
     *      as If ISR delayed and restart or stop condition received then
     *      the data should be read first.
     *  2.  ARDY: In case of stop condition bus busy will be reset. If it is a
     *      restart condition bus busy will still be set.
     *  3.  AAS: In case of addressed as slave after transfer is initiated, it
     *      is a restat condition. Give the restart callback.
     *  4.  XRDY: Read application tx buffer and send data.
     *
     *  In case of restart hold the bus low till application gives next buffer.
     *  If the Buffers are overflowing or underflowing return error code
     *  accordingly. Application should call the abort transfer explicitly.
     */
    rawStat = I2CMasterIntRawStatus(instObj->baseAddr);
    intStat = I2CSlaveIntStatus(instObj->baseAddr);

    if (instObj->state == LLD_HSI2C_INST_OPENED)
    {
        I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
    }

    if ((i2cXferParams != NULL) && (((intStat & I2C_INT_RECV_READY) != 0U) ||
                                    ((intStat & I2C_INT_RECV_DRAIN) != 0U)))
    {
        if (instObj->state == LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED)
        {
            uint32_t rxBufStat = I2CBufferStatus(instObj->baseAddr,
                                                 I2C_RX_BUFFER_STATUS);
            if ((intStat & I2C_INT_RECV_DRAIN) != 0U)
            {
                bytesToProcess = rxBufStat;
            }
            else
            {
                bytesToProcess = ((uint32_t) instObj->rxThreshold + 1U);
            }
            for (i = 0; i < bytesToProcess; i++)
            {
                /* Read from Rx register only when current transaction is
                 *ongoing */
                if ((i2cXferParams->processedRxBufLen <
                     i2cXferParams->rxBufLen) ||
                    ((i2cXferParams->flags & LLD_HSI2C_OVERWRITE_RX_BUF) != 0U))
                {
                    i2cXferParams->rxBuffer[(i2cXferParams->processedRxBufLen %
                                             i2cXferParams->rxBufLen)] =
                        I2CMasterDataGet(instObj->baseAddr);
                    i2cXferParams->processedRxBufLen++;
                    I2CMasterIntClearEx(instObj->baseAddr,
                                        I2C_INT_RECV_READY | I2C_INT_RECV_DRAIN);
                }
                else
                {
                    retVal = LLD_HSI2C_RECEIVE_OVERFLOW_ERR;
                    i2cXferParams->transferStatus =
                        LLD_HSI2C_RECEIVE_OVERFLOW_ERR;
                    instObj->i2cXferParams = NULL;
                    instObj->state         = LLD_HSI2C_INST_OPENED;
                    i2cDrvObj->callbackFunPtr(handle, retVal,
                                              i2cDrvObj->appCbData);
                    break;
                }
            }
        }
    }

    if ((i2cXferParams != NULL) && ((intStat & I2C_INT_ADRR_READY_ACESS) != 0))
    {
        if ((rawStat & I2C_INT_BUS_BUSY) != 0)
        {
            /* Clear Interrupt, Callback will be handled in ADDR_SLAVE */
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ADRR_READY_ACESS);
        }
        else
        {
            /* This is end of current transfer */
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
            retVal = LLD_HSI2C_SUCCESS;
            i2cXferParams->transferStatus = LLD_HSI2C_SUCCESS;
            /* Flush FIFO */
            I2CFlushFifo(instObj->baseAddr);
            I2CMasterIntDisableEx(instObj->baseAddr, I2C_INT_ALL);
            instObj->i2cXferParams = NULL;
            instObj->state         = LLD_HSI2C_INST_OPENED;
            i2cDrvObj->callbackFunPtr(handle, retVal, i2cDrvObj->appCbData);
        }
    }

    if ((i2cXferParams != NULL) && ((intStat & I2C_INT_ADRR_SLAVE) != 0))
    {
        if (instObj->state == LLD_HSI2C_INST_BUSY_SLAVE_TFR_NOT_STARTED)
        {
            /* This is the first transfer initiation from master */
            /* Update the state to transfer started and Clear the Interrupt */
            instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED;
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ADRR_SLAVE);
        }
        else if (instObj->state == LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED)
        {
            /* This is a restart condition, Give callback to app */
            if ((rawStat & I2C_INT_TRANSMIT_UNDER_FLOW) != 0)
            {
                i2cXferParams->transferStatus = LLD_HSI2C_SLAVE_TX_PENDING;
                retVal = LLD_HSI2C_SUCCESS;
            }
            else
            {
                i2cXferParams->transferStatus = LLD_HSI2C_SLAVE_RX_PENDING;
                retVal = LLD_HSI2C_SUCCESS;
            }

            if (i2cXferParams->txRxRestartCb != NULL)
            {
                instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_HOLD;
                i2cXferParams->txRxRestartCb(handle, (void *) i2cXferParams);
                if (instObj->i2cXferParams->transferStatus ==
                    LLD_HSI2C_SLAVE_BUFFER_UPDATED)
                {
                    /* Buffer was updated in the callback. */
                    instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED;
                    instObj->i2cXferParams->processedTxBufLen = 0;
                    instObj->i2cXferParams->processedRxBufLen = 0;
                }
                else
                {
                    /* Buffer was not updated. Complete the current transaction
                     * call the completion App Callback. Transfer will continue
                     * in the next transaction */
                    instObj->i2cXferParams = NULL;
                    /* Disable the transmit ready, receive ready and
                     * receive drain interrupts.
                     * Otherwise the ISRs keep getting called again and again
                     * but driver cant process this until application initiates
                     * new transaction with the buffer, which could happen in
                     * task context. */
                    regVal = I2CGetEnabledIntStatus(instObj->baseAddr,
                                                    I2C_INT_ALL);
                    regVal = regVal & (~(I2C_INT_TRANSMIT_READY |
                                         I2C_INT_RECV_READY |
                                         I2C_INT_RECV_DRAIN));
                    I2CMasterIntEnableEx(instObj->baseAddr, regVal);
                    I2CMasterIntDisableEx(instObj->baseAddr, ~(regVal));
                    i2cDrvObj->callbackFunPtr(handle, retVal,
                                              i2cDrvObj->appCbData);
                }
            }
            else
            {
                instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_HOLD;
                /* Restart callback function not present. complete the current
                 * transaction by calling  the completion App Callback.
                 * Transfer will continue in the next transaction */
                instObj->i2cXferParams = NULL;
                i2cDrvObj->callbackFunPtr(handle, retVal, i2cDrvObj->appCbData);
            }
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ADRR_SLAVE);
        }
        else
        {
            /* Control should not come here. Sphurious interrupt clear it. */
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ADRR_SLAVE);
        }
    }

    if ((i2cXferParams != NULL) && ((intStat & I2C_INT_TRANSMIT_READY) != 0U))
    {
        if (instObj->state == LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED)
        {
            for (i = 0; i < ((uint32_t) instObj->txThreshold + 1U); i++)
            {
                if ((i2cXferParams->processedTxBufLen <
                     i2cXferParams->txBufLen) ||
                    ((i2cXferParams->flags & LLD_HSI2C_REPEAT_TX_BUF) != 0U))
                {
                    I2CMasterDataPut(
                        instObj->baseAddr, i2cXferParams->txBuffer[
                            (i2cXferParams->processedTxBufLen %
                             i2cXferParams->txBufLen)]);
                    i2cXferParams->processedTxBufLen++;
                    I2CMasterIntClearEx(instObj->baseAddr,
                                        I2C_INT_TRANSMIT_READY);
                }
                else if (i == 0)
                {
                    retVal = LLD_HSI2C_TRANSMIT_UNDERFLOW_ERR;
                    i2cXferParams->transferStatus =
                        LLD_HSI2C_TRANSMIT_UNDERFLOW_ERR;
                    instObj->i2cXferParams = NULL;
                    instObj->state         = LLD_HSI2C_INST_OPENED;
                    i2cDrvObj->callbackFunPtr(handle, retVal,
                                              i2cDrvObj->appCbData);
                }
                else
                {
                    /* This is not error condition.
                     * We have written last few bytes in Tx FIFO. */
                }
            }
        }
    }
}

static void lld_i2c_isr_master(hsI2cHandle handle)
{
    LLD_hsi2cErrorCode_t errStatus = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    uint32_t isrLoopCount = 0;
    uint32_t w;
    uint32_t stat;
    uint32_t rawStat;
    uint8_t  fifoThreshold;

    uint32_t retVal         = 0;
    uint32_t remainingBytes = 0;

    i2cDrvObj = (lld_hsi2c_handle_t *) handle;
    instObj   = (lld_hsi2c_obj_t *) i2cDrvObj->i2cObj;

    /*
     * Ack the stat in one go, but [R/X]DR and [R/X]RDY should be
     * acked after the data operation is complete.
     */

    if (LLD_HSI2C_INST_BUSY == instObj->state)
    {
        /* Keep looping till there are no pending interrupts.
         * This allows I2C_INT_ADRR_READY_ACESS to be processed in same ISR
         * as I2C_INT_RECV_READY/I2C_INT_RECV_DRAIN and reduce interrupt
         * count.
         * This also reduces additional interrupt if Rx is followed by Tx
         * and application calls Tx from within the callback from within
         * callback function called during I2C_INT_ADRR_READY_ACESS event.
         */
        while (1)
        {
            stat = I2CMasterIntStatus(instObj->baseAddr);

            if ((0U == stat) || (isrLoopCount > MAX_CONSECUTIVE_ISRS))
            {
                break;
            }
            isrLoopCount++;

            rawStat = I2CMasterIntRawStatus(instObj->baseAddr);
            w       = stat & ~(I2C_INT_RECV_READY | I2C_INT_RECV_DRAIN |
                               I2C_INT_TRANSMIT_READY | I2C_INT_TRANSMIT_DRAIN);
            I2CMasterIntClearEx(instObj->baseAddr, w);

            if (stat & I2C_INT_ADRR_READY_ACESS)
            {
                if (rawStat & I2C_INT_NO_ACK)
                {
                    retVal   |= I2C_INT_NO_ACK;
                    errStatus = LLD_HSI2C_NACK_ERR;
                    I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_NO_ACK);
                    I2CMasterStop(instObj->baseAddr);
                }
                if (rawStat & I2C_INT_ARBITRATION_LOST)
                {
                    I2CMasterIntClearEx(instObj->baseAddr,
                                        I2C_INT_ARBITRATION_LOST);
                    retVal   |= I2C_INT_ARBITRATION_LOST;
                    errStatus = LLD_HSI2C_ARBITRATION_LOSS_ERR;
                }
                if (errStatus != LLD_HSI2C_SUCCESS)
                {
                    retVal |= I2C_INT_ADRR_READY_ACESS;
                }
                if (instObj->dataTfrParam.flags & LLD_HSI2C_STOP)
                {
                    I2CFlushFifo(instObj->baseAddr);

                    /*Clear data buffer length*/
                    I2CSetDataCount(instObj->baseAddr, 0);
                }
                w = stat & (I2C_INT_RECV_READY | I2C_INT_RECV_DRAIN |
                            I2C_INT_TRANSMIT_READY | I2C_INT_TRANSMIT_DRAIN);

                I2CMasterIntClearEx(instObj->baseAddr, w);
                instObj->state = LLD_HSI2C_INST_OPENED;
                I2CMasterIntDisableEx(instObj->baseAddr, I2C_INT_ALL);
                i2cDrvObj->callbackFunPtr(handle,
                                          errStatus,
                                          i2cDrvObj->appCbData);
            }

            if (0U == retVal)
            {
                if (stat & I2C_INT_RECV_READY)
                {
                    for (fifoThreshold = 0;
                         fifoThreshold < (instObj->rxThreshold + (uint8_t) 1U);
                         fifoThreshold++)
                    {
                        w = (uint32_t) I2CMasterDataGet(instObj->baseAddr);

                        if (instObj->dataTfrParam.bufLen)
                        {
                            *instObj->dataTfrParam.buffer = (uint8_t) w;
                            instObj->dataTfrParam.buffer++;
                            instObj->dataTfrParam.bufLen--;
                        }
                        else
                        {
                            /*printf("Rx IRQ while no data requested")*/
                        }
                    }

                    I2CMasterIntClearEx(instObj->baseAddr,
                                        (stat & I2C_INT_RECV_READY));
                }

                if (stat & I2C_INT_RECV_DRAIN)
                {
                    remainingBytes = I2CBufferStatus(instObj->baseAddr,
                                                     I2C_RX_BUFFER_STATUS);

                    for (; remainingBytes > 0; remainingBytes--)
                    {
                        w = (uint32_t) I2CMasterDataGet(instObj->baseAddr);

                        if (instObj->dataTfrParam.bufLen)
                        {
                            *instObj->dataTfrParam.buffer = (uint8_t) w;
                            instObj->dataTfrParam.buffer++;
                            instObj->dataTfrParam.bufLen--;
                        }
                        else
                        {
                            /*printf("Rx IRQ while no data requested")*/
                        }
                    }

                    I2CMasterIntClearEx(instObj->baseAddr,
                                        (stat & I2C_INT_RECV_DRAIN));
                }

                if (stat & I2C_INT_TRANSMIT_READY)
                {
                    for (fifoThreshold = 0;
                         fifoThreshold < (instObj->txThreshold + (uint8_t) 1U);
                         fifoThreshold++)
                    {
                        w = 0;
                        if (instObj->dataTfrParam.bufLen)
                        {
                            w = *instObj->dataTfrParam.buffer;
                            instObj->dataTfrParam.buffer++;
                            instObj->dataTfrParam.bufLen--;
                        }
                        else
                        {
                            /*printf("Tx IRQ while no data to send")*/
                        }

                        I2CMasterDataPut(instObj->baseAddr, (uint8_t) w);
                    }

                    I2CMasterIntClearEx(instObj->baseAddr,
                                        (stat & I2C_INT_TRANSMIT_READY));
                }

                if (stat & I2C_INT_TRANSMIT_DRAIN)
                {
                    remainingBytes = I2CBufferStatus(instObj->baseAddr,
                                                     I2C_TX_BUFFER_STATUS);

                    for (; remainingBytes > 0; remainingBytes--)
                    {
                        w = 0;
                        if (instObj->dataTfrParam.bufLen)
                        {
                            w = *instObj->dataTfrParam.buffer;
                            instObj->dataTfrParam.buffer++;
                            instObj->dataTfrParam.bufLen--;
                        }
                        else
                        {
                            /*printf("Tx IRQ while no data to send")*/
                        }

                        I2CMasterDataPut(instObj->baseAddr, (uint8_t) w);
                    }

                    I2CMasterIntClearEx(instObj->baseAddr,
                                        (stat & I2C_INT_TRANSMIT_DRAIN));
                }
            }

            if (0U == retVal)
            {
                if (stat & I2C_INT_RECV_OVER_RUN)
                {
                    /*printf (" I2C: Receive overrun !!!\r\n");*/
                    retVal |= I2C_INT_RECV_OVER_RUN;
                }
                if (stat & I2C_INT_TRANSMIT_UNDER_FLOW)
                {
                    /*printf (" I2C: Transmit underflow !!!\r\n");*/
                    retVal |= I2C_INT_TRANSMIT_UNDER_FLOW;
                }
            }
        }
    }
    /*
     * case where isr is triggered due to initial state of some register
     * Ideally all the bits should be zero but due to some bug always
     * RRDY bit is set always and some time both RRDY and ARDY are set
     * We need to clear these bit, RRDY can be cleared only be reading
     * something from DATA register
     *
     */
    else
    {
        stat = I2CMasterIntRawStatus(instObj->baseAddr);

        while ((uint32_t) 0U != (stat & I2C_INT_RECV_READY))
        {
            w = (uint32_t) I2CMasterDataGet(instObj->baseAddr);
            I2CMasterIntClearEx(instObj->baseAddr, stat);
            stat = I2CMasterIntRawStatus(instObj->baseAddr);
        }
        if (stat & I2C_INT_BUS_BUSY)
        {
            /* Driver is not in Busy state and not expecting any transfers.
             * Still IP has bus busy set. So resetting the controller */
            lld_i2c_ctrlInit(instObj);
        }

        I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
    }
}

/* ========================================================================= */
/**
 * @fn         lld_hsi2c_waitForBb() Waits till the BUS is available within the
 *             time out period
 *
 * @see        hal_hsi2c.c
 */
/* ========================================================================= */
static LLD_hsi2cErrorCode_t lld_hsi2c_waitForBb(const lld_hsi2c_obj_t *instObj,
                                                uint32_t               timeout)
{
    volatile uint32_t    bbtimeout = timeout;
    uint32_t             stat;

    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    /* Clear current interrupts...*/
    I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

    while (bbtimeout > 0)
    {
        stat = I2CMasterIntRawStatus(instObj->baseAddr);
        if ((stat & I2C_INT_BUS_BUSY) == 0)
        {
            break;
        }
        bbtimeout--;
        I2CMasterIntClearEx(instObj->baseAddr, stat);
    }

    if (timeout > 0)
    {
        if (bbtimeout == 0)
        {
            retVal = LLD_HSI2C_BUS_BUSY_ERR;
        }
    }

    /* clear delayed stuff*/
    I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

    return retVal;
}

/* ========================================================================= */
/**
 * @fn         lld_hsi2c_waitForPin() Waits till any of the TX or RX event
 *             within the time out period
 *
 * @see        hal_hsi2c.c
 */
/* ========================================================================= */
static uint32_t lld_hsi2c_waitForPin(const lld_hsi2c_obj_t *instObj,
                                     uint32_t               flag,
                                     uint32_t               timeout,
                                     uint8_t               *timeOutStatus)
{
    uint32_t          status;

    volatile uint32_t pinTimeout = timeout;
    *timeOutStatus = 0;

    status = I2CMasterIntRawStatus(instObj->baseAddr);
    while ((uint32_t) 0U == (status & flag))
    {
        if ((uint32_t) 0U != pinTimeout)
        {
            status = I2CMasterIntRawStatus(instObj->baseAddr);
            pinTimeout--;
        }
        else
        {
            break;
        }
    }

    if (0U != timeout)
    {
        if (pinTimeout == 0)
        {
            *timeOutStatus = 1U;
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
        }
    }

    return status;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_tranceiver() API performes read or write transaction
 *
 * @see     hal_hsi2c.h
 *
 */
/* ========================================================================= */
static LLD_hsi2cErrorCode_t lld_i2c_tranceiver(
    const lld_hsi2c_obj_t            *instObj,
    const lld_hsi2c_datatfr_params_t *i2cXferParams)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    int32_t  buflen;

    uint8_t  fifoThreshold;
    uint8_t  timeOutStatus = 0;

    uint32_t flag           = 0;
    uint32_t status         = 0;
    uint32_t conParams      = 0;
    uint32_t remainingBytes = 0;
    uint32_t loopBreakFlag  = 0;

    if ((uint32_t) 0U == (i2cXferParams->flags & LLD_HSI2C_IGNORE_BUS_BUSY))
    {
        retVal = lld_hsi2c_waitForBb(instObj, i2cXferParams->timeout);
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Write the slave address */
        I2CMasterSlaveAddrSet(instObj->baseAddr, i2cXferParams->slaveAddr);

        /*Configure data buffer length*/
        I2CSetDataCount(instObj->baseAddr, i2cXferParams->bufLen);

        /* Enable I2C controller */
        conParams = I2C_CFG_MST_ENABLE;

        /* High speed configuration */
        if (instObj->initParam.i2cBusFreq > 400)
        {
            conParams |= I2C_OPMODE_HIGH_SPEED_MODE;
        }

        if (instObj->initParam.is10BitAddr)
        {
            conParams |= I2C_XSA_10BIT;
        }

        if (i2cXferParams->flags & LLD_HSI2C_MASTER)
        {
            conParams |= I2C_CFG_MST_RX;
        }

        if (i2cXferParams->flags & LLD_HSI2C_WRITE)
        {
            conParams |= I2C_CFG_MST_TX;
        }

        if (i2cXferParams->flags & LLD_HSI2C_START)
        {
            conParams |= I2C_CFG_START;
        }

        if (i2cXferParams->flags & LLD_HSI2C_STOP)
        {
            conParams |= I2C_CFG_STOP;
        }

        /* Configure i2c control parameters*/
        I2CConfig(instObj->baseAddr, conParams);

        if (HSI2C_OPMODE_POLLED == instObj->initParam.opMode)
        {
            if (i2cXferParams->flags & LLD_HSI2C_WRITE)
            {
                /* Transmit */
                buflen = 0;
                while (buflen < i2cXferParams->bufLen)
                {
                    flag = I2C_INT_TRANSMIT_READY | I2C_INT_TRANSMIT_DRAIN |
                           I2C_INT_ADRR_READY_ACESS;
                    status = lld_hsi2c_waitForPin(instObj, flag,
                                                  i2cXferParams->timeout,
                                                  &timeOutStatus);

                    if (0 == timeOutStatus)
                    {
                        if (status & I2C_INT_ADRR_READY_ACESS)
                        {
                            /*Check for status*/
                            status = I2CMasterIntRawStatus(instObj->baseAddr);

                            /*check nack status*/
                            if (status & I2C_INT_NO_ACK)
                            {
                                retVal = LLD_HSI2C_NACK_ERR;
                                I2CMasterIntClearEx(instObj->baseAddr,
                                                    I2C_INT_NO_ACK);
                            }
                            /*Check for arbitration lost*/
                            else if (status & I2C_INT_ARBITRATION_LOST)
                            {
                                retVal = LLD_HSI2C_ARBITRATION_LOSS_ERR;
                                I2CMasterIntClearEx(instObj->baseAddr,
                                                    I2C_INT_ARBITRATION_LOST);
                            }
                            else
                            {
                                /* No error status */
                            }
                            loopBreakFlag = 1U;
                        }
                        if (((status & I2C_INT_TRANSMIT_READY) != 0U) &&
                            (loopBreakFlag != 1U))
                        {
                            for (fifoThreshold = 0;
                                 fifoThreshold <
                                 (instObj->txThreshold + (uint8_t) 1U);
                                 fifoThreshold++)
                            {
                                /*transmit byte of data*/
                                I2CMasterDataPut(instObj->baseAddr,
                                                 i2cXferParams->buffer[
                                                     buflen]);
                                buflen++;
                            }

                            /*Clear transmit ready interrupt*/
                            I2CMasterIntClearEx(instObj->baseAddr,
                                                I2C_INT_TRANSMIT_READY);
                        }

                        if (((status & I2C_INT_TRANSMIT_DRAIN) != 0U) &&
                            (loopBreakFlag != 1U))
                        {
                            remainingBytes = I2CBufferStatus(
                                instObj->baseAddr,
                                I2C_TX_BUFFER_STATUS);

                            for (; remainingBytes > 0; remainingBytes--)
                            {
                                /*transmit byte of data*/
                                I2CMasterDataPut(instObj->baseAddr,
                                                 i2cXferParams->buffer[
                                                     buflen]);
                                buflen++;
                            }

                            I2CMasterIntClearEx(instObj->baseAddr,
                                                I2C_INT_TRANSMIT_DRAIN);
                        }
                    }
                    else
                    {
                        retVal        = LLD_HSI2C_ETIMEOUT;
                        loopBreakFlag = 1U;
                    }

                    if (loopBreakFlag == 1U)
                    {
                        break;
                    }
                }
            }
            else
            {
                /* Receive */
                buflen = 0;
                while (buflen < i2cXferParams->bufLen)
                {
                    flag = I2C_INT_RECV_READY | I2C_INT_RECV_DRAIN |
                           I2C_INT_ADRR_READY_ACESS;
                    status = lld_hsi2c_waitForPin(instObj, flag,
                                                  i2cXferParams->timeout,
                                                  &timeOutStatus);

                    if (0 == timeOutStatus)
                    {
                        if (status & I2C_INT_ADRR_READY_ACESS)
                        {
                            /*Check for status*/
                            status = I2CMasterIntRawStatus(instObj->baseAddr);

                            /*check nack status*/
                            if (status & I2C_INT_NO_ACK)
                            {
                                retVal = LLD_HSI2C_NACK_ERR;
                                I2CMasterIntClearEx(instObj->baseAddr,
                                                    I2C_INT_NO_ACK);
                            }
                            /*Check for arbitration lost*/
                            else if (status & I2C_INT_ARBITRATION_LOST)
                            {
                                retVal = LLD_HSI2C_ARBITRATION_LOSS_ERR;
                                I2CMasterIntClearEx(instObj->baseAddr,
                                                    I2C_INT_ARBITRATION_LOST);
                            }
                            else
                            {
                                /* No error status */
                            }
                        }
                        if (status & I2C_INT_RECV_READY)
                        {
                            for (fifoThreshold = 0;
                                 fifoThreshold <
                                 (instObj->rxThreshold + (uint8_t) 1U);
                                 fifoThreshold++)
                            {
                                /*Receive byte of data*/
                                i2cXferParams->buffer[buflen] =
                                    I2CMasterDataGet(
                                        instObj->baseAddr);
                                buflen++;
                            }

                            /*Clear receive ready interrupt*/
                            I2CMasterIntClearEx(instObj->baseAddr,
                                                I2C_INT_RECV_READY);
                        }

                        if (status & I2C_INT_RECV_DRAIN)
                        {
                            remainingBytes = I2CBufferStatus(
                                instObj->baseAddr,
                                I2C_RX_BUFFER_STATUS);

                            for (; remainingBytes > 0; remainingBytes--)
                            {
                                /*Receive byte of data*/
                                i2cXferParams->buffer[buflen] =
                                    I2CMasterDataGet(
                                        instObj->baseAddr);
                                buflen++;
                            }

                            /*Clear receive ready interrupt*/
                            I2CMasterIntClearEx(instObj->baseAddr,
                                                I2C_INT_RECV_DRAIN);
                        }
                    }
                    else
                    {
                        retVal = LLD_HSI2C_ETIMEOUT;
                    }
                }
            }

            if (((i2cXferParams->flags & LLD_HSI2C_STOP) != 0) ||
                (retVal != LLD_HSI2C_SUCCESS))
            {
                /*Wait till bus is free*/
                flag   = I2C_INT_BUS_FREE;
                status = lld_hsi2c_waitForPin(instObj, flag,
                                              i2cXferParams->timeout,
                                              &timeOutStatus);

                /*Wait till bus can be accessed*/
                flag   = I2C_INT_ADRR_READY_ACESS;
                status = lld_hsi2c_waitForPin(instObj, flag,
                                              i2cXferParams->timeout,
                                              &timeOutStatus);

                /*Flush FIFO*/
                I2CFlushFifo(instObj->baseAddr);

                /*Clear all interrupt status*/
                I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

                /*Clear data buffer length*/
                I2CSetDataCount(instObj->baseAddr, 0);
            }
        }
    }
    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_abort_transfer(hsI2cHandle handle)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    if (NULL == handle)
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    else
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        instObj = i2cDrvObj->i2cObj;
        if (NULL == instObj)
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }
    if (retVal == LLD_HSI2C_SUCCESS)
    {
        if (LLD_HSI2C_INST_BUSY == instObj->state)
        {
            /*Disable all interrupts */
            if (HSI2C_OPMODE_INTERRUPT == instObj->initParam.opMode)
            {
                I2CMasterIntDisableEx(instObj->baseAddr, I2C_INT_ALL);
            }

            /*Flush FIFO*/
            I2CFlushFifo(instObj->baseAddr);

            /*Clear all interrupt status*/
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

            /*Clear data buffer length*/
            I2CSetDataCount(instObj->baseAddr, 0);

            instObj->state = LLD_HSI2C_INST_OPENED;
        }
        if (instObj->initParam.isMasterMode ==
            LLD_HSI2C_MODE_SLAVE_TRANSRECEIVE)
        {
            I2CMasterDisable(instObj->baseAddr);
            I2CMasterIntDisableEx(instObj->baseAddr, I2C_INT_ALL);
            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
            instObj->state = LLD_HSI2C_INST_OPENED;
        }
    }
    return retVal;
}

static LLD_hsi2cErrorCode_t lld_i2c_slavetranceiver(
    lld_hsi2c_handle_t              *i2cDrvObj,
    lld_hsi2c_obj_t                 *instObj,
    lld_hsi2c_transreceive_params_t *i2cXferParams)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    uint32_t conParams = 0;
    uint32_t regVal;

    if (instObj->state == LLD_HSI2C_INST_OPENED)
    {
        /* Initiate the I2C Module for slave transfer */
        /* Transfer starts when external master initiates */
        instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_NOT_STARTED;

        instObj->i2cXferParams           = i2cXferParams;
        i2cXferParams->processedTxBufLen = 0U;
        i2cXferParams->processedRxBufLen = 0U;

        /*Configure data buffer length to 0 as the actual number of bytes to
         * transmit/receive is dependant on external master. */
        I2CSetDataCount(instObj->baseAddr, 0U);

        /* Enable I2C controller */
        conParams = I2C_CFG_MST_ENABLE;

        if (i2cXferParams->flags & LLD_HSI2C_SLAVE)
        {
            conParams &= ~I2C_CFG_MST;
        }

        /* Configure i2c control parameters. */
        I2CConfig(instObj->baseAddr, conParams);
        /* configure the registers for interrupt mode*/
        regVal = I2C_INT_TRANSMIT_READY | I2C_INT_RECV_READY |
                 I2C_INT_ADRR_READY_ACESS | I2C_INT_RECV_DRAIN |
                 I2C_INT_TRANSMIT_DRAIN | I2C_INT_ADRR_SLAVE;
        I2CMasterIntEnableEx(instObj->baseAddr, regVal);
        I2CMasterIntDisableEx(instObj->baseAddr, ~(regVal));
        /* Now we are ready to service any transfer from the external master. */
    }
    else if (instObj->state == LLD_HSI2C_INST_BUSY_SLAVE_TFR_HOLD)
    {
        /* Previous transfer was pending as App had to give data */
        /* Inititate the Slave receive function now */
        instObj->state = LLD_HSI2C_INST_BUSY_SLAVE_TFR_STARTED;

        instObj->i2cXferParams           = i2cXferParams;
        i2cXferParams->processedTxBufLen = 0U;
        i2cXferParams->processedRxBufLen = 0U;
        lld_i2c_isr_slave_transreceive(i2cDrvObj);
        regVal = I2CGetEnabledIntStatus(instObj->baseAddr, I2C_INT_ALL);
        regVal = regVal | (I2C_INT_TRANSMIT_READY | I2C_INT_RECV_READY |
                           I2C_INT_RECV_DRAIN);
        I2CMasterIntEnableEx(instObj->baseAddr, regVal);
        I2CMasterIntDisableEx(instObj->baseAddr, ~(regVal));
    }
    else
    {
        /* Nothing to be done here */
    }
    return retVal;
}

static LLD_hsi2cErrorCode_t lld_i2c_validateArgsTransReceive(
    hsI2cHandle                      handle,
    lld_hsi2c_transreceive_params_t *i2cXferParams)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    /* Check input params */
    if ((NULL == handle) || (NULL == i2cXferParams))
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        if ((NULL == i2cXferParams->txBuffer) &&
            (NULL == i2cXferParams->rxBuffer))
        {
            /* Both Tx and Rx Buffer cant be NULL */
            retVal = LLD_HSI2C_BADARGS;
        }
        if ((0 == i2cXferParams->txBufLen) &&
            (0 == i2cXferParams->rxBufLen))
        {
            /* Buffer lengths of both Tx and Rx buffer cant be NULL */
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        if (instObj->initParam.isMasterMode !=
            LLD_HSI2C_MODE_SLAVE_TRANSRECEIVE)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* check the status of the instance */
        if ((instObj->state != LLD_HSI2C_INST_OPENED) &&
            (instObj->state != LLD_HSI2C_INST_BUSY_SLAVE_TFR_HOLD))
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Only slave is supported only in interrupt mode. */
        if (instObj->initParam.opMode != HSI2C_OPMODE_INTERRUPT)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    if (NULL != i2cXferParams)
    {
        i2cXferParams->transferStatus = retVal;
    }
    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_transReceive() is used to send or receive data
 *          as I2C slave. Only Interrupt mode is supported.
 *          Function is not Re-entrant. Please use semaphore lock in the
 *          application
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_transReceive(
    hsI2cHandle                      handle,
    lld_hsi2c_transreceive_params_t *i2cXferParams)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    /* Check input params */
    retVal = lld_i2c_validateArgsTransReceive(handle, i2cXferParams);

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;
        instObj   = i2cDrvObj->i2cObj;

        retVal = lld_i2c_slavetranceiver(i2cDrvObj, instObj, i2cXferParams);

        if (retVal != LLD_HSI2C_SUCCESS)
        {
            /* Error accured while configuring I2C transfer.
             * Transfer not initiated.
             * Hence driver state is set to Opened. */
            instObj->state = LLD_HSI2C_INST_OPENED;
            i2cXferParams->transferStatus = retVal;
        }
        else
        {
            /* Transfer is initiated. Driver state should be Busy.
             * Once transfer is done ISR will set driver state to opened */
            i2cXferParams->transferStatus =
                LLD_HSI2C_SLAVE_TRANSFER_PENDING;
        }
    }
    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_transfer() is used to send or receive data
 *          Data is transfered depending on the mode of operation(DMA, Interrupt
 *          or polled)
 *          Function is not Re-entrant. Please use semaphore lock in the
 *          application
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_transfer(
    hsI2cHandle handle,
    const lld_hsi2c_datatfr_params_t *
    i2cXferParams)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;
    uint32_t regVal = 0;
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;
    lld_hsi2c_obj_t     *tempInstObj    = NULL;
    lld_hsi2c_handle_t  *tempI2cDrvObj  = NULL;

    if ((NULL == handle) || (NULL == i2cXferParams))
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    else
    {
        /* Check input params */
        if (NULL == i2cXferParams->buffer)
        {
            retVal = LLD_HSI2C_BADARGS;
        }

        if ((LLD_HSI2C_SUCCESS == retVal)
            && ((0 == i2cXferParams->bufLen)
                || (i2cXferParams->bufLen > HSI2C_BUFFER_MAXLENGTH)))
        {
            /* Buffer length should be between 1 and HSI2C_BUFFER_MAXLENGTH */
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* check the status of the instance */
        if (instObj->state != LLD_HSI2C_INST_OPENED)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        if (instObj->initParam.opMode == HSI2C_OPMODE_POLLED)
        {
            instObj->state = LLD_HSI2C_INST_BUSY;

            retVal = lld_i2c_tranceiver(instObj, i2cXferParams);

            instObj->state = LLD_HSI2C_INST_OPENED;
        }
        else if (instObj->initParam.opMode == HSI2C_OPMODE_INTERRUPT)
        {
            /* interrupt mode*/
            instObj->state = LLD_HSI2C_INST_BUSY;

            /* configure the registers for interrupt mode*/
            regVal = I2C_INT_TRANSMIT_READY | I2C_INT_RECV_READY |
                     I2C_INT_ADRR_READY_ACESS | I2C_INT_RECV_DRAIN |
                     I2C_INT_TRANSMIT_DRAIN;
            I2CMasterIntEnableEx(instObj->baseAddr, regVal);

            regVal = ~(I2C_INT_TRANSMIT_READY | I2C_INT_RECV_READY |
                       I2C_INT_ADRR_READY_ACESS | I2C_INT_RECV_DRAIN |
                       I2C_INT_TRANSMIT_DRAIN);
            I2CMasterIntDisableEx(instObj->baseAddr, regVal);

            instObj->maxBufLength         = i2cXferParams->bufLen;
            instObj->dataTfrParam.bufLen  = i2cXferParams->bufLen;
            instObj->dataTfrParam.buffer  = i2cXferParams->buffer;
            instObj->dataTfrParam.flags   = i2cXferParams->flags;
            instObj->dataTfrParam.timeout = i2cXferParams->timeout;

            retVal = lld_i2c_tranceiver(instObj, i2cXferParams);

            if (retVal != LLD_HSI2C_SUCCESS)
            {
                /* Error accured while configuring I2C transfer.
                 * Transfer not initiated.
                 * Hence driver state is set to Opened. */
                instObj->state = LLD_HSI2C_INST_OPENED;
            }
            else
            {
                /* Transfer is initiated. Driver state should be Busy.
                 * Once transfer is done ISR will set driver state to opened */
            }
        }
        else
        {
            /* dma mode*/
            tempI2cDrvObj = (lld_hsi2c_handle_t *) handle;
            tempInstObj = tempI2cDrvObj->i2cObj;
            if (tempInstObj->initParam.edmaParam == NULL)
            {
                retVal = LLD_HSI2C_FAIL;
            }
            else
            {
                instObj->state = LLD_HSI2C_INST_BUSY;

                instObj->maxBufLength         = i2cXferParams->bufLen;
                instObj->dataTfrParam.bufLen  = i2cXferParams->bufLen;
                instObj->dataTfrParam.buffer  = i2cXferParams->buffer;
                instObj->dataTfrParam.flags   = i2cXferParams->flags;
                instObj->dataTfrParam.timeout = i2cXferParams->timeout;

                retVal = lld_i2c_localEdmaTransfer(handle);

                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    retVal = lld_i2c_tranceiver(instObj, i2cXferParams);
                }
            }

        }
    }

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_getProcessedBufLength(hsI2cHandle handle,
                                                   uint32_t   *validBufLength)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS;
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    if ((NULL == handle) || (NULL == validBufLength))
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Store maxBufLength when i2c transfer is initiated.
         * dataTfrParam.bufLen keeps decrementing when buffer is processed.
         * The difference between them at any point of time will give length of
         * the total buffer that is processed till this point.
         */
        *validBufLength = instObj->maxBufLength - instObj->dataTfrParam.bufLen;
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn     lld_i2c_localEdmaTransfer() initiates Edma mode of operation
 *
 * @see    lld_hsi2c.c
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_localEdmaTransfer(hsI2cHandle handle)
{
    void    *srcPtr        = NULL;
    void    *dstPtr        = NULL;
    uint32_t chan          = 0;
    uint32_t flag          = 0;
    uint8_t  fifoThreshold = 0;
    uint32_t dstAddress;
    uint32_t srcAddress;

    lld_hsi2c_obj_t     *instObj    = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj  = NULL;
    LLD_hsi2cErrorCode_t retVal     = LLD_HSI2C_SUCCESS;
    LLD_hsi2cEdmaStatus  edmaStatus = EDMA_TRANSFER_SUCCESS;

    if (NULL == handle)
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        if ((instObj->dataTfrParam.flags & LLD_HSI2C_WRITE) == LLD_HSI2C_WRITE)
        {
            srcPtr        = (void *) instObj->dataTfrParam.buffer;
            dstAddress    = instObj->baseAddr + (uint32_t) I2C_DATA;
            dstPtr        = (void *) dstAddress;
            chan          = instObj->txDmaEventNumber;
            flag          = LLD_HSI2C_WRITE;
            fifoThreshold = instObj->txThreshold + (uint8_t) 1U;

            if (instObj->dataTfrParam.bufLen < fifoThreshold)
            {
                /* Set TX threshold to 0 for transfers less than transmit
                 * Threshold value */
                I2CFIFOThresholdConfig(instObj->baseAddr, 0, I2C_TX_MODE);
            }
        }
        else
        {
            srcAddress    = instObj->baseAddr + (uint32_t) I2C_DATA;
            srcPtr        = (void *) srcAddress;
            dstPtr        = (void *) instObj->dataTfrParam.buffer;
            chan          = (uint32_t) instObj->rxDmaEventNumber;
            flag          = LLD_HSI2C_READ;
            fifoThreshold = instObj->rxThreshold + (uint8_t) 1U;

            if (instObj->dataTfrParam.bufLen < fifoThreshold)
            {
                /* Set RX threshold to 0 for transfers less than receive
                 * Threshold value*/
                I2CFIFOThresholdConfig(instObj->baseAddr, 0, I2C_RX_MODE);
            }
        }

        /* clear if any pending events in the EDMA event register for
         * this channel*/
        edmaStatus = EDMA_clearErrorBits(chan, instObj->initParam.edmaParam);
        if (EDMA_TRANSFER_SUCCESS != edmaStatus)
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        edmaStatus =
            EDMA_setPaRAM(srcPtr, dstPtr, flag, chan,
                          instObj->dataTfrParam.bufLen,
                          instObj->initParam.edmaParam,
                          fifoThreshold);
        if (EDMA_TRANSFER_SUCCESS != edmaStatus)
        {
            retVal = LLD_HSI2C_FAIL;
        }

        if (LLD_HSI2C_SUCCESS == retVal)
        {
            edmaStatus = EDMA_enableTransfer(chan, instObj->initParam.edmaParam);

            if (EDMA_TRANSFER_SUCCESS != edmaStatus)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }

        if (LLD_HSI2C_SUCCESS == retVal)
        {
            /* Enable the EDMA */
            if ((instObj->dataTfrParam.flags & LLD_HSI2C_WRITE) ==
                LLD_HSI2C_WRITE)
            {
                I2CDMATxEventEnable(instObj->baseAddr);
            }
            else
            {
                I2CDMARxEventEnable(instObj->baseAddr);
            }
        }
        else
        {
            retVal = LLD_HSI2C_FAIL;
        }
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_ctrlProbe() API probes the I2C device
 *
 * @see     hal_hsi2c.h
 */
/* ========================================================================= */
static LLD_hsi2cErrorCode_t lld_i2c_ctrlProbe(const lld_hsi2c_obj_t *instObj,
                                              uint8_t                slaveAddr)
{
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_FAIL; /* default = fail */
    uint32_t regVal;
    uint32_t intStatus;

    if (slaveAddr != (uint8_t) I2CActiveOwnAddressGet(instObj->baseAddr))
    {
        /* Disable interrupts first */
        regVal = I2CGetEnabledIntStatus(instObj->baseAddr, I2C_INT_ALL);

        I2CMasterIntDisableEx(instObj->baseAddr, I2C_INT_ALL);

        /* wait until bus not busy */
        if (lld_hsi2c_waitForBb(instObj, HSI2C_DELAY_MED) != LLD_HSI2C_SUCCESS)
        {
            retVal = LLD_HSI2C_ETIMEOUT;
        }
        else
        {
            /* set slave address */
            I2CMasterSlaveAddrSet(instObj->baseAddr, (uint32_t) slaveAddr);

            /* Try reading 1 byte from slave */
            I2CSetDataCount(instObj->baseAddr, (uint32_t) 1U);

            /* stop bit needed here */
            I2CConfig(instObj->baseAddr,
                      (I2C_CFG_MST_ENABLE | I2C_CFG_MST | I2C_CFG_START |
                       I2C_CFG_STOP | I2C_CFG_MST_RX));

            /* enough delay for the NACK bit set */
            lld_hsi2c_udelay(HSI2C_DELAY_BIG);

            intStatus = I2CMasterIntRawStatusEx(instObj->baseAddr,
                                                (I2C_INT_NO_ACK |
                                                 I2C_INT_RECV_READY |
                                                 I2C_INT_RECV_DRAIN));

            if (((intStatus & I2C_INT_NO_ACK) == 0)
                && (((intStatus & I2C_INT_RECV_READY) != 0) ||
                    ((intStatus & I2C_INT_RECV_DRAIN) != 0)))
            {
                retVal = LLD_HSI2C_SUCCESS;      /* success case */
                /* Read one byte from the slave */
                (void) I2CMasterDataGet(instObj->baseAddr);
            }
            else
            {
                /* failure, clear sources*/
                I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);

                /* finish up xfer */
                I2CMasterStop(instObj->baseAddr);
                lld_hsi2c_waitForBb(instObj, HSI2C_DELAY_MED);
            }

            I2CFlushFifo(instObj->baseAddr);

            I2CSetDataCount(instObj->baseAddr, 0);

            I2CMasterIntClearEx(instObj->baseAddr, I2C_INT_ALL);
        }

        /* Enable interrupts now */
        I2CMasterIntEnableEx(instObj->baseAddr, regVal);
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_probe() probes the i2c device for the slave address passed
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_probe(hsI2cHandle handle, uint8_t slaveAddr)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS; /* default = fail */
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;

    if ((NULL == handle) || ((uint8_t) 0 == slaveAddr))
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;

        if (NULL != i2cDrvObj)
        {
            instObj = i2cDrvObj->i2cObj;
            if (NULL == instObj)
            {
                retVal = LLD_HSI2C_BADARGS;
            }
        }
        else
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        retVal = lld_i2c_ctrlProbe(instObj, slaveAddr);
    }

    return retVal;
}

/* ========================================================================= */
/**
 * @fn      lld_i2c_recoverBus() Generate 9 CLK pulses on SCL
 *
 * @see     lld_hsi2c.h
 */
/* ========================================================================= */
LLD_hsi2cErrorCode_t lld_i2c_recoverBus(hsI2cHandle handle,
                                        uint32_t    i2cDelay)
{
    LLD_hsi2cErrorCode_t retVal    = LLD_HSI2C_SUCCESS; /* default = fail */
    lld_hsi2c_obj_t     *instObj   = NULL;
    lld_hsi2c_handle_t  *i2cDrvObj = NULL;
    uint32_t sysTest, i;

    if (NULL == handle)
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        i2cDrvObj = (lld_hsi2c_handle_t *) handle;
        instObj   = i2cDrvObj->i2cObj;
        if (NULL == instObj)
        {
            retVal = LLD_HSI2C_BADARGS;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Check if SDA or SCL is stuck low based on the SYSTEST.
         * If SCL is stuck low we reset the IP.
         * If SDA is stuck low drive 9 clock pulses on SCL and check if the
         * slave has released the SDA. If not we reset the I2C controller.
         */

        sysTest = I2CMasterGetSysTest(instObj->baseAddr);
        if ((sysTest & I2C_SYSTEST_SCL_I_FUNC_MASK) == 0U)
        {
            /* SCL is stuck low reset the I2C IP */
            retVal = lld_i2c_resetCtrl(handle);
        }
        else if ((sysTest & I2C_SYSTEST_SDA_I_FUNC_MASK) == 0U)
        {
            /* SDA is stuck low generate 9 clk pulses on SCL */
            /* switch to system test mode */
            HW_SET_FIELD32(sysTest, I2C_SYSTEST_ST_EN, I2C_SYSTEST_ST_EN_ENABLE);
            HW_SET_FIELD32(sysTest, I2C_SYSTEST_TMODE,
                           I2C_SYSTEST_TMODE_LOOPBACK);
            I2CMasterSetSysTest(instObj->baseAddr, sysTest);
            for (i = 0; i < 9U; i++)
            {
                HW_SET_FIELD32(sysTest, I2C_SYSTEST_SCL_O,
                               I2C_SYSTEST_SCL_O_SCLOH);
                I2CMasterSetSysTest(instObj->baseAddr, sysTest);
                lld_hsi2c_udelay(i2cDelay);
                HW_SET_FIELD32(sysTest, I2C_SYSTEST_SCL_O,
                               I2C_SYSTEST_SCL_O_SCLOL);
                I2CMasterSetSysTest(instObj->baseAddr, sysTest);
                lld_hsi2c_udelay(i2cDelay);
            }
            /* Switch back to functional mode */
            HW_SET_FIELD32(sysTest, I2C_SYSTEST_ST_EN,
                           I2C_SYSTEST_ST_EN_DISABLE);
            HW_SET_FIELD32(sysTest, I2C_SYSTEST_TMODE,
                           I2C_SYSTEST_TMODE_FUNCTIONAL);
            I2CMasterSetSysTest(instObj->baseAddr, sysTest);
            /* Now check if the SDA is releases. If its still stuck low,
             * There is nothing that can be done. We still try to reset our IP.
             */
            sysTest = I2CMasterGetSysTest(instObj->baseAddr);
            if ((sysTest & I2C_SYSTEST_SDA_I_FUNC_MASK) == 0U)
            {
                retVal = lld_i2c_resetCtrl(handle);
            }
        }
        else
        {
            /* Nothing to be done. SCA and SDA both are not stuck to low */
        }
    }
    return retVal;
}

void lld_hsi2c_udelay(uint32_t delay)
{
    volatile uint32_t del = delay;
    while (del--) {}
}

void lld_i2c_getInitParams(hsI2cHandle            i2chandle,
                           lld_hsi2c_initParam_t *initParams)
{
    lld_hsi2c_handle_t    *hsi2cHandle;
    lld_hsi2c_initParam_t *instInitParam;
    hsi2cHandle   = (lld_hsi2c_handle_t *) i2chandle;
    instInitParam = &hsi2cHandle->i2cObj->initParam;

    initParams->opMode       = instInitParam->opMode;
    initParams->isMasterMode = instInitParam->isMasterMode;
    initParams->is10BitAddr  = instInitParam->is10BitAddr;
    initParams->i2cBusFreq   = instInitParam->i2cBusFreq;
    initParams->i2cOwnAddr   = instInitParam->i2cOwnAddr;
    initParams->i2cIsr       = instInitParam->i2cIsr;
    initParams->i2cIntNum    = instInitParam->i2cIntNum;
    initParams->edmaParam    = instInitParam->edmaParam;
}

void lld_i2c_getInstNum(hsI2cHandle i2chandle, LLD_Hsi2cInstId_t *instNum)
{
    lld_hsi2c_handle_t *hsi2cHandle;
    hsi2cHandle = (lld_hsi2c_handle_t *) i2chandle;
    *instNum    = hsi2cHandle->i2cObj->instNum;
}

void lld_i2c_getOpenCount(hsI2cHandle i2chandle, uint8_t *numOpens)
{
    lld_hsi2c_handle_t *hsi2cHandle;
    hsi2cHandle = (lld_hsi2c_handle_t *) i2chandle;
    *numOpens   = hsi2cHandle->i2cObj->numOpens;
}

uint32_t lld_i2c_getFclk(LLD_Hsi2cInstId_t instanceId)
{
    lld_hsi2c_obj_t *instObj = NULL;
    instObj = &lld_hsi2c_obj_arr[instanceId];
    return instObj->i2cFclk;
}

LLD_hsi2cErrorCode_t lld_i2c_SetFifoThreshold(
    LLD_Hsi2cInstId_t instanceId,
    uint8_t
    rxThreshold,
    uint8_t
    txThreshold)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;

    /* Validate arguments */
    if (instanceId >= HSI2C_INST_MAX)
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        instObj = &lld_hsi2c_obj_arr[instanceId];

        instObj->txThreshold = txThreshold;
        instObj->rxThreshold = rxThreshold;
        if (instObj->state != LLD_HSI2C_INST_CREATED)
        {
            /*Set Rx and Tx FIFO threshold value and reset the fifo*/
            I2CFIFOThresholdConfig(instObj->baseAddr, instObj->txThreshold,
                                   I2C_TX_MODE);

            I2CFIFOThresholdConfig(instObj->baseAddr, instObj->rxThreshold,
                                   I2C_RX_MODE);
        }
    }

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_clockConfig(LLD_Hsi2cInstId_t instanceId,
                                         uint32_t          functionalClock,
                                         lld_i2c_busspeed  busFrequency)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    uint32_t             baseAddr;
    uint32_t             busFreq;
    uint32_t             internalClk;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    instObj = &lld_hsi2c_obj_arr[instanceId];
    switch (instanceId)
    {
        case HSI2C_INST_0:
            baseAddr = (uint32_t) SOC_I2C1_BASE;
            break;
        case HSI2C_INST_1:
            baseAddr = (uint32_t) SOC_I2C2_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case HSI2C_INST_2:
            baseAddr = (uint32_t) SOC_I2C3_BASE;
            break;
        case HSI2C_INST_3:
            baseAddr = (uint32_t) SOC_I2C4_BASE;
            break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case HSI2C_INST_4:
            baseAddr = (uint32_t) SOC_I2C5_BASE;
            break;
#if defined (SOC_TDA2EX)
        case HSI2C_INST_5:
            baseAddr = (uint32_t) SOC_I2C6_BASE;
            break;
#endif
#endif
        default:
            baseAddr = (uint32_t) SOC_I2C1_BASE;
            instObj  = &lld_hsi2c_obj_arr[0];
            break;
    }

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(baseAddr);

    /* Configure i2c bus speed*/
    busFreq = (uint32_t) busFrequency * 1000U;

    if (busFreq > 100000U)
    {
        internalClk = 12000000U; /* 12 MHz */
    }
    else
    {
        internalClk = 4000000U;  /* 4 MHz */
    }
    instObj->busFreq = busFrequency;
    instObj->i2cFclk = functionalClock;
    instObj->i2cIclk = internalClk;

    I2CMasterInitExpClk(baseAddr, functionalClock,
                        internalClk, busFreq);

    /* Take the I2C module out of reset: */
    I2CMasterEnable(baseAddr);

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_getClockDiv(LLD_Hsi2cInstId_t instanceId,
                                         uint32_t         *sCll,
                                         uint32_t         *sClh,
                                         uint32_t         *pSc)
{
    uint32_t baseAddr;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    if ((sCll == NULL) || (sClh == NULL) || (pSc == NULL))
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        switch (instanceId)
        {
            case HSI2C_INST_0:
                baseAddr = (uint32_t) SOC_I2C1_BASE;
                break;
            case HSI2C_INST_1:
                baseAddr = (uint32_t) SOC_I2C2_BASE;
                break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
            case HSI2C_INST_2:
                baseAddr = (uint32_t) SOC_I2C3_BASE;
                break;
            case HSI2C_INST_3:
                baseAddr = (uint32_t) SOC_I2C4_BASE;
                break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            case HSI2C_INST_4:
                baseAddr = (uint32_t) SOC_I2C5_BASE;
                break;
#if defined (SOC_TDA2EX)
            case HSI2C_INST_5:
                baseAddr = (uint32_t) SOC_I2C6_BASE;
                break;
#endif
#endif
            default:
                retVal = LLD_HSI2C_BADARGS;
                break;
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        *sCll = HW_RD_REG32(baseAddr + I2C_SCLL);

        *sClh = HW_RD_REG32(baseAddr + I2C_SCLH);

        *pSc = HW_RD_REG32(baseAddr + I2C_PSC);
    }

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_setClockDiv(LLD_Hsi2cInstId_t instanceId,
                                         uint32_t          sCll,
                                         uint32_t          sClh,
                                         uint32_t          pSc)
{
    uint32_t baseAddr;
    LLD_hsi2cErrorCode_t retVal = LLD_HSI2C_SUCCESS;

    switch (instanceId)
    {
        case HSI2C_INST_0:
            baseAddr = (uint32_t) SOC_I2C1_BASE;
            break;
        case HSI2C_INST_1:
            baseAddr = (uint32_t) SOC_I2C2_BASE;
            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        case HSI2C_INST_2:
            baseAddr = (uint32_t) SOC_I2C3_BASE;
            break;
        case HSI2C_INST_3:
            baseAddr = (uint32_t) SOC_I2C4_BASE;
            break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        case HSI2C_INST_4:
            baseAddr = (uint32_t) SOC_I2C5_BASE;
            break;
#if defined (SOC_TDA2EX)
        case HSI2C_INST_5:
            baseAddr = (uint32_t) SOC_I2C6_BASE;
            break;
#endif
#endif
        default:
            retVal = LLD_HSI2C_BADARGS;
            break;
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /* Put i2c in reset/disabled state */
        I2CMasterDisable(baseAddr);

        HW_WR_REG32(baseAddr + I2C_SCLL, sCll);

        HW_WR_REG32(baseAddr + I2C_SCLH, sClh);

        HW_WR_REG32(baseAddr + I2C_PSC, pSc);

        /* Take the I2C module out of reset: */
        I2CMasterEnable(baseAddr);
    }

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_setFclk(LLD_Hsi2cInstId_t instanceId,
                                     uint32_t          fclk)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;
    instObj = &lld_hsi2c_obj_arr[instanceId];
    if ((instanceId < HSI2C_INST_MAX) && ((int32_t) instanceId >= HSI2C_INST_0))
    {
        instObj->i2cFclk = fclk;
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    return retVal;
}

uint32_t lld_i2c_getIclk(LLD_Hsi2cInstId_t instanceId)
{
    lld_hsi2c_obj_t *instObj = NULL;
    instObj = &lld_hsi2c_obj_arr[instanceId];
    return instObj->i2cIclk;
}

LLD_hsi2cErrorCode_t lld_i2c_setIclk(LLD_Hsi2cInstId_t instanceId,
                                     uint32_t          iclk)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;
    instObj = &lld_hsi2c_obj_arr[instanceId];
    if ((instanceId < HSI2C_INST_MAX) && ((int32_t) instanceId >= HSI2C_INST_0))
    {
        instObj->i2cIclk = iclk;
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_getBusFreq(LLD_Hsi2cInstId_t instanceId,
                                        lld_i2c_busspeed *busFreq)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;

    if ((instanceId < HSI2C_INST_MAX) &&
        ((int32_t) instanceId >= HSI2C_INST_0) && (NULL != busFreq))
    {
        instObj  = &lld_hsi2c_obj_arr[instanceId];
        *busFreq = instObj->busFreq;
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }

    return retVal;
}

LLD_hsi2cErrorCode_t lld_i2c_setBusFreq(LLD_Hsi2cInstId_t instanceId,
                                        lld_i2c_busspeed  busFreq)
{
    lld_hsi2c_obj_t     *instObj = NULL;
    LLD_hsi2cErrorCode_t retVal  = LLD_HSI2C_SUCCESS;
    if ((instanceId < HSI2C_INST_MAX) &&
        ((int32_t) instanceId >= HSI2C_INST_0) &&
        ((uint32_t) busFreq >= HSI2C_MIN_BUS_FREQ) &&
        ((uint32_t) busFreq <= HSI2C_MAX_BUS_FREQ))
    {
        instObj = &lld_hsi2c_obj_arr[instanceId];
        if (instObj->busFreq != busFreq)
        {
            retVal = lld_i2c_clockConfig(instanceId, lld_i2c_getFclk(
                                             instanceId), busFreq);
        }
    }
    else
    {
        retVal = LLD_HSI2C_BADARGS;
    }
    return retVal;
}

