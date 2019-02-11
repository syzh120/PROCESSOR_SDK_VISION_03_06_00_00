/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     l3fw_writeOnly_main.c
 *
 *  \brief    This file contains L3FW test code for checking OCMC firewall.
 *
 *  \details  This application will produce violation by writing into write
 *            protected area.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_l3fw.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_l3fw.h>
#include <ti/drv/fw_l3l4/fwlibl3.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_L3FW_REGION_ID               (1U)
#define APP_L3FW_REGION_PERMISSOIN       (0xFFFFFFFFU)
#define APP_L3FW_PORT_NUM                (0x0U)

#if defined (SOC_TDA3XX)
/* Example will run on M4 on TDA3xx*/
    #define APP_HF_ERROR_INT                    (EXCEPTION_M4_HARD_FAULT_NUM_3)
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_IPU1)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)

#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)

#ifdef __TI_ARM_V7M4__
/* Example will run on M4 on TDA2ex */
    #define APP_HF_ERROR_INT                    (EXCEPTION_M4_HARD_FAULT_NUM_3)
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_IPU1)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_IPU1)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#else
/* Example will run on A15 on TDA2xx*/
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CPU_MPUSS)
    #define APP_XBAR_INST_ERROR                 (XBAR_INST_MPU_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_MPU)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#endif
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
l3fwRegionConfigParams_t configParams;
volatile uint32_t       isrFlag = 0U;
l3fwRegionErrorStatus_t errorLog;
int32_t gTestStatus = STW_SOK;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   None.
 *
 * \retval  status          Configuration status.
 */
static int32_t L3FWAppXBarConfig(void);

/**
 * \brief   This Interrupt Service Routine for L3FW error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L3FWAppErrorIntrISR(void *handle);

#if defined (__TI_ARM_V7M4__)
/**
 * \brief   This is custom hard fault handler.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L3FWAppHFISR(void *handle);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t                  configStatus, xBarStatus;
    uint32_t                 numOfMaster;
    l3fwMasterList_t         masterList[16];

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\r\nL3FW Test Application\r\n", -1);

    /* Initialize L3FW configuration parameters */
    configParams.regionId         = APP_L3FW_REGION_ID;
    configParams.targetBaseAddr   = APP_L3FW_REGION_TARGET_ADDR;
    configParams.regionStartAddr  = APP_L3FW_REGION_START_ADDR;
    configParams.regionEndAddr    = APP_L3FW_REGION_END_ADDR;
    configParams.regionPermission = APP_L3FW_REGION_PERMISSOIN;

    numOfMaster              = 1U;
    masterList[0].connId     = APP_CONN_ID;
    masterList[0].permission = L3FW_MRM_RW_PERMISSION_WRITE_ONLY;
    /* Configure XBar and interrupt */
    xBarStatus = L3FWAppXBarConfig();
    if (STW_SOK == xBarStatus)
    {
        /* Configure L3FW module */
        configStatus = FWLIBL3ConfigRegion(APP_L3FW_MODULE_INST,
                                           &configParams,
                                           numOfMaster,
                                           masterList);
        if (STW_SOK == configStatus)
        {
            UARTPuts("L3 Firewall configuration done.\r\n", -1);
            configStatus = FWLIBL3RegionEnable(APP_L3FW_MODULE_INST,
                                               configParams.regionId,
                                               APP_L3FW_PORT_NUM);
            if (STW_SOK == configStatus)
            {
                UARTPuts("L3 Firewall region is enabled.\r\n", -1);
                UARTPuts("Waiting for violation to happen.\r\n", -1);
                /* Generating violation here */
                /*HW_WR_REG32(0x40301050, 0xAAAAAAAAU);*/
                if(0xAAAAAAAAU != HW_RD_REG32(0x40301050))
                {
                }
                while (0U == isrFlag)
                {
                }
                /* Check for valid violation */
                if((0x1050 == errorLog.addrOffset)&&
                   (0x0U == errorLog.accessType) &&
                   ((APP_CONN_ID >> 2) == errorLog.connIdMSB4bit))
                {
                    gTestStatus = STW_SOK;
                }
                else
                {
                    gTestStatus = STW_EFAIL;
                }
            }
            else
            {
                UARTPuts("L3 Firewall region can not be enabled.\r\n", -1);
                gTestStatus = STW_EFAIL;
            }
        }
        else
        {
            UARTPuts("Error in L3 Firewall configuration done.\r\n", -1);
        }
    }

    if (gTestStatus == STW_SOK)
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
        UARTPuts("\r\nL3FW Test Pass\r\n", -1);
    }
    else
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTPuts("\r\nL3FW Test Fail\r\n", -1);
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t L3FWAppXBarConfig(void)
{
    int32_t status = STW_EFAIL;

    /* Configure Cross bar instance and interrupt */
    PlatformUnlockMMR();

    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       APP_XBAR_CPU, APP_XBAR_INST_ERROR,
                       APP_XBAR_INTR_SOURCE_ERROR))
    {
        /* Successfully configured CrossBar */
        status = STW_SOK;
    }
    else
    {
        UARTPuts("Error in configuring CrossBar.\r\n", -1);
        gTestStatus = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        Intc_Init();
    #if defined (__TI_ARM_V7M4__)
        /* Register custom HF handler */
        Intc_IntEnable(APP_HF_ERROR_INT);

        /* Register ISR */
        Intc_IntRegister(APP_HF_ERROR_INT,
                         (IntrFuncPtr) L3FWAppHFISR, 0);
        Intc_IntPrioritySet(APP_HF_ERROR_INT, 1, 0);
        Intc_SystemEnable(APP_HF_ERROR_INT);
    #endif

        /* Enable Error interrupt for L3FW */
        Intc_IntEnable(APP_L3FW_ERROR_INT);

        /* Register ISR */
        Intc_IntRegister(APP_L3FW_ERROR_INT,
                         (IntrFuncPtr) L3FWAppErrorIntrISR, 0);
        Intc_IntPrioritySet(APP_L3FW_ERROR_INT, 1, 0);
        Intc_SystemEnable(APP_L3FW_ERROR_INT);

    }
    return status;
}

