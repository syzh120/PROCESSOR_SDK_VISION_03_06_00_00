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
 *  \file        pmhal_lp8733.c
 *
 *  \brief       Power Management IC - LP8733 specific API implementation.
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
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#include "pmhal_pmicComm.h"
#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Output voltage step for the Buck regulator for the output voltage
 *         between 0.7 V - 0.73 V, 10 mV steps. Step voltage in 10^ (-4) V.
 */
#define PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE1    (100U)

/** \brief Output voltage step for the Buck regulator for the output voltage
 *         between 0.73 V - 1.4 V, 5 mV steps. Step voltage in 10^ (-4) V.
 */
#define PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE2    (50U)

/** \brief Output voltage step for the Buck regulator for the output voltage
 *         between 1.4 V - 3.36 V, 20 mV steps. Step voltage in 10^ (-4) V.
 */
#define PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE3    (200U)

/** \brief Output voltage minimum and maximum values for Buck Regulators
 *         Range 1: 0.7 V - 0.73 V
 */
#define PMHAL_LP8733_BUCK_RANGE1_MIN_VOLTAGE     (7000U)
#define PMHAL_LP8733_BUCK_RANGE1_MAX_VOLTAGE     (7300U)

/** \brief Minimum and Maximum value of VSEL for Range 1 */
#define PMHAL_LP8733_BUCK_RANGE1_MIN_VSEL        (0x14U)
#define PMHAL_LP8733_BUCK_RANGE1_MAX_VSEL        (0x17U)

/** \brief Output voltage minimum and maximum values for Buck Regulators
 *         Range 2: 0.735 V - 1.4 V
 */
#define PMHAL_LP8733_BUCK_RANGE2_MIN_VOLTAGE     (7350U)
#define PMHAL_LP8733_BUCK_RANGE2_MAX_VOLTAGE     (14000U)

/** \brief Minimum and Maximum value of VSEL for Range 2 */
#define PMHAL_LP8733_BUCK_RANGE2_MIN_VSEL        (0x18U)
#define PMHAL_LP8733_BUCK_RANGE2_MAX_VSEL        (0x9DU)

/** \brief Output voltage minimum and maximum values for Buck Regulators
 *         Range 3: 1.42 V - 3.36 V
 */
#define PMHAL_LP8733_BUCK_RANGE3_MIN_VOLTAGE     (14200U)
#define PMHAL_LP8733_BUCK_RANGE3_MAX_VOLTAGE     (33600U)

/** \brief Minimum and Maximum value of VSEL for Range 3 */
#define PMHAL_LP8733_BUCK_RANGE3_MIN_VSEL        (0x9EU)
#define PMHAL_LP8733_BUCK_RANGE3_MAX_VSEL        (0xFFU)

/** \brief Output voltage step for the LDO regulator. */
#define PMHAL_LP8733_LDO_STEP_VOLTAGE            (1000U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Check if the LP8733 PMIC is present. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  PM_SUCCESS - LP8733 PMIC is present.
 *          PM_PMHAL_PMIC_VENDOR_ID_INVALID - PMIC vendor id doesn't match the
 *                                     expected value.
 *          PM_PMHAL_PMIC_PRODUCT_ID_INVALID - PMIC product id doesn't match the
 *                                      expected value.
 */
static pmErrCode_t PMHALLP8733IsPresent(void);

/**
 * \brief   Get the LP8733 PMIC chip revision. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  revString - The revision. "INVALID" is returned in case of error.
 */
static const char *PMHALLP8733GetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   vendorId    The Vendor ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8733GetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   productId   The Product ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8733GetProductId(uint32_t *productId);

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
static pmErrCode_t PMHALLP8733GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage);

