/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 *  \file        pmhal_lp8731.c
 *
 *  \brief       Power Management IC - LP8731 specific API implementation.
 *               APIs are exported by using function pointers.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_pmic.h"
#include <ti/drv/pm/include/pmic/pmhal_lp8731.h>
#include "pmhal_pmicComm.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Check if the LP8731 PMIC is present. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  PM_SUCCESS - LP8731 PMIC is present.
 *          PM_PMHAL_PMIC_VENDOR_ID_INVALID - PMIC vendor id doesn't match the
 *                                     expected value.
 *          PM_PMHAL_PMIC_PRODUCT_ID_INVALID - PMIC product id doesn't match the
 *                                      expected value.
 */
static pmErrCode_t PMHALLP8731IsPresent(void);

/**
 * \brief   Get the LP8731 PMIC chip revision. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  revString - The revision. "INVALID" is returned in case of error.
 */
static const char *PMHALLP8731GetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   vendorId    The Vendor ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8731GetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   productId   The Product ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8731GetProductId(uint32_t *productId);

/**
 * \brief  Get the voltage setting of the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId    Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param  voltage  Voltage in mV returned.
 *
 * \return status   PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8731GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage);

/**
 * \brief  Set the voltage of the regulator to the mV given. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 *         NOTE:
 *         PMIC allows controlling the voltage in many ways. The approach
 *         taken by this routine is to use the current configuration for
 *         voltage setting and try to succeed. It doesn't try to alter the
 *         configuration to ensure success. For example, if ROOF_FLOOR_EN
 *         control bit is set to 1 to mean that the voltage is controlled
 *         by the device resource pins, then this routine returns error;
 *         even though this bit can be changed to 0U to succeed.
 *
 * \param  regId    Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param  voltage  Voltage in mV returned.
 * \param  timeout  Timeout iterations to wait for setting the right regulator
 *                  voltage value. Possible values can be:
 *                  PM_TIMEOUT_NOWAIT   Do not wait for voltage setting.
 *                  PM_TIMEOUT_INFINITE Wait infinitely till the voltage is set.
 *                  Non Zero Value      Wait for the time provided by the user.
 *
 * \return Status   PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8731SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout);

/**
 * \brief  API to check if the given regulator enabled. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return enabled  TRUE if regulator is enabled; FALSE otherwise.
 */
static uint32_t    PMHALLP8731IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  Enable the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return status PM_SUCCESS if API is a success. PM_BADARGS/FAIL otherwise.
 */
static pmErrCode_t PMHALLP8731EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief  Disable the given regulator. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return status PM_SUCCESS if API is a success. PM_BADARGS/FAIL otherwise.
 */
static pmErrCode_t PMHALLP8731DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief   Return the Regulator Step voltage size. This is required by the
 *          voltage manager to understand the opp for the given voltage set for
 *          the given voltage rail.
 *
 * \param   regId       Regulator ID. Refer #pmhalPrcmPmicRegulatorId_t for
 *                      details.
 * \param   avsVoltage     AVS voltage which is to be converted to regulator
 *                      voltage
 *
 * \return  convVolt    The voltage that would be supplied by the regulator if
 *                      the AVS voltage is given to the API.
 *                      NOTE: This API does not program the PMIC. It just
 *                      returns the calculated value of AVS voltage converted to
 *                      PMIC voltage based on the PMIC voltage resolution.
 */
static uint32_t PMHALLP8731GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage);

#ifdef __cplusplus
}
#endif

/**
 * \brief Given voltage in mV and range, return the VSEL offset
 *
 * \param   regId   Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   voltage Voltage in mV.
 * \param   vsel    VSEL value returned.
 *
 * \return  status
 */
static pmErrCode_t PmhalLP8731VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel);

/**
 * \brief Given VSEL offset convert it to voltage in mV and return.
 *
 * \param   regId   Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   vsel    VSEL value returned.
 *
 * \return  voltage Voltage in mV.
 */
static uint32_t    PmhalLP8731VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   vsel);

