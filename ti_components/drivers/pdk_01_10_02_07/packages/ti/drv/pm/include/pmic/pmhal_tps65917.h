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
 *  \file  pmhal_tps65917.h
 *
 *  \brief The Power Management IC (PMIC) tps65917 specific API definition.
 *
 *         The APIs defined here are to control the voltage of the
 *         PMIC rails and to query the status.
 */

#ifndef PM_TPS65917_H_
#define PM_TPS65917_H_

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

/**
 * \brief       PMHAL_TPS65917_SMPS Regulator Register Fields Mask Field
 *              PMHAL_TPS65917_SMPSxx_CTRL.MODE_ACTIVE
 *      1:0     MODE_ACTIVE: PMHAL_TPS65917_SMPS Active Mode
 *              0x00: OFF  (Default)
 *              0x01: Forced PWM
 *              0x10: ECO
 *              0x11: Forced PWM
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_MODE_ACTIVE_MASK      (0x03U)

/**
 * \brief       PMHAL_TPS65917_SMPS Regulator Register Fields Shift Field
 *              PMHAL_TPS65917_SMPSxx_CTRL.MODE_ACTIVE
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_MODE_ACTIVE_SHIFT     (0x0U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.MODE_SLEEP Mask.
 *      3:2     MODE_SLEEP: PMHAL_TPS65917_SMPS Sleep Mode, values/meaning
 *              same as above
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_MODE_SLEEP_MASK       (0x0CU)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.MODE_SLEEP Shift.
 *      3:2     MODE_SLEEP: PMHAL_TPS65917_SMPS Sleep Mode, values/meaning
 *              same as above
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_MODE_SLEEP_SHIFT      (2U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.STATUS Mask.
 *      4:5     STATUS: PMHAL_TPS65917_SMPS Status, values/meaning
 *              same as above.
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_STATUS_MASK           (0x30U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.STATUS Shift.
 *      4:5     STATUS: PMHAL_TPS65917_SMPS Status, values/meaning
 *              same as above.
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_STATUS_SHIFT          (4U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.ROOF_FLOOR_EN Mask.
 *      6       ROOF_FLOOR_EN:
 *              0x0: Voltage selection controlled by FORCE.CMD bit
 *              0x1: Voltage selection controlled by device resource pins.
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_ROOF_FLOOR_EN_MASK    (0x40U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.ROOF_FLOOR_EN Shift.
 *      6       ROOF_FLOOR_EN:
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_ROOF_FLOOR_EN_SHIFT   (6U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.WR_S Mask.
 *      7       WR_S: Warm reset sensitivity
 *              0x0: Reload the default vlaue from OTP (VSEL, CMD etc).
 *              0x1: Maintain the current voltage during warm reset.
 *              (Registers remain unchanged and no voltage change)
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_WR_S_MASK             (0x80U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_CTRL.WR_S Shift.
 *      7       WR_S: Warm reset sensitivity
 */
#define PMHAL_TPS65917_SMPSxx_CTRL_WR_S_SHIFT            (7U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_FORCE.VSEL Mask
 *      6:0     VSEL
 */
#define PMHAL_TPS65917_SMPSxx_FORCE_VSEL_MASK            (0x7FU)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_FORCE.VSEL Shift
 *      6:0     VSEL
 */
#define PMHAL_TPS65917_SMPSxx_FORCE_VSEL_SHIFT           (0U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_FORCE.CMD Mask
 *      7       CMD     (RW but the PMIC HAL will only use the
 *                      default value of 1.)
 *                      CMD is effective only if
 *                      PMHAL_TPS65917_SMPSxx_CTRL.ROOF_FLOOR_EN = 0.
 *              0x0: FORCE.VSEL is applied.
 *              0x1: VOLTAGE.VSEL is applied.
 */
#define PMHAL_TPS65917_SMPSxx_FORCE_CMD_MASK             (0x80U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_FORCE.CMD Shift.
 */
#define PMHAL_TPS65917_SMPSxx_FORCE_CMD_SHIFT            (7U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_VOLTAGE.VSEL Mask.
 *      6:0     VSEL
 *              0x0000000  => 0V (OFF)
 *              0x0000001 - 0x0000110 => 0.5V
 *              Step voltage is 0.01V (10mv)
 *              0x1111001 - 1.65V (max)
 */
#define PMHAL_TPS65917_SMPSxx_VOLTAGE_VSEL_MASK          (0x7FU)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_VOLTAGE.VSEL Shift.
 */