/**
 * \brief  Set the voltage of the regulator to the mV given. The declaration is
 *         present here to ensure this function is used only via function
 *         pointer.
 *
 * \param  regId    Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t for
 *                  more details.
 * \param  voltage  Voltage in mV returned.
 * \param  timeout  Timeout iterations to wait for setting the right regulator
 *                  voltage value. Possible values can be:
 *                  PM_TIMEOUT_NOWAIT   Do not wait for voltage setting.
 *                  PM_TIMEOUT_INFINITE Wait infinitely till the voltage is set.
 *                  Non Zero Value      Wait for the time provided by the user.
 *
 * \return Status   PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP8733SetRegulatorVoltage(
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
static uint32_t    PMHALLP8733IsRegulatorEnabled(
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
static pmErrCode_t PMHALLP8733EnableRegulator(
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
static pmErrCode_t PMHALLP8733DisableRegulator(
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
static uint32_t PMHALLP8733GetRegulatorConvVoltage(
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
static pmErrCode_t PmhalLP8733VoltageToVselOffset(
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
static uint32_t    PmhalLP8733VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   vsel);

/**
 * \brief  Read the register value at the given physical address.
 *
 * \param   i2cNumber    The PMIC chip number to which the voltage regulator is
 *                      connected.
 * \param   slaveAddr   The I2C PMIC Slave address.
 * \param   phyAddr     Address to be read.
 * \param   value       Returns the value read.
 *
 * \return  status      Return PM_SUCCESS if read is successful. Else returns
 *                      PM_FAIL.
 */
static pmErrCode_t PmhalLP8733ReadPhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
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
static pmErrCode_t PmhalLP8733WritePhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
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
static uint32_t PmhalLP8733CheckRegulatorEnabled
    (pmhalPrcmPmicRegulatorId_t regId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Power Management IC device callbacks. */
const pmhalPmicOperations_t       gPmhalLP8733Ops =
{
    &PMHALLP8733IsPresent,               /* isPresent */
    &PMHALLP8733GetRevision,             /* getRevision */
    &PMHALLP8733GetVendorId,             /* getVendorId */
    &PMHALLP8733GetProductId,            /* getProductId */
    &PMHALLP8733IsRegulatorEnabled,      /* isRegulatorEnabled */
    &PMHALLP8733EnableRegulator,         /* regulatorEnable */
    &PMHALLP8733DisableRegulator,        /* regulatorDisable */
    &PMHALLP8733GetRegulatorVoltage,     /* regulatorGetVoltage */
    &PMHALLP8733SetRegulatorVoltage,     /* regulatorSetVoltage */
    &PMHALLP8733GetRegulatorConvVoltage, /* regulatorGetConvVoltage */
};

/* Data structure to describe the regulator for all the regulators. */
const pmhalLP8733RegulatorProp_t  gPmhalLP8733Regulator[
    PMHAL_LP8733_REGULATOR_MAX] =
{
    /* PMHAL_LP8733_REGULATOR_BUCK1 */
    {
        7000U, 33600U, PMHAL_LP8733_RTYPE_BUCK, 0x14U, 0xFFU,
        PMHAL_LP8733_BUCK0_CTRL_1, PMHAL_LP8733_BUCK_STAT,
        PMHAL_LP8733_BUCK_CTRL_BUCK_EN_SHIFT,
        PMHAL_LP8733_BUCK_STAT_BUCK0_STAT_SHIFT, PMHAL_LP8733_BUCK0_VOUT
    },
    /* PMHAL_LP8733_REGULATOR_BUCK2 */
    {
        7000U, 33600U, PMHAL_LP8733_RTYPE_BUCK, 0x14U, 0xFFU,
        PMHAL_LP8733_BUCK1_CTRL_1, PMHAL_LP8733_BUCK_STAT,
        PMHAL_LP8733_BUCK_CTRL_BUCK_EN_SHIFT,
        PMHAL_LP8733_BUCK_STAT_BUCK1_STAT_SHIFT, PMHAL_LP8733_BUCK1_VOUT
    },
    /*  PMHAL_LP8733_REGULATOR_LDO1 */
    {
        8000U, 33000U, PMHAL_LP8733_RTYPE_LDO, 0x00U, 0x19U,
        PMHAL_LP8733_LDO0_CTRL, PMHAL_LP8733_LDO_STAT,
        PMHAL_LP8733_LDO_CTRL_LDO_EN_SHIFT,
        PMHAL_LP8733_LDO_STAT_LDO0_STAT_SHIFT,
        PMHAL_LP8733_LDO0_VOUT
    },
    /*  PMHAL_LP8733_REGULATOR_LDO2 */
    {
        8000U, 33000U, PMHAL_LP8733_RTYPE_LDO, 0x00U, 0x19U,
        PMHAL_LP8733_LDO0_CTRL, PMHAL_LP8733_LDO_STAT,
        PMHAL_LP8733_LDO_CTRL_LDO_EN_SHIFT,
        PMHAL_LP8733_LDO_STAT_LDO1_STAT_SHIFT,
        PMHAL_LP8733_LDO1_VOUT
    }
};

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalLP8733RegulatorMap_t         gPmhalLP8733DefaultRegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DDR */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    }
};
#endif

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalLP8733RegulatorMap_t         gPmhalLP8733DefaultRegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MPU */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_IVA */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_GPU */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_SHV5.
     * This is not connected  for J6 Eco 17X17 Evm. */
    {
        NULL,
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO2],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_LDO1],
        (uint8_t) PMHAL_LP8733_I2C_NUMBER,
        (uint8_t) PMHAL_LP8733_CHIP_ADDRESS_2
    }
};
#endif