/**
 * \brief  Read the register value at the given physical address.
 *
 * \param   i2cNumber   The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   The I2C PMIC Slave address.
 * \param   phyAddr     Address to be read.
 * \param   value       Returns the value read.
 *
 * \return  status      Return PM_SUCCESS if read is successful. Else returns
 *                      PM_FAIL.
 */
static pmErrCode_t PmhalLP8731ReadPhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
                                          uint32_t phyAddr, uint32_t *value);

/**
 * \brief  Write the given register value at the given physical address.
 *
 * \param   i2cNumber   The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   The I2C PMIC Slave address.
 * \param   phyAddr     Address to be written to.
 * \param   value       Returns the value to be written.
 *
 * \return Return success or failure.
 */
static pmErrCode_t PmhalLP8731WritePhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
                                           uint32_t phyAddr, uint32_t value);

/**
 * \brief  Is the given regulator enabled?
 *         This utility function must only be called by functions in this
 *         file and the caller must ensure that the PMIC communication is
 *         configured and enabled before calling this function.
 *
 * \param  regId  Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 *
 * \return TRUE if regulator is enabled; FALSE otherwise.
 */
static uint32_t PmhalLP8731CheckRegulatorEnabled
    (pmhalPrcmPmicRegulatorId_t regId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Power Management IC device callbacks. */
const pmhalPmicOperations_t       gPmhalLP8731Ops =
{
    &PMHALLP8731IsPresent,               /* isPresent */
    &PMHALLP8731GetRevision,             /* getRevision */
    &PMHALLP8731GetVendorId,             /* getVendorId */
    &PMHALLP8731GetProductId,            /* getProductId */
    &PMHALLP8731IsRegulatorEnabled,      /* isRegulatorEnabled */
    &PMHALLP8731EnableRegulator,         /* regulatorEnable */
    &PMHALLP8731DisableRegulator,        /* regulatorDisable */
    &PMHALLP8731GetRegulatorVoltage,     /* regulatorGetVoltage */
    &PMHALLP8731SetRegulatorVoltage,     /* regulatorSetVoltage */
    &PMHALLP8731GetRegulatorConvVoltage, /* regulatorGetConvVoltage */
};

/* Data structure to describe the regulator for all the regulators. */
const pmhalLP8731RegulatorProp_t  gPmhalLP8731Regulator[
    PMHAL_LP8731_REGULATOR_MAX] =
{
    /* PMHAL_LP8731_REGULATOR_BUCK1 */
    {
        8875U, 16750U, 125U, PMHAL_LP8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_LP8731_BKLDOSR_BK1_OK_SHIFT, PMHAL_LP8731_BKLDOSR_BK1_OK_SHIFT,
        PMHAL_LP8731_VCCR_BUCK1_RAMP_CTRL_SHIFT,
        PMHAL_LP8731_VCCR_BUCK1_TARG_VOLT_SEL_SHIFT, PMHAL_LP8731_B1TV1
    },
    /* PMHAL_LP8731_REGULATOR_BUCK2 */
    {
        8875U, 16750U, 125U, PMHAL_LP8731_RTYPE_BUCK, 8000U, 0x00U, 0x3FU,
        PMHAL_LP8731_BKLDOSR_BK2_OK_SHIFT, PMHAL_LP8731_BKLDOSR_BK2_OK_SHIFT,
        PMHAL_LP8731_VCCR_BUCK2_RAMP_CTRL_SHIFT,
        PMHAL_LP8731_VCCR_BUCK2_TARG_VOLT_SEL_SHIFT, PMHAL_LP8731_B2TV1
    },
    /*  PMHAL_LP8731_REGULATOR_LDO1 */
    {
        8000U, 33000U, 50U, PMHAL_LP8731_RTYPE_LDO, 8000U, 0x00U, 0x19U,
        PMHAL_LP8731_BKLDOSR_LDO1_OK_SHIFT, PMHAL_LP8731_BKLDOSR_LDO1_OK_SHIFT,
        0x0U, 0x0U, PMHAL_LP8731_LDO1VCR
    },
    /*  PMHAL_LP8731_REGULATOR_LDO2 */
    {
        8000U, 33000U, 50U, PMHAL_LP8731_RTYPE_LDO, 8000U, 0x00U, 0x19U,
        PMHAL_LP8731_BKLDOSR_LDO2_OK_SHIFT, PMHAL_LP8731_BKLDOSR_LDO2_OK_SHIFT,
        0x0U, 0x0U, PMHAL_LP8731_LDO2VCR
    }
};

/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalLP8731RegulatorMap_t         gPmhalDefaultLP8731RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalLP8731Regulator[PMHAL_LP8731_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8731_I2C_NUM_1,
        (uint8_t) PMHAL_LP8731_CHIP_ADDRESS
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalLP8731Regulator[PMHAL_LP8731_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8731_I2C_NUM_1,
        (uint8_t) PMHAL_LP8731_CHIP_ADDRESS
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        &gPmhalLP8731Regulator[PMHAL_LP8731_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8731_I2C_NUM_2,
        (uint8_t) PMHAL_LP8731_CHIP_ADDRESS
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DDR */
    {
        &gPmhalLP8731Regulator[PMHAL_LP8731_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8731_I2C_NUM_2,
        (uint8_t) PMHAL_LP8731_CHIP_ADDRESS
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        &gPmhalLP8731Regulator[PMHAL_LP8731_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8731_I2C_NUM_2,
        (uint8_t) PMHAL_LP8731_CHIP_ADDRESS
    }
};

/* Pointer to array of pointers describing the mapping from regulators to
 * device voltage rails.
 */
static pmhalLP8731RegulatorMap_t *gPmhalLP8731RegulatorTable =
    gPmhalDefaultLP8731RegulatorTable;

/* Chip Revisions of the PMIC. */
const char *gPmhalLP8731RevStrings[PMHAL_PMIC_MAX_REV] =
{"CS1.0", "CS2.0", "CS2.1", "CS2.2"};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalPmicOperations_t *PMHALLP8731GetPMICOps(void)
{
    return &gPmhalLP8731Ops;
}

void PMHALLP8731ConfigureRegulatorMap(pmhalLP8731RegulatorMapPtr_t regulatorMap)
{
    /* If the regulatorMap provided by the caller is NULL then the default
     * regulator map as present on TI EVMs is used.
     */
    if (NULL == regulatorMap)
    {
        gPmhalLP8731RegulatorTable = gPmhalDefaultLP8731RegulatorTable;
    }
    else
    {
        gPmhalLP8731RegulatorTable = regulatorMap;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PMHALLP8731GetVendorId(uint32_t *vendorId)
{
    /* This is a dummy function to match with the other PMIC ICs. Vendor ID
     * Register not defined in the data sheet.
     */
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == vendorId)
    {
        status = PM_BADARGS;
    }
    else
    {
        *vendorId = PMHAL_LP8731_VENDOR_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP8731GetProductId(uint32_t *productId)
{
    /* This is a dummy function to match with the other PMIC ICs. Product ID
     * Register not defined in the data sheet.
     */
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == productId)
    {
        status = PM_BADARGS;
    }
    else
    {
        *productId = PMHAL_LP8731_1_0_PRODUCT_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP8731IsPresent(void)
{
    uint32_t    prodId = 0U, vendorId = 0U;
    pmErrCode_t status = PM_SUCCESS;

    /*
     * Check if the LP8731 PMIC is present. This function
     * ensures that this specific PMIC is in the system by
     * reading and verifying the vendor ID and product ID.
     * Return success only if the vendor ID and product ID
     * matches the expected value.
     */

    /* Check the Vendor ID. */
    status = PMHALLP8731GetVendorId(&vendorId);

    /* Check the Product ID. */
    if (PMHAL_LP8731_VENDOR_ID == vendorId)
    {
        status = PMHALLP8731GetProductId(&prodId);
    }

    return status;
}

static const char *PMHALLP8731GetRevision(void)
{
    /* This is a dummy function to match with the other PMIC ICs. Revision ID
     * Register not defined in the data sheet.
     */
    uint32_t    rev;
    const char *revString = "INVALID";

    rev = 0U;
    if (rev < PMHAL_PMIC_MAX_REV)
    {
        revString = gPmhalLP8731RevStrings[rev];
    }

    return revString;
}

static pmErrCode_t PMHALLP8731GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    ctrl;
    uint32_t    vsel = 0U;
    const pmhalLP8731RegulatorProp_t *regulator;
    uint8_t     i2cNumber, slaveAddr;

    if ((NULL == voltage) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8731RegulatorTable[regId].regulatorMap;
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8731RegulatorTable[regId].i2cSlaveAddress;
        *voltage  = 0U;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);

        if ((TRUE == PmhalLP8731CheckRegulatorEnabled(regId)) &&
            (PM_SUCCESS == status))
        {
            if (PMHAL_LP8731_RTYPE_BUCK == regulator->type)
            {
                /* The VCCR register holds the information as to which target
                 * voltage register must be read to see if the voltage is
                 * set correctly.
                 */
                status = PmhalLP8731ReadPhyAddr(
                    (uint8_t) i2cNumber, (uint8_t) slaveAddr,
                    (uint32_t)
                    PMHAL_LP8731_BUCK_VCCR,
                    &ctrl);
                /* Read the corresponding target voltage register */
                if ((ctrl &
                     ((uint32_t) 1U <<
                      (uint32_t) regulator->vccrTargetVoltSelShift)) ==
                    (uint32_t) 0U)
                {
                    status = PmhalLP8731ReadPhyAddr(
                        i2cNumber, (uint8_t) slaveAddr,
                        (uint32_t) regulator->
                        voltageControlReg,
                        &vsel);
                }
                else
                {
                    status = PmhalLP8731ReadPhyAddr(i2cNumber,
                                                    (uint8_t) slaveAddr,
                                                    ((uint32_t) regulator->
                                                     voltageControlReg
                                                     + (uint32_t) 0x4U), &vsel);
                }
                if (PM_SUCCESS == status)
                {
                    *voltage = PmhalLP8731VselOffsetToVoltage(regId, vsel);
                }
            }
            else
            {
                /* For the LDOs there are dedicated target voltage registers */
                status = PmhalLP8731ReadPhyAddr(i2cNumber, (uint8_t) slaveAddr,
                                                regulator->voltageControlReg,
                                                &vsel);
                if (PM_SUCCESS == status)
                {
                    *voltage = PmhalLP8731VselOffsetToVoltage(regId, vsel);
                }
            }
        }
    }

    return status;
}

static pmErrCode_t PMHALLP8731SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    ctrl   = 0U;
    uint32_t    vsel   = 0U;
    const pmhalLP8731RegulatorProp_t *regulator;
    uint8_t     i2cNumber, slaveAddr;
    uint32_t    currVolt = 0U;

    /*
     * Check whether input arguments are correct. Check for the voltage is done
     * later in the function.
     */
    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8731RegulatorTable[regId].regulatorMap;
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8731RegulatorTable[regId].i2cSlaveAddress;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);

        if (TRUE == PmhalLP8731CheckRegulatorEnabled(regId))
        {
            PmhalLP8731VoltageToVselOffset(regId, voltage, &vsel);
            if (PMHAL_LP8731_RTYPE_BUCK == regulator->type)
            {
                /* Configure the target voltage. Then set the VCCR register to
                 * read the desired target voltage register and then ramp the
                 * voltage to the desired target register.
                 */
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        regulator->voltageControlReg,
                                        vsel);
                PmhalLP8731ReadPhyAddr(i2cNumber, (uint8_t) slaveAddr,
                                       (uint32_t) PMHAL_LP8731_BUCK_VCCR,
                                       &ctrl);
                ctrl = ctrl &
                       ~((uint32_t) 1U <<
                         (uint32_t) regulator->vccrTargetVoltSelShift);
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) PMHAL_LP8731_BUCK_VCCR,
                                        ctrl);
                /* Ramp to voltage */
                ctrl = ctrl |
                       ((uint32_t) 1U <<
                        (uint32_t) regulator->vccrRampCtrlShift);
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) PMHAL_LP8731_BUCK_VCCR,
                                        ctrl);
            }
            else
            {
                /* For LDO just configure the voltage. No status registers to
                 * observe.
                 */
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) regulator->voltageControlReg,
                                        vsel);
            }
        }
        /*
         * Wait for the voltage ramp up to complete. The caller can perform
         * operations that require the voltage rail to be at the given voltage
         * right after this call. So, ensure the voltage ramps up before
         * returning.
         */
        if (PM_SUCCESS == status)
        {
            uint32_t newV = PmhalLP8731VselOffsetToVoltage(regId, vsel);

            if (PM_TIMEOUT_INFINITE == timeout)
            {
                while (newV != currVolt)
                {
                    PMHALLP8731GetRegulatorVoltage(regId, &currVolt);
                }
            }
            else if (PM_TIMEOUT_NOWAIT == timeout)
            {
                ; /* nothing to do here */
            }
            else
            {
                uint32_t timeToWait = timeout;

                while ((newV != currVolt) && (0U != timeToWait))
                {
                    PMHALLP8731GetRegulatorVoltage(regId, &currVolt);
                    timeToWait--;
                }

                if (0U == timeToWait)
                {
                    status = PM_FAIL;
                }
            }
        }
    }
    return status;
}

