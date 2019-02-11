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
 *  \file  pmhal_lp8731_lp3907.h
 *
 *  \brief The Power Management IC (PMIC) L8731 specific API definition.
 *
 *         The APIs defined here are to control the voltage of the
 *         PMIC rails and to query the status.
 */

#ifndef PM_LP8731_LP3907_H_
#define PM_LP8731_LP3907_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief I2C Address for LP8731 PMIC */
#define PMHAL_LP8731_LP3907_I2C_CHIP_ADDRESS_LP8731            (0x59U)

/** \brief I2C Address for LP3907 PMIC */
#define PMHAL_LP8731_LP3907_I2C_CHIP_ADDRESS_LP3907            (0x61U)

/** \brief I2C Address for LP8731 PMIC */
#define PMHAL_LP8731_LP3907_PMIC_TYPE_LP8731                   (0x0U)

/** \brief I2C Address for LP3907 PMIC */
#define PMHAL_LP8731_LP3907_PMIC_TYPE_LP3907                   (0x1U)

/** \brief I2C1 Line number to which the PMICs are connected */
#define PMHAL_LP8731_LP3907_I2C1_LINE_NUMBER                    (0x0U)

/** \brief I2C2 Line number to which the PMICs are connected */
#define PMHAL_LP8731_LP3907_I2C2_LINE_NUMBER                    (0x1U)

/** \brief Maximum Number of PMIC Revisions available */
#define PMHAL_PMIC_MAX_REV                   (4U)

/** \brief The BUCK LDO Status register BUCK 1 voltage OK shift. */
#define PMHAL_LP8731_LP3907_BKLDOSR_BK1_OK_SHIFT         (0U)

/** \brief The BUCK LDO Status register BUCK 1 voltage OK mask. */
#define PMHAL_LP8731_LP3907_BKLDOSR_BK1_OK_MASK          (1U)

/** \brief The BUCK LDO Status register BUCK 2 voltage OK shift. */
#define PMHAL_LP8731_LP3907_BKLDOSR_BK2_OK_SHIFT         (2U)

/** \brief The BUCK LDO Status register BUCK 2 voltage OK mask. */
#define PMHAL_LP8731_LP3907_BKLDOSR_BK2_OK_MASK          (4U)

/** \brief The BUCK LDO Status register LDO 1 voltage OK shift. */
#define PMHAL_LP8731_LP3907_BKLDOSR_LDO1_OK_SHIFT        (4U)

/** \brief The BUCK LDO Status register LDO 1 voltage OK mask. */
#define PMHAL_LP8731_LP3907_BKLDOSR_LDO1_OK_MASK         (0x10U)

/** \brief The BUCK LDO Status register LDO 2 voltage OK shift. */
#define PMHAL_LP8731_LP3907_BKLDOSR_LDO2_OK_SHIFT        (5U)

/** \brief The BUCK LDO Status register LDO 2 voltage OK mask. */
#define PMHAL_LP8731_LP3907_BKLDOSR_LDO2_OK_MASK         (0x20U)

/**
 * \brief The VCCR register BUCK 1 Ramp Control Shift.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK1_RAMP_CTRL_SHIFT   (0U)

/**
 * \brief The VCCR register BUCK 1 Ramp Control Mask.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK1_RAMP_CTRL_MASK    (1U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Shift.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK1_TARG_VOLT_SEL_SHIFT   (1U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Mask.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK1_TARG_VOLT_SEL_MASK    (2U)

/**
 * \brief The VCCR register BUCK 2 Ramp Control Shift.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK2_RAMP_CTRL_SHIFT   (4U)

/**
 * \brief The VCCR register BUCK 2 Ramp Control Mask.
 *         Program 0 to hold the voltage to its current value.
 *         Program 1 to ramp to the target voltage.
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK2_RAMP_CTRL_MASK    (0x10U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Shift.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK2_TARG_VOLT_SEL_SHIFT   (5U)

/**
 * \brief The VCCR register BUCK 1 Target Voltage Select Mask.
 *         Program 0 to ramp to voltage defined in Target Voltage register 1
 *         Program 1 to ramp to voltage defined in Target Voltage register 2
 */