/* Pointer to array of pointers describing the mapping from regulators to
 * device voltage rails.
 */
static pmhalLP8733RegulatorMap_t *gPmhalLP8733RegulatorTable =
    gPmhalLP8733DefaultRegulatorTable;

/* Chip Revisions of the PMIC. */
const char *gPmhalLP8733RevStrings[PMHAL_PMIC_MAX_REV] =
{"CS1.0", "CS2.0", "CS2.1", "CS2.2"};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalPmicOperations_t *PMHALLP8733GetPMICOps(void)
{
    return &gPmhalLP8733Ops;
}

void PMHALLP8733ConfigureRegulatorMap(pmhalLP8733RegulatorMapPtr_t regulatorMap)
{
    /* If the regulatorMap provided by the caller is NULL then the default
     * regulator map as present on TI EVMs is used.
     */
    if (NULL == regulatorMap)
    {
        gPmhalLP8733RegulatorTable = gPmhalLP8733DefaultRegulatorTable;
    }
    else
    {
        gPmhalLP8733RegulatorTable = regulatorMap;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PMHALLP8733GetVendorId(uint32_t *vendorId)
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
        *vendorId = PMHAL_LP8733_VENDOR_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP8733GetProductId(uint32_t *productId)
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
        *productId = PMHAL_LP8733_1_0_PRODUCT_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP8733IsPresent(void)
{
    uint32_t    prodId = 0U, vendorId = 0U;
    pmErrCode_t status = PM_SUCCESS;

    /*
     * Check if the LP8733 PMIC is present. This function
     * ensures that this specific PMIC is in the system by
     * reading and verifying the vendor ID and product ID.
     * Return success only if the vendor ID and product ID
     * matches the expected value.
     */

    /* Check the Vendor ID. */
    status = PMHALLP8733GetVendorId(&vendorId);

    /* Check the Product ID. */
    if (PMHAL_LP8733_VENDOR_ID == vendorId)
    {
        status = PMHALLP8733GetProductId(&prodId);
    }

    return status;
}

static const char *PMHALLP8733GetRevision(void)
{
    uint8_t     i2cNumber, slaveAddr;
    uint32_t    rev       = 0U;
    const char *revString = "INVALID";
    pmErrCode_t status    = PM_SUCCESS;
    /* There are 2 ICs which provide for the voltage rails on different
     * I2C lines. Depending on the regulator ID read which I2C line does
     * this correspond to.
     */
    i2cNumber =
        gPmhalLP8733RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
        i2cInstanceNum;
    slaveAddr =
        gPmhalLP8733RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
        i2cSlaveAddress;
    /*
     * Configure and enable PMIC communication bus.
     */
    status = PMHALPmicCommConfigure(i2cNumber);

    /*
     * Get the Chip Revision ID.
     */
    if (PM_SUCCESS == status)
    {
        status = PmhalLP8733ReadPhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) PMHAL_LP8733_DEV_REV,
                                        &rev);
    }

    if (PM_SUCCESS == status)
    {
        rev = HW_GET_FIELD(rev, PMHAL_LP8733_DEV_REV_DEVICE_ID);
        if (rev < PMHAL_PMIC_MAX_REV)
        {
            revString = gPmhalLP8733RevStrings[rev];
        }
    }

    return revString;
}

