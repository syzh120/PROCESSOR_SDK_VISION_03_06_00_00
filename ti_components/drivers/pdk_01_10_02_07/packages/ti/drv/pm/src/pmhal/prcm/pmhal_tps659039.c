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
 * \file        pmhal_tps659039.c
 *
 * \brief       Power Management IC - TPS659039 specific API implementation.
 *              APIs are exported by using function pointers.
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
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#include "pmhal_pmicComm.h"

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
 * \brief   Check if the TPS659039 PMIC is present. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  PM_SUCCESS - TPS659039 PMIC is present.
 *          PM_PMHAL_PMIC_VENDOR_ID_INVALID - PMIC vendor id doesn't match the
 *                                     expected value.
 *          PM_PMHAL_PMIC_PRODUCT_ID_INVALID - PMIC product id doesn't match the
 *                                      expected value.
 */
static pmErrCode_t PMHALTps659039IsPresent(void);

/**
 * \brief   Get the TPS659039 PMIC chip revision. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  revString - The revision. "INVALID" is returned in case of error.
 */
static const char *PMHALTps659039GetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   vendorId    The Vendor ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALTps659039GetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   productId   The Product ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALTps659039GetProductId(uint32_t *productId);

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
static pmErrCode_t PMHALTps659039GetRegulatorVoltage(
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
static pmErrCode_t PMHALTps659039SetRegulatorVoltage(
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
static uint32_t    PMHALTps659039IsRegulatorEnabled(
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
static pmErrCode_t PMHALTps659039EnableRegulator(
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
static pmErrCode_t PMHALTps659039DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief   Return the Regulator Step voltage size. This is required by the
 *          voltage manager to understand the opp for the given voltage set for
 *          the given voltage rail.
 *
 * \param   regId       Regulator ID. Refer #pmhalPrcmPmicRegulatorId_t for
 *                      details.
 * \param   avsVolt     AVS voltage which is to be converted to regulator
 *                      voltage
 *
 * \return  convVolt    The voltage that would be supplied by the regulator if
 *                      the AVS voltage is given to the API.
 *                      NOTE: This API does not program the PMIC. It just
 *                      returns the calculated value of AVS voltage converted to
 *                      PMIC voltage based on the PMIC voltage resolution.
 */
static uint32_t PMHALTps659039GetRegulatorConvVoltage(
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
 * \param   range   Range of the VSEL voltage.
 * \param   vsel    VSEL value returned.
 *
 * \return  status
 */
static pmErrCode_t PmhalTps659039VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   range,
    uint32_t                  *vsel);

/**
 * \brief Given VSEL offset convert it to voltage in mV and return.
 *
 * \param   regId   Regulator Id. Refer Enum #pmhalPrcmPmicRegulatorId_t
 * \param   range   Range of the VSEL voltage.
 * \param   vsel    VSEL value returned.
 *
 * \return  voltage Voltage in mV.
 */
static uint32_t    PmhalTps659039VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   vsel,
    uint32_t                   range);

/**
 * \brief  Read the register value at the given physical address.
 *
 * \param   i2cNum      I2C instance number used to communicate with PMIC.
 * \param   phyAddr     Address to be read.
 * \param   value       Returns the value read.
 *
 * \return  status      Return PM_SUCCESS if read is successful. Else returns
 *                      PM_FAIL.
 */
static pmErrCode_t PmhalTps659039ReadPhyAddr(uint8_t i2cNum, uint32_t phyAddr,
                                             uint32_t *value);

/**
 * \brief  Write the given register value at the given physical address.
 *
 * \param   i2cNum      I2C instance number used to communicate with PMIC.
 * \param   phyAddr     Address to be written to.
 * \param   value       Returns the value to be written.
 *
 * \return Return success or failure.
 */
static pmErrCode_t PmhalTps659039WritePhyAddr(uint8_t i2cNum, uint32_t phyAddr,
                                              uint32_t value);

/**
 * \brief Check if the given product ID is the ID of a supported PMIC.
 *
 * \param       prodId  Product ID to be checked.
 *
 * \return true if the product ID is valid; false otherwise
 */
static uint32_t    PmhalTps659039IsProductIdValid(uint32_t prodId);

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
static uint32_t PmhalTps659039CheckRegulatorEnabled
    (pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief Function to convert the physical address to the slave address.
 *
 * \param   phyAddr     Physical Address
 * \return  slaveAddr   Slave Address
 */
static uint8_t PmhalTps659039PhytoSlaveAddr(uint32_t phyAddr);

/**
 * \brief In line function to find the Offset of a register address in a page.
 *
 * \param   phyAddr   Physical Address
 * \return  Page offset
 */
static uint8_t PmhalTps659039PhyToPageOffset(uint32_t phyAddr);

/**
 * \brief In line function to find the Offset of a register address in a page.
 *
 * \param   phyAddr   Physical Address
 * \return  Page Number
 */
static uint32_t PmhalTps659039PhyToPage(uint32_t phyAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Power Management IC device callbacks. */
const pmhalPmicOperations_t          gPmhalTps659039Ops =
{
    &PMHALTps659039IsPresent,               /* isPresent */
    &PMHALTps659039GetRevision,             /* getRevision */
    &PMHALTps659039GetVendorId,             /* getVendorId */
    &PMHALTps659039GetProductId,            /* getProductId */
    &PMHALTps659039IsRegulatorEnabled,      /* isRegulatorEnabled */
    &PMHALTps659039EnableRegulator,         /* regulatorEnable */
    &PMHALTps659039DisableRegulator,        /* regulatorDisable */
    &PMHALTps659039GetRegulatorVoltage,     /* regulatorGetVoltage */
    &PMHALTps659039SetRegulatorVoltage,     /* regulatorSetVoltage */
    &PMHALTps659039GetRegulatorConvVoltage, /* regulatorGetConvVoltage */
};

/* Data structure to describe the regulator for all the regulators. */
const pmhalTps659039RegulatorProp_t  gPmhalTps659039Regulator[
    PMHAL_TPS65039_REGULATOR_MAX] =
{
    /* PMHAL_TPS65039_REGULATOR_SMPS12 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS12_CTRL, PMHAL_TPS659039_SMPS12_VOLTAGE,
        PMHAL_TPS659039_SMPS12_FORCE
    },
    /* PMHAL_TPS65039_REGULATOR_SMPS3 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS3_CTRL, PMHAL_TPS659039_SMPS3_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_SMPS45 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS45_CTRL, PMHAL_TPS659039_SMPS45_VOLTAGE,
        PMHAL_TPS659039_SMPS45_FORCE
    },
    /* PMHAL_TPS659039_SMPS6 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS6_CTRL, PMHAL_TPS659039_SMPS6_VOLTAGE,
        PMHAL_TPS659039_SMPS6_FORCE
    },
    /* PMHAL_TPS65039_REGULATOR_SMPS7 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS7_CTRL, PMHAL_TPS659039_SMPS7_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_SMPS8 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS8_CTRL, PMHAL_TPS659039_SMPS8_VOLTAGE,
        PMHAL_TPS659039_SMPS8_FORCE
    },
    /* PMHAL_TPS65039_REGULATOR_SMPS9 */
    {
        500U, 1650U, 10U, PMHAL_TPS659039_RTYPE_SMPS, 2500U, 0x06U, 0x79U,
        PMHAL_TPS659039_SMPS9_CTRL, PMHAL_TPS659039_SMPS9_VOLTAGE,
        0x0
    },
    /* PMHAL_TPS65039_REGULATOR_LDO1 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO1_CTRL, PMHAL_TPS659039_LDO1_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO2 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO2_CTRL, PMHAL_TPS659039_LDO2_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO3 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO3_CTRL, PMHAL_TPS659039_LDO3_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO4 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO4_CTRL, PMHAL_TPS659039_LDO4_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO5 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO5_CTRL, PMHAL_TPS659039_LDO5_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO6 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO6_CTRL, PMHAL_TPS659039_LDO6_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO7 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO7_CTRL, PMHAL_TPS659039_LDO7_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO8 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO8_CTRL, PMHAL_TPS659039_LDO8_VOLTAGE,
        0x0U
    },
    /* PMHAL_TPS65039_REGULATOR_LDO9 */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDO9_CTRL, PMHAL_TPS659039_LDO9_VOLTAGE,
        0x0U
    },
    /*  PMHAL_TPS65039_REGULATOR_LDOLN */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDOLN_CTRL, PMHAL_TPS659039_LDOLN_VOLTAGE,
        0x0U
    },
    /*  PMHAL_TPS65039_REGULATOR_LDOUSB */
    {
        900U, 3300U, 50U, PMHAL_TPS659039_RTYPE_LDO, 2500U, 0x01U, 0x31U,
        PMHAL_TPS659039_LDOUSB_CTRL, PMHAL_TPS659039_LDOUSB_VOLTAGE,
        0x0U
    }
};

/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalTps659039RegulatorMap_t         gPmhalDefaultTps659039RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MPU */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_SMPS12],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_SMPS7],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_IVA */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_SMPS8],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_SMPS45],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_GPU */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_SMPS6],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_LDO1],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_SHV5 */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_LDO2],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_LDO3],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        &gPmhalTps659039Regulator[PMHAL_TPS65039_REGULATOR_LDON],
        (uint8_t) PMHAL_TPS659039_I2C_NUM_1
    }
};

