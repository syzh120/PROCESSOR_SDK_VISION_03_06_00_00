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

/**
 *  \file     dcan_evm_loopback_app_main.c
 *
 *  \brief    This file contains DCAN board to board loopback test for TX and RX
 *
 *  \details  DCAN board to board which tests the Tx from board 1 output to
 *            Rx input of board 2. Transmitted messages are treated as
 *            received messages and can be stored into message objects if they
 *            pass acceptance filtering.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_dcan.h>

#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief 32K Timer Frequency */
#define TIMER_FREQUENCY_32KCOUNTER          (32 * 1024U)

/** \brief DCAN instance used */
#define DCAN_APP_INST                   (SOC_DCAN1_BASE)

/** \brief DCAN interrupt line used */
#define DCAN_APP_INTR_LINE_NUM          (DCAN_INTR_LINE_NUM_0)

/** \brief DCAN input clock - 20MHz */
#define DCAN_APP_INPUT_CLK              (20000000U)
/** \brief DCAN output bit rate - 1MHz */
#define DCAN_APP_BIT_RATE               (1000000U)
/** \brief DCAN Propagation Delay - 700ns */
#define DCAN_APP_PROP_DELAY               (700U)
/** \brief DCAN Sampling Point - 70% */
#define DCAN_APP_SAMP_PT               (70U)

/** \brief DCAN TX interface register used */
#define DCAN_APP_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define DCAN_APP_RX_IF_REG              (DCAN_IF_REG_NUM_2)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0          (0x5)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (0x3)

#define DCAN_TX_TEST       ('1')
#define DCAN_RX_TEST       ('2')
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/** \brief DCAN message object identifier used */
#define DCAN_APP_MSG_IDENTIFIER            (0xC1)
/** \brief DCAN FIFO Buffer depth used */
#define DCAN_APP_FIFO_BUF_DEPTH            (8U)
/** \brief DCAN TX FIFO Buffer start index used */
#define DCAN_APP_TX_FIFO_BUF_START_IDX        (1U)
/** \brief DCAN RX FIFO Buffer start index used */
#define DCAN_APP_RX_FIFO_BUF_START_IDX        (30U)

/** \brief Global Buffer Size which used to track Received Message Object*/
#define DCAN_APP_RX_BUF_SIZE        (20U)

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
/*                         Structures and Enums                               */
/* ========================================================================== */

/* NONE*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void DCANAppConfigIntr(char mainMenuOption);
static void DCANAppTxIntIsr();
static void DCANAppRxIntIsr();

static void DCANAppInitCfgParams(dcanCfgParams_t *pDcanCfgPrms);

static void DCANAppInitTxParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                dcanTxParams_t        *pDcanTxPrms,
                                uint32_t               dataLength,
                                uint8_t               *dataBuffer,
                                uint32_t               msgIdType,
                                uint32_t               msgIdentifier);

static void DCANAppInitRxParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                                uint32_t               msgIdType,
                                uint32_t               msgIdentifier);

static void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum);

/**
 * \brief   This function takes I/P Clk frequency, required bit-rate, reference
 *          sampling point, propagation delayon the CAN bus and calculates the
 *          value to be programmed for DCAN BTR register.
 *          This API doesn't do the actual programming. This is
 *          intended to be used as a utility function. And the application
 *          should call the #DCANSetBitTime function to do the actual
 *          programming.
 *
 * \param   clkFreq       I/P clock frequency to DCAN controller in terms of MHz
 * \param   bitRate       Required bit-rate on the CAN bus in KHz
 * \param   refSamplePnt  Reference Sampling point in terms of %
 * \param   propDelay     Required Propagation delay in terms of ns
 * \param   pBitTimePrms  Pointer to params where the calculated register
 *                        fields are populated
 *
 * \return  Returns the error status information as STW_SOK for success and
 *          STW_EFAIL when no valid baudrate calculation possible for the
 *          configured baudrate and propagation delay
 */
int32_t DCANCalcBitTimeParams(uint32_t             clkFreq,
                              uint32_t             bitRate,
                              uint32_t             refSamplePnt,
                              uint32_t             propDelay,
                              dcanBitTimeParams_t *pBitTimePrms);

volatile unsigned char gRxDoneFlag          = 0;
volatile unsigned char gErrStatus           = 0;
volatile unsigned char gEccRParityErrStatus = 0;

volatile unsigned int  gMsgObj[DCAN_APP_RX_BUF_SIZE] = {0};
volatile unsigned char gIsrCnt   = 0;
volatile unsigned char gRxAppCnt = 0;

