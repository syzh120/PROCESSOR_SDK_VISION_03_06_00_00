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
 *  \file  pmhal_lp87565.h
 *
 *  \brief The Power Management IC (PMIC) lp87565 specific API definition.
 *
 *         The APIs defined here are to control the voltage of the
 *         PMIC rails and to query the status.
 */

#ifndef PM_LP87565_H_
#define PM_LP87565_H_

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

/** \brief Maximum Number of PMIC Revisions available */
#define PMHAL_PMIC_MAX_REV                   (4U)

/** \brief Device Revision Register */
#define PMHAL_LP87565_REG_DEV_REV              (0x00U)
/** \brief OTP Revision Register */
#define PMHAL_LP87565_REG_OTP_REV              (0x01U)
/** \brief Buck Control register */
#define PMHAL_LP87565_REG_BUCK0_CTRL_1         (0x02U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK0_CTRL_2         (0x03U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK1_CTRL_1         (0x04U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK1_CTRL_2         (0x05U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK2_CTRL_1         (0x06U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK2_CTRL_2         (0x07U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK3_CTRL_1         (0x08U)
/** \brief Buck Control Register */
#define PMHAL_LP87565_REG_BUCK3_CTRL_2         (0x09U)
/** \brief Sets the output voltage of Buck0 regulator */
#define PMHAL_LP87565_REG_BUCK0_VOUT           (0x0AU)
/** \brief Sets the output voltage of Buck0 regulator when Floor state is
 *         used.
 */
#define PMHAL_LP87565_REG_BUCK0_FLOOR_VOUT     (0x0BU)
/** \brief Sets the output voltage of Buck1 regulator */
#define PMHAL_LP87565_REG_BUCK1_VOUT           (0x0CU)
/** \brief Sets the output voltage of Buck0 regulator when Floor state is
 *         used.
 */
#define PMHAL_LP87565_REG_BUCK1_FLOOR_VOUT     (0x0DU)
/** \brief Sets the output voltage of Buck2 regulator */
#define PMHAL_LP87565_REG_BUCK2_VOUT           (0x0EU)
/** \brief Sets the output voltage of Buck2 regulator when Floor state is
 *         used.
 */
#define PMHAL_LP87565_REG_BUCK2_FLOOR_VOUT     (0x0FU)
/** \brief Sets the output voltage of Buck3 regulator */
#define PMHAL_LP87565_REG_BUCK3_VOUT           (0x10U)
/** \brief Sets the output voltage of Buck3 regulator when Floor state is
 *         used.
 */
#define PMHAL_LP87565_REG_BUCK3_FLOOR_VOUT     (0x11U)
/** \brief Shutdown and Startup delay of Buck0 */
#define PMHAL_LP87565_REG_BUCK0_DELAY          (0x12U)
/** \brief Shutdown and Startup delay of Buck1 */
#define PMHAL_LP87565_REG_BUCK1_DELAY          (0x13U)
/** \brief Shutdown and Startup delay of Buck2 */
#define PMHAL_LP87565_REG_BUCK2_DELAY          (0x14U)
/** \brief Shutdown and Startup delay of Buck3 */
#define PMHAL_LP87565_REG_BUCK3_DELAY          (0x15U)
/** \brief Status register for Buck 0 and 1 */
#define PMHAL_LP87565_REG_BUCK_0_1_STAT        (0x1FU)
/** \brief Status register for Buck 2 and 3 */
#define PMHAL_LP87565_REG_BUCK_2_3_STAT        (0x20U)

/** \brief LP87565 Device ID mask */
#define PMHAL_LP87565_DEV_REV_DEV_ID_MASK            (0xC0U)
/** \brief LP87565 Device ID shift */
#define PMHAL_LP87565_DEV_REV_DEV_ID_SHIFT           (0x6U)
/** \brief LP87565 All Layer PG mask */
#define PMHAL_LP87565_DEV_REV_ALL_LAYER_MASK         (0x30U)
/** \brief LP87565 All Layer PG shift */
#define PMHAL_LP87565_DEV_REV_ALL_LAYER_SHIFT        (0x4U)
/** \brief LP87565 Metal Layer PG mask */
#define PMHAL_LP87565_DEV_REV_METAL_LAYER_MASK       (0x0FU)
/** \brief LP87565 Metal Layer PG shift */
#define PMHAL_LP87565_DEV_REV_METAL_LAYER_SHIFT      (0x0U)
/** \brief LP87565 OTP ID mask */
#define PMHAL_LP87565_OTP_REV_OTP_ID_MASK            (0xFFU)
/** \brief LP87565 OTP ID shift */
#define PMHAL_LP87565_OTP_REV_OTP_ID_SHIFT           (0x0U)

