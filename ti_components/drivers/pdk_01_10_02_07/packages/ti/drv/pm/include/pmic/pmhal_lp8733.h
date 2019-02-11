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
 *  \file  pmhal_lp8733.h
 *
 *  \brief The Power Management IC (PMIC) LP8733 specific API definition.
 *
 *         The APIs defined here are to control the voltage of the
 *         PMIC rails and to query the status.
 */

#ifndef PM_LP8733_H_
#define PM_LP8733_H_

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

/** \brief The I2C line on which the PMICs are present */
#define PMHAL_LP8733_I2C_NUMBER               (0x0U)

/** \brief The PMIC number to which the voltage rail is connected */
#define PMHAL_LP8733_IC_NUM_1                 (0x0U)

/** \brief The PMIC number to which the voltage rail is connected */
#define PMHAL_LP8733_IC_NUM_2                 (0x1U)

/** \brief Chip Address 1 of the LP8733/32 PMIC ICs */
#define PMHAL_LP8733_CHIP_ADDRESS_1             (0x60U)
/** \brief Chip Address 2 of the LP8733/32 PMIC ICs */
#define PMHAL_LP8733_CHIP_ADDRESS_2             (0x61U)

/** \brief Maximum Number of PMIC Revisions available */
#define PMHAL_PMIC_MAX_REV                   (4U)

/** \brief The BUCK LDO Status register BUCK 1 voltage OK shift. */
#define PMHAL_LP8733_BUCK_CTRL_BUCK_EN_SHIFT         (0x0U)
/** \brief The BUCK LDO Status register BUCK 1 voltage OK mask. */
#define PMHAL_LP8733_BUCK_CTRL_BUCK_EN_MASK          (0x1U)

/** \brief The LDO CTRL register LDO_EN Shift */
#define PMHAL_LP8733_LDO_CTRL_LDO_EN_SHIFT            (0x0U)
/** \brief The LDO CTRL register LDO_EN Mask */
#define PMHAL_LP8733_LDO_CTRL_LDO_EN_MASK             (0x1U)

/** \brief The BUCK STAT register BUCK0_EN Shift */
#define PMHAL_LP8733_BUCK_STAT_BUCK0_STAT_SHIFT       (0x3U)
/** \brief The BUCK STAT register BUCK0_EN Mask */
#define PMHAL_LP8733_BUCK_STAT_BUCK0_STAT_MASK        (0x8U)

/** \brief The BUCK STAT register BUCK0_PG Shift */
#define PMHAL_LP8733_BUCK_STAT_BUCK0_PG_STAT_SHIFT    (0x2U)
/** \brief The BUCK STAT register BUCK0_PG Mask */
#define PMHAL_LP8733_BUCK_STAT_BUCK0_PG_STAT_MASK     (0x4U)

/** \brief The BUCK STAT register BUCK1_EN Shift */
#define PMHAL_LP8733_BUCK_STAT_BUCK1_STAT_SHIFT       (0x7U)
/** \brief The BUCK STAT register BUCK1_EN Mask */
#define PMHAL_LP8733_BUCK_STAT_BUCK1_STAT_MASK        (0x80U)

/** \brief The BUCK STAT register BUCK1_PG Shift */
#define PMHAL_LP8733_BUCK_STAT_BUCK1_PG_STAT_SHIFT    (0x6U)
/** \brief The BUCK STAT register BUCK1_PG Mask */
#define PMHAL_LP8733_BUCK_STAT_BUCK1_PG_STAT_MASK     (0x40U)

/** \brief The LDO STAT register LDO0_EN Shift */
#define PMHAL_LP8733_LDO_STAT_LDO0_STAT_SHIFT         (0x3U)
/** \brief The LDO STAT register LDO0_EN Mask */
#define PMHAL_LP8733_LDO_STAT_LDO0_STAT_MASK          (0x8U)

/** \brief The LDO STAT register LDO0_PG Shift */
#define PMHAL_LP8733_LDO_STAT_LDO0_PG_STAT_SHIFT      (0x2U)
/** \brief The LDO STAT register LDO0_PG Mask */
#define PMHAL_LP8733_LDO_STAT_LDO0_PG_STAT_MASK       (0x4U)

/** \brief The LDO STAT register LDO1_EN Shift */
#define PMHAL_LP8733_LDO_STAT_LDO1_STAT_SHIFT         (0x7U)
/** \brief The LDO STAT register LDO1_EN Mask */
#define PMHAL_LP8733_LDO_STAT_LDO1_STAT_MASK          (0x80U)

/** \brief The LDO STAT register LDO1_PG Shift */
#define PMHAL_LP8733_LDO_STAT_LDO1_PG_STAT_SHIFT      (0x6U)
/** \brief The LDO STAT register LDO1_PG Mask */
#define PMHAL_LP8733_LDO_STAT_LDO1_PG_STAT_MASK       (0x40U)