/* Pointer to array of pointers describing the mapping from regulators to
 * device voltage rails.
 */
static pmhalTps659039RegulatorMap_t *gPmhalTps659039RegulatorTable =
    gPmhalDefaultTps659039RegulatorTable;

/*
 * PMIC uses different slave addresses to access different register
 *        pages. This table lists the page slave addresses.
 */
const uint8_t gPmhalTps659039SlaveAddressTable[
    PMHAL_TPS659039_SLAVE_ADDR_COUNT] =
{
    PMHAL_TPS659039_SLAVE_ADDR_PAGE0,
    PMHAL_TPS659039_SLAVE_ADDR_PAGE1,
    PMHAL_TPS659039_SLAVE_ADDR_PAGE2,
    PMHAL_TPS659039_SLAVE_ADDR_PAGE3,
    PMHAL_TPS659039_SLAVE_ADDR_PAGE4
};

/* Chip Revisions of the PMIC. */
const char   *gPmhalTps659039RevStrings[PMHAL_PMIC_MAX_REV] =
{"CS1.0", "CS2.0", "CS2.1", "CS2.2"};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalPmicOperations_t *PMHALTps659039GetPMICOps(void)
{
    return &gPmhalTps659039Ops;
}

void PMHALTps659039ConfigureRegulatorMap(
    pmhalTps659039RegulatorMapPtr_t regulatorMap)
{
    /* If the regulatorMap provided by the caller is NULL then the default
     * regulator map as present on TI EVMs is used.
     */
    if (NULL == regulatorMap)
    {
        gPmhalTps659039RegulatorTable = gPmhalDefaultTps659039RegulatorTable;
    }
    else
    {
        gPmhalTps659039RegulatorTable = regulatorMap;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PMHALTps659039GetVendorId(uint32_t *vendorId)
{
    uint32_t    lsb    = 0U;
    uint32_t    msb    = 0U;
    uint32_t    value  = 0U;
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNum;

    if (NULL == vendorId)
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum =
            gPmhalTps659039RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
            i2cInstanceNum;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNum);

        /*
         * Check the Vendor ID.
         */
        if (PM_SUCCESS == status)
        {
            status = PmhalTps659039ReadPhyAddr(
                i2cNum,
                (uint32_t)
                PMHAL_TPS659039_PHYADDR_VENDOR_ID_LSB,
                &value);
            lsb = (value & 0xFFU);
        }

        if (PM_SUCCESS == status)
        {
            status = PmhalTps659039ReadPhyAddr(
                i2cNum,
                (uint32_t)
                PMHAL_TPS659039_PHYADDR_VENDOR_ID_MSB,
                &value);
            msb = (value & 0xFFU);
        }

        if (PM_SUCCESS == status)
        {
            *vendorId = (msb << 8U) | lsb;
        }
        else
        {
            *vendorId = 0U;
        }
    }

    return status;
}