/** \brief LP87565 Buck 1 Control Enable Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_EN_MASK            (0x80U)
/** \brief LP87565 Buck 1 Control Enable Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_EN_SHIFT           (0x7U)
/** \brief LP87565 Buck 1 Control Enable Pin Control Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_EN_PIN_CTRL_MASK   (0x40U)
/** \brief LP87565 Buck 1 Control Enable Pin Control Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_EN_PIN_CTRL_SHIFT  (0x6U)
/** \brief LP87565 Buck 1 Control Pin Select Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_PIN_SELECT_EN_MASK  (0x30U)
/** \brief LP87565 Buck 1 Control Pin Select Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_PIN_SELECT_EN_SHIFT (0x4U)

/** \brief LP87565 Buck 1 Control Roof Floor Enable Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_ROOF_FLOOR_EN_MASK  (0x08U)
/** \brief LP87565 Buck 1 Control Roof Floor Enable Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_ROOF_FLOOR_EN_SHIFT (0x3U)
/** \brief LP87565 Buck 1 Control RDIS Enable Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_RDIS_EN_MASK       (0x04U)
/** \brief LP87565 Buck 1 Control RDIS Enable Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_RDIS_EN_SHIFT      (0x2U)
/** \brief LP87565 Buck 1 Control FPWM Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_FPWM_MASK          (0x02U)
/** \brief LP87565 Buck 1 Control FPWM Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_FPWM_SHIFT         (0x1U)
/* Bit0 is reserved for BUCK1 and BUCK3 and valid only for BUCK0 and BUCK2 */
/** \brief LP87565 Buck 1 Control FPWM MP Mask */
#define PMHAL_LP87565_BUCK_CTRL_1_FPWM_MP_0_2_MASK   (0x01U)
/** \brief LP87565 Buck 1 Control FPWM MP Shift */
#define PMHAL_LP87565_BUCK_CTRL_1_FPWM_MP_0_2_SHIFT  (0x0U)

/** \brief LP87565 Buck Control Current Limit Mask */
#define PMHAL_LP87565_BUCK_CTRL_2_ILIM_MASK          (0x38U)
/** \brief LP87565 Buck Control Current Limit Shift */
#define PMHAL_LP87565_BUCK_CTRL_2_ILIM_SHIFT         (0x3U)
/** \brief LP87565 Buck Control Slew Rate Mask */
#define PMHAL_LP87565_BUCK_CTRL_2_SLEW_RATE_MASK     (0x07U)
/** \brief LP87565 Buck Control Slew Rate Shift */
#define PMHAL_LP87565_BUCK_CTRL_2_SLEW_RATE_SHIFT    (0x0U)

/** \brief LP87565 Buck Vset Mask */
#define PMHAL_LP87565_BUCK_VSET_MASK                 (0xFFU)
/** \brief LP87565 Buck Vset Shift */
#define PMHAL_LP87565_BUCK_VSET_SHIFT                (0x00U)
/** \brief LP87565 Buck Vset Floor Mask */
#define PMHAL_LP87565_BUCK_FLOOR_VSET_MASK           (0xFFU)
/** \brief LP87565 Buck Vset Floor Shift */
#define PMHAL_LP87565_BUCK_FLOOR_VSET_SHIFT          (0x00U)

/** \brief LP87565 Buck Shutdown delay Mask */
#define PMHAL_LP87565_BUCK_SHUTDOWN_DELAY_MASK       (0xF0U)
/** \brief LP87565 Buck Shutdown delay Shift */
#define PMHAL_LP87565_BUCK_SHUTDOWN_DELAY_SHIFT      (0x04U)
/** \brief LP87565 Buck Startup delay Mask */
#define PMHAL_LP87565_BUCK_STARTUP_DELAY_MASK        (0x0FU)
/** \brief LP87565 Buck Startup delay Shift */
#define PMHAL_LP87565_BUCK_STARTUP_DELAY_SHIFT       (0x00U)

/** \brief LP87565 GPIO shutdown delay Mask */
#define PMHAL_LP87565_GPIO_SHUTDOWN_DELAY_MASK       (0xF0U)
/** \brief LP87565 GPIO shutdown delay Shift */
#define PMHAL_LP87565_GPIO_SHUTDOWN_DELAY_SHIFT      (0x4U)
/** \brief LP87565 GPIO startup delay Mask */
#define PMHAL_LP87565_GPIO_STARTUP_DELAY_MASK        (0x0FU)
/** \brief LP87565 GPIO startup delay Shift */
#define PMHAL_LP87565_GPIO_STARTUP_DELAY_SHIFT       (0x00U)