/** \brief The Device ID shift */
#define PMHAL_LP8733_DEV_REV_DEVICE_ID_SHIFT          (0x6U)
/** \brief The Device ID Mask */
#define PMHAL_LP8733_DEV_REV_DEVICE_ID_MASK           (0xC0U)

/** \brief Regulator Register DEV_REV Address. */
#define PMHAL_LP8733_DEV_REV                 (0x00U)
/** \brief Regulator Register OTP_REV Address. */
#define PMHAL_LP8733_OTP_REV                 (0x01U)
/** \brief Regulator Register BUCK0_CTRL_1 Address. */
#define PMHAL_LP8733_BUCK0_CTRL_1            (0x02U)
/** \brief Regulator Register BUCK0_CTRL_2 Address. */
#define PMHAL_LP8733_BUCK0_CTRL_2            (0x03U)
/** \brief Regulator Register BUCK1_CTRL_1 Address. */
#define PMHAL_LP8733_BUCK1_CTRL_1            (0x04U)
/** \brief Regulator Register BUCK1_CTRL_2 Address. */
#define PMHAL_LP8733_BUCK1_CTRL_2            (0x05U)
/** \brief Regulator Register BUCK0_VOUT Address. */
#define PMHAL_LP8733_BUCK0_VOUT              (0x06U)
/** \brief Regulator Register BUCK1_VOUT Address. */
#define PMHAL_LP8733_BUCK1_VOUT              (0x07U)
/** \brief Regulator Register LDO0_CTRL Address. */
#define PMHAL_LP8733_LDO0_CTRL               (0x08U)
/** \brief Regulator Register LDO1_CTRL Address. */
#define PMHAL_LP8733_LDO1_CTRL               (0x09U)
/** \brief Regulator Register LDO0_VOUT Address. */
#define PMHAL_LP8733_LDO0_VOUT               (0x0AU)
/** \brief Regulator Register LDO1_VOUT Address. */
#define PMHAL_LP8733_LDO1_VOUT               (0x0BU)
/** \brief Regulator Register BUCK_STAT Address. */
#define PMHAL_LP8733_BUCK_STAT               (0x1EU)
/** \brief Regulator Register LDO_STAT Address. */
#define PMHAL_LP8733_LDO_STAT                (0x1FU)

/** \brief LP8733 vendor ID LSB. */
#define PMHAL_LP8733_PHYADDR_VENDOR_ID_LSB   (0x24FU)

/** \brief LP8733 vendor ID MSB. */
#define PMHAL_LP8733_PHYADDR_VENDOR_ID_MSB   (0x250U)

/** \brief LP8733 Product ID LSB. */
#define PMHAL_LP8733_PHYADDR_PRODUCT_ID_LSB  (0x251U)

/** \brief LP8733 Product ID MSB. */
#define PMHAL_LP8733_PHYADDR_PRODUCT_ID_MSB  (0x252U)

/** \brief Expected vendor ID values for LP8733. */
#define PMHAL_LP8733_VENDOR_ID            (0x0451U)

/** \brief Expected product ID values for LP8733 1.0. */
#define PMHAL_LP8733_1_0_PRODUCT_ID       (0x0917U)

/**
 * \brief LP8733 device revision register physical address and the
 *        field definitions.
 */
#define PMHAL_LP8733_PHYADDR_CHIP_REVISION_ID        (0x357U)

/** \brief Chip Revision ID mask */
#define PMHAL_LP8733_CHIP_REVISION_ID_MASK          (0x0FU)

/** \brief Chip Revision ID Shift */
#define PMHAL_LP8733_CHIP_REVISION_ID_SHIFT         (0x0U)

/** \brief Regulator Type for SMPS */
#define PMHAL_LP8733_RTYPE_BUCK                (1U)

/** \brief Regulator Type for LDO */
#define PMHAL_LP8733_RTYPE_LDO                 (2U)

/** \brief Macro defining whether the LP8733 regulator is off */
#define PMHAL_LP8733_STATUS_OFF                 (0x0U)
/** \brief Macro defining whether the LP8733 regulator is on */
#define PMHAL_LP8733_STATUS_ON                  (0x1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Abstract Enumeration for the Regulators.
 */
typedef enum pmhalLP8733RegulatorId
{
    PMHAL_LP8733_REGULATOR_INVALID = (-(int32_t)1),
    /**< Invalid PMIC regulator ID */
    PMHAL_LP8733_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator ID */
    PMHAL_LP8733_REGULATOR_BUCK1 = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for LP8733 BUCK 1 */
    PMHAL_LP8733_REGULATOR_BUCK2 = 1,
    /**< Abstracted PMIC Regulator ID for LP8733 BUCK 2 */
    PMHAL_LP8733_REGULATOR_LDO1 = 2,
    /**< Abstracted PMIC Regulator ID for LP8733 LDO 1 */
    PMHAL_LP8733_REGULATOR_LDO2 = 3,
    /**< Abstracted PMIC Regulator ID for LP8733 LDO 2 */
    PMHAL_LP8733_REGULATOR_MAX = (PMHAL_LP8733_REGULATOR_LDO2 + 1)
                                 /**< Maximum Abstracted PMIC Regulator ID */
} pmhalLP8733RegulatorId_t;

