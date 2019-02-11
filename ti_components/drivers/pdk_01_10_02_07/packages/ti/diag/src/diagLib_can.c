/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - www.ti.com/
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
 * \file     diagLib_can.c
 *
 * \brief    This file contains CAN software test APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/include/pm_types.h>
#include <diagLib_utils.h>

/* library header files */
#include <ti/diag/diagLib_can.h>


/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief DCAN TX message object used */
#define DCAN_TX_MSG_OBJ                 (0x1U)
/** \brief DCAN RX message object used */
#define DCAN_RX_MSG_OBJ                 (0x2U)

/** \brief DCAN TX interface register used */
#define DCAN_APP_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define DCAN_APP_RX_IF_REG              (DCAN_IF_REG_NUM_2)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204U)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief Offset of DRM SUSPEND_CTRL2 register */
#define DRM_SUSPEND_CTRL2               (0x208U)
/** \brief DRM_SUSPEND_CTRL2 is mapped to DCAN2 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN2          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL2)

/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0          (uint32_t)(0x5U)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (uint32_t)(0x3U)

#if defined (SOC_TDA3XX)
/** \brief DCAN Message Object used for ECC Test */
#define DCAN_NUM_MSG_OBJ                 (0x2U)
#else
/** \brief DCAN Message Object used for PARITY Test */
#define DCAN_NUM_MSG_OBJ                 (0x1U)
#endif

#define DCAN_MSG_OBJ_1                   (0x4U)
#define DCAN_MSG_OBJ_2                   (0x6U)

/** \brief DCAN Message Object RAM Address */
#define DCAN1_MSG_OBJ_RAM_ADDR_1        ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_1 * DCAN_MSG_OBJ_SIZE))
#define DCAN1_MSG_OBJ_RAM_ADDR_2        ((SOC_DCAN1_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_2 * DCAN_MSG_OBJ_SIZE))
#define DCAN2_MSG_OBJ_RAM_ADDR_1        ((SOC_DCAN2_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_1 * DCAN_MSG_OBJ_SIZE))
#define DCAN2_MSG_OBJ_RAM_ADDR_2        ((SOC_DCAN2_MESSAGERAM_BASE) + \
                                         (DCAN_MSG_OBJ_2 * DCAN_MSG_OBJ_SIZE))