/** \brief LP87565 Buck1 status Mask */
#define PMHAL_LP87565_BUCK1_STAT_MASK               (0x80U)
/** \brief LP87565 Buck1 status Shift */
#define PMHAL_LP87565_BUCK1_STAT_SHIFT              (0x07U)
/** \brief LP87565 Buck1 PGood status Mask */
#define PMHAL_LP87565_BUCK1_PG_STAT_MASK            (0x40U)
/** \brief LP87565 Buck1 PGood status Shift */
#define PMHAL_LP87565_BUCK1_PG_STAT_SHIFT           (0x06U)
/** \brief LP87565 Buck1 Current Limit status Mask */
#define PMHAL_LP87565_BUCK1_ILIM_STAT_MASK          (0x10U)
/** \brief LP87565 Buck1 Current Limit status Shift */
#define PMHAL_LP87565_BUCK1_ILIM_STAT_SHIFT         (0x04U)
/** \brief LP87565 Buck0 status Mask */
#define PMHAL_LP87565_BUCK0_STAT_MASK               (0x08U)
/** \brief LP87565 Buck0 status Shift */
#define PMHAL_LP87565_BUCK0_STAT_SHIFT              (0x03U)
/** \brief LP87565 Buck0 PGood status Mask */
#define PMHAL_LP87565_BUCK0_PG_STAT_MASK            (0x04U)
/** \brief LP87565 Buck0 PGood status Shift */
#define PMHAL_LP87565_BUCK0_PG_STAT_SHIFT           (0x02U)
/** \brief LP87565 Buck0 Current Limit status Mask */
#define PMHAL_LP87565_BUCK0_ILIM_STAT_MASK          (0x01U)
/** \brief LP87565 Buck0 Current Limit status Shift */
#define PMHAL_LP87565_BUCK0_ILIM_STAT_SHIFT         (0x00U)

/** \brief LP87565 Buck3 status Mask */
#define PMHAL_LP87565_BUCK3_STAT_MASK               (0x80U)
/** \brief LP87565 Buck3 status shift */
#define PMHAL_LP87565_BUCK3_STAT_SHIFT              (0x7U)
/** \brief LP87565 Buck3 PGood status Mask */
#define PMHAL_LP87565_BUCK3_PG_STAT_MASK            (0x40U)
/** \brief LP87565 Buck3 PGood status Shift */
#define PMHAL_LP87565_BUCK3_PG_STAT_SHIFT           (0x6U)
/** \brief LP87565 Buck3 Current Limit status Mask */
#define PMHAL_LP87565_BUCK3_ILIM_STAT_MASK          (0x10U)
/** \brief LP87565 Buck3 Current Limit status Shift */
#define PMHAL_LP87565_BUCK3_ILIM_STAT_SHIFT         (0x4U)
/** \brief LP87565 Buck2 status Mask */
#define PMHAL_LP87565_BUCK2_STAT_MASK               (0x08U)
/** \brief LP87565 Buck2 status Shift */
#define PMHAL_LP87565_BUCK2_STAT_SHIFT              (0x3U)
/** \brief LP87565 Buck2 PGood status Mask */
#define PMHAL_LP87565_BUCK2_PG_STAT_MASK            (0x04U)
/** \brief LP87565 Buck2 PGood status Shift */
#define PMHAL_LP87565_BUCK2_PG_STAT_SHIFT           (0x2U)
/** \brief LP87565 Buck2 Current Limit status Mask */
#define PMHAL_LP87565_BUCK2_ILIM_STAT_MASK          (0x01U)
/** \brief LP87565 Buck2 Current Limit status Shift */
#define PMHAL_LP87565_BUCK2_ILIM_STAT_SHIFT         (0x0U)

/** \brief Expected vendor ID values for LP87565. */
#define PMHAL_LP87565_VENDOR_ID            (0x0451U)

/** \brief Expected product ID values for LP87565 1.0. */
#define PMHAL_LP87565_1_0_PRODUCT_ID       (0x0917U)

/** \brief The I2C number to which the voltage rail is connected */
#define PMHAL_LP87565_I2C_NUM                   (0x0U)

/** \brief The I2C Address to which the voltage rail is connected */
#define PMHAL_LP87565_I2C_ADDR                  (0x60U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Abstract Enumeration for the Regulators.
 */
