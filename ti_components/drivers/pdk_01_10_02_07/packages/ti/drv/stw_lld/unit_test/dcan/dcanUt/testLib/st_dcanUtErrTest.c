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
 *  \file st_dcanUtErrTest.c
 *
 *  \brief  DCAN which tests the different error test cases of peripheral
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
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern uint32_t gDcanAppTxMsgObj;
extern uint32_t gDcanAppRxMsgObj;
extern uint32_t gDcanAppTestModeTxIfReg;
extern uint32_t gDcanAppTestModeRxIfReg;
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
int32_t st_dcanErrTest_main(st_DCANTestcaseParams_t *testParams)
{
    int32_t             retVal    = STW_SOK;
    int32_t             errStatus = STW_SOK;
    uint32_t            timeOut   = 100U;
    dcanBitTimeParams_t appDcanBitTimePrms;
    dcanRxParams_t      appDcanRxPrms;
    uint32_t            dcanMsgObjAddr;
    int32_t            *pMsgObj;
    uint32_t            msgObj;
    int32_t             errStat;

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

    if ((testParams->testErrType == ST_TET_ECC_SBE) ||
        (testParams->testErrType == ST_TET_ECC_DBE) ||
        (testParams->testErrType == ST_TET_PARITY))
    {
        dcanMsgObjAddr = (SOC_DCAN1_MESSAGERAM_BASE +
                          (testParams->dcanAppTxMsgObj * DCAN_MSG_OBJ_SIZE));

        /* Disable SECDED to corrupt the RAM */
        DCANParityEnable(testParams->dcanAppInstance, FALSE);
        if (testParams->dcanTxPrms.dataLength > 4)
            pMsgObj = (int32_t *) (dcanMsgObjAddr);
        else
            pMsgObj = (int32_t *) (dcanMsgObjAddr + 4);

        if ((testParams->testErrType == ST_TET_ECC_SBE) ||
            (testParams->testErrType == ST_TET_ECC_DBE))
        {
            /* Enable ECCDIAG mode */
            DCANEccDiagModeEnable(testParams->dcanAppInstance, TRUE);
        }
        /* RDA mode is enabled to ACCESS the MessageRAM */
        DCANTestModeEnable(testParams->dcanAppInstance, TRUE,
                           DCAN_TEST_RDA_MASK);
        /* Corrupting the data in Message RAM in RDA Mode which introduces
         * single
         * bit error.
         */
        *pMsgObj = (*pMsgObj & testParams->testErrMask);
        /* RDA mode is disabled to ACCESS the MessageRAM */
        DCANTestModeEnable(testParams->dcanAppInstance, FALSE,
                           DCAN_TEST_RDA_MASK);

        if ((testParams->testErrType == ST_TET_ECC_SBE) ||
            (testParams->testErrType == ST_TET_PARITY))
        {
            /* Enable SECDED / Parity */
            DCANParityEnable(testParams->dcanAppInstance, TRUE);

            /* Wait for interface to become free */
            st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                                   gDcanAppTestModeTxIfReg);

            retVal = DCANGetData(testParams->dcanAppInstance,
                                 testParams->dcanAppTxMsgObj,
                                 gDcanAppTestModeTxIfReg,
                                 &appDcanRxPrms,
                                 timeOut);
            /* Wait for interface to become free */
            st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                                   gDcanAppTestModeTxIfReg);

            if (testParams->testErrType == ST_TET_ECC_SBE)
            {
                /* Check for whether single bit error is detected */
                msgObj = DCANGetMsgObjBitErrDetected(
                    testParams->dcanAppInstance);

                DCANEccDiagModeEnable(testParams->dcanAppInstance, FALSE);
                DCANParityEnable(testParams->dcanAppInstance, FALSE);

                if (msgObj != testParams->dcanAppTxMsgObj)
                {
                    UARTPuts("\nDCAN -- ECC SBE test Failed!! \n", -1);
                }
                else
                {
                    UARTPuts("\nDCAN -- ECC SBE test Passed!! \n", -1);
                }
            }
            else
            {
                /* Check for whether Parity error is detected */
                errStat = DCANGetParityErrStatus(testParams->dcanAppInstance);

                DCANParityEnable(testParams->dcanAppInstance, FALSE);

                if ((errStat & DCAN_PARITY_ERR_STS_MSG_NUM) !=
                    testParams->dcanAppTxMsgObj)
                {
                    UARTPuts("\nDCAN -- ECC PARITY test Failed!! \n", -1);
                }
                else
                {
                    UARTPuts("\nDCAN -- ECC PARITY test Passed!! \n", -1);
                }
            }
        }
        else
        {
#if defined (SOC_TDA3XX)
            errStat = DCANGetEccErrStatus(testParams->dcanAppInstance);
            if ((errStat & DCAN_ECC_DB_ERR_STS) !=
                DCAN_ECC_DB_ERR_STS)
            {
                UARTPuts("\nDCAN -- ECC DBE test Failed!! \n", -1);
            }
            else
            {
                UARTPuts("\nDCAN -- ECC DBE test Passed!! \n", -1);
            }
#endif
        }
    }

    return retVal;
}