static pmErrCode_t PMHALTps659039GetProductId(uint32_t *productId)
{
    uint32_t    lsb    = 0U, msb = 0U;
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNum;

    if (NULL == productId)
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum =
            gPmhalTps659039RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
            i2cInstanceNum;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNum);

        /*
         * Read the LSB and MSB of the product ID.
         */
        if (PM_SUCCESS == status)
        {
            status = PmhalTps659039ReadPhyAddr(
                i2cNum,
                (uint32_t)
                PMHAL_TPS659039_PHYADDR_PRODUCT_ID_LSB,
                &lsb);
        }

        if (PM_SUCCESS == status)
        {
            status = PmhalTps659039ReadPhyAddr(
                i2cNum,
                (uint32_t)
                PMHAL_TPS659039_PHYADDR_PRODUCT_ID_MSB, &msb);
        }

        if (PM_SUCCESS == status)
        {
            *productId = ((uint32_t) msb << 8) | lsb;
        }
        else
        {
            *productId = 0U;
        }
    }

    return status;
}

static pmErrCode_t PMHALTps659039IsPresent(void)
{
    uint32_t    prodId = 0U, vendorId = 0U;
    pmErrCode_t status = PM_SUCCESS;

    /*
     * Check if the TPS659039 PMIC is present. This function
     * ensures that this specific PMIC is in the system by
     * reading and verifying the vendor ID and product ID.
     * Return success only if the vendor ID and product ID
     * matches the expected value.
     */

    /* Check the Vendor ID. */
    status = PMHALTps659039GetVendorId(&vendorId);

    /* Check the Product ID. */
    if (PMHAL_TPS659039_VENDOR_ID == vendorId)
    {
        status = PMHALTps659039GetProductId(&prodId);
        if (PM_SUCCESS == status)
        {
            if (PmhalTps659039IsProductIdValid(prodId) == FALSE)
            {
                status = PM_PMIC_PRODUCT_ID_INVALID;
            }
        }
    }
    else
    {
        status = PM_PMIC_VENDOR_ID_INVALID;
    }

    return status;
}

