/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file        pmhal_lp87565.c
 *
 *  \brief       Power Management IC - LP87565 specific API implementation.
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
#include <ti/drv/pm/include/pmic/pmhal_lp87565.h>
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
 * \brief   Check if the LP87565 PMIC is present. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  PM_SUCCESS - LP87565 PMIC is present.
 *          PM_PMHAL_PMIC_VENDOR_ID_INVALID - PMIC vendor id doesn't match the
 *                                     expected value.
 *          PM_PMHAL_PMIC_PRODUCT_ID_INVALID - PMIC product id doesn't match the
 *                                      expected value.
 */
static pmErrCode_t PMHALLP87565IsPresent(void);

/**
 * \brief   Get the LP87565 PMIC chip revision. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   void
 *
 * \return  revString - The revision. "INVALID" is returned in case of error.
 */
static const char *PMHALLP87565GetRevision(void);

/**
 * \brief   Return the PMIC Vendor ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   vendorId    The Vendor ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP87565GetVendorId(uint32_t *vendorId);

/**
 * \brief   Return the PMIC Product ID. The declaration is present
 *          here to ensure this function is used only via function pointer.
 *
 * \param   productId   The Product ID is populated in this parameter.
 *
 * \return  status      PM_SUCCESS if API is a success. PM_BADARGS otherwise.
 */