#define PMHAL_LP8731_LP3907_VCCR_BUCK2_TARG_VOLT_SEL_MASK    (0x20U)

/** \brief Target Voltage Shift */
#define PMHAL_LP8731_LP3907_TARG_VOLT_SHIFT              (0U)
/** \brief Target Voltage Mask */
#define PMHAL_LP8731_LP3907_TARG_VOLT_MASK               (0x3FU)

/**
 * \brief Ramp Control register Shift. This determines the slew rate.
 *         Slew rate kept at default 8mv/us. Not programmed here.
 */
#define PMHAL_LP8731_LP3907_RAMP_CTRL_SHIFT               (0U)

/**
 * \brief Ramp Control register Mask. This determines the slew rate.
 *         Slew rate kept at default 8mv/us. Not programmed here.
 */
#define PMHAL_LP8731_LP3907_RAMP_CTRL_MASK                (0xFU)

/** \brief LDO voltage control register Shift. */
#define PMHAL_LP8731_LP3907_LDO_OUT_VOLT_SHIFT             (0U)

/** \brief LDO voltage control register Mask. */
#define PMHAL_LP8731_LP3907_LDO_OUT_VOLT_MASK              (0x1FU)

/** \brief Invalid Page Address */
#define PMHAL_LP8731_LP3907_SLAVE_ADDR_INVALID   (0xFFU)

/** \brief       Control Status Macro for Off */
#define PMHAL_LP8731_LP3907_STATUS_OFF                   (0U)

/** \brief Regulator Register Physical Addresses for BKLDOEN. */
#define PMHAL_LP8731_LP3907_BKLDOEN                 (0x10U)
/** \brief Regulator Register Physical Addresses for BKLDOSR. */
#define PMHAL_LP8731_LP3907_BKLDOSR                 (0x11U)
/** \brief Regulator Register Physical Addresses for BUCK_VCCR. */
#define PMHAL_LP8731_LP3907_BUCK_VCCR               (0x20U)
/** \brief Regulator Register Physical Addresses for B1TV1. */
#define PMHAL_LP8731_LP3907_B1TV1                   (0x23U)
/** \brief Regulator Register Physical Addresses for B1TV2. */
#define PMHAL_LP8731_LP3907_B1TV2                   (0x24U)
/** \brief Regulator Register Physical Addresses for B1RC. */
#define PMHAL_LP8731_LP3907_B1RC                    (0x25U)
/** \brief Regulator Register Physical Addresses for B2TV1. */
#define PMHAL_LP8731_LP3907_B2TV1                   (0x29U)
/** \brief Regulator Register Physical Addresses for B2TV2. */
#define PMHAL_LP8731_LP3907_B2TV2                   (0x2AU)
/** \brief Regulator Register Physical Addresses for B2RC. */
#define PMHAL_LP8731_LP3907_B2RC                    (0x2BU)
/** \brief Regulator Register Physical Addresses for LDO1VCR. */
#define PMHAL_LP8731_LP3907_LDO1VCR                 (0x39U)
/** \brief Regulator Register Physical Addresses for LDO2VCR. */
#define PMHAL_LP8731_LP3907_LDO2VCR                 (0x3AU)

/** \brief L8731 vendor ID LSB. */
#define PMHAL_LP8731_LP3907_PHYADDR_VENDOR_ID_LSB   (0x24FU)

/** \brief L8731 vendor ID MSB. */
#define PMHAL_LP8731_LP3907_PHYADDR_VENDOR_ID_MSB   (0x250U)

/** \brief L8731 Product ID LSB. */
#define PMHAL_LP8731_LP3907_PHYADDR_PRODUCT_ID_LSB  (0x251U)

