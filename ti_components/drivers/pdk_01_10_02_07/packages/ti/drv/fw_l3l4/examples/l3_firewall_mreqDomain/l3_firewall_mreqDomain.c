/*
 *  Copyright (C) 2015-2018 Texas Instruments Incorporated
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
 *  \file     l3_firewall_mreqDomain_app.c
 *
 *  \brief    This file contains L3FW test code for checking OCMC firewall.
 *
 *  \details  This application have two binaries, one runs on A15 while other
 *            runs on EVE(both cores).
 *            The application running from A15 and configures OCMC FW to
 *            report any violations caused by invalid access done by EVE cores.
 *            The application running on EVE will produce violation by
 *            reading/writing into read/write protected area.
 *            To produce violation, user needs to run application
 *            (same application) from EVE1/EVE2 when prompted.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/drv/fw_l3l4/fwlibl3.h>
#include <l3_firewall_mreqDomain.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_EVE1_DOMAIN		(1U)
#define APP_EVE2_DOMAIN		(2U)

#define APP_NUMBER_OF_MASTERS_MAX         (2U)

#define APP_L3FW_REGION1_ID               (1U)
#define APP_L3FW_REGION2_ID               (2U)
/* Give permission for all modes plus give permission to domain 1 for EVE 1 */
#define APP_L3FW_REGION1_PERMISSION       (0xFFFFU |\
                                (uint32_t)L3FW_REGION_PERMISSION_DOMAIN1_FUNC |\
                                (uint32_t)L3FW_REGION_PERMISSION_DOMAIN1_DBG)
/* Give permission for all modes plus give permission to domain 2 for EVE 2 */
#define APP_L3FW_REGION2_PERMISSION       (0xFFFFU|\
                                (uint32_t)L3FW_REGION_PERMISSION_DOMAIN2_FUNC |\
                                (uint32_t)L3FW_REGION_PERMISSION_DOMAIN2_DBG)
#define APP_L3FW_PORT_NUM                 (0x0U)

/* Example will run on A15 on TDA2xx*/
#define APP_L3FW_ERROR_INT                  (44U)
#define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_MPU)
#define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_MPU_IRQ_44)
#define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
#define APP_CONN_ID_MASTER0                 (SOC_CONNID_EVE1_MMU0)
#define APP_CONN_ID_MASTER1                 (SOC_CONNID_EVE2_MMU0)
#define APP_L3FW_MODULE_INST                (L3FW_OCMC_RAM2_INST)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t gTestPass = 0;
volatile uint32_t       gIsrFlag = 0U;
l3fwRegionErrorStatus_t gErrorLog;
int32_t gTestStatus = STW_SOK;
volatile uint32_t gReadViolations, gWriteViolations;
uint32_t gUartBaseAddr = SOC_UART1_BASE;

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