static uint32_t PMHALLP8731IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t    enabled   = 0U;
    pmErrCode_t status    = PM_SUCCESS;
    uint8_t     i2cNumber = (uint8_t) 0U;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
    }

    if (PM_SUCCESS == status)
    {
        enabled = (uint32_t) PmhalLP8731CheckRegulatorEnabled(regId);
    }

    return enabled;
}

static pmErrCode_t PMHALLP8731EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalLP8731RegulatorProp_t *regulator;
    uint32_t    value   = 0U;
    uint32_t    enabled = FALSE;
    uint8_t     i2cNumber, slaveAddr;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8731RegulatorTable[regId].regulatorMap;
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8731RegulatorTable[regId].i2cSlaveAddress;

        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
        if (PM_SUCCESS == status)
        {
            /*
             * If the Regulator is disabled, enable by setting the MODE_ACTIVE
             * and MODE_SLEEP to 0x01 (Forced PWM)
             */
            enabled = PmhalLP8731CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                PmhalLP8731ReadPhyAddr(i2cNumber, slaveAddr,
                                       (uint32_t) PMHAL_LP8731_BKLDOEN,
                                       &value);
                value = value |
                        ((uint32_t) 1U << (uint32_t) regulator->voltEnRegShift);
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) PMHAL_LP8731_BKLDOEN,
                                        value);

                enabled = PmhalLP8731CheckRegulatorEnabled(regId);
                if (FALSE == enabled)
                {
                    status = PM_FAIL;
                }
            }
        }
    }
    return status;
}