/** \brief L8731 Product ID MSB. */
#define PMHAL_LP8731_LP3907_PHYADDR_PRODUCT_ID_MSB  (0x252U)

/** \brief Expected vendor ID values for L8731. */
#define PMHAL_LP8731_LP3907_VENDOR_ID            (0x0451U)

/** \brief Expected product ID values for L8731 1.0. */
#define PMHAL_LP8731_LP3907_1_0_PRODUCT_ID       (0x0917U)

/**
 * \brief L8731 device revision register physical address and the
 *        field definitions.
 */
#define PMHAL_LP8731_LP3907_PHYADDR_CHIP_REVISION_ID        (0x357U)

/** \brief Chip Revision ID mask */
#define PMHAL_LP8731_LP3907_CHIP_REVISION_ID_MASK          (0x0FU)

/** \brief Chip Revision ID Shift */
#define PMHAL_LP8731_LP3907_CHIP_REVISION_ID_SHIFT         (0x0U)

/** \brief Regulator Type for SMPS */
#define PMHAL_LP8731_LP3907_RTYPE_BUCK                (1U)

/** \brief Regulator Type for LDO */
#define PMHAL_LP8731_LP3907_RTYPE_LDO                 (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Abstract Enumeration for the Regulators.
 */
typedef enum pmhalLP8731LP3907RegulatorId
{
    PMHAL_LP8731_LP3907_REGULATOR_INVALID = (-(int32_t)1),
    /**< Invalid PMIC regulator ID */
    PMHAL_LP8731_LP3907_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator ID */
    PMHAL_LP8731_LP3907_REGULATOR_BUCK1 = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for LP8731/LP3907 BUCK 1 */
    PMHAL_LP8731_LP3907_REGULATOR_BUCK2 = 1,
    /**< Abstracted PMIC Regulator ID for LP8731/LP3907 BUCK 2 */
    PMHAL_LP8731_LP3907_REGULATOR_LDO1 = 2,
    /**< Abstracted PMIC Regulator ID for LP8731/LP3907 LDO 1 */
    PMHAL_LP8731_LP3907_REGULATOR_LDO2 = 3,
    /**< Abstracted PMIC Regulator ID for LP8731/LP3907 LDO 2 */
    PMHAL_LP8731_LP3907_REGULATOR_MAX =
        (PMHAL_LP8731_LP3907_REGULATOR_LDO2 + 1)
        /**< Maximum Abstracted PMIC Regulator ID */
} pmhalLP8731LP3907RegulatorId_t;

/**
 * \brief LP8731/LP3907 Regulator description structure
 */
typedef struct pmhalLP8731LP3907RegulatorProp
{
    uint32_t minVolt;
    /**< Minimum voltage supported by the regulator in 10^ (-4) V. */
    uint32_t maxVolt;
    /**< Maximum voltage supported by the regulator in 10^ (-4) V. */
    uint16_t stepVolt;
    /**< Step voltage in 10^ (-4) V. */
    uint8_t  type;
    /**< The regulator type namely PMHAL_LP8731_LP3907_SMPS or
     *PMHAL_LP8731_LP3907_LDO. */
    uint8_t  minVoltVsel;
    /**< VSEL value corresponding to the minVolt.*/
    uint8_t  maxVoltVsel;
    /**< VSEL value corresponding to the maxVolt.*/
    uint8_t  voltEnRegShift;
    /**< Buck/LDO Output Voltage Enable Register bit field shift */
    uint8_t  voltStatusRegShift;
    /**< Buck/LDO Output Voltage Status Register bit field shift */
    uint8_t  vccrRampCtrlShift;
    /**< Bit field to enable ramp to a given voltage */
    uint8_t  vccrTargetVoltSelShift;
    /**< Bit field to select the target voltage */
    uint8_t  voltageControlReg;
    /**< Address of the voltage control register */
} pmhalLP8731LP3907RegulatorProp_t;