static const char *PMHALTps659039GetRevision(void)
{
    uint32_t    rev=0;
    const char *revString = "INVALID";
    pmErrCode_t status    = PM_SUCCESS;
    uint8_t     i2cNum;

    i2cNum =
        gPmhalTps659039RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
        i2cInstanceNum;
    /*
     * Configure and enable PMIC communication bus.
     */
    status = PMHALPmicCommConfigure(i2cNum);

    /*
     * Get the Chip Revision ID.
     */
    if (PM_SUCCESS == status)
    {
        status = PmhalTps659039ReadPhyAddr(
            i2cNum,
            (uint32_t)
            PMHAL_TPS659039_PHYADDR_CHIP_REVISION_ID, &rev);
    }

    if (PM_SUCCESS == status)
    {
        rev = HW_GET_FIELD(rev, PMHAL_TPS659039_CHIP_REVISION_ID);
        if (rev < PMHAL_PMIC_MAX_REV)
        {
            revString = gPmhalTps659039RevStrings[rev];
        }
    }

    return revString;
}

static pmErrCode_t PMHALTps659039GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    ctrl, force, volt;
    uint32_t    forceCmd = 0U;
    uint32_t    range    = 0U;
    uint32_t    vsel     = 0U;
    const pmhalTps659039RegulatorProp_t *regulator;
    uint8_t     i2cNum;

    if ((NULL == voltage) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalTps659039RegulatorTable[regId].regulatorMap;
        i2cNum    = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNum);

        if ((TRUE == PmhalTps659039CheckRegulatorEnabled(regId)) &&
            (PM_SUCCESS == status))
        {
            uint32_t ctrlRoofEn = 0U;

            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->ctrlRegAddr,
                                               &ctrl);

            /*
             * If CTRL.ROOF_FLOOR_EN bit is 0x0, the voltage is controlled by
             * the FORCE.CMD bit. If it is 0x1, the voltage is controlled by the
             * device resource pins. Since we want to set the voltage, proceed
             * only when the voltage is controlled by FORCE.CMD bit. So, return
             * error if CTRL.ROOF_FLOOR_EN bit is set to 1.
             *
             * Note: Note that we can override this bit to 0x0 and proceed but
             * we choose not to do this. The OTP will set it to 0x0 and if this
             * default value has been overwritten, let us not assume that we can
             * override it.
             */
            if (PM_SUCCESS == status)
            {
                ctrlRoofEn = HW_GET_FIELD(
                    ctrl,
                    PMHAL_TPS659039_SMPSxx_CTRL_ROOF_FLOOR_EN);

                if ((PMHAL_TPS659039_RTYPE_SMPS == regulator->type) &&
                    (1U == ctrlRoofEn))
                {
                    status = PM_REGULATOR_STATE_INVALID;
                }
            }
        }

        /*
         * If the regulator has the force register and if the FORCE.CMD bit is
         * set to 0x0, the pmic uses the voltage value in the FORCE.VSEL
         * register bits. Otherwise, the pmic uses the voltage value in the
         * VOLTAGE.VSEL bits. Read the FORCE.CMD bit to choose the right
         * register to program.
         */
        if ((0x0U != regulator->forceRegAddr) && (PM_SUCCESS == status))
        {
            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->forceRegAddr,
                                               &force);

            if (PM_SUCCESS == status)
            {
                forceCmd = HW_GET_FIELD(force,
                                        PMHAL_TPS659039_SMPSxx_FORCE_CMD);
            }
        }

        /*
         * Read the VOLTAGE register and determine the range. The range bit
         * determines the voltage range:
         *   0x0 - 0.5V to 1.65V
         *   0x1 - 1.0V to 3.3V
         * Note that this function reads the range and uses it to calculate the
         * right VSEL offset for the given voltage. It wont' change the range
         * value to suit the given voltage. If the range bit doesn't support
         * the input voltage an error is returned.
         */
        if ((PM_SUCCESS == status) &&
            (PMHAL_TPS659039_RTYPE_SMPS == regulator->type))
        {
            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->voltRegAddr,
                                               &volt);
            if (PM_SUCCESS == status)
            {
                range = HW_GET_FIELD(volt,
                                     PMHAL_TPS659039_SMPSxx_VOLTAGE_RANGE);
            }
        }

        /*
         * If FORCE.CMD is 0x0, read the VSEL value from FORCE.VSEL bits.
         */
        if (PM_SUCCESS == status)
        {
            if ((0x0U != regulator->forceRegAddr) && (0x0U == forceCmd))
            {
                status =
                    PmhalTps659039ReadPhyAddr(i2cNum, regulator->forceRegAddr,
                                              &force);
                vsel = HW_GET_FIELD(force, PMHAL_TPS659039_SMPSxx_FORCE_VSEL);
            }
            /*
             * If FORCE.CMD is 0x1, read the VSEL value to VOLTAGE.VSEL bits.
             */
            else
            {
                status =
                    PmhalTps659039ReadPhyAddr(i2cNum, regulator->voltRegAddr,
                                              &volt);
                if (PMHAL_TPS659039_RTYPE_SMPS == regulator->type)
                {
                    vsel = HW_GET_FIELD(volt,
                                        PMHAL_TPS659039_SMPSxx_VOLTAGE_VSEL);
                }
                else
                {
                    vsel = HW_GET_FIELD(volt,
                                        PMHAL_TPS659039_LDOxx_VOLTAGE_VSEL);
                }
            }
        }

        if (PM_SUCCESS == status)
        {
            *voltage = PmhalTps659039VselOffsetToVoltage(regId, vsel, range);
        }
        else
        {
            *voltage = 0U;
        }
    }

    return status;
}