#define ISR_REG_WAIT_TIMEOUT            (500U)


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used for initializing the test for the DCAN module.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DiagLib_dcanStartTest(DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for calculating the bit time parameter for
 *          the DCAN module.
 *
 * \param  clkFreq         Input clock frequency
 * \param  bitRate         Output bit rate
 * \param  refSamplePnt    DCAN sampling point
 * \param  propDelay       DCAN Propagation Delay
 * \param  pBitTimePrms    Pointer to structure for holding bit time params
 *
 * \return  None.
 */
static int32_t DiagLib_dcanCalcBitTimeParams(uint32_t      clkFreq,
                              uint32_t             bitRate,
                              uint32_t             refSamplePnt,
                              uint32_t             propDelay,
                              dcanBitTimeParams_t *pBitTimePrms);

/**
 * \brief   This API is used for calculating the bit time parameter for
 *          the DCAN module.
 *
 * \param  baseAddr         Base address for DCAN module
 * \param  ifRegNum         Interface to be checked
 * \param  timeout          Timeout value
 *
 * \return  None.
 */
static int32_t DiagLib_dcanWaitForIfRef(uint32_t baseAddr, uint32_t ifRegNum,
                                      uint32_t timeOut);

/**
 * \brief   This API is used for initializing the loopback test for the DCAN
 *          module.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DiagLib_dcanLoopbackTest(const DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for initializing the parity test for the DCAN
 *          module.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DiagLib_dcanParityTest(DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for checking the input parameters for the test.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DiagLib_canChkParams(const DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for get the data and check for parity errors
 *          from ISR.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DcanLib_parityCheck(const DiagLib_CanTestParam_t *testPrm);

/**
 * \brief   This API is used for get and verify the data for loopback test
 *          from ISR.
 *
 * \param   testPrm   Pointer to structure #DiagLib_CanTestParam_t.
 *
 * \return  None.
 */
static int32_t DcanLib_loopbackCheck(const DiagLib_CanTestParam_t *testPrm);

static void PlatformDcanMessageRamInit(uint32_t instance);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t DiagLib_canTestParamsInit(DiagLib_CanTestParam_t *testPrm)
{
    int32_t errStatus;
    uint8_t index;

    if(NULL == testPrm)
    {
        errStatus = STW_EINVALID_PARAMS;
    }
    else
    {
        errStatus = DIAGLIB_CAN_TEST_OK;

        testPrm->timeout = DIAGLIB_UTILS_DEFAULT_TIMEOUT;

        /* CAN input clock */
        testPrm->clkFrequency = DIAGLIB_CAN_DEFAULT_CLK_FREQ;
        /* CAN output bit rate */
        testPrm->bitRate = DIAGLIB_CAN_DEFAULT_BIT_RATE;
        /* CAN APP propagation delay */
        testPrm->propDelay = DIAGLIB_CAN_DEFAULT_PROP_DELAY;
        /* CAN APP sampling point */
        testPrm->samplingPt = DIAGLIB_CAN_DEFAULT_SAMP_PT;

        /*Initialize DCAN Config parameters*/
        if (DIAGLIB_CAN_PARITY_ECC_TEST == testPrm->testType)
        {
            testPrm->dcanPrm.canCfgPrm.parityEnable = (uint32_t)TRUE;
            testPrm->dcanPrm.canCfgPrm.intrLine0Enable = (uint32_t)FALSE;
#if defined (SOC_TDA3XX)
            testPrm->dcanPrm.canCfgPrm.eccModeEnable     = (uint32_t)TRUE;
            testPrm->dcanPrm.canCfgPrm.eccDiagModeEnable = (uint32_t)FALSE;
            testPrm->dcanPrm.canCfgPrm.sbeEventEnable    = (uint32_t)TRUE;
#endif
            testPrm->dcanPrm.canCfgPrm.testModeEnable = (uint32_t)FALSE;
        }
        else
        {
            testPrm->dcanPrm.canCfgPrm.parityEnable    = (uint32_t)FALSE;
            testPrm->dcanPrm.canCfgPrm.intrLine0Enable = (uint32_t)TRUE;
#if defined (SOC_TDA3XX)
            testPrm->dcanPrm.canCfgPrm.eccModeEnable = (uint32_t)FALSE;
#endif
            testPrm->dcanPrm.canCfgPrm.testModeEnable = (uint32_t)TRUE;
            if (DIAGLIB_CAN_TEST_INT_LOOPBACK == testPrm->testType)
            {
                testPrm->dcanPrm.canCfgPrm.testMode =
                                                   DCAN_TEST_MODE_LPBACK;
            }
            else
            {
                /* DIAGLIB_CAN_TEST_EXT_LOOPBACK */
                testPrm->dcanPrm.canCfgPrm.testMode =
                                                   DCAN_TEST_MODE_EXT_LPBACK;
            }
        }

        testPrm->dcanPrm.canCfgPrm.autoRetransmitDisable = (uint32_t)TRUE;
        testPrm->dcanPrm.canCfgPrm.autoBusOnEnable       = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.intrLine1Enable       = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.errIntrEnable         = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.stsChangeIntrEnable   = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.autoBusOnTimerVal     = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.if1DmaEnable          = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.if2DmaEnable          = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.if3DmaEnable          = (uint32_t)FALSE;
        testPrm->dcanPrm.canCfgPrm.ramAccessEnable       = (uint32_t)FALSE;

        /*Initialize DCAN TX Config Parameters*/
        testPrm->dcanPrm.canTxCfgPrms.xIdFlagMask       = 0x1U;
        testPrm->dcanPrm.canTxCfgPrms.dirMask           = 0x1U;
        testPrm->dcanPrm.canTxCfgPrms.msgIdentifierMask = 0x1FFFFFFFU;

        testPrm->dcanPrm.canTxCfgPrms.msgValid      = (uint32_t)TRUE;
        testPrm->dcanPrm.canTxCfgPrms.xIdFlag       = (uint32_t)TRUE;
        testPrm->dcanPrm.canTxCfgPrms.direction     = DCAN_DIR_TX;
        testPrm->dcanPrm.canTxCfgPrms.msgIdentifier = 0xC1U;

        testPrm->dcanPrm.canTxCfgPrms.uMaskUsed    = (uint32_t)TRUE;
        testPrm->dcanPrm.canTxCfgPrms.intEnable    = (uint32_t)TRUE;
        testPrm->dcanPrm.canTxCfgPrms.remoteEnable = (uint32_t)FALSE;
        testPrm->dcanPrm.canTxCfgPrms.fifoEOBFlag  = (uint32_t)TRUE;

        /*Initialize DCAN Rx Config Parameters*/
        testPrm->dcanPrm.canRxCfgPrms.xIdFlagMask  = 0x1U;
        testPrm->dcanPrm.canRxCfgPrms.msgIdentifierMask = 0x1FFFFFFFU;
        testPrm->dcanPrm.canRxCfgPrms.dirMask           = 0x1U;

        testPrm->dcanPrm.canRxCfgPrms.msgValid      = (uint32_t)TRUE;
        testPrm->dcanPrm.canRxCfgPrms.xIdFlag       = (uint32_t)TRUE;
        testPrm->dcanPrm.canRxCfgPrms.direction     = DCAN_DIR_RX;
        testPrm->dcanPrm.canRxCfgPrms.msgIdentifier = 0xC1U;

        testPrm->dcanPrm.canRxCfgPrms.uMaskUsed    = (uint32_t)TRUE;
        testPrm->dcanPrm.canRxCfgPrms.intEnable    = (uint32_t)TRUE;
        testPrm->dcanPrm.canRxCfgPrms.remoteEnable = (uint32_t)FALSE;
        testPrm->dcanPrm.canRxCfgPrms.fifoEOBFlag  = (uint32_t)TRUE;

        testPrm->dcanPrm.canTxPrms.dataLength = DCAN_MAX_MSG_LENGTH;

        for (index = 0U; index < DCAN_MAX_MSG_LENGTH; index++)
        {
            /* Initialize the txBuffer & rxBuffer with a known pattern of data */
            testPrm->dcanPrm.canTxPrms.msgData[index] = index;
            testPrm->dcanPrm.canRxPrms[0].msgData[index] = 0xAAU;
            testPrm->dcanPrm.canRxPrms[1].msgData[index] = 0xAAU;
        }
    }

    return errStatus;
}

int32_t DiagLib_canStartTest(DiagLib_CanTestParam_t *testPrm)
{
    int32_t  retVal;

    /* Check input parameters */
    retVal =  DiagLib_canChkParams(testPrm);

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DiagLib_dcanStartTest(testPrm);
    }

    return retVal;
}