static void mainMenu(char *option);
static void mainSubMenu(char      mainMenuOption,
                        uint32_t *dataLength,
                        uint8_t  *dataBuffer,
                        uint32_t *numMsg,
                        uint32_t *msgIdType,
                        uint32_t *msgIdentifier);

static int32_t dcanTxTest(char mainMenuOption);
static int32_t dcanRxTest(char mainMenuOption);
static uint32_t read32KTimer(void);
static uint32_t dcanGetTheoriticalMax(uint32_t dataLength,
                                      uint32_t msgId,
                                      uint32_t bitRate);
#if defined (__TI_ARM_V7M4__)
static void enableIPU1Unicache(void);
static void disableIPU1Unicache(void);
#endif

#if defined (__TI_ARM_V7M4__)
uint32_t gIntrNum = 28U;
#elif defined (__ARM_ARCH_7A__)
uint32_t gIntrNum = 77U;
#endif

int main(void)
{
    volatile uint32_t testDone = 1;
    char mainMenuOption;
    int32_t           retVal = STW_SOK;
#if defined (SOC_TDA2XX)
    uint32_t          siliconRev;
#endif

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();

#if defined (SOC_TDA2XX)
    siliconRev = PlatformGetSiliconRev();

    if (0U == siliconRev)
    {
        UARTPuts(
            "\r\nDCAN Evm Loopback is not supported for Tda2xx PG1.0 Silicon", -1);
        return 0;
    }
#endif

#if defined (__TI_ARM_V7M4__)
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)|| defined (SOC_TDA2EX)
    StwUtils_appConfig32KCounterSuspendState();
#endif
#endif

#if defined (SOC_TDA2PX)
    PlatformDCAN1PadConfig();
#endif

    while (1)
    {
        mainMenu(&mainMenuOption);
        if (DCAN_TX_TEST == mainMenuOption)
        {
            retVal = dcanTxTest(mainMenuOption);
        }
        else if (DCAN_RX_TEST == mainMenuOption)
        {
            retVal = dcanRxTest(mainMenuOption);
        }
        else
        {
            UARTPuts("\r\nDCAN Evm Loopback test exiting...", -1);
            break;
        }
    }
    while (testDone) ;
    return retVal;
}

static int32_t dcanTxTest(char mainMenuOption)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanTxParams_t        appDcanTxPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    uint32_t              timeOut       = 100U;
    uint32_t              msgCnt        = 0U;
    uint32_t              numMsg        = 0U;
    uint32_t              dataLength    = 0U;
    uint8_t               dataBuffer[8] = {0};
    uint32_t              fifoBufIdx;
    uint32_t              fifoBufCnt   = 1U;
    uint32_t              startTimeVal = 0U;
    uint32_t              endTimeVal   = 0U;
    Float32               timeTaken;
    uint32_t              numMsgTxedPerSec;
    uint32_t              theoriticalMaxTBA;
    uint32_t              hwUtilizeStat;
    uint32_t              msgIdType    = 0U;
    uint32_t              msgIdentifier    = 0U;

    UARTPuts("\r\nDCAN Transmit Test App: DCAN1 MSG OBJ 1 (TX)", -1);

    /* Configure the Control module & Dcan Clock */
    retVal = PlatformDcanClkConfig(0);
    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\r\nControl module & Dcan Clock Configure fails", -1);
    }

    mainSubMenu(mainMenuOption, &dataLength, dataBuffer, &numMsg, &msgIdType, &msgIdentifier);

