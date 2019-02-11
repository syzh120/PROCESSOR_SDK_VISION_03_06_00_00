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
 * \file main.c
 *
 * \brief   Voltage Manager API implementation test.
 *
 *          The Voltage API supports the following features. The test would be
 *          targeted towards verifying these.
 *          - Operating Performance Point (OPP)
 *          - AVS Class-0
 *          - Adaptive Body Bias (ABB)
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <stdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8731.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8731_lp3907.h>
#include <ti/csl/csl_i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define PM_TEST_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define PM_TEST_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define PM_TEST_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define PM_TEST_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define PM_TEST_UTILS_I2C_READ               (2U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Helper function to check the start up voltage of the different
 *        voltage domain. Used to check the API PMHALVMGetCurrentOpp &
 *        PMHALVMGetCurrentVoltage.
 *
 * \param void
 *
 * \retval status Returns the success or failure of the helper function.
 *                PM_SUCCESS if all the voltages at boot up are correct.
 *                PM_FAIL/PM_BADARGS/PM_TIMEOUT on error conditions of the API.
 */
static pmErrCode_t checkStartupVoltages(void);

/**
 * \brief Helper function to switch OPP for the different voltage domains.
 *
 * \param void
 *
 * \retval status Returns the success or failure of the helper function.
 *                PM_SUCCESS if all the voltages at boot up are correct.
 *                PM_FAIL/PM_BADARGS/PM_TIMEOUT on error conditions of the API.
 */
static pmErrCode_t checkSwitchOPP(void);

/**
 * \brief Print the current voltage setting of the given VD
 *
 * \param vd   Voltage domain ID
 *
 * \retval     status Returns the success or failure of the helper function.
 *                PM_SUCCESS if all the voltages at boot up are correct.
 *                PM_FAIL/PM_BADARGS/PM_TIMEOUT on error conditions of the API.
 */
static pmErrCode_t printNoMVoltage(pmhalPrcmVdId_t vd);

/**
 * \brief Swith the OPP voltage and handle the return value.
 *
 * \param vd   Voltage domain ID
 * \param opp  OPP ID
 *
 * \retval     status Returns the success or failure of the helper function.
 *                PM_SUCCESS if all the voltages at boot up are correct.
 *                PM_FAIL/PM_BADARGS/PM_TIMEOUT on error conditions of the API.
 */
static pmErrCode_t switchOPP(pmhalPrcmVdId_t vd, pmhalVmOppId_t opp);

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t PmTestUtilsI2cInit(void);