int32_t DiagLib_canISR(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t  status = DIAGLIB_CAN_TEST_PENDING;

    if((DIAGLIB_CAN_TEST_INT_LOOPBACK == testPrm->testType) ||
         (DIAGLIB_CAN_TEST_EXT_LOOPBACK == testPrm->testType))
    {
        if(TRUE == DCANIsMsgObjIntrPending(testPrm->canBase, DCAN_TX_MSG_OBJ))
        {
            /* Clear the interrupts  of MSG_OBJ 1 for transmit */
            DCANIntrClearStatus(testPrm->canBase, DCAN_TX_MSG_OBJ,
                                DCAN_APP_TX_IF_REG);
        }

        if(TRUE == DCANIsMsgObjIntrPending(testPrm->canBase, DCAN_RX_MSG_OBJ))
        {
            /* Clear the interrupts  of MSG_OBJ 2 for Receive */
            DCANIntrClearStatus(testPrm->canBase, DCAN_RX_MSG_OBJ,
                                DCAN_APP_RX_IF_REG);

            status = DcanLib_loopbackCheck(testPrm);
        }
    }
    else if(DIAGLIB_CAN_PARITY_ECC_TEST == testPrm->testType)
    {
        status = DcanLib_parityCheck(testPrm);
    }
    else
    {
        /* Invalid case */
    }

    return status;
}