#if defined (__TI_ARM_V7M4__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as MPU_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif

    DCANAppInitCfgParams(&appDcanCfgPrms);
    DCANAppInitTxParams(&appDcanTxCfgPrms, &appDcanTxPrms, dataLength,
                        dataBuffer, msgIdType, msgIdentifier);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Register Crossbars and IRQ numbers */
    DCANAppConfigIntr(mainMenuOption);

    /* Reset the DCAN IP */
    retVal = DCANReset(DCAN_APP_INST, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_INIT);
        errStatus = DCANCalcBitTimeParams(DCAN_APP_INPUT_CLK / 1000000,
                                          DCAN_APP_BIT_RATE / 1000,
                                          DCAN_APP_SAMP_PT,
                                          DCAN_APP_PROP_DELAY,
                                          &appDcanBitTimePrms);
        if (errStatus != STW_SOK)
        {
            return errStatus;
        }

        DCANSetBitTime(DCAN_APP_INST, &appDcanBitTimePrms);
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(DCAN_APP_INST, &appDcanCfgPrms);
    }

    if (appDcanCfgPrms.parityEnable == TRUE)
    {
        /* Priming DCAN message RAM to generate ECC/Parity Bits*/
        PlatformDcanMessageRamInit(0);
    }

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_TX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line 0/1
         */
        DCANConfigIntrMux(DCAN_APP_INST, DCAN_APP_INTR_LINE_NUM, fifoBufIdx);

        if (fifoBufIdx ==
            ((DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            appDcanTxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            appDcanTxCfgPrms.fifoEOBFlag = FALSE;
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            retVal = DCANConfigMsgObj(DCAN_APP_INST,
                                      fifoBufIdx,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        }
    }

#if defined (__TI_ARM_V7M4__)
    enableIPU1Unicache();
#endif
    startTimeVal = read32KTimer();

    for (msgCnt = 0; msgCnt < numMsg; msgCnt++)
    {
        gErrStatus = 0;

        if (retVal == STW_SOK)
        {
            while (DCANIsTxMsgPending(DCAN_APP_INST, fifoBufCnt)) ;

            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            retVal = DCANTransmitData(DCAN_APP_INST,
                                      fifoBufCnt,
                                      DCAN_APP_TX_IF_REG,
                                      &appDcanTxPrms,
                                      timeOut);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
            fifoBufCnt++;

            if (fifoBufCnt > DCAN_APP_FIFO_BUF_DEPTH)
                fifoBufCnt = 1;
        }
        if (retVal == STW_SOK)
        {
            /* check for Error is occured or not */
            if ((gErrStatus != 0) && (gEccRParityErrStatus != 0))
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

    if (retVal == STW_SOK)
    {
        for (fifoBufCnt = 1; fifoBufCnt <= DCAN_APP_FIFO_BUF_DEPTH;
             fifoBufCnt++)
        {
            while (DCANIsTxMsgPending(DCAN_APP_INST, fifoBufCnt)) ;
        }
    }

    endTimeVal = read32KTimer();
#if defined (__TI_ARM_V7M4__)
    disableIPU1Unicache();
#endif

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\r\nDCAN -- Board to Board Test (TX) Failed!! \r\n", -1);
    }
    else
    {
        UARTPuts("\r\nDCAN -- Board to Board Test (TX) Passed!! \r\n", -1);
    }

    timeTaken =
        ((Float32) (endTimeVal -
                    startTimeVal)) / ((Float32) TIMER_FREQUENCY_32KCOUNTER);
    numMsgTxedPerSec = (uint32_t) (((Float32) numMsg) / ((Float32) timeTaken));

    theoriticalMaxTBA = dcanGetTheoriticalMax(dataLength,
                                              appDcanTxCfgPrms.xIdFlag,
                                              DCAN_APP_BIT_RATE);

    hwUtilizeStat =
        (uint32_t) ((((Float32) numMsgTxedPerSec) /
                     ((Float32) theoriticalMaxTBA)) * 100);

    UARTPuts("\r\n Messages transmitted per sec: ", -1);
    UARTPutNum(numMsgTxedPerSec);

    UARTPuts("\r\n Theoritical Max to be achieved :", -1);
    UARTPutNum(theoriticalMaxTBA);

    UARTPuts("\r\n DCAN HW utilization achieved : ", -1);
    UARTPutNum(hwUtilizeStat);
    UARTPuts("% ", -1);

    return retVal;
}

static int32_t dcanRxTest(char mainMenuOption)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    dcanRxParams_t        appDcanRxPrms;
    uint32_t              timeOut    = 100U;
    uint32_t              dataLength = 0U;
    uint32_t              msgCnt, fifoBufIdx, i;
    uint32_t              rxMsgStatus           = FALSE;
    uint32_t              msgLstErrCnt          = 0U;
    uint32_t              dataMissMatchErrCnt   = 0U;
    uint32_t              msgIdentifierMissMatchErrCnt   = 0U;
    uint32_t              frameTypeMissMatchErrCnt   = 0U;
    uint32_t              expectedDataLength    = 0U;
    uint32_t              expectedNumMsg        = 0U;
    uint8_t               expectedDataBuffer[8] = {0};
    uint32_t              expectedFrameType    = DCAN_DATA_FRAME;
    uint32_t              expectedMsgIdType    = 0U;
    uint32_t              expectedMsgIdentifier    = 0U;

    UARTPuts("\r\nDCAN Receive Test App: DCAN1 MSG OBJ (RX)", -1);

    for (i = 0; i < DCAN_APP_RX_BUF_SIZE; i++)
    {
        /* Intialize gMsgObj buffer with DCAN_APP_RX_FIFO_BUF_START_IDX */
        gMsgObj[i] = DCAN_APP_RX_FIFO_BUF_START_IDX;
    }

    retVal = PlatformDcanClkConfig(0);
    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\r\nControl module & Dcan Clock Configure fails", -1);
    }

    mainSubMenu(mainMenuOption, &expectedDataLength, expectedDataBuffer,
                &expectedNumMsg, &expectedMsgIdType, &expectedMsgIdentifier);

    if(expectedMsgIdType == DCAN_XID_11_BIT)
    {
        expectedMsgIdentifier = expectedMsgIdentifier & DCAN_MSGID_MASK_STD;
    }
    else
    {
        expectedMsgIdentifier = expectedMsgIdentifier & DCAN_MSGID_MASK_XTD;
    }

#if defined (__TI_ARM_V7M4__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as MPU_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#endif

    DCANAppInitCfgParams(&appDcanCfgPrms);
    DCANAppInitRxParams(&appDcanRxCfgPrms,
                        expectedMsgIdType,
                        expectedMsgIdentifier);

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN1RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();
#if defined (__TI_ARM_V7M4__)
    enableIPU1Unicache();
#endif

    /* Register Crossbars and IRQ numbers */
    DCANAppConfigIntr(mainMenuOption);

    /* Reset the DCAN IP */
    retVal = DCANReset(DCAN_APP_INST, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_INIT);
        errStatus = DCANCalcBitTimeParams(DCAN_APP_INPUT_CLK / 1000000,
                                          DCAN_APP_BIT_RATE / 1000,
                                          DCAN_APP_SAMP_PT,
                                          DCAN_APP_PROP_DELAY,
                                          &appDcanBitTimePrms);
        if (errStatus != STW_SOK)
        {
            return errStatus;
        }
        DCANSetBitTime(DCAN_APP_INST, &appDcanBitTimePrms);
        DCANSetMode(DCAN_APP_INST, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(DCAN_APP_INST, &appDcanCfgPrms);
    }

    if (appDcanCfgPrms.parityEnable == TRUE)
    {
        /* Priming DCAN message RAM to generate ECC/Parity Bits*/
        PlatformDcanMessageRamInit(0);
    }

    /* Configuring FIFO Buffer of depth DCAN_APP_FIFO_BUF_DEPTH*/
    for (fifoBufIdx = DCAN_APP_RX_FIFO_BUF_START_IDX;
         fifoBufIdx < (DCAN_APP_RX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH);
         fifoBufIdx++)
    {
        /*
         * Enable message object interrupt to route interrupt line 0/1
         */
        DCANConfigIntrMux(DCAN_APP_INST, DCAN_APP_INTR_LINE_NUM, fifoBufIdx);

        if (fifoBufIdx ==
            ((DCAN_APP_TX_FIFO_BUF_START_IDX + DCAN_APP_FIFO_BUF_DEPTH) - 1))
        {
            appDcanRxCfgPrms.fifoEOBFlag = TRUE;
        }
        else
        {
            appDcanRxCfgPrms.fifoEOBFlag = FALSE;
        }
        if (retVal == STW_SOK)
        {
            /* Wait for interface to become free */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
            retVal = DCANConfigMsgObj(DCAN_APP_INST,
                                      fifoBufIdx,
                                      DCAN_APP_RX_IF_REG,
                                      &appDcanRxCfgPrms);
            /* Wait for config to be copied to internal message RAM */
            DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
        }
    }

    memset(&appDcanRxPrms, 0, sizeof (dcanRxParams_t));

    UARTPuts("\r\nWaiting for message from DCAN1 TX....\r\n", -1);

    for (msgCnt = 0; msgCnt < expectedNumMsg; msgCnt++)
    {
        rxMsgStatus = 0;
        gRxDoneFlag = 0;
        gErrStatus  = 0;

        if (msgCnt == 0)
        {
            if (retVal == STW_SOK)
            {
                /* Wait for Receive / Error interrupt */
                while ((gRxDoneFlag == 0) &&
                       ((gErrStatus == 0) && (gEccRParityErrStatus == 0))) ;
                /* Check for whether error is occured or not */
                if ((gErrStatus != 0) && (gEccRParityErrStatus != 0))
                {
                    retVal = STW_EFAIL;
                    break;
                }
            }
        }
        else
        {
            if ((gErrStatus != 0) && (gEccRParityErrStatus != 0))
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
                    DCANHasRxMsgArrived(DCAN_APP_INST, gMsgObj[gRxAppCnt]);
            }
            if (rxMsgStatus == TRUE)
            {
                /* Wait for interface to become free */
                DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
                retVal = DCANGetData(DCAN_APP_INST,
                                     gMsgObj[gRxAppCnt++],
                                     DCAN_APP_RX_IF_REG,
                                     &appDcanRxPrms,
                                     timeOut);
                if (gRxAppCnt == DCAN_APP_RX_BUF_SIZE)
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
                if (appDcanRxPrms.rxFrameType != expectedFrameType)
                {
                    retVal = STW_EFAIL;
                    frameTypeMissMatchErrCnt++;
                }
            }

            /* Check if sent Msg Identifier has been received */
            if (retVal == STW_SOK)
            {
                /* Check if sent  Msg Identifier has been received */
                if ((appDcanRxPrms.rxMsgIdentifier != expectedMsgIdentifier) ||
                    (appDcanRxPrms.rxIdType != expectedMsgIdType))
                {
                    retVal = STW_EFAIL;
                    msgIdentifierMissMatchErrCnt++;
                }
            }

            /* Check if sent data has been received */
            if (retVal == STW_SOK)
            {
                /* Check if sent data has been received */
                if (appDcanRxPrms.dataLength == expectedDataLength)
                {
                    dataLength = 0U;
                    while (dataLength < appDcanRxPrms.dataLength)
                    {
                        if (appDcanRxPrms.msgData[dataLength] !=
                            expectedDataBuffer[dataLength])
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
#if defined (__TI_ARM_V7M4__)
    disableIPU1Unicache();
#endif

    if (((msgLstErrCnt == 0) && (msgIdentifierMissMatchErrCnt == 0) &&
         (frameTypeMissMatchErrCnt == 0) && (dataMissMatchErrCnt == 0)) &&
         (retVal == STW_SOK))
    {
        UARTPuts("\r\nDCAN -- Board to Board Test (RX) Passed!! \r\n", -1);
    }
    else
    {
        UARTPuts("\r\nDCAN -- Board to Board Test (RX) Failed!! \r\n", -1);
    }

    return retVal;
}

static void DCANAppInitCfgParams(dcanCfgParams_t *pDcanCfgPrms)
{
    /*Intialize DCAN Config Params*/
    pDcanCfgPrms->autoRetransmitDisable = TRUE;
    pDcanCfgPrms->autoBusOnEnable       = FALSE;
    pDcanCfgPrms->testModeEnable        = FALSE;

    if (DCAN_APP_INTR_LINE_NUM == DCAN_INTR_LINE_NUM_0)
    {
        pDcanCfgPrms->intrLine0Enable = TRUE;
        pDcanCfgPrms->intrLine1Enable = FALSE;
    }
    else
    {
        pDcanCfgPrms->intrLine0Enable = FALSE;
        pDcanCfgPrms->intrLine1Enable = TRUE;
    }

    pDcanCfgPrms->errIntrEnable       = TRUE;
    pDcanCfgPrms->stsChangeIntrEnable = FALSE;
#if defined (SOC_TDA3XX)
    pDcanCfgPrms->eccModeEnable  = TRUE;
    pDcanCfgPrms->sbeEventEnable = TRUE;
    pDcanCfgPrms->parityEnable   = TRUE;
    pDcanCfgPrms->eccDiagModeEnable = FALSE;
#else
    pDcanCfgPrms->parityEnable = TRUE;
#endif
    pDcanCfgPrms->autoBusOnTimerVal = FALSE;
    pDcanCfgPrms->testMode          = DCAN_TEST_MODE_EXT_LPBACK;
    pDcanCfgPrms->if1DmaEnable      = FALSE;
    pDcanCfgPrms->if2DmaEnable      = FALSE;
    pDcanCfgPrms->if3DmaEnable      = FALSE;
    pDcanCfgPrms->ramAccessEnable   = FALSE;
}

static void DCANAppInitTxParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                dcanTxParams_t        *pDcanTxPrms,
                                uint32_t               dataLength,
                                uint8_t               *dataBuffer,
                                uint32_t               msgIdType,
                                uint32_t               msgIdentifier)
{
    /*Intialize DCAN tx Config Params*/
    pDcanTxCfgPrms->msgValid      = TRUE;
    pDcanTxCfgPrms->xIdFlag       = msgIdType;
    pDcanTxCfgPrms->direction     = DCAN_DIR_TX;
    pDcanTxCfgPrms->msgIdentifier = msgIdentifier;
    pDcanTxCfgPrms->intEnable     = TRUE;
    pDcanTxCfgPrms->remoteEnable  = FALSE;

    /*Intialize DCAN Tx transfer Params */
    pDcanTxPrms->dataLength = dataLength;
    pDcanTxPrms->msgData[0] = dataBuffer[0];
    pDcanTxPrms->msgData[1] = dataBuffer[1];
    pDcanTxPrms->msgData[2] = dataBuffer[2];
    pDcanTxPrms->msgData[3] = dataBuffer[3];
    pDcanTxPrms->msgData[4] = dataBuffer[4];
    pDcanTxPrms->msgData[5] = dataBuffer[5];
    pDcanTxPrms->msgData[6] = dataBuffer[6];
    pDcanTxPrms->msgData[7] = dataBuffer[7];
}

static void DCANAppInitRxParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                                uint32_t               msgIdType,
                                uint32_t               msgIdentifier)
{
    /*Intialize DCAN Rx Config Params*/
    pDcanRxCfgPrms->xIdFlagMask       = 0x1;
    pDcanRxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;
    pDcanRxCfgPrms->dirMask           = 0x1;

    pDcanRxCfgPrms->msgValid      = TRUE;
    pDcanRxCfgPrms->xIdFlag       = msgIdType;
    pDcanRxCfgPrms->direction     = DCAN_DIR_RX;
    pDcanRxCfgPrms->msgIdentifier = msgIdentifier;

    pDcanRxCfgPrms->uMaskUsed    = TRUE;
    pDcanRxCfgPrms->intEnable    = TRUE;
    pDcanRxCfgPrms->remoteEnable = FALSE;
}

static void DCANAppConfigIntr(char mainMenuOption)
{
    xbar_irq_t intrSource;

    if (DCAN_APP_INTR_LINE_NUM == DCAN_INTR_LINE_NUM_0)
    {
        intrSource = DCAN1_IRQ_INT0;
    }
    else
    {
        intrSource = DCAN1_IRQ_INT1;
    }
#if defined (__TI_ARM_V7M4__)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   XBAR_INST_IPU1_IRQ_28, intrSource);
#elif defined (__ARM_ARCH_7A__)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                   XBAR_INST_MPU_IRQ_77, intrSource);
#endif

    Intc_Init();
    Intc_IntEnable(0);

    if (DCAN_TX_TEST == mainMenuOption)
    {
        Intc_IntRegister(gIntrNum, (IntrFuncPtr) DCANAppTxIntIsr, (void *) 0);
    }
    if (DCAN_RX_TEST == mainMenuOption)
    {
        Intc_IntRegister(gIntrNum, (IntrFuncPtr) DCANAppRxIntIsr, (void *) 0);
    }

    Intc_IntPrioritySet(gIntrNum, 1, 0);

    Intc_SystemEnable(gIntrNum);
}

static void DCANAppTxIntIsr()
{
    uint32_t           intrStatus, errStatus;
    uint32_t           msgObj, pErrStatus;
#if defined (SOC_TDA3XX)
    dcanEccErrStatus_t eccErrFlag;
    uint32_t           eccErrStatus;
#endif

    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
    intrStatus = DCANGetIntrStatus(DCAN_APP_INST, DCAN_APP_INTR_LINE_NUM);

    if ((intrStatus == DCAN_ERR_STS_UPDATED) ||
        ((intrStatus >= 0x1) && (intrStatus <= 0x80)))
    {
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        errStatus = DCANGetErrStatus(DCAN_APP_INST);

        pErrStatus = ((errStatus & DCAN_ES_PER_MASK) >> DCAN_ES_PER_SHIFT);

#if defined (SOC_TDA3XX)
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        eccErrStatus = DCANGetEccErrStatus(DCAN_APP_INST);

        eccErrFlag.singleBitErr = (eccErrStatus & DCAN_ECC_CSR_SE_FLAG_MASK);
        eccErrFlag.doubleBitErr = ((eccErrStatus & DCAN_ECC_CSR_DE_FLAG_MASK)
                                   >> DCAN_ECC_CSR_DE_FLAG_SHIFT);

        if ((eccErrFlag.singleBitErr == 1) || (eccErrFlag.doubleBitErr == 1) ||
            (pErrStatus == 1))
        {
            gEccRParityErrStatus = 1;
        }
#else
        if (pErrStatus == 1)
        {
            gEccRParityErrStatus = 1;
        }

#endif
        if (gEccRParityErrStatus == 0)
        {
            if (errStatus != DCAN_ES_MASK_TX_OK)
            {
                gErrStatus = errStatus;
            }
            else
            {
                msgObj = DCANGetIntrStatus(DCAN_APP_INST,
                                           DCAN_APP_INTR_LINE_NUM);
                if ((DCANIsMsgObjIntrPending(DCAN_APP_INST, msgObj)) == TRUE)
                {
                    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
                    /* Clear the interrupts  of MSG_OBJ 1 for transmit */
                    DCANIntrClearStatus(DCAN_APP_INST, msgObj,
                                        DCAN_APP_TX_IF_REG);
                }
            }
        }
    }
}

static void DCANAppRxIntIsr()
{
    uint32_t           intrStatus, errStatus;
    uint32_t           msgObj, pErrStatus;
#if defined (SOC_TDA3XX)
    dcanEccErrStatus_t eccErrFlag;
    uint32_t           eccErrStatus;
#endif

    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
    intrStatus = DCANGetIntrStatus(DCAN_APP_INST, DCAN_APP_INTR_LINE_NUM);

    if ((intrStatus == DCAN_ERR_STS_UPDATED) ||
        ((intrStatus >= 0x1) && (intrStatus <= 0x80)))
    {
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
        errStatus = DCANGetErrStatus(DCAN_APP_INST);

        pErrStatus = ((errStatus & DCAN_ES_PER_MASK) >> DCAN_ES_PER_SHIFT);

#if defined (SOC_TDA3XX)
        DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_TX_IF_REG);
        eccErrStatus = DCANGetEccErrStatus(DCAN_APP_INST);

        eccErrFlag.singleBitErr = (eccErrStatus & DCAN_ECC_CSR_SE_FLAG_MASK);
        eccErrFlag.doubleBitErr = ((eccErrStatus & DCAN_ECC_CSR_DE_FLAG_MASK)
                                   >> DCAN_ECC_CSR_DE_FLAG_SHIFT);

        if ((eccErrFlag.singleBitErr == 1) || (eccErrFlag.doubleBitErr == 1) ||
            (pErrStatus == 1))
        {
            gEccRParityErrStatus = 1;
        }
#else
        if (pErrStatus == 1)
        {
            gEccRParityErrStatus = 1;
        }

#endif
        if (gEccRParityErrStatus == 0)
        {
            if (errStatus != DCAN_ES_MASK_RX_OK)
            {
                gErrStatus = errStatus;
            }
            else
            {
                msgObj = DCANGetIntrStatus(DCAN_APP_INST,
                                           DCAN_APP_INTR_LINE_NUM);
                gMsgObj[gIsrCnt++] = msgObj;
                if (gIsrCnt == DCAN_APP_RX_BUF_SIZE)
                    gIsrCnt = 0;
                if ((DCANIsMsgObjIntrPending(DCAN_APP_INST, msgObj)) == TRUE)
                {
                    DCANAppWaitForIfReg(DCAN_APP_INST, DCAN_APP_RX_IF_REG);
                    /* Clear the interrupts  of MSG_OBJ 2 for Receive */
                    DCANIntrClearStatus(DCAN_APP_INST, msgObj,
                                        DCAN_APP_RX_IF_REG);
                    gRxDoneFlag = 1;
                }
            }
        }
    }
}

static void DCANAppWaitForIfReg(uint32_t baseAddr, uint32_t ifRegNum)
{
    do
    {
        if (TRUE != DCANIsIfRegBusy(baseAddr, ifRegNum))
        {
            break;
        }
    }
    while (1);
}

static void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\r\n\r\n**** DCAN EVM LOOPBACK TEST ****", -1);
        UARTPuts("\r\nMenu:", -1);
        UARTPuts("\r\n1. DCAN Transmit test", -1);
        UARTPuts("\r\n2. DCAN Receive test", -1);
        UARTPuts("\r\nx. Exit", -1);
        UARTPuts("\r\nSelect DCAN EVM LOOPBACK TEST : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (DCAN_TX_TEST == *option || DCAN_RX_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\r\nEnter Valid option\r\n", -1);
        }
    }
}