#define PMHAL_TPS65917_SMPSxx_VOLTAGE_VSEL_SHIFT         (0U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_VOLTAGE.RANGE Mask.
 *      7       RANGE  (RW but the PMIC HAL will only support RO)
 */
#define PMHAL_TPS65917_SMPSxx_VOLTAGE_RANGE_MASK         (0x80U)

/**
 * \brief       PMHAL_TPS65917_SMPSxx_VOLTAGE.RANGE Shift.
 */
#define PMHAL_TPS65917_SMPSxx_VOLTAGE_RANGE_SHIFT        (7U)

/** \brief       Control Status Macro for Off */
#define CTRL_STATUS_OFF                   (0U)

/**
 * \brief   PMHAL_TPS65917_LDO Regulator Register Fields:
 *
 *      PMHAL_TPS65917_LDOxx_CTRL.MODE_ACTIVE Mask
 *      0       MODE_ACTIVE: PMHAL_TPS65917_LDO Active Mode
 *              0x00: OFF  (Default)
 *              0x01: ON
 *      1       Reserved
 */
#define PMHAL_TPS65917_LDOxx_CTRL_MODE_ACTIVE_MASK      (0x01U)

/**
 * \brief   PMHAL_TPS65917_LDO Regulator Register
 *          PMHAL_TPS65917_LDOxx_CTRL.MODE_ACTIVE Shift
 */
#define PMHAL_TPS65917_LDOxx_CTRL_MODE_ACTIVE_SHIFT     (0U)

/**
 * \brief       PMHAL_TPS65917_LDOxx_CTRL.MODE_SLEEP Mask
 *      2       MODE_SLEEP: PMHAL_TPS65917_LDO Sleep Mode, values/meaning
 *              same as above
 *      3       Reserved
 */
#define PMHAL_TPS65917_LDOxx_CTRL_MODE_SLEEP_MASK       (0x04U)

/** \brief       PMHAL_TPS65917_LDOxx_CTRL.MODE_SLEEP Shift */
#define PMHAL_TPS65917_LDOxx_CTRL_MODE_SLEEP_SHIFT      (2U)

/**
 * \brief       PMHAL_TPS65917_LDOxx_CTRL.STATUS Mask
 *      4       STATUS: PMHAL_TPS65917_LDO Status, values/meaning
 *              same as above.
 *      6:5     Reserved
 */
#define PMHAL_TPS65917_LDOxx_CTRL_STATUS_MASK           (0x10U)

/** \brief       PMHAL_TPS65917_LDOxx_CTRL.STATUS Shift */
#define PMHAL_TPS65917_LDOxx_CTRL_STATUS_SHIFT          (4U)

/**
 * \brief       PMHAL_TPS65917_LDOxx_CTRL.WR_S Mask
 *      7       WR_S: Warm reset sensitivity
 *              0x0: Reload the default vlaue from OTP (VSEL, CMD etc).
 *              0x1: Maintain the current voltage during warm reset.
 *              (Registers remain unchanged and no voltage change)
 */
#define PMHAL_TPS65917_LDOxx_CTRL_WR_S_MASK             (0x80U)

/** \brief      PMHAL_TPS65917_LDOxx_CTRL.WR_S Mask */
#define PMHAL_TPS65917_LDOxx_CTRL_WR_S_SHIFT            (7U)

/**
 * \brief       PMHAL_TPS65917_LDOxx_VOLTAGE Mask.
 *      5:0     VSEL
 *              0b000000 => 0V (OFF)
 *              0b000001 => 0.9V (min)
 *              Step voltage is 0.05V
 *              0b111111 => 3.3V (max)
 *
 *      7:6     Reserved
 *
 */
#define PMHAL_TPS65917_LDOxx_VOLTAGE_VSEL_MASK          (0x3FU)

/** \brief       PMHAL_TPS65917_LDOxx_VOLTAGE Mask. */
#define PMHAL_TPS65917_LDOxx_VOLTAGE_VSEL_SHIFT         (0U)

/**
 * \brief Slave Address:
 *
 * The TPS65917 PMIC uses the standard 7-bit slave I2C address to access
 * the register address space. This PMIC has 5 internal pages each of 256
 * bytes. The register address is 8-bits and can address one page. Multiple
 * pages are addressed using different slave addresses. The table below
 * gives the slave address for the register pages as programmed in the
 * TDA2xx device EVMs.
 */
#define PMHAL_TPS65917_SLAVE_ADDR_COUNT     (5U)