int32_t DiagLib_canParityVerifyData(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t retVal = DIAGLIB_CAN_TEST_OK;
    uint32_t dataLength;
    uint32_t cnt;


    for (cnt = 0U; cnt < DCAN_NUM_MSG_OBJ; cnt++)
    {
        dataLength = 0U;
        if (DIAGLIB_CAN_TEST_OK == retVal)
        {

            /* Check if sent data has been received */
            if((testPrm->dcanPrm.canRxPrms[cnt].dataLength ==
                testPrm->dcanPrm.canTxPrms.dataLength) &&
                (testPrm->dcanPrm.canRxPrms[cnt].msgLostFlag != TRUE))
            {
                while (dataLength < testPrm->dcanPrm.canRxPrms[cnt].dataLength)
                {
                    if (testPrm->dcanPrm.canRxPrms[cnt].msgData[dataLength] !=
                        testPrm->dcanPrm.canTxPrms.msgData[dataLength])
                    {
                        retVal = DIAGLIB_CAN_DATA_MISMATCH;
                    }
                    dataLength++;
                }
                if ((0U == cnt) && (DIAGLIB_CAN_DATA_MISMATCH == retVal))
                {
                    /* single bit parity error wasn't auto corrected */
                    retVal = DIAGLIB_CAN_TEST_FAIL;
                }
                else if((1U == cnt) && (DIAGLIB_CAN_TEST_OK == retVal))
                {
                    /* couldn't detect the induced double bit parity error */
                    retVal = DIAGLIB_CAN_TEST_FAIL;
                }
                else
                {
                    retVal = DIAGLIB_CAN_TEST_OK;
                }
            }
            else
            {
                retVal = DIAGLIB_CAN_TEST_FAIL;
            }
        }
    }
    return retVal;
}

/*==========================================================================*/
/*                Internal Function Definitions                             */
/*==========================================================================*/

static int32_t DcanLib_loopbackCheck(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t               retVal;
    uint32_t              dataLength = 0U;
    dcanRxParams_t        canRxPrms[2];
    uint32_t              isrTimeout;

    if(testPrm->timeout > ISR_REG_WAIT_TIMEOUT)
    {
        isrTimeout = ISR_REG_WAIT_TIMEOUT;
    }
    else
    {
        isrTimeout = testPrm->timeout;
    }

    retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                          (uint32_t)DCAN_APP_RX_IF_REG,
                          isrTimeout);

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DCANGetData(testPrm->canBase,
                             DCAN_RX_MSG_OBJ,
                             DCAN_APP_RX_IF_REG,
                             &canRxPrms[0],
                             isrTimeout);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* verify the received data */
        if((canRxPrms[0].dataLength ==
             testPrm->dcanPrm.canTxPrms.dataLength) &&
            (canRxPrms[0].msgLostFlag != TRUE))
        {
            while(dataLength < canRxPrms[0].dataLength)
            {
                if(canRxPrms[0].msgData[dataLength] !=
                    testPrm->dcanPrm.canTxPrms.msgData[dataLength])
                {
                    retVal = DIAGLIB_CAN_TEST_FAIL;
                }
                dataLength++;
            }
        }
        else
        {
            retVal = DIAGLIB_CAN_TEST_FAIL;
        }
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DIAGLIB_CAN_LOOPBACK_VERIFIED;
    }

    return retVal;
}

static int32_t DcanLib_parityCheck(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t       retVal = DIAGLIB_CAN_TEST_OK;
    uint32_t      errStatus;

#if defined (SOC_TDA3XX)
    dcanEccErrStatus_t    errClr;
    uint32_t              msgObjSBE = 0;
    uint32_t              msgObjDBE = 0;
#else
    uint32_t              msgObj;
#endif

    /* Get the error status for the DCAN transfer */
#if defined (SOC_TDA3XX)
    errStatus = DCANGetEccErrStatus(testPrm->canBase);

    errClr.singleBitErr = (errStatus & DCAN_ECC_CSR_SE_FLAG_MASK);
    errClr.doubleBitErr = ((errStatus & DCAN_ECC_CSR_DE_FLAG_MASK) >>
                            DCAN_ECC_CSR_DE_FLAG_SHIFT);

    (void)DCANClrEccErrStatus(testPrm->canBase, &errClr);

    if (errClr.singleBitErr != 0U)
    {
        msgObjSBE = DCANGetMsgObjBitErrDetected(testPrm->canBase);
    }

    if (errClr.doubleBitErr != 0U)
    {
        errStatus  = DCANGetParityErrStatus(testPrm->canBase);
        msgObjDBE = (errStatus & DCAN_PERR_MESSAGE_NUMBER_MASK);
    }
#else
    errStatus = DCANGetParityErrStatus(testPrm->canBase);
    msgObj   = (errStatus & DCAN_PERR_MESSAGE_NUMBER_MASK);
#endif

    DCANClrParityIntrStatus(testPrm->canBase);

#if defined (SOC_TDA3XX)
    if(DCAN_MSG_OBJ_1 == msgObjSBE)
    {
        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED;
        }
    }
    else if(DCAN_MSG_OBJ_2 == msgObjDBE)
    {
        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DIAGLIB_CAN_PARITY_DBE_ISR_RECEIVED;
        }
    }
    else
    {
        retVal = DIAGLIB_CAN_TEST_PENDING;
    }