int main(void) {

    int32_t results = STW_SOK;
    int32_t                  configStatus = STW_SOK;
	uint32_t                 xBarStatus, numOfMaster;
    l3fwMasterList_t         masterList[APP_NUMBER_OF_MASTERS_MAX];
	l3fwRegionConfigParams_t configParams;

    /* UART Setup */
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* set the uart parameters */
    UARTConfigInit(gUartBaseAddr,
                   BAUD_RATE_115200,
                   UART_WORD_LENGTH_8,
                   UART_STOP_BIT_1,
                   UART_NO_PARITY,
                   UART_16x_MODE);

    UARTConfigPuts(gUartBaseAddr,
                   "\r\nL3FW MreqDomain Config Test Application...\r\n", -1);
    UARTConfigPuts(gUartBaseAddr,
               "\r\nMreqDomain Values before MreqDomain configuration:", -1);
    UARTConfigPuts(gUartBaseAddr,"\r\nEVE 1 :", -1);
    UARTConfigPutHexNum(gUartBaseAddr,
            FWLIBL3MReqDomainReadDomainId(CSL_MREQDOMAIN_INITIATOR_EVE1_TC0));
    UARTConfigPuts(gUartBaseAddr,"\r\nEVE 2 :", -1);
    UARTConfigPutHexNum(gUartBaseAddr,
            FWLIBL3MReqDomainReadDomainId(CSL_MREQDOMAIN_INITIATOR_EVE2_TC0));


    results += FWLIBL3MReqDomainWriteDomainId(CSL_MREQDOMAIN_INITIATOR_EVE1_TC0,
                                              APP_EVE1_DOMAIN);
    if (results == STW_SOK)
    {
    	results =
            FWLIBL3MReqDomainWriteDomainId(CSL_MREQDOMAIN_INITIATOR_EVE2_TC0,
                                           APP_EVE2_DOMAIN);
    }
    if (results == STW_SOK)
    {
        UARTConfigPuts(gUartBaseAddr,
                   "\r\nMreqDomain Values after MreqDomain configuration:", -1);
        UARTConfigPuts(gUartBaseAddr,"\r\nEVE 1 :", -1);
        UARTConfigPutHexNum(gUartBaseAddr,
            FWLIBL3MReqDomainReadDomainId(CSL_MREQDOMAIN_INITIATOR_EVE1_TC0));
        UARTConfigPuts(gUartBaseAddr,"\r\nEVE 2 :", -1);
        UARTConfigPutHexNum(gUartBaseAddr,
            FWLIBL3MReqDomainReadDomainId(CSL_MREQDOMAIN_INITIATOR_EVE2_TC0));
    }
    else
    {
        UARTConfigPuts(gUartBaseAddr,
                   "\r\nMreqDomain Configuration failed:", -1);
        gTestStatus += STW_EFAIL;
    }
    gReadViolations = 0;
    gWriteViolations = 0;
    gIsrFlag = 0U;
    /* Configure XBar and interrupt */
	xBarStatus = L3FWAppXBarConfig();
	if (SUCCESS == xBarStatus)
	{
		/* Initialize L3FW configuration parameters */
		configParams.regionId         = APP_L3FW_REGION1_ID;
		configParams.targetBaseAddr   = APP_L3FW_REGION_TARGET_ADDR1;
		configParams.regionStartAddr  = APP_L3FW_REGION_START_ADDR1;
		configParams.regionEndAddr    = APP_L3FW_REGION_END_ADDR1;
		configParams.regionPermission = APP_L3FW_REGION1_PERMISSION;

		numOfMaster              = 1U;
		masterList[0].connId     = APP_CONN_ID_MASTER0;
		masterList[0].permission = L3FW_MRM_RW_PERMISSION_READ_WRITE;
		/* Configure L3FW module */
		configStatus += FWLIBL3ConfigRegion(APP_L3FW_MODULE_INST,
										   &configParams,
										   numOfMaster,
										   masterList);
		if (STW_SOK == configStatus)
		{
			configStatus += FWLIBL3RegionEnable(APP_L3FW_MODULE_INST,
											   APP_L3FW_REGION1_ID,
											   APP_L3FW_PORT_NUM);
            UARTConfigPuts(gUartBaseAddr,"\r\nL3 Firewall configuration done.\r\n", -1);
		}
		if (STW_SOK == configStatus)
		{
            UARTConfigPuts(gUartBaseAddr,"\r\nL3 Firewall region is enabled.\r\n", -1);
			configParams.regionId         = APP_L3FW_REGION2_ID;
			configParams.targetBaseAddr   = APP_L3FW_REGION_TARGET_ADDR2;
			configParams.regionStartAddr  = APP_L3FW_REGION_START_ADDR2;
			configParams.regionEndAddr    = APP_L3FW_REGION_END_ADDR2;
			configParams.regionPermission = APP_L3FW_REGION2_PERMISSION;

			numOfMaster              = 1U;
			masterList[0].connId     = APP_CONN_ID_MASTER1;
			masterList[0].permission = L3FW_MRM_RW_PERMISSION_READ_WRITE;
			/* Configure L3FW module */
			configStatus += FWLIBL3ConfigRegion(APP_L3FW_MODULE_INST,
											   &configParams,
											   numOfMaster,
											   masterList);
		}
		if (STW_SOK == configStatus)
		{
			configStatus += FWLIBL3RegionEnable(APP_L3FW_MODULE_INST,
											   APP_L3FW_REGION2_ID,
											   APP_L3FW_PORT_NUM);
            UARTConfigPuts(gUartBaseAddr,
                            "L3 Firewall configuration done.\r\n", -1);
		}
		if (STW_SOK == configStatus)
		{
            UARTConfigPuts(gUartBaseAddr,
                            "L3 Firewall region is enabled.\r\n", -1);
			/* Should hit violation 4 times */
            UARTConfigPuts(gUartBaseAddr,
                            "Waiting for  2 violations to happen.\r\n", -1);
            UARTConfigPuts(gUartBaseAddr,
                            "Enable EVE1/EVE2 cores from Gel files(Run this):",
                            -1);
            UARTConfigPuts(gUartBaseAddr,
            "(CCS->Scripts->TDA2Px MULTICORE Initialization->TDA2Px_MULTICORE_EnableAllCores)\r\n", -1);
			/* First two violations are from EVE Core 1 */
            UARTConfigPuts(gUartBaseAddr,
                            "Load and run binary on EVE Core 1...\r\n", -1);
            while ((gIsrFlag != 1U) && (gReadViolations != 1U))
			{
				/* Generating violation here */
			}
            UARTConfigPuts(gUartBaseAddr,
                    "Read violation is generated on EVE Core 1.\r\n", -1);
            UARTConfigPuts(gUartBaseAddr,
                            "Load and run binary on EVE Core 2...\r\n", -1);
            /* First two violations are from EVE Core 2 */
            while ((gIsrFlag != 2U) && (gWriteViolations != 1U))
			{
				/* Generating violation here */
			}
            UARTConfigPuts(gUartBaseAddr,
                    "Write violation is generated on EVE Core 2.\r\n", -1);
		}
		if (STW_SOK == configStatus)
		{
			FWLIBL3RegionDisable(APP_L3FW_MODULE_INST,
								 APP_L3FW_REGION2_ID,
								 APP_L3FW_PORT_NUM);
			FWLIBL3RegionDisable(APP_L3FW_MODULE_INST,
								 APP_L3FW_REGION1_ID,
								 APP_L3FW_PORT_NUM);
		}
		else
		{
            UARTConfigPuts(gUartBaseAddr,"L3 Firewall region can not be disabled.\r\n", -1);
			gTestStatus += STW_EFAIL;
		}
	}
	else
	{
		gTestStatus += STW_EFAIL;
	}

    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(gUartBaseAddr,
                "\r\nL3FW MreqDomain Config Test Application Pass\r\n", -1);
    }
    else
    {
        UARTConfigPuts(gUartBaseAddr,
                "\r\nL3FW MreqDomain Config Test Application Fail\r\n", -1);
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
    int32_t retVal = STW_SOK;

    UARTConfigPuts(gUartBaseAddr,"\r\nIn ISR...\r\n", -1);
    UARTConfigPuts(gUartBaseAddr,"OUT BAND ERROR interrupt generated.\r\n", -1);
    retVal += FWLIBL3GetErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM,
                                &gErrorLog);
    if (retVal == STW_SOK)
    {
    	if (gErrorLog.accessType == 0)
    		gReadViolations = gReadViolations + 1;
    	else
    		gWriteViolations = gWriteViolations + 1;
        FWLIBL3ClearErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM);
    }
    else
    {
        gTestStatus += STW_EFAIL;
    }
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(gUartBaseAddr,"Out Band error is generated by L3 Firewall.\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"===================================================\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Violation Details:\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"L3 Firewall Instance : ", -1);
        UARTConfigPutHexNum(gUartBaseAddr, APP_L3FW_MODULE_INST);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"MReqType(0:data access/1:\
instruction fetch) : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.mReqType);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Supervisor mode(0:User/1:Privilege) : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.mReqSupervisor);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Mode(0:Functional/Debug) : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.mReqDebug);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Access Type(0:Read/1:Write) : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.accessType);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Master connId : ", -1);
        UARTConfigPutHexNum(gUartBaseAddr, gErrorLog.connIdMSB4bit);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Error Start Region : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.errorStartRegion);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Error End Region : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.errorEndRegion);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Block burst violation : ", -1);
        UARTConfigPutNum(gUartBaseAddr, gErrorLog.blockBurstViolation);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"Error address offset : ", -1);
        UARTConfigPutHexNum(gUartBaseAddr, gErrorLog.addrOffset);
        UARTConfigPuts(gUartBaseAddr, "\r\n", -1);
        UARTConfigPuts(gUartBaseAddr,"===================================================\r\n", -1);
        FWLIBL3ClearErrorLog(APP_L3FW_MODULE_INST, APP_L3FW_PORT_NUM);
    }
    else
    {
        UARTConfigPuts(gUartBaseAddr,"No error generated by L3 Firewall.\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    gIsrFlag = gIsrFlag + 1U;
}