static pmErrCode_t PMHALLP8731DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNumber, slaveAddr;
    uint32_t    value;
    const pmhalLP8731RegulatorProp_t *regulator;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8731RegulatorTable[regId].regulatorMap;
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8731RegulatorTable[regId].i2cSlaveAddress;

        /* Configure and enable PMIC communication bus. */
        status = PMHALPmicCommConfigure(i2cNumber);

        /* If the Regulator is enabled, disable by setting the voltage to 0U. */
        if (PM_SUCCESS == status)
        {
            if (TRUE == PmhalLP8731CheckRegulatorEnabled(regId))
            {
                PmhalLP8731ReadPhyAddr(i2cNumber, slaveAddr,
                                       (uint32_t) PMHAL_LP8731_BKLDOEN,
                                       &value);
                value = value &
                        ~((uint32_t) 1U << (uint32_t) regulator->voltEnRegShift);
                PmhalLP8731WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) PMHAL_LP8731_BKLDOEN,
                                        value);

                /* Check if the regulator is truly disabled */
                if (TRUE == PmhalLP8731CheckRegulatorEnabled(regId))
                {
                    status = PM_FAIL;
                }
            }
        }
    }

    return status;
}

static uint32_t PMHALLP8731GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    convVoltage  = 0U;
    uint32_t    internalVsel = 0U;

    status = PmhalLP8731VoltageToVselOffset(regId, avsVoltage, &internalVsel);
    if (PM_SUCCESS == status)
    {
        convVoltage = PmhalLP8731VselOffsetToVoltage(regId, internalVsel);
    }

    return convVoltage;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalLP8731CheckRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t enabled = FALSE;
    uint32_t ctrl    = 0U;
    uint8_t  i2cNumber, slaveAddr;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8731RegulatorProp_t *regulator =
        gPmhalLP8731RegulatorTable[regId].regulatorMap;
    i2cNumber = gPmhalLP8731RegulatorTable[regId].i2cInstanceNum;
    slaveAddr = gPmhalLP8731RegulatorTable[regId].i2cSlaveAddress;

    /* Read the regulator CTRL_STATUS and return the status. */
    if (PM_SUCCESS ==
        PmhalLP8731ReadPhyAddr(i2cNumber, slaveAddr,
                               (uint32_t) PMHAL_LP8731_BKLDOEN,
                               &ctrl))
    {
        if ((ctrl &
             ((uint32_t) 1U << (uint32_t) regulator->voltStatusRegShift)) !=
            (uint32_t) PMHAL_LP8731_STATUS_OFF)
        {
            enabled = TRUE;
        }
    }

    return enabled;
}