#else
    if (msgObj == DCAN_MSG_OBJ_1)
    {
        retVal = DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED;
    }
    else
    {
        retVal = DIAGLIB_CAN_TEST_PENDING;
    }
#endif

    return retVal;
}

static int32_t DiagLib_canChkParams(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t status;

    if(NULL == testPrm)
    {
        status = DIAGLIB_CAN_TEST_INVALID_PARAMS;
    }
    else
    {
        status = DIAGLIB_CAN_TEST_OK;
    }

    return status;
}

static int32_t DiagLib_dcanStartTest(DiagLib_CanTestParam_t *testPrm)
{
    dcanBitTimeParams_t   canBitTimePrms;
    int32_t               retVal;

    if(SOC_DCAN1_BASE == testPrm->canBase)
    {
#if defined (__TI_ARM_V7M4__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4U) | 0x1U));
#elif defined (__ARM_ARCH_7A__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4U) | 0x1U));
#endif
        retVal = DIAGLIB_CAN_TEST_OK;
    }
    else if(SOC_DCAN2_BASE == testPrm->canBase)
    {
#if defined (__TI_ARM_V7M4__)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         *  must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4U) | 0x1U));
#elif defined (__ARM_ARCH_7A__)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4U) | 0x1U));
#endif
        retVal = DIAGLIB_CAN_TEST_OK;
    }
    else
    {
        /* Invalid case */
        retVal = STW_EINVALID_PARAMS;
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Reset the DCAN IP */
        retVal = DCANReset(testPrm->canBase, testPrm->timeout);
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(testPrm->canBase, DCAN_MODE_INIT);

        retVal = DiagLib_dcanCalcBitTimeParams(testPrm->clkFrequency / 1000000U,
                                          testPrm->bitRate / 1000U,
                                          testPrm->samplingPt,
                                          testPrm->propDelay,
                                          &canBitTimePrms);
    }
    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        DCANSetBitTime(testPrm->canBase,
                       &canBitTimePrms);
        DCANSetMode(testPrm->canBase, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(testPrm->canBase, &testPrm->dcanPrm.canCfgPrm);

        if(DIAGLIB_CAN_PARITY_ECC_TEST != testPrm->testType)
        {
            /* Call API for Non parity test case */
            retVal = DiagLib_dcanLoopbackTest(testPrm);
        }
        else
        {
            /* Call API for the eCC parity test */
            retVal = DiagLib_dcanParityTest(testPrm);
        }
    }

    return retVal;
}


