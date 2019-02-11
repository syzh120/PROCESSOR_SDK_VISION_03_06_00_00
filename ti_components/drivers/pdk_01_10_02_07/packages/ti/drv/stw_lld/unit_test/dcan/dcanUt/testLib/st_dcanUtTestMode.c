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
 *  \file st_dcanUtTestMode.c
 *
 *  \brief  DCAN which tests the different test modes of peripheral
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <string.h>
#include <st_dcanUt.h>
#include <ti/drv/stw_lld/platform/platform.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
volatile unsigned char gTestModeTxDoneFlag = 0;
volatile unsigned char gTestModeRxDoneFlag = 0;

extern uint32_t        gDcanAppTestModeTxIfReg;
extern uint32_t        gDcanAppTestModeRxIfReg;
extern uint32_t        gDcanAppTxMsgObj;
extern uint32_t        gDcanAppRxMsgObj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_dcanTestModeTest_main(st_DCANTestcaseParams_t *testParams)
{
    int32_t                 retVal    = STW_SOK;
    int32_t                 errStatus = STW_SOK;
    int32_t                 status    = FALSE;
    uint32_t                timeOut   = 100U;
    dcanBitTimeParams_t     appDcanBitTimePrms;
    uint32_t                intrLine;
    dcanRxParams_t          appDcanRxPrms;
    uint32_t                dataLength;
    st_TestDataTransferMode dataTransferMode = ST_TT_DTM_INT;
    uint32_t                msgLstErrCnt          = 0U;
    uint32_t                dataMissMatchErrCnt   = 0U;
    uint32_t                msgIdentifierMissMatchErrCnt   = 0U;
    uint32_t                frameTypeMissMatchErrCnt   = 0U;

    testParams->isRun = TRUE;

    gDcanAppTxMsgObj = testParams->dcanAppTxMsgObj;
    gDcanAppRxMsgObj = testParams->dcanAppRxMsgObj;

    if (testParams->dcanAppIfReg == DCAN_IF_REG_NUM_1)
    {
        gDcanAppTestModeTxIfReg = DCAN_IF_REG_NUM_1;
        gDcanAppTestModeRxIfReg = DCAN_IF_REG_NUM_2;
    }
    else
    {
        gDcanAppTestModeTxIfReg = DCAN_IF_REG_NUM_2;
        gDcanAppTestModeRxIfReg = DCAN_IF_REG_NUM_1;
    }

    if (testParams->dcanAppInstance == DCAN1_APP_INST)
    {
        UARTprintf("\nDCAN Transmit Test App: DCAN1 MSG OBJ 1 (TX) \n");

#if defined (__TI_ARM_V7M4__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif
    }
    else
    {
        UARTprintf("\nDCAN Transmit Test App: DCAN2 MSG OBJ 1 (TX)\n");

#if defined (__TI_ARM_V7M4__)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         *  must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif
    }

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    if (testParams->dcanAppInstance == DCAN1_APP_INST)
    {
        /* Clock Configuration. */
        PlatformDCAN1PrcmEnable();

        /* Perform the DCAN pinmux. */
        PlatformDCAN1SetPinMux();

        /* Initialize the DCAN message RAM. */
        PlatformDcanMessageRamInit(0);
    }
    else
    {
        /* Clock Configuration. */
        PlatformDCAN2PrcmEnable();

        /* Perform the DCAN pinmux. */
        PlatformDCAN2SetPinMux();

        /* Initialize the DCAN message RAM. */
        PlatformDcanMessageRamInit(1);
    }

    gTestModeTxDoneFlag = 0;
    gTestModeRxDoneFlag = 0;

    if ((testParams->dcanCfgPrms.intrLine0Enable == TRUE) ||
        (testParams->dcanCfgPrms.intrLine1Enable == TRUE))
    {
        /* Register Crossbars and IRQ numbers */
        st_dcanAppConfigIntr(testParams);
    }

    /* Reset the DCAN IP */
    retVal = DCANReset(testParams->dcanAppInstance, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(testParams->dcanAppInstance, DCAN_MODE_INIT);
        errStatus = st_dcanAppCalculateBitTimeParams(
            testParams->clkFreq / 1000000,
            testParams->bitrate / 1000,
            testParams->refSamplePoint,
            testParams->propDelay,
            &appDcanBitTimePrms);
        if (errStatus != STW_SOK)
        {
            return errStatus;
        }
        DCANSetBitTime(testParams->dcanAppInstance, &appDcanBitTimePrms);
        DCANSetMode(testParams->dcanAppInstance, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(testParams->dcanAppInstance, &testParams->dcanCfgPrms);

        /*
         * Enable message object interrupt to route interrupt line
         */
        if (testParams->dcanCfgPrms.intrLine0Enable == TRUE)
        {
            dataTransferMode = ST_TT_DTM_INT;
            intrLine         = DCAN_INTR_LINE_NUM_0;
        }
        else if (testParams->dcanCfgPrms.intrLine1Enable == TRUE)
        {
            dataTransferMode = ST_TT_DTM_INT;
            intrLine         = DCAN_INTR_LINE_NUM_1;
        }
        else
        {
            dataTransferMode = ST_TT_DTM_POLLED;
        }

        if (dataTransferMode == ST_TT_DTM_INT)
        {
            DCANConfigIntrMux(testParams->dcanAppInstance,
                              intrLine,
                              testParams->dcanAppTxMsgObj);

            DCANConfigIntrMux(testParams->dcanAppInstance,
                              intrLine,
                              testParams->dcanAppRxMsgObj);
        }
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeRxIfReg);
        retVal = DCANConfigMsgObj(testParams->dcanAppInstance,
                                  testParams->dcanAppRxMsgObj,
                                  gDcanAppTestModeRxIfReg,
                                  &testParams->dcanRxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeRxIfReg);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeTxIfReg);

        retVal = DCANConfigMsgObj(testParams->dcanAppInstance,
                                  testParams->dcanAppTxMsgObj,
                                  gDcanAppTestModeTxIfReg,
                                  &testParams->dcanTxCfgPrms);

        /* Wait for config to be copied to internal message RAM */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeTxIfReg);
    }

    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeTxIfReg);
        retVal = DCANTransmitData(testParams->dcanAppInstance,
                                  testParams->dcanAppTxMsgObj,
                                  gDcanAppTestModeTxIfReg,
                                  &testParams->dcanTxPrms,
                                  timeOut);
        /* Wait for config to be copied to internal message RAM */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeTxIfReg);
    }

    if (dataTransferMode == ST_TT_DTM_INT)
    {
        if (retVal == STW_SOK)
        {
            /* Wait for transmit interrupt */
            while (gTestModeTxDoneFlag == 0) ;
        }

        if (retVal == STW_SOK)
        {
            /* Wait for receive interrupt */
            while (gTestModeRxDoneFlag == 0) ;
        }
    }
    else
    {
        do
        {
            status = DCANIsTxMsgPending(testParams->dcanAppInstance,
                                        testParams->dcanAppTxMsgObj);
        }
        while (status != FALSE); // wait for the transmission to be completed.
        do
        {
            status = DCANHasRxMsgArrived(testParams->dcanAppInstance,
                                         testParams->dcanAppRxMsgObj);
        }
        while (status != TRUE); // wait for the arrival of new data
    }

    if (retVal == STW_SOK)
    {
        /* Clear RX structure */
        memset(&appDcanRxPrms, 0, sizeof (appDcanRxPrms));

        /* Wait for interface to become free */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               gDcanAppTestModeRxIfReg);

        retVal = DCANGetData(testParams->dcanAppInstance,
                             testParams->dcanAppRxMsgObj,
                             gDcanAppTestModeRxIfReg,
                             &appDcanRxPrms,
                             timeOut);
    }

    dataLength = 0;

    if (retVal == STW_SOK)
    {
        /* Check if sent data is lost or not */
        if (appDcanRxPrms.msgLostFlag == TRUE)
        {
            msgLstErrCnt++;
        }

        /* Check if sent Frame type has been received */
        if (retVal == STW_SOK)
        {
            /* Check if sent  Frame type has been received */
            if (appDcanRxPrms.rxFrameType != testParams->dcanRxPrms.rxFrameType)
            {
                retVal = STW_EFAIL;
                frameTypeMissMatchErrCnt++;
            }
        }

        /* Check if sent Msg Identifier has been received */
        if (retVal == STW_SOK)
        {
            /* Check if sent  Msg Identifier has been received */
            if ((appDcanRxPrms.rxMsgIdentifier !=
                 testParams->dcanRxPrms.rxMsgIdentifier) ||
                (appDcanRxPrms.rxIdType != testParams->dcanRxPrms.rxIdType))
            {
                retVal = STW_EFAIL;
                msgIdentifierMissMatchErrCnt++;
            }
        }

        /* Check if expected data has been received */
        if (appDcanRxPrms.dataLength == testParams->dcanRxPrms.dataLength)
        {
            while (dataLength < appDcanRxPrms.dataLength)
            {
                if (appDcanRxPrms.msgData[dataLength] !=
                    testParams->dcanRxPrms.msgData[dataLength])
                {
                    retVal = STW_EFAIL;
                }
                dataLength++;
            }
        }
        else
        {
            retVal = STW_EFAIL;
            dataMissMatchErrCnt++;
        }
    }

    if (((msgLstErrCnt == 0) && (msgIdentifierMissMatchErrCnt == 0) &&
        (frameTypeMissMatchErrCnt == 0) && (dataMissMatchErrCnt == 0)) &&
        (retVal == STW_SOK))
    {
        UARTprintf("\nDCAN -- Test Mode Passed!! \n");
        testParams->testResult = STW_SOK;
    }
    else
    {
        UARTprintf("\nDCAN -- Test Mode Failed!! \n");
        testParams->testResult = STW_EFAIL;
    }

    return retVal;
}