static pmErrCode_t PMHALLP8733GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    vsel   = 0U;
    const pmhalLP8733RegulatorProp_t *regulator;
    uint8_t     i2cNumber, slaveAddr;

    if ((NULL == voltage) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8733RegulatorTable[regId].regulatorMap;
        /* There are 2 PMIC ICs which provide for the voltage rails on same
         * I2C lines. Depending on the regulator ID read which PMIC IC does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8733RegulatorTable[regId].i2cSlaveAddress;
        *voltage  = 0U;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);

        if ((TRUE == PmhalLP8733CheckRegulatorEnabled(regId)) &&
            (PM_SUCCESS == status))
        {
            /* The Buck/LDO VOUT register should be checked for the output
             * voltage.
             */
            status = PmhalLP8733ReadPhyAddr(
                i2cNumber, slaveAddr,
                (uint32_t) regulator->
                voutSetRegAddr,
                &vsel);
            if (PM_SUCCESS == status)
            {
                *voltage = PmhalLP8733VselOffsetToVoltage(regId, vsel);
            }
        }
    }

    return status;
}

static pmErrCode_t PMHALLP8733SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    vsel   = 0U;
    const pmhalLP8733RegulatorProp_t *regulator;
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
        regulator = gPmhalLP8733RegulatorTable[regId].regulatorMap;
        /* There are 2 PMIC ICs which provide for the voltage rails on same
         * I2C lines. Depending on the regulator ID read which PMIC IC does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8733RegulatorTable[regId].i2cSlaveAddress;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);
        if (PM_SUCCESS == status)
        {
            status = PMHALLP8733EnableRegulator(regId);
            if (TRUE == PmhalLP8733CheckRegulatorEnabled(regId))
            {
                PmhalLP8733VoltageToVselOffset(regId, voltage, &vsel);
                /* For LDO/BUCK just configure the voltage. */
                PmhalLP8733WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) regulator->voutSetRegAddr,
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
            uint32_t newV = PmhalLP8733VselOffsetToVoltage(regId, vsel);

            if (PM_TIMEOUT_INFINITE == timeout)
            {
                while (newV != currVolt)
                {
                    PMHALLP8733GetRegulatorVoltage(regId, &currVolt);
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
                    PMHALLP8733GetRegulatorVoltage(regId, &currVolt);
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

static uint32_t PMHALLP8733IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t    enabled = 0U;
    uint8_t     i2cNumber;
    pmErrCode_t status = PM_SUCCESS;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
    }

    if (PM_SUCCESS == status)
    {
        enabled = (uint32_t) PmhalLP8733CheckRegulatorEnabled(regId);
    }

    return enabled;
}

static pmErrCode_t PMHALLP8733EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalLP8733RegulatorProp_t *regulator;
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
        regulator = gPmhalLP8733RegulatorTable[regId].regulatorMap;
        /* There are 2 PMIC ICs which provide for the voltage rails on same
         * I2C lines. Depending on the regulator ID read which PMIC IC does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8733RegulatorTable[regId].i2cSlaveAddress;

        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNumber);
        if (PM_SUCCESS == status)
        {
            /*
             * If the Regulator is disabled, enable by setting the BUCK/LDO_EN
             * bit.
             */
            enabled = PmhalLP8733CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                PmhalLP8733ReadPhyAddr(i2cNumber, slaveAddr,
                                       (uint32_t) regulator->ctrlRegAddr,
                                       &value);
                value = value |
                        ((uint32_t) 1U << (uint32_t) regulator->ctrlEnShift);
                PmhalLP8733WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) regulator->ctrlRegAddr,
                                        value);

                enabled = PmhalLP8733CheckRegulatorEnabled(regId);
                if (FALSE == enabled)
                {
                    status = PM_FAIL;
                }
            }
        }
    }
    return status;
}