typedef enum pmhalLp87565RegulatorId
{
    PMHAL_LP87565_REGULATOR_INVALID = (-(int32_t)1),
    /**< Invalid PMIC regulator ID */
    PMHAL_LP87565_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator ID */
    PMHAL_LP87565_REGULATOR_BUCK_0 = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for Buck 0 */
    PMHAL_LP87565_REGULATOR_BUCK_1 = 1,
    /**< Abstracted PMIC Regulator ID for Buck 1 */
    PMHAL_LP87565_REGULATOR_BUCK_2 = 2,
    /**< Abstracted PMIC Regulator ID for Buck 2 */
    PMHAL_LP87565_REGULATOR_BUCK_3 = 3,
    /**< Abstracted PMIC Regulator ID for Buck 3 */
    PMHAL_LP87565_REGULATOR_BUCK_01 = 4,
    /**< Abstracted PMIC Regulator ID for Buck 01 */
    PMHAL_LP87565_REGULATOR_BUCK_23 = 5,
    /**< Abstracted PMIC Regulator ID for Buck 23 */
    PMHAL_LP87565_REGULATOR_MAX = (PMHAL_LP87565_REGULATOR_BUCK_23 + 1)
} pmhalLp87565RegulatorId_t;

/**
 * \brief LP87565 Regulator description structure
 */
typedef struct pmhalLp87565RegulatorProp
{
    uint32_t ctrlRegAddr;
    /**< The regulator control register address.*/
    uint32_t voltRegAddr;
    /**< The regulator voltage register address.*/
    uint32_t floorVoltRegAddr;
    /**< The regulator voltage register address.*/
    uint32_t statusRegAddr;
    /**< The regulator voltage register address.*/
    uint8_t  enStatShift;
    /**< Shift value for the enable status */
} pmhalLp87565RegulatorProp_t;

/** \brief  Pointer to pmhalLp87565RegulatorProp_t structure.
 */
typedef const pmhalLp87565RegulatorProp_t *pmhalLp87565RegulatorPtr_t;

/** \brief  LP87565 Regulator Map description structure. This is used
 *          for keeping track of the regulator connection to the I2C instance
 *          and PMIC device.
 */
typedef struct pmhalLp87565RegulatorMap
{
    pmhalLp87565RegulatorPtr_t regulatorMap;
    /**< Pointer to the regulator properties */
    uint8_t                    i2cInstanceNum;
    /**< SoC I2C instance number to which the regulator of the PMIC will be
     *   connected to.
     */
    uint8_t                    i2cAddr;
    /**< SoC I2C address to which the regulator of the PMIC will be connected */
} pmhalLp87565RegulatorMap_t;

/** \brief Pointer to the structure pmhalLp87565RegulatorMap_t */
typedef pmhalLp87565RegulatorMap_t *const pmhalLp87565RegulatorMapPtr_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/** Array of the properties of all the SMPS and LDO PMIC regulators */
extern const pmhalLp87565RegulatorProp_t gPmhalLp87565Regulator[
    PMHAL_LP87565_REGULATOR_MAX];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Get PMIC ops structure. All the other functions are accessed via
 *          function pointers whose array is exported by this function.
 *
 * \return  Return pointer to the PMIC ops structure.
 */
const pmhalPmicOperations_t *PMHALLP87565GetPMICOps(void);

/**
 * \brief   The PMIC regulator output to the device input mapping can be
 *          different on different boards. This API can be used to provide
 *          a different mapping to the PMIC driver if the mapping does not
 *          match the default. Example table is shown below:
 *       ---------------------------------------------------------------------
 *       | Device voltage Rail            | Ptr to Regulator                 |
 *       ---------------------------------------------------------------------
 *       | PMHAL_PRCM_PMIC_REGULATOR_MPU  | PMHAL_LP87565_REGULATOR_SMPS1   |
 *       | PMHAL_PRCM_PMIC_REGULATOR_CORE | PMHAL_LP87565_REGULATOR_SMPS2   |
 *       | ....                                                              |
 *       | index (Refer                   | For index of the                 |
 *       | #pmhalPrcmPmicRegulatorId_t)   | gPmhalLp87565Regulator          |
 *       |                                | refer                            |
 *       |                                | #pmhalLp87565RegulatorId_t      |
 *       ---------------------------------------------------------------------
 *          This table when translated to code is as below:
 *       pmhalLp87565RegulatorMap_t regulatorMap[
 *          PMHAL_PRCM_PMIC_REGULATOR_COUNT] = {
 *              {
 *                  &gPmhalLp87565Regulator[PMHAL_LP87565_REGULATOR_SMPS1],
 *                  I2C_INSTANCE,
 *                  PMIC_I2C_SLAVE_ADDRESS
 *              },
 *              {
 *                  &gPmhalLp87565Regulator[PMHAL_LP87565_REGULATOR_SMPS2],
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
void PMHALLP87565ConfigureRegulatorMap(
    pmhalLp87565RegulatorMapPtr_t regulatorMap);

#ifdef __cplusplus
}
#endif

#endif

