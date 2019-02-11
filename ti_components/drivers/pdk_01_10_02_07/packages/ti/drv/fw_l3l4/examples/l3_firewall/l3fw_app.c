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
 *  \file     l3fw_app.c
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
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/fw_l3l4/fwlibl3.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_L3FW_REGION_ID               (1U)
#define APP_L3FW_REGION_PERMISSOIN       (0xFFFFFFFFU)
#define APP_L3FW_PORT_NUM                (0x0U)

#if defined (SOC_TDA3XX) || defined (SOC_DRA78X)
/* Example will run on M4 on TDA3xx*/
    #define APP_L3FW_ERROR_INT                  (EXCEPTION_M4_HARD_FAULT_NUM_3)
    /* Register the L3FW error handler ISR to HF interrupt number, as hard fault
     * is generated when running from M4. */
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_IPU1)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)

#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA75X)

#ifdef __TI_ARM_V7M4__
/* Example will run on M4 on TDA2ex */
    #define APP_L3FW_ERROR_INT                  (EXCEPTION_M4_HARD_FAULT_NUM_3)
    /* Register the L3FW error handler ISR to HF interrupt number, as hard fault
     * is generated when running from M4. */
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (L3FW_IPU1_INST)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#else
/* Example will run on A15 on TDA2xx*/
    #define APP_L3FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_MPU)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_MPU_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
    #define APP_CONN_ID                         (SOC_CONNID_MPU)
    #define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM1_INST)
    #define APP_L3FW_REGION_TARGET_ADDR         (SOC_OCMC_RAM1_BASE)
    #define APP_L3FW_REGION_START_ADDR          (SOC_OCMC_RAM1_BASE + 0x1000U)
    #define APP_L3FW_REGION_END_ADDR            (SOC_OCMC_RAM1_BASE + 0x2000U)
#endif
#endif

/**
 * \brief  This macro defines the Boolean that is used for True.
 */
#define SUCCESS                                        ((uint32_t) 1U)
/**
 * \brief  This macro defines the Boolean that is used for False.
 */
#define FAIL                                           ((uint32_t) 0U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t       isrFlag = 0U;
l3fwRegionErrorStatus_t errorLog;
int32_t gTestStatus = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA75X)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78X)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

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
static uint32_t L3FWAppXBarConfig(void);

/**
 * \brief   This Interrupt Service Routine for L3FW error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L3FWAppErrorIntrISR(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    int32_t                  configStatus;
    uint32_t                 xBarStatus, numOfMaster;
    l3fwMasterList_t         masterList[16];
    l3fwRegionConfigParams_t configParams;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA75X)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78X)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif

    UARTConfigPuts(uartBaseAddr,"\r\nL3FW Test Application\r\n", -1);

    /* Initialize L3FW configuration parameters */
    configParams.regionId         = APP_L3FW_REGION_ID;
    configParams.targetBaseAddr   = APP_L3FW_REGION_TARGET_ADDR;
    configParams.regionStartAddr  = APP_L3FW_REGION_START_ADDR;
    configParams.regionEndAddr    = APP_L3FW_REGION_END_ADDR;
    configParams.regionPermission = APP_L3FW_REGION_PERMISSOIN;

    numOfMaster              = 1U;
    masterList[0].connId     = APP_CONN_ID;
    masterList[0].permission = L3FW_MRM_RW_PERMISSION_READ_ONLY;
    /* Configure XBar and interrupt */
    xBarStatus = L3FWAppXBarConfig();
    if (SUCCESS == xBarStatus)
    {
        /* Configure L3FW module */
        configStatus = FWLIBL3ConfigRegion(APP_L3FW_MODULE_INST,
                                           &configParams,
                                           numOfMaster,
                                           masterList);
        if (STW_SOK == configStatus)
        {
            UARTConfigPuts(uartBaseAddr,"L3 Firewall configuration done.\r\n", -1);
            configStatus = FWLIBL3RegionEnable(APP_L3FW_MODULE_INST,
                                               configParams.regionId,
                                               APP_L3FW_PORT_NUM);
            if (STW_SOK == configStatus)
            {
                UARTConfigPuts(uartBaseAddr,"L3 Firewall region is enabled.\r\n", -1);
                UARTConfigPuts(uartBaseAddr,"Waiting for violation to happen.\r\n", -1);
                while (0U == isrFlag)
                {
                    /* Generating violation here */
                    HW_WR_REG32(0x40301050, 0xAAAAAAAAU);
                }
                FWLIBL3RegionDisable(APP_L3FW_MODULE_INST,
                                     configParams.regionId,
                                     APP_L3FW_PORT_NUM);
            }
            else
            {
                UARTConfigPuts(uartBaseAddr,"L3 Firewall region can not be enabled.\r\n", -1);
                gTestStatus = STW_EFAIL;
            }
        }
        else
        {
            UARTConfigPuts(uartBaseAddr,"Error in L3 Firewall configuration done.\r\n", -1);
        }
    }

    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nL3FW Test Pass\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\nL3FW Test Fail\r\n", -1);
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static uint32_t L3FWAppXBarConfig(void)
{
    uint32_t status = SUCCESS;

    /* Configure Cross bar instance and interrupt */
    CSL_xbarIrqConfigure(APP_XBAR_CPU,APP_XBAR_INST_ERROR,APP_XBAR_INTR_SOURCE_ERROR);

    if (SUCCESS == status)
    {
        /* Enable Error interrupt for L3FW */
        Intc_Init();
        Intc_IntEnable(APP_L3FW_ERROR_INT);

        /* Register ISR */
        Intc_IntRegister(APP_L3FW_ERROR_INT,
                         (IntrFuncPtr) L3FWAppErrorIntrISR, 0);
        Intc_IntPrioritySet(APP_L3FW_ERROR_INT, 1, 0);
        Intc_SystemEnable(APP_L3FW_ERROR_INT);
    }
    return status;
}

static void L3FWAppErrorIntrISR(void *handle)
{
    uint32_t retVal;

    UARTConfigPuts(uartBaseAddr,"\r\nIn ISR...\r\n", -1);
    UARTConfigPuts(uartBaseAddr,"OUT BAND ERROR interrupt generated.\r\n", -1);
    retVal = FWLIBL3GetErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM,
                                &errorLog);
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"Out Band error is generated by L3 Firewall.\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"===================================================\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Violation Details:\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"L3 Firewall Instance : ", -1);
        UARTConfigPutHexNum(uartBaseAddr, APP_L3FW_MODULE_INST);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"MReqType(0:data access/1:\
instruction fetch) : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.mReqType);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Supervisor mode(0:User/1:Privilege) : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.mReqSupervisor);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Mode(0:Functional/Debug) : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.mReqDebug);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Access Type(0:Read/1:Write) : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.accessType);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Master connId : ", -1);
        UARTConfigPutHexNum(uartBaseAddr, errorLog.connIdMSB4bit);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Error Start Region : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.errorStartRegion);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Error End Region : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.errorEndRegion);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Block burst violation : ", -1);
        UARTConfigPutNum(uartBaseAddr, errorLog.blockBurstViolation);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"Error address offset : ", -1);
        UARTConfigPutHexNum(uartBaseAddr, errorLog.addrOffset);
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPuts(uartBaseAddr,"===================================================\r\n", -1);
        FWLIBL3ClearErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"No error generated by L3 Firewall.\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    isrFlag = 1U;
}