static void mainSubMenu(char      mainMenuOption,
                        uint32_t *dataLength,
                        uint8_t  *dataBuffer,
                        uint32_t *numMsg,
                        uint32_t *msgIdType,
                        uint32_t *msgIdentifier)
{
    int32_t i;
    while (1)
    {
        if (mainMenuOption == DCAN_TX_TEST)
        {
            UARTPuts("\r\nEnter number of messages to be transmitted from:",
                     -1);
            *numMsg = UARTGetNum();

            UARTPuts("\r\nEnter the message ID Type to be transmitted- 0 for Stardard ID, 1 for Extended ID:",
                     -1);
            *msgIdType = UARTGetNum();

            UARTPuts("\r\nEnter the msgIdentifier to be transmitted as- [28:18] Valid Bits: Standard Identifier, [17:0] Valid Bits: Extended Identifier:",
                     -1);
            *msgIdentifier = UARTGetHexNum();

            UARTPuts("\r\nEnter the data length to be transmitted from 1 to 8:",
                     -1);
            *dataLength = UARTGetNum();

            UARTPuts("\r\nEnter the data sequence to be transmitted in Hex", -1);
            for (i = 0; i < *dataLength; i++)
            {
                UARTPuts("\r\ndataByte ", -1);
                UARTPutNum(i);
                UARTPuts("  :   ", -1);
                *dataBuffer = UARTGetHexNum();
                dataBuffer++;
            }
            break;
        }
        else if (mainMenuOption == DCAN_RX_TEST)
        {
            UARTPuts("\r\nEnter the expected number of messages to be received:",
                     -1);
            *numMsg = UARTGetNum();

            UARTPuts("\r\nEnter the expected message ID Type to be received- 0 for Stardard ID, 1 for Extended ID:",
                     -1);
            *msgIdType = UARTGetNum();

            UARTPuts("\r\nEnter the expected msgIdentifier to be received as- [28:18] Valid Bits: Standard Identifier, [17:0] Valid Bits: Extended Identifier:",
                     -1);
            *msgIdentifier = UARTGetHexNum();

            UARTPuts(
                "\r\nEnter the expected data length to be received from 1 to 8:",
                -1);
            *dataLength = UARTGetNum();
            UARTPuts(
                "\r\nEnter the expected data sequence to be received in Hex",
                -1);
            for (i = 0; i < *dataLength; i++)
            {
                UARTPuts("\r\ndataByte ", -1);
                UARTPutNum(i);
                UARTPuts("  :   ", -1);
                *dataBuffer = UARTGetHexNum();
                dataBuffer++;
            }
            break;
        }
        else
        {
            UARTPuts("\r\nEnter Valid option\r\n", -1);
        }
    }
}