/**
 * \brief LP8733 Regulator description structure
 */
typedef struct pmhalLP8733RegulatorProp
{
    uint16_t minVolt;
    /**< Minimum voltage supported by the regulator in 10^ (-4) V. */
    uint16_t maxVolt;
    /**< Maximum voltage supported by the regulator in 10^ (-4) V. */
    uint8_t  type;
    /**< The regulator type namely PMHAL_LP8733_BUCK or PMHAL_LP8733_LDO. */
    uint8_t  minVoltVsel;
    /**< VSEL value corresponding to the minVolt.*/
    uint8_t  maxVoltVsel;
    /**< VSEL value corresponding to the maxVolt.*/
    uint8_t  ctrlRegAddr;
    /**< Register address corresponding to the BUCK/LDO control */
    uint8_t  statRegAddr;
    /**< Register address corresponding to the BUCK/LDO status */
    uint8_t  ctrlEnShift;
    /**< Register bit field shift corresponding to the BUCK/LDO Enable */
    uint8_t  enStatShift;
    /**< Register bit field shift corresponding to whether BUCK/LDO is enabled
     *   or not.
     */
    uint8_t  voutSetRegAddr;
    /**< Register address for setting the Voltage output of the regulator */
} pmhalLP8733RegulatorProp_t;

/** \brief  Pointer to pmhalLP8731RegulatorProp_t structure.
 */
typedef const pmhalLP8733RegulatorProp_t *pmhalLP8733RegulatorPtr_t;

/** \brief  LP8733 Regulator Map description structure. This is used
 *          for keeping track of the regulator connection to the I2C instance
 *          and PMIC device.
 */
typedef struct pmhalLP8733RegulatorMap
{
    pmhalLP8733RegulatorPtr_t regulatorMap;
    /**< Pointer to the regulator properties */
    uint8_t                   i2cInstanceNum;
    /**< SoC I2C instance number to which the regulator of the PMIC will be
     *   connected to.
     */
    uint8_t                   i2cSlaveAddress;
    /**< PMIC slave Address to which the regulator is connected to */
} pmhalLP8733RegulatorMap_t;

/** \brief Pointer to the structure pmhalLP8733RegulatorMap_t */
typedef pmhalLP8733RegulatorMap_t *const pmhalLP8733RegulatorMapPtr_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/** Data structure to describe the regulator for all the regulators. */
extern const pmhalLP8733RegulatorProp_t gPmhalLP8733Regulator[
    PMHAL_LP8733_REGULATOR_MAX];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Get PMIC ops structure. All the other functions are accessed via
 *          function pointers whose array is exported by this function.
 *
 * \return  Return pointer to the PMIC ops structure.
 */
const pmhalPmicOperations_t *PMHALLP8733GetPMICOps(void);

/**
 * \brief The PMIC regulator output to the device input mapping can be
 *        different on different boards. This API can be used to provide
 *        a different mapping to the PMIC driver if the mapping does not
 *        match the default. Example table is shown below:
 *    ------------------------------------------------------------------------
 *    | Device voltage Rail            | Ptr to Regulator                    |
 *    ------------------------------------------------------------------------
 *    | PMHAL_PRCM_PMIC_REGULATOR_CORE | PMHAL_LP8733_REGULATOR_BUCK2        |
 *    | PMHAL_PRCM_PMIC_REGULATOR_DSPEVE| PMHAL_LP8733_REGULATOR_BUCK1       |
 *    | ....                                                                 |
 *    | index (Refer                   | For index of the                    |
 *    | #pmhalPrcmPmicRegulatorId_t)   | gPmhalLP8733Regulator               |
 *    |                                | refer                               |
 *    |                                | #pmhalLP8733RegulatorId_t           |
 *    ------------------------------------------------------------------------
 *       This table when translated to code is as below:
 *       pmhalLP8733RegulatorMap_t regulatorMap[
 *          PMHAL_PRCM_PMIC_REGULATOR_COUNT] = {
 *              {
 *                  &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK1],
 *                  I2C_INSTANCE,
 *                  PMIC_I2C_SLAVE_ADDRESS
 *              },
 *              {
 *                  &gPmhalLP8733Regulator[PMHAL_LP8733_REGULATOR_BUCK2],
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
void PMHALLP8733ConfigureRegulatorMap(pmhalLP8733RegulatorMapPtr_t regulatorMap);

#ifdef __cplusplus
}
#endif

#endif