static int32_t DiagLib_dcanLoopbackTest(const DiagLib_CanTestParam_t *testPrm)
{
    int32_t         retVal;

    /*
     * Enable message object interrupt to route interrupt line 1
     */
    DCANConfigIntrMux(testPrm->canBase, DCAN_INTR_LINE_NUM_0,
                      DCAN_TX_MSG_OBJ);
    DCANConfigIntrMux(testPrm->canBase, DCAN_INTR_LINE_NUM_0,
                      DCAN_RX_MSG_OBJ);

    /* Wait for interface to become free */
    retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                          (uint32_t)DCAN_APP_RX_IF_REG,
                          testPrm->timeout);

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DCANConfigMsgObj(testPrm->canBase,
                              DCAN_RX_MSG_OBJ,
                              DCAN_APP_RX_IF_REG,
                              &testPrm->dcanPrm.canRxCfgPrms);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Wait for config to be copied to internal message RAM */
        retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                              (uint32_t)DCAN_APP_RX_IF_REG,
                              testPrm->timeout);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Wait for interface to become free */
        retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                              (uint32_t)DCAN_APP_TX_IF_REG,
                              testPrm->timeout);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DCANConfigMsgObj(testPrm->canBase,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &testPrm->dcanPrm.canTxCfgPrms);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Wait for interface to become free */
        retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                               (uint32_t)DCAN_APP_TX_IF_REG,
                               testPrm->timeout);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DCANTransmitData(testPrm->canBase,
                                  DCAN_TX_MSG_OBJ,
                                  DCAN_APP_TX_IF_REG,
                                  &testPrm->dcanPrm.canTxPrms,
                                  testPrm->timeout);
    }

    if (DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Wait for config to be copied to internal message RAM */
        retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                              (uint32_t)DCAN_APP_TX_IF_REG,
                              testPrm->timeout);
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DIAGLIB_CAN_TEST_PENDING;
    }

    return retVal;
}

static int32_t DiagLib_dcanParityTest(DiagLib_CanTestParam_t *testPrm)
{
    int32_t               retVal             = DIAGLIB_CAN_TEST_OK;
    uint32_t              *pMsgObj            = 0U;
    uint32_t              msgObj;
    uint32_t              cnt;

#if defined (SOC_TDA3XX)
    uint32_t              errStatus;
    dcanEccErrStatus_t    eccDiagErrClr;
#endif

    if(TRUE == testPrm->dcanPrm.canCfgPrm.parityEnable)
    {
        /* Priming DCAN message RAM to generate ECC/Parity Bits*/
        PlatformDcanMessageRamInit(0);
    }

    for (cnt = 0U; cnt < DCAN_NUM_MSG_OBJ; cnt++)
    {
        if (0U == cnt)
        {
            msgObj = DCAN_MSG_OBJ_1;
        }
        else
        {
            msgObj = DCAN_MSG_OBJ_2;
        }

        if (DIAGLIB_CAN_TEST_OK == retVal)
        {
            /* Wait for interface to become free */
            retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                                  (uint32_t)DCAN_APP_TX_IF_REG,
                                  testPrm->timeout);
        }
        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DCANConfigMsgObj(testPrm->canBase,
                                      msgObj,
                                      DCAN_APP_TX_IF_REG,
                                      &testPrm->dcanPrm.canTxCfgPrms);
        }

        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            /* Wait for interface to become free */
            retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                                  (uint32_t)DCAN_APP_TX_IF_REG,
                                  testPrm->timeout);
        }

        if (DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DCANTransmitData(testPrm->canBase,
                                      msgObj,
                                      DCAN_APP_TX_IF_REG,
                                      &testPrm->dcanPrm.canTxPrms,
                                      testPrm->timeout);
        }
        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            /* Wait for config to be copied to internal message RAM */
            retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                                  (uint32_t)DCAN_APP_TX_IF_REG,
                                  testPrm->timeout);
        }
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        /* Disable SECDED to corrupt the RAM */
        DCANParityEnable(testPrm->canBase, (uint32_t) FALSE);

#if defined (SOC_TDA3XX)
        /* Enable ECCDIAG mode */
        DCANEccDiagModeEnable(testPrm->canBase, TRUE);
#endif

        /* RDA mode is enabled to ACCESS the MessageRAM */
        DCANTestModeEnable(testPrm->canBase, (uint32_t) TRUE, DCAN_TEST_RDA_MASK);

        if(SOC_DCAN1_BASE == testPrm->canBase)
        {
            pMsgObj = (uint32_t *) (DCAN1_MSG_OBJ_RAM_ADDR_1);
        }
        else if(SOC_DCAN2_BASE == testPrm->canBase)
        {
            pMsgObj = (uint32_t *) (DCAN2_MSG_OBJ_RAM_ADDR_1);
        }
        else
        {
            /* Invalid input */
            retVal = STW_EINVALID_PARAMS;
        }

        /* Corrupt the data in Message RAM in RDA Mode to introduces
         * single bit error.
         */
        if(pMsgObj != NULL)
        {
            *pMsgObj = (*pMsgObj & 0xFFFFFFFEU);
        }