static pmErrCode_t PMHALTps659039SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout)
{
    pmErrCode_t status   = PM_SUCCESS;
    uint32_t    ctrl     = 0U;
    uint32_t    force    = 0U, volt = 0U;
    uint32_t    forceCmd = 0U;
    uint32_t    range    = 0U;
    uint32_t    vsel     = 0U;
    const pmhalTps659039RegulatorProp_t *regulator;
    uint8_t     i2cNum;
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
        regulator = gPmhalTps659039RegulatorTable[regId].regulatorMap;
        i2cNum    = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNum);

        if (TRUE == PmhalTps659039CheckRegulatorEnabled(regId))
        {
            uint32_t ctrlRoofEn = 0U;

            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->ctrlRegAddr,
                                               &ctrl);

            /*
             * If CTRL.ROOF_FLOOR_EN bit is 0x0, the voltage is controlled by
             * the FORCE.CMD bit. If it is 0x1, the voltage is controlled by the
             * device resource pins. Since we want to set the voltage, proceed
             * only when the voltage is controlled by FORCE.CMD bit. So, return
             * error if CTRL.ROOF_FLOOR_EN bit is set to 1.
             *
             * Note: Note that we can override this bit to 0x0 and proceed but
             * we choose not to do this. The OTP will set it to 0x0 and if this
             * default value has been overwritten, let us not assume that we can
             * override it.
             */
            if (PM_SUCCESS == status)
            {
                ctrlRoofEn = HW_GET_FIELD(
                    ctrl,
                    PMHAL_TPS659039_SMPSxx_CTRL_ROOF_FLOOR_EN);

                if ((PMHAL_TPS659039_RTYPE_SMPS == regulator->type) &&
                    (1U == ctrlRoofEn))
                {
                    status = PM_REGULATOR_STATE_INVALID;
                }
            }
        }

        /*
         * If the FORCE.CMD bit is set to 0x0, the PMIC uses the voltage value
         * in the FORCE.VSEL register bits. Otherwise, the PMIC uses the voltage
         * value in the VOLTAGE.VSEL bits. Read the FORCE.CMD bit to choose
         * the right register to program.
         */
        if ((0x0U != regulator->forceRegAddr) && (PM_SUCCESS == status))
        {
            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->forceRegAddr,
                                               &force);
            if (PM_SUCCESS == status)
            {
                forceCmd = HW_GET_FIELD(force,
                                        PMHAL_TPS659039_SMPSxx_FORCE_CMD);
            }
        }

        /*
         * Read the VOLTAGE register and determine the range. The range bit
         * determines the voltage range:
         *   0x0 - 0.5V to 1.65V
         *   0x1 - 1.0V to 3.3V
         * Note that this function reads the range and uses it to calculate the
         * right VSEL offset for the given voltage. It wont' change the range
         * value to suit the given voltage. If the range bit doesn't support
         * the input voltage the range is appropriately updated.
         */
        range = 0U;
        if ((PM_SUCCESS == status) &&
            (PMHAL_TPS659039_RTYPE_SMPS == regulator->type))
        {
            status = PmhalTps659039ReadPhyAddr(i2cNum, regulator->voltRegAddr,
                                               &volt);
            if (PM_SUCCESS == status)
            {
                range = HW_GET_FIELD(volt, PMHAL_TPS659039_SMPSxx_VOLTAGE_RANGE);
                /* Apply correction to the range value if it is out of range */
                if ((voltage < 1000U) && (range == 1U))
                {
                    range = 0U;
                }
                else if ((voltage > 1650U) && (range == 0U))
                {
                    range = 1U;
                }
                else
                {
                    ; /* Do nothing */
                }
            }
        }

        /*
         * Convert the given voltage value to the VSEL offset; use the range
         * read above to convert the offset.
         */
        if (PM_SUCCESS == status)
        {
            status = PmhalTps659039VoltageToVselOffset(regId, voltage, range,
                                                       &vsel);
            if (PM_SUCCESS == status)
            {
                /*
                 * If FORCE.CMD is 0x0, write the VSEL value to FORCE.VSEL bits.
                 */
                if ((0x0U != regulator->forceRegAddr) && (0x0U == forceCmd))
                {
                    HW_SET_FIELD32(force, PMHAL_TPS659039_SMPSxx_FORCE_VSEL,
                                   vsel);
                    status =
                        PmhalTps659039WritePhyAddr(i2cNum,
                                                   regulator->forceRegAddr,
                                                   force);
                }
                /*
                 * If FORCE.CMD is 0x1, write the VSEL value to VOLTAGE.VSEL
                 * bits.
                 */
                else if (PMHAL_TPS659039_RTYPE_SMPS == regulator->type)
                {
                    HW_SET_FIELD32(volt, PMHAL_TPS659039_SMPSxx_VOLTAGE_VSEL,
                                   vsel);
                    HW_SET_FIELD32(volt, PMHAL_TPS659039_SMPSxx_VOLTAGE_RANGE,
                                   range);
                    status =
                        PmhalTps659039WritePhyAddr(i2cNum,
                                                   regulator->voltRegAddr,
                                                   volt);
                }
                else if (PMHAL_TPS659039_RTYPE_LDO == regulator->type)
                {
                    HW_SET_FIELD32(volt, PMHAL_TPS659039_LDOxx_VOLTAGE_VSEL,
                                   vsel);
                    status =
                        PmhalTps659039WritePhyAddr(i2cNum,
                                                   regulator->voltRegAddr,
                                                   volt);
                }
                else
                {
                    ; /* should not get here */
                }
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
            uint32_t newV = PmhalTps659039VselOffsetToVoltage(regId, vsel,
                                                              range);

            if (PM_TIMEOUT_INFINITE == timeout)
            {
                while (newV != currVolt)
                {
                    PMHALTps659039GetRegulatorVoltage(regId, &currVolt);
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
                    PMHALTps659039GetRegulatorVoltage(regId, &currVolt);
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

static uint32_t PMHALTps659039IsRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t    enabled = 0U;
    pmErrCode_t status  = PM_SUCCESS;
    uint8_t     i2cNum;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;
        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNum);
    }

    if (PM_SUCCESS == status)
    {
        enabled = (uint32_t) PmhalTps659039CheckRegulatorEnabled(regId);
    }

    return enabled;
}

static pmErrCode_t PMHALTps659039EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalTps659039RegulatorProp_t *regulator;
    uint32_t    value   = 0U;
    uint32_t    enabled = FALSE;
    uint8_t     i2cNum;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        regulator = gPmhalTps659039RegulatorTable[regId].regulatorMap;
        i2cNum    = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;

        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNum);
        if (PM_SUCCESS == status)
        {
            /*
             * If the Regulator is disabled, enable by setting the MODE_ACTIVE
             * and MODE_SLEEP to 0x01 (Forced PWM)
             */
            enabled = PmhalTps659039CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                if (PMHAL_TPS659039_RTYPE_SMPS == regulator->type)
                {
                    HW_SET_FIELD32(
                        value,
                        PMHAL_TPS659039_SMPSxx_CTRL_MODE_ACTIVE,
                        0x01U);
                    HW_SET_FIELD32(value,
                                   PMHAL_TPS659039_SMPSxx_CTRL_MODE_SLEEP,
                                   0x01U);
                    status =
                        PmhalTps659039WritePhyAddr(i2cNum,
                                                   regulator->ctrlRegAddr,
                                                   value);
                }
                else if (PMHAL_TPS659039_RTYPE_LDO == regulator->type)
                {
                    HW_SET_FIELD32(value,
                                   PMHAL_TPS659039_LDOxx_CTRL_MODE_ACTIVE,
                                   0x01U);
                    HW_SET_FIELD32(value,
                                   PMHAL_TPS659039_LDOxx_CTRL_MODE_SLEEP,
                                   0x01U);
                    status =
                        PmhalTps659039WritePhyAddr(i2cNum,
                                                   regulator->ctrlRegAddr,
                                                   value);
                }
                else
                {
                    ; /* Should not reach here */
                }
            }
            enabled = PmhalTps659039CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                status = PM_FAIL;
            }
        }
    }
    return status;
}