#if defined (__TI_ARM_V7M4__)
static void L3FWAppHFISR(void *handle)
{
    uint32_t retVal;
    volatile uint32_t loop = 1U;

    UARTPuts("\r\nIn HF Handler...\r\n", -1);
    retVal = FWLIBL3GetErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM,
                                &errorLog);
    if (retVal == STW_SOK)
    {
        UARTPuts("Firewall error.\r\n", -1);
        UARTPuts("Firewall ISR will execute after HF.\r\n", -1);
    }
    else
    {
        UARTPuts("HF not due to firewall -- looping indefinitely.\r\n", -1);
        while (1U == loop)
        {
            ;
        }
    }
}
#endif

static void L3FWAppErrorIntrISR(void *handle)
{
    uint32_t retVal;

    UARTPuts("\r\nIn ISR...\r\n", -1);
    UARTPuts("OUT BAND ERROR interrupt generated.\r\n", -1);
    retVal = FWLIBL3GetErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM,
                                &errorLog);
    if (retVal == STW_SOK)
    {
        UARTPuts("Out Band error is generated by L3 Firewall.\r\n", -1);
        UARTPuts("===================================================\r\n", -1);
        UARTPuts("Violation Details:\r\n", -1);
        UARTprintf("L3 Firewall Instance : 0x%x\r\n", APP_L3FW_MODULE_INST);
        UARTprintf("MReqType(0:data access/1:\
instruction fetch) : %d\r\n", errorLog.mReqType);
        UARTprintf("Supervisor mode(0:User/1:Privilege) : %d\r\n",
                   errorLog.mReqSupervisor);
        UARTprintf("Mode(0:Functional/Debug) : %d\r\n", errorLog.mReqDebug);
        UARTprintf("Access Type(0:Read/1:Write) : %d\r\n", errorLog.accessType);
        UARTprintf("Master connId : 0x%x\r\n", errorLog.connIdMSB4bit);
        UARTprintf("Error Start Region : %d\r\n", errorLog.errorStartRegion);
        UARTprintf("Error End Region : %d\r\n", errorLog.errorEndRegion);
        UARTprintf("Block burst violation : %d\r\n", errorLog.blockBurstViolation);
        UARTprintf("Error address offset : 0x%x\r\n", errorLog.addrOffset);
        UARTPuts("===================================================\r\n", -1);
        FWLIBL3ClearErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM);
    }
    else
    {
        UARTPuts("No error generated by L3 Firewall.\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    /* Disable FW here to avoid core to get stuck in accessing the location
    *  for read.
    *  This issue will be faced when core which will get interrupt for violation
    *  is same as core which generates violation.
    *  This should not done in actual application.
    *  This is use here for demo purpose only.
    *  */
    FWLIBL3RegionDisable(APP_L3FW_MODULE_INST,
                         configParams.regionId,
                         APP_L3FW_PORT_NUM);
    isrFlag = 1U;
}