#if defined (SOC_TDA3XX)
        /* introduce the double parity error */
        /* copy the message address */
        if(SOC_DCAN1_BASE == testPrm->canBase)
        {
            pMsgObj = (uint32_t *) (DCAN1_MSG_OBJ_RAM_ADDR_2);
        }
        else
        {
            /* SOC_DCAN2_BASE */
            pMsgObj = (uint32_t *) (DCAN2_MSG_OBJ_RAM_ADDR_2);
        }

        /*
         * Corrupt the data in Message RAM in RDA Mode to introduce
         * double bit error.
         */
         *pMsgObj = (*pMsgObj & 0xFFFFFFFCU);

#endif

        /* RDA mode is disabled to ACCESS the MessageRAM */
        DCANTestModeEnable(testPrm->canBase, (uint32_t) FALSE,
            DCAN_TEST_RDA_MASK);
        /* Enable SECDED */
        DCANParityEnable(testPrm->canBase, (uint32_t) TRUE);
    }

    for (cnt = 0U; cnt < DCAN_NUM_MSG_OBJ; cnt++)
    {
        if (cnt == 0U)
        {
            msgObj = DCAN_MSG_OBJ_1;
        }
        else
        {
            msgObj = DCAN_MSG_OBJ_2;
        }

        if (DIAGLIB_CAN_TEST_OK == retVal)
        {
            /* Wait for interface to become free */
            retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                                  (uint32_t)DCAN_APP_TX_IF_REG,
                                  testPrm->timeout);
        }

        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DCANGetData(testPrm->canBase,
                                 msgObj,
                                 DCAN_APP_RX_IF_REG,
                                 &testPrm->dcanPrm.canRxPrms[cnt],
                                 testPrm->timeout);
        }

        if(DIAGLIB_CAN_TEST_OK == retVal)
        {
            /* Wait for config to be copied to internal message RAM */
            retVal = DiagLib_dcanWaitForIfRef(testPrm->canBase,
                                  (uint32_t)DCAN_APP_TX_IF_REG,
                                  testPrm->timeout);
        }

#if defined (SOC_TDA3XX)
        errStatus = DCANGetEccDiagErrStatus(testPrm->canBase);

        eccDiagErrClr.singleBitErr = ((uint32_t)errStatus &
                                      DCAN_ECC_DIAG_STATUS_SE_FLAG_MASK);
        eccDiagErrClr.doubleBitErr = (((uint32_t)errStatus &
                                       DCAN_ECC_DIAG_STATUS_DE_FLAG_MASK) >>
                                      DCAN_ECC_DIAG_STATUS_DE_FLAG_SHIFT);

        if (DIAGLIB_CAN_TEST_OK == retVal)
        {
            retVal = DCANClrEccDiagErrStatus(testPrm->canBase, &eccDiagErrClr);
        }
#endif
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
#if defined (SOC_TDA3XX)
        /* Disable ECCDIAG mode */
        DCANEccDiagModeEnable(testPrm->canBase, (uint32_t) FALSE);
#endif
        /* Disable SECDED */
        DCANParityEnable(testPrm->canBase, (uint32_t) FALSE);
    }

    if(DIAGLIB_CAN_TEST_OK == retVal)
    {
        retVal = DIAGLIB_CAN_TEST_PENDING;
    }

return retVal;
}