static pmErrCode_t PMHALTps659039DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNum;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;
        /* Configure and enable PMIC communication bus. */
        status = PMHALPmicCommConfigure(i2cNum);

        /* If the Regulator is enabled, disable by setting the voltage to 0U. */
        if (PM_SUCCESS == status)
        {
            if (PmhalTps659039CheckRegulatorEnabled(regId) == TRUE)
            {
                /*
                 * Setting the SMPS Voltage to 0U effectively disables the
                 * Regulator. The same is the case for LDO as well.
                 */
                PMHALTps659039SetRegulatorVoltage(regId, (uint32_t) 0U,
                                                  PM_TIMEOUT_INFINITE);

                /* Check if the regulator is truly disabled */
                if (TRUE == PmhalTps659039CheckRegulatorEnabled(regId))
                {
                    status = PM_FAIL;
                }
            }
        }
    }

    return status;
}

static uint32_t PMHALTps659039GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    convVoltage  = 0U;
    uint32_t    internalVsel = 0U;

    status = PmhalTps659039VoltageToVselOffset(regId, avsVoltage, (uint32_t) 0U,
                                               &internalVsel);
    if (PM_SUCCESS == status)
    {
        convVoltage = PmhalTps659039VselOffsetToVoltage(regId,
                                                        internalVsel,
                                                        (uint32_t) 0U);
    }
    return convVoltage;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalTps659039CheckRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t enabled = FALSE;
    uint32_t ctrl    = 0U;
    uint8_t  i2cNum;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalTps659039RegulatorProp_t *regulator =
        gPmhalTps659039RegulatorTable[regId].regulatorMap;

    i2cNum = gPmhalTps659039RegulatorTable[regId].i2cInstanceNum;

    /* Read the regulator CTRL_STATUS and return the status. */
    if (PM_SUCCESS ==
        PmhalTps659039ReadPhyAddr(i2cNum, regulator->ctrlRegAddr, &ctrl))
    {
        /*
         * Check if the regulator type is SMPS or LDO. Based on this check if
         * the regulator is enabled or not.
         */
        if (PMHAL_TPS659039_RTYPE_SMPS == regulator->type)
        {
            if (HW_GET_FIELD(ctrl,
                             PMHAL_TPS659039_SMPSxx_CTRL_STATUS) !=
                CTRL_STATUS_OFF)
            {
                enabled = TRUE;
            }
        }
        else if (PMHAL_TPS659039_RTYPE_LDO == regulator->type)
        {
            if (HW_GET_FIELD(ctrl,
                             PMHAL_TPS659039_LDOxx_CTRL_STATUS) !=
                CTRL_STATUS_OFF)
            {
                enabled = TRUE;
            }
        }
        else
        {
            ; /* Should not get here */
        }
    }

    return enabled;
}

