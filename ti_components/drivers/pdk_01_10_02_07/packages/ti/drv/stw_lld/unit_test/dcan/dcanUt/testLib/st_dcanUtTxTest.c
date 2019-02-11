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
 *  \file st_dcanUtTxTest.c
 *
 *  \brief  DCAN board which transmits the data from one Node to other
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <st_dcanUt.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/cslr_synctimer.h>
#if defined (__TI_ARM_V7M4__)
#include <ti/csl/arch/csl_arch.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
volatile unsigned char        gTxDoneFlag = 0;
extern volatile unsigned char gErrStatus;
/** \brief DCAN FIFO Buffer depth used */
#define DCAN_APP_FIFO_BUF_DEPTH            (8U)
/** \brief DCAN TX FIFO Buffer start index used */
#define DCAN_APP_TX_FIFO_BUF_START_IDX        (1U)
/** \brief 32K Timer Frequency */
#define TIMER_FREQUENCY_32KCOUNTER          (32 * 1024U)
/** \brief DCAN Standard Frame Format Length excluding Data field used
 *   Start of Frame (SOF) : 1 bit field,
 *   Identifier : 11 bit field
 *   Remote transmission request  (RTR) : 1 bit field,
 *   Identifier extension bit (IDE) : 1 bit field
 *   Reserved bit (r0) : 1 bit field
 *   Data length code (DLC)  : 4 bit field
 *   Data field : (0 - 64 bit)
 *   CRC : 15 bit field
 *   CRC delimiter (r0) : 1 bit field
 *   ACK slot (r0) : 1 bit field
 *   ACK delimiter : 1 bit field
 *   End-of-frame (EOF) : 7 bit field
 */
#define DCAN_APP_STD_FIXED_FRAME_FMT_LENGTH        (44U)

/** \brief DCAN Extended Frame Format Length excluding Data field used
 *   Start of Frame (SOF) : 1 bit field,
 *   Identifier A : 11 bit field
 *   Substitute remote request  (SRR) : 1 bit field,
 *   Identifier extension bit (IDE) : 1 bit field
 *   Identifier B : 18 bit field
 *   Remote transmission request  (RTR) : 1 bit field,
 *   Reserved bit (r0) : 1 bit field
 *   Reserved bit (r1) : 1 bit field
 *   Data length code (DLC)  : 4 bit field
 *   Data field : (0 - 64 bit)
 *   CRC : 15 bit field
 *   CRC delimiter (r0) : 1 bit field
 *   ACK slot (r0) : 1 bit field
 *   ACK delimiter : 1 bit field
 *   End-of-frame (EOF) : 7 bit field
 */
#define DCAN_APP_EXT_FIXED_FRAME_FMT_LENGTH        (64U)

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
static uint32_t st_dcanRead32KTimer(void);
static uint32_t st_dcanGetTheoriticalMax(uint32_t dataLength,
                                         uint32_t msgId,
                                         uint32_t bitRate);