static int32_t DiagLib_dcanCalcBitTimeParams(uint32_t      clkFreq,
                              uint32_t             bitRate,
                              uint32_t             refSamplePnt,
                              uint32_t             propDelay,
                              dcanBitTimeParams_t *pBitTimePrms)
{
    Double  tBitRef = ((1000.0 * 1000.0) / (Double)bitRate);
    Double  newBaud = 0.0, newNProp = 0.0, newNSeg = 0.0, newSjw = 0.0, newP = 0.0;
    Double  nQRef, nProp, fCan, nQ, nSeg, baud, sp, newSp = 0.0;
    int32_t errStatus = DIAGLIB_CAN_TEST_OK;
    int32_t p;
    Double   tQ;

    for (p = 1; p <= 1024; p++)
    {
        tQ    = (((Double)p / (Double)clkFreq) * 1000.0);
        nQRef = tBitRef / (Double)tQ;

        if ((nQRef >= 8.0) && (nQRef <= 25.0))
        {
            nProp = ceil((Double)propDelay / tQ);
            fCan  = (Double)clkFreq / (Double)p;
            nQ    = (fCan / (Double)bitRate) * 1000.0;
            nSeg  = ceil((nQ - nProp - 1.0) / 2.0);

            if ((nProp <= 8.0) && (nProp > 0.0) && (nSeg <= 8.0) && (nSeg > 0.0))
            {
                baud = (fCan / (1.0 + nProp + (2.0 * nSeg))) * 1000.0;

                sp = ((1.0 + nProp + nSeg) / (1.0 + nProp + nSeg + nSeg)) * 100.0;

                if (abs((int32_t)baud -  (int32_t)bitRate) <
                    abs((int32_t)newBaud - (int32_t)bitRate))
                {
                    newBaud  = baud;
                    newNProp = nProp;
                    newNSeg  = nSeg;
                    newSjw   = (nSeg < 4.0) ? nSeg : 4.0;
                    newP     = (Double)p - 1.0;
                    newSp    = sp;
                }
                if (abs((int32_t)baud - (int32_t)bitRate) ==
                    abs((int32_t)newBaud - (int32_t)bitRate))
                {
                    if (abs((int32_t)sp - (int32_t)refSamplePnt) <
                        abs((int32_t)newSp - (int32_t)refSamplePnt))
                    {
                        newBaud  = baud;
                        newNProp = nProp;
                        newNSeg  = nSeg;
                        newSjw   = (nSeg < 4.0) ? nSeg : 4.0;
                        newP     = (Double)p - 1.0;
                        newSp    = sp;
                    }
                }
            }
        }
    }
    if (((uint32_t)newBaud == 0U) || (newBaud > 1000.0))
    {
        errStatus = DIAGLIB_CAN_TEST_FAIL;
    }
    if(DIAGLIB_CAN_TEST_OK == errStatus)
    {
        pBitTimePrms->baudRatePrescaler    = (((uint32_t) newP) & 0x3FU);
        pBitTimePrms->baudRatePrescalerExt =
            (((((uint32_t) newP) & 0x3C0U) != 0U) ? (((uint32_t) newP) & 0x3C0U) >> 6U : 0U);
        pBitTimePrms->syncJumpWidth = ((uint32_t) newSjw) - 1U;

        pBitTimePrms->timeSegment1 = ((uint32_t)newNProp + (uint32_t)newNSeg) - 1U;
        pBitTimePrms->timeSegment2 = (uint32_t)newNSeg - 1U;
    }

    return errStatus;
}

static int32_t DiagLib_dcanWaitForIfRef(uint32_t baseAddr, uint32_t ifRegNum,
                                      uint32_t timeOut)
{
    int32_t  retVal = DIAGLIB_CAN_TEST_OK;

    while((TRUE == DCANIsIfRegBusy(baseAddr, ifRegNum)) && (timeOut > 0))
    {
        /* Wait while the interface is busy */
        timeOut--;
        if(timeOut == 0)
        {
            retVal = DIAGLIB_CAN_TEST_TIMEOUT;
        }
    }

    return retVal;
}

static void PlatformDcanMessageRamInit(uint32_t instance)
{
    uint32_t status = 0U;

    switch (instance)
    {
        case 0U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_CLEAR);
            break;

        case 1U:
            /* Clear the start bit so that pulse is generated
             * when run second time */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CLEAR);
            /* Set the start bit so that pulse is generated
             * when run second time.
             * CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET
             * causes Init pulse to happen and SW not needed to write */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET);
            status =
                ((uint32_t) 0x1 <<
                 CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT) &
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK;

            while (status !=
                   ((status &
                     HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 CTRL_CORE_CONTROL_IO_2))))
            {
                ;
            }

            /* Write one to clear done bit */
            HW_WR_FIELD32(
                (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_CONTROL_IO_2,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE,
                CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_CLEAR);
            break;

        default:
            break;
    }
}
