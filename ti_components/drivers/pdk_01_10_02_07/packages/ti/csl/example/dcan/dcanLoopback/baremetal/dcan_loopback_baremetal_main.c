/*
 *  Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     dcan_loopback_baremetal_main.c
 *
 *  \brief    This file contains the bare-metal specific implementation for
 *			  executing the DCAN test
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/example/dcan/dcanLoopback/dcan_loopback_app.h>

/* ========================================================================== */
/*                         Global Variables                                   */
/* ========================================================================== */

extern char gMainMenuOption;
volatile uint32_t testDone = 1;
uint32_t gDcanAppInstance;
dcanTxParams_t appDcanTxPrms;

#if defined (SOC_TDA3XX)
extern dcanEccErrStatus_t     gErrClr;
extern uint32_t               gMsgObjSBE;
extern uint32_t               gMsgObjDBE;
#endif
#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
extern uint32_t               gMsgObj;
extern uint32_t               gWordNum;
#endif

#if defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA3XX)
/**
 * \brief   DCAN Parity Error Interrupt Service Routine. This function checks
 *          and handles parity error.
 *
 */
static void DCANAppParityIsr();
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern void padConfig_prcmEnable(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t dcanReceiveData(uint32_t msgLstErrCnt, uint32_t dataMissMatchErrCnt)
{
    dcanRxParams_t appDcanRxPrms;
    uint32_t dataLength = 0U, timeOut = 100U;
    int32_t retVal = STW_SOK;

    /* Clear RX structure */
    memset(&appDcanRxPrms, 0, sizeof (appDcanRxPrms));

    /* Wait for interface to become free */
    DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
    retVal = DCANGetData(gDcanAppInstance,
                         DCAN_RX_MSG_OBJ,
                         DCAN_APP_RX_IF_REG,
                         &appDcanRxPrms,
                         timeOut);

    if (retVal == STW_SOK)
    {
        /* Check if sent data is lost or not */
        if (appDcanRxPrms.msgLostFlag == TRUE)
        {
            msgLstErrCnt++;
        }

        /* Check if sent data has been received */
        if (appDcanRxPrms.dataLength == appDcanTxPrms.dataLength)
        {
                while (dataLength < appDcanRxPrms.dataLength)
                {
                    if (appDcanRxPrms.msgData[dataLength] !=
                        appDcanTxPrms.msgData[dataLength])
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
        }
    }
    return retVal;
}

/*
 * ======== DCAN Loopback Test ========
 */

int32_t dcanLoopbackTest(void)
{
    int32_t               retVal    = STW_SOK;
    int32_t               errStatus = STW_SOK;
    dcanCfgParams_t       appDcanCfgPrms;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    uint32_t              timeOut = 100U;
    uint32_t              msgLstErrCnt        = 0U;
    uint32_t              dataMissMatchErrCnt = 0U;

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        PRINT_MSG("\nDCAN External Loopback Test App: DCAN1 MSG OBJ 1 (TX) to DCAN1 MSG OBJ 2 (RX)\n");

#if defined (__TI_ARM_V7M4__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * IPU1_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));
#elif defined (__ARM_ARCH_7A__)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * MPU_C0
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_MPU_C0 << 4) | 0x1));
#elif defined (_TMS320C6X)
        /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as
         * DSP1
         * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach
         * the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1,
                    ((DRM_SUSPEND_SRC_C66_C0 << 4) | 0x1));
#endif
    }
    else
    {
        PRINT_MSG("\nDCAN Internal Loopback Test App: DCAN2 MSG OBJ 1 (TX) to DCAN2 MSG OBJ 2 (RX)\n");
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
#elif defined (_TMS320C6X)
        /* DRM_SUSPEND_CTRL_DCAN2 - SUSPEND_SEL(Suspend source selection) as
         * DSP1 & SENS_CTRL(Sensitivity control) as 1 means suspend signal
         * must reach the peripheral-IP  */
        HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN2,
                    ((DRM_SUSPEND_SRC_C66_C0 << 4) | 0x1));