static pmErrCode_t PmhalLP8731VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    internalVsel = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8731RegulatorProp_t *regulator =
        gPmhalLP8731RegulatorTable[regId].regulatorMap;

    if (NULL == vsel)
    {
        status = PM_BADARGS;
    }
    else
    {
        /* Convert the Voltage from mV to 10 ^ (-4) V */
        voltage = voltage * 10U;

        if (0U == voltage)
        {
            internalVsel = 0U;
        }
        else if (voltage > regulator->maxVolt)
        {
            internalVsel = regulator->maxVoltVsel;
            status       = PM_BADARGS;
        }
        else
        {
            /* +1 is added here to ensure the voltage would be higher than
             * requested when the voltage is not an exact multiple of step
             * voltage.
             */
            uint32_t remainder = (voltage - regulator->minVolt) %
                                 regulator->stepVolt;
            if (remainder > 0U)
            {
                internalVsel =
                    ((voltage - regulator->minVolt) / regulator->stepVolt) +
                    regulator->minVoltVsel + 1U;
            }
            else
            {
                internalVsel =
                    ((voltage - regulator->minVolt) / regulator->stepVolt) +
                    regulator->minVoltVsel;
            }
        }

        if (PMHAL_LP8731_RTYPE_BUCK == regulator->type)
        {
            /* In the BUCK target voltage register the voltage is represented
             * as the following table:
             *
             * ---------------------------------------------------------------
             * | D7 - D6       |    D5       |   D4 -D0      |   Voltage     |
             * | Reserved      | 12p5 mV Step|    B1TV1      |      (V)      |
             * ---------------------------------------------------------------
             * |               |     0b0     |   0b0 0000    |   0.8875      |
             * |               |     0b1     |   0b0 0000    |   0.9000      |
             * |               |     0b0     |   0b0 0001    |   0.9125      |
             * |               |     0b1     |   0b0 0001    |   0.9000      |
             * | ....................................
             * |               |     0b1     |   0b1 1110    |   1.6500      |
             * |               |     0b0     |   0b1 1111    |   1.6625      |
             * |               |     0b1     |   0b1 1111    |   1.6750      |
             * ---------------------------------------------------------------
             * As can be seen re-arranging the bits as 0b D4 D3 D2 D1 D0 D5 then
             * a sequential numbering scheme can be obtained. Hence even the
             * limits for VSEL are given as the sequential numbering scheme to
             * make the conversion easy.
             */
            *vsel = ((internalVsel & (uint32_t) 0x1U) << (uint32_t) 5U) |
                    ((internalVsel & (uint32_t) 0x1E) >> (uint32_t) 1U);
        }
        else
        {
            *vsel = internalVsel;
        }
    }
    return status;
}