/**
 * \brief   This function reads a byte from the PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be read.
 * \param   regValue    Pointer to the location where the read value will be
 *                      placed.
 * \param   numRegs     Number of registers to be read.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                      const uint8_t *regAddr,
                                      uint8_t *regValue,
                                      uint32_t numRegs);

/**
 * \brief   This function writes a byte of data to the register of PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be written.
 * \param   regValue    Pointer to the location where the write value will be
 *                      placed.
 * \param   numRegs     Number of registers to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs);
#ifdef __cplusplus
}
#endif
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
                                   uint8_t slaveAddr, const uint8_t data[],
                                   uint8_t count);

/**
 * \brief  Read one byte from the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   value       Data to be read is returned.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of PM_TEST_UTILS_I2C_WRITE or
 *                  PM_TEST_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static char *oppStr[PMHAL_VM_OPP_MAX] = {"LOW", "NOM", "OD", "HIGH"};
static char *vdStr[PMHAL_PRCM_VD_COUNT] = {"CORE", "DSPEVE"};

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalI2cCommOperations_t pmicI2cfunc = {
    &PmTestUtilsI2cInit,
    &PmTestUtilsI2cReadByte,
    &PmTestUtilsI2cWriteByte,
    NULL,
    NULL
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void main(void)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalPmicOperations_t *pmicOps;
    uint32_t    i = 0U;
    uint32_t    choiceCorrect;
    int32_t     pmicType = 0;
    uint32_t    voltage;

    /*Unlock the Control registers */
    HAL_CTRL_UnlockMMR();
    /* Enable UART3 module */
    status = (pmErrCode_t) PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                              PMHAL_PRCM_MODULE_MODE_ENABLED,
                                              PM_TIMEOUT_INFINITE);
    PlatformUART3SetPinMux();
    UARTStdioInit();

    Intc_Init();
    Intc_IntEnable(0U);

    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALI2CCommRegister(&pmicI2cfunc);
    choiceCorrect = 0U;
    do
    {
        UARTPuts("\n Select the PMIC to test: \n", -1);
        UARTPuts("1. TPS65917\n", -1);
        UARTPuts("2. LP8731 A and B\n", -1);
        UARTPuts("3. LP8731 A and LP3907 B\n", -1);
        UARTPuts("\n Enter Choice: ", -1);
        pmicType = UARTGetNum();

        /*
         * Get the pmic ops and register with the pmic interface.
         */
        if (1 == pmicType)
        {
            pmicOps       = PMHALTps65917GetPMICOps();
            choiceCorrect = 1U;
        }
        else if (2 == pmicType)
        {
            pmicOps       = PMHALLP8731GetPMICOps();
            choiceCorrect = 1U;
        }
        else if (3 == pmicType)
        {
            pmicOps       = PMHALLP8731LP3907GetPMICOps();
            choiceCorrect = 1U;
        }
        else
        {
            UARTPuts("\n Wrong Choice entered! Please enter again.\n", -1);
        }
    } while (choiceCorrect != 1U);

    status = PMHALPmicRegister(pmicOps);

    for (i = 0U; i < 10U; i++)
    {
        UARTPuts("\n----------------------------------------------------", -1);
        UARTPuts("\nIteration: ", -1);
        UARTPutNum(i);
        UARTPuts("\n----------------------------------------------------", -1);
        /*
         * Get the PMIC revision and print
         */
        if (status == PM_SUCCESS)
        {
            uint32_t    id;
            const char *verstr = PMHALPmicGetRevision();
            UARTPuts("\nPMIC Revision:", -1);
            UARTPuts((char *) verstr, -1);
            UARTPuts("\n", -1);

            status = PMHALPmicGetVendorId(&id);
            if (status == PM_SUCCESS)
            {
                UARTPuts("\nPMIC Vendor ID:", -1);
                UARTPutHexNum(id);
                UARTPuts("\n", -1);

                status = PMHALPmicGetProductId(&id);
                if (status == PM_SUCCESS)
                {
                    UARTPuts("\nPMIC Product ID:", -1);
                    UARTPutHexNum(id);
                    UARTPuts("\n", -1);
                }
            }
        }

        if (status == PM_SUCCESS)
        {
            UARTPuts("\nChecking for the Startup Voltages:\n", -1);
            status = checkStartupVoltages();
        }

        if (status == PM_SUCCESS)
        {
            UARTPuts("\nStartup Voltages Check is successful\n", -1);
            UARTPuts("\nChecking for Switching the OPP\n", -1);
            status = checkSwitchOPP();
        }

        if (status == PM_SUCCESS)
        {
            status = PMHALPmicGetRegulatorVoltage(
                PMHAL_PRCM_PMIC_REGULATOR_1V8PHY,
                &voltage);
            UARTPuts("\nPMHAL_PRCM_PMIC_REGULATOR_1V8PHY Voltage(mV) = ", -1);
            UARTPutNum(voltage);
            status = (pmErrCode_t) ((int32_t) status +
                                    (int32_t) PMHALPmicGetRegulatorVoltage(
                                        PMHAL_PRCM_PMIC_REGULATOR_DDR_DV,
                                        &voltage));
            UARTPuts("\nPMHAL_PRCM_PMIC_REGULATOR_DDR_DV Voltage(mV) = ", -1);
            UARTPutNum(voltage);
            status = (pmErrCode_t) ((int32_t) status +
                                    (int32_t) PMHALPmicGetRegulatorVoltage(
                                        PMHAL_PRCM_PMIC_REGULATOR_1V8PLL,
                                        &voltage));
            UARTPuts("\nPMHAL_PRCM_PMIC_REGULATOR_1V8PLL Voltage(mV) = ", -1);
            UARTPutNum(voltage);
        }

        if (status == PM_SUCCESS)
            UARTPuts("\nVM test: successful \n", -1);
        else
        {
            UARTPuts("\nVM test: failed \n", -1);
            UARTPutNum(status);
        }

        PMUtilsMinDelayUS(10U);
    }
    if (status == PM_SUCCESS)
    {
        UARTPuts("\n----------------------------------------------------", -1);
        UARTPuts("\n10 Iterations Pass", -1);
        UARTPuts("\n----------------------------------------------------", -1);
    }
    else
    {
        UARTPuts("\n----------------------------------------------------", -1);
        UARTPuts("\nVM Unit Test Fail", -1);
        UARTPuts("\n----------------------------------------------------", -1);
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t checkStartupVoltages(void)
{
    pmhalPrcmVdId_t vd;
    pmhalVmOppId_t  opp;
    pmErrCode_t     status = PM_SUCCESS;

    UARTPuts("\nOPP at Startup:", -1);

    for (vd = PMHAL_PRCM_VD_MIN;
         status == PM_SUCCESS && vd < PMHAL_PRCM_VD_COUNT;
         vd = (pmhalPrcmVdId_t) ((int32_t) vd + 1))
    {
        uint32_t v = 0U;

        UARTPuts("\nVD: ", -1);
        UARTPuts(vdStr[vd], -1);

        status = PMHALVMGetCurrentOpp(vd, &opp);

        if ((status == PM_SUCCESS) && (opp < PMHAL_VM_OPP_MAX)
             && (opp != PMHAL_VM_OPP_UNDEF))
        {
            UARTPuts(", OPP is : ", -1);
            UARTPuts(oppStr[opp], -1);
        }
        else
        {
            UARTPuts("\n\tPMHALVMGetCurrentOpp() failed", -1);
        }

        status = PMHALVMGetCurrentVoltage(vd, &v);

        if (status == PM_SUCCESS)
        {
            UARTPuts(", Voltage (mV): ", -1);
            UARTPutNum(v);
        }
        else
        {
            UARTPuts("\n\tPMHALVMGetCurrentVoltage() failed", -1);
        }
    }

    UARTPuts("\n", -1);

    return status;
}

static pmErrCode_t printNoMVoltage(pmhalPrcmVdId_t vd)
{
    pmErrCode_t status  = PM_SUCCESS;
    uint32_t    voltage = 0U;

    status = PMHALVMGetCurrentVoltage(vd, &voltage);
    if (status == PM_SUCCESS)
    {
        UARTPuts("\n\t\tNOM mV:", -1);
        UARTPutNum(voltage);
    }
    else
    {
        UARTPuts("\n\tPMHALVMGetCurrentVoltage() Failed\n", -1);
    }

    return status;
}

static pmErrCode_t switchOPP(pmhalPrcmVdId_t vd, pmhalVmOppId_t opp)
{
    pmErrCode_t status  = PM_SUCCESS;
    uint32_t    voltage = 0U;

    status = PMHALVMSetOpp(vd, opp, PM_TIMEOUT_INFINITE);

    PMUtilsMinDelayUS(5U);

    if (status == PM_SUCCESS)
    {
        pmhalVmOppId_t oppId = PMHAL_VM_OPP_UNDEF;
        status = PMHALVMGetCurrentOpp(vd, &oppId);
        if ((status != PM_SUCCESS) || (opp != oppId))
        {
            UARTPuts("\n\t PMHALVMGetCurrentOpp() Failed, ", -1);
            UARTPuts("required OPP = ", -1);
            UARTPuts(oppStr[opp], -1);
            UARTPuts(" Current OPP = ", -1);
            if(PMHAL_VM_OPP_UNDEF != oppId)
            {
                UARTPuts(oppStr[oppId], -1);
            }
        }
        else
        {
            status = PMHALVMGetCurrentVoltage(vd, &voltage);
            if (status == PM_SUCCESS)
            {
                UARTPuts("\n\t\t", -1);
                UARTPuts(oppStr[opp], -1);
                UARTPuts(" mV:", -1);
                UARTPutNum(voltage);
            }
            else
            {
                UARTPuts("\n\tPMHALVMGetCurrentVoltage() Failed\n", -1);
            }
        }
    }
    else
    {
        UARTPuts("\n\t PMHALVMSetOpp() Failed\n", -1);
    }

    return status;
}

static pmErrCode_t checkSwitchOPP()
{
    pmErrCode_t status = PM_SUCCESS;

    UARTPuts("\nSwitchOPP():", -1);

    /*
     * DSPEVE
     */
    if (status == PM_SUCCESS)
    {
        UARTPuts("\n\tDSPEVE:", -1);
        printNoMVoltage(PMHAL_PRCM_VD_DSPEVE);
    }
    UARTPuts("\nSwitch to OD: ... ", -1);
    if (status == PM_SUCCESS)
    {
        status = switchOPP(PMHAL_PRCM_VD_DSPEVE, PMHAL_VM_OPP_OD);
    }
    UARTPuts("\nSwitch to HIGH: ... ", -1);
    if (status == PM_SUCCESS)
    {
        status = switchOPP(PMHAL_PRCM_VD_DSPEVE, PMHAL_VM_OPP_HIGH);
    }
    UARTPuts("\nSwitch to NOM: ... ", -1);
    if (status == PM_SUCCESS)
    {
        status = switchOPP(PMHAL_PRCM_VD_DSPEVE, PMHAL_VM_OPP_NOM);
    }

    /*
     * CORE
     */
    if (status == PM_SUCCESS)
    {
        UARTPuts("\n\tCORE:", -1);
        status = printNoMVoltage(PMHAL_PRCM_VD_CORE);
    }
    UARTPuts("\nSwitch to NOM: ... ", -1);
    if (status == PM_SUCCESS)
    {
        status = switchOPP(PMHAL_PRCM_VD_CORE, PMHAL_VM_OPP_NOM);
    }

    return status;
}

static int32_t PmTestUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t i          = 0U;
    uint32_t baseAddr[] = {SOC_I2C1_BASE, SOC_I2C2_BASE};

    /* Force Wake-up clock domain L4PER1 */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C2,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    for (i = 0U; i < (sizeof (baseAddr) / sizeof (uint32_t)); i++)
    {
        /*
         * Do a soft reset so we can clear any incorrect state and
         * configure to suit the PMIC communication.
         */
        I2CSoftReset(baseAddr[i]);

        /*
         * Ensure that the reset is completed. The RDONE bit is set
         * only when the I2C is enabled, so enable I2C before
         * checking for the reset completion.
         */
        I2CMasterEnable(baseAddr[i]);

        timeout = 50U;  /* Approximately 50ms */
        while ((I2CSystemStatusGet(baseAddr[i]) !=
                I2C_SYSS_RDONE_RSTCOMP)
               && (timeout > 0))
        {
            PMUtilsMinDelayMS((uint32_t) 1U);
            timeout--;
        }

        if (timeout == 0)
        {
            status = STW_EFAIL;
        }

        if (status == STW_SOK)
        {
            /* Disable I2C so we can configure for the PMIC communication. */
            I2CMasterEnable(baseAddr[i]);

            /* Configure the I2C BUS clock frequency (I2C_SCL). */
            I2CMasterInitExpClk(baseAddr[i],
                                PM_TEST_UTILS_I2C_SYSTEM_CLOCK,
                                PM_TEST_UTILS_I2C_INTERNAL_CLOCK,
                                PM_TEST_UTILS_I2C_OUTPUT_CLOCK);

            /*
             * The PMIC communication is always as a master so we don't have
             * to configure the I2C own address. However, it doesn't hurt.
             */
            I2COwnAddressSet(baseAddr[i], 0,
                             I2C_OWN_ADDR_0);

            /*
             * Make sure the I2C is not in Forced Idle Mode by setting it to No
             * Idle mode.
             */
            I2CSyscInit(baseAddr[i],
                        (uint32_t) (I2C_AUTOIDLE_DISABLE |
                                    I2C_CUT_OFF_BOTH_CLK |
                                    I2C_ENAWAKEUP_DISABLE |
                                    I2C_NO_IDLE_MODE));

            /*
             * Configure the I2C:
             *    Select Fast/Standard Mode
             *    Select normal mode (vs. start byte mode)
             *    Select 7-bit slave address mode
             *
             * Note that this API writes the 32-bit value passed to the I2C_CON
             * register; the config bits not mentioned below is set to zero.
             */
            I2CConfig(baseAddr[i], I2C_CFG_N0RMAL_MODE |
                      I2C_CFG_7BIT_SLAVE_ADDR |
                      I2C_OPMODE_FAST_STAND_MODE);

            /* PMIC Comm uses polling mode; disable all the interrupts. */
            I2CMasterIntDisableEx(baseAddr[i], I2C_INT_ALL);

            /*
             * Bypass the Tx/Rx FIFO. For PRCM access we always read one byte
             * at a time so FIFO is bypassed.
             */
            I2CFIFOThresholdConfig(baseAddr[i],
                                   0, I2C_TX_MODE);
            I2CFIFOThresholdConfig(baseAddr[i],
                                   0, I2C_RX_MODE);
            I2CFIFOClear(baseAddr[i], I2C_TX_MODE);
            I2CFIFOClear(baseAddr[i], I2C_RX_MODE);

            /* Enable I2C module. */
            I2CMasterEnable(baseAddr[i]);

            /*
             * This is required to ensure that the I2C communication continues
             * even if A15 (the master core) is debug halted on a breakpoint.
             */
            I2CMasterEnableFreeRun(baseAddr[i]);
        }

        /* Clear status register  */
        I2CMasterIntClearEx(baseAddr[i], I2C_INT_ALL);
    }
    return status;
}