static uint32_t read32KTimer(void)
{
    uint32_t timerVal = 0U;

    /* Read the counter value for 32 KHz SoC Synchronous Timer */
    timerVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    return timerVal;
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

static uint32_t dcanGetTheoriticalMax(uint32_t dataLength,
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

int32_t DCANCalcBitTimeParams(uint32_t             clkFreq,
                              uint32_t             bitRate,
                              uint32_t             refSamplePnt,
                              uint32_t             propDelay,
                              dcanBitTimeParams_t *pBitTimePrms)
{
    Double  tBitRef = 1000 * 1000 / bitRate;
    Double  newBaud = 0, newNProp = 0, newNSeg = 0, newSjw = 0, newP = 0;
    Double  nQRef, nProp, fCan, nQ, nSeg, baud, sp, p, newSp = 0;
    int32_t errStatus = STW_SOK;
    float   tQ;

    for (p = 1; p <= 1024; p++)
    {
        tQ    = ((p / clkFreq) * 1000.0);
        nQRef = tBitRef / tQ;

        if ((nQRef >= 8) && (nQRef <= 25))
        {
            nProp = ceil(propDelay / tQ);
            fCan  = clkFreq / p;
            nQ    = fCan / bitRate * 1000;
            nSeg  = ceil((nQ - nProp - 1) / 2);

            if ((nProp <= 8) && (nProp > 0) && (nSeg <= 8) && (nSeg > 0))
            {
                baud = fCan / (1 + nProp + 2 * nSeg) * 1000;

                sp = (1 + nProp + nSeg) / (1 + nProp + nSeg + nSeg) * 100;

                if ((abs(baud - bitRate)) < (abs(newBaud - bitRate)))
                {
                    newBaud  = baud;
                    newNProp = nProp;
                    newNSeg  = nSeg;
                    newSjw   = (nSeg < 4) ? nSeg : 4;
                    newP     = p - 1;
                    newSp    = sp;
                }
                else if ((abs(baud - bitRate)) == (abs(newBaud - bitRate)))
                {
                    if ((abs(sp - refSamplePnt)) < (abs(newSp - refSamplePnt)))
                    {
                        newBaud  = baud;
                        newNProp = nProp;
                        newNSeg  = nSeg;
                        newSjw   = (nSeg < 4) ? nSeg : 4;
                        newP     = p - 1;
                        newSp    = sp;
                    }
                }
            }
        }
    }
    if ((newBaud == 0) || (newBaud > 1000))
    {
        errStatus = STW_EFAIL;
        return errStatus;
    }

    pBitTimePrms->baudRatePrescaler    = (((uint32_t) newP) & 0x3F);
    pBitTimePrms->baudRatePrescalerExt =
        ((((uint32_t) newP) & 0x3C0) ? (((uint32_t) newP) & 0x3C0) >> 6 : 0);
    pBitTimePrms->syncJumpWidth = ((uint32_t) newSjw) - 1;

    /* propSeg = newNProp, phaseSeg = newNSeg, samplePoint = newSp
     * nominalBitTime = (1 + newNProp + 2 * newNSeg), nominalBitRate = newBaud
     * brpFreq  = clkFreq / (brp + 1), brpeFreq = clkFreq / (newP + 1)
     * brp      = pBitTimePrms->baudRatePrescaler;
     */

    pBitTimePrms->timeSegment1 = newNProp + newNSeg - 1;
    pBitTimePrms->timeSegment2 = newNSeg - 1;

    return errStatus;
}