/**
 *   \brief SLAVE Address Page 0
 *
 *    Page    Phy Addr Range      Slave Address      OTP choice     Register
 *    ------------------------------------------------------------------------
 *     0      0x000 - 0x0FF       0x12                0x12          DVS
 */
#define PMHAL_TPS65917_SLAVE_ADDR_PAGE0     (0x12U)

/**
 *   \brief SLAVE Address Page 1
 *
 *    Page    Phy Addr Range      Slave Address      OTP choice     Register
 *    ------------------------------------------------------------------------
 *     1      0x100 - 0x1FF       0x48 or 0x58        0x58          Power
 */
#define PMHAL_TPS65917_SLAVE_ADDR_PAGE1     (0x58U)

/**
 *   \brief SLAVE Address Page 2
 *
 *    Page    Phy Addr Range      Slave Address      OTP choice     Register
 *    ------------------------------------------------------------------------
 *     2      0x200 - 0x2FF       0x49 or 0x59        0x59          Interfaces
 *                                                                & Auxiliaries
 */
#define PMHAL_TPS65917_SLAVE_ADDR_PAGE2     (0x59U)

/**
 *   \brief SLAVE Address Page 3
 *
 *    Page    Phy Addr Range      Slave Address      OTP choice     Register
 *    ------------------------------------------------------------------------
 *     3      0x300 - 0x3FF       0x4A or 0x5A        0x5A          Trimming
 *                                                                & Test
 */
#define PMHAL_TPS65917_SLAVE_ADDR_PAGE3     (0x5AU)

/**
 *   \brief SLAVE Address Page 4
 *
 *    Page    Phy Addr Range      Slave Address      OTP choice     Register
 *    ------------------------------------------------------------------------
 *     4      0x400 - 0x4FF       0x4B or 0x5B        0x5B          OTP
 */
#define PMHAL_TPS65917_SLAVE_ADDR_PAGE4     (0x5BU)

/** \brief Invalid Page Address */
#define PMHAL_TPS65917_SLAVE_ADDR_INVALID   (0xFFU)

/**
 * \brief Regulator Register Physical Addresses.
 */

/** Regulator SMPS1_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS1_CTRL             (0x120U)
/** Regulator SMPS1_FORCE Physical Address */
#define PMHAL_TPS65917_SMPS1_FORCE            (0x122U)
/** Regulator SMPS1_VOLTAGE Physical Address */
#define PMHAL_TPS65917_SMPS1_VOLTAGE          (0x123U)

/** Regulator SMPS2_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS2_CTRL             (0x124U)
/** Regulator SMPS2_FORCE Physical Address */
#define PMHAL_TPS65917_SMPS2_FORCE            (0x126U)
/** Regulator SMPS2_VOLTAGE Physical Address */
#define PMHAL_TPS65917_SMPS2_VOLTAGE          (0x127U)

/** Regulator SMPS3_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS3_CTRL             (0x12CU)
/** Regulator SMPS3_FORCE Physical Address */
#define PMHAL_TPS65917_SMPS3_FORCE            (0x12EU)
/** Regulator SMPS3_VOLTAGE Physical Address */
#define PMHAL_TPS65917_SMPS3_VOLTAGE          (0x12FU)

/** Regulator SMPS4_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS4_CTRL              (0x130U)
/** Regulator SMPS4_VOLTAGE Physical Address */
#define PMHAL_TPS65917_SMPS4_VOLTAGE           (0x133U)

/** Regulator SMPS5_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS5_CTRL              (0x138U)
/** Regulator SMPS5_VOLTAGE Physical Address */
#define PMHAL_TPS65917_SMPS5_VOLTAGE           (0x13BU)

/** Regulator SMPS_CTRL Physical Address */
#define PMHAL_TPS65917_SMPS_CTRL               (0x144U)

/** Regulator LDO1_CTRL Physical Address */
#define PMHAL_TPS65917_LDO1_CTRL               (0x150U)
/** Regulator LDO1_VOLTAGE Physical Address */
#define PMHAL_TPS65917_LDO1_VOLTAGE            (0x151U)

/** Regulator LDO2_CTRL Physical Address */
#define PMHAL_TPS65917_LDO2_CTRL               (0x152U)
/** Regulator LDO2_VOLTAGE Physical Address */
#define PMHAL_TPS65917_LDO2_VOLTAGE            (0x153U)

/** Regulator LDO3_CTRL Physical Address */
#define PMHAL_TPS65917_LDO3_CTRL               (0x154U)
/** Regulator LDO3_VOLTAGE Physical Address */
#define PMHAL_TPS65917_LDO3_VOLTAGE            (0x155U)