static pmErrCode_t PMHALLP87565GetProductId(uint32_t *productId);

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
static pmErrCode_t PMHALLP87565GetRegulatorVoltage(
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
static pmErrCode_t PMHALLP87565SetRegulatorVoltage(
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
static uint32_t    PMHALLP87565IsRegulatorEnabled(
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
static pmErrCode_t PMHALLP87565EnableRegulator(
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
static pmErrCode_t PMHALLP87565DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId);

/**
 * \brief   Return the Regulator Step voltage size. This is required by the
 *          voltage manager to understand the opp for the given voltage set for
 *          the given voltage rail.
 *
 * \param   regId       Regulator ID. Refer #pmhalPrcmPmicRegulatorId_t for
 *                      details.
 * \param   avsVoltage  AVS voltage which is to be converted to regulator
 *                      voltage
 *
 * \return  convVolt    The voltage that would be supplied by the regulator if
 *                      the AVS voltage is given to the API.
 *                      NOTE: This API does not program the PMIC. It just
 *                      returns the calculated value of AVS voltage converted to
 *                      PMIC voltage based on the PMIC voltage resolution.
 */
static uint32_t PMHALLP87565GetRegulatorConvVoltage(
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
static pmErrCode_t PmhalLp87565VoltageToVselOffset(
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
static uint32_t    PmhalLp87565VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   vsel);

/**
 * \brief  Read the register value at the given physical address.
 *
 * \param   i2cNum      I2C Instance number to which the PMIC is connected
 * \param   i2cAddr     I2C Instance addr to which the PMIC is connected
 * \param   phyAddr     Address to be read.
 * \param   value       Returns the value read.
 *
 * \return  status      Return PM_SUCCESS if read is successful. Else returns
 *                      PM_FAIL.
 */
static pmErrCode_t PmhalLp87565ReadPhyAddr(uint8_t i2cNum, uint8_t i2cAddr, 
                                           uint32_t phyAddr,
                                           uint32_t *value);

/**
 * \brief  Write the given register value at the given physical address.
 *
 * \param   i2cNum      I2C Instance number to which the PMIC is connected
 * \param   i2cAddr     I2C Slave Address to which the PMIC is connected
 * \param   phyAddr     Address to be written to.
 * \param   value       Returns the value to be written.
 *
 * \return Return success or failure.
 */
static pmErrCode_t PmhalLp87565WritePhyAddr(uint8_t i2cNum,
                                            uint8_t i2cAddr,
                                            uint32_t phyAddr,
                                            uint32_t value);

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
static uint32_t PmhalLp87565CheckRegulatorEnabled
    (pmhalPrcmPmicRegulatorId_t regId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Power Management IC device callbacks. */
const pmhalPmicOperations_t         gPmhalLp87565Ops =
{
    &PMHALLP87565IsPresent,               /* isPresent */
    &PMHALLP87565GetRevision,             /* getRevision */
    &PMHALLP87565GetVendorId,             /* getVendorId */
    &PMHALLP87565GetProductId,            /* getProductId */
    &PMHALLP87565IsRegulatorEnabled,      /* isRegulatorEnabled */
    &PMHALLP87565EnableRegulator,         /* regulatorEnable */
    &PMHALLP87565DisableRegulator,        /* regulatorDisable */
    &PMHALLP87565GetRegulatorVoltage,     /* regulatorGetVoltage */
    &PMHALLP87565SetRegulatorVoltage,     /* regulatorSetVoltage */
    &PMHALLP87565GetRegulatorConvVoltage, /* regulatorGetConvVoltage */
};

/* Data structure to describe the regulator for all the regulators. */
const pmhalLp87565RegulatorProp_t  gPmhalLp87565Regulator[
    PMHAL_LP87565_REGULATOR_MAX] =
{
    /* PMHAL_LP87565_REGULATOR_BUCK_0  */
    {
        PMHAL_LP87565_REG_BUCK0_CTRL_1,
        PMHAL_LP87565_REG_BUCK0_VOUT,
        PMHAL_LP87565_REG_BUCK0_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_0_1_STAT,
        PMHAL_LP87565_BUCK0_STAT_SHIFT
    },
    /* PMHAL_LP87565_REGULATOR_BUCK_1  */
    {
        PMHAL_LP87565_REG_BUCK1_CTRL_1,
        PMHAL_LP87565_REG_BUCK1_VOUT,
        PMHAL_LP87565_REG_BUCK1_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_0_1_STAT,
        PMHAL_LP87565_BUCK1_STAT_SHIFT
    },
    /* PMHAL_LP87565_REGULATOR_BUCK_2  */
    {
        PMHAL_LP87565_REG_BUCK2_CTRL_1,
        PMHAL_LP87565_REG_BUCK2_VOUT,
        PMHAL_LP87565_REG_BUCK2_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_2_3_STAT,
        PMHAL_LP87565_BUCK2_STAT_SHIFT
    },
    /* PMHAL_LP87565_REGULATOR_BUCK_3  */
    {
        PMHAL_LP87565_REG_BUCK3_CTRL_1,
        PMHAL_LP87565_REG_BUCK3_VOUT,
        PMHAL_LP87565_REG_BUCK3_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_2_3_STAT,
        PMHAL_LP87565_BUCK3_STAT_SHIFT
    },
    /* PMHAL_LP87565_REGULATOR_BUCK_01 */
    {
        PMHAL_LP87565_REG_BUCK0_CTRL_1,
        PMHAL_LP87565_REG_BUCK0_VOUT,
        PMHAL_LP87565_REG_BUCK0_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_0_1_STAT,
        PMHAL_LP87565_BUCK0_STAT_SHIFT
    },
    /* PMHAL_LP87565_REGULATOR_BUCK_23 */
    {
        PMHAL_LP87565_REG_BUCK2_CTRL_1,
        PMHAL_LP87565_REG_BUCK2_VOUT,
        PMHAL_LP87565_REG_BUCK2_FLOOR_VOUT,
        PMHAL_LP87565_REG_BUCK_2_3_STAT,
        PMHAL_LP87565_BUCK2_STAT_SHIFT
    },
};

/* Table mapping from SMPS/LDO to Voltage Rails on the device */
pmhalLp87565RegulatorMap_t         gPmhalDefaultLp87565RegulatorTable[
    PMHAL_PRCM_PMIC_REGULATOR_COUNT] =
{
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MPU */
    {
        &gPmhalLp87565Regulator[PMHAL_LP87565_REGULATOR_BUCK_01],
        (uint8_t) PMHAL_LP87565_I2C_NUM,
        (uint8_t) PMHAL_LP87565_I2C_ADDR
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_CORE */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_IVA */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_DSPEVE */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_GPU */
    {
        &gPmhalLp87565Regulator[PMHAL_LP87565_REGULATOR_BUCK_23],
        (uint8_t) PMHAL_LP87565_I2C_NUM,
        (uint8_t) PMHAL_LP87565_I2C_ADDR
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_MMC13V3 */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_SHV5 */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PHY */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
    /* HW Regulator for PMHAL_PRCM_PMIC_REGULATOR_1V8PLL */
    {
        NULL,
        (uint8_t) 0,
        (uint8_t) 0
    },
};

/* Pointer to array of pointers describing the mapping from regulators to
 * device voltage rails.
 */
static pmhalLp87565RegulatorMap_t *gPmhalLp87565RegulatorTable =
    gPmhalDefaultLp87565RegulatorTable;

/* Chip Revisions of the PMIC. */
const char *gPmhalLp87565RevStrings[PMHAL_PMIC_MAX_REV] =
{"DEVID_00", "DEVID_01", "DEVID_10", "DEVID_11"};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalPmicOperations_t *PMHALLP87565GetPMICOps(void)
{
    return &gPmhalLp87565Ops;
}

void PMHALLP87565ConfigureRegulatorMap(
    pmhalLp87565RegulatorMapPtr_t regulatorMap)
{
    /* If the regulatorMap provided by the caller is NULL then the default
     * regulator map as present on TI EVMs is used.
     */
    if (NULL == regulatorMap)
    {
        gPmhalLp87565RegulatorTable = gPmhalDefaultLp87565RegulatorTable;
    }
    else
    {
        gPmhalLp87565RegulatorTable = regulatorMap;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PMHALLP87565GetVendorId(uint32_t *vendorId)
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
        *vendorId = PMHAL_LP87565_VENDOR_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP87565GetProductId(uint32_t *productId)
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
        *productId = PMHAL_LP87565_1_0_PRODUCT_ID;
    }

    return status;
}

static pmErrCode_t PMHALLP87565IsPresent(void)
{
    pmErrCode_t status = PM_SUCCESS;

    /*
     * Dummy Function always returns success.
     */
    return status;
}

static const char *PMHALLP87565GetRevision(void)
{
    uint32_t    rev = 0U;
    const char *revString = "INVALID";
    pmErrCode_t status    = PM_SUCCESS;
    uint8_t     i2cNum    =
        gPmhalLp87565RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
        i2cInstanceNum;
    uint8_t     i2cAddr   =
        gPmhalLp87565RegulatorTable[PMHAL_PRCM_PMIC_REGULATOR_MIN].
        i2cAddr;

    /*
     * Configure and enable PMIC communication bus.
     */
    status = PMHALPmicCommConfigure(i2cNum);

    /*
     * Get the Chip Revision ID.
     */
    if (PM_SUCCESS == status)
    {
        status = PmhalLp87565ReadPhyAddr(
            i2cNum, i2cAddr,
            (uint32_t)
            PMHAL_LP87565_REG_DEV_REV, &rev);
    }

    if (PM_SUCCESS == status)
    {
        rev = HW_GET_FIELD(rev, PMHAL_LP87565_DEV_REV_DEV_ID);
        revString = gPmhalLp87565RevStrings[rev];
    }

    return revString;
}

static pmErrCode_t PMHALLP87565GetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                  *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    vsel     = 0U;
    const pmhalLp87565RegulatorProp_t *regulator;
    uint8_t     i2cNum, i2cAddr;

    if ((NULL == voltage) || (regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum    = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
        i2cAddr   = gPmhalLp87565RegulatorTable[regId].i2cAddr;
        regulator = gPmhalLp87565RegulatorTable[regId].regulatorMap;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNum);

        if ((TRUE == PmhalLp87565CheckRegulatorEnabled(regId)) &&
            (PM_SUCCESS == status))
        {
            status = PmhalLp87565ReadPhyAddr(i2cNum, i2cAddr,
                                             regulator->voltRegAddr,
                                             &vsel);
        }
        else
        {
            status = PM_REGULATOR_STATE_INVALID;
        }

        if (PM_SUCCESS == status)
        {
            *voltage = PmhalLp87565VselOffsetToVoltage(regId, vsel);
        }
        else
        {
            *voltage = 0U;
        }
    }

    return status;
}

static pmErrCode_t PMHALLP87565SetRegulatorVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                   timeout)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    vsel   = 0U;
    const pmhalLp87565RegulatorProp_t *regulator;
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
        regulator = gPmhalLp87565RegulatorTable[regId].regulatorMap;
        /* There are 2 PMIC ICs which provide for the voltage rails on same
         * I2C lines. Depending on the regulator ID read which PMIC IC does
         * this correspond to.
         */
        i2cNumber = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
        slaveAddr = gPmhalLp87565RegulatorTable[regId].i2cAddr;
        /*
         * Configure and enable PMIC communication bus.
         */
        status = PMHALPmicCommConfigure(i2cNumber);
        if (PM_SUCCESS == status)
        {
            status = PMHALLP87565EnableRegulator(regId);
            if (TRUE == PmhalLp87565CheckRegulatorEnabled(regId))
            {
                PmhalLp87565VoltageToVselOffset(regId, voltage, &vsel);
                /* For Buck just configure the voltage. */
                PmhalLp87565WritePhyAddr(i2cNumber, slaveAddr,
                                        (uint32_t) regulator->voltRegAddr,
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
            uint32_t newV = PmhalLp87565VselOffsetToVoltage(regId, vsel);

            if (PM_TIMEOUT_INFINITE == timeout)
            {
                while (newV != currVolt)
                {
                    PMHALLP87565GetRegulatorVoltage(regId, &currVolt);
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
                    PMHALLP87565GetRegulatorVoltage(regId, &currVolt);
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

static uint32_t PMHALLP87565IsRegulatorEnabled(
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
        i2cNum = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNum);
    }

    if (PM_SUCCESS == status)
    {
        enabled = (uint32_t) PmhalLp87565CheckRegulatorEnabled(regId);
    }

    return enabled;
}

static pmErrCode_t PMHALLP87565EnableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalLp87565RegulatorProp_t *regulator;
    uint32_t    value   = 0U;
    uint32_t    enabled = FALSE;
    uint8_t     i2cNum, i2cAddr;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum    = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
        regulator = gPmhalLp87565RegulatorTable[regId].regulatorMap;
        i2cAddr = gPmhalLp87565RegulatorTable[regId].i2cAddr;

        /* Configure and enable PMIC communication bus.  */
        status = PMHALPmicCommConfigure(i2cNum);
        if (PM_SUCCESS == status)
        {
            /*
             * If the Regulator is disabled, enable it
             */
            enabled = PmhalLp87565CheckRegulatorEnabled(regId);
            if (FALSE == enabled)
            {
                status =
                        PmhalLp87565ReadPhyAddr(i2cNum, i2cAddr,
                                                  regulator->ctrlRegAddr,
                                                  &value);
                if (PM_SUCCESS == status)
                {
                    value = (uint32_t)value |
                            (uint32_t)((uint32_t)1U <<
                            (uint32_t)PMHAL_LP87565_BUCK_CTRL_1_EN_SHIFT);
                    status =
                            PmhalLp87565WritePhyAddr(i2cNum, i2cAddr,
                                                    regulator->ctrlRegAddr,
                                                    value);
                }
                if (PM_SUCCESS == status)
                {
                    enabled = PmhalLp87565CheckRegulatorEnabled(regId);
                    if (FALSE == enabled)
                    {
                        status = PM_FAIL;
                    }
                }
            }
        }
    }
    return status;
}

static pmErrCode_t PMHALLP87565DisableRegulator(
    pmhalPrcmPmicRegulatorId_t regId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint8_t     i2cNum, i2cAddr;
    const pmhalLp87565RegulatorProp_t *regulator;
    uint32_t value;

    if ((regId >= PMHAL_PRCM_PMIC_REGULATOR_COUNT) ||
        (regId < PMHAL_PRCM_PMIC_REGULATOR_MIN))
    {
        status = PM_BADARGS;
    }
    else
    {
        i2cNum = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
        i2cAddr = gPmhalLp87565RegulatorTable[regId].i2cAddr;
        regulator = gPmhalLp87565RegulatorTable[regId].regulatorMap;
        /* Configure and enable PMIC communication bus. */
        status = PMHALPmicCommConfigure(i2cNum);

        /* If the Regulator is enabled, disable by setting the voltage to 0U. */
        if (PM_SUCCESS == status)
        {
            if (TRUE == PmhalLp87565CheckRegulatorEnabled(regId))
            {
                PmhalLp87565ReadPhyAddr(i2cNum, i2cAddr,
                                       (uint32_t) regulator->ctrlRegAddr,
                                       &value);
                value = value &
                        ~((uint32_t) 1U << PMHAL_LP87565_BUCK_CTRL_1_EN_SHIFT);
                PmhalLp87565WritePhyAddr(i2cNum, i2cAddr,
                                        (uint32_t) regulator->ctrlRegAddr,
                                        value);

                /* Check if the regulator is truly disabled */
                if (TRUE == PmhalLp87565CheckRegulatorEnabled(regId))
                {
                    status = PM_FAIL;
                }
            }
        }
    }

    return status;
}

static uint32_t PMHALLP87565GetRegulatorConvVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   avsVoltage)
{
    pmErrCode_t status       = PM_SUCCESS;
    uint32_t    convVoltage  = 0U;
    uint32_t    internalVsel = 0U;

    status = PmhalLp87565VoltageToVselOffset(regId, avsVoltage, 
                                             &internalVsel);
    if (PM_SUCCESS == status)
    {
        convVoltage = PmhalLp87565VselOffsetToVoltage(regId,
                                                       internalVsel);
    }

    return convVoltage;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalLp87565CheckRegulatorEnabled(
    pmhalPrcmPmicRegulatorId_t regId)
{
    uint32_t enabled = FALSE;
    uint32_t status    = 0U;
    uint8_t  i2cNum, i2cAddr;
    /*
     * regId checks are not done here as this is an internal function and
     * the check would have happened before calling this function.
     */
    const pmhalLp87565RegulatorProp_t *regulator =
        gPmhalLp87565RegulatorTable[regId].regulatorMap;

    i2cNum = gPmhalLp87565RegulatorTable[regId].i2cInstanceNum;
    i2cAddr = gPmhalLp87565RegulatorTable[regId].i2cAddr;

    /* Read the regulator CTRL_STATUS and return the status. */
    if (PM_SUCCESS ==
        PmhalLp87565ReadPhyAddr(i2cNum, i2cAddr, regulator->statusRegAddr, &status))
    {
        /* Check if the regulator is enabled or not. */
        if ((uint32_t)(status &
            (uint32_t)((uint32_t)1U << (uint32_t)regulator->enStatShift)) !=
            (uint32_t)0U)
        {
            enabled = TRUE;
        }
    }
    return enabled;
}

static pmErrCode_t PmhalLp87565VoltageToVselOffset(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t                   voltage,
    uint32_t                  *vsel)
{
    pmErrCode_t status = PM_SUCCESS;

    if (NULL == vsel)
    {
        status = PM_BADARGS;
    }
    else
    {
        if (0U == voltage)
        {
            *vsel = 0U;
        }
        else if ((voltage >= 500U) && (voltage < 735U))
        {
            *vsel = (voltage - 500U)/10U;
        }
        else if ((voltage >= 735U) && (voltage < 1420U))
        {
            *vsel = ((voltage - 735U)/5U) + 0x18U;
        }
        else if ((voltage >= 1420U) && (voltage < 3360U))
        {
            *vsel = ((voltage - 1420U)/20U) + 0x9EU;
        }
        else
        {
            *vsel = 0U;
            status = PM_BADARGS;
        }
    }

    return status;
}

static uint32_t PmhalLp87565VselOffsetToVoltage(
    pmhalPrcmPmicRegulatorId_t regId,
    uint32_t vsel)
{
    uint32_t mv;

    if (vsel < 0x18U)
    {
        mv = 500U + (10U * vsel);
    }
    else if (vsel < 0x9EU)
    {
        mv = 735U + (5U * (vsel - 0x18U));
    }
    else if (vsel <= 0xFFU)
    {
        mv = 1420U + (20U * (vsel - 0x9EU));
    }
    else
    {
        mv = 0U;
    }

    return mv;
}

static pmErrCode_t PmhalLp87565ReadPhyAddr(uint8_t i2cNum, uint8_t i2cAddr,
                                           uint32_t phyAddr,
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
        slaveAddr = i2cAddr;
        regAddr   = (uint8_t) (phyAddr & 0xFFU);
        status    = PMHALPmicCommReadByte(i2cNum, slaveAddr, regAddr, &byte);
        *value    = (uint32_t) byte;
    }

    return status;
}

static pmErrCode_t PmhalLp87565WritePhyAddr(uint8_t i2cNum, uint8_t i2cAddr,
                                            uint32_t phyAddr,
                                            uint32_t value)
{
    uint8_t     slaveAddr;
    uint8_t     regAddr;
    uint8_t     byte;
    pmErrCode_t status;

    byte      = (uint8_t) value;
    slaveAddr = i2cAddr;
    regAddr   = (uint8_t) (phyAddr & 0xFFU);
    status    = PMHALPmicCommWriteByte(i2cNum, slaveAddr, regAddr, byte);

    return status;
}

