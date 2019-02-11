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
 *  \file st_dcanTestStubRxTest.c
 *
 *  \brief  DCAN board which receives the data from can Node
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <string.h>
#include <st_dcanTestStub.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_dcan.h>
#if defined (__TI_ARM_V7M4__)
#include <ti/csl/arch/csl_arch.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
volatile unsigned char        gTestStubRxDoneFlag = 0;
extern volatile unsigned char gTestStubErrStatus;
volatile unsigned int         gMsgObj[20] = {0};
volatile unsigned char        gIsrCnt   = 0;
volatile unsigned char        gRxAppCnt = 0;
extern uint32_t gPerfTest;

/** \brief DCAN FIFO Buffer depth used */
#define DCAN_APP_FIFO_BUF_DEPTH            (8U)
/** \brief DCAN RX FIFO Buffer start index used */
#define DCAN_APP_RX_FIFO_BUF_START_IDX        (30U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if defined (__TI_ARM_V7M4__)
static void enableIPU1Unicache(void);
static void disableIPU1Unicache(void);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_dcanTestStubRxTest_main(st_DCANTestcaseParams_t *testParams)
{
    int32_t             retVal    = STW_SOK;
    int32_t             errStatus = STW_SOK;
    dcanBitTimeParams_t appDcanBitTimePrms;
    dcanRxParams_t      appDcanRxPrms;
    uint32_t            timeOut    = 100U;
    uint32_t            dataLength = 0U;
    uint32_t            msgCnt, fifoBufIdx;
    uint32_t            rxMsgStatus         = FALSE;
    uint32_t            msgLstErrCnt        = 0U;
    uint32_t            dataMissMatchErrCnt = 0U;
    uint32_t            msgIdentifierMissMatchErrCnt = 0U;
    uint32_t            frameTypeMissMatchErrCnt = 0U;

    UARTprintf("\nDCAN Receive Test App: DCAN MSG OBJ (RX)\n");

#if defined (__TI_ARM_V7M4__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
     * IPU1_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal must
     * reach the peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
     * MPU_C0 & SENS_CTRL(Sensitivity control) as 1 means suspend signal must
     * reach the peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Register Crossbars and IRQ numbers */
    st_dcanAppTestStubConfigIntr(testParams);

    if (gPerfTest == 1)
    {
#if defined (__TI_ARM_V7M4__)
        enableIPU1Unicache();
#endif
    }

    /* Reset the DCAN IP */
    retVal = DCANReset(DCAN1_APP_INST, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(DCAN1_APP_INST, DCAN_MODE_INIT);
        errStatus = st_dcanAppTestStubCalculateBitTimeParams(
            testParams->clkFreq / 1000000,
            testParams->bitrate / 1000,
            testParams->refSamplePoint,
            testParams->propDelay,
            &appDcanBitTimePrms);
        if (errStatus != STW_SOK)
        {
            return errStatus;
        }
        DCANSetBitTime(DCAN1_APP_INST, &appDcanBitTimePrms);
        DCANSetMode(DCAN1_APP_INST, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(DCAN1_APP_INST, &testParams->dcanCfgPrms);
    }

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_RX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_RX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line
         */
        DCANConfigIntrMux(DCAN1_APP_INST, DCAN_INTR_LINE_NUM_0,
                          fifoBufIdx);
        if (fifoBufIdx ==
            ((DCAN_APP_RX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            testParams->dcanRxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            testParams->dcanRxCfgPrms.fifoEOBFlag = FALSE;
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            st_dcanAppTestStubWaitForIfReg(DCAN1_APP_INST,
                                           DCAN_IF_REG_NUM_1);
            retVal = DCANConfigMsgObj(DCAN1_APP_INST,
                                      fifoBufIdx,
                                      DCAN_IF_REG_NUM_1,
                                      &testParams->dcanRxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            st_dcanAppTestStubWaitForIfReg(DCAN1_APP_INST,
                                           DCAN_IF_REG_NUM_1);
        }
    }
    memset(&appDcanRxPrms, 0, sizeof (dcanRxParams_t));
    UARTprintf("\nWaiting for message from DCAN1 TX....\n");

    for (msgCnt = 0; msgCnt < testParams->numMsg; msgCnt++)
    {
        rxMsgStatus         = 0;
        gTestStubRxDoneFlag = 0;
        gTestStubErrStatus  = 0;
        if (msgCnt == 0)
        {
            if (retVal == STW_SOK)
            {
                /* Wait for Receive / Error interrupt */
                while ((gTestStubRxDoneFlag == 0) && (gTestStubErrStatus == 0)) ;
                /* Check for whether error is occured or not */
                if (gTestStubErrStatus != 0)
                {
                    retVal = STW_EFAIL;
                    break;
                }
            }
        }
        else
        {
            if (gTestStubErrStatus != 0)
            {
                retVal = STW_EFAIL;
                break;
            }
        }

        if (retVal == STW_SOK)
        {
            while (!rxMsgStatus)
            {
                /* check for msg is arrived or not */
                rxMsgStatus =
                    DCANHasRxMsgArrived(DCAN1_APP_INST, gMsgObj[gRxAppCnt]);
            }
            if (rxMsgStatus == TRUE)
            {
                /* Clear RX structure */
                memset(&appDcanRxPrms, 0, sizeof (appDcanRxPrms));

                /* Wait for interface to become free */
                st_dcanAppTestStubWaitForIfReg(DCAN1_APP_INST,
                                               DCAN_IF_REG_NUM_1);
                retVal = DCANGetData(DCAN1_APP_INST,
                                     gMsgObj[gRxAppCnt++],
                                     DCAN_IF_REG_NUM_1,
                                     &appDcanRxPrms,
                                     timeOut);

                if (gRxAppCnt == 20)
                    gRxAppCnt = 0;
            }
        }

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
                if (appDcanRxPrms.rxFrameType !=
                    testParams->dcanRxPrms.rxFrameType)
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
                    (appDcanRxPrms.rxIdType !=
                     testParams->dcanRxPrms.rxIdType))
                {
                    retVal = STW_EFAIL;
                    msgIdentifierMissMatchErrCnt++;
                }
            }

            /* Check if sent data has been received */
            if (retVal == STW_SOK)
            {
                /* Check if sent data has been received */
                if (appDcanRxPrms.dataLength ==
                    testParams->dcanRxPrms.dataLength)
                {
                    dataLength = 0U;
                    while (dataLength < appDcanRxPrms.dataLength)
                    {
                        if (appDcanRxPrms.msgData[dataLength] !=
                            testParams->dcanRxPrms.msgData[dataLength])
                        {
                            retVal = STW_EFAIL;
                            dataMissMatchErrCnt++;
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
        }
    }

    if (gPerfTest == 1)
    {
#if defined (__TI_ARM_V7M4__)
        disableIPU1Unicache();
#endif
    }

    if (((msgLstErrCnt == 0) && (frameTypeMissMatchErrCnt == 0) &&
         (msgIdentifierMissMatchErrCnt == 0) && (dataMissMatchErrCnt == 0)) &&
         (retVal == STW_SOK))
    {
        UARTprintf("\nDCAN -- Board to Board Test (RX) Passed!! \n");
    }
    else
    {
        UARTprintf("\nDCAN -- Board to Board Test (RX) Failed!! \n");
    }

    return retVal;
}

#if defined (__TI_ARM_V7M4__)
static void enableIPU1Unicache(void)
{
    UNICACHEInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE, UNICACHE_WAIT_INFINITE);
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
}

static void disableIPU1Unicache(void)
{
    UNICACHEWriteBackAndInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE, UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);

}

#endif