static pmErrCode_t PMHALLP8733DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNumber, slaveAddr;
    uint32_t    value = 0U;
    const pmhalLP8733RegulatorProp_t *regulator;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalLP8733RegulatorTable[regId].regulatorMap;
        /* There are 2 ICs which provide for the voltage rails on different
         * I2C lines. Depending on the regulator ID read which I2C line does
         * this correspond to.
         */
        i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLP8733RegulatorTable[regId].i2cSlaveAddress;

        /* Configure and enable PMIC communication bus. */
        status = PMHALPmicCommConfigure(i2cNumber);

        /* If the Regulator is enabled, disable by setting the voltage to 0U. */
        if (PM_SUCCESS == status)
        {
            if (TRUE == PmhalLP8733CheckRegulatorEnabled(regId))
            {
                PmhalLP8733ReadPhyAddr(i2cNumber, slaveAddr,
                                       (uint32_t) regulator->ctrlRegAddr,
                                       &value);
                value = value &
                        ~((uint32_t) 1U << (uint32_t) regulator->ctrlEnShift);
                PmhalLP8733WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) regulator->ctrlRegAddr,
                                        value);

                /* Check if the regulator is truly disabled */
                if (TRUE == PmhalLP8733CheckRegulatorEnabled(regId))
                {
                    status = PM_FAIL;
                }
            }
        }
    }

    return status;
}

static uint32_t PMHALLP8733GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    convVoltage  = 0U;
    uint32_t    internalVsel = 0U;

    status = PmhalLP8733VoltageToVselOffset(regId, avsVoltage, &internalVsel);
    if (PM_SUCCESS == status)
    {
        convVoltage = PmhalLP8733VselOffsetToVoltage(regId, internalVsel);
    }

    return convVoltage;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalLP8733CheckRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t enabled = FALSE;
    uint32_t ctrl    = 0U;
    uint8_t  i2cNumber, slaveAddr;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8733RegulatorProp_t *regulator =
        gPmhalLP8733RegulatorTable[regId].regulatorMap;
    i2cNumber = gPmhalLP8733RegulatorTable[regId].i2cInstanceNum;
    slaveAddr = gPmhalLP8733RegulatorTable[regId].i2cSlaveAddress;

    /* Read the regulator CTRL_STATUS and return the status. */
    if (PM_SUCCESS ==
        PmhalLP8733ReadPhyAddr(i2cNumber, slaveAddr,
                               (uint32_t) regulator->statRegAddr,
                               &ctrl))
    {
        if ((ctrl &
             ((uint32_t) 1U << (uint32_t) regulator->enStatShift)) !=
            (uint32_t) PMHAL_LP8733_STATUS_OFF)
        {
            enabled = TRUE;
        }
    }

    return enabled;
}

static pmErrCode_t PmhalLP8733VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    internalVsel = 0U;
    uint32_t    remainder;
    uint32_t    stepVoltage = 0U, minVoltageVsel = 0U, minVoltage = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8733RegulatorProp_t *regulator =
        gPmhalLP8733RegulatorTable[regId].regulatorMap;

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
            voltage = regulator->maxVolt;
            status  = PM_BADARGS;
        }
        else if (voltage < regulator->minVolt)
        {
            voltage = regulator->minVolt;
            status  = PM_BADARGS;
        }
        else
        {
            /* Nothing to do here */
            status = PM_SUCCESS;
        }

        if (PMHAL_LP8733_RTYPE_BUCK == regulator->type)
        {
            if ((voltage >= PMHAL_LP8733_BUCK_RANGE1_MIN_VOLTAGE) &&
                (voltage <= PMHAL_LP8733_BUCK_RANGE1_MAX_VOLTAGE))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE1_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE1;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE1_MIN_VSEL;
            }
            else if ((voltage >= PMHAL_LP8733_BUCK_RANGE2_MIN_VOLTAGE) &&
                     (voltage <= PMHAL_LP8733_BUCK_RANGE2_MAX_VOLTAGE))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE2_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE2;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE2_MIN_VSEL;
            }
            else if ((voltage >= PMHAL_LP8733_BUCK_RANGE3_MIN_VOLTAGE) &&
                     (voltage <= PMHAL_LP8733_BUCK_RANGE3_MAX_VOLTAGE))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE3_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE3;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE3_MIN_VSEL;
            }
            else
            {
                /* Should not enter here */
                status = PM_BADARGS;
            }
        }
        else
        {
            minVoltage     = regulator->minVolt;
            stepVoltage    = PMHAL_LP8733_LDO_STEP_VOLTAGE;
            minVoltageVsel = regulator->minVoltVsel;
        }
        /* +1 is added here to ensure the voltage would be higher than
         * requested when the voltage is not an exact multiple of step
         * voltage.
         */
        if (status == PM_SUCCESS)
        {
            remainder = (voltage - minVoltage) % stepVoltage;
            if (remainder > 0U)
            {
                internalVsel = ((voltage - minVoltage) / stepVoltage) +
                               minVoltageVsel + 1U;
            }
            else
            {
                internalVsel = ((voltage - minVoltage) / stepVoltage) +
                               minVoltageVsel;
            }
            *vsel = internalVsel;
        }
    }
    return status;
}