static int32_t PmTestUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                      const uint8_t *regAddr,
                                      uint8_t *regValue,
                                      uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = PmTestUtilsI2cRead(i2cNum, i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t PmTestUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                       const uint8_t *regAddr,
                                       const uint8_t *regValue,
                                       uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = PmTestUtilsI2cWrite(i2cNum, i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                            I2C_INT_BUS_FREE |
                                            I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t PmTestUtilsI2cRead(uint32_t i2cNum,
                                  uint8_t  slaveAddr,
                                  uint8_t *value)
{
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /* Set the slave address */
    I2CMasterSlaveAddrSet(baseAddress,
                          (uint32_t) slaveAddr);

    /* Configure to read 1 data word from the PMIC register.  */
    I2CSetDataCount(baseAddress, (uint32_t) 1U);

    /*
     * Configure i2c as master-receive and enable.
     * Make sure stop condition is generated after the transaction.
     */
    I2CMasterControl(baseAddress,
                     (uint32_t) (I2C_CFG_MST_RX | I2C_CFG_START | I2C_CFG_STOP));

    /* Read the data if the data is ready. */
    status = PmTestUtilsI2cCheckXfrStatus(i2cNum,
                                          (uint32_t) PM_TEST_UTILS_I2C_READ);
    if (status == STW_SOK)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value = 0U;
    }

    /* Wait for I2C access ready before returning. */
    if (status == STW_SOK)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t PmTestUtilsI2cWrite(uint32_t i2cNum,
                                   uint8_t slaveAddr, const uint8_t data[],
                                   uint8_t count)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = PmTestUtilsI2cWaitForBB(i2cNum);

    if (status == STW_SOK)
    {
        /* Set the slave address */
        I2CMasterSlaveAddrSet(baseAddress,
                              (uint32_t) slaveAddr);

        /* Configure to send 'count' data words */
        I2CSetDataCount(baseAddress, (uint32_t) count);

        /*
         * Configure i2c as master-transmitter, enable and set start condition.
         * Stop condition is NOT generated as this could be a part of write
         * followed by read (combined format).
         */
        I2CMasterControl(baseAddress,
                         I2C_CFG_MST_TX | I2C_CFG_START);

        /* Transmit 'count' bytes.  */
        for (i = 0; ((i < count) && (status == STW_SOK)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = PmTestUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                PM_TEST_UTILS_I2C_WRITE);
            if (status == PM_SUCCESS)
            {
                I2CMasterDataPut(baseAddress, data[i]);
            }

            /* Clear XRDY flags */
            rawSt = I2CMasterIntRawStatus(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_TRANSMIT_READY);
        }

        /*
         * Once we complete writing the 'count' bytes, wait for the
         * ARDY flag to be set. This flag indicates that the I2C
         * is access ready for next transmission. ARDY can also be
         * set if we received NACK so ensure it is not the case.
         */
        if (status == STW_SOK)
        {
            status = PmTestUtilsI2cWaitForFlags(i2cNum,
                                                I2C_INT_ADRR_READY_ACESS);
            if (status == STW_SOK)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status = STW_EFAIL;
                    /* Clear the NACK flag. */
                    I2CMasterIntClearEx(baseAddress,
                                        rawSt & I2C_INT_NO_ACK);
                }

                /* Clear the ARDY flag. */
                I2CMasterIntClearEx(baseAddress,
                                    rawSt & I2C_INT_ADRR_READY_ACESS);
            }
        }
    }

    return status;
}