static pmErrCode_t PmhalTps659039VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   range,
    uint32_t                  *vsel)
{
    pmErrCode_t status = PM_SUCCESS;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalTps659039RegulatorProp_t *regulator =
        gPmhalTps659039RegulatorTable[regId].regulatorMap;

    if (NULL == vsel)
    {
        status = PM_BADARGS;
    }
    else
    {
        /* Ensure range is 0U or 1. */
        range = range & 0x1U;

        /*
         * It is easier to operate on the non-range-adjusted voltage as we
         * keep the step, min/max volts in non-range-adjusted voltages.
         * Divide by the voltage by 2 if range is 0x1.
         */
        voltage = voltage >> range;

        if (0U == voltage)
        {
            *vsel = 0U;
        }
        else if (voltage > regulator->maxVolt)
        {
            *vsel  = regulator->maxVoltVsel;
            status = PM_BADARGS;
        }
        else
        {
            /* The vsel is always chosen to be greater than equal to the AVS
             * voltage.
             */
            *vsel = (((voltage - regulator->minVolt) +
                      (regulator->stepVolt - 1U)) / regulator->stepVolt) +
                    regulator->minVoltVsel;
        }
    }

    return status;
}

static uint32_t PmhalTps659039VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t vsel, uint32_t range)
{
    uint32_t mv;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalTps659039RegulatorProp_t *regulator =
        gPmhalTps659039RegulatorTable[regId].regulatorMap;

    /* Ensure range is 0U or 1. */
    range = range & 0x1U;

    if (0U == vsel)
    {
        mv = 0U;
    }
    else if (vsel <= regulator->minVoltVsel)
    {
        mv = regulator->minVolt;
    }
    else if (vsel >= regulator->maxVoltVsel)
    {
        mv = regulator->maxVolt;
    }
    else
    {
        mv = regulator->minVolt +
             (regulator->stepVolt * (vsel - regulator->minVoltVsel));
    }

    /* Apply range multiplier. */
    mv = mv << range;

    return mv;
}