/** Regulator LDO4_CTRL Physical Address */
#define PMHAL_TPS65917_LDO4_CTRL               (0x15EU)
/** Regulator LDO4_VOLTAGE Physical Address */
#define PMHAL_TPS65917_LDO4_VOLTAGE            (0x15FU)

/** Regulator LDO5_CTRL Physical Address */
#define PMHAL_TPS65917_LDO5_CTRL               (0x162U)
/** Regulator LDO5_VOLTAGE Physical Address */
#define PMHAL_TPS65917_LDO5_VOLTAGE            (0x163U)

/** \brief TPS65917 vendor ID LSB. */
#define PMHAL_TPS65917_PHYADDR_VENDOR_ID_LSB   (0x24FU)

/** \brief TPS65917 vendor ID MSB. */
#define PMHAL_TPS65917_PHYADDR_VENDOR_ID_MSB   (0x250U)

/** \brief TPS65917 Product ID LSB. */
#define PMHAL_TPS65917_PHYADDR_PRODUCT_ID_LSB  (0x251U)

/** \brief TPS65917 Product ID MSB. */
#define PMHAL_TPS65917_PHYADDR_PRODUCT_ID_MSB  (0x252U)

/** \brief Expected vendor ID values for TPS65917. */
#define PMHAL_TPS65917_VENDOR_ID            (0x0451U)

/** \brief Expected product ID values for TPS65917 1.0. */
#define PMHAL_TPS65917_1_0_PRODUCT_ID       (0x0917U)

/** \brief Expected product ID values for TPS65917 1.1. */
#define PMHAL_TPS65917_1_1_PRODUCT_ID       (0x9039U)
/**
 * \brief TPS65917 device revision register physical address and the
 *        field definitions.
 */
#define PMHAL_TPS65917_PHYADDR_CHIP_REVISION_ID        (0x357U)

/** \brief Chip Revision ID mask */
#define PMHAL_TPS65917_CHIP_REVISION_ID_MASK          (0x0FU)

/** \brief Chip Revision ID Shift */
#define PMHAL_TPS65917_CHIP_REVISION_ID_SHIFT         (0x0U)

/** \brief Regulator Type for SMPS */
#define PMHAL_TPS65917_RTYPE_SMPS                (1U)

/** \brief Regulator Type for LDO */
#define PMHAL_TPS65917_RTYPE_LDO                 (2U)

/** \brief The I2C number to which the voltage rail is connected */
#define PMHAL_TPS65917_I2C_NUM_1                 (0x0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Abstract Enumeration for the Regulators.
 */
typedef enum pmhalTps65917RegulatorId
{
    PMHAL_TPS65917_REGULATOR_INVALID = (-(int32_t)1),
    /**< Invalid PMIC regulator ID */
    PMHAL_TPS65917_REGULATOR_MIN = 0,
    /**< Minimum Abstracted PMIC Regulator ID */
    PMHAL_TPS65917_REGULATOR_SMPS1 = PMHAL_PRCM_PMIC_REGULATOR_MIN,
    /**< Abstracted PMIC Regulator ID for SMPS1 */
    PMHAL_TPS65917_REGULATOR_SMPS2 = 1,
    /**< Abstracted PMIC Regulator ID for SMPS2 */
    PMHAL_TPS65917_REGULATOR_SMPS3 = 2,
    /**< Abstracted PMIC Regulator ID for SMPS3 */
    PMHAL_TPS65917_REGULATOR_SMPS4 = 3,
    /**< Abstracted PMIC Regulator ID for SMPS4*/
    PMHAL_TPS65917_REGULATOR_SMPS5 = 4,
    /**< Abstracted PMIC Regulator ID for SMPS5*/
    PMHAL_TPS65917_REGULATOR_LDO1 = 5,
    /**< Abstracted PMIC Regulator ID for LDO1 */
    PMHAL_TPS65917_REGULATOR_LDO2 = 6,
    /**< Abstracted PMIC Regulator ID for LDO2 */
    PMHAL_TPS65917_REGULATOR_LDO3 = 7,
    /**< Abstracted PMIC Regulator ID for LDO3 */
    PMHAL_TPS65917_REGULATOR_LDO4 = 8,
    /**< Abstracted PMIC Regulator ID for LDO4 */
    PMHAL_TPS65917_REGULATOR_LDO5 = 9,
    /**< Abstracted PMIC Regulator ID for LDO5 */
    PMHAL_TPS65917_REGULATOR_MAX = (PMHAL_TPS65917_REGULATOR_LDO5 + 1)
} pmhalTps65917RegulatorId_t;