#endif
    }

	DCANAppInitParams(&appDcanCfgPrms,
                    &appDcanTxCfgPrms,
                    &appDcanRxCfgPrms,
                    &appDcanTxPrms,
                    gMainMenuOption);

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        DCAN1Prcm_clck_ram();
    }
    else
    {
        DCAN2Prcm_clck_ram();
    }

    /* Reset the DCAN IP */
    retVal = DCANReset(gDcanAppInstance, timeOut);
    if (retVal == STW_SOK)
    {
        /* Set the desired bit rate based on input clock */
        DCANSetMode(gDcanAppInstance, DCAN_MODE_INIT);
        errStatus = DCANCalculateBitTimeParams(DCAN_APP_INPUT_CLK,
                                                DCAN_APP_BIT_RATE,
                                                &appDcanBitTimePrms);
        if (errStatus != DCAN_BIT_RATE_ERR_NONE)
        {
            return errStatus;
        }
        DCANSetBitTime(gDcanAppInstance, &appDcanBitTimePrms);
        DCANSetMode(gDcanAppInstance, DCAN_MODE_NORMAL);

        /* Configure DCAN controller */
        DCANConfig(gDcanAppInstance, &appDcanCfgPrms);
    }
    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
		retVal = DCANConfigMsgObj(gDcanAppInstance,
                                DCAN_RX_MSG_OBJ,
                                DCAN_APP_RX_IF_REG,
                                &appDcanRxCfgPrms);

        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_RX_IF_REG);
    }
    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
		retVal = DCANConfigMsgObj(gDcanAppInstance,
									DCAN_TX_MSG_OBJ,
									DCAN_APP_TX_IF_REG,
									&appDcanTxCfgPrms);
        /* Wait for config to be copied to internal message RAM */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
    }
    if (retVal == STW_SOK)
    {
        /* Wait for interface to become free */
        DCANAppWaitForIfReg(gDcanAppInstance, DCAN_APP_TX_IF_REG);
		retVal = DCANTransmitData(gDcanAppInstance,
									DCAN_TX_MSG_OBJ,
									DCAN_APP_TX_IF_REG,
									&appDcanTxPrms,
									timeOut);
    }/* End Of Transmission */

	if (retVal == STW_SOK)
    {
        /* Wait for transmit interrupt */
        while (DCANIsTxMsgPending(gDcanAppInstance,
                                            DCAN_TX_MSG_OBJ)==TRUE) ;

        if (retVal == STW_SOK)
        {
            /* Wait for receive interrupt */
            while (DCANHasRxMsgArrived(gDcanAppInstance,
                                       DCAN_RX_MSG_OBJ)==FALSE) ;
        }
        /* Get the DCAN Rx data */
        retVal = dcanReceiveData(msgLstErrCnt, dataMissMatchErrCnt);
    }
	if (((msgLstErrCnt == 0) &&
         (dataMissMatchErrCnt == 0)) && (retVal == STW_SOK))
    {
        if (gMainMenuOption == DCAN_EXT_LOOPBACK_TEST)
        {
            PRINT_MSG("\nDCAN -- External Loopback Testmode test Passed!! \n");
        }
        else
        {
            PRINT_MSG("\nDCAN -- Internal Loopback Testmode test Passed!! \n");
        }
    }
    else
    {
        if (gMainMenuOption == DCAN_EXT_LOOPBACK_TEST)
        {
            PRINT_MSG("\nDCAN -- External Loopback Testmode test Failed!! \n");
        }
        else
        {
            PRINT_MSG("\nDCAN -- Internal Loopback Testmode test Failed!! \n");
        }
    }
    return retVal;
}

/*
 *  ======== main ========
 */
int main(void)
{
    int32_t retVal   = STW_SOK;

    retVal = execTest();

    while (testDone);
    return retVal;
}

#if defined (SOC_TDA3XX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/*
 *  ======== DCAN Parity Error interrupt Configuration ========
 */
void DCANAppConfigParityIntr(void)
{
    CSL_XbarIrq intrSource;

    if (gDcanAppInstance == DCAN1_APP_INST)
    {
        intrSource = CSL_XBAR_DCAN1_IRQ_PARITY;
    }
    else
    {
        intrSource = CSL_XBAR_DCAN2_IRQ_PARITY;
    }
    /* XBar configuration */
    CSL_xbarIrqConfigure(XBAR_CPU,XBAR_INST,intrSource);

    Intc_Init();
    Intc_IntEnable(APP_DCAN_INT);
    Intc_IntRegister(APP_DCAN_INT, (IntrFuncPtr) DCANAppParityIsr, (void *) 0);
    Intc_IntPrioritySet(APP_DCAN_INT, 1, 0);
    Intc_SystemEnable(APP_DCAN_INT);
}

/*
 *  ======== DCAN Parity Error Interrupt Service Routine ========
 */
static void DCANAppParityIsr()
{
    uint32_t errStatus;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    errStatus = DCANGetEccErrStatus(gDcanAppInstance);

    gErrClr.singleBitErr = (errStatus & DCAN_ECC_CSR_SE_FLAG_MASK);
    gErrClr.doubleBitErr = ((errStatus & DCAN_ECC_CSR_DE_FLAG_MASK) >>
                            DCAN_ECC_CSR_DE_FLAG_SHIFT);

    DCANClrEccErrStatus(gDcanAppInstance, &gErrClr);

    if (gErrClr.singleBitErr)
    {
        gMsgObjSBE = DCANGetMsgObjBitErrDetected(gDcanAppInstance);
    }

    if (gErrClr.doubleBitErr)
    {
        errStatus  = DCANGetParityErrStatus(gDcanAppInstance);
        gMsgObjDBE = (errStatus & DCAN_PERR_MESSAGE_NUMBER_MASK);
    }
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    errStatus = DCANGetParityErrStatus(gDcanAppInstance);
    gMsgObj   = (errStatus & DCAN_PERR_MESSAGE_NUMBER_MASK);
    gWordNum  = ((errStatus & DCAN_PERR_WORD_NUMBER_MASK) >>
                 DCAN_PERR_WORD_NUMBER_SHIFT);
#endif

    DCANClrParityIntrStatus(gDcanAppInstance);
}
#endif
/********************************* End of file ******************************/