static uint8_t PmhalTps659039PhytoSlaveAddr(uint32_t phyAddr)
{
    uint32_t page      = PmhalTps659039PhyToPage(phyAddr);
    uint8_t  slaveAddr = (uint8_t) PMHAL_TPS659039_SLAVE_ADDR_INVALID;

    if (page < PMHAL_TPS659039_SLAVE_ADDR_COUNT)
    {
        slaveAddr = gPmhalTps659039SlaveAddressTable[page];
    }

    return slaveAddr;
}

static pmErrCode_t PmhalTps659039ReadPhyAddr(uint8_t i2cNum, uint32_t phyAddr,
                                             uint32_t *value)
{
    uint8_t     slaveAddr;
    uint8_t     regAddr;
    pmErrCode_t status;
    uint8_t     byte;

    if (NULL == value)
    {
        status = PM_BADARGS;
    }
    else
    {
        byte      = (uint8_t) *value;
        slaveAddr = PmhalTps659039PhytoSlaveAddr(phyAddr);
        regAddr   = PmhalTps659039PhyToPageOffset(phyAddr);
        status    = PMHALPmicCommReadByte(i2cNum, slaveAddr, regAddr, &byte);
        *value    = byte;
    }

    return status;
}

static pmErrCode_t PmhalTps659039WritePhyAddr(uint8_t i2cNum, uint32_t phyAddr,
                                              uint32_t value)
{
    uint8_t     slaveAddr;
    uint8_t     regAddr;
    uint8_t     byte;
    pmErrCode_t status;

    byte      = (uint8_t) value;
    slaveAddr = PmhalTps659039PhytoSlaveAddr(phyAddr);
    regAddr   = PmhalTps659039PhyToPageOffset(phyAddr);
    status    = PMHALPmicCommWriteByte(i2cNum, slaveAddr, regAddr, byte);

    return status;
}

static uint32_t PmhalTps659039IsProductIdValid(uint32_t prodId)
{
    uint32_t prodIdValid = FALSE;
    /*
     * TDA2xx EVM can have PMIC v1.0 or v1.0 and the product ID
     * of these versions differ. Accept both the product IDs.
     */
    if ((PMHAL_TPS659039_1_0_PRODUCT_ID == prodId) ||
        (PMHAL_TPS659039_1_1_PRODUCT_ID == prodId))
    {
        prodIdValid = TRUE;
    }

    return prodIdValid;
}

static uint8_t PmhalTps659039PhyToPageOffset(uint32_t phyAddr)
{
    return (uint8_t) phyAddr;
}

static uint32_t PmhalTps659039PhyToPage(uint32_t phyAddr)
{
    return ((phyAddr) >> 8U);
}