static uint32_t PmhalLP8731VselOffsetToVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                               uint32_t                   vsel)
{
    uint32_t mv;
    uint32_t modVsel = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8731RegulatorProp_t *regulator =
        gPmhalLP8731RegulatorTable[regId].regulatorMap;

    if (PMHAL_LP8731_RTYPE_BUCK == regulator->type)
    {
        /* In the BUCK target voltage register the voltage is represented
         * as the following table:
         *
         * ---------------------------------------------------------------
         * | D7 - D6       |    D5       |   D4 -D0      |   Voltage     |
         * | Reserved      | 12p5 mV Step|    B1TV1      |      (V)      |
         * ---------------------------------------------------------------
         * |               |     0b0     |   0b0 0000    |   0.8875      |
         * |               |     0b1     |   0b0 0000    |   0.9000      |
         * |               |     0b0     |   0b0 0001    |   0.9125      |
         * |               |     0b1     |   0b0 0001    |   0.9000      |
         * | ....................................
         * |               |     0b1     |   0b1 1110    |   1.6500      |
         * |               |     0b0     |   0b1 1111    |   1.6625      |
         * |               |     0b1     |   0b1 1111    |   1.6750      |
         * ---------------------------------------------------------------
         * As can be seen re-arranging the bits as 0b D4 D3 D2 D1 D0 D5 then
         * a sequential numbering scheme can be obtained. Hence even the
         * limits for VSEL are given as the sequential numbering scheme to make
         * the conversion easy.
         */
        modVsel = ((vsel & (uint32_t) 0x1FU) << (uint32_t) 1U) |
                  ((vsel & (uint32_t) 0x20U) >> (uint32_t) 5U);
    }
    else
    {
        modVsel = vsel;
    }

    if (0U == vsel)
    {
        mv = 0U;
    }
    else if (modVsel <= regulator->minVoltVsel)
    {
        mv = regulator->minVolt;
    }
    else if (modVsel >= regulator->maxVoltVsel)
    {
        mv = regulator->maxVolt;
    }
    else
    {
        mv = regulator->minVolt +
             (regulator->stepVolt * (modVsel - regulator->minVoltVsel));
    }
    /* To Convert to milli volt from 10 ^ (-4) volts*/
    mv = mv / 10U;

    return mv;
}

static pmErrCode_t PmhalLP8731ReadPhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
                                          uint32_t phyAddr, uint32_t *value)
{
    uint8_t     slaveAddrInternal;
    uint8_t     regAddr;
    pmErrCode_t status;
    uint8_t     byte;

    if (NULL == value)
    {
        status = PM_BADARGS;
    }
    else
    {
        byte = (uint8_t) *value;
        slaveAddrInternal = (uint8_t) slaveAddr;
        regAddr           = (uint8_t) phyAddr;
        status = PMHALPmicCommReadByte(i2cNumber,
                                       slaveAddrInternal, regAddr, &byte);
        *value = byte;
    }

    return status;
}

static pmErrCode_t PmhalLP8731WritePhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
                                           uint32_t phyAddr, uint32_t value)
{
    uint8_t     slaveAddrInternal;
    uint8_t     regAddr;
    uint8_t     byte;
    pmErrCode_t status;

    byte = (uint8_t) value;
    slaveAddrInternal = (uint8_t) slaveAddr;
    regAddr           = (uint8_t) phyAddr;
    status = PMHALPmicCommWriteByte(i2cNumber, slaveAddrInternal, regAddr, byte);

    return status;
}