static uint32_t PmhalLP8733VselOffsetToVoltage(pmhalPrcmPmicRegulatorId_t regId,
                                               uint32_t                   vsel)
{
    uint32_t mv;
    uint32_t modVsel     = 0U;
    uint32_t stepVoltage = 0U, minVoltageVsel = 0U, minVoltage = 0U;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLP8733RegulatorProp_t *regulator =
        gPmhalLP8733RegulatorTable[regId].regulatorMap;

    modVsel = vsel;

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
        if (PMHAL_LP8733_RTYPE_BUCK == regulator->type)
        {
            if ((modVsel >= PMHAL_LP8733_BUCK_RANGE1_MIN_VSEL) &&
                (modVsel <= PMHAL_LP8733_BUCK_RANGE1_MAX_VSEL))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE1_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE1;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE1_MIN_VSEL;
            }
            else if ((modVsel >= PMHAL_LP8733_BUCK_RANGE2_MIN_VSEL) &&
                     (modVsel <= PMHAL_LP8733_BUCK_RANGE2_MAX_VSEL))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE2_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE2;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE2_MIN_VSEL;
            }
            else if ((modVsel >= PMHAL_LP8733_BUCK_RANGE3_MIN_VSEL) &&
                     (modVsel <= PMHAL_LP8733_BUCK_RANGE3_MAX_VSEL))
            {
                minVoltage     = PMHAL_LP8733_BUCK_RANGE3_MIN_VOLTAGE;
                stepVoltage    = PMHAL_LP8733_BUCK_STEP_VOLTAGE_RANGE3;
                minVoltageVsel = PMHAL_LP8733_BUCK_RANGE3_MIN_VSEL;
            }
            else
            {
                ; /* Should not enter here */
            }
        }
        else
        {
            minVoltage     = regulator->minVolt;
            stepVoltage    = PMHAL_LP8733_LDO_STEP_VOLTAGE;
            minVoltageVsel = regulator->minVoltVsel;
        }
        mv = minVoltage + (stepVoltage * (modVsel - minVoltageVsel));
    }
    /* To Convert to milli volt from 10 ^ (-4) volts*/
    mv = mv / 10U;

    return mv;
}

static pmErrCode_t PmhalLP8733ReadPhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
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
        slaveAddrInternal = slaveAddr;
        regAddr           = (uint8_t) phyAddr;
        status = PMHALPmicCommReadByte(i2cNumber,
                                       slaveAddrInternal, regAddr, &byte);
        *value = byte;
    }

    return status;
}

static pmErrCode_t PmhalLP8733WritePhyAddr(uint8_t i2cNumber, uint8_t slaveAddr,
                                           uint32_t phyAddr, uint32_t value)
{
    uint8_t     slaveAddrInternal;
    uint8_t     regAddr;
    uint8_t     byte;
    pmErrCode_t status;

    byte = (uint8_t) value;
    slaveAddrInternal = slaveAddr;
    regAddr           = (uint8_t) phyAddr;
    status = PMHALPmicCommWriteByte(i2cNumber,
                                    slaveAddrInternal, regAddr, byte);

    return status;
}