#if defined (__TI_ARM_V7M4__)
static void enableIPU1Unicache(void);
static void disableIPU1Unicache(void);
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_dcanTxTest_main(st_DCANTestcaseParams_t *testParams)
{
    int32_t  retVal    = STW_SOK;
    int32_t  errStatus = STW_SOK;
    uint32_t timeOut   = 100U;
    dcanBitTimeParams_t appDcanBitTimePrms;
    uint32_t intrLine;
    uint32_t msgCnt;
    uint32_t fifoBufIdx;
    uint32_t fifoBufCnt   = 1U;
    uint32_t startTimeVal = 0U;
    uint32_t endTimeVal   = 0U;
    Float32  timeTaken;
    uint32_t numMsgTxedPerSec;
    uint32_t theoriticalMaxTBA;
    uint32_t hwUtilizeStat;

    testParams->isRun = TRUE;
    gTxDoneFlag       = 0;

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

    /* Register Crossbars and IRQ numbers */
    st_dcanAppConfigIntr(testParams);

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

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_TX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line
         */
        if (testParams->dcanCfgPrms.intrLine0Enable == TRUE)
        {
            intrLine = DCAN_INTR_LINE_NUM_0;
        }
        else
        {
            intrLine = DCAN_INTR_LINE_NUM_1;
        }

        if (fifoBufIdx ==
            ((DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            testParams->dcanTxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            testParams->dcanTxCfgPrms.fifoEOBFlag = FALSE;
        }

        DCANConfigIntrMux(testParams->dcanAppInstance,
                          intrLine,
                          fifoBufIdx);
        /* Wait for interface to become free */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               testParams->dcanAppIfReg);
        retVal = DCANConfigMsgObj(testParams->dcanAppInstance,
                                  fifoBufIdx,
                                  testParams->dcanAppIfReg,
                                  &testParams->dcanTxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                               testParams->dcanAppIfReg);
    }

    if (testParams->isPerfTest)
    {
#if defined (__TI_ARM_V7M4__)
        enableIPU1Unicache();
#endif
        startTimeVal = st_dcanRead32KTimer();
    }

    for (msgCnt = 0; msgCnt < testParams->numMsg; msgCnt++)
    {
        gErrStatus = 0;

        if (retVal == STW_SOK)
        {
            while (DCANIsTxMsgPending(testParams->dcanAppInstance, fifoBufCnt)) ;

            /* Wait for interface to become free */
            st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                                   testParams->dcanAppIfReg);
            retVal = DCANTransmitData(testParams->dcanAppInstance,
                                      fifoBufCnt,
                                      testParams->dcanAppIfReg,
                                      &testParams->dcanTxPrms,
                                      timeOut);
            /* Wait for config to be copied to internal message RAM */
            st_dcanAppWaitForIfReg(testParams->dcanAppInstance,
                                   testParams->dcanAppIfReg);

            fifoBufCnt++;
            if (fifoBufCnt > DCAN_APP_FIFO_BUF_DEPTH)
                fifoBufCnt = 1;
        }

        if (retVal == STW_SOK)
        {
            /* check for Error is occured or not */
            if (gErrStatus != 0)
            {
                retVal = STW_EFAIL;
                break;
            }
        }
        else
        {
            break;
        }
    }

    for (fifoBufCnt = 1; fifoBufCnt <= DCAN_APP_FIFO_BUF_DEPTH; fifoBufCnt++)
    {
        while (DCANIsTxMsgPending(testParams->dcanAppInstance, fifoBufCnt)) ;
    }

    if (testParams->isPerfTest)
    {
        endTimeVal = st_dcanRead32KTimer();
#if defined (__TI_ARM_V7M4__)
        disableIPU1Unicache();
#endif
    }

    if (retVal == STW_EFAIL)
    {
        UARTprintf("\nDCAN -- Board to Board Test (TX) Failed!! \n");
        testParams->testResult = STW_EFAIL;
    }
    else
    {
        UARTprintf("\nDCAN -- Board to Board Test (TX) Passed!! \n");
        testParams->testResult = STW_SOK;
    }

    if (testParams->isPerfTest)
    {
        timeTaken =
            ((Float32) (endTimeVal -
                        startTimeVal)) / ((Float32) TIMER_FREQUENCY_32KCOUNTER);
        numMsgTxedPerSec =
            (uint32_t) (((Float32) testParams->numMsg) / ((Float32) timeTaken));

        theoriticalMaxTBA = st_dcanGetTheoriticalMax(
            testParams->dcanTxPrms.dataLength,
            testParams->dcanTxCfgPrms.
            xIdFlag,
            testParams->bitrate);

        hwUtilizeStat =
            (uint32_t) ((((Float32) numMsgTxedPerSec) /
                         ((Float32) theoriticalMaxTBA)) * 100);

        UARTprintf("\n Messages transmitted per sec = %d ", numMsgTxedPerSec);
        UARTprintf("\n Theoritical Max to be achieved = %d ", theoriticalMaxTBA);
        UARTprintf("\n DCAN HW utilization achieved = %d", hwUtilizeStat);
        UARTPuts("% ", -1);
    }
    return retVal;
}

static uint32_t st_dcanRead32KTimer(void)
{
    uint32_t timerVal = 0U;

    /* Read the counter value for 32 KHz SoC Synchronous Timer */
    timerVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    return timerVal;
}

static uint32_t st_dcanGetTheoriticalMax(uint32_t dataLength,
                                         uint32_t msgId,
                                         uint32_t bitRate)
{
    uint32_t theoriticalMax;
    uint32_t numBitsPerMsg;

    if (msgId == DCAN_XID_11_BIT)
    {
        /*Data field : (dataLength * 8) */
        numBitsPerMsg = DCAN_APP_STD_FIXED_FRAME_FMT_LENGTH + (dataLength * 8);
    }
    else
    {
        /*Data field : (dataLength * 8) */
        numBitsPerMsg = DCAN_APP_EXT_FIXED_FRAME_FMT_LENGTH + (dataLength * 8);
    }
    theoriticalMax = bitRate / numBitsPerMsg;

    return theoriticalMax;
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