/**
 * \brief TPS65917 Regulator description structure
 */
typedef struct pmhalTps65917RegulatorProp
{
    uint16_t minVolt;
    /**< Minimum voltage supported by the regulator in mV. */
    uint16_t maxVolt;
    /**< Maximum voltage supported by the regulator in mV. */
    uint8_t  stepVolt;
    /**< Step voltage in mV. */
    uint8_t  type;
    /**< The regulator type namely PMHAL_TPS659039_SMPS or
     * PMHAL_TPS659039_LDO.
     */
    uint16_t slewRate;
    /**< The voltage ramp delay in uV/us */
    uint16_t minVoltVsel;
    /**< VSEL value corresponding to the minVolt.*/
    uint16_t maxVoltVsel;
    /**< VSEL value corresponding to the maxVolt.*/
    uint32_t ctrlRegAddr;
    /**< The regulator control register address.*/
    uint32_t voltRegAddr;
    /**< The regulator voltage register address.*/
    uint32_t forceRegAddr;
    /**< The regulator force command voltage register address. Not all
     *   regulators have the force register; if not present the value
     *   of this field is expected to be NULL. */
} pmhalTps65917RegulatorProp_t;

/** \brief  Pointer to pmhalTps65917RegulatorProp_t structure.
 */
typedef const pmhalTps65917RegulatorProp_t *pmhalTps65917RegulatorPtr_t;

/** \brief  TPS65917 Regulator Map description structure. This is used
 *          for keeping track of the regulator connection to the I2C instance
 *          and PMIC device.
 */
typedef struct pmhalTps65917RegulatorMap
{
    pmhalTps65917RegulatorPtr_t regulatorMap;
    /**< Pointer to the regulator properties */
    uint8_t                     i2cInstanceNum;
    /**< SoC I2C instance number to which the regulator of the PMIC will be
     *   connected to.
     */
} pmhalTps65917RegulatorMap_t;

/** \brief Pointer to the structure pmhalTps65917RegulatorMap_t */
typedef pmhalTps65917RegulatorMap_t *const pmhalTps65917RegulatorMapPtr_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/** Array of the properties of all the SMPS and LDO PMIC regulators */
extern const pmhalTps65917RegulatorProp_t gPmhalTps65917Regulator[
    PMHAL_TPS65917_REGULATOR_MAX];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Get PMIC ops structure. All the other functions are accessed via
 *          function pointers whose array is exported by this function.
 *
 * \return  Return pointer to the PMIC ops structure.
 */
const pmhalPmicOperations_t *PMHALTps65917GetPMICOps(void);

/**
 * \brief   The PMIC regulator output to the device input mapping can be
 *          different on different boards. This API can be used to provide
 *          a different mapping to the PMIC driver if the mapping does not
 *          match the default. Example table is shown below:
 *       ---------------------------------------------------------------------
 *       | Device voltage Rail            | Ptr to Regulator                 |
 *       ---------------------------------------------------------------------
 *       | PMHAL_PRCM_PMIC_REGULATOR_MPU  | PMHAL_TPS65917_REGULATOR_SMPS1   |
 *       | PMHAL_PRCM_PMIC_REGULATOR_CORE | PMHAL_TPS65917_REGULATOR_SMPS2   |
 *       | ....                                                              |
 *       | index (Refer                   | For index of the                 |
 *       | #pmhalPrcmPmicRegulatorId_t)   | gPmhalTps65917Regulator          |
 *       |                                | refer                            |
 *       |                                | #pmhalTps65917RegulatorId_t      |
 *       ---------------------------------------------------------------------
 *          This table when translated to code is as below:
 *       pmhalTps65917RegulatorMap_t regulatorMap[
 *          PMHAL_PRCM_PMIC_REGULATOR_COUNT] = {
 *              {
 *                  &gPmhalTps65917Regulator[PMHAL_TPS65917_REGULATOR_SMPS1],
 *                  I2C_INSTANCE,
 *                  PMIC_I2C_SLAVE_ADDRESS
 *              },
 *              {
 *                  &gPmhalTps65917Regulator[PMHAL_TPS65917_REGULATOR_SMPS2],
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
void PMHALTps65917ConfigureRegulatorMap(
    pmhalTps65917RegulatorMapPtr_t regulatorMap);

#ifdef __cplusplus
}
#endif

#endif