static int32_t PmTestUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == PM_TEST_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == PM_TEST_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status = STW_EFAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == STW_SOK)
    {
        status = PmTestUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == STW_SOK)
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);

        /*
         * When I2C is configured as master-transmitter and didn't
         * receive ACK from slave, NACK condition is generated. The
         * following could cause this situation:
         * 1. No receiver is present on the bus with the transmitted
         *    address; board issue
         * 2. Receiver is not ready to communicate with the master
         *    (probably a board/pmic device issue).
         * 3. Receiver gets data or commands it doesn't understand
         *    (incorrect PMIC)
         * 4. Receiver can't receive any more data bytes.
         *
         * NACK can be handled by a master by either generating a
         * STOP condition or a repeated START condition to start
         * a new transfer. In PMIC COMM we generate a STOP
         * condition to abort the transfer and clear the NACK
         * flag.
         *
         * I2C HW clears STT and STP bits in I2C_CON registers.
         */
        if ((rawSt & I2C_INT_NO_ACK) != 0)
        {
            I2CMasterStop(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_NO_ACK);
            status = STW_EFAIL;
        }
        /*
         * Arbitration loss occurs when multiple masters initiate
         * transfer at the same time. Only one master wins and others
         * loose the arbitration. The arbitration loss flag is set
         * if this local host lost the arbitration. After an
         * arbitration loss, the local host can continue to generate
         * clock till the end of the byte transfer on the bus and
         * must restart the transmission. Recovering from arbitration
         * loss slightly complicates the code and this can be added
         * if there is a need. At present we clear the flag  and
         * return error.
         *
         * When arbitration loss occurs, the I2C HW clears the
         * STT, STP and MST bits. The local host switches to the
         * slave mode.
         */
        else if ((rawSt & I2C_INT_ARBITRATION_LOST) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ARBITRATION_LOST);
            status = STW_EFAIL;
        }
        /*
         * ARDY flag is set to indicate that the local host is access
         * ready. We are in the middle of a data transfer and hence
         * it is bad if we get ARDY flag set. For example, if we
         * get NACKed, the ARDY flag is set in the middle of data
         * transfer.
         */
        else if ((rawSt & I2C_INT_ADRR_READY_ACESS) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ADRR_READY_ACESS);
            status = STW_EFAIL;
        }
        /*
         * XRDY flag is set when the TX FIFO is empty or the TX FIFO
         * threshold is not reached. This means the local host can
         * transmit now.
         *
         * RRDY flag is set when the RX FIFO is empty or the RX FIFO
         * threshold is not reached. This means the local host can
         * receive now.
         */
        else if (((xfr == PM_TEST_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == PM_TEST_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = STW_SOK;
        }
        else
        {
            /*
             * We should not get here...
             */
            status = STW_EFAIL;
        }
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    return status;
}

static int32_t PmTestUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Clear all current interrupts first.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    for (timeout = PM_TEST_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}