/** \brief  Pointer to pmhalLP8731RegulatorProp_t structure.
 */
typedef const pmhalLP8731LP3907RegulatorProp_t *pmhalLP8731LP3907RegulatorPtr_t;

/** \brief  LP8731/LP3907 Regulator Map description structure. This is used
 *          for keeping track of the regulator connection to the I2C instance
 *          and PMIC device.
 */
typedef struct pmhalLP8731LP3907RegulatorMap
{
    pmhalLP8731LP3907RegulatorPtr_t regulatorMap;
    /**< Pointer to the regulator properties */
    uint8_t                         i2cInstanceNum;
    /**< SoC I2C instance number to which the regulator of the PMIC will be
     *   connected to.
     */
    uint8_t                         i2cSlaveAddress;
    /**< PMIC slave Address to which the regulator is connected to */
    uint8_t                         pmicType;
    /**< Flag to differentiate between LP8731 and LP3907 */
} pmhalLP8731LP3907RegulatorMap_t;

/** \brief Pointer to the structure pmhalLP8731LP3907RegulatorMap_t */
typedef pmhalLP8731LP3907RegulatorMap_t *const
pmhalLP8731LP3907RegulatorMapPtr_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/** Data structure to describe the properties for all the regulators. */
extern const pmhalLP8731LP3907RegulatorProp_t gPmhalLP8731LP3907Regulator[
    PMHAL_LP8731_LP3907_REGULATOR_MAX];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Get PMIC ops structure. All the other functions are accessed via
 *          function pointers whose array is exported by this function.
 *
 * \return  Return pointer to the PMIC ops structure.
 */
const pmhalPmicOperations_t *PMHALLP8731LP3907GetPMICOps(void);

/**
 * \brief The PMIC regulator output to the device input mapping can be
 *        different on different boards. This API can be used to provide
 *        a different mapping to the PMIC driver if the mapping does not
 *        match the default. Example table is shown below:
 *    ------------------------------------------------------------------------
 *    | Device voltage Rail            | Ptr to Regulator                    |
 *    ------------------------------------------------------------------------
 *    | PMHAL_PRCM_PMIC_REGULATOR_CORE | PMHAL_LP8731_LP3907_REGULATOR_BUCK1 |
 *    | PMHAL_PRCM_PMIC_REGULATOR_DSPEVE| PMHAL_LP8731_LP3907_REGULATOR_BUCK2|
 *    | ....                                                                 |
 *    | index (Refer                   | For index of the                    |
 *    | #pmhalPrcmPmicRegulatorId_t)   | gPmhalLP8731LP3907Regulator         |
 *    |                                | refer                               |
 *    |                                | #pmhalLP8731LP3907RegulatorId_t     |
 *    ------------------------------------------------------------------------
 *        This table when translated to code is as below:
 *        pmhalLP8731LP3907RegulatorMap_t regulatorMap[
 *          PMHAL_PRCM_PMIC_REGULATOR_COUNT] = {
 *              {
 *                  &gPmhalLP8731LP3907Regulator[
 *                      PMHAL_LP8731_LP3907_REGULATOR_BUCK1],
 *                  I2C_INSTANCE,
 *                  PMIC_I2C_SLAVE_ADDRESS
 *              },
 *              {
 *                  &gPmhalLP8731LP3907Regulator[
 *                      PMHAL_LP8731_LP3907_REGULATOR_BUCK2],
 *                  I2C_INSTANCE,
 *                  PMIC_I2C_SLAVE_ADDRESS
 *              },
 *               ......
 *          };
 *
 * \param   regulatorMap    Pointer to the array of pointers which gives the
 *                          mapping. The array is defined as above.
 *
 * \return  None
 */
void PMHALLP8731LP3907ConfigureRegulatorMap(
    pmhalLP8731LP3907RegulatorMapPtr_t regulatorMap);

#ifdef __cplusplus
}
#endif

#endif

